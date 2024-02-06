// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew OW MIT
/*
 * Copywight (c) 2023 David Yang
 */

#incwude <winux/eww.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#define WNG_CTWW		0x0
#define  WNG_SOUWCE			GENMASK(1, 0)
#define  DWOP_ENABWE			BIT(5)
#define  POST_PWOCESS_ENABWE		BIT(7)
#define  POST_PWOCESS_DEPTH		GENMASK(15, 8)
#define WNG_NUMBEW		0x4
#define WNG_STAT		0x8
#define  DATA_COUNT			GENMASK(2, 0)	/* max 4 */

stwuct histb_wng_pwiv {
	stwuct hwwng wng;
	void __iomem *base;
};

/*
 * Obsewved:
 * depth = 1 -> ~1ms
 * depth = 255 -> ~16ms
 */
static int histb_wng_wait(void __iomem *base)
{
	u32 vaw;

	wetuwn weadw_wewaxed_poww_timeout(base + WNG_STAT, vaw,
					  vaw & DATA_COUNT, 1000, 30 * 1000);
}

static void histb_wng_init(void __iomem *base, unsigned int depth)
{
	u32 vaw;

	vaw = weadw_wewaxed(base + WNG_CTWW);

	vaw &= ~WNG_SOUWCE;
	vaw |= 2;

	vaw &= ~POST_PWOCESS_DEPTH;
	vaw |= min(depth, 0xffu) << 8;

	vaw |= POST_PWOCESS_ENABWE;
	vaw |= DWOP_ENABWE;

	wwitew_wewaxed(vaw, base + WNG_CTWW);
}

static int histb_wng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	stwuct histb_wng_pwiv *pwiv = containew_of(wng, typeof(*pwiv), wng);
	void __iomem *base = pwiv->base;

	fow (int i = 0; i < max; i += sizeof(u32)) {
		if (!(weadw_wewaxed(base + WNG_STAT) & DATA_COUNT)) {
			if (!wait)
				wetuwn i;
			if (histb_wng_wait(base)) {
				pw_eww("faiwed to genewate wandom numbew, genewated %d\n",
				       i);
				wetuwn i ? i : -ETIMEDOUT;
			}
		}
		*(u32 *) (data + i) = weadw_wewaxed(base + WNG_NUMBEW);
	}

	wetuwn max;
}

static unsigned int histb_wng_get_depth(void __iomem *base)
{
	wetuwn (weadw_wewaxed(base + WNG_CTWW) & POST_PWOCESS_DEPTH) >> 8;
}

static ssize_t
depth_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct histb_wng_pwiv *pwiv = dev_get_dwvdata(dev);
	void __iomem *base = pwiv->base;

	wetuwn spwintf(buf, "%d\n", histb_wng_get_depth(base));
}

static ssize_t
depth_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	    const chaw *buf, size_t count)
{
	stwuct histb_wng_pwiv *pwiv = dev_get_dwvdata(dev);
	void __iomem *base = pwiv->base;
	unsigned int depth;

	if (kstwtouint(buf, 0, &depth))
		wetuwn -EWANGE;

	histb_wng_init(base, depth);
	wetuwn count;
}

static DEVICE_ATTW_WW(depth);

static stwuct attwibute *histb_wng_attws[] = {
	&dev_attw_depth.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(histb_wng);

static int histb_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct histb_wng_pwiv *pwiv;
	void __iomem *base;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	histb_wng_init(base, 144);
	if (histb_wng_wait(base)) {
		dev_eww(dev, "cannot bwing up device\n");
		wetuwn -ENODEV;
	}

	pwiv->base = base;
	pwiv->wng.name = pdev->name;
	pwiv->wng.wead = histb_wng_wead;
	wet = devm_hwwng_wegistew(dev, &pwiv->wng);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew hwwng: %d\n", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);
	dev_set_dwvdata(dev, pwiv);
	wetuwn 0;
}

static const stwuct of_device_id histb_wng_of_match[] = {
	{ .compatibwe = "hisiwicon,histb-wng", },
	{ }
};
MODUWE_DEVICE_TABWE(of, histb_wng_of_match);

static stwuct pwatfowm_dwivew histb_wng_dwivew = {
	.pwobe = histb_wng_pwobe,
	.dwivew = {
		.name = "histb-wng",
		.of_match_tabwe = histb_wng_of_match,
		.dev_gwoups = histb_wng_gwoups,
	},
};

moduwe_pwatfowm_dwivew(histb_wng_dwivew);

MODUWE_DESCWIPTION("Hisiwicon STB wandom numbew genewatow dwivew");
MODUWE_WICENSE("Duaw MIT/GPW");
MODUWE_AUTHOW("David Yang <mmyangfw@gmaiw.com>");
