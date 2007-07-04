
#ifndef _SysInfoCANVAS_H_
#define _SysInfoCANVAS_H_

#include <qcanvas.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qtextcodec.h>
#include <stdio.h>
#include "pictures.h"
#include <time.h>
#include "sysinfo.h"
#include "dapplication.h"

#define MEMWIDTH 200
#define MEMHSTART 35
#define CPUHSTOP 290
#define CPUHSTOP2 292
#define CPUWSTART 20
#define CPUWIDTH 200
#define CPUHEIGHT 90
#define CPULINES 20
#define CPUPOINTS CPULINES + 1
#define CPUSTEP CPUWIDTH/CPULINES

#define ISTHSTART 115
#define ISTWSTART 35

static const QColor colorarray[]={
    Qt::darkRed,Qt::green,Qt::blue,Qt::yellow,Qt::cyan,Qt::red,Qt::yellow
};

class SysInfoCanvas : public QCanvas
{
    QCanvasText *memInfoText;
    QCanvasRectangle *memTotalBox;
    QCanvasRectangle *memUsedBox;
    QCanvasRectangle *memActivedBox;
    QCanvasRectangle *memSharedBox;
    QCanvasRectangle *memCachedBox;
    QCanvasRectangle *memBufferdBox;
    QCanvasRectangle *istbox[5];

//    QCanvasLine *cpuinfoLine[CPULINES];
    QCanvasLine *cpuUsrLine[CPULINES];
    QCanvasLine *cpuSysLine[CPULINES];

    int pointcnt;
//    int pointpos[CPUPOINTS];
    int pointpos1[CPUPOINTS];
    int pointpos2[CPUPOINTS];
    void init( );

    void updateMemUsed(int persent);
    void updateMemActived(int persent);
    void updateMemShared(int persent);
    void updateMemCached(int persent);
    void updateMemBufferd(int persent);

public:
    void updateMemInfo(int perused,int peractived,int pershared,int percached,int perbuffered );
    void updateCpuInfo(int persent,int sysper,int usrper);
    void updateMemText(char *str);

        SysInfoCanvas( int w, int h ) : QCanvas( w, h )
        {
            init();

            for( int i = 0; i < 1; i++) {
                QCanvasPixmap *img = new QCanvasPixmap(static_screen_xpm[i],QPoint(static_screen_pos[i].x , static_screen_pos[i].y));
                QCanvasPixmapArray *imgarray = new QCanvasPixmapArray( );
                imgarray->setImage(0,img);
                QCanvasSprite *static_Screen_sprite = new QCanvasSprite(imgarray,this);
                static_Screen_sprite->show();
            }

            QCanvasText *title = new QCanvasText("       System Infomation",this);
            QFont tfont = title->font();
            tfont.setPixelSize(20);
            title->setColor(yellow);
            title->setFont(tfont);
            title->show();

            memInfoText = new QCanvasText(" ",this);
            QFont *tfont2 = new QFont();
            tfont2->setPixelSize(12);
            memInfoText->setColor(white);
            memInfoText->setFont(*tfont2);
            memInfoText->show();

            QCanvasText *cpuInfoText = new QCanvasText("\n\n\n\n\n\n\n\n\n\n\n\n\n\n             USER\n            SYS ",this);
            cpuInfoText->setColor(white);
            cpuInfoText->setFont(*tfont2);
            cpuInfoText->show();

            QCanvasText *cpuInfoLine1 = new QCanvasText("\n\n\n\n\n\n\n\n\n\n\n\n\n\n        ----",this);
            cpuInfoLine1->setColor(yellow);
            cpuInfoLine1->setFont(*tfont2);
            cpuInfoLine1->show();

            QCanvasText *cpuInfoLine2 = new QCanvasText("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n        ----",this);
            cpuInfoLine2->setColor(red);
            cpuInfoLine2->setFont(*tfont2);
            cpuInfoLine2->show();

            memTotalBox = new QCanvasRectangle(19,MEMHSTART,201,50,this);
            QPen pen = memTotalBox->pen();
            pen.setColor(darkGray);
            pen.setStyle(SolidLine);
            memTotalBox->setPen(pen);
            QBrush brush = memTotalBox->brush();
            brush.setColor(green);
            brush.setStyle(SolidPattern);
            memTotalBox->setBrush(brush);
            memTotalBox->show();

            memUsedBox = new QCanvasRectangle(20,MEMHSTART + 1,0,48,this);
            pen = memUsedBox->pen();
            pen.setStyle(NoPen);
            memUsedBox->setPen(pen);
            brush = memUsedBox->brush();
            brush.setColor(darkRed);
            brush.setStyle(SolidPattern);
            memUsedBox->setBrush(brush);
            memUsedBox->show();

            memActivedBox = new QCanvasRectangle(20,MEMHSTART + 1 + 2 * 0,0,2,this);
            pen = memActivedBox->pen();
            pen.setStyle(NoPen);
            memActivedBox->setPen(pen);
            brush = memActivedBox->brush();
            brush.setColor(blue);
            brush.setStyle(SolidPattern);
            memActivedBox->setBrush(brush);
            memActivedBox->show();

            memCachedBox = new QCanvasRectangle(20,MEMHSTART + 1 + 2 * 1,0,2,this);
            pen = memCachedBox->pen();
            pen.setStyle(NoPen);
            memCachedBox->setPen(pen);
            brush = memCachedBox->brush();
            brush.setColor(magenta);
            brush.setStyle(SolidPattern);
            memCachedBox->setBrush(brush);
            memCachedBox->show();

            memBufferdBox = new QCanvasRectangle(20,MEMHSTART + 1 + 2 * 2,0,2,this);
            pen = memBufferdBox->pen();
            pen.setStyle(NoPen);
            memBufferdBox->setPen(pen);
            brush = memBufferdBox->brush();
            brush.setColor(yellow);
            brush.setStyle(SolidPattern);
            memBufferdBox->setBrush(brush);
            memBufferdBox->show();

            memSharedBox = new QCanvasRectangle(20,MEMHSTART + 1 + 2 * 3,0,2,this);
            pen = memSharedBox->pen();
            pen.setStyle(NoPen);
            memSharedBox->setPen(pen);
            brush = memSharedBox->brush();
            brush.setColor(cyan);
            brush.setStyle(SolidPattern);
            memSharedBox->setBrush(brush);
            memSharedBox->show();

            QCanvasRectangle *cpuinfobox = new QCanvasRectangle(18,195,204,100,this);
            pen = cpuinfobox->pen();
            pen.setColor(darkGray);
            pen.setStyle(SolidLine);
            cpuinfobox->setPen(pen);
            brush = cpuinfobox->brush();
            brush.setColor(darkGreen);
            brush.setStyle(Dense7Pattern);
            cpuinfobox->setBrush(brush);
            cpuinfobox->show();


            for(int i = 0; i < 5; i++) {
                istbox[i] = new QCanvasRectangle(ISTWSTART,ISTHSTART + 13 * i,12,12,this);
                pen = istbox[i]->pen();
                pen.setColor(darkGray);
                pen.setStyle(SolidLine);
                istbox[i]->setPen(pen);
                brush = istbox[i]->brush();
                brush.setColor(colorarray[i]);
                brush.setStyle(SolidPattern);
                istbox[i]->setBrush(brush);
                istbox[i]->show();
            }

/*
            for(int i = 0; i < CPULINES; i++) {
                cpuinfoLine[i] = new QCanvasLine(this);
                pen = cpuinfoLine[i]->pen();
                pen.setColor(green);
                cpuinfoLine[i]->setPen(pen);
                cpuinfoLine[i]->setPoints(0,0,0,0);
                cpuinfoLine[i]->show();
            }
*/
            for(int i = 0; i < CPULINES; i++) {
                cpuUsrLine[i] = new QCanvasLine(this);
                pen = cpuUsrLine[i]->pen();
                pen.setColor(yellow);
                cpuUsrLine[i]->setPen(pen);
                cpuUsrLine[i]->setPoints(0,0,0,0);
                cpuUsrLine[i]->show();
            }

            for(int i = 0; i < CPULINES; i++) {
                cpuSysLine[i] = new QCanvasLine(this);
                pen = cpuSysLine[i]->pen();
                pen.setColor(red);
                cpuSysLine[i]->setPen(pen);
                cpuSysLine[i]->setPoints(0,0,0,0);
                cpuSysLine[i]->show();
            }
            //setup background color
            setBackgroundColor( qRgb( 0, 0, 0) );
        }

        
        virtual ~SysInfoCanvas( ) {
            printf("delete image source\n");
				}

};

#endif

