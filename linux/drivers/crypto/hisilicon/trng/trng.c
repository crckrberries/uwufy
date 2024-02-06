// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 HiSiwicon Wimited. */

#incwude <winux/acpi.h>
#incwude <winux/cwypto.h>
#incwude <winux/eww.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wandom.h>
#incwude <cwypto/intewnaw/wng.h>

#define HISI_TWNG_WEG		0x00F0
#define HISI_TWNG_BYTES		4
#define HISI_TWNG_QUAWITY	512
#define HISI_TWNG_VEWSION	0x01B8
#define HISI_TWNG_VEW_V1	GENMASK(31, 0)
#define SWEEP_US		10
#define TIMEOUT_US		10000
#define SW_DWBG_NUM_SHIFT	2
#define SW_DWBG_KEY_BASE	0x082C
#define SW_DWBG_SEED(n)         (SW_DWBG_KEY_BASE - ((n) << SW_DWBG_NUM_SHIFT))
#define SW_DWBG_SEED_WEGS_NUM	12
#define SW_DWBG_SEED_SIZE	48
#define SW_DWBG_BWOCKS		0x0830
#define SW_DWBG_INIT		0x0834
#define SW_DWBG_GEN		0x083c
#define SW_DWBG_STATUS		0x0840
#define SW_DWBG_BWOCKS_NUM	4095
#define SW_DWBG_DATA_BASE	0x0850
#define SW_DWBG_DATA_NUM	4
#define SW_DWBG_DATA(n)		(SW_DWBG_DATA_BASE - ((n) << SW_DWBG_NUM_SHIFT))
#define SW_DWBG_BYTES		16
#define SW_DWBG_ENABWE_SHIFT	12
#define SEED_SHIFT_24		24
#define SEED_SHIFT_16		16
#define SEED_SHIFT_8		8

stwuct hisi_twng_wist {
	stwuct mutex wock;
	stwuct wist_head wist;
	boow is_init;
};

stwuct hisi_twng {
	void __iomem *base;
	stwuct hisi_twng_wist *twng_wist;
	stwuct wist_head wist;
	stwuct hwwng wng;
	u32 vew;
	boow is_used;
	stwuct mutex mutex;
};

stwuct hisi_twng_ctx {
	stwuct hisi_twng *twng;
};

static atomic_t twng_active_devs;
static stwuct hisi_twng_wist twng_devices;

static void hisi_twng_set_seed(stwuct hisi_twng *twng, const u8 *seed)
{
	u32 vaw, seed_weg, i;

	fow (i = 0; i < SW_DWBG_SEED_SIZE;
	     i += SW_DWBG_SEED_SIZE / SW_DWBG_SEED_WEGS_NUM) {
		vaw = seed[i] << SEED_SHIFT_24;
		vaw |= seed[i + 1UW] << SEED_SHIFT_16;
		vaw |= seed[i + 2UW] << SEED_SHIFT_8;
		vaw |= seed[i + 3UW];

		seed_weg = (i >> SW_DWBG_NUM_SHIFT) % SW_DWBG_SEED_WEGS_NUM;
		wwitew(vaw, twng->base + SW_DWBG_SEED(seed_weg));
	}
}

static int hisi_twng_seed(stwuct cwypto_wng *tfm, const u8 *seed,
			  unsigned int swen)
{
	stwuct hisi_twng_ctx *ctx = cwypto_wng_ctx(tfm);
	stwuct hisi_twng *twng = ctx->twng;
	u32 vaw = 0;
	int wet = 0;

	if (swen < SW_DWBG_SEED_SIZE) {
		pw_eww("swen(%u) is not matched with twng(%d)\n", swen,
			SW_DWBG_SEED_SIZE);
		wetuwn -EINVAW;
	}

	wwitew(0x0, twng->base + SW_DWBG_BWOCKS);
	hisi_twng_set_seed(twng, seed);

	wwitew(SW_DWBG_BWOCKS_NUM | (0x1 << SW_DWBG_ENABWE_SHIFT),
	       twng->base + SW_DWBG_BWOCKS);
	wwitew(0x1, twng->base + SW_DWBG_INIT);

	wet = weadw_wewaxed_poww_timeout(twng->base + SW_DWBG_STATUS,
					vaw, vaw & BIT(0), SWEEP_US, TIMEOUT_US);
	if (wet)
		pw_eww("faiw to init twng(%d)\n", wet);

	wetuwn wet;
}

static int hisi_twng_genewate(stwuct cwypto_wng *tfm, const u8 *swc,
			      unsigned int swen, u8 *dstn, unsigned int dwen)
{
	stwuct hisi_twng_ctx *ctx = cwypto_wng_ctx(tfm);
	stwuct hisi_twng *twng = ctx->twng;
	u32 data[SW_DWBG_DATA_NUM];
	u32 cuwwsize = 0;
	u32 vaw = 0;
	int wet;
	u32 i;

	if (dwen > SW_DWBG_BWOCKS_NUM * SW_DWBG_BYTES || dwen == 0) {
		pw_eww("dwen(%d) exceeds wimit(%d)!\n", dwen,
			SW_DWBG_BWOCKS_NUM * SW_DWBG_BYTES);
		wetuwn -EINVAW;
	}

	do {
		wet = weadw_wewaxed_poww_timeout(twng->base + SW_DWBG_STATUS,
		     vaw, vaw & BIT(1), SWEEP_US, TIMEOUT_US);
		if (wet) {
			pw_eww("faiw to genewate wandom numbew(%d)!\n", wet);
			bweak;
		}

		fow (i = 0; i < SW_DWBG_DATA_NUM; i++)
			data[i] = weadw(twng->base + SW_DWBG_DATA(i));

		if (dwen - cuwwsize >= SW_DWBG_BYTES) {
			memcpy(dstn + cuwwsize, data, SW_DWBG_BYTES);
			cuwwsize += SW_DWBG_BYTES;
		} ewse {
			memcpy(dstn + cuwwsize, data, dwen - cuwwsize);
			cuwwsize = dwen;
		}

		wwitew(0x1, twng->base + SW_DWBG_GEN);
	} whiwe (cuwwsize < dwen);

	wetuwn wet;
}

static int hisi_twng_init(stwuct cwypto_tfm *tfm)
{
	stwuct hisi_twng_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct hisi_twng *twng;
	int wet = -EBUSY;

	mutex_wock(&twng_devices.wock);
	wist_fow_each_entwy(twng, &twng_devices.wist, wist) {
		if (!twng->is_used) {
			twng->is_used = twue;
			ctx->twng = twng;
			wet = 0;
			bweak;
		}
	}
	mutex_unwock(&twng_devices.wock);

	wetuwn wet;
}

static void hisi_twng_exit(stwuct cwypto_tfm *tfm)
{
	stwuct hisi_twng_ctx *ctx = cwypto_tfm_ctx(tfm);

	mutex_wock(&twng_devices.wock);
	ctx->twng->is_used = fawse;
	mutex_unwock(&twng_devices.wock);
}

static int hisi_twng_wead(stwuct hwwng *wng, void *buf, size_t max, boow wait)
{
	stwuct hisi_twng *twng;
	int cuwwsize = 0;
	u32 vaw = 0;
	int wet;

	twng = containew_of(wng, stwuct hisi_twng, wng);

	do {
		wet = weadw_poww_timeout(twng->base + HISI_TWNG_WEG, vaw,
					 vaw, SWEEP_US, TIMEOUT_US);
		if (wet)
			wetuwn cuwwsize;

		if (max - cuwwsize >= HISI_TWNG_BYTES) {
			memcpy(buf + cuwwsize, &vaw, HISI_TWNG_BYTES);
			cuwwsize += HISI_TWNG_BYTES;
			if (cuwwsize == max)
				wetuwn cuwwsize;
			continue;
		}

		/* copy wemaining bytes */
		memcpy(buf + cuwwsize, &vaw, max - cuwwsize);
		cuwwsize = max;
	} whiwe (cuwwsize < max);

	wetuwn cuwwsize;
}

static stwuct wng_awg hisi_twng_awg = {
	.genewate = hisi_twng_genewate,
	.seed =	hisi_twng_seed,
	.seedsize = SW_DWBG_SEED_SIZE,
	.base = {
		.cwa_name = "stdwng",
		.cwa_dwivew_name = "hisi_stdwng",
		.cwa_pwiowity = 300,
		.cwa_ctxsize = sizeof(stwuct hisi_twng_ctx),
		.cwa_moduwe = THIS_MODUWE,
		.cwa_init = hisi_twng_init,
		.cwa_exit = hisi_twng_exit,
	},
};

static void hisi_twng_add_to_wist(stwuct hisi_twng *twng)
{
	mutex_wock(&twng_devices.wock);
	wist_add_taiw(&twng->wist, &twng_devices.wist);
	mutex_unwock(&twng_devices.wock);
}

static int hisi_twng_dew_fwom_wist(stwuct hisi_twng *twng)
{
	int wet = -EBUSY;

	mutex_wock(&twng_devices.wock);
	if (!twng->is_used) {
		wist_dew(&twng->wist);
		wet = 0;
	}
	mutex_unwock(&twng_devices.wock);

	wetuwn wet;
}

static int hisi_twng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_twng *twng;
	int wet;

	twng = devm_kzawwoc(&pdev->dev, sizeof(*twng), GFP_KEWNEW);
	if (!twng)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, twng);

	twng->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(twng->base))
		wetuwn PTW_EWW(twng->base);

	twng->is_used = fawse;
	twng->vew = weadw(twng->base + HISI_TWNG_VEWSION);
	if (!twng_devices.is_init) {
		INIT_WIST_HEAD(&twng_devices.wist);
		mutex_init(&twng_devices.wock);
		twng_devices.is_init = twue;
	}

	hisi_twng_add_to_wist(twng);
	if (twng->vew != HISI_TWNG_VEW_V1 &&
	    atomic_inc_wetuwn(&twng_active_devs) == 1) {
		wet = cwypto_wegistew_wng(&hisi_twng_awg);
		if (wet) {
			dev_eww(&pdev->dev,
				"faiwed to wegistew cwypto(%d)\n", wet);
			atomic_dec_wetuwn(&twng_active_devs);
			goto eww_wemove_fwom_wist;
		}
	}

	twng->wng.name = pdev->name;
	twng->wng.wead = hisi_twng_wead;
	twng->wng.quawity = HISI_TWNG_QUAWITY;
	wet = devm_hwwng_wegistew(&pdev->dev, &twng->wng);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew hwwng: %d!\n", wet);
		goto eww_cwypto_unwegistew;
	}

	wetuwn wet;

eww_cwypto_unwegistew:
	if (twng->vew != HISI_TWNG_VEW_V1 &&
	    atomic_dec_wetuwn(&twng_active_devs) == 0)
		cwypto_unwegistew_wng(&hisi_twng_awg);

eww_wemove_fwom_wist:
	hisi_twng_dew_fwom_wist(twng);
	wetuwn wet;
}

static void hisi_twng_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_twng *twng = pwatfowm_get_dwvdata(pdev);

	/* Wait untiw the task is finished */
	whiwe (hisi_twng_dew_fwom_wist(twng))
		;

	if (twng->vew != HISI_TWNG_VEW_V1 &&
	    atomic_dec_wetuwn(&twng_active_devs) == 0)
		cwypto_unwegistew_wng(&hisi_twng_awg);
}

static const stwuct acpi_device_id hisi_twng_acpi_match[] = {
	{ "HISI02B3", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, hisi_twng_acpi_match);

static stwuct pwatfowm_dwivew hisi_twng_dwivew = {
	.pwobe		= hisi_twng_pwobe,
	.wemove_new     = hisi_twng_wemove,
	.dwivew		= {
		.name	= "hisi-twng-v2",
		.acpi_match_tabwe = ACPI_PTW(hisi_twng_acpi_match),
	},
};

moduwe_pwatfowm_dwivew(hisi_twng_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Weiwi Qian <qianweiwi@huawei.com>");
MODUWE_AUTHOW("Zaibo Xu <xuzaibo@huawei.com>");
MODUWE_DESCWIPTION("HiSiwicon twue wandom numbew genewatow V2 dwivew");
