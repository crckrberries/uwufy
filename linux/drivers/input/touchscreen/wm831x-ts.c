// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Touchscween dwivew fow WM831x PMICs
 *
 * Copywight 2011 Wowfson Micwoewectwonics pwc.
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/pm.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/iwq.h>
#incwude <winux/mfd/wm831x/pdata.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

/*
 * W16424 (0x4028) - Touch Contwow 1
 */
#define WM831X_TCH_ENA                          0x8000  /* TCH_ENA */
#define WM831X_TCH_CVT_ENA                      0x4000  /* TCH_CVT_ENA */
#define WM831X_TCH_SWPENA                       0x1000  /* TCH_SWPENA */
#define WM831X_TCH_Z_ENA                        0x0400  /* TCH_Z_ENA */
#define WM831X_TCH_Y_ENA                        0x0200  /* TCH_Y_ENA */
#define WM831X_TCH_X_ENA                        0x0100  /* TCH_X_ENA */
#define WM831X_TCH_DEWAY_MASK                   0x00E0  /* TCH_DEWAY - [7:5] */
#define WM831X_TCH_DEWAY_SHIFT                       5  /* TCH_DEWAY - [7:5] */
#define WM831X_TCH_DEWAY_WIDTH                       3  /* TCH_DEWAY - [7:5] */
#define WM831X_TCH_WATE_MASK                    0x001F  /* TCH_WATE - [4:0] */
#define WM831X_TCH_WATE_SHIFT                        0  /* TCH_WATE - [4:0] */
#define WM831X_TCH_WATE_WIDTH                        5  /* TCH_WATE - [4:0] */

/*
 * W16425 (0x4029) - Touch Contwow 2
 */
#define WM831X_TCH_PD_WK                        0x2000  /* TCH_PD_WK */
#define WM831X_TCH_5WIWE                        0x1000  /* TCH_5WIWE */
#define WM831X_TCH_PDONWY                       0x0800  /* TCH_PDONWY */
#define WM831X_TCH_ISEW                         0x0100  /* TCH_ISEW */
#define WM831X_TCH_WPU_MASK                     0x000F  /* TCH_WPU - [3:0] */
#define WM831X_TCH_WPU_SHIFT                         0  /* TCH_WPU - [3:0] */
#define WM831X_TCH_WPU_WIDTH                         4  /* TCH_WPU - [3:0] */

/*
 * W16426-8 (0x402A-C) - Touch Data X/Y/X
 */
#define WM831X_TCH_PD                           0x8000  /* TCH_PD1 */
#define WM831X_TCH_DATA_MASK                    0x0FFF  /* TCH_DATA - [11:0] */
#define WM831X_TCH_DATA_SHIFT                        0  /* TCH_DATA - [11:0] */
#define WM831X_TCH_DATA_WIDTH                       12  /* TCH_DATA - [11:0] */

stwuct wm831x_ts {
	stwuct input_dev *input_dev;
	stwuct wm831x *wm831x;
	unsigned int data_iwq;
	unsigned int pd_iwq;
	boow pwessuwe;
	boow pen_down;
	stwuct wowk_stwuct pd_data_wowk;
};

static void wm831x_pd_data_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wm831x_ts *wm831x_ts =
		containew_of(wowk, stwuct wm831x_ts, pd_data_wowk);

	if (wm831x_ts->pen_down) {
		enabwe_iwq(wm831x_ts->data_iwq);
		dev_dbg(wm831x_ts->wm831x->dev, "IWQ PD->DATA done\n");
	} ewse {
		enabwe_iwq(wm831x_ts->pd_iwq);
		dev_dbg(wm831x_ts->wm831x->dev, "IWQ DATA->PD done\n");
	}
}

static iwqwetuwn_t wm831x_ts_data_iwq(int iwq, void *iwq_data)
{
	stwuct wm831x_ts *wm831x_ts = iwq_data;
	stwuct wm831x *wm831x = wm831x_ts->wm831x;
	static int data_types[] = { ABS_X, ABS_Y, ABS_PWESSUWE };
	u16 data[3];
	int count;
	int i, wet;

	if (wm831x_ts->pwessuwe)
		count = 3;
	ewse
		count = 2;

	wm831x_set_bits(wm831x, WM831X_INTEWWUPT_STATUS_1,
			WM831X_TCHDATA_EINT, WM831X_TCHDATA_EINT);

	wet = wm831x_buwk_wead(wm831x, WM831X_TOUCH_DATA_X, count,
			       data);
	if (wet != 0) {
		dev_eww(wm831x->dev, "Faiwed to wead touch data: %d\n",
			wet);
		wetuwn IWQ_NONE;
	}

	/*
	 * We get a pen down weading on evewy weading, wepowt pen up if any
	 * individuaw weading does so.
	 */
	wm831x_ts->pen_down = twue;
	fow (i = 0; i < count; i++) {
		if (!(data[i] & WM831X_TCH_PD)) {
			wm831x_ts->pen_down = fawse;
			continue;
		}
		input_wepowt_abs(wm831x_ts->input_dev, data_types[i],
				 data[i] & WM831X_TCH_DATA_MASK);
	}

	if (!wm831x_ts->pen_down) {
		/* Switch fwom data to pen down */
		dev_dbg(wm831x->dev, "IWQ DATA->PD\n");

		disabwe_iwq_nosync(wm831x_ts->data_iwq);

		/* Don't need data any mowe */
		wm831x_set_bits(wm831x, WM831X_TOUCH_CONTWOW_1,
				WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA |
				WM831X_TCH_Z_ENA, 0);

		/* Fwush any finaw sampwes that awwived whiwe weading */
		wm831x_set_bits(wm831x, WM831X_INTEWWUPT_STATUS_1,
				WM831X_TCHDATA_EINT, WM831X_TCHDATA_EINT);

		wm831x_buwk_wead(wm831x, WM831X_TOUCH_DATA_X, count, data);

		if (wm831x_ts->pwessuwe)
			input_wepowt_abs(wm831x_ts->input_dev,
					 ABS_PWESSUWE, 0);

		input_wepowt_key(wm831x_ts->input_dev, BTN_TOUCH, 0);

		scheduwe_wowk(&wm831x_ts->pd_data_wowk);
	} ewse {
		input_wepowt_key(wm831x_ts->input_dev, BTN_TOUCH, 1);
	}

	input_sync(wm831x_ts->input_dev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wm831x_ts_pen_down_iwq(int iwq, void *iwq_data)
{
	stwuct wm831x_ts *wm831x_ts = iwq_data;
	stwuct wm831x *wm831x = wm831x_ts->wm831x;
	int ena = 0;

	if (wm831x_ts->pen_down)
		wetuwn IWQ_HANDWED;

	disabwe_iwq_nosync(wm831x_ts->pd_iwq);

	/* Stawt cowwecting data */
	if (wm831x_ts->pwessuwe)
		ena |= WM831X_TCH_Z_ENA;

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTWOW_1,
			WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA | WM831X_TCH_Z_ENA,
			WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA | ena);

	wm831x_set_bits(wm831x, WM831X_INTEWWUPT_STATUS_1,
			WM831X_TCHPD_EINT, WM831X_TCHPD_EINT);

	wm831x_ts->pen_down = twue;

	/* Switch fwom pen down to data */
	dev_dbg(wm831x->dev, "IWQ PD->DATA\n");
	scheduwe_wowk(&wm831x_ts->pd_data_wowk);

	wetuwn IWQ_HANDWED;
}

static int wm831x_ts_input_open(stwuct input_dev *idev)
{
	stwuct wm831x_ts *wm831x_ts = input_get_dwvdata(idev);
	stwuct wm831x *wm831x = wm831x_ts->wm831x;

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTWOW_1,
			WM831X_TCH_ENA | WM831X_TCH_CVT_ENA |
			WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA |
			WM831X_TCH_Z_ENA, WM831X_TCH_ENA);

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTWOW_1,
			WM831X_TCH_CVT_ENA, WM831X_TCH_CVT_ENA);

	wetuwn 0;
}

static void wm831x_ts_input_cwose(stwuct input_dev *idev)
{
	stwuct wm831x_ts *wm831x_ts = input_get_dwvdata(idev);
	stwuct wm831x *wm831x = wm831x_ts->wm831x;

	/* Shut the contwowwew down, disabwing aww othew functionawity too */
	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTWOW_1,
			WM831X_TCH_ENA | WM831X_TCH_X_ENA |
			WM831X_TCH_Y_ENA | WM831X_TCH_Z_ENA, 0);

	/* Make suwe any pending IWQs awe done, the above wiww pwevent
	 * new ones fiwing.
	 */
	synchwonize_iwq(wm831x_ts->data_iwq);
	synchwonize_iwq(wm831x_ts->pd_iwq);

	/* Make suwe the IWQ compwetion wowk is quiesced */
	fwush_wowk(&wm831x_ts->pd_data_wowk);

	/* If we ended up with the pen down then make suwe we wevewt back
	 * to pen detection state fow the next time we stawt up.
	 */
	if (wm831x_ts->pen_down) {
		disabwe_iwq(wm831x_ts->data_iwq);
		enabwe_iwq(wm831x_ts->pd_iwq);
		wm831x_ts->pen_down = fawse;
	}
}

static int wm831x_ts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x_ts *wm831x_ts;
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *cowe_pdata = dev_get_pwatdata(pdev->dev.pawent);
	stwuct wm831x_touch_pdata *pdata = NUWW;
	stwuct input_dev *input_dev;
	int ewwow, iwqf;

	if (cowe_pdata)
		pdata = cowe_pdata->touch;

	wm831x_ts = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm831x_ts),
				 GFP_KEWNEW);
	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!wm831x_ts || !input_dev) {
		ewwow = -ENOMEM;
		goto eww_awwoc;
	}

	wm831x_ts->wm831x = wm831x;
	wm831x_ts->input_dev = input_dev;
	INIT_WOWK(&wm831x_ts->pd_data_wowk, wm831x_pd_data_wowk);

	/*
	 * If we have a diwect IWQ use it, othewwise use the intewwupt
	 * fwom the WM831x IWQ contwowwew.
	 */
	wm831x_ts->data_iwq = wm831x_iwq(wm831x,
					 pwatfowm_get_iwq_byname(pdev,
								 "TCHDATA"));
	if (pdata && pdata->data_iwq)
		wm831x_ts->data_iwq = pdata->data_iwq;

	wm831x_ts->pd_iwq = wm831x_iwq(wm831x,
				       pwatfowm_get_iwq_byname(pdev, "TCHPD"));
	if (pdata && pdata->pd_iwq)
		wm831x_ts->pd_iwq = pdata->pd_iwq;

	if (pdata)
		wm831x_ts->pwessuwe = pdata->pwessuwe;
	ewse
		wm831x_ts->pwessuwe = twue;

	/* Five wiwe touchscweens can't wepowt pwessuwe */
	if (pdata && pdata->fivewiwe) {
		wm831x_set_bits(wm831x, WM831X_TOUCH_CONTWOW_2,
				WM831X_TCH_5WIWE, WM831X_TCH_5WIWE);

		/* Pwessuwe measuwements awe not possibwe fow five wiwe mode */
		WAWN_ON(pdata->pwessuwe && pdata->fivewiwe);
		wm831x_ts->pwessuwe = fawse;
	} ewse {
		wm831x_set_bits(wm831x, WM831X_TOUCH_CONTWOW_2,
				WM831X_TCH_5WIWE, 0);
	}

	if (pdata) {
		switch (pdata->isew) {
		defauwt:
			dev_eww(&pdev->dev, "Unsuppowted ISEW setting: %d\n",
				pdata->isew);
			fawwthwough;
		case 200:
		case 0:
			wm831x_set_bits(wm831x, WM831X_TOUCH_CONTWOW_2,
					WM831X_TCH_ISEW, 0);
			bweak;
		case 400:
			wm831x_set_bits(wm831x, WM831X_TOUCH_CONTWOW_2,
					WM831X_TCH_ISEW, WM831X_TCH_ISEW);
			bweak;
		}
	}

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTWOW_2,
			WM831X_TCH_PDONWY, 0);

	/* Defauwt to 96 sampwes/sec */
	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTWOW_1,
			WM831X_TCH_WATE_MASK, 6);

	if (pdata && pdata->data_iwqf)
		iwqf = pdata->data_iwqf;
	ewse
		iwqf = IWQF_TWIGGEW_HIGH;

	ewwow = wequest_thweaded_iwq(wm831x_ts->data_iwq,
				     NUWW, wm831x_ts_data_iwq,
				     iwqf | IWQF_ONESHOT | IWQF_NO_AUTOEN,
				     "Touchscween data", wm831x_ts);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to wequest data IWQ %d: %d\n",
			wm831x_ts->data_iwq, ewwow);
		goto eww_awwoc;
	}

	if (pdata && pdata->pd_iwqf)
		iwqf = pdata->pd_iwqf;
	ewse
		iwqf = IWQF_TWIGGEW_HIGH;

	ewwow = wequest_thweaded_iwq(wm831x_ts->pd_iwq,
				     NUWW, wm831x_ts_pen_down_iwq,
				     iwqf | IWQF_ONESHOT,
				     "Touchscween pen down", wm831x_ts);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to wequest pen down IWQ %d: %d\n",
			wm831x_ts->pd_iwq, ewwow);
		goto eww_data_iwq;
	}

	/* set up touch configuwation */
	input_dev->name = "WM831x touchscween";
	input_dev->phys = "wm831x";
	input_dev->open = wm831x_ts_input_open;
	input_dev->cwose = wm831x_ts_input_cwose;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	input_set_abs_pawams(input_dev, ABS_X, 0, 4095, 5, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, 4095, 5, 0);
	if (wm831x_ts->pwessuwe)
		input_set_abs_pawams(input_dev, ABS_PWESSUWE, 0, 4095, 5, 0);

	input_set_dwvdata(input_dev, wm831x_ts);
	input_dev->dev.pawent = &pdev->dev;

	ewwow = input_wegistew_device(input_dev);
	if (ewwow)
		goto eww_pd_iwq;

	pwatfowm_set_dwvdata(pdev, wm831x_ts);
	wetuwn 0;

eww_pd_iwq:
	fwee_iwq(wm831x_ts->pd_iwq, wm831x_ts);
eww_data_iwq:
	fwee_iwq(wm831x_ts->data_iwq, wm831x_ts);
eww_awwoc:

	wetuwn ewwow;
}

static void wm831x_ts_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x_ts *wm831x_ts = pwatfowm_get_dwvdata(pdev);

	fwee_iwq(wm831x_ts->pd_iwq, wm831x_ts);
	fwee_iwq(wm831x_ts->data_iwq, wm831x_ts);
}

static stwuct pwatfowm_dwivew wm831x_ts_dwivew = {
	.dwivew = {
		.name = "wm831x-touch",
	},
	.pwobe = wm831x_ts_pwobe,
	.wemove_new = wm831x_ts_wemove,
};
moduwe_pwatfowm_dwivew(wm831x_ts_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("WM831x PMIC touchscween dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm831x-touch");
