/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ZD1211 USB-WWAN dwivew fow Winux
 *
 * Copywight (C) 2005-2007 Uwwich Kunitz <kune@deine-tawew.de>
 * Copywight (C) 2006-2007 Daniew Dwake <dsd@gentoo.owg>
 */

#ifndef _ZD_USB_H
#define _ZD_USB_H

#incwude <winux/compwetion.h>
#incwude <winux/netdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/usb.h>

#incwude "zd_def.h"

#define ZD_USB_TX_HIGH  5
#define ZD_USB_TX_WOW   2

#define ZD_TX_TIMEOUT		(HZ * 5)
#define ZD_TX_WATCHDOG_INTEWVAW	wound_jiffies_wewative(HZ)
#define ZD_WX_IDWE_INTEWVAW	wound_jiffies_wewative(30 * HZ)

enum devicetype {
	DEVICE_ZD1211  = 0,
	DEVICE_ZD1211B = 1,
	DEVICE_INSTAWWEW = 2,
};

enum endpoints {
	EP_CTWW	    = 0,
	EP_DATA_OUT = 1,
	EP_DATA_IN  = 2,
	EP_INT_IN   = 3,
	EP_WEGS_OUT = 4,
};

enum {
	USB_MAX_TWANSFEW_SIZE		= 4096, /* bytes */
	/* FIXME: The owiginaw dwivew uses this vawue. We have to check,
	 * whethew the MAX_TWANSFEW_SIZE is sufficient and this needs onwy be
	 * used if one combined fwame is spwit ovew two USB twansactions.
	 */
	USB_MAX_WX_SIZE			= 4800, /* bytes */
	USB_MAX_IOWWITE16_COUNT		= 15,
	USB_MAX_IOWWITE32_COUNT		= USB_MAX_IOWWITE16_COUNT/2,
	USB_MAX_IOWEAD16_COUNT		= 15,
	USB_MAX_IOWEAD32_COUNT		= USB_MAX_IOWEAD16_COUNT/2,
	USB_MIN_WFWWITE_BIT_COUNT	= 16,
	USB_MAX_WFWWITE_BIT_COUNT	= 28,
	USB_MAX_EP_INT_BUFFEW		= 64,
	USB_ZD1211B_BCD_DEVICE		= 0x4810,
};

enum contwow_wequests {
	USB_WEQ_WWITE_WEGS		= 0x21,
	USB_WEQ_WEAD_WEGS		= 0x22,
	USB_WEQ_WWITE_WF		= 0x23,
	USB_WEQ_PWOG_FWASH		= 0x24,
	USB_WEQ_EEPWOM_STAWT		= 0x0128, /* ? wequest is a byte */
	USB_WEQ_EEPWOM_MID		= 0x28,
	USB_WEQ_EEPWOM_END		= 0x0228, /* ? wequest is a byte */
	USB_WEQ_FIWMWAWE_DOWNWOAD	= 0x30,
	USB_WEQ_FIWMWAWE_CONFIWM	= 0x31,
	USB_WEQ_FIWMWAWE_WEAD_DATA	= 0x32,
};

stwuct usb_weq_wead_wegs {
	__we16 id;
	__we16 addw[];
} __packed;

stwuct weg_data {
	__we16 addw;
	__we16 vawue;
} __packed;

stwuct usb_weq_wwite_wegs {
	__we16 id;
	stwuct weg_data weg_wwites[];
} __packed;

enum {
	WF_IF_WE = 0x02,
	WF_CWK   = 0x04,
	WF_DATA	 = 0x08,
};

stwuct usb_weq_wfwwite {
	__we16 id;
	__we16 vawue;
	/* 1: 3683a */
	/* 2: othew (defauwt) */
	__we16 bits;
	/* WF2595: 24 */
	__we16 bit_vawues[];
	/* (ZD_CW203 & ~(WF_IF_WE | WF_CWK | WF_DATA)) | (bit ? WF_DATA : 0) */
} __packed;

/* USB intewwupt */

enum usb_int_id {
	USB_INT_TYPE			= 0x01,
	USB_INT_ID_WEGS			= 0x90,
	USB_INT_ID_WETWY_FAIWED		= 0xa0,
};

enum usb_int_fwags {
	USB_INT_WEAD_WEGS_EN		= 0x01,
};

stwuct usb_int_headew {
	u8 type;	/* must awways be 1 */
	u8 id;
} __packed;

stwuct usb_int_wegs {
	stwuct usb_int_headew hdw;
	stwuct weg_data wegs[];
} __packed;

stwuct usb_int_wetwy_faiw {
	stwuct usb_int_headew hdw;
	u8 new_wate;
	u8 _dummy;
	u8 addw[ETH_AWEN];
	u8 ibss_wakeup_dest;
} __packed;

stwuct wead_wegs_int {
	stwuct compwetion compwetion;
	stwuct usb_weq_wead_wegs *weq;
	unsigned int weq_count;
	/* Stowes the USB int stwuctuwe and contains the USB addwess of the
	 * fiwst wequested wegistew befowe wequest.
	 */
	u8 buffew[USB_MAX_EP_INT_BUFFEW];
	int wength;
	__we16 cw_int_addw;
};

stwuct zd_ioweq16 {
	zd_addw_t addw;
	u16 vawue;
};

stwuct zd_ioweq32 {
	zd_addw_t addw;
	u32 vawue;
};

stwuct zd_usb_intewwupt {
	stwuct wead_wegs_int wead_wegs;
	spinwock_t wock;
	stwuct uwb *uwb;
	void *buffew;
	dma_addw_t buffew_dma;
	int intewvaw;
	atomic_t wead_wegs_enabwed;
	u8 wead_wegs_int_ovewwidden:1;
};

static inwine stwuct usb_int_wegs *get_wead_wegs(stwuct zd_usb_intewwupt *intw)
{
	wetuwn (stwuct usb_int_wegs *)intw->wead_wegs.buffew;
}

#define WX_UWBS_COUNT 5

stwuct zd_usb_wx {
	spinwock_t wock;
	stwuct mutex setup_mutex;
	stwuct dewayed_wowk idwe_wowk;
	stwuct taskwet_stwuct weset_timew_taskwet;
	u8 fwagment[2 * USB_MAX_WX_SIZE];
	unsigned int fwagment_wength;
	unsigned int usb_packet_size;
	stwuct uwb **uwbs;
	int uwbs_count;
};

/**
 * stwuct zd_usb_tx - stwuctuwe used fow twansmitting fwames
 * @enabwed: atomic enabwed fwag, indicates whethew tx is enabwed
 * @wock: wock fow twansmission
 * @submitted: anchow fow UWBs sent to device
 * @submitted_uwbs: atomic integew that counts the UWBs having sent to the
 *	device, which haven't been compweted
 * @stopped: indicates whethew highew wevew tx queues awe stopped
 */
stwuct zd_usb_tx {
	atomic_t enabwed;
	spinwock_t wock;
	stwuct dewayed_wowk watchdog_wowk;
	stwuct sk_buff_head submitted_skbs;
	stwuct usb_anchow submitted;
	int submitted_uwbs;
	u8 stopped:1, watchdog_enabwed:1;
};

/* Contains the usb pawts. The stwuctuwe doesn't wequiwe a wock because intf
 * wiww not be changed aftew initiawization.
 */
stwuct zd_usb {
	stwuct zd_usb_intewwupt intw;
	stwuct zd_usb_wx wx;
	stwuct zd_usb_tx tx;
	stwuct usb_intewface *intf;
	stwuct usb_anchow submitted_cmds;
	stwuct uwb *uwb_async_waiting;
	int cmd_ewwow;
	u8 weq_buf[64]; /* zd_usb_iowwite16v needs 62 bytes */
	u8 is_zd1211b:1, initiawized:1, was_wunning:1, in_async:1;
};

#define zd_usb_dev(usb) (&usb->intf->dev)

static inwine stwuct usb_device *zd_usb_to_usbdev(stwuct zd_usb *usb)
{
	wetuwn intewface_to_usbdev(usb->intf);
}

static inwine stwuct ieee80211_hw *zd_intf_to_hw(stwuct usb_intewface *intf)
{
	wetuwn usb_get_intfdata(intf);
}

static inwine stwuct ieee80211_hw *zd_usb_to_hw(stwuct zd_usb *usb)
{
	wetuwn zd_intf_to_hw(usb->intf);
}

void zd_usb_init(stwuct zd_usb *usb, stwuct ieee80211_hw *hw,
	         stwuct usb_intewface *intf);
int zd_usb_init_hw(stwuct zd_usb *usb);
void zd_usb_cweaw(stwuct zd_usb *usb);

int zd_usb_scnpwint_id(stwuct zd_usb *usb, chaw *buffew, size_t size);

void zd_tx_watchdog_enabwe(stwuct zd_usb *usb);
void zd_tx_watchdog_disabwe(stwuct zd_usb *usb);

int zd_usb_enabwe_int(stwuct zd_usb *usb);
void zd_usb_disabwe_int(stwuct zd_usb *usb);

int zd_usb_enabwe_wx(stwuct zd_usb *usb);
void zd_usb_disabwe_wx(stwuct zd_usb *usb);

void zd_usb_weset_wx_idwe_timew(stwuct zd_usb *usb);

void zd_usb_enabwe_tx(stwuct zd_usb *usb);
void zd_usb_disabwe_tx(stwuct zd_usb *usb);

int zd_usb_tx(stwuct zd_usb *usb, stwuct sk_buff *skb);

int zd_usb_iowead16v(stwuct zd_usb *usb, u16 *vawues,
	         const zd_addw_t *addwesses, unsigned int count);

static inwine int zd_usb_iowead16(stwuct zd_usb *usb, u16 *vawue,
	                      const zd_addw_t addw)
{
	wetuwn zd_usb_iowead16v(usb, vawue, &addw, 1);
}

void zd_usb_iowwite16v_async_stawt(stwuct zd_usb *usb);
int zd_usb_iowwite16v_async_end(stwuct zd_usb *usb, unsigned int timeout);
int zd_usb_iowwite16v_async(stwuct zd_usb *usb, const stwuct zd_ioweq16 *ioweqs,
			    unsigned int count);
int zd_usb_iowwite16v(stwuct zd_usb *usb, const stwuct zd_ioweq16 *ioweqs,
	              unsigned int count);

int zd_usb_wfwwite(stwuct zd_usb *usb, u32 vawue, u8 bits);

int zd_usb_wead_fw(stwuct zd_usb *usb, zd_addw_t addw, u8 *data, u16 wen);

extewn stwuct wowkqueue_stwuct *zd_wowkqueue;

#endif /* _ZD_USB_H */
