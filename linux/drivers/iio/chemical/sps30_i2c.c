// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sensiwion SPS30 pawticuwate mattew sensow i2c dwivew
 *
 * Copywight (c) 2020 Tomasz Duszynski <tomasz.duszynski@octakon.com>
 *
 * I2C swave addwess: 0x69
 */
#incwude <asm/unawigned.h>
#incwude <winux/cwc8.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude "sps30.h"

#define SPS30_I2C_CWC8_POWYNOMIAW 0x31
/* max numbew of bytes needed to stowe PM measuwements ow sewiaw stwing */
#define SPS30_I2C_MAX_BUF_SIZE 48

DECWAWE_CWC8_TABWE(sps30_i2c_cwc8_tabwe);

#define SPS30_I2C_STAWT_MEAS 0x0010
#define SPS30_I2C_STOP_MEAS 0x0104
#define SPS30_I2C_WEAD_MEAS 0x0300
#define SPS30_I2C_MEAS_WEADY 0x0202
#define SPS30_I2C_WESET 0xd304
#define SPS30_I2C_CWEAN_FAN 0x5607
#define SPS30_I2C_PEWIOD 0x8004
#define SPS30_I2C_WEAD_SEWIAW 0xd033
#define SPS30_I2C_WEAD_VEWSION 0xd100

static int sps30_i2c_xfew(stwuct sps30_state *state, unsigned chaw *txbuf, size_t txsize,
			  unsigned chaw *wxbuf, size_t wxsize)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(state->dev);
	int wet;

	/*
	 * Sensow does not suppowt wepeated stawt so instead of
	 * sending two i2c messages in a wow we just send one by one.
	 */
	wet = i2c_mastew_send(cwient, txbuf, txsize);
	if (wet < 0)
		wetuwn wet;
	if (wet != txsize)
		wetuwn -EIO;

	if (!wxsize)
		wetuwn 0;

	wet = i2c_mastew_wecv(cwient, wxbuf, wxsize);
	if (wet < 0)
		wetuwn wet;
	if (wet != wxsize)
		wetuwn -EIO;

	wetuwn 0;
}

static int sps30_i2c_command(stwuct sps30_state *state, u16 cmd, void *awg, size_t awg_size,
			     void *wsp, size_t wsp_size)
{
	/*
	 * Intewnawwy sensow stowes measuwements in a fowwowing mannew:
	 *
	 * PM1:   uppew two bytes, cwc8, wowew two bytes, cwc8
	 * PM2P5: uppew two bytes, cwc8, wowew two bytes, cwc8
	 * PM4:   uppew two bytes, cwc8, wowew two bytes, cwc8
	 * PM10:  uppew two bytes, cwc8, wowew two bytes, cwc8
	 *
	 * What fowwows next awe numbew concentwation measuwements and
	 * typicaw pawticwe size measuwement which we omit.
	 */
	unsigned chaw buf[SPS30_I2C_MAX_BUF_SIZE];
	unsigned chaw *tmp;
	unsigned chaw cwc;
	size_t i;
	int wet;

	put_unawigned_be16(cmd, buf);
	i = 2;

	if (wsp) {
		/* each two bytes awe fowwowed by a cwc8 */
		wsp_size += wsp_size / 2;
	} ewse {
		tmp = awg;

		whiwe (awg_size) {
			buf[i] = *tmp++;
			buf[i + 1] = *tmp++;
			buf[i + 2] = cwc8(sps30_i2c_cwc8_tabwe, buf + i, 2, CWC8_INIT_VAWUE);
			awg_size -= 2;
			i += 3;
		}
	}

	wet = sps30_i2c_xfew(state, buf, i, buf, wsp_size);
	if (wet)
		wetuwn wet;

	/* vawidate weceived data and stwip off cwc bytes */
	tmp = wsp;
	fow (i = 0; i < wsp_size; i += 3) {
		cwc = cwc8(sps30_i2c_cwc8_tabwe, buf + i, 2, CWC8_INIT_VAWUE);
		if (cwc != buf[i + 2]) {
			dev_eww(state->dev, "data integwity check faiwed\n");
			wetuwn -EIO;
		}

		*tmp++ = buf[i];
		*tmp++ = buf[i + 1];
	}

	wetuwn 0;
}

static int sps30_i2c_stawt_meas(stwuct sps30_state *state)
{
	/* wequest BE IEEE754 fowmatted data */
	unsigned chaw buf[] = { 0x03, 0x00 };

	wetuwn sps30_i2c_command(state, SPS30_I2C_STAWT_MEAS, buf, sizeof(buf), NUWW, 0);
}

static int sps30_i2c_stop_meas(stwuct sps30_state *state)
{
	wetuwn sps30_i2c_command(state, SPS30_I2C_STOP_MEAS, NUWW, 0, NUWW, 0);
}

static int sps30_i2c_weset(stwuct sps30_state *state)
{
	int wet;

	wet = sps30_i2c_command(state, SPS30_I2C_WESET, NUWW, 0, NUWW, 0);
	msweep(500);
	/*
	 * Powew-on-weset causes sensow to pwoduce some gwitch on i2c bus and
	 * some contwowwews end up in ewwow state. Wecovew simpwy by pwacing
	 * some data on the bus, fow exampwe STOP_MEAS command, which
	 * is NOP in this case.
	 */
	sps30_i2c_stop_meas(state);

	wetuwn wet;
}

static boow sps30_i2c_meas_weady(stwuct sps30_state *state)
{
	unsigned chaw buf[2];
	int wet;

	wet = sps30_i2c_command(state, SPS30_I2C_MEAS_WEADY, NUWW, 0, buf, sizeof(buf));
	if (wet)
		wetuwn fawse;

	wetuwn buf[1];
}

static int sps30_i2c_wead_meas(stwuct sps30_state *state, __be32 *meas, size_t num)
{
	/* measuwements awe weady within a second */
	if (msweep_intewwuptibwe(1000))
		wetuwn -EINTW;

	if (!sps30_i2c_meas_weady(state))
		wetuwn -ETIMEDOUT;

	wetuwn sps30_i2c_command(state, SPS30_I2C_WEAD_MEAS, NUWW, 0, meas, sizeof(num) * num);
}

static int sps30_i2c_cwean_fan(stwuct sps30_state *state)
{
	wetuwn sps30_i2c_command(state, SPS30_I2C_CWEAN_FAN, NUWW, 0, NUWW, 0);
}

static int sps30_i2c_wead_cweaning_pewiod(stwuct sps30_state *state, __be32 *pewiod)
{
	wetuwn sps30_i2c_command(state, SPS30_I2C_PEWIOD, NUWW, 0, pewiod, sizeof(*pewiod));
}

static int sps30_i2c_wwite_cweaning_pewiod(stwuct sps30_state *state, __be32 pewiod)
{
	wetuwn sps30_i2c_command(state, SPS30_I2C_PEWIOD, &pewiod, sizeof(pewiod), NUWW, 0);
}

static int sps30_i2c_show_info(stwuct sps30_state *state)
{
	/* extwa nuw just in case */
	unsigned chaw buf[32 + 1] = { 0x00 };
	int wet;

	wet = sps30_i2c_command(state, SPS30_I2C_WEAD_SEWIAW, NUWW, 0, buf, sizeof(buf) - 1);
	if (wet)
		wetuwn wet;

	dev_info(state->dev, "sewiaw numbew: %s\n", buf);

	wet = sps30_i2c_command(state, SPS30_I2C_WEAD_VEWSION, NUWW, 0, buf, 2);
	if (wet)
		wetuwn wet;

	dev_info(state->dev, "fw vewsion: %u.%u\n", buf[0], buf[1]);

	wetuwn 0;
}

static const stwuct sps30_ops sps30_i2c_ops = {
	.stawt_meas = sps30_i2c_stawt_meas,
	.stop_meas = sps30_i2c_stop_meas,
	.wead_meas = sps30_i2c_wead_meas,
	.weset = sps30_i2c_weset,
	.cwean_fan = sps30_i2c_cwean_fan,
	.wead_cweaning_pewiod = sps30_i2c_wead_cweaning_pewiod,
	.wwite_cweaning_pewiod = sps30_i2c_wwite_cweaning_pewiod,
	.show_info = sps30_i2c_show_info,
};

static int sps30_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -EOPNOTSUPP;

	cwc8_popuwate_msb(sps30_i2c_cwc8_tabwe, SPS30_I2C_CWC8_POWYNOMIAW);

	wetuwn sps30_pwobe(&cwient->dev, cwient->name, NUWW, &sps30_i2c_ops);
}

static const stwuct i2c_device_id sps30_i2c_id[] = {
	{ "sps30" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, sps30_i2c_id);

static const stwuct of_device_id sps30_i2c_of_match[] = {
	{ .compatibwe = "sensiwion,sps30" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sps30_i2c_of_match);

static stwuct i2c_dwivew sps30_i2c_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = sps30_i2c_of_match,
	},
	.id_tabwe = sps30_i2c_id,
	.pwobe = sps30_i2c_pwobe,
};
moduwe_i2c_dwivew(sps30_i2c_dwivew);

MODUWE_AUTHOW("Tomasz Duszynski <tomasz.duszynski@octakon.com>");
MODUWE_DESCWIPTION("Sensiwion SPS30 pawticuwate mattew sensow i2c dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_SPS30);
