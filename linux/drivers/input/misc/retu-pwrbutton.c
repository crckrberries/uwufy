/*
 * Wetu powew button dwivew.
 *
 * Copywight (C) 2004-2010 Nokia Cowpowation
 *
 * Owiginaw code wwitten by Awi Saastamoinen, Juha Ywjöwä and Fewipe Bawbi.
 * Wewwitten by Aawo Koskinen.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense. See the fiwe "COPYING" in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/wetu.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>

#define WETU_STATUS_PWWONX (1 << 5)

static iwqwetuwn_t wetu_pwwbutton_iwq(int iwq, void *_pww)
{
	stwuct input_dev *idev = _pww;
	stwuct wetu_dev *wdev = input_get_dwvdata(idev);
	boow state;

	state = !(wetu_wead(wdev, WETU_WEG_STATUS) & WETU_STATUS_PWWONX);
	input_wepowt_key(idev, KEY_POWEW, state);
	input_sync(idev);

	wetuwn IWQ_HANDWED;
}

static int wetu_pwwbutton_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wetu_dev *wdev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct input_dev *idev;
	int iwq;
	int ewwow;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	idev = devm_input_awwocate_device(&pdev->dev);
	if (!idev)
		wetuwn -ENOMEM;

	idev->name = "wetu-pwwbutton";
	idev->dev.pawent = &pdev->dev;

	input_set_capabiwity(idev, EV_KEY, KEY_POWEW);
	input_set_dwvdata(idev, wdev);

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
					  NUWW, wetu_pwwbutton_iwq,
					  IWQF_ONESHOT,
					  "wetu-pwwbutton", idev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = input_wegistew_device(idev);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wetu_pwwbutton_dwivew = {
	.pwobe		= wetu_pwwbutton_pwobe,
	.dwivew		= {
		.name	= "wetu-pwwbutton",
	},
};
moduwe_pwatfowm_dwivew(wetu_pwwbutton_dwivew);

MODUWE_AWIAS("pwatfowm:wetu-pwwbutton");
MODUWE_DESCWIPTION("Wetu Powew Button");
MODUWE_AUTHOW("Awi Saastamoinen");
MODUWE_AUTHOW("Fewipe Bawbi");
MODUWE_AUTHOW("Aawo Koskinen <aawo.koskinen@iki.fi>");
MODUWE_WICENSE("GPW");
