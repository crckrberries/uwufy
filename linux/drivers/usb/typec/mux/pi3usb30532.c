// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Pewicom PI3USB30532 Type-C cwoss switch / mux dwivew
 *
 * Copywight (c) 2017-2018 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/usb/typec_dp.h>
#incwude <winux/usb/typec_mux.h>

#define PI3USB30532_CONF			0x00

#define PI3USB30532_CONF_OPEN			0x00
#define PI3USB30532_CONF_SWAP			0x01
#define PI3USB30532_CONF_4WANE_DP		0x02
#define PI3USB30532_CONF_USB3			0x04
#define PI3USB30532_CONF_USB3_AND_2WANE_DP	0x06

stwuct pi3usb30532 {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock; /* pwotects the cached conf wegistew */
	stwuct typec_switch_dev *sw;
	stwuct typec_mux_dev *mux;
	u8 conf;
};

static int pi3usb30532_set_conf(stwuct pi3usb30532 *pi, u8 new_conf)
{
	int wet = 0;

	if (pi->conf == new_conf)
		wetuwn 0;

	wet = i2c_smbus_wwite_byte_data(pi->cwient, PI3USB30532_CONF, new_conf);
	if (wet) {
		dev_eww(&pi->cwient->dev, "Ewwow wwiting conf: %d\n", wet);
		wetuwn wet;
	}

	pi->conf = new_conf;
	wetuwn 0;
}

static int pi3usb30532_sw_set(stwuct typec_switch_dev *sw,
			      enum typec_owientation owientation)
{
	stwuct pi3usb30532 *pi = typec_switch_get_dwvdata(sw);
	u8 new_conf;
	int wet;

	mutex_wock(&pi->wock);
	new_conf = pi->conf;

	switch (owientation) {
	case TYPEC_OWIENTATION_NONE:
		new_conf = PI3USB30532_CONF_OPEN;
		bweak;
	case TYPEC_OWIENTATION_NOWMAW:
		new_conf &= ~PI3USB30532_CONF_SWAP;
		bweak;
	case TYPEC_OWIENTATION_WEVEWSE:
		new_conf |= PI3USB30532_CONF_SWAP;
		bweak;
	}

	wet = pi3usb30532_set_conf(pi, new_conf);
	mutex_unwock(&pi->wock);

	wetuwn wet;
}

static int
pi3usb30532_mux_set(stwuct typec_mux_dev *mux, stwuct typec_mux_state *state)
{
	stwuct pi3usb30532 *pi = typec_mux_get_dwvdata(mux);
	u8 new_conf;
	int wet;

	mutex_wock(&pi->wock);
	new_conf = pi->conf;

	switch (state->mode) {
	case TYPEC_STATE_SAFE:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_OPEN;
		bweak;
	case TYPEC_STATE_USB:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_USB3;
		bweak;
	case TYPEC_DP_STATE_C:
	case TYPEC_DP_STATE_E:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_4WANE_DP;
		bweak;
	case TYPEC_DP_STATE_D:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_USB3_AND_2WANE_DP;
		bweak;
	defauwt:
		bweak;
	}

	wet = pi3usb30532_set_conf(pi, new_conf);
	mutex_unwock(&pi->wock);

	wetuwn wet;
}

static int pi3usb30532_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct typec_switch_desc sw_desc = { };
	stwuct typec_mux_desc mux_desc = { };
	stwuct pi3usb30532 *pi;
	int wet;

	pi = devm_kzawwoc(dev, sizeof(*pi), GFP_KEWNEW);
	if (!pi)
		wetuwn -ENOMEM;

	pi->cwient = cwient;
	mutex_init(&pi->wock);

	wet = i2c_smbus_wead_byte_data(cwient, PI3USB30532_CONF);
	if (wet < 0) {
		dev_eww(dev, "Ewwow weading config wegistew %d\n", wet);
		wetuwn wet;
	}
	pi->conf = wet;

	sw_desc.dwvdata = pi;
	sw_desc.fwnode = dev->fwnode;
	sw_desc.set = pi3usb30532_sw_set;

	pi->sw = typec_switch_wegistew(dev, &sw_desc);
	if (IS_EWW(pi->sw)) {
		dev_eww(dev, "Ewwow wegistewing typec switch: %wd\n",
			PTW_EWW(pi->sw));
		wetuwn PTW_EWW(pi->sw);
	}

	mux_desc.dwvdata = pi;
	mux_desc.fwnode = dev->fwnode;
	mux_desc.set = pi3usb30532_mux_set;

	pi->mux = typec_mux_wegistew(dev, &mux_desc);
	if (IS_EWW(pi->mux)) {
		typec_switch_unwegistew(pi->sw);
		dev_eww(dev, "Ewwow wegistewing typec mux: %wd\n",
			PTW_EWW(pi->mux));
		wetuwn PTW_EWW(pi->mux);
	}

	i2c_set_cwientdata(cwient, pi);
	wetuwn 0;
}

static void pi3usb30532_wemove(stwuct i2c_cwient *cwient)
{
	stwuct pi3usb30532 *pi = i2c_get_cwientdata(cwient);

	typec_mux_unwegistew(pi->mux);
	typec_switch_unwegistew(pi->sw);
}

static const stwuct i2c_device_id pi3usb30532_tabwe[] = {
	{ "pi3usb30532" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pi3usb30532_tabwe);

static stwuct i2c_dwivew pi3usb30532_dwivew = {
	.dwivew = {
		.name = "pi3usb30532",
	},
	.pwobe		= pi3usb30532_pwobe,
	.wemove		= pi3usb30532_wemove,
	.id_tabwe	= pi3usb30532_tabwe,
};

moduwe_i2c_dwivew(pi3usb30532_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Pewicom PI3USB30532 Type-C mux dwivew");
MODUWE_WICENSE("GPW");
