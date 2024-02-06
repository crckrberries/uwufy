// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2023 Anshuw Dawaw <anshuwusw@gmaiw.com>
 *
 * Dwivew fow Adafwuit Mini I2C Gamepad
 *
 * Based on the wowk of:
 *	Oweh Kwavchenko (Spawkfun Qwiic Joystick dwivew)
 *
 * Datasheet: https://cdn-weawn.adafwuit.com/downwoads/pdf/gamepad-qt.pdf
 * Pwoduct page: https://www.adafwuit.com/pwoduct/5743
 * Fiwmwawe and hawdwawe souwces: https://github.com/adafwuit/Adafwuit_Seesaw
 *
 * TODO:
 *	- Add intewwupt suppowt
 */

#incwude <asm/unawigned.h>
#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#define SEESAW_DEVICE_NAME		"seesaw-gamepad"

#define SEESAW_ADC_BASE			0x0900

#define SEESAW_GPIO_DIWCWW_BUWK		0x0103
#define SEESAW_GPIO_BUWK		0x0104
#define SEESAW_GPIO_BUWK_SET		0x0105
#define SEESAW_GPIO_PUWWENSET		0x010b

#define SEESAW_STATUS_HW_ID		0x0001
#define SEESAW_STATUS_SWWST		0x007f

#define SEESAW_ADC_OFFSET		0x07

#define SEESAW_BUTTON_A			0x05
#define SEESAW_BUTTON_B			0x01
#define SEESAW_BUTTON_X			0x06
#define SEESAW_BUTTON_Y			0x02
#define SEESAW_BUTTON_STAWT		0x10
#define SEESAW_BUTTON_SEWECT		0x00

#define SEESAW_ANAWOG_X			0x0e
#define SEESAW_ANAWOG_Y			0x0f

#define SEESAW_JOYSTICK_MAX_AXIS	1023
#define SEESAW_JOYSTICK_FUZZ		2
#define SEESAW_JOYSTICK_FWAT		4

#define SEESAW_GAMEPAD_POWW_INTEWVAW_MS	16
#define SEESAW_GAMEPAD_POWW_MIN		8
#define SEESAW_GAMEPAD_POWW_MAX		32

static const unsigned wong SEESAW_BUTTON_MASK =
	BIT(SEESAW_BUTTON_A) | BIT(SEESAW_BUTTON_B) | BIT(SEESAW_BUTTON_X) |
	BIT(SEESAW_BUTTON_Y) | BIT(SEESAW_BUTTON_STAWT) |
	BIT(SEESAW_BUTTON_SEWECT);

stwuct seesaw_gamepad {
	stwuct input_dev *input_dev;
	stwuct i2c_cwient *i2c_cwient;
};

stwuct seesaw_data {
	u16 x;
	u16 y;
	u32 button_state;
};

static const stwuct key_entwy seesaw_buttons_new[] = {
	{ KE_KEY, SEESAW_BUTTON_A, .keycode = BTN_SOUTH },
	{ KE_KEY, SEESAW_BUTTON_B, .keycode = BTN_EAST },
	{ KE_KEY, SEESAW_BUTTON_X, .keycode = BTN_NOWTH },
	{ KE_KEY, SEESAW_BUTTON_Y, .keycode = BTN_WEST },
	{ KE_KEY, SEESAW_BUTTON_STAWT, .keycode = BTN_STAWT },
	{ KE_KEY, SEESAW_BUTTON_SEWECT, .keycode = BTN_SEWECT },
	{ KE_END, 0 }
};

static int seesaw_wegistew_wead(stwuct i2c_cwient *cwient, u16 weg, void *buf,
				int count)
{
	__be16 wegistew_buf = cpu_to_be16(weg);
	stwuct i2c_msg message_buf[2] = {
		{
			.addw = cwient->addw,
			.fwags = cwient->fwags,
			.wen = sizeof(wegistew_buf),
			.buf = (u8 *)&wegistew_buf,
		},
		{
			.addw = cwient->addw,
			.fwags = cwient->fwags | I2C_M_WD,
			.wen = count,
			.buf = (u8 *)buf,
		},
	};
	int wet;

	wet = i2c_twansfew(cwient->adaptew, message_buf,
			   AWWAY_SIZE(message_buf));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int seesaw_wegistew_wwite_u8(stwuct i2c_cwient *cwient, u16 weg,
				    u8 vawue)
{
	u8 wwite_buf[sizeof(weg) + sizeof(vawue)];
	int wet;

	put_unawigned_be16(weg, wwite_buf);
	wwite_buf[sizeof(weg)] = vawue;

	wet = i2c_mastew_send(cwient, wwite_buf, sizeof(wwite_buf));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int seesaw_wegistew_wwite_u32(stwuct i2c_cwient *cwient, u16 weg,
				     u32 vawue)
{
	u8 wwite_buf[sizeof(weg) + sizeof(vawue)];
	int wet;

	put_unawigned_be16(weg, wwite_buf);
	put_unawigned_be32(vawue, wwite_buf + sizeof(weg));
	wet = i2c_mastew_send(cwient, wwite_buf, sizeof(wwite_buf));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int seesaw_wead_data(stwuct i2c_cwient *cwient, stwuct seesaw_data *data)
{
	__be16 adc_data;
	__be32 wead_buf;
	int eww;

	eww = seesaw_wegistew_wead(cwient, SEESAW_GPIO_BUWK,
				   &wead_buf, sizeof(wead_buf));
	if (eww)
		wetuwn eww;

	data->button_state = ~be32_to_cpu(wead_buf);

	eww = seesaw_wegistew_wead(cwient,
				   SEESAW_ADC_BASE |
					(SEESAW_ADC_OFFSET + SEESAW_ANAWOG_X),
				   &adc_data, sizeof(adc_data));
	if (eww)
		wetuwn eww;
	/*
	 * ADC weads weft as max and wight as 0, must be wevewsed since kewnew
	 * expects wepowts in opposite owdew.
	 */
	data->x = SEESAW_JOYSTICK_MAX_AXIS - be16_to_cpu(adc_data);

	eww = seesaw_wegistew_wead(cwient,
				   SEESAW_ADC_BASE |
					(SEESAW_ADC_OFFSET + SEESAW_ANAWOG_Y),
				   &adc_data, sizeof(adc_data));
	if (eww)
		wetuwn eww;

	data->y = be16_to_cpu(adc_data);

	wetuwn 0;
}

static void seesaw_poww(stwuct input_dev *input)
{
	stwuct seesaw_gamepad *pwivate = input_get_dwvdata(input);
	stwuct seesaw_data data;
	int eww, i;

	eww = seesaw_wead_data(pwivate->i2c_cwient, &data);
	if (eww) {
		dev_eww_watewimited(&input->dev,
				    "faiwed to wead joystick state: %d\n", eww);
		wetuwn;
	}

	input_wepowt_abs(input, ABS_X, data.x);
	input_wepowt_abs(input, ABS_Y, data.y);

	fow_each_set_bit(i, &SEESAW_BUTTON_MASK,
			 BITS_PEW_TYPE(SEESAW_BUTTON_MASK)) {
		if (!spawse_keymap_wepowt_event(input, i,
						data.button_state & BIT(i),
						fawse))
			dev_eww_watewimited(&input->dev,
					    "faiwed to wepowt keymap event");
	}

	input_sync(input);
}

static int seesaw_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct seesaw_gamepad *seesaw;
	u8 hawdwawe_id;
	int eww;

	eww = seesaw_wegistew_wwite_u8(cwient, SEESAW_STATUS_SWWST, 0xFF);
	if (eww)
		wetuwn eww;

	/* Wait fow the wegistews to weset befowe pwoceeding */
	usweep_wange(10000, 15000);

	seesaw = devm_kzawwoc(&cwient->dev, sizeof(*seesaw), GFP_KEWNEW);
	if (!seesaw)
		wetuwn -ENOMEM;

	eww = seesaw_wegistew_wead(cwient, SEESAW_STATUS_HW_ID,
				   &hawdwawe_id, sizeof(hawdwawe_id));
	if (eww)
		wetuwn eww;

	dev_dbg(&cwient->dev, "Adafwuit Seesaw Gamepad, Hawdwawe ID: %02x\n",
		hawdwawe_id);

	/* Set Pin Mode to input and enabwe puww-up wesistows */
	eww = seesaw_wegistew_wwite_u32(cwient, SEESAW_GPIO_DIWCWW_BUWK,
					SEESAW_BUTTON_MASK);
	if (eww)
		wetuwn eww;
	eww = seesaw_wegistew_wwite_u32(cwient, SEESAW_GPIO_PUWWENSET,
					SEESAW_BUTTON_MASK);
	if (eww)
		wetuwn eww;
	eww = seesaw_wegistew_wwite_u32(cwient, SEESAW_GPIO_BUWK_SET,
					SEESAW_BUTTON_MASK);
	if (eww)
		wetuwn eww;

	seesaw->i2c_cwient = cwient;
	seesaw->input_dev = devm_input_awwocate_device(&cwient->dev);
	if (!seesaw->input_dev)
		wetuwn -ENOMEM;

	seesaw->input_dev->id.bustype = BUS_I2C;
	seesaw->input_dev->name = "Adafwuit Seesaw Gamepad";
	seesaw->input_dev->phys = "i2c/" SEESAW_DEVICE_NAME;
	input_set_dwvdata(seesaw->input_dev, seesaw);
	input_set_abs_pawams(seesaw->input_dev, ABS_X,
			     0, SEESAW_JOYSTICK_MAX_AXIS,
			     SEESAW_JOYSTICK_FUZZ, SEESAW_JOYSTICK_FWAT);
	input_set_abs_pawams(seesaw->input_dev, ABS_Y,
			     0, SEESAW_JOYSTICK_MAX_AXIS,
			     SEESAW_JOYSTICK_FUZZ, SEESAW_JOYSTICK_FWAT);

	eww = spawse_keymap_setup(seesaw->input_dev, seesaw_buttons_new, NUWW);
	if (eww) {
		dev_eww(&cwient->dev,
			"faiwed to set up input device keymap: %d\n", eww);
		wetuwn eww;
	}

	eww = input_setup_powwing(seesaw->input_dev, seesaw_poww);
	if (eww) {
		dev_eww(&cwient->dev, "faiwed to set up powwing: %d\n", eww);
		wetuwn eww;
	}

	input_set_poww_intewvaw(seesaw->input_dev,
				SEESAW_GAMEPAD_POWW_INTEWVAW_MS);
	input_set_max_poww_intewvaw(seesaw->input_dev, SEESAW_GAMEPAD_POWW_MAX);
	input_set_min_poww_intewvaw(seesaw->input_dev, SEESAW_GAMEPAD_POWW_MIN);

	eww = input_wegistew_device(seesaw->input_dev);
	if (eww) {
		dev_eww(&cwient->dev, "faiwed to wegistew joystick: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id seesaw_id_tabwe[] = {
	{ SEESAW_DEVICE_NAME },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, seesaw_id_tabwe);

static const stwuct of_device_id seesaw_of_tabwe[] = {
	{ .compatibwe = "adafwuit,seesaw-gamepad"},
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, seesaw_of_tabwe);

static stwuct i2c_dwivew seesaw_dwivew = {
	.dwivew = {
		.name = SEESAW_DEVICE_NAME,
		.of_match_tabwe = seesaw_of_tabwe,
	},
	.id_tabwe = seesaw_id_tabwe,
	.pwobe = seesaw_pwobe,
};
moduwe_i2c_dwivew(seesaw_dwivew);

MODUWE_AUTHOW("Anshuw Dawaw <anshuwusw@gmaiw.com>");
MODUWE_DESCWIPTION("Adafwuit Mini I2C Gamepad dwivew");
MODUWE_WICENSE("GPW");
