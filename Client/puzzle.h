#ifndef PUZZLE_H
#define PUZZLE_H
#include <vector>
#include <QSize>
#include <QPoint>
#include <QImage>
#include <action.h>
#include <Box2D.h>
#include <sprite2dobject.h>
#include <iterator>


class Puzzle
{
public:

    Puzzle(QSize);
    Puzzle();
    ~Puzzle();
    //managing components
    void addComponent(sprite2dObject*);
    void addComponent(std::string name, int points, int width, int height, int x, int y, b2BodyType type);
    virtual sprite2dObject getComponent(unsigned int);
    std::vector<sprite2dObject*> getAllComponents();
    std::vector<sprite2dObject*> getComponents();
    void changeComponentImage(unsigned int, sf::Image);
    int getnumComponents();
    void step(float time);
    //polymorphic stuff
    virtual void runAction(Action action);

protected:
    std::vector<sprite2dObject*> components;
    b2World *thisWorld;

private:

    QSize size;
    int numComponents;

};

#endif // PUZZLE_H
