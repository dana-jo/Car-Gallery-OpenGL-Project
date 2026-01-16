#pragma once
#include "../core/SceneNode.h"

class Box;
class Cylinder;
class Material;

class Street : public SceneNode {
public:
    Street(float w, float d);
    ~Street() override;
private:
    Box* ground = nullptr;
};

class Building : public SceneNode {
public:
    Building(float w, float h, float d);
    ~Building() override;
private:
    Box* body = nullptr;
};

class Tree : public SceneNode {
public:
    Tree(float trunkH, float trunkR, float foliageSize);
    ~Tree() override;
private:
    Cylinder* trunk = nullptr;
    Box* foliage = nullptr;
};

class Surroundings : public SceneNode {
public:
    Surroundings();
    ~Surroundings() override;
};
