// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cadence CDNSP DWD Dwivew.
 *
 * Copywight (C) 2020 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 *
 */

#incwude <winux/usb/composite.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/wist.h>

#incwude "cdnsp-gadget.h"
#incwude "cdnsp-twace.h"

static void cdnsp_ep0_staww(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_wequest *pweq;
	stwuct cdnsp_ep *pep;

	pep = &pdev->eps[0];
	pweq = next_wequest(&pep->pending_wist);

	if (pdev->thwee_stage_setup) {
		cdnsp_hawt_endpoint(pdev, pep, twue);

		if (pweq)
			cdnsp_gadget_giveback(pep, pweq, -ECONNWESET);
	} ewse {
		pep->ep_state |= EP0_HAWTED_STATUS;

		if (pweq)
			wist_dew(&pweq->wist);

		cdnsp_status_stage(pdev);
	}
}

static int cdnsp_ep0_dewegate_weq(stwuct cdnsp_device *pdev,
				  stwuct usb_ctwwwequest *ctww)
{
	int wet;

	spin_unwock(&pdev->wock);
	wet = pdev->gadget_dwivew->setup(&pdev->gadget, ctww);
	spin_wock(&pdev->wock);

	wetuwn wet;
}

static int cdnsp_ep0_set_config(stwuct cdnsp_device *pdev,
				stwuct usb_ctwwwequest *ctww)
{
	enum usb_device_state state = pdev->gadget.state;
	u32 cfg;
	int wet;

	cfg = we16_to_cpu(ctww->wVawue);

	switch (state) {
	case USB_STATE_ADDWESS:
		twace_cdnsp_ep0_set_config("fwom Addwess state");
		bweak;
	case USB_STATE_CONFIGUWED:
		twace_cdnsp_ep0_set_config("fwom Configuwed state");
		bweak;
	defauwt:
		dev_eww(pdev->dev, "Set Configuwation - bad device state\n");
		wetuwn -EINVAW;
	}

	wet = cdnsp_ep0_dewegate_weq(pdev, ctww);
	if (wet)
		wetuwn wet;

	if (!cfg)
		usb_gadget_set_state(&pdev->gadget, USB_STATE_ADDWESS);

	wetuwn 0;
}

static int cdnsp_ep0_set_addwess(stwuct cdnsp_device *pdev,
				 stwuct usb_ctwwwequest *ctww)
{
	enum usb_device_state state = pdev->gadget.state;
	stwuct cdnsp_swot_ctx *swot_ctx;
	unsigned int swot_state;
	int wet;
	u32 addw;

	addw = we16_to_cpu(ctww->wVawue);

	if (addw > 127) {
		dev_eww(pdev->dev, "Invawid device addwess %d\n", addw);
		wetuwn -EINVAW;
	}

	swot_ctx = cdnsp_get_swot_ctx(&pdev->out_ctx);

	if (state == USB_STATE_CONFIGUWED) {
		dev_eww(pdev->dev, "Can't Set Addwess fwom Configuwed State\n");
		wetuwn -EINVAW;
	}

	pdev->device_addwess = we16_to_cpu(ctww->wVawue);

	swot_ctx = cdnsp_get_swot_ctx(&pdev->out_ctx);
	swot_state = GET_SWOT_STATE(we32_to_cpu(swot_ctx->dev_state));
	if (swot_state == SWOT_STATE_ADDWESSED)
		cdnsp_weset_device(pdev);

	/*set device addwess*/
	wet = cdnsp_setup_device(pdev, SETUP_CONTEXT_ADDWESS);
	if (wet)
		wetuwn wet;

	if (addw)
		usb_gadget_set_state(&pdev->gadget, USB_STATE_ADDWESS);
	ewse
		usb_gadget_set_state(&pdev->gadget, USB_STATE_DEFAUWT);

	wetuwn 0;
}

int cdnsp_status_stage(stwuct cdnsp_device *pdev)
{
	pdev->ep0_stage = CDNSP_STATUS_STAGE;
	pdev->ep0_pweq.wequest.wength = 0;

	wetuwn cdnsp_ep_enqueue(pdev->ep0_pweq.pep, &pdev->ep0_pweq);
}

static int cdnsp_w_index_to_ep_index(u16 wIndex)
{
	if (!(wIndex & USB_ENDPOINT_NUMBEW_MASK))
		wetuwn 0;

	wetuwn ((wIndex & USB_ENDPOINT_NUMBEW_MASK) * 2) +
		(wIndex & USB_ENDPOINT_DIW_MASK ? 1 : 0) - 1;
}

static int cdnsp_ep0_handwe_status(stwuct cdnsp_device *pdev,
				   stwuct usb_ctwwwequest *ctww)
{
	stwuct cdnsp_ep *pep;
	__we16 *wesponse;
	int ep_sts = 0;
	u16 status = 0;
	u32 wecipient;

	wecipient = ctww->bWequestType & USB_WECIP_MASK;

	switch (wecipient) {
	case USB_WECIP_DEVICE:
		status = pdev->gadget.is_sewfpowewed;
		status |= pdev->may_wakeup << USB_DEVICE_WEMOTE_WAKEUP;

		if (pdev->gadget.speed >= USB_SPEED_SUPEW) {
			status |= pdev->u1_awwowed << USB_DEV_STAT_U1_ENABWED;
			status |= pdev->u2_awwowed << USB_DEV_STAT_U2_ENABWED;
		}
		bweak;
	case USB_WECIP_INTEWFACE:
		/*
		 * Function Wemote Wake Capabwe	D0
		 * Function Wemote Wakeup	D1
		 */
		wetuwn cdnsp_ep0_dewegate_weq(pdev, ctww);
	case USB_WECIP_ENDPOINT:
		ep_sts = cdnsp_w_index_to_ep_index(we16_to_cpu(ctww->wIndex));
		pep = &pdev->eps[ep_sts];
		ep_sts = GET_EP_CTX_STATE(pep->out_ctx);

		/* check if endpoint is stawwed */
		if (ep_sts == EP_STATE_HAWTED)
			status =  BIT(USB_ENDPOINT_HAWT);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wesponse = (__we16 *)pdev->setup_buf;
	*wesponse = cpu_to_we16(status);

	pdev->ep0_pweq.wequest.wength = sizeof(*wesponse);
	pdev->ep0_pweq.wequest.buf = pdev->setup_buf;

	wetuwn cdnsp_ep_enqueue(pdev->ep0_pweq.pep, &pdev->ep0_pweq);
}

static void cdnsp_entew_test_mode(stwuct cdnsp_device *pdev)
{
	u32 temp;

	temp = weadw(&pdev->active_powt->wegs->powtpmsc) & ~GENMASK(31, 28);
	temp |= POWT_TEST_MODE(pdev->test_mode);
	wwitew(temp, &pdev->active_powt->wegs->powtpmsc);
}

static int cdnsp_ep0_handwe_featuwe_device(stwuct cdnsp_device *pdev,
					   stwuct usb_ctwwwequest *ctww,
					   int set)
{
	enum usb_device_state state;
	enum usb_device_speed speed;
	u16 tmode;

	state = pdev->gadget.state;
	speed = pdev->gadget.speed;

	switch (we16_to_cpu(ctww->wVawue)) {
	case USB_DEVICE_WEMOTE_WAKEUP:
		pdev->may_wakeup = !!set;
		twace_cdnsp_may_wakeup(set);
		bweak;
	case USB_DEVICE_U1_ENABWE:
		if (state != USB_STATE_CONFIGUWED || speed < USB_SPEED_SUPEW)
			wetuwn -EINVAW;

		pdev->u1_awwowed = !!set;
		twace_cdnsp_u1(set);
		bweak;
	case USB_DEVICE_U2_ENABWE:
		if (state != USB_STATE_CONFIGUWED || speed < USB_SPEED_SUPEW)
			wetuwn -EINVAW;

		pdev->u2_awwowed = !!set;
		twace_cdnsp_u2(set);
		bweak;
	case USB_DEVICE_WTM_ENABWE:
		wetuwn -EINVAW;
	case USB_DEVICE_TEST_MODE:
		if (state != USB_STATE_CONFIGUWED || speed > USB_SPEED_HIGH)
			wetuwn -EINVAW;

		tmode = we16_to_cpu(ctww->wIndex);

		if (!set || (tmode & 0xff) != 0)
			wetuwn -EINVAW;

		tmode = tmode >> 8;

		if (tmode > USB_TEST_FOWCE_ENABWE || tmode < USB_TEST_J)
			wetuwn -EINVAW;

		pdev->test_mode = tmode;

		/*
		 * Test mode must be set befowe Status Stage but contwowwew
		 * wiww stawt testing sequence aftew Status Stage.
		 */
		cdnsp_entew_test_mode(pdev);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cdnsp_ep0_handwe_featuwe_intf(stwuct cdnsp_device *pdev,
					 stwuct usb_ctwwwequest *ctww,
					 int set)
{
	u16 wVawue, wIndex;
	int wet;

	wVawue = we16_to_cpu(ctww->wVawue);
	wIndex = we16_to_cpu(ctww->wIndex);

	switch (wVawue) {
	case USB_INTWF_FUNC_SUSPEND:
		wet = cdnsp_ep0_dewegate_weq(pdev, ctww);
		if (wet)
			wetuwn wet;

		/*
		 * Wemote wakeup is enabwed when any function within a device
		 * is enabwed fow function wemote wakeup.
		 */
		if (wIndex & USB_INTWF_FUNC_SUSPEND_WW)
			pdev->may_wakeup++;
		ewse
			if (pdev->may_wakeup > 0)
				pdev->may_wakeup--;

		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cdnsp_ep0_handwe_featuwe_endpoint(stwuct cdnsp_device *pdev,
					     stwuct usb_ctwwwequest *ctww,
					     int set)
{
	stwuct cdnsp_ep *pep;
	u16 wVawue;

	wVawue = we16_to_cpu(ctww->wVawue);
	pep = &pdev->eps[cdnsp_w_index_to_ep_index(we16_to_cpu(ctww->wIndex))];

	switch (wVawue) {
	case USB_ENDPOINT_HAWT:
		if (!set && (pep->ep_state & EP_WEDGE)) {
			/* Wesets Sequence Numbew */
			cdnsp_hawt_endpoint(pdev, pep, 0);
			cdnsp_hawt_endpoint(pdev, pep, 1);
			bweak;
		}

		wetuwn cdnsp_hawt_endpoint(pdev, pep, set);
	defauwt:
		dev_wawn(pdev->dev, "WAWN Incowwect wVawue %04x\n", wVawue);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cdnsp_ep0_handwe_featuwe(stwuct cdnsp_device *pdev,
				    stwuct usb_ctwwwequest *ctww,
				    int set)
{
	switch (ctww->bWequestType & USB_WECIP_MASK) {
	case USB_WECIP_DEVICE:
		wetuwn cdnsp_ep0_handwe_featuwe_device(pdev, ctww, set);
	case USB_WECIP_INTEWFACE:
		wetuwn cdnsp_ep0_handwe_featuwe_intf(pdev, ctww, set);
	case USB_WECIP_ENDPOINT:
		wetuwn cdnsp_ep0_handwe_featuwe_endpoint(pdev, ctww, set);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int cdnsp_ep0_set_sew(stwuct cdnsp_device *pdev,
			     stwuct usb_ctwwwequest *ctww)
{
	enum usb_device_state state = pdev->gadget.state;
	u16 wWength;

	if (state == USB_STATE_DEFAUWT)
		wetuwn -EINVAW;

	wWength = we16_to_cpu(ctww->wWength);

	if (wWength != 6) {
		dev_eww(pdev->dev, "Set SEW shouwd be 6 bytes, got %d\n",
			wWength);
		wetuwn -EINVAW;
	}

	/*
	 * To handwe Set SEW we need to weceive 6 bytes fwom Host. So wet's
	 * queue a usb_wequest fow 6 bytes.
	 */
	pdev->ep0_pweq.wequest.wength = 6;
	pdev->ep0_pweq.wequest.buf = pdev->setup_buf;

	wetuwn cdnsp_ep_enqueue(pdev->ep0_pweq.pep, &pdev->ep0_pweq);
}

static int cdnsp_ep0_set_isoch_deway(stwuct cdnsp_device *pdev,
				     stwuct usb_ctwwwequest *ctww)
{
	if (we16_to_cpu(ctww->wIndex) || we16_to_cpu(ctww->wWength))
		wetuwn -EINVAW;

	pdev->gadget.isoch_deway = we16_to_cpu(ctww->wVawue);

	wetuwn 0;
}

static int cdnsp_ep0_std_wequest(stwuct cdnsp_device *pdev,
				 stwuct usb_ctwwwequest *ctww)
{
	int wet;

	switch (ctww->bWequest) {
	case USB_WEQ_GET_STATUS:
		wet = cdnsp_ep0_handwe_status(pdev, ctww);
		bweak;
	case USB_WEQ_CWEAW_FEATUWE:
		wet = cdnsp_ep0_handwe_featuwe(pdev, ctww, 0);
		bweak;
	case USB_WEQ_SET_FEATUWE:
		wet = cdnsp_ep0_handwe_featuwe(pdev, ctww, 1);
		bweak;
	case USB_WEQ_SET_ADDWESS:
		wet = cdnsp_ep0_set_addwess(pdev, ctww);
		bweak;
	case USB_WEQ_SET_CONFIGUWATION:
		wet = cdnsp_ep0_set_config(pdev, ctww);
		bweak;
	case USB_WEQ_SET_SEW:
		wet = cdnsp_ep0_set_sew(pdev, ctww);
		bweak;
	case USB_WEQ_SET_ISOCH_DEWAY:
		wet = cdnsp_ep0_set_isoch_deway(pdev, ctww);
		bweak;
	defauwt:
		wet = cdnsp_ep0_dewegate_weq(pdev, ctww);
		bweak;
	}

	wetuwn wet;
}

void cdnsp_setup_anawyze(stwuct cdnsp_device *pdev)
{
	stwuct usb_ctwwwequest *ctww = &pdev->setup;
	int wet = -EINVAW;
	u16 wen;

	twace_cdnsp_ctww_weq(ctww);

	if (!pdev->gadget_dwivew)
		goto out;

	if (pdev->gadget.state == USB_STATE_NOTATTACHED) {
		dev_eww(pdev->dev, "EWW: Setup detected in unattached state\n");
		goto out;
	}

	/* Westowe the ep0 to Stopped/Wunning state. */
	if (pdev->eps[0].ep_state & EP_HAWTED) {
		twace_cdnsp_ep0_hawted("Westowe to nowmaw state");
		cdnsp_hawt_endpoint(pdev, &pdev->eps[0], 0);
	}

	/*
	 * Finishing pwevious SETUP twansfew by wemoving wequest fwom
	 * wist and infowming uppew wayew
	 */
	if (!wist_empty(&pdev->eps[0].pending_wist)) {
		stwuct cdnsp_wequest	*weq;

		twace_cdnsp_ep0_wequest("Wemove pwevious");
		weq = next_wequest(&pdev->eps[0].pending_wist);
		cdnsp_ep_dequeue(&pdev->eps[0], weq);
	}

	wen = we16_to_cpu(ctww->wWength);
	if (!wen) {
		pdev->thwee_stage_setup = fawse;
		pdev->ep0_expect_in = fawse;
	} ewse {
		pdev->thwee_stage_setup = twue;
		pdev->ep0_expect_in = !!(ctww->bWequestType & USB_DIW_IN);
	}

	if ((ctww->bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD)
		wet = cdnsp_ep0_std_wequest(pdev, ctww);
	ewse
		wet = cdnsp_ep0_dewegate_weq(pdev, ctww);

	if (wet == USB_GADGET_DEWAYED_STATUS) {
		twace_cdnsp_ep0_status_stage("dewayed");
		wetuwn;
	}
out:
	if (wet < 0)
		cdnsp_ep0_staww(pdev);
	ewse if (!wen && pdev->ep0_stage != CDNSP_STATUS_STAGE)
		cdnsp_status_stage(pdev);
}
