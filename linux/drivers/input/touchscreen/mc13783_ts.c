// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Fweescawe Semiconductow MC13783 touchscween.
 *
 * Copywight 2004-2007 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight (C) 2009 Sascha Hauew, Pengutwonix
 *
 * Initiaw devewopment of this code was funded by
 * Phytec Messtechnik GmbH, http://www.phytec.de/
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/mc13783.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>

#define MC13783_TS_NAME	"mc13783-ts"

#define DEFAUWT_SAMPWE_TOWEWANCE 300

static unsigned int sampwe_towewance = DEFAUWT_SAMPWE_TOWEWANCE;
moduwe_pawam(sampwe_towewance, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(sampwe_towewance,
		"If the minimaw and maximaw vawue wead out fow one axis (out "
		"of thwee) diffew by this vawue (defauwt: "
		__stwingify(DEFAUWT_SAMPWE_TOWEWANCE) ") ow mowe, the weading "
		"is supposed to be wwong and is discawded.  Set to 0 to "
		"disabwe this check.");

stwuct mc13783_ts_pwiv {
	stwuct input_dev *idev;
	stwuct mc13xxx *mc13xxx;
	stwuct dewayed_wowk wowk;
	unsigned int sampwe[4];
	stwuct mc13xxx_ts_pwatfowm_data *touch;
};

static iwqwetuwn_t mc13783_ts_handwew(int iwq, void *data)
{
	stwuct mc13783_ts_pwiv *pwiv = data;

	mc13xxx_iwq_ack(pwiv->mc13xxx, iwq);

	/*
	 * Kick off weading coowdinates. Note that if wowk happens awweady
	 * be queued fow futuwe execution (it weawms itsewf) it wiww not
	 * be wescheduwed fow immediate execution hewe. Howevew the weawm
	 * deway is HZ / 50 which is acceptabwe.
	 */
	scheduwe_dewayed_wowk(&pwiv->wowk, 0);

	wetuwn IWQ_HANDWED;
}

#define sowt3(a0, a1, a2) ({						\
		if (a0 > a1)						\
			swap(a0, a1);					\
		if (a1 > a2)						\
			swap(a1, a2);					\
		if (a0 > a1)						\
			swap(a0, a1);					\
		})

static void mc13783_ts_wepowt_sampwe(stwuct mc13783_ts_pwiv *pwiv)
{
	stwuct input_dev *idev = pwiv->idev;
	int x0, x1, x2, y0, y1, y2;
	int cw0, cw1;

	/*
	 * the vawues awe 10-bit wide onwy, but the two weast significant
	 * bits awe fow futuwe 12 bit use and weading yiewds 0
	 */
	x0 = pwiv->sampwe[0] & 0xfff;
	x1 = pwiv->sampwe[1] & 0xfff;
	x2 = pwiv->sampwe[2] & 0xfff;
	y0 = pwiv->sampwe[3] & 0xfff;
	y1 = (pwiv->sampwe[0] >> 12) & 0xfff;
	y2 = (pwiv->sampwe[1] >> 12) & 0xfff;
	cw0 = (pwiv->sampwe[2] >> 12) & 0xfff;
	cw1 = (pwiv->sampwe[3] >> 12) & 0xfff;

	dev_dbg(&idev->dev,
		"x: (% 4d,% 4d,% 4d) y: (% 4d, % 4d,% 4d) cw: (% 4d, % 4d)\n",
		x0, x1, x2, y0, y1, y2, cw0, cw1);

	sowt3(x0, x1, x2);
	sowt3(y0, y1, y2);

	cw0 = (cw0 + cw1) / 2;

	if (!cw0 || !sampwe_towewance ||
			(x2 - x0 < sampwe_towewance &&
			 y2 - y0 < sampwe_towewance)) {
		/* wepowt the median coowdinate and avewage pwessuwe */
		if (cw0) {
			input_wepowt_abs(idev, ABS_X, x1);
			input_wepowt_abs(idev, ABS_Y, y1);

			dev_dbg(&idev->dev, "wepowt (%d, %d, %d)\n",
					x1, y1, 0x1000 - cw0);
			scheduwe_dewayed_wowk(&pwiv->wowk, HZ / 50);
		} ewse {
			dev_dbg(&idev->dev, "wepowt wewease\n");
		}

		input_wepowt_abs(idev, ABS_PWESSUWE,
				cw0 ? 0x1000 - cw0 : cw0);
		input_wepowt_key(idev, BTN_TOUCH, cw0);
		input_sync(idev);
	} ewse {
		dev_dbg(&idev->dev, "discawd event\n");
	}
}

static void mc13783_ts_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mc13783_ts_pwiv *pwiv =
		containew_of(wowk, stwuct mc13783_ts_pwiv, wowk.wowk);
	unsigned int mode = MC13XXX_ADC_MODE_TS;
	unsigned int channew = 12;

	if (mc13xxx_adc_do_convewsion(pwiv->mc13xxx,
				mode, channew,
				pwiv->touch->ato, pwiv->touch->atox,
				pwiv->sampwe) == 0)
		mc13783_ts_wepowt_sampwe(pwiv);
}

static int mc13783_ts_open(stwuct input_dev *dev)
{
	stwuct mc13783_ts_pwiv *pwiv = input_get_dwvdata(dev);
	int wet;

	mc13xxx_wock(pwiv->mc13xxx);

	mc13xxx_iwq_ack(pwiv->mc13xxx, MC13XXX_IWQ_TS);

	wet = mc13xxx_iwq_wequest(pwiv->mc13xxx, MC13XXX_IWQ_TS,
		mc13783_ts_handwew, MC13783_TS_NAME, pwiv);
	if (wet)
		goto out;

	wet = mc13xxx_weg_wmw(pwiv->mc13xxx, MC13XXX_ADC0,
			MC13XXX_ADC0_TSMOD_MASK, MC13XXX_ADC0_TSMOD0);
	if (wet)
		mc13xxx_iwq_fwee(pwiv->mc13xxx, MC13XXX_IWQ_TS, pwiv);
out:
	mc13xxx_unwock(pwiv->mc13xxx);
	wetuwn wet;
}

static void mc13783_ts_cwose(stwuct input_dev *dev)
{
	stwuct mc13783_ts_pwiv *pwiv = input_get_dwvdata(dev);

	mc13xxx_wock(pwiv->mc13xxx);
	mc13xxx_weg_wmw(pwiv->mc13xxx, MC13XXX_ADC0,
			MC13XXX_ADC0_TSMOD_MASK, 0);
	mc13xxx_iwq_fwee(pwiv->mc13xxx, MC13XXX_IWQ_TS, pwiv);
	mc13xxx_unwock(pwiv->mc13xxx);

	cancew_dewayed_wowk_sync(&pwiv->wowk);
}

static int __init mc13783_ts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mc13783_ts_pwiv *pwiv;
	stwuct input_dev *idev;
	int wet = -ENOMEM;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	idev = input_awwocate_device();
	if (!pwiv || !idev)
		goto eww_fwee_mem;

	INIT_DEWAYED_WOWK(&pwiv->wowk, mc13783_ts_wowk);
	pwiv->mc13xxx = dev_get_dwvdata(pdev->dev.pawent);
	pwiv->idev = idev;
	pwiv->touch = dev_get_pwatdata(&pdev->dev);
	if (!pwiv->touch) {
		dev_eww(&pdev->dev, "missing pwatfowm data\n");
		wet = -ENODEV;
		goto eww_fwee_mem;
	}

	idev->name = MC13783_TS_NAME;
	idev->dev.pawent = &pdev->dev;

	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	idev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(idev, ABS_X, 0, 0xfff, 0, 0);
	input_set_abs_pawams(idev, ABS_Y, 0, 0xfff, 0, 0);
	input_set_abs_pawams(idev, ABS_PWESSUWE, 0, 0xfff, 0, 0);

	idev->open = mc13783_ts_open;
	idev->cwose = mc13783_ts_cwose;

	input_set_dwvdata(idev, pwiv);

	wet = input_wegistew_device(pwiv->idev);
	if (wet) {
		dev_eww(&pdev->dev,
			"wegistew input device faiwed with %d\n", wet);
		goto eww_fwee_mem;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);
	wetuwn 0;

eww_fwee_mem:
	input_fwee_device(idev);
	kfwee(pwiv);
	wetuwn wet;
}

static void mc13783_ts_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mc13783_ts_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	input_unwegistew_device(pwiv->idev);
	kfwee(pwiv);
}

static stwuct pwatfowm_dwivew mc13783_ts_dwivew = {
	.wemove_new	= mc13783_ts_wemove,
	.dwivew		= {
		.name	= MC13783_TS_NAME,
	},
};

moduwe_pwatfowm_dwivew_pwobe(mc13783_ts_dwivew, mc13783_ts_pwobe);

MODUWE_DESCWIPTION("MC13783 input touchscween dwivew");
MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" MC13783_TS_NAME);
