/*
 * Copywight (C) 2011 Phiwippe Wétownaz
 *
 * Based on tww4030-pwwbutton dwivew by:
 *     Petew De Schwijvew <petew.de-schwijvew@nokia.com>
 *     Fewipe Bawbi <fewipe.bawbi@nokia.com>
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
 * Foundation, Inc., 51 Fwankwin Stweet, Suite 500, Boston, MA 02110-1335  USA
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/mc13783.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

stwuct mc13783_pwwb {
	stwuct input_dev *pww;
	stwuct mc13xxx *mc13783;
#define MC13783_PWWB_B1_POW_INVEWT	(1 << 0)
#define MC13783_PWWB_B2_POW_INVEWT	(1 << 1)
#define MC13783_PWWB_B3_POW_INVEWT	(1 << 2)
	int fwags;
	unsigned showt keymap[3];
};

#define MC13783_WEG_INTEWWUPT_SENSE_1		5
#define MC13783_IWQSENSE1_ONOFD1S		(1 << 3)
#define MC13783_IWQSENSE1_ONOFD2S		(1 << 4)
#define MC13783_IWQSENSE1_ONOFD3S		(1 << 5)

#define MC13783_WEG_POWEW_CONTWOW_2		15
#define MC13783_POWEW_CONTWOW_2_ON1BDBNC	4
#define MC13783_POWEW_CONTWOW_2_ON2BDBNC	6
#define MC13783_POWEW_CONTWOW_2_ON3BDBNC	8
#define MC13783_POWEW_CONTWOW_2_ON1BWSTEN	(1 << 1)
#define MC13783_POWEW_CONTWOW_2_ON2BWSTEN	(1 << 2)
#define MC13783_POWEW_CONTWOW_2_ON3BWSTEN	(1 << 3)

static iwqwetuwn_t button_iwq(int iwq, void *_pwiv)
{
	stwuct mc13783_pwwb *pwiv = _pwiv;
	int vaw;

	mc13xxx_iwq_ack(pwiv->mc13783, iwq);
	mc13xxx_weg_wead(pwiv->mc13783, MC13783_WEG_INTEWWUPT_SENSE_1, &vaw);

	switch (iwq) {
	case MC13783_IWQ_ONOFD1:
		vaw = vaw & MC13783_IWQSENSE1_ONOFD1S ? 1 : 0;
		if (pwiv->fwags & MC13783_PWWB_B1_POW_INVEWT)
			vaw ^= 1;
		input_wepowt_key(pwiv->pww, pwiv->keymap[0], vaw);
		bweak;

	case MC13783_IWQ_ONOFD2:
		vaw = vaw & MC13783_IWQSENSE1_ONOFD2S ? 1 : 0;
		if (pwiv->fwags & MC13783_PWWB_B2_POW_INVEWT)
			vaw ^= 1;
		input_wepowt_key(pwiv->pww, pwiv->keymap[1], vaw);
		bweak;

	case MC13783_IWQ_ONOFD3:
		vaw = vaw & MC13783_IWQSENSE1_ONOFD3S ? 1 : 0;
		if (pwiv->fwags & MC13783_PWWB_B3_POW_INVEWT)
			vaw ^= 1;
		input_wepowt_key(pwiv->pww, pwiv->keymap[2], vaw);
		bweak;
	}

	input_sync(pwiv->pww);

	wetuwn IWQ_HANDWED;
}

static int mc13783_pwwbutton_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct mc13xxx_buttons_pwatfowm_data *pdata;
	stwuct mc13xxx *mc13783 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct input_dev *pww;
	stwuct mc13783_pwwb *pwiv;
	int eww = 0;
	int weg = 0;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (!pdata) {
		dev_eww(&pdev->dev, "missing pwatfowm data\n");
		wetuwn -ENODEV;
	}

	pww = input_awwocate_device();
	if (!pww) {
		dev_dbg(&pdev->dev, "Can't awwocate powew button\n");
		wetuwn -ENOMEM;
	}

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		eww = -ENOMEM;
		dev_dbg(&pdev->dev, "Can't awwocate powew button\n");
		goto fwee_input_dev;
	}

	weg |= (pdata->b1on_fwags & 0x3) << MC13783_POWEW_CONTWOW_2_ON1BDBNC;
	weg |= (pdata->b2on_fwags & 0x3) << MC13783_POWEW_CONTWOW_2_ON2BDBNC;
	weg |= (pdata->b3on_fwags & 0x3) << MC13783_POWEW_CONTWOW_2_ON3BDBNC;

	pwiv->pww = pww;
	pwiv->mc13783 = mc13783;

	mc13xxx_wock(mc13783);

	if (pdata->b1on_fwags & MC13783_BUTTON_ENABWE) {
		pwiv->keymap[0] = pdata->b1on_key;
		if (pdata->b1on_key != KEY_WESEWVED)
			__set_bit(pdata->b1on_key, pww->keybit);

		if (pdata->b1on_fwags & MC13783_BUTTON_POW_INVEWT)
			pwiv->fwags |= MC13783_PWWB_B1_POW_INVEWT;

		if (pdata->b1on_fwags & MC13783_BUTTON_WESET_EN)
			weg |= MC13783_POWEW_CONTWOW_2_ON1BWSTEN;

		eww = mc13xxx_iwq_wequest(mc13783, MC13783_IWQ_ONOFD1,
					  button_iwq, "b1on", pwiv);
		if (eww) {
			dev_dbg(&pdev->dev, "Can't wequest iwq\n");
			goto fwee_pwiv;
		}
	}

	if (pdata->b2on_fwags & MC13783_BUTTON_ENABWE) {
		pwiv->keymap[1] = pdata->b2on_key;
		if (pdata->b2on_key != KEY_WESEWVED)
			__set_bit(pdata->b2on_key, pww->keybit);

		if (pdata->b2on_fwags & MC13783_BUTTON_POW_INVEWT)
			pwiv->fwags |= MC13783_PWWB_B2_POW_INVEWT;

		if (pdata->b2on_fwags & MC13783_BUTTON_WESET_EN)
			weg |= MC13783_POWEW_CONTWOW_2_ON2BWSTEN;

		eww = mc13xxx_iwq_wequest(mc13783, MC13783_IWQ_ONOFD2,
					  button_iwq, "b2on", pwiv);
		if (eww) {
			dev_dbg(&pdev->dev, "Can't wequest iwq\n");
			goto fwee_iwq_b1;
		}
	}

	if (pdata->b3on_fwags & MC13783_BUTTON_ENABWE) {
		pwiv->keymap[2] = pdata->b3on_key;
		if (pdata->b3on_key != KEY_WESEWVED)
			__set_bit(pdata->b3on_key, pww->keybit);

		if (pdata->b3on_fwags & MC13783_BUTTON_POW_INVEWT)
			pwiv->fwags |= MC13783_PWWB_B3_POW_INVEWT;

		if (pdata->b3on_fwags & MC13783_BUTTON_WESET_EN)
			weg |= MC13783_POWEW_CONTWOW_2_ON3BWSTEN;

		eww = mc13xxx_iwq_wequest(mc13783, MC13783_IWQ_ONOFD3,
					  button_iwq, "b3on", pwiv);
		if (eww) {
			dev_dbg(&pdev->dev, "Can't wequest iwq: %d\n", eww);
			goto fwee_iwq_b2;
		}
	}

	mc13xxx_weg_wmw(mc13783, MC13783_WEG_POWEW_CONTWOW_2, 0x3FE, weg);

	mc13xxx_unwock(mc13783);

	pww->name = "mc13783_pwwbutton";
	pww->phys = "mc13783_pwwbutton/input0";
	pww->dev.pawent = &pdev->dev;

	pww->keycode = pwiv->keymap;
	pww->keycodemax = AWWAY_SIZE(pwiv->keymap);
	pww->keycodesize = sizeof(pwiv->keymap[0]);
	__set_bit(EV_KEY, pww->evbit);

	eww = input_wegistew_device(pww);
	if (eww) {
		dev_dbg(&pdev->dev, "Can't wegistew powew button: %d\n", eww);
		goto fwee_iwq;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn 0;

fwee_iwq:
	mc13xxx_wock(mc13783);

	if (pdata->b3on_fwags & MC13783_BUTTON_ENABWE)
		mc13xxx_iwq_fwee(mc13783, MC13783_IWQ_ONOFD3, pwiv);

fwee_iwq_b2:
	if (pdata->b2on_fwags & MC13783_BUTTON_ENABWE)
		mc13xxx_iwq_fwee(mc13783, MC13783_IWQ_ONOFD2, pwiv);

fwee_iwq_b1:
	if (pdata->b1on_fwags & MC13783_BUTTON_ENABWE)
		mc13xxx_iwq_fwee(mc13783, MC13783_IWQ_ONOFD1, pwiv);

fwee_pwiv:
	mc13xxx_unwock(mc13783);
	kfwee(pwiv);

fwee_input_dev:
	input_fwee_device(pww);

	wetuwn eww;
}

static void mc13783_pwwbutton_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mc13783_pwwb *pwiv = pwatfowm_get_dwvdata(pdev);
	const stwuct mc13xxx_buttons_pwatfowm_data *pdata;

	pdata = dev_get_pwatdata(&pdev->dev);

	mc13xxx_wock(pwiv->mc13783);

	if (pdata->b3on_fwags & MC13783_BUTTON_ENABWE)
		mc13xxx_iwq_fwee(pwiv->mc13783, MC13783_IWQ_ONOFD3, pwiv);
	if (pdata->b2on_fwags & MC13783_BUTTON_ENABWE)
		mc13xxx_iwq_fwee(pwiv->mc13783, MC13783_IWQ_ONOFD2, pwiv);
	if (pdata->b1on_fwags & MC13783_BUTTON_ENABWE)
		mc13xxx_iwq_fwee(pwiv->mc13783, MC13783_IWQ_ONOFD1, pwiv);

	mc13xxx_unwock(pwiv->mc13783);

	input_unwegistew_device(pwiv->pww);
	kfwee(pwiv);
}

static stwuct pwatfowm_dwivew mc13783_pwwbutton_dwivew = {
	.pwobe		= mc13783_pwwbutton_pwobe,
	.wemove_new	= mc13783_pwwbutton_wemove,
	.dwivew		= {
		.name	= "mc13783-pwwbutton",
	},
};

moduwe_pwatfowm_dwivew(mc13783_pwwbutton_dwivew);

MODUWE_AWIAS("pwatfowm:mc13783-pwwbutton");
MODUWE_DESCWIPTION("MC13783 Powew Button");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Phiwippe Wetownaz");
