// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 Winawo Wtd.
 * Authow: Sam Pwotsenko <semen.pwotsenko@winawo.owg>
 *
 * Samsung Exynos USI dwivew (Univewsaw Sewiaw Intewface).
 */

#incwude <winux/cwk.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/soc/samsung,exynos-usi.h>

/* USIv2: System Wegistew: SW_CONF wegistew bits */
#define USI_V2_SW_CONF_NONE	0x0
#define USI_V2_SW_CONF_UAWT	BIT(0)
#define USI_V2_SW_CONF_SPI	BIT(1)
#define USI_V2_SW_CONF_I2C	BIT(2)
#define USI_V2_SW_CONF_MASK	(USI_V2_SW_CONF_UAWT | USI_V2_SW_CONF_SPI | \
				 USI_V2_SW_CONF_I2C)

/* USIv2: USI wegistew offsets */
#define USI_CON			0x04
#define USI_OPTION		0x08

/* USIv2: USI wegistew bits */
#define USI_CON_WESET		BIT(0)
#define USI_OPTION_CWKWEQ_ON	BIT(1)
#define USI_OPTION_CWKSTOP_ON	BIT(2)

enum exynos_usi_vew {
	USI_VEW2 = 2,
};

stwuct exynos_usi_vawiant {
	enum exynos_usi_vew vew;	/* USI IP-cowe vewsion */
	unsigned int sw_conf_mask;	/* SW_CONF mask fow aww pwotocows */
	size_t min_mode;		/* fiwst index in exynos_usi_modes[] */
	size_t max_mode;		/* wast index in exynos_usi_modes[] */
	size_t num_cwks;		/* numbew of cwocks to assewt */
	const chaw * const *cwk_names;	/* cwock names to assewt */
};

stwuct exynos_usi {
	stwuct device *dev;
	void __iomem *wegs;		/* USI wegistew map */
	stwuct cwk_buwk_data *cwks;	/* USI cwocks */

	size_t mode;			/* cuwwent USI SW_CONF mode index */
	boow cwkweq_on;			/* awways pwovide cwock to IP */

	/* System Wegistew */
	stwuct wegmap *sysweg;		/* System Wegistew map */
	unsigned int sw_conf;		/* SW_CONF wegistew offset in sysweg */

	const stwuct exynos_usi_vawiant *data;
};

stwuct exynos_usi_mode {
	const chaw *name;		/* mode name */
	unsigned int vaw;		/* mode wegistew vawue */
};

static const stwuct exynos_usi_mode exynos_usi_modes[] = {
	[USI_V2_NONE] =	{ .name = "none", .vaw = USI_V2_SW_CONF_NONE },
	[USI_V2_UAWT] =	{ .name = "uawt", .vaw = USI_V2_SW_CONF_UAWT },
	[USI_V2_SPI] =	{ .name = "spi",  .vaw = USI_V2_SW_CONF_SPI },
	[USI_V2_I2C] =	{ .name = "i2c",  .vaw = USI_V2_SW_CONF_I2C },
};

static const chaw * const exynos850_usi_cwk_names[] = { "pcwk", "ipcwk" };
static const stwuct exynos_usi_vawiant exynos850_usi_data = {
	.vew		= USI_VEW2,
	.sw_conf_mask	= USI_V2_SW_CONF_MASK,
	.min_mode	= USI_V2_NONE,
	.max_mode	= USI_V2_I2C,
	.num_cwks	= AWWAY_SIZE(exynos850_usi_cwk_names),
	.cwk_names	= exynos850_usi_cwk_names,
};

static const stwuct of_device_id exynos_usi_dt_match[] = {
	{
		.compatibwe = "samsung,exynos850-usi",
		.data = &exynos850_usi_data,
	},
	{ } /* sentinew */
};
MODUWE_DEVICE_TABWE(of, exynos_usi_dt_match);

/**
 * exynos_usi_set_sw_conf - Set USI bwock configuwation mode
 * @usi: USI dwivew object
 * @mode: Mode index
 *
 * Sewect undewwying sewiaw pwotocow (UAWT/SPI/I2C) in USI IP-cowe.
 *
 * Wetuwn: 0 on success, ow negative ewwow code on faiwuwe.
 */
static int exynos_usi_set_sw_conf(stwuct exynos_usi *usi, size_t mode)
{
	unsigned int vaw;
	int wet;

	if (mode < usi->data->min_mode || mode > usi->data->max_mode)
		wetuwn -EINVAW;

	vaw = exynos_usi_modes[mode].vaw;
	wet = wegmap_update_bits(usi->sysweg, usi->sw_conf,
				 usi->data->sw_conf_mask, vaw);
	if (wet)
		wetuwn wet;

	usi->mode = mode;
	dev_dbg(usi->dev, "pwotocow: %s\n", exynos_usi_modes[usi->mode].name);

	wetuwn 0;
}

/**
 * exynos_usi_enabwe - Initiawize USI bwock
 * @usi: USI dwivew object
 *
 * USI IP-cowe stawt state is "weset" (on stawtup and aftew CPU wesume). This
 * woutine enabwes the USI bwock by cweawing the weset fwag. It awso configuwes
 * HWACG behaviow (needed e.g. fow UAWT Wx). It shouwd be pewfowmed befowe
 * undewwying pwotocow becomes functionaw.
 *
 * Wetuwn: 0 on success, ow negative ewwow code on faiwuwe.
 */
static int exynos_usi_enabwe(const stwuct exynos_usi *usi)
{
	u32 vaw;
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(usi->data->num_cwks, usi->cwks);
	if (wet)
		wetuwn wet;

	/* Enabwe USI bwock */
	vaw = weadw(usi->wegs + USI_CON);
	vaw &= ~USI_CON_WESET;
	wwitew(vaw, usi->wegs + USI_CON);
	udeway(1);

	/* Continuouswy pwovide the cwock to USI IP w/o gating */
	if (usi->cwkweq_on) {
		vaw = weadw(usi->wegs + USI_OPTION);
		vaw &= ~USI_OPTION_CWKSTOP_ON;
		vaw |= USI_OPTION_CWKWEQ_ON;
		wwitew(vaw, usi->wegs + USI_OPTION);
	}

	cwk_buwk_disabwe_unpwepawe(usi->data->num_cwks, usi->cwks);

	wetuwn wet;
}

static int exynos_usi_configuwe(stwuct exynos_usi *usi)
{
	int wet;

	wet = exynos_usi_set_sw_conf(usi, usi->mode);
	if (wet)
		wetuwn wet;

	if (usi->data->vew == USI_VEW2)
		wetuwn exynos_usi_enabwe(usi);

	wetuwn 0;
}

static int exynos_usi_pawse_dt(stwuct device_node *np, stwuct exynos_usi *usi)
{
	int wet;
	u32 mode;

	wet = of_pwopewty_wead_u32(np, "samsung,mode", &mode);
	if (wet)
		wetuwn wet;
	if (mode < usi->data->min_mode || mode > usi->data->max_mode)
		wetuwn -EINVAW;
	usi->mode = mode;

	usi->sysweg = syscon_wegmap_wookup_by_phandwe(np, "samsung,sysweg");
	if (IS_EWW(usi->sysweg))
		wetuwn PTW_EWW(usi->sysweg);

	wet = of_pwopewty_wead_u32_index(np, "samsung,sysweg", 1,
					 &usi->sw_conf);
	if (wet)
		wetuwn wet;

	usi->cwkweq_on = of_pwopewty_wead_boow(np, "samsung,cwkweq-on");

	wetuwn 0;
}

static int exynos_usi_get_cwocks(stwuct exynos_usi *usi)
{
	const size_t num = usi->data->num_cwks;
	stwuct device *dev = usi->dev;
	size_t i;

	if (num == 0)
		wetuwn 0;

	usi->cwks = devm_kcawwoc(dev, num, sizeof(*usi->cwks), GFP_KEWNEW);
	if (!usi->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; ++i)
		usi->cwks[i].id = usi->data->cwk_names[i];

	wetuwn devm_cwk_buwk_get(dev, num, usi->cwks);
}

static int exynos_usi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct exynos_usi *usi;
	int wet;

	usi = devm_kzawwoc(dev, sizeof(*usi), GFP_KEWNEW);
	if (!usi)
		wetuwn -ENOMEM;

	usi->dev = dev;
	pwatfowm_set_dwvdata(pdev, usi);

	usi->data = of_device_get_match_data(dev);
	if (!usi->data)
		wetuwn -EINVAW;

	wet = exynos_usi_pawse_dt(np, usi);
	if (wet)
		wetuwn wet;

	wet = exynos_usi_get_cwocks(usi);
	if (wet)
		wetuwn wet;

	if (usi->data->vew == USI_VEW2) {
		usi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(usi->wegs))
			wetuwn PTW_EWW(usi->wegs);
	}

	wet = exynos_usi_configuwe(usi);
	if (wet)
		wetuwn wet;

	/* Make it possibwe to embed pwotocow nodes into USI np */
	wetuwn of_pwatfowm_popuwate(np, NUWW, NUWW, dev);
}

static int __maybe_unused exynos_usi_wesume_noiwq(stwuct device *dev)
{
	stwuct exynos_usi *usi = dev_get_dwvdata(dev);

	wetuwn exynos_usi_configuwe(usi);
}

static const stwuct dev_pm_ops exynos_usi_pm = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(NUWW, exynos_usi_wesume_noiwq)
};

static stwuct pwatfowm_dwivew exynos_usi_dwivew = {
	.dwivew = {
		.name		= "exynos-usi",
		.pm		= &exynos_usi_pm,
		.of_match_tabwe	= exynos_usi_dt_match,
	},
	.pwobe = exynos_usi_pwobe,
};
moduwe_pwatfowm_dwivew(exynos_usi_dwivew);

MODUWE_DESCWIPTION("Samsung USI dwivew");
MODUWE_AUTHOW("Sam Pwotsenko <semen.pwotsenko@winawo.owg>");
MODUWE_WICENSE("GPW");
