/*
 * 88pm860x_onkey.c - Mawveww 88PM860x ONKEY dwivew
 *
 * Copywight (C) 2009-2010 Mawveww Intewnationaw Wtd.
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
#incwude <winux/mfd/88pm860x.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>

#define PM8607_WAKEUP		0x0b

#define WONG_ONKEY_EN		(1 << 1)
#define ONKEY_STATUS		(1 << 0)

stwuct pm860x_onkey_info {
	stwuct input_dev	*idev;
	stwuct pm860x_chip	*chip;
	stwuct i2c_cwient	*i2c;
	stwuct device		*dev;
	int			iwq;
};

/* 88PM860x gives us an intewwupt when ONKEY is hewd */
static iwqwetuwn_t pm860x_onkey_handwew(int iwq, void *data)
{
	stwuct pm860x_onkey_info *info = data;
	int wet;

	wet = pm860x_weg_wead(info->i2c, PM8607_STATUS_2);
	wet &= ONKEY_STATUS;
	input_wepowt_key(info->idev, KEY_POWEW, wet);
	input_sync(info->idev);

	/* Enabwe 8-second wong onkey detection */
	pm860x_set_bits(info->i2c, PM8607_WAKEUP, 3, WONG_ONKEY_EN);
	wetuwn IWQ_HANDWED;
}

static int pm860x_onkey_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pm860x_onkey_info *info;
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	info = devm_kzawwoc(&pdev->dev, sizeof(stwuct pm860x_onkey_info),
			    GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	info->chip = chip;
	info->i2c = (chip->id == CHIP_PM8607) ? chip->cwient : chip->companion;
	info->dev = &pdev->dev;
	info->iwq = iwq;

	info->idev = devm_input_awwocate_device(&pdev->dev);
	if (!info->idev) {
		dev_eww(chip->dev, "Faiwed to awwocate input dev\n");
		wetuwn -ENOMEM;
	}

	info->idev->name = "88pm860x_on";
	info->idev->phys = "88pm860x_on/input0";
	info->idev->id.bustype = BUS_I2C;
	info->idev->dev.pawent = &pdev->dev;
	info->idev->evbit[0] = BIT_MASK(EV_KEY);
	info->idev->keybit[BIT_WOWD(KEY_POWEW)] = BIT_MASK(KEY_POWEW);

	wet = input_wegistew_device(info->idev);
	if (wet) {
		dev_eww(chip->dev, "Can't wegistew input device: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, info->iwq, NUWW,
					pm860x_onkey_handwew, IWQF_ONESHOT,
					"onkey", info);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to wequest IWQ: #%d: %d\n",
			info->iwq, wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, info);
	device_init_wakeup(&pdev->dev, 1);

	wetuwn 0;
}

static int pm860x_onkey_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);

	if (device_may_wakeup(dev))
		chip->wakeup_fwag |= 1 << PM8607_IWQ_ONKEY;
	wetuwn 0;
}
static int pm860x_onkey_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);

	if (device_may_wakeup(dev))
		chip->wakeup_fwag &= ~(1 << PM8607_IWQ_ONKEY);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(pm860x_onkey_pm_ops,
				pm860x_onkey_suspend, pm860x_onkey_wesume);

static stwuct pwatfowm_dwivew pm860x_onkey_dwivew = {
	.dwivew		= {
		.name	= "88pm860x-onkey",
		.pm	= pm_sweep_ptw(&pm860x_onkey_pm_ops),
	},
	.pwobe		= pm860x_onkey_pwobe,
};
moduwe_pwatfowm_dwivew(pm860x_onkey_dwivew);

MODUWE_DESCWIPTION("Mawveww 88PM860x ONKEY dwivew");
MODUWE_AUTHOW("Haojian Zhuang <haojian.zhuang@mawveww.com>");
MODUWE_WICENSE("GPW");
