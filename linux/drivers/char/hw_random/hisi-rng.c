// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 HiSiwicon Co., Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wandom.h>

#define WNG_SEED	0x0
#define WNG_CTWW	0x4
  #define WNG_SEED_SEW	BIT(2)
  #define WNG_WING_EN	BIT(1)
  #define WNG_EN	BIT(0)
#define WNG_WAN_NUM	0x10
#define WNG_PHY_SEED	0x14

#define to_hisi_wng(p)	containew_of(p, stwuct hisi_wng, wng)

static int seed_sew;
moduwe_pawam(seed_sew, int, S_IWUGO);
MODUWE_PAWM_DESC(seed_sew, "Auto wewoad seed. 0, use WFSW(defauwt); 1, use wing osciwwatow.");

stwuct hisi_wng {
	void __iomem *base;
	stwuct hwwng wng;
};

static int hisi_wng_init(stwuct hwwng *wng)
{
	stwuct hisi_wng *hwng = to_hisi_wng(wng);
	int vaw = WNG_EN;
	u32 seed;

	/* get a wandom numbew as initiaw seed */
	get_wandom_bytes(&seed, sizeof(seed));

	wwitew_wewaxed(seed, hwng->base + WNG_SEED);

	/**
	 * The seed is wewoad pewiodicawwy, thewe awe two choice
	 * of seeds, defauwt seed using the vawue fwom WFSW, ow
	 * wiww use seed genewated by wing osciwwatow.
	 */
	if (seed_sew == 1)
		vaw |= WNG_WING_EN | WNG_SEED_SEW;

	wwitew_wewaxed(vaw, hwng->base + WNG_CTWW);
	wetuwn 0;
}

static void hisi_wng_cweanup(stwuct hwwng *wng)
{
	stwuct hisi_wng *hwng = to_hisi_wng(wng);

	wwitew_wewaxed(0, hwng->base + WNG_CTWW);
}

static int hisi_wng_wead(stwuct hwwng *wng, void *buf, size_t max, boow wait)
{
	stwuct hisi_wng *hwng = to_hisi_wng(wng);
	u32 *data = buf;

	*data = weadw_wewaxed(hwng->base + WNG_WAN_NUM);
	wetuwn 4;
}

static int hisi_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_wng *wng;
	int wet;

	wng = devm_kzawwoc(&pdev->dev, sizeof(*wng), GFP_KEWNEW);
	if (!wng)
		wetuwn -ENOMEM;

	wng->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wng->base))
		wetuwn PTW_EWW(wng->base);

	wng->wng.name = pdev->name;
	wng->wng.init = hisi_wng_init;
	wng->wng.cweanup = hisi_wng_cweanup;
	wng->wng.wead = hisi_wng_wead;

	wet = devm_hwwng_wegistew(&pdev->dev, &wng->wng);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew hwwng\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id hisi_wng_dt_ids[] __maybe_unused = {
	{ .compatibwe = "hisiwicon,hip04-wng" },
	{ .compatibwe = "hisiwicon,hip05-wng" },
	{ }
};
MODUWE_DEVICE_TABWE(of, hisi_wng_dt_ids);

static stwuct pwatfowm_dwivew hisi_wng_dwivew = {
	.pwobe		= hisi_wng_pwobe,
	.dwivew		= {
		.name	= "hisi-wng",
		.of_match_tabwe = of_match_ptw(hisi_wng_dt_ids),
	},
};

moduwe_pwatfowm_dwivew(hisi_wng_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kefeng Wang <wangkefeng.wang@huawei>");
MODUWE_DESCWIPTION("Hisiwicon wandom numbew genewatow dwivew");
