/*============================----beg-of-source---============================*/
#include   "pacer.h"



tSET   g_set;

tSTEP     g_steps [MAX_STEP];



/*---(locals)--------------------------------*/
static FILE     *f         = NULL;            /* input file                     */
static char      s_recd [LEN_RECD] = "";         /* record from stdin              */



char
FILE__purge             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   strlcpy (g_set.title, "", LEN_LABEL);
   g_set.chime  = 0;
   strlcpy (g_set.desc , "", LEN_HUND);
   g_set.per    = 0.0f;
   for (i = 0; i < MAX_STEP; ++i) {
      g_set.step [i].num      = 0;
      strlcpy (g_set.step [i].terse, "", LEN_TERSE);
      strlcpy (g_set.step [i].desc , "", LEN_DESC);
      g_set.step [i].dur      = 0;
   }
   g_set.max    = 0;
   g_set.cur    = 0;
   g_set.dur    = 0.0f;
   g_set.scale  = 0.0f;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



char
FILE__open              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f != NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open)---------------------------*/
   DEBUG_INPT   yLOG_info    ("conf"      , my.conf);
   f = fopen (my.conf, "rt");
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILE__close             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close)--------------------------*/
   DEBUG_INPT   yLOG_info    ("conf"      , my.conf);
   f = fclose (f);
   DEBUG_INPT   yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   f = NULL;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILE__read              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(next record)--------------------*/
   --rce;  while (1) {
      /*---(read one)--------------------*/
      fgets (s_recd, LEN_RECD, f);
      if (feof (f)) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(filter)----------------------*/
      l = strlen (s_recd);
      if (s_recd [l - 1] == '\n')  s_recd [--l] = '\0';
      DEBUG_INPT   yLOG_complex ("s_recd"    , "%3då%sæ", l, s_recd);
      if (l == 0)             continue;
      if (s_recd [0] == '#')  continue;
      if (s_recd [0] != ' ') {
         DEBUG_INPT   yLOG_note    ("found a header line, returning");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 'h';
      }
      /*---(trim)------------------------*/
      strltrim (s_recd, ySTR_BOTH, LEN_RECD);
      l = strlen (s_recd);
      if (l == 0)             continue;
      if (s_recd [0] == '#')  continue;
      DEBUG_INPT   yLOG_complex ("s_recd"    , "%3då%sæ", l, s_recd);
      DEBUG_INPT   yLOG_note    ("found a detail line, returning");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 'd';
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILE__header            (cchar *a_recd, char *a_title, int *a_chime, char *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   char       *p           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   char        t           [LEN_HUND]  = "";
   int         x_chime     =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_title != NULL)  strlcpy (a_title, "", LEN_LABEL);
   if (a_chime != NULL)  *a_chime = 0;
   if (a_desc  != NULL)  strlcpy (a_desc , "", LEN_HUND);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   l = strlen (a_recd);
   DEBUG_INPT   yLOG_value   ("l"         , l);
   --rce;  if (l < 3) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(working copy)-------------------*/
   strlcpy (x_recd, a_recd, LEN_RECD);
   /*---(title)--------------------------*/
   p = strtok (x_recd, "§");
   DEBUG_INPT   yLOG_point   ("title"     , p);
   --rce;  if (p == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (t, p, LEN_HUND);
   strltrim (t, ySTR_BOTH, LEN_HUND);
   l = strlen (t);
   DEBUG_INPT   yLOG_value   ("l"         , l);
   --rce;  if (l < 3) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = strlgood (t, ySTR_ALNUM, LEN_HUND);
   DEBUG_INPT   yLOG_value   ("strlgood"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("title"     , t);
   if (a_title != NULL)  strlcpy (a_title, t, LEN_LABEL);
   /*---(chime)--------------------------*/
   p = strtok (NULL  , "§");
   DEBUG_INPT   yLOG_point   ("dur"       , p);
   --rce;  if (p != NULL) {
      strlcpy  (t, p, LEN_HUND);
      strltrim (t, ySTR_BOTH, LEN_HUND);
      l = strlen (t);
      DEBUG_INPT   yLOG_value   ("l"         , l);
      --rce;  if (l < 1) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_INPT   yLOG_info    ("t"         , t);
      rc = yEXEC_dur_in_sec (t, &x_chime);
      DEBUG_INPT   yLOG_value   ("dur_in_sec", rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_INPT   yLOG_value   ("x_chime"   , x_chime);
      --rce;  if (x_chime < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (a_chime != NULL)  *a_chime = x_chime;
   }
   /*---(desc)---------------------------*/
   p = strtok (NULL  , "§");
   DEBUG_INPT   yLOG_point   ("desc"      , p);
   --rce;  if (p != NULL) {
      strlcpy  (t, p, LEN_HUND);
      strltrim (t, ySTR_BOTH, LEN_HUND);
      DEBUG_INPT   yLOG_info    ("desc"      , t);
      if (a_desc  != NULL)  strlcpy (a_desc , t, LEN_HUND);
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILE__detail            (cchar *a_recd, int *a_dur, char *a_terse, char *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   char       *p           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   char        t           [LEN_HUND]  = "";
   int         x_dur       =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_dur   != NULL)  *a_dur   = 0;
   if (a_terse != NULL)  strlcpy (a_terse, "", LEN_LABEL);
   if (a_desc  != NULL)  strlcpy (a_desc , "", LEN_DESC);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   l = strlen (a_recd);
   DEBUG_INPT   yLOG_value   ("l"         , l);
   --rce;  if (l < 3) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(working copy)-------------------*/
   strlcpy (x_recd, a_recd, LEN_RECD);
   /*---(duration)-----------------------*/
   p = strtok (x_recd, "§");
   DEBUG_INPT   yLOG_point   ("dur"       , p);
   --rce;  if (p == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (t, p, LEN_HUND);
   strltrim (t, ySTR_BOTH, LEN_HUND);
   l = strlen (t);
   DEBUG_INPT   yLOG_value   ("l"         , l);
   --rce;  if (l < 1) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yEXEC_dur_in_sec (t, &x_dur);
   DEBUG_INPT   yLOG_value   ("dur_in_sec", rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("x_dur"     , x_dur);
   --rce;  if (x_dur <= 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(terse)--------------------------*/
   p = strtok (NULL  , "§");
   DEBUG_INPT   yLOG_point   ("terse"     , p);
   --rce;  if (p == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (t, p, LEN_HUND);
   strltrim (t, ySTR_BOTH, LEN_HUND);
   l = strlen (t);
   DEBUG_INPT   yLOG_value   ("l"         , l);
   --rce;  if (l < 3) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = strlgood (t, ySTR_ALNUM, LEN_HUND);
   DEBUG_INPT   yLOG_value   ("strlgood"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("terse"     , t);
   if (a_dur   != NULL)  *a_dur = x_dur;
   if (a_terse != NULL)  strlcpy (a_terse, t, LEN_LABEL);
   /*---(desc)---------------------------*/
   p = strtok (NULL  , "§");
   DEBUG_INPT   yLOG_point   ("desc"      , p);
   --rce;  if (p != NULL) {
      strlcpy  (t, p, LEN_HUND);
      strltrim (t, ySTR_BOTH, LEN_HUND);
      DEBUG_INPT   yLOG_info    ("desc"      , t);
      if (a_desc  != NULL)  strlcpy (a_desc , t, LEN_DESC);
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILE_import             (char *a_target)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        l           =    0;
   int         x_dur       =    0;
   int         x_chime     =    0;
   char        x_title     [LEN_LABEL] = "";
   char        x_desc      [LEN_HUND]  = "";
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(cleanse)------------------------*/
   FILE__purge ();
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_target"  , a_target);
   --rce;  if (a_target == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_target"  , a_target);
   l = strlen (a_target);
   DEBUG_INPT   yLOG_value   ("l"         , l);
   --rce;  if (l < 3) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open the file)------------------*/
   rc = FILE__open ();
   DEBUG_INPT   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find target)--------------------*/
   DEBUG_INPT   yLOG_note    ("find target header");
   --rce;  while (1) {
      rc = FILE__read ();
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("could not find target");
         FILE__close ();
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (rc != 'h')  continue;
      rc = FILE__header (s_recd, x_title, &x_chime, x_desc);
      DEBUG_INPT   yLOG_value   ("header"    , rc);
      if (rc < 0)  {
         DEBUG_INPT   yLOG_note    ("bad header read, continue anyway");
         continue;
      }
      if (strcmp (x_title, a_target) != 0)  {
         DEBUG_INPT   yLOG_note    ("not a match");
         continue;
      }
      break;
   }
   /*---(import header)------------------*/
   DEBUG_INPT   yLOG_note    ("match found, import header");
   strlcpy (g_set.title, x_title, LEN_LABEL);
   g_set.chime = x_chime;
   strlcpy (g_set.desc , x_desc , LEN_HUND);
   /*---(import details)-----------------*/
   DEBUG_INPT   yLOG_note    ("import all details");
   --rce;  while (1) {
      rc = FILE__read ();
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0) {
         if (c <= 0) {
            DEBUG_INPT   yLOG_note    ("no details found");
            FILE__close ();
            FILE__purge ();
            DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         break;
      }
      if (rc != 'd') {
         DEBUG_INPT   yLOG_note    ("next header reached");
         if (c <= 0) {
            DEBUG_INPT   yLOG_note    ("no details found");
            FILE__close ();
            FILE__purge ();
            DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         break;
      }
      rc = FILE__detail (s_recd, &x_dur, x_title, x_desc);
      DEBUG_INPT   yLOG_value   ("detail"    , rc);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("detail line is corrupted");
         FILE__close ();
         FILE__purge ();
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_INPT   yLOG_note    ("adding detail");
      g_set.step [c].num = c + 1;
      strlcpy (g_set.step [c].terse, x_title, LEN_TERSE);
      strlcpy (g_set.step [c].desc , x_desc , LEN_DESC);
      g_set.step [c].dur = x_dur;
      ++c;
      g_set.max  = c;
      g_set.dur += x_dur;
   }
   DEBUG_INPT   yLOG_value   ("max"       , g_set.max);
   DEBUG_INPT   yLOG_value   ("dur"       , g_set.dur);
   /*---(calc the scale)------------------------*/
   g_set.scale  = ((float) my.win_w) / ((float) g_set.dur);
   /*---(close the file)------------------------*/
   rc = FILE__close ();
   DEBUG_INPT   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      FILE__purge ();
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare timing)------------------------*/
   my.beg  = my.cur = BASE_msec ();
   my.dur  = g_set.dur * 1000;
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}


