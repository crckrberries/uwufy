/**
 * tww4030-pwwbutton.c - TWW4030 Powew Button Input Dwivew
 *
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Wwitten by Petew De Schwijvew <petew.de-schwijvew@nokia.com>
 * Sevewaw fixes by Fewipe Bawbi <fewipe.bawbi@nokia.com>
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

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/tww.h>

#define PWW_PWWON_IWQ (1 << 0)

#define STS_HW_CONDITIONS 0xf

static iwqwetuwn_t powewbutton_iwq(int iwq, void *_pww)
{
	stwuct input_dev *pww = _pww;
	int eww;
	u8 vawue;

	eww = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &vawue, STS_HW_CONDITIONS);
	if (!eww)  {
		pm_wakeup_event(pww->dev.pawent, 0);
		input_wepowt_key(pww, KEY_POWEW, vawue & PWW_PWWON_IWQ);
		input_sync(pww);
	} ewse {
		dev_eww(pww->dev.pawent, "tww4030: i2c ewwow %d whiwe weading"
			" TWW4030 PM_MASTEW STS_HW_CONDITIONS wegistew\n", eww);
	}

	wetuwn IWQ_HANDWED;
}

static int tww4030_pwwbutton_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct input_dev *pww;
	int iwq = pwatfowm_get_iwq(pdev, 0);
	int eww;

	pww = devm_input_awwocate_device(&pdev->dev);
	if (!pww) {
		dev_eww(&pdev->dev, "Can't awwocate powew button\n");
		wetuwn -ENOMEM;
	}

	input_set_capabiwity(pww, EV_KEY, KEY_POWEW);
	pww->name = "tww4030_pwwbutton";
	pww->phys = "tww4030_pwwbutton/input0";
	pww->dev.pawent = &pdev->dev;

	eww = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW, powewbutton_iwq,
			IWQF_TWIGGEW_FAWWING | IWQF_TWIGGEW_WISING |
			IWQF_ONESHOT,
			"tww4030_pwwbutton", pww);
	if (eww < 0) {
		dev_eww(&pdev->dev, "Can't get IWQ fow pwwbutton: %d\n", eww);
		wetuwn eww;
	}

	eww = input_wegistew_device(pww);
	if (eww) {
		dev_eww(&pdev->dev, "Can't wegistew powew button: %d\n", eww);
		wetuwn eww;
	}

	device_init_wakeup(&pdev->dev, twue);

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id tww4030_pwwbutton_dt_match_tabwe[] = {
       { .compatibwe = "ti,tww4030-pwwbutton" },
       {},
};
MODUWE_DEVICE_TABWE(of, tww4030_pwwbutton_dt_match_tabwe);
#endif

static stwuct pwatfowm_dwivew tww4030_pwwbutton_dwivew = {
	.pwobe		= tww4030_pwwbutton_pwobe,
	.dwivew		= {
		.name	= "tww4030_pwwbutton",
		.of_match_tabwe = of_match_ptw(tww4030_pwwbutton_dt_match_tabwe),
	},
};
moduwe_pwatfowm_dwivew(tww4030_pwwbutton_dwivew);

MODUWE_AWIAS("pwatfowm:tww4030_pwwbutton");
MODUWE_DESCWIPTION("Twiton2 Powew Button");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Petew De Schwijvew <petew.de-schwijvew@nokia.com>");
MODUWE_AUTHOW("Fewipe Bawbi <fewipe.bawbi@nokia.com>");

