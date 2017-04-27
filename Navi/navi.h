#ifndef NAVI_H
#define NAVI_H


#include <QWidget>
#include <QtSvg/QtSvg>
#include <QtSvg/QSvgRenderer>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Navi : public QWidget
{

    Q_OBJECT

public:
    Navi(QWidget *parent = 0);

    bool homeScreen = true;
    bool navScreen = false;
    bool playerScreen = false;
    bool phoneScreen = false;

private:

    //######### GENERAL #########
    QTimer *timer;

    QPainter *backGroundRect = new QPainter (this);
    QPainter *paninter_return = new QPainter (this);
    QSvgRenderer *renderer_returnIcon;


    //######### NAV PLAYER #########
    QPainter *navigationCard = new QPainter (this);

    QSvgRenderer *renderer_navigationIcon;
    QPainter *painter_navigationIcon = new QPainter (this);

    //######### MUSIC PLAYER #########
    QPainter *musicPlayer_CardBack = new QPainter (this);
    QPainter *musicPlayer_CardUpBar = new QPainter (this);
    QPainter *musicPlayer_CardDownBar = new QPainter (this);

    QPainter *paniter_musicPlayer_Play = new QPainter (this);
    QSvgRenderer *renderer_playIcon;

    QPainter *paniter_musicPlayer_Stop = new QPainter (this);
    QSvgRenderer *renderer_stopIcon;

    QPainter *paniter_musicPlayer_Next = new QPainter (this);
    QSvgRenderer *renderer_nextIcon;

    QPainter *paniter_musicPlayer_Previous = new QPainter (this);
    QSvgRenderer *renderer_previousIcon;

    QPainter *musicPlayer_List = new QPainter (this);
    QPainter *musicPlayer_CurrentSongImg = new QPainter (this);

    QMediaPlayer *player = new QMediaPlayer;
    QMediaPlaylist *playlist = new QMediaPlaylist;
    bool isPlaying = false;
    QPainter *currentMadiaTime = new QPainter (this);
    QPainter *currentMadiaTotalTime = new QPainter (this);
    QPainter *mediaTimeBar = new QPainter (this);
    QPainter *currentMadiaTimeBar = new QPainter (this);

    //######### PHONE PLAYER #########
    QPainter *phonePlayerCard = new QPainter (this);
    QSvgRenderer *renderer_phoneIcon;
    QPainter *painter_phoneIcon = new QPainter (this);


protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *eventPress) override;

};

#endif // NAVI_H


