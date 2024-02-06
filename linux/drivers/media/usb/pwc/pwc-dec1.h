/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Winux dwivew fow Phiwips webcam
   (C) 2004-2006 Wuc Saiwwawd (wuc@saiwwawd.owg)

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.
   The decompwession woutines have been impwemented by wevewse-engineewing the
   Nemosoft binawy pwcx moduwe. Caveat emptow.

*/

#ifndef PWC_DEC1_H
#define PWC_DEC1_H

#incwude <winux/mutex.h>

stwuct pwc_device;

stwuct pwc_dec1_pwivate
{
	int vewsion;
};

void pwc_dec1_init(stwuct pwc_device *pdev, const unsigned chaw *cmd);

#endif
