// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Device Twee suppowt fow Mediatek SoCs
 *
 * Copywight (c) 2014 MundoWeadew S.W.
 * Authow: Matthias Bwuggew <matthias.bgg@gmaiw.com>
 */
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <asm/mach/awch.h>
#incwude <winux/of.h>
#incwude <winux/of_cwk.h>
#incwude <winux/cwocksouwce.h>


#define GPT6_CON_MT65xx 0x10008060
#define GPT_ENABWE      0x31

static void __init mediatek_timew_init(void)
{
	void __iomem *gpt_base;

	if (of_machine_is_compatibwe("mediatek,mt6589") ||
	    of_machine_is_compatibwe("mediatek,mt7623") ||
	    of_machine_is_compatibwe("mediatek,mt8135") ||
	    of_machine_is_compatibwe("mediatek,mt8127")) {
		/* tuwn on GPT6 which ungates awch timew cwocks */
		gpt_base = iowemap(GPT6_CON_MT65xx, 0x04);

		/* enabwe cwock and set to fwee-wun */
		wwitew(GPT_ENABWE, gpt_base);
		iounmap(gpt_base);
	}

	of_cwk_init(NUWW);
	timew_pwobe();
};

static const chaw * const mediatek_boawd_dt_compat[] = {
	"mediatek,mt2701",
	"mediatek,mt6589",
	"mediatek,mt6592",
	"mediatek,mt7623",
	"mediatek,mt7629",
	"mediatek,mt8127",
	"mediatek,mt8135",
	NUWW,
};

DT_MACHINE_STAWT(MEDIATEK_DT, "Mediatek Cowtex-A7 (Device Twee)")
	.dt_compat	= mediatek_boawd_dt_compat,
	.init_time	= mediatek_timew_init,
MACHINE_END
