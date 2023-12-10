
#ifndef PPGSO_TREESTRUCT_H
#define PPGSO_TREESTRUCT_H

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>
#include"src/object/object.h"

class Scene;
//class Object;

class treeStruct: public std::enable_shared_from_this<treeStruct> {
public:
    treeStruct(std::string id, std::unique_ptr<Object> obj, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
    treeStruct(std::string id, std::unique_ptr<Object> obj, glm::vec3 pos, glm::vec3 scale);
    treeStruct(std::string id, std::unique_ptr<Object> obj);
    treeStruct(std::string id, std::unique_ptr<Object> obj, glm::vec3 pos);
    treeStruct(std::string id);
    treeStruct(std::string id, glm::vec3 pos);

    std::string id;
    glm::vec3 position;
    bool positionSet;
    std::unique_ptr<Object> obj;
    std::shared_ptr<treeStruct> parent;
    std::shared_ptr<treeStruct> child;
    std::shared_ptr<treeStruct> left;           //??
    std::shared_ptr<treeStruct> right;

public:
    void addObject(std::string parent_id, std::shared_ptr<treeStruct> newStruct);
    void addRight(std::shared_ptr<treeStruct> newStruct);
    void addChild(std::shared_ptr<treeStruct> newStruct);
    void update(Scene &scene, float dt);
    void render(Scene &scene);
    std::shared_ptr<treeStruct> getStructById(std::string parent_id);

};


#endif //PPGSO_TREESTRUCT_H
