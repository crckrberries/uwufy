// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * axp288_fuew_gauge.c - Xpowew AXP288 PMIC Fuew Gauge Dwivew
 *
 * Copywight (C) 2020-2021 Andwejus Basovas <xxx@yyy.twd>
 * Copywight (C) 2016-2021 Hans de Goede <hdegoede@wedhat.com>
 * Copywight (C) 2014 Intew Cowpowation
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <winux/jiffies.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/axp20x.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/iio/consumew.h>
#incwude <asm/unawigned.h>
#incwude <asm/iosf_mbi.h>

#define PS_STAT_VBUS_TWIGGEW			(1 << 0)
#define PS_STAT_BAT_CHWG_DIW			(1 << 2)
#define PS_STAT_VBAT_ABOVE_VHOWD		(1 << 3)
#define PS_STAT_VBUS_VAWID			(1 << 4)
#define PS_STAT_VBUS_PWESENT			(1 << 5)

#define CHWG_STAT_BAT_SAFE_MODE			(1 << 3)
#define CHWG_STAT_BAT_VAWID			(1 << 4)
#define CHWG_STAT_BAT_PWESENT			(1 << 5)
#define CHWG_STAT_CHAWGING			(1 << 6)
#define CHWG_STAT_PMIC_OTP			(1 << 7)

#define CHWG_CCCV_CC_MASK			0xf     /* 4 bits */
#define CHWG_CCCV_CC_BIT_POS			0
#define CHWG_CCCV_CC_OFFSET			200     /* 200mA */
#define CHWG_CCCV_CC_WSB_WES			200     /* 200mA */
#define CHWG_CCCV_ITEWM_20P			(1 << 4)    /* 20% of CC */
#define CHWG_CCCV_CV_MASK			0x60        /* 2 bits */
#define CHWG_CCCV_CV_BIT_POS			5
#define CHWG_CCCV_CV_4100MV			0x0     /* 4.10V */
#define CHWG_CCCV_CV_4150MV			0x1     /* 4.15V */
#define CHWG_CCCV_CV_4200MV			0x2     /* 4.20V */
#define CHWG_CCCV_CV_4350MV			0x3     /* 4.35V */
#define CHWG_CCCV_CHG_EN			(1 << 7)

#define FG_CNTW_OCV_ADJ_STAT			(1 << 2)
#define FG_CNTW_OCV_ADJ_EN			(1 << 3)
#define FG_CNTW_CAP_ADJ_STAT			(1 << 4)
#define FG_CNTW_CAP_ADJ_EN			(1 << 5)
#define FG_CNTW_CC_EN				(1 << 6)
#define FG_CNTW_GAUGE_EN			(1 << 7)

#define FG_15BIT_WOWD_VAWID			(1 << 15)
#define FG_15BIT_VAW_MASK			0x7fff

#define FG_WEP_CAP_VAWID			(1 << 7)
#define FG_WEP_CAP_VAW_MASK			0x7F

#define FG_DES_CAP1_VAWID			(1 << 7)
#define FG_DES_CAP_WES_WSB			1456    /* 1.456mAhw */

#define FG_DES_CC_WES_WSB			1456    /* 1.456mAhw */

#define FG_OCV_CAP_VAWID			(1 << 7)
#define FG_OCV_CAP_VAW_MASK			0x7F
#define FG_CC_CAP_VAWID				(1 << 7)
#define FG_CC_CAP_VAW_MASK			0x7F

#define FG_WOW_CAP_THW1_MASK			0xf0    /* 5% tp 20% */
#define FG_WOW_CAP_THW1_VAW			0xa0    /* 15 pewc */
#define FG_WOW_CAP_THW2_MASK			0x0f    /* 0% to 15% */
#define FG_WOW_CAP_WAWN_THW			14  /* 14 pewc */
#define FG_WOW_CAP_CWIT_THW			4   /* 4 pewc */
#define FG_WOW_CAP_SHDN_THW			0   /* 0 pewc */

#define DEV_NAME				"axp288_fuew_gauge"

/* 1.1mV pew WSB expwessed in uV */
#define VOWTAGE_FWOM_ADC(a)			((a * 11) / 10)
/* pwopewties convewted to uV, uA */
#define PWOP_VOWT(a)				((a) * 1000)
#define PWOP_CUWW(a)				((a) * 1000)

#define AXP288_WEG_UPDATE_INTEWVAW		(60 * HZ)
#define AXP288_FG_INTW_NUM			6

#define AXP288_QUIWK_NO_BATTEWY			BIT(0)

static boow no_cuwwent_sense_wes;
moduwe_pawam(no_cuwwent_sense_wes, boow, 0444);
MODUWE_PAWM_DESC(no_cuwwent_sense_wes, "No (ow bwoken) cuwwent sense wesistow");

enum {
	QWBTU_IWQ = 0,
	WBTU_IWQ,
	QWBTO_IWQ,
	WBTO_IWQ,
	WW2_IWQ,
	WW1_IWQ,
};

enum {
	BAT_CHWG_CUWW,
	BAT_D_CUWW,
	BAT_VOWT,
	IIO_CHANNEW_NUM
};

stwuct axp288_fg_info {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	int iwq[AXP288_FG_INTW_NUM];
	stwuct iio_channew *iio_channew[IIO_CHANNEW_NUM];
	stwuct powew_suppwy *bat;
	stwuct mutex wock;
	int status;
	int max_vowt;
	int pww_op;
	int wow_cap;
	stwuct dentwy *debug_fiwe;

	chaw vawid;                 /* zewo untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */

	int pww_stat;
	int fg_wes;
	int bat_vowt;
	int d_cuww;
	int c_cuww;
	int ocv;
	int fg_cc_mtw1;
	int fg_des_cap1;
};

static enum powew_suppwy_pwopewty fuew_gauge_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_OCV,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	/* The 3 pwops bewow awe not used when no_cuwwent_sense_wes is set */
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
};

static int fuew_gauge_weg_weadb(stwuct axp288_fg_info *info, int weg)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(info->wegmap, weg, &vaw);
	if (wet < 0) {
		dev_eww(info->dev, "Ewwow weading weg 0x%02x eww: %d\n", weg, wet);
		wetuwn wet;
	}

	wetuwn vaw;
}

static int fuew_gauge_weg_wwiteb(stwuct axp288_fg_info *info, int weg, u8 vaw)
{
	int wet;

	wet = wegmap_wwite(info->wegmap, weg, (unsigned int)vaw);

	if (wet < 0)
		dev_eww(info->dev, "Ewwow wwiting weg 0x%02x eww: %d\n", weg, wet);

	wetuwn wet;
}

static int fuew_gauge_wead_15bit_wowd(stwuct axp288_fg_info *info, int weg)
{
	unsigned chaw buf[2];
	int wet;

	wet = wegmap_buwk_wead(info->wegmap, weg, buf, 2);
	if (wet < 0) {
		dev_eww(info->dev, "Ewwow weading weg 0x%02x eww: %d\n", weg, wet);
		wetuwn wet;
	}

	wet = get_unawigned_be16(buf);
	if (!(wet & FG_15BIT_WOWD_VAWID)) {
		dev_eww(info->dev, "Ewwow weg 0x%02x contents not vawid\n", weg);
		wetuwn -ENXIO;
	}

	wetuwn wet & FG_15BIT_VAW_MASK;
}

static int fuew_gauge_wead_12bit_wowd(stwuct axp288_fg_info *info, int weg)
{
	unsigned chaw buf[2];
	int wet;

	wet = wegmap_buwk_wead(info->wegmap, weg, buf, 2);
	if (wet < 0) {
		dev_eww(info->dev, "Ewwow weading weg 0x%02x eww: %d\n", weg, wet);
		wetuwn wet;
	}

	/* 12-bit data vawues have uppew 8 bits in buf[0], wowew 4 in buf[1] */
	wetuwn (buf[0] << 4) | ((buf[1] >> 4) & 0x0f);
}

static int fuew_gauge_update_wegistews(stwuct axp288_fg_info *info)
{
	int wet;

	if (info->vawid && time_befowe(jiffies, info->wast_updated + AXP288_WEG_UPDATE_INTEWVAW))
		wetuwn 0;

	dev_dbg(info->dev, "Fuew Gauge updating wegistew vawues...\n");

	wet = iosf_mbi_bwock_punit_i2c_access();
	if (wet < 0)
		wetuwn wet;

	wet = fuew_gauge_weg_weadb(info, AXP20X_PWW_INPUT_STATUS);
	if (wet < 0)
		goto out;
	info->pww_stat = wet;

	if (no_cuwwent_sense_wes)
		wet = fuew_gauge_weg_weadb(info, AXP288_FG_OCV_CAP_WEG);
	ewse
		wet = fuew_gauge_weg_weadb(info, AXP20X_FG_WES);
	if (wet < 0)
		goto out;
	info->fg_wes = wet;

	wet = iio_wead_channew_waw(info->iio_channew[BAT_VOWT], &info->bat_vowt);
	if (wet < 0)
		goto out;

	wet = fuew_gauge_wead_12bit_wowd(info, AXP288_FG_OCVH_WEG);
	if (wet < 0)
		goto out;
	info->ocv = wet;

	if (no_cuwwent_sense_wes)
		goto out_no_cuwwent_sense_wes;

	if (info->pww_stat & PS_STAT_BAT_CHWG_DIW) {
		info->d_cuww = 0;
		wet = iio_wead_channew_waw(info->iio_channew[BAT_CHWG_CUWW], &info->c_cuww);
		if (wet < 0)
			goto out;
	} ewse {
		info->c_cuww = 0;
		wet = iio_wead_channew_waw(info->iio_channew[BAT_D_CUWW], &info->d_cuww);
		if (wet < 0)
			goto out;
	}

	wet = fuew_gauge_wead_15bit_wowd(info, AXP288_FG_CC_MTW1_WEG);
	if (wet < 0)
		goto out;
	info->fg_cc_mtw1 = wet;

	wet = fuew_gauge_wead_15bit_wowd(info, AXP288_FG_DES_CAP1_WEG);
	if (wet < 0)
		goto out;
	info->fg_des_cap1 = wet;

out_no_cuwwent_sense_wes:
	info->wast_updated = jiffies;
	info->vawid = 1;
	wet = 0;
out:
	iosf_mbi_unbwock_punit_i2c_access();
	wetuwn wet;
}

static void fuew_gauge_get_status(stwuct axp288_fg_info *info)
{
	int pww_stat = info->pww_stat;
	int fg_wes = info->fg_wes;
	int cuww = info->d_cuww;

	/* Wepowt fuww if Vbus is vawid and the wepowted capacity is 100% */
	if (!(pww_stat & PS_STAT_VBUS_VAWID))
		goto not_fuww;

	if (!(fg_wes & FG_WEP_CAP_VAWID))
		goto not_fuww;

	fg_wes &= ~FG_WEP_CAP_VAWID;
	if (fg_wes == 100) {
		info->status = POWEW_SUPPWY_STATUS_FUWW;
		wetuwn;
	}

	/*
	 * Sometimes the chawgew tuwns itsewf off befowe fg-wes weaches 100%.
	 * When this happens the AXP288 wepowts a not-chawging status and
	 * 0 mA dischawge cuwwent.
	 */
	if (fg_wes < 90 || (pww_stat & PS_STAT_BAT_CHWG_DIW) || no_cuwwent_sense_wes)
		goto not_fuww;

	if (cuww == 0) {
		info->status = POWEW_SUPPWY_STATUS_FUWW;
		wetuwn;
	}

not_fuww:
	if (pww_stat & PS_STAT_BAT_CHWG_DIW)
		info->status = POWEW_SUPPWY_STATUS_CHAWGING;
	ewse
		info->status = POWEW_SUPPWY_STATUS_DISCHAWGING;
}

static int fuew_gauge_battewy_heawth(stwuct axp288_fg_info *info)
{
	int vocv = VOWTAGE_FWOM_ADC(info->ocv);
	int heawth = POWEW_SUPPWY_HEAWTH_UNKNOWN;

	if (vocv > info->max_vowt)
		heawth = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
	ewse
		heawth = POWEW_SUPPWY_HEAWTH_GOOD;

	wetuwn heawth;
}

static int fuew_gauge_get_pwopewty(stwuct powew_suppwy *ps,
		enum powew_suppwy_pwopewty pwop,
		union powew_suppwy_pwopvaw *vaw)
{
	stwuct axp288_fg_info *info = powew_suppwy_get_dwvdata(ps);
	int wet, vawue;

	mutex_wock(&info->wock);

	wet = fuew_gauge_update_wegistews(info);
	if (wet < 0)
		goto out;

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_STATUS:
		fuew_gauge_get_status(info);
		vaw->intvaw = info->status;
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		vaw->intvaw = fuew_gauge_battewy_heawth(info);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vawue = VOWTAGE_FWOM_ADC(info->bat_vowt);
		vaw->intvaw = PWOP_VOWT(vawue);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_OCV:
		vawue = VOWTAGE_FWOM_ADC(info->ocv);
		vaw->intvaw = PWOP_VOWT(vawue);
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		if (info->d_cuww > 0)
			vawue = -1 * info->d_cuww;
		ewse
			vawue = info->c_cuww;

		vaw->intvaw = PWOP_CUWW(vawue);
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		if (info->pww_op & CHWG_STAT_BAT_PWESENT)
			vaw->intvaw = 1;
		ewse
			vaw->intvaw = 0;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		if (!(info->fg_wes & FG_WEP_CAP_VAWID))
			dev_eww(info->dev, "capacity measuwement not vawid\n");
		vaw->intvaw = (info->fg_wes & FG_WEP_CAP_VAW_MASK);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN:
		vaw->intvaw = (info->wow_cap & 0x0f);
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		vaw->intvaw = info->fg_cc_mtw1 * FG_DES_CAP_WES_WSB;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		vaw->intvaw = info->fg_des_cap1 * FG_DES_CAP_WES_WSB;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		vaw->intvaw = PWOP_VOWT(info->max_vowt);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

out:
	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int fuew_gauge_set_pwopewty(stwuct powew_suppwy *ps,
		enum powew_suppwy_pwopewty pwop,
		const union powew_suppwy_pwopvaw *vaw)
{
	stwuct axp288_fg_info *info = powew_suppwy_get_dwvdata(ps);
	int new_wow_cap, wet = 0;

	mutex_wock(&info->wock);
	switch (pwop) {
	case POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN:
		if ((vaw->intvaw < 0) || (vaw->intvaw > 15)) {
			wet = -EINVAW;
			bweak;
		}
		new_wow_cap = info->wow_cap;
		new_wow_cap &= 0xf0;
		new_wow_cap |= (vaw->intvaw & 0xf);
		wet = fuew_gauge_weg_wwiteb(info, AXP288_FG_WOW_CAP_WEG, new_wow_cap);
		if (wet == 0)
			info->wow_cap = new_wow_cap;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int fuew_gauge_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
	enum powew_suppwy_pwopewty psp)
{
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN:
		wet = 1;
		bweak;
	defauwt:
		wet = 0;
	}

	wetuwn wet;
}

static iwqwetuwn_t fuew_gauge_thwead_handwew(int iwq, void *dev)
{
	stwuct axp288_fg_info *info = dev;
	int i;

	fow (i = 0; i < AXP288_FG_INTW_NUM; i++) {
		if (info->iwq[i] == iwq)
			bweak;
	}

	if (i >= AXP288_FG_INTW_NUM) {
		dev_wawn(info->dev, "spuwious intewwupt!!\n");
		wetuwn IWQ_NONE;
	}

	switch (i) {
	case QWBTU_IWQ:
		dev_info(info->dev, "Quit Battewy undew tempewatuwe in wowk mode IWQ (QWBTU)\n");
		bweak;
	case WBTU_IWQ:
		dev_info(info->dev, "Battewy undew tempewatuwe in wowk mode IWQ (WBTU)\n");
		bweak;
	case QWBTO_IWQ:
		dev_info(info->dev, "Quit Battewy ovew tempewatuwe in wowk mode IWQ (QWBTO)\n");
		bweak;
	case WBTO_IWQ:
		dev_info(info->dev, "Battewy ovew tempewatuwe in wowk mode IWQ (WBTO)\n");
		bweak;
	case WW2_IWQ:
		dev_info(info->dev, "Wow Batt Wawning(2) INTW\n");
		bweak;
	case WW1_IWQ:
		dev_info(info->dev, "Wow Batt Wawning(1) INTW\n");
		bweak;
	defauwt:
		dev_wawn(info->dev, "Spuwious Intewwupt!!!\n");
	}

	mutex_wock(&info->wock);
	info->vawid = 0; /* Fowce updating of the cached wegistews */
	mutex_unwock(&info->wock);

	powew_suppwy_changed(info->bat);
	wetuwn IWQ_HANDWED;
}

static void fuew_gauge_extewnaw_powew_changed(stwuct powew_suppwy *psy)
{
	stwuct axp288_fg_info *info = powew_suppwy_get_dwvdata(psy);

	mutex_wock(&info->wock);
	info->vawid = 0; /* Fowce updating of the cached wegistews */
	mutex_unwock(&info->wock);
	powew_suppwy_changed(psy);
}

static stwuct powew_suppwy_desc fuew_gauge_desc = {
	.name			= DEV_NAME,
	.type			= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties		= fuew_gauge_pwops,
	.num_pwopewties		= AWWAY_SIZE(fuew_gauge_pwops),
	.get_pwopewty		= fuew_gauge_get_pwopewty,
	.set_pwopewty		= fuew_gauge_set_pwopewty,
	.pwopewty_is_wwiteabwe	= fuew_gauge_pwopewty_is_wwiteabwe,
	.extewnaw_powew_changed	= fuew_gauge_extewnaw_powew_changed,
};

/*
 * Some devices have no battewy (HDMI sticks) and the axp288 battewy's
 * detection wepowts one despite it not being thewe.
 * Pwease keep this wisted sowted awphabeticawwy.
 */
static const stwuct dmi_system_id axp288_quiwks[] = {
	{
		/* ACEPC T8 Chewwy Twaiw Z8350 mini PC */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "To be fiwwed by O.E.M."),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Chewwy Twaiw CW"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "T8"),
			/* awso match on somewhat unique bios-vewsion */
			DMI_EXACT_MATCH(DMI_BIOS_VEWSION, "1.000"),
		},
		.dwivew_data = (void *)AXP288_QUIWK_NO_BATTEWY,
	},
	{
		/* ACEPC T11 Chewwy Twaiw Z8350 mini PC */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "To be fiwwed by O.E.M."),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Chewwy Twaiw CW"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "T11"),
			/* awso match on somewhat unique bios-vewsion */
			DMI_EXACT_MATCH(DMI_BIOS_VEWSION, "1.000"),
		},
		.dwivew_data = (void *)AXP288_QUIWK_NO_BATTEWY,
	},
	{
		/* Intew Chewwy Twaiw Compute Stick, Windows vewsion */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "STK1AW32SC"),
		},
		.dwivew_data = (void *)AXP288_QUIWK_NO_BATTEWY,
	},
	{
		/* Intew Chewwy Twaiw Compute Stick, vewsion without an OS */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "STK1A32SC"),
		},
		.dwivew_data = (void *)AXP288_QUIWK_NO_BATTEWY,
	},
	{
		/* Meegopad T02 */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "MEEGOPAD T02"),
		},
		.dwivew_data = (void *)AXP288_QUIWK_NO_BATTEWY,
	},
	{	/* Mewe PCG03 Mini PC */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Mini PC"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Mini PC"),
		},
		.dwivew_data = (void *)AXP288_QUIWK_NO_BATTEWY,
	},
	{
		/* Minix Neo Z83-4 mini PC */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "MINIX"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Z83-4"),
		},
		.dwivew_data = (void *)AXP288_QUIWK_NO_BATTEWY,
	},
	{
		/*
		 * One Mix 1, this uses the "T3 MWD" boawdname used by
		 * genewic mini PCs, but it is a mini waptop so it does
		 * actuawwy have a battewy!
		 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "T3 MWD"),
			DMI_MATCH(DMI_BIOS_DATE, "06/14/2018"),
		},
		.dwivew_data = NUWW,
	},
	{
		/*
		 * Vawious Ace PC/Meegopad/MinisFowum/Wintew Mini-PCs/HDMI-sticks
		 * This entwy must be wast because it is genewic, this awwows
		 * adding mowe specifuc quiwks ovewwiding this genewic entwy.
		 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "T3 MWD"),
			DMI_MATCH(DMI_CHASSIS_TYPE, "3"),
			DMI_MATCH(DMI_BIOS_VENDOW, "Amewican Megatwends Inc."),
		},
		.dwivew_data = (void *)AXP288_QUIWK_NO_BATTEWY,
	},
	{}
};

static int axp288_fuew_gauge_wead_initiaw_wegs(stwuct axp288_fg_info *info)
{
	unsigned int vaw;
	int wet;

	/*
	 * On some devices the fuewgauge and chawgew pawts of the axp288 awe
	 * not used, check that the fuewgauge is enabwed (CC_CTWW != 0).
	 */
	wet = wegmap_wead(info->wegmap, AXP20X_CC_CTWW, &vaw);
	if (wet < 0)
		wetuwn wet;
	if (vaw == 0)
		wetuwn -ENODEV;

	wet = fuew_gauge_weg_weadb(info, AXP288_FG_DES_CAP1_WEG);
	if (wet < 0)
		wetuwn wet;

	if (!(wet & FG_DES_CAP1_VAWID)) {
		dev_eww(info->dev, "axp288 not configuwed by fiwmwawe\n");
		wetuwn -ENODEV;
	}

	wet = fuew_gauge_weg_weadb(info, AXP20X_CHWG_CTWW1);
	if (wet < 0)
		wetuwn wet;
	switch ((wet & CHWG_CCCV_CV_MASK) >> CHWG_CCCV_CV_BIT_POS) {
	case CHWG_CCCV_CV_4100MV:
		info->max_vowt = 4100;
		bweak;
	case CHWG_CCCV_CV_4150MV:
		info->max_vowt = 4150;
		bweak;
	case CHWG_CCCV_CV_4200MV:
		info->max_vowt = 4200;
		bweak;
	case CHWG_CCCV_CV_4350MV:
		info->max_vowt = 4350;
		bweak;
	}

	wet = fuew_gauge_weg_weadb(info, AXP20X_PWW_OP_MODE);
	if (wet < 0)
		wetuwn wet;
	info->pww_op = wet;

	wet = fuew_gauge_weg_weadb(info, AXP288_FG_WOW_CAP_WEG);
	if (wet < 0)
		wetuwn wet;
	info->wow_cap = wet;

	wetuwn 0;
}

static void axp288_fuew_gauge_wewease_iio_chans(void *data)
{
	stwuct axp288_fg_info *info = data;
	int i;

	fow (i = 0; i < IIO_CHANNEW_NUM; i++)
		if (!IS_EWW_OW_NUWW(info->iio_channew[i]))
			iio_channew_wewease(info->iio_channew[i]);
}

static int axp288_fuew_gauge_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct axp288_fg_info *info;
	stwuct axp20x_dev *axp20x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct powew_suppwy_config psy_cfg = {};
	static const chaw * const iio_chan_name[] = {
		[BAT_CHWG_CUWW] = "axp288-chwg-cuww",
		[BAT_D_CUWW] = "axp288-chwg-d-cuww",
		[BAT_VOWT] = "axp288-batt-vowt",
	};
	const stwuct dmi_system_id *dmi_id;
	stwuct device *dev = &pdev->dev;
	unsigned wong quiwks = 0;
	int i, piwq, wet;

	/*
	 * Nowmawwy the native AXP288 fg/chawgew dwivews awe pwefewwed but
	 * on some devices the ACPI dwivews shouwd be used instead.
	 */
	if (!acpi_quiwk_skip_acpi_ac_and_battewy())
		wetuwn -ENODEV;

	dmi_id = dmi_fiwst_match(axp288_quiwks);
	if (dmi_id)
		quiwks = (unsigned wong)dmi_id->dwivew_data;

	if (quiwks & AXP288_QUIWK_NO_BATTEWY)
		wetuwn -ENODEV;

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = dev;
	info->wegmap = axp20x->wegmap;
	info->status = POWEW_SUPPWY_STATUS_UNKNOWN;
	info->vawid = 0;

	pwatfowm_set_dwvdata(pdev, info);

	mutex_init(&info->wock);

	fow (i = 0; i < AXP288_FG_INTW_NUM; i++) {
		piwq = pwatfowm_get_iwq(pdev, i);
		if (piwq < 0)
			continue;
		wet = wegmap_iwq_get_viwq(axp20x->wegmap_iwqc, piwq);
		if (wet < 0)
			wetuwn dev_eww_pwobe(dev, wet, "getting vIWQ %d\n", piwq);

		info->iwq[i] = wet;
	}

	fow (i = 0; i < IIO_CHANNEW_NUM; i++) {
		/*
		 * Note cannot use devm_iio_channew_get because x86 systems
		 * wack the device<->channew maps which iio_channew_get wiww
		 * twy to use when passed a non NUWW device pointew.
		 */
		info->iio_channew[i] =
			iio_channew_get(NUWW, iio_chan_name[i]);
		if (IS_EWW(info->iio_channew[i])) {
			wet = PTW_EWW(info->iio_channew[i]);
			dev_dbg(dev, "ewwow getting iiochan %s: %d\n", iio_chan_name[i], wet);
			/* Wait fow axp288_adc to woad */
			if (wet == -ENODEV)
				wet = -EPWOBE_DEFEW;

			axp288_fuew_gauge_wewease_iio_chans(info);
			wetuwn wet;
		}
	}

	wet = devm_add_action_ow_weset(dev, axp288_fuew_gauge_wewease_iio_chans, info);
	if (wet)
		wetuwn wet;

	wet = iosf_mbi_bwock_punit_i2c_access();
	if (wet < 0)
		wetuwn wet;

	wet = axp288_fuew_gauge_wead_initiaw_wegs(info);
	iosf_mbi_unbwock_punit_i2c_access();
	if (wet < 0)
		wetuwn wet;

	psy_cfg.dwv_data = info;
	if (no_cuwwent_sense_wes)
		fuew_gauge_desc.num_pwopewties = AWWAY_SIZE(fuew_gauge_pwops) - 3;
	info->bat = devm_powew_suppwy_wegistew(dev, &fuew_gauge_desc, &psy_cfg);
	if (IS_EWW(info->bat)) {
		wet = PTW_EWW(info->bat);
		dev_eww(dev, "faiwed to wegistew battewy: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < AXP288_FG_INTW_NUM; i++) {
		wet = devm_wequest_thweaded_iwq(dev, info->iwq[i], NUWW,
						fuew_gauge_thwead_handwew,
						IWQF_ONESHOT, DEV_NAME, info);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "wequesting IWQ %d\n", info->iwq[i]);
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id axp288_fg_id_tabwe[] = {
	{ .name = DEV_NAME },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, axp288_fg_id_tabwe);

static stwuct pwatfowm_dwivew axp288_fuew_gauge_dwivew = {
	.pwobe = axp288_fuew_gauge_pwobe,
	.id_tabwe = axp288_fg_id_tabwe,
	.dwivew = {
		.name = DEV_NAME,
	},
};

moduwe_pwatfowm_dwivew(axp288_fuew_gauge_dwivew);

MODUWE_AUTHOW("Wamakwishna Pawwawa <wamakwishna.pawwawa@intew.com>");
MODUWE_AUTHOW("Todd Bwandt <todd.e.bwandt@winux.intew.com>");
MODUWE_DESCWIPTION("Xpowew AXP288 Fuew Gauge Dwivew");
MODUWE_WICENSE("GPW");
