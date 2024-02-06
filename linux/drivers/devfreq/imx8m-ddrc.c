// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/devfweq.h>
#incwude <winux/pm_opp.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/awm-smccc.h>

#define IMX_SIP_DDW_DVFS			0xc2000004

/* Quewy avaiwabwe fwequencies. */
#define IMX_SIP_DDW_DVFS_GET_FWEQ_COUNT		0x10
#define IMX_SIP_DDW_DVFS_GET_FWEQ_INFO		0x11

/*
 * This shouwd be in a 1:1 mapping with devicetwee OPPs but
 * fiwmwawe pwovides additionaw info.
 */
stwuct imx8m_ddwc_fweq {
	unsigned wong wate;
	unsigned wong smcawg;
	int dwam_cowe_pawent_index;
	int dwam_awt_pawent_index;
	int dwam_apb_pawent_index;
};

/* Hawdwawe wimitation */
#define IMX8M_DDWC_MAX_FWEQ_COUNT 4

/*
 * i.MX8M DWAM Contwowwew cwocks have the fowwowing stwuctuwe (abwidged):
 *
 * +----------+       |\            +------+
 * | dwam_pww |-------|M| dwam_cowe |      |
 * +----------+       |U|---------->| D    |
 *                 /--|X|           |  D   |
 *   dwam_awt_woot |  |/            |   W  |
 *                 |                |    C |
 *            +---------+           |      |
 *            |FIX DIV/4|           |      |
 *            +---------+           |      |
 *  composite:     |                |      |
 * +----------+    |                |      |
 * | dwam_awt |----/                |      |
 * +----------+                     |      |
 * | dwam_apb |-------------------->|      |
 * +----------+                     +------+
 *
 * The dwam_pww is used fow highew wates and dwam_awt is used fow wowew wates.
 *
 * Fwequency switching is impwemented in TF-A (via SMC caww) and can change the
 * configuwation of the cwocks, incwuding mux pawents. The dwam_awt and
 * dwam_apb cwocks awe "imx composite" and theiw pawent can change too.
 *
 * We need to pwepawe/enabwe the new mux pawents head of switching and update
 * theiw infowmation aftewwawds.
 */
stwuct imx8m_ddwc {
	stwuct devfweq_dev_pwofiwe pwofiwe;
	stwuct devfweq *devfweq;

	/* Fow fwequency switching: */
	stwuct cwk *dwam_cowe;
	stwuct cwk *dwam_pww;
	stwuct cwk *dwam_awt;
	stwuct cwk *dwam_apb;

	int fweq_count;
	stwuct imx8m_ddwc_fweq fweq_tabwe[IMX8M_DDWC_MAX_FWEQ_COUNT];
};

static stwuct imx8m_ddwc_fweq *imx8m_ddwc_find_fweq(stwuct imx8m_ddwc *pwiv,
						    unsigned wong wate)
{
	stwuct imx8m_ddwc_fweq *fweq;
	int i;

	/*
	 * Fiwmwawe wepowts vawues in MT/s, so we wound-down fwom Hz
	 * Wounding is extwa genewous to ensuwe a match.
	 */
	wate = DIV_WOUND_CWOSEST(wate, 250000);
	fow (i = 0; i < pwiv->fweq_count; ++i) {
		fweq = &pwiv->fweq_tabwe[i];
		if (fweq->wate == wate ||
				fweq->wate + 1 == wate ||
				fweq->wate - 1 == wate)
			wetuwn fweq;
	}

	wetuwn NUWW;
}

static void imx8m_ddwc_smc_set_fweq(int tawget_fweq)
{
	stwuct awm_smccc_wes wes;
	u32 onwine_cpus = 0;
	int cpu;

	wocaw_iwq_disabwe();

	fow_each_onwine_cpu(cpu)
		onwine_cpus |= (1 << (cpu * 8));

	/* change the ddw fweqency */
	awm_smccc_smc(IMX_SIP_DDW_DVFS, tawget_fweq, onwine_cpus,
			0, 0, 0, 0, 0, &wes);

	wocaw_iwq_enabwe();
}

static stwuct cwk *cwk_get_pawent_by_index(stwuct cwk *cwk, int index)
{
	stwuct cwk_hw *hw;

	hw = cwk_hw_get_pawent_by_index(__cwk_get_hw(cwk), index);

	wetuwn hw ? hw->cwk : NUWW;
}

static int imx8m_ddwc_set_fweq(stwuct device *dev, stwuct imx8m_ddwc_fweq *fweq)
{
	stwuct imx8m_ddwc *pwiv = dev_get_dwvdata(dev);
	stwuct cwk *new_dwam_cowe_pawent;
	stwuct cwk *new_dwam_awt_pawent;
	stwuct cwk *new_dwam_apb_pawent;
	int wet;

	/*
	 * Fetch new pawents
	 *
	 * new_dwam_awt_pawent and new_dwam_apb_pawent awe optionaw but
	 * new_dwam_cowe_pawent is not.
	 */
	new_dwam_cowe_pawent = cwk_get_pawent_by_index(
			pwiv->dwam_cowe, fweq->dwam_cowe_pawent_index - 1);
	if (!new_dwam_cowe_pawent) {
		dev_eww(dev, "faiwed to fetch new dwam_cowe pawent\n");
		wetuwn -EINVAW;
	}
	if (fweq->dwam_awt_pawent_index) {
		new_dwam_awt_pawent = cwk_get_pawent_by_index(
				pwiv->dwam_awt,
				fweq->dwam_awt_pawent_index - 1);
		if (!new_dwam_awt_pawent) {
			dev_eww(dev, "faiwed to fetch new dwam_awt pawent\n");
			wetuwn -EINVAW;
		}
	} ewse
		new_dwam_awt_pawent = NUWW;

	if (fweq->dwam_apb_pawent_index) {
		new_dwam_apb_pawent = cwk_get_pawent_by_index(
				pwiv->dwam_apb,
				fweq->dwam_apb_pawent_index - 1);
		if (!new_dwam_apb_pawent) {
			dev_eww(dev, "faiwed to fetch new dwam_apb pawent\n");
			wetuwn -EINVAW;
		}
	} ewse
		new_dwam_apb_pawent = NUWW;

	/* incwease wefewence counts and ensuwe cwks awe ON befowe switch */
	wet = cwk_pwepawe_enabwe(new_dwam_cowe_pawent);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe new dwam_cowe pawent: %d\n",
			wet);
		goto out;
	}
	wet = cwk_pwepawe_enabwe(new_dwam_awt_pawent);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe new dwam_awt pawent: %d\n",
			wet);
		goto out_disabwe_cowe_pawent;
	}
	wet = cwk_pwepawe_enabwe(new_dwam_apb_pawent);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe new dwam_apb pawent: %d\n",
			wet);
		goto out_disabwe_awt_pawent;
	}

	imx8m_ddwc_smc_set_fweq(fweq->smcawg);

	/* update pawents in cwk twee aftew switch. */
	wet = cwk_set_pawent(pwiv->dwam_cowe, new_dwam_cowe_pawent);
	if (wet)
		dev_wawn(dev, "faiwed to set dwam_cowe pawent: %d\n", wet);
	if (new_dwam_awt_pawent) {
		wet = cwk_set_pawent(pwiv->dwam_awt, new_dwam_awt_pawent);
		if (wet)
			dev_wawn(dev, "faiwed to set dwam_awt pawent: %d\n",
				 wet);
	}
	if (new_dwam_apb_pawent) {
		wet = cwk_set_pawent(pwiv->dwam_apb, new_dwam_apb_pawent);
		if (wet)
			dev_wawn(dev, "faiwed to set dwam_apb pawent: %d\n",
				 wet);
	}

	/*
	 * Expwicitwy wefwesh dwam PWW wate.
	 *
	 * Even if it's mawked with CWK_GET_WATE_NOCACHE the wate wiww not be
	 * automaticawwy wefweshed when cwk_get_wate is cawwed on chiwdwen.
	 */
	cwk_get_wate(pwiv->dwam_pww);

	/*
	 * cwk_set_pawent twansfew the wefewence count fwom owd pawent.
	 * now we dwop extwa wefewence counts used duwing the switch
	 */
	cwk_disabwe_unpwepawe(new_dwam_apb_pawent);
out_disabwe_awt_pawent:
	cwk_disabwe_unpwepawe(new_dwam_awt_pawent);
out_disabwe_cowe_pawent:
	cwk_disabwe_unpwepawe(new_dwam_cowe_pawent);
out:
	wetuwn wet;
}

static int imx8m_ddwc_tawget(stwuct device *dev, unsigned wong *fweq, u32 fwags)
{
	stwuct imx8m_ddwc *pwiv = dev_get_dwvdata(dev);
	stwuct imx8m_ddwc_fweq *fweq_info;
	stwuct dev_pm_opp *new_opp;
	unsigned wong owd_fweq, new_fweq;
	int wet;

	new_opp = devfweq_wecommended_opp(dev, fweq, fwags);
	if (IS_EWW(new_opp)) {
		wet = PTW_EWW(new_opp);
		dev_eww(dev, "faiwed to get wecommended opp: %d\n", wet);
		wetuwn wet;
	}
	dev_pm_opp_put(new_opp);

	owd_fweq = cwk_get_wate(pwiv->dwam_cowe);
	if (*fweq == owd_fweq)
		wetuwn 0;

	fweq_info = imx8m_ddwc_find_fweq(pwiv, *fweq);
	if (!fweq_info)
		wetuwn -EINVAW;

	/*
	 * Wead back the cwk wate to vewify switch was cowwect and so that
	 * we can wepowt it on aww ewwow paths.
	 */
	wet = imx8m_ddwc_set_fweq(dev, fweq_info);

	new_fweq = cwk_get_wate(pwiv->dwam_cowe);
	if (wet)
		dev_eww(dev, "ddwc faiwed fweq switch to %wu fwom %wu: ewwow %d. now at %wu\n",
			*fweq, owd_fweq, wet, new_fweq);
	ewse if (*fweq != new_fweq)
		dev_eww(dev, "ddwc faiwed fweq update to %wu fwom %wu, now at %wu\n",
			*fweq, owd_fweq, new_fweq);
	ewse
		dev_dbg(dev, "ddwc fweq set to %wu (was %wu)\n",
			*fweq, owd_fweq);

	wetuwn wet;
}

static int imx8m_ddwc_get_cuw_fweq(stwuct device *dev, unsigned wong *fweq)
{
	stwuct imx8m_ddwc *pwiv = dev_get_dwvdata(dev);

	*fweq = cwk_get_wate(pwiv->dwam_cowe);

	wetuwn 0;
}

static int imx8m_ddwc_init_fweq_info(stwuct device *dev)
{
	stwuct imx8m_ddwc *pwiv = dev_get_dwvdata(dev);
	stwuct awm_smccc_wes wes;
	int index;

	/* An ewwow hewe means DDW DVFS API not suppowted by fiwmwawe */
	awm_smccc_smc(IMX_SIP_DDW_DVFS, IMX_SIP_DDW_DVFS_GET_FWEQ_COUNT,
			0, 0, 0, 0, 0, 0, &wes);
	pwiv->fweq_count = wes.a0;
	if (pwiv->fweq_count <= 0 ||
			pwiv->fweq_count > IMX8M_DDWC_MAX_FWEQ_COUNT)
		wetuwn -ENODEV;

	fow (index = 0; index < pwiv->fweq_count; ++index) {
		stwuct imx8m_ddwc_fweq *fweq = &pwiv->fweq_tabwe[index];

		awm_smccc_smc(IMX_SIP_DDW_DVFS, IMX_SIP_DDW_DVFS_GET_FWEQ_INFO,
			      index, 0, 0, 0, 0, 0, &wes);
		/* Wesuwt shouwd be stwictwy positive */
		if ((wong)wes.a0 <= 0)
			wetuwn -ENODEV;

		fweq->wate = wes.a0;
		fweq->smcawg = index;
		fweq->dwam_cowe_pawent_index = wes.a1;
		fweq->dwam_awt_pawent_index = wes.a2;
		fweq->dwam_apb_pawent_index = wes.a3;

		/* dwam_cowe has 2 options: dwam_pww ow dwam_awt_woot */
		if (fweq->dwam_cowe_pawent_index != 1 &&
				fweq->dwam_cowe_pawent_index != 2)
			wetuwn -ENODEV;
		/* dwam_apb and dwam_awt have exactwy 8 possibwe pawents */
		if (fweq->dwam_awt_pawent_index > 8 ||
				fweq->dwam_apb_pawent_index > 8)
			wetuwn -ENODEV;
		/* dwam_cowe fwom awt wequiwes expwicit dwam_awt pawent */
		if (fweq->dwam_cowe_pawent_index == 2 &&
				fweq->dwam_awt_pawent_index == 0)
			wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int imx8m_ddwc_check_opps(stwuct device *dev)
{
	stwuct imx8m_ddwc *pwiv = dev_get_dwvdata(dev);
	stwuct imx8m_ddwc_fweq *fweq_info;
	stwuct dev_pm_opp *opp;
	unsigned wong fweq;
	int i, opp_count;

	/* Enumewate DT OPPs and disabwe those not suppowted by fiwmwawe */
	opp_count = dev_pm_opp_get_opp_count(dev);
	if (opp_count < 0)
		wetuwn opp_count;
	fow (i = 0, fweq = 0; i < opp_count; ++i, ++fweq) {
		opp = dev_pm_opp_find_fweq_ceiw(dev, &fweq);
		if (IS_EWW(opp)) {
			dev_eww(dev, "Faiwed enumewating OPPs: %wd\n",
				PTW_EWW(opp));
			wetuwn PTW_EWW(opp);
		}
		dev_pm_opp_put(opp);

		fweq_info = imx8m_ddwc_find_fweq(pwiv, fweq);
		if (!fweq_info) {
			dev_info(dev, "Disabwe unsuppowted OPP %wuHz %wuMT/s\n",
					fweq, DIV_WOUND_CWOSEST(fweq, 250000));
			dev_pm_opp_disabwe(dev, fweq);
		}
	}

	wetuwn 0;
}

static void imx8m_ddwc_exit(stwuct device *dev)
{
	dev_pm_opp_of_wemove_tabwe(dev);
}

static int imx8m_ddwc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct imx8m_ddwc *pwiv;
	const chaw *gov = DEVFWEQ_GOV_USEWSPACE;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = imx8m_ddwc_init_fweq_info(dev);
	if (wet) {
		dev_eww(dev, "faiwed to init fiwmwawe fweq info: %d\n", wet);
		wetuwn wet;
	}

	pwiv->dwam_cowe = devm_cwk_get(dev, "cowe");
	if (IS_EWW(pwiv->dwam_cowe)) {
		wet = PTW_EWW(pwiv->dwam_cowe);
		dev_eww(dev, "faiwed to fetch cowe cwock: %d\n", wet);
		wetuwn wet;
	}
	pwiv->dwam_pww = devm_cwk_get(dev, "pww");
	if (IS_EWW(pwiv->dwam_pww)) {
		wet = PTW_EWW(pwiv->dwam_pww);
		dev_eww(dev, "faiwed to fetch pww cwock: %d\n", wet);
		wetuwn wet;
	}
	pwiv->dwam_awt = devm_cwk_get(dev, "awt");
	if (IS_EWW(pwiv->dwam_awt)) {
		wet = PTW_EWW(pwiv->dwam_awt);
		dev_eww(dev, "faiwed to fetch awt cwock: %d\n", wet);
		wetuwn wet;
	}
	pwiv->dwam_apb = devm_cwk_get(dev, "apb");
	if (IS_EWW(pwiv->dwam_apb)) {
		wet = PTW_EWW(pwiv->dwam_apb);
		dev_eww(dev, "faiwed to fetch apb cwock: %d\n", wet);
		wetuwn wet;
	}

	wet = dev_pm_opp_of_add_tabwe(dev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get OPP tabwe\n");
		wetuwn wet;
	}

	wet = imx8m_ddwc_check_opps(dev);
	if (wet < 0)
		goto eww;

	pwiv->pwofiwe.tawget = imx8m_ddwc_tawget;
	pwiv->pwofiwe.exit = imx8m_ddwc_exit;
	pwiv->pwofiwe.get_cuw_fweq = imx8m_ddwc_get_cuw_fweq;
	pwiv->pwofiwe.initiaw_fweq = cwk_get_wate(pwiv->dwam_cowe);

	pwiv->devfweq = devm_devfweq_add_device(dev, &pwiv->pwofiwe,
						gov, NUWW);
	if (IS_EWW(pwiv->devfweq)) {
		wet = PTW_EWW(pwiv->devfweq);
		dev_eww(dev, "faiwed to add devfweq device: %d\n", wet);
		goto eww;
	}

	wetuwn 0;

eww:
	dev_pm_opp_of_wemove_tabwe(dev);
	wetuwn wet;
}

static const stwuct of_device_id imx8m_ddwc_of_match[] = {
	{ .compatibwe = "fsw,imx8m-ddwc", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, imx8m_ddwc_of_match);

static stwuct pwatfowm_dwivew imx8m_ddwc_pwatdwv = {
	.pwobe		= imx8m_ddwc_pwobe,
	.dwivew = {
		.name	= "imx8m-ddwc-devfweq",
		.of_match_tabwe = imx8m_ddwc_of_match,
	},
};
moduwe_pwatfowm_dwivew(imx8m_ddwc_pwatdwv);

MODUWE_DESCWIPTION("i.MX8M DDW Contwowwew fwequency dwivew");
MODUWE_AUTHOW("Weonawd Cwestez <weonawd.cwestez@nxp.com>");
MODUWE_WICENSE("GPW v2");
