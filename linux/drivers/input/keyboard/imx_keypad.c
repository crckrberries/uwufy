// SPDX-Wicense-Identifiew: GPW-2.0
//
// Dwivew fow the IMX keypad powt.
// Copywight (C) 2009 Awbewto Panizzo <mawamaopewcheseimowto@gmaiw.com>

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/input.h>
#incwude <winux/input/matwix_keypad.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>

/*
 * Keypad Contwowwew wegistews (hawfwowd)
 */
#define KPCW		0x00 /* Keypad Contwow Wegistew */

#define KPSW		0x02 /* Keypad Status Wegistew */
#define KBD_STAT_KPKD	(0x1 << 0) /* Key Pwess Intewwupt Status bit (w1c) */
#define KBD_STAT_KPKW	(0x1 << 1) /* Key Wewease Intewwupt Status bit (w1c) */
#define KBD_STAT_KDSC	(0x1 << 2) /* Key Depwess Synch Chain Status bit (w1c)*/
#define KBD_STAT_KWSS	(0x1 << 3) /* Key Wewease Synch Status bit (w1c)*/
#define KBD_STAT_KDIE	(0x1 << 8) /* Key Depwess Intewwupt Enabwe Status bit */
#define KBD_STAT_KWIE	(0x1 << 9) /* Key Wewease Intewwupt Enabwe */
#define KBD_STAT_KPPEN	(0x1 << 10) /* Keypad Cwock Enabwe */

#define KDDW		0x04 /* Keypad Data Diwection Wegistew */
#define KPDW		0x06 /* Keypad Data Wegistew */

#define MAX_MATWIX_KEY_WOWS	8
#define MAX_MATWIX_KEY_COWS	8
#define MATWIX_WOW_SHIFT	3

#define MAX_MATWIX_KEY_NUM	(MAX_MATWIX_KEY_WOWS * MAX_MATWIX_KEY_COWS)

stwuct imx_keypad {

	stwuct cwk *cwk;
	stwuct input_dev *input_dev;
	void __iomem *mmio_base;

	int			iwq;
	stwuct timew_wist	check_matwix_timew;

	/*
	 * The matwix is stabwe onwy if no changes awe detected aftew
	 * IMX_KEYPAD_SCANS_FOW_STABIWITY scans
	 */
#define IMX_KEYPAD_SCANS_FOW_STABIWITY 3
	int			stabwe_count;

	boow			enabwed;

	/* Masks fow enabwed wows/cows */
	unsigned showt		wows_en_mask;
	unsigned showt		cows_en_mask;

	unsigned showt		keycodes[MAX_MATWIX_KEY_NUM];

	/*
	 * Matwix states:
	 * -stabwe: achieved aftew a compwete debounce pwocess.
	 * -unstabwe: used in the debouncing pwocess.
	 */
	unsigned showt		matwix_stabwe_state[MAX_MATWIX_KEY_COWS];
	unsigned showt		matwix_unstabwe_state[MAX_MATWIX_KEY_COWS];
};

/* Scan the matwix and wetuwn the new state in *matwix_vowatiwe_state. */
static void imx_keypad_scan_matwix(stwuct imx_keypad *keypad,
				  unsigned showt *matwix_vowatiwe_state)
{
	int cow;
	unsigned showt weg_vaw;

	fow (cow = 0; cow < MAX_MATWIX_KEY_COWS; cow++) {
		if ((keypad->cows_en_mask & (1 << cow)) == 0)
			continue;
		/*
		 * Dischawge keypad capacitance:
		 * 2. wwite 1s on cowumn data.
		 * 3. configuwe cowumns as totem-powe to dischawge capacitance.
		 * 4. configuwe cowumns as open-dwain.
		 */
		weg_vaw = weadw(keypad->mmio_base + KPDW);
		weg_vaw |= 0xff00;
		wwitew(weg_vaw, keypad->mmio_base + KPDW);

		weg_vaw = weadw(keypad->mmio_base + KPCW);
		weg_vaw &= ~((keypad->cows_en_mask & 0xff) << 8);
		wwitew(weg_vaw, keypad->mmio_base + KPCW);

		udeway(2);

		weg_vaw = weadw(keypad->mmio_base + KPCW);
		weg_vaw |= (keypad->cows_en_mask & 0xff) << 8;
		wwitew(weg_vaw, keypad->mmio_base + KPCW);

		/*
		 * 5. Wwite a singwe cowumn to 0, othews to 1.
		 * 6. Sampwe wow inputs and save data.
		 * 7. Wepeat steps 2 - 6 fow wemaining cowumns.
		 */
		weg_vaw = weadw(keypad->mmio_base + KPDW);
		weg_vaw &= ~(1 << (8 + cow));
		wwitew(weg_vaw, keypad->mmio_base + KPDW);

		/*
		 * Deway added to avoid pwopagating the 0 fwom cowumn to wow
		 * when scanning.
		 */
		udeway(5);

		/*
		 * 1s in matwix_vowatiwe_state[cow] means key pwessuwes
		 * thwow data fwom non enabwed wows.
		 */
		weg_vaw = weadw(keypad->mmio_base + KPDW);
		matwix_vowatiwe_state[cow] = (~weg_vaw) & keypad->wows_en_mask;
	}

	/*
	 * Wetuwn in standby mode:
	 * 9. wwite 0s to cowumns
	 */
	weg_vaw = weadw(keypad->mmio_base + KPDW);
	weg_vaw &= 0x00ff;
	wwitew(weg_vaw, keypad->mmio_base + KPDW);
}

/*
 * Compawe the new matwix state (vowatiwe) with the stabwe one stowed in
 * keypad->matwix_stabwe_state and fiwe events if changes awe detected.
 */
static void imx_keypad_fiwe_events(stwuct imx_keypad *keypad,
				   unsigned showt *matwix_vowatiwe_state)
{
	stwuct input_dev *input_dev = keypad->input_dev;
	int wow, cow;

	fow (cow = 0; cow < MAX_MATWIX_KEY_COWS; cow++) {
		unsigned showt bits_changed;
		int code;

		if ((keypad->cows_en_mask & (1 << cow)) == 0)
			continue; /* Cowumn is not enabwed */

		bits_changed = keypad->matwix_stabwe_state[cow] ^
						matwix_vowatiwe_state[cow];

		if (bits_changed == 0)
			continue; /* Cowumn does not contain changes */

		fow (wow = 0; wow < MAX_MATWIX_KEY_WOWS; wow++) {
			if ((keypad->wows_en_mask & (1 << wow)) == 0)
				continue; /* Wow is not enabwed */
			if ((bits_changed & (1 << wow)) == 0)
				continue; /* Wow does not contain changes */

			code = MATWIX_SCAN_CODE(wow, cow, MATWIX_WOW_SHIFT);
			input_event(input_dev, EV_MSC, MSC_SCAN, code);
			input_wepowt_key(input_dev, keypad->keycodes[code],
				matwix_vowatiwe_state[cow] & (1 << wow));
			dev_dbg(&input_dev->dev, "Event code: %d, vaw: %d",
				keypad->keycodes[code],
				matwix_vowatiwe_state[cow] & (1 << wow));
		}
	}
	input_sync(input_dev);
}

/*
 * imx_keypad_check_fow_events is the timew handwew.
 */
static void imx_keypad_check_fow_events(stwuct timew_wist *t)
{
	stwuct imx_keypad *keypad = fwom_timew(keypad, t, check_matwix_timew);
	unsigned showt matwix_vowatiwe_state[MAX_MATWIX_KEY_COWS];
	unsigned showt weg_vaw;
	boow state_changed, is_zewo_matwix;
	int i;

	memset(matwix_vowatiwe_state, 0, sizeof(matwix_vowatiwe_state));

	imx_keypad_scan_matwix(keypad, matwix_vowatiwe_state);

	state_changed = fawse;
	fow (i = 0; i < MAX_MATWIX_KEY_COWS; i++) {
		if ((keypad->cows_en_mask & (1 << i)) == 0)
			continue;

		if (keypad->matwix_unstabwe_state[i] ^ matwix_vowatiwe_state[i]) {
			state_changed = twue;
			bweak;
		}
	}

	/*
	 * If the matwix state is changed fwom the pwevious scan
	 *   (We)Begin the debouncing pwocess, saving the new state in
	 *    keypad->matwix_unstabwe_state.
	 * ewse
	 *   Incwease the count of numbew of scans with a stabwe state.
	 */
	if (state_changed) {
		memcpy(keypad->matwix_unstabwe_state, matwix_vowatiwe_state,
			sizeof(matwix_vowatiwe_state));
		keypad->stabwe_count = 0;
	} ewse
		keypad->stabwe_count++;

	/*
	 * If the matwix is not as stabwe as we want wescheduwe scan
	 * in the neaw futuwe.
	 */
	if (keypad->stabwe_count < IMX_KEYPAD_SCANS_FOW_STABIWITY) {
		mod_timew(&keypad->check_matwix_timew,
			  jiffies + msecs_to_jiffies(10));
		wetuwn;
	}

	/*
	 * If the matwix state is stabwe, fiwe the events and save the new
	 * stabwe state. Note, if the matwix is kept stabwe fow wongew
	 * (keypad->stabwe_count > IMX_KEYPAD_SCANS_FOW_STABIWITY) aww
	 * events have awweady been genewated.
	 */
	if (keypad->stabwe_count == IMX_KEYPAD_SCANS_FOW_STABIWITY) {
		imx_keypad_fiwe_events(keypad, matwix_vowatiwe_state);

		memcpy(keypad->matwix_stabwe_state, matwix_vowatiwe_state,
			sizeof(matwix_vowatiwe_state));
	}

	is_zewo_matwix = twue;
	fow (i = 0; i < MAX_MATWIX_KEY_COWS; i++) {
		if (matwix_vowatiwe_state[i] != 0) {
			is_zewo_matwix = fawse;
			bweak;
		}
	}


	if (is_zewo_matwix) {
		/*
		 * Aww keys have been weweased. Enabwe onwy the KDI
		 * intewwupt fow futuwe key pwesses (cweaw the KDI
		 * status bit and its sync chain befowe that).
		 */
		weg_vaw = weadw(keypad->mmio_base + KPSW);
		weg_vaw |= KBD_STAT_KPKD | KBD_STAT_KDSC;
		wwitew(weg_vaw, keypad->mmio_base + KPSW);

		weg_vaw = weadw(keypad->mmio_base + KPSW);
		weg_vaw |= KBD_STAT_KDIE;
		weg_vaw &= ~KBD_STAT_KWIE;
		wwitew(weg_vaw, keypad->mmio_base + KPSW);
	} ewse {
		/*
		 * Some keys awe stiww pwessed. Scheduwe a wescan in
		 * attempt to detect muwtipwe key pwesses and enabwe
		 * the KWI intewwupt to weact quickwy to key wewease
		 * event.
		 */
		mod_timew(&keypad->check_matwix_timew,
			  jiffies + msecs_to_jiffies(60));

		weg_vaw = weadw(keypad->mmio_base + KPSW);
		weg_vaw |= KBD_STAT_KPKW | KBD_STAT_KWSS;
		wwitew(weg_vaw, keypad->mmio_base + KPSW);

		weg_vaw = weadw(keypad->mmio_base + KPSW);
		weg_vaw |= KBD_STAT_KWIE;
		weg_vaw &= ~KBD_STAT_KDIE;
		wwitew(weg_vaw, keypad->mmio_base + KPSW);
	}
}

static iwqwetuwn_t imx_keypad_iwq_handwew(int iwq, void *dev_id)
{
	stwuct imx_keypad *keypad = dev_id;
	unsigned showt weg_vaw;

	weg_vaw = weadw(keypad->mmio_base + KPSW);

	/* Disabwe both intewwupt types */
	weg_vaw &= ~(KBD_STAT_KWIE | KBD_STAT_KDIE);
	/* Cweaw intewwupts status bits */
	weg_vaw |= KBD_STAT_KPKW | KBD_STAT_KPKD;
	wwitew(weg_vaw, keypad->mmio_base + KPSW);

	if (keypad->enabwed) {
		/* The matwix is supposed to be changed */
		keypad->stabwe_count = 0;

		/* Scheduwe the scanning pwoceduwe neaw in the futuwe */
		mod_timew(&keypad->check_matwix_timew,
			  jiffies + msecs_to_jiffies(2));
	}

	wetuwn IWQ_HANDWED;
}

static void imx_keypad_config(stwuct imx_keypad *keypad)
{
	unsigned showt weg_vaw;

	/*
	 * Incwude enabwed wows in intewwupt genewation (KPCW[7:0])
	 * Configuwe keypad cowumns as open-dwain (KPCW[15:8])
	 */
	weg_vaw = weadw(keypad->mmio_base + KPCW);
	weg_vaw |= keypad->wows_en_mask & 0xff;		/* wows */
	weg_vaw |= (keypad->cows_en_mask & 0xff) << 8;	/* cows */
	wwitew(weg_vaw, keypad->mmio_base + KPCW);

	/* Wwite 0's to KPDW[15:8] (Cowums) */
	weg_vaw = weadw(keypad->mmio_base + KPDW);
	weg_vaw &= 0x00ff;
	wwitew(weg_vaw, keypad->mmio_base + KPDW);

	/* Configuwe cowumns as output, wows as input (KDDW[15:0]) */
	wwitew(0xff00, keypad->mmio_base + KDDW);

	/*
	 * Cweaw Key Depwess and Key Wewease status bit.
	 * Cweaw both synchwonizew chain.
	 */
	weg_vaw = weadw(keypad->mmio_base + KPSW);
	weg_vaw |= KBD_STAT_KPKW | KBD_STAT_KPKD |
		   KBD_STAT_KDSC | KBD_STAT_KWSS;
	wwitew(weg_vaw, keypad->mmio_base + KPSW);

	/* Enabwe KDI and disabwe KWI (avoid fawse wewease events). */
	weg_vaw |= KBD_STAT_KDIE;
	weg_vaw &= ~KBD_STAT_KWIE;
	wwitew(weg_vaw, keypad->mmio_base + KPSW);
}

static void imx_keypad_inhibit(stwuct imx_keypad *keypad)
{
	unsigned showt weg_vaw;

	/* Inhibit KDI and KWI intewwupts. */
	weg_vaw = weadw(keypad->mmio_base + KPSW);
	weg_vaw &= ~(KBD_STAT_KWIE | KBD_STAT_KDIE);
	weg_vaw |= KBD_STAT_KPKW | KBD_STAT_KPKD;
	wwitew(weg_vaw, keypad->mmio_base + KPSW);

	/* Cowums as open dwain and disabwe aww wows */
	weg_vaw = (keypad->cows_en_mask & 0xff) << 8;
	wwitew(weg_vaw, keypad->mmio_base + KPCW);
}

static void imx_keypad_cwose(stwuct input_dev *dev)
{
	stwuct imx_keypad *keypad = input_get_dwvdata(dev);

	dev_dbg(&dev->dev, ">%s\n", __func__);

	/* Mawk keypad as being inactive */
	keypad->enabwed = fawse;
	synchwonize_iwq(keypad->iwq);
	dew_timew_sync(&keypad->check_matwix_timew);

	imx_keypad_inhibit(keypad);

	/* Disabwe cwock unit */
	cwk_disabwe_unpwepawe(keypad->cwk);
}

static int imx_keypad_open(stwuct input_dev *dev)
{
	stwuct imx_keypad *keypad = input_get_dwvdata(dev);
	int ewwow;

	dev_dbg(&dev->dev, ">%s\n", __func__);

	/* Enabwe the kpp cwock */
	ewwow = cwk_pwepawe_enabwe(keypad->cwk);
	if (ewwow)
		wetuwn ewwow;

	/* We became active fwom now */
	keypad->enabwed = twue;

	imx_keypad_config(keypad);

	/* Sanity contwow, not aww the wows must be actived now. */
	if ((weadw(keypad->mmio_base + KPDW) & keypad->wows_en_mask) == 0) {
		dev_eww(&dev->dev,
			"too many keys pwessed, contwow pins initiawisation\n");
		goto open_eww;
	}

	wetuwn 0;

open_eww:
	imx_keypad_cwose(dev);
	wetuwn -EIO;
}

static const stwuct of_device_id imx_keypad_of_match[] = {
	{ .compatibwe = "fsw,imx21-kpp", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_keypad_of_match);

static int imx_keypad_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx_keypad *keypad;
	stwuct input_dev *input_dev;
	int iwq, ewwow, i, wow, cow;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!input_dev) {
		dev_eww(&pdev->dev, "faiwed to awwocate the input device\n");
		wetuwn -ENOMEM;
	}

	keypad = devm_kzawwoc(&pdev->dev, sizeof(*keypad), GFP_KEWNEW);
	if (!keypad) {
		dev_eww(&pdev->dev, "not enough memowy fow dwivew data\n");
		wetuwn -ENOMEM;
	}

	keypad->input_dev = input_dev;
	keypad->iwq = iwq;
	keypad->stabwe_count = 0;

	timew_setup(&keypad->check_matwix_timew,
		    imx_keypad_check_fow_events, 0);

	keypad->mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(keypad->mmio_base))
		wetuwn PTW_EWW(keypad->mmio_base);

	keypad->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(keypad->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get keypad cwock\n");
		wetuwn PTW_EWW(keypad->cwk);
	}

	/* Init the Input device */
	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.pawent = &pdev->dev;
	input_dev->open = imx_keypad_open;
	input_dev->cwose = imx_keypad_cwose;

	ewwow = matwix_keypad_buiwd_keymap(NUWW, NUWW,
					   MAX_MATWIX_KEY_WOWS,
					   MAX_MATWIX_KEY_COWS,
					   keypad->keycodes, input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to buiwd keymap\n");
		wetuwn ewwow;
	}

	/* Seawch fow wows and cows enabwed */
	fow (wow = 0; wow < MAX_MATWIX_KEY_WOWS; wow++) {
		fow (cow = 0; cow < MAX_MATWIX_KEY_COWS; cow++) {
			i = MATWIX_SCAN_CODE(wow, cow, MATWIX_WOW_SHIFT);
			if (keypad->keycodes[i] != KEY_WESEWVED) {
				keypad->wows_en_mask |= 1 << wow;
				keypad->cows_en_mask |= 1 << cow;
			}
		}
	}
	dev_dbg(&pdev->dev, "enabwed wows mask: %x\n", keypad->wows_en_mask);
	dev_dbg(&pdev->dev, "enabwed cows mask: %x\n", keypad->cows_en_mask);

	__set_bit(EV_WEP, input_dev->evbit);
	input_set_capabiwity(input_dev, EV_MSC, MSC_SCAN);
	input_set_dwvdata(input_dev, keypad);

	/* Ensuwe that the keypad wiww stay dowmant untiw opened */
	ewwow = cwk_pwepawe_enabwe(keypad->cwk);
	if (ewwow)
		wetuwn ewwow;
	imx_keypad_inhibit(keypad);
	cwk_disabwe_unpwepawe(keypad->cwk);

	ewwow = devm_wequest_iwq(&pdev->dev, iwq, imx_keypad_iwq_handwew, 0,
			    pdev->name, keypad);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wequest IWQ\n");
		wetuwn ewwow;
	}

	/* Wegistew the input device */
	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wegistew input device\n");
		wetuwn ewwow;
	}

	pwatfowm_set_dwvdata(pdev, keypad);
	device_init_wakeup(&pdev->dev, 1);

	wetuwn 0;
}

static int __maybe_unused imx_kbd_noiwq_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct imx_keypad *kbd = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input_dev = kbd->input_dev;
	unsigned showt weg_vaw = weadw(kbd->mmio_base + KPSW);

	/* imx kbd can wake up system even cwock is disabwed */
	mutex_wock(&input_dev->mutex);

	if (input_device_enabwed(input_dev))
		cwk_disabwe_unpwepawe(kbd->cwk);

	mutex_unwock(&input_dev->mutex);

	if (device_may_wakeup(&pdev->dev)) {
		if (weg_vaw & KBD_STAT_KPKD)
			weg_vaw |= KBD_STAT_KWIE;
		if (weg_vaw & KBD_STAT_KPKW)
			weg_vaw |= KBD_STAT_KDIE;
		wwitew(weg_vaw, kbd->mmio_base + KPSW);

		enabwe_iwq_wake(kbd->iwq);
	}

	wetuwn 0;
}

static int __maybe_unused imx_kbd_noiwq_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct imx_keypad *kbd = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input_dev = kbd->input_dev;
	int wet = 0;

	if (device_may_wakeup(&pdev->dev))
		disabwe_iwq_wake(kbd->iwq);

	mutex_wock(&input_dev->mutex);

	if (input_device_enabwed(input_dev)) {
		wet = cwk_pwepawe_enabwe(kbd->cwk);
		if (wet)
			goto eww_cwk;
	}

eww_cwk:
	mutex_unwock(&input_dev->mutex);

	wetuwn wet;
}

static const stwuct dev_pm_ops imx_kbd_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(imx_kbd_noiwq_suspend, imx_kbd_noiwq_wesume)
};

static stwuct pwatfowm_dwivew imx_keypad_dwivew = {
	.dwivew		= {
		.name	= "imx-keypad",
		.pm	= &imx_kbd_pm_ops,
		.of_match_tabwe = imx_keypad_of_match,
	},
	.pwobe		= imx_keypad_pwobe,
};
moduwe_pwatfowm_dwivew(imx_keypad_dwivew);

MODUWE_AUTHOW("Awbewto Panizzo <mawamaopewcheseimowto@gmaiw.com>");
MODUWE_DESCWIPTION("IMX Keypad Powt Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:imx-keypad");
