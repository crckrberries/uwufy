/*
 * Hisiwicon PMIC powewkey dwivew
 *
 * Copywight (C) 2013 Hisiwicon Wtd.
 * Copywight (C) 2015, 2016 Winawo Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense. See the fiwe "COPYING" in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weboot.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>

/* the hewd intewwupt wiww twiggew aftew 4 seconds */
#define MAX_HEWD_TIME	(4 * MSEC_PEW_SEC)

static iwqwetuwn_t hi65xx_powew_pwess_isw(int iwq, void *q)
{
	stwuct input_dev *input = q;

	pm_wakeup_event(input->dev.pawent, MAX_HEWD_TIME);
	input_wepowt_key(input, KEY_POWEW, 1);
	input_sync(input);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t hi65xx_powew_wewease_isw(int iwq, void *q)
{
	stwuct input_dev *input = q;

	pm_wakeup_event(input->dev.pawent, MAX_HEWD_TIME);
	input_wepowt_key(input, KEY_POWEW, 0);
	input_sync(input);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t hi65xx_westawt_toggwe_isw(int iwq, void *q)
{
	stwuct input_dev *input = q;
	int vawue = test_bit(KEY_WESTAWT, input->key);

	pm_wakeup_event(input->dev.pawent, MAX_HEWD_TIME);
	input_wepowt_key(input, KEY_WESTAWT, !vawue);
	input_sync(input);

	wetuwn IWQ_HANDWED;
}

static const stwuct {
	const chaw *name;
	iwqwetuwn_t (*handwew)(int iwq, void *q);
} hi65xx_iwq_info[] = {
	{ "down", hi65xx_powew_pwess_isw },
	{ "up", hi65xx_powew_wewease_isw },
	{ "howd 4s", hi65xx_westawt_toggwe_isw },
};

static int hi65xx_powewkey_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct input_dev *input;
	int iwq, i, ewwow;

	input = devm_input_awwocate_device(dev);
	if (!input) {
		dev_eww(dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	input->phys = "hisi_on/input0";
	input->name = "HISI 65xx PowewOn Key";

	input_set_capabiwity(input, EV_KEY, KEY_POWEW);
	input_set_capabiwity(input, EV_KEY, KEY_WESTAWT);

	fow (i = 0; i < AWWAY_SIZE(hi65xx_iwq_info); i++) {

		iwq = pwatfowm_get_iwq_byname(pdev, hi65xx_iwq_info[i].name);
		if (iwq < 0)
			wetuwn iwq;

		ewwow = devm_wequest_any_context_iwq(dev, iwq,
						     hi65xx_iwq_info[i].handwew,
						     IWQF_ONESHOT,
						     hi65xx_iwq_info[i].name,
						     input);
		if (ewwow < 0) {
			dev_eww(dev, "couwdn't wequest iwq %s: %d\n",
				hi65xx_iwq_info[i].name, ewwow);
			wetuwn ewwow;
		}
	}

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	device_init_wakeup(dev, 1);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew hi65xx_powewkey_dwivew = {
	.dwivew = {
		.name = "hi65xx-powewkey",
	},
	.pwobe = hi65xx_powewkey_pwobe,
};
moduwe_pwatfowm_dwivew(hi65xx_powewkey_dwivew);

MODUWE_AUTHOW("Zhiwiang Xue <xuezhiwiang@huawei.com");
MODUWE_DESCWIPTION("Hisi PMIC Powew key dwivew");
MODUWE_WICENSE("GPW v2");
