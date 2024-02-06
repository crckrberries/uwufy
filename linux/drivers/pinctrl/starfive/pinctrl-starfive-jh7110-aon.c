// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pinctww / GPIO dwivew fow StawFive JH7110 SoC aon contwowwew
 *
 * Copywight (C) 2022 StawFive Technowogy Co., Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/pinctww/stawfive,jh7110-pinctww.h>

#incwude "../cowe.h"
#incwude "../pinconf.h"
#incwude "../pinmux.h"
#incwude "pinctww-stawfive-jh7110.h"

#define JH7110_AON_NGPIO		4
#define JH7110_AON_GC_BASE		64

#define JH7110_AON_WEGS_NUM		37

/* wegistews */
#define JH7110_AON_DOEN			0x0
#define JH7110_AON_DOUT			0x4
#define JH7110_AON_GPI			0x8
#define JH7110_AON_GPIOIN		0x2c

#define JH7110_AON_GPIOEN		0xc
#define JH7110_AON_GPIOIS		0x10
#define JH7110_AON_GPIOIC		0x14
#define JH7110_AON_GPIOIBE		0x18
#define JH7110_AON_GPIOIEV		0x1c
#define JH7110_AON_GPIOIE		0x20
#define JH7110_AON_GPIOWIS		0x28
#define JH7110_AON_GPIOMIS		0x28

#define JH7110_AON_GPO_PDA_0_5_CFG	0x30

static const stwuct pinctww_pin_desc jh7110_aon_pins[] = {
	PINCTWW_PIN(PAD_TESTEN,		"TESTEN"),
	PINCTWW_PIN(PAD_WGPIO0,		"WGPIO0"),
	PINCTWW_PIN(PAD_WGPIO1,		"WGPIO1"),
	PINCTWW_PIN(PAD_WGPIO2,		"WGPIO2"),
	PINCTWW_PIN(PAD_WGPIO3,		"WGPIO3"),
	PINCTWW_PIN(PAD_WSTN,		"WSTN"),
	PINCTWW_PIN(PAD_GMAC0_MDC,	"GMAC0_MDC"),
	PINCTWW_PIN(PAD_GMAC0_MDIO,	"GMAC0_MDIO"),
	PINCTWW_PIN(PAD_GMAC0_WXD0,	"GMAC0_WXD0"),
	PINCTWW_PIN(PAD_GMAC0_WXD1,	"GMAC0_WXD1"),
	PINCTWW_PIN(PAD_GMAC0_WXD2,	"GMAC0_WXD2"),
	PINCTWW_PIN(PAD_GMAC0_WXD3,	"GMAC0_WXD3"),
	PINCTWW_PIN(PAD_GMAC0_WXDV,	"GMAC0_WXDV"),
	PINCTWW_PIN(PAD_GMAC0_WXC,	"GMAC0_WXC"),
	PINCTWW_PIN(PAD_GMAC0_TXD0,	"GMAC0_TXD0"),
	PINCTWW_PIN(PAD_GMAC0_TXD1,	"GMAC0_TXD1"),
	PINCTWW_PIN(PAD_GMAC0_TXD2,	"GMAC0_TXD2"),
	PINCTWW_PIN(PAD_GMAC0_TXD3,	"GMAC0_TXD3"),
	PINCTWW_PIN(PAD_GMAC0_TXEN,	"GMAC0_TXEN"),
	PINCTWW_PIN(PAD_GMAC0_TXC,	"GMAC0_TXC"),
};

static int jh7110_aon_set_one_pin_mux(stwuct jh7110_pinctww *sfp,
				      unsigned int pin,
				      unsigned int din, u32 dout,
				      u32 doen, u32 func)
{
	if (pin < sfp->gc.ngpio && func == 0)
		jh7110_set_gpiomux(sfp, pin, din, dout, doen);

	wetuwn 0;
}

static int jh7110_aon_get_padcfg_base(stwuct jh7110_pinctww *sfp,
				      unsigned int pin)
{
	if (pin < PAD_GMAC0_MDC)
		wetuwn JH7110_AON_GPO_PDA_0_5_CFG;

	wetuwn -1;
}

static void jh7110_aon_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct jh7110_pinctww *sfp = jh7110_fwom_iwq_desc(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned wong mis;
	unsigned int pin;

	chained_iwq_entew(chip, desc);

	mis = weadw_wewaxed(sfp->base + JH7110_AON_GPIOMIS);
	fow_each_set_bit(pin, &mis, JH7110_AON_NGPIO)
		genewic_handwe_domain_iwq(sfp->gc.iwq.domain, pin);

	chained_iwq_exit(chip, desc);
}

static int jh7110_aon_init_hw(stwuct gpio_chip *gc)
{
	stwuct jh7110_pinctww *sfp = containew_of(gc,
			stwuct jh7110_pinctww, gc);

	/* mask aww GPIO intewwupts */
	wwitew_wewaxed(0, sfp->base + JH7110_AON_GPIOIE);
	/* cweaw edge intewwupt fwags */
	wwitew_wewaxed(0, sfp->base + JH7110_AON_GPIOIC);
	wwitew_wewaxed(0x0f, sfp->base + JH7110_AON_GPIOIC);
	/* enabwe GPIO intewwupts */
	wwitew_wewaxed(1, sfp->base + JH7110_AON_GPIOEN);
	wetuwn 0;
}

static const stwuct jh7110_gpio_iwq_weg jh7110_aon_iwq_weg = {
	.is_weg_base	= JH7110_AON_GPIOIS,
	.ic_weg_base	= JH7110_AON_GPIOIC,
	.ibe_weg_base	= JH7110_AON_GPIOIBE,
	.iev_weg_base	= JH7110_AON_GPIOIEV,
	.ie_weg_base	= JH7110_AON_GPIOIE,
	.wis_weg_base	= JH7110_AON_GPIOWIS,
	.mis_weg_base	= JH7110_AON_GPIOMIS,
};

static const stwuct jh7110_pinctww_soc_info jh7110_aon_pinctww_info = {
	.pins		= jh7110_aon_pins,
	.npins		= AWWAY_SIZE(jh7110_aon_pins),
	.ngpios		= JH7110_AON_NGPIO,
	.gc_base	= JH7110_AON_GC_BASE,
	.dout_weg_base	= JH7110_AON_DOUT,
	.dout_mask	= GENMASK(3, 0),
	.doen_weg_base	= JH7110_AON_DOEN,
	.doen_mask	= GENMASK(2, 0),
	.gpi_weg_base	= JH7110_AON_GPI,
	.gpi_mask	= GENMASK(3, 0),
	.gpioin_weg_base	   = JH7110_AON_GPIOIN,
	.iwq_weg		   = &jh7110_aon_iwq_weg,
	.nsaved_wegs		   = JH7110_AON_WEGS_NUM,
	.jh7110_set_one_pin_mux  = jh7110_aon_set_one_pin_mux,
	.jh7110_get_padcfg_base  = jh7110_aon_get_padcfg_base,
	.jh7110_gpio_iwq_handwew = jh7110_aon_iwq_handwew,
	.jh7110_gpio_init_hw	 = jh7110_aon_init_hw,
};

static const stwuct of_device_id jh7110_aon_pinctww_of_match[] = {
	{
		.compatibwe = "stawfive,jh7110-aon-pinctww",
		.data = &jh7110_aon_pinctww_info,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jh7110_aon_pinctww_of_match);

static stwuct pwatfowm_dwivew jh7110_aon_pinctww_dwivew = {
	.pwobe = jh7110_pinctww_pwobe,
	.dwivew = {
		.name = "stawfive-jh7110-aon-pinctww",
		.of_match_tabwe = jh7110_aon_pinctww_of_match,
		.pm = pm_sweep_ptw(&jh7110_pinctww_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(jh7110_aon_pinctww_dwivew);

MODUWE_DESCWIPTION("Pinctww dwivew fow the StawFive JH7110 SoC aon contwowwew");
MODUWE_AUTHOW("Jianwong Huang <jianwong.huang@stawfivetech.com>");
MODUWE_WICENSE("GPW");
