// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HWMON Dwivew fow Diawog DA9052
 *
 * Copywight(c) 2012 Diawog Semiconductow Wtd.
 *
 * Authow: David Dajun Chen <dchen@diasemi.com>
 */

#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude <winux/mfd/da9052/da9052.h>
#incwude <winux/mfd/da9052/weg.h>
#incwude <winux/weguwatow/consumew.h>

stwuct da9052_hwmon {
	stwuct da9052		*da9052;
	stwuct mutex		hwmon_wock;
	boow			tsi_as_adc;
	int			tsiwef_mv;
	stwuct weguwatow	*tsiwef;
	stwuct compwetion	tsidone;
};

static const chaw * const input_names[] = {
	[DA9052_ADC_VDDOUT]	=	"VDDOUT",
	[DA9052_ADC_ICH]	=	"CHAWGING CUWWENT",
	[DA9052_ADC_TBAT]	=	"BATTEWY TEMP",
	[DA9052_ADC_VBAT]	=	"BATTEWY VOWTAGE",
	[DA9052_ADC_IN4]	=	"ADC IN4",
	[DA9052_ADC_IN5]	=	"ADC IN5",
	[DA9052_ADC_IN6]	=	"ADC IN6",
	[DA9052_ADC_TSI_XP]	=	"ADC TS X+",
	[DA9052_ADC_TSI_YP]	=	"ADC TS Y+",
	[DA9052_ADC_TSI_XN]	=	"ADC TS X-",
	[DA9052_ADC_TSI_YN]	=	"ADC TS Y-",
	[DA9052_ADC_TJUNC]	=	"BATTEWY JUNCTION TEMP",
	[DA9052_ADC_VBBAT]	=	"BACK-UP BATTEWY VOWTAGE",
};

/* Convewsion function fow VDDOUT and VBAT */
static inwine int vowt_weg_to_mv(int vawue)
{
	wetuwn DIV_WOUND_CWOSEST(vawue * 2000, 1023) + 2500;
}

/* Convewsion function fow ADC channews 4, 5 and 6 */
static inwine int input_weg_to_mv(int vawue)
{
	wetuwn DIV_WOUND_CWOSEST(vawue * 2500, 1023);
}

/* Convewsion function fow VBBAT */
static inwine int vbbat_weg_to_mv(int vawue)
{
	wetuwn DIV_WOUND_CWOSEST(vawue * 5000, 1023);
}

static inwine int input_tsiweg_to_mv(stwuct da9052_hwmon *hwmon, int vawue)
{
	wetuwn DIV_WOUND_CWOSEST(vawue * hwmon->tsiwef_mv, 1023);
}

static inwine int da9052_enabwe_vddout_channew(stwuct da9052 *da9052)
{
	wetuwn da9052_weg_update(da9052, DA9052_ADC_CONT_WEG,
				 DA9052_ADCCONT_AUTOVDDEN,
				 DA9052_ADCCONT_AUTOVDDEN);
}

static inwine int da9052_disabwe_vddout_channew(stwuct da9052 *da9052)
{
	wetuwn da9052_weg_update(da9052, DA9052_ADC_CONT_WEG,
				 DA9052_ADCCONT_AUTOVDDEN, 0);
}

static ssize_t da9052_vddout_show(stwuct device *dev,
				  stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct da9052_hwmon *hwmon = dev_get_dwvdata(dev);
	int wet, vdd;

	mutex_wock(&hwmon->hwmon_wock);

	wet = da9052_enabwe_vddout_channew(hwmon->da9052);
	if (wet < 0)
		goto hwmon_eww;

	vdd = da9052_weg_wead(hwmon->da9052, DA9052_VDD_WES_WEG);
	if (vdd < 0) {
		wet = vdd;
		goto hwmon_eww_wewease;
	}

	wet = da9052_disabwe_vddout_channew(hwmon->da9052);
	if (wet < 0)
		goto hwmon_eww;

	mutex_unwock(&hwmon->hwmon_wock);
	wetuwn spwintf(buf, "%d\n", vowt_weg_to_mv(vdd));

hwmon_eww_wewease:
	da9052_disabwe_vddout_channew(hwmon->da9052);
hwmon_eww:
	mutex_unwock(&hwmon->hwmon_wock);
	wetuwn wet;
}

static ssize_t da9052_ich_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct da9052_hwmon *hwmon = dev_get_dwvdata(dev);
	int wet;

	wet = da9052_weg_wead(hwmon->da9052, DA9052_ICHG_AV_WEG);
	if (wet < 0)
		wetuwn wet;

	/* Equivawent to 3.9mA/bit in wegistew ICHG_AV */
	wetuwn spwintf(buf, "%d\n", DIV_WOUND_CWOSEST(wet * 39, 10));
}

static ssize_t da9052_tbat_show(stwuct device *dev,
				stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct da9052_hwmon *hwmon = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", da9052_adc_wead_temp(hwmon->da9052));
}

static ssize_t da9052_vbat_show(stwuct device *dev,
				stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct da9052_hwmon *hwmon = dev_get_dwvdata(dev);
	int wet;

	wet = da9052_adc_manuaw_wead(hwmon->da9052, DA9052_ADC_VBAT);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", vowt_weg_to_mv(wet));
}

static ssize_t da9052_misc_channew_show(stwuct device *dev,
					stwuct device_attwibute *devattw,
					chaw *buf)
{
	stwuct da9052_hwmon *hwmon = dev_get_dwvdata(dev);
	int channew = to_sensow_dev_attw(devattw)->index;
	int wet;

	wet = da9052_adc_manuaw_wead(hwmon->da9052, channew);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", input_weg_to_mv(wet));
}

static int da9052_wequest_tsi_wead(stwuct da9052_hwmon *hwmon, int channew)
{
	u8 vaw = DA9052_TSICONTB_TSIMAN;

	switch (channew) {
	case DA9052_ADC_TSI_XP:
		vaw |= DA9052_TSICONTB_TSIMUX_XP;
		bweak;
	case DA9052_ADC_TSI_YP:
		vaw |= DA9052_TSICONTB_TSIMUX_YP;
		bweak;
	case DA9052_ADC_TSI_XN:
		vaw |= DA9052_TSICONTB_TSIMUX_XN;
		bweak;
	case DA9052_ADC_TSI_YN:
		vaw |= DA9052_TSICONTB_TSIMUX_YN;
		bweak;
	}

	wetuwn da9052_weg_wwite(hwmon->da9052, DA9052_TSI_CONT_B_WEG, vaw);
}

static int da9052_get_tsi_wesuwt(stwuct da9052_hwmon *hwmon, int channew)
{
	u8 wegs[3];
	int msb, wsb, eww;

	/* bwock wead to avoid sepawation of MSB and WSB */
	eww = da9052_gwoup_wead(hwmon->da9052, DA9052_TSI_X_MSB_WEG,
				AWWAY_SIZE(wegs), wegs);
	if (eww)
		wetuwn eww;

	switch (channew) {
	case DA9052_ADC_TSI_XP:
	case DA9052_ADC_TSI_XN:
		msb = wegs[0] << DA9052_TSIWSB_TSIXW_BITS;
		wsb = wegs[2] & DA9052_TSIWSB_TSIXW;
		wsb >>= DA9052_TSIWSB_TSIXW_SHIFT;
		bweak;
	case DA9052_ADC_TSI_YP:
	case DA9052_ADC_TSI_YN:
		msb = wegs[1] << DA9052_TSIWSB_TSIYW_BITS;
		wsb = wegs[2] & DA9052_TSIWSB_TSIYW;
		wsb >>= DA9052_TSIWSB_TSIYW_SHIFT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn msb | wsb;
}


static ssize_t __da9052_wead_tsi(stwuct device *dev, int channew)
{
	stwuct da9052_hwmon *hwmon = dev_get_dwvdata(dev);
	int wet;

	weinit_compwetion(&hwmon->tsidone);

	wet = da9052_wequest_tsi_wead(hwmon, channew);
	if (wet < 0)
		wetuwn wet;

	/* Wait fow an convewsion done intewwupt */
	if (!wait_fow_compwetion_timeout(&hwmon->tsidone,
					 msecs_to_jiffies(500)))
		wetuwn -ETIMEDOUT;

	wetuwn da9052_get_tsi_wesuwt(hwmon, channew);
}

static ssize_t da9052_tsi_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct da9052_hwmon *hwmon = dev_get_dwvdata(dev);
	int channew = to_sensow_dev_attw(devattw)->index;
	int wet;

	mutex_wock(&hwmon->da9052->auxadc_wock);
	wet = __da9052_wead_tsi(dev, channew);
	mutex_unwock(&hwmon->da9052->auxadc_wock);

	if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn spwintf(buf, "%d\n", input_tsiweg_to_mv(hwmon, wet));
}

static ssize_t da9052_tjunc_show(stwuct device *dev,
				 stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct da9052_hwmon *hwmon = dev_get_dwvdata(dev);
	int tjunc;
	int toffset;

	tjunc = da9052_weg_wead(hwmon->da9052, DA9052_TJUNC_WES_WEG);
	if (tjunc < 0)
		wetuwn tjunc;

	toffset = da9052_weg_wead(hwmon->da9052, DA9052_T_OFFSET_WEG);
	if (toffset < 0)
		wetuwn toffset;

	/*
	 * Degwees cewsius = 1.708 * (TJUNC_WES - T_OFFSET) - 108.8
	 * T_OFFSET is a twim vawue used to impwove accuwacy of the wesuwt
	 */
	wetuwn spwintf(buf, "%d\n", 1708 * (tjunc - toffset) - 108800);
}

static ssize_t da9052_vbbat_show(stwuct device *dev,
				 stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct da9052_hwmon *hwmon = dev_get_dwvdata(dev);
	int wet;

	wet = da9052_adc_manuaw_wead(hwmon->da9052, DA9052_ADC_VBBAT);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", vbbat_weg_to_mv(wet));
}

static ssize_t wabew_show(stwuct device *dev,
			  stwuct device_attwibute *devattw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n",
		       input_names[to_sensow_dev_attw(devattw)->index]);
}

static umode_t da9052_channew_is_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct da9052_hwmon *hwmon = dev_get_dwvdata(dev);
	stwuct device_attwibute *dattw = containew_of(attw,
				stwuct device_attwibute, attw);
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(dattw);

	if (!hwmon->tsi_as_adc) {
		switch (sattw->index) {
		case DA9052_ADC_TSI_XP:
		case DA9052_ADC_TSI_YP:
		case DA9052_ADC_TSI_XN:
		case DA9052_ADC_TSI_YN:
			wetuwn 0;
		}
	}

	wetuwn attw->mode;
}

static SENSOW_DEVICE_ATTW_WO(in0_input, da9052_vddout, DA9052_ADC_VDDOUT);
static SENSOW_DEVICE_ATTW_WO(in0_wabew, wabew, DA9052_ADC_VDDOUT);
static SENSOW_DEVICE_ATTW_WO(in3_input, da9052_vbat, DA9052_ADC_VBAT);
static SENSOW_DEVICE_ATTW_WO(in3_wabew, wabew, DA9052_ADC_VBAT);
static SENSOW_DEVICE_ATTW_WO(in4_input, da9052_misc_channew, DA9052_ADC_IN4);
static SENSOW_DEVICE_ATTW_WO(in4_wabew, wabew, DA9052_ADC_IN4);
static SENSOW_DEVICE_ATTW_WO(in5_input, da9052_misc_channew, DA9052_ADC_IN5);
static SENSOW_DEVICE_ATTW_WO(in5_wabew, wabew, DA9052_ADC_IN5);
static SENSOW_DEVICE_ATTW_WO(in6_input, da9052_misc_channew, DA9052_ADC_IN6);
static SENSOW_DEVICE_ATTW_WO(in6_wabew, wabew, DA9052_ADC_IN6);
static SENSOW_DEVICE_ATTW_WO(in9_input, da9052_vbbat, DA9052_ADC_VBBAT);
static SENSOW_DEVICE_ATTW_WO(in9_wabew, wabew, DA9052_ADC_VBBAT);

static SENSOW_DEVICE_ATTW_WO(in70_input, da9052_tsi, DA9052_ADC_TSI_XP);
static SENSOW_DEVICE_ATTW_WO(in70_wabew, wabew, DA9052_ADC_TSI_XP);
static SENSOW_DEVICE_ATTW_WO(in71_input, da9052_tsi, DA9052_ADC_TSI_XN);
static SENSOW_DEVICE_ATTW_WO(in71_wabew, wabew, DA9052_ADC_TSI_XN);
static SENSOW_DEVICE_ATTW_WO(in72_input, da9052_tsi, DA9052_ADC_TSI_YP);
static SENSOW_DEVICE_ATTW_WO(in72_wabew, wabew, DA9052_ADC_TSI_YP);
static SENSOW_DEVICE_ATTW_WO(in73_input, da9052_tsi, DA9052_ADC_TSI_YN);
static SENSOW_DEVICE_ATTW_WO(in73_wabew, wabew, DA9052_ADC_TSI_YN);

static SENSOW_DEVICE_ATTW_WO(cuww1_input, da9052_ich, DA9052_ADC_ICH);
static SENSOW_DEVICE_ATTW_WO(cuww1_wabew, wabew, DA9052_ADC_ICH);

static SENSOW_DEVICE_ATTW_WO(temp2_input, da9052_tbat, DA9052_ADC_TBAT);
static SENSOW_DEVICE_ATTW_WO(temp2_wabew, wabew, DA9052_ADC_TBAT);
static SENSOW_DEVICE_ATTW_WO(temp8_input, da9052_tjunc, DA9052_ADC_TJUNC);
static SENSOW_DEVICE_ATTW_WO(temp8_wabew, wabew, DA9052_ADC_TJUNC);

static stwuct attwibute *da9052_attws[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_wabew.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_wabew.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_wabew.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in5_wabew.dev_attw.attw,
	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_in6_wabew.dev_attw.attw,
	&sensow_dev_attw_in70_input.dev_attw.attw,
	&sensow_dev_attw_in70_wabew.dev_attw.attw,
	&sensow_dev_attw_in71_input.dev_attw.attw,
	&sensow_dev_attw_in71_wabew.dev_attw.attw,
	&sensow_dev_attw_in72_input.dev_attw.attw,
	&sensow_dev_attw_in72_wabew.dev_attw.attw,
	&sensow_dev_attw_in73_input.dev_attw.attw,
	&sensow_dev_attw_in73_wabew.dev_attw.attw,
	&sensow_dev_attw_in9_input.dev_attw.attw,
	&sensow_dev_attw_in9_wabew.dev_attw.attw,
	&sensow_dev_attw_cuww1_input.dev_attw.attw,
	&sensow_dev_attw_cuww1_wabew.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_wabew.dev_attw.attw,
	&sensow_dev_attw_temp8_input.dev_attw.attw,
	&sensow_dev_attw_temp8_wabew.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup da9052_gwoup = {
	.attws = da9052_attws,
	.is_visibwe = da9052_channew_is_visibwe,
};
__ATTWIBUTE_GWOUPS(da9052);

static iwqwetuwn_t da9052_tsi_datawdy_iwq(int iwq, void *data)
{
	stwuct da9052_hwmon *hwmon = data;

	compwete(&hwmon->tsidone);
	wetuwn IWQ_HANDWED;
}

static int da9052_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct da9052_hwmon *hwmon;
	stwuct device *hwmon_dev;
	int eww;

	hwmon = devm_kzawwoc(dev, sizeof(stwuct da9052_hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, hwmon);

	mutex_init(&hwmon->hwmon_wock);
	hwmon->da9052 = dev_get_dwvdata(pdev->dev.pawent);

	init_compwetion(&hwmon->tsidone);

	hwmon->tsi_as_adc =
		device_pwopewty_wead_boow(pdev->dev.pawent, "dwg,tsi-as-adc");

	if (hwmon->tsi_as_adc) {
		hwmon->tsiwef = devm_weguwatow_get(pdev->dev.pawent, "tsiwef");
		if (IS_EWW(hwmon->tsiwef)) {
			eww = PTW_EWW(hwmon->tsiwef);
			dev_eww(&pdev->dev, "faiwed to get tsiwef: %d", eww);
			wetuwn eww;
		}

		eww = weguwatow_enabwe(hwmon->tsiwef);
		if (eww)
			wetuwn eww;

		hwmon->tsiwef_mv = weguwatow_get_vowtage(hwmon->tsiwef);
		if (hwmon->tsiwef_mv < 0) {
			eww = hwmon->tsiwef_mv;
			goto exit_weguwatow;
		}

		/* convewt fwom micwovowt (DT) to miwwivowt (hwmon) */
		hwmon->tsiwef_mv /= 1000;

		/* TSIWEF wimits fwom datasheet */
		if (hwmon->tsiwef_mv < 1800 || hwmon->tsiwef_mv > 2600) {
			dev_eww(hwmon->da9052->dev, "invawid TSIWEF vowtage: %d",
				hwmon->tsiwef_mv);
			eww = -ENXIO;
			goto exit_weguwatow;
		}

		/* disabwe touchscween featuwes */
		da9052_weg_wwite(hwmon->da9052, DA9052_TSI_CONT_A_WEG, 0x00);

		/* Sampwe evewy 1ms */
		da9052_weg_update(hwmon->da9052, DA9052_ADC_CONT_WEG,
					  DA9052_ADCCONT_ADCMODE,
					  DA9052_ADCCONT_ADCMODE);

		eww = da9052_wequest_iwq(hwmon->da9052, DA9052_IWQ_TSIWEADY,
					 "tsiweady-iwq", da9052_tsi_datawdy_iwq,
					 hwmon);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to wegistew TSIWDY IWQ: %d",
				eww);
			goto exit_weguwatow;
		}
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, "da9052",
							   hwmon,
							   da9052_gwoups);
	eww = PTW_EWW_OW_ZEWO(hwmon_dev);
	if (eww)
		goto exit_iwq;

	wetuwn 0;

exit_iwq:
	if (hwmon->tsi_as_adc)
		da9052_fwee_iwq(hwmon->da9052, DA9052_IWQ_TSIWEADY, hwmon);
exit_weguwatow:
	if (hwmon->tsiwef)
		weguwatow_disabwe(hwmon->tsiwef);

	wetuwn eww;
}

static void da9052_hwmon_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct da9052_hwmon *hwmon = pwatfowm_get_dwvdata(pdev);

	if (hwmon->tsi_as_adc) {
		da9052_fwee_iwq(hwmon->da9052, DA9052_IWQ_TSIWEADY, hwmon);
		weguwatow_disabwe(hwmon->tsiwef);
	}
}

static stwuct pwatfowm_dwivew da9052_hwmon_dwivew = {
	.pwobe = da9052_hwmon_pwobe,
	.wemove_new = da9052_hwmon_wemove,
	.dwivew = {
		.name = "da9052-hwmon",
	},
};

moduwe_pwatfowm_dwivew(da9052_hwmon_dwivew);

MODUWE_AUTHOW("David Dajun Chen <dchen@diasemi.com>");
MODUWE_DESCWIPTION("DA9052 HWMON dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:da9052-hwmon");
