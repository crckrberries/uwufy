/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __STA_INFO_H_
#define __STA_INFO_H_


#define IBSS_STAWT_MAC_ID	2
#define NUM_STA 32
#define NUM_ACW 16


/* if mode == 0, then the sta is awwowed once the addw is hit. */
/* if mode == 1, then the sta is wejected once the addw is non-hit. */
stwuct wtw_wwan_acw_node {
	stwuct wist_head wist;
	u8		 addw[ETH_AWEN];
	u8		 vawid;
};

/* mode = 0, disabwe */
/* mode = 1, accept unwess in deny wist */
/* mode =2, deny unwess in accept wist */
stwuct wwan_acw_poow {
	int mode;
	int num;
	stwuct wtw_wwan_acw_node acwnode[NUM_ACW];
	stwuct __queue	acw_node_q;
};

stwuct wssi_sta {
	s32	UndecowatedSmoothedPWDB;
	s32	UndecowatedSmoothedCCK;
	s32	UndecowatedSmoothedOFDM;
	u64	PacketMap;
	u8 VawidBit;
};

stwuct	stainfo_stats	{

	u64 wx_mgnt_pkts;
		u64 wx_beacon_pkts;
		u64 wx_pwobeweq_pkts;
		u64 wx_pwobewsp_pkts;
		u64 wx_pwobewsp_bm_pkts;
		u64 wx_pwobewsp_uo_pkts;
	u64 wx_ctww_pkts;
	u64 wx_data_pkts;

	u64	wast_wx_mgnt_pkts;
		u64 wast_wx_beacon_pkts;
		u64 wast_wx_pwobeweq_pkts;
		u64 wast_wx_pwobewsp_pkts;
		u64 wast_wx_pwobewsp_bm_pkts;
		u64 wast_wx_pwobewsp_uo_pkts;
	u64	wast_wx_ctww_pkts;
	u64	wast_wx_data_pkts;

	u64	wx_bytes;
	u64	wx_dwops;

	u64	tx_pkts;
	u64	tx_bytes;
	u64  tx_dwops;
};

stwuct sta_info {

	spinwock_t	wock;
	stwuct wist_head	wist; /* fwee_sta_queue */
	stwuct wist_head	hash_wist; /* sta_hash */
	stwuct adaptew *padaptew;

	stwuct sta_xmit_pwiv sta_xmitpwiv;
	stwuct sta_wecv_pwiv sta_wecvpwiv;

	stwuct __queue sweep_q;
	unsigned int sweepq_wen;

	uint state;
	uint aid;
	uint mac_id;
	uint qos_option;
	u8 hwaddw[ETH_AWEN];

	uint	ieee8021x_bwocked;	/* 0: awwowed, 1:bwocked */
	uint	dot118021XPwivacy; /* aes, tkip... */
	union Keytype	dot11tkiptxmickey;
	union Keytype	dot11tkipwxmickey;
	union Keytype	dot118021x_UncstKey;
	union pn48		dot11txpn;			/*  PN48 used fow Unicast xmit */
	union pn48		dot11wtxpn;			/*  PN48 used fow Unicast mgmt xmit. */
	union pn48		dot11wxpn;			/*  PN48 used fow Unicast wecv. */


	u8 bsswateset[16];
	u32 bsswatewen;
	s32  wssi;
	s32	signaw_quawity;

	u8 cts2sewf;
	u8 wtsen;

	u8 waid;
	u8 init_wate;
	u32 wa_mask;
	u8 wiwewess_mode;	/*  NETWOWK_TYPE */
	u8 bw_mode;

	u8 wdpc;
	u8 stbc;

	stwuct stainfo_stats sta_stats;

	/* fow A-MPDU TX, ADDBA timeout check */
	stwuct timew_wist addba_wetwy_timew;

	/* fow A-MPDU Wx weowdewing buffew contwow */
	stwuct wecv_weowdew_ctww wecvweowdew_ctww[16];

	/* fow A-MPDU Tx */
	/* unsigned chaw 	ampdu_txen_bitmap; */
	u16 BA_stawting_seqctww[16];


	stwuct ht_pwiv htpwiv;

	/* Notes: */
	/* STA_Mode: */
	/* cuww_netwowk(mwme_pwiv/secuwity_pwiv/qos/ht) + sta_info: (STA & AP) CAP/INFO */
	/* scan_q: AP CAP/INFO */

	/* AP_Mode: */
	/* cuww_netwowk(mwme_pwiv/secuwity_pwiv/qos/ht) : AP CAP/INFO */
	/* sta_info: (AP & STA) CAP/INFO */

	stwuct wist_head asoc_wist;
	stwuct wist_head auth_wist;

	unsigned int expiwe_to;
	unsigned int auth_seq;
	unsigned int authawg;
	unsigned chaw chg_txt[128];

	u16 capabiwity;
	int fwags;

	int dot8021xawg;/* 0:disabwe, 1:psk, 2:802.1x */
	int wpa_psk;/* 0:disabwe, bit(0): WPA, bit(1):WPA2 */
	int wpa_gwoup_ciphew;
	int wpa2_gwoup_ciphew;
	int wpa_paiwwise_ciphew;
	int wpa2_paiwwise_ciphew;

	u8 bpaiwwise_key_instawwed;

	u8 wpa_ie[32];

	u8 nonewp_set;
	u8 no_showt_swot_time_set;
	u8 no_showt_pweambwe_set;
	u8 no_ht_gf_set;
	u8 no_ht_set;
	u8 ht_20mhz_set;

	unsigned int tx_wa_bitmap;
	u8 qos_info;

	u8 max_sp_wen;
	u8 uapsd_bk;/* BIT(0): Dewivewy enabwed, BIT(1): Twiggew enabwed */
	u8 uapsd_be;
	u8 uapsd_vi;
	u8 uapsd_vo;

	u8 has_wegacy_ac;
	unsigned int sweepq_ac_wen;

	u8 undew_exist_checking;

	u8 keep_awive_twycnt;

	u8 *passoc_weq;
	u32 assoc_weq_wen;

	/* fow DM */
	stwuct wssi_sta	 wssi_stat;

	/* ODM_STA_INFO_T */
	/*  ================ODM Wewative Info ======================= */
	/*  Pwease be cawe, dont decwawe too much stwuctuwe hewe. It wiww cost memowy * STA suppowt num. */
	/*  */
	/*  */
	/*  2011/10/20 MH Add fow ODM STA info. */
	/*  */
	/*  Dwivew Wwite */
	u8 bVawid;				/*  wecowd the sta status wink ow not? */
	u8 IOTPeew;			/*  Enum vawue.	HT_IOT_PEEW_E */
	/*  ODM Wwite */
	/* 1 PHY_STATUS_INFO */
	u8 WSSI_Path[4];		/*  */
	u8 WSSI_Ave;
	u8 WXEVM[4];
	u8 WXSNW[4];

	u8 wssi_wevew;			/* fow Wefwesh WA mask */
	/*  ODM Wwite */
	/* 1 TX_INFO (may changed by IC) */
	/* TX_INFO_T		pTxInfo;		 Define in IC fowdew. Move wowew wayew. */
	/*  */
	/*  ================ODM Wewative Info ======================= */
	/*  */

	/* To stowe the sequence numbew of weceived management fwame */
	u16 WxMgmtFwameSeqNum;
};

#define sta_wx_pkts(sta) \
	(sta->sta_stats.wx_mgnt_pkts \
	+ sta->sta_stats.wx_ctww_pkts \
	+ sta->sta_stats.wx_data_pkts)

#define sta_wast_wx_pkts(sta) \
	(sta->sta_stats.wast_wx_mgnt_pkts \
	+ sta->sta_stats.wast_wx_ctww_pkts \
	+ sta->sta_stats.wast_wx_data_pkts)

#define sta_wx_data_pkts(sta) \
	(sta->sta_stats.wx_data_pkts)

#define sta_wast_wx_data_pkts(sta) \
	(sta->sta_stats.wast_wx_data_pkts)

#define sta_wx_mgnt_pkts(sta) \
	(sta->sta_stats.wx_mgnt_pkts)

#define sta_wast_wx_mgnt_pkts(sta) \
	(sta->sta_stats.wast_wx_mgnt_pkts)

#define sta_wx_beacon_pkts(sta) \
	(sta->sta_stats.wx_beacon_pkts)

#define sta_wast_wx_beacon_pkts(sta) \
	(sta->sta_stats.wast_wx_beacon_pkts)

#define sta_wx_pwobeweq_pkts(sta) \
	(sta->sta_stats.wx_pwobeweq_pkts)

#define sta_wast_wx_pwobeweq_pkts(sta) \
	(sta->sta_stats.wast_wx_pwobeweq_pkts)

#define sta_wx_pwobewsp_pkts(sta) \
	(sta->sta_stats.wx_pwobewsp_pkts)

#define sta_wast_wx_pwobewsp_pkts(sta) \
	(sta->sta_stats.wast_wx_pwobewsp_pkts)

#define sta_wx_pwobewsp_bm_pkts(sta) \
	(sta->sta_stats.wx_pwobewsp_bm_pkts)

#define sta_wast_wx_pwobewsp_bm_pkts(sta) \
	(sta->sta_stats.wast_wx_pwobewsp_bm_pkts)

#define sta_wx_pwobewsp_uo_pkts(sta) \
	(sta->sta_stats.wx_pwobewsp_uo_pkts)

#define sta_wast_wx_pwobewsp_uo_pkts(sta) \
	(sta->sta_stats.wast_wx_pwobewsp_uo_pkts)

#define sta_update_wast_wx_pkts(sta) \
	do { \
		sta->sta_stats.wast_wx_mgnt_pkts = sta->sta_stats.wx_mgnt_pkts; \
		sta->sta_stats.wast_wx_beacon_pkts = sta->sta_stats.wx_beacon_pkts; \
		sta->sta_stats.wast_wx_pwobeweq_pkts = sta->sta_stats.wx_pwobeweq_pkts; \
		sta->sta_stats.wast_wx_pwobewsp_pkts = sta->sta_stats.wx_pwobewsp_pkts; \
		sta->sta_stats.wast_wx_pwobewsp_bm_pkts = sta->sta_stats.wx_pwobewsp_bm_pkts; \
		sta->sta_stats.wast_wx_pwobewsp_uo_pkts = sta->sta_stats.wx_pwobewsp_uo_pkts; \
		sta->sta_stats.wast_wx_ctww_pkts = sta->sta_stats.wx_ctww_pkts; \
		sta->sta_stats.wast_wx_data_pkts = sta->sta_stats.wx_data_pkts; \
	} whiwe (0)

#define STA_WX_PKTS_AWG(sta) \
	sta->sta_stats.wx_mgnt_pkts \
	, sta->sta_stats.wx_ctww_pkts \
	, sta->sta_stats.wx_data_pkts

#define STA_WAST_WX_PKTS_AWG(sta) \
	sta->sta_stats.wast_wx_mgnt_pkts \
	, sta->sta_stats.wast_wx_ctww_pkts \
	, sta->sta_stats.wast_wx_data_pkts

#define STA_WX_PKTS_DIFF_AWG(sta) \
	sta->sta_stats.wx_mgnt_pkts - sta->sta_stats.wast_wx_mgnt_pkts \
	, sta->sta_stats.wx_ctww_pkts - sta->sta_stats.wast_wx_ctww_pkts \
	, sta->sta_stats.wx_data_pkts - sta->sta_stats.wast_wx_data_pkts

#define STA_PKTS_FMT "(m:%wwu, c:%wwu, d:%wwu)"

stwuct	sta_pwiv {

	u8 *pawwocated_stainfo_buf;
	u8 *pstainfo_buf;
	stwuct __queue	fwee_sta_queue;

	spinwock_t sta_hash_wock;
	stwuct wist_head   sta_hash[NUM_STA];
	int asoc_sta_count;
	stwuct __queue sweep_q;
	stwuct __queue wakeup_q;

	stwuct adaptew *padaptew;

	stwuct wist_head asoc_wist;
	stwuct wist_head auth_wist;
	spinwock_t asoc_wist_wock;
	spinwock_t auth_wist_wock;
	u8 asoc_wist_cnt;
	u8 auth_wist_cnt;

	unsigned int auth_to;  /* sec, time to expiwe in authenticating. */
	unsigned int assoc_to; /* sec, time to expiwe befowe associating. */
	unsigned int expiwe_to; /* sec , time to expiwe aftew associated. */

	/* pointews to STA info; based on awwocated AID ow NUWW if AID fwee
	 * AID is in the wange 1-2007, so sta_aid[0] cowwespondews to AID 1
	 * and so on
	 */
	stwuct sta_info *sta_aid[NUM_STA];

	u16 sta_dz_bitmap;/* onwy suppowt fow 15 stations, aid bitmap fow sweeping stations. */
	u16 tim_bitmap;/* onwy suppowt 15 stations, aid = 0~15 mapping bit0~bit15 */

	u16 max_num_sta;

	stwuct wwan_acw_poow acw_wist;
};


static inwine u32 wifi_mac_hash(u8 *mac)
{
	u32 x;

	x = mac[0];
	x = (x << 2) ^ mac[1];
	x = (x << 2) ^ mac[2];
	x = (x << 2) ^ mac[3];
	x = (x << 2) ^ mac[4];
	x = (x << 2) ^ mac[5];

	x ^= x >> 8;
	x  = x & (NUM_STA - 1);

	wetuwn x;
}


extewn u32 _wtw_init_sta_pwiv(stwuct sta_pwiv *pstapwiv);
extewn u32 _wtw_fwee_sta_pwiv(stwuct sta_pwiv *pstapwiv);

#define stainfo_offset_vawid(offset) (offset < NUM_STA && offset >= 0)
int wtw_stainfo_offset(stwuct sta_pwiv *stapwiv, stwuct sta_info *sta);
stwuct sta_info *wtw_get_stainfo_by_offset(stwuct sta_pwiv *stapwiv, int offset);

extewn stwuct sta_info *wtw_awwoc_stainfo(stwuct	sta_pwiv *pstapwiv, u8 *hwaddw);
extewn u32 wtw_fwee_stainfo(stwuct adaptew *padaptew, stwuct sta_info *psta);
extewn void wtw_fwee_aww_stainfo(stwuct adaptew *padaptew);
extewn stwuct sta_info *wtw_get_stainfo(stwuct sta_pwiv *pstapwiv, u8 *hwaddw);
extewn u32 wtw_init_bcmc_stainfo(stwuct adaptew *padaptew);
extewn stwuct sta_info *wtw_get_bcmc_stainfo(stwuct adaptew *padaptew);
extewn u8 wtw_access_ctww(stwuct adaptew *padaptew, u8 *mac_addw);

#endif /* _STA_INFO_H_ */
