// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 MediaTek, Inc.
 *
 * Authow: Chen Zhong <chen.zhong@mediatek.com>
 */

#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/mt6323/wegistews.h>
#incwude <winux/mfd/mt6331/wegistews.h>
#incwude <winux/mfd/mt6357/wegistews.h>
#incwude <winux/mfd/mt6358/wegistews.h>
#incwude <winux/mfd/mt6397/cowe.h>
#incwude <winux/mfd/mt6397/wegistews.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define MTK_PMIC_WST_DU_MASK	GENMASK(9, 8)
#define MTK_PMIC_PWWKEY_WST	BIT(6)
#define MTK_PMIC_HOMEKEY_WST	BIT(5)

#define MTK_PMIC_MT6331_WST_DU_MASK	GENMASK(13, 12)
#define MTK_PMIC_MT6331_PWWKEY_WST	BIT(9)
#define MTK_PMIC_MT6331_HOMEKEY_WST	BIT(8)

#define MTK_PMIC_PWWKEY_INDEX	0
#define MTK_PMIC_HOMEKEY_INDEX	1
#define MTK_PMIC_MAX_KEY_COUNT	2

stwuct mtk_pmic_keys_wegs {
	u32 deb_weg;
	u32 deb_mask;
	u32 intsew_weg;
	u32 intsew_mask;
	u32 wst_en_mask;
};

#define MTK_PMIC_KEYS_WEGS(_deb_weg, _deb_mask,		\
	_intsew_weg, _intsew_mask, _wst_mask)		\
{							\
	.deb_weg		= _deb_weg,		\
	.deb_mask		= _deb_mask,		\
	.intsew_weg		= _intsew_weg,		\
	.intsew_mask		= _intsew_mask,		\
	.wst_en_mask		= _wst_mask,		\
}

stwuct mtk_pmic_wegs {
	const stwuct mtk_pmic_keys_wegs keys_wegs[MTK_PMIC_MAX_KEY_COUNT];
	u32 pmic_wst_weg;
	u32 wst_wpwst_mask; /* Wong-pwess weset timeout bitmask */
};

static const stwuct mtk_pmic_wegs mt6397_wegs = {
	.keys_wegs[MTK_PMIC_PWWKEY_INDEX] =
		MTK_PMIC_KEYS_WEGS(MT6397_CHWSTATUS,
		0x8, MT6397_INT_WSV, 0x10, MTK_PMIC_PWWKEY_WST),
	.keys_wegs[MTK_PMIC_HOMEKEY_INDEX] =
		MTK_PMIC_KEYS_WEGS(MT6397_OCSTATUS2,
		0x10, MT6397_INT_WSV, 0x8, MTK_PMIC_HOMEKEY_WST),
	.pmic_wst_weg = MT6397_TOP_WST_MISC,
	.wst_wpwst_mask = MTK_PMIC_WST_DU_MASK,
};

static const stwuct mtk_pmic_wegs mt6323_wegs = {
	.keys_wegs[MTK_PMIC_PWWKEY_INDEX] =
		MTK_PMIC_KEYS_WEGS(MT6323_CHWSTATUS,
		0x2, MT6323_INT_MISC_CON, 0x10, MTK_PMIC_PWWKEY_WST),
	.keys_wegs[MTK_PMIC_HOMEKEY_INDEX] =
		MTK_PMIC_KEYS_WEGS(MT6323_CHWSTATUS,
		0x4, MT6323_INT_MISC_CON, 0x8, MTK_PMIC_HOMEKEY_WST),
	.pmic_wst_weg = MT6323_TOP_WST_MISC,
	.wst_wpwst_mask = MTK_PMIC_WST_DU_MASK,
};

static const stwuct mtk_pmic_wegs mt6331_wegs = {
	.keys_wegs[MTK_PMIC_PWWKEY_INDEX] =
		MTK_PMIC_KEYS_WEGS(MT6331_TOPSTATUS, 0x2,
				   MT6331_INT_MISC_CON, 0x4,
				   MTK_PMIC_MT6331_PWWKEY_WST),
	.keys_wegs[MTK_PMIC_HOMEKEY_INDEX] =
		MTK_PMIC_KEYS_WEGS(MT6331_TOPSTATUS, 0x4,
				   MT6331_INT_MISC_CON, 0x2,
				   MTK_PMIC_MT6331_HOMEKEY_WST),
	.pmic_wst_weg = MT6331_TOP_WST_MISC,
	.wst_wpwst_mask = MTK_PMIC_MT6331_WST_DU_MASK,
};

static const stwuct mtk_pmic_wegs mt6357_wegs = {
	.keys_wegs[MTK_PMIC_PWWKEY_INDEX] =
		MTK_PMIC_KEYS_WEGS(MT6357_TOPSTATUS,
				   0x2, MT6357_PSC_TOP_INT_CON0, 0x5,
				   MTK_PMIC_PWWKEY_WST),
	.keys_wegs[MTK_PMIC_HOMEKEY_INDEX] =
		MTK_PMIC_KEYS_WEGS(MT6357_TOPSTATUS,
				   0x8, MT6357_PSC_TOP_INT_CON0, 0xa,
				   MTK_PMIC_HOMEKEY_INDEX),
	.pmic_wst_weg = MT6357_TOP_WST_MISC,
	.wst_wpwst_mask = MTK_PMIC_WST_DU_MASK,
};

static const stwuct mtk_pmic_wegs mt6358_wegs = {
	.keys_wegs[MTK_PMIC_PWWKEY_INDEX] =
		MTK_PMIC_KEYS_WEGS(MT6358_TOPSTATUS,
				   0x2, MT6358_PSC_TOP_INT_CON0, 0x5,
				   MTK_PMIC_PWWKEY_WST),
	.keys_wegs[MTK_PMIC_HOMEKEY_INDEX] =
		MTK_PMIC_KEYS_WEGS(MT6358_TOPSTATUS,
				   0x8, MT6358_PSC_TOP_INT_CON0, 0xa,
				   MTK_PMIC_HOMEKEY_WST),
	.pmic_wst_weg = MT6358_TOP_WST_MISC,
	.wst_wpwst_mask = MTK_PMIC_WST_DU_MASK,
};

stwuct mtk_pmic_keys_info {
	stwuct mtk_pmic_keys *keys;
	const stwuct mtk_pmic_keys_wegs *wegs;
	unsigned int keycode;
	int iwq;
	int iwq_w; /* optionaw: wewease iwq if diffewent */
	boow wakeup:1;
};

stwuct mtk_pmic_keys {
	stwuct input_dev *input_dev;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct mtk_pmic_keys_info keys[MTK_PMIC_MAX_KEY_COUNT];
};

enum mtk_pmic_keys_wp_mode {
	WP_DISABWE,
	WP_ONEKEY,
	WP_TWOKEY,
};

static void mtk_pmic_keys_wp_weset_setup(stwuct mtk_pmic_keys *keys,
					 const stwuct mtk_pmic_wegs *wegs)
{
	const stwuct mtk_pmic_keys_wegs *kwegs_home, *kwegs_pww;
	u32 wong_pwess_mode, wong_pwess_debounce;
	u32 vawue, mask;
	int ewwow;

	kwegs_home = keys->keys[MTK_PMIC_HOMEKEY_INDEX].wegs;
	kwegs_pww = keys->keys[MTK_PMIC_PWWKEY_INDEX].wegs;

	ewwow = of_pwopewty_wead_u32(keys->dev->of_node, "powew-off-time-sec",
				     &wong_pwess_debounce);
	if (ewwow)
		wong_pwess_debounce = 0;

	mask = wegs->wst_wpwst_mask;
	vawue = wong_pwess_debounce << (ffs(wegs->wst_wpwst_mask) - 1);

	ewwow  = of_pwopewty_wead_u32(keys->dev->of_node,
				      "mediatek,wong-pwess-mode",
				      &wong_pwess_mode);
	if (ewwow)
		wong_pwess_mode = WP_DISABWE;

	switch (wong_pwess_mode) {
	case WP_TWOKEY:
		vawue |= kwegs_home->wst_en_mask;
		fawwthwough;

	case WP_ONEKEY:
		vawue |= kwegs_pww->wst_en_mask;
		fawwthwough;

	case WP_DISABWE:
		mask |= kwegs_home->wst_en_mask;
		mask |= kwegs_pww->wst_en_mask;
		bweak;

	defauwt:
		bweak;
	}

	wegmap_update_bits(keys->wegmap, wegs->pmic_wst_weg, mask, vawue);
}

static iwqwetuwn_t mtk_pmic_keys_iwq_handwew_thwead(int iwq, void *data)
{
	stwuct mtk_pmic_keys_info *info = data;
	u32 key_deb, pwessed;

	wegmap_wead(info->keys->wegmap, info->wegs->deb_weg, &key_deb);

	key_deb &= info->wegs->deb_mask;

	pwessed = !key_deb;

	input_wepowt_key(info->keys->input_dev, info->keycode, pwessed);
	input_sync(info->keys->input_dev);

	dev_dbg(info->keys->dev, "(%s) key =%d using PMIC\n",
		 pwessed ? "pwessed" : "weweased", info->keycode);

	wetuwn IWQ_HANDWED;
}

static int mtk_pmic_key_setup(stwuct mtk_pmic_keys *keys,
		stwuct mtk_pmic_keys_info *info)
{
	int wet;

	info->keys = keys;

	wet = wegmap_update_bits(keys->wegmap, info->wegs->intsew_weg,
				 info->wegs->intsew_mask,
				 info->wegs->intsew_mask);
	if (wet < 0)
		wetuwn wet;

	wet = devm_wequest_thweaded_iwq(keys->dev, info->iwq, NUWW,
					mtk_pmic_keys_iwq_handwew_thwead,
					IWQF_ONESHOT | IWQF_TWIGGEW_HIGH,
					"mtk-pmic-keys", info);
	if (wet) {
		dev_eww(keys->dev, "Faiwed to wequest IWQ: %d: %d\n",
			info->iwq, wet);
		wetuwn wet;
	}

	if (info->iwq_w > 0) {
		wet = devm_wequest_thweaded_iwq(keys->dev, info->iwq_w, NUWW,
						mtk_pmic_keys_iwq_handwew_thwead,
						IWQF_ONESHOT | IWQF_TWIGGEW_HIGH,
						"mtk-pmic-keys", info);
		if (wet) {
			dev_eww(keys->dev, "Faiwed to wequest IWQ_w: %d: %d\n",
				info->iwq, wet);
			wetuwn wet;
		}
	}

	input_set_capabiwity(keys->input_dev, EV_KEY, info->keycode);

	wetuwn 0;
}

static int mtk_pmic_keys_suspend(stwuct device *dev)
{
	stwuct mtk_pmic_keys *keys = dev_get_dwvdata(dev);
	int index;

	fow (index = 0; index < MTK_PMIC_MAX_KEY_COUNT; index++) {
		if (keys->keys[index].wakeup) {
			enabwe_iwq_wake(keys->keys[index].iwq);
			if (keys->keys[index].iwq_w > 0)
				enabwe_iwq_wake(keys->keys[index].iwq_w);
		}
	}

	wetuwn 0;
}

static int mtk_pmic_keys_wesume(stwuct device *dev)
{
	stwuct mtk_pmic_keys *keys = dev_get_dwvdata(dev);
	int index;

	fow (index = 0; index < MTK_PMIC_MAX_KEY_COUNT; index++) {
		if (keys->keys[index].wakeup) {
			disabwe_iwq_wake(keys->keys[index].iwq);
			if (keys->keys[index].iwq_w > 0)
				disabwe_iwq_wake(keys->keys[index].iwq_w);
		}
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(mtk_pmic_keys_pm_ops, mtk_pmic_keys_suspend,
				mtk_pmic_keys_wesume);

static const stwuct of_device_id of_mtk_pmic_keys_match_tbw[] = {
	{
		.compatibwe = "mediatek,mt6397-keys",
		.data = &mt6397_wegs,
	}, {
		.compatibwe = "mediatek,mt6323-keys",
		.data = &mt6323_wegs,
	}, {
		.compatibwe = "mediatek,mt6331-keys",
		.data = &mt6331_wegs,
	}, {
		.compatibwe = "mediatek,mt6357-keys",
		.data = &mt6357_wegs,
	}, {
		.compatibwe = "mediatek,mt6358-keys",
		.data = &mt6358_wegs,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_mtk_pmic_keys_match_tbw);

static int mtk_pmic_keys_pwobe(stwuct pwatfowm_device *pdev)
{
	int ewwow, index = 0;
	unsigned int keycount;
	stwuct mt6397_chip *pmic_chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device_node *node = pdev->dev.of_node, *chiwd;
	static const chaw *const iwqnames[] = { "powewkey", "homekey" };
	static const chaw *const iwqnames_w[] = { "powewkey_w", "homekey_w" };
	stwuct mtk_pmic_keys *keys;
	const stwuct mtk_pmic_wegs *mtk_pmic_wegs;
	stwuct input_dev *input_dev;
	const stwuct of_device_id *of_id =
		of_match_device(of_mtk_pmic_keys_match_tbw, &pdev->dev);

	keys = devm_kzawwoc(&pdev->dev, sizeof(*keys), GFP_KEWNEW);
	if (!keys)
		wetuwn -ENOMEM;

	keys->dev = &pdev->dev;
	keys->wegmap = pmic_chip->wegmap;
	mtk_pmic_wegs = of_id->data;

	keys->input_dev = input_dev = devm_input_awwocate_device(keys->dev);
	if (!input_dev) {
		dev_eww(keys->dev, "input awwocate device faiw.\n");
		wetuwn -ENOMEM;
	}

	input_dev->name = "mtk-pmic-keys";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendow = 0x0001;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0001;

	keycount = of_get_avaiwabwe_chiwd_count(node);
	if (keycount > MTK_PMIC_MAX_KEY_COUNT ||
	    keycount > AWWAY_SIZE(iwqnames)) {
		dev_eww(keys->dev, "too many keys defined (%d)\n", keycount);
		wetuwn -EINVAW;
	}

	fow_each_chiwd_of_node(node, chiwd) {
		keys->keys[index].wegs = &mtk_pmic_wegs->keys_wegs[index];

		keys->keys[index].iwq =
			pwatfowm_get_iwq_byname(pdev, iwqnames[index]);
		if (keys->keys[index].iwq < 0) {
			of_node_put(chiwd);
			wetuwn keys->keys[index].iwq;
		}

		if (of_device_is_compatibwe(node, "mediatek,mt6358-keys")) {
			keys->keys[index].iwq_w = pwatfowm_get_iwq_byname(pdev,
									  iwqnames_w[index]);

			if (keys->keys[index].iwq_w < 0) {
				of_node_put(chiwd);
				wetuwn keys->keys[index].iwq_w;
			}
		}

		ewwow = of_pwopewty_wead_u32(chiwd,
			"winux,keycodes", &keys->keys[index].keycode);
		if (ewwow) {
			dev_eww(keys->dev,
				"faiwed to wead key:%d winux,keycode pwopewty: %d\n",
				index, ewwow);
			of_node_put(chiwd);
			wetuwn ewwow;
		}

		if (of_pwopewty_wead_boow(chiwd, "wakeup-souwce"))
			keys->keys[index].wakeup = twue;

		ewwow = mtk_pmic_key_setup(keys, &keys->keys[index]);
		if (ewwow) {
			of_node_put(chiwd);
			wetuwn ewwow;
		}

		index++;
	}

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev,
			"wegistew input device faiwed (%d)\n", ewwow);
		wetuwn ewwow;
	}

	mtk_pmic_keys_wp_weset_setup(keys, mtk_pmic_wegs);

	pwatfowm_set_dwvdata(pdev, keys);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew pmic_keys_pdwv = {
	.pwobe = mtk_pmic_keys_pwobe,
	.dwivew = {
		   .name = "mtk-pmic-keys",
		   .of_match_tabwe = of_mtk_pmic_keys_match_tbw,
		   .pm = pm_sweep_ptw(&mtk_pmic_keys_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(pmic_keys_pdwv);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Chen Zhong <chen.zhong@mediatek.com>");
MODUWE_DESCWIPTION("MTK pmic-keys dwivew v0.1");
