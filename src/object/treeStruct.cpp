
#include "treeStruct.h"

#include <utility>

treeStruct::treeStruct(std::string id, std::unique_ptr<Object> obj, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : treeStruct(id, std::move(obj),pos, scale) {
    this->obj->rotation = rot;
}

treeStruct::treeStruct(std::string id, std::unique_ptr<Object> obj, glm::vec3 pos, glm::vec3 scale) : treeStruct(id, std::move(obj)) {
    this->obj->position = pos;
    this->obj->scale = scale;
    this->obj->rotation = {0,0,0};
}

treeStruct::treeStruct(std::string id, std::unique_ptr<Object> obj, glm::vec3 pos): treeStruct(id) {
    this->obj = std::move(obj);
    this->obj->position = pos;
}

treeStruct::treeStruct(std::string id, std::unique_ptr<Object> obj): treeStruct(id) {
    this->obj = std::move(obj);
    this->positionSet = false;
}

treeStruct::treeStruct(std::string id, glm::vec3 pos): treeStruct(id) {
    this->position = pos;
    this->positionSet = true;
}

treeStruct::treeStruct(std::string id) {
    this->id = id;
}

void treeStruct::addObject(std::string parent_id, std::shared_ptr<treeStruct> newStruct) {
    std::shared_ptr<treeStruct> parentStruct = this->getStructById(parent_id);

    if(parentStruct) {
        parentStruct->addChild(std::move(newStruct));
    }

}

void treeStruct::update(Scene &scene, float dt) {
    if(obj) {
        if (parent && parent->obj) {
            this->obj->parentModelMatrix = this->parent->obj->modelMatrix;
        }
        else if (parent && parent->positionSet) {
            this->obj->parentModelMatrix = glm::translate(glm::mat4(1), this->parent->position);
        }
        else {
            this->obj->parentModelMatrix = glm::mat4{1};
        }
    }

    if(obj && !(obj->update(scene, dt))) {
        if(child) {
            child->parent = NULL;

        }

        if(left) {
            if (right) {
                left->right = right;
                right->left = left;
            } else {
                left->right = NULL;
            }
        }

        if(!left && parent) {
            if(right) {
                right->left = NULL;
                parent->child = right;
            }
            else {
                parent->child = NULL;
            }
        }
    }

    if(child) {
        child->update(scene, dt);
    }
    if(right) {
        right->update(scene,dt);
    }
}

void treeStruct::render(Scene &scene) {
    if(obj) {
        obj->render(scene);
    }

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
