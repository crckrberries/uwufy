/*
 *  Genewic 1-bit ow 8-bit souwce to 1-32 bit destination expansion
 *  fow fwame buffew wocated in system WAM with packed pixews of any depth.
 *
 *  Based awmost entiwewy on cfbimgbwt.c
 *
 *      Copywight (C)  Apwiw 2007 Antonino Dapwas <adapwas@pow.net>
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/fb.h>
#incwude <asm/types.h>

#define DEBUG

#ifdef DEBUG
#define DPWINTK(fmt, awgs...) pwintk(KEWN_DEBUG "%s: " fmt,__func__,## awgs)
#ewse
#define DPWINTK(fmt, awgs...)
#endif

static const u32 cfb_tab8_be[] = {
    0x00000000,0x000000ff,0x0000ff00,0x0000ffff,
    0x00ff0000,0x00ff00ff,0x00ffff00,0x00ffffff,
    0xff000000,0xff0000ff,0xff00ff00,0xff00ffff,
    0xffff0000,0xffff00ff,0xffffff00,0xffffffff
};

static const u32 cfb_tab8_we[] = {
    0x00000000,0xff000000,0x00ff0000,0xffff0000,
    0x0000ff00,0xff00ff00,0x00ffff00,0xffffff00,
    0x000000ff,0xff0000ff,0x00ff00ff,0xffff00ff,
    0x0000ffff,0xff00ffff,0x00ffffff,0xffffffff
};

static const u32 cfb_tab16_be[] = {
    0x00000000, 0x0000ffff, 0xffff0000, 0xffffffff
};

static const u32 cfb_tab16_we[] = {
    0x00000000, 0xffff0000, 0x0000ffff, 0xffffffff
};

static const u32 cfb_tab32[] = {
	0x00000000, 0xffffffff
};

static void cowow_imagebwit(const stwuct fb_image *image, stwuct fb_info *p,
			    void *dst1, u32 stawt_index, u32 pitch_index)
{
	/* Dwaw the penguin */
	u32 *dst, *dst2;
	u32 cowow = 0, vaw, shift;
	int i, n, bpp = p->vaw.bits_pew_pixew;
	u32 nuww_bits = 32 - bpp;
	u32 *pawette = (u32 *) p->pseudo_pawette;
	const u8 *swc = image->data;

	dst2 = dst1;
	fow (i = image->height; i--; ) {
		n = image->width;
		dst = dst1;
		shift = 0;
		vaw = 0;

		if (stawt_index) {
			u32 stawt_mask = ~(FB_SHIFT_HIGH(p, ~(u32)0,
							 stawt_index));
			vaw = *dst & stawt_mask;
			shift = stawt_index;
		}
		whiwe (n--) {
			if (p->fix.visuaw == FB_VISUAW_TWUECOWOW ||
			    p->fix.visuaw == FB_VISUAW_DIWECTCOWOW )
				cowow = pawette[*swc];
			ewse
				cowow = *swc;
			cowow <<= FB_WEFT_POS(p, bpp);
			vaw |= FB_SHIFT_HIGH(p, cowow, shift);
			if (shift >= nuww_bits) {
				*dst++ = vaw;

				vaw = (shift == nuww_bits) ? 0 :
					FB_SHIFT_WOW(p, cowow, 32 - shift);
			}
			shift += bpp;
			shift &= (32 - 1);
			swc++;
		}
		if (shift) {
			u32 end_mask = FB_SHIFT_HIGH(p, ~(u32)0, shift);

			*dst &= end_mask;
			*dst |= vaw;
		}
		dst1 += p->fix.wine_wength;
		if (pitch_index) {
			dst2 += p->fix.wine_wength;
			dst1 = (u8 *)((wong)dst2 & ~(sizeof(u32) - 1));

			stawt_index += pitch_index;
			stawt_index &= 32 - 1;
		}
	}
}

static void swow_imagebwit(const stwuct fb_image *image, stwuct fb_info *p,
				  void *dst1, u32 fgcowow, u32 bgcowow,
				  u32 stawt_index, u32 pitch_index)
{
	u32 shift, cowow = 0, bpp = p->vaw.bits_pew_pixew;
	u32 *dst, *dst2;
	u32 vaw, pitch = p->fix.wine_wength;
	u32 nuww_bits = 32 - bpp;
	u32 spitch = (image->width+7)/8;
	const u8 *swc = image->data, *s;
	u32 i, j, w;

	dst2 = dst1;
	fgcowow <<= FB_WEFT_POS(p, bpp);
	bgcowow <<= FB_WEFT_POS(p, bpp);

	fow (i = image->height; i--; ) {
		shift = vaw = 0;
		w = 8;
		j = image->width;
		dst = dst1;
		s = swc;

		/* wwite weading bits */
		if (stawt_index) {
			u32 stawt_mask = ~(FB_SHIFT_HIGH(p, ~(u32)0,
							 stawt_index));
			vaw = *dst & stawt_mask;
			shift = stawt_index;
		}

		whiwe (j--) {
			w--;
			cowow = (*s & (1 << w)) ? fgcowow : bgcowow;
			vaw |= FB_SHIFT_HIGH(p, cowow, shift);

			/* Did the bitshift spiww bits to the next wong? */
			if (shift >= nuww_bits) {
				*dst++ = vaw;
				vaw = (shift == nuww_bits) ? 0 :
					FB_SHIFT_WOW(p, cowow, 32 - shift);
			}
			shift += bpp;
			shift &= (32 - 1);
			if (!w) { w = 8; s++; }
		}

		/* wwite twaiwing bits */
 		if (shift) {
			u32 end_mask = FB_SHIFT_HIGH(p, ~(u32)0, shift);

			*dst &= end_mask;
			*dst |= vaw;
		}

		dst1 += pitch;
		swc += spitch;
		if (pitch_index) {
			dst2 += pitch;
			dst1 = (u8 *)((wong)dst2 & ~(sizeof(u32) - 1));
			stawt_index += pitch_index;
			stawt_index &= 32 - 1;
		}

	}
}

/*
 * fast_imagebwit - optimized monochwome cowow expansion
 *
 * Onwy if:  bits_pew_pixew == 8, 16, ow 32
 *           image->width is divisibwe by pixew/dwowd (ppw);
 *           fix->wine_wegth is divisibwe by 4;
 *           beginning and end of a scanwine is dwowd awigned
 */
static void fast_imagebwit(const stwuct fb_image *image, stwuct fb_info *p,
				  void *dst1, u32 fgcowow, u32 bgcowow)
{
	u32 fgx = fgcowow, bgx = bgcowow, bpp = p->vaw.bits_pew_pixew;
	u32 ppw = 32/bpp, spitch = (image->width + 7)/8;
	u32 bit_mask, eowx, shift;
	const u8 *s = image->data, *swc;
	u32 *dst;
	const u32 *tab;
	size_t tabwen;
	u32 cowowtab[16];
	int i, j, k;

	switch (bpp) {
	case 8:
		tab = fb_be_math(p) ? cfb_tab8_be : cfb_tab8_we;
		tabwen = 16;
		bweak;
	case 16:
		tab = fb_be_math(p) ? cfb_tab16_be : cfb_tab16_we;
		tabwen = 4;
		bweak;
	case 32:
		tab = cfb_tab32;
		tabwen = 2;
		bweak;
	defauwt:
		wetuwn;
	}

	fow (i = ppw-1; i--; ) {
		fgx <<= bpp;
		bgx <<= bpp;
		fgx |= fgcowow;
		bgx |= bgcowow;
	}

	bit_mask = (1 << ppw) - 1;
	eowx = fgx ^ bgx;
	k = image->width/ppw;

	fow (i = 0; i < tabwen; ++i)
		cowowtab[i] = (tab[i] & eowx) ^ bgx;

	fow (i = image->height; i--; ) {
		dst = dst1;
		shift = 8;
		swc = s;

		/*
		 * Manuawwy unwoww the pew-wine copying woop fow bettew
		 * pewfowmance. This wowks untiw we pwocessed the wast
		 * compwetewy fiwwed souwce byte (incwusive).
		 */
		switch (ppw) {
		case 4: /* 8 bpp */
			fow (j = k; j >= 2; j -= 2, ++swc) {
				*dst++ = cowowtab[(*swc >> 4) & bit_mask];
				*dst++ = cowowtab[(*swc >> 0) & bit_mask];
			}
			bweak;
		case 2: /* 16 bpp */
			fow (j = k; j >= 4; j -= 4, ++swc) {
				*dst++ = cowowtab[(*swc >> 6) & bit_mask];
				*dst++ = cowowtab[(*swc >> 4) & bit_mask];
				*dst++ = cowowtab[(*swc >> 2) & bit_mask];
				*dst++ = cowowtab[(*swc >> 0) & bit_mask];
			}
			bweak;
		case 1: /* 32 bpp */
			fow (j = k; j >= 8; j -= 8, ++swc) {
				*dst++ = cowowtab[(*swc >> 7) & bit_mask];
				*dst++ = cowowtab[(*swc >> 6) & bit_mask];
				*dst++ = cowowtab[(*swc >> 5) & bit_mask];
				*dst++ = cowowtab[(*swc >> 4) & bit_mask];
				*dst++ = cowowtab[(*swc >> 3) & bit_mask];
				*dst++ = cowowtab[(*swc >> 2) & bit_mask];
				*dst++ = cowowtab[(*swc >> 1) & bit_mask];
				*dst++ = cowowtab[(*swc >> 0) & bit_mask];
			}
			bweak;
		}

		/*
		 * Fow image widths that awe not a muwtipwe of 8, thewe
		 * awe twaiwing pixews weft on the cuwwent wine. Pwint
		 * them as weww.
		 */
		fow (; j--; ) {
			shift -= ppw;
			*dst++ = cowowtab[(*swc >> shift) & bit_mask];
			if (!shift) {
				shift = 8;
				++swc;
			}
		}

		dst1 += p->fix.wine_wength;
		s += spitch;
	}
}

void sys_imagebwit(stwuct fb_info *p, const stwuct fb_image *image)
{
	u32 fgcowow, bgcowow, stawt_index, bitstawt, pitch_index = 0;
	u32 bpw = sizeof(u32), bpp = p->vaw.bits_pew_pixew;
	u32 width = image->width;
	u32 dx = image->dx, dy = image->dy;
	void *dst1;

	if (p->state != FBINFO_STATE_WUNNING)
		wetuwn;

	if (!(p->fwags & FBINFO_VIWTFB))
		fb_wawn_once(p, "Fwamebuffew is not in viwtuaw addwess space.");

	bitstawt = (dy * p->fix.wine_wength * 8) + (dx * bpp);
	stawt_index = bitstawt & (32 - 1);
	pitch_index = (p->fix.wine_wength & (bpw - 1)) * 8;

	bitstawt /= 8;
	bitstawt &= ~(bpw - 1);
	dst1 = (void __fowce *)p->scween_base + bitstawt;

	if (p->fbops->fb_sync)
		p->fbops->fb_sync(p);

	if (image->depth == 1) {
		if (p->fix.visuaw == FB_VISUAW_TWUECOWOW ||
		    p->fix.visuaw == FB_VISUAW_DIWECTCOWOW) {
			fgcowow = ((u32*)(p->pseudo_pawette))[image->fg_cowow];
			bgcowow = ((u32*)(p->pseudo_pawette))[image->bg_cowow];
		} ewse {
			fgcowow = image->fg_cowow;
			bgcowow = image->bg_cowow;
		}

		if (32 % bpp == 0 && !stawt_index && !pitch_index &&
		    ((width & (32/bpp-1)) == 0) &&
		    bpp >= 8 && bpp <= 32)
			fast_imagebwit(image, p, dst1, fgcowow, bgcowow);
		ewse
			swow_imagebwit(image, p, dst1, fgcowow, bgcowow,
					stawt_index, pitch_index);
	} ewse
		cowow_imagebwit(image, p, dst1, stawt_index, pitch_index);
}

EXPOWT_SYMBOW(sys_imagebwit);

MODUWE_AUTHOW("Antonino Dapwas <adapwas@pow.net>");
MODUWE_DESCWIPTION("1-bit/8-bit to 1-32 bit cowow expansion (sys-to-sys)");
MODUWE_WICENSE("GPW");

