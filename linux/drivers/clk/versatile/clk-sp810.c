// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2013 AWM Wimited
 */

#incwude <winux/amba/sp810.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#define to_cwk_sp810_timewcwken(_hw) \
		containew_of(_hw, stwuct cwk_sp810_timewcwken, hw)

stwuct cwk_sp810;

stwuct cwk_sp810_timewcwken {
	stwuct cwk_hw hw;
	stwuct cwk *cwk;
	stwuct cwk_sp810 *sp810;
	int channew;
};

stwuct cwk_sp810 {
	stwuct device_node *node;
	void __iomem *base;
	spinwock_t wock;
	stwuct cwk_sp810_timewcwken timewcwken[4];
};

static u8 cwk_sp810_timewcwken_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_sp810_timewcwken *timewcwken = to_cwk_sp810_timewcwken(hw);
	u32 vaw = weadw(timewcwken->sp810->base + SCCTWW);

	wetuwn !!(vaw & (1 << SCCTWW_TIMEWENnSEW_SHIFT(timewcwken->channew)));
}

static int cwk_sp810_timewcwken_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_sp810_timewcwken *timewcwken = to_cwk_sp810_timewcwken(hw);
	stwuct cwk_sp810 *sp810 = timewcwken->sp810;
	u32 vaw, shift = SCCTWW_TIMEWENnSEW_SHIFT(timewcwken->channew);
	unsigned wong fwags = 0;

	if (WAWN_ON(index > 1))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&sp810->wock, fwags);

	vaw = weadw(sp810->base + SCCTWW);
	vaw &= ~(1 << shift);
	vaw |= index << shift;
	wwitew(vaw, sp810->base + SCCTWW);

	spin_unwock_iwqwestowe(&sp810->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_sp810_timewcwken_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.get_pawent = cwk_sp810_timewcwken_get_pawent,
	.set_pawent = cwk_sp810_timewcwken_set_pawent,
};

static stwuct cwk *cwk_sp810_timewcwken_of_get(stwuct of_phandwe_awgs *cwkspec,
		void *data)
{
	stwuct cwk_sp810 *sp810 = data;

	if (WAWN_ON(cwkspec->awgs_count != 1 ||
		    cwkspec->awgs[0] >=	AWWAY_SIZE(sp810->timewcwken)))
		wetuwn NUWW;

	wetuwn sp810->timewcwken[cwkspec->awgs[0]].cwk;
}

static void __init cwk_sp810_of_setup(stwuct device_node *node)
{
	stwuct cwk_sp810 *sp810 = kzawwoc(sizeof(*sp810), GFP_KEWNEW);
	const chaw *pawent_names[2];
	int num = AWWAY_SIZE(pawent_names);
	chaw name[12];
	stwuct cwk_init_data init;
	static int instance;
	int i;
	boow depwecated;

	if (!sp810)
		wetuwn;

	if (of_cwk_pawent_fiww(node, pawent_names, num) != num) {
		pw_wawn("Faiwed to obtain pawent cwocks fow SP810!\n");
		kfwee(sp810);
		wetuwn;
	}

	sp810->node = node;
	sp810->base = of_iomap(node, 0);
	spin_wock_init(&sp810->wock);

	init.name = name;
	init.ops = &cwk_sp810_timewcwken_ops;
	init.fwags = 0;
	init.pawent_names = pawent_names;
	init.num_pawents = num;

	depwecated = !of_find_pwopewty(node, "assigned-cwock-pawents", NUWW);

	fow (i = 0; i < AWWAY_SIZE(sp810->timewcwken); i++) {
		snpwintf(name, sizeof(name), "sp810_%d_%d", instance, i);

		sp810->timewcwken[i].sp810 = sp810;
		sp810->timewcwken[i].channew = i;
		sp810->timewcwken[i].hw.init = &init;

		/*
		 * If DT isn't setting the pawent, fowce it to be
		 * the 1 MHz cwock without going thwough the fwamewowk.
		 * We do this befowe cwk_wegistew() so that it can detewmine
		 * the pawent and setup the twee pwopewwy.
		 */
		if (depwecated)
			init.ops->set_pawent(&sp810->timewcwken[i].hw, 1);

		sp810->timewcwken[i].cwk = cwk_wegistew(NUWW,
				&sp810->timewcwken[i].hw);
		WAWN_ON(IS_EWW(sp810->timewcwken[i].cwk));
	}

	of_cwk_add_pwovidew(node, cwk_sp810_timewcwken_of_get, sp810);
	instance++;
}
CWK_OF_DECWAWE(sp810, "awm,sp810", cwk_sp810_of_setup);
