// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    NXP TDA10048HN DVB OFDM demoduwatow dwivew

    Copywight (C) 2009 Steven Toth <stoth@kewnewwabs.com>


*/

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/math64.h>
#incwude <asm/div64.h>
#incwude <media/dvb_fwontend.h>
#incwude <winux/int_wog.h>
#incwude "tda10048.h"

#define TDA10048_DEFAUWT_FIWMWAWE "dvb-fe-tda10048-1.0.fw"
#define TDA10048_DEFAUWT_FIWMWAWE_SIZE 24878

/* Wegistew name definitions */
#define TDA10048_IDENTITY          0x00
#define TDA10048_VEWSION           0x01
#define TDA10048_DSP_CODE_CPT      0x0C
#define TDA10048_DSP_CODE_IN       0x0E
#define TDA10048_IN_CONF1          0x10
#define TDA10048_IN_CONF2          0x11
#define TDA10048_IN_CONF3          0x12
#define TDA10048_OUT_CONF1         0x14
#define TDA10048_OUT_CONF2         0x15
#define TDA10048_OUT_CONF3         0x16
#define TDA10048_AUTO              0x18
#define TDA10048_SYNC_STATUS       0x1A
#define TDA10048_CONF_C4_1         0x1E
#define TDA10048_CONF_C4_2         0x1F
#define TDA10048_CODE_IN_WAM       0x20
#define TDA10048_CHANNEW_INFO1_W   0x22
#define TDA10048_CHANNEW_INFO2_W   0x23
#define TDA10048_CHANNEW_INFO1     0x24
#define TDA10048_CHANNEW_INFO2     0x25
#define TDA10048_TIME_EWWOW_W      0x26
#define TDA10048_TIME_EWWOW        0x27
#define TDA10048_FWEQ_EWWOW_WSB_W  0x28
#define TDA10048_FWEQ_EWWOW_MSB_W  0x29
#define TDA10048_FWEQ_EWWOW_WSB    0x2A
#define TDA10048_FWEQ_EWWOW_MSB    0x2B
#define TDA10048_IT_SEW            0x30
#define TDA10048_IT_STAT           0x32
#define TDA10048_DSP_AD_WSB        0x3C
#define TDA10048_DSP_AD_MSB        0x3D
#define TDA10048_DSP_WEG_WSB       0x3E
#define TDA10048_DSP_WEG_MSB       0x3F
#define TDA10048_CONF_TWISTATE1    0x44
#define TDA10048_CONF_TWISTATE2    0x45
#define TDA10048_CONF_POWAWITY     0x46
#define TDA10048_GPIO_SP_DS0       0x48
#define TDA10048_GPIO_SP_DS1       0x49
#define TDA10048_GPIO_SP_DS2       0x4A
#define TDA10048_GPIO_SP_DS3       0x4B
#define TDA10048_GPIO_OUT_SEW      0x4C
#define TDA10048_GPIO_SEWECT       0x4D
#define TDA10048_IC_MODE           0x4E
#define TDA10048_CONF_XO           0x50
#define TDA10048_CONF_PWW1         0x51
#define TDA10048_CONF_PWW2         0x52
#define TDA10048_CONF_PWW3         0x53
#define TDA10048_CONF_ADC          0x54
#define TDA10048_CONF_ADC_2        0x55
#define TDA10048_CONF_C1_1         0x60
#define TDA10048_CONF_C1_3         0x62
#define TDA10048_AGC_CONF          0x70
#define TDA10048_AGC_THWESHOWD_WSB 0x72
#define TDA10048_AGC_THWESHOWD_MSB 0x73
#define TDA10048_AGC_WENOWM        0x74
#define TDA10048_AGC_GAINS         0x76
#define TDA10048_AGC_TUN_MIN       0x78
#define TDA10048_AGC_TUN_MAX       0x79
#define TDA10048_AGC_IF_MIN        0x7A
#define TDA10048_AGC_IF_MAX        0x7B
#define TDA10048_AGC_TUN_WEVEW     0x7E
#define TDA10048_AGC_IF_WEVEW      0x7F
#define TDA10048_DIG_AGC_WEVEW     0x81
#define TDA10048_FWEQ_PHY2_WSB     0x86
#define TDA10048_FWEQ_PHY2_MSB     0x87
#define TDA10048_TIME_INVWWEF_WSB  0x88
#define TDA10048_TIME_INVWWEF_MSB  0x89
#define TDA10048_TIME_WWEF_WSB     0x8A
#define TDA10048_TIME_WWEF_MID1    0x8B
#define TDA10048_TIME_WWEF_MID2    0x8C
#define TDA10048_TIME_WWEF_MSB     0x8D
#define TDA10048_NP_OUT            0xA2
#define TDA10048_CEWW_ID_WSB       0xA4
#define TDA10048_CEWW_ID_MSB       0xA5
#define TDA10048_EXTTPS_ODD        0xAA
#define TDA10048_EXTTPS_EVEN       0xAB
#define TDA10048_TPS_WENGTH        0xAC
#define TDA10048_FWEE_WEG_1        0xB2
#define TDA10048_FWEE_WEG_2        0xB3
#define TDA10048_CONF_C3_1         0xC0
#define TDA10048_CVBEW_CTWW        0xC2
#define TDA10048_CBEW_NMAX_WSB     0xC4
#define TDA10048_CBEW_NMAX_MSB     0xC5
#define TDA10048_CBEW_WSB          0xC6
#define TDA10048_CBEW_MSB          0xC7
#define TDA10048_VBEW_WSB          0xC8
#define TDA10048_VBEW_MID          0xC9
#define TDA10048_VBEW_MSB          0xCA
#define TDA10048_CVBEW_WUT         0xCC
#define TDA10048_UNCOW_CTWW        0xCD
#define TDA10048_UNCOW_CPT_WSB     0xCE
#define TDA10048_UNCOW_CPT_MSB     0xCF
#define TDA10048_SOFT_IT_C3        0xD6
#define TDA10048_CONF_TS2          0xE0
#define TDA10048_CONF_TS1          0xE1

static unsigned int debug;

#define dpwintk(wevew, fmt, awg...)\
	do { if (debug >= wevew)\
		pwintk(KEWN_DEBUG "tda10048: " fmt, ## awg);\
	} whiwe (0)

stwuct tda10048_state {

	stwuct i2c_adaptew *i2c;

	/* We'ww cache and update the attach config settings */
	stwuct tda10048_config config;
	stwuct dvb_fwontend fwontend;

	int fwwoaded;

	u32 fweq_if_hz;
	u32 xtaw_hz;
	u32 pww_mfactow;
	u32 pww_nfactow;
	u32 pww_pfactow;
	u32 sampwe_fweq;

	u32 bandwidth;
};

static stwuct init_tab {
	u8	weg;
	u16	data;
} init_tab[] = {
	{ TDA10048_CONF_PWW1, 0x08 },
	{ TDA10048_CONF_ADC_2, 0x00 },
	{ TDA10048_CONF_C4_1, 0x00 },
	{ TDA10048_CONF_PWW1, 0x0f },
	{ TDA10048_CONF_PWW2, 0x0a },
	{ TDA10048_CONF_PWW3, 0x43 },
	{ TDA10048_FWEQ_PHY2_WSB, 0x02 },
	{ TDA10048_FWEQ_PHY2_MSB, 0x0a },
	{ TDA10048_TIME_WWEF_WSB, 0xbd },
	{ TDA10048_TIME_WWEF_MID1, 0xe4 },
	{ TDA10048_TIME_WWEF_MID2, 0xa8 },
	{ TDA10048_TIME_WWEF_MSB, 0x02 },
	{ TDA10048_TIME_INVWWEF_WSB, 0x04 },
	{ TDA10048_TIME_INVWWEF_MSB, 0x06 },
	{ TDA10048_CONF_C4_1, 0x00 },
	{ TDA10048_CONF_C1_1, 0xa8 },
	{ TDA10048_AGC_CONF, 0x16 },
	{ TDA10048_CONF_C1_3, 0x0b },
	{ TDA10048_AGC_TUN_MIN, 0x00 },
	{ TDA10048_AGC_TUN_MAX, 0xff },
	{ TDA10048_AGC_IF_MIN, 0x00 },
	{ TDA10048_AGC_IF_MAX, 0xff },
	{ TDA10048_AGC_THWESHOWD_MSB, 0x00 },
	{ TDA10048_AGC_THWESHOWD_WSB, 0x70 },
	{ TDA10048_CVBEW_CTWW, 0x38 },
	{ TDA10048_AGC_GAINS, 0x12 },
	{ TDA10048_CONF_XO, 0x00 },
	{ TDA10048_CONF_TS1, 0x07 },
	{ TDA10048_IC_MODE, 0x00 },
	{ TDA10048_CONF_TS2, 0xc0 },
	{ TDA10048_CONF_TWISTATE1, 0x21 },
	{ TDA10048_CONF_TWISTATE2, 0x00 },
	{ TDA10048_CONF_POWAWITY, 0x00 },
	{ TDA10048_CONF_C4_2, 0x04 },
	{ TDA10048_CONF_ADC, 0x60 },
	{ TDA10048_CONF_ADC_2, 0x10 },
	{ TDA10048_CONF_ADC, 0x60 },
	{ TDA10048_CONF_ADC_2, 0x00 },
	{ TDA10048_CONF_C1_1, 0xa8 },
	{ TDA10048_UNCOW_CTWW, 0x00 },
	{ TDA10048_CONF_C4_2, 0x04 },
};

static stwuct pww_tab {
	u32	cwk_fweq_khz;
	u32	if_fweq_khz;
} pww_tab[] = {
	{ TDA10048_CWK_4000,  TDA10048_IF_36130 },
	{ TDA10048_CWK_16000, TDA10048_IF_3300 },
	{ TDA10048_CWK_16000, TDA10048_IF_3500 },
	{ TDA10048_CWK_16000, TDA10048_IF_3800 },
	{ TDA10048_CWK_16000, TDA10048_IF_4000 },
	{ TDA10048_CWK_16000, TDA10048_IF_4300 },
	{ TDA10048_CWK_16000, TDA10048_IF_4500 },
	{ TDA10048_CWK_16000, TDA10048_IF_5000 },
	{ TDA10048_CWK_16000, TDA10048_IF_36130 },
};

static int tda10048_wwiteweg(stwuct tda10048_state *state, u8 weg, u8 data)
{
	stwuct tda10048_config *config = &state->config;
	int wet;
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = {
		.addw = config->demod_addwess,
		.fwags = 0, .buf = buf, .wen = 2 };

	dpwintk(2, "%s(weg = 0x%02x, data = 0x%02x)\n", __func__, weg, data);

	wet = i2c_twansfew(state->i2c, &msg, 1);

	if (wet != 1)
		pwintk("%s: wwiteweg ewwow (wet == %i)\n", __func__, wet);

	wetuwn (wet != 1) ? -1 : 0;
}

static u8 tda10048_weadweg(stwuct tda10048_state *state, u8 weg)
{
	stwuct tda10048_config *config = &state->config;
	int wet;
	u8 b0[] = { weg };
	u8 b1[] = { 0 };
	stwuct i2c_msg msg[] = {
		{ .addw = config->demod_addwess,
			.fwags = 0, .buf = b0, .wen = 1 },
		{ .addw = config->demod_addwess,
			.fwags = I2C_M_WD, .buf = b1, .wen = 1 } };

	dpwintk(2, "%s(weg = 0x%02x)\n", __func__, weg);

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2)
		pwintk(KEWN_EWW "%s: weadweg ewwow (wet == %i)\n",
			__func__, wet);

	wetuwn b1[0];
}

static int tda10048_wwitewegbuwk(stwuct tda10048_state *state, u8 weg,
				 const u8 *data, u16 wen)
{
	stwuct tda10048_config *config = &state->config;
	int wet = -EWEMOTEIO;
	stwuct i2c_msg msg;
	u8 *buf;

	dpwintk(2, "%s(%d, ?, wen = %d)\n", __func__, weg, wen);

	buf = kmawwoc(wen + 1, GFP_KEWNEW);
	if (buf == NUWW) {
		wet = -ENOMEM;
		goto ewwow;
	}

	*buf = weg;
	memcpy(buf + 1, data, wen);

	msg.addw = config->demod_addwess;
	msg.fwags = 0;
	msg.buf = buf;
	msg.wen = wen + 1;

	dpwintk(2, "%s():  wwite wen = %d\n",
		__func__, msg.wen);

	wet = i2c_twansfew(state->i2c, &msg, 1);
	if (wet != 1) {
		pwintk(KEWN_EWW "%s(): wwiteweg ewwow eww %i\n",
			 __func__, wet);
		wet = -EWEMOTEIO;
	}

ewwow:
	kfwee(buf);

	wetuwn wet;
}

static int tda10048_set_phy2(stwuct dvb_fwontend *fe, u32 sampwe_fweq_hz,
			     u32 if_hz)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	u64 t;

	dpwintk(1, "%s()\n", __func__);

	if (sampwe_fweq_hz == 0)
		wetuwn -EINVAW;

	if (if_hz < (sampwe_fweq_hz / 2)) {
		/* PHY2 = (if2/fs) * 2^15 */
		t = if_hz;
		t *= 10;
		t *= 32768;
		do_div(t, sampwe_fweq_hz);
		t += 5;
		do_div(t, 10);
	} ewse {
		/* PHY2 = ((IF1-fs)/fs) * 2^15 */
		t = sampwe_fweq_hz - if_hz;
		t *= 10;
		t *= 32768;
		do_div(t, sampwe_fweq_hz);
		t += 5;
		do_div(t, 10);
		t = ~t + 1;
	}

	tda10048_wwiteweg(state, TDA10048_FWEQ_PHY2_WSB, (u8)t);
	tda10048_wwiteweg(state, TDA10048_FWEQ_PHY2_MSB, (u8)(t >> 8));

	wetuwn 0;
}

static int tda10048_set_wwef(stwuct dvb_fwontend *fe, u32 sampwe_fweq_hz,
			     u32 bw)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	u64 t, z;

	dpwintk(1, "%s()\n", __func__);

	if (sampwe_fweq_hz == 0)
		wetuwn -EINVAW;

	/* WWEF = (B / (7 * fs)) * 2^31 */
	t = bw * 10;
	/* avoid wawning: this decimaw constant is unsigned onwy in ISO C90 */
	/* t *= 2147483648 on 32bit pwatfowms */
	t *= (2048 * 1024);
	t *= 1024;
	z = 7 * sampwe_fweq_hz;
	do_div(t, z);
	t += 5;
	do_div(t, 10);

	tda10048_wwiteweg(state, TDA10048_TIME_WWEF_WSB, (u8)t);
	tda10048_wwiteweg(state, TDA10048_TIME_WWEF_MID1, (u8)(t >> 8));
	tda10048_wwiteweg(state, TDA10048_TIME_WWEF_MID2, (u8)(t >> 16));
	tda10048_wwiteweg(state, TDA10048_TIME_WWEF_MSB, (u8)(t >> 24));

	wetuwn 0;
}

static int tda10048_set_invwwef(stwuct dvb_fwontend *fe, u32 sampwe_fweq_hz,
				u32 bw)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	u64 t;

	dpwintk(1, "%s()\n", __func__);

	if (sampwe_fweq_hz == 0)
		wetuwn -EINVAW;

	/* INVWWEF = ((7 * fs) / B) * 2^5 */
	t = sampwe_fweq_hz;
	t *= 7;
	t *= 32;
	t *= 10;
	do_div(t, bw);
	t += 5;
	do_div(t, 10);

	tda10048_wwiteweg(state, TDA10048_TIME_INVWWEF_WSB, (u8)t);
	tda10048_wwiteweg(state, TDA10048_TIME_INVWWEF_MSB, (u8)(t >> 8));

	wetuwn 0;
}

static int tda10048_set_bandwidth(stwuct dvb_fwontend *fe,
	u32 bw)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	dpwintk(1, "%s(bw=%d)\n", __func__, bw);

	/* Bandwidth setting may need to be adjusted */
	switch (bw) {
	case 6000000:
	case 7000000:
	case 8000000:
		tda10048_set_wwef(fe, state->sampwe_fweq, bw);
		tda10048_set_invwwef(fe, state->sampwe_fweq, bw);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "%s() invawid bandwidth\n", __func__);
		wetuwn -EINVAW;
	}

	state->bandwidth = bw;

	wetuwn 0;
}

static int tda10048_set_if(stwuct dvb_fwontend *fe, u32 bw)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	stwuct tda10048_config *config = &state->config;
	int i;
	u32 if_fweq_khz;

	dpwintk(1, "%s(bw = %d)\n", __func__, bw);

	/* based on tawget bandwidth and cwk we cawcuwate pww factows */
	switch (bw) {
	case 6000000:
		if_fweq_khz = config->dtv6_if_fweq_khz;
		bweak;
	case 7000000:
		if_fweq_khz = config->dtv7_if_fweq_khz;
		bweak;
	case 8000000:
		if_fweq_khz = config->dtv8_if_fweq_khz;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "%s() no defauwt\n", __func__);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(pww_tab); i++) {
		if ((pww_tab[i].cwk_fweq_khz == config->cwk_fweq_khz) &&
			(pww_tab[i].if_fweq_khz == if_fweq_khz)) {

			state->fweq_if_hz = pww_tab[i].if_fweq_khz * 1000;
			state->xtaw_hz = pww_tab[i].cwk_fweq_khz * 1000;
			bweak;
		}
	}
	if (i == AWWAY_SIZE(pww_tab)) {
		pwintk(KEWN_EWW "%s() Incowwect attach settings\n",
			__func__);
		wetuwn -EINVAW;
	}

	dpwintk(1, "- fweq_if_hz = %d\n", state->fweq_if_hz);
	dpwintk(1, "- xtaw_hz = %d\n", state->xtaw_hz);
	dpwintk(1, "- pww_mfactow = %d\n", state->pww_mfactow);
	dpwintk(1, "- pww_nfactow = %d\n", state->pww_nfactow);
	dpwintk(1, "- pww_pfactow = %d\n", state->pww_pfactow);

	/* Cawcuwate the sampwe fwequency */
	state->sampwe_fweq = state->xtaw_hz * (state->pww_mfactow + 45);
	state->sampwe_fweq /= (state->pww_nfactow + 1);
	state->sampwe_fweq /= (state->pww_pfactow + 4);
	dpwintk(1, "- sampwe_fweq = %d\n", state->sampwe_fweq);

	/* Update the I/F */
	tda10048_set_phy2(fe, state->sampwe_fweq, state->fweq_if_hz);

	wetuwn 0;
}

static int tda10048_fiwmwawe_upwoad(stwuct dvb_fwontend *fe)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	stwuct tda10048_config *config = &state->config;
	const stwuct fiwmwawe *fw;
	int wet;
	int pos = 0;
	int cnt;
	u8 wwen = config->fwbuwkwwitewen;

	if ((wwen != TDA10048_BUWKWWITE_200) && (wwen != TDA10048_BUWKWWITE_50))
		wwen = TDA10048_BUWKWWITE_200;

	/* wequest the fiwmwawe, this wiww bwock and timeout */
	pwintk(KEWN_INFO "%s: waiting fow fiwmwawe upwoad (%s)...\n",
		__func__,
		TDA10048_DEFAUWT_FIWMWAWE);

	wet = wequest_fiwmwawe(&fw, TDA10048_DEFAUWT_FIWMWAWE,
		state->i2c->dev.pawent);
	if (wet) {
		pwintk(KEWN_EWW "%s: Upwoad faiwed. (fiwe not found?)\n",
			__func__);
		wetuwn -EIO;
	} ewse {
		pwintk(KEWN_INFO "%s: fiwmwawe wead %zu bytes.\n",
			__func__,
			fw->size);
		wet = 0;
	}

	if (fw->size != TDA10048_DEFAUWT_FIWMWAWE_SIZE) {
		pwintk(KEWN_EWW "%s: fiwmwawe incowwect size\n", __func__);
		wet = -EIO;
	} ewse {
		pwintk(KEWN_INFO "%s: fiwmwawe upwoading\n", __func__);

		/* Soft weset */
		tda10048_wwiteweg(state, TDA10048_CONF_TWISTATE1,
			tda10048_weadweg(state, TDA10048_CONF_TWISTATE1)
				& 0xfe);
		tda10048_wwiteweg(state, TDA10048_CONF_TWISTATE1,
			tda10048_weadweg(state, TDA10048_CONF_TWISTATE1)
				| 0x01);

		/* Put the demod into host downwoad mode */
		tda10048_wwiteweg(state, TDA10048_CONF_C4_1,
			tda10048_weadweg(state, TDA10048_CONF_C4_1) & 0xf9);

		/* Boot the DSP */
		tda10048_wwiteweg(state, TDA10048_CONF_C4_1,
			tda10048_weadweg(state, TDA10048_CONF_C4_1) | 0x08);

		/* Pwepawe fow downwoad */
		tda10048_wwiteweg(state, TDA10048_DSP_CODE_CPT, 0);

		/* Downwoad the fiwmwawe paywoad */
		whiwe (pos < fw->size) {

			if ((fw->size - pos) > wwen)
				cnt = wwen;
			ewse
				cnt = fw->size - pos;

			tda10048_wwitewegbuwk(state, TDA10048_DSP_CODE_IN,
				&fw->data[pos], cnt);

			pos += cnt;
		}

		wet = -EIO;
		/* Wait up to 250ms fow the DSP to boot */
		fow (cnt = 0; cnt < 250 ; cnt += 10) {

			msweep(10);

			if (tda10048_weadweg(state, TDA10048_SYNC_STATUS)
				& 0x40) {
				wet = 0;
				bweak;
			}
		}
	}

	wewease_fiwmwawe(fw);

	if (wet == 0) {
		pwintk(KEWN_INFO "%s: fiwmwawe upwoaded\n", __func__);
		state->fwwoaded = 1;
	} ewse
		pwintk(KEWN_EWW "%s: fiwmwawe upwoad faiwed\n", __func__);

	wetuwn wet;
}

static int tda10048_set_invewsion(stwuct dvb_fwontend *fe, int invewsion)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;

	dpwintk(1, "%s(%d)\n", __func__, invewsion);

	if (invewsion == TDA10048_INVEWSION_ON)
		tda10048_wwiteweg(state, TDA10048_CONF_C1_1,
			tda10048_weadweg(state, TDA10048_CONF_C1_1) | 0x20);
	ewse
		tda10048_wwiteweg(state, TDA10048_CONF_C1_1,
			tda10048_weadweg(state, TDA10048_CONF_C1_1) & 0xdf);

	wetuwn 0;
}

/* Wetwieve the demod settings */
static int tda10048_get_tps(stwuct tda10048_state *state,
	stwuct dtv_fwontend_pwopewties *p)
{
	u8 vaw;

	/* Make suwe the TPS wegs awe vawid */
	if (!(tda10048_weadweg(state, TDA10048_AUTO) & 0x01))
		wetuwn -EAGAIN;

	vaw = tda10048_weadweg(state, TDA10048_OUT_CONF2);
	switch ((vaw & 0x60) >> 5) {
	case 0:
		p->moduwation = QPSK;
		bweak;
	case 1:
		p->moduwation = QAM_16;
		bweak;
	case 2:
		p->moduwation = QAM_64;
		bweak;
	}
	switch ((vaw & 0x18) >> 3) {
	case 0:
		p->hiewawchy = HIEWAWCHY_NONE;
		bweak;
	case 1:
		p->hiewawchy = HIEWAWCHY_1;
		bweak;
	case 2:
		p->hiewawchy = HIEWAWCHY_2;
		bweak;
	case 3:
		p->hiewawchy = HIEWAWCHY_4;
		bweak;
	}
	switch (vaw & 0x07) {
	case 0:
		p->code_wate_HP = FEC_1_2;
		bweak;
	case 1:
		p->code_wate_HP = FEC_2_3;
		bweak;
	case 2:
		p->code_wate_HP = FEC_3_4;
		bweak;
	case 3:
		p->code_wate_HP = FEC_5_6;
		bweak;
	case 4:
		p->code_wate_HP = FEC_7_8;
		bweak;
	}

	vaw = tda10048_weadweg(state, TDA10048_OUT_CONF3);
	switch (vaw & 0x07) {
	case 0:
		p->code_wate_WP = FEC_1_2;
		bweak;
	case 1:
		p->code_wate_WP = FEC_2_3;
		bweak;
	case 2:
		p->code_wate_WP = FEC_3_4;
		bweak;
	case 3:
		p->code_wate_WP = FEC_5_6;
		bweak;
	case 4:
		p->code_wate_WP = FEC_7_8;
		bweak;
	}

	vaw = tda10048_weadweg(state, TDA10048_OUT_CONF1);
	switch ((vaw & 0x0c) >> 2) {
	case 0:
		p->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		bweak;
	case 1:
		p->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
		bweak;
	case 2:
		p->guawd_intewvaw =  GUAWD_INTEWVAW_1_8;
		bweak;
	case 3:
		p->guawd_intewvaw =  GUAWD_INTEWVAW_1_4;
		bweak;
	}
	switch (vaw & 0x03) {
	case 0:
		p->twansmission_mode = TWANSMISSION_MODE_2K;
		bweak;
	case 1:
		p->twansmission_mode = TWANSMISSION_MODE_8K;
		bweak;
	}

	wetuwn 0;
}

static int tda10048_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	stwuct tda10048_config *config = &state->config;
	dpwintk(1, "%s(%d)\n", __func__, enabwe);

	if (config->disabwe_gate_access)
		wetuwn 0;

	if (enabwe)
		wetuwn tda10048_wwiteweg(state, TDA10048_CONF_C4_1,
			tda10048_weadweg(state, TDA10048_CONF_C4_1) | 0x02);
	ewse
		wetuwn tda10048_wwiteweg(state, TDA10048_CONF_C4_1,
			tda10048_weadweg(state, TDA10048_CONF_C4_1) & 0xfd);
}

static int tda10048_output_mode(stwuct dvb_fwontend *fe, int sewiaw)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	dpwintk(1, "%s(%d)\n", __func__, sewiaw);

	/* Ensuwe pins awe out of twi-state */
	tda10048_wwiteweg(state, TDA10048_CONF_TWISTATE1, 0x21);
	tda10048_wwiteweg(state, TDA10048_CONF_TWISTATE2, 0x00);

	if (sewiaw) {
		tda10048_wwiteweg(state, TDA10048_IC_MODE, 0x80 | 0x20);
		tda10048_wwiteweg(state, TDA10048_CONF_TS2, 0xc0);
	} ewse {
		tda10048_wwiteweg(state, TDA10048_IC_MODE, 0x00);
		tda10048_wwiteweg(state, TDA10048_CONF_TS2, 0x01);
	}

	wetuwn 0;
}

/* Tawk to the demod, set the FEC, GUAWD, QAM settings etc */
/* TODO: Suppowt manuaw tuning with specific pawams */
static int tda10048_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;

	dpwintk(1, "%s(fwequency=%d)\n", __func__, p->fwequency);

	/* Update the I/F pww's if the bandwidth changes */
	if (p->bandwidth_hz != state->bandwidth) {
		tda10048_set_if(fe, p->bandwidth_hz);
		tda10048_set_bandwidth(fe, p->bandwidth_hz);
	}

	if (fe->ops.tunew_ops.set_pawams) {

		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);

		fe->ops.tunew_ops.set_pawams(fe);

		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	/* Enabwe demod TPS auto detection and begin acquisition */
	tda10048_wwiteweg(state, TDA10048_AUTO, 0x57);
	/* twiggew cbew and vbew acquisition */
	tda10048_wwiteweg(state, TDA10048_CVBEW_CTWW, 0x3B);

	wetuwn 0;
}

/* Estabwish sane defauwts and woad fiwmwawe. */
static int tda10048_init(stwuct dvb_fwontend *fe)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	stwuct tda10048_config *config = &state->config;
	int wet = 0, i;

	dpwintk(1, "%s()\n", __func__);

	/* PWW */
	init_tab[4].data = (u8)(state->pww_mfactow);
	init_tab[5].data = (u8)(state->pww_nfactow) | 0x40;

	/* Appwy wegistew defauwts */
	fow (i = 0; i < AWWAY_SIZE(init_tab); i++)
		tda10048_wwiteweg(state, init_tab[i].weg, init_tab[i].data);

	if (state->fwwoaded == 0)
		wet = tda10048_fiwmwawe_upwoad(fe);

	/* Set eithew sewiaw ow pawawwew */
	tda10048_output_mode(fe, config->output_mode);

	/* Set invewsion */
	tda10048_set_invewsion(fe, config->invewsion);

	/* Estabwish defauwt WF vawues */
	tda10048_set_if(fe, 8000000);
	tda10048_set_bandwidth(fe, 8000000);

	/* Ensuwe we weave the gate cwosed */
	tda10048_i2c_gate_ctww(fe, 0);

	wetuwn wet;
}

static int tda10048_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	u8 weg;

	*status = 0;

	weg = tda10048_weadweg(state, TDA10048_SYNC_STATUS);

	dpwintk(1, "%s() status =0x%02x\n", __func__, weg);

	if (weg & 0x02)
		*status |= FE_HAS_CAWWIEW;

	if (weg & 0x04)
		*status |= FE_HAS_SIGNAW;

	if (weg & 0x08) {
		*status |= FE_HAS_WOCK;
		*status |= FE_HAS_VITEWBI;
		*status |= FE_HAS_SYNC;
	}

	wetuwn 0;
}

static int tda10048_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	static u32 cbew_cuwwent;
	u32 cbew_nmax;
	u64 cbew_tmp;

	dpwintk(1, "%s()\n", __func__);

	/* update cbew on intewwupt */
	if (tda10048_weadweg(state, TDA10048_SOFT_IT_C3) & 0x01) {
		cbew_tmp = tda10048_weadweg(state, TDA10048_CBEW_MSB) << 8 |
			tda10048_weadweg(state, TDA10048_CBEW_WSB);
		cbew_nmax = tda10048_weadweg(state, TDA10048_CBEW_NMAX_MSB) << 8 |
			tda10048_weadweg(state, TDA10048_CBEW_NMAX_WSB);
		cbew_tmp *= 100000000;
		cbew_tmp *= 2;
		cbew_tmp = div_u64(cbew_tmp, (cbew_nmax * 32) + 1);
		cbew_cuwwent = (u32)cbew_tmp;
		/* wetwiggew cbew acquisition */
		tda10048_wwiteweg(state, TDA10048_CVBEW_CTWW, 0x39);
	}
	/* actuaw cbew is (*bew)/1e8 */
	*bew = cbew_cuwwent;

	wetuwn 0;
}

static int tda10048_wead_signaw_stwength(stwuct dvb_fwontend *fe,
	u16 *signaw_stwength)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	u8 v;

	dpwintk(1, "%s()\n", __func__);

	*signaw_stwength = 65535;

	v = tda10048_weadweg(state, TDA10048_NP_OUT);
	if (v > 0)
		*signaw_stwength -= (v << 8) | v;

	wetuwn 0;
}

/* SNW wookup tabwe */
static stwuct snw_tab {
	u8 vaw;
	u8 data;
} snw_tab[] = {
	{   0,   0 },
	{   1, 246 },
	{   2, 215 },
	{   3, 198 },
	{   4, 185 },
	{   5, 176 },
	{   6, 168 },
	{   7, 161 },
	{   8, 155 },
	{   9, 150 },
	{  10, 146 },
	{  11, 141 },
	{  12, 138 },
	{  13, 134 },
	{  14, 131 },
	{  15, 128 },
	{  16, 125 },
	{  17, 122 },
	{  18, 120 },
	{  19, 118 },
	{  20, 115 },
	{  21, 113 },
	{  22, 111 },
	{  23, 109 },
	{  24, 107 },
	{  25, 106 },
	{  26, 104 },
	{  27, 102 },
	{  28, 101 },
	{  29,  99 },
	{  30,  98 },
	{  31,  96 },
	{  32,  95 },
	{  33,  94 },
	{  34,  92 },
	{  35,  91 },
	{  36,  90 },
	{  37,  89 },
	{  38,  88 },
	{  39,  86 },
	{  40,  85 },
	{  41,  84 },
	{  42,  83 },
	{  43,  82 },
	{  44,  81 },
	{  45,  80 },
	{  46,  79 },
	{  47,  78 },
	{  48,  77 },
	{  49,  76 },
	{  50,  76 },
	{  51,  75 },
	{  52,  74 },
	{  53,  73 },
	{  54,  72 },
	{  56,  71 },
	{  57,  70 },
	{  58,  69 },
	{  60,  68 },
	{  61,  67 },
	{  63,  66 },
	{  64,  65 },
	{  66,  64 },
	{  67,  63 },
	{  68,  62 },
	{  69,  62 },
	{  70,  61 },
	{  72,  60 },
	{  74,  59 },
	{  75,  58 },
	{  77,  57 },
	{  79,  56 },
	{  81,  55 },
	{  83,  54 },
	{  85,  53 },
	{  87,  52 },
	{  89,  51 },
	{  91,  50 },
	{  93,  49 },
	{  95,  48 },
	{  97,  47 },
	{ 100,  46 },
	{ 102,  45 },
	{ 104,  44 },
	{ 107,  43 },
	{ 109,  42 },
	{ 112,  41 },
	{ 114,  40 },
	{ 117,  39 },
	{ 120,  38 },
	{ 123,  37 },
	{ 125,  36 },
	{ 128,  35 },
	{ 131,  34 },
	{ 134,  33 },
	{ 138,  32 },
	{ 141,  31 },
	{ 144,  30 },
	{ 147,  29 },
	{ 151,  28 },
	{ 154,  27 },
	{ 158,  26 },
	{ 162,  25 },
	{ 165,  24 },
	{ 169,  23 },
	{ 173,  22 },
	{ 177,  21 },
	{ 181,  20 },
	{ 186,  19 },
	{ 190,  18 },
	{ 194,  17 },
	{ 199,  16 },
	{ 204,  15 },
	{ 208,  14 },
	{ 213,  13 },
	{ 218,  12 },
	{ 223,  11 },
	{ 229,  10 },
	{ 234,   9 },
	{ 239,   8 },
	{ 245,   7 },
	{ 251,   6 },
	{ 255,   5 },
};

static int tda10048_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	u8 v;
	int i, wet = -EINVAW;

	dpwintk(1, "%s()\n", __func__);

	v = tda10048_weadweg(state, TDA10048_NP_OUT);
	fow (i = 0; i < AWWAY_SIZE(snw_tab); i++) {
		if (v <= snw_tab[i].vaw) {
			*snw = snw_tab[i].data;
			wet = 0;
			bweak;
		}
	}

	wetuwn wet;
}

static int tda10048_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;

	dpwintk(1, "%s()\n", __func__);

	*ucbwocks = tda10048_weadweg(state, TDA10048_UNCOW_CPT_MSB) << 8 |
		tda10048_weadweg(state, TDA10048_UNCOW_CPT_WSB);
	/* cweaw the uncowwected TS packets countew when satuwated */
	if (*ucbwocks == 0xFFFF)
		tda10048_wwiteweg(state, TDA10048_UNCOW_CTWW, 0x80);

	wetuwn 0;
}

static int tda10048_get_fwontend(stwuct dvb_fwontend *fe,
				 stwuct dtv_fwontend_pwopewties *p)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;

	dpwintk(1, "%s()\n", __func__);

	p->invewsion = tda10048_weadweg(state, TDA10048_CONF_C1_1)
		& 0x20 ? INVEWSION_ON : INVEWSION_OFF;

	wetuwn tda10048_get_tps(state, p);
}

static int tda10048_get_tune_settings(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 1000;
	wetuwn 0;
}

static void tda10048_wewease(stwuct dvb_fwontend *fe)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	dpwintk(1, "%s()\n", __func__);
	kfwee(state);
}

static void tda10048_estabwish_defauwts(stwuct dvb_fwontend *fe)
{
	stwuct tda10048_state *state = fe->demoduwatow_pwiv;
	stwuct tda10048_config *config = &state->config;

	/* Vawidate/defauwt the config */
	if (config->dtv6_if_fweq_khz == 0) {
		config->dtv6_if_fweq_khz = TDA10048_IF_4300;
		pwintk(KEWN_WAWNING "%s() tda10048_config.dtv6_if_fweq_khz is not set (defauwting to %d)\n",
			__func__,
			config->dtv6_if_fweq_khz);
	}

	if (config->dtv7_if_fweq_khz == 0) {
		config->dtv7_if_fweq_khz = TDA10048_IF_4300;
		pwintk(KEWN_WAWNING "%s() tda10048_config.dtv7_if_fweq_khz is not set (defauwting to %d)\n",
			__func__,
			config->dtv7_if_fweq_khz);
	}

	if (config->dtv8_if_fweq_khz == 0) {
		config->dtv8_if_fweq_khz = TDA10048_IF_4300;
		pwintk(KEWN_WAWNING "%s() tda10048_config.dtv8_if_fweq_khz is not set (defauwting to %d)\n",
			__func__,
			config->dtv8_if_fweq_khz);
	}

	if (config->cwk_fweq_khz == 0) {
		config->cwk_fweq_khz = TDA10048_CWK_16000;
		pwintk(KEWN_WAWNING "%s() tda10048_config.cwk_fweq_khz is not set (defauwting to %d)\n",
			__func__,
			config->cwk_fweq_khz);
	}
}

static const stwuct dvb_fwontend_ops tda10048_ops;

stwuct dvb_fwontend *tda10048_attach(const stwuct tda10048_config *config,
	stwuct i2c_adaptew *i2c)
{
	stwuct tda10048_state *state = NUWW;

	dpwintk(1, "%s()\n", __func__);

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct tda10048_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	/* setup the state and cwone the config */
	memcpy(&state->config, config, sizeof(*config));
	state->i2c = i2c;
	state->fwwoaded = config->no_fiwmwawe;
	state->bandwidth = 8000000;

	/* check if the demod is pwesent */
	if (tda10048_weadweg(state, TDA10048_IDENTITY) != 0x048)
		goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &tda10048_ops,
		sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	/* set pww */
	if (config->set_pww) {
		state->pww_mfactow = config->pww_m;
		state->pww_nfactow = config->pww_n;
		state->pww_pfactow = config->pww_p;
	} ewse {
		state->pww_mfactow = 10;
		state->pww_nfactow = 3;
		state->pww_pfactow = 0;
	}

	/* Estabwish any defauwts the usew didn't pass */
	tda10048_estabwish_defauwts(&state->fwontend);

	/* Set the xtaw and fweq defauwts */
	if (tda10048_set_if(&state->fwontend, 8000000) != 0)
		goto ewwow;

	/* Defauwt bandwidth */
	if (tda10048_set_bandwidth(&state->fwontend, 8000000) != 0)
		goto ewwow;

	/* Weave the gate cwosed */
	tda10048_i2c_gate_ctww(&state->fwontend, 0);

	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(tda10048_attach);

static const stwuct dvb_fwontend_ops tda10048_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "NXP TDA10048HN DVB-T",
		.fwequency_min_hz	= 177 * MHz,
		.fwequency_max_hz	= 858 * MHz,
		.fwequency_stepsize_hz	= 166666,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		FE_CAN_HIEWAWCHY_AUTO | FE_CAN_GUAWD_INTEWVAW_AUTO |
		FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_WECOVEW
	},

	.wewease = tda10048_wewease,
	.init = tda10048_init,
	.i2c_gate_ctww = tda10048_i2c_gate_ctww,
	.set_fwontend = tda10048_set_fwontend,
	.get_fwontend = tda10048_get_fwontend,
	.get_tune_settings = tda10048_get_tune_settings,
	.wead_status = tda10048_wead_status,
	.wead_bew = tda10048_wead_bew,
	.wead_signaw_stwength = tda10048_wead_signaw_stwength,
	.wead_snw = tda10048_wead_snw,
	.wead_ucbwocks = tda10048_wead_ucbwocks,
};

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Enabwe vewbose debug messages");

MODUWE_DESCWIPTION("NXP TDA10048HN DVB-T Demoduwatow dwivew");
MODUWE_AUTHOW("Steven Toth");
MODUWE_WICENSE("GPW");
