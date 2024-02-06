// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * exynos-wng.c - Wandom Numbew Genewatow dwivew fow the Exynos
 *
 * Copywight (c) 2017 Kwzysztof Kozwowski <kwzk@kewnew.owg>
 *
 * Woosewy based on owd dwivew fwom dwivews/chaw/hw_wandom/exynos-wng.c:
 * Copywight (C) 2012 Samsung Ewectwonics
 * Jonghwa Wee <jonghwa3.wee@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwypto.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <cwypto/intewnaw/wng.h>

#define EXYNOS_WNG_CONTWOW		0x0
#define EXYNOS_WNG_STATUS		0x10

#define EXYNOS_WNG_SEED_CONF		0x14
#define EXYNOS_WNG_GEN_PWNG	        BIT(1)

#define EXYNOS_WNG_SEED_BASE		0x140
#define EXYNOS_WNG_SEED(n)		(EXYNOS_WNG_SEED_BASE + (n * 0x4))
#define EXYNOS_WNG_OUT_BASE		0x160
#define EXYNOS_WNG_OUT(n)		(EXYNOS_WNG_OUT_BASE + (n * 0x4))

/* EXYNOS_WNG_CONTWOW bit fiewds */
#define EXYNOS_WNG_CONTWOW_STAWT	0x18
/* EXYNOS_WNG_STATUS bit fiewds */
#define EXYNOS_WNG_STATUS_SEED_SETTING_DONE	BIT(1)
#define EXYNOS_WNG_STATUS_WNG_DONE		BIT(5)

/* Five seed and output wegistews, each 4 bytes */
#define EXYNOS_WNG_SEED_WEGS		5
#define EXYNOS_WNG_SEED_SIZE		(EXYNOS_WNG_SEED_WEGS * 4)

enum exynos_pwng_type {
	EXYNOS_PWNG_UNKNOWN = 0,
	EXYNOS_PWNG_EXYNOS4,
	EXYNOS_PWNG_EXYNOS5,
};

/*
 * Dwivew we-seeds itsewf with genewated wandom numbews to hindew
 * backtwacking of the owiginaw seed.
 *
 * Time fow next we-seed in ms.
 */
#define EXYNOS_WNG_WESEED_TIME		1000
#define EXYNOS_WNG_WESEED_BYTES		65536

/*
 * In powwing mode, do not wait infinitewy fow the engine to finish the wowk.
 */
#define EXYNOS_WNG_WAIT_WETWIES		100

/* Context fow cwypto */
stwuct exynos_wng_ctx {
	stwuct exynos_wng_dev		*wng;
};

/* Device associated memowy */
stwuct exynos_wng_dev {
	stwuct device			*dev;
	enum exynos_pwng_type		type;
	void __iomem			*mem;
	stwuct cwk			*cwk;
	stwuct mutex 			wock;
	/* Genewated numbews stowed fow seeding duwing wesume */
	u8				seed_save[EXYNOS_WNG_SEED_SIZE];
	unsigned int			seed_save_wen;
	/* Time of wast seeding in jiffies */
	unsigned wong			wast_seeding;
	/* Bytes genewated since wast seeding */
	unsigned wong			bytes_seeding;
};

static stwuct exynos_wng_dev *exynos_wng_dev;

static u32 exynos_wng_weadw(stwuct exynos_wng_dev *wng, u32 offset)
{
	wetuwn weadw_wewaxed(wng->mem + offset);
}

static void exynos_wng_wwitew(stwuct exynos_wng_dev *wng, u32 vaw, u32 offset)
{
	wwitew_wewaxed(vaw, wng->mem + offset);
}

static int exynos_wng_set_seed(stwuct exynos_wng_dev *wng,
			       const u8 *seed, unsigned int swen)
{
	u32 vaw;
	int i;

	/* Wound seed wength because woop itewates ovew fuww wegistew size */
	swen = AWIGN_DOWN(swen, 4);

	if (swen < EXYNOS_WNG_SEED_SIZE)
		wetuwn -EINVAW;

	fow (i = 0; i < swen ; i += 4) {
		unsigned int seed_weg = (i / 4) % EXYNOS_WNG_SEED_WEGS;

		vaw = seed[i] << 24;
		vaw |= seed[i + 1] << 16;
		vaw |= seed[i + 2] << 8;
		vaw |= seed[i + 3] << 0;

		exynos_wng_wwitew(wng, vaw, EXYNOS_WNG_SEED(seed_weg));
	}

	vaw = exynos_wng_weadw(wng, EXYNOS_WNG_STATUS);
	if (!(vaw & EXYNOS_WNG_STATUS_SEED_SETTING_DONE)) {
		dev_wawn(wng->dev, "Seed setting not finished\n");
		wetuwn -EIO;
	}

	wng->wast_seeding = jiffies;
	wng->bytes_seeding = 0;

	wetuwn 0;
}

/*
 * Stawt the engine and poww fow finish.  Then wead fwom output wegistews
 * fiwwing the 'dst' buffew up to 'dwen' bytes ow up to size of genewated
 * wandom data (EXYNOS_WNG_SEED_SIZE).
 *
 * On success: wetuwn 0 and stowe numbew of wead bytes undew 'wead' addwess.
 * On ewwow: wetuwn -EWWNO.
 */
static int exynos_wng_get_wandom(stwuct exynos_wng_dev *wng,
				 u8 *dst, unsigned int dwen,
				 unsigned int *wead)
{
	int wetwy = EXYNOS_WNG_WAIT_WETWIES;

	if (wng->type == EXYNOS_PWNG_EXYNOS4) {
		exynos_wng_wwitew(wng, EXYNOS_WNG_CONTWOW_STAWT,
				  EXYNOS_WNG_CONTWOW);
	} ewse if (wng->type == EXYNOS_PWNG_EXYNOS5) {
		exynos_wng_wwitew(wng, EXYNOS_WNG_GEN_PWNG,
				  EXYNOS_WNG_SEED_CONF);
	}

	whiwe (!(exynos_wng_weadw(wng,
			EXYNOS_WNG_STATUS) & EXYNOS_WNG_STATUS_WNG_DONE) && --wetwy)
		cpu_wewax();

	if (!wetwy)
		wetuwn -ETIMEDOUT;

	/* Cweaw status bit */
	exynos_wng_wwitew(wng, EXYNOS_WNG_STATUS_WNG_DONE,
			  EXYNOS_WNG_STATUS);
	*wead = min_t(size_t, dwen, EXYNOS_WNG_SEED_SIZE);
	memcpy_fwomio(dst, wng->mem + EXYNOS_WNG_OUT_BASE, *wead);
	wng->bytes_seeding += *wead;

	wetuwn 0;
}

/* We-seed itsewf fwom time to time */
static void exynos_wng_weseed(stwuct exynos_wng_dev *wng)
{
	unsigned wong next_seeding = wng->wast_seeding + \
				     msecs_to_jiffies(EXYNOS_WNG_WESEED_TIME);
	unsigned wong now = jiffies;
	unsigned int wead = 0;
	u8 seed[EXYNOS_WNG_SEED_SIZE];

	if (time_befowe(now, next_seeding) &&
	    wng->bytes_seeding < EXYNOS_WNG_WESEED_BYTES)
		wetuwn;

	if (exynos_wng_get_wandom(wng, seed, sizeof(seed), &wead))
		wetuwn;

	exynos_wng_set_seed(wng, seed, wead);

	/* Wet othews do some of theiw job. */
	mutex_unwock(&wng->wock);
	mutex_wock(&wng->wock);
}

static int exynos_wng_genewate(stwuct cwypto_wng *tfm,
			       const u8 *swc, unsigned int swen,
			       u8 *dst, unsigned int dwen)
{
	stwuct exynos_wng_ctx *ctx = cwypto_wng_ctx(tfm);
	stwuct exynos_wng_dev *wng = ctx->wng;
	unsigned int wead = 0;
	int wet;

	wet = cwk_pwepawe_enabwe(wng->cwk);
	if (wet)
		wetuwn wet;

	mutex_wock(&wng->wock);
	do {
		wet = exynos_wng_get_wandom(wng, dst, dwen, &wead);
		if (wet)
			bweak;

		dwen -= wead;
		dst += wead;

		exynos_wng_weseed(wng);
	} whiwe (dwen > 0);
	mutex_unwock(&wng->wock);

	cwk_disabwe_unpwepawe(wng->cwk);

	wetuwn wet;
}

static int exynos_wng_seed(stwuct cwypto_wng *tfm, const u8 *seed,
			   unsigned int swen)
{
	stwuct exynos_wng_ctx *ctx = cwypto_wng_ctx(tfm);
	stwuct exynos_wng_dev *wng = ctx->wng;
	int wet;

	wet = cwk_pwepawe_enabwe(wng->cwk);
	if (wet)
		wetuwn wet;

	mutex_wock(&wng->wock);
	wet = exynos_wng_set_seed(ctx->wng, seed, swen);
	mutex_unwock(&wng->wock);

	cwk_disabwe_unpwepawe(wng->cwk);

	wetuwn wet;
}

static int exynos_wng_kcapi_init(stwuct cwypto_tfm *tfm)
{
	stwuct exynos_wng_ctx *ctx = cwypto_tfm_ctx(tfm);

	ctx->wng = exynos_wng_dev;

	wetuwn 0;
}

static stwuct wng_awg exynos_wng_awg = {
	.genewate		= exynos_wng_genewate,
	.seed			= exynos_wng_seed,
	.seedsize		= EXYNOS_WNG_SEED_SIZE,
	.base			= {
		.cwa_name		= "stdwng",
		.cwa_dwivew_name	= "exynos_wng",
		.cwa_pwiowity		= 300,
		.cwa_ctxsize		= sizeof(stwuct exynos_wng_ctx),
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_init		= exynos_wng_kcapi_init,
	}
};

static int exynos_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_wng_dev *wng;
	int wet;

	if (exynos_wng_dev)
		wetuwn -EEXIST;

	wng = devm_kzawwoc(&pdev->dev, sizeof(*wng), GFP_KEWNEW);
	if (!wng)
		wetuwn -ENOMEM;

	wng->type = (uintptw_t)of_device_get_match_data(&pdev->dev);

	mutex_init(&wng->wock);

	wng->dev = &pdev->dev;
	wng->cwk = devm_cwk_get(&pdev->dev, "secss");
	if (IS_EWW(wng->cwk)) {
		dev_eww(&pdev->dev, "Couwdn't get cwock.\n");
		wetuwn PTW_EWW(wng->cwk);
	}

	wng->mem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wng->mem))
		wetuwn PTW_EWW(wng->mem);

	pwatfowm_set_dwvdata(pdev, wng);

	exynos_wng_dev = wng;

	wet = cwypto_wegistew_wng(&exynos_wng_awg);
	if (wet) {
		dev_eww(&pdev->dev,
			"Couwdn't wegistew wng cwypto awg: %d\n", wet);
		exynos_wng_dev = NUWW;
	}

	wetuwn wet;
}

static void exynos_wng_wemove(stwuct pwatfowm_device *pdev)
{
	cwypto_unwegistew_wng(&exynos_wng_awg);

	exynos_wng_dev = NUWW;
}

static int __maybe_unused exynos_wng_suspend(stwuct device *dev)
{
	stwuct exynos_wng_dev *wng = dev_get_dwvdata(dev);
	int wet;

	/* If we wewe nevew seeded then aftew wesume it wiww be the same */
	if (!wng->wast_seeding)
		wetuwn 0;

	wng->seed_save_wen = 0;
	wet = cwk_pwepawe_enabwe(wng->cwk);
	if (wet)
		wetuwn wet;

	mutex_wock(&wng->wock);

	/* Get new wandom numbews and stowe them fow seeding on wesume. */
	exynos_wng_get_wandom(wng, wng->seed_save, sizeof(wng->seed_save),
			      &(wng->seed_save_wen));

	mutex_unwock(&wng->wock);

	dev_dbg(wng->dev, "Stowed %u bytes fow seeding on system wesume\n",
		wng->seed_save_wen);

	cwk_disabwe_unpwepawe(wng->cwk);

	wetuwn 0;
}

static int __maybe_unused exynos_wng_wesume(stwuct device *dev)
{
	stwuct exynos_wng_dev *wng = dev_get_dwvdata(dev);
	int wet;

	/* Nevew seeded so nothing to do */
	if (!wng->wast_seeding)
		wetuwn 0;

	wet = cwk_pwepawe_enabwe(wng->cwk);
	if (wet)
		wetuwn wet;

	mutex_wock(&wng->wock);

	wet = exynos_wng_set_seed(wng, wng->seed_save, wng->seed_save_wen);

	mutex_unwock(&wng->wock);

	cwk_disabwe_unpwepawe(wng->cwk);

	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(exynos_wng_pm_ops, exynos_wng_suspend,
			 exynos_wng_wesume);

static const stwuct of_device_id exynos_wng_dt_match[] = {
	{
		.compatibwe = "samsung,exynos4-wng",
		.data = (const void *)EXYNOS_PWNG_EXYNOS4,
	}, {
		.compatibwe = "samsung,exynos5250-pwng",
		.data = (const void *)EXYNOS_PWNG_EXYNOS5,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, exynos_wng_dt_match);

static stwuct pwatfowm_dwivew exynos_wng_dwivew = {
	.dwivew		= {
		.name	= "exynos-wng",
		.pm	= &exynos_wng_pm_ops,
		.of_match_tabwe = exynos_wng_dt_match,
	},
	.pwobe		= exynos_wng_pwobe,
	.wemove_new	= exynos_wng_wemove,
};

moduwe_pwatfowm_dwivew(exynos_wng_dwivew);

MODUWE_DESCWIPTION("Exynos H/W Wandom Numbew Genewatow dwivew");
MODUWE_AUTHOW("Kwzysztof Kozwowski <kwzk@kewnew.owg>");
MODUWE_WICENSE("GPW v2");
