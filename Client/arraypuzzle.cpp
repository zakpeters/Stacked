#include "arraypuzzle.h"
ArrayPuzzle::ArrayPuzzle() : Puzzle() {

    b2Vec2 grav(0, 0.1);
    thisWorld->SetGravity(grav);

    SpriteDefinition floordef(100, 200, b2_staticBody, "testbox");
    floordef.setShape(4, 1500, 0);
    sprite2dObject *floor = new sprite2dObject(thisWorld, floordef);
    inactive_components.push_back(floor);

    for(int i = 0; i < 5; i++){
        this->addComponent("array_"+i, 4, 100, 25, 100+(i*75), -200, b2_dynamicBody);
    }
    activeIndex = 0;
}


ArrayPuzzle::~ArrayPuzzle() {}

void ArrayPuzzle::runAction(Qt::Key key){
    if(key == Qt::Key_Left){
        if(activeIndex != 0){
            activeIndex--;
        }
    }
    if(key == Qt::Key_Right){
        if(activeIndex < components.size()-1){
            activeIndex++;
        }
    }
    if(key == Qt::Key_E){
        deleteAtIndexAction();
    }
    if(key == Qt::Key_R){
        addAtIndexAction();
    }
    if(key == Qt::Key_S){
        sortArrayAction();
    }
}

void ArrayPuzzle::deleteAtIndexAction(){
    b2Body *bod;
    bod = components[activeIndex]->getBody();
    this->thisWorld->DestroyBody(bod);
    //might want to restrict the deletion if size = 1
    components.erase(components.begin() + activeIndex);

    if(components.size() > 1){
        for(int i = activeIndex; i < components.size(); i++){
            sprite2dObject * obj = (components[i]);
            obj->moveBody(sprite2dObject::left, 15);
        }
    }
}

void ArrayPuzzle::addAtIndexAction(){
    b2Body *bod;
    int x;
    bod = components[activeIndex]->getBody();
    x = bod->GetPosition().x;
    this->thisWorld->DestroyBody(bod);
    //might want to restrict the deletion if size = 1
    components.erase(components.begin() + activeIndex);
    addComponent("array_"+activeIndex, 4, 100, 25, x, -200, b2_dynamicBody);
}

void ArrayPuzzle::sortArrayAction(){
}
