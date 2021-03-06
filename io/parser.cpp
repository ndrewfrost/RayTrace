#include "parser.h"

///////////////////////////////////////////////////////////////////////////
// Parser                                                                //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
//
//
std::shared_ptr<Settings> Parser::readSettings(Value& value)
{
    assert(value.HasMember("width")   && "Must specify [width] setting");
    assert(value.HasMember("height")  && "Must specify [height] setting");
    assert(value.HasMember("samples") && "Must specify [samples] setting");

    unsigned int width   = value["width"].GetInt();
    unsigned int height  = value["height"].GetInt();
    unsigned int samples = value["samples"].GetInt();
    bool bvh             = value["bvh"].GetBool();

    return std::make_shared<Settings>(width, height, samples, bvh);
}

//-------------------------------------------------------------------------
// Create a camera object, either Pinhole or Thin lens
// Depending on the data from JSON in Value& CameraSpecs
//
std::unique_ptr<Camera> Parser::readCamera(Value& value, std::shared_ptr<Settings> settings)
{
    // check if defined cameratype
    assert(value.HasMember("type") && "Camera type not specified");

    const std::string cameraType = readString(value["type"], "Camera type"); 

    float aspectRatio = static_cast<float>(settings->width) / static_cast<float>(settings->height);

    // Pinhole Camera
    if (cameraType == "pinhole") {

        glm::vec3 origin  = readVector(value["origin"], "Camera origin");
        glm::vec3 lookAt  = readVector(value["lookat"], "Camera lookAt");
        glm::vec3 vup     = readVector(value["vup"], "Camera vup");
        float hfov        = readFloat(value["hfov"], "Camera hfov");

        return std::make_unique<Pinhole>(Pinhole(origin, lookAt, vup, hfov, aspectRatio));
    }
    // Thin lens Camera
    else if (cameraType == "thinlens") {

        glm::vec3 origin = readVector(value["origin"], "Camera origin");
        glm::vec3 lookAt = readVector(value["lookat"], "Camera lookAt");
        glm::vec3 vup    = readVector(value["vup"], "Camera vup");
        float hfov       = readFloat(value["hfov"], "Camera hfov");
        float focalDist  = readFloat(value["focaldistance"], "Camera focal distance");
        float aperture   = readFloat(value["aperture"], "Camera aperture");

        return std::make_unique<ThinLens>(ThinLens(origin, lookAt, vup, hfov, aspectRatio, aperture, focalDist));
    }
    // Error
    else {
        std::cerr << "Camera type can either be: [pinhole] or [thinlens]" << std::endl;
        exit(-1);
    }
}

//-------------------------------------------------------------------------
// Read and generate the world geometry
//
std::unique_ptr<Scene> Parser::readScene(Value& value, std::shared_ptr<Settings> settings)
{    
    std::vector<std::shared_ptr<Light>>     sceneLights;
    std::vector<std::shared_ptr<AreaLight>> sceneAreaLights;

    std::vector<std::shared_ptr<Geometry>>  sceneGeometry;
    MaterialList                            sceneMaterials;

    Value& materials = value["materials"];
    for (unsigned int i = 0; i < materials.Size(); ++i) {
        storeMaterial(sceneMaterials, materials[i]);
    }

    Value& geometry = value["geometry"];
    for (unsigned int i = 0; i < geometry.Size(); ++i) {
        sceneGeometry.push_back(readGeometry(geometry[i], &sceneMaterials));
    }

    Value& lights = value["lights"];
    for (unsigned int i = 0; i < lights.Size(); ++i) {
        sceneLights.push_back(readLight(lights[i]));
    }

    // If using BVH load it here
    if (settings->bvh) {
        std::vector<std::shared_ptr<Geometry>> BVH;
        BVH.push_back(std::make_shared<BVHNode>(BVHNode(sceneGeometry, 0, sceneGeometry.size())));
        return std::make_unique<Scene>(Scene(BVH, sceneLights));
    }
    else {
        return std::make_unique<Scene>(Scene(sceneGeometry, sceneLights));
    }   
}

//-------------------------------------------------------------------------
// Read and store a material to be referenced by geometry
//
void Parser::storeMaterial(MaterialList& sceneMaterials, Value& material)
{
    assert(material.HasMember("name")  && "defined materials must have members : [name]");
    assert(material.HasMember("type")  && "defined materials must have members : [type]");

    std::string name = readString(material["name"], "material name");
    std::string type = readString(material["type"], "material name");

    sceneMaterials.insert(std::make_pair(name, readMaterial(material)));
}

//-------------------------------------------------------------------------
// Generate a geometry primitive
//
std::shared_ptr<Geometry> Parser::readGeometry(Value& geometry, MaterialList* sceneMaterials = nullptr)
{
    assert(geometry.HasMember("type") && "geometry must have type member");

    // Geometry material
    std::shared_ptr<Material> material = nullptr;

    if (sceneMaterials) {
        // Retrieve from scene materials
        if (geometry["material"].IsString()) {
            material = sceneMaterials->at(readString(geometry["material"], "geometry material"));
        }
        // generate a new material
        else {
            material = readMaterial(geometry["material"]);
        }
    }

    // Sphere
    if (readString(geometry["type"], "Geometry type") == "sphere") {
        glm::vec3 center = readVector(geometry["center"], "Sphere Center");
        float radius = readFloat(geometry["radius"], "Sphere Radius");

        return std::make_shared<Sphere>(center, radius, material);
    }

    // Triangle
    else if (readString(geometry["type"], "Geometry type") == "triangle") {
        glm::vec3 v0 = readVector(geometry["v0"], "Triangle v0");
        glm::vec3 v1 = readVector(geometry["v1"], "Triangle v1");
        glm::vec3 v2 = readVector(geometry["v2"], "Triangle v2");

        return std::make_shared<Triangle>(v0, v1, v2, material);
    }
    // Planar Quad
    else if (readString(geometry["type"], "Geometry type") == "plane") {
        glm::vec3 center = readVector(geometry["center"], "Plane center");
        glm::vec3 rotation = readVector(geometry["rot"], "Plane rotation");
        float width = readFloat(geometry["width"], "Plane width");
        float height = readFloat(geometry["height"], "Plane height");

        return std::make_shared<Plane>(center, width, height, rotation, material);
    }
    // Box
    else if (readString(geometry["type"], "Geometry type") == "box") {
        glm::vec3 center   = readVector(geometry["center"], "Box center");
        glm::vec3 rotation = readVector(geometry["rot"], "Box rotation");
        float width  = readFloat(geometry["width"], "Box width");
        float height = readFloat(geometry["height"], "Box height");
        float depth  = readFloat(geometry["depth"], "Box depth");

        return std::make_shared<Box>(center, width, height, depth, rotation, material);
    }
    // Cone 
    else if (readString(geometry["type"], "Geometry type") == "cone") {

    }
    // Mesh
    else if (readString(geometry["type"], "Geometry type") == "mesh") {

    }
    else {
        std::cerr << "error Geometry type [ " << geometry["type"].GetString() << " ] doesn't exist" << std::endl;
        exit(-1);
    }
}

//-------------------------------------------------------------------------
// Read and generate a material
//
std::shared_ptr<Material> Parser::readMaterial(Value& material)
{
    assert(material.HasMember("type") && "materials must have member: [type]");
    std::string type = readString(material["type"], "material type");

    // Material == Normal
    if (type == "normal") {
        //return std::make_shared<Normal>();
    }
    // Material == Lambertian
    else if (type == "lambertian") {
        glm::vec3 color = readVector(material["color"], "lambertian color");
        //return std::make_shared<Lambertian>(color);
    }
    // Material == Dielectric
    else if (type == "dielectric") {
        float ri = readFloat(material["ri"], "dielectric ri");
        //return std::make_shared<Dielectric>(ri);
    }
    // Material == Blinn Phong
    else if (type == "blinnphong") {
        glm::vec3 color = readVector(material["color"], "blinnphong color");
        float ks = readFloat(material["ks"], "blinnphong ks");
        float kd = readFloat(material["kd"], "blinnphong kd");
        float kr = readFloat(material["kr"], "blinnphong kr");
        float specExp = readFloat(material["specularexp"], "blinnphong specular exp");

        //return std::make_shared<BlinnPhong>(ks, kd, kr, specExp, color);
    }
    // Material == Gooch
    else if (type == "gooch") {
        glm::vec3 color = readVector(material["color"], "Gooch color");

        return std::make_shared<Gooch>(color);
    }
    // Material == Oren Nayer
    else if (type == "orennayer") {
        glm::vec3 color = readVector(material["color"], "orennayer color");
        float sigma = readFloat(material["sigma"], "orennayer Sigma");

        return std::make_shared<OrenNayer>(color, sigma);
    }
    // Material == Emissive
    else if (type == "emissive") {
        glm::vec3 color = readVector(material["color"], "emissive color");
        float intensity = readFloat(material["intensity"], "emissive intensity");

        return std::make_shared<Emissive>(color, intensity);
    }
    else {
        std::cerr << "error material type [ " << type << " ] doesn't exist" << std::endl;
        exit(-1);
    }
}

//-------------------------------------------------------------------------
// Read and generate a light
//
std::shared_ptr<Light> Parser::readLight(Value& light)
{
    assert(light.HasMember("type") && "lights must have member: [type]");
    std::string type = readString(light["type"], "light type");

    // Light == area 
    if (type == "area") {
        assert(light.HasMember("geometry") && "area lights must have member: [geometry]");
        glm::vec3 color = readVector(light["color"], "area light color");
        float intensity = readFloat(light["intensity"], "area light intensity");
        std::shared_ptr<Geometry> shape = readGeometry(light["geometry"]);

        return std::make_shared<AreaLight>(shape, color, intensity);
    }
    // Light == distant
    else if (type == "distant") {
        glm::vec3 direction = readVector(light["direction"], "distant light direction");
        glm::vec3 color = readVector(light["color"], "distant light color");
        float intensity = readFloat(light["intensity"], "distant light intensity");

        return std::make_shared<DistantLight>(direction, color, intensity);
    }
    // Light == infinite TODO
    else if (type == "infinite") {
        return std::make_shared<InfiniteAreaLight>();
    }
    // Light == point
    else if (type == "point") {
        glm::vec3 position = readVector(light["pos"], "point light pos");
        glm::vec3 color = readVector(light["color"], "point light color");
        float intensity = readFloat(light["intensity"], "point light intensity");

        return std::make_shared<PointLight>(position, color, intensity);
    }
    // Light == spotlight
    else if (type == "spotlight") {
        glm::vec3 position = readVector(light["pos"], "spotlight pos");
        glm::vec3 direction = readVector(light["direction"], "spotlight direction");
        glm::vec3 color = readVector(light["color"], "spotlight color");
        float radius = readFloat(light["radius"], "spotlight radius");
        float intensity = readFloat(light["intensity"], "spotlight intensity");

        return std::make_shared<SpotLight>(position, direction, color, intensity, radius);
    }
    // Error
    else {
        std::cerr << "error light type [ " << type << " ] doesn't exist" << std::endl;
        exit(-1);
    }
}

//-------------------------------------------------------------------------
// Generate a vec3 else generate warning for invalid input
//
glm::vec3 Parser::readVector(Value& value, std::string jsonLoc)
{
    std::vector<float> values;
    for (auto& v : value.GetArray()) {
        assert(v.IsFloat() && (jsonLoc + ": vector values must all be floats"));
        values.push_back(v.GetFloat());
    }

    if (values.size() != 3)
        std::cerr << jsonLoc << ": vector size must be 3" << std::endl;

    return glm::vec3(values[0], values[1], values[2]);
}

//-------------------------------------------------------------------------
// Generate a float else generate warning for invalid input
//
float Parser::readFloat(Value& value, std::string jsonLoc)
{
    assert(value.IsFloat() && (jsonLoc + ": value must be a float"));
    return value.GetFloat();
}

//-------------------------------------------------------------------------
// Generate a string else generate warning for invalid input
//
std::string Parser::readString(Value& value, std::string jsonLoc)
{
    assert(value.IsString() && (jsonLoc + ": must be a string"));
    return value.GetString();
}