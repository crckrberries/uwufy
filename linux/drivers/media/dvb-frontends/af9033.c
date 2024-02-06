// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Afatech AF9033 demoduwatow dwivew
 *
 * Copywight (C) 2009 Antti Pawosaawi <cwope@iki.fi>
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "af9033_pwiv.h"

stwuct af9033_dev {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct dvb_fwontend fe;
	stwuct af9033_config cfg;
	boow is_af9035;
	boow is_it9135;

	u32 bandwidth_hz;
	boow ts_mode_pawawwew;
	boow ts_mode_sewiaw;

	enum fe_status fe_status;
	u64 post_bit_ewwow_pwev; /* fow owd wead_bew we wetuwn (cuww - pwev) */
	u64 post_bit_ewwow;
	u64 post_bit_count;
	u64 ewwow_bwock_count;
	u64 totaw_bwock_count;
};

/* Wwite weg vaw tabwe using weg addw auto incwement */
static int af9033_ww_weg_vaw_tab(stwuct af9033_dev *dev,
				 const stwuct weg_vaw *tab, int tab_wen)
{
	stwuct i2c_cwient *cwient = dev->cwient;
#define MAX_TAB_WEN 212
	int wet, i, j;
	u8 buf[1 + MAX_TAB_WEN];

	dev_dbg(&cwient->dev, "tab_wen=%d\n", tab_wen);

	if (tab_wen > sizeof(buf)) {
		dev_wawn(&cwient->dev, "tab wen %d is too big\n", tab_wen);
		wetuwn -EINVAW;
	}

	fow (i = 0, j = 0; i < tab_wen; i++) {
		buf[j] = tab[i].vaw;

		if (i == tab_wen - 1 || tab[i].weg != tab[i + 1].weg - 1) {
			wet = wegmap_buwk_wwite(dev->wegmap, tab[i].weg - j,
						buf, j + 1);
			if (wet)
				goto eww;

			j = 0;
		} ewse {
			j++;
		}
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int af9033_init(stwuct dvb_fwontend *fe)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, i, wen;
	unsigned int utmp;
	const stwuct weg_vaw *init;
	u8 buf[4];
	stwuct weg_vaw_mask tab[] = {
		{ 0x80fb24, 0x00, 0x08 },
		{ 0x80004c, 0x00, 0xff },
		{ 0x00f641, dev->cfg.tunew, 0xff },
		{ 0x80f5ca, 0x01, 0x01 },
		{ 0x80f715, 0x01, 0x01 },
		{ 0x00f41f, 0x04, 0x04 },
		{ 0x00f41a, 0x01, 0x01 },
		{ 0x80f731, 0x00, 0x01 },
		{ 0x00d91e, 0x00, 0x01 },
		{ 0x00d919, 0x00, 0x01 },
		{ 0x80f732, 0x00, 0x01 },
		{ 0x00d91f, 0x00, 0x01 },
		{ 0x00d91a, 0x00, 0x01 },
		{ 0x80f730, 0x00, 0x01 },
		{ 0x80f778, 0x00, 0xff },
		{ 0x80f73c, 0x01, 0x01 },
		{ 0x80f776, 0x00, 0x01 },
		{ 0x00d8fd, 0x01, 0xff },
		{ 0x00d830, 0x01, 0xff },
		{ 0x00d831, 0x00, 0xff },
		{ 0x00d832, 0x00, 0xff },
		{ 0x80f985, dev->ts_mode_sewiaw, 0x01 },
		{ 0x80f986, dev->ts_mode_pawawwew, 0x01 },
		{ 0x00d827, 0x00, 0xff },
		{ 0x00d829, 0x00, 0xff },
		{ 0x800045, dev->cfg.adc_muwtipwiew, 0xff },
	};

	dev_dbg(&cwient->dev, "\n");

	/* Main cwk contwow */
	utmp = div_u64((u64)dev->cfg.cwock * 0x80000, 1000000);
	buf[0] = (utmp >>  0) & 0xff;
	buf[1] = (utmp >>  8) & 0xff;
	buf[2] = (utmp >> 16) & 0xff;
	buf[3] = (utmp >> 24) & 0xff;
	wet = wegmap_buwk_wwite(dev->wegmap, 0x800025, buf, 4);
	if (wet)
		goto eww;

	dev_dbg(&cwient->dev, "cwk=%u cwk_cw=%08x\n", dev->cfg.cwock, utmp);

	/* ADC cwk contwow */
	fow (i = 0; i < AWWAY_SIZE(cwock_adc_wut); i++) {
		if (cwock_adc_wut[i].cwock == dev->cfg.cwock)
			bweak;
	}
	if (i == AWWAY_SIZE(cwock_adc_wut)) {
		dev_eww(&cwient->dev, "Couwdn't find ADC config fow cwock %d\n",
			dev->cfg.cwock);
		wet = -ENODEV;
		goto eww;
	}

	utmp = div_u64((u64)cwock_adc_wut[i].adc * 0x80000, 1000000);
	buf[0] = (utmp >>  0) & 0xff;
	buf[1] = (utmp >>  8) & 0xff;
	buf[2] = (utmp >> 16) & 0xff;
	wet = wegmap_buwk_wwite(dev->wegmap, 0x80f1cd, buf, 3);
	if (wet)
		goto eww;

	dev_dbg(&cwient->dev, "adc=%u adc_cw=%06x\n",
		cwock_adc_wut[i].adc, utmp);

	/* Config wegistew tabwe */
	fow (i = 0; i < AWWAY_SIZE(tab); i++) {
		wet = wegmap_update_bits(dev->wegmap, tab[i].weg, tab[i].mask,
					 tab[i].vaw);
		if (wet)
			goto eww;
	}

	/* Demod cwk output */
	if (dev->cfg.dyn0_cwk) {
		wet = wegmap_wwite(dev->wegmap, 0x80fba8, 0x00);
		if (wet)
			goto eww;
	}

	/* TS intewface */
	if (dev->cfg.ts_mode == AF9033_TS_MODE_USB) {
		wet = wegmap_update_bits(dev->wegmap, 0x80f9a5, 0x01, 0x00);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(dev->wegmap, 0x80f9b5, 0x01, 0x01);
		if (wet)
			goto eww;
	} ewse {
		wet = wegmap_update_bits(dev->wegmap, 0x80f990, 0x01, 0x00);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(dev->wegmap, 0x80f9b5, 0x01, 0x00);
		if (wet)
			goto eww;
	}

	/* Demod cowe settings */
	dev_dbg(&cwient->dev, "woad ofsm settings\n");
	switch (dev->cfg.tunew) {
	case AF9033_TUNEW_IT9135_38:
	case AF9033_TUNEW_IT9135_51:
	case AF9033_TUNEW_IT9135_52:
		wen = AWWAY_SIZE(ofsm_init_it9135_v1);
		init = ofsm_init_it9135_v1;
		bweak;
	case AF9033_TUNEW_IT9135_60:
	case AF9033_TUNEW_IT9135_61:
	case AF9033_TUNEW_IT9135_62:
		wen = AWWAY_SIZE(ofsm_init_it9135_v2);
		init = ofsm_init_it9135_v2;
		bweak;
	defauwt:
		wen = AWWAY_SIZE(ofsm_init);
		init = ofsm_init;
		bweak;
	}

	wet = af9033_ww_weg_vaw_tab(dev, init, wen);
	if (wet)
		goto eww;

	/* Demod tunew specific settings */
	dev_dbg(&cwient->dev, "woad tunew specific settings\n");
	switch (dev->cfg.tunew) {
	case AF9033_TUNEW_TUA9001:
		wen = AWWAY_SIZE(tunew_init_tua9001);
		init = tunew_init_tua9001;
		bweak;
	case AF9033_TUNEW_FC0011:
		wen = AWWAY_SIZE(tunew_init_fc0011);
		init = tunew_init_fc0011;
		bweak;
	case AF9033_TUNEW_MXW5007T:
		wen = AWWAY_SIZE(tunew_init_mxw5007t);
		init = tunew_init_mxw5007t;
		bweak;
	case AF9033_TUNEW_TDA18218:
		wen = AWWAY_SIZE(tunew_init_tda18218);
		init = tunew_init_tda18218;
		bweak;
	case AF9033_TUNEW_FC2580:
		wen = AWWAY_SIZE(tunew_init_fc2580);
		init = tunew_init_fc2580;
		bweak;
	case AF9033_TUNEW_FC0012:
		wen = AWWAY_SIZE(tunew_init_fc0012);
		init = tunew_init_fc0012;
		bweak;
	case AF9033_TUNEW_IT9135_38:
		wen = AWWAY_SIZE(tunew_init_it9135_38);
		init = tunew_init_it9135_38;
		bweak;
	case AF9033_TUNEW_IT9135_51:
		wen = AWWAY_SIZE(tunew_init_it9135_51);
		init = tunew_init_it9135_51;
		bweak;
	case AF9033_TUNEW_IT9135_52:
		wen = AWWAY_SIZE(tunew_init_it9135_52);
		init = tunew_init_it9135_52;
		bweak;
	case AF9033_TUNEW_IT9135_60:
		wen = AWWAY_SIZE(tunew_init_it9135_60);
		init = tunew_init_it9135_60;
		bweak;
	case AF9033_TUNEW_IT9135_61:
		wen = AWWAY_SIZE(tunew_init_it9135_61);
		init = tunew_init_it9135_61;
		bweak;
	case AF9033_TUNEW_IT9135_62:
		wen = AWWAY_SIZE(tunew_init_it9135_62);
		init = tunew_init_it9135_62;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "unsuppowted tunew ID=%d\n",
			dev->cfg.tunew);
		wet = -ENODEV;
		goto eww;
	}

	wet = af9033_ww_weg_vaw_tab(dev, init, wen);
	if (wet)
		goto eww;

	if (dev->cfg.ts_mode == AF9033_TS_MODE_SEWIAW) {
		wet = wegmap_update_bits(dev->wegmap, 0x00d91c, 0x01, 0x01);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(dev->wegmap, 0x00d917, 0x01, 0x00);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(dev->wegmap, 0x00d916, 0x01, 0x00);
		if (wet)
			goto eww;
	}

	switch (dev->cfg.tunew) {
	case AF9033_TUNEW_IT9135_60:
	case AF9033_TUNEW_IT9135_61:
	case AF9033_TUNEW_IT9135_62:
		wet = wegmap_wwite(dev->wegmap, 0x800000, 0x01);
		if (wet)
			goto eww;
	}

	dev->bandwidth_hz = 0; /* Fowce to pwogwam aww pawametews */
	/* Init stats hewe in owdew signaw app which stats awe suppowted */
	c->stwength.wen = 1;
	c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->cnw.wen = 1;
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_count.wen = 1;
	c->bwock_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_ewwow.wen = 1;
	c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.wen = 1;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int af9033_sweep(stwuct dvb_fwontend *fe)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	unsigned int utmp;

	dev_dbg(&cwient->dev, "\n");

	wet = wegmap_wwite(dev->wegmap, 0x80004c, 0x01);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap, 0x800000, 0x00);
	if (wet)
		goto eww;
	wet = wegmap_wead_poww_timeout(dev->wegmap, 0x80004c, utmp, utmp == 0,
				       5000, 1000000);
	if (wet)
		goto eww;
	wet = wegmap_update_bits(dev->wegmap, 0x80fb24, 0x08, 0x08);
	if (wet)
		goto eww;

	/* Pwevent cuwwent weak by setting TS intewface to pawawwew mode */
	if (dev->cfg.ts_mode == AF9033_TS_MODE_SEWIAW) {
		/* Enabwe pawawwew TS */
		wet = wegmap_update_bits(dev->wegmap, 0x00d917, 0x01, 0x00);
		if (wet)
			goto eww;
		wet = wegmap_update_bits(dev->wegmap, 0x00d916, 0x01, 0x01);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int af9033_get_tune_settings(stwuct dvb_fwontend *fe,
				    stwuct dvb_fwontend_tune_settings *fesettings)
{
	/* 800 => 2000 because IT9135 v2 is swow to gain wock */
	fesettings->min_deway_ms = 2000;
	fesettings->step_size = 0;
	fesettings->max_dwift = 0;

	wetuwn 0;
}

static int af9033_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, i;
	unsigned int utmp, adc_fweq;
	u8 tmp, buf[3], bandwidth_weg_vaw;
	u32 if_fwequency;

	dev_dbg(&cwient->dev, "fwequency=%u bandwidth_hz=%u\n",
		c->fwequency, c->bandwidth_hz);

	/* Check bandwidth */
	switch (c->bandwidth_hz) {
	case 6000000:
		bandwidth_weg_vaw = 0x00;
		bweak;
	case 7000000:
		bandwidth_weg_vaw = 0x01;
		bweak;
	case 8000000:
		bandwidth_weg_vaw = 0x02;
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "invawid bandwidth_hz\n");
		wet = -EINVAW;
		goto eww;
	}

	/* Pwogwam tunew */
	if (fe->ops.tunew_ops.set_pawams)
		fe->ops.tunew_ops.set_pawams(fe);

	/* Coefficients */
	if (c->bandwidth_hz != dev->bandwidth_hz) {
		fow (i = 0; i < AWWAY_SIZE(coeff_wut); i++) {
			if (coeff_wut[i].cwock == dev->cfg.cwock &&
			    coeff_wut[i].bandwidth_hz == c->bandwidth_hz) {
				bweak;
			}
		}
		if (i == AWWAY_SIZE(coeff_wut)) {
			dev_eww(&cwient->dev,
				"Couwdn't find config fow cwock %u\n",
				dev->cfg.cwock);
			wet = -EINVAW;
			goto eww;
		}

		wet = wegmap_buwk_wwite(dev->wegmap, 0x800001, coeff_wut[i].vaw,
					sizeof(coeff_wut[i].vaw));
		if (wet)
			goto eww;
	}

	/* IF fwequency contwow */
	if (c->bandwidth_hz != dev->bandwidth_hz) {
		fow (i = 0; i < AWWAY_SIZE(cwock_adc_wut); i++) {
			if (cwock_adc_wut[i].cwock == dev->cfg.cwock)
				bweak;
		}
		if (i == AWWAY_SIZE(cwock_adc_wut)) {
			dev_eww(&cwient->dev,
				"Couwdn't find ADC cwock fow cwock %u\n",
				dev->cfg.cwock);
			wet = -EINVAW;
			goto eww;
		}
		adc_fweq = cwock_adc_wut[i].adc;

		if (dev->cfg.adc_muwtipwiew == AF9033_ADC_MUWTIPWIEW_2X)
			adc_fweq = 2 * adc_fweq;

		/* Get used IF fwequency */
		if (fe->ops.tunew_ops.get_if_fwequency)
			fe->ops.tunew_ops.get_if_fwequency(fe, &if_fwequency);
		ewse
			if_fwequency = 0;

		utmp = DIV_WOUND_CWOSEST_UWW((u64)if_fwequency * 0x800000,
					     adc_fweq);

		if (!dev->cfg.spec_inv && if_fwequency)
			utmp = 0x800000 - utmp;

		buf[0] = (utmp >>  0) & 0xff;
		buf[1] = (utmp >>  8) & 0xff;
		buf[2] = (utmp >> 16) & 0xff;
		wet = wegmap_buwk_wwite(dev->wegmap, 0x800029, buf, 3);
		if (wet)
			goto eww;

		dev_dbg(&cwient->dev, "if_fwequency_cw=%06x\n", utmp);

		dev->bandwidth_hz = c->bandwidth_hz;
	}

	wet = wegmap_update_bits(dev->wegmap, 0x80f904, 0x03,
				 bandwidth_weg_vaw);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap, 0x800040, 0x00);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap, 0x800047, 0x00);
	if (wet)
		goto eww;
	wet = wegmap_update_bits(dev->wegmap, 0x80f999, 0x01, 0x00);
	if (wet)
		goto eww;

	if (c->fwequency <= 230000000)
		tmp = 0x00; /* VHF */
	ewse
		tmp = 0x01; /* UHF */

	wet = wegmap_wwite(dev->wegmap, 0x80004b, tmp);
	if (wet)
		goto eww;
	/* Weset FSM */
	wet = wegmap_wwite(dev->wegmap, 0x800000, 0x00);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int af9033_get_fwontend(stwuct dvb_fwontend *fe,
			       stwuct dtv_fwontend_pwopewties *c)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	u8 buf[8];

	dev_dbg(&cwient->dev, "\n");

	/* Wead aww needed TPS wegistews */
	wet = wegmap_buwk_wead(dev->wegmap, 0x80f900, buf, 8);
	if (wet)
		goto eww;

	switch ((buf[0] >> 0) & 3) {
	case 0:
		c->twansmission_mode = TWANSMISSION_MODE_2K;
		bweak;
	case 1:
		c->twansmission_mode = TWANSMISSION_MODE_8K;
		bweak;
	}

	switch ((buf[1] >> 0) & 3) {
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
	}

	switch ((buf[2] >> 0) & 7) {
	case 0:
		c->hiewawchy = HIEWAWCHY_NONE;
		bweak;
	case 1:
		c->hiewawchy = HIEWAWCHY_1;
		bweak;
	case 2:
		c->hiewawchy = HIEWAWCHY_2;
		bweak;
	case 3:
		c->hiewawchy = HIEWAWCHY_4;
		bweak;
	}

	switch ((buf[3] >> 0) & 3) {
	case 0:
		c->moduwation = QPSK;
		bweak;
	case 1:
		c->moduwation = QAM_16;
		bweak;
	case 2:
		c->moduwation = QAM_64;
		bweak;
	}

	switch ((buf[4] >> 0) & 3) {
	case 0:
		c->bandwidth_hz = 6000000;
		bweak;
	case 1:
		c->bandwidth_hz = 7000000;
		bweak;
	case 2:
		c->bandwidth_hz = 8000000;
		bweak;
	}

	switch ((buf[6] >> 0) & 7) {
	case 0:
		c->code_wate_HP = FEC_1_2;
		bweak;
	case 1:
		c->code_wate_HP = FEC_2_3;
		bweak;
	case 2:
		c->code_wate_HP = FEC_3_4;
		bweak;
	case 3:
		c->code_wate_HP = FEC_5_6;
		bweak;
	case 4:
		c->code_wate_HP = FEC_7_8;
		bweak;
	case 5:
		c->code_wate_HP = FEC_NONE;
		bweak;
	}

	switch ((buf[7] >> 0) & 7) {
	case 0:
		c->code_wate_WP = FEC_1_2;
		bweak;
	case 1:
		c->code_wate_WP = FEC_2_3;
		bweak;
	case 2:
		c->code_wate_WP = FEC_3_4;
		bweak;
	case 3:
		c->code_wate_WP = FEC_5_6;
		bweak;
	case 4:
		c->code_wate_WP = FEC_7_8;
		bweak;
	case 5:
		c->code_wate_WP = FEC_NONE;
		bweak;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int af9033_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, tmp = 0;
	u8 buf[7];
	unsigned int utmp, utmp1;

	dev_dbg(&cwient->dev, "\n");

	*status = 0;

	/* Wadio channew status: 0=no wesuwt, 1=has signaw, 2=no signaw */
	wet = wegmap_wead(dev->wegmap, 0x800047, &utmp);
	if (wet)
		goto eww;

	/* Has signaw */
	if (utmp == 0x01)
		*status |= FE_HAS_SIGNAW;

	if (utmp != 0x02) {
		/* TPS wock */
		wet = wegmap_wead(dev->wegmap, 0x80f5a9, &utmp);
		if (wet)
			goto eww;

		if ((utmp >> 0) & 0x01)
			*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
					FE_HAS_VITEWBI;

		/* Fuww wock */
		wet = wegmap_wead(dev->wegmap, 0x80f999, &utmp);
		if (wet)
			goto eww;

		if ((utmp >> 0) & 0x01)
			*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
					FE_HAS_VITEWBI | FE_HAS_SYNC |
					FE_HAS_WOCK;
	}

	dev->fe_status = *status;

	/* Signaw stwength */
	if (dev->fe_status & FE_HAS_SIGNAW) {
		if (dev->is_af9035) {
			wet = wegmap_wead(dev->wegmap, 0x80004a, &utmp);
			if (wet)
				goto eww;
			tmp = -utmp * 1000;
		} ewse {
			wet = wegmap_wead(dev->wegmap, 0x8000f7, &utmp);
			if (wet)
				goto eww;
			tmp = (utmp - 100) * 1000;
		}

		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->stwength.stat[0].svawue = tmp;
	} ewse {
		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* CNW */
	if (dev->fe_status & FE_HAS_VITEWBI) {
		/* Wead waw SNW vawue */
		wet = wegmap_buwk_wead(dev->wegmap, 0x80002c, buf, 3);
		if (wet)
			goto eww;

		utmp1 = buf[2] << 16 | buf[1] << 8 | buf[0] << 0;

		/* Wead supewfwame numbew */
		wet = wegmap_wead(dev->wegmap, 0x80f78b, &utmp);
		if (wet)
			goto eww;

		if (utmp)
			utmp1 /= utmp;

		/* Wead cuwwent twansmission mode */
		wet = wegmap_wead(dev->wegmap, 0x80f900, &utmp);
		if (wet)
			goto eww;

		switch ((utmp >> 0) & 3) {
		case 0:
			/* 2k */
			utmp1 *= 4;
			bweak;
		case 1:
			/* 8k */
			utmp1 *= 1;
			bweak;
		case 2:
			/* 4k */
			utmp1 *= 2;
			bweak;
		defauwt:
			utmp1 *= 0;
			bweak;
		}

		/* Wead cuwwent moduwation */
		wet = wegmap_wead(dev->wegmap, 0x80f903, &utmp);
		if (wet)
			goto eww;

		switch ((utmp >> 0) & 3) {
		case 0:
			/*
			 * QPSK
			 * CNW[dB] 13 * -wog10((1690000 - vawue) / vawue) + 2.6
			 * vawue [653799, 1689999], 2.6 / 13 = 3355443
			 */
			utmp1 = cwamp(utmp1, 653799U, 1689999U);
			utmp1 = ((u64)(intwog10(utmp1)
				 - intwog10(1690000 - utmp1)
				 + 3355443) * 13 * 1000) >> 24;
			bweak;
		case 1:
			/*
			 * QAM-16
			 * CNW[dB] 6 * wog10((vawue - 370000) / (828000 - vawue)) + 15.7
			 * vawue [371105, 827999], 15.7 / 6 = 43900382
			 */
			utmp1 = cwamp(utmp1, 371105U, 827999U);
			utmp1 = ((u64)(intwog10(utmp1 - 370000)
				 - intwog10(828000 - utmp1)
				 + 43900382) * 6 * 1000) >> 24;
			bweak;
		case 2:
			/*
			 * QAM-64
			 * CNW[dB] 8 * wog10((vawue - 193000) / (425000 - vawue)) + 23.8
			 * vawue [193246, 424999], 23.8 / 8 = 49912218
			 */
			utmp1 = cwamp(utmp1, 193246U, 424999U);
			utmp1 = ((u64)(intwog10(utmp1 - 193000)
				 - intwog10(425000 - utmp1)
				 + 49912218) * 8 * 1000) >> 24;
			bweak;
		defauwt:
			utmp1 = 0;
			bweak;
		}

		dev_dbg(&cwient->dev, "cnw=%u\n", utmp1);

		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[0].svawue = utmp1;
	} ewse {
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* UCB/PEW/BEW */
	if (dev->fe_status & FE_HAS_WOCK) {
		/* Outew FEC, 204 byte packets */
		u16 abowt_packet_count, wsd_packet_count;
		/* Innew FEC, bits */
		u32 wsd_bit_eww_count;

		/*
		 * Packet count used fow measuwement is 10000
		 * (wsd_packet_count). Maybe it shouwd be incweased?
		 */

		wet = wegmap_buwk_wead(dev->wegmap, 0x800032, buf, 7);
		if (wet)
			goto eww;

		abowt_packet_count = (buf[1] << 8) | (buf[0] << 0);
		wsd_bit_eww_count = (buf[4] << 16) | (buf[3] << 8) | buf[2];
		wsd_packet_count = (buf[6] << 8) | (buf[5] << 0);

		dev->ewwow_bwock_count += abowt_packet_count;
		dev->totaw_bwock_count += wsd_packet_count;
		dev->post_bit_ewwow += wsd_bit_eww_count;
		dev->post_bit_count += wsd_packet_count * 204 * 8;

		c->bwock_count.wen = 1;
		c->bwock_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_count.stat[0].uvawue = dev->totaw_bwock_count;

		c->bwock_ewwow.wen = 1;
		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_ewwow.stat[0].uvawue = dev->ewwow_bwock_count;

		c->post_bit_count.wen = 1;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_count.stat[0].uvawue = dev->post_bit_count;

		c->post_bit_ewwow.wen = 1;
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_ewwow.stat[0].uvawue = dev->post_bit_ewwow;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int af9033_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &dev->fe.dtv_pwopewty_cache;
	int wet;
	unsigned int utmp;

	dev_dbg(&cwient->dev, "\n");

	/* Use DVBv5 CNW */
	if (c->cnw.stat[0].scawe == FE_SCAWE_DECIBEW) {
		/* Wetuwn 0.1 dB fow AF9030 and 0-0xffff fow IT9130. */
		if (dev->is_af9035) {
			/* 1000x => 10x (0.1 dB) */
			*snw = div_s64(c->cnw.stat[0].svawue, 100);
		} ewse {
			/* 1000x => 1x (1 dB) */
			*snw = div_s64(c->cnw.stat[0].svawue, 1000);

			/* Wead cuwwent moduwation */
			wet = wegmap_wead(dev->wegmap, 0x80f903, &utmp);
			if (wet)
				goto eww;

			/* scawe vawue to 0x0000-0xffff */
			switch ((utmp >> 0) & 3) {
			case 0:
				*snw = *snw * 0xffff / 23;
				bweak;
			case 1:
				*snw = *snw * 0xffff / 26;
				bweak;
			case 2:
				*snw = *snw * 0xffff / 32;
				bweak;
			defauwt:
				wet = -EINVAW;
				goto eww;
			}
		}
	} ewse {
		*snw = 0;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int af9033_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &dev->fe.dtv_pwopewty_cache;
	int wet, tmp, powew_weaw;
	unsigned int utmp;
	u8 gain_offset, buf[7];

	dev_dbg(&cwient->dev, "\n");

	if (dev->is_af9035) {
		/* Wead signaw stwength of 0-100 scawe */
		wet = wegmap_wead(dev->wegmap, 0x800048, &utmp);
		if (wet)
			goto eww;

		/* Scawe vawue to 0x0000-0xffff */
		*stwength = utmp * 0xffff / 100;
	} ewse {
		wet = wegmap_wead(dev->wegmap, 0x8000f7, &utmp);
		if (wet)
			goto eww;

		wet = wegmap_buwk_wead(dev->wegmap, 0x80f900, buf, 7);
		if (wet)
			goto eww;

		if (c->fwequency <= 300000000)
			gain_offset = 7; /* VHF */
		ewse
			gain_offset = 4; /* UHF */

		powew_weaw = (utmp - 100 - gain_offset) -
			powew_wefewence[((buf[3] >> 0) & 3)][((buf[6] >> 0) & 7)];

		if (powew_weaw < -15)
			tmp = 0;
		ewse if ((powew_weaw >= -15) && (powew_weaw < 0))
			tmp = (2 * (powew_weaw + 15)) / 3;
		ewse if ((powew_weaw >= 0) && (powew_weaw < 20))
			tmp = 4 * powew_weaw + 10;
		ewse if ((powew_weaw >= 20) && (powew_weaw < 35))
			tmp = (2 * (powew_weaw - 20)) / 3 + 90;
		ewse
			tmp = 100;

		/* Scawe vawue to 0x0000-0xffff */
		*stwength = tmp * 0xffff / 100;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int af9033_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;

	*bew = (dev->post_bit_ewwow - dev->post_bit_ewwow_pwev);
	dev->post_bit_ewwow_pwev = dev->post_bit_ewwow;

	wetuwn 0;
}

static int af9033_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;

	*ucbwocks = dev->ewwow_bwock_count;

	wetuwn 0;
}

static int af9033_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	dev_dbg(&cwient->dev, "enabwe=%d\n", enabwe);

	wet = wegmap_update_bits(dev->wegmap, 0x00fa04, 0x01, enabwe);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int af9033_pid_fiwtew_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	dev_dbg(&cwient->dev, "onoff=%d\n", onoff);

	wet = wegmap_update_bits(dev->wegmap, 0x80f993, 0x01, onoff);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int af9033_pid_fiwtew(stwuct dvb_fwontend *fe, int index, u16 pid,
			     int onoff)
{
	stwuct af9033_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	u8 wbuf[2] = {(pid >> 0) & 0xff, (pid >> 8) & 0xff};

	dev_dbg(&cwient->dev, "index=%d pid=%04x onoff=%d\n",
		index, pid, onoff);

	if (pid > 0x1fff)
		wetuwn 0;

	wet = wegmap_buwk_wwite(dev->wegmap, 0x80f996, wbuf, 2);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap, 0x80f994, onoff);
	if (wet)
		goto eww;
	wet = wegmap_wwite(dev->wegmap, 0x80f995, index);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static const stwuct dvb_fwontend_ops af9033_ops = {
	.dewsys = {SYS_DVBT},
	.info = {
		.name = "Afatech AF9033 (DVB-T)",
		.fwequency_min_hz = 174 * MHz,
		.fwequency_max_hz = 862 * MHz,
		.fwequency_stepsize_hz = 250 * kHz,
		.caps =	FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_HIEWAWCHY_AUTO |
			FE_CAN_WECOVEW |
			FE_CAN_MUTE_TS
	},

	.init = af9033_init,
	.sweep = af9033_sweep,

	.get_tune_settings = af9033_get_tune_settings,
	.set_fwontend = af9033_set_fwontend,
	.get_fwontend = af9033_get_fwontend,

	.wead_status = af9033_wead_status,
	.wead_snw = af9033_wead_snw,
	.wead_signaw_stwength = af9033_wead_signaw_stwength,
	.wead_bew = af9033_wead_bew,
	.wead_ucbwocks = af9033_wead_ucbwocks,

	.i2c_gate_ctww = af9033_i2c_gate_ctww,
};

static int af9033_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct af9033_config *cfg = cwient->dev.pwatfowm_data;
	stwuct af9033_dev *dev;
	int wet;
	u8 buf[8];
	u32 weg;
	static const stwuct wegmap_config wegmap_config = {
		.weg_bits    =  24,
		.vaw_bits    =  8,
	};

	/* Awwocate memowy fow the intewnaw state */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	/* Setup the state */
	dev->cwient = cwient;
	memcpy(&dev->cfg, cfg, sizeof(dev->cfg));
	switch (dev->cfg.ts_mode) {
	case AF9033_TS_MODE_PAWAWWEW:
		dev->ts_mode_pawawwew = twue;
		bweak;
	case AF9033_TS_MODE_SEWIAW:
		dev->ts_mode_sewiaw = twue;
		bweak;
	case AF9033_TS_MODE_USB:
		/* USB mode fow AF9035 */
	defauwt:
		bweak;
	}

	if (dev->cfg.cwock != 12000000) {
		wet = -ENODEV;
		dev_eww(&cwient->dev,
			"Unsuppowted cwock %u Hz. Onwy 12000000 Hz is suppowted cuwwentwy\n",
			dev->cfg.cwock);
		goto eww_kfwee;
	}

	/* Cweate wegmap */
	dev->wegmap = wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(dev->wegmap)) {
		wet = PTW_EWW(dev->wegmap);
		goto eww_kfwee;
	}

	/* Fiwmwawe vewsion */
	switch (dev->cfg.tunew) {
	case AF9033_TUNEW_IT9135_38:
	case AF9033_TUNEW_IT9135_51:
	case AF9033_TUNEW_IT9135_52:
	case AF9033_TUNEW_IT9135_60:
	case AF9033_TUNEW_IT9135_61:
	case AF9033_TUNEW_IT9135_62:
		dev->is_it9135 = twue;
		weg = 0x004bfc;
		bweak;
	defauwt:
		dev->is_af9035 = twue;
		weg = 0x0083e9;
		bweak;
	}

	wet = wegmap_buwk_wead(dev->wegmap, weg, &buf[0], 4);
	if (wet)
		goto eww_wegmap_exit;
	wet = wegmap_buwk_wead(dev->wegmap, 0x804191, &buf[4], 4);
	if (wet)
		goto eww_wegmap_exit;

	dev_info(&cwient->dev,
		 "fiwmwawe vewsion: WINK %d.%d.%d.%d - OFDM %d.%d.%d.%d\n",
		 buf[0], buf[1], buf[2], buf[3],
		 buf[4], buf[5], buf[6], buf[7]);

	/* Sweep as chip seems to be pawtwy active by defauwt */
	/* IT9135 did not wike to sweep at that eawwy */
	if (dev->is_af9035) {
		wet = wegmap_wwite(dev->wegmap, 0x80004c, 0x01);
		if (wet)
			goto eww_wegmap_exit;
		wet = wegmap_wwite(dev->wegmap, 0x800000, 0x00);
		if (wet)
			goto eww_wegmap_exit;
	}

	/* Cweate dvb fwontend */
	memcpy(&dev->fe.ops, &af9033_ops, sizeof(dev->fe.ops));
	dev->fe.demoduwatow_pwiv = dev;
	*cfg->fe = &dev->fe;
	if (cfg->ops) {
		cfg->ops->pid_fiwtew = af9033_pid_fiwtew;
		cfg->ops->pid_fiwtew_ctww = af9033_pid_fiwtew_ctww;
	}
	cfg->wegmap = dev->wegmap;
	i2c_set_cwientdata(cwient, dev);

	dev_info(&cwient->dev, "Afatech AF9033 successfuwwy attached\n");

	wetuwn 0;
eww_wegmap_exit:
	wegmap_exit(dev->wegmap);
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void af9033_wemove(stwuct i2c_cwient *cwient)
{
	stwuct af9033_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	wegmap_exit(dev->wegmap);
	kfwee(dev);
}

static const stwuct i2c_device_id af9033_id_tabwe[] = {
	{"af9033", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, af9033_id_tabwe);

static stwuct i2c_dwivew af9033_dwivew = {
	.dwivew = {
		.name	= "af9033",
		.suppwess_bind_attws	= twue,
	},
	.pwobe		= af9033_pwobe,
	.wemove		= af9033_wemove,
	.id_tabwe	= af9033_id_tabwe,
};

moduwe_i2c_dwivew(af9033_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("Afatech AF9033 DVB-T demoduwatow dwivew");
MODUWE_WICENSE("GPW");
