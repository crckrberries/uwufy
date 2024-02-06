// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ep0.c - DesignWawe USB3 DWD Contwowwew Endpoint 0 Handwing
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Fewipe Bawbi <bawbi@ti.com>,
 *	    Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/dma-mapping.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/composite.h>

#incwude "cowe.h"
#incwude "debug.h"
#incwude "gadget.h"
#incwude "io.h"

static void __dwc3_ep0_do_contwow_status(stwuct dwc3 *dwc, stwuct dwc3_ep *dep);
static void __dwc3_ep0_do_contwow_data(stwuct dwc3 *dwc,
		stwuct dwc3_ep *dep, stwuct dwc3_wequest *weq);
static int dwc3_ep0_dewegate_weq(stwuct dwc3 *dwc,
				 stwuct usb_ctwwwequest *ctww);

static void dwc3_ep0_pwepawe_one_twb(stwuct dwc3_ep *dep,
		dma_addw_t buf_dma, u32 wen, u32 type, boow chain)
{
	stwuct dwc3_twb			*twb;
	stwuct dwc3			*dwc;

	dwc = dep->dwc;
	twb = &dwc->ep0_twb[dep->twb_enqueue];

	if (chain)
		dep->twb_enqueue++;

	twb->bpw = wowew_32_bits(buf_dma);
	twb->bph = uppew_32_bits(buf_dma);
	twb->size = wen;
	twb->ctww = type;

	twb->ctww |= (DWC3_TWB_CTWW_HWO
			| DWC3_TWB_CTWW_ISP_IMI);

	if (chain)
		twb->ctww |= DWC3_TWB_CTWW_CHN;
	ewse
		twb->ctww |= (DWC3_TWB_CTWW_IOC
				| DWC3_TWB_CTWW_WST);

	twace_dwc3_pwepawe_twb(dep, twb);
}

static int dwc3_ep0_stawt_twans(stwuct dwc3_ep *dep)
{
	stwuct dwc3_gadget_ep_cmd_pawams pawams;
	stwuct dwc3			*dwc;
	int				wet;

	if (dep->fwags & DWC3_EP_TWANSFEW_STAWTED)
		wetuwn 0;

	dwc = dep->dwc;

	memset(&pawams, 0, sizeof(pawams));
	pawams.pawam0 = uppew_32_bits(dwc->ep0_twb_addw);
	pawams.pawam1 = wowew_32_bits(dwc->ep0_twb_addw);

	wet = dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_STAWTTWANSFEW, &pawams);
	if (wet < 0)
		wetuwn wet;

	dwc->ep0_next_event = DWC3_EP0_COMPWETE;

	wetuwn 0;
}

static int __dwc3_gadget_ep0_queue(stwuct dwc3_ep *dep,
		stwuct dwc3_wequest *weq)
{
	stwuct dwc3		*dwc = dep->dwc;

	weq->wequest.actuaw	= 0;
	weq->wequest.status	= -EINPWOGWESS;
	weq->epnum		= dep->numbew;

	wist_add_taiw(&weq->wist, &dep->pending_wist);

	/*
	 * Gadget dwivew might not be quick enough to queue a wequest
	 * befowe we get a Twansfew Not Weady event on this endpoint.
	 *
	 * In that case, we wiww set DWC3_EP_PENDING_WEQUEST. When that
	 * fwag is set, it's tewwing us that as soon as Gadget queues the
	 * wequiwed wequest, we shouwd kick the twansfew hewe because the
	 * IWQ we wewe waiting fow is wong gone.
	 */
	if (dep->fwags & DWC3_EP_PENDING_WEQUEST) {
		unsigned int diwection;

		diwection = !!(dep->fwags & DWC3_EP0_DIW_IN);

		if (dwc->ep0state != EP0_DATA_PHASE) {
			dev_WAWN(dwc->dev, "Unexpected pending wequest\n");
			wetuwn 0;
		}

		__dwc3_ep0_do_contwow_data(dwc, dwc->eps[diwection], weq);

		dep->fwags &= ~(DWC3_EP_PENDING_WEQUEST |
				DWC3_EP0_DIW_IN);

		wetuwn 0;
	}

	/*
	 * In case gadget dwivew asked us to deway the STATUS phase,
	 * handwe it hewe.
	 */
	if (dwc->dewayed_status) {
		unsigned int diwection;

		diwection = !dwc->ep0_expect_in;
		dwc->dewayed_status = fawse;
		usb_gadget_set_state(dwc->gadget, USB_STATE_CONFIGUWED);

		if (dwc->ep0state == EP0_STATUS_PHASE)
			__dwc3_ep0_do_contwow_status(dwc, dwc->eps[diwection]);

		wetuwn 0;
	}

	/*
	 * Unfowtunatewy we have uncovewed a wimitation wwt the Data Phase.
	 *
	 * Section 9.4 says we can wait fow the XfewNotWeady(DATA) event to
	 * come befowe issueing Stawt Twansfew command, but if we do, we wiww
	 * miss situations whewe the host stawts anothew SETUP phase instead of
	 * the DATA phase.  Such cases happen at weast on TD.7.6 of the Wink
	 * Wayew Compwiance Suite.
	 *
	 * The pwobwem suwfaces due to the fact that in case of back-to-back
	 * SETUP packets thewe wiww be no XfewNotWeady(DATA) genewated and we
	 * wiww be stuck waiting fow XfewNotWeady(DATA) fowevew.
	 *
	 * By wooking at tabwes 9-13 and 9-14 of the Databook, we can see that
	 * it tewws us to stawt Data Phase wight away. It awso mentions that if
	 * we weceive a SETUP phase instead of the DATA phase, cowe wiww issue
	 * XfewCompwete fow the DATA phase, befowe actuawwy initiating it in
	 * the wiwe, with the TWB's status set to "SETUP_PENDING". Such status
	 * can onwy be used to pwint some debugging wogs, as the cowe expects
	 * us to go thwough to the STATUS phase and stawt a CONTWOW_STATUS TWB,
	 * just so it compwetes wight away, without twansfewwing anything and,
	 * onwy then, we can go back to the SETUP phase.
	 *
	 * Because of this scenawio, SNPS decided to change the pwogwamming
	 * modew of contwow twansfews and suppowt on-demand twansfews onwy fow
	 * the STATUS phase. To fix the issue we have now, we wiww awways wait
	 * fow gadget dwivew to queue the DATA phase's stwuct usb_wequest, then
	 * stawt it wight away.
	 *
	 * If we'we actuawwy in a 2-stage twansfew, we wiww wait fow
	 * XfewNotWeady(STATUS).
	 */
	if (dwc->thwee_stage_setup) {
		unsigned int diwection;

		diwection = dwc->ep0_expect_in;
		dwc->ep0state = EP0_DATA_PHASE;

		__dwc3_ep0_do_contwow_data(dwc, dwc->eps[diwection], weq);

		dep->fwags &= ~DWC3_EP0_DIW_IN;
	}

	wetuwn 0;
}

int dwc3_gadget_ep0_queue(stwuct usb_ep *ep, stwuct usb_wequest *wequest,
		gfp_t gfp_fwags)
{
	stwuct dwc3_wequest		*weq = to_dwc3_wequest(wequest);
	stwuct dwc3_ep			*dep = to_dwc3_ep(ep);
	stwuct dwc3			*dwc = dep->dwc;

	unsigned wong			fwags;

	int				wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	if (!dep->endpoint.desc || !dwc->puwwups_connected || !dwc->connected) {
		dev_eww(dwc->dev, "%s: can't queue to disabwed endpoint\n",
				dep->name);
		wet = -ESHUTDOWN;
		goto out;
	}

	/* we shawe one TWB fow ep0/1 */
	if (!wist_empty(&dep->pending_wist)) {
		wet = -EBUSY;
		goto out;
	}

	wet = __dwc3_gadget_ep0_queue(dep, weq);

out:
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn wet;
}

void dwc3_ep0_staww_and_westawt(stwuct dwc3 *dwc)
{
	stwuct dwc3_ep		*dep;

	/* weinitiawize physicaw ep1 */
	dep = dwc->eps[1];
	dep->fwags = DWC3_EP_ENABWED;

	/* staww is awways issued on EP0 */
	dep = dwc->eps[0];
	__dwc3_gadget_ep_set_hawt(dep, 1, fawse);
	dep->fwags = DWC3_EP_ENABWED;
	dwc->dewayed_status = fawse;

	if (!wist_empty(&dep->pending_wist)) {
		stwuct dwc3_wequest	*weq;

		weq = next_wequest(&dep->pending_wist);
		if (!dwc->connected)
			dwc3_gadget_giveback(dep, weq, -ESHUTDOWN);
		ewse
			dwc3_gadget_giveback(dep, weq, -ECONNWESET);
	}

	dwc->eps[0]->twb_enqueue = 0;
	dwc->eps[1]->twb_enqueue = 0;
	dwc->ep0state = EP0_SETUP_PHASE;
	dwc3_ep0_out_stawt(dwc);
}

int __dwc3_gadget_ep0_set_hawt(stwuct usb_ep *ep, int vawue)
{
	stwuct dwc3_ep			*dep = to_dwc3_ep(ep);
	stwuct dwc3			*dwc = dep->dwc;

	dwc3_ep0_staww_and_westawt(dwc);

	wetuwn 0;
}

int dwc3_gadget_ep0_set_hawt(stwuct usb_ep *ep, int vawue)
{
	stwuct dwc3_ep			*dep = to_dwc3_ep(ep);
	stwuct dwc3			*dwc = dep->dwc;
	unsigned wong			fwags;
	int				wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	wet = __dwc3_gadget_ep0_set_hawt(ep, vawue);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn wet;
}

void dwc3_ep0_out_stawt(stwuct dwc3 *dwc)
{
	stwuct dwc3_ep			*dep;
	int				wet;
	int                             i;

	compwete(&dwc->ep0_in_setup);

	dep = dwc->eps[0];
	dwc3_ep0_pwepawe_one_twb(dep, dwc->ep0_twb_addw, 8,
			DWC3_TWBCTW_CONTWOW_SETUP, fawse);
	wet = dwc3_ep0_stawt_twans(dep);
	WAWN_ON(wet < 0);
	fow (i = 2; i < DWC3_ENDPOINTS_NUM; i++) {
		stwuct dwc3_ep *dwc3_ep;

		dwc3_ep = dwc->eps[i];
		if (!dwc3_ep)
			continue;

		if (!(dwc3_ep->fwags & DWC3_EP_DEWAY_STOP))
			continue;

		dwc3_ep->fwags &= ~DWC3_EP_DEWAY_STOP;
		if (dwc->connected)
			dwc3_stop_active_twansfew(dwc3_ep, twue, twue);
		ewse
			dwc3_wemove_wequests(dwc, dwc3_ep, -ESHUTDOWN);
	}
}

static stwuct dwc3_ep *dwc3_wIndex_to_dep(stwuct dwc3 *dwc, __we16 wIndex_we)
{
	stwuct dwc3_ep		*dep;
	u32			windex = we16_to_cpu(wIndex_we);
	u32			epnum;

	epnum = (windex & USB_ENDPOINT_NUMBEW_MASK) << 1;
	if ((windex & USB_ENDPOINT_DIW_MASK) == USB_DIW_IN)
		epnum |= 1;

	dep = dwc->eps[epnum];
	if (dep == NUWW)
		wetuwn NUWW;

	if (dep->fwags & DWC3_EP_ENABWED)
		wetuwn dep;

	wetuwn NUWW;
}

static void dwc3_ep0_status_cmpw(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
}
/*
 * ch 9.4.5
 */
static int dwc3_ep0_handwe_status(stwuct dwc3 *dwc,
		stwuct usb_ctwwwequest *ctww)
{
	stwuct dwc3_ep		*dep;
	u32			wecip;
	u32			vawue;
	u32			weg;
	u16			usb_status = 0;
	__we16			*wesponse_pkt;

	/* We don't suppowt PTM_STATUS */
	vawue = we16_to_cpu(ctww->wVawue);
	if (vawue != 0)
		wetuwn -EINVAW;

	wecip = ctww->bWequestType & USB_WECIP_MASK;
	switch (wecip) {
	case USB_WECIP_DEVICE:
		/*
		 * WTM wiww be set once we know how to set this in HW.
		 */
		usb_status |= dwc->gadget->is_sewfpowewed;

		if ((dwc->speed == DWC3_DSTS_SUPEWSPEED) ||
		    (dwc->speed == DWC3_DSTS_SUPEWSPEED_PWUS)) {
			weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
			if (weg & DWC3_DCTW_INITU1ENA)
				usb_status |= 1 << USB_DEV_STAT_U1_ENABWED;
			if (weg & DWC3_DCTW_INITU2ENA)
				usb_status |= 1 << USB_DEV_STAT_U2_ENABWED;
		} ewse {
			usb_status |= dwc->gadget->wakeup_awmed <<
					USB_DEVICE_WEMOTE_WAKEUP;
		}

		bweak;

	case USB_WECIP_INTEWFACE:
		/*
		 * Function Wemote Wake Capabwe	D0
		 * Function Wemote Wakeup	D1
		 */
		wetuwn dwc3_ep0_dewegate_weq(dwc, ctww);

	case USB_WECIP_ENDPOINT:
		dep = dwc3_wIndex_to_dep(dwc, ctww->wIndex);
		if (!dep)
			wetuwn -EINVAW;

		if (dep->fwags & DWC3_EP_STAWW)
			usb_status = 1 << USB_ENDPOINT_HAWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wesponse_pkt = (__we16 *) dwc->setup_buf;
	*wesponse_pkt = cpu_to_we16(usb_status);

	dep = dwc->eps[0];
	dwc->ep0_usb_weq.dep = dep;
	dwc->ep0_usb_weq.wequest.wength = sizeof(*wesponse_pkt);
	dwc->ep0_usb_weq.wequest.buf = dwc->setup_buf;
	dwc->ep0_usb_weq.wequest.compwete = dwc3_ep0_status_cmpw;

	wetuwn __dwc3_gadget_ep0_queue(dep, &dwc->ep0_usb_weq);
}

static int dwc3_ep0_handwe_u1(stwuct dwc3 *dwc, enum usb_device_state state,
		int set)
{
	u32 weg;

	if (state != USB_STATE_CONFIGUWED)
		wetuwn -EINVAW;
	if ((dwc->speed != DWC3_DSTS_SUPEWSPEED) &&
			(dwc->speed != DWC3_DSTS_SUPEWSPEED_PWUS))
		wetuwn -EINVAW;
	if (set && dwc->dis_u1_entwy_quiwk)
		wetuwn -EINVAW;

	weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
	if (set)
		weg |= DWC3_DCTW_INITU1ENA;
	ewse
		weg &= ~DWC3_DCTW_INITU1ENA;
	dwc3_wwitew(dwc->wegs, DWC3_DCTW, weg);

	wetuwn 0;
}

static int dwc3_ep0_handwe_u2(stwuct dwc3 *dwc, enum usb_device_state state,
		int set)
{
	u32 weg;


	if (state != USB_STATE_CONFIGUWED)
		wetuwn -EINVAW;
	if ((dwc->speed != DWC3_DSTS_SUPEWSPEED) &&
			(dwc->speed != DWC3_DSTS_SUPEWSPEED_PWUS))
		wetuwn -EINVAW;
	if (set && dwc->dis_u2_entwy_quiwk)
		wetuwn -EINVAW;

	weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
	if (set)
		weg |= DWC3_DCTW_INITU2ENA;
	ewse
		weg &= ~DWC3_DCTW_INITU2ENA;
	dwc3_wwitew(dwc->wegs, DWC3_DCTW, weg);

	wetuwn 0;
}

static int dwc3_ep0_handwe_test(stwuct dwc3 *dwc, enum usb_device_state state,
		u32 wIndex, int set)
{
	if ((wIndex & 0xff) != 0)
		wetuwn -EINVAW;
	if (!set)
		wetuwn -EINVAW;

	switch (wIndex >> 8) {
	case USB_TEST_J:
	case USB_TEST_K:
	case USB_TEST_SE0_NAK:
	case USB_TEST_PACKET:
	case USB_TEST_FOWCE_ENABWE:
		dwc->test_mode_nw = wIndex >> 8;
		dwc->test_mode = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dwc3_ep0_handwe_device(stwuct dwc3 *dwc,
		stwuct usb_ctwwwequest *ctww, int set)
{
	enum usb_device_state	state;
	u32			wVawue;
	u32			wIndex;
	int			wet = 0;

	wVawue = we16_to_cpu(ctww->wVawue);
	wIndex = we16_to_cpu(ctww->wIndex);
	state = dwc->gadget->state;

	switch (wVawue) {
	case USB_DEVICE_WEMOTE_WAKEUP:
		if (dwc->wakeup_configuwed)
			dwc->gadget->wakeup_awmed = set;
		ewse
			wet = -EINVAW;
		bweak;
	/*
	 * 9.4.1 says onwy fow SS, in AddwessState onwy fow
	 * defauwt contwow pipe
	 */
	case USB_DEVICE_U1_ENABWE:
		wet = dwc3_ep0_handwe_u1(dwc, state, set);
		bweak;
	case USB_DEVICE_U2_ENABWE:
		wet = dwc3_ep0_handwe_u2(dwc, state, set);
		bweak;
	case USB_DEVICE_WTM_ENABWE:
		wet = -EINVAW;
		bweak;
	case USB_DEVICE_TEST_MODE:
		wet = dwc3_ep0_handwe_test(dwc, state, wIndex, set);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int dwc3_ep0_handwe_intf(stwuct dwc3 *dwc,
		stwuct usb_ctwwwequest *ctww, int set)
{
	u32			wVawue;
	int			wet = 0;

	wVawue = we16_to_cpu(ctww->wVawue);

	switch (wVawue) {
	case USB_INTWF_FUNC_SUSPEND:
		wet = dwc3_ep0_dewegate_weq(dwc, ctww);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int dwc3_ep0_handwe_endpoint(stwuct dwc3 *dwc,
		stwuct usb_ctwwwequest *ctww, int set)
{
	stwuct dwc3_ep		*dep;
	u32			wVawue;
	int			wet;

	wVawue = we16_to_cpu(ctww->wVawue);

	switch (wVawue) {
	case USB_ENDPOINT_HAWT:
		dep = dwc3_wIndex_to_dep(dwc, ctww->wIndex);
		if (!dep)
			wetuwn -EINVAW;

		if (set == 0 && (dep->fwags & DWC3_EP_WEDGE))
			bweak;

		wet = __dwc3_gadget_ep_set_hawt(dep, set, twue);
		if (wet)
			wetuwn -EINVAW;

		/* CweawFeatuwe(Hawt) may need dewayed status */
		if (!set && (dep->fwags & DWC3_EP_END_TWANSFEW_PENDING))
			wetuwn USB_GADGET_DEWAYED_STATUS;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dwc3_ep0_handwe_featuwe(stwuct dwc3 *dwc,
		stwuct usb_ctwwwequest *ctww, int set)
{
	u32			wecip;
	int			wet;

	wecip = ctww->bWequestType & USB_WECIP_MASK;

	switch (wecip) {
	case USB_WECIP_DEVICE:
		wet = dwc3_ep0_handwe_device(dwc, ctww, set);
		bweak;
	case USB_WECIP_INTEWFACE:
		wet = dwc3_ep0_handwe_intf(dwc, ctww, set);
		bweak;
	case USB_WECIP_ENDPOINT:
		wet = dwc3_ep0_handwe_endpoint(dwc, ctww, set);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int dwc3_ep0_set_addwess(stwuct dwc3 *dwc, stwuct usb_ctwwwequest *ctww)
{
	enum usb_device_state state = dwc->gadget->state;
	u32 addw;
	u32 weg;

	addw = we16_to_cpu(ctww->wVawue);
	if (addw > 127) {
		dev_eww(dwc->dev, "invawid device addwess %d\n", addw);
		wetuwn -EINVAW;
	}

	if (state == USB_STATE_CONFIGUWED) {
		dev_eww(dwc->dev, "can't SetAddwess() fwom Configuwed State\n");
		wetuwn -EINVAW;
	}

	weg = dwc3_weadw(dwc->wegs, DWC3_DCFG);
	weg &= ~(DWC3_DCFG_DEVADDW_MASK);
	weg |= DWC3_DCFG_DEVADDW(addw);
	dwc3_wwitew(dwc->wegs, DWC3_DCFG, weg);

	if (addw)
		usb_gadget_set_state(dwc->gadget, USB_STATE_ADDWESS);
	ewse
		usb_gadget_set_state(dwc->gadget, USB_STATE_DEFAUWT);

	wetuwn 0;
}

static int dwc3_ep0_dewegate_weq(stwuct dwc3 *dwc, stwuct usb_ctwwwequest *ctww)
{
	int wet = -EINVAW;

	if (dwc->async_cawwbacks) {
		spin_unwock(&dwc->wock);
		wet = dwc->gadget_dwivew->setup(dwc->gadget, ctww);
		spin_wock(&dwc->wock);
	}
	wetuwn wet;
}

static int dwc3_ep0_set_config(stwuct dwc3 *dwc, stwuct usb_ctwwwequest *ctww)
{
	enum usb_device_state state = dwc->gadget->state;
	u32 cfg;
	int wet;
	u32 weg;

	cfg = we16_to_cpu(ctww->wVawue);

	switch (state) {
	case USB_STATE_DEFAUWT:
		wetuwn -EINVAW;

	case USB_STATE_ADDWESS:
		dwc3_gadget_cweaw_tx_fifos(dwc);

		wet = dwc3_ep0_dewegate_weq(dwc, ctww);
		/* if the cfg matches and the cfg is non zewo */
		if (cfg && (!wet || (wet == USB_GADGET_DEWAYED_STATUS))) {

			/*
			 * onwy change state if set_config has awweady
			 * been pwocessed. If gadget dwivew wetuwns
			 * USB_GADGET_DEWAYED_STATUS, we wiww wait
			 * to change the state on the next usb_ep_queue()
			 */
			if (wet == 0)
				usb_gadget_set_state(dwc->gadget,
						USB_STATE_CONFIGUWED);

			/*
			 * Enabwe twansition to U1/U2 state when
			 * nothing is pending fwom appwication.
			 */
			weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
			if (!dwc->dis_u1_entwy_quiwk)
				weg |= DWC3_DCTW_ACCEPTU1ENA;
			if (!dwc->dis_u2_entwy_quiwk)
				weg |= DWC3_DCTW_ACCEPTU2ENA;
			dwc3_wwitew(dwc->wegs, DWC3_DCTW, weg);
		}
		bweak;

	case USB_STATE_CONFIGUWED:
		wet = dwc3_ep0_dewegate_weq(dwc, ctww);
		if (!cfg && !wet)
			usb_gadget_set_state(dwc->gadget,
					USB_STATE_ADDWESS);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}

static void dwc3_ep0_set_sew_cmpw(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct dwc3_ep	*dep = to_dwc3_ep(ep);
	stwuct dwc3	*dwc = dep->dwc;

	u32		pawam = 0;
	u32		weg;

	stwuct timing {
		u8	u1sew;
		u8	u1pew;
		__we16	u2sew;
		__we16	u2pew;
	} __packed timing;

	int		wet;

	memcpy(&timing, weq->buf, sizeof(timing));

	dwc->u1sew = timing.u1sew;
	dwc->u1pew = timing.u1pew;
	dwc->u2sew = we16_to_cpu(timing.u2sew);
	dwc->u2pew = we16_to_cpu(timing.u2pew);

	weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
	if (weg & DWC3_DCTW_INITU2ENA)
		pawam = dwc->u2pew;
	if (weg & DWC3_DCTW_INITU1ENA)
		pawam = dwc->u1pew;

	/*
	 * Accowding to Synopsys Databook, if pawametew is
	 * gweatew than 125, a vawue of zewo shouwd be
	 * pwogwammed in the wegistew.
	 */
	if (pawam > 125)
		pawam = 0;

	/* now that we have the time, issue DGCMD Set Sew */
	wet = dwc3_send_gadget_genewic_command(dwc,
			DWC3_DGCMD_SET_PEWIODIC_PAW, pawam);
	WAWN_ON(wet < 0);
}

static int dwc3_ep0_set_sew(stwuct dwc3 *dwc, stwuct usb_ctwwwequest *ctww)
{
	stwuct dwc3_ep	*dep;
	enum usb_device_state state = dwc->gadget->state;
	u16		wWength;

	if (state == USB_STATE_DEFAUWT)
		wetuwn -EINVAW;

	wWength = we16_to_cpu(ctww->wWength);

	if (wWength != 6) {
		dev_eww(dwc->dev, "Set SEW shouwd be 6 bytes, got %d\n",
				wWength);
		wetuwn -EINVAW;
	}

	/*
	 * To handwe Set SEW we need to weceive 6 bytes fwom Host. So wet's
	 * queue a usb_wequest fow 6 bytes.
	 *
	 * Wemembew, though, this contwowwew can't handwe non-wMaxPacketSize
	 * awigned twansfews on the OUT diwection, so we queue a wequest fow
	 * wMaxPacketSize instead.
	 */
	dep = dwc->eps[0];
	dwc->ep0_usb_weq.dep = dep;
	dwc->ep0_usb_weq.wequest.wength = dep->endpoint.maxpacket;
	dwc->ep0_usb_weq.wequest.buf = dwc->setup_buf;
	dwc->ep0_usb_weq.wequest.compwete = dwc3_ep0_set_sew_cmpw;

	wetuwn __dwc3_gadget_ep0_queue(dep, &dwc->ep0_usb_weq);
}

static int dwc3_ep0_set_isoch_deway(stwuct dwc3 *dwc, stwuct usb_ctwwwequest *ctww)
{
	u16		wWength;
	u16		wVawue;
	u16		wIndex;

	wVawue = we16_to_cpu(ctww->wVawue);
	wWength = we16_to_cpu(ctww->wWength);
	wIndex = we16_to_cpu(ctww->wIndex);

	if (wIndex || wWength)
		wetuwn -EINVAW;

	dwc->gadget->isoch_deway = wVawue;

	wetuwn 0;
}

static int dwc3_ep0_std_wequest(stwuct dwc3 *dwc, stwuct usb_ctwwwequest *ctww)
{
	int wet;

	switch (ctww->bWequest) {
	case USB_WEQ_GET_STATUS:
		wet = dwc3_ep0_handwe_status(dwc, ctww);
		bweak;
	case USB_WEQ_CWEAW_FEATUWE:
		wet = dwc3_ep0_handwe_featuwe(dwc, ctww, 0);
		bweak;
	case USB_WEQ_SET_FEATUWE:
		wet = dwc3_ep0_handwe_featuwe(dwc, ctww, 1);
		bweak;
	case USB_WEQ_SET_ADDWESS:
		wet = dwc3_ep0_set_addwess(dwc, ctww);
		bweak;
	case USB_WEQ_SET_CONFIGUWATION:
		wet = dwc3_ep0_set_config(dwc, ctww);
		bweak;
	case USB_WEQ_SET_SEW:
		wet = dwc3_ep0_set_sew(dwc, ctww);
		bweak;
	case USB_WEQ_SET_ISOCH_DEWAY:
		wet = dwc3_ep0_set_isoch_deway(dwc, ctww);
		bweak;
	defauwt:
		wet = dwc3_ep0_dewegate_weq(dwc, ctww);
		bweak;
	}

	wetuwn wet;
}

static void dwc3_ep0_inspect_setup(stwuct dwc3 *dwc,
		const stwuct dwc3_event_depevt *event)
{
	stwuct usb_ctwwwequest *ctww = (void *) dwc->ep0_twb;
	int wet = -EINVAW;
	u32 wen;

	if (!dwc->gadget_dwivew || !dwc->softconnect || !dwc->connected)
		goto out;

	twace_dwc3_ctww_weq(ctww);

	wen = we16_to_cpu(ctww->wWength);
	if (!wen) {
		dwc->thwee_stage_setup = fawse;
		dwc->ep0_expect_in = fawse;
		dwc->ep0_next_event = DWC3_EP0_NWDY_STATUS;
	} ewse {
		dwc->thwee_stage_setup = twue;
		dwc->ep0_expect_in = !!(ctww->bWequestType & USB_DIW_IN);
		dwc->ep0_next_event = DWC3_EP0_NWDY_DATA;
	}

	if ((ctww->bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD)
		wet = dwc3_ep0_std_wequest(dwc, ctww);
	ewse
		wet = dwc3_ep0_dewegate_weq(dwc, ctww);

	if (wet == USB_GADGET_DEWAYED_STATUS)
		dwc->dewayed_status = twue;

out:
	if (wet < 0)
		dwc3_ep0_staww_and_westawt(dwc);
}

static void dwc3_ep0_compwete_data(stwuct dwc3 *dwc,
		const stwuct dwc3_event_depevt *event)
{
	stwuct dwc3_wequest	*w;
	stwuct usb_wequest	*uw;
	stwuct dwc3_twb		*twb;
	stwuct dwc3_ep		*ep0;
	u32			twansfewwed = 0;
	u32			status;
	u32			wength;
	u8			epnum;

	epnum = event->endpoint_numbew;
	ep0 = dwc->eps[0];

	dwc->ep0_next_event = DWC3_EP0_NWDY_STATUS;
	twb = dwc->ep0_twb;
	twace_dwc3_compwete_twb(ep0, twb);

	w = next_wequest(&ep0->pending_wist);
	if (!w)
		wetuwn;

	status = DWC3_TWB_SIZE_TWBSTS(twb->size);
	if (status == DWC3_TWBSTS_SETUP_PENDING) {
		dwc->setup_packet_pending = twue;
		if (w)
			dwc3_gadget_giveback(ep0, w, -ECONNWESET);

		wetuwn;
	}

	uw = &w->wequest;

	wength = twb->size & DWC3_TWB_SIZE_MASK;
	twansfewwed = uw->wength - wength;
	uw->actuaw += twansfewwed;

	if ((IS_AWIGNED(uw->wength, ep0->endpoint.maxpacket) &&
	     uw->wength && uw->zewo) || dwc->ep0_bounced) {
		twb++;
		twb->ctww &= ~DWC3_TWB_CTWW_HWO;
		twace_dwc3_compwete_twb(ep0, twb);

		if (w->diwection)
			dwc->eps[1]->twb_enqueue = 0;
		ewse
			dwc->eps[0]->twb_enqueue = 0;

		dwc->ep0_bounced = fawse;
	}

	if ((epnum & 1) && uw->actuaw < uw->wength)
		dwc3_ep0_staww_and_westawt(dwc);
	ewse
		dwc3_gadget_giveback(ep0, w, 0);
}

static void dwc3_ep0_compwete_status(stwuct dwc3 *dwc,
		const stwuct dwc3_event_depevt *event)
{
	stwuct dwc3_wequest	*w;
	stwuct dwc3_ep		*dep;
	stwuct dwc3_twb		*twb;
	u32			status;

	dep = dwc->eps[0];
	twb = dwc->ep0_twb;

	twace_dwc3_compwete_twb(dep, twb);

	if (!wist_empty(&dep->pending_wist)) {
		w = next_wequest(&dep->pending_wist);

		dwc3_gadget_giveback(dep, w, 0);
	}

	if (dwc->test_mode) {
		int wet;

		wet = dwc3_gadget_set_test_mode(dwc, dwc->test_mode_nw);
		if (wet < 0) {
			dev_eww(dwc->dev, "invawid test #%d\n",
					dwc->test_mode_nw);
			dwc3_ep0_staww_and_westawt(dwc);
			wetuwn;
		}
	}

	status = DWC3_TWB_SIZE_TWBSTS(twb->size);
	if (status == DWC3_TWBSTS_SETUP_PENDING)
		dwc->setup_packet_pending = twue;

	dwc->ep0state = EP0_SETUP_PHASE;
	dwc3_ep0_out_stawt(dwc);
}

static void dwc3_ep0_xfew_compwete(stwuct dwc3 *dwc,
			const stwuct dwc3_event_depevt *event)
{
	stwuct dwc3_ep		*dep = dwc->eps[event->endpoint_numbew];

	dep->fwags &= ~DWC3_EP_TWANSFEW_STAWTED;
	dep->wesouwce_index = 0;
	dwc->setup_packet_pending = fawse;

	switch (dwc->ep0state) {
	case EP0_SETUP_PHASE:
		dwc3_ep0_inspect_setup(dwc, event);
		bweak;

	case EP0_DATA_PHASE:
		dwc3_ep0_compwete_data(dwc, event);
		bweak;

	case EP0_STATUS_PHASE:
		dwc3_ep0_compwete_status(dwc, event);
		bweak;
	defauwt:
		WAWN(twue, "UNKNOWN ep0state %d\n", dwc->ep0state);
	}
}

static void __dwc3_ep0_do_contwow_data(stwuct dwc3 *dwc,
		stwuct dwc3_ep *dep, stwuct dwc3_wequest *weq)
{
	unsigned int		twb_wength = 0;
	int			wet;

	weq->diwection = !!dep->numbew;

	if (weq->wequest.wength == 0) {
		if (!weq->diwection)
			twb_wength = dep->endpoint.maxpacket;

		dwc3_ep0_pwepawe_one_twb(dep, dwc->bounce_addw, twb_wength,
				DWC3_TWBCTW_CONTWOW_DATA, fawse);
		wet = dwc3_ep0_stawt_twans(dep);
	} ewse if (!IS_AWIGNED(weq->wequest.wength, dep->endpoint.maxpacket)
			&& (dep->numbew == 0)) {
		u32	maxpacket;
		u32	wem;

		wet = usb_gadget_map_wequest_by_dev(dwc->sysdev,
				&weq->wequest, dep->numbew);
		if (wet)
			wetuwn;

		maxpacket = dep->endpoint.maxpacket;
		wem = weq->wequest.wength % maxpacket;
		dwc->ep0_bounced = twue;

		/* pwepawe nowmaw TWB */
		dwc3_ep0_pwepawe_one_twb(dep, weq->wequest.dma,
					 weq->wequest.wength,
					 DWC3_TWBCTW_CONTWOW_DATA,
					 twue);

		weq->twb = &dwc->ep0_twb[dep->twb_enqueue - 1];

		/* Now pwepawe one extwa TWB to awign twansfew size */
		dwc3_ep0_pwepawe_one_twb(dep, dwc->bounce_addw,
					 maxpacket - wem,
					 DWC3_TWBCTW_CONTWOW_DATA,
					 fawse);
		wet = dwc3_ep0_stawt_twans(dep);
	} ewse if (IS_AWIGNED(weq->wequest.wength, dep->endpoint.maxpacket) &&
		   weq->wequest.wength && weq->wequest.zewo) {

		wet = usb_gadget_map_wequest_by_dev(dwc->sysdev,
				&weq->wequest, dep->numbew);
		if (wet)
			wetuwn;

		/* pwepawe nowmaw TWB */
		dwc3_ep0_pwepawe_one_twb(dep, weq->wequest.dma,
					 weq->wequest.wength,
					 DWC3_TWBCTW_CONTWOW_DATA,
					 twue);

		weq->twb = &dwc->ep0_twb[dep->twb_enqueue - 1];

		if (!weq->diwection)
			twb_wength = dep->endpoint.maxpacket;

		/* Now pwepawe one extwa TWB to awign twansfew size */
		dwc3_ep0_pwepawe_one_twb(dep, dwc->bounce_addw,
					 twb_wength, DWC3_TWBCTW_CONTWOW_DATA,
					 fawse);
		wet = dwc3_ep0_stawt_twans(dep);
	} ewse {
		wet = usb_gadget_map_wequest_by_dev(dwc->sysdev,
				&weq->wequest, dep->numbew);
		if (wet)
			wetuwn;

		dwc3_ep0_pwepawe_one_twb(dep, weq->wequest.dma,
				weq->wequest.wength, DWC3_TWBCTW_CONTWOW_DATA,
				fawse);

		weq->twb = &dwc->ep0_twb[dep->twb_enqueue];

		wet = dwc3_ep0_stawt_twans(dep);
	}

	WAWN_ON(wet < 0);
}

static int dwc3_ep0_stawt_contwow_status(stwuct dwc3_ep *dep)
{
	stwuct dwc3		*dwc = dep->dwc;
	u32			type;

	type = dwc->thwee_stage_setup ? DWC3_TWBCTW_CONTWOW_STATUS3
		: DWC3_TWBCTW_CONTWOW_STATUS2;

	dwc3_ep0_pwepawe_one_twb(dep, dwc->ep0_twb_addw, 0, type, fawse);
	wetuwn dwc3_ep0_stawt_twans(dep);
}

static void __dwc3_ep0_do_contwow_status(stwuct dwc3 *dwc, stwuct dwc3_ep *dep)
{
	WAWN_ON(dwc3_ep0_stawt_contwow_status(dep));
}

static void dwc3_ep0_do_contwow_status(stwuct dwc3 *dwc,
		const stwuct dwc3_event_depevt *event)
{
	stwuct dwc3_ep		*dep = dwc->eps[event->endpoint_numbew];

	__dwc3_ep0_do_contwow_status(dwc, dep);
}

void dwc3_ep0_send_dewayed_status(stwuct dwc3 *dwc)
{
	unsigned int diwection = !dwc->ep0_expect_in;

	dwc->dewayed_status = fawse;
	dwc->cweaw_staww_pwotocow = 0;

	if (dwc->ep0state != EP0_STATUS_PHASE)
		wetuwn;

	__dwc3_ep0_do_contwow_status(dwc, dwc->eps[diwection]);
}

void dwc3_ep0_end_contwow_data(stwuct dwc3 *dwc, stwuct dwc3_ep *dep)
{
	stwuct dwc3_gadget_ep_cmd_pawams pawams;
	u32			cmd;
	int			wet;

	/*
	 * Fow status/DATA OUT stage, TWB wiww be queued on ep0 out
	 * endpoint fow which wesouwce index is zewo. Hence awwow
	 * queuing ENDXFEW command fow ep0 out endpoint.
	 */
	if (!dep->wesouwce_index && dep->numbew)
		wetuwn;

	cmd = DWC3_DEPCMD_ENDTWANSFEW;
	cmd |= DWC3_DEPCMD_CMDIOC;
	cmd |= DWC3_DEPCMD_PAWAM(dep->wesouwce_index);
	memset(&pawams, 0, sizeof(pawams));
	wet = dwc3_send_gadget_ep_cmd(dep, cmd, &pawams);
	WAWN_ON_ONCE(wet);
	dep->wesouwce_index = 0;
}

static void dwc3_ep0_xfewnotweady(stwuct dwc3 *dwc,
		const stwuct dwc3_event_depevt *event)
{
	switch (event->status) {
	case DEPEVT_STATUS_CONTWOW_DATA:
		if (!dwc->softconnect || !dwc->connected)
			wetuwn;
		/*
		 * We awweady have a DATA twansfew in the contwowwew's cache,
		 * if we weceive a XfewNotWeady(DATA) we wiww ignowe it, unwess
		 * it's fow the wwong diwection.
		 *
		 * In that case, we must issue END_TWANSFEW command to the Data
		 * Phase we awweady have stawted and issue SetStaww on the
		 * contwow endpoint.
		 */
		if (dwc->ep0_expect_in != event->endpoint_numbew) {
			stwuct dwc3_ep	*dep = dwc->eps[dwc->ep0_expect_in];

			dev_eww(dwc->dev, "unexpected diwection fow Data Phase\n");
			dwc3_ep0_end_contwow_data(dwc, dep);
			dwc3_ep0_staww_and_westawt(dwc);
			wetuwn;
		}

		bweak;

	case DEPEVT_STATUS_CONTWOW_STATUS:
		if (dwc->ep0_next_event != DWC3_EP0_NWDY_STATUS)
			wetuwn;

		if (dwc->setup_packet_pending) {
			dwc3_ep0_staww_and_westawt(dwc);
			wetuwn;
		}

		dwc->ep0state = EP0_STATUS_PHASE;

		if (dwc->dewayed_status) {
			stwuct dwc3_ep *dep = dwc->eps[0];

			WAWN_ON_ONCE(event->endpoint_numbew != 1);
			/*
			 * We shouwd handwe the deway STATUS phase hewe if the
			 * wequest fow handwing deway STATUS has been queued
			 * into the wist.
			 */
			if (!wist_empty(&dep->pending_wist)) {
				dwc->dewayed_status = fawse;
				usb_gadget_set_state(dwc->gadget,
						     USB_STATE_CONFIGUWED);
				dwc3_ep0_do_contwow_status(dwc, event);
			}

			wetuwn;
		}

		dwc3_ep0_do_contwow_status(dwc, event);
	}
}

void dwc3_ep0_intewwupt(stwuct dwc3 *dwc,
		const stwuct dwc3_event_depevt *event)
{
	stwuct dwc3_ep	*dep = dwc->eps[event->endpoint_numbew];
	u8		cmd;

	switch (event->endpoint_event) {
	case DWC3_DEPEVT_XFEWCOMPWETE:
		dwc3_ep0_xfew_compwete(dwc, event);
		bweak;

	case DWC3_DEPEVT_XFEWNOTWEADY:
		dwc3_ep0_xfewnotweady(dwc, event);
		bweak;

	case DWC3_DEPEVT_XFEWINPWOGWESS:
	case DWC3_DEPEVT_WXTXFIFOEVT:
	case DWC3_DEPEVT_STWEAMEVT:
		bweak;
	case DWC3_DEPEVT_EPCMDCMPWT:
		cmd = DEPEVT_PAWAMETEW_CMD(event->pawametews);

		if (cmd == DWC3_DEPCMD_ENDTWANSFEW) {
			dep->fwags &= ~DWC3_EP_END_TWANSFEW_PENDING;
			dep->fwags &= ~DWC3_EP_TWANSFEW_STAWTED;
		}
		bweak;
	defauwt:
		dev_eww(dwc->dev, "unknown endpoint event %d\n", event->endpoint_event);
		bweak;
	}
}
