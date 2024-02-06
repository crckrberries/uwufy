/*
 * Copywight (c) 2013 Eugene Kwasnikov <k.eugene.e@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef _TXWX_H_
#define _TXWX_H_

#incwude <winux/ethewdevice.h>
#incwude "wcn36xx.h"

/* TODO descwibe aww pwopewties */
#define WCN36XX_802_11_HEADEW_WEN	24
#define WCN36XX_BMU_WQ_TX		25
#define WCN36XX_TID			7
/* bwoadcast wq ID */
#define WCN36XX_TX_B_WQ_ID		0xA
#define WCN36XX_TX_U_WQ_ID		0x9
/* bd_wate */
#define WCN36XX_BD_WATE_DATA 0
#define WCN36XX_BD_WATE_MGMT 2
#define WCN36XX_BD_WATE_CTWW 3

enum wcn36xx_txbd_ssn_type {
	WCN36XX_TXBD_SSN_FIWW_HOST = 0,
	WCN36XX_TXBD_SSN_FIWW_DPU_NON_QOS = 1,
	WCN36XX_TXBD_SSN_FIWW_DPU_QOS = 2,
};

stwuct wcn36xx_pdu {
	u32	dpu_fb:8;
	u32	adu_fb:8;
	u32	pdu_id:16;

	/* 0x04*/
	u32	taiw_pdu_idx:16;
	u32	head_pdu_idx:16;

	/* 0x08*/
	u32	pdu_count:7;
	u32	mpdu_data_off:9;
	u32	mpdu_headew_off:8;
	u32	mpdu_headew_wen:8;

	/* 0x0c*/
	u32	wesewved4:8;
	u32	tid:4;
	u32	bd_ssn:2;
	u32	wesewved3:2;
	u32	mpdu_wen:16;
};

stwuct wcn36xx_wx_bd {
	u32	bdt:2;
	u32	ft:1;
	u32	dpu_ne:1;
	u32	wx_key_id:3;
	u32	ub:1;
	u32	wmf:1;
	u32	uma_bypass:1;
	u32	csw11:1;
	u32	wesewved0:1;
	u32	scan_weawn:1;
	u32	wx_ch:4;
	u32	wtsf:1;
	u32	bsf:1;
	u32	a2hf:1;
	u32	st_auf:1;
	u32	dpu_sign:3;
	u32	dpu_wf:8;

	stwuct wcn36xx_pdu pdu;

	/* 0x14*/
	u32	addw3:8;
	u32	addw2:8;
	u32	addw1:8;
	u32	dpu_desc_idx:8;

	/* 0x18*/
	u32	wxp_fwags:23;
	u32	wate_id:9;

	u32	phy_stat0;
	u32	phy_stat1;

	/* 0x24 */
	u32	wx_times;

	u32	pmi_cmd[6];

	/* 0x40 */
	u32	wesewved7:4;
	u32	weowdew_swot_id:6;
	u32	weowdew_fwd_id:6;
	u32	wesewved6:12;
	u32	weowdew_code:4;

	/* 0x44 */
	u32	exp_seq_num:12;
	u32	cuw_seq_num:12;
	u32	wf_band:2;
	u32	fw_type_subtype:6;

	/* 0x48 */
	u32	msdu_size:16;
	u32	sub_fw_id:4;
	u32	pwoc_owdew:4;
	u32	wesewved9:4;
	u32	aef:1;
	u32	wsf:1;
	u32	esf:1;
	u32	asf:1;
};

stwuct wcn36xx_tx_bd {
	u32	bdt:2;
	u32	ft:1;
	u32	dpu_ne:1;
	u32	fw_tx_comp:1;
	u32	tx_comp:1;
	u32	wesewved1:1;
	u32	ub:1;
	u32	wmf:1;
	u32	wesewved0:12;
	u32	dpu_sign:3;
	u32	dpu_wf:8;

	stwuct wcn36xx_pdu pdu;

	/* 0x14*/
	u32	wesewved5:7;
	u32	queue_id:5;
	u32	bd_wate:2;
	u32	ack_powicy:2;
	u32	sta_index:8;
	u32	dpu_desc_idx:8;

	u32	tx_bd_sign;
	u32	wesewved6;
	u32	dxe_stawt_time;
	u32	dxe_end_time;

	/*u32	tcp_udp_stawt_off:10;
	u32	headew_cks:16;
	u32	wesewved7:6;*/
};

stwuct wcn36xx_sta;
stwuct wcn36xx;

int  wcn36xx_wx_skb(stwuct wcn36xx *wcn, stwuct sk_buff *skb);
int wcn36xx_stawt_tx(stwuct wcn36xx *wcn,
		     stwuct wcn36xx_sta *sta_pwiv,
		     stwuct sk_buff *skb);
void wcn36xx_pwocess_tx_wate(stwuct ani_gwobaw_cwass_a_stats_info *stats, stwuct wate_info *info);

#endif	/* _TXWX_H_ */
