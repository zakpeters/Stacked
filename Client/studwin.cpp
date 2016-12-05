#include "studwin.h"
#include "ui_studwin.h"
#include "client.h"
#include <vector>
#include "qstandarditemmodel.h"

StudWin::StudWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudWin) {
    ui->setupUi(this);
    levelshow = true;

    ui->userLabel->setText("Welcome: TestUser");
    setupLevels();
    pw = new PuzzleWindow();
    pw->setPuzzle(puzzles.front());
    pw->setFocus();


    QGridLayout *lay = new QGridLayout(this);
    lay->addWidget(pw);
    ui->mainGameWidget->setLayout(lay);
}

StudWin::~StudWin() {
    delete ui;
    for(auto it = puzzles.begin(); it < puzzles.end(); it++){
        delete *it;
    }
}

void StudWin::setupLevels() {
//    std::vector<QString> dataList;
//    std::vector<QString> levelList;
//    QStandardItemModel model;

//    for (int i = 0; i < 5; i++) {
//        dataList.push_back("DataStructure " + i);
//        levelList.push_back("Level " + i);
//    }

//    Puzzle *treepuzzle = new TreePuzzle(size()); //trying this for debugging?


    puzzles.push_back(new StackPuzzle(size()));
    puzzles.push_back(new ArrayPuzzle(size()));
    puzzles.push_back(new TreePuzzle(size()));
    puzzles.push_back(new ListPuzzle(size()));

//    Connect TreePuzzle slots to PuzzleWindow singals
     Puzzle *treepuzzle = puzzles[2]; //trying this for debugging?

   //"Failed to load font "font.ttf" (failed to create the font face)" (unrelated ?)
    //The program has unexpectedly finished. (after Torie commented out)

    connect(pw, SIGNAL(mousePressedSignal(QPoint)), treepuzzle, SLOT(mousePressedSlot(QPoint)));
    connect(pw, SIGNAL(mouseMovedSignal(QPoint)), treepuzzle, SLOT(mouseMovedSlot(QPoint)));
    connect(pw, SIGNAL(mouseReleasedSignal(QPoint)), treepuzzle, SLOT(mouseReleasedSlot(QPoint)));

    ui->listWidget->addItem("stack");
    ui->listWidget->addItem("array");
    ui->listWidget->addItem("tree");
    ui->listWidget->addItem("list");
}

void StudWin::on_hideButton_clicked() {
    if (levelshow) {
        ui->levelFrame->hide();
        levelshow = false;
        ui->hideButton->setText(QString("Show Levels"));
    } else {
        ui->levelFrame->showNormal();
        ui->hideButton->setText(QString("Hide Levels"));
        levelshow = true;
    }
}

//Move to controller?
void StudWin::on_logoutButton_clicked() {
    Client *par = (Client *)this->parentWidget();   
    par->setCurrentPage("login");

    //emit signal to release sources?
}

void StudWin::on_listWidget_currentRowChanged(int currentRow)
{
    if(currentRow>-1&&currentRow<4){
        pw->setPuzzle(puzzles[currentRow]);
        pw->setFocus();
    }
    // memory leak here.
//    switch(currentRow){
//        case 0:
//            pw->setPuzzle(new StackPuzzle);
//            break;
//        case 1:
//            pw->setPuzzle(new ArrayPuzzle);
//            break;
//        case 2:
//            pw->setPuzzle(new TreePuzzle);
//            break;
//        case 3:
//            pw->setPuzzle(new ListPuzzle);
//            break;
//    }
}
