/*============================----beg-of-source---============================*/
#include   "pacer.h"


static llong  s_time  =  0;

llong             /* PURPOSE : timestamp in milliseconds      */
BASE_msec               (void)
{
   /* second
    * millisecond  ms  0.001 sec
    * microsecond  us  0.000001 sec
    * nanosecond   ns  0.000000001 sec
    * picosecond   ps  0.000000000001 sec
    */
   llong       a           =   0;
   tTSPEC      t;
   clock_gettime (CLOCK_MONOTONIC, &t);
   a += (llong) t.tv_sec  * 1000;
   a += (llong) t.tv_nsec / 1000000;
   /*> if (s_time == 0)  s_time  = a;                                                 <* 
    *> else              a      -= s_time;                                            <*/
   return a;
}


