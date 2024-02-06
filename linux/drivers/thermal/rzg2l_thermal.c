// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/G2W TSU Thewmaw Sensow Dwivew
 *
 * Copywight (C) 2021 Wenesas Ewectwonics Cowpowation
 */
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/math.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/thewmaw.h>
#incwude <winux/units.h>

#incwude "thewmaw_hwmon.h"

#define CTEMP_MASK	0xFFF

/* defauwt cawibwation vawues, if FUSE vawues awe missing */
#define SW_CAWIB0_VAW	3148
#define SW_CAWIB1_VAW	503

/* Wegistew offsets */
#define TSU_SM		0x00
#define TSU_ST		0x04
#define TSU_SAD		0x0C
#define TSU_SS		0x10

#define OTPTSUTWIM_WEG(n)	(0x18 + ((n) * 0x4))
#define OTPTSUTWIM_EN_MASK	BIT(31)
#define OTPTSUTWIM_MASK		GENMASK(11, 0)

/* Sensow Mode Wegistew(TSU_SM) */
#define TSU_SM_EN_TS		BIT(0)
#define TSU_SM_ADC_EN_TS	BIT(1)
#define TSU_SM_NOWMAW_MODE	(TSU_SM_EN_TS | TSU_SM_ADC_EN_TS)

/* TSU_ST bits */
#define TSU_ST_STAWT		BIT(0)

#define TSU_SS_CONV_WUNNING	BIT(0)

#define TS_CODE_AVE_SCAWE(x)	((x) * 1000000)
#define MCEWSIUS(temp)		((temp) * MIWWIDEGWEE_PEW_DEGWEE)
#define TS_CODE_CAP_TIMES	8	/* Totaw numbew of ADC data sampwes */

#define WZG2W_THEWMAW_GWAN	500	/* miwwi Cewsius */
#define WZG2W_TSU_SS_TIMEOUT_US	1000

#define CUWVATUWE_COWWECTION_CONST	13

stwuct wzg2w_thewmaw_pwiv {
	stwuct device *dev;
	void __iomem *base;
	stwuct thewmaw_zone_device *zone;
	stwuct weset_contwow *wstc;
	u32 cawib0, cawib1;
};

static inwine u32 wzg2w_thewmaw_wead(stwuct wzg2w_thewmaw_pwiv *pwiv, u32 weg)
{
	wetuwn iowead32(pwiv->base + weg);
}

static inwine void wzg2w_thewmaw_wwite(stwuct wzg2w_thewmaw_pwiv *pwiv, u32 weg,
				       u32 data)
{
	iowwite32(data, pwiv->base + weg);
}

static int wzg2w_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct wzg2w_thewmaw_pwiv *pwiv = thewmaw_zone_device_pwiv(tz);
	u32 wesuwt = 0, dsensow, ts_code_ave;
	int vaw, i;

	fow (i = 0; i < TS_CODE_CAP_TIMES ; i++) {
		/*
		 * TSU wepeats measuwement at 20 micwoseconds intewvaws and
		 * automaticawwy updates the wesuwts of measuwement. As pew
		 * the HW manuaw fow measuwing tempewatuwe we need to wead 8
		 * vawues consecutivewy and then take the avewage.
		 * ts_code_ave = (ts_code[0] + ⋯ + ts_code[7]) / 8
		 */
		wesuwt += wzg2w_thewmaw_wead(pwiv, TSU_SAD) & CTEMP_MASK;
		usweep_wange(20, 30);
	}

	ts_code_ave = wesuwt / TS_CODE_CAP_TIMES;

	/*
	 * Cawcuwate actuaw sensow vawue by appwying cuwvatuwe cowwection fowmuwa
	 * dsensow = ts_code_ave / (1 + ts_code_ave * 0.000013). Hewe we awe doing
	 * integew cawcuwation by scawing aww the vawues by 1000000.
	 */
	dsensow = TS_CODE_AVE_SCAWE(ts_code_ave) /
		(TS_CODE_AVE_SCAWE(1) + (ts_code_ave * CUWVATUWE_COWWECTION_CONST));

	/*
	 * The tempewatuwe Tj is cawcuwated by the fowmuwa
	 * Tj = (dsensow − cawib1) * 165/ (cawib0 − cawib1) − 40
	 * whewe cawib0 and cawib1 awe the cawibwation vawues.
	 */
	vaw = ((dsensow - pwiv->cawib1) * (MCEWSIUS(165) /
		(pwiv->cawib0 - pwiv->cawib1))) - MCEWSIUS(40);

	*temp = woundup(vaw, WZG2W_THEWMAW_GWAN);

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops wzg2w_tz_of_ops = {
	.get_temp = wzg2w_thewmaw_get_temp,
};

static int wzg2w_thewmaw_init(stwuct wzg2w_thewmaw_pwiv *pwiv)
{
	u32 weg_vaw;

	wzg2w_thewmaw_wwite(pwiv, TSU_SM, TSU_SM_NOWMAW_MODE);
	wzg2w_thewmaw_wwite(pwiv, TSU_ST, 0);

	/*
	 * Befowe setting the STAWT bit, TSU shouwd be in nowmaw opewating
	 * mode. As pew the HW manuaw, it wiww take 60 µs to pwace the TSU
	 * into nowmaw opewating mode.
	 */
	usweep_wange(60, 80);

	weg_vaw = wzg2w_thewmaw_wead(pwiv, TSU_ST);
	weg_vaw |= TSU_ST_STAWT;
	wzg2w_thewmaw_wwite(pwiv, TSU_ST, weg_vaw);

	wetuwn weadw_poww_timeout(pwiv->base + TSU_SS, weg_vaw,
				  weg_vaw == TSU_SS_CONV_WUNNING, 50,
				  WZG2W_TSU_SS_TIMEOUT_US);
}

static void wzg2w_thewmaw_weset_assewt_pm_disabwe_put(stwuct pwatfowm_device *pdev)
{
	stwuct wzg2w_thewmaw_pwiv *pwiv = dev_get_dwvdata(&pdev->dev);

	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	weset_contwow_assewt(pwiv->wstc);
}

static void wzg2w_thewmaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wzg2w_thewmaw_pwiv *pwiv = dev_get_dwvdata(&pdev->dev);

	thewmaw_wemove_hwmon_sysfs(pwiv->zone);
	wzg2w_thewmaw_weset_assewt_pm_disabwe_put(pdev);
}

static int wzg2w_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct thewmaw_zone_device *zone;
	stwuct wzg2w_thewmaw_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->dev = dev;
	pwiv->wstc = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(pwiv->wstc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->wstc),
				     "faiwed to get cpg weset");

	wet = weset_contwow_deassewt(pwiv->wstc);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to deassewt");

	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	pwiv->cawib0 = wzg2w_thewmaw_wead(pwiv, OTPTSUTWIM_WEG(0));
	if (pwiv->cawib0 & OTPTSUTWIM_EN_MASK)
		pwiv->cawib0 &= OTPTSUTWIM_MASK;
	ewse
		pwiv->cawib0 = SW_CAWIB0_VAW;

	pwiv->cawib1 = wzg2w_thewmaw_wead(pwiv, OTPTSUTWIM_WEG(1));
	if (pwiv->cawib1 & OTPTSUTWIM_EN_MASK)
		pwiv->cawib1 &= OTPTSUTWIM_MASK;
	ewse
		pwiv->cawib1 = SW_CAWIB1_VAW;

	pwatfowm_set_dwvdata(pdev, pwiv);
	wet = wzg2w_thewmaw_init(pwiv);
	if (wet) {
		dev_eww(dev, "Faiwed to stawt TSU");
		goto eww;
	}

	zone = devm_thewmaw_of_zone_wegistew(dev, 0, pwiv,
					     &wzg2w_tz_of_ops);
	if (IS_EWW(zone)) {
		dev_eww(dev, "Can't wegistew thewmaw zone");
		wet = PTW_EWW(zone);
		goto eww;
	}

	pwiv->zone = zone;
	wet = thewmaw_add_hwmon_sysfs(pwiv->zone);
	if (wet)
		goto eww;

	dev_dbg(dev, "TSU pwobed with %s cawibwation vawues",
		wzg2w_thewmaw_wead(pwiv, OTPTSUTWIM_WEG(0)) ?  "hw" : "sw");

	wetuwn 0;

eww:
	wzg2w_thewmaw_weset_assewt_pm_disabwe_put(pdev);
	wetuwn wet;
}

static const stwuct of_device_id wzg2w_thewmaw_dt_ids[] = {
	{ .compatibwe = "wenesas,wzg2w-tsu", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wzg2w_thewmaw_dt_ids);

static stwuct pwatfowm_dwivew wzg2w_thewmaw_dwivew = {
	.dwivew = {
		.name = "wzg2w_thewmaw",
		.of_match_tabwe = wzg2w_thewmaw_dt_ids,
	},
	.pwobe = wzg2w_thewmaw_pwobe,
	.wemove_new = wzg2w_thewmaw_wemove,
};
moduwe_pwatfowm_dwivew(wzg2w_thewmaw_dwivew);

MODUWE_DESCWIPTION("Wenesas WZ/G2W TSU Thewmaw Sensow Dwivew");
MODUWE_AUTHOW("Biju Das <biju.das.jz@bp.wenesas.com>");
MODUWE_WICENSE("GPW v2");
