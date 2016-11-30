#include "puzzle.h"

Puzzle::Puzzle(QSize size) {
    b2Vec2 gravity(0.0f, -10.0f);

    this->size=size;
    this->thisWorld = new b2World(gravity);
    this->numComponents = 0;
}

void Puzzle::addComponent(sprite2dObject obj){
    components.push_back(obj);
    numComponents++;
}

void Puzzle::changeComponentImage(unsigned int, const QImage){}
sprite2dObject Puzzle::getComponent(unsigned int){sprite2dObject ob; return ob;}
void Puzzle::runAction(Action){}
