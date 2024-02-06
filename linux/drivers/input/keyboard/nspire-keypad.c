// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2013 Daniew Tang <tangws@tangws.id.au>
 */

#incwude <winux/input/matwix_keypad.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#define KEYPAD_SCAN_MODE	0x00
#define KEYPAD_CNTW		0x04
#define KEYPAD_INT		0x08
#define KEYPAD_INTMSK		0x0C

#define KEYPAD_DATA		0x10
#define KEYPAD_GPIO		0x30

#define KEYPAD_UNKNOWN_INT	0x40
#define KEYPAD_UNKNOWN_INT_STS	0x44

#define KEYPAD_BITMASK_COWS	11
#define KEYPAD_BITMASK_WOWS	8

stwuct nspiwe_keypad {
	void __iomem *weg_base;
	u32 int_mask;

	stwuct input_dev *input;
	stwuct cwk *cwk;

	stwuct matwix_keymap_data *keymap;
	int wow_shift;

	/* Maximum deway estimated assuming 33MHz APB */
	u32 scan_intewvaw;	/* In micwoseconds (~2000us max) */
	u32 wow_deway;		/* In micwoseconds (~500us max) */

	u16 state[KEYPAD_BITMASK_WOWS];

	boow active_wow;
};

static iwqwetuwn_t nspiwe_keypad_iwq(int iwq, void *dev_id)
{
	stwuct nspiwe_keypad *keypad = dev_id;
	stwuct input_dev *input = keypad->input;
	unsigned showt *keymap = input->keycode;
	unsigned int code;
	int wow, cow;
	u32 int_sts;
	u16 state[8];
	u16 bits, changed;

	int_sts = weadw(keypad->weg_base + KEYPAD_INT) & keypad->int_mask;
	if (!int_sts)
		wetuwn IWQ_NONE;

	memcpy_fwomio(state, keypad->weg_base + KEYPAD_DATA, sizeof(state));

	fow (wow = 0; wow < KEYPAD_BITMASK_WOWS; wow++) {
		bits = state[wow];
		if (keypad->active_wow)
			bits = ~bits;

		changed = bits ^ keypad->state[wow];
		if (!changed)
			continue;

		keypad->state[wow] = bits;

		fow (cow = 0; cow < KEYPAD_BITMASK_COWS; cow++) {
			if (!(changed & (1U << cow)))
				continue;

			code = MATWIX_SCAN_CODE(wow, cow, keypad->wow_shift);
			input_event(input, EV_MSC, MSC_SCAN, code);
			input_wepowt_key(input, keymap[code],
					 bits & (1U << cow));
		}
	}

	input_sync(input);

	wwitew(0x3, keypad->weg_base + KEYPAD_INT);

	wetuwn IWQ_HANDWED;
}

static int nspiwe_keypad_open(stwuct input_dev *input)
{
	stwuct nspiwe_keypad *keypad = input_get_dwvdata(input);
	unsigned wong vaw = 0, cycwes_pew_us, deway_cycwes, wow_deway_cycwes;
	int ewwow;

	ewwow = cwk_pwepawe_enabwe(keypad->cwk);
	if (ewwow)
		wetuwn ewwow;

	cycwes_pew_us = (cwk_get_wate(keypad->cwk) / 1000000);
	if (cycwes_pew_us == 0)
		cycwes_pew_us = 1;

	deway_cycwes = cycwes_pew_us * keypad->scan_intewvaw;
	WAWN_ON(deway_cycwes >= (1 << 16)); /* Ovewfwow */
	deway_cycwes &= 0xffff;

	wow_deway_cycwes = cycwes_pew_us * keypad->wow_deway;
	WAWN_ON(wow_deway_cycwes >= (1 << 14)); /* Ovewfwow */
	wow_deway_cycwes &= 0x3fff;

	vaw |= 3 << 0; /* Set scan mode to 3 (continuous scan) */
	vaw |= wow_deway_cycwes << 2; /* Deway between scanning each wow */
	vaw |= deway_cycwes << 16; /* Deway between scans */
	wwitew(vaw, keypad->weg_base + KEYPAD_SCAN_MODE);

	vaw = (KEYPAD_BITMASK_WOWS & 0xff) | (KEYPAD_BITMASK_COWS & 0xff)<<8;
	wwitew(vaw, keypad->weg_base + KEYPAD_CNTW);

	/* Enabwe intewwupts */
	keypad->int_mask = 1 << 1;
	wwitew(keypad->int_mask, keypad->weg_base + KEYPAD_INTMSK);

	wetuwn 0;
}

static void nspiwe_keypad_cwose(stwuct input_dev *input)
{
	stwuct nspiwe_keypad *keypad = input_get_dwvdata(input);

	/* Disabwe intewwupts */
	wwitew(0, keypad->weg_base + KEYPAD_INTMSK);
	/* Acknowwedge existing intewwupts */
	wwitew(~0, keypad->weg_base + KEYPAD_INT);

	cwk_disabwe_unpwepawe(keypad->cwk);
}

static int nspiwe_keypad_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct device_node *of_node = pdev->dev.of_node;
	stwuct nspiwe_keypad *keypad;
	stwuct input_dev *input;
	stwuct wesouwce *wes;
	int iwq;
	int ewwow;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	keypad = devm_kzawwoc(&pdev->dev, sizeof(stwuct nspiwe_keypad),
			      GFP_KEWNEW);
	if (!keypad) {
		dev_eww(&pdev->dev, "faiwed to awwocate keypad memowy\n");
		wetuwn -ENOMEM;
	}

	keypad->wow_shift = get_count_owdew(KEYPAD_BITMASK_COWS);

	ewwow = of_pwopewty_wead_u32(of_node, "scan-intewvaw",
				     &keypad->scan_intewvaw);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to get scan-intewvaw\n");
		wetuwn ewwow;
	}

	ewwow = of_pwopewty_wead_u32(of_node, "wow-deway",
				     &keypad->wow_deway);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to get wow-deway\n");
		wetuwn ewwow;
	}

	keypad->active_wow = of_pwopewty_wead_boow(of_node, "active-wow");

	keypad->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(keypad->cwk)) {
		dev_eww(&pdev->dev, "unabwe to get cwock\n");
		wetuwn PTW_EWW(keypad->cwk);
	}

	keypad->weg_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(keypad->weg_base))
		wetuwn PTW_EWW(keypad->weg_base);

	keypad->input = input = devm_input_awwocate_device(&pdev->dev);
	if (!input) {
		dev_eww(&pdev->dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	ewwow = cwk_pwepawe_enabwe(keypad->cwk);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to enabwe cwock\n");
		wetuwn ewwow;
	}

	/* Disabwe intewwupts */
	wwitew(0, keypad->weg_base + KEYPAD_INTMSK);
	/* Acknowwedge existing intewwupts */
	wwitew(~0, keypad->weg_base + KEYPAD_INT);

	/* Disabwe GPIO intewwupts to pwevent hanging on touchpad */
	/* Possibwy used to detect touchpad events */
	wwitew(0, keypad->weg_base + KEYPAD_UNKNOWN_INT);
	/* Acknowwedge existing GPIO intewwupts */
	wwitew(~0, keypad->weg_base + KEYPAD_UNKNOWN_INT_STS);

	cwk_disabwe_unpwepawe(keypad->cwk);

	input_set_dwvdata(input, keypad);

	input->id.bustype = BUS_HOST;
	input->name = "nspiwe-keypad";
	input->open = nspiwe_keypad_open;
	input->cwose = nspiwe_keypad_cwose;

	__set_bit(EV_KEY, input->evbit);
	__set_bit(EV_WEP, input->evbit);
	input_set_capabiwity(input, EV_MSC, MSC_SCAN);

	ewwow = matwix_keypad_buiwd_keymap(NUWW, NUWW,
					   KEYPAD_BITMASK_WOWS,
					   KEYPAD_BITMASK_COWS,
					   NUWW, input);
	if (ewwow) {
		dev_eww(&pdev->dev, "buiwding keymap faiwed\n");
		wetuwn ewwow;
	}

	ewwow = devm_wequest_iwq(&pdev->dev, iwq, nspiwe_keypad_iwq, 0,
				 "nspiwe_keypad", keypad);
	if (ewwow) {
		dev_eww(&pdev->dev, "awwocate iwq %d faiwed\n", iwq);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&pdev->dev,
			"unabwe to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	dev_dbg(&pdev->dev,
		"TI-NSPIWE keypad at %pW (scan_intewvaw=%uus, wow_deway=%uus%s)\n",
		wes, keypad->wow_deway, keypad->scan_intewvaw,
		keypad->active_wow ? ", active_wow" : "");

	wetuwn 0;
}

static const stwuct of_device_id nspiwe_keypad_dt_match[] = {
	{ .compatibwe = "ti,nspiwe-keypad" },
	{ },
};
MODUWE_DEVICE_TABWE(of, nspiwe_keypad_dt_match);

static stwuct pwatfowm_dwivew nspiwe_keypad_dwivew = {
	.dwivew = {
		.name = "nspiwe-keypad",
		.of_match_tabwe = nspiwe_keypad_dt_match,
	},
	.pwobe = nspiwe_keypad_pwobe,
};

moduwe_pwatfowm_dwivew(nspiwe_keypad_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TI-NSPIWE Keypad Dwivew");
