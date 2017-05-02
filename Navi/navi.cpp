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

    resize(display_width, display_height);

    renderer_navigationIcon = new QSvgRenderer(QString(":/Resources/navigation.svg"));
    renderer_phoneIcon = new QSvgRenderer(QString(":/Resources/call-answer.svg"));
    renderer_stopIcon = new QSvgRenderer(QString(":/Resources/player_STOP.svg"));
    renderer_nextIcon = new QSvgRenderer(QString(":/Resources/player_NEXT.svg"));
    renderer_previousIcon = new QSvgRenderer(QString(":/Resources/player_PREV.svg"));
    renderer_homeIcon= new QSvgRenderer(QString(":/Resources/home.svg"));
    renderer_musicIcon= new QSvgRenderer(QString(":/Resources/music.svg"));
}

void Navi::paintEvent(QPaintEvent *)
{
    painter_backgroundColor->begin(this);
    painter_backgroundColor->fillRect(QRect(0,0,display_width,display_height),QColor(63,63,63,255));
    painter_backgroundColor->end();

    paniter_sideBarBackground->begin(this);
    paniter_sideBarBackground->fillRect(QRect(0,0,80,display_height),QColor(201,201,189,255));
    paniter_sideBarBackground->end();

    painter_selectedItemOnSideBarBackground->begin(this);
    painter_selectedItemOnSideBarBackground->fillRect(QRect(0,80 * itemSelected,80,80),QColor(182,182,171,255));
    painter_selectedItemOnSideBarBackground->end();


    painter_homeIcon->begin(this);
    painter_homeIcon->translate(7, 10);
    painter_homeIcon->scale(0.08,0.12);
    renderer_homeIcon->render(painter_homeIcon);
    painter_homeIcon->end();

    painter_musicIcon->begin(this);
    painter_musicIcon->translate(22, 100);
    painter_musicIcon->scale(0.04,0.07);
    renderer_musicIcon->render(painter_musicIcon);
    painter_musicIcon->end();

    painter_navigationIcon->begin(this);
    painter_navigationIcon->translate(23, 185);
    painter_navigationIcon->scale(0.04,0.07);
    renderer_navigationIcon->render(painter_navigationIcon);
    painter_navigationIcon->end();


    painter_phoneIcon->begin(this);
    painter_phoneIcon->translate(23, 265);
    painter_phoneIcon->scale(0.04,0.07);
    renderer_phoneIcon->render(painter_phoneIcon);
    painter_phoneIcon->end();



    if(itemSelected == 1){


        musicPlayer_CardDownBar->begin(this);
        musicPlayer_CardDownBar->fillRect(QRect(80,475,1024,130),QColor(234,234,234,255));
        musicPlayer_CardDownBar->end();

        paniter_musicPlayer_Stop->begin(this);
        paniter_musicPlayer_Stop->translate(520, 525);
        paniter_musicPlayer_Stop->scale(0.06,0.10);
        renderer_stopIcon->render(paniter_musicPlayer_Stop);
        paniter_musicPlayer_Stop->end();

        paniter_musicPlayer_Previous->begin(this);
        paniter_musicPlayer_Previous->translate(450, 536);
        paniter_musicPlayer_Previous->scale(0.038,0.065);
        renderer_previousIcon->render(paniter_musicPlayer_Previous);
        paniter_musicPlayer_Previous->end();

        paniter_musicPlayer_Next->begin(this);
        paniter_musicPlayer_Next->translate(610, 536);
        paniter_musicPlayer_Next->scale(0.038,0.065);
        renderer_nextIcon->render(paniter_musicPlayer_Next);
        paniter_musicPlayer_Next->end();

        currentMadiaTime->begin(this);
        currentMadiaTime->setPen(QColor(160, 160, 160));
        currentMadiaTime->setFont(QFont("Arial", 14));
        int seconds2 = (player->position() / 1000) % 60 ;
        int minutes2 = ((player->position() / (1000*60)) % 60);
        currentMadiaTime->drawText(QRect(95, 485 ,40,20),
                                   QString::number(minutes2) + ":" + QString::number(seconds2),
                                   Qt::AlignRight | Qt::AlignVCenter);
        currentMadiaTime->end();

        currentMadiaTotalTime->begin(this);
        currentMadiaTotalTime->setPen(QColor(50, 50, 50));
        currentMadiaTotalTime->setFont(QFont("Arial", 14));
        int seconds = (player->duration() / 1000) % 60 ;
        int minutes = ((player->duration() / (1000*60)) % 60);

        currentMadiaTotalTime->drawText(QRect(965, 485 ,40,20),
                                        QString::number(minutes) + ":" + QString::number(seconds),
                                        Qt::AlignLeft | Qt::AlignVCenter);
        currentMadiaTotalTime->end();

        mediaTimeBar->begin(this);
        mediaTimeBar->fillRect(QRect(150,490,800,10),QColor(70,70,70,255));
        mediaTimeBar->end();

        mediaTimeBar->begin(this);
        int a = (float)(player->position()*800.0f)/ (float)player->duration();
        mediaTimeBar->fillRect(QRect(150,490,a,10),QColor(160,160,160,255));
        mediaTimeBar->end();


        if(!isPlaying){
            playlist->addMedia(QUrl::fromLocalFile("C:/Users/Karl/Desktop/NAVI/Below My Feet.mp3"));
            playlist->addMedia(QUrl::fromLocalFile("C:/Users/Karl/Desktop/NAVI/Babel.mp3"));

            playlist->setCurrentIndex(1);

            player->setPlaylist(playlist);
            player->setVolume(0);

            player->play();

            qDebug() << "hey" << player->duration();
            isPlaying = true;
        }
    }


}


void Navi::mouseMoveEvent(QMouseEvent *event){
    //qDebug() << event->pos();
}

void Navi::mousePressEvent(QMouseEvent *eventPress){
    qDebug() << "clickPos[homeScreen]: " << eventPress->pos();
    if (eventPress->pos().x() >= 0 && eventPress->pos().x() <=80){
        if (eventPress->pos().y() >= 0 && eventPress->pos().y() <=80 ){
            itemSelected = 0;
            update();

            qDebug() << "hs";
        }
    }
    if (eventPress->pos().x() >= 0 && eventPress->pos().x() <=80){
        if (eventPress->pos().y() > 80 && eventPress->pos().y() <=160){
            itemSelected = 1;
            update();

            qDebug() << "mp";
        }
    }
    if (eventPress->pos().x() >= 0 && eventPress->pos().x() <=80){
        if (eventPress->pos().y() > 160 && eventPress->pos().y() <=250){
            itemSelected = 2;
            update();

            qDebug() << "nav";
        }
    }
    if (eventPress->pos().x() >= 0 && eventPress->pos().x() <=80){
        if (eventPress->pos().y() > 250 && eventPress->pos().y() <=330){
            itemSelected = 3;
            update();

            qDebug() << "phone";
        }
    }
}

