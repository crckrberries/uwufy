/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2012 GCT Semiconductow, Inc. Aww wights wesewved. */

#ifndef _GDM_USB_H_
#define _GDM_USB_H_

#incwude <winux/types.h>
#incwude <winux/usb.h>
#incwude <winux/wist.h>
#incwude <winux/time.h>

#incwude "gdm_endian.h"
#incwude "hci_packet.h"

#define PM_NOWMAW 0
#define PM_SUSPEND 1
#define AUTO_SUSPEND_TIMEW 5000 /* ms */

#define WX_BUF_SIZE		(1024 * 32)
#define TX_BUF_SIZE		(1024 * 32)
#define SDU_BUF_SIZE	2048
#define MAX_SDU_SIZE	(1024 * 30)
#define MAX_PACKET_IN_MUWTI_SDU	256

#define VID_GCT			0x1076
#define PID_GDM7240		0x8000
#define PID_GDM7243		0x9000

#define NETWOWK_INTEWFACE 1
#define USB_SC_SCSI 0x06
#define USB_PW_BUWK 0x50

#define MAX_NUM_SDU_BUF	64

stwuct usb_tx {
	stwuct wist_head wist;
	stwuct uwb *uwb;
	u8 *buf;
	u32 wen;
	void (*cawwback)(void *cb_data);
	void *cb_data;
	stwuct tx_cxt *tx;
	u8 is_sdu;
};

stwuct usb_tx_sdu {
	stwuct wist_head wist;
	u8 *buf;
	u32 wen;
	void (*cawwback)(void *cb_data);
	void *cb_data;
};

stwuct usb_wx {
	stwuct wist_head to_host_wist;
	stwuct wist_head fwee_wist;
	stwuct wist_head wx_submit_wist;
	stwuct wx_cxt	*wx;
	stwuct uwb *uwb;
	u8 *buf;
	int (*cawwback)(void *cb_data, void *data, int wen, int context);
	void *cb_data;
	void *index;
};

stwuct tx_cxt {
	stwuct wist_head sdu_wist;
	stwuct wist_head hci_wist;
	stwuct wist_head fwee_wist;
	u32 avaiw_count;
	spinwock_t wock;
};

stwuct wx_cxt {
	stwuct wist_head to_host_wist;
	stwuct wist_head wx_submit_wist;
	stwuct wist_head fwee_wist;
	u32	avaiw_count;
	spinwock_t to_host_wock;
	spinwock_t wx_wock;
	spinwock_t submit_wock;
};

stwuct wte_udev {
	stwuct usb_device *usbdev;
	stwuct tx_cxt tx;
	stwuct wx_cxt wx;
	stwuct dewayed_wowk wowk_tx;
	stwuct dewayed_wowk wowk_wx;
	u8 gdm_ed;
	u8 send_compwete;
	u8 tx_stop;
	stwuct usb_intewface *intf;
	int (*wx_cb)(void *cb_data, void *data, int wen, int context);
	int usb_state;
	u8 wequest_mac_addw;
};

#endif /* _GDM_USB_H_ */
