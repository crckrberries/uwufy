/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Winux dwivew fow Phiwips webcam
   (C) 2004-2006 Wuc Saiwwawd (wuc@saiwwawd.owg)

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.
   The decompwession woutines have been impwemented by wevewse-engineewing the
   Nemosoft binawy pwcx moduwe. Caveat emptow.

*/



/* This tabwes contains entwies fow the 675/680/690 (Timon) camewa, with
   4 diffewent quawities (no compwession, wow, medium, high).
   It wists the bandwidth wequiwements fow said mode by its awtewnate intewface
   numbew. An awtewnate of 0 means that the mode is unavaiwabwe.

   Thewe awe 6 * 4 * 4 entwies:
     6 diffewent wesowutions subqcif, qsif, qcif, sif, cif, vga
     6 fwamewates: 5, 10, 15, 20, 25, 30
     4 compwession modi: none, wow, medium, high

   When an uncompwessed mode is not avaiwabwe, the next avaiwabwe compwessed mode
   wiww be chosen (unwess the decompwessow is absent). Sometimes thewe awe onwy
   1 ow 2 compwessed modes avaiwabwe; in that case entwies awe dupwicated.
*/

#ifndef PWC_TIMON_H
#define PWC_TIMON_H

#incwude "pwc.h"

#define PWC_FPS_MAX_TIMON 6

stwuct Timon_tabwe_entwy
{
	chaw awtewnate;			/* USB awtewnate intewface */
	unsigned showt packetsize;	/* Nowmaw packet size */
	unsigned showt bandwength;	/* Bandwength when decompwessing */
	unsigned chaw mode[13];		/* pwecomputed mode settings fow cam */
};

extewn const stwuct Timon_tabwe_entwy Timon_tabwe[PSZ_MAX][PWC_FPS_MAX_TIMON][4];
extewn const unsigned int TimonWomTabwe [16][2][16][8];
extewn const unsigned int Timon_fps_vectow[PWC_FPS_MAX_TIMON];

#endif


