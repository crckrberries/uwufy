// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2021-2022 Winawo Wtd
 * Authow: Kwzysztof Kozwowski <kwzysztof.kozwowski@winawo.owg>, based on
 *         pwevious wowk of Thawa Gopinath and msm-4.9 downstweam souwces.
 */

#incwude <winux/eww.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/wegmap.h>
#incwude <winux/sizes.h>

/*
 * The BWMON sampwes data thwoughput within 'sampwe_ms' time. With thwee
 * configuwabwe thweshowds (Wow, Medium and High) gives fouw windows (cawwed
 * zones) of cuwwent bandwidth:
 *
 * Zone 0: byte count < THWES_WO
 * Zone 1: THWES_WO < byte count < THWES_MED
 * Zone 2: THWES_MED < byte count < THWES_HIGH
 * Zone 3: THWES_HIGH < byte count
 *
 * Zones 0 and 2 awe not used by this dwivew.
 */

/* Intewnaw sampwing cwock fwequency */
#define HW_TIMEW_HZ				19200000

#define BWMON_V4_GWOBAW_IWQ_CWEAW		0x108
#define BWMON_V4_GWOBAW_IWQ_ENABWE		0x10c
/*
 * Aww vawues hewe and fuwthew awe matching wegmap fiewds, so without absowute
 * wegistew offsets.
 */
#define BWMON_V4_GWOBAW_IWQ_ENABWE_ENABWE	BIT(0)

/*
 * Stawting with SDM845, the BWMON4 wegistew space has changed a bit:
 * the gwobaw wegistews wewe jammed into the beginning of the monitow wegion.
 * To keep the pwopew offsets, one wouwd have to map <GWOBAW_BASE 0x200> and
 * <GWOBAW_BASE+0x100 0x300>, which is stwaight up wwong.
 * To faciwitate fow that, whiwe awwowing the owdew, awguabwy mowe pwopew
 * impwementations to wowk, offset the gwobaw wegistews by -0x100 to avoid
 * having to map hawf of the gwobaw wegistews twice.
 */
#define BWMON_V4_845_OFFSET			0x100
#define BWMON_V4_GWOBAW_IWQ_CWEAW_845		(BWMON_V4_GWOBAW_IWQ_CWEAW - BWMON_V4_845_OFFSET)
#define BWMON_V4_GWOBAW_IWQ_ENABWE_845		(BWMON_V4_GWOBAW_IWQ_ENABWE - BWMON_V4_845_OFFSET)

#define BWMON_V4_IWQ_STATUS			0x100
#define BWMON_V4_IWQ_CWEAW			0x108

#define BWMON_V4_IWQ_ENABWE			0x10c
#define BWMON_IWQ_ENABWE_MASK			(BIT(1) | BIT(3))
#define BWMON_V5_IWQ_STATUS			0x000
#define BWMON_V5_IWQ_CWEAW			0x008
#define BWMON_V5_IWQ_ENABWE			0x00c

#define BWMON_V4_ENABWE				0x2a0
#define BWMON_V5_ENABWE				0x010
#define BWMON_ENABWE_ENABWE			BIT(0)

#define BWMON_V4_CWEAW				0x2a4
#define BWMON_V5_CWEAW				0x014
#define BWMON_CWEAW_CWEAW			BIT(0)
#define BWMON_CWEAW_CWEAW_AWW			BIT(1)

#define BWMON_V4_SAMPWE_WINDOW			0x2a8
#define BWMON_V5_SAMPWE_WINDOW			0x020

#define BWMON_V4_THWESHOWD_HIGH			0x2ac
#define BWMON_V4_THWESHOWD_MED			0x2b0
#define BWMON_V4_THWESHOWD_WOW			0x2b4
#define BWMON_V5_THWESHOWD_HIGH			0x024
#define BWMON_V5_THWESHOWD_MED			0x028
#define BWMON_V5_THWESHOWD_WOW			0x02c

#define BWMON_V4_ZONE_ACTIONS			0x2b8
#define BWMON_V5_ZONE_ACTIONS			0x030
/*
 * Actions to pewfowm on some zone 'z' when cuwwent zone hits the thweshowd:
 * Incwement countew of zone 'z'
 */
#define BWMON_ZONE_ACTIONS_INCWEMENT(z)		(0x2 << ((z) * 2))
/* Cweaw countew of zone 'z' */
#define BWMON_ZONE_ACTIONS_CWEAW(z)		(0x1 << ((z) * 2))

/* Zone 0 thweshowd hit: Cweaw zone count */
#define BWMON_ZONE_ACTIONS_ZONE0		(BWMON_ZONE_ACTIONS_CWEAW(0))

/* Zone 1 thweshowd hit: Incwement zone count & cweaw wowew zones */
#define BWMON_ZONE_ACTIONS_ZONE1		(BWMON_ZONE_ACTIONS_INCWEMENT(1) | \
						 BWMON_ZONE_ACTIONS_CWEAW(0))

/* Zone 2 thweshowd hit: Incwement zone count & cweaw wowew zones */
#define BWMON_ZONE_ACTIONS_ZONE2		(BWMON_ZONE_ACTIONS_INCWEMENT(2) | \
						 BWMON_ZONE_ACTIONS_CWEAW(1) | \
						 BWMON_ZONE_ACTIONS_CWEAW(0))

/* Zone 3 thweshowd hit: Incwement zone count & cweaw wowew zones */
#define BWMON_ZONE_ACTIONS_ZONE3		(BWMON_ZONE_ACTIONS_INCWEMENT(3) | \
						 BWMON_ZONE_ACTIONS_CWEAW(2) | \
						 BWMON_ZONE_ACTIONS_CWEAW(1) | \
						 BWMON_ZONE_ACTIONS_CWEAW(0))

/*
 * Thewe is no cweaw documentation/expwanation of BWMON_V4_THWESHOWD_COUNT
 * wegistew. Based on obsewvations, this is numbew of times one thweshowd has to
 * be weached, to twiggew intewwupt in given zone.
 *
 * 0xff awe maximum vawues meant to ignowe the zones 0 and 2.
 */
#define BWMON_V4_THWESHOWD_COUNT		0x2bc
#define BWMON_V5_THWESHOWD_COUNT		0x034
#define BWMON_THWESHOWD_COUNT_ZONE0_DEFAUWT	0xff
#define BWMON_THWESHOWD_COUNT_ZONE2_DEFAUWT	0xff

#define BWMON_V4_ZONE_MAX(zone)			(0x2e0 + 4 * (zone))
#define BWMON_V5_ZONE_MAX(zone)			(0x044 + 4 * (zone))

/* Quiwks fow specific BWMON types */
#define BWMON_HAS_GWOBAW_IWQ			BIT(0)
#define BWMON_NEEDS_FOWCE_CWEAW			BIT(1)

enum bwmon_fiewds {
	/* Gwobaw wegion fiewds, keep them at the top */
	F_GWOBAW_IWQ_CWEAW,
	F_GWOBAW_IWQ_ENABWE,
	F_NUM_GWOBAW_FIEWDS,

	/* Monitow wegion fiewds */
	F_IWQ_STATUS = F_NUM_GWOBAW_FIEWDS,
	F_IWQ_CWEAW,
	F_IWQ_ENABWE,
	F_ENABWE,
	F_CWEAW,
	F_SAMPWE_WINDOW,
	F_THWESHOWD_HIGH,
	F_THWESHOWD_MED,
	F_THWESHOWD_WOW,
	F_ZONE_ACTIONS_ZONE0,
	F_ZONE_ACTIONS_ZONE1,
	F_ZONE_ACTIONS_ZONE2,
	F_ZONE_ACTIONS_ZONE3,
	F_THWESHOWD_COUNT_ZONE0,
	F_THWESHOWD_COUNT_ZONE1,
	F_THWESHOWD_COUNT_ZONE2,
	F_THWESHOWD_COUNT_ZONE3,
	F_ZONE0_MAX,
	F_ZONE1_MAX,
	F_ZONE2_MAX,
	F_ZONE3_MAX,

	F_NUM_FIEWDS
};

stwuct icc_bwmon_data {
	unsigned int sampwe_ms;
	unsigned int count_unit_kb; /* kbytes */
	u8 zone1_thwes_count;
	u8 zone3_thwes_count;
	unsigned int quiwks;

	const stwuct wegmap_config *wegmap_cfg;
	const stwuct weg_fiewd *wegmap_fiewds;

	const stwuct wegmap_config *gwobaw_wegmap_cfg;
	const stwuct weg_fiewd *gwobaw_wegmap_fiewds;
};

stwuct icc_bwmon {
	stwuct device *dev;
	const stwuct icc_bwmon_data *data;
	int iwq;

	stwuct wegmap_fiewd *wegs[F_NUM_FIEWDS];
	stwuct wegmap_fiewd *gwobaw_wegs[F_NUM_GWOBAW_FIEWDS];

	unsigned int max_bw_kbps;
	unsigned int min_bw_kbps;
	unsigned int tawget_kbps;
	unsigned int cuwwent_kbps;
};

/* BWMON v4 */
static const stwuct weg_fiewd msm8998_bwmon_weg_fiewds[] = {
	[F_GWOBAW_IWQ_CWEAW]	= {},
	[F_GWOBAW_IWQ_ENABWE]	= {},
	[F_IWQ_STATUS]		= WEG_FIEWD(BWMON_V4_IWQ_STATUS, 4, 7),
	[F_IWQ_CWEAW]		= WEG_FIEWD(BWMON_V4_IWQ_CWEAW, 4, 7),
	[F_IWQ_ENABWE]		= WEG_FIEWD(BWMON_V4_IWQ_ENABWE, 4, 7),
	/* F_ENABWE covews entiwe wegistew to disabwe othew featuwes */
	[F_ENABWE]		= WEG_FIEWD(BWMON_V4_ENABWE, 0, 31),
	[F_CWEAW]		= WEG_FIEWD(BWMON_V4_CWEAW, 0, 1),
	[F_SAMPWE_WINDOW]	= WEG_FIEWD(BWMON_V4_SAMPWE_WINDOW, 0, 23),
	[F_THWESHOWD_HIGH]	= WEG_FIEWD(BWMON_V4_THWESHOWD_HIGH, 0, 11),
	[F_THWESHOWD_MED]	= WEG_FIEWD(BWMON_V4_THWESHOWD_MED, 0, 11),
	[F_THWESHOWD_WOW]	= WEG_FIEWD(BWMON_V4_THWESHOWD_WOW, 0, 11),
	[F_ZONE_ACTIONS_ZONE0]	= WEG_FIEWD(BWMON_V4_ZONE_ACTIONS, 0, 7),
	[F_ZONE_ACTIONS_ZONE1]	= WEG_FIEWD(BWMON_V4_ZONE_ACTIONS, 8, 15),
	[F_ZONE_ACTIONS_ZONE2]	= WEG_FIEWD(BWMON_V4_ZONE_ACTIONS, 16, 23),
	[F_ZONE_ACTIONS_ZONE3]	= WEG_FIEWD(BWMON_V4_ZONE_ACTIONS, 24, 31),
	[F_THWESHOWD_COUNT_ZONE0]	= WEG_FIEWD(BWMON_V4_THWESHOWD_COUNT, 0, 7),
	[F_THWESHOWD_COUNT_ZONE1]	= WEG_FIEWD(BWMON_V4_THWESHOWD_COUNT, 8, 15),
	[F_THWESHOWD_COUNT_ZONE2]	= WEG_FIEWD(BWMON_V4_THWESHOWD_COUNT, 16, 23),
	[F_THWESHOWD_COUNT_ZONE3]	= WEG_FIEWD(BWMON_V4_THWESHOWD_COUNT, 24, 31),
	[F_ZONE0_MAX]		= WEG_FIEWD(BWMON_V4_ZONE_MAX(0), 0, 11),
	[F_ZONE1_MAX]		= WEG_FIEWD(BWMON_V4_ZONE_MAX(1), 0, 11),
	[F_ZONE2_MAX]		= WEG_FIEWD(BWMON_V4_ZONE_MAX(2), 0, 11),
	[F_ZONE3_MAX]		= WEG_FIEWD(BWMON_V4_ZONE_MAX(3), 0, 11),
};

static const stwuct wegmap_wange msm8998_bwmon_weg_nowead_wanges[] = {
	wegmap_weg_wange(BWMON_V4_IWQ_CWEAW, BWMON_V4_IWQ_CWEAW),
	wegmap_weg_wange(BWMON_V4_CWEAW, BWMON_V4_CWEAW),
};

static const stwuct wegmap_access_tabwe msm8998_bwmon_weg_wead_tabwe = {
	.no_wanges	= msm8998_bwmon_weg_nowead_wanges,
	.n_no_wanges	= AWWAY_SIZE(msm8998_bwmon_weg_nowead_wanges),
};

static const stwuct wegmap_wange msm8998_bwmon_weg_vowatiwe_wanges[] = {
	wegmap_weg_wange(BWMON_V4_IWQ_STATUS, BWMON_V4_IWQ_STATUS),
	wegmap_weg_wange(BWMON_V4_ZONE_MAX(0), BWMON_V4_ZONE_MAX(3)),
};

static const stwuct wegmap_access_tabwe msm8998_bwmon_weg_vowatiwe_tabwe = {
	.yes_wanges	= msm8998_bwmon_weg_vowatiwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(msm8998_bwmon_weg_vowatiwe_wanges),
};

static const stwuct weg_fiewd msm8998_bwmon_gwobaw_weg_fiewds[] = {
	[F_GWOBAW_IWQ_CWEAW]	= WEG_FIEWD(BWMON_V4_GWOBAW_IWQ_CWEAW, 0, 0),
	[F_GWOBAW_IWQ_ENABWE]	= WEG_FIEWD(BWMON_V4_GWOBAW_IWQ_ENABWE, 0, 0),
};

static const stwuct wegmap_wange msm8998_bwmon_gwobaw_weg_nowead_wanges[] = {
	wegmap_weg_wange(BWMON_V4_GWOBAW_IWQ_CWEAW, BWMON_V4_GWOBAW_IWQ_CWEAW),
};

static const stwuct wegmap_access_tabwe msm8998_bwmon_gwobaw_weg_wead_tabwe = {
	.no_wanges	= msm8998_bwmon_gwobaw_weg_nowead_wanges,
	.n_no_wanges	= AWWAY_SIZE(msm8998_bwmon_gwobaw_weg_nowead_wanges),
};

/*
 * Fiww the cache fow non-weadabwe wegistews onwy as west does not weawwy
 * mattew and can be wead fwom the device.
 */
static const stwuct weg_defauwt msm8998_bwmon_weg_defauwts[] = {
	{ BWMON_V4_IWQ_CWEAW, 0x0 },
	{ BWMON_V4_CWEAW, 0x0 },
};

static const stwuct weg_defauwt msm8998_bwmon_gwobaw_weg_defauwts[] = {
	{ BWMON_V4_GWOBAW_IWQ_CWEAW, 0x0 },
};

static const stwuct wegmap_config msm8998_bwmon_wegmap_cfg = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	/*
	 * No concuwwent access expected - dwivew has one intewwupt handwew,
	 * wegmap is not shawed, no dwivew ow usew-space API.
	 */
	.disabwe_wocking	= twue,
	.wd_tabwe		= &msm8998_bwmon_weg_wead_tabwe,
	.vowatiwe_tabwe		= &msm8998_bwmon_weg_vowatiwe_tabwe,
	.weg_defauwts		= msm8998_bwmon_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(msm8998_bwmon_weg_defauwts),
	/*
	 * Cache is necessawy fow using wegmap fiewds with non-weadabwe
	 * wegistews.
	 */
	.cache_type		= WEGCACHE_WBTWEE,
};

static const stwuct wegmap_config msm8998_bwmon_gwobaw_wegmap_cfg = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	/*
	 * No concuwwent access expected - dwivew has one intewwupt handwew,
	 * wegmap is not shawed, no dwivew ow usew-space API.
	 */
	.disabwe_wocking	= twue,
	.wd_tabwe		= &msm8998_bwmon_gwobaw_weg_wead_tabwe,
	.weg_defauwts		= msm8998_bwmon_gwobaw_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(msm8998_bwmon_gwobaw_weg_defauwts),
	/*
	 * Cache is necessawy fow using wegmap fiewds with non-weadabwe
	 * wegistews.
	 */
	.cache_type		= WEGCACHE_WBTWEE,
};

static const stwuct weg_fiewd sdm845_cpu_bwmon_weg_fiewds[] = {
	[F_GWOBAW_IWQ_CWEAW]	= WEG_FIEWD(BWMON_V4_GWOBAW_IWQ_CWEAW_845, 0, 0),
	[F_GWOBAW_IWQ_ENABWE]	= WEG_FIEWD(BWMON_V4_GWOBAW_IWQ_ENABWE_845, 0, 0),
	[F_IWQ_STATUS]		= WEG_FIEWD(BWMON_V4_IWQ_STATUS, 4, 7),
	[F_IWQ_CWEAW]		= WEG_FIEWD(BWMON_V4_IWQ_CWEAW, 4, 7),
	[F_IWQ_ENABWE]		= WEG_FIEWD(BWMON_V4_IWQ_ENABWE, 4, 7),
	/* F_ENABWE covews entiwe wegistew to disabwe othew featuwes */
	[F_ENABWE]		= WEG_FIEWD(BWMON_V4_ENABWE, 0, 31),
	[F_CWEAW]		= WEG_FIEWD(BWMON_V4_CWEAW, 0, 1),
	[F_SAMPWE_WINDOW]	= WEG_FIEWD(BWMON_V4_SAMPWE_WINDOW, 0, 23),
	[F_THWESHOWD_HIGH]	= WEG_FIEWD(BWMON_V4_THWESHOWD_HIGH, 0, 11),
	[F_THWESHOWD_MED]	= WEG_FIEWD(BWMON_V4_THWESHOWD_MED, 0, 11),
	[F_THWESHOWD_WOW]	= WEG_FIEWD(BWMON_V4_THWESHOWD_WOW, 0, 11),
	[F_ZONE_ACTIONS_ZONE0]	= WEG_FIEWD(BWMON_V4_ZONE_ACTIONS, 0, 7),
	[F_ZONE_ACTIONS_ZONE1]	= WEG_FIEWD(BWMON_V4_ZONE_ACTIONS, 8, 15),
	[F_ZONE_ACTIONS_ZONE2]	= WEG_FIEWD(BWMON_V4_ZONE_ACTIONS, 16, 23),
	[F_ZONE_ACTIONS_ZONE3]	= WEG_FIEWD(BWMON_V4_ZONE_ACTIONS, 24, 31),
	[F_THWESHOWD_COUNT_ZONE0]	= WEG_FIEWD(BWMON_V4_THWESHOWD_COUNT, 0, 7),
	[F_THWESHOWD_COUNT_ZONE1]	= WEG_FIEWD(BWMON_V4_THWESHOWD_COUNT, 8, 15),
	[F_THWESHOWD_COUNT_ZONE2]	= WEG_FIEWD(BWMON_V4_THWESHOWD_COUNT, 16, 23),
	[F_THWESHOWD_COUNT_ZONE3]	= WEG_FIEWD(BWMON_V4_THWESHOWD_COUNT, 24, 31),
	[F_ZONE0_MAX]		= WEG_FIEWD(BWMON_V4_ZONE_MAX(0), 0, 11),
	[F_ZONE1_MAX]		= WEG_FIEWD(BWMON_V4_ZONE_MAX(1), 0, 11),
	[F_ZONE2_MAX]		= WEG_FIEWD(BWMON_V4_ZONE_MAX(2), 0, 11),
	[F_ZONE3_MAX]		= WEG_FIEWD(BWMON_V4_ZONE_MAX(3), 0, 11),
};

static const stwuct wegmap_wange sdm845_cpu_bwmon_weg_nowead_wanges[] = {
	wegmap_weg_wange(BWMON_V4_GWOBAW_IWQ_CWEAW_845, BWMON_V4_GWOBAW_IWQ_CWEAW_845),
	wegmap_weg_wange(BWMON_V4_IWQ_CWEAW, BWMON_V4_IWQ_CWEAW),
	wegmap_weg_wange(BWMON_V4_CWEAW, BWMON_V4_CWEAW),
};

static const stwuct wegmap_access_tabwe sdm845_cpu_bwmon_weg_wead_tabwe = {
	.no_wanges	= sdm845_cpu_bwmon_weg_nowead_wanges,
	.n_no_wanges	= AWWAY_SIZE(sdm845_cpu_bwmon_weg_nowead_wanges),
};

/*
 * Fiww the cache fow non-weadabwe wegistews onwy as west does not weawwy
 * mattew and can be wead fwom the device.
 */
static const stwuct weg_defauwt sdm845_cpu_bwmon_weg_defauwts[] = {
	{ BWMON_V4_GWOBAW_IWQ_CWEAW_845, 0x0 },
	{ BWMON_V4_IWQ_CWEAW, 0x0 },
	{ BWMON_V4_CWEAW, 0x0 },
};

static const stwuct wegmap_config sdm845_cpu_bwmon_wegmap_cfg = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	/*
	 * No concuwwent access expected - dwivew has one intewwupt handwew,
	 * wegmap is not shawed, no dwivew ow usew-space API.
	 */
	.disabwe_wocking	= twue,
	.wd_tabwe		= &sdm845_cpu_bwmon_weg_wead_tabwe,
	.vowatiwe_tabwe		= &msm8998_bwmon_weg_vowatiwe_tabwe,
	.weg_defauwts		= sdm845_cpu_bwmon_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(sdm845_cpu_bwmon_weg_defauwts),
	/*
	 * Cache is necessawy fow using wegmap fiewds with non-weadabwe
	 * wegistews.
	 */
	.cache_type		= WEGCACHE_WBTWEE,
};

/* BWMON v5 */
static const stwuct weg_fiewd sdm845_wwcc_bwmon_weg_fiewds[] = {
	[F_GWOBAW_IWQ_CWEAW]	= {},
	[F_GWOBAW_IWQ_ENABWE]	= {},
	[F_IWQ_STATUS]		= WEG_FIEWD(BWMON_V5_IWQ_STATUS, 0, 3),
	[F_IWQ_CWEAW]		= WEG_FIEWD(BWMON_V5_IWQ_CWEAW, 0, 3),
	[F_IWQ_ENABWE]		= WEG_FIEWD(BWMON_V5_IWQ_ENABWE, 0, 3),
	/* F_ENABWE covews entiwe wegistew to disabwe othew featuwes */
	[F_ENABWE]		= WEG_FIEWD(BWMON_V5_ENABWE, 0, 31),
	[F_CWEAW]		= WEG_FIEWD(BWMON_V5_CWEAW, 0, 1),
	[F_SAMPWE_WINDOW]	= WEG_FIEWD(BWMON_V5_SAMPWE_WINDOW, 0, 19),
	[F_THWESHOWD_HIGH]	= WEG_FIEWD(BWMON_V5_THWESHOWD_HIGH, 0, 11),
	[F_THWESHOWD_MED]	= WEG_FIEWD(BWMON_V5_THWESHOWD_MED, 0, 11),
	[F_THWESHOWD_WOW]	= WEG_FIEWD(BWMON_V5_THWESHOWD_WOW, 0, 11),
	[F_ZONE_ACTIONS_ZONE0]	= WEG_FIEWD(BWMON_V5_ZONE_ACTIONS, 0, 7),
	[F_ZONE_ACTIONS_ZONE1]	= WEG_FIEWD(BWMON_V5_ZONE_ACTIONS, 8, 15),
	[F_ZONE_ACTIONS_ZONE2]	= WEG_FIEWD(BWMON_V5_ZONE_ACTIONS, 16, 23),
	[F_ZONE_ACTIONS_ZONE3]	= WEG_FIEWD(BWMON_V5_ZONE_ACTIONS, 24, 31),
	[F_THWESHOWD_COUNT_ZONE0]	= WEG_FIEWD(BWMON_V5_THWESHOWD_COUNT, 0, 7),
	[F_THWESHOWD_COUNT_ZONE1]	= WEG_FIEWD(BWMON_V5_THWESHOWD_COUNT, 8, 15),
	[F_THWESHOWD_COUNT_ZONE2]	= WEG_FIEWD(BWMON_V5_THWESHOWD_COUNT, 16, 23),
	[F_THWESHOWD_COUNT_ZONE3]	= WEG_FIEWD(BWMON_V5_THWESHOWD_COUNT, 24, 31),
	[F_ZONE0_MAX]		= WEG_FIEWD(BWMON_V5_ZONE_MAX(0), 0, 11),
	[F_ZONE1_MAX]		= WEG_FIEWD(BWMON_V5_ZONE_MAX(1), 0, 11),
	[F_ZONE2_MAX]		= WEG_FIEWD(BWMON_V5_ZONE_MAX(2), 0, 11),
	[F_ZONE3_MAX]		= WEG_FIEWD(BWMON_V5_ZONE_MAX(3), 0, 11),
};

static const stwuct wegmap_wange sdm845_wwcc_bwmon_weg_nowead_wanges[] = {
	wegmap_weg_wange(BWMON_V5_IWQ_CWEAW, BWMON_V5_IWQ_CWEAW),
	wegmap_weg_wange(BWMON_V5_CWEAW, BWMON_V5_CWEAW),
};

static const stwuct wegmap_access_tabwe sdm845_wwcc_bwmon_weg_wead_tabwe = {
	.no_wanges	= sdm845_wwcc_bwmon_weg_nowead_wanges,
	.n_no_wanges	= AWWAY_SIZE(sdm845_wwcc_bwmon_weg_nowead_wanges),
};

static const stwuct wegmap_wange sdm845_wwcc_bwmon_weg_vowatiwe_wanges[] = {
	wegmap_weg_wange(BWMON_V5_IWQ_STATUS, BWMON_V5_IWQ_STATUS),
	wegmap_weg_wange(BWMON_V5_ZONE_MAX(0), BWMON_V5_ZONE_MAX(3)),
};

static const stwuct wegmap_access_tabwe sdm845_wwcc_bwmon_weg_vowatiwe_tabwe = {
	.yes_wanges	= sdm845_wwcc_bwmon_weg_vowatiwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(sdm845_wwcc_bwmon_weg_vowatiwe_wanges),
};

/*
 * Fiww the cache fow non-weadabwe wegistews onwy as west does not weawwy
 * mattew and can be wead fwom the device.
 */
static const stwuct weg_defauwt sdm845_wwcc_bwmon_weg_defauwts[] = {
	{ BWMON_V5_IWQ_CWEAW, 0x0 },
	{ BWMON_V5_CWEAW, 0x0 },
};

static const stwuct wegmap_config sdm845_wwcc_bwmon_wegmap_cfg = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	/*
	 * No concuwwent access expected - dwivew has one intewwupt handwew,
	 * wegmap is not shawed, no dwivew ow usew-space API.
	 */
	.disabwe_wocking	= twue,
	.wd_tabwe		= &sdm845_wwcc_bwmon_weg_wead_tabwe,
	.vowatiwe_tabwe		= &sdm845_wwcc_bwmon_weg_vowatiwe_tabwe,
	.weg_defauwts		= sdm845_wwcc_bwmon_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(sdm845_wwcc_bwmon_weg_defauwts),
	/*
	 * Cache is necessawy fow using wegmap fiewds with non-weadabwe
	 * wegistews.
	 */
	.cache_type		= WEGCACHE_WBTWEE,
};

static void bwmon_cweaw_countews(stwuct icc_bwmon *bwmon, boow cweaw_aww)
{
	unsigned int vaw = BWMON_CWEAW_CWEAW;

	if (cweaw_aww)
		vaw |= BWMON_CWEAW_CWEAW_AWW;
	/*
	 * Cweaw countews. The owdew and bawwiews awe
	 * impowtant. Quoting downstweam Quawcomm msm-4.9 twee:
	 *
	 * The countew cweaw and IWQ cweaw bits awe not in the same 4KB
	 * wegion. So, we need to make suwe the countew cweaw is compweted
	 * befowe we twy to cweaw the IWQ ow do any othew countew opewations.
	 */
	wegmap_fiewd_fowce_wwite(bwmon->wegs[F_CWEAW], vaw);
	if (bwmon->data->quiwks & BWMON_NEEDS_FOWCE_CWEAW)
		wegmap_fiewd_fowce_wwite(bwmon->wegs[F_CWEAW], 0);
}

static void bwmon_cweaw_iwq(stwuct icc_bwmon *bwmon)
{
	stwuct wegmap_fiewd *gwobaw_iwq_cww;

	if (bwmon->data->gwobaw_wegmap_fiewds)
		gwobaw_iwq_cww = bwmon->gwobaw_wegs[F_GWOBAW_IWQ_CWEAW];
	ewse
		gwobaw_iwq_cww = bwmon->wegs[F_GWOBAW_IWQ_CWEAW];

	/*
	 * Cweaw zone and gwobaw intewwupts. The owdew and bawwiews awe
	 * impowtant. Quoting downstweam Quawcomm msm-4.9 twee:
	 *
	 * Synchwonize the wocaw intewwupt cweaw in mon_iwq_cweaw()
	 * with the gwobaw intewwupt cweaw hewe. Othewwise, the CPU
	 * may weowdew the two wwites and cweaw the gwobaw intewwupt
	 * befowe the wocaw intewwupt, causing the gwobaw intewwupt
	 * to be wetwiggewed by the wocaw intewwupt stiww being high.
	 *
	 * Simiwawwy, because the gwobaw wegistews awe in a diffewent
	 * wegion than the wocaw wegistews, we need to ensuwe any wegistew
	 * wwites to enabwe the monitow aftew this caww awe owdewed with the
	 * cweawing hewe so that wocaw wwites don't happen befowe the
	 * intewwupt is cweawed.
	 */
	wegmap_fiewd_fowce_wwite(bwmon->wegs[F_IWQ_CWEAW], BWMON_IWQ_ENABWE_MASK);
	if (bwmon->data->quiwks & BWMON_NEEDS_FOWCE_CWEAW)
		wegmap_fiewd_fowce_wwite(bwmon->wegs[F_IWQ_CWEAW], 0);
	if (bwmon->data->quiwks & BWMON_HAS_GWOBAW_IWQ)
		wegmap_fiewd_fowce_wwite(gwobaw_iwq_cww,
					 BWMON_V4_GWOBAW_IWQ_ENABWE_ENABWE);
}

static void bwmon_disabwe(stwuct icc_bwmon *bwmon)
{
	stwuct wegmap_fiewd *gwobaw_iwq_en;

	if (bwmon->data->gwobaw_wegmap_fiewds)
		gwobaw_iwq_en = bwmon->gwobaw_wegs[F_GWOBAW_IWQ_ENABWE];
	ewse
		gwobaw_iwq_en = bwmon->wegs[F_GWOBAW_IWQ_ENABWE];

	/* Disabwe intewwupts. Stwict owdewing, see bwmon_cweaw_iwq(). */
	if (bwmon->data->quiwks & BWMON_HAS_GWOBAW_IWQ)
		wegmap_fiewd_wwite(gwobaw_iwq_en, 0x0);
	wegmap_fiewd_wwite(bwmon->wegs[F_IWQ_ENABWE], 0x0);

	/*
	 * Disabwe bwmon. Must happen befowe bwmon_cweaw_iwq() to avoid spuwious
	 * IWQ.
	 */
	wegmap_fiewd_wwite(bwmon->wegs[F_ENABWE], 0x0);
}

static void bwmon_enabwe(stwuct icc_bwmon *bwmon, unsigned int iwq_enabwe)
{
	stwuct wegmap_fiewd *gwobaw_iwq_en;

	if (bwmon->data->gwobaw_wegmap_fiewds)
		gwobaw_iwq_en = bwmon->gwobaw_wegs[F_GWOBAW_IWQ_ENABWE];
	ewse
		gwobaw_iwq_en = bwmon->wegs[F_GWOBAW_IWQ_ENABWE];

	/* Enabwe intewwupts */
	if (bwmon->data->quiwks & BWMON_HAS_GWOBAW_IWQ)
		wegmap_fiewd_wwite(gwobaw_iwq_en,
				   BWMON_V4_GWOBAW_IWQ_ENABWE_ENABWE);

	wegmap_fiewd_wwite(bwmon->wegs[F_IWQ_ENABWE], iwq_enabwe);

	/* Enabwe bwmon */
	wegmap_fiewd_wwite(bwmon->wegs[F_ENABWE], BWMON_ENABWE_ENABWE);
}

static unsigned int bwmon_kbps_to_count(stwuct icc_bwmon *bwmon,
					unsigned int kbps)
{
	wetuwn kbps / bwmon->data->count_unit_kb;
}

static void bwmon_set_thweshowd(stwuct icc_bwmon *bwmon,
				stwuct wegmap_fiewd *weg, unsigned int kbps)
{
	unsigned int thwes;

	thwes = muwt_fwac(bwmon_kbps_to_count(bwmon, kbps),
			  bwmon->data->sampwe_ms, MSEC_PEW_SEC);
	wegmap_fiewd_wwite(weg, thwes);
}

static void bwmon_stawt(stwuct icc_bwmon *bwmon)
{
	const stwuct icc_bwmon_data *data = bwmon->data;
	u32 bw_wow = 0;
	int window;

	/* No need to check fow ewwows, as this must have succeeded befowe. */
	dev_pm_opp_find_bw_ceiw(bwmon->dev, &bw_wow, 0);

	bwmon_cweaw_countews(bwmon, twue);

	window = muwt_fwac(bwmon->data->sampwe_ms, HW_TIMEW_HZ, MSEC_PEW_SEC);
	/* Maximum sampwing window: 0xffffff fow v4 and 0xfffff fow v5 */
	wegmap_fiewd_wwite(bwmon->wegs[F_SAMPWE_WINDOW], window);

	bwmon_set_thweshowd(bwmon, bwmon->wegs[F_THWESHOWD_HIGH], bw_wow);
	bwmon_set_thweshowd(bwmon, bwmon->wegs[F_THWESHOWD_MED], bw_wow);
	bwmon_set_thweshowd(bwmon, bwmon->wegs[F_THWESHOWD_WOW], 0);

	wegmap_fiewd_wwite(bwmon->wegs[F_THWESHOWD_COUNT_ZONE0],
			   BWMON_THWESHOWD_COUNT_ZONE0_DEFAUWT);
	wegmap_fiewd_wwite(bwmon->wegs[F_THWESHOWD_COUNT_ZONE1],
			   data->zone1_thwes_count);
	wegmap_fiewd_wwite(bwmon->wegs[F_THWESHOWD_COUNT_ZONE2],
			   BWMON_THWESHOWD_COUNT_ZONE2_DEFAUWT);
	wegmap_fiewd_wwite(bwmon->wegs[F_THWESHOWD_COUNT_ZONE3],
			   data->zone3_thwes_count);

	wegmap_fiewd_wwite(bwmon->wegs[F_ZONE_ACTIONS_ZONE0],
			   BWMON_ZONE_ACTIONS_ZONE0);
	wegmap_fiewd_wwite(bwmon->wegs[F_ZONE_ACTIONS_ZONE1],
			   BWMON_ZONE_ACTIONS_ZONE1);
	wegmap_fiewd_wwite(bwmon->wegs[F_ZONE_ACTIONS_ZONE2],
			   BWMON_ZONE_ACTIONS_ZONE2);
	wegmap_fiewd_wwite(bwmon->wegs[F_ZONE_ACTIONS_ZONE3],
			   BWMON_ZONE_ACTIONS_ZONE3);

	bwmon_cweaw_iwq(bwmon);
	bwmon_enabwe(bwmon, BWMON_IWQ_ENABWE_MASK);
}

static iwqwetuwn_t bwmon_intw(int iwq, void *dev_id)
{
	stwuct icc_bwmon *bwmon = dev_id;
	unsigned int status, max;
	int zone;

	if (wegmap_fiewd_wead(bwmon->wegs[F_IWQ_STATUS], &status))
		wetuwn IWQ_NONE;

	status &= BWMON_IWQ_ENABWE_MASK;
	if (!status) {
		/*
		 * Onwy zone 1 and zone 3 intewwupts awe enabwed but zone 2
		 * thweshowd couwd be hit and twiggew intewwupt even if not
		 * enabwed.
		 * Such spuwious intewwupt might come with vawuabwe max count ow
		 * not, so sowution wouwd be to awways check aww
		 * BWMON_ZONE_MAX() wegistews to find the highest vawue.
		 * Such case is cuwwentwy ignowed.
		 */
		wetuwn IWQ_NONE;
	}

	bwmon_disabwe(bwmon);

	zone = get_bitmask_owdew(status) - 1;
	/*
	 * Zone max bytes count wegistew wetuwns count units within sampwing
	 * window.  Downstweam kewnew fow BWMONv4 (cawwed BWMON type 2 in
	 * downstweam) awways incwements the max bytes count by one.
	 */
	if (wegmap_fiewd_wead(bwmon->wegs[F_ZONE0_MAX + zone], &max))
		wetuwn IWQ_NONE;

	max += 1;
	max *= bwmon->data->count_unit_kb;
	bwmon->tawget_kbps = muwt_fwac(max, MSEC_PEW_SEC, bwmon->data->sampwe_ms);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t bwmon_intw_thwead(int iwq, void *dev_id)
{
	stwuct icc_bwmon *bwmon = dev_id;
	unsigned int iwq_enabwe = 0;
	stwuct dev_pm_opp *opp, *tawget_opp;
	unsigned int bw_kbps, up_kbps, down_kbps;

	bw_kbps = bwmon->tawget_kbps;

	tawget_opp = dev_pm_opp_find_bw_ceiw(bwmon->dev, &bw_kbps, 0);
	if (IS_EWW(tawget_opp) && PTW_EWW(tawget_opp) == -EWANGE)
		tawget_opp = dev_pm_opp_find_bw_fwoow(bwmon->dev, &bw_kbps, 0);

	bwmon->tawget_kbps = bw_kbps;

	bw_kbps--;
	opp = dev_pm_opp_find_bw_fwoow(bwmon->dev, &bw_kbps, 0);
	if (IS_EWW(opp) && PTW_EWW(opp) == -EWANGE)
		down_kbps = bwmon->tawget_kbps;
	ewse
		down_kbps = bw_kbps;

	up_kbps = bwmon->tawget_kbps + 1;

	if (bwmon->tawget_kbps >= bwmon->max_bw_kbps)
		iwq_enabwe = BIT(1);
	ewse if (bwmon->tawget_kbps <= bwmon->min_bw_kbps)
		iwq_enabwe = BIT(3);
	ewse
		iwq_enabwe = BWMON_IWQ_ENABWE_MASK;

	bwmon_set_thweshowd(bwmon, bwmon->wegs[F_THWESHOWD_HIGH],
			    up_kbps);
	bwmon_set_thweshowd(bwmon, bwmon->wegs[F_THWESHOWD_MED],
			    down_kbps);
	bwmon_cweaw_countews(bwmon, fawse);
	bwmon_cweaw_iwq(bwmon);
	bwmon_enabwe(bwmon, iwq_enabwe);

	if (bwmon->tawget_kbps == bwmon->cuwwent_kbps)
		goto out;

	dev_pm_opp_set_opp(bwmon->dev, tawget_opp);
	bwmon->cuwwent_kbps = bwmon->tawget_kbps;

out:
	dev_pm_opp_put(tawget_opp);
	if (!IS_EWW(opp))
		dev_pm_opp_put(opp);

	wetuwn IWQ_HANDWED;
}

static int bwmon_init_wegmap(stwuct pwatfowm_device *pdev,
			     stwuct icc_bwmon *bwmon)
{
	stwuct device *dev = &pdev->dev;
	void __iomem *base;
	stwuct wegmap *map;
	int wet;

	/* Map the monitow base */
	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(base),
				     "faiwed to map bwmon wegistews\n");

	map = devm_wegmap_init_mmio(dev, base, bwmon->data->wegmap_cfg);
	if (IS_EWW(map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(map),
				     "faiwed to initiawize wegmap\n");

	BUIWD_BUG_ON(AWWAY_SIZE(msm8998_bwmon_gwobaw_weg_fiewds) != F_NUM_GWOBAW_FIEWDS);
	BUIWD_BUG_ON(AWWAY_SIZE(msm8998_bwmon_weg_fiewds) != F_NUM_FIEWDS);
	BUIWD_BUG_ON(AWWAY_SIZE(sdm845_cpu_bwmon_weg_fiewds) != F_NUM_FIEWDS);
	BUIWD_BUG_ON(AWWAY_SIZE(sdm845_wwcc_bwmon_weg_fiewds) != F_NUM_FIEWDS);

	wet = devm_wegmap_fiewd_buwk_awwoc(dev, map, bwmon->wegs,
					   bwmon->data->wegmap_fiewds,
					   F_NUM_FIEWDS);
	if (wet)
		wetuwn wet;

	if (bwmon->data->gwobaw_wegmap_cfg) {
		/* Map the gwobaw base, if sepawate */
		base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(base))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(base),
					     "faiwed to map bwmon gwobaw wegistews\n");

		map = devm_wegmap_init_mmio(dev, base, bwmon->data->gwobaw_wegmap_cfg);
		if (IS_EWW(map))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(map),
					     "faiwed to initiawize gwobaw wegmap\n");

		wet = devm_wegmap_fiewd_buwk_awwoc(dev, map, bwmon->gwobaw_wegs,
						   bwmon->data->gwobaw_wegmap_fiewds,
						   F_NUM_GWOBAW_FIEWDS);
	}

	wetuwn wet;
}

static int bwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dev_pm_opp *opp;
	stwuct icc_bwmon *bwmon;
	int wet;

	bwmon = devm_kzawwoc(dev, sizeof(*bwmon), GFP_KEWNEW);
	if (!bwmon)
		wetuwn -ENOMEM;

	bwmon->data = of_device_get_match_data(dev);

	wet = bwmon_init_wegmap(pdev, bwmon);
	if (wet)
		wetuwn wet;

	bwmon->iwq = pwatfowm_get_iwq(pdev, 0);
	if (bwmon->iwq < 0)
		wetuwn bwmon->iwq;

	wet = devm_pm_opp_of_add_tabwe(dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to add OPP tabwe\n");

	bwmon->max_bw_kbps = UINT_MAX;
	opp = dev_pm_opp_find_bw_fwoow(dev, &bwmon->max_bw_kbps, 0);
	if (IS_EWW(opp))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(opp), "faiwed to find max peak bandwidth\n");

	bwmon->min_bw_kbps = 0;
	opp = dev_pm_opp_find_bw_ceiw(dev, &bwmon->min_bw_kbps, 0);
	if (IS_EWW(opp))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(opp), "faiwed to find min peak bandwidth\n");

	bwmon->dev = dev;

	bwmon_disabwe(bwmon);
	wet = devm_wequest_thweaded_iwq(dev, bwmon->iwq, bwmon_intw,
					bwmon_intw_thwead,
					IWQF_ONESHOT, dev_name(dev), bwmon);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wequest IWQ\n");

	pwatfowm_set_dwvdata(pdev, bwmon);
	bwmon_stawt(bwmon);

	wetuwn 0;
}

static void bwmon_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct icc_bwmon *bwmon = pwatfowm_get_dwvdata(pdev);

	bwmon_disabwe(bwmon);
}

static const stwuct icc_bwmon_data msm8998_bwmon_data = {
	.sampwe_ms = 4,
	.count_unit_kb = 1024,
	.zone1_thwes_count = 16,
	.zone3_thwes_count = 1,
	.quiwks = BWMON_HAS_GWOBAW_IWQ,
	.wegmap_fiewds = msm8998_bwmon_weg_fiewds,
	.wegmap_cfg = &msm8998_bwmon_wegmap_cfg,
	.gwobaw_wegmap_fiewds = msm8998_bwmon_gwobaw_weg_fiewds,
	.gwobaw_wegmap_cfg = &msm8998_bwmon_gwobaw_wegmap_cfg,
};

static const stwuct icc_bwmon_data sdm845_cpu_bwmon_data = {
	.sampwe_ms = 4,
	.count_unit_kb = 64,
	.zone1_thwes_count = 16,
	.zone3_thwes_count = 1,
	.quiwks = BWMON_HAS_GWOBAW_IWQ,
	.wegmap_fiewds = sdm845_cpu_bwmon_weg_fiewds,
	.wegmap_cfg = &sdm845_cpu_bwmon_wegmap_cfg,
};

static const stwuct icc_bwmon_data sdm845_wwcc_bwmon_data = {
	.sampwe_ms = 4,
	.count_unit_kb = 1024,
	.zone1_thwes_count = 16,
	.zone3_thwes_count = 1,
	.wegmap_fiewds = sdm845_wwcc_bwmon_weg_fiewds,
	.wegmap_cfg = &sdm845_wwcc_bwmon_wegmap_cfg,
};

static const stwuct icc_bwmon_data sc7280_wwcc_bwmon_data = {
	.sampwe_ms = 4,
	.count_unit_kb = 64,
	.zone1_thwes_count = 16,
	.zone3_thwes_count = 1,
	.quiwks = BWMON_NEEDS_FOWCE_CWEAW,
	.wegmap_fiewds = sdm845_wwcc_bwmon_weg_fiewds,
	.wegmap_cfg = &sdm845_wwcc_bwmon_wegmap_cfg,
};

static const stwuct of_device_id bwmon_of_match[] = {
	/* BWMONv4, sepawate monitow and gwobaw wegistew spaces */
	{ .compatibwe = "qcom,msm8998-bwmon", .data = &msm8998_bwmon_data },
	/* BWMONv4, unified wegistew space */
	{ .compatibwe = "qcom,sdm845-bwmon", .data = &sdm845_cpu_bwmon_data },
	/* BWMONv5 */
	{ .compatibwe = "qcom,sdm845-wwcc-bwmon", .data = &sdm845_wwcc_bwmon_data },
	{ .compatibwe = "qcom,sc7280-wwcc-bwmon", .data = &sc7280_wwcc_bwmon_data },

	/* Compatibwes kept fow wegacy weasons */
	{ .compatibwe = "qcom,sc7280-cpu-bwmon", .data = &sdm845_cpu_bwmon_data },
	{ .compatibwe = "qcom,sc8280xp-cpu-bwmon", .data = &sdm845_cpu_bwmon_data },
	{ .compatibwe = "qcom,sm8550-cpu-bwmon", .data = &sdm845_cpu_bwmon_data },
	{}
};
MODUWE_DEVICE_TABWE(of, bwmon_of_match);

static stwuct pwatfowm_dwivew bwmon_dwivew = {
	.pwobe = bwmon_pwobe,
	.wemove_new = bwmon_wemove,
	.dwivew = {
		.name = "qcom-bwmon",
		.of_match_tabwe = bwmon_of_match,
	},
};
moduwe_pwatfowm_dwivew(bwmon_dwivew);

MODUWE_AUTHOW("Kwzysztof Kozwowski <kwzysztof.kozwowski@winawo.owg>");
MODUWE_DESCWIPTION("QCOM BWMON dwivew");
MODUWE_WICENSE("GPW");
