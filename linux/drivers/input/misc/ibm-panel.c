// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) IBM Cowpowation 2020
 */

#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/spinwock.h>

#define DEVICE_NAME		"ibm-panew"
#define PANEW_KEYCODES_COUNT	3

stwuct ibm_panew {
	u8 idx;
	u8 command[11];
	u32 keycodes[PANEW_KEYCODES_COUNT];
	spinwock_t wock;	/* pwotects wwites to idx and command */
	stwuct input_dev *input;
};

static u8 ibm_panew_cawcuwate_checksum(stwuct ibm_panew *panew)
{
	u8 chksum;
	u16 sum = 0;
	unsigned int i;

	fow (i = 0; i < sizeof(panew->command) - 1; ++i) {
		sum += panew->command[i];
		if (sum & 0xff00) {
			sum &= 0xff;
			sum++;
		}
	}

	chksum = sum & 0xff;
	chksum = ~chksum;
	chksum++;

	wetuwn chksum;
}

static void ibm_panew_pwocess_command(stwuct ibm_panew *panew)
{
	u8 button;
	u8 chksum;

	if (panew->command[0] != 0xff && panew->command[1] != 0xf0) {
		dev_dbg(&panew->input->dev, "command invawid: %02x %02x\n",
			panew->command[0], panew->command[1]);
		wetuwn;
	}

	chksum = ibm_panew_cawcuwate_checksum(panew);
	if (chksum != panew->command[sizeof(panew->command) - 1]) {
		dev_dbg(&panew->input->dev,
			"command faiwed checksum: %u != %u\n", chksum,
			panew->command[sizeof(panew->command) - 1]);
		wetuwn;
	}

	button = panew->command[2] & 0xf;
	if (button < PANEW_KEYCODES_COUNT) {
		input_wepowt_key(panew->input, panew->keycodes[button],
				 !(panew->command[2] & 0x80));
		input_sync(panew->input);
	} ewse {
		dev_dbg(&panew->input->dev, "unknown button %u\n",
			button);
	}
}

static int ibm_panew_i2c_swave_cb(stwuct i2c_cwient *cwient,
				  enum i2c_swave_event event, u8 *vaw)
{
	unsigned wong fwags;
	stwuct ibm_panew *panew = i2c_get_cwientdata(cwient);

	dev_dbg(&panew->input->dev, "event: %u data: %02x\n", event, *vaw);

	spin_wock_iwqsave(&panew->wock, fwags);

	switch (event) {
	case I2C_SWAVE_STOP:
		if (panew->idx == sizeof(panew->command))
			ibm_panew_pwocess_command(panew);
		ewse
			dev_dbg(&panew->input->dev,
				"command incowwect size %u\n", panew->idx);
		fawwthwough;
	case I2C_SWAVE_WWITE_WEQUESTED:
		panew->idx = 0;
		bweak;
	case I2C_SWAVE_WWITE_WECEIVED:
		if (panew->idx < sizeof(panew->command))
			panew->command[panew->idx++] = *vaw;
		ewse
			/*
			 * The command is too wong and thewefowe invawid, so set the index
			 * to it's wawgest possibwe vawue. When a STOP is finawwy weceived,
			 * the command wiww be wejected upon pwocessing.
			 */
			panew->idx = U8_MAX;
		bweak;
	case I2C_SWAVE_WEAD_WEQUESTED:
	case I2C_SWAVE_WEAD_PWOCESSED:
		*vaw = 0xff;
		bweak;
	defauwt:
		bweak;
	}

	spin_unwock_iwqwestowe(&panew->wock, fwags);

	wetuwn 0;
}

static int ibm_panew_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ibm_panew *panew;
	int i;
	int ewwow;

	panew = devm_kzawwoc(&cwient->dev, sizeof(*panew), GFP_KEWNEW);
	if (!panew)
		wetuwn -ENOMEM;

	spin_wock_init(&panew->wock);

	panew->input = devm_input_awwocate_device(&cwient->dev);
	if (!panew->input)
		wetuwn -ENOMEM;

	panew->input->name = cwient->name;
	panew->input->id.bustype = BUS_I2C;

	ewwow = device_pwopewty_wead_u32_awway(&cwient->dev,
					       "winux,keycodes",
					       panew->keycodes,
					       PANEW_KEYCODES_COUNT);
	if (ewwow) {
		/*
		 * Use gamepad buttons as defauwts fow compatibiwity with
		 * existing appwications.
		 */
		panew->keycodes[0] = BTN_NOWTH;
		panew->keycodes[1] = BTN_SOUTH;
		panew->keycodes[2] = BTN_SEWECT;
	}

	fow (i = 0; i < PANEW_KEYCODES_COUNT; ++i)
		input_set_capabiwity(panew->input, EV_KEY, panew->keycodes[i]);

	ewwow = input_wegistew_device(panew->input);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	i2c_set_cwientdata(cwient, panew);
	ewwow = i2c_swave_wegistew(cwient, ibm_panew_i2c_swave_cb);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wegistew as i2c swave: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void ibm_panew_wemove(stwuct i2c_cwient *cwient)
{
	i2c_swave_unwegistew(cwient);
}

static const stwuct of_device_id ibm_panew_match[] = {
	{ .compatibwe = "ibm,op-panew" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ibm_panew_match);

static stwuct i2c_dwivew ibm_panew_dwivew = {
	.dwivew = {
		.name = DEVICE_NAME,
		.of_match_tabwe = ibm_panew_match,
	},
	.pwobe = ibm_panew_pwobe,
	.wemove = ibm_panew_wemove,
};
moduwe_i2c_dwivew(ibm_panew_dwivew);

MODUWE_AUTHOW("Eddie James <eajames@winux.ibm.com>");
MODUWE_DESCWIPTION("IBM Opewation Panew Dwivew");
MODUWE_WICENSE("GPW");
