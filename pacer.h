/*============================----beg-of-source---============================*/


/*===[[ ONE_LINERS ]]=========================================================*/
/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-"  */

#define     P_FOCUS     "MH (mind hacking)"
#define     P_NICHE     "sc (scheduling)"
#define     P_SUBJECT   "guide for paced activities"
#define     P_PURPOSE   "small tool to guide paced activities, like zhan zhuang"

#define     P_NAMESAKE  "penelope-ypomoni (patience)"
#define     P_HERITAGE  "wife of odysseus, endless fidelity and patience"
#define     P_IMAGERY   ""
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "pacer"
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   ""

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2010-12"

#define     P_VERMAJOR  "2.--, relaunch a more streamlined version"
#define     P_VERMINOR  "2.1-, get it working again"
#define     P_VERNUM    "2.1b"
#define     P_VERTXT    "cleaned interface and published to squarespace"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-"  */
/*===[[ END ONE_LINERS ]]=====================================================*/

/*===[[ HEADER ]]=============================================================*

 *   focus         : (MH) mind_hacking
 *   niche         : (sc) scheduling
 *   heritage      : penelope (wife of odysseus, endless fidelity and patience)
 *   purpose       : small tool to guide paced activities, like zhan zhuang
 *
 *   base_system   : gnu/linux  (because it's powerful, universal, and hackable)
 *   lang_name     : ansi-c     (because it's right, just, best, and universal)
 *   dependencies  : opengl, yFONT
 *   size goal     : tiny (less than 500 slocL)
 *
 *   author        : the_heatherlys
 *   created       : 2010-12
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, portable
 * 
 */
/*===[[ SUMMARY ]]============================================================*

 *   pacer is a small visualization tool to assist in guiding and sequencing
 *   paced activities in order to keep the mind clearer and less troubled
 *
 */
/*===[[ PURPOSE ]]============================================================*

 *   pacer will act as a prototype for a much simpler, wearable pacer that we
 *   can use in the future.  so, the idea is to evolve some excellent, standard,
 *   and simple practices that we can transport to a very, very small device
 *
 *   pacer will
 *      - provide a standard sized window and a customizable title
 *      - allows activities to be broken into sequenced positions
 *      - allows the definition of a standard period/block to measure time
 *      - allows the definition of a standard breath cycle
 *      - shows a progress bar to indicate current position
 *      - provides auditory clues for position, period, and breath changes
 *      - have some scrolling for very long sequences
 *      - use a single main configuration file, but also allow stdin
 *
 *   pacer will not...
 *      - change the size of its window
 *      - have custom sounds that vary for different sequences
 *      - have any graphics or symbols for different sequences
 *
 *   rational limits and standards...
 *      - set names less than 20 char
 *      - titles less than 100 char
 *      - period lengths must be between 0.1 and 99.9 seconds
 *      - sequence descriptions less than 50 char (just not that much room)
 *      - max of 200 steps in a sequence
 *      - step lengths must be between 1 and 99 periods
 *
 */
/*============================================================================*/


/*---(c-standard libraries)--------------*/
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <sys/time.h>
#include   <time.h>


#include    <make_opengl.h>       /* heatherly standard opengl headers        */


/*---(x11/opengl standard)---------------*/
/*> #include    <X11/X.h>        /+ X11     standard overall file                 +/   <* 
 *> #include    <X11/Xlib.h>     /+ X11     standard C API                        +/   <* 
 *> #include    <GL/gl.h>        /+ OPENGL  standard primary header               +/   <* 
 *> #include    <GL/glx.h>       /+ OPENGL  standard X11 integration              +/   <*/

/*===[[ CUSTOM LIBRARIES ]]===================================================*/
/*> #include    <yURG.h>         /+ CUSTOM : heatherly urgent processing          +/   <* 
 *> #include    <yLOG.h>         /+ CUSTOM : heatherly program logging            +/   <* 
 *> #include    <ySTR.h>         /+ CUSTOM : heatherly string handling            +/   <*/

/*---(custom vi-keys)--------------------*/
/*> #include    <yKEYS.h>             /+ heatherly vikeys key handling            +/   <* 
 *> #include    <yMODE.h>             /+ heatherly vikeys mode tracking           +/   <* 
 *> #include    <yMACRO.h>            /+ heatherly vikeys macro processing        +/   <* 
 *> #include    <ySRC.h>              /+ heatherly vikeys source editing          +/   <* 
 *> #include    <yCMD.h>              /+ heatherly vikeys command processing      +/   <* 
 *> #include    <yVIEW.h>             /+ heatherly vikeys view management         +/   <* 
 *> #include    <yMAP.h>              /+ heatherly vikeys location management     +/   <* 
 *> #include    <yFILE.h>             /+ heatherly vikeys content file handling   +/   <* 
 *> #include    <yMARK.h>             /+ heatherly vikeys search and marking      +/   <* 
 *> #include    <yVIOPENGL.h>         /+ heatherly vikeys opengl handler          +/   <*/

#include    <yEXEC.h>             /* heatherly job execution and control      */


/*> #include    <yX11.h>         /+ heatherly xlib/glx setup            +/             <* 
 *> #include    <yFONT.h>        /+ heatherly text display for opengl   +/             <* 
 *> #include    <yGLTEX.h>       /+ heatherly opengl texture support              +/   <* 
 *> #include    <yCOLOR.h>       /+ heatherly opengl color support                +/   <*/

typedef  struct cMY  tMY;
struct cMY {
   int         win_w;
   int         win_h;
   int         tex_w;
   int         tex_h;
   char        target          [LEN_LABEL];
   char        conf            [LEN_HUND];
   llong       beg;
   llong       cur;
   llong       dur;
   llong       dif;
   float       prg;
};
extern tMY  my;

#define   MYCONF  "/etc/pacer.conf"



#define   MAX_STEP      200
typedef  struct cSTEP tSTEP;
struct cSTEP {
   int       num;                      /* identifying number, i.e, seq num    */
   char      terse [LEN_TERSE];        /* short name                          */
   char      desc  [LEN_DESC];         /* descriptive text                    */
   int       dur;                      /* number of periods                   */
};
extern tSTEP     g_steps [MAX_STEP];

typedef  struct cSET  tSET;
struct cSET {
   char        title       [LEN_LABEL];
   int         chime;
   char        desc        [LEN_HUND];
   float       per;
   tSTEP       step        [MAX_STEP];
   int         max;
   int         dur;
   int         beg;
   int         cur;
   float       scale;
};
extern tSET   g_set;


extern  char   win_title[];            /* window title                        */
extern  int    size_height;            /* full window height                  */
extern  int    size_width;             /* full window width                   */

typedef   unsigned int  uint;
typedef   const char    cchar;
#define   PRIV          static


typedef struct timespec  tTSPEC;

extern char      unit_answer [LEN_RECD];

/*===[[ pacer_prog.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(support)---------------------------*/
char*       PROG_version            (void);
/*---(startup)---------------------------*/
char        PROG__init              (int argc, char *argv[]);
char        PROG__args              (int argc, char *argv[]);
char        PROG__begin             (void);
char        PROG_startup            (int argc, char *argv[]);
/*---(execution)-------------------------*/
char        PROG_dawn               (void);
char        PROG_dusk               (void);
/*---(shutdown)--------------------------*/
char        PROG__end               (void);
char        PROG_shutdown           (void);



llong       BASE_msec               (void);


/*===[[ pacer_test.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        PROG__unit_quiet        (void);
char        PROG__unit_loud         (void);
char        PROG__unit_end          (void);
char*       PROG__unit              (char *a_question, int i);


/*> int        main              (int argc, char *argv[]);                            <*/
/*> char       prog_args         (int argc, char *argv[]);                            <*/
/*> char       prog_begin        (void);                                              <*/
/*> char       prog_event        (void);                                              <*/
/*> char       prog_end          (void);                                              <*/
llong      time_stamp        (void);

char       FONT_load         (void);
char       FONT_free         (void);

char       DRAW_init         (void);
char       DRAW_wrap            (void);
char       DRAW_primary      (void);
char       draw_main         (void);
float      draw_position     (int, char*, int);
float      draw_period       (void);
char       draw_progress     (float);
char       draw_resize       (uint, uint);

char       FILE__purge             (void);
char       FILE__open              (void);
char       FILE__close             (void);
char       FILE__read              (void);
char       FILE__header            (cchar *a_recd, char *a_title, int *a_chime, char *a_desc);
char       FILE__detail            (cchar *a_recd, int *a_dur, char *a_terse, char *a_desc);
char       FILE_import             (char *a_title);

/*============================----end-of-source---============================*/
