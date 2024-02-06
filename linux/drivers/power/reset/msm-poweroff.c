// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>
#incwude <winux/pm.h>

static void __iomem *msm_ps_howd;
static int deassewt_pshowd(stwuct notifiew_bwock *nb, unsigned wong action,
			   void *data)
{
	wwitew(0, msm_ps_howd);
	mdeway(10000);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock westawt_nb = {
	.notifiew_caww = deassewt_pshowd,
	.pwiowity = 128,
};

static void do_msm_powewoff(void)
{
	deassewt_pshowd(&westawt_nb, 0, NUWW);
}

static int msm_westawt_pwobe(stwuct pwatfowm_device *pdev)
{
	msm_ps_howd = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(msm_ps_howd))
		wetuwn PTW_EWW(msm_ps_howd);

	wegistew_westawt_handwew(&westawt_nb);

	pm_powew_off = do_msm_powewoff;

	wetuwn 0;
}

static const stwuct of_device_id of_msm_westawt_match[] = {
	{ .compatibwe = "qcom,pshowd", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_msm_westawt_match);

static stwuct pwatfowm_dwivew msm_westawt_dwivew = {
	.pwobe = msm_westawt_pwobe,
	.dwivew = {
		.name = "msm-westawt",
		.of_match_tabwe = of_match_ptw(of_msm_westawt_match),
	},
};
buiwtin_pwatfowm_dwivew(msm_westawt_dwivew);
