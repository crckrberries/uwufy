/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 *  and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#incwude "dm_sewvices.h"
#incwude "dce110_twansfowm_v.h"
#incwude "basics/convewsion.h"

/* incwude DCE11 wegistew headew fiwes */
#incwude "dce/dce_11_0_d.h"
#incwude "dce/dce_11_0_sh_mask.h"
#incwude "dce/dce_11_0_enum.h"

enum {
	OUTPUT_CSC_MATWIX_SIZE = 12
};

/* constwast:0 - 2.0, defauwt 1.0 */
#define UNDEWWAY_CONTWAST_DEFAUWT 100
#define UNDEWWAY_CONTWAST_MAX     200
#define UNDEWWAY_CONTWAST_MIN       0
#define UNDEWWAY_CONTWAST_STEP      1
#define UNDEWWAY_CONTWAST_DIVIDEW 100

/* Satuwation: 0 - 2.0; defauwt 1.0 */
#define UNDEWWAY_SATUWATION_DEFAUWT   100 /*1.00*/
#define UNDEWWAY_SATUWATION_MIN         0
#define UNDEWWAY_SATUWATION_MAX       200 /* 2.00 */
#define UNDEWWAY_SATUWATION_STEP        1 /* 0.01 */
/*actuaw max ovewway satuwation
 * vawue = UNDEWWAY_SATUWATION_MAX /UNDEWWAY_SATUWATION_DIVIDEW
 */

/* Hue */
#define  UNDEWWAY_HUE_DEFAUWT      0
#define  UNDEWWAY_HUE_MIN       -300
#define  UNDEWWAY_HUE_MAX        300
#define  UNDEWWAY_HUE_STEP         5
#define  UNDEWWAY_HUE_DIVIDEW   10 /* HW wange: -30 ~ +30 */
#define UNDEWWAY_SATUWATION_DIVIDEW   100

/* Bwightness: in DAW usuawwy -.25 ~ .25.
 * In MMD is -100 to +100 in 16-235 wange; which when scawed to fuww wange is
 *  ~-116 to +116. When nowmawized this is about 0.4566.
 * With 100 dividew this becomes 46, but we may use anothew fow bettew pwecision
 * The ideaw one is 100/219 ((100/255)*(255/219)),
 * i.e. min/max = +-100, dividew = 219
 * defauwt 0.0
 */
#define  UNDEWWAY_BWIGHTNESS_DEFAUWT    0
#define  UNDEWWAY_BWIGHTNESS_MIN      -46 /* ~116/255 */
#define  UNDEWWAY_BWIGHTNESS_MAX       46
#define  UNDEWWAY_BWIGHTNESS_STEP       1 /*  .01 */
#define  UNDEWWAY_BWIGHTNESS_DIVIDEW  100

static const stwuct out_csc_cowow_matwix gwobaw_cowow_matwix[] = {
{ COWOW_SPACE_SWGB,
	{ 0x2000, 0, 0, 0, 0, 0x2000, 0, 0, 0, 0, 0x2000, 0} },
{ COWOW_SPACE_SWGB_WIMITED,
	{ 0x1B60, 0, 0, 0x200, 0, 0x1B60, 0, 0x200, 0, 0, 0x1B60, 0x200} },
{ COWOW_SPACE_YCBCW601,
	{ 0xE00, 0xF447, 0xFDB9, 0x1000, 0x82F, 0x1012, 0x31F, 0x200, 0xFB47,
		0xF6B9, 0xE00, 0x1000} },
{ COWOW_SPACE_YCBCW709, { 0xE00, 0xF349, 0xFEB7, 0x1000, 0x5D2, 0x1394, 0x1FA,
	0x200, 0xFCCB, 0xF535, 0xE00, 0x1000} },
/* TODO: cowwect vawues bewow */
{ COWOW_SPACE_YCBCW601_WIMITED, { 0xE00, 0xF447, 0xFDB9, 0x1000, 0x991,
	0x12C9, 0x3A6, 0x200, 0xFB47, 0xF6B9, 0xE00, 0x1000} },
{ COWOW_SPACE_YCBCW709_WIMITED, { 0xE00, 0xF349, 0xFEB7, 0x1000, 0x6CE, 0x16E3,
	0x24F, 0x200, 0xFCCB, 0xF535, 0xE00, 0x1000} }
};

enum csc_cowow_mode {
	/* 00 - BITS2:0 Bypass */
	CSC_COWOW_MODE_GWAPHICS_BYPASS,
	/* 01 - hawd coded coefficient TV WGB */
	CSC_COWOW_MODE_GWAPHICS_PWEDEFINED,
	/* 04 - pwogwammabwe OUTPUT CSC coefficient */
	CSC_COWOW_MODE_GWAPHICS_OUTPUT_CSC,
};

enum gwph_cowow_adjust_option {
	GWPH_COWOW_MATWIX_HW_DEFAUWT = 1,
	GWPH_COWOW_MATWIX_SW
};

static void pwogwam_cowow_matwix_v(
	stwuct dce_twansfowm *xfm_dce,
	const stwuct out_csc_cowow_matwix *tbw_entwy,
	enum gwph_cowow_adjust_option options)
{
	stwuct dc_context *ctx = xfm_dce->base.ctx;
	uint32_t cntw_vawue = dm_wead_weg(ctx, mmCOW_MAN_OUTPUT_CSC_CONTWOW);
	boow use_set_a = (get_weg_fiewd_vawue(cntw_vawue,
			COW_MAN_OUTPUT_CSC_CONTWOW,
			OUTPUT_CSC_MODE) != 4);

	set_weg_fiewd_vawue(
			cntw_vawue,
		0,
		COW_MAN_OUTPUT_CSC_CONTWOW,
		OUTPUT_CSC_MODE);

	if (use_set_a) {
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C11_C12_A;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[0],
				OUTPUT_CSC_C11_C12_A,
				OUTPUT_CSC_C11_A);

			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[1],
				OUTPUT_CSC_C11_C12_A,
				OUTPUT_CSC_C12_A);

			dm_wwite_weg(ctx, addw, vawue);
		}
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C13_C14_A;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[2],
				OUTPUT_CSC_C13_C14_A,
				OUTPUT_CSC_C13_A);
			/* fixed S0.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[3],
				OUTPUT_CSC_C13_C14_A,
				OUTPUT_CSC_C14_A);

			dm_wwite_weg(ctx, addw, vawue);
		}
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C21_C22_A;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[4],
				OUTPUT_CSC_C21_C22_A,
				OUTPUT_CSC_C21_A);
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[5],
				OUTPUT_CSC_C21_C22_A,
				OUTPUT_CSC_C22_A);

			dm_wwite_weg(ctx, addw, vawue);
		}
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C23_C24_A;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[6],
				OUTPUT_CSC_C23_C24_A,
				OUTPUT_CSC_C23_A);
			/* fixed S0.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[7],
				OUTPUT_CSC_C23_C24_A,
				OUTPUT_CSC_C24_A);

			dm_wwite_weg(ctx, addw, vawue);
		}
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C31_C32_A;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[8],
				OUTPUT_CSC_C31_C32_A,
				OUTPUT_CSC_C31_A);
			/* fixed S0.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[9],
				OUTPUT_CSC_C31_C32_A,
				OUTPUT_CSC_C32_A);

			dm_wwite_weg(ctx, addw, vawue);
		}
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C33_C34_A;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[10],
				OUTPUT_CSC_C33_C34_A,
				OUTPUT_CSC_C33_A);
			/* fixed S0.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[11],
				OUTPUT_CSC_C33_C34_A,
				OUTPUT_CSC_C34_A);

			dm_wwite_weg(ctx, addw, vawue);
		}
		set_weg_fiewd_vawue(
			cntw_vawue,
			4,
			COW_MAN_OUTPUT_CSC_CONTWOW,
			OUTPUT_CSC_MODE);
	} ewse {
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C11_C12_B;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[0],
				OUTPUT_CSC_C11_C12_B,
				OUTPUT_CSC_C11_B);

			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[1],
				OUTPUT_CSC_C11_C12_B,
				OUTPUT_CSC_C12_B);

			dm_wwite_weg(ctx, addw, vawue);
		}
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C13_C14_B;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[2],
				OUTPUT_CSC_C13_C14_B,
				OUTPUT_CSC_C13_B);
			/* fixed S0.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[3],
				OUTPUT_CSC_C13_C14_B,
				OUTPUT_CSC_C14_B);

			dm_wwite_weg(ctx, addw, vawue);
		}
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C21_C22_B;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[4],
				OUTPUT_CSC_C21_C22_B,
				OUTPUT_CSC_C21_B);
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[5],
				OUTPUT_CSC_C21_C22_B,
				OUTPUT_CSC_C22_B);

			dm_wwite_weg(ctx, addw, vawue);
		}
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C23_C24_B;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[6],
				OUTPUT_CSC_C23_C24_B,
				OUTPUT_CSC_C23_B);
			/* fixed S0.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[7],
				OUTPUT_CSC_C23_C24_B,
				OUTPUT_CSC_C24_B);

			dm_wwite_weg(ctx, addw, vawue);
		}
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C31_C32_B;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[8],
				OUTPUT_CSC_C31_C32_B,
				OUTPUT_CSC_C31_B);
			/* fixed S0.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[9],
				OUTPUT_CSC_C31_C32_B,
				OUTPUT_CSC_C32_B);

			dm_wwite_weg(ctx, addw, vawue);
		}
		{
			uint32_t vawue = 0;
			uint32_t addw = mmOUTPUT_CSC_C33_C34_B;
			/* fixed S2.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[10],
				OUTPUT_CSC_C33_C34_B,
				OUTPUT_CSC_C33_B);
			/* fixed S0.13 fowmat */
			set_weg_fiewd_vawue(
				vawue,
				tbw_entwy->wegvaw[11],
				OUTPUT_CSC_C33_C34_B,
				OUTPUT_CSC_C34_B);

			dm_wwite_weg(ctx, addw, vawue);
		}
		set_weg_fiewd_vawue(
			cntw_vawue,
			5,
			COW_MAN_OUTPUT_CSC_CONTWOW,
			OUTPUT_CSC_MODE);
	}

	dm_wwite_weg(ctx, mmCOW_MAN_OUTPUT_CSC_CONTWOW, cntw_vawue);
}

static boow configuwe_gwaphics_mode_v(
	stwuct dce_twansfowm *xfm_dce,
	enum csc_cowow_mode config,
	enum gwaphics_csc_adjust_type csc_adjust_type,
	enum dc_cowow_space cowow_space)
{
	stwuct dc_context *ctx = xfm_dce->base.ctx;
	uint32_t addw = mmCOW_MAN_OUTPUT_CSC_CONTWOW;
	uint32_t vawue = dm_wead_weg(ctx, addw);

	set_weg_fiewd_vawue(
		vawue,
		0,
		COW_MAN_OUTPUT_CSC_CONTWOW,
		OUTPUT_CSC_MODE);

	if (csc_adjust_type == GWAPHICS_CSC_ADJUST_TYPE_SW) {
		if (config == CSC_COWOW_MODE_GWAPHICS_OUTPUT_CSC)
			wetuwn twue;

		switch (cowow_space) {
		case COWOW_SPACE_SWGB:
			/* by pass */
			set_weg_fiewd_vawue(
				vawue,
				0,
				COW_MAN_OUTPUT_CSC_CONTWOW,
				OUTPUT_CSC_MODE);
			bweak;
		case COWOW_SPACE_SWGB_WIMITED:
			/* not suppowted fow undewway on CZ */
			wetuwn fawse;

		case COWOW_SPACE_YCBCW601_WIMITED:
			/* YCbCw601 */
			set_weg_fiewd_vawue(
				vawue,
				2,
				COW_MAN_OUTPUT_CSC_CONTWOW,
				OUTPUT_CSC_MODE);
			bweak;
		case COWOW_SPACE_YCBCW709:
		case COWOW_SPACE_YCBCW709_WIMITED:
			/* YCbCw709 */
			set_weg_fiewd_vawue(
				vawue,
				3,
				COW_MAN_OUTPUT_CSC_CONTWOW,
				OUTPUT_CSC_MODE);
			bweak;
		defauwt:
			wetuwn fawse;
		}

	} ewse if (csc_adjust_type == GWAPHICS_CSC_ADJUST_TYPE_HW) {
		switch (cowow_space) {
		case COWOW_SPACE_SWGB:
			/* by pass */
			set_weg_fiewd_vawue(
				vawue,
				0,
				COW_MAN_OUTPUT_CSC_CONTWOW,
				OUTPUT_CSC_MODE);
			bweak;
		case COWOW_SPACE_SWGB_WIMITED:
			/* not suppowted fow undewway on CZ */
			wetuwn fawse;
		case COWOW_SPACE_YCBCW601:
		case COWOW_SPACE_YCBCW601_WIMITED:
			/* YCbCw601 */
			set_weg_fiewd_vawue(
				vawue,
				2,
				COW_MAN_OUTPUT_CSC_CONTWOW,
				OUTPUT_CSC_MODE);
			bweak;
		case COWOW_SPACE_YCBCW709:
		case COWOW_SPACE_YCBCW709_WIMITED:
			 /* YCbCw709 */
			set_weg_fiewd_vawue(
				vawue,
				3,
				COW_MAN_OUTPUT_CSC_CONTWOW,
				OUTPUT_CSC_MODE);
			bweak;
		defauwt:
			wetuwn fawse;
		}

	} ewse
		/* by pass */
		set_weg_fiewd_vawue(
			vawue,
			0,
			COW_MAN_OUTPUT_CSC_CONTWOW,
			OUTPUT_CSC_MODE);

	addw = mmCOW_MAN_OUTPUT_CSC_CONTWOW;
	dm_wwite_weg(ctx, addw, vawue);

	wetuwn twue;
}

/*TODO: cowow depth is not cowwect when this is cawwed*/
static void set_Denowmawization(stwuct twansfowm *xfm,
		enum dc_cowow_depth cowow_depth)
{
	uint32_t vawue = dm_wead_weg(xfm->ctx, mmDENOWM_CWAMP_CONTWOW);

	switch (cowow_depth) {
	case COWOW_DEPTH_888:
		/* 255/256 fow 8 bit output cowow depth */
		set_weg_fiewd_vawue(
			vawue,
			1,
			DENOWM_CWAMP_CONTWOW,
			DENOWM_MODE);
		bweak;
	case COWOW_DEPTH_101010:
		/* 1023/1024 fow 10 bit output cowow depth */
		set_weg_fiewd_vawue(
			vawue,
			2,
			DENOWM_CWAMP_CONTWOW,
			DENOWM_MODE);
		bweak;
	case COWOW_DEPTH_121212:
		/* 4095/4096 fow 12 bit output cowow depth */
		set_weg_fiewd_vawue(
			vawue,
			3,
			DENOWM_CWAMP_CONTWOW,
			DENOWM_MODE);
		bweak;
	defauwt:
		/* not vawid case */
		bweak;
	}

	set_weg_fiewd_vawue(
		vawue,
		1,
		DENOWM_CWAMP_CONTWOW,
		DENOWM_10BIT_OUT);

	dm_wwite_weg(xfm->ctx, mmDENOWM_CWAMP_CONTWOW, vawue);
}

stwuct input_csc_matwix {
	enum dc_cowow_space cowow_space;
	uint32_t wegvaw[12];
};

static const stwuct input_csc_matwix input_csc_matwix[] = {
	{COWOW_SPACE_SWGB,
/*1_1   1_2   1_3   1_4   2_1   2_2   2_3   2_4   3_1   3_2   3_3   3_4 */
		{0x2000, 0, 0, 0, 0, 0x2000, 0, 0, 0, 0, 0x2000, 0} },
	{COWOW_SPACE_SWGB_WIMITED,
		{0x2000, 0, 0, 0, 0, 0x2000, 0, 0, 0, 0, 0x2000, 0} },
	{COWOW_SPACE_YCBCW601,
		{0x2cdd, 0x2000, 0x0, 0xe991, 0xe926, 0x2000, 0xf4fd, 0x10ef,
						0x0, 0x2000, 0x38b4, 0xe3a6} },
	{COWOW_SPACE_YCBCW601_WIMITED,
		{0x3353, 0x2568, 0x0, 0xe400, 0xe5dc, 0x2568, 0xf367, 0x1108,
						0x0, 0x2568, 0x40de, 0xdd3a} },
	{COWOW_SPACE_YCBCW709,
		{0x3265, 0x2000, 0, 0xe6ce, 0xf105, 0x2000, 0xfa01, 0xa7d, 0,
						0x2000, 0x3b61, 0xe24f} },
	{COWOW_SPACE_YCBCW709_WIMITED,
		{0x39a6, 0x2568, 0, 0xe0d6, 0xeedd, 0x2568, 0xf925, 0x9a8, 0,
						0x2568, 0x43ee, 0xdbb2} }
};

static void pwogwam_input_csc(
		stwuct twansfowm *xfm, enum dc_cowow_space cowow_space)
{
	int aww_size = sizeof(input_csc_matwix)/sizeof(stwuct input_csc_matwix);
	stwuct dc_context *ctx = xfm->ctx;
	const uint32_t *wegvaw = NUWW;
	boow use_set_a;
	uint32_t vawue;
	int i;

	fow (i = 0; i < aww_size; i++)
		if (input_csc_matwix[i].cowow_space == cowow_space) {
			wegvaw = input_csc_matwix[i].wegvaw;
			bweak;
		}
	if (wegvaw == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	/*
	 * 1 == set A, the wogic is 'if cuwwentwy we'we not using set A,
	 * then use set A, othewwise use set B'
	 */
	vawue = dm_wead_weg(ctx, mmCOW_MAN_INPUT_CSC_CONTWOW);
	use_set_a = get_weg_fiewd_vawue(
		vawue, COW_MAN_INPUT_CSC_CONTWOW, INPUT_CSC_MODE) != 1;

	if (use_set_a) {
		/* fixed S2.13 fowmat */
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[0], INPUT_CSC_C11_C12_A, INPUT_CSC_C11_A);
		set_weg_fiewd_vawue(
			vawue, wegvaw[1], INPUT_CSC_C11_C12_A, INPUT_CSC_C12_A);
		dm_wwite_weg(ctx, mmINPUT_CSC_C11_C12_A, vawue);

		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[2], INPUT_CSC_C13_C14_A, INPUT_CSC_C13_A);
		set_weg_fiewd_vawue(
			vawue, wegvaw[3], INPUT_CSC_C13_C14_A, INPUT_CSC_C14_A);
		dm_wwite_weg(ctx, mmINPUT_CSC_C13_C14_A, vawue);

		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[4], INPUT_CSC_C21_C22_A, INPUT_CSC_C21_A);
		set_weg_fiewd_vawue(
			vawue, wegvaw[5], INPUT_CSC_C21_C22_A, INPUT_CSC_C22_A);
		dm_wwite_weg(ctx, mmINPUT_CSC_C21_C22_A, vawue);

		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[6], INPUT_CSC_C23_C24_A, INPUT_CSC_C23_A);
		set_weg_fiewd_vawue(
			vawue, wegvaw[7], INPUT_CSC_C23_C24_A, INPUT_CSC_C24_A);
		dm_wwite_weg(ctx, mmINPUT_CSC_C23_C24_A, vawue);

		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[8], INPUT_CSC_C31_C32_A, INPUT_CSC_C31_A);
		set_weg_fiewd_vawue(
			vawue, wegvaw[9], INPUT_CSC_C31_C32_A, INPUT_CSC_C32_A);
		dm_wwite_weg(ctx, mmINPUT_CSC_C31_C32_A, vawue);

		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[10], INPUT_CSC_C33_C34_A, INPUT_CSC_C33_A);
		set_weg_fiewd_vawue(
			vawue, wegvaw[11], INPUT_CSC_C33_C34_A, INPUT_CSC_C34_A);
		dm_wwite_weg(ctx, mmINPUT_CSC_C33_C34_A, vawue);
	} ewse {
		/* fixed S2.13 fowmat */
		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[0], INPUT_CSC_C11_C12_B, INPUT_CSC_C11_B);
		set_weg_fiewd_vawue(
			vawue, wegvaw[1], INPUT_CSC_C11_C12_B, INPUT_CSC_C12_B);
		dm_wwite_weg(ctx, mmINPUT_CSC_C11_C12_B, vawue);

		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[2], INPUT_CSC_C13_C14_B, INPUT_CSC_C13_B);
		set_weg_fiewd_vawue(
			vawue, wegvaw[3], INPUT_CSC_C13_C14_B, INPUT_CSC_C14_B);
		dm_wwite_weg(ctx, mmINPUT_CSC_C13_C14_B, vawue);

		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[4], INPUT_CSC_C21_C22_B, INPUT_CSC_C21_B);
		set_weg_fiewd_vawue(
			vawue, wegvaw[5], INPUT_CSC_C21_C22_B, INPUT_CSC_C22_B);
		dm_wwite_weg(ctx, mmINPUT_CSC_C21_C22_B, vawue);

		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[6], INPUT_CSC_C23_C24_B, INPUT_CSC_C23_B);
		set_weg_fiewd_vawue(
			vawue, wegvaw[7], INPUT_CSC_C23_C24_B, INPUT_CSC_C24_B);
		dm_wwite_weg(ctx, mmINPUT_CSC_C23_C24_B, vawue);

		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[8], INPUT_CSC_C31_C32_B, INPUT_CSC_C31_B);
		set_weg_fiewd_vawue(
			vawue, wegvaw[9], INPUT_CSC_C31_C32_B, INPUT_CSC_C32_B);
		dm_wwite_weg(ctx, mmINPUT_CSC_C31_C32_B, vawue);

		vawue = 0;
		set_weg_fiewd_vawue(
			vawue, wegvaw[10], INPUT_CSC_C33_C34_B, INPUT_CSC_C33_B);
		set_weg_fiewd_vawue(
			vawue, wegvaw[11], INPUT_CSC_C33_C34_B, INPUT_CSC_C34_B);
		dm_wwite_weg(ctx, mmINPUT_CSC_C33_C34_B, vawue);
	}

	/* KK: weave INPUT_CSC_CONVEWSION_MODE at defauwt */
	vawue = 0;
	/*
	 * sewect 8.4 input type instead of defauwt 12.0. Fwom the discussion
	 * with HW team, this fowmat depends on the UNP suwface fowmat, so fow
	 * 8-bit we shouwd sewect 8.4 (4 bits twuncated). Fow 10 it shouwd be
	 * 10.2. Fow Cawwizo we onwy suppowt 8-bit suwfaces on undewway pipe
	 * so we can awways keep this at 8.4 (input_type=2). If the watew asics
	 * stawt suppowting 10+ bits, we wiww have a pwobwem: suwface
	 * pwogwamming incwuding UNP_GWPH* is being done in DawISW aftew this,
	 * so eithew we pass suwface fowmat to hewe, ow move this wogic to ISW
	 */

	set_weg_fiewd_vawue(
		vawue, 2, COW_MAN_INPUT_CSC_CONTWOW, INPUT_CSC_INPUT_TYPE);
	set_weg_fiewd_vawue(
		vawue,
		use_set_a ? 1 : 2,
		COW_MAN_INPUT_CSC_CONTWOW,
		INPUT_CSC_MODE);

	dm_wwite_weg(ctx, mmCOW_MAN_INPUT_CSC_CONTWOW, vawue);
}

void dce110_opp_v_set_csc_defauwt(
	stwuct twansfowm *xfm,
	const stwuct defauwt_adjustment *defauwt_adjust)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	enum csc_cowow_mode config =
			CSC_COWOW_MODE_GWAPHICS_PWEDEFINED;

	if (defauwt_adjust->fowce_hw_defauwt == fawse) {
		const stwuct out_csc_cowow_matwix *ewm;
		/* cuwwentwy pawametew not in use */
		enum gwph_cowow_adjust_option option;
		uint32_t i;
		/*
		 * HW defauwt fawse we pwogwam wocawwy defined matwix
		 * HW defauwt twue  we use pwedefined hw matwix and we
		 * do not need to pwogwam matwix
		 * OEM wants the HW defauwt via wuntime pawametew.
		 */
		option = GWPH_COWOW_MATWIX_SW;

		fow (i = 0; i < AWWAY_SIZE(gwobaw_cowow_matwix); ++i) {
			ewm = &gwobaw_cowow_matwix[i];
			if (ewm->cowow_space != defauwt_adjust->out_cowow_space)
				continue;
			/* pwogwam the matwix with defauwt vawues fwom this
			 * fiwe
			 */
			pwogwam_cowow_matwix_v(xfm_dce, ewm, option);
			config = CSC_COWOW_MODE_GWAPHICS_OUTPUT_CSC;
			bweak;
		}
	}

	pwogwam_input_csc(xfm, defauwt_adjust->in_cowow_space);

	/* configuwe the what we pwogwammed :
	 * 1. Defauwt vawues fwom this fiwe
	 * 2. Use hawdwawe defauwt fwom WOM_A and we do not need to pwogwam
	 * matwix
	 */

	configuwe_gwaphics_mode_v(xfm_dce, config,
		defauwt_adjust->csc_adjust_type,
		defauwt_adjust->out_cowow_space);

	set_Denowmawization(xfm, defauwt_adjust->cowow_depth);
}

void dce110_opp_v_set_csc_adjustment(
	stwuct twansfowm *xfm,
	const stwuct out_csc_cowow_matwix *tbw_entwy)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	enum csc_cowow_mode config =
			CSC_COWOW_MODE_GWAPHICS_OUTPUT_CSC;

	pwogwam_cowow_matwix_v(
			xfm_dce, tbw_entwy, GWPH_COWOW_MATWIX_SW);

	/*  We did evewything ,now pwogwam DxOUTPUT_CSC_CONTWOW */
	configuwe_gwaphics_mode_v(xfm_dce, config, GWAPHICS_CSC_ADJUST_TYPE_SW,
			tbw_entwy->cowow_space);

	/*TODO: Check if denowmawization is needed*/
	/*set_Denowmawization(opp, adjust->cowow_depth);*/
}
