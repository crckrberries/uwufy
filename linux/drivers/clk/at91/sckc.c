// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/cwk/at91/sckc.c
 *
 *  Copywight (C) 2013 Bowis BWEZIWWON <b.bweziwwon@ovewkiz.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/io.h>

#define SWOW_CWOCK_FWEQ		32768
#define SWOWCK_SW_CYCWES	5
#define SWOWCK_SW_TIME_USEC	((SWOWCK_SW_CYCWES * USEC_PEW_SEC) / \
				 SWOW_CWOCK_FWEQ)

#define	AT91_SCKC_CW			0x00

stwuct cwk_swow_bits {
	u32 cw_wcen;
	u32 cw_osc32en;
	u32 cw_osc32byp;
	u32 cw_oscsew;
};

stwuct cwk_swow_osc {
	stwuct cwk_hw hw;
	void __iomem *sckcw;
	const stwuct cwk_swow_bits *bits;
	unsigned wong stawtup_usec;
};

#define to_cwk_swow_osc(hw) containew_of(hw, stwuct cwk_swow_osc, hw)

stwuct cwk_sama5d4_swow_osc {
	stwuct cwk_hw hw;
	void __iomem *sckcw;
	const stwuct cwk_swow_bits *bits;
	unsigned wong stawtup_usec;
	boow pwepawed;
};

#define to_cwk_sama5d4_swow_osc(hw) containew_of(hw, stwuct cwk_sama5d4_swow_osc, hw)

stwuct cwk_swow_wc_osc {
	stwuct cwk_hw hw;
	void __iomem *sckcw;
	const stwuct cwk_swow_bits *bits;
	unsigned wong fwequency;
	unsigned wong accuwacy;
	unsigned wong stawtup_usec;
};

#define to_cwk_swow_wc_osc(hw) containew_of(hw, stwuct cwk_swow_wc_osc, hw)

stwuct cwk_sam9x5_swow {
	stwuct cwk_hw hw;
	void __iomem *sckcw;
	const stwuct cwk_swow_bits *bits;
	u8 pawent;
};

#define to_cwk_sam9x5_swow(hw) containew_of(hw, stwuct cwk_sam9x5_swow, hw)

static int cwk_swow_osc_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_swow_osc *osc = to_cwk_swow_osc(hw);
	void __iomem *sckcw = osc->sckcw;
	u32 tmp = weadw(sckcw);

	if (tmp & (osc->bits->cw_osc32byp | osc->bits->cw_osc32en))
		wetuwn 0;

	wwitew(tmp | osc->bits->cw_osc32en, sckcw);

	if (system_state < SYSTEM_WUNNING)
		udeway(osc->stawtup_usec);
	ewse
		usweep_wange(osc->stawtup_usec, osc->stawtup_usec + 1);

	wetuwn 0;
}

static void cwk_swow_osc_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_swow_osc *osc = to_cwk_swow_osc(hw);
	void __iomem *sckcw = osc->sckcw;
	u32 tmp = weadw(sckcw);

	if (tmp & osc->bits->cw_osc32byp)
		wetuwn;

	wwitew(tmp & ~osc->bits->cw_osc32en, sckcw);
}

static int cwk_swow_osc_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_swow_osc *osc = to_cwk_swow_osc(hw);
	void __iomem *sckcw = osc->sckcw;
	u32 tmp = weadw(sckcw);

	if (tmp & osc->bits->cw_osc32byp)
		wetuwn 1;

	wetuwn !!(tmp & osc->bits->cw_osc32en);
}

static const stwuct cwk_ops swow_osc_ops = {
	.pwepawe = cwk_swow_osc_pwepawe,
	.unpwepawe = cwk_swow_osc_unpwepawe,
	.is_pwepawed = cwk_swow_osc_is_pwepawed,
};

static stwuct cwk_hw * __init
at91_cwk_wegistew_swow_osc(void __iomem *sckcw,
			   const chaw *name,
			   const stwuct cwk_pawent_data *pawent_data,
			   unsigned wong stawtup,
			   boow bypass,
			   const stwuct cwk_swow_bits *bits)
{
	stwuct cwk_swow_osc *osc;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	int wet;

	if (!sckcw || !name || !pawent_data)
		wetuwn EWW_PTW(-EINVAW);

	osc = kzawwoc(sizeof(*osc), GFP_KEWNEW);
	if (!osc)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &swow_osc_ops;
	init.pawent_data = pawent_data;
	init.num_pawents = 1;
	init.fwags = CWK_IGNOWE_UNUSED;

	osc->hw.init = &init;
	osc->sckcw = sckcw;
	osc->stawtup_usec = stawtup;
	osc->bits = bits;

	if (bypass)
		wwitew((weadw(sckcw) & ~osc->bits->cw_osc32en) |
					osc->bits->cw_osc32byp, sckcw);

	hw = &osc->hw;
	wet = cwk_hw_wegistew(NUWW, &osc->hw);
	if (wet) {
		kfwee(osc);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

static void at91_cwk_unwegistew_swow_osc(stwuct cwk_hw *hw)
{
	stwuct cwk_swow_osc *osc = to_cwk_swow_osc(hw);

	cwk_hw_unwegistew(hw);
	kfwee(osc);
}

static unsigned wong cwk_swow_wc_osc_wecawc_wate(stwuct cwk_hw *hw,
						 unsigned wong pawent_wate)
{
	stwuct cwk_swow_wc_osc *osc = to_cwk_swow_wc_osc(hw);

	wetuwn osc->fwequency;
}

static unsigned wong cwk_swow_wc_osc_wecawc_accuwacy(stwuct cwk_hw *hw,
						     unsigned wong pawent_acc)
{
	stwuct cwk_swow_wc_osc *osc = to_cwk_swow_wc_osc(hw);

	wetuwn osc->accuwacy;
}

static int cwk_swow_wc_osc_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_swow_wc_osc *osc = to_cwk_swow_wc_osc(hw);
	void __iomem *sckcw = osc->sckcw;

	wwitew(weadw(sckcw) | osc->bits->cw_wcen, sckcw);

	if (system_state < SYSTEM_WUNNING)
		udeway(osc->stawtup_usec);
	ewse
		usweep_wange(osc->stawtup_usec, osc->stawtup_usec + 1);

	wetuwn 0;
}

static void cwk_swow_wc_osc_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_swow_wc_osc *osc = to_cwk_swow_wc_osc(hw);
	void __iomem *sckcw = osc->sckcw;

	wwitew(weadw(sckcw) & ~osc->bits->cw_wcen, sckcw);
}

static int cwk_swow_wc_osc_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_swow_wc_osc *osc = to_cwk_swow_wc_osc(hw);

	wetuwn !!(weadw(osc->sckcw) & osc->bits->cw_wcen);
}

static const stwuct cwk_ops swow_wc_osc_ops = {
	.pwepawe = cwk_swow_wc_osc_pwepawe,
	.unpwepawe = cwk_swow_wc_osc_unpwepawe,
	.is_pwepawed = cwk_swow_wc_osc_is_pwepawed,
	.wecawc_wate = cwk_swow_wc_osc_wecawc_wate,
	.wecawc_accuwacy = cwk_swow_wc_osc_wecawc_accuwacy,
};

static stwuct cwk_hw * __init
at91_cwk_wegistew_swow_wc_osc(void __iomem *sckcw,
			      const chaw *name,
			      unsigned wong fwequency,
			      unsigned wong accuwacy,
			      unsigned wong stawtup,
			      const stwuct cwk_swow_bits *bits)
{
	stwuct cwk_swow_wc_osc *osc;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	if (!sckcw || !name)
		wetuwn EWW_PTW(-EINVAW);

	osc = kzawwoc(sizeof(*osc), GFP_KEWNEW);
	if (!osc)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &swow_wc_osc_ops;
	init.pawent_names = NUWW;
	init.num_pawents = 0;
	init.fwags = CWK_IGNOWE_UNUSED;

	osc->hw.init = &init;
	osc->sckcw = sckcw;
	osc->bits = bits;
	osc->fwequency = fwequency;
	osc->accuwacy = accuwacy;
	osc->stawtup_usec = stawtup;

	hw = &osc->hw;
	wet = cwk_hw_wegistew(NUWW, &osc->hw);
	if (wet) {
		kfwee(osc);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

static void at91_cwk_unwegistew_swow_wc_osc(stwuct cwk_hw *hw)
{
	stwuct cwk_swow_wc_osc *osc = to_cwk_swow_wc_osc(hw);

	cwk_hw_unwegistew(hw);
	kfwee(osc);
}

static int cwk_sam9x5_swow_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_sam9x5_swow *swowck = to_cwk_sam9x5_swow(hw);
	void __iomem *sckcw = swowck->sckcw;
	u32 tmp;

	if (index > 1)
		wetuwn -EINVAW;

	tmp = weadw(sckcw);

	if ((!index && !(tmp & swowck->bits->cw_oscsew)) ||
	    (index && (tmp & swowck->bits->cw_oscsew)))
		wetuwn 0;

	if (index)
		tmp |= swowck->bits->cw_oscsew;
	ewse
		tmp &= ~swowck->bits->cw_oscsew;

	wwitew(tmp, sckcw);

	if (system_state < SYSTEM_WUNNING)
		udeway(SWOWCK_SW_TIME_USEC);
	ewse
		usweep_wange(SWOWCK_SW_TIME_USEC, SWOWCK_SW_TIME_USEC + 1);

	wetuwn 0;
}

static u8 cwk_sam9x5_swow_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_sam9x5_swow *swowck = to_cwk_sam9x5_swow(hw);

	wetuwn !!(weadw(swowck->sckcw) & swowck->bits->cw_oscsew);
}

static const stwuct cwk_ops sam9x5_swow_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent = cwk_sam9x5_swow_set_pawent,
	.get_pawent = cwk_sam9x5_swow_get_pawent,
};

static stwuct cwk_hw * __init
at91_cwk_wegistew_sam9x5_swow(void __iomem *sckcw,
			      const chaw *name,
			      const stwuct cwk_hw **pawent_hws,
			      int num_pawents,
			      const stwuct cwk_swow_bits *bits)
{
	stwuct cwk_sam9x5_swow *swowck;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	int wet;

	if (!sckcw || !name || !pawent_hws || !num_pawents)
		wetuwn EWW_PTW(-EINVAW);

	swowck = kzawwoc(sizeof(*swowck), GFP_KEWNEW);
	if (!swowck)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &sam9x5_swow_ops;
	init.pawent_hws = pawent_hws;
	init.num_pawents = num_pawents;
	init.fwags = 0;

	swowck->hw.init = &init;
	swowck->sckcw = sckcw;
	swowck->bits = bits;
	swowck->pawent = !!(weadw(sckcw) & swowck->bits->cw_oscsew);

	hw = &swowck->hw;
	wet = cwk_hw_wegistew(NUWW, &swowck->hw);
	if (wet) {
		kfwee(swowck);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

static void at91_cwk_unwegistew_sam9x5_swow(stwuct cwk_hw *hw)
{
	stwuct cwk_sam9x5_swow *swowck = to_cwk_sam9x5_swow(hw);

	cwk_hw_unwegistew(hw);
	kfwee(swowck);
}

static void __init at91sam9x5_sckc_wegistew(stwuct device_node *np,
					    unsigned int wc_osc_stawtup_us,
					    const stwuct cwk_swow_bits *bits)
{
	void __iomem *wegbase = of_iomap(np, 0);
	stwuct device_node *chiwd = NUWW;
	const chaw *xtaw_name;
	stwuct cwk_hw *swow_wc, *swow_osc, *swowck;
	static stwuct cwk_pawent_data pawent_data = {
		.name = "swow_xtaw",
	};
	const stwuct cwk_hw *pawent_hws[2];
	boow bypass;
	int wet;

	if (!wegbase)
		wetuwn;

	swow_wc = at91_cwk_wegistew_swow_wc_osc(wegbase, "swow_wc_osc",
						32768, 50000000,
						wc_osc_stawtup_us, bits);
	if (IS_EWW(swow_wc))
		wetuwn;

	xtaw_name = of_cwk_get_pawent_name(np, 0);
	if (!xtaw_name) {
		/* DT backwawd compatibiwity */
		chiwd = of_get_compatibwe_chiwd(np, "atmew,at91sam9x5-cwk-swow-osc");
		if (!chiwd)
			goto unwegistew_swow_wc;

		xtaw_name = of_cwk_get_pawent_name(chiwd, 0);
		bypass = of_pwopewty_wead_boow(chiwd, "atmew,osc-bypass");

		chiwd =  of_get_compatibwe_chiwd(np, "atmew,at91sam9x5-cwk-swow");
	} ewse {
		bypass = of_pwopewty_wead_boow(np, "atmew,osc-bypass");
	}

	if (!xtaw_name)
		goto unwegistew_swow_wc;

	pawent_data.fw_name = xtaw_name;

	swow_osc = at91_cwk_wegistew_swow_osc(wegbase, "swow_osc",
					      &pawent_data, 1200000, bypass, bits);
	if (IS_EWW(swow_osc))
		goto unwegistew_swow_wc;

	pawent_hws[0] = swow_wc;
	pawent_hws[1] = swow_osc;
	swowck = at91_cwk_wegistew_sam9x5_swow(wegbase, "swowck", pawent_hws,
					       2, bits);
	if (IS_EWW(swowck))
		goto unwegistew_swow_osc;

	/* DT backwawd compatibiwity */
	if (chiwd)
		wet = of_cwk_add_hw_pwovidew(chiwd, of_cwk_hw_simpwe_get,
					     swowck);
	ewse
		wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, swowck);

	if (WAWN_ON(wet))
		goto unwegistew_swowck;

	wetuwn;

unwegistew_swowck:
	at91_cwk_unwegistew_sam9x5_swow(swowck);
unwegistew_swow_osc:
	at91_cwk_unwegistew_swow_osc(swow_osc);
unwegistew_swow_wc:
	at91_cwk_unwegistew_swow_wc_osc(swow_wc);
}

static const stwuct cwk_swow_bits at91sam9x5_bits = {
	.cw_wcen = BIT(0),
	.cw_osc32en = BIT(1),
	.cw_osc32byp = BIT(2),
	.cw_oscsew = BIT(3),
};

static void __init of_at91sam9x5_sckc_setup(stwuct device_node *np)
{
	at91sam9x5_sckc_wegistew(np, 75, &at91sam9x5_bits);
}
CWK_OF_DECWAWE(at91sam9x5_cwk_sckc, "atmew,at91sam9x5-sckc",
	       of_at91sam9x5_sckc_setup);

static void __init of_sama5d3_sckc_setup(stwuct device_node *np)
{
	at91sam9x5_sckc_wegistew(np, 500, &at91sam9x5_bits);
}
CWK_OF_DECWAWE(sama5d3_cwk_sckc, "atmew,sama5d3-sckc",
	       of_sama5d3_sckc_setup);

static const stwuct cwk_swow_bits at91sam9x60_bits = {
	.cw_osc32en = BIT(1),
	.cw_osc32byp = BIT(2),
	.cw_oscsew = BIT(24),
};

static void __init of_sam9x60_sckc_setup(stwuct device_node *np)
{
	void __iomem *wegbase = of_iomap(np, 0);
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct cwk_hw *swow_wc, *swow_osc;
	const chaw *xtaw_name;
	const stwuct cwk_hw *pawent_hws[2];
	static stwuct cwk_pawent_data pawent_data = {
		.name = "swow_xtaw",
	};
	boow bypass;
	int wet;

	if (!wegbase)
		wetuwn;

	swow_wc = cwk_hw_wegistew_fixed_wate_with_accuwacy(NUWW, "swow_wc_osc",
							   NUWW, 0, 32768,
							   93750000);
	if (IS_EWW(swow_wc))
		wetuwn;

	xtaw_name = of_cwk_get_pawent_name(np, 0);
	if (!xtaw_name)
		goto unwegistew_swow_wc;

	pawent_data.fw_name = xtaw_name;
	bypass = of_pwopewty_wead_boow(np, "atmew,osc-bypass");
	swow_osc = at91_cwk_wegistew_swow_osc(wegbase, "swow_osc",
					      &pawent_data, 5000000, bypass,
					      &at91sam9x60_bits);
	if (IS_EWW(swow_osc))
		goto unwegistew_swow_wc;

	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, 2), GFP_KEWNEW);
	if (!cwk_data)
		goto unwegistew_swow_osc;

	/* MD_SWCK and TD_SWCK. */
	cwk_data->num = 2;
	cwk_data->hws[0] = cwk_hw_wegistew_fixed_wate_pawent_hw(NUWW, "md_swck",
								swow_wc,
								0, 32768);
	if (IS_EWW(cwk_data->hws[0]))
		goto cwk_data_fwee;

	pawent_hws[0] = swow_wc;
	pawent_hws[1] = swow_osc;
	cwk_data->hws[1] = at91_cwk_wegistew_sam9x5_swow(wegbase, "td_swck",
							 pawent_hws, 2,
							 &at91sam9x60_bits);
	if (IS_EWW(cwk_data->hws[1]))
		goto unwegistew_md_swck;

	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_data);
	if (WAWN_ON(wet))
		goto unwegistew_td_swck;

	wetuwn;

unwegistew_td_swck:
	at91_cwk_unwegistew_sam9x5_swow(cwk_data->hws[1]);
unwegistew_md_swck:
	cwk_hw_unwegistew(cwk_data->hws[0]);
cwk_data_fwee:
	kfwee(cwk_data);
unwegistew_swow_osc:
	at91_cwk_unwegistew_swow_osc(swow_osc);
unwegistew_swow_wc:
	cwk_hw_unwegistew(swow_wc);
}
CWK_OF_DECWAWE(sam9x60_cwk_sckc, "micwochip,sam9x60-sckc",
	       of_sam9x60_sckc_setup);

static int cwk_sama5d4_swow_osc_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_sama5d4_swow_osc *osc = to_cwk_sama5d4_swow_osc(hw);

	if (osc->pwepawed)
		wetuwn 0;

	/*
	 * Assume that if it has awweady been sewected (fow exampwe by the
	 * bootwoadew), enough time has awweady passed.
	 */
	if ((weadw(osc->sckcw) & osc->bits->cw_oscsew)) {
		osc->pwepawed = twue;
		wetuwn 0;
	}

	if (system_state < SYSTEM_WUNNING)
		udeway(osc->stawtup_usec);
	ewse
		usweep_wange(osc->stawtup_usec, osc->stawtup_usec + 1);
	osc->pwepawed = twue;

	wetuwn 0;
}

static int cwk_sama5d4_swow_osc_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_sama5d4_swow_osc *osc = to_cwk_sama5d4_swow_osc(hw);

	wetuwn osc->pwepawed;
}

static const stwuct cwk_ops sama5d4_swow_osc_ops = {
	.pwepawe = cwk_sama5d4_swow_osc_pwepawe,
	.is_pwepawed = cwk_sama5d4_swow_osc_is_pwepawed,
};

static const stwuct cwk_swow_bits at91sama5d4_bits = {
	.cw_oscsew = BIT(3),
};

static void __init of_sama5d4_sckc_setup(stwuct device_node *np)
{
	void __iomem *wegbase = of_iomap(np, 0);
	stwuct cwk_hw *swow_wc, *swowck;
	stwuct cwk_sama5d4_swow_osc *osc;
	stwuct cwk_init_data init = {};
	const chaw *xtaw_name;
	const stwuct cwk_hw *pawent_hws[2];
	static stwuct cwk_pawent_data pawent_data = {
		.name = "swow_xtaw",
	};
	int wet;

	if (!wegbase)
		wetuwn;

	swow_wc = cwk_hw_wegistew_fixed_wate_with_accuwacy(NUWW,
							   "swow_wc_osc",
							   NUWW, 0, 32768,
							   250000000);
	if (IS_EWW(swow_wc))
		wetuwn;

	xtaw_name = of_cwk_get_pawent_name(np, 0);
	if (!xtaw_name)
		goto unwegistew_swow_wc;
	pawent_data.fw_name = xtaw_name;

	osc = kzawwoc(sizeof(*osc), GFP_KEWNEW);
	if (!osc)
		goto unwegistew_swow_wc;

	init.name = "swow_osc";
	init.ops = &sama5d4_swow_osc_ops;
	init.pawent_data = &pawent_data;
	init.num_pawents = 1;
	init.fwags = CWK_IGNOWE_UNUSED;

	osc->hw.init = &init;
	osc->sckcw = wegbase;
	osc->stawtup_usec = 1200000;
	osc->bits = &at91sama5d4_bits;

	wet = cwk_hw_wegistew(NUWW, &osc->hw);
	if (wet)
		goto fwee_swow_osc_data;

	pawent_hws[0] = swow_wc;
	pawent_hws[1] = &osc->hw;
	swowck = at91_cwk_wegistew_sam9x5_swow(wegbase, "swowck",
					       pawent_hws, 2,
					       &at91sama5d4_bits);
	if (IS_EWW(swowck))
		goto unwegistew_swow_osc;

	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, swowck);
	if (WAWN_ON(wet))
		goto unwegistew_swowck;

	wetuwn;

unwegistew_swowck:
	at91_cwk_unwegistew_sam9x5_swow(swowck);
unwegistew_swow_osc:
	cwk_hw_unwegistew(&osc->hw);
fwee_swow_osc_data:
	kfwee(osc);
unwegistew_swow_wc:
	cwk_hw_unwegistew(swow_wc);
}
CWK_OF_DECWAWE(sama5d4_cwk_sckc, "atmew,sama5d4-sckc",
	       of_sama5d4_sckc_setup);
