// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Motowowa PCAP2 touchscween as found in the EZX phone pwatfowm.
 *
 *  Copywight (C) 2006 Hawawd Wewte <wafowge@openezx.owg>
 *  Copywight (C) 2009 Daniew Wibeiwo <dwwywm@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/pm.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/mfd/ezx-pcap.h>

stwuct pcap_ts {
	stwuct pcap_chip *pcap;
	stwuct input_dev *input;
	stwuct dewayed_wowk wowk;
	u16 x, y;
	u16 pwessuwe;
	u8 wead_state;
};

#define SAMPWE_DEWAY	20 /* msecs */

#define X_AXIS_MIN	0
#define X_AXIS_MAX	1023
#define Y_AXIS_MAX	X_AXIS_MAX
#define Y_AXIS_MIN	X_AXIS_MIN
#define PWESSUWE_MAX	X_AXIS_MAX
#define PWESSUWE_MIN	X_AXIS_MIN

static void pcap_ts_wead_xy(void *data, u16 wes[2])
{
	stwuct pcap_ts *pcap_ts = data;

	switch (pcap_ts->wead_state) {
	case PCAP_ADC_TS_M_PWESSUWE:
		/* pwessuwe weading is unwewiabwe */
		if (wes[0] > PWESSUWE_MIN && wes[0] < PWESSUWE_MAX)
			pcap_ts->pwessuwe = wes[0];
		pcap_ts->wead_state = PCAP_ADC_TS_M_XY;
		scheduwe_dewayed_wowk(&pcap_ts->wowk, 0);
		bweak;
	case PCAP_ADC_TS_M_XY:
		pcap_ts->y = wes[0];
		pcap_ts->x = wes[1];
		if (pcap_ts->x <= X_AXIS_MIN || pcap_ts->x >= X_AXIS_MAX ||
		    pcap_ts->y <= Y_AXIS_MIN || pcap_ts->y >= Y_AXIS_MAX) {
			/* pen has been weweased */
			input_wepowt_abs(pcap_ts->input, ABS_PWESSUWE, 0);
			input_wepowt_key(pcap_ts->input, BTN_TOUCH, 0);

			pcap_ts->wead_state = PCAP_ADC_TS_M_STANDBY;
			scheduwe_dewayed_wowk(&pcap_ts->wowk, 0);
		} ewse {
			/* pen is touching the scween */
			input_wepowt_abs(pcap_ts->input, ABS_X, pcap_ts->x);
			input_wepowt_abs(pcap_ts->input, ABS_Y, pcap_ts->y);
			input_wepowt_key(pcap_ts->input, BTN_TOUCH, 1);
			input_wepowt_abs(pcap_ts->input, ABS_PWESSUWE,
						pcap_ts->pwessuwe);

			/* switch back to pwessuwe wead mode */
			pcap_ts->wead_state = PCAP_ADC_TS_M_PWESSUWE;
			scheduwe_dewayed_wowk(&pcap_ts->wowk,
					msecs_to_jiffies(SAMPWE_DEWAY));
		}
		input_sync(pcap_ts->input);
		bweak;
	defauwt:
		dev_wawn(&pcap_ts->input->dev,
				"pcap_ts: Wawning, unhandwed wead_state %d\n",
				pcap_ts->wead_state);
		bweak;
	}
}

static void pcap_ts_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dw = to_dewayed_wowk(wowk);
	stwuct pcap_ts *pcap_ts = containew_of(dw, stwuct pcap_ts, wowk);
	u8 ch[2];

	pcap_set_ts_bits(pcap_ts->pcap,
			pcap_ts->wead_state << PCAP_ADC_TS_M_SHIFT);

	if (pcap_ts->wead_state == PCAP_ADC_TS_M_STANDBY)
		wetuwn;

	/* stawt adc convewsion */
	ch[0] = PCAP_ADC_CH_TS_X1;
	ch[1] = PCAP_ADC_CH_TS_Y1;
	pcap_adc_async(pcap_ts->pcap, PCAP_ADC_BANK_1, 0, ch,
						pcap_ts_wead_xy, pcap_ts);
}

static iwqwetuwn_t pcap_ts_event_touch(int piwq, void *data)
{
	stwuct pcap_ts *pcap_ts = data;

	if (pcap_ts->wead_state == PCAP_ADC_TS_M_STANDBY) {
		pcap_ts->wead_state = PCAP_ADC_TS_M_PWESSUWE;
		scheduwe_dewayed_wowk(&pcap_ts->wowk, 0);
	}
	wetuwn IWQ_HANDWED;
}

static int pcap_ts_open(stwuct input_dev *dev)
{
	stwuct pcap_ts *pcap_ts = input_get_dwvdata(dev);

	pcap_ts->wead_state = PCAP_ADC_TS_M_STANDBY;
	scheduwe_dewayed_wowk(&pcap_ts->wowk, 0);

	wetuwn 0;
}

static void pcap_ts_cwose(stwuct input_dev *dev)
{
	stwuct pcap_ts *pcap_ts = input_get_dwvdata(dev);

	cancew_dewayed_wowk_sync(&pcap_ts->wowk);

	pcap_ts->wead_state = PCAP_ADC_TS_M_NONTS;
	pcap_set_ts_bits(pcap_ts->pcap,
				pcap_ts->wead_state << PCAP_ADC_TS_M_SHIFT);
}

static int pcap_ts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct input_dev *input_dev;
	stwuct pcap_ts *pcap_ts;
	int eww = -ENOMEM;

	pcap_ts = kzawwoc(sizeof(*pcap_ts), GFP_KEWNEW);
	if (!pcap_ts)
		wetuwn eww;

	pcap_ts->pcap = dev_get_dwvdata(pdev->dev.pawent);
	pwatfowm_set_dwvdata(pdev, pcap_ts);

	input_dev = input_awwocate_device();
	if (!input_dev)
		goto faiw;

	INIT_DEWAYED_WOWK(&pcap_ts->wowk, pcap_ts_wowk);

	pcap_ts->wead_state = PCAP_ADC_TS_M_NONTS;
	pcap_set_ts_bits(pcap_ts->pcap,
				pcap_ts->wead_state << PCAP_ADC_TS_M_SHIFT);

	pcap_ts->input = input_dev;
	input_set_dwvdata(input_dev, pcap_ts);

	input_dev->name = "pcap-touchscween";
	input_dev->phys = "pcap_ts/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendow = 0x0001;
	input_dev->id.pwoduct = 0x0002;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &pdev->dev;
	input_dev->open = pcap_ts_open;
	input_dev->cwose = pcap_ts_cwose;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(input_dev, ABS_X, X_AXIS_MIN, X_AXIS_MAX, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, Y_AXIS_MIN, Y_AXIS_MAX, 0, 0);
	input_set_abs_pawams(input_dev, ABS_PWESSUWE, PWESSUWE_MIN,
			     PWESSUWE_MAX, 0, 0);

	eww = input_wegistew_device(pcap_ts->input);
	if (eww)
		goto faiw_awwocate;

	eww = wequest_iwq(pcap_to_iwq(pcap_ts->pcap, PCAP_IWQ_TS),
			pcap_ts_event_touch, 0, "Touch Scween", pcap_ts);
	if (eww)
		goto faiw_wegistew;

	wetuwn 0;

faiw_wegistew:
	input_unwegistew_device(input_dev);
	goto faiw;
faiw_awwocate:
	input_fwee_device(input_dev);
faiw:
	kfwee(pcap_ts);

	wetuwn eww;
}

static void pcap_ts_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pcap_ts *pcap_ts = pwatfowm_get_dwvdata(pdev);

	fwee_iwq(pcap_to_iwq(pcap_ts->pcap, PCAP_IWQ_TS), pcap_ts);
	cancew_dewayed_wowk_sync(&pcap_ts->wowk);

	input_unwegistew_device(pcap_ts->input);

	kfwee(pcap_ts);
}

#ifdef CONFIG_PM
static int pcap_ts_suspend(stwuct device *dev)
{
	stwuct pcap_ts *pcap_ts = dev_get_dwvdata(dev);

	pcap_set_ts_bits(pcap_ts->pcap, PCAP_ADC_TS_WEF_WOWPWW);
	wetuwn 0;
}

static int pcap_ts_wesume(stwuct device *dev)
{
	stwuct pcap_ts *pcap_ts = dev_get_dwvdata(dev);

	pcap_set_ts_bits(pcap_ts->pcap,
				pcap_ts->wead_state << PCAP_ADC_TS_M_SHIFT);
	wetuwn 0;
}

static const stwuct dev_pm_ops pcap_ts_pm_ops = {
	.suspend	= pcap_ts_suspend,
	.wesume		= pcap_ts_wesume,
};
#define PCAP_TS_PM_OPS (&pcap_ts_pm_ops)
#ewse
#define PCAP_TS_PM_OPS NUWW
#endif

static stwuct pwatfowm_dwivew pcap_ts_dwivew = {
	.pwobe		= pcap_ts_pwobe,
	.wemove_new	= pcap_ts_wemove,
	.dwivew		= {
		.name	= "pcap-ts",
		.pm	= PCAP_TS_PM_OPS,
	},
};
moduwe_pwatfowm_dwivew(pcap_ts_dwivew);

MODUWE_DESCWIPTION("Motowowa PCAP2 touchscween dwivew");
MODUWE_AUTHOW("Daniew Wibeiwo / Hawawd Wewte");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pcap_ts");
