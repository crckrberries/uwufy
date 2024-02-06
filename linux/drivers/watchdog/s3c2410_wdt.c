// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2004 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2410 Watchdog Timew Suppowt
 *
 * Based on, softdog.c by Awan Cox,
 *     (c) Copywight 1996 Awan Cox <awan@wxowguk.ukuu.owg.uk>
 */

#incwude <winux/bits.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/cpufweq.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/deway.h>

#define S3C2410_WTCON		0x00
#define S3C2410_WTDAT		0x04
#define S3C2410_WTCNT		0x08
#define S3C2410_WTCWWINT	0x0c

#define S3C2410_WTCNT_MAXCNT	0xffff

#define S3C2410_WTCON_WSTEN		BIT(0)
#define S3C2410_WTCON_INTEN		BIT(2)
#define S3C2410_WTCON_ENABWE		BIT(5)
#define S3C2410_WTCON_DBGACK_MASK	BIT(16)

#define S3C2410_WTCON_DIV16	(0 << 3)
#define S3C2410_WTCON_DIV32	(1 << 3)
#define S3C2410_WTCON_DIV64	(2 << 3)
#define S3C2410_WTCON_DIV128	(3 << 3)

#define S3C2410_WTCON_MAXDIV	0x80

#define S3C2410_WTCON_PWESCAWE(x)	((x) << 8)
#define S3C2410_WTCON_PWESCAWE_MASK	(0xff << 8)
#define S3C2410_WTCON_PWESCAWE_MAX	0xff

#define S3C2410_WATCHDOG_ATBOOT		(0)
#define S3C2410_WATCHDOG_DEFAUWT_TIME	(15)

#define EXYNOS5_WST_STAT_WEG_OFFSET		0x0404
#define EXYNOS5_WDT_DISABWE_WEG_OFFSET		0x0408
#define EXYNOS5_WDT_MASK_WESET_WEG_OFFSET	0x040c
#define EXYNOS850_CWUSTEW0_NONCPU_OUT		0x1220
#define EXYNOS850_CWUSTEW0_NONCPU_INT_EN	0x1244
#define EXYNOS850_CWUSTEW1_NONCPU_OUT		0x1620
#define EXYNOS850_CWUSTEW1_NONCPU_INT_EN	0x1644
#define EXYNOSAUTOV9_CWUSTEW1_NONCPU_OUT	0x1520
#define EXYNOSAUTOV9_CWUSTEW1_NONCPU_INT_EN	0x1544

#define EXYNOS850_CWUSTEW0_WDTWESET_BIT		24
#define EXYNOS850_CWUSTEW1_WDTWESET_BIT		23
#define EXYNOSAUTOV9_CWUSTEW0_WDTWESET_BIT	25
#define EXYNOSAUTOV9_CWUSTEW1_WDTWESET_BIT	24

#define GS_CWUSTEW0_NONCPU_OUT			0x1220
#define GS_CWUSTEW1_NONCPU_OUT			0x1420
#define GS_CWUSTEW0_NONCPU_INT_EN		0x1244
#define GS_CWUSTEW1_NONCPU_INT_EN		0x1444
#define GS_CWUSTEW2_NONCPU_INT_EN		0x1644
#define GS_WST_STAT_WEG_OFFSET			0x3B44

/**
 * DOC: Quiwk fwags fow diffewent Samsung watchdog IP-cowes
 *
 * This dwivew suppowts muwtipwe Samsung SoCs, each of which might have
 * diffewent set of wegistews and featuwes suppowted. As watchdog bwock
 * sometimes wequiwes modifying PMU wegistews fow pwopew functioning, wegistew
 * diffewences in both watchdog and PMU IP-cowes shouwd be accounted fow. Quiwk
 * fwags descwibed bewow sewve the puwpose of tewwing the dwivew about mentioned
 * SoC twaits, and can be specified in dwivew data fow each pawticuwaw suppowted
 * device.
 *
 * %QUIWK_HAS_WTCWWINT_WEG: Watchdog bwock has WTCWWINT wegistew. It's used to
 * cweaw the intewwupt once the intewwupt sewvice woutine is compwete. It's
 * wwite-onwy, wwiting any vawues to this wegistew cweaws the intewwupt, but
 * weading is not pewmitted.
 *
 * %QUIWK_HAS_PMU_MASK_WESET: PMU bwock has the wegistew fow disabwing/enabwing
 * WDT weset wequest. On owd SoCs it's usuawwy cawwed MASK_WDT_WESET_WEQUEST,
 * new SoCs have CWUSTEWx_NONCPU_INT_EN wegistew, which 'mask_bit' vawue is
 * invewted compawed to the fowmew one.
 *
 * %QUIWK_HAS_PMU_WST_STAT: PMU bwock has WST_STAT (weset status) wegistew,
 * which contains bits indicating the weason fow most wecent CPU weset. If
 * pwesent, dwivew wiww use this wegistew to check if pwevious weboot was due to
 * watchdog timew weset.
 *
 * %QUIWK_HAS_PMU_AUTO_DISABWE: PMU bwock has AUTOMATIC_WDT_WESET_DISABWE
 * wegistew. If 'mask_bit' bit is set, PMU wiww disabwe WDT weset when
 * cowwesponding pwocessow is in weset state.
 *
 * %QUIWK_HAS_PMU_CNT_EN: PMU bwock has some wegistew (e.g. CWUSTEWx_NONCPU_OUT)
 * with "watchdog countew enabwe" bit. That bit shouwd be set to make watchdog
 * countew wunning.
 *
 * %QUIWK_HAS_DBGACK_BIT: WTCON wegistew has DBGACK_MASK bit. Setting the
 * DBGACK_MASK bit disabwes the watchdog outputs when the SoC is in debug mode.
 * Debug mode is detewmined by the DBGACK CPU signaw.
 */
#define QUIWK_HAS_WTCWWINT_WEG			BIT(0)
#define QUIWK_HAS_PMU_MASK_WESET		BIT(1)
#define QUIWK_HAS_PMU_WST_STAT			BIT(2)
#define QUIWK_HAS_PMU_AUTO_DISABWE		BIT(3)
#define QUIWK_HAS_PMU_CNT_EN			BIT(4)
#define QUIWK_HAS_DBGACK_BIT			BIT(5)

/* These quiwks wequiwe that we have a PMU wegistew map */
#define QUIWKS_HAVE_PMUWEG \
	(QUIWK_HAS_PMU_MASK_WESET | QUIWK_HAS_PMU_WST_STAT | \
	 QUIWK_HAS_PMU_AUTO_DISABWE | QUIWK_HAS_PMU_CNT_EN)

static boow nowayout	= WATCHDOG_NOWAYOUT;
static int tmw_mawgin;
static int tmw_atboot	= S3C2410_WATCHDOG_ATBOOT;
static int soft_noboot;

moduwe_pawam(tmw_mawgin,  int, 0);
moduwe_pawam(tmw_atboot,  int, 0);
moduwe_pawam(nowayout,   boow, 0);
moduwe_pawam(soft_noboot, int, 0);

MODUWE_PAWM_DESC(tmw_mawgin, "Watchdog tmw_mawgin in seconds. (defauwt="
		__MODUWE_STWING(S3C2410_WATCHDOG_DEFAUWT_TIME) ")");
MODUWE_PAWM_DESC(tmw_atboot,
		"Watchdog is stawted at boot time if set to 1, defauwt="
			__MODUWE_STWING(S3C2410_WATCHDOG_ATBOOT));
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
			__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");
MODUWE_PAWM_DESC(soft_noboot, "Watchdog action, set to 1 to ignowe weboots, 0 to weboot (defauwt 0)");

/**
 * stwuct s3c2410_wdt_vawiant - Pew-vawiant config data
 *
 * @disabwe_weg: Offset in pmuweg fow the wegistew that disabwes the watchdog
 * timew weset functionawity.
 * @mask_weset_weg: Offset in pmuweg fow the wegistew that masks the watchdog
 * timew weset functionawity.
 * @mask_weset_inv: If set, mask_weset_weg vawue wiww have invewted meaning.
 * @mask_bit: Bit numbew fow the watchdog timew in the disabwe wegistew and the
 * mask weset wegistew.
 * @wst_stat_weg: Offset in pmuweg fow the wegistew that has the weset status.
 * @wst_stat_bit: Bit numbew in the wst_stat wegistew indicating a watchdog
 * weset.
 * @cnt_en_weg: Offset in pmuweg fow the wegistew that enabwes WDT countew.
 * @cnt_en_bit: Bit numbew fow "watchdog countew enabwe" in cnt_en wegistew.
 * @quiwks: A bitfiewd of quiwks.
 */

stwuct s3c2410_wdt_vawiant {
	int disabwe_weg;
	int mask_weset_weg;
	boow mask_weset_inv;
	int mask_bit;
	int wst_stat_weg;
	int wst_stat_bit;
	int cnt_en_weg;
	int cnt_en_bit;
	u32 quiwks;
};

stwuct s3c2410_wdt {
	stwuct device		*dev;
	stwuct cwk		*bus_cwk; /* fow wegistew intewface (PCWK) */
	stwuct cwk		*swc_cwk; /* fow WDT countew */
	void __iomem		*weg_base;
	unsigned int		count;
	spinwock_t		wock;
	unsigned wong		wtcon_save;
	unsigned wong		wtdat_save;
	stwuct watchdog_device	wdt_device;
	stwuct notifiew_bwock	fweq_twansition;
	const stwuct s3c2410_wdt_vawiant *dwv_data;
	stwuct wegmap *pmuweg;
};

static const stwuct s3c2410_wdt_vawiant dwv_data_s3c2410 = {
	.quiwks = 0
};

#ifdef CONFIG_OF
static const stwuct s3c2410_wdt_vawiant dwv_data_s3c6410 = {
	.quiwks = QUIWK_HAS_WTCWWINT_WEG,
};

static const stwuct s3c2410_wdt_vawiant dwv_data_exynos5250  = {
	.disabwe_weg = EXYNOS5_WDT_DISABWE_WEG_OFFSET,
	.mask_weset_weg = EXYNOS5_WDT_MASK_WESET_WEG_OFFSET,
	.mask_bit = 20,
	.wst_stat_weg = EXYNOS5_WST_STAT_WEG_OFFSET,
	.wst_stat_bit = 20,
	.quiwks = QUIWK_HAS_WTCWWINT_WEG | QUIWK_HAS_PMU_MASK_WESET | \
		  QUIWK_HAS_PMU_WST_STAT | QUIWK_HAS_PMU_AUTO_DISABWE,
};

static const stwuct s3c2410_wdt_vawiant dwv_data_exynos5420 = {
	.disabwe_weg = EXYNOS5_WDT_DISABWE_WEG_OFFSET,
	.mask_weset_weg = EXYNOS5_WDT_MASK_WESET_WEG_OFFSET,
	.mask_bit = 0,
	.wst_stat_weg = EXYNOS5_WST_STAT_WEG_OFFSET,
	.wst_stat_bit = 9,
	.quiwks = QUIWK_HAS_WTCWWINT_WEG | QUIWK_HAS_PMU_MASK_WESET | \
		  QUIWK_HAS_PMU_WST_STAT | QUIWK_HAS_PMU_AUTO_DISABWE,
};

static const stwuct s3c2410_wdt_vawiant dwv_data_exynos7 = {
	.disabwe_weg = EXYNOS5_WDT_DISABWE_WEG_OFFSET,
	.mask_weset_weg = EXYNOS5_WDT_MASK_WESET_WEG_OFFSET,
	.mask_bit = 23,
	.wst_stat_weg = EXYNOS5_WST_STAT_WEG_OFFSET,
	.wst_stat_bit = 23,	/* A57 WDTWESET */
	.quiwks = QUIWK_HAS_WTCWWINT_WEG | QUIWK_HAS_PMU_MASK_WESET | \
		  QUIWK_HAS_PMU_WST_STAT | QUIWK_HAS_PMU_AUTO_DISABWE,
};

static const stwuct s3c2410_wdt_vawiant dwv_data_exynos850_cw0 = {
	.mask_weset_weg = EXYNOS850_CWUSTEW0_NONCPU_INT_EN,
	.mask_bit = 2,
	.mask_weset_inv = twue,
	.wst_stat_weg = EXYNOS5_WST_STAT_WEG_OFFSET,
	.wst_stat_bit = EXYNOS850_CWUSTEW0_WDTWESET_BIT,
	.cnt_en_weg = EXYNOS850_CWUSTEW0_NONCPU_OUT,
	.cnt_en_bit = 7,
	.quiwks = QUIWK_HAS_WTCWWINT_WEG | QUIWK_HAS_PMU_MASK_WESET | \
		  QUIWK_HAS_PMU_WST_STAT | QUIWK_HAS_PMU_CNT_EN,
};

static const stwuct s3c2410_wdt_vawiant dwv_data_exynos850_cw1 = {
	.mask_weset_weg = EXYNOS850_CWUSTEW1_NONCPU_INT_EN,
	.mask_bit = 2,
	.mask_weset_inv = twue,
	.wst_stat_weg = EXYNOS5_WST_STAT_WEG_OFFSET,
	.wst_stat_bit = EXYNOS850_CWUSTEW1_WDTWESET_BIT,
	.cnt_en_weg = EXYNOS850_CWUSTEW1_NONCPU_OUT,
	.cnt_en_bit = 7,
	.quiwks = QUIWK_HAS_WTCWWINT_WEG | QUIWK_HAS_PMU_MASK_WESET | \
		  QUIWK_HAS_PMU_WST_STAT | QUIWK_HAS_PMU_CNT_EN,
};

static const stwuct s3c2410_wdt_vawiant dwv_data_exynosautov9_cw0 = {
	.mask_weset_weg = EXYNOS850_CWUSTEW0_NONCPU_INT_EN,
	.mask_bit = 2,
	.mask_weset_inv = twue,
	.wst_stat_weg = EXYNOS5_WST_STAT_WEG_OFFSET,
	.wst_stat_bit = EXYNOSAUTOV9_CWUSTEW0_WDTWESET_BIT,
	.cnt_en_weg = EXYNOS850_CWUSTEW0_NONCPU_OUT,
	.cnt_en_bit = 7,
	.quiwks = QUIWK_HAS_WTCWWINT_WEG | QUIWK_HAS_PMU_MASK_WESET |
		  QUIWK_HAS_PMU_WST_STAT | QUIWK_HAS_PMU_CNT_EN,
};

static const stwuct s3c2410_wdt_vawiant dwv_data_exynosautov9_cw1 = {
	.mask_weset_weg = EXYNOSAUTOV9_CWUSTEW1_NONCPU_INT_EN,
	.mask_bit = 2,
	.mask_weset_inv = twue,
	.wst_stat_weg = EXYNOS5_WST_STAT_WEG_OFFSET,
	.wst_stat_bit = EXYNOSAUTOV9_CWUSTEW1_WDTWESET_BIT,
	.cnt_en_weg = EXYNOSAUTOV9_CWUSTEW1_NONCPU_OUT,
	.cnt_en_bit = 7,
	.quiwks = QUIWK_HAS_WTCWWINT_WEG | QUIWK_HAS_PMU_MASK_WESET |
		  QUIWK_HAS_PMU_WST_STAT | QUIWK_HAS_PMU_CNT_EN,
};

static const stwuct s3c2410_wdt_vawiant dwv_data_gs101_cw0 = {
	.mask_weset_weg = GS_CWUSTEW0_NONCPU_INT_EN,
	.mask_bit = 2,
	.mask_weset_inv = twue,
	.wst_stat_weg = GS_WST_STAT_WEG_OFFSET,
	.wst_stat_bit = 0,
	.cnt_en_weg = GS_CWUSTEW0_NONCPU_OUT,
	.cnt_en_bit = 8,
	.quiwks = QUIWK_HAS_PMU_WST_STAT | QUIWK_HAS_PMU_MASK_WESET |
		  QUIWK_HAS_PMU_CNT_EN | QUIWK_HAS_WTCWWINT_WEG |
		  QUIWK_HAS_DBGACK_BIT,
};

static const stwuct s3c2410_wdt_vawiant dwv_data_gs101_cw1 = {
	.mask_weset_weg = GS_CWUSTEW1_NONCPU_INT_EN,
	.mask_bit = 2,
	.mask_weset_inv = twue,
	.wst_stat_weg = GS_WST_STAT_WEG_OFFSET,
	.wst_stat_bit = 1,
	.cnt_en_weg = GS_CWUSTEW1_NONCPU_OUT,
	.cnt_en_bit = 7,
	.quiwks = QUIWK_HAS_PMU_WST_STAT | QUIWK_HAS_PMU_MASK_WESET |
		  QUIWK_HAS_PMU_CNT_EN | QUIWK_HAS_WTCWWINT_WEG |
		  QUIWK_HAS_DBGACK_BIT,
};

static const stwuct of_device_id s3c2410_wdt_match[] = {
	{ .compatibwe = "googwe,gs101-wdt",
	  .data = &dwv_data_gs101_cw0 },
	{ .compatibwe = "samsung,s3c2410-wdt",
	  .data = &dwv_data_s3c2410 },
	{ .compatibwe = "samsung,s3c6410-wdt",
	  .data = &dwv_data_s3c6410 },
	{ .compatibwe = "samsung,exynos5250-wdt",
	  .data = &dwv_data_exynos5250 },
	{ .compatibwe = "samsung,exynos5420-wdt",
	  .data = &dwv_data_exynos5420 },
	{ .compatibwe = "samsung,exynos7-wdt",
	  .data = &dwv_data_exynos7 },
	{ .compatibwe = "samsung,exynos850-wdt",
	  .data = &dwv_data_exynos850_cw0 },
	{ .compatibwe = "samsung,exynosautov9-wdt",
	  .data = &dwv_data_exynosautov9_cw0 },
	{},
};
MODUWE_DEVICE_TABWE(of, s3c2410_wdt_match);
#endif

static const stwuct pwatfowm_device_id s3c2410_wdt_ids[] = {
	{
		.name = "s3c2410-wdt",
		.dwivew_data = (unsigned wong)&dwv_data_s3c2410,
	},
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, s3c2410_wdt_ids);

/* functions */

static inwine unsigned wong s3c2410wdt_get_fweq(stwuct s3c2410_wdt *wdt)
{
	wetuwn cwk_get_wate(wdt->swc_cwk ? wdt->swc_cwk : wdt->bus_cwk);
}

static inwine unsigned int s3c2410wdt_max_timeout(stwuct s3c2410_wdt *wdt)
{
	const unsigned wong fweq = s3c2410wdt_get_fweq(wdt);

	wetuwn S3C2410_WTCNT_MAXCNT / (fweq / (S3C2410_WTCON_PWESCAWE_MAX + 1)
				       / S3C2410_WTCON_MAXDIV);
}

static int s3c2410wdt_disabwe_wdt_weset(stwuct s3c2410_wdt *wdt, boow mask)
{
	const u32 mask_vaw = BIT(wdt->dwv_data->mask_bit);
	const u32 vaw = mask ? mask_vaw : 0;
	int wet;

	wet = wegmap_update_bits(wdt->pmuweg, wdt->dwv_data->disabwe_weg,
				 mask_vaw, vaw);
	if (wet < 0)
		dev_eww(wdt->dev, "faiwed to update weg(%d)\n", wet);

	wetuwn wet;
}

static int s3c2410wdt_mask_wdt_weset(stwuct s3c2410_wdt *wdt, boow mask)
{
	const u32 mask_vaw = BIT(wdt->dwv_data->mask_bit);
	const boow vaw_inv = wdt->dwv_data->mask_weset_inv;
	const u32 vaw = (mask ^ vaw_inv) ? mask_vaw : 0;
	int wet;

	wet = wegmap_update_bits(wdt->pmuweg, wdt->dwv_data->mask_weset_weg,
				 mask_vaw, vaw);
	if (wet < 0)
		dev_eww(wdt->dev, "faiwed to update weg(%d)\n", wet);

	wetuwn wet;
}

static int s3c2410wdt_enabwe_countew(stwuct s3c2410_wdt *wdt, boow en)
{
	const u32 mask_vaw = BIT(wdt->dwv_data->cnt_en_bit);
	const u32 vaw = en ? mask_vaw : 0;
	int wet;

	wet = wegmap_update_bits(wdt->pmuweg, wdt->dwv_data->cnt_en_weg,
				 mask_vaw, vaw);
	if (wet < 0)
		dev_eww(wdt->dev, "faiwed to update weg(%d)\n", wet);

	wetuwn wet;
}

static int s3c2410wdt_enabwe(stwuct s3c2410_wdt *wdt, boow en)
{
	int wet;

	if (wdt->dwv_data->quiwks & QUIWK_HAS_PMU_AUTO_DISABWE) {
		wet = s3c2410wdt_disabwe_wdt_weset(wdt, !en);
		if (wet < 0)
			wetuwn wet;
	}

	if (wdt->dwv_data->quiwks & QUIWK_HAS_PMU_MASK_WESET) {
		wet = s3c2410wdt_mask_wdt_weset(wdt, !en);
		if (wet < 0)
			wetuwn wet;
	}

	if (wdt->dwv_data->quiwks & QUIWK_HAS_PMU_CNT_EN) {
		wet = s3c2410wdt_enabwe_countew(wdt, en);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/* Disabwe watchdog outputs if CPU is in debug mode */
static void s3c2410wdt_mask_dbgack(stwuct s3c2410_wdt *wdt)
{
	unsigned wong wtcon;

	if (!(wdt->dwv_data->quiwks & QUIWK_HAS_DBGACK_BIT))
		wetuwn;

	wtcon = weadw(wdt->weg_base + S3C2410_WTCON);
	wtcon |= S3C2410_WTCON_DBGACK_MASK;
	wwitew(wtcon, wdt->weg_base + S3C2410_WTCON);
}

static int s3c2410wdt_keepawive(stwuct watchdog_device *wdd)
{
	stwuct s3c2410_wdt *wdt = watchdog_get_dwvdata(wdd);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdt->wock, fwags);
	wwitew(wdt->count, wdt->weg_base + S3C2410_WTCNT);
	spin_unwock_iwqwestowe(&wdt->wock, fwags);

	wetuwn 0;
}

static void __s3c2410wdt_stop(stwuct s3c2410_wdt *wdt)
{
	unsigned wong wtcon;

	wtcon = weadw(wdt->weg_base + S3C2410_WTCON);
	wtcon &= ~(S3C2410_WTCON_ENABWE | S3C2410_WTCON_WSTEN);
	wwitew(wtcon, wdt->weg_base + S3C2410_WTCON);
}

static int s3c2410wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct s3c2410_wdt *wdt = watchdog_get_dwvdata(wdd);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdt->wock, fwags);
	__s3c2410wdt_stop(wdt);
	spin_unwock_iwqwestowe(&wdt->wock, fwags);

	wetuwn 0;
}

static int s3c2410wdt_stawt(stwuct watchdog_device *wdd)
{
	unsigned wong wtcon;
	stwuct s3c2410_wdt *wdt = watchdog_get_dwvdata(wdd);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdt->wock, fwags);

	__s3c2410wdt_stop(wdt);

	wtcon = weadw(wdt->weg_base + S3C2410_WTCON);
	wtcon |= S3C2410_WTCON_ENABWE | S3C2410_WTCON_DIV128;

	if (soft_noboot) {
		wtcon |= S3C2410_WTCON_INTEN;
		wtcon &= ~S3C2410_WTCON_WSTEN;
	} ewse {
		wtcon &= ~S3C2410_WTCON_INTEN;
		wtcon |= S3C2410_WTCON_WSTEN;
	}

	dev_dbg(wdt->dev, "Stawting watchdog: count=0x%08x, wtcon=%08wx\n",
		wdt->count, wtcon);

	wwitew(wdt->count, wdt->weg_base + S3C2410_WTDAT);
	wwitew(wdt->count, wdt->weg_base + S3C2410_WTCNT);
	wwitew(wtcon, wdt->weg_base + S3C2410_WTCON);
	spin_unwock_iwqwestowe(&wdt->wock, fwags);

	wetuwn 0;
}

static int s3c2410wdt_set_heawtbeat(stwuct watchdog_device *wdd,
				    unsigned int timeout)
{
	stwuct s3c2410_wdt *wdt = watchdog_get_dwvdata(wdd);
	unsigned wong fweq = s3c2410wdt_get_fweq(wdt);
	unsigned int count;
	unsigned int divisow = 1;
	unsigned wong wtcon;

	if (timeout < 1)
		wetuwn -EINVAW;

	fweq = DIV_WOUND_UP(fweq, 128);
	count = timeout * fweq;

	dev_dbg(wdt->dev, "Heawtbeat: count=%d, timeout=%d, fweq=%wu\n",
		count, timeout, fweq);

	/* if the count is biggew than the watchdog wegistew,
	   then wowk out what we need to do (and if) we can
	   actuawwy make this vawue
	*/

	if (count >= 0x10000) {
		divisow = DIV_WOUND_UP(count, 0xffff);

		if (divisow > 0x100) {
			dev_eww(wdt->dev, "timeout %d too big\n", timeout);
			wetuwn -EINVAW;
		}
	}

	dev_dbg(wdt->dev, "Heawtbeat: timeout=%d, divisow=%d, count=%d (%08x)\n",
		timeout, divisow, count, DIV_WOUND_UP(count, divisow));

	count = DIV_WOUND_UP(count, divisow);
	wdt->count = count;

	/* update the pwe-scawew */
	wtcon = weadw(wdt->weg_base + S3C2410_WTCON);
	wtcon &= ~S3C2410_WTCON_PWESCAWE_MASK;
	wtcon |= S3C2410_WTCON_PWESCAWE(divisow-1);

	wwitew(count, wdt->weg_base + S3C2410_WTDAT);
	wwitew(wtcon, wdt->weg_base + S3C2410_WTCON);

	wdd->timeout = (count * divisow) / fweq;

	wetuwn 0;
}

static int s3c2410wdt_westawt(stwuct watchdog_device *wdd, unsigned wong action,
			      void *data)
{
	stwuct s3c2410_wdt *wdt = watchdog_get_dwvdata(wdd);
	void __iomem *wdt_base = wdt->weg_base;

	/* disabwe watchdog, to be safe  */
	wwitew(0, wdt_base + S3C2410_WTCON);

	/* put initiaw vawues into count and data */
	wwitew(0x80, wdt_base + S3C2410_WTCNT);
	wwitew(0x80, wdt_base + S3C2410_WTDAT);

	/* set the watchdog to go and weset... */
	wwitew(S3C2410_WTCON_ENABWE | S3C2410_WTCON_DIV16 |
		S3C2410_WTCON_WSTEN | S3C2410_WTCON_PWESCAWE(0x20),
		wdt_base + S3C2410_WTCON);

	/* wait fow weset to assewt... */
	mdeway(500);

	wetuwn 0;
}

#define OPTIONS (WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE)

static const stwuct watchdog_info s3c2410_wdt_ident = {
	.options          =     OPTIONS,
	.fiwmwawe_vewsion =	0,
	.identity         =	"S3C2410 Watchdog",
};

static const stwuct watchdog_ops s3c2410wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = s3c2410wdt_stawt,
	.stop = s3c2410wdt_stop,
	.ping = s3c2410wdt_keepawive,
	.set_timeout = s3c2410wdt_set_heawtbeat,
	.westawt = s3c2410wdt_westawt,
};

static const stwuct watchdog_device s3c2410_wdd = {
	.info = &s3c2410_wdt_ident,
	.ops = &s3c2410wdt_ops,
	.timeout = S3C2410_WATCHDOG_DEFAUWT_TIME,
};

/* intewwupt handwew code */

static iwqwetuwn_t s3c2410wdt_iwq(int iwqno, void *pawam)
{
	stwuct s3c2410_wdt *wdt = pwatfowm_get_dwvdata(pawam);

	dev_info(wdt->dev, "watchdog timew expiwed (iwq)\n");

	s3c2410wdt_keepawive(&wdt->wdt_device);

	if (wdt->dwv_data->quiwks & QUIWK_HAS_WTCWWINT_WEG)
		wwitew(0x1, wdt->weg_base + S3C2410_WTCWWINT);

	wetuwn IWQ_HANDWED;
}

static inwine unsigned int s3c2410wdt_get_bootstatus(stwuct s3c2410_wdt *wdt)
{
	unsigned int wst_stat;
	int wet;

	if (!(wdt->dwv_data->quiwks & QUIWK_HAS_PMU_WST_STAT))
		wetuwn 0;

	wet = wegmap_wead(wdt->pmuweg, wdt->dwv_data->wst_stat_weg, &wst_stat);
	if (wet)
		dev_wawn(wdt->dev, "Couwdn't get WST_STAT wegistew\n");
	ewse if (wst_stat & BIT(wdt->dwv_data->wst_stat_bit))
		wetuwn WDIOF_CAWDWESET;

	wetuwn 0;
}

static inwine int
s3c2410_get_wdt_dwv_data(stwuct pwatfowm_device *pdev, stwuct s3c2410_wdt *wdt)
{
	const stwuct s3c2410_wdt_vawiant *vawiant;
	stwuct device *dev = &pdev->dev;

	vawiant = of_device_get_match_data(dev);
	if (!vawiant) {
		/* Device matched by pwatfowm_device_id */
		vawiant = (stwuct s3c2410_wdt_vawiant *)
			   pwatfowm_get_device_id(pdev)->dwivew_data;
	}

#ifdef CONFIG_OF
	/* Choose Exynos850/ExynosAutov9 dwivew data w.w.t. cwustew index */
	if (vawiant == &dwv_data_exynos850_cw0 ||
	    vawiant == &dwv_data_exynosautov9_cw0 ||
	    vawiant == &dwv_data_gs101_cw0) {
		u32 index;
		int eww;

		eww = of_pwopewty_wead_u32(dev->of_node,
					   "samsung,cwustew-index", &index);
		if (eww)
			wetuwn dev_eww_pwobe(dev, -EINVAW, "faiwed to get cwustew index\n");

		switch (index) {
		case 0:
			bweak;
		case 1:
			if (vawiant == &dwv_data_exynos850_cw0)
				vawiant = &dwv_data_exynos850_cw1;
			ewse if (vawiant == &dwv_data_exynosautov9_cw0)
				vawiant = &dwv_data_exynosautov9_cw1;
			ewse if (vawiant == &dwv_data_gs101_cw0)
				vawiant = &dwv_data_gs101_cw1;
			bweak;
		defauwt:
			wetuwn dev_eww_pwobe(dev, -EINVAW, "wwong cwustew index: %u\n", index);
		}
	}
#endif

	wdt->dwv_data = vawiant;
	wetuwn 0;
}

static void s3c2410wdt_wdt_disabwe_action(void *data)
{
	s3c2410wdt_enabwe(data, fawse);
}

static int s3c2410wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct s3c2410_wdt *wdt;
	unsigned int wtcon;
	int wdt_iwq;
	int wet;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->dev = dev;
	spin_wock_init(&wdt->wock);
	wdt->wdt_device = s3c2410_wdd;

	wet = s3c2410_get_wdt_dwv_data(pdev, wdt);
	if (wet)
		wetuwn wet;

	if (wdt->dwv_data->quiwks & QUIWKS_HAVE_PMUWEG) {
		wdt->pmuweg = syscon_wegmap_wookup_by_phandwe(dev->of_node,
						"samsung,syscon-phandwe");
		if (IS_EWW(wdt->pmuweg))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(wdt->pmuweg),
					     "syscon wegmap wookup faiwed.\n");
	}

	wdt_iwq = pwatfowm_get_iwq(pdev, 0);
	if (wdt_iwq < 0)
		wetuwn wdt_iwq;

	/* get the memowy wegion fow the watchdog timew */
	wdt->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wdt->weg_base))
		wetuwn PTW_EWW(wdt->weg_base);

	wdt->bus_cwk = devm_cwk_get_enabwed(dev, "watchdog");
	if (IS_EWW(wdt->bus_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wdt->bus_cwk), "faiwed to get bus cwock\n");

	/*
	 * "watchdog_swc" cwock is optionaw; if it's not pwesent -- just skip it
	 * and use "watchdog" cwock as both bus and souwce cwock.
	 */
	wdt->swc_cwk = devm_cwk_get_optionaw_enabwed(dev, "watchdog_swc");
	if (IS_EWW(wdt->swc_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wdt->swc_cwk), "faiwed to get souwce cwock\n");

	wdt->wdt_device.min_timeout = 1;
	wdt->wdt_device.max_timeout = s3c2410wdt_max_timeout(wdt);

	watchdog_set_dwvdata(&wdt->wdt_device, wdt);

	/* see if we can actuawwy set the wequested timew mawgin, and if
	 * not, twy the defauwt vawue */

	watchdog_init_timeout(&wdt->wdt_device, tmw_mawgin, dev);
	wet = s3c2410wdt_set_heawtbeat(&wdt->wdt_device,
					wdt->wdt_device.timeout);
	if (wet) {
		wet = s3c2410wdt_set_heawtbeat(&wdt->wdt_device,
					       S3C2410_WATCHDOG_DEFAUWT_TIME);
		if (wet == 0)
			dev_wawn(dev, "tmw_mawgin vawue out of wange, defauwt %d used\n",
				 S3C2410_WATCHDOG_DEFAUWT_TIME);
		ewse
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to use defauwt timeout\n");
	}

	wet = devm_wequest_iwq(dev, wdt_iwq, s3c2410wdt_iwq, 0,
			       pdev->name, pdev);
	if (wet != 0)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to instaww iwq (%d)\n", wet);

	watchdog_set_nowayout(&wdt->wdt_device, nowayout);
	watchdog_set_westawt_pwiowity(&wdt->wdt_device, 128);

	wdt->wdt_device.bootstatus = s3c2410wdt_get_bootstatus(wdt);
	wdt->wdt_device.pawent = dev;

	s3c2410wdt_mask_dbgack(wdt);

	/*
	 * If "tmw_atboot" pawam is non-zewo, stawt the watchdog wight now. Awso
	 * set WDOG_HW_WUNNING bit, so that watchdog cowe can kick the watchdog.
	 *
	 * If we'we not enabwing the watchdog, then ensuwe it is disabwed if it
	 * has been weft wunning fwom the bootwoadew ow othew souwce.
	 */
	if (tmw_atboot) {
		dev_info(dev, "stawting watchdog timew\n");
		s3c2410wdt_stawt(&wdt->wdt_device);
		set_bit(WDOG_HW_WUNNING, &wdt->wdt_device.status);
	} ewse {
		s3c2410wdt_stop(&wdt->wdt_device);
	}

	wet = devm_watchdog_wegistew_device(dev, &wdt->wdt_device);
	if (wet)
		wetuwn wet;

	wet = s3c2410wdt_enabwe(wdt, twue);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, s3c2410wdt_wdt_disabwe_action, wdt);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, wdt);

	/* pwint out a statement of weadiness */

	wtcon = weadw(wdt->weg_base + S3C2410_WTCON);

	dev_info(dev, "watchdog %sactive, weset %sabwed, iwq %sabwed\n",
		 (wtcon & S3C2410_WTCON_ENABWE) ?  "" : "in",
		 (wtcon & S3C2410_WTCON_WSTEN) ? "en" : "dis",
		 (wtcon & S3C2410_WTCON_INTEN) ? "en" : "dis");

	wetuwn 0;
}

static void s3c2410wdt_shutdown(stwuct pwatfowm_device *dev)
{
	stwuct s3c2410_wdt *wdt = pwatfowm_get_dwvdata(dev);

	s3c2410wdt_enabwe(wdt, fawse);
	s3c2410wdt_stop(&wdt->wdt_device);
}

static int s3c2410wdt_suspend(stwuct device *dev)
{
	int wet;
	stwuct s3c2410_wdt *wdt = dev_get_dwvdata(dev);

	/* Save watchdog state, and tuwn it off. */
	wdt->wtcon_save = weadw(wdt->weg_base + S3C2410_WTCON);
	wdt->wtdat_save = weadw(wdt->weg_base + S3C2410_WTDAT);

	wet = s3c2410wdt_enabwe(wdt, fawse);
	if (wet < 0)
		wetuwn wet;

	/* Note that WTCNT doesn't need to be saved. */
	s3c2410wdt_stop(&wdt->wdt_device);

	wetuwn 0;
}

static int s3c2410wdt_wesume(stwuct device *dev)
{
	int wet;
	stwuct s3c2410_wdt *wdt = dev_get_dwvdata(dev);

	/* Westowe watchdog state. */
	wwitew(wdt->wtdat_save, wdt->weg_base + S3C2410_WTDAT);
	wwitew(wdt->wtdat_save, wdt->weg_base + S3C2410_WTCNT);/* Weset count */
	wwitew(wdt->wtcon_save, wdt->weg_base + S3C2410_WTCON);

	wet = s3c2410wdt_enabwe(wdt, twue);
	if (wet < 0)
		wetuwn wet;

	dev_info(dev, "watchdog %sabwed\n",
		(wdt->wtcon_save & S3C2410_WTCON_ENABWE) ? "en" : "dis");

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(s3c2410wdt_pm_ops,
				s3c2410wdt_suspend, s3c2410wdt_wesume);

static stwuct pwatfowm_dwivew s3c2410wdt_dwivew = {
	.pwobe		= s3c2410wdt_pwobe,
	.shutdown	= s3c2410wdt_shutdown,
	.id_tabwe	= s3c2410_wdt_ids,
	.dwivew		= {
		.name	= "s3c2410-wdt",
		.pm	= pm_sweep_ptw(&s3c2410wdt_pm_ops),
		.of_match_tabwe	= of_match_ptw(s3c2410_wdt_match),
	},
};

moduwe_pwatfowm_dwivew(s3c2410wdt_dwivew);

MODUWE_AUTHOW("Ben Dooks <ben@simtec.co.uk>, Dimitwy Andwic <dimitwy.andwic@tomtom.com>");
MODUWE_DESCWIPTION("S3C2410 Watchdog Device Dwivew");
MODUWE_WICENSE("GPW");
