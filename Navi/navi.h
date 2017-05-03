#ifndef NAVI_H
#define NAVI_H


#include <QWidget>
#include <QtSvg/QtSvg>
#include <QtSvg/QSvgRenderer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QStringList>

class Navi : public QWidget
{

    Q_OBJECT

public:
    Navi(QWidget *parent = 0);

    int display_height = 600;
    int display_width = 1024;

    bool homeScreen = true;
    bool navScreen = false;
    bool playerScreen = false;
    bool phoneScreen = false;
    int itemSelected = 0; // home = 0; mp = 1; nav = 2; phone = 3

    int currentSongPos = 0;

private:

    //######### GENERAL #########
    QTime *time;
    QTimer *timer;

    QPainter *backGroundRect = new QPainter (this);
    QPainter *painter_upBar = new QPainter (this);
    QPainter *painter_timeLabel = new QPainter (this);
    QPainter *paninter_return = new QPainter (this);
    QSvgRenderer *renderer_returnIcon;

    QPainter *paniter_sideBarBackground = new QPainter (this);
    QPainter *painter_selectedItemOnSideBarBackground = new QPainter (this);

    QPainter *painter_homeIcon = new QPainter (this);
    QSvgRenderer *renderer_homeIcon;

    QPainter *painter_navigationIcon = new QPainter (this);
    QSvgRenderer *renderer_navigationIcon;

    QPainter *painter_phoneIcon = new QPainter (this);
    QSvgRenderer *renderer_phoneIcon;

    QPainter *painter_musicIcon = new QPainter (this);
    QSvgRenderer *renderer_musicIcon;

    //######### NAV PLAYER #########
    QPainter *painter_backgroundColor = new QPainter (this);

    //######### MUSIC PLAYER #########
    QPainter *musicPlayer_CardUpBar = new QPainter (this);
    QPainter *musicPlayer_CardDownBar = new QPainter (this);
    QPainter *painter_mediaTimeBarBack = new QPainter (this);

    QStringList fileList;

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



protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *eventPress) override;

};

#endif // NAVI_H


