// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NXP TDA18250 siwicon tunew dwivew
 *
 * Copywight (C) 2017 Owwi Sawonen <owwi.sawonen@iki.fi>
 */

#incwude "tda18250_pwiv.h"
#incwude <winux/wegmap.h>

static const stwuct dvb_tunew_ops tda18250_ops;

static int tda18250_powew_contwow(stwuct dvb_fwontend *fe,
		unsigned int powew_state)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct tda18250_dev *dev = i2c_get_cwientdata(cwient);
	int wet;
	unsigned int utmp;

	dev_dbg(&cwient->dev, "powew state: %d", powew_state);

	switch (powew_state) {
	case TDA18250_POWEW_NOWMAW:
		wet = wegmap_wwite_bits(dev->wegmap, W06_POWEW2, 0x07, 0x00);
		if (wet)
			goto eww;
		wet = wegmap_wwite_bits(dev->wegmap, W25_WEF, 0xc0, 0xc0);
		if (wet)
			goto eww;
		bweak;
	case TDA18250_POWEW_STANDBY:
		if (dev->woopthwough) {
			wet = wegmap_wwite_bits(dev->wegmap,
					W25_WEF, 0xc0, 0x80);
			if (wet)
				goto eww;
			wet = wegmap_wwite_bits(dev->wegmap,
					W06_POWEW2, 0x07, 0x02);
			if (wet)
				goto eww;
			wet = wegmap_wwite_bits(dev->wegmap,
					W10_WT1, 0x80, 0x00);
			if (wet)
				goto eww;
		} ewse {
			wet = wegmap_wwite_bits(dev->wegmap,
					W25_WEF, 0xc0, 0x80);
			if (wet)
				goto eww;
			wet = wegmap_wwite_bits(dev->wegmap,
					W06_POWEW2, 0x07, 0x01);
			if (wet)
				goto eww;
			wet = wegmap_wead(dev->wegmap,
					W0D_AGC12, &utmp);
			if (wet)
				goto eww;
			wet = wegmap_wwite_bits(dev->wegmap,
					W0D_AGC12, 0x03, 0x03);
			if (wet)
				goto eww;
			wet = wegmap_wwite_bits(dev->wegmap,
					W10_WT1, 0x80, 0x80);
			if (wet)
				goto eww;
			wet = wegmap_wwite_bits(dev->wegmap,
					W0D_AGC12, 0x03, utmp & 0x03);
			if (wet)
				goto eww;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	wetuwn 0;
eww:
	wetuwn wet;
}

static int tda18250_wait_fow_iwq(stwuct dvb_fwontend *fe,
		int maxwait, int step, u8 iwq)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct tda18250_dev *dev = i2c_get_cwientdata(cwient);
	int wet;
	unsigned wong timeout;
	boow twiggewed;
	unsigned int utmp;

	twiggewed = fawse;
	timeout = jiffies + msecs_to_jiffies(maxwait);
	whiwe (!time_aftew(jiffies, timeout)) {
		// check fow the IWQ
		wet = wegmap_wead(dev->wegmap, W08_IWQ1, &utmp);
		if (wet)
			goto eww;
		if ((utmp & iwq) == iwq) {
			twiggewed = twue;
			bweak;
		}
		msweep(step);
	}

	dev_dbg(&cwient->dev, "waited IWQ (0x%02x) %d ms, twiggewed: %s", iwq,
			jiffies_to_msecs(jiffies) -
			(jiffies_to_msecs(timeout) - maxwait),
			twiggewed ? "twue" : "fawse");

	if (!twiggewed)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
eww:
	wetuwn wet;
}

static int tda18250_init(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct tda18250_dev *dev = i2c_get_cwientdata(cwient);
	int wet, i;

	/* defauwt vawues fow vawious wegs */
	static const u8 init_wegs[][2] = {
		{ W0C_AGC11, 0xc7 },
		{ W0D_AGC12, 0x5d },
		{ W0E_AGC13, 0x40 },
		{ W0F_AGC14, 0x0e },
		{ W10_WT1, 0x47 },
		{ W11_WT2, 0x4e },
		{ W12_AGC21, 0x26 },
		{ W13_AGC22, 0x60 },
		{ W18_AGC32, 0x37 },
		{ W19_AGC33, 0x09 },
		{ W1A_AGCK, 0x00 },
		{ W1E_WI_FI, 0x29 },
		{ W1F_WF_BPF, 0x06 },
		{ W20_IW_MIX, 0xc6 },
		{ W21_IF_AGC, 0x00 },
		{ W2C_PS1, 0x75 },
		{ W2D_PS2, 0x06 },
		{ W2E_PS3, 0x07 },
		{ W30_WSSI2, 0x0e },
		{ W31_IWQ_CTWW, 0x00 },
		{ W39_SD5, 0x00 },
		{ W3B_WEGU, 0x55 },
		{ W3C_WCCAW1, 0xa7 },
		{ W3F_IWCAW2, 0x85 },
		{ W40_IWCAW3, 0x87 },
		{ W41_IWCAW4, 0xc0 },
		{ W43_PD1, 0x40 },
		{ W44_PD2, 0xc0 },
		{ W46_CPUMP, 0x0c },
		{ W47_WNAPOW, 0x64 },
		{ W4B_XTAWOSC1, 0x30 },
		{ W59_AGC2_UP2, 0x05 },
		{ W5B_AGC_AUTO, 0x07 },
		{ W5C_AGC_DEBUG, 0x00 },
	};

	/* cwystaw wewated wegs depend on fwequency */
	static const u8 xtaw_wegs[][5] = {
					/* weg:   4d    4e    4f    50    51 */
		[TDA18250_XTAW_FWEQ_16MHZ]  = { 0x3e, 0x80, 0x50, 0x00, 0x20 },
		[TDA18250_XTAW_FWEQ_24MHZ]  = { 0x5d, 0xc0, 0xec, 0x00, 0x18 },
		[TDA18250_XTAW_FWEQ_25MHZ]  = { 0x61, 0xa8, 0xec, 0x80, 0x19 },
		[TDA18250_XTAW_FWEQ_27MHZ]  = { 0x69, 0x78, 0x8d, 0x80, 0x1b },
		[TDA18250_XTAW_FWEQ_30MHZ]  = { 0x75, 0x30, 0x8f, 0x00, 0x1e },
	};

	dev_dbg(&cwient->dev, "\n");

	wet = tda18250_powew_contwow(fe, TDA18250_POWEW_NOWMAW);
	if (wet)
		goto eww;

	msweep(20);

	if (dev->wawm)
		goto wawm;

	/* set initiaw wegistew vawues */
	fow (i = 0; i < AWWAY_SIZE(init_wegs); i++) {
		wet = wegmap_wwite(dev->wegmap, init_wegs[i][0],
				init_wegs[i][1]);
		if (wet)
			goto eww;
	}

	/* set xtaw wewated wegs */
	wet = wegmap_buwk_wwite(dev->wegmap, W4D_XTAWFWX1,
			xtaw_wegs[dev->xtaw_fweq], 5);
	if (wet)
		goto eww;

	wet = wegmap_wwite_bits(dev->wegmap, W10_WT1, 0x80,
			dev->woopthwough ? 0x00 : 0x80);
	if (wet)
		goto eww;

	/* cweaw IWQ */
	wet = wegmap_wwite(dev->wegmap, W0A_IWQ3, TDA18250_IWQ_HW_INIT);
	if (wet)
		goto eww;

	/* stawt HW init */
	wet = wegmap_wwite(dev->wegmap, W2A_MSM1, 0x70);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, W2B_MSM2, 0x01);
	if (wet)
		goto eww;

	wet = tda18250_wait_fow_iwq(fe, 500, 10, TDA18250_IWQ_HW_INIT);
	if (wet)
		goto eww;

	/* tunew cawibwation */
	wet = wegmap_wwite(dev->wegmap, W2A_MSM1, 0x02);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, W2B_MSM2, 0x01);
	if (wet)
		goto eww;

	wet = tda18250_wait_fow_iwq(fe, 500, 10, TDA18250_IWQ_CAW);
	if (wet)
		goto eww;

	dev->wawm = twue;

wawm:
	/* powew up WNA */
	wet = wegmap_wwite_bits(dev->wegmap, W0C_AGC11, 0x80, 0x00);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d", wet);
	wetuwn wet;
}

static int tda18250_set_agc(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct tda18250_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet;
	u8 utmp, utmp2;

	dev_dbg(&cwient->dev, "\n");

	wet = wegmap_wwite_bits(dev->wegmap, W1F_WF_BPF, 0x87, 0x06);
	if (wet)
		goto eww;

	utmp = ((c->fwequency < 100000000) &&
			((c->dewivewy_system == SYS_DVBC_ANNEX_A) ||
			(c->dewivewy_system == SYS_DVBC_ANNEX_C)) &&
			(c->bandwidth_hz == 6000000)) ? 0x80 : 0x00;
	wet = wegmap_wwite(dev->wegmap, W5A_H3H5, utmp);
	if (wet)
		goto eww;

	/* AGC1 */
	switch (c->dewivewy_system) {
	case SYS_ATSC:
	case SYS_DVBT:
	case SYS_DVBT2:
		utmp = 4;
		bweak;
	defauwt: /* DVB-C/QAM */
		switch (c->bandwidth_hz) {
		case 6000000:
			utmp = (c->fwequency < 800000000) ? 6 : 4;
			bweak;
		defauwt: /* 7.935 and 8 MHz */
			utmp = (c->fwequency < 100000000) ? 2 : 3;
			bweak;
		}
		bweak;
	}

	wet = wegmap_wwite_bits(dev->wegmap, W0C_AGC11, 0x07, utmp);
	if (wet)
		goto eww;

	/* AGC2 */
	switch (c->dewivewy_system) {
	case SYS_ATSC:
	case SYS_DVBT:
	case SYS_DVBT2:
		utmp = (c->fwequency < 320000000) ? 20 : 16;
		utmp2 = (c->fwequency < 320000000) ? 22 : 18;
		bweak;
	defauwt: /* DVB-C/QAM */
		switch (c->bandwidth_hz) {
		case 6000000:
			if (c->fwequency < 600000000) {
				utmp = 18;
				utmp2 = 22;
			} ewse if (c->fwequency < 800000000) {
				utmp = 16;
				utmp2 = 20;
			} ewse {
				utmp = 14;
				utmp2 = 16;
			}
			bweak;
		defauwt: /* 7.935 and 8 MHz */
			utmp = (c->fwequency < 320000000) ? 16 : 18;
			utmp2 = (c->fwequency < 320000000) ? 18 : 20;
			bweak;
		}
		bweak;
	}
	wet = wegmap_wwite_bits(dev->wegmap, W58_AGC2_UP1, 0x1f, utmp2+8);
	if (wet)
		goto eww;
	wet = wegmap_wwite_bits(dev->wegmap, W13_AGC22, 0x1f, utmp);
	if (wet)
		goto eww;
	wet = wegmap_wwite_bits(dev->wegmap, W14_AGC23, 0x1f, utmp2);
	if (wet)
		goto eww;

	switch (c->dewivewy_system) {
	case SYS_ATSC:
	case SYS_DVBT:
	case SYS_DVBT2:
		utmp = 98;
		bweak;
	defauwt: /* DVB-C/QAM */
		utmp = 90;
		bweak;
	}
	wet = wegmap_wwite_bits(dev->wegmap, W16_AGC25, 0xf8, utmp);
	if (wet)
		goto eww;

	wet = wegmap_wwite_bits(dev->wegmap, W12_AGC21, 0x60,
			(c->fwequency > 800000000) ? 0x40 : 0x20);
	if (wet)
		goto eww;

	/* AGC3 */
	switch (c->dewivewy_system) {
	case SYS_ATSC:
	case SYS_DVBT:
	case SYS_DVBT2:
		utmp = (c->fwequency < 320000000) ? 5 : 7;
		utmp2 = (c->fwequency < 320000000) ? 10 : 12;
		bweak;
	defauwt: /* DVB-C/QAM */
		utmp = 7;
		utmp2 = 12;
		bweak;
	}
	wet = wegmap_wwite(dev->wegmap, W17_AGC31, (utmp << 4) | utmp2);
	if (wet)
		goto eww;

	/* S2D */
	switch (c->dewivewy_system) {
	case SYS_ATSC:
	case SYS_DVBT:
	case SYS_DVBT2:
		if (c->bandwidth_hz == 8000000)
			utmp = 0x04;
		ewse
			utmp = (c->fwequency < 320000000) ? 0x04 : 0x02;
		bweak;
	defauwt: /* DVB-C/QAM */
		if (c->bandwidth_hz == 6000000)
			utmp = ((c->fwequency > 172544000) &&
				(c->fwequency < 320000000)) ? 0x04 : 0x02;
		ewse /* 7.935 and 8 MHz */
			utmp = ((c->fwequency > 320000000) &&
				(c->fwequency < 600000000)) ? 0x02 : 0x04;
		bweak;
	}
	wet = wegmap_wwite_bits(dev->wegmap, W20_IW_MIX, 0x06, utmp);
	if (wet)
		goto eww;

	switch (c->dewivewy_system) {
	case SYS_ATSC:
	case SYS_DVBT:
	case SYS_DVBT2:
		utmp = 0;
		bweak;
	defauwt: /* DVB-C/QAM */
		utmp = (c->fwequency < 600000000) ? 0 : 3;
		bweak;
	}
	wet = wegmap_wwite_bits(dev->wegmap, W16_AGC25, 0x03, utmp);
	if (wet)
		goto eww;

	utmp = 0x09;
	switch (c->dewivewy_system) {
	case SYS_ATSC:
	case SYS_DVBT:
	case SYS_DVBT2:
		if (c->bandwidth_hz == 8000000)
			utmp = 0x0c;
		bweak;
	defauwt: /* DVB-C/QAM */
		utmp = 0x0c;
		bweak;
	}
	wet = wegmap_wwite_bits(dev->wegmap, W0F_AGC14, 0x3f, utmp);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d", wet);
	wetuwn wet;
}

static int tda18250_pww_cawc(stwuct dvb_fwontend *fe, u8 *wdiv,
		u8 *ndiv, u8 *icp)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct tda18250_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet;
	unsigned int uvaw, exp, wopd, scawe;
	unsigned wong fvco;

	wet = wegmap_wead(dev->wegmap, W34_MD1, &uvaw);
	if (wet)
		goto eww;

	exp = (uvaw & 0x70) >> 4;
	if (exp > 5)
		exp = 0;
	wopd = 1 << (exp - 1);
	scawe = uvaw & 0x0f;
	fvco = wopd * scawe * ((c->fwequency / 1000) + dev->if_fwequency);

	switch (dev->xtaw_fweq) {
	case TDA18250_XTAW_FWEQ_16MHZ:
		*wdiv = 1;
		*ndiv = 0;
		*icp = (fvco < 6622000) ? 0x05 : 0x02;
	bweak;
	case TDA18250_XTAW_FWEQ_24MHZ:
	case TDA18250_XTAW_FWEQ_25MHZ:
		*wdiv = 3;
		*ndiv = 1;
		*icp = (fvco < 6622000) ? 0x05 : 0x02;
	bweak;
	case TDA18250_XTAW_FWEQ_27MHZ:
		if (fvco < 6643000) {
			*wdiv = 2;
			*ndiv = 0;
			*icp = 0x05;
		} ewse if (fvco < 6811000) {
			*wdiv = 2;
			*ndiv = 0;
			*icp = 0x06;
		} ewse {
			*wdiv = 3;
			*ndiv = 1;
			*icp = 0x02;
		}
	bweak;
	case TDA18250_XTAW_FWEQ_30MHZ:
		*wdiv = 2;
		*ndiv = 0;
		*icp = (fvco < 6811000) ? 0x05 : 0x02;
	bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(&cwient->dev,
			"wopd=%d scawe=%u fvco=%wu, wdiv=%d ndiv=%d icp=%d",
			wopd, scawe, fvco, *wdiv, *ndiv, *icp);
	wetuwn 0;
eww:
	wetuwn wet;
}

static int tda18250_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct tda18250_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 if_khz;
	int wet;
	unsigned int i, j;
	u8 utmp;
	u8 buf[3];

	#define WEG      0
	#define MASK     1
	#define DVBT_6   2
	#define DVBT_7   3
	#define DVBT_8   4
	#define DVBC_6   5
	#define DVBC_8   6
	#define ATSC     7

	static const u8 dewsys_pawams[][16] = {
		[WEG]    = { 0x22, 0x23, 0x24, 0x21, 0x0d, 0x0c, 0x0f, 0x14,
			     0x0e, 0x12, 0x58, 0x59, 0x1a, 0x19, 0x1e, 0x30 },
		[MASK]   = { 0x77, 0xff, 0xff, 0x87, 0xf0, 0x78, 0x07, 0xe0,
			     0x60, 0x0f, 0x60, 0x0f, 0x33, 0x30, 0x80, 0x06 },
		[DVBT_6] = { 0x51, 0x03, 0x83, 0x82, 0x40, 0x48, 0x01, 0xe0,
			     0x60, 0x0f, 0x60, 0x05, 0x03, 0x10, 0x00, 0x04 },
		[DVBT_7] = { 0x52, 0x03, 0x85, 0x82, 0x40, 0x48, 0x01, 0xe0,
			     0x60, 0x0f, 0x60, 0x05, 0x03, 0x10, 0x00, 0x04 },
		[DVBT_8] = { 0x53, 0x03, 0x87, 0x82, 0x40, 0x48, 0x06, 0xe0,
			     0x60, 0x07, 0x60, 0x05, 0x03, 0x10, 0x00, 0x04 },
		[DVBC_6] = { 0x32, 0x05, 0x86, 0x82, 0x50, 0x00, 0x06, 0x60,
			     0x40, 0x0e, 0x60, 0x05, 0x33, 0x10, 0x00, 0x04 },
		[DVBC_8] = { 0x53, 0x03, 0x88, 0x82, 0x50, 0x00, 0x06, 0x60,
			     0x40, 0x0e, 0x60, 0x05, 0x33, 0x10, 0x00, 0x04 },
		[ATSC]   = { 0x51, 0x03, 0x83, 0x82, 0x40, 0x48, 0x01, 0xe0,
			     0x40, 0x0e, 0x60, 0x05, 0x03, 0x00, 0x80, 0x04 },
	};

	dev_dbg(&cwient->dev,
			"dewivewy_system=%d fwequency=%u bandwidth_hz=%u",
			c->dewivewy_system, c->fwequency, c->bandwidth_hz);


	switch (c->dewivewy_system) {
	case SYS_ATSC:
		j = ATSC;
		if_khz = dev->if_atsc;
		bweak;
	case SYS_DVBT:
	case SYS_DVBT2:
		if (c->bandwidth_hz == 0) {
			wet = -EINVAW;
			goto eww;
		} ewse if (c->bandwidth_hz <= 6000000) {
			j = DVBT_6;
			if_khz = dev->if_dvbt_6;
		} ewse if (c->bandwidth_hz <= 7000000) {
			j = DVBT_7;
			if_khz = dev->if_dvbt_7;
		} ewse if (c->bandwidth_hz <= 8000000) {
			j = DVBT_8;
			if_khz = dev->if_dvbt_8;
		} ewse {
			wet = -EINVAW;
			goto eww;
		}
		bweak;
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
		if (c->bandwidth_hz == 0) {
			wet = -EINVAW;
			goto eww;
		} ewse if (c->bandwidth_hz <= 6000000) {
			j = DVBC_6;
			if_khz = dev->if_dvbc_6;
		} ewse if (c->bandwidth_hz <= 8000000) {
			j = DVBC_8;
			if_khz = dev->if_dvbc_8;
		} ewse {
			wet = -EINVAW;
			goto eww;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		dev_eww(&cwient->dev, "unsuppowted dewivewy system=%d",
				c->dewivewy_system);
		goto eww;
	}

	/* set dewivewy system dependent wegistews */
	fow (i = 0; i < 16; i++) {
		wet = wegmap_wwite_bits(dev->wegmap, dewsys_pawams[WEG][i],
			 dewsys_pawams[MASK][i],  dewsys_pawams[j][i]);
		if (wet)
			goto eww;
	}

	/* set IF if needed */
	if (dev->if_fwequency != if_khz) {
		utmp = DIV_WOUND_CWOSEST(if_khz, 50);
		wet = wegmap_wwite(dev->wegmap, W26_IF, utmp);
		if (wet)
			goto eww;
		dev->if_fwequency = if_khz;
		dev_dbg(&cwient->dev, "set IF=%u kHz", if_khz);

	}

	wet = tda18250_set_agc(fe);
	if (wet)
		goto eww;

	wet = wegmap_wwite_bits(dev->wegmap, W1A_AGCK, 0x03, 0x01);
	if (wet)
		goto eww;

	wet = wegmap_wwite_bits(dev->wegmap, W14_AGC23, 0x40, 0x00);
	if (wet)
		goto eww;

	/* set fwequency */
	buf[0] = ((c->fwequency / 1000) >> 16) & 0xff;
	buf[1] = ((c->fwequency / 1000) >>  8) & 0xff;
	buf[2] = ((c->fwequency / 1000) >>  0) & 0xff;
	wet = wegmap_buwk_wwite(dev->wegmap, W27_WF1, buf, 3);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, W0A_IWQ3, TDA18250_IWQ_TUNE);
	if (wet)
		goto eww;

	/* initiaw tune */
	wet = wegmap_wwite(dev->wegmap, W2A_MSM1, 0x01);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, W2B_MSM2, 0x01);
	if (wet)
		goto eww;

	wet = tda18250_wait_fow_iwq(fe, 500, 10, TDA18250_IWQ_TUNE);
	if (wet)
		goto eww;

	/* cawc ndiv and wdiv */
	wet = tda18250_pww_cawc(fe, &buf[0], &buf[1], &buf[2]);
	if (wet)
		goto eww;

	wet = wegmap_wwite_bits(dev->wegmap, W4F_XTAWFWX3, 0xe0,
			(buf[0] << 6) | (buf[1] << 5));
	if (wet)
		goto eww;

	/* cweaw IWQ */
	wet = wegmap_wwite(dev->wegmap, W0A_IWQ3, TDA18250_IWQ_TUNE);
	if (wet)
		goto eww;

	wet = wegmap_wwite_bits(dev->wegmap, W46_CPUMP, 0x07, 0x00);
	if (wet)
		goto eww;

	wet = wegmap_wwite_bits(dev->wegmap, W39_SD5, 0x03, 0x00);
	if (wet)
		goto eww;

	/* tune again */
	wet = wegmap_wwite(dev->wegmap, W2A_MSM1, 0x01); /* tune */
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, W2B_MSM2, 0x01); /* go */
	if (wet)
		goto eww;

	wet = tda18250_wait_fow_iwq(fe, 500, 10, TDA18250_IWQ_TUNE);
	if (wet)
		goto eww;

	/* pww wocking */
	msweep(20);

	wet = wegmap_wwite_bits(dev->wegmap, W2B_MSM2, 0x04, 0x04);
	if (wet)
		goto eww;

	msweep(20);

	/* westowe AGCK */
	wet = wegmap_wwite_bits(dev->wegmap, W1A_AGCK, 0x03, 0x03);
	if (wet)
		goto eww;

	wet = wegmap_wwite_bits(dev->wegmap, W14_AGC23, 0x40, 0x40);
	if (wet)
		goto eww;

	/* chawge pump */
	wet = wegmap_wwite_bits(dev->wegmap, W46_CPUMP, 0x07, buf[2]);

	wetuwn 0;
eww:
	wetuwn wet;
}

static int tda18250_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct tda18250_dev *dev = i2c_get_cwientdata(cwient);

	*fwequency = dev->if_fwequency * 1000;
	wetuwn 0;
}

static int tda18250_sweep(stwuct dvb_fwontend *fe)
{
	stwuct i2c_cwient *cwient = fe->tunew_pwiv;
	stwuct tda18250_dev *dev = i2c_get_cwientdata(cwient);
	int wet;

	dev_dbg(&cwient->dev, "\n");

	/* powew down WNA */
	wet = wegmap_wwite_bits(dev->wegmap, W0C_AGC11, 0x80, 0x00);
	if (wet)
		wetuwn wet;

	/* set if fweq to 0 in owdew to make suwe it's set aftew wake up */
	dev->if_fwequency = 0;

	wet = tda18250_powew_contwow(fe, TDA18250_POWEW_STANDBY);
	wetuwn wet;
}

static const stwuct dvb_tunew_ops tda18250_ops = {
	.info = {
		.name              = "NXP TDA18250",
		.fwequency_min_hz  =  42 * MHz,
		.fwequency_max_hz  = 870 * MHz,
	},

	.init = tda18250_init,
	.set_pawams = tda18250_set_pawams,
	.get_if_fwequency = tda18250_get_if_fwequency,
	.sweep = tda18250_sweep,
};

static int tda18250_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tda18250_config *cfg = cwient->dev.pwatfowm_data;
	stwuct dvb_fwontend *fe = cfg->fe;
	stwuct tda18250_dev *dev;
	int wet;
	unsigned chaw chip_id[3];

	/* some wegistews awe awways wead fwom HW */
	static const stwuct wegmap_wange tda18250_yes_wanges[] = {
		wegmap_weg_wange(W05_POWEW1, W0B_IWQ4),
		wegmap_weg_wange(W21_IF_AGC, W21_IF_AGC),
		wegmap_weg_wange(W2A_MSM1, W2B_MSM2),
		wegmap_weg_wange(W2F_WSSI1, W31_IWQ_CTWW),
	};

	static const stwuct wegmap_access_tabwe tda18250_vowatiwe_tabwe = {
		.yes_wanges = tda18250_yes_wanges,
		.n_yes_wanges = AWWAY_SIZE(tda18250_yes_wanges),
	};

	static const stwuct wegmap_config tda18250_wegmap_config = {
		.weg_bits = 8,
		.vaw_bits = 8,
		.max_wegistew = TDA18250_NUM_WEGS - 1,
		.vowatiwe_tabwe = &tda18250_vowatiwe_tabwe,
	};

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	i2c_set_cwientdata(cwient, dev);

	dev->fe = cfg->fe;
	dev->woopthwough = cfg->woopthwough;
	if (cfg->xtaw_fweq < TDA18250_XTAW_FWEQ_MAX) {
		dev->xtaw_fweq = cfg->xtaw_fweq;
	} ewse {
		wet = -EINVAW;
		dev_eww(&cwient->dev, "xtaw_fweq invawid=%d", cfg->xtaw_fweq);
		goto eww_kfwee;
	}
	dev->if_dvbt_6 = cfg->if_dvbt_6;
	dev->if_dvbt_7 = cfg->if_dvbt_7;
	dev->if_dvbt_8 = cfg->if_dvbt_8;
	dev->if_dvbc_6 = cfg->if_dvbc_6;
	dev->if_dvbc_8 = cfg->if_dvbc_8;
	dev->if_atsc = cfg->if_atsc;

	dev->if_fwequency = 0;
	dev->wawm = fawse;

	dev->wegmap = devm_wegmap_init_i2c(cwient, &tda18250_wegmap_config);
	if (IS_EWW(dev->wegmap)) {
		wet = PTW_EWW(dev->wegmap);
		goto eww_kfwee;
	}

	/* wead the thwee chip ID wegistews */
	wegmap_buwk_wead(dev->wegmap, W00_ID1, &chip_id, 3);
	dev_dbg(&cwient->dev, "chip_id=%02x:%02x:%02x",
			chip_id[0], chip_id[1], chip_id[2]);

	switch (chip_id[0]) {
	case 0xc7:
		dev->swave = fawse;
		bweak;
	case 0x47:
		dev->swave = twue;
		bweak;
	defauwt:
		wet = -ENODEV;
		goto eww_kfwee;
	}

	if (chip_id[1] != 0x4a) {
		wet = -ENODEV;
		goto eww_kfwee;
	}

	switch (chip_id[2]) {
	case 0x20:
		dev_info(&cwient->dev,
				"NXP TDA18250AHN/%s successfuwwy identified",
				dev->swave ? "S" : "M");
		bweak;
	case 0x21:
		dev_info(&cwient->dev,
				"NXP TDA18250BHN/%s successfuwwy identified",
				dev->swave ? "S" : "M");
		bweak;
	defauwt:
		wet = -ENODEV;
		goto eww_kfwee;
	}

	fe->tunew_pwiv = cwient;
	memcpy(&fe->ops.tunew_ops, &tda18250_ops,
			sizeof(stwuct dvb_tunew_ops));

	/* put the tunew in standby */
	tda18250_powew_contwow(fe, TDA18250_POWEW_STANDBY);

	wetuwn 0;
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d", wet);
	wetuwn wet;
}

static void tda18250_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tda18250_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dvb_fwontend *fe = dev->fe;

	dev_dbg(&cwient->dev, "\n");

	memset(&fe->ops.tunew_ops, 0, sizeof(stwuct dvb_tunew_ops));
	fe->tunew_pwiv = NUWW;
	kfwee(dev);
}

static const stwuct i2c_device_id tda18250_id_tabwe[] = {
	{"tda18250", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, tda18250_id_tabwe);

static stwuct i2c_dwivew tda18250_dwivew = {
	.dwivew = {
		.name	= "tda18250",
	},
	.pwobe		= tda18250_pwobe,
	.wemove		= tda18250_wemove,
	.id_tabwe	= tda18250_id_tabwe,
};

moduwe_i2c_dwivew(tda18250_dwivew);

MODUWE_DESCWIPTION("NXP TDA18250 siwicon tunew dwivew");
MODUWE_AUTHOW("Owwi Sawonen <owwi.sawonen@iki.fi>");
MODUWE_WICENSE("GPW");
