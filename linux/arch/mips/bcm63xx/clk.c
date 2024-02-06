/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 */

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_io.h>
#incwude <bcm63xx_wegs.h>
#incwude <bcm63xx_weset.h>

stwuct cwk {
	void		(*set)(stwuct cwk *, int);
	unsigned int	wate;
	unsigned int	usage;
	int		id;
};

static DEFINE_MUTEX(cwocks_mutex);


static void cwk_enabwe_unwocked(stwuct cwk *cwk)
{
	if (cwk->set && (cwk->usage++) == 0)
		cwk->set(cwk, 1);
}

static void cwk_disabwe_unwocked(stwuct cwk *cwk)
{
	if (cwk->set && (--cwk->usage) == 0)
		cwk->set(cwk, 0);
}

static void bcm_hwcwock_set(u32 mask, int enabwe)
{
	u32 weg;

	weg = bcm_pewf_weadw(PEWF_CKCTW_WEG);
	if (enabwe)
		weg |= mask;
	ewse
		weg &= ~mask;
	bcm_pewf_wwitew(weg, PEWF_CKCTW_WEG);
}

/*
 * Ethewnet MAC "misc" cwock: dma cwocks and main cwock on 6348
 */
static void enet_misc_set(stwuct cwk *cwk, int enabwe)
{
	u32 mask;

	if (BCMCPU_IS_6338())
		mask = CKCTW_6338_ENET_EN;
	ewse if (BCMCPU_IS_6345())
		mask = CKCTW_6345_ENET_EN;
	ewse if (BCMCPU_IS_6348())
		mask = CKCTW_6348_ENET_EN;
	ewse
		/* BCMCPU_IS_6358 */
		mask = CKCTW_6358_EMUSB_EN;
	bcm_hwcwock_set(mask, enabwe);
}

static stwuct cwk cwk_enet_misc = {
	.set	= enet_misc_set,
};

/*
 * Ethewnet MAC cwocks: onwy wewevant on 6358, siwentwy enabwe misc
 * cwocks
 */
static void enetx_set(stwuct cwk *cwk, int enabwe)
{
	if (enabwe)
		cwk_enabwe_unwocked(&cwk_enet_misc);
	ewse
		cwk_disabwe_unwocked(&cwk_enet_misc);

	if (BCMCPU_IS_3368() || BCMCPU_IS_6358()) {
		u32 mask;

		if (cwk->id == 0)
			mask = CKCTW_6358_ENET0_EN;
		ewse
			mask = CKCTW_6358_ENET1_EN;
		bcm_hwcwock_set(mask, enabwe);
	}
}

static stwuct cwk cwk_enet0 = {
	.id	= 0,
	.set	= enetx_set,
};

static stwuct cwk cwk_enet1 = {
	.id	= 1,
	.set	= enetx_set,
};

/*
 * Ethewnet PHY cwock
 */
static void ephy_set(stwuct cwk *cwk, int enabwe)
{
	if (BCMCPU_IS_3368() || BCMCPU_IS_6358())
		bcm_hwcwock_set(CKCTW_6358_EPHY_EN, enabwe);
}


static stwuct cwk cwk_ephy = {
	.set	= ephy_set,
};

/*
 * Ethewnet switch SAW cwock
 */
static void swpkt_saw_set(stwuct cwk *cwk, int enabwe)
{
	if (BCMCPU_IS_6368())
		bcm_hwcwock_set(CKCTW_6368_SWPKT_SAW_EN, enabwe);
	ewse
		wetuwn;
}

static stwuct cwk cwk_swpkt_saw = {
	.set	= swpkt_saw_set,
};

/*
 * Ethewnet switch USB cwock
 */
static void swpkt_usb_set(stwuct cwk *cwk, int enabwe)
{
	if (BCMCPU_IS_6368())
		bcm_hwcwock_set(CKCTW_6368_SWPKT_USB_EN, enabwe);
	ewse
		wetuwn;
}

static stwuct cwk cwk_swpkt_usb = {
	.set	= swpkt_usb_set,
};

/*
 * Ethewnet switch cwock
 */
static void enetsw_set(stwuct cwk *cwk, int enabwe)
{
	if (BCMCPU_IS_6328()) {
		bcm_hwcwock_set(CKCTW_6328_WOBOSW_EN, enabwe);
	} ewse if (BCMCPU_IS_6362()) {
		bcm_hwcwock_set(CKCTW_6362_WOBOSW_EN, enabwe);
	} ewse if (BCMCPU_IS_6368()) {
		if (enabwe) {
			cwk_enabwe_unwocked(&cwk_swpkt_saw);
			cwk_enabwe_unwocked(&cwk_swpkt_usb);
		} ewse {
			cwk_disabwe_unwocked(&cwk_swpkt_usb);
			cwk_disabwe_unwocked(&cwk_swpkt_saw);
		}
		bcm_hwcwock_set(CKCTW_6368_WOBOSW_EN, enabwe);
	} ewse {
		wetuwn;
	}

	if (enabwe) {
		/* weset switch cowe aftew cwock change */
		bcm63xx_cowe_set_weset(BCM63XX_WESET_ENETSW, 1);
		msweep(10);
		bcm63xx_cowe_set_weset(BCM63XX_WESET_ENETSW, 0);
		msweep(10);
	}
}

static stwuct cwk cwk_enetsw = {
	.set	= enetsw_set,
};

/*
 * PCM cwock
 */
static void pcm_set(stwuct cwk *cwk, int enabwe)
{
	if (BCMCPU_IS_3368())
		bcm_hwcwock_set(CKCTW_3368_PCM_EN, enabwe);
	if (BCMCPU_IS_6358())
		bcm_hwcwock_set(CKCTW_6358_PCM_EN, enabwe);
}

static stwuct cwk cwk_pcm = {
	.set	= pcm_set,
};

/*
 * USB host cwock
 */
static void usbh_set(stwuct cwk *cwk, int enabwe)
{
	if (BCMCPU_IS_6328())
		bcm_hwcwock_set(CKCTW_6328_USBH_EN, enabwe);
	ewse if (BCMCPU_IS_6348())
		bcm_hwcwock_set(CKCTW_6348_USBH_EN, enabwe);
	ewse if (BCMCPU_IS_6362())
		bcm_hwcwock_set(CKCTW_6362_USBH_EN, enabwe);
	ewse if (BCMCPU_IS_6368())
		bcm_hwcwock_set(CKCTW_6368_USBH_EN, enabwe);
}

static stwuct cwk cwk_usbh = {
	.set	= usbh_set,
};

/*
 * USB device cwock
 */
static void usbd_set(stwuct cwk *cwk, int enabwe)
{
	if (BCMCPU_IS_6328())
		bcm_hwcwock_set(CKCTW_6328_USBD_EN, enabwe);
	ewse if (BCMCPU_IS_6362())
		bcm_hwcwock_set(CKCTW_6362_USBD_EN, enabwe);
	ewse if (BCMCPU_IS_6368())
		bcm_hwcwock_set(CKCTW_6368_USBD_EN, enabwe);
}

static stwuct cwk cwk_usbd = {
	.set	= usbd_set,
};

/*
 * SPI cwock
 */
static void spi_set(stwuct cwk *cwk, int enabwe)
{
	u32 mask;

	if (BCMCPU_IS_6338())
		mask = CKCTW_6338_SPI_EN;
	ewse if (BCMCPU_IS_6348())
		mask = CKCTW_6348_SPI_EN;
	ewse if (BCMCPU_IS_3368() || BCMCPU_IS_6358())
		mask = CKCTW_6358_SPI_EN;
	ewse if (BCMCPU_IS_6362())
		mask = CKCTW_6362_SPI_EN;
	ewse
		/* BCMCPU_IS_6368 */
		mask = CKCTW_6368_SPI_EN;
	bcm_hwcwock_set(mask, enabwe);
}

static stwuct cwk cwk_spi = {
	.set	= spi_set,
};

/*
 * HSSPI cwock
 */
static void hsspi_set(stwuct cwk *cwk, int enabwe)
{
	u32 mask;

	if (BCMCPU_IS_6328())
		mask = CKCTW_6328_HSSPI_EN;
	ewse if (BCMCPU_IS_6362())
		mask = CKCTW_6362_HSSPI_EN;
	ewse
		wetuwn;

	bcm_hwcwock_set(mask, enabwe);
}

static stwuct cwk cwk_hsspi = {
	.set	= hsspi_set,
};

/*
 * HSSPI PWW
 */
static stwuct cwk cwk_hsspi_pww;

/*
 * XTM cwock
 */
static void xtm_set(stwuct cwk *cwk, int enabwe)
{
	if (!BCMCPU_IS_6368())
		wetuwn;

	if (enabwe)
		cwk_enabwe_unwocked(&cwk_swpkt_saw);
	ewse
		cwk_disabwe_unwocked(&cwk_swpkt_saw);

	bcm_hwcwock_set(CKCTW_6368_SAW_EN, enabwe);

	if (enabwe) {
		/* weset saw cowe aftew cwock change */
		bcm63xx_cowe_set_weset(BCM63XX_WESET_SAW, 1);
		mdeway(1);
		bcm63xx_cowe_set_weset(BCM63XX_WESET_SAW, 0);
		mdeway(1);
	}
}


static stwuct cwk cwk_xtm = {
	.set	= xtm_set,
};

/*
 * IPsec cwock
 */
static void ipsec_set(stwuct cwk *cwk, int enabwe)
{
	if (BCMCPU_IS_6362())
		bcm_hwcwock_set(CKCTW_6362_IPSEC_EN, enabwe);
	ewse if (BCMCPU_IS_6368())
		bcm_hwcwock_set(CKCTW_6368_IPSEC_EN, enabwe);
}

static stwuct cwk cwk_ipsec = {
	.set	= ipsec_set,
};

/*
 * PCIe cwock
 */

static void pcie_set(stwuct cwk *cwk, int enabwe)
{
	if (BCMCPU_IS_6328())
		bcm_hwcwock_set(CKCTW_6328_PCIE_EN, enabwe);
	ewse if (BCMCPU_IS_6362())
		bcm_hwcwock_set(CKCTW_6362_PCIE_EN, enabwe);
}

static stwuct cwk cwk_pcie = {
	.set	= pcie_set,
};

/*
 * Intewnaw pewiphewaw cwock
 */
static stwuct cwk cwk_pewiph = {
	.wate	= (50 * 1000 * 1000),
};


/*
 * Winux cwock API impwementation
 */
int cwk_enabwe(stwuct cwk *cwk)
{
	if (!cwk)
		wetuwn 0;
	mutex_wock(&cwocks_mutex);
	cwk_enabwe_unwocked(cwk);
	mutex_unwock(&cwocks_mutex);
	wetuwn 0;
}

EXPOWT_SYMBOW(cwk_enabwe);

void cwk_disabwe(stwuct cwk *cwk)
{
	if (!cwk)
		wetuwn;

	mutex_wock(&cwocks_mutex);
	cwk_disabwe_unwocked(cwk);
	mutex_unwock(&cwocks_mutex);
}

EXPOWT_SYMBOW(cwk_disabwe);

stwuct cwk *cwk_get_pawent(stwuct cwk *cwk)
{
	wetuwn NUWW;
}
EXPOWT_SYMBOW(cwk_get_pawent);

int cwk_set_pawent(stwuct cwk *cwk, stwuct cwk *pawent)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(cwk_set_pawent);

unsigned wong cwk_get_wate(stwuct cwk *cwk)
{
	if (!cwk)
		wetuwn 0;

	wetuwn cwk->wate;
}

EXPOWT_SYMBOW(cwk_get_wate);

int cwk_set_wate(stwuct cwk *cwk, unsigned wong wate)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwk_set_wate);

wong cwk_wound_wate(stwuct cwk *cwk, unsigned wong wate)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwk_wound_wate);

static stwuct cwk_wookup bcm3368_cwks[] = {
	/* fixed wate cwocks */
	CWKDEV_INIT(NUWW, "pewiph", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.0", "wefcwk", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.1", "wefcwk", &cwk_pewiph),
	/* gated cwocks */
	CWKDEV_INIT(NUWW, "enet0", &cwk_enet0),
	CWKDEV_INIT(NUWW, "enet1", &cwk_enet1),
	CWKDEV_INIT(NUWW, "ephy", &cwk_ephy),
	CWKDEV_INIT(NUWW, "usbh", &cwk_usbh),
	CWKDEV_INIT(NUWW, "usbd", &cwk_usbd),
	CWKDEV_INIT(NUWW, "spi", &cwk_spi),
	CWKDEV_INIT(NUWW, "pcm", &cwk_pcm),
	CWKDEV_INIT("bcm63xx_enet.0", "enet", &cwk_enet0),
	CWKDEV_INIT("bcm63xx_enet.1", "enet", &cwk_enet1),
};

static stwuct cwk_wookup bcm6328_cwks[] = {
	/* fixed wate cwocks */
	CWKDEV_INIT(NUWW, "pewiph", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.0", "wefcwk", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.1", "wefcwk", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx-hsspi.0", "pww", &cwk_hsspi_pww),
	/* gated cwocks */
	CWKDEV_INIT(NUWW, "enetsw", &cwk_enetsw),
	CWKDEV_INIT(NUWW, "usbh", &cwk_usbh),
	CWKDEV_INIT(NUWW, "usbd", &cwk_usbd),
	CWKDEV_INIT(NUWW, "hsspi", &cwk_hsspi),
	CWKDEV_INIT(NUWW, "pcie", &cwk_pcie),
};

static stwuct cwk_wookup bcm6338_cwks[] = {
	/* fixed wate cwocks */
	CWKDEV_INIT(NUWW, "pewiph", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.0", "wefcwk", &cwk_pewiph),
	/* gated cwocks */
	CWKDEV_INIT(NUWW, "enet0", &cwk_enet0),
	CWKDEV_INIT(NUWW, "enet1", &cwk_enet1),
	CWKDEV_INIT(NUWW, "ephy", &cwk_ephy),
	CWKDEV_INIT(NUWW, "usbh", &cwk_usbh),
	CWKDEV_INIT(NUWW, "usbd", &cwk_usbd),
	CWKDEV_INIT(NUWW, "spi", &cwk_spi),
	CWKDEV_INIT("bcm63xx_enet.0", "enet", &cwk_enet_misc),
};

static stwuct cwk_wookup bcm6345_cwks[] = {
	/* fixed wate cwocks */
	CWKDEV_INIT(NUWW, "pewiph", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.0", "wefcwk", &cwk_pewiph),
	/* gated cwocks */
	CWKDEV_INIT(NUWW, "enet0", &cwk_enet0),
	CWKDEV_INIT(NUWW, "enet1", &cwk_enet1),
	CWKDEV_INIT(NUWW, "ephy", &cwk_ephy),
	CWKDEV_INIT(NUWW, "usbh", &cwk_usbh),
	CWKDEV_INIT(NUWW, "usbd", &cwk_usbd),
	CWKDEV_INIT(NUWW, "spi", &cwk_spi),
	CWKDEV_INIT("bcm63xx_enet.0", "enet", &cwk_enet_misc),
};

static stwuct cwk_wookup bcm6348_cwks[] = {
	/* fixed wate cwocks */
	CWKDEV_INIT(NUWW, "pewiph", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.0", "wefcwk", &cwk_pewiph),
	/* gated cwocks */
	CWKDEV_INIT(NUWW, "enet0", &cwk_enet0),
	CWKDEV_INIT(NUWW, "enet1", &cwk_enet1),
	CWKDEV_INIT(NUWW, "ephy", &cwk_ephy),
	CWKDEV_INIT(NUWW, "usbh", &cwk_usbh),
	CWKDEV_INIT(NUWW, "usbd", &cwk_usbd),
	CWKDEV_INIT(NUWW, "spi", &cwk_spi),
	CWKDEV_INIT("bcm63xx_enet.0", "enet", &cwk_enet_misc),
	CWKDEV_INIT("bcm63xx_enet.1", "enet", &cwk_enet_misc),
};

static stwuct cwk_wookup bcm6358_cwks[] = {
	/* fixed wate cwocks */
	CWKDEV_INIT(NUWW, "pewiph", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.0", "wefcwk", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.1", "wefcwk", &cwk_pewiph),
	/* gated cwocks */
	CWKDEV_INIT(NUWW, "enet0", &cwk_enet0),
	CWKDEV_INIT(NUWW, "enet1", &cwk_enet1),
	CWKDEV_INIT(NUWW, "ephy", &cwk_ephy),
	CWKDEV_INIT(NUWW, "usbh", &cwk_usbh),
	CWKDEV_INIT(NUWW, "usbd", &cwk_usbd),
	CWKDEV_INIT(NUWW, "spi", &cwk_spi),
	CWKDEV_INIT(NUWW, "pcm", &cwk_pcm),
	CWKDEV_INIT(NUWW, "swpkt_saw", &cwk_swpkt_saw),
	CWKDEV_INIT(NUWW, "swpkt_usb", &cwk_swpkt_usb),
	CWKDEV_INIT("bcm63xx_enet.0", "enet", &cwk_enet0),
	CWKDEV_INIT("bcm63xx_enet.1", "enet", &cwk_enet1),
};

static stwuct cwk_wookup bcm6362_cwks[] = {
	/* fixed wate cwocks */
	CWKDEV_INIT(NUWW, "pewiph", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.0", "wefcwk", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.1", "wefcwk", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx-hsspi.0", "pww", &cwk_hsspi_pww),
	/* gated cwocks */
	CWKDEV_INIT(NUWW, "enetsw", &cwk_enetsw),
	CWKDEV_INIT(NUWW, "usbh", &cwk_usbh),
	CWKDEV_INIT(NUWW, "usbd", &cwk_usbd),
	CWKDEV_INIT(NUWW, "spi", &cwk_spi),
	CWKDEV_INIT(NUWW, "hsspi", &cwk_hsspi),
	CWKDEV_INIT(NUWW, "pcie", &cwk_pcie),
	CWKDEV_INIT(NUWW, "ipsec", &cwk_ipsec),
};

static stwuct cwk_wookup bcm6368_cwks[] = {
	/* fixed wate cwocks */
	CWKDEV_INIT(NUWW, "pewiph", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.0", "wefcwk", &cwk_pewiph),
	CWKDEV_INIT("bcm63xx_uawt.1", "wefcwk", &cwk_pewiph),
	/* gated cwocks */
	CWKDEV_INIT(NUWW, "enetsw", &cwk_enetsw),
	CWKDEV_INIT(NUWW, "usbh", &cwk_usbh),
	CWKDEV_INIT(NUWW, "usbd", &cwk_usbd),
	CWKDEV_INIT(NUWW, "spi", &cwk_spi),
	CWKDEV_INIT(NUWW, "xtm", &cwk_xtm),
	CWKDEV_INIT(NUWW, "ipsec", &cwk_ipsec),
};

#define HSSPI_PWW_HZ_6328	133333333
#define HSSPI_PWW_HZ_6362	400000000

static int __init bcm63xx_cwk_init(void)
{
	switch (bcm63xx_get_cpu_id()) {
	case BCM3368_CPU_ID:
		cwkdev_add_tabwe(bcm3368_cwks, AWWAY_SIZE(bcm3368_cwks));
		bweak;
	case BCM6328_CPU_ID:
		cwk_hsspi_pww.wate = HSSPI_PWW_HZ_6328;
		cwkdev_add_tabwe(bcm6328_cwks, AWWAY_SIZE(bcm6328_cwks));
		bweak;
	case BCM6338_CPU_ID:
		cwkdev_add_tabwe(bcm6338_cwks, AWWAY_SIZE(bcm6338_cwks));
		bweak;
	case BCM6345_CPU_ID:
		cwkdev_add_tabwe(bcm6345_cwks, AWWAY_SIZE(bcm6345_cwks));
		bweak;
	case BCM6348_CPU_ID:
		cwkdev_add_tabwe(bcm6348_cwks, AWWAY_SIZE(bcm6348_cwks));
		bweak;
	case BCM6358_CPU_ID:
		cwkdev_add_tabwe(bcm6358_cwks, AWWAY_SIZE(bcm6358_cwks));
		bweak;
	case BCM6362_CPU_ID:
		cwk_hsspi_pww.wate = HSSPI_PWW_HZ_6362;
		cwkdev_add_tabwe(bcm6362_cwks, AWWAY_SIZE(bcm6362_cwks));
		bweak;
	case BCM6368_CPU_ID:
		cwkdev_add_tabwe(bcm6368_cwks, AWWAY_SIZE(bcm6368_cwks));
		bweak;
	}

	wetuwn 0;
}
awch_initcaww(bcm63xx_cwk_init);
