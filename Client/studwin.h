#ifndef STUDWIN_H
#define STUDWIN_H
#include <QObject>
#include <QPoint>
#include <QWidget>
#include <client.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>
#include <stackpuzzle.h>
#include <treepuzzle.h>
#include <arraypuzzle.h>
#include <listpuzzle.h>
#include <sstream>

namespace Ui {
class StudWin;
}

class StudWin : public QWidget, sf::RenderWindow
{
    Q_OBJECT

public:
    explicit StudWin(QWidget *parent = 0);
    ~StudWin();
    std::vector<bool> getSolvedList();
    std::vector<bool> getUpdatedPuzzles();

//    void setMainGameWidget(QWidget *widget);

private slots:
    void on_hideButton_clicked();
    void on_logoutButton_clicked();
    void on_listWidget_currentRowChanged(int currentRow);

    void on_checkBox_stateChanged(int arg1);


private:
    Ui::StudWin *ui;
    sf::Music music;
    bool levelshow;
    PuzzleWindow* pw;
    void setupLevels();
    std::vector<Puzzle*> puzzles;
    std::vector<bool> convertStringsToBools(QVector<QString>);

};

#endif // STUDWIN_H
