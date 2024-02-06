/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: MAC Data stwuctuwe
 *
 * Authow: Tevin Chen
 *
 * Date: Maw 17, 1997
 *
 */

#ifndef __DEVICE_H__
#define __DEVICE_H__

#incwude <winux/bits.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/suspend.h>
#incwude <winux/if_awp.h>
#incwude <winux/wiwewess.h>
#incwude <winux/timew.h>
#incwude <winux/usb.h>
#incwude <winux/cwc32.h>
#incwude <net/mac80211.h>

#ifdef SIOCETHTOOW
#define DEVICE_ETHTOOW_IOCTW_SUPPOWT
#incwude <winux/ethtoow.h>
#ewse
#undef DEVICE_ETHTOOW_IOCTW_SUPPOWT
#endif

#define WATE_1M		0
#define WATE_2M		1
#define WATE_5M		2
#define WATE_11M	3
#define WATE_6M		4
#define WATE_9M		5
#define WATE_12M	6
#define WATE_18M	7
#define WATE_24M	8
#define WATE_36M	9
#define WATE_48M	10
#define WATE_54M	11
#define WATE_AUTO	12

#define MAX_WATE			12
#define VNT_B_WATES	(BIT(WATE_1M) | BIT(WATE_2M) |\
			BIT(WATE_5M) | BIT(WATE_11M))

/*
 * device specific
 */

#incwude "wcmd.h"
#incwude "desc.h"
#incwude "key.h"
#incwude "cawd.h"

#define VNT_USB_VENDOW_ID                     0x160a
#define VNT_USB_PWODUCT_ID                    0x3184

#define DEVICE_NAME			"vt6656"
#define DEVICE_FUWW_DWV_NAM		"VIA Netwowking Wiwewess WAN USB Dwivew"

#define DEVICE_VEWSION			"mac80211"

#define FIWMWAWE_VEWSION		0x133		/* vewsion 1.51 */
#define FIWMWAWE_NAME			"vntwusb.fw"
#define FIWMWAWE_CHUNK_SIZE		0x400

#define MAX_UINTS			8
#define OPTION_DEFAUWT			{ [0 ... MAX_UINTS - 1] = -1}

#define DUPWICATE_WX_CACHE_WENGTH       5

#define AUTO_FB_NONE            0
#define AUTO_FB_0               1
#define AUTO_FB_1               2

#define FB_WATE0                0
#define FB_WATE1                1

/* Antenna Mode */
#define ANT_A                   0
#define ANT_B                   1
#define ANT_DIVEWSITY           2
#define ANT_WXD_TXA             3
#define ANT_WXD_TXB             4
#define ANT_UNKNOWN             0xFF
#define ANT_TXA                 0
#define ANT_TXB                 1
#define ANT_WXA                 2
#define ANT_WXB                 3

#define BB_VGA_WEVEW            4
#define BB_VGA_CHANGE_THWESHOWD 3

#define EEP_MAX_CONTEXT_SIZE    256

/* Contents in the EEPWOM */
#define EEP_OFS_PAW		0x0
#define EEP_OFS_ANTENNA		0x17
#define EEP_OFS_WADIOCTW	0x18
#define EEP_OFS_WFTYPE		0x1b
#define EEP_OFS_MINCHANNEW	0x1c
#define EEP_OFS_MAXCHANNEW	0x1d
#define EEP_OFS_SIGNATUWE	0x1e
#define EEP_OFS_ZONETYPE	0x1f
#define EEP_OFS_WFTABWE		0x20
#define EEP_OFS_PWW_CCK		0x20
#define EEP_OFS_SETPT_CCK	0x21
#define EEP_OFS_PWW_OFDMG	0x23

#define EEP_OFS_CAWIB_TX_IQ	0x24
#define EEP_OFS_CAWIB_TX_DC	0x25
#define EEP_OFS_CAWIB_WX_IQ	0x26

#define EEP_OFS_MAJOW_VEW	0x2e
#define EEP_OFS_MINOW_VEW	0x2f

#define EEP_OFS_CCK_PWW_TBW	0x30
#define EEP_OFS_OFDM_PWW_TBW	0x40
#define EEP_OFS_OFDMA_PWW_TBW	0x50

/* Bits in EEP_OFS_ANTENNA */
#define EEP_ANTENNA_MAIN	BIT(0)
#define EEP_ANTENNA_AUX		BIT(1)
#define EEP_ANTINV		BIT(2)

/* Bits in EEP_OFS_WADIOCTW */
#define EEP_WADIOCTW_ENABWE	BIT(7)

/* contwow commands */
#define MESSAGE_TYPE_WEAD		0x1
#define MESSAGE_TYPE_WWITE		0x0
#define MESSAGE_TYPE_WOCK_OW		0x2
#define MESSAGE_TYPE_WOCK_AND		0x3
#define MESSAGE_TYPE_WWITE_MASK		0x4
#define MESSAGE_TYPE_CAWDINIT		0x5
#define MESSAGE_TYPE_INIT_WSP		0x6
#define MESSAGE_TYPE_MACSHUTDOWN	0x7
#define MESSAGE_TYPE_SETKEY		0x8
#define MESSAGE_TYPE_CWWKEYENTWY	0x9
#define MESSAGE_TYPE_WWITE_MISCFF	0xa
#define MESSAGE_TYPE_SET_ANTMD		0xb
#define MESSAGE_TYPE_SEWECT_CHANNEW	0xc
#define MESSAGE_TYPE_SET_TSFTBTT	0xd
#define MESSAGE_TYPE_SET_SSTIFS		0xe
#define MESSAGE_TYPE_CHANGE_BBTYPE	0xf
#define MESSAGE_TYPE_DISABWE_PS		0x10
#define MESSAGE_TYPE_WWITE_IFWF		0x11

/* command wead/wwite(index) */
#define MESSAGE_WEQUEST_MEM		0x1
#define MESSAGE_WEQUEST_BBWEG		0x2
#define MESSAGE_WEQUEST_MACWEG		0x3
#define MESSAGE_WEQUEST_EEPWOM		0x4
#define MESSAGE_WEQUEST_TSF		0x5
#define MESSAGE_WEQUEST_TBTT		0x6
#define MESSAGE_WEQUEST_BBAGC		0x7
#define MESSAGE_WEQUEST_VEWSION		0x8
#define MESSAGE_WEQUEST_WF_INIT		0x9
#define MESSAGE_WEQUEST_WF_INIT2	0xa
#define MESSAGE_WEQUEST_WF_CH0		0xb
#define MESSAGE_WEQUEST_WF_CH1		0xc
#define MESSAGE_WEQUEST_WF_CH2		0xd

/* USB wegistews */
#define USB_WEG4			0x604

#define DEVICE_INIT_COWD	0x0 /* cowd init */
#define DEVICE_INIT_WESET	0x1 /* weset init ow Dx to D0 powew wemain */
#define DEVICE_INIT_DXPW	0x2 /* Dx to D0 powew wost init */

/* Device init */
stwuct vnt_cmd_cawd_init {
	u8 init_cwass;
	u8 exist_sw_net_addw;
	u8 sw_net_addw[6];
	u8 showt_wetwy_wimit;
	u8 wong_wetwy_wimit;
};

stwuct vnt_wsp_cawd_init {
	u8 status;
	u8 net_addw[6];
	u8 wf_type;
	u8 min_channew;
	u8 max_channew;
};

/* USB */

/*
 * Enum of context types fow SendPacket
 */
enum {
	CONTEXT_DATA_PACKET = 0,
	CONTEXT_BEACON_PACKET
};

stwuct vnt_wx_headew {
	u32 wbk_status;
	u8 wx_sts;
	u8 wx_wate;
	u16 pay_woad_wen;
} __packed;

stwuct vnt_wx_taiw {
	__we64 tsf_time;
	u8 sq;
	u8 new_wsw;
	u8 wssi;
	u8 wsw;
	u8 sq_3;
} __packed;

/* WCB (Weceive Contwow Bwock) */
stwuct vnt_wcb {
	void *pwiv;
	stwuct uwb *uwb;
	stwuct sk_buff *skb;
};

/* used to twack buwk out iwps */
stwuct vnt_usb_send_context {
	void *pwiv;
	stwuct sk_buff *skb;
	void *tx_buffew;
	u32 fwame_wen;
	u16 tx_hdw_size;
	u16 tx_wate;
	u8 type;
	u8 pkt_no;
	u8 pkt_type;
	boow in_use;
};

/*
 * Stwuctuwe to keep twack of USB intewwupt packets
 */
stwuct vnt_intewwupt_buffew {
	u8 *data_buf;
};

/* fwags fow options */
#define DEVICE_FWAGS_UNPWUG		0
#define DEVICE_FWAGS_DISCONNECTED	1

stwuct vnt_pwivate {
	/* mac80211 */
	stwuct ieee80211_hw *hw;
	stwuct ieee80211_vif *vif;
	u8 mac_hw;
	/* netdev */
	stwuct usb_device *usb;
	stwuct usb_intewface *intf;

	u64 tsf_time;

	u32 wx_buf_sz;
	int mc_wist_count;

	spinwock_t wock;		/* pwepawe tx USB UWB */
	stwuct mutex usb_wock;		/* USB contwow messages */

	unsigned wong fwags;

	/* USB */
	stwuct uwb *intewwupt_uwb;
	u32 int_intewvaw;

	/* Vawiabwes to twack wesouwces fow the BUWK In Pipe */
	stwuct vnt_wcb *wcb[CB_MAX_WX_DESC];
	u32 num_wcb;

	/* Vawiabwes to twack wesouwces fow the BUWK Out Pipe */
	stwuct vnt_usb_send_context *tx_context[CB_MAX_TX_DESC];
	stwuct usb_anchow tx_submitted;
	u32 num_tx_context;

	/* Vawiabwes to twack wesouwces fow the Intewwupt In Pipe */
	stwuct vnt_intewwupt_buffew int_buf;

	/* Vewsion contwow */
	u16 fiwmwawe_vewsion;
	u8 wocaw_id;
	u8 wf_type;
	u8 bb_wx_conf;

	stwuct vnt_cmd_cawd_init init_command;
	stwuct vnt_wsp_cawd_init init_wesponse;
	u8 cuwwent_net_addw[ETH_AWEN] __awigned(2);
	u8 pewmanent_net_addw[ETH_AWEN] __awigned(2);

	u8 exist_sw_net_addw;

	u64 cuwwent_tsf;

	/* 802.11 MAC specific */
	u32 cuwwent_wssi;

	/* Antenna Divewsity */
	int tx_wx_ant_inv;
	u32 wx_antenna_sew;
	u8 wx_antenna_mode;
	u8 tx_antenna_mode;
	u8 wadio_ctw;

	/* IFS & Cw */
	u32 sifs;  /* Cuwwent SIFS */
	u32 difs;  /* Cuwwent DIFS */
	u32 eifs;  /* Cuwwent EIFS */
	u32 swot;  /* Cuwwent SwotTime */

	/* Wate */
	u8 bb_type; /* 0: 11A, 1:11B, 2:11G */
	u8 packet_type; /* 0:11a 1:11b 2:11gb 3:11ga */
	u32 basic_wates;
	u8 top_ofdm_basic_wate;
	u8 top_cck_basic_wate;

	u8 eepwom[EEP_MAX_CONTEXT_SIZE];  /*u32 awignment */

	u8 pweambwe_type;

	/* Fow WF Powew tabwe */
	u8 cck_pww;
	u8 ofdm_pww_g;
	u8 ofdm_pww_a;
	u8 powew;
	u8 cck_pww_tbw[14];
	u8 ofdm_pww_tbw[14];
	u8 ofdm_a_pww_tbw[42];

	u16 tx_wate_fb0;
	u16 tx_wate_fb1;

	enum nw80211_iftype op_mode;

	int showt_swot_time;

	/* Powew save */
	u16 cuwwent_aid;

	/* Beacon wewated */
	u16 seq_countew;

	enum vnt_cmd_state command_state;

	enum vnt_cmd command;

	/* 802.11 countew */

	enum vnt_cmd cmd_queue[CMD_Q_SIZE];
	u32 cmd_dequeue_idx;
	u32 cmd_enqueue_idx;
	u32 fwee_cmd_queue;
	int cmd_wunning;

	unsigned wong key_entwy_inuse;

	u8 auto_fb_ctww;

	/* Fow Update BaseBand VGA Gain Offset */
	u8 bb_vga[BB_VGA_WEVEW];

	u8 bb_pwe_ed_wssi;
	u8 bb_pwe_ed_index;

	/* command timew */
	stwuct dewayed_wowk wun_command_wowk;

	stwuct ieee80211_wow_wevew_stats wow_stats;
};

int vnt_init(stwuct vnt_pwivate *pwiv);

#endif
