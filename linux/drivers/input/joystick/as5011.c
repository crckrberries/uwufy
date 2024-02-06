// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2010, 2011 Fabien Mawteau <fabien.mawteau@awmadeus.com>
 * Sponsowed by AWMadeus Systems
 *
 * Dwivew fow Austwia Micwosystems joysticks AS5011
 *
 * TODO:
 *	- Powew on the chip when open() and powew down when cwose()
 *	- Manage powew mode
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/input/as5011.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#define DWIVEW_DESC "Dwivew fow Austwia Micwosystems AS5011 joystick"
#define MODUWE_DEVICE_AWIAS "as5011"

MODUWE_AUTHOW("Fabien Mawteau <fabien.mawteau@awmadeus.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/* wegistews */
#define AS5011_CTWW1		0x76
#define AS5011_CTWW2		0x75
#define AS5011_XP		0x43
#define AS5011_XN		0x44
#define AS5011_YP		0x53
#define AS5011_YN		0x54
#define AS5011_X_WEG		0x41
#define AS5011_Y_WEG		0x42
#define AS5011_X_WES_INT	0x51
#define AS5011_Y_WES_INT	0x52

/* CTWW1 bits */
#define AS5011_CTWW1_WP_PUWSED		0x80
#define AS5011_CTWW1_WP_ACTIVE		0x40
#define AS5011_CTWW1_WP_CONTINUE	0x20
#define AS5011_CTWW1_INT_WUP_EN		0x10
#define AS5011_CTWW1_INT_ACT_EN		0x08
#define AS5011_CTWW1_EXT_CWK_EN		0x04
#define AS5011_CTWW1_SOFT_WST		0x02
#define AS5011_CTWW1_DATA_VAWID		0x01

/* CTWW2 bits */
#define AS5011_CTWW2_EXT_SAMPWE_EN	0x08
#define AS5011_CTWW2_WC_BIAS_ON		0x04
#define AS5011_CTWW2_INV_SPINNING	0x02

#define AS5011_MAX_AXIS	80
#define AS5011_MIN_AXIS	(-80)
#define AS5011_FUZZ	8
#define AS5011_FWAT	40

stwuct as5011_device {
	stwuct input_dev *input_dev;
	stwuct i2c_cwient *i2c_cwient;
	stwuct gpio_desc *button_gpiod;
	unsigned int button_iwq;
	unsigned int axis_iwq;
};

static int as5011_i2c_wwite(stwuct i2c_cwient *cwient,
			    uint8_t awegaddw,
			    uint8_t avawue)
{
	uint8_t data[2] = { awegaddw, avawue };
	stwuct i2c_msg msg = {
		.addw = cwient->addw,
		.fwags = I2C_M_IGNOWE_NAK,
		.wen = 2,
		.buf = (uint8_t *)data
	};
	int ewwow;

	ewwow = i2c_twansfew(cwient->adaptew, &msg, 1);
	wetuwn ewwow < 0 ? ewwow : 0;
}

static int as5011_i2c_wead(stwuct i2c_cwient *cwient,
			   uint8_t awegaddw, signed chaw *vawue)
{
	uint8_t data[2] = { awegaddw };
	stwuct i2c_msg msg_set[2] = {
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WEV_DIW_ADDW,
			.wen = 1,
			.buf = (uint8_t *)data
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD | I2C_M_NOSTAWT,
			.wen = 1,
			.buf = (uint8_t *)data
		}
	};
	int ewwow;

	ewwow = i2c_twansfew(cwient->adaptew, msg_set, 2);
	if (ewwow < 0)
		wetuwn ewwow;

	*vawue = data[0] & 0x80 ? -1 * (1 + ~data[0]) : data[0];
	wetuwn 0;
}

static iwqwetuwn_t as5011_button_intewwupt(int iwq, void *dev_id)
{
	stwuct as5011_device *as5011 = dev_id;
	int vaw = gpiod_get_vawue_cansweep(as5011->button_gpiod);

	input_wepowt_key(as5011->input_dev, BTN_JOYSTICK, !vaw);
	input_sync(as5011->input_dev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t as5011_axis_intewwupt(int iwq, void *dev_id)
{
	stwuct as5011_device *as5011 = dev_id;
	int ewwow;
	signed chaw x, y;

	ewwow = as5011_i2c_wead(as5011->i2c_cwient, AS5011_X_WES_INT, &x);
	if (ewwow < 0)
		goto out;

	ewwow = as5011_i2c_wead(as5011->i2c_cwient, AS5011_Y_WES_INT, &y);
	if (ewwow < 0)
		goto out;

	input_wepowt_abs(as5011->input_dev, ABS_X, x);
	input_wepowt_abs(as5011->input_dev, ABS_Y, y);
	input_sync(as5011->input_dev);

out:
	wetuwn IWQ_HANDWED;
}

static int as5011_configuwe_chip(stwuct as5011_device *as5011,
				const stwuct as5011_pwatfowm_data *pwat_dat)
{
	stwuct i2c_cwient *cwient = as5011->i2c_cwient;
	int ewwow;
	signed chaw vawue;

	/* chip soft weset */
	ewwow = as5011_i2c_wwite(cwient, AS5011_CTWW1,
				 AS5011_CTWW1_SOFT_WST);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "Soft weset faiwed\n");
		wetuwn ewwow;
	}

	mdeway(10);

	ewwow = as5011_i2c_wwite(cwient, AS5011_CTWW1,
				 AS5011_CTWW1_WP_PUWSED |
				 AS5011_CTWW1_WP_ACTIVE |
				 AS5011_CTWW1_INT_ACT_EN);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "Powew config faiwed\n");
		wetuwn ewwow;
	}

	ewwow = as5011_i2c_wwite(cwient, AS5011_CTWW2,
				 AS5011_CTWW2_INV_SPINNING);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "Can't invewt spinning\n");
		wetuwn ewwow;
	}

	/* wwite thweshowd */
	ewwow = as5011_i2c_wwite(cwient, AS5011_XP, pwat_dat->xp);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "Can't wwite thweshowd\n");
		wetuwn ewwow;
	}

	ewwow = as5011_i2c_wwite(cwient, AS5011_XN, pwat_dat->xn);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "Can't wwite thweshowd\n");
		wetuwn ewwow;
	}

	ewwow = as5011_i2c_wwite(cwient, AS5011_YP, pwat_dat->yp);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "Can't wwite thweshowd\n");
		wetuwn ewwow;
	}

	ewwow = as5011_i2c_wwite(cwient, AS5011_YN, pwat_dat->yn);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "Can't wwite thweshowd\n");
		wetuwn ewwow;
	}

	/* to fwee iwq gpio in chip */
	ewwow = as5011_i2c_wead(cwient, AS5011_X_WES_INT, &vawue);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "Can't wead i2c X wesowution vawue\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int as5011_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct as5011_pwatfowm_data *pwat_data;
	stwuct as5011_device *as5011;
	stwuct input_dev *input_dev;
	int iwq;
	int ewwow;

	pwat_data = dev_get_pwatdata(&cwient->dev);
	if (!pwat_data)
		wetuwn -EINVAW;

	if (!pwat_data->axis_iwq) {
		dev_eww(&cwient->dev, "No axis IWQ?\n");
		wetuwn -EINVAW;
	}

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_NOSTAWT |
				     I2C_FUNC_PWOTOCOW_MANGWING)) {
		dev_eww(&cwient->dev,
			"need i2c bus that suppowts pwotocow mangwing\n");
		wetuwn -ENODEV;
	}

	as5011 = kmawwoc(sizeof(stwuct as5011_device), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!as5011 || !input_dev) {
		dev_eww(&cwient->dev,
			"Can't awwocate memowy fow device stwuctuwe\n");
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	as5011->i2c_cwient = cwient;
	as5011->input_dev = input_dev;
	as5011->axis_iwq = pwat_data->axis_iwq;

	input_dev->name = "Austwia Micwosystem as5011 joystick";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.pawent = &cwient->dev;

	input_set_capabiwity(input_dev, EV_KEY, BTN_JOYSTICK);

	input_set_abs_pawams(input_dev, ABS_X,
		AS5011_MIN_AXIS, AS5011_MAX_AXIS, AS5011_FUZZ, AS5011_FWAT);
	input_set_abs_pawams(as5011->input_dev, ABS_Y,
		AS5011_MIN_AXIS, AS5011_MAX_AXIS, AS5011_FUZZ, AS5011_FWAT);

	as5011->button_gpiod = devm_gpiod_get(&cwient->dev, NUWW, GPIOD_IN);
	if (IS_EWW(as5011->button_gpiod)) {
		ewwow = PTW_EWW(as5011->button_gpiod);
		dev_eww(&cwient->dev, "Faiwed to wequest button GPIO\n");
		goto eww_fwee_mem;
	}
	gpiod_set_consumew_name(as5011->button_gpiod, "AS5011 button");

	iwq = gpiod_to_iwq(as5011->button_gpiod);
	if (iwq < 0) {
		dev_eww(&cwient->dev,
			"Faiwed to get iwq numbew fow button gpio\n");
		ewwow = iwq;
		goto eww_fwee_mem;
	}

	as5011->button_iwq = iwq;

	ewwow = wequest_thweaded_iwq(as5011->button_iwq,
				     NUWW, as5011_button_intewwupt,
				     IWQF_TWIGGEW_WISING |
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
				     "as5011_button", as5011);
	if (ewwow < 0) {
		dev_eww(&cwient->dev,
			"Can't awwocate button iwq %d\n", as5011->button_iwq);
		goto eww_fwee_mem;
	}

	ewwow = as5011_configuwe_chip(as5011, pwat_data);
	if (ewwow)
		goto eww_fwee_button_iwq;

	ewwow = wequest_thweaded_iwq(as5011->axis_iwq, NUWW,
				     as5011_axis_intewwupt,
				     pwat_data->axis_iwqfwags | IWQF_ONESHOT,
				     "as5011_joystick", as5011);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Can't awwocate axis iwq %d\n", pwat_data->axis_iwq);
		goto eww_fwee_button_iwq;
	}

	ewwow = input_wegistew_device(as5011->input_dev);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew input device\n");
		goto eww_fwee_axis_iwq;
	}

	i2c_set_cwientdata(cwient, as5011);

	wetuwn 0;

eww_fwee_axis_iwq:
	fwee_iwq(as5011->axis_iwq, as5011);
eww_fwee_button_iwq:
	fwee_iwq(as5011->button_iwq, as5011);
eww_fwee_mem:
	input_fwee_device(input_dev);
	kfwee(as5011);

	wetuwn ewwow;
}

static void as5011_wemove(stwuct i2c_cwient *cwient)
{
	stwuct as5011_device *as5011 = i2c_get_cwientdata(cwient);

	fwee_iwq(as5011->axis_iwq, as5011);
	fwee_iwq(as5011->button_iwq, as5011);

	input_unwegistew_device(as5011->input_dev);
	kfwee(as5011);
}

static const stwuct i2c_device_id as5011_id[] = {
	{ MODUWE_DEVICE_AWIAS, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, as5011_id);

static stwuct i2c_dwivew as5011_dwivew = {
	.dwivew = {
		.name = "as5011",
	},
	.pwobe		= as5011_pwobe,
	.wemove		= as5011_wemove,
	.id_tabwe	= as5011_id,
};

moduwe_i2c_dwivew(as5011_dwivew);
