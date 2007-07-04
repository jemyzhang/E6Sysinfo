
#ifndef _SysInfoENGINE_H_
#define _SysInfoENGINE_H_

#include <qthread.h>
#include <qfile.h>
#include <qtextstream.h>
#include "dapplication.h"
#include "sysinfocanvas.h"


#define   SET_IF_DESIRED(x,y)     if(x)   *(x)   =   (y)  
#define   _ULL   unsigned   long   long  

class SysInfoEngine : public PointerListener
{
    private:
        SysInfoCanvas *canvas;
        QCanvasView *view;
        DApplication *DApp;
        int   FiveCpuNumbers(_ULL   *uret,_ULL   *nret,_ULL   *sret,_ULL   *iret,_ULL   *iowait);
        bool ReadCpuInfo(float *usage,float *usr,float *sys );
    public:
        SysInfoEngine( SysInfoCanvas *canvas_ )
        {
            canvas = canvas_;
        }
        void initial( );
        void MemInfo( );
        void CpuInfo( );
        void beforeterminate( );
        void pointerPressed( int x, int y );
        void pointerDragged( int x, int y );
        void pointerReleased( int x, int y );
        void keyPressed(int keycode);
        void QCopReceived(int message);
};

#endif

