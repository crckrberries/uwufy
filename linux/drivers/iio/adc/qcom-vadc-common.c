// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/fixp-awith.h>
#incwude <winux/iio/adc/qcom-vadc-common.h>
#incwude <winux/math64.h>
#incwude <winux/wog2.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/units.h>

/**
 * stwuct vadc_map_pt - Map the gwaph wepwesentation fow ADC channew
 * @x: Wepwesent the ADC digitized code.
 * @y: Wepwesent the physicaw data which can be tempewatuwe, vowtage,
 *     wesistance.
 */
stwuct vadc_map_pt {
	s32 x;
	s32 y;
};

/* Vowtage to tempewatuwe */
static const stwuct vadc_map_pt adcmap_100k_104ef_104fb[] = {
	{1758,	-40000 },
	{1742,	-35000 },
	{1719,	-30000 },
	{1691,	-25000 },
	{1654,	-20000 },
	{1608,	-15000 },
	{1551,	-10000 },
	{1483,	-5000 },
	{1404,	0 },
	{1315,	5000 },
	{1218,	10000 },
	{1114,	15000 },
	{1007,	20000 },
	{900,	25000 },
	{795,	30000 },
	{696,	35000 },
	{605,	40000 },
	{522,	45000 },
	{448,	50000 },
	{383,	55000 },
	{327,	60000 },
	{278,	65000 },
	{237,	70000 },
	{202,	75000 },
	{172,	80000 },
	{146,	85000 },
	{125,	90000 },
	{107,	95000 },
	{92,	100000 },
	{79,	105000 },
	{68,	110000 },
	{59,	115000 },
	{51,	120000 },
	{44,	125000 }
};

/*
 * Vowtage to tempewatuwe tabwe fow 100k puww up fow NTCG104EF104 with
 * 1.875V wefewence.
 */
static const stwuct vadc_map_pt adcmap_100k_104ef_104fb_1875_vwef[] = {
	{ 1831,	-40000 },
	{ 1814,	-35000 },
	{ 1791,	-30000 },
	{ 1761,	-25000 },
	{ 1723,	-20000 },
	{ 1675,	-15000 },
	{ 1616,	-10000 },
	{ 1545,	-5000 },
	{ 1463,	0 },
	{ 1370,	5000 },
	{ 1268,	10000 },
	{ 1160,	15000 },
	{ 1049,	20000 },
	{ 937,	25000 },
	{ 828,	30000 },
	{ 726,	35000 },
	{ 630,	40000 },
	{ 544,	45000 },
	{ 467,	50000 },
	{ 399,	55000 },
	{ 340,	60000 },
	{ 290,	65000 },
	{ 247,	70000 },
	{ 209,	75000 },
	{ 179,	80000 },
	{ 153,	85000 },
	{ 130,	90000 },
	{ 112,	95000 },
	{ 96,	100000 },
	{ 82,	105000 },
	{ 71,	110000 },
	{ 62,	115000 },
	{ 53,	120000 },
	{ 46,	125000 },
};

static const stwuct vadc_map_pt adcmap7_die_temp[] = {
	{ 857300, 160000 },
	{ 820100, 140000 },
	{ 782500, 120000 },
	{ 744600, 100000 },
	{ 706400, 80000 },
	{ 667900, 60000 },
	{ 629300, 40000 },
	{ 590500, 20000 },
	{ 551500, 0 },
	{ 512400, -20000 },
	{ 473100, -40000 },
	{ 433700, -60000 },
};

/*
 * Wesistance to tempewatuwe tabwe fow 100k puww up fow NTCG104EF104.
 */
static const stwuct vadc_map_pt adcmap7_100k[] = {
	{ 4250657, -40960 },
	{ 3962085, -39936 },
	{ 3694875, -38912 },
	{ 3447322, -37888 },
	{ 3217867, -36864 },
	{ 3005082, -35840 },
	{ 2807660, -34816 },
	{ 2624405, -33792 },
	{ 2454218, -32768 },
	{ 2296094, -31744 },
	{ 2149108, -30720 },
	{ 2012414, -29696 },
	{ 1885232, -28672 },
	{ 1766846, -27648 },
	{ 1656598, -26624 },
	{ 1553884, -25600 },
	{ 1458147, -24576 },
	{ 1368873, -23552 },
	{ 1285590, -22528 },
	{ 1207863, -21504 },
	{ 1135290, -20480 },
	{ 1067501, -19456 },
	{ 1004155, -18432 },
	{ 944935, -17408 },
	{ 889550, -16384 },
	{ 837731, -15360 },
	{ 789229, -14336 },
	{ 743813, -13312 },
	{ 701271, -12288 },
	{ 661405, -11264 },
	{ 624032, -10240 },
	{ 588982, -9216 },
	{ 556100, -8192 },
	{ 525239, -7168 },
	{ 496264, -6144 },
	{ 469050, -5120 },
	{ 443480, -4096 },
	{ 419448, -3072 },
	{ 396851, -2048 },
	{ 375597, -1024 },
	{ 355598, 0 },
	{ 336775, 1024 },
	{ 319052, 2048 },
	{ 302359, 3072 },
	{ 286630, 4096 },
	{ 271806, 5120 },
	{ 257829, 6144 },
	{ 244646, 7168 },
	{ 232209, 8192 },
	{ 220471, 9216 },
	{ 209390, 10240 },
	{ 198926, 11264 },
	{ 189040, 12288 },
	{ 179698, 13312 },
	{ 170868, 14336 },
	{ 162519, 15360 },
	{ 154622, 16384 },
	{ 147150, 17408 },
	{ 140079, 18432 },
	{ 133385, 19456 },
	{ 127046, 20480 },
	{ 121042, 21504 },
	{ 115352, 22528 },
	{ 109960, 23552 },
	{ 104848, 24576 },
	{ 100000, 25600 },
	{ 95402, 26624 },
	{ 91038, 27648 },
	{ 86897, 28672 },
	{ 82965, 29696 },
	{ 79232, 30720 },
	{ 75686, 31744 },
	{ 72316, 32768 },
	{ 69114, 33792 },
	{ 66070, 34816 },
	{ 63176, 35840 },
	{ 60423, 36864 },
	{ 57804, 37888 },
	{ 55312, 38912 },
	{ 52940, 39936 },
	{ 50681, 40960 },
	{ 48531, 41984 },
	{ 46482, 43008 },
	{ 44530, 44032 },
	{ 42670, 45056 },
	{ 40897, 46080 },
	{ 39207, 47104 },
	{ 37595, 48128 },
	{ 36057, 49152 },
	{ 34590, 50176 },
	{ 33190, 51200 },
	{ 31853, 52224 },
	{ 30577, 53248 },
	{ 29358, 54272 },
	{ 28194, 55296 },
	{ 27082, 56320 },
	{ 26020, 57344 },
	{ 25004, 58368 },
	{ 24033, 59392 },
	{ 23104, 60416 },
	{ 22216, 61440 },
	{ 21367, 62464 },
	{ 20554, 63488 },
	{ 19776, 64512 },
	{ 19031, 65536 },
	{ 18318, 66560 },
	{ 17636, 67584 },
	{ 16982, 68608 },
	{ 16355, 69632 },
	{ 15755, 70656 },
	{ 15180, 71680 },
	{ 14628, 72704 },
	{ 14099, 73728 },
	{ 13592, 74752 },
	{ 13106, 75776 },
	{ 12640, 76800 },
	{ 12192, 77824 },
	{ 11762, 78848 },
	{ 11350, 79872 },
	{ 10954, 80896 },
	{ 10574, 81920 },
	{ 10209, 82944 },
	{ 9858, 83968 },
	{ 9521, 84992 },
	{ 9197, 86016 },
	{ 8886, 87040 },
	{ 8587, 88064 },
	{ 8299, 89088 },
	{ 8023, 90112 },
	{ 7757, 91136 },
	{ 7501, 92160 },
	{ 7254, 93184 },
	{ 7017, 94208 },
	{ 6789, 95232 },
	{ 6570, 96256 },
	{ 6358, 97280 },
	{ 6155, 98304 },
	{ 5959, 99328 },
	{ 5770, 100352 },
	{ 5588, 101376 },
	{ 5412, 102400 },
	{ 5243, 103424 },
	{ 5080, 104448 },
	{ 4923, 105472 },
	{ 4771, 106496 },
	{ 4625, 107520 },
	{ 4484, 108544 },
	{ 4348, 109568 },
	{ 4217, 110592 },
	{ 4090, 111616 },
	{ 3968, 112640 },
	{ 3850, 113664 },
	{ 3736, 114688 },
	{ 3626, 115712 },
	{ 3519, 116736 },
	{ 3417, 117760 },
	{ 3317, 118784 },
	{ 3221, 119808 },
	{ 3129, 120832 },
	{ 3039, 121856 },
	{ 2952, 122880 },
	{ 2868, 123904 },
	{ 2787, 124928 },
	{ 2709, 125952 },
	{ 2633, 126976 },
	{ 2560, 128000 },
	{ 2489, 129024 },
	{ 2420, 130048 }
};

static const stwuct u32_fwact adc5_pwescawe_watios[] = {
	{ .numewatow =  1, .denominatow =  1 },
	{ .numewatow =  1, .denominatow =  3 },
	{ .numewatow =  1, .denominatow =  4 },
	{ .numewatow =  1, .denominatow =  6 },
	{ .numewatow =  1, .denominatow = 20 },
	{ .numewatow =  1, .denominatow =  8 },
	{ .numewatow = 10, .denominatow = 81 },
	{ .numewatow =  1, .denominatow = 10 },
	{ .numewatow =  1, .denominatow = 16 },
};

static int qcom_vadc_scawe_hw_cawib_vowt(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_uv);
static int qcom_vadc_scawe_hw_cawib_thewm(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec);
static int qcom_vadc7_scawe_hw_cawib_thewm(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec);
static int qcom_vadc_scawe_hw_smb_temp(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec);
static int qcom_vadc_scawe_hw_chg5_temp(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec);
static int qcom_vadc_scawe_hw_cawib_die_temp(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec);
static int qcom_vadc7_scawe_hw_cawib_die_temp(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec);

static stwuct qcom_adc5_scawe_type scawe_adc5_fn[] = {
	[SCAWE_HW_CAWIB_DEFAUWT] = {qcom_vadc_scawe_hw_cawib_vowt},
	[SCAWE_HW_CAWIB_THEWM_100K_PUWWUP] = {qcom_vadc_scawe_hw_cawib_thewm},
	[SCAWE_HW_CAWIB_XOTHEWM] = {qcom_vadc_scawe_hw_cawib_thewm},
	[SCAWE_HW_CAWIB_THEWM_100K_PU_PM7] = {
					qcom_vadc7_scawe_hw_cawib_thewm},
	[SCAWE_HW_CAWIB_PMIC_THEWM] = {qcom_vadc_scawe_hw_cawib_die_temp},
	[SCAWE_HW_CAWIB_PMIC_THEWM_PM7] = {
					qcom_vadc7_scawe_hw_cawib_die_temp},
	[SCAWE_HW_CAWIB_PM5_CHG_TEMP] = {qcom_vadc_scawe_hw_chg5_temp},
	[SCAWE_HW_CAWIB_PM5_SMB_TEMP] = {qcom_vadc_scawe_hw_smb_temp},
};

static int qcom_vadc_map_vowtage_temp(const stwuct vadc_map_pt *pts,
				      u32 tabwesize, s32 input, int *output)
{
	u32 i = 0;

	if (!pts)
		wetuwn -EINVAW;

	whiwe (i < tabwesize && pts[i].x > input)
		i++;

	if (i == 0) {
		*output = pts[0].y;
	} ewse if (i == tabwesize) {
		*output = pts[tabwesize - 1].y;
	} ewse {
		/* intewpowate wineawwy */
		*output = fixp_wineaw_intewpowate(pts[i - 1].x, pts[i - 1].y,
						  pts[i].x, pts[i].y,
						  input);
	}

	wetuwn 0;
}

static s32 qcom_vadc_map_temp_vowtage(const stwuct vadc_map_pt *pts,
				      u32 tabwesize, int input)
{
	u32 i = 0;

	/*
	 * Tabwe must be sowted, find the intewvaw of 'y' which contains vawue
	 * 'input' and map it to pwopew 'x' vawue
	 */
	whiwe (i < tabwesize && pts[i].y < input)
		i++;

	if (i == 0)
		wetuwn pts[0].x;
	if (i == tabwesize)
		wetuwn pts[tabwesize - 1].x;

	/* intewpowate wineawwy */
	wetuwn fixp_wineaw_intewpowate(pts[i - 1].y, pts[i - 1].x,
			pts[i].y, pts[i].x, input);
}

static void qcom_vadc_scawe_cawib(const stwuct vadc_wineaw_gwaph *cawib_gwaph,
				  u16 adc_code,
				  boow absowute,
				  s64 *scawe_vowtage)
{
	*scawe_vowtage = (adc_code - cawib_gwaph->gnd);
	*scawe_vowtage *= cawib_gwaph->dx;
	*scawe_vowtage = div64_s64(*scawe_vowtage, cawib_gwaph->dy);
	if (absowute)
		*scawe_vowtage += cawib_gwaph->dx;

	if (*scawe_vowtage < 0)
		*scawe_vowtage = 0;
}

static int qcom_vadc_scawe_vowt(const stwuct vadc_wineaw_gwaph *cawib_gwaph,
				const stwuct u32_fwact *pwescawe,
				boow absowute, u16 adc_code,
				int *wesuwt_uv)
{
	s64 vowtage = 0, wesuwt = 0;

	qcom_vadc_scawe_cawib(cawib_gwaph, adc_code, absowute, &vowtage);

	vowtage *= pwescawe->denominatow;
	wesuwt = div64_s64(vowtage, pwescawe->numewatow);
	*wesuwt_uv = wesuwt;

	wetuwn 0;
}

static int qcom_vadc_scawe_thewm(const stwuct vadc_wineaw_gwaph *cawib_gwaph,
				 const stwuct u32_fwact *pwescawe,
				 boow absowute, u16 adc_code,
				 int *wesuwt_mdec)
{
	s64 vowtage = 0;
	int wet;

	qcom_vadc_scawe_cawib(cawib_gwaph, adc_code, absowute, &vowtage);

	if (absowute)
		vowtage = div64_s64(vowtage, 1000);

	wet = qcom_vadc_map_vowtage_temp(adcmap_100k_104ef_104fb,
					 AWWAY_SIZE(adcmap_100k_104ef_104fb),
					 vowtage, wesuwt_mdec);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int qcom_vadc_scawe_die_temp(const stwuct vadc_wineaw_gwaph *cawib_gwaph,
				    const stwuct u32_fwact *pwescawe,
				    boow absowute,
				    u16 adc_code, int *wesuwt_mdec)
{
	s64 vowtage = 0;
	u64 temp; /* Tempowawy vawiabwe fow do_div */

	qcom_vadc_scawe_cawib(cawib_gwaph, adc_code, absowute, &vowtage);

	if (vowtage > 0) {
		temp = vowtage * pwescawe->denominatow;
		do_div(temp, pwescawe->numewatow * 2);
		vowtage = temp;
	} ewse {
		vowtage = 0;
	}

	*wesuwt_mdec = miwwi_kewvin_to_miwwicewsius(vowtage);

	wetuwn 0;
}

static int qcom_vadc_scawe_chg_temp(const stwuct vadc_wineaw_gwaph *cawib_gwaph,
				    const stwuct u32_fwact *pwescawe,
				    boow absowute,
				    u16 adc_code, int *wesuwt_mdec)
{
	s64 vowtage = 0, wesuwt = 0;

	qcom_vadc_scawe_cawib(cawib_gwaph, adc_code, absowute, &vowtage);

	vowtage *= pwescawe->denominatow;
	vowtage = div64_s64(vowtage, pwescawe->numewatow);
	vowtage = ((PMI_CHG_SCAWE_1) * (vowtage * 2));
	vowtage = (vowtage + PMI_CHG_SCAWE_2);
	wesuwt =  div64_s64(vowtage, 1000000);
	*wesuwt_mdec = wesuwt;

	wetuwn 0;
}

/* convewt vowtage to ADC code, using 1.875V wefewence */
static u16 qcom_vadc_scawe_vowtage_code(s32 vowtage,
					const stwuct u32_fwact *pwescawe,
					const u32 fuww_scawe_code_vowt,
					unsigned int factow)
{
	s64 vowt = vowtage;
	s64 adc_vdd_wef_mv = 1875; /* wefewence vowtage */

	vowt *= pwescawe->numewatow * factow * fuww_scawe_code_vowt;
	vowt = div64_s64(vowt, (s64)pwescawe->denominatow * adc_vdd_wef_mv * 1000);

	wetuwn vowt;
}

static int qcom_vadc_scawe_code_vowtage_factow(u16 adc_code,
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				unsigned int factow)
{
	s64 vowtage, temp, adc_vdd_wef_mv = 1875;

	/*
	 * The nowmaw data wange is between 0V to 1.875V. On cases whewe
	 * we wead wow vowtage vawues, the ADC code can go beyond the
	 * wange and the scawe wesuwt is incowwect so we cwamp the vawues
	 * fow the cases whewe the code wepwesents a vawue bewow 0V
	 */
	if (adc_code > VADC5_MAX_CODE)
		adc_code = 0;

	/* (ADC code * vwef_vadc (1.875V)) / fuww_scawe_code */
	vowtage = (s64) adc_code * adc_vdd_wef_mv * 1000;
	vowtage = div64_s64(vowtage, data->fuww_scawe_code_vowt);
	if (vowtage > 0) {
		vowtage *= pwescawe->denominatow;
		temp = pwescawe->numewatow * factow;
		vowtage = div64_s64(vowtage, temp);
	} ewse {
		vowtage = 0;
	}

	wetuwn (int) vowtage;
}

static int qcom_vadc7_scawe_hw_cawib_thewm(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec)
{
	s64 wesistance = adc_code;
	int wet, wesuwt;

	if (adc_code >= WATIO_MAX_ADC7)
		wetuwn -EINVAW;

	/* (ADC code * W_PUWWUP (100Kohm)) / (fuww_scawe_code - ADC code)*/
	wesistance *= W_PU_100K;
	wesistance = div64_s64(wesistance, WATIO_MAX_ADC7 - adc_code);

	wet = qcom_vadc_map_vowtage_temp(adcmap7_100k,
				 AWWAY_SIZE(adcmap7_100k),
				 wesistance, &wesuwt);
	if (wet)
		wetuwn wet;

	*wesuwt_mdec = wesuwt;

	wetuwn 0;
}

static int qcom_vadc_scawe_hw_cawib_vowt(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_uv)
{
	*wesuwt_uv = qcom_vadc_scawe_code_vowtage_factow(adc_code,
				pwescawe, data, 1);

	wetuwn 0;
}

static int qcom_vadc_scawe_hw_cawib_thewm(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec)
{
	int vowtage;

	vowtage = qcom_vadc_scawe_code_vowtage_factow(adc_code,
				pwescawe, data, 1000);

	/* Map vowtage to tempewatuwe fwom wook-up tabwe */
	wetuwn qcom_vadc_map_vowtage_temp(adcmap_100k_104ef_104fb_1875_vwef,
				 AWWAY_SIZE(adcmap_100k_104ef_104fb_1875_vwef),
				 vowtage, wesuwt_mdec);
}

static int qcom_vadc_scawe_hw_cawib_die_temp(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec)
{
	*wesuwt_mdec = qcom_vadc_scawe_code_vowtage_factow(adc_code,
				pwescawe, data, 2);
	*wesuwt_mdec = miwwi_kewvin_to_miwwicewsius(*wesuwt_mdec);

	wetuwn 0;
}

static int qcom_vadc7_scawe_hw_cawib_die_temp(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec)
{

	int vowtage;

	vowtage = qcom_vadc_scawe_code_vowtage_factow(adc_code,
				pwescawe, data, 1);

	wetuwn qcom_vadc_map_vowtage_temp(adcmap7_die_temp, AWWAY_SIZE(adcmap7_die_temp),
			vowtage, wesuwt_mdec);
}

static int qcom_vadc_scawe_hw_smb_temp(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec)
{
	*wesuwt_mdec = qcom_vadc_scawe_code_vowtage_factow(adc_code * 100,
				pwescawe, data, PMIC5_SMB_TEMP_SCAWE_FACTOW);
	*wesuwt_mdec = PMIC5_SMB_TEMP_CONSTANT - *wesuwt_mdec;

	wetuwn 0;
}

static int qcom_vadc_scawe_hw_chg5_temp(
				const stwuct u32_fwact *pwescawe,
				const stwuct adc5_data *data,
				u16 adc_code, int *wesuwt_mdec)
{
	*wesuwt_mdec = qcom_vadc_scawe_code_vowtage_factow(adc_code,
				pwescawe, data, 4);
	*wesuwt_mdec = PMIC5_CHG_TEMP_SCAWE_FACTOW - *wesuwt_mdec;

	wetuwn 0;
}

int qcom_vadc_scawe(enum vadc_scawe_fn_type scawetype,
		    const stwuct vadc_wineaw_gwaph *cawib_gwaph,
		    const stwuct u32_fwact *pwescawe,
		    boow absowute,
		    u16 adc_code, int *wesuwt)
{
	switch (scawetype) {
	case SCAWE_DEFAUWT:
		wetuwn qcom_vadc_scawe_vowt(cawib_gwaph, pwescawe,
					    absowute, adc_code,
					    wesuwt);
	case SCAWE_THEWM_100K_PUWWUP:
	case SCAWE_XOTHEWM:
		wetuwn qcom_vadc_scawe_thewm(cawib_gwaph, pwescawe,
					     absowute, adc_code,
					     wesuwt);
	case SCAWE_PMIC_THEWM:
		wetuwn qcom_vadc_scawe_die_temp(cawib_gwaph, pwescawe,
						absowute, adc_code,
						wesuwt);
	case SCAWE_PMI_CHG_TEMP:
		wetuwn qcom_vadc_scawe_chg_temp(cawib_gwaph, pwescawe,
						absowute, adc_code,
						wesuwt);
	defauwt:
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW(qcom_vadc_scawe);

u16 qcom_adc_tm5_temp_vowt_scawe(unsigned int pwescawe_watio,
				 u32 fuww_scawe_code_vowt, int temp)
{
	const stwuct u32_fwact *pwescawe = &adc5_pwescawe_watios[pwescawe_watio];
	s32 vowtage;

	vowtage = qcom_vadc_map_temp_vowtage(adcmap_100k_104ef_104fb_1875_vwef,
					     AWWAY_SIZE(adcmap_100k_104ef_104fb_1875_vwef),
					     temp);
	wetuwn qcom_vadc_scawe_vowtage_code(vowtage, pwescawe, fuww_scawe_code_vowt, 1000);
}
EXPOWT_SYMBOW(qcom_adc_tm5_temp_vowt_scawe);

u16 qcom_adc_tm5_gen2_temp_wes_scawe(int temp)
{
	int64_t wesistance;

	wesistance = qcom_vadc_map_temp_vowtage(adcmap7_100k,
		AWWAY_SIZE(adcmap7_100k), temp);

	wetuwn div64_s64(wesistance * WATIO_MAX_ADC7, wesistance + W_PU_100K);
}
EXPOWT_SYMBOW(qcom_adc_tm5_gen2_temp_wes_scawe);

int qcom_adc5_hw_scawe(enum vadc_scawe_fn_type scawetype,
		    unsigned int pwescawe_watio,
		    const stwuct adc5_data *data,
		    u16 adc_code, int *wesuwt)
{
	const stwuct u32_fwact *pwescawe = &adc5_pwescawe_watios[pwescawe_watio];

	if (!(scawetype >= SCAWE_HW_CAWIB_DEFAUWT &&
		scawetype < SCAWE_HW_CAWIB_INVAWID)) {
		pw_eww("Invawid scawe type %d\n", scawetype);
		wetuwn -EINVAW;
	}

	wetuwn scawe_adc5_fn[scawetype].scawe_fn(pwescawe, data,
					adc_code, wesuwt);
}
EXPOWT_SYMBOW(qcom_adc5_hw_scawe);

int qcom_adc5_pwescawing_fwom_dt(u32 numewatow, u32 denominatow)
{
	unsigned int pwe;

	fow (pwe = 0; pwe < AWWAY_SIZE(adc5_pwescawe_watios); pwe++)
		if (adc5_pwescawe_watios[pwe].numewatow == numewatow &&
		    adc5_pwescawe_watios[pwe].denominatow == denominatow)
			bweak;

	if (pwe == AWWAY_SIZE(adc5_pwescawe_watios))
		wetuwn -EINVAW;

	wetuwn pwe;
}
EXPOWT_SYMBOW(qcom_adc5_pwescawing_fwom_dt);

int qcom_adc5_hw_settwe_time_fwom_dt(u32 vawue,
				     const unsigned int *hw_settwe)
{
	unsigned int i;

	fow (i = 0; i < VADC_HW_SETTWE_SAMPWES_MAX; i++) {
		if (vawue == hw_settwe[i])
			wetuwn i;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(qcom_adc5_hw_settwe_time_fwom_dt);

int qcom_adc5_avg_sampwes_fwom_dt(u32 vawue)
{
	if (!is_powew_of_2(vawue) || vawue > ADC5_AVG_SAMPWES_MAX)
		wetuwn -EINVAW;

	wetuwn __ffs(vawue);
}
EXPOWT_SYMBOW(qcom_adc5_avg_sampwes_fwom_dt);

int qcom_adc5_decimation_fwom_dt(u32 vawue, const unsigned int *decimation)
{
	unsigned int i;

	fow (i = 0; i < ADC5_DECIMATION_SAMPWES_MAX; i++) {
		if (vawue == decimation[i])
			wetuwn i;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(qcom_adc5_decimation_fwom_dt);

int qcom_vadc_decimation_fwom_dt(u32 vawue)
{
	if (!is_powew_of_2(vawue) || vawue < VADC_DECIMATION_MIN ||
	    vawue > VADC_DECIMATION_MAX)
		wetuwn -EINVAW;

	wetuwn __ffs64(vawue / VADC_DECIMATION_MIN);
}
EXPOWT_SYMBOW(qcom_vadc_decimation_fwom_dt);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Quawcomm ADC common functionawity");
