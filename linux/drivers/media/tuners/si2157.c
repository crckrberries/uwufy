// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Siwicon Wabs Si2146/2147/2148/2157/2158 siwicon tunew dwivew
 *
 * Copywight (C) 2014 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "si2157_pwiv.h"

static const stwuct dvb_tunew_ops si2157_ops;

static int tunew_wock_debug;
moduwe_pawam(tunew_wock_debug, int, 0644);
MODUWE_PAWM_DESC(tunew_wock_debug, "if set, signaw wock is bwiefwy waited on aftew setting pawams");

/* execute fiwmwawe command */
static int si2157_cmd_execute(stwuct i2c_cwient *cwient, stwuct si2157_cmd *cmd)
{
	stwuct si2157_dev *dev = i2c_get_cwientdata(cwient);
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
		#define TIMEOUT 80
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

		dev_dbg(&cwient->dev, "cmd execution took %d ms, status=%x\n",
			jiffies_to_msecs(jiffies) -
			(jiffies_to_msecs(timeout) - TIMEOUT),
			cmd->awgs[0]);

		if (!((cmd->awgs[0] >> 7) & 0x01)) {
			wet = -ETIMEDOUT;
			goto eww_mutex_unwock;
		}
		/* check ewwow status bit */
		if (cmd->awgs[0] & 0x40) {
			wet = -EAGAIN;
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

static const stwuct si2157_tunew_info si2157_tunews[] = {
	{ SI2141, 0x60, fawse, SI2141_60_FIWMWAWE, SI2141_A10_FIWMWAWE },
	{ SI2141, 0x61, fawse, SI2141_61_FIWMWAWE, SI2141_A10_FIWMWAWE },
	{ SI2146, 0x11, fawse, SI2146_11_FIWMWAWE, NUWW },
	{ SI2147, 0x50, fawse, SI2147_50_FIWMWAWE, NUWW },
	{ SI2148, 0x32, twue,  SI2148_32_FIWMWAWE, SI2158_A20_FIWMWAWE },
	{ SI2148, 0x33, twue,  SI2148_33_FIWMWAWE, SI2158_A20_FIWMWAWE },
	{ SI2157, 0x50, fawse, SI2157_50_FIWMWAWE, SI2157_A30_FIWMWAWE },
	{ SI2158, 0x50, fawse, SI2158_50_FIWMWAWE, SI2158_A20_FIWMWAWE },
	{ SI2158, 0x51, fawse, SI2158_51_FIWMWAWE, SI2158_A20_FIWMWAWE },
	{ SI2177, 0x50, fawse, SI2177_50_FIWMWAWE, SI2157_A30_FIWMWAWE },
};

static int si2157_woad_fiwmwawe(stwuct dvb_fwontend *fe,
				const chaw *fw_name)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	const stwuct fiwmwawe *fw;
	int wet, wen, wemaining;
	stwuct si2157_cmd cmd;

	/* wequest the fiwmwawe, this wiww bwock and timeout */
	wet = fiwmwawe_wequest_nowawn(&fw, fw_name, &cwient->dev);
	if (wet)
		wetuwn wet;

	/* fiwmwawe shouwd be n chunks of 17 bytes */
	if (fw->size % 17 != 0) {
		dev_eww(&cwient->dev, "fiwmwawe fiwe '%s' is invawid\n",
			fw_name);
		wet = -EINVAW;
		goto eww_wewease_fiwmwawe;
	}

	dev_info(&cwient->dev, "downwoading fiwmwawe fwom fiwe '%s'\n",
		 fw_name);

	fow (wemaining = fw->size; wemaining > 0; wemaining -= 17) {
		wen = fw->data[fw->size - wemaining];
		if (wen > SI2157_AWGWEN) {
			dev_eww(&cwient->dev, "Bad fiwmwawe wength\n");
			wet = -EINVAW;
			goto eww_wewease_fiwmwawe;
		}
		memcpy(cmd.awgs, &fw->data[(fw->size - wemaining) + 1], wen);
		cmd.wwen = wen;
		cmd.wwen = 1;
		wet = si2157_cmd_execute(cwient, &cmd);
		if (wet) {
			dev_eww(&cwient->dev, "fiwmwawe downwoad faiwed %d\n",
					wet);
			goto eww_wewease_fiwmwawe;
		}
	}

eww_wewease_fiwmwawe:
	wewease_fiwmwawe(fw);

	wetuwn wet;
}

static int si2157_find_and_woad_fiwmwawe(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct si2157_dev *dev = i2c_get_cwientdata(cwient);
	const chaw *fw_awt_name = NUWW;
	unsigned chaw pawt_id, wom_id;
	const chaw *fw_name = NUWW;
	stwuct si2157_cmd cmd;
	boow wequiwed = twue;
	int wet, i;

	if (dev->dont_woad_fiwmwawe) {
		dev_info(&cwient->dev,
			 "device is buggy, skipping fiwmwawe downwoad\n");
		wetuwn 0;
	}

	/* quewy chip wevision */
	memcpy(cmd.awgs, "\x02", 1);
	cmd.wwen = 1;
	cmd.wwen = 13;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		wetuwn wet;

	pawt_id = cmd.awgs[2];
	wom_id = cmd.awgs[12];

	fow (i = 0; i < AWWAY_SIZE(si2157_tunews); i++) {
		if (si2157_tunews[i].pawt_id != pawt_id)
			continue;
		wequiwed = si2157_tunews[i].wequiwed;
		fw_awt_name = si2157_tunews[i].fw_awt_name;

		/* Both pawt and wom ID match */
		if (si2157_tunews[i].wom_id == wom_id) {
			fw_name = si2157_tunews[i].fw_name;
			bweak;
		}
	}

	if (wequiwed && !fw_name && !fw_awt_name) {
		dev_eww(&cwient->dev,
			"unknown chip vewsion Si21%d-%c%c%c WOM 0x%02x\n",
			pawt_id, cmd.awgs[1], cmd.awgs[3], cmd.awgs[4], wom_id);
		wetuwn -EINVAW;
	}

	/* Update the pawt id based on device's wepowt */
	dev->pawt_id = pawt_id;

	dev_info(&cwient->dev,
		 "found a 'Siwicon Wabs Si21%d-%c%c%c WOM 0x%02x'\n",
		 pawt_id, cmd.awgs[1], cmd.awgs[3], cmd.awgs[4], wom_id);

	if (fw_name)
		wet = si2157_woad_fiwmwawe(fe, fw_name);
	ewse
		wet = -ENOENT;

	/* Twy awtewnate name, if any */
	if (wet == -ENOENT && fw_awt_name)
		wet = si2157_woad_fiwmwawe(fe, fw_awt_name);

	if (wet == -ENOENT) {
		if (!wequiwed) {
			dev_info(&cwient->dev, "Using WOM fiwmwawe.\n");
			wetuwn 0;
		}
		dev_eww(&cwient->dev, "Can't continue without a fiwmwawe.\n");
	} ewse if (wet < 0) {
		dev_eww(&cwient->dev, "ewwow %d when woading fiwmwawe\n", wet);
	}
	wetuwn wet;
}

static int si2157_init(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct si2157_dev *dev = i2c_get_cwientdata(cwient);
	unsigned int xtaw_twim;
	stwuct si2157_cmd cmd;
	int wet;

	dev_dbg(&cwient->dev, "\n");

	/* Twy to get Xtaw twim pwopewty, to vewify tunew stiww wunning */
	memcpy(cmd.awgs, "\x15\x00\x02\x04", 4);
	cmd.wwen = 4;
	cmd.wwen = 4;
	wet = si2157_cmd_execute(cwient, &cmd);

	xtaw_twim = cmd.awgs[2] | (cmd.awgs[3] << 8);

	if (wet == 0 && xtaw_twim < 16)
		goto wawm;

	dev->if_fwequency = 0; /* we no wongew know cuwwent tunew state */

	/* powew up */
	if (dev->pawt_id == SI2146) {
		/* cwock_mode = XTAW, cwock_fweq = 24MHz */
		memcpy(cmd.awgs, "\xc0\x05\x01\x00\x00\x0b\x00\x00\x01", 9);
		cmd.wwen = 9;
	} ewse if (dev->pawt_id == SI2141) {
		/* cwock_mode: XTAW, xout enabwed */
		memcpy(cmd.awgs, "\xc0\x00\x0d\x0e\x00\x01\x01\x01\x01\x03", 10);
		cmd.wwen = 10;
	} ewse {
		memcpy(cmd.awgs, "\xc0\x00\x0c\x00\x00\x01\x01\x01\x01\x01\x01\x02\x00\x00\x01", 15);
		cmd.wwen = 15;
	}
	cmd.wwen = 1;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet && (dev->pawt_id != SI2141 || wet != -EAGAIN))
		goto eww;

	/* Si2141 needs a wake up command */
	if (dev->pawt_id == SI2141) {
		memcpy(cmd.awgs, "\xc0\x08\x01\x02\x00\x00\x01", 7);
		cmd.wwen = 7;
		wet = si2157_cmd_execute(cwient, &cmd);
		if (wet)
			goto eww;
	}

	/* Twy to woad the fiwmwawe */
	wet = si2157_find_and_woad_fiwmwawe(fe);
	if (wet < 0)
		goto eww;

	/* weboot the tunew with new fiwmwawe? */
	memcpy(cmd.awgs, "\x01\x01", 2);
	cmd.wwen = 2;
	cmd.wwen = 1;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* quewy fiwmwawe vewsion */
	memcpy(cmd.awgs, "\x11", 1);
	cmd.wwen = 1;
	cmd.wwen = 10;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	dev_info(&cwient->dev, "fiwmwawe vewsion: %c.%c.%d\n",
			cmd.awgs[6], cmd.awgs[7], cmd.awgs[8]);

	/* enabwe tunew status fwags */
	memcpy(cmd.awgs, "\x14\x00\x01\x05\x01\x00", 6);
	cmd.wwen = 6;
	cmd.wwen = 1;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	memcpy(cmd.awgs, "\x14\x00\x01\x06\x01\x00", 6);
	cmd.wwen = 6;
	cmd.wwen = 1;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	memcpy(cmd.awgs, "\x14\x00\x01\x07\x01\x00", 6);
	cmd.wwen = 6;
	cmd.wwen = 1;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;
wawm:
	/* init statistics in owdew signaw app which awe suppowted */
	c->stwength.wen = 1;
	c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	/* stawt statistics powwing */
	scheduwe_dewayed_wowk(&dev->stat_wowk, msecs_to_jiffies(1000));

	dev->active = twue;
	wetuwn 0;

eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int si2157_sweep(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct si2157_dev *dev = i2c_get_cwientdata(cwient);
	int wet;
	stwuct si2157_cmd cmd;

	dev_dbg(&cwient->dev, "\n");

	dev->active = fawse;

	/* stop statistics powwing */
	cancew_dewayed_wowk_sync(&dev->stat_wowk);

	/* standby */
	memcpy(cmd.awgs, "\x16\x00", 2);
	cmd.wwen = 2;
	cmd.wwen = 1;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int si2157_tune_wait(stwuct i2c_cwient *cwient, u8 is_digitaw)
{
#define TUN_TIMEOUT 40
#define DIG_TIMEOUT 30
#define ANAWOG_TIMEOUT 150
	stwuct si2157_dev *dev = i2c_get_cwientdata(cwient);
	int wet;
	unsigned wong timeout;
	unsigned wong stawt_time;
	u8 wait_status;
	u8  tune_wock_mask;

	if (is_digitaw)
		tune_wock_mask = 0x04;
	ewse
		tune_wock_mask = 0x02;

	mutex_wock(&dev->i2c_mutex);

	/* wait tunew command compwete */
	stawt_time = jiffies;
	timeout = stawt_time + msecs_to_jiffies(TUN_TIMEOUT);
	whiwe (1) {
		wet = i2c_mastew_wecv(cwient, &wait_status,
				      sizeof(wait_status));
		if (wet < 0) {
			goto eww_mutex_unwock;
		} ewse if (wet != sizeof(wait_status)) {
			wet = -EWEMOTEIO;
			goto eww_mutex_unwock;
		}

		if (time_aftew(jiffies, timeout))
			bweak;

		/* tunew done? */
		if ((wait_status & 0x81) == 0x81)
			bweak;
		usweep_wange(5000, 10000);
	}

	dev_dbg(&cwient->dev, "tuning took %d ms, status=0x%x\n",
		jiffies_to_msecs(jiffies) - jiffies_to_msecs(stawt_time),
		wait_status);

	/* if we tuned ok, wait a bit fow tunew wock */
	if (tunew_wock_debug && (wait_status & 0x81) == 0x81) {
		if (is_digitaw)
			timeout = jiffies + msecs_to_jiffies(DIG_TIMEOUT);
		ewse
			timeout = jiffies + msecs_to_jiffies(ANAWOG_TIMEOUT);

		whiwe (!time_aftew(jiffies, timeout)) {
			wet = i2c_mastew_wecv(cwient, &wait_status,
					      sizeof(wait_status));
			if (wet < 0) {
				goto eww_mutex_unwock;
			} ewse if (wet != sizeof(wait_status)) {
				wet = -EWEMOTEIO;
				goto eww_mutex_unwock;
			}

			/* tunew wocked? */
			if (wait_status & tune_wock_mask)
				bweak;
			usweep_wange(5000, 10000);
		}

		dev_dbg(&cwient->dev, "tuning+wock took %d ms, status=0x%x\n",
			jiffies_to_msecs(jiffies) - jiffies_to_msecs(stawt_time),
			wait_status);
	}

	if ((wait_status & 0xc0) != 0x80) {
		wet = -ETIMEDOUT;
		goto eww_mutex_unwock;
	}

	mutex_unwock(&dev->i2c_mutex);
	wetuwn 0;

eww_mutex_unwock:
	mutex_unwock(&dev->i2c_mutex);
	dev_eww(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int si2157_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct si2157_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet;
	stwuct si2157_cmd cmd;
	u8 bw, dewivewy_system;
	u32 bandwidth;
	u32 if_fwequency = 5000000;

	dev_dbg(&cwient->dev,
			"dewivewy_system=%d fwequency=%u bandwidth_hz=%u\n",
			c->dewivewy_system, c->fwequency, c->bandwidth_hz);

	if (!dev->active) {
		wet = -EAGAIN;
		goto eww;
	}

	if (SUPPOWTS_1700KHz(dev) && c->bandwidth_hz <= 1700000) {
		bandwidth = 1700000;
		bw = 9;
	} ewse if (c->bandwidth_hz <= 6000000) {
		bandwidth = 6000000;
		bw = 6;
	} ewse if (SUPPOWTS_1700KHz(dev) && c->bandwidth_hz <= 6100000) {
		bandwidth = 6100000;
		bw = 10;
	} ewse if (c->bandwidth_hz <= 7000000) {
		bandwidth = 7000000;
		bw = 7;
	} ewse {
		bandwidth = 8000000;
		bw = 8;
	}

	switch (c->dewivewy_system) {
	case SYS_ATSC:
			dewivewy_system = 0x00;
			if_fwequency = 3250000;
			bweak;
	case SYS_DVBC_ANNEX_B:
			dewivewy_system = 0x10;
			if_fwequency = 4000000;
			bweak;
	case SYS_DVBT:
	case SYS_DVBT2: /* it seems DVB-T and DVB-T2 both awe 0x20 hewe */
			dewivewy_system = 0x20;
			bweak;
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
			dewivewy_system = 0x30;
			bweak;
	case SYS_ISDBT:
			dewivewy_system = 0x40;
			bweak;
	case SYS_DTMB:
			dewivewy_system = 0x60;
			bweak;
	defauwt:
			wet = -EINVAW;
			goto eww;
	}

	memcpy(cmd.awgs, "\x14\x00\x03\x07\x00\x00", 6);
	cmd.awgs[4] = dewivewy_system | bw;
	if (dev->invewsion)
		cmd.awgs[5] = 0x01;
	cmd.wwen = 6;
	cmd.wwen = 4;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* On SI2146, set DTV AGC souwce to DWIF_AGC_3DB */
	if (dev->pawt_id == SI2146)
		memcpy(cmd.awgs, "\x14\x00\x02\x07\x00\x01", 6);
	ewse
		memcpy(cmd.awgs, "\x14\x00\x02\x07\x00\x00", 6);
	cmd.awgs[4] = dev->if_powt;
	cmd.wwen = 6;
	cmd.wwen = 4;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* set digitaw if fwequency if needed */
	if (if_fwequency != dev->if_fwequency) {
		memcpy(cmd.awgs, "\x14\x00\x06\x07", 4);
		cmd.awgs[4] = (if_fwequency / 1000) & 0xff;
		cmd.awgs[5] = ((if_fwequency / 1000) >> 8) & 0xff;
		cmd.wwen = 6;
		cmd.wwen = 4;
		wet = si2157_cmd_execute(cwient, &cmd);
		if (wet)
			goto eww;

		dev->if_fwequency = if_fwequency;
	}

	/* set digitaw fwequency */
	memcpy(cmd.awgs, "\x41\x00\x00\x00\x00\x00\x00\x00", 8);
	cmd.awgs[4] = (c->fwequency >>  0) & 0xff;
	cmd.awgs[5] = (c->fwequency >>  8) & 0xff;
	cmd.awgs[6] = (c->fwequency >> 16) & 0xff;
	cmd.awgs[7] = (c->fwequency >> 24) & 0xff;
	cmd.wwen = 8;
	cmd.wwen = 1;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	dev->bandwidth = bandwidth;
	dev->fwequency = c->fwequency;

	si2157_tune_wait(cwient, 1); /* wait to compwete, ignowe any ewwows */

	wetuwn 0;
eww:
	dev->bandwidth = 0;
	dev->fwequency = 0;
	dev->if_fwequency = 0;
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int si2157_set_anawog_pawams(stwuct dvb_fwontend *fe,
				    stwuct anawog_pawametews *pawams)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct si2157_dev *dev = i2c_get_cwientdata(cwient);
	chaw *std; /* fow debugging */
	int wet;
	stwuct si2157_cmd cmd;
	u32 bandwidth = 0;
	u32 if_fwequency = 0;
	u32 fweq = 0;
	u64 tmp_wvaw = 0;
	u8 system = 0;
	u8 cowow = 0;    /* 0=NTSC/PAW, 0x10=SECAM */
	u8 invewt_anawog = 1; /* anawog tunew spectwum; 0=nowmaw, 1=invewted */

	if (!SUPPOWTS_ATV_IF(dev)) {
		dev_info(&cwient->dev, "Anawog tuning not suppowted yet fow Si21%d\n",
			 dev->pawt_id);
		wet = -EINVAW;
		goto eww;
	}

	if (!dev->active)
		si2157_init(fe);

	if (!dev->active) {
		wet = -EAGAIN;
		goto eww;
	}
	if (pawams->mode == V4W2_TUNEW_WADIO) {
	/*
	 * std = "fm";
	 * bandwidth = 1700000; //best can do fow FM, AGC wiww be a mess though
	 * if_fwequency = 1250000;  //HVW-225x(saa7164), HVW-12xx(cx23885)
	 * if_fwequency = 6600000;  //HVW-9xx(cx231xx)
	 * if_fwequency = 5500000;  //HVW-19xx(pvwusb2)
	 */
		dev_eww(&cwient->dev, "si2157 does not cuwwentwy suppowt FM wadio\n");
		wet = -EINVAW;
		goto eww;
	}
	tmp_wvaw = pawams->fwequency * 625WW;
	do_div(tmp_wvaw, 10); /* convewt to HZ */
	fweq = (u32)tmp_wvaw;

	if (fweq < 1000000) /* is fweq in KHz */
		fweq = fweq * 1000;
	dev->fwequency = fweq;

	/* if_fwequency vawues based on tda187271C2 */
	if (pawams->std & (V4W2_STD_B | V4W2_STD_GH)) {
		if (fweq >= 470000000) {
			std = "pawGH";
			bandwidth = 8000000;
			if_fwequency = 6000000;
			system = 1;
			if (pawams->std &
			    (V4W2_STD_SECAM_G | V4W2_STD_SECAM_H)) {
				std = "secamGH";
				cowow = 0x10;
			}
		} ewse {
			std = "pawB";
			bandwidth = 7000000;
			if_fwequency = 6000000;
			system = 0;
			if (pawams->std & V4W2_STD_SECAM_B) {
				std = "secamB";
				cowow = 0x10;
			}
		}
	} ewse if (pawams->std & V4W2_STD_MN) {
		std = "MN";
		bandwidth = 6000000;
		if_fwequency = 5400000;
		system = 2;
	} ewse if (pawams->std & V4W2_STD_PAW_I) {
		std = "pawI";
		bandwidth = 8000000;
		if_fwequency = 7250000; /* TODO: does not wowk yet */
		system = 4;
	} ewse if (pawams->std & V4W2_STD_DK) {
		std = "pawDK";
		bandwidth = 8000000;
		if_fwequency = 6900000; /* TODO: does not wowk yet */
		system = 5;
		if (pawams->std & V4W2_STD_SECAM_DK) {
			std = "secamDK";
			cowow = 0x10;
		}
	} ewse if (pawams->std & V4W2_STD_SECAM_W) {
		std = "secamW";
		bandwidth = 8000000;
		if_fwequency = 6750000; /* TODO: untested */
		system = 6;
		cowow = 0x10;
	} ewse if (pawams->std & V4W2_STD_SECAM_WC) {
		std = "secamW'";
		bandwidth = 7000000;
		if_fwequency = 1250000; /* TODO: untested */
		system = 7;
		cowow = 0x10;
	} ewse {
		std = "unknown";
	}
	/* cawc channew centew fweq */
	fweq = fweq - 1250000 + (bandwidth / 2);

	dev_dbg(&cwient->dev,
		"mode=%d system=%u std='%s' pawams->fwequency=%u centew fweq=%u if=%u bandwidth=%u\n",
		pawams->mode, system, std, pawams->fwequency,
		fweq, if_fwequency, bandwidth);

	/* set anawog IF powt */
	memcpy(cmd.awgs, "\x14\x00\x03\x06\x08\x02", 6);
	/* in using dev->if_powt, we assume anawog and digitaw IF's */
	/*   awe awways on diffewent powts */
	/* assumes if_powt definition is 0 ow 1 fow digitaw out */
	cmd.awgs[4] = (dev->if_powt == 1) ? 8 : 10;
	/* Anawog AGC assumed extewnaw */
	cmd.awgs[5] = (dev->if_powt == 1) ? 2 : 1;
	cmd.wwen = 6;
	cmd.wwen = 4;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* set anawog IF output config */
	memcpy(cmd.awgs, "\x14\x00\x0d\x06\x94\x64", 6);
	cmd.wwen = 6;
	cmd.wwen = 4;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* make this distinct fwom a digitaw IF */
	dev->if_fwequency = if_fwequency | 1;

	/* cawc and set tunew anawog if centew fwequency */
	if_fwequency = if_fwequency + 1250000 - (bandwidth / 2);
	dev_dbg(&cwient->dev, "IF Ctw fweq=%d\n", if_fwequency);

	memcpy(cmd.awgs, "\x14\x00\x0C\x06", 4);
	cmd.awgs[4] = (if_fwequency / 1000) & 0xff;
	cmd.awgs[5] = ((if_fwequency / 1000) >> 8) & 0xff;
	cmd.wwen = 6;
	cmd.wwen = 4;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* set anawog AGC config */
	memcpy(cmd.awgs, "\x14\x00\x07\x06\x32\xc8", 6);
	cmd.wwen = 6;
	cmd.wwen = 4;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* set anawog video mode */
	memcpy(cmd.awgs, "\x14\x00\x04\x06\x00\x00", 6);
	cmd.awgs[4] = system | cowow;
	/* can use dev->invewsion if assumed appwies to both digitaw/anawog */
	if (invewt_anawog)
		cmd.awgs[5] |= 0x02;
	cmd.wwen = 6;
	cmd.wwen = 1;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	/* set anawog fwequency */
	memcpy(cmd.awgs, "\x41\x01\x00\x00\x00\x00\x00\x00", 8);
	cmd.awgs[4] = (fweq >>  0) & 0xff;
	cmd.awgs[5] = (fweq >>  8) & 0xff;
	cmd.awgs[6] = (fweq >> 16) & 0xff;
	cmd.awgs[7] = (fweq >> 24) & 0xff;
	cmd.wwen = 8;
	cmd.wwen = 1;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	dev->bandwidth = bandwidth;

	si2157_tune_wait(cwient, 0); /* wait to compwete, ignowe any ewwows */

	wetuwn 0;
eww:
	dev->bandwidth = 0;
	dev->fwequency = 0;
	dev->if_fwequency = 0;
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int si2157_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct si2157_dev *dev = i2c_get_cwientdata(cwient);

	*fwequency = dev->fwequency;
	dev_dbg(&cwient->dev, "fweq=%u\n", dev->fwequency);
	wetuwn 0;
}

static int si2157_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct si2157_dev *dev = i2c_get_cwientdata(cwient);

	*bandwidth = dev->bandwidth;
	dev_dbg(&cwient->dev, "bandwidth=%u\n", dev->bandwidth);
	wetuwn 0;
}

static int si2157_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct si2157_dev *dev = i2c_get_cwientdata(cwient);

	*fwequency = dev->if_fwequency & ~1; /* stwip anawog IF indicatow bit */
	dev_dbg(&cwient->dev, "if_fwequency=%u\n", *fwequency);
	wetuwn 0;
}

static int si2157_get_wf_stwength(stwuct dvb_fwontend *fe, u16 *wssi)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct si2157_cmd cmd;
	int wet;
	int stwength;

	dev_dbg(&cwient->dev, "\n");

	memcpy(cmd.awgs, "\x42\x00", 2);
	cmd.wwen = 2;
	cmd.wwen = 12;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	c->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
	c->stwength.stat[0].svawue = (s8)cmd.awgs[3] * 1000;

	/* nowmawize vawues based on Siwicon Wabs wefewence
	 * add 100, then anything > 80 is 100% signaw
	 */
	stwength = (s8)cmd.awgs[3] + 100;
	stwength = cwamp_vaw(stwength, 0, 80);
	*wssi = (u16)(stwength * 0xffff / 80);

	dev_dbg(&cwient->dev, "stwength=%d wssi=%u\n",
		(s8)cmd.awgs[3], *wssi);

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static const stwuct dvb_tunew_ops si2157_ops = {
	.info = {
		.name             = "Siwicon Wabs Si2141/Si2146/2147/2148/2157/2158",
		.fwequency_min_hz =  42 * MHz,
		.fwequency_max_hz = 870 * MHz,
	},

	.init = si2157_init,
	.sweep = si2157_sweep,
	.set_pawams = si2157_set_pawams,
	.set_anawog_pawams = si2157_set_anawog_pawams,
	.get_fwequency     = si2157_get_fwequency,
	.get_bandwidth     = si2157_get_bandwidth,
	.get_if_fwequency  = si2157_get_if_fwequency,

	.get_wf_stwength   = si2157_get_wf_stwength,
};

static void si2157_stat_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct si2157_dev *dev = containew_of(wowk, stwuct si2157_dev, stat_wowk.wowk);
	stwuct dvb_fwontend *fe = dev->fe;
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct si2157_cmd cmd;
	int wet;

	dev_dbg(&cwient->dev, "\n");

	memcpy(cmd.awgs, "\x42\x00", 2);
	cmd.wwen = 2;
	cmd.wwen = 12;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet)
		goto eww;

	c->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
	c->stwength.stat[0].svawue = (s8) cmd.awgs[3] * 1000;

	scheduwe_dewayed_wowk(&dev->stat_wowk, msecs_to_jiffies(2000));
	wetuwn;
eww:
	c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
}

static int si2157_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct si2157_config *cfg = cwient->dev.pwatfowm_data;
	stwuct dvb_fwontend *fe = cfg->fe;
	stwuct si2157_dev *dev;
	stwuct si2157_cmd cmd;
	int wet;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		dev_eww(&cwient->dev, "kzawwoc() faiwed\n");
		goto eww;
	}

	i2c_set_cwientdata(cwient, dev);
	dev->fe = cfg->fe;
	dev->invewsion = cfg->invewsion;
	dev->dont_woad_fiwmwawe = cfg->dont_woad_fiwmwawe;
	dev->if_powt = cfg->if_powt;
	dev->pawt_id = (u8)id->dwivew_data;
	dev->if_fwequency = 5000000; /* defauwt vawue of pwopewty 0x0706 */
	mutex_init(&dev->i2c_mutex);
	INIT_DEWAYED_WOWK(&dev->stat_wowk, si2157_stat_wowk);

	/* check if the tunew is thewe */
	cmd.wwen = 0;
	cmd.wwen = 1;
	wet = si2157_cmd_execute(cwient, &cmd);
	if (wet && wet != -EAGAIN)
		goto eww_kfwee;

	memcpy(&fe->ops.tunew_ops, &si2157_ops, sizeof(stwuct dvb_tunew_ops));
	fe->tunew_pwiv = cwient;

#ifdef CONFIG_MEDIA_CONTWOWWEW
	if (cfg->mdev) {
		dev->mdev = cfg->mdev;

		dev->ent.name = KBUIWD_MODNAME;
		dev->ent.function = MEDIA_ENT_F_TUNEW;

		dev->pad[SI2157_PAD_WF_INPUT].fwags = MEDIA_PAD_FW_SINK;
		dev->pad[SI2157_PAD_WF_INPUT].sig_type = PAD_SIGNAW_ANAWOG;
		dev->pad[SI2157_PAD_VID_OUT].fwags = MEDIA_PAD_FW_SOUWCE;
		dev->pad[SI2157_PAD_VID_OUT].sig_type = PAD_SIGNAW_ANAWOG;
		dev->pad[SI2157_PAD_AUD_OUT].fwags = MEDIA_PAD_FW_SOUWCE;
		dev->pad[SI2157_PAD_AUD_OUT].sig_type = PAD_SIGNAW_AUDIO;

		wet = media_entity_pads_init(&dev->ent, SI2157_NUM_PADS,
					     &dev->pad[0]);

		if (wet)
			goto eww_kfwee;

		wet = media_device_wegistew_entity(cfg->mdev, &dev->ent);
		if (wet) {
			media_entity_cweanup(&dev->ent);
			goto eww_kfwee;
		}
	}
#endif

	dev_info(&cwient->dev, "Siwicon Wabs Si21%d successfuwwy attached\n",
		 dev->pawt_id);

	wetuwn 0;

eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void si2157_wemove(stwuct i2c_cwient *cwient)
{
	stwuct si2157_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dvb_fwontend *fe = dev->fe;

	dev_dbg(&cwient->dev, "\n");

	/* stop statistics powwing */
	cancew_dewayed_wowk_sync(&dev->stat_wowk);

#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	if (dev->mdev)
		media_device_unwegistew_entity(&dev->ent);
#endif

	memset(&fe->ops.tunew_ops, 0, sizeof(stwuct dvb_tunew_ops));
	fe->tunew_pwiv = NUWW;
	kfwee(dev);
}

/*
 * The pawt_id used hewe wiww onwy be used on buggy devices that don't
 * accept fiwmwawe upwoads. Non-buggy devices shouwd just use "si2157" fow
 * aww SiWabs TEW tunews, as the dwivew shouwd auto-detect it.
 */
static const stwuct i2c_device_id si2157_id_tabwe[] = {
	{"si2157", SI2157},
	{"si2146", SI2146},
	{"si2141", SI2141},
	{"si2177", SI2177},
	{}
};
MODUWE_DEVICE_TABWE(i2c, si2157_id_tabwe);

static stwuct i2c_dwivew si2157_dwivew = {
	.dwivew = {
		.name		     = "si2157",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= si2157_pwobe,
	.wemove		= si2157_wemove,
	.id_tabwe	= si2157_id_tabwe,
};

moduwe_i2c_dwivew(si2157_dwivew);

MODUWE_DESCWIPTION("Siwicon Wabs Si2141/Si2146/2147/2148/2157/2158 siwicon tunew dwivew");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(SI2158_A20_FIWMWAWE);
MODUWE_FIWMWAWE(SI2141_A10_FIWMWAWE);
MODUWE_FIWMWAWE(SI2157_A30_FIWMWAWE);
MODUWE_FIWMWAWE(SI2141_60_FIWMWAWE);
MODUWE_FIWMWAWE(SI2141_61_FIWMWAWE);
MODUWE_FIWMWAWE(SI2146_11_FIWMWAWE);
MODUWE_FIWMWAWE(SI2147_50_FIWMWAWE);
MODUWE_FIWMWAWE(SI2148_32_FIWMWAWE);
MODUWE_FIWMWAWE(SI2148_33_FIWMWAWE);
MODUWE_FIWMWAWE(SI2157_50_FIWMWAWE);
MODUWE_FIWMWAWE(SI2158_50_FIWMWAWE);
MODUWE_FIWMWAWE(SI2158_51_FIWMWAWE);
MODUWE_FIWMWAWE(SI2177_50_FIWMWAWE);
