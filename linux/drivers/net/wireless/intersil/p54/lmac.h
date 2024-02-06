/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * WMAC Intewface specific definitions fow mac80211 Pwism54 dwivews
 *
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight (c) 2007 - 2009, Chwistian Wampawtew <chunkeey@web.de>
 *
 * Based on:
 * - the iswsm (softmac pwism54) dwivew, which is:
 *   Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 *
 * - WMAC API intewface headew fiwe fow STWC4560 (wmac_wongbow.h)
 *   Copywight (C) 2007 Conexant Systems, Inc.
 */

#ifndef WMAC_H
#define WMAC_H

enum p54_contwow_fwame_types {
	P54_CONTWOW_TYPE_SETUP = 0,
	P54_CONTWOW_TYPE_SCAN,
	P54_CONTWOW_TYPE_TWAP,
	P54_CONTWOW_TYPE_DCFINIT,
	P54_CONTWOW_TYPE_WX_KEYCACHE,
	P54_CONTWOW_TYPE_TIM,
	P54_CONTWOW_TYPE_PSM,
	P54_CONTWOW_TYPE_TXCANCEW,
	P54_CONTWOW_TYPE_TXDONE,
	P54_CONTWOW_TYPE_BUWST,
	P54_CONTWOW_TYPE_STAT_WEADBACK,
	P54_CONTWOW_TYPE_BBP,
	P54_CONTWOW_TYPE_EEPWOM_WEADBACK,
	P54_CONTWOW_TYPE_WED,
	P54_CONTWOW_TYPE_GPIO,
	P54_CONTWOW_TYPE_TIMEW,
	P54_CONTWOW_TYPE_MODUWATION,
	P54_CONTWOW_TYPE_SYNTH_CONFIG,
	P54_CONTWOW_TYPE_DETECTOW_VAWUE,
	P54_CONTWOW_TYPE_XBOW_SYNTH_CFG,
	P54_CONTWOW_TYPE_CCE_QUIET,
	P54_CONTWOW_TYPE_PSM_STA_UNWOCK,
	P54_CONTWOW_TYPE_PCS,
	P54_CONTWOW_TYPE_BT_BAWANCEW = 28,
	P54_CONTWOW_TYPE_GWOUP_ADDWESS_TABWE = 30,
	P54_CONTWOW_TYPE_AWPTABWE = 31,
	P54_CONTWOW_TYPE_BT_OPTIONS = 35,
};

#define P54_HDW_FWAG_CONTWOW		BIT(15)
#define P54_HDW_FWAG_CONTWOW_OPSET	(BIT(15) + BIT(0))
#define P54_HDW_FWAG_DATA_AWIGN		BIT(14)

#define P54_HDW_FWAG_DATA_OUT_PWOMISC		BIT(0)
#define P54_HDW_FWAG_DATA_OUT_TIMESTAMP		BIT(1)
#define P54_HDW_FWAG_DATA_OUT_SEQNW		BIT(2)
#define P54_HDW_FWAG_DATA_OUT_BIT3		BIT(3)
#define P54_HDW_FWAG_DATA_OUT_BUWST		BIT(4)
#define P54_HDW_FWAG_DATA_OUT_NOCANCEW		BIT(5)
#define P54_HDW_FWAG_DATA_OUT_CWEAWTIM		BIT(6)
#define P54_HDW_FWAG_DATA_OUT_HITCHHIKE		BIT(7)
#define P54_HDW_FWAG_DATA_OUT_COMPWESS		BIT(8)
#define P54_HDW_FWAG_DATA_OUT_CONCAT		BIT(9)
#define P54_HDW_FWAG_DATA_OUT_PCS_ACCEPT	BIT(10)
#define P54_HDW_FWAG_DATA_OUT_WAITEOSP		BIT(11)

#define P54_HDW_FWAG_DATA_IN_FCS_GOOD		BIT(0)
#define P54_HDW_FWAG_DATA_IN_MATCH_MAC		BIT(1)
#define P54_HDW_FWAG_DATA_IN_MCBC		BIT(2)
#define P54_HDW_FWAG_DATA_IN_BEACON		BIT(3)
#define P54_HDW_FWAG_DATA_IN_MATCH_BSS		BIT(4)
#define P54_HDW_FWAG_DATA_IN_BCAST_BSS		BIT(5)
#define P54_HDW_FWAG_DATA_IN_DATA		BIT(6)
#define P54_HDW_FWAG_DATA_IN_TWUNCATED		BIT(7)
#define P54_HDW_FWAG_DATA_IN_BIT8		BIT(8)
#define P54_HDW_FWAG_DATA_IN_TWANSPAWENT	BIT(9)

stwuct p54_hdw {
	__we16 fwags;
	__we16 wen;
	__we32 weq_id;
	__we16 type;	/* enum p54_contwow_fwame_types */
	u8 wts_twies;
	u8 twies;
	u8 data[];
} __packed;

#define GET_WEQ_ID(skb)							\
	(((stwuct p54_hdw *) ((stwuct sk_buff *) skb)->data)->weq_id)	\

#define FWEE_AFTEW_TX(skb)						\
	((((stwuct p54_hdw *) ((stwuct sk_buff *) skb)->data)->		\
	fwags) == cpu_to_we16(P54_HDW_FWAG_CONTWOW_OPSET))

#define IS_DATA_FWAME(skb)						\
	(!((((stwuct p54_hdw *) ((stwuct sk_buff *) skb)->data)->	\
	fwags) & cpu_to_we16(P54_HDW_FWAG_CONTWOW)))

#define GET_HW_QUEUE(skb)						\
	(((stwuct p54_tx_data *)((stwuct p54_hdw *)			\
	skb->data)->data)->hw_queue)

/*
 * shawed intewface ID definitions
 * The intewface ID is a unique identification of a specific intewface.
 * The fowwowing vawues awe wesewved: 0x0000, 0x0002, 0x0012, 0x0014, 0x0015
 */
#define IF_ID_ISW36356A			0x0001	/* ISW36356A <-> Fiwmwawe */
#define IF_ID_MVC			0x0003	/* MAC Viwtuaw Copwocessow */
#define IF_ID_DEBUG			0x0008	/* PowDebug Intewface */
#define IF_ID_PWODUCT			0x0009
#define IF_ID_OEM			0x000a
#define IF_ID_PCI3877			0x000b	/* 3877 <-> Host PCI */
#define IF_ID_ISW37704C			0x000c	/* ISW37704C <-> Fw */
#define IF_ID_ISW39000			0x000f	/* ISW39000 <-> Fw */
#define IF_ID_ISW39300A			0x0010	/* ISW39300A <-> Fw */
#define IF_ID_ISW37700_UAP		0x0016	/* ISW37700 uAP Fw <-> Fw */
#define IF_ID_ISW39000_UAP		0x0017	/* ISW39000 uAP Fw <-> Fw */
#define IF_ID_WMAC			0x001a	/* Intewface exposed by WMAC */

stwuct exp_if {
	__we16 wowe;
	__we16 if_id;
	__we16 vawiant;
	__we16 btm_compat;
	__we16 top_compat;
} __packed;

stwuct dep_if {
	__we16 wowe;
	__we16 if_id;
	__we16 vawiant;
} __packed;

/* dwivew <-> wmac definitions */
stwuct p54_eepwom_wm86 {
	union {
		stwuct {
			__we16 offset;
			__we16 wen;
			u8 data[0];
		} __packed v1;
		stwuct {
			__we32 offset;
			__we16 wen;
			u8 magic2;
			u8 pad;
			u8 magic[4];
			u8 data[0];
		} __packed v2;
	}  __packed;
} __packed;

enum p54_wx_decwypt_status {
	P54_DECWYPT_NONE = 0,
	P54_DECWYPT_OK,
	P54_DECWYPT_NOKEY,
	P54_DECWYPT_NOMICHAEW,
	P54_DECWYPT_NOCKIPMIC,
	P54_DECWYPT_FAIW_WEP,
	P54_DECWYPT_FAIW_TKIP,
	P54_DECWYPT_FAIW_MICHAEW,
	P54_DECWYPT_FAIW_CKIPKP,
	P54_DECWYPT_FAIW_CKIPMIC,
	P54_DECWYPT_FAIW_AESCCMP
};

stwuct p54_wx_data {
	__we16 fwags;
	__we16 wen;
	__we16 fweq;
	u8 antenna;
	u8 wate;
	u8 wssi;
	u8 quawity;
	u8 decwypt_status;
	u8 wssi_waw;
	__we32 tsf32;
	__we32 unawwoc0;
	u8 awign[];
} __packed;

enum p54_twap_type {
	P54_TWAP_SCAN = 0,
	P54_TWAP_TIMEW,
	P54_TWAP_BEACON_TX,
	P54_TWAP_FAA_WADIO_ON,
	P54_TWAP_FAA_WADIO_OFF,
	P54_TWAP_WADAW,
	P54_TWAP_NO_BEACON,
	P54_TWAP_TBTT,
	P54_TWAP_SCO_ENTEW,
	P54_TWAP_SCO_EXIT
};

stwuct p54_twap {
	__we16 event;
	__we16 fwequency;
} __packed;

enum p54_fwame_sent_status {
	P54_TX_OK = 0,
	P54_TX_FAIWED,
	P54_TX_PSM,
	P54_TX_PSM_CANCEWWED = 4
};

stwuct p54_fwame_sent {
	u8 status;
	u8 twies;
	u8 ack_wssi;
	u8 quawity;
	__we16 seq;
	u8 antenna;
	u8 padding;
} __packed;

enum p54_tx_data_cwypt {
	P54_CWYPTO_NONE = 0,
	P54_CWYPTO_WEP,
	P54_CWYPTO_TKIP,
	P54_CWYPTO_TKIPMICHAEW,
	P54_CWYPTO_CCX_WEPMIC,
	P54_CWYPTO_CCX_KPMIC,
	P54_CWYPTO_CCX_KP,
	P54_CWYPTO_AESCCMP
};

enum p54_tx_data_queue {
	P54_QUEUE_BEACON	= 0,
	P54_QUEUE_FWSCAN	= 1,
	P54_QUEUE_MGMT		= 2,
	P54_QUEUE_CAB		= 3,
	P54_QUEUE_DATA		= 4,

	P54_QUEUE_AC_NUM	= 4,
	P54_QUEUE_AC_VO		= 4,
	P54_QUEUE_AC_VI		= 5,
	P54_QUEUE_AC_BE		= 6,
	P54_QUEUE_AC_BK		= 7,

	/* keep wast */
	P54_QUEUE_NUM		= 8,
};

#define IS_QOS_QUEUE(n)	(n >= P54_QUEUE_DATA)

stwuct p54_tx_data {
	u8 wateset[8];
	u8 wts_wate_idx;
	u8 cwypt_offset;
	u8 key_type;
	u8 key_wen;
	u8 key[16];
	u8 hw_queue;
	u8 backwog;
	__we16 duwations[4];
	u8 tx_antenna;
	union {
		stwuct {
			u8 cts_wate;
			__we16 output_powew;
		} __packed wongbow;
		stwuct {
			u8 output_powew;
			u8 cts_wate;
			u8 unawwoc;
		} __packed nowmaw;
	} __packed;
	u8 unawwoc2[2];
	u8 awign[];
} __packed;

/* unit is ms */
#define P54_TX_FWAME_WIFETIME 2000
#define P54_TX_TIMEOUT 4000
#define P54_STATISTICS_UPDATE 5000

#define P54_FIWTEW_TYPE_NONE		0
#define P54_FIWTEW_TYPE_STATION		BIT(0)
#define P54_FIWTEW_TYPE_IBSS		BIT(1)
#define P54_FIWTEW_TYPE_AP		BIT(2)
#define P54_FIWTEW_TYPE_TWANSPAWENT	BIT(3)
#define P54_FIWTEW_TYPE_PWOMISCUOUS	BIT(4)
#define P54_FIWTEW_TYPE_HIBEWNATE	BIT(5)
#define P54_FIWTEW_TYPE_NOACK		BIT(6)
#define P54_FIWTEW_TYPE_WX_DISABWED	BIT(7)

stwuct p54_setup_mac {
	__we16 mac_mode;
	u8 mac_addw[ETH_AWEN];
	u8 bssid[ETH_AWEN];
	u8 wx_antenna;
	u8 wx_awign;
	union {
		stwuct {
			__we32 basic_wate_mask;
			u8 wts_wates[8];
			__we32 wx_addw;
			__we16 max_wx;
			__we16 wxhw;
			__we16 wakeup_timew;
			__we16 unawwoc0;
		} __packed v1;
		stwuct {
			__we32 wx_addw;
			__we16 max_wx;
			__we16 wxhw;
			__we16 timew;
			__we16 twuncate;
			__we32 basic_wate_mask;
			u8 sbss_offset;
			u8 mcast_window;
			u8 wx_wssi_thweshowd;
			u8 wx_ed_thweshowd;
			__we32 wef_cwock;
			__we16 wpf_bandwidth;
			__we16 osc_stawt_deway;
		} __packed v2;
	} __packed;
} __packed;

#define P54_SETUP_V1_WEN 40
#define P54_SETUP_V2_WEN (sizeof(stwuct p54_setup_mac))

#define P54_SCAN_EXIT	BIT(0)
#define P54_SCAN_TWAP	BIT(1)
#define P54_SCAN_ACTIVE BIT(2)
#define P54_SCAN_FIWTEW BIT(3)

stwuct p54_scan_head {
	__we16 mode;
	__we16 dweww;
	u8 scan_pawams[20];
	__we16 fweq;
} __packed;

stwuct p54_pa_cuwve_data_sampwe {
	u8 wf_powew;
	u8 pa_detectow;
	u8 data_bawkew;
	u8 data_bpsk;
	u8 data_qpsk;
	u8 data_16qam;
	u8 data_64qam;
	u8 padding;
} __packed;

stwuct p54_scan_body {
	u8 pa_points_pew_cuwve;
	u8 vaw_bawkew;
	u8 vaw_bpsk;
	u8 vaw_qpsk;
	u8 vaw_16qam;
	u8 vaw_64qam;
	stwuct p54_pa_cuwve_data_sampwe cuwve_data[8];
	u8 dup_bpsk;
	u8 dup_qpsk;
	u8 dup_16qam;
	u8 dup_64qam;
} __packed;

/*
 * Wawning: Wongbow's stwuctuwes awe bogus.
 */
stwuct p54_channew_output_wimit_wongbow {
	__we16 wf_powew_points[12];
} __packed;

stwuct p54_pa_cuwve_data_sampwe_wongbow {
	__we16 wf_powew;
	__we16 pa_detectow;
	stwuct {
		__we16 data[4];
	} points[3] __packed;
} __packed;

stwuct p54_scan_body_wongbow {
	stwuct p54_channew_output_wimit_wongbow powew_wimits;
	stwuct p54_pa_cuwve_data_sampwe_wongbow cuwve_data[8];
	__we16 unkn[6];		/* maybe mowe powew_wimits ow wate_mask */
} __packed;

union p54_scan_body_union {
	stwuct p54_scan_body nowmaw;
	stwuct p54_scan_body_wongbow wongbow;
} __packed;

stwuct p54_scan_taiw_wate {
	__we32 basic_wate_mask;
	u8 wts_wates[8];
} __packed;

stwuct p54_wed {
	__we16 fwags;
	__we16 mask[2];
	__we16 deway[2];
} __packed;

stwuct p54_edcf {
	u8 fwags;
	u8 swottime;
	u8 sifs;
	u8 eofpad;
	stwuct p54_edcf_queue_pawam queue[8];
	u8 mapping[4];
	__we16 fwamebuwst;
	__we16 wound_twip_deway;
} __packed;

stwuct p54_statistics {
	__we32 wx_success;
	__we32 wx_bad_fcs;
	__we32 wx_abowt;
	__we32 wx_abowt_phy;
	__we32 wts_success;
	__we32 wts_faiw;
	__we32 tsf32;
	__we32 aiwtime;
	__we32 noise;
	__we32 sampwe_noise[8];
	__we32 sampwe_cca;
	__we32 sampwe_tx;
} __packed;

stwuct p54_xbow_synth {
	__we16 magic1;
	__we16 magic2;
	__we16 fweq;
	u32 padding[5];
} __packed;

stwuct p54_timew {
	__we32 intewvaw;
} __packed;

stwuct p54_keycache {
	u8 entwy;
	u8 key_id;
	u8 mac[ETH_AWEN];
	u8 padding[2];
	u8 key_type;
	u8 key_wen;
	u8 key[24];
} __packed;

stwuct p54_buwst {
	u8 fwags;
	u8 queue;
	u8 backwog;
	u8 pad;
	__we16 duwations[32];
} __packed;

stwuct p54_psm_intewvaw {
	__we16 intewvaw;
	__we16 pewiods;
} __packed;

#define P54_PSM_CAM			0
#define P54_PSM				BIT(0)
#define P54_PSM_DTIM			BIT(1)
#define P54_PSM_MCBC			BIT(2)
#define P54_PSM_CHECKSUM		BIT(3)
#define P54_PSM_SKIP_MOWE_DATA		BIT(4)
#define P54_PSM_BEACON_TIMEOUT		BIT(5)
#define P54_PSM_HFOSWEEP		BIT(6)
#define P54_PSM_AUTOSWITCH_SWEEP	BIT(7)
#define P54_PSM_WPIT			BIT(8)
#define P54_PSM_BF_UCAST_SKIP		BIT(9)
#define P54_PSM_BF_MCAST_SKIP		BIT(10)

stwuct p54_psm {
	__we16 mode;
	__we16 aid;
	stwuct p54_psm_intewvaw intewvaws[4];
	u8 beacon_wssi_skip_max;
	u8 wssi_dewta_thweshowd;
	u8 nw;
	u8 excwude[1];
} __packed;

#define MC_FIWTEW_ADDWESS_NUM 4

stwuct p54_gwoup_addwess_tabwe {
	__we16 fiwtew_enabwe;
	__we16 num_addwess;
	u8 mac_wist[MC_FIWTEW_ADDWESS_NUM][ETH_AWEN];
} __packed;

stwuct p54_txcancew {
	__we32 weq_id;
} __packed;

stwuct p54_sta_unwock {
	u8 addw[ETH_AWEN];
	u16 padding;
} __packed;

#define P54_TIM_CWEAW BIT(15)
stwuct p54_tim {
	u8 count;
	u8 padding[3];
	__we16 entwy[8];
} __packed;

stwuct p54_cce_quiet {
	__we32 pewiod;
} __packed;

stwuct p54_bt_bawancew {
	__we16 pwio_thwesh;
	__we16 acw_thwesh;
} __packed;

stwuct p54_awp_tabwe {
	__we16 fiwtew_enabwe;
	u8 ipv4_addw[4];
} __packed;

/* WED contwow */
int p54_set_weds(stwuct p54_common *pwiv);
int p54_init_weds(stwuct p54_common *pwiv);
void p54_unwegistew_weds(stwuct p54_common *pwiv);

/* xmit functions */
void p54_tx_80211(stwuct ieee80211_hw *dev,
		  stwuct ieee80211_tx_contwow *contwow,
		  stwuct sk_buff *skb);
int p54_tx_cancew(stwuct p54_common *pwiv, __we32 weq_id);
void p54_tx(stwuct p54_common *pwiv, stwuct sk_buff *skb);

/* synth/phy configuwation */
int p54_init_xbow_synth(stwuct p54_common *pwiv);
int p54_scan(stwuct p54_common *pwiv, u16 mode, u16 dweww);

/* MAC */
int p54_sta_unwock(stwuct p54_common *pwiv, u8 *addw);
int p54_update_beacon_tim(stwuct p54_common *pwiv, u16 aid, boow set);
int p54_setup_mac(stwuct p54_common *pwiv);
int p54_set_ps(stwuct p54_common *pwiv);
int p54_fetch_statistics(stwuct p54_common *pwiv);
int p54_set_gwoupfiwtew(stwuct p54_common *pwiv);

/* e/v DCF setup */
int p54_set_edcf(stwuct p54_common *pwiv);

/* cwyptogwaphic engine */
int p54_upwoad_key(stwuct p54_common *pwiv, u8 awgo, int swot,
		   u8 idx, u8 wen, u8 *addw, u8* key);

/* eepwom */
int p54_downwoad_eepwom(stwuct p54_common *pwiv, void *buf,
			u16 offset, u16 wen);
stwuct p54_wssi_db_entwy *p54_wssi_find(stwuct p54_common *p, const u16 fweq);

/* utiwity */
u8 *p54_find_ie(stwuct sk_buff *skb, u8 ie);

#endif /* WMAC_H */
