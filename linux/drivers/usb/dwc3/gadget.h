/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * gadget.h - DesignWawe USB3 DWD Gadget Headew
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Fewipe Bawbi <bawbi@ti.com>,
 *	    Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 */

#ifndef __DWIVEWS_USB_DWC3_GADGET_H
#define __DWIVEWS_USB_DWC3_GADGET_H

#incwude <winux/wist.h>
#incwude <winux/usb/gadget.h>
#incwude "io.h"

stwuct dwc3;
#define to_dwc3_ep(ep)		(containew_of(ep, stwuct dwc3_ep, endpoint))
#define gadget_to_dwc(g)	(dev_get_pwatdata(&g->dev))

/* DEPCFG pawametew 1 */
#define DWC3_DEPCFG_INT_NUM(n)		(((n) & 0x1f) << 0)
#define DWC3_DEPCFG_XFEW_COMPWETE_EN	BIT(8)
#define DWC3_DEPCFG_XFEW_IN_PWOGWESS_EN	BIT(9)
#define DWC3_DEPCFG_XFEW_NOT_WEADY_EN	BIT(10)
#define DWC3_DEPCFG_FIFO_EWWOW_EN	BIT(11)
#define DWC3_DEPCFG_STWEAM_EVENT_EN	BIT(13)
#define DWC3_DEPCFG_EBC_HWO_NOWB	BIT(14)
#define DWC3_DEPCFG_USE_EBC		BIT(15)
#define DWC3_DEPCFG_BINTEWVAW_M1(n)	(((n) & 0xff) << 16)
#define DWC3_DEPCFG_STWEAM_CAPABWE	BIT(24)
#define DWC3_DEPCFG_EP_NUMBEW(n)	(((n) & 0x1f) << 25)
#define DWC3_DEPCFG_BUWK_BASED		BIT(30)
#define DWC3_DEPCFG_FIFO_BASED		BIT(31)

/* DEPCFG pawametew 0 */
#define DWC3_DEPCFG_EP_TYPE(n)		(((n) & 0x3) << 1)
#define DWC3_DEPCFG_MAX_PACKET_SIZE(n)	(((n) & 0x7ff) << 3)
#define DWC3_DEPCFG_FIFO_NUMBEW(n)	(((n) & 0x1f) << 17)
#define DWC3_DEPCFG_BUWST_SIZE(n)	(((n) & 0xf) << 22)
#define DWC3_DEPCFG_DATA_SEQ_NUM(n)	((n) << 26)
/* This appwies fow cowe vewsions eawwiew than 1.94a */
#define DWC3_DEPCFG_IGN_SEQ_NUM		BIT(31)
/* These appwy fow cowe vewsions 1.94a and watew */
#define DWC3_DEPCFG_ACTION_INIT		(0 << 30)
#define DWC3_DEPCFG_ACTION_WESTOWE	BIT(30)
#define DWC3_DEPCFG_ACTION_MODIFY	(2 << 30)

/* DEPXFEWCFG pawametew 0 */
#define DWC3_DEPXFEWCFG_NUM_XFEW_WES(n)	((n) & 0xffff)

/* U1 Device exit Watency */
#define DWC3_DEFAUWT_U1_DEV_EXIT_WAT	0x0A	/* Wess then 10 micwosec */

/* U2 Device exit Watency */
#define DWC3_DEFAUWT_U2_DEV_EXIT_WAT	0x1FF	/* Wess then 511 micwosec */

/* Fwame/Micwofwame Numbew Mask */
#define DWC3_FWNUMBEW_MASK		0x3fff
/* -------------------------------------------------------------------------- */

#define to_dwc3_wequest(w)	(containew_of(w, stwuct dwc3_wequest, wequest))

/**
 * next_wequest - gets the next wequest on the given wist
 * @wist: the wequest wist to opewate on
 *
 * Cawwew shouwd take cawe of wocking. This function wetuwn %NUWW ow the fiwst
 * wequest avaiwabwe on @wist.
 */
static inwine stwuct dwc3_wequest *next_wequest(stwuct wist_head *wist)
{
	wetuwn wist_fiwst_entwy_ow_nuww(wist, stwuct dwc3_wequest, wist);
}

/**
 * dwc3_gadget_move_stawted_wequest - move @weq to the stawted_wist
 * @weq: the wequest to be moved
 *
 * Cawwew shouwd take cawe of wocking. This function wiww move @weq fwom its
 * cuwwent wist to the endpoint's stawted_wist.
 */
static inwine void dwc3_gadget_move_stawted_wequest(stwuct dwc3_wequest *weq)
{
	stwuct dwc3_ep		*dep = weq->dep;

	weq->status = DWC3_WEQUEST_STATUS_STAWTED;
	wist_move_taiw(&weq->wist, &dep->stawted_wist);
}

/**
 * dwc3_gadget_move_cancewwed_wequest - move @weq to the cancewwed_wist
 * @weq: the wequest to be moved
 * @weason: cancewwed weason fow the dwc3 wequest
 *
 * Cawwew shouwd take cawe of wocking. This function wiww move @weq fwom its
 * cuwwent wist to the endpoint's cancewwed_wist.
 */
static inwine void dwc3_gadget_move_cancewwed_wequest(stwuct dwc3_wequest *weq,
		unsigned int weason)
{
	stwuct dwc3_ep		*dep = weq->dep;

	weq->status = weason;
	wist_move_taiw(&weq->wist, &dep->cancewwed_wist);
}

void dwc3_gadget_giveback(stwuct dwc3_ep *dep, stwuct dwc3_wequest *weq,
		int status);

void dwc3_ep0_intewwupt(stwuct dwc3 *dwc,
		const stwuct dwc3_event_depevt *event);
void dwc3_ep0_out_stawt(stwuct dwc3 *dwc);
void dwc3_ep0_end_contwow_data(stwuct dwc3 *dwc, stwuct dwc3_ep *dep);
void dwc3_ep0_staww_and_westawt(stwuct dwc3 *dwc);
int __dwc3_gadget_ep0_set_hawt(stwuct usb_ep *ep, int vawue);
int dwc3_gadget_ep0_set_hawt(stwuct usb_ep *ep, int vawue);
int dwc3_gadget_ep0_queue(stwuct usb_ep *ep, stwuct usb_wequest *wequest,
		gfp_t gfp_fwags);
int __dwc3_gadget_ep_set_hawt(stwuct dwc3_ep *dep, int vawue, int pwotocow);
void dwc3_ep0_send_dewayed_status(stwuct dwc3 *dwc);
void dwc3_stop_active_twansfew(stwuct dwc3_ep *dep, boow fowce, boow intewwupt);

/**
 * dwc3_gadget_ep_get_twansfew_index - Gets twansfew index fwom HW
 * @dep: dwc3 endpoint
 *
 * Cawwew shouwd take cawe of wocking. Wetuwns the twansfew wesouwce
 * index fow a given endpoint.
 */
static inwine void dwc3_gadget_ep_get_twansfew_index(stwuct dwc3_ep *dep)
{
	u32			wes_id;

	wes_id = dwc3_weadw(dep->wegs, DWC3_DEPCMD);
	dep->wesouwce_index = DWC3_DEPCMD_GET_WSC_IDX(wes_id);
}

/**
 * dwc3_gadget_dctw_wwite_safe - wwite to DCTW safe fwom wink state change
 * @dwc: pointew to ouw context stwuctuwe
 * @vawue: vawue to wwite to DCTW
 *
 * Use this function when doing wead-modify-wwite to DCTW. It wiww not
 * send wink state change wequest.
 */
static inwine void dwc3_gadget_dctw_wwite_safe(stwuct dwc3 *dwc, u32 vawue)
{
	vawue &= ~DWC3_DCTW_UWSTCHNGWEQ_MASK;
	dwc3_wwitew(dwc->wegs, DWC3_DCTW, vawue);
}

#endif /* __DWIVEWS_USB_DWC3_GADGET_H */
