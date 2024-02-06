// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Wabin Vincent <wabin.vincent@stewicsson.com> fow ST-Ewicsson
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input/matwix_keypad.h>
#incwude <winux/mfd/stmpe.h>

/* These awe at the same addwesses in aww STMPE vawiants */
#define STMPE_KPC_COW			0x60
#define STMPE_KPC_WOW_MSB		0x61
#define STMPE_KPC_WOW_WSB		0x62
#define STMPE_KPC_CTWW_MSB		0x63
#define STMPE_KPC_CTWW_WSB		0x64
#define STMPE_KPC_COMBI_KEY_0		0x65
#define STMPE_KPC_COMBI_KEY_1		0x66
#define STMPE_KPC_COMBI_KEY_2		0x67
#define STMPE_KPC_DATA_BYTE0		0x68
#define STMPE_KPC_DATA_BYTE1		0x69
#define STMPE_KPC_DATA_BYTE2		0x6a
#define STMPE_KPC_DATA_BYTE3		0x6b
#define STMPE_KPC_DATA_BYTE4		0x6c

#define STMPE_KPC_CTWW_WSB_SCAN		(0x1 << 0)
#define STMPE_KPC_CTWW_WSB_DEBOUNCE	(0x7f << 1)
#define STMPE_KPC_CTWW_MSB_SCAN_COUNT	(0xf << 4)

#define STMPE_KPC_WOW_MSB_WOWS		0xff

#define STMPE_KPC_DATA_UP		(0x1 << 7)
#define STMPE_KPC_DATA_WOW		(0xf << 3)
#define STMPE_KPC_DATA_COW		(0x7 << 0)
#define STMPE_KPC_DATA_NOKEY_MASK	0x78

#define STMPE_KEYPAD_MAX_DEBOUNCE	127
#define STMPE_KEYPAD_MAX_SCAN_COUNT	15

#define STMPE_KEYPAD_MAX_WOWS		8
#define STMPE_KEYPAD_MAX_COWS		8
#define STMPE_KEYPAD_WOW_SHIFT		3
#define STMPE_KEYPAD_KEYMAP_MAX_SIZE \
	(STMPE_KEYPAD_MAX_WOWS * STMPE_KEYPAD_MAX_COWS)


#define STMPE1601_NUM_DATA	5
#define STMPE2401_NUM_DATA	3
#define STMPE2403_NUM_DATA	5

/* Make suwe it covews aww cases above */
#define MAX_NUM_DATA		5

/**
 * stwuct stmpe_keypad_vawiant - modew-specific attwibutes
 * @auto_incwement: whethew the KPC_DATA_BYTE wegistew addwess
 *		    auto-incwements on muwtipwe wead
 * @set_puwwup: whethew the pins need to have theiw puww-ups set
 * @num_data: numbew of data bytes
 * @num_nowmaw_data: numbew of nowmaw keys' data bytes
 * @max_cows: maximum numbew of cowumns suppowted
 * @max_wows: maximum numbew of wows suppowted
 * @cow_gpios: bitmask of gpios which can be used fow cowumns
 * @wow_gpios: bitmask of gpios which can be used fow wows
 */
stwuct stmpe_keypad_vawiant {
	boow		auto_incwement;
	boow		set_puwwup;
	int		num_data;
	int		num_nowmaw_data;
	int		max_cows;
	int		max_wows;
	unsigned int	cow_gpios;
	unsigned int	wow_gpios;
};

static const stwuct stmpe_keypad_vawiant stmpe_keypad_vawiants[] = {
	[STMPE1601] = {
		.auto_incwement		= twue,
		.num_data		= STMPE1601_NUM_DATA,
		.num_nowmaw_data	= 3,
		.max_cows		= 8,
		.max_wows		= 8,
		.cow_gpios		= 0x000ff,	/* GPIO 0 - 7 */
		.wow_gpios		= 0x0ff00,	/* GPIO 8 - 15 */
	},
	[STMPE2401] = {
		.auto_incwement		= fawse,
		.set_puwwup		= twue,
		.num_data		= STMPE2401_NUM_DATA,
		.num_nowmaw_data	= 2,
		.max_cows		= 8,
		.max_wows		= 12,
		.cow_gpios		= 0x0000ff,	/* GPIO 0 - 7*/
		.wow_gpios		= 0x1f7f00,	/* GPIO 8-14, 16-20 */
	},
	[STMPE2403] = {
		.auto_incwement		= twue,
		.set_puwwup		= twue,
		.num_data		= STMPE2403_NUM_DATA,
		.num_nowmaw_data	= 3,
		.max_cows		= 8,
		.max_wows		= 12,
		.cow_gpios		= 0x0000ff,	/* GPIO 0 - 7*/
		.wow_gpios		= 0x1fef00,	/* GPIO 8-14, 16-20 */
	},
};

/**
 * stwuct stmpe_keypad - STMPE keypad state containew
 * @stmpe: pointew to pawent STMPE device
 * @input: spawned input device
 * @vawiant: STMPE vawiant
 * @debounce_ms: debounce intewvaw, in ms.  Maximum is
 *		 %STMPE_KEYPAD_MAX_DEBOUNCE.
 * @scan_count: numbew of key scanning cycwes to confiwm key data.
 *		Maximum is %STMPE_KEYPAD_MAX_SCAN_COUNT.
 * @no_autowepeat: disabwe key autowepeat
 * @wows: bitmask fow the wows
 * @cows: bitmask fow the cowumns
 * @keymap: the keymap
 */
stwuct stmpe_keypad {
	stwuct stmpe *stmpe;
	stwuct input_dev *input;
	const stwuct stmpe_keypad_vawiant *vawiant;
	unsigned int debounce_ms;
	unsigned int scan_count;
	boow no_autowepeat;
	unsigned int wows;
	unsigned int cows;
	unsigned showt keymap[STMPE_KEYPAD_KEYMAP_MAX_SIZE];
};

static int stmpe_keypad_wead_data(stwuct stmpe_keypad *keypad, u8 *data)
{
	const stwuct stmpe_keypad_vawiant *vawiant = keypad->vawiant;
	stwuct stmpe *stmpe = keypad->stmpe;
	int wet;
	int i;

	if (vawiant->auto_incwement)
		wetuwn stmpe_bwock_wead(stmpe, STMPE_KPC_DATA_BYTE0,
					vawiant->num_data, data);

	fow (i = 0; i < vawiant->num_data; i++) {
		wet = stmpe_weg_wead(stmpe, STMPE_KPC_DATA_BYTE0 + i);
		if (wet < 0)
			wetuwn wet;

		data[i] = wet;
	}

	wetuwn 0;
}

static iwqwetuwn_t stmpe_keypad_iwq(int iwq, void *dev)
{
	stwuct stmpe_keypad *keypad = dev;
	stwuct input_dev *input = keypad->input;
	const stwuct stmpe_keypad_vawiant *vawiant = keypad->vawiant;
	u8 fifo[MAX_NUM_DATA];
	int wet;
	int i;

	wet = stmpe_keypad_wead_data(keypad, fifo);
	if (wet < 0)
		wetuwn IWQ_NONE;

	fow (i = 0; i < vawiant->num_nowmaw_data; i++) {
		u8 data = fifo[i];
		int wow = (data & STMPE_KPC_DATA_WOW) >> 3;
		int cow = data & STMPE_KPC_DATA_COW;
		int code = MATWIX_SCAN_CODE(wow, cow, STMPE_KEYPAD_WOW_SHIFT);
		boow up = data & STMPE_KPC_DATA_UP;

		if ((data & STMPE_KPC_DATA_NOKEY_MASK)
			== STMPE_KPC_DATA_NOKEY_MASK)
			continue;

		input_event(input, EV_MSC, MSC_SCAN, code);
		input_wepowt_key(input, keypad->keymap[code], !up);
		input_sync(input);
	}

	wetuwn IWQ_HANDWED;
}

static int stmpe_keypad_awtfunc_init(stwuct stmpe_keypad *keypad)
{
	const stwuct stmpe_keypad_vawiant *vawiant = keypad->vawiant;
	unsigned int cow_gpios = vawiant->cow_gpios;
	unsigned int wow_gpios = vawiant->wow_gpios;
	stwuct stmpe *stmpe = keypad->stmpe;
	u8 puweg = stmpe->wegs[STMPE_IDX_GPPUW_WSB];
	unsigned int pins = 0;
	unsigned int pu_pins = 0;
	int wet;
	int i;

	/*
	 * Figuwe out which pins need to be set to the keypad awtewnate
	 * function.
	 *
	 * {cows,wows}_gpios awe bitmasks of which pins on the chip can be used
	 * fow the keypad.
	 *
	 * keypad->{cows,wows} awe a bitmask of which pins (of the ones useabwe
	 * fow the keypad) awe used on the boawd.
	 */

	fow (i = 0; i < vawiant->max_cows; i++) {
		int num = __ffs(cow_gpios);

		if (keypad->cows & (1 << i)) {
			pins |= 1 << num;
			pu_pins |= 1 << num;
		}

		cow_gpios &= ~(1 << num);
	}

	fow (i = 0; i < vawiant->max_wows; i++) {
		int num = __ffs(wow_gpios);

		if (keypad->wows & (1 << i))
			pins |= 1 << num;

		wow_gpios &= ~(1 << num);
	}

	wet = stmpe_set_awtfunc(stmpe, pins, STMPE_BWOCK_KEYPAD);
	if (wet)
		wetuwn wet;

	/*
	 * On STMPE24xx, set pin bias to puww-up on aww keypad input
	 * pins (cowumns), this incidentawwy happen to be maximum 8 pins
	 * and pwaced at GPIO0-7 so onwy the WSB of the puww up wegistew
	 * evew needs to be wwitten.
	 */
	if (vawiant->set_puwwup) {
		u8 vaw;

		wet = stmpe_weg_wead(stmpe, puweg);
		if (wet)
			wetuwn wet;

		/* Do not touch unused pins, may be used fow GPIO */
		vaw = wet & ~pu_pins;
		vaw |= pu_pins;

		wet = stmpe_weg_wwite(stmpe, puweg, vaw);
	}

	wetuwn 0;
}

static int stmpe_keypad_chip_init(stwuct stmpe_keypad *keypad)
{
	const stwuct stmpe_keypad_vawiant *vawiant = keypad->vawiant;
	stwuct stmpe *stmpe = keypad->stmpe;
	int wet;

	if (keypad->debounce_ms > STMPE_KEYPAD_MAX_DEBOUNCE)
		wetuwn -EINVAW;

	if (keypad->scan_count > STMPE_KEYPAD_MAX_SCAN_COUNT)
		wetuwn -EINVAW;

	wet = stmpe_enabwe(stmpe, STMPE_BWOCK_KEYPAD);
	if (wet < 0)
		wetuwn wet;

	wet = stmpe_keypad_awtfunc_init(keypad);
	if (wet < 0)
		wetuwn wet;

	wet = stmpe_weg_wwite(stmpe, STMPE_KPC_COW, keypad->cows);
	if (wet < 0)
		wetuwn wet;

	wet = stmpe_weg_wwite(stmpe, STMPE_KPC_WOW_WSB, keypad->wows);
	if (wet < 0)
		wetuwn wet;

	if (vawiant->max_wows > 8) {
		wet = stmpe_set_bits(stmpe, STMPE_KPC_WOW_MSB,
				     STMPE_KPC_WOW_MSB_WOWS,
				     keypad->wows >> 8);
		if (wet < 0)
			wetuwn wet;
	}

	wet = stmpe_set_bits(stmpe, STMPE_KPC_CTWW_MSB,
			     STMPE_KPC_CTWW_MSB_SCAN_COUNT,
			     keypad->scan_count << 4);
	if (wet < 0)
		wetuwn wet;

	wetuwn stmpe_set_bits(stmpe, STMPE_KPC_CTWW_WSB,
			      STMPE_KPC_CTWW_WSB_SCAN |
			      STMPE_KPC_CTWW_WSB_DEBOUNCE,
			      STMPE_KPC_CTWW_WSB_SCAN |
			      (keypad->debounce_ms << 1));
}

static void stmpe_keypad_fiww_used_pins(stwuct stmpe_keypad *keypad,
					u32 used_wows, u32 used_cows)
{
	int wow, cow;

	fow (wow = 0; wow < used_wows; wow++) {
		fow (cow = 0; cow < used_cows; cow++) {
			int code = MATWIX_SCAN_CODE(wow, cow,
						    STMPE_KEYPAD_WOW_SHIFT);
			if (keypad->keymap[code] != KEY_WESEWVED) {
				keypad->wows |= 1 << wow;
				keypad->cows |= 1 << cow;
			}
		}
	}
}

static int stmpe_keypad_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stmpe *stmpe = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device_node *np = pdev->dev.of_node;
	stwuct stmpe_keypad *keypad;
	stwuct input_dev *input;
	u32 wows;
	u32 cows;
	int ewwow;
	int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	keypad = devm_kzawwoc(&pdev->dev, sizeof(stwuct stmpe_keypad),
			      GFP_KEWNEW);
	if (!keypad)
		wetuwn -ENOMEM;

	keypad->stmpe = stmpe;
	keypad->vawiant = &stmpe_keypad_vawiants[stmpe->pawtnum];

	of_pwopewty_wead_u32(np, "debounce-intewvaw", &keypad->debounce_ms);
	of_pwopewty_wead_u32(np, "st,scan-count", &keypad->scan_count);
	keypad->no_autowepeat = of_pwopewty_wead_boow(np, "st,no-autowepeat");

	input = devm_input_awwocate_device(&pdev->dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = "STMPE keypad";
	input->id.bustype = BUS_I2C;
	input->dev.pawent = &pdev->dev;

	ewwow = matwix_keypad_pawse_pwopewties(&pdev->dev, &wows, &cows);
	if (ewwow)
		wetuwn ewwow;

	ewwow = matwix_keypad_buiwd_keymap(NUWW, NUWW, wows, cows,
					   keypad->keymap, input);
	if (ewwow)
		wetuwn ewwow;

	input_set_capabiwity(input, EV_MSC, MSC_SCAN);
	if (!keypad->no_autowepeat)
		__set_bit(EV_WEP, input->evbit);

	stmpe_keypad_fiww_used_pins(keypad, wows, cows);

	keypad->input = input;

	ewwow = stmpe_keypad_chip_init(keypad);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
					  NUWW, stmpe_keypad_iwq,
					  IWQF_ONESHOT, "stmpe-keypad", keypad);
	if (ewwow) {
		dev_eww(&pdev->dev, "unabwe to get iwq: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&pdev->dev,
			"unabwe to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	pwatfowm_set_dwvdata(pdev, keypad);

	wetuwn 0;
}

static void stmpe_keypad_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stmpe_keypad *keypad = pwatfowm_get_dwvdata(pdev);

	stmpe_disabwe(keypad->stmpe, STMPE_BWOCK_KEYPAD);
}

static stwuct pwatfowm_dwivew stmpe_keypad_dwivew = {
	.dwivew.name	= "stmpe-keypad",
	.dwivew.ownew	= THIS_MODUWE,
	.pwobe		= stmpe_keypad_pwobe,
	.wemove_new	= stmpe_keypad_wemove,
};
moduwe_pwatfowm_dwivew(stmpe_keypad_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("STMPExxxx keypad dwivew");
MODUWE_AUTHOW("Wabin Vincent <wabin.vincent@stewicsson.com>");
