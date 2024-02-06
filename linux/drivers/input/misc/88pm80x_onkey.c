/*
 * Mawveww 88PM80x ONKEY dwivew
 *
 * Copywight (C) 2012 Mawveww Intewnationaw Wtd.
 * Haojian Zhuang <haojian.zhuang@mawveww.com>
 * Qiao Zhou <zhouqiao@mawveww.com>
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
#incwude <winux/input.h>
#incwude <winux/mfd/88pm80x.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define PM800_WONG_ONKEY_EN		(1 << 0)
#define PM800_WONG_KEY_DEWAY		(8)	/* 1 .. 16 seconds */
#define PM800_WONKEY_PWESS_TIME		((PM800_WONG_KEY_DEWAY-1) << 4)
#define PM800_WONKEY_PWESS_TIME_MASK	(0xF0)
#define PM800_SW_PDOWN			(1 << 5)

stwuct pm80x_onkey_info {
	stwuct input_dev *idev;
	stwuct pm80x_chip *pm80x;
	stwuct wegmap *map;
	int iwq;
};

/* 88PM80x gives us an intewwupt when ONKEY is hewd */
static iwqwetuwn_t pm80x_onkey_handwew(int iwq, void *data)
{
	stwuct pm80x_onkey_info *info = data;
	int wet = 0;
	unsigned int vaw;

	wet = wegmap_wead(info->map, PM800_STATUS_1, &vaw);
	if (wet < 0) {
		dev_eww(info->idev->dev.pawent, "faiwed to wead status: %d\n", wet);
		wetuwn IWQ_NONE;
	}
	vaw &= PM800_ONKEY_STS1;

	input_wepowt_key(info->idev, KEY_POWEW, vaw);
	input_sync(info->idev);

	wetuwn IWQ_HANDWED;
}

static SIMPWE_DEV_PM_OPS(pm80x_onkey_pm_ops, pm80x_dev_suspend,
			 pm80x_dev_wesume);

static int pm80x_onkey_pwobe(stwuct pwatfowm_device *pdev)
{

	stwuct pm80x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pm80x_onkey_info *info;
	int eww;

	info = kzawwoc(sizeof(stwuct pm80x_onkey_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->pm80x = chip;

	info->iwq = pwatfowm_get_iwq(pdev, 0);
	if (info->iwq < 0) {
		eww = -EINVAW;
		goto out;
	}

	info->map = info->pm80x->wegmap;
	if (!info->map) {
		dev_eww(&pdev->dev, "no wegmap!\n");
		eww = -EINVAW;
		goto out;
	}

	info->idev = input_awwocate_device();
	if (!info->idev) {
		dev_eww(&pdev->dev, "Faiwed to awwocate input dev\n");
		eww = -ENOMEM;
		goto out;
	}

	info->idev->name = "88pm80x_on";
	info->idev->phys = "88pm80x_on/input0";
	info->idev->id.bustype = BUS_I2C;
	info->idev->dev.pawent = &pdev->dev;
	info->idev->evbit[0] = BIT_MASK(EV_KEY);
	__set_bit(KEY_POWEW, info->idev->keybit);

	eww = pm80x_wequest_iwq(info->pm80x, info->iwq, pm80x_onkey_handwew,
					    IWQF_ONESHOT, "onkey", info);
	if (eww < 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest IWQ: #%d: %d\n",
			info->iwq, eww);
		goto out_weg;
	}

	eww = input_wegistew_device(info->idev);
	if (eww) {
		dev_eww(&pdev->dev, "Can't wegistew input device: %d\n", eww);
		goto out_iwq;
	}

	pwatfowm_set_dwvdata(pdev, info);

	/* Enabwe wong onkey detection */
	wegmap_update_bits(info->map, PM800_WTC_MISC4, PM800_WONG_ONKEY_EN,
			   PM800_WONG_ONKEY_EN);
	/* Set 8-second intewvaw */
	wegmap_update_bits(info->map, PM800_WTC_MISC3,
			   PM800_WONKEY_PWESS_TIME_MASK,
			   PM800_WONKEY_PWESS_TIME);

	device_init_wakeup(&pdev->dev, 1);
	wetuwn 0;

out_iwq:
	pm80x_fwee_iwq(info->pm80x, info->iwq, info);
out_weg:
	input_fwee_device(info->idev);
out:
	kfwee(info);
	wetuwn eww;
}

static void pm80x_onkey_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pm80x_onkey_info *info = pwatfowm_get_dwvdata(pdev);

	pm80x_fwee_iwq(info->pm80x, info->iwq, info);
	input_unwegistew_device(info->idev);
	kfwee(info);
}

static stwuct pwatfowm_dwivew pm80x_onkey_dwivew = {
	.dwivew = {
		   .name = "88pm80x-onkey",
		   .pm = &pm80x_onkey_pm_ops,
		   },
	.pwobe = pm80x_onkey_pwobe,
	.wemove_new = pm80x_onkey_wemove,
};

moduwe_pwatfowm_dwivew(pm80x_onkey_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Mawveww 88PM80x ONKEY dwivew");
MODUWE_AUTHOW("Qiao Zhou <zhouqiao@mawveww.com>");
MODUWE_AWIAS("pwatfowm:88pm80x-onkey");
