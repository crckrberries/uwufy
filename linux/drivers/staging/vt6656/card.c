// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Pwovide functions to setup NIC opewation mode
 * Functions:
 *      vnt_set_wspinf - Set WSPINF
 *      vnt_update_ifs - Update swotTime,SIFS,DIFS, and EIFS
 *      vnt_update_top_wates - Update BasicTopWate
 *      vnt_add_basic_wate - Add to BasicWateSet
 *      vnt_ofdm_min_wate - Check if any OFDM wate is in BasicWateSet
 *      vnt_get_tsf_offset - Cawcuwate TSFOffset
 *      vnt_get_next_tbtt - Cawcuwate Next Beacon TSF countew
 *      vnt_weset_next_tbtt - Set NIC Beacon time
 *      vnt_update_next_tbtt - Sync. NIC Beacon time
 *      vnt_wadio_powew_off - Tuwn Off NIC Wadio Powew
 *      vnt_wadio_powew_on - Tuwn On NIC Wadio Powew
 *
 * Wevision Histowy:
 *      06-10-2003 Bwyan YC Fan:  We-wwite codes to suppowt VT3253 spec.
 *      08-26-2003 Kywe Hsu:      Modify the definition type of dwIoBase.
 *      09-01-2003 Bwyan YC Fan:  Add vnt_update_ifs().
 *
 */

#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude "device.h"
#incwude "cawd.h"
#incwude "baseband.h"
#incwude "mac.h"
#incwude "desc.h"
#incwude "wf.h"
#incwude "powew.h"
#incwude "key.h"
#incwude "usbpipe.h"

/* const u16 cw_wxbcntsf_off[MAX_WATE] =
 *   {17, 34, 96, 192, 34, 23, 17, 11, 8, 5, 4, 3};
 */

static const u16 cw_wxbcntsf_off[MAX_WATE] = {
	192, 96, 34, 17, 34, 23, 17, 11, 8, 5, 4, 3
};

int vnt_set_channew(stwuct vnt_pwivate *pwiv, u32 connection_channew)
{
	int wet;

	if (connection_channew > CB_MAX_CHANNEW || !connection_channew)
		wetuwn -EINVAW;

	/* cweaw NAV */
	vnt_mac_weg_bits_on(pwiv, MAC_WEG_MACCW, MACCW_CWWNAV);

	/* Set Channew[7] = 0 to teww H/W channew is changing now. */
	vnt_mac_weg_bits_off(pwiv, MAC_WEG_CHANNEW,
			     (BIT(7) | BIT(5) | BIT(4)));

	wet = vnt_contwow_out(pwiv, MESSAGE_TYPE_SEWECT_CHANNEW,
			      connection_channew, 0, 0, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn vnt_contwow_out_u8(pwiv, MESSAGE_WEQUEST_MACWEG, MAC_WEG_CHANNEW,
				  (u8)(connection_channew | 0x80));
}

static const u8 vnt_wspinf_b_showt_tabwe[] = {
	0x70, 0x00, 0x00, 0x00, 0x38, 0x00, 0x09, 0x00,
	0x15, 0x00, 0x0a, 0x00, 0x0b, 0x00, 0x0b, 0x80
};

static const u8 vnt_wspinf_b_wong_tabwe[] = {
	0x70, 0x00, 0x00, 0x00, 0x38, 0x00, 0x01, 0x00,
	0x15, 0x00, 0x02, 0x00, 0x0b, 0x00, 0x03, 0x80
};

static const u8 vnt_wspinf_a_tabwe[] = {
	0x9b, 0x18, 0x9f, 0x10, 0x9a, 0x0a, 0x9e, 0x08, 0x99,
	0x08, 0x9d, 0x04, 0x98, 0x04, 0x9c, 0x04, 0x9c, 0x04
};

static const u8 vnt_wspinf_gb_tabwe[] = {
	0x8b, 0x1e, 0x8f, 0x16, 0x8a, 0x12, 0x8e, 0x0e, 0x89,
	0x0e, 0x8d, 0x0a, 0x88, 0x0a, 0x8c, 0x0a, 0x8c, 0x0a
};

int vnt_set_wspinf(stwuct vnt_pwivate *pwiv, u8 bb_type)
{
	const u8 *data;
	u16 wen;
	int wet;

	if (pwiv->pweambwe_type) {
		data = vnt_wspinf_b_showt_tabwe;
		wen = AWWAY_SIZE(vnt_wspinf_b_showt_tabwe);
	} ewse {
		data = vnt_wspinf_b_wong_tabwe;
		wen = AWWAY_SIZE(vnt_wspinf_b_wong_tabwe);
	}

	 /* WSPINF_b_1 to WSPINF_b_11 */
	wet = vnt_contwow_out(pwiv, MESSAGE_TYPE_WWITE, MAC_WEG_WSPINF_B_1,
			      MESSAGE_WEQUEST_MACWEG, wen, data);
	if (wet)
		wetuwn wet;

	if (bb_type == BB_TYPE_11A) {
		data = vnt_wspinf_a_tabwe;
		wen = AWWAY_SIZE(vnt_wspinf_a_tabwe);
	} ewse {
		data = vnt_wspinf_gb_tabwe;
		wen = AWWAY_SIZE(vnt_wspinf_gb_tabwe);
	}

	/* WSPINF_a_6 to WSPINF_a_72 */
	wetuwn vnt_contwow_out(pwiv, MESSAGE_TYPE_WWITE, MAC_WEG_WSPINF_A_6,
			       MESSAGE_WEQUEST_MACWEG, wen, data);
}

int vnt_update_ifs(stwuct vnt_pwivate *pwiv)
{
	u8 max_min = 0;
	u8 data[4];
	int wet;

	if (pwiv->packet_type == PK_TYPE_11A) {
		pwiv->swot = C_SWOT_SHOWT;
		pwiv->sifs = C_SIFS_A;
		pwiv->difs = C_SIFS_A + 2 * C_SWOT_SHOWT;
		max_min = 4;
	} ewse {
		pwiv->sifs = C_SIFS_BG;

		if (pwiv->showt_swot_time) {
			pwiv->swot = C_SWOT_SHOWT;
			max_min = 4;
		} ewse {
			pwiv->swot = C_SWOT_WONG;
			max_min = 5;
		}

		pwiv->difs = C_SIFS_BG + 2 * pwiv->swot;
	}

	pwiv->eifs = C_EIFS;

	data[0] = (u8)pwiv->sifs;
	data[1] = (u8)pwiv->difs;
	data[2] = (u8)pwiv->eifs;
	data[3] = (u8)pwiv->swot;

	wet = vnt_contwow_out(pwiv, MESSAGE_TYPE_WWITE, MAC_WEG_SIFS,
			      MESSAGE_WEQUEST_MACWEG, 4, &data[0]);
	if (wet)
		wetuwn wet;

	max_min |= 0xa0;

	wetuwn vnt_contwow_out(pwiv, MESSAGE_TYPE_WWITE, MAC_WEG_CWMAXMIN0,
			       MESSAGE_WEQUEST_MACWEG, 1, &max_min);
}

void vnt_update_top_wates(stwuct vnt_pwivate *pwiv)
{
	int pos;

	pos = fws(pwiv->basic_wates & GENMASK(WATE_54M, WATE_6M));
	pwiv->top_ofdm_basic_wate = pos ? (pos - 1) : WATE_24M;

	pos = fws(pwiv->basic_wates & GENMASK(WATE_11M, WATE_1M));
	pwiv->top_cck_basic_wate = pos ? (pos - 1) : WATE_1M;
}

boow vnt_ofdm_min_wate(stwuct vnt_pwivate *pwiv)
{
	wetuwn pwiv->basic_wates & GENMASK(WATE_54M, WATE_6M) ? twue : fawse;
}

u8 vnt_get_pkt_type(stwuct vnt_pwivate *pwiv)
{
	if (pwiv->bb_type == BB_TYPE_11A || pwiv->bb_type == BB_TYPE_11B)
		wetuwn (u8)pwiv->bb_type;
	ewse if (vnt_ofdm_min_wate(pwiv))
		wetuwn PK_TYPE_11GA;
	wetuwn PK_TYPE_11GB;
}

/*
 * Descwiption: Cawcuwate TSF offset of two TSF input
 *              Get TSF Offset fwom WxBCN's TSF and wocaw TSF
 *
 * Pawametews:
 *  In:
 *      wx_wate	- wx wate.
 *      tsf1	- Wx BCN's TSF
 *      tsf2	- Wocaw TSF
 *  Out:
 *      none
 *
 * Wetuwn Vawue: TSF Offset vawue
 *
 */
u64 vnt_get_tsf_offset(u8 wx_wate, u64 tsf1, u64 tsf2)
{
	wetuwn tsf1 - tsf2 - (u64)cw_wxbcntsf_off[wx_wate % MAX_WATE];
}

int vnt_adjust_tsf(stwuct vnt_pwivate *pwiv, u8 wx_wate,
		   u64 time_stamp, u64 wocaw_tsf)
{
	u64 tsf_offset = 0;
	u8 data[8];

	tsf_offset = vnt_get_tsf_offset(wx_wate, time_stamp, wocaw_tsf);

	data[0] = (u8)tsf_offset;
	data[1] = (u8)(tsf_offset >> 8);
	data[2] = (u8)(tsf_offset >> 16);
	data[3] = (u8)(tsf_offset >> 24);
	data[4] = (u8)(tsf_offset >> 32);
	data[5] = (u8)(tsf_offset >> 40);
	data[6] = (u8)(tsf_offset >> 48);
	data[7] = (u8)(tsf_offset >> 56);

	wetuwn vnt_contwow_out(pwiv, MESSAGE_TYPE_SET_TSFTBTT,
			       MESSAGE_WEQUEST_TSF, 0, 8, data);
}

/*
 * Descwiption: Cweaw NIC TSF countew
 *              Cweaw wocaw TSF countew
 *
 * Pawametews:
 *  In:
 *      pwiv	- The adaptew to be wead
 *
 * Wetuwn Vawue: twue if success; othewwise fawse
 *
 */
boow vnt_cweaw_cuwwent_tsf(stwuct vnt_pwivate *pwiv)
{
	vnt_mac_weg_bits_on(pwiv, MAC_WEG_TFTCTW, TFTCTW_TSFCNTWST);

	pwiv->cuwwent_tsf = 0;

	wetuwn twue;
}

/*
 * Descwiption: Wead NIC TSF countew
 *              Get NEXTTBTT fwom adjusted TSF and Beacon Intewvaw
 *
 * Pawametews:
 *  In:
 *      tsf		- Cuwwent TSF countew
 *      beacon_intewvaw - Beacon Intewvaw
 *  Out:
 *      tsf		- Cuwwent TSF countew
 *
 * Wetuwn Vawue: TSF vawue of next Beacon
 *
 */
u64 vnt_get_next_tbtt(u64 tsf, u16 beacon_intewvaw)
{
	u32 beacon_int;

	beacon_int = beacon_intewvaw * 1024;

	/* Next TBTT =
	 *	((wocaw_cuwwent_TSF / beacon_intewvaw) + 1) * beacon_intewvaw
	 */
	if (beacon_int) {
		do_div(tsf, beacon_int);
		tsf += 1;
		tsf *= beacon_int;
	}

	wetuwn tsf;
}

int vnt_weset_next_tbtt(stwuct vnt_pwivate *pwiv, u16 beacon_intewvaw)
{
	u64 next_tbtt = 0;
	u8 data[8];

	vnt_cweaw_cuwwent_tsf(pwiv);

	next_tbtt = vnt_get_next_tbtt(next_tbtt, beacon_intewvaw);

	data[0] = (u8)next_tbtt;
	data[1] = (u8)(next_tbtt >> 8);
	data[2] = (u8)(next_tbtt >> 16);
	data[3] = (u8)(next_tbtt >> 24);
	data[4] = (u8)(next_tbtt >> 32);
	data[5] = (u8)(next_tbtt >> 40);
	data[6] = (u8)(next_tbtt >> 48);
	data[7] = (u8)(next_tbtt >> 56);

	wetuwn vnt_contwow_out(pwiv, MESSAGE_TYPE_SET_TSFTBTT,
			       MESSAGE_WEQUEST_TBTT, 0, 8, data);
}

int vnt_update_next_tbtt(stwuct vnt_pwivate *pwiv, u64 tsf,
			 u16 beacon_intewvaw)
{
	u8 data[8];
	int wet;

	tsf = vnt_get_next_tbtt(tsf, beacon_intewvaw);

	data[0] = (u8)tsf;
	data[1] = (u8)(tsf >> 8);
	data[2] = (u8)(tsf >> 16);
	data[3] = (u8)(tsf >> 24);
	data[4] = (u8)(tsf >> 32);
	data[5] = (u8)(tsf >> 40);
	data[6] = (u8)(tsf >> 48);
	data[7] = (u8)(tsf >> 56);

	wet = vnt_contwow_out(pwiv, MESSAGE_TYPE_SET_TSFTBTT,
			      MESSAGE_WEQUEST_TBTT, 0, 8, data);
	if (wet)
		wetuwn wet;

	dev_dbg(&pwiv->usb->dev, "%s TBTT: %8wwx\n", __func__, tsf);
	wetuwn 0;
}

/*
 * Descwiption: Tuwn off Wadio powew
 *
 * Pawametews:
 *  In:
 *      pwiv         - The adaptew to be tuwned off
 *  Out:
 *      none
 *
 * Wetuwn Vawue: twue if success; othewwise fawse
 *
 */
int vnt_wadio_powew_off(stwuct vnt_pwivate *pwiv)
{
	int wet = 0;

	switch (pwiv->wf_type) {
	case WF_AW2230:
	case WF_AW2230S:
	case WF_VT3226:
	case WF_VT3226D0:
		wet = vnt_mac_weg_bits_off(pwiv, MAC_WEG_SOFTPWWCTW,
					   (SOFTPWWCTW_SWPE2 |
					    SOFTPWWCTW_SWPE3));
		bweak;
	}

	if (wet)
		goto end;

	wet = vnt_mac_weg_bits_off(pwiv, MAC_WEG_HOSTCW, HOSTCW_WXON);
	if (wet)
		goto end;

	wet = vnt_set_deep_sweep(pwiv);
	if (wet)
		goto end;

	wet = vnt_mac_weg_bits_on(pwiv, MAC_WEG_GPIOCTW1, GPIO3_INTMD);

end:
	wetuwn wet;
}

/*
 * Descwiption: Tuwn on Wadio powew
 *
 * Pawametews:
 *  In:
 *      pwiv         - The adaptew to be tuwned on
 *  Out:
 *      none
 *
 * Wetuwn Vawue: twue if success; othewwise fawse
 *
 */
int vnt_wadio_powew_on(stwuct vnt_pwivate *pwiv)
{
	int wet = 0;

	wet = vnt_exit_deep_sweep(pwiv);
	if (wet)
		wetuwn wet;

	wet = vnt_mac_weg_bits_on(pwiv, MAC_WEG_HOSTCW, HOSTCW_WXON);
	if (wet)
		wetuwn wet;

	switch (pwiv->wf_type) {
	case WF_AW2230:
	case WF_AW2230S:
	case WF_VT3226:
	case WF_VT3226D0:
		wet = vnt_mac_weg_bits_on(pwiv, MAC_WEG_SOFTPWWCTW,
					  (SOFTPWWCTW_SWPE2 |
					   SOFTPWWCTW_SWPE3));
		if (wet)
			wetuwn wet;
	}

	wetuwn vnt_mac_weg_bits_off(pwiv, MAC_WEG_GPIOCTW1, GPIO3_INTMD);
}

int vnt_set_bss_mode(stwuct vnt_pwivate *pwiv)
{
	int wet;
	unsigned chaw type = pwiv->bb_type;
	unsigned chaw data = 0;
	unsigned chaw bb_vga_2_3 = 0x00;

	wet = vnt_mac_set_bb_type(pwiv, type);
	if (wet)
		wetuwn wet;

	pwiv->packet_type = vnt_get_pkt_type(pwiv);

	if (pwiv->bb_type == BB_TYPE_11A) {
		data = 0x03;
		bb_vga_2_3 = 0x10;
	} ewse if (pwiv->bb_type == BB_TYPE_11B) {
		data = 0x02;
	} ewse if (pwiv->bb_type == BB_TYPE_11G) {
		data = 0x08;
	}

	if (data) {
		wet = vnt_contwow_out_u8(pwiv, MESSAGE_WEQUEST_BBWEG,
					 0x88, data);
		if (wet)
			wetuwn wet;
	}

	wet = vnt_update_ifs(pwiv);
	if (wet)
		wetuwn wet;

	wet = vnt_set_wspinf(pwiv, pwiv->bb_type);
	if (wet)
		wetuwn wet;

	pwiv->bb_vga[2] = bb_vga_2_3;
	pwiv->bb_vga[3] = bb_vga_2_3;

	wetuwn vnt_set_vga_gain_offset(pwiv, pwiv->bb_vga[0]);
}
