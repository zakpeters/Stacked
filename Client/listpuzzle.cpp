#include "listpuzzle.h"

ListPuzzle::ListPuzzle(QSize size) : Puzzle(size) {
    establishGravity();
    establishFloor();

    this->addComponent("list body", 4, CubeSideLength, CubeSideLength, InitialXSpawn, YSpawn, b2_dynamicBody);

    activeIndex = 0;
    colorActiveBody();
}

ListPuzzle::~ListPuzzle(){
}

void ListPuzzle::runAction(Qt::Key key) {
    if (key == Qt::Key_W) {
        pushFront();
    } else if (key == Qt::Key_E) {
        pushBack();
    } else if (key == Qt::Key_S) {
        popFront();
    } else if (key == Qt::Key_D) {
        popBack();
    } else if (key == Qt::Key_X) {
        retreatActiveIndex();
    } else if (key == Qt::Key_C) {
        advanceActiveIndex();
    }
}

void ListPuzzle::pushFront(){
    if (components.size() == 0) {
        this->addComponent("list body", 4, CubeSideLength, CubeSideLength, InitialXSpawn, YSpawn, b2_dynamicBody);
        activeIndex = 0;
        colorActiveBody();
    } else {
        b2Body *bod;
        bod = components.front()->getBody();
        this->addComponent("list body", 4, 10, 10, bod->GetPosition().x - 10, bod->GetPosition().y, b2_dynamicBody, false, true);
        activeIndex++;
    }
}

void ListPuzzle::pushBack(){
    if (components.size() == 0) {
        this->addComponent("list body", 4, CubeSideLength, CubeSideLength, InitialXSpawn, YSpawn, b2_dynamicBody);
        activeIndex = 0;
        colorActiveBody();
    } else {
        b2Body *bod;
        bod = components.back()->getBody();
        this->addComponent("list body", 4, 10, 10, bod->GetPosition().x + 10, bod->GetPosition().y, b2_dynamicBody);
    }
}

void ListPuzzle::popFront(){
    uncolorActiveBody();
    if (components.size() > 0) {
        b2Body *bod;
        bod = components.front()->getBody();
        thisWorld->DestroyBody(bod);
        components.erase(components.begin());
    }
    if (activeIndex > 0) {
        activeIndex--;
    }
    colorActiveBody();
}

void ListPuzzle::popBack(){
    if (components.size() > 0) {
        if (activeIndex == components.size() - 1) {
            retreatActiveIndex();
        }

        b2Body *bod;
        bod = components.back()->getBody();
        thisWorld->DestroyBody(bod);
        components.pop_back();
    }
}

void ListPuzzle::sortList(){
}

void ListPuzzle::colorActiveBody() {
    if (components.size() > 0) {
        components[activeIndex]->changeColor(ActiveColor);
    }
}

void ListPuzzle::uncolorActiveBody() {
    if (components.size() > 0) {
        components[activeIndex]->changeColor(DefaultColor);
    }
}

void ListPuzzle::advanceActiveIndex() {
    if (components.size() - 1 > activeIndex) {
        uncolorActiveBody();
        activeIndex++;
        colorActiveBody();
    }
}

void ListPuzzle::retreatActiveIndex() {
    if (0 < activeIndex) {
        uncolorActiveBody();
        activeIndex--;
        colorActiveBody();
    }
}
