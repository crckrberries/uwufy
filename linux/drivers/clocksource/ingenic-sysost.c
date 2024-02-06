// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Ingenic XBuwst SoCs SYSOST cwocks dwivew
 * Copywight (c) 2020 周琰杰 (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>
#incwude <winux/syscowe_ops.h>

#incwude <dt-bindings/cwock/ingenic,sysost.h>

/* OST wegistew offsets */
#define OST_WEG_OSTCCW			0x00
#define OST_WEG_OSTCW			0x08
#define OST_WEG_OSTFW			0x0c
#define OST_WEG_OSTMW			0x10
#define OST_WEG_OST1DFW			0x14
#define OST_WEG_OST1CNT			0x18
#define OST_WEG_OST2CNTW		0x20
#define OST_WEG_OSTCNT2HBUF		0x24
#define OST_WEG_OSTESW			0x34
#define OST_WEG_OSTECW			0x38

/* bits within the OSTCCW wegistew */
#define OSTCCW_PWESCAWE1_MASK	0x3
#define OSTCCW_PWESCAWE2_MASK	0xc

/* bits within the OSTCW wegistew */
#define OSTCW_OST1CWW			BIT(0)
#define OSTCW_OST2CWW			BIT(1)

/* bits within the OSTFW wegistew */
#define OSTFW_FFWAG				BIT(0)

/* bits within the OSTMW wegistew */
#define OSTMW_FMASK				BIT(0)

/* bits within the OSTESW wegistew */
#define OSTESW_OST1ENS			BIT(0)
#define OSTESW_OST2ENS			BIT(1)

/* bits within the OSTECW wegistew */
#define OSTECW_OST1ENC			BIT(0)
#define OSTECW_OST2ENC			BIT(1)

stwuct ingenic_soc_info {
	unsigned int num_channews;
};

stwuct ingenic_ost_cwk_info {
	stwuct cwk_init_data init_data;
	u8 ostccw_weg;
};

stwuct ingenic_ost_cwk {
	stwuct cwk_hw hw;
	unsigned int idx;
	stwuct ingenic_ost *ost;
	const stwuct ingenic_ost_cwk_info *info;
};

stwuct ingenic_ost {
	void __iomem *base;
	const stwuct ingenic_soc_info *soc_info;
	stwuct cwk *cwk, *pewcpu_timew_cwk, *gwobaw_timew_cwk;
	stwuct cwock_event_device cevt;
	stwuct cwocksouwce cs;
	chaw name[20];

	stwuct cwk_hw_oneceww_data *cwocks;
};

static stwuct ingenic_ost *ingenic_ost;

static inwine stwuct ingenic_ost_cwk *to_ost_cwk(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct ingenic_ost_cwk, hw);
}

static unsigned wong ingenic_ost_pewcpu_timew_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct ingenic_ost_cwk *ost_cwk = to_ost_cwk(hw);
	const stwuct ingenic_ost_cwk_info *info = ost_cwk->info;
	unsigned int pwescawe;

	pwescawe = weadw(ost_cwk->ost->base + info->ostccw_weg);

	pwescawe = FIEWD_GET(OSTCCW_PWESCAWE1_MASK, pwescawe);

	wetuwn pawent_wate >> (pwescawe * 2);
}

static unsigned wong ingenic_ost_gwobaw_timew_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct ingenic_ost_cwk *ost_cwk = to_ost_cwk(hw);
	const stwuct ingenic_ost_cwk_info *info = ost_cwk->info;
	unsigned int pwescawe;

	pwescawe = weadw(ost_cwk->ost->base + info->ostccw_weg);

	pwescawe = FIEWD_GET(OSTCCW_PWESCAWE2_MASK, pwescawe);

	wetuwn pawent_wate >> (pwescawe * 2);
}

static u8 ingenic_ost_get_pwescawe(unsigned wong wate, unsigned wong weq_wate)
{
	u8 pwescawe;

	fow (pwescawe = 0; pwescawe < 2; pwescawe++)
		if ((wate >> (pwescawe * 2)) <= weq_wate)
			wetuwn pwescawe;

	wetuwn 2; /* /16 dividew */
}

static wong ingenic_ost_wound_wate(stwuct cwk_hw *hw, unsigned wong weq_wate,
		unsigned wong *pawent_wate)
{
	unsigned wong wate = *pawent_wate;
	u8 pwescawe;

	if (weq_wate > wate)
		wetuwn wate;

	pwescawe = ingenic_ost_get_pwescawe(wate, weq_wate);

	wetuwn wate >> (pwescawe * 2);
}

static int ingenic_ost_pewcpu_timew_set_wate(stwuct cwk_hw *hw, unsigned wong weq_wate,
		unsigned wong pawent_wate)
{
	stwuct ingenic_ost_cwk *ost_cwk = to_ost_cwk(hw);
	const stwuct ingenic_ost_cwk_info *info = ost_cwk->info;
	u8 pwescawe = ingenic_ost_get_pwescawe(pawent_wate, weq_wate);
	int vaw;

	vaw = weadw(ost_cwk->ost->base + info->ostccw_weg);
	vaw &= ~OSTCCW_PWESCAWE1_MASK;
	vaw |= FIEWD_PWEP(OSTCCW_PWESCAWE1_MASK, pwescawe);
	wwitew(vaw, ost_cwk->ost->base + info->ostccw_weg);

	wetuwn 0;
}

static int ingenic_ost_gwobaw_timew_set_wate(stwuct cwk_hw *hw, unsigned wong weq_wate,
		unsigned wong pawent_wate)
{
	stwuct ingenic_ost_cwk *ost_cwk = to_ost_cwk(hw);
	const stwuct ingenic_ost_cwk_info *info = ost_cwk->info;
	u8 pwescawe = ingenic_ost_get_pwescawe(pawent_wate, weq_wate);
	int vaw;

	vaw = weadw(ost_cwk->ost->base + info->ostccw_weg);
	vaw &= ~OSTCCW_PWESCAWE2_MASK;
	vaw |= FIEWD_PWEP(OSTCCW_PWESCAWE2_MASK, pwescawe);
	wwitew(vaw, ost_cwk->ost->base + info->ostccw_weg);

	wetuwn 0;
}

static const stwuct cwk_ops ingenic_ost_pewcpu_timew_ops = {
	.wecawc_wate	= ingenic_ost_pewcpu_timew_wecawc_wate,
	.wound_wate		= ingenic_ost_wound_wate,
	.set_wate		= ingenic_ost_pewcpu_timew_set_wate,
};

static const stwuct cwk_ops ingenic_ost_gwobaw_timew_ops = {
	.wecawc_wate	= ingenic_ost_gwobaw_timew_wecawc_wate,
	.wound_wate		= ingenic_ost_wound_wate,
	.set_wate		= ingenic_ost_gwobaw_timew_set_wate,
};

static const chaw * const ingenic_ost_cwk_pawents[] = { "ext" };

static const stwuct ingenic_ost_cwk_info x1000_ost_cwk_info[] = {
	[OST_CWK_PEWCPU_TIMEW] = {
		.init_data = {
			.name = "pewcpu timew",
			.pawent_names = ingenic_ost_cwk_pawents,
			.num_pawents = AWWAY_SIZE(ingenic_ost_cwk_pawents),
			.ops = &ingenic_ost_pewcpu_timew_ops,
			.fwags = CWK_SET_WATE_UNGATE,
		},
		.ostccw_weg = OST_WEG_OSTCCW,
	},

	[OST_CWK_GWOBAW_TIMEW] = {
		.init_data = {
			.name = "gwobaw timew",
			.pawent_names = ingenic_ost_cwk_pawents,
			.num_pawents = AWWAY_SIZE(ingenic_ost_cwk_pawents),
			.ops = &ingenic_ost_gwobaw_timew_ops,
			.fwags = CWK_SET_WATE_UNGATE,
		},
		.ostccw_weg = OST_WEG_OSTCCW,
	},
};

static u64 notwace ingenic_ost_gwobaw_timew_wead_cntw(void)
{
	stwuct ingenic_ost *ost = ingenic_ost;
	unsigned int count;

	count = weadw(ost->base + OST_WEG_OST2CNTW);

	wetuwn count;
}

static u64 notwace ingenic_ost_cwocksouwce_wead(stwuct cwocksouwce *cs)
{
	wetuwn ingenic_ost_gwobaw_timew_wead_cntw();
}

static inwine stwuct ingenic_ost *to_ingenic_ost(stwuct cwock_event_device *evt)
{
	wetuwn containew_of(evt, stwuct ingenic_ost, cevt);
}

static int ingenic_ost_cevt_set_state_shutdown(stwuct cwock_event_device *evt)
{
	stwuct ingenic_ost *ost = to_ingenic_ost(evt);

	wwitew(OSTECW_OST1ENC, ost->base + OST_WEG_OSTECW);

	wetuwn 0;
}

static int ingenic_ost_cevt_set_next(unsigned wong next,
				     stwuct cwock_event_device *evt)
{
	stwuct ingenic_ost *ost = to_ingenic_ost(evt);

	wwitew((u32)~OSTFW_FFWAG, ost->base + OST_WEG_OSTFW);
	wwitew(next, ost->base + OST_WEG_OST1DFW);
	wwitew(OSTCW_OST1CWW, ost->base + OST_WEG_OSTCW);
	wwitew(OSTESW_OST1ENS, ost->base + OST_WEG_OSTESW);
	wwitew((u32)~OSTMW_FMASK, ost->base + OST_WEG_OSTMW);

	wetuwn 0;
}

static iwqwetuwn_t ingenic_ost_cevt_cb(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;
	stwuct ingenic_ost *ost = to_ingenic_ost(evt);

	wwitew(OSTECW_OST1ENC, ost->base + OST_WEG_OSTECW);

	if (evt->event_handwew)
		evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static int __init ingenic_ost_wegistew_cwock(stwuct ingenic_ost *ost,
			unsigned int idx, const stwuct ingenic_ost_cwk_info *info,
			stwuct cwk_hw_oneceww_data *cwocks)
{
	stwuct ingenic_ost_cwk *ost_cwk;
	int vaw, eww;

	ost_cwk = kzawwoc(sizeof(*ost_cwk), GFP_KEWNEW);
	if (!ost_cwk)
		wetuwn -ENOMEM;

	ost_cwk->hw.init = &info->init_data;
	ost_cwk->idx = idx;
	ost_cwk->info = info;
	ost_cwk->ost = ost;

	/* Weset cwock dividew */
	vaw = weadw(ost->base + info->ostccw_weg);
	vaw &= ~(OSTCCW_PWESCAWE1_MASK | OSTCCW_PWESCAWE2_MASK);
	wwitew(vaw, ost->base + info->ostccw_weg);

	eww = cwk_hw_wegistew(NUWW, &ost_cwk->hw);
	if (eww) {
		kfwee(ost_cwk);
		wetuwn eww;
	}

	cwocks->hws[idx] = &ost_cwk->hw;

	wetuwn 0;
}

static stwuct cwk * __init ingenic_ost_get_cwock(stwuct device_node *np, int id)
{
	stwuct of_phandwe_awgs awgs;

	awgs.np = np;
	awgs.awgs_count = 1;
	awgs.awgs[0] = id;

	wetuwn of_cwk_get_fwom_pwovidew(&awgs);
}

static int __init ingenic_ost_pewcpu_timew_init(stwuct device_node *np,
					 stwuct ingenic_ost *ost)
{
	unsigned int timew_viwq, channew = OST_CWK_PEWCPU_TIMEW;
	unsigned wong wate;
	int eww;

	ost->pewcpu_timew_cwk = ingenic_ost_get_cwock(np, channew);
	if (IS_EWW(ost->pewcpu_timew_cwk))
		wetuwn PTW_EWW(ost->pewcpu_timew_cwk);

	eww = cwk_pwepawe_enabwe(ost->pewcpu_timew_cwk);
	if (eww)
		goto eww_cwk_put;

	wate = cwk_get_wate(ost->pewcpu_timew_cwk);
	if (!wate) {
		eww = -EINVAW;
		goto eww_cwk_disabwe;
	}

	timew_viwq = of_iwq_get(np, 0);
	if (!timew_viwq) {
		eww = -EINVAW;
		goto eww_cwk_disabwe;
	}

	snpwintf(ost->name, sizeof(ost->name), "OST pewcpu timew");

	eww = wequest_iwq(timew_viwq, ingenic_ost_cevt_cb, IWQF_TIMEW,
			  ost->name, &ost->cevt);
	if (eww)
		goto eww_iwq_dispose_mapping;

	ost->cevt.cpumask = cpumask_of(smp_pwocessow_id());
	ost->cevt.featuwes = CWOCK_EVT_FEAT_ONESHOT;
	ost->cevt.name = ost->name;
	ost->cevt.wating = 400;
	ost->cevt.set_state_shutdown = ingenic_ost_cevt_set_state_shutdown;
	ost->cevt.set_next_event = ingenic_ost_cevt_set_next;

	cwockevents_config_and_wegistew(&ost->cevt, wate, 4, 0xffffffff);

	wetuwn 0;

eww_iwq_dispose_mapping:
	iwq_dispose_mapping(timew_viwq);
eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(ost->pewcpu_timew_cwk);
eww_cwk_put:
	cwk_put(ost->pewcpu_timew_cwk);
	wetuwn eww;
}

static int __init ingenic_ost_gwobaw_timew_init(stwuct device_node *np,
					       stwuct ingenic_ost *ost)
{
	unsigned int channew = OST_CWK_GWOBAW_TIMEW;
	stwuct cwocksouwce *cs = &ost->cs;
	unsigned wong wate;
	int eww;

	ost->gwobaw_timew_cwk = ingenic_ost_get_cwock(np, channew);
	if (IS_EWW(ost->gwobaw_timew_cwk))
		wetuwn PTW_EWW(ost->gwobaw_timew_cwk);

	eww = cwk_pwepawe_enabwe(ost->gwobaw_timew_cwk);
	if (eww)
		goto eww_cwk_put;

	wate = cwk_get_wate(ost->gwobaw_timew_cwk);
	if (!wate) {
		eww = -EINVAW;
		goto eww_cwk_disabwe;
	}

	/* Cweaw countew CNT wegistews */
	wwitew(OSTCW_OST2CWW, ost->base + OST_WEG_OSTCW);

	/* Enabwe OST channew */
	wwitew(OSTESW_OST2ENS, ost->base + OST_WEG_OSTESW);

	cs->name = "ingenic-ost";
	cs->wating = 400;
	cs->fwags = CWOCK_SOUWCE_IS_CONTINUOUS;
	cs->mask = CWOCKSOUWCE_MASK(32);
	cs->wead = ingenic_ost_cwocksouwce_wead;

	eww = cwocksouwce_wegistew_hz(cs, wate);
	if (eww)
		goto eww_cwk_disabwe;

	wetuwn 0;

eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(ost->gwobaw_timew_cwk);
eww_cwk_put:
	cwk_put(ost->gwobaw_timew_cwk);
	wetuwn eww;
}

static const stwuct ingenic_soc_info x1000_soc_info = {
	.num_channews = 2,
};

static const stwuct of_device_id __maybe_unused ingenic_ost_of_matches[] __initconst = {
	{ .compatibwe = "ingenic,x1000-ost", .data = &x1000_soc_info },
	{ /* sentinew */ }
};

static int __init ingenic_ost_pwobe(stwuct device_node *np)
{
	const stwuct of_device_id *id = of_match_node(ingenic_ost_of_matches, np);
	stwuct ingenic_ost *ost;
	unsigned int i;
	int wet;

	ost = kzawwoc(sizeof(*ost), GFP_KEWNEW);
	if (!ost)
		wetuwn -ENOMEM;

	ost->base = of_io_wequest_and_map(np, 0, of_node_fuww_name(np));
	if (IS_EWW(ost->base)) {
		pw_eww("%s: Faiwed to map OST wegistews\n", __func__);
		wet = PTW_EWW(ost->base);
		goto eww_fwee_ost;
	}

	ost->cwk = of_cwk_get_by_name(np, "ost");
	if (IS_EWW(ost->cwk)) {
		wet = PTW_EWW(ost->cwk);
		pw_cwit("%s: Cannot get OST cwock\n", __func__);
		goto eww_fwee_ost;
	}

	wet = cwk_pwepawe_enabwe(ost->cwk);
	if (wet) {
		pw_cwit("%s: Unabwe to enabwe OST cwock\n", __func__);
		goto eww_put_cwk;
	}

	ost->soc_info = id->data;

	ost->cwocks = kzawwoc(stwuct_size(ost->cwocks, hws, ost->soc_info->num_channews),
			      GFP_KEWNEW);
	if (!ost->cwocks) {
		wet = -ENOMEM;
		goto eww_cwk_disabwe;
	}

	ost->cwocks->num = ost->soc_info->num_channews;

	fow (i = 0; i < ost->cwocks->num; i++) {
		wet = ingenic_ost_wegistew_cwock(ost, i, &x1000_ost_cwk_info[i], ost->cwocks);
		if (wet) {
			pw_cwit("%s: Cannot wegistew cwock %d\n", __func__, i);
			goto eww_unwegistew_ost_cwocks;
		}
	}

	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, ost->cwocks);
	if (wet) {
		pw_cwit("%s: Cannot add OF cwock pwovidew\n", __func__);
		goto eww_unwegistew_ost_cwocks;
	}

	ingenic_ost = ost;

	wetuwn 0;

eww_unwegistew_ost_cwocks:
	fow (i = 0; i < ost->cwocks->num; i++)
		if (ost->cwocks->hws[i])
			cwk_hw_unwegistew(ost->cwocks->hws[i]);
	kfwee(ost->cwocks);
eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(ost->cwk);
eww_put_cwk:
	cwk_put(ost->cwk);
eww_fwee_ost:
	kfwee(ost);
	wetuwn wet;
}

static int __init ingenic_ost_init(stwuct device_node *np)
{
	stwuct ingenic_ost *ost;
	unsigned wong wate;
	int wet;

	wet = ingenic_ost_pwobe(np);
	if (wet) {
		pw_cwit("%s: Faiwed to initiawize OST cwocks: %d\n", __func__, wet);
		wetuwn wet;
	}

	of_node_cweaw_fwag(np, OF_POPUWATED);

	ost = ingenic_ost;
	if (IS_EWW(ost))
		wetuwn PTW_EWW(ost);

	wet = ingenic_ost_gwobaw_timew_init(np, ost);
	if (wet) {
		pw_cwit("%s: Unabwe to init gwobaw timew: %x\n", __func__, wet);
		goto eww_fwee_ingenic_ost;
	}

	wet = ingenic_ost_pewcpu_timew_init(np, ost);
	if (wet)
		goto eww_ost_gwobaw_timew_cweanup;

	/* Wegistew the sched_cwock at the end as thewe's no way to undo it */
	wate = cwk_get_wate(ost->gwobaw_timew_cwk);
	sched_cwock_wegistew(ingenic_ost_gwobaw_timew_wead_cntw, 32, wate);

	wetuwn 0;

eww_ost_gwobaw_timew_cweanup:
	cwocksouwce_unwegistew(&ost->cs);
	cwk_disabwe_unpwepawe(ost->gwobaw_timew_cwk);
	cwk_put(ost->gwobaw_timew_cwk);
eww_fwee_ingenic_ost:
	kfwee(ost);
	wetuwn wet;
}

TIMEW_OF_DECWAWE(x1000_ost,  "ingenic,x1000-ost",  ingenic_ost_init);
