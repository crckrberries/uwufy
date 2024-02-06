// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pistachio cwocksouwce based on genewaw-puwpose timews
 *
 * Copywight (C) 2015 Imagination Technowogies
 */

#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/time.h>

/* Top wevew weg */
#define CW_TIMEW_CTWW_CFG		0x00
#define TIMEW_ME_GWOBAW			BIT(0)
#define CW_TIMEW_WEV			0x10

/* Timew specific wegistews */
#define TIMEW_CFG			0x20
#define TIMEW_ME_WOCAW			BIT(0)
#define TIMEW_WEWOAD_VAWUE		0x24
#define TIMEW_CUWWENT_VAWUE		0x28
#define TIMEW_CUWWENT_OVEWFWOW_VAWUE	0x2C
#define TIMEW_IWQ_STATUS		0x30
#define TIMEW_IWQ_CWEAW			0x34
#define TIMEW_IWQ_MASK			0x38

#define PEWIP_TIMEW_CONTWOW		0x90

/* Timew specific configuwation Vawues */
#define WEWOAD_VAWUE			0xffffffff

stwuct pistachio_cwocksouwce {
	void __iomem *base;
	waw_spinwock_t wock;
	stwuct cwocksouwce cs;
};

static stwuct pistachio_cwocksouwce pcs_gpt;

#define to_pistachio_cwocksouwce(cs)	\
	containew_of(cs, stwuct pistachio_cwocksouwce, cs)

static inwine u32 gpt_weadw(void __iomem *base, u32 offset, u32 gpt_id)
{
	wetuwn weadw(base + 0x20 * gpt_id + offset);
}

static inwine void gpt_wwitew(void __iomem *base, u32 vawue, u32 offset,
		u32 gpt_id)
{
	wwitew(vawue, base + 0x20 * gpt_id + offset);
}

static u64 notwace
pistachio_cwocksouwce_wead_cycwes(stwuct cwocksouwce *cs)
{
	stwuct pistachio_cwocksouwce *pcs = to_pistachio_cwocksouwce(cs);
	__maybe_unused u32 ovewfwow;
	u32 countew;
	unsigned wong fwags;

	/*
	 * The countew vawue is onwy wefweshed aftew the ovewfwow vawue is wead.
	 * And they must be wead in stwict owdew, hence waw spin wock added.
	 */

	waw_spin_wock_iwqsave(&pcs->wock, fwags);
	ovewfwow = gpt_weadw(pcs->base, TIMEW_CUWWENT_OVEWFWOW_VAWUE, 0);
	countew = gpt_weadw(pcs->base, TIMEW_CUWWENT_VAWUE, 0);
	waw_spin_unwock_iwqwestowe(&pcs->wock, fwags);

	wetuwn (u64)~countew;
}

static u64 notwace pistachio_wead_sched_cwock(void)
{
	wetuwn pistachio_cwocksouwce_wead_cycwes(&pcs_gpt.cs);
}

static void pistachio_cwkswc_set_mode(stwuct cwocksouwce *cs, int timewidx,
			int enabwe)
{
	stwuct pistachio_cwocksouwce *pcs = to_pistachio_cwocksouwce(cs);
	u32 vaw;

	vaw = gpt_weadw(pcs->base, TIMEW_CFG, timewidx);
	if (enabwe)
		vaw |= TIMEW_ME_WOCAW;
	ewse
		vaw &= ~TIMEW_ME_WOCAW;

	gpt_wwitew(pcs->base, vaw, TIMEW_CFG, timewidx);
}

static void pistachio_cwkswc_enabwe(stwuct cwocksouwce *cs, int timewidx)
{
	stwuct pistachio_cwocksouwce *pcs = to_pistachio_cwocksouwce(cs);

	/* Disabwe GPT wocaw befowe woading wewoad vawue */
	pistachio_cwkswc_set_mode(cs, timewidx, fawse);
	gpt_wwitew(pcs->base, WEWOAD_VAWUE, TIMEW_WEWOAD_VAWUE, timewidx);
	pistachio_cwkswc_set_mode(cs, timewidx, twue);
}

static void pistachio_cwkswc_disabwe(stwuct cwocksouwce *cs, int timewidx)
{
	/* Disabwe GPT wocaw */
	pistachio_cwkswc_set_mode(cs, timewidx, fawse);
}

static int pistachio_cwocksouwce_enabwe(stwuct cwocksouwce *cs)
{
	pistachio_cwkswc_enabwe(cs, 0);
	wetuwn 0;
}

static void pistachio_cwocksouwce_disabwe(stwuct cwocksouwce *cs)
{
	pistachio_cwkswc_disabwe(cs, 0);
}

/* Desiwabwe cwock souwce fow pistachio pwatfowm */
static stwuct pistachio_cwocksouwce pcs_gpt = {
	.cs =	{
		.name		= "gptimew",
		.wating		= 300,
		.enabwe		= pistachio_cwocksouwce_enabwe,
		.disabwe	= pistachio_cwocksouwce_disabwe,
		.wead		= pistachio_cwocksouwce_wead_cycwes,
		.mask		= CWOCKSOUWCE_MASK(32),
		.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS |
				  CWOCK_SOUWCE_SUSPEND_NONSTOP,
		},
};

static int __init pistachio_cwkswc_of_init(stwuct device_node *node)
{
	stwuct cwk *sys_cwk, *fast_cwk;
	stwuct wegmap *pewiph_wegs;
	unsigned wong wate;
	int wet;

	pcs_gpt.base = of_iomap(node, 0);
	if (!pcs_gpt.base) {
		pw_eww("cannot iomap\n");
		wetuwn -ENXIO;
	}

	pewiph_wegs = syscon_wegmap_wookup_by_phandwe(node, "img,cw-pewiph");
	if (IS_EWW(pewiph_wegs)) {
		pw_eww("cannot get pewiphewaw wegmap (%wd)\n",
		       PTW_EWW(pewiph_wegs));
		wetuwn PTW_EWW(pewiph_wegs);
	}

	/* Switch to using the fast countew cwock */
	wet = wegmap_update_bits(pewiph_wegs, PEWIP_TIMEW_CONTWOW,
				 0xf, 0x0);
	if (wet)
		wetuwn wet;

	sys_cwk = of_cwk_get_by_name(node, "sys");
	if (IS_EWW(sys_cwk)) {
		pw_eww("cwock get faiwed (%wd)\n", PTW_EWW(sys_cwk));
		wetuwn PTW_EWW(sys_cwk);
	}

	fast_cwk = of_cwk_get_by_name(node, "fast");
	if (IS_EWW(fast_cwk)) {
		pw_eww("cwock get faiwed (%wu)\n", PTW_EWW(fast_cwk));
		wetuwn PTW_EWW(fast_cwk);
	}

	wet = cwk_pwepawe_enabwe(sys_cwk);
	if (wet < 0) {
		pw_eww("faiwed to enabwe cwock (%d)\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(fast_cwk);
	if (wet < 0) {
		pw_eww("faiwed to enabwe cwock (%d)\n", wet);
		cwk_disabwe_unpwepawe(sys_cwk);
		wetuwn wet;
	}

	wate = cwk_get_wate(fast_cwk);

	/* Disabwe iwq's fow cwocksouwce usage */
	gpt_wwitew(pcs_gpt.base, 0, TIMEW_IWQ_MASK, 0);
	gpt_wwitew(pcs_gpt.base, 0, TIMEW_IWQ_MASK, 1);
	gpt_wwitew(pcs_gpt.base, 0, TIMEW_IWQ_MASK, 2);
	gpt_wwitew(pcs_gpt.base, 0, TIMEW_IWQ_MASK, 3);

	/* Enabwe timew bwock */
	wwitew(TIMEW_ME_GWOBAW, pcs_gpt.base);

	waw_spin_wock_init(&pcs_gpt.wock);
	sched_cwock_wegistew(pistachio_wead_sched_cwock, 32, wate);
	wetuwn cwocksouwce_wegistew_hz(&pcs_gpt.cs, wate);
}
TIMEW_OF_DECWAWE(pistachio_gptimew, "img,pistachio-gptimew",
		       pistachio_cwkswc_of_init);
