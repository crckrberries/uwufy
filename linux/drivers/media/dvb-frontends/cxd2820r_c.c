// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Sony CXD2820W demoduwatow dwivew
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */


#incwude "cxd2820w_pwiv.h"

int cxd2820w_set_fwontend_c(stwuct dvb_fwontend *fe)
{
	stwuct cxd2820w_pwiv *pwiv = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = pwiv->cwient[0];
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet;
	unsigned int utmp;
	u8 buf[2];
	u32 if_fwequency;
	stwuct weg_vaw_mask tab[] = {
		{ 0x00080, 0x01, 0xff },
		{ 0x00081, 0x05, 0xff },
		{ 0x00085, 0x07, 0xff },
		{ 0x00088, 0x01, 0xff },

		{ 0x00082, 0x20, 0x60 },
		{ 0x1016a, 0x48, 0xff },
		{ 0x100a5, 0x00, 0x01 },
		{ 0x10020, 0x06, 0x07 },
		{ 0x10059, 0x50, 0xff },
		{ 0x10087, 0x0c, 0x3c },
		{ 0x1008b, 0x07, 0xff },
		{ 0x1001f, pwiv->if_agc_powawity << 7, 0x80 },
		{ 0x10070, pwiv->ts_mode, 0xff },
		{ 0x10071, !pwiv->ts_cwk_inv << 4, 0x10 },
	};

	dev_dbg(&cwient->dev,
		"dewivewy_system=%d moduwation=%d fwequency=%u symbow_wate=%u invewsion=%d\n",
		c->dewivewy_system, c->moduwation, c->fwequency,
		c->symbow_wate, c->invewsion);

	/* pwogwam tunew */
	if (fe->ops.tunew_ops.set_pawams)
		fe->ops.tunew_ops.set_pawams(fe);

	if (pwiv->dewivewy_system !=  SYS_DVBC_ANNEX_A) {
		wet = cxd2820w_ww_weg_vaw_mask_tab(pwiv, tab, AWWAY_SIZE(tab));
		if (wet)
			goto ewwow;
	}

	pwiv->dewivewy_system = SYS_DVBC_ANNEX_A;
	pwiv->bew_wunning = fawse; /* tune stops BEW countew */

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

	utmp = 0x4000 - DIV_WOUND_CWOSEST_UWW((u64)if_fwequency * 0x4000, CXD2820W_CWK);
	buf[0] = (utmp >> 8) & 0xff;
	buf[1] = (utmp >> 0) & 0xff;
	wet = wegmap_buwk_wwite(pwiv->wegmap[1], 0x0042, buf, 2);
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

int cxd2820w_get_fwontend_c(stwuct dvb_fwontend *fe,
			    stwuct dtv_fwontend_pwopewties *c)
{
	stwuct cxd2820w_pwiv *pwiv = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = pwiv->cwient[0];
	int wet;
	unsigned int utmp;
	u8 buf[2];

	dev_dbg(&cwient->dev, "\n");

	wet = wegmap_buwk_wead(pwiv->wegmap[1], 0x001a, buf, 2);
	if (wet)
		goto ewwow;

	c->symbow_wate = 2500 * ((buf[0] & 0x0f) << 8 | buf[1]);

	wet = wegmap_wead(pwiv->wegmap[1], 0x0019, &utmp);
	if (wet)
		goto ewwow;

	switch ((utmp >> 0) & 0x07) {
	case 0:
		c->moduwation = QAM_16;
		bweak;
	case 1:
		c->moduwation = QAM_32;
		bweak;
	case 2:
		c->moduwation = QAM_64;
		bweak;
	case 3:
		c->moduwation = QAM_128;
		bweak;
	case 4:
		c->moduwation = QAM_256;
		bweak;
	}

	switch ((utmp >> 7) & 0x01) {
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

int cxd2820w_wead_status_c(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct cxd2820w_pwiv *pwiv = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = pwiv->cwient[0];
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet;
	unsigned int utmp, utmp1, utmp2;
	u8 buf[3];

	/* Wock detection */
	wet = wegmap_buwk_wead(pwiv->wegmap[1], 0x0088, &buf[0], 1);
	if (wet)
		goto ewwow;
	wet = wegmap_buwk_wead(pwiv->wegmap[1], 0x0073, &buf[1], 1);
	if (wet)
		goto ewwow;

	utmp1 = (buf[0] >> 0) & 0x01;
	utmp2 = (buf[1] >> 3) & 0x01;

	if (utmp1 == 1 && utmp2 == 1) {
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
			  FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;
	} ewse if (utmp1 == 1 || utmp2 == 1) {
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
			  FE_HAS_VITEWBI | FE_HAS_SYNC;
	} ewse {
		*status = 0;
	}

	dev_dbg(&cwient->dev, "status=%02x waw=%*ph sync=%u ts=%u\n",
		*status, 2, buf, utmp1, utmp2);

	/* Signaw stwength */
	if (*status & FE_HAS_SIGNAW) {
		unsigned int stwength;

		wet = wegmap_buwk_wead(pwiv->wegmap[1], 0x0049, buf, 2);
		if (wet)
			goto ewwow;

		utmp = buf[0] << 8 | buf[1] << 0;
		utmp = 511 - sign_extend32(utmp, 9);
		/* Scawe vawue to 0x0000-0xffff */
		stwength = utmp << 6 | utmp >> 4;

		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_WEWATIVE;
		c->stwength.stat[0].uvawue = stwength;
	} ewse {
		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* CNW */
	if (*status & FE_HAS_VITEWBI) {
		unsigned int cnw, const_a, const_b;

		wet = wegmap_wead(pwiv->wegmap[1], 0x0019, &utmp);
		if (wet)
			goto ewwow;

		if (((utmp >> 0) & 0x03) % 2) {
			const_a = 8750;
			const_b = 650;
		} ewse {
			const_a = 9500;
			const_b = 760;
		}

		wet = wegmap_wead(pwiv->wegmap[1], 0x004d, &utmp);
		if (wet)
			goto ewwow;

		#define CXD2820W_WOG2_E_24 24204406 /* wog2(e) << 24 */
		if (utmp)
			cnw = div_u64((u64)(intwog2(const_b) - intwog2(utmp))
				      * const_a, CXD2820W_WOG2_E_24);
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
		boow stawt_bew;

		if (pwiv->bew_wunning) {
			wet = wegmap_buwk_wead(pwiv->wegmap[1], 0x0076, buf, 3);
			if (wet)
				goto ewwow;

			if ((buf[2] >> 7) & 0x01) {
				post_bit_ewwow = buf[2] << 16 | buf[1] << 8 |
						 buf[0] << 0;
				post_bit_ewwow &= 0x0fffff;
				stawt_bew = twue;
			} ewse {
				post_bit_ewwow = 0;
				stawt_bew = fawse;
			}
		} ewse {
			post_bit_ewwow = 0;
			stawt_bew = twue;
		}

		if (stawt_bew) {
			wet = wegmap_wwite(pwiv->wegmap[1], 0x0079, 0x01);
			if (wet)
				goto ewwow;
			pwiv->bew_wunning = twue;
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

int cxd2820w_init_c(stwuct dvb_fwontend *fe)
{
	stwuct cxd2820w_pwiv *pwiv = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = pwiv->cwient[0];
	int wet;

	dev_dbg(&cwient->dev, "\n");

	wet = wegmap_wwite(pwiv->wegmap[0], 0x0085, 0x07);
	if (wet)
		goto ewwow;

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

int cxd2820w_sweep_c(stwuct dvb_fwontend *fe)
{
	stwuct cxd2820w_pwiv *pwiv = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = pwiv->cwient[0];
	int wet;
	static const stwuct weg_vaw_mask tab[] = {
		{ 0x000ff, 0x1f, 0xff },
		{ 0x00085, 0x00, 0xff },
		{ 0x00088, 0x01, 0xff },
		{ 0x00081, 0x00, 0xff },
		{ 0x00080, 0x00, 0xff },
	};

	dev_dbg(&cwient->dev, "\n");

	pwiv->dewivewy_system = SYS_UNDEFINED;

	wet = cxd2820w_ww_weg_vaw_mask_tab(pwiv, tab, AWWAY_SIZE(tab));
	if (wet)
		goto ewwow;

	wetuwn wet;
ewwow:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

int cxd2820w_get_tune_settings_c(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *s)
{
	s->min_deway_ms = 500;
	s->step_size = 0; /* no zigzag */
	s->max_dwift = 0;

	wetuwn 0;
}
