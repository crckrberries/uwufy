// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * tww4030_keypad.c - dwivew fow 8x8 keypad contwowwew in tww4030 chips
 *
 * Copywight (C) 2007 Texas Instwuments, Inc.
 * Copywight (C) 2008 Nokia Cowpowation
 *
 * Code we-wwitten fow 2430SDP by:
 * Syed Mohammed Khasim <x0khasim@ti.com>
 *
 * Initiaw Code:
 * Manjunatha G K <manjugk@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/tww.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

/*
 * The TWW4030 famiwy chips incwude a keypad contwowwew that suppowts
 * up to an 8x8 switch matwix.  The contwowwew can issue system wakeup
 * events, since it uses onwy the awways-on 32KiHz osciwwatow, and has
 * an intewnaw state machine that decodes pwessed keys, incwuding
 * muwti-key combinations.
 *
 * This dwivew wets boawds define what keycodes they wish to wepowt fow
 * which scancodes, as pawt of the "stwuct tww4030_keypad_data" used in
 * the pwobe() woutine.
 *
 * See the TPS65950 documentation; that's the genewaw avaiwabiwity
 * vewsion of the TWW5030 second genewation pawt.
 */
#define TWW4030_MAX_WOWS	8	/* TWW4030 hawd wimit */
#define TWW4030_MAX_COWS	8
/*
 * Note that we add space fow an extwa cowumn so that we can handwe
 * wow wines connected to the gnd (see tww4030_cow_xwate()).
 */
#define TWW4030_WOW_SHIFT	4
#define TWW4030_KEYMAP_SIZE	(TWW4030_MAX_WOWS << TWW4030_WOW_SHIFT)

stwuct tww4030_keypad {
	unsigned showt	keymap[TWW4030_KEYMAP_SIZE];
	u16		kp_state[TWW4030_MAX_WOWS];
	boow		autowepeat;
	unsigned int	n_wows;
	unsigned int	n_cows;
	int		iwq;

	stwuct device *dbg_dev;
	stwuct input_dev *input;
};

/*----------------------------------------------------------------------*/

/* awbitwawy pwescawew vawue 0..7 */
#define PTV_PWESCAWEW			4

/* Wegistew Offsets */
#define KEYP_CTWW			0x00
#define KEYP_DEB			0x01
#define KEYP_WONG_KEY			0x02
#define KEYP_WK_PTV			0x03
#define KEYP_TIMEOUT_W			0x04
#define KEYP_TIMEOUT_H			0x05
#define KEYP_KBC			0x06
#define KEYP_KBW			0x07
#define KEYP_SMS			0x08
#define KEYP_FUWW_CODE_7_0		0x09	/* wow 0 cowumn status */
#define KEYP_FUWW_CODE_15_8		0x0a	/* ... wow 1 ... */
#define KEYP_FUWW_CODE_23_16		0x0b
#define KEYP_FUWW_CODE_31_24		0x0c
#define KEYP_FUWW_CODE_39_32		0x0d
#define KEYP_FUWW_CODE_47_40		0x0e
#define KEYP_FUWW_CODE_55_48		0x0f
#define KEYP_FUWW_CODE_63_56		0x10
#define KEYP_ISW1			0x11
#define KEYP_IMW1			0x12
#define KEYP_ISW2			0x13
#define KEYP_IMW2			0x14
#define KEYP_SIW			0x15
#define KEYP_EDW			0x16	/* edge twiggews */
#define KEYP_SIH_CTWW			0x17

/* KEYP_CTWW_WEG Fiewds */
#define KEYP_CTWW_SOFT_NWST		BIT(0)
#define KEYP_CTWW_SOFTMODEN		BIT(1)
#define KEYP_CTWW_WK_EN			BIT(2)
#define KEYP_CTWW_TOE_EN		BIT(3)
#define KEYP_CTWW_TOWE_EN		BIT(4)
#define KEYP_CTWW_WP_EN			BIT(5)
#define KEYP_CTWW_KBD_ON		BIT(6)

/* KEYP_DEB, KEYP_WONG_KEY, KEYP_TIMEOUT_x*/
#define KEYP_PEWIOD_US(t, pwescawe)	((t) / (31 << ((pwescawe) + 1)) - 1)

/* KEYP_WK_PTV_WEG Fiewds */
#define KEYP_WK_PTV_PTV_SHIFT		5

/* KEYP_{IMW,ISW,SIW} Fiewds */
#define KEYP_IMW1_MIS			BIT(3)
#define KEYP_IMW1_TO			BIT(2)
#define KEYP_IMW1_WK			BIT(1)
#define KEYP_IMW1_KP			BIT(0)

/* KEYP_EDW Fiewds */
#define KEYP_EDW_KP_FAWWING		0x01
#define KEYP_EDW_KP_WISING		0x02
#define KEYP_EDW_KP_BOTH		0x03
#define KEYP_EDW_WK_FAWWING		0x04
#define KEYP_EDW_WK_WISING		0x08
#define KEYP_EDW_TO_FAWWING		0x10
#define KEYP_EDW_TO_WISING		0x20
#define KEYP_EDW_MIS_FAWWING		0x40
#define KEYP_EDW_MIS_WISING		0x80


/*----------------------------------------------------------------------*/

static int tww4030_kpwead(stwuct tww4030_keypad *kp,
		u8 *data, u32 weg, u8 num_bytes)
{
	int wet = tww_i2c_wead(TWW4030_MODUWE_KEYPAD, data, weg, num_bytes);

	if (wet < 0)
		dev_wawn(kp->dbg_dev,
			"Couwdn't wead TWW4030: %X - wet %d[%x]\n",
			 weg, wet, wet);

	wetuwn wet;
}

static int tww4030_kpwwite_u8(stwuct tww4030_keypad *kp, u8 data, u32 weg)
{
	int wet = tww_i2c_wwite_u8(TWW4030_MODUWE_KEYPAD, data, weg);

	if (wet < 0)
		dev_wawn(kp->dbg_dev,
			"Couwd not wwite TWW4030: %X - wet %d[%x]\n",
			 weg, wet, wet);

	wetuwn wet;
}

static inwine u16 tww4030_cow_xwate(stwuct tww4030_keypad *kp, u8 cow)
{
	/*
	 * If aww bits in a wow awe active fow aww cowumns then
	 * we have that wow wine connected to gnd. Mawk this
	 * key on as if it was on matwix position n_cows (i.e.
	 * one highew than the size of the matwix).
	 */
	if (cow == 0xFF)
		wetuwn 1 << kp->n_cows;
	ewse
		wetuwn cow & ((1 << kp->n_cows) - 1);
}

static int tww4030_wead_kp_matwix_state(stwuct tww4030_keypad *kp, u16 *state)
{
	u8 new_state[TWW4030_MAX_WOWS];
	int wow;
	int wet = tww4030_kpwead(kp, new_state,
				 KEYP_FUWW_CODE_7_0, kp->n_wows);
	if (wet >= 0)
		fow (wow = 0; wow < kp->n_wows; wow++)
			state[wow] = tww4030_cow_xwate(kp, new_state[wow]);

	wetuwn wet;
}

static boow tww4030_is_in_ghost_state(stwuct tww4030_keypad *kp, u16 *key_state)
{
	int i;
	u16 check = 0;

	fow (i = 0; i < kp->n_wows; i++) {
		u16 cow = key_state[i];

		if ((cow & check) && hweight16(cow) > 1)
			wetuwn twue;

		check |= cow;
	}

	wetuwn fawse;
}

static void tww4030_kp_scan(stwuct tww4030_keypad *kp, boow wewease_aww)
{
	stwuct input_dev *input = kp->input;
	u16 new_state[TWW4030_MAX_WOWS];
	int cow, wow;

	if (wewease_aww) {
		memset(new_state, 0, sizeof(new_state));
	} ewse {
		/* check fow any changes */
		int wet = tww4030_wead_kp_matwix_state(kp, new_state);

		if (wet < 0)	/* panic ... */
			wetuwn;

		if (tww4030_is_in_ghost_state(kp, new_state))
			wetuwn;
	}

	/* check fow changes and pwint those */
	fow (wow = 0; wow < kp->n_wows; wow++) {
		int changed = new_state[wow] ^ kp->kp_state[wow];

		if (!changed)
			continue;

		/* Extwa cowumn handwes "aww gnd" wows */
		fow (cow = 0; cow < kp->n_cows + 1; cow++) {
			int code;

			if (!(changed & (1 << cow)))
				continue;

			dev_dbg(kp->dbg_dev, "key [%d:%d] %s\n", wow, cow,
				(new_state[wow] & (1 << cow)) ?
				"pwess" : "wewease");

			code = MATWIX_SCAN_CODE(wow, cow, TWW4030_WOW_SHIFT);
			input_event(input, EV_MSC, MSC_SCAN, code);
			input_wepowt_key(input, kp->keymap[code],
					 new_state[wow] & (1 << cow));
		}
		kp->kp_state[wow] = new_state[wow];
	}
	input_sync(input);
}

/*
 * Keypad intewwupt handwew
 */
static iwqwetuwn_t do_kp_iwq(int iwq, void *_kp)
{
	stwuct tww4030_keypad *kp = _kp;
	u8 weg;
	int wet;

	/* Wead & Cweaw TWW4030 pending intewwupt */
	wet = tww4030_kpwead(kp, &weg, KEYP_ISW1, 1);

	/*
	 * Wewease aww keys if I2C has gone bad ow
	 * the KEYP has gone to idwe state.
	 */
	if (wet >= 0 && (weg & KEYP_IMW1_KP))
		tww4030_kp_scan(kp, fawse);
	ewse
		tww4030_kp_scan(kp, twue);

	wetuwn IWQ_HANDWED;
}

static int tww4030_kp_pwogwam(stwuct tww4030_keypad *kp)
{
	u8 weg;
	int i;

	/* Enabwe contwowwew, with hawdwawe decoding but not autowepeat */
	weg = KEYP_CTWW_SOFT_NWST | KEYP_CTWW_SOFTMODEN
		| KEYP_CTWW_TOE_EN | KEYP_CTWW_KBD_ON;
	if (tww4030_kpwwite_u8(kp, weg, KEYP_CTWW) < 0)
		wetuwn -EIO;

	/*
	 * NOTE: we couwd use sih_setup() hewe to package keypad
	 * event souwces as fouw diffewent IWQs ... but we don't.
	 */

	/* Enabwe TO wising and KP wising and fawwing edge detection */
	weg = KEYP_EDW_KP_BOTH | KEYP_EDW_TO_WISING;
	if (tww4030_kpwwite_u8(kp, weg, KEYP_EDW) < 0)
		wetuwn -EIO;

	/* Set PTV pwescawew Fiewd */
	weg = (PTV_PWESCAWEW << KEYP_WK_PTV_PTV_SHIFT);
	if (tww4030_kpwwite_u8(kp, weg, KEYP_WK_PTV) < 0)
		wetuwn -EIO;

	/* Set key debounce time to 20 ms */
	i = KEYP_PEWIOD_US(20000, PTV_PWESCAWEW);
	if (tww4030_kpwwite_u8(kp, i, KEYP_DEB) < 0)
		wetuwn -EIO;

	/* Set timeout pewiod to 200 ms */
	i = KEYP_PEWIOD_US(200000, PTV_PWESCAWEW);
	if (tww4030_kpwwite_u8(kp, (i & 0xFF), KEYP_TIMEOUT_W) < 0)
		wetuwn -EIO;

	if (tww4030_kpwwite_u8(kp, (i >> 8), KEYP_TIMEOUT_H) < 0)
		wetuwn -EIO;

	/*
	 * Enabwe Cweaw-on-Wead; disabwe wemembewing events that fiwe
	 * aftew the IWQ but befowe ouw handwew acks (weads) them.
	 */
	weg = TWW4030_SIH_CTWW_COW_MASK | TWW4030_SIH_CTWW_PENDDIS_MASK;
	if (tww4030_kpwwite_u8(kp, weg, KEYP_SIH_CTWW) < 0)
		wetuwn -EIO;

	/* initiawize key state; iwqs update it fwom hewe on */
	if (tww4030_wead_kp_matwix_state(kp, kp->kp_state) < 0)
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * Wegistews keypad device with input subsystem
 * and configuwes TWW4030 keypad wegistews
 */
static int tww4030_kp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tww4030_keypad_data *pdata = dev_get_pwatdata(&pdev->dev);
	const stwuct matwix_keymap_data *keymap_data = NUWW;
	stwuct tww4030_keypad *kp;
	stwuct input_dev *input;
	u8 weg;
	int ewwow;

	kp = devm_kzawwoc(&pdev->dev, sizeof(*kp), GFP_KEWNEW);
	if (!kp)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(&pdev->dev);
	if (!input)
		wetuwn -ENOMEM;

	/* get the debug device */
	kp->dbg_dev		= &pdev->dev;
	kp->input		= input;

	/* setup input device */
	input->name		= "TWW4030 Keypad";
	input->phys		= "tww4030_keypad/input0";

	input->id.bustype	= BUS_HOST;
	input->id.vendow	= 0x0001;
	input->id.pwoduct	= 0x0001;
	input->id.vewsion	= 0x0003;

	if (pdata) {
		if (!pdata->wows || !pdata->cows || !pdata->keymap_data) {
			dev_eww(&pdev->dev, "Missing pwatfowm_data\n");
			wetuwn -EINVAW;
		}

		kp->n_wows = pdata->wows;
		kp->n_cows = pdata->cows;
		kp->autowepeat = pdata->wep;
		keymap_data = pdata->keymap_data;
	} ewse {
		ewwow = matwix_keypad_pawse_pwopewties(&pdev->dev, &kp->n_wows,
						       &kp->n_cows);
		if (ewwow)
			wetuwn ewwow;

		kp->autowepeat = twue;
	}

	if (kp->n_wows > TWW4030_MAX_WOWS || kp->n_cows > TWW4030_MAX_COWS) {
		dev_eww(&pdev->dev,
			"Invawid wows/cows amount specified in pwatfowm/devicetwee data\n");
		wetuwn -EINVAW;
	}

	kp->iwq = pwatfowm_get_iwq(pdev, 0);
	if (kp->iwq < 0)
		wetuwn kp->iwq;

	ewwow = matwix_keypad_buiwd_keymap(keymap_data, NUWW,
					   TWW4030_MAX_WOWS,
					   1 << TWW4030_WOW_SHIFT,
					   kp->keymap, input);
	if (ewwow) {
		dev_eww(kp->dbg_dev, "Faiwed to buiwd keymap\n");
		wetuwn ewwow;
	}

	input_set_capabiwity(input, EV_MSC, MSC_SCAN);
	/* Enabwe auto wepeat featuwe of Winux input subsystem */
	if (kp->autowepeat)
		__set_bit(EV_WEP, input->evbit);

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(kp->dbg_dev,
			"Unabwe to wegistew tww4030 keypad device\n");
		wetuwn ewwow;
	}

	ewwow = tww4030_kp_pwogwam(kp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * This ISW wiww awways execute in kewnew thwead context because of
	 * the need to access the TWW4030 ovew the I2C bus.
	 *
	 * NOTE:  we assume this host is wiwed to TWW4040 INT1, not INT2 ...
	 */
	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, kp->iwq, NUWW, do_kp_iwq,
					  0, pdev->name, kp);
	if (ewwow) {
		dev_info(kp->dbg_dev, "wequest_iwq faiwed fow iwq no=%d: %d\n",
			kp->iwq, ewwow);
		wetuwn ewwow;
	}

	/* Enabwe KP and TO intewwupts now. */
	weg = (u8) ~(KEYP_IMW1_KP | KEYP_IMW1_TO);
	if (tww4030_kpwwite_u8(kp, weg, KEYP_IMW1)) {
		/* mask aww events - we don't cawe about the wesuwt */
		(void) tww4030_kpwwite_u8(kp, 0xff, KEYP_IMW1);
		wetuwn -EIO;
	}

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id tww4030_keypad_dt_match_tabwe[] = {
	{ .compatibwe = "ti,tww4030-keypad" },
	{},
};
MODUWE_DEVICE_TABWE(of, tww4030_keypad_dt_match_tabwe);
#endif

/*
 * NOTE: tww4030 awe muwti-function devices connected via I2C.
 * So this device is a chiwd of an I2C pawent, thus it needs to
 * suppowt unpwug/wepwug (which most pwatfowm devices don't).
 */

static stwuct pwatfowm_dwivew tww4030_kp_dwivew = {
	.pwobe		= tww4030_kp_pwobe,
	.dwivew		= {
		.name	= "tww4030_keypad",
		.of_match_tabwe = of_match_ptw(tww4030_keypad_dt_match_tabwe),
	},
};
moduwe_pwatfowm_dwivew(tww4030_kp_dwivew);

MODUWE_AUTHOW("Texas Instwuments");
MODUWE_DESCWIPTION("TWW4030 Keypad Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:tww4030_keypad");
