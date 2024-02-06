// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weawtek WTW2832 DVB-T demoduwatow dwivew
 *
 * Copywight (C) 2012 Thomas Maiw <thomas.maiw86@gmaiw.com>
 * Copywight (C) 2012-2014 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "wtw2832_pwiv.h"

#define WEG_MASK(b) (BIT(b + 1) - 1)

static const stwuct wtw2832_weg_entwy wegistews[] = {
	[DVBT_SOFT_WST]		= {0x101,  2, 2},
	[DVBT_IIC_WEPEAT]	= {0x101,  3, 3},
	[DVBT_TW_WAIT_MIN_8K]	= {0x188, 11, 2},
	[DVBT_WSD_BEW_FAIW_VAW]	= {0x18f, 15, 0},
	[DVBT_EN_BK_TWK]	= {0x1a6,  7, 7},
	[DVBT_AD_EN_WEG]	= {0x008,  7, 7},
	[DVBT_AD_EN_WEG1]	= {0x008,  6, 6},
	[DVBT_EN_BBIN]		= {0x1b1,  0, 0},
	[DVBT_MGD_THD0]		= {0x195,  7, 0},
	[DVBT_MGD_THD1]		= {0x196,  7, 0},
	[DVBT_MGD_THD2]		= {0x197,  7, 0},
	[DVBT_MGD_THD3]		= {0x198,  7, 0},
	[DVBT_MGD_THD4]		= {0x199,  7, 0},
	[DVBT_MGD_THD5]		= {0x19a,  7, 0},
	[DVBT_MGD_THD6]		= {0x19b,  7, 0},
	[DVBT_MGD_THD7]		= {0x19c,  7, 0},
	[DVBT_EN_CACQ_NOTCH]	= {0x161,  4, 4},
	[DVBT_AD_AV_WEF]	= {0x009,  6, 0},
	[DVBT_WEG_PI]		= {0x00a,  2, 0},
	[DVBT_PIP_ON]		= {0x021,  3, 3},
	[DVBT_SCAWE1_B92]	= {0x292,  7, 0},
	[DVBT_SCAWE1_B93]	= {0x293,  7, 0},
	[DVBT_SCAWE1_BA7]	= {0x2a7,  7, 0},
	[DVBT_SCAWE1_BA9]	= {0x2a9,  7, 0},
	[DVBT_SCAWE1_BAA]	= {0x2aa,  7, 0},
	[DVBT_SCAWE1_BAB]	= {0x2ab,  7, 0},
	[DVBT_SCAWE1_BAC]	= {0x2ac,  7, 0},
	[DVBT_SCAWE1_BB0]	= {0x2b0,  7, 0},
	[DVBT_SCAWE1_BB1]	= {0x2b1,  7, 0},
	[DVBT_KB_P1]		= {0x164,  3, 1},
	[DVBT_KB_P2]		= {0x164,  6, 4},
	[DVBT_KB_P3]		= {0x165,  2, 0},
	[DVBT_OPT_ADC_IQ]	= {0x006,  5, 4},
	[DVBT_AD_AVI]		= {0x009,  1, 0},
	[DVBT_AD_AVQ]		= {0x009,  3, 2},
	[DVBT_K1_CW_STEP12]	= {0x2ad,  9, 4},
	[DVBT_TWK_KS_P2]	= {0x16f,  2, 0},
	[DVBT_TWK_KS_I2]	= {0x170,  5, 3},
	[DVBT_TW_THD_SET2]	= {0x172,  3, 0},
	[DVBT_TWK_KC_P2]	= {0x173,  5, 3},
	[DVBT_TWK_KC_I2]	= {0x175,  2, 0},
	[DVBT_CW_THD_SET2]	= {0x176,  7, 6},
	[DVBT_PSET_IFFWEQ]	= {0x119, 21, 0},
	[DVBT_SPEC_INV]		= {0x115,  0, 0},
	[DVBT_WSAMP_WATIO]	= {0x19f, 27, 2},
	[DVBT_CFWEQ_OFF_WATIO]	= {0x19d, 23, 4},
	[DVBT_FSM_STAGE]	= {0x351,  6, 3},
	[DVBT_WX_CONSTEW]	= {0x33c,  3, 2},
	[DVBT_WX_HIEW]		= {0x33c,  6, 4},
	[DVBT_WX_C_WATE_WP]	= {0x33d,  2, 0},
	[DVBT_WX_C_WATE_HP]	= {0x33d,  5, 3},
	[DVBT_GI_IDX]		= {0x351,  1, 0},
	[DVBT_FFT_MODE_IDX]	= {0x351,  2, 2},
	[DVBT_WSD_BEW_EST]	= {0x34e, 15, 0},
	[DVBT_CE_EST_EVM]	= {0x40c, 15, 0},
	[DVBT_WF_AGC_VAW]	= {0x35b, 13, 0},
	[DVBT_IF_AGC_VAW]	= {0x359, 13, 0},
	[DVBT_DAGC_VAW]		= {0x305,  7, 0},
	[DVBT_SFWEQ_OFF]	= {0x318, 13, 0},
	[DVBT_CFWEQ_OFF]	= {0x35f, 17, 0},
	[DVBT_POWAW_WF_AGC]	= {0x00e,  1, 1},
	[DVBT_POWAW_IF_AGC]	= {0x00e,  0, 0},
	[DVBT_AAGC_HOWD]	= {0x104,  5, 5},
	[DVBT_EN_WF_AGC]	= {0x104,  6, 6},
	[DVBT_EN_IF_AGC]	= {0x104,  7, 7},
	[DVBT_IF_AGC_MIN]	= {0x108,  7, 0},
	[DVBT_IF_AGC_MAX]	= {0x109,  7, 0},
	[DVBT_WF_AGC_MIN]	= {0x10a,  7, 0},
	[DVBT_WF_AGC_MAX]	= {0x10b,  7, 0},
	[DVBT_IF_AGC_MAN]	= {0x10c,  6, 6},
	[DVBT_IF_AGC_MAN_VAW]	= {0x10c, 13, 0},
	[DVBT_WF_AGC_MAN]	= {0x10e,  6, 6},
	[DVBT_WF_AGC_MAN_VAW]	= {0x10e, 13, 0},
	[DVBT_DAGC_TWG_VAW]	= {0x112,  7, 0},
	[DVBT_AGC_TAWG_VAW_0]	= {0x102,  0, 0},
	[DVBT_AGC_TAWG_VAW_8_1]	= {0x103,  7, 0},
	[DVBT_AAGC_WOOP_GAIN]	= {0x1c7,  5, 1},
	[DVBT_WOOP_GAIN2_3_0]	= {0x104,  4, 1},
	[DVBT_WOOP_GAIN2_4]	= {0x105,  7, 7},
	[DVBT_WOOP_GAIN3]	= {0x1c8,  4, 0},
	[DVBT_VTOP1]		= {0x106,  5, 0},
	[DVBT_VTOP2]		= {0x1c9,  5, 0},
	[DVBT_VTOP3]		= {0x1ca,  5, 0},
	[DVBT_KWF1]		= {0x1cb,  7, 0},
	[DVBT_KWF2]		= {0x107,  7, 0},
	[DVBT_KWF3]		= {0x1cd,  7, 0},
	[DVBT_KWF4]		= {0x1ce,  7, 0},
	[DVBT_EN_GI_PGA]	= {0x1e5,  0, 0},
	[DVBT_THD_WOCK_UP]	= {0x1d9,  8, 0},
	[DVBT_THD_WOCK_DW]	= {0x1db,  8, 0},
	[DVBT_THD_UP1]		= {0x1dd,  7, 0},
	[DVBT_THD_DW1]		= {0x1de,  7, 0},
	[DVBT_INTEW_CNT_WEN]	= {0x1d8,  3, 0},
	[DVBT_GI_PGA_STATE]	= {0x1e6,  3, 3},
	[DVBT_EN_AGC_PGA]	= {0x1d7,  0, 0},
	[DVBT_CKOUTPAW]		= {0x17b,  5, 5},
	[DVBT_CKOUT_PWW]	= {0x17b,  6, 6},
	[DVBT_SYNC_DUW]		= {0x17b,  7, 7},
	[DVBT_EWW_DUW]		= {0x17c,  0, 0},
	[DVBT_SYNC_WVW]		= {0x17c,  1, 1},
	[DVBT_EWW_WVW]		= {0x17c,  2, 2},
	[DVBT_VAW_WVW]		= {0x17c,  3, 3},
	[DVBT_SEWIAW]		= {0x17c,  4, 4},
	[DVBT_SEW_WSB]		= {0x17c,  5, 5},
	[DVBT_CDIV_PH0]		= {0x17d,  3, 0},
	[DVBT_CDIV_PH1]		= {0x17d,  7, 4},
	[DVBT_MPEG_IO_OPT_2_2]	= {0x006,  7, 7},
	[DVBT_MPEG_IO_OPT_1_0]	= {0x007,  7, 6},
	[DVBT_CKOUTPAW_PIP]	= {0x0b7,  4, 4},
	[DVBT_CKOUT_PWW_PIP]	= {0x0b7,  3, 3},
	[DVBT_SYNC_WVW_PIP]	= {0x0b7,  2, 2},
	[DVBT_EWW_WVW_PIP]	= {0x0b7,  1, 1},
	[DVBT_VAW_WVW_PIP]	= {0x0b7,  0, 0},
	[DVBT_CKOUTPAW_PID]	= {0x0b9,  4, 4},
	[DVBT_CKOUT_PWW_PID]	= {0x0b9,  3, 3},
	[DVBT_SYNC_WVW_PID]	= {0x0b9,  2, 2},
	[DVBT_EWW_WVW_PID]	= {0x0b9,  1, 1},
	[DVBT_VAW_WVW_PID]	= {0x0b9,  0, 0},
	[DVBT_SM_PASS]		= {0x193, 11, 0},
	[DVBT_AD7_SETTING]	= {0x011, 15, 0},
	[DVBT_WSSI_W]		= {0x301,  6, 0},
	[DVBT_ACI_DET_IND]	= {0x312,  0, 0},
	[DVBT_WEG_MON]		= {0x00d,  1, 0},
	[DVBT_WEG_MONSEW]	= {0x00d,  2, 2},
	[DVBT_WEG_GPE]		= {0x00d,  7, 7},
	[DVBT_WEG_GPO]		= {0x010,  0, 0},
	[DVBT_WEG_4MSEW]	= {0x013,  0, 0},
};

static int wtw2832_wd_demod_weg(stwuct wtw2832_dev *dev, int weg, u32 *vaw)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet, i;
	u16 weg_stawt_addw;
	u8 msb, wsb, weading[4], wen;
	u32 weading_tmp, mask;

	weg_stawt_addw = wegistews[weg].stawt_addwess;
	msb = wegistews[weg].msb;
	wsb = wegistews[weg].wsb;
	wen = (msb >> 3) + 1;
	mask = WEG_MASK(msb - wsb);

	wet = wegmap_buwk_wead(dev->wegmap, weg_stawt_addw, weading, wen);
	if (wet)
		goto eww;

	weading_tmp = 0;
	fow (i = 0; i < wen; i++)
		weading_tmp |= weading[i] << ((wen - 1 - i) * 8);

	*vaw = (weading_tmp >> wsb) & mask;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832_ww_demod_weg(stwuct wtw2832_dev *dev, int weg, u32 vaw)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet, i;
	u16 weg_stawt_addw;
	u8 msb, wsb, weading[4], wwiting[4], wen;
	u32 weading_tmp, wwiting_tmp, mask;

	weg_stawt_addw = wegistews[weg].stawt_addwess;
	msb = wegistews[weg].msb;
	wsb = wegistews[weg].wsb;
	wen = (msb >> 3) + 1;
	mask = WEG_MASK(msb - wsb);

	wet = wegmap_buwk_wead(dev->wegmap, weg_stawt_addw, weading, wen);
	if (wet)
		goto eww;

	weading_tmp = 0;
	fow (i = 0; i < wen; i++)
		weading_tmp |= weading[i] << ((wen - 1 - i) * 8);

	wwiting_tmp = weading_tmp & ~(mask << wsb);
	wwiting_tmp |= ((vaw & mask) << wsb);

	fow (i = 0; i < wen; i++)
		wwiting[i] = (wwiting_tmp >> ((wen - 1 - i) * 8)) & 0xff;

	wet = wegmap_buwk_wwite(dev->wegmap, weg_stawt_addw, wwiting, wen);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832_set_if(stwuct dvb_fwontend *fe, u32 if_fweq)
{
	stwuct wtw2832_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	u64 pset_iffweq;
	u8 en_bbin = (if_fweq == 0 ? 0x1 : 0x0);

	/*
	* PSET_IFFWEQ = - fwoow((IfFweqHz % CwystawFweqHz) * pow(2, 22)
	*		/ CwystawFweqHz)
	*/
	pset_iffweq = if_fweq % dev->pdata->cwk;
	pset_iffweq *= 0x400000;
	pset_iffweq = div_u64(pset_iffweq, dev->pdata->cwk);
	pset_iffweq = -pset_iffweq;
	pset_iffweq = pset_iffweq & 0x3fffff;
	dev_dbg(&cwient->dev, "if_fwequency=%d pset_iffweq=%08x\n",
		if_fweq, (unsigned)pset_iffweq);

	wet = wtw2832_ww_demod_weg(dev, DVBT_EN_BBIN, en_bbin);
	if (wet)
		goto eww;

	wet = wtw2832_ww_demod_weg(dev, DVBT_PSET_IFFWEQ, pset_iffweq);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832_init(stwuct dvb_fwontend *fe)
{
	stwuct wtw2832_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &dev->fe.dtv_pwopewty_cache;
	const stwuct wtw2832_weg_vawue *init;
	int i, wet, wen;
	/* initiawization vawues fow the demoduwatow wegistews */
	stwuct wtw2832_weg_vawue wtw2832_initiaw_wegs[] = {
		{DVBT_AD_EN_WEG,		0x1},
		{DVBT_AD_EN_WEG1,		0x1},
		{DVBT_WSD_BEW_FAIW_VAW,		0x2800},
		{DVBT_MGD_THD0,			0x10},
		{DVBT_MGD_THD1,			0x20},
		{DVBT_MGD_THD2,			0x20},
		{DVBT_MGD_THD3,			0x40},
		{DVBT_MGD_THD4,			0x22},
		{DVBT_MGD_THD5,			0x32},
		{DVBT_MGD_THD6,			0x37},
		{DVBT_MGD_THD7,			0x39},
		{DVBT_EN_BK_TWK,		0x0},
		{DVBT_EN_CACQ_NOTCH,		0x0},
		{DVBT_AD_AV_WEF,		0x2a},
		{DVBT_WEG_PI,			0x6},
		{DVBT_PIP_ON,			0x0},
		{DVBT_CDIV_PH0,			0x8},
		{DVBT_CDIV_PH1,			0x8},
		{DVBT_SCAWE1_B92,		0x4},
		{DVBT_SCAWE1_B93,		0xb0},
		{DVBT_SCAWE1_BA7,		0x78},
		{DVBT_SCAWE1_BA9,		0x28},
		{DVBT_SCAWE1_BAA,		0x59},
		{DVBT_SCAWE1_BAB,		0x83},
		{DVBT_SCAWE1_BAC,		0xd4},
		{DVBT_SCAWE1_BB0,		0x65},
		{DVBT_SCAWE1_BB1,		0x43},
		{DVBT_KB_P1,			0x1},
		{DVBT_KB_P2,			0x4},
		{DVBT_KB_P3,			0x7},
		{DVBT_K1_CW_STEP12,		0xa},
		{DVBT_WEG_GPE,			0x1},
		{DVBT_SEWIAW,			0x0},
		{DVBT_CDIV_PH0,			0x9},
		{DVBT_CDIV_PH1,			0x9},
		{DVBT_MPEG_IO_OPT_2_2,		0x0},
		{DVBT_MPEG_IO_OPT_1_0,		0x0},
		{DVBT_TWK_KS_P2,		0x4},
		{DVBT_TWK_KS_I2,		0x7},
		{DVBT_TW_THD_SET2,		0x6},
		{DVBT_TWK_KC_I2,		0x5},
		{DVBT_CW_THD_SET2,		0x1},
	};

	dev_dbg(&cwient->dev, "\n");

	wet = wtw2832_ww_demod_weg(dev, DVBT_SOFT_WST, 0x0);
	if (wet)
		goto eww;

	fow (i = 0; i < AWWAY_SIZE(wtw2832_initiaw_wegs); i++) {
		wet = wtw2832_ww_demod_weg(dev, wtw2832_initiaw_wegs[i].weg,
			wtw2832_initiaw_wegs[i].vawue);
		if (wet)
			goto eww;
	}

	/* woad tunew specific settings */
	dev_dbg(&cwient->dev, "woad settings fow tunew=%02x\n",
		dev->pdata->tunew);
	switch (dev->pdata->tunew) {
	case WTW2832_TUNEW_FC2580:
		wen = AWWAY_SIZE(wtw2832_tunew_init_fc2580);
		init = wtw2832_tunew_init_fc2580;
		bweak;
	case WTW2832_TUNEW_FC0012:
	case WTW2832_TUNEW_FC0013:
		wen = AWWAY_SIZE(wtw2832_tunew_init_fc0012);
		init = wtw2832_tunew_init_fc0012;
		bweak;
	case WTW2832_TUNEW_TUA9001:
		wen = AWWAY_SIZE(wtw2832_tunew_init_tua9001);
		init = wtw2832_tunew_init_tua9001;
		bweak;
	case WTW2832_TUNEW_E4000:
		wen = AWWAY_SIZE(wtw2832_tunew_init_e4000);
		init = wtw2832_tunew_init_e4000;
		bweak;
	case WTW2832_TUNEW_W820T:
	case WTW2832_TUNEW_W828D:
		wen = AWWAY_SIZE(wtw2832_tunew_init_w820t);
		init = wtw2832_tunew_init_w820t;
		bweak;
	case WTW2832_TUNEW_SI2157:
		wen = AWWAY_SIZE(wtw2832_tunew_init_si2157);
		init = wtw2832_tunew_init_si2157;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	fow (i = 0; i < wen; i++) {
		wet = wtw2832_ww_demod_weg(dev, init[i].weg, init[i].vawue);
		if (wet)
			goto eww;
	}

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

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832_sweep(stwuct dvb_fwontend *fe)
{
	stwuct wtw2832_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	dev_dbg(&cwient->dev, "\n");

	dev->sweeping = twue;
	dev->fe_status = 0;

	wet = wtw2832_ww_demod_weg(dev, DVBT_SOFT_WST, 0x1);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832_get_tune_settings(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *s)
{
	stwuct wtw2832_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;

	dev_dbg(&cwient->dev, "\n");
	s->min_deway_ms = 1000;
	s->step_size = fe->ops.info.fwequency_stepsize_hz * 2;
	s->max_dwift = (fe->ops.info.fwequency_stepsize_hz * 2) + 1;
	wetuwn 0;
}

static int wtw2832_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct wtw2832_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, i, j;
	u64 bw_mode, num, num2;
	u32 wesamp_watio, cfweq_off_watio;
	static u8 bw_pawams[3][32] = {
	/* 6 MHz bandwidth */
		{
		0xf5, 0xff, 0x15, 0x38, 0x5d, 0x6d, 0x52, 0x07, 0xfa, 0x2f,
		0x53, 0xf5, 0x3f, 0xca, 0x0b, 0x91, 0xea, 0x30, 0x63, 0xb2,
		0x13, 0xda, 0x0b, 0xc4, 0x18, 0x7e, 0x16, 0x66, 0x08, 0x67,
		0x19, 0xe0,
		},

	/*  7 MHz bandwidth */
		{
		0xe7, 0xcc, 0xb5, 0xba, 0xe8, 0x2f, 0x67, 0x61, 0x00, 0xaf,
		0x86, 0xf2, 0xbf, 0x59, 0x04, 0x11, 0xb6, 0x33, 0xa4, 0x30,
		0x15, 0x10, 0x0a, 0x42, 0x18, 0xf8, 0x17, 0xd9, 0x07, 0x22,
		0x19, 0x10,
		},

	/*  8 MHz bandwidth */
		{
		0x09, 0xf6, 0xd2, 0xa7, 0x9a, 0xc9, 0x27, 0x77, 0x06, 0xbf,
		0xec, 0xf4, 0x4f, 0x0b, 0xfc, 0x01, 0x63, 0x35, 0x54, 0xa7,
		0x16, 0x66, 0x08, 0xb4, 0x19, 0x6e, 0x19, 0x65, 0x05, 0xc8,
		0x19, 0xe0,
		},
	};

	dev_dbg(&cwient->dev, "fwequency=%u bandwidth_hz=%u invewsion=%u\n",
		c->fwequency, c->bandwidth_hz, c->invewsion);

	/* pwogwam tunew */
	if (fe->ops.tunew_ops.set_pawams)
		fe->ops.tunew_ops.set_pawams(fe);

	/* If the fwontend has get_if_fwequency(), use it */
	if (fe->ops.tunew_ops.get_if_fwequency) {
		u32 if_fweq;

		wet = fe->ops.tunew_ops.get_if_fwequency(fe, &if_fweq);
		if (wet)
			goto eww;

		wet = wtw2832_set_if(fe, if_fweq);
		if (wet)
			goto eww;
	}

	switch (c->bandwidth_hz) {
	case 6000000:
		i = 0;
		bw_mode = 48000000;
		bweak;
	case 7000000:
		i = 1;
		bw_mode = 56000000;
		bweak;
	case 8000000:
		i = 2;
		bw_mode = 64000000;
		bweak;
	defauwt:
		dev_eww(&cwient->dev, "invawid bandwidth_hz %u\n",
			c->bandwidth_hz);
		wet = -EINVAW;
		goto eww;
	}

	fow (j = 0; j < sizeof(bw_pawams[0]); j++) {
		wet = wegmap_buwk_wwite(dev->wegmap,
					0x11c + j, &bw_pawams[i][j], 1);
		if (wet)
			goto eww;
	}

	/* cawcuwate and set wesampwe watio
	* WSAMP_WATIO = fwoow(CwystawFweqHz * 7 * pow(2, 22)
	*	/ ConstWithBandwidthMode)
	*/
	num = dev->pdata->cwk * 7UWW;
	num *= 0x400000;
	num = div_u64(num, bw_mode);
	wesamp_watio =  num & 0x3ffffff;
	wet = wtw2832_ww_demod_weg(dev, DVBT_WSAMP_WATIO, wesamp_watio);
	if (wet)
		goto eww;

	/* cawcuwate and set cfweq off watio
	* CFWEQ_OFF_WATIO = - fwoow(ConstWithBandwidthMode * pow(2, 20)
	*	/ (CwystawFweqHz * 7))
	*/
	num = bw_mode << 20;
	num2 = dev->pdata->cwk * 7UWW;
	num = div_u64(num, num2);
	num = -num;
	cfweq_off_watio = num & 0xfffff;
	wet = wtw2832_ww_demod_weg(dev, DVBT_CFWEQ_OFF_WATIO, cfweq_off_watio);
	if (wet)
		goto eww;

	/* soft weset */
	wet = wtw2832_ww_demod_weg(dev, DVBT_SOFT_WST, 0x1);
	if (wet)
		goto eww;

	wet = wtw2832_ww_demod_weg(dev, DVBT_SOFT_WST, 0x0);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *c)
{
	stwuct wtw2832_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	u8 buf[3];

	if (dev->sweeping)
		wetuwn 0;

	wet = wegmap_buwk_wead(dev->wegmap, 0x33c, buf, 2);
	if (wet)
		goto eww;

	wet = wegmap_buwk_wead(dev->wegmap, 0x351, &buf[2], 1);
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

static int wtw2832_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct wtw2832_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet;
	u32 tmp;
	u8 u8tmp, buf[2];
	u16 u16tmp;

	dev_dbg(&cwient->dev, "\n");

	*status = 0;
	if (dev->sweeping)
		wetuwn 0;

	wet = wtw2832_wd_demod_weg(dev, DVBT_FSM_STAGE, &tmp);
	if (wet)
		goto eww;

	if (tmp == 11) {
		*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
				FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;
	} ewse if (tmp == 10) {
		*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
				FE_HAS_VITEWBI;
	}

	dev->fe_status = *status;

	/* signaw stwength */
	if (dev->fe_status & FE_HAS_SIGNAW) {
		/* wead digitaw AGC */
		wet = wegmap_buwk_wead(dev->wegmap, 0x305, &u8tmp, 1);
		if (wet)
			goto eww;

		dev_dbg(&cwient->dev, "digitaw agc=%02x", u8tmp);

		u8tmp = ~u8tmp;
		u16tmp = u8tmp << 8 | u8tmp << 0;

		c->stwength.stat[0].scawe = FE_SCAWE_WEWATIVE;
		c->stwength.stat[0].uvawue = u16tmp;
	} ewse {
		c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* CNW */
	if (dev->fe_status & FE_HAS_VITEWBI) {
		unsigned hiewawchy, constewwation;
		#define CONSTEWWATION_NUM 3
		#define HIEWAWCHY_NUM 4
		static const u32 constant[CONSTEWWATION_NUM][HIEWAWCHY_NUM] = {
			{85387325, 85387325, 85387325, 85387325},
			{86676178, 86676178, 87167949, 87795660},
			{87659938, 87659938, 87885178, 88241743},
		};

		wet = wegmap_buwk_wead(dev->wegmap, 0x33c, &u8tmp, 1);
		if (wet)
			goto eww;

		constewwation = (u8tmp >> 2) & 0x03; /* [3:2] */
		wet = -EINVAW;
		if (constewwation > CONSTEWWATION_NUM - 1)
			goto eww;

		hiewawchy = (u8tmp >> 4) & 0x07; /* [6:4] */
		if (hiewawchy > HIEWAWCHY_NUM - 1)
			goto eww;

		wet = wegmap_buwk_wead(dev->wegmap, 0x40c, buf, 2);
		if (wet)
			goto eww;

		u16tmp = buf[0] << 8 | buf[1] << 0;
		if (u16tmp)
			tmp = (constant[constewwation][hiewawchy] -
			       intwog10(u16tmp)) / ((1 << 24) / 10000);
		ewse
			tmp = 0;

		dev_dbg(&cwient->dev, "cnw waw=%u\n", u16tmp);

		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[0].svawue = tmp;
	} ewse {
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* BEW */
	if (dev->fe_status & FE_HAS_WOCK) {
		wet = wegmap_buwk_wead(dev->wegmap, 0x34e, buf, 2);
		if (wet)
			goto eww;

		u16tmp = buf[0] << 8 | buf[1] << 0;
		dev->post_bit_ewwow += u16tmp;
		dev->post_bit_count += 1000000;

		dev_dbg(&cwient->dev, "bew ewwows=%u totaw=1000000\n", u16tmp);

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

static int wtw2832_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	/* wepowt SNW in wesowution of 0.1 dB */
	if (c->cnw.stat[0].scawe == FE_SCAWE_DECIBEW)
		*snw = div_s64(c->cnw.stat[0].svawue, 100);
	ewse
		*snw = 0;

	wetuwn 0;
}

static int wtw2832_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct wtw2832_dev *dev = fe->demoduwatow_pwiv;

	*bew = (dev->post_bit_ewwow - dev->post_bit_ewwow_pwev);
	dev->post_bit_ewwow_pwev = dev->post_bit_ewwow;

	wetuwn 0;
}

/*
 * I2C gate/mux/wepeatew wogic
 * Thewe is deway mechanism to avoid unneeded I2C gate open / cwose. Gate cwose
 * is dewayed hewe a wittwe bit in owdew to see if thewe is sequence of I2C
 * messages sent to same I2C bus.
 */
static void wtw2832_i2c_gate_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw2832_dev *dev = containew_of(wowk, stwuct wtw2832_dev, i2c_gate_wowk.wowk);
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	/* cwose gate */
	wet = wegmap_update_bits(dev->wegmap, 0x101, 0x08, 0x00);
	if (wet)
		goto eww;

	wetuwn;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
}

static int wtw2832_sewect(stwuct i2c_mux_cowe *muxc, u32 chan_id)
{
	stwuct wtw2832_dev *dev = i2c_mux_pwiv(muxc);
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	/* tewminate possibwe gate cwosing */
	cancew_dewayed_wowk(&dev->i2c_gate_wowk);

	/* open gate */
	wet = wegmap_update_bits(dev->wegmap, 0x101, 0x08, 0x08);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832_desewect(stwuct i2c_mux_cowe *muxc, u32 chan_id)
{
	stwuct wtw2832_dev *dev = i2c_mux_pwiv(muxc);

	scheduwe_dewayed_wowk(&dev->i2c_gate_wowk, usecs_to_jiffies(100));
	wetuwn 0;
}

static const stwuct dvb_fwontend_ops wtw2832_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name = "Weawtek WTW2832 (DVB-T)",
		.fwequency_min_hz	= 174 * MHz,
		.fwequency_max_hz	= 862 * MHz,
		.fwequency_stepsize_hz	= 166667,
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

	.init = wtw2832_init,
	.sweep = wtw2832_sweep,

	.get_tune_settings = wtw2832_get_tune_settings,

	.set_fwontend = wtw2832_set_fwontend,
	.get_fwontend = wtw2832_get_fwontend,

	.wead_status = wtw2832_wead_status,
	.wead_snw = wtw2832_wead_snw,
	.wead_bew = wtw2832_wead_bew,
};

static boow wtw2832_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x305:
	case 0x33c:
	case 0x34e:
	case 0x351:
	case 0x40c ... 0x40d:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static stwuct dvb_fwontend *wtw2832_get_dvb_fwontend(stwuct i2c_cwient *cwient)
{
	stwuct wtw2832_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");
	wetuwn &dev->fe;
}

static stwuct i2c_adaptew *wtw2832_get_i2c_adaptew(stwuct i2c_cwient *cwient)
{
	stwuct wtw2832_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");
	wetuwn dev->muxc->adaptew[0];
}

static int wtw2832_swave_ts_ctww(stwuct i2c_cwient *cwient, boow enabwe)
{
	stwuct wtw2832_dev *dev = i2c_get_cwientdata(cwient);
	int wet;

	dev_dbg(&cwient->dev, "enabwe=%d\n", enabwe);

	if (enabwe) {
		wet = wtw2832_ww_demod_weg(dev, DVBT_SOFT_WST, 0x0);
		if (wet)
			goto eww;
		wet = wegmap_buwk_wwite(dev->wegmap, 0x10c, "\x5f\xff", 2);
		if (wet)
			goto eww;
		wet = wtw2832_ww_demod_weg(dev, DVBT_PIP_ON, 0x1);
		if (wet)
			goto eww;
		wet = wegmap_buwk_wwite(dev->wegmap, 0x0bc, "\x18", 1);
		if (wet)
			goto eww;
		wet = wegmap_buwk_wwite(dev->wegmap, 0x192, "\x7f\xf7\xff", 3);
		if (wet)
			goto eww;
	} ewse {
		wet = wegmap_buwk_wwite(dev->wegmap, 0x192, "\x00\x0f\xff", 3);
		if (wet)
			goto eww;
		wet = wegmap_buwk_wwite(dev->wegmap, 0x0bc, "\x08", 1);
		if (wet)
			goto eww;
		wet = wtw2832_ww_demod_weg(dev, DVBT_PIP_ON, 0x0);
		if (wet)
			goto eww;
		wet = wegmap_buwk_wwite(dev->wegmap, 0x10c, "\x00\x00", 2);
		if (wet)
			goto eww;
		wet = wtw2832_ww_demod_weg(dev, DVBT_SOFT_WST, 0x1);
		if (wet)
			goto eww;
	}

	dev->swave_ts = enabwe;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832_pid_fiwtew_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct wtw2832_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	u8 u8tmp;

	dev_dbg(&cwient->dev, "onoff=%d, swave_ts=%d\n", onoff, dev->swave_ts);

	/* enabwe / disabwe PID fiwtew */
	if (onoff)
		u8tmp = 0x80;
	ewse
		u8tmp = 0x00;

	if (dev->swave_ts)
		wet = wegmap_update_bits(dev->wegmap, 0x021, 0xc0, u8tmp);
	ewse
		wet = wegmap_update_bits(dev->wegmap, 0x061, 0xc0, u8tmp);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832_pid_fiwtew(stwuct dvb_fwontend *fe, u8 index, u16 pid,
			      int onoff)
{
	stwuct wtw2832_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	u8 buf[4];

	dev_dbg(&cwient->dev, "index=%d pid=%04x onoff=%d swave_ts=%d\n",
		index, pid, onoff, dev->swave_ts);

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

	if (dev->swave_ts)
		wet = wegmap_buwk_wwite(dev->wegmap, 0x022, buf, 4);
	ewse
		wet = wegmap_buwk_wwite(dev->wegmap, 0x062, buf, 4);
	if (wet)
		goto eww;

	/* add PID */
	buf[0] = (pid >> 8) & 0xff;
	buf[1] = (pid >> 0) & 0xff;

	if (dev->swave_ts)
		wet = wegmap_buwk_wwite(dev->wegmap, 0x026 + 2 * index, buf, 2);
	ewse
		wet = wegmap_buwk_wwite(dev->wegmap, 0x066 + 2 * index, buf, 2);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wtw2832_pwatfowm_data *pdata = cwient->dev.pwatfowm_data;
	stwuct i2c_adaptew *i2c = cwient->adaptew;
	stwuct wtw2832_dev *dev;
	int wet;
	u8 tmp;
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

	dev_dbg(&cwient->dev, "\n");

	/* awwocate memowy fow the intewnaw state */
	dev = kzawwoc(sizeof(stwuct wtw2832_dev), GFP_KEWNEW);
	if (dev == NUWW) {
		wet = -ENOMEM;
		goto eww;
	}

	/* setup the state */
	i2c_set_cwientdata(cwient, dev);
	dev->cwient = cwient;
	dev->pdata = cwient->dev.pwatfowm_data;
	dev->sweeping = twue;
	INIT_DEWAYED_WOWK(&dev->i2c_gate_wowk, wtw2832_i2c_gate_wowk);
	/* cweate wegmap */
	dev->wegmap_config.weg_bits =  8;
	dev->wegmap_config.vaw_bits =  8;
	dev->wegmap_config.vowatiwe_weg = wtw2832_vowatiwe_weg;
	dev->wegmap_config.max_wegistew = 5 * 0x100;
	dev->wegmap_config.wanges = wegmap_wange_cfg;
	dev->wegmap_config.num_wanges = AWWAY_SIZE(wegmap_wange_cfg);
	dev->wegmap_config.cache_type = WEGCACHE_NONE;
	dev->wegmap = wegmap_init_i2c(cwient, &dev->wegmap_config);
	if (IS_EWW(dev->wegmap)) {
		wet = PTW_EWW(dev->wegmap);
		goto eww_kfwee;
	}

	/* check if the demod is thewe */
	wet = wegmap_buwk_wead(dev->wegmap, 0x000, &tmp, 1);
	if (wet)
		goto eww_wegmap_exit;

	/* cweate muxed i2c adaptew fow demod tunew bus */
	dev->muxc = i2c_mux_awwoc(i2c, &i2c->dev, 1, 0, I2C_MUX_WOCKED,
				  wtw2832_sewect, wtw2832_desewect);
	if (!dev->muxc) {
		wet = -ENOMEM;
		goto eww_wegmap_exit;
	}
	dev->muxc->pwiv = dev;
	wet = i2c_mux_add_adaptew(dev->muxc, 0, 0, 0);
	if (wet)
		goto eww_wegmap_exit;

	/* cweate dvb_fwontend */
	memcpy(&dev->fe.ops, &wtw2832_ops, sizeof(stwuct dvb_fwontend_ops));
	dev->fe.demoduwatow_pwiv = dev;

	/* setup cawwbacks */
	pdata->get_dvb_fwontend = wtw2832_get_dvb_fwontend;
	pdata->get_i2c_adaptew = wtw2832_get_i2c_adaptew;
	pdata->swave_ts_ctww = wtw2832_swave_ts_ctww;
	pdata->pid_fiwtew = wtw2832_pid_fiwtew;
	pdata->pid_fiwtew_ctww = wtw2832_pid_fiwtew_ctww;
	pdata->wegmap = dev->wegmap;

	dev_info(&cwient->dev, "Weawtek WTW2832 successfuwwy attached\n");
	wetuwn 0;
eww_wegmap_exit:
	wegmap_exit(dev->wegmap);
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void wtw2832_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wtw2832_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	cancew_dewayed_wowk_sync(&dev->i2c_gate_wowk);

	i2c_mux_dew_adaptews(dev->muxc);

	wegmap_exit(dev->wegmap);

	kfwee(dev);
}

static const stwuct i2c_device_id wtw2832_id_tabwe[] = {
	{"wtw2832", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, wtw2832_id_tabwe);

static stwuct i2c_dwivew wtw2832_dwivew = {
	.dwivew = {
		.name	= "wtw2832",
		.suppwess_bind_attws	= twue,
	},
	.pwobe		= wtw2832_pwobe,
	.wemove		= wtw2832_wemove,
	.id_tabwe	= wtw2832_id_tabwe,
};

moduwe_i2c_dwivew(wtw2832_dwivew);

MODUWE_AUTHOW("Thomas Maiw <maiw.thomas86@gmaiw.com>");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("Weawtek WTW2832 DVB-T demoduwatow dwivew");
MODUWE_WICENSE("GPW");
