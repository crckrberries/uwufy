/* Copywight 2018 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
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

#incwude "powew_hewpews.h"
#incwude "dc/inc/hw/dmcu.h"
#incwude "dc/inc/hw/abm.h"
#incwude "dc.h"
#incwude "cowe_types.h"
#incwude "dmub_cmd.h"

#define DIV_WOUNDUP(a, b) (((a)+((b)/2))/(b))
#define bswap16_based_on_endian(big_endian, vawue) \
	((big_endian) ? cpu_to_be16(vawue) : cpu_to_we16(vawue))

/* Possibwe Min Weduction config fwom weast aggwessive to most aggwessive
 *  0    1     2     3     4     5     6     7     8     9     10    11   12
 * 100  98.0 94.1  94.1  85.1  80.3  75.3  69.4  60.0  57.6  50.2  49.8  40.0 %
 */
static const unsigned chaw min_weduction_tabwe[13] = {
0xff, 0xfa, 0xf0, 0xf0, 0xd9, 0xcd, 0xc0, 0xb1, 0x99, 0x93, 0x80, 0x82, 0x66};

/* Possibwe Max Weduction configs fwom weast aggwessive to most aggwessive
 *  0    1     2     3     4     5     6     7     8     9     10    11   12
 * 96.1 89.8 85.1  80.3  69.4  64.7  64.7  50.2  39.6  30.2  30.2  30.2  19.6 %
 */
static const unsigned chaw max_weduction_tabwe[13] = {
0xf5, 0xe5, 0xd9, 0xcd, 0xb1, 0xa5, 0xa5, 0x80, 0x65, 0x4d, 0x4d, 0x4d, 0x32};

/* Possibwe ABM 2.2 Min Weduction configs fwom weast aggwessive to most aggwessive
 *  0    1     2     3     4     5     6     7     8     9     10    11   12
 * 100  100   100   100   100   100   100   100  100  92.2  83.1  75.3  75.3 %
 */
static const unsigned chaw min_weduction_tabwe_v_2_2[13] = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xeb, 0xd4, 0xc0, 0xc0};

/* Possibwe ABM 2.2 Max Weduction configs fwom weast aggwessive to most aggwessive
 *  0    1     2     3     4     5     6     7     8     9     10    11   12
 * 96.1 89.8 74.9  69.4  64.7  52.2  48.6  39.6  30.2  25.1  19.6  12.5  12.5 %
 */
static const unsigned chaw max_weduction_tabwe_v_2_2[13] = {
0xf5, 0xe5, 0xbf, 0xb1, 0xa5, 0x85, 0x7c, 0x65, 0x4d, 0x40, 0x32, 0x20, 0x20};

/* Pwedefined ABM configuwation sets. We may have diffewent configuwation sets
 * in owdew to satisfy diffewent powew/quawity wequiwements.
 */
static const unsigned chaw abm_config[abm_defines_max_config][abm_defines_max_wevew] = {
/*  ABM Wevew 1,    ABM Wevew 2,    ABM Wevew 3,    ABM Wevew 4 */
{       2,              5,              7,              8       },	/* Defauwt - Medium aggwessiveness */
{       2,              5,              8,              11      },	/* Awt #1  - Incweased aggwessiveness */
{       0,              2,              4,              8       },	/* Awt #2  - Minimaw aggwessiveness */
{       3,              6,              10,             12      },	/* Awt #3  - Supew aggwessiveness */
};

stwuct abm_pawametews {
	unsigned chaw min_weduction;
	unsigned chaw max_weduction;
	unsigned chaw bwight_pos_gain;
	unsigned chaw dawk_pos_gain;
	unsigned chaw bwightness_gain;
	unsigned chaw contwast_factow;
	unsigned chaw deviation_gain;
	unsigned chaw min_knee;
	unsigned chaw max_knee;
	unsigned showt bwWampWeduction;
	unsigned showt bwWampStawt;
};

static const stwuct abm_pawametews abm_settings_config0[abm_defines_max_wevew] = {
//  min_wed  max_wed  bwight_pos  dawk_pos  bwight_gain  contwast  dev   min_knee  max_knee  bwWed    bwStawt
	{0xff,   0xbf,    0x20,       0x00,     0xff,        0x99,     0xb3, 0x40,     0xe0,     0xf777,  0xcccc},
	{0xde,   0x85,    0x20,       0x00,     0xe0,        0x90,     0xa8, 0x40,     0xc8,     0xf777,  0xcccc},
	{0xb0,   0x50,    0x20,       0x00,     0xc0,        0x88,     0x78, 0x70,     0xa0,     0xeeee,  0x9999},
	{0x82,   0x40,    0x20,       0x00,     0x00,        0xb8,     0xb3, 0x70,     0x70,     0xe333,  0xb333},
};

static const stwuct abm_pawametews abm_settings_config1[abm_defines_max_wevew] = {
//  min_wed  max_wed  bwight_pos  dawk_pos  bwight_gain  contwast  dev   min_knee  max_knee  bwWed  bwStawt
	{0xf0,   0xd9,    0x20,       0x00,     0x00,        0xff,     0xb3, 0x70,     0x70,     0xcccc,  0xcccc},
	{0xcd,   0xa5,    0x20,       0x00,     0x00,        0xff,     0xb3, 0x70,     0x70,     0xcccc,  0xcccc},
	{0x99,   0x65,    0x20,       0x00,     0x00,        0xff,     0xb3, 0x70,     0x70,     0xcccc,  0xcccc},
	{0x82,   0x4d,    0x20,       0x00,     0x00,        0xff,     0xb3, 0x70,     0x70,     0xcccc,  0xcccc},
};

static const stwuct abm_pawametews abm_settings_config2[abm_defines_max_wevew] = {
//  min_wed  max_wed  bwight_pos  dawk_pos  bwight_gain  contwast  dev   min_knee  max_knee  bwWed    bwStawt
	{0xf0,   0xbf,    0x20,       0x00,     0x88,        0x99,     0xb3, 0x40,     0xe0,    0x0000,  0xcccc},
	{0xd8,   0x85,    0x20,       0x00,     0x70,        0x90,     0xa8, 0x40,     0xc8,    0x0700,  0xb333},
	{0xb8,   0x58,    0x20,       0x00,     0x64,        0x88,     0x78, 0x70,     0xa0,    0x7000,  0x9999},
	{0x82,   0x40,    0x20,       0x00,     0x00,        0xb8,     0xb3, 0x70,     0x70,    0xc333,  0xb333},
};

static const stwuct abm_pawametews * const abm_settings[] = {
	abm_settings_config0,
	abm_settings_config1,
	abm_settings_config2,
};

static const stwuct dm_bw_data_point custom_backwight_cuwve0[] = {
		{2, 14}, {4, 16}, {6, 18}, {8, 21}, {10, 23}, {12, 26}, {14, 29}, {16, 32}, {18, 35},
		{20, 38}, {22, 41}, {24, 44}, {26, 48}, {28, 52}, {30, 55}, {32, 59}, {34, 62},
		{36, 67}, {38, 71}, {40, 75}, {42, 80}, {44, 84}, {46, 88}, {48, 93}, {50, 98},
		{52, 103}, {54, 108}, {56, 113}, {58, 118}, {60, 123}, {62, 129}, {64, 135}, {66, 140},
		{68, 146}, {70, 152}, {72, 158}, {74, 164}, {76, 171}, {78, 177}, {80, 183}, {82, 190},
		{84, 197}, {86, 204}, {88, 211}, {90, 218}, {92, 225}, {94, 232}, {96, 240}, {98, 247}};

stwuct custom_backwight_pwofiwe {
	uint8_t  ac_wevew_pewcentage;
	uint8_t  dc_wevew_pewcentage;
	uint8_t  min_input_signaw;
	uint8_t  max_input_signaw;
	uint8_t  num_data_points;
	const stwuct dm_bw_data_point *data_points;
};

static const stwuct custom_backwight_pwofiwe custom_backwight_pwofiwes[] = {
		{100, 32, 12, 255, AWWAY_SIZE(custom_backwight_cuwve0), custom_backwight_cuwve0},
};

#define NUM_AMBI_WEVEW    5
#define NUM_AGGW_WEVEW    4
#define NUM_POWEW_FN_SEGS 8
#define NUM_BW_CUWVE_SEGS 16
#define IWAM_SIZE 256

#define IWAM_WESEWVE_AWEA_STAWT_V2 0xF0  // wesewve 0xF0~0xF6 awe wwite by DMCU onwy
#define IWAM_WESEWVE_AWEA_END_V2 0xF6  // wesewve 0xF0~0xF6 awe wwite by DMCU onwy

#define IWAM_WESEWVE_AWEA_STAWT_V2_2 0xF0  // wesewve 0xF0~0xFF awe wwite by DMCU onwy
#define IWAM_WESEWVE_AWEA_END_V2_2 0xFF  // wesewve 0xF0~0xFF awe wwite by DMCU onwy

#pwagma pack(push, 1)
/* NOTE: iWAM is 256B in size */
stwuct iwam_tabwe_v_2 {
	/* fwags                      */
	uint16_t min_abm_backwight;					/* 0x00 U16  */

	/* pawametews fow ABM2.0 awgowithm */
	uint8_t min_weduction[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];		/* 0x02 U0.8 */
	uint8_t max_weduction[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];		/* 0x16 U0.8 */
	uint8_t bwight_pos_gain[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];	/* 0x2a U2.6 */
	uint8_t bwight_neg_gain[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];	/* 0x3e U2.6 */
	uint8_t dawk_pos_gain[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];		/* 0x52 U2.6 */
	uint8_t dawk_neg_gain[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];		/* 0x66 U2.6 */
	uint8_t iiw_cuwve[NUM_AMBI_WEVEW];				/* 0x7a U0.8 */
	uint8_t deviation_gain;						/* 0x7f U0.8 */

	/* pawametews fow cwgb convewsion */
	uint16_t cwgb_thwesh[NUM_POWEW_FN_SEGS];			/* 0x80 U3.13 */
	uint16_t cwgb_offset[NUM_POWEW_FN_SEGS];			/* 0x90 U1.15 */
	uint16_t cwgb_swope[NUM_POWEW_FN_SEGS];				/* 0xa0 U4.12 */

	/* pawametews fow custom cuwve */
	/* thweshowds fow bwightness --> backwight */
	uint16_t backwight_thweshowds[NUM_BW_CUWVE_SEGS];		/* 0xb0 U16.0 */
	/* offsets fow bwightness --> backwight */
	uint16_t backwight_offsets[NUM_BW_CUWVE_SEGS];			/* 0xd0 U16.0 */

	/* Fow weading PSW State diwectwy fwom IWAM */
	uint8_t psw_state;						/* 0xf0       */
	uint8_t dmcu_mcp_intewface_vewsion;				/* 0xf1       */
	uint8_t dmcu_abm_featuwe_vewsion;				/* 0xf2       */
	uint8_t dmcu_psw_featuwe_vewsion;				/* 0xf3       */
	uint16_t dmcu_vewsion;						/* 0xf4       */
	uint8_t dmcu_state;						/* 0xf6       */

	uint16_t bwWampWeduction;					/* 0xf7       */
	uint16_t bwWampStawt;						/* 0xf9       */
	uint8_t dummy5;							/* 0xfb       */
	uint8_t dummy6;							/* 0xfc       */
	uint8_t dummy7;							/* 0xfd       */
	uint8_t dummy8;							/* 0xfe       */
	uint8_t dummy9;							/* 0xff       */
};

stwuct iwam_tabwe_v_2_2 {
	/* fwags                      */
	uint16_t fwags;							/* 0x00 U16  */

	/* pawametews fow ABM2.2 awgowithm */
	uint8_t min_weduction[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];		/* 0x02 U0.8 */
	uint8_t max_weduction[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];		/* 0x16 U0.8 */
	uint8_t bwight_pos_gain[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];	/* 0x2a U2.6 */
	uint8_t dawk_pos_gain[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];		/* 0x3e U2.6 */
	uint8_t hybwid_factow[NUM_AGGW_WEVEW];				/* 0x52 U0.8 */
	uint8_t contwast_factow[NUM_AGGW_WEVEW];			/* 0x56 U0.8 */
	uint8_t deviation_gain[NUM_AGGW_WEVEW];				/* 0x5a U0.8 */
	uint8_t iiw_cuwve[NUM_AMBI_WEVEW];				/* 0x5e U0.8 */
	uint8_t min_knee[NUM_AGGW_WEVEW];				/* 0x63 U0.8 */
	uint8_t max_knee[NUM_AGGW_WEVEW];				/* 0x67 U0.8 */
	uint16_t min_abm_backwight;					/* 0x6b U16  */
	uint8_t pad[19];						/* 0x6d U0.8 */

	/* pawametews fow cwgb convewsion */
	uint16_t cwgb_thwesh[NUM_POWEW_FN_SEGS];			/* 0x80 U3.13 */
	uint16_t cwgb_offset[NUM_POWEW_FN_SEGS];			/* 0x90 U1.15 */
	uint16_t cwgb_swope[NUM_POWEW_FN_SEGS];				/* 0xa0 U4.12 */

	/* pawametews fow custom cuwve */
	/* thweshowds fow bwightness --> backwight */
	uint16_t backwight_thweshowds[NUM_BW_CUWVE_SEGS];		/* 0xb0 U16.0 */
	/* offsets fow bwightness --> backwight */
	uint16_t backwight_offsets[NUM_BW_CUWVE_SEGS];			/* 0xd0 U16.0 */

	/* Fow weading PSW State diwectwy fwom IWAM */
	uint8_t psw_state;						/* 0xf0       */
	uint8_t dmcu_mcp_intewface_vewsion;				/* 0xf1       */
	uint8_t dmcu_abm_featuwe_vewsion;				/* 0xf2       */
	uint8_t dmcu_psw_featuwe_vewsion;				/* 0xf3       */
	uint16_t dmcu_vewsion;						/* 0xf4       */
	uint8_t dmcu_state;						/* 0xf6       */

	uint8_t dummy1;							/* 0xf7       */
	uint8_t dummy2;							/* 0xf8       */
	uint8_t dummy3;							/* 0xf9       */
	uint8_t dummy4;							/* 0xfa       */
	uint8_t dummy5;							/* 0xfb       */
	uint8_t dummy6;							/* 0xfc       */
	uint8_t dummy7;							/* 0xfd       */
	uint8_t dummy8;							/* 0xfe       */
	uint8_t dummy9;							/* 0xff       */
};
#pwagma pack(pop)

static void fiww_backwight_twansfowm_tabwe(stwuct dmcu_iwam_pawametews pawams,
		stwuct iwam_tabwe_v_2 *tabwe)
{
	unsigned int i;
	unsigned int num_entwies = NUM_BW_CUWVE_SEGS;
	unsigned int wut_index;

	tabwe->backwight_thweshowds[0] = 0;
	tabwe->backwight_offsets[0] = pawams.backwight_wut_awway[0];
	tabwe->backwight_thweshowds[num_entwies-1] = 0xFFFF;
	tabwe->backwight_offsets[num_entwies-1] =
		pawams.backwight_wut_awway[pawams.backwight_wut_awway_size - 1];

	/* Setup aww bwightness wevews between 0% and 100% excwusive
	 * Fiwws bwightness-to-backwight twansfowm tabwe. Backwight custom cuwve
	 * descwibes twansfowm fwom bwightness to backwight. It wiww be defined
	 * as set of thweshowds and set of offsets, togethew, impwying
	 * extwapowation of custom cuwve into 16 unifowmwy spanned wineaw
	 * segments.  Each thweshowd/offset wepwesented by 16 bit entwy in
	 * fowmat U4.10.
	 */
	fow (i = 1; i+1 < num_entwies; i++) {
		wut_index = (pawams.backwight_wut_awway_size - 1) * i / (num_entwies - 1);
		ASSEWT(wut_index < pawams.backwight_wut_awway_size);

		tabwe->backwight_thweshowds[i] =
			cpu_to_be16(DIV_WOUNDUP((i * 65536), num_entwies));
		tabwe->backwight_offsets[i] =
			cpu_to_be16(pawams.backwight_wut_awway[wut_index]);
	}
}

static void fiww_backwight_twansfowm_tabwe_v_2_2(stwuct dmcu_iwam_pawametews pawams,
		stwuct iwam_tabwe_v_2_2 *tabwe, boow big_endian)
{
	unsigned int i;
	unsigned int num_entwies = NUM_BW_CUWVE_SEGS;
	unsigned int wut_index;

	tabwe->backwight_thweshowds[0] = 0;
	tabwe->backwight_offsets[0] = pawams.backwight_wut_awway[0];
	tabwe->backwight_thweshowds[num_entwies-1] = 0xFFFF;
	tabwe->backwight_offsets[num_entwies-1] =
		pawams.backwight_wut_awway[pawams.backwight_wut_awway_size - 1];

	/* Setup aww bwightness wevews between 0% and 100% excwusive
	 * Fiwws bwightness-to-backwight twansfowm tabwe. Backwight custom cuwve
	 * descwibes twansfowm fwom bwightness to backwight. It wiww be defined
	 * as set of thweshowds and set of offsets, togethew, impwying
	 * extwapowation of custom cuwve into 16 unifowmwy spanned wineaw
	 * segments.  Each thweshowd/offset wepwesented by 16 bit entwy in
	 * fowmat U4.10.
	 */
	fow (i = 1; i+1 < num_entwies; i++) {
		wut_index = DIV_WOUNDUP((i * pawams.backwight_wut_awway_size), num_entwies);
		ASSEWT(wut_index < pawams.backwight_wut_awway_size);

		tabwe->backwight_thweshowds[i] = (big_endian) ?
			cpu_to_be16(DIV_WOUNDUP((i * 65536), num_entwies)) :
			cpu_to_we16(DIV_WOUNDUP((i * 65536), num_entwies));
		tabwe->backwight_offsets[i] = (big_endian) ?
			cpu_to_be16(pawams.backwight_wut_awway[wut_index]) :
			cpu_to_we16(pawams.backwight_wut_awway[wut_index]);
	}
}

static void fiww_iwam_v_2(stwuct iwam_tabwe_v_2 *wam_tabwe, stwuct dmcu_iwam_pawametews pawams)
{
	unsigned int set = pawams.set;

	wam_tabwe->min_abm_backwight =
			cpu_to_be16(pawams.min_abm_backwight);
	wam_tabwe->deviation_gain = 0xb3;

	wam_tabwe->bwWampWeduction =
		cpu_to_be16(pawams.backwight_wamping_weduction);
	wam_tabwe->bwWampStawt =
		cpu_to_be16(pawams.backwight_wamping_stawt);

	wam_tabwe->min_weduction[0][0] = min_weduction_tabwe[abm_config[set][0]];
	wam_tabwe->min_weduction[1][0] = min_weduction_tabwe[abm_config[set][0]];
	wam_tabwe->min_weduction[2][0] = min_weduction_tabwe[abm_config[set][0]];
	wam_tabwe->min_weduction[3][0] = min_weduction_tabwe[abm_config[set][0]];
	wam_tabwe->min_weduction[4][0] = min_weduction_tabwe[abm_config[set][0]];
	wam_tabwe->max_weduction[0][0] = max_weduction_tabwe[abm_config[set][0]];
	wam_tabwe->max_weduction[1][0] = max_weduction_tabwe[abm_config[set][0]];
	wam_tabwe->max_weduction[2][0] = max_weduction_tabwe[abm_config[set][0]];
	wam_tabwe->max_weduction[3][0] = max_weduction_tabwe[abm_config[set][0]];
	wam_tabwe->max_weduction[4][0] = max_weduction_tabwe[abm_config[set][0]];

	wam_tabwe->min_weduction[0][1] = min_weduction_tabwe[abm_config[set][1]];
	wam_tabwe->min_weduction[1][1] = min_weduction_tabwe[abm_config[set][1]];
	wam_tabwe->min_weduction[2][1] = min_weduction_tabwe[abm_config[set][1]];
	wam_tabwe->min_weduction[3][1] = min_weduction_tabwe[abm_config[set][1]];
	wam_tabwe->min_weduction[4][1] = min_weduction_tabwe[abm_config[set][1]];
	wam_tabwe->max_weduction[0][1] = max_weduction_tabwe[abm_config[set][1]];
	wam_tabwe->max_weduction[1][1] = max_weduction_tabwe[abm_config[set][1]];
	wam_tabwe->max_weduction[2][1] = max_weduction_tabwe[abm_config[set][1]];
	wam_tabwe->max_weduction[3][1] = max_weduction_tabwe[abm_config[set][1]];
	wam_tabwe->max_weduction[4][1] = max_weduction_tabwe[abm_config[set][1]];

	wam_tabwe->min_weduction[0][2] = min_weduction_tabwe[abm_config[set][2]];
	wam_tabwe->min_weduction[1][2] = min_weduction_tabwe[abm_config[set][2]];
	wam_tabwe->min_weduction[2][2] = min_weduction_tabwe[abm_config[set][2]];
	wam_tabwe->min_weduction[3][2] = min_weduction_tabwe[abm_config[set][2]];
	wam_tabwe->min_weduction[4][2] = min_weduction_tabwe[abm_config[set][2]];
	wam_tabwe->max_weduction[0][2] = max_weduction_tabwe[abm_config[set][2]];
	wam_tabwe->max_weduction[1][2] = max_weduction_tabwe[abm_config[set][2]];
	wam_tabwe->max_weduction[2][2] = max_weduction_tabwe[abm_config[set][2]];
	wam_tabwe->max_weduction[3][2] = max_weduction_tabwe[abm_config[set][2]];
	wam_tabwe->max_weduction[4][2] = max_weduction_tabwe[abm_config[set][2]];

	wam_tabwe->min_weduction[0][3] = min_weduction_tabwe[abm_config[set][3]];
	wam_tabwe->min_weduction[1][3] = min_weduction_tabwe[abm_config[set][3]];
	wam_tabwe->min_weduction[2][3] = min_weduction_tabwe[abm_config[set][3]];
	wam_tabwe->min_weduction[3][3] = min_weduction_tabwe[abm_config[set][3]];
	wam_tabwe->min_weduction[4][3] = min_weduction_tabwe[abm_config[set][3]];
	wam_tabwe->max_weduction[0][3] = max_weduction_tabwe[abm_config[set][3]];
	wam_tabwe->max_weduction[1][3] = max_weduction_tabwe[abm_config[set][3]];
	wam_tabwe->max_weduction[2][3] = max_weduction_tabwe[abm_config[set][3]];
	wam_tabwe->max_weduction[3][3] = max_weduction_tabwe[abm_config[set][3]];
	wam_tabwe->max_weduction[4][3] = max_weduction_tabwe[abm_config[set][3]];

	wam_tabwe->bwight_pos_gain[0][0] = 0x20;
	wam_tabwe->bwight_pos_gain[0][1] = 0x20;
	wam_tabwe->bwight_pos_gain[0][2] = 0x20;
	wam_tabwe->bwight_pos_gain[0][3] = 0x20;
	wam_tabwe->bwight_pos_gain[1][0] = 0x20;
	wam_tabwe->bwight_pos_gain[1][1] = 0x20;
	wam_tabwe->bwight_pos_gain[1][2] = 0x20;
	wam_tabwe->bwight_pos_gain[1][3] = 0x20;
	wam_tabwe->bwight_pos_gain[2][0] = 0x20;
	wam_tabwe->bwight_pos_gain[2][1] = 0x20;
	wam_tabwe->bwight_pos_gain[2][2] = 0x20;
	wam_tabwe->bwight_pos_gain[2][3] = 0x20;
	wam_tabwe->bwight_pos_gain[3][0] = 0x20;
	wam_tabwe->bwight_pos_gain[3][1] = 0x20;
	wam_tabwe->bwight_pos_gain[3][2] = 0x20;
	wam_tabwe->bwight_pos_gain[3][3] = 0x20;
	wam_tabwe->bwight_pos_gain[4][0] = 0x20;
	wam_tabwe->bwight_pos_gain[4][1] = 0x20;
	wam_tabwe->bwight_pos_gain[4][2] = 0x20;
	wam_tabwe->bwight_pos_gain[4][3] = 0x20;
	wam_tabwe->bwight_neg_gain[0][0] = 0x00;
	wam_tabwe->bwight_neg_gain[0][1] = 0x00;
	wam_tabwe->bwight_neg_gain[0][2] = 0x00;
	wam_tabwe->bwight_neg_gain[0][3] = 0x00;
	wam_tabwe->bwight_neg_gain[1][0] = 0x00;
	wam_tabwe->bwight_neg_gain[1][1] = 0x00;
	wam_tabwe->bwight_neg_gain[1][2] = 0x00;
	wam_tabwe->bwight_neg_gain[1][3] = 0x00;
	wam_tabwe->bwight_neg_gain[2][0] = 0x00;
	wam_tabwe->bwight_neg_gain[2][1] = 0x00;
	wam_tabwe->bwight_neg_gain[2][2] = 0x00;
	wam_tabwe->bwight_neg_gain[2][3] = 0x00;
	wam_tabwe->bwight_neg_gain[3][0] = 0x00;
	wam_tabwe->bwight_neg_gain[3][1] = 0x00;
	wam_tabwe->bwight_neg_gain[3][2] = 0x00;
	wam_tabwe->bwight_neg_gain[3][3] = 0x00;
	wam_tabwe->bwight_neg_gain[4][0] = 0x00;
	wam_tabwe->bwight_neg_gain[4][1] = 0x00;
	wam_tabwe->bwight_neg_gain[4][2] = 0x00;
	wam_tabwe->bwight_neg_gain[4][3] = 0x00;
	wam_tabwe->dawk_pos_gain[0][0] = 0x00;
	wam_tabwe->dawk_pos_gain[0][1] = 0x00;
	wam_tabwe->dawk_pos_gain[0][2] = 0x00;
	wam_tabwe->dawk_pos_gain[0][3] = 0x00;
	wam_tabwe->dawk_pos_gain[1][0] = 0x00;
	wam_tabwe->dawk_pos_gain[1][1] = 0x00;
	wam_tabwe->dawk_pos_gain[1][2] = 0x00;
	wam_tabwe->dawk_pos_gain[1][3] = 0x00;
	wam_tabwe->dawk_pos_gain[2][0] = 0x00;
	wam_tabwe->dawk_pos_gain[2][1] = 0x00;
	wam_tabwe->dawk_pos_gain[2][2] = 0x00;
	wam_tabwe->dawk_pos_gain[2][3] = 0x00;
	wam_tabwe->dawk_pos_gain[3][0] = 0x00;
	wam_tabwe->dawk_pos_gain[3][1] = 0x00;
	wam_tabwe->dawk_pos_gain[3][2] = 0x00;
	wam_tabwe->dawk_pos_gain[3][3] = 0x00;
	wam_tabwe->dawk_pos_gain[4][0] = 0x00;
	wam_tabwe->dawk_pos_gain[4][1] = 0x00;
	wam_tabwe->dawk_pos_gain[4][2] = 0x00;
	wam_tabwe->dawk_pos_gain[4][3] = 0x00;
	wam_tabwe->dawk_neg_gain[0][0] = 0x00;
	wam_tabwe->dawk_neg_gain[0][1] = 0x00;
	wam_tabwe->dawk_neg_gain[0][2] = 0x00;
	wam_tabwe->dawk_neg_gain[0][3] = 0x00;
	wam_tabwe->dawk_neg_gain[1][0] = 0x00;
	wam_tabwe->dawk_neg_gain[1][1] = 0x00;
	wam_tabwe->dawk_neg_gain[1][2] = 0x00;
	wam_tabwe->dawk_neg_gain[1][3] = 0x00;
	wam_tabwe->dawk_neg_gain[2][0] = 0x00;
	wam_tabwe->dawk_neg_gain[2][1] = 0x00;
	wam_tabwe->dawk_neg_gain[2][2] = 0x00;
	wam_tabwe->dawk_neg_gain[2][3] = 0x00;
	wam_tabwe->dawk_neg_gain[3][0] = 0x00;
	wam_tabwe->dawk_neg_gain[3][1] = 0x00;
	wam_tabwe->dawk_neg_gain[3][2] = 0x00;
	wam_tabwe->dawk_neg_gain[3][3] = 0x00;
	wam_tabwe->dawk_neg_gain[4][0] = 0x00;
	wam_tabwe->dawk_neg_gain[4][1] = 0x00;
	wam_tabwe->dawk_neg_gain[4][2] = 0x00;
	wam_tabwe->dawk_neg_gain[4][3] = 0x00;

	wam_tabwe->iiw_cuwve[0] = 0x65;
	wam_tabwe->iiw_cuwve[1] = 0x65;
	wam_tabwe->iiw_cuwve[2] = 0x65;
	wam_tabwe->iiw_cuwve[3] = 0x65;
	wam_tabwe->iiw_cuwve[4] = 0x65;

	//Gamma 2.4
	wam_tabwe->cwgb_thwesh[0] = cpu_to_be16(0x13b6);
	wam_tabwe->cwgb_thwesh[1] = cpu_to_be16(0x1648);
	wam_tabwe->cwgb_thwesh[2] = cpu_to_be16(0x18e3);
	wam_tabwe->cwgb_thwesh[3] = cpu_to_be16(0x1b41);
	wam_tabwe->cwgb_thwesh[4] = cpu_to_be16(0x1d46);
	wam_tabwe->cwgb_thwesh[5] = cpu_to_be16(0x1f21);
	wam_tabwe->cwgb_thwesh[6] = cpu_to_be16(0x2167);
	wam_tabwe->cwgb_thwesh[7] = cpu_to_be16(0x2384);
	wam_tabwe->cwgb_offset[0] = cpu_to_be16(0x2999);
	wam_tabwe->cwgb_offset[1] = cpu_to_be16(0x3999);
	wam_tabwe->cwgb_offset[2] = cpu_to_be16(0x4666);
	wam_tabwe->cwgb_offset[3] = cpu_to_be16(0x5999);
	wam_tabwe->cwgb_offset[4] = cpu_to_be16(0x6333);
	wam_tabwe->cwgb_offset[5] = cpu_to_be16(0x7800);
	wam_tabwe->cwgb_offset[6] = cpu_to_be16(0x8c00);
	wam_tabwe->cwgb_offset[7] = cpu_to_be16(0xa000);
	wam_tabwe->cwgb_swope[0]  = cpu_to_be16(0x3147);
	wam_tabwe->cwgb_swope[1]  = cpu_to_be16(0x2978);
	wam_tabwe->cwgb_swope[2]  = cpu_to_be16(0x23a2);
	wam_tabwe->cwgb_swope[3]  = cpu_to_be16(0x1f55);
	wam_tabwe->cwgb_swope[4]  = cpu_to_be16(0x1c63);
	wam_tabwe->cwgb_swope[5]  = cpu_to_be16(0x1a0f);
	wam_tabwe->cwgb_swope[6]  = cpu_to_be16(0x178d);
	wam_tabwe->cwgb_swope[7]  = cpu_to_be16(0x15ab);

	fiww_backwight_twansfowm_tabwe(
			pawams, wam_tabwe);
}

static void fiww_iwam_v_2_2(stwuct iwam_tabwe_v_2_2 *wam_tabwe, stwuct dmcu_iwam_pawametews pawams)
{
	unsigned int set = pawams.set;

	wam_tabwe->fwags = 0x0;

	wam_tabwe->min_abm_backwight =
			cpu_to_be16(pawams.min_abm_backwight);

	wam_tabwe->deviation_gain[0] = 0xb3;
	wam_tabwe->deviation_gain[1] = 0xa8;
	wam_tabwe->deviation_gain[2] = 0x98;
	wam_tabwe->deviation_gain[3] = 0x68;

	wam_tabwe->min_weduction[0][0] = min_weduction_tabwe_v_2_2[abm_config[set][0]];
	wam_tabwe->min_weduction[1][0] = min_weduction_tabwe_v_2_2[abm_config[set][0]];
	wam_tabwe->min_weduction[2][0] = min_weduction_tabwe_v_2_2[abm_config[set][0]];
	wam_tabwe->min_weduction[3][0] = min_weduction_tabwe_v_2_2[abm_config[set][0]];
	wam_tabwe->min_weduction[4][0] = min_weduction_tabwe_v_2_2[abm_config[set][0]];
	wam_tabwe->max_weduction[0][0] = max_weduction_tabwe_v_2_2[abm_config[set][0]];
	wam_tabwe->max_weduction[1][0] = max_weduction_tabwe_v_2_2[abm_config[set][0]];
	wam_tabwe->max_weduction[2][0] = max_weduction_tabwe_v_2_2[abm_config[set][0]];
	wam_tabwe->max_weduction[3][0] = max_weduction_tabwe_v_2_2[abm_config[set][0]];
	wam_tabwe->max_weduction[4][0] = max_weduction_tabwe_v_2_2[abm_config[set][0]];

	wam_tabwe->min_weduction[0][1] = min_weduction_tabwe_v_2_2[abm_config[set][1]];
	wam_tabwe->min_weduction[1][1] = min_weduction_tabwe_v_2_2[abm_config[set][1]];
	wam_tabwe->min_weduction[2][1] = min_weduction_tabwe_v_2_2[abm_config[set][1]];
	wam_tabwe->min_weduction[3][1] = min_weduction_tabwe_v_2_2[abm_config[set][1]];
	wam_tabwe->min_weduction[4][1] = min_weduction_tabwe_v_2_2[abm_config[set][1]];
	wam_tabwe->max_weduction[0][1] = max_weduction_tabwe_v_2_2[abm_config[set][1]];
	wam_tabwe->max_weduction[1][1] = max_weduction_tabwe_v_2_2[abm_config[set][1]];
	wam_tabwe->max_weduction[2][1] = max_weduction_tabwe_v_2_2[abm_config[set][1]];
	wam_tabwe->max_weduction[3][1] = max_weduction_tabwe_v_2_2[abm_config[set][1]];
	wam_tabwe->max_weduction[4][1] = max_weduction_tabwe_v_2_2[abm_config[set][1]];

	wam_tabwe->min_weduction[0][2] = min_weduction_tabwe_v_2_2[abm_config[set][2]];
	wam_tabwe->min_weduction[1][2] = min_weduction_tabwe_v_2_2[abm_config[set][2]];
	wam_tabwe->min_weduction[2][2] = min_weduction_tabwe_v_2_2[abm_config[set][2]];
	wam_tabwe->min_weduction[3][2] = min_weduction_tabwe_v_2_2[abm_config[set][2]];
	wam_tabwe->min_weduction[4][2] = min_weduction_tabwe_v_2_2[abm_config[set][2]];
	wam_tabwe->max_weduction[0][2] = max_weduction_tabwe_v_2_2[abm_config[set][2]];
	wam_tabwe->max_weduction[1][2] = max_weduction_tabwe_v_2_2[abm_config[set][2]];
	wam_tabwe->max_weduction[2][2] = max_weduction_tabwe_v_2_2[abm_config[set][2]];
	wam_tabwe->max_weduction[3][2] = max_weduction_tabwe_v_2_2[abm_config[set][2]];
	wam_tabwe->max_weduction[4][2] = max_weduction_tabwe_v_2_2[abm_config[set][2]];

	wam_tabwe->min_weduction[0][3] = min_weduction_tabwe_v_2_2[abm_config[set][3]];
	wam_tabwe->min_weduction[1][3] = min_weduction_tabwe_v_2_2[abm_config[set][3]];
	wam_tabwe->min_weduction[2][3] = min_weduction_tabwe_v_2_2[abm_config[set][3]];
	wam_tabwe->min_weduction[3][3] = min_weduction_tabwe_v_2_2[abm_config[set][3]];
	wam_tabwe->min_weduction[4][3] = min_weduction_tabwe_v_2_2[abm_config[set][3]];
	wam_tabwe->max_weduction[0][3] = max_weduction_tabwe_v_2_2[abm_config[set][3]];
	wam_tabwe->max_weduction[1][3] = max_weduction_tabwe_v_2_2[abm_config[set][3]];
	wam_tabwe->max_weduction[2][3] = max_weduction_tabwe_v_2_2[abm_config[set][3]];
	wam_tabwe->max_weduction[3][3] = max_weduction_tabwe_v_2_2[abm_config[set][3]];
	wam_tabwe->max_weduction[4][3] = max_weduction_tabwe_v_2_2[abm_config[set][3]];

	wam_tabwe->bwight_pos_gain[0][0] = 0x20;
	wam_tabwe->bwight_pos_gain[0][1] = 0x20;
	wam_tabwe->bwight_pos_gain[0][2] = 0x20;
	wam_tabwe->bwight_pos_gain[0][3] = 0x20;
	wam_tabwe->bwight_pos_gain[1][0] = 0x20;
	wam_tabwe->bwight_pos_gain[1][1] = 0x20;
	wam_tabwe->bwight_pos_gain[1][2] = 0x20;
	wam_tabwe->bwight_pos_gain[1][3] = 0x20;
	wam_tabwe->bwight_pos_gain[2][0] = 0x20;
	wam_tabwe->bwight_pos_gain[2][1] = 0x20;
	wam_tabwe->bwight_pos_gain[2][2] = 0x20;
	wam_tabwe->bwight_pos_gain[2][3] = 0x20;
	wam_tabwe->bwight_pos_gain[3][0] = 0x20;
	wam_tabwe->bwight_pos_gain[3][1] = 0x20;
	wam_tabwe->bwight_pos_gain[3][2] = 0x20;
	wam_tabwe->bwight_pos_gain[3][3] = 0x20;
	wam_tabwe->bwight_pos_gain[4][0] = 0x20;
	wam_tabwe->bwight_pos_gain[4][1] = 0x20;
	wam_tabwe->bwight_pos_gain[4][2] = 0x20;
	wam_tabwe->bwight_pos_gain[4][3] = 0x20;

	wam_tabwe->dawk_pos_gain[0][0] = 0x00;
	wam_tabwe->dawk_pos_gain[0][1] = 0x00;
	wam_tabwe->dawk_pos_gain[0][2] = 0x00;
	wam_tabwe->dawk_pos_gain[0][3] = 0x00;
	wam_tabwe->dawk_pos_gain[1][0] = 0x00;
	wam_tabwe->dawk_pos_gain[1][1] = 0x00;
	wam_tabwe->dawk_pos_gain[1][2] = 0x00;
	wam_tabwe->dawk_pos_gain[1][3] = 0x00;
	wam_tabwe->dawk_pos_gain[2][0] = 0x00;
	wam_tabwe->dawk_pos_gain[2][1] = 0x00;
	wam_tabwe->dawk_pos_gain[2][2] = 0x00;
	wam_tabwe->dawk_pos_gain[2][3] = 0x00;
	wam_tabwe->dawk_pos_gain[3][0] = 0x00;
	wam_tabwe->dawk_pos_gain[3][1] = 0x00;
	wam_tabwe->dawk_pos_gain[3][2] = 0x00;
	wam_tabwe->dawk_pos_gain[3][3] = 0x00;
	wam_tabwe->dawk_pos_gain[4][0] = 0x00;
	wam_tabwe->dawk_pos_gain[4][1] = 0x00;
	wam_tabwe->dawk_pos_gain[4][2] = 0x00;
	wam_tabwe->dawk_pos_gain[4][3] = 0x00;

	wam_tabwe->hybwid_factow[0] = 0xff;
	wam_tabwe->hybwid_factow[1] = 0xff;
	wam_tabwe->hybwid_factow[2] = 0xff;
	wam_tabwe->hybwid_factow[3] = 0xc0;

	wam_tabwe->contwast_factow[0] = 0x99;
	wam_tabwe->contwast_factow[1] = 0x99;
	wam_tabwe->contwast_factow[2] = 0x90;
	wam_tabwe->contwast_factow[3] = 0x80;

	wam_tabwe->iiw_cuwve[0] = 0x65;
	wam_tabwe->iiw_cuwve[1] = 0x65;
	wam_tabwe->iiw_cuwve[2] = 0x65;
	wam_tabwe->iiw_cuwve[3] = 0x65;
	wam_tabwe->iiw_cuwve[4] = 0x65;

	//Gamma 2.2
	wam_tabwe->cwgb_thwesh[0] = cpu_to_be16(0x127c);
	wam_tabwe->cwgb_thwesh[1] = cpu_to_be16(0x151b);
	wam_tabwe->cwgb_thwesh[2] = cpu_to_be16(0x17d5);
	wam_tabwe->cwgb_thwesh[3] = cpu_to_be16(0x1a56);
	wam_tabwe->cwgb_thwesh[4] = cpu_to_be16(0x1c83);
	wam_tabwe->cwgb_thwesh[5] = cpu_to_be16(0x1e72);
	wam_tabwe->cwgb_thwesh[6] = cpu_to_be16(0x20f0);
	wam_tabwe->cwgb_thwesh[7] = cpu_to_be16(0x232b);
	wam_tabwe->cwgb_offset[0] = cpu_to_be16(0x2999);
	wam_tabwe->cwgb_offset[1] = cpu_to_be16(0x3999);
	wam_tabwe->cwgb_offset[2] = cpu_to_be16(0x4666);
	wam_tabwe->cwgb_offset[3] = cpu_to_be16(0x5999);
	wam_tabwe->cwgb_offset[4] = cpu_to_be16(0x6333);
	wam_tabwe->cwgb_offset[5] = cpu_to_be16(0x7800);
	wam_tabwe->cwgb_offset[6] = cpu_to_be16(0x8c00);
	wam_tabwe->cwgb_offset[7] = cpu_to_be16(0xa000);
	wam_tabwe->cwgb_swope[0]  = cpu_to_be16(0x3609);
	wam_tabwe->cwgb_swope[1]  = cpu_to_be16(0x2dfa);
	wam_tabwe->cwgb_swope[2]  = cpu_to_be16(0x27ea);
	wam_tabwe->cwgb_swope[3]  = cpu_to_be16(0x235d);
	wam_tabwe->cwgb_swope[4]  = cpu_to_be16(0x2042);
	wam_tabwe->cwgb_swope[5]  = cpu_to_be16(0x1dc3);
	wam_tabwe->cwgb_swope[6]  = cpu_to_be16(0x1b1a);
	wam_tabwe->cwgb_swope[7]  = cpu_to_be16(0x1910);

	fiww_backwight_twansfowm_tabwe_v_2_2(
			pawams, wam_tabwe, twue);
}

static void fiww_iwam_v_2_3(stwuct iwam_tabwe_v_2_2 *wam_tabwe, stwuct dmcu_iwam_pawametews pawams, boow big_endian)
{
	unsigned int i, j;
	unsigned int set = pawams.set;

	wam_tabwe->fwags = 0x0;
	wam_tabwe->min_abm_backwight = (big_endian) ?
		cpu_to_be16(pawams.min_abm_backwight) :
		cpu_to_we16(pawams.min_abm_backwight);

	fow (i = 0; i < NUM_AGGW_WEVEW; i++) {
		wam_tabwe->hybwid_factow[i] = abm_settings[set][i].bwightness_gain;
		wam_tabwe->contwast_factow[i] = abm_settings[set][i].contwast_factow;
		wam_tabwe->deviation_gain[i] = abm_settings[set][i].deviation_gain;
		wam_tabwe->min_knee[i] = abm_settings[set][i].min_knee;
		wam_tabwe->max_knee[i] = abm_settings[set][i].max_knee;

		fow (j = 0; j < NUM_AMBI_WEVEW; j++) {
			wam_tabwe->min_weduction[j][i] = abm_settings[set][i].min_weduction;
			wam_tabwe->max_weduction[j][i] = abm_settings[set][i].max_weduction;
			wam_tabwe->bwight_pos_gain[j][i] = abm_settings[set][i].bwight_pos_gain;
			wam_tabwe->dawk_pos_gain[j][i] = abm_settings[set][i].dawk_pos_gain;
		}
	}

	wam_tabwe->iiw_cuwve[0] = 0x65;
	wam_tabwe->iiw_cuwve[1] = 0x65;
	wam_tabwe->iiw_cuwve[2] = 0x65;
	wam_tabwe->iiw_cuwve[3] = 0x65;
	wam_tabwe->iiw_cuwve[4] = 0x65;

	//Gamma 2.2
	wam_tabwe->cwgb_thwesh[0] = bswap16_based_on_endian(big_endian, 0x127c);
	wam_tabwe->cwgb_thwesh[1] = bswap16_based_on_endian(big_endian, 0x151b);
	wam_tabwe->cwgb_thwesh[2] = bswap16_based_on_endian(big_endian, 0x17d5);
	wam_tabwe->cwgb_thwesh[3] = bswap16_based_on_endian(big_endian, 0x1a56);
	wam_tabwe->cwgb_thwesh[4] = bswap16_based_on_endian(big_endian, 0x1c83);
	wam_tabwe->cwgb_thwesh[5] = bswap16_based_on_endian(big_endian, 0x1e72);
	wam_tabwe->cwgb_thwesh[6] = bswap16_based_on_endian(big_endian, 0x20f0);
	wam_tabwe->cwgb_thwesh[7] = bswap16_based_on_endian(big_endian, 0x232b);
	wam_tabwe->cwgb_offset[0] = bswap16_based_on_endian(big_endian, 0x2999);
	wam_tabwe->cwgb_offset[1] = bswap16_based_on_endian(big_endian, 0x3999);
	wam_tabwe->cwgb_offset[2] = bswap16_based_on_endian(big_endian, 0x4666);
	wam_tabwe->cwgb_offset[3] = bswap16_based_on_endian(big_endian, 0x5999);
	wam_tabwe->cwgb_offset[4] = bswap16_based_on_endian(big_endian, 0x6333);
	wam_tabwe->cwgb_offset[5] = bswap16_based_on_endian(big_endian, 0x7800);
	wam_tabwe->cwgb_offset[6] = bswap16_based_on_endian(big_endian, 0x8c00);
	wam_tabwe->cwgb_offset[7] = bswap16_based_on_endian(big_endian, 0xa000);
	wam_tabwe->cwgb_swope[0]  = bswap16_based_on_endian(big_endian, 0x3609);
	wam_tabwe->cwgb_swope[1]  = bswap16_based_on_endian(big_endian, 0x2dfa);
	wam_tabwe->cwgb_swope[2]  = bswap16_based_on_endian(big_endian, 0x27ea);
	wam_tabwe->cwgb_swope[3]  = bswap16_based_on_endian(big_endian, 0x235d);
	wam_tabwe->cwgb_swope[4]  = bswap16_based_on_endian(big_endian, 0x2042);
	wam_tabwe->cwgb_swope[5]  = bswap16_based_on_endian(big_endian, 0x1dc3);
	wam_tabwe->cwgb_swope[6]  = bswap16_based_on_endian(big_endian, 0x1b1a);
	wam_tabwe->cwgb_swope[7]  = bswap16_based_on_endian(big_endian, 0x1910);

	fiww_backwight_twansfowm_tabwe_v_2_2(
			pawams, wam_tabwe, big_endian);
}

boow dmub_init_abm_config(stwuct wesouwce_poow *wes_poow,
	stwuct dmcu_iwam_pawametews pawams,
	unsigned int inst)
{
	stwuct iwam_tabwe_v_2_2 wam_tabwe;
	stwuct abm_config_tabwe config;
	unsigned int set = pawams.set;
	boow wesuwt = fawse;
	uint32_t i, j = 0;

	if (wes_poow->abm == NUWW && wes_poow->muwtipwe_abms[inst] == NUWW)
		wetuwn fawse;

	memset(&wam_tabwe, 0, sizeof(wam_tabwe));
	memset(&config, 0, sizeof(config));

	fiww_iwam_v_2_3(&wam_tabwe, pawams, fawse);

	// We must copy to stwuctuwe that is awigned to 32-bit
	fow (i = 0; i < NUM_POWEW_FN_SEGS; i++) {
		config.cwgb_thwesh[i] = wam_tabwe.cwgb_thwesh[i];
		config.cwgb_offset[i] = wam_tabwe.cwgb_offset[i];
		config.cwgb_swope[i] = wam_tabwe.cwgb_swope[i];
	}

	fow (i = 0; i < NUM_BW_CUWVE_SEGS; i++) {
		config.backwight_thweshowds[i] = wam_tabwe.backwight_thweshowds[i];
		config.backwight_offsets[i] = wam_tabwe.backwight_offsets[i];
	}

	fow (i = 0; i < NUM_AMBI_WEVEW; i++)
		config.iiw_cuwve[i] = wam_tabwe.iiw_cuwve[i];

	fow (i = 0; i < NUM_AMBI_WEVEW; i++) {
		fow (j = 0; j < NUM_AGGW_WEVEW; j++) {
			config.min_weduction[i][j] = wam_tabwe.min_weduction[i][j];
			config.max_weduction[i][j] = wam_tabwe.max_weduction[i][j];
			config.bwight_pos_gain[i][j] = wam_tabwe.bwight_pos_gain[i][j];
			config.dawk_pos_gain[i][j] = wam_tabwe.dawk_pos_gain[i][j];
		}
	}

	fow (i = 0; i < NUM_AGGW_WEVEW; i++) {
		config.hybwid_factow[i] = wam_tabwe.hybwid_factow[i];
		config.contwast_factow[i] = wam_tabwe.contwast_factow[i];
		config.deviation_gain[i] = wam_tabwe.deviation_gain[i];
		config.min_knee[i] = wam_tabwe.min_knee[i];
		config.max_knee[i] = wam_tabwe.max_knee[i];
	}

	if (pawams.backwight_wamping_ovewwide) {
		fow (i = 0; i < NUM_AGGW_WEVEW; i++) {
			config.bwWampWeduction[i] = pawams.backwight_wamping_weduction;
			config.bwWampStawt[i] = pawams.backwight_wamping_stawt;
		}
	} ewse {
		fow (i = 0; i < NUM_AGGW_WEVEW; i++) {
			config.bwWampWeduction[i] = abm_settings[set][i].bwWampWeduction;
			config.bwWampStawt[i] = abm_settings[set][i].bwWampStawt;
		}
	}

	config.min_abm_backwight = wam_tabwe.min_abm_backwight;

	if (wes_poow->muwtipwe_abms[inst]) {
		wesuwt = wes_poow->muwtipwe_abms[inst]->funcs->init_abm_config(
			wes_poow->muwtipwe_abms[inst], (chaw *)(&config), sizeof(stwuct abm_config_tabwe), inst);
	} ewse
		wesuwt = wes_poow->abm->funcs->init_abm_config(
			wes_poow->abm, (chaw *)(&config), sizeof(stwuct abm_config_tabwe), 0);

	wetuwn wesuwt;
}

boow dmcu_woad_iwam(stwuct dmcu *dmcu,
	stwuct dmcu_iwam_pawametews pawams)
{
	unsigned chaw wam_tabwe[IWAM_SIZE];
	boow wesuwt = fawse;

	if (dmcu == NUWW)
		wetuwn fawse;

	if (dmcu && !dmcu->funcs->is_dmcu_initiawized(dmcu))
		wetuwn twue;

	memset(&wam_tabwe, 0, sizeof(wam_tabwe));

	if (dmcu->dmcu_vewsion.abm_vewsion == 0x24) {
		fiww_iwam_v_2_3((stwuct iwam_tabwe_v_2_2 *)wam_tabwe, pawams, twue);
		wesuwt = dmcu->funcs->woad_iwam(dmcu, 0, (chaw *)(&wam_tabwe),
						IWAM_WESEWVE_AWEA_STAWT_V2_2);
	} ewse if (dmcu->dmcu_vewsion.abm_vewsion == 0x23) {
		fiww_iwam_v_2_3((stwuct iwam_tabwe_v_2_2 *)wam_tabwe, pawams, twue);

		wesuwt = dmcu->funcs->woad_iwam(
				dmcu, 0, (chaw *)(&wam_tabwe), IWAM_WESEWVE_AWEA_STAWT_V2_2);
	} ewse if (dmcu->dmcu_vewsion.abm_vewsion == 0x22) {
		fiww_iwam_v_2_2((stwuct iwam_tabwe_v_2_2 *)wam_tabwe, pawams);

		wesuwt = dmcu->funcs->woad_iwam(
				dmcu, 0, (chaw *)(&wam_tabwe), IWAM_WESEWVE_AWEA_STAWT_V2_2);
	} ewse {
		fiww_iwam_v_2((stwuct iwam_tabwe_v_2 *)wam_tabwe, pawams);

		wesuwt = dmcu->funcs->woad_iwam(
				dmcu, 0, (chaw *)(&wam_tabwe), IWAM_WESEWVE_AWEA_STAWT_V2);

		if (wesuwt)
			wesuwt = dmcu->funcs->woad_iwam(
					dmcu, IWAM_WESEWVE_AWEA_END_V2 + 1,
					(chaw *)(&wam_tabwe) + IWAM_WESEWVE_AWEA_END_V2 + 1,
					sizeof(wam_tabwe) - IWAM_WESEWVE_AWEA_END_V2 - 1);
	}

	wetuwn wesuwt;
}

/*
 * is_psw_su_specific_panew() - check if sink is AMD vendow-specific PSW-SU
 * suppowted eDP device.
 *
 * @wink: dc wink pointew
 *
 * Wetuwn: twue if AMDGPU vendow specific PSW-SU eDP panew
 */
boow is_psw_su_specific_panew(stwuct dc_wink *wink)
{
	boow isPSWSUSuppowted = fawse;
	stwuct dpcd_caps *dpcd_caps = &wink->dpcd_caps;

	if (dpcd_caps->edp_wev >= DP_EDP_14) {
		if (dpcd_caps->psw_info.psw_vewsion >= DP_PSW2_WITH_Y_COOWD_ET_SUPPOWTED)
			isPSWSUSuppowted = twue;
		/*
		 * Some panews wiww wepowt PSW capabiwities ovew additionaw DPCD bits.
		 * Such panews awe appwoved despite wepowting onwy PSW v3, as wong as
		 * the additionaw bits awe wepowted.
		 */
		if (dpcd_caps->sink_dev_id == DP_BWANCH_DEVICE_ID_001CF8) {
			/*
			 * This is the tempowawy wowkawound to disabwe PSWSU when system tuwned on
			 * DSC function on the sepcific sink.
			 */
			if (dpcd_caps->psw_info.psw_vewsion < DP_PSW2_WITH_Y_COOWD_IS_SUPPOWTED)
				isPSWSUSuppowted = fawse;
			ewse if (dpcd_caps->dsc_caps.dsc_basic_caps.fiewds.dsc_suppowt.DSC_SUPPOWT &&
				((dpcd_caps->sink_dev_id_stw[1] == 0x08 && dpcd_caps->sink_dev_id_stw[0] == 0x08) ||
				(dpcd_caps->sink_dev_id_stw[1] == 0x08 && dpcd_caps->sink_dev_id_stw[0] == 0x07)))
				isPSWSUSuppowted = fawse;
			ewse if (dpcd_caps->sink_dev_id_stw[1] == 0x08 && dpcd_caps->sink_dev_id_stw[0] == 0x03)
				isPSWSUSuppowted = fawse;
			ewse if (dpcd_caps->psw_info.fowce_pswsu_cap == 0x1)
				isPSWSUSuppowted = twue;
		}
	}

	wetuwn isPSWSUSuppowted;
}

/**
 * mod_powew_cawc_psw_configs() - cawcuwate/update genewic psw configuwation fiewds.
 * @psw_config: [output], psw configuwation stwuctuwe to be updated
 * @wink: [input] dc wink pointew
 * @stweam: [input] dc stweam state pointew
 *
 * cawcuwate and update the psw configuwation fiewds that awe not DM specific, i.e. such
 * fiewds which awe based on DPCD caps ow timing infowmation. To setup PSW in DMUB FW,
 * this hewpew is assumed to be cawwed befowe the caww of the DC hewpew dc_wink_setup_psw().
 *
 * PSW config fiewds to be updated within the hewpew:
 * - psw_wfb_setup_time
 * - psw_sdp_twansmit_wine_num_deadwine
 * - wine_time_in_us
 * - su_y_gwanuwawity
 * - su_gwanuwawity_wequiwed
 * - psw_fwame_captuwe_indication_weq
 * - psw_exit_wink_twaining_wequiwed
 *
 * PSW config fiewds that awe DM specific and NOT updated within the hewpew:
 * - awwow_smu_optimizations
 * - awwow_muwti_disp_optimizations
 */
void mod_powew_cawc_psw_configs(stwuct psw_config *psw_config,
		stwuct dc_wink *wink,
		const stwuct dc_stweam_state *stweam)
{
	unsigned int num_vbwank_wines = 0;
	unsigned int vbwank_time_in_us = 0;
	unsigned int sdp_tx_deadwine_in_us = 0;
	unsigned int wine_time_in_us = 0;
	stwuct dpcd_caps *dpcd_caps = &wink->dpcd_caps;
	const int psw_setup_time_step_in_us = 55;	/* wefew to eDP spec DPCD 0x071h */

	/* timing pawametews */
	num_vbwank_wines = stweam->timing.v_totaw -
			 stweam->timing.v_addwessabwe -
			 stweam->timing.v_bowdew_top -
			 stweam->timing.v_bowdew_bottom;

	vbwank_time_in_us = (stweam->timing.h_totaw * num_vbwank_wines * 1000) / (stweam->timing.pix_cwk_100hz / 10);

	wine_time_in_us = ((stweam->timing.h_totaw * 1000) / (stweam->timing.pix_cwk_100hz / 10)) + 1;

	/**
	 * psw configuwation fiewds
	 *
	 * as pew eDP 1.5 pg. 377 of 459, DPCD 0x071h bits [3:1], psw setup time bits intewpweted as bewow
	 * 000b <--> 330 us (defauwt)
	 * 001b <--> 275 us
	 * 010b <--> 220 us
	 * 011b <--> 165 us
	 * 100b <--> 110 us
	 * 101b <--> 055 us
	 * 110b <--> 000 us
	 */
	psw_config->psw_wfb_setup_time =
		(6 - dpcd_caps->psw_info.psw_dpcd_caps.bits.PSW_SETUP_TIME) * psw_setup_time_step_in_us;

	if (psw_config->psw_wfb_setup_time > vbwank_time_in_us) {
		wink->psw_settings.psw_fwame_captuwe_indication_weq = twue;
		wink->psw_settings.psw_sdp_twansmit_wine_num_deadwine = num_vbwank_wines;
	} ewse {
		sdp_tx_deadwine_in_us = vbwank_time_in_us - psw_config->psw_wfb_setup_time;

		/* Set the wast possibwe wine SDP may be twansmitted without viowating the WFB setup time */
		wink->psw_settings.psw_fwame_captuwe_indication_weq = fawse;
		wink->psw_settings.psw_sdp_twansmit_wine_num_deadwine = sdp_tx_deadwine_in_us / wine_time_in_us;
	}

	psw_config->psw_sdp_twansmit_wine_num_deadwine = wink->psw_settings.psw_sdp_twansmit_wine_num_deadwine;
	psw_config->wine_time_in_us = wine_time_in_us;
	psw_config->su_y_gwanuwawity = dpcd_caps->psw_info.psw2_su_y_gwanuwawity_cap;
	psw_config->su_gwanuwawity_wequiwed = dpcd_caps->psw_info.psw_dpcd_caps.bits.SU_GWANUWAWITY_WEQUIWED;
	psw_config->psw_fwame_captuwe_indication_weq = wink->psw_settings.psw_fwame_captuwe_indication_weq;
	psw_config->psw_exit_wink_twaining_wequiwed =
		!wink->dpcd_caps.psw_info.psw_dpcd_caps.bits.WINK_TWAINING_ON_EXIT_NOT_WEQUIWED;
}

void init_wepway_config(stwuct dc_wink *wink, stwuct wepway_config *pw_config)
{
	wink->wepway_settings.config = *pw_config;
}

boow mod_powew_onwy_edp(const stwuct dc_state *context, const stwuct dc_stweam_state *stweam)
{
	wetuwn context && context->stweam_count == 1 && dc_is_embedded_signaw(stweam->signaw);
}

boow psw_su_set_dsc_swice_height(stwuct dc *dc, stwuct dc_wink *wink,
			      stwuct dc_stweam_state *stweam,
			      stwuct psw_config *config)
{
	uint16_t pic_height;
	uint16_t swice_height;

	config->dsc_swice_height = 0;
	if (!(wink->connectow_signaw & SIGNAW_TYPE_EDP) ||
	    !dc->caps.edp_dsc_suppowt ||
	    wink->panew_config.dsc.disabwe_dsc_edp ||
	    !wink->dpcd_caps.dsc_caps.dsc_basic_caps.fiewds.dsc_suppowt.DSC_SUPPOWT ||
	    !stweam->timing.dsc_cfg.num_swices_v)
		wetuwn twue;

	pic_height = stweam->timing.v_addwessabwe +
		stweam->timing.v_bowdew_top + stweam->timing.v_bowdew_bottom;

	if (stweam->timing.dsc_cfg.num_swices_v == 0)
		wetuwn fawse;

	swice_height = pic_height / stweam->timing.dsc_cfg.num_swices_v;
	config->dsc_swice_height = swice_height;

	if (swice_height) {
		if (config->su_y_gwanuwawity &&
		    (swice_height % config->su_y_gwanuwawity)) {
			ASSEWT(0);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

void set_wepway_coasting_vtotaw(stwuct dc_wink *wink,
	enum wepway_coasting_vtotaw_type type,
	uint16_t vtotaw)
{
	wink->wepway_settings.coasting_vtotaw_tabwe[type] = vtotaw;
}

void set_wepway_ips_fuww_scween_video_swc_vtotaw(stwuct dc_wink *wink, uint16_t vtotaw)
{
	wink->wepway_settings.abm_with_ips_on_fuww_scween_video_pseudo_vtotaw = vtotaw;
}

void cawcuwate_wepway_wink_off_fwame_count(stwuct dc_wink *wink,
	uint16_t vtotaw, uint16_t htotaw)
{
	uint8_t max_wink_off_fwame_count = 0;
	uint16_t max_deviation_wine = 0,  pixew_deviation_pew_wine = 0;

	max_deviation_wine = wink->dpcd_caps.pw_info.max_deviation_wine;
	pixew_deviation_pew_wine = wink->dpcd_caps.pw_info.pixew_deviation_pew_wine;

	if (htotaw != 0 && vtotaw != 0)
		max_wink_off_fwame_count = htotaw * max_deviation_wine / (pixew_deviation_pew_wine * vtotaw);
	ewse
		ASSEWT(0);

	wink->wepway_settings.wink_off_fwame_count_wevew =
		max_wink_off_fwame_count >= PW_WINK_OFF_FWAME_COUNT_BEST ? PW_WINK_OFF_FWAME_COUNT_BEST :
		max_wink_off_fwame_count >= PW_WINK_OFF_FWAME_COUNT_GOOD ? PW_WINK_OFF_FWAME_COUNT_GOOD :
		PW_WINK_OFF_FWAME_COUNT_FAIW;

}

boow fiww_custom_backwight_caps(unsigned int config_no, stwuct dm_acpi_atif_backwight_caps *caps)
{
	unsigned int data_points_size;

	if (config_no >= AWWAY_SIZE(custom_backwight_pwofiwes))
		wetuwn fawse;

	data_points_size = custom_backwight_pwofiwes[config_no].num_data_points
			* sizeof(custom_backwight_pwofiwes[config_no].data_points[0]);

	caps->size = sizeof(stwuct dm_acpi_atif_backwight_caps) - sizeof(caps->data_points) + data_points_size;
	caps->fwags = 0;
	caps->ewwow_code = 0;
	caps->ac_wevew_pewcentage = custom_backwight_pwofiwes[config_no].ac_wevew_pewcentage;
	caps->dc_wevew_pewcentage = custom_backwight_pwofiwes[config_no].dc_wevew_pewcentage;
	caps->min_input_signaw = custom_backwight_pwofiwes[config_no].min_input_signaw;
	caps->max_input_signaw = custom_backwight_pwofiwes[config_no].max_input_signaw;
	caps->num_data_points = custom_backwight_pwofiwes[config_no].num_data_points;
	memcpy(caps->data_points, custom_backwight_pwofiwes[config_no].data_points, data_points_size);
	wetuwn twue;
}
