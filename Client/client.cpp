#include "client.h"
#include "loginwin.h"
#include "studwin.h"
#include "teachwin.h"
#include "studreg.h"
#include "teachreg.h"
#include "ui_client.h"
#include "QGraphicsView"
#include "QGridLayout"
#include "QPushButton"
#include <usersocket.h>
#include <iostream>
#include <SFML/Audio.hpp>
#include <QDesktopWidget>
#include <QDebug>
#include <QUrl>
#include <QDesktopServices>
#include <QTimer>

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client) {
    ui->setupUi(this);
    QObject::connect(&timer,&QTimer::timeout,this,&Client::autosave);
    //move the window to the center of the screen
    move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
    timer.start(30000); //every 30 seconds or so
    widgets.push_back(new LoginWin);
    widgets.push_back(new StudWin);
    widgets.push_back(new TeachWin);
    widgets.push_back(new StudReg);
    widgets.push_back(new TeachReg);
    this->setStyleSheet("background-color: black; color: white");
}

Client::~Client() {
    delete ui;
    try{
        UserSocket sock(sf::IpAddress::LocalHost, 11777,getSessionId());
        sock.deauthenticate();
    }catch(std::exception){

    }
}

//TODO: Move this all to controller later?
void Client::setCurrentPage(QString s) {
    if (s == "login") {
        setCentralWidget(widgets[0]);
        activeWidget = 0;
    } else if (s == "studwin") {
        setCentralWidget(widgets[1]);
        activeWidget = 1;
    } else if (s == "teachwin") {
        setCentralWidget(widgets[2]);
        static_cast<TeachWin*>(widgets[2])->updateStudents();
        activeWidget = 2;
    } else if (s == "studreg") {
        setCentralWidget(widgets[3]);
        activeWidget = 3;
    } else if (s == "teachreg") {
        setCentralWidget(widgets[4]);
        activeWidget = 4;
    }
}

void Client::autosave(){
    if(activeWidget == 1&&sessionid!=""){
        UserSocket sock(sf::IpAddress::LocalHost, 11777, sessionid);
        StudWin * win = static_cast<StudWin*>(widgets[activeWidget]);
        std::vector<bool> solvedlist = win->getSolvedList();
        int index = 0;
        for(auto it = solvedlist.begin(); it < solvedlist.end(); it++){
            bool i = *it;
             // send to the client
            if(i){
                std::stringstream ss;
                ss << username << "," << index;
                sock.sendPayload("puzzlesolved",ss.str());
            }
            index++;
        }
    }
}


bool Client::sendLogin(QString user, QString pass) {
    try {
        UserSocket sock(sf::IpAddress::LocalHost, 11777);
        sock.authenticate(user.toStdString(), pass.toStdString()); //if no exceptions thrown, then we are authenticated
        sessionid = sock.sid();
        username = user.toStdString();
        // sock.deauthenticate(); //when you are done deauthenticate, or save the sid for later
        //(note: the server will be configured to auto check for expired session ids -- probably every like 20 minutes or something )
    } catch (authenticationexception) { // if the client was not authenticated properly, or the session key was invalid
        return false;
    }
    //send payload and parse payload to determine if teach/student
    bool teach = false;
    if (teach) {
        TeachWin* teachwindow = new TeachWin();
        setCentralWidget(teachwindow);
        teachwindow->setCurrentUsername(QString::fromStdString(username));
    } else {
        StudWin* studwindow = new StudWin();
        setCentralWidget(studwindow);
        studwindow->setCurrentUsername(QString::fromStdString(username));
    }

    return true;
}

int Client::sendReg(QString data) {
    UserSocket sock(sf::IpAddress::LocalHost, 11777);

    try {
        Message msg = sock.sendPayload("register", data.toStdString());
    } catch (reguserexception) {
        return 1;
    } catch (regclassexception) {
        return 2;
    }

    setCentralWidget(new LoginWin());
    return 0;
}

//hardcoded to class "" for now
QVector<QString> Client::getStudents(QString) { // still unimplemented
    UserSocket sock(sf::IpAddress::LocalHost, 11777);

    sock.authenticate("", "");
    Message msg = sock.sendPayload("getstudents", "");//classcode.toStdString());
    QVector<QString> students = QString::fromStdString(msg.payload).split(",").toVector();
    return students;
}

//UI debug individual pages
void Client::on_pushButton_clicked() {
    setCentralWidget(new LoginWin());
}

void Client::on_pushButton_2_clicked() {
    //This logic will need to be changed later
    StudWin *studwin = new StudWin(this);

    setCentralWidget(studwin);
}

std::string Client::getSessionId(){
   return sessionid;
}

void Client::on_pushButton_3_clicked() {
    setCentralWidget(new TeachWin());
}

void Client::on_pushButton_4_clicked() {
    setCentralWidget(new StudReg());
}

void Client::on_pushButton_5_clicked() {
    setCentralWidget(new TeachReg());
}

void Client::on_pushButton_6_clicked() {
//    PuzzleWindow pw;
//    setCentralWidget(new GraphicsObjectTest);
}

void Client::on_pushButton_7_clicked()
{
    UserSocket sock(sf::IpAddress::LocalHost, 11777);
    try{
        sock.authenticate("averysecretusername", "averysecretpassword");
        qDebug() << "tried to send payload";
        Message msg = sock.sendPayload("studentlist", "");
        QDesktopServices::openUrl(QUrl(QString::fromStdString(msg.payload)));
    }catch(...){
        qDebug() << "Error 404 God not found";
    }
}
