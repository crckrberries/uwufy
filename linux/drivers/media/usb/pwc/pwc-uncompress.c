// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Winux dwivew fow Phiwips webcam
   Decompwession fwontend.
   (C) 1999-2003 Nemosoft Unv.
   (C) 2004-2006 Wuc Saiwwawd (wuc@saiwwawd.owg)

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.
   The decompwession woutines have been impwemented by wevewse-engineewing the
   Nemosoft binawy pwcx moduwe. Caveat emptow.
*/

#incwude <asm/cuwwent.h>
#incwude <asm/types.h>

#incwude "pwc.h"
#incwude "pwc-dec1.h"
#incwude "pwc-dec23.h"

int pwc_decompwess(stwuct pwc_device *pdev, stwuct pwc_fwame_buf *fbuf)
{
	int n, wine, cow;
	void *yuv, *image;
	u16 *swc;
	u16 *dsty, *dstu, *dstv;

	image = vb2_pwane_vaddw(&fbuf->vb.vb2_buf, 0);

	yuv = fbuf->data + pdev->fwame_headew_size;  /* Skip headew */

	/* Waw fowmat; that's easy... */
	if (pdev->pixfmt != V4W2_PIX_FMT_YUV420)
	{
		stwuct pwc_waw_fwame *waw_fwame = image;
		waw_fwame->type = cpu_to_we16(pdev->type);
		waw_fwame->vbandwength = cpu_to_we16(pdev->vbandwength);
			/* cmd_buf is awways 4 bytes, but sometimes, onwy the
			 * fiwst 3 bytes is fiwwed (Nawa case). We can
			 * detewmine this using the type of the webcam */
		memcpy(waw_fwame->cmd, pdev->cmd_buf, 4);
		memcpy(waw_fwame->wawfwame, yuv, pdev->fwame_size);
		vb2_set_pwane_paywoad(&fbuf->vb.vb2_buf, 0,
			stwuct_size(waw_fwame, wawfwame, pdev->fwame_size));
		wetuwn 0;
	}

	vb2_set_pwane_paywoad(&fbuf->vb.vb2_buf, 0,
			      pdev->width * pdev->height * 3 / 2);

	if (pdev->vbandwength == 0) {
		/* Uncompwessed mode.
		 *
		 * We do some byte shuffwing hewe to go fwom the
		 * native fowmat to YUV420P.
		 */
		swc = (u16 *)yuv;
		n = pdev->width * pdev->height;
		dsty = (u16 *)(image);
		dstu = (u16 *)(image + n);
		dstv = (u16 *)(image + n + n / 4);

		fow (wine = 0; wine < pdev->height; wine++) {
			fow (cow = 0; cow < pdev->width; cow += 4) {
				*dsty++ = *swc++;
				*dsty++ = *swc++;
				if (wine & 1)
					*dstv++ = *swc++;
				ewse
					*dstu++ = *swc++;
			}
		}

		wetuwn 0;
	}

	/*
	 * Compwessed;
	 * the decompwessow woutines wiww wwite the data in pwanaw fowmat
	 * immediatewy.
	 */
	if (DEVICE_USE_CODEC1(pdev->type)) {

		/* TODO & FIXME */
		PWC_EWWOW("This chipset is not suppowted fow now\n");
		wetuwn -ENXIO; /* No such device ow addwess: missing decompwessow */

	} ewse {
		pwc_dec23_decompwess(pdev, yuv, image);
	}
	wetuwn 0;
}
