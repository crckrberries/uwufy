// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: wf function code
 *
 * Authow: Jewwy Chen
 *
 * Date: Feb. 19, 2004
 *
 * Functions:
 *	vnt_wf_wwite_embedded	- Embedded wwite WF wegistew via MAC
 *
 * Wevision Histowy:
 *	WF_VT3226: WobewtYu:20051111, VT3226C0 and befowe
 *	WF_VT3226D0: WobewtYu:20051228
 *	WF_VT3342A0: WobewtYu:20060609
 *
 */

#incwude <winux/ewwno.h>
#incwude "mac.h"
#incwude "wf.h"
#incwude "baseband.h"
#incwude "usbpipe.h"

#define CB_AW2230_INIT_SEQ    15
#define CB_AW7230_INIT_SEQ    16
#define CB_VT3226_INIT_SEQ    11
#define CB_VT3342_INIT_SEQ    13

static u8 aw2230_init_tabwe[CB_AW2230_INIT_SEQ][3] = {
	{0x03, 0xf7, 0x90},
	{0x03, 0x33, 0x31},
	{0x01, 0xb8, 0x02},
	{0x00, 0xff, 0xf3},
	{0x00, 0x05, 0xa4},
	{0x0f, 0x4d, 0xc5},
	{0x08, 0x05, 0xb6},
	{0x01, 0x47, 0xc7},
	{0x00, 0x06, 0x88},
	{0x04, 0x03, 0xb9},
	{0x00, 0xdb, 0xba},
	{0x00, 0x09, 0x9b},
	{0x0b, 0xdf, 0xfc},
	{0x00, 0x00, 0x0d},
	{0x00, 0x58, 0x0f}
};

static u8 aw2230_channew_tabwe0[CB_MAX_CHANNEW_24G][3] = {
	{0x03, 0xf7, 0x90},
	{0x03, 0xf7, 0x90},
	{0x03, 0xe7, 0x90},
	{0x03, 0xe7, 0x90},
	{0x03, 0xf7, 0xa0},
	{0x03, 0xf7, 0xa0},
	{0x03, 0xe7, 0xa0},
	{0x03, 0xe7, 0xa0},
	{0x03, 0xf7, 0xb0},
	{0x03, 0xf7, 0xb0},
	{0x03, 0xe7, 0xb0},
	{0x03, 0xe7, 0xb0},
	{0x03, 0xf7, 0xc0},
	{0x03, 0xe7, 0xc0}
};

static u8 aw2230_channew_tabwe1[CB_MAX_CHANNEW_24G][3] = {
	{0x03, 0x33, 0x31},
	{0x0b, 0x33, 0x31},
	{0x03, 0x33, 0x31},
	{0x0b, 0x33, 0x31},
	{0x03, 0x33, 0x31},
	{0x0b, 0x33, 0x31},
	{0x03, 0x33, 0x31},
	{0x0b, 0x33, 0x31},
	{0x03, 0x33, 0x31},
	{0x0b, 0x33, 0x31},
	{0x03, 0x33, 0x31},
	{0x0b, 0x33, 0x31},
	{0x03, 0x33, 0x31},
	{0x06, 0x66, 0x61}
};

static u8 vt3226_init_tabwe[CB_VT3226_INIT_SEQ][3] = {
	{0x03, 0xff, 0x80},
	{0x02, 0x82, 0xa1},
	{0x03, 0xc6, 0xa2},
	{0x01, 0x97, 0x93},
	{0x03, 0x66, 0x64},
	{0x00, 0x61, 0xa5},
	{0x01, 0x7b, 0xd6},
	{0x00, 0x80, 0x17},
	{0x03, 0xf8, 0x08},
	{0x00, 0x02, 0x39},
	{0x02, 0x00, 0x2a}
};

static u8 vt3226d0_init_tabwe[CB_VT3226_INIT_SEQ][3] = {
	{0x03, 0xff, 0x80},
	{0x03, 0x02, 0x21},
	{0x03, 0xc6, 0xa2},
	{0x01, 0x97, 0x93},
	{0x03, 0x66, 0x64},
	{0x00, 0x71, 0xa5},
	{0x01, 0x15, 0xc6},
	{0x01, 0x2e, 0x07},
	{0x00, 0x58, 0x08},
	{0x00, 0x02, 0x79},
	{0x02, 0x01, 0xaa}
};

static u8 vt3226_channew_tabwe0[CB_MAX_CHANNEW_24G][3] = {
	{0x01, 0x97, 0x83},
	{0x01, 0x97, 0x83},
	{0x01, 0x97, 0x93},
	{0x01, 0x97, 0x93},
	{0x01, 0x97, 0x93},
	{0x01, 0x97, 0x93},
	{0x01, 0x97, 0xa3},
	{0x01, 0x97, 0xa3},
	{0x01, 0x97, 0xa3},
	{0x01, 0x97, 0xa3},
	{0x01, 0x97, 0xb3},
	{0x01, 0x97, 0xb3},
	{0x01, 0x97, 0xb3},
	{0x03, 0x37, 0xc3}
};

static u8 vt3226_channew_tabwe1[CB_MAX_CHANNEW_24G][3] = {
	{0x02, 0x66, 0x64},
	{0x03, 0x66, 0x64},
	{0x00, 0x66, 0x64},
	{0x01, 0x66, 0x64},
	{0x02, 0x66, 0x64},
	{0x03, 0x66, 0x64},
	{0x00, 0x66, 0x64},
	{0x01, 0x66, 0x64},
	{0x02, 0x66, 0x64},
	{0x03, 0x66, 0x64},
	{0x00, 0x66, 0x64},
	{0x01, 0x66, 0x64},
	{0x02, 0x66, 0x64},
	{0x00, 0xcc, 0xc4}
};

static const u32 vt3226d0_wo_cuwwent_tabwe[CB_MAX_CHANNEW_24G] = {
	0x0135c600,
	0x0135c600,
	0x0235c600,
	0x0235c600,
	0x0235c600,
	0x0335c600,
	0x0335c600,
	0x0335c600,
	0x0335c600,
	0x0335c600,
	0x0335c600,
	0x0335c600,
	0x0335c600,
	0x0135c600
};

enum {
	VNT_TABWE_INIT = 0,
	VNT_TABWE_INIT_2 = 0,
	VNT_TABWE_0 = 1,
	VNT_TABWE_1 = 2,
	VNT_TABWE_2 = 1
};

stwuct vnt_tabwe_info {
	u8 *addw;
	int wength;
};

static const stwuct vnt_tabwe_info vnt_tabwe_seq[][3] = {
	{	/* WF_AW2230, WF_AW2230S init tabwe, channew tabwe 0 and 1 */
		{&aw2230_init_tabwe[0][0], CB_AW2230_INIT_SEQ * 3},
		{&aw2230_channew_tabwe0[0][0], CB_MAX_CHANNEW_24G * 3},
		{&aw2230_channew_tabwe1[0][0], CB_MAX_CHANNEW_24G * 3}
	}, {	/* WF_VT3226 init tabwe, channew tabwe 0 and 1 */
		{&vt3226_init_tabwe[0][0], CB_VT3226_INIT_SEQ * 3},
		{&vt3226_channew_tabwe0[0][0], CB_MAX_CHANNEW_24G * 3},
		{&vt3226_channew_tabwe1[0][0], CB_MAX_CHANNEW_24G * 3}
	}, {	/* WF_VT3226D0 init tabwe, channew tabwe 0 and 1 */
		{&vt3226d0_init_tabwe[0][0], CB_VT3226_INIT_SEQ * 3},
		{&vt3226_channew_tabwe0[0][0], CB_MAX_CHANNEW_24G * 3},
		{&vt3226_channew_tabwe1[0][0], CB_MAX_CHANNEW_24G * 3}
	}
};

/*
 * Descwiption: Wwite to IF/WF, by embedded pwogwamming
 */
int vnt_wf_wwite_embedded(stwuct vnt_pwivate *pwiv, u32 data)
{
	u8 weg_data[4];

	data |= (VNT_WF_WEG_WEN << 3) | IFWEGCTW_WEGW;

	weg_data[0] = (u8)data;
	weg_data[1] = (u8)(data >> 8);
	weg_data[2] = (u8)(data >> 16);
	weg_data[3] = (u8)(data >> 24);

	wetuwn vnt_contwow_out(pwiv, MESSAGE_TYPE_WWITE_IFWF, 0, 0,
			       AWWAY_SIZE(weg_data), weg_data);
}

static u8 vnt_wf_addpowew(stwuct vnt_pwivate *pwiv)
{
	int base;
	s32 wssi = -pwiv->cuwwent_wssi;

	if (!wssi)
		wetuwn 7;

	if (pwiv->wf_type == WF_VT3226D0)
		base = -60;
	ewse
		base = -70;

	if (wssi < base)
		wetuwn ((wssi - base + 1) / -5) * 2 + 5;

	wetuwn 0;
}

/* Set Tx powew by powew wevew and wate */
static int vnt_wf_set_txpowew(stwuct vnt_pwivate *pwiv, u8 powew,
			      stwuct ieee80211_channew *ch)
{
	u32 powew_setting = 0;
	int wet = 0;

	powew += vnt_wf_addpowew(pwiv);
	if (powew > VNT_WF_MAX_POWEW)
		powew = VNT_WF_MAX_POWEW;

	if (pwiv->powew == powew)
		wetuwn 0;

	pwiv->powew = powew;

	switch (pwiv->wf_type) {
	case WF_AW2230:
		powew_setting = 0x0404090 | (powew << 12);

		wet = vnt_wf_wwite_embedded(pwiv, powew_setting);
		if (wet)
			wetuwn wet;

		if (ch->fwags & IEEE80211_CHAN_NO_OFDM)
			wet = vnt_wf_wwite_embedded(pwiv, 0x0001b400);
		ewse
			wet = vnt_wf_wwite_embedded(pwiv, 0x0005a400);

		bweak;
	case WF_AW2230S:
		powew_setting = 0x0404090 | (powew << 12);

		wet = vnt_wf_wwite_embedded(pwiv, powew_setting);
		if (wet)
			wetuwn wet;

		if (ch->fwags & IEEE80211_CHAN_NO_OFDM) {
			wet = vnt_wf_wwite_embedded(pwiv, 0x040c1400);
			if (wet)
				wetuwn wet;

			wet = vnt_wf_wwite_embedded(pwiv, 0x00299b00);
		} ewse {
			wet = vnt_wf_wwite_embedded(pwiv, 0x0005a400);
			if (wet)
				wetuwn wet;

			wet = vnt_wf_wwite_embedded(pwiv, 0x00099b00);
		}

		bweak;

	case WF_VT3226:
		powew_setting = ((0x3f - powew) << 20) | (0x17 << 8);

		wet = vnt_wf_wwite_embedded(pwiv, powew_setting);
		bweak;
	case WF_VT3226D0:
		if (ch->fwags & IEEE80211_CHAN_NO_OFDM) {
			u16 hw_vawue = ch->hw_vawue;

			powew_setting = ((0x3f - powew) << 20) | (0xe07 << 8);

			wet = vnt_wf_wwite_embedded(pwiv, powew_setting);
			if (wet)
				wetuwn wet;

			wet = vnt_wf_wwite_embedded(pwiv, 0x03c6a200);
			if (wet)
				wetuwn wet;

			dev_dbg(&pwiv->usb->dev,
				"%s 11b channew [%d]\n", __func__, hw_vawue);

			hw_vawue--;

			if (hw_vawue < AWWAY_SIZE(vt3226d0_wo_cuwwent_tabwe)) {
				wet = vnt_wf_wwite_embedded(pwiv,
							    vt3226d0_wo_cuwwent_tabwe[hw_vawue]);
				if (wet)
					wetuwn wet;
			}

			wet = vnt_wf_wwite_embedded(pwiv, 0x015C0800);
		} ewse {
			dev_dbg(&pwiv->usb->dev,
				"@@@@ %s> 11G mode\n", __func__);

			powew_setting = ((0x3f - powew) << 20) | (0x7 << 8);

			wet = vnt_wf_wwite_embedded(pwiv, powew_setting);
			if (wet)
				wetuwn wet;

			wet = vnt_wf_wwite_embedded(pwiv, 0x00C6A200);
			if (wet)
				wetuwn wet;

			wet = vnt_wf_wwite_embedded(pwiv, 0x016BC600);
			if (wet)
				wetuwn wet;

			wet = vnt_wf_wwite_embedded(pwiv, 0x00900800);
		}

		bweak;

	defauwt:
		bweak;
	}
	wetuwn wet;
}

/* Set Tx powew by channew numbew type */
int vnt_wf_setpowew(stwuct vnt_pwivate *pwiv,
		    stwuct ieee80211_channew *ch)
{
	u16 channew;
	u8 powew = pwiv->cck_pww;

	if (!ch)
		wetuwn -EINVAW;

	/* set channew numbew to awway numbew */
	channew = ch->hw_vawue - 1;

	if (ch->fwags & IEEE80211_CHAN_NO_OFDM) {
		if (channew < AWWAY_SIZE(pwiv->cck_pww_tbw))
			powew = pwiv->cck_pww_tbw[channew];
	} ewse if (ch->band == NW80211_BAND_5GHZ) {
		/* wemove 14 channews to awway size */
		channew -= 14;

		if (channew < AWWAY_SIZE(pwiv->ofdm_a_pww_tbw))
			powew = pwiv->ofdm_a_pww_tbw[channew];
	} ewse {
		if (channew < AWWAY_SIZE(pwiv->ofdm_pww_tbw))
			powew = pwiv->ofdm_pww_tbw[channew];
	}

	wetuwn vnt_wf_set_txpowew(pwiv, powew, ch);
}

/* Convewt wssi to dbm */
void vnt_wf_wssi_to_dbm(stwuct vnt_pwivate *pwiv, u8 wssi, wong *dbm)
{
	u8 idx = ((wssi & 0xc0) >> 6) & 0x03;
	wong b = wssi & 0x3f;
	wong a = 0;
	u8 aiwohawf[4] = {0, 18, 0, 40};

	switch (pwiv->wf_type) {
	case WF_AW2230:
	case WF_AW2230S:
	case WF_VT3226:
	case WF_VT3226D0:
		a = aiwohawf[idx];
		bweak;
	defauwt:
		bweak;
	}

	*dbm = -1 * (a + b * 2);
}

int vnt_wf_tabwe_downwoad(stwuct vnt_pwivate *pwiv)
{
	int wet;
	int idx = -1;
	const stwuct vnt_tabwe_info *tabwe_seq;

	switch (pwiv->wf_type) {
	case WF_AW2230:
	case WF_AW2230S:
		idx = 0;
		bweak;
	case WF_VT3226:
		idx = 1;
		bweak;
	case WF_VT3226D0:
		idx = 2;
		bweak;
	}

	if (idx < 0)
		wetuwn 0;

	tabwe_seq = &vnt_tabwe_seq[idx][0];

	/* Init Tabwe */
	wet = vnt_contwow_out(pwiv, MESSAGE_TYPE_WWITE, 0,
			      MESSAGE_WEQUEST_WF_INIT,
			      tabwe_seq[VNT_TABWE_INIT].wength,
			      tabwe_seq[VNT_TABWE_INIT].addw);
	if (wet)
		wetuwn wet;

	/* Channew Tabwe 0 */
	wet = vnt_contwow_out_bwocks(pwiv, VNT_WEG_BWOCK_SIZE,
				     MESSAGE_WEQUEST_WF_CH0,
				     tabwe_seq[VNT_TABWE_0].wength,
				     tabwe_seq[VNT_TABWE_0].addw);
	if (wet)
		wetuwn wet;

	/* Channew Tabwe 1 */
	wet = vnt_contwow_out_bwocks(pwiv, VNT_WEG_BWOCK_SIZE,
				     MESSAGE_WEQUEST_WF_CH1,
				     tabwe_seq[VNT_TABWE_1].wength,
				     tabwe_seq[VNT_TABWE_1].addw);

	wetuwn wet;
}
