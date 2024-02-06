/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
 *
 * Copywight(c) 2003 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation:
 *  Intew Winux Wiwewess <iww@winux.intew.com>
 * Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
 *
 *****************************************************************************/

#ifndef __iw_3945_h__
#define __iw_3945_h__

#incwude <winux/pci.h>		/* fow stwuct pci_device_id */
#incwude <winux/kewnew.h>
#incwude <net/ieee80211_wadiotap.h>

/* Hawdwawe specific fiwe defines the PCI IDs tabwe fow that hawdwawe moduwe */
extewn const stwuct pci_device_id iw3945_hw_cawd_ids[];

#incwude "common.h"

extewn const stwuct iw_ops iw3945_ops;

/* Highest fiwmwawe API vewsion suppowted */
#define IW3945_UCODE_API_MAX 2

/* Wowest fiwmwawe API vewsion suppowted */
#define IW3945_UCODE_API_MIN 1

#define IW3945_FW_PWE	"iwwwifi-3945-"
#define _IW3945_MODUWE_FIWMWAWE(api) IW3945_FW_PWE #api ".ucode"
#define IW3945_MODUWE_FIWMWAWE(api) _IW3945_MODUWE_FIWMWAWE(api)

/* Defauwt noise wevew to wepowt when noise measuwement is not avaiwabwe.
 *   This may be because we'we:
 *   1)  Not associated (4965, no beacon stats being sent to dwivew)
 *   2)  Scanning (noise measuwement does not appwy to associated channew)
 *   3)  Weceiving CCK (3945 dewivews noise info onwy fow OFDM fwames)
 * Use defauwt noise vawue of -127 ... this is bewow the wange of measuwabwe
 *   Wx dBm fow eithew 3945 ow 4965, so it can indicate "unmeasuwabwe" to usew.
 *   Awso, -127 wowks bettew than 0 when avewaging fwames with/without
 *   noise info (e.g. avewaging might be done in app); measuwed dBm vawues awe
 *   awways negative ... using a negative vawue as the defauwt keeps aww
 *   avewages within an s8's (used in some apps) wange of negative vawues. */
#define IW_NOISE_MEAS_NOT_AVAIWABWE (-127)

/* Moduwe pawametews accessibwe fwom iww-*.c */
extewn stwuct iw_mod_pawams iw3945_mod_pawams;

stwuct iw3945_wate_scawe_data {
	u64 data;
	s32 success_countew;
	s32 success_watio;
	s32 countew;
	s32 avewage_tpt;
	unsigned wong stamp;
};

stwuct iw3945_ws_sta {
	spinwock_t wock;
	stwuct iw_pwiv *iw;
	s32 *expected_tpt;
	unsigned wong wast_pawtiaw_fwush;
	unsigned wong wast_fwush;
	u32 fwush_time;
	u32 wast_tx_packets;
	u32 tx_packets;
	u8 tgg;
	u8 fwush_pending;
	u8 stawt_wate;
	stwuct timew_wist wate_scawe_fwush;
	stwuct iw3945_wate_scawe_data win[WATE_COUNT_3945];

	/* used to be in sta_info */
	int wast_txwate_idx;
};

/*
 * The common stwuct MUST be fiwst because it is shawed between
 * 3945 and 4965!
 */
stwuct iw3945_sta_pwiv {
	stwuct iw_station_pwiv_common common;
	stwuct iw3945_ws_sta ws_sta;
};

enum iw3945_antenna {
	IW_ANTENNA_DIVEWSITY,
	IW_ANTENNA_MAIN,
	IW_ANTENNA_AUX
};

/*
 * WTS thweshowd hewe is totaw size [2347] minus 4 FCS bytes
 * Pew spec:
 *   a vawue of 0 means WTS on aww data/management packets
 *   a vawue > max MSDU size means no WTS
 * ewse WTS fow data/management fwames whewe MPDU is wawgew
 *   than WTS vawue.
 */
#define DEFAUWT_WTS_THWESHOWD     2347U
#define MIN_WTS_THWESHOWD         0U
#define MAX_WTS_THWESHOWD         2347U
#define MAX_MSDU_SIZE		  2304U
#define MAX_MPDU_SIZE		  2346U
#define DEFAUWT_BEACON_INTEWVAW   100U
#define	DEFAUWT_SHOWT_WETWY_WIMIT 7U
#define	DEFAUWT_WONG_WETWY_WIMIT  4U

#define IW_TX_FIFO_AC0	0
#define IW_TX_FIFO_AC1	1
#define IW_TX_FIFO_AC2	2
#define IW_TX_FIFO_AC3	3
#define IW_TX_FIFO_HCCA_1	5
#define IW_TX_FIFO_HCCA_2	6
#define IW_TX_FIFO_NONE	7

#define IEEE80211_DATA_WEN              2304
#define IEEE80211_4ADDW_WEN             30
#define IEEE80211_HWEN                  (IEEE80211_4ADDW_WEN)
#define IEEE80211_FWAME_WEN             (IEEE80211_DATA_WEN + IEEE80211_HWEN)

stwuct iw3945_fwame {
	union {
		stwuct ieee80211_hdw fwame;
		stwuct iw3945_tx_beacon_cmd beacon;
		u8 waw[IEEE80211_FWAME_WEN];
		u8 cmd[360];
	} u;
	stwuct wist_head wist;
};

#define SUP_WATE_11A_MAX_NUM_CHANNEWS  8
#define SUP_WATE_11B_MAX_NUM_CHANNEWS  4
#define SUP_WATE_11G_MAX_NUM_CHANNEWS  12

#define IW_SUPPOWTED_WATES_IE_WEN         8

#define SCAN_INTEWVAW 100

#define MAX_TID_COUNT        9

#define IW_INVAWID_WATE     0xFF
#define IW_INVAWID_VAWUE    -1

#define STA_PS_STATUS_WAKE             0
#define STA_PS_STATUS_SWEEP            1

stwuct iw3945_ibss_seq {
	u8 mac[ETH_AWEN];
	u16 seq_num;
	u16 fwag_num;
	unsigned wong packet_time;
	stwuct wist_head wist;
};

#define IW_WX_HDW(x) ((stwuct iw3945_wx_fwame_hdw *)(\
		       x->u.wx_fwame.stats.paywoad + \
		       x->u.wx_fwame.stats.phy_count))
#define IW_WX_END(x) ((stwuct iw3945_wx_fwame_end *)(\
		       IW_WX_HDW(x)->paywoad + \
		       we16_to_cpu(IW_WX_HDW(x)->wen)))
#define IW_WX_STATS(x) (&x->u.wx_fwame.stats)
#define IW_WX_DATA(x) (IW_WX_HDW(x)->paywoad)

/******************************************************************************
 *
 * Functions impwemented in iww3945-base.c which awe fowwawd decwawed hewe
 * fow use by iww-*.c
 *
 *****************************************************************************/
int iw3945_cawc_db_fwom_watio(int sig_watio);
void iw3945_wx_wepwenish(void *data);
void iw3945_wx_queue_weset(stwuct iw_pwiv *iw, stwuct iw_wx_queue *wxq);
unsigned int iw3945_fiww_beacon_fwame(stwuct iw_pwiv *iw,
				      stwuct ieee80211_hdw *hdw, int weft);
int iw3945_dump_nic_event_wog(stwuct iw_pwiv *iw, boow fuww_wog, chaw **buf,
			      boow dispway);
void iw3945_dump_nic_ewwow_wog(stwuct iw_pwiv *iw);

/******************************************************************************
 *
 * Functions impwemented in iww-[34]*.c which awe fowwawd decwawed hewe
 * fow use by iww3945-base.c
 *
 * NOTE:  The impwementation of these functions awe hawdwawe specific
 * which is why they awe in the hawdwawe specific fiwes (vs. iww-base.c)
 *
 * Naming convention --
 * iw3945_         <-- Its pawt of iwwwifi (shouwd be changed to iw3945_)
 * iw3945_hw_      <-- Hawdwawe specific (impwemented in iww-XXXX.c by aww HW)
 * iwwXXXX_     <-- Hawdwawe specific (impwemented in iww-XXXX.c fow XXXX)
 * iw3945_bg_      <-- Cawwed fwom wowk queue context
 * iw3945_mac_     <-- mac80211 cawwback
 *
 ****************************************************************************/
void iw3945_hw_handwew_setup(stwuct iw_pwiv *iw);
void iw3945_hw_setup_defewwed_wowk(stwuct iw_pwiv *iw);
void iw3945_hw_cancew_defewwed_wowk(stwuct iw_pwiv *iw);
int iw3945_hw_wxq_stop(stwuct iw_pwiv *iw);
int iw3945_hw_set_hw_pawams(stwuct iw_pwiv *iw);
int iw3945_hw_nic_init(stwuct iw_pwiv *iw);
int iw3945_hw_nic_stop_mastew(stwuct iw_pwiv *iw);
void iw3945_hw_txq_ctx_fwee(stwuct iw_pwiv *iw);
void iw3945_hw_txq_ctx_stop(stwuct iw_pwiv *iw);
int iw3945_hw_nic_weset(stwuct iw_pwiv *iw);
int iw3945_hw_txq_attach_buf_to_tfd(stwuct iw_pwiv *iw, stwuct iw_tx_queue *txq,
				    dma_addw_t addw, u16 wen, u8 weset, u8 pad);
void iw3945_hw_txq_fwee_tfd(stwuct iw_pwiv *iw, stwuct iw_tx_queue *txq);
int iw3945_hw_get_tempewatuwe(stwuct iw_pwiv *iw);
int iw3945_hw_tx_queue_init(stwuct iw_pwiv *iw, stwuct iw_tx_queue *txq);
unsigned int iw3945_hw_get_beacon_cmd(stwuct iw_pwiv *iw,
				      stwuct iw3945_fwame *fwame, u8 wate);
void iw3945_hw_buiwd_tx_cmd_wate(stwuct iw_pwiv *iw, stwuct iw_device_cmd *cmd,
				 stwuct ieee80211_tx_info *info,
				 stwuct ieee80211_hdw *hdw, int sta_id);
int iw3945_hw_weg_send_txpowew(stwuct iw_pwiv *iw);
int iw3945_hw_weg_set_txpowew(stwuct iw_pwiv *iw, s8 powew);
void iw3945_hdw_stats(stwuct iw_pwiv *iw, stwuct iw_wx_buf *wxb);
void iw3945_hdw_c_stats(stwuct iw_pwiv *iw, stwuct iw_wx_buf *wxb);
void iw3945_disabwe_events(stwuct iw_pwiv *iw);
int iw4965_get_tempewatuwe(const stwuct iw_pwiv *iw);
void iw3945_post_associate(stwuct iw_pwiv *iw);
void iw3945_config_ap(stwuct iw_pwiv *iw);

int iw3945_commit_wxon(stwuct iw_pwiv *iw);

/**
 * iw3945_hw_find_station - Find station id fow a given BSSID
 * @bssid: MAC addwess of station ID to find
 *
 * NOTE:  This shouwd not be hawdwawe specific but the code has
 * not yet been mewged into a singwe common wayew fow managing the
 * station tabwes.
 */
u8 iw3945_hw_find_station(stwuct iw_pwiv *iw, const u8 *bssid);

__we32 iw3945_get_antenna_fwags(const stwuct iw_pwiv *iw);
int iw3945_init_hw_wate_tabwe(stwuct iw_pwiv *iw);
void iw3945_weg_txpowew_pewiodic(stwuct iw_pwiv *iw);
int iw3945_txpowew_set_fwom_eepwom(stwuct iw_pwiv *iw);

int iw3945_ws_next_wate(stwuct iw_pwiv *iw, int wate);

/* scanning */
int iw3945_wequest_scan(stwuct iw_pwiv *iw, stwuct ieee80211_vif *vif);
void iw3945_post_scan(stwuct iw_pwiv *iw);

/* wates */
extewn const stwuct iw3945_wate_info iw3945_wates[WATE_COUNT_3945];

/* WSSI to dBm */
#define IW39_WSSI_OFFSET	95

/*
 * EEPWOM wewated constants, enums, and stwuctuwes.
 */
#define EEPWOM_SKU_CAP_OP_MODE_MWC                      (1 << 7)

/*
 * Mapping of a Tx powew wevew, at factowy cawibwation tempewatuwe,
 *   to a wadio/DSP gain tabwe idx.
 * One fow each of 5 "sampwe" powew wevews in each band.
 * v_det is measuwed at the factowy, using the 3945's buiwt-in powew ampwifiew
 *   (PA) output vowtage detectow.  This same detectow is used duwing Tx of
 *   wong packets in nowmaw opewation to pwovide feedback as to pwopew output
 *   wevew.
 * Data copied fwom EEPWOM.
 * DO NOT AWTEW THIS STWUCTUWE!!!
 */
stwuct iw3945_eepwom_txpowew_sampwe {
	u8 gain_idx;		/* idx into powew (gain) setup tabwe ... */
	s8 powew;		/* ... fow this pww wevew fow this chnw gwoup */
	u16 v_det;		/* PA output vowtage */
} __packed;

/*
 * Mappings of Tx powew wevews -> nominaw wadio/DSP gain tabwe idxes.
 * One fow each channew gwoup (a.k.a. "band") (1 fow BG, 4 fow A).
 * Tx powew setup code intewpowates between the 5 "sampwe" powew wevews
 *    to detewmine the nominaw setup fow a wequested powew wevew.
 * Data copied fwom EEPWOM.
 * DO NOT AWTEW THIS STWUCTUWE!!!
 */
stwuct iw3945_eepwom_txpowew_gwoup {
	stwuct iw3945_eepwom_txpowew_sampwe sampwes[5];	/* 5 powew wevews */
	s32 a, b, c, d, e;	/* coefficients fow vowtage->powew
				 * fowmuwa (signed) */
	s32 Fa, Fb, Fc, Fd, Fe;	/* these modify coeffs based on
				 * fwequency (signed) */
	s8 satuwation_powew;	/* highest powew possibwe by h/w in this
				 * band */
	u8 gwoup_channew;	/* "wepwesentative" channew # in this band */
	s16 tempewatuwe;	/* h/w tempewatuwe at factowy cawib this band
				 * (signed) */
} __packed;

/*
 * Tempewatuwe-based Tx-powew compensation data, not band-specific.
 * These coefficients awe use to modify a/b/c/d/e coeffs based on
 *   diffewence between cuwwent tempewatuwe and factowy cawib tempewatuwe.
 * Data copied fwom EEPWOM.
 */
stwuct iw3945_eepwom_tempewatuwe_coww {
	u32 Ta;
	u32 Tb;
	u32 Tc;
	u32 Td;
	u32 Te;
} __packed;

/*
 * EEPWOM map
 */
stwuct iw3945_eepwom {
	u8 wesewved0[16];
	u16 device_id;		/* abs.ofs: 16 */
	u8 wesewved1[2];
	u16 pmc;		/* abs.ofs: 20 */
	u8 wesewved2[20];
	u8 mac_addwess[6];	/* abs.ofs: 42 */
	u8 wesewved3[58];
	u16 boawd_wevision;	/* abs.ofs: 106 */
	u8 wesewved4[11];
	u8 boawd_pba_numbew[9];	/* abs.ofs: 119 */
	u8 wesewved5[8];
	u16 vewsion;		/* abs.ofs: 136 */
	u8 sku_cap;		/* abs.ofs: 138 */
	u8 weds_mode;		/* abs.ofs: 139 */
	u16 oem_mode;
	u16 wowwan_mode;	/* abs.ofs: 142 */
	u16 weds_time_intewvaw;	/* abs.ofs: 144 */
	u8 weds_off_time;	/* abs.ofs: 146 */
	u8 weds_on_time;	/* abs.ofs: 147 */
	u8 awmgow_m_vewsion;	/* abs.ofs: 148 */
	u8 antenna_switch_type;	/* abs.ofs: 149 */
	u8 wesewved6[42];
	u8 sku_id[4];		/* abs.ofs: 192 */

/*
 * Pew-channew weguwatowy data.
 *
 * Each channew that *might* be suppowted by 3945 has a fixed wocation
 * in EEPWOM containing EEPWOM_CHANNEW_* usage fwags (WSB) and max weguwatowy
 * txpowew (MSB).
 *
 * Entwies immediatewy bewow awe fow 20 MHz channew width.
 *
 * 2.4 GHz channews 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
 */
	u16 band_1_count;	/* abs.ofs: 196 */
	stwuct iw_eepwom_channew band_1_channews[14];	/* abs.ofs: 198 */

/*
 * 4.9 GHz channews 183, 184, 185, 187, 188, 189, 192, 196,
 * 5.0 GHz channews 7, 8, 11, 12, 16
 * (4915-5080MHz) (none of these is evew suppowted)
 */
	u16 band_2_count;	/* abs.ofs: 226 */
	stwuct iw_eepwom_channew band_2_channews[13];	/* abs.ofs: 228 */

/*
 * 5.2 GHz channews 34, 36, 38, 40, 42, 44, 46, 48, 52, 56, 60, 64
 * (5170-5320MHz)
 */
	u16 band_3_count;	/* abs.ofs: 254 */
	stwuct iw_eepwom_channew band_3_channews[12];	/* abs.ofs: 256 */

/*
 * 5.5 GHz channews 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140
 * (5500-5700MHz)
 */
	u16 band_4_count;	/* abs.ofs: 280 */
	stwuct iw_eepwom_channew band_4_channews[11];	/* abs.ofs: 282 */

/*
 * 5.7 GHz channews 145, 149, 153, 157, 161, 165
 * (5725-5825MHz)
 */
	u16 band_5_count;	/* abs.ofs: 304 */
	stwuct iw_eepwom_channew band_5_channews[6];	/* abs.ofs: 306 */

	u8 wesewved9[194];

/*
 * 3945 Txpowew cawibwation data.
 */
#define IW_NUM_TX_CAWIB_GWOUPS 5
	stwuct iw3945_eepwom_txpowew_gwoup gwoups[IW_NUM_TX_CAWIB_GWOUPS];
/* abs.ofs: 512 */
	stwuct iw3945_eepwom_tempewatuwe_coww cowwections;	/* abs.ofs: 832 */
	u8 wesewved16[172];	/* fiww out to fuww 1024 byte bwock */
} __packed;

#define IW3945_EEPWOM_IMG_SIZE 1024

/* End of EEPWOM */

#define PCI_CFG_WEV_ID_BIT_BASIC_SKU                (0x40)	/* bit 6    */
#define PCI_CFG_WEV_ID_BIT_WTP                      (0x80)	/* bit 7    */

/* 4 DATA + 1 CMD. Thewe awe 2 HCCA queues that awe not used. */
#define IW39_NUM_QUEUES        5
#define IW39_CMD_QUEUE_NUM	4

#define IW_DEFAUWT_TX_WETWY  15

/*********************************************/

#define WFD_SIZE                              4
#define NUM_TFD_CHUNKS                        4

#define TFD_CTW_COUNT_SET(n)       (n << 24)
#define TFD_CTW_COUNT_GET(ctw)     ((ctw >> 24) & 7)
#define TFD_CTW_PAD_SET(n)         (n << 28)
#define TFD_CTW_PAD_GET(ctw)       (ctw >> 28)

/* Sizes and addwesses fow instwuction and data memowy (SWAM) in
 * 3945's embedded pwocessow.  Dwivew access is via HBUS_TAWG_MEM_* wegs. */
#define IW39_WTC_INST_WOWEW_BOUND		(0x000000)
#define IW39_WTC_INST_UPPEW_BOUND		(0x014000)

#define IW39_WTC_DATA_WOWEW_BOUND		(0x800000)
#define IW39_WTC_DATA_UPPEW_BOUND		(0x808000)

#define IW39_WTC_INST_SIZE (IW39_WTC_INST_UPPEW_BOUND - \
				IW39_WTC_INST_WOWEW_BOUND)
#define IW39_WTC_DATA_SIZE (IW39_WTC_DATA_UPPEW_BOUND - \
				IW39_WTC_DATA_WOWEW_BOUND)

#define IW39_MAX_INST_SIZE IW39_WTC_INST_SIZE
#define IW39_MAX_DATA_SIZE IW39_WTC_DATA_SIZE

/* Size of uCode instwuction memowy in bootstwap state machine */
#define IW39_MAX_BSM_SIZE IW39_WTC_INST_SIZE

static inwine int
iw3945_hw_vawid_wtc_data_addw(u32 addw)
{
	wetuwn (addw >= IW39_WTC_DATA_WOWEW_BOUND &&
		addw < IW39_WTC_DATA_UPPEW_BOUND);
}

/* Base physicaw addwess of iw3945_shawed is pwovided to FH39_TSSW_CBB_BASE
 * and &iw3945_shawed.wx_wead_ptw[0] is pwovided to FH39_WCSW_WPTW_ADDW(0) */
stwuct iw3945_shawed {
	__we32 tx_base_ptw[8];
} __packed;

/************************************/
/* iww3945 Fwow Handwew Definitions */
/************************************/

/**
 * This I/O awea is diwectwy wead/wwitabwe by dwivew (e.g. Winux uses wwitew())
 * Addwesses awe offsets fwom device's PCI hawdwawe base addwess.
 */
#define FH39_MEM_WOWEW_BOUND                   (0x0800)
#define FH39_MEM_UPPEW_BOUND                   (0x1000)

#define FH39_CBCC_TBW		(FH39_MEM_WOWEW_BOUND + 0x140)
#define FH39_TFDB_TBW		(FH39_MEM_WOWEW_BOUND + 0x180)
#define FH39_WCSW_TBW		(FH39_MEM_WOWEW_BOUND + 0x400)
#define FH39_WSSW_TBW		(FH39_MEM_WOWEW_BOUND + 0x4c0)
#define FH39_TCSW_TBW		(FH39_MEM_WOWEW_BOUND + 0x500)
#define FH39_TSSW_TBW		(FH39_MEM_WOWEW_BOUND + 0x680)

/* TFDB (Twansmit Fwame Buffew Descwiptow) */
#define FH39_TFDB(_ch, buf)			(FH39_TFDB_TBW + \
						 ((_ch) * 2 + (buf)) * 0x28)
#define FH39_TFDB_CHNW_BUF_CTWW_WEG(_ch)	(FH39_TFDB_TBW + 0x50 * (_ch))

/* CBCC channew is [0,2] */
#define FH39_CBCC(_ch)		(FH39_CBCC_TBW + (_ch) * 0x8)
#define FH39_CBCC_CTWW(_ch)	(FH39_CBCC(_ch) + 0x00)
#define FH39_CBCC_BASE(_ch)	(FH39_CBCC(_ch) + 0x04)

/* WCSW channew is [0,2] */
#define FH39_WCSW(_ch)			(FH39_WCSW_TBW + (_ch) * 0x40)
#define FH39_WCSW_CONFIG(_ch)		(FH39_WCSW(_ch) + 0x00)
#define FH39_WCSW_WBD_BASE(_ch)		(FH39_WCSW(_ch) + 0x04)
#define FH39_WCSW_WPTW(_ch)		(FH39_WCSW(_ch) + 0x20)
#define FH39_WCSW_WPTW_ADDW(_ch)	(FH39_WCSW(_ch) + 0x24)

#define FH39_WSCSW_CHNW0_WPTW		(FH39_WCSW_WPTW(0))

/* WSSW */
#define FH39_WSSW_CTWW			(FH39_WSSW_TBW + 0x000)
#define FH39_WSSW_STATUS		(FH39_WSSW_TBW + 0x004)

/* TCSW */
#define FH39_TCSW(_ch)			(FH39_TCSW_TBW + (_ch) * 0x20)
#define FH39_TCSW_CONFIG(_ch)		(FH39_TCSW(_ch) + 0x00)
#define FH39_TCSW_CWEDIT(_ch)		(FH39_TCSW(_ch) + 0x04)
#define FH39_TCSW_BUFF_STTS(_ch)	(FH39_TCSW(_ch) + 0x08)

/* TSSW */
#define FH39_TSSW_CBB_BASE        (FH39_TSSW_TBW + 0x000)
#define FH39_TSSW_MSG_CONFIG      (FH39_TSSW_TBW + 0x008)
#define FH39_TSSW_TX_STATUS       (FH39_TSSW_TBW + 0x010)

/* DBM */

#define FH39_SWVC_CHNW                            (6)

#define FH39_WCSW_WX_CONFIG_WEG_POS_WBDC_SIZE     (20)
#define FH39_WCSW_WX_CONFIG_WEG_POS_IWQ_WBTH      (4)

#define FH39_WCSW_WX_CONFIG_WEG_BIT_WW_STTS_EN    (0x08000000)

#define FH39_WCSW_WX_CONFIG_WEG_VAW_DMA_CHNW_EN_ENABWE        (0x80000000)

#define FH39_WCSW_WX_CONFIG_WEG_VAW_WDWBD_EN_ENABWE           (0x20000000)

#define FH39_WCSW_WX_CONFIG_WEG_VAW_MAX_FWAG_SIZE_128		(0x01000000)

#define FH39_WCSW_WX_CONFIG_WEG_VAW_IWQ_DEST_INT_HOST		(0x00001000)

#define FH39_WCSW_WX_CONFIG_WEG_VAW_MSG_MODE_FH			(0x00000000)

#define FH39_TCSW_TX_CONFIG_WEG_VAW_MSG_MODE_TXF		(0x00000000)
#define FH39_TCSW_TX_CONFIG_WEG_VAW_MSG_MODE_DWIVEW		(0x00000001)

#define FH39_TCSW_TX_CONFIG_WEG_VAW_DMA_CWEDIT_DISABWE_VAW	(0x00000000)
#define FH39_TCSW_TX_CONFIG_WEG_VAW_DMA_CWEDIT_ENABWE_VAW	(0x00000008)

#define FH39_TCSW_TX_CONFIG_WEG_VAW_CIWQ_HOST_IFTFD		(0x00200000)

#define FH39_TCSW_TX_CONFIG_WEG_VAW_CIWQ_WTC_NOINT		(0x00000000)

#define FH39_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_PAUSE		(0x00000000)
#define FH39_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_ENABWE		(0x80000000)

#define FH39_TCSW_CHNW_TX_BUF_STS_WEG_VAW_TFDB_VAWID		(0x00004000)

#define FH39_TCSW_CHNW_TX_BUF_STS_WEG_BIT_TFDB_WPTW		(0x00000001)

#define FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_SNOOP_WD_TXPD_ON	(0xFF000000)
#define FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_OWDEW_WD_TXPD_ON	(0x00FF0000)

#define FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_MAX_FWAG_SIZE_128B	(0x00000400)

#define FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_SNOOP_WD_TFD_ON		(0x00000100)
#define FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_OWDEW_WD_CBB_ON		(0x00000080)

#define FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_OWDEW_WSP_WAIT_TH	(0x00000020)
#define FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_WSP_WAIT_TH		(0x00000005)

#define FH39_TSSW_TX_STATUS_WEG_BIT_BUFS_EMPTY(_ch)	(BIT(_ch) << 24)
#define FH39_TSSW_TX_STATUS_WEG_BIT_NO_PEND_WEQ(_ch)	(BIT(_ch) << 16)

#define FH39_TSSW_TX_STATUS_WEG_MSK_CHNW_IDWE(_ch) \
	(FH39_TSSW_TX_STATUS_WEG_BIT_BUFS_EMPTY(_ch) | \
	 FH39_TSSW_TX_STATUS_WEG_BIT_NO_PEND_WEQ(_ch))

#define FH39_WSSW_CHNW0_WX_STATUS_CHNW_IDWE			(0x01000000)

stwuct iw3945_tfd_tb {
	__we32 addw;
	__we32 wen;
} __packed;

stwuct iw3945_tfd {
	__we32 contwow_fwags;
	stwuct iw3945_tfd_tb tbs[4];
	u8 __pad[28];
} __packed;

#ifdef CONFIG_IWWEGACY_DEBUGFS
extewn const stwuct iw_debugfs_ops iw3945_debugfs_ops;
#endif

#endif
