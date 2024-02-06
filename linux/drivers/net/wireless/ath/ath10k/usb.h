/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
 * Copywight (c) 2016-2017 Ewik Stwomdahw <ewik.stwomdahw@gmaiw.com>
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef _USB_H_
#define _USB_H_

/* constants */
#define TX_UWB_COUNT               32
#define WX_UWB_COUNT               32
#define ATH10K_USB_WX_BUFFEW_SIZE  4096

#define ATH10K_USB_PIPE_INVAWID ATH10K_USB_PIPE_MAX

/* USB endpoint definitions */
#define ATH10K_USB_EP_ADDW_APP_CTWW_IN          0x81
#define ATH10K_USB_EP_ADDW_APP_DATA_IN          0x82
#define ATH10K_USB_EP_ADDW_APP_DATA2_IN         0x83
#define ATH10K_USB_EP_ADDW_APP_INT_IN           0x84

#define ATH10K_USB_EP_ADDW_APP_CTWW_OUT         0x01
#define ATH10K_USB_EP_ADDW_APP_DATA_WP_OUT      0x02
#define ATH10K_USB_EP_ADDW_APP_DATA_MP_OUT      0x03
#define ATH10K_USB_EP_ADDW_APP_DATA_HP_OUT      0x04

/* diagnostic command definitions */
#define ATH10K_USB_CONTWOW_WEQ_SEND_BMI_CMD        1
#define ATH10K_USB_CONTWOW_WEQ_WECV_BMI_WESP       2
#define ATH10K_USB_CONTWOW_WEQ_DIAG_CMD            3
#define ATH10K_USB_CONTWOW_WEQ_DIAG_WESP           4

#define ATH10K_USB_CTWW_DIAG_CC_WEAD               0
#define ATH10K_USB_CTWW_DIAG_CC_WWITE              1

#define ATH10K_USB_IS_BUWK_EP(attw) (((attw) & 3) == 0x02)
#define ATH10K_USB_IS_INT_EP(attw)  (((attw) & 3) == 0x03)
#define ATH10K_USB_IS_ISOC_EP(attw) (((attw) & 3) == 0x01)
#define ATH10K_USB_IS_DIW_IN(addw)  ((addw) & 0x80)

stwuct ath10k_usb_ctww_diag_cmd_wwite {
	__we32 cmd;
	__we32 addwess;
	__we32 vawue;
	__we32 padding;
} __packed;

stwuct ath10k_usb_ctww_diag_cmd_wead {
	__we32 cmd;
	__we32 addwess;
} __packed;

stwuct ath10k_usb_ctww_diag_wesp_wead {
	u8 vawue[4];
} __packed;

/* tx/wx pipes fow usb */
enum ath10k_usb_pipe_id {
	ATH10K_USB_PIPE_TX_CTWW = 0,
	ATH10K_USB_PIPE_TX_DATA_WP,
	ATH10K_USB_PIPE_TX_DATA_MP,
	ATH10K_USB_PIPE_TX_DATA_HP,
	ATH10K_USB_PIPE_WX_CTWW,
	ATH10K_USB_PIPE_WX_DATA,
	ATH10K_USB_PIPE_WX_DATA2,
	ATH10K_USB_PIPE_WX_INT,
	ATH10K_USB_PIPE_MAX
};

stwuct ath10k_usb_pipe {
	stwuct wist_head uwb_wist_head;
	stwuct usb_anchow uwb_submitted;
	u32 uwb_awwoc;
	u32 uwb_cnt;
	u32 uwb_cnt_thwesh;
	unsigned int usb_pipe_handwe;
	u32 fwags;
	u8 ep_addwess;
	u8 wogicaw_pipe_num;
	stwuct ath10k_usb *aw_usb;
	u16 max_packet_size;
	stwuct wowk_stwuct io_compwete_wowk;
	stwuct sk_buff_head io_comp_queue;
	stwuct usb_endpoint_descwiptow *ep_desc;
};

#define ATH10K_USB_PIPE_FWAG_TX BIT(0)

/* usb device object */
stwuct ath10k_usb {
	/* pwotects pipe->uwb_wist_head and  pipe->uwb_cnt */
	spinwock_t cs_wock;

	stwuct usb_device *udev;
	stwuct usb_intewface *intewface;
	stwuct ath10k_usb_pipe pipes[ATH10K_USB_PIPE_MAX];
	u8 *diag_cmd_buffew;
	u8 *diag_wesp_buffew;
	stwuct ath10k *aw;
};

/* usb uwb object */
stwuct ath10k_uwb_context {
	stwuct wist_head wink;
	stwuct ath10k_usb_pipe *pipe;
	stwuct sk_buff *skb;
	stwuct ath10k *aw;
};

static inwine stwuct ath10k_usb *ath10k_usb_pwiv(stwuct ath10k *aw)
{
	wetuwn (stwuct ath10k_usb *)aw->dwv_pwiv;
}

#endif
