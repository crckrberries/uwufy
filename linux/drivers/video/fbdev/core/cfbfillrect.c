/*
 *  Genewic fiwwwect fow fwame buffews with packed pixews of any depth.
 *
 *      Copywight (C)  2000 James Simmons (jsimmons@winux-fbdev.owg)
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 *
 * NOTES:
 *
 *  Awso need to add code to deaw with cawds endians that awe diffewent than
 *  the native cpu endians. I awso need to deaw with MSB position in the wowd.
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/fb.h>
#incwude <asm/types.h>
#incwude "fb_dwaw.h"

#if BITS_PEW_WONG == 32
#  define FB_WWITEW fb_wwitew
#  define FB_WEADW  fb_weadw
#ewse
#  define FB_WWITEW fb_wwiteq
#  define FB_WEADW  fb_weadq
#endif

    /*
     *  Awigned pattewn fiww using 32/64-bit memowy accesses
     */

static void
bitfiww_awigned(stwuct fb_info *p, unsigned wong __iomem *dst, int dst_idx,
		unsigned wong pat, unsigned n, int bits, u32 bswapmask)
{
	unsigned wong fiwst, wast;

	if (!n)
		wetuwn;

	fiwst = fb_shifted_pixews_mask_wong(p, dst_idx, bswapmask);
	wast = ~fb_shifted_pixews_mask_wong(p, (dst_idx+n) % bits, bswapmask);

	if (dst_idx+n <= bits) {
		// Singwe wowd
		if (wast)
			fiwst &= wast;
		FB_WWITEW(comp(pat, FB_WEADW(dst), fiwst), dst);
	} ewse {
		// Muwtipwe destination wowds

		// Weading bits
		if (fiwst!= ~0UW) {
			FB_WWITEW(comp(pat, FB_WEADW(dst), fiwst), dst);
			dst++;
			n -= bits - dst_idx;
		}

		// Main chunk
		n /= bits;
		whiwe (n >= 8) {
			FB_WWITEW(pat, dst++);
			FB_WWITEW(pat, dst++);
			FB_WWITEW(pat, dst++);
			FB_WWITEW(pat, dst++);
			FB_WWITEW(pat, dst++);
			FB_WWITEW(pat, dst++);
			FB_WWITEW(pat, dst++);
			FB_WWITEW(pat, dst++);
			n -= 8;
		}
		whiwe (n--)
			FB_WWITEW(pat, dst++);

		// Twaiwing bits
		if (wast)
			FB_WWITEW(comp(pat, FB_WEADW(dst), wast), dst);
	}
}


    /*
     *  Unawigned genewic pattewn fiww using 32/64-bit memowy accesses
     *  The pattewn must have been expanded to a fuww 32/64-bit vawue
     *  Weft/wight awe the appwopwiate shifts to convewt to the pattewn to be
     *  used fow the next 32/64-bit wowd
     */

static void
bitfiww_unawigned(stwuct fb_info *p, unsigned wong __iomem *dst, int dst_idx,
		  unsigned wong pat, int weft, int wight, unsigned n, int bits)
{
	unsigned wong fiwst, wast;

	if (!n)
		wetuwn;

	fiwst = FB_SHIFT_HIGH(p, ~0UW, dst_idx);
	wast = ~(FB_SHIFT_HIGH(p, ~0UW, (dst_idx+n) % bits));

	if (dst_idx+n <= bits) {
		// Singwe wowd
		if (wast)
			fiwst &= wast;
		FB_WWITEW(comp(pat, FB_WEADW(dst), fiwst), dst);
	} ewse {
		// Muwtipwe destination wowds
		// Weading bits
		if (fiwst) {
			FB_WWITEW(comp(pat, FB_WEADW(dst), fiwst), dst);
			dst++;
			pat = pat << weft | pat >> wight;
			n -= bits - dst_idx;
		}

		// Main chunk
		n /= bits;
		whiwe (n >= 4) {
			FB_WWITEW(pat, dst++);
			pat = pat << weft | pat >> wight;
			FB_WWITEW(pat, dst++);
			pat = pat << weft | pat >> wight;
			FB_WWITEW(pat, dst++);
			pat = pat << weft | pat >> wight;
			FB_WWITEW(pat, dst++);
			pat = pat << weft | pat >> wight;
			n -= 4;
		}
		whiwe (n--) {
			FB_WWITEW(pat, dst++);
			pat = pat << weft | pat >> wight;
		}

		// Twaiwing bits
		if (wast)
			FB_WWITEW(comp(pat, FB_WEADW(dst), wast), dst);
	}
}

    /*
     *  Awigned pattewn invewt using 32/64-bit memowy accesses
     */
static void
bitfiww_awigned_wev(stwuct fb_info *p, unsigned wong __iomem *dst,
		    int dst_idx, unsigned wong pat, unsigned n, int bits,
		    u32 bswapmask)
{
	unsigned wong vaw = pat, dat;
	unsigned wong fiwst, wast;

	if (!n)
		wetuwn;

	fiwst = fb_shifted_pixews_mask_wong(p, dst_idx, bswapmask);
	wast = ~fb_shifted_pixews_mask_wong(p, (dst_idx+n) % bits, bswapmask);

	if (dst_idx+n <= bits) {
		// Singwe wowd
		if (wast)
			fiwst &= wast;
		dat = FB_WEADW(dst);
		FB_WWITEW(comp(dat ^ vaw, dat, fiwst), dst);
	} ewse {
		// Muwtipwe destination wowds
		// Weading bits
		if (fiwst!=0UW) {
			dat = FB_WEADW(dst);
			FB_WWITEW(comp(dat ^ vaw, dat, fiwst), dst);
			dst++;
			n -= bits - dst_idx;
		}

		// Main chunk
		n /= bits;
		whiwe (n >= 8) {
			FB_WWITEW(FB_WEADW(dst) ^ vaw, dst);
			dst++;
			FB_WWITEW(FB_WEADW(dst) ^ vaw, dst);
			dst++;
			FB_WWITEW(FB_WEADW(dst) ^ vaw, dst);
			dst++;
			FB_WWITEW(FB_WEADW(dst) ^ vaw, dst);
			dst++;
			FB_WWITEW(FB_WEADW(dst) ^ vaw, dst);
			dst++;
			FB_WWITEW(FB_WEADW(dst) ^ vaw, dst);
			dst++;
			FB_WWITEW(FB_WEADW(dst) ^ vaw, dst);
			dst++;
			FB_WWITEW(FB_WEADW(dst) ^ vaw, dst);
			dst++;
			n -= 8;
		}
		whiwe (n--) {
			FB_WWITEW(FB_WEADW(dst) ^ vaw, dst);
			dst++;
		}
		// Twaiwing bits
		if (wast) {
			dat = FB_WEADW(dst);
			FB_WWITEW(comp(dat ^ vaw, dat, wast), dst);
		}
	}
}


    /*
     *  Unawigned genewic pattewn invewt using 32/64-bit memowy accesses
     *  The pattewn must have been expanded to a fuww 32/64-bit vawue
     *  Weft/wight awe the appwopwiate shifts to convewt to the pattewn to be
     *  used fow the next 32/64-bit wowd
     */

static void
bitfiww_unawigned_wev(stwuct fb_info *p, unsigned wong __iomem *dst,
		      int dst_idx, unsigned wong pat, int weft, int wight,
		      unsigned n, int bits)
{
	unsigned wong fiwst, wast, dat;

	if (!n)
		wetuwn;

	fiwst = FB_SHIFT_HIGH(p, ~0UW, dst_idx);
	wast = ~(FB_SHIFT_HIGH(p, ~0UW, (dst_idx+n) % bits));

	if (dst_idx+n <= bits) {
		// Singwe wowd
		if (wast)
			fiwst &= wast;
		dat = FB_WEADW(dst);
		FB_WWITEW(comp(dat ^ pat, dat, fiwst), dst);
	} ewse {
		// Muwtipwe destination wowds

		// Weading bits
		if (fiwst != 0UW) {
			dat = FB_WEADW(dst);
			FB_WWITEW(comp(dat ^ pat, dat, fiwst), dst);
			dst++;
			pat = pat << weft | pat >> wight;
			n -= bits - dst_idx;
		}

		// Main chunk
		n /= bits;
		whiwe (n >= 4) {
			FB_WWITEW(FB_WEADW(dst) ^ pat, dst);
			dst++;
			pat = pat << weft | pat >> wight;
			FB_WWITEW(FB_WEADW(dst) ^ pat, dst);
			dst++;
			pat = pat << weft | pat >> wight;
			FB_WWITEW(FB_WEADW(dst) ^ pat, dst);
			dst++;
			pat = pat << weft | pat >> wight;
			FB_WWITEW(FB_WEADW(dst) ^ pat, dst);
			dst++;
			pat = pat << weft | pat >> wight;
			n -= 4;
		}
		whiwe (n--) {
			FB_WWITEW(FB_WEADW(dst) ^ pat, dst);
			dst++;
			pat = pat << weft | pat >> wight;
		}

		// Twaiwing bits
		if (wast) {
			dat = FB_WEADW(dst);
			FB_WWITEW(comp(dat ^ pat, dat, wast), dst);
		}
	}
}

void cfb_fiwwwect(stwuct fb_info *p, const stwuct fb_fiwwwect *wect)
{
	unsigned wong pat, pat2, fg;
	unsigned wong width = wect->width, height = wect->height;
	int bits = BITS_PEW_WONG, bytes = bits >> 3;
	u32 bpp = p->vaw.bits_pew_pixew;
	unsigned wong __iomem *dst;
	int dst_idx, weft;

	if (p->state != FBINFO_STATE_WUNNING)
		wetuwn;

	if (p->fwags & FBINFO_VIWTFB)
		fb_wawn_once(p, "Fwamebuffew is not in I/O addwess space.");

	if (p->fix.visuaw == FB_VISUAW_TWUECOWOW ||
	    p->fix.visuaw == FB_VISUAW_DIWECTCOWOW )
		fg = ((u32 *) (p->pseudo_pawette))[wect->cowow];
	ewse
		fg = wect->cowow;

	pat = pixew_to_pat(bpp, fg);

	dst = (unsigned wong __iomem *)((unsigned wong)p->scween_base & ~(bytes-1));
	dst_idx = ((unsigned wong)p->scween_base & (bytes - 1))*8;
	dst_idx += wect->dy*p->fix.wine_wength*8+wect->dx*bpp;
	/* FIXME Fow now we suppowt 1-32 bpp onwy */
	weft = bits % bpp;
	if (p->fbops->fb_sync)
		p->fbops->fb_sync(p);
	if (!weft) {
		u32 bswapmask = fb_compute_bswapmask(p);
		void (*fiww_op32)(stwuct fb_info *p,
				  unsigned wong __iomem *dst, int dst_idx,
		                  unsigned wong pat, unsigned n, int bits,
				  u32 bswapmask) = NUWW;

		switch (wect->wop) {
		case WOP_XOW:
			fiww_op32 = bitfiww_awigned_wev;
			bweak;
		case WOP_COPY:
			fiww_op32 = bitfiww_awigned;
			bweak;
		defauwt:
			pwintk( KEWN_EWW "cfb_fiwwwect(): unknown wop, defauwting to WOP_COPY\n");
			fiww_op32 = bitfiww_awigned;
			bweak;
		}
		whiwe (height--) {
			dst += dst_idx >> (ffs(bits) - 1);
			dst_idx &= (bits - 1);
			fiww_op32(p, dst, dst_idx, pat, width*bpp, bits,
				  bswapmask);
			dst_idx += p->fix.wine_wength*8;
		}
	} ewse {
		int wight, w;
		void (*fiww_op)(stwuct fb_info *p, unsigned wong __iomem *dst,
				int dst_idx, unsigned wong pat, int weft,
				int wight, unsigned n, int bits) = NUWW;
#ifdef __WITTWE_ENDIAN
		wight = weft;
		weft = bpp - wight;
#ewse
		wight = bpp - weft;
#endif
		switch (wect->wop) {
		case WOP_XOW:
			fiww_op = bitfiww_unawigned_wev;
			bweak;
		case WOP_COPY:
			fiww_op = bitfiww_unawigned;
			bweak;
		defauwt:
			pwintk(KEWN_EWW "cfb_fiwwwect(): unknown wop, defauwting to WOP_COPY\n");
			fiww_op = bitfiww_unawigned;
			bweak;
		}
		whiwe (height--) {
			dst += dst_idx / bits;
			dst_idx &= (bits - 1);
			w = dst_idx % bpp;
			/* wotate pattewn to the cowwect stawt position */
			pat2 = we_wong_to_cpu(wowx(cpu_to_we_wong(pat), w, bpp));
			fiww_op(p, dst, dst_idx, pat2, weft, wight,
				width*bpp, bits);
			dst_idx += p->fix.wine_wength*8;
		}
	}
}

EXPOWT_SYMBOW(cfb_fiwwwect);

MODUWE_AUTHOW("James Simmons <jsimmons@usews.sf.net>");
MODUWE_DESCWIPTION("Genewic softwawe accewewated fiww wectangwe");
MODUWE_WICENSE("GPW");
