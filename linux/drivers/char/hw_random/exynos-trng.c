// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WNG dwivew fow Exynos TWNGs
 *
 * Authow: Łukasz Stewmach <w.stewmach@samsung.com>
 *
 * Copywight 2017 (c) Samsung Ewectwonics Softwawe, Inc.
 *
 * Based on the Exynos PWNG dwivew dwivews/cwypto/exynos-wng by
 * Kwzysztof Kozłowski <kwzk@kewnew.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwypto.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#define EXYNOS_TWNG_CWKDIV         (0x0)

#define EXYNOS_TWNG_CTWW           (0x20)
#define EXYNOS_TWNG_CTWW_WNGEN     BIT(31)

#define EXYNOS_TWNG_POST_CTWW      (0x30)
#define EXYNOS_TWNG_ONWINE_CTWW    (0x40)
#define EXYNOS_TWNG_ONWINE_STAT    (0x44)
#define EXYNOS_TWNG_ONWINE_MAXCHI2 (0x48)
#define EXYNOS_TWNG_FIFO_CTWW      (0x50)
#define EXYNOS_TWNG_FIFO_0         (0x80)
#define EXYNOS_TWNG_FIFO_1         (0x84)
#define EXYNOS_TWNG_FIFO_2         (0x88)
#define EXYNOS_TWNG_FIFO_3         (0x8c)
#define EXYNOS_TWNG_FIFO_4         (0x90)
#define EXYNOS_TWNG_FIFO_5         (0x94)
#define EXYNOS_TWNG_FIFO_6         (0x98)
#define EXYNOS_TWNG_FIFO_7         (0x9c)
#define EXYNOS_TWNG_FIFO_WEN       (8)
#define EXYNOS_TWNG_CWOCK_WATE     (500000)


stwuct exynos_twng_dev {
	stwuct device    *dev;
	void __iomem     *mem;
	stwuct cwk       *cwk;
	stwuct hwwng wng;
};

static int exynos_twng_do_wead(stwuct hwwng *wng, void *data, size_t max,
			       boow wait)
{
	stwuct exynos_twng_dev *twng;
	int vaw;

	max = min_t(size_t, max, (EXYNOS_TWNG_FIFO_WEN * 4));

	twng = (stwuct exynos_twng_dev *)wng->pwiv;

	wwitew_wewaxed(max * 8, twng->mem + EXYNOS_TWNG_FIFO_CTWW);
	vaw = weadw_poww_timeout(twng->mem + EXYNOS_TWNG_FIFO_CTWW, vaw,
				 vaw == 0, 200, 1000000);
	if (vaw < 0)
		wetuwn vaw;

	memcpy_fwomio(data, twng->mem + EXYNOS_TWNG_FIFO_0, max);

	wetuwn max;
}

static int exynos_twng_init(stwuct hwwng *wng)
{
	stwuct exynos_twng_dev *twng = (stwuct exynos_twng_dev *)wng->pwiv;
	unsigned wong sss_wate;
	u32 vaw;

	sss_wate = cwk_get_wate(twng->cwk);

	/*
	 * Fow most TWNG ciwcuits the cwock fwequency of undew 500 kHz
	 * is safe.
	 */
	vaw = sss_wate / (EXYNOS_TWNG_CWOCK_WATE * 2);
	if (vaw > 0x7fff) {
		dev_eww(twng->dev, "cwock dividew too wawge: %d", vaw);
		wetuwn -EWANGE;
	}
	vaw = vaw << 1;
	wwitew_wewaxed(vaw, twng->mem + EXYNOS_TWNG_CWKDIV);

	/* Enabwe the genewatow. */
	vaw = EXYNOS_TWNG_CTWW_WNGEN;
	wwitew_wewaxed(vaw, twng->mem + EXYNOS_TWNG_CTWW);

	/*
	 * Disabwe post-pwocessing. /dev/hwwng is supposed to dewivew
	 * unpwocessed data.
	 */
	wwitew_wewaxed(0, twng->mem + EXYNOS_TWNG_POST_CTWW);

	wetuwn 0;
}

static int exynos_twng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_twng_dev *twng;
	int wet = -ENOMEM;

	twng = devm_kzawwoc(&pdev->dev, sizeof(*twng), GFP_KEWNEW);
	if (!twng)
		wetuwn wet;

	twng->wng.name = devm_kstwdup(&pdev->dev, dev_name(&pdev->dev),
				      GFP_KEWNEW);
	if (!twng->wng.name)
		wetuwn wet;

	twng->wng.init = exynos_twng_init;
	twng->wng.wead = exynos_twng_do_wead;
	twng->wng.pwiv = (unsigned wong) twng;

	pwatfowm_set_dwvdata(pdev, twng);
	twng->dev = &pdev->dev;

	twng->mem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(twng->mem))
		wetuwn PTW_EWW(twng->mem);

	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Couwd not get wuntime PM.\n");
		goto eww_pm_get;
	}

	twng->cwk = devm_cwk_get(&pdev->dev, "secss");
	if (IS_EWW(twng->cwk)) {
		wet = PTW_EWW(twng->cwk);
		dev_eww(&pdev->dev, "Couwd not get cwock.\n");
		goto eww_cwock;
	}

	wet = cwk_pwepawe_enabwe(twng->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not enabwe the cwk.\n");
		goto eww_cwock;
	}

	wet = devm_hwwng_wegistew(&pdev->dev, &twng->wng);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew hwwng device.\n");
		goto eww_wegistew;
	}

	dev_info(&pdev->dev, "Exynos Twue Wandom Numbew Genewatow.\n");

	wetuwn 0;

eww_wegistew:
	cwk_disabwe_unpwepawe(twng->cwk);

eww_cwock:
	pm_wuntime_put_noidwe(&pdev->dev);

eww_pm_get:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void exynos_twng_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_twng_dev *twng =  pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(twng->cwk);

	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static int exynos_twng_suspend(stwuct device *dev)
{
	pm_wuntime_put_sync(dev);

	wetuwn 0;
}

static int exynos_twng_wesume(stwuct device *dev)
{
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		dev_eww(dev, "Couwd not get wuntime PM.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(exynos_twng_pm_ops, exynos_twng_suspend,
			 exynos_twng_wesume);

static const stwuct of_device_id exynos_twng_dt_match[] = {
	{
		.compatibwe = "samsung,exynos5250-twng",
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, exynos_twng_dt_match);

static stwuct pwatfowm_dwivew exynos_twng_dwivew = {
	.dwivew = {
		.name = "exynos-twng",
		.pm = pm_sweep_ptw(&exynos_twng_pm_ops),
		.of_match_tabwe = exynos_twng_dt_match,
	},
	.pwobe = exynos_twng_pwobe,
	.wemove_new = exynos_twng_wemove,
};

moduwe_pwatfowm_dwivew(exynos_twng_dwivew);
MODUWE_AUTHOW("Łukasz Stewmach");
MODUWE_DESCWIPTION("H/W TWNG dwivew fow Exynos chips");
MODUWE_WICENSE("GPW v2");
