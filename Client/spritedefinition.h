#ifndef SPRITEDEFINITION_H
#define SPRITEDEFINITION_H
#include <Box2D.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2Body.h>

class SpriteDefinition
{
public:
    b2BodyDef * body;
    std::vector<b2FixtureDef *> fixtures;
    SpriteDefinition(int, int, b2BodyType, std::string);
    SpriteDefinition();
    ~SpriteDefinition();
    std::string name;
    void setShape(int,int,int);

};

#endif // SPRITEDEFINITION_H
