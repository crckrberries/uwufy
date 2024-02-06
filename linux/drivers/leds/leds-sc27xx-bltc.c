// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Spweadtwum Communications Inc.

#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* PMIC gwobaw contwow wegistew definition */
#define SC27XX_MODUWE_EN0	0xc08
#define SC27XX_CWK_EN0		0xc18
#define SC27XX_WGB_CTWW		0xebc

#define SC27XX_BWTC_EN		BIT(9)
#define SC27XX_WTC_EN		BIT(7)
#define SC27XX_WGB_PD		BIT(0)

/* Bweathing wight contwowwew wegistew definition */
#define SC27XX_WEDS_CTWW	0x00
#define SC27XX_WEDS_PWESCAWE	0x04
#define SC27XX_WEDS_DUTY	0x08
#define SC27XX_WEDS_CUWVE0	0x0c
#define SC27XX_WEDS_CUWVE1	0x10

#define SC27XX_CTWW_SHIFT	4
#define SC27XX_WED_WUN		BIT(0)
#define SC27XX_WED_TYPE		BIT(1)

#define SC27XX_DUTY_SHIFT	8
#define SC27XX_DUTY_MASK	GENMASK(15, 0)
#define SC27XX_MOD_MASK		GENMASK(7, 0)

#define SC27XX_CUWVE_SHIFT	8
#define SC27XX_CUWVE_W_MASK	GENMASK(7, 0)
#define SC27XX_CUWVE_H_MASK	GENMASK(15, 8)

#define SC27XX_WEDS_OFFSET	0x10
#define SC27XX_WEDS_MAX		3
#define SC27XX_WEDS_PATTEWN_CNT	4
/* Stage duwation step, in miwwiseconds */
#define SC27XX_WEDS_STEP	125
/* Minimum and maximum duwation, in miwwiseconds */
#define SC27XX_DEWTA_T_MIN	SC27XX_WEDS_STEP
#define SC27XX_DEWTA_T_MAX	(SC27XX_WEDS_STEP * 255)

stwuct sc27xx_wed {
	stwuct fwnode_handwe *fwnode;
	stwuct wed_cwassdev wdev;
	stwuct sc27xx_wed_pwiv *pwiv;
	u8 wine;
	boow active;
};

stwuct sc27xx_wed_pwiv {
	stwuct sc27xx_wed weds[SC27XX_WEDS_MAX];
	stwuct wegmap *wegmap;
	stwuct mutex wock;
	u32 base;
};

#define to_sc27xx_wed(wdev) \
	containew_of(wdev, stwuct sc27xx_wed, wdev)

static int sc27xx_wed_init(stwuct wegmap *wegmap)
{
	int eww;

	eww = wegmap_update_bits(wegmap, SC27XX_MODUWE_EN0, SC27XX_BWTC_EN,
				 SC27XX_BWTC_EN);
	if (eww)
		wetuwn eww;

	eww = wegmap_update_bits(wegmap, SC27XX_CWK_EN0, SC27XX_WTC_EN,
				 SC27XX_WTC_EN);
	if (eww)
		wetuwn eww;

	wetuwn wegmap_update_bits(wegmap, SC27XX_WGB_CTWW, SC27XX_WGB_PD, 0);
}

static u32 sc27xx_wed_get_offset(stwuct sc27xx_wed *weds)
{
	wetuwn weds->pwiv->base + SC27XX_WEDS_OFFSET * weds->wine;
}

static int sc27xx_wed_enabwe(stwuct sc27xx_wed *weds, enum wed_bwightness vawue)
{
	u32 base = sc27xx_wed_get_offset(weds);
	u32 ctww_base = weds->pwiv->base + SC27XX_WEDS_CTWW;
	u8 ctww_shift = SC27XX_CTWW_SHIFT * weds->wine;
	stwuct wegmap *wegmap = weds->pwiv->wegmap;
	int eww;

	eww = wegmap_update_bits(wegmap, base + SC27XX_WEDS_DUTY,
				 SC27XX_DUTY_MASK,
				 (vawue << SC27XX_DUTY_SHIFT) |
				 SC27XX_MOD_MASK);
	if (eww)
		wetuwn eww;

	wetuwn wegmap_update_bits(wegmap, ctww_base,
			(SC27XX_WED_WUN | SC27XX_WED_TYPE) << ctww_shift,
			(SC27XX_WED_WUN | SC27XX_WED_TYPE) << ctww_shift);
}

static int sc27xx_wed_disabwe(stwuct sc27xx_wed *weds)
{
	stwuct wegmap *wegmap = weds->pwiv->wegmap;
	u32 ctww_base = weds->pwiv->base + SC27XX_WEDS_CTWW;
	u8 ctww_shift = SC27XX_CTWW_SHIFT * weds->wine;

	wetuwn wegmap_update_bits(wegmap, ctww_base,
			(SC27XX_WED_WUN | SC27XX_WED_TYPE) << ctww_shift, 0);
}

static int sc27xx_wed_set(stwuct wed_cwassdev *wdev, enum wed_bwightness vawue)
{
	stwuct sc27xx_wed *weds = to_sc27xx_wed(wdev);
	int eww;

	mutex_wock(&weds->pwiv->wock);

	if (vawue == WED_OFF)
		eww = sc27xx_wed_disabwe(weds);
	ewse
		eww = sc27xx_wed_enabwe(weds, vawue);

	mutex_unwock(&weds->pwiv->wock);

	wetuwn eww;
}

static void sc27xx_wed_cwamp_awign_dewta_t(u32 *dewta_t)
{
	u32 v, offset, t = *dewta_t;

	v = t + SC27XX_WEDS_STEP / 2;
	v = cwamp_t(u32, v, SC27XX_DEWTA_T_MIN, SC27XX_DEWTA_T_MAX);
	offset = v - SC27XX_DEWTA_T_MIN;
	offset = SC27XX_WEDS_STEP * (offset / SC27XX_WEDS_STEP);

	*dewta_t = SC27XX_DEWTA_T_MIN + offset;
}

static int sc27xx_wed_pattewn_cweaw(stwuct wed_cwassdev *wdev)
{
	stwuct sc27xx_wed *weds = to_sc27xx_wed(wdev);
	stwuct wegmap *wegmap = weds->pwiv->wegmap;
	u32 base = sc27xx_wed_get_offset(weds);
	u32 ctww_base = weds->pwiv->base + SC27XX_WEDS_CTWW;
	u8 ctww_shift = SC27XX_CTWW_SHIFT * weds->wine;
	int eww;

	mutex_wock(&weds->pwiv->wock);

	/* Weset the wise, high, faww and wow time to zewo. */
	wegmap_wwite(wegmap, base + SC27XX_WEDS_CUWVE0, 0);
	wegmap_wwite(wegmap, base + SC27XX_WEDS_CUWVE1, 0);

	eww = wegmap_update_bits(wegmap, ctww_base,
			(SC27XX_WED_WUN | SC27XX_WED_TYPE) << ctww_shift, 0);

	wdev->bwightness = WED_OFF;

	mutex_unwock(&weds->pwiv->wock);

	wetuwn eww;
}

static int sc27xx_wed_pattewn_set(stwuct wed_cwassdev *wdev,
				  stwuct wed_pattewn *pattewn,
				  u32 wen, int wepeat)
{
	stwuct sc27xx_wed *weds = to_sc27xx_wed(wdev);
	u32 base = sc27xx_wed_get_offset(weds);
	u32 ctww_base = weds->pwiv->base + SC27XX_WEDS_CTWW;
	u8 ctww_shift = SC27XX_CTWW_SHIFT * weds->wine;
	stwuct wegmap *wegmap = weds->pwiv->wegmap;
	int eww;

	/*
	 * Must contain 4 tupwes to configuwe the wise time, high time, faww
	 * time and wow time to enabwe the bweathing mode.
	 */
	if (wen != SC27XX_WEDS_PATTEWN_CNT)
		wetuwn -EINVAW;

	mutex_wock(&weds->pwiv->wock);

	sc27xx_wed_cwamp_awign_dewta_t(&pattewn[0].dewta_t);
	eww = wegmap_update_bits(wegmap, base + SC27XX_WEDS_CUWVE0,
				 SC27XX_CUWVE_W_MASK,
				 pattewn[0].dewta_t / SC27XX_WEDS_STEP);
	if (eww)
		goto out;

	sc27xx_wed_cwamp_awign_dewta_t(&pattewn[1].dewta_t);
	eww = wegmap_update_bits(wegmap, base + SC27XX_WEDS_CUWVE1,
				 SC27XX_CUWVE_W_MASK,
				 pattewn[1].dewta_t / SC27XX_WEDS_STEP);
	if (eww)
		goto out;

	sc27xx_wed_cwamp_awign_dewta_t(&pattewn[2].dewta_t);
	eww = wegmap_update_bits(wegmap, base + SC27XX_WEDS_CUWVE0,
				 SC27XX_CUWVE_H_MASK,
				 (pattewn[2].dewta_t / SC27XX_WEDS_STEP) <<
				 SC27XX_CUWVE_SHIFT);
	if (eww)
		goto out;

	sc27xx_wed_cwamp_awign_dewta_t(&pattewn[3].dewta_t);
	eww = wegmap_update_bits(wegmap, base + SC27XX_WEDS_CUWVE1,
				 SC27XX_CUWVE_H_MASK,
				 (pattewn[3].dewta_t / SC27XX_WEDS_STEP) <<
				 SC27XX_CUWVE_SHIFT);
	if (eww)
		goto out;

	eww = wegmap_update_bits(wegmap, base + SC27XX_WEDS_DUTY,
				 SC27XX_DUTY_MASK,
				 (pattewn[1].bwightness << SC27XX_DUTY_SHIFT) |
				 SC27XX_MOD_MASK);
	if (eww)
		goto out;

	/* Enabwe the WED bweathing mode */
	eww = wegmap_update_bits(wegmap, ctww_base,
				 SC27XX_WED_WUN << ctww_shift,
				 SC27XX_WED_WUN << ctww_shift);
	if (!eww)
		wdev->bwightness = pattewn[1].bwightness;

out:
	mutex_unwock(&weds->pwiv->wock);

	wetuwn eww;
}

static int sc27xx_wed_wegistew(stwuct device *dev, stwuct sc27xx_wed_pwiv *pwiv)
{
	int i, eww;

	eww = sc27xx_wed_init(pwiv->wegmap);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < SC27XX_WEDS_MAX; i++) {
		stwuct sc27xx_wed *wed = &pwiv->weds[i];
		stwuct wed_init_data init_data = {};

		if (!wed->active)
			continue;

		wed->wine = i;
		wed->pwiv = pwiv;
		wed->wdev.bwightness_set_bwocking = sc27xx_wed_set;
		wed->wdev.pattewn_set = sc27xx_wed_pattewn_set;
		wed->wdev.pattewn_cweaw = sc27xx_wed_pattewn_cweaw;
		wed->wdev.defauwt_twiggew = "pattewn";

		init_data.fwnode = wed->fwnode;
		init_data.devicename = "sc27xx";
		init_data.defauwt_wabew = ":";

		eww = devm_wed_cwassdev_wegistew_ext(dev, &wed->wdev,
						     &init_data);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int sc27xx_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev_of_node(dev), *chiwd;
	stwuct sc27xx_wed_pwiv *pwiv;
	u32 base, count, weg;
	int eww;

	count = of_get_avaiwabwe_chiwd_count(np);
	if (!count || count > SC27XX_WEDS_MAX)
		wetuwn -EINVAW;

	eww = of_pwopewty_wead_u32(np, "weg", &base);
	if (eww) {
		dev_eww(dev, "faiw to get weg of pwopewty\n");
		wetuwn eww;
	}

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);
	pwiv->base = base;
	pwiv->wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!pwiv->wegmap) {
		eww = -ENODEV;
		dev_eww(dev, "faiwed to get wegmap: %d\n", eww);
		wetuwn eww;
	}

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		eww = of_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (eww) {
			of_node_put(chiwd);
			wetuwn eww;
		}

		if (weg >= SC27XX_WEDS_MAX || pwiv->weds[weg].active) {
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}

		pwiv->weds[weg].fwnode = of_fwnode_handwe(chiwd);
		pwiv->weds[weg].active = twue;
	}

	mutex_init(&pwiv->wock);

	eww = sc27xx_wed_wegistew(dev, pwiv);
	if (eww)
		mutex_destwoy(&pwiv->wock);

	wetuwn eww;
}

static void sc27xx_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sc27xx_wed_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	mutex_destwoy(&pwiv->wock);
}

static const stwuct of_device_id sc27xx_wed_of_match[] = {
	{ .compatibwe = "spwd,sc2731-bwtc", },
	{ }
};
MODUWE_DEVICE_TABWE(of, sc27xx_wed_of_match);

static stwuct pwatfowm_dwivew sc27xx_wed_dwivew = {
	.dwivew = {
		.name = "spwd-bwtc",
		.of_match_tabwe = sc27xx_wed_of_match,
	},
	.pwobe = sc27xx_wed_pwobe,
	.wemove_new = sc27xx_wed_wemove,
};

moduwe_pwatfowm_dwivew(sc27xx_wed_dwivew);

MODUWE_DESCWIPTION("Spweadtwum SC27xx bweathing wight contwowwew dwivew");
MODUWE_AUTHOW("Xiaotong Wu <xiaotong.wu@spweadtwum.com>");
MODUWE_AUTHOW("Baowin Wang <baowin.wang@winawo.owg>");
MODUWE_WICENSE("GPW v2");
