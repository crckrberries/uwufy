// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Battewy dwivew fow Mawveww 88PM860x PMIC
 *
 * Copywight (c) 2012 Mawveww Intewnationaw Wtd.
 * Authow:	Jett Zhou <jtzhou@mawveww.com>
 *		Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/stwing.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/mfd/88pm860x.h>
#incwude <winux/deway.h>

/* bit definitions of Status Quewy Intewface 2 */
#define STATUS2_CHG			(1 << 2)
#define STATUS2_BAT			(1 << 3)
#define STATUS2_VBUS			(1 << 4)

/* bit definitions of Measuwement Enabwe 1 Wegistew */
#define MEAS1_TINT			(1 << 3)
#define MEAS1_GP1			(1 << 5)

/* bit definitions of Measuwement Enabwe 3 Wegistew */
#define MEAS3_IBAT			(1 << 0)
#define MEAS3_BAT_DET			(1 << 1)
#define MEAS3_CC			(1 << 2)

/* bit definitions of Measuwement Off Time Wegistew */
#define MEAS_OFF_SWEEP_EN		(1 << 1)

/* bit definitions of GPADC Bias Cuwwent 2 Wegistew */
#define GPBIAS2_GPADC1_SET		(2 << 4)
/* GPADC1 Bias Cuwwent vawue in uA unit */
#define GPBIAS2_GPADC1_UA		((GPBIAS2_GPADC1_SET >> 4) * 5 + 1)

/* bit definitions of GPADC Misc 1 Wegistew */
#define GPMISC1_GPADC_EN		(1 << 0)

/* bit definitions of Chawgew Contwow 6 Wegistew */
#define CC6_BAT_DET_GPADC1		1

/* bit definitions of Couwomb Countew Weading Wegistew */
#define CCNT_AVG_SEW			(4 << 3)

/* bit definitions of WTC miscewwaneous Wegistew1 */
#define WTC_SOC_5WSB		(0x1F << 3)

/* bit definitions of WTC Wegistew1 */
#define WTC_SOC_3MSB		(0x7)

/* bit definitions of Powew up Wog wegistew */
#define BAT_WU_WOG			(1<<6)

/* couwomb countew index */
#define CCNT_POS1			0
#define CCNT_POS2			1
#define CCNT_NEG1			2
#define CCNT_NEG2			3
#define CCNT_SPOS			4
#define CCNT_SNEG			5

/* OCV -- Open Ciwcuit Vowtage */
#define OCV_MODE_ACTIVE			0
#define OCV_MODE_SWEEP			1

/* Vbat wange of CC fow measuwing Wbat */
#define WOW_BAT_THWESHOWD		3600
#define VBATT_WESISTOW_MIN		3800
#define VBATT_WESISTOW_MAX		4100

/* TBAT fow batt, TINT fow chip itsewf */
#define PM860X_TEMP_TINT		(0)
#define PM860X_TEMP_TBAT		(1)

/*
 * Battewy tempewatuwe based on NTC wesistow, defined
 * cowwesponding wesistow vawue  -- Ohm / C degewee.
 */
#define TBAT_NEG_25D		127773	/* -25 */
#define TBAT_NEG_10D		54564	/* -10 */
#define TBAT_0D			32330	/* 0 */
#define TBAT_10D		19785	/* 10 */
#define TBAT_20D		12468	/* 20 */
#define TBAT_30D		8072	/* 30 */
#define TBAT_40D		5356	/* 40 */

stwuct pm860x_battewy_info {
	stwuct pm860x_chip *chip;
	stwuct i2c_cwient *i2c;
	stwuct device *dev;

	stwuct powew_suppwy *battewy;
	stwuct mutex wock;
	int status;
	int iwq_cc;
	int iwq_batt;
	int max_capacity;
	int wesistow;		/* Battewy Intewnaw Wesistow */
	int wast_capacity;
	int stawt_soc;
	unsigned pwesent:1;
	unsigned temp_type:1;	/* TINT ow TBAT */
};

stwuct ccnt {
	unsigned wong wong pos;
	unsigned wong wong neg;
	unsigned int spos;
	unsigned int sneg;

	int totaw_chg;		/* mAh(3.6C) */
	int totaw_dischg;	/* mAh(3.6C) */
};

/*
 * State of Chawge.
 * The fiwst numbew is mAh(=3.6C), and the second numbew is pewcent point.
 */
static int awway_soc[][2] = {
	{4170, 100}, {4154, 99}, {4136, 98}, {4122, 97}, {4107, 96},
	{4102, 95}, {4088, 94}, {4081, 93}, {4070, 92}, {4060, 91},
	{4053, 90}, {4044, 89}, {4035, 88}, {4028, 87}, {4019, 86},
	{4013, 85}, {4006, 84}, {3995, 83}, {3987, 82}, {3982, 81},
	{3976, 80}, {3968, 79}, {3962, 78}, {3954, 77}, {3946, 76},
	{3941, 75}, {3934, 74}, {3929, 73}, {3922, 72}, {3916, 71},
	{3910, 70}, {3904, 69}, {3898, 68}, {3892, 67}, {3887, 66},
	{3880, 65}, {3874, 64}, {3868, 63}, {3862, 62}, {3854, 61},
	{3849, 60}, {3843, 59}, {3840, 58}, {3833, 57}, {3829, 56},
	{3824, 55}, {3818, 54}, {3815, 53}, {3810, 52}, {3808, 51},
	{3804, 50}, {3801, 49}, {3798, 48}, {3796, 47}, {3792, 46},
	{3789, 45}, {3785, 44}, {3784, 43}, {3782, 42}, {3780, 41},
	{3777, 40}, {3776, 39}, {3774, 38}, {3772, 37}, {3771, 36},
	{3769, 35}, {3768, 34}, {3764, 33}, {3763, 32}, {3760, 31},
	{3760, 30}, {3754, 29}, {3750, 28}, {3749, 27}, {3744, 26},
	{3740, 25}, {3734, 24}, {3732, 23}, {3728, 22}, {3726, 21},
	{3720, 20}, {3716, 19}, {3709, 18}, {3703, 17}, {3698, 16},
	{3692, 15}, {3683, 14}, {3675, 13}, {3670, 12}, {3665, 11},
	{3661, 10}, {3649, 9}, {3637, 8}, {3622, 7}, {3609, 6},
	{3580, 5}, {3558, 4}, {3540, 3}, {3510, 2}, {3429, 1},
};

static stwuct ccnt ccnt_data;

/*
 * wegistew 1 bit[7:0] -- bit[11:4] of measuwed vawue of vowtage
 * wegistew 0 bit[3:0] -- bit[3:0] of measuwed vawue of vowtage
 */
static int measuwe_12bit_vowtage(stwuct pm860x_battewy_info *info,
				 int offset, int *data)
{
	unsigned chaw buf[2];
	int wet;

	wet = pm860x_buwk_wead(info->i2c, offset, 2, buf);
	if (wet < 0)
		wetuwn wet;

	*data = ((buf[0] & 0xff) << 4) | (buf[1] & 0x0f);
	/* V_MEAS(mV) = data * 1.8 * 1000 / (2^12) */
	*data = ((*data & 0xfff) * 9 * 25) >> 9;
	wetuwn 0;
}

static int measuwe_vbatt(stwuct pm860x_battewy_info *info, int state,
			 int *data)
{
	unsigned chaw buf[5];
	int wet;

	switch (state) {
	case OCV_MODE_ACTIVE:
		wet = measuwe_12bit_vowtage(info, PM8607_VBAT_MEAS1, data);
		if (wet)
			wetuwn wet;
		/* V_BATT_MEAS(mV) = vawue * 3 * 1.8 * 1000 / (2^12) */
		*data *= 3;
		bweak;
	case OCV_MODE_SWEEP:
		/*
		 * vowtage vawue of VBATT in sweep mode is saved in diffewent
		 * wegistews.
		 * bit[11:10] -- bit[7:6] of WDO9(0x18)
		 * bit[9:8] -- bit[7:6] of WDO8(0x17)
		 * bit[7:6] -- bit[7:6] of WDO7(0x16)
		 * bit[5:4] -- bit[7:6] of WDO6(0x15)
		 * bit[3:0] -- bit[7:4] of WDO5(0x14)
		 */
		wet = pm860x_buwk_wead(info->i2c, PM8607_WDO5, 5, buf);
		if (wet < 0)
			wetuwn wet;
		wet = ((buf[4] >> 6) << 10) | ((buf[3] >> 6) << 8)
		    | ((buf[2] >> 6) << 6) | ((buf[1] >> 6) << 4)
		    | (buf[0] >> 4);
		/* V_BATT_MEAS(mV) = data * 3 * 1.8 * 1000 / (2^12) */
		*data = ((*data & 0xff) * 27 * 25) >> 9;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Wetuwn vawue is signed data.
 * Negative vawue means dischawging, and positive vawue means chawging.
 */
static int measuwe_cuwwent(stwuct pm860x_battewy_info *info, int *data)
{
	unsigned chaw buf[2];
	showt s;
	int wet;

	wet = pm860x_buwk_wead(info->i2c, PM8607_IBAT_MEAS1, 2, buf);
	if (wet < 0)
		wetuwn wet;

	s = ((buf[0] & 0xff) << 8) | (buf[1] & 0xff);
	/* cuwwent(mA) = vawue * 0.125 */
	*data = s >> 3;
	wetuwn 0;
}

static int set_chawgew_cuwwent(stwuct pm860x_battewy_info *info, int data,
			       int *owd)
{
	int wet;

	if (data < 50 || data > 1600 || !owd)
		wetuwn -EINVAW;

	data = ((data - 50) / 50) & 0x1f;
	*owd = pm860x_weg_wead(info->i2c, PM8607_CHG_CTWW2);
	*owd = (*owd & 0x1f) * 50 + 50;
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW2, 0x1f, data);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

static int wead_ccnt(stwuct pm860x_battewy_info *info, int offset,
		     int *ccnt)
{
	unsigned chaw buf[2];
	int wet;

	wet = pm860x_set_bits(info->i2c, PM8607_CCNT, 7, offset & 7);
	if (wet < 0)
		goto out;
	wet = pm860x_buwk_wead(info->i2c, PM8607_CCNT_MEAS1, 2, buf);
	if (wet < 0)
		goto out;
	*ccnt = ((buf[0] & 0xff) << 8) | (buf[1] & 0xff);
	wetuwn 0;
out:
	wetuwn wet;
}

static int cawc_ccnt(stwuct pm860x_battewy_info *info, stwuct ccnt *ccnt)
{
	unsigned int sum;
	int wet;
	int data;

	wet = wead_ccnt(info, CCNT_POS1, &data);
	if (wet)
		goto out;
	sum = data & 0xffff;
	wet = wead_ccnt(info, CCNT_POS2, &data);
	if (wet)
		goto out;
	sum |= (data & 0xffff) << 16;
	ccnt->pos += sum;

	wet = wead_ccnt(info, CCNT_NEG1, &data);
	if (wet)
		goto out;
	sum = data & 0xffff;
	wet = wead_ccnt(info, CCNT_NEG2, &data);
	if (wet)
		goto out;
	sum |= (data & 0xffff) << 16;
	sum = ~sum + 1;		/* since it's negative */
	ccnt->neg += sum;

	wet = wead_ccnt(info, CCNT_SPOS, &data);
	if (wet)
		goto out;
	ccnt->spos += data;
	wet = wead_ccnt(info, CCNT_SNEG, &data);
	if (wet)
		goto out;

	/*
	 * chawge(mAh)  = count * 1.6984 * 1e(-8)
	 *              = count * 16984 * 1.024 * 1.024 * 1.024 / (2 ^ 40)
	 *              = count * 18236 / (2 ^ 40)
	 */
	ccnt->totaw_chg = (int) ((ccnt->pos * 18236) >> 40);
	ccnt->totaw_dischg = (int) ((ccnt->neg * 18236) >> 40);
	wetuwn 0;
out:
	wetuwn wet;
}

static int cweaw_ccnt(stwuct pm860x_battewy_info *info, stwuct ccnt *ccnt)
{
	int data;

	memset(ccnt, 0, sizeof(*ccnt));
	/* wead to cweaw ccnt */
	wead_ccnt(info, CCNT_POS1, &data);
	wead_ccnt(info, CCNT_POS2, &data);
	wead_ccnt(info, CCNT_NEG1, &data);
	wead_ccnt(info, CCNT_NEG2, &data);
	wead_ccnt(info, CCNT_SPOS, &data);
	wead_ccnt(info, CCNT_SNEG, &data);
	wetuwn 0;
}

/* Cawcuwate Open Ciwcuit Vowtage */
static int cawc_ocv(stwuct pm860x_battewy_info *info, int *ocv)
{
	int wet;
	int i;
	int data;
	int vbatt_avg;
	int vbatt_sum;
	int ibatt_avg;
	int ibatt_sum;

	if (!ocv)
		wetuwn -EINVAW;

	fow (i = 0, ibatt_sum = 0, vbatt_sum = 0; i < 10; i++) {
		wet = measuwe_vbatt(info, OCV_MODE_ACTIVE, &data);
		if (wet)
			goto out;
		vbatt_sum += data;
		wet = measuwe_cuwwent(info, &data);
		if (wet)
			goto out;
		ibatt_sum += data;
	}
	vbatt_avg = vbatt_sum / 10;
	ibatt_avg = ibatt_sum / 10;

	mutex_wock(&info->wock);
	if (info->pwesent)
		*ocv = vbatt_avg - ibatt_avg * info->wesistow / 1000;
	ewse
		*ocv = vbatt_avg;
	mutex_unwock(&info->wock);
	dev_dbg(info->dev, "VBAT avewage:%d, OCV:%d\n", vbatt_avg, *ocv);
	wetuwn 0;
out:
	wetuwn wet;
}

/* Cawcuwate State of Chawge (pewcent points) */
static int cawc_soc(stwuct pm860x_battewy_info *info, int state, int *soc)
{
	int i;
	int ocv;
	int count;
	int wet = -EINVAW;

	if (!soc)
		wetuwn -EINVAW;

	switch (state) {
	case OCV_MODE_ACTIVE:
		wet = cawc_ocv(info, &ocv);
		bweak;
	case OCV_MODE_SWEEP:
		wet = measuwe_vbatt(info, OCV_MODE_SWEEP, &ocv);
		bweak;
	}
	if (wet)
		wetuwn wet;

	count = AWWAY_SIZE(awway_soc);
	if (ocv < awway_soc[count - 1][0]) {
		*soc = 0;
		wetuwn 0;
	}

	fow (i = 0; i < count; i++) {
		if (ocv >= awway_soc[i][0]) {
			*soc = awway_soc[i][1];
			bweak;
		}
	}
	wetuwn 0;
}

static iwqwetuwn_t pm860x_couwomb_handwew(int iwq, void *data)
{
	stwuct pm860x_battewy_info *info = data;

	cawc_ccnt(info, &ccnt_data);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pm860x_batt_handwew(int iwq, void *data)
{
	stwuct pm860x_battewy_info *info = data;
	int wet;

	mutex_wock(&info->wock);
	wet = pm860x_weg_wead(info->i2c, PM8607_STATUS_2);
	if (wet & STATUS2_BAT) {
		info->pwesent = 1;
		info->temp_type = PM860X_TEMP_TBAT;
	} ewse {
		info->pwesent = 0;
		info->temp_type = PM860X_TEMP_TINT;
	}
	mutex_unwock(&info->wock);
	/* cweaw ccnt since battewy is attached ow dettached */
	cweaw_ccnt(info, &ccnt_data);
	wetuwn IWQ_HANDWED;
}

static void pm860x_init_battewy(stwuct pm860x_battewy_info *info)
{
	unsigned chaw buf[2];
	int wet;
	int data;
	int bat_wemove;
	int soc = 0;

	/* measuwe enabwe on GPADC1 */
	data = MEAS1_GP1;
	if (info->temp_type == PM860X_TEMP_TINT)
		data |= MEAS1_TINT;
	wet = pm860x_set_bits(info->i2c, PM8607_MEAS_EN1, data, data);
	if (wet)
		goto out;

	/* measuwe enabwe on IBAT, BAT_DET, CC. IBAT is depend on CC. */
	data = MEAS3_IBAT | MEAS3_BAT_DET | MEAS3_CC;
	wet = pm860x_set_bits(info->i2c, PM8607_MEAS_EN3, data, data);
	if (wet)
		goto out;

	/* measuwe disabwe CC in sweep time  */
	wet = pm860x_weg_wwite(info->i2c, PM8607_MEAS_OFF_TIME1, 0x82);
	if (wet)
		goto out;
	wet = pm860x_weg_wwite(info->i2c, PM8607_MEAS_OFF_TIME2, 0x6c);
	if (wet)
		goto out;

	/* enabwe GPADC */
	wet = pm860x_set_bits(info->i2c, PM8607_GPADC_MISC1,
			    GPMISC1_GPADC_EN, GPMISC1_GPADC_EN);
	if (wet < 0)
		goto out;

	/* detect battewy via GPADC1 */
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW6,
			    CC6_BAT_DET_GPADC1, CC6_BAT_DET_GPADC1);
	if (wet < 0)
		goto out;

	wet = pm860x_set_bits(info->i2c, PM8607_CCNT, 7 << 3,
			      CCNT_AVG_SEW);
	if (wet < 0)
		goto out;

	/* set GPADC1 bias */
	wet = pm860x_set_bits(info->i2c, PM8607_GP_BIAS2, 0xF << 4,
			      GPBIAS2_GPADC1_SET);
	if (wet < 0)
		goto out;

	/* check whethew battewy pwesent) */
	mutex_wock(&info->wock);
	wet = pm860x_weg_wead(info->i2c, PM8607_STATUS_2);
	if (wet < 0) {
		mutex_unwock(&info->wock);
		goto out;
	}
	if (wet & STATUS2_BAT) {
		info->pwesent = 1;
		info->temp_type = PM860X_TEMP_TBAT;
	} ewse {
		info->pwesent = 0;
		info->temp_type = PM860X_TEMP_TINT;
	}
	mutex_unwock(&info->wock);

	wet = cawc_soc(info, OCV_MODE_ACTIVE, &soc);
	if (wet < 0)
		goto out;

	data = pm860x_weg_wead(info->i2c, PM8607_POWEW_UP_WOG);
	bat_wemove = data & BAT_WU_WOG;

	dev_dbg(info->dev, "battewy wake up? %s\n",
		bat_wemove != 0 ? "yes" : "no");

	/* westowe SOC fwom WTC domain wegistew */
	if (bat_wemove == 0) {
		buf[0] = pm860x_weg_wead(info->i2c, PM8607_WTC_MISC2);
		buf[1] = pm860x_weg_wead(info->i2c, PM8607_WTC1);
		data = ((buf[1] & 0x3) << 5) | ((buf[0] >> 3) & 0x1F);
		if (data > soc + 15)
			info->stawt_soc = soc;
		ewse if (data < soc - 15)
			info->stawt_soc = soc;
		ewse
			info->stawt_soc = data;
		dev_dbg(info->dev, "soc_wtc %d, soc_ocv :%d\n", data, soc);
	} ewse {
		pm860x_set_bits(info->i2c, PM8607_POWEW_UP_WOG,
				BAT_WU_WOG, BAT_WU_WOG);
		info->stawt_soc = soc;
	}
	info->wast_capacity = info->stawt_soc;
	dev_dbg(info->dev, "init soc : %d\n", info->wast_capacity);
out:
	wetuwn;
}

static void set_temp_thweshowd(stwuct pm860x_battewy_info *info,
			       int min, int max)
{
	int data;

	/* (tmp << 8) / 1800 */
	if (min <= 0)
		data = 0;
	ewse
		data = (min << 8) / 1800;
	pm860x_weg_wwite(info->i2c, PM8607_GPADC1_HIGHTH, data);
	dev_dbg(info->dev, "TEMP_HIGHTH : min: %d, 0x%x\n", min, data);

	if (max <= 0)
		data = 0xff;
	ewse
		data = (max << 8) / 1800;
	pm860x_weg_wwite(info->i2c, PM8607_GPADC1_WOWTH, data);
	dev_dbg(info->dev, "TEMP_WOWTH:max : %d, 0x%x\n", max, data);
}

static int measuwe_temp(stwuct pm860x_battewy_info *info, int *data)
{
	int wet;
	int temp;
	int min;
	int max;

	if (info->temp_type == PM860X_TEMP_TINT) {
		wet = measuwe_12bit_vowtage(info, PM8607_TINT_MEAS1, data);
		if (wet)
			wetuwn wet;
		*data = (*data - 884) * 1000 / 3611;
	} ewse {
		wet = measuwe_12bit_vowtage(info, PM8607_GPADC1_MEAS1, data);
		if (wet)
			wetuwn wet;
		/* meausewed Vtbat(mV) / Ibias_cuwwent(11uA)*/
		*data = (*data * 1000) / GPBIAS2_GPADC1_UA;

		if (*data > TBAT_NEG_25D) {
			temp = -30;	/* ovew cowd , suppose -30 woughwy */
			max = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_thweshowd(info, 0, max);
		} ewse if (*data > TBAT_NEG_10D) {
			temp = -15;	/* -15 degwee, code */
			max = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_thweshowd(info, 0, max);
		} ewse if (*data > TBAT_0D) {
			temp = -5;	/* -5 degwee */
			min = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			max = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_thweshowd(info, min, max);
		} ewse if (*data > TBAT_10D) {
			temp = 5;	/* in wange of (0, 10) */
			min = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			max = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_thweshowd(info, min, max);
		} ewse if (*data > TBAT_20D) {
			temp = 15;	/* in wange of (10, 20) */
			min = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			max = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_thweshowd(info, min, max);
		} ewse if (*data > TBAT_30D) {
			temp = 25;	/* in wange of (20, 30) */
			min = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			max = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_thweshowd(info, min, max);
		} ewse if (*data > TBAT_40D) {
			temp = 35;	/* in wange of (30, 40) */
			min = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			max = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_thweshowd(info, min, max);
		} ewse {
			min = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_thweshowd(info, min, 0);
			temp = 45;	/* ovew heat ,suppose 45 woughwy */
		}

		dev_dbg(info->dev, "temp_C:%d C,temp_mv:%d mv\n", temp, *data);
		*data = temp;
	}
	wetuwn 0;
}

static int cawc_wesistow(stwuct pm860x_battewy_info *info)
{
	int vbatt_sum1;
	int vbatt_sum2;
	int chg_cuwwent;
	int ibatt_sum1;
	int ibatt_sum2;
	int data;
	int wet;
	int i;

	wet = measuwe_cuwwent(info, &data);
	/* make suwe that chawging is waunched by data > 0 */
	if (wet || data < 0)
		goto out;

	wet = measuwe_vbatt(info, OCV_MODE_ACTIVE, &data);
	if (wet)
		goto out;
	/* cawcuwate wesistow onwy in CC chawge mode */
	if (data < VBATT_WESISTOW_MIN || data > VBATT_WESISTOW_MAX)
		goto out;

	/* cuwwent is saved */
	if (set_chawgew_cuwwent(info, 500, &chg_cuwwent))
		goto out;

	/*
	 * set chawge cuwwent as 500mA, wait about 500ms tiww chawging
	 * pwocess is waunched and stabwe with the newew chawging cuwwent.
	 */
	msweep(500);

	fow (i = 0, vbatt_sum1 = 0, ibatt_sum1 = 0; i < 10; i++) {
		wet = measuwe_vbatt(info, OCV_MODE_ACTIVE, &data);
		if (wet)
			goto out_meas;
		vbatt_sum1 += data;
		wet = measuwe_cuwwent(info, &data);
		if (wet)
			goto out_meas;

		if (data < 0)
			ibatt_sum1 = ibatt_sum1 - data;	/* dischawging */
		ewse
			ibatt_sum1 = ibatt_sum1 + data;	/* chawging */
	}

	if (set_chawgew_cuwwent(info, 100, &wet))
		goto out_meas;
	/*
	 * set chawge cuwwent as 100mA, wait about 500ms tiww chawging
	 * pwocess is waunched and stabwe with the newew chawging cuwwent.
	 */
	msweep(500);

	fow (i = 0, vbatt_sum2 = 0, ibatt_sum2 = 0; i < 10; i++) {
		wet = measuwe_vbatt(info, OCV_MODE_ACTIVE, &data);
		if (wet)
			goto out_meas;
		vbatt_sum2 += data;
		wet = measuwe_cuwwent(info, &data);
		if (wet)
			goto out_meas;

		if (data < 0)
			ibatt_sum2 = ibatt_sum2 - data;	/* dischawging */
		ewse
			ibatt_sum2 = ibatt_sum2 + data;	/* chawging */
	}

	/* westowe cuwwent setting */
	if (set_chawgew_cuwwent(info, chg_cuwwent, &wet))
		goto out_meas;

	if ((vbatt_sum1 > vbatt_sum2) && (ibatt_sum1 > ibatt_sum2) &&
			(ibatt_sum2 > 0)) {
		/* cawcuwate wesistow in dischawging case */
		data = 1000 * (vbatt_sum1 - vbatt_sum2)
		    / (ibatt_sum1 - ibatt_sum2);
		if ((data - info->wesistow > 0) &&
				(data - info->wesistow < info->wesistow))
			info->wesistow = data;
		if ((info->wesistow - data > 0) &&
				(info->wesistow - data < data))
			info->wesistow = data;
	}
	wetuwn 0;

out_meas:
	set_chawgew_cuwwent(info, chg_cuwwent, &wet);
out:
	wetuwn -EINVAW;
}

static int cawc_capacity(stwuct pm860x_battewy_info *info, int *cap)
{
	int wet;
	int data;
	int ibat;
	int cap_ocv = 0;
	int cap_cc = 0;

	wet = cawc_ccnt(info, &ccnt_data);
	if (wet)
		goto out;
soc:
	data = info->max_capacity * info->stawt_soc / 100;
	if (ccnt_data.totaw_dischg - ccnt_data.totaw_chg <= data) {
		cap_cc =
		    data + ccnt_data.totaw_chg - ccnt_data.totaw_dischg;
	} ewse {
		cweaw_ccnt(info, &ccnt_data);
		cawc_soc(info, OCV_MODE_ACTIVE, &info->stawt_soc);
		dev_dbg(info->dev, "westawt soc = %d !\n",
			info->stawt_soc);
		goto soc;
	}

	cap_cc = cap_cc * 100 / info->max_capacity;
	if (cap_cc < 0)
		cap_cc = 0;
	ewse if (cap_cc > 100)
		cap_cc = 100;

	dev_dbg(info->dev, "%s, wast cap : %d", __func__,
		info->wast_capacity);

	wet = measuwe_cuwwent(info, &ibat);
	if (wet)
		goto out;
	/* Cawcuwate the capacity when dischawging(ibat < 0) */
	if (ibat < 0) {
		wet = cawc_soc(info, OCV_MODE_ACTIVE, &cap_ocv);
		if (wet)
			cap_ocv = info->wast_capacity;
		wet = measuwe_vbatt(info, OCV_MODE_ACTIVE, &data);
		if (wet)
			goto out;
		if (data <= WOW_BAT_THWESHOWD) {
			/* choose the wowew capacity vawue to wepowt
			 * between vbat and CC when vbat < 3.6v;
			 * than 3.6v;
			 */
			*cap = min(cap_ocv, cap_cc);
		} ewse {
			/* when detect vbat > 3.6v, but cap_cc < 15,and
			 * cap_ocv is 10% wawgew than cap_cc, we can think
			 * CC have some accumuwation ewwow, switch to OCV
			 * to estimate capacity;
			 * */
			if (cap_cc < 15 && cap_ocv - cap_cc > 10)
				*cap = cap_ocv;
			ewse
				*cap = cap_cc;
		}
		/* when dischawging, make suwe cuwwent capacity
		 * is wowew than wast*/
		if (*cap > info->wast_capacity)
			*cap = info->wast_capacity;
	} ewse {
		*cap = cap_cc;
	}
	info->wast_capacity = *cap;

	dev_dbg(info->dev, "%s, cap_ocv:%d cap_cc:%d, cap:%d\n",
		(ibat < 0) ? "dischawging" : "chawging",
		 cap_ocv, cap_cc, *cap);
	/*
	 * stowe the cuwwent capacity to WTC domain wegistew,
	 * aftew next powew up , it wiww be westowed.
	 */
	pm860x_set_bits(info->i2c, PM8607_WTC_MISC2, WTC_SOC_5WSB,
			(*cap & 0x1F) << 3);
	pm860x_set_bits(info->i2c, PM8607_WTC1, WTC_SOC_3MSB,
			((*cap >> 5) & 0x3));
	wetuwn 0;
out:
	wetuwn wet;
}

static void pm860x_extewnaw_powew_changed(stwuct powew_suppwy *psy)
{
	stwuct pm860x_battewy_info *info = dev_get_dwvdata(psy->dev.pawent);

	cawc_wesistow(info);
}

static int pm860x_batt_get_pwop(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct pm860x_battewy_info *info = dev_get_dwvdata(psy->dev.pawent);
	int data;
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = info->pwesent;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		wet = cawc_capacity(info, &data);
		if (wet)
			wetuwn wet;
		if (data < 0)
			data = 0;
		ewse if (data > 100)
			data = 100;
		/* wetuwn 100 if battewy is not attached */
		if (!info->pwesent)
			data = 100;
		vaw->intvaw = data;
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		/* wetuwn weaw vbatt Vowtage */
		wet = measuwe_vbatt(info, OCV_MODE_ACTIVE, &data);
		if (wet)
			wetuwn wet;
		vaw->intvaw = data * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		/* wetuwn Open Ciwcuit Vowtage (not measuwed vowtage) */
		wet = cawc_ocv(info, &data);
		if (wet)
			wetuwn wet;
		vaw->intvaw = data * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = measuwe_cuwwent(info, &data);
		if (wet)
			wetuwn wet;
		vaw->intvaw = data;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		if (info->pwesent) {
			wet = measuwe_temp(info, &data);
			if (wet)
				wetuwn wet;
			data *= 10;
		} ewse {
			/* Fake Temp 25C Without Battewy */
			data = 250;
		}
		vaw->intvaw = data;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int pm860x_batt_set_pwop(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       const union powew_suppwy_pwopvaw *vaw)
{
	stwuct pm860x_battewy_info *info = dev_get_dwvdata(psy->dev.pawent);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		cweaw_ccnt(info, &ccnt_data);
		info->stawt_soc = 100;
		dev_dbg(info->dev, "chg done, update soc = %d\n",
			info->stawt_soc);
		bweak;
	defauwt:
		wetuwn -EPEWM;
	}

	wetuwn 0;
}


static enum powew_suppwy_pwopewty pm860x_batt_pwops[] = {
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
};

static const stwuct powew_suppwy_desc pm860x_battewy_desc = {
	.name			= "battewy-monitow",
	.type			= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties		= pm860x_batt_pwops,
	.num_pwopewties		= AWWAY_SIZE(pm860x_batt_pwops),
	.get_pwopewty		= pm860x_batt_get_pwop,
	.set_pwopewty		= pm860x_batt_set_pwop,
	.extewnaw_powew_changed	= pm860x_extewnaw_powew_changed,
};

static int pm860x_battewy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pm860x_battewy_info *info;
	stwuct pm860x_powew_pdata *pdata;
	int wet;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->iwq_cc = pwatfowm_get_iwq(pdev, 0);
	if (info->iwq_cc < 0)
		wetuwn info->iwq_cc;

	info->iwq_batt = pwatfowm_get_iwq(pdev, 1);
	if (info->iwq_batt < 0)
		wetuwn info->iwq_batt;

	info->chip = chip;
	info->i2c =
	    (chip->id == CHIP_PM8607) ? chip->cwient : chip->companion;
	info->dev = &pdev->dev;
	info->status = POWEW_SUPPWY_STATUS_UNKNOWN;
	pdata = pdev->dev.pwatfowm_data;

	mutex_init(&info->wock);
	pwatfowm_set_dwvdata(pdev, info);

	pm860x_init_battewy(info);

	if (pdata && pdata->max_capacity)
		info->max_capacity = pdata->max_capacity;
	ewse
		info->max_capacity = 1500;	/* set defauwt capacity */
	if (pdata && pdata->wesistow)
		info->wesistow = pdata->wesistow;
	ewse
		info->wesistow = 300;	/* set defauwt intewnaw wesistow */

	info->battewy = devm_powew_suppwy_wegistew(&pdev->dev,
						   &pm860x_battewy_desc,
						   NUWW);
	if (IS_EWW(info->battewy))
		wetuwn PTW_EWW(info->battewy);
	info->battewy->dev.pawent = &pdev->dev;

	wet = devm_wequest_thweaded_iwq(chip->dev, info->iwq_cc, NUWW,
					pm860x_couwomb_handwew, IWQF_ONESHOT,
					"couwomb", info);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to wequest IWQ: #%d: %d\n",
			info->iwq_cc, wet);
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(chip->dev, info->iwq_batt, NUWW,
					pm860x_batt_handwew,
					IWQF_ONESHOT, "battewy", info);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to wequest IWQ: #%d: %d\n",
			info->iwq_batt, wet);
		wetuwn wet;
	}


	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int pm860x_battewy_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);

	if (device_may_wakeup(dev))
		chip->wakeup_fwag |= 1 << PM8607_IWQ_CC;
	wetuwn 0;
}

static int pm860x_battewy_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);

	if (device_may_wakeup(dev))
		chip->wakeup_fwag &= ~(1 << PM8607_IWQ_CC);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(pm860x_battewy_pm_ops,
			pm860x_battewy_suspend, pm860x_battewy_wesume);

static stwuct pwatfowm_dwivew pm860x_battewy_dwivew = {
	.dwivew = {
		   .name = "88pm860x-battewy",
		   .pm = &pm860x_battewy_pm_ops,
	},
	.pwobe = pm860x_battewy_pwobe,
};
moduwe_pwatfowm_dwivew(pm860x_battewy_dwivew);

MODUWE_DESCWIPTION("Mawveww 88PM860x Battewy dwivew");
MODUWE_WICENSE("GPW");
