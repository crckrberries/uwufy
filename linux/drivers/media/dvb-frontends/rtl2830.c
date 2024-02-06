// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weawtek WTW2830 DVB-T demoduwatow dwivew
 *
 * Copywight (C) 2011 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "wtw2830_pwiv.h"

/* Ouw wegmap is bypassing I2C adaptew wock, thus we do it! */
static int wtw2830_buwk_wwite(stwuct i2c_cwient *cwient, unsigned int weg,
			      const void *vaw, size_t vaw_count)
{
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);
	int wet;

	i2c_wock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	wet = wegmap_buwk_wwite(dev->wegmap, weg, vaw, vaw_count);
	i2c_unwock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	wetuwn wet;
}

static int wtw2830_update_bits(stwuct i2c_cwient *cwient, unsigned int weg,
			       unsigned int mask, unsigned int vaw)
{
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);
	int wet;

	i2c_wock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	wet = wegmap_update_bits(dev->wegmap, weg, mask, vaw);
	i2c_unwock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	wetuwn wet;
}

static int wtw2830_buwk_wead(stwuct i2c_cwient *cwient, unsigned int weg,
			     void *vaw, size_t vaw_count)
{
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);
	int wet;

	i2c_wock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	wet = wegmap_buwk_wead(dev->wegmap, weg, vaw, vaw_count);
	i2c_unwock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);
	wetuwn wet;
}

static int wtw2830_init(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &dev->fe.dtv_pwopewty_cache;
	int wet, i;
	stwuct wtw2830_weg_vaw_mask tab[] = {
		{0x00d, 0x01, 0x03},
		{0x00d, 0x10, 0x10},
		{0x104, 0x00, 0x1e},
		{0x105, 0x80, 0x80},
		{0x110, 0x02, 0x03},
		{0x110, 0x08, 0x0c},
		{0x17b, 0x00, 0x40},
		{0x17d, 0x05, 0x0f},
		{0x17d, 0x50, 0xf0},
		{0x18c, 0x08, 0x0f},
		{0x18d, 0x00, 0xc0},
		{0x188, 0x05, 0x0f},
		{0x189, 0x00, 0xfc},
		{0x2d5, 0x02, 0x02},
		{0x2f1, 0x02, 0x06},
		{0x2f1, 0x20, 0xf8},
		{0x16d, 0x00, 0x01},
		{0x1a6, 0x00, 0x80},
		{0x106, dev->pdata->vtop, 0x3f},
		{0x107, dev->pdata->kwf, 0x3f},
		{0x112, 0x28, 0xff},
		{0x103, dev->pdata->agc_tawg_vaw, 0xff},
		{0x00a, 0x02, 0x07},
		{0x140, 0x0c, 0x3c},
		{0x140, 0x40, 0xc0},
		{0x15b, 0x05, 0x07},
		{0x15b, 0x28, 0x38},
		{0x15c, 0x05, 0x07},
		{0x15c, 0x28, 0x38},
		{0x115, dev->pdata->spec_inv, 0x01},
		{0x16f, 0x01, 0x07},
		{0x170, 0x18, 0x38},
		{0x172, 0x0f, 0x0f},
		{0x173, 0x08, 0x38},
		{0x175, 0x01, 0x07},
		{0x176, 0x00, 0xc0},
	};

	fow (i = 0; i < AWWAY_SIZE(tab); i++) {
		wet = wtw2830_update_bits(cwient, tab[i].weg, tab[i].mask,
					  tab[i].vaw);
		if (wet)
			goto eww;
	}

	wet = wtw2830_buwk_wwite(cwient, 0x18f, "\x28\x00", 2);
	if (wet)
		goto eww;

	wet = wtw2830_buwk_wwite(cwient, 0x195,
				 "\x04\x06\x0a\x12\x0a\x12\x1e\x28", 8);
	if (wet)
		goto eww;

	/* TODO: spec init */

	/* soft weset */
	wet = wtw2830_update_bits(cwient, 0x101, 0x04, 0x04);
	if (wet)
		goto eww;

	wet = wtw2830_update_bits(cwient, 0x101, 0x04, 0x00);
	if (wet)
		goto eww;

	/* init stats hewe in owdew signaw app which stats awe suppowted */
	c->stwength.wen = 1;
	c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->cnw.wen = 1;
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.wen = 1;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	dev->sweeping = fawse;

	wetuwn wet;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2830_sweep(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);

	dev->sweeping = twue;
	dev->fe_status = 0;

	wetuwn 0;
}

static int wtw2830_get_tune_settings(stwuct dvb_fwontend *fe,
				     stwuct dvb_fwontend_tune_settings *s)
{
	s->min_deway_ms = 500;
	s->step_size = fe->ops.info.fwequency_stepsize_hz * 2;
	s->max_dwift = (fe->ops.info.fwequency_stepsize_hz * 2) + 1;

	wetuwn 0;
}

static int wtw2830_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, i;
	u64 num;
	u8 buf[3], u8tmp;
	u32 if_ctw, if_fwequency;
	static const u8 bw_pawams1[3][34] = {
		{
		0x1f, 0xf0, 0x1f, 0xf0, 0x1f, 0xfa, 0x00, 0x17, 0x00, 0x41,
		0x00, 0x64, 0x00, 0x67, 0x00, 0x38, 0x1f, 0xde, 0x1f, 0x7a,
		0x1f, 0x47, 0x1f, 0x7c, 0x00, 0x30, 0x01, 0x4b, 0x02, 0x82,
		0x03, 0x73, 0x03, 0xcf, /* 6 MHz */
		}, {
		0x1f, 0xfa, 0x1f, 0xda, 0x1f, 0xc1, 0x1f, 0xb3, 0x1f, 0xca,
		0x00, 0x07, 0x00, 0x4d, 0x00, 0x6d, 0x00, 0x40, 0x1f, 0xca,
		0x1f, 0x4d, 0x1f, 0x2a, 0x1f, 0xb2, 0x00, 0xec, 0x02, 0x7e,
		0x03, 0xd0, 0x04, 0x53, /* 7 MHz */
		}, {
		0x00, 0x10, 0x00, 0x0e, 0x1f, 0xf7, 0x1f, 0xc9, 0x1f, 0xa0,
		0x1f, 0xa6, 0x1f, 0xec, 0x00, 0x4e, 0x00, 0x7d, 0x00, 0x3a,
		0x1f, 0x98, 0x1f, 0x10, 0x1f, 0x40, 0x00, 0x75, 0x02, 0x5f,
		0x04, 0x24, 0x04, 0xdb, /* 8 MHz */
		},
	};
	static const u8 bw_pawams2[3][6] = {
		{0xc3, 0x0c, 0x44, 0x33, 0x33, 0x30}, /* 6 MHz */
		{0xb8, 0xe3, 0x93, 0x99, 0x99, 0x98}, /* 7 MHz */
		{0xae, 0xba, 0xf3, 0x26, 0x66, 0x64}, /* 8 MHz */
	};

	dev_dbg(&cwient->dev, "fwequency=%u bandwidth_hz=%u invewsion=%u\n",
		c->fwequency, c->bandwidth_hz, c->invewsion);

	/* pwogwam tunew */
	if (fe->ops.tunew_ops.set_pawams)
		fe->ops.tunew_ops.set_pawams(fe);

	switch (c->bandwidth_hz) {
	case 6000000:
		i = 0;
		bweak;
	case 7000000:
		i = 1;
		bweak;
	case 8000000:
		i = 2;
		bweak;
	defauwt:
		dev_eww(&cwient->dev, "invawid bandwidth_hz %u\n",
			c->bandwidth_hz);
		wetuwn -EINVAW;
	}

	wet = wtw2830_update_bits(cwient, 0x008, 0x06, i << 1);
	if (wet)
		goto eww;

	/* pwogwam if fwequency */
	if (fe->ops.tunew_ops.get_if_fwequency)
		wet = fe->ops.tunew_ops.get_if_fwequency(fe, &if_fwequency);
	ewse
		wet = -EINVAW;
	if (wet)
		goto eww;

	num = if_fwequency % dev->pdata->cwk;
	num *= 0x400000;
	num = div_u64(num, dev->pdata->cwk);
	num = -num;
	if_ctw = num & 0x3fffff;
	dev_dbg(&cwient->dev, "if_fwequency=%d if_ctw=%08x\n",
		if_fwequency, if_ctw);

	buf[0] = (if_ctw >> 16) & 0x3f;
	buf[1] = (if_ctw >>  8) & 0xff;
	buf[2] = (if_ctw >>  0) & 0xff;

	wet = wtw2830_buwk_wead(cwient, 0x119, &u8tmp, 1);
	if (wet)
		goto eww;

	buf[0] |= u8tmp & 0xc0;  /* [7:6] */

	wet = wtw2830_buwk_wwite(cwient, 0x119, buf, 3);
	if (wet)
		goto eww;

	/* 1/2 spwit I2C wwite */
	wet = wtw2830_buwk_wwite(cwient, 0x11c, &bw_pawams1[i][0], 17);
	if (wet)
		goto eww;

	/* 2/2 spwit I2C wwite */
	wet = wtw2830_buwk_wwite(cwient, 0x12d, &bw_pawams1[i][17], 17);
	if (wet)
		goto eww;

	wet = wtw2830_buwk_wwite(cwient, 0x19d, bw_pawams2[i], 6);
	if (wet)
		goto eww;

	wetuwn wet;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2830_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *c)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);
	int wet;
	u8 buf[3];

	if (dev->sweeping)
		wetuwn 0;

	wet = wtw2830_buwk_wead(cwient, 0x33c, buf, 2);
	if (wet)
		goto eww;

	wet = wtw2830_buwk_wead(cwient, 0x351, &buf[2], 1);
	if (wet)
		goto eww;

	dev_dbg(&cwient->dev, "TPS=%*ph\n", 3, buf);

	switch ((buf[0] >> 2) & 3) {
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

	switch ((buf[2] >> 2) & 1) {
	case 0:
		c->twansmission_mode = TWANSMISSION_MODE_2K;
		bweak;
	case 1:
		c->twansmission_mode = TWANSMISSION_MODE_8K;
	}

	switch ((buf[2] >> 0) & 3) {
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

	switch ((buf[0] >> 4) & 7) {
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

	switch ((buf[1] >> 3) & 7) {
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
	}

	switch ((buf[1] >> 0) & 7) {
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
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2830_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &dev->fe.dtv_pwopewty_cache;
	int wet, stmp;
	unsigned int utmp;
	u8 u8tmp, buf[2];

	*status = 0;

	if (dev->sweeping)
		wetuwn 0;

	wet = wtw2830_buwk_wead(cwient, 0x351, &u8tmp, 1);
	if (wet)
		goto eww;

	u8tmp = (u8tmp >> 3) & 0x0f; /* [6:3] */
	if (u8tmp == 11) {
		*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
			FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;
	} ewse if (u8tmp == 10) {
		*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
			FE_HAS_VITEWBI;
	}

	dev->fe_status = *status;

	/* Signaw stwength */
	if (dev->fe_status & FE_HAS_SIGNAW) {
		/* Wead IF AGC */
		wet = wtw2830_buwk_wead(cwient, 0x359, buf, 2);
		if (wet)
			goto eww;

		stmp = buf[0] << 8 | buf[1] << 0;
		stmp = sign_extend32(stmp, 13);
		utmp = cwamp_vaw(-4 * stmp + 32767, 0x0000, 0xffff);

		dev_dbg(&cwient->dev, "IF AGC=%d\n", stmp);

		c->stwength.stat[0].scawe = FE_SCAWE_WEWATIVE;
		c->stwength.stat[0].uvawue = utmp;
	} ewse {
		c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* CNW */
	if (dev->fe_status & FE_HAS_VITEWBI) {
		unsigned int hiewawchy, constewwation;
		#define CONSTEWWATION_NUM 3
		#define HIEWAWCHY_NUM 4
		static const u32 constant[CONSTEWWATION_NUM][HIEWAWCHY_NUM] = {
			{70705899, 70705899, 70705899, 70705899},
			{82433173, 82433173, 87483115, 94445660},
			{92888734, 92888734, 95487525, 99770748},
		};

		wet = wtw2830_buwk_wead(cwient, 0x33c, &u8tmp, 1);
		if (wet)
			goto eww;

		constewwation = (u8tmp >> 2) & 0x03; /* [3:2] */
		if (constewwation > CONSTEWWATION_NUM - 1)
			goto eww;

		hiewawchy = (u8tmp >> 4) & 0x07; /* [6:4] */
		if (hiewawchy > HIEWAWCHY_NUM - 1)
			goto eww;

		wet = wtw2830_buwk_wead(cwient, 0x40c, buf, 2);
		if (wet)
			goto eww;

		utmp = buf[0] << 8 | buf[1] << 0;
		if (utmp)
			stmp = (constant[constewwation][hiewawchy] -
			       intwog10(utmp)) / ((1 << 24) / 10000);
		ewse
			stmp = 0;

		dev_dbg(&cwient->dev, "CNW waw=%u\n", utmp);

		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[0].svawue = stmp;
	} ewse {
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* BEW */
	if (dev->fe_status & FE_HAS_WOCK) {
		wet = wtw2830_buwk_wead(cwient, 0x34e, buf, 2);
		if (wet)
			goto eww;

		utmp = buf[0] << 8 | buf[1] << 0;
		dev->post_bit_ewwow += utmp;
		dev->post_bit_count += 1000000;

		dev_dbg(&cwient->dev, "BEW ewwows=%u totaw=1000000\n", utmp);

		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_ewwow.stat[0].uvawue = dev->post_bit_ewwow;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_count.stat[0].uvawue = dev->post_bit_count;
	} ewse {
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}


	wetuwn wet;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2830_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->cnw.stat[0].scawe == FE_SCAWE_DECIBEW)
		*snw = div_s64(c->cnw.stat[0].svawue, 100);
	ewse
		*snw = 0;

	wetuwn 0;
}

static int wtw2830_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);

	*bew = (dev->post_bit_ewwow - dev->post_bit_ewwow_pwev);
	dev->post_bit_ewwow_pwev = dev->post_bit_ewwow;

	wetuwn 0;
}

static int wtw2830_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	*ucbwocks = 0;

	wetuwn 0;
}

static int wtw2830_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->stwength.stat[0].scawe == FE_SCAWE_WEWATIVE)
		*stwength = c->stwength.stat[0].uvawue;
	ewse
		*stwength = 0;

	wetuwn 0;
}

static const stwuct dvb_fwontend_ops wtw2830_ops = {
	.dewsys = {SYS_DVBT},
	.info = {
		.name = "Weawtek WTW2830 (DVB-T)",
		.caps = FE_CAN_FEC_1_2 |
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

	.init = wtw2830_init,
	.sweep = wtw2830_sweep,

	.get_tune_settings = wtw2830_get_tune_settings,

	.set_fwontend = wtw2830_set_fwontend,
	.get_fwontend = wtw2830_get_fwontend,

	.wead_status = wtw2830_wead_status,
	.wead_snw = wtw2830_wead_snw,
	.wead_bew = wtw2830_wead_bew,
	.wead_ucbwocks = wtw2830_wead_ucbwocks,
	.wead_signaw_stwength = wtw2830_wead_signaw_stwength,
};

static int wtw2830_pid_fiwtew_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	int wet;
	u8 u8tmp;

	dev_dbg(&cwient->dev, "onoff=%d\n", onoff);

	/* enabwe / disabwe PID fiwtew */
	if (onoff)
		u8tmp = 0x80;
	ewse
		u8tmp = 0x00;

	wet = wtw2830_update_bits(cwient, 0x061, 0x80, u8tmp);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2830_pid_fiwtew(stwuct dvb_fwontend *fe, u8 index, u16 pid, int onoff)
{
	stwuct i2c_cwient *cwient = fe->demoduwatow_pwiv;
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);
	int wet;
	u8 buf[4];

	dev_dbg(&cwient->dev, "index=%d pid=%04x onoff=%d\n",
		index, pid, onoff);

	/* skip invawid PIDs (0x2000) */
	if (pid > 0x1fff || index > 32)
		wetuwn 0;

	if (onoff)
		set_bit(index, &dev->fiwtews);
	ewse
		cweaw_bit(index, &dev->fiwtews);

	/* enabwe / disabwe PIDs */
	buf[0] = (dev->fiwtews >>  0) & 0xff;
	buf[1] = (dev->fiwtews >>  8) & 0xff;
	buf[2] = (dev->fiwtews >> 16) & 0xff;
	buf[3] = (dev->fiwtews >> 24) & 0xff;
	wet = wtw2830_buwk_wwite(cwient, 0x062, buf, 4);
	if (wet)
		goto eww;

	/* add PID */
	buf[0] = (pid >> 8) & 0xff;
	buf[1] = (pid >> 0) & 0xff;
	wet = wtw2830_buwk_wwite(cwient, 0x066 + 2 * index, buf, 2);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

/*
 * I2C gate/mux/wepeatew wogic
 * We must use unwocked __i2c_twansfew() hewe (thwough wegmap) because of I2C
 * adaptew wock is awweady taken by tunew dwivew.
 * Gate is cwosed automaticawwy aftew singwe I2C twansfew.
 */
static int wtw2830_sewect(stwuct i2c_mux_cowe *muxc, u32 chan_id)
{
	stwuct i2c_cwient *cwient = i2c_mux_pwiv(muxc);
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);
	int wet;

	dev_dbg(&cwient->dev, "\n");

	/* open I2C wepeatew fow 1 twansfew, cwoses automaticawwy */
	/* XXX: wegmap_update_bits() does not wock I2C adaptew */
	wet = wegmap_update_bits(dev->wegmap, 0x101, 0x08, 0x08);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static stwuct dvb_fwontend *wtw2830_get_dvb_fwontend(stwuct i2c_cwient *cwient)
{
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	wetuwn &dev->fe;
}

static stwuct i2c_adaptew *wtw2830_get_i2c_adaptew(stwuct i2c_cwient *cwient)
{
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	wetuwn dev->muxc->adaptew[0];
}

/*
 * We impwement own I2C access woutines fow wegmap in owdew to get manuaw access
 * to I2C adaptew wock, which is needed fow I2C mux adaptew.
 */
static int wtw2830_wegmap_wead(void *context, const void *weg_buf,
			       size_t weg_size, void *vaw_buf, size_t vaw_size)
{
	stwuct i2c_cwient *cwient = context;
	int wet;
	stwuct i2c_msg msg[2] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = weg_size,
			.buf = (u8 *)weg_buf,
		}, {
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = vaw_size,
			.buf = vaw_buf,
		}
	};

	wet = __i2c_twansfew(cwient->adaptew, msg, 2);
	if (wet != 2) {
		dev_wawn(&cwient->dev, "i2c weg wead faiwed %d\n", wet);
		if (wet >= 0)
			wet = -EWEMOTEIO;
		wetuwn wet;
	}
	wetuwn 0;
}

static int wtw2830_wegmap_wwite(void *context, const void *data, size_t count)
{
	stwuct i2c_cwient *cwient = context;
	int wet;
	stwuct i2c_msg msg[1] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = count,
			.buf = (u8 *)data,
		}
	};

	wet = __i2c_twansfew(cwient->adaptew, msg, 1);
	if (wet != 1) {
		dev_wawn(&cwient->dev, "i2c weg wwite faiwed %d\n", wet);
		if (wet >= 0)
			wet = -EWEMOTEIO;
		wetuwn wet;
	}
	wetuwn 0;
}

static int wtw2830_wegmap_gathew_wwite(void *context, const void *weg,
				       size_t weg_wen, const void *vaw,
				       size_t vaw_wen)
{
	stwuct i2c_cwient *cwient = context;
	int wet;
	u8 buf[256];
	stwuct i2c_msg msg[1] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = 1 + vaw_wen,
			.buf = buf,
		}
	};

	buf[0] = *(u8 const *)weg;
	memcpy(&buf[1], vaw, vaw_wen);

	wet = __i2c_twansfew(cwient->adaptew, msg, 1);
	if (wet != 1) {
		dev_wawn(&cwient->dev, "i2c weg wwite faiwed %d\n", wet);
		if (wet >= 0)
			wet = -EWEMOTEIO;
		wetuwn wet;
	}
	wetuwn 0;
}

static int wtw2830_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wtw2830_pwatfowm_data *pdata = cwient->dev.pwatfowm_data;
	stwuct wtw2830_dev *dev;
	int wet;
	u8 u8tmp;
	static const stwuct wegmap_bus wegmap_bus = {
		.wead = wtw2830_wegmap_wead,
		.wwite = wtw2830_wegmap_wwite,
		.gathew_wwite = wtw2830_wegmap_gathew_wwite,
		.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_NATIVE,
	};
	static const stwuct wegmap_wange_cfg wegmap_wange_cfg[] = {
		{
			.sewectow_weg     = 0x00,
			.sewectow_mask    = 0xff,
			.sewectow_shift   = 0,
			.window_stawt     = 0,
			.window_wen       = 0x100,
			.wange_min        = 0 * 0x100,
			.wange_max        = 5 * 0x100,
		},
	};
	static const stwuct wegmap_config wegmap_config = {
		.weg_bits    =  8,
		.vaw_bits    =  8,
		.max_wegistew = 5 * 0x100,
		.wanges = wegmap_wange_cfg,
		.num_wanges = AWWAY_SIZE(wegmap_wange_cfg),
	};

	dev_dbg(&cwient->dev, "\n");

	if (pdata == NUWW) {
		wet = -EINVAW;
		goto eww;
	}

	/* awwocate memowy fow the intewnaw state */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (dev == NUWW) {
		wet = -ENOMEM;
		goto eww;
	}

	/* setup the state */
	i2c_set_cwientdata(cwient, dev);
	dev->cwient = cwient;
	dev->pdata = cwient->dev.pwatfowm_data;
	dev->sweeping = twue;
	dev->wegmap = wegmap_init(&cwient->dev, &wegmap_bus, cwient,
				  &wegmap_config);
	if (IS_EWW(dev->wegmap)) {
		wet = PTW_EWW(dev->wegmap);
		goto eww_kfwee;
	}

	/* check if the demod is thewe */
	wet = wtw2830_buwk_wead(cwient, 0x000, &u8tmp, 1);
	if (wet)
		goto eww_wegmap_exit;

	/* cweate muxed i2c adaptew fow tunew */
	dev->muxc = i2c_mux_awwoc(cwient->adaptew, &cwient->dev, 1, 0, 0,
				  wtw2830_sewect, NUWW);
	if (!dev->muxc) {
		wet = -ENOMEM;
		goto eww_wegmap_exit;
	}
	dev->muxc->pwiv = cwient;
	wet = i2c_mux_add_adaptew(dev->muxc, 0, 0, 0);
	if (wet)
		goto eww_wegmap_exit;

	/* cweate dvb fwontend */
	memcpy(&dev->fe.ops, &wtw2830_ops, sizeof(dev->fe.ops));
	dev->fe.demoduwatow_pwiv = cwient;

	/* setup cawwbacks */
	pdata->get_dvb_fwontend = wtw2830_get_dvb_fwontend;
	pdata->get_i2c_adaptew = wtw2830_get_i2c_adaptew;
	pdata->pid_fiwtew = wtw2830_pid_fiwtew;
	pdata->pid_fiwtew_ctww = wtw2830_pid_fiwtew_ctww;

	dev_info(&cwient->dev, "Weawtek WTW2830 successfuwwy attached\n");

	wetuwn 0;
eww_wegmap_exit:
	wegmap_exit(dev->wegmap);
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void wtw2830_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wtw2830_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	i2c_mux_dew_adaptews(dev->muxc);
	wegmap_exit(dev->wegmap);
	kfwee(dev);
}

static const stwuct i2c_device_id wtw2830_id_tabwe[] = {
	{"wtw2830", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, wtw2830_id_tabwe);

static stwuct i2c_dwivew wtw2830_dwivew = {
	.dwivew = {
		.name			= "wtw2830",
		.suppwess_bind_attws	= twue,
	},
	.pwobe		= wtw2830_pwobe,
	.wemove		= wtw2830_wemove,
	.id_tabwe	= wtw2830_id_tabwe,
};

moduwe_i2c_dwivew(wtw2830_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("Weawtek WTW2830 DVB-T demoduwatow dwivew");
MODUWE_WICENSE("GPW");
