
#include <ZMessageBox.h>

#include "sysinfoengine.h"
#include "dapplication.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <UTIL_MemInfo.h>

#include <string.h>
#include <unistd.h>

QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

void SysInfoEngine :: initial( )
{

}

void SysInfoEngine :: MemInfo( )
{
    long perUsed,peractived,perShared,perCached,perBufferd;
    long mtotal,mfree,muse,mcache,mbuffer,mactive,mshare;
    char memstr[256];

    UTIL_MemInfo *meminfo = new UTIL_MemInfo();
    meminfo->refresh();
    mtotal = meminfo->memTotal() /1024;
    mfree = meminfo->memFree() /1024;
    muse = mtotal - mfree;
    mcache = meminfo->cached() /1024;
    mbuffer = meminfo->buffers() /1024;
    mactive = meminfo->active() /1024;
    mshare = meminfo->memShared() /1024;

    sprintf(memstr,"\n\n\n\n\n\n \
           Memory information:\n \
                Total:    %6dK\n \
                Used:     %6dK\n \
                Free:     %6dK\n \
                Cached:   %6dK\n \
                Bufferd:  %6dK\n \
                Active:   %6dK",
            mtotal,
            muse,
            mfree,
            mcache,
            mbuffer,
            mactive);

    perUsed = 100 - mfree * 100 / mtotal;
    peractived = mactive * 100 / mtotal;
    perShared = mshare * 100 / mtotal;
    perCached = mcache * 100 / mtotal;
    perBufferd = mbuffer * 100 / mtotal;

    canvas->updateMemInfo((int)perUsed,(int)peractived,(int)perShared,(int)perCached,(int)perBufferd);
    canvas->updateMemText(memstr);
    canvas->update();
    delete meminfo;

}
void SysInfoEngine :: CpuInfo( )
{
    float usage, sys, usr;
    if(ReadCpuInfo(&usage,&sys,&usr)){
        canvas->updateCpuInfo((int)usage,(int)sys,(int)usr);
    }else
    {
        printf("error while reading cpu information\n");
    }
}

void SysInfoEngine :: QCopReceived(int message)
{

}

void SysInfoEngine :: pointerPressed( int x, int y )
{
    std::cout << "Pointer pressed on " << x << "," << y << std::endl;
    if( x > 220 && y < 10 )
    {
        beforeterminate( );
        DApplication :: exit();
        ::exit( 0 );
    }
    
}

void SysInfoEngine :: pointerDragged( int x, int y )
{
    //std::cout << "Pointer dragged on " << x << "," << y << std::endl;
}

void SysInfoEngine :: pointerReleased( int x, int y )
{
    //std::cout << "Pointer released on " << x << "," << y << std::endl;
}

void SysInfoEngine :: keyPressed(int keycode)
{

}

void SysInfoEngine :: beforeterminate( )
{
}


int   SysInfoEngine :: FiveCpuNumbers(_ULL   *uret,_ULL   *nret,_ULL   *sret,_ULL   *iret,_ULL   *iowait)  
{  
      static   _ULL   u   =   0,   m   =   0,   s   =   0,   i   =   0,   iw   =   0;  
      _ULL   user_j,   nice_j,   sys_j,   idle_j,   iowait_j   =   0;  
      FILE   *fp;  
      size_t   byte_read;  
      char   buffer[100];  

      fp   =   fopen("/proc/stat",   "r");  
      byte_read   =   fread(buffer,   1,   sizeof(buffer)-1,   fp);  
      fclose(fp);  

      if   (byte_read==0   ||   byte_read==sizeof(buffer))  return   -1;  

      buffer[byte_read]   =   '\0';  

      sscanf(buffer,   "cpu   %Lu   %Lu   %Lu   %Lu   %Lu",   &user_j,   &nice_j,   &sys_j,   &idle_j,   &iowait_j);  

      SET_IF_DESIRED(uret,   user_j   -   u);  
      SET_IF_DESIRED(nret,   nice_j   -   m);  
      SET_IF_DESIRED(sret,   sys_j   -   s);  
  /*   Idle   can   go   backwards   one   tick   due   to   kernel   calculation   issues   */  
      SET_IF_DESIRED(iret,   (idle_j   >   i)   ?   (idle_j   -   i)   :   0);  
      SET_IF_DESIRED(iowait,   iowait_j   -   iw);  

      u   =   user_j;  
      m   =   nice_j;  
      s   =   sys_j;  
      i   =   idle_j;  
      iw   =   iowait_j;  
  //printf("cpu   %Lu   %Lu   %Lu   %Lu   %Lu   \n",user_j,nice_j,sys_j,idle_j,iowait_j);  
  return   0;  
}  
   
  /*  
    *   get   the   cpu   usage  
    */  
bool   SysInfoEngine :: ReadCpuInfo(float *usage,float *usr,float *sys )  
{  
      float   cpu_usage;  
      _ULL   user_j,   nice_j,   sys_j,   idle_j,   iowait_j   =   0;  

      if(FiveCpuNumbers(&user_j,   &nice_j,   &sys_j,   &idle_j,   &iowait_j)!=0)  return   false;  
      usleep(50000);  
      if(FiveCpuNumbers(&user_j,   &nice_j,   &sys_j,   &idle_j,   &iowait_j)!=0)  return   -1;  
      usleep(50000);  
      if(FiveCpuNumbers(&user_j,   &nice_j,   &sys_j,   &idle_j,   &iowait_j)!=0)  return   -1;  

      cpu_usage   =   (idle_j * 100.0)   /   (user_j   +   nice_j   +   sys_j   +   idle_j   +   iowait_j);  
      *usr = (user_j * 100.0)   /   (user_j   +   nice_j   +   sys_j   +   idle_j   +   iowait_j);
      *sys = (sys_j * 100.0)   /   (user_j   +   nice_j   +   sys_j   +   idle_j   +   iowait_j);
      if   (cpu_usage>100.0)  cpu_usage   =   100.0;  

      /*   change   to   useage   */  
      cpu_usage   =   100.0   -   (cpu_usage);
      *usage = cpu_usage;
      //printf("###   CPU   Usage   :   %0.3f   %%\n",   cpu_usage*100);  
      return   true;  
}  

