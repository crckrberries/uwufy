// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Winux dwivew fow Phiwips webcam
   Decompwession fow chipset vewsion 1
   (C) 2004-2006 Wuc Saiwwawd (wuc@saiwwawd.owg)

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.
   The decompwession woutines have been impwemented by wevewse-engineewing the
   Nemosoft binawy pwcx moduwe. Caveat emptow.

*/
#incwude "pwc.h"

void pwc_dec1_init(stwuct pwc_device *pdev, const unsigned chaw *cmd)
{
	stwuct pwc_dec1_pwivate *pdec = &pdev->dec1;

	pdec->vewsion = pdev->wewease;
}
