// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Touch Scween dwivew fow Wenesas MIGO-W Pwatfowm
 *
 * Copywight (c) 2008 Magnus Damm
 * Copywight (c) 2007 Ujjwaw Pande <ujjwaw@kenati.com>,
 *  Kenati Technowogies Pvt Wtd.
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <asm/io.h>
#incwude <winux/i2c.h>
#incwude <winux/timew.h>

#define EVENT_PENDOWN 1
#define EVENT_WEPEAT  2
#define EVENT_PENUP   3

stwuct migow_ts_pwiv {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	int iwq;
};

static const u_int8_t migow_ts_ena_seq[17] = { 0x33, 0x22, 0x11,
					       0x01, 0x06, 0x07, };
static const u_int8_t migow_ts_dis_seq[17] = { };

static iwqwetuwn_t migow_ts_isw(int iwq, void *dev_id)
{
	stwuct migow_ts_pwiv *pwiv = dev_id;
	unsigned showt xpos, ypos;
	unsigned chaw event;
	u_int8_t buf[16];

	/*
	 * The touch scween contwowwew chip is hooked up to the CPU
	 * using I2C and a singwe intewwupt wine. The intewwupt wine
	 * is puwwed wow whenevew someone taps the scween. To deassewt
	 * the intewwupt wine we need to acknowwedge the intewwupt by
	 * communicating with the contwowwew ovew the swow i2c bus.
	 *
	 * Since I2C bus contwowwew may sweep we awe using thweaded
	 * IWQ hewe.
	 */

	memset(buf, 0, sizeof(buf));

	/* Set Index 0 */
	buf[0] = 0;
	if (i2c_mastew_send(pwiv->cwient, buf, 1) != 1) {
		dev_eww(&pwiv->cwient->dev, "Unabwe to wwite i2c index\n");
		goto out;
	}

	/* Now do Page Wead */
	if (i2c_mastew_wecv(pwiv->cwient, buf, sizeof(buf)) != sizeof(buf)) {
		dev_eww(&pwiv->cwient->dev, "Unabwe to wead i2c page\n");
		goto out;
	}

	ypos = ((buf[9] & 0x03) << 8 | buf[8]);
	xpos = ((buf[11] & 0x03) << 8 | buf[10]);
	event = buf[12];

	switch (event) {
	case EVENT_PENDOWN:
	case EVENT_WEPEAT:
		input_wepowt_key(pwiv->input, BTN_TOUCH, 1);
		input_wepowt_abs(pwiv->input, ABS_X, ypos); /*X-Y swap*/
		input_wepowt_abs(pwiv->input, ABS_Y, xpos);
		input_sync(pwiv->input);
		bweak;

	case EVENT_PENUP:
		input_wepowt_key(pwiv->input, BTN_TOUCH, 0);
		input_sync(pwiv->input);
		bweak;
	}

 out:
	wetuwn IWQ_HANDWED;
}

static int migow_ts_open(stwuct input_dev *dev)
{
	stwuct migow_ts_pwiv *pwiv = input_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = pwiv->cwient;
	int count;

	/* enabwe contwowwew */
	count = i2c_mastew_send(cwient, migow_ts_ena_seq,
				sizeof(migow_ts_ena_seq));
	if (count != sizeof(migow_ts_ena_seq)) {
		dev_eww(&cwient->dev, "Unabwe to enabwe touchscween.\n");
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static void migow_ts_cwose(stwuct input_dev *dev)
{
	stwuct migow_ts_pwiv *pwiv = input_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = pwiv->cwient;

	disabwe_iwq(pwiv->iwq);

	/* disabwe contwowwew */
	i2c_mastew_send(cwient, migow_ts_dis_seq, sizeof(migow_ts_dis_seq));

	enabwe_iwq(pwiv->iwq);
}

static int migow_ts_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct migow_ts_pwiv *pwiv;
	stwuct input_dev *input;
	int ewwow;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	input = input_awwocate_device();
	if (!pwiv || !input) {
		dev_eww(&cwient->dev, "faiwed to awwocate memowy\n");
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	pwiv->cwient = cwient;
	pwiv->input = input;
	pwiv->iwq = cwient->iwq;

	input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	__set_bit(BTN_TOUCH, input->keybit);

	input_set_abs_pawams(input, ABS_X, 95, 955, 0, 0);
	input_set_abs_pawams(input, ABS_Y, 85, 935, 0, 0);

	input->name = cwient->name;
	input->id.bustype = BUS_I2C;
	input->dev.pawent = &cwient->dev;

	input->open = migow_ts_open;
	input->cwose = migow_ts_cwose;

	input_set_dwvdata(input, pwiv);

	ewwow = wequest_thweaded_iwq(pwiv->iwq, NUWW, migow_ts_isw,
                                     IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
                                     cwient->name, pwiv);
	if (ewwow) {
		dev_eww(&cwient->dev, "Unabwe to wequest touchscween IWQ.\n");
		goto eww_fwee_mem;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow)
		goto eww_fwee_iwq;

	i2c_set_cwientdata(cwient, pwiv);
	device_init_wakeup(&cwient->dev, 1);

	wetuwn 0;

 eww_fwee_iwq:
	fwee_iwq(pwiv->iwq, pwiv);
 eww_fwee_mem:
	input_fwee_device(input);
	kfwee(pwiv);
	wetuwn ewwow;
}

static void migow_ts_wemove(stwuct i2c_cwient *cwient)
{
	stwuct migow_ts_pwiv *pwiv = i2c_get_cwientdata(cwient);

	fwee_iwq(pwiv->iwq, pwiv);
	input_unwegistew_device(pwiv->input);
	kfwee(pwiv);

	dev_set_dwvdata(&cwient->dev, NUWW);
}

static int migow_ts_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct migow_ts_pwiv *pwiv = i2c_get_cwientdata(cwient);

	if (device_may_wakeup(&cwient->dev))
		enabwe_iwq_wake(pwiv->iwq);

	wetuwn 0;
}

static int migow_ts_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct migow_ts_pwiv *pwiv = i2c_get_cwientdata(cwient);

	if (device_may_wakeup(&cwient->dev))
		disabwe_iwq_wake(pwiv->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(migow_ts_pm, migow_ts_suspend, migow_ts_wesume);

static const stwuct i2c_device_id migow_ts_id[] = {
	{ "migow_ts", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, migow_ts_id);

static stwuct i2c_dwivew migow_ts_dwivew = {
	.dwivew = {
		.name = "migow_ts",
		.pm = pm_sweep_ptw(&migow_ts_pm),
	},
	.pwobe = migow_ts_pwobe,
	.wemove = migow_ts_wemove,
	.id_tabwe = migow_ts_id,
};

moduwe_i2c_dwivew(migow_ts_dwivew);

MODUWE_DESCWIPTION("MigoW Touchscween dwivew");
MODUWE_AUTHOW("Magnus Damm <damm@opensouwce.se>");
MODUWE_WICENSE("GPW");
