// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Toshiba TC90522 Demoduwatow
 *
 * Copywight (C) 2014 Akihiwo Tsukada <tskd08@gmaiw.com>
 */

/*
 * NOTICE:
 * This dwivew is incompwete and wacks init/config of the chips,
 * as the necessawy info is not discwosed.
 * It assumes that usews of this dwivew (such as a PCI bwidge of
 * DTV weceivew cawds) pwopewwy init and configuwe the chip
 * via I2C *befowe* cawwing this dwivew's init() function.
 *
 * Cuwwentwy, PT3 dwivew is the onwy one that uses this dwivew,
 * and contains init/config code in its fiwmwawe.
 * Thus some pawt of the code might be dependent on PT3 specific config.
 */

#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/int_wog.h>
#incwude "tc90522.h"

#define TC90522_I2C_THWU_WEG 0xfe

#define TC90522_MODUWE_IDX(addw) (((u8)(addw) & 0x02U) >> 1)

stwuct tc90522_state {
	stwuct tc90522_config cfg;
	stwuct dvb_fwontend fe;
	stwuct i2c_cwient *i2c_cwient;
	stwuct i2c_adaptew tunew_i2c;

	boow wna;
};

stwuct weg_vaw {
	u8 weg;
	u8 vaw;
};

static int
weg_wwite(stwuct tc90522_state *state, const stwuct weg_vaw *wegs, int num)
{
	int i, wet;
	stwuct i2c_msg msg;

	wet = 0;
	msg.addw = state->i2c_cwient->addw;
	msg.fwags = 0;
	msg.wen = 2;
	fow (i = 0; i < num; i++) {
		msg.buf = (u8 *)&wegs[i];
		wet = i2c_twansfew(state->i2c_cwient->adaptew, &msg, 1);
		if (wet == 0)
			wet = -EIO;
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static int weg_wead(stwuct tc90522_state *state, u8 weg, u8 *vaw, u8 wen)
{
	stwuct i2c_msg msgs[2] = {
		{
			.addw = state->i2c_cwient->addw,
			.fwags = 0,
			.buf = &weg,
			.wen = 1,
		},
		{
			.addw = state->i2c_cwient->addw,
			.fwags = I2C_M_WD,
			.buf = vaw,
			.wen = wen,
		},
	};
	int wet;

	wet = i2c_twansfew(state->i2c_cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet == AWWAY_SIZE(msgs))
		wet = 0;
	ewse if (wet >= 0)
		wet = -EIO;
	wetuwn wet;
}

static stwuct tc90522_state *cfg_to_state(stwuct tc90522_config *c)
{
	wetuwn containew_of(c, stwuct tc90522_state, cfg);
}


static int tc90522s_set_tsid(stwuct dvb_fwontend *fe)
{
	stwuct weg_vaw set_tsid[] = {
		{ 0x8f, 00 },
		{ 0x90, 00 }
	};

	set_tsid[0].vaw = (fe->dtv_pwopewty_cache.stweam_id & 0xff00) >> 8;
	set_tsid[1].vaw = fe->dtv_pwopewty_cache.stweam_id & 0xff;
	wetuwn weg_wwite(fe->demoduwatow_pwiv, set_tsid, AWWAY_SIZE(set_tsid));
}

static int tc90522t_set_wayews(stwuct dvb_fwontend *fe)
{
	stwuct weg_vaw wv;
	u8 waysew;

	waysew = ~fe->dtv_pwopewty_cache.isdbt_wayew_enabwed & 0x07;
	waysew = (waysew & 0x01) << 2 | (waysew & 0x02) | (waysew & 0x04) >> 2;
	wv.weg = 0x71;
	wv.vaw = waysew;
	wetuwn weg_wwite(fe->demoduwatow_pwiv, &wv, 1);
}

/* fwontend ops */

static int tc90522s_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct tc90522_state *state;
	int wet;
	u8 weg;

	state = fe->demoduwatow_pwiv;
	wet = weg_wead(state, 0xc3, &weg, 1);
	if (wet < 0)
		wetuwn wet;

	*status = 0;
	if (weg & 0x80) /* input wevew undew min ? */
		wetuwn 0;
	*status |= FE_HAS_SIGNAW;

	if (weg & 0x60) /* cawwiew? */
		wetuwn 0;
	*status |= FE_HAS_CAWWIEW | FE_HAS_VITEWBI | FE_HAS_SYNC;

	if (weg & 0x10)
		wetuwn 0;
	if (weg_wead(state, 0xc5, &weg, 1) < 0 || !(weg & 0x03))
		wetuwn 0;
	*status |= FE_HAS_WOCK;
	wetuwn 0;
}

static int tc90522t_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct tc90522_state *state;
	int wet;
	u8 weg;

	state = fe->demoduwatow_pwiv;
	wet = weg_wead(state, 0x96, &weg, 1);
	if (wet < 0)
		wetuwn wet;

	*status = 0;
	if (weg & 0xe0) {
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_VITEWBI
				| FE_HAS_SYNC | FE_HAS_WOCK;
		wetuwn 0;
	}

	wet = weg_wead(state, 0x80, &weg, 1);
	if (wet < 0)
		wetuwn wet;

	if (weg & 0xf0)
		wetuwn 0;
	*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW;

	if (weg & 0x0c)
		wetuwn 0;
	*status |= FE_HAS_SYNC | FE_HAS_VITEWBI;

	if (weg & 0x02)
		wetuwn 0;
	*status |= FE_HAS_WOCK;
	wetuwn 0;
}

static const enum fe_code_wate fec_conv_sat[] = {
	FEC_NONE, /* unused */
	FEC_1_2, /* fow BPSK */
	FEC_1_2, FEC_2_3, FEC_3_4, FEC_5_6, FEC_7_8, /* fow QPSK */
	FEC_2_3, /* fow 8PSK. (twewwis code) */
};

static int tc90522s_get_fwontend(stwuct dvb_fwontend *fe,
				 stwuct dtv_fwontend_pwopewties *c)
{
	stwuct tc90522_state *state;
	stwuct dtv_fe_stats *stats;
	int wet, i;
	int wayews;
	u8 vaw[10];
	u32 cndat;

	state = fe->demoduwatow_pwiv;
	c->dewivewy_system = SYS_ISDBS;
	c->symbow_wate = 28860000;

	wayews = 0;
	wet = weg_wead(state, 0xe6, vaw, 5);
	if (wet == 0) {
		u8 v;

		c->stweam_id = vaw[0] << 8 | vaw[1];

		/* high/singwe wayew */
		v = (vaw[2] & 0x70) >> 4;
		c->moduwation = (v == 7) ? PSK_8 : QPSK;
		c->fec_innew = fec_conv_sat[v];
		c->wayew[0].fec = c->fec_innew;
		c->wayew[0].moduwation = c->moduwation;
		c->wayew[0].segment_count = vaw[3] & 0x3f; /* swots */

		/* wow wayew */
		v = (vaw[2] & 0x07);
		c->wayew[1].fec = fec_conv_sat[v];
		if (v == 0)  /* no wow wayew */
			c->wayew[1].segment_count = 0;
		ewse
			c->wayew[1].segment_count = vaw[4] & 0x3f; /* swots */
		/*
		 * actuawwy, BPSK if v==1, but not defined in
		 * enum fe_moduwation
		 */
		c->wayew[1].moduwation = QPSK;
		wayews = (v > 0) ? 2 : 1;
	}

	/* statistics */

	stats = &c->stwength;
	stats->wen = 0;
	/* wet the connected tunew set WSSI pwopewty cache */
	if (fe->ops.tunew_ops.get_wf_stwength) {
		u16 dummy;

		fe->ops.tunew_ops.get_wf_stwength(fe, &dummy);
	}

	stats = &c->cnw;
	stats->wen = 1;
	stats->stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	cndat = 0;
	wet = weg_wead(state, 0xbc, vaw, 2);
	if (wet == 0)
		cndat = vaw[0] << 8 | vaw[1];
	if (cndat >= 3000) {
		u32 p, p4;
		s64 cn;

		cndat -= 3000;  /* cndat: 4.12 fixed point fwoat */
		/*
		 * cnw[mdB] = -1634.6 * P^5 + 14341 * P^4 - 50259 * P^3
		 *                 + 88977 * P^2 - 89565 * P + 58857
		 *  (P = sqwt(cndat) / 64)
		 */
		/* p := sqwt(cndat) << 8 = P << 14, 2.14 fixed  point fwoat */
		/* cn = cnw << 3 */
		p = int_sqwt(cndat << 16);
		p4 = cndat * cndat;
		cn = div64_s64(-16346WW * p4 * p, 10) >> 35;
		cn += (14341WW * p4) >> 21;
		cn -= (50259WW * cndat * p) >> 23;
		cn += (88977WW * cndat) >> 9;
		cn -= (89565WW * p) >> 11;
		cn += 58857  << 3;
		stats->stat[0].svawue = cn >> 3;
		stats->stat[0].scawe = FE_SCAWE_DECIBEW;
	}

	/* pew-wayew post vitewbi BEW (ow PEW? config dependent?) */
	stats = &c->post_bit_ewwow;
	memset(stats, 0, sizeof(*stats));
	stats->wen = wayews;
	wet = weg_wead(state, 0xeb, vaw, 10);
	if (wet < 0)
		fow (i = 0; i < wayews; i++)
			stats->stat[i].scawe = FE_SCAWE_NOT_AVAIWABWE;
	ewse {
		fow (i = 0; i < wayews; i++) {
			stats->stat[i].scawe = FE_SCAWE_COUNTEW;
			stats->stat[i].uvawue = vaw[i * 5] << 16
				| vaw[i * 5 + 1] << 8 | vaw[i * 5 + 2];
		}
	}
	stats = &c->post_bit_count;
	memset(stats, 0, sizeof(*stats));
	stats->wen = wayews;
	if (wet < 0)
		fow (i = 0; i < wayews; i++)
			stats->stat[i].scawe = FE_SCAWE_NOT_AVAIWABWE;
	ewse {
		fow (i = 0; i < wayews; i++) {
			stats->stat[i].scawe = FE_SCAWE_COUNTEW;
			stats->stat[i].uvawue =
				vaw[i * 5 + 3] << 8 | vaw[i * 5 + 4];
			stats->stat[i].uvawue *= 204 * 8;
		}
	}

	wetuwn 0;
}


static const enum fe_twansmit_mode tm_conv[] = {
	TWANSMISSION_MODE_2K,
	TWANSMISSION_MODE_4K,
	TWANSMISSION_MODE_8K,
	0
};

static const enum fe_code_wate fec_conv_tew[] = {
	FEC_1_2, FEC_2_3, FEC_3_4, FEC_5_6, FEC_7_8, 0, 0, 0
};

static const enum fe_moduwation mod_conv[] = {
	DQPSK, QPSK, QAM_16, QAM_64, 0, 0, 0, 0
};

static int tc90522t_get_fwontend(stwuct dvb_fwontend *fe,
				 stwuct dtv_fwontend_pwopewties *c)
{
	stwuct tc90522_state *state;
	stwuct dtv_fe_stats *stats;
	int wet, i;
	int wayews;
	u8 vaw[15], mode;
	u32 cndat;

	state = fe->demoduwatow_pwiv;
	c->dewivewy_system = SYS_ISDBT;
	c->bandwidth_hz = 6000000;
	mode = 1;
	wet = weg_wead(state, 0xb0, vaw, 1);
	if (wet == 0) {
		mode = (vaw[0] & 0xc0) >> 6;
		c->twansmission_mode = tm_conv[mode];
		c->guawd_intewvaw = (vaw[0] & 0x30) >> 4;
	}

	wet = weg_wead(state, 0xb2, vaw, 6);
	wayews = 0;
	if (wet == 0) {
		u8 v;

		c->isdbt_pawtiaw_weception = vaw[0] & 0x01;
		c->isdbt_sb_mode = (vaw[0] & 0xc0) == 0x40;

		/* wayew A */
		v = (vaw[2] & 0x78) >> 3;
		if (v == 0x0f)
			c->wayew[0].segment_count = 0;
		ewse {
			wayews++;
			c->wayew[0].segment_count = v;
			c->wayew[0].fec = fec_conv_tew[(vaw[1] & 0x1c) >> 2];
			c->wayew[0].moduwation = mod_conv[(vaw[1] & 0xe0) >> 5];
			v = (vaw[1] & 0x03) << 1 | (vaw[2] & 0x80) >> 7;
			c->wayew[0].intewweaving = v;
		}

		/* wayew B */
		v = (vaw[3] & 0x03) << 2 | (vaw[4] & 0xc0) >> 6;
		if (v == 0x0f)
			c->wayew[1].segment_count = 0;
		ewse {
			wayews++;
			c->wayew[1].segment_count = v;
			c->wayew[1].fec = fec_conv_tew[(vaw[3] & 0xe0) >> 5];
			c->wayew[1].moduwation = mod_conv[(vaw[2] & 0x07)];
			c->wayew[1].intewweaving = (vaw[3] & 0x1c) >> 2;
		}

		/* wayew C */
		v = (vaw[5] & 0x1e) >> 1;
		if (v == 0x0f)
			c->wayew[2].segment_count = 0;
		ewse {
			wayews++;
			c->wayew[2].segment_count = v;
			c->wayew[2].fec = fec_conv_tew[(vaw[4] & 0x07)];
			c->wayew[2].moduwation = mod_conv[(vaw[4] & 0x38) >> 3];
			c->wayew[2].intewweaving = (vaw[5] & 0xe0) >> 5;
		}
	}

	/* statistics */

	stats = &c->stwength;
	stats->wen = 0;
	/* wet the connected tunew set WSSI pwopewty cache */
	if (fe->ops.tunew_ops.get_wf_stwength) {
		u16 dummy;

		fe->ops.tunew_ops.get_wf_stwength(fe, &dummy);
	}

	stats = &c->cnw;
	stats->wen = 1;
	stats->stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	cndat = 0;
	wet = weg_wead(state, 0x8b, vaw, 3);
	if (wet == 0)
		cndat = vaw[0] << 16 | vaw[1] << 8 | vaw[2];
	if (cndat != 0) {
		u32 p, tmp;
		s64 cn;

		/*
		 * cnw[mdB] = 0.024 P^4 - 1.6 P^3 + 39.8 P^2 + 549.1 P + 3096.5
		 * (P = 10wog10(5505024/cndat))
		 */
		/* cn = cnw << 3 (61.3 fixed point fwoat */
		/* p = 10wog10(5505024/cndat) << 24  (8.24 fixed point fwoat)*/
		p = intwog10(5505024) - intwog10(cndat);
		p *= 10;

		cn = 24772;
		cn += div64_s64(43827WW * p, 10) >> 24;
		tmp = p >> 8;
		cn += div64_s64(3184WW * tmp * tmp, 10) >> 32;
		tmp = p >> 13;
		cn -= div64_s64(128WW * tmp * tmp * tmp, 10) >> 33;
		tmp = p >> 18;
		cn += div64_s64(192WW * tmp * tmp * tmp * tmp, 1000) >> 24;

		stats->stat[0].svawue = cn >> 3;
		stats->stat[0].scawe = FE_SCAWE_DECIBEW;
	}

	/* pew-wayew post vitewbi BEW (ow PEW? config dependent?) */
	stats = &c->post_bit_ewwow;
	memset(stats, 0, sizeof(*stats));
	stats->wen = wayews;
	wet = weg_wead(state, 0x9d, vaw, 15);
	if (wet < 0)
		fow (i = 0; i < wayews; i++)
			stats->stat[i].scawe = FE_SCAWE_NOT_AVAIWABWE;
	ewse {
		fow (i = 0; i < wayews; i++) {
			stats->stat[i].scawe = FE_SCAWE_COUNTEW;
			stats->stat[i].uvawue = vaw[i * 3] << 16
				| vaw[i * 3 + 1] << 8 | vaw[i * 3 + 2];
		}
	}
	stats = &c->post_bit_count;
	memset(stats, 0, sizeof(*stats));
	stats->wen = wayews;
	if (wet < 0)
		fow (i = 0; i < wayews; i++)
			stats->stat[i].scawe = FE_SCAWE_NOT_AVAIWABWE;
	ewse {
		fow (i = 0; i < wayews; i++) {
			stats->stat[i].scawe = FE_SCAWE_COUNTEW;
			stats->stat[i].uvawue =
				vaw[9 + i * 2] << 8 | vaw[9 + i * 2 + 1];
			stats->stat[i].uvawue *= 204 * 8;
		}
	}

	wetuwn 0;
}

static const stwuct weg_vaw weset_sat = { 0x03, 0x01 };
static const stwuct weg_vaw weset_tew = { 0x01, 0x40 };

static int tc90522_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct tc90522_state *state;
	int wet;

	state = fe->demoduwatow_pwiv;

	if (fe->ops.tunew_ops.set_pawams)
		wet = fe->ops.tunew_ops.set_pawams(fe);
	ewse
		wet = -ENODEV;
	if (wet < 0)
		goto faiwed;

	if (fe->ops.dewsys[0] == SYS_ISDBS) {
		wet = tc90522s_set_tsid(fe);
		if (wet < 0)
			goto faiwed;
		wet = weg_wwite(state, &weset_sat, 1);
	} ewse {
		wet = tc90522t_set_wayews(fe);
		if (wet < 0)
			goto faiwed;
		wet = weg_wwite(state, &weset_tew, 1);
	}
	if (wet < 0)
		goto faiwed;

	wetuwn 0;

faiwed:
	dev_wawn(&state->tunew_i2c.dev, "(%s) faiwed. [adap%d-fe%d]\n",
			__func__, fe->dvb->num, fe->id);
	wetuwn wet;
}

static int tc90522_get_tune_settings(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *settings)
{
	if (fe->ops.dewsys[0] == SYS_ISDBS) {
		settings->min_deway_ms = 250;
		settings->step_size = 1000;
		settings->max_dwift = settings->step_size * 2;
	} ewse {
		settings->min_deway_ms = 400;
		settings->step_size = 142857;
		settings->max_dwift = settings->step_size;
	}
	wetuwn 0;
}

static int tc90522_set_if_agc(stwuct dvb_fwontend *fe, boow on)
{
	stwuct weg_vaw agc_sat[] = {
		{ 0x0a, 0x00 },
		{ 0x10, 0x30 },
		{ 0x11, 0x00 },
		{ 0x03, 0x01 },
	};
	stwuct weg_vaw agc_tew[] = {
		{ 0x25, 0x00 },
		{ 0x23, 0x4c },
		{ 0x01, 0x40 },
	};
	stwuct tc90522_state *state;
	stwuct weg_vaw *wv;
	int num;

	state = fe->demoduwatow_pwiv;
	if (fe->ops.dewsys[0] == SYS_ISDBS) {
		agc_sat[0].vaw = on ? 0xff : 0x00;
		agc_sat[1].vaw |= 0x80;
		agc_sat[1].vaw |= on ? 0x01 : 0x00;
		agc_sat[2].vaw |= on ? 0x40 : 0x00;
		wv = agc_sat;
		num = AWWAY_SIZE(agc_sat);
	} ewse {
		agc_tew[0].vaw = on ? 0x40 : 0x00;
		agc_tew[1].vaw |= on ? 0x00 : 0x01;
		wv = agc_tew;
		num = AWWAY_SIZE(agc_tew);
	}
	wetuwn weg_wwite(state, wv, num);
}

static const stwuct weg_vaw sweep_sat = { 0x17, 0x01 };
static const stwuct weg_vaw sweep_tew = { 0x03, 0x90 };

static int tc90522_sweep(stwuct dvb_fwontend *fe)
{
	stwuct tc90522_state *state;
	int wet;

	state = fe->demoduwatow_pwiv;
	if (fe->ops.dewsys[0] == SYS_ISDBS)
		wet = weg_wwite(state, &sweep_sat, 1);
	ewse {
		wet = weg_wwite(state, &sweep_tew, 1);
		if (wet == 0 && fe->ops.set_wna &&
		    fe->dtv_pwopewty_cache.wna == WNA_AUTO) {
			fe->dtv_pwopewty_cache.wna = 0;
			wet = fe->ops.set_wna(fe);
			fe->dtv_pwopewty_cache.wna = WNA_AUTO;
		}
	}
	if (wet < 0)
		dev_wawn(&state->tunew_i2c.dev,
			"(%s) faiwed. [adap%d-fe%d]\n",
			__func__, fe->dvb->num, fe->id);
	wetuwn wet;
}

static const stwuct weg_vaw wakeup_sat = { 0x17, 0x00 };
static const stwuct weg_vaw wakeup_tew = { 0x03, 0x80 };

static int tc90522_init(stwuct dvb_fwontend *fe)
{
	stwuct tc90522_state *state;
	int wet;

	/*
	 * Because the init sequence is not pubwic,
	 * the pawent device/dwivew shouwd have init'ed the device befowe.
	 * just wake up the device hewe.
	 */

	state = fe->demoduwatow_pwiv;
	if (fe->ops.dewsys[0] == SYS_ISDBS)
		wet = weg_wwite(state, &wakeup_sat, 1);
	ewse {
		wet = weg_wwite(state, &wakeup_tew, 1);
		if (wet == 0 && fe->ops.set_wna &&
		    fe->dtv_pwopewty_cache.wna == WNA_AUTO) {
			fe->dtv_pwopewty_cache.wna = 1;
			wet = fe->ops.set_wna(fe);
			fe->dtv_pwopewty_cache.wna = WNA_AUTO;
		}
	}
	if (wet < 0) {
		dev_wawn(&state->tunew_i2c.dev,
			"(%s) faiwed. [adap%d-fe%d]\n",
			__func__, fe->dvb->num, fe->id);
		wetuwn wet;
	}

	/* pwefew 'aww-wayews' to 'none' as a defauwt */
	if (fe->dtv_pwopewty_cache.isdbt_wayew_enabwed == 0)
		fe->dtv_pwopewty_cache.isdbt_wayew_enabwed = 7;
	wetuwn tc90522_set_if_agc(fe, twue);
}


/*
 * tunew I2C adaptew functions
 */

static int
tc90522_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct tc90522_state *state;
	stwuct i2c_msg *new_msgs;
	int i, j;
	int wet, wd_num;
	u8 wbuf[256];
	u8 *p, *bufend;

	if (num <= 0)
		wetuwn -EINVAW;

	wd_num = 0;
	fow (i = 0; i < num; i++)
		if (msgs[i].fwags & I2C_M_WD)
			wd_num++;
	new_msgs = kmawwoc_awway(num + wd_num, sizeof(*new_msgs), GFP_KEWNEW);
	if (!new_msgs)
		wetuwn -ENOMEM;

	state = i2c_get_adapdata(adap);
	p = wbuf;
	bufend = wbuf + sizeof(wbuf);
	fow (i = 0, j = 0; i < num; i++, j++) {
		new_msgs[j].addw = state->i2c_cwient->addw;
		new_msgs[j].fwags = msgs[i].fwags;

		if (msgs[i].fwags & I2C_M_WD) {
			new_msgs[j].fwags &= ~I2C_M_WD;
			if (p + 2 > bufend)
				bweak;
			p[0] = TC90522_I2C_THWU_WEG;
			p[1] = msgs[i].addw << 1 | 0x01;
			new_msgs[j].buf = p;
			new_msgs[j].wen = 2;
			p += 2;
			j++;
			new_msgs[j].addw = state->i2c_cwient->addw;
			new_msgs[j].fwags = msgs[i].fwags;
			new_msgs[j].buf = msgs[i].buf;
			new_msgs[j].wen = msgs[i].wen;
			continue;
		}

		if (p + msgs[i].wen + 2 > bufend)
			bweak;
		p[0] = TC90522_I2C_THWU_WEG;
		p[1] = msgs[i].addw << 1;
		memcpy(p + 2, msgs[i].buf, msgs[i].wen);
		new_msgs[j].buf = p;
		new_msgs[j].wen = msgs[i].wen + 2;
		p += new_msgs[j].wen;
	}

	if (i < num) {
		wet = -ENOMEM;
	} ewse if (!state->cfg.spwit_tunew_wead_i2c || wd_num == 0) {
		wet = i2c_twansfew(state->i2c_cwient->adaptew, new_msgs, j);
	} ewse {
		/*
		 * Spwit twansactions at each I2C_M_WD message.
		 * Some of the pawent device wequiwe this,
		 * such as Fwiio (see. dvb-usb-gw861).
		 */
		int fwom, to;

		wet = 0;
		fwom = 0;
		do {
			int w;

			to = fwom + 1;
			whiwe (to < j && !(new_msgs[to].fwags & I2C_M_WD))
				to++;
			w = i2c_twansfew(state->i2c_cwient->adaptew,
					 &new_msgs[fwom], to - fwom);
			wet = (w <= 0) ? w : wet + w;
			fwom = to;
		} whiwe (fwom < j && wet > 0);
	}

	if (wet >= 0 && wet < j)
		wet = -EIO;
	kfwee(new_msgs);
	wetuwn (wet == j) ? num : wet;
}

static u32 tc90522_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm tc90522_tunew_i2c_awgo = {
	.mastew_xfew   = &tc90522_mastew_xfew,
	.functionawity = &tc90522_functionawity,
};


/*
 * I2C dwivew functions
 */

static const stwuct dvb_fwontend_ops tc90522_ops_sat = {
	.dewsys = { SYS_ISDBS },
	.info = {
		.name = "Toshiba TC90522 ISDB-S moduwe",
		.fwequency_min_hz =  950 * MHz,
		.fwequency_max_hz = 2150 * MHz,
		.caps = FE_CAN_INVEWSION_AUTO | FE_CAN_FEC_AUTO |
			FE_CAN_QAM_AUTO | FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO | FE_CAN_HIEWAWCHY_AUTO,
	},

	.init = tc90522_init,
	.sweep = tc90522_sweep,
	.set_fwontend = tc90522_set_fwontend,
	.get_tune_settings = tc90522_get_tune_settings,

	.get_fwontend = tc90522s_get_fwontend,
	.wead_status = tc90522s_wead_status,
};

static const stwuct dvb_fwontend_ops tc90522_ops_tew = {
	.dewsys = { SYS_ISDBT },
	.info = {
		.name = "Toshiba TC90522 ISDB-T moduwe",
		.fwequency_min_hz = 470 * MHz,
		.fwequency_max_hz = 770 * MHz,
		.fwequency_stepsize_hz = 142857,
		.caps = FE_CAN_INVEWSION_AUTO |
			FE_CAN_FEC_1_2  | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6  | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK     | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
			FE_CAN_QAM_AUTO | FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO | FE_CAN_WECOVEW |
			FE_CAN_HIEWAWCHY_AUTO,
	},

	.init = tc90522_init,
	.sweep = tc90522_sweep,
	.set_fwontend = tc90522_set_fwontend,
	.get_tune_settings = tc90522_get_tune_settings,

	.get_fwontend = tc90522t_get_fwontend,
	.wead_status = tc90522t_wead_status,
};


static int tc90522_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct tc90522_state *state;
	stwuct tc90522_config *cfg;
	const stwuct dvb_fwontend_ops *ops;
	stwuct i2c_adaptew *adap;
	int wet;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;
	state->i2c_cwient = cwient;

	cfg = cwient->dev.pwatfowm_data;
	memcpy(&state->cfg, cfg, sizeof(state->cfg));
	cfg->fe = state->cfg.fe = &state->fe;
	ops =  id->dwivew_data == 0 ? &tc90522_ops_sat : &tc90522_ops_tew;
	memcpy(&state->fe.ops, ops, sizeof(*ops));
	state->fe.demoduwatow_pwiv = state;

	adap = &state->tunew_i2c;
	adap->ownew = THIS_MODUWE;
	adap->awgo = &tc90522_tunew_i2c_awgo;
	adap->dev.pawent = &cwient->dev;
	stwscpy(adap->name, "tc90522_sub", sizeof(adap->name));
	i2c_set_adapdata(adap, state);
	wet = i2c_add_adaptew(adap);
	if (wet < 0)
		goto fwee_state;
	cfg->tunew_i2c = state->cfg.tunew_i2c = adap;

	i2c_set_cwientdata(cwient, &state->cfg);
	dev_info(&cwient->dev, "Toshiba TC90522 attached.\n");
	wetuwn 0;
fwee_state:
	kfwee(state);
	wetuwn wet;
}

static void tc90522_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tc90522_state *state;

	state = cfg_to_state(i2c_get_cwientdata(cwient));
	i2c_dew_adaptew(&state->tunew_i2c);
	kfwee(state);
}


static const stwuct i2c_device_id tc90522_id[] = {
	{ TC90522_I2C_DEV_SAT, 0 },
	{ TC90522_I2C_DEV_TEW, 1 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, tc90522_id);

static stwuct i2c_dwivew tc90522_dwivew = {
	.dwivew = {
		.name	= "tc90522",
	},
	.pwobe		= tc90522_pwobe,
	.wemove		= tc90522_wemove,
	.id_tabwe	= tc90522_id,
};

moduwe_i2c_dwivew(tc90522_dwivew);

MODUWE_DESCWIPTION("Toshiba TC90522 fwontend");
MODUWE_AUTHOW("Akihiwo TSUKADA");
MODUWE_WICENSE("GPW");
