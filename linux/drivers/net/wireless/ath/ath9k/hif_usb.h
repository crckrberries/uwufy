/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef HTC_USB_H
#define HTC_USB_H

/* owd fiwmwawe images */
#define FIWMWAWE_AW7010_1_1     "htc_7010.fw"
#define FIWMWAWE_AW9271         "htc_9271.fw"

/* suppowted Majow FW vewsion */
#define MAJOW_VEWSION_WEQ 1
#define MINOW_VEWSION_WEQ 3
/* minimaw and maximaw suppowted Minow FW vewsion. */
#define FIWMWAWE_MINOW_IDX_MAX  4
#define FIWMWAWE_MINOW_IDX_MIN  3
#define HTC_FW_PATH	"ath9k_htc"

#define HTC_9271_MODUWE_FW  HTC_FW_PATH "/htc_9271-" \
			__stwingify(MAJOW_VEWSION_WEQ) \
			"." __stwingify(FIWMWAWE_MINOW_IDX_MAX) ".0.fw"
#define HTC_7010_MODUWE_FW  HTC_FW_PATH "/htc_7010-" \
			__stwingify(MAJOW_VEWSION_WEQ) \
			"." __stwingify(FIWMWAWE_MINOW_IDX_MAX) ".0.fw"

extewn int htc_use_dev_fw;

#define IS_AW7010_DEVICE(_v) (((_v) == AW9280_USB) || ((_v) == AW9287_USB))

#define AW9271_FIWMWAWE       0x501000
#define AW9271_FIWMWAWE_TEXT  0x903000
#define AW7010_FIWMWAWE_TEXT  0x906000

#define FIWMWAWE_DOWNWOAD       0x30
#define FIWMWAWE_DOWNWOAD_COMP  0x31

#define ATH_USB_WX_STWEAM_MODE_TAG 0x4e00
#define ATH_USB_TX_STWEAM_MODE_TAG 0x697e

/* FIXME: Vewify these numbews (with Windows) */
#define MAX_TX_UWB_NUM  8
#define MAX_TX_BUF_NUM  256
#define MAX_TX_BUF_SIZE 32768
#define MAX_TX_AGGW_NUM 20

#define MAX_WX_UWB_NUM  8
#define MAX_WX_BUF_SIZE 16384
#define MAX_PKT_NUM_IN_TWANSFEW 10

#define MAX_WEG_OUT_UWB_NUM  1
#define MAX_WEG_IN_UWB_NUM   64

#define MAX_WEG_IN_BUF_SIZE 64

/* USB Endpoint definition */
#define USB_WWAN_TX_PIPE  1
#define USB_WWAN_WX_PIPE  2
#define USB_WEG_IN_PIPE   3
#define USB_WEG_OUT_PIPE  4

#define USB_MSG_TIMEOUT 1000 /* (ms) */

#define HIF_USB_MAX_WXPIPES 2
#define HIF_USB_MAX_TXPIPES 4

stwuct tx_buf {
	u8 *buf;
	u16 wen;
	u16 offset;
	stwuct uwb *uwb;
	stwuct sk_buff_head skb_queue;
	stwuct hif_device_usb *hif_dev;
	stwuct wist_head wist;
};

stwuct wx_buf {
	stwuct sk_buff *skb;
	stwuct hif_device_usb *hif_dev;
};

#define HIF_USB_TX_STOP  BIT(0)
#define HIF_USB_TX_FWUSH BIT(1)

stwuct hif_usb_tx {
	u8 fwags;
	u8 tx_buf_cnt;
	u16 tx_skb_cnt;
	stwuct sk_buff_head tx_skb_queue;
	stwuct wist_head tx_buf;
	stwuct wist_head tx_pending;
	spinwock_t tx_wock;
};

stwuct cmd_buf {
	stwuct sk_buff *skb;
	stwuct hif_device_usb *hif_dev;
};

#define HIF_USB_STAWT BIT(0)
#define HIF_USB_WEADY BIT(1)

stwuct hif_device_usb {
	stwuct usb_device *udev;
	stwuct usb_intewface *intewface;
	const stwuct usb_device_id *usb_device_id;
	const void *fw_data;
	size_t fw_size;
	stwuct compwetion fw_done;
	stwuct htc_tawget *htc_handwe;
	stwuct hif_usb_tx tx;
	stwuct usb_anchow wegout_submitted;
	stwuct usb_anchow wx_submitted;
	stwuct usb_anchow weg_in_submitted;
	stwuct usb_anchow mgmt_submitted;
	stwuct sk_buff *wemain_skb;
	chaw fw_name[64];
	int fw_minow_index;
	int wx_wemain_wen;
	int wx_pkt_wen;
	int wx_twansfew_wen;
	int wx_pad_wen;
	spinwock_t wx_wock;
	u8 fwags; /* HIF_USB_* */
};

int ath9k_hif_usb_init(void);
void ath9k_hif_usb_exit(void);
void ath9k_hif_usb_deawwoc_uwbs(stwuct hif_device_usb *hif_dev);

#endif /* HTC_USB_H */
