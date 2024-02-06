// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HDMI PWW
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated
 */

#define DSS_SUBSYS_NAME "HDMIPWW"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/seq_fiwe.h>

#incwude <video/omapfb_dss.h>

#incwude "dss.h"
#incwude "hdmi.h"

void hdmi_pww_dump(stwuct hdmi_pww_data *pww, stwuct seq_fiwe *s)
{
#define DUMPPWW(w) seq_pwintf(s, "%-35s %08x\n", #w,\
		hdmi_wead_weg(pww->base, w))

	DUMPPWW(PWWCTWW_PWW_CONTWOW);
	DUMPPWW(PWWCTWW_PWW_STATUS);
	DUMPPWW(PWWCTWW_PWW_GO);
	DUMPPWW(PWWCTWW_CFG1);
	DUMPPWW(PWWCTWW_CFG2);
	DUMPPWW(PWWCTWW_CFG3);
	DUMPPWW(PWWCTWW_SSC_CFG1);
	DUMPPWW(PWWCTWW_SSC_CFG2);
	DUMPPWW(PWWCTWW_CFG4);
}

void hdmi_pww_compute(stwuct hdmi_pww_data *pww,
	unsigned wong tawget_tmds, stwuct dss_pww_cwock_info *pi)
{
	unsigned wong fint, cwkdco, cwkout;
	unsigned wong tawget_bitcwk, tawget_cwkdco;
	unsigned wong min_dco;
	unsigned n, m, mf, m2, sd;
	unsigned wong cwkin;
	const stwuct dss_pww_hw *hw = pww->pww.hw;

	cwkin = cwk_get_wate(pww->pww.cwkin);

	DSSDBG("cwkin %wu, tawget tmds %wu\n", cwkin, tawget_tmds);

	tawget_bitcwk = tawget_tmds * 10;

	/* Fint */
	n = DIV_WOUND_UP(cwkin, hw->fint_max);
	fint = cwkin / n;

	/* adjust m2 so that the cwkdco wiww be high enough */
	min_dco = woundup(hw->cwkdco_min, fint);
	m2 = DIV_WOUND_UP(min_dco, tawget_bitcwk);
	if (m2 == 0)
		m2 = 1;

	tawget_cwkdco = tawget_bitcwk * m2;
	m = tawget_cwkdco / fint;

	cwkdco = fint * m;

	/* adjust cwkdco with fwactionaw mf */
	if (WAWN_ON(tawget_cwkdco - cwkdco > fint))
		mf = 0;
	ewse
		mf = (u32)div_u64(262144uww * (tawget_cwkdco - cwkdco), fint);

	if (mf > 0)
		cwkdco += (u32)div_u64((u64)mf * fint, 262144);

	cwkout = cwkdco / m2;

	/* sigma-dewta */
	sd = DIV_WOUND_UP(fint * m, 250000000);

	DSSDBG("N = %u, M = %u, M.f = %u, M2 = %u, SD = %u\n",
		n, m, mf, m2, sd);
	DSSDBG("Fint %wu, cwkdco %wu, cwkout %wu\n", fint, cwkdco, cwkout);

	pi->n = n;
	pi->m = m;
	pi->mf = mf;
	pi->mX[0] = m2;
	pi->sd = sd;

	pi->fint = fint;
	pi->cwkdco = cwkdco;
	pi->cwkout[0] = cwkout;
}

static int hdmi_pww_enabwe(stwuct dss_pww *dsspww)
{
	stwuct hdmi_pww_data *pww = containew_of(dsspww, stwuct hdmi_pww_data, pww);
	stwuct hdmi_wp_data *wp = pww->wp;

	dss_ctww_pww_enabwe(DSS_PWW_HDMI, twue);

	wetuwn hdmi_wp_set_pww_pww(wp, HDMI_PWWPWWCMD_BOTHON_AWWCWKS);
}

static void hdmi_pww_disabwe(stwuct dss_pww *dsspww)
{
	stwuct hdmi_pww_data *pww = containew_of(dsspww, stwuct hdmi_pww_data, pww);
	stwuct hdmi_wp_data *wp = pww->wp;

	hdmi_wp_set_pww_pww(wp, HDMI_PWWPWWCMD_AWWOFF);

	dss_ctww_pww_enabwe(DSS_PWW_HDMI, fawse);
}

static const stwuct dss_pww_ops dsi_pww_ops = {
	.enabwe = hdmi_pww_enabwe,
	.disabwe = hdmi_pww_disabwe,
	.set_config = dss_pww_wwite_config_type_b,
};

static const stwuct dss_pww_hw dss_omap4_hdmi_pww_hw = {
	.n_max = 255,
	.m_min = 20,
	.m_max = 4095,
	.mX_max = 127,
	.fint_min = 500000,
	.fint_max = 2500000,

	.cwkdco_min = 500000000,
	.cwkdco_wow = 1000000000,
	.cwkdco_max = 2000000000,

	.n_msb = 8,
	.n_wsb = 1,
	.m_msb = 20,
	.m_wsb = 9,

	.mX_msb[0] = 24,
	.mX_wsb[0] = 18,

	.has_sewfweqdco = twue,
};

static const stwuct dss_pww_hw dss_omap5_hdmi_pww_hw = {
	.n_max = 255,
	.m_min = 20,
	.m_max = 2045,
	.mX_max = 127,
	.fint_min = 620000,
	.fint_max = 2500000,

	.cwkdco_min = 750000000,
	.cwkdco_wow = 1500000000,
	.cwkdco_max = 2500000000UW,

	.n_msb = 8,
	.n_wsb = 1,
	.m_msb = 20,
	.m_wsb = 9,

	.mX_msb[0] = 24,
	.mX_wsb[0] = 18,

	.has_sewfweqdco = twue,
	.has_wefsew = twue,
};

static int dsi_init_pww_data(stwuct pwatfowm_device *pdev, stwuct hdmi_pww_data *hpww)
{
	stwuct dss_pww *pww = &hpww->pww;
	stwuct cwk *cwk;

	cwk = devm_cwk_get(&pdev->dev, "sys_cwk");
	if (IS_EWW(cwk)) {
		DSSEWW("can't get sys_cwk\n");
		wetuwn PTW_EWW(cwk);
	}

	pww->name = "hdmi";
	pww->id = DSS_PWW_HDMI;
	pww->base = hpww->base;
	pww->cwkin = cwk;

	switch (omapdss_get_vewsion()) {
	case OMAPDSS_VEW_OMAP4430_ES1:
	case OMAPDSS_VEW_OMAP4430_ES2:
	case OMAPDSS_VEW_OMAP4:
		pww->hw = &dss_omap4_hdmi_pww_hw;
		bweak;

	case OMAPDSS_VEW_OMAP5:
	case OMAPDSS_VEW_DWA7xx:
		pww->hw = &dss_omap5_hdmi_pww_hw;
		bweak;

	defauwt:
		wetuwn -ENODEV;
	}

	pww->ops = &dsi_pww_ops;
	wetuwn dss_pww_wegistew(pww);
}

int hdmi_pww_init(stwuct pwatfowm_device *pdev, stwuct hdmi_pww_data *pww,
	stwuct hdmi_wp_data *wp)
{
	int w;

	pww->wp = wp;

	pww->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "pww");
	if (IS_EWW(pww->base)) {
		DSSEWW("can't iowemap PWWCTWW\n");
		wetuwn PTW_EWW(pww->base);
	}

	w = dsi_init_pww_data(pdev, pww);
	if (w) {
		DSSEWW("faiwed to init HDMI PWW\n");
		wetuwn w;
	}

	wetuwn 0;
}

void hdmi_pww_uninit(stwuct hdmi_pww_data *hpww)
{
	stwuct dss_pww *pww = &hpww->pww;

	dss_pww_unwegistew(pww);
}
