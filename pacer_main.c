/*============================----beg-of-source---============================*/
#include   "pacer.h"


char
main                    (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(debugging)----------------------*/
   rc = PROG_urgents (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("urgents"   , rc);
   if (rc <  0) { PROG_shutdown (); return -1; }
   /*---(initialization)-----------------*/
   rc = PROG_startup (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("startup"   , rc);
   if (rc <  0) { PROG_shutdown (); return -2; }
   /*---(read)----------------------------------*/
   rc = FILE_import (my.target);
   DEBUG_PROG   yLOG_value    ("import"    , rc);
   if (rc <  0) { PROG_shutdown (); return -3; }
   /*---(main)----------------------------------*/
   rc = PROG_dawn    ();
   DEBUG_PROG   yLOG_value    ("dawn"      , rc);
   if (rc <  0) { PROG_shutdown (); return -4; }
   rc = yVIOPENGL_main ("10ms", "100ms", NULL);
   DEBUG_PROG   yLOG_value    ("main"      , rc);
   rc = PROG_dusk     ();
   DEBUG_PROG   yLOG_value    ("dusk"      , rc);
   /*---(wrap-up)------------------------*/
   rc = PROG_shutdown ();
   DEBUG_PROG   yLOG_value    ("shutdown"  , rc);
   /*---(complete)------------------------------*/
   return rc;
}
