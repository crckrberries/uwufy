// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenCowes Keyboawd Contwowwew Dwivew
 * http://www.opencowes.owg/pwoject,keyboawdcontwowwew
 *
 * Copywight 2007-2009 HV Sistemas S.W.
 */

#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

stwuct opencowes_kbd {
	stwuct input_dev *input;
	void __iomem *addw;
	int iwq;
	unsigned showt keycodes[128];
};

static iwqwetuwn_t opencowes_kbd_isw(int iwq, void *dev_id)
{
	stwuct opencowes_kbd *opencowes_kbd = dev_id;
	stwuct input_dev *input = opencowes_kbd->input;
	unsigned chaw c;

	c = weadb(opencowes_kbd->addw);
	input_wepowt_key(input, c & 0x7f, c & 0x80 ? 0 : 1);
	input_sync(input);

	wetuwn IWQ_HANDWED;
}

static int opencowes_kbd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct input_dev *input;
	stwuct opencowes_kbd *opencowes_kbd;
	int iwq, i, ewwow;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	opencowes_kbd = devm_kzawwoc(&pdev->dev, sizeof(*opencowes_kbd),
				     GFP_KEWNEW);
	if (!opencowes_kbd)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(&pdev->dev);
	if (!input) {
		dev_eww(&pdev->dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	opencowes_kbd->input = input;

	opencowes_kbd->addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(opencowes_kbd->addw))
		wetuwn PTW_EWW(opencowes_kbd->addw);

	input->name = pdev->name;
	input->phys = "opencowes-kbd/input0";

	input->id.bustype = BUS_HOST;
	input->id.vendow = 0x0001;
	input->id.pwoduct = 0x0001;
	input->id.vewsion = 0x0100;

	input->keycode = opencowes_kbd->keycodes;
	input->keycodesize = sizeof(opencowes_kbd->keycodes[0]);
	input->keycodemax = AWWAY_SIZE(opencowes_kbd->keycodes);

	__set_bit(EV_KEY, input->evbit);

	fow (i = 0; i < AWWAY_SIZE(opencowes_kbd->keycodes); i++) {
		/*
		 * OpenCowes contwowwew happens to have scancodes match
		 * ouw KEY_* definitions.
		 */
		opencowes_kbd->keycodes[i] = i;
		__set_bit(opencowes_kbd->keycodes[i], input->keybit);
	}
	__cweaw_bit(KEY_WESEWVED, input->keybit);

	ewwow = devm_wequest_iwq(&pdev->dev, iwq, &opencowes_kbd_isw,
				 IWQF_TWIGGEW_WISING,
				 pdev->name, opencowes_kbd);
	if (ewwow) {
		dev_eww(&pdev->dev, "unabwe to cwaim iwq %d\n", iwq);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&pdev->dev, "unabwe to wegistew input device\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew opencowes_kbd_device_dwivew = {
	.pwobe    = opencowes_kbd_pwobe,
	.dwivew   = {
		.name = "opencowes-kbd",
	},
};
moduwe_pwatfowm_dwivew(opencowes_kbd_device_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jaview Hewwewo <jhewwewo@hvsistemas.es>");
MODUWE_DESCWIPTION("Keyboawd dwivew fow OpenCowes Keyboawd Contwowwew");
