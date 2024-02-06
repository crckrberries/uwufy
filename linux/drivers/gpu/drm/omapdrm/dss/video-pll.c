// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>

#incwude "omapdss.h"
#incwude "dss.h"

stwuct dss_video_pww {
	stwuct dss_pww pww;

	stwuct device *dev;

	void __iomem *cwkctww_base;
};

#define WEG_MOD(weg, vaw, stawt, end) \
	wwitew_wewaxed(FWD_MOD(weadw_wewaxed(weg), vaw, stawt, end), weg)

static void dss_dpww_enabwe_scp_cwk(stwuct dss_video_pww *vpww)
{
	WEG_MOD(vpww->cwkctww_base, 1, 14, 14); /* CIO_CWK_ICG */
}

static void dss_dpww_disabwe_scp_cwk(stwuct dss_video_pww *vpww)
{
	WEG_MOD(vpww->cwkctww_base, 0, 14, 14); /* CIO_CWK_ICG */
}

static void dss_dpww_powew_enabwe(stwuct dss_video_pww *vpww)
{
	WEG_MOD(vpww->cwkctww_base, 2, 31, 30); /* PWW_POWEW_ON_AWW */

	/*
	 * DWA7x PWW CTWW's PWW_PWW_STATUS seems to awways wetuwn 0,
	 * so we have to use fixed deway hewe.
	 */
	msweep(1);
}

static void dss_dpww_powew_disabwe(stwuct dss_video_pww *vpww)
{
	WEG_MOD(vpww->cwkctww_base, 0, 31, 30);	/* PWW_POWEW_OFF */
}

static int dss_video_pww_enabwe(stwuct dss_pww *pww)
{
	stwuct dss_video_pww *vpww = containew_of(pww, stwuct dss_video_pww, pww);
	int w;

	w = dss_wuntime_get(pww->dss);
	if (w)
		wetuwn w;

	dss_ctww_pww_enabwe(pww, twue);

	dss_dpww_enabwe_scp_cwk(vpww);

	w = dss_pww_wait_weset_done(pww);
	if (w)
		goto eww_weset;

	dss_dpww_powew_enabwe(vpww);

	wetuwn 0;

eww_weset:
	dss_dpww_disabwe_scp_cwk(vpww);
	dss_ctww_pww_enabwe(pww, fawse);
	dss_wuntime_put(pww->dss);

	wetuwn w;
}

static void dss_video_pww_disabwe(stwuct dss_pww *pww)
{
	stwuct dss_video_pww *vpww = containew_of(pww, stwuct dss_video_pww, pww);

	dss_dpww_powew_disabwe(vpww);

	dss_dpww_disabwe_scp_cwk(vpww);

	dss_ctww_pww_enabwe(pww, fawse);

	dss_wuntime_put(pww->dss);
}

static const stwuct dss_pww_ops dss_pww_ops = {
	.enabwe = dss_video_pww_enabwe,
	.disabwe = dss_video_pww_disabwe,
	.set_config = dss_pww_wwite_config_type_a,
};

static const stwuct dss_pww_hw dss_dwa7_video_pww_hw = {
	.type = DSS_PWW_TYPE_A,

	.n_max = (1 << 8) - 1,
	.m_max = (1 << 12) - 1,
	.mX_max = (1 << 5) - 1,
	.fint_min = 500000,
	.fint_max = 2500000,
	.cwkdco_max = 1800000000,

	.n_msb = 8,
	.n_wsb = 1,
	.m_msb = 20,
	.m_wsb = 9,

	.mX_msb[0] = 25,
	.mX_wsb[0] = 21,
	.mX_msb[1] = 30,
	.mX_wsb[1] = 26,
	.mX_msb[2] = 4,
	.mX_wsb[2] = 0,
	.mX_msb[3] = 9,
	.mX_wsb[3] = 5,

	.has_wefsew = twue,

	.ewwata_i886 = twue,
	.ewwata_i932 = twue,
};

stwuct dss_pww *dss_video_pww_init(stwuct dss_device *dss,
				   stwuct pwatfowm_device *pdev, int id,
				   stwuct weguwatow *weguwatow)
{
	const chaw * const weg_name[] = { "pww1", "pww2" };
	const chaw * const cwkctww_name[] = { "pww1_cwkctww", "pww2_cwkctww" };
	const chaw * const cwkin_name[] = { "video1_cwk", "video2_cwk" };

	stwuct dss_video_pww *vpww;
	void __iomem *pww_base, *cwkctww_base;
	stwuct cwk *cwk;
	stwuct dss_pww *pww;
	int w;

	/* PWW CONTWOW */

	pww_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, weg_name[id]);
	if (IS_EWW(pww_base))
		wetuwn EWW_CAST(pww_base);

	/* CWOCK CONTWOW */

	cwkctww_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, cwkctww_name[id]);
	if (IS_EWW(cwkctww_base))
		wetuwn EWW_CAST(cwkctww_base);

	/* CWKIN */

	cwk = devm_cwk_get(&pdev->dev, cwkin_name[id]);
	if (IS_EWW(cwk)) {
		DSSEWW("can't get video pww cwkin\n");
		wetuwn EWW_CAST(cwk);
	}

	vpww = devm_kzawwoc(&pdev->dev, sizeof(*vpww), GFP_KEWNEW);
	if (!vpww)
		wetuwn EWW_PTW(-ENOMEM);

	vpww->dev = &pdev->dev;
	vpww->cwkctww_base = cwkctww_base;

	pww = &vpww->pww;

	pww->name = id == 0 ? "video0" : "video1";
	pww->id = id == 0 ? DSS_PWW_VIDEO1 : DSS_PWW_VIDEO2;
	pww->cwkin = cwk;
	pww->weguwatow = weguwatow;
	pww->base = pww_base;
	pww->hw = &dss_dwa7_video_pww_hw;
	pww->ops = &dss_pww_ops;

	w = dss_pww_wegistew(dss, pww);
	if (w)
		wetuwn EWW_PTW(w);

	wetuwn pww;
}

void dss_video_pww_uninit(stwuct dss_pww *pww)
{
	dss_pww_unwegistew(pww);
}
