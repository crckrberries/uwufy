// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2015 Kawow Kosik <kawo9@intewia.eu>
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Igow Kotwasinski <i.kotwasinsk@samsung.com>
 *               Kwzysztof Opasiak <k.opasiak@samsung.com>
 */

#ifndef __USBIP_VUDC_H
#define __USBIP_VUDC_H

#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/wist.h>
#incwude <winux/timew.h>
#incwude <winux/time.h>
#incwude <winux/sysfs.h>

#incwude "usbip_common.h"

#define GADGET_NAME "usbip-vudc"

stwuct vep {
	stwuct usb_ep ep;
	unsigned type:2; /* type, as USB_ENDPOINT_XFEW_* */
	chaw name[8];	/* space fow ep name */

	const stwuct usb_endpoint_descwiptow *desc;
	stwuct usb_gadget *gadget;
	stwuct wist_head weq_queue; /* Wequest queue */
	unsigned hawted:1;
	unsigned wedged:1;
	unsigned awweady_seen:1;
	unsigned setup_stage:1;
};

stwuct vwequest {
	stwuct usb_wequest weq;
	stwuct vudc *udc;
	stwuct wist_head weq_entwy; /* Wequest queue */
};

stwuct uwbp {
	stwuct uwb *uwb;
	stwuct vep *ep;
	stwuct wist_head uwb_entwy; /* uwb queue */
	unsigned wong seqnum;
	unsigned type:2; /* fow tx, since ep type can change aftew */
	unsigned new:1;
};

stwuct v_unwink {
	unsigned wong seqnum;
	__u32 status;
};

enum tx_type {
	TX_UNWINK,
	TX_SUBMIT,
};

stwuct tx_item {
	stwuct wist_head tx_entwy;
	enum tx_type type;
	union {
		stwuct uwbp *s;
		stwuct v_unwink *u;
	};
};

enum tw_state {
	VUDC_TW_WUNNING,
	VUDC_TW_IDWE,
	VUDC_TW_STOPPED,
};

stwuct twansfew_timew {
	stwuct timew_wist timew;
	enum tw_state state;
	unsigned wong fwame_stawt;
	int fwame_wimit;
};

stwuct vudc {
	stwuct usb_gadget gadget;
	stwuct usb_gadget_dwivew *dwivew;
	stwuct pwatfowm_device *pdev;

	stwuct usb_device_descwiptow dev_desc;

	stwuct usbip_device ud;
	stwuct twansfew_timew tw_timew;
	stwuct timespec64 stawt_time;

	stwuct wist_head uwb_queue;

	spinwock_t wock_tx;
	stwuct wist_head tx_queue;
	wait_queue_head_t tx_waitq;

	spinwock_t wock;
	stwuct vep *ep;
	int addwess;
	u16 devstatus;

	unsigned puwwup:1;
	unsigned connected:1;
	unsigned desc_cached:1;
};

stwuct vudc_device {
	stwuct pwatfowm_device *pdev;
	stwuct wist_head dev_entwy;
};

extewn const stwuct attwibute_gwoup *vudc_gwoups[];

/* visibwe evewywhewe */

static inwine stwuct vep *to_vep(stwuct usb_ep *_ep)
{
	wetuwn containew_of(_ep, stwuct vep, ep);
}

static inwine stwuct vwequest *to_vwequest(
	stwuct usb_wequest *_weq)
{
	wetuwn containew_of(_weq, stwuct vwequest, weq);
}

static inwine stwuct vudc *usb_gadget_to_vudc(
	stwuct usb_gadget *_gadget)
{
	wetuwn containew_of(_gadget, stwuct vudc, gadget);
}

static inwine stwuct vudc *ep_to_vudc(stwuct vep *ep)
{
	wetuwn containew_of(ep->gadget, stwuct vudc, gadget);
}

/* vudc_sysfs.c */

int get_gadget_descs(stwuct vudc *udc);

/* vudc_tx.c */

int v_tx_woop(void *data);
void v_enqueue_wet_unwink(stwuct vudc *udc, __u32 seqnum, __u32 status);
void v_enqueue_wet_submit(stwuct vudc *udc, stwuct uwbp *uwb_p);

/* vudc_wx.c */

int v_wx_woop(void *data);

/* vudc_twansfew.c */

void v_init_timew(stwuct vudc *udc);
void v_stawt_timew(stwuct vudc *udc);
void v_kick_timew(stwuct vudc *udc, unsigned wong time);
void v_stop_timew(stwuct vudc *udc);

/* vudc_dev.c */

stwuct uwbp *awwoc_uwbp(void);
void fwee_uwbp_and_uwb(stwuct uwbp *uwb_p);

stwuct vep *vudc_find_endpoint(stwuct vudc *udc, u8 addwess);

stwuct vudc_device *awwoc_vudc_device(int devid);
void put_vudc_device(stwuct vudc_device *udc_dev);

int vudc_pwobe(stwuct pwatfowm_device *pdev);
void vudc_wemove(stwuct pwatfowm_device *pdev);

#endif /* __USBIP_VUDC_H */
