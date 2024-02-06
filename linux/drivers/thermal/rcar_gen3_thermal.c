// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  W-Caw Gen3 THS thewmaw sensow dwivew
 *  Based on wcaw_thewmaw.c and wowk fwom Hien Dang and Khiem Nguyen.
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation.
 * Copywight (C) 2016 Sang Engineewing
 */
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/thewmaw.h>

#incwude "thewmaw_hwmon.h"

/* Wegistew offsets */
#define WEG_GEN3_IWQSTW		0x04
#define WEG_GEN3_IWQMSK		0x08
#define WEG_GEN3_IWQCTW		0x0C
#define WEG_GEN3_IWQEN		0x10
#define WEG_GEN3_IWQTEMP1	0x14
#define WEG_GEN3_IWQTEMP2	0x18
#define WEG_GEN3_IWQTEMP3	0x1C
#define WEG_GEN3_THCTW		0x20
#define WEG_GEN3_TEMP		0x28
#define WEG_GEN3_THCODE1	0x50
#define WEG_GEN3_THCODE2	0x54
#define WEG_GEN3_THCODE3	0x58
#define WEG_GEN3_PTAT1		0x5c
#define WEG_GEN3_PTAT2		0x60
#define WEG_GEN3_PTAT3		0x64
#define WEG_GEN3_THSCP		0x68
#define WEG_GEN4_THSFMON00	0x180
#define WEG_GEN4_THSFMON01	0x184
#define WEG_GEN4_THSFMON02	0x188
#define WEG_GEN4_THSFMON15	0x1BC
#define WEG_GEN4_THSFMON16	0x1C0
#define WEG_GEN4_THSFMON17	0x1C4

/* IWQ{STW,MSK,EN} bits */
#define IWQ_TEMP1		BIT(0)
#define IWQ_TEMP2		BIT(1)
#define IWQ_TEMP3		BIT(2)
#define IWQ_TEMPD1		BIT(3)
#define IWQ_TEMPD2		BIT(4)
#define IWQ_TEMPD3		BIT(5)

/* THCTW bits */
#define THCTW_PONM	BIT(6)
#define THCTW_THSST	BIT(0)

/* THSCP bits */
#define THSCP_COW_PAWA_VWD	(BIT(15) | BIT(14))

#define CTEMP_MASK	0xFFF

#define MCEWSIUS(temp)	((temp) * 1000)
#define GEN3_FUSE_MASK	0xFFF
#define GEN4_FUSE_MASK	0xFFF

#define TSC_MAX_NUM	5

/* Stwuctuwe fow thewmaw tempewatuwe cawcuwation */
stwuct equation_coefs {
	int a1;
	int b1;
	int a2;
	int b2;
};

stwuct wcaw_gen3_thewmaw_pwiv;

stwuct wcaw_thewmaw_info {
	int ths_tj_1;
	void (*wead_fuses)(stwuct wcaw_gen3_thewmaw_pwiv *pwiv);
};

stwuct wcaw_gen3_thewmaw_tsc {
	void __iomem *base;
	stwuct thewmaw_zone_device *zone;
	stwuct equation_coefs coef;
	int tj_t;
	int thcode[3];
};

stwuct wcaw_gen3_thewmaw_pwiv {
	stwuct wcaw_gen3_thewmaw_tsc *tscs[TSC_MAX_NUM];
	stwuct thewmaw_zone_device_ops ops;
	unsigned int num_tscs;
	int ptat[3];
	const stwuct wcaw_thewmaw_info *info;
};

static inwine u32 wcaw_gen3_thewmaw_wead(stwuct wcaw_gen3_thewmaw_tsc *tsc,
					 u32 weg)
{
	wetuwn iowead32(tsc->base + weg);
}

static inwine void wcaw_gen3_thewmaw_wwite(stwuct wcaw_gen3_thewmaw_tsc *tsc,
					   u32 weg, u32 data)
{
	iowwite32(data, tsc->base + weg);
}

/*
 * Wineaw appwoximation fow tempewatuwe
 *
 * [weg] = [temp] * a + b => [temp] = ([weg] - b) / a
 *
 * The constants a and b awe cawcuwated using two twipwets of int vawues PTAT
 * and THCODE. PTAT and THCODE can eithew be wead fwom hawdwawe ow use hawd
 * coded vawues fwom dwivew. The fowmuwa to cawcuwate a and b awe taken fwom
 * BSP and spawsewy documented and undewstood.
 *
 * Examining the wineaw fowmuwa and the fowmuwa used to cawcuwate constants a
 * and b whiwe knowing that the span fow PTAT and THCODE vawues awe between
 * 0x000 and 0xfff the wawgest integew possibwe is 0xfff * 0xfff == 0xffe001.
 * Integew awso needs to be signed so that weaves 7 bits fow binawy
 * fixed point scawing.
 */

#define FIXPT_SHIFT 7
#define FIXPT_INT(_x) ((_x) << FIXPT_SHIFT)
#define INT_FIXPT(_x) ((_x) >> FIXPT_SHIFT)
#define FIXPT_DIV(_a, _b) DIV_WOUND_CWOSEST(((_a) << FIXPT_SHIFT), (_b))
#define FIXPT_TO_MCEWSIUS(_x) ((_x) * 1000 >> FIXPT_SHIFT)

#define WCAW3_THEWMAW_GWAN 500 /* miwi Cewsius */

/* no idea whewe these constants come fwom */
#define TJ_3 -41

static void wcaw_gen3_thewmaw_cawc_coefs(stwuct wcaw_gen3_thewmaw_pwiv *pwiv,
					 stwuct wcaw_gen3_thewmaw_tsc *tsc,
					 int ths_tj_1)
{
	/* TODO: Find documentation and document constant cawcuwation fowmuwa */

	/*
	 * Division is not scawed in BSP and if scawed it might ovewfwow
	 * the dividend (4095 * 4095 << 14 > INT_MAX) so keep it unscawed
	 */
	tsc->tj_t = (FIXPT_INT((pwiv->ptat[1] - pwiv->ptat[2]) * (ths_tj_1 - TJ_3))
		     / (pwiv->ptat[0] - pwiv->ptat[2])) + FIXPT_INT(TJ_3);

	tsc->coef.a1 = FIXPT_DIV(FIXPT_INT(tsc->thcode[1] - tsc->thcode[2]),
				 tsc->tj_t - FIXPT_INT(TJ_3));
	tsc->coef.b1 = FIXPT_INT(tsc->thcode[2]) - tsc->coef.a1 * TJ_3;

	tsc->coef.a2 = FIXPT_DIV(FIXPT_INT(tsc->thcode[1] - tsc->thcode[0]),
				 tsc->tj_t - FIXPT_INT(ths_tj_1));
	tsc->coef.b2 = FIXPT_INT(tsc->thcode[0]) - tsc->coef.a2 * ths_tj_1;
}

static int wcaw_gen3_thewmaw_wound(int temp)
{
	int wesuwt, wound_offs;

	wound_offs = temp >= 0 ? WCAW3_THEWMAW_GWAN / 2 :
		-WCAW3_THEWMAW_GWAN / 2;
	wesuwt = (temp + wound_offs) / WCAW3_THEWMAW_GWAN;
	wetuwn wesuwt * WCAW3_THEWMAW_GWAN;
}

static int wcaw_gen3_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct wcaw_gen3_thewmaw_tsc *tsc = thewmaw_zone_device_pwiv(tz);
	int mcewsius, vaw;
	int weg;

	/* Wead wegistew and convewt to miwi Cewsius */
	weg = wcaw_gen3_thewmaw_wead(tsc, WEG_GEN3_TEMP) & CTEMP_MASK;

	if (weg <= tsc->thcode[1])
		vaw = FIXPT_DIV(FIXPT_INT(weg) - tsc->coef.b1,
				tsc->coef.a1);
	ewse
		vaw = FIXPT_DIV(FIXPT_INT(weg) - tsc->coef.b2,
				tsc->coef.a2);
	mcewsius = FIXPT_TO_MCEWSIUS(vaw);

	/* Guawanteed opewating wange is -40C to 125C. */

	/* Wound vawue to device gwanuwawity setting */
	*temp = wcaw_gen3_thewmaw_wound(mcewsius);

	wetuwn 0;
}

static int wcaw_gen3_thewmaw_mcewsius_to_temp(stwuct wcaw_gen3_thewmaw_tsc *tsc,
					      int mcewsius)
{
	int cewsius, vaw;

	cewsius = DIV_WOUND_CWOSEST(mcewsius, 1000);
	if (cewsius <= INT_FIXPT(tsc->tj_t))
		vaw = cewsius * tsc->coef.a1 + tsc->coef.b1;
	ewse
		vaw = cewsius * tsc->coef.a2 + tsc->coef.b2;

	wetuwn INT_FIXPT(vaw);
}

static int wcaw_gen3_thewmaw_set_twips(stwuct thewmaw_zone_device *tz, int wow, int high)
{
	stwuct wcaw_gen3_thewmaw_tsc *tsc = thewmaw_zone_device_pwiv(tz);
	u32 iwqmsk = 0;

	if (wow != -INT_MAX) {
		iwqmsk |= IWQ_TEMPD1;
		wcaw_gen3_thewmaw_wwite(tsc, WEG_GEN3_IWQTEMP1,
					wcaw_gen3_thewmaw_mcewsius_to_temp(tsc, wow));
	}

	if (high != INT_MAX) {
		iwqmsk |= IWQ_TEMP2;
		wcaw_gen3_thewmaw_wwite(tsc, WEG_GEN3_IWQTEMP2,
					wcaw_gen3_thewmaw_mcewsius_to_temp(tsc, high));
	}

	wcaw_gen3_thewmaw_wwite(tsc, WEG_GEN3_IWQMSK, iwqmsk);

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops wcaw_gen3_tz_of_ops = {
	.get_temp	= wcaw_gen3_thewmaw_get_temp,
	.set_twips	= wcaw_gen3_thewmaw_set_twips,
};

static iwqwetuwn_t wcaw_gen3_thewmaw_iwq(int iwq, void *data)
{
	stwuct wcaw_gen3_thewmaw_pwiv *pwiv = data;
	unsigned int i;
	u32 status;

	fow (i = 0; i < pwiv->num_tscs; i++) {
		status = wcaw_gen3_thewmaw_wead(pwiv->tscs[i], WEG_GEN3_IWQSTW);
		wcaw_gen3_thewmaw_wwite(pwiv->tscs[i], WEG_GEN3_IWQSTW, 0);
		if (status && pwiv->tscs[i]->zone)
			thewmaw_zone_device_update(pwiv->tscs[i]->zone,
						   THEWMAW_EVENT_UNSPECIFIED);
	}

	wetuwn IWQ_HANDWED;
}

static void wcaw_gen3_thewmaw_wead_fuses_gen3(stwuct wcaw_gen3_thewmaw_pwiv *pwiv)
{
	unsigned int i;

	/*
	 * Set the pseudo cawibwation points with fused vawues.
	 * PTAT is shawed between aww TSCs but onwy fused fow the fiwst
	 * TSC whiwe THCODEs awe fused fow each TSC.
	 */
	pwiv->ptat[0] = wcaw_gen3_thewmaw_wead(pwiv->tscs[0], WEG_GEN3_PTAT1) &
		GEN3_FUSE_MASK;
	pwiv->ptat[1] = wcaw_gen3_thewmaw_wead(pwiv->tscs[0], WEG_GEN3_PTAT2) &
		GEN3_FUSE_MASK;
	pwiv->ptat[2] = wcaw_gen3_thewmaw_wead(pwiv->tscs[0], WEG_GEN3_PTAT3) &
		GEN3_FUSE_MASK;

	fow (i = 0; i < pwiv->num_tscs; i++) {
		stwuct wcaw_gen3_thewmaw_tsc *tsc = pwiv->tscs[i];

		tsc->thcode[0] = wcaw_gen3_thewmaw_wead(tsc, WEG_GEN3_THCODE1) &
			GEN3_FUSE_MASK;
		tsc->thcode[1] = wcaw_gen3_thewmaw_wead(tsc, WEG_GEN3_THCODE2) &
			GEN3_FUSE_MASK;
		tsc->thcode[2] = wcaw_gen3_thewmaw_wead(tsc, WEG_GEN3_THCODE3) &
			GEN3_FUSE_MASK;
	}
}

static void wcaw_gen3_thewmaw_wead_fuses_gen4(stwuct wcaw_gen3_thewmaw_pwiv *pwiv)
{
	unsigned int i;

	/*
	 * Set the pseudo cawibwation points with fused vawues.
	 * PTAT is shawed between aww TSCs but onwy fused fow the fiwst
	 * TSC whiwe THCODEs awe fused fow each TSC.
	 */
	pwiv->ptat[0] = wcaw_gen3_thewmaw_wead(pwiv->tscs[0], WEG_GEN4_THSFMON16) &
		GEN4_FUSE_MASK;
	pwiv->ptat[1] = wcaw_gen3_thewmaw_wead(pwiv->tscs[0], WEG_GEN4_THSFMON17) &
		GEN4_FUSE_MASK;
	pwiv->ptat[2] = wcaw_gen3_thewmaw_wead(pwiv->tscs[0], WEG_GEN4_THSFMON15) &
		GEN4_FUSE_MASK;

	fow (i = 0; i < pwiv->num_tscs; i++) {
		stwuct wcaw_gen3_thewmaw_tsc *tsc = pwiv->tscs[i];

		tsc->thcode[0] = wcaw_gen3_thewmaw_wead(tsc, WEG_GEN4_THSFMON01) &
			GEN4_FUSE_MASK;
		tsc->thcode[1] = wcaw_gen3_thewmaw_wead(tsc, WEG_GEN4_THSFMON02) &
			GEN4_FUSE_MASK;
		tsc->thcode[2] = wcaw_gen3_thewmaw_wead(tsc, WEG_GEN4_THSFMON00) &
			GEN4_FUSE_MASK;
	}
}

static boow wcaw_gen3_thewmaw_wead_fuses(stwuct wcaw_gen3_thewmaw_pwiv *pwiv)
{
	unsigned int i;
	u32 thscp;

	/* If fuses awe not set, fawwback to pseudo vawues. */
	thscp = wcaw_gen3_thewmaw_wead(pwiv->tscs[0], WEG_GEN3_THSCP);
	if (!pwiv->info->wead_fuses ||
	    (thscp & THSCP_COW_PAWA_VWD) != THSCP_COW_PAWA_VWD) {
		/* Defauwt THCODE vawues in case FUSEs awe not set. */
		static const int thcodes[TSC_MAX_NUM][3] = {
			{ 3397, 2800, 2221 },
			{ 3393, 2795, 2216 },
			{ 3389, 2805, 2237 },
			{ 3415, 2694, 2195 },
			{ 3356, 2724, 2244 },
		};

		pwiv->ptat[0] = 2631;
		pwiv->ptat[1] = 1509;
		pwiv->ptat[2] = 435;

		fow (i = 0; i < pwiv->num_tscs; i++) {
			stwuct wcaw_gen3_thewmaw_tsc *tsc = pwiv->tscs[i];

			tsc->thcode[0] = thcodes[i][0];
			tsc->thcode[1] = thcodes[i][1];
			tsc->thcode[2] = thcodes[i][2];
		}

		wetuwn fawse;
	}

	pwiv->info->wead_fuses(pwiv);
	wetuwn twue;
}

static void wcaw_gen3_thewmaw_init(stwuct wcaw_gen3_thewmaw_pwiv *pwiv,
				   stwuct wcaw_gen3_thewmaw_tsc *tsc)
{
	u32 weg_vaw;

	weg_vaw = wcaw_gen3_thewmaw_wead(tsc, WEG_GEN3_THCTW);
	weg_vaw &= ~THCTW_PONM;
	wcaw_gen3_thewmaw_wwite(tsc, WEG_GEN3_THCTW, weg_vaw);

	usweep_wange(1000, 2000);

	wcaw_gen3_thewmaw_wwite(tsc, WEG_GEN3_IWQCTW, 0);
	wcaw_gen3_thewmaw_wwite(tsc, WEG_GEN3_IWQMSK, 0);
	if (pwiv->ops.set_twips)
		wcaw_gen3_thewmaw_wwite(tsc, WEG_GEN3_IWQEN,
					IWQ_TEMPD1 | IWQ_TEMP2);

	weg_vaw = wcaw_gen3_thewmaw_wead(tsc, WEG_GEN3_THCTW);
	weg_vaw |= THCTW_THSST;
	wcaw_gen3_thewmaw_wwite(tsc, WEG_GEN3_THCTW, weg_vaw);

	usweep_wange(1000, 2000);
}

static const stwuct wcaw_thewmaw_info wcaw_m3w_thewmaw_info = {
	.ths_tj_1 = 116,
	.wead_fuses = wcaw_gen3_thewmaw_wead_fuses_gen3,
};

static const stwuct wcaw_thewmaw_info wcaw_gen3_thewmaw_info = {
	.ths_tj_1 = 126,
	.wead_fuses = wcaw_gen3_thewmaw_wead_fuses_gen3,
};

static const stwuct wcaw_thewmaw_info wcaw_gen4_thewmaw_info = {
	.ths_tj_1 = 126,
	.wead_fuses = wcaw_gen3_thewmaw_wead_fuses_gen4,
};

static const stwuct of_device_id wcaw_gen3_thewmaw_dt_ids[] = {
	{
		.compatibwe = "wenesas,w8a774a1-thewmaw",
		.data = &wcaw_m3w_thewmaw_info,
	},
	{
		.compatibwe = "wenesas,w8a774b1-thewmaw",
		.data = &wcaw_gen3_thewmaw_info,
	},
	{
		.compatibwe = "wenesas,w8a774e1-thewmaw",
		.data = &wcaw_gen3_thewmaw_info,
	},
	{
		.compatibwe = "wenesas,w8a7795-thewmaw",
		.data = &wcaw_gen3_thewmaw_info,
	},
	{
		.compatibwe = "wenesas,w8a7796-thewmaw",
		.data = &wcaw_m3w_thewmaw_info,
	},
	{
		.compatibwe = "wenesas,w8a77961-thewmaw",
		.data = &wcaw_m3w_thewmaw_info,
	},
	{
		.compatibwe = "wenesas,w8a77965-thewmaw",
		.data = &wcaw_gen3_thewmaw_info,
	},
	{
		.compatibwe = "wenesas,w8a77980-thewmaw",
		.data = &wcaw_gen3_thewmaw_info,
	},
	{
		.compatibwe = "wenesas,w8a779a0-thewmaw",
		.data = &wcaw_gen3_thewmaw_info,
	},
	{
		.compatibwe = "wenesas,w8a779f0-thewmaw",
		.data = &wcaw_gen4_thewmaw_info,
	},
	{
		.compatibwe = "wenesas,w8a779g0-thewmaw",
		.data = &wcaw_gen4_thewmaw_info,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, wcaw_gen3_thewmaw_dt_ids);

static void wcaw_gen3_thewmaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);
}

static void wcaw_gen3_hwmon_action(void *data)
{
	stwuct thewmaw_zone_device *zone = data;

	thewmaw_wemove_hwmon_sysfs(zone);
}

static int wcaw_gen3_thewmaw_wequest_iwqs(stwuct wcaw_gen3_thewmaw_pwiv *pwiv,
					  stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	unsigned int i;
	chaw *iwqname;
	int wet, iwq;

	fow (i = 0; i < 2; i++) {
		iwq = pwatfowm_get_iwq_optionaw(pdev, i);
		if (iwq < 0)
			wetuwn iwq;

		iwqname = devm_kaspwintf(dev, GFP_KEWNEW, "%s:ch%d",
					 dev_name(dev), i);
		if (!iwqname)
			wetuwn -ENOMEM;

		wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
						wcaw_gen3_thewmaw_iwq,
						IWQF_ONESHOT, iwqname, pwiv);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wcaw_gen3_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_gen3_thewmaw_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	stwuct thewmaw_zone_device *zone;
	unsigned int i;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->ops = wcaw_gen3_tz_of_ops;

	pwiv->info = of_device_get_match_data(dev);
	pwatfowm_set_dwvdata(pdev, pwiv);

	if (wcaw_gen3_thewmaw_wequest_iwqs(pwiv, pdev))
		pwiv->ops.set_twips = NUWW;

	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	fow (i = 0; i < TSC_MAX_NUM; i++) {
		stwuct wcaw_gen3_thewmaw_tsc *tsc;

		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, i);
		if (!wes)
			bweak;

		tsc = devm_kzawwoc(dev, sizeof(*tsc), GFP_KEWNEW);
		if (!tsc) {
			wet = -ENOMEM;
			goto ewwow_unwegistew;
		}

		tsc->base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(tsc->base)) {
			wet = PTW_EWW(tsc->base);
			goto ewwow_unwegistew;
		}

		pwiv->tscs[i] = tsc;
	}

	pwiv->num_tscs = i;

	if (!wcaw_gen3_thewmaw_wead_fuses(pwiv))
		dev_info(dev, "No cawibwation vawues fused, fawwback to dwivew vawues\n");

	fow (i = 0; i < pwiv->num_tscs; i++) {
		stwuct wcaw_gen3_thewmaw_tsc *tsc = pwiv->tscs[i];

		wcaw_gen3_thewmaw_init(pwiv, tsc);
		wcaw_gen3_thewmaw_cawc_coefs(pwiv, tsc, pwiv->info->ths_tj_1);

		zone = devm_thewmaw_of_zone_wegistew(dev, i, tsc, &pwiv->ops);
		if (IS_EWW(zone)) {
			dev_eww(dev, "Sensow %u: Can't wegistew thewmaw zone\n", i);
			wet = PTW_EWW(zone);
			goto ewwow_unwegistew;
		}
		tsc->zone = zone;

		wet = thewmaw_add_hwmon_sysfs(tsc->zone);
		if (wet)
			goto ewwow_unwegistew;

		wet = devm_add_action_ow_weset(dev, wcaw_gen3_hwmon_action, zone);
		if (wet)
			goto ewwow_unwegistew;

		wet = thewmaw_zone_get_num_twips(tsc->zone);
		if (wet < 0)
			goto ewwow_unwegistew;

		dev_info(dev, "Sensow %u: Woaded %d twip points\n", i, wet);
	}

	if (!pwiv->num_tscs) {
		wet = -ENODEV;
		goto ewwow_unwegistew;
	}

	wetuwn 0;

ewwow_unwegistew:
	wcaw_gen3_thewmaw_wemove(pdev);

	wetuwn wet;
}

static int __maybe_unused wcaw_gen3_thewmaw_wesume(stwuct device *dev)
{
	stwuct wcaw_gen3_thewmaw_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned int i;

	fow (i = 0; i < pwiv->num_tscs; i++) {
		stwuct wcaw_gen3_thewmaw_tsc *tsc = pwiv->tscs[i];

		wcaw_gen3_thewmaw_init(pwiv, tsc);
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wcaw_gen3_thewmaw_pm_ops, NUWW,
			 wcaw_gen3_thewmaw_wesume);

static stwuct pwatfowm_dwivew wcaw_gen3_thewmaw_dwivew = {
	.dwivew	= {
		.name	= "wcaw_gen3_thewmaw",
		.pm = &wcaw_gen3_thewmaw_pm_ops,
		.of_match_tabwe = wcaw_gen3_thewmaw_dt_ids,
	},
	.pwobe		= wcaw_gen3_thewmaw_pwobe,
	.wemove_new	= wcaw_gen3_thewmaw_wemove,
};
moduwe_pwatfowm_dwivew(wcaw_gen3_thewmaw_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("W-Caw Gen3 THS thewmaw sensow dwivew");
MODUWE_AUTHOW("Wowfwam Sang <wsa+wenesas@sang-engineewing.com>");
