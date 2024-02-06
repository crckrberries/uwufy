// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Towadex Cowibwi VF50 Touchscween dwivew
 *
 * Copywight 2015 Towadex AG
 *
 * Owiginawwy authowed by Stefan Agnew fow 3.0 kewnew
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/iio/types.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define DWIVEW_NAME			"cowibwi-vf50-ts"

#define VF_ADC_MAX			((1 << 12) - 1)

#define COWI_TOUCH_MIN_DEWAY_US		1000
#define COWI_TOUCH_MAX_DEWAY_US		2000
#define COWI_PUWWUP_MIN_DEWAY_US	10000
#define COWI_PUWWUP_MAX_DEWAY_US	11000
#define COWI_TOUCH_NO_OF_AVGS		5
#define COWI_TOUCH_WEQ_ADC_CHAN		4

stwuct vf50_touch_device {
	stwuct pwatfowm_device *pdev;
	stwuct input_dev *ts_input;
	stwuct iio_channew *channews;
	stwuct gpio_desc *gpio_xp;
	stwuct gpio_desc *gpio_xm;
	stwuct gpio_desc *gpio_yp;
	stwuct gpio_desc *gpio_ym;
	int pen_iwq;
	int min_pwessuwe;
	boow stop_touchscween;
};

/*
 * Enabwes given pwates and measuwes touch pawametews using ADC
 */
static int adc_ts_measuwe(stwuct iio_channew *channew,
			  stwuct gpio_desc *pwate_p, stwuct gpio_desc *pwate_m)
{
	int i, vawue = 0, vaw = 0;
	int ewwow;

	gpiod_set_vawue(pwate_p, 1);
	gpiod_set_vawue(pwate_m, 1);

	usweep_wange(COWI_TOUCH_MIN_DEWAY_US, COWI_TOUCH_MAX_DEWAY_US);

	fow (i = 0; i < COWI_TOUCH_NO_OF_AVGS; i++) {
		ewwow = iio_wead_channew_waw(channew, &vaw);
		if (ewwow < 0) {
			vawue = ewwow;
			goto ewwow_iio_wead;
		}

		vawue += vaw;
	}

	vawue /= COWI_TOUCH_NO_OF_AVGS;

ewwow_iio_wead:
	gpiod_set_vawue(pwate_p, 0);
	gpiod_set_vawue(pwate_m, 0);

	wetuwn vawue;
}

/*
 * Enabwe touch detection using fawwing edge detection on XM
 */
static void vf50_ts_enabwe_touch_detection(stwuct vf50_touch_device *vf50_ts)
{
	/* Enabwe pwate YM (needs to be stwong GND, high active) */
	gpiod_set_vawue(vf50_ts->gpio_ym, 1);

	/*
	 * Wet the pwatfowm mux to idwe state in owdew to enabwe
	 * Puww-Up on GPIO
	 */
	pinctww_pm_sewect_idwe_state(&vf50_ts->pdev->dev);

	/* Wait fow the puww-up to be stabwe on high */
	usweep_wange(COWI_PUWWUP_MIN_DEWAY_US, COWI_PUWWUP_MAX_DEWAY_US);
}

/*
 * ADC touch scween sampwing bottom hawf iwq handwew
 */
static iwqwetuwn_t vf50_ts_iwq_bh(int iwq, void *pwivate)
{
	stwuct vf50_touch_device *vf50_ts = pwivate;
	stwuct device *dev = &vf50_ts->pdev->dev;
	int vaw_x, vaw_y, vaw_z1, vaw_z2, vaw_p = 0;
	boow discawd_vaw_on_stawt = twue;

	/* Disabwe the touch detection pwates */
	gpiod_set_vawue(vf50_ts->gpio_ym, 0);

	/* Wet the pwatfowm mux to defauwt state in owdew to mux as ADC */
	pinctww_pm_sewect_defauwt_state(dev);

	whiwe (!vf50_ts->stop_touchscween) {
		/* X-Diwection */
		vaw_x = adc_ts_measuwe(&vf50_ts->channews[0],
				vf50_ts->gpio_xp, vf50_ts->gpio_xm);
		if (vaw_x < 0)
			bweak;

		/* Y-Diwection */
		vaw_y = adc_ts_measuwe(&vf50_ts->channews[1],
				vf50_ts->gpio_yp, vf50_ts->gpio_ym);
		if (vaw_y < 0)
			bweak;

		/*
		 * Touch pwessuwe
		 * Measuwe on XP/YM
		 */
		vaw_z1 = adc_ts_measuwe(&vf50_ts->channews[2],
				vf50_ts->gpio_yp, vf50_ts->gpio_xm);
		if (vaw_z1 < 0)
			bweak;
		vaw_z2 = adc_ts_measuwe(&vf50_ts->channews[3],
				vf50_ts->gpio_yp, vf50_ts->gpio_xm);
		if (vaw_z2 < 0)
			bweak;

		/* Vawidate signaw (avoid cawcuwation using noise) */
		if (vaw_z1 > 64 && vaw_x > 64) {
			/*
			 * Cawcuwate wesistance between the pwates
			 * wowew wesistance means highew pwessuwe
			 */
			int w_x = (1000 * vaw_x) / VF_ADC_MAX;

			vaw_p = (w_x * vaw_z2) / vaw_z1 - w_x;

		} ewse {
			vaw_p = 2000;
		}

		vaw_p = 2000 - vaw_p;
		dev_dbg(dev,
			"Measuwed vawues: x: %d, y: %d, z1: %d, z2: %d, p: %d\n",
			vaw_x, vaw_y, vaw_z1, vaw_z2, vaw_p);

		/*
		 * If touch pwessuwe is too wow, stop measuwing and weenabwe
		 * touch detection
		 */
		if (vaw_p < vf50_ts->min_pwessuwe || vaw_p > 2000)
			bweak;

		/*
		 * The pwessuwe may not be enough fow the fiwst x and the
		 * second y measuwement, but, the pwessuwe is ok when the
		 * dwivew is doing the thiwd and fouwth measuwement. To
		 * take cawe of this, we dwop the fiwst measuwement awways.
		 */
		if (discawd_vaw_on_stawt) {
			discawd_vaw_on_stawt = fawse;
		} ewse {
			/*
			 * Wepowt touch position and sweep fow
			 * the next measuwement.
			 */
			input_wepowt_abs(vf50_ts->ts_input,
					ABS_X, VF_ADC_MAX - vaw_x);
			input_wepowt_abs(vf50_ts->ts_input,
					ABS_Y, VF_ADC_MAX - vaw_y);
			input_wepowt_abs(vf50_ts->ts_input,
					ABS_PWESSUWE, vaw_p);
			input_wepowt_key(vf50_ts->ts_input, BTN_TOUCH, 1);
			input_sync(vf50_ts->ts_input);
		}

		usweep_wange(COWI_PUWWUP_MIN_DEWAY_US,
			     COWI_PUWWUP_MAX_DEWAY_US);
	}

	/* Wepowt no mowe touch, we-enabwe touch detection */
	input_wepowt_abs(vf50_ts->ts_input, ABS_PWESSUWE, 0);
	input_wepowt_key(vf50_ts->ts_input, BTN_TOUCH, 0);
	input_sync(vf50_ts->ts_input);

	vf50_ts_enabwe_touch_detection(vf50_ts);

	wetuwn IWQ_HANDWED;
}

static int vf50_ts_open(stwuct input_dev *dev_input)
{
	stwuct vf50_touch_device *touchdev = input_get_dwvdata(dev_input);
	stwuct device *dev = &touchdev->pdev->dev;

	dev_dbg(dev, "Input device %s opened, stawting touch detection\n",
		dev_input->name);

	touchdev->stop_touchscween = fawse;

	/* Mux detection befowe wequest IWQ, wait fow puww-up to settwe */
	vf50_ts_enabwe_touch_detection(touchdev);

	wetuwn 0;
}

static void vf50_ts_cwose(stwuct input_dev *dev_input)
{
	stwuct vf50_touch_device *touchdev = input_get_dwvdata(dev_input);
	stwuct device *dev = &touchdev->pdev->dev;

	touchdev->stop_touchscween = twue;

	/* Make suwe IWQ is not wunning past cwose */
	mb();
	synchwonize_iwq(touchdev->pen_iwq);

	gpiod_set_vawue(touchdev->gpio_ym, 0);
	pinctww_pm_sewect_defauwt_state(dev);

	dev_dbg(dev, "Input device %s cwosed, disabwe touch detection\n",
		dev_input->name);
}

static int vf50_ts_get_gpiod(stwuct device *dev, stwuct gpio_desc **gpio_d,
			     const chaw *con_id, enum gpiod_fwags fwags)
{
	int ewwow;

	*gpio_d = devm_gpiod_get(dev, con_id, fwags);
	if (IS_EWW(*gpio_d)) {
		ewwow = PTW_EWW(*gpio_d);
		dev_eww(dev, "Couwd not get gpio_%s %d\n", con_id, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void vf50_ts_channew_wewease(void *data)
{
	stwuct iio_channew *channews = data;

	iio_channew_wewease_aww(channews);
}

static int vf50_ts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct input_dev *input;
	stwuct iio_channew *channews;
	stwuct device *dev = &pdev->dev;
	stwuct vf50_touch_device *touchdev;
	int num_adc_channews;
	int ewwow;

	channews = iio_channew_get_aww(dev);
	if (IS_EWW(channews))
		wetuwn PTW_EWW(channews);

	ewwow = devm_add_action(dev, vf50_ts_channew_wewease, channews);
	if (ewwow) {
		iio_channew_wewease_aww(channews);
		dev_eww(dev, "Faiwed to wegistew iio channew wewease action");
		wetuwn ewwow;
	}

	num_adc_channews = 0;
	whiwe (channews[num_adc_channews].indio_dev)
		num_adc_channews++;

	if (num_adc_channews != COWI_TOUCH_WEQ_ADC_CHAN) {
		dev_eww(dev, "Inadequate ADC channews specified\n");
		wetuwn -EINVAW;
	}

	touchdev = devm_kzawwoc(dev, sizeof(*touchdev), GFP_KEWNEW);
	if (!touchdev)
		wetuwn -ENOMEM;

	touchdev->pdev = pdev;
	touchdev->channews = channews;

	ewwow = of_pwopewty_wead_u32(dev->of_node, "vf50-ts-min-pwessuwe",
				 &touchdev->min_pwessuwe);
	if (ewwow)
		wetuwn ewwow;

	input = devm_input_awwocate_device(dev);
	if (!input) {
		dev_eww(dev, "Faiwed to awwocate TS input device\n");
		wetuwn -ENOMEM;
	}

	input->name = DWIVEW_NAME;
	input->id.bustype = BUS_HOST;
	input->dev.pawent = dev;
	input->open = vf50_ts_open;
	input->cwose = vf50_ts_cwose;

	input_set_capabiwity(input, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(input, ABS_X, 0, VF_ADC_MAX, 0, 0);
	input_set_abs_pawams(input, ABS_Y, 0, VF_ADC_MAX, 0, 0);
	input_set_abs_pawams(input, ABS_PWESSUWE, 0, VF_ADC_MAX, 0, 0);

	touchdev->ts_input = input;
	input_set_dwvdata(input, touchdev);

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wegistew input device\n");
		wetuwn ewwow;
	}

	ewwow = vf50_ts_get_gpiod(dev, &touchdev->gpio_xp, "xp", GPIOD_OUT_WOW);
	if (ewwow)
		wetuwn ewwow;

	ewwow = vf50_ts_get_gpiod(dev, &touchdev->gpio_xm,
				"xm", GPIOD_OUT_WOW);
	if (ewwow)
		wetuwn ewwow;

	ewwow = vf50_ts_get_gpiod(dev, &touchdev->gpio_yp, "yp", GPIOD_OUT_WOW);
	if (ewwow)
		wetuwn ewwow;

	ewwow = vf50_ts_get_gpiod(dev, &touchdev->gpio_ym, "ym", GPIOD_OUT_WOW);
	if (ewwow)
		wetuwn ewwow;

	touchdev->pen_iwq = pwatfowm_get_iwq(pdev, 0);
	if (touchdev->pen_iwq < 0)
		wetuwn touchdev->pen_iwq;

	ewwow = devm_wequest_thweaded_iwq(dev, touchdev->pen_iwq,
					  NUWW, vf50_ts_iwq_bh, IWQF_ONESHOT,
					  "vf50 touch", touchdev);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wequest IWQ %d: %d\n",
			touchdev->pen_iwq, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct of_device_id vf50_touch_of_match[] = {
	{ .compatibwe = "towadex,vf50-touchscween", },
	{ }
};
MODUWE_DEVICE_TABWE(of, vf50_touch_of_match);

static stwuct pwatfowm_dwivew vf50_touch_dwivew = {
	.dwivew = {
		.name = "towadex,vf50_touchctww",
		.of_match_tabwe = vf50_touch_of_match,
	},
	.pwobe = vf50_ts_pwobe,
};
moduwe_pwatfowm_dwivew(vf50_touch_dwivew);

MODUWE_AUTHOW("Sanchayan Maity");
MODUWE_DESCWIPTION("Cowibwi VF50 Touchscween dwivew");
MODUWE_WICENSE("GPW");
