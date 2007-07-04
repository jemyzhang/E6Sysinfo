
#include <qcanvas.h>
#include <stdio.h>
#include "sysinfocanvas.h"


void SysInfoCanvas :: init( )
{
    pointcnt = 0;
    for(int i = 0; i< CPUPOINTS; i++) {
//        pointpos[i] = 0;
        pointpos1[i] = 0;
        pointpos2[i] = 0;
    }
}

void SysInfoCanvas :: updateMemUsed(int persent)
{
    memUsedBox->setSize(MEMWIDTH * persent / 100,memUsedBox->height());
}


void SysInfoCanvas :: updateMemActived(int persent)
{
    memActivedBox->setSize(MEMWIDTH * persent / 100,memActivedBox->height());
}

void SysInfoCanvas :: updateMemShared(int persent)
{
    memSharedBox->setSize(MEMWIDTH * persent / 100,memSharedBox->height());
}

void SysInfoCanvas :: updateMemCached(int persent)
{
    memCachedBox->setSize(MEMWIDTH * persent / 100,memCachedBox->height());
}

void SysInfoCanvas :: updateMemBufferd(int persent)
{
    memBufferdBox->setSize(MEMWIDTH * persent / 100,memBufferdBox->height());
}

void SysInfoCanvas :: updateMemInfo(int perused,int peractived,int pershared,int percached,int perbuffered )
{
    updateMemUsed(perused);
    updateMemActived(peractived);
    updateMemShared(pershared);
    updateMemCached(percached);
    updateMemBufferd(perbuffered);
}

void SysInfoCanvas :: updateCpuInfo(int persent,int sysper,int usrper)
{
    if (pointcnt < CPUPOINTS) {
//        pointpos[pointcnt] = CPUHSTOP - CPUHEIGHT * persent / 100;
        pointpos1[pointcnt] = CPUHSTOP - CPUHEIGHT * sysper / 100;
        pointpos2[pointcnt] = CPUHSTOP2 - CPUHEIGHT * usrper / 100;
        for(int i = 0; i < pointcnt; i++) {
//            cpuinfoLine[i]->setPoints(CPUWIDTH - CPUSTEP * (pointcnt - i),pointpos[i],
//                                        CPUWIDTH - CPUSTEP * (pointcnt -1 - i),pointpos[i + 1]);
            cpuSysLine[i]->setPoints(CPUWIDTH + CPUWSTART - CPUSTEP * (pointcnt - i),pointpos1[i],
                                        CPUWIDTH + CPUWSTART - CPUSTEP * (pointcnt -1 - i),pointpos1[i + 1]);
            cpuUsrLine[i]->setPoints(CPUWIDTH + CPUWSTART - CPUSTEP * (pointcnt - i),pointpos2[i],
                                        CPUWIDTH + CPUWSTART - CPUSTEP * (pointcnt -1 - i),pointpos2[i + 1]);
        }
        pointcnt ++;
    }else
    {
        for(int i = 1; i < CPUPOINTS;i ++) {
//            pointpos[i-1] = pointpos[i];
            pointpos1[i-1] = pointpos1[i];
            pointpos2[i-1] = pointpos2[i];
        }
//        pointpos[CPUPOINTS - 1] = CPUHSTOP - CPUHEIGHT * persent / 100;
        pointpos1[CPUPOINTS - 1] = CPUHSTOP - CPUHEIGHT * sysper / 100;
        pointpos2[CPUPOINTS - 1] = CPUHSTOP2 - CPUHEIGHT * usrper / 100;

        for(int i = 1; i < CPUPOINTS; i ++) {
//            cpuinfoLine[i-1]->setPoints(CPUWSTART + CPUSTEP * (i -1),pointpos[i-1],
//                                        CPUWSTART + CPUSTEP * i,pointpos[i]);
            cpuSysLine[i-1]->setPoints(CPUWSTART + CPUSTEP * (i -1),pointpos1[i-1],
                                        CPUWSTART + CPUSTEP * i,pointpos1[i]);
            cpuUsrLine[i-1]->setPoints(CPUWSTART + CPUSTEP * (i -1),pointpos2[i-1],
                                        CPUWSTART + CPUSTEP * i,pointpos2[i]);
        }
    }
}

void SysInfoCanvas :: updateMemText(char *str)
{
    memInfoText->setText(str);
}
