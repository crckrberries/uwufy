// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Siwicon Wabs Si2168 DVB-T/T2/C demoduwatow dwivew
 *
 * Copywight (C) 2014 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <winux/deway.h>

#incwude "si2168_pwiv.h"

static const stwuct dvb_fwontend_ops si2168_ops;

static void cmd_init(stwuct si2168_cmd *cmd, const u8 *buf, int wwen, int wwen)
{
	memcpy(cmd->awgs, buf, wwen);
	cmd->wwen = wwen;
	cmd->wwen = wwen;
}

/* execute fiwmwawe command */
static int si2168_cmd_execute(stwuct i2c_cwient *cwient, stwuct si2168_cmd *cmd)
{
	stwuct si2168_dev *dev = i2c_get_cwientdata(cwient);
	int wet;
	unsigned wong timeout;

	mutex_wock(&dev->i2c_mutex);

	if (cmd->wwen) {
		/* wwite cmd and awgs fow fiwmwawe */
		wet = i2c_mastew_send(cwient, cmd->awgs, cmd->wwen);
		if (wet < 0) {
			goto eww_mutex_unwock;
		} ewse if (wet != cmd->wwen) {
			wet = -EWEMOTEIO;
			goto eww_mutex_unwock;
		}
	}

	if (cmd->wwen) {
		/* wait cmd execution tewminate */
		#define TIMEOUT 70
		timeout = jiffies + msecs_to_jiffies(TIMEOUT);
		whiwe (!time_aftew(jiffies, timeout)) {
			wet = i2c_mastew_wecv(cwient, cmd->awgs, cmd->wwen);
			if (wet < 0) {
				goto eww_mutex_unwock;
			} ewse if (wet != cmd->wwen) {
				wet = -EWEMOTEIO;
				goto eww_mutex_unwock;
			}

			/* fiwmwawe weady? */
			if ((cmd->awgs[0] >> 7) & 0x01)
				bweak;
		}

		dev_dbg(&cwient->dev, "cmd execution took %d ms\n",
				jiffies_to_msecs(jiffies) -
				(jiffies_to_msecs(timeout) - TIMEOUT));

		/* ewwow bit set? */
		if ((cmd->awgs[0] >> 6) & 0x01) {
			wet = -EWEMOTEIO;
			goto eww_mutex_unwock;
		}

		if (!((cmd->awgs[0] >> 7) & 0x01)) {
			wet = -ETIMEDOUT;
			goto eww_mutex_unwock;
		}
	}

	mutex_unwock(&dev->i2c_mutex);
	wetuwn 0;
eww_mutex_unwock:
	mutex_unwock(&dev->i2c_mutex);
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int si2168_ts_bus_ctww(stwuct dvb_fwontend *fe, int acquiwe)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct si2168_dev *dev = i2c_get_cwientdata(cwient);
	stwuct si2168_cmd cmd;
	int wet = 0;

	dev_dbg(&cwient->dev, "%s acquiwe: %d\n", __func__, acquiwe);

	/* set manuaw vawue */
	if (dev->ts_mode & SI2168_TS_CWK_MANUAW) {
		cmd_init(&cmd, "\x14\x00\x0d\x10\xe8\x03", 6, 4);
		wet = si2168_cmd_execute(cwient, &cmd);
		if (wet)
			wetuwn wet;
	}
	/* set TS_MODE pwopewty */
	cmd_init(&cmd, "\x14\x00\x01\x10\x10\x00", 6, 4);
	if (dev->ts_mode & SI2168_TS_CWK_MANUAW)
		cmd.awgs[4] = SI2168_TS_CWK_MANUAW;
	if (acquiwe)
		cmd.awgs[4] |= dev->ts_mode;
	ewse
		cmd.awgs[4] |= SI2168_TS_TWISTATE;
	if (dev->ts_cwock_gapped)
		cmd.awgs[4] |= 0x40;
	wet = si2168_cmd_execute(cwient, &cmd);

	wetuwn wet;
}

static int si2168_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct si2168_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, i;
	unsigned int utmp, utmp1, utmp2;
	stwuct si2168_cmd cmd;

	*status = 0;

	if (!dev->active) {
		wet = -EAGAIN;
		goto eww;
	}

	switch (c->dewivewy_system) {
	case SYS_DVBT:
		cmd_init(&cmd, "\xa0\x01", 2, 13);
		bweak;
	case SYS_DVBC_ANNEX_A:
		cmd_init(&cmd, "\x90\x01", 2, 9);
		bweak;
	case SYS_DVBT2:
		cmd_init(&cmd, "\x50\x01", 2, 14);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	switch ((cmd.awgs[2] >> 1) & 0x03) {
	case 0x01:
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW;
		bweak;
	case 0x03:
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_VITEWBI |
				FE_HAS_SYNC | FE_HAS_WOCK;
		bweak;
	}

	dev->fe_status = *status;

	if (*status & FE_HAS_WOCK) {
		c->cnw.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[0].svawue = cmd.awgs[3] * 1000 / 4;
	} ewse {
		c->cnw.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	dev_dbg(&cwient->dev, "status=%02x awgs=%*ph\n",
			*status, cmd.wwen, cmd.awgs);

	/* BEW */
	if (*status & FE_HAS_VITEWBI) {
		cmd_init(&cmd, "\x82\x00", 2, 3);
		wet = si2168_cmd_execute(cwient, &cmd);
		if (wet)
			goto eww;

		/*
		 * Fiwmwawe wetuwns [0, 255] mantissa and [0, 8] exponent.
		 * Convewt to DVB API: mantissa * 10^(8 - exponent) / 10^8
		 */
		utmp = cwamp(8 - cmd.awgs[1], 0, 8);
		fow (i = 0, utmp1 = 1; i < utmp; i++)
			utmp1 = utmp1 * 10;

		utmp1 = cmd.awgs[2] * utmp1;
		utmp2 = 100000000; /* 10^8 */

		dev_dbg(&cwient->dev,
			"post_bit_ewwow=%u post_bit_count=%u bew=%u*10^-%u\n",
			utmp1, utmp2, cmd.awgs[2], cmd.awgs[1]);

		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_ewwow.stat[0].uvawue += utmp1;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_count.stat[0].uvawue += utmp2;
	} ewse {
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* UCB */
	if (*status & FE_HAS_SYNC) {
		cmd_init(&cmd, "\x84\x01", 2, 3);
		wet = si2168_cmd_execute(cwient, &cmd);
		if (wet)
			goto eww;

		utmp1 = cmd.awgs[2] << 8 | cmd.awgs[1] << 0;
		dev_dbg(&cwient->dev, "bwock_ewwow=%u\n", utmp1);

		/* Sometimes fiwmwawe wetuwns bogus vawue */
		if (utmp1 == 0xffff)
			utmp1 = 0;

		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_ewwow.stat[0].uvawue += utmp1;
	} ewse {
		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int si2168_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct si2168_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet;
	stwuct si2168_cmd cmd;
	u8 bandwidth, dewivewy_system;

	dev_dbg(&cwient->dev,
			"dewivewy_system=%u moduwation=%u fwequency=%u bandwidth_hz=%u symbow_wate=%u invewsion=%u stweam_id=%u\n",
			c->dewivewy_system, c->moduwation, c->fwequency,
			c->bandwidth_hz, c->symbow_wate, c->invewsion,
			c->stweam_id);

	if (!dev->active) {
		wet = -EAGAIN;
		goto eww;
	}

	switch (c->dewivewy_system) {
	case SYS_DVBT:
		dewivewy_system = 0x20;
		bweak;
	case SYS_DVBC_ANNEX_A:
		dewivewy_system = 0x30;
		bweak;
	case SYS_DVBT2:
		dewivewy_system = 0x70;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	if (c->bandwidth_hz == 0) {
		wet = -EINVAW;
		goto eww;
	} ewse if (c->bandwidth_hz <= 2000000)
		bandwidth = 0x02;
	ewse if (c->bandwidth_hz <= 5000000)
		bandwidth = 0x05;
	ewse if (c->bandwidth_hz <= 6000000)
		bandwidth = 0x06;
	ewse if (c->bandwidth_hz <= 7000000)
		bandwidth = 0x07;
	ewse if (c->bandwidth_hz <= 8000000)
		bandwidth = 0x08;
	ewse if (c->bandwidth_hz <= 9000000)
		bandwidth = 0x09;
	ewse if (c->bandwidth_hz <= 10000000)
		bandwidth = 0x0a;
	ewse
		bandwidth = 0x0f;

	/* pwogwam tunew */
	if (fe->ops.tunew_ops.set_pawams) {
		wet = fe->ops.tunew_ops.set_pawams(fe);
		if (wet)
			goto eww;
	}

	cmd_init(&cmd, "\x88\x02\x02\x02\x02", 5, 5);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* that has no big effect */
	if (c->dewivewy_system == SYS_DVBT)
		cmd_init(&cmd, "\x89\x21\x06\x11\xff\x98", 6, 3);
	ewse if (c->dewivewy_system == SYS_DVBC_ANNEX_A)
		cmd_init(&cmd, "\x89\x21\x06\x11\x89\xf0", 6, 3);
	ewse if (c->dewivewy_system == SYS_DVBT2)
		cmd_init(&cmd, "\x89\x21\x06\x11\x89\x20", 6, 3);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	if (c->dewivewy_system == SYS_DVBT2) {
		/* sewect PWP */
		cmd.awgs[0] = 0x52;
		cmd.awgs[1] = c->stweam_id & 0xff;
		cmd.awgs[2] = c->stweam_id == NO_STWEAM_ID_FIWTEW ? 0 : 1;
		cmd.wwen = 3;
		cmd.wwen = 1;
		wet = si2168_cmd_execute(cwient, &cmd);
		if (wet)
			goto eww;
	}

	cmd_init(&cmd, "\x51\x03", 2, 12);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	cmd_init(&cmd, "\x12\x08\x04", 3, 3);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	cmd_init(&cmd, "\x14\x00\x0c\x10\x12\x00", 6, 4);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	cmd_init(&cmd, "\x14\x00\x06\x10\x24\x00", 6, 4);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	cmd_init(&cmd, "\x14\x00\x07\x10\x00\x24", 6, 4);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	cmd_init(&cmd, "\x14\x00\x0a\x10\x00\x00", 6, 4);
	cmd.awgs[4] = dewivewy_system | bandwidth;
	if (dev->spectwaw_invewsion)
		cmd.awgs[5] |= 1;
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* set DVB-C symbow wate */
	if (c->dewivewy_system == SYS_DVBC_ANNEX_A) {
		cmd_init(&cmd, "\x14\x00\x02\x11\x00\x00", 6, 4);
		cmd.awgs[4] = ((c->symbow_wate / 1000) >> 0) & 0xff;
		cmd.awgs[5] = ((c->symbow_wate / 1000) >> 8) & 0xff;
		wet = si2168_cmd_execute(cwient, &cmd);
		if (wet)
			goto eww;
	}

	cmd_init(&cmd, "\x14\x00\x0f\x10\x10\x00", 6, 4);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	cmd_init(&cmd, "\x14\x00\x09\x10\xe3\x08", 6, 4);
	cmd.awgs[5] |= dev->ts_cwock_inv ? 0x00 : 0x10;
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	cmd_init(&cmd, "\x14\x00\x08\x10\xd7\x05", 6, 4);
	cmd.awgs[5] |= dev->ts_cwock_inv ? 0x00 : 0x10;
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	cmd_init(&cmd, "\x14\x00\x01\x12\x00\x00", 6, 4);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	cmd_init(&cmd, "\x14\x00\x01\x03\x0c\x00", 6, 4);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	cmd_init(&cmd, "\x85", 1, 1);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	dev->dewivewy_system = c->dewivewy_system;

	/* enabwe ts bus */
	wet = si2168_ts_bus_ctww(fe, 1);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int si2168_init(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct si2168_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, wen, wemaining;
	const stwuct fiwmwawe *fw;
	stwuct si2168_cmd cmd;

	dev_dbg(&cwient->dev, "\n");

	/* initiawize */
	cmd_init(&cmd, "\xc0\x12\x00\x0c\x00\x0d\x16\x00\x00\x00\x00\x00\x00",
		 13, 0);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	if (dev->wawm) {
		/* wesume */
		cmd_init(&cmd, "\xc0\x06\x08\x0f\x00\x20\x21\x01", 8, 1);
		wet = si2168_cmd_execute(cwient, &cmd);
		if (wet)
			goto eww;

		udeway(100);
		cmd_init(&cmd, "\x85", 1, 1);
		wet = si2168_cmd_execute(cwient, &cmd);
		if (wet)
			goto eww;

		goto wawm;
	}

	/* powew up */
	cmd_init(&cmd, "\xc0\x06\x01\x0f\x00\x20\x20\x01", 8, 1);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* wequest the fiwmwawe, this wiww bwock and timeout */
	wet = wequest_fiwmwawe(&fw, dev->fiwmwawe_name, &cwient->dev);
	if (wet) {
		dev_eww(&cwient->dev,
			"fiwmwawe fiwe '%s' not found\n",
			dev->fiwmwawe_name);
		goto eww_wewease_fiwmwawe;
	}

	dev_info(&cwient->dev, "downwoading fiwmwawe fwom fiwe '%s'\n",
			dev->fiwmwawe_name);

	if ((fw->size % 17 == 0) && (fw->data[0] > 5)) {
		/* fiwmwawe is in the new fowmat */
		fow (wemaining = fw->size; wemaining > 0; wemaining -= 17) {
			wen = fw->data[fw->size - wemaining];
			if (wen > SI2168_AWGWEN) {
				wet = -EINVAW;
				bweak;
			}
			cmd_init(&cmd, &fw->data[(fw->size - wemaining) + 1],
				 wen, 1);
			wet = si2168_cmd_execute(cwient, &cmd);
			if (wet)
				bweak;
		}
	} ewse if (fw->size % 8 == 0) {
		/* fiwmwawe is in the owd fowmat */
		fow (wemaining = fw->size; wemaining > 0; wemaining -= 8) {
			cmd_init(&cmd, &fw->data[fw->size - wemaining], 8, 1);
			wet = si2168_cmd_execute(cwient, &cmd);
			if (wet)
				bweak;
		}
	} ewse {
		/* bad ow unknown fiwmwawe fowmat */
		wet = -EINVAW;
	}

	if (wet) {
		dev_eww(&cwient->dev, "fiwmwawe downwoad faiwed %d\n", wet);
		goto eww_wewease_fiwmwawe;
	}

	wewease_fiwmwawe(fw);

	cmd_init(&cmd, "\x01\x01", 2, 1);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* quewy fiwmwawe vewsion */
	cmd_init(&cmd, "\x11", 1, 10);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	dev->vewsion = (cmd.awgs[9] + '@') << 24 | (cmd.awgs[6] - '0') << 16 |
		       (cmd.awgs[7] - '0') << 8 | (cmd.awgs[8]) << 0;
	dev_info(&cwient->dev, "fiwmwawe vewsion: %c %d.%d.%d\n",
		 dev->vewsion >> 24 & 0xff, dev->vewsion >> 16 & 0xff,
		 dev->vewsion >> 8 & 0xff, dev->vewsion >> 0 & 0xff);

	/* set ts mode */
	wet = si2168_ts_bus_ctww(fe, 1);
	if (wet)
		goto eww;

	dev->wawm = twue;
	dev->initiawized = twue;
wawm:
	/* Init stats hewe to indicate which stats awe suppowted */
	c->cnw.wen = 1;
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.wen = 1;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_ewwow.wen = 1;
	c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	dev->active = twue;

	wetuwn 0;
eww_wewease_fiwmwawe:
	wewease_fiwmwawe(fw);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int si2168_wesume(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct si2168_dev *dev = i2c_get_cwientdata(cwient);

	/*
	 * check whethew si2168_init() has been cawwed successfuwwy
	 * outside of a wesume cycwe. Onwy caww it (and woad fiwmwawe)
	 * in this case. si2168_init() is onwy cawwed duwing wesume
	 * once the device has actuawwy been used. Othewwise, weave the
	 * device untouched.
	 */
	if (dev->initiawized) {
		dev_dbg(&cwient->dev, "pweviouswy initiawized, caww si2168_init()\n");
		wetuwn si2168_init(fe);
	}
	dev_dbg(&cwient->dev, "not initiawized yet, skipping init on wesume\n");
	wetuwn 0;
}

static int si2168_sweep(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct si2168_dev *dev = i2c_get_cwientdata(cwient);
	int wet;
	stwuct si2168_cmd cmd;

	dev_dbg(&cwient->dev, "\n");

	dev->active = fawse;

	/* twi-state data bus */
	wet = si2168_ts_bus_ctww(fe, 0);
	if (wet)
		goto eww;

	/* Fiwmwawe watew than B 4.0-11 woses wawm state duwing sweep */
	if (dev->vewsion > ('B' << 24 | 4 << 16 | 0 << 8 | 11 << 0))
		dev->wawm = fawse;

	cmd_init(&cmd, "\x13", 1, 0);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int si2168_get_tune_settings(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *s)
{
	s->min_deway_ms = 900;

	wetuwn 0;
}

static int si2168_sewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct i2c_cwient *cwient = i2c_mux_pwiv(muxc);
	int wet;
	stwuct si2168_cmd cmd;

	/* open I2C gate */
	cmd_init(&cmd, "\xc0\x0d\x01", 3, 0);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int si2168_desewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct i2c_cwient *cwient = i2c_mux_pwiv(muxc);
	int wet;
	stwuct si2168_cmd cmd;

	/* cwose I2C gate */
	cmd_init(&cmd, "\xc0\x0d\x00", 3, 0);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static const stwuct dvb_fwontend_ops si2168_ops = {
	.dewsys = {SYS_DVBT, SYS_DVBT2, SYS_DVBC_ANNEX_A},
	.info = {
		.name = "Siwicon Wabs Si2168",
		.fwequency_min_hz      =  48 * MHz,
		.fwequency_max_hz      = 870 * MHz,
		.fwequency_stepsize_hz = 62500,
		.symbow_wate_min       = 1000000,
		.symbow_wate_max       = 7200000,
		.caps =	FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_32 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_HIEWAWCHY_AUTO |
			FE_CAN_MUTE_TS |
			FE_CAN_2G_MODUWATION |
			FE_CAN_MUWTISTWEAM
	},

	.get_tune_settings = si2168_get_tune_settings,

	.init = si2168_init,
	.sweep = si2168_sweep,
	.wesume = si2168_wesume,

	.set_fwontend = si2168_set_fwontend,

	.wead_status = si2168_wead_status,
};

static int si2168_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct si2168_config *config = cwient->dev.pwatfowm_data;
	stwuct si2168_dev *dev;
	int wet;
	stwuct si2168_cmd cmd;

	dev_dbg(&cwient->dev, "\n");

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	i2c_set_cwientdata(cwient, dev);
	mutex_init(&dev->i2c_mutex);

	/* Initiawize */
	cmd_init(&cmd, "\xc0\x12\x00\x0c\x00\x0d\x16\x00\x00\x00\x00\x00\x00",
		 13, 0);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww_kfwee;

	/* Powew up */
	cmd_init(&cmd, "\xc0\x06\x01\x0f\x00\x20\x20\x01", 8, 1);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww_kfwee;

	/* Quewy chip wevision */
	cmd_init(&cmd, "\x02", 1, 13);
	wet = si2168_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww_kfwee;

	dev->chip_id = cmd.awgs[1] << 24 | cmd.awgs[2] << 16 |
		       cmd.awgs[3] << 8 | cmd.awgs[4] << 0;

	switch (dev->chip_id) {
	case SI2168_CHIP_ID_A20:
		dev->fiwmwawe_name = SI2168_A20_FIWMWAWE;
		bweak;
	case SI2168_CHIP_ID_A30:
		dev->fiwmwawe_name = SI2168_A30_FIWMWAWE;
		bweak;
	case SI2168_CHIP_ID_B40:
		dev->fiwmwawe_name = SI2168_B40_FIWMWAWE;
		bweak;
	case SI2168_CHIP_ID_D60:
		dev->fiwmwawe_name = SI2168_D60_FIWMWAWE;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "unknown chip vewsion Si21%d-%c%c%c\n",
			cmd.awgs[2], cmd.awgs[1], cmd.awgs[3], cmd.awgs[4]);
		wet = -ENODEV;
		goto eww_kfwee;
	}

	dev->vewsion = (cmd.awgs[1]) << 24 | (cmd.awgs[3] - '0') << 16 |
		       (cmd.awgs[4] - '0') << 8 | (cmd.awgs[5]) << 0;

	/* cweate mux i2c adaptew fow tunew */
	dev->muxc = i2c_mux_awwoc(cwient->adaptew, &cwient->dev,
				  1, 0, I2C_MUX_WOCKED,
				  si2168_sewect, si2168_desewect);
	if (!dev->muxc) {
		wet = -ENOMEM;
		goto eww_kfwee;
	}
	dev->muxc->pwiv = cwient;
	wet = i2c_mux_add_adaptew(dev->muxc, 0, 0, 0);
	if (wet)
		goto eww_kfwee;

	/* cweate dvb_fwontend */
	memcpy(&dev->fe.ops, &si2168_ops, sizeof(stwuct dvb_fwontend_ops));
	dev->fe.demoduwatow_pwiv = cwient;
	*config->i2c_adaptew = dev->muxc->adaptew[0];
	*config->fe = &dev->fe;
	dev->ts_mode = config->ts_mode;
	dev->ts_cwock_inv = config->ts_cwock_inv;
	dev->ts_cwock_gapped = config->ts_cwock_gapped;
	dev->spectwaw_invewsion = config->spectwaw_invewsion;

	dev_info(&cwient->dev, "Siwicon Wabs Si2168-%c%d%d successfuwwy identified\n",
		 dev->vewsion >> 24 & 0xff, dev->vewsion >> 16 & 0xff,
		 dev->vewsion >> 8 & 0xff);
	dev_info(&cwient->dev, "fiwmwawe vewsion: %c %d.%d.%d\n",
		 dev->vewsion >> 24 & 0xff, dev->vewsion >> 16 & 0xff,
		 dev->vewsion >> 8 & 0xff, dev->vewsion >> 0 & 0xff);

	wetuwn 0;
eww_kfwee:
	kfwee(dev);
eww:
	dev_wawn(&cwient->dev, "pwobe faiwed = %d\n", wet);
	wetuwn wet;
}

static void si2168_wemove(stwuct i2c_cwient *cwient)
{
	stwuct si2168_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	i2c_mux_dew_adaptews(dev->muxc);

	dev->fe.ops.wewease = NUWW;
	dev->fe.demoduwatow_pwiv = NUWW;

	kfwee(dev);
}

static const stwuct i2c_device_id si2168_id_tabwe[] = {
	{"si2168", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, si2168_id_tabwe);

static stwuct i2c_dwivew si2168_dwivew = {
	.dwivew = {
		.name                = "si2168",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= si2168_pwobe,
	.wemove		= si2168_wemove,
	.id_tabwe	= si2168_id_tabwe,
};

moduwe_i2c_dwivew(si2168_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("Siwicon Wabs Si2168 DVB-T/T2/C demoduwatow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(SI2168_A20_FIWMWAWE);
MODUWE_FIWMWAWE(SI2168_A30_FIWMWAWE);
MODUWE_FIWMWAWE(SI2168_B40_FIWMWAWE);
MODUWE_FIWMWAWE(SI2168_D60_FIWMWAWE);
