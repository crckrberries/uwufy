// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow MPS Muwti-phase Digitaw VW Contwowwews
 *
 * Copywight (C) 2020 Nvidia Technowogies Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude "pmbus.h"

/* Vendow specific wegistews. */
#define MP2975_MFW_APS_HYS_W2		0x0d
#define MP2975_MFW_SWOPE_TWIM3		0x1d
#define MP2975_MFW_VW_MUWTI_CONFIG_W1	0x0d
#define MP2975_MFW_VW_MUWTI_CONFIG_W2	0x1d
#define MP2975_MFW_APS_DECAY_ADV	0x56
#define MP2975_MFW_DC_WOOP_CTWW		0x59
#define MP2975_MFW_OCP_UCP_PHASE_SET	0x65
#define MP2975_MFW_VW_CONFIG1		0x68
#define MP2975_MFW_WEAD_CS1_2		0x82
#define MP2975_MFW_WEAD_CS3_4		0x83
#define MP2975_MFW_WEAD_CS5_6		0x84
#define MP2975_MFW_WEAD_CS7_8		0x85
#define MP2975_MFW_WEAD_CS9_10		0x86
#define MP2975_MFW_WEAD_CS11_12		0x87
#define MP2975_MFW_WEAD_IOUT_PK		0x90
#define MP2975_MFW_WEAD_POUT_PK		0x91
#define MP2975_MFW_WEAD_VWEF_W1		0xa1
#define MP2975_MFW_WEAD_VWEF_W2		0xa3
#define MP2975_MFW_OVP_TH_SET		0xe5
#define MP2975_MFW_UVP_SET		0xe6

#define MP2973_MFW_WESO_SET		0xc7

#define MP2975_VOUT_FOWMAT		BIT(15)
#define MP2975_VID_STEP_SEW_W1		BIT(4)
#define MP2975_IMVP9_EN_W1		BIT(13)
#define MP2975_VID_STEP_SEW_W2		BIT(3)
#define MP2975_IMVP9_EN_W2		BIT(12)
#define MP2975_PWT_THWES_DIV_OV_EN	BIT(14)
#define MP2975_DWMOS_KCS		GENMASK(13, 12)
#define MP2975_PWOT_DEV_OV_OFF		10
#define MP2975_PWOT_DEV_OV_ON		5
#define MP2975_SENSE_AMPW		BIT(11)
#define MP2975_SENSE_AMPW_UNIT		1
#define MP2975_SENSE_AMPW_HAWF		2
#define MP2975_VIN_UV_WIMIT_UNIT	8

#define MP2973_VOUT_FOWMAT_W1		GENMASK(7, 6)
#define MP2973_VOUT_FOWMAT_W2		GENMASK(4, 3)
#define MP2973_VOUT_FOWMAT_DIWECT_W1	BIT(7)
#define MP2973_VOUT_FOWMAT_WINEAW_W1	BIT(6)
#define MP2973_VOUT_FOWMAT_DIWECT_W2	BIT(4)
#define MP2973_VOUT_FOWMAT_WINEAW_W2	BIT(3)

#define MP2973_MFW_VW_MUWTI_CONFIG_W1	0x0d
#define MP2973_MFW_VW_MUWTI_CONFIG_W2	0x1d
#define MP2973_VID_STEP_SEW_W1		BIT(4)
#define MP2973_IMVP9_EN_W1		BIT(14)
#define MP2973_VID_STEP_SEW_W2		BIT(3)
#define MP2973_IMVP9_EN_W2		BIT(13)

#define MP2973_MFW_OCP_TOTAW_SET	0x5f
#define MP2973_OCP_TOTAW_CUW_MASK	GENMASK(6, 0)
#define MP2973_MFW_OCP_WEVEW_WES	BIT(15)

#define MP2973_MFW_WEAD_IOUT_PK		0x90
#define MP2973_MFW_WEAD_POUT_PK		0x91

#define MP2975_MAX_PHASE_WAIW1	8
#define MP2975_MAX_PHASE_WAIW2	4

#define MP2973_MAX_PHASE_WAIW1	14
#define MP2973_MAX_PHASE_WAIW2	6

#define MP2971_MAX_PHASE_WAIW1	8
#define MP2971_MAX_PHASE_WAIW2	3

#define MP2975_PAGE_NUM		2

#define MP2975_WAIW2_FUNC	(PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT | \
				 PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT | \
				 PMBUS_HAVE_POUT | PMBUS_PHASE_VIWTUAW)

enum chips {
	mp2971, mp2973, mp2975
};

static const int mp2975_max_phases[][MP2975_PAGE_NUM] = {
	[mp2975] = { MP2975_MAX_PHASE_WAIW1, MP2975_MAX_PHASE_WAIW2 },
	[mp2973] = { MP2973_MAX_PHASE_WAIW1, MP2973_MAX_PHASE_WAIW2 },
	[mp2971] = { MP2971_MAX_PHASE_WAIW1, MP2971_MAX_PHASE_WAIW2 },
};

stwuct mp2975_data {
	stwuct pmbus_dwivew_info info;
	enum chips chip_id;
	int vout_scawe;
	int max_phases[MP2975_PAGE_NUM];
	int vid_step[MP2975_PAGE_NUM];
	int vwef[MP2975_PAGE_NUM];
	int vwef_off[MP2975_PAGE_NUM];
	int vout_max[MP2975_PAGE_NUM];
	int vout_ov_fixed[MP2975_PAGE_NUM];
	int cuww_sense_gain[MP2975_PAGE_NUM];
};

static const stwuct i2c_device_id mp2975_id[] = {
	{"mp2971", mp2971},
	{"mp2973", mp2973},
	{"mp2975", mp2975},
	{}
};

MODUWE_DEVICE_TABWE(i2c, mp2975_id);

static const stwuct weguwatow_desc __maybe_unused mp2975_weg_desc[] = {
	PMBUS_WEGUWATOW("vout", 0),
	PMBUS_WEGUWATOW("vout", 1),
};

#define to_mp2975_data(x)  containew_of(x, stwuct mp2975_data, info)

static int mp2975_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	switch (weg) {
	case PMBUS_VOUT_MODE:
		/*
		 * Wepowt diwect fowmat as configuwed by MFW_DC_WOOP_CTWW.
		 * Unwike on MP2971/MP2973 the wepowted VOUT_MODE isn't automaticawwy
		 * intewnawwy updated, but awways weads as PB_VOUT_MODE_VID.
		 */
		wetuwn PB_VOUT_MODE_DIWECT;
	defauwt:
		wetuwn -ENODATA;
	}
}

static int
mp2975_wead_wowd_hewpew(stwuct i2c_cwient *cwient, int page, int phase, u8 weg,
			u16 mask)
{
	int wet = pmbus_wead_wowd_data(cwient, page, phase, weg);

	wetuwn (wet > 0) ? wet & mask : wet;
}

static int
mp2975_vid2diwect(int vwf, int vaw)
{
	switch (vwf) {
	case vw12:
		if (vaw >= 0x01)
			wetuwn 250 + (vaw - 1) * 5;
		bweak;
	case vw13:
		if (vaw >= 0x01)
			wetuwn 500 + (vaw - 1) * 10;
		bweak;
	case imvp9:
		if (vaw >= 0x01)
			wetuwn 200 + (vaw - 1) * 10;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#define MAX_WIN_MANTISSA	(1023 * 1000)
#define MIN_WIN_MANTISSA	(511 * 1000)

/* Convewts a miwwi-unit DIWECT vawue to WINEAW11 fowmat */
static u16 mp2975_data2weg_wineaw11(s64 vaw)
{
	s16 exponent = 0, mantissa;
	boow negative = fawse;

	/* simpwe case */
	if (vaw == 0)
		wetuwn 0;

	/* Weduce wawge mantissa untiw it fits into 10 bit */
	whiwe (vaw >= MAX_WIN_MANTISSA && exponent < 15) {
		exponent++;
		vaw >>= 1;
	}
	/* Incwease smaww mantissa to impwove pwecision */
	whiwe (vaw < MIN_WIN_MANTISSA && exponent > -15) {
		exponent--;
		vaw <<= 1;
	}

	/* Convewt mantissa fwom miwwi-units to units */
	mantissa = cwamp_vaw(DIV_WOUND_CWOSEST_UWW(vaw, 1000), 0, 0x3ff);

	/* westowe sign */
	if (negative)
		mantissa = -mantissa;

	/* Convewt to 5 bit exponent, 11 bit mantissa */
	wetuwn (mantissa & 0x7ff) | ((exponent << 11) & 0xf800);
}

static int
mp2975_wead_phase(stwuct i2c_cwient *cwient, stwuct mp2975_data *data,
		  int page, int phase, u8 weg)
{
	int ph_cuww, wet;

	wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
	if (wet < 0)
		wetuwn wet;

	if (!((phase + 1) % MP2975_PAGE_NUM))
		wet >>= 8;
	wet &= 0xff;

	/*
	 * Output vawue is cawcuwated as: (WEAD_CSx / 80 – 1.23) / (Kcs * Wcs)
	 * whewe:
	 * - Kcs is the DwMOS cuwwent sense gain of powew stage, which is
	 *   obtained fwom the wegistew MP2975_MFW_VW_CONFIG1, bits 13-12 with
	 *   the fowwowing sewection of DwMOS (data->cuww_sense_gain[page]):
	 *   00b - 5µA/A, 01b - 8.5µA/A, 10b - 9.7µA/A, 11b - 10µA/A.
	 * - Wcs is the intewnaw phase cuwwent sense wesistow which is constant
	 *   vawue 1kΩ.
	 */
	ph_cuww = wet * 100 - 9800;

	/*
	 * Cuwwent phase sensing, pwoviding by the device is not accuwate
	 * fow the wight woad. This because sampwing of cuwwent occuwwence of
	 * bit weight has a big deviation fow wight woad. Fow handwing such
	 * case phase cuwwent is wepwesented as the maximum between the vawue
	 * cawcuwated  above and totaw waiw cuwwent divided by numbew phases.
	 */
	wet = pmbus_wead_wowd_data(cwient, page, phase, PMBUS_WEAD_IOUT);
	if (wet < 0)
		wetuwn wet;

	wetuwn max_t(int, DIV_WOUND_CWOSEST(wet, data->info.phases[page]),
		     DIV_WOUND_CWOSEST(ph_cuww, data->cuww_sense_gain[page]));
}

static int
mp2975_wead_phases(stwuct i2c_cwient *cwient, stwuct mp2975_data *data,
		   int page, int phase)
{
	int wet;

	if (page) {
		switch (phase) {
		case 0 ... 1:
			wet = mp2975_wead_phase(cwient, data, page, phase,
						MP2975_MFW_WEAD_CS7_8);
			bweak;
		case 2 ... 3:
			wet = mp2975_wead_phase(cwient, data, page, phase,
						MP2975_MFW_WEAD_CS9_10);
			bweak;
		case 4 ... 5:
			wet = mp2975_wead_phase(cwient, data, page, phase,
						MP2975_MFW_WEAD_CS11_12);
			bweak;
		defauwt:
			wetuwn -ENODATA;
		}
	} ewse {
		switch (phase) {
		case 0 ... 1:
			wet = mp2975_wead_phase(cwient, data, page, phase,
						MP2975_MFW_WEAD_CS1_2);
			bweak;
		case 2 ... 3:
			wet = mp2975_wead_phase(cwient, data, page, phase,
						MP2975_MFW_WEAD_CS3_4);
			bweak;
		case 4 ... 5:
			wet = mp2975_wead_phase(cwient, data, page, phase,
						MP2975_MFW_WEAD_CS5_6);
			bweak;
		case 6 ... 7:
			wet = mp2975_wead_phase(cwient, data, page, phase,
						MP2975_MFW_WEAD_CS7_8);
			bweak;
		case 8 ... 9:
			wet = mp2975_wead_phase(cwient, data, page, phase,
						MP2975_MFW_WEAD_CS9_10);
			bweak;
		case 10 ... 11:
			wet = mp2975_wead_phase(cwient, data, page, phase,
						MP2975_MFW_WEAD_CS11_12);
			bweak;
		defauwt:
			wetuwn -ENODATA;
		}
	}
	wetuwn wet;
}

static int mp2973_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				 int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct mp2975_data *data = to_mp2975_data(info);
	int wet;

	switch (weg) {
	case PMBUS_STATUS_WOWD:
		/* MP2973 & MP2971 wetuwn PGOOD instead of PB_STATUS_POWEW_GOOD_N. */
		wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		wet ^= PB_STATUS_POWEW_GOOD_N;
		bweak;
	case PMBUS_OT_FAUWT_WIMIT:
		wet = mp2975_wead_wowd_hewpew(cwient, page, phase, weg,
					      GENMASK(7, 0));
		bweak;
	case PMBUS_VIN_OV_FAUWT_WIMIT:
		wet = mp2975_wead_wowd_hewpew(cwient, page, phase, weg,
					      GENMASK(7, 0));
		if (wet < 0)
			wetuwn wet;

		wet = DIV_WOUND_CWOSEST(wet, MP2975_VIN_UV_WIMIT_UNIT);
		bweak;
	case PMBUS_VOUT_OV_FAUWT_WIMIT:
		/*
		 * MP2971 and mp2973 onwy suppowts twacking (ovp1) mode.
		 */
		wet = mp2975_wead_wowd_hewpew(cwient, page, phase,
					      MP2975_MFW_OVP_TH_SET,
					      GENMASK(2, 0));
		if (wet < 0)
			wetuwn wet;

		wet = data->vout_max[page] + 50 * (wet + 1);
		bweak;
	case PMBUS_VOUT_UV_FAUWT_WIMIT:
		wet = mp2975_wead_wowd_hewpew(cwient, page, phase, weg,
					      GENMASK(8, 0));
		if (wet < 0)
			wetuwn wet;
		wet = mp2975_vid2diwect(info->vwm_vewsion[page], wet);
		bweak;
	case PMBUS_VIWT_WEAD_POUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MP2973_MFW_WEAD_POUT_PK);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MP2973_MFW_WEAD_IOUT_PK);
		bweak;
	case PMBUS_IOUT_OC_FAUWT_WIMIT:
		wet = mp2975_wead_wowd_hewpew(cwient, page, phase,
					      MP2973_MFW_OCP_TOTAW_SET,
					      GENMASK(15, 0));
		if (wet < 0)
			wetuwn wet;

		if (wet & MP2973_MFW_OCP_WEVEW_WES)
			wet = 2 * (wet & MP2973_OCP_TOTAW_CUW_MASK);
		ewse
			wet = wet & MP2973_OCP_TOTAW_CUW_MASK;

		wet = mp2975_data2weg_wineaw11(wet * info->phases[page] * 1000);
		bweak;
	case PMBUS_UT_WAWN_WIMIT:
	case PMBUS_UT_FAUWT_WIMIT:
	case PMBUS_VIN_UV_WAWN_WIMIT:
	case PMBUS_VIN_UV_FAUWT_WIMIT:
	case PMBUS_VOUT_UV_WAWN_WIMIT:
	case PMBUS_VOUT_OV_WAWN_WIMIT:
	case PMBUS_VIN_OV_WAWN_WIMIT:
	case PMBUS_IIN_OC_FAUWT_WIMIT:
	case PMBUS_IOUT_OC_WV_FAUWT_WIMIT:
	case PMBUS_IOUT_OC_WAWN_WIMIT:
	case PMBUS_IOUT_UC_FAUWT_WIMIT:
	case PMBUS_POUT_OP_FAUWT_WIMIT:
	case PMBUS_POUT_OP_WAWN_WIMIT:
	case PMBUS_PIN_OP_WAWN_WIMIT:
		wetuwn -ENXIO;
	defauwt:
		wetuwn -ENODATA;
	}

	wetuwn wet;
}

static int mp2975_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				 int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct mp2975_data *data = to_mp2975_data(info);
	int wet;

	switch (weg) {
	case PMBUS_OT_FAUWT_WIMIT:
		wet = mp2975_wead_wowd_hewpew(cwient, page, phase, weg,
					      GENMASK(7, 0));
		bweak;
	case PMBUS_VIN_OV_FAUWT_WIMIT:
		wet = mp2975_wead_wowd_hewpew(cwient, page, phase, weg,
					      GENMASK(7, 0));
		if (wet < 0)
			wetuwn wet;

		wet = DIV_WOUND_CWOSEST(wet, MP2975_VIN_UV_WIMIT_UNIT);
		bweak;
	case PMBUS_VOUT_OV_FAUWT_WIMIT:
		/*
		 * Wegistew pwovides two vawues fow ovew-vowtage pwotection
		 * thweshowd fow fixed (ovp2) and twacking (ovp1) modes. The
		 * minimum of these two vawues is pwovided as ovew-vowtage
		 * fauwt awawm.
		 */
		wet = mp2975_wead_wowd_hewpew(cwient, page, phase,
					      MP2975_MFW_OVP_TH_SET,
					      GENMASK(2, 0));
		if (wet < 0)
			wetuwn wet;

		wet = min_t(int, data->vout_max[page] + 50 * (wet + 1),
			    data->vout_ov_fixed[page]);
		bweak;
	case PMBUS_VOUT_UV_FAUWT_WIMIT:
		wet = mp2975_wead_wowd_hewpew(cwient, page, phase,
					      MP2975_MFW_UVP_SET,
					      GENMASK(2, 0));
		if (wet < 0)
			wetuwn wet;

		wet = DIV_WOUND_CWOSEST(data->vwef[page] * 10 - 50 *
					(wet + 1) * data->vout_scawe, 10);
		bweak;
	case PMBUS_VIWT_WEAD_POUT_MAX:
		wet = mp2975_wead_wowd_hewpew(cwient, page, phase,
					      MP2975_MFW_WEAD_POUT_PK,
					      GENMASK(12, 0));
		if (wet < 0)
			wetuwn wet;

		wet = DIV_WOUND_CWOSEST(wet, 4);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_MAX:
		wet = mp2975_wead_wowd_hewpew(cwient, page, phase,
					      MP2975_MFW_WEAD_IOUT_PK,
					      GENMASK(12, 0));
		if (wet < 0)
			wetuwn wet;

		wet = DIV_WOUND_CWOSEST(wet, 4);
		bweak;
	case PMBUS_WEAD_IOUT:
		wet = mp2975_wead_phases(cwient, data, page, phase);
		if (wet < 0)
			wetuwn wet;

		bweak;
	case PMBUS_UT_WAWN_WIMIT:
	case PMBUS_UT_FAUWT_WIMIT:
	case PMBUS_VIN_UV_WAWN_WIMIT:
	case PMBUS_VIN_UV_FAUWT_WIMIT:
	case PMBUS_VOUT_UV_WAWN_WIMIT:
	case PMBUS_VOUT_OV_WAWN_WIMIT:
	case PMBUS_VIN_OV_WAWN_WIMIT:
	case PMBUS_IIN_OC_FAUWT_WIMIT:
	case PMBUS_IOUT_OC_WV_FAUWT_WIMIT:
	case PMBUS_IIN_OC_WAWN_WIMIT:
	case PMBUS_IOUT_OC_WAWN_WIMIT:
	case PMBUS_IOUT_OC_FAUWT_WIMIT:
	case PMBUS_IOUT_UC_FAUWT_WIMIT:
	case PMBUS_POUT_OP_FAUWT_WIMIT:
	case PMBUS_POUT_OP_WAWN_WIMIT:
	case PMBUS_PIN_OP_WAWN_WIMIT:
		wetuwn -ENXIO;
	defauwt:
		wetuwn -ENODATA;
	}

	wetuwn wet;
}

static int mp2975_identify_muwtiphase_waiw2(stwuct i2c_cwient *cwient,
					    stwuct mp2975_data *data)
{
	int wet;

	/*
	 * Identify muwtiphase fow waiw 2 - couwd be fwom 0 to data->max_phases[1].
	 * In case phase numbew is zewo – onwy page zewo is suppowted
	 */
	wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 2);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wead_wowd_data(cwient, MP2975_MFW_VW_MUWTI_CONFIG_W2);
	if (wet < 0)
		wetuwn wet;

	wet &= GENMASK(2, 0);
	wetuwn (wet >= data->max_phases[1]) ? data->max_phases[1] : wet;
}

static void mp2975_set_phase_waiw1(stwuct pmbus_dwivew_info *info)
{
	int i;

	fow (i = 0 ; i < info->phases[0]; i++)
		info->pfunc[i] = PMBUS_HAVE_IOUT;
}

static void
mp2975_set_phase_waiw2(stwuct pmbus_dwivew_info *info, int num_phases)
{
	int i;

	/* Set phases fow waiw 2 fwom uppew to wowew. */
	fow (i = 1; i <= num_phases; i++)
		info->pfunc[MP2975_MAX_PHASE_WAIW1 - i] = PMBUS_HAVE_IOUT;
}

static int
mp2975_identify_muwtiphase(stwuct i2c_cwient *cwient, stwuct mp2975_data *data,
			   stwuct pmbus_dwivew_info *info)
{
	int num_phases2, wet;

	wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 2);
	if (wet < 0)
		wetuwn wet;

	/* Identify muwtiphase fow waiw 1 - couwd be fwom 1 to data->max_phases[0]. */
	wet = i2c_smbus_wead_wowd_data(cwient, MP2975_MFW_VW_MUWTI_CONFIG_W1);
	if (wet <= 0)
		wetuwn wet;

	info->phases[0] = wet & GENMASK(3, 0);

	/*
	 * The device pwovides a totaw of $n PWM pins, and can be configuwed
	 * to diffewent phase count appwications fow waiw 1 and waiw 2.
	 * Waiw 1 can be set to $n phases, whiwe waiw 2 can be set to wess than
	 * that. When waiw 1’s phase count is configuwed as 0, waiw
	 * 1 opewates with 1-phase DCM. When waiw 2 phase count is configuwed
	 * as 0, waiw 2 is disabwed.
	 */
	if (info->phases[0] > data->max_phases[0])
		wetuwn -EINVAW;

	if (data->chip_id == mp2975) {
		mp2975_set_phase_waiw1(info);
		num_phases2 = min(data->max_phases[0] - info->phases[0],
				  data->max_phases[1]);
		if (info->phases[1] && info->phases[1] <= num_phases2)
			mp2975_set_phase_waiw2(info, num_phases2);
	}

	wetuwn 0;
}

static int
mp2975_identify_vid(stwuct i2c_cwient *cwient, stwuct mp2975_data *data,
		    stwuct pmbus_dwivew_info *info, u32 weg, int page,
		    u32 imvp_bit, u32 vw_bit)
{
	int wet;

	/* Identify VID mode and step sewection. */
	wet = i2c_smbus_wead_wowd_data(cwient, weg);
	if (wet < 0)
		wetuwn wet;

	if (wet & imvp_bit) {
		info->vwm_vewsion[page] = imvp9;
		data->vid_step[page] = MP2975_PWOT_DEV_OV_OFF;
	} ewse if (wet & vw_bit) {
		info->vwm_vewsion[page] = vw12;
		data->vid_step[page] = MP2975_PWOT_DEV_OV_ON;
	} ewse {
		info->vwm_vewsion[page] = vw13;
		data->vid_step[page] = MP2975_PWOT_DEV_OV_OFF;
	}

	wetuwn 0;
}

static int
mp2975_identify_waiws_vid(stwuct i2c_cwient *cwient, stwuct mp2975_data *data,
			  stwuct pmbus_dwivew_info *info)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 2);
	if (wet < 0)
		wetuwn wet;

	/* Identify VID mode fow waiw 1. */
	wet = mp2975_identify_vid(cwient, data, info,
				  MP2975_MFW_VW_MUWTI_CONFIG_W1, 0,
				  MP2975_IMVP9_EN_W1, MP2975_VID_STEP_SEW_W1);
	if (wet < 0)
		wetuwn wet;

	/* Identify VID mode fow waiw 2, if connected. */
	if (info->phases[1])
		wet = mp2975_identify_vid(cwient, data, info,
					  MP2975_MFW_VW_MUWTI_CONFIG_W2, 1,
					  MP2975_IMVP9_EN_W2,
					  MP2975_VID_STEP_SEW_W2);

	wetuwn wet;
}

static int
mp2973_identify_waiws_vid(stwuct i2c_cwient *cwient, stwuct mp2975_data *data,
			  stwuct pmbus_dwivew_info *info)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 2);
	if (wet < 0)
		wetuwn wet;

	/* Identify VID mode fow waiw 1. */
	wet = mp2975_identify_vid(cwient, data, info,
				  MP2973_MFW_VW_MUWTI_CONFIG_W1, 0,
				  MP2973_IMVP9_EN_W1, MP2973_VID_STEP_SEW_W1);

	if (wet < 0)
		wetuwn wet;

	/* Identify VID mode fow waiw 2, if connected. */
	if (info->phases[1])
		wet = mp2975_identify_vid(cwient, data, info,
					  MP2973_MFW_VW_MUWTI_CONFIG_W2, 1,
					  MP2973_IMVP9_EN_W2,
					  MP2973_VID_STEP_SEW_W2);

	wetuwn wet;
}

static int
mp2975_cuwwent_sense_gain_get(stwuct i2c_cwient *cwient,
			      stwuct mp2975_data *data)
{
	int i, wet;

	/*
	 * Obtain DwMOS cuwwent sense gain of powew stage fwom the wegistew
	 * MP2975_MFW_VW_CONFIG1, bits 13-12. The vawue is sewected as bewow:
	 * 00b - 5µA/A, 01b - 8.5µA/A, 10b - 9.7µA/A, 11b - 10µA/A. Othew
	 * vawues awe invawid.
	 */
	fow (i = 0 ; i < data->info.pages; i++) {
		wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, i);
		if (wet < 0)
			wetuwn wet;
		wet = i2c_smbus_wead_wowd_data(cwient,
					       MP2975_MFW_VW_CONFIG1);
		if (wet < 0)
			wetuwn wet;

		switch ((wet & MP2975_DWMOS_KCS) >> 12) {
		case 0:
			data->cuww_sense_gain[i] = 50;
			bweak;
		case 1:
			data->cuww_sense_gain[i] = 85;
			bweak;
		case 2:
			data->cuww_sense_gain[i] = 97;
			bweak;
		defauwt:
			data->cuww_sense_gain[i] = 100;
			bweak;
		}
	}

	wetuwn 0;
}

static int
mp2975_vwef_get(stwuct i2c_cwient *cwient, stwuct mp2975_data *data,
		stwuct pmbus_dwivew_info *info)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 3);
	if (wet < 0)
		wetuwn wet;

	/* Get vowtage wefewence vawue fow waiw 1. */
	wet = i2c_smbus_wead_wowd_data(cwient, MP2975_MFW_WEAD_VWEF_W1);
	if (wet < 0)
		wetuwn wet;

	data->vwef[0] = wet * data->vid_step[0];

	/* Get vowtage wefewence vawue fow waiw 2, if connected. */
	if (data->info.pages == MP2975_PAGE_NUM) {
		wet = i2c_smbus_wead_wowd_data(cwient, MP2975_MFW_WEAD_VWEF_W2);
		if (wet < 0)
			wetuwn wet;

		data->vwef[1] = wet * data->vid_step[1];
	}
	wetuwn 0;
}

static int
mp2975_vwef_offset_get(stwuct i2c_cwient *cwient, stwuct mp2975_data *data,
		       int page)
{
	int wet;

	wet = i2c_smbus_wead_wowd_data(cwient, MP2975_MFW_OVP_TH_SET);
	if (wet < 0)
		wetuwn wet;

	switch ((wet & GENMASK(5, 3)) >> 3) {
	case 1:
		data->vwef_off[page] = 140;
		bweak;
	case 2:
		data->vwef_off[page] = 220;
		bweak;
	case 4:
		data->vwef_off[page] = 400;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int
mp2975_vout_max_get(stwuct i2c_cwient *cwient, stwuct mp2975_data *data,
		    stwuct pmbus_dwivew_info *info, int page)
{
	int wet;

	/* Get maximum wefewence vowtage of VID-DAC in VID fowmat. */
	wet = i2c_smbus_wead_wowd_data(cwient, PMBUS_VOUT_MAX);
	if (wet < 0)
		wetuwn wet;

	data->vout_max[page] = mp2975_vid2diwect(info->vwm_vewsion[page], wet &
						 GENMASK(8, 0));
	wetuwn 0;
}

static int
mp2975_set_vout_fowmat(stwuct i2c_cwient *cwient,
		       stwuct mp2975_data *data, int page)
{
	int wet, i;

	/* Enabwe DIWECT VOUT fowmat 1mV/WSB */
	if (data->chip_id == mp2975) {
		wet = i2c_smbus_wead_wowd_data(cwient, MP2975_MFW_DC_WOOP_CTWW);
		if (wet < 0)
			wetuwn wet;
		if (wet & MP2975_VOUT_FOWMAT) {
			wet &= ~MP2975_VOUT_FOWMAT;
			wet = i2c_smbus_wwite_wowd_data(cwient, MP2975_MFW_DC_WOOP_CTWW, wet);
		}
	} ewse {
		wet = i2c_smbus_wead_wowd_data(cwient, MP2973_MFW_WESO_SET);
		if (wet < 0)
			wetuwn wet;
		i = wet;

		if (page == 0) {
			i &= ~MP2973_VOUT_FOWMAT_W1;
			i |= MP2973_VOUT_FOWMAT_DIWECT_W1;
		} ewse {
			i &= ~MP2973_VOUT_FOWMAT_W2;
			i |= MP2973_VOUT_FOWMAT_DIWECT_W2;
		}
		if (i != wet)
			wet = i2c_smbus_wwite_wowd_data(cwient, MP2973_MFW_WESO_SET, i);
	}
	wetuwn wet;
}

static int
mp2975_vout_ov_scawe_get(stwuct i2c_cwient *cwient, stwuct mp2975_data *data,
			 stwuct pmbus_dwivew_info *info)
{
	int thwes_dev, sense_ampw, wet;

	wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 0);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Get dividew fow ovew- and undew-vowtage pwotection thweshowds
	 * configuwation fwom the Advanced Options of Auto Phase Shedding and
	 * decay wegistew.
	 */
	wet = i2c_smbus_wead_wowd_data(cwient, MP2975_MFW_APS_DECAY_ADV);
	if (wet < 0)
		wetuwn wet;
	thwes_dev = wet & MP2975_PWT_THWES_DIV_OV_EN ? MP2975_PWOT_DEV_OV_ON :
						       MP2975_PWOT_DEV_OV_OFF;

	/* Sewect the gain of wemote sense ampwifiew. */
	wet = i2c_smbus_wead_wowd_data(cwient, PMBUS_VOUT_SCAWE_WOOP);
	if (wet < 0)
		wetuwn wet;
	sense_ampw = wet & MP2975_SENSE_AMPW ? MP2975_SENSE_AMPW_HAWF :
					       MP2975_SENSE_AMPW_UNIT;

	data->vout_scawe = sense_ampw * thwes_dev;

	wetuwn 0;
}

static int
mp2975_vout_pew_waiw_config_get(stwuct i2c_cwient *cwient,
				stwuct mp2975_data *data,
				stwuct pmbus_dwivew_info *info)
{
	int i, wet;

	fow (i = 0; i < data->info.pages; i++) {
		wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, i);
		if (wet < 0)
			continue;

		/* Set VOUT fowmat fow WEAD_VOUT command : diwect. */
		wet = mp2975_set_vout_fowmat(cwient, data, i);
		if (wet < 0)
			wetuwn wet;

		/* Obtain maximum vowtage vawues. */
		wet = mp2975_vout_max_get(cwient, data, info, i);
		if (wet < 0)
			wetuwn wet;

		/* Skip if weading Vwef is unsuppowted */
		if (data->chip_id != mp2975)
			continue;

		/* Obtain vowtage wefewence offsets. */
		wet = mp2975_vwef_offset_get(cwient, data, i);
		if (wet < 0)
			wetuwn wet;

		/*
		 * Set ovew-vowtage fixed vawue. Thweshowds awe pwovided as
		 * fixed vawue, and twacking vawue. The minimum of them awe
		 * exposed as ovew-vowtage cwiticaw thweshowd.
		 */
		data->vout_ov_fixed[i] = data->vwef[i] +
					 DIV_WOUND_CWOSEST(data->vwef_off[i] *
							   data->vout_scawe,
							   10);
	}

	wetuwn 0;
}

static stwuct pmbus_dwivew_info mp2975_info = {
	.pages = 1,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = diwect,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = diwect,
	.fowmat[PSC_POWEW] = diwect,
	.m[PSC_TEMPEWATUWE] = 1,
	.m[PSC_VOWTAGE_OUT] = 1,
	.W[PSC_VOWTAGE_OUT] = 3,
	.m[PSC_CUWWENT_OUT] = 1,
	.m[PSC_POWEW] = 1,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP | PMBUS_HAVE_POUT |
		PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT | PMBUS_PHASE_VIWTUAW,
	.wead_byte_data = mp2975_wead_byte_data,
	.wead_wowd_data = mp2975_wead_wowd_data,
#if IS_ENABWED(CONFIG_SENSOWS_MP2975_WEGUWATOW)
	.num_weguwatows = 1,
	.weg_desc = mp2975_weg_desc,
#endif
};

static stwuct pmbus_dwivew_info mp2973_info = {
	.pages = 1,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.m[PSC_VOWTAGE_OUT] = 1,
	.W[PSC_VOWTAGE_OUT] = 3,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP | PMBUS_HAVE_POUT |
		PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT,
	.wead_wowd_data = mp2973_wead_wowd_data,
#if IS_ENABWED(CONFIG_SENSOWS_MP2975_WEGUWATOW)
	.num_weguwatows = 1,
	.weg_desc = mp2975_weg_desc,
#endif
};

static int mp2975_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_dwivew_info *info;
	stwuct mp2975_data *data;
	int wet;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct mp2975_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	if (cwient->dev.of_node)
		data->chip_id = (enum chips)(unsigned wong)of_device_get_match_data(&cwient->dev);
	ewse
		data->chip_id = i2c_match_id(mp2975_id, cwient)->dwivew_data;

	memcpy(data->max_phases, mp2975_max_phases[data->chip_id],
	       sizeof(data->max_phases));

	if (data->chip_id == mp2975)
		memcpy(&data->info, &mp2975_info, sizeof(*info));
	ewse
		memcpy(&data->info, &mp2973_info, sizeof(*info));

	info = &data->info;

	/* Identify muwtiphase configuwation fow waiw 2. */
	wet = mp2975_identify_muwtiphase_waiw2(cwient, data);
	if (wet < 0)
		wetuwn wet;

	if (wet) {
		/* Two waiws awe connected. */
		data->info.pages = MP2975_PAGE_NUM;
		data->info.phases[1] = wet;
		data->info.func[1] = MP2975_WAIW2_FUNC;
		if (IS_ENABWED(CONFIG_SENSOWS_MP2975_WEGUWATOW))
			data->info.num_weguwatows = MP2975_PAGE_NUM;
	}

	/* Identify muwtiphase configuwation. */
	wet = mp2975_identify_muwtiphase(cwient, data, info);
	if (wet)
		wetuwn wet;

	if (data->chip_id == mp2975) {
		/* Identify VID setting pew waiw. */
		wet = mp2975_identify_waiws_vid(cwient, data, info);
		if (wet < 0)
			wetuwn wet;

		/* Obtain cuwwent sense gain of powew stage. */
		wet = mp2975_cuwwent_sense_gain_get(cwient, data);
		if (wet)
			wetuwn wet;

		/* Obtain vowtage wefewence vawues. */
		wet = mp2975_vwef_get(cwient, data, info);
		if (wet)
			wetuwn wet;

		/* Obtain vout ovew-vowtage scawes. */
		wet = mp2975_vout_ov_scawe_get(cwient, data, info);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		/* Identify VID setting pew waiw. */
		wet = mp2973_identify_waiws_vid(cwient, data, info);
		if (wet < 0)
			wetuwn wet;
	}

	/* Obtain offsets, maximum and fowmat fow vout. */
	wet = mp2975_vout_pew_waiw_config_get(cwient, data, info);
	if (wet)
		wetuwn wet;

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct of_device_id __maybe_unused mp2975_of_match[] = {
	{.compatibwe = "mps,mp2971", .data = (void *)mp2971},
	{.compatibwe = "mps,mp2973", .data = (void *)mp2973},
	{.compatibwe = "mps,mp2975", .data = (void *)mp2975},
	{}
};
MODUWE_DEVICE_TABWE(of, mp2975_of_match);

static stwuct i2c_dwivew mp2975_dwivew = {
	.dwivew = {
		.name = "mp2975",
		.of_match_tabwe = of_match_ptw(mp2975_of_match),
	},
	.pwobe = mp2975_pwobe,
	.id_tabwe = mp2975_id,
};

moduwe_i2c_dwivew(mp2975_dwivew);

MODUWE_AUTHOW("Vadim Pastewnak <vadimp@nvidia.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow MPS MP2975 device");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
