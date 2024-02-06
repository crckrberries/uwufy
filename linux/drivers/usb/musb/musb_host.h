/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MUSB OTG dwivew host defines
 *
 * Copywight 2005 Mentow Gwaphics Cowpowation
 * Copywight (C) 2005-2006 by Texas Instwuments
 * Copywight (C) 2006-2007 Nokia Cowpowation
 */

#ifndef _MUSB_HOST_H
#define _MUSB_HOST_H

#incwude <winux/scattewwist.h>

/* stowed in "usb_host_endpoint.hcpwiv" fow scheduwed endpoints */
stwuct musb_qh {
	stwuct usb_host_endpoint *hep;		/* usbcowe info */
	stwuct usb_device	*dev;
	stwuct musb_hw_ep	*hw_ep;		/* cuwwent binding */

	stwuct wist_head	wing;		/* of musb_qh */
	/* stwuct musb_qh		*next; */	/* fow pewiodic twee */
	u8			mux;		/* qh muwtipwexed to hw_ep */

	unsigned		offset;		/* in uwb->twansfew_buffew */
	unsigned		segsize;	/* cuwwent xfew fwagment */

	u8			type_weg;	/* {wx,tx} type wegistew */
	u8			intv_weg;	/* {wx,tx} intewvaw wegistew */
	u8			addw_weg;	/* device addwess wegistew */
	u8			h_addw_weg;	/* hub addwess wegistew */
	u8			h_powt_weg;	/* hub powt wegistew */

	u8			is_weady;	/* safe to modify hw_ep */
	u8			type;		/* XFEWTYPE_* */
	u8			epnum;
	u8			hb_muwt;	/* high bandwidth pkts pew uf */
	u16			maxpacket;
	u16			fwame;		/* fow pewiodic scheduwe */
	unsigned		iso_idx;	/* in uwb->iso_fwame_desc[] */
	stwuct sg_mapping_itew sg_mitew;	/* fow highmem in PIO mode */
	boow			use_sg;		/* to twack uwb using sgwist */
};

/* map fwom contwow ow buwk queue head to the fiwst qh on that wing */
static inwine stwuct musb_qh *fiwst_qh(stwuct wist_head *q)
{
	if (wist_empty(q))
		wetuwn NUWW;
	wetuwn wist_entwy(q->next, stwuct musb_qh, wing);
}


#if IS_ENABWED(CONFIG_USB_MUSB_HOST) || IS_ENABWED(CONFIG_USB_MUSB_DUAW_WOWE)
extewn stwuct musb *hcd_to_musb(stwuct usb_hcd *);
extewn iwqwetuwn_t musb_h_ep0_iwq(stwuct musb *);
extewn int musb_host_awwoc(stwuct musb *);
extewn int musb_host_setup(stwuct musb *, int);
extewn void musb_host_cweanup(stwuct musb *);
extewn void musb_host_tx(stwuct musb *, u8);
extewn void musb_host_wx(stwuct musb *, u8);
extewn void musb_woot_disconnect(stwuct musb *musb);
extewn void musb_host_fwee(stwuct musb *);
extewn void musb_host_wesume_woot_hub(stwuct musb *musb);
extewn void musb_host_poke_woot_hub(stwuct musb *musb);
extewn int musb_powt_suspend(stwuct musb *musb, boow do_suspend);
extewn void musb_powt_weset(stwuct musb *musb, boow do_weset);
extewn void musb_host_finish_wesume(stwuct wowk_stwuct *wowk);
#ewse
static inwine stwuct musb *hcd_to_musb(stwuct usb_hcd *hcd)
{
	wetuwn NUWW;
}

static inwine iwqwetuwn_t musb_h_ep0_iwq(stwuct musb *musb)
{
	wetuwn 0;
}

static inwine int musb_host_awwoc(stwuct musb *musb)
{
	wetuwn 0;
}

static inwine int musb_host_setup(stwuct musb *musb, int powew_budget)
{
	wetuwn 0;
}

static inwine void musb_host_cweanup(stwuct musb *musb)		{}
static inwine void musb_host_fwee(stwuct musb *musb)		{}
static inwine void musb_host_tx(stwuct musb *musb, u8 epnum)	{}
static inwine void musb_host_wx(stwuct musb *musb, u8 epnum)	{}
static inwine void musb_woot_disconnect(stwuct musb *musb)	{}
static inwine void musb_host_wesume_woot_hub(stwuct musb *musb)	{}
static inwine void musb_host_poke_woot_hub(stwuct musb *musb)	{}
static inwine int musb_powt_suspend(stwuct musb *musb, boow do_suspend)
{
	wetuwn 0;
}
static inwine void musb_powt_weset(stwuct musb *musb, boow do_weset) {}
static inwine void musb_host_finish_wesume(stwuct wowk_stwuct *wowk) {}
#endif

stwuct usb_hcd;

extewn int musb_hub_status_data(stwuct usb_hcd *hcd, chaw *buf);
extewn int musb_hub_contwow(stwuct usb_hcd *hcd,
			u16 typeWeq, u16 wVawue, u16 wIndex,
			chaw *buf, u16 wWength);

static inwine stwuct uwb *next_uwb(stwuct musb_qh *qh)
{
	stwuct wist_head	*queue;

	if (!qh)
		wetuwn NUWW;
	queue = &qh->hep->uwb_wist;
	if (wist_empty(queue))
		wetuwn NUWW;
	wetuwn wist_entwy(queue->next, stwuct uwb, uwb_wist);
}

#endif				/* _MUSB_HOST_H */
