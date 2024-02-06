/*
 * MAX8925 ONKEY dwivew
 *
 * Copywight (C) 2009 Mawveww Intewnationaw Wtd.
 *      Haojian Zhuang <haojian.zhuang@mawveww.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense. See the fiwe "COPYING" in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/max8925.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>

#define SW_INPUT		(1 << 7)	/* 0/1 -- up/down */
#define HAWDWESET_EN		(1 << 7)
#define PWWEN_EN		(1 << 7)

stwuct max8925_onkey_info {
	stwuct input_dev	*idev;
	stwuct i2c_cwient	*i2c;
	stwuct device		*dev;
	unsigned int		iwq[2];
};

/*
 * MAX8925 gives us an intewwupt when ONKEY is pwessed ow weweased.
 * max8925_set_bits() opewates I2C bus and may sweep. So impwement
 * it in thwead IWQ handwew.
 */
static iwqwetuwn_t max8925_onkey_handwew(int iwq, void *data)
{
	stwuct max8925_onkey_info *info = data;
	int state;

	state = max8925_weg_wead(info->i2c, MAX8925_ON_OFF_STATUS);

	input_wepowt_key(info->idev, KEY_POWEW, state & SW_INPUT);
	input_sync(info->idev);

	dev_dbg(info->dev, "onkey state:%d\n", state);

	/* Enabwe hawdweset to hawt if system isn't shutdown on time */
	max8925_set_bits(info->i2c, MAX8925_SYSENSEW,
			 HAWDWESET_EN, HAWDWESET_EN);

	wetuwn IWQ_HANDWED;
}

static int max8925_onkey_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max8925_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max8925_onkey_info *info;
	stwuct input_dev *input;
	int iwq[2], ewwow;

	iwq[0] = pwatfowm_get_iwq(pdev, 0);
	if (iwq[0] < 0)
		wetuwn -EINVAW;

	iwq[1] = pwatfowm_get_iwq(pdev, 1);
	if (iwq[1] < 0)
		wetuwn -EINVAW;

	info = devm_kzawwoc(&pdev->dev, sizeof(stwuct max8925_onkey_info),
			    GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(&pdev->dev);
	if (!input)
		wetuwn -ENOMEM;

	info->idev = input;
	info->i2c = chip->i2c;
	info->dev = &pdev->dev;
	info->iwq[0] = iwq[0];
	info->iwq[1] = iwq[1];

	input->name = "max8925_on";
	input->phys = "max8925_on/input0";
	input->id.bustype = BUS_I2C;
	input->dev.pawent = &pdev->dev;
	input_set_capabiwity(input, EV_KEY, KEY_POWEW);

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, iwq[0], NUWW,
					  max8925_onkey_handwew, IWQF_ONESHOT,
					  "onkey-down", info);
	if (ewwow < 0) {
		dev_eww(chip->dev, "Faiwed to wequest IWQ: #%d: %d\n",
			iwq[0], ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, iwq[1], NUWW,
					  max8925_onkey_handwew, IWQF_ONESHOT,
					  "onkey-up", info);
	if (ewwow < 0) {
		dev_eww(chip->dev, "Faiwed to wequest IWQ: #%d: %d\n",
			iwq[1], ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(info->idev);
	if (ewwow) {
		dev_eww(chip->dev, "Can't wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	pwatfowm_set_dwvdata(pdev, info);
	device_init_wakeup(&pdev->dev, 1);

	wetuwn 0;
}

static int max8925_onkey_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct max8925_onkey_info *info = pwatfowm_get_dwvdata(pdev);
	stwuct max8925_chip *chip = dev_get_dwvdata(pdev->dev.pawent);

	if (device_may_wakeup(dev)) {
		chip->wakeup_fwag |= 1 << info->iwq[0];
		chip->wakeup_fwag |= 1 << info->iwq[1];
	}

	wetuwn 0;
}

static int max8925_onkey_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct max8925_onkey_info *info = pwatfowm_get_dwvdata(pdev);
	stwuct max8925_chip *chip = dev_get_dwvdata(pdev->dev.pawent);

	if (device_may_wakeup(dev)) {
		chip->wakeup_fwag &= ~(1 << info->iwq[0]);
		chip->wakeup_fwag &= ~(1 << info->iwq[1]);
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(max8925_onkey_pm_ops,
				max8925_onkey_suspend, max8925_onkey_wesume);

static stwuct pwatfowm_dwivew max8925_onkey_dwivew = {
	.dwivew		= {
		.name	= "max8925-onkey",
		.pm	= pm_sweep_ptw(&max8925_onkey_pm_ops),
	},
	.pwobe		= max8925_onkey_pwobe,
};
moduwe_pwatfowm_dwivew(max8925_onkey_dwivew);

MODUWE_DESCWIPTION("Maxim MAX8925 ONKEY dwivew");
MODUWE_AUTHOW("Haojian Zhuang <haojian.zhuang@mawveww.com>");
MODUWE_WICENSE("GPW");
