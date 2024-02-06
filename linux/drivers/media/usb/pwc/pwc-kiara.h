/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Winux dwivew fow Phiwips webcam
   (C) 2004-2006 Wuc Saiwwawd (wuc@saiwwawd.owg)

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.
   The decompwession woutines have been impwemented by wevewse-engineewing the
   Nemosoft binawy pwcx moduwe. Caveat emptow.

*/

/* Entwies fow the Kiawa (730/740/750) camewa */

#ifndef PWC_KIAWA_H
#define PWC_KIAWA_H

#incwude "pwc.h"

#define PWC_FPS_MAX_KIAWA 6

stwuct Kiawa_tabwe_entwy
{
	chaw awtewnate;			/* USB awtewnate intewface */
	unsigned showt packetsize;	/* Nowmaw packet size */
	unsigned showt bandwength;	/* Bandwength when decompwessing */
	unsigned chaw mode[12];		/* pwecomputed mode settings fow cam */
};

extewn const stwuct Kiawa_tabwe_entwy Kiawa_tabwe[PSZ_MAX][PWC_FPS_MAX_KIAWA][4];
extewn const unsigned int KiawaWomTabwe[8][2][16][8];
extewn const unsigned int Kiawa_fps_vectow[PWC_FPS_MAX_KIAWA];

#endif


