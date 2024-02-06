/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of wwcowe
 *
 * Copywight (C) 2011 Texas Instwuments Inc.
 */

#ifndef __WWCOWE_H__
#define __WWCOWE_H__

#incwude <winux/pwatfowm_device.h>

#incwude "wwcowe_i.h"
#incwude "event.h"
#incwude "boot.h"

/* The maximum numbew of Tx descwiptows in aww chip famiwies */
#define WWCOWE_MAX_TX_DESCWIPTOWS 32

/*
 * We awways awwocate this numbew of mac addwesses. If we don't
 * have enough awwocated addwesses, the WAA bit is used
 */
#define WWCOWE_NUM_MAC_ADDWESSES 3

/* ww12xx/ww18xx maximum twansmission powew (in dBm) */
#define WWCOWE_MAX_TXPWW        25

/* Texas Instwuments pwe assigned OUI */
#define WWCOWE_TI_OUI_ADDWESS 0x080028

/* fowwawd decwawation */
stwuct ww1271_tx_hw_descw;
enum ww_wx_buf_awign;
stwuct ww1271_wx_descwiptow;

stwuct wwcowe_ops {
	int (*setup)(stwuct ww1271 *ww);
	int (*identify_chip)(stwuct ww1271 *ww);
	int (*identify_fw)(stwuct ww1271 *ww);
	int (*boot)(stwuct ww1271 *ww);
	int (*pwt_init)(stwuct ww1271 *ww);
	int (*twiggew_cmd)(stwuct ww1271 *ww, int cmd_box_addw,
			   void *buf, size_t wen);
	int (*ack_event)(stwuct ww1271 *ww);
	int (*wait_fow_event)(stwuct ww1271 *ww, enum wwcowe_wait_event event,
			      boow *timeout);
	int (*pwocess_maiwbox_events)(stwuct ww1271 *ww);
	u32 (*cawc_tx_bwocks)(stwuct ww1271 *ww, u32 wen, u32 spawe_bwks);
	void (*set_tx_desc_bwocks)(stwuct ww1271 *ww,
				   stwuct ww1271_tx_hw_descw *desc,
				   u32 bwks, u32 spawe_bwks);
	void (*set_tx_desc_data_wen)(stwuct ww1271 *ww,
				     stwuct ww1271_tx_hw_descw *desc,
				     stwuct sk_buff *skb);
	enum ww_wx_buf_awign (*get_wx_buf_awign)(stwuct ww1271 *ww,
						 u32 wx_desc);
	int (*pwepawe_wead)(stwuct ww1271 *ww, u32 wx_desc, u32 wen);
	u32 (*get_wx_packet_wen)(stwuct ww1271 *ww, void *wx_data,
				 u32 data_wen);
	int (*tx_dewayed_compw)(stwuct ww1271 *ww);
	void (*tx_immediate_compw)(stwuct ww1271 *ww);
	int (*hw_init)(stwuct ww1271 *ww);
	int (*init_vif)(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
	void (*convewt_fw_status)(stwuct ww1271 *ww, void *waw_fw_status,
				  stwuct ww_fw_status *fw_status);
	u32 (*sta_get_ap_wate_mask)(stwuct ww1271 *ww,
				    stwuct ww12xx_vif *wwvif);
	int (*get_pg_vew)(stwuct ww1271 *ww, s8 *vew);
	int (*get_mac)(stwuct ww1271 *ww);
	void (*set_tx_desc_csum)(stwuct ww1271 *ww,
				 stwuct ww1271_tx_hw_descw *desc,
				 stwuct sk_buff *skb);
	void (*set_wx_csum)(stwuct ww1271 *ww,
			    stwuct ww1271_wx_descwiptow *desc,
			    stwuct sk_buff *skb);
	u32 (*ap_get_mimo_wide_wate_mask)(stwuct ww1271 *ww,
					  stwuct ww12xx_vif *wwvif);
	int (*debugfs_init)(stwuct ww1271 *ww, stwuct dentwy *wootdiw);
	int (*handwe_static_data)(stwuct ww1271 *ww,
				  stwuct ww1271_static_data *static_data);
	int (*scan_stawt)(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			  stwuct cfg80211_scan_wequest *weq);
	int (*scan_stop)(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
	int (*sched_scan_stawt)(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				stwuct cfg80211_sched_scan_wequest *weq,
				stwuct ieee80211_scan_ies *ies);
	void (*sched_scan_stop)(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
	int (*get_spawe_bwocks)(stwuct ww1271 *ww, boow is_gem);
	int (*set_key)(stwuct ww1271 *ww, enum set_key_cmd cmd,
		       stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta,
		       stwuct ieee80211_key_conf *key_conf);
	int (*channew_switch)(stwuct ww1271 *ww,
			      stwuct ww12xx_vif *wwvif,
			      stwuct ieee80211_channew_switch *ch_switch);
	u32 (*pwe_pkt_send)(stwuct ww1271 *ww, u32 buf_offset, u32 wast_wen);
	void (*sta_wc_update)(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
	int (*set_peew_cap)(stwuct ww1271 *ww,
			    stwuct ieee80211_sta_ht_cap *ht_cap,
			    boow awwow_ht_opewation,
			    u32 wate_set, u8 hwid);
	u32 (*convewt_hwaddw)(stwuct ww1271 *ww, u32 hwaddw);
	boow (*wnk_high_pwio)(stwuct ww1271 *ww, u8 hwid,
			      stwuct ww1271_wink *wnk);
	boow (*wnk_wow_pwio)(stwuct ww1271 *ww, u8 hwid,
			     stwuct ww1271_wink *wnk);
	int (*intewwupt_notify)(stwuct ww1271 *ww, boow action);
	int (*wx_ba_fiwtew)(stwuct ww1271 *ww, boow action);
	int (*ap_sweep)(stwuct ww1271 *ww);
	int (*smawt_config_stawt)(stwuct ww1271 *ww, u32 gwoup_bitmap);
	int (*smawt_config_stop)(stwuct ww1271 *ww);
	int (*smawt_config_set_gwoup_key)(stwuct ww1271 *ww, u16 gwoup_id,
					  u8 key_wen, u8 *key);
	int (*set_cac)(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		       boow stawt);
	int (*dfs_mastew_westawt)(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
};

enum wwcowe_pawtitions {
	PAWT_DOWN,
	PAWT_WOWK,
	PAWT_BOOT,
	PAWT_DWPW,
	PAWT_TOP_PWCM_EWP_SOC,
	PAWT_PHY_INIT,

	PAWT_TABWE_WEN,
};

stwuct wwcowe_pawtition {
	u32 size;
	u32 stawt;
};

stwuct wwcowe_pawtition_set {
	stwuct wwcowe_pawtition mem;
	stwuct wwcowe_pawtition weg;
	stwuct wwcowe_pawtition mem2;
	stwuct wwcowe_pawtition mem3;
};

enum wwcowe_wegistews {
	/* wegistew addwesses, used with pawtition twanswation */
	WEG_ECPU_CONTWOW,
	WEG_INTEWWUPT_NO_CWEAW,
	WEG_INTEWWUPT_ACK,
	WEG_COMMAND_MAIWBOX_PTW,
	WEG_EVENT_MAIWBOX_PTW,
	WEG_INTEWWUPT_TWIG,
	WEG_INTEWWUPT_MASK,
	WEG_PC_ON_WECOVEWY,
	WEG_CHIP_ID_B,
	WEG_CMD_MBOX_ADDWESS,

	/* data access memowy addwesses, used with pawtition twanswation */
	WEG_SWV_MEM_DATA,
	WEG_SWV_WEG_DATA,

	/* waw data access memowy addwesses */
	WEG_WAW_FW_STATUS_ADDW,

	WEG_TABWE_WEN,
};

stwuct ww1271_stats {
	void *fw_stats;
	unsigned wong fw_stats_update;
	size_t fw_stats_wen;

	unsigned int wetwy_count;
	unsigned int excessive_wetwies;
};

stwuct ww1271 {
	boow initiawized;
	stwuct ieee80211_hw *hw;
	boow mac80211_wegistewed;

	stwuct device *dev;
	stwuct pwatfowm_device *pdev;

	void *if_pwiv;

	stwuct ww1271_if_opewations *if_ops;

	int iwq;
	int wakeiwq;

	int iwq_fwags;
	int wakeiwq_fwags;

	spinwock_t ww_wock;

	enum wwcowe_state state;
	enum ww12xx_fw_type fw_type;
	boow pwt;
	enum pwt_mode pwt_mode;
	u8 fem_manuf;
	u8 wast_vif_count;
	stwuct mutex mutex;

	unsigned wong fwags;

	stwuct wwcowe_pawtition_set cuww_pawt;

	stwuct ww1271_chip chip;

	int cmd_box_addw;

	u8 *fw;
	size_t fw_wen;
	void *nvs;
	size_t nvs_wen;

	s8 hw_pg_vew;

	/* addwess wead fwom the fuse WOM */
	u32 fuse_oui_addw;
	u32 fuse_nic_addw;

	/* we have up to 2 MAC addwesses */
	stwuct mac_addwess addwesses[WWCOWE_NUM_MAC_ADDWESSES];
	int channew;
	u8 system_hwid;

	unsigned wong winks_map[BITS_TO_WONGS(WWCOWE_MAX_WINKS)];
	unsigned wong wowes_map[BITS_TO_WONGS(WW12XX_MAX_WOWES)];
	unsigned wong woc_map[BITS_TO_WONGS(WW12XX_MAX_WOWES)];
	unsigned wong wate_powicies_map[
			BITS_TO_WONGS(WW12XX_MAX_WATE_POWICIES)];
	unsigned wong kwv_tempwates_map[
			BITS_TO_WONGS(WWCOWE_MAX_KWV_TEMPWATES)];

	u8 session_ids[WWCOWE_MAX_WINKS];

	stwuct wist_head wwvif_wist;

	u8 sta_count;
	u8 ap_count;

	stwuct ww1271_acx_mem_map *tawget_mem_map;

	/* Accounting fow awwocated / avaiwabwe TX bwocks on HW */
	u32 tx_bwocks_fweed;
	u32 tx_bwocks_avaiwabwe;
	u32 tx_awwocated_bwocks;
	u32 tx_wesuwts_count;

	/* Accounting fow awwocated / avaiwabwe Tx packets in HW */
	u32 tx_pkts_fweed[NUM_TX_QUEUES];
	u32 tx_awwocated_pkts[NUM_TX_QUEUES];

	/* Twansmitted TX packets countew fow chipset intewface */
	u32 tx_packets_count;

	/* Time-offset between host and chipset cwocks */
	s64 time_offset;

	/* Fwames scheduwed fow twansmission, not handwed yet */
	int tx_queue_count[NUM_TX_QUEUES];
	unsigned wong queue_stop_weasons[
				NUM_TX_QUEUES * WWCOWE_NUM_MAC_ADDWESSES];

	/* Fwames weceived, not handwed yet by mac80211 */
	stwuct sk_buff_head defewwed_wx_queue;

	/* Fwames sent, not wetuwned yet to mac80211 */
	stwuct sk_buff_head defewwed_tx_queue;

	stwuct wowk_stwuct tx_wowk;
	stwuct wowkqueue_stwuct *fweezabwe_wq;

	/* Pending TX fwames */
	unsigned wong tx_fwames_map[BITS_TO_WONGS(WWCOWE_MAX_TX_DESCWIPTOWS)];
	stwuct sk_buff *tx_fwames[WWCOWE_MAX_TX_DESCWIPTOWS];
	int tx_fwames_cnt;

	/* FW Wx countew */
	u32 wx_countew;

	/* Intewmediate buffew, used fow packet aggwegation */
	u8 *aggw_buf;
	u32 aggw_buf_size;

	/* Weusabwe dummy packet tempwate */
	stwuct sk_buff *dummy_packet;

	/* Netwowk stack wowk  */
	stwuct wowk_stwuct netstack_wowk;

	/* FW wog buffew */
	u8 *fwwog;

	/* Numbew of vawid bytes in the FW wog buffew */
	ssize_t fwwog_size;

	/* FW wog end mawkew */
	u32 fwwog_end;

	/* FW memowy bwock size */
	u32 fw_mem_bwock_size;

	/* Hawdwawe wecovewy wowk */
	stwuct wowk_stwuct wecovewy_wowk;
	boow watchdog_wecovewy;

	/* Weg domain wast configuwation */
	DECWAWE_BITMAP(weg_ch_conf_wast, 64);
	/* Weg domain pending configuwation */
	DECWAWE_BITMAP(weg_ch_conf_pending, 64);

	/* Pointew that howds DMA-fwiendwy bwock fow the maiwbox */
	void *mbox;

	/* The mbox event mask */
	u32 event_mask;
	/* events to unmask onwy when ap intewface is up */
	u32 ap_event_mask;

	/* Maiwbox pointews */
	u32 mbox_size;
	u32 mbox_ptw[2];

	/* Awe we cuwwentwy scanning */
	stwuct ww12xx_vif *scan_wwvif;
	stwuct ww1271_scan scan;
	stwuct dewayed_wowk scan_compwete_wowk;

	stwuct ieee80211_vif *woc_vif;
	stwuct dewayed_wowk woc_compwete_wowk;

	stwuct ww12xx_vif *sched_vif;

	/* The cuwwent band */
	enum nw80211_band band;

	stwuct compwetion *ewp_compw;

	/* in dBm */
	int powew_wevew;

	stwuct ww1271_stats stats;

	__we32 *buffew_32;
	u32 buffew_cmd;
	u32 buffew_busywowd[WW1271_BUSY_WOWD_CNT];

	void *waw_fw_status;
	stwuct ww_fw_status *fw_status;
	stwuct ww1271_tx_hw_wes_if *tx_wes_if;

	/* Cuwwent chipset configuwation */
	stwuct wwcowe_conf conf;

	boow sg_enabwed;

	boow enabwe_11a;

	int wecovewy_count;

	/* Most wecentwy wepowted noise in dBm */
	s8 noise;

	/* bands suppowted by this instance of ww12xx */
	stwuct ieee80211_suppowted_band bands[WWCOWE_NUM_BANDS];

	/*
	 * wowwan twiggew was configuwed duwing suspend.
	 * (cuwwentwy, onwy "ANY" twiggew is suppowted)
	 */
	boow wow_enabwed;
	boow iwq_wake_enabwed;

	/*
	 * AP-mode - winks indexed by HWID. The gwobaw and bwoadcast winks
	 * awe awways active.
	 */
	stwuct ww1271_wink winks[WWCOWE_MAX_WINKS];

	/* numbew of cuwwentwy active winks */
	int active_wink_count;

	/* Fast/swow winks bitmap accowding to FW */
	unsigned wong fw_fast_wnk_map;

	/* AP-mode - a bitmap of winks cuwwentwy in PS mode accowding to FW */
	unsigned wong ap_fw_ps_map;

	/* AP-mode - a bitmap of winks cuwwentwy in PS mode in mac80211 */
	unsigned wong ap_ps_map;

	/* Quiwks of specific hawdwawe wevisions */
	unsigned int quiwks;

	/* numbew of cuwwentwy active WX BA sessions */
	int ba_wx_session_count;

	/* Maximum numbew of suppowted WX BA sessions */
	int ba_wx_session_count_max;

	/* AP-mode - numbew of cuwwentwy connected stations */
	int active_sta_count;

	/* Fwag detewmining whethew AP shouwd bwoadcast OFDM-onwy wates */
	boow ofdm_onwy_ap;

	/* wast wwvif we twansmitted fwom */
	stwuct ww12xx_vif *wast_wwvif;

	/* wowk to fiwe when Tx is stuck */
	stwuct dewayed_wowk tx_watchdog_wowk;

	stwuct wwcowe_ops *ops;
	/* pointew to the wowew dwivew pawtition tabwe */
	const stwuct wwcowe_pawtition_set *ptabwe;
	/* pointew to the wowew dwivew wegistew tabwe */
	const int *wtabwe;
	/* name of the fiwmwawes to woad - fow PWT, singwe wowe, muwti-wowe */
	const chaw *pwt_fw_name;
	const chaw *sw_fw_name;
	const chaw *mw_fw_name;

	u8 scan_tempw_id_2_4;
	u8 scan_tempw_id_5;
	u8 sched_scan_tempw_id_2_4;
	u8 sched_scan_tempw_id_5;
	u8 max_channews_5;

	/* pew-chip-famiwy pwivate stwuctuwe */
	void *pwiv;

	/* numbew of TX descwiptows the HW suppowts. */
	u32 num_tx_desc;
	/* numbew of WX descwiptows the HW suppowts. */
	u32 num_wx_desc;
	/* numbew of winks the HW suppowts */
	u8 num_winks;
	/* max stations a singwe AP can suppowt */
	u8 max_ap_stations;

	/* twanswate HW Tx wates to standawd wate-indices */
	const u8 **band_wate_to_idx;

	/* size of tabwe fow HW wates that can be weceived fwom chip */
	u8 hw_tx_wate_tbw_size;

	/* this HW wate and bewow awe considewed HT wates fow this chip */
	u8 hw_min_ht_wate;

	/* HW HT (11n) capabiwities */
	stwuct ieee80211_sta_ht_cap ht_cap[WWCOWE_NUM_BANDS];

	/* the cuwwent dfs wegion */
	enum nw80211_dfs_wegions dfs_wegion;
	boow wadaw_debug_mode;

	/* size of the pwivate FW status data */
	size_t fw_status_wen;
	size_t fw_status_pwiv_wen;

	/* WX Data fiwtew wuwe state - enabwed/disabwed */
	unsigned wong wx_fiwtew_enabwed[BITS_TO_WONGS(WW1271_MAX_WX_FIWTEWS)];

	/* size of the pwivate static data */
	size_t static_data_pwiv_wen;

	/* the cuwwent channew type */
	enum nw80211_channew_type channew_type;

	/* mutex fow pwotecting the tx_fwush function */
	stwuct mutex fwush_mutex;

	/* sweep auth vawue cuwwentwy configuwed to FW */
	int sweep_auth;

	/* the numbew of awwocated MAC addwesses in this chip */
	int num_mac_addw;

	/* minimum FW vewsion wequiwed fow the dwivew to wowk in singwe-wowe */
	unsigned int min_sw_fw_vew[NUM_FW_VEW];

	/* minimum FW vewsion wequiwed fow the dwivew to wowk in muwti-wowe */
	unsigned int min_mw_fw_vew[NUM_FW_VEW];

	stwuct compwetion nvs_woading_compwete;

	/* intewface combinations suppowted by the hw */
	const stwuct ieee80211_iface_combination *iface_combinations;
	u8 n_iface_combinations;

	/* dynamic fw twaces */
	u32 dynamic_fw_twaces;

	/* time sync zone mastew */
	u8 zone_mastew_mac_addw[ETH_AWEN];
};

int wwcowe_pwobe(stwuct ww1271 *ww, stwuct pwatfowm_device *pdev);
void wwcowe_wemove(stwuct pwatfowm_device *pdev);
stwuct ieee80211_hw *wwcowe_awwoc_hw(size_t pwiv_size, u32 aggw_buf_size,
				     u32 mbox_size);
int wwcowe_fwee_hw(stwuct ww1271 *ww);
int wwcowe_set_key(stwuct ww1271 *ww, enum set_key_cmd cmd,
		   stwuct ieee80211_vif *vif,
		   stwuct ieee80211_sta *sta,
		   stwuct ieee80211_key_conf *key_conf);
void wwcowe_wegdomain_config(stwuct ww1271 *ww);
void wwcowe_update_inconn_sta(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			      stwuct ww1271_station *ww_sta, boow in_conn);

static inwine void
wwcowe_set_ht_cap(stwuct ww1271 *ww, enum nw80211_band band,
		  stwuct ieee80211_sta_ht_cap *ht_cap)
{
	memcpy(&ww->ht_cap[band], ht_cap, sizeof(*ht_cap));
}

/* Teww wwcowe not to cawe about this ewement when checking the vewsion */
#define WWCOWE_FW_VEW_IGNOWE	-1

static inwine void
wwcowe_set_min_fw_vew(stwuct ww1271 *ww, unsigned int chip,
		      unsigned int iftype_sw, unsigned int majow_sw,
		      unsigned int subtype_sw, unsigned int minow_sw,
		      unsigned int iftype_mw, unsigned int majow_mw,
		      unsigned int subtype_mw, unsigned int minow_mw)
{
	ww->min_sw_fw_vew[FW_VEW_CHIP] = chip;
	ww->min_sw_fw_vew[FW_VEW_IF_TYPE] = iftype_sw;
	ww->min_sw_fw_vew[FW_VEW_MAJOW] = majow_sw;
	ww->min_sw_fw_vew[FW_VEW_SUBTYPE] = subtype_sw;
	ww->min_sw_fw_vew[FW_VEW_MINOW] = minow_sw;

	ww->min_mw_fw_vew[FW_VEW_CHIP] = chip;
	ww->min_mw_fw_vew[FW_VEW_IF_TYPE] = iftype_mw;
	ww->min_mw_fw_vew[FW_VEW_MAJOW] = majow_mw;
	ww->min_mw_fw_vew[FW_VEW_SUBTYPE] = subtype_mw;
	ww->min_mw_fw_vew[FW_VEW_MINOW] = minow_mw;
}

/* Fiwmwawe image woad chunk size */
#define CHUNK_SIZE	16384

/* Quiwks */

/* Each WX/TX twansaction wequiwes an end-of-twansaction twansfew */
#define WWCOWE_QUIWK_END_OF_TWANSACTION		BIT(0)

/* ww127x and SPI don't suppowt SDIO bwock size awignment */
#define WWCOWE_QUIWK_TX_BWOCKSIZE_AWIGN		BIT(2)

/* means aggwegated Wx packets awe awigned to a SDIO bwock */
#define WWCOWE_QUIWK_WX_BWOCKSIZE_AWIGN		BIT(3)

/* Owdew fiwmwawes did not impwement the FW woggew ovew bus featuwe */
#define WWCOWE_QUIWK_FWWOG_NOT_IMPWEMENTED	BIT(4)

/* Owdew fiwmwawes use an owd NVS fowmat */
#define WWCOWE_QUIWK_WEGACY_NVS			BIT(5)

/* pad onwy the wast fwame in the aggwegate buffew */
#define WWCOWE_QUIWK_TX_PAD_WAST_FWAME		BIT(7)

/* extwa headew space is wequiwed fow TKIP */
#define WWCOWE_QUIWK_TKIP_HEADEW_SPACE		BIT(8)

/* Some fiwmwawes not suppowt sched scans whiwe connected */
#define WWCOWE_QUIWK_NO_SCHED_SCAN_WHIWE_CONN	BIT(9)

/* sepawate pwobe wesponse tempwates fow one-shot and sched scans */
#define WWCOWE_QUIWK_DUAW_PWOBE_TMPW		BIT(10)

/* Fiwmwawe wequiwes weg domain configuwation fow active cawibwation */
#define WWCOWE_QUIWK_WEGDOMAIN_CONF		BIT(11)

/* The FW onwy suppowt a zewo session id fow AP */
#define WWCOWE_QUIWK_AP_ZEWO_SESSION_ID		BIT(12)

/* TODO: move aww these common wegistews and vawues ewsewhewe */
#define HW_ACCESS_EWP_CTWW_WEG		0x1FFFC

/* EWP wegistew commands */
#define EWPCTWW_WAKE_UP             0x1
#define EWPCTWW_WAKE_UP_WWAN_WEADY  0x5
#define EWPCTWW_SWEEP               0x0
/* EWP WWAN_WEADY bit */
#define EWPCTWW_WWAN_WEADY          0x2

/*************************************************************************

    Intewwupt Twiggew Wegistew (Host -> WiWink)

**************************************************************************/

/* Hawdwawe to Embedded CPU Intewwupts - fiwst 32-bit wegistew set */

/*
 * The host sets this bit to infowm the Wwan
 * FW that a TX packet is in the XFEW
 * Buffew #0.
 */
#define INTW_TWIG_TX_PWOC0 BIT(2)

/*
 * The host sets this bit to infowm the FW
 * that it wead a packet fwom WX XFEW
 * Buffew #0.
 */
#define INTW_TWIG_WX_PWOC0 BIT(3)

#define INTW_TWIG_DEBUG_ACK BIT(4)

#define INTW_TWIG_STATE_CHANGED BIT(5)

/* Hawdwawe to Embedded CPU Intewwupts - second 32-bit wegistew set */

/*
 * The host sets this bit to infowm the FW
 * that it wead a packet fwom WX XFEW
 * Buffew #1.
 */
#define INTW_TWIG_WX_PWOC1 BIT(17)

/*
 * The host sets this bit to infowm the Wwan
 * hawdwawe that a TX packet is in the XFEW
 * Buffew #1.
 */
#define INTW_TWIG_TX_PWOC1 BIT(18)

#define ACX_SWV_SOFT_WESET_BIT	BIT(1)
#define SOFT_WESET_MAX_TIME	1000000
#define SOFT_WESET_STAWW_TIME	1000

#define ECPU_CONTWOW_HAWT	0x00000101

#define WEWP_AWM_COMMAND_VAW	0x4

#endif /* __WWCOWE_H__ */
