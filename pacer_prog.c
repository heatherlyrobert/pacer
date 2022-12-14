/*============================----beg-of-source---============================*/
#include   "pacer.h"


tMY       my;


/*============================--------------------============================*/
/*===----                     startup and shutdown                     ----===*/
/*============================--------------------============================*/
void o___SHOOTS_________________o (void) {;}

char      verstring    [500];

char*        /*-> return library versio --------------[ leaf   [gs.420.012.00]*/ /*-[00.0000.012.!]-*/ /*-[--.---.---.--]-*/
PROG_version         (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __CBANG__  > 0
   strncpy (t, "[cbang      ]", 15);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (verstring, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return verstring;
}



/*====================------------------------------------====================*/
/*===----                       pre-initialization                     ----===*/
/*====================------------------------------------====================*/
static void      o___PREINIT_________________o (void) {;}

char       /*----: very first setup ------------------s-----------------------*/
PROG__header            (void)
{
   /*---(header)----------------------*/
   DEBUG_PROG   yLOG_enter (__FUNCTION__);
   /*---(versioning)------------------*/
   DEBUG_PROG   yLOG_info     ("gregg"   , PROG_version      ());
   DEBUG_PROG   yLOG_info     ("purpose" , P_PURPOSE);
   DEBUG_PROG   yLOG_info     ("namesake", P_NAMESAKE);
   DEBUG_PROG   yLOG_info     ("heritage", P_HERITAGE);
   DEBUG_PROG   yLOG_info     ("imagery" , P_IMAGERY);
   DEBUG_PROG   yLOG_note     ("custom core");
   DEBUG_PROG   yLOG_info     ("yURG"    , yURG_version      ());
   DEBUG_PROG   yLOG_info     ("yLOG"    , yLOGS_version     ());
   DEBUG_PROG   yLOG_info     ("ySTR"    , ySTR_version      ());
   DEBUG_PROG   yLOG_note     ("yvikeys foundation");
   DEBUG_PROG   yLOG_info     ("yMODE"   , yMODE_version     ());
   DEBUG_PROG   yLOG_info     ("yKEYS"   , yKEYS_version     ());
   DEBUG_PROG   yLOG_info     ("yFILE"   , yFILE_version     ());
   DEBUG_PROG   yLOG_info     ("yVIEW"   , yVIEW_version     ());
   DEBUG_PROG   yLOG_note     ("yvikeys major");
   DEBUG_PROG   yLOG_info     ("yMAP"    , yMAP_version      ());
   DEBUG_PROG   yLOG_info     ("yCMD"    , yCMD_version      ());
   DEBUG_PROG   yLOG_info     ("yMACRO"  , yMACRO_version    ());
   DEBUG_PROG   yLOG_info     ("ySRC"    , ySRC_version      ());
   DEBUG_PROG   yLOG_info     ("yMARK"   , yMARK_version     ());
   DEBUG_PROG   yLOG_note     ("custom opengl");
   DEBUG_PROG   yLOG_info     ("yVIOP"   , yVIOPENGL_version ());
   DEBUG_PROG   yLOG_info     ("yX11"    , yX11_version      ());
   DEBUG_PROG   yLOG_info     ("yFONT"   , yFONT_version     ());
   DEBUG_PROG   yLOG_info     ("yCOLOR"  , yCOLOR_version    ());
   DEBUG_PROG   yLOG_info     ("yGLTEX"  , yGLTEX_version    ());
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG_urgents            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(set mute)-----------------------*/
   yURG_all_mute ();
   /*---(start logger)-------------------*/
   rc = yURG_logger  (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = yURG_urgs    (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = PROG__header ();
   DEBUG_PROG   yLOG_value    ("header"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        program startup                       ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP_________________o (void) {;}

char       /*----: very first setup ------------------s-----------------------*/
PROG__init              (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   DEBUG_PROG   yLOG_enter (__FUNCTION__);
   /*---(defaults)-----------------------*/
   my.win_w     =  1366;                /* window width                   */
   my.win_h     =    40;                /* window height                  */
   my.tex_w     =  1000;                /* texture width                  */
   my.tex_h     =   125;                /* texture height                 */
   strlcpy (my.conf, MYCONF, LEN_HUND);
   my.beg = my.cur = my.dur = my.prg = 0.0;
   /*---(yviopengl config)---------------*/
   rc = yVIOPENGL_init   (P_NAMESAKE, P_VERNUM, MODE_MAP, my.win_w,  my.win_h);
   DEBUG_PROG   yLOG_value    ("yVIOPENGL" , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*> strlcpy (my.t_text     , "arachne, spider robot visualization and simulation"       , LEN_STR  );   <*/
   /*---(library config)-----------------*/
   rc = yMAP_config       (YMAP_OFFICE, NULL, NULL, NULL, NULL, NULL, NULL);
   DEBUG_PROG   yLOG_value    ("yMAP"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(setup yVIKEYS)------------------*/
   DEBUG_PROG   yLOG_note  ("prepare modes");
   /*> yVIKEYS_init   (MODE_GOD);                                                     <*/
   /*> yGOLEM_init    ();                                                             <*/
   /*> yVIKEYS_mode_init    ();                                                       <* 
    *> yVIKEYS_mode_enter   (MODE_GOD);                                               <*/
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG__args              (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   char       *a           = NULL;
   char       *b           = NULL;
   int         x_total     =    0;
   int         x_args      =    0;
   uchar       x_name      [LEN_FULL]  = "";
   uchar       t           [LEN_FULL]  = "";
   /*---(header)-------------------------*/
   /*> printf ("entering PROG_args\n");                                               <*/
   DEBUG_ARGS  yLOG_enter   (__FUNCTION__);
   /*---(process)------------------------*/
   for (i = 1; i < a_argc; ++i) {
      /*---(set up args)-----------------*/
      DEBUG_ARGS  yLOG_value   ("check----" , i);
      a = a_argv [i];
      if (i + 1 < a_argc)  b = a_argv [i + 1];
      else                 b = NULL;
      DEBUG_ARGS  yLOG_info    ("a"         , a);
      DEBUG_ARGS  yLOG_info    ("b"         , b);
      ++x_total;
      /*---(check vikeys)----------------*/
      rc = yKEYS_arg_handle (&i, a, b);
      DEBUG_ARGS  yLOG_value   ("ykeys"     , rc);
      if (rc == 1) {
         DEBUG_ARGS  yLOG_note    ("handled by yKEYS_arg_handle");
         DEBUG_ARGS  yLOG_value   ("bumped i"  , i);
         continue;
      }
      /*---(filter)----------------------*/
      if (a[0] == '@') {
         DEBUG_ARGS  yLOG_note    ("skipped urgent");
         continue;
      }
      /*---(local)-----------------------*/
      DEBUG_ARGS  yLOG_note    ("check for local argument handling");
      ++x_args;
      if (a [0] != '-') {
         strlcpy (my.target, a, LEN_LABEL);
      }
      /*> if      (strcmp (a, "--rptg-touch"        ) == 0)   my.rptg_touch   = 'y';           <* 
       *> else if (strcmp (a, "--rptg-raw"          ) == 0)   my.rptg_raw     = 'y';           <* 
       *> else if (strcmp (a, "--rptg-base"         ) == 0)   my.rptg_base    = 'y';           <* 
       *> else if (strcmp (a, "--rptg-key"          ) == 0)   my.rptg_key     = 'y';           <* 
       *> else if (strcmp (a, "--rptg-dict"         ) == 0)   my.rptg_dict    = 'y';           <* 
       *> else if (strcmp (a, "--rptg-letter"       ) == 0)   my.rptg_letter  = 'y';           <* 
       *> else if (strcmp (a, "--show-control"      ) == 0)   my.show_control = 'y';           <* 
       *> else if (strcmp (a, "--show-player"       ) == 0)   my.show_player  = 'y';           <* 
       *> else if (strcmp (a, "--show-sample"       ) == 0)   my.show_sample  = 'y';           <* 
       *> else if (strcmp (a, "--english"           ) == 0)   my.run_mode     = RUN_ENGLISH;   <* 
       *> else if (strcmp (a, "--gregg"             ) == 0)   my.run_mode     = RUN_GREGG;     <* 
       *> else if (strcmp (a, "--convert"           ) == 0)   my.run_mode     = RUN_CONVERT;   <* 
       *> else if (strcmp (a, "--exact"             ) == 0)   my.run_mode     = RUN_EXACT;     <* 
       *> else if (strcmp (a, "--reverse"           ) == 0)   my.run_mode     = RUN_REVERSE;   <* 
       *> else if (strcmp (a, "--words"             ) == 0)   my.run_mode     = RUN_WORDS;     <*/
   }
   DEBUG_ARGS  yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS  yLOG_value  ("arguments" , x_args);
   if (x_args == 0) {
      DEBUG_ARGS  yLOG_note   ("no arguments identified");
   }
   /*---(complete)-----------------------*/
   DEBUG_ARGS  yLOG_exit  (__FUNCTION__);
   return 0;
}


char       /*----: drive program setup activities ----------------------------*/
PROG__begin             (void)
{
   char        rc          =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_startup            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   yURG_stage_check (YURG_BEG);
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = PROG__init   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(arguments)----------------------*/
   rc = PROG__args   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("args"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)--------------------------*/
   rc = PROG__begin  ();
   DEBUG_PROG   yLOG_value    ("begin"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   yURG_stage_check (YURG_MID);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        program execution                     ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTION_______________o (void) {;}

char       /*----: process the xwindows event stream -------------------------*/
PROG_dawn          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(create window)------------------*/
   rc = yVIOPENGL_dawn ();
   DEBUG_PROG   yLOG_value   ("dawn"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yCMD_direct (":layout min");
   DRAW_init  ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_dusk          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter (__FUNCTION__);
   /*---(clean up)-----------------------*/
   DRAW_wrap  ();
   /*---(destroy window)-----------------*/
   rc = yVIOPENGL_dusk ();
   DEBUG_PROG   yLOG_value   ("dusk"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program shutdown                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN________________o (void) {;}

char       /*----: drive the program closure activities ----------------------*/
PROG__end               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(shutdown)--------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(destroy window)-----------------*/
   rc = yVIOPENGL_wrap ();
   DEBUG_PROG   yLOG_value   ("wrap"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   FONT_free    ();
   DRAW_wrap    ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] drive the program closure activities ------------*/
PROG_shutdown           (void)
{
   /*---(stage-check)--------------------*/
   yURG_stage_check (YURG_END);
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter    (__FUNCTION__);
   PROG__end ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit     (__FUNCTION__);
   DEBUG_PROG   yLOGS_end    ();
   return 0;
}



/*============================----(source-end)----============================*/
