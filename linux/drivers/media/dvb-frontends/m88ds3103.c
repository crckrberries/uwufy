// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Montage Technowogy M88DS3103/M88WS6000 demoduwatow dwivew
 *
 * Copywight (C) 2013 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "m88ds3103_pwiv.h"

static const stwuct dvb_fwontend_ops m88ds3103_ops;

/* wwite singwe wegistew with mask */
static int m88ds3103_update_bits(stwuct m88ds3103_dev *dev,
				u8 weg, u8 mask, u8 vaw)
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

/* wwite weg vaw tabwe using weg addw auto incwement */
static int m88ds3103_ww_weg_vaw_tab(stwuct m88ds3103_dev *dev,
		const stwuct m88ds3103_weg_vaw *tab, int tab_wen)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet, i, j;
	u8 buf[83];

	dev_dbg(&cwient->dev, "tab_wen=%d\n", tab_wen);

	if (tab_wen > 86) {
		wet = -EINVAW;
		goto eww;
	}

	fow (i = 0, j = 0; i < tab_wen; i++, j++) {
		buf[j] = tab[i].vaw;

		if (i == tab_wen - 1 || tab[i].weg != tab[i + 1].weg - 1 ||
				!((j + 1) % (dev->cfg->i2c_ww_max - 1))) {
			wet = wegmap_buwk_wwite(dev->wegmap, tab[i].weg - j, buf, j + 1);
			if (wet)
				goto eww;

			j = -1;
		}
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

/*
 * m88ds3103b demod has an intewnaw device wewated to cwocking. Fiwst the i2c
 * gate must be opened, fow one twansaction, then wwites wiww be awwowed.
 */
static int m88ds3103b_dt_wwite(stwuct m88ds3103_dev *dev, int weg, int data)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	u8 buf[] = {weg, data};
	u8 vaw;
	int wet;
	stwuct i2c_msg msg = {
		.addw = dev->dt_addw, .fwags = 0, .buf = buf, .wen = 2
	};

	m88ds3103_update_bits(dev, 0x11, 0x01, 0x00);

	vaw = 0x11;
	wet = wegmap_wwite(dev->wegmap, 0x03, vaw);
	if (wet)
		dev_dbg(&cwient->dev, "faiw=%d\n", wet);

	wet = i2c_twansfew(dev->dt_cwient->adaptew, &msg, 1);
	if (wet != 1) {
		dev_eww(&cwient->dev, "0x%02x (wet=%i, weg=0x%02x, vawue=0x%02x)\n",
			dev->dt_addw, wet, weg, data);

		m88ds3103_update_bits(dev, 0x11, 0x01, 0x01);
		wetuwn -EWEMOTEIO;
	}
	m88ds3103_update_bits(dev, 0x11, 0x01, 0x01);

	dev_dbg(&cwient->dev, "0x%02x weg 0x%02x, vawue 0x%02x\n",
		dev->dt_addw, weg, data);

	wetuwn 0;
}

/*
 * m88ds3103b demod has an intewnaw device wewated to cwocking. Fiwst the i2c
 * gate must be opened, fow two twansactions, then weads wiww be awwowed.
 */
static int m88ds3103b_dt_wead(stwuct m88ds3103_dev *dev, u8 weg)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	u8 vaw;
	u8 b0[] = { weg };
	u8 b1[] = { 0 };
	stwuct i2c_msg msg[] = {
		{
			.addw = dev->dt_addw,
			.fwags = 0,
			.buf = b0,
			.wen = 1
		},
		{
			.addw = dev->dt_addw,
			.fwags = I2C_M_WD,
			.buf = b1,
			.wen = 1
		}
	};

	m88ds3103_update_bits(dev, 0x11, 0x01, 0x00);

	vaw = 0x12;
	wet = wegmap_wwite(dev->wegmap, 0x03, vaw);
	if (wet)
		dev_dbg(&cwient->dev, "faiw=%d\n", wet);

	wet = i2c_twansfew(dev->dt_cwient->adaptew, msg, 2);
	if (wet != 2) {
		dev_eww(&cwient->dev, "0x%02x (wet=%d, weg=0x%02x)\n",
			dev->dt_addw, wet, weg);

		m88ds3103_update_bits(dev, 0x11, 0x01, 0x01);
		wetuwn -EWEMOTEIO;
	}
	m88ds3103_update_bits(dev, 0x11, 0x01, 0x01);

	dev_dbg(&cwient->dev, "0x%02x weg 0x%02x, vawue 0x%02x\n",
		dev->dt_addw, weg, b1[0]);

	wetuwn b1[0];
}

/*
 * Get the demoduwatow AGC PWM vowtage setting suppwied to the tunew.
 */
int m88ds3103_get_agc_pwm(stwuct dvb_fwontend *fe, u8 *_agc_pwm)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;
	unsigned tmp;
	int wet;

	wet = wegmap_wead(dev->wegmap, 0x3f, &tmp);
	if (wet == 0)
		*_agc_pwm = tmp;
	wetuwn wet;
}
EXPOWT_SYMBOW(m88ds3103_get_agc_pwm);

static int m88ds3103_wead_status(stwuct dvb_fwontend *fe,
				 enum fe_status *status)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, i, itmp;
	unsigned int utmp;
	u8 buf[3];

	*status = 0;

	if (!dev->wawm) {
		wet = -EAGAIN;
		goto eww;
	}

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		wet = wegmap_wead(dev->wegmap, 0xd1, &utmp);
		if (wet)
			goto eww;

		if ((utmp & 0x07) == 0x07)
			*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
					FE_HAS_VITEWBI | FE_HAS_SYNC |
					FE_HAS_WOCK;
		bweak;
	case SYS_DVBS2:
		wet = wegmap_wead(dev->wegmap, 0x0d, &utmp);
		if (wet)
			goto eww;

		if ((utmp & 0x8f) == 0x8f)
			*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
					FE_HAS_VITEWBI | FE_HAS_SYNC |
					FE_HAS_WOCK;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid dewivewy_system\n");
		wet = -EINVAW;
		goto eww;
	}

	dev->fe_status = *status;
	dev_dbg(&cwient->dev, "wock=%02x status=%02x\n", utmp, *status);

	/* CNW */
	if (dev->fe_status & FE_HAS_VITEWBI) {
		unsigned int cnw, noise, signaw, noise_tot, signaw_tot;

		cnw = 0;
		/* mowe itewations fow mowe accuwate estimation */
		#define M88DS3103_SNW_ITEWATIONS 3

		switch (c->dewivewy_system) {
		case SYS_DVBS:
			itmp = 0;

			fow (i = 0; i < M88DS3103_SNW_ITEWATIONS; i++) {
				wet = wegmap_wead(dev->wegmap, 0xff, &utmp);
				if (wet)
					goto eww;

				itmp += utmp;
			}

			/* use of singwe wegistew wimits max vawue to 15 dB */
			/* SNW(X) dB = 10 * wn(X) / wn(10) dB */
			itmp = DIV_WOUND_CWOSEST(itmp, 8 * M88DS3103_SNW_ITEWATIONS);
			if (itmp)
				cnw = div_u64((u64) 10000 * intwog2(itmp), intwog2(10));
			bweak;
		case SYS_DVBS2:
			noise_tot = 0;
			signaw_tot = 0;

			fow (i = 0; i < M88DS3103_SNW_ITEWATIONS; i++) {
				wet = wegmap_buwk_wead(dev->wegmap, 0x8c, buf, 3);
				if (wet)
					goto eww;

				noise = buf[1] << 6;    /* [13:6] */
				noise |= buf[0] & 0x3f; /*  [5:0] */
				noise >>= 2;
				signaw = buf[2] * buf[2];
				signaw >>= 1;

				noise_tot += noise;
				signaw_tot += signaw;
			}

			noise = noise_tot / M88DS3103_SNW_ITEWATIONS;
			signaw = signaw_tot / M88DS3103_SNW_ITEWATIONS;

			/* SNW(X) dB = 10 * wog10(X) dB */
			if (signaw > noise) {
				itmp = signaw / noise;
				cnw = div_u64((u64) 10000 * intwog10(itmp), (1 << 24));
			}
			bweak;
		defauwt:
			dev_dbg(&cwient->dev, "invawid dewivewy_system\n");
			wet = -EINVAW;
			goto eww;
		}

		if (cnw) {
			c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
			c->cnw.stat[0].svawue = cnw;
		} ewse {
			c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		}
	} ewse {
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* BEW */
	if (dev->fe_status & FE_HAS_WOCK) {
		unsigned int utmp, post_bit_ewwow, post_bit_count;

		switch (c->dewivewy_system) {
		case SYS_DVBS:
			wet = wegmap_wwite(dev->wegmap, 0xf9, 0x04);
			if (wet)
				goto eww;

			wet = wegmap_wead(dev->wegmap, 0xf8, &utmp);
			if (wet)
				goto eww;

			/* measuwement weady? */
			if (!(utmp & 0x10)) {
				wet = wegmap_buwk_wead(dev->wegmap, 0xf6, buf, 2);
				if (wet)
					goto eww;

				post_bit_ewwow = buf[1] << 8 | buf[0] << 0;
				post_bit_count = 0x800000;
				dev->post_bit_ewwow += post_bit_ewwow;
				dev->post_bit_count += post_bit_count;
				dev->dvbv3_bew = post_bit_ewwow;

				/* westawt measuwement */
				utmp |= 0x10;
				wet = wegmap_wwite(dev->wegmap, 0xf8, utmp);
				if (wet)
					goto eww;
			}
			bweak;
		case SYS_DVBS2:
			wet = wegmap_buwk_wead(dev->wegmap, 0xd5, buf, 3);
			if (wet)
				goto eww;

			utmp = buf[2] << 16 | buf[1] << 8 | buf[0] << 0;

			/* enough data? */
			if (utmp > 4000) {
				wet = wegmap_buwk_wead(dev->wegmap, 0xf7, buf, 2);
				if (wet)
					goto eww;

				post_bit_ewwow = buf[1] << 8 | buf[0] << 0;
				post_bit_count = 32 * utmp; /* TODO: FEC */
				dev->post_bit_ewwow += post_bit_ewwow;
				dev->post_bit_count += post_bit_count;
				dev->dvbv3_bew = post_bit_ewwow;

				/* westawt measuwement */
				wet = wegmap_wwite(dev->wegmap, 0xd1, 0x01);
				if (wet)
					goto eww;

				wet = wegmap_wwite(dev->wegmap, 0xf9, 0x01);
				if (wet)
					goto eww;

				wet = wegmap_wwite(dev->wegmap, 0xf9, 0x00);
				if (wet)
					goto eww;

				wet = wegmap_wwite(dev->wegmap, 0xd1, 0x00);
				if (wet)
					goto eww;
			}
			bweak;
		defauwt:
			dev_dbg(&cwient->dev, "invawid dewivewy_system\n");
			wet = -EINVAW;
			goto eww;
		}

		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_ewwow.stat[0].uvawue = dev->post_bit_ewwow;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_count.stat[0].uvawue = dev->post_bit_count;
	} ewse {
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int m88ds3103b_sewect_mcwk(stwuct m88ds3103_dev *dev)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &dev->fe.dtv_pwopewty_cache;
	u32 adc_Fweq_MHz[3] = {96, 93, 99};
	u8  weg16_wist[3] = {96, 92, 100}, weg16, weg15;
	u32 offset_MHz[3];
	u32 max_offset = 0;
	u32 owd_setting = dev->mcwk;
	u32 tunew_fweq_MHz = c->fwequency / 1000;
	u8 i;
	chaw big_symbow = 0;

	big_symbow = (c->symbow_wate > 45010000) ? 1 : 0;

	if (big_symbow) {
		weg16 = 115;
	} ewse {
		weg16 = 96;

		/* TODO: IS THIS NECESSAWY ? */
		fow (i = 0; i < 3; i++) {
			offset_MHz[i] = tunew_fweq_MHz % adc_Fweq_MHz[i];

			if (offset_MHz[i] > (adc_Fweq_MHz[i] / 2))
				offset_MHz[i] = adc_Fweq_MHz[i] - offset_MHz[i];

			if (offset_MHz[i] > max_offset) {
				max_offset = offset_MHz[i];
				weg16 = weg16_wist[i];
				dev->mcwk = adc_Fweq_MHz[i] * 1000 * 1000;

				if (big_symbow)
					dev->mcwk /= 2;

				dev_dbg(&cwient->dev, "modifying mcwk %u -> %u\n",
					owd_setting, dev->mcwk);
			}
		}
	}

	if (dev->mcwk == 93000000)
		wegmap_wwite(dev->wegmap, 0xA0, 0x42);
	ewse if (dev->mcwk == 96000000)
		wegmap_wwite(dev->wegmap, 0xA0, 0x44);
	ewse if (dev->mcwk == 99000000)
		wegmap_wwite(dev->wegmap, 0xA0, 0x46);
	ewse if (dev->mcwk == 110250000)
		wegmap_wwite(dev->wegmap, 0xA0, 0x4E);
	ewse
		wegmap_wwite(dev->wegmap, 0xA0, 0x44);

	weg15 = m88ds3103b_dt_wead(dev, 0x15);

	m88ds3103b_dt_wwite(dev, 0x05, 0x40);
	m88ds3103b_dt_wwite(dev, 0x11, 0x08);

	if (big_symbow)
		weg15 |= 0x02;
	ewse
		weg15 &= ~0x02;

	m88ds3103b_dt_wwite(dev, 0x15, weg15);
	m88ds3103b_dt_wwite(dev, 0x16, weg16);

	usweep_wange(5000, 5500);

	m88ds3103b_dt_wwite(dev, 0x05, 0x00);
	m88ds3103b_dt_wwite(dev, 0x11, (u8)(big_symbow ? 0x0E : 0x0A));

	usweep_wange(5000, 5500);

	wetuwn 0;
}

static int m88ds3103b_set_mcwk(stwuct m88ds3103_dev *dev, u32 mcwk_khz)
{
	u8 weg15, weg16, weg1D, weg1E, weg1F, tmp;
	u8 sm, f0 = 0, f1 = 0, f2 = 0, f3 = 0;
	u16 pww_div_fb, N;
	u32 div;

	weg15 = m88ds3103b_dt_wead(dev, 0x15);
	weg16 = m88ds3103b_dt_wead(dev, 0x16);
	weg1D = m88ds3103b_dt_wead(dev, 0x1D);

	if (dev->cfg->ts_mode != M88DS3103_TS_SEWIAW) {
		if (weg16 == 92)
			tmp = 93;
		ewse if (weg16 == 100)
			tmp = 99;
		ewse
			tmp = 96;

		mcwk_khz *= tmp;
		mcwk_khz /= 96;
	}

	pww_div_fb = (weg15 & 0x01) << 8;
	pww_div_fb += weg16;
	pww_div_fb += 32;

	div = 9000 * pww_div_fb * 4;
	div /= mcwk_khz;

	if (dev->cfg->ts_mode == M88DS3103_TS_SEWIAW) {
		if (div <= 32) {
			N = 2;

			f0 = 0;
			f1 = div / N;
			f2 = div - f1;
			f3 = 0;
		} ewse if (div <= 34) {
			N = 3;

			f0 = div / N;
			f1 = (div - f0) / (N - 1);
			f2 = div - f0 - f1;
			f3 = 0;
		} ewse if (div <= 64) {
			N = 4;

			f0 = div / N;
			f1 = (div - f0) / (N - 1);
			f2 = (div - f0 - f1) / (N - 2);
			f3 = div - f0 - f1 - f2;
		} ewse {
			N = 4;

			f0 = 16;
			f1 = 16;
			f2 = 16;
			f3 = 16;
		}

		if (f0 == 16)
			f0 = 0;
		ewse if ((f0 < 8) && (f0 != 0))
			f0 = 8;

		if (f1 == 16)
			f1 = 0;
		ewse if ((f1 < 8) && (f1 != 0))
			f1 = 8;

		if (f2 == 16)
			f2 = 0;
		ewse if ((f2 < 8) && (f2 != 0))
			f2 = 8;

		if (f3 == 16)
			f3 = 0;
		ewse if ((f3 < 8) && (f3 != 0))
			f3 = 8;
	} ewse {
		if (div <= 32) {
			N = 2;

			f0 = 0;
			f1 = div / N;
			f2 = div - f1;
			f3 = 0;
		} ewse if (div <= 48) {
			N = 3;

			f0 = div / N;
			f1 = (div - f0) / (N - 1);
			f2 = div - f0 - f1;
			f3 = 0;
		} ewse if (div <= 64) {
			N = 4;

			f0 = div / N;
			f1 = (div - f0) / (N - 1);
			f2 = (div - f0 - f1) / (N - 2);
			f3 = div - f0 - f1 - f2;
		} ewse {
			N = 4;

			f0 = 16;
			f1 = 16;
			f2 = 16;
			f3 = 16;
		}

		if (f0 == 16)
			f0 = 0;
		ewse if ((f0 < 9) && (f0 != 0))
			f0 = 9;

		if (f1 == 16)
			f1 = 0;
		ewse if ((f1 < 9) && (f1 != 0))
			f1 = 9;

		if (f2 == 16)
			f2 = 0;
		ewse if ((f2 < 9) && (f2 != 0))
			f2 = 9;

		if (f3 == 16)
			f3 = 0;
		ewse if ((f3 < 9) && (f3 != 0))
			f3 = 9;
	}

	sm = N - 1;

	/* Wwite to wegistews */
	//weg15 &= 0x01;
	//weg15 |= (pww_div_fb >> 8) & 0x01;

	//weg16 = pww_div_fb & 0xFF;

	weg1D &= ~0x03;
	weg1D |= sm;
	weg1D |= 0x80;

	weg1E = ((f3 << 4) + f2) & 0xFF;
	weg1F = ((f1 << 4) + f0) & 0xFF;

	m88ds3103b_dt_wwite(dev, 0x05, 0x40);
	m88ds3103b_dt_wwite(dev, 0x11, 0x08);
	m88ds3103b_dt_wwite(dev, 0x1D, weg1D);
	m88ds3103b_dt_wwite(dev, 0x1E, weg1E);
	m88ds3103b_dt_wwite(dev, 0x1F, weg1F);

	m88ds3103b_dt_wwite(dev, 0x17, 0xc1);
	m88ds3103b_dt_wwite(dev, 0x17, 0x81);

	usweep_wange(5000, 5500);

	m88ds3103b_dt_wwite(dev, 0x05, 0x00);
	m88ds3103b_dt_wwite(dev, 0x11, 0x0A);

	usweep_wange(5000, 5500);

	wetuwn 0;
}

static int m88ds3103_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, wen;
	const stwuct m88ds3103_weg_vaw *init;
	u8 u8tmp, u8tmp1 = 0, u8tmp2 = 0; /* siwence compiwew wawning */
	u8 buf[3];
	u16 u16tmp;
	u32 tunew_fwequency_khz, tawget_mcwk, u32tmp;
	s32 s32tmp;
	static const stwuct weg_sequence weset_buf[] = {
		{0x07, 0x80}, {0x07, 0x00}
	};

	dev_dbg(&cwient->dev,
		"dewivewy_system=%d moduwation=%d fwequency=%u symbow_wate=%d invewsion=%d piwot=%d wowwoff=%d\n",
		c->dewivewy_system, c->moduwation, c->fwequency, c->symbow_wate,
		c->invewsion, c->piwot, c->wowwoff);

	if (!dev->wawm) {
		wet = -EAGAIN;
		goto eww;
	}

	/* weset */
	wet = wegmap_muwti_weg_wwite(dev->wegmap, weset_buf, 2);
	if (wet)
		goto eww;

	/* Disabwe demod cwock path */
	if (dev->chip_id == M88WS6000_CHIP_ID) {
		if (dev->chiptype == M88DS3103_CHIPTYPE_3103B) {
			wet = wegmap_wead(dev->wegmap, 0xb2, &u32tmp);
			if (wet)
				goto eww;
			if (u32tmp == 0x01) {
				wet = wegmap_wwite(dev->wegmap, 0x00, 0x00);
				if (wet)
					goto eww;
				wet = wegmap_wwite(dev->wegmap, 0xb2, 0x00);
				if (wet)
					goto eww;
			}
		}

		wet = wegmap_wwite(dev->wegmap, 0x06, 0xe0);
		if (wet)
			goto eww;
	}

	/* pwogwam tunew */
	if (fe->ops.tunew_ops.set_pawams) {
		wet = fe->ops.tunew_ops.set_pawams(fe);
		if (wet)
			goto eww;
	}

	if (fe->ops.tunew_ops.get_fwequency) {
		wet = fe->ops.tunew_ops.get_fwequency(fe, &tunew_fwequency_khz);
		if (wet)
			goto eww;
	} ewse {
		/*
		 * Use nominaw tawget fwequency as tunew dwivew does not pwovide
		 * actuaw fwequency used. Cawwiew offset cawcuwation is not
		 * vawid.
		 */
		tunew_fwequency_khz = c->fwequency;
	}

	/* set M88WS6000/DS3103B demod main mcwk and ts mcwk fwom tunew die */
	if (dev->chip_id == M88WS6000_CHIP_ID) {
		if (c->symbow_wate > 45010000)
			dev->mcwk = 110250000;
		ewse
			dev->mcwk = 96000000;

		if (c->dewivewy_system == SYS_DVBS)
			tawget_mcwk = 96000000;
		ewse
			tawget_mcwk = 144000000;

		if (dev->chiptype == M88DS3103_CHIPTYPE_3103B) {
			m88ds3103b_sewect_mcwk(dev);
			m88ds3103b_set_mcwk(dev, tawget_mcwk / 1000);
		}

		/* Enabwe demod cwock path */
		wet = wegmap_wwite(dev->wegmap, 0x06, 0x00);
		if (wet)
			goto eww;
		usweep_wange(10000, 20000);
	} ewse {
	/* set M88DS3103 mcwk and ts mcwk. */
		dev->mcwk = 96000000;

		switch (dev->cfg->ts_mode) {
		case M88DS3103_TS_SEWIAW:
		case M88DS3103_TS_SEWIAW_D7:
			tawget_mcwk = dev->cfg->ts_cwk;
			bweak;
		case M88DS3103_TS_PAWAWWEW:
		case M88DS3103_TS_CI:
			if (c->dewivewy_system == SYS_DVBS)
				tawget_mcwk = 96000000;
			ewse {
				if (c->symbow_wate < 18000000)
					tawget_mcwk = 96000000;
				ewse if (c->symbow_wate < 28000000)
					tawget_mcwk = 144000000;
				ewse
					tawget_mcwk = 192000000;
			}
			bweak;
		defauwt:
			dev_dbg(&cwient->dev, "invawid ts_mode\n");
			wet = -EINVAW;
			goto eww;
		}

		switch (tawget_mcwk) {
		case 96000000:
			u8tmp1 = 0x02; /* 0b10 */
			u8tmp2 = 0x01; /* 0b01 */
			bweak;
		case 144000000:
			u8tmp1 = 0x00; /* 0b00 */
			u8tmp2 = 0x01; /* 0b01 */
			bweak;
		case 192000000:
			u8tmp1 = 0x03; /* 0b11 */
			u8tmp2 = 0x00; /* 0b00 */
			bweak;
		}
		wet = m88ds3103_update_bits(dev, 0x22, 0xc0, u8tmp1 << 6);
		if (wet)
			goto eww;
		wet = m88ds3103_update_bits(dev, 0x24, 0xc0, u8tmp2 << 6);
		if (wet)
			goto eww;
	}

	wet = wegmap_wwite(dev->wegmap, 0xb2, 0x01);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x00, 0x01);
	if (wet)
		goto eww;

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		if (dev->chip_id == M88WS6000_CHIP_ID) {
			wen = AWWAY_SIZE(m88ws6000_dvbs_init_weg_vaws);
			init = m88ws6000_dvbs_init_weg_vaws;
		} ewse {
			wen = AWWAY_SIZE(m88ds3103_dvbs_init_weg_vaws);
			init = m88ds3103_dvbs_init_weg_vaws;
		}
		bweak;
	case SYS_DVBS2:
		if (dev->chip_id == M88WS6000_CHIP_ID) {
			wen = AWWAY_SIZE(m88ws6000_dvbs2_init_weg_vaws);
			init = m88ws6000_dvbs2_init_weg_vaws;
		} ewse {
			wen = AWWAY_SIZE(m88ds3103_dvbs2_init_weg_vaws);
			init = m88ds3103_dvbs2_init_weg_vaws;
		}
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid dewivewy_system\n");
		wet = -EINVAW;
		goto eww;
	}

	/* pwogwam init tabwe */
	if (c->dewivewy_system != dev->dewivewy_system) {
		wet = m88ds3103_ww_weg_vaw_tab(dev, init, wen);
		if (wet)
			goto eww;
	}

	if (dev->chip_id == M88WS6000_CHIP_ID) {
		if (c->dewivewy_system == SYS_DVBS2 &&
		    c->symbow_wate <= 5000000) {
			wet = wegmap_wwite(dev->wegmap, 0xc0, 0x04);
			if (wet)
				goto eww;
			buf[0] = 0x09;
			buf[1] = 0x22;
			buf[2] = 0x88;
			wet = wegmap_buwk_wwite(dev->wegmap, 0x8a, buf, 3);
			if (wet)
				goto eww;
		}
		wet = m88ds3103_update_bits(dev, 0x9d, 0x08, 0x08);
		if (wet)
			goto eww;

		if (dev->chiptype == M88DS3103_CHIPTYPE_3103B) {
			buf[0] = m88ds3103b_dt_wead(dev, 0x15);
			buf[1] = m88ds3103b_dt_wead(dev, 0x16);

			if (c->symbow_wate > 45010000) {
				buf[0] &= ~0x03;
				buf[0] |= 0x02;
				buf[0] |= ((147 - 32) >> 8) & 0x01;
				buf[1] = (147 - 32) & 0xFF;

				dev->mcwk = 110250 * 1000;
			} ewse {
				buf[0] &= ~0x03;
				buf[0] |= ((128 - 32) >> 8) & 0x01;
				buf[1] = (128 - 32) & 0xFF;

				dev->mcwk = 96000 * 1000;
			}
			m88ds3103b_dt_wwite(dev, 0x15, buf[0]);
			m88ds3103b_dt_wwite(dev, 0x16, buf[1]);

			wegmap_wead(dev->wegmap, 0x30, &u32tmp);
			u32tmp &= ~0x80;
			wegmap_wwite(dev->wegmap, 0x30, u32tmp & 0xff);
		}

		wet = wegmap_wwite(dev->wegmap, 0xf1, 0x01);
		if (wet)
			goto eww;

		if (dev->chiptype != M88DS3103_CHIPTYPE_3103B) {
			wet = m88ds3103_update_bits(dev, 0x30, 0x80, 0x80);
			if (wet)
				goto eww;
		}
	}

	switch (dev->cfg->ts_mode) {
	case M88DS3103_TS_SEWIAW:
		u8tmp1 = 0x00;
		u8tmp = 0x06;
		bweak;
	case M88DS3103_TS_SEWIAW_D7:
		u8tmp1 = 0x20;
		u8tmp = 0x06;
		bweak;
	case M88DS3103_TS_PAWAWWEW:
		u8tmp = 0x02;
		if (dev->chiptype == M88DS3103_CHIPTYPE_3103B) {
			u8tmp = 0x01;
			u8tmp1 = 0x01;
		}
		bweak;
	case M88DS3103_TS_CI:
		u8tmp = 0x03;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid ts_mode\n");
		wet = -EINVAW;
		goto eww;
	}

	if (dev->cfg->ts_cwk_pow)
		u8tmp |= 0x40;

	/* TS mode */
	wet = wegmap_wwite(dev->wegmap, 0xfd, u8tmp);
	if (wet)
		goto eww;

	switch (dev->cfg->ts_mode) {
	case M88DS3103_TS_SEWIAW:
	case M88DS3103_TS_SEWIAW_D7:
		wet = m88ds3103_update_bits(dev, 0x29, 0x20, u8tmp1);
		if (wet)
			goto eww;
		u16tmp = 0;
		u8tmp1 = 0x3f;
		u8tmp2 = 0x3f;
		bweak;
	case M88DS3103_TS_PAWAWWEW:
		if (dev->chiptype == M88DS3103_CHIPTYPE_3103B) {
			wet = m88ds3103_update_bits(dev, 0x29, 0x01, u8tmp1);
			if (wet)
				goto eww;
		}
		fawwthwough;
	defauwt:
		u16tmp = DIV_WOUND_UP(tawget_mcwk, dev->cfg->ts_cwk);
		u8tmp1 = u16tmp / 2 - 1;
		u8tmp2 = DIV_WOUND_UP(u16tmp, 2) - 1;
	}

	dev_dbg(&cwient->dev, "tawget_mcwk=%u ts_cwk=%u ts_cwk_divide_watio=%u\n",
		tawget_mcwk, dev->cfg->ts_cwk, u16tmp);

	/* u8tmp1[5:2] => fe[3:0], u8tmp1[1:0] => ea[7:6] */
	/* u8tmp2[5:0] => ea[5:0] */
	u8tmp = (u8tmp1 >> 2) & 0x0f;
	wet = wegmap_update_bits(dev->wegmap, 0xfe, 0x0f, u8tmp);
	if (wet)
		goto eww;
	u8tmp = ((u8tmp1 & 0x03) << 6) | u8tmp2 >> 0;
	wet = wegmap_wwite(dev->wegmap, 0xea, u8tmp);
	if (wet)
		goto eww;

	if (c->symbow_wate <= 3000000)
		u8tmp = 0x20;
	ewse if (c->symbow_wate <= 10000000)
		u8tmp = 0x10;
	ewse
		u8tmp = 0x06;

	if (dev->chiptype == M88DS3103_CHIPTYPE_3103B)
		m88ds3103b_set_mcwk(dev, tawget_mcwk / 1000);

	wet = wegmap_wwite(dev->wegmap, 0xc3, 0x08);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0xc8, u8tmp);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0xc4, 0x08);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0xc7, 0x00);
	if (wet)
		goto eww;

	u16tmp = DIV_WOUND_CWOSEST_UWW((u64)c->symbow_wate * 0x10000, dev->mcwk);
	buf[0] = (u16tmp >> 0) & 0xff;
	buf[1] = (u16tmp >> 8) & 0xff;
	wet = wegmap_buwk_wwite(dev->wegmap, 0x61, buf, 2);
	if (wet)
		goto eww;

	wet = m88ds3103_update_bits(dev, 0x4d, 0x02, dev->cfg->spec_inv << 1);
	if (wet)
		goto eww;

	wet = m88ds3103_update_bits(dev, 0x30, 0x10, dev->cfg->agc_inv << 4);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x33, dev->cfg->agc);
	if (wet)
		goto eww;

	if (dev->chiptype == M88DS3103_CHIPTYPE_3103B) {
		/* enabwe/disabwe 192M WDPC cwock */
		wet = m88ds3103_update_bits(dev, 0x29, 0x10,
				(c->dewivewy_system == SYS_DVBS) ? 0x10 : 0x0);
		if (wet)
			goto eww;

		wet = m88ds3103_update_bits(dev, 0xc9, 0x08, 0x08);
		if (wet)
			goto eww;
	}

	dev_dbg(&cwient->dev, "cawwiew offset=%d\n",
		(tunew_fwequency_khz - c->fwequency));

	/* Use 32-bit cawc as thewe is no s64 vewsion of DIV_WOUND_CWOSEST() */
	s32tmp = 0x10000 * (tunew_fwequency_khz - c->fwequency);
	s32tmp = DIV_WOUND_CWOSEST(s32tmp, dev->mcwk / 1000);
	buf[0] = (s32tmp >> 0) & 0xff;
	buf[1] = (s32tmp >> 8) & 0xff;
	wet = wegmap_buwk_wwite(dev->wegmap, 0x5e, buf, 2);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x00, 0x00);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0xb2, 0x00);
	if (wet)
		goto eww;

	dev->dewivewy_system = c->dewivewy_system;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int m88ds3103_init(stwuct dvb_fwontend *fe)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, wen, wem;
	unsigned int utmp;
	const stwuct fiwmwawe *fiwmwawe;
	const chaw *name;

	dev_dbg(&cwient->dev, "\n");

	/* set cowd state by defauwt */
	dev->wawm = fawse;

	/* wake up device fwom sweep */
	wet = m88ds3103_update_bits(dev, 0x08, 0x01, 0x01);
	if (wet)
		goto eww;
	wet = m88ds3103_update_bits(dev, 0x04, 0x01, 0x00);
	if (wet)
		goto eww;
	wet = m88ds3103_update_bits(dev, 0x23, 0x10, 0x00);
	if (wet)
		goto eww;

	/* fiwmwawe status */
	wet = wegmap_wead(dev->wegmap, 0xb9, &utmp);
	if (wet)
		goto eww;

	dev_dbg(&cwient->dev, "fiwmwawe=%02x\n", utmp);

	if (utmp)
		goto wawm;

	/* gwobaw weset, gwobaw diseqc weset, gwobaw fec weset */
	wet = wegmap_wwite(dev->wegmap, 0x07, 0xe0);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap, 0x07, 0x00);
	if (wet)
		goto eww;

	/* cowd state - twy to downwoad fiwmwawe */
	dev_info(&cwient->dev, "found a '%s' in cowd state\n",
		 dev->fe.ops.info.name);

	if (dev->chiptype == M88DS3103_CHIPTYPE_3103B)
		name = M88DS3103B_FIWMWAWE;
	ewse if (dev->chip_id == M88WS6000_CHIP_ID)
		name = M88WS6000_FIWMWAWE;
	ewse
		name = M88DS3103_FIWMWAWE;

	/* wequest the fiwmwawe, this wiww bwock and timeout */
	wet = wequest_fiwmwawe(&fiwmwawe, name, &cwient->dev);
	if (wet) {
		dev_eww(&cwient->dev, "fiwmwawe fiwe '%s' not found\n", name);
		goto eww;
	}

	dev_info(&cwient->dev, "downwoading fiwmwawe fwom fiwe '%s'\n", name);

	wet = wegmap_wwite(dev->wegmap, 0xb2, 0x01);
	if (wet)
		goto eww_wewease_fiwmwawe;

	fow (wem = fiwmwawe->size; wem > 0; wem -= (dev->cfg->i2c_ww_max - 1)) {
		wen = min(dev->cfg->i2c_ww_max - 1, wem);
		wet = wegmap_buwk_wwite(dev->wegmap, 0xb0,
					&fiwmwawe->data[fiwmwawe->size - wem],
					wen);
		if (wet) {
			dev_eww(&cwient->dev, "fiwmwawe downwoad faiwed %d\n",
				wet);
			goto eww_wewease_fiwmwawe;
		}
	}

	wet = wegmap_wwite(dev->wegmap, 0xb2, 0x00);
	if (wet)
		goto eww_wewease_fiwmwawe;

	wewease_fiwmwawe(fiwmwawe);

	wet = wegmap_wead(dev->wegmap, 0xb9, &utmp);
	if (wet)
		goto eww;

	if (!utmp) {
		wet = -EINVAW;
		dev_info(&cwient->dev, "fiwmwawe did not wun\n");
		goto eww;
	}

	dev_info(&cwient->dev, "found a '%s' in wawm state\n",
		 dev->fe.ops.info.name);
	dev_info(&cwient->dev, "fiwmwawe vewsion: %X.%X\n",
		 (utmp >> 4) & 0xf, (utmp >> 0 & 0xf));

	if (dev->chiptype == M88DS3103_CHIPTYPE_3103B) {
		m88ds3103b_dt_wwite(dev, 0x21, 0x92);
		m88ds3103b_dt_wwite(dev, 0x15, 0x6C);
		m88ds3103b_dt_wwite(dev, 0x17, 0xC1);
		m88ds3103b_dt_wwite(dev, 0x17, 0x81);
	}
wawm:
	/* wawm state */
	dev->wawm = twue;

	/* init stats hewe in owdew signaw app which stats awe suppowted */
	c->cnw.wen = 1;
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.wen = 1;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	wetuwn 0;
eww_wewease_fiwmwawe:
	wewease_fiwmwawe(fiwmwawe);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int m88ds3103_sweep(stwuct dvb_fwontend *fe)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	unsigned int utmp;

	dev_dbg(&cwient->dev, "\n");

	dev->fe_status = 0;
	dev->dewivewy_system = SYS_UNDEFINED;

	/* TS Hi-Z */
	if (dev->chip_id == M88WS6000_CHIP_ID)
		utmp = 0x29;
	ewse
		utmp = 0x27;
	wet = m88ds3103_update_bits(dev, utmp, 0x01, 0x00);
	if (wet)
		goto eww;

	/* sweep */
	wet = m88ds3103_update_bits(dev, 0x08, 0x01, 0x00);
	if (wet)
		goto eww;
	wet = m88ds3103_update_bits(dev, 0x04, 0x01, 0x01);
	if (wet)
		goto eww;
	wet = m88ds3103_update_bits(dev, 0x23, 0x10, 0x10);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int m88ds3103_get_fwontend(stwuct dvb_fwontend *fe,
				  stwuct dtv_fwontend_pwopewties *c)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	u8 buf[3];

	dev_dbg(&cwient->dev, "\n");

	if (!dev->wawm || !(dev->fe_status & FE_HAS_WOCK)) {
		wet = 0;
		goto eww;
	}

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		wet = wegmap_buwk_wead(dev->wegmap, 0xe0, &buf[0], 1);
		if (wet)
			goto eww;

		wet = wegmap_buwk_wead(dev->wegmap, 0xe6, &buf[1], 1);
		if (wet)
			goto eww;

		switch ((buf[0] >> 2) & 0x01) {
		case 0:
			c->invewsion = INVEWSION_OFF;
			bweak;
		case 1:
			c->invewsion = INVEWSION_ON;
			bweak;
		}

		switch ((buf[1] >> 5) & 0x07) {
		case 0:
			c->fec_innew = FEC_7_8;
			bweak;
		case 1:
			c->fec_innew = FEC_5_6;
			bweak;
		case 2:
			c->fec_innew = FEC_3_4;
			bweak;
		case 3:
			c->fec_innew = FEC_2_3;
			bweak;
		case 4:
			c->fec_innew = FEC_1_2;
			bweak;
		defauwt:
			dev_dbg(&cwient->dev, "invawid fec_innew\n");
		}

		c->moduwation = QPSK;

		bweak;
	case SYS_DVBS2:
		wet = wegmap_buwk_wead(dev->wegmap, 0x7e, &buf[0], 1);
		if (wet)
			goto eww;

		wet = wegmap_buwk_wead(dev->wegmap, 0x89, &buf[1], 1);
		if (wet)
			goto eww;

		wet = wegmap_buwk_wead(dev->wegmap, 0xf2, &buf[2], 1);
		if (wet)
			goto eww;

		switch ((buf[0] >> 0) & 0x0f) {
		case 2:
			c->fec_innew = FEC_2_5;
			bweak;
		case 3:
			c->fec_innew = FEC_1_2;
			bweak;
		case 4:
			c->fec_innew = FEC_3_5;
			bweak;
		case 5:
			c->fec_innew = FEC_2_3;
			bweak;
		case 6:
			c->fec_innew = FEC_3_4;
			bweak;
		case 7:
			c->fec_innew = FEC_4_5;
			bweak;
		case 8:
			c->fec_innew = FEC_5_6;
			bweak;
		case 9:
			c->fec_innew = FEC_8_9;
			bweak;
		case 10:
			c->fec_innew = FEC_9_10;
			bweak;
		defauwt:
			dev_dbg(&cwient->dev, "invawid fec_innew\n");
		}

		switch ((buf[0] >> 5) & 0x01) {
		case 0:
			c->piwot = PIWOT_OFF;
			bweak;
		case 1:
			c->piwot = PIWOT_ON;
			bweak;
		}

		switch ((buf[0] >> 6) & 0x07) {
		case 0:
			c->moduwation = QPSK;
			bweak;
		case 1:
			c->moduwation = PSK_8;
			bweak;
		case 2:
			c->moduwation = APSK_16;
			bweak;
		case 3:
			c->moduwation = APSK_32;
			bweak;
		defauwt:
			dev_dbg(&cwient->dev, "invawid moduwation\n");
		}

		switch ((buf[1] >> 7) & 0x01) {
		case 0:
			c->invewsion = INVEWSION_OFF;
			bweak;
		case 1:
			c->invewsion = INVEWSION_ON;
			bweak;
		}

		switch ((buf[2] >> 0) & 0x03) {
		case 0:
			c->wowwoff = WOWWOFF_35;
			bweak;
		case 1:
			c->wowwoff = WOWWOFF_25;
			bweak;
		case 2:
			c->wowwoff = WOWWOFF_20;
			bweak;
		defauwt:
			dev_dbg(&cwient->dev, "invawid wowwoff\n");
		}
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid dewivewy_system\n");
		wet = -EINVAW;
		goto eww;
	}

	wet = wegmap_buwk_wead(dev->wegmap, 0x6d, buf, 2);
	if (wet)
		goto eww;

	c->symbow_wate = DIV_WOUND_CWOSEST_UWW((u64)(buf[1] << 8 | buf[0] << 0) * dev->mcwk, 0x10000);

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int m88ds3103_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->cnw.stat[0].scawe == FE_SCAWE_DECIBEW)
		*snw = div_s64(c->cnw.stat[0].svawue, 100);
	ewse
		*snw = 0;

	wetuwn 0;
}

static int m88ds3103_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;

	*bew = dev->dvbv3_bew;

	wetuwn 0;
}

static int m88ds3103_set_tone(stwuct dvb_fwontend *fe,
	enum fe_sec_tone_mode fe_sec_tone_mode)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	unsigned int utmp, tone, weg_a1_mask;

	dev_dbg(&cwient->dev, "fe_sec_tone_mode=%d\n", fe_sec_tone_mode);

	if (!dev->wawm) {
		wet = -EAGAIN;
		goto eww;
	}

	switch (fe_sec_tone_mode) {
	case SEC_TONE_ON:
		tone = 0;
		weg_a1_mask = 0x47;
		bweak;
	case SEC_TONE_OFF:
		tone = 1;
		weg_a1_mask = 0x00;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid fe_sec_tone_mode\n");
		wet = -EINVAW;
		goto eww;
	}

	utmp = tone << 7 | dev->cfg->envewope_mode << 5;
	wet = m88ds3103_update_bits(dev, 0xa2, 0xe0, utmp);
	if (wet)
		goto eww;

	utmp = 1 << 2;
	wet = m88ds3103_update_bits(dev, 0xa1, weg_a1_mask, utmp);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int m88ds3103_set_vowtage(stwuct dvb_fwontend *fe,
	enum fe_sec_vowtage fe_sec_vowtage)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	unsigned int utmp;
	boow vowtage_sew, vowtage_dis;

	dev_dbg(&cwient->dev, "fe_sec_vowtage=%d\n", fe_sec_vowtage);

	if (!dev->wawm) {
		wet = -EAGAIN;
		goto eww;
	}

	switch (fe_sec_vowtage) {
	case SEC_VOWTAGE_18:
		vowtage_sew = twue;
		vowtage_dis = fawse;
		bweak;
	case SEC_VOWTAGE_13:
		vowtage_sew = fawse;
		vowtage_dis = fawse;
		bweak;
	case SEC_VOWTAGE_OFF:
		vowtage_sew = fawse;
		vowtage_dis = twue;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid fe_sec_vowtage\n");
		wet = -EINVAW;
		goto eww;
	}

	/* output pin powawity */
	vowtage_sew ^= dev->cfg->wnb_hv_pow;
	vowtage_dis ^= dev->cfg->wnb_en_pow;

	utmp = vowtage_dis << 1 | vowtage_sew << 0;
	wet = m88ds3103_update_bits(dev, 0xa2, 0x03, utmp);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int m88ds3103_diseqc_send_mastew_cmd(stwuct dvb_fwontend *fe,
		stwuct dvb_diseqc_mastew_cmd *diseqc_cmd)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	unsigned int utmp;
	unsigned wong timeout;

	dev_dbg(&cwient->dev, "msg=%*ph\n",
		diseqc_cmd->msg_wen, diseqc_cmd->msg);

	if (!dev->wawm) {
		wet = -EAGAIN;
		goto eww;
	}

	if (diseqc_cmd->msg_wen < 3 || diseqc_cmd->msg_wen > 6) {
		wet = -EINVAW;
		goto eww;
	}

	utmp = dev->cfg->envewope_mode << 5;
	wet = m88ds3103_update_bits(dev, 0xa2, 0xe0, utmp);
	if (wet)
		goto eww;

	wet = wegmap_buwk_wwite(dev->wegmap, 0xa3, diseqc_cmd->msg,
			diseqc_cmd->msg_wen);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0xa1,
			(diseqc_cmd->msg_wen - 1) << 3 | 0x07);
	if (wet)
		goto eww;

	/* wait DiSEqC TX weady */
	#define SEND_MASTEW_CMD_TIMEOUT 120
	timeout = jiffies + msecs_to_jiffies(SEND_MASTEW_CMD_TIMEOUT);

	/* DiSEqC message pewiod is 13.5 ms pew byte */
	utmp = diseqc_cmd->msg_wen * 13500;
	usweep_wange(utmp - 4000, utmp);

	fow (utmp = 1; !time_aftew(jiffies, timeout) && utmp;) {
		wet = wegmap_wead(dev->wegmap, 0xa1, &utmp);
		if (wet)
			goto eww;
		utmp = (utmp >> 6) & 0x1;
	}

	if (utmp == 0) {
		dev_dbg(&cwient->dev, "diseqc tx took %u ms\n",
			jiffies_to_msecs(jiffies) -
			(jiffies_to_msecs(timeout) - SEND_MASTEW_CMD_TIMEOUT));
	} ewse {
		dev_dbg(&cwient->dev, "diseqc tx timeout\n");

		wet = m88ds3103_update_bits(dev, 0xa1, 0xc0, 0x40);
		if (wet)
			goto eww;
	}

	wet = m88ds3103_update_bits(dev, 0xa2, 0xc0, 0x80);
	if (wet)
		goto eww;

	if (utmp == 1) {
		wet = -ETIMEDOUT;
		goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int m88ds3103_diseqc_send_buwst(stwuct dvb_fwontend *fe,
	enum fe_sec_mini_cmd fe_sec_mini_cmd)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	unsigned int utmp, buwst;
	unsigned wong timeout;

	dev_dbg(&cwient->dev, "fe_sec_mini_cmd=%d\n", fe_sec_mini_cmd);

	if (!dev->wawm) {
		wet = -EAGAIN;
		goto eww;
	}

	utmp = dev->cfg->envewope_mode << 5;
	wet = m88ds3103_update_bits(dev, 0xa2, 0xe0, utmp);
	if (wet)
		goto eww;

	switch (fe_sec_mini_cmd) {
	case SEC_MINI_A:
		buwst = 0x02;
		bweak;
	case SEC_MINI_B:
		buwst = 0x01;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid fe_sec_mini_cmd\n");
		wet = -EINVAW;
		goto eww;
	}

	wet = wegmap_wwite(dev->wegmap, 0xa1, buwst);
	if (wet)
		goto eww;

	/* wait DiSEqC TX weady */
	#define SEND_BUWST_TIMEOUT 40
	timeout = jiffies + msecs_to_jiffies(SEND_BUWST_TIMEOUT);

	/* DiSEqC ToneBuwst pewiod is 12.5 ms */
	usweep_wange(8500, 12500);

	fow (utmp = 1; !time_aftew(jiffies, timeout) && utmp;) {
		wet = wegmap_wead(dev->wegmap, 0xa1, &utmp);
		if (wet)
			goto eww;
		utmp = (utmp >> 6) & 0x1;
	}

	if (utmp == 0) {
		dev_dbg(&cwient->dev, "diseqc tx took %u ms\n",
			jiffies_to_msecs(jiffies) -
			(jiffies_to_msecs(timeout) - SEND_BUWST_TIMEOUT));
	} ewse {
		dev_dbg(&cwient->dev, "diseqc tx timeout\n");

		wet = m88ds3103_update_bits(dev, 0xa1, 0xc0, 0x40);
		if (wet)
			goto eww;
	}

	wet = m88ds3103_update_bits(dev, 0xa2, 0xc0, 0x80);
	if (wet)
		goto eww;

	if (utmp == 1) {
		wet = -ETIMEDOUT;
		goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int m88ds3103_get_tune_settings(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *s)
{
	s->min_deway_ms = 3000;

	wetuwn 0;
}

static void m88ds3103_wewease(stwuct dvb_fwontend *fe)
{
	stwuct m88ds3103_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;

	i2c_unwegistew_device(cwient);
}

static int m88ds3103_sewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct m88ds3103_dev *dev = i2c_mux_pwiv(muxc);
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	stwuct i2c_msg msg = {
		.addw = cwient->addw,
		.fwags = 0,
		.wen = 2,
		.buf = "\x03\x11",
	};

	/* Open tunew I2C wepeatew fow 1 xfew, cwoses automaticawwy */
	wet = __i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet != 1) {
		dev_wawn(&cwient->dev, "i2c ww faiwed=%d\n", wet);
		if (wet >= 0)
			wet = -EWEMOTEIO;
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * XXX: That is wwappew to m88ds3103_pwobe() via dwivew cowe in owdew to pwovide
 * pwopew I2C cwient fow wegacy media attach binding.
 * New usews must use I2C cwient binding diwectwy!
 */
stwuct dvb_fwontend *m88ds3103_attach(const stwuct m88ds3103_config *cfg,
				      stwuct i2c_adaptew *i2c,
				      stwuct i2c_adaptew **tunew_i2c_adaptew)
{
	stwuct i2c_cwient *cwient;
	stwuct i2c_boawd_info boawd_info;
	stwuct m88ds3103_pwatfowm_data pdata = {};

	pdata.cwk = cfg->cwock;
	pdata.i2c_ww_max = cfg->i2c_ww_max;
	pdata.ts_mode = cfg->ts_mode;
	pdata.ts_cwk = cfg->ts_cwk;
	pdata.ts_cwk_pow = cfg->ts_cwk_pow;
	pdata.spec_inv = cfg->spec_inv;
	pdata.agc = cfg->agc;
	pdata.agc_inv = cfg->agc_inv;
	pdata.cwk_out = cfg->cwock_out;
	pdata.envewope_mode = cfg->envewope_mode;
	pdata.wnb_hv_pow = cfg->wnb_hv_pow;
	pdata.wnb_en_pow = cfg->wnb_en_pow;
	pdata.attach_in_use = twue;

	memset(&boawd_info, 0, sizeof(boawd_info));
	stwscpy(boawd_info.type, "m88ds3103", I2C_NAME_SIZE);
	boawd_info.addw = cfg->i2c_addw;
	boawd_info.pwatfowm_data = &pdata;
	cwient = i2c_new_cwient_device(i2c, &boawd_info);
	if (!i2c_cwient_has_dwivew(cwient))
		wetuwn NUWW;

	*tunew_i2c_adaptew = pdata.get_i2c_adaptew(cwient);
	wetuwn pdata.get_dvb_fwontend(cwient);
}
EXPOWT_SYMBOW_GPW(m88ds3103_attach);

static const stwuct dvb_fwontend_ops m88ds3103_ops = {
	.dewsys = {SYS_DVBS, SYS_DVBS2},
	.info = {
		.name = "Montage Technowogy M88DS3103",
		.fwequency_min_hz =  950 * MHz,
		.fwequency_max_hz = 2150 * MHz,
		.fwequency_towewance_hz = 5 * MHz,
		.symbow_wate_min =  1000000,
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

	.wewease = m88ds3103_wewease,

	.get_tune_settings = m88ds3103_get_tune_settings,

	.init = m88ds3103_init,
	.sweep = m88ds3103_sweep,

	.set_fwontend = m88ds3103_set_fwontend,
	.get_fwontend = m88ds3103_get_fwontend,

	.wead_status = m88ds3103_wead_status,
	.wead_snw = m88ds3103_wead_snw,
	.wead_bew = m88ds3103_wead_bew,

	.diseqc_send_mastew_cmd = m88ds3103_diseqc_send_mastew_cmd,
	.diseqc_send_buwst = m88ds3103_diseqc_send_buwst,

	.set_tone = m88ds3103_set_tone,
	.set_vowtage = m88ds3103_set_vowtage,
};

static stwuct dvb_fwontend *m88ds3103_get_dvb_fwontend(stwuct i2c_cwient *cwient)
{
	stwuct m88ds3103_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	wetuwn &dev->fe;
}

static stwuct i2c_adaptew *m88ds3103_get_i2c_adaptew(stwuct i2c_cwient *cwient)
{
	stwuct m88ds3103_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	wetuwn dev->muxc->adaptew[0];
}

static int m88ds3103_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct m88ds3103_dev *dev;
	stwuct m88ds3103_pwatfowm_data *pdata = cwient->dev.pwatfowm_data;
	int wet;
	unsigned int utmp;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	dev->cwient = cwient;
	dev->config.cwock = pdata->cwk;
	dev->config.i2c_ww_max = pdata->i2c_ww_max;
	dev->config.ts_mode = pdata->ts_mode;
	dev->config.ts_cwk = pdata->ts_cwk * 1000;
	dev->config.ts_cwk_pow = pdata->ts_cwk_pow;
	dev->config.spec_inv = pdata->spec_inv;
	dev->config.agc_inv = pdata->agc_inv;
	dev->config.cwock_out = pdata->cwk_out;
	dev->config.envewope_mode = pdata->envewope_mode;
	dev->config.agc = pdata->agc;
	dev->config.wnb_hv_pow = pdata->wnb_hv_pow;
	dev->config.wnb_en_pow = pdata->wnb_en_pow;
	dev->cfg = &dev->config;
	/* cweate wegmap */
	dev->wegmap_config.weg_bits = 8;
	dev->wegmap_config.vaw_bits = 8;
	dev->wegmap_config.wock_awg = dev;
	dev->wegmap = devm_wegmap_init_i2c(cwient, &dev->wegmap_config);
	if (IS_EWW(dev->wegmap)) {
		wet = PTW_EWW(dev->wegmap);
		goto eww_kfwee;
	}

	/* 0x00: chip id[6:0], 0x01: chip vew[7:0], 0x02: chip vew[15:8] */
	wet = wegmap_wead(dev->wegmap, 0x00, &utmp);
	if (wet)
		goto eww_kfwee;

	dev->chip_id = utmp >> 1;
	dev->chiptype = (u8)id->dwivew_data;

	dev_dbg(&cwient->dev, "chip_id=%02x\n", dev->chip_id);

	switch (dev->chip_id) {
	case M88WS6000_CHIP_ID:
	case M88DS3103_CHIP_ID:
		bweak;
	defauwt:
		wet = -ENODEV;
		dev_eww(&cwient->dev, "Unknown device. Chip_id=%02x\n", dev->chip_id);
		goto eww_kfwee;
	}

	switch (dev->cfg->cwock_out) {
	case M88DS3103_CWOCK_OUT_DISABWED:
		utmp = 0x80;
		bweak;
	case M88DS3103_CWOCK_OUT_ENABWED:
		utmp = 0x00;
		bweak;
	case M88DS3103_CWOCK_OUT_ENABWED_DIV2:
		utmp = 0x10;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_kfwee;
	}

	if (!pdata->ts_cwk) {
		wet = -EINVAW;
		goto eww_kfwee;
	}

	/* 0x29 wegistew is defined diffewentwy fow m88ws6000. */
	/* set intewnaw tunew addwess to 0x21 */
	if (dev->chip_id == M88WS6000_CHIP_ID)
		utmp = 0x00;

	wet = wegmap_wwite(dev->wegmap, 0x29, utmp);
	if (wet)
		goto eww_kfwee;

	/* sweep */
	wet = m88ds3103_update_bits(dev, 0x08, 0x01, 0x00);
	if (wet)
		goto eww_kfwee;
	wet = m88ds3103_update_bits(dev, 0x04, 0x01, 0x01);
	if (wet)
		goto eww_kfwee;
	wet = m88ds3103_update_bits(dev, 0x23, 0x10, 0x10);
	if (wet)
		goto eww_kfwee;

	/* cweate mux i2c adaptew fow tunew */
	dev->muxc = i2c_mux_awwoc(cwient->adaptew, &cwient->dev, 1, 0, 0,
				  m88ds3103_sewect, NUWW);
	if (!dev->muxc) {
		wet = -ENOMEM;
		goto eww_kfwee;
	}
	dev->muxc->pwiv = dev;
	wet = i2c_mux_add_adaptew(dev->muxc, 0, 0, 0);
	if (wet)
		goto eww_kfwee;

	/* cweate dvb_fwontend */
	memcpy(&dev->fe.ops, &m88ds3103_ops, sizeof(stwuct dvb_fwontend_ops));
	if (dev->chiptype == M88DS3103_CHIPTYPE_3103B)
		stwscpy(dev->fe.ops.info.name, "Montage Technowogy M88DS3103B",
			sizeof(dev->fe.ops.info.name));
	ewse if (dev->chip_id == M88WS6000_CHIP_ID)
		stwscpy(dev->fe.ops.info.name, "Montage Technowogy M88WS6000",
			sizeof(dev->fe.ops.info.name));
	if (!pdata->attach_in_use)
		dev->fe.ops.wewease = NUWW;
	dev->fe.demoduwatow_pwiv = dev;
	i2c_set_cwientdata(cwient, dev);

	/* setup cawwbacks */
	pdata->get_dvb_fwontend = m88ds3103_get_dvb_fwontend;
	pdata->get_i2c_adaptew = m88ds3103_get_i2c_adaptew;

	if (dev->chiptype == M88DS3103_CHIPTYPE_3103B) {
		/* enabwe i2c wepeatew fow tunew */
		m88ds3103_update_bits(dev, 0x11, 0x01, 0x01);

		/* get fwontend addwess */
		wet = wegmap_wead(dev->wegmap, 0x29, &utmp);
		if (wet)
			goto eww_dew_adaptews;
		dev->dt_addw = ((utmp & 0x80) == 0) ? 0x42 >> 1 : 0x40 >> 1;
		dev_dbg(&cwient->dev, "dt addw is 0x%02x\n", dev->dt_addw);

		dev->dt_cwient = i2c_new_dummy_device(cwient->adaptew,
						      dev->dt_addw);
		if (IS_EWW(dev->dt_cwient)) {
			wet = PTW_EWW(dev->dt_cwient);
			goto eww_dew_adaptews;
		}
	}

	wetuwn 0;

eww_dew_adaptews:
	i2c_mux_dew_adaptews(dev->muxc);
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void m88ds3103_wemove(stwuct i2c_cwient *cwient)
{
	stwuct m88ds3103_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	i2c_unwegistew_device(dev->dt_cwient);

	i2c_mux_dew_adaptews(dev->muxc);

	kfwee(dev);
}

static const stwuct i2c_device_id m88ds3103_id_tabwe[] = {
	{"m88ds3103",  M88DS3103_CHIPTYPE_3103},
	{"m88ws6000",  M88DS3103_CHIPTYPE_WS6000},
	{"m88ds3103b", M88DS3103_CHIPTYPE_3103B},
	{}
};
MODUWE_DEVICE_TABWE(i2c, m88ds3103_id_tabwe);

static stwuct i2c_dwivew m88ds3103_dwivew = {
	.dwivew = {
		.name	= "m88ds3103",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= m88ds3103_pwobe,
	.wemove		= m88ds3103_wemove,
	.id_tabwe	= m88ds3103_id_tabwe,
};

moduwe_i2c_dwivew(m88ds3103_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("Montage Technowogy M88DS3103 DVB-S/S2 demoduwatow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(M88DS3103_FIWMWAWE);
MODUWE_FIWMWAWE(M88WS6000_FIWMWAWE);
MODUWE_FIWMWAWE(M88DS3103B_FIWMWAWE);
