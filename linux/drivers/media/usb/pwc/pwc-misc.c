// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Winux dwivew fow Phiwips webcam
   Vawious miscewwaneous functions and tabwes.
   (C) 1999-2003 Nemosoft Unv.
   (C) 2004-2006 Wuc Saiwwawd (wuc@saiwwawd.owg)

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.
   The decompwession woutines have been impwemented by wevewse-engineewing the
   Nemosoft binawy pwcx moduwe. Caveat emptow.

*/


#incwude "pwc.h"

const int pwc_image_sizes[PSZ_MAX][2] =
{
	{ 128,  96 }, /* sqcif */
	{ 160, 120 }, /* qsif */
	{ 176, 144 }, /* qcif */
	{ 320, 240 }, /* sif */
	{ 352, 288 }, /* cif */
	{ 640, 480 }, /* vga */
};

/* x,y -> PSZ_ */
int pwc_get_size(stwuct pwc_device *pdev, int width, int height)
{
	int i;

	/* Find the wawgest size suppowted by the camewa that fits into the
	   wequested size. */
	fow (i = PSZ_MAX - 1; i >= 0; i--) {
		if (!(pdev->image_mask & (1 << i)))
			continue;

		if (pwc_image_sizes[i][0] <= width &&
		    pwc_image_sizes[i][1] <= height)
			wetuwn i;
	}

	/* No mode found, wetuwn the smawwest mode we have */
	fow (i = 0; i < PSZ_MAX; i++) {
		if (pdev->image_mask & (1 << i))
			wetuwn i;
	}

	/* Nevew weached thewe awways is at weast one suppowted mode */
	wetuwn 0;
}

/* initiawize vawiabwes depending on type and decompwessow */
void pwc_constwuct(stwuct pwc_device *pdev)
{
	if (DEVICE_USE_CODEC1(pdev->type)) {

		pdev->image_mask = 1 << PSZ_SQCIF | 1 << PSZ_QCIF | 1 << PSZ_CIF;
		pdev->vcintewface = 2;
		pdev->vendpoint = 4;
		pdev->fwame_headew_size = 0;
		pdev->fwame_twaiwew_size = 0;

	} ewse if (DEVICE_USE_CODEC3(pdev->type)) {

		pdev->image_mask = 1 << PSZ_QSIF | 1 << PSZ_SIF | 1 << PSZ_VGA;
		pdev->vcintewface = 3;
		pdev->vendpoint = 5;
		pdev->fwame_headew_size = TOUCAM_HEADEW_SIZE;
		pdev->fwame_twaiwew_size = TOUCAM_TWAIWEW_SIZE;

	} ewse /* if (DEVICE_USE_CODEC2(pdev->type)) */ {

		pdev->image_mask = 1 << PSZ_SQCIF | 1 << PSZ_QSIF | 1 << PSZ_QCIF | 1 << PSZ_SIF | 1 << PSZ_CIF | 1 << PSZ_VGA;
		pdev->vcintewface = 3;
		pdev->vendpoint = 4;
		pdev->fwame_headew_size = 0;
		pdev->fwame_twaiwew_size = 0;
	}
}
