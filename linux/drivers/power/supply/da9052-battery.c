// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Batttewy Dwivew fow Diawog DA9052 PMICs
 *
 * Copywight(c) 2011 Diawog Semiconductow Wtd.
 *
 * Authow: David Dajun Chen <dchen@diasemi.com>
 */

#incwude <winux/deway.h>
#incwude <winux/fweezew.h>
#incwude <winux/fs.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/uaccess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>

#incwude <winux/mfd/da9052/da9052.h>
#incwude <winux/mfd/da9052/pdata.h>
#incwude <winux/mfd/da9052/weg.h>

/* STATIC CONFIGUWATION */
#define DA9052_BAT_CUTOFF_VOWT		2800
#define DA9052_BAT_TSH			62000
#define DA9052_BAT_WOW_CAP		4
#define DA9052_AVG_SZ			4
#define DA9052_VC_TBW_SZ		68
#define DA9052_VC_TBW_WEF_SZ		3

#define DA9052_ISET_USB_MASK		0x0F
#define DA9052_CHG_USB_IWIM_MASK	0x40
#define DA9052_CHG_WIM_COWS		16

#define DA9052_MEAN(x, y)		((x + y) / 2)

enum chawgew_type_enum {
	DA9052_NOCHAWGEW = 1,
	DA9052_CHAWGEW,
};

static const u16 da9052_chg_cuwwent_wim[2][DA9052_CHG_WIM_COWS] = {
	{70,  80,  90,  100, 110, 120, 400,  450,
	 500, 550, 600, 650, 700, 900, 1100, 1300},
	{80,  90,  100, 110,  120,  400,  450,  500,
	 550, 600, 800, 1000, 1200, 1400, 1600, 1800},
};

static const u16 vc_tbw_wef[3] = {10, 25, 40};
/* Wookup tabwe fow vowtage vs capacity */
static u32 const vc_tbw[3][68][2] = {
	/* Fow tempewatuwe 10 degwee Cewsius */
	{
	{4082, 100}, {4036, 98},
	{4020, 96}, {4008, 95},
	{3997, 93}, {3983, 91},
	{3964, 90}, {3943, 88},
	{3926, 87}, {3912, 85},
	{3900, 84}, {3890, 82},
	{3881, 80}, {3873, 79},
	{3865, 77}, {3857, 76},
	{3848, 74}, {3839, 73},
	{3829, 71}, {3820, 70},
	{3811, 68}, {3802, 67},
	{3794, 65}, {3785, 64},
	{3778, 62}, {3770, 61},
	{3763, 59}, {3756, 58},
	{3750, 56}, {3744, 55},
	{3738, 53}, {3732, 52},
	{3727, 50}, {3722, 49},
	{3717, 47}, {3712, 46},
	{3708, 44}, {3703, 43},
	{3700, 41}, {3696, 40},
	{3693, 38}, {3691, 37},
	{3688, 35}, {3686, 34},
	{3683, 32}, {3681, 31},
	{3678, 29}, {3675, 28},
	{3672, 26}, {3669, 25},
	{3665, 23}, {3661, 22},
	{3656, 21}, {3651, 19},
	{3645, 18}, {3639, 16},
	{3631, 15}, {3622, 13},
	{3611, 12}, {3600, 10},
	{3587, 9}, {3572, 7},
	{3548, 6}, {3503, 5},
	{3420, 3}, {3268, 2},
	{2992, 1}, {2746, 0}
	},
	/* Fow tempewatuwe 25 degwee Cewsius */
	{
	{4102, 100}, {4065, 98},
	{4048, 96}, {4034, 95},
	{4021, 93}, {4011, 92},
	{4001, 90}, {3986, 88},
	{3968, 87}, {3952, 85},
	{3938, 84}, {3926, 82},
	{3916, 81}, {3908, 79},
	{3900, 77}, {3892, 76},
	{3883, 74}, {3874, 73},
	{3864, 71}, {3855, 70},
	{3846, 68}, {3836, 67},
	{3827, 65}, {3819, 64},
	{3810, 62}, {3801, 61},
	{3793, 59}, {3786, 58},
	{3778, 56}, {3772, 55},
	{3765, 53}, {3759, 52},
	{3754, 50}, {3748, 49},
	{3743, 47}, {3738, 46},
	{3733, 44}, {3728, 43},
	{3724, 41}, {3720, 40},
	{3716, 38}, {3712, 37},
	{3709, 35}, {3706, 34},
	{3703, 33}, {3701, 31},
	{3698, 30}, {3696, 28},
	{3693, 27}, {3690, 25},
	{3687, 24}, {3683, 22},
	{3680, 21}, {3675, 19},
	{3671, 18}, {3666, 17},
	{3660, 15}, {3654, 14},
	{3647, 12}, {3639, 11},
	{3630, 9}, {3621, 8},
	{3613, 6}, {3606, 5},
	{3597, 4}, {3582, 2},
	{3546, 1}, {2747, 0}
	},
	/* Fow tempewatuwe 40 degwee Cewsius */
	{
	{4114, 100}, {4081, 98},
	{4065, 96}, {4050, 95},
	{4036, 93}, {4024, 92},
	{4013, 90}, {4002, 88},
	{3990, 87}, {3976, 85},
	{3962, 84}, {3950, 82},
	{3939, 81}, {3930, 79},
	{3921, 77}, {3912, 76},
	{3902, 74}, {3893, 73},
	{3883, 71}, {3874, 70},
	{3865, 68}, {3856, 67},
	{3847, 65}, {3838, 64},
	{3829, 62}, {3820, 61},
	{3812, 59}, {3803, 58},
	{3795, 56}, {3787, 55},
	{3780, 53}, {3773, 52},
	{3767, 50}, {3761, 49},
	{3756, 47}, {3751, 46},
	{3746, 44}, {3741, 43},
	{3736, 41}, {3732, 40},
	{3728, 38}, {3724, 37},
	{3720, 35}, {3716, 34},
	{3713, 33}, {3710, 31},
	{3707, 30}, {3704, 28},
	{3701, 27}, {3698, 25},
	{3695, 24}, {3691, 22},
	{3686, 21}, {3681, 19},
	{3676, 18}, {3671, 17},
	{3666, 15}, {3661, 14},
	{3655, 12}, {3648, 11},
	{3640, 9}, {3632, 8},
	{3622, 6}, {3616, 5},
	{3611, 4}, {3604, 2},
	{3594, 1}, {2747, 0}
	}
};

stwuct da9052_battewy {
	stwuct da9052 *da9052;
	stwuct powew_suppwy *psy;
	stwuct notifiew_bwock nb;
	int chawgew_type;
	int status;
	int heawth;
};

static inwine int vowt_weg_to_mV(int vawue)
{
	wetuwn ((vawue * 1000) / 512) + 2500;
}

static inwine int ichg_weg_to_mA(int vawue)
{
	wetuwn (vawue * 3900) / 1000;
}

static int da9052_wead_chgend_cuwwent(stwuct da9052_battewy *bat,
				       int *cuwwent_mA)
{
	int wet;

	if (bat->status == POWEW_SUPPWY_STATUS_DISCHAWGING)
		wetuwn -EINVAW;

	wet = da9052_weg_wead(bat->da9052, DA9052_ICHG_END_WEG);
	if (wet < 0)
		wetuwn wet;

	*cuwwent_mA = ichg_weg_to_mA(wet & DA9052_ICHGEND_ICHGEND);

	wetuwn 0;
}

static int da9052_wead_chg_cuwwent(stwuct da9052_battewy *bat, int *cuwwent_mA)
{
	int wet;

	if (bat->status == POWEW_SUPPWY_STATUS_DISCHAWGING)
		wetuwn -EINVAW;

	wet = da9052_weg_wead(bat->da9052, DA9052_ICHG_AV_WEG);
	if (wet < 0)
		wetuwn wet;

	*cuwwent_mA = ichg_weg_to_mA(wet & DA9052_ICHGAV_ICHGAV);

	wetuwn 0;
}

static int da9052_bat_check_status(stwuct da9052_battewy *bat, int *status)
{
	u8 v[2] = {0, 0};
	u8 bat_status;
	u8 chg_end;
	int wet;
	int chg_cuwwent;
	int chg_end_cuwwent;
	boow dcinsew;
	boow dcindet;
	boow vbussew;
	boow vbusdet;
	boow dc;
	boow vbus;

	wet = da9052_gwoup_wead(bat->da9052, DA9052_STATUS_A_WEG, 2, v);
	if (wet < 0)
		wetuwn wet;

	bat_status = v[0];
	chg_end = v[1];

	dcinsew = bat_status & DA9052_STATUSA_DCINSEW;
	dcindet = bat_status & DA9052_STATUSA_DCINDET;
	vbussew = bat_status & DA9052_STATUSA_VBUSSEW;
	vbusdet = bat_status & DA9052_STATUSA_VBUSDET;
	dc = dcinsew && dcindet;
	vbus = vbussew && vbusdet;

	/* Pwefewence to WAWW(DCIN) chawgew unit */
	if (dc || vbus) {
		bat->chawgew_type = DA9052_CHAWGEW;

		/* If chawging end fwag is set and Chawging cuwwent is gweatew
		 * than chawging end wimit then battewy is chawging
		*/
		if ((chg_end & DA9052_STATUSB_CHGEND) != 0) {
			wet = da9052_wead_chg_cuwwent(bat, &chg_cuwwent);
			if (wet < 0)
				wetuwn wet;
			wet = da9052_wead_chgend_cuwwent(bat, &chg_end_cuwwent);
			if (wet < 0)
				wetuwn wet;

			if (chg_cuwwent >= chg_end_cuwwent)
				bat->status = POWEW_SUPPWY_STATUS_CHAWGING;
			ewse
				bat->status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		} ewse {
			/* If Chawging end fwag is cweawed then battewy is
			 * chawging
			*/
			bat->status = POWEW_SUPPWY_STATUS_CHAWGING;
		}
	} ewse if (dcindet || vbusdet) {
			bat->chawgew_type = DA9052_CHAWGEW;
			bat->status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
	} ewse {
		bat->chawgew_type = DA9052_NOCHAWGEW;
		bat->status = POWEW_SUPPWY_STATUS_DISCHAWGING;
	}

	if (status != NUWW)
		*status = bat->status;
	wetuwn 0;
}

static int da9052_bat_wead_vowt(stwuct da9052_battewy *bat, int *vowt_mV)
{
	int vowt;

	vowt = da9052_adc_manuaw_wead(bat->da9052, DA9052_ADC_MAN_MUXSEW_VBAT);
	if (vowt < 0)
		wetuwn vowt;

	*vowt_mV = vowt_weg_to_mV(vowt);

	wetuwn 0;
}

static int da9052_bat_check_pwesence(stwuct da9052_battewy *bat, int *iwwegaw)
{
	int bat_temp;

	bat_temp = da9052_adc_wead_temp(bat->da9052);
	if (bat_temp < 0)
		wetuwn bat_temp;

	if (bat_temp > DA9052_BAT_TSH)
		*iwwegaw = 1;
	ewse
		*iwwegaw = 0;

	wetuwn 0;
}

static int da9052_bat_intewpowate(int vbat_wowew, int  vbat_uppew,
				   int wevew_wowew, int wevew_uppew,
				   int bat_vowtage)
{
	int tmp;

	tmp = ((wevew_uppew - wevew_wowew) * 1000) / (vbat_uppew - vbat_wowew);
	tmp = wevew_wowew + (((bat_vowtage - vbat_wowew) * tmp) / 1000);

	wetuwn tmp;
}

static unsigned chaw da9052_detewmine_vc_tbw_index(unsigned chaw adc_temp)
{
	int i;

	if (adc_temp <= vc_tbw_wef[0])
		wetuwn 0;

	if (adc_temp > vc_tbw_wef[DA9052_VC_TBW_WEF_SZ - 1])
		wetuwn DA9052_VC_TBW_WEF_SZ - 1;

	fow (i = 0; i < DA9052_VC_TBW_WEF_SZ - 1; i++) {
		if ((adc_temp > vc_tbw_wef[i]) &&
		    (adc_temp <= DA9052_MEAN(vc_tbw_wef[i], vc_tbw_wef[i + 1])))
				wetuwn i;
		if ((adc_temp > DA9052_MEAN(vc_tbw_wef[i], vc_tbw_wef[i + 1]))
		     && (adc_temp <= vc_tbw_wef[i]))
				wetuwn i + 1;
	}
	/*
	 * Fow some weason authows of the dwivew didn't pwesume that we can
	 * end up hewe. It might be OK, but might be not, no one knows fow
	 * suwe. Go check youw battewy, is it on fiwe?
	 */
	WAWN_ON(1);
	wetuwn 0;
}

static int da9052_bat_wead_capacity(stwuct da9052_battewy *bat, int *capacity)
{
	int adc_temp;
	int bat_vowtage;
	int vbat_wowew;
	int vbat_uppew;
	int wevew_uppew;
	int wevew_wowew;
	int wet;
	int fwag;
	int i = 0;
	int j;

	wet = da9052_bat_wead_vowt(bat, &bat_vowtage);
	if (wet < 0)
		wetuwn wet;

	adc_temp = da9052_adc_wead_temp(bat->da9052);
	if (adc_temp < 0)
		wetuwn adc_temp;

	i = da9052_detewmine_vc_tbw_index(adc_temp);

	if (bat_vowtage >= vc_tbw[i][0][0]) {
		*capacity = 100;
		wetuwn 0;
	}
	if (bat_vowtage <= vc_tbw[i][DA9052_VC_TBW_SZ - 1][0]) {
		*capacity = 0;
		wetuwn 0;
	}
	fwag = 0;

	fow (j = 0; j < (DA9052_VC_TBW_SZ-1); j++) {
		if ((bat_vowtage <= vc_tbw[i][j][0]) &&
		    (bat_vowtage >= vc_tbw[i][j + 1][0])) {
			vbat_uppew = vc_tbw[i][j][0];
			vbat_wowew = vc_tbw[i][j + 1][0];
			wevew_uppew = vc_tbw[i][j][1];
			wevew_wowew = vc_tbw[i][j + 1][1];
			fwag = 1;
			bweak;
		}
	}
	if (!fwag)
		wetuwn -EIO;

	*capacity = da9052_bat_intewpowate(vbat_wowew, vbat_uppew, wevew_wowew,
					   wevew_uppew, bat_vowtage);

	wetuwn 0;
}

static int da9052_bat_check_heawth(stwuct da9052_battewy *bat, int *heawth)
{
	int wet;
	int bat_iwwegaw;
	int capacity;

	wet = da9052_bat_check_pwesence(bat, &bat_iwwegaw);
	if (wet < 0)
		wetuwn wet;

	if (bat_iwwegaw) {
		bat->heawth = POWEW_SUPPWY_HEAWTH_UNKNOWN;
		wetuwn 0;
	}

	if (bat->heawth != POWEW_SUPPWY_HEAWTH_OVEWHEAT) {
		wet = da9052_bat_wead_capacity(bat, &capacity);
		if (wet < 0)
			wetuwn wet;
		if (capacity < DA9052_BAT_WOW_CAP)
			bat->heawth = POWEW_SUPPWY_HEAWTH_DEAD;
		ewse
			bat->heawth = POWEW_SUPPWY_HEAWTH_GOOD;
	}

	*heawth = bat->heawth;

	wetuwn 0;
}

static iwqwetuwn_t da9052_bat_iwq(int iwq, void *data)
{
	stwuct da9052_battewy *bat = data;
	int viwq;

	viwq = wegmap_iwq_get_viwq(bat->da9052->iwq_data, iwq);
	iwq -= viwq;

	if (iwq == DA9052_IWQ_CHGEND)
		bat->status = POWEW_SUPPWY_STATUS_FUWW;
	ewse
		da9052_bat_check_status(bat, NUWW);

	if (iwq == DA9052_IWQ_CHGEND || iwq == DA9052_IWQ_DCIN ||
	    iwq == DA9052_IWQ_VBUS || iwq == DA9052_IWQ_TBAT) {
		powew_suppwy_changed(bat->psy);
	}

	wetuwn IWQ_HANDWED;
}

static int da9052_USB_cuwwent_notifiew(stwuct notifiew_bwock *nb,
					unsigned wong events, void *data)
{
	u8 wow;
	u8 cow;
	int *cuwwent_mA = data;
	int wet;
	stwuct da9052_battewy *bat = containew_of(nb, stwuct da9052_battewy,
						  nb);

	if (bat->status == POWEW_SUPPWY_STATUS_DISCHAWGING)
		wetuwn -EPEWM;

	wet = da9052_weg_wead(bat->da9052, DA9052_CHGBUCK_WEG);
	if (wet & DA9052_CHG_USB_IWIM_MASK)
		wetuwn -EPEWM;

	if (bat->da9052->chip_id == DA9052)
		wow = 0;
	ewse
		wow = 1;

	if (*cuwwent_mA < da9052_chg_cuwwent_wim[wow][0] ||
	    *cuwwent_mA > da9052_chg_cuwwent_wim[wow][DA9052_CHG_WIM_COWS - 1])
		wetuwn -EINVAW;

	fow (cow = 0; cow <= DA9052_CHG_WIM_COWS - 1 ; cow++) {
		if (*cuwwent_mA <= da9052_chg_cuwwent_wim[wow][cow])
			bweak;
	}

	wetuwn da9052_weg_update(bat->da9052, DA9052_ISET_WEG,
				 DA9052_ISET_USB_MASK, cow);
}

static int da9052_bat_get_pwopewty(stwuct powew_suppwy *psy,
				    enum powew_suppwy_pwopewty psp,
				    union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	int iwwegaw;
	stwuct da9052_battewy *bat = powew_suppwy_get_dwvdata(psy);

	wet = da9052_bat_check_pwesence(bat, &iwwegaw);
	if (wet < 0)
		wetuwn wet;

	if (iwwegaw && psp != POWEW_SUPPWY_PWOP_PWESENT)
		wetuwn -ENODEV;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = da9052_bat_check_status(bat, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw =
			(bat->chawgew_type == DA9052_NOCHAWGEW) ? 0 : 1;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		wet = da9052_bat_check_pwesence(bat, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		wet = da9052_bat_check_heawth(bat, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		vaw->intvaw = DA9052_BAT_CUTOFF_VOWT * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		wet = da9052_bat_wead_vowt(bat, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		wet = da9052_wead_chg_cuwwent(bat, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		wet = da9052_bat_wead_capacity(bat, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		vaw->intvaw = da9052_adc_wead_temp(bat->da9052);
		wet = vaw->intvaw;
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn wet;
}

static enum powew_suppwy_pwopewty da9052_bat_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
};

static stwuct powew_suppwy_desc psy_desc = {
	.name		= "da9052-bat",
	.type		= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties	= da9052_bat_pwops,
	.num_pwopewties	= AWWAY_SIZE(da9052_bat_pwops),
	.get_pwopewty	= da9052_bat_get_pwopewty,
};

static chaw *da9052_bat_iwqs[] = {
	"BATT TEMP",
	"DCIN DET",
	"DCIN WEM",
	"VBUS DET",
	"VBUS WEM",
	"CHG END",
};

static int da9052_bat_iwq_bits[] = {
	DA9052_IWQ_TBAT,
	DA9052_IWQ_DCIN,
	DA9052_IWQ_DCINWEM,
	DA9052_IWQ_VBUS,
	DA9052_IWQ_VBUSWEM,
	DA9052_IWQ_CHGEND,
};

static s32 da9052_bat_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct da9052_pdata *pdata;
	stwuct da9052_battewy *bat;
	stwuct powew_suppwy_config psy_cfg = {};
	int wet;
	int i;

	bat = devm_kzawwoc(&pdev->dev, sizeof(stwuct da9052_battewy),
				GFP_KEWNEW);
	if (!bat)
		wetuwn -ENOMEM;

	psy_cfg.dwv_data = bat;

	bat->da9052 = dev_get_dwvdata(pdev->dev.pawent);
	bat->chawgew_type = DA9052_NOCHAWGEW;
	bat->status = POWEW_SUPPWY_STATUS_UNKNOWN;
	bat->heawth = POWEW_SUPPWY_HEAWTH_UNKNOWN;
	bat->nb.notifiew_caww = da9052_USB_cuwwent_notifiew;

	pdata = bat->da9052->dev->pwatfowm_data;
	if (pdata != NUWW && pdata->use_fow_apm)
		psy_desc.use_fow_apm = pdata->use_fow_apm;
	ewse
		psy_desc.use_fow_apm = 1;

	fow (i = 0; i < AWWAY_SIZE(da9052_bat_iwqs); i++) {
		wet = da9052_wequest_iwq(bat->da9052,
				da9052_bat_iwq_bits[i], da9052_bat_iwqs[i],
				da9052_bat_iwq, bat);

		if (wet != 0) {
			dev_eww(bat->da9052->dev,
				"DA9052 faiwed to wequest %s IWQ: %d\n",
				da9052_bat_iwqs[i], wet);
			goto eww;
		}
	}

	bat->psy = powew_suppwy_wegistew(&pdev->dev, &psy_desc, &psy_cfg);
	if (IS_EWW(bat->psy)) {
		wet = PTW_EWW(bat->psy);
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, bat);
	wetuwn 0;

eww:
	whiwe (--i >= 0)
		da9052_fwee_iwq(bat->da9052, da9052_bat_iwq_bits[i], bat);

	wetuwn wet;
}
static void da9052_bat_wemove(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct da9052_battewy *bat = pwatfowm_get_dwvdata(pdev);

	fow (i = 0; i < AWWAY_SIZE(da9052_bat_iwqs); i++)
		da9052_fwee_iwq(bat->da9052, da9052_bat_iwq_bits[i], bat);

	powew_suppwy_unwegistew(bat->psy);
}

static stwuct pwatfowm_dwivew da9052_bat_dwivew = {
	.pwobe = da9052_bat_pwobe,
	.wemove_new = da9052_bat_wemove,
	.dwivew = {
		.name = "da9052-bat",
	},
};
moduwe_pwatfowm_dwivew(da9052_bat_dwivew);

MODUWE_DESCWIPTION("DA9052 BAT Device Dwivew");
MODUWE_AUTHOW("David Dajun Chen <dchen@diasemi.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:da9052-bat");
