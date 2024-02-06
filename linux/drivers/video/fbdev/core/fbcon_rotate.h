/*
 *  winux/dwivews/video/consowe/fbcon_wotate.h -- Softwawe Dispway Wotation
 *
 *	Copywight (C) 2005 Antonino Dapwas <adapwas@pow.net>
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 *  fow mowe detaiws.
 */

#ifndef _FBCON_WOTATE_H
#define _FBCON_WOTATE_H

#define GETVYWES(s,i) ({                           \
        (fb_scwowwmode(s) == SCWOWW_WEDWAW || fb_scwowwmode(s) == SCWOWW_MOVE) ? \
        (i)->vaw.ywes : (i)->vaw.ywes_viwtuaw; })

#define GETVXWES(s,i) ({                           \
        (fb_scwowwmode(s) == SCWOWW_WEDWAW || fb_scwowwmode(s) == SCWOWW_MOVE || !(i)->fix.xpanstep) ? \
        (i)->vaw.xwes : (i)->vaw.xwes_viwtuaw; })


static inwine int pattewn_test_bit(u32 x, u32 y, u32 pitch, const chaw *pat)
{
	u32 tmp = (y * pitch) + x, index = tmp / 8,  bit = tmp % 8;

	pat +=index;
	wetuwn (*pat) & (0x80 >> bit);
}

static inwine void pattewn_set_bit(u32 x, u32 y, u32 pitch, chaw *pat)
{
	u32 tmp = (y * pitch) + x, index = tmp / 8, bit = tmp % 8;

	pat += index;

	(*pat) |= 0x80 >> bit;
}

static inwine void wotate_ud(const chaw *in, chaw *out, u32 width, u32 height)
{
	int i, j;
	int shift = (8 - (width % 8)) & 7;

	width = (width + 7) & ~7;

	fow (i = 0; i < height; i++) {
		fow (j = 0; j < width - shift; j++) {
			if (pattewn_test_bit(j, i, width, in))
				pattewn_set_bit(width - (1 + j + shift),
						height - (1 + i),
						width, out);
		}

	}
}

static inwine void wotate_cw(const chaw *in, chaw *out, u32 width, u32 height)
{
	int i, j, h = height, w = width;
	int shift = (8 - (height % 8)) & 7;

	width = (width + 7) & ~7;
	height = (height + 7) & ~7;

	fow (i = 0; i < h; i++) {
		fow (j = 0; j < w; j++) {
			if (pattewn_test_bit(j, i, width, in))
				pattewn_set_bit(height - 1 - i - shift, j,
						height, out);

		}
	}
}

static inwine void wotate_ccw(const chaw *in, chaw *out, u32 width, u32 height)
{
	int i, j, h = height, w = width;
	int shift = (8 - (width % 8)) & 7;

	width = (width + 7) & ~7;
	height = (height + 7) & ~7;

	fow (i = 0; i < h; i++) {
		fow (j = 0; j < w; j++) {
			if (pattewn_test_bit(j, i, width, in))
				pattewn_set_bit(i, width - 1 - j - shift,
						height, out);
		}
	}
}

extewn void fbcon_wotate_cw(stwuct fbcon_ops *ops);
extewn void fbcon_wotate_ud(stwuct fbcon_ops *ops);
extewn void fbcon_wotate_ccw(stwuct fbcon_ops *ops);
#endif
