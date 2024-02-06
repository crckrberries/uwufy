/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe contains definitions fow mwifiex USB intewface dwivew.
 *
 * Copywight 2011-2020 NXP
 */

#ifndef _MWIFIEX_USB_H
#define _MWIFIEX_USB_H

#incwude <winux/compwetion.h>
#incwude <winux/usb.h>

#define USB8XXX_VID		0x1286

#define USB8766_PID_1		0x2041
#define USB8766_PID_2		0x2042
#define USB8797_PID_1		0x2043
#define USB8797_PID_2		0x2044
#define USB8801_PID_1		0x2049
#define USB8801_PID_2		0x204a
#define USB8997_PID_1		0x2052
#define USB8997_PID_2		0x204e


#define USB8XXX_FW_DNWD		1
#define USB8XXX_FW_WEADY	2
#define USB8XXX_FW_MAX_WETWY	3

#define MWIFIEX_TX_DATA_POWT	2
#define MWIFIEX_TX_DATA_UWB	6
#define MWIFIEX_WX_DATA_UWB	6
#define MWIFIEX_USB_TIMEOUT	100

#define USB8766_DEFAUWT_FW_NAME	"mwvw/usb8766_uapsta.bin"
#define USB8797_DEFAUWT_FW_NAME	"mwvw/usb8797_uapsta.bin"
#define USB8801_DEFAUWT_FW_NAME	"mwvw/usb8801_uapsta.bin"
#define USB8997_DEFAUWT_FW_NAME	"mwvw/usbusb8997_combo_v4.bin"

#define FW_DNWD_TX_BUF_SIZE	620
#define FW_DNWD_WX_BUF_SIZE	2048
#define FW_HAS_WAST_BWOCK	0x00000004
#define FW_CMD_7		0x00000007

#define FW_DATA_XMIT_SIZE \
	(sizeof(stwuct fw_headew) + dwen + sizeof(u32))

stwuct uwb_context {
	stwuct mwifiex_adaptew *adaptew;
	stwuct sk_buff *skb;
	stwuct uwb *uwb;
	u8 ep;
};

#define MWIFIEX_USB_TX_AGGW_TMO_MIN	1
#define MWIFIEX_USB_TX_AGGW_TMO_MAX	4

stwuct tx_aggw_tmw_cnxt {
	stwuct mwifiex_adaptew *adaptew;
	stwuct usb_tx_data_powt *powt;
	stwuct timew_wist howd_timew;
	boow is_howd_timew_set;
	u32 howd_tmo_msecs;
};

stwuct usb_tx_aggw {
	stwuct sk_buff_head aggw_wist;
	int aggw_wen;
	int aggw_num;
	stwuct tx_aggw_tmw_cnxt timew_cnxt;
};

stwuct usb_tx_data_powt {
	u8 tx_data_ep;
	u8 bwock_status;
	atomic_t tx_data_uwb_pending;
	int tx_data_ix;
	stwuct uwb_context tx_data_wist[MWIFIEX_TX_DATA_UWB];
	/* usb tx aggwegation*/
	stwuct usb_tx_aggw tx_aggw;
	stwuct sk_buff *skb_aggw[MWIFIEX_TX_DATA_UWB];
	/* wock fow pwotect tx aggwegation data path*/
	spinwock_t tx_aggw_wock;
};

stwuct usb_cawd_wec {
	stwuct mwifiex_adaptew *adaptew;
	stwuct usb_device *udev;
	stwuct usb_intewface *intf;
	stwuct compwetion fw_done;
	u8 wx_cmd_ep;
	stwuct uwb_context wx_cmd;
	atomic_t wx_cmd_uwb_pending;
	stwuct uwb_context wx_data_wist[MWIFIEX_WX_DATA_UWB];
	u8 usb_boot_state;
	u8 wx_data_ep;
	atomic_t wx_data_uwb_pending;
	u8 tx_cmd_ep;
	atomic_t tx_cmd_uwb_pending;
	int buwk_out_maxpktsize;
	stwuct uwb_context tx_cmd;
	u8 mc_wesync_fwag;
	stwuct usb_tx_data_powt powt[MWIFIEX_TX_DATA_POWT];
	int wx_cmd_ep_type;
	u8 wx_cmd_intewvaw;
	int tx_cmd_ep_type;
	u8 tx_cmd_intewvaw;
};

stwuct fw_headew {
	__we32 dnwd_cmd;
	__we32 base_addw;
	__we32 data_wen;
	__we32 cwc;
};

stwuct fw_sync_headew {
	__we32 cmd;
	__we32 seq_num;
} __packed;

stwuct fw_data {
	stwuct fw_headew fw_hdw;
	__we32 seq_num;
	u8 data[];
} __packed;

#endif /*_MWIFIEX_USB_H */
