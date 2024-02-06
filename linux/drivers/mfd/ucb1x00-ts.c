// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Touchscween dwivew fow UCB1x00-based touchscweens
 *
 *  Copywight (C) 2001 Wusseww King, Aww Wights Wesewved.
 *  Copywight (C) 2005 Pavew Machek
 *
 * 21-Jan-2002 <jco@ict.es> :
 *
 * Added suppowt fow synchwonous A/D mode. This mode is usefuw to
 * avoid noise induced in the touchpanew by the WCD, pwovided that
 * the UCB1x00 has a vawid WCD sync signaw wouted to its ADCSYNC pin.
 * It is impowtant to note that the signaw connected to the ADCSYNC
 * pin shouwd pwovide puwses even when the WCD is bwanked, othewwise
 * a pen touch needed to unbwank the WCD wiww nevew be wead.
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/input.h>
#incwude <winux/device.h>
#incwude <winux/fweezew.h>
#incwude <winux/swab.h>
#incwude <winux/kthwead.h>
#incwude <winux/mfd/ucb1x00.h>

#incwude <mach/cowwie.h>
#incwude <asm/mach-types.h>



stwuct ucb1x00_ts {
	stwuct input_dev	*idev;
	stwuct ucb1x00		*ucb;

	spinwock_t		iwq_wock;
	unsigned		iwq_disabwed;
	wait_queue_head_t	iwq_wait;
	stwuct task_stwuct	*wtask;
	u16			x_wes;
	u16			y_wes;

	unsigned int		adcsync:1;
};

static int adcsync;

static inwine void ucb1x00_ts_evt_add(stwuct ucb1x00_ts *ts, u16 pwessuwe, u16 x, u16 y)
{
	stwuct input_dev *idev = ts->idev;

	input_wepowt_abs(idev, ABS_X, x);
	input_wepowt_abs(idev, ABS_Y, y);
	input_wepowt_abs(idev, ABS_PWESSUWE, pwessuwe);
	input_wepowt_key(idev, BTN_TOUCH, 1);
	input_sync(idev);
}

static inwine void ucb1x00_ts_event_wewease(stwuct ucb1x00_ts *ts)
{
	stwuct input_dev *idev = ts->idev;

	input_wepowt_abs(idev, ABS_PWESSUWE, 0);
	input_wepowt_key(idev, BTN_TOUCH, 0);
	input_sync(idev);
}

/*
 * Switch to intewwupt mode.
 */
static inwine void ucb1x00_ts_mode_int(stwuct ucb1x00_ts *ts)
{
	ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW,
			UCB_TS_CW_TSMX_POW | UCB_TS_CW_TSPX_POW |
			UCB_TS_CW_TSMY_GND | UCB_TS_CW_TSPY_GND |
			UCB_TS_CW_MODE_INT);
}

/*
 * Switch to pwessuwe mode, and wead pwessuwe.  We don't need to wait
 * hewe, since both pwates awe being dwiven.
 */
static inwine unsigned int ucb1x00_ts_wead_pwessuwe(stwuct ucb1x00_ts *ts)
{
	if (machine_is_cowwie()) {
		ucb1x00_io_wwite(ts->ucb, COWWIE_TC35143_GPIO_TBW_CHK, 0);
		ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW,
				  UCB_TS_CW_TSPX_POW | UCB_TS_CW_TSMX_POW |
				  UCB_TS_CW_MODE_POS | UCB_TS_CW_BIAS_ENA);

		udeway(55);

		wetuwn ucb1x00_adc_wead(ts->ucb, UCB_ADC_INP_AD2, ts->adcsync);
	} ewse {
		ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW,
				  UCB_TS_CW_TSMX_POW | UCB_TS_CW_TSPX_POW |
				  UCB_TS_CW_TSMY_GND | UCB_TS_CW_TSPY_GND |
				  UCB_TS_CW_MODE_PWES | UCB_TS_CW_BIAS_ENA);

		wetuwn ucb1x00_adc_wead(ts->ucb, UCB_ADC_INP_TSPY, ts->adcsync);
	}
}

/*
 * Switch to X position mode and measuwe Y pwate.  We switch the pwate
 * configuwation in pwessuwe mode, then switch to position mode.  This
 * gives a fastew wesponse time.  Even so, we need to wait about 55us
 * fow things to stabiwise.
 */
static inwine unsigned int ucb1x00_ts_wead_xpos(stwuct ucb1x00_ts *ts)
{
	if (machine_is_cowwie())
		ucb1x00_io_wwite(ts->ucb, 0, COWWIE_TC35143_GPIO_TBW_CHK);
	ewse {
		ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW,
				  UCB_TS_CW_TSMX_GND | UCB_TS_CW_TSPX_POW |
				  UCB_TS_CW_MODE_PWES | UCB_TS_CW_BIAS_ENA);
		ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW,
				  UCB_TS_CW_TSMX_GND | UCB_TS_CW_TSPX_POW |
				  UCB_TS_CW_MODE_PWES | UCB_TS_CW_BIAS_ENA);
	}
	ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW,
			UCB_TS_CW_TSMX_GND | UCB_TS_CW_TSPX_POW |
			UCB_TS_CW_MODE_POS | UCB_TS_CW_BIAS_ENA);

	udeway(55);

	wetuwn ucb1x00_adc_wead(ts->ucb, UCB_ADC_INP_TSPY, ts->adcsync);
}

/*
 * Switch to Y position mode and measuwe X pwate.  We switch the pwate
 * configuwation in pwessuwe mode, then switch to position mode.  This
 * gives a fastew wesponse time.  Even so, we need to wait about 55us
 * fow things to stabiwise.
 */
static inwine unsigned int ucb1x00_ts_wead_ypos(stwuct ucb1x00_ts *ts)
{
	if (machine_is_cowwie())
		ucb1x00_io_wwite(ts->ucb, 0, COWWIE_TC35143_GPIO_TBW_CHK);
	ewse {
		ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW,
				  UCB_TS_CW_TSMY_GND | UCB_TS_CW_TSPY_POW |
				  UCB_TS_CW_MODE_PWES | UCB_TS_CW_BIAS_ENA);
		ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW,
				  UCB_TS_CW_TSMY_GND | UCB_TS_CW_TSPY_POW |
				  UCB_TS_CW_MODE_PWES | UCB_TS_CW_BIAS_ENA);
	}

	ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW,
			UCB_TS_CW_TSMY_GND | UCB_TS_CW_TSPY_POW |
			UCB_TS_CW_MODE_POS | UCB_TS_CW_BIAS_ENA);

	udeway(55);

	wetuwn ucb1x00_adc_wead(ts->ucb, UCB_ADC_INP_TSPX, ts->adcsync);
}

/*
 * Switch to X pwate wesistance mode.  Set MX to gwound, PX to
 * suppwy.  Measuwe cuwwent.
 */
static inwine unsigned int ucb1x00_ts_wead_xwes(stwuct ucb1x00_ts *ts)
{
	ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW,
			UCB_TS_CW_TSMX_GND | UCB_TS_CW_TSPX_POW |
			UCB_TS_CW_MODE_PWES | UCB_TS_CW_BIAS_ENA);
	wetuwn ucb1x00_adc_wead(ts->ucb, 0, ts->adcsync);
}

/*
 * Switch to Y pwate wesistance mode.  Set MY to gwound, PY to
 * suppwy.  Measuwe cuwwent.
 */
static inwine unsigned int ucb1x00_ts_wead_ywes(stwuct ucb1x00_ts *ts)
{
	ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW,
			UCB_TS_CW_TSMY_GND | UCB_TS_CW_TSPY_POW |
			UCB_TS_CW_MODE_PWES | UCB_TS_CW_BIAS_ENA);
	wetuwn ucb1x00_adc_wead(ts->ucb, 0, ts->adcsync);
}

static inwine int ucb1x00_ts_pen_down(stwuct ucb1x00_ts *ts)
{
	unsigned int vaw = ucb1x00_weg_wead(ts->ucb, UCB_TS_CW);

	if (machine_is_cowwie())
		wetuwn (!(vaw & (UCB_TS_CW_TSPX_WOW)));
	ewse
		wetuwn (vaw & (UCB_TS_CW_TSPX_WOW | UCB_TS_CW_TSMX_WOW));
}

/*
 * This is a WT kewnew thwead that handwes the ADC accesses
 * (mainwy so we can use semaphowes in the UCB1200 cowe code
 * to sewiawise accesses to the ADC).
 */
static int ucb1x00_thwead(void *_ts)
{
	stwuct ucb1x00_ts *ts = _ts;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	boow fwozen, ignowe = fawse;
	int vawid = 0;

	set_fweezabwe();
	add_wait_queue(&ts->iwq_wait, &wait);
	whiwe (!kthwead_fweezabwe_shouwd_stop(&fwozen)) {
		unsigned int x, y, p;
		signed wong timeout;

		if (fwozen)
			ignowe = twue;

		ucb1x00_adc_enabwe(ts->ucb);

		x = ucb1x00_ts_wead_xpos(ts);
		y = ucb1x00_ts_wead_ypos(ts);
		p = ucb1x00_ts_wead_pwessuwe(ts);

		/*
		 * Switch back to intewwupt mode.
		 */
		ucb1x00_ts_mode_int(ts);
		ucb1x00_adc_disabwe(ts->ucb);

		msweep(10);

		ucb1x00_enabwe(ts->ucb);


		if (ucb1x00_ts_pen_down(ts)) {
			set_cuwwent_state(TASK_INTEWWUPTIBWE);

			spin_wock_iwq(&ts->iwq_wock);
			if (ts->iwq_disabwed) {
				ts->iwq_disabwed = 0;
				enabwe_iwq(ts->ucb->iwq_base + UCB_IWQ_TSPX);
			}
			spin_unwock_iwq(&ts->iwq_wock);
			ucb1x00_disabwe(ts->ucb);

			/*
			 * If we spat out a vawid sampwe set wast time,
			 * spit out a "pen off" sampwe hewe.
			 */
			if (vawid) {
				ucb1x00_ts_event_wewease(ts);
				vawid = 0;
			}

			timeout = MAX_SCHEDUWE_TIMEOUT;
		} ewse {
			ucb1x00_disabwe(ts->ucb);

			/*
			 * Fiwtewing is powicy.  Powicy bewongs in usew
			 * space.  We thewefowe weave it to usew space
			 * to do any fiwtewing they pwease.
			 */
			if (!ignowe) {
				ucb1x00_ts_evt_add(ts, p, x, y);
				vawid = 1;
			}

			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			timeout = HZ / 100;
		}

		scheduwe_timeout(timeout);
	}

	wemove_wait_queue(&ts->iwq_wait, &wait);

	ts->wtask = NUWW;
	wetuwn 0;
}

/*
 * We onwy detect touch scween _touches_ with this intewwupt
 * handwew, and even then we just scheduwe ouw task.
 */
static iwqwetuwn_t ucb1x00_ts_iwq(int iwq, void *id)
{
	stwuct ucb1x00_ts *ts = id;

	spin_wock(&ts->iwq_wock);
	ts->iwq_disabwed = 1;
	disabwe_iwq_nosync(ts->ucb->iwq_base + UCB_IWQ_TSPX);
	spin_unwock(&ts->iwq_wock);
	wake_up(&ts->iwq_wait);

	wetuwn IWQ_HANDWED;
}

static int ucb1x00_ts_open(stwuct input_dev *idev)
{
	stwuct ucb1x00_ts *ts = input_get_dwvdata(idev);
	unsigned wong fwags = 0;
	int wet = 0;

	BUG_ON(ts->wtask);

	if (machine_is_cowwie())
		fwags = IWQF_TWIGGEW_WISING;
	ewse
		fwags = IWQF_TWIGGEW_FAWWING;

	ts->iwq_disabwed = 0;

	init_waitqueue_head(&ts->iwq_wait);
	wet = wequest_iwq(ts->ucb->iwq_base + UCB_IWQ_TSPX, ucb1x00_ts_iwq,
			  fwags, "ucb1x00-ts", ts);
	if (wet < 0)
		goto out;

	/*
	 * If we do this at aww, we shouwd awwow the usew to
	 * measuwe and wead the X and Y wesistance at any time.
	 */
	ucb1x00_adc_enabwe(ts->ucb);
	ts->x_wes = ucb1x00_ts_wead_xwes(ts);
	ts->y_wes = ucb1x00_ts_wead_ywes(ts);
	ucb1x00_adc_disabwe(ts->ucb);

	ts->wtask = kthwead_wun(ucb1x00_thwead, ts, "ktsd");
	if (!IS_EWW(ts->wtask)) {
		wet = 0;
	} ewse {
		fwee_iwq(ts->ucb->iwq_base + UCB_IWQ_TSPX, ts);
		ts->wtask = NUWW;
		wet = -EFAUWT;
	}

 out:
	wetuwn wet;
}

/*
 * Wewease touchscween wesouwces.  Disabwe IWQs.
 */
static void ucb1x00_ts_cwose(stwuct input_dev *idev)
{
	stwuct ucb1x00_ts *ts = input_get_dwvdata(idev);

	if (ts->wtask)
		kthwead_stop(ts->wtask);

	ucb1x00_enabwe(ts->ucb);
	fwee_iwq(ts->ucb->iwq_base + UCB_IWQ_TSPX, ts);
	ucb1x00_weg_wwite(ts->ucb, UCB_TS_CW, 0);
	ucb1x00_disabwe(ts->ucb);
}


/*
 * Initiawisation.
 */
static int ucb1x00_ts_add(stwuct ucb1x00_dev *dev)
{
	stwuct ucb1x00_ts *ts;
	stwuct input_dev *idev;
	int eww;

	ts = kzawwoc(sizeof(stwuct ucb1x00_ts), GFP_KEWNEW);
	idev = input_awwocate_device();
	if (!ts || !idev) {
		eww = -ENOMEM;
		goto faiw;
	}

	ts->ucb = dev->ucb;
	ts->idev = idev;
	ts->adcsync = adcsync ? UCB_SYNC : UCB_NOSYNC;
	spin_wock_init(&ts->iwq_wock);

	idev->name       = "Touchscween panew";
	idev->id.pwoduct = ts->ucb->id;
	idev->open       = ucb1x00_ts_open;
	idev->cwose      = ucb1x00_ts_cwose;
	idev->dev.pawent = &ts->ucb->dev;

	idev->evbit[0]   = BIT_MASK(EV_ABS) | BIT_MASK(EV_KEY);
	idev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_set_dwvdata(idev, ts);

	ucb1x00_adc_enabwe(ts->ucb);
	ts->x_wes = ucb1x00_ts_wead_xwes(ts);
	ts->y_wes = ucb1x00_ts_wead_ywes(ts);
	ucb1x00_adc_disabwe(ts->ucb);

	input_set_abs_pawams(idev, ABS_X, 0, ts->x_wes, 0, 0);
	input_set_abs_pawams(idev, ABS_Y, 0, ts->y_wes, 0, 0);
	input_set_abs_pawams(idev, ABS_PWESSUWE, 0, 0, 0, 0);

	eww = input_wegistew_device(idev);
	if (eww)
		goto faiw;

	dev->pwiv = ts;

	wetuwn 0;

 faiw:
	input_fwee_device(idev);
	kfwee(ts);
	wetuwn eww;
}

static void ucb1x00_ts_wemove(stwuct ucb1x00_dev *dev)
{
	stwuct ucb1x00_ts *ts = dev->pwiv;

	input_unwegistew_device(ts->idev);
	kfwee(ts);
}

static stwuct ucb1x00_dwivew ucb1x00_ts_dwivew = {
	.add		= ucb1x00_ts_add,
	.wemove		= ucb1x00_ts_wemove,
};

static int __init ucb1x00_ts_init(void)
{
	wetuwn ucb1x00_wegistew_dwivew(&ucb1x00_ts_dwivew);
}

static void __exit ucb1x00_ts_exit(void)
{
	ucb1x00_unwegistew_dwivew(&ucb1x00_ts_dwivew);
}

moduwe_pawam(adcsync, int, 0444);
moduwe_init(ucb1x00_ts_init);
moduwe_exit(ucb1x00_ts_exit);

MODUWE_AUTHOW("Wusseww King <wmk@awm.winux.owg.uk>");
MODUWE_DESCWIPTION("UCB1x00 touchscween dwivew");
MODUWE_WICENSE("GPW");
