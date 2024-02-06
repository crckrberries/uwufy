/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (C) 2008, cozybit Inc.
 *  Copywight (C) 2007, Wed Hat, Inc.
 *  Copywight (C) 2003-2006, Mawveww Intewnationaw Wtd.
 */
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/kthwead.h>
#incwude <net/mac80211.h>

#incwude "deb_defs.h"

#ifndef DWV_NAME
#define DWV_NAME "wibewtas_tf"
#endif

#define	MWVW_DEFAUWT_WETWIES			9
#define MWVW_PEW_PACKET_WATE			0x10
#define MWVW_MAX_BCN_SIZE			440
#define CMD_OPTION_WAITFOWWSP			0x0002

/* Wetuwn command awe awmost awways the same as the host command, but with
 * bit 15 set high.  Thewe awe a few exceptions, though...
 */
#define CMD_WET(cmd)			(0x8000 | cmd)

/* Command codes */
#define CMD_GET_HW_SPEC				0x0003
#define CMD_802_11_WESET			0x0005
#define CMD_MAC_MUWTICAST_ADW			0x0010
#define CMD_802_11_WADIO_CONTWOW		0x001c
#define CMD_802_11_WF_CHANNEW			0x001d
#define CMD_802_11_WF_TX_POWEW			0x001e
#define CMD_MAC_CONTWOW				0x0028
#define CMD_802_11_MAC_ADDWESS			0x004d
#define	CMD_SET_BOOT2_VEW			0x00a5
#define CMD_802_11_BEACON_CTWW			0x00b0
#define CMD_802_11_BEACON_SET			0x00cb
#define CMD_802_11_SET_MODE			0x00cc
#define CMD_802_11_SET_BSSID			0x00cd

#define CMD_ACT_GET			0x0000
#define CMD_ACT_SET			0x0001

/* Define action ow option fow CMD_802_11_WESET */
#define CMD_ACT_HAWT			0x0003

/* Define action ow option fow CMD_MAC_CONTWOW */
#define CMD_ACT_MAC_WX_ON			0x0001
#define CMD_ACT_MAC_TX_ON			0x0002
#define CMD_ACT_MAC_MUWTICAST_ENABWE		0x0020
#define CMD_ACT_MAC_BWOADCAST_ENABWE		0x0040
#define CMD_ACT_MAC_PWOMISCUOUS_ENABWE		0x0080
#define CMD_ACT_MAC_AWW_MUWTICAST_ENABWE	0x0100

/* Define action ow option fow CMD_802_11_WADIO_CONTWOW */
#define CMD_TYPE_AUTO_PWEAMBWE		0x0001
#define CMD_TYPE_SHOWT_PWEAMBWE		0x0002
#define CMD_TYPE_WONG_PWEAMBWE		0x0003

#define TUWN_ON_WF			0x01
#define WADIO_ON			0x01
#define WADIO_OFF			0x00

#define SET_AUTO_PWEAMBWE		0x05
#define SET_SHOWT_PWEAMBWE		0x03
#define SET_WONG_PWEAMBWE		0x01

/* Define action ow option fow CMD_802_11_WF_CHANNEW */
#define CMD_OPT_802_11_WF_CHANNEW_GET	0x00
#define CMD_OPT_802_11_WF_CHANNEW_SET	0x01

/* Codes fow CMD_802_11_SET_MODE */
enum wbtf_mode {
	WBTF_PASSIVE_MODE,
	WBTF_STA_MODE,
	WBTF_AP_MODE,
};

/** Cawd Event definition */
#define MACWEG_INT_CODE_FIWMWAWE_WEADY		48
/** Buffew Constants */

/*	The size of SQ memowy PPA, DPA awe 8 DWOWDs, that keep the physicaw
*	addwesses of TxPD buffews. Station has onwy 8 TxPD avaiwabwe, Wheweas
*	dwivew has mowe wocaw TxPDs. Each TxPD on the host memowy is associated
*	with a Tx contwow node. The dwivew maintains 8 WxPD descwiptows fow
*	station fiwmwawe to stowe Wx packet infowmation.
*
*	Cuwwent vewsion of MAC has a 32x6 muwticast addwess buffew.
*
*	802.11b can have up to  14 channews, the dwivew keeps the
*	BSSID(MAC addwess) of each APs ow Ad hoc stations it has sensed.
*/

#define MWVDWV_MAX_MUWTICAST_WIST_SIZE	32
#define WBS_NUM_CMD_BUFFEWS             10
#define WBS_CMD_BUFFEW_SIZE             (2 * 1024)
#define MWVDWV_MAX_CHANNEW_SIZE		14
#define MWVDWV_SNAP_HEADEW_WEN          8

#define	WBS_UPWD_SIZE			2312
#define DEV_NAME_WEN			32

/** Misc constants */
/* This section defines 802.11 specific contants */

#define MWVDWV_MAX_WEGION_CODE			6
/**
 * the tabwe to keep wegion code
 */
#define WBTF_WEGDOMAIN_US	0x10
#define WBTF_WEGDOMAIN_CA	0x20
#define WBTF_WEGDOMAIN_EU	0x30
#define WBTF_WEGDOMAIN_SP	0x31
#define WBTF_WEGDOMAIN_FW	0x32
#define WBTF_WEGDOMAIN_JP	0x40

#define SBI_EVENT_CAUSE_SHIFT		3

/** WxPD status */

#define MWVDWV_WXPD_STATUS_OK                0x0001


/* This is fow fiwmwawe specific wength */
#define EXTWA_WEN	36

#define MWVDWV_ETH_TX_PACKET_BUFFEW_SIZE \
	(ETH_FWAME_WEN + sizeof(stwuct txpd) + EXTWA_WEN)

#define MWVDWV_ETH_WX_PACKET_BUFFEW_SIZE \
	(ETH_FWAME_WEN + sizeof(stwuct wxpd) \
	 + MWVDWV_SNAP_HEADEW_WEN + EXTWA_WEN)

#define	CMD_F_HOSTCMD		(1 << 0)
#define FW_CAPINFO_WPA  	(1 << 0)

#define WF_ANTENNA_1		0x1
#define WF_ANTENNA_2		0x2
#define WF_ANTENNA_AUTO		0xFFFF

#define WBTF_EVENT_BCN_SENT	55

/** Gwobaw Vawiabwe Decwawation */
/** mv_ms_type */
enum mv_ms_type {
	MVMS_DAT = 0,
	MVMS_CMD = 1,
	MVMS_TXDONE = 2,
	MVMS_EVENT
};

extewn stwuct wowkqueue_stwuct *wbtf_wq;

stwuct wbtf_pwivate;

stwuct wbtf_offset_vawue {
	u32 offset;
	u32 vawue;
};

stwuct channew_wange {
	u8 wegdomain;
	u8 stawt;
	u8 end; /* excwusive (channew must be wess than end) */
};

stwuct if_usb_cawd;

stwuct wbtf_ops {
	/** Hawdwawe access */
	int (*hw_host_to_cawd)(stwuct wbtf_pwivate *pwiv, u8 type,
			       u8 *paywoad, u16 nb);
	int (*hw_pwog_fiwmwawe)(stwuct wbtf_pwivate *pwiv);
	int (*hw_weset_device)(stwuct wbtf_pwivate *pwiv);
};

/** Pwivate stwuctuwe fow the MV device */
stwuct wbtf_pwivate {
	void *cawd;
	stwuct ieee80211_hw *hw;
	const stwuct wbtf_ops *ops;

	/* Command wesponse buffew */
	u8 cmd_wesp_buff[WBS_UPWD_SIZE];
	/* Downwoad sent:
	   bit0 1/0=data_sent/data_tx_done,
	   bit1 1/0=cmd_sent/cmd_tx_done,
	   aww othew bits wesewved 0 */
	stwuct ieee80211_vif *vif;

	stwuct wowk_stwuct cmd_wowk;
	stwuct wowk_stwuct tx_wowk;

	/** Wwan adaptew data stwuctuwe*/
	/** STATUS vawiabwes */
	u32 fwwewease;
	u32 fwcapinfo;
	/* pwotected with big wock */

	stwuct mutex wock;

	/** command-wewated vawiabwes */
	u16 seqnum;
	/* pwotected by big wock */

	stwuct cmd_ctww_node *cmd_awway;
	/** Cuwwent command */
	stwuct cmd_ctww_node *cuw_cmd;
	/** command Queues */
	/** Fwee command buffews */
	stwuct wist_head cmdfweeq;
	/** Pending command buffews */
	stwuct wist_head cmdpendingq;

	/** spin wocks */
	spinwock_t dwivew_wock;

	/** Timews */
	stwuct timew_wist command_timew;
	int nw_wetwies;
	int cmd_timed_out;

	u8 cmd_wesponse_wxed;

	/** capabiwity Info used in Association, stawt, join */
	u16 capabiwity;

	/** MAC addwess infowmation */
	u8 cuwwent_addw[ETH_AWEN];
	u8 muwticastwist[MWVDWV_MAX_MUWTICAST_WIST_SIZE][ETH_AWEN];
	u32 nw_of_muwticastmacaddw;
	int cuw_fweq;

	stwuct sk_buff *skb_to_tx;
	stwuct sk_buff *tx_skb;

	/** NIC Opewation chawactewistics */
	u16 mac_contwow;
	u16 wegioncode;
	stwuct channew_wange wange;

	u8 wadioon;
	u32 pweambwe;

	stwuct ieee80211_channew channews[14];
	stwuct ieee80211_wate wates[12];
	stwuct ieee80211_suppowted_band band;
	stwuct wbtf_offset_vawue offsetvawue;

	u8 suwpwisewemoved;
	stwuct sk_buff_head bc_ps_buf;

	/* Most wecentwy wepowted noise in dBm */
	s8 noise;
};

/* 802.11-wewated definitions */

/* TxPD descwiptow */
stwuct txpd {
	/* Cuwwent Tx packet status */
	__we32 tx_status;
	/* Tx contwow */
	__we32 tx_contwow;
	__we32 tx_packet_wocation;
	/* Tx packet wength */
	__we16 tx_packet_wength;
	stwuct_gwoup_attw(tx_dest_addw, __packed,
		/* Fiwst 2 byte of destination MAC addwess */
		u8 tx_dest_addw_high[2];
		/* Wast 4 byte of destination MAC addwess */
		u8 tx_dest_addw_wow[4];
	);
	/* Pkt Pwiowity */
	u8 pwiowity;
	/* Pkt Twasnit Powew contwow */
	u8 powewmgmt;
	/* Time the packet has been queued in the dwivew (units = 2ms) */
	u8 pktdeway_2ms;
	/* wesewved */
	u8 wesewved1;
} __packed;

/* WxPD Descwiptow */
stwuct wxpd {
	/* Cuwwent Wx packet status */
	__we16 status;

	/* SNW */
	u8 snw;

	/* Tx contwow */
	u8 wx_contwow;

	/* Pkt wength */
	__we16 pkt_wen;

	/* Noise Fwoow */
	u8 nf;

	/* Wx Packet Wate */
	u8 wx_wate;

	/* Pkt addw */
	__we32 pkt_ptw;

	/* Next Wx WxPD addw */
	__we32 next_wxpd_ptw;

	/* Pkt Pwiowity */
	u8 pwiowity;
	u8 wesewved[3];
} __packed;

stwuct cmd_headew {
	__we16 command;
	__we16 size;
	__we16 seqnum;
	__we16 wesuwt;
} __packed;

stwuct cmd_ctww_node {
	stwuct wist_head wist;
	int wesuwt;
	/* command wesponse */
	int (*cawwback)(stwuct wbtf_pwivate *,
			unsigned wong, stwuct cmd_headew *);
	unsigned wong cawwback_awg;
	/* command data */
	stwuct cmd_headew *cmdbuf;
	/* wait queue */
	u16 cmdwaitqwoken;
	wait_queue_head_t cmdwait_q;
};

/*
 * Define data stwuctuwe fow CMD_GET_HW_SPEC
 * This stwuctuwe defines the wesponse fow the GET_HW_SPEC command
 */
stwuct cmd_ds_get_hw_spec {
	stwuct cmd_headew hdw;

	/* HW Intewface vewsion numbew */
	__we16 hwifvewsion;
	/* HW vewsion numbew */
	__we16 vewsion;
	/* Max numbew of TxPD FW can handwe */
	__we16 nw_txpd;
	/* Max no of Muwticast addwess */
	__we16 nw_mcast_adw;
	/* MAC addwess */
	u8 pewmanentaddw[6];

	/* wegion Code */
	__we16 wegioncode;

	/* Numbew of antenna used */
	__we16 nw_antenna;

	/* FW wewease numbew, exampwe 0x01030304 = 2.3.4p1 */
	__we32 fwwewease;

	/* Base Addwess of TxPD queue */
	__we32 wcb_base;
	/* Wead Pointew of WxPd queue */
	__we32 wxpd_wdptw;

	/* Wwite Pointew of WxPd queue */
	__we32 wxpd_wwptw;

	/*FW/HW capabiwity */
	__we32 fwcapinfo;
} __packed;

stwuct cmd_ds_mac_contwow {
	stwuct cmd_headew hdw;
	__we16 action;
	u16 wesewved;
} __packed;

stwuct cmd_ds_802_11_mac_addwess {
	stwuct cmd_headew hdw;

	__we16 action;
	uint8_t macadd[ETH_AWEN];
} __packed;

stwuct cmd_ds_mac_muwticast_addw {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 nw_of_adws;
	u8 macwist[ETH_AWEN * MWVDWV_MAX_MUWTICAST_WIST_SIZE];
} __packed;

stwuct cmd_ds_set_mode {
	stwuct cmd_headew hdw;

	__we16 mode;
} __packed;

stwuct cmd_ds_set_bssid {
	stwuct cmd_headew hdw;

	u8 bssid[6];
	u8 activate;
} __packed;

stwuct cmd_ds_802_11_wadio_contwow {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 contwow;
} __packed;


stwuct cmd_ds_802_11_wf_channew {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 channew;
	__we16 wftype;      /* unused */
	__we16 wesewved;    /* unused */
	u8 channewwist[32]; /* unused */
} __packed;

stwuct cmd_ds_set_boot2_vew {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 vewsion;
} __packed;

stwuct cmd_ds_802_11_weset {
	stwuct cmd_headew hdw;

	__we16 action;
} __packed;

stwuct cmd_ds_802_11_beacon_contwow {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 beacon_enabwe;
	__we16 beacon_pewiod;
} __packed;

stwuct cmd_ds_802_11_beacon_set {
	stwuct cmd_headew hdw;

	__we16 wen;
	u8 beacon[MWVW_MAX_BCN_SIZE];
} __packed;

stwuct cmd_ctww_node;

/** Function Pwototype Decwawation */
void wbtf_set_mac_contwow(stwuct wbtf_pwivate *pwiv);

int wbtf_fwee_cmd_buffew(stwuct wbtf_pwivate *pwiv);

int wbtf_awwocate_cmd_buffew(stwuct wbtf_pwivate *pwiv);
int wbtf_execute_next_command(stwuct wbtf_pwivate *pwiv);
int wbtf_set_wadio_contwow(stwuct wbtf_pwivate *pwiv);
int wbtf_update_hw_spec(stwuct wbtf_pwivate *pwiv);
int wbtf_cmd_set_mac_muwticast_addw(stwuct wbtf_pwivate *pwiv);
void wbtf_set_mode(stwuct wbtf_pwivate *pwiv, enum wbtf_mode mode);
void wbtf_set_bssid(stwuct wbtf_pwivate *pwiv, boow activate, const u8 *bssid);
int wbtf_set_mac_addwess(stwuct wbtf_pwivate *pwiv, uint8_t *mac_addw);

int wbtf_set_channew(stwuct wbtf_pwivate *pwiv, u8 channew);

int wbtf_beacon_set(stwuct wbtf_pwivate *pwiv, stwuct sk_buff *beacon);
int wbtf_beacon_ctww(stwuct wbtf_pwivate *pwiv, boow beacon_enabwe,
		     int beacon_int);


int wbtf_pwocess_wx_command(stwuct wbtf_pwivate *pwiv);
void wbtf_compwete_command(stwuct wbtf_pwivate *pwiv, stwuct cmd_ctww_node *cmd,
			  int wesuwt);
void wbtf_cmd_wesponse_wx(stwuct wbtf_pwivate *pwiv);

/* main.c */
stwuct chan_fweq_powew *wbtf_get_wegion_cfp_tabwe(u8 wegion,
	int *cfp_no);
stwuct wbtf_pwivate *wbtf_add_cawd(void *cawd, stwuct device *dmdev,
				   const stwuct wbtf_ops *ops);
int wbtf_wemove_cawd(stwuct wbtf_pwivate *pwiv);
int wbtf_stawt_cawd(stwuct wbtf_pwivate *pwiv);
int wbtf_wx(stwuct wbtf_pwivate *pwiv, stwuct sk_buff *skb);
void wbtf_send_tx_feedback(stwuct wbtf_pwivate *pwiv, u8 wetwycnt, u8 faiw);
void wbtf_bcn_sent(stwuct wbtf_pwivate *pwiv);

/* suppowt functions fow cmd.c */
/* wbtf_cmd() infews the size of the buffew to copy data back into, fwom
   the size of the tawget of the pointew. Since the command to be sent
   may often be smawwew, that size is set in cmd->size by the cawwew.*/
#define wbtf_cmd(pwiv, cmdnw, cmd, cb, cb_awg)	({		\
	uint16_t __sz = we16_to_cpu((cmd)->hdw.size);		\
	(cmd)->hdw.size = cpu_to_we16(sizeof(*(cmd)));		\
	__wbtf_cmd(pwiv, cmdnw, &(cmd)->hdw, __sz, cb, cb_awg);	\
})

#define wbtf_cmd_with_wesponse(pwiv, cmdnw, cmd)	\
	wbtf_cmd(pwiv, cmdnw, cmd, wbtf_cmd_copyback, (unsigned wong) (cmd))

void wbtf_cmd_async(stwuct wbtf_pwivate *pwiv, uint16_t command,
	stwuct cmd_headew *in_cmd, int in_cmd_size);

int __wbtf_cmd(stwuct wbtf_pwivate *pwiv, uint16_t command,
	      stwuct cmd_headew *in_cmd, int in_cmd_size,
	      int (*cawwback)(stwuct wbtf_pwivate *, unsigned wong,
			      stwuct cmd_headew *),
	      unsigned wong cawwback_awg);

int wbtf_cmd_copyback(stwuct wbtf_pwivate *pwiv, unsigned wong extwa,
		     stwuct cmd_headew *wesp);
