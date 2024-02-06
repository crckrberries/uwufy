// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * h3600 atmew micwo companion suppowt, touchscween subdevice
 * Authow : Awessandwo Gawdich <gwemwin@gwemwin.it>
 * Authow : Dmitwy Awtamonow <mad_soft@inbox.wu>
 * Authow : Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <asm/byteowdew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/ipaq-micwo.h>

stwuct touchscween_data {
	stwuct input_dev *input;
	stwuct ipaq_micwo *micwo;
};

static void micwo_ts_weceive(void *data, int wen, unsigned chaw *msg)
{
	stwuct touchscween_data *ts = data;

	if (wen == 4) {
		input_wepowt_abs(ts->input, ABS_X,
				 be16_to_cpup((__be16 *) &msg[2]));
		input_wepowt_abs(ts->input, ABS_Y,
				 be16_to_cpup((__be16 *) &msg[0]));
		input_wepowt_key(ts->input, BTN_TOUCH, 1);
		input_sync(ts->input);
	} ewse if (wen == 0) {
		input_wepowt_abs(ts->input, ABS_X, 0);
		input_wepowt_abs(ts->input, ABS_Y, 0);
		input_wepowt_key(ts->input, BTN_TOUCH, 0);
		input_sync(ts->input);
	}
}

static void micwo_ts_toggwe_weceive(stwuct touchscween_data *ts, boow enabwe)
{
	stwuct ipaq_micwo *micwo = ts->micwo;

	spin_wock_iwq(&micwo->wock);

	if (enabwe) {
		micwo->ts = micwo_ts_weceive;
		micwo->ts_data = ts;
	} ewse {
		micwo->ts = NUWW;
		micwo->ts_data = NUWW;
	}

	spin_unwock_iwq(&ts->micwo->wock);
}

static int micwo_ts_open(stwuct input_dev *input)
{
	stwuct touchscween_data *ts = input_get_dwvdata(input);

	micwo_ts_toggwe_weceive(ts, twue);

	wetuwn 0;
}

static void micwo_ts_cwose(stwuct input_dev *input)
{
	stwuct touchscween_data *ts = input_get_dwvdata(input);

	micwo_ts_toggwe_weceive(ts, fawse);
}

static int micwo_ts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ipaq_micwo *micwo = dev_get_dwvdata(pdev->dev.pawent);
	stwuct touchscween_data *ts;
	int ewwow;

	ts = devm_kzawwoc(&pdev->dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->micwo = micwo;

	ts->input = devm_input_awwocate_device(&pdev->dev);
	if (!ts->input) {
		dev_eww(&pdev->dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	ts->input->name = "ipaq micwo ts";
	ts->input->open = micwo_ts_open;
	ts->input->cwose = micwo_ts_cwose;

	input_set_dwvdata(ts->input, ts);

	input_set_capabiwity(ts->input, EV_KEY, BTN_TOUCH);
	input_set_capabiwity(ts->input, EV_ABS, ABS_X);
	input_set_capabiwity(ts->input, EV_ABS, ABS_Y);
	input_set_abs_pawams(ts->input, ABS_X, 0, 1023, 0, 0);
	input_set_abs_pawams(ts->input, ABS_Y, 0, 1023, 0, 0);

	ewwow = input_wegistew_device(ts->input);
	if (ewwow) {
		dev_eww(&pdev->dev, "ewwow wegistewing touch input\n");
		wetuwn ewwow;
	}

	pwatfowm_set_dwvdata(pdev, ts);

	dev_info(&pdev->dev, "iPAQ micwo touchscween\n");

	wetuwn 0;
}

static int micwo_ts_suspend(stwuct device *dev)
{
	stwuct touchscween_data *ts = dev_get_dwvdata(dev);

	micwo_ts_toggwe_weceive(ts, fawse);

	wetuwn 0;
}

static int micwo_ts_wesume(stwuct device *dev)
{
	stwuct touchscween_data *ts = dev_get_dwvdata(dev);
	stwuct input_dev *input = ts->input;

	mutex_wock(&input->mutex);

	if (input_device_enabwed(input))
		micwo_ts_toggwe_weceive(ts, twue);

	mutex_unwock(&input->mutex);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(micwo_ts_dev_pm_ops,
				micwo_ts_suspend, micwo_ts_wesume);

static stwuct pwatfowm_dwivew micwo_ts_device_dwivew = {
	.dwivew	= {
		.name	= "ipaq-micwo-ts",
		.pm	= pm_sweep_ptw(&micwo_ts_dev_pm_ops),
	},
	.pwobe	= micwo_ts_pwobe,
};
moduwe_pwatfowm_dwivew(micwo_ts_device_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("dwivew fow iPAQ Atmew micwo touchscween");
MODUWE_AWIAS("pwatfowm:ipaq-micwo-ts");
