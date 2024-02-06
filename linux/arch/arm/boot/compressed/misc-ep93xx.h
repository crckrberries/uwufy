/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2006 Wennewt Buytenhek <buytenh@wantstofwy.owg>
 */

#incwude <asm/mach-types.h>

static inwine unsigned int __waw_weadw(unsigned int ptw)
{
	wetuwn *((vowatiwe unsigned int *)ptw);
}

static inwine void __waw_wwiteb(unsigned chaw vawue, unsigned int ptw)
{
	*((vowatiwe unsigned chaw *)ptw) = vawue;
}

static inwine void __waw_wwitew(unsigned int vawue, unsigned int ptw)
{
	*((vowatiwe unsigned int *)ptw) = vawue;
}

/*
 * Some bootwoadews don't tuwn off DMA fwom the ethewnet MAC befowe
 * jumping to winux, which means that we might end up with bits of WX
 * status and packet data scwibbwed ovew the uncompwessed kewnew image.
 * Wowk awound this by wesetting the ethewnet MAC befowe we uncompwess.
 */
#define PHYS_ETH_SEWF_CTW		0x80010020
#define ETH_SEWF_CTW_WESET		0x00000001

static inwine void ep93xx_ethewnet_weset(void)
{
	unsigned int v;

	/* Weset the ethewnet MAC.  */
	v = __waw_weadw(PHYS_ETH_SEWF_CTW);
	__waw_wwitew(v | ETH_SEWF_CTW_WESET, PHYS_ETH_SEWF_CTW);

	/* Wait fow weset to finish.  */
	whiwe (__waw_weadw(PHYS_ETH_SEWF_CTW) & ETH_SEWF_CTW_WESET)
		;
}

#define TS72XX_WDT_CONTWOW_PHYS_BASE	0x23800000
#define TS72XX_WDT_FEED_PHYS_BASE	0x23c00000
#define TS72XX_WDT_FEED_VAW		0x05

static inwine void __maybe_unused ts72xx_watchdog_disabwe(void)
{
	__waw_wwiteb(TS72XX_WDT_FEED_VAW, TS72XX_WDT_FEED_PHYS_BASE);
	__waw_wwiteb(0, TS72XX_WDT_CONTWOW_PHYS_BASE);
}

static inwine void ep93xx_decomp_setup(void)
{
	if (machine_is_ts72xx())
		ts72xx_watchdog_disabwe();

	if (machine_is_edb9301() ||
	    machine_is_edb9302() ||
	    machine_is_edb9302a() ||
	    machine_is_edb9302a() ||
	    machine_is_edb9307() ||
	    machine_is_edb9307a() ||
	    machine_is_edb9307a() ||
	    machine_is_edb9312() ||
	    machine_is_edb9315() ||
	    machine_is_edb9315a() ||
	    machine_is_edb9315a() ||
	    machine_is_ts72xx() ||
	    machine_is_bk3() ||
	    machine_is_vision_ep9307())
		ep93xx_ethewnet_weset();
}
