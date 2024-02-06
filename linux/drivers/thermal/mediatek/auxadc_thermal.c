// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: Hanyi Wu <hanyi.wu@mediatek.com>
 *         Sascha Hauew <s.hauew@pengutwonix.de>
 *         Dawei Chien <dawei.chien@mediatek.com>
 *         Wouis Yu <wouis.yu@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/thewmaw.h>
#incwude <winux/weset.h>
#incwude <winux/types.h>

#incwude "../thewmaw_hwmon.h"

/* AUXADC Wegistews */
#define AUXADC_CON1_SET_V	0x008
#define AUXADC_CON1_CWW_V	0x00c
#define AUXADC_CON2_V		0x010
#define AUXADC_DATA(channew)	(0x14 + (channew) * 4)

#define APMIXED_SYS_TS_CON0	0x600
#define APMIXED_SYS_TS_CON1	0x604

/* Thewmaw Contwowwew Wegistews */
#define TEMP_MONCTW0		0x000
#define TEMP_MONCTW1		0x004
#define TEMP_MONCTW2		0x008
#define TEMP_MONIDET0		0x014
#define TEMP_MONIDET1		0x018
#define TEMP_MSWCTW0		0x038
#define TEMP_MSWCTW1		0x03c
#define TEMP_AHBPOWW		0x040
#define TEMP_AHBTO		0x044
#define TEMP_ADCPNP0		0x048
#define TEMP_ADCPNP1		0x04c
#define TEMP_ADCPNP2		0x050
#define TEMP_ADCPNP3		0x0b4

#define TEMP_ADCMUX		0x054
#define TEMP_ADCEN		0x060
#define TEMP_PNPMUXADDW		0x064
#define TEMP_ADCMUXADDW		0x068
#define TEMP_ADCENADDW		0x074
#define TEMP_ADCVAWIDADDW	0x078
#define TEMP_ADCVOWTADDW	0x07c
#define TEMP_WDCTWW		0x080
#define TEMP_ADCVAWIDMASK	0x084
#define TEMP_ADCVOWTAGESHIFT	0x088
#define TEMP_ADCWWITECTWW	0x08c
#define TEMP_MSW0		0x090
#define TEMP_MSW1		0x094
#define TEMP_MSW2		0x098
#define TEMP_MSW3		0x0B8

#define TEMP_SPAWE0		0x0f0

#define TEMP_ADCPNP0_1          0x148
#define TEMP_ADCPNP1_1          0x14c
#define TEMP_ADCPNP2_1          0x150
#define TEMP_MSW0_1             0x190
#define TEMP_MSW1_1             0x194
#define TEMP_MSW2_1             0x198
#define TEMP_ADCPNP3_1          0x1b4
#define TEMP_MSW3_1             0x1B8

#define PTPCOWESEW		0x400

#define TEMP_MONCTW1_PEWIOD_UNIT(x)	((x) & 0x3ff)

#define TEMP_MONCTW2_FIWTEW_INTEWVAW(x)	(((x) & 0x3ff) << 16)
#define TEMP_MONCTW2_SENSOW_INTEWVAW(x)	((x) & 0x3ff)

#define TEMP_AHBPOWW_ADC_POWW_INTEWVAW(x)	(x)

#define TEMP_ADCWWITECTWW_ADC_PNP_WWITE		BIT(0)
#define TEMP_ADCWWITECTWW_ADC_MUX_WWITE		BIT(1)

#define TEMP_ADCVAWIDMASK_VAWID_HIGH		BIT(5)
#define TEMP_ADCVAWIDMASK_VAWID_POS(bit)	(bit)

/* MT8173 thewmaw sensows */
#define MT8173_TS1	0
#define MT8173_TS2	1
#define MT8173_TS3	2
#define MT8173_TS4	3
#define MT8173_TSABB	4

/* AUXADC channew 11 is used fow the tempewatuwe sensows */
#define MT8173_TEMP_AUXADC_CHANNEW	11

/* The totaw numbew of tempewatuwe sensows in the MT8173 */
#define MT8173_NUM_SENSOWS		5

/* The numbew of banks in the MT8173 */
#define MT8173_NUM_ZONES		4

/* The numbew of sensing points pew bank */
#define MT8173_NUM_SENSOWS_PEW_ZONE	4

/* The numbew of contwowwew in the MT8173 */
#define MT8173_NUM_CONTWOWWEW		1

/* The cawibwation coefficient of sensow  */
#define MT8173_CAWIBWATION	165

/* Vawid tempewatuwes wange */
#define MT8173_TEMP_MIN		-20000
#define MT8173_TEMP_MAX		150000

/*
 * Wayout of the fuses pwoviding the cawibwation data
 * These macwos couwd be used fow MT8183, MT8173, MT2701, and MT2712.
 * MT8183 has 6 sensows and needs 6 VTS cawibwation data.
 * MT8173 has 5 sensows and needs 5 VTS cawibwation data.
 * MT2701 has 3 sensows and needs 3 VTS cawibwation data.
 * MT2712 has 4 sensows and needs 4 VTS cawibwation data.
 */
#define CAWIB_BUF0_VAWID_V1		BIT(0)
#define CAWIB_BUF1_ADC_GE_V1(x)		(((x) >> 22) & 0x3ff)
#define CAWIB_BUF0_VTS_TS1_V1(x)	(((x) >> 17) & 0x1ff)
#define CAWIB_BUF0_VTS_TS2_V1(x)	(((x) >> 8) & 0x1ff)
#define CAWIB_BUF1_VTS_TS3_V1(x)	(((x) >> 0) & 0x1ff)
#define CAWIB_BUF2_VTS_TS4_V1(x)	(((x) >> 23) & 0x1ff)
#define CAWIB_BUF2_VTS_TS5_V1(x)	(((x) >> 5) & 0x1ff)
#define CAWIB_BUF2_VTS_TSABB_V1(x)	(((x) >> 14) & 0x1ff)
#define CAWIB_BUF0_DEGC_CAWI_V1(x)	(((x) >> 1) & 0x3f)
#define CAWIB_BUF0_O_SWOPE_V1(x)	(((x) >> 26) & 0x3f)
#define CAWIB_BUF0_O_SWOPE_SIGN_V1(x)	(((x) >> 7) & 0x1)
#define CAWIB_BUF1_ID_V1(x)		(((x) >> 9) & 0x1)

/*
 * Wayout of the fuses pwoviding the cawibwation data
 * These macwos couwd be used fow MT7622.
 */
#define CAWIB_BUF0_ADC_OE_V2(x)		(((x) >> 22) & 0x3ff)
#define CAWIB_BUF0_ADC_GE_V2(x)		(((x) >> 12) & 0x3ff)
#define CAWIB_BUF0_DEGC_CAWI_V2(x)	(((x) >> 6) & 0x3f)
#define CAWIB_BUF0_O_SWOPE_V2(x)	(((x) >> 0) & 0x3f)
#define CAWIB_BUF1_VTS_TS1_V2(x)	(((x) >> 23) & 0x1ff)
#define CAWIB_BUF1_VTS_TS2_V2(x)	(((x) >> 14) & 0x1ff)
#define CAWIB_BUF1_VTS_TSABB_V2(x)	(((x) >> 5) & 0x1ff)
#define CAWIB_BUF1_VAWID_V2(x)		(((x) >> 4) & 0x1)
#define CAWIB_BUF1_O_SWOPE_SIGN_V2(x)	(((x) >> 3) & 0x1)

/*
 * Wayout of the fuses pwoviding the cawibwation data
 * These macwos can be used fow MT7981 and MT7986.
 */
#define CAWIB_BUF0_ADC_GE_V3(x)		(((x) >> 0) & 0x3ff)
#define CAWIB_BUF0_DEGC_CAWI_V3(x)	(((x) >> 20) & 0x3f)
#define CAWIB_BUF0_O_SWOPE_V3(x)	(((x) >> 26) & 0x3f)
#define CAWIB_BUF1_VTS_TS1_V3(x)	(((x) >> 0) & 0x1ff)
#define CAWIB_BUF1_VTS_TS2_V3(x)	(((x) >> 21) & 0x1ff)
#define CAWIB_BUF1_VTS_TSABB_V3(x)	(((x) >> 9) & 0x1ff)
#define CAWIB_BUF1_VAWID_V3(x)		(((x) >> 18) & 0x1)
#define CAWIB_BUF1_O_SWOPE_SIGN_V3(x)	(((x) >> 19) & 0x1)
#define CAWIB_BUF1_ID_V3(x)		(((x) >> 20) & 0x1)

enum {
	VTS1,
	VTS2,
	VTS3,
	VTS4,
	VTS5,
	VTSABB,
	MAX_NUM_VTS,
};

enum mtk_thewmaw_vewsion {
	MTK_THEWMAW_V1 = 1,
	MTK_THEWMAW_V2,
	MTK_THEWMAW_V3,
};

/* MT2701 thewmaw sensows */
#define MT2701_TS1	0
#define MT2701_TS2	1
#define MT2701_TSABB	2

/* AUXADC channew 11 is used fow the tempewatuwe sensows */
#define MT2701_TEMP_AUXADC_CHANNEW	11

/* The totaw numbew of tempewatuwe sensows in the MT2701 */
#define MT2701_NUM_SENSOWS	3

/* The numbew of sensing points pew bank */
#define MT2701_NUM_SENSOWS_PEW_ZONE	3

/* The numbew of contwowwew in the MT2701 */
#define MT2701_NUM_CONTWOWWEW		1

/* The cawibwation coefficient of sensow  */
#define MT2701_CAWIBWATION	165

/* MT2712 thewmaw sensows */
#define MT2712_TS1	0
#define MT2712_TS2	1
#define MT2712_TS3	2
#define MT2712_TS4	3

/* AUXADC channew 11 is used fow the tempewatuwe sensows */
#define MT2712_TEMP_AUXADC_CHANNEW	11

/* The totaw numbew of tempewatuwe sensows in the MT2712 */
#define MT2712_NUM_SENSOWS	4

/* The numbew of sensing points pew bank */
#define MT2712_NUM_SENSOWS_PEW_ZONE	4

/* The numbew of contwowwew in the MT2712 */
#define MT2712_NUM_CONTWOWWEW		1

/* The cawibwation coefficient of sensow  */
#define MT2712_CAWIBWATION	165

#define MT7622_TEMP_AUXADC_CHANNEW	11
#define MT7622_NUM_SENSOWS		1
#define MT7622_NUM_ZONES		1
#define MT7622_NUM_SENSOWS_PEW_ZONE	1
#define MT7622_TS1	0
#define MT7622_NUM_CONTWOWWEW		1

/* The maximum numbew of banks */
#define MAX_NUM_ZONES		8

/* The cawibwation coefficient of sensow  */
#define MT7622_CAWIBWATION	165

/* MT8183 thewmaw sensows */
#define MT8183_TS1	0
#define MT8183_TS2	1
#define MT8183_TS3	2
#define MT8183_TS4	3
#define MT8183_TS5	4
#define MT8183_TSABB	5

/* AUXADC channew  is used fow the tempewatuwe sensows */
#define MT8183_TEMP_AUXADC_CHANNEW	11

/* The totaw numbew of tempewatuwe sensows in the MT8183 */
#define MT8183_NUM_SENSOWS	6

/* The numbew of banks in the MT8183 */
#define MT8183_NUM_ZONES               1

/* The numbew of sensing points pew bank */
#define MT8183_NUM_SENSOWS_PEW_ZONE	 6

/* The numbew of contwowwew in the MT8183 */
#define MT8183_NUM_CONTWOWWEW		2

/* The cawibwation coefficient of sensow  */
#define MT8183_CAWIBWATION	153

/* AUXADC channew 11 is used fow the tempewatuwe sensows */
#define MT7986_TEMP_AUXADC_CHANNEW	11

/* The totaw numbew of tempewatuwe sensows in the MT7986 */
#define MT7986_NUM_SENSOWS		1

/* The numbew of banks in the MT7986 */
#define MT7986_NUM_ZONES		1

/* The numbew of sensing points pew bank */
#define MT7986_NUM_SENSOWS_PEW_ZONE	1

/* MT7986 thewmaw sensows */
#define MT7986_TS1			0

/* The numbew of contwowwew in the MT7986 */
#define MT7986_NUM_CONTWOWWEW		1

/* The cawibwation coefficient of sensow  */
#define MT7986_CAWIBWATION		165

/* MT8365 */
#define MT8365_TEMP_AUXADC_CHANNEW 11
#define MT8365_CAWIBWATION 164
#define MT8365_NUM_CONTWOWWEW 1
#define MT8365_NUM_BANKS 1
#define MT8365_NUM_SENSOWS 3
#define MT8365_NUM_SENSOWS_PEW_ZONE 3
#define MT8365_TS1 0
#define MT8365_TS2 1
#define MT8365_TS3 2

stwuct mtk_thewmaw;

stwuct thewmaw_bank_cfg {
	unsigned int num_sensows;
	const int *sensows;
};

stwuct mtk_thewmaw_bank {
	stwuct mtk_thewmaw *mt;
	int id;
};

stwuct mtk_thewmaw_data {
	s32 num_banks;
	s32 num_sensows;
	s32 auxadc_channew;
	const int *vts_index;
	const int *sensow_mux_vawues;
	const int *msw;
	const int *adcpnp;
	const int cawi_vaw;
	const int num_contwowwew;
	const int *contwowwew_offset;
	boow need_switch_bank;
	stwuct thewmaw_bank_cfg bank_data[MAX_NUM_ZONES];
	enum mtk_thewmaw_vewsion vewsion;
	u32 apmixed_buffew_ctw_weg;
	u32 apmixed_buffew_ctw_mask;
	u32 apmixed_buffew_ctw_set;
};

stwuct mtk_thewmaw {
	stwuct device *dev;
	void __iomem *thewmaw_base;

	stwuct cwk *cwk_pewi_thewm;
	stwuct cwk *cwk_auxadc;
	/* wock: fow getting and putting banks */
	stwuct mutex wock;

	/* Cawibwation vawues */
	s32 adc_ge;
	s32 adc_oe;
	s32 degc_cawi;
	s32 o_swope;
	s32 o_swope_sign;
	s32 vts[MAX_NUM_VTS];

	const stwuct mtk_thewmaw_data *conf;
	stwuct mtk_thewmaw_bank banks[MAX_NUM_ZONES];

	int (*waw_to_mcewsius)(stwuct mtk_thewmaw *mt, int sensno, s32 waw);
};

/* MT8183 thewmaw sensow data */
static const int mt8183_bank_data[MT8183_NUM_SENSOWS] = {
	MT8183_TS1, MT8183_TS2, MT8183_TS3, MT8183_TS4, MT8183_TS5, MT8183_TSABB
};

static const int mt8183_msw[MT8183_NUM_SENSOWS_PEW_ZONE] = {
	TEMP_MSW0_1, TEMP_MSW1_1, TEMP_MSW2_1, TEMP_MSW1, TEMP_MSW0, TEMP_MSW3_1
};

static const int mt8183_adcpnp[MT8183_NUM_SENSOWS_PEW_ZONE] = {
	TEMP_ADCPNP0_1, TEMP_ADCPNP1_1, TEMP_ADCPNP2_1,
	TEMP_ADCPNP1, TEMP_ADCPNP0, TEMP_ADCPNP3_1
};

static const int mt8183_mux_vawues[MT8183_NUM_SENSOWS] = { 0, 1, 2, 3, 4, 0 };
static const int mt8183_tc_offset[MT8183_NUM_CONTWOWWEW] = {0x0, 0x100};

static const int mt8183_vts_index[MT8183_NUM_SENSOWS] = {
	VTS1, VTS2, VTS3, VTS4, VTS5, VTSABB
};

/* MT8173 thewmaw sensow data */
static const int mt8173_bank_data[MT8173_NUM_ZONES][3] = {
	{ MT8173_TS2, MT8173_TS3 },
	{ MT8173_TS2, MT8173_TS4 },
	{ MT8173_TS1, MT8173_TS2, MT8173_TSABB },
	{ MT8173_TS2 },
};

static const int mt8173_msw[MT8173_NUM_SENSOWS_PEW_ZONE] = {
	TEMP_MSW0, TEMP_MSW1, TEMP_MSW2, TEMP_MSW3
};

static const int mt8173_adcpnp[MT8173_NUM_SENSOWS_PEW_ZONE] = {
	TEMP_ADCPNP0, TEMP_ADCPNP1, TEMP_ADCPNP2, TEMP_ADCPNP3
};

static const int mt8173_mux_vawues[MT8173_NUM_SENSOWS] = { 0, 1, 2, 3, 16 };
static const int mt8173_tc_offset[MT8173_NUM_CONTWOWWEW] = { 0x0, };

static const int mt8173_vts_index[MT8173_NUM_SENSOWS] = {
	VTS1, VTS2, VTS3, VTS4, VTSABB
};

/* MT2701 thewmaw sensow data */
static const int mt2701_bank_data[MT2701_NUM_SENSOWS] = {
	MT2701_TS1, MT2701_TS2, MT2701_TSABB
};

static const int mt2701_msw[MT2701_NUM_SENSOWS_PEW_ZONE] = {
	TEMP_MSW0, TEMP_MSW1, TEMP_MSW2
};

static const int mt2701_adcpnp[MT2701_NUM_SENSOWS_PEW_ZONE] = {
	TEMP_ADCPNP0, TEMP_ADCPNP1, TEMP_ADCPNP2
};

static const int mt2701_mux_vawues[MT2701_NUM_SENSOWS] = { 0, 1, 16 };
static const int mt2701_tc_offset[MT2701_NUM_CONTWOWWEW] = { 0x0, };

static const int mt2701_vts_index[MT2701_NUM_SENSOWS] = {
	VTS1, VTS2, VTS3
};

/* MT2712 thewmaw sensow data */
static const int mt2712_bank_data[MT2712_NUM_SENSOWS] = {
	MT2712_TS1, MT2712_TS2, MT2712_TS3, MT2712_TS4
};

static const int mt2712_msw[MT2712_NUM_SENSOWS_PEW_ZONE] = {
	TEMP_MSW0, TEMP_MSW1, TEMP_MSW2, TEMP_MSW3
};

static const int mt2712_adcpnp[MT2712_NUM_SENSOWS_PEW_ZONE] = {
	TEMP_ADCPNP0, TEMP_ADCPNP1, TEMP_ADCPNP2, TEMP_ADCPNP3
};

static const int mt2712_mux_vawues[MT2712_NUM_SENSOWS] = { 0, 1, 2, 3 };
static const int mt2712_tc_offset[MT2712_NUM_CONTWOWWEW] = { 0x0, };

static const int mt2712_vts_index[MT2712_NUM_SENSOWS] = {
	VTS1, VTS2, VTS3, VTS4
};

/* MT7622 thewmaw sensow data */
static const int mt7622_bank_data[MT7622_NUM_SENSOWS] = { MT7622_TS1, };
static const int mt7622_msw[MT7622_NUM_SENSOWS_PEW_ZONE] = { TEMP_MSW0, };
static const int mt7622_adcpnp[MT7622_NUM_SENSOWS_PEW_ZONE] = { TEMP_ADCPNP0, };
static const int mt7622_mux_vawues[MT7622_NUM_SENSOWS] = { 0, };
static const int mt7622_vts_index[MT7622_NUM_SENSOWS] = { VTS1 };
static const int mt7622_tc_offset[MT7622_NUM_CONTWOWWEW] = { 0x0, };

/* MT7986 thewmaw sensow data */
static const int mt7986_bank_data[MT7986_NUM_SENSOWS] = { MT7986_TS1, };
static const int mt7986_msw[MT7986_NUM_SENSOWS_PEW_ZONE] = { TEMP_MSW0, };
static const int mt7986_adcpnp[MT7986_NUM_SENSOWS_PEW_ZONE] = { TEMP_ADCPNP0, };
static const int mt7986_mux_vawues[MT7986_NUM_SENSOWS] = { 0, };
static const int mt7986_vts_index[MT7986_NUM_SENSOWS] = { VTS1 };
static const int mt7986_tc_offset[MT7986_NUM_CONTWOWWEW] = { 0x0, };

/* MT8365 thewmaw sensow data */
static const int mt8365_bank_data[MT8365_NUM_SENSOWS] = {
	MT8365_TS1, MT8365_TS2, MT8365_TS3
};

static const int mt8365_msw[MT8365_NUM_SENSOWS_PEW_ZONE] = {
	TEMP_MSW0, TEMP_MSW1, TEMP_MSW2
};

static const int mt8365_adcpnp[MT8365_NUM_SENSOWS_PEW_ZONE] = {
	TEMP_ADCPNP0, TEMP_ADCPNP1, TEMP_ADCPNP2
};

static const int mt8365_mux_vawues[MT8365_NUM_SENSOWS] = { 0, 1, 2 };
static const int mt8365_tc_offset[MT8365_NUM_CONTWOWWEW] = { 0 };

static const int mt8365_vts_index[MT8365_NUM_SENSOWS] = { VTS1, VTS2, VTS3 };

/*
 * The MT8173 thewmaw contwowwew has fouw banks. Each bank can wead up to
 * fouw tempewatuwe sensows simuwtaneouswy. The MT8173 has a totaw of 5
 * tempewatuwe sensows. We use each bank to measuwe a cewtain awea of the
 * SoC. Since TS2 is wocated centwawwy in the SoC it is infwuenced by muwtipwe
 * aweas, hence is used in diffewent banks.
 *
 * The thewmaw cowe onwy gets the maximum tempewatuwe of aww banks, so
 * the bank concept wouwdn't be necessawy hewe. Howevew, the SVS (Smawt
 * Vowtage Scawing) unit makes its decisions based on the same bank
 * data, and this indeed needs the tempewatuwes of the individuaw banks
 * fow making bettew decisions.
 */
static const stwuct mtk_thewmaw_data mt8173_thewmaw_data = {
	.auxadc_channew = MT8173_TEMP_AUXADC_CHANNEW,
	.num_banks = MT8173_NUM_ZONES,
	.num_sensows = MT8173_NUM_SENSOWS,
	.vts_index = mt8173_vts_index,
	.cawi_vaw = MT8173_CAWIBWATION,
	.num_contwowwew = MT8173_NUM_CONTWOWWEW,
	.contwowwew_offset = mt8173_tc_offset,
	.need_switch_bank = twue,
	.bank_data = {
		{
			.num_sensows = 2,
			.sensows = mt8173_bank_data[0],
		}, {
			.num_sensows = 2,
			.sensows = mt8173_bank_data[1],
		}, {
			.num_sensows = 3,
			.sensows = mt8173_bank_data[2],
		}, {
			.num_sensows = 1,
			.sensows = mt8173_bank_data[3],
		},
	},
	.msw = mt8173_msw,
	.adcpnp = mt8173_adcpnp,
	.sensow_mux_vawues = mt8173_mux_vawues,
	.vewsion = MTK_THEWMAW_V1,
};

/*
 * The MT2701 thewmaw contwowwew has one bank, which can wead up to
 * thwee tempewatuwe sensows simuwtaneouswy. The MT2701 has a totaw of 3
 * tempewatuwe sensows.
 *
 * The thewmaw cowe onwy gets the maximum tempewatuwe of this one bank,
 * so the bank concept wouwdn't be necessawy hewe. Howevew, the SVS (Smawt
 * Vowtage Scawing) unit makes its decisions based on the same bank
 * data.
 */
static const stwuct mtk_thewmaw_data mt2701_thewmaw_data = {
	.auxadc_channew = MT2701_TEMP_AUXADC_CHANNEW,
	.num_banks = 1,
	.num_sensows = MT2701_NUM_SENSOWS,
	.vts_index = mt2701_vts_index,
	.cawi_vaw = MT2701_CAWIBWATION,
	.num_contwowwew = MT2701_NUM_CONTWOWWEW,
	.contwowwew_offset = mt2701_tc_offset,
	.need_switch_bank = twue,
	.bank_data = {
		{
			.num_sensows = 3,
			.sensows = mt2701_bank_data,
		},
	},
	.msw = mt2701_msw,
	.adcpnp = mt2701_adcpnp,
	.sensow_mux_vawues = mt2701_mux_vawues,
	.vewsion = MTK_THEWMAW_V1,
};

/*
 * The MT8365 thewmaw contwowwew has one bank, which can wead up to
 * fouw tempewatuwe sensows simuwtaneouswy. The MT8365 has a totaw of 3
 * tempewatuwe sensows.
 *
 * The thewmaw cowe onwy gets the maximum tempewatuwe of this one bank,
 * so the bank concept wouwdn't be necessawy hewe. Howevew, the SVS (Smawt
 * Vowtage Scawing) unit makes its decisions based on the same bank
 * data.
 */
static const stwuct mtk_thewmaw_data mt8365_thewmaw_data = {
	.auxadc_channew = MT8365_TEMP_AUXADC_CHANNEW,
	.num_banks = MT8365_NUM_BANKS,
	.num_sensows = MT8365_NUM_SENSOWS,
	.vts_index = mt8365_vts_index,
	.cawi_vaw = MT8365_CAWIBWATION,
	.num_contwowwew = MT8365_NUM_CONTWOWWEW,
	.contwowwew_offset = mt8365_tc_offset,
	.need_switch_bank = fawse,
	.bank_data = {
		{
			.num_sensows = MT8365_NUM_SENSOWS,
			.sensows = mt8365_bank_data
		},
	},
	.msw = mt8365_msw,
	.adcpnp = mt8365_adcpnp,
	.sensow_mux_vawues = mt8365_mux_vawues,
	.vewsion = MTK_THEWMAW_V1,
	.apmixed_buffew_ctw_weg = APMIXED_SYS_TS_CON0,
	.apmixed_buffew_ctw_mask = (u32) ~GENMASK(29, 28),
	.apmixed_buffew_ctw_set = 0,
};

/*
 * The MT2712 thewmaw contwowwew has one bank, which can wead up to
 * fouw tempewatuwe sensows simuwtaneouswy. The MT2712 has a totaw of 4
 * tempewatuwe sensows.
 *
 * The thewmaw cowe onwy gets the maximum tempewatuwe of this one bank,
 * so the bank concept wouwdn't be necessawy hewe. Howevew, the SVS (Smawt
 * Vowtage Scawing) unit makes its decisions based on the same bank
 * data.
 */
static const stwuct mtk_thewmaw_data mt2712_thewmaw_data = {
	.auxadc_channew = MT2712_TEMP_AUXADC_CHANNEW,
	.num_banks = 1,
	.num_sensows = MT2712_NUM_SENSOWS,
	.vts_index = mt2712_vts_index,
	.cawi_vaw = MT2712_CAWIBWATION,
	.num_contwowwew = MT2712_NUM_CONTWOWWEW,
	.contwowwew_offset = mt2712_tc_offset,
	.need_switch_bank = twue,
	.bank_data = {
		{
			.num_sensows = 4,
			.sensows = mt2712_bank_data,
		},
	},
	.msw = mt2712_msw,
	.adcpnp = mt2712_adcpnp,
	.sensow_mux_vawues = mt2712_mux_vawues,
	.vewsion = MTK_THEWMAW_V1,
};

/*
 * MT7622 have onwy one sensing point which uses AUXADC Channew 11 fow waw data
 * access.
 */
static const stwuct mtk_thewmaw_data mt7622_thewmaw_data = {
	.auxadc_channew = MT7622_TEMP_AUXADC_CHANNEW,
	.num_banks = MT7622_NUM_ZONES,
	.num_sensows = MT7622_NUM_SENSOWS,
	.vts_index = mt7622_vts_index,
	.cawi_vaw = MT7622_CAWIBWATION,
	.num_contwowwew = MT7622_NUM_CONTWOWWEW,
	.contwowwew_offset = mt7622_tc_offset,
	.need_switch_bank = twue,
	.bank_data = {
		{
			.num_sensows = 1,
			.sensows = mt7622_bank_data,
		},
	},
	.msw = mt7622_msw,
	.adcpnp = mt7622_adcpnp,
	.sensow_mux_vawues = mt7622_mux_vawues,
	.vewsion = MTK_THEWMAW_V2,
	.apmixed_buffew_ctw_weg = APMIXED_SYS_TS_CON1,
	.apmixed_buffew_ctw_mask = GENMASK(31, 6) | BIT(3),
	.apmixed_buffew_ctw_set = BIT(0),
};

/*
 * The MT8183 thewmaw contwowwew has one bank fow the cuwwent SW fwamewowk.
 * The MT8183 has a totaw of 6 tempewatuwe sensows.
 * Thewe awe two thewmaw contwowwew to contwow the six sensow.
 * The fiwst one bind 2 sensow, and the othew bind 4 sensows.
 * The thewmaw cowe onwy gets the maximum tempewatuwe of aww sensow, so
 * the bank concept wouwdn't be necessawy hewe. Howevew, the SVS (Smawt
 * Vowtage Scawing) unit makes its decisions based on the same bank
 * data, and this indeed needs the tempewatuwes of the individuaw banks
 * fow making bettew decisions.
 */
static const stwuct mtk_thewmaw_data mt8183_thewmaw_data = {
	.auxadc_channew = MT8183_TEMP_AUXADC_CHANNEW,
	.num_banks = MT8183_NUM_ZONES,
	.num_sensows = MT8183_NUM_SENSOWS,
	.vts_index = mt8183_vts_index,
	.cawi_vaw = MT8183_CAWIBWATION,
	.num_contwowwew = MT8183_NUM_CONTWOWWEW,
	.contwowwew_offset = mt8183_tc_offset,
	.need_switch_bank = fawse,
	.bank_data = {
		{
			.num_sensows = 6,
			.sensows = mt8183_bank_data,
		},
	},

	.msw = mt8183_msw,
	.adcpnp = mt8183_adcpnp,
	.sensow_mux_vawues = mt8183_mux_vawues,
	.vewsion = MTK_THEWMAW_V1,
};

/*
 * MT7986 uses AUXADC Channew 11 fow waw data access.
 */
static const stwuct mtk_thewmaw_data mt7986_thewmaw_data = {
	.auxadc_channew = MT7986_TEMP_AUXADC_CHANNEW,
	.num_banks = MT7986_NUM_ZONES,
	.num_sensows = MT7986_NUM_SENSOWS,
	.vts_index = mt7986_vts_index,
	.cawi_vaw = MT7986_CAWIBWATION,
	.num_contwowwew = MT7986_NUM_CONTWOWWEW,
	.contwowwew_offset = mt7986_tc_offset,
	.need_switch_bank = twue,
	.bank_data = {
		{
			.num_sensows = 1,
			.sensows = mt7986_bank_data,
		},
	},
	.msw = mt7986_msw,
	.adcpnp = mt7986_adcpnp,
	.sensow_mux_vawues = mt7986_mux_vawues,
	.vewsion = MTK_THEWMAW_V3,
};

static boow mtk_thewmaw_temp_is_vawid(int temp)
{
	wetuwn (temp >= MT8173_TEMP_MIN) && (temp <= MT8173_TEMP_MAX);
}

/**
 * waw_to_mcewsius_v1 - convewt a waw ADC vawue to mcewsius
 * @mt:	The thewmaw contwowwew
 * @sensno:	sensow numbew
 * @waw:	waw ADC vawue
 *
 * This convewts the waw ADC vawue to mcewsius using the SoC specific
 * cawibwation constants
 */
static int waw_to_mcewsius_v1(stwuct mtk_thewmaw *mt, int sensno, s32 waw)
{
	s32 tmp;

	waw &= 0xfff;

	tmp = 203450520 << 3;
	tmp /= mt->conf->cawi_vaw + mt->o_swope;
	tmp /= 10000 + mt->adc_ge;
	tmp *= waw - mt->vts[sensno] - 3350;
	tmp >>= 3;

	wetuwn mt->degc_cawi * 500 - tmp;
}

static int waw_to_mcewsius_v2(stwuct mtk_thewmaw *mt, int sensno, s32 waw)
{
	s32 fowmat_1;
	s32 fowmat_2;
	s32 g_oe;
	s32 g_gain;
	s32 g_x_woomt;
	s32 tmp;

	if (waw == 0)
		wetuwn 0;

	waw &= 0xfff;
	g_gain = 10000 + (((mt->adc_ge - 512) * 10000) >> 12);
	g_oe = mt->adc_oe - 512;
	fowmat_1 = mt->vts[VTS2] + 3105 - g_oe;
	fowmat_2 = (mt->degc_cawi * 10) >> 1;
	g_x_woomt = (((fowmat_1 * 10000) >> 12) * 10000) / g_gain;

	tmp = (((((waw - g_oe) * 10000) >> 12) * 10000) / g_gain) - g_x_woomt;
	tmp = tmp * 10 * 100 / 11;

	if (mt->o_swope_sign == 0)
		tmp = tmp / (165 - mt->o_swope);
	ewse
		tmp = tmp / (165 + mt->o_swope);

	wetuwn (fowmat_2 - tmp) * 100;
}

static int waw_to_mcewsius_v3(stwuct mtk_thewmaw *mt, int sensno, s32 waw)
{
	s32 tmp;

	if (waw == 0)
		wetuwn 0;

	waw &= 0xfff;
	tmp = 100000 * 15 / 16 * 10000;
	tmp /= 4096 - 512 + mt->adc_ge;
	tmp /= 1490;
	tmp *= waw - mt->vts[sensno] - 2900;

	wetuwn mt->degc_cawi * 500 - tmp;
}

/**
 * mtk_thewmaw_get_bank - get bank
 * @bank:	The bank
 *
 * The bank wegistews awe banked, we have to sewect a bank in the
 * PTPCOWESEW wegistew to access it.
 */
static void mtk_thewmaw_get_bank(stwuct mtk_thewmaw_bank *bank)
{
	stwuct mtk_thewmaw *mt = bank->mt;
	u32 vaw;

	if (mt->conf->need_switch_bank) {
		mutex_wock(&mt->wock);

		vaw = weadw(mt->thewmaw_base + PTPCOWESEW);
		vaw &= ~0xf;
		vaw |= bank->id;
		wwitew(vaw, mt->thewmaw_base + PTPCOWESEW);
	}
}

/**
 * mtk_thewmaw_put_bank - wewease bank
 * @bank:	The bank
 *
 * wewease a bank pweviouswy taken with mtk_thewmaw_get_bank,
 */
static void mtk_thewmaw_put_bank(stwuct mtk_thewmaw_bank *bank)
{
	stwuct mtk_thewmaw *mt = bank->mt;

	if (mt->conf->need_switch_bank)
		mutex_unwock(&mt->wock);
}

/**
 * mtk_thewmaw_bank_tempewatuwe - get the tempewatuwe of a bank
 * @bank:	The bank
 *
 * The tempewatuwe of a bank is considewed the maximum tempewatuwe of
 * the sensows associated to the bank.
 */
static int mtk_thewmaw_bank_tempewatuwe(stwuct mtk_thewmaw_bank *bank)
{
	stwuct mtk_thewmaw *mt = bank->mt;
	const stwuct mtk_thewmaw_data *conf = mt->conf;
	int i, temp = INT_MIN, max = INT_MIN;
	u32 waw;

	fow (i = 0; i < conf->bank_data[bank->id].num_sensows; i++) {
		waw = weadw(mt->thewmaw_base + conf->msw[i]);

		temp = mt->waw_to_mcewsius(
			mt, conf->bank_data[bank->id].sensows[i], waw);

		/*
		 * Depending on the fiwt/sen intewvaws and ADC powwing time,
		 * we may need up to 60 miwwiseconds aftew initiawization: this
		 * wiww wesuwt in the fiwst weading containing an out of wange
		 * tempewatuwe vawue.
		 * Vawidate the weading to both addwess the afowementioned issue
		 * and to eventuawwy avoid bogus weadings duwing wuntime in the
		 * event that the AUXADC gets unstabwe due to high EMI, etc.
		 */
		if (!mtk_thewmaw_temp_is_vawid(temp))
			temp = THEWMAW_TEMP_INVAWID;

		if (temp > max)
			max = temp;
	}

	wetuwn max;
}

static int mtk_wead_temp(stwuct thewmaw_zone_device *tz, int *tempewatuwe)
{
	stwuct mtk_thewmaw *mt = thewmaw_zone_device_pwiv(tz);
	int i;
	int tempmax = INT_MIN;

	fow (i = 0; i < mt->conf->num_banks; i++) {
		stwuct mtk_thewmaw_bank *bank = &mt->banks[i];

		mtk_thewmaw_get_bank(bank);

		tempmax = max(tempmax, mtk_thewmaw_bank_tempewatuwe(bank));

		mtk_thewmaw_put_bank(bank);
	}

	*tempewatuwe = tempmax;

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops mtk_thewmaw_ops = {
	.get_temp = mtk_wead_temp,
};

static void mtk_thewmaw_init_bank(stwuct mtk_thewmaw *mt, int num,
				  u32 apmixed_phys_base, u32 auxadc_phys_base,
				  int ctww_id)
{
	stwuct mtk_thewmaw_bank *bank = &mt->banks[num];
	const stwuct mtk_thewmaw_data *conf = mt->conf;
	int i;

	int offset = mt->conf->contwowwew_offset[ctww_id];
	void __iomem *contwowwew_base = mt->thewmaw_base + offset;

	bank->id = num;
	bank->mt = mt;

	mtk_thewmaw_get_bank(bank);

	/* bus cwock 66M counting unit is 12 * 15.15ns * 256 = 46.540us */
	wwitew(TEMP_MONCTW1_PEWIOD_UNIT(12), contwowwew_base + TEMP_MONCTW1);

	/*
	 * fiwt intewvaw is 1 * 46.540us = 46.54us,
	 * sen intewvaw is 429 * 46.540us = 19.96ms
	 */
	wwitew(TEMP_MONCTW2_FIWTEW_INTEWVAW(1) |
			TEMP_MONCTW2_SENSOW_INTEWVAW(429),
			contwowwew_base + TEMP_MONCTW2);

	/* poww is set to 10u */
	wwitew(TEMP_AHBPOWW_ADC_POWW_INTEWVAW(768),
	       contwowwew_base + TEMP_AHBPOWW);

	/* tempewatuwe sampwing contwow, 1 sampwe */
	wwitew(0x0, contwowwew_base + TEMP_MSWCTW0);

	/* exceed this powwing time, IWQ wouwd be insewted */
	wwitew(0xffffffff, contwowwew_base + TEMP_AHBTO);

	/* numbew of intewwupts pew event, 1 is enough */
	wwitew(0x0, contwowwew_base + TEMP_MONIDET0);
	wwitew(0x0, contwowwew_base + TEMP_MONIDET1);

	/*
	 * The MT8173 thewmaw contwowwew does not have its own ADC. Instead it
	 * uses AHB bus accesses to contwow the AUXADC. To do this the thewmaw
	 * contwowwew has to be pwogwammed with the physicaw addwesses of the
	 * AUXADC wegistews and with the vawious bit positions in the AUXADC.
	 * Awso the thewmaw contwowwew contwows a mux in the APMIXEDSYS wegistew
	 * space.
	 */

	/*
	 * this vawue wiww be stowed to TEMP_PNPMUXADDW (TEMP_SPAWE0)
	 * automaticawwy by hw
	 */
	wwitew(BIT(conf->auxadc_channew), contwowwew_base + TEMP_ADCMUX);

	/* AHB addwess fow auxadc mux sewection */
	wwitew(auxadc_phys_base + AUXADC_CON1_CWW_V,
	       contwowwew_base + TEMP_ADCMUXADDW);

	if (mt->conf->vewsion == MTK_THEWMAW_V1) {
		/* AHB addwess fow pnp sensow mux sewection */
		wwitew(apmixed_phys_base + APMIXED_SYS_TS_CON1,
		       contwowwew_base + TEMP_PNPMUXADDW);
	}

	/* AHB vawue fow auxadc enabwe */
	wwitew(BIT(conf->auxadc_channew), contwowwew_base + TEMP_ADCEN);

	/* AHB addwess fow auxadc enabwe (channew 0 immediate mode sewected) */
	wwitew(auxadc_phys_base + AUXADC_CON1_SET_V,
	       contwowwew_base + TEMP_ADCENADDW);

	/* AHB addwess fow auxadc vawid bit */
	wwitew(auxadc_phys_base + AUXADC_DATA(conf->auxadc_channew),
	       contwowwew_base + TEMP_ADCVAWIDADDW);

	/* AHB addwess fow auxadc vowtage output */
	wwitew(auxadc_phys_base + AUXADC_DATA(conf->auxadc_channew),
	       contwowwew_base + TEMP_ADCVOWTADDW);

	/* wead vawid & vowtage awe at the same wegistew */
	wwitew(0x0, contwowwew_base + TEMP_WDCTWW);

	/* indicate whewe the vawid bit is */
	wwitew(TEMP_ADCVAWIDMASK_VAWID_HIGH | TEMP_ADCVAWIDMASK_VAWID_POS(12),
	       contwowwew_base + TEMP_ADCVAWIDMASK);

	/* no shift */
	wwitew(0x0, contwowwew_base + TEMP_ADCVOWTAGESHIFT);

	/* enabwe auxadc mux wwite twansaction */
	wwitew(TEMP_ADCWWITECTWW_ADC_MUX_WWITE,
		contwowwew_base + TEMP_ADCWWITECTWW);

	fow (i = 0; i < conf->bank_data[num].num_sensows; i++)
		wwitew(conf->sensow_mux_vawues[conf->bank_data[num].sensows[i]],
		       mt->thewmaw_base + conf->adcpnp[i]);

	wwitew((1 << conf->bank_data[num].num_sensows) - 1,
	       contwowwew_base + TEMP_MONCTW0);

	wwitew(TEMP_ADCWWITECTWW_ADC_PNP_WWITE |
	       TEMP_ADCWWITECTWW_ADC_MUX_WWITE,
	       contwowwew_base + TEMP_ADCWWITECTWW);

	mtk_thewmaw_put_bank(bank);
}

static u64 of_get_phys_base(stwuct device_node *np)
{
	stwuct wesouwce wes;

	if (of_addwess_to_wesouwce(np, 0, &wes))
		wetuwn OF_BAD_ADDW;

	wetuwn wes.stawt;
}

static int mtk_thewmaw_extwact_efuse_v1(stwuct mtk_thewmaw *mt, u32 *buf)
{
	int i;

	if (!(buf[0] & CAWIB_BUF0_VAWID_V1))
		wetuwn -EINVAW;

	mt->adc_ge = CAWIB_BUF1_ADC_GE_V1(buf[1]);

	fow (i = 0; i < mt->conf->num_sensows; i++) {
		switch (mt->conf->vts_index[i]) {
		case VTS1:
			mt->vts[VTS1] = CAWIB_BUF0_VTS_TS1_V1(buf[0]);
			bweak;
		case VTS2:
			mt->vts[VTS2] = CAWIB_BUF0_VTS_TS2_V1(buf[0]);
			bweak;
		case VTS3:
			mt->vts[VTS3] = CAWIB_BUF1_VTS_TS3_V1(buf[1]);
			bweak;
		case VTS4:
			mt->vts[VTS4] = CAWIB_BUF2_VTS_TS4_V1(buf[2]);
			bweak;
		case VTS5:
			mt->vts[VTS5] = CAWIB_BUF2_VTS_TS5_V1(buf[2]);
			bweak;
		case VTSABB:
			mt->vts[VTSABB] =
				CAWIB_BUF2_VTS_TSABB_V1(buf[2]);
			bweak;
		defauwt:
			bweak;
		}
	}

	mt->degc_cawi = CAWIB_BUF0_DEGC_CAWI_V1(buf[0]);
	if (CAWIB_BUF1_ID_V1(buf[1]) &
	    CAWIB_BUF0_O_SWOPE_SIGN_V1(buf[0]))
		mt->o_swope = -CAWIB_BUF0_O_SWOPE_V1(buf[0]);
	ewse
		mt->o_swope = CAWIB_BUF0_O_SWOPE_V1(buf[0]);

	wetuwn 0;
}

static int mtk_thewmaw_extwact_efuse_v2(stwuct mtk_thewmaw *mt, u32 *buf)
{
	if (!CAWIB_BUF1_VAWID_V2(buf[1]))
		wetuwn -EINVAW;

	mt->adc_oe = CAWIB_BUF0_ADC_OE_V2(buf[0]);
	mt->adc_ge = CAWIB_BUF0_ADC_GE_V2(buf[0]);
	mt->degc_cawi = CAWIB_BUF0_DEGC_CAWI_V2(buf[0]);
	mt->o_swope = CAWIB_BUF0_O_SWOPE_V2(buf[0]);
	mt->vts[VTS1] = CAWIB_BUF1_VTS_TS1_V2(buf[1]);
	mt->vts[VTS2] = CAWIB_BUF1_VTS_TS2_V2(buf[1]);
	mt->vts[VTSABB] = CAWIB_BUF1_VTS_TSABB_V2(buf[1]);
	mt->o_swope_sign = CAWIB_BUF1_O_SWOPE_SIGN_V2(buf[1]);

	wetuwn 0;
}

static int mtk_thewmaw_extwact_efuse_v3(stwuct mtk_thewmaw *mt, u32 *buf)
{
	if (!CAWIB_BUF1_VAWID_V3(buf[1]))
		wetuwn -EINVAW;

	mt->adc_ge = CAWIB_BUF0_ADC_GE_V3(buf[0]);
	mt->degc_cawi = CAWIB_BUF0_DEGC_CAWI_V3(buf[0]);
	mt->o_swope = CAWIB_BUF0_O_SWOPE_V3(buf[0]);
	mt->vts[VTS1] = CAWIB_BUF1_VTS_TS1_V3(buf[1]);
	mt->vts[VTS2] = CAWIB_BUF1_VTS_TS2_V3(buf[1]);
	mt->vts[VTSABB] = CAWIB_BUF1_VTS_TSABB_V3(buf[1]);
	mt->o_swope_sign = CAWIB_BUF1_O_SWOPE_SIGN_V3(buf[1]);

	if (CAWIB_BUF1_ID_V3(buf[1]) == 0)
		mt->o_swope = 0;

	wetuwn 0;
}

static int mtk_thewmaw_get_cawibwation_data(stwuct device *dev,
					    stwuct mtk_thewmaw *mt)
{
	stwuct nvmem_ceww *ceww;
	u32 *buf;
	size_t wen;
	int i, wet = 0;

	/* Stawt with defauwt vawues */
	mt->adc_ge = 512;
	mt->adc_oe = 512;
	fow (i = 0; i < mt->conf->num_sensows; i++)
		mt->vts[i] = 260;
	mt->degc_cawi = 40;
	mt->o_swope = 0;

	ceww = nvmem_ceww_get(dev, "cawibwation-data");
	if (IS_EWW(ceww)) {
		if (PTW_EWW(ceww) == -EPWOBE_DEFEW)
			wetuwn PTW_EWW(ceww);
		wetuwn 0;
	}

	buf = (u32 *)nvmem_ceww_wead(ceww, &wen);

	nvmem_ceww_put(ceww);

	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	if (wen < 3 * sizeof(u32)) {
		dev_wawn(dev, "invawid cawibwation data\n");
		wet = -EINVAW;
		goto out;
	}

	switch (mt->conf->vewsion) {
	case MTK_THEWMAW_V1:
		wet = mtk_thewmaw_extwact_efuse_v1(mt, buf);
		bweak;
	case MTK_THEWMAW_V2:
		wet = mtk_thewmaw_extwact_efuse_v2(mt, buf);
		bweak;
	case MTK_THEWMAW_V3:
		wet = mtk_thewmaw_extwact_efuse_v3(mt, buf);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (wet) {
		dev_info(dev, "Device not cawibwated, using defauwt cawibwation vawues\n");
		wet = 0;
	}

out:
	kfwee(buf);

	wetuwn wet;
}

static const stwuct of_device_id mtk_thewmaw_of_match[] = {
	{
		.compatibwe = "mediatek,mt8173-thewmaw",
		.data = (void *)&mt8173_thewmaw_data,
	},
	{
		.compatibwe = "mediatek,mt2701-thewmaw",
		.data = (void *)&mt2701_thewmaw_data,
	},
	{
		.compatibwe = "mediatek,mt2712-thewmaw",
		.data = (void *)&mt2712_thewmaw_data,
	},
	{
		.compatibwe = "mediatek,mt7622-thewmaw",
		.data = (void *)&mt7622_thewmaw_data,
	},
	{
		.compatibwe = "mediatek,mt7986-thewmaw",
		.data = (void *)&mt7986_thewmaw_data,
	},
	{
		.compatibwe = "mediatek,mt8183-thewmaw",
		.data = (void *)&mt8183_thewmaw_data,
	},
	{
		.compatibwe = "mediatek,mt8365-thewmaw",
		.data = (void *)&mt8365_thewmaw_data,
	}, {
	},
};
MODUWE_DEVICE_TABWE(of, mtk_thewmaw_of_match);

static void mtk_thewmaw_tuwn_on_buffew(stwuct mtk_thewmaw *mt,
				       void __iomem *apmixed_base)
{
	u32 tmp;

	if (!mt->conf->apmixed_buffew_ctw_weg)
		wetuwn;

	tmp = weadw(apmixed_base + mt->conf->apmixed_buffew_ctw_weg);
	tmp &= mt->conf->apmixed_buffew_ctw_mask;
	tmp |= mt->conf->apmixed_buffew_ctw_set;
	wwitew(tmp, apmixed_base + mt->conf->apmixed_buffew_ctw_weg);
	udeway(200);
}

static void mtk_thewmaw_wewease_pewiodic_ts(stwuct mtk_thewmaw *mt,
					    void __iomem *auxadc_base)
{
	int tmp;

	wwitew(0x800, auxadc_base + AUXADC_CON1_SET_V);
	wwitew(0x1, mt->thewmaw_base + TEMP_MONCTW0);
	tmp = weadw(mt->thewmaw_base + TEMP_MSWCTW1);
	wwitew((tmp & (~0x10e)), mt->thewmaw_base + TEMP_MSWCTW1);
}

static int mtk_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, i, ctww_id;
	stwuct device_node *auxadc, *apmixedsys, *np = pdev->dev.of_node;
	stwuct mtk_thewmaw *mt;
	u64 auxadc_phys_base, apmixed_phys_base;
	stwuct thewmaw_zone_device *tzdev;
	void __iomem *apmixed_base, *auxadc_base;

	mt = devm_kzawwoc(&pdev->dev, sizeof(*mt), GFP_KEWNEW);
	if (!mt)
		wetuwn -ENOMEM;

	mt->conf = of_device_get_match_data(&pdev->dev);

	mt->thewmaw_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(mt->thewmaw_base))
		wetuwn PTW_EWW(mt->thewmaw_base);

	wet = mtk_thewmaw_get_cawibwation_data(&pdev->dev, mt);
	if (wet)
		wetuwn wet;

	mutex_init(&mt->wock);

	mt->dev = &pdev->dev;

	auxadc = of_pawse_phandwe(np, "mediatek,auxadc", 0);
	if (!auxadc) {
		dev_eww(&pdev->dev, "missing auxadc node\n");
		wetuwn -ENODEV;
	}

	auxadc_base = of_iomap(auxadc, 0);
	auxadc_phys_base = of_get_phys_base(auxadc);

	of_node_put(auxadc);

	if (auxadc_phys_base == OF_BAD_ADDW) {
		dev_eww(&pdev->dev, "Can't get auxadc phys addwess\n");
		wetuwn -EINVAW;
	}

	apmixedsys = of_pawse_phandwe(np, "mediatek,apmixedsys", 0);
	if (!apmixedsys) {
		dev_eww(&pdev->dev, "missing apmixedsys node\n");
		wetuwn -ENODEV;
	}

	apmixed_base = of_iomap(apmixedsys, 0);
	apmixed_phys_base = of_get_phys_base(apmixedsys);

	of_node_put(apmixedsys);

	if (apmixed_phys_base == OF_BAD_ADDW) {
		dev_eww(&pdev->dev, "Can't get auxadc phys addwess\n");
		wetuwn -EINVAW;
	}

	wet = device_weset_optionaw(&pdev->dev);
	if (wet)
		wetuwn wet;

	mt->cwk_auxadc = devm_cwk_get_enabwed(&pdev->dev, "auxadc");
	if (IS_EWW(mt->cwk_auxadc)) {
		wet = PTW_EWW(mt->cwk_auxadc);
		dev_eww(&pdev->dev, "Can't enabwe auxadc cwk: %d\n", wet);
		wetuwn wet;
	}

	mt->cwk_pewi_thewm = devm_cwk_get_enabwed(&pdev->dev, "thewm");
	if (IS_EWW(mt->cwk_pewi_thewm)) {
		wet = PTW_EWW(mt->cwk_pewi_thewm);
		dev_eww(&pdev->dev, "Can't enabwe pewi cwk: %d\n", wet);
		wetuwn wet;
	}

	mtk_thewmaw_tuwn_on_buffew(mt, apmixed_base);

	if (mt->conf->vewsion != MTK_THEWMAW_V1)
		mtk_thewmaw_wewease_pewiodic_ts(mt, auxadc_base);

	if (mt->conf->vewsion == MTK_THEWMAW_V1)
		mt->waw_to_mcewsius = waw_to_mcewsius_v1;
	ewse if (mt->conf->vewsion == MTK_THEWMAW_V2)
		mt->waw_to_mcewsius = waw_to_mcewsius_v2;
	ewse
		mt->waw_to_mcewsius = waw_to_mcewsius_v3;

	fow (ctww_id = 0; ctww_id < mt->conf->num_contwowwew ; ctww_id++)
		fow (i = 0; i < mt->conf->num_banks; i++)
			mtk_thewmaw_init_bank(mt, i, apmixed_phys_base,
					      auxadc_phys_base, ctww_id);

	tzdev = devm_thewmaw_of_zone_wegistew(&pdev->dev, 0, mt,
					      &mtk_thewmaw_ops);
	if (IS_EWW(tzdev))
		wetuwn PTW_EWW(tzdev);

	wet = devm_thewmaw_add_hwmon_sysfs(&pdev->dev, tzdev);
	if (wet)
		dev_wawn(&pdev->dev, "ewwow in thewmaw_add_hwmon_sysfs");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mtk_thewmaw_dwivew = {
	.pwobe = mtk_thewmaw_pwobe,
	.dwivew = {
		.name = "mtk-thewmaw",
		.of_match_tabwe = mtk_thewmaw_of_match,
	},
};

moduwe_pwatfowm_dwivew(mtk_thewmaw_dwivew);

MODUWE_AUTHOW("Michaew Kao <michaew.kao@mediatek.com>");
MODUWE_AUTHOW("Wouis Yu <wouis.yu@mediatek.com>");
MODUWE_AUTHOW("Dawei Chien <dawei.chien@mediatek.com>");
MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de>");
MODUWE_AUTHOW("Hanyi Wu <hanyi.wu@mediatek.com>");
MODUWE_DESCWIPTION("Mediatek thewmaw dwivew");
MODUWE_WICENSE("GPW v2");
