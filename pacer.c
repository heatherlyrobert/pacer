/*============================----beg-of-source---============================*/

#include   "pacer.h"



#define   PLAY       -0.0002
#define   STOP        0.0
#define   MAX_SPEED   0.0005
#define   INC_SPEED   0.0001
#define   STEP        (1.0 / 8.0)
float     offset    = 0.0;            /* background image offset               */
float     increment = PLAY;
char      action    = 0;
int       curr      = 0;
int       speed     = 0;

float     prog      = 0.0f;
float     per       = 0.0f;
float     total     = 0.0f;

float     num_min   = 0.0f;
float     len_min   = 0.0f;
float     len_sec   = 0.0f;


char     *face_eng  = "clarity";
/*> char     *face_eng  = "verdana";                                                  <*/
/*> int       txf_eng;                                                                <*/






/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}


llong
time_stamp()                      /* PURPOSE : timestamp in microseconds      */
{
   /* second
    * millisecond  ms  0.001 sec
    * microsecond  us  0.000001 sec
    * nanosecond   ns  0.000000001 sec
    * picosecond   ps  0.000000000001 sec
    */
   llong             tint = 0;
   struct timeval   tv;
   gettimeofday (&tv, NULL);
   tint += (int) (tv.tv_sec  * 1000000.0);
   tint += (int) (tv.tv_usec / 1000000.0);
   return tint;
}



/*============================--------------------============================*/
/*===----                             input                            ----===*/
/*============================--------------------============================*/
static void      o___INPUT___________________o (void) {;}



/*====================------------------------------------====================*/
/*===----                           drivers                            ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVERS_________________o (void) {;}

/*> char        /+ PURPOSE : process the command line arguments                   +/    <* 
 *> prog_args     (int argc, char *argv[])                                              <* 
 *> {                                                                                   <* 
 *>                                                                                     <* 
 *>    char    *a = NULL;                                                               <* 
 *>    int       i;                                                                     <* 
 *>    int       len       = 0;                                                         <* 
 *>    for (i = 1; i < argc; ++i) {                                                     <* 
 *>       a = argv[i];                                                                  <* 
 *>       if      (strncmp(a, "@t",     5) == 0)     debug_top                 = 1;     <* 
 *>       else if (strncmp(a, "@m",     5) == 0)     debug_top   = debug_mem   = 1;     <* 
 *>       else if (strncmp(a, "@i",     5) == 0)     debug_top   = debug_input = 1;     <* 
 *>       else if (strncmp(a, "@a",     5) == 0)     debug_top   = debug_args  = 1;     <* 
 *>       else if (strncmp(a, "@g",     5) == 0)     debug_top   = debug_graph = 1;     <* 
 *>       else if (strncmp(a, "-l",     5) == 0)     arg_list    = 1;                   <* 
 *>       else                                       strncpy(set_name, a, LEN_LABEL);   <* 
 *>    }                                                                                <* 
 *>    return 0;                                                                        <* 
 *> }                                                                                   <*/

/*> char        /+ PURPOSE : drive program setup activities                       +/     <* 
 *> prog_begin(void)                                                                     <* 
 *> {                                                                                    <* 
 *>    /+---(open window)---------------------------+/                                   <* 
 *>    yXINIT_start(win_title, my.win_w, my.win_h, YX_FOCUSABLE, YX_FIXED, YX_SILENT);   <* 
 *>    /+---(create texture)------------------------+/                                   <* 
 *>    font_load();                                                                      <* 
 *>    draw_init();                                                                      <* 
 *>    draw_main();                                                                      <* 
 *>    /+---(complete)------------------------------+/                                   <* 
 *>    return 0;                                                                         <* 
 *> }                                                                                    <*/

/*> char        /+ PURPOSE : process the xwindows event stream                    +/               <* 
 *> prog_event    (void)                                                                           <* 
 *> {                                                                                              <* 
 *>    /+---(locals)--------------------------------+/                                             <* 
 *>    long  xstart, xstop, xspeed;           /+ time drawing                     +/               <* 
 *>    /+---(for event)------------------------+/                                                  <* 
 *>    XKeyEvent *key_event;                                                                       <* 
 *>    char       the_key[5];                                                                      <* 
 *>    int        the_bytes;                                                                       <* 
 *>    char       done   = 0;                                                                      <* 
 *>    /+---(event loop)----------------------------+/                                             <* 
 *>    while (!done) {                                                                             <* 
 *>       if (XPending(DISP) || action == 0) {                                                     <* 
 *>          XNextEvent(DISP, &EVNT);                                                              <* 
 *>          /+---(start)----------------------------+/                                            <* 
 *>          switch(EVNT.type) {                                                                   <* 
 *>          case Expose:                                                                          <* 
 *>             /+> if (EVNT.xexpose.count == 0) draw_main();                                <+/   <* 
 *>             break;                                                                             <* 
 *>                                                                                                <* 
 *>          case ConfigureNotify:                                                                 <* 
 *>             break;                                                                             <* 
 *>                                                                                                <* 
 *>          case KeyPress:                                                                        <* 
 *>             key_event  = (XKeyEvent *) &EVNT;                                                  <* 
 *>             the_bytes = XLookupString((XKeyEvent *) &EVNT, the_key, 5, NULL, NULL);            <* 
 *>             if (the_bytes < 1) break;                                                          <* 
 *>             switch (the_key[0]) {                                                              <* 
 *>             case 'Q': done = 1;                   break;                                       <* 
 *>             case '<': curr -= 1; break;                                                        <* 
 *>             case '-': increment -= INC_SPEED;              break;                              <* 
 *>             case '.': increment  = STOP;   action = 0;     break;                              <* 
 *>             case ',': increment  = PLAY;                   break;                              <* 
 *>             case '+': increment += INC_SPEED;              break;                              <* 
 *>             case '>': curr += 1; break;                                                        <* 
 *>             }                                                                                  <* 
 *>             if (increment >  MAX_SPEED)  increment =  MAX_SPEED;                               <* 
 *>             if (increment < -MAX_SPEED)  increment = -MAX_SPEED;                               <* 
 *>             action = 0;                                                                        <* 
 *>             if (increment != 0.0)     action    = 1;                                           <* 
 *>             break;                                                                             <* 
 *>                                                                                                <* 
 *>          default          :                                                                    <* 
 *>             break;                                                                             <* 
 *>          }                                                                                     <* 
 *>       }                                                                                        <* 
 *>       /+---(timer)----------------------------------------+/                                   <* 
 *>       if (action) offset -=  increment;                                                        <* 
 *>       if (offset <  0.0) offset +=  1.0;                                                       <* 
 *>       if (offset >  1.0) offset -=  1.0;                                                       <* 
 *>       xstart = time_stamp();                                                                   <* 
 *>       draw_texture();                                                                          <* 
 *>       xstop  = time_stamp();                                                                   <* 
 *>       xspeed = xstop - xstart;                                                                 <* 
 *>       if (action == 1) {                                                                       <* 
 *>          usleep(100000);                                                                       <* 
 *>          prog += (0.01 / 6.0);                                                                 <* 
 *>          if (prog > my.tex_w - 100) prog = my.tex_w - 100;                                     <* 
 *>       }                                                                                        <* 
 *>    }                                                                                           <* 
 *>    /+---(complete)------------------------------+/                                             <* 
 *>    return 0;                                                                                   <* 
 *> }                                                                                              <*/

/*> char        /+ PURPOSE : drive the program closure activities                 +/   <* 
 *> prog_end      (void)                                                               <* 
 *> {                                                                                  <* 
 *>    font_delete();                                                                  <* 
 *>    yXINIT_end();                  /+ close window and xwin context            +/   <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/



/*====================------------------------------------====================*/
/*===----                             fonts                            ----===*/
/*====================------------------------------------====================*/
static void      o___FONTS___________________o (void) {;}

/*> char                                                                              <* 
 *> font_load(void)                                                                   <* 
 *> {                                                                                 <* 
 *>    txf_eng = yFONT_load(face_eng);                                                <* 
 *>    if (txf_eng <  0) {                                                            <* 
 *>       fprintf(stderr, "Problem loading %s\n", face_eng);                          <* 
 *>       exit(1);                                                                    <* 
 *>    }                                                                              <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                              <* 
 *> font_delete(void)                                                                 <* 
 *> {                                                                                 <* 
 *>    yFONT_free(txf_eng);                                                           <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/




/*============================--------------------============================*/
/*===----                             draw                             ----===*/
/*============================--------------------============================*/
static void      o___OPENGL__________________o (void) {;}





/*============================----end-of-source---============================*/
