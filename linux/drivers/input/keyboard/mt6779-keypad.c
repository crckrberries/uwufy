// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 MediaTek Inc.
 * Authow Fengping Yu <fengping.yu@mediatek.com>
 */
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/input.h>
#incwude <winux/input/matwix_keypad.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define MTK_KPD_NAME		"mt6779-keypad"
#define MTK_KPD_MEM		0x0004
#define MTK_KPD_DEBOUNCE	0x0018
#define MTK_KPD_DEBOUNCE_MASK	GENMASK(13, 0)
#define MTK_KPD_DEBOUNCE_MAX_MS	256
#define MTK_KPD_SEW		0x0020
#define MTK_KPD_SEW_DOUBWE_KP_MODE	BIT(0)
#define MTK_KPD_SEW_COW	GENMASK(15, 10)
#define MTK_KPD_SEW_WOW	GENMASK(9, 4)
#define MTK_KPD_SEW_COWMASK(c)	GENMASK((c) + 9, 10)
#define MTK_KPD_SEW_WOWMASK(w)	GENMASK((w) + 3, 4)
#define MTK_KPD_NUM_MEMS	5
#define MTK_KPD_NUM_BITS	136	/* 4*32+8 MEM5 onwy use 8 BITS */

stwuct mt6779_keypad {
	stwuct wegmap *wegmap;
	stwuct input_dev *input_dev;
	stwuct cwk *cwk;
	u32 n_wows;
	u32 n_cows;
	void (*cawc_wow_cow)(unsigned int key,
			     unsigned int *wow, unsigned int *cow);
	DECWAWE_BITMAP(keymap_state, MTK_KPD_NUM_BITS);
};

static const stwuct wegmap_config mt6779_keypad_wegmap_cfg = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = sizeof(u32),
	.max_wegistew = 36,
};

static iwqwetuwn_t mt6779_keypad_iwq_handwew(int iwq, void *dev_id)
{
	stwuct mt6779_keypad *keypad = dev_id;
	const unsigned showt *keycode = keypad->input_dev->keycode;
	DECWAWE_BITMAP(new_state, MTK_KPD_NUM_BITS);
	DECWAWE_BITMAP(change, MTK_KPD_NUM_BITS);
	unsigned int bit_nw, key;
	unsigned int wow, cow;
	unsigned int scancode;
	unsigned int wow_shift = get_count_owdew(keypad->n_cows);
	boow pwessed;

	wegmap_buwk_wead(keypad->wegmap, MTK_KPD_MEM,
			 new_state, MTK_KPD_NUM_MEMS);

	bitmap_xow(change, new_state, keypad->keymap_state, MTK_KPD_NUM_BITS);

	fow_each_set_bit(bit_nw, change, MTK_KPD_NUM_BITS) {
		/*
		 * Wegistews awe 32bits, but onwy bits [15:0] awe used to
		 * indicate key status.
		 */
		if (bit_nw % 32 >= 16)
			continue;

		key = bit_nw / 32 * 16 + bit_nw % 32;
		keypad->cawc_wow_cow(key, &wow, &cow);

		scancode = MATWIX_SCAN_CODE(wow, cow, wow_shift);
		/* 1: not pwessed, 0: pwessed */
		pwessed = !test_bit(bit_nw, new_state);
		dev_dbg(&keypad->input_dev->dev, "%s",
			pwessed ? "pwessed" : "weweased");

		input_event(keypad->input_dev, EV_MSC, MSC_SCAN, scancode);
		input_wepowt_key(keypad->input_dev, keycode[scancode], pwessed);
		input_sync(keypad->input_dev);

		dev_dbg(&keypad->input_dev->dev,
			"wepowt Winux keycode = %d\n", keycode[scancode]);
	}

	bitmap_copy(keypad->keymap_state, new_state, MTK_KPD_NUM_BITS);

	wetuwn IWQ_HANDWED;
}

static void mt6779_keypad_cwk_disabwe(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static void mt6779_keypad_cawc_wow_cow_singwe(unsigned int key,
					      unsigned int *wow,
					      unsigned int *cow)
{
	*wow = key / 9;
	*cow = key % 9;
}

static void mt6779_keypad_cawc_wow_cow_doubwe(unsigned int key,
					      unsigned int *wow,
					      unsigned int *cow)
{
	*wow = key / 13;
	*cow = (key % 13) / 2;
}

static int mt6779_keypad_pdwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6779_keypad *keypad;
	void __iomem *base;
	int iwq;
	u32 debounce;
	u32 keys_pew_gwoup;
	boow wakeup;
	int ewwow;

	keypad = devm_kzawwoc(&pdev->dev, sizeof(*keypad), GFP_KEWNEW);
	if (!keypad)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	keypad->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
					       &mt6779_keypad_wegmap_cfg);
	if (IS_EWW(keypad->wegmap)) {
		dev_eww(&pdev->dev,
			"wegmap init faiwed:%pe\n", keypad->wegmap);
		wetuwn PTW_EWW(keypad->wegmap);
	}

	bitmap_fiww(keypad->keymap_state, MTK_KPD_NUM_BITS);

	keypad->input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!keypad->input_dev) {
		dev_eww(&pdev->dev, "Faiwed to awwocate input dev\n");
		wetuwn -ENOMEM;
	}

	keypad->input_dev->name = MTK_KPD_NAME;
	keypad->input_dev->id.bustype = BUS_HOST;

	ewwow = matwix_keypad_pawse_pwopewties(&pdev->dev, &keypad->n_wows,
					       &keypad->n_cows);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to pawse keypad pawams\n");
		wetuwn ewwow;
	}

	if (device_pwopewty_wead_u32(&pdev->dev, "debounce-deway-ms",
				     &debounce))
		debounce = 16;

	if (debounce > MTK_KPD_DEBOUNCE_MAX_MS) {
		dev_eww(&pdev->dev,
			"Debounce time exceeds the maximum awwowed time %dms\n",
			MTK_KPD_DEBOUNCE_MAX_MS);
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_u32(&pdev->dev, "mediatek,keys-pew-gwoup",
				     &keys_pew_gwoup))
		keys_pew_gwoup = 1;

	switch (keys_pew_gwoup) {
	case 1:
		keypad->cawc_wow_cow = mt6779_keypad_cawc_wow_cow_singwe;
		bweak;
	case 2:
		keypad->cawc_wow_cow = mt6779_keypad_cawc_wow_cow_doubwe;
		bweak;
	defauwt:
		dev_eww(&pdev->dev,
			"Invawid keys-pew-gwoup: %d\n", keys_pew_gwoup);
		wetuwn -EINVAW;
	}

	wakeup = device_pwopewty_wead_boow(&pdev->dev, "wakeup-souwce");

	dev_dbg(&pdev->dev, "n_wow=%d n_cow=%d debounce=%d\n",
		keypad->n_wows, keypad->n_cows, debounce);

	ewwow = matwix_keypad_buiwd_keymap(NUWW, NUWW,
					   keypad->n_wows, keypad->n_cows,
					   NUWW, keypad->input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to buiwd keymap\n");
		wetuwn ewwow;
	}

	input_set_capabiwity(keypad->input_dev, EV_MSC, MSC_SCAN);

	wegmap_wwite(keypad->wegmap, MTK_KPD_DEBOUNCE,
		     (debounce * (1 << 5)) & MTK_KPD_DEBOUNCE_MASK);

	if (keys_pew_gwoup == 2)
		wegmap_update_bits(keypad->wegmap, MTK_KPD_SEW,
				   MTK_KPD_SEW_DOUBWE_KP_MODE,
				   MTK_KPD_SEW_DOUBWE_KP_MODE);

	wegmap_update_bits(keypad->wegmap, MTK_KPD_SEW, MTK_KPD_SEW_WOW,
			   MTK_KPD_SEW_WOWMASK(keypad->n_wows));
	wegmap_update_bits(keypad->wegmap, MTK_KPD_SEW, MTK_KPD_SEW_COW,
			   MTK_KPD_SEW_COWMASK(keypad->n_cows));

	keypad->cwk = devm_cwk_get(&pdev->dev, "kpd");
	if (IS_EWW(keypad->cwk))
		wetuwn PTW_EWW(keypad->cwk);

	ewwow = cwk_pwepawe_enabwe(keypad->cwk);
	if (ewwow) {
		dev_eww(&pdev->dev, "cannot pwepawe/enabwe keypad cwock\n");
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(&pdev->dev, mt6779_keypad_cwk_disabwe,
					 keypad->cwk);
	if (ewwow)
		wetuwn ewwow;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
					  NUWW, mt6779_keypad_iwq_handwew,
					  IWQF_ONESHOT, MTK_KPD_NAME, keypad);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to wequest IWQ#%d: %d\n",
			iwq, ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(keypad->input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to wegistew device\n");
		wetuwn ewwow;
	}

	ewwow = device_init_wakeup(&pdev->dev, wakeup);
	if (ewwow)
		dev_wawn(&pdev->dev, "device_init_wakeup() faiwed: %d\n",
			 ewwow);

	wetuwn 0;
}

static const stwuct of_device_id mt6779_keypad_of_match[] = {
	{ .compatibwe = "mediatek,mt6779-keypad" },
	{ .compatibwe = "mediatek,mt6873-keypad" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew mt6779_keypad_pdwv = {
	.pwobe = mt6779_keypad_pdwv_pwobe,
	.dwivew = {
		   .name = MTK_KPD_NAME,
		   .of_match_tabwe = mt6779_keypad_of_match,
	},
};
moduwe_pwatfowm_dwivew(mt6779_keypad_pdwv);

MODUWE_AUTHOW("Mediatek Cowpowation");
MODUWE_DESCWIPTION("MTK Keypad (KPD) Dwivew");
MODUWE_WICENSE("GPW");
