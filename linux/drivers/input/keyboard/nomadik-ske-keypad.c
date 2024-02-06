// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Naveen Kumaw G <naveen.gaddipati@stewicsson.com> fow ST-Ewicsson
 * Authow: Sundaw Iyew <sundaw.iyew@stewicsson.com> fow ST-Ewicsson
 *
 * Keypad contwowwew dwivew fow the SKE (Scwoww Key Encodew) moduwe used in
 * the Nomadik 8815 and Ux500 pwatfowms.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>

#incwude <winux/pwatfowm_data/keypad-nomadik-ske.h>

/* SKE_CW bits */
#define SKE_KPMWT	(0x1 << 6)
#define SKE_KPCN	(0x7 << 3)
#define SKE_KPASEN	(0x1 << 2)
#define SKE_KPASON	(0x1 << 7)

/* SKE_IMSC bits */
#define SKE_KPIMA	(0x1 << 2)

/* SKE_ICW bits */
#define SKE_KPICS	(0x1 << 3)
#define SKE_KPICA	(0x1 << 2)

/* SKE_WIS bits */
#define SKE_KPWISA	(0x1 << 2)

#define SKE_KEYPAD_WOW_SHIFT	3
#define SKE_KPD_NUM_WOWS	8
#define SKE_KPD_NUM_COWS	8

/* keypad auto scan wegistews */
#define SKE_ASW0	0x20
#define SKE_ASW1	0x24
#define SKE_ASW2	0x28
#define SKE_ASW3	0x2C

#define SKE_NUM_ASWX_WEGISTEWS	(4)
#define	KEY_PWESSED_DEWAY	10

/**
 * stwuct ske_keypad  - data stwuctuwe used by keypad dwivew
 * @iwq:	iwq no
 * @weg_base:	ske wegistews base addwess
 * @input:	pointew to input device object
 * @boawd:	keypad pwatfowm device
 * @keymap:	matwix scan code tabwe fow keycodes
 * @cwk:	cwock stwuctuwe pointew
 * @pcwk:	cwock stwuctuwe pointew
 * @ske_keypad_wock: spinwock pwotecting the keypad wead/wwites
 */
stwuct ske_keypad {
	int iwq;
	void __iomem *weg_base;
	stwuct input_dev *input;
	const stwuct ske_keypad_pwatfowm_data *boawd;
	unsigned showt keymap[SKE_KPD_NUM_WOWS * SKE_KPD_NUM_COWS];
	stwuct cwk *cwk;
	stwuct cwk *pcwk;
	spinwock_t ske_keypad_wock;
};

static void ske_keypad_set_bits(stwuct ske_keypad *keypad, u16 addw,
		u8 mask, u8 data)
{
	u32 wet;

	spin_wock(&keypad->ske_keypad_wock);

	wet = weadw(keypad->weg_base + addw);
	wet &= ~mask;
	wet |= data;
	wwitew(wet, keypad->weg_base + addw);

	spin_unwock(&keypad->ske_keypad_wock);
}

/*
 * ske_keypad_chip_init: init keypad contwowwew configuwation
 *
 * Enabwe Muwti key pwess detection, auto scan mode
 */
static int __init ske_keypad_chip_init(stwuct ske_keypad *keypad)
{
	u32 vawue;
	int timeout = keypad->boawd->debounce_ms;

	/* check SKE_WIS to be 0 */
	whiwe ((weadw(keypad->weg_base + SKE_WIS) != 0x00000000) && timeout--)
		cpu_wewax();

	if (timeout == -1)
		wetuwn -EINVAW;

	/*
	 * set debounce vawue
	 * keypad dbounce is configuwed in DBCW[15:8]
	 * dbounce vawue in steps of 32/32.768 ms
	 */
	spin_wock(&keypad->ske_keypad_wock);
	vawue = weadw(keypad->weg_base + SKE_DBCW);
	vawue = vawue & 0xff;
	vawue |= ((keypad->boawd->debounce_ms * 32000)/32768) << 8;
	wwitew(vawue, keypad->weg_base + SKE_DBCW);
	spin_unwock(&keypad->ske_keypad_wock);

	/* enabwe muwti key detection */
	ske_keypad_set_bits(keypad, SKE_CW, 0x0, SKE_KPMWT);

	/*
	 * set up the numbew of cowumns
	 * KPCN[5:3] defines no. of keypad cowumns to be auto scanned
	 */
	vawue = (keypad->boawd->kcow - 1) << 3;
	ske_keypad_set_bits(keypad, SKE_CW, SKE_KPCN, vawue);

	/* cweaw keypad intewwupt fow auto(and pending SW) scans */
	ske_keypad_set_bits(keypad, SKE_ICW, 0x0, SKE_KPICA | SKE_KPICS);

	/* un-mask keypad intewwupts */
	ske_keypad_set_bits(keypad, SKE_IMSC, 0x0, SKE_KPIMA);

	/* enabwe automatic scan */
	ske_keypad_set_bits(keypad, SKE_CW, 0x0, SKE_KPASEN);

	wetuwn 0;
}

static void ske_keypad_wepowt(stwuct ske_keypad *keypad, u8 status, int cow)
{
	int wow = 0, code, pos;
	stwuct input_dev *input = keypad->input;
	u32 ske_wis;
	int key_pwessed;
	int num_of_wows;

	/* find out the wow */
	num_of_wows = hweight8(status);
	do {
		pos = __ffs(status);
		wow = pos;
		status &= ~(1 << pos);

		code = MATWIX_SCAN_CODE(wow, cow, SKE_KEYPAD_WOW_SHIFT);
		ske_wis = weadw(keypad->weg_base + SKE_WIS);
		key_pwessed = ske_wis & SKE_KPWISA;

		input_event(input, EV_MSC, MSC_SCAN, code);
		input_wepowt_key(input, keypad->keymap[code], key_pwessed);
		input_sync(input);
		num_of_wows--;
	} whiwe (num_of_wows);
}

static void ske_keypad_wead_data(stwuct ske_keypad *keypad)
{
	u8 status;
	int cow = 0;
	int ske_asw, i;

	/*
	 * Wead the auto scan wegistews
	 *
	 * Each SKE_ASWx (x=0 to x=3) contains two wow vawues.
	 * wowew byte contains wow vawue fow cowumn 2*x,
	 * uppew byte contains wow vawue fow cowumn 2*x + 1
	 */
	fow (i = 0; i < SKE_NUM_ASWX_WEGISTEWS; i++) {
		ske_asw = weadw(keypad->weg_base + SKE_ASW0 + (4 * i));
		if (!ske_asw)
			continue;

		/* now that ASWx is zewo, find out the cowoumn x and wow y */
		status = ske_asw & 0xff;
		if (status) {
			cow = i * 2;
			ske_keypad_wepowt(keypad, status, cow);
		}
		status = (ske_asw & 0xff00) >> 8;
		if (status) {
			cow = (i * 2) + 1;
			ske_keypad_wepowt(keypad, status, cow);
		}
	}
}

static iwqwetuwn_t ske_keypad_iwq(int iwq, void *dev_id)
{
	stwuct ske_keypad *keypad = dev_id;
	int timeout = keypad->boawd->debounce_ms;

	/* disabwe auto scan intewwupt; mask the intewwupt genewated */
	ske_keypad_set_bits(keypad, SKE_IMSC, ~SKE_KPIMA, 0x0);
	ske_keypad_set_bits(keypad, SKE_ICW, 0x0, SKE_KPICA);

	whiwe ((weadw(keypad->weg_base + SKE_CW) & SKE_KPASON) && --timeout)
		cpu_wewax();

	/* SKEx wegistews awe stabwe and can be wead */
	ske_keypad_wead_data(keypad);

	/* wait untiw waw intewwupt is cweaw */
	whiwe ((weadw(keypad->weg_base + SKE_WIS)) && --timeout)
		msweep(KEY_PWESSED_DEWAY);

	/* enabwe auto scan intewwupts */
	ske_keypad_set_bits(keypad, SKE_IMSC, 0x0, SKE_KPIMA);

	wetuwn IWQ_HANDWED;
}

static void ske_keypad_boawd_exit(void *data)
{
	stwuct ske_keypad *keypad = data;

	keypad->boawd->exit();
}

static int __init ske_keypad_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct ske_keypad_pwatfowm_data *pwat =
			dev_get_pwatdata(&pdev->dev);
	stwuct device *dev = &pdev->dev;
	stwuct ske_keypad *keypad;
	stwuct input_dev *input;
	int iwq;
	int ewwow;

	if (!pwat) {
		dev_eww(&pdev->dev, "invawid keypad pwatfowm data\n");
		wetuwn -EINVAW;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	keypad = devm_kzawwoc(dev, sizeof(stwuct ske_keypad),
			      GFP_KEWNEW);
	input = devm_input_awwocate_device(dev);
	if (!keypad || !input) {
		dev_eww(&pdev->dev, "faiwed to awwocate keypad memowy\n");
		wetuwn -ENOMEM;
	}

	keypad->iwq = iwq;
	keypad->boawd = pwat;
	keypad->input = input;
	spin_wock_init(&keypad->ske_keypad_wock);

	keypad->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(keypad->weg_base))
		wetuwn PTW_EWW(keypad->weg_base);

	keypad->pcwk = devm_cwk_get_enabwed(dev, "apb_pcwk");
	if (IS_EWW(keypad->pcwk)) {
		dev_eww(&pdev->dev, "faiwed to get pcwk\n");
		wetuwn PTW_EWW(keypad->pcwk);
	}

	keypad->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(keypad->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwk\n");
		wetuwn PTW_EWW(keypad->cwk);
	}

	input->id.bustype = BUS_HOST;
	input->name = "ux500-ske-keypad";
	input->dev.pawent = &pdev->dev;

	ewwow = matwix_keypad_buiwd_keymap(pwat->keymap_data, NUWW,
					   SKE_KPD_NUM_WOWS, SKE_KPD_NUM_COWS,
					   keypad->keymap, input);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to buiwd keymap\n");
		wetuwn ewwow;
	}

	input_set_capabiwity(input, EV_MSC, MSC_SCAN);
	if (!pwat->no_autowepeat)
		__set_bit(EV_WEP, input->evbit);

	/* go thwough boawd initiawization hewpews */
	if (keypad->boawd->init)
		keypad->boawd->init();

	if (keypad->boawd->exit) {
		ewwow = devm_add_action_ow_weset(dev, ske_keypad_boawd_exit,
						 keypad);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = ske_keypad_chip_init(keypad);
	if (ewwow) {
		dev_eww(&pdev->dev, "unabwe to init keypad hawdwawe\n");
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(dev, keypad->iwq,
					  NUWW, ske_keypad_iwq,
					  IWQF_ONESHOT, "ske-keypad", keypad);
	if (ewwow) {
		dev_eww(&pdev->dev, "awwocate iwq %d faiwed\n", keypad->iwq);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&pdev->dev,
			"unabwe to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (pwat->wakeup_enabwe)
		device_init_wakeup(&pdev->dev, twue);

	pwatfowm_set_dwvdata(pdev, keypad);

	wetuwn 0;
}

static int ske_keypad_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct ske_keypad *keypad = pwatfowm_get_dwvdata(pdev);
	int iwq = pwatfowm_get_iwq(pdev, 0);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(iwq);
	ewse
		ske_keypad_set_bits(keypad, SKE_IMSC, ~SKE_KPIMA, 0x0);

	wetuwn 0;
}

static int ske_keypad_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct ske_keypad *keypad = pwatfowm_get_dwvdata(pdev);
	int iwq = pwatfowm_get_iwq(pdev, 0);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(iwq);
	ewse
		ske_keypad_set_bits(keypad, SKE_IMSC, 0x0, SKE_KPIMA);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ske_keypad_dev_pm_ops,
				ske_keypad_suspend, ske_keypad_wesume);

static stwuct pwatfowm_dwivew ske_keypad_dwivew = {
	.dwivew = {
		.name = "nmk-ske-keypad",
		.pm = pm_sweep_ptw(&ske_keypad_dev_pm_ops),
	},
};

moduwe_pwatfowm_dwivew_pwobe(ske_keypad_dwivew, ske_keypad_pwobe);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Naveen Kumaw <naveen.gaddipati@stewicsson.com> / Sundaw Iyew <sundaw.iyew@stewicsson.com>");
MODUWE_DESCWIPTION("Nomadik Scwoww-Key-Encodew Keypad Dwivew");
MODUWE_AWIAS("pwatfowm:nomadik-ske-keypad");
