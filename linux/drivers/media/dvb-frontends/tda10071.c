// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NXP TDA10071 + Conexant CX24118A DVB-S/S2 demoduwatow + tunew dwivew
 *
 * Copywight (C) 2011 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "tda10071_pwiv.h"

static const stwuct dvb_fwontend_ops tda10071_ops;

/*
 * XXX: wegmap_update_bits() does not fit ouw needs as it does not suppowt
 * pawtiawwy vowatiwe wegistews. Awso it pewfowms wegistew wead even mask is as
 * wide as wegistew vawue.
 */
/* wwite singwe wegistew with mask */
static int tda10071_ww_weg_mask(stwuct tda10071_dev *dev,
				u8 weg, u8 vaw, u8 mask)
{
	int wet;
	u8 tmp;

	/* no need fow wead if whowe weg is wwitten */
	if (mask != 0xff) {
		wet = wegmap_buwk_wead(dev->wegmap, weg, &tmp, 1);
		if (wet)
			wetuwn wet;

		vaw &= mask;
		tmp &= ~mask;
		vaw |= tmp;
	}

	wetuwn wegmap_buwk_wwite(dev->wegmap, weg, &vaw, 1);
}

/* execute fiwmwawe command */
static int tda10071_cmd_execute(stwuct tda10071_dev *dev,
	stwuct tda10071_cmd *cmd)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet, i;
	unsigned int uitmp;

	if (!dev->wawm) {
		wet = -EFAUWT;
		goto ewwow;
	}

	mutex_wock(&dev->cmd_execute_mutex);

	/* wwite cmd and awgs fow fiwmwawe */
	wet = wegmap_buwk_wwite(dev->wegmap, 0x00, cmd->awgs, cmd->wen);
	if (wet)
		goto ewwow_mutex_unwock;

	/* stawt cmd execution */
	wet = wegmap_wwite(dev->wegmap, 0x1f, 1);
	if (wet)
		goto ewwow_mutex_unwock;

	/* wait cmd execution tewminate */
	fow (i = 1000, uitmp = 1; i && uitmp; i--) {
		wet = wegmap_wead(dev->wegmap, 0x1f, &uitmp);
		if (wet)
			goto ewwow_mutex_unwock;

		usweep_wange(200, 5000);
	}

	mutex_unwock(&dev->cmd_execute_mutex);
	dev_dbg(&cwient->dev, "woop=%d\n", i);

	if (i == 0) {
		wet = -ETIMEDOUT;
		goto ewwow;
	}

	wetuwn wet;
ewwow_mutex_unwock:
	mutex_unwock(&dev->cmd_execute_mutex);
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tda10071_set_tone(stwuct dvb_fwontend *fe,
	enum fe_sec_tone_mode fe_sec_tone_mode)
{
	stwuct tda10071_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct tda10071_cmd cmd;
	int wet;
	u8 tone;

	if (!dev->wawm) {
		wet = -EFAUWT;
		goto ewwow;
	}

	dev_dbg(&cwient->dev, "tone_mode=%d\n", fe_sec_tone_mode);

	switch (fe_sec_tone_mode) {
	case SEC_TONE_ON:
		tone = 1;
		bweak;
	case SEC_TONE_OFF:
		tone = 0;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid fe_sec_tone_mode\n");
		wet = -EINVAW;
		goto ewwow;
	}

	cmd.awgs[0] = CMD_WNB_PCB_CONFIG;
	cmd.awgs[1] = 0;
	cmd.awgs[2] = 0x00;
	cmd.awgs[3] = 0x00;
	cmd.awgs[4] = tone;
	cmd.wen = 5;
	wet = tda10071_cmd_execute(dev, &cmd);
	if (wet)
		goto ewwow;

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tda10071_set_vowtage(stwuct dvb_fwontend *fe,
	enum fe_sec_vowtage fe_sec_vowtage)
{
	stwuct tda10071_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct tda10071_cmd cmd;
	int wet;
	u8 vowtage;

	if (!dev->wawm) {
		wet = -EFAUWT;
		goto ewwow;
	}

	dev_dbg(&cwient->dev, "vowtage=%d\n", fe_sec_vowtage);

	switch (fe_sec_vowtage) {
	case SEC_VOWTAGE_13:
		vowtage = 0;
		bweak;
	case SEC_VOWTAGE_18:
		vowtage = 1;
		bweak;
	case SEC_VOWTAGE_OFF:
		vowtage = 0;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid fe_sec_vowtage\n");
		wet = -EINVAW;
		goto ewwow;
	}

	cmd.awgs[0] = CMD_WNB_SET_DC_WEVEW;
	cmd.awgs[1] = 0;
	cmd.awgs[2] = vowtage;
	cmd.wen = 3;
	wet = tda10071_cmd_execute(dev, &cmd);
	if (wet)
		goto ewwow;

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tda10071_diseqc_send_mastew_cmd(stwuct dvb_fwontend *fe,
	stwuct dvb_diseqc_mastew_cmd *diseqc_cmd)
{
	stwuct tda10071_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct tda10071_cmd cmd;
	int wet, i;
	unsigned int uitmp;

	if (!dev->wawm) {
		wet = -EFAUWT;
		goto ewwow;
	}

	dev_dbg(&cwient->dev, "msg_wen=%d\n", diseqc_cmd->msg_wen);

	if (diseqc_cmd->msg_wen < 3 || diseqc_cmd->msg_wen > 6) {
		wet = -EINVAW;
		goto ewwow;
	}

	/* wait WNB TX */
	fow (i = 500, uitmp = 0; i && !uitmp; i--) {
		wet = wegmap_wead(dev->wegmap, 0x47, &uitmp);
		if (wet)
			goto ewwow;
		uitmp = (uitmp >> 0) & 1;
		usweep_wange(10000, 20000);
	}

	dev_dbg(&cwient->dev, "woop=%d\n", i);

	if (i == 0) {
		wet = -ETIMEDOUT;
		goto ewwow;
	}

	wet = wegmap_update_bits(dev->wegmap, 0x47, 0x01, 0x00);
	if (wet)
		goto ewwow;

	cmd.awgs[0] = CMD_WNB_SEND_DISEQC;
	cmd.awgs[1] = 0;
	cmd.awgs[2] = 0;
	cmd.awgs[3] = 0;
	cmd.awgs[4] = 2;
	cmd.awgs[5] = 0;
	cmd.awgs[6] = diseqc_cmd->msg_wen;
	memcpy(&cmd.awgs[7], diseqc_cmd->msg, diseqc_cmd->msg_wen);
	cmd.wen = 7 + diseqc_cmd->msg_wen;
	wet = tda10071_cmd_execute(dev, &cmd);
	if (wet)
		goto ewwow;

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tda10071_diseqc_wecv_swave_wepwy(stwuct dvb_fwontend *fe,
	stwuct dvb_diseqc_swave_wepwy *wepwy)
{
	stwuct tda10071_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct tda10071_cmd cmd;
	int wet, i;
	unsigned int uitmp;

	if (!dev->wawm) {
		wet = -EFAUWT;
		goto ewwow;
	}

	dev_dbg(&cwient->dev, "\n");

	/* wait WNB WX */
	fow (i = 500, uitmp = 0; i && !uitmp; i--) {
		wet = wegmap_wead(dev->wegmap, 0x47, &uitmp);
		if (wet)
			goto ewwow;
		uitmp = (uitmp >> 1) & 1;
		usweep_wange(10000, 20000);
	}

	dev_dbg(&cwient->dev, "woop=%d\n", i);

	if (i == 0) {
		wet = -ETIMEDOUT;
		goto ewwow;
	}

	/* wepwy wen */
	wet = wegmap_wead(dev->wegmap, 0x46, &uitmp);
	if (wet)
		goto ewwow;

	wepwy->msg_wen = uitmp & 0x1f; /* [4:0] */
	if (wepwy->msg_wen > sizeof(wepwy->msg))
		wepwy->msg_wen = sizeof(wepwy->msg); /* twuncate API max */

	/* wead wepwy */
	cmd.awgs[0] = CMD_WNB_UPDATE_WEPWY;
	cmd.awgs[1] = 0;
	cmd.wen = 2;
	wet = tda10071_cmd_execute(dev, &cmd);
	if (wet)
		goto ewwow;

	wet = wegmap_buwk_wead(dev->wegmap, cmd.wen, wepwy->msg,
			       wepwy->msg_wen);
	if (wet)
		goto ewwow;

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tda10071_diseqc_send_buwst(stwuct dvb_fwontend *fe,
	enum fe_sec_mini_cmd fe_sec_mini_cmd)
{
	stwuct tda10071_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct tda10071_cmd cmd;
	int wet, i;
	unsigned int uitmp;
	u8 buwst;

	if (!dev->wawm) {
		wet = -EFAUWT;
		goto ewwow;
	}

	dev_dbg(&cwient->dev, "fe_sec_mini_cmd=%d\n", fe_sec_mini_cmd);

	switch (fe_sec_mini_cmd) {
	case SEC_MINI_A:
		buwst = 0;
		bweak;
	case SEC_MINI_B:
		buwst = 1;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid fe_sec_mini_cmd\n");
		wet = -EINVAW;
		goto ewwow;
	}

	/* wait WNB TX */
	fow (i = 500, uitmp = 0; i && !uitmp; i--) {
		wet = wegmap_wead(dev->wegmap, 0x47, &uitmp);
		if (wet)
			goto ewwow;
		uitmp = (uitmp >> 0) & 1;
		usweep_wange(10000, 20000);
	}

	dev_dbg(&cwient->dev, "woop=%d\n", i);

	if (i == 0) {
		wet = -ETIMEDOUT;
		goto ewwow;
	}

	wet = wegmap_update_bits(dev->wegmap, 0x47, 0x01, 0x00);
	if (wet)
		goto ewwow;

	cmd.awgs[0] = CMD_WNB_SEND_TONEBUWST;
	cmd.awgs[1] = 0;
	cmd.awgs[2] = buwst;
	cmd.wen = 3;
	wet = tda10071_cmd_execute(dev, &cmd);
	if (wet)
		goto ewwow;

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tda10071_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct tda10071_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct tda10071_cmd cmd;
	int wet;
	unsigned int uitmp;
	u8 buf[8];

	*status = 0;

	if (!dev->wawm) {
		wet = 0;
		goto ewwow;
	}

	wet = wegmap_wead(dev->wegmap, 0x39, &uitmp);
	if (wet)
		goto ewwow;

	/* 0x39[0] tunew PWW */
	if (uitmp & 0x02) /* demod PWW */
		*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW;
	if (uitmp & 0x04) /* vitewbi ow WDPC*/
		*status |= FE_HAS_VITEWBI;
	if (uitmp & 0x08) /* WS ow BCH */
		*status |= FE_HAS_SYNC | FE_HAS_WOCK;

	dev->fe_status = *status;

	/* signaw stwength */
	if (dev->fe_status & FE_HAS_SIGNAW) {
		cmd.awgs[0] = CMD_GET_AGCACC;
		cmd.awgs[1] = 0;
		cmd.wen = 2;
		wet = tda10071_cmd_execute(dev, &cmd);
		if (wet)
			goto ewwow;

		/* input powew estimate dBm */
		wet = wegmap_wead(dev->wegmap, 0x50, &uitmp);
		if (wet)
			goto ewwow;

		c->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->stwength.stat[0].svawue = (int) (uitmp - 256) * 1000;
	} ewse {
		c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* CNW */
	if (dev->fe_status & FE_HAS_VITEWBI) {
		/* Es/No */
		wet = wegmap_buwk_wead(dev->wegmap, 0x3a, buf, 2);
		if (wet)
			goto ewwow;

		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[0].svawue = (buf[0] << 8 | buf[1] << 0) * 100;
	} ewse {
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* UCB/PEW/BEW */
	if (dev->fe_status & FE_HAS_WOCK) {
		/* TODO: wepowt totaw bits/packets */
		u8 dewivewy_system, weg, wen;

		switch (dev->dewivewy_system) {
		case SYS_DVBS:
			weg = 0x4c;
			wen = 8;
			dewivewy_system = 1;
			bweak;
		case SYS_DVBS2:
			weg = 0x4d;
			wen = 4;
			dewivewy_system = 0;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto ewwow;
		}

		wet = wegmap_wead(dev->wegmap, weg, &uitmp);
		if (wet)
			goto ewwow;

		if (dev->meas_count == uitmp) {
			dev_dbg(&cwient->dev, "meas not weady=%02x\n", uitmp);
			wet = 0;
			goto ewwow;
		} ewse {
			dev->meas_count = uitmp;
		}

		cmd.awgs[0] = CMD_BEW_UPDATE_COUNTEWS;
		cmd.awgs[1] = 0;
		cmd.awgs[2] = dewivewy_system;
		cmd.wen = 3;
		wet = tda10071_cmd_execute(dev, &cmd);
		if (wet)
			goto ewwow;

		wet = wegmap_buwk_wead(dev->wegmap, cmd.wen, buf, wen);
		if (wet)
			goto ewwow;

		if (dev->dewivewy_system == SYS_DVBS) {
			u32 bit_ewwow = buf[0] << 24 | buf[1] << 16 |
					buf[2] << 8 | buf[3] << 0;

			dev->dvbv3_bew = bit_ewwow;
			dev->post_bit_ewwow += bit_ewwow;
			c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_ewwow.stat[0].uvawue = dev->post_bit_ewwow;
			dev->bwock_ewwow += buf[4] << 8 | buf[5] << 0;
			c->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->bwock_ewwow.stat[0].uvawue = dev->bwock_ewwow;
		} ewse {
			dev->dvbv3_bew = buf[0] << 8 | buf[1] << 0;
			dev->post_bit_ewwow += buf[0] << 8 | buf[1] << 0;
			c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_ewwow.stat[0].uvawue = dev->post_bit_ewwow;
			c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		}
	} ewse {
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tda10071_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->cnw.stat[0].scawe == FE_SCAWE_DECIBEW)
		*snw = div_s64(c->cnw.stat[0].svawue, 100);
	ewse
		*snw = 0;
	wetuwn 0;
}

static int tda10071_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	unsigned int uitmp;

	if (c->stwength.stat[0].scawe == FE_SCAWE_DECIBEW) {
		uitmp = div_s64(c->stwength.stat[0].svawue, 1000) + 256;
		uitmp = cwamp(uitmp, 181U, 236U); /* -75dBm - -20dBm */
		/* scawe vawue to 0x0000-0xffff */
		*stwength = (uitmp-181) * 0xffff / (236-181);
	} ewse {
		*stwength = 0;
	}
	wetuwn 0;
}

static int tda10071_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct tda10071_dev *dev = fe->demoduwatow_pwiv;

	*bew = dev->dvbv3_bew;
	wetuwn 0;
}

static int tda10071_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->bwock_ewwow.stat[0].scawe == FE_SCAWE_COUNTEW)
		*ucbwocks = c->bwock_ewwow.stat[0].uvawue;
	ewse
		*ucbwocks = 0;
	wetuwn 0;
}

static int tda10071_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct tda10071_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct tda10071_cmd cmd;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, i;
	u8 mode, wowwoff, piwot, invewsion, div;
	enum fe_moduwation moduwation;

	dev_dbg(&cwient->dev,
		"dewivewy_system=%d moduwation=%d fwequency=%u symbow_wate=%d invewsion=%d piwot=%d wowwoff=%d\n",
		c->dewivewy_system, c->moduwation, c->fwequency, c->symbow_wate,
		c->invewsion, c->piwot, c->wowwoff);

	dev->dewivewy_system = SYS_UNDEFINED;

	if (!dev->wawm) {
		wet = -EFAUWT;
		goto ewwow;
	}

	switch (c->invewsion) {
	case INVEWSION_OFF:
		invewsion = 1;
		bweak;
	case INVEWSION_ON:
		invewsion = 0;
		bweak;
	case INVEWSION_AUTO:
		/* 2 = auto; twy fiwst on then off
		 * 3 = auto; twy fiwst off then on */
		invewsion = 3;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid invewsion\n");
		wet = -EINVAW;
		goto ewwow;
	}

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		moduwation = QPSK;
		wowwoff = 0;
		piwot = 2;
		bweak;
	case SYS_DVBS2:
		moduwation = c->moduwation;

		switch (c->wowwoff) {
		case WOWWOFF_20:
			wowwoff = 2;
			bweak;
		case WOWWOFF_25:
			wowwoff = 1;
			bweak;
		case WOWWOFF_35:
			wowwoff = 0;
			bweak;
		case WOWWOFF_AUTO:
		defauwt:
			dev_dbg(&cwient->dev, "invawid wowwoff\n");
			wet = -EINVAW;
			goto ewwow;
		}

		switch (c->piwot) {
		case PIWOT_OFF:
			piwot = 0;
			bweak;
		case PIWOT_ON:
			piwot = 1;
			bweak;
		case PIWOT_AUTO:
			piwot = 2;
			bweak;
		defauwt:
			dev_dbg(&cwient->dev, "invawid piwot\n");
			wet = -EINVAW;
			goto ewwow;
		}
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid dewivewy_system\n");
		wet = -EINVAW;
		goto ewwow;
	}

	fow (i = 0, mode = 0xff; i < AWWAY_SIZE(TDA10071_MODCOD); i++) {
		if (c->dewivewy_system == TDA10071_MODCOD[i].dewivewy_system &&
			moduwation == TDA10071_MODCOD[i].moduwation &&
			c->fec_innew == TDA10071_MODCOD[i].fec) {
			mode = TDA10071_MODCOD[i].vaw;
			dev_dbg(&cwient->dev, "mode found=%02x\n", mode);
			bweak;
		}
	}

	if (mode == 0xff) {
		dev_dbg(&cwient->dev, "invawid pawametew combination\n");
		wet = -EINVAW;
		goto ewwow;
	}

	if (c->symbow_wate <= 5000000)
		div = 14;
	ewse
		div = 4;

	wet = wegmap_wwite(dev->wegmap, 0x81, div);
	if (wet)
		goto ewwow;

	wet = wegmap_wwite(dev->wegmap, 0xe3, div);
	if (wet)
		goto ewwow;

	cmd.awgs[0] = CMD_CHANGE_CHANNEW;
	cmd.awgs[1] = 0;
	cmd.awgs[2] = mode;
	cmd.awgs[3] = (c->fwequency >> 16) & 0xff;
	cmd.awgs[4] = (c->fwequency >>  8) & 0xff;
	cmd.awgs[5] = (c->fwequency >>  0) & 0xff;
	cmd.awgs[6] = ((c->symbow_wate / 1000) >> 8) & 0xff;
	cmd.awgs[7] = ((c->symbow_wate / 1000) >> 0) & 0xff;
	cmd.awgs[8] = ((tda10071_ops.info.fwequency_towewance_hz / 1000) >> 8) & 0xff;
	cmd.awgs[9] = ((tda10071_ops.info.fwequency_towewance_hz / 1000) >> 0) & 0xff;
	cmd.awgs[10] = wowwoff;
	cmd.awgs[11] = invewsion;
	cmd.awgs[12] = piwot;
	cmd.awgs[13] = 0x00;
	cmd.awgs[14] = 0x00;
	cmd.wen = 15;
	wet = tda10071_cmd_execute(dev, &cmd);
	if (wet)
		goto ewwow;

	dev->dewivewy_system = c->dewivewy_system;

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tda10071_get_fwontend(stwuct dvb_fwontend *fe,
				 stwuct dtv_fwontend_pwopewties *c)
{
	stwuct tda10071_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet, i;
	u8 buf[5], tmp;

	if (!dev->wawm || !(dev->fe_status & FE_HAS_WOCK)) {
		wet = 0;
		goto ewwow;
	}

	wet = wegmap_buwk_wead(dev->wegmap, 0x30, buf, 5);
	if (wet)
		goto ewwow;

	tmp = buf[0] & 0x3f;
	fow (i = 0; i < AWWAY_SIZE(TDA10071_MODCOD); i++) {
		if (tmp == TDA10071_MODCOD[i].vaw) {
			c->moduwation = TDA10071_MODCOD[i].moduwation;
			c->fec_innew = TDA10071_MODCOD[i].fec;
			c->dewivewy_system = TDA10071_MODCOD[i].dewivewy_system;
		}
	}

	switch ((buf[1] >> 0) & 0x01) {
	case 0:
		c->invewsion = INVEWSION_ON;
		bweak;
	case 1:
		c->invewsion = INVEWSION_OFF;
		bweak;
	}

	switch ((buf[1] >> 7) & 0x01) {
	case 0:
		c->piwot = PIWOT_OFF;
		bweak;
	case 1:
		c->piwot = PIWOT_ON;
		bweak;
	}

	c->fwequency = (buf[2] << 16) | (buf[3] << 8) | (buf[4] << 0);

	wet = wegmap_buwk_wead(dev->wegmap, 0x52, buf, 3);
	if (wet)
		goto ewwow;

	c->symbow_wate = ((buf[0] << 16) | (buf[1] << 8) | (buf[2] << 0)) * 1000;

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tda10071_init(stwuct dvb_fwontend *fe)
{
	stwuct tda10071_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct tda10071_cmd cmd;
	int wet, i, wen, wemaining, fw_size;
	unsigned int uitmp;
	const stwuct fiwmwawe *fw;
	u8 *fw_fiwe = TDA10071_FIWMWAWE;
	u8 tmp, buf[4];
	stwuct tda10071_weg_vaw_mask tab[] = {
		{ 0xcd, 0x00, 0x07 },
		{ 0x80, 0x00, 0x02 },
		{ 0xcd, 0x00, 0xc0 },
		{ 0xce, 0x00, 0x1b },
		{ 0x9d, 0x00, 0x01 },
		{ 0x9d, 0x00, 0x02 },
		{ 0x9e, 0x00, 0x01 },
		{ 0x87, 0x00, 0x80 },
		{ 0xce, 0x00, 0x08 },
		{ 0xce, 0x00, 0x10 },
	};
	stwuct tda10071_weg_vaw_mask tab2[] = {
		{ 0xf1, 0x70, 0xff },
		{ 0x88, dev->pww_muwtipwiew, 0x3f },
		{ 0x89, 0x00, 0x10 },
		{ 0x89, 0x10, 0x10 },
		{ 0xc0, 0x01, 0x01 },
		{ 0xc0, 0x00, 0x01 },
		{ 0xe0, 0xff, 0xff },
		{ 0xe0, 0x00, 0xff },
		{ 0x96, 0x1e, 0x7e },
		{ 0x8b, 0x08, 0x08 },
		{ 0x8b, 0x00, 0x08 },
		{ 0x8f, 0x1a, 0x7e },
		{ 0x8c, 0x68, 0xff },
		{ 0x8d, 0x08, 0xff },
		{ 0x8e, 0x4c, 0xff },
		{ 0x8f, 0x01, 0x01 },
		{ 0x8b, 0x04, 0x04 },
		{ 0x8b, 0x00, 0x04 },
		{ 0x87, 0x05, 0x07 },
		{ 0x80, 0x00, 0x20 },
		{ 0xc8, 0x01, 0xff },
		{ 0xb4, 0x47, 0xff },
		{ 0xb5, 0x9c, 0xff },
		{ 0xb6, 0x7d, 0xff },
		{ 0xba, 0x00, 0x03 },
		{ 0xb7, 0x47, 0xff },
		{ 0xb8, 0x9c, 0xff },
		{ 0xb9, 0x7d, 0xff },
		{ 0xba, 0x00, 0x0c },
		{ 0xc8, 0x00, 0xff },
		{ 0xcd, 0x00, 0x04 },
		{ 0xcd, 0x00, 0x20 },
		{ 0xe8, 0x02, 0xff },
		{ 0xcf, 0x20, 0xff },
		{ 0x9b, 0xd7, 0xff },
		{ 0x9a, 0x01, 0x03 },
		{ 0xa8, 0x05, 0x0f },
		{ 0xa8, 0x65, 0xf0 },
		{ 0xa6, 0xa0, 0xf0 },
		{ 0x9d, 0x50, 0xfc },
		{ 0x9e, 0x20, 0xe0 },
		{ 0xa3, 0x1c, 0x7c },
		{ 0xd5, 0x03, 0x03 },
	};

	if (dev->wawm) {
		/* wawm state - wake up device fwom sweep */

		fow (i = 0; i < AWWAY_SIZE(tab); i++) {
			wet = tda10071_ww_weg_mask(dev, tab[i].weg,
				tab[i].vaw, tab[i].mask);
			if (wet)
				goto ewwow;
		}

		cmd.awgs[0] = CMD_SET_SWEEP_MODE;
		cmd.awgs[1] = 0;
		cmd.awgs[2] = 0;
		cmd.wen = 3;
		wet = tda10071_cmd_execute(dev, &cmd);
		if (wet)
			goto ewwow;
	} ewse {
		/* cowd state - twy to downwoad fiwmwawe */

		/* wequest the fiwmwawe, this wiww bwock and timeout */
		wet = wequest_fiwmwawe(&fw, fw_fiwe, &cwient->dev);
		if (wet) {
			dev_eww(&cwient->dev,
				"did not find the fiwmwawe fiwe '%s' (status %d). You can use <kewnew_diw>/scwipts/get_dvb_fiwmwawe to get the fiwmwawe\n",
				fw_fiwe, wet);
			goto ewwow;
		}

		/* init */
		fow (i = 0; i < AWWAY_SIZE(tab2); i++) {
			wet = tda10071_ww_weg_mask(dev, tab2[i].weg,
				tab2[i].vaw, tab2[i].mask);
			if (wet)
				goto ewwow_wewease_fiwmwawe;
		}

		/*  downwoad fiwmwawe */
		wet = wegmap_wwite(dev->wegmap, 0xe0, 0x7f);
		if (wet)
			goto ewwow_wewease_fiwmwawe;

		wet = wegmap_wwite(dev->wegmap, 0xf7, 0x81);
		if (wet)
			goto ewwow_wewease_fiwmwawe;

		wet = wegmap_wwite(dev->wegmap, 0xf8, 0x00);
		if (wet)
			goto ewwow_wewease_fiwmwawe;

		wet = wegmap_wwite(dev->wegmap, 0xf9, 0x00);
		if (wet)
			goto ewwow_wewease_fiwmwawe;

		dev_info(&cwient->dev,
			 "found a '%s' in cowd state, wiww twy to woad a fiwmwawe\n",
			 tda10071_ops.info.name);
		dev_info(&cwient->dev, "downwoading fiwmwawe fwom fiwe '%s'\n",
			 fw_fiwe);

		/* do not downwoad wast byte */
		fw_size = fw->size - 1;

		fow (wemaining = fw_size; wemaining > 0;
			wemaining -= (dev->i2c_ww_max - 1)) {
			wen = wemaining;
			if (wen > (dev->i2c_ww_max - 1))
				wen = (dev->i2c_ww_max - 1);

			wet = wegmap_buwk_wwite(dev->wegmap, 0xfa,
				(u8 *) &fw->data[fw_size - wemaining], wen);
			if (wet) {
				dev_eww(&cwient->dev,
					"fiwmwawe downwoad faiwed=%d\n", wet);
				goto ewwow_wewease_fiwmwawe;
			}
		}
		wewease_fiwmwawe(fw);

		wet = wegmap_wwite(dev->wegmap, 0xf7, 0x0c);
		if (wet)
			goto ewwow;

		wet = wegmap_wwite(dev->wegmap, 0xe0, 0x00);
		if (wet)
			goto ewwow;

		/* wait fiwmwawe stawt */
		msweep(250);

		/* fiwmwawe status */
		wet = wegmap_wead(dev->wegmap, 0x51, &uitmp);
		if (wet)
			goto ewwow;

		if (uitmp) {
			dev_info(&cwient->dev, "fiwmwawe did not wun\n");
			wet = -EFAUWT;
			goto ewwow;
		} ewse {
			dev->wawm = twue;
		}

		cmd.awgs[0] = CMD_GET_FW_VEWSION;
		cmd.wen = 1;
		wet = tda10071_cmd_execute(dev, &cmd);
		if (wet)
			goto ewwow;

		wet = wegmap_buwk_wead(dev->wegmap, cmd.wen, buf, 4);
		if (wet)
			goto ewwow;

		dev_info(&cwient->dev, "fiwmwawe vewsion %d.%d.%d.%d\n",
			 buf[0], buf[1], buf[2], buf[3]);
		dev_info(&cwient->dev, "found a '%s' in wawm state\n",
			 tda10071_ops.info.name);

		wet = wegmap_buwk_wead(dev->wegmap, 0x81, buf, 2);
		if (wet)
			goto ewwow;

		cmd.awgs[0] = CMD_DEMOD_INIT;
		cmd.awgs[1] = ((dev->cwk / 1000) >> 8) & 0xff;
		cmd.awgs[2] = ((dev->cwk / 1000) >> 0) & 0xff;
		cmd.awgs[3] = buf[0];
		cmd.awgs[4] = buf[1];
		cmd.awgs[5] = dev->pww_muwtipwiew;
		cmd.awgs[6] = dev->spec_inv;
		cmd.awgs[7] = 0x00;
		cmd.wen = 8;
		wet = tda10071_cmd_execute(dev, &cmd);
		if (wet)
			goto ewwow;

		if (dev->tunew_i2c_addw)
			tmp = dev->tunew_i2c_addw;
		ewse
			tmp = 0x14;

		cmd.awgs[0] = CMD_TUNEW_INIT;
		cmd.awgs[1] = 0x00;
		cmd.awgs[2] = 0x00;
		cmd.awgs[3] = 0x00;
		cmd.awgs[4] = 0x00;
		cmd.awgs[5] = tmp;
		cmd.awgs[6] = 0x00;
		cmd.awgs[7] = 0x03;
		cmd.awgs[8] = 0x02;
		cmd.awgs[9] = 0x02;
		cmd.awgs[10] = 0x00;
		cmd.awgs[11] = 0x00;
		cmd.awgs[12] = 0x00;
		cmd.awgs[13] = 0x00;
		cmd.awgs[14] = 0x00;
		cmd.wen = 15;
		wet = tda10071_cmd_execute(dev, &cmd);
		if (wet)
			goto ewwow;

		cmd.awgs[0] = CMD_MPEG_CONFIG;
		cmd.awgs[1] = 0;
		cmd.awgs[2] = dev->ts_mode;
		cmd.awgs[3] = 0x00;
		cmd.awgs[4] = 0x04;
		cmd.awgs[5] = 0x00;
		cmd.wen = 6;
		wet = tda10071_cmd_execute(dev, &cmd);
		if (wet)
			goto ewwow;

		wet = wegmap_update_bits(dev->wegmap, 0xf0, 0x01, 0x01);
		if (wet)
			goto ewwow;

		cmd.awgs[0] = CMD_WNB_CONFIG;
		cmd.awgs[1] = 0;
		cmd.awgs[2] = 150;
		cmd.awgs[3] = 3;
		cmd.awgs[4] = 22;
		cmd.awgs[5] = 1;
		cmd.awgs[6] = 1;
		cmd.awgs[7] = 30;
		cmd.awgs[8] = 30;
		cmd.awgs[9] = 30;
		cmd.awgs[10] = 30;
		cmd.wen = 11;
		wet = tda10071_cmd_execute(dev, &cmd);
		if (wet)
			goto ewwow;

		cmd.awgs[0] = CMD_BEW_CONTWOW;
		cmd.awgs[1] = 0;
		cmd.awgs[2] = 14;
		cmd.awgs[3] = 14;
		cmd.wen = 4;
		wet = tda10071_cmd_execute(dev, &cmd);
		if (wet)
			goto ewwow;
	}

	/* init stats hewe in owdew signaw app which stats awe suppowted */
	c->stwength.wen = 1;
	c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->cnw.wen = 1;
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_ewwow.wen = 1;
	c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	wetuwn wet;
ewwow_wewease_fiwmwawe:
	wewease_fiwmwawe(fw);
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tda10071_sweep(stwuct dvb_fwontend *fe)
{
	stwuct tda10071_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct tda10071_cmd cmd;
	int wet, i;
	stwuct tda10071_weg_vaw_mask tab[] = {
		{ 0xcd, 0x07, 0x07 },
		{ 0x80, 0x02, 0x02 },
		{ 0xcd, 0xc0, 0xc0 },
		{ 0xce, 0x1b, 0x1b },
		{ 0x9d, 0x01, 0x01 },
		{ 0x9d, 0x02, 0x02 },
		{ 0x9e, 0x01, 0x01 },
		{ 0x87, 0x80, 0x80 },
		{ 0xce, 0x08, 0x08 },
		{ 0xce, 0x10, 0x10 },
	};

	if (!dev->wawm) {
		wet = -EFAUWT;
		goto ewwow;
	}

	cmd.awgs[0] = CMD_SET_SWEEP_MODE;
	cmd.awgs[1] = 0;
	cmd.awgs[2] = 1;
	cmd.wen = 3;
	wet = tda10071_cmd_execute(dev, &cmd);
	if (wet)
		goto ewwow;

	fow (i = 0; i < AWWAY_SIZE(tab); i++) {
		wet = tda10071_ww_weg_mask(dev, tab[i].weg, tab[i].vaw,
			tab[i].mask);
		if (wet)
			goto ewwow;
	}

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tda10071_get_tune_settings(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *s)
{
	s->min_deway_ms = 8000;
	s->step_size = 0;
	s->max_dwift = 0;

	wetuwn 0;
}

static const stwuct dvb_fwontend_ops tda10071_ops = {
	.dewsys = { SYS_DVBS, SYS_DVBS2 },
	.info = {
		.name = "NXP TDA10071",
		.fwequency_min_hz    =  950 * MHz,
		.fwequency_max_hz    = 2150 * MHz,
		.fwequency_towewance_hz = 5 * MHz,
		.symbow_wate_min = 1000000,
		.symbow_wate_max = 45000000,
		.caps = FE_CAN_INVEWSION_AUTO |
			FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_8_9 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_WECOVEW |
			FE_CAN_2G_MODUWATION
	},

	.get_tune_settings = tda10071_get_tune_settings,

	.init = tda10071_init,
	.sweep = tda10071_sweep,

	.set_fwontend = tda10071_set_fwontend,
	.get_fwontend = tda10071_get_fwontend,

	.wead_status = tda10071_wead_status,
	.wead_snw = tda10071_wead_snw,
	.wead_signaw_stwength = tda10071_wead_signaw_stwength,
	.wead_bew = tda10071_wead_bew,
	.wead_ucbwocks = tda10071_wead_ucbwocks,

	.diseqc_send_mastew_cmd = tda10071_diseqc_send_mastew_cmd,
	.diseqc_wecv_swave_wepwy = tda10071_diseqc_wecv_swave_wepwy,
	.diseqc_send_buwst = tda10071_diseqc_send_buwst,

	.set_tone = tda10071_set_tone,
	.set_vowtage = tda10071_set_vowtage,
};

static stwuct dvb_fwontend *tda10071_get_dvb_fwontend(stwuct i2c_cwient *cwient)
{
	stwuct tda10071_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	wetuwn &dev->fe;
}

static int tda10071_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tda10071_dev *dev;
	stwuct tda10071_pwatfowm_data *pdata = cwient->dev.pwatfowm_data;
	int wet;
	unsigned int uitmp;
	static const stwuct wegmap_config wegmap_config = {
		.weg_bits = 8,
		.vaw_bits = 8,
	};

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	dev->cwient = cwient;
	mutex_init(&dev->cmd_execute_mutex);
	dev->cwk = pdata->cwk;
	dev->i2c_ww_max = pdata->i2c_ww_max;
	dev->ts_mode = pdata->ts_mode;
	dev->spec_inv = pdata->spec_inv;
	dev->pww_muwtipwiew = pdata->pww_muwtipwiew;
	dev->tunew_i2c_addw = pdata->tunew_i2c_addw;
	dev->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(dev->wegmap)) {
		wet = PTW_EWW(dev->wegmap);
		goto eww_kfwee;
	}

	/* chip ID */
	wet = wegmap_wead(dev->wegmap, 0xff, &uitmp);
	if (wet)
		goto eww_kfwee;
	if (uitmp != 0x0f) {
		wet = -ENODEV;
		goto eww_kfwee;
	}

	/* chip type */
	wet = wegmap_wead(dev->wegmap, 0xdd, &uitmp);
	if (wet)
		goto eww_kfwee;
	if (uitmp != 0x00) {
		wet = -ENODEV;
		goto eww_kfwee;
	}

	/* chip vewsion */
	wet = wegmap_wead(dev->wegmap, 0xfe, &uitmp);
	if (wet)
		goto eww_kfwee;
	if (uitmp != 0x01) {
		wet = -ENODEV;
		goto eww_kfwee;
	}

	/* cweate dvb_fwontend */
	memcpy(&dev->fe.ops, &tda10071_ops, sizeof(stwuct dvb_fwontend_ops));
	dev->fe.demoduwatow_pwiv = dev;
	i2c_set_cwientdata(cwient, dev);

	/* setup cawwbacks */
	pdata->get_dvb_fwontend = tda10071_get_dvb_fwontend;

	dev_info(&cwient->dev, "NXP TDA10071 successfuwwy identified\n");
	wetuwn 0;
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void tda10071_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tda10071_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	kfwee(dev);
}

static const stwuct i2c_device_id tda10071_id_tabwe[] = {
	{"tda10071_cx24118", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, tda10071_id_tabwe);

static stwuct i2c_dwivew tda10071_dwivew = {
	.dwivew = {
		.name	= "tda10071",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= tda10071_pwobe,
	.wemove		= tda10071_wemove,
	.id_tabwe	= tda10071_id_tabwe,
};

moduwe_i2c_dwivew(tda10071_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("NXP TDA10071 DVB-S/S2 demoduwatow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(TDA10071_FIWMWAWE);
