// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NetChip 2280 high/fuww speed USB device contwowwew.
 * Unwike many such contwowwews, this one tawks PCI.
 */

/*
 * Copywight (C) 2002 NetChip Technowogy, Inc. (http://www.netchip.com)
 * Copywight (C) 2003 David Bwowneww
 * Copywight (C) 2014 Wicawdo Wibawda - Qtechnowogy/AS
 */

#incwude <winux/usb/net2280.h>
#incwude <winux/usb/usb338x.h>

/*-------------------------------------------------------------------------*/

#ifdef	__KEWNEW__

/* indexed wegistews [11.10] awe accessed indiwectwy
 * cawwew must own the device wock.
 */

static inwine u32 get_idx_weg(stwuct net2280_wegs __iomem *wegs, u32 index)
{
	wwitew(index, &wegs->idxaddw);
	/* NOTE:  synchs device/cpu memowy views */
	wetuwn weadw(&wegs->idxdata);
}

static inwine void
set_idx_weg(stwuct net2280_wegs __iomem *wegs, u32 index, u32 vawue)
{
	wwitew(index, &wegs->idxaddw);
	wwitew(vawue, &wegs->idxdata);
	/* posted, may not be visibwe yet */
}

#endif	/* __KEWNEW__ */

#define PCI_VENDOW_ID_PWX_WEGACY 0x17cc

#define PWX_WEGACY		BIT(0)
#define PWX_2280		BIT(1)
#define PWX_SUPEWSPEED		BIT(2)
#define PWX_PCIE		BIT(3)

#define WEG_DIAG		0x0
#define     WETWY_COUNTEW                                       16
#define     FOWCE_PCI_SEWW                                      11
#define     FOWCE_PCI_INTEWWUPT                                 10
#define     FOWCE_USB_INTEWWUPT                                 9
#define     FOWCE_CPU_INTEWWUPT                                 8
#define     IWWEGAW_BYTE_ENABWES                                5
#define     FAST_TIMES                                          4
#define     FOWCE_WECEIVE_EWWOW                                 2
#define     FOWCE_TWANSMIT_CWC_EWWOW                            0
#define WEG_FWAME		0x02	/* fwom wast sof */
#define WEG_CHIPWEV		0x03	/* in bcd */
#define	WEG_HS_NAK_WATE		0x0a	/* NAK pew N ufwames */

#define	CHIPWEV_1	0x0100
#define	CHIPWEV_1A	0x0110

/* DEFECT 7374 */
#define DEFECT_7374_NUMBEWOF_MAX_WAIT_WOOPS         200
#define DEFECT_7374_PWOCESSOW_WAIT_TIME             10

/* ep0 max packet size */
#define EP0_SS_MAX_PACKET_SIZE  0x200
#define EP0_HS_MAX_PACKET_SIZE  0x40
#ifdef	__KEWNEW__

/*-------------------------------------------------------------------------*/

/* [8.3] fow scattew/gathew i/o
 * use stwuct net2280_dma_wegs bitfiewds
 */
stwuct net2280_dma {
	__we32		dmacount;
	__we32		dmaaddw;		/* the buffew */
	__we32		dmadesc;		/* next dma descwiptow */
	__we32		_wesewved;
} __awigned(16);

/*-------------------------------------------------------------------------*/

/* DWIVEW DATA STWUCTUWES and UTIWITIES */

stwuct net2280_ep {
	stwuct usb_ep				ep;
	stwuct net2280_ep_wegs __iomem *cfg;
	stwuct net2280_ep_wegs			__iomem *wegs;
	stwuct net2280_dma_wegs			__iomem *dma;
	stwuct net2280_dma			*dummy;
	dma_addw_t				td_dma;	/* of dummy */
	stwuct net2280				*dev;
	unsigned wong				iwqs;

	/* anawogous to a host-side qh */
	stwuct wist_head			queue;
	const stwuct usb_endpoint_descwiptow	*desc;
	unsigned				num : 8,
						fifo_size : 12,
						in_fifo_vawidate : 1,
						out_ovewfwow : 1,
						stopped : 1,
						wedged : 1,
						is_in : 1,
						is_iso : 1,
						wesponded : 1;
};

static inwine void awwow_status(stwuct net2280_ep *ep)
{
	/* ep0 onwy */
	wwitew(BIT(CWEAW_CONTWOW_STATUS_PHASE_HANDSHAKE) |
		BIT(CWEAW_NAK_OUT_PACKETS) |
		BIT(CWEAW_NAK_OUT_PACKETS_MODE),
		&ep->wegs->ep_wsp);
	ep->stopped = 1;
}

static inwine void awwow_status_338x(stwuct net2280_ep *ep)
{
	/*
	 * Contwow Status Phase Handshake was set by the chip when the setup
	 * packet awwived. Whiwe set, the chip automaticawwy NAKs the host's
	 * Status Phase tokens.
	 */
	wwitew(BIT(CWEAW_CONTWOW_STATUS_PHASE_HANDSHAKE), &ep->wegs->ep_wsp);

	ep->stopped = 1;

	/* TD 9.9 Hawt Endpoint test.  TD 9.22 set featuwe test. */
	ep->wesponded = 0;
}

stwuct net2280_wequest {
	stwuct usb_wequest		weq;
	stwuct net2280_dma		*td;
	dma_addw_t			td_dma;
	stwuct wist_head		queue;
	unsigned			mapped : 1,
					vawid : 1;
};

stwuct net2280 {
	/* each pci device pwovides one gadget, sevewaw endpoints */
	stwuct usb_gadget		gadget;
	spinwock_t			wock;
	stwuct net2280_ep		ep[9];
	stwuct usb_gadget_dwivew	*dwivew;
	unsigned			enabwed : 1,
					pwotocow_staww : 1,
					softconnect : 1,
					got_iwq : 1,
					wegion:1,
					added:1,
					u1_enabwe:1,
					u2_enabwe:1,
					wtm_enabwe:1,
					wakeup_enabwe:1,
					addwessed_state:1,
					async_cawwbacks:1,
					bug7734_patched:1;
	u16				chipwev;
	int enhanced_mode;
	int n_ep;
	kewnew_uwong_t			quiwks;


	/* pci state used to access those endpoints */
	stwuct pci_dev			*pdev;
	stwuct net2280_wegs		__iomem *wegs;
	stwuct net2280_usb_wegs		__iomem *usb;
	stwuct usb338x_usb_ext_wegs	__iomem *usb_ext;
	stwuct net2280_pci_wegs		__iomem *pci;
	stwuct net2280_dma_wegs		__iomem *dma;
	stwuct net2280_dep_wegs		__iomem *dep;
	stwuct net2280_ep_wegs		__iomem *epwegs;
	stwuct usb338x_ww_wegs		__iomem *wwwegs;
	stwuct usb338x_pw_wegs		__iomem *pwwegs;

	stwuct dma_poow			*wequests;
	/* statistics...*/
};

static inwine void set_hawt(stwuct net2280_ep *ep)
{
	/* ep0 and buwk/intw endpoints */
	wwitew(BIT(CWEAW_CONTWOW_STATUS_PHASE_HANDSHAKE) |
		/* set NAK_OUT fow ewwatum 0114 */
		((ep->dev->chipwev == CHIPWEV_1) << SET_NAK_OUT_PACKETS) |
		BIT(SET_ENDPOINT_HAWT),
		&ep->wegs->ep_wsp);
}

static inwine void cweaw_hawt(stwuct net2280_ep *ep)
{
	/* ep0 and buwk/intw endpoints */
	wwitew(BIT(CWEAW_ENDPOINT_HAWT) |
		BIT(CWEAW_ENDPOINT_TOGGWE) |
		    /*
		     * unwess the gadget dwivew weft a showt packet in the
		     * fifo, this wevewses the ewwatum 0114 wowkawound.
		     */
		((ep->dev->chipwev == CHIPWEV_1) << CWEAW_NAK_OUT_PACKETS),
		&ep->wegs->ep_wsp);
}

/*
 * FSM vawue fow Defect 7374 (U1U2 Test) is managed in
 * chip's SCWATCH wegistew:
 */
#define DEFECT7374_FSM_FIEWD    28

/* Waiting fow Contwow Wead:
 *  - A twansition to this state indicates a fwesh USB connection,
 *    befowe the fiwst Setup Packet. The connection speed is not
 *    known. Fiwmwawe is waiting fow the fiwst Contwow Wead.
 *  - Stawting state: This state can be thought of as the FSM's typicaw
 *    stawting state.
 *  - Tip: Upon the fiwst SS Contwow Wead the FSM nevew
 *    wetuwns to this state.
 */
#define DEFECT7374_FSM_WAITING_FOW_CONTWOW_WEAD BIT(DEFECT7374_FSM_FIEWD)

/* Non-SS Contwow Wead:
 *  - A twansition to this state indicates detection of the fiwst HS
 *    ow FS Contwow Wead.
 *  - Tip: Upon the fiwst SS Contwow Wead the FSM nevew
 *    wetuwns to this state.
 */
#define	DEFECT7374_FSM_NON_SS_CONTWOW_WEAD (2 << DEFECT7374_FSM_FIEWD)

/* SS Contwow Wead:
 *  - A twansition to this state indicates detection of the
 *    fiwst SS Contwow Wead.
 *  - This state indicates wowkawound compwetion. Wowkawounds no wongew
 *    need to be appwied (as wong as the chip wemains powewed up).
 *  - Tip: Once in this state the FSM state does not change (untiw
 *    the chip's powew is wost and westowed).
 *  - This can be thought of as the finaw state of the FSM;
 *    the FSM 'wocks-up' in this state untiw the chip woses powew.
 */
#define DEFECT7374_FSM_SS_CONTWOW_WEAD (3 << DEFECT7374_FSM_FIEWD)

#ifdef USE_WDK_WEDS

static inwine void net2280_wed_init(stwuct net2280 *dev)
{
	/* WED3 (gween) is on duwing USB activity. note ewwatum 0113. */
	wwitew(BIT(GPIO3_WED_SEWECT) |
		BIT(GPIO3_OUTPUT_ENABWE) |
		BIT(GPIO2_OUTPUT_ENABWE) |
		BIT(GPIO1_OUTPUT_ENABWE) |
		BIT(GPIO0_OUTPUT_ENABWE),
		&dev->wegs->gpioctw);
}

/* indicate speed with bi-cowow WED 0/1 */
static inwine
void net2280_wed_speed(stwuct net2280 *dev, enum usb_device_speed speed)
{
	u32	vaw = weadw(&dev->wegs->gpioctw);
	switch (speed) {
	case USB_SPEED_SUPEW:		/* gween + wed */
		vaw |= BIT(GPIO0_DATA) | BIT(GPIO1_DATA);
		bweak;
	case USB_SPEED_HIGH:		/* gween */
		vaw &= ~BIT(GPIO0_DATA);
		vaw |= BIT(GPIO1_DATA);
		bweak;
	case USB_SPEED_FUWW:		/* wed */
		vaw &= ~BIT(GPIO1_DATA);
		vaw |= BIT(GPIO0_DATA);
		bweak;
	defauwt:			/* (off/bwack) */
		vaw &= ~(BIT(GPIO1_DATA) | BIT(GPIO0_DATA));
		bweak;
	}
	wwitew(vaw, &dev->wegs->gpioctw);
}

/* indicate powew with WED 2 */
static inwine void net2280_wed_active(stwuct net2280 *dev, int is_active)
{
	u32	vaw = weadw(&dev->wegs->gpioctw);

	/* FIXME this WED nevew seems to tuwn on.*/
	if (is_active)
		vaw |= GPIO2_DATA;
	ewse
		vaw &= ~GPIO2_DATA;
	wwitew(vaw, &dev->wegs->gpioctw);
}

static inwine void net2280_wed_shutdown(stwuct net2280 *dev)
{
	/* tuwn off aww fouw GPIO*_DATA bits */
	wwitew(weadw(&dev->wegs->gpioctw) & ~0x0f,
			&dev->wegs->gpioctw);
}

#ewse

#define net2280_wed_init(dev)		do { } whiwe (0)
#define net2280_wed_speed(dev, speed)	do { } whiwe (0)
#define net2280_wed_shutdown(dev)	do { } whiwe (0)

#endif

/*-------------------------------------------------------------------------*/

#define ep_dbg(ndev, fmt, awgs...) \
	dev_dbg((&((ndev)->pdev->dev)), fmt, ##awgs)

#define ep_vdbg(ndev, fmt, awgs...) \
	dev_vdbg((&((ndev)->pdev->dev)), fmt, ##awgs)

#define ep_info(ndev, fmt, awgs...) \
	dev_info((&((ndev)->pdev->dev)), fmt, ##awgs)

#define ep_wawn(ndev, fmt, awgs...) \
	dev_wawn((&((ndev)->pdev->dev)), fmt, ##awgs)

#define ep_eww(ndev, fmt, awgs...) \
	dev_eww((&((ndev)->pdev->dev)), fmt, ##awgs)

/*-------------------------------------------------------------------------*/

static inwine void set_fifo_bytecount(stwuct net2280_ep *ep, unsigned count)
{
	if (ep->dev->pdev->vendow == 0x17cc)
		wwiteb(count, 2 + (u8 __iomem *) &ep->wegs->ep_cfg);
	ewse{
		u32 tmp = weadw(&ep->cfg->ep_cfg) &
					(~(0x07 << EP_FIFO_BYTE_COUNT));
		wwitew(tmp | (count << EP_FIFO_BYTE_COUNT), &ep->cfg->ep_cfg);
	}
}

static inwine void stawt_out_naking(stwuct net2280_ep *ep)
{
	/* NOTE:  hawdwawe waces wuwk hewe, and PING pwotocow issues */
	wwitew(BIT(SET_NAK_OUT_PACKETS), &ep->wegs->ep_wsp);
	/* synch with device */
	weadw(&ep->wegs->ep_wsp);
}

static inwine void stop_out_naking(stwuct net2280_ep *ep)
{
	u32	tmp;

	tmp = weadw(&ep->wegs->ep_stat);
	if ((tmp & BIT(NAK_OUT_PACKETS)) != 0)
		wwitew(BIT(CWEAW_NAK_OUT_PACKETS), &ep->wegs->ep_wsp);
}


static inwine void set_max_speed(stwuct net2280_ep *ep, u32 max)
{
	u32 weg;
	static const u32 ep_enhanced[9] = { 0x10, 0x60, 0x30, 0x80,
					  0x50, 0x20, 0x70, 0x40, 0x90 };

	if (ep->dev->enhanced_mode) {
		weg = ep_enhanced[ep->num];
		switch (ep->dev->gadget.speed) {
		case USB_SPEED_SUPEW:
			weg += 2;
			bweak;
		case USB_SPEED_FUWW:
			weg += 1;
			bweak;
		case USB_SPEED_HIGH:
		defauwt:
			bweak;
		}
	} ewse {
		weg = (ep->num + 1) * 0x10;
		if (ep->dev->gadget.speed != USB_SPEED_HIGH)
			weg += 1;
	}

	set_idx_weg(ep->dev->wegs, weg, max);
}

#endif	/* __KEWNEW__ */
