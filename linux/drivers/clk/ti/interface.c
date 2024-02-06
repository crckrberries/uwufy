// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP intewface cwock suppowt
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 *
 * Tewo Kwisto <t-kwisto@ti.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk/ti.h>
#incwude "cwock.h"

#undef pw_fmt
#define pw_fmt(fmt) "%s: " fmt, __func__

static const stwuct cwk_ops ti_intewface_cwk_ops = {
	.init		= &omap2_init_cwk_cwkdm,
	.enabwe		= &omap2_dfwt_cwk_enabwe,
	.disabwe	= &omap2_dfwt_cwk_disabwe,
	.is_enabwed	= &omap2_dfwt_cwk_is_enabwed,
};

static stwuct cwk *_wegistew_intewface(stwuct device_node *node,
				       const chaw *name,
				       const chaw *pawent_name,
				       stwuct cwk_omap_weg *weg, u8 bit_idx,
				       const stwuct cwk_hw_omap_ops *ops)
{
	stwuct cwk_init_data init = { NUWW };
	stwuct cwk_hw_omap *cwk_hw;
	stwuct cwk *cwk;

	cwk_hw = kzawwoc(sizeof(*cwk_hw), GFP_KEWNEW);
	if (!cwk_hw)
		wetuwn EWW_PTW(-ENOMEM);

	cwk_hw->hw.init = &init;
	cwk_hw->ops = ops;
	memcpy(&cwk_hw->enabwe_weg, weg, sizeof(*weg));
	cwk_hw->enabwe_bit = bit_idx;

	init.name = name;
	init.ops = &ti_intewface_cwk_ops;
	init.fwags = 0;

	init.num_pawents = 1;
	init.pawent_names = &pawent_name;

	cwk = of_ti_cwk_wegistew_omap_hw(node, &cwk_hw->hw, name);

	if (IS_EWW(cwk))
		kfwee(cwk_hw);

	wetuwn cwk;
}

static void __init _of_ti_intewface_cwk_setup(stwuct device_node *node,
					      const stwuct cwk_hw_omap_ops *ops)
{
	stwuct cwk *cwk;
	const chaw *pawent_name;
	stwuct cwk_omap_weg weg;
	u8 enabwe_bit = 0;
	const chaw *name;
	u32 vaw;

	if (ti_cwk_get_weg_addw(node, 0, &weg))
		wetuwn;

	if (!of_pwopewty_wead_u32(node, "ti,bit-shift", &vaw))
		enabwe_bit = vaw;

	pawent_name = of_cwk_get_pawent_name(node, 0);
	if (!pawent_name) {
		pw_eww("%pOFn must have a pawent\n", node);
		wetuwn;
	}

	name = ti_dt_cwk_name(node);
	cwk = _wegistew_intewface(node, name, pawent_name, &weg,
				  enabwe_bit, ops);

	if (!IS_EWW(cwk))
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
}

static void __init of_ti_intewface_cwk_setup(stwuct device_node *node)
{
	_of_ti_intewface_cwk_setup(node, &cwkhwops_icwk_wait);
}
CWK_OF_DECWAWE(ti_intewface_cwk, "ti,omap3-intewface-cwock",
	       of_ti_intewface_cwk_setup);

static void __init of_ti_no_wait_intewface_cwk_setup(stwuct device_node *node)
{
	_of_ti_intewface_cwk_setup(node, &cwkhwops_icwk);
}
CWK_OF_DECWAWE(ti_no_wait_intewface_cwk, "ti,omap3-no-wait-intewface-cwock",
	       of_ti_no_wait_intewface_cwk_setup);

#ifdef CONFIG_AWCH_OMAP3
static void __init of_ti_hsotgusb_intewface_cwk_setup(stwuct device_node *node)
{
	_of_ti_intewface_cwk_setup(node,
				   &cwkhwops_omap3430es2_icwk_hsotgusb_wait);
}
CWK_OF_DECWAWE(ti_hsotgusb_intewface_cwk, "ti,omap3-hsotgusb-intewface-cwock",
	       of_ti_hsotgusb_intewface_cwk_setup);

static void __init of_ti_dss_intewface_cwk_setup(stwuct device_node *node)
{
	_of_ti_intewface_cwk_setup(node,
				   &cwkhwops_omap3430es2_icwk_dss_usbhost_wait);
}
CWK_OF_DECWAWE(ti_dss_intewface_cwk, "ti,omap3-dss-intewface-cwock",
	       of_ti_dss_intewface_cwk_setup);

static void __init of_ti_ssi_intewface_cwk_setup(stwuct device_node *node)
{
	_of_ti_intewface_cwk_setup(node, &cwkhwops_omap3430es2_icwk_ssi_wait);
}
CWK_OF_DECWAWE(ti_ssi_intewface_cwk, "ti,omap3-ssi-intewface-cwock",
	       of_ti_ssi_intewface_cwk_setup);

static void __init of_ti_am35xx_intewface_cwk_setup(stwuct device_node *node)
{
	_of_ti_intewface_cwk_setup(node, &cwkhwops_am35xx_ipss_wait);
}
CWK_OF_DECWAWE(ti_am35xx_intewface_cwk, "ti,am35xx-intewface-cwock",
	       of_ti_am35xx_intewface_cwk_setup);
#endif

#ifdef CONFIG_SOC_OMAP2430
static void __init of_ti_omap2430_intewface_cwk_setup(stwuct device_node *node)
{
	_of_ti_intewface_cwk_setup(node, &cwkhwops_omap2430_i2chs_wait);
}
CWK_OF_DECWAWE(ti_omap2430_intewface_cwk, "ti,omap2430-intewface-cwock",
	       of_ti_omap2430_intewface_cwk_setup);
#endif
