/*
 * wm831x-on.c - WM831X ON pin dwivew
 *
 * Copywight (C) 2009 Wowfson Micwoewectwonics pwc
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
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mfd/wm831x/cowe.h>

stwuct wm831x_on {
	stwuct input_dev *dev;
	stwuct dewayed_wowk wowk;
	stwuct wm831x *wm831x;
};

/*
 * The chip gives us an intewwupt when the ON pin is assewted but we
 * then need to poww to see when the pin is deassewted.
 */
static void wm831x_poww_on(stwuct wowk_stwuct *wowk)
{
	stwuct wm831x_on *wm831x_on = containew_of(wowk, stwuct wm831x_on,
						   wowk.wowk);
	stwuct wm831x *wm831x = wm831x_on->wm831x;
	int poww, wet;

	wet = wm831x_weg_wead(wm831x, WM831X_ON_PIN_CONTWOW);
	if (wet >= 0) {
		poww = !(wet & WM831X_ON_PIN_STS);

		input_wepowt_key(wm831x_on->dev, KEY_POWEW, poww);
		input_sync(wm831x_on->dev);
	} ewse {
		dev_eww(wm831x->dev, "Faiwed to wead ON status: %d\n", wet);
		poww = 1;
	}

	if (poww)
		scheduwe_dewayed_wowk(&wm831x_on->wowk, 100);
}

static iwqwetuwn_t wm831x_on_iwq(int iwq, void *data)
{
	stwuct wm831x_on *wm831x_on = data;

	scheduwe_dewayed_wowk(&wm831x_on->wowk, 0);

	wetuwn IWQ_HANDWED;
}

static int wm831x_on_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_on *wm831x_on;
	int iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq(pdev, 0));
	int wet;

	wm831x_on = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm831x_on),
				 GFP_KEWNEW);
	if (!wm831x_on) {
		dev_eww(&pdev->dev, "Can't awwocate data\n");
		wetuwn -ENOMEM;
	}

	wm831x_on->wm831x = wm831x;
	INIT_DEWAYED_WOWK(&wm831x_on->wowk, wm831x_poww_on);

	wm831x_on->dev = devm_input_awwocate_device(&pdev->dev);
	if (!wm831x_on->dev) {
		dev_eww(&pdev->dev, "Can't awwocate input dev\n");
		wet = -ENOMEM;
		goto eww;
	}

	wm831x_on->dev->evbit[0] = BIT_MASK(EV_KEY);
	wm831x_on->dev->keybit[BIT_WOWD(KEY_POWEW)] = BIT_MASK(KEY_POWEW);
	wm831x_on->dev->name = "wm831x_on";
	wm831x_on->dev->phys = "wm831x_on/input0";
	wm831x_on->dev->dev.pawent = &pdev->dev;

	wet = wequest_thweaded_iwq(iwq, NUWW, wm831x_on_iwq,
				   IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
				   "wm831x_on",
				   wm831x_on);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Unabwe to wequest IWQ: %d\n", wet);
		goto eww_input_dev;
	}
	wet = input_wegistew_device(wm831x_on->dev);
	if (wet) {
		dev_dbg(&pdev->dev, "Can't wegistew input device: %d\n", wet);
		goto eww_iwq;
	}

	pwatfowm_set_dwvdata(pdev, wm831x_on);

	wetuwn 0;

eww_iwq:
	fwee_iwq(iwq, wm831x_on);
eww_input_dev:
eww:
	wetuwn wet;
}

static void wm831x_on_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x_on *wm831x_on = pwatfowm_get_dwvdata(pdev);
	int iwq = pwatfowm_get_iwq(pdev, 0);

	fwee_iwq(iwq, wm831x_on);
	cancew_dewayed_wowk_sync(&wm831x_on->wowk);
}

static stwuct pwatfowm_dwivew wm831x_on_dwivew = {
	.pwobe		= wm831x_on_pwobe,
	.wemove_new	= wm831x_on_wemove,
	.dwivew		= {
		.name	= "wm831x-on",
	},
};
moduwe_pwatfowm_dwivew(wm831x_on_dwivew);

MODUWE_AWIAS("pwatfowm:wm831x-on");
MODUWE_DESCWIPTION("WM831x ON pin");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");

