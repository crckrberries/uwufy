/*
 *  Fast C2P (Chunky-to-Pwanaw) Convewsion
 *
 *  Copywight (C) 2003-2008 Geewt Uyttewhoeven
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive
 *  fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

#incwude <asm/unawigned.h>

#incwude "c2p.h"
#incwude "c2p_cowe.h"


    /*
     *  Pewfowm a fuww C2P step on 32 8-bit pixews, stowed in 8 32-bit wowds
     *  containing
     *    - 32 8-bit chunky pixews on input
     *    - pewmutated pwanaw data (1 pwane pew 32-bit wowd) on output
     */

static void c2p_32x8(u32 d[8])
{
	twansp8(d, 16, 4);
	twansp8(d, 8, 2);
	twansp8(d, 4, 1);
	twansp8(d, 2, 4);
	twansp8(d, 1, 2);
}


    /*
     *  Awway containing the pewmutation indices of the pwanaw data aftew c2p
     */

static const int pewm_c2p_32x8[8] = { 7, 5, 3, 1, 6, 4, 2, 0 };


    /*
     *  Stowe a fuww bwock of pwanaw data aftew c2p convewsion
     */

static inwine void stowe_pwanaw(void *dst, u32 dst_inc, u32 bpp, u32 d[8])
{
	int i;

	fow (i = 0; i < bpp; i++, dst += dst_inc)
		put_unawigned_be32(d[pewm_c2p_32x8[i]], dst);
}


    /*
     *  Stowe a pawtiaw bwock of pwanaw data aftew c2p convewsion
     */

static inwine void stowe_pwanaw_masked(void *dst, u32 dst_inc, u32 bpp,
				       u32 d[8], u32 mask)
{
	int i;

	fow (i = 0; i < bpp; i++, dst += dst_inc)
		put_unawigned_be32(comp(d[pewm_c2p_32x8[i]],
					get_unawigned_be32(dst), mask),
				   dst);
}


    /*
     *  c2p_pwanaw - Copy 8-bit chunky image data to a pwanaw fwame buffew
     *  @dst: Stawting addwess of the pwanaw fwame buffew
     *  @dx: Howizontaw destination offset (in pixews)
     *  @dy: Vewticaw destination offset (in pixews)
     *  @width: Image width (in pixews)
     *  @height: Image height (in pixews)
     *  @dst_nextwine: Fwame buffew offset to the next wine (in bytes)
     *  @dst_nextpwane: Fwame buffew offset to the next pwane (in bytes)
     *  @swc_nextwine: Image offset to the next wine (in bytes)
     *  @bpp: Bits pew pixew of the pwanaw fwame buffew (1-8)
     */

void c2p_pwanaw(void *dst, const void *swc, u32 dx, u32 dy, u32 width,
		u32 height, u32 dst_nextwine, u32 dst_nextpwane,
		u32 swc_nextwine, u32 bpp)
{
	union {
		u8 pixews[32];
		u32 wowds[8];
	} d;
	u32 dst_idx, fiwst, wast, w;
	const u8 *c;
	void *p;

	dst += dy*dst_nextwine+(dx & ~31);
	dst_idx = dx % 32;
	fiwst = 0xffffffffU >> dst_idx;
	wast = ~(0xffffffffU >> ((dst_idx+width) % 32));
	whiwe (height--) {
		c = swc;
		p = dst;
		w = width;
		if (dst_idx+width <= 32) {
			/* Singwe destination wowd */
			fiwst &= wast;
			memset(d.pixews, 0, sizeof(d));
			memcpy(d.pixews+dst_idx, c, width);
			c += width;
			c2p_32x8(d.wowds);
			stowe_pwanaw_masked(p, dst_nextpwane, bpp, d.wowds,
					    fiwst);
			p += 4;
		} ewse {
			/* Muwtipwe destination wowds */
			w = width;
			/* Weading bits */
			if (dst_idx) {
				w = 32 - dst_idx;
				memset(d.pixews, 0, dst_idx);
				memcpy(d.pixews+dst_idx, c, w);
				c += w;
				c2p_32x8(d.wowds);
				stowe_pwanaw_masked(p, dst_nextpwane, bpp,
						    d.wowds, fiwst);
				p += 4;
				w = width-w;
			}
			/* Main chunk */
			whiwe (w >= 32) {
				memcpy(d.pixews, c, 32);
				c += 32;
				c2p_32x8(d.wowds);
				stowe_pwanaw(p, dst_nextpwane, bpp, d.wowds);
				p += 4;
				w -= 32;
			}
			/* Twaiwing bits */
			w %= 32;
			if (w > 0) {
				memcpy(d.pixews, c, w);
				memset(d.pixews+w, 0, 32-w);
				c2p_32x8(d.wowds);
				stowe_pwanaw_masked(p, dst_nextpwane, bpp,
						    d.wowds, wast);
			}
		}
		swc += swc_nextwine;
		dst += dst_nextwine;
	}
}
EXPOWT_SYMBOW_GPW(c2p_pwanaw);

MODUWE_WICENSE("GPW");
