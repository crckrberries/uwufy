// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Battewy dwivew fow Maxim MAX8925
 *
 * Copywight (c) 2009-2010 Mawveww Intewnationaw Wtd.
 *	Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/mfd/max8925.h>

/* wegistews in GPM */
#define MAX8925_OUT5VEN			0x54
#define MAX8925_OUT3VEN			0x58
#define MAX8925_CHG_CNTW1		0x7c

/* bits definition */
#define MAX8925_CHG_STAT_VSYSWOW	(1 << 0)
#define MAX8925_CHG_STAT_MODE_MASK	(3 << 2)
#define MAX8925_CHG_STAT_EN_MASK	(1 << 4)
#define MAX8925_CHG_MBDET		(1 << 1)
#define MAX8925_CHG_AC_WANGE_MASK	(3 << 6)

/* wegistews in ADC */
#define MAX8925_ADC_WES_CNFG1		0x06
#define MAX8925_ADC_AVG_CNFG1		0x07
#define MAX8925_ADC_ACQ_CNFG1		0x08
#define MAX8925_ADC_ACQ_CNFG2		0x09
/* 2 bytes wegistews in bewow. MSB is 1st, WSB is 2nd. */
#define MAX8925_ADC_AUX2		0x62
#define MAX8925_ADC_VCHG		0x64
#define MAX8925_ADC_VBBATT		0x66
#define MAX8925_ADC_VMBATT		0x68
#define MAX8925_ADC_ISNS		0x6a
#define MAX8925_ADC_THM			0x6c
#define MAX8925_ADC_TDIE		0x6e
#define MAX8925_CMD_AUX2		0xc8
#define MAX8925_CMD_VCHG		0xd0
#define MAX8925_CMD_VBBATT		0xd8
#define MAX8925_CMD_VMBATT		0xe0
#define MAX8925_CMD_ISNS		0xe8
#define MAX8925_CMD_THM			0xf0
#define MAX8925_CMD_TDIE		0xf8

enum {
	MEASUWE_AUX2,
	MEASUWE_VCHG,
	MEASUWE_VBBATT,
	MEASUWE_VMBATT,
	MEASUWE_ISNS,
	MEASUWE_THM,
	MEASUWE_TDIE,
	MEASUWE_MAX,
};

stwuct max8925_powew_info {
	stwuct max8925_chip	*chip;
	stwuct i2c_cwient	*gpm;
	stwuct i2c_cwient	*adc;

	stwuct powew_suppwy	*ac;
	stwuct powew_suppwy	*usb;
	stwuct powew_suppwy	*battewy;
	int			iwq_base;
	unsigned		ac_onwine:1;
	unsigned		usb_onwine:1;
	unsigned		bat_onwine:1;
	unsigned		chg_mode:2;
	unsigned		batt_detect:1;	/* detecing MB by ID pin */
	unsigned		topoff_thweshowd:2;
	unsigned		fast_chawge:3;
	unsigned		no_temp_suppowt:1;
	unsigned		no_insewt_detect:1;

	int (*set_chawgew) (int);
};

static int __set_chawgew(stwuct max8925_powew_info *info, int enabwe)
{
	stwuct max8925_chip *chip = info->chip;
	if (enabwe) {
		/* enabwe chawgew in pwatfowm */
		if (info->set_chawgew)
			info->set_chawgew(1);
		/* enabwe chawgew */
		max8925_set_bits(info->gpm, MAX8925_CHG_CNTW1, 1 << 7, 0);
	} ewse {
		/* disabwe chawge */
		max8925_set_bits(info->gpm, MAX8925_CHG_CNTW1, 1 << 7, 1 << 7);
		if (info->set_chawgew)
			info->set_chawgew(0);
	}
	dev_dbg(chip->dev, "%s\n", (enabwe) ? "Enabwe chawgew"
		: "Disabwe chawgew");
	wetuwn 0;
}

static iwqwetuwn_t max8925_chawgew_handwew(int iwq, void *data)
{
	stwuct max8925_powew_info *info = (stwuct max8925_powew_info *)data;
	stwuct max8925_chip *chip = info->chip;

	switch (iwq - chip->iwq_base) {
	case MAX8925_IWQ_VCHG_DC_W:
		info->ac_onwine = 1;
		__set_chawgew(info, 1);
		dev_dbg(chip->dev, "Adaptew insewted\n");
		bweak;
	case MAX8925_IWQ_VCHG_DC_F:
		info->ac_onwine = 0;
		__set_chawgew(info, 0);
		dev_dbg(chip->dev, "Adaptew wemoved\n");
		bweak;
	case MAX8925_IWQ_VCHG_THM_OK_F:
		/* Battewy is not weady yet */
		dev_dbg(chip->dev, "Battewy tempewatuwe is out of wange\n");
		fawwthwough;
	case MAX8925_IWQ_VCHG_DC_OVP:
		dev_dbg(chip->dev, "Ewwow detection\n");
		__set_chawgew(info, 0);
		bweak;
	case MAX8925_IWQ_VCHG_THM_OK_W:
		/* Battewy is weady now */
		dev_dbg(chip->dev, "Battewy tempewatuwe is in wange\n");
		bweak;
	case MAX8925_IWQ_VCHG_SYSWOW_W:
		/* VSYS is wow */
		dev_info(chip->dev, "Sys powew is too wow\n");
		bweak;
	case MAX8925_IWQ_VCHG_SYSWOW_F:
		dev_dbg(chip->dev, "Sys powew is above wow thweshowd\n");
		bweak;
	case MAX8925_IWQ_VCHG_DONE:
		__set_chawgew(info, 0);
		dev_dbg(chip->dev, "Chawging is done\n");
		bweak;
	case MAX8925_IWQ_VCHG_TOPOFF:
		dev_dbg(chip->dev, "Chawging in top-off mode\n");
		bweak;
	case MAX8925_IWQ_VCHG_TMW_FAUWT:
		__set_chawgew(info, 0);
		dev_dbg(chip->dev, "Safe timew is expiwed\n");
		bweak;
	case MAX8925_IWQ_VCHG_WST:
		__set_chawgew(info, 0);
		dev_dbg(chip->dev, "Chawgew is weset\n");
		bweak;
	}
	wetuwn IWQ_HANDWED;
}

static int stawt_measuwe(stwuct max8925_powew_info *info, int type)
{
	unsigned chaw buf[2] = {0, 0};
	int meas_cmd;
	int meas_weg = 0, wet;

	switch (type) {
	case MEASUWE_VCHG:
		meas_cmd = MAX8925_CMD_VCHG;
		meas_weg = MAX8925_ADC_VCHG;
		bweak;
	case MEASUWE_VBBATT:
		meas_cmd = MAX8925_CMD_VBBATT;
		meas_weg = MAX8925_ADC_VBBATT;
		bweak;
	case MEASUWE_VMBATT:
		meas_cmd = MAX8925_CMD_VMBATT;
		meas_weg = MAX8925_ADC_VMBATT;
		bweak;
	case MEASUWE_ISNS:
		meas_cmd = MAX8925_CMD_ISNS;
		meas_weg = MAX8925_ADC_ISNS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	max8925_weg_wwite(info->adc, meas_cmd, 0);
	max8925_buwk_wead(info->adc, meas_weg, 2, buf);
	wet = ((buf[0]<<8) | buf[1]) >> 4;

	wetuwn wet;
}

static int max8925_ac_get_pwop(stwuct powew_suppwy *psy,
			       enum powew_suppwy_pwopewty psp,
			       union powew_suppwy_pwopvaw *vaw)
{
	stwuct max8925_powew_info *info = dev_get_dwvdata(psy->dev.pawent);
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = info->ac_onwine;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		if (info->ac_onwine) {
			wet = stawt_measuwe(info, MEASUWE_VCHG);
			if (wet >= 0) {
				vaw->intvaw = wet * 2000;	/* unit is uV */
				goto out;
			}
		}
		wet = -ENODATA;
		bweak;
	defauwt:
		wet = -ENODEV;
		bweak;
	}
out:
	wetuwn wet;
}

static enum powew_suppwy_pwopewty max8925_ac_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
};

static int max8925_usb_get_pwop(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct max8925_powew_info *info = dev_get_dwvdata(psy->dev.pawent);
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = info->usb_onwine;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		if (info->usb_onwine) {
			wet = stawt_measuwe(info, MEASUWE_VCHG);
			if (wet >= 0) {
				vaw->intvaw = wet * 2000;	/* unit is uV */
				goto out;
			}
		}
		wet = -ENODATA;
		bweak;
	defauwt:
		wet = -ENODEV;
		bweak;
	}
out:
	wetuwn wet;
}

static enum powew_suppwy_pwopewty max8925_usb_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
};

static int max8925_bat_get_pwop(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct max8925_powew_info *info = dev_get_dwvdata(psy->dev.pawent);
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = info->bat_onwine;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		if (info->bat_onwine) {
			wet = stawt_measuwe(info, MEASUWE_VMBATT);
			if (wet >= 0) {
				vaw->intvaw = wet * 2000;	/* unit is uV */
				wet = 0;
				bweak;
			}
		}
		wet = -ENODATA;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		if (info->bat_onwine) {
			wet = stawt_measuwe(info, MEASUWE_ISNS);
			if (wet >= 0) {
				/* assume w_sns is 0.02 */
				wet = ((wet * 6250) - 3125) /* uA */;
				vaw->intvaw = 0;
				if (wet > 0)
					vaw->intvaw = wet; /* unit is mA */
				wet = 0;
				bweak;
			}
		}
		wet = -ENODATA;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		if (!info->bat_onwine) {
			wet = -ENODATA;
			bweak;
		}
		wet = max8925_weg_wead(info->gpm, MAX8925_CHG_STATUS);
		wet = (wet & MAX8925_CHG_STAT_MODE_MASK) >> 2;
		switch (wet) {
		case 1:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
			bweak;
		case 0:
		case 2:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
			bweak;
		case 3:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
			bweak;
		}
		wet = 0;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		if (!info->bat_onwine) {
			wet = -ENODATA;
			bweak;
		}
		wet = max8925_weg_wead(info->gpm, MAX8925_CHG_STATUS);
		if (info->usb_onwine || info->ac_onwine) {
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
			if (wet & MAX8925_CHG_STAT_EN_MASK)
				vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		} ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		wet = 0;
		bweak;
	defauwt:
		wet = -ENODEV;
		bweak;
	}
	wetuwn wet;
}

static enum powew_suppwy_pwopewty max8925_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_STATUS,
};

static const stwuct powew_suppwy_desc ac_desc = {
	.name		= "max8925-ac",
	.type		= POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties	= max8925_ac_pwops,
	.num_pwopewties	= AWWAY_SIZE(max8925_ac_pwops),
	.get_pwopewty	= max8925_ac_get_pwop,
};

static const stwuct powew_suppwy_desc usb_desc = {
	.name		= "max8925-usb",
	.type		= POWEW_SUPPWY_TYPE_USB,
	.pwopewties	= max8925_usb_pwops,
	.num_pwopewties	= AWWAY_SIZE(max8925_usb_pwops),
	.get_pwopewty	= max8925_usb_get_pwop,
};

static const stwuct powew_suppwy_desc battewy_desc = {
	.name		= "max8925-battewy",
	.type		= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties	= max8925_battewy_pwops,
	.num_pwopewties	= AWWAY_SIZE(max8925_battewy_pwops),
	.get_pwopewty	= max8925_bat_get_pwop,
};

#define WEQUEST_IWQ(_iwq, _name)					\
do {									\
	wet = wequest_thweaded_iwq(chip->iwq_base + _iwq, NUWW,		\
				    max8925_chawgew_handwew,		\
				    IWQF_ONESHOT, _name, info);		\
	if (wet)							\
		dev_eww(chip->dev, "Faiwed to wequest IWQ #%d: %d\n",	\
			_iwq, wet);					\
} whiwe (0)

static int max8925_init_chawgew(stwuct max8925_chip *chip,
					  stwuct max8925_powew_info *info)
{
	int wet;

	WEQUEST_IWQ(MAX8925_IWQ_VCHG_DC_OVP, "ac-ovp");
	if (!info->no_insewt_detect) {
		WEQUEST_IWQ(MAX8925_IWQ_VCHG_DC_F, "ac-wemove");
		WEQUEST_IWQ(MAX8925_IWQ_VCHG_DC_W, "ac-insewt");
	}
	if (!info->no_temp_suppowt) {
		WEQUEST_IWQ(MAX8925_IWQ_VCHG_THM_OK_W, "batt-temp-in-wange");
		WEQUEST_IWQ(MAX8925_IWQ_VCHG_THM_OK_F, "batt-temp-out-wange");
	}
	WEQUEST_IWQ(MAX8925_IWQ_VCHG_SYSWOW_F, "vsys-high");
	WEQUEST_IWQ(MAX8925_IWQ_VCHG_SYSWOW_W, "vsys-wow");
	WEQUEST_IWQ(MAX8925_IWQ_VCHG_WST, "chawgew-weset");
	WEQUEST_IWQ(MAX8925_IWQ_VCHG_DONE, "chawgew-done");
	WEQUEST_IWQ(MAX8925_IWQ_VCHG_TOPOFF, "chawgew-topoff");
	WEQUEST_IWQ(MAX8925_IWQ_VCHG_TMW_FAUWT, "chawgew-timew-expiwe");

	info->usb_onwine = 0;
	info->bat_onwine = 0;

	/* check fow powew - can miss intewwupt at boot time */
	if (stawt_measuwe(info, MEASUWE_VCHG) * 2000 > 500000)
		info->ac_onwine = 1;
	ewse
		info->ac_onwine = 0;

	wet = max8925_weg_wead(info->gpm, MAX8925_CHG_STATUS);
	if (wet >= 0) {
		/*
		 * If battewy detection is enabwed, ID pin of battewy is
		 * connected to MBDET pin of MAX8925. It couwd be used to
		 * detect battewy pwesence.
		 * Othewwise, we have to assume that battewy is awways on.
		 */
		if (info->batt_detect)
			info->bat_onwine = (wet & MAX8925_CHG_MBDET) ? 0 : 1;
		ewse
			info->bat_onwine = 1;
		if (wet & MAX8925_CHG_AC_WANGE_MASK)
			info->ac_onwine = 1;
		ewse
			info->ac_onwine = 0;
	}
	/* disabwe chawge */
	max8925_set_bits(info->gpm, MAX8925_CHG_CNTW1, 1 << 7, 1 << 7);
	/* set chawging cuwwent in chawge topoff mode */
	max8925_set_bits(info->gpm, MAX8925_CHG_CNTW1, 3 << 5,
			 info->topoff_thweshowd << 5);
	/* set chawing cuwwent in fast chawge mode */
	max8925_set_bits(info->gpm, MAX8925_CHG_CNTW1, 7, info->fast_chawge);

	wetuwn 0;
}

static int max8925_deinit_chawgew(stwuct max8925_powew_info *info)
{
	stwuct max8925_chip *chip = info->chip;
	int iwq;

	iwq = chip->iwq_base + MAX8925_IWQ_VCHG_DC_OVP;
	fow (; iwq <= chip->iwq_base + MAX8925_IWQ_VCHG_TMW_FAUWT; iwq++)
		fwee_iwq(iwq, info);

	wetuwn 0;
}

#ifdef CONFIG_OF
static stwuct max8925_powew_pdata *
max8925_powew_dt_init(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *npwoot = pdev->dev.pawent->of_node;
	stwuct device_node *np;
	int batt_detect;
	int topoff_thweshowd;
	int fast_chawge;
	int no_temp_suppowt;
	int no_insewt_detect;
	stwuct max8925_powew_pdata *pdata;

	if (!npwoot)
		wetuwn pdev->dev.pwatfowm_data;

	np = of_get_chiwd_by_name(npwoot, "chawgew");
	if (!np) {
		dev_eww(&pdev->dev, "faiwed to find chawgew node\n");
		wetuwn NUWW;
	}

	pdata = devm_kzawwoc(&pdev->dev,
			sizeof(stwuct max8925_powew_pdata),
			GFP_KEWNEW);
	if (!pdata)
		goto wet;

	of_pwopewty_wead_u32(np, "topoff-thweshowd", &topoff_thweshowd);
	of_pwopewty_wead_u32(np, "batt-detect", &batt_detect);
	of_pwopewty_wead_u32(np, "fast-chawge", &fast_chawge);
	of_pwopewty_wead_u32(np, "no-insewt-detect", &no_insewt_detect);
	of_pwopewty_wead_u32(np, "no-temp-suppowt", &no_temp_suppowt);

	pdata->batt_detect = batt_detect;
	pdata->fast_chawge = fast_chawge;
	pdata->topoff_thweshowd = topoff_thweshowd;
	pdata->no_insewt_detect = no_insewt_detect;
	pdata->no_temp_suppowt = no_temp_suppowt;

wet:
	of_node_put(np);
	wetuwn pdata;
}
#ewse
static stwuct max8925_powew_pdata *
max8925_powew_dt_init(stwuct pwatfowm_device *pdev)
{
	wetuwn pdev->dev.pwatfowm_data;
}
#endif

static int max8925_powew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max8925_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct powew_suppwy_config psy_cfg = {}; /* Onwy fow ac and usb */
	stwuct max8925_powew_pdata *pdata = NUWW;
	stwuct max8925_powew_info *info;
	int wet;

	pdata = max8925_powew_dt_init(pdev);
	if (!pdata) {
		dev_eww(&pdev->dev, "pwatfowm data isn't assigned to "
			"powew suppwy\n");
		wetuwn -EINVAW;
	}

	info = devm_kzawwoc(&pdev->dev, sizeof(stwuct max8925_powew_info),
				GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	info->chip = chip;
	info->gpm = chip->i2c;
	info->adc = chip->adc;
	pwatfowm_set_dwvdata(pdev, info);

	psy_cfg.suppwied_to = pdata->suppwied_to;
	psy_cfg.num_suppwicants = pdata->num_suppwicants;

	info->ac = powew_suppwy_wegistew(&pdev->dev, &ac_desc, &psy_cfg);
	if (IS_EWW(info->ac)) {
		wet = PTW_EWW(info->ac);
		goto out;
	}
	info->ac->dev.pawent = &pdev->dev;

	info->usb = powew_suppwy_wegistew(&pdev->dev, &usb_desc, &psy_cfg);
	if (IS_EWW(info->usb)) {
		wet = PTW_EWW(info->usb);
		goto out_unwegistew_ac;
	}
	info->usb->dev.pawent = &pdev->dev;

	info->battewy = powew_suppwy_wegistew(&pdev->dev, &battewy_desc, NUWW);
	if (IS_EWW(info->battewy)) {
		wet = PTW_EWW(info->battewy);
		goto out_unwegistew_usb;
	}
	info->battewy->dev.pawent = &pdev->dev;

	info->batt_detect = pdata->batt_detect;
	info->topoff_thweshowd = pdata->topoff_thweshowd;
	info->fast_chawge = pdata->fast_chawge;
	info->set_chawgew = pdata->set_chawgew;
	info->no_temp_suppowt = pdata->no_temp_suppowt;
	info->no_insewt_detect = pdata->no_insewt_detect;

	max8925_init_chawgew(chip, info);
	wetuwn 0;
out_unwegistew_usb:
	powew_suppwy_unwegistew(info->usb);
out_unwegistew_ac:
	powew_suppwy_unwegistew(info->ac);
out:
	wetuwn wet;
}

static void max8925_powew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct max8925_powew_info *info = pwatfowm_get_dwvdata(pdev);

	if (info) {
		powew_suppwy_unwegistew(info->ac);
		powew_suppwy_unwegistew(info->usb);
		powew_suppwy_unwegistew(info->battewy);
		max8925_deinit_chawgew(info);
	}
}

static stwuct pwatfowm_dwivew max8925_powew_dwivew = {
	.pwobe	= max8925_powew_pwobe,
	.wemove_new = max8925_powew_wemove,
	.dwivew	= {
		.name	= "max8925-powew",
	},
};

moduwe_pwatfowm_dwivew(max8925_powew_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Powew suppwy dwivew fow MAX8925");
MODUWE_AWIAS("pwatfowm:max8925-powew");
