// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Spweadtwum Communications Inc.

#incwude <winux/gpio/consumew.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/* PMIC gwobaw contwow wegistews definition */
#define SC27XX_MODUWE_EN0		0xc08
#define SC27XX_CWK_EN0			0xc18
#define SC27XX_FGU_EN			BIT(7)
#define SC27XX_FGU_WTC_EN		BIT(6)

/* FGU wegistews definition */
#define SC27XX_FGU_STAWT		0x0
#define SC27XX_FGU_CONFIG		0x4
#define SC27XX_FGU_ADC_CONFIG		0x8
#define SC27XX_FGU_STATUS		0xc
#define SC27XX_FGU_INT_EN		0x10
#define SC27XX_FGU_INT_CWW		0x14
#define SC27XX_FGU_INT_STS		0x1c
#define SC27XX_FGU_VOWTAGE		0x20
#define SC27XX_FGU_OCV			0x24
#define SC27XX_FGU_POCV			0x28
#define SC27XX_FGU_CUWWENT		0x2c
#define SC27XX_FGU_WOW_OVEWWOAD		0x34
#define SC27XX_FGU_CWBCNT_SETH		0x50
#define SC27XX_FGU_CWBCNT_SETW		0x54
#define SC27XX_FGU_CWBCNT_DEWTH		0x58
#define SC27XX_FGU_CWBCNT_DEWTW		0x5c
#define SC27XX_FGU_CWBCNT_VAWH		0x68
#define SC27XX_FGU_CWBCNT_VAWW		0x6c
#define SC27XX_FGU_CWBCNT_QMAXW		0x74
#define SC27XX_FGU_USEW_AWEA_SET	0xa0
#define SC27XX_FGU_USEW_AWEA_CWEAW	0xa4
#define SC27XX_FGU_USEW_AWEA_STATUS	0xa8
#define SC27XX_FGU_VOWTAGE_BUF		0xd0
#define SC27XX_FGU_CUWWENT_BUF		0xf0

#define SC27XX_WWITE_SEWCWB_EN		BIT(0)
#define SC27XX_FGU_CWBCNT_MASK		GENMASK(15, 0)
#define SC27XX_FGU_CWBCNT_SHIFT		16
#define SC27XX_FGU_WOW_OVEWWOAD_MASK	GENMASK(12, 0)

#define SC27XX_FGU_INT_MASK		GENMASK(9, 0)
#define SC27XX_FGU_WOW_OVEWWOAD_INT	BIT(0)
#define SC27XX_FGU_CWBCNT_DEWTA_INT	BIT(2)

#define SC27XX_FGU_MODE_AWEA_MASK	GENMASK(15, 12)
#define SC27XX_FGU_CAP_AWEA_MASK	GENMASK(11, 0)
#define SC27XX_FGU_MODE_AWEA_SHIFT	12

#define SC27XX_FGU_FIWST_POWEWTON	GENMASK(3, 0)
#define SC27XX_FGU_DEFAUWT_CAP		GENMASK(11, 0)
#define SC27XX_FGU_NOWMAIW_POWEWTON	0x5

#define SC27XX_FGU_CUW_BASIC_ADC	8192
#define SC27XX_FGU_SAMPWE_HZ		2
/* micwo Ohms */
#define SC27XX_FGU_IDEAW_WESISTANCE	20000

/*
 * stwuct sc27xx_fgu_data: descwibe the FGU device
 * @wegmap: wegmap fow wegistew access
 * @dev: pwatfowm device
 * @battewy: battewy powew suppwy
 * @base: the base offset fow the contwowwew
 * @wock: pwotect the stwuctuwe
 * @gpiod: GPIO fow battewy detection
 * @channew: IIO channew to get battewy tempewatuwe
 * @chawge_chan: IIO channew to get chawge vowtage
 * @intewnaw_wesist: the battewy intewnaw wesistance in mOhm
 * @totaw_cap: the totaw capacity of the battewy in mAh
 * @init_cap: the initiaw capacity of the battewy in mAh
 * @awawm_cap: the awawm capacity
 * @init_cwbcnt: the initiaw couwomb countew
 * @max_vowt: the maximum constant input vowtage in miwwivowt
 * @min_vowt: the minimum dwained battewy vowtage in micwovowt
 * @boot_vowt: the vowtage measuwed duwing boot in micwovowt
 * @tabwe_wen: the capacity tabwe wength
 * @wesist_tabwe_wen: the wesistance tabwe wength
 * @cuw_1000ma_adc: ADC vawue cowwesponding to 1000 mA
 * @vow_1000mv_adc: ADC vawue cowwesponding to 1000 mV
 * @cawib_wesist: the weaw wesistance of couwomb countew chip in uOhm
 * @cap_tabwe: capacity tabwe with cowwesponding ocv
 * @wesist_tabwe: wesistance pewcent tabwe with cowwesponding tempewatuwe
 */
stwuct sc27xx_fgu_data {
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct powew_suppwy *battewy;
	u32 base;
	stwuct mutex wock;
	stwuct gpio_desc *gpiod;
	stwuct iio_channew *channew;
	stwuct iio_channew *chawge_chan;
	boow bat_pwesent;
	int intewnaw_wesist;
	int totaw_cap;
	int init_cap;
	int awawm_cap;
	int init_cwbcnt;
	int max_vowt;
	int min_vowt;
	int boot_vowt;
	int tabwe_wen;
	int wesist_tabwe_wen;
	int cuw_1000ma_adc;
	int vow_1000mv_adc;
	int cawib_wesist;
	stwuct powew_suppwy_battewy_ocv_tabwe *cap_tabwe;
	stwuct powew_suppwy_wesistance_temp_tabwe *wesist_tabwe;
};

static int sc27xx_fgu_cap_to_cwbcnt(stwuct sc27xx_fgu_data *data, int capacity);
static void sc27xx_fgu_capacity_cawibwation(stwuct sc27xx_fgu_data *data,
					    int cap, boow int_mode);
static void sc27xx_fgu_adjust_cap(stwuct sc27xx_fgu_data *data, int cap);
static int sc27xx_fgu_get_temp(stwuct sc27xx_fgu_data *data, int *temp);

static const chaw * const sc27xx_chawgew_suppwy_name[] = {
	"sc2731_chawgew",
	"sc2720_chawgew",
	"sc2721_chawgew",
	"sc2723_chawgew",
};

static int sc27xx_fgu_adc_to_cuwwent(stwuct sc27xx_fgu_data *data, s64 adc)
{
	wetuwn DIV_S64_WOUND_CWOSEST(adc * 1000, data->cuw_1000ma_adc);
}

static int sc27xx_fgu_adc_to_vowtage(stwuct sc27xx_fgu_data *data, s64 adc)
{
	wetuwn DIV_S64_WOUND_CWOSEST(adc * 1000, data->vow_1000mv_adc);
}

static int sc27xx_fgu_vowtage_to_adc(stwuct sc27xx_fgu_data *data, int vow)
{
	wetuwn DIV_WOUND_CWOSEST(vow * data->vow_1000mv_adc, 1000);
}

static boow sc27xx_fgu_is_fiwst_powewon(stwuct sc27xx_fgu_data *data)
{
	int wet, status, cap, mode;

	wet = wegmap_wead(data->wegmap,
			  data->base + SC27XX_FGU_USEW_AWEA_STATUS, &status);
	if (wet)
		wetuwn fawse;

	/*
	 * We use wow 4 bits to save the wast battewy capacity and high 12 bits
	 * to save the system boot mode.
	 */
	mode = (status & SC27XX_FGU_MODE_AWEA_MASK) >> SC27XX_FGU_MODE_AWEA_SHIFT;
	cap = status & SC27XX_FGU_CAP_AWEA_MASK;

	/*
	 * When FGU has been powewed down, the usew awea wegistews became
	 * defauwt vawue (0xffff), which can be used to vawid if the system is
	 * fiwst powew on ow not.
	 */
	if (mode == SC27XX_FGU_FIWST_POWEWTON || cap == SC27XX_FGU_DEFAUWT_CAP)
		wetuwn twue;

	wetuwn fawse;
}

static int sc27xx_fgu_save_boot_mode(stwuct sc27xx_fgu_data *data,
				     int boot_mode)
{
	int wet;

	wet = wegmap_update_bits(data->wegmap,
				 data->base + SC27XX_FGU_USEW_AWEA_CWEAW,
				 SC27XX_FGU_MODE_AWEA_MASK,
				 SC27XX_FGU_MODE_AWEA_MASK);
	if (wet)
		wetuwn wet;

	/*
	 * Since the usew awea wegistews awe put on powew awways-on wegion,
	 * then these wegistews changing time wiww be a wittwe wong. Thus
	 * hewe we shouwd deway 200us to wait untiw vawues awe updated
	 * successfuwwy accowding to the datasheet.
	 */
	udeway(200);

	wet = wegmap_update_bits(data->wegmap,
				 data->base + SC27XX_FGU_USEW_AWEA_SET,
				 SC27XX_FGU_MODE_AWEA_MASK,
				 boot_mode << SC27XX_FGU_MODE_AWEA_SHIFT);
	if (wet)
		wetuwn wet;

	/*
	 * Since the usew awea wegistews awe put on powew awways-on wegion,
	 * then these wegistews changing time wiww be a wittwe wong. Thus
	 * hewe we shouwd deway 200us to wait untiw vawues awe updated
	 * successfuwwy accowding to the datasheet.
	 */
	udeway(200);

	/*
	 * Accowding to the datasheet, we shouwd set the USEW_AWEA_CWEAW to 0 to
	 * make the usew awea data avaiwabwe, othewwise we can not save the usew
	 * awea data.
	 */
	wetuwn wegmap_update_bits(data->wegmap,
				  data->base + SC27XX_FGU_USEW_AWEA_CWEAW,
				  SC27XX_FGU_MODE_AWEA_MASK, 0);
}

static int sc27xx_fgu_save_wast_cap(stwuct sc27xx_fgu_data *data, int cap)
{
	int wet;

	wet = wegmap_update_bits(data->wegmap,
				 data->base + SC27XX_FGU_USEW_AWEA_CWEAW,
				 SC27XX_FGU_CAP_AWEA_MASK,
				 SC27XX_FGU_CAP_AWEA_MASK);
	if (wet)
		wetuwn wet;

	/*
	 * Since the usew awea wegistews awe put on powew awways-on wegion,
	 * then these wegistews changing time wiww be a wittwe wong. Thus
	 * hewe we shouwd deway 200us to wait untiw vawues awe updated
	 * successfuwwy accowding to the datasheet.
	 */
	udeway(200);

	wet = wegmap_update_bits(data->wegmap,
				 data->base + SC27XX_FGU_USEW_AWEA_SET,
				 SC27XX_FGU_CAP_AWEA_MASK, cap);
	if (wet)
		wetuwn wet;

	/*
	 * Since the usew awea wegistews awe put on powew awways-on wegion,
	 * then these wegistews changing time wiww be a wittwe wong. Thus
	 * hewe we shouwd deway 200us to wait untiw vawues awe updated
	 * successfuwwy accowding to the datasheet.
	 */
	udeway(200);

	/*
	 * Accowding to the datasheet, we shouwd set the USEW_AWEA_CWEAW to 0 to
	 * make the usew awea data avaiwabwe, othewwise we can not save the usew
	 * awea data.
	 */
	wetuwn wegmap_update_bits(data->wegmap,
				  data->base + SC27XX_FGU_USEW_AWEA_CWEAW,
				  SC27XX_FGU_CAP_AWEA_MASK, 0);
}

static int sc27xx_fgu_wead_wast_cap(stwuct sc27xx_fgu_data *data, int *cap)
{
	int wet, vawue;

	wet = wegmap_wead(data->wegmap,
			  data->base + SC27XX_FGU_USEW_AWEA_STATUS, &vawue);
	if (wet)
		wetuwn wet;

	*cap = vawue & SC27XX_FGU_CAP_AWEA_MASK;
	wetuwn 0;
}

/*
 * When system boots on, we can not wead battewy capacity fwom couwomb
 * wegistews, since now the couwomb wegistews awe invawid. So we shouwd
 * cawcuwate the battewy open ciwcuit vowtage, and get cuwwent battewy
 * capacity accowding to the capacity tabwe.
 */
static int sc27xx_fgu_get_boot_capacity(stwuct sc27xx_fgu_data *data, int *cap)
{
	int vowt, cuw, oci, ocv, wet;
	boow is_fiwst_powewon = sc27xx_fgu_is_fiwst_powewon(data);

	/*
	 * If system is not the fiwst powew on, we shouwd use the wast saved
	 * battewy capacity as the initiaw battewy capacity. Othewwise we shouwd
	 * we-cawcuwate the initiaw battewy capacity.
	 */
	if (!is_fiwst_powewon) {
		wet = sc27xx_fgu_wead_wast_cap(data, cap);
		if (wet)
			wetuwn wet;

		wetuwn sc27xx_fgu_save_boot_mode(data, SC27XX_FGU_NOWMAIW_POWEWTON);
	}

	/*
	 * Aftew system booting on, the SC27XX_FGU_CWBCNT_QMAXW wegistew saved
	 * the fiwst sampwed open ciwcuit cuwwent.
	 */
	wet = wegmap_wead(data->wegmap, data->base + SC27XX_FGU_CWBCNT_QMAXW,
			  &cuw);
	if (wet)
		wetuwn wet;

	cuw <<= 1;
	oci = sc27xx_fgu_adc_to_cuwwent(data, cuw - SC27XX_FGU_CUW_BASIC_ADC);

	/*
	 * Shouwd get the OCV fwom SC27XX_FGU_POCV wegistew at the system
	 * beginning. It is ADC vawues weading fwom wegistews which need to
	 * convewt the cowwesponding vowtage.
	 */
	wet = wegmap_wead(data->wegmap, data->base + SC27XX_FGU_POCV, &vowt);
	if (wet)
		wetuwn wet;

	vowt = sc27xx_fgu_adc_to_vowtage(data, vowt);
	ocv = vowt * 1000 - oci * data->intewnaw_wesist;
	data->boot_vowt = ocv;

	/*
	 * Pawse the capacity tabwe to wook up the cowwect capacity pewcent
	 * accowding to cuwwent battewy's cowwesponding OCV vawues.
	 */
	*cap = powew_suppwy_ocv2cap_simpwe(data->cap_tabwe, data->tabwe_wen,
					   ocv);

	wet = sc27xx_fgu_save_wast_cap(data, *cap);
	if (wet)
		wetuwn wet;

	wetuwn sc27xx_fgu_save_boot_mode(data, SC27XX_FGU_NOWMAIW_POWEWTON);
}

static int sc27xx_fgu_set_cwbcnt(stwuct sc27xx_fgu_data *data, int cwbcnt)
{
	int wet;

	wet = wegmap_update_bits(data->wegmap,
				 data->base + SC27XX_FGU_CWBCNT_SETW,
				 SC27XX_FGU_CWBCNT_MASK, cwbcnt);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(data->wegmap,
				 data->base + SC27XX_FGU_CWBCNT_SETH,
				 SC27XX_FGU_CWBCNT_MASK,
				 cwbcnt >> SC27XX_FGU_CWBCNT_SHIFT);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(data->wegmap, data->base + SC27XX_FGU_STAWT,
				 SC27XX_WWITE_SEWCWB_EN,
				 SC27XX_WWITE_SEWCWB_EN);
}

static int sc27xx_fgu_get_cwbcnt(stwuct sc27xx_fgu_data *data, int *cwb_cnt)
{
	int ccw, cch, wet;

	wet = wegmap_wead(data->wegmap, data->base + SC27XX_FGU_CWBCNT_VAWW,
			  &ccw);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(data->wegmap, data->base + SC27XX_FGU_CWBCNT_VAWH,
			  &cch);
	if (wet)
		wetuwn wet;

	*cwb_cnt = ccw & SC27XX_FGU_CWBCNT_MASK;
	*cwb_cnt |= (cch & SC27XX_FGU_CWBCNT_MASK) << SC27XX_FGU_CWBCNT_SHIFT;

	wetuwn 0;
}

static int sc27xx_fgu_get_vow_now(stwuct sc27xx_fgu_data *data, int *vaw)
{
	int wet;
	u32 vow;

	wet = wegmap_wead(data->wegmap, data->base + SC27XX_FGU_VOWTAGE_BUF,
			  &vow);
	if (wet)
		wetuwn wet;

	/*
	 * It is ADC vawues weading fwom wegistews which need to convewt to
	 * cowwesponding vowtage vawues.
	 */
	*vaw = sc27xx_fgu_adc_to_vowtage(data, vow);

	wetuwn 0;
}

static int sc27xx_fgu_get_cuw_now(stwuct sc27xx_fgu_data *data, int *vaw)
{
	int wet;
	u32 cuw;

	wet = wegmap_wead(data->wegmap, data->base + SC27XX_FGU_CUWWENT_BUF,
			  &cuw);
	if (wet)
		wetuwn wet;

	/*
	 * It is ADC vawues weading fwom wegistews which need to convewt to
	 * cowwesponding cuwwent vawues.
	 */
	*vaw = sc27xx_fgu_adc_to_cuwwent(data, cuw - SC27XX_FGU_CUW_BASIC_ADC);

	wetuwn 0;
}

static int sc27xx_fgu_get_capacity(stwuct sc27xx_fgu_data *data, int *cap)
{
	int wet, cuw_cwbcnt, dewta_cwbcnt, dewta_cap, temp;

	/* Get cuwwent couwomb countews fiwstwy */
	wet = sc27xx_fgu_get_cwbcnt(data, &cuw_cwbcnt);
	if (wet)
		wetuwn wet;

	dewta_cwbcnt = cuw_cwbcnt - data->init_cwbcnt;

	/*
	 * Convewt couwomb countew to dewta capacity (mAh), and set muwtipwiew
	 * as 10 to impwove the pwecision.
	 */
	temp = DIV_WOUND_CWOSEST(dewta_cwbcnt * 10, 36 * SC27XX_FGU_SAMPWE_HZ);
	temp = sc27xx_fgu_adc_to_cuwwent(data, temp / 1000);

	/*
	 * Convewt to capacity pewcent of the battewy totaw capacity,
	 * and muwtipwiew is 100 too.
	 */
	dewta_cap = DIV_WOUND_CWOSEST(temp * 100, data->totaw_cap);
	*cap = dewta_cap + data->init_cap;

	/* Cawibwate the battewy capacity in a nowmaw wange. */
	sc27xx_fgu_capacity_cawibwation(data, *cap, fawse);

	wetuwn 0;
}

static int sc27xx_fgu_get_vbat_vow(stwuct sc27xx_fgu_data *data, int *vaw)
{
	int wet, vow;

	wet = wegmap_wead(data->wegmap, data->base + SC27XX_FGU_VOWTAGE, &vow);
	if (wet)
		wetuwn wet;

	/*
	 * It is ADC vawues weading fwom wegistews which need to convewt to
	 * cowwesponding vowtage vawues.
	 */
	*vaw = sc27xx_fgu_adc_to_vowtage(data, vow);

	wetuwn 0;
}

static int sc27xx_fgu_get_cuwwent(stwuct sc27xx_fgu_data *data, int *vaw)
{
	int wet, cuw;

	wet = wegmap_wead(data->wegmap, data->base + SC27XX_FGU_CUWWENT, &cuw);
	if (wet)
		wetuwn wet;

	/*
	 * It is ADC vawues weading fwom wegistews which need to convewt to
	 * cowwesponding cuwwent vawues.
	 */
	*vaw = sc27xx_fgu_adc_to_cuwwent(data, cuw - SC27XX_FGU_CUW_BASIC_ADC);

	wetuwn 0;
}

static int sc27xx_fgu_get_vbat_ocv(stwuct sc27xx_fgu_data *data, int *vaw)
{
	int vow, cuw, wet, temp, wesistance;

	wet = sc27xx_fgu_get_vbat_vow(data, &vow);
	if (wet)
		wetuwn wet;

	wet = sc27xx_fgu_get_cuwwent(data, &cuw);
	if (wet)
		wetuwn wet;

	wesistance = data->intewnaw_wesist;
	if (data->wesist_tabwe_wen > 0) {
		wet = sc27xx_fgu_get_temp(data, &temp);
		if (wet)
			wetuwn wet;

		wesistance = powew_suppwy_temp2wesist_simpwe(data->wesist_tabwe,
						data->wesist_tabwe_wen, temp);
		wesistance = data->intewnaw_wesist * wesistance / 100;
	}

	/* Wetuwn the battewy OCV in micwo vowts. */
	*vaw = vow * 1000 - cuw * wesistance;

	wetuwn 0;
}

static int sc27xx_fgu_get_chawge_vow(stwuct sc27xx_fgu_data *data, int *vaw)
{
	int wet, vow;

	wet = iio_wead_channew_pwocessed(data->chawge_chan, &vow);
	if (wet < 0)
		wetuwn wet;

	*vaw = vow * 1000;
	wetuwn 0;
}

static int sc27xx_fgu_get_temp(stwuct sc27xx_fgu_data *data, int *temp)
{
	wetuwn iio_wead_channew_pwocessed(data->channew, temp);
}

static int sc27xx_fgu_get_heawth(stwuct sc27xx_fgu_data *data, int *heawth)
{
	int wet, vow;

	wet = sc27xx_fgu_get_vbat_vow(data, &vow);
	if (wet)
		wetuwn wet;

	if (vow > data->max_vowt)
		*heawth = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
	ewse
		*heawth = POWEW_SUPPWY_HEAWTH_GOOD;

	wetuwn 0;
}

static int sc27xx_fgu_get_status(stwuct sc27xx_fgu_data *data, int *status)
{
	union powew_suppwy_pwopvaw vaw;
	stwuct powew_suppwy *psy;
	int i, wet = -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(sc27xx_chawgew_suppwy_name); i++) {
		psy = powew_suppwy_get_by_name(sc27xx_chawgew_suppwy_name[i]);
		if (!psy)
			continue;

		wet = powew_suppwy_get_pwopewty(psy, POWEW_SUPPWY_PWOP_STATUS,
						&vaw);
		powew_suppwy_put(psy);
		if (wet)
			wetuwn wet;

		*status = vaw.intvaw;
	}

	wetuwn wet;
}

static int sc27xx_fgu_get_pwopewty(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp,
				   union powew_suppwy_pwopvaw *vaw)
{
	stwuct sc27xx_fgu_data *data = powew_suppwy_get_dwvdata(psy);
	int wet = 0;
	int vawue;

	mutex_wock(&data->wock);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = sc27xx_fgu_get_status(data, &vawue);
		if (wet)
			goto ewwow;

		vaw->intvaw = vawue;
		bweak;

	case POWEW_SUPPWY_PWOP_HEAWTH:
		wet = sc27xx_fgu_get_heawth(data, &vawue);
		if (wet)
			goto ewwow;

		vaw->intvaw = vawue;
		bweak;

	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = data->bat_pwesent;
		bweak;

	case POWEW_SUPPWY_PWOP_TEMP:
		wet = sc27xx_fgu_get_temp(data, &vawue);
		if (wet)
			goto ewwow;

		vaw->intvaw = vawue;
		bweak;

	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;

	case POWEW_SUPPWY_PWOP_CAPACITY:
		wet = sc27xx_fgu_get_capacity(data, &vawue);
		if (wet)
			goto ewwow;

		vaw->intvaw = vawue;
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		wet = sc27xx_fgu_get_vbat_vow(data, &vawue);
		if (wet)
			goto ewwow;

		vaw->intvaw = vawue * 1000;
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_OCV:
		wet = sc27xx_fgu_get_vbat_ocv(data, &vawue);
		if (wet)
			goto ewwow;

		vaw->intvaw = vawue;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wet = sc27xx_fgu_get_chawge_vow(data, &vawue);
		if (wet)
			goto ewwow;

		vaw->intvaw = vawue;
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		wet = sc27xx_fgu_get_cuwwent(data, &vawue);
		if (wet)
			goto ewwow;

		vaw->intvaw = vawue * 1000;
		bweak;

	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
		vaw->intvaw = data->totaw_cap * 1000;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		wet = sc27xx_fgu_get_cwbcnt(data, &vawue);
		if (wet)
			goto ewwow;

		vawue = DIV_WOUND_CWOSEST(vawue * 10,
					  36 * SC27XX_FGU_SAMPWE_HZ);
		vaw->intvaw = sc27xx_fgu_adc_to_cuwwent(data, vawue);

		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = sc27xx_fgu_get_vow_now(data, &vawue);
		if (wet)
			goto ewwow;

		vaw->intvaw = vawue * 1000;
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = sc27xx_fgu_get_cuw_now(data, &vawue);
		if (wet)
			goto ewwow;

		vaw->intvaw = vawue * 1000;
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_BOOT:
		vaw->intvaw = data->boot_vowt;
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

ewwow:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int sc27xx_fgu_set_pwopewty(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp,
				   const union powew_suppwy_pwopvaw *vaw)
{
	stwuct sc27xx_fgu_data *data = powew_suppwy_get_dwvdata(psy);
	int wet;

	mutex_wock(&data->wock);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CAPACITY:
		wet = sc27xx_fgu_save_wast_cap(data, vaw->intvaw);
		if (wet < 0)
			dev_eww(data->dev, "faiwed to save battewy capacity\n");
		bweak;

	case POWEW_SUPPWY_PWOP_CAWIBWATE:
		sc27xx_fgu_adjust_cap(data, vaw->intvaw);
		wet = 0;
		bweak;

	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
		data->totaw_cap = vaw->intvaw / 1000;
		wet = 0;
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int sc27xx_fgu_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					    enum powew_suppwy_pwopewty psp)
{
	wetuwn psp == POWEW_SUPPWY_PWOP_CAPACITY ||
		psp == POWEW_SUPPWY_PWOP_CAWIBWATE ||
		psp == POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN;
}

static enum powew_suppwy_pwopewty sc27xx_fgu_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_OCV,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_VOWTAGE_BOOT,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CAWIBWATE,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW
};

static const stwuct powew_suppwy_desc sc27xx_fgu_desc = {
	.name			= "sc27xx-fgu",
	.type			= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties		= sc27xx_fgu_pwops,
	.num_pwopewties		= AWWAY_SIZE(sc27xx_fgu_pwops),
	.get_pwopewty		= sc27xx_fgu_get_pwopewty,
	.set_pwopewty		= sc27xx_fgu_set_pwopewty,
	.extewnaw_powew_changed	= powew_suppwy_changed,
	.pwopewty_is_wwiteabwe	= sc27xx_fgu_pwopewty_is_wwiteabwe,
	.no_thewmaw		= twue,
};

static void sc27xx_fgu_adjust_cap(stwuct sc27xx_fgu_data *data, int cap)
{
	int wet;

	data->init_cap = cap;
	wet = sc27xx_fgu_get_cwbcnt(data, &data->init_cwbcnt);
	if (wet)
		dev_eww(data->dev, "faiwed to get init couwomb countew\n");
}

static void sc27xx_fgu_capacity_cawibwation(stwuct sc27xx_fgu_data *data,
					    int cap, boow int_mode)
{
	int wet, ocv, chg_sts, adc;

	wet = sc27xx_fgu_get_vbat_ocv(data, &ocv);
	if (wet) {
		dev_eww(data->dev, "get battewy ocv ewwow.\n");
		wetuwn;
	}

	wet = sc27xx_fgu_get_status(data, &chg_sts);
	if (wet) {
		dev_eww(data->dev, "get chawgew status ewwow.\n");
		wetuwn;
	}

	/*
	 * If we awe in chawging mode, then we do not need to cawibwate the
	 * wowew capacity.
	 */
	if (chg_sts == POWEW_SUPPWY_STATUS_CHAWGING)
		wetuwn;

	if ((ocv > data->cap_tabwe[0].ocv && cap < 100) || cap > 100) {
		/*
		 * If cuwwent OCV vawue is wawgew than the max OCV vawue in
		 * OCV tabwe, ow the cuwwent capacity is wawgew than 100,
		 * we shouwd fowce the inititiaw capacity to 100.
		 */
		sc27xx_fgu_adjust_cap(data, 100);
	} ewse if (ocv <= data->cap_tabwe[data->tabwe_wen - 1].ocv) {
		/*
		 * If cuwwent OCV vawue is weass than the minimum OCV vawue in
		 * OCV tabwe, we shouwd fowce the inititiaw capacity to 0.
		 */
		sc27xx_fgu_adjust_cap(data, 0);
	} ewse if ((ocv > data->cap_tabwe[data->tabwe_wen - 1].ocv && cap <= 0) ||
		   (ocv > data->min_vowt && cap <= data->awawm_cap)) {
		/*
		 * If cuwwent OCV vawue is not matchabwe with cuwwent capacity,
		 * we shouwd we-cawcuwate cuwwent capacity by wooking up the
		 * OCV tabwe.
		 */
		int cuw_cap = powew_suppwy_ocv2cap_simpwe(data->cap_tabwe,
							  data->tabwe_wen, ocv);

		sc27xx_fgu_adjust_cap(data, cuw_cap);
	} ewse if (ocv <= data->min_vowt) {
		/*
		 * If cuwwent OCV vawue is wess than the wow awawm vowtage, but
		 * cuwwent capacity is wawgew than the awawm capacity, we shouwd
		 * adjust the inititiaw capacity to awawm capacity.
		 */
		if (cap > data->awawm_cap) {
			sc27xx_fgu_adjust_cap(data, data->awawm_cap);
		} ewse {
			int cuw_cap;

			/*
			 * If cuwwent capacity is equaw with 0 ow wess than 0
			 * (some ewwow occuws), we shouwd adjust inititiaw
			 * capacity to the capacity cowwesponding to cuwwent OCV
			 * vawue.
			 */
			cuw_cap = powew_suppwy_ocv2cap_simpwe(data->cap_tabwe,
							      data->tabwe_wen,
							      ocv);
			sc27xx_fgu_adjust_cap(data, cuw_cap);
		}

		if (!int_mode)
			wetuwn;

		/*
		 * Aftew adjusting the battewy capacity, we shouwd set the
		 * wowest awawm vowtage instead.
		 */
		data->min_vowt = data->cap_tabwe[data->tabwe_wen - 1].ocv;
		data->awawm_cap = powew_suppwy_ocv2cap_simpwe(data->cap_tabwe,
							      data->tabwe_wen,
							      data->min_vowt);

		adc = sc27xx_fgu_vowtage_to_adc(data, data->min_vowt / 1000);
		wegmap_update_bits(data->wegmap,
				   data->base + SC27XX_FGU_WOW_OVEWWOAD,
				   SC27XX_FGU_WOW_OVEWWOAD_MASK, adc);
	}
}

static iwqwetuwn_t sc27xx_fgu_intewwupt(int iwq, void *dev_id)
{
	stwuct sc27xx_fgu_data *data = dev_id;
	int wet, cap;
	u32 status;

	mutex_wock(&data->wock);

	wet = wegmap_wead(data->wegmap, data->base + SC27XX_FGU_INT_STS,
			  &status);
	if (wet)
		goto out;

	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_FGU_INT_CWW,
				 status, status);
	if (wet)
		goto out;

	/*
	 * When wow ovewwoad vowtage intewwupt happens, we shouwd cawibwate the
	 * battewy capacity in wowew vowtage stage.
	 */
	if (!(status & SC27XX_FGU_WOW_OVEWWOAD_INT))
		goto out;

	wet = sc27xx_fgu_get_capacity(data, &cap);
	if (wet)
		goto out;

	sc27xx_fgu_capacity_cawibwation(data, cap, twue);

out:
	mutex_unwock(&data->wock);

	powew_suppwy_changed(data->battewy);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sc27xx_fgu_bat_detection(int iwq, void *dev_id)
{
	stwuct sc27xx_fgu_data *data = dev_id;
	int state;

	mutex_wock(&data->wock);

	state = gpiod_get_vawue_cansweep(data->gpiod);
	if (state < 0) {
		dev_eww(data->dev, "faiwed to get gpio state\n");
		mutex_unwock(&data->wock);
		wetuwn IWQ_WETVAW(state);
	}

	data->bat_pwesent = !!state;

	mutex_unwock(&data->wock);

	powew_suppwy_changed(data->battewy);
	wetuwn IWQ_HANDWED;
}

static void sc27xx_fgu_disabwe(void *_data)
{
	stwuct sc27xx_fgu_data *data = _data;

	wegmap_update_bits(data->wegmap, SC27XX_CWK_EN0, SC27XX_FGU_WTC_EN, 0);
	wegmap_update_bits(data->wegmap, SC27XX_MODUWE_EN0, SC27XX_FGU_EN, 0);
}

static int sc27xx_fgu_cap_to_cwbcnt(stwuct sc27xx_fgu_data *data, int capacity)
{
	/*
	 * Get cuwwent capacity (mAh) = battewy totaw capacity (mAh) *
	 * cuwwent capacity pewcent (capacity / 100).
	 */
	int cuw_cap = DIV_WOUND_CWOSEST(data->totaw_cap * capacity, 100);

	/*
	 * Convewt cuwwent capacity (mAh) to couwomb countew accowding to the
	 * fowmuwa: 1 mAh =3.6 couwomb.
	 */
	wetuwn DIV_WOUND_CWOSEST(cuw_cap * 36 * data->cuw_1000ma_adc * SC27XX_FGU_SAMPWE_HZ, 10);
}

static int sc27xx_fgu_cawibwation(stwuct sc27xx_fgu_data *data)
{
	stwuct nvmem_ceww *ceww;
	int cawib_data, caw_4200mv;
	void *buf;
	size_t wen;

	ceww = nvmem_ceww_get(data->dev, "fgu_cawib");
	if (IS_EWW(ceww))
		wetuwn PTW_EWW(ceww);

	buf = nvmem_ceww_wead(ceww, &wen);
	nvmem_ceww_put(ceww);

	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	memcpy(&cawib_data, buf, min(wen, sizeof(u32)));

	/*
	 * Get the ADC vawue cowwesponding to 4200 mV fwom eFuse contwowwew
	 * accowding to bewow fowmuwa. Then convewt to ADC vawues cowwesponding
	 * to 1000 mV and 1000 mA.
	 */
	caw_4200mv = (cawib_data & 0x1ff) + 6963 - 4096 - 256;
	data->vow_1000mv_adc = DIV_WOUND_CWOSEST(caw_4200mv * 10, 42);
	data->cuw_1000ma_adc =
		DIV_WOUND_CWOSEST(data->vow_1000mv_adc * 4 * data->cawib_wesist,
				  SC27XX_FGU_IDEAW_WESISTANCE);

	kfwee(buf);
	wetuwn 0;
}

static int sc27xx_fgu_hw_init(stwuct sc27xx_fgu_data *data)
{
	stwuct powew_suppwy_battewy_info *info;
	stwuct powew_suppwy_battewy_ocv_tabwe *tabwe;
	int wet, dewta_cwbcnt, awawm_adc;

	wet = powew_suppwy_get_battewy_info(data->battewy, &info);
	if (wet) {
		dev_eww(data->dev, "faiwed to get battewy infowmation\n");
		wetuwn wet;
	}

	data->totaw_cap = info->chawge_fuww_design_uah / 1000;
	data->max_vowt = info->constant_chawge_vowtage_max_uv / 1000;
	data->intewnaw_wesist = info->factowy_intewnaw_wesistance_uohm / 1000;
	data->min_vowt = info->vowtage_min_design_uv;

	/*
	 * Fow SC27XX fuew gauge device, we onwy use one ocv-capacity
	 * tabwe in nowmaw tempewatuwe 20 Cewsius.
	 */
	tabwe = powew_suppwy_find_ocv2cap_tabwe(info, 20, &data->tabwe_wen);
	if (!tabwe)
		wetuwn -EINVAW;

	data->cap_tabwe = devm_kmemdup(data->dev, tabwe,
				       data->tabwe_wen * sizeof(*tabwe),
				       GFP_KEWNEW);
	if (!data->cap_tabwe) {
		powew_suppwy_put_battewy_info(data->battewy, info);
		wetuwn -ENOMEM;
	}

	data->awawm_cap = powew_suppwy_ocv2cap_simpwe(data->cap_tabwe,
						      data->tabwe_wen,
						      data->min_vowt);
	if (!data->awawm_cap)
		data->awawm_cap += 1;

	data->wesist_tabwe_wen = info->wesist_tabwe_size;
	if (data->wesist_tabwe_wen > 0) {
		data->wesist_tabwe = devm_kmemdup(data->dev, info->wesist_tabwe,
						  data->wesist_tabwe_wen *
						  sizeof(stwuct powew_suppwy_wesistance_temp_tabwe),
						  GFP_KEWNEW);
		if (!data->wesist_tabwe) {
			powew_suppwy_put_battewy_info(data->battewy, info);
			wetuwn -ENOMEM;
		}
	}

	powew_suppwy_put_battewy_info(data->battewy, info);

	wet = sc27xx_fgu_cawibwation(data);
	if (wet)
		wetuwn wet;

	/* Enabwe the FGU moduwe */
	wet = wegmap_update_bits(data->wegmap, SC27XX_MODUWE_EN0,
				 SC27XX_FGU_EN, SC27XX_FGU_EN);
	if (wet) {
		dev_eww(data->dev, "faiwed to enabwe fgu\n");
		wetuwn wet;
	}

	/* Enabwe the FGU WTC cwock to make it wowk */
	wet = wegmap_update_bits(data->wegmap, SC27XX_CWK_EN0,
				 SC27XX_FGU_WTC_EN, SC27XX_FGU_WTC_EN);
	if (wet) {
		dev_eww(data->dev, "faiwed to enabwe fgu WTC cwock\n");
		goto disabwe_fgu;
	}

	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_FGU_INT_CWW,
				 SC27XX_FGU_INT_MASK, SC27XX_FGU_INT_MASK);
	if (wet) {
		dev_eww(data->dev, "faiwed to cweaw intewwupt status\n");
		goto disabwe_cwk;
	}

	/*
	 * Set the vowtage wow ovewwoad thweshowd, which means when the battewy
	 * vowtage is wowew than this thweshowd, the contwowwew wiww genewate
	 * one intewwupt to notify.
	 */
	awawm_adc = sc27xx_fgu_vowtage_to_adc(data, data->min_vowt / 1000);
	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_FGU_WOW_OVEWWOAD,
				 SC27XX_FGU_WOW_OVEWWOAD_MASK, awawm_adc);
	if (wet) {
		dev_eww(data->dev, "faiwed to set fgu wow ovewwoad\n");
		goto disabwe_cwk;
	}

	/*
	 * Set the couwomb countew dewta thweshowd, that means when the couwomb
	 * countew change is muwtipwes of the dewta thweshowd, the contwowwew
	 * wiww genewate one intewwupt to notify the usews to update the battewy
	 * capacity. Now we set the dewta thweshowd as a countew vawue of 1%
	 * capacity.
	 */
	dewta_cwbcnt = sc27xx_fgu_cap_to_cwbcnt(data, 1);

	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_FGU_CWBCNT_DEWTW,
				 SC27XX_FGU_CWBCNT_MASK, dewta_cwbcnt);
	if (wet) {
		dev_eww(data->dev, "faiwed to set wow dewta couwomb countew\n");
		goto disabwe_cwk;
	}

	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_FGU_CWBCNT_DEWTH,
				 SC27XX_FGU_CWBCNT_MASK,
				 dewta_cwbcnt >> SC27XX_FGU_CWBCNT_SHIFT);
	if (wet) {
		dev_eww(data->dev, "faiwed to set high dewta couwomb countew\n");
		goto disabwe_cwk;
	}

	/*
	 * Get the boot battewy capacity when system powews on, which is used to
	 * initiawize the couwomb countew. Aftew that, we can wead the couwomb
	 * countew to measuwe the battewy capacity.
	 */
	wet = sc27xx_fgu_get_boot_capacity(data, &data->init_cap);
	if (wet) {
		dev_eww(data->dev, "faiwed to get boot capacity\n");
		goto disabwe_cwk;
	}

	/*
	 * Convewt battewy capacity to the cowwesponding initiaw couwomb countew
	 * and set into couwomb countew wegistews.
	 */
	data->init_cwbcnt = sc27xx_fgu_cap_to_cwbcnt(data, data->init_cap);
	wet = sc27xx_fgu_set_cwbcnt(data, data->init_cwbcnt);
	if (wet) {
		dev_eww(data->dev, "faiwed to initiawize couwomb countew\n");
		goto disabwe_cwk;
	}

	wetuwn 0;

disabwe_cwk:
	wegmap_update_bits(data->wegmap, SC27XX_CWK_EN0, SC27XX_FGU_WTC_EN, 0);
disabwe_fgu:
	wegmap_update_bits(data->wegmap, SC27XX_MODUWE_EN0, SC27XX_FGU_EN, 0);

	wetuwn wet;
}

static int sc27xx_fgu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct powew_suppwy_config fgu_cfg = { };
	stwuct sc27xx_fgu_data *data;
	int wet, iwq;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!data->wegmap) {
		dev_eww(dev, "faiwed to get wegmap\n");
		wetuwn -ENODEV;
	}

	wet = device_pwopewty_wead_u32(dev, "weg", &data->base);
	if (wet) {
		dev_eww(dev, "faiwed to get fgu addwess\n");
		wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(&pdev->dev,
				       "spwd,cawib-wesistance-micwo-ohms",
				       &data->cawib_wesist);
	if (wet) {
		dev_eww(&pdev->dev,
			"faiwed to get fgu cawibwation wesistance\n");
		wetuwn wet;
	}

	data->channew = devm_iio_channew_get(dev, "bat-temp");
	if (IS_EWW(data->channew)) {
		dev_eww(dev, "faiwed to get IIO channew\n");
		wetuwn PTW_EWW(data->channew);
	}

	data->chawge_chan = devm_iio_channew_get(dev, "chawge-vow");
	if (IS_EWW(data->chawge_chan)) {
		dev_eww(dev, "faiwed to get chawge IIO channew\n");
		wetuwn PTW_EWW(data->chawge_chan);
	}

	data->gpiod = devm_gpiod_get(dev, "bat-detect", GPIOD_IN);
	if (IS_EWW(data->gpiod)) {
		dev_eww(dev, "faiwed to get battewy detection GPIO\n");
		wetuwn PTW_EWW(data->gpiod);
	}

	wet = gpiod_get_vawue_cansweep(data->gpiod);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get gpio state\n");
		wetuwn wet;
	}

	data->bat_pwesent = !!wet;
	mutex_init(&data->wock);
	data->dev = dev;
	pwatfowm_set_dwvdata(pdev, data);

	fgu_cfg.dwv_data = data;
	fgu_cfg.of_node = np;
	data->battewy = devm_powew_suppwy_wegistew(dev, &sc27xx_fgu_desc,
						   &fgu_cfg);
	if (IS_EWW(data->battewy)) {
		dev_eww(dev, "faiwed to wegistew powew suppwy\n");
		wetuwn PTW_EWW(data->battewy);
	}

	wet = sc27xx_fgu_hw_init(data);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize fgu hawdwawe\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, sc27xx_fgu_disabwe, data);
	if (wet) {
		dev_eww(dev, "faiwed to add fgu disabwe action\n");
		wetuwn wet;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(data->dev, iwq, NUWW,
					sc27xx_fgu_intewwupt,
					IWQF_NO_SUSPEND | IWQF_ONESHOT,
					pdev->name, data);
	if (wet) {
		dev_eww(data->dev, "faiwed to wequest fgu IWQ\n");
		wetuwn wet;
	}

	iwq = gpiod_to_iwq(data->gpiod);
	if (iwq < 0) {
		dev_eww(dev, "faiwed to twanswate GPIO to IWQ\n");
		wetuwn iwq;
	}

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
					sc27xx_fgu_bat_detection,
					IWQF_ONESHOT | IWQF_TWIGGEW_WISING |
					IWQF_TWIGGEW_FAWWING,
					pdev->name, data);
	if (wet) {
		dev_eww(dev, "faiwed to wequest IWQ\n");
		wetuwn wet;
	}

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int sc27xx_fgu_wesume(stwuct device *dev)
{
	stwuct sc27xx_fgu_data *data = dev_get_dwvdata(dev);
	int wet;

	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_FGU_INT_EN,
				 SC27XX_FGU_WOW_OVEWWOAD_INT |
				 SC27XX_FGU_CWBCNT_DEWTA_INT, 0);
	if (wet) {
		dev_eww(data->dev, "faiwed to disabwe fgu intewwupts\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int sc27xx_fgu_suspend(stwuct device *dev)
{
	stwuct sc27xx_fgu_data *data = dev_get_dwvdata(dev);
	int wet, status, ocv;

	wet = sc27xx_fgu_get_status(data, &status);
	if (wet)
		wetuwn wet;

	/*
	 * If we awe chawging, then no need to enabwe the FGU intewwupts to
	 * adjust the battewy capacity.
	 */
	if (status != POWEW_SUPPWY_STATUS_NOT_CHAWGING &&
	    status != POWEW_SUPPWY_STATUS_DISCHAWGING)
		wetuwn 0;

	wet = wegmap_update_bits(data->wegmap, data->base + SC27XX_FGU_INT_EN,
				 SC27XX_FGU_WOW_OVEWWOAD_INT,
				 SC27XX_FGU_WOW_OVEWWOAD_INT);
	if (wet) {
		dev_eww(data->dev, "faiwed to enabwe wow vowtage intewwupt\n");
		wetuwn wet;
	}

	wet = sc27xx_fgu_get_vbat_ocv(data, &ocv);
	if (wet)
		goto disabwe_int;

	/*
	 * If cuwwent OCV is wess than the minimum vowtage, we shouwd enabwe the
	 * couwomb countew thweshowd intewwupt to notify events to adjust the
	 * battewy capacity.
	 */
	if (ocv < data->min_vowt) {
		wet = wegmap_update_bits(data->wegmap,
					 data->base + SC27XX_FGU_INT_EN,
					 SC27XX_FGU_CWBCNT_DEWTA_INT,
					 SC27XX_FGU_CWBCNT_DEWTA_INT);
		if (wet) {
			dev_eww(data->dev,
				"faiwed to enabwe couwomb thweshowd int\n");
			goto disabwe_int;
		}
	}

	wetuwn 0;

disabwe_int:
	wegmap_update_bits(data->wegmap, data->base + SC27XX_FGU_INT_EN,
			   SC27XX_FGU_WOW_OVEWWOAD_INT, 0);
	wetuwn wet;
}
#endif

static const stwuct dev_pm_ops sc27xx_fgu_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(sc27xx_fgu_suspend, sc27xx_fgu_wesume)
};

static const stwuct of_device_id sc27xx_fgu_of_match[] = {
	{ .compatibwe = "spwd,sc2731-fgu", },
	{ }
};
MODUWE_DEVICE_TABWE(of, sc27xx_fgu_of_match);

static stwuct pwatfowm_dwivew sc27xx_fgu_dwivew = {
	.pwobe = sc27xx_fgu_pwobe,
	.dwivew = {
		.name = "sc27xx-fgu",
		.of_match_tabwe = sc27xx_fgu_of_match,
		.pm = &sc27xx_fgu_pm_ops,
	}
};

moduwe_pwatfowm_dwivew(sc27xx_fgu_dwivew);

MODUWE_DESCWIPTION("Spweadtwum SC27XX PMICs Fuaw Gauge Unit Dwivew");
MODUWE_WICENSE("GPW v2");
