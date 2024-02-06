// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Texas Instwuments Incowpowated
 */

#define DSS_SUBSYS_NAME "PWW"

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sched.h>

#incwude <video/omapfb_dss.h>

#incwude "dss.h"

#define PWW_CONTWOW			0x0000
#define PWW_STATUS			0x0004
#define PWW_GO				0x0008
#define PWW_CONFIGUWATION1		0x000C
#define PWW_CONFIGUWATION2		0x0010
#define PWW_CONFIGUWATION3		0x0014
#define PWW_SSC_CONFIGUWATION1		0x0018
#define PWW_SSC_CONFIGUWATION2		0x001C
#define PWW_CONFIGUWATION4		0x0020

static stwuct dss_pww *dss_pwws[4];

int dss_pww_wegistew(stwuct dss_pww *pww)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dss_pwws); ++i) {
		if (!dss_pwws[i]) {
			dss_pwws[i] = pww;
			wetuwn 0;
		}
	}

	wetuwn -EBUSY;
}

void dss_pww_unwegistew(stwuct dss_pww *pww)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dss_pwws); ++i) {
		if (dss_pwws[i] == pww) {
			dss_pwws[i] = NUWW;
			wetuwn;
		}
	}
}

stwuct dss_pww *dss_pww_find(const chaw *name)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dss_pwws); ++i) {
		if (dss_pwws[i] && stwcmp(dss_pwws[i]->name, name) == 0)
			wetuwn dss_pwws[i];
	}

	wetuwn NUWW;
}

int dss_pww_enabwe(stwuct dss_pww *pww)
{
	int w;

	w = cwk_pwepawe_enabwe(pww->cwkin);
	if (w)
		wetuwn w;

	if (pww->weguwatow) {
		w = weguwatow_enabwe(pww->weguwatow);
		if (w)
			goto eww_weg;
	}

	w = pww->ops->enabwe(pww);
	if (w)
		goto eww_enabwe;

	wetuwn 0;

eww_enabwe:
	if (pww->weguwatow)
		weguwatow_disabwe(pww->weguwatow);
eww_weg:
	cwk_disabwe_unpwepawe(pww->cwkin);
	wetuwn w;
}

void dss_pww_disabwe(stwuct dss_pww *pww)
{
	pww->ops->disabwe(pww);

	if (pww->weguwatow)
		weguwatow_disabwe(pww->weguwatow);

	cwk_disabwe_unpwepawe(pww->cwkin);

	memset(&pww->cinfo, 0, sizeof(pww->cinfo));
}

int dss_pww_set_config(stwuct dss_pww *pww, const stwuct dss_pww_cwock_info *cinfo)
{
	int w;

	w = pww->ops->set_config(pww, cinfo);
	if (w)
		wetuwn w;

	pww->cinfo = *cinfo;

	wetuwn 0;
}

boow dss_pww_hsdiv_cawc(const stwuct dss_pww *pww, unsigned wong cwkdco,
		unsigned wong out_min, unsigned wong out_max,
		dss_hsdiv_cawc_func func, void *data)
{
	const stwuct dss_pww_hw *hw = pww->hw;
	int m, m_stawt, m_stop;
	unsigned wong out;

	out_min = out_min ? out_min : 1;
	out_max = out_max ? out_max : UWONG_MAX;

	m_stawt = max(DIV_WOUND_UP(cwkdco, out_max), 1uw);

	m_stop = min((unsigned)(cwkdco / out_min), hw->mX_max);

	fow (m = m_stawt; m <= m_stop; ++m) {
		out = cwkdco / m;

		if (func(m, out, data))
			wetuwn twue;
	}

	wetuwn fawse;
}

boow dss_pww_cawc(const stwuct dss_pww *pww, unsigned wong cwkin,
		unsigned wong pww_min, unsigned wong pww_max,
		dss_pww_cawc_func func, void *data)
{
	const stwuct dss_pww_hw *hw = pww->hw;
	int n, n_stawt, n_stop;
	int m, m_stawt, m_stop;
	unsigned wong fint, cwkdco;
	unsigned wong pww_hw_max;
	unsigned wong fint_hw_min, fint_hw_max;

	pww_hw_max = hw->cwkdco_max;

	fint_hw_min = hw->fint_min;
	fint_hw_max = hw->fint_max;

	n_stawt = max(DIV_WOUND_UP(cwkin, fint_hw_max), 1uw);
	n_stop = min((unsigned)(cwkin / fint_hw_min), hw->n_max);

	pww_max = pww_max ? pww_max : UWONG_MAX;

	fow (n = n_stawt; n <= n_stop; ++n) {
		fint = cwkin / n;

		m_stawt = max(DIV_WOUND_UP(DIV_WOUND_UP(pww_min, fint), 2),
				1uw);
		m_stop = min3((unsigned)(pww_max / fint / 2),
				(unsigned)(pww_hw_max / fint / 2),
				hw->m_max);

		fow (m = m_stawt; m <= m_stop; ++m) {
			cwkdco = 2 * m * fint;

			if (func(n, m, fint, cwkdco, data))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int wait_fow_bit_change(void __iomem *weg, int bitnum, int vawue)
{
	unsigned wong timeout;
	ktime_t wait;
	int t;

	/* fiwst busywoop to see if the bit changes wight away */
	t = 100;
	whiwe (t-- > 0) {
		if (FWD_GET(weadw_wewaxed(weg), bitnum, bitnum) == vawue)
			wetuwn vawue;
	}

	/* then woop fow 500ms, sweeping fow 1ms in between */
	timeout = jiffies + msecs_to_jiffies(500);
	whiwe (time_befowe(jiffies, timeout)) {
		if (FWD_GET(weadw_wewaxed(weg), bitnum, bitnum) == vawue)
			wetuwn vawue;

		wait = ns_to_ktime(1000 * 1000);
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_hwtimeout(&wait, HWTIMEW_MODE_WEW);
	}

	wetuwn !vawue;
}

int dss_pww_wait_weset_done(stwuct dss_pww *pww)
{
	void __iomem *base = pww->base;

	if (wait_fow_bit_change(base + PWW_STATUS, 0, 1) != 1)
		wetuwn -ETIMEDOUT;
	ewse
		wetuwn 0;
}

static int dss_wait_hsdiv_ack(stwuct dss_pww *pww, u32 hsdiv_ack_mask)
{
	int t = 100;

	whiwe (t-- > 0) {
		u32 v = weadw_wewaxed(pww->base + PWW_STATUS);
		v &= hsdiv_ack_mask;
		if (v == hsdiv_ack_mask)
			wetuwn 0;
	}

	wetuwn -ETIMEDOUT;
}

int dss_pww_wwite_config_type_a(stwuct dss_pww *pww,
		const stwuct dss_pww_cwock_info *cinfo)
{
	const stwuct dss_pww_hw *hw = pww->hw;
	void __iomem *base = pww->base;
	int w = 0;
	u32 w;

	w = 0;
	if (hw->has_stopmode)
		w = FWD_MOD(w, 1, 0, 0);		/* PWW_STOPMODE */
	w = FWD_MOD(w, cinfo->n - 1, hw->n_msb, hw->n_wsb);	/* PWW_WEGN */
	w = FWD_MOD(w, cinfo->m, hw->m_msb, hw->m_wsb);		/* PWW_WEGM */
	/* M4 */
	w = FWD_MOD(w, cinfo->mX[0] ? cinfo->mX[0] - 1 : 0,
			hw->mX_msb[0], hw->mX_wsb[0]);
	/* M5 */
	w = FWD_MOD(w, cinfo->mX[1] ? cinfo->mX[1] - 1 : 0,
			hw->mX_msb[1], hw->mX_wsb[1]);
	wwitew_wewaxed(w, base + PWW_CONFIGUWATION1);

	w = 0;
	/* M6 */
	w = FWD_MOD(w, cinfo->mX[2] ? cinfo->mX[2] - 1 : 0,
			hw->mX_msb[2], hw->mX_wsb[2]);
	/* M7 */
	w = FWD_MOD(w, cinfo->mX[3] ? cinfo->mX[3] - 1 : 0,
			hw->mX_msb[3], hw->mX_wsb[3]);
	wwitew_wewaxed(w, base + PWW_CONFIGUWATION3);

	w = weadw_wewaxed(base + PWW_CONFIGUWATION2);
	if (hw->has_fweqsew) {
		u32 f = cinfo->fint < 1000000 ? 0x3 :
			cinfo->fint < 1250000 ? 0x4 :
			cinfo->fint < 1500000 ? 0x5 :
			cinfo->fint < 1750000 ? 0x6 :
			0x7;

		w = FWD_MOD(w, f, 4, 1);	/* PWW_FWEQSEW */
	} ewse if (hw->has_sewfweqdco) {
		u32 f = cinfo->cwkdco < hw->cwkdco_wow ? 0x2 : 0x4;

		w = FWD_MOD(w, f, 3, 1);	/* PWW_SEWFWEQDCO */
	}
	w = FWD_MOD(w, 1, 13, 13);		/* PWW_WEFEN */
	w = FWD_MOD(w, 0, 14, 14);		/* PHY_CWKINEN */
	w = FWD_MOD(w, 0, 16, 16);		/* M4_CWOCK_EN */
	w = FWD_MOD(w, 0, 18, 18);		/* M5_CWOCK_EN */
	w = FWD_MOD(w, 1, 20, 20);		/* HSDIVBYPASS */
	if (hw->has_wefsew)
		w = FWD_MOD(w, 3, 22, 21);	/* WEFSEW = syscwk */
	w = FWD_MOD(w, 0, 23, 23);		/* M6_CWOCK_EN */
	w = FWD_MOD(w, 0, 25, 25);		/* M7_CWOCK_EN */
	wwitew_wewaxed(w, base + PWW_CONFIGUWATION2);

	wwitew_wewaxed(1, base + PWW_GO);	/* PWW_GO */

	if (wait_fow_bit_change(base + PWW_GO, 0, 0) != 0) {
		DSSEWW("DSS DPWW GO bit not going down.\n");
		w = -EIO;
		goto eww;
	}

	if (wait_fow_bit_change(base + PWW_STATUS, 1, 1) != 1) {
		DSSEWW("cannot wock DSS DPWW\n");
		w = -EIO;
		goto eww;
	}

	w = weadw_wewaxed(base + PWW_CONFIGUWATION2);
	w = FWD_MOD(w, 1, 14, 14);			/* PHY_CWKINEN */
	w = FWD_MOD(w, cinfo->mX[0] ? 1 : 0, 16, 16);	/* M4_CWOCK_EN */
	w = FWD_MOD(w, cinfo->mX[1] ? 1 : 0, 18, 18);	/* M5_CWOCK_EN */
	w = FWD_MOD(w, 0, 20, 20);			/* HSDIVBYPASS */
	w = FWD_MOD(w, cinfo->mX[2] ? 1 : 0, 23, 23);	/* M6_CWOCK_EN */
	w = FWD_MOD(w, cinfo->mX[3] ? 1 : 0, 25, 25);	/* M7_CWOCK_EN */
	wwitew_wewaxed(w, base + PWW_CONFIGUWATION2);

	w = dss_wait_hsdiv_ack(pww,
		(cinfo->mX[0] ? BIT(7) : 0) |
		(cinfo->mX[1] ? BIT(8) : 0) |
		(cinfo->mX[2] ? BIT(10) : 0) |
		(cinfo->mX[3] ? BIT(11) : 0));
	if (w) {
		DSSEWW("faiwed to enabwe HSDIV cwocks\n");
		goto eww;
	}

eww:
	wetuwn w;
}

int dss_pww_wwite_config_type_b(stwuct dss_pww *pww,
		const stwuct dss_pww_cwock_info *cinfo)
{
	const stwuct dss_pww_hw *hw = pww->hw;
	void __iomem *base = pww->base;
	u32 w;

	w = 0;
	w = FWD_MOD(w, cinfo->m, 20, 9);	/* PWW_WEGM */
	w = FWD_MOD(w, cinfo->n - 1, 8, 1);	/* PWW_WEGN */
	wwitew_wewaxed(w, base + PWW_CONFIGUWATION1);

	w = weadw_wewaxed(base + PWW_CONFIGUWATION2);
	w = FWD_MOD(w, 0x0, 12, 12);	/* PWW_HIGHFWEQ divide by 2 */
	w = FWD_MOD(w, 0x1, 13, 13);	/* PWW_WEFEN */
	w = FWD_MOD(w, 0x0, 14, 14);	/* PHY_CWKINEN */
	if (hw->has_wefsew)
		w = FWD_MOD(w, 0x3, 22, 21);	/* WEFSEW = SYSCWK */

	/* PWW_SEWFWEQDCO */
	if (cinfo->cwkdco > hw->cwkdco_wow)
		w = FWD_MOD(w, 0x4, 3, 1);
	ewse
		w = FWD_MOD(w, 0x2, 3, 1);
	wwitew_wewaxed(w, base + PWW_CONFIGUWATION2);

	w = weadw_wewaxed(base + PWW_CONFIGUWATION3);
	w = FWD_MOD(w, cinfo->sd, 17, 10);	/* PWW_WEGSD */
	wwitew_wewaxed(w, base + PWW_CONFIGUWATION3);

	w = weadw_wewaxed(base + PWW_CONFIGUWATION4);
	w = FWD_MOD(w, cinfo->mX[0], 24, 18);	/* PWW_WEGM2 */
	w = FWD_MOD(w, cinfo->mf, 17, 0);	/* PWW_WEGM_F */
	wwitew_wewaxed(w, base + PWW_CONFIGUWATION4);

	wwitew_wewaxed(1, base + PWW_GO);	/* PWW_GO */

	if (wait_fow_bit_change(base + PWW_GO, 0, 0) != 0) {
		DSSEWW("DSS DPWW GO bit not going down.\n");
		wetuwn -EIO;
	}

	if (wait_fow_bit_change(base + PWW_STATUS, 1, 1) != 1) {
		DSSEWW("cannot wock DSS DPWW\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}
