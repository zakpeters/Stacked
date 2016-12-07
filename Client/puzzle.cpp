#include "puzzle.h"
#include <iostream>

Puzzle::Puzzle(QObject *parent) :  QObject(parent) {
    b2Vec2 g(0,9.8);
    thisWorld = new b2World(g);
}

Puzzle::Puzzle(QSize size, QObject*) : Puzzle(){
    this->size=size;
}

Puzzle::~Puzzle(){
    delete thisWorld;
    for(auto it = inactive_components.begin(); it < inactive_components.end(); it++){
        sprite2dObject * obj = *it;
        delete obj;
    }
    for(auto it = components.begin(); it < components.end(); it++){
        sprite2dObject * obj = *it;
        delete obj;
    }
}

void Puzzle::step(float time){
   thisWorld->Step(time,10,10);
   //apparently there are performance issues when the last two numbers are < 10
}




sprite2dObject * Puzzle::getComponentAt(int x, int y){

    //x and y need to be adjusted. Switch x and y, add 90 to x on Tyler's machine
    foreach(sprite2dObject *sp, components)
    {
        int spx = sp->getBody()->GetPosition().x;
        std::cout << "spx "<<spx<<std::endl;
        std::cout << "x "<<x<<std::endl;
        int spy = sp->getBody()->GetPosition().y;
        std::cout << "spy "<<spy<<std::endl;
        std::cout << "y "<<y<<std::endl;

        int diffx = abs(spx-x);
        int diffy = abs(spy-y);

        std::cout << "diffx " << diffx << std::endl;
        std::cout << "diffy " << diffy << std::endl;
        if (diffx<10 && diffy<10)
        {
            std::cout << "object found " << std::endl;
            return sp;
        }

    }

//   b2Body * results = nullptr;
//   for(b2Body* bodyIterator = thisWorld->GetBodyList(); bodyIterator; bodyIterator->GetNext()){

//      b2Vec2 bodyPosition(bodyIterator->GetPosition());
////      std::cout << " b2dx " << bodyIterator->GetPosition().x << " b2dy " << bodyIterator->GetPosition().y << std::endl;
//      b2Vec2 mousePosition(x,y);
////      std::cout << " qtx " << x << " qtx " << y << std::endl;
//      b2Vec2 difference;

//      difference+=bodyPosition; // load first point set
//      difference-=mousePosition; // take difference

//      if(difference.Normalize()<10){

//         results = bodyIterator;
//      }

//   }

//   if(results!=nullptr){
//      for(auto it = components.begin(); it < components.end(); it++){
//         b2Body * compare = (*it)->getBody();
//         if(results==compare){
//            return *it; // return the pointer to the correct sprite2dObject
//         }
//      }
//      for(auto it = inactive_components.begin(); it < inactive_components.end(); it++){
//         b2Body * compare = (*it)->getBody();
//         if(results==compare){
//            return *it; // return the pointer to the correct sprite2dObject
//         }
//      }
//    } return nullptr;
}

void Puzzle::addComponent(std::string name, int points, int width, int height, int x, int y, b2BodyType type, bool ignored, bool pushFront){
    SpriteDefinition tempdef(x,y, type,name);
    tempdef.setShape(points,width,height); // set shape is (verticeCount, width, height ) -- if 0 the height/width will be 1.
    if(!ignored){
        if (pushFront) {
            components.insert(components.begin(), new sprite2dObject(thisWorld,tempdef));
        } else {
            components.push_back(new sprite2dObject(thisWorld,tempdef));
        }
    }else{
        inactive_components.push_back(new sprite2dObject(thisWorld,tempdef));
    }
}

//if you want to change by index
void Puzzle::replaceComponent(std::string name, int points, int width, int height, int x, int y, b2BodyType type, int ind, bool ignored){
    SpriteDefinition tempdef(x,y, type,name);
    tempdef.setShape(points,width,height); // set shape is (verticeCount, width, height ) -- if 0 the height/width will be 1.
    if(!ignored){
        components[ind] = new sprite2dObject(thisWorld, tempdef);
    }else{
        inactive_components.push_back(new sprite2dObject(thisWorld,tempdef));
    }
}

void Puzzle::addComponent(SpriteDefinition def, bool ignored, bool pushFront){
    if(!ignored){
        if (pushFront) {
            components.insert(components.begin(), new sprite2dObject(thisWorld,def));
        } else {
            components.push_back(new sprite2dObject(thisWorld,def));
        }
    }else{
        inactive_components.push_back(new sprite2dObject(thisWorld,def));
    }
}

void Puzzle::addComponent(sprite2dObject* obj, bool ignored, bool pushFront){
    if(!ignored){
        if (pushFront) {
            components.insert(components.begin(), obj);
        } else {
            components.push_back(obj);
        }
    }else{
        inactive_components.push_back(obj);
    }

}

sprite2dObject* Puzzle::getComponent(std::string name)
{
    for(auto it = components.begin(); it < components.end(); it++)
    {
        sprite2dObject * obj = *it;
        if(obj->getName()==name)
        {
            return obj;
        }
   }
   return nullptr;
}

//polymorphic stuff
void Puzzle::runAction(Qt::Key){}

//returns vector of all of the sprites2dobjects/sprites
//(i.e. so they can be pulled and drawn by PuzzleWindow)
std::vector<sprite2dObject*> Puzzle::getAllComponents()
{
    std::vector<sprite2dObject*> vec;
    vec.insert(vec.end(), components.begin(), components.end());
    vec.insert(vec.end(), inactive_components.begin(), inactive_components.end());
    return vec;
}

void Puzzle::establishGravity() {
    b2Vec2 graf(0,0.1); // gravity is set low here
    thisWorld->SetGravity(graf);
}

void Puzzle::establishGravity(int gravityfactor) {
    b2Vec2 graf(0,0.1*gravityfactor); // gravity is set low here
    thisWorld->SetGravity(graf);
}

void Puzzle::establishFloor() {
    SpriteDefinition floordef(100,200, b2_staticBody,"floor");
    floordef.setShape(4,1000,0); // set shape is (verticeCount, width, height ) -- if 0 the height/width will be 1.
    sprite2dObject *floor = new sprite2dObject(thisWorld,floordef);
    inactive_components.push_back(floor);
}


void Puzzle::establishSides() {
    SpriteDefinition lsidedef(0,0, b2_staticBody,"lside");
    SpriteDefinition rsidedef(390,0, b2_staticBody,"rside");
    lsidedef.setShape(4,0,650); // set shape is (verticeCount, width, height ) -- if 0 the height/width will be 1.
    rsidedef.setShape(4,0,650);
    sprite2dObject *lside = new sprite2dObject(thisWorld,lsidedef);
    sprite2dObject *rside = new sprite2dObject(thisWorld,rsidedef);
    inactive_components.push_back(lside);
    inactive_components.push_back(rside);
}


void Puzzle::collectGarbage(){
    garbageCollection(components);
    garbageCollection(inactive_components);
}


void Puzzle::mousePressedSlot(QPointF)
{
    //to be implemented in child class
}

void Puzzle::mouseMovedSlot(QPointF)
{
    //to be implemented in child class
}

void Puzzle::mouseReleasedSlot(QPointF)
{
    //to be implemented in child class
}

//here be dragons.
void Puzzle::garbageCollection(std::vector<sprite2dObject*>& objs){
    int i = 0;
    for(auto it = objs.begin(); it < objs.end(); it++){
        sprite2dObject * obj = *it;
        if(obj==nullptr||obj->getBody()==nullptr){
            delete obj;
            objs.erase(objs.begin()+i); // erase if we need to
            break;
        }
        else if(obj->isIgnored()){
            b2Vec2 vec(obj->getBody()->GetPosition());
            if(vec.x<-10000||vec.x>10000||vec.y>10000){ // magic numbers here << we should probably tie in some sort of size
                delete obj;
                objs.erase(objs.begin()+i); // erase if we need to
                break;
            }
        }
        if(obj->marked()){
            delete obj;
            objs.erase(objs.begin()+i); // erase if we need to
            break;
        }
        i++;
    }
}










