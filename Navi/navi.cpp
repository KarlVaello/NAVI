#include "navi.h"
#include <QtWidgets>
#include <QApplication>
#include <QtSvg/QtSvg>
#include <QtSvg/QSvgRenderer>
#include <QDebug>
#include <QDateTime>
#include <QMediaPlayer>
#include <QMediaPlaylist>


Navi::Navi(QWidget *parent)
    : QWidget(parent)
{

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1);

    setWindowTitle(tr("VCS"));

    resize(800, 480);

    renderer_navigationIcon = new QSvgRenderer(QString(":/Resources/location-on-map.svg"));
    renderer_phoneIcon = new QSvgRenderer(QString(":/Resources/call-answer.svg"));
    renderer_stopIcon = new QSvgRenderer(QString(":/Resources/player_STOP.svg"));
    renderer_nextIcon = new QSvgRenderer(QString(":/Resources/player_NEXT.svg"));
    renderer_previousIcon = new QSvgRenderer(QString(":/Resources/player_PREV.svg"));
    renderer_returnIcon = new QSvgRenderer(QString(":/Resources/return-button.svg"));



}

void Navi::paintEvent(QPaintEvent *)
{

    //backGroundRect->begin(this);
    //backGroundRect->fillRect(QRect(0,0,800,480),QColor(246,241,237,255));
    //backGroundRect->end();
    if(homeScreen){
        QPainter painter(this);
        painter.drawImage(QRect(0,0,800,480), QImage(QString(":/Resources/backg.jpg")));
        painter.end();

        navigationCard->begin(this);
        navigationCard->fillRect(QRect(30,90,225,360),QColor(255,255,255,100));
        navigationCard->end();

        painter_navigationIcon->begin(this);
        painter_navigationIcon->translate(60, 180);
        painter_navigationIcon->scale(0.2,0.32);
        renderer_navigationIcon->render(painter_navigationIcon);
        painter_navigationIcon->end();


        //######### MUSIC PLAYER #########
        musicPlayer_CardBack->begin(this);
        musicPlayer_CardBack->fillRect(QRect(289,90,225,360),QColor(255,255,255,100));
        musicPlayer_CardBack->end();

        musicPlayer_CardUpBar->begin(this);
        musicPlayer_CardUpBar->fillRect(QRect(289,90,225,40),QColor(100,100,100,100));
        musicPlayer_CardUpBar->end();

        musicPlayer_CardDownBar->begin(this);
        musicPlayer_CardDownBar->fillRect(QRect(289,310,225,140),QColor(234,234,234,255));
        musicPlayer_CardDownBar->end();




        //######### PHONE #########

        phonePlayerCard->begin(this);
        phonePlayerCard->fillRect(QRect(545,90,225,360),QColor(255,255,255,100));
        phonePlayerCard->end();

        painter_phoneIcon->begin(this);
        painter_phoneIcon->translate(600, 180);
        painter_phoneIcon->scale(0.15,0.28);
        renderer_phoneIcon->render(painter_phoneIcon);
        painter_phoneIcon->end();

    }

    if(playerScreen){

        QPainter painter(this);
        painter.drawImage(QRect(0,-200,800,800), QImage("C:/Users/Karl/Desktop/NAVI/Resources/epBack2.jpg"));
        painter.end();

        musicPlayer_CardBack->begin(this);
        musicPlayer_CardBack->fillRect(QRect(0,0,800,480),QColor(255,255,255,110));
        musicPlayer_CardBack->end();

        QPainter painter3(this);
        painter3.drawImage(QRect(30,30,200,200), QImage("C:/Users/Karl/Desktop/NAVI/Resources/epBack2.jpg"));
        painter3.end();

        musicPlayer_CardUpBar->begin(this);
        musicPlayer_CardUpBar->fillRect(QRect(0,320,800,50),QColor(235,235,235,110));
        musicPlayer_CardUpBar->end();

        musicPlayer_CardDownBar->begin(this);
        musicPlayer_CardDownBar->fillRect(QRect(0,370,800,110),QColor(234,234,234,255));
        musicPlayer_CardDownBar->end();

        paniter_musicPlayer_Stop->begin(this);
        paniter_musicPlayer_Stop->translate(25, 395);
        paniter_musicPlayer_Stop->scale(0.08,0.13);
        renderer_stopIcon->render(paniter_musicPlayer_Stop);
        paniter_musicPlayer_Stop->end();

        paniter_musicPlayer_Previous->begin(this);
        paniter_musicPlayer_Previous->translate(110, 405);
        paniter_musicPlayer_Previous->scale(0.048,0.08);
        renderer_previousIcon->render(paniter_musicPlayer_Previous);
        paniter_musicPlayer_Previous->end();

        paniter_musicPlayer_Next->begin(this);
        paniter_musicPlayer_Next->translate(160, 405);
        paniter_musicPlayer_Next->scale(0.048,0.08);
        renderer_nextIcon->render(paniter_musicPlayer_Next);
        paniter_musicPlayer_Next->end();

        paninter_return->begin(this);
        paninter_return->translate(720, 405);
        paninter_return->scale(0.048,0.08);
        renderer_returnIcon->render(paninter_return);
        paninter_return->end();


        currentMadiaTime->begin(this);
        currentMadiaTime->setPen(QColor(160, 160, 160));
        currentMadiaTime->setFont(QFont("Arial", 14));
        int seconds2 = (player->position() / 1000) % 60 ;
        int minutes2 = ((player->position() / (1000*60)) % 60);
        currentMadiaTime->drawText(QRect(15, 335 ,40,20),
                                   QString::number(minutes2) + ":" + QString::number(seconds2),
                                   Qt::AlignRight | Qt::AlignVCenter);
        currentMadiaTime->end();

        currentMadiaTotalTime->begin(this);
        currentMadiaTotalTime->setPen(QColor(50, 50, 50));
        currentMadiaTotalTime->setFont(QFont("Arial", 14));
        int seconds = (player->duration() / 1000) % 60 ;
        int minutes = ((player->duration() / (1000*60)) % 60);

        currentMadiaTotalTime->drawText(QRect(750, 335 ,40,20),
                                        QString::number(minutes) + ":" + QString::number(seconds),
                                        Qt::AlignLeft | Qt::AlignVCenter);
        currentMadiaTotalTime->end();

        mediaTimeBar->begin(this);
        mediaTimeBar->fillRect(QRect(70,340,660,10),QColor(70,70,70,255));
        mediaTimeBar->end();

        mediaTimeBar->begin(this);
        int a = (float)(player->position()*660.0f)/ (float)player->duration();
        mediaTimeBar->fillRect(QRect(70,340,a,10),QColor(160,160,160,255));
        mediaTimeBar->end();


        if(!isPlaying){
            playlist->addMedia(QUrl::fromLocalFile("/Users/cvaello/Desktop/NAVI/Below My Feet.mp3"));
            playlist->addMedia(QUrl::fromLocalFile("/Users/cvaello/Desktop/NAVI/Babel.mp3"));

            playlist->setCurrentIndex(1);

            player->setPlaylist(playlist);
            player->setVolume(0);

            player->play();

            qDebug() << "hey" << player->duration();
            isPlaying = true;
        }
    }

    if(navScreen){
        paninter_return->begin(this);
        paninter_return->translate(720, 405);
        paninter_return->scale(0.048,0.08);
        renderer_returnIcon->render(paninter_return);
        paninter_return->end();
    }

    if(phoneScreen){
        paninter_return->begin(this);
        paninter_return->translate(720, 405);
        paninter_return->scale(0.048,0.08);
        renderer_returnIcon->render(paninter_return);
        paninter_return->end();
    }

}


void Navi::mouseMoveEvent(QMouseEvent *event){
    //qDebug() << event->pos();
}

void Navi::mousePressEvent(QMouseEvent *eventPress){
    if(homeScreen){
        qDebug() << "clickPos[homeScreen]: " << eventPress->pos();
        if (eventPress->pos().x() >= 30 && eventPress->pos().x() <=30 + 224){
            if (eventPress->pos().y() >= 60 && eventPress->pos().y() <=60 + 360){
                navScreen = true;

                homeScreen = false;
                playerScreen = false;
                phoneScreen = false;

                update();

                qDebug() << "nav";
            }
        }else if (eventPress->pos().x() >= 289 && eventPress->pos().x() <=289 + 224){
            if (eventPress->pos().y() >= 60 && eventPress->pos().y() <=60 + 360){
                playerScreen = true;

                homeScreen = false;
                navScreen = false;
                phoneScreen = false;

                update();

                qDebug() << "player";
            }
        }else if (eventPress->pos().x() >= 545 && eventPress->pos().x() <=545 + 224){
            if (eventPress->pos().y() >= 60 && eventPress->pos().y() <=60 + 360){
                phoneScreen = true;

                homeScreen = false;
                navScreen = false;
                playerScreen = false;

                update();

                qDebug() << "phone";
            }
        }
    }

    if(navScreen){
        qDebug() << "clickPos[playerScreen]: " << eventPress->pos();

        if (eventPress->pos().x() >= 720 && eventPress->pos().x() <=720 + 40){
            if (eventPress->pos().y() >= 405 && eventPress->pos().y() <=405 + 40){

                homeScreen = true;
                navScreen = false;

                update();
            }
        }
    }



    if(playerScreen){
        qDebug() << "clickPos[playerScreen]: " << eventPress->pos();
        qDebug() << "hey2" << player->duration();

        if (eventPress->pos().x() >= 720 && eventPress->pos().x() <=720 + 40){
            if (eventPress->pos().y() >= 405 && eventPress->pos().y() <=405 + 40){

                homeScreen = true;
                playerScreen = false;

                update();
            }
        }
        update();

    }

    if(phoneScreen){
        qDebug() << "clickPos[playerScreen]: " << eventPress->pos();

        if (eventPress->pos().x() >= 720 && eventPress->pos().x() <=720 + 40){
            if (eventPress->pos().y() >= 405 && eventPress->pos().y() <=405 + 40){

                homeScreen = true;
                phoneScreen = false;

                update();
            }
        }
    }

}

