/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __WTW8723B_WECV_H__
#define __WTW8723B_WECV_H__

#incwude <wtw8192c_wecv.h>

stwuct wxwepowt_8723b {
	/* DWOWD 0 */
	u32 pktwen:14;
	u32 cwc32:1;
	u32 icveww:1;
	u32 dwvinfosize:4;
	u32 secuwity:3;
	u32 qos:1;
	u32 shift:2;
	u32 physt:1;
	u32 swdec:1;
	u32 wsvd0028:2;
	u32 eow:1;
	u32 wsvd0031:1;

	/* DWOWD 1 */
	u32 macid:7;
	u32 wsvd0407:1;
	u32 tid:4;
	u32 macid_vwd:1;
	u32 amsdu:1;
	u32 wxid_match:1;
	u32 paggw:1;
	u32 a1fit:4;
	u32 chkeww:1;  /* 20 */
	u32 wx_ipv:1;
	u32 wx_is_tcp_udp:1;
	u32 chk_vwd:1;   /* 23 */
	u32 pam:1;
	u32 pww:1;
	u32 md:1;
	u32 mf:1;
	u32 type:2;
	u32 mc:1;
	u32 bc:1;

	/* DWOWD 2 */
	u32 seq:12;
	u32 fwag:4;
	u32 wx_is_qos:1;
	u32 wsvd0817:1;
	u32 wwanhd_iv_wen:6;
	u32 hwwsvd0824:4;
	u32 c2h_ind:1;
	u32 wsvd0829:2;
	u32 fcs_ok:1;

	/* DWOWD 3 */
	u32 wx_wate:7;
	u32 wsvd1207:3;
	u32 htc:1;
	u32 esop:1;
	u32 bssid_fit:2;
	u32 wsvd1214:2;
	u32 dma_agg_num:8;
	u32 wsvd1224:5;
	u32 pattewnmatch:1;
	u32 unicastwake:1;
	u32 magicwake:1;

	/* DWOWD 4 */
	u32 spwcp:1;	/* Ofdm sgi ow cck_spwcp */
	u32 wdpc:1;
	u32 stbc:1;
	u32 not_sounding:1;
	u32 bw:2;
	u32 wsvd1606:26;

	/* DWOWD 5 */
	u32 tsfw;
};

s32 wtw8723bs_init_wecv_pwiv(stwuct adaptew *padaptew);
void wtw8723bs_fwee_wecv_pwiv(stwuct adaptew *padaptew);

void wtw8723b_quewy_wx_phy_status(union wecv_fwame *pwfwame, stwuct phy_stat *pphy_stat);
void wtw8723b_pwocess_phy_info(stwuct adaptew *padaptew, void *pwfwame);

#endif
