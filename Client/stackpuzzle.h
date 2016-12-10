#ifndef STACKPUZZLE_H
#define STACKPUZZLE_H
#include <QGraphicsScene>
#include <QWidget>
#include <stack>
#include <QObject>
#include <puzzle.h>
#include <QSize>
#include <sprite2dobject.h>
#include <Box2D/Box2D.h>
class StackPuzzle : public Puzzle
{
public:
    StackPuzzle();
    StackPuzzle(QSize size);
    ~StackPuzzle();
    void virtual runAction(Qt::Key action) override;
    void virtual step(float time) override;
private:

    //part of orig API
    std::string peekAction();
    bool waiting = false;

    std::vector<sprite2dObject*> inpit;
    void popAndSend(sprite2dObject *);
    void dropOperator();
    bool pitFull();
    void emptyPit();
    bool addToPit(sprite2dObject*);
    void updatePit(); //update logic
    void popAction();
    void pushAction();
    //world generation
    void generateStackPiece(int,int);
    void createStackContainer(int);
    void createBoundary(int,bool);
    void setActiveOperator(unsigned int);
    void startGame();
    void buildPuzzle();
    sprite2dObject * createNode(int,int, b2BodyType);
    sprite2dObject * left;
    sprite2dObject * right;
    sprite2dObject * middle;
    int itemlimit = 7;
    int operatorindex=0;
    std::vector<sprite2dObject*> operators;
    b2Vec2 ssize;
    std::stack <sprite2dObject> s;
};

#endif // STACKPUZZLE_H
