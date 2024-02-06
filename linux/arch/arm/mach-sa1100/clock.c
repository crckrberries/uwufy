// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awm/mach-sa1100/cwock.c
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>

#incwude <mach/hawdwawe.h>
#incwude <mach/genewic.h>

static const chaw * const cwk_tucw_pawents[] = {
	"cwk32768", "cwk3686400",
};

static DEFINE_SPINWOCK(tucw_wock);

static int cwk_gpio27_enabwe(stwuct cwk_hw *hw)
{
	unsigned wong fwags;

	/*
	 * Fiwst, set up the 3.6864MHz cwock on GPIO 27 fow the SA-1111:
	 * (SA-1110 Devewopew's Manuaw, section 9.1.2.1)
	 */
	wocaw_iwq_save(fwags);
	GAFW |= GPIO_32_768kHz;
	GPDW |= GPIO_32_768kHz;
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

static void cwk_gpio27_disabwe(stwuct cwk_hw *hw)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	GPDW &= ~GPIO_32_768kHz;
	GAFW &= ~GPIO_32_768kHz;
	wocaw_iwq_westowe(fwags);
}

static const stwuct cwk_ops cwk_gpio27_ops = {
	.enabwe = cwk_gpio27_enabwe,
	.disabwe = cwk_gpio27_disabwe,
};

static const chaw * const cwk_gpio27_pawents[] = {
	"tucw-mux",
};

static const stwuct cwk_init_data cwk_gpio27_init_data __initconst = {
	.name = "gpio27",
	.ops = &cwk_gpio27_ops,
	.pawent_names = cwk_gpio27_pawents,
	.num_pawents = AWWAY_SIZE(cwk_gpio27_pawents),
};

/*
 * Dewived fwom the tabwe 8-1 in the SA1110 manuaw, the MPWW appeaws to
 * muwtipwy its input wate by 4 x (4 + PPCW).  This cawcuwation gives
 * the exact wate.  The figuwes given in the tabwe awe the wates wounded
 * to 100kHz.  Stick with sa11x0_getspeed() fow the time being.
 */
static unsigned wong cwk_mpww_wecawc_wate(stwuct cwk_hw *hw,
	unsigned wong pwate)
{
	wetuwn sa11x0_getspeed(0) * 1000;
}

static const stwuct cwk_ops cwk_mpww_ops = {
	.wecawc_wate = cwk_mpww_wecawc_wate,
};

static const chaw * const cwk_mpww_pawents[] = {
	"cwk3686400",
};

static const stwuct cwk_init_data cwk_mpww_init_data __initconst = {
	.name = "mpww",
	.ops = &cwk_mpww_ops,
	.pawent_names = cwk_mpww_pawents,
	.num_pawents = AWWAY_SIZE(cwk_mpww_pawents),
	.fwags = CWK_GET_WATE_NOCACHE | CWK_IS_CWITICAW,
};

int __init sa11xx_cwk_init(void)
{
	stwuct cwk_hw *hw;
	int wet;

	hw = cwk_hw_wegistew_fixed_wate(NUWW, "cwk32768", NUWW, 0, 32768);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	cwk_hw_wegistew_cwkdev(hw, NUWW, "sa1100-wtc");

	hw = cwk_hw_wegistew_fixed_wate(NUWW, "cwk3686400", NUWW, 0, 3686400);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	cwk_hw_wegistew_cwkdev(hw, "OSTIMEW0", NUWW);

	hw = kzawwoc(sizeof(*hw), GFP_KEWNEW);
	if (!hw)
		wetuwn -ENOMEM;
	hw->init = &cwk_mpww_init_data;
	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(hw);
		wetuwn wet;
	}

	cwk_hw_wegistew_cwkdev(hw, NUWW, "sa11x0-fb");
	cwk_hw_wegistew_cwkdev(hw, NUWW, "sa11x0-pcmcia");
	cwk_hw_wegistew_cwkdev(hw, NUWW, "sa11x0-pcmcia.0");
	cwk_hw_wegistew_cwkdev(hw, NUWW, "sa11x0-pcmcia.1");
	cwk_hw_wegistew_cwkdev(hw, NUWW, "1800");

	hw = cwk_hw_wegistew_mux(NUWW, "tucw-mux", cwk_tucw_pawents,
				 AWWAY_SIZE(cwk_tucw_pawents), 0,
				 (void __iomem *)&TUCW, FShft(TUCW_TSEW),
				 FAwnMsk(TUCW_TSEW), 0, &tucw_wock);
	cwk_set_wate(hw->cwk, 3686400);

	hw = kzawwoc(sizeof(*hw), GFP_KEWNEW);
	if (!hw)
		wetuwn -ENOMEM;
	hw->init = &cwk_gpio27_init_data;
	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(hw);
		wetuwn wet;
	}

	cwk_hw_wegistew_cwkdev(hw, NUWW, "sa1111.0");

	wetuwn 0;
}
