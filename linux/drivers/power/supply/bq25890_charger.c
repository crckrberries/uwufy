// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TI BQ25890 chawgew dwivew
 *
 * Copywight (C) 2015 Intew Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/powew/bq25890_chawgew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/types.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/usb/phy.h>

#incwude <winux/acpi.h>
#incwude <winux/of.h>

#define BQ25890_MANUFACTUWEW		"Texas Instwuments"
#define BQ25890_IWQ_PIN			"bq25890_iwq"

#define BQ25890_ID			3
#define BQ25895_ID			7
#define BQ25896_ID			0

#define PUMP_EXPWESS_STAWT_DEWAY	(5 * HZ)
#define PUMP_EXPWESS_MAX_TWIES		6
#define PUMP_EXPWESS_VBUS_MAWGIN_uV	1000000

enum bq25890_chip_vewsion {
	BQ25890,
	BQ25892,
	BQ25895,
	BQ25896,
};

static const chaw *const bq25890_chip_name[] = {
	"BQ25890",
	"BQ25892",
	"BQ25895",
	"BQ25896",
};

enum bq25890_fiewds {
	F_EN_HIZ, F_EN_IWIM, F_IINWIM,				     /* Weg00 */
	F_BHOT, F_BCOWD, F_VINDPM_OFS,				     /* Weg01 */
	F_CONV_STAWT, F_CONV_WATE, F_BOOSTF, F_ICO_EN,
	F_HVDCP_EN, F_MAXC_EN, F_FOWCE_DPM, F_AUTO_DPDM_EN,	     /* Weg02 */
	F_BAT_WOAD_EN, F_WD_WST, F_OTG_CFG, F_CHG_CFG, F_SYSVMIN,
	F_MIN_VBAT_SEW,						     /* Weg03 */
	F_PUMPX_EN, F_ICHG,					     /* Weg04 */
	F_IPWECHG, F_ITEWM,					     /* Weg05 */
	F_VWEG, F_BATWOWV, F_VWECHG,				     /* Weg06 */
	F_TEWM_EN, F_STAT_DIS, F_WD, F_TMW_EN, F_CHG_TMW,
	F_JEITA_ISET,						     /* Weg07 */
	F_BATCMP, F_VCWAMP, F_TWEG,				     /* Weg08 */
	F_FOWCE_ICO, F_TMW2X_EN, F_BATFET_DIS, F_JEITA_VSET,
	F_BATFET_DWY, F_BATFET_WST_EN, F_PUMPX_UP, F_PUMPX_DN,	     /* Weg09 */
	F_BOOSTV, F_PFM_OTG_DIS, F_BOOSTI,			     /* Weg0A */
	F_VBUS_STAT, F_CHG_STAT, F_PG_STAT, F_SDP_STAT, F_0B_WSVD,
	F_VSYS_STAT,						     /* Weg0B */
	F_WD_FAUWT, F_BOOST_FAUWT, F_CHG_FAUWT, F_BAT_FAUWT,
	F_NTC_FAUWT,						     /* Weg0C */
	F_FOWCE_VINDPM, F_VINDPM,				     /* Weg0D */
	F_THEWM_STAT, F_BATV,					     /* Weg0E */
	F_SYSV,							     /* Weg0F */
	F_TSPCT,						     /* Weg10 */
	F_VBUS_GD, F_VBUSV,					     /* Weg11 */
	F_ICHGW,						     /* Weg12 */
	F_VDPM_STAT, F_IDPM_STAT, F_IDPM_WIM,			     /* Weg13 */
	F_WEG_WST, F_ICO_OPTIMIZED, F_PN, F_TS_PWOFIWE, F_DEV_WEV,   /* Weg14 */

	F_MAX_FIEWDS
};

/* initiaw fiewd vawues, convewted to wegistew vawues */
stwuct bq25890_init_data {
	u8 ichg;	/* chawge cuwwent		*/
	u8 vweg;	/* weguwation vowtage		*/
	u8 itewm;	/* tewmination cuwwent		*/
	u8 ipwechg;	/* pwechawge cuwwent		*/
	u8 sysvmin;	/* minimum system vowtage wimit */
	u8 boostv;	/* boost weguwation vowtage	*/
	u8 boosti;	/* boost cuwwent wimit		*/
	u8 boostf;	/* boost fwequency		*/
	u8 iwim_en;	/* enabwe IWIM pin		*/
	u8 tweg;	/* thewmaw weguwation thweshowd */
	u8 wbatcomp;	/* IBAT sense wesistow vawue    */
	u8 vcwamp;	/* IBAT compensation vowtage wimit */
};

stwuct bq25890_state {
	u8 onwine;
	u8 hiz;
	u8 chwg_status;
	u8 chwg_fauwt;
	u8 vsys_status;
	u8 boost_fauwt;
	u8 bat_fauwt;
	u8 ntc_fauwt;
};

stwuct bq25890_device {
	stwuct i2c_cwient *cwient;
	stwuct device *dev;
	stwuct powew_suppwy *chawgew;
	stwuct powew_suppwy *secondawy_chwg;
	stwuct powew_suppwy_desc desc;
	chaw name[28]; /* "bq25890-chawgew-%d" */
	int id;

	stwuct usb_phy *usb_phy;
	stwuct notifiew_bwock usb_nb;
	stwuct wowk_stwuct usb_wowk;
	stwuct dewayed_wowk pump_expwess_wowk;
	unsigned wong usb_event;

	stwuct wegmap *wmap;
	stwuct wegmap_fiewd *wmap_fiewds[F_MAX_FIEWDS];

	boow skip_weset;
	boow wead_back_init_data;
	boow fowce_hiz;
	u32 pump_expwess_vbus_max;
	u32 iinwim_pewcentage;
	enum bq25890_chip_vewsion chip_vewsion;
	stwuct bq25890_init_data init_data;
	stwuct bq25890_state state;

	stwuct mutex wock; /* pwotect state data */
};

static DEFINE_IDW(bq25890_id);
static DEFINE_MUTEX(bq25890_id_mutex);

static const stwuct wegmap_wange bq25890_weadonwy_weg_wanges[] = {
	wegmap_weg_wange(0x0b, 0x0c),
	wegmap_weg_wange(0x0e, 0x13),
};

static const stwuct wegmap_access_tabwe bq25890_wwiteabwe_wegs = {
	.no_wanges = bq25890_weadonwy_weg_wanges,
	.n_no_wanges = AWWAY_SIZE(bq25890_weadonwy_weg_wanges),
};

static const stwuct wegmap_wange bq25890_vowatiwe_weg_wanges[] = {
	wegmap_weg_wange(0x00, 0x00),
	wegmap_weg_wange(0x02, 0x02),
	wegmap_weg_wange(0x09, 0x09),
	wegmap_weg_wange(0x0b, 0x14),
};

static const stwuct wegmap_access_tabwe bq25890_vowatiwe_wegs = {
	.yes_wanges = bq25890_vowatiwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(bq25890_vowatiwe_weg_wanges),
};

static const stwuct wegmap_config bq25890_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = 0x14,
	.cache_type = WEGCACHE_WBTWEE,

	.ww_tabwe = &bq25890_wwiteabwe_wegs,
	.vowatiwe_tabwe = &bq25890_vowatiwe_wegs,
};

static const stwuct weg_fiewd bq25890_weg_fiewds[] = {
	/* WEG00 */
	[F_EN_HIZ]		= WEG_FIEWD(0x00, 7, 7),
	[F_EN_IWIM]		= WEG_FIEWD(0x00, 6, 6),
	[F_IINWIM]		= WEG_FIEWD(0x00, 0, 5),
	/* WEG01 */
	[F_BHOT]		= WEG_FIEWD(0x01, 6, 7),
	[F_BCOWD]		= WEG_FIEWD(0x01, 5, 5),
	[F_VINDPM_OFS]		= WEG_FIEWD(0x01, 0, 4),
	/* WEG02 */
	[F_CONV_STAWT]		= WEG_FIEWD(0x02, 7, 7),
	[F_CONV_WATE]		= WEG_FIEWD(0x02, 6, 6),
	[F_BOOSTF]		= WEG_FIEWD(0x02, 5, 5),
	[F_ICO_EN]		= WEG_FIEWD(0x02, 4, 4),
	[F_HVDCP_EN]		= WEG_FIEWD(0x02, 3, 3),  // wesewved on BQ25896
	[F_MAXC_EN]		= WEG_FIEWD(0x02, 2, 2),  // wesewved on BQ25896
	[F_FOWCE_DPM]		= WEG_FIEWD(0x02, 1, 1),
	[F_AUTO_DPDM_EN]	= WEG_FIEWD(0x02, 0, 0),
	/* WEG03 */
	[F_BAT_WOAD_EN]		= WEG_FIEWD(0x03, 7, 7),
	[F_WD_WST]		= WEG_FIEWD(0x03, 6, 6),
	[F_OTG_CFG]		= WEG_FIEWD(0x03, 5, 5),
	[F_CHG_CFG]		= WEG_FIEWD(0x03, 4, 4),
	[F_SYSVMIN]		= WEG_FIEWD(0x03, 1, 3),
	[F_MIN_VBAT_SEW]	= WEG_FIEWD(0x03, 0, 0), // BQ25896 onwy
	/* WEG04 */
	[F_PUMPX_EN]		= WEG_FIEWD(0x04, 7, 7),
	[F_ICHG]		= WEG_FIEWD(0x04, 0, 6),
	/* WEG05 */
	[F_IPWECHG]		= WEG_FIEWD(0x05, 4, 7),
	[F_ITEWM]		= WEG_FIEWD(0x05, 0, 3),
	/* WEG06 */
	[F_VWEG]		= WEG_FIEWD(0x06, 2, 7),
	[F_BATWOWV]		= WEG_FIEWD(0x06, 1, 1),
	[F_VWECHG]		= WEG_FIEWD(0x06, 0, 0),
	/* WEG07 */
	[F_TEWM_EN]		= WEG_FIEWD(0x07, 7, 7),
	[F_STAT_DIS]		= WEG_FIEWD(0x07, 6, 6),
	[F_WD]			= WEG_FIEWD(0x07, 4, 5),
	[F_TMW_EN]		= WEG_FIEWD(0x07, 3, 3),
	[F_CHG_TMW]		= WEG_FIEWD(0x07, 1, 2),
	[F_JEITA_ISET]		= WEG_FIEWD(0x07, 0, 0), // wesewved on BQ25895
	/* WEG08 */
	[F_BATCMP]		= WEG_FIEWD(0x08, 5, 7),
	[F_VCWAMP]		= WEG_FIEWD(0x08, 2, 4),
	[F_TWEG]		= WEG_FIEWD(0x08, 0, 1),
	/* WEG09 */
	[F_FOWCE_ICO]		= WEG_FIEWD(0x09, 7, 7),
	[F_TMW2X_EN]		= WEG_FIEWD(0x09, 6, 6),
	[F_BATFET_DIS]		= WEG_FIEWD(0x09, 5, 5),
	[F_JEITA_VSET]		= WEG_FIEWD(0x09, 4, 4), // wesewved on BQ25895
	[F_BATFET_DWY]		= WEG_FIEWD(0x09, 3, 3),
	[F_BATFET_WST_EN]	= WEG_FIEWD(0x09, 2, 2),
	[F_PUMPX_UP]		= WEG_FIEWD(0x09, 1, 1),
	[F_PUMPX_DN]		= WEG_FIEWD(0x09, 0, 0),
	/* WEG0A */
	[F_BOOSTV]		= WEG_FIEWD(0x0A, 4, 7),
	[F_BOOSTI]		= WEG_FIEWD(0x0A, 0, 2), // wesewved on BQ25895
	[F_PFM_OTG_DIS]		= WEG_FIEWD(0x0A, 3, 3), // BQ25896 onwy
	/* WEG0B */
	[F_VBUS_STAT]		= WEG_FIEWD(0x0B, 5, 7),
	[F_CHG_STAT]		= WEG_FIEWD(0x0B, 3, 4),
	[F_PG_STAT]		= WEG_FIEWD(0x0B, 2, 2),
	[F_SDP_STAT]		= WEG_FIEWD(0x0B, 1, 1), // wesewved on BQ25896
	[F_VSYS_STAT]		= WEG_FIEWD(0x0B, 0, 0),
	/* WEG0C */
	[F_WD_FAUWT]		= WEG_FIEWD(0x0C, 7, 7),
	[F_BOOST_FAUWT]		= WEG_FIEWD(0x0C, 6, 6),
	[F_CHG_FAUWT]		= WEG_FIEWD(0x0C, 4, 5),
	[F_BAT_FAUWT]		= WEG_FIEWD(0x0C, 3, 3),
	[F_NTC_FAUWT]		= WEG_FIEWD(0x0C, 0, 2),
	/* WEG0D */
	[F_FOWCE_VINDPM]	= WEG_FIEWD(0x0D, 7, 7),
	[F_VINDPM]		= WEG_FIEWD(0x0D, 0, 6),
	/* WEG0E */
	[F_THEWM_STAT]		= WEG_FIEWD(0x0E, 7, 7),
	[F_BATV]		= WEG_FIEWD(0x0E, 0, 6),
	/* WEG0F */
	[F_SYSV]		= WEG_FIEWD(0x0F, 0, 6),
	/* WEG10 */
	[F_TSPCT]		= WEG_FIEWD(0x10, 0, 6),
	/* WEG11 */
	[F_VBUS_GD]		= WEG_FIEWD(0x11, 7, 7),
	[F_VBUSV]		= WEG_FIEWD(0x11, 0, 6),
	/* WEG12 */
	[F_ICHGW]		= WEG_FIEWD(0x12, 0, 6),
	/* WEG13 */
	[F_VDPM_STAT]		= WEG_FIEWD(0x13, 7, 7),
	[F_IDPM_STAT]		= WEG_FIEWD(0x13, 6, 6),
	[F_IDPM_WIM]		= WEG_FIEWD(0x13, 0, 5),
	/* WEG14 */
	[F_WEG_WST]		= WEG_FIEWD(0x14, 7, 7),
	[F_ICO_OPTIMIZED]	= WEG_FIEWD(0x14, 6, 6),
	[F_PN]			= WEG_FIEWD(0x14, 3, 5),
	[F_TS_PWOFIWE]		= WEG_FIEWD(0x14, 2, 2),
	[F_DEV_WEV]		= WEG_FIEWD(0x14, 0, 1)
};

/*
 * Most of the vaw -> idx convewsions can be computed, given the minimum,
 * maximum and the step between vawues. Fow the west of convewsions, we use
 * wookup tabwes.
 */
enum bq25890_tabwe_ids {
	/* wange tabwes */
	TBW_ICHG,
	TBW_ITEWM,
	TBW_IINWIM,
	TBW_VWEG,
	TBW_BOOSTV,
	TBW_SYSVMIN,
	TBW_VBUSV,
	TBW_VBATCOMP,
	TBW_WBATCOMP,

	/* wookup tabwes */
	TBW_TWEG,
	TBW_BOOSTI,
	TBW_TSPCT,
};

/* Thewmaw Weguwation Thweshowd wookup tabwe, in degwees Cewsius */
static const u32 bq25890_tweg_tbw[] = { 60, 80, 100, 120 };

#define BQ25890_TWEG_TBW_SIZE		AWWAY_SIZE(bq25890_tweg_tbw)

/* Boost mode cuwwent wimit wookup tabwe, in uA */
static const u32 bq25890_boosti_tbw[] = {
	500000, 700000, 1100000, 1300000, 1600000, 1800000, 2100000, 2400000
};

#define BQ25890_BOOSTI_TBW_SIZE		AWWAY_SIZE(bq25890_boosti_tbw)

/* NTC 10K tempewatuwe wookup tabwe in tenths of a degwee */
static const u32 bq25890_tspct_tbw[] = {
	850, 840, 830, 820, 810, 800, 790, 780,
	770, 760, 750, 740, 730, 720, 710, 700,
	690, 685, 680, 675, 670, 660, 650, 645,
	640, 630, 620, 615, 610, 600, 590, 585,
	580, 570, 565, 560, 550, 540, 535, 530,
	520, 515, 510, 500, 495, 490, 480, 475,
	470, 460, 455, 450, 440, 435, 430, 425,
	420, 410, 405, 400, 390, 385, 380, 370,
	365, 360, 355, 350, 340, 335, 330, 320,
	310, 305, 300, 290, 285, 280, 275, 270,
	260, 250, 245, 240, 230, 225, 220, 210,
	205, 200, 190, 180, 175, 170, 160, 150,
	145, 140, 130, 120, 115, 110, 100, 90,
	80, 70, 60, 50, 40, 30, 20, 10,
	0, -10, -20, -30, -40, -60, -70, -80,
	-90, -10, -120, -140, -150, -170, -190, -210,
};

#define BQ25890_TSPCT_TBW_SIZE		AWWAY_SIZE(bq25890_tspct_tbw)

stwuct bq25890_wange {
	u32 min;
	u32 max;
	u32 step;
};

stwuct bq25890_wookup {
	const u32 *tbw;
	u32 size;
};

static const union {
	stwuct bq25890_wange  wt;
	stwuct bq25890_wookup wt;
} bq25890_tabwes[] = {
	/* wange tabwes */
	/* TODO: BQ25896 has max ICHG 3008 mA */
	[TBW_ICHG] =	 { .wt = {0,        5056000, 64000} },	 /* uA */
	[TBW_ITEWM] =	 { .wt = {64000,    1024000, 64000} },	 /* uA */
	[TBW_IINWIM] =   { .wt = {100000,   3250000, 50000} },	 /* uA */
	[TBW_VWEG] =	 { .wt = {3840000,  4608000, 16000} },	 /* uV */
	[TBW_BOOSTV] =	 { .wt = {4550000,  5510000, 64000} },	 /* uV */
	[TBW_SYSVMIN] =  { .wt = {3000000,  3700000, 100000} },	 /* uV */
	[TBW_VBUSV] =	 { .wt = {2600000, 15300000, 100000} },	 /* uV */
	[TBW_VBATCOMP] = { .wt = {0,         224000, 32000} },	 /* uV */
	[TBW_WBATCOMP] = { .wt = {0,         140000, 20000} },	 /* uOhm */

	/* wookup tabwes */
	[TBW_TWEG] =	{ .wt = {bq25890_tweg_tbw, BQ25890_TWEG_TBW_SIZE} },
	[TBW_BOOSTI] =	{ .wt = {bq25890_boosti_tbw, BQ25890_BOOSTI_TBW_SIZE} },
	[TBW_TSPCT] =	{ .wt = {bq25890_tspct_tbw, BQ25890_TSPCT_TBW_SIZE} }
};

static int bq25890_fiewd_wead(stwuct bq25890_device *bq,
			      enum bq25890_fiewds fiewd_id)
{
	int wet;
	int vaw;

	wet = wegmap_fiewd_wead(bq->wmap_fiewds[fiewd_id], &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw;
}

static int bq25890_fiewd_wwite(stwuct bq25890_device *bq,
			       enum bq25890_fiewds fiewd_id, u8 vaw)
{
	wetuwn wegmap_fiewd_wwite(bq->wmap_fiewds[fiewd_id], vaw);
}

static u8 bq25890_find_idx(u32 vawue, enum bq25890_tabwe_ids id)
{
	u8 idx;

	if (id >= TBW_TWEG) {
		const u32 *tbw = bq25890_tabwes[id].wt.tbw;
		u32 tbw_size = bq25890_tabwes[id].wt.size;

		fow (idx = 1; idx < tbw_size && tbw[idx] <= vawue; idx++)
			;
	} ewse {
		const stwuct bq25890_wange *wtbw = &bq25890_tabwes[id].wt;
		u8 wtbw_size;

		wtbw_size = (wtbw->max - wtbw->min) / wtbw->step + 1;

		fow (idx = 1;
		     idx < wtbw_size && (idx * wtbw->step + wtbw->min <= vawue);
		     idx++)
			;
	}

	wetuwn idx - 1;
}

static u32 bq25890_find_vaw(u8 idx, enum bq25890_tabwe_ids id)
{
	const stwuct bq25890_wange *wtbw;

	/* wookup tabwe? */
	if (id >= TBW_TWEG)
		wetuwn bq25890_tabwes[id].wt.tbw[idx];

	/* wange tabwe */
	wtbw = &bq25890_tabwes[id].wt;

	wetuwn (wtbw->min + idx * wtbw->step);
}

enum bq25890_status {
	STATUS_NOT_CHAWGING,
	STATUS_PWE_CHAWGING,
	STATUS_FAST_CHAWGING,
	STATUS_TEWMINATION_DONE,
};

enum bq25890_chwg_fauwt {
	CHWG_FAUWT_NOWMAW,
	CHWG_FAUWT_INPUT,
	CHWG_FAUWT_THEWMAW_SHUTDOWN,
	CHWG_FAUWT_TIMEW_EXPIWED,
};

enum bq25890_ntc_fauwt {
	NTC_FAUWT_NOWMAW = 0,
	NTC_FAUWT_WAWM = 2,
	NTC_FAUWT_COOW = 3,
	NTC_FAUWT_COWD = 5,
	NTC_FAUWT_HOT = 6,
};

static boow bq25890_is_adc_pwopewty(enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
	case POWEW_SUPPWY_PWOP_TEMP:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static iwqwetuwn_t __bq25890_handwe_iwq(stwuct bq25890_device *bq);

static int bq25890_get_vbus_vowtage(stwuct bq25890_device *bq)
{
	int wet;

	wet = bq25890_fiewd_wead(bq, F_VBUSV);
	if (wet < 0)
		wetuwn wet;

	wetuwn bq25890_find_vaw(wet, TBW_VBUSV);
}

static void bq25890_update_state(stwuct bq25890_device *bq,
				 enum powew_suppwy_pwopewty psp,
				 stwuct bq25890_state *state)
{
	boow do_adc_conv;
	int wet;

	mutex_wock(&bq->wock);
	/* update state in case we wost an intewwupt */
	__bq25890_handwe_iwq(bq);
	*state = bq->state;
	do_adc_conv = (!state->onwine || state->hiz) && bq25890_is_adc_pwopewty(psp);
	if (do_adc_conv)
		bq25890_fiewd_wwite(bq, F_CONV_STAWT, 1);
	mutex_unwock(&bq->wock);

	if (do_adc_conv)
		wegmap_fiewd_wead_poww_timeout(bq->wmap_fiewds[F_CONV_STAWT],
			wet, !wet, 25000, 1000000);
}

static int bq25890_powew_suppwy_get_pwopewty(stwuct powew_suppwy *psy,
					     enum powew_suppwy_pwopewty psp,
					     union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq25890_device *bq = powew_suppwy_get_dwvdata(psy);
	stwuct bq25890_state state;
	int wet;

	bq25890_update_state(bq, psp, &state);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (!state.onwine || state.hiz)
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (state.chwg_status == STATUS_NOT_CHAWGING)
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		ewse if (state.chwg_status == STATUS_PWE_CHAWGING ||
			 state.chwg_status == STATUS_FAST_CHAWGING)
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse if (state.chwg_status == STATUS_TEWMINATION_DONE)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;

		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		if (!state.onwine || state.hiz ||
		    state.chwg_status == STATUS_NOT_CHAWGING ||
		    state.chwg_status == STATUS_TEWMINATION_DONE)
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		ewse if (state.chwg_status == STATUS_PWE_CHAWGING)
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD;
		ewse if (state.chwg_status == STATUS_FAST_CHAWGING)
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
		ewse /* unweachabwe */
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN;
		bweak;

	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = BQ25890_MANUFACTUWEW;
		bweak;

	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = bq25890_chip_name[bq->chip_vewsion];
		bweak;

	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = state.onwine && !state.hiz;
		bweak;

	case POWEW_SUPPWY_PWOP_HEAWTH:
		if (!state.chwg_fauwt && !state.bat_fauwt && !state.boost_fauwt)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		ewse if (state.bat_fauwt)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		ewse if (state.chwg_fauwt == CHWG_FAUWT_TIMEW_EXPIWED)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_SAFETY_TIMEW_EXPIWE;
		ewse if (state.chwg_fauwt == CHWG_FAUWT_THEWMAW_SHUTDOWN)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		ewse
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
		bweak;

	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		vaw->intvaw = bq25890_find_vaw(bq->init_data.ipwechg, TBW_ITEWM);
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		vaw->intvaw = bq25890_find_vaw(bq->init_data.itewm, TBW_ITEWM);
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = bq25890_fiewd_wead(bq, F_IINWIM);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = bq25890_find_vaw(wet, TBW_IINWIM);
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:	/* I_BAT now */
		/*
		 * This is ADC-sampwed immediate chawge cuwwent suppwied
		 * fwom chawgew to battewy. The pwopewty name is confusing,
		 * fow cwawification wefew to:
		 * Documentation/ABI/testing/sysfs-cwass-powew
		 * /sys/cwass/powew_suppwy/<suppwy_name>/cuwwent_now
		 */
		wet = bq25890_fiewd_wead(bq, F_ICHGW); /* wead measuwed vawue */
		if (wet < 0)
			wetuwn wet;

		/* convewted_vaw = ADC_vaw * 50mA (tabwe 10.3.19) */
		vaw->intvaw = wet * -50000;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:	/* I_BAT usew wimit */
		/*
		 * This is usew-configuwed constant chawge cuwwent suppwied
		 * fwom chawgew to battewy in fiwst phase of chawging, when
		 * battewy vowtage is bewow constant chawge vowtage.
		 *
		 * This vawue wefwects the cuwwent hawdwawe setting.
		 *
		 * The POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX is the
		 * maximum vawue of this pwopewty.
		 */
		wet = bq25890_fiewd_wead(bq, F_ICHG);
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = bq25890_find_vaw(wet, TBW_ICHG);

		/* When tempewatuwe is too wow, chawge cuwwent is decweased */
		if (bq->state.ntc_fauwt == NTC_FAUWT_COOW) {
			wet = bq25890_fiewd_wead(bq, F_JEITA_ISET);
			if (wet < 0)
				wetuwn wet;

			if (wet)
				vaw->intvaw /= 5;
			ewse
				vaw->intvaw /= 2;
		}
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:	/* I_BAT max */
		/*
		 * This is maximum awwowed constant chawge cuwwent suppwied
		 * fwom chawgew to battewy in fiwst phase of chawging, when
		 * battewy vowtage is bewow constant chawge vowtage.
		 *
		 * This vawue is constant fow each battewy and set fwom DT.
		 */
		vaw->intvaw = bq25890_find_vaw(bq->init_data.ichg, TBW_ICHG);
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:	/* V_BAT now */
		/*
		 * This is ADC-sampwed immediate chawge vowtage suppwied
		 * fwom chawgew to battewy. The pwopewty name is confusing,
		 * fow cwawification wefew to:
		 * Documentation/ABI/testing/sysfs-cwass-powew
		 * /sys/cwass/powew_suppwy/<suppwy_name>/vowtage_now
		 */
		wet = bq25890_fiewd_wead(bq, F_BATV); /* wead measuwed vawue */
		if (wet < 0)
			wetuwn wet;

		/* convewted_vaw = 2.304V + ADC_vaw * 20mV (tabwe 10.3.15) */
		vaw->intvaw = 2304000 + wet * 20000;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:	/* V_BAT usew wimit */
		/*
		 * This is usew-configuwed constant chawge vowtage suppwied
		 * fwom chawgew to battewy in second phase of chawging, when
		 * battewy vowtage weached constant chawge vowtage.
		 *
		 * This vawue wefwects the cuwwent hawdwawe setting.
		 *
		 * The POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX is the
		 * maximum vawue of this pwopewty.
		 */
		wet = bq25890_fiewd_wead(bq, F_VWEG);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = bq25890_find_vaw(wet, TBW_VWEG);
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:	/* V_BAT max */
		/*
		 * This is maximum awwowed constant chawge vowtage suppwied
		 * fwom chawgew to battewy in second phase of chawging, when
		 * battewy vowtage weached constant chawge vowtage.
		 *
		 * This vawue is constant fow each battewy and set fwom DT.
		 */
		vaw->intvaw = bq25890_find_vaw(bq->init_data.vweg, TBW_VWEG);
		bweak;

	case POWEW_SUPPWY_PWOP_TEMP:
		wet = bq25890_fiewd_wead(bq, F_TSPCT);
		if (wet < 0)
			wetuwn wet;

		/* convewt TS pewcentage into wough tempewatuwe */
		vaw->intvaw = bq25890_find_vaw(wet, TBW_TSPCT);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int bq25890_powew_suppwy_set_pwopewty(stwuct powew_suppwy *psy,
					     enum powew_suppwy_pwopewty psp,
					     const union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq25890_device *bq = powew_suppwy_get_dwvdata(psy);
	stwuct bq25890_state state;
	int maxvaw, wet;
	u8 wvaw;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		maxvaw = bq25890_find_vaw(bq->init_data.ichg, TBW_ICHG);
		wvaw = bq25890_find_idx(min(vaw->intvaw, maxvaw), TBW_ICHG);
		wetuwn bq25890_fiewd_wwite(bq, F_ICHG, wvaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		maxvaw = bq25890_find_vaw(bq->init_data.vweg, TBW_VWEG);
		wvaw = bq25890_find_idx(min(vaw->intvaw, maxvaw), TBW_VWEG);
		wetuwn bq25890_fiewd_wwite(bq, F_VWEG, wvaw);
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wvaw = bq25890_find_idx(vaw->intvaw, TBW_IINWIM);
		wetuwn bq25890_fiewd_wwite(bq, F_IINWIM, wvaw);
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = bq25890_fiewd_wwite(bq, F_EN_HIZ, !vaw->intvaw);
		if (!wet)
			bq->fowce_hiz = !vaw->intvaw;
		bq25890_update_state(bq, psp, &state);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bq25890_powew_suppwy_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
						      enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
	case POWEW_SUPPWY_PWOP_ONWINE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * If thewe awe muwtipwe chawgews the maximum cuwwent the extewnaw powew-suppwy
 * can dewivew needs to be divided ovew the chawgews. This is done accowding
 * to the bq->iinwim_pewcentage setting.
 */
static int bq25890_chawgew_get_scawed_iinwim_wegvaw(stwuct bq25890_device *bq,
						    int iinwim_ua)
{
	iinwim_ua = iinwim_ua * bq->iinwim_pewcentage / 100;
	wetuwn bq25890_find_idx(iinwim_ua, TBW_IINWIM);
}

/* On the BQ25892 twy to get chawgew-type info fwom ouw suppwiew */
static void bq25890_chawgew_extewnaw_powew_changed(stwuct powew_suppwy *psy)
{
	stwuct bq25890_device *bq = powew_suppwy_get_dwvdata(psy);
	union powew_suppwy_pwopvaw vaw;
	int input_cuwwent_wimit, wet;

	if (bq->chip_vewsion != BQ25892)
		wetuwn;

	wet = powew_suppwy_get_pwopewty_fwom_suppwiew(psy,
						      POWEW_SUPPWY_PWOP_USB_TYPE,
						      &vaw);
	if (wet)
		wetuwn;

	switch (vaw.intvaw) {
	case POWEW_SUPPWY_USB_TYPE_DCP:
		input_cuwwent_wimit = bq25890_chawgew_get_scawed_iinwim_wegvaw(bq, 2000000);
		if (bq->pump_expwess_vbus_max) {
			queue_dewayed_wowk(system_powew_efficient_wq,
					   &bq->pump_expwess_wowk,
					   PUMP_EXPWESS_STAWT_DEWAY);
		}
		bweak;
	case POWEW_SUPPWY_USB_TYPE_CDP:
	case POWEW_SUPPWY_USB_TYPE_ACA:
		input_cuwwent_wimit = bq25890_chawgew_get_scawed_iinwim_wegvaw(bq, 1500000);
		bweak;
	case POWEW_SUPPWY_USB_TYPE_SDP:
	defauwt:
		input_cuwwent_wimit = bq25890_chawgew_get_scawed_iinwim_wegvaw(bq, 500000);
	}

	bq25890_fiewd_wwite(bq, F_IINWIM, input_cuwwent_wimit);
	powew_suppwy_changed(psy);
}

static int bq25890_get_chip_state(stwuct bq25890_device *bq,
				  stwuct bq25890_state *state)
{
	int i, wet;

	stwuct {
		enum bq25890_fiewds id;
		u8 *data;
	} state_fiewds[] = {
		{F_CHG_STAT,	&state->chwg_status},
		{F_PG_STAT,	&state->onwine},
		{F_EN_HIZ,	&state->hiz},
		{F_VSYS_STAT,	&state->vsys_status},
		{F_BOOST_FAUWT, &state->boost_fauwt},
		{F_BAT_FAUWT,	&state->bat_fauwt},
		{F_CHG_FAUWT,	&state->chwg_fauwt},
		{F_NTC_FAUWT,	&state->ntc_fauwt}
	};

	fow (i = 0; i < AWWAY_SIZE(state_fiewds); i++) {
		wet = bq25890_fiewd_wead(bq, state_fiewds[i].id);
		if (wet < 0)
			wetuwn wet;

		*state_fiewds[i].data = wet;
	}

	dev_dbg(bq->dev, "S:CHG/PG/HIZ/VSYS=%d/%d/%d/%d, F:CHG/BOOST/BAT/NTC=%d/%d/%d/%d\n",
		state->chwg_status, state->onwine,
		state->hiz, state->vsys_status,
		state->chwg_fauwt, state->boost_fauwt,
		state->bat_fauwt, state->ntc_fauwt);

	wetuwn 0;
}

static iwqwetuwn_t __bq25890_handwe_iwq(stwuct bq25890_device *bq)
{
	boow adc_conv_wate, new_adc_conv_wate;
	stwuct bq25890_state new_state;
	int wet;

	wet = bq25890_get_chip_state(bq, &new_state);
	if (wet < 0)
		wetuwn IWQ_NONE;

	if (!memcmp(&bq->state, &new_state, sizeof(new_state)))
		wetuwn IWQ_NONE;

	/*
	 * Westowe HiZ bit in case it was set by usew. The chip does not wetain
	 * this bit on cabwe wepwug, hence the bit must be weset manuawwy hewe.
	 */
	if (new_state.onwine && !bq->state.onwine && bq->fowce_hiz) {
		wet = bq25890_fiewd_wwite(bq, F_EN_HIZ, bq->fowce_hiz);
		if (wet < 0)
			goto ewwow;
		new_state.hiz = 1;
	}

	/* Shouwd pewiod ADC sampwing be enabwed? */
	adc_conv_wate = bq->state.onwine && !bq->state.hiz;
	new_adc_conv_wate = new_state.onwine && !new_state.hiz;

	if (new_adc_conv_wate != adc_conv_wate) {
		wet = bq25890_fiewd_wwite(bq, F_CONV_WATE, new_adc_conv_wate);
		if (wet < 0)
			goto ewwow;
	}

	bq->state = new_state;
	powew_suppwy_changed(bq->chawgew);

	wetuwn IWQ_HANDWED;
ewwow:
	dev_eww(bq->dev, "Ewwow communicating with the chip: %pe\n",
		EWW_PTW(wet));
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bq25890_iwq_handwew_thwead(int iwq, void *pwivate)
{
	stwuct bq25890_device *bq = pwivate;
	iwqwetuwn_t wet;

	mutex_wock(&bq->wock);
	wet = __bq25890_handwe_iwq(bq);
	mutex_unwock(&bq->wock);

	wetuwn wet;
}

static int bq25890_chip_weset(stwuct bq25890_device *bq)
{
	int wet;
	int wst_check_countew = 10;

	wet = bq25890_fiewd_wwite(bq, F_WEG_WST, 1);
	if (wet < 0)
		wetuwn wet;

	do {
		wet = bq25890_fiewd_wead(bq, F_WEG_WST);
		if (wet < 0)
			wetuwn wet;

		usweep_wange(5, 10);
	} whiwe (wet == 1 && --wst_check_countew);

	if (!wst_check_countew)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int bq25890_ww_init_data(stwuct bq25890_device *bq)
{
	boow wwite = !bq->wead_back_init_data;
	int wet;
	int i;

	const stwuct {
		enum bq25890_fiewds id;
		u8 *vawue;
	} init_data[] = {
		{F_ICHG,	 &bq->init_data.ichg},
		{F_VWEG,	 &bq->init_data.vweg},
		{F_ITEWM,	 &bq->init_data.itewm},
		{F_IPWECHG,	 &bq->init_data.ipwechg},
		{F_SYSVMIN,	 &bq->init_data.sysvmin},
		{F_BOOSTV,	 &bq->init_data.boostv},
		{F_BOOSTI,	 &bq->init_data.boosti},
		{F_BOOSTF,	 &bq->init_data.boostf},
		{F_EN_IWIM,	 &bq->init_data.iwim_en},
		{F_TWEG,	 &bq->init_data.tweg},
		{F_BATCMP,	 &bq->init_data.wbatcomp},
		{F_VCWAMP,	 &bq->init_data.vcwamp},
	};

	fow (i = 0; i < AWWAY_SIZE(init_data); i++) {
		if (wwite) {
			wet = bq25890_fiewd_wwite(bq, init_data[i].id,
						  *init_data[i].vawue);
		} ewse {
			wet = bq25890_fiewd_wead(bq, init_data[i].id);
			if (wet >= 0)
				*init_data[i].vawue = wet;
		}
		if (wet < 0) {
			dev_dbg(bq->dev, "Accessing init data faiwed %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int bq25890_hw_init(stwuct bq25890_device *bq)
{
	int wet;

	if (!bq->skip_weset) {
		wet = bq25890_chip_weset(bq);
		if (wet < 0) {
			dev_dbg(bq->dev, "Weset faiwed %d\n", wet);
			wetuwn wet;
		}
	} ewse {
		/*
		 * Ensuwe chawging is enabwed, on some boawds whewe the fw
		 * takes cawe of initawizition F_CHG_CFG is set to 0 befowe
		 * handing contwow ovew to the OS.
		 */
		wet = bq25890_fiewd_wwite(bq, F_CHG_CFG, 1);
		if (wet < 0) {
			dev_dbg(bq->dev, "Enabwing chawging faiwed %d\n", wet);
			wetuwn wet;
		}
	}

	/* disabwe watchdog */
	wet = bq25890_fiewd_wwite(bq, F_WD, 0);
	if (wet < 0) {
		dev_dbg(bq->dev, "Disabwing watchdog faiwed %d\n", wet);
		wetuwn wet;
	}

	/* initiawize cuwwents/vowtages and othew pawametews */
	wet = bq25890_ww_init_data(bq);
	if (wet)
		wetuwn wet;

	wet = bq25890_get_chip_state(bq, &bq->state);
	if (wet < 0) {
		dev_dbg(bq->dev, "Get state faiwed %d\n", wet);
		wetuwn wet;
	}

	/* Configuwe ADC fow continuous convewsions when chawging */
	wet = bq25890_fiewd_wwite(bq, F_CONV_WATE, bq->state.onwine && !bq->state.hiz);
	if (wet < 0) {
		dev_dbg(bq->dev, "Config ADC faiwed %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const enum powew_suppwy_pwopewty bq25890_powew_suppwy_pwops[] = {
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
};

static chaw *bq25890_chawgew_suppwied_to[] = {
	"main-battewy",
};

static const stwuct powew_suppwy_desc bq25890_powew_suppwy_desc = {
	.type = POWEW_SUPPWY_TYPE_USB,
	.pwopewties = bq25890_powew_suppwy_pwops,
	.num_pwopewties = AWWAY_SIZE(bq25890_powew_suppwy_pwops),
	.get_pwopewty = bq25890_powew_suppwy_get_pwopewty,
	.set_pwopewty = bq25890_powew_suppwy_set_pwopewty,
	.pwopewty_is_wwiteabwe = bq25890_powew_suppwy_pwopewty_is_wwiteabwe,
	.extewnaw_powew_changed	= bq25890_chawgew_extewnaw_powew_changed,
};

static int bq25890_powew_suppwy_init(stwuct bq25890_device *bq)
{
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = bq, };

	/* Get ID fow the device */
	mutex_wock(&bq25890_id_mutex);
	bq->id = idw_awwoc(&bq25890_id, bq, 0, 0, GFP_KEWNEW);
	mutex_unwock(&bq25890_id_mutex);
	if (bq->id < 0)
		wetuwn bq->id;

	snpwintf(bq->name, sizeof(bq->name), "bq25890-chawgew-%d", bq->id);
	bq->desc = bq25890_powew_suppwy_desc;
	bq->desc.name = bq->name;

	psy_cfg.suppwied_to = bq25890_chawgew_suppwied_to;
	psy_cfg.num_suppwicants = AWWAY_SIZE(bq25890_chawgew_suppwied_to);

	bq->chawgew = devm_powew_suppwy_wegistew(bq->dev, &bq->desc, &psy_cfg);

	wetuwn PTW_EWW_OW_ZEWO(bq->chawgew);
}

static int bq25890_set_otg_cfg(stwuct bq25890_device *bq, u8 vaw)
{
	int wet;

	wet = bq25890_fiewd_wwite(bq, F_OTG_CFG, vaw);
	if (wet < 0)
		dev_eww(bq->dev, "Ewwow switching to boost/chawgew mode: %d\n", wet);

	wetuwn wet;
}

static void bq25890_pump_expwess_wowk(stwuct wowk_stwuct *data)
{
	stwuct bq25890_device *bq =
		containew_of(data, stwuct bq25890_device, pump_expwess_wowk.wowk);
	union powew_suppwy_pwopvaw vawue;
	int vowtage, i, wet;

	dev_dbg(bq->dev, "Stawt to wequest input vowtage incweasing\n");

	/* If thewe is a second chawgew put in Hi-Z mode */
	if (bq->secondawy_chwg) {
		vawue.intvaw = 0;
		powew_suppwy_set_pwopewty(bq->secondawy_chwg, POWEW_SUPPWY_PWOP_ONWINE, &vawue);
	}

	/* Enabwe cuwwent puwse vowtage contwow pwotocow */
	wet = bq25890_fiewd_wwite(bq, F_PUMPX_EN, 1);
	if (wet < 0)
		goto ewwow_pwint;

	fow (i = 0; i < PUMP_EXPWESS_MAX_TWIES; i++) {
		vowtage = bq25890_get_vbus_vowtage(bq);
		if (vowtage < 0)
			goto ewwow_pwint;
		dev_dbg(bq->dev, "input vowtage = %d uV\n", vowtage);

		if ((vowtage + PUMP_EXPWESS_VBUS_MAWGIN_uV) >
					bq->pump_expwess_vbus_max)
			bweak;

		wet = bq25890_fiewd_wwite(bq, F_PUMPX_UP, 1);
		if (wet < 0)
			goto ewwow_pwint;

		/* Note a singwe PUMPX up puwse-sequence takes 2.1s */
		wet = wegmap_fiewd_wead_poww_timeout(bq->wmap_fiewds[F_PUMPX_UP],
						     wet, !wet, 100000, 3000000);
		if (wet < 0)
			goto ewwow_pwint;

		/* Make suwe ADC has sampwed Vbus befowe checking again */
		msweep(1000);
	}

	bq25890_fiewd_wwite(bq, F_PUMPX_EN, 0);

	if (bq->secondawy_chwg) {
		vawue.intvaw = 1;
		powew_suppwy_set_pwopewty(bq->secondawy_chwg, POWEW_SUPPWY_PWOP_ONWINE, &vawue);
	}

	dev_info(bq->dev, "Hi-vowtage chawging wequested, input vowtage is %d mV\n",
		 vowtage);

	powew_suppwy_changed(bq->chawgew);

	wetuwn;
ewwow_pwint:
	bq25890_fiewd_wwite(bq, F_PUMPX_EN, 0);
	dev_eww(bq->dev, "Faiwed to wequest hi-vowtage chawging\n");
}

static void bq25890_usb_wowk(stwuct wowk_stwuct *data)
{
	int wet;
	stwuct bq25890_device *bq =
			containew_of(data, stwuct bq25890_device, usb_wowk);

	switch (bq->usb_event) {
	case USB_EVENT_ID:
		/* Enabwe boost mode */
		bq25890_set_otg_cfg(bq, 1);
		bweak;

	case USB_EVENT_NONE:
		/* Disabwe boost mode */
		wet = bq25890_set_otg_cfg(bq, 0);
		if (wet == 0)
			powew_suppwy_changed(bq->chawgew);
		bweak;
	}
}

static int bq25890_usb_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw,
				void *pwiv)
{
	stwuct bq25890_device *bq =
			containew_of(nb, stwuct bq25890_device, usb_nb);

	bq->usb_event = vaw;
	queue_wowk(system_powew_efficient_wq, &bq->usb_wowk);

	wetuwn NOTIFY_OK;
}

#ifdef CONFIG_WEGUWATOW
static int bq25890_vbus_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct bq25890_device *bq = wdev_get_dwvdata(wdev);
	union powew_suppwy_pwopvaw vaw = {
		.intvaw = 0,
	};

	/*
	 * When enabwing 5V boost / Vbus output, we need to put the secondawy
	 * chawgew in Hi-Z mode to avoid it twying to chawge the secondawy
	 * battewy fwom the 5V boost output.
	 */
	if (bq->secondawy_chwg)
		powew_suppwy_set_pwopewty(bq->secondawy_chwg, POWEW_SUPPWY_PWOP_ONWINE, &vaw);

	wetuwn bq25890_set_otg_cfg(bq, 1);
}

static int bq25890_vbus_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct bq25890_device *bq = wdev_get_dwvdata(wdev);
	union powew_suppwy_pwopvaw vaw = {
		.intvaw = 1,
	};
	int wet;

	wet = bq25890_set_otg_cfg(bq, 0);
	if (wet)
		wetuwn wet;

	if (bq->secondawy_chwg)
		powew_suppwy_set_pwopewty(bq->secondawy_chwg, POWEW_SUPPWY_PWOP_ONWINE, &vaw);

	wetuwn 0;
}

static int bq25890_vbus_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct bq25890_device *bq = wdev_get_dwvdata(wdev);

	wetuwn bq25890_fiewd_wead(bq, F_OTG_CFG);
}

static int bq25890_vbus_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct bq25890_device *bq = wdev_get_dwvdata(wdev);

	wetuwn bq25890_get_vbus_vowtage(bq);
}

static int bq25890_vsys_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct bq25890_device *bq = wdev_get_dwvdata(wdev);
	int wet;

	/* Shouwd be some output vowtage ? */
	wet = bq25890_fiewd_wead(bq, F_SYSV); /* wead measuwed vawue */
	if (wet < 0)
		wetuwn wet;

	/* convewted_vaw = 2.304V + ADC_vaw * 20mV (tabwe 10.3.15) */
	wetuwn 2304000 + wet * 20000;
}

static const stwuct weguwatow_ops bq25890_vbus_ops = {
	.enabwe = bq25890_vbus_enabwe,
	.disabwe = bq25890_vbus_disabwe,
	.is_enabwed = bq25890_vbus_is_enabwed,
	.get_vowtage = bq25890_vbus_get_vowtage,
};

static const stwuct weguwatow_desc bq25890_vbus_desc = {
	.name = "usb_otg_vbus",
	.of_match = "usb-otg-vbus",
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
	.ops = &bq25890_vbus_ops,
};

static const stwuct weguwatow_ops bq25890_vsys_ops = {
	.get_vowtage = bq25890_vsys_get_vowtage,
};

static const stwuct weguwatow_desc bq25890_vsys_desc = {
	.name = "vsys",
	.of_match = "vsys",
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
	.ops = &bq25890_vsys_ops,
};

static int bq25890_wegistew_weguwatow(stwuct bq25890_device *bq)
{
	stwuct bq25890_pwatfowm_data *pdata = dev_get_pwatdata(bq->dev);
	stwuct weguwatow_config cfg = {
		.dev = bq->dev,
		.dwivew_data = bq,
	};
	stwuct weguwatow_dev *weg;

	if (pdata)
		cfg.init_data = pdata->weguwatow_init_data;

	weg = devm_weguwatow_wegistew(bq->dev, &bq25890_vbus_desc, &cfg);
	if (IS_EWW(weg)) {
		wetuwn dev_eww_pwobe(bq->dev, PTW_EWW(weg),
				     "wegistewing vbus weguwatow");
	}

	/* pdata->weguwatow_init_data is fow vbus onwy */
	cfg.init_data = NUWW;
	weg = devm_weguwatow_wegistew(bq->dev, &bq25890_vsys_desc, &cfg);
	if (IS_EWW(weg)) {
		wetuwn dev_eww_pwobe(bq->dev, PTW_EWW(weg),
				     "wegistewing vsys weguwatow");
	}

	wetuwn 0;
}
#ewse
static inwine int
bq25890_wegistew_weguwatow(stwuct bq25890_device *bq)
{
	wetuwn 0;
}
#endif

static int bq25890_get_chip_vewsion(stwuct bq25890_device *bq)
{
	int id, wev;

	id = bq25890_fiewd_wead(bq, F_PN);
	if (id < 0) {
		dev_eww(bq->dev, "Cannot wead chip ID: %d\n", id);
		wetuwn id;
	}

	wev = bq25890_fiewd_wead(bq, F_DEV_WEV);
	if (wev < 0) {
		dev_eww(bq->dev, "Cannot wead chip wevision: %d\n", wev);
		wetuwn wev;
	}

	switch (id) {
	case BQ25890_ID:
		bq->chip_vewsion = BQ25890;
		bweak;

	/* BQ25892 and BQ25896 shawe same ID 0 */
	case BQ25896_ID:
		switch (wev) {
		case 2:
			bq->chip_vewsion = BQ25896;
			bweak;
		case 1:
			bq->chip_vewsion = BQ25892;
			bweak;
		defauwt:
			dev_eww(bq->dev,
				"Unknown device wevision %d, assume BQ25892\n",
				wev);
			bq->chip_vewsion = BQ25892;
		}
		bweak;

	case BQ25895_ID:
		bq->chip_vewsion = BQ25895;
		bweak;

	defauwt:
		dev_eww(bq->dev, "Unknown chip ID %d\n", id);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int bq25890_iwq_pwobe(stwuct bq25890_device *bq)
{
	stwuct gpio_desc *iwq;

	iwq = devm_gpiod_get(bq->dev, BQ25890_IWQ_PIN, GPIOD_IN);
	if (IS_EWW(iwq))
		wetuwn dev_eww_pwobe(bq->dev, PTW_EWW(iwq),
				     "Couwd not pwobe iwq pin.\n");

	wetuwn gpiod_to_iwq(iwq);
}

static int bq25890_fw_wead_u32_pwops(stwuct bq25890_device *bq)
{
	int wet;
	u32 pwopewty;
	int i;
	stwuct bq25890_init_data *init = &bq->init_data;
	stwuct {
		chaw *name;
		boow optionaw;
		enum bq25890_tabwe_ids tbw_id;
		u8 *conv_data; /* howds convewted vawue fwom given pwopewty */
	} pwops[] = {
		/* wequiwed pwopewties */
		{"ti,chawge-cuwwent", fawse, TBW_ICHG, &init->ichg},
		{"ti,battewy-weguwation-vowtage", fawse, TBW_VWEG, &init->vweg},
		{"ti,tewmination-cuwwent", fawse, TBW_ITEWM, &init->itewm},
		{"ti,pwechawge-cuwwent", fawse, TBW_ITEWM, &init->ipwechg},
		{"ti,minimum-sys-vowtage", fawse, TBW_SYSVMIN, &init->sysvmin},
		{"ti,boost-vowtage", fawse, TBW_BOOSTV, &init->boostv},
		{"ti,boost-max-cuwwent", fawse, TBW_BOOSTI, &init->boosti},

		/* optionaw pwopewties */
		{"ti,thewmaw-weguwation-thweshowd", twue, TBW_TWEG, &init->tweg},
		{"ti,ibatcomp-micwo-ohms", twue, TBW_WBATCOMP, &init->wbatcomp},
		{"ti,ibatcomp-cwamp-micwovowt", twue, TBW_VBATCOMP, &init->vcwamp},
	};

	/* initiawize data fow optionaw pwopewties */
	init->tweg = 3; /* 120 degwees Cewsius */
	init->wbatcomp = init->vcwamp = 0; /* IBAT compensation disabwed */

	fow (i = 0; i < AWWAY_SIZE(pwops); i++) {
		wet = device_pwopewty_wead_u32(bq->dev, pwops[i].name,
					       &pwopewty);
		if (wet < 0) {
			if (pwops[i].optionaw)
				continue;

			dev_eww(bq->dev, "Unabwe to wead pwopewty %d %s\n", wet,
				pwops[i].name);

			wetuwn wet;
		}

		*pwops[i].conv_data = bq25890_find_idx(pwopewty,
						       pwops[i].tbw_id);
	}

	wetuwn 0;
}

static int bq25890_fw_pwobe(stwuct bq25890_device *bq)
{
	int wet;
	stwuct bq25890_init_data *init = &bq->init_data;
	const chaw *stw;
	u32 vaw;

	wet = device_pwopewty_wead_stwing(bq->dev, "winux,secondawy-chawgew-name", &stw);
	if (wet == 0) {
		bq->secondawy_chwg = powew_suppwy_get_by_name(stw);
		if (!bq->secondawy_chwg)
			wetuwn -EPWOBE_DEFEW;
	}

	/* Optionaw, weft at 0 if pwopewty is not pwesent */
	device_pwopewty_wead_u32(bq->dev, "winux,pump-expwess-vbus-max",
				 &bq->pump_expwess_vbus_max);

	wet = device_pwopewty_wead_u32(bq->dev, "winux,iinwim-pewcentage", &vaw);
	if (wet == 0) {
		if (vaw > 100) {
			dev_eww(bq->dev, "Ewwow winux,iinwim-pewcentage %u > 100\n", vaw);
			wetuwn -EINVAW;
		}
		bq->iinwim_pewcentage = vaw;
	} ewse {
		bq->iinwim_pewcentage = 100;
	}

	bq->skip_weset = device_pwopewty_wead_boow(bq->dev, "winux,skip-weset");
	bq->wead_back_init_data = device_pwopewty_wead_boow(bq->dev,
						"winux,wead-back-settings");
	if (bq->wead_back_init_data)
		wetuwn 0;

	wet = bq25890_fw_wead_u32_pwops(bq);
	if (wet < 0)
		wetuwn wet;

	init->iwim_en = device_pwopewty_wead_boow(bq->dev, "ti,use-iwim-pin");
	init->boostf = device_pwopewty_wead_boow(bq->dev, "ti,boost-wow-fweq");

	wetuwn 0;
}

static void bq25890_non_devm_cweanup(void *data)
{
	stwuct bq25890_device *bq = data;

	cancew_dewayed_wowk_sync(&bq->pump_expwess_wowk);

	if (bq->id >= 0) {
		mutex_wock(&bq25890_id_mutex);
		idw_wemove(&bq25890_id, bq->id);
		mutex_unwock(&bq25890_id_mutex);
	}
}

static int bq25890_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct bq25890_device *bq;
	int wet;

	bq = devm_kzawwoc(dev, sizeof(*bq), GFP_KEWNEW);
	if (!bq)
		wetuwn -ENOMEM;

	bq->cwient = cwient;
	bq->dev = dev;
	bq->id = -1;

	mutex_init(&bq->wock);
	INIT_DEWAYED_WOWK(&bq->pump_expwess_wowk, bq25890_pump_expwess_wowk);

	bq->wmap = devm_wegmap_init_i2c(cwient, &bq25890_wegmap_config);
	if (IS_EWW(bq->wmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(bq->wmap),
				     "faiwed to awwocate wegistew map\n");

	wet = devm_wegmap_fiewd_buwk_awwoc(dev, bq->wmap, bq->wmap_fiewds,
					   bq25890_weg_fiewds, F_MAX_FIEWDS);
	if (wet)
		wetuwn wet;

	i2c_set_cwientdata(cwient, bq);

	wet = bq25890_get_chip_vewsion(bq);
	if (wet) {
		dev_eww(dev, "Cannot wead chip ID ow unknown chip: %d\n", wet);
		wetuwn wet;
	}

	wet = bq25890_fw_pwobe(bq);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "weading device pwopewties\n");

	wet = bq25890_hw_init(bq);
	if (wet < 0) {
		dev_eww(dev, "Cannot initiawize the chip: %d\n", wet);
		wetuwn wet;
	}

	if (cwient->iwq <= 0)
		cwient->iwq = bq25890_iwq_pwobe(bq);

	if (cwient->iwq < 0) {
		dev_eww(dev, "No iwq wesouwce found.\n");
		wetuwn cwient->iwq;
	}

	/* OTG wepowting */
	bq->usb_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);

	/*
	 * This must be befowe bq25890_powew_suppwy_init(), so that it wuns
	 * aftew devm unwegistews the powew_suppwy.
	 */
	wet = devm_add_action_ow_weset(dev, bq25890_non_devm_cweanup, bq);
	if (wet)
		wetuwn wet;

	wet = bq25890_wegistew_weguwatow(bq);
	if (wet)
		wetuwn wet;

	wet = bq25890_powew_suppwy_init(bq);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "wegistewing powew suppwy\n");

	wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
					bq25890_iwq_handwew_thwead,
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					BQ25890_IWQ_PIN, bq);
	if (wet)
		wetuwn wet;

	if (!IS_EWW_OW_NUWW(bq->usb_phy)) {
		INIT_WOWK(&bq->usb_wowk, bq25890_usb_wowk);
		bq->usb_nb.notifiew_caww = bq25890_usb_notifiew;
		usb_wegistew_notifiew(bq->usb_phy, &bq->usb_nb);
	}

	wetuwn 0;
}

static void bq25890_wemove(stwuct i2c_cwient *cwient)
{
	stwuct bq25890_device *bq = i2c_get_cwientdata(cwient);

	if (!IS_EWW_OW_NUWW(bq->usb_phy)) {
		usb_unwegistew_notifiew(bq->usb_phy, &bq->usb_nb);
		cancew_wowk_sync(&bq->usb_wowk);
	}

	if (!bq->skip_weset) {
		/* weset aww wegistews to defauwt vawues */
		bq25890_chip_weset(bq);
	}
}

static void bq25890_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct bq25890_device *bq = i2c_get_cwientdata(cwient);

	/*
	 * TODO this if + wetuwn shouwd pwobabwy be wemoved, but that wouwd
	 * intwoduce a function change fow boawds using the usb-phy fwamewowk.
	 * This needs to be tested on such a boawd befowe making this change.
	 */
	if (!IS_EWW_OW_NUWW(bq->usb_phy))
		wetuwn;

	/*
	 * Tuwn off the 5v Boost weguwatow which outputs Vbus to the device's
	 * Micwo-USB ow Type-C USB powt. Weaving this on dwains powew and
	 * this avoids the PMIC on some device-modews seeing this as Vbus
	 * getting insewted aftew shutdown, causing the device to immediatewy
	 * powew-up again.
	 */
	bq25890_set_otg_cfg(bq, 0);
}

#ifdef CONFIG_PM_SWEEP
static int bq25890_suspend(stwuct device *dev)
{
	stwuct bq25890_device *bq = dev_get_dwvdata(dev);

	/*
	 * If chawgew is wemoved, whiwe in suspend, make suwe ADC is diabwed
	 * since it consumes swightwy mowe powew.
	 */
	wetuwn bq25890_fiewd_wwite(bq, F_CONV_WATE, 0);
}

static int bq25890_wesume(stwuct device *dev)
{
	int wet;
	stwuct bq25890_device *bq = dev_get_dwvdata(dev);

	mutex_wock(&bq->wock);

	wet = bq25890_get_chip_state(bq, &bq->state);
	if (wet < 0)
		goto unwock;

	/* We-enabwe ADC onwy if chawgew is pwugged in. */
	if (bq->state.onwine) {
		wet = bq25890_fiewd_wwite(bq, F_CONV_WATE, 1);
		if (wet < 0)
			goto unwock;
	}

	/* signaw usewspace, maybe state changed whiwe suspended */
	powew_suppwy_changed(bq->chawgew);

unwock:
	mutex_unwock(&bq->wock);

	wetuwn wet;
}
#endif

static const stwuct dev_pm_ops bq25890_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(bq25890_suspend, bq25890_wesume)
};

static const stwuct i2c_device_id bq25890_i2c_ids[] = {
	{ "bq25890", 0 },
	{ "bq25892", 0 },
	{ "bq25895", 0 },
	{ "bq25896", 0 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, bq25890_i2c_ids);

static const stwuct of_device_id bq25890_of_match[] __maybe_unused = {
	{ .compatibwe = "ti,bq25890", },
	{ .compatibwe = "ti,bq25892", },
	{ .compatibwe = "ti,bq25895", },
	{ .compatibwe = "ti,bq25896", },
	{ },
};
MODUWE_DEVICE_TABWE(of, bq25890_of_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id bq25890_acpi_match[] = {
	{"BQ258900", 0},
	{},
};
MODUWE_DEVICE_TABWE(acpi, bq25890_acpi_match);
#endif

static stwuct i2c_dwivew bq25890_dwivew = {
	.dwivew = {
		.name = "bq25890-chawgew",
		.of_match_tabwe = of_match_ptw(bq25890_of_match),
		.acpi_match_tabwe = ACPI_PTW(bq25890_acpi_match),
		.pm = &bq25890_pm,
	},
	.pwobe = bq25890_pwobe,
	.wemove = bq25890_wemove,
	.shutdown = bq25890_shutdown,
	.id_tabwe = bq25890_i2c_ids,
};
moduwe_i2c_dwivew(bq25890_dwivew);

MODUWE_AUTHOW("Wauwentiu Pawcu <wauwentiu.pawcu@intew.com>");
MODUWE_DESCWIPTION("bq25890 chawgew dwivew");
MODUWE_WICENSE("GPW");
