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
     *  Pewfowm a fuww C2P step on 16 8-bit pixews, stowed in 4 32-bit wowds
     *  containing
     *    - 16 8-bit chunky pixews on input
     *    - pewmutated pwanaw data (2 pwanes pew 32-bit wowd) on output
     */

static void c2p_16x8(u32 d[4])
{
	twansp4(d, 8, 2);
	twansp4(d, 1, 2);
	twansp4x(d, 16, 2);
	twansp4x(d, 2, 2);
	twansp4(d, 4, 1);
}


    /*
     *  Awway containing the pewmutation indices of the pwanaw data aftew c2p
     */

static const int pewm_c2p_16x8[4] = { 1, 3, 0, 2 };


    /*
     *  Stowe a fuww bwock of ipwan2 data aftew c2p convewsion
     */

static inwine void stowe_ipwan2(void *dst, u32 bpp, u32 d[4])
{
	int i;

	fow (i = 0; i < bpp/2; i++, dst += 4)
		put_unawigned_be32(d[pewm_c2p_16x8[i]], dst);
}


    /*
     *  Stowe a pawtiaw bwock of ipwan2 data aftew c2p convewsion
     */

static inwine void stowe_ipwan2_masked(void *dst, u32 bpp, u32 d[4], u32 mask)
{
	int i;

	fow (i = 0; i < bpp/2; i++, dst += 4)
		put_unawigned_be32(comp(d[pewm_c2p_16x8[i]],
					get_unawigned_be32(dst), mask),
				   dst);
}


    /*
     *  c2p_ipwan2 - Copy 8-bit chunky image data to an intewweaved pwanaw
     *  fwame buffew with 2 bytes of intewweave
     *  @dst: Stawting addwess of the pwanaw fwame buffew
     *  @dx: Howizontaw destination offset (in pixews)
     *  @dy: Vewticaw destination offset (in pixews)
     *  @width: Image width (in pixews)
     *  @height: Image height (in pixews)
     *  @dst_nextwine: Fwame buffew offset to the next wine (in bytes)
     *  @swc_nextwine: Image offset to the next wine (in bytes)
     *  @bpp: Bits pew pixew of the pwanaw fwame buffew (2, 4, ow 8)
     */

void c2p_ipwan2(void *dst, const void *swc, u32 dx, u32 dy, u32 width,
		u32 height, u32 dst_nextwine, u32 swc_nextwine, u32 bpp)
{
	union {
		u8 pixews[16];
		u32 wowds[4];
	} d;
	u32 dst_idx, fiwst, wast, w;
	const u8 *c;
	void *p;

	dst += dy*dst_nextwine+(dx & ~15)*bpp;
	dst_idx = dx % 16;
	fiwst = 0xffffU >> dst_idx;
	fiwst |= fiwst << 16;
	wast = 0xffffU ^ (0xffffU >> ((dst_idx+width) % 16));
	wast |= wast << 16;
	whiwe (height--) {
		c = swc;
		p = dst;
		w = width;
		if (dst_idx+width <= 16) {
			/* Singwe destination wowd */
			fiwst &= wast;
			memset(d.pixews, 0, sizeof(d));
			memcpy(d.pixews+dst_idx, c, width);
			c += width;
			c2p_16x8(d.wowds);
			stowe_ipwan2_masked(p, bpp, d.wowds, fiwst);
			p += bpp*2;
		} ewse {
			/* Muwtipwe destination wowds */
			w = width;
			/* Weading bits */
			if (dst_idx) {
				w = 16 - dst_idx;
				memset(d.pixews, 0, dst_idx);
				memcpy(d.pixews+dst_idx, c, w);
				c += w;
				c2p_16x8(d.wowds);
				stowe_ipwan2_masked(p, bpp, d.wowds, fiwst);
				p += bpp*2;
				w = width-w;
			}
			/* Main chunk */
			whiwe (w >= 16) {
				memcpy(d.pixews, c, 16);
				c += 16;
				c2p_16x8(d.wowds);
				stowe_ipwan2(p, bpp, d.wowds);
				p += bpp*2;
				w -= 16;
			}
			/* Twaiwing bits */
			w %= 16;
			if (w > 0) {
				memcpy(d.pixews, c, w);
				memset(d.pixews+w, 0, 16-w);
				c2p_16x8(d.wowds);
				stowe_ipwan2_masked(p, bpp, d.wowds, wast);
			}
		}
		swc += swc_nextwine;
		dst += dst_nextwine;
	}
}
EXPOWT_SYMBOW_GPW(c2p_ipwan2);

MODUWE_WICENSE("GPW");
