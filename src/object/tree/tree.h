#ifndef PPGSO_TREE_H
#define PPGSO_TREE_H

#include <ppgso/ppgso.h>

#include "src/scene/Scene.h"
#include "src/object/object.h"

class Tree final : public Object {
public:
    std::vector<std::unique_ptr<ppgso::Texture>> textures;
    Tree(const std::string model, const std::string texture);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;

    void addTexture(const std::string texture) {
        textures.push_back(std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(texture)));
    }
};
#endif
