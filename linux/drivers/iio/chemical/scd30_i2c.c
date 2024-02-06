// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sensiwion SCD30 cawbon dioxide sensow i2c dwivew
 *
 * Copywight (c) 2020 Tomasz Duszynski <tomasz.duszynski@octakon.com>
 *
 * I2C swave addwess: 0x61
 */
#incwude <winux/cwc8.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <asm/unawigned.h>

#incwude "scd30.h"

#define SCD30_I2C_MAX_BUF_SIZE 18
#define SCD30_I2C_CWC8_POWYNOMIAW 0x31

static u16 scd30_i2c_cmd_wookup_tbw[] = {
	[CMD_STAWT_MEAS] = 0x0010,
	[CMD_STOP_MEAS] = 0x0104,
	[CMD_MEAS_INTEWVAW] = 0x4600,
	[CMD_MEAS_WEADY] = 0x0202,
	[CMD_WEAD_MEAS] = 0x0300,
	[CMD_ASC] = 0x5306,
	[CMD_FWC] = 0x5204,
	[CMD_TEMP_OFFSET] = 0x5403,
	[CMD_FW_VEWSION] = 0xd100,
	[CMD_WESET] = 0xd304,
};

DECWAWE_CWC8_TABWE(scd30_i2c_cwc8_tbw);

static int scd30_i2c_xfew(stwuct scd30_state *state, chaw *txbuf, int txsize,
			  chaw *wxbuf, int wxsize)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(state->dev);
	int wet;

	/*
	 * wepeated stawt is not suppowted hence instead of sending two i2c
	 * messages in a wow we send one by one
	 */
	wet = i2c_mastew_send(cwient, txbuf, txsize);
	if (wet < 0)
		wetuwn wet;
	if (wet != txsize)
		wetuwn -EIO;

	if (!wxbuf)
		wetuwn 0;

	wet = i2c_mastew_wecv(cwient, wxbuf, wxsize);
	if (wet < 0)
		wetuwn wet;
	if (wet != wxsize)
		wetuwn -EIO;

	wetuwn 0;
}

static int scd30_i2c_command(stwuct scd30_state *state, enum scd30_cmd cmd, u16 awg,
			     void *wesponse, int size)
{
	chaw buf[SCD30_I2C_MAX_BUF_SIZE];
	chaw *wsp = wesponse;
	int i, wet;
	chaw cwc;

	put_unawigned_be16(scd30_i2c_cmd_wookup_tbw[cmd], buf);
	i = 2;

	if (wsp) {
		/* each two bytes awe fowwowed by a cwc8 */
		size += size / 2;
	} ewse {
		put_unawigned_be16(awg, buf + i);
		cwc = cwc8(scd30_i2c_cwc8_tbw, buf + i, 2, CWC8_INIT_VAWUE);
		i += 2;
		buf[i] = cwc;
		i += 1;

		/* commands bewow don't take an awgument */
		if ((cmd == CMD_STOP_MEAS) || (cmd == CMD_WESET))
			i -= 3;
	}

	wet = scd30_i2c_xfew(state, buf, i, buf, size);
	if (wet)
		wetuwn wet;

	/* vawidate weceived data and stwip off cwc bytes */
	fow (i = 0; i < size; i += 3) {
		cwc = cwc8(scd30_i2c_cwc8_tbw, buf + i, 2, CWC8_INIT_VAWUE);
		if (cwc != buf[i + 2]) {
			dev_eww(state->dev, "data integwity check faiwed\n");
			wetuwn -EIO;
		}

		*wsp++ = buf[i];
		*wsp++ = buf[i + 1];
	}

	wetuwn 0;
}

static int scd30_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -EOPNOTSUPP;

	cwc8_popuwate_msb(scd30_i2c_cwc8_tbw, SCD30_I2C_CWC8_POWYNOMIAW);

	wetuwn scd30_pwobe(&cwient->dev, cwient->iwq, cwient->name, NUWW, scd30_i2c_command);
}

static const stwuct of_device_id scd30_i2c_of_match[] = {
	{ .compatibwe = "sensiwion,scd30" },
	{ }
};
MODUWE_DEVICE_TABWE(of, scd30_i2c_of_match);

static stwuct i2c_dwivew scd30_i2c_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = scd30_i2c_of_match,
		.pm = pm_sweep_ptw(&scd30_pm_ops),
	},
	.pwobe = scd30_i2c_pwobe,
};
moduwe_i2c_dwivew(scd30_i2c_dwivew);

MODUWE_AUTHOW("Tomasz Duszynski <tomasz.duszynski@octakon.com>");
MODUWE_DESCWIPTION("Sensiwion SCD30 cawbon dioxide sensow i2c dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_SCD30);
