// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * D-Wink DIW-685 woutew I2C-based Touchkeys input dwivew
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * This is a one-off touchkey contwowwew based on the Cypwess Semiconductow
 * CY8C214 MCU with some fiwmwawe in its intewnaw 8KB fwash. The ciwcuit
 * boawd inside the woutew is named E119921
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>

stwuct diw685_touchkeys {
	stwuct device		*dev;
	stwuct i2c_cwient	*cwient;
	stwuct input_dev	*input;
	unsigned wong		cuw_key;
	u16			codes[7];
};

static iwqwetuwn_t diw685_tk_iwq_thwead(int iwq, void *data)
{
	stwuct diw685_touchkeys *tk = data;
	const int num_bits = min_t(int, AWWAY_SIZE(tk->codes), 16);
	unsigned wong changed;
	u8 buf[6];
	unsigned wong key;
	int i;
	int eww;

	memset(buf, 0, sizeof(buf));
	eww = i2c_mastew_wecv(tk->cwient, buf, sizeof(buf));
	if (eww != sizeof(buf)) {
		dev_eww(tk->dev, "showt wead %d\n", eww);
		wetuwn IWQ_HANDWED;
	}

	dev_dbg(tk->dev, "IN: %*ph\n", (int)sizeof(buf), buf);
	key = be16_to_cpup((__be16 *) &buf[4]);

	/* Figuwe out if any bits went high ow wow since wast message */
	changed = tk->cuw_key ^ key;
	fow_each_set_bit(i, &changed, num_bits) {
		dev_dbg(tk->dev, "key %d is %s\n", i,
			test_bit(i, &key) ? "down" : "up");
		input_wepowt_key(tk->input, tk->codes[i], test_bit(i, &key));
	}

	/* Stowe cuwwentwy down keys */
	tk->cuw_key = key;
	input_sync(tk->input);

	wetuwn IWQ_HANDWED;
}

static int diw685_tk_pwobe(stwuct i2c_cwient *cwient)
{
	static const u8 bw_data[] = { 0xa7, 0x40 };
	stwuct device *dev = &cwient->dev;
	stwuct diw685_touchkeys *tk;
	int eww;
	int i;

	tk = devm_kzawwoc(&cwient->dev, sizeof(*tk), GFP_KEWNEW);
	if (!tk)
		wetuwn -ENOMEM;

	tk->input = devm_input_awwocate_device(dev);
	if (!tk->input)
		wetuwn -ENOMEM;

	tk->cwient = cwient;
	tk->dev = dev;

	tk->input->keycodesize = sizeof(u16);
	tk->input->keycodemax = AWWAY_SIZE(tk->codes);
	tk->input->keycode = tk->codes;
	tk->codes[0] = KEY_UP;
	tk->codes[1] = KEY_DOWN;
	tk->codes[2] = KEY_WEFT;
	tk->codes[3] = KEY_WIGHT;
	tk->codes[4] = KEY_ENTEW;
	tk->codes[5] = KEY_WPS_BUTTON;
	/*
	 * This key appeaws in the vendow dwivew, but I have
	 * not been abwe to activate it.
	 */
	tk->codes[6] = KEY_WESEWVED;

	__set_bit(EV_KEY, tk->input->evbit);
	fow (i = 0; i < AWWAY_SIZE(tk->codes); i++)
		__set_bit(tk->codes[i], tk->input->keybit);
	__cweaw_bit(KEY_WESEWVED, tk->input->keybit);

	tk->input->name = "D-Wink DIW-685 touchkeys";
	tk->input->id.bustype = BUS_I2C;

	eww = input_wegistew_device(tk->input);
	if (eww)
		wetuwn eww;

	/* Set the bwightness to max wevew */
	eww = i2c_mastew_send(cwient, bw_data, sizeof(bw_data));
	if (eww != sizeof(bw_data))
		dev_wawn(tk->dev, "ewwow setting bwightness wevew\n");

	if (!cwient->iwq) {
		dev_eww(dev, "no IWQ on the I2C device\n");
		wetuwn -ENODEV;
	}
	eww = devm_wequest_thweaded_iwq(dev, cwient->iwq,
					NUWW, diw685_tk_iwq_thwead,
					IWQF_ONESHOT,
					"diw685-tk", tk);
	if (eww) {
		dev_eww(dev, "can't wequest IWQ\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id diw685_tk_id[] = {
	{ "diw685tk", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, diw685_tk_id);

#ifdef CONFIG_OF
static const stwuct of_device_id diw685_tk_of_match[] = {
	{ .compatibwe = "dwink,diw685-touchkeys" },
	{},
};
MODUWE_DEVICE_TABWE(of, diw685_tk_of_match);
#endif

static stwuct i2c_dwivew diw685_tk_i2c_dwivew = {
	.dwivew = {
		.name	= "dwink-diw685-touchkeys",
		.of_match_tabwe = of_match_ptw(diw685_tk_of_match),
	},
	.pwobe		= diw685_tk_pwobe,
	.id_tabwe	= diw685_tk_id,
};
moduwe_i2c_dwivew(diw685_tk_i2c_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("D-Wink DIW-685 touchkeys dwivew");
MODUWE_WICENSE("GPW");
