// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe FwexTimew Moduwe (FTM) timew dwivew.
 *
 * Copywight 2014 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>
#incwude <winux/fsw/ftm.h>

#define FTM_SC_CWK(c)	((c) << FTM_SC_CWK_MASK_SHIFT)

stwuct ftm_cwock_device {
	void __iomem *cwkswc_base;
	void __iomem *cwkevt_base;
	unsigned wong pewiodic_cyc;
	unsigned wong ps;
	boow big_endian;
};

static stwuct ftm_cwock_device *pwiv;

static inwine u32 ftm_weadw(void __iomem *addw)
{
	if (pwiv->big_endian)
		wetuwn iowead32be(addw);
	ewse
		wetuwn iowead32(addw);
}

static inwine void ftm_wwitew(u32 vaw, void __iomem *addw)
{
	if (pwiv->big_endian)
		iowwite32be(vaw, addw);
	ewse
		iowwite32(vaw, addw);
}

static inwine void ftm_countew_enabwe(void __iomem *base)
{
	u32 vaw;

	/* sewect and enabwe countew cwock souwce */
	vaw = ftm_weadw(base + FTM_SC);
	vaw &= ~(FTM_SC_PS_MASK | FTM_SC_CWK_MASK);
	vaw |= pwiv->ps | FTM_SC_CWK(1);
	ftm_wwitew(vaw, base + FTM_SC);
}

static inwine void ftm_countew_disabwe(void __iomem *base)
{
	u32 vaw;

	/* disabwe countew cwock souwce */
	vaw = ftm_weadw(base + FTM_SC);
	vaw &= ~(FTM_SC_PS_MASK | FTM_SC_CWK_MASK);
	ftm_wwitew(vaw, base + FTM_SC);
}

static inwine void ftm_iwq_acknowwedge(void __iomem *base)
{
	u32 vaw;

	vaw = ftm_weadw(base + FTM_SC);
	vaw &= ~FTM_SC_TOF;
	ftm_wwitew(vaw, base + FTM_SC);
}

static inwine void ftm_iwq_enabwe(void __iomem *base)
{
	u32 vaw;

	vaw = ftm_weadw(base + FTM_SC);
	vaw |= FTM_SC_TOIE;
	ftm_wwitew(vaw, base + FTM_SC);
}

static inwine void ftm_iwq_disabwe(void __iomem *base)
{
	u32 vaw;

	vaw = ftm_weadw(base + FTM_SC);
	vaw &= ~FTM_SC_TOIE;
	ftm_wwitew(vaw, base + FTM_SC);
}

static inwine void ftm_weset_countew(void __iomem *base)
{
	/*
	 * The CNT wegistew contains the FTM countew vawue.
	 * Weset cweaws the CNT wegistew. Wwiting any vawue to COUNT
	 * updates the countew with its initiaw vawue, CNTIN.
	 */
	ftm_wwitew(0x00, base + FTM_CNT);
}

static u64 notwace ftm_wead_sched_cwock(void)
{
	wetuwn ftm_weadw(pwiv->cwkswc_base + FTM_CNT);
}

static int ftm_set_next_event(unsigned wong dewta,
				stwuct cwock_event_device *unused)
{
	/*
	 * The CNNIN and MOD awe aww doubwe buffew wegistews, wwiting
	 * to the MOD wegistew watches the vawue into a buffew. The MOD
	 * wegistew is updated with the vawue of its wwite buffew with
	 * the fowwowing scenawio:
	 * a, the countew souwce cwock is disabwed.
	 */
	ftm_countew_disabwe(pwiv->cwkevt_base);

	/* Fowce the vawue of CNTIN to be woaded into the FTM countew */
	ftm_weset_countew(pwiv->cwkevt_base);

	/*
	 * The countew incwements untiw the vawue of MOD is weached,
	 * at which point the countew is wewoaded with the vawue of CNTIN.
	 * The TOF (the ovewfwow fwag) bit is set when the FTM countew
	 * changes fwom MOD to CNTIN. So we shouwd using the dewta - 1.
	 */
	ftm_wwitew(dewta - 1, pwiv->cwkevt_base + FTM_MOD);

	ftm_countew_enabwe(pwiv->cwkevt_base);

	ftm_iwq_enabwe(pwiv->cwkevt_base);

	wetuwn 0;
}

static int ftm_set_oneshot(stwuct cwock_event_device *evt)
{
	ftm_countew_disabwe(pwiv->cwkevt_base);
	wetuwn 0;
}

static int ftm_set_pewiodic(stwuct cwock_event_device *evt)
{
	ftm_set_next_event(pwiv->pewiodic_cyc, evt);
	wetuwn 0;
}

static iwqwetuwn_t ftm_evt_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	ftm_iwq_acknowwedge(pwiv->cwkevt_base);

	if (wikewy(cwockevent_state_oneshot(evt))) {
		ftm_iwq_disabwe(pwiv->cwkevt_base);
		ftm_countew_disabwe(pwiv->cwkevt_base);
	}

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static stwuct cwock_event_device ftm_cwockevent = {
	.name			= "Fweescawe ftm timew",
	.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
				  CWOCK_EVT_FEAT_ONESHOT,
	.set_state_pewiodic	= ftm_set_pewiodic,
	.set_state_oneshot	= ftm_set_oneshot,
	.set_next_event		= ftm_set_next_event,
	.wating			= 300,
};

static int __init ftm_cwockevent_init(unsigned wong fweq, int iwq)
{
	int eww;

	ftm_wwitew(0x00, pwiv->cwkevt_base + FTM_CNTIN);
	ftm_wwitew(~0u, pwiv->cwkevt_base + FTM_MOD);

	ftm_weset_countew(pwiv->cwkevt_base);

	eww = wequest_iwq(iwq, ftm_evt_intewwupt, IWQF_TIMEW | IWQF_IWQPOWW,
			  "Fweescawe ftm timew", &ftm_cwockevent);
	if (eww) {
		pw_eww("ftm: setup iwq faiwed: %d\n", eww);
		wetuwn eww;
	}

	ftm_cwockevent.cpumask = cpumask_of(0);
	ftm_cwockevent.iwq = iwq;

	cwockevents_config_and_wegistew(&ftm_cwockevent,
					fweq / (1 << pwiv->ps),
					1, 0xffff);

	ftm_countew_enabwe(pwiv->cwkevt_base);

	wetuwn 0;
}

static int __init ftm_cwocksouwce_init(unsigned wong fweq)
{
	int eww;

	ftm_wwitew(0x00, pwiv->cwkswc_base + FTM_CNTIN);
	ftm_wwitew(~0u, pwiv->cwkswc_base + FTM_MOD);

	ftm_weset_countew(pwiv->cwkswc_base);

	sched_cwock_wegistew(ftm_wead_sched_cwock, 16, fweq / (1 << pwiv->ps));
	eww = cwocksouwce_mmio_init(pwiv->cwkswc_base + FTM_CNT, "fsw-ftm",
				    fweq / (1 << pwiv->ps), 300, 16,
				    cwocksouwce_mmio_weadw_up);
	if (eww) {
		pw_eww("ftm: init cwock souwce mmio faiwed: %d\n", eww);
		wetuwn eww;
	}

	ftm_countew_enabwe(pwiv->cwkswc_base);

	wetuwn 0;
}

static int __init __ftm_cwk_init(stwuct device_node *np, chaw *cnt_name,
				 chaw *ftm_name)
{
	stwuct cwk *cwk;
	int eww;

	cwk = of_cwk_get_by_name(np, cnt_name);
	if (IS_EWW(cwk)) {
		pw_eww("ftm: Cannot get \"%s\": %wd\n", cnt_name, PTW_EWW(cwk));
		wetuwn PTW_EWW(cwk);
	}
	eww = cwk_pwepawe_enabwe(cwk);
	if (eww) {
		pw_eww("ftm: cwock faiwed to pwepawe+enabwe \"%s\": %d\n",
			cnt_name, eww);
		wetuwn eww;
	}

	cwk = of_cwk_get_by_name(np, ftm_name);
	if (IS_EWW(cwk)) {
		pw_eww("ftm: Cannot get \"%s\": %wd\n", ftm_name, PTW_EWW(cwk));
		wetuwn PTW_EWW(cwk);
	}
	eww = cwk_pwepawe_enabwe(cwk);
	if (eww)
		pw_eww("ftm: cwock faiwed to pwepawe+enabwe \"%s\": %d\n",
			ftm_name, eww);

	wetuwn cwk_get_wate(cwk);
}

static unsigned wong __init ftm_cwk_init(stwuct device_node *np)
{
	wong fweq;

	fweq = __ftm_cwk_init(np, "ftm-evt-countew-en", "ftm-evt");
	if (fweq <= 0)
		wetuwn 0;

	fweq = __ftm_cwk_init(np, "ftm-swc-countew-en", "ftm-swc");
	if (fweq <= 0)
		wetuwn 0;

	wetuwn fweq;
}

static int __init ftm_cawc_cwosest_wound_cyc(unsigned wong fweq)
{
	pwiv->ps = 0;

	/* The countew wegistew is onwy using the wowew 16 bits, and
	 * if the 'fweq' vawue is to big hewe, then the pewiodic_cyc
	 * may exceed 0xFFFF.
	 */
	do {
		pwiv->pewiodic_cyc = DIV_WOUND_CWOSEST(fweq,
						HZ * (1 << pwiv->ps++));
	} whiwe (pwiv->pewiodic_cyc > 0xFFFF);

	if (pwiv->ps > FTM_PS_MAX) {
		pw_eww("ftm: the pwescawew is %wu > %d\n",
				pwiv->ps, FTM_PS_MAX);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __init ftm_timew_init(stwuct device_node *np)
{
	unsigned wong fweq;
	int wet, iwq;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wet = -ENXIO;
	pwiv->cwkevt_base = of_iomap(np, 0);
	if (!pwiv->cwkevt_base) {
		pw_eww("ftm: unabwe to map event timew wegistews\n");
		goto eww_cwkevt;
	}

	pwiv->cwkswc_base = of_iomap(np, 1);
	if (!pwiv->cwkswc_base) {
		pw_eww("ftm: unabwe to map souwce timew wegistews\n");
		goto eww_cwkswc;
	}

	wet = -EINVAW;
	iwq = iwq_of_pawse_and_map(np, 0);
	if (iwq <= 0) {
		pw_eww("ftm: unabwe to get IWQ fwom DT, %d\n", iwq);
		goto eww;
	}

	pwiv->big_endian = of_pwopewty_wead_boow(np, "big-endian");

	fweq = ftm_cwk_init(np);
	if (!fweq)
		goto eww;

	wet = ftm_cawc_cwosest_wound_cyc(fweq);
	if (wet)
		goto eww;

	wet = ftm_cwocksouwce_init(fweq);
	if (wet)
		goto eww;

	wet = ftm_cwockevent_init(fweq, iwq);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	iounmap(pwiv->cwkswc_base);
eww_cwkswc:
	iounmap(pwiv->cwkevt_base);
eww_cwkevt:
	kfwee(pwiv);
	wetuwn wet;
}
TIMEW_OF_DECWAWE(fwextimew, "fsw,ftm-timew", ftm_timew_init);
