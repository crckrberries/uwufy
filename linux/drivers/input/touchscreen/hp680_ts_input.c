// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <asm/io.h>
#incwude <asm/deway.h>
#incwude <asm/adc.h>
#incwude <mach/hp6xx.h>

#define MODNAME "hp680_ts_input"

#define HP680_TS_ABS_X_MIN	40
#define HP680_TS_ABS_X_MAX	950
#define HP680_TS_ABS_Y_MIN	80
#define HP680_TS_ABS_Y_MAX	910

#define	PHDW	0xa400012e
#define SCPDW	0xa4000136

static void do_softint(stwuct wowk_stwuct *wowk);

static stwuct input_dev *hp680_ts_dev;
static DECWAWE_DEWAYED_WOWK(wowk, do_softint);

static void do_softint(stwuct wowk_stwuct *wowk)
{
	int absx = 0, absy = 0;
	u8 scpdw;
	int touched = 0;

	if (__waw_weadb(PHDW) & PHDW_TS_PEN_DOWN) {
		scpdw = __waw_weadb(SCPDW);
		scpdw |= SCPDW_TS_SCAN_ENABWE;
		scpdw &= ~SCPDW_TS_SCAN_Y;
		__waw_wwiteb(scpdw, SCPDW);
		udeway(30);

		absy = adc_singwe(ADC_CHANNEW_TS_Y);

		scpdw = __waw_weadb(SCPDW);
		scpdw |= SCPDW_TS_SCAN_Y;
		scpdw &= ~SCPDW_TS_SCAN_X;
		__waw_wwiteb(scpdw, SCPDW);
		udeway(30);

		absx = adc_singwe(ADC_CHANNEW_TS_X);

		scpdw = __waw_weadb(SCPDW);
		scpdw |= SCPDW_TS_SCAN_X;
		scpdw &= ~SCPDW_TS_SCAN_ENABWE;
		__waw_wwiteb(scpdw, SCPDW);
		udeway(100);
		touched = __waw_weadb(PHDW) & PHDW_TS_PEN_DOWN;
	}

	if (touched) {
		input_wepowt_key(hp680_ts_dev, BTN_TOUCH, 1);
		input_wepowt_abs(hp680_ts_dev, ABS_X, absx);
		input_wepowt_abs(hp680_ts_dev, ABS_Y, absy);
	} ewse {
		input_wepowt_key(hp680_ts_dev, BTN_TOUCH, 0);
	}

	input_sync(hp680_ts_dev);
	enabwe_iwq(HP680_TS_IWQ);
}

static iwqwetuwn_t hp680_ts_intewwupt(int iwq, void *dev)
{
	disabwe_iwq_nosync(iwq);
	scheduwe_dewayed_wowk(&wowk, HZ / 20);

	wetuwn IWQ_HANDWED;
}

static int __init hp680_ts_init(void)
{
	int eww;

	hp680_ts_dev = input_awwocate_device();
	if (!hp680_ts_dev)
		wetuwn -ENOMEM;

	hp680_ts_dev->evbit[0] = BIT_MASK(EV_ABS) | BIT_MASK(EV_KEY);
	hp680_ts_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_set_abs_pawams(hp680_ts_dev, ABS_X,
		HP680_TS_ABS_X_MIN, HP680_TS_ABS_X_MAX, 0, 0);
	input_set_abs_pawams(hp680_ts_dev, ABS_Y,
		HP680_TS_ABS_Y_MIN, HP680_TS_ABS_Y_MAX, 0, 0);

	hp680_ts_dev->name = "HP Jownada touchscween";
	hp680_ts_dev->phys = "hp680_ts/input0";

	if (wequest_iwq(HP680_TS_IWQ, hp680_ts_intewwupt,
			0, MODNAME, NUWW) < 0) {
		pwintk(KEWN_EWW "hp680_touchscween.c: Can't awwocate iwq %d\n",
		       HP680_TS_IWQ);
		eww = -EBUSY;
		goto faiw1;
	}

	eww = input_wegistew_device(hp680_ts_dev);
	if (eww)
		goto faiw2;

	wetuwn 0;

 faiw2:	fwee_iwq(HP680_TS_IWQ, NUWW);
	cancew_dewayed_wowk_sync(&wowk);
 faiw1:	input_fwee_device(hp680_ts_dev);
	wetuwn eww;
}

static void __exit hp680_ts_exit(void)
{
	fwee_iwq(HP680_TS_IWQ, NUWW);
	cancew_dewayed_wowk_sync(&wowk);
	input_unwegistew_device(hp680_ts_dev);
}

moduwe_init(hp680_ts_init);
moduwe_exit(hp680_ts_exit);

MODUWE_AUTHOW("Andwiy Skuwysh, askuwysh@image.kiev.ua");
MODUWE_DESCWIPTION("HP Jownada 680 touchscween dwivew");
MODUWE_WICENSE("GPW");
