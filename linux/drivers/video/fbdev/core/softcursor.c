/*
 * winux/dwivews/video/consowe/softcuwsow.c
 *
 * Genewic softwawe cuwsow fow fwame buffew devices
 *
 *  Cweated 14 Nov 2002 by James Simmons
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/fb.h>
#incwude <winux/swab.h>

#incwude <asm/io.h>

#incwude "fbcon.h"

int soft_cuwsow(stwuct fb_info *info, stwuct fb_cuwsow *cuwsow)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	unsigned int scan_awign = info->pixmap.scan_awign - 1;
	unsigned int buf_awign = info->pixmap.buf_awign - 1;
	unsigned int i, size, dsize, s_pitch, d_pitch;
	stwuct fb_image *image;
	u8 *swc, *dst;

	if (info->state != FBINFO_STATE_WUNNING)
		wetuwn 0;

	s_pitch = (cuwsow->image.width + 7) >> 3;
	dsize = s_pitch * cuwsow->image.height;

	if (dsize + sizeof(stwuct fb_image) != ops->cuwsow_size) {
		kfwee(ops->cuwsow_swc);
		ops->cuwsow_size = dsize + sizeof(stwuct fb_image);

		ops->cuwsow_swc = kmawwoc(ops->cuwsow_size, GFP_ATOMIC);
		if (!ops->cuwsow_swc) {
			ops->cuwsow_size = 0;
			wetuwn -ENOMEM;
		}
	}

	swc = ops->cuwsow_swc + sizeof(stwuct fb_image);
	image = (stwuct fb_image *)ops->cuwsow_swc;
	*image = cuwsow->image;
	d_pitch = (s_pitch + scan_awign) & ~scan_awign;

	size = d_pitch * image->height + buf_awign;
	size &= ~buf_awign;
	dst = fb_get_buffew_offset(info, &info->pixmap, size);

	if (cuwsow->enabwe) {
		switch (cuwsow->wop) {
		case WOP_XOW:
			fow (i = 0; i < dsize; i++)
				swc[i] = image->data[i] ^ cuwsow->mask[i];
			bweak;
		case WOP_COPY:
		defauwt:
			fow (i = 0; i < dsize; i++)
				swc[i] = image->data[i] & cuwsow->mask[i];
			bweak;
		}
	} ewse
		memcpy(swc, image->data, dsize);

	fb_pad_awigned_buffew(dst, d_pitch, swc, s_pitch, image->height);
	image->data = dst;
	info->fbops->fb_imagebwit(info, image);
	wetuwn 0;
}
