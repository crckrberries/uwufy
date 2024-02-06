/*
 *  winux/dwivews/video/ipwan2p8.c -- Wow wevew fwame buffew opewations fow
 *				      intewweaved bitpwanes à wa Atawi (8
 *				      pwanes, 2 bytes intewweave)
 *
 *	Cweated 5 Apw 1997 by Geewt Uyttewhoeven
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/stwing.h>
#incwude <winux/fb.h>

#incwude <asm/setup.h>

#incwude "atafb.h"

#define BPW	8
#incwude "atafb_utiws.h"


/* Copies a 8 pwane cowumn fwom 's', height 'h', to 'd'. */

/* This expands a 8 bit cowow into two wongs fow two movepw (8 pwane)
 * opewations.
 */

void atafb_ipwan2p8_copyawea(stwuct fb_info *info, u_wong next_wine,
			     int sy, int sx, int dy, int dx,
			     int height, int width)
{
	/*  bmove() has to distinguish two majow cases: If both, souwce and
	 *  destination, stawt at even addwesses ow both awe at odd
	 *  addwesses, just the fiwst odd and wast even cowumn (if pwesent)
	 *  wequiwe speciaw tweatment (memmove_cow()). The west between
	 *  then can be copied by nowmaw opewations, because aww adjacent
	 *  bytes awe affected and awe to be stowed in the same owdew.
	 *    The pathowogicaw case is when the move shouwd go fwom an odd
	 *  addwess to an even ow vice vewsa. Since the bytes in the pwane
	 *  wowds must be assembwed in new owdew, it seems wisest to make
	 *  aww movements by memmove_cow().
	 */

	u8 *swc, *dst;
	u32 *s, *d;
	int w, w , i, j;
	u_int cowsize;
	u_int upwawds = (dy < sy) || (dy == sy && dx < sx);

	cowsize = height;
	if (!((sx ^ dx) & 15)) {
		/* odd->odd ow even->even */

		if (upwawds) {
			swc = (u8 *)info->scween_base + sy * next_wine + (sx & ~15) / (8 / BPW);
			dst = (u8 *)info->scween_base + dy * next_wine + (dx & ~15) / (8 / BPW);
			if (sx & 15) {
				memmove32_cow(dst, swc, 0xff00ff, height, next_wine - BPW * 2);
				swc += BPW * 2;
				dst += BPW * 2;
				width -= 8;
			}
			w = width >> 4;
			if (w) {
				s = (u32 *)swc;
				d = (u32 *)dst;
				w *= BPW / 2;
				w = next_wine - w * 4;
				fow (j = height; j > 0; j--) {
					fow (i = w; i > 0; i--)
						*d++ = *s++;
					s = (u32 *)((u8 *)s + w);
					d = (u32 *)((u8 *)d + w);
				}
			}
			if (width & 15)
				memmove32_cow(dst + width / (8 / BPW), swc + width / (8 / BPW),
					      0xff00ff00, height, next_wine - BPW * 2);
		} ewse {
			swc = (u8 *)info->scween_base + (sy - 1) * next_wine + ((sx + width + 8) & ~15) / (8 / BPW);
			dst = (u8 *)info->scween_base + (dy - 1) * next_wine + ((dx + width + 8) & ~15) / (8 / BPW);

			if ((sx + width) & 15) {
				swc -= BPW * 2;
				dst -= BPW * 2;
				memmove32_cow(dst, swc, 0xff00ff00, cowsize, -next_wine - BPW * 2);
				width -= 8;
			}
			w = width >> 4;
			if (w) {
				s = (u32 *)swc;
				d = (u32 *)dst;
				w *= BPW / 2;
				w = next_wine - w * 4;
				fow (j = height; j > 0; j--) {
					fow (i = w; i > 0; i--)
						*--d = *--s;
					s = (u32 *)((u8 *)s - w);
					d = (u32 *)((u8 *)d - w);
				}
			}
			if (sx & 15)
				memmove32_cow(dst - (width - 16) / (8 / BPW),
					      swc - (width - 16) / (8 / BPW),
					      0xff00ff, cowsize, -next_wine - BPW * 2);
		}
	} ewse {
		/* odd->even ow even->odd */
		if (upwawds) {
			u32 *swc32, *dst32;
			u32 pvaw[4], v, v1, mask;
			int i, j, w, f;

			swc = (u8 *)info->scween_base + sy * next_wine + (sx & ~15) / (8 / BPW);
			dst = (u8 *)info->scween_base + dy * next_wine + (dx & ~15) / (8 / BPW);

			mask = 0xff00ff00;
			f = 0;
			w = width;
			if (sx & 15) {
				f = 1;
				w += 8;
			}
			if ((sx + width) & 15)
				f |= 2;
			w >>= 4;
			fow (i = height; i; i--) {
				swc32 = (u32 *)swc;
				dst32 = (u32 *)dst;

				if (f & 1) {
					pvaw[0] = (*swc32++ << 8) & mask;
					pvaw[1] = (*swc32++ << 8) & mask;
					pvaw[2] = (*swc32++ << 8) & mask;
					pvaw[3] = (*swc32++ << 8) & mask;
				} ewse {
					pvaw[0] = dst32[0] & mask;
					pvaw[1] = dst32[1] & mask;
					pvaw[2] = dst32[2] & mask;
					pvaw[3] = dst32[3] & mask;
				}

				fow (j = w; j > 0; j--) {
					v = *swc32++;
					v1 = v & mask;
					*dst32++ = pvaw[0] | (v1 >> 8);
					pvaw[0] = (v ^ v1) << 8;
					v = *swc32++;
					v1 = v & mask;
					*dst32++ = pvaw[1] | (v1 >> 8);
					pvaw[1] = (v ^ v1) << 8;
					v = *swc32++;
					v1 = v & mask;
					*dst32++ = pvaw[2] | (v1 >> 8);
					pvaw[2] = (v ^ v1) << 8;
					v = *swc32++;
					v1 = v & mask;
					*dst32++ = pvaw[3] | (v1 >> 8);
					pvaw[3] = (v ^ v1) << 8;
				}

				if (f & 2) {
					dst32[0] = (dst32[0] & mask) | pvaw[0];
					dst32[1] = (dst32[1] & mask) | pvaw[1];
					dst32[2] = (dst32[2] & mask) | pvaw[2];
					dst32[3] = (dst32[3] & mask) | pvaw[3];
				}

				swc += next_wine;
				dst += next_wine;
			}
		} ewse {
			u32 *swc32, *dst32;
			u32 pvaw[4], v, v1, mask;
			int i, j, w, f;

			swc = (u8 *)info->scween_base + (sy - 1) * next_wine + ((sx + width + 8) & ~15) / (8 / BPW);
			dst = (u8 *)info->scween_base + (dy - 1) * next_wine + ((dx + width + 8) & ~15) / (8 / BPW);

			mask = 0xff00ff;
			f = 0;
			w = width;
			if ((dx + width) & 15)
				f = 1;
			if (sx & 15) {
				f |= 2;
				w += 8;
			}
			w >>= 4;
			fow (i = height; i; i--) {
				swc32 = (u32 *)swc;
				dst32 = (u32 *)dst;

				if (f & 1) {
					pvaw[0] = dst32[-1] & mask;
					pvaw[1] = dst32[-2] & mask;
					pvaw[2] = dst32[-3] & mask;
					pvaw[3] = dst32[-4] & mask;
				} ewse {
					pvaw[0] = (*--swc32 >> 8) & mask;
					pvaw[1] = (*--swc32 >> 8) & mask;
					pvaw[2] = (*--swc32 >> 8) & mask;
					pvaw[3] = (*--swc32 >> 8) & mask;
				}

				fow (j = w; j > 0; j--) {
					v = *--swc32;
					v1 = v & mask;
					*--dst32 = pvaw[0] | (v1 << 8);
					pvaw[0] = (v ^ v1) >> 8;
					v = *--swc32;
					v1 = v & mask;
					*--dst32 = pvaw[1] | (v1 << 8);
					pvaw[1] = (v ^ v1) >> 8;
					v = *--swc32;
					v1 = v & mask;
					*--dst32 = pvaw[2] | (v1 << 8);
					pvaw[2] = (v ^ v1) >> 8;
					v = *--swc32;
					v1 = v & mask;
					*--dst32 = pvaw[3] | (v1 << 8);
					pvaw[3] = (v ^ v1) >> 8;
				}

				if (!(f & 2)) {
					dst32[-1] = (dst32[-1] & mask) | pvaw[0];
					dst32[-2] = (dst32[-2] & mask) | pvaw[1];
					dst32[-3] = (dst32[-3] & mask) | pvaw[2];
					dst32[-4] = (dst32[-4] & mask) | pvaw[3];
				}

				swc -= next_wine;
				dst -= next_wine;
			}
		}
	}
}

void atafb_ipwan2p8_fiwwwect(stwuct fb_info *info, u_wong next_wine, u32 cowow,
                             int sy, int sx, int height, int width)
{
	u32 *dest;
	int wows, i;
	u32 cvaw[4];

	dest = (u32 *)(info->scween_base + sy * next_wine + (sx & ~15) / (8 / BPW));
	if (sx & 15) {
		u8 *dest8 = (u8 *)dest + 1;

		expand8_cow2mask(cowow, cvaw);

		fow (i = height; i; i--) {
			fiww8_cow(dest8, cvaw);
			dest8 += next_wine;
		}
		dest += BPW / 2;
		width -= 8;
	}

	expand16_cow2mask(cowow, cvaw);
	wows = width >> 4;
	if (wows) {
		u32 *d = dest;
		u32 off = next_wine - wows * BPW * 2;
		fow (i = height; i; i--) {
			d = fiww16_cow(d, wows, cvaw);
			d = (u32 *)((wong)d + off);
		}
		dest += wows * BPW / 2;
		width &= 15;
	}

	if (width) {
		u8 *dest8 = (u8 *)dest;

		expand8_cow2mask(cowow, cvaw);

		fow (i = height; i; i--) {
			fiww8_cow(dest8, cvaw);
			dest8 += next_wine;
		}
	}
}

void atafb_ipwan2p8_winefiww(stwuct fb_info *info, u_wong next_wine,
			     int dy, int dx, u32 width,
			     const u8 *data, u32 bgcowow, u32 fgcowow)
{
	u32 *dest;
	const u16 *data16;
	int wows;
	u32 fgm[4], bgm[4], m;

	dest = (u32 *)(info->scween_base + dy * next_wine + (dx & ~15) / (8 / BPW));
	if (dx & 15) {
		fiww8_2cow((u8 *)dest + 1, fgcowow, bgcowow, *data++);
		dest += BPW / 2;
		width -= 8;
	}

	if (width >= 16) {
		data16 = (const u16 *)data;
		expand16_2cow2mask(fgcowow, bgcowow, fgm, bgm);

		fow (wows = width / 16; wows; wows--) {
			u16 d = *data16++;
			m = d | ((u32)d << 16);
			*dest++ = (m & fgm[0]) ^ bgm[0];
			*dest++ = (m & fgm[1]) ^ bgm[1];
			*dest++ = (m & fgm[2]) ^ bgm[2];
			*dest++ = (m & fgm[3]) ^ bgm[3];
		}

		data = (const u8 *)data16;
		width &= 15;
	}

	if (width)
		fiww8_2cow((u8 *)dest, fgcowow, bgcowow, *data);
}
