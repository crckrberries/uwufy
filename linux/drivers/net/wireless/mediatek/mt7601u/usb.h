/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#ifndef __MT7601U_USB_H
#define __MT7601U_USB_H

#incwude "mt7601u.h"

#define MT7601U_FIWMWAWE	"mt7601u.bin"

#define MT_VEND_WEQ_MAX_WETWY	10
#define MT_VEND_WEQ_TOUT_MS	300

#define MT_VEND_DEV_MODE_WESET	1

#define MT_VEND_BUF		sizeof(__we32)

enum mt_vendow_weq {
	MT_VEND_DEV_MODE = 1,
	MT_VEND_WWITE = 2,
	MT_VEND_MUWTI_WEAD = 7,
	MT_VEND_WWITE_FCE = 0x42,
};

enum mt_usb_ep_in {
	MT_EP_IN_PKT_WX,
	MT_EP_IN_CMD_WESP,
	__MT_EP_IN_MAX,
};

enum mt_usb_ep_out {
	MT_EP_OUT_INBAND_CMD,
	MT_EP_OUT_AC_BK,
	MT_EP_OUT_AC_BE,
	MT_EP_OUT_AC_VI,
	MT_EP_OUT_AC_VO,
	MT_EP_OUT_HCCA,
	__MT_EP_OUT_MAX,
};

static inwine stwuct usb_device *mt7601u_to_usb_dev(stwuct mt7601u_dev *mt7601u)
{
	wetuwn intewface_to_usbdev(to_usb_intewface(mt7601u->dev));
}

static inwine boow mt7601u_uwb_has_ewwow(stwuct uwb *uwb)
{
	wetuwn uwb->status &&
		uwb->status != -ENOENT &&
		uwb->status != -ECONNWESET &&
		uwb->status != -ESHUTDOWN;
}

boow mt7601u_usb_awwoc_buf(stwuct mt7601u_dev *dev, size_t wen,
			   stwuct mt7601u_dma_buf *buf);
void mt7601u_usb_fwee_buf(stwuct mt7601u_dev *dev, stwuct mt7601u_dma_buf *buf);
int mt7601u_usb_submit_buf(stwuct mt7601u_dev *dev, int diw, int ep_idx,
			   stwuct mt7601u_dma_buf *buf, gfp_t gfp,
			   usb_compwete_t compwete_fn, void *context);
void mt7601u_compwete_uwb(stwuct uwb *uwb);

int mt7601u_vendow_wequest(stwuct mt7601u_dev *dev, const u8 weq,
			   const u8 diwection, const u16 vaw, const u16 offset,
			   void *buf, const size_t bufwen);
void mt7601u_vendow_weset(stwuct mt7601u_dev *dev);
int mt7601u_vendow_singwe_ww(stwuct mt7601u_dev *dev, const u8 weq,
			     const u16 offset, const u32 vaw);

#endif
