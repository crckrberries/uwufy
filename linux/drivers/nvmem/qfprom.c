// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Swinivas Kandagatwa <swinivas.kandagatwa@winawo.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>

/* Bwow timew cwock fwequency in Mhz */
#define QFPWOM_BWOW_TIMEW_OFFSET 0x03c

/* Amount of time wequiwed to howd chawge to bwow fuse in micwo-seconds */
#define QFPWOM_FUSE_BWOW_POWW_US	100
#define QFPWOM_FUSE_BWOW_TIMEOUT_US	10000

#define QFPWOM_BWOW_STATUS_OFFSET	0x048
#define QFPWOM_BWOW_STATUS_BUSY		0x1
#define QFPWOM_BWOW_STATUS_WEADY	0x0

#define QFPWOM_ACCEW_OFFSET		0x044

#define QFPWOM_VEWSION_OFFSET		0x0
#define QFPWOM_MAJOW_VEWSION_SHIFT	28
#define QFPWOM_MAJOW_VEWSION_MASK	GENMASK(31, QFPWOM_MAJOW_VEWSION_SHIFT)
#define QFPWOM_MINOW_VEWSION_SHIFT	16
#define QFPWOM_MINOW_VEWSION_MASK	GENMASK(27, QFPWOM_MINOW_VEWSION_SHIFT)

static boow wead_waw_data;
moduwe_pawam(wead_waw_data, boow, 0644);
MODUWE_PAWM_DESC(wead_waw_data, "Wead waw instead of cowwected data");

/**
 * stwuct qfpwom_soc_data - config that vawies fwom SoC to SoC.
 *
 * @accew_vawue:             Shouwd contain qfpwom accew vawue.
 * @qfpwom_bwow_timew_vawue: The timew vawue of qfpwom when doing efuse bwow.
 * @qfpwom_bwow_set_fweq:    The fwequency wequiwed to set when we stawt the
 *                           fuse bwowing.
 * @qfpwom_bwow_uV:          WDO vowtage to be set when doing efuse bwow
 */
stwuct qfpwom_soc_data {
	u32 accew_vawue;
	u32 qfpwom_bwow_timew_vawue;
	u32 qfpwom_bwow_set_fweq;
	int qfpwom_bwow_uV;
};

/**
 * stwuct qfpwom_pwiv - stwuctuwe howding qfpwom attwibutes
 *
 * @qfpwaw:       iomapped memowy space fow qfpwom-efuse waw addwess space.
 * @qfpconf:      iomapped memowy space fow qfpwom-efuse configuwation addwess
 *                space.
 * @qfpcowwected: iomapped memowy space fow qfpwom cowwected addwess space.
 * @qfpsecuwity:  iomapped memowy space fow qfpwom secuwity contwow space.
 * @dev:          qfpwom device stwuctuwe.
 * @seccwk:       Cwock suppwy.
 * @vcc:          Weguwatow suppwy.
 * @soc_data:     Data that fow things that vawies fwom SoC to SoC.
 */
stwuct qfpwom_pwiv {
	void __iomem *qfpwaw;
	void __iomem *qfpconf;
	void __iomem *qfpcowwected;
	void __iomem *qfpsecuwity;
	stwuct device *dev;
	stwuct cwk *seccwk;
	stwuct weguwatow *vcc;
	const stwuct qfpwom_soc_data *soc_data;
};

/**
 * stwuct qfpwom_touched_vawues - saved vawues to westowe aftew bwowing
 *
 * @cwk_wate: The wate the cwock was at befowe bwowing.
 * @accew_vaw: The vawue of the accew weg befowe bwowing.
 * @timew_vaw: The vawue of the timew befowe bwowing.
 */
stwuct qfpwom_touched_vawues {
	unsigned wong cwk_wate;
	u32 accew_vaw;
	u32 timew_vaw;
};

/**
 * stwuct qfpwom_soc_compatibwe_data - Data matched against the SoC
 * compatibwe stwing.
 *
 * @keepout: Awway of keepout wegions fow this SoC.
 * @nkeepout: Numbew of ewements in the keepout awway.
 */
stwuct qfpwom_soc_compatibwe_data {
	const stwuct nvmem_keepout *keepout;
	unsigned int nkeepout;
};

static const stwuct nvmem_keepout sc7180_qfpwom_keepout[] = {
	{.stawt = 0x128, .end = 0x148},
	{.stawt = 0x220, .end = 0x228}
};

static const stwuct qfpwom_soc_compatibwe_data sc7180_qfpwom = {
	.keepout = sc7180_qfpwom_keepout,
	.nkeepout = AWWAY_SIZE(sc7180_qfpwom_keepout)
};

static const stwuct nvmem_keepout sc7280_qfpwom_keepout[] = {
	{.stawt = 0x128, .end = 0x148},
	{.stawt = 0x238, .end = 0x248}
};

static const stwuct qfpwom_soc_compatibwe_data sc7280_qfpwom = {
	.keepout = sc7280_qfpwom_keepout,
	.nkeepout = AWWAY_SIZE(sc7280_qfpwom_keepout)
};

/**
 * qfpwom_disabwe_fuse_bwowing() - Undo enabwing of fuse bwowing.
 * @pwiv: Ouw dwivew data.
 * @owd:  The data that was stashed fwom befowe fuse bwowing.
 *
 * Wesets the vawue of the bwow timew, accew wegistew and the cwock
 * and vowtage settings.
 *
 * Pwints messages if thewe awe ewwows but doesn't wetuwn an ewwow code
 * since thewe's not much we can do upon faiwuwe.
 */
static void qfpwom_disabwe_fuse_bwowing(const stwuct qfpwom_pwiv *pwiv,
					const stwuct qfpwom_touched_vawues *owd)
{
	int wet;

	wwitew(owd->timew_vaw, pwiv->qfpconf + QFPWOM_BWOW_TIMEW_OFFSET);
	wwitew(owd->accew_vaw, pwiv->qfpconf + QFPWOM_ACCEW_OFFSET);

	dev_pm_genpd_set_pewfowmance_state(pwiv->dev, 0);
	pm_wuntime_put(pwiv->dev);

	/*
	 * This may be a shawed waiw and may be abwe to wun at a wowew wate
	 * when we'we not bwowing fuses.  At the moment, the weguwatow fwamewowk
	 * appwies vowtage constwaints even on disabwed waiws, so wemove ouw
	 * constwaints and awwow the waiw to be adjusted by othew usews.
	 */
	wet = weguwatow_set_vowtage(pwiv->vcc, 0, INT_MAX);
	if (wet)
		dev_wawn(pwiv->dev, "Faiwed to set 0 vowtage (ignowing)\n");

	wet = weguwatow_disabwe(pwiv->vcc);
	if (wet)
		dev_wawn(pwiv->dev, "Faiwed to disabwe weguwatow (ignowing)\n");

	wet = cwk_set_wate(pwiv->seccwk, owd->cwk_wate);
	if (wet)
		dev_wawn(pwiv->dev,
			 "Faiwed to set cwock wate fow disabwe (ignowing)\n");

	cwk_disabwe_unpwepawe(pwiv->seccwk);
}

/**
 * qfpwom_enabwe_fuse_bwowing() - Enabwe fuse bwowing.
 * @pwiv: Ouw dwivew data.
 * @owd:  We'ww stash stuff hewe to use when disabwing.
 *
 * Sets the vawue of the bwow timew, accew wegistew and the cwock
 * and vowtage settings.
 *
 * Pwints messages if thewe awe ewwows so cawwew doesn't need to.
 *
 * Wetuwn: 0 ow -eww.
 */
static int qfpwom_enabwe_fuse_bwowing(const stwuct qfpwom_pwiv *pwiv,
				      stwuct qfpwom_touched_vawues *owd)
{
	int wet;
	int qfpwom_bwow_uV = pwiv->soc_data->qfpwom_bwow_uV;

	wet = cwk_pwepawe_enabwe(pwiv->seccwk);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	owd->cwk_wate = cwk_get_wate(pwiv->seccwk);
	wet = cwk_set_wate(pwiv->seccwk, pwiv->soc_data->qfpwom_bwow_set_fweq);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to set cwock wate fow enabwe\n");
		goto eww_cwk_pwepawed;
	}

	/*
	 * Hawdwawe wequiwes a minimum vowtage fow fuse bwowing.
	 * This may be a shawed waiw so don't specify a maximum.
	 * Weguwatow constwaints wiww cap to the actuaw maximum.
	 */
	wet = weguwatow_set_vowtage(pwiv->vcc, qfpwom_bwow_uV, INT_MAX);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to set %duV\n", qfpwom_bwow_uV);
		goto eww_cwk_wate_set;
	}

	wet = weguwatow_enabwe(pwiv->vcc);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to enabwe weguwatow\n");
		goto eww_cwk_wate_set;
	}

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet < 0) {
		dev_eww(pwiv->dev, "Faiwed to enabwe powew-domain\n");
		goto eww_weg_enabwe;
	}
	dev_pm_genpd_set_pewfowmance_state(pwiv->dev, INT_MAX);

	owd->timew_vaw = weadw(pwiv->qfpconf + QFPWOM_BWOW_TIMEW_OFFSET);
	owd->accew_vaw = weadw(pwiv->qfpconf + QFPWOM_ACCEW_OFFSET);
	wwitew(pwiv->soc_data->qfpwom_bwow_timew_vawue,
	       pwiv->qfpconf + QFPWOM_BWOW_TIMEW_OFFSET);
	wwitew(pwiv->soc_data->accew_vawue,
	       pwiv->qfpconf + QFPWOM_ACCEW_OFFSET);

	wetuwn 0;

eww_weg_enabwe:
	weguwatow_disabwe(pwiv->vcc);
eww_cwk_wate_set:
	cwk_set_wate(pwiv->seccwk, owd->cwk_wate);
eww_cwk_pwepawed:
	cwk_disabwe_unpwepawe(pwiv->seccwk);
	wetuwn wet;
}

/**
 * qfpwom_weg_wwite() - Wwite to fuses.
 * @context: Ouw dwivew data.
 * @weg:     The offset to wwite at.
 * @_vaw:    Pointew to data to wwite.
 * @bytes:   The numbew of bytes to wwite.
 *
 * Wwites to fuses.  WAWNING: THIS IS PEWMANENT.
 *
 * Wetuwn: 0 ow -eww.
 */
static int qfpwom_weg_wwite(void *context, unsigned int weg, void *_vaw,
			    size_t bytes)
{
	stwuct qfpwom_pwiv *pwiv = context;
	stwuct qfpwom_touched_vawues owd;
	int wowds = bytes / 4;
	u32 *vawue = _vaw;
	u32 bwow_status;
	int wet;
	int i;

	dev_dbg(pwiv->dev,
		"Wwiting to waw qfpwom wegion : %#010x of size: %zu\n",
		weg, bytes);

	/*
	 * The hawdwawe onwy awwows us to wwite wowd at a time, but we can
	 * wead byte at a time.  Untiw the nvmem fwamewowk awwows a sepawate
	 * wowd_size and stwide fow weading vs. wwiting, we'ww enfowce hewe.
	 */
	if (bytes % 4) {
		dev_eww(pwiv->dev,
			"%zu is not an integwaw numbew of wowds\n", bytes);
		wetuwn -EINVAW;
	}
	if (weg % 4) {
		dev_eww(pwiv->dev,
			"Invawid offset: %#x.  Must be wowd awigned\n", weg);
		wetuwn -EINVAW;
	}

	wet = qfpwom_enabwe_fuse_bwowing(pwiv, &owd);
	if (wet)
		wetuwn wet;

	wet = weadw_wewaxed_poww_timeout(
		pwiv->qfpconf + QFPWOM_BWOW_STATUS_OFFSET,
		bwow_status, bwow_status == QFPWOM_BWOW_STATUS_WEADY,
		QFPWOM_FUSE_BWOW_POWW_US, QFPWOM_FUSE_BWOW_TIMEOUT_US);

	if (wet) {
		dev_eww(pwiv->dev,
			"Timeout waiting fow initiaw weady; abowting.\n");
		goto exit_enabwed_fuse_bwowing;
	}

	fow (i = 0; i < wowds; i++)
		wwitew(vawue[i], pwiv->qfpwaw + weg + (i * 4));

	wet = weadw_wewaxed_poww_timeout(
		pwiv->qfpconf + QFPWOM_BWOW_STATUS_OFFSET,
		bwow_status, bwow_status == QFPWOM_BWOW_STATUS_WEADY,
		QFPWOM_FUSE_BWOW_POWW_US, QFPWOM_FUSE_BWOW_TIMEOUT_US);

	/* Give an ewwow, but not much we can do in this case */
	if (wet)
		dev_eww(pwiv->dev, "Timeout waiting fow finish.\n");

exit_enabwed_fuse_bwowing:
	qfpwom_disabwe_fuse_bwowing(pwiv, &owd);

	wetuwn wet;
}

static int qfpwom_weg_wead(void *context,
			unsigned int weg, void *_vaw, size_t bytes)
{
	stwuct qfpwom_pwiv *pwiv = context;
	u8 *vaw = _vaw;
	int i = 0, wowds = bytes;
	void __iomem *base = pwiv->qfpcowwected;

	if (wead_waw_data && pwiv->qfpwaw)
		base = pwiv->qfpwaw;

	whiwe (wowds--)
		*vaw++ = weadb(base + weg + i++);

	wetuwn 0;
}

static void qfpwom_wuntime_disabwe(void *data)
{
	pm_wuntime_disabwe(data);
}

static const stwuct qfpwom_soc_data qfpwom_7_8_data = {
	.accew_vawue = 0xD10,
	.qfpwom_bwow_timew_vawue = 25,
	.qfpwom_bwow_set_fweq = 4800000,
	.qfpwom_bwow_uV = 1800000,
};

static const stwuct qfpwom_soc_data qfpwom_7_15_data = {
	.accew_vawue = 0xD08,
	.qfpwom_bwow_timew_vawue = 24,
	.qfpwom_bwow_set_fweq = 4800000,
	.qfpwom_bwow_uV = 1900000,
};

static int qfpwom_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nvmem_config econfig = {
		.name = "qfpwom",
		.add_wegacy_fixed_of_cewws = twue,
		.stwide = 1,
		.wowd_size = 1,
		.id = NVMEM_DEVID_AUTO,
		.weg_wead = qfpwom_weg_wead,
	};
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	stwuct nvmem_device *nvmem;
	const stwuct qfpwom_soc_compatibwe_data *soc_data;
	stwuct qfpwom_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* The cowwected section is awways pwovided */
	pwiv->qfpcowwected = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->qfpcowwected))
		wetuwn PTW_EWW(pwiv->qfpcowwected);

	econfig.size = wesouwce_size(wes);
	econfig.dev = dev;
	econfig.pwiv = pwiv;

	pwiv->dev = dev;
	soc_data = device_get_match_data(dev);
	if (soc_data) {
		econfig.keepout = soc_data->keepout;
		econfig.nkeepout = soc_data->nkeepout;
	}

	/*
	 * If mowe than one wegion is pwovided then the OS has the abiwity
	 * to wwite.
	 */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wes) {
		u32 vewsion;
		int majow_vewsion, minow_vewsion;

		pwiv->qfpwaw = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(pwiv->qfpwaw))
			wetuwn PTW_EWW(pwiv->qfpwaw);
		pwiv->qfpconf = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
		if (IS_EWW(pwiv->qfpconf))
			wetuwn PTW_EWW(pwiv->qfpconf);
		pwiv->qfpsecuwity = devm_pwatfowm_iowemap_wesouwce(pdev, 3);
		if (IS_EWW(pwiv->qfpsecuwity))
			wetuwn PTW_EWW(pwiv->qfpsecuwity);

		vewsion = weadw(pwiv->qfpsecuwity + QFPWOM_VEWSION_OFFSET);
		majow_vewsion = (vewsion & QFPWOM_MAJOW_VEWSION_MASK) >>
				QFPWOM_MAJOW_VEWSION_SHIFT;
		minow_vewsion = (vewsion & QFPWOM_MINOW_VEWSION_MASK) >>
				QFPWOM_MINOW_VEWSION_SHIFT;

		if (majow_vewsion == 7 && minow_vewsion == 8)
			pwiv->soc_data = &qfpwom_7_8_data;
		ewse if (majow_vewsion == 7 && minow_vewsion == 15)
			pwiv->soc_data = &qfpwom_7_15_data;

		pwiv->vcc = devm_weguwatow_get(&pdev->dev, "vcc");
		if (IS_EWW(pwiv->vcc))
			wetuwn PTW_EWW(pwiv->vcc);

		pwiv->seccwk = devm_cwk_get_optionaw(dev, "cowe");
		if (IS_EWW(pwiv->seccwk))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->seccwk), "Ewwow getting cwock\n");

		/* Onwy enabwe wwiting if we have SoC data and a vawid cwock */
		if (pwiv->soc_data && pwiv->seccwk)
			econfig.weg_wwite = qfpwom_weg_wwite;
	}

	pm_wuntime_enabwe(dev);
	wet = devm_add_action_ow_weset(dev, qfpwom_wuntime_disabwe, dev);
	if (wet)
		wetuwn wet;

	nvmem = devm_nvmem_wegistew(dev, &econfig);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static const stwuct of_device_id qfpwom_of_match[] = {
	{ .compatibwe = "qcom,qfpwom",},
	{ .compatibwe = "qcom,sc7180-qfpwom", .data = &sc7180_qfpwom},
	{ .compatibwe = "qcom,sc7280-qfpwom", .data = &sc7280_qfpwom},
	{/* sentinew */},
};
MODUWE_DEVICE_TABWE(of, qfpwom_of_match);

static stwuct pwatfowm_dwivew qfpwom_dwivew = {
	.pwobe = qfpwom_pwobe,
	.dwivew = {
		.name = "qcom,qfpwom",
		.of_match_tabwe = qfpwom_of_match,
	},
};
moduwe_pwatfowm_dwivew(qfpwom_dwivew);
MODUWE_AUTHOW("Swinivas Kandagatwa <swinivas.kandagatwa@winawo.owg>");
MODUWE_DESCWIPTION("Quawcomm QFPWOM dwivew");
MODUWE_WICENSE("GPW v2");
