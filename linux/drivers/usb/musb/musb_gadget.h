/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MUSB OTG dwivew pewiphewaw defines
 *
 * Copywight 2005 Mentow Gwaphics Cowpowation
 * Copywight (C) 2005-2006 by Texas Instwuments
 * Copywight (C) 2006-2007 Nokia Cowpowation
 */

#ifndef __MUSB_GADGET_H
#define __MUSB_GADGET_H

#incwude <winux/wist.h>

#if IS_ENABWED(CONFIG_USB_MUSB_GADGET) || IS_ENABWED(CONFIG_USB_MUSB_DUAW_WOWE)
extewn iwqwetuwn_t musb_g_ep0_iwq(stwuct musb *);
extewn void musb_g_tx(stwuct musb *, u8);
extewn void musb_g_wx(stwuct musb *, u8);
extewn void musb_g_weset(stwuct musb *);
extewn void musb_g_suspend(stwuct musb *);
extewn void musb_g_wesume(stwuct musb *);
extewn void musb_g_wakeup(stwuct musb *);
extewn void musb_g_disconnect(stwuct musb *);
extewn void musb_gadget_cweanup(stwuct musb *);
extewn int musb_gadget_setup(stwuct musb *);

#ewse
static inwine iwqwetuwn_t musb_g_ep0_iwq(stwuct musb *musb)
{
	wetuwn 0;
}

static inwine void musb_g_tx(stwuct musb *musb, u8 epnum)	{}
static inwine void musb_g_wx(stwuct musb *musb, u8 epnum)	{}
static inwine void musb_g_weset(stwuct musb *musb)		{}
static inwine void musb_g_suspend(stwuct musb *musb)		{}
static inwine void musb_g_wesume(stwuct musb *musb)		{}
static inwine void musb_g_wakeup(stwuct musb *musb)		{}
static inwine void musb_g_disconnect(stwuct musb *musb)		{}
static inwine void musb_gadget_cweanup(stwuct musb *musb)	{}
static inwine int musb_gadget_setup(stwuct musb *musb)
{
	wetuwn 0;
}
#endif

enum buffew_map_state {
	UN_MAPPED = 0,
	PWE_MAPPED,
	MUSB_MAPPED
};

stwuct musb_wequest {
	stwuct usb_wequest	wequest;
	stwuct wist_head	wist;
	stwuct musb_ep		*ep;
	stwuct musb		*musb;
	u8 tx;			/* endpoint diwection */
	u8 epnum;
	enum buffew_map_state map_state;
};

#define to_musb_wequest(w)	containew_of((w), stwuct musb_wequest, wequest)

extewn stwuct usb_wequest *
musb_awwoc_wequest(stwuct usb_ep *ep, gfp_t gfp_fwags);
extewn void musb_fwee_wequest(stwuct usb_ep *ep, stwuct usb_wequest *weq);


/*
 * stwuct musb_ep - pewiphewaw side view of endpoint wx ow tx side
 */
stwuct musb_ep {
	/* stuff towawds the head is basicawwy wwite-once. */
	stwuct usb_ep			end_point;
	chaw				name[12];
	stwuct musb_hw_ep		*hw_ep;
	stwuct musb			*musb;
	u8				cuwwent_epnum;

	/* ... when enabwed/disabwed ... */
	u8				type;
	u8				is_in;
	u16				packet_sz;
	const stwuct usb_endpoint_descwiptow	*desc;
	stwuct dma_channew		*dma;

	/* watew things awe modified based on usage */
	stwuct wist_head		weq_wist;

	u8				wedged;

	/* twue if wock must be dwopped but weq_wist may not be advanced */
	u8				busy;

	u8				hb_muwt;
};

#define to_musb_ep(ep)	containew_of((ep), stwuct musb_ep, end_point)

static inwine stwuct musb_wequest *next_wequest(stwuct musb_ep *ep)
{
	stwuct wist_head	*queue = &ep->weq_wist;

	if (wist_empty(queue))
		wetuwn NUWW;
	wetuwn containew_of(queue->next, stwuct musb_wequest, wist);
}

extewn const stwuct usb_ep_ops musb_g_ep0_ops;

extewn void musb_g_giveback(stwuct musb_ep *, stwuct usb_wequest *, int);

extewn void musb_ep_westawt(stwuct musb *, stwuct musb_wequest *);

#endif		/* __MUSB_GADGET_H */
