/*============================----beg-of-source---============================*/
#include   "pacer.h"



char      unit_answer [LEN_RECD];



/*============================--------------------============================*/
/*===----                         unit testing                         ----===*/
/*============================--------------------============================*/
void o___UNITTEST_______________o (void) {;}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.#]-*/ /*-[--.---.---.--]-*/
PROG__unit_quiet    (void)
{
   char        x_narg  = 1;
   char       *x_args [1]  = { "pacer" };
   PROG_urgents (x_narg, x_args);
   PROG_startup (x_narg, x_args);
   return 0;
}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
PROG__unit_loud     (void)
{
   char        x_narg  = 2;
   char       *x_args [2]  = { "pacer_unit", "@@kitchen"    };
   PROG_urgents (x_narg, x_args);
   PROG_startup (x_narg, x_args);
   return 0;
}

char         /*-> set up program urgents/debugging ---[ light  [uz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
PROG__unit_end      (void)
{
   PROG_shutdown  ();
   return 0;
}

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
PROG__unit              (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   char        s           [LEN_RECD] = "[]";
   char        r           [LEN_RECD] = "[]";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "PROG unit        : question unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "header"    )     == 0) {
      if (strlen (g_set.title) < 1) {
         snprintf (unit_answer, LEN_RECD, "PROG header      :  ·  ·                ·                                    ·");
      } else {
         sprintf (s, "%2då%.12sæ", strlen (g_set.title), g_set.title);
         if (strlen (g_set.desc ) < 1)   sprintf (t, " ·");
         else                            sprintf (t, "%2då%.30sæ", strlen (g_set.desc ), g_set.desc);
         snprintf (unit_answer, LEN_RECD, "PROG header      : %2d %-16.16s %-34.34s %4d %6.2f", g_set.max, s, t, g_set.dur, g_set.scale);
      }
   }
   else if (strcmp (a_question, "detail"    )     == 0) {
      if (strlen (g_set.step [i].terse) < 1) {
         snprintf (unit_answer, LEN_RECD, "PROG detail (%2d) :  ·  ·                ·                                    ·", i);
      } else {
         sprintf (s, "%2då%.12sæ", strlen (g_set.step [i].terse), g_set.step [i].terse);
         if (strlen (g_set.desc ) < 1)   sprintf (t, " ·");
         else                            sprintf (t, "%2då%.30sæ", strlen (g_set.step [i].desc ), g_set.step [i].desc);
         snprintf (unit_answer, LEN_RECD, "PROG detail (%2d) : %2d %-16.16s %-34.34s %4d", i, g_set.step [i].num, s, t, g_set.step [i].dur);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
