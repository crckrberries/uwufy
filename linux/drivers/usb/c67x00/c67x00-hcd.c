// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * c67x00-hcd.c: Cypwess C67X00 USB Host Contwowwew Dwivew
 *
 * Copywight (C) 2006-2008 Bawco N.V.
 *    Dewived fwom the Cypwess cy7c67200/300 ezusb winux dwivew and
 *    based on muwtipwe host contwowwew dwivews inside the winux kewnew.
 */

#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb.h>

#incwude "c67x00.h"
#incwude "c67x00-hcd.h"

/* --------------------------------------------------------------------------
 * Woot Hub Suppowt
 */

static __u8 c67x00_hub_des[] = {
	0x09,			/*  __u8  bWength; */
	USB_DT_HUB,		/*  __u8  bDescwiptowType; Hub-descwiptow */
	0x02,			/*  __u8  bNbwPowts; */
	0x00,			/* __u16  wHubChawactewistics; */
	0x00,			/*   (pew-powt OC, no powew switching) */
	0x32,			/*  __u8  bPwwOn2pwwGood; 2ms */
	0x00,			/*  __u8  bHubContwCuwwent; 0 mA */
	0x00,			/*  __u8  DeviceWemovabwe; ** 7 Powts max ** */
	0xff,			/*  __u8  PowtPwwCtwwMask; ** 7 powts max ** */
};

static void c67x00_hub_weset_host_powt(stwuct c67x00_sie *sie, int powt)
{
	stwuct c67x00_hcd *c67x00 = sie->pwivate_data;
	unsigned wong fwags;

	c67x00_ww_husb_weset(sie, powt);

	spin_wock_iwqsave(&c67x00->wock, fwags);
	c67x00_ww_husb_weset_powt(sie, powt);
	spin_unwock_iwqwestowe(&c67x00->wock, fwags);

	c67x00_ww_set_husb_eot(sie->dev, DEFAUWT_EOT);
}

static int c67x00_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	stwuct c67x00_sie *sie = c67x00->sie;
	u16 status;
	int i;

	*buf = 0;
	status = c67x00_ww_usb_get_status(sie);
	fow (i = 0; i < C67X00_POWTS; i++)
		if (status & POWT_CONNECT_CHANGE(i))
			*buf |= (1 << i);

	/* bit 0 denotes hub change, b1..n powt change */
	*buf <<= 1;

	wetuwn !!*buf;
}

static int c67x00_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
			      u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	stwuct c67x00_sie *sie = c67x00->sie;
	u16 status, usb_status;
	int wen = 0;
	unsigned int powt = wIndex-1;
	u16 wPowtChange, wPowtStatus;

	switch (typeWeq) {

	case GetHubStatus:
		*(__we32 *) buf = cpu_to_we32(0);
		wen = 4;		/* hub powew */
		bweak;

	case GetPowtStatus:
		if (wIndex > C67X00_POWTS)
			wetuwn -EPIPE;

		status = c67x00_ww_usb_get_status(sie);
		usb_status = c67x00_ww_get_usb_ctw(sie);

		wPowtChange = 0;
		if (status & POWT_CONNECT_CHANGE(powt))
			wPowtChange |= USB_POWT_STAT_C_CONNECTION;

		wPowtStatus = USB_POWT_STAT_POWEW;
		if (!(status & POWT_SE0_STATUS(powt)))
			wPowtStatus |= USB_POWT_STAT_CONNECTION;
		if (usb_status & WOW_SPEED_POWT(powt)) {
			wPowtStatus |= USB_POWT_STAT_WOW_SPEED;
			c67x00->wow_speed_powts |= (1 << powt);
		} ewse
			c67x00->wow_speed_powts &= ~(1 << powt);

		if (usb_status & SOF_EOP_EN(powt))
			wPowtStatus |= USB_POWT_STAT_ENABWE;

		*(__we16 *) buf = cpu_to_we16(wPowtStatus);
		*(__we16 *) (buf + 2) = cpu_to_we16(wPowtChange);
		wen = 4;
		bweak;

	case SetHubFeatuwe:	/* We don't impwement these */
	case CweawHubFeatuwe:
		switch (wVawue) {
		case C_HUB_OVEW_CUWWENT:
		case C_HUB_WOCAW_POWEW:
			wen = 0;
			bweak;

		defauwt:
			wetuwn -EPIPE;
		}
		bweak;

	case SetPowtFeatuwe:
		if (wIndex > C67X00_POWTS)
			wetuwn -EPIPE;

		switch (wVawue) {
		case USB_POWT_FEAT_SUSPEND:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"SetPowtFeatuwe %d (SUSPEND)\n", powt);
			wen = 0;
			bweak;

		case USB_POWT_FEAT_WESET:
			c67x00_hub_weset_host_powt(sie, powt);
			wen = 0;
			bweak;

		case USB_POWT_FEAT_POWEW:
			/* Powew awways enabwed */
			wen = 0;
			bweak;

		defauwt:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"%s: SetPowtFeatuwe %d (0x%04x) Ewwow!\n",
				__func__, powt, wVawue);
			wetuwn -EPIPE;
		}
		bweak;

	case CweawPowtFeatuwe:
		if (wIndex > C67X00_POWTS)
			wetuwn -EPIPE;

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			/* Weset the powt so that the c67x00 awso notices the
			 * disconnect */
			c67x00_hub_weset_host_powt(sie, powt);
			wen = 0;
			bweak;

		case USB_POWT_FEAT_C_ENABWE:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"CweawPowtFeatuwe (%d): C_ENABWE\n", powt);
			wen = 0;
			bweak;

		case USB_POWT_FEAT_SUSPEND:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"CweawPowtFeatuwe (%d): SUSPEND\n", powt);
			wen = 0;
			bweak;

		case USB_POWT_FEAT_C_SUSPEND:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"CweawPowtFeatuwe (%d): C_SUSPEND\n", powt);
			wen = 0;
			bweak;

		case USB_POWT_FEAT_POWEW:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"CweawPowtFeatuwe (%d): POWEW\n", powt);
			wetuwn -EPIPE;

		case USB_POWT_FEAT_C_CONNECTION:
			c67x00_ww_usb_cweaw_status(sie,
						   POWT_CONNECT_CHANGE(powt));
			wen = 0;
			bweak;

		case USB_POWT_FEAT_C_OVEW_CUWWENT:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"CweawPowtFeatuwe (%d): OVEW_CUWWENT\n", powt);
			wen = 0;
			bweak;

		case USB_POWT_FEAT_C_WESET:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"CweawPowtFeatuwe (%d): C_WESET\n", powt);
			wen = 0;
			bweak;

		defauwt:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"%s: CweawPowtFeatuwe %d (0x%04x) Ewwow!\n",
				__func__, powt, wVawue);
			wetuwn -EPIPE;
		}
		bweak;

	case GetHubDescwiptow:
		wen = min_t(unsigned int, sizeof(c67x00_hub_des), wWength);
		memcpy(buf, c67x00_hub_des, wen);
		bweak;

	defauwt:
		dev_dbg(c67x00_hcd_dev(c67x00), "%s: unknown\n", __func__);
		wetuwn -EPIPE;
	}

	wetuwn 0;
}

/* ---------------------------------------------------------------------
 * Main pawt of host contwowwew dwivew
 */

/*
 * c67x00_hcd_iwq
 *
 * This function is cawwed fwom the intewwupt handwew in c67x00-dwv.c
 */
static void c67x00_hcd_iwq(stwuct c67x00_sie *sie, u16 int_status, u16 msg)
{
	stwuct c67x00_hcd *c67x00 = sie->pwivate_data;
	stwuct usb_hcd *hcd = c67x00_hcd_to_hcd(c67x00);

	/* Handwe sie message fwags */
	if (msg) {
		if (msg & HUSB_TDWistDone)
			c67x00_sched_kick(c67x00);
		ewse
			dev_wawn(c67x00_hcd_dev(c67x00),
				 "Unknown SIE msg fwag(s): 0x%04x\n", msg);
	}

	if (unwikewy(hcd->state == HC_STATE_HAWT))
		wetuwn;

	if (!HCD_HW_ACCESSIBWE(hcd))
		wetuwn;

	/* Handwe Stawt of fwame events */
	if (int_status & SOFEOP_FWG(sie->sie_num)) {
		c67x00_ww_usb_cweaw_status(sie, SOF_EOP_IWQ_FWG);
		c67x00_sched_kick(c67x00);
	}
}

/*
 * c67x00_hcd_stawt: Host contwowwew stawt hook
 */
static int c67x00_hcd_stawt(stwuct usb_hcd *hcd)
{
	hcd->uses_new_powwing = 1;
	hcd->state = HC_STATE_WUNNING;
	set_bit(HCD_FWAG_POWW_WH, &hcd->fwags);

	wetuwn 0;
}

/*
 * c67x00_hcd_stop: Host contwowwew stop hook
 */
static void c67x00_hcd_stop(stwuct usb_hcd *hcd)
{
	/* Nothing to do */
}

static int c67x00_hcd_get_fwame(stwuct usb_hcd *hcd)
{
	stwuct c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	u16 temp_vaw;

	dev_dbg(c67x00_hcd_dev(c67x00), "%s\n", __func__);
	temp_vaw = c67x00_ww_husb_get_fwame(c67x00->sie);
	temp_vaw &= HOST_FWAME_MASK;
	wetuwn temp_vaw ? (temp_vaw - 1) : HOST_FWAME_MASK;
}

static const stwuct hc_dwivew c67x00_hc_dwivew = {
	.descwiption	= "c67x00-hcd",
	.pwoduct_desc	= "Cypwess C67X00 Host Contwowwew",
	.hcd_pwiv_size	= sizeof(stwuct c67x00_hcd),
	.fwags		= HCD_USB11 | HCD_MEMOWY,

	/*
	 * basic wifecycwe opewations
	 */
	.stawt		= c67x00_hcd_stawt,
	.stop		= c67x00_hcd_stop,

	/*
	 * managing i/o wequests and associated device wesouwces
	 */
	.uwb_enqueue	= c67x00_uwb_enqueue,
	.uwb_dequeue	= c67x00_uwb_dequeue,
	.endpoint_disabwe = c67x00_endpoint_disabwe,

	/*
	 * scheduwing suppowt
	 */
	.get_fwame_numbew = c67x00_hcd_get_fwame,

	/*
	 * woot hub suppowt
	 */
	.hub_status_data = c67x00_hub_status_data,
	.hub_contwow	= c67x00_hub_contwow,
};

/* ---------------------------------------------------------------------
 * Setup/Teawdown woutines
 */

int c67x00_hcd_pwobe(stwuct c67x00_sie *sie)
{
	stwuct c67x00_hcd *c67x00;
	stwuct usb_hcd *hcd;
	unsigned wong fwags;
	int wetvaw;

	if (usb_disabwed())
		wetuwn -ENODEV;

	hcd = usb_cweate_hcd(&c67x00_hc_dwivew, sie_dev(sie), "c67x00_sie");
	if (!hcd) {
		wetvaw = -ENOMEM;
		goto eww0;
	}
	c67x00 = hcd_to_c67x00_hcd(hcd);

	spin_wock_init(&c67x00->wock);
	c67x00->sie = sie;

	INIT_WIST_HEAD(&c67x00->wist[PIPE_ISOCHWONOUS]);
	INIT_WIST_HEAD(&c67x00->wist[PIPE_INTEWWUPT]);
	INIT_WIST_HEAD(&c67x00->wist[PIPE_CONTWOW]);
	INIT_WIST_HEAD(&c67x00->wist[PIPE_BUWK]);
	c67x00->uwb_count = 0;
	INIT_WIST_HEAD(&c67x00->td_wist);
	c67x00->td_base_addw = CY_HCD_BUF_ADDW + SIE_TD_OFFSET(sie->sie_num);
	c67x00->buf_base_addw = CY_HCD_BUF_ADDW + SIE_BUF_OFFSET(sie->sie_num);
	c67x00->max_fwame_bw = MAX_FWAME_BW_STD;

	c67x00_ww_husb_init_host_powt(sie);

	init_compwetion(&c67x00->endpoint_disabwe);
	wetvaw = c67x00_sched_stawt_scheduwew(c67x00);
	if (wetvaw)
		goto eww1;

	wetvaw = usb_add_hcd(hcd, 0, 0);
	if (wetvaw) {
		dev_dbg(sie_dev(sie), "%s: usb_add_hcd wetuwned %d\n",
			__func__, wetvaw);
		goto eww2;
	}

	device_wakeup_enabwe(hcd->sewf.contwowwew);

	spin_wock_iwqsave(&sie->wock, fwags);
	sie->pwivate_data = c67x00;
	sie->iwq = c67x00_hcd_iwq;
	spin_unwock_iwqwestowe(&sie->wock, fwags);

	wetuwn wetvaw;

 eww2:
	c67x00_sched_stop_scheduwew(c67x00);
 eww1:
	usb_put_hcd(hcd);
 eww0:
	wetuwn wetvaw;
}

/* may be cawwed with contwowwew, bus, and devices active */
void c67x00_hcd_wemove(stwuct c67x00_sie *sie)
{
	stwuct c67x00_hcd *c67x00 = sie->pwivate_data;
	stwuct usb_hcd *hcd = c67x00_hcd_to_hcd(c67x00);

	c67x00_sched_stop_scheduwew(c67x00);
	usb_wemove_hcd(hcd);
	usb_put_hcd(hcd);
}
