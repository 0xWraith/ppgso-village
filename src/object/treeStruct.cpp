
#include "treeStruct.h"

#include <utility>

treeStruct::treeStruct(std::string id, std::unique_ptr<Object> obj, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : treeStruct(id, std::move(obj),pos, scale) {
    this->obj->rotation = rot;
}

treeStruct::treeStruct(std::string id, std::unique_ptr<Object> obj, glm::vec3 pos, glm::vec3 scale) : treeStruct(id, std::move(obj)) {
    this->obj->position = pos;
    this->obj->scale = scale;
}

treeStruct::treeStruct(std::string id, std::unique_ptr<Object> obj) {
    this->obj = std::move(obj);
    this->id = id;
}

void treeStruct::addObject(std::string parent_id, std::shared_ptr<treeStruct> newStruct) {
    std::shared_ptr<treeStruct> parentStruct = this->getStructById(parent_id);

    if(parentStruct) {
        parentStruct->addChild(std::move(newStruct));
    }

}

void treeStruct::update(Scene &scene, float dt) {
    if(parent) {
        this->obj->parentModelMatrix = this->parent->obj->modelMatrix;
    }
    else {
        this->obj->parentModelMatrix = glm::mat4 {1};
    }

    if(!obj->update(scene, dt)) {
        if(right) {
            right->left = NULL;
        }
        if(left) {
            left->right = NULL;
        }
        if(parent && !right) {
            parent->child = NULL;
        }
        if(child) {
            child->parent = parent;
        }
    }

    if(child != NULL) {
        child->update(scene, dt);
    }
    if(right != NULL) {
        right->update(scene,dt);
    }
}

void treeStruct::render(Scene &scene) {
    obj->render(scene);

    if(child != NULL) {
        child->render(scene);
    }
    if(right != NULL) {
        right->render(scene);
    }

}

void treeStruct::addChild(std::shared_ptr<treeStruct> newStruct) {
    if(!child) {
        child = newStruct;
        child->parent = shared_from_this();
    }
    else {
        child->addRight(newStruct);
    }

}

void treeStruct::addRight(std::shared_ptr<treeStruct> newStruct) {
    if(!right) {
        right = newStruct;
        right->left = shared_from_this();
        right->parent = this->parent;
    }
    else {
        right->addRight(newStruct);
    }

}

std::shared_ptr<treeStruct> treeStruct::getStructById(const std::string parent_id) {
    if (this->id == parent_id) {
        return shared_from_this();
    }
    else {
        std::shared_ptr<treeStruct> node;

        if(this->child) {
            node = this->child->getStructById(parent_id);
            if (node) {
                return node;
            }
        }
        if (this->right) {
            node = this->right->getStructById(parent_id);
            if (node) {
                return node;
            }
        }
        return NULL;
    }

}
