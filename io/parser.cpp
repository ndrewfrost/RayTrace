#include "parser.h"

///////////////////////////////////////////////////////////////////////////
// Parser                                                                //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
// Create a camera object, either Pinhole or Thin lens
// Depending on the data from JSON in Value& CameraSpecs
//
std::unique_ptr<Camera> Parser::readCamera(Value& value, float aspectRatio)
{
    // check if defined cameratype
    assert(value.HasMember("type") && "Camera type not specified");

    const std::string cameraType = readString(value["type"], "Camera type");

    // Pinhole Camera
    if (cameraType == "pinhole") {

        glm::vec3 origin = readVector(value["origin"], "Camera origin");
        glm::vec3 lookAt = readVector(value["lookat"], "Camera lookAt");
        glm::vec3 vup = readVector(value["vup"], "Camera vup");
        float hfov = readFloat(value["hfov"], "Camera hfov");

        return std::make_unique<Pinhole>(Pinhole(origin, lookAt, vup, hfov, aspectRatio));
    }
    // Thin lens Camera
    else if (cameraType == "thinlens") {
        std::cerr << "[thinlens] is yet to be implemented" << std::endl;
        exit(-1);
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
std::unique_ptr<Scene> Parser::readScene(Value& value)
{
    std::vector<std::shared_ptr<Geometry>> sceneGeometry;
    MaterialList sceneMaterials;

    Value& materials = value["materials"];
    for (unsigned int i = 0; i < materials.Size(); i++) {
        storeMaterial(sceneMaterials, materials[i]);
    }

    Value& geometry = value["geometry"];
    for (unsigned int i = 0; i < geometry.Size(); i++) {
        sceneGeometry.push_back(readGeometry(geometry[i], sceneMaterials));
    }

    return std::make_unique<Scene>(Scene(sceneGeometry));
}

//-------------------------------------------------------------------------
// Read and store a material to be referenced by geometry
//
void Parser::storeMaterial(MaterialList& sceneMaterials, Value& material)
{
    assert(material.HasMember("name") && "defined materials must have members : [name]");
    assert(material.HasMember("type") && "defined materials must have members : [type]");

    std::string name = readString(material["name"], "material name");
    std::string type = readString(material["type"], "material name");

    sceneMaterials.insert(std::make_pair(name, readMaterial(material)));
}

//-------------------------------------------------------------------------
// Generate a geometry primitive
//
std::shared_ptr<Geometry> Parser::readGeometry(Value& geometry, MaterialList& sceneMaterials)
{
    assert(geometry.HasMember("type") && "geometry must have type member");

    // Geometry material
    std::shared_ptr<Material> material;
    // Retrieve from scene materials
    if (geometry["material"].IsString()) {
        material = sceneMaterials.at(readString(geometry["material"], "geometry material"));
    }
    // generate a new material
    else {
        material = readMaterial(geometry["material"]);
    }

    // Sphere
    if (readString(geometry["type"], "Geometry type") == "sphere") {
        glm::vec3 center = readVector(geometry["center"], "Sphere Center");
        float radius = readFloat(geometry["radius"], "Sphere Radius");

        std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Sphere(center, radius, material));
        return sphere;
    }

    // Triangle TODO

    // Quad TODO

    //TriMesh TODO

    return std::shared_ptr<Geometry>();
}

//-------------------------------------------------------------------------
// Read and generate a material
//
std::shared_ptr<Material> Parser::readMaterial(Value& material)
{
    assert(material.HasMember("type") && "materials must have members : [type]");

    std::string type = readString(material["type"], "material type");

    // Material == Normal,  Special Case
    if (type == "normal") {
        return std::make_shared<Normal>();
    }
    // Material == Lambertian
    else if (type == "lambertian") {
        glm::vec3 color = readVector(material["color"], "material color");
        return std::make_shared<Lambertian>(color);
    }
    // Material == Dielectric
    else if (type == "dielectric") {
        float ri = readFloat(material["ri"], "dielectric ri");
        return std::make_shared<Dielectric>(ri);
    }
    else {
        std::cerr << "error existing material type is called: " << type << std::endl;
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