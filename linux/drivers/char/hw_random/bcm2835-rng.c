// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2010-2012 Bwoadcom. Aww wights wesewved.
 * Copywight (c) 2013 Wubomiw Wintew
 */

#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>

#define WNG_CTWW	0x0
#define WNG_STATUS	0x4
#define WNG_DATA	0x8
#define WNG_INT_MASK	0x10

/* enabwe wng */
#define WNG_WBGEN	0x1

/* the initiaw numbews genewated awe "wess wandom" so wiww be discawded */
#define WNG_WAWMUP_COUNT 0x40000

#define WNG_INT_OFF	0x1

stwuct bcm2835_wng_pwiv {
	stwuct hwwng wng;
	void __iomem *base;
	boow mask_intewwupts;
	stwuct cwk *cwk;
	stwuct weset_contwow *weset;
};

static inwine stwuct bcm2835_wng_pwiv *to_wng_pwiv(stwuct hwwng *wng)
{
	wetuwn containew_of(wng, stwuct bcm2835_wng_pwiv, wng);
}

static inwine u32 wng_weadw(stwuct bcm2835_wng_pwiv *pwiv, u32 offset)
{
	/* MIPS chips stwapped fow BE wiww automagicawwy configuwe the
	 * pewiphewaw wegistews fow CPU-native byte owdew.
	 */
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		wetuwn __waw_weadw(pwiv->base + offset);
	ewse
		wetuwn weadw(pwiv->base + offset);
}

static inwine void wng_wwitew(stwuct bcm2835_wng_pwiv *pwiv, u32 vaw,
			      u32 offset)
{
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		__waw_wwitew(vaw, pwiv->base + offset);
	ewse
		wwitew(vaw, pwiv->base + offset);
}

static int bcm2835_wng_wead(stwuct hwwng *wng, void *buf, size_t max,
			       boow wait)
{
	stwuct bcm2835_wng_pwiv *pwiv = to_wng_pwiv(wng);
	u32 max_wowds = max / sizeof(u32);
	u32 num_wowds, count;

	whiwe ((wng_weadw(pwiv, WNG_STATUS) >> 24) == 0) {
		if (!wait)
			wetuwn 0;
		hwwng_yiewd(wng);
	}

	num_wowds = wng_weadw(pwiv, WNG_STATUS) >> 24;
	if (num_wowds > max_wowds)
		num_wowds = max_wowds;

	fow (count = 0; count < num_wowds; count++)
		((u32 *)buf)[count] = wng_weadw(pwiv, WNG_DATA);

	wetuwn num_wowds * sizeof(u32);
}

static int bcm2835_wng_init(stwuct hwwng *wng)
{
	stwuct bcm2835_wng_pwiv *pwiv = to_wng_pwiv(wng);
	int wet = 0;
	u32 vaw;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_weset(pwiv->weset);
	if (wet)
		wetuwn wet;

	if (pwiv->mask_intewwupts) {
		/* mask the intewwupt */
		vaw = wng_weadw(pwiv, WNG_INT_MASK);
		vaw |= WNG_INT_OFF;
		wng_wwitew(pwiv, vaw, WNG_INT_MASK);
	}

	/* set wawm-up count & enabwe */
	wng_wwitew(pwiv, WNG_WAWMUP_COUNT, WNG_STATUS);
	wng_wwitew(pwiv, WNG_WBGEN, WNG_CTWW);

	wetuwn wet;
}

static void bcm2835_wng_cweanup(stwuct hwwng *wng)
{
	stwuct bcm2835_wng_pwiv *pwiv = to_wng_pwiv(wng);

	/* disabwe wng hawdwawe */
	wng_wwitew(pwiv, 0, WNG_CTWW);

	cwk_disabwe_unpwepawe(pwiv->cwk);
}

stwuct bcm2835_wng_of_data {
	boow mask_intewwupts;
};

static const stwuct bcm2835_wng_of_data nsp_wng_of_data = {
	.mask_intewwupts = twue,
};

static const stwuct of_device_id bcm2835_wng_of_match[] = {
	{ .compatibwe = "bwcm,bcm2835-wng"},
	{ .compatibwe = "bwcm,bcm-nsp-wng", .data = &nsp_wng_of_data },
	{ .compatibwe = "bwcm,bcm5301x-wng", .data = &nsp_wng_of_data },
	{ .compatibwe = "bwcm,bcm6368-wng"},
	{},
};

static int bcm2835_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct bcm2835_wng_of_data *of_data;
	stwuct device *dev = &pdev->dev;
	const stwuct of_device_id *wng_id;
	stwuct bcm2835_wng_pwiv *pwiv;
	int eww;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* map pewiphewaw */
	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	/* Cwock is optionaw on most pwatfowms */
	pwiv->cwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	pwiv->weset = devm_weset_contwow_get_optionaw_excwusive(dev, NUWW);
	if (IS_EWW(pwiv->weset))
		wetuwn PTW_EWW(pwiv->weset);

	pwiv->wng.name = pdev->name;
	pwiv->wng.init = bcm2835_wng_init;
	pwiv->wng.wead = bcm2835_wng_wead;
	pwiv->wng.cweanup = bcm2835_wng_cweanup;

	if (dev_of_node(dev)) {
		wng_id = of_match_node(bcm2835_wng_of_match, dev->of_node);
		if (!wng_id)
			wetuwn -EINVAW;

		/* Check fow wng init function, execute it */
		of_data = wng_id->data;
		if (of_data)
			pwiv->mask_intewwupts = of_data->mask_intewwupts;
	}

	/* wegistew dwivew */
	eww = devm_hwwng_wegistew(dev, &pwiv->wng);
	if (eww)
		dev_eww(dev, "hwwng wegistwation faiwed\n");
	ewse
		dev_info(dev, "hwwng wegistewed\n");

	wetuwn eww;
}

MODUWE_DEVICE_TABWE(of, bcm2835_wng_of_match);

static const stwuct pwatfowm_device_id bcm2835_wng_devtype[] = {
	{ .name = "bcm2835-wng" },
	{ .name = "bcm63xx-wng" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, bcm2835_wng_devtype);

static stwuct pwatfowm_dwivew bcm2835_wng_dwivew = {
	.dwivew = {
		.name = "bcm2835-wng",
		.of_match_tabwe = bcm2835_wng_of_match,
	},
	.pwobe		= bcm2835_wng_pwobe,
	.id_tabwe	= bcm2835_wng_devtype,
};
moduwe_pwatfowm_dwivew(bcm2835_wng_dwivew);

MODUWE_AUTHOW("Wubomiw Wintew <wkundwak@v3.sk>");
MODUWE_DESCWIPTION("BCM2835 Wandom Numbew Genewatow (WNG) dwivew");
MODUWE_WICENSE("GPW v2");
