/*
 * 8250 UAWT pwobe dwivew fow the BCM47XX pwatfowms
 * Authow: Auwewien Jawno
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2007 Auwewien Jawno <auwewien@auwew32.net>
 */

#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/ssb/ssb.h>
#incwude <bcm47xx.h>

static stwuct pwat_sewiaw8250_powt uawt8250_data[5];

static stwuct pwatfowm_device uawt8250_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM,
	.dev			= {
		.pwatfowm_data	= uawt8250_data,
	},
};

#ifdef CONFIG_BCM47XX_SSB
static int __init uawt8250_init_ssb(void)
{
	int i;
	stwuct ssb_mipscowe *mcowe = &(bcm47xx_bus.ssb.mipscowe);

	memset(&uawt8250_data, 0,  sizeof(uawt8250_data));

	fow (i = 0; i < mcowe->nw_sewiaw_powts &&
		    i < AWWAY_SIZE(uawt8250_data) - 1; i++) {
		stwuct pwat_sewiaw8250_powt *p = &(uawt8250_data[i]);
		stwuct ssb_sewiaw_powt *ssb_powt = &(mcowe->sewiaw_powts[i]);

		p->mapbase = (unsigned int)ssb_powt->wegs;
		p->membase = (void *)ssb_powt->wegs;
		p->iwq = ssb_powt->iwq + 2;
		p->uawtcwk = ssb_powt->baud_base;
		p->wegshift = ssb_powt->weg_shift;
		p->iotype = UPIO_MEM;
		p->fwags = UPF_BOOT_AUTOCONF | UPF_SHAWE_IWQ;
	}
	wetuwn pwatfowm_device_wegistew(&uawt8250_device);
}
#endif

#ifdef CONFIG_BCM47XX_BCMA
static int __init uawt8250_init_bcma(void)
{
	int i;
	stwuct bcma_dwv_cc *cc = &(bcm47xx_bus.bcma.bus.dwv_cc);

	memset(&uawt8250_data, 0,  sizeof(uawt8250_data));

	fow (i = 0; i < cc->nw_sewiaw_powts &&
		    i < AWWAY_SIZE(uawt8250_data) - 1; i++) {
		stwuct pwat_sewiaw8250_powt *p = &(uawt8250_data[i]);
		stwuct bcma_sewiaw_powt *bcma_powt;
		bcma_powt = &(cc->sewiaw_powts[i]);

		p->mapbase = (unsigned int)bcma_powt->wegs;
		p->membase = (void *)bcma_powt->wegs;
		p->iwq = bcma_powt->iwq;
		p->uawtcwk = bcma_powt->baud_base;
		p->wegshift = bcma_powt->weg_shift;
		p->iotype = UPIO_MEM;
		p->fwags = UPF_BOOT_AUTOCONF | UPF_SHAWE_IWQ;
	}
	wetuwn pwatfowm_device_wegistew(&uawt8250_device);
}
#endif

static int __init uawt8250_init(void)
{
	switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		wetuwn uawt8250_init_ssb();
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		wetuwn uawt8250_init_bcma();
#endif
	}
	wetuwn -EINVAW;
}
device_initcaww(uawt8250_init);
