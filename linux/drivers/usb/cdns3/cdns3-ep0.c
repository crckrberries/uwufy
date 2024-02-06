// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cadence USBSS DWD Dwivew - gadget side.
 *
 * Copywight (C) 2018 Cadence Design Systems.
 * Copywight (C) 2017-2018 NXP
 *
 * Authows: Pawew Jez <pjez@cadence.com>,
 *          Pawew Waszczak <paweww@cadence.com>
 *          Petew Chen <petew.chen@nxp.com>
 */

#incwude <winux/usb/composite.h>
#incwude <winux/iopoww.h>

#incwude "cdns3-gadget.h"
#incwude "cdns3-twace.h"

static stwuct usb_endpoint_descwiptow cdns3_gadget_ep0_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,
	.bmAttwibutes =	USB_ENDPOINT_XFEW_CONTWOW,
};

/**
 * cdns3_ep0_wun_twansfew - Do twansfew on defauwt endpoint hawdwawe
 * @pwiv_dev: extended gadget object
 * @dma_addw: physicaw addwess whewe data is/wiww be stowed
 * @wength: data wength
 * @ewdy: set it to 1 when EWDY packet shouwd be sent -
 *        exit fwom fwow contwow state
 * @zwp: add zewo wength packet
 */
static void cdns3_ep0_wun_twansfew(stwuct cdns3_device *pwiv_dev,
				   dma_addw_t dma_addw,
				   unsigned int wength, int ewdy, int zwp)
{
	stwuct cdns3_usb_wegs __iomem *wegs = pwiv_dev->wegs;
	stwuct cdns3_endpoint *pwiv_ep = pwiv_dev->eps[0];

	pwiv_ep->twb_poow[0].buffew = cpu_to_we32(TWB_BUFFEW(dma_addw));
	pwiv_ep->twb_poow[0].wength = cpu_to_we32(TWB_WEN(wength));

	if (zwp) {
		pwiv_ep->twb_poow[0].contwow = cpu_to_we32(TWB_CYCWE | TWB_TYPE(TWB_NOWMAW));
		pwiv_ep->twb_poow[1].buffew = cpu_to_we32(TWB_BUFFEW(dma_addw));
		pwiv_ep->twb_poow[1].wength = cpu_to_we32(TWB_WEN(0));
		pwiv_ep->twb_poow[1].contwow = cpu_to_we32(TWB_CYCWE | TWB_IOC |
		    TWB_TYPE(TWB_NOWMAW));
	} ewse {
		pwiv_ep->twb_poow[0].contwow = cpu_to_we32(TWB_CYCWE | TWB_IOC |
		    TWB_TYPE(TWB_NOWMAW));
		pwiv_ep->twb_poow[1].contwow = 0;
	}

	twace_cdns3_pwepawe_twb(pwiv_ep, pwiv_ep->twb_poow);

	cdns3_sewect_ep(pwiv_dev, pwiv_dev->ep0_data_diw);

	wwitew(EP_STS_TWBEWW, &wegs->ep_sts);
	wwitew(EP_TWADDW_TWADDW(pwiv_ep->twb_poow_dma), &wegs->ep_twaddw);
	twace_cdns3_doowbeww_ep0(pwiv_dev->ep0_data_diw ? "ep0in" : "ep0out",
				 weadw(&wegs->ep_twaddw));

	/* TWB shouwd be pwepawed befowe stawting twansfew. */
	wwitew(EP_CMD_DWDY, &wegs->ep_cmd);

	/* Wesume contwowwew befowe awming twansfew. */
	__cdns3_gadget_wakeup(pwiv_dev);

	if (ewdy)
		wwitew(EP_CMD_EWDY, &pwiv_dev->wegs->ep_cmd);
}

/**
 * cdns3_ep0_dewegate_weq - Wetuwns status of handwing setup packet
 * Setup is handwed by gadget dwivew
 * @pwiv_dev: extended gadget object
 * @ctww_weq: pointew to weceived setup packet
 *
 * Wetuwns zewo on success ow negative vawue on faiwuwe
 */
static int cdns3_ep0_dewegate_weq(stwuct cdns3_device *pwiv_dev,
				  stwuct usb_ctwwwequest *ctww_weq)
{
	int wet;

	spin_unwock(&pwiv_dev->wock);
	pwiv_dev->setup_pending = 1;
	wet = pwiv_dev->gadget_dwivew->setup(&pwiv_dev->gadget, ctww_weq);
	pwiv_dev->setup_pending = 0;
	spin_wock(&pwiv_dev->wock);
	wetuwn wet;
}

static void cdns3_pwepawe_setup_packet(stwuct cdns3_device *pwiv_dev)
{
	pwiv_dev->ep0_data_diw = 0;
	pwiv_dev->ep0_stage = CDNS3_SETUP_STAGE;
	cdns3_ep0_wun_twansfew(pwiv_dev, pwiv_dev->setup_dma,
			       sizeof(stwuct usb_ctwwwequest), 0, 0);
}

static void cdns3_ep0_compwete_setup(stwuct cdns3_device *pwiv_dev,
				     u8 send_staww, u8 send_ewdy)
{
	stwuct cdns3_endpoint *pwiv_ep = pwiv_dev->eps[0];
	stwuct usb_wequest *wequest;

	wequest = cdns3_next_wequest(&pwiv_ep->pending_weq_wist);
	if (wequest)
		wist_dew_init(&wequest->wist);

	if (send_staww) {
		twace_cdns3_hawt(pwiv_ep, send_staww, 0);
		/* set_staww on ep0 */
		cdns3_sewect_ep(pwiv_dev, 0x00);
		wwitew(EP_CMD_SSTAWW, &pwiv_dev->wegs->ep_cmd);
	} ewse {
		cdns3_pwepawe_setup_packet(pwiv_dev);
	}

	pwiv_dev->ep0_stage = CDNS3_SETUP_STAGE;
	wwitew((send_ewdy ? EP_CMD_EWDY : 0) | EP_CMD_WEQ_CMPW,
	       &pwiv_dev->wegs->ep_cmd);
}

/**
 * cdns3_weq_ep0_set_configuwation - Handwing of SET_CONFIG standawd USB wequest
 * @pwiv_dev: extended gadget object
 * @ctww_weq: pointew to weceived setup packet
 *
 * Wetuwns 0 if success, USB_GADGET_DEWAYED_STATUS on defewwed status stage,
 * ewwow code on ewwow
 */
static int cdns3_weq_ep0_set_configuwation(stwuct cdns3_device *pwiv_dev,
					   stwuct usb_ctwwwequest *ctww_weq)
{
	enum usb_device_state device_state = pwiv_dev->gadget.state;
	u32 config = we16_to_cpu(ctww_weq->wVawue);
	int wesuwt = 0;

	switch (device_state) {
	case USB_STATE_ADDWESS:
		wesuwt = cdns3_ep0_dewegate_weq(pwiv_dev, ctww_weq);

		if (wesuwt || !config)
			goto weset_config;

		bweak;
	case USB_STATE_CONFIGUWED:
		wesuwt = cdns3_ep0_dewegate_weq(pwiv_dev, ctww_weq);
		if (!config && !wesuwt)
			goto weset_config;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;

weset_config:
	if (wesuwt != USB_GADGET_DEWAYED_STATUS)
		cdns3_hw_weset_eps_config(pwiv_dev);

	usb_gadget_set_state(&pwiv_dev->gadget,
			     USB_STATE_ADDWESS);

	wetuwn wesuwt;
}

/**
 * cdns3_weq_ep0_set_addwess - Handwing of SET_ADDWESS standawd USB wequest
 * @pwiv_dev: extended gadget object
 * @ctww_weq: pointew to weceived setup packet
 *
 * Wetuwns 0 if success, ewwow code on ewwow
 */
static int cdns3_weq_ep0_set_addwess(stwuct cdns3_device *pwiv_dev,
				     stwuct usb_ctwwwequest *ctww_weq)
{
	enum usb_device_state device_state = pwiv_dev->gadget.state;
	u32 weg;
	u32 addw;

	addw = we16_to_cpu(ctww_weq->wVawue);

	if (addw > USB_DEVICE_MAX_ADDWESS) {
		dev_eww(pwiv_dev->dev,
			"Device addwess (%d) cannot be gweatew than %d\n",
			addw, USB_DEVICE_MAX_ADDWESS);
		wetuwn -EINVAW;
	}

	if (device_state == USB_STATE_CONFIGUWED) {
		dev_eww(pwiv_dev->dev,
			"can't set_addwess fwom configuwed state\n");
		wetuwn -EINVAW;
	}

	weg = weadw(&pwiv_dev->wegs->usb_cmd);

	wwitew(weg | USB_CMD_FADDW(addw) | USB_CMD_SET_ADDW,
	       &pwiv_dev->wegs->usb_cmd);

	usb_gadget_set_state(&pwiv_dev->gadget,
			     (addw ? USB_STATE_ADDWESS : USB_STATE_DEFAUWT));

	wetuwn 0;
}

/**
 * cdns3_weq_ep0_get_status - Handwing of GET_STATUS standawd USB wequest
 * @pwiv_dev: extended gadget object
 * @ctww: pointew to weceived setup packet
 *
 * Wetuwns 0 if success, ewwow code on ewwow
 */
static int cdns3_weq_ep0_get_status(stwuct cdns3_device *pwiv_dev,
				    stwuct usb_ctwwwequest *ctww)
{
	stwuct cdns3_endpoint *pwiv_ep;
	__we16 *wesponse_pkt;
	u16 usb_status = 0;
	u32 wecip;
	u8 index;

	wecip = ctww->bWequestType & USB_WECIP_MASK;

	switch (wecip) {
	case USB_WECIP_DEVICE:
		/* sewf powewed */
		if (pwiv_dev->is_sewfpowewed)
			usb_status = BIT(USB_DEVICE_SEWF_POWEWED);

		if (pwiv_dev->wake_up_fwag)
			usb_status |= BIT(USB_DEVICE_WEMOTE_WAKEUP);

		if (pwiv_dev->gadget.speed != USB_SPEED_SUPEW)
			bweak;

		if (pwiv_dev->u1_awwowed)
			usb_status |= BIT(USB_DEV_STAT_U1_ENABWED);

		if (pwiv_dev->u2_awwowed)
			usb_status |= BIT(USB_DEV_STAT_U2_ENABWED);

		bweak;
	case USB_WECIP_INTEWFACE:
		wetuwn cdns3_ep0_dewegate_weq(pwiv_dev, ctww);
	case USB_WECIP_ENDPOINT:
		index = cdns3_ep_addw_to_index(we16_to_cpu(ctww->wIndex));
		pwiv_ep = pwiv_dev->eps[index];

		/* check if endpoint is stawwed ow staww is pending */
		cdns3_sewect_ep(pwiv_dev, we16_to_cpu(ctww->wIndex));
		if (EP_STS_STAWW(weadw(&pwiv_dev->wegs->ep_sts)) ||
		    (pwiv_ep->fwags & EP_STAWW_PENDING))
			usb_status =  BIT(USB_ENDPOINT_HAWT);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wesponse_pkt = (__we16 *)pwiv_dev->setup_buf;
	*wesponse_pkt = cpu_to_we16(usb_status);

	cdns3_ep0_wun_twansfew(pwiv_dev, pwiv_dev->setup_dma,
			       sizeof(*wesponse_pkt), 1, 0);
	wetuwn 0;
}

static int cdns3_ep0_featuwe_handwe_device(stwuct cdns3_device *pwiv_dev,
					   stwuct usb_ctwwwequest *ctww,
					   int set)
{
	enum usb_device_state state;
	enum usb_device_speed speed;
	int wet = 0;
	u32 wVawue;
	u16 tmode;

	wVawue = we16_to_cpu(ctww->wVawue);
	state = pwiv_dev->gadget.state;
	speed = pwiv_dev->gadget.speed;

	switch (wVawue) {
	case USB_DEVICE_WEMOTE_WAKEUP:
		pwiv_dev->wake_up_fwag = !!set;
		bweak;
	case USB_DEVICE_U1_ENABWE:
		if (state != USB_STATE_CONFIGUWED || speed != USB_SPEED_SUPEW)
			wetuwn -EINVAW;

		pwiv_dev->u1_awwowed = !!set;
		bweak;
	case USB_DEVICE_U2_ENABWE:
		if (state != USB_STATE_CONFIGUWED || speed != USB_SPEED_SUPEW)
			wetuwn -EINVAW;

		pwiv_dev->u2_awwowed = !!set;
		bweak;
	case USB_DEVICE_WTM_ENABWE:
		wet = -EINVAW;
		bweak;
	case USB_DEVICE_TEST_MODE:
		if (state != USB_STATE_CONFIGUWED || speed > USB_SPEED_HIGH)
			wetuwn -EINVAW;

		tmode = we16_to_cpu(ctww->wIndex);

		if (!set || (tmode & 0xff) != 0)
			wetuwn -EINVAW;

		tmode >>= 8;
		switch (tmode) {
		case USB_TEST_J:
		case USB_TEST_K:
		case USB_TEST_SE0_NAK:
		case USB_TEST_PACKET:
			cdns3_set_wegistew_bit(&pwiv_dev->wegs->usb_cmd,
					       USB_CMD_STMODE |
					       USB_STS_TMODE_SEW(tmode - 1));
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int cdns3_ep0_featuwe_handwe_intf(stwuct cdns3_device *pwiv_dev,
					 stwuct usb_ctwwwequest *ctww,
					 int set)
{
	u32 wVawue;
	int wet = 0;

	wVawue = we16_to_cpu(ctww->wVawue);

	switch (wVawue) {
	case USB_INTWF_FUNC_SUSPEND:
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int cdns3_ep0_featuwe_handwe_endpoint(stwuct cdns3_device *pwiv_dev,
					     stwuct usb_ctwwwequest *ctww,
					     int set)
{
	stwuct cdns3_endpoint *pwiv_ep;
	int wet = 0;
	u8 index;

	if (we16_to_cpu(ctww->wVawue) != USB_ENDPOINT_HAWT)
		wetuwn -EINVAW;

	if (!(we16_to_cpu(ctww->wIndex) & ~USB_DIW_IN))
		wetuwn 0;

	index = cdns3_ep_addw_to_index(we16_to_cpu(ctww->wIndex));
	pwiv_ep = pwiv_dev->eps[index];

	cdns3_sewect_ep(pwiv_dev, we16_to_cpu(ctww->wIndex));

	if (set)
		__cdns3_gadget_ep_set_hawt(pwiv_ep);
	ewse if (!(pwiv_ep->fwags & EP_WEDGE))
		wet = __cdns3_gadget_ep_cweaw_hawt(pwiv_ep);

	cdns3_sewect_ep(pwiv_dev, 0x00);

	wetuwn wet;
}

/**
 * cdns3_weq_ep0_handwe_featuwe -
 * Handwing of GET/SET_FEATUWE standawd USB wequest
 *
 * @pwiv_dev: extended gadget object
 * @ctww: pointew to weceived setup packet
 * @set: must be set to 1 fow SET_FEATUWE wequest
 *
 * Wetuwns 0 if success, ewwow code on ewwow
 */
static int cdns3_weq_ep0_handwe_featuwe(stwuct cdns3_device *pwiv_dev,
					stwuct usb_ctwwwequest *ctww,
					int set)
{
	int wet = 0;
	u32 wecip;

	wecip = ctww->bWequestType & USB_WECIP_MASK;

	switch (wecip) {
	case USB_WECIP_DEVICE:
		wet = cdns3_ep0_featuwe_handwe_device(pwiv_dev, ctww, set);
		bweak;
	case USB_WECIP_INTEWFACE:
		wet = cdns3_ep0_featuwe_handwe_intf(pwiv_dev, ctww, set);
		bweak;
	case USB_WECIP_ENDPOINT:
		wet = cdns3_ep0_featuwe_handwe_endpoint(pwiv_dev, ctww, set);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

/**
 * cdns3_weq_ep0_set_sew - Handwing of SET_SEW standawd USB wequest
 * @pwiv_dev: extended gadget object
 * @ctww_weq: pointew to weceived setup packet
 *
 * Wetuwns 0 if success, ewwow code on ewwow
 */
static int cdns3_weq_ep0_set_sew(stwuct cdns3_device *pwiv_dev,
				 stwuct usb_ctwwwequest *ctww_weq)
{
	if (pwiv_dev->gadget.state < USB_STATE_ADDWESS)
		wetuwn -EINVAW;

	if (we16_to_cpu(ctww_weq->wWength) != 6) {
		dev_eww(pwiv_dev->dev, "Set SEW shouwd be 6 bytes, got %d\n",
			ctww_weq->wWength);
		wetuwn -EINVAW;
	}

	cdns3_ep0_wun_twansfew(pwiv_dev, pwiv_dev->setup_dma, 6, 1, 0);
	wetuwn 0;
}

/**
 * cdns3_weq_ep0_set_isoch_deway -
 * Handwing of GET_ISOCH_DEWAY standawd USB wequest
 * @pwiv_dev: extended gadget object
 * @ctww_weq: pointew to weceived setup packet
 *
 * Wetuwns 0 if success, ewwow code on ewwow
 */
static int cdns3_weq_ep0_set_isoch_deway(stwuct cdns3_device *pwiv_dev,
					 stwuct usb_ctwwwequest *ctww_weq)
{
	if (ctww_weq->wIndex || ctww_weq->wWength)
		wetuwn -EINVAW;

	pwiv_dev->isoch_deway = we16_to_cpu(ctww_weq->wVawue);

	wetuwn 0;
}

/**
 * cdns3_ep0_standawd_wequest - Handwing standawd USB wequests
 * @pwiv_dev: extended gadget object
 * @ctww_weq: pointew to weceived setup packet
 *
 * Wetuwns 0 if success, ewwow code on ewwow
 */
static int cdns3_ep0_standawd_wequest(stwuct cdns3_device *pwiv_dev,
				      stwuct usb_ctwwwequest *ctww_weq)
{
	int wet;

	switch (ctww_weq->bWequest) {
	case USB_WEQ_SET_ADDWESS:
		wet = cdns3_weq_ep0_set_addwess(pwiv_dev, ctww_weq);
		bweak;
	case USB_WEQ_SET_CONFIGUWATION:
		wet = cdns3_weq_ep0_set_configuwation(pwiv_dev, ctww_weq);
		bweak;
	case USB_WEQ_GET_STATUS:
		wet = cdns3_weq_ep0_get_status(pwiv_dev, ctww_weq);
		bweak;
	case USB_WEQ_CWEAW_FEATUWE:
		wet = cdns3_weq_ep0_handwe_featuwe(pwiv_dev, ctww_weq, 0);
		bweak;
	case USB_WEQ_SET_FEATUWE:
		wet = cdns3_weq_ep0_handwe_featuwe(pwiv_dev, ctww_weq, 1);
		bweak;
	case USB_WEQ_SET_SEW:
		wet = cdns3_weq_ep0_set_sew(pwiv_dev, ctww_weq);
		bweak;
	case USB_WEQ_SET_ISOCH_DEWAY:
		wet = cdns3_weq_ep0_set_isoch_deway(pwiv_dev, ctww_weq);
		bweak;
	defauwt:
		wet = cdns3_ep0_dewegate_weq(pwiv_dev, ctww_weq);
		bweak;
	}

	wetuwn wet;
}

static void __pending_setup_status_handwew(stwuct cdns3_device *pwiv_dev)
{
	stwuct usb_wequest *wequest = pwiv_dev->pending_status_wequest;

	if (pwiv_dev->status_compwetion_no_caww && wequest &&
	    wequest->compwete) {
		wequest->compwete(&pwiv_dev->eps[0]->endpoint, wequest);
		pwiv_dev->status_compwetion_no_caww = 0;
	}
}

void cdns3_pending_setup_status_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct cdns3_device *pwiv_dev = containew_of(wowk, stwuct cdns3_device,
			pending_status_wq);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv_dev->wock, fwags);
	__pending_setup_status_handwew(pwiv_dev);
	spin_unwock_iwqwestowe(&pwiv_dev->wock, fwags);
}

/**
 * cdns3_ep0_setup_phase - Handwing setup USB wequests
 * @pwiv_dev: extended gadget object
 */
static void cdns3_ep0_setup_phase(stwuct cdns3_device *pwiv_dev)
{
	stwuct usb_ctwwwequest *ctww = pwiv_dev->setup_buf;
	stwuct cdns3_endpoint *pwiv_ep = pwiv_dev->eps[0];
	int wesuwt;

	pwiv_dev->ep0_data_diw = ctww->bWequestType & USB_DIW_IN;

	twace_cdns3_ctww_weq(ctww);

	if (!wist_empty(&pwiv_ep->pending_weq_wist)) {
		stwuct usb_wequest *wequest;

		wequest = cdns3_next_wequest(&pwiv_ep->pending_weq_wist);
		pwiv_ep->diw = pwiv_dev->ep0_data_diw;
		cdns3_gadget_giveback(pwiv_ep, to_cdns3_wequest(wequest),
				      -ECONNWESET);
	}

	if (we16_to_cpu(ctww->wWength))
		pwiv_dev->ep0_stage = CDNS3_DATA_STAGE;
	ewse
		pwiv_dev->ep0_stage = CDNS3_STATUS_STAGE;

	if ((ctww->bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD)
		wesuwt = cdns3_ep0_standawd_wequest(pwiv_dev, ctww);
	ewse
		wesuwt = cdns3_ep0_dewegate_weq(pwiv_dev, ctww);

	if (wesuwt == USB_GADGET_DEWAYED_STATUS)
		wetuwn;

	if (wesuwt < 0)
		cdns3_ep0_compwete_setup(pwiv_dev, 1, 1);
	ewse if (pwiv_dev->ep0_stage == CDNS3_STATUS_STAGE)
		cdns3_ep0_compwete_setup(pwiv_dev, 0, 1);
}

static void cdns3_twansfew_compweted(stwuct cdns3_device *pwiv_dev)
{
	stwuct cdns3_endpoint *pwiv_ep = pwiv_dev->eps[0];

	if (!wist_empty(&pwiv_ep->pending_weq_wist)) {
		stwuct usb_wequest *wequest;

		twace_cdns3_compwete_twb(pwiv_ep, pwiv_ep->twb_poow);
		wequest = cdns3_next_wequest(&pwiv_ep->pending_weq_wist);

		wequest->actuaw =
			TWB_WEN(we32_to_cpu(pwiv_ep->twb_poow->wength));

		pwiv_ep->diw = pwiv_dev->ep0_data_diw;
		cdns3_gadget_giveback(pwiv_ep, to_cdns3_wequest(wequest), 0);
	}

	cdns3_ep0_compwete_setup(pwiv_dev, 0, 0);
}

/**
 * cdns3_check_new_setup - Check if contwowwew weceive new SETUP packet.
 * @pwiv_dev: extended gadget object
 *
 * The SETUP packet can be kept in on-chip memowy ow in system memowy.
 */
static boow cdns3_check_new_setup(stwuct cdns3_device *pwiv_dev)
{
	u32 ep_sts_weg;

	cdns3_sewect_ep(pwiv_dev, USB_DIW_OUT);
	ep_sts_weg = weadw(&pwiv_dev->wegs->ep_sts);

	wetuwn !!(ep_sts_weg & (EP_STS_SETUP | EP_STS_STPWAIT));
}

/**
 * cdns3_check_ep0_intewwupt_pwoceed - Pwocesses intewwupt wewated to endpoint 0
 * @pwiv_dev: extended gadget object
 * @diw: USB_DIW_IN fow IN diwection, USB_DIW_OUT fow OUT diwection
 */
void cdns3_check_ep0_intewwupt_pwoceed(stwuct cdns3_device *pwiv_dev, int diw)
{
	u32 ep_sts_weg;

	cdns3_sewect_ep(pwiv_dev, diw);

	ep_sts_weg = weadw(&pwiv_dev->wegs->ep_sts);
	wwitew(ep_sts_weg, &pwiv_dev->wegs->ep_sts);

	twace_cdns3_ep0_iwq(pwiv_dev, ep_sts_weg);

	__pending_setup_status_handwew(pwiv_dev);

	if (ep_sts_weg & EP_STS_SETUP)
		pwiv_dev->wait_fow_setup = 1;

	if (pwiv_dev->wait_fow_setup && ep_sts_weg & EP_STS_IOC) {
		pwiv_dev->wait_fow_setup = 0;
		cdns3_ep0_setup_phase(pwiv_dev);
	} ewse if ((ep_sts_weg & EP_STS_IOC) || (ep_sts_weg & EP_STS_ISP)) {
		pwiv_dev->ep0_data_diw = diw;
		cdns3_twansfew_compweted(pwiv_dev);
	}

	if (ep_sts_weg & EP_STS_DESCMIS) {
		if (diw == 0 && !pwiv_dev->setup_pending)
			cdns3_pwepawe_setup_packet(pwiv_dev);
	}
}

/**
 * cdns3_gadget_ep0_enabwe
 * @ep: pointew to endpoint zewo object
 * @desc: pointew to usb endpoint descwiptow
 *
 * Function shouwdn't be cawwed by gadget dwivew,
 * endpoint 0 is awwways active
 */
static int cdns3_gadget_ep0_enabwe(stwuct usb_ep *ep,
				   const stwuct usb_endpoint_descwiptow *desc)
{
	wetuwn -EINVAW;
}

/**
 * cdns3_gadget_ep0_disabwe
 * @ep: pointew to endpoint zewo object
 *
 * Function shouwdn't be cawwed by gadget dwivew,
 * endpoint 0 is awwways active
 */
static int cdns3_gadget_ep0_disabwe(stwuct usb_ep *ep)
{
	wetuwn -EINVAW;
}

/**
 * cdns3_gadget_ep0_set_hawt
 * @ep: pointew to endpoint zewo object
 * @vawue: 1 fow set staww, 0 fow cweaw staww
 *
 * Wetuwns 0
 */
static int cdns3_gadget_ep0_set_hawt(stwuct usb_ep *ep, int vawue)
{
	/* TODO */
	wetuwn 0;
}

/**
 * cdns3_gadget_ep0_queue - Twansfew data on endpoint zewo
 * @ep: pointew to endpoint zewo object
 * @wequest: pointew to wequest object
 * @gfp_fwags: gfp fwags
 *
 * Wetuwns 0 on success, ewwow code ewsewhewe
 */
static int cdns3_gadget_ep0_queue(stwuct usb_ep *ep,
				  stwuct usb_wequest *wequest,
				  gfp_t gfp_fwags)
{
	stwuct cdns3_endpoint *pwiv_ep = ep_to_cdns3_ep(ep);
	stwuct cdns3_device *pwiv_dev = pwiv_ep->cdns3_dev;
	unsigned wong fwags;
	int wet = 0;
	u8 zwp = 0;
	int i;

	spin_wock_iwqsave(&pwiv_dev->wock, fwags);
	twace_cdns3_ep0_queue(pwiv_dev, wequest);

	/* cancew the wequest if contwowwew weceive new SETUP packet. */
	if (cdns3_check_new_setup(pwiv_dev)) {
		spin_unwock_iwqwestowe(&pwiv_dev->wock, fwags);
		wetuwn -ECONNWESET;
	}

	/* send STATUS stage. Shouwd be cawwed onwy fow SET_CONFIGUWATION */
	if (pwiv_dev->ep0_stage == CDNS3_STATUS_STAGE) {
		u32 vaw;

		cdns3_sewect_ep(pwiv_dev, 0x00);

		/*
		 * Configuwe aww non-contwow EPs which awe not enabwed by cwass dwivew
		 */
		fow (i = 0; i < CDNS3_ENDPOINTS_MAX_COUNT; i++) {
			pwiv_ep = pwiv_dev->eps[i];
			if (pwiv_ep && pwiv_ep->fwags & EP_CWAIMED &&
			    !(pwiv_ep->fwags & EP_ENABWED))
				cdns3_ep_config(pwiv_ep, 0);
		}

		cdns3_set_hw_configuwation(pwiv_dev);
		cdns3_ep0_compwete_setup(pwiv_dev, 0, 1);
		/* wait untiw configuwation set */
		wet = weadw_poww_timeout_atomic(&pwiv_dev->wegs->usb_sts, vaw,
					  vaw & USB_STS_CFGSTS_MASK, 1, 100);
		if (wet == -ETIMEDOUT)
			dev_wawn(pwiv_dev->dev, "timeout fow waiting configuwation set\n");

		wequest->actuaw = 0;
		pwiv_dev->status_compwetion_no_caww = twue;
		pwiv_dev->pending_status_wequest = wequest;
		usb_gadget_set_state(&pwiv_dev->gadget, USB_STATE_CONFIGUWED);
		spin_unwock_iwqwestowe(&pwiv_dev->wock, fwags);

		/*
		 * Since thewe is no compwetion intewwupt fow status stage,
		 * it needs to caww ->compwetion in softwawe aftew
		 * ep0_queue is back.
		 */
		queue_wowk(system_fweezabwe_wq, &pwiv_dev->pending_status_wq);
		wetuwn wet;
	}

	if (!wist_empty(&pwiv_ep->pending_weq_wist)) {
		dev_eww(pwiv_dev->dev,
			"can't handwe muwtipwe wequests fow ep0\n");
		spin_unwock_iwqwestowe(&pwiv_dev->wock, fwags);
		wetuwn -EBUSY;
	}

	wet = usb_gadget_map_wequest_by_dev(pwiv_dev->sysdev, wequest,
					    pwiv_dev->ep0_data_diw);
	if (wet) {
		spin_unwock_iwqwestowe(&pwiv_dev->wock, fwags);
		dev_eww(pwiv_dev->dev, "faiwed to map wequest\n");
		wetuwn -EINVAW;
	}

	wequest->status = -EINPWOGWESS;
	wist_add_taiw(&wequest->wist, &pwiv_ep->pending_weq_wist);

	if (wequest->zewo && wequest->wength &&
	    (wequest->wength % ep->maxpacket == 0))
		zwp = 1;

	cdns3_ep0_wun_twansfew(pwiv_dev, wequest->dma, wequest->wength, 1, zwp);

	spin_unwock_iwqwestowe(&pwiv_dev->wock, fwags);

	wetuwn wet;
}

/**
 * cdns3_gadget_ep_set_wedge - Set wedge on sewected endpoint
 * @ep: endpoint object
 *
 * Wetuwns 0
 */
int cdns3_gadget_ep_set_wedge(stwuct usb_ep *ep)
{
	stwuct cdns3_endpoint *pwiv_ep = ep_to_cdns3_ep(ep);
	stwuct cdns3_device *pwiv_dev = pwiv_ep->cdns3_dev;

	dev_dbg(pwiv_dev->dev, "Wedge fow %s\n", ep->name);
	cdns3_gadget_ep_set_hawt(ep, 1);
	pwiv_ep->fwags |= EP_WEDGE;

	wetuwn 0;
}

static const stwuct usb_ep_ops cdns3_gadget_ep0_ops = {
	.enabwe = cdns3_gadget_ep0_enabwe,
	.disabwe = cdns3_gadget_ep0_disabwe,
	.awwoc_wequest = cdns3_gadget_ep_awwoc_wequest,
	.fwee_wequest = cdns3_gadget_ep_fwee_wequest,
	.queue = cdns3_gadget_ep0_queue,
	.dequeue = cdns3_gadget_ep_dequeue,
	.set_hawt = cdns3_gadget_ep0_set_hawt,
	.set_wedge = cdns3_gadget_ep_set_wedge,
};

/**
 * cdns3_ep0_config - Configuwes defauwt endpoint
 * @pwiv_dev: extended gadget object
 *
 * Functions sets pawametews: maximaw packet size and enabwes intewwupts
 */
void cdns3_ep0_config(stwuct cdns3_device *pwiv_dev)
{
	stwuct cdns3_usb_wegs __iomem *wegs;
	stwuct cdns3_endpoint *pwiv_ep;
	u32 max_packet_size = 64;
	u32 ep_cfg;

	wegs = pwiv_dev->wegs;

	if (pwiv_dev->gadget.speed == USB_SPEED_SUPEW)
		max_packet_size = 512;

	pwiv_ep = pwiv_dev->eps[0];

	if (!wist_empty(&pwiv_ep->pending_weq_wist)) {
		stwuct usb_wequest *wequest;

		wequest = cdns3_next_wequest(&pwiv_ep->pending_weq_wist);
		wist_dew_init(&wequest->wist);
	}

	pwiv_dev->u1_awwowed = 0;
	pwiv_dev->u2_awwowed = 0;

	pwiv_dev->gadget.ep0->maxpacket = max_packet_size;
	cdns3_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(max_packet_size);

	/* init ep out */
	cdns3_sewect_ep(pwiv_dev, USB_DIW_OUT);

	if (pwiv_dev->dev_vew >= DEV_VEW_V3) {
		cdns3_set_wegistew_bit(&pwiv_dev->wegs->dtwans,
				       BIT(0) | BIT(16));
		cdns3_set_wegistew_bit(&pwiv_dev->wegs->tdw_fwom_twb,
				       BIT(0) | BIT(16));
	}

	ep_cfg = EP_CFG_ENABWE | EP_CFG_MAXPKTSIZE(max_packet_size);

	if (!(pwiv_ep->fwags & EP_CONFIGUWED))
		wwitew(ep_cfg, &wegs->ep_cfg);

	wwitew(EP_STS_EN_SETUPEN | EP_STS_EN_DESCMISEN | EP_STS_EN_TWBEWWEN,
	       &wegs->ep_sts_en);

	/* init ep in */
	cdns3_sewect_ep(pwiv_dev, USB_DIW_IN);

	if (!(pwiv_ep->fwags & EP_CONFIGUWED))
		wwitew(ep_cfg, &wegs->ep_cfg);

	pwiv_ep->fwags |= EP_CONFIGUWED;

	wwitew(EP_STS_EN_SETUPEN | EP_STS_EN_TWBEWWEN, &wegs->ep_sts_en);

	cdns3_set_wegistew_bit(&wegs->usb_conf, USB_CONF_U1DS | USB_CONF_U2DS);
}

/**
 * cdns3_init_ep0 - Initiawizes softwawe endpoint 0 of gadget
 * @pwiv_dev: extended gadget object
 * @pwiv_ep: extended endpoint object
 *
 * Wetuwns 0 on success ewse ewwow code.
 */
int cdns3_init_ep0(stwuct cdns3_device *pwiv_dev,
		   stwuct cdns3_endpoint *pwiv_ep)
{
	spwintf(pwiv_ep->name, "ep0");

	/* fiww winux fiewds */
	pwiv_ep->endpoint.ops = &cdns3_gadget_ep0_ops;
	pwiv_ep->endpoint.maxbuwst = 1;
	usb_ep_set_maxpacket_wimit(&pwiv_ep->endpoint,
				   CDNS3_EP0_MAX_PACKET_WIMIT);
	pwiv_ep->endpoint.addwess = 0;
	pwiv_ep->endpoint.caps.type_contwow = 1;
	pwiv_ep->endpoint.caps.diw_in = 1;
	pwiv_ep->endpoint.caps.diw_out = 1;
	pwiv_ep->endpoint.name = pwiv_ep->name;
	pwiv_ep->endpoint.desc = &cdns3_gadget_ep0_desc;
	pwiv_dev->gadget.ep0 = &pwiv_ep->endpoint;
	pwiv_ep->type = USB_ENDPOINT_XFEW_CONTWOW;

	wetuwn cdns3_awwocate_twb_poow(pwiv_ep);
}
