/*============================----beg-of-source---============================*/
#include   "pacer.h"



static char      s_face     [LEN_DESC] = "shrike";
static int       s_font     = -1;

static uint      s_tex      = 0;
static uint      s_fbo      = 0;
static uint      s_depth    = 0;
static float     s_per      = 0.0;


/*====================------------------------------------====================*/
/*===----                             fonts                            ----===*/
/*====================------------------------------------====================*/
static void      o___FONT____________________o (void) {;}

char
FONT_load           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(load)---------------------------*/
   DEBUG_GRAF   yLOG_info    ("s_face"    , s_face);
   s_font = yFONT_load (s_face);
   DEBUG_GRAF   yLOG_value   ("s_font"    , s_font);
   --rce;  if (s_font < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FONT_free           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(free)---------------------------*/
   DEBUG_GRAF   yLOG_info    ("s_face"    , s_face);
   rc = yFONT_free (s_font);
   DEBUG_GRAF   yLOG_value   ("free"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   s_font = -1;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}


char         /*-> tbd --------------------------------[ shoot  [gz.742.001.01]*/ /*-[00.0000.112.!]-*/ /*-[--.---.---.--]-*/
DRAW_init            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(globals)------------------------*/
   s_tex   = 0;
   s_fbo   = 0;
   s_depth = 0;
   /*---(window)-------------------------*/
   rc = yVIEW_full    (YVIEW_MAIN , YVIEW_FLAT, YVIEW_BOTLEF, YCOLOR_BAS, YCOLOR_MED, DRAW_primary);
   /*---(colors)-------------------------*/
   yCOLOR_palette (315, "rana" , "pastel", "warm");
   /*---(custom drawing)-----------------*/
   FONT_load      ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_wrap            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(globals)------------------------*/
   FONT_free    ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW__timing            (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(usec)---------------------------*/
   my.cur = BASE_msec ();
   my.dif  = my.cur - my.beg;
   my.prg  = ((float) my.dif) / ((float) my.dur);
   DEBUG_GRAF   yLOG_complex ("timing"    , "%20lld, %20lld, %20lld, %20lld, %5.3f", my.dur, my.beg, my.cur, my.dif, my.prg);
   /*---(seconds)------------------------*/
   if (g_set.beg == 0)  g_set.beg = time (NULL);
   g_set.cur = time (NULL) - g_set.beg;
   if (g_set.cur < 0)  g_set.cur = 0;
   if (g_set.cur > g_set.dur)  g_set.cur = g_set.dur;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW__background        (float z)
{
   /*---(locals)-----------+-----+-----+-*/
   float       xb, xe;
   int         i           =    0;
   char        t           [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   xb = 0.0;
   for (i = 0; i < g_set.max; ++i) {
      xe = xb + (g_set.step [i].dur * g_set.scale);
      switch (i % 2) {
      case 0 : yCOLOR_opengl (YCOLOR_BAS, YCOLOR_LIG, 0.7); break;
      case 1 : yCOLOR_opengl (YCOLOR_BAS, YCOLOR_MED, 0.7); break;
      }
      glBegin(GL_POLYGON); {
         glVertex3f (xb, 50.0,  z);
         glVertex3f (xe, 50.0,  z);
         glVertex3f (xe,  0.0,  z);
         glVertex3f (xb,  0.0,  z);
      } glEnd();
      /*> glPushMatrix (); {                                                          <* 
       *>    glTranslatef (xb + ((xe - xb) / 2.0), 20.0, z + 5);                      <* 
       *>    yCOLOR_opengl (YCOLOR_BAS, YCOLOR_MIN, 1.0);                             <* 
       *>    sprintf (t, "%s", g_set.step [i].terse);                                 <* 
       *>    yFONT_print (s_font,  8, YF_MIDCEN, t);                                  <* 
       *>    glTranslatef (0.0, -10.0, 0);                                            <* 
       *>    sprintf (t, "%s", g_set.step [i].desc);                                  <* 
       *>    yFONT_print (s_font,  8, YF_MIDCEN, t);                                  <* 
       *> } glPopMatrix ();                                                           <*/
      xb = xe;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW__hatching          (float z)
{
   /*---(locals)-----------+-----+-----+-*/
   float       x           =  0.0;
   int         i           =    0;
   char        t           [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_value   ("chime"     , g_set.chime);
   if (g_set.chime <= 0) {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   yCOLOR_opengl (YCOLOR_BAS, YCOLOR_MAX, 0.4);
   glEnable      (GL_LINE_STIPPLE);
   glLineStipple (1, 0x5555);
   glLineWidth (2.0);
   for (i = 0; i < g_set.dur; i += g_set.chime) {
      x = i * g_set.scale;
      glBegin(GL_LINES); {
         glVertex3f (x, 30.0,  z);
         glVertex3f (x,  0.0,  z);
      } glEnd();
   }
   glDisable     (GL_LINE_STIPPLE);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW__progress          (float z)
{
   /*---(locals)-----------+-----+-----+-*/
   float       xb, xe;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(full progress background)-------*/
   xb = 0.0;
   xe = my.win_w;
   yCOLOR_opengl (YCOLOR_COM, YCOLOR_DRK, 1.0);
   glBegin(GL_POLYGON); {
      glVertex3f (xb, 40.0,  z);
      glVertex3f (xe, 40.0,  z);
      glVertex3f (xe, 25.0,  z);
      glVertex3f (xb, 25.0,  z);
   } glEnd();
   /*---(current progress)---------------*/
   z += 5;
   xb = 0.0;
   xe = my.prg * my.win_w;
   yCOLOR_opengl (YCOLOR_COM, YCOLOR_MOR, 1.0);
   glBegin(GL_POLYGON); {
      glVertex3f (xb, 40.0,  z);
      glVertex3f (xe, 40.0,  z);
      glVertex3f (xe, 25.0,  z);
      glVertex3f (xb, 25.0,  z);
   } glEnd();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW__steps             (float z)
{
   /*---(locals)-----------+-----+-----+-*/
   float       xb, xe;
   int         i           =    0;
   char        t           [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   xb = 0.0;
   for (i = 0; i < g_set.max; ++i) {
      xe = xb + (g_set.step [i].dur * g_set.scale);
      glPushMatrix (); {
         glTranslatef (xb + ((xe - xb) / 2.0), 20.0, z + 5);
         yCOLOR_opengl (YCOLOR_BAS, YCOLOR_MIN, 1.0);
         sprintf (t, "%s", g_set.step [i].terse);
         yFONT_print (s_font,  8, YF_MIDCEN, t);
         glTranslatef (0.0, -10.0, 0);
         sprintf (t, "%s", g_set.step [i].desc);
         yFONT_print (s_font,  8, YF_MIDCEN, t);
      } glPopMatrix ();
      xb = xe;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW__labels            (float z)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD]  = "";
   int         x_dur       =    0;
   char        u           =  's';
   char        s           [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(main title)---------------------*/
   glPushMatrix (); {
      glTranslatef (my.win_w / 2.0, 30.0, z);
      yCOLOR_opengl (YCOLOR_BAS, YCOLOR_ACC, 1.0);
      sprintf (t, "%s, %s", g_set.title, g_set.desc);
      yFONT_print (s_font,  8, YF_TOPCEN, t);
   } glPopMatrix ();
   /*---(current time)-------------------*/
   glPushMatrix (); {
      glTranslatef (5.0, 30.0, z);
      yCOLOR_opengl (YCOLOR_BAS, YCOLOR_MAX, 1.0);
      x_dur = g_set.cur;
      u     = 's';
      if (x_dur >= 60) {
         u = 'm';
         x_dur /= 60;
         if (x_dur >= 60) {
            u = 'h';
            x_dur /= 60;
         }
      }
      strl4comma (g_set.cur, s, 0, ',', '-', LEN_LABEL);
      /*> sprintf (t, "%d%c (%ss)", x_dur, u, s);                                     <*/
      sprintf (t, "%5.1f (%ss)", my.prg * 100, s);
      yFONT_print (s_font,  8, YF_TOPLEF, t);
   } glPopMatrix ();
   /*---(final duration)-----------------*/
   glPushMatrix (); {
      glTranslatef (my.win_w - 5.0, 30.0, z);
      yCOLOR_opengl (YCOLOR_BAS, YCOLOR_MAX, 1.0);
      x_dur = g_set.dur;
      u     = 's';
      if (x_dur >= 60) {
         u = 'm';
         x_dur /= 60;
         if (x_dur >= 60) {
            u = 'h';
            x_dur /= 60;
         }
      }
      strl4comma (g_set.dur, s, 0, ',', '-', LEN_LABEL);
      sprintf (t, "%d%c (%ss)", x_dur, u, s);
      yFONT_print (s_font,  8, YF_TOPRIG, t);
   } glPopMatrix ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /* PURPOSE : place the texture in the window ----------------------*/
DRAW_primary       (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(update time)--------------------*/
   DRAW__timing      ();
   DRAW__background (10);
   DRAW__hatching   (20);
   DRAW__progress   (30);
   DRAW__steps      (40);
   DRAW__labels     (50);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

