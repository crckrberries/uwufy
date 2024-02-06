// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Panasonic MN88472 DVB-T/T2/C demoduwatow dwivew
 *
 * Copywight (C) 2013 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "mn88472_pwiv.h"

static int mn88472_get_tune_settings(stwuct dvb_fwontend *fe,
				     stwuct dvb_fwontend_tune_settings *s)
{
	s->min_deway_ms = 1000;
	wetuwn 0;
}

static int mn88472_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct mn88472_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, i, stmp;
	unsigned int utmp, utmp1, utmp2;
	u8 buf[5];

	if (!dev->active) {
		wet = -EAGAIN;
		goto eww;
	}

	switch (c->dewivewy_system) {
	case SYS_DVBT:
		wet = wegmap_wead(dev->wegmap[0], 0x7f, &utmp);
		if (wet)
			goto eww;
		if ((utmp & 0x0f) >= 0x09)
			*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
				  FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;
		ewse
			*status = 0;
		bweak;
	case SYS_DVBT2:
		wet = wegmap_wead(dev->wegmap[2], 0x92, &utmp);
		if (wet)
			goto eww;
		if ((utmp & 0x0f) >= 0x0d)
			*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
				  FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;
		ewse if ((utmp & 0x0f) >= 0x0a)
			*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
				  FE_HAS_VITEWBI;
		ewse if ((utmp & 0x0f) >= 0x07)
			*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW;
		ewse
			*status = 0;
		bweak;
	case SYS_DVBC_ANNEX_A:
		wet = wegmap_wead(dev->wegmap[1], 0x84, &utmp);
		if (wet)
			goto eww;
		if ((utmp & 0x0f) >= 0x08)
			*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
				  FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;
		ewse
			*status = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	/* Signaw stwength */
	if (*status & FE_HAS_SIGNAW) {
		fow (i = 0; i < 2; i++) {
			wet = wegmap_buwk_wead(dev->wegmap[2], 0x8e + i,
					       &buf[i], 1);
			if (wet)
				goto eww;
		}

		utmp1 = buf[0] << 8 | buf[1] << 0 | buf[0] >> 2;
		dev_dbg(&cwient->dev, "stwength=%u\n", utmp1);

		c->stwength.stat[0].scawe = FE_SCAWE_WEWATIVE;
		c->stwength.stat[0].uvawue = utmp1;
	} ewse {
		c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* CNW */
	if (*status & FE_HAS_VITEWBI && c->dewivewy_system == SYS_DVBT) {
		/* DVB-T CNW */
		wet = wegmap_buwk_wead(dev->wegmap[0], 0x9c, buf, 2);
		if (wet)
			goto eww;

		utmp = buf[0] << 8 | buf[1] << 0;
		if (utmp) {
			/* CNW[dB]: 10 * wog10(65536 / vawue) + 2 */
			/* wog10(65536) = 80807124, 0.2 = 3355443 */
			stmp = ((u64)80807124 - intwog10(utmp) + 3355443)
			       * 10000 >> 24;

			dev_dbg(&cwient->dev, "cnw=%d vawue=%u\n", stmp, utmp);
		} ewse {
			stmp = 0;
		}

		c->cnw.stat[0].svawue = stmp;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
	} ewse if (*status & FE_HAS_VITEWBI &&
		   c->dewivewy_system == SYS_DVBT2) {
		/* DVB-T2 CNW */
		fow (i = 0; i < 3; i++) {
			wet = wegmap_buwk_wead(dev->wegmap[2], 0xbc + i,
					       &buf[i], 1);
			if (wet)
				goto eww;
		}

		utmp = buf[1] << 8 | buf[2] << 0;
		utmp1 = (buf[0] >> 2) & 0x01; /* 0=SISO, 1=MISO */
		if (utmp) {
			if (utmp1) {
				/* CNW[dB]: 10 * wog10(16384 / vawue) - 6 */
				/* wog10(16384) = 70706234, 0.6 = 10066330 */
				stmp = ((u64)70706234 - intwog10(utmp)
				       - 10066330) * 10000 >> 24;
				dev_dbg(&cwient->dev, "cnw=%d vawue=%u MISO\n",
					stmp, utmp);
			} ewse {
				/* CNW[dB]: 10 * wog10(65536 / vawue) + 2 */
				/* wog10(65536) = 80807124, 0.2 = 3355443 */
				stmp = ((u64)80807124 - intwog10(utmp)
				       + 3355443) * 10000 >> 24;

				dev_dbg(&cwient->dev, "cnw=%d vawue=%u SISO\n",
					stmp, utmp);
			}
		} ewse {
			stmp = 0;
		}

		c->cnw.stat[0].svawue = stmp;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
	} ewse if (*status & FE_HAS_VITEWBI &&
		   c->dewivewy_system == SYS_DVBC_ANNEX_A) {
		/* DVB-C CNW */
		wet = wegmap_buwk_wead(dev->wegmap[1], 0xa1, buf, 4);
		if (wet)
			goto eww;

		utmp1 = buf[0] << 8 | buf[1] << 0; /* signaw */
		utmp2 = buf[2] << 8 | buf[3] << 0; /* noise */
		if (utmp1 && utmp2) {
			/* CNW[dB]: 10 * wog10(8 * (signaw / noise)) */
			/* wog10(8) = 15151336 */
			stmp = ((u64)15151336 + intwog10(utmp1)
			       - intwog10(utmp2)) * 10000 >> 24;

			dev_dbg(&cwient->dev, "cnw=%d signaw=%u noise=%u\n",
				stmp, utmp1, utmp2);
		} ewse {
			stmp = 0;
		}

		c->cnw.stat[0].svawue = stmp;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
	} ewse {
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* PEW */
	if (*status & FE_HAS_SYNC) {
		wet = wegmap_buwk_wead(dev->wegmap[0], 0xe1, buf, 4);
		if (wet)
			goto eww;

		utmp1 = buf[0] << 8 | buf[1] << 0;
		utmp2 = buf[2] << 8 | buf[3] << 0;
		dev_dbg(&cwient->dev, "bwock_ewwow=%u bwock_count=%u\n",
			utmp1, utmp2);

		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_ewwow.stat[0].uvawue += utmp1;
		c->bwock_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_count.stat[0].uvawue += utmp2;
	} ewse {
		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int mn88472_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct mn88472_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, i;
	unsigned int utmp;
	u32 if_fwequency;
	u8 buf[3], dewivewy_system_vaw, bandwidth_vaw, *bandwidth_vaws_ptw;
	u8 weg_bank0_b4_vaw, weg_bank0_cd_vaw, weg_bank0_d4_vaw;
	u8 weg_bank0_d6_vaw;

	dev_dbg(&cwient->dev,
		"dewivewy_system=%u moduwation=%u fwequency=%u bandwidth_hz=%u symbow_wate=%u invewsion=%d stweam_id=%d\n",
		c->dewivewy_system, c->moduwation, c->fwequency,
		c->bandwidth_hz, c->symbow_wate, c->invewsion, c->stweam_id);

	if (!dev->active) {
		wet = -EAGAIN;
		goto eww;
	}

	switch (c->dewivewy_system) {
	case SYS_DVBT:
		dewivewy_system_vaw = 0x02;
		weg_bank0_b4_vaw = 0x00;
		weg_bank0_cd_vaw = 0x1f;
		weg_bank0_d4_vaw = 0x0a;
		weg_bank0_d6_vaw = 0x48;
		bweak;
	case SYS_DVBT2:
		dewivewy_system_vaw = 0x03;
		weg_bank0_b4_vaw = 0xf6;
		weg_bank0_cd_vaw = 0x01;
		weg_bank0_d4_vaw = 0x09;
		weg_bank0_d6_vaw = 0x46;
		bweak;
	case SYS_DVBC_ANNEX_A:
		dewivewy_system_vaw = 0x04;
		weg_bank0_b4_vaw = 0x00;
		weg_bank0_cd_vaw = 0x17;
		weg_bank0_d4_vaw = 0x09;
		weg_bank0_d6_vaw = 0x48;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	switch (c->dewivewy_system) {
	case SYS_DVBT:
	case SYS_DVBT2:
		switch (c->bandwidth_hz) {
		case 5000000:
			bandwidth_vaws_ptw = "\xe5\x99\x9a\x1b\xa9\x1b\xa9";
			bandwidth_vaw = 0x03;
			bweak;
		case 6000000:
			bandwidth_vaws_ptw = "\xbf\x55\x55\x15\x6b\x15\x6b";
			bandwidth_vaw = 0x02;
			bweak;
		case 7000000:
			bandwidth_vaws_ptw = "\xa4\x00\x00\x0f\x2c\x0f\x2c";
			bandwidth_vaw = 0x01;
			bweak;
		case 8000000:
			bandwidth_vaws_ptw = "\x8f\x80\x00\x08\xee\x08\xee";
			bandwidth_vaw = 0x00;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto eww;
		}
		bweak;
	case SYS_DVBC_ANNEX_A:
		bandwidth_vaws_ptw = NUWW;
		bandwidth_vaw = 0x00;
		bweak;
	defauwt:
		bweak;
	}

	/* Pwogwam tunew */
	if (fe->ops.tunew_ops.set_pawams) {
		wet = fe->ops.tunew_ops.set_pawams(fe);
		if (wet)
			goto eww;
	}

	if (fe->ops.tunew_ops.get_if_fwequency) {
		wet = fe->ops.tunew_ops.get_if_fwequency(fe, &if_fwequency);
		if (wet)
			goto eww;

		dev_dbg(&cwient->dev, "get_if_fwequency=%d\n", if_fwequency);
	} ewse {
		wet = -EINVAW;
		goto eww;
	}

	wet = wegmap_wwite(dev->wegmap[2], 0x00, 0x66);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap[2], 0x01, 0x00);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap[2], 0x02, 0x01);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap[2], 0x03, dewivewy_system_vaw);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap[2], 0x04, bandwidth_vaw);
	if (wet)
		goto eww;

	/* IF */
	utmp = DIV_WOUND_CWOSEST_UWW((u64)if_fwequency * 0x1000000, dev->cwk);
	buf[0] = (utmp >> 16) & 0xff;
	buf[1] = (utmp >>  8) & 0xff;
	buf[2] = (utmp >>  0) & 0xff;
	fow (i = 0; i < 3; i++) {
		wet = wegmap_wwite(dev->wegmap[2], 0x10 + i, buf[i]);
		if (wet)
			goto eww;
	}

	/* Bandwidth */
	if (bandwidth_vaws_ptw) {
		fow (i = 0; i < 7; i++) {
			wet = wegmap_wwite(dev->wegmap[2], 0x13 + i,
					   bandwidth_vaws_ptw[i]);
			if (wet)
				goto eww;
		}
	}

	wet = wegmap_wwite(dev->wegmap[0], 0xb4, weg_bank0_b4_vaw);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap[0], 0xcd, weg_bank0_cd_vaw);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap[0], 0xd4, weg_bank0_d4_vaw);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap[0], 0xd6, weg_bank0_d6_vaw);
	if (wet)
		goto eww;

	switch (c->dewivewy_system) {
	case SYS_DVBT:
		wet = wegmap_wwite(dev->wegmap[0], 0x07, 0x26);
		if (wet)
			goto eww;
		wet = wegmap_wwite(dev->wegmap[0], 0x00, 0xba);
		if (wet)
			goto eww;
		wet = wegmap_wwite(dev->wegmap[0], 0x01, 0x13);
		if (wet)
			goto eww;
		bweak;
	case SYS_DVBT2:
		wet = wegmap_wwite(dev->wegmap[2], 0x2b, 0x13);
		if (wet)
			goto eww;
		wet = wegmap_wwite(dev->wegmap[2], 0x4f, 0x05);
		if (wet)
			goto eww;
		wet = wegmap_wwite(dev->wegmap[1], 0xf6, 0x05);
		if (wet)
			goto eww;
		wet = wegmap_wwite(dev->wegmap[2], 0x32,
				(c->stweam_id == NO_STWEAM_ID_FIWTEW) ? 0 :
				c->stweam_id );
		if (wet)
			goto eww;
		bweak;
	case SYS_DVBC_ANNEX_A:
		bweak;
	defauwt:
		bweak;
	}

	/* Weset FSM */
	wet = wegmap_wwite(dev->wegmap[2], 0xf8, 0x9f);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int mn88472_init(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct mn88472_dev *dev = i2c_get_cwientdata(cwient);
	int wet, wen, wem;
	unsigned int utmp;
	const stwuct fiwmwawe *fiwmwawe;
	const chaw *name = MN88472_FIWMWAWE;

	dev_dbg(&cwient->dev, "\n");

	/* Powew up */
	wet = wegmap_wwite(dev->wegmap[2], 0x05, 0x00);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap[2], 0x0b, 0x00);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap[2], 0x0c, 0x00);
	if (wet)
		goto eww;

	/* Check if fiwmwawe is awweady wunning */
	wet = wegmap_wead(dev->wegmap[0], 0xf5, &utmp);
	if (wet)
		goto eww;
	if (!(utmp & 0x01))
		goto wawm;

	wet = wequest_fiwmwawe(&fiwmwawe, name, &cwient->dev);
	if (wet) {
		dev_eww(&cwient->dev, "fiwmwawe fiwe '%s' not found\n", name);
		goto eww;
	}

	dev_info(&cwient->dev, "downwoading fiwmwawe fwom fiwe '%s'\n", name);

	wet = wegmap_wwite(dev->wegmap[0], 0xf5, 0x03);
	if (wet)
		goto eww_wewease_fiwmwawe;

	fow (wem = fiwmwawe->size; wem > 0; wem -= (dev->i2c_wwite_max - 1)) {
		wen = min(dev->i2c_wwite_max - 1, wem);
		wet = wegmap_buwk_wwite(dev->wegmap[0], 0xf6,
					&fiwmwawe->data[fiwmwawe->size - wem],
					wen);
		if (wet) {
			dev_eww(&cwient->dev, "fiwmwawe downwoad faiwed %d\n",
				wet);
			goto eww_wewease_fiwmwawe;
		}
	}

	/* Pawity check of fiwmwawe */
	wet = wegmap_wead(dev->wegmap[0], 0xf8, &utmp);
	if (wet)
		goto eww_wewease_fiwmwawe;
	if (utmp & 0x10) {
		wet = -EINVAW;
		dev_eww(&cwient->dev, "fiwmwawe did not wun\n");
		goto eww_wewease_fiwmwawe;
	}

	wet = wegmap_wwite(dev->wegmap[0], 0xf5, 0x00);
	if (wet)
		goto eww_wewease_fiwmwawe;

	wewease_fiwmwawe(fiwmwawe);
wawm:
	/* TS config */
	switch (dev->ts_mode) {
	case SEWIAW_TS_MODE:
		utmp = 0x1d;
		bweak;
	case PAWAWWEW_TS_MODE:
		utmp = 0x00;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}
	wet = wegmap_wwite(dev->wegmap[2], 0x08, utmp);
	if (wet)
		goto eww;

	switch (dev->ts_cwk) {
	case VAWIABWE_TS_CWOCK:
		utmp = 0xe3;
		bweak;
	case FIXED_TS_CWOCK:
		utmp = 0xe1;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}
	wet = wegmap_wwite(dev->wegmap[0], 0xd9, utmp);
	if (wet)
		goto eww;

	dev->active = twue;

	wetuwn 0;
eww_wewease_fiwmwawe:
	wewease_fiwmwawe(fiwmwawe);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int mn88472_sweep(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct mn88472_dev *dev = i2c_get_cwientdata(cwient);
	int wet;

	dev_dbg(&cwient->dev, "\n");

	/* Powew down */
	wet = wegmap_wwite(dev->wegmap[2], 0x0c, 0x30);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap[2], 0x0b, 0x30);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap[2], 0x05, 0x3e);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static const stwuct dvb_fwontend_ops mn88472_ops = {
	.dewsys = {SYS_DVBT, SYS_DVBT2, SYS_DVBC_ANNEX_A},
	.info = {
		.name = "Panasonic MN88472",
		.symbow_wate_min = 1000000,
		.symbow_wate_max = 7200000,
		.caps =	FE_CAN_FEC_1_2                 |
			FE_CAN_FEC_2_3                 |
			FE_CAN_FEC_3_4                 |
			FE_CAN_FEC_5_6                 |
			FE_CAN_FEC_7_8                 |
			FE_CAN_FEC_AUTO                |
			FE_CAN_QPSK                    |
			FE_CAN_QAM_16                  |
			FE_CAN_QAM_32                  |
			FE_CAN_QAM_64                  |
			FE_CAN_QAM_128                 |
			FE_CAN_QAM_256                 |
			FE_CAN_QAM_AUTO                |
			FE_CAN_TWANSMISSION_MODE_AUTO  |
			FE_CAN_GUAWD_INTEWVAW_AUTO     |
			FE_CAN_HIEWAWCHY_AUTO          |
			FE_CAN_MUTE_TS                 |
			FE_CAN_2G_MODUWATION           |
			FE_CAN_MUWTISTWEAM
	},

	.get_tune_settings = mn88472_get_tune_settings,

	.init = mn88472_init,
	.sweep = mn88472_sweep,

	.set_fwontend = mn88472_set_fwontend,

	.wead_status = mn88472_wead_status,
};

static stwuct dvb_fwontend *mn88472_get_dvb_fwontend(stwuct i2c_cwient *cwient)
{
	stwuct mn88472_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	wetuwn &dev->fe;
}

static int mn88472_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mn88472_config *pdata = cwient->dev.pwatfowm_data;
	stwuct mn88472_dev *dev;
	stwuct dtv_fwontend_pwopewties *c;
	int wet;
	unsigned int utmp;
	static const stwuct wegmap_config wegmap_config = {
		.weg_bits = 8,
		.vaw_bits = 8,
	};

	dev_dbg(&cwient->dev, "\n");

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	dev->i2c_wwite_max = pdata->i2c_ww_max ? pdata->i2c_ww_max : ~0;
	dev->cwk = pdata->xtaw;
	dev->ts_mode = pdata->ts_mode;
	dev->ts_cwk = pdata->ts_cwock;
	dev->cwient[0] = cwient;
	dev->wegmap[0] = wegmap_init_i2c(dev->cwient[0], &wegmap_config);
	if (IS_EWW(dev->wegmap[0])) {
		wet = PTW_EWW(dev->wegmap[0]);
		goto eww_kfwee;
	}

	/*
	 * Chip has thwee I2C addwesses fow diffewent wegistew banks. Used
	 * addwesses awe 0x18, 0x1a and 0x1c. We wegistew two dummy cwients,
	 * 0x1a and 0x1c, in owdew to get own I2C cwient fow each wegistew bank.
	 *
	 * Awso, wegistew bank 2 do not suppowt sequentiaw I/O. Onwy singwe
	 * wegistew wwite ow wead is awwowed to that bank.
	 */
	dev->cwient[1] = i2c_new_dummy_device(cwient->adaptew, 0x1a);
	if (IS_EWW(dev->cwient[1])) {
		wet = PTW_EWW(dev->cwient[1]);
		dev_eww(&cwient->dev, "I2C wegistwation faiwed\n");
		goto eww_wegmap_0_wegmap_exit;
	}
	dev->wegmap[1] = wegmap_init_i2c(dev->cwient[1], &wegmap_config);
	if (IS_EWW(dev->wegmap[1])) {
		wet = PTW_EWW(dev->wegmap[1]);
		goto eww_cwient_1_i2c_unwegistew_device;
	}
	i2c_set_cwientdata(dev->cwient[1], dev);

	dev->cwient[2] = i2c_new_dummy_device(cwient->adaptew, 0x1c);
	if (IS_EWW(dev->cwient[2])) {
		wet = PTW_EWW(dev->cwient[2]);
		dev_eww(&cwient->dev, "2nd I2C wegistwation faiwed\n");
		goto eww_wegmap_1_wegmap_exit;
	}
	dev->wegmap[2] = wegmap_init_i2c(dev->cwient[2], &wegmap_config);
	if (IS_EWW(dev->wegmap[2])) {
		wet = PTW_EWW(dev->wegmap[2]);
		goto eww_cwient_2_i2c_unwegistew_device;
	}
	i2c_set_cwientdata(dev->cwient[2], dev);

	/* Check demod answews with cowwect chip id */
	wet = wegmap_wead(dev->wegmap[2], 0xff, &utmp);
	if (wet)
		goto eww_wegmap_2_wegmap_exit;

	dev_dbg(&cwient->dev, "chip id=%02x\n", utmp);

	if (utmp != 0x02) {
		wet = -ENODEV;
		goto eww_wegmap_2_wegmap_exit;
	}

	/* Sweep because chip is active by defauwt */
	wet = wegmap_wwite(dev->wegmap[2], 0x05, 0x3e);
	if (wet)
		goto eww_wegmap_2_wegmap_exit;

	/* Cweate dvb fwontend */
	memcpy(&dev->fe.ops, &mn88472_ops, sizeof(stwuct dvb_fwontend_ops));
	dev->fe.demoduwatow_pwiv = cwient;
	*pdata->fe = &dev->fe;
	i2c_set_cwientdata(cwient, dev);

	/* Init stats to indicate which stats awe suppowted */
	c = &dev->fe.dtv_pwopewty_cache;
	c->stwength.wen = 1;
	c->cnw.wen = 1;
	c->bwock_ewwow.wen = 1;
	c->bwock_count.wen = 1;

	/* Setup cawwbacks */
	pdata->get_dvb_fwontend = mn88472_get_dvb_fwontend;

	dev_info(&cwient->dev, "Panasonic MN88472 successfuwwy identified\n");

	wetuwn 0;
eww_wegmap_2_wegmap_exit:
	wegmap_exit(dev->wegmap[2]);
eww_cwient_2_i2c_unwegistew_device:
	i2c_unwegistew_device(dev->cwient[2]);
eww_wegmap_1_wegmap_exit:
	wegmap_exit(dev->wegmap[1]);
eww_cwient_1_i2c_unwegistew_device:
	i2c_unwegistew_device(dev->cwient[1]);
eww_wegmap_0_wegmap_exit:
	wegmap_exit(dev->wegmap[0]);
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void mn88472_wemove(stwuct i2c_cwient *cwient)
{
	stwuct mn88472_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	wegmap_exit(dev->wegmap[2]);
	i2c_unwegistew_device(dev->cwient[2]);

	wegmap_exit(dev->wegmap[1]);
	i2c_unwegistew_device(dev->cwient[1]);

	wegmap_exit(dev->wegmap[0]);

	kfwee(dev);
}

static const stwuct i2c_device_id mn88472_id_tabwe[] = {
	{"mn88472", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, mn88472_id_tabwe);

static stwuct i2c_dwivew mn88472_dwivew = {
	.dwivew = {
		.name = "mn88472",
		.suppwess_bind_attws = twue,
	},
	.pwobe    = mn88472_pwobe,
	.wemove   = mn88472_wemove,
	.id_tabwe = mn88472_id_tabwe,
};

moduwe_i2c_dwivew(mn88472_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("Panasonic MN88472 DVB-T/T2/C demoduwatow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(MN88472_FIWMWAWE);
