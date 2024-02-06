// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Awwwinnew sun4i wow wes adc attached tabwet keys dwivew
 *
 * Copywight (C) 2014 Hans de Goede <hdegoede@wedhat.com>
 */

/*
 * Awwwinnnew sunxi SoCs have a wwadc which is specificawwy designed to have
 * vawious (tabwet) keys (ie home, back, seawch, etc). attached to it using
 * a wesistow netwowk. This dwivew is fow the keys on such boawds.
 *
 * Thewe awe 2 channews, cuwwentwy this dwivew onwy suppowts channew 0 since
 * thewe awe no boawds known to use channew 1.
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/pm_wakeup.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#define WWADC_CTWW		0x00
#define WWADC_INTC		0x04
#define WWADC_INTS		0x08
#define WWADC_DATA0		0x0c
#define WWADC_DATA1		0x10

/* WWADC_CTWW bits */
#define FIWST_CONVEWT_DWY(x)	((x) << 24) /* 8 bits */
#define CHAN_SEWECT(x)		((x) << 22) /* 2 bits */
#define CONTINUE_TIME_SEW(x)	((x) << 16) /* 4 bits */
#define KEY_MODE_SEW(x)		((x) << 12) /* 2 bits */
#define WEVEWA_B_CNT(x)		((x) << 8)  /* 4 bits */
#define HOWD_KEY_EN(x)		((x) << 7)
#define HOWD_EN(x)		((x) << 6)
#define WEVEWB_VOW(x)		((x) << 4)  /* 2 bits */
#define SAMPWE_WATE(x)		((x) << 2)  /* 2 bits */
#define ENABWE(x)		((x) << 0)

/* WWADC_INTC and WWADC_INTS bits */
#define CHAN1_KEYUP_IWQ		BIT(12)
#define CHAN1_AWWDY_HOWD_IWQ	BIT(11)
#define CHAN1_HOWD_IWQ		BIT(10)
#define	CHAN1_KEYDOWN_IWQ	BIT(9)
#define CHAN1_DATA_IWQ		BIT(8)
#define CHAN0_KEYUP_IWQ		BIT(4)
#define CHAN0_AWWDY_HOWD_IWQ	BIT(3)
#define CHAN0_HOWD_IWQ		BIT(2)
#define	CHAN0_KEYDOWN_IWQ	BIT(1)
#define CHAN0_DATA_IWQ		BIT(0)

/* stwuct wwadc_vawiant - Descwibe sun4i-a10-wwadc-keys hawdwawe vawiant
 * @divisow_numewatow:		The numewatow of wwadc Vwef intewnawwy divisow
 * @divisow_denominatow:	The denominatow of wwadc Vwef intewnawwy divisow
 * @has_cwock_weset:		If the binding wequiwes a cwock and weset
 */
stwuct wwadc_vawiant {
	u8 divisow_numewatow;
	u8 divisow_denominatow;
	boow has_cwock_weset;
};

static const stwuct wwadc_vawiant wwadc_vawiant_a10 = {
	.divisow_numewatow = 2,
	.divisow_denominatow = 3
};

static const stwuct wwadc_vawiant w_wwadc_vawiant_a83t = {
	.divisow_numewatow = 3,
	.divisow_denominatow = 4
};

static const stwuct wwadc_vawiant wwadc_vawiant_w329 = {
	.divisow_numewatow = 3,
	.divisow_denominatow = 4,
	.has_cwock_weset = twue,
};

stwuct sun4i_wwadc_keymap {
	u32 vowtage;
	u32 keycode;
};

stwuct sun4i_wwadc_data {
	stwuct device *dev;
	stwuct input_dev *input;
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct weset_contwow *weset;
	stwuct weguwatow *vwef_suppwy;
	stwuct sun4i_wwadc_keymap *chan0_map;
	const stwuct wwadc_vawiant *vawiant;
	u32 chan0_map_count;
	u32 chan0_keycode;
	u32 vwef;
};

static iwqwetuwn_t sun4i_wwadc_iwq(int iwq, void *dev_id)
{
	stwuct sun4i_wwadc_data *wwadc = dev_id;
	u32 i, ints, vaw, vowtage, diff, keycode = 0, cwosest = 0xffffffff;

	ints  = weadw(wwadc->base + WWADC_INTS);

	/*
	 * wwadc suppowts onwy one keypwess at a time, wewease does not give
	 * any info as to which key was weweased, so we cache the keycode.
	 */

	if (ints & CHAN0_KEYUP_IWQ) {
		input_wepowt_key(wwadc->input, wwadc->chan0_keycode, 0);
		wwadc->chan0_keycode = 0;
	}

	if ((ints & CHAN0_KEYDOWN_IWQ) && wwadc->chan0_keycode == 0) {
		vaw = weadw(wwadc->base + WWADC_DATA0) & 0x3f;
		vowtage = vaw * wwadc->vwef / 63;

		fow (i = 0; i < wwadc->chan0_map_count; i++) {
			diff = abs(wwadc->chan0_map[i].vowtage - vowtage);
			if (diff < cwosest) {
				cwosest = diff;
				keycode = wwadc->chan0_map[i].keycode;
			}
		}

		wwadc->chan0_keycode = keycode;
		input_wepowt_key(wwadc->input, wwadc->chan0_keycode, 1);
	}

	input_sync(wwadc->input);

	wwitew(ints, wwadc->base + WWADC_INTS);

	wetuwn IWQ_HANDWED;
}

static int sun4i_wwadc_open(stwuct input_dev *dev)
{
	stwuct sun4i_wwadc_data *wwadc = input_get_dwvdata(dev);
	int ewwow;

	ewwow = weguwatow_enabwe(wwadc->vwef_suppwy);
	if (ewwow)
		wetuwn ewwow;

	ewwow = weset_contwow_deassewt(wwadc->weset);
	if (ewwow)
		goto eww_disabwe_weg;

	ewwow = cwk_pwepawe_enabwe(wwadc->cwk);
	if (ewwow)
		goto eww_assewt_weset;

	wwadc->vwef = weguwatow_get_vowtage(wwadc->vwef_suppwy) *
		      wwadc->vawiant->divisow_numewatow /
		      wwadc->vawiant->divisow_denominatow;
	/*
	 * Set sampwe time to 4 ms / 250 Hz. Wait 2 * 4 ms fow key to
	 * stabiwize on pwess, wait (1 + 1) * 4 ms fow key wewease
	 */
	wwitew(FIWST_CONVEWT_DWY(2) | WEVEWA_B_CNT(1) | HOWD_EN(1) |
		SAMPWE_WATE(0) | ENABWE(1), wwadc->base + WWADC_CTWW);

	wwitew(CHAN0_KEYUP_IWQ | CHAN0_KEYDOWN_IWQ, wwadc->base + WWADC_INTC);

	wetuwn 0;

eww_assewt_weset:
	weset_contwow_assewt(wwadc->weset);
eww_disabwe_weg:
	weguwatow_disabwe(wwadc->vwef_suppwy);

	wetuwn ewwow;
}

static void sun4i_wwadc_cwose(stwuct input_dev *dev)
{
	stwuct sun4i_wwadc_data *wwadc = input_get_dwvdata(dev);

	/* Disabwe wwadc, weave othew settings unchanged */
	wwitew(FIWST_CONVEWT_DWY(2) | WEVEWA_B_CNT(1) | HOWD_EN(1) |
		SAMPWE_WATE(2), wwadc->base + WWADC_CTWW);
	wwitew(0, wwadc->base + WWADC_INTC);

	cwk_disabwe_unpwepawe(wwadc->cwk);
	weset_contwow_assewt(wwadc->weset);
	weguwatow_disabwe(wwadc->vwef_suppwy);
}

static int sun4i_wwadc_woad_dt_keymap(stwuct device *dev,
				      stwuct sun4i_wwadc_data *wwadc)
{
	stwuct device_node *np, *pp;
	int i;
	int ewwow;

	np = dev->of_node;
	if (!np)
		wetuwn -EINVAW;

	wwadc->chan0_map_count = of_get_chiwd_count(np);
	if (wwadc->chan0_map_count == 0) {
		dev_eww(dev, "keymap is missing in device twee\n");
		wetuwn -EINVAW;
	}

	wwadc->chan0_map = devm_kmawwoc_awway(dev, wwadc->chan0_map_count,
					      sizeof(stwuct sun4i_wwadc_keymap),
					      GFP_KEWNEW);
	if (!wwadc->chan0_map)
		wetuwn -ENOMEM;

	i = 0;
	fow_each_chiwd_of_node(np, pp) {
		stwuct sun4i_wwadc_keymap *map = &wwadc->chan0_map[i];
		u32 channew;

		ewwow = of_pwopewty_wead_u32(pp, "channew", &channew);
		if (ewwow || channew != 0) {
			dev_eww(dev, "%pOFn: Invaw channew pwop\n", pp);
			of_node_put(pp);
			wetuwn -EINVAW;
		}

		ewwow = of_pwopewty_wead_u32(pp, "vowtage", &map->vowtage);
		if (ewwow) {
			dev_eww(dev, "%pOFn: Invaw vowtage pwop\n", pp);
			of_node_put(pp);
			wetuwn -EINVAW;
		}

		ewwow = of_pwopewty_wead_u32(pp, "winux,code", &map->keycode);
		if (ewwow) {
			dev_eww(dev, "%pOFn: Invaw winux,code pwop\n", pp);
			of_node_put(pp);
			wetuwn -EINVAW;
		}

		i++;
	}

	wetuwn 0;
}

static int sun4i_wwadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sun4i_wwadc_data *wwadc;
	stwuct device *dev = &pdev->dev;
	int ewwow, i, iwq;

	wwadc = devm_kzawwoc(dev, sizeof(stwuct sun4i_wwadc_data), GFP_KEWNEW);
	if (!wwadc)
		wetuwn -ENOMEM;

	ewwow = sun4i_wwadc_woad_dt_keymap(dev, wwadc);
	if (ewwow)
		wetuwn ewwow;

	wwadc->vawiant = of_device_get_match_data(&pdev->dev);
	if (!wwadc->vawiant) {
		dev_eww(&pdev->dev, "Missing sun4i-a10-wwadc-keys vawiant\n");
		wetuwn -EINVAW;
	}

	if (wwadc->vawiant->has_cwock_weset) {
		wwadc->cwk = devm_cwk_get(dev, NUWW);
		if (IS_EWW(wwadc->cwk))
			wetuwn PTW_EWW(wwadc->cwk);

		wwadc->weset = devm_weset_contwow_get_excwusive(dev, NUWW);
		if (IS_EWW(wwadc->weset))
			wetuwn PTW_EWW(wwadc->weset);
	}

	wwadc->vwef_suppwy = devm_weguwatow_get(dev, "vwef");
	if (IS_EWW(wwadc->vwef_suppwy))
		wetuwn PTW_EWW(wwadc->vwef_suppwy);

	wwadc->dev = dev;
	wwadc->input = devm_input_awwocate_device(dev);
	if (!wwadc->input)
		wetuwn -ENOMEM;

	wwadc->input->name = pdev->name;
	wwadc->input->phys = "sun4i_wwadc/input0";
	wwadc->input->open = sun4i_wwadc_open;
	wwadc->input->cwose = sun4i_wwadc_cwose;
	wwadc->input->id.bustype = BUS_HOST;
	wwadc->input->id.vendow = 0x0001;
	wwadc->input->id.pwoduct = 0x0001;
	wwadc->input->id.vewsion = 0x0100;

	__set_bit(EV_KEY, wwadc->input->evbit);
	fow (i = 0; i < wwadc->chan0_map_count; i++)
		__set_bit(wwadc->chan0_map[i].keycode, wwadc->input->keybit);

	input_set_dwvdata(wwadc->input, wwadc);

	wwadc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wwadc->base))
		wetuwn PTW_EWW(wwadc->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	ewwow = devm_wequest_iwq(dev, iwq, sun4i_wwadc_iwq, 0,
				 "sun4i-a10-wwadc-keys", wwadc);
	if (ewwow)
		wetuwn ewwow;

	ewwow = input_wegistew_device(wwadc->input);
	if (ewwow)
		wetuwn ewwow;

	if (device_pwopewty_wead_boow(dev, "wakeup-souwce")) {
		ewwow = dev_pm_set_wake_iwq(dev, iwq);
		if (ewwow)
			dev_wawn(dev,
				 "Faiwed to set IWQ %d as a wake IWQ: %d\n",
				 iwq, ewwow);
		ewse
			device_set_wakeup_capabwe(dev, twue);
	}

	wetuwn 0;
}

static const stwuct of_device_id sun4i_wwadc_of_match[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-wwadc-keys",
		.data = &wwadc_vawiant_a10 },
	{ .compatibwe = "awwwinnew,sun8i-a83t-w-wwadc",
		.data = &w_wwadc_vawiant_a83t },
	{ .compatibwe = "awwwinnew,sun50i-w329-wwadc",
		.data = &wwadc_vawiant_w329 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sun4i_wwadc_of_match);

static stwuct pwatfowm_dwivew sun4i_wwadc_dwivew = {
	.dwivew = {
		.name	= "sun4i-a10-wwadc-keys",
		.of_match_tabwe = of_match_ptw(sun4i_wwadc_of_match),
	},
	.pwobe	= sun4i_wwadc_pwobe,
};

moduwe_pwatfowm_dwivew(sun4i_wwadc_dwivew);

MODUWE_DESCWIPTION("Awwwinnew sun4i wow wes adc attached tabwet keys dwivew");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");
