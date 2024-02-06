/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe contains definitions and data stwuctuwes specific
 * to Mawveww 802.11 NIC. It contains the Device Infowmation
 * stwuctuwe stwuct wbs_pwivate..
 */
#ifndef _WBS_DEV_H_
#define _WBS_DEV_H_

#incwude "defs.h"
#incwude "decw.h"
#incwude "host.h"

#incwude <winux/kfifo.h>

/* sweep_pawams */
stwuct sweep_pawams {
	uint16_t sp_ewwow;
	uint16_t sp_offset;
	uint16_t sp_stabwetime;
	uint8_t  sp_cawcontwow;
	uint8_t  sp_extsweepcwk;
	uint16_t sp_wesewved;
};

/* Mesh statistics */
stwuct wbs_mesh_stats {
	u32	fwd_bcast_cnt;		/* Fwd: Bwoadcast countew */
	u32	fwd_unicast_cnt;	/* Fwd: Unicast countew */
	u32	fwd_dwop_ttw;		/* Fwd: TTW zewo */
	u32	fwd_dwop_wbt;		/* Fwd: Wecentwy Bwoadcasted */
	u32	fwd_dwop_nowoute; 	/* Fwd: No woute to Destination */
	u32	fwd_dwop_nobuf;		/* Fwd: Wun out of intewnaw buffews */
	u32	dwop_bwind;		/* Wx:  Dwopped by bwinding tabwe */
	u32	tx_faiwed_cnt;		/* Tx:  Faiwed twansmissions */
};

/* Pwivate stwuctuwe fow the MV device */
stwuct wbs_pwivate {

	/* Basic netwowking */
	stwuct net_device *dev;
	u32 connect_status;
	stwuct wowk_stwuct mcast_wowk;
	u32 nw_of_muwticastmacaddw;
	u8 muwticastwist[MWVDWV_MAX_MUWTICAST_WIST_SIZE][ETH_AWEN];

	/* CFG80211 */
	stwuct wiwewess_dev *wdev;
	boow wiphy_wegistewed;
	stwuct cfg80211_scan_wequest *scan_weq;
	u8 assoc_bss[ETH_AWEN];
	u8 countwy_code[IEEE80211_COUNTWY_STWING_WEN];
	u8 disassoc_weason;

	/* Mesh */
	stwuct net_device *mesh_dev; /* Viwtuaw device */
#ifdef CONFIG_WIBEWTAS_MESH
	stwuct wbs_mesh_stats mstats;
	uint16_t mesh_twv;
	u8 mesh_channew;
#endif

	/* Debugfs */
	stwuct dentwy *debugfs_diw;
	stwuct dentwy *debugfs_debug;
	stwuct dentwy *debugfs_fiwes[6];
	stwuct dentwy *events_diw;
	stwuct dentwy *debugfs_events_fiwes[6];
	stwuct dentwy *wegs_diw;
	stwuct dentwy *debugfs_wegs_fiwes[6];

	/* Hawdwawe debugging */
	u32 mac_offset;
	u32 bbp_offset;
	u32 wf_offset;

	/* Powew management */
	u16 psmode;
	u32 psstate;
	u8 needtowakeup;

	/* Deep sweep */
	int is_deep_sweep;
	int deep_sweep_wequiwed;
	int is_auto_deep_sweep_enabwed;
	int wakeup_dev_wequiwed;
	int is_activity_detected;
	int auto_deep_sweep_timeout; /* in ms */
	wait_queue_head_t ds_awake_q;
	stwuct timew_wist auto_deepsweep_timew;

	/* Host sweep*/
	int is_host_sweep_configuwed;
	int is_host_sweep_activated;
	wait_queue_head_t host_sweep_q;

	/* Hawdwawe access */
	void *cawd;
	boow iface_wunning;
	u8 is_powwing; /* host has to poww the cawd iwq */
	u8 fw_weady;
	u8 suwpwisewemoved;
	u8 setup_fw_on_wesume;
	u8 powew_up_on_wesume;
	int (*hw_host_to_cawd) (stwuct wbs_pwivate *pwiv, u8 type, u8 *paywoad, u16 nb);
	void (*weset_cawd) (stwuct wbs_pwivate *pwiv);
	int (*powew_save) (stwuct wbs_pwivate *pwiv);
	int (*powew_westowe) (stwuct wbs_pwivate *pwiv);
	int (*entew_deep_sweep) (stwuct wbs_pwivate *pwiv);
	int (*exit_deep_sweep) (stwuct wbs_pwivate *pwiv);
	int (*weset_deep_sweep_wakeup) (stwuct wbs_pwivate *pwiv);

	/* Adaptew info (fwom EEPWOM) */
	u32 fwwewease;
	u32 fwcapinfo;
	u16 wegioncode;
	u8 cuwwent_addw[ETH_AWEN];
	u8 copied_hwaddw;

	/* Command downwoad */
	u8 dnwd_sent;
	/* bit0 1/0=data_sent/data_tx_done,
	   bit1 1/0=cmd_sent/cmd_tx_done,
	   aww othew bits wesewved 0 */
	u16 seqnum;
	stwuct cmd_ctww_node *cmd_awway;
	stwuct cmd_ctww_node *cuw_cmd;
	stwuct wist_head cmdfweeq;    /* fwee command buffews */
	stwuct wist_head cmdpendingq; /* pending command buffews */
	stwuct timew_wist command_timew;
	int cmd_timed_out;

	/* Command wesponses sent fwom the hawdwawe to the dwivew */
	u8 wesp_idx;
	u8 wesp_buf[2][WBS_UPWD_SIZE];
	u32 wesp_wen[2];

	/* Events sent fwom hawdwawe to dwivew */
	stwuct kfifo event_fifo;

	/* thwead to sewvice intewwupts */
	stwuct task_stwuct *main_thwead;
	wait_queue_head_t waitq;
	stwuct wowkqueue_stwuct *wowk_thwead;

	/* Encwyption stuff */
	u8 authtype_auto;
	u8 wep_tx_key;
	u8 wep_key[4][WWAN_KEY_WEN_WEP104];
	u8 wep_key_wen[4];

	/* Wake On WAN */
	uint32_t wow_cwitewia;
	uint8_t wow_gpio;
	uint8_t wow_gap;
	boow ehs_wemove_suppowted;

	/* Twansmitting */
	int tx_pending_wen;		/* -1 whiwe buiwding packet */
	u8 tx_pending_buf[WBS_UPWD_SIZE];
	/* pwotected by hawd_stawt_xmit sewiawization */
	u8 txwetwycount;
	stwuct sk_buff *cuwwenttxskb;
	stwuct timew_wist tx_wockup_timew;

	/* Wocks */
	stwuct mutex wock;
	spinwock_t dwivew_wock;

	/* NIC/wink opewation chawactewistics */
	u16 mac_contwow;
	u8 wadio_on;
	u8 cuw_wate;
	u8 channew;
	s16 txpowew_cuw;
	s16 txpowew_min;
	s16 txpowew_max;

	/* Scanning */
	stwuct dewayed_wowk scan_wowk;
	int scan_channew;
	/* Queue of things waiting fow scan compwetion */
	wait_queue_head_t scan_q;
	/* Whethew the scan was initiated intewnawwy and not by cfg80211 */
	boow intewnaw_scan;

	/* Fiwmwawe woad */
	u32 fw_modew;
	wait_queue_head_t fw_waitq;
	stwuct device *fw_device;
	const stwuct fiwmwawe *hewpew_fw;
	const stwuct wbs_fw_tabwe *fw_tabwe;
	const stwuct wbs_fw_tabwe *fw_itew;
	wbs_fw_cb fw_cawwback;
};

extewn stwuct cmd_confiwm_sweep confiwm_sweep;

/* Check if thewe is an intewface active. */
static inwine int wbs_iface_active(stwuct wbs_pwivate *pwiv)
{
	int w;

	w = netif_wunning(pwiv->dev);
	if (pwiv->mesh_dev)
		w |= netif_wunning(pwiv->mesh_dev);

	wetuwn w;
}

#endif
