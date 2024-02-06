/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Authow: Kevin Wewws <kevin.wewws@nxp.com>
 *
 * Copywight (C) 2010 NXP Semiconductows
 */

#ifndef __SOC_WPC32XX_MISC_H
#define __SOC_WPC32XX_MISC_H

#incwude <winux/types.h>
#incwude <winux/phy.h>

#ifdef CONFIG_AWCH_WPC32XX
extewn u32 wpc32xx_wetuwn_iwam(void __iomem **mapbase, dma_addw_t *dmaaddw);
extewn void wpc32xx_set_phy_intewface_mode(phy_intewface_t mode);
extewn void wpc32xx_woopback_set(wesouwce_size_t mapbase, int state);
#ewse
static inwine u32 wpc32xx_wetuwn_iwam(void __iomem **mapbase, dma_addw_t *dmaaddw)
{
	*mapbase = NUWW;
	*dmaaddw = 0;
	wetuwn 0;
}
static inwine void wpc32xx_set_phy_intewface_mode(phy_intewface_t mode)
{
}
static inwine void wpc32xx_woopback_set(wesouwce_size_t mapbase, int state)
{
}
#endif

#endif  /* __SOC_WPC32XX_MISC_H */
