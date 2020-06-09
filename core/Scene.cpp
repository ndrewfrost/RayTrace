/*
 * Scene.cpp
 *
 */
#include "Scene.h"




namespace rt {

    /**
     * Parses json scene object to generate scene to render
     *
     * @param scenespecs the json scene specificatioon
     */
    void Scene::createScene(Value& scenespecs) {

        readBackgroundColor(scenespecs);

        Value& lights = scenespecs["lightsources"];
        readLights(lights);

        Value& shapes = scenespecs["shapes"];
        for (int i = 0; i < shapes.Size(); i++) {
            this->shapes.push_back(readShape(shapes[i]));
        }
    }

    void Scene::readBackgroundColor(Value& scenespecs) {
        if (scenespecs.HasMember("backgroundcolor")) {
            assert(scenespecs.GetObject()["backgroundcolor"].IsArray());
            Vec3f background = readVec3f(scenespecs.GetObject()["backgroundcolor"], "background color");
            backgroundColor = background;
        }
        else {
            backgroundColor.x = 0.01f;
            backgroundColor.y = 0.01f;
            backgroundColor.z = 0.01f;
        }
    }

    
    void Scene::readLights(Value& lights) {
        for (SizeType i = 0; i < lights.Size(); i++) {
            assert(lights[i].HasMember("type") && lights[i]["type"].IsString());
            //PointLight
            if (lights[i]["type"] == "pointlight") {
                Vec3f position = readVec3f(lights[i]["position"], "light position");
                Vec3f color = readVec3f(lights[i]["color"], "color");
                float intensity = lights[i]["intensity"].GetFloat();
                PointLight* point = new PointLight(position, color, intensity);
                lightSources.push_back(point);
            }
            //AreaLight
            else if (lights[i]["type"] == "arealight") {
                Vec3f position = readVec3f(lights[i]["position"], "light position");
                Vec3f color = readVec3f(lights[i]["color"], "color");
                float intensity = lights[i]["intensity"].GetFloat();
                std::string sampling = lights[i]["sampling"].GetString();
                int samples = lights[i]["samples"].GetInt();
                Value& s = lights[i]["shape"];
                Shape* shape = readShape(lights[i]["shape"]);
                AreaLight* area = new AreaLight(position, color, intensity, shape, sampling, samples);
                lightSources.push_back(area);
            }

            else {
                std::cerr << "Light type must be arealight or pointlight" << std::endl;
                exit(-1);
            }
        }
    }

    Shape* Scene::readShape(Value& shape) {
        assert(shape.HasMember("type") && shape["type"].IsString());
        //SPHERE
        if (shape["type"] == "sphere") {
            Vec3f centre = readVec3f(shape["center"], "sphere centre");
            float radius = shape["radius"].GetFloat();
            Value& materialValue = shape["material"];
            BlinnPhong material = readMaterial(materialValue);
            Sphere* sphere;
            if (shape.HasMember("texture")) {
                std::string textureLocation = shape["texture"].GetString();
                sphere = new Sphere(centre, radius, material, textureLocation);
            }
            else {
                sphere = new Sphere(centre, radius, material);
            }
            return sphere;
        }
        //TRIANGLE
        else if (shape["type"] == "triangle") {
            Vec3f point[3];
            point[0] = readVec3f(shape["points"][0], "point 1 triangle");
            point[1] = readVec3f(shape["points"][1], "point 2 triangle");
            point[2] = readVec3f(shape["points"][2], "point 3 triangle");

            Vec3f e = point[0] - point[1];
            Vec3f e2 = point[0] - point[2];
            Vec3f normal = e.crossProduct(e2).normalize();
            if (shape.HasMember("normal")) {
                int n = shape["normal"].GetInt();
                if (n != -1) {
                    std::cerr << "the normal can only be -1";
                    exit(-1);
                }
                normal = n * normal;
            }

            Value& materialValue = shape["material"];
            BlinnPhong material = readMaterial(materialValue);

            Triangle* triangle;
            if (shape.HasMember("texture")) {
                std::string textureLocation = shape["texture"].GetString();
                triangle = new Triangle(point, normal, material, textureLocation);
            }
            else {
                triangle = new Triangle(point, normal, material);
            }

            return triangle;
        }
        //PLANE
        else if (shape["type"] == "plane") {
            Vec3f point[4];
            point[0] = readVec3f(shape["points"][0], "point 1 plane");
            point[1] = readVec3f(shape["points"][1], "point 2 plane");
            point[2] = readVec3f(shape["points"][2], "point 3 plane");
            point[3] = readVec3f(shape["points"][3], "point 4 plane");
            Vec3f e = point[0] - point[1];
            Vec3f e2 = point[0] - point[2];
            Vec3f normal = e.crossProduct(e2).normalize();
            if (shape.HasMember("normal")) {
                int n = shape["normal"].GetInt();
                if (n != -1) {
                    std::cerr << "the normal can only be -1";
                    exit(-1);
                }
                normal = n * normal;
            }
            Value& materialValue = shape["material"];
            BlinnPhong material = readMaterial(materialValue);
            Plane* plane;
            if (shape.HasMember("texture")) {
                std::string textureLocation = shape["texture"].GetString();
                plane = new Plane(point, normal, material, textureLocation);
            }
            else {
                plane = new Plane(point, normal, material);
            }
            return plane;
        }
        ///TRIMESH
        else if (shape["type"] == "trimesh") {
            int size = shape["size"].GetInt();

            if (size < 2) {
                std::cerr << "tri mesh must have atleast 3 points" << std::endl;
                exit(-1);
            }
            Value& materialValue = shape["material"];
            BlinnPhong material = readMaterial(materialValue);

            TriMesh* tri = new TriMesh(size, material);
            for (int s = 0; s < size; s++) {
                Vec3f vec = readVec3f(shape["points"][s], "point trimesh");
                tri->addVertex(vec);
            }

            if (shape.HasMember("normal")) {
                for (int s = 0; s < size - 2; s++) {
                    int n = shape["normal"][s].GetInt();
                    if ( n != 0 && n != -1) {
                        std::cerr << "trimesh normals can only be -1 or 0";
                        exit(-1);
                    }
                    tri->addNormal(n);
                }
            }

            for (int s = 0; s < size - 2; s++) {
                tri->addFace(s, s + 1, s + 2);
            }

            return tri;
        }

        else {
            std::cerr << "Shape type must be sphere,plane, triangle, trimesh" << std::endl;
            exit(-1);
        }

    }

    BlinnPhong Scene::readMaterial(Value& material) {
        float ks = material["ks"].GetFloat();
        float kd = material["kd"].GetFloat();
        float kr = 0.f;
        if (material.HasMember("kr")) {
            kr = material["kr"].GetFloat();
        }
        float specularExponent = material["specularexponent"].GetFloat();
        Vec3f diffuseColor = readVec3f(material["diffusecolor"], "material Diffuse Color ");
        BlinnPhong blinn = BlinnPhong(ks, kd, kr, specularExponent, diffuseColor);
        return blinn;
    }

    Vec3f Scene::readVec3f(Value& val, char* jsonLocation) {
        std::vector<float> values;
        for (auto& v : val.GetArray())
            values.push_back(v.GetFloat());

        if (values.size() != 3) {
            std::cerr << jsonLocation << ": Vec3f size must be 3" << std::endl;
        }

        Vec3f vec(values[0], values[1], values[2]);
        return vec;
    }

    Vec2f Scene::readVec2f(Value& val, char* jsonLocation) {
        std::vector<float> values;
        for (auto& v : val.GetArray())
            values.push_back(v.GetFloat());

        if (values.size() != 2) {
            std::cerr << jsonLocation << " Vec2f size must be 2" << std::endl;
        }

        Vec2f vec(values[0], values[1]);
        return vec;
    }


} //namespace rt
