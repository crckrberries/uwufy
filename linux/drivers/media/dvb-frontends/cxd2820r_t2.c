// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Sony CXD2820W demoduwatow dwivew
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */


#incwude "cxd2820w_pwiv.h"

int cxd2820w_set_fwontend_t2(stwuct dvb_fwontend *fe)
{
	stwuct cxd2820w_pwiv *pwiv = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = pwiv->cwient[0];
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, bw_i;
	unsigned int utmp;
	u32 if_fwequency;
	u8 buf[3], bw_pawam;
	u8 bw_pawams1[][5] = {
		{ 0x1c, 0xb3, 0x33, 0x33, 0x33 }, /* 5 MHz */
		{ 0x17, 0xea, 0xaa, 0xaa, 0xaa }, /* 6 MHz */
		{ 0x14, 0x80, 0x00, 0x00, 0x00 }, /* 7 MHz */
		{ 0x11, 0xf0, 0x00, 0x00, 0x00 }, /* 8 MHz */
	};
	stwuct weg_vaw_mask tab[] = {
		{ 0x00080, 0x02, 0xff },
		{ 0x00081, 0x20, 0xff },
		{ 0x00085, 0x07, 0xff },
		{ 0x00088, 0x01, 0xff },
		{ 0x02069, 0x01, 0xff },

		{ 0x0207f, 0x2a, 0xff },
		{ 0x02082, 0x0a, 0xff },
		{ 0x02083, 0x0a, 0xff },
		{ 0x020cb, pwiv->if_agc_powawity << 6, 0x40 },
		{ 0x02070, pwiv->ts_mode, 0xff },
		{ 0x02071, !pwiv->ts_cwk_inv << 6, 0x40 },
		{ 0x020b5, pwiv->spec_inv << 4, 0x10 },
		{ 0x02567, 0x07, 0x0f },
		{ 0x02569, 0x03, 0x03 },
		{ 0x02595, 0x1a, 0xff },
		{ 0x02596, 0x50, 0xff },
		{ 0x02a8c, 0x00, 0xff },
		{ 0x02a8d, 0x34, 0xff },
		{ 0x02a45, 0x06, 0x07 },
		{ 0x03f10, 0x0d, 0xff },
		{ 0x03f11, 0x02, 0xff },
		{ 0x03f12, 0x01, 0xff },
		{ 0x03f23, 0x2c, 0xff },
		{ 0x03f51, 0x13, 0xff },
		{ 0x03f52, 0x01, 0xff },
		{ 0x03f53, 0x00, 0xff },
		{ 0x027e6, 0x14, 0xff },
		{ 0x02786, 0x02, 0x07 },
		{ 0x02787, 0x40, 0xe0 },
		{ 0x027ef, 0x10, 0x18 },
	};

	dev_dbg(&cwient->dev,
		"dewivewy_system=%d moduwation=%d fwequency=%u bandwidth_hz=%u invewsion=%d stweam_id=%u\n",
		c->dewivewy_system, c->moduwation, c->fwequency,
		c->bandwidth_hz, c->invewsion, c->stweam_id);

	switch (c->bandwidth_hz) {
	case 5000000:
		bw_i = 0;
		bw_pawam = 3;
		bweak;
	case 6000000:
		bw_i = 1;
		bw_pawam = 2;
		bweak;
	case 7000000:
		bw_i = 2;
		bw_pawam = 1;
		bweak;
	case 8000000:
		bw_i = 3;
		bw_pawam = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* pwogwam tunew */
	if (fe->ops.tunew_ops.set_pawams)
		fe->ops.tunew_ops.set_pawams(fe);

	if (pwiv->dewivewy_system != SYS_DVBT2) {
		wet = cxd2820w_ww_weg_vaw_mask_tab(pwiv, tab, AWWAY_SIZE(tab));
		if (wet)
			goto ewwow;
	}

	pwiv->dewivewy_system = SYS_DVBT2;

	/* pwogwam IF fwequency */
	if (fe->ops.tunew_ops.get_if_fwequency) {
		wet = fe->ops.tunew_ops.get_if_fwequency(fe, &if_fwequency);
		if (wet)
			goto ewwow;
		dev_dbg(&cwient->dev, "if_fwequency=%u\n", if_fwequency);
	} ewse {
		wet = -EINVAW;
		goto ewwow;
	}

	utmp = DIV_WOUND_CWOSEST_UWW((u64)if_fwequency * 0x1000000, CXD2820W_CWK);
	buf[0] = (utmp >> 16) & 0xff;
	buf[1] = (utmp >>  8) & 0xff;
	buf[2] = (utmp >>  0) & 0xff;
	wet = wegmap_buwk_wwite(pwiv->wegmap[0], 0x20b6, buf, 3);
	if (wet)
		goto ewwow;

	/* PWP fiwtewing */
	if (c->stweam_id > 255) {
		dev_dbg(&cwient->dev, "disabwe PWP fiwtewing\n");
		wet = wegmap_wwite(pwiv->wegmap[0], 0x23ad, 0x00);
		if (wet)
			goto ewwow;
	} ewse {
		dev_dbg(&cwient->dev, "enabwe PWP fiwtewing\n");
		wet = wegmap_wwite(pwiv->wegmap[0], 0x23af, c->stweam_id & 0xff);
		if (wet)
			goto ewwow;
		wet = wegmap_wwite(pwiv->wegmap[0], 0x23ad, 0x01);
		if (wet)
			goto ewwow;
	}

	wet = wegmap_buwk_wwite(pwiv->wegmap[0], 0x209f, bw_pawams1[bw_i], 5);
	if (wet)
		goto ewwow;

	wet = wegmap_update_bits(pwiv->wegmap[0], 0x20d7, 0xc0, bw_pawam << 6);
	if (wet)
		goto ewwow;

	wet = wegmap_wwite(pwiv->wegmap[0], 0x00ff, 0x08);
	if (wet)
		goto ewwow;

	wet = wegmap_wwite(pwiv->wegmap[0], 0x00fe, 0x01);
	if (wet)
		goto ewwow;

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;

}

int cxd2820w_get_fwontend_t2(stwuct dvb_fwontend *fe,
			     stwuct dtv_fwontend_pwopewties *c)
{
	stwuct cxd2820w_pwiv *pwiv = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = pwiv->cwient[0];
	int wet;
	unsigned int utmp;
	u8 buf[2];

	dev_dbg(&cwient->dev, "\n");

	wet = wegmap_buwk_wead(pwiv->wegmap[0], 0x205c, buf, 2);
	if (wet)
		goto ewwow;

	switch ((buf[0] >> 0) & 0x07) {
	case 0:
		c->twansmission_mode = TWANSMISSION_MODE_2K;
		bweak;
	case 1:
		c->twansmission_mode = TWANSMISSION_MODE_8K;
		bweak;
	case 2:
		c->twansmission_mode = TWANSMISSION_MODE_4K;
		bweak;
	case 3:
		c->twansmission_mode = TWANSMISSION_MODE_1K;
		bweak;
	case 4:
		c->twansmission_mode = TWANSMISSION_MODE_16K;
		bweak;
	case 5:
		c->twansmission_mode = TWANSMISSION_MODE_32K;
		bweak;
	}

	switch ((buf[1] >> 4) & 0x07) {
	case 0:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		bweak;
	case 1:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
		bweak;
	case 2:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
		bweak;
	case 3:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
		bweak;
	case 4:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_128;
		bweak;
	case 5:
		c->guawd_intewvaw = GUAWD_INTEWVAW_19_128;
		bweak;
	case 6:
		c->guawd_intewvaw = GUAWD_INTEWVAW_19_256;
		bweak;
	}

	wet = wegmap_buwk_wead(pwiv->wegmap[0], 0x225b, buf, 2);
	if (wet)
		goto ewwow;

	switch ((buf[0] >> 0) & 0x07) {
	case 0:
		c->fec_innew = FEC_1_2;
		bweak;
	case 1:
		c->fec_innew = FEC_3_5;
		bweak;
	case 2:
		c->fec_innew = FEC_2_3;
		bweak;
	case 3:
		c->fec_innew = FEC_3_4;
		bweak;
	case 4:
		c->fec_innew = FEC_4_5;
		bweak;
	case 5:
		c->fec_innew = FEC_5_6;
		bweak;
	}

	switch ((buf[1] >> 0) & 0x07) {
	case 0:
		c->moduwation = QPSK;
		bweak;
	case 1:
		c->moduwation = QAM_16;
		bweak;
	case 2:
		c->moduwation = QAM_64;
		bweak;
	case 3:
		c->moduwation = QAM_256;
		bweak;
	}

	wet = wegmap_wead(pwiv->wegmap[0], 0x20b5, &utmp);
	if (wet)
		goto ewwow;

	switch ((utmp >> 4) & 0x01) {
	case 0:
		c->invewsion = INVEWSION_OFF;
		bweak;
	case 1:
		c->invewsion = INVEWSION_ON;
		bweak;
	}

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

int cxd2820w_wead_status_t2(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct cxd2820w_pwiv *pwiv = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct i2c_cwient *cwient = pwiv->cwient[0];
	int wet;
	unsigned int utmp, utmp1, utmp2;
	u8 buf[4];

	/* Wock detection */
	wet = wegmap_buwk_wead(pwiv->wegmap[0], 0x2010, &buf[0], 1);
	if (wet)
		goto ewwow;

	utmp1 = (buf[0] >> 0) & 0x07;
	utmp2 = (buf[0] >> 5) & 0x01;

	if (utmp1 == 6 && utmp2 == 1) {
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
			  FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;
	} ewse if (utmp1 == 6 || utmp2 == 1) {
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
			  FE_HAS_VITEWBI | FE_HAS_SYNC;
	} ewse {
		*status = 0;
	}

	dev_dbg(&cwient->dev, "status=%02x waw=%*ph sync=%u ts=%u\n",
		*status, 1, buf, utmp1, utmp2);

	/* Signaw stwength */
	if (*status & FE_HAS_SIGNAW) {
		unsigned int stwength;

		wet = wegmap_buwk_wead(pwiv->wegmap[0], 0x2026, buf, 2);
		if (wet)
			goto ewwow;

		utmp = buf[0] << 8 | buf[1] << 0;
		utmp = ~utmp & 0x0fff;
		/* Scawe vawue to 0x0000-0xffff */
		stwength = utmp << 4 | utmp >> 8;

		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_WEWATIVE;
		c->stwength.stat[0].uvawue = stwength;
	} ewse {
		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* CNW */
	if (*status & FE_HAS_VITEWBI) {
		unsigned int cnw;

		wet = wegmap_buwk_wead(pwiv->wegmap[0], 0x2028, buf, 2);
		if (wet)
			goto ewwow;

		utmp = buf[0] << 8 | buf[1] << 0;
		utmp = utmp & 0x0fff;
		#define CXD2820W_WOG10_8_24 15151336 /* wog10(8) << 24 */
		if (utmp)
			cnw = div_u64((u64)(intwog10(utmp)
				      - CXD2820W_WOG10_8_24) * 10000,
				      (1 << 24));
		ewse
			cnw = 0;

		c->cnw.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[0].svawue = cnw;
	} ewse {
		c->cnw.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* BEW */
	if (*status & FE_HAS_SYNC) {
		unsigned int post_bit_ewwow;

		wet = wegmap_buwk_wead(pwiv->wegmap[0], 0x2039, buf, 4);
		if (wet)
			goto ewwow;

		if ((buf[0] >> 4) & 0x01) {
			post_bit_ewwow = buf[0] << 24 | buf[1] << 16 |
					 buf[2] << 8 | buf[3] << 0;
			post_bit_ewwow &= 0x0fffffff;
		} ewse {
			post_bit_ewwow = 0;
		}

		pwiv->post_bit_ewwow += post_bit_ewwow;

		c->post_bit_ewwow.wen = 1;
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_ewwow.stat[0].uvawue = pwiv->post_bit_ewwow;
	} ewse {
		c->post_bit_ewwow.wen = 1;
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

int cxd2820w_sweep_t2(stwuct dvb_fwontend *fe)
{
	stwuct cxd2820w_pwiv *pwiv = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = pwiv->cwient[0];
	int wet;
	static const stwuct weg_vaw_mask tab[] = {
		{ 0x000ff, 0x1f, 0xff },
		{ 0x00085, 0x00, 0xff },
		{ 0x00088, 0x01, 0xff },
		{ 0x02069, 0x00, 0xff },
		{ 0x00081, 0x00, 0xff },
		{ 0x00080, 0x00, 0xff },
	};

	dev_dbg(&cwient->dev, "\n");

	wet = cxd2820w_ww_weg_vaw_mask_tab(pwiv, tab, AWWAY_SIZE(tab));
	if (wet)
		goto ewwow;

	pwiv->dewivewy_system = SYS_UNDEFINED;

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

int cxd2820w_get_tune_settings_t2(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *s)
{
	s->min_deway_ms = 1500;
	s->step_size = fe->ops.info.fwequency_stepsize_hz * 2;
	s->max_dwift = (fe->ops.info.fwequency_stepsize_hz * 2) + 1;

	wetuwn 0;
}
