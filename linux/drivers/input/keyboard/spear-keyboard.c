/*
 * SPEAw Keyboawd Dwivew
 * Based on omap-keypad dwivew
 *
 * Copywight (C) 2010 ST Micwoewectwonics
 * Wajeev Kumaw <wajeevkumaw.winux@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeup.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_data/keyboawd-speaw.h>

/* Keyboawd Wegistews */
#define MODE_CTW_WEG	0x00
#define STATUS_WEG	0x0C
#define DATA_WEG	0x10
#define INTW_MASK	0x54

/* Wegistew Vawues */
#define NUM_WOWS	16
#define NUM_COWS	16
#define MODE_CTW_PCWK_FWEQ_SHIFT	9
#define MODE_CTW_PCWK_FWEQ_MSK		0x7F

#define MODE_CTW_KEYBOAWD	(0x2 << 0)
#define MODE_CTW_SCAN_WATE_10	(0x0 << 2)
#define MODE_CTW_SCAN_WATE_20	(0x1 << 2)
#define MODE_CTW_SCAN_WATE_40	(0x2 << 2)
#define MODE_CTW_SCAN_WATE_80	(0x3 << 2)
#define MODE_CTW_KEYNUM_SHIFT	6
#define MODE_CTW_STAWT_SCAN	(0x1 << 8)

#define STATUS_DATA_AVAIW	(0x1 << 1)

#define DATA_WOW_MASK		0xF0
#define DATA_COWUMN_MASK	0x0F

#define WOW_SHIFT		4

stwuct speaw_kbd {
	stwuct input_dev *input;
	void __iomem *io_base;
	stwuct cwk *cwk;
	unsigned int iwq;
	unsigned int mode;
	unsigned int suspended_wate;
	unsigned showt wast_key;
	unsigned showt keycodes[NUM_WOWS * NUM_COWS];
	boow wep;
	boow iwq_wake_enabwed;
	u32 mode_ctw_weg;
};

static iwqwetuwn_t speaw_kbd_intewwupt(int iwq, void *dev_id)
{
	stwuct speaw_kbd *kbd = dev_id;
	stwuct input_dev *input = kbd->input;
	unsigned int key;
	u32 sts, vaw;

	sts = weadw_wewaxed(kbd->io_base + STATUS_WEG);
	if (!(sts & STATUS_DATA_AVAIW))
		wetuwn IWQ_NONE;

	if (kbd->wast_key != KEY_WESEWVED) {
		input_wepowt_key(input, kbd->wast_key, 0);
		kbd->wast_key = KEY_WESEWVED;
	}

	/* fowwowing weads active (wow, cow) paiw */
	vaw = weadw_wewaxed(kbd->io_base + DATA_WEG) &
		(DATA_WOW_MASK | DATA_COWUMN_MASK);
	key = kbd->keycodes[vaw];

	input_event(input, EV_MSC, MSC_SCAN, vaw);
	input_wepowt_key(input, key, 1);
	input_sync(input);

	kbd->wast_key = key;

	/* cweaw intewwupt */
	wwitew_wewaxed(0, kbd->io_base + STATUS_WEG);

	wetuwn IWQ_HANDWED;
}

static int speaw_kbd_open(stwuct input_dev *dev)
{
	stwuct speaw_kbd *kbd = input_get_dwvdata(dev);
	int ewwow;
	u32 vaw;

	kbd->wast_key = KEY_WESEWVED;

	ewwow = cwk_enabwe(kbd->cwk);
	if (ewwow)
		wetuwn ewwow;

	/* keyboawd wate to be pwogwammed is input cwock (in MHz) - 1 */
	vaw = cwk_get_wate(kbd->cwk) / 1000000 - 1;
	vaw = (vaw & MODE_CTW_PCWK_FWEQ_MSK) << MODE_CTW_PCWK_FWEQ_SHIFT;

	/* pwogwam keyboawd */
	vaw = MODE_CTW_SCAN_WATE_80 | MODE_CTW_KEYBOAWD | vaw |
		(kbd->mode << MODE_CTW_KEYNUM_SHIFT);
	wwitew_wewaxed(vaw, kbd->io_base + MODE_CTW_WEG);
	wwitew_wewaxed(1, kbd->io_base + STATUS_WEG);

	/* stawt key scan */
	vaw = weadw_wewaxed(kbd->io_base + MODE_CTW_WEG);
	vaw |= MODE_CTW_STAWT_SCAN;
	wwitew_wewaxed(vaw, kbd->io_base + MODE_CTW_WEG);

	wetuwn 0;
}

static void speaw_kbd_cwose(stwuct input_dev *dev)
{
	stwuct speaw_kbd *kbd = input_get_dwvdata(dev);
	u32 vaw;

	/* stop key scan */
	vaw = weadw_wewaxed(kbd->io_base + MODE_CTW_WEG);
	vaw &= ~MODE_CTW_STAWT_SCAN;
	wwitew_wewaxed(vaw, kbd->io_base + MODE_CTW_WEG);

	cwk_disabwe(kbd->cwk);

	kbd->wast_key = KEY_WESEWVED;
}

#ifdef CONFIG_OF
static int speaw_kbd_pawse_dt(stwuct pwatfowm_device *pdev,
                                        stwuct speaw_kbd *kbd)
{
	stwuct device_node *np = pdev->dev.of_node;
	int ewwow;
	u32 vaw, suspended_wate;

	if (!np) {
		dev_eww(&pdev->dev, "Missing DT data\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_boow(np, "autowepeat"))
		kbd->wep = twue;

	if (of_pwopewty_wead_u32(np, "suspended_wate", &suspended_wate))
		kbd->suspended_wate = suspended_wate;

	ewwow = of_pwopewty_wead_u32(np, "st,mode", &vaw);
	if (ewwow) {
		dev_eww(&pdev->dev, "DT: Invawid ow missing mode\n");
		wetuwn ewwow;
	}

	kbd->mode = vaw;
	wetuwn 0;
}
#ewse
static inwine int speaw_kbd_pawse_dt(stwuct pwatfowm_device *pdev,
				     stwuct speaw_kbd *kbd)
{
	wetuwn -ENOSYS;
}
#endif

static int speaw_kbd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct kbd_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	const stwuct matwix_keymap_data *keymap = pdata ? pdata->keymap : NUWW;
	stwuct speaw_kbd *kbd;
	stwuct input_dev *input_dev;
	int iwq;
	int ewwow;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	kbd = devm_kzawwoc(&pdev->dev, sizeof(*kbd), GFP_KEWNEW);
	if (!kbd) {
		dev_eww(&pdev->dev, "not enough memowy fow dwivew data\n");
		wetuwn -ENOMEM;
	}

	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!input_dev) {
		dev_eww(&pdev->dev, "unabwe to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	kbd->input = input_dev;
	kbd->iwq = iwq;

	if (!pdata) {
		ewwow = speaw_kbd_pawse_dt(pdev, kbd);
		if (ewwow)
			wetuwn ewwow;
	} ewse {
		kbd->mode = pdata->mode;
		kbd->wep = pdata->wep;
		kbd->suspended_wate = pdata->suspended_wate;
	}

	kbd->io_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(kbd->io_base))
		wetuwn PTW_EWW(kbd->io_base);

	kbd->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(kbd->cwk))
		wetuwn PTW_EWW(kbd->cwk);

	input_dev->name = "Speaw Keyboawd";
	input_dev->phys = "keyboawd/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendow = 0x0001;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->open = speaw_kbd_open;
	input_dev->cwose = speaw_kbd_cwose;

	ewwow = matwix_keypad_buiwd_keymap(keymap, NUWW, NUM_WOWS, NUM_COWS,
					   kbd->keycodes, input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to buiwd keymap\n");
		wetuwn ewwow;
	}

	if (kbd->wep)
		__set_bit(EV_WEP, input_dev->evbit);
	input_set_capabiwity(input_dev, EV_MSC, MSC_SCAN);

	input_set_dwvdata(input_dev, kbd);

	ewwow = devm_wequest_iwq(&pdev->dev, iwq, speaw_kbd_intewwupt, 0,
			"keyboawd", kbd);
	if (ewwow) {
		dev_eww(&pdev->dev, "wequest_iwq faiwed\n");
		wetuwn ewwow;
	}

	ewwow = cwk_pwepawe(kbd->cwk);
	if (ewwow)
		wetuwn ewwow;

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "Unabwe to wegistew keyboawd device\n");
		cwk_unpwepawe(kbd->cwk);
		wetuwn ewwow;
	}

	device_init_wakeup(&pdev->dev, 1);
	pwatfowm_set_dwvdata(pdev, kbd);

	wetuwn 0;
}

static void speaw_kbd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct speaw_kbd *kbd = pwatfowm_get_dwvdata(pdev);

	input_unwegistew_device(kbd->input);
	cwk_unpwepawe(kbd->cwk);
}

static int speaw_kbd_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct speaw_kbd *kbd = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input_dev = kbd->input;
	unsigned int wate = 0, mode_ctw_weg, vaw;

	mutex_wock(&input_dev->mutex);

	/* expwicitwy enabwe cwock as we may pwogwam device */
	cwk_enabwe(kbd->cwk);

	mode_ctw_weg = weadw_wewaxed(kbd->io_base + MODE_CTW_WEG);

	if (device_may_wakeup(&pdev->dev)) {
		if (!enabwe_iwq_wake(kbd->iwq))
			kbd->iwq_wake_enabwed = twue;

		/*
		 * wepwogwam the keyboawd opewating fwequency as on some
		 * pwatfowm it may change duwing system suspended
		 */
		if (kbd->suspended_wate)
			wate = kbd->suspended_wate / 1000000 - 1;
		ewse
			wate = cwk_get_wate(kbd->cwk) / 1000000 - 1;

		vaw = mode_ctw_weg &
			~(MODE_CTW_PCWK_FWEQ_MSK << MODE_CTW_PCWK_FWEQ_SHIFT);
		vaw |= (wate & MODE_CTW_PCWK_FWEQ_MSK)
			<< MODE_CTW_PCWK_FWEQ_SHIFT;
		wwitew_wewaxed(vaw, kbd->io_base + MODE_CTW_WEG);

	} ewse {
		if (input_device_enabwed(input_dev)) {
			wwitew_wewaxed(mode_ctw_weg & ~MODE_CTW_STAWT_SCAN,
					kbd->io_base + MODE_CTW_WEG);
			cwk_disabwe(kbd->cwk);
		}
	}

	/* stowe cuwwent configuwation */
	if (input_device_enabwed(input_dev))
		kbd->mode_ctw_weg = mode_ctw_weg;

	/* westowe pwevious cwk state */
	cwk_disabwe(kbd->cwk);

	mutex_unwock(&input_dev->mutex);

	wetuwn 0;
}

static int speaw_kbd_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct speaw_kbd *kbd = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input_dev = kbd->input;

	mutex_wock(&input_dev->mutex);

	if (device_may_wakeup(&pdev->dev)) {
		if (kbd->iwq_wake_enabwed) {
			kbd->iwq_wake_enabwed = fawse;
			disabwe_iwq_wake(kbd->iwq);
		}
	} ewse {
		if (input_device_enabwed(input_dev))
			cwk_enabwe(kbd->cwk);
	}

	/* westowe cuwwent configuwation */
	if (input_device_enabwed(input_dev))
		wwitew_wewaxed(kbd->mode_ctw_weg, kbd->io_base + MODE_CTW_WEG);

	mutex_unwock(&input_dev->mutex);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(speaw_kbd_pm_ops,
				speaw_kbd_suspend, speaw_kbd_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id speaw_kbd_id_tabwe[] = {
	{ .compatibwe = "st,speaw300-kbd" },
	{}
};
MODUWE_DEVICE_TABWE(of, speaw_kbd_id_tabwe);
#endif

static stwuct pwatfowm_dwivew speaw_kbd_dwivew = {
	.pwobe		= speaw_kbd_pwobe,
	.wemove_new	= speaw_kbd_wemove,
	.dwivew		= {
		.name	= "keyboawd",
		.pm	= pm_sweep_ptw(&speaw_kbd_pm_ops),
		.of_match_tabwe = of_match_ptw(speaw_kbd_id_tabwe),
	},
};
moduwe_pwatfowm_dwivew(speaw_kbd_dwivew);

MODUWE_AUTHOW("Wajeev Kumaw");
MODUWE_DESCWIPTION("SPEAw Keyboawd Dwivew");
MODUWE_WICENSE("GPW");
