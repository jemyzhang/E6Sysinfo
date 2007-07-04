
#include <qcanvas.h>

#include "sysinfo.h"
#include "sysinfocanvas.h"
#include "sysinfoengine.h"
#include <qtextcodec.h>

#include <signal.h>

SysInfoEngine *engine;

void refreshInfo(int signo)
{
    switch (signo) {
    case SIGALRM:
        engine->MemInfo();
        engine->CpuInfo();
        break;
    case SIGVTALRM:
        engine->CpuInfo();
        break;
    default:
        break;
    }
    signal(SIGALRM,refreshInfo);
    signal(ITIMER_VIRTUAL,refreshInfo);
}

void killhandle(int signo)
{
    switch(signo) {
    case SIGTERM:
        printf("catch signal: SIGTERM\n");
        break;
    case SIGINT:
        printf("catch signal: SIGTERM\n");
        break;
    default:
        printf("catch signal: UNKNOWN[%d]\n",signo);
        return;
    }
    engine->beforeterminate();
    exit(0);
}

int main( int argc, char **argv )
{
    printf("sysinfo ver.1.0beta(20070703-01.10) by Jemyzhang\n");
    ZApplication app( argc, argv );
    SysInfoCanvas *canvas = new SysInfoCanvas( 236, 316 );
    QCanvasView *view = new QCanvasView( canvas );
    engine = new SysInfoEngine( canvas );
    engine->MemInfo();
    view->showFullScreen( );
    view->show( );
    //app.setMainWidget( view );
    engine->initial( );

    signal(SIGALRM,refreshInfo);
    signal(SIGVTALRM,refreshInfo);
    signal(SIGTERM,killhandle);
    signal(SIGINT,killhandle);

    struct itimerval value,value2;
    value.it_value.tv_sec = 1;
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 1;
    value.it_interval.tv_usec = 0; 
    setitimer(ITIMER_REAL, &value,NULL);
/*
    value2.it_value.tv_sec = 0;
    value2.it_value.tv_usec = 500000;
    value2.it_interval.tv_sec = 0;
    value2.it_interval.tv_usec = 500000; 
    setitimer(ITIMER_VIRTUAL,&value2,NULL);
*/
    return app.exec( );
}

