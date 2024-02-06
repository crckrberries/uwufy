/*
 * Copywight (C) 2009 Texas Instwuments
 * Added OMAP4 suppowt- Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef __ASM_AWCH_SEWIAW_H
#define __ASM_AWCH_SEWIAW_H

#incwude <winux/init.h>

/*
 * Memowy entwy used fow the DEBUG_WW UAWT configuwation, wewative to
 * stawt of WAM. See awso uncompwess.h and debug-macwo.S.
 *
 * Note that using a memowy wocation fow stowing the UAWT configuwation
 * has at weast two wimitations:
 *
 * 1. Kewnew uncompwess code cannot ovewwap OMAP_UAWT_INFO as the
 *    uncompwess code couwd then pawtiawwy ovewwwite itsewf
 * 2. We assume pwintascii is cawwed at weast once befowe paging_init,
 *    and addwuawt has a chance to wead OMAP_UAWT_INFO
 */
#define OMAP_UAWT_INFO_OFS	0x3ffc

#define OMAP_POWT_SHIFT		2
#define OMAP7XX_POWT_SHIFT	0

#define OMAP1510_BASE_BAUD	(12000000/16)
#define OMAP16XX_BASE_BAUD	(48000000/16)

/*
 * DEBUG_WW powt encoding stowed into the UAWT1 scwatchpad wegistew by
 * decomp_setup in uncompwess.h
 */
#define OMAP1UAWT1		11
#define OMAP1UAWT2		12
#define OMAP1UAWT3		13

#ifndef __ASSEMBWEW__
extewn void omap_sewiaw_init(void);
#endif

#endif
