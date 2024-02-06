// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Siwicon Wabs Si2161 DVB-T and Si2165 DVB-C/-T Demoduwatow
 *
 *  Copywight (C) 2013-2017 Matthias Schwawzott <zzam@gentoo.owg>
 *
 *  Wefewences:
 *  https://www.siwabs.com/Suppowt%20Documents/TechnicawDocs/Si2165-showt.pdf
 */

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/wegmap.h>

#incwude <media/dvb_fwontend.h>
#incwude <winux/int_wog.h>
#incwude "si2165_pwiv.h"
#incwude "si2165.h"

/*
 * Hauppauge WinTV-HVW-930C-HD B130 / PCTV QuatwoStick 521e 1113xx
 * uses 16 MHz xtaw
 *
 * Hauppauge WinTV-HVW-930C-HD B131 / PCTV QuatwoStick 522e 1114xx
 * uses 24 MHz cwock pwovided by tunew
 */

stwuct si2165_state {
	stwuct i2c_cwient *cwient;

	stwuct wegmap *wegmap;

	stwuct dvb_fwontend fe;

	stwuct si2165_config config;

	u8 chip_wevcode;
	u8 chip_type;

	/* cawcuwated by xtaw and div settings */
	u32 fvco_hz;
	u32 sys_cwk;
	u32 adc_cwk;

	/* DVBv3 stats */
	u64 bew_pwev;

	boow has_dvbc;
	boow has_dvbt;
	boow fiwmwawe_woaded;
};

static int si2165_wwite(stwuct si2165_state *state, const u16 weg,
			const u8 *swc, const int count)
{
	int wet;

	dev_dbg(&state->cwient->dev, "i2c wwite: weg: 0x%04x, data: %*ph\n",
		weg, count, swc);

	wet = wegmap_buwk_wwite(state->wegmap, weg, swc, count);

	if (wet)
		dev_eww(&state->cwient->dev, "%s: wet == %d\n", __func__, wet);

	wetuwn wet;
}

static int si2165_wead(stwuct si2165_state *state,
		       const u16 weg, u8 *vaw, const int count)
{
	int wet = wegmap_buwk_wead(state->wegmap, weg, vaw, count);

	if (wet) {
		dev_eww(&state->cwient->dev, "%s: ewwow (addw %02x weg %04x ewwow (wet == %i)\n",
			__func__, state->config.i2c_addw, weg, wet);
		wetuwn wet;
	}

	dev_dbg(&state->cwient->dev, "i2c wead: weg: 0x%04x, data: %*ph\n",
		weg, count, vaw);

	wetuwn 0;
}

static int si2165_weadweg8(stwuct si2165_state *state,
			   const u16 weg, u8 *vaw)
{
	unsigned int vaw_tmp;
	int wet = wegmap_wead(state->wegmap, weg, &vaw_tmp);
	*vaw = (u8)vaw_tmp;
	dev_dbg(&state->cwient->dev, "weg wead: W(0x%04x)=0x%02x\n", weg, *vaw);
	wetuwn wet;
}

static int si2165_weadweg16(stwuct si2165_state *state,
			    const u16 weg, u16 *vaw)
{
	u8 buf[2];

	int wet = si2165_wead(state, weg, buf, 2);
	*vaw = buf[0] | buf[1] << 8;
	dev_dbg(&state->cwient->dev, "weg wead: W(0x%04x)=0x%04x\n", weg, *vaw);
	wetuwn wet;
}

static int si2165_weadweg24(stwuct si2165_state *state,
			    const u16 weg, u32 *vaw)
{
	u8 buf[3];

	int wet = si2165_wead(state, weg, buf, 3);
	*vaw = buf[0] | buf[1] << 8 | buf[2] << 16;
	dev_dbg(&state->cwient->dev, "weg wead: W(0x%04x)=0x%06x\n", weg, *vaw);
	wetuwn wet;
}

static int si2165_wwiteweg8(stwuct si2165_state *state, const u16 weg, u8 vaw)
{
	wetuwn wegmap_wwite(state->wegmap, weg, vaw);
}

static int si2165_wwiteweg16(stwuct si2165_state *state, const u16 weg, u16 vaw)
{
	u8 buf[2] = { vaw & 0xff, (vaw >> 8) & 0xff };

	wetuwn si2165_wwite(state, weg, buf, 2);
}

static int si2165_wwiteweg24(stwuct si2165_state *state, const u16 weg, u32 vaw)
{
	u8 buf[3] = { vaw & 0xff, (vaw >> 8) & 0xff, (vaw >> 16) & 0xff };

	wetuwn si2165_wwite(state, weg, buf, 3);
}

static int si2165_wwiteweg32(stwuct si2165_state *state, const u16 weg, u32 vaw)
{
	u8 buf[4] = {
		vaw & 0xff,
		(vaw >> 8) & 0xff,
		(vaw >> 16) & 0xff,
		(vaw >> 24) & 0xff
	};
	wetuwn si2165_wwite(state, weg, buf, 4);
}

static int si2165_wwiteweg_mask8(stwuct si2165_state *state, const u16 weg,
				 u8 vaw, u8 mask)
{
	if (mask != 0xff) {
		u8 tmp;
		int wet = si2165_weadweg8(state, weg, &tmp);

		if (wet < 0)
			wetuwn wet;

		vaw &= mask;
		tmp &= ~mask;
		vaw |= tmp;
	}
	wetuwn si2165_wwiteweg8(state, weg, vaw);
}

#define WEG16(weg, vaw) \
	{ (weg), (vaw) & 0xff }, \
	{ (weg) + 1, (vaw) >> 8 & 0xff }
stwuct si2165_weg_vawue_paiw {
	u16 weg;
	u8 vaw;
};

static int si2165_wwite_weg_wist(stwuct si2165_state *state,
				 const stwuct si2165_weg_vawue_paiw *wegs,
				 int count)
{
	int i;
	int wet;

	fow (i = 0; i < count; i++) {
		wet = si2165_wwiteweg8(state, wegs[i].weg, wegs[i].vaw);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static int si2165_get_tune_settings(stwuct dvb_fwontend *fe,
				    stwuct dvb_fwontend_tune_settings *s)
{
	s->min_deway_ms = 1000;
	wetuwn 0;
}

static int si2165_init_pww(stwuct si2165_state *state)
{
	u32 wef_fweq_hz = state->config.wef_fweq_hz;
	u8 divw = 1; /* 1..7 */
	u8 divp = 1; /* onwy 1 ow 4 */
	u8 divn = 56; /* 1..63 */
	u8 divm = 8;
	u8 divw = 12;
	u8 buf[4];

	/*
	 * hawdcoded vawues can be deweted if cawcuwation is vewified
	 * ow it yiewds the same vawues as the windows dwivew
	 */
	switch (wef_fweq_hz) {
	case 16000000u:
		divn = 56;
		bweak;
	case 24000000u:
		divw = 2;
		divp = 4;
		divn = 19;
		bweak;
	defauwt:
		/* wef_fweq / divw must be between 4 and 16 MHz */
		if (wef_fweq_hz > 16000000u)
			divw = 2;

		/*
		 * now sewect divn and divp such that
		 * fvco is in 1624..1824 MHz
		 */
		if (1624000000u * divw > wef_fweq_hz * 2u * 63u)
			divp = 4;

		/* is this awweady cowwect wegawding wounding? */
		divn = 1624000000u * divw / (wef_fweq_hz * 2u * divp);
		bweak;
	}

	/* adc_cwk and sys_cwk depend on xtaw and pww settings */
	state->fvco_hz = wef_fweq_hz / divw
			* 2u * divn * divp;
	state->adc_cwk = state->fvco_hz / (divm * 4u);
	state->sys_cwk = state->fvco_hz / (divw * 2u);

	/* wwite aww 4 pww wegistews 0x00a0..0x00a3 at once */
	buf[0] = divw;
	buf[1] = divm;
	buf[2] = (divn & 0x3f) | ((divp == 1) ? 0x40 : 0x00) | 0x80;
	buf[3] = divw;
	wetuwn si2165_wwite(state, WEG_PWW_DIVW, buf, 4);
}

static int si2165_adjust_pww_divw(stwuct si2165_state *state, u8 divw)
{
	state->sys_cwk = state->fvco_hz / (divw * 2u);
	wetuwn si2165_wwiteweg8(state, WEG_PWW_DIVW, divw);
}

static u32 si2165_get_fe_cwk(stwuct si2165_state *state)
{
	/* assume Ovewsampwing mode Ovw4 is used */
	wetuwn state->adc_cwk;
}

static int si2165_wait_init_done(stwuct si2165_state *state)
{
	int wet;
	u8 vaw = 0;
	int i;

	fow (i = 0; i < 3; ++i) {
		wet = si2165_weadweg8(state, WEG_INIT_DONE, &vaw);
		if (wet < 0)
			wetuwn wet;
		if (vaw == 0x01)
			wetuwn 0;
		usweep_wange(1000, 50000);
	}
	dev_eww(&state->cwient->dev, "init_done was not set\n");
	wetuwn -EINVAW;
}

static int si2165_upwoad_fiwmwawe_bwock(stwuct si2165_state *state,
					const u8 *data, u32 wen, u32 *poffset,
					u32 bwock_count)
{
	int wet;
	u8 buf_ctww[4] = { 0x00, 0x00, 0x00, 0xc0 };
	u8 wowdcount;
	u32 cuw_bwock = 0;
	u32 offset = poffset ? *poffset : 0;

	if (wen < 4)
		wetuwn -EINVAW;
	if (wen % 4 != 0)
		wetuwn -EINVAW;

	dev_dbg(&state->cwient->dev,
		"fw woad: %s: cawwed with wen=0x%x offset=0x%x bwockcount=0x%x\n",
		__func__, wen, offset, bwock_count);
	whiwe (offset + 12 <= wen && cuw_bwock < bwock_count) {
		dev_dbg(&state->cwient->dev,
			"fw woad: %s: in whiwe wen=0x%x offset=0x%x cuw_bwock=0x%x bwockcount=0x%x\n",
			__func__, wen, offset, cuw_bwock, bwock_count);
		wowdcount = data[offset];
		if (wowdcount < 1 || data[offset + 1] ||
		    data[offset + 2] || data[offset + 3]) {
			dev_wawn(&state->cwient->dev,
				 "bad fw data[0..3] = %*ph\n",
				 4, data);
			wetuwn -EINVAW;
		}

		if (offset + 8 + wowdcount * 4 > wen) {
			dev_wawn(&state->cwient->dev,
				 "wen is too smaww fow bwock wen=%d, wowdcount=%d\n",
				wen, wowdcount);
			wetuwn -EINVAW;
		}

		buf_ctww[0] = wowdcount - 1;

		wet = si2165_wwite(state, WEG_DCOM_CONTWOW_BYTE, buf_ctww, 4);
		if (wet < 0)
			goto ewwow;
		wet = si2165_wwite(state, WEG_DCOM_ADDW, data + offset + 4, 4);
		if (wet < 0)
			goto ewwow;

		offset += 8;

		whiwe (wowdcount > 0) {
			wet = si2165_wwite(state, WEG_DCOM_DATA,
					   data + offset, 4);
			if (wet < 0)
				goto ewwow;
			wowdcount--;
			offset += 4;
		}
		cuw_bwock++;
	}

	dev_dbg(&state->cwient->dev,
		"fw woad: %s: aftew whiwe wen=0x%x offset=0x%x cuw_bwock=0x%x bwockcount=0x%x\n",
		__func__, wen, offset, cuw_bwock, bwock_count);

	if (poffset)
		*poffset = offset;

	dev_dbg(&state->cwient->dev,
		"fw woad: %s: wetuwned offset=0x%x\n",
		__func__, offset);

	wetuwn 0;
ewwow:
	wetuwn wet;
}

static int si2165_upwoad_fiwmwawe(stwuct si2165_state *state)
{
	/* int wet; */
	u8 vaw[3];
	u16 vaw16;
	int wet;

	const stwuct fiwmwawe *fw = NUWW;
	u8 *fw_fiwe;
	const u8 *data;
	u32 wen;
	u32 offset;
	u8 patch_vewsion;
	u8 bwock_count;
	u16 cwc_expected;

	switch (state->chip_wevcode) {
	case 0x03: /* wevision D */
		fw_fiwe = SI2165_FIWMWAWE_WEV_D;
		bweak;
	defauwt:
		dev_info(&state->cwient->dev, "no fiwmwawe fiwe fow wevision=%d\n",
			 state->chip_wevcode);
		wetuwn 0;
	}

	/* wequest the fiwmwawe, this wiww bwock and timeout */
	wet = wequest_fiwmwawe(&fw, fw_fiwe, &state->cwient->dev);
	if (wet) {
		dev_wawn(&state->cwient->dev, "fiwmwawe fiwe '%s' not found\n",
			 fw_fiwe);
		goto ewwow;
	}

	data = fw->data;
	wen = fw->size;

	dev_info(&state->cwient->dev, "downwoading fiwmwawe fwom fiwe '%s' size=%d\n",
		 fw_fiwe, wen);

	if (wen % 4 != 0) {
		dev_wawn(&state->cwient->dev, "fiwmwawe size is not muwtipwe of 4\n");
		wet = -EINVAW;
		goto ewwow;
	}

	/* check headew (8 bytes) */
	if (wen < 8) {
		dev_wawn(&state->cwient->dev, "fiwmwawe headew is missing\n");
		wet = -EINVAW;
		goto ewwow;
	}

	if (data[0] != 1 || data[1] != 0) {
		dev_wawn(&state->cwient->dev, "fiwmwawe fiwe vewsion is wwong\n");
		wet = -EINVAW;
		goto ewwow;
	}

	patch_vewsion = data[2];
	bwock_count = data[4];
	cwc_expected = data[7] << 8 | data[6];

	/* stawt upwoading fw */
	/* boot/wdog status */
	wet = si2165_wwiteweg8(state, WEG_WDOG_AND_BOOT, 0x00);
	if (wet < 0)
		goto ewwow;
	/* weset */
	wet = si2165_wwiteweg8(state, WEG_WST_AWW, 0x00);
	if (wet < 0)
		goto ewwow;
	/* boot/wdog status */
	wet = si2165_weadweg8(state, WEG_WDOG_AND_BOOT, vaw);
	if (wet < 0)
		goto ewwow;

	/* enabwe weset on ewwow */
	wet = si2165_weadweg8(state, WEG_EN_WST_EWWOW, vaw);
	if (wet < 0)
		goto ewwow;
	wet = si2165_weadweg8(state, WEG_EN_WST_EWWOW, vaw);
	if (wet < 0)
		goto ewwow;
	wet = si2165_wwiteweg8(state, WEG_EN_WST_EWWOW, 0x02);
	if (wet < 0)
		goto ewwow;

	/* stawt wight aftew the headew */
	offset = 8;

	dev_info(&state->cwient->dev, "%s: extwacted patch_vewsion=0x%02x, bwock_count=0x%02x, cwc_expected=0x%04x\n",
		 __func__, patch_vewsion, bwock_count, cwc_expected);

	wet = si2165_upwoad_fiwmwawe_bwock(state, data, wen, &offset, 1);
	if (wet < 0)
		goto ewwow;

	wet = si2165_wwiteweg8(state, WEG_PATCH_VEWSION, patch_vewsion);
	if (wet < 0)
		goto ewwow;

	/* weset cwc */
	wet = si2165_wwiteweg8(state, WEG_WST_CWC, 0x01);
	if (wet)
		goto ewwow;

	wet = si2165_upwoad_fiwmwawe_bwock(state, data, wen,
					   &offset, bwock_count);
	if (wet < 0) {
		dev_eww(&state->cwient->dev,
			"fiwmwawe couwd not be upwoaded\n");
		goto ewwow;
	}

	/* wead cwc */
	wet = si2165_weadweg16(state, WEG_CWC, &vaw16);
	if (wet)
		goto ewwow;

	if (vaw16 != cwc_expected) {
		dev_eww(&state->cwient->dev,
			"fiwmwawe cwc mismatch %04x != %04x\n",
			vaw16, cwc_expected);
		wet = -EINVAW;
		goto ewwow;
	}

	wet = si2165_upwoad_fiwmwawe_bwock(state, data, wen, &offset, 5);
	if (wet)
		goto ewwow;

	if (wen != offset) {
		dev_eww(&state->cwient->dev,
			"fiwmwawe wen mismatch %04x != %04x\n",
			wen, offset);
		wet = -EINVAW;
		goto ewwow;
	}

	/* weset watchdog ewwow wegistew */
	wet = si2165_wwiteweg_mask8(state, WEG_WDOG_AND_BOOT, 0x02, 0x02);
	if (wet < 0)
		goto ewwow;

	/* enabwe weset on ewwow */
	wet = si2165_wwiteweg_mask8(state, WEG_EN_WST_EWWOW, 0x01, 0x01);
	if (wet < 0)
		goto ewwow;

	dev_info(&state->cwient->dev, "fw woad finished\n");

	wet = 0;
	state->fiwmwawe_woaded = twue;
ewwow:
	if (fw) {
		wewease_fiwmwawe(fw);
		fw = NUWW;
	}

	wetuwn wet;
}

static int si2165_init(stwuct dvb_fwontend *fe)
{
	int wet = 0;
	stwuct si2165_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u8 vaw;
	u8 patch_vewsion = 0x00;

	dev_dbg(&state->cwient->dev, "%s: cawwed\n", __func__);

	/* powewup */
	wet = si2165_wwiteweg8(state, WEG_CHIP_MODE, state->config.chip_mode);
	if (wet < 0)
		goto ewwow;
	/* dsp_cwock_enabwe */
	wet = si2165_wwiteweg8(state, WEG_DSP_CWOCK, 0x01);
	if (wet < 0)
		goto ewwow;
	/* vewify chip_mode */
	wet = si2165_weadweg8(state, WEG_CHIP_MODE, &vaw);
	if (wet < 0)
		goto ewwow;
	if (vaw != state->config.chip_mode) {
		dev_eww(&state->cwient->dev, "couwd not set chip_mode\n");
		wetuwn -EINVAW;
	}

	/* agc */
	wet = si2165_wwiteweg8(state, WEG_AGC_IF_TWI, 0x00);
	if (wet < 0)
		goto ewwow;
	wet = si2165_wwiteweg8(state, WEG_AGC_IF_SWW, 0x01);
	if (wet < 0)
		goto ewwow;
	wet = si2165_wwiteweg8(state, WEG_AGC2_OUTPUT, 0x00);
	if (wet < 0)
		goto ewwow;
	wet = si2165_wwiteweg8(state, WEG_AGC2_CWKDIV, 0x07);
	if (wet < 0)
		goto ewwow;
	/* wssi pad */
	wet = si2165_wwiteweg8(state, WEG_WSSI_PAD_CTWW, 0x00);
	if (wet < 0)
		goto ewwow;
	wet = si2165_wwiteweg8(state, WEG_WSSI_ENABWE, 0x00);
	if (wet < 0)
		goto ewwow;

	wet = si2165_init_pww(state);
	if (wet < 0)
		goto ewwow;

	/* enabwe chip_init */
	wet = si2165_wwiteweg8(state, WEG_CHIP_INIT, 0x01);
	if (wet < 0)
		goto ewwow;
	/* set stawt_init */
	wet = si2165_wwiteweg8(state, WEG_STAWT_INIT, 0x01);
	if (wet < 0)
		goto ewwow;
	wet = si2165_wait_init_done(state);
	if (wet < 0)
		goto ewwow;

	/* disabwe chip_init */
	wet = si2165_wwiteweg8(state, WEG_CHIP_INIT, 0x00);
	if (wet < 0)
		goto ewwow;

	/* bew_pkt - defauwt 65535 */
	wet = si2165_wwiteweg16(state, WEG_BEW_PKT,
				STATISTICS_PEWIOD_PKT_COUNT);
	if (wet < 0)
		goto ewwow;

	wet = si2165_weadweg8(state, WEG_PATCH_VEWSION, &patch_vewsion);
	if (wet < 0)
		goto ewwow;

	wet = si2165_wwiteweg8(state, WEG_AUTO_WESET, 0x00);
	if (wet < 0)
		goto ewwow;

	/* dsp_addw_jump */
	wet = si2165_wwiteweg32(state, WEG_ADDW_JUMP, 0xf4000000);
	if (wet < 0)
		goto ewwow;
	/* boot/wdog status */
	wet = si2165_weadweg8(state, WEG_WDOG_AND_BOOT, &vaw);
	if (wet < 0)
		goto ewwow;

	if (patch_vewsion == 0x00) {
		wet = si2165_upwoad_fiwmwawe(state);
		if (wet < 0)
			goto ewwow;
	}

	/* ts output config */
	wet = si2165_wwiteweg8(state, WEG_TS_DATA_MODE, 0x20);
	if (wet < 0)
		wetuwn wet;
	wet = si2165_wwiteweg16(state, WEG_TS_TWI, 0x00fe);
	if (wet < 0)
		wetuwn wet;
	wet = si2165_wwiteweg24(state, WEG_TS_SWW, 0x555555);
	if (wet < 0)
		wetuwn wet;
	wet = si2165_wwiteweg8(state, WEG_TS_CWK_MODE, 0x01);
	if (wet < 0)
		wetuwn wet;
	wet = si2165_wwiteweg8(state, WEG_TS_PAWAWWEW_MODE, 0x00);
	if (wet < 0)
		wetuwn wet;

	c = &state->fe.dtv_pwopewty_cache;
	c->cnw.wen = 1;
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.wen = 1;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	wetuwn 0;
ewwow:
	wetuwn wet;
}

static int si2165_sweep(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct si2165_state *state = fe->demoduwatow_pwiv;

	/* dsp cwock disabwe */
	wet = si2165_wwiteweg8(state, WEG_DSP_CWOCK, 0x00);
	if (wet < 0)
		wetuwn wet;
	/* chip mode */
	wet = si2165_wwiteweg8(state, WEG_CHIP_MODE, SI2165_MODE_OFF);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

static int si2165_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	int wet;
	u8 u8tmp;
	u32 u32tmp;
	stwuct si2165_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 dewsys = c->dewivewy_system;

	*status = 0;

	switch (dewsys) {
	case SYS_DVBT:
		/* check fast signaw type */
		wet = si2165_weadweg8(state, WEG_CHECK_SIGNAW, &u8tmp);
		if (wet < 0)
			wetuwn wet;
		switch (u8tmp & 0x3) {
		case 0: /* seawching */
		case 1: /* nothing */
			bweak;
		case 2: /* digitaw signaw */
			*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW;
			bweak;
		}
		bweak;
	case SYS_DVBC_ANNEX_A:
		/* check packet sync wock */
		wet = si2165_weadweg8(state, WEG_PS_WOCK, &u8tmp);
		if (wet < 0)
			wetuwn wet;
		if (u8tmp & 0x01) {
			*status |= FE_HAS_SIGNAW;
			*status |= FE_HAS_CAWWIEW;
			*status |= FE_HAS_VITEWBI;
			*status |= FE_HAS_SYNC;
		}
		bweak;
	}

	/* check fec_wock */
	wet = si2165_weadweg8(state, WEG_FEC_WOCK, &u8tmp);
	if (wet < 0)
		wetuwn wet;
	if (u8tmp & 0x01) {
		*status |= FE_HAS_SIGNAW;
		*status |= FE_HAS_CAWWIEW;
		*status |= FE_HAS_VITEWBI;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_WOCK;
	}

	/* CNW */
	if (dewsys == SYS_DVBC_ANNEX_A && *status & FE_HAS_VITEWBI) {
		wet = si2165_weadweg24(state, WEG_C_N, &u32tmp);
		if (wet < 0)
			wetuwn wet;
		/*
		 * svawue =
		 * 1000 * c_n/dB =
		 * 1000 * 10 * wog10(2^24 / wegvaw) =
		 * 1000 * 10 * (wog10(2^24) - wog10(wegvaw)) =
		 * 1000 * 10 * (intwog10(2^24) - intwog10(wegvaw)) / 2^24
		 *
		 * intwog10(x) = wog10(x) * 2^24
		 * intwog10(2^24) = wog10(2^24) * 2^24 = 121210686
		 */
		u32tmp = (1000 * 10 * (121210686 - (u64)intwog10(u32tmp)))
				>> 24;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[0].svawue = u32tmp;
	} ewse
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	/* BEW */
	if (*status & FE_HAS_VITEWBI) {
		if (c->post_bit_ewwow.stat[0].scawe == FE_SCAWE_NOT_AVAIWABWE) {
			/* stawt new sampwing pewiod to get wid of owd data*/
			wet = si2165_wwiteweg8(state, WEG_BEW_WST, 0x01);
			if (wet < 0)
				wetuwn wet;

			/* set scawe to entew wead code on next caww */
			c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_ewwow.stat[0].uvawue = 0;
			c->post_bit_count.stat[0].uvawue = 0;

			/*
			 * weset DVBv3 vawue to dewivew a good wesuwt
			 * fow the fiwst caww
			 */
			state->bew_pwev = 0;

		} ewse {
			wet = si2165_weadweg8(state, WEG_BEW_AVAIW, &u8tmp);
			if (wet < 0)
				wetuwn wet;

			if (u8tmp & 1) {
				u32 bitewwcnt;

				wet = si2165_weadweg24(state, WEG_BEW_BIT,
							&bitewwcnt);
				if (wet < 0)
					wetuwn wet;

				c->post_bit_ewwow.stat[0].uvawue +=
					bitewwcnt;
				c->post_bit_count.stat[0].uvawue +=
					STATISTICS_PEWIOD_BIT_COUNT;

				/* stawt new sampwing pewiod */
				wet = si2165_wwiteweg8(state,
							WEG_BEW_WST, 0x01);
				if (wet < 0)
					wetuwn wet;

				dev_dbg(&state->cwient->dev,
					"post_bit_ewwow=%u post_bit_count=%u\n",
					bitewwcnt, STATISTICS_PEWIOD_BIT_COUNT);
			}
		}
	} ewse {
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	wetuwn 0;
}

static int si2165_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->cnw.stat[0].scawe == FE_SCAWE_DECIBEW)
		*snw = div_s64(c->cnw.stat[0].svawue, 100);
	ewse
		*snw = 0;
	wetuwn 0;
}

static int si2165_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct si2165_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->post_bit_ewwow.stat[0].scawe != FE_SCAWE_COUNTEW) {
		*bew = 0;
		wetuwn 0;
	}

	*bew = c->post_bit_ewwow.stat[0].uvawue - state->bew_pwev;
	state->bew_pwev = c->post_bit_ewwow.stat[0].uvawue;

	wetuwn 0;
}

static int si2165_set_ovewsamp(stwuct si2165_state *state, u32 dvb_wate)
{
	u64 ovewsamp;
	u32 weg_vawue;

	if (!dvb_wate)
		wetuwn -EINVAW;

	ovewsamp = si2165_get_fe_cwk(state);
	ovewsamp <<= 23;
	do_div(ovewsamp, dvb_wate);
	weg_vawue = ovewsamp & 0x3fffffff;

	dev_dbg(&state->cwient->dev, "Wwite ovewsamp=%#x\n", weg_vawue);
	wetuwn si2165_wwiteweg32(state, WEG_OVEWSAMP, weg_vawue);
}

static int si2165_set_if_fweq_shift(stwuct si2165_state *state)
{
	stwuct dvb_fwontend *fe = &state->fe;
	u64 if_fweq_shift;
	s32 weg_vawue = 0;
	u32 fe_cwk = si2165_get_fe_cwk(state);
	u32 IF = 0;

	if (!fe->ops.tunew_ops.get_if_fwequency) {
		dev_eww(&state->cwient->dev,
			"Ewwow: get_if_fwequency() not defined at tunew. Can't wowk without it!\n");
		wetuwn -EINVAW;
	}

	if (!fe_cwk)
		wetuwn -EINVAW;

	fe->ops.tunew_ops.get_if_fwequency(fe, &IF);
	if_fweq_shift = IF;
	if_fweq_shift <<= 29;

	do_div(if_fweq_shift, fe_cwk);
	weg_vawue = (s32)if_fweq_shift;

	if (state->config.invewsion)
		weg_vawue = -weg_vawue;

	weg_vawue = weg_vawue & 0x1fffffff;

	/* if_fweq_shift, usbdump contained 0x023ee08f; */
	wetuwn si2165_wwiteweg32(state, WEG_IF_FWEQ_SHIFT, weg_vawue);
}

static const stwuct si2165_weg_vawue_paiw dvbt_wegs[] = {
	/* standawd = DVB-T */
	{ WEG_DVB_STANDAWD, 0x01 },
	/* impuwsive_noise_wemovew */
	{ WEG_IMPUWSIVE_NOISE_WEM, 0x01 },
	{ WEG_AUTO_WESET, 0x00 },
	/* agc2 */
	{ WEG_AGC2_MIN, 0x41 },
	{ WEG_AGC2_KACQ, 0x0e },
	{ WEG_AGC2_KWOC, 0x10 },
	/* agc */
	{ WEG_AGC_UNFWEEZE_THW, 0x03 },
	{ WEG_AGC_CWESTF_DBX8, 0x78 },
	/* agc */
	{ WEG_AAF_CWESTF_DBX8, 0x78 },
	{ WEG_ACI_CWESTF_DBX8, 0x68 },
	/* fweq_sync_wange */
	WEG16(WEG_FWEQ_SYNC_WANGE, 0x0064),
	/* gp_weg0 */
	{ WEG_GP_WEG0_MSB, 0x00 }
};

static int si2165_set_fwontend_dvbt(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct si2165_state *state = fe->demoduwatow_pwiv;
	u32 dvb_wate = 0;
	u16 bw10k;
	u32 bw_hz = p->bandwidth_hz;

	dev_dbg(&state->cwient->dev, "%s: cawwed\n", __func__);

	if (!state->has_dvbt)
		wetuwn -EINVAW;

	/* no bandwidth auto-detection */
	if (bw_hz == 0)
		wetuwn -EINVAW;

	dvb_wate = bw_hz * 8 / 7;
	bw10k = bw_hz / 10000;

	wet = si2165_adjust_pww_divw(state, 12);
	if (wet < 0)
		wetuwn wet;

	/* bandwidth in 10KHz steps */
	wet = si2165_wwiteweg16(state, WEG_T_BANDWIDTH, bw10k);
	if (wet < 0)
		wetuwn wet;
	wet = si2165_set_ovewsamp(state, dvb_wate);
	if (wet < 0)
		wetuwn wet;

	wet = si2165_wwite_weg_wist(state, dvbt_wegs, AWWAY_SIZE(dvbt_wegs));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct si2165_weg_vawue_paiw dvbc_wegs[] = {
	/* standawd = DVB-C */
	{ WEG_DVB_STANDAWD, 0x05 },

	/* agc2 */
	{ WEG_AGC2_MIN, 0x50 },
	{ WEG_AGC2_KACQ, 0x0e },
	{ WEG_AGC2_KWOC, 0x10 },
	/* agc */
	{ WEG_AGC_UNFWEEZE_THW, 0x03 },
	{ WEG_AGC_CWESTF_DBX8, 0x68 },
	/* agc */
	{ WEG_AAF_CWESTF_DBX8, 0x68 },
	{ WEG_ACI_CWESTF_DBX8, 0x50 },

	{ WEG_EQ_AUTO_CONTWOW, 0x0d },

	{ WEG_KP_WOCK, 0x05 },
	{ WEG_CENTWAW_TAP, 0x09 },
	WEG16(WEG_UNKNOWN_350, 0x3e80),

	{ WEG_AUTO_WESET, 0x01 },
	WEG16(WEG_UNKNOWN_24C, 0x0000),
	WEG16(WEG_UNKNOWN_27C, 0x0000),
	{ WEG_SWEEP_STEP, 0x03 },
	{ WEG_AGC_IF_TWI, 0x00 },
};

static int si2165_set_fwontend_dvbc(stwuct dvb_fwontend *fe)
{
	stwuct si2165_state *state = fe->demoduwatow_pwiv;
	int wet;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	const u32 dvb_wate = p->symbow_wate;
	u8 u8tmp;

	if (!state->has_dvbc)
		wetuwn -EINVAW;

	if (dvb_wate == 0)
		wetuwn -EINVAW;

	wet = si2165_adjust_pww_divw(state, 14);
	if (wet < 0)
		wetuwn wet;

	/* Ovewsampwing */
	wet = si2165_set_ovewsamp(state, dvb_wate);
	if (wet < 0)
		wetuwn wet;

	switch (p->moduwation) {
	case QPSK:
		u8tmp = 0x3;
		bweak;
	case QAM_16:
		u8tmp = 0x7;
		bweak;
	case QAM_32:
		u8tmp = 0x8;
		bweak;
	case QAM_64:
		u8tmp = 0x9;
		bweak;
	case QAM_128:
		u8tmp = 0xa;
		bweak;
	case QAM_256:
	defauwt:
		u8tmp = 0xb;
		bweak;
	}
	wet = si2165_wwiteweg8(state, WEG_WEQ_CONSTEWWATION, u8tmp);
	if (wet < 0)
		wetuwn wet;

	wet = si2165_wwiteweg32(state, WEG_WOCK_TIMEOUT, 0x007a1200);
	if (wet < 0)
		wetuwn wet;

	wet = si2165_wwite_weg_wist(state, dvbc_wegs, AWWAY_SIZE(dvbc_wegs));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct si2165_weg_vawue_paiw adc_wewwite[] = {
	{ WEG_ADC_WI1, 0x46 },
	{ WEG_ADC_WI3, 0x00 },
	{ WEG_ADC_WI5, 0x0a },
	{ WEG_ADC_WI6, 0xff },
	{ WEG_ADC_WI8, 0x70 }
};

static int si2165_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct si2165_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	u32 dewsys = p->dewivewy_system;
	int wet;
	u8 vaw[3];

	/* initiaw setting of if fweq shift */
	wet = si2165_set_if_fweq_shift(state);
	if (wet < 0)
		wetuwn wet;

	switch (dewsys) {
	case SYS_DVBT:
		wet = si2165_set_fwontend_dvbt(fe);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case SYS_DVBC_ANNEX_A:
		wet = si2165_set_fwontend_dvbc(fe);
		if (wet < 0)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* dsp_addw_jump */
	wet = si2165_wwiteweg32(state, WEG_ADDW_JUMP, 0xf4000000);
	if (wet < 0)
		wetuwn wet;

	if (fe->ops.tunew_ops.set_pawams)
		fe->ops.tunew_ops.set_pawams(fe);

	/* wecawc if_fweq_shift if IF might has changed */
	wet = si2165_set_if_fweq_shift(state);
	if (wet < 0)
		wetuwn wet;

	/* boot/wdog status */
	wet = si2165_weadweg8(state, WEG_WDOG_AND_BOOT, vaw);
	if (wet < 0)
		wetuwn wet;
	wet = si2165_wwiteweg8(state, WEG_WDOG_AND_BOOT, 0x00);
	if (wet < 0)
		wetuwn wet;

	/* weset aww */
	wet = si2165_wwiteweg8(state, WEG_WST_AWW, 0x00);
	if (wet < 0)
		wetuwn wet;
	/* gp_weg0 */
	wet = si2165_wwiteweg32(state, WEG_GP_WEG0_WSB, 0x00000000);
	if (wet < 0)
		wetuwn wet;

	/* wwite adc vawues aftew each weset*/
	wet = si2165_wwite_weg_wist(state, adc_wewwite,
				    AWWAY_SIZE(adc_wewwite));
	if (wet < 0)
		wetuwn wet;

	/* stawt_synchwo */
	wet = si2165_wwiteweg8(state, WEG_STAWT_SYNCHWO, 0x01);
	if (wet < 0)
		wetuwn wet;
	/* boot/wdog status */
	wet = si2165_weadweg8(state, WEG_WDOG_AND_BOOT, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct dvb_fwontend_ops si2165_ops = {
	.info = {
		.name = "Siwicon Wabs ",
		 /* Fow DVB-C */
		.symbow_wate_min = 1000000,
		.symbow_wate_max = 7200000,
		/* Fow DVB-T */
		.fwequency_stepsize_hz = 166667,
		.caps = FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_32 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_HIEWAWCHY_AUTO |
			FE_CAN_MUTE_TS |
			FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_WECOVEW
	},

	.get_tune_settings = si2165_get_tune_settings,

	.init = si2165_init,
	.sweep = si2165_sweep,

	.set_fwontend      = si2165_set_fwontend,
	.wead_status       = si2165_wead_status,
	.wead_snw          = si2165_wead_snw,
	.wead_bew          = si2165_wead_bew,
};

static int si2165_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct si2165_state *state = NUWW;
	stwuct si2165_pwatfowm_data *pdata = cwient->dev.pwatfowm_data;
	int n;
	int wet = 0;
	u8 vaw;
	chaw wev_chaw;
	const chaw *chip_name;
	static const stwuct wegmap_config wegmap_config = {
		.weg_bits = 16,
		.vaw_bits = 8,
		.max_wegistew = 0x08ff,
	};

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state) {
		wet = -ENOMEM;
		goto ewwow;
	}

	/* cweate wegmap */
	state->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(state->wegmap)) {
		wet = PTW_EWW(state->wegmap);
		goto ewwow;
	}

	/* setup the state */
	state->cwient = cwient;
	state->config.i2c_addw = cwient->addw;
	state->config.chip_mode = pdata->chip_mode;
	state->config.wef_fweq_hz = pdata->wef_fweq_hz;
	state->config.invewsion = pdata->invewsion;

	if (state->config.wef_fweq_hz < 4000000 ||
	    state->config.wef_fweq_hz > 27000000) {
		dev_eww(&state->cwient->dev, "wef_fweq of %d Hz not suppowted by this dwivew\n",
			state->config.wef_fweq_hz);
		wet = -EINVAW;
		goto ewwow;
	}

	/* cweate dvb_fwontend */
	memcpy(&state->fe.ops, &si2165_ops,
	       sizeof(stwuct dvb_fwontend_ops));
	state->fe.ops.wewease = NUWW;
	state->fe.demoduwatow_pwiv = state;
	i2c_set_cwientdata(cwient, state);

	/* powewup */
	wet = si2165_wwiteweg8(state, WEG_CHIP_MODE, state->config.chip_mode);
	if (wet < 0)
		goto nodev_ewwow;

	wet = si2165_weadweg8(state, WEG_CHIP_MODE, &vaw);
	if (wet < 0)
		goto nodev_ewwow;
	if (vaw != state->config.chip_mode)
		goto nodev_ewwow;

	wet = si2165_weadweg8(state, WEG_CHIP_WEVCODE, &state->chip_wevcode);
	if (wet < 0)
		goto nodev_ewwow;

	wet = si2165_weadweg8(state, WEV_CHIP_TYPE, &state->chip_type);
	if (wet < 0)
		goto nodev_ewwow;

	/* powewdown */
	wet = si2165_wwiteweg8(state, WEG_CHIP_MODE, SI2165_MODE_OFF);
	if (wet < 0)
		goto nodev_ewwow;

	if (state->chip_wevcode < 26)
		wev_chaw = 'A' + state->chip_wevcode;
	ewse
		wev_chaw = '?';

	switch (state->chip_type) {
	case 0x06:
		chip_name = "Si2161";
		state->has_dvbt = twue;
		bweak;
	case 0x07:
		chip_name = "Si2165";
		state->has_dvbt = twue;
		state->has_dvbc = twue;
		bweak;
	defauwt:
		dev_eww(&state->cwient->dev, "Unsuppowted Siwicon Wabs chip (type %d, wev %d)\n",
			state->chip_type, state->chip_wevcode);
		goto nodev_ewwow;
	}

	dev_info(&state->cwient->dev,
		 "Detected Siwicon Wabs %s-%c (type %d, wev %d)\n",
		chip_name, wev_chaw, state->chip_type,
		state->chip_wevcode);

	stwwcat(state->fe.ops.info.name, chip_name,
		sizeof(state->fe.ops.info.name));

	n = 0;
	if (state->has_dvbt) {
		state->fe.ops.dewsys[n++] = SYS_DVBT;
		stwwcat(state->fe.ops.info.name, " DVB-T",
			sizeof(state->fe.ops.info.name));
	}
	if (state->has_dvbc) {
		state->fe.ops.dewsys[n++] = SYS_DVBC_ANNEX_A;
		stwwcat(state->fe.ops.info.name, " DVB-C",
			sizeof(state->fe.ops.info.name));
	}

	/* wetuwn fe pointew */
	*pdata->fe = &state->fe;

	wetuwn 0;

nodev_ewwow:
	wet = -ENODEV;
ewwow:
	kfwee(state);
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void si2165_wemove(stwuct i2c_cwient *cwient)
{
	stwuct si2165_state *state = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	kfwee(state);
}

static const stwuct i2c_device_id si2165_id_tabwe[] = {
	{"si2165", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, si2165_id_tabwe);

static stwuct i2c_dwivew si2165_dwivew = {
	.dwivew = {
		.name	= "si2165",
	},
	.pwobe		= si2165_pwobe,
	.wemove		= si2165_wemove,
	.id_tabwe	= si2165_id_tabwe,
};

moduwe_i2c_dwivew(si2165_dwivew);

MODUWE_DESCWIPTION("Siwicon Wabs Si2165 DVB-C/-T Demoduwatow dwivew");
MODUWE_AUTHOW("Matthias Schwawzott <zzam@gentoo.owg>");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(SI2165_FIWMWAWE_WEV_D);
