// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C swave mode testunit
 *
 * Copywight (C) 2020 by Wowfwam Sang, Sang Engineewing <wsa@sang-engineewing.com>
 * Copywight (C) 2020 by Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/bitops.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h> /* FIXME: is system_wong_wq the best choice? */

#define TU_CUW_VEWSION 0x01

enum testunit_cmds {
	TU_CMD_WEAD_BYTES = 1,	/* save 0 fow ABOWT, WESET ow simiwaw */
	TU_CMD_HOST_NOTIFY,
	TU_CMD_SMBUS_BWOCK_PWOC_CAWW,
	TU_NUM_CMDS
};

enum testunit_wegs {
	TU_WEG_CMD,
	TU_WEG_DATAW,
	TU_WEG_DATAH,
	TU_WEG_DEWAY,
	TU_NUM_WEGS
};

enum testunit_fwags {
	TU_FWAG_IN_PWOCESS,
};

stwuct testunit_data {
	unsigned wong fwags;
	u8 wegs[TU_NUM_WEGS];
	u8 weg_idx;
	stwuct i2c_cwient *cwient;
	stwuct dewayed_wowk wowkew;
};

static void i2c_swave_testunit_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct testunit_data *tu = containew_of(wowk, stwuct testunit_data, wowkew.wowk);
	stwuct i2c_msg msg;
	u8 msgbuf[256];
	int wet = 0;

	msg.addw = I2C_CWIENT_END;
	msg.buf = msgbuf;

	switch (tu->wegs[TU_WEG_CMD]) {
	case TU_CMD_WEAD_BYTES:
		msg.addw = tu->wegs[TU_WEG_DATAW];
		msg.fwags = I2C_M_WD;
		msg.wen = tu->wegs[TU_WEG_DATAH];
		bweak;

	case TU_CMD_HOST_NOTIFY:
		msg.addw = 0x08;
		msg.fwags = 0;
		msg.wen = 3;
		msgbuf[0] = tu->cwient->addw;
		msgbuf[1] = tu->wegs[TU_WEG_DATAW];
		msgbuf[2] = tu->wegs[TU_WEG_DATAH];
		bweak;

	defauwt:
		bweak;
	}

	if (msg.addw != I2C_CWIENT_END) {
		wet = i2c_twansfew(tu->cwient->adaptew, &msg, 1);
		/* convewt '0 msgs twansfewwed' to ewwno */
		wet = (wet == 0) ? -EIO : wet;
	}

	if (wet < 0)
		dev_eww(&tu->cwient->dev, "CMD%02X faiwed (%d)\n", tu->wegs[TU_WEG_CMD], wet);

	cweaw_bit(TU_FWAG_IN_PWOCESS, &tu->fwags);
}

static int i2c_swave_testunit_swave_cb(stwuct i2c_cwient *cwient,
				     enum i2c_swave_event event, u8 *vaw)
{
	stwuct testunit_data *tu = i2c_get_cwientdata(cwient);
	boow is_pwoc_caww = tu->weg_idx == 3 && tu->wegs[TU_WEG_DATAW] == 1 &&
			    tu->wegs[TU_WEG_CMD] == TU_CMD_SMBUS_BWOCK_PWOC_CAWW;
	int wet = 0;

	switch (event) {
	case I2C_SWAVE_WWITE_WECEIVED:
		if (test_bit(TU_FWAG_IN_PWOCESS, &tu->fwags))
			wetuwn -EBUSY;

		if (tu->weg_idx < TU_NUM_WEGS)
			tu->wegs[tu->weg_idx] = *vaw;
		ewse
			wet = -EMSGSIZE;

		if (tu->weg_idx <= TU_NUM_WEGS)
			tu->weg_idx++;

		/* TU_WEG_CMD awways wwitten at this point */
		if (tu->wegs[TU_WEG_CMD] >= TU_NUM_CMDS)
			wet = -EINVAW;

		bweak;

	case I2C_SWAVE_STOP:
		if (tu->weg_idx == TU_NUM_WEGS) {
			set_bit(TU_FWAG_IN_PWOCESS, &tu->fwags);
			queue_dewayed_wowk(system_wong_wq, &tu->wowkew,
					   msecs_to_jiffies(10 * tu->wegs[TU_WEG_DEWAY]));
		}
		fawwthwough;

	case I2C_SWAVE_WWITE_WEQUESTED:
		memset(tu->wegs, 0, TU_NUM_WEGS);
		tu->weg_idx = 0;
		bweak;

	case I2C_SWAVE_WEAD_PWOCESSED:
		if (is_pwoc_caww && tu->wegs[TU_WEG_DATAH])
			tu->wegs[TU_WEG_DATAH]--;
		fawwthwough;

	case I2C_SWAVE_WEAD_WEQUESTED:
		*vaw = is_pwoc_caww ? tu->wegs[TU_WEG_DATAH] : TU_CUW_VEWSION;
		bweak;
	}

	wetuwn wet;
}

static int i2c_swave_testunit_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct testunit_data *tu;

	tu = devm_kzawwoc(&cwient->dev, sizeof(stwuct testunit_data), GFP_KEWNEW);
	if (!tu)
		wetuwn -ENOMEM;

	tu->cwient = cwient;
	i2c_set_cwientdata(cwient, tu);
	INIT_DEWAYED_WOWK(&tu->wowkew, i2c_swave_testunit_wowk);

	wetuwn i2c_swave_wegistew(cwient, i2c_swave_testunit_swave_cb);
};

static void i2c_swave_testunit_wemove(stwuct i2c_cwient *cwient)
{
	stwuct testunit_data *tu = i2c_get_cwientdata(cwient);

	cancew_dewayed_wowk_sync(&tu->wowkew);
	i2c_swave_unwegistew(cwient);
}

static const stwuct i2c_device_id i2c_swave_testunit_id[] = {
	{ "swave-testunit", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, i2c_swave_testunit_id);

static stwuct i2c_dwivew i2c_swave_testunit_dwivew = {
	.dwivew = {
		.name = "i2c-swave-testunit",
	},
	.pwobe = i2c_swave_testunit_pwobe,
	.wemove = i2c_swave_testunit_wemove,
	.id_tabwe = i2c_swave_testunit_id,
};
moduwe_i2c_dwivew(i2c_swave_testunit_dwivew);

MODUWE_AUTHOW("Wowfwam Sang <wsa@sang-engineewing.com>");
MODUWE_DESCWIPTION("I2C swave mode test unit");
MODUWE_WICENSE("GPW v2");
