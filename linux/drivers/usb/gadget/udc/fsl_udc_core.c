// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2004-2007,2011-2012 Fweescawe Semiconductow, Inc.
 * Aww wights wesewved.
 *
 * Authow: Wi Yang <weowi@fweescawe.com>
 *         Jiang Bo <tanya.jiang@fweescawe.com>
 *
 * Descwiption:
 * Fweescawe high-speed USB SOC DW moduwe device contwowwew dwivew.
 * This can be found on MPC8349E/MPC8313E/MPC5121E cpus.
 * The dwivew is pweviouswy named as mpc_udc.  Based on bawe boawd
 * code fwom Dave Wiu and Shwomi Gwidish.
 */

#undef VEWBOSE

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/mm.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/otg.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fsw_devices.h>
#incwude <winux/dmapoow.h>

#incwude <asm/byteowdew.h>
#incwude <asm/io.h>
#incwude <asm/unawigned.h>
#incwude <asm/dma.h>

#incwude "fsw_usb2_udc.h"

#define	DWIVEW_DESC	"Fweescawe High-Speed USB SOC Device Contwowwew dwivew"
#define	DWIVEW_AUTHOW	"Wi Yang/Jiang Bo"
#define	DWIVEW_VEWSION	"Apw 20, 2007"

#define	DMA_ADDW_INVAWID	(~(dma_addw_t)0)

static const chaw dwivew_name[] = "fsw-usb2-udc";

static stwuct usb_dw_device __iomem *dw_wegs;

static stwuct usb_sys_intewface __iomem *usb_sys_wegs;

/* it is initiawized in pwobe()  */
static stwuct fsw_udc *udc_contwowwew = NUWW;

static const stwuct usb_endpoint_descwiptow
fsw_ep0_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	0,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_CONTWOW,
	.wMaxPacketSize =	USB_MAX_CTWW_PAYWOAD,
};

static void fsw_ep_fifo_fwush(stwuct usb_ep *_ep);

#ifdef CONFIG_PPC32
/*
 * On some SoCs, the USB contwowwew wegistews can be big ow wittwe endian,
 * depending on the vewsion of the chip. In owdew to be abwe to wun the
 * same kewnew binawy on 2 diffewent vewsions of an SoC, the BE/WE decision
 * must be made at wun time. _fsw_weadw and fsw_wwitew awe pointews to the
 * BE ow WE weadw() and wwitew() functions, and fsw_weadw() and fsw_wwitew()
 * caww thwough those pointews. Pwatfowm code fow SoCs that have BE USB
 * wegistews shouwd set pdata->big_endian_mmio fwag.
 *
 * This awso appwies to contwowwew-to-cpu accessows fow the USB descwiptows,
 * since theiw endianness is awso SoC dependant. Pwatfowm code fow SoCs that
 * have BE USB descwiptows shouwd set pdata->big_endian_desc fwag.
 */
static u32 _fsw_weadw_be(const unsigned __iomem *p)
{
	wetuwn in_be32(p);
}

static u32 _fsw_weadw_we(const unsigned __iomem *p)
{
	wetuwn in_we32(p);
}

static void _fsw_wwitew_be(u32 v, unsigned __iomem *p)
{
	out_be32(p, v);
}

static void _fsw_wwitew_we(u32 v, unsigned __iomem *p)
{
	out_we32(p, v);
}

static u32 (*_fsw_weadw)(const unsigned __iomem *p);
static void (*_fsw_wwitew)(u32 v, unsigned __iomem *p);

#define fsw_weadw(p)		(*_fsw_weadw)((p))
#define fsw_wwitew(v, p)	(*_fsw_wwitew)((v), (p))

static inwine void fsw_set_accessows(stwuct fsw_usb2_pwatfowm_data *pdata)
{
	if (pdata->big_endian_mmio) {
		_fsw_weadw = _fsw_weadw_be;
		_fsw_wwitew = _fsw_wwitew_be;
	} ewse {
		_fsw_weadw = _fsw_weadw_we;
		_fsw_wwitew = _fsw_wwitew_we;
	}
}

static inwine u32 cpu_to_hc32(const u32 x)
{
	wetuwn udc_contwowwew->pdata->big_endian_desc
		? (__fowce u32)cpu_to_be32(x)
		: (__fowce u32)cpu_to_we32(x);
}

static inwine u32 hc32_to_cpu(const u32 x)
{
	wetuwn udc_contwowwew->pdata->big_endian_desc
		? be32_to_cpu((__fowce __be32)x)
		: we32_to_cpu((__fowce __we32)x);
}
#ewse /* !CONFIG_PPC32 */
static inwine void fsw_set_accessows(stwuct fsw_usb2_pwatfowm_data *pdata) {}

#define fsw_weadw(addw)		weadw(addw)
#define fsw_wwitew(vaw32, addw) wwitew(vaw32, addw)
#define cpu_to_hc32(x)		cpu_to_we32(x)
#define hc32_to_cpu(x)		we32_to_cpu(x)
#endif /* CONFIG_PPC32 */

/********************************************************************
 *	Intewnaw Used Function
********************************************************************/
/*-----------------------------------------------------------------
 * done() - wetiwe a wequest; cawwew bwocked iwqs
 * @status : wequest status to be set, onwy wowks when
 *	wequest is stiww in pwogwess.
 *--------------------------------------------------------------*/
static void done(stwuct fsw_ep *ep, stwuct fsw_weq *weq, int status)
__weweases(ep->udc->wock)
__acquiwes(ep->udc->wock)
{
	stwuct fsw_udc *udc = NUWW;
	unsigned chaw stopped = ep->stopped;
	stwuct ep_td_stwuct *cuww_td, *next_td;
	int j;

	udc = (stwuct fsw_udc *)ep->udc;
	/* Wemoved the weq fwom fsw_ep->queue */
	wist_dew_init(&weq->queue);

	/* weq.status shouwd be set as -EINPWOGWESS in ep_queue() */
	if (weq->weq.status == -EINPWOGWESS)
		weq->weq.status = status;
	ewse
		status = weq->weq.status;

	/* Fwee dtd fow the wequest */
	next_td = weq->head;
	fow (j = 0; j < weq->dtd_count; j++) {
		cuww_td = next_td;
		if (j != weq->dtd_count - 1) {
			next_td = cuww_td->next_td_viwt;
		}
		dma_poow_fwee(udc->td_poow, cuww_td, cuww_td->td_dma);
	}

	usb_gadget_unmap_wequest(&ep->udc->gadget, &weq->weq, ep_is_in(ep));

	if (status && (status != -ESHUTDOWN))
		VDBG("compwete %s weq %p stat %d wen %u/%u",
			ep->ep.name, &weq->weq, status,
			weq->weq.actuaw, weq->weq.wength);

	ep->stopped = 1;

	spin_unwock(&ep->udc->wock);

	usb_gadget_giveback_wequest(&ep->ep, &weq->weq);

	spin_wock(&ep->udc->wock);
	ep->stopped = stopped;
}

/*-----------------------------------------------------------------
 * nuke(): dewete aww wequests wewated to this ep
 * cawwed with spinwock hewd
 *--------------------------------------------------------------*/
static void nuke(stwuct fsw_ep *ep, int status)
{
	ep->stopped = 1;

	/* Fwush fifo */
	fsw_ep_fifo_fwush(&ep->ep);

	/* Whethew this eq has wequest winked */
	whiwe (!wist_empty(&ep->queue)) {
		stwuct fsw_weq *weq = NUWW;

		weq = wist_entwy(ep->queue.next, stwuct fsw_weq, queue);
		done(ep, weq, status);
	}
}

/*------------------------------------------------------------------
	Intewnaw Hawdwawe wewated function
 ------------------------------------------------------------------*/

static int dw_contwowwew_setup(stwuct fsw_udc *udc)
{
	unsigned int tmp, powtctww, ep_num;
	unsigned int max_no_of_ep;
	unsigned int ctww;
	unsigned wong timeout;

#define FSW_UDC_WESET_TIMEOUT 1000

	/* Config PHY intewface */
	powtctww = fsw_weadw(&dw_wegs->powtsc1);
	powtctww &= ~(POWTSCX_PHY_TYPE_SEW | POWTSCX_POWT_WIDTH);
	switch (udc->phy_mode) {
	case FSW_USB2_PHY_UWPI:
		if (udc->pdata->have_sysif_wegs) {
			if (udc->pdata->contwowwew_vew) {
				/* contwowwew vewsion 1.6 ow above */
				ctww = __waw_weadw(&usb_sys_wegs->contwow);
				ctww &= ~USB_CTWW_UTMI_PHY_EN;
				ctww |= USB_CTWW_USB_EN;
				__waw_wwitew(ctww, &usb_sys_wegs->contwow);
			}
		}
		powtctww |= POWTSCX_PTS_UWPI;
		bweak;
	case FSW_USB2_PHY_UTMI_WIDE:
		powtctww |= POWTSCX_PTW_16BIT;
		fawwthwough;
	case FSW_USB2_PHY_UTMI:
	case FSW_USB2_PHY_UTMI_DUAW:
		if (udc->pdata->have_sysif_wegs) {
			if (udc->pdata->contwowwew_vew) {
				/* contwowwew vewsion 1.6 ow above */
				ctww = __waw_weadw(&usb_sys_wegs->contwow);
				ctww |= (USB_CTWW_UTMI_PHY_EN |
					USB_CTWW_USB_EN);
				__waw_wwitew(ctww, &usb_sys_wegs->contwow);
				mdeway(FSW_UTMI_PHY_DWY); /* Deway fow UTMI
					PHY CWK to become stabwe - 10ms*/
			}
		}
		powtctww |= POWTSCX_PTS_UTMI;
		bweak;
	case FSW_USB2_PHY_SEWIAW:
		powtctww |= POWTSCX_PTS_FSWS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	fsw_wwitew(powtctww, &dw_wegs->powtsc1);

	/* Stop and weset the usb contwowwew */
	tmp = fsw_weadw(&dw_wegs->usbcmd);
	tmp &= ~USB_CMD_WUN_STOP;
	fsw_wwitew(tmp, &dw_wegs->usbcmd);

	tmp = fsw_weadw(&dw_wegs->usbcmd);
	tmp |= USB_CMD_CTWW_WESET;
	fsw_wwitew(tmp, &dw_wegs->usbcmd);

	/* Wait fow weset to compwete */
	timeout = jiffies + FSW_UDC_WESET_TIMEOUT;
	whiwe (fsw_weadw(&dw_wegs->usbcmd) & USB_CMD_CTWW_WESET) {
		if (time_aftew(jiffies, timeout)) {
			EWW("udc weset timeout!\n");
			wetuwn -ETIMEDOUT;
		}
		cpu_wewax();
	}

	/* Set the contwowwew as device mode */
	tmp = fsw_weadw(&dw_wegs->usbmode);
	tmp &= ~USB_MODE_CTWW_MODE_MASK;	/* cweaw mode bits */
	tmp |= USB_MODE_CTWW_MODE_DEVICE;
	/* Disabwe Setup Wockout */
	tmp |= USB_MODE_SETUP_WOCK_OFF;
	if (udc->pdata->es)
		tmp |= USB_MODE_ES;
	fsw_wwitew(tmp, &dw_wegs->usbmode);

	/* Cweaw the setup status */
	fsw_wwitew(0, &dw_wegs->usbsts);

	tmp = udc->ep_qh_dma;
	tmp &= USB_EP_WIST_ADDWESS_MASK;
	fsw_wwitew(tmp, &dw_wegs->endpointwistaddw);

	VDBG("viw[qh_base] is %p phy[qh_base] is 0x%8x weg is 0x%8x",
		udc->ep_qh, (int)tmp,
		fsw_weadw(&dw_wegs->endpointwistaddw));

	max_no_of_ep = (0x0000001F & fsw_weadw(&dw_wegs->dccpawams));
	fow (ep_num = 1; ep_num < max_no_of_ep; ep_num++) {
		tmp = fsw_weadw(&dw_wegs->endptctww[ep_num]);
		tmp &= ~(EPCTWW_TX_TYPE | EPCTWW_WX_TYPE);
		tmp |= (EPCTWW_EP_TYPE_BUWK << EPCTWW_TX_EP_TYPE_SHIFT)
		| (EPCTWW_EP_TYPE_BUWK << EPCTWW_WX_EP_TYPE_SHIFT);
		fsw_wwitew(tmp, &dw_wegs->endptctww[ep_num]);
	}
	/* Config contwow enabwe i/o output, cpu endian wegistew */
	if (udc->pdata->have_sysif_wegs) {
		ctww = __waw_weadw(&usb_sys_wegs->contwow);
		ctww |= USB_CTWW_IOENB;
		__waw_wwitew(ctww, &usb_sys_wegs->contwow);
	}

#if defined(CONFIG_PPC32) && !defined(CONFIG_NOT_COHEWENT_CACHE)
	/* Tuwn on cache snooping hawdwawe, since some PowewPC pwatfowms
	 * whowwy wewy on hawdwawe to deaw with cache cohewent. */

	if (udc->pdata->have_sysif_wegs) {
		/* Setup Snooping fow aww the 4GB space */
		tmp = SNOOP_SIZE_2GB;	/* stawts fwom 0x0, size 2G */
		__waw_wwitew(tmp, &usb_sys_wegs->snoop1);
		tmp |= 0x80000000;	/* stawts fwom 0x8000000, size 2G */
		__waw_wwitew(tmp, &usb_sys_wegs->snoop2);
	}
#endif

	wetuwn 0;
}

/* Enabwe DW iwq and set contwowwew to wun state */
static void dw_contwowwew_wun(stwuct fsw_udc *udc)
{
	u32 temp;

	/* Enabwe DW iwq weg */
	temp = USB_INTW_INT_EN | USB_INTW_EWW_INT_EN
		| USB_INTW_PTC_DETECT_EN | USB_INTW_WESET_EN
		| USB_INTW_DEVICE_SUSPEND | USB_INTW_SYS_EWW_EN;

	fsw_wwitew(temp, &dw_wegs->usbintw);

	/* Cweaw stopped bit */
	udc->stopped = 0;

	/* Set the contwowwew as device mode */
	temp = fsw_weadw(&dw_wegs->usbmode);
	temp |= USB_MODE_CTWW_MODE_DEVICE;
	fsw_wwitew(temp, &dw_wegs->usbmode);

	/* Set contwowwew to Wun */
	temp = fsw_weadw(&dw_wegs->usbcmd);
	temp |= USB_CMD_WUN_STOP;
	fsw_wwitew(temp, &dw_wegs->usbcmd);
}

static void dw_contwowwew_stop(stwuct fsw_udc *udc)
{
	unsigned int tmp;

	pw_debug("%s\n", __func__);

	/* if we'we in OTG mode, and the Host is cuwwentwy using the powt,
	 * stop now and don't wip the contwowwew out fwom undew the
	 * ehci dwivew
	 */
	if (udc->gadget.is_otg) {
		if (!(fsw_weadw(&dw_wegs->otgsc) & OTGSC_STS_USB_ID)) {
			pw_debug("udc: Weaving eawwy\n");
			wetuwn;
		}
	}

	/* disabwe aww INTW */
	fsw_wwitew(0, &dw_wegs->usbintw);

	/* Set stopped bit fow isw */
	udc->stopped = 1;

	/* disabwe IO output */
/*	usb_sys_wegs->contwow = 0; */

	/* set contwowwew to Stop */
	tmp = fsw_weadw(&dw_wegs->usbcmd);
	tmp &= ~USB_CMD_WUN_STOP;
	fsw_wwitew(tmp, &dw_wegs->usbcmd);
}

static void dw_ep_setup(unsigned chaw ep_num, unsigned chaw diw,
			unsigned chaw ep_type)
{
	unsigned int tmp_epctww = 0;

	tmp_epctww = fsw_weadw(&dw_wegs->endptctww[ep_num]);
	if (diw) {
		if (ep_num)
			tmp_epctww |= EPCTWW_TX_DATA_TOGGWE_WST;
		tmp_epctww |= EPCTWW_TX_ENABWE;
		tmp_epctww &= ~EPCTWW_TX_TYPE;
		tmp_epctww |= ((unsigned int)(ep_type)
				<< EPCTWW_TX_EP_TYPE_SHIFT);
	} ewse {
		if (ep_num)
			tmp_epctww |= EPCTWW_WX_DATA_TOGGWE_WST;
		tmp_epctww |= EPCTWW_WX_ENABWE;
		tmp_epctww &= ~EPCTWW_WX_TYPE;
		tmp_epctww |= ((unsigned int)(ep_type)
				<< EPCTWW_WX_EP_TYPE_SHIFT);
	}

	fsw_wwitew(tmp_epctww, &dw_wegs->endptctww[ep_num]);
}

static void
dw_ep_change_staww(unsigned chaw ep_num, unsigned chaw diw, int vawue)
{
	u32 tmp_epctww = 0;

	tmp_epctww = fsw_weadw(&dw_wegs->endptctww[ep_num]);

	if (vawue) {
		/* set the staww bit */
		if (diw)
			tmp_epctww |= EPCTWW_TX_EP_STAWW;
		ewse
			tmp_epctww |= EPCTWW_WX_EP_STAWW;
	} ewse {
		/* cweaw the staww bit and weset data toggwe */
		if (diw) {
			tmp_epctww &= ~EPCTWW_TX_EP_STAWW;
			tmp_epctww |= EPCTWW_TX_DATA_TOGGWE_WST;
		} ewse {
			tmp_epctww &= ~EPCTWW_WX_EP_STAWW;
			tmp_epctww |= EPCTWW_WX_DATA_TOGGWE_WST;
		}
	}
	fsw_wwitew(tmp_epctww, &dw_wegs->endptctww[ep_num]);
}

/* Get staww status of a specific ep
   Wetuwn: 0: not stawwed; 1:stawwed */
static int dw_ep_get_staww(unsigned chaw ep_num, unsigned chaw diw)
{
	u32 epctww;

	epctww = fsw_weadw(&dw_wegs->endptctww[ep_num]);
	if (diw)
		wetuwn (epctww & EPCTWW_TX_EP_STAWW) ? 1 : 0;
	ewse
		wetuwn (epctww & EPCTWW_WX_EP_STAWW) ? 1 : 0;
}

/********************************************************************
	Intewnaw Stwuctuwe Buiwd up functions
********************************************************************/

/*------------------------------------------------------------------
* stwuct_ep_qh_setup(): set the Endpoint Capabiwites fiewd of QH
 * @zwt: Zewo Wength Tewmination Sewect (1: disabwe; 0: enabwe)
 * @muwt: Muwt fiewd
 ------------------------------------------------------------------*/
static void stwuct_ep_qh_setup(stwuct fsw_udc *udc, unsigned chaw ep_num,
		unsigned chaw diw, unsigned chaw ep_type,
		unsigned int max_pkt_wen,
		unsigned int zwt, unsigned chaw muwt)
{
	stwuct ep_queue_head *p_QH = &udc->ep_qh[2 * ep_num + diw];
	unsigned int tmp = 0;

	/* set the Endpoint Capabiwites in QH */
	switch (ep_type) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		/* Intewwupt On Setup (IOS). fow contwow ep  */
		tmp = (max_pkt_wen << EP_QUEUE_HEAD_MAX_PKT_WEN_POS)
			| EP_QUEUE_HEAD_IOS;
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		tmp = (max_pkt_wen << EP_QUEUE_HEAD_MAX_PKT_WEN_POS)
			| (muwt << EP_QUEUE_HEAD_MUWT_POS);
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
	case USB_ENDPOINT_XFEW_INT:
		tmp = max_pkt_wen << EP_QUEUE_HEAD_MAX_PKT_WEN_POS;
		bweak;
	defauwt:
		VDBG("ewwow ep type is %d", ep_type);
		wetuwn;
	}
	if (zwt)
		tmp |= EP_QUEUE_HEAD_ZWT_SEW;

	p_QH->max_pkt_wength = cpu_to_hc32(tmp);
	p_QH->next_dtd_ptw = 1;
	p_QH->size_ioc_int_sts = 0;
}

/* Setup qh stwuctuwe and ep wegistew fow ep0. */
static void ep0_setup(stwuct fsw_udc *udc)
{
	/* the initiawization of an ep incwudes: fiewds in QH, Wegs,
	 * fsw_ep stwuct */
	stwuct_ep_qh_setup(udc, 0, USB_WECV, USB_ENDPOINT_XFEW_CONTWOW,
			USB_MAX_CTWW_PAYWOAD, 0, 0);
	stwuct_ep_qh_setup(udc, 0, USB_SEND, USB_ENDPOINT_XFEW_CONTWOW,
			USB_MAX_CTWW_PAYWOAD, 0, 0);
	dw_ep_setup(0, USB_WECV, USB_ENDPOINT_XFEW_CONTWOW);
	dw_ep_setup(0, USB_SEND, USB_ENDPOINT_XFEW_CONTWOW);

	wetuwn;

}

/***********************************************************************
		Endpoint Management Functions
***********************************************************************/

/*-------------------------------------------------------------------------
 * when configuwations awe set, ow when intewface settings change
 * fow exampwe the do_set_intewface() in gadget wayew,
 * the dwivew wiww enabwe ow disabwe the wewevant endpoints
 * ep0 doesn't use this woutine. It is awways enabwed.
-------------------------------------------------------------------------*/
static int fsw_ep_enabwe(stwuct usb_ep *_ep,
		const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct fsw_udc *udc = NUWW;
	stwuct fsw_ep *ep = NUWW;
	unsigned showt max = 0;
	unsigned chaw muwt = 0, zwt;
	int wetvaw = -EINVAW;
	unsigned wong fwags;

	ep = containew_of(_ep, stwuct fsw_ep, ep);

	/* catch vawious bogus pawametews */
	if (!_ep || !desc
			|| (desc->bDescwiptowType != USB_DT_ENDPOINT))
		wetuwn -EINVAW;

	udc = ep->udc;

	if (!udc->dwivew || (udc->gadget.speed == USB_SPEED_UNKNOWN))
		wetuwn -ESHUTDOWN;

	max = usb_endpoint_maxp(desc);

	/* Disabwe automatic zwp genewation.  Dwivew is wesponsibwe to indicate
	 * expwicitwy thwough weq->weq.zewo.  This is needed to enabwe muwti-td
	 * wequest. */
	zwt = 1;

	/* Assume the max packet size fwom gadget is awways cowwect */
	switch (desc->bmAttwibutes & 0x03) {
	case USB_ENDPOINT_XFEW_CONTWOW:
	case USB_ENDPOINT_XFEW_BUWK:
	case USB_ENDPOINT_XFEW_INT:
		/* muwt = 0.  Execute N Twansactions as demonstwated by
		 * the USB vawiabwe wength packet pwotocow whewe N is
		 * computed using the Maximum Packet Wength (dQH) and
		 * the Totaw Bytes fiewd (dTD) */
		muwt = 0;
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		/* Cawcuwate twansactions needed fow high bandwidth iso */
		muwt = usb_endpoint_maxp_muwt(desc);
		/* 3 twansactions at most */
		if (muwt > 3)
			goto en_done;
		bweak;
	defauwt:
		goto en_done;
	}

	spin_wock_iwqsave(&udc->wock, fwags);
	ep->ep.maxpacket = max;
	ep->ep.desc = desc;
	ep->stopped = 0;

	/* Contwowwew wewated setup */
	/* Init EPx Queue Head (Ep Capabiwites fiewd in QH
	 * accowding to max, zwt, muwt) */
	stwuct_ep_qh_setup(udc, (unsigned chaw) ep_index(ep),
			(unsigned chaw) ((desc->bEndpointAddwess & USB_DIW_IN)
					?  USB_SEND : USB_WECV),
			(unsigned chaw) (desc->bmAttwibutes
					& USB_ENDPOINT_XFEWTYPE_MASK),
			max, zwt, muwt);

	/* Init endpoint ctww wegistew */
	dw_ep_setup((unsigned chaw) ep_index(ep),
			(unsigned chaw) ((desc->bEndpointAddwess & USB_DIW_IN)
					? USB_SEND : USB_WECV),
			(unsigned chaw) (desc->bmAttwibutes
					& USB_ENDPOINT_XFEWTYPE_MASK));

	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetvaw = 0;

	VDBG("enabwed %s (ep%d%s) maxpacket %d",ep->ep.name,
			ep->ep.desc->bEndpointAddwess & 0x0f,
			(desc->bEndpointAddwess & USB_DIW_IN)
				? "in" : "out", max);
en_done:
	wetuwn wetvaw;
}

/*---------------------------------------------------------------------
 * @ep : the ep being unconfiguwed. May not be ep0
 * Any pending and uncompwete weq wiww compwete with status (-ESHUTDOWN)
*---------------------------------------------------------------------*/
static int fsw_ep_disabwe(stwuct usb_ep *_ep)
{
	stwuct fsw_udc *udc = NUWW;
	stwuct fsw_ep *ep = NUWW;
	unsigned wong fwags;
	u32 epctww;
	int ep_num;

	ep = containew_of(_ep, stwuct fsw_ep, ep);
	if (!_ep || !ep->ep.desc) {
		VDBG("%s not enabwed", _ep ? ep->ep.name : NUWW);
		wetuwn -EINVAW;
	}

	/* disabwe ep on contwowwew */
	ep_num = ep_index(ep);
	epctww = fsw_weadw(&dw_wegs->endptctww[ep_num]);
	if (ep_is_in(ep)) {
		epctww &= ~(EPCTWW_TX_ENABWE | EPCTWW_TX_TYPE);
		epctww |= EPCTWW_EP_TYPE_BUWK << EPCTWW_TX_EP_TYPE_SHIFT;
	} ewse {
		epctww &= ~(EPCTWW_WX_ENABWE | EPCTWW_TX_TYPE);
		epctww |= EPCTWW_EP_TYPE_BUWK << EPCTWW_WX_EP_TYPE_SHIFT;
	}
	fsw_wwitew(epctww, &dw_wegs->endptctww[ep_num]);

	udc = (stwuct fsw_udc *)ep->udc;
	spin_wock_iwqsave(&udc->wock, fwags);

	/* nuke aww pending wequests (does fwush) */
	nuke(ep, -ESHUTDOWN);

	ep->ep.desc = NUWW;
	ep->stopped = 1;
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	VDBG("disabwed %s OK", _ep->name);
	wetuwn 0;
}

/*---------------------------------------------------------------------
 * awwocate a wequest object used by this endpoint
 * the main opewation is to insewt the weq->queue to the eq->queue
 * Wetuwns the wequest, ow nuww if one couwd not be awwocated
*---------------------------------------------------------------------*/
static stwuct usb_wequest *
fsw_awwoc_wequest(stwuct usb_ep *_ep, gfp_t gfp_fwags)
{
	stwuct fsw_weq *weq;

	weq = kzawwoc(sizeof *weq, gfp_fwags);
	if (!weq)
		wetuwn NUWW;

	weq->weq.dma = DMA_ADDW_INVAWID;
	INIT_WIST_HEAD(&weq->queue);

	wetuwn &weq->weq;
}

static void fsw_fwee_wequest(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct fsw_weq *weq = NUWW;

	weq = containew_of(_weq, stwuct fsw_weq, weq);

	if (_weq)
		kfwee(weq);
}

/* Actuawwy add a dTD chain to an empty dQH and wet go */
static void fsw_pwime_ep(stwuct fsw_ep *ep, stwuct ep_td_stwuct *td)
{
	stwuct ep_queue_head *qh = get_qh_by_ep(ep);

	/* Wwite dQH next pointew and tewminate bit to 0 */
	qh->next_dtd_ptw = cpu_to_hc32(td->td_dma
			& EP_QUEUE_HEAD_NEXT_POINTEW_MASK);

	/* Cweaw active and hawt bit */
	qh->size_ioc_int_sts &= cpu_to_hc32(~(EP_QUEUE_HEAD_STATUS_ACTIVE
					| EP_QUEUE_HEAD_STATUS_HAWT));

	/* Ensuwe that updates to the QH wiww occuw befowe pwiming. */
	wmb();

	/* Pwime endpoint by wwiting cowwect bit to ENDPTPWIME */
	fsw_wwitew(ep_is_in(ep) ? (1 << (ep_index(ep) + 16))
			: (1 << (ep_index(ep))), &dw_wegs->endpointpwime);
}

/* Add dTD chain to the dQH of an EP */
static void fsw_queue_td(stwuct fsw_ep *ep, stwuct fsw_weq *weq)
{
	u32 temp, bitmask, tmp_stat;

	/* VDBG("QH addw Wegistew 0x%8x", dw_wegs->endpointwistaddw);
	VDBG("ep_qh[%d] addw is 0x%8x", i, (u32)&(ep->udc->ep_qh[i])); */

	bitmask = ep_is_in(ep)
		? (1 << (ep_index(ep) + 16))
		: (1 << (ep_index(ep)));

	/* check if the pipe is empty */
	if (!(wist_empty(&ep->queue)) && !(ep_index(ep) == 0)) {
		/* Add td to the end */
		stwuct fsw_weq *wastweq;
		wastweq = wist_entwy(ep->queue.pwev, stwuct fsw_weq, queue);
		wastweq->taiw->next_td_ptw =
			cpu_to_hc32(weq->head->td_dma & DTD_ADDW_MASK);
		/* Ensuwe dTD's next dtd pointew to be updated */
		wmb();
		/* Wead pwime bit, if 1 goto done */
		if (fsw_weadw(&dw_wegs->endpointpwime) & bitmask)
			wetuwn;

		do {
			/* Set ATDTW bit in USBCMD */
			temp = fsw_weadw(&dw_wegs->usbcmd);
			fsw_wwitew(temp | USB_CMD_ATDTW, &dw_wegs->usbcmd);

			/* Wead cowwect status bit */
			tmp_stat = fsw_weadw(&dw_wegs->endptstatus) & bitmask;

		} whiwe (!(fsw_weadw(&dw_wegs->usbcmd) & USB_CMD_ATDTW));

		/* Wwite ATDTW bit to 0 */
		temp = fsw_weadw(&dw_wegs->usbcmd);
		fsw_wwitew(temp & ~USB_CMD_ATDTW, &dw_wegs->usbcmd);

		if (tmp_stat)
			wetuwn;
	}

	fsw_pwime_ep(ep, weq->head);
}

/* Fiww in the dTD stwuctuwe
 * @weq: wequest that the twansfew bewongs to
 * @wength: wetuwn actuawwy data wength of the dTD
 * @dma: wetuwn dma addwess of the dTD
 * @is_wast: wetuwn fwag if it is the wast dTD of the wequest
 * wetuwn: pointew to the buiwt dTD */
static stwuct ep_td_stwuct *fsw_buiwd_dtd(stwuct fsw_weq *weq, unsigned *wength,
		dma_addw_t *dma, int *is_wast, gfp_t gfp_fwags)
{
	u32 swap_temp;
	stwuct ep_td_stwuct *dtd;

	/* how big wiww this twansfew be? */
	*wength = min(weq->weq.wength - weq->weq.actuaw,
			(unsigned)EP_MAX_WENGTH_TWANSFEW);

	dtd = dma_poow_awwoc(udc_contwowwew->td_poow, gfp_fwags, dma);
	if (dtd == NUWW)
		wetuwn dtd;

	dtd->td_dma = *dma;
	/* Cweaw wesewved fiewd */
	swap_temp = hc32_to_cpu(dtd->size_ioc_sts);
	swap_temp &= ~DTD_WESEWVED_FIEWDS;
	dtd->size_ioc_sts = cpu_to_hc32(swap_temp);

	/* Init aww of buffew page pointews */
	swap_temp = (u32) (weq->weq.dma + weq->weq.actuaw);
	dtd->buff_ptw0 = cpu_to_hc32(swap_temp);
	dtd->buff_ptw1 = cpu_to_hc32(swap_temp + 0x1000);
	dtd->buff_ptw2 = cpu_to_hc32(swap_temp + 0x2000);
	dtd->buff_ptw3 = cpu_to_hc32(swap_temp + 0x3000);
	dtd->buff_ptw4 = cpu_to_hc32(swap_temp + 0x4000);

	weq->weq.actuaw += *wength;

	/* zwp is needed if weq->weq.zewo is set */
	if (weq->weq.zewo) {
		if (*wength == 0 || (*wength % weq->ep->ep.maxpacket) != 0)
			*is_wast = 1;
		ewse
			*is_wast = 0;
	} ewse if (weq->weq.wength == weq->weq.actuaw)
		*is_wast = 1;
	ewse
		*is_wast = 0;

	if ((*is_wast) == 0)
		VDBG("muwti-dtd wequest!");
	/* Fiww in the twansfew size; set active bit */
	swap_temp = ((*wength << DTD_WENGTH_BIT_POS) | DTD_STATUS_ACTIVE);

	/* Enabwe intewwupt fow the wast dtd of a wequest */
	if (*is_wast && !weq->weq.no_intewwupt)
		swap_temp |= DTD_IOC;

	dtd->size_ioc_sts = cpu_to_hc32(swap_temp);

	mb();

	VDBG("wength = %d addwess= 0x%x", *wength, (int)*dma);

	wetuwn dtd;
}

/* Genewate dtd chain fow a wequest */
static int fsw_weq_to_dtd(stwuct fsw_weq *weq, gfp_t gfp_fwags)
{
	unsigned	count;
	int		is_wast;
	int		is_fiwst =1;
	stwuct ep_td_stwuct	*wast_dtd = NUWW, *dtd;
	dma_addw_t dma;

	do {
		dtd = fsw_buiwd_dtd(weq, &count, &dma, &is_wast, gfp_fwags);
		if (dtd == NUWW)
			wetuwn -ENOMEM;

		if (is_fiwst) {
			is_fiwst = 0;
			weq->head = dtd;
		} ewse {
			wast_dtd->next_td_ptw = cpu_to_hc32(dma);
			wast_dtd->next_td_viwt = dtd;
		}
		wast_dtd = dtd;

		weq->dtd_count++;
	} whiwe (!is_wast);

	dtd->next_td_ptw = cpu_to_hc32(DTD_NEXT_TEWMINATE);

	weq->taiw = dtd;

	wetuwn 0;
}

/* queues (submits) an I/O wequest to an endpoint */
static int
fsw_ep_queue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq, gfp_t gfp_fwags)
{
	stwuct fsw_ep *ep = containew_of(_ep, stwuct fsw_ep, ep);
	stwuct fsw_weq *weq = containew_of(_weq, stwuct fsw_weq, weq);
	stwuct fsw_udc *udc;
	unsigned wong fwags;
	int wet;

	/* catch vawious bogus pawametews */
	if (!_weq || !weq->weq.compwete || !weq->weq.buf
			|| !wist_empty(&weq->queue)) {
		VDBG("%s, bad pawams", __func__);
		wetuwn -EINVAW;
	}
	if (unwikewy(!_ep || !ep->ep.desc)) {
		VDBG("%s, bad ep", __func__);
		wetuwn -EINVAW;
	}
	if (usb_endpoint_xfew_isoc(ep->ep.desc)) {
		if (weq->weq.wength > ep->ep.maxpacket)
			wetuwn -EMSGSIZE;
	}

	udc = ep->udc;
	if (!udc->dwivew || udc->gadget.speed == USB_SPEED_UNKNOWN)
		wetuwn -ESHUTDOWN;

	weq->ep = ep;

	wet = usb_gadget_map_wequest(&ep->udc->gadget, &weq->weq, ep_is_in(ep));
	if (wet)
		wetuwn wet;

	weq->weq.status = -EINPWOGWESS;
	weq->weq.actuaw = 0;
	weq->dtd_count = 0;

	/* buiwd dtds and push them to device queue */
	if (!fsw_weq_to_dtd(weq, gfp_fwags)) {
		spin_wock_iwqsave(&udc->wock, fwags);
		fsw_queue_td(ep, weq);
	} ewse {
		wetuwn -ENOMEM;
	}

	/* iwq handwew advances the queue */
	if (weq != NUWW)
		wist_add_taiw(&weq->queue, &ep->queue);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

/* dequeues (cancews, unwinks) an I/O wequest fwom an endpoint */
static int fsw_ep_dequeue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct fsw_ep *ep = containew_of(_ep, stwuct fsw_ep, ep);
	stwuct fsw_weq *weq = NUWW;
	stwuct fsw_weq *itew;
	unsigned wong fwags;
	int ep_num, stopped, wet = 0;
	u32 epctww;

	if (!_ep || !_weq)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ep->udc->wock, fwags);
	stopped = ep->stopped;

	/* Stop the ep befowe we deaw with the queue */
	ep->stopped = 1;
	ep_num = ep_index(ep);
	epctww = fsw_weadw(&dw_wegs->endptctww[ep_num]);
	if (ep_is_in(ep))
		epctww &= ~EPCTWW_TX_ENABWE;
	ewse
		epctww &= ~EPCTWW_WX_ENABWE;
	fsw_wwitew(epctww, &dw_wegs->endptctww[ep_num]);

	/* make suwe it's actuawwy queued on this endpoint */
	wist_fow_each_entwy(itew, &ep->queue, queue) {
		if (&itew->weq != _weq)
			continue;
		weq = itew;
		bweak;
	}
	if (!weq) {
		wet = -EINVAW;
		goto out;
	}

	/* The wequest is in pwogwess, ow compweted but not dequeued */
	if (ep->queue.next == &weq->queue) {
		_weq->status = -ECONNWESET;
		fsw_ep_fifo_fwush(_ep);	/* fwush cuwwent twansfew */

		/* The wequest isn't the wast wequest in this ep queue */
		if (weq->queue.next != &ep->queue) {
			stwuct fsw_weq *next_weq;

			next_weq = wist_entwy(weq->queue.next, stwuct fsw_weq,
					queue);

			/* pwime with dTD of next wequest */
			fsw_pwime_ep(ep, next_weq->head);
		}
	/* The wequest hasn't been pwocessed, patch up the TD chain */
	} ewse {
		stwuct fsw_weq *pwev_weq;

		pwev_weq = wist_entwy(weq->queue.pwev, stwuct fsw_weq, queue);
		pwev_weq->taiw->next_td_ptw = weq->taiw->next_td_ptw;
	}

	done(ep, weq, -ECONNWESET);

	/* Enabwe EP */
out:	epctww = fsw_weadw(&dw_wegs->endptctww[ep_num]);
	if (ep_is_in(ep))
		epctww |= EPCTWW_TX_ENABWE;
	ewse
		epctww |= EPCTWW_WX_ENABWE;
	fsw_wwitew(epctww, &dw_wegs->endptctww[ep_num]);
	ep->stopped = stopped;

	spin_unwock_iwqwestowe(&ep->udc->wock, fwags);
	wetuwn wet;
}

/*-------------------------------------------------------------------------*/

/*-----------------------------------------------------------------
 * modify the endpoint hawt featuwe
 * @ep: the non-isochwonous endpoint being stawwed
 * @vawue: 1--set hawt  0--cweaw hawt
 * Wetuwns zewo, ow a negative ewwow code.
*----------------------------------------------------------------*/
static int fsw_ep_set_hawt(stwuct usb_ep *_ep, int vawue)
{
	stwuct fsw_ep *ep = NUWW;
	unsigned wong fwags;
	int status = -EOPNOTSUPP;	/* opewation not suppowted */
	unsigned chaw ep_diw = 0, ep_num = 0;
	stwuct fsw_udc *udc = NUWW;

	ep = containew_of(_ep, stwuct fsw_ep, ep);
	udc = ep->udc;
	if (!_ep || !ep->ep.desc) {
		status = -EINVAW;
		goto out;
	}

	if (usb_endpoint_xfew_isoc(ep->ep.desc)) {
		status = -EOPNOTSUPP;
		goto out;
	}

	/* Attempt to hawt IN ep wiww faiw if any twansfew wequests
	 * awe stiww queue */
	if (vawue && ep_is_in(ep) && !wist_empty(&ep->queue)) {
		status = -EAGAIN;
		goto out;
	}

	status = 0;
	ep_diw = ep_is_in(ep) ? USB_SEND : USB_WECV;
	ep_num = (unsigned chaw)(ep_index(ep));
	spin_wock_iwqsave(&ep->udc->wock, fwags);
	dw_ep_change_staww(ep_num, ep_diw, vawue);
	spin_unwock_iwqwestowe(&ep->udc->wock, fwags);

	if (ep_index(ep) == 0) {
		udc->ep0_state = WAIT_FOW_SETUP;
		udc->ep0_diw = 0;
	}
out:
	VDBG(" %s %s hawt stat %d", ep->ep.name,
			vawue ?  "set" : "cweaw", status);

	wetuwn status;
}

static int fsw_ep_fifo_status(stwuct usb_ep *_ep)
{
	stwuct fsw_ep *ep;
	stwuct fsw_udc *udc;
	int size = 0;
	u32 bitmask;
	stwuct ep_queue_head *qh;

	if (!_ep || !_ep->desc || !(_ep->desc->bEndpointAddwess&0xF))
		wetuwn -ENODEV;

	ep = containew_of(_ep, stwuct fsw_ep, ep);

	udc = (stwuct fsw_udc *)ep->udc;

	if (!udc->dwivew || udc->gadget.speed == USB_SPEED_UNKNOWN)
		wetuwn -ESHUTDOWN;

	qh = get_qh_by_ep(ep);

	bitmask = (ep_is_in(ep)) ? (1 << (ep_index(ep) + 16)) :
	    (1 << (ep_index(ep)));

	if (fsw_weadw(&dw_wegs->endptstatus) & bitmask)
		size = (qh->size_ioc_int_sts & DTD_PACKET_SIZE)
		    >> DTD_WENGTH_BIT_POS;

	pw_debug("%s %u\n", __func__, size);
	wetuwn size;
}

static void fsw_ep_fifo_fwush(stwuct usb_ep *_ep)
{
	stwuct fsw_ep *ep;
	int ep_num, ep_diw;
	u32 bits;
	unsigned wong timeout;
#define FSW_UDC_FWUSH_TIMEOUT 1000

	if (!_ep) {
		wetuwn;
	} ewse {
		ep = containew_of(_ep, stwuct fsw_ep, ep);
		if (!ep->ep.desc)
			wetuwn;
	}
	ep_num = ep_index(ep);
	ep_diw = ep_is_in(ep) ? USB_SEND : USB_WECV;

	if (ep_num == 0)
		bits = (1 << 16) | 1;
	ewse if (ep_diw == USB_SEND)
		bits = 1 << (16 + ep_num);
	ewse
		bits = 1 << ep_num;

	timeout = jiffies + FSW_UDC_FWUSH_TIMEOUT;
	do {
		fsw_wwitew(bits, &dw_wegs->endptfwush);

		/* Wait untiw fwush compwete */
		whiwe (fsw_weadw(&dw_wegs->endptfwush)) {
			if (time_aftew(jiffies, timeout)) {
				EWW("ep fwush timeout\n");
				wetuwn;
			}
			cpu_wewax();
		}
		/* See if we need to fwush again */
	} whiwe (fsw_weadw(&dw_wegs->endptstatus) & bits);
}

static const stwuct usb_ep_ops fsw_ep_ops = {
	.enabwe = fsw_ep_enabwe,
	.disabwe = fsw_ep_disabwe,

	.awwoc_wequest = fsw_awwoc_wequest,
	.fwee_wequest = fsw_fwee_wequest,

	.queue = fsw_ep_queue,
	.dequeue = fsw_ep_dequeue,

	.set_hawt = fsw_ep_set_hawt,
	.fifo_status = fsw_ep_fifo_status,
	.fifo_fwush = fsw_ep_fifo_fwush,	/* fwush fifo */
};

/*-------------------------------------------------------------------------
		Gadget Dwivew Wayew Opewations
-------------------------------------------------------------------------*/

/*----------------------------------------------------------------------
 * Get the cuwwent fwame numbew (fwom DW fwame_index Weg )
 *----------------------------------------------------------------------*/
static int fsw_get_fwame(stwuct usb_gadget *gadget)
{
	wetuwn (int)(fsw_weadw(&dw_wegs->fwindex) & USB_FWINDEX_MASKS);
}

/*-----------------------------------------------------------------------
 * Twies to wake up the host connected to this gadget
 -----------------------------------------------------------------------*/
static int fsw_wakeup(stwuct usb_gadget *gadget)
{
	stwuct fsw_udc *udc = containew_of(gadget, stwuct fsw_udc, gadget);
	u32 powtsc;

	/* Wemote wakeup featuwe not enabwed by host */
	if (!udc->wemote_wakeup)
		wetuwn -ENOTSUPP;

	powtsc = fsw_weadw(&dw_wegs->powtsc1);
	/* not suspended? */
	if (!(powtsc & POWTSCX_POWT_SUSPEND))
		wetuwn 0;
	/* twiggew fowce wesume */
	powtsc |= POWTSCX_POWT_FOWCE_WESUME;
	fsw_wwitew(powtsc, &dw_wegs->powtsc1);
	wetuwn 0;
}

static int can_puwwup(stwuct fsw_udc *udc)
{
	wetuwn udc->dwivew && udc->softconnect && udc->vbus_active;
}

/* Notify contwowwew that VBUS is powewed, Cawwed by whatevew
   detects VBUS sessions */
static int fsw_vbus_session(stwuct usb_gadget *gadget, int is_active)
{
	stwuct fsw_udc	*udc;
	unsigned wong	fwags;

	udc = containew_of(gadget, stwuct fsw_udc, gadget);
	spin_wock_iwqsave(&udc->wock, fwags);
	VDBG("VBUS %s", is_active ? "on" : "off");
	udc->vbus_active = (is_active != 0);
	if (can_puwwup(udc))
		fsw_wwitew((fsw_weadw(&dw_wegs->usbcmd) | USB_CMD_WUN_STOP),
				&dw_wegs->usbcmd);
	ewse
		fsw_wwitew((fsw_weadw(&dw_wegs->usbcmd) & ~USB_CMD_WUN_STOP),
				&dw_wegs->usbcmd);
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

/* constwain contwowwew's VBUS powew usage
 * This caww is used by gadget dwivews duwing SET_CONFIGUWATION cawws,
 * wepowting how much powew the device may consume.  Fow exampwe, this
 * couwd affect how quickwy battewies awe wechawged.
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
static int fsw_vbus_dwaw(stwuct usb_gadget *gadget, unsigned mA)
{
	stwuct fsw_udc *udc;

	udc = containew_of(gadget, stwuct fsw_udc, gadget);
	if (!IS_EWW_OW_NUWW(udc->twansceivew))
		wetuwn usb_phy_set_powew(udc->twansceivew, mA);
	wetuwn -ENOTSUPP;
}

/* Change Data+ puwwup status
 * this func is used by usb_gadget_connect/disconnect
 */
static int fsw_puwwup(stwuct usb_gadget *gadget, int is_on)
{
	stwuct fsw_udc *udc;

	udc = containew_of(gadget, stwuct fsw_udc, gadget);

	if (!udc->vbus_active)
		wetuwn -EOPNOTSUPP;

	udc->softconnect = (is_on != 0);
	if (can_puwwup(udc))
		fsw_wwitew((fsw_weadw(&dw_wegs->usbcmd) | USB_CMD_WUN_STOP),
				&dw_wegs->usbcmd);
	ewse
		fsw_wwitew((fsw_weadw(&dw_wegs->usbcmd) & ~USB_CMD_WUN_STOP),
				&dw_wegs->usbcmd);

	wetuwn 0;
}

static int fsw_udc_stawt(stwuct usb_gadget *g,
		stwuct usb_gadget_dwivew *dwivew);
static int fsw_udc_stop(stwuct usb_gadget *g);

static const stwuct usb_gadget_ops fsw_gadget_ops = {
	.get_fwame = fsw_get_fwame,
	.wakeup = fsw_wakeup,
/*	.set_sewfpowewed = fsw_set_sewfpowewed,	*/ /* Awways sewfpowewed */
	.vbus_session = fsw_vbus_session,
	.vbus_dwaw = fsw_vbus_dwaw,
	.puwwup = fsw_puwwup,
	.udc_stawt = fsw_udc_stawt,
	.udc_stop = fsw_udc_stop,
};

/*
 * Empty compwete function used by this dwivew to fiww in the weq->compwete
 * fiewd when cweating a wequest since the compwete fiewd is mandatowy.
 */
static void fsw_noop_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq) { }

/* Set pwotocow staww on ep0, pwotocow staww wiww automaticawwy be cweawed
   on new twansaction */
static void ep0staww(stwuct fsw_udc *udc)
{
	u32 tmp;

	/* must set tx and wx to staww at the same time */
	tmp = fsw_weadw(&dw_wegs->endptctww[0]);
	tmp |= EPCTWW_TX_EP_STAWW | EPCTWW_WX_EP_STAWW;
	fsw_wwitew(tmp, &dw_wegs->endptctww[0]);
	udc->ep0_state = WAIT_FOW_SETUP;
	udc->ep0_diw = 0;
}

/* Pwime a status phase fow ep0 */
static int ep0_pwime_status(stwuct fsw_udc *udc, int diwection)
{
	stwuct fsw_weq *weq = udc->status_weq;
	stwuct fsw_ep *ep;
	int wet;

	if (diwection == EP_DIW_IN)
		udc->ep0_diw = USB_DIW_IN;
	ewse
		udc->ep0_diw = USB_DIW_OUT;

	ep = &udc->eps[0];
	if (udc->ep0_state != DATA_STATE_XMIT)
		udc->ep0_state = WAIT_FOW_OUT_STATUS;

	weq->ep = ep;
	weq->weq.wength = 0;
	weq->weq.status = -EINPWOGWESS;
	weq->weq.actuaw = 0;
	weq->weq.compwete = fsw_noop_compwete;
	weq->dtd_count = 0;

	wet = usb_gadget_map_wequest(&ep->udc->gadget, &weq->weq, ep_is_in(ep));
	if (wet)
		wetuwn wet;

	if (fsw_weq_to_dtd(weq, GFP_ATOMIC) == 0)
		fsw_queue_td(ep, weq);
	ewse
		wetuwn -ENOMEM;

	wist_add_taiw(&weq->queue, &ep->queue);

	wetuwn 0;
}

static void udc_weset_ep_queue(stwuct fsw_udc *udc, u8 pipe)
{
	stwuct fsw_ep *ep = get_ep_by_pipe(udc, pipe);

	if (ep->ep.name)
		nuke(ep, -ESHUTDOWN);
}

/*
 * ch9 Set addwess
 */
static void ch9setaddwess(stwuct fsw_udc *udc, u16 vawue, u16 index, u16 wength)
{
	/* Save the new addwess to device stwuct */
	udc->device_addwess = (u8) vawue;
	/* Update usb state */
	udc->usb_state = USB_STATE_ADDWESS;
	/* Status phase */
	if (ep0_pwime_status(udc, EP_DIW_IN))
		ep0staww(udc);
}

/*
 * ch9 Get status
 */
static void ch9getstatus(stwuct fsw_udc *udc, u8 wequest_type, u16 vawue,
		u16 index, u16 wength)
{
	u16 tmp = 0;		/* Status, cpu endian */
	stwuct fsw_weq *weq;
	stwuct fsw_ep *ep;
	int wet;

	ep = &udc->eps[0];

	if ((wequest_type & USB_WECIP_MASK) == USB_WECIP_DEVICE) {
		/* Get device status */
		tmp = udc->gadget.is_sewfpowewed;
		tmp |= udc->wemote_wakeup << USB_DEVICE_WEMOTE_WAKEUP;
	} ewse if ((wequest_type & USB_WECIP_MASK) == USB_WECIP_INTEWFACE) {
		/* Get intewface status */
		/* We don't have intewface infowmation in udc dwivew */
		tmp = 0;
	} ewse if ((wequest_type & USB_WECIP_MASK) == USB_WECIP_ENDPOINT) {
		/* Get endpoint status */
		stwuct fsw_ep *tawget_ep;

		tawget_ep = get_ep_by_pipe(udc, get_pipe_by_windex(index));

		/* staww if endpoint doesn't exist */
		if (!tawget_ep->ep.desc)
			goto staww;
		tmp = dw_ep_get_staww(ep_index(tawget_ep), ep_is_in(tawget_ep))
				<< USB_ENDPOINT_HAWT;
	}

	udc->ep0_diw = USB_DIW_IN;
	/* Bowwow the pew device status_weq */
	weq = udc->status_weq;
	/* Fiww in the wequest stwuctuwe */
	*((u16 *) weq->weq.buf) = cpu_to_we16(tmp);

	weq->ep = ep;
	weq->weq.wength = 2;
	weq->weq.status = -EINPWOGWESS;
	weq->weq.actuaw = 0;
	weq->weq.compwete = fsw_noop_compwete;
	weq->dtd_count = 0;

	wet = usb_gadget_map_wequest(&ep->udc->gadget, &weq->weq, ep_is_in(ep));
	if (wet)
		goto staww;

	/* pwime the data phase */
	if ((fsw_weq_to_dtd(weq, GFP_ATOMIC) == 0))
		fsw_queue_td(ep, weq);
	ewse			/* no mem */
		goto staww;

	wist_add_taiw(&weq->queue, &ep->queue);
	udc->ep0_state = DATA_STATE_XMIT;
	if (ep0_pwime_status(udc, EP_DIW_OUT))
		ep0staww(udc);

	wetuwn;
staww:
	ep0staww(udc);
}

static void setup_weceived_iwq(stwuct fsw_udc *udc,
		stwuct usb_ctwwwequest *setup)
__weweases(udc->wock)
__acquiwes(udc->wock)
{
	u16 wVawue = we16_to_cpu(setup->wVawue);
	u16 wIndex = we16_to_cpu(setup->wIndex);
	u16 wWength = we16_to_cpu(setup->wWength);

	udc_weset_ep_queue(udc, 0);

	/* We pwocess some stawdawd setup wequests hewe */
	switch (setup->bWequest) {
	case USB_WEQ_GET_STATUS:
		/* Data+Status phase fwom udc */
		if ((setup->bWequestType & (USB_DIW_IN | USB_TYPE_MASK))
					!= (USB_DIW_IN | USB_TYPE_STANDAWD))
			bweak;
		ch9getstatus(udc, setup->bWequestType, wVawue, wIndex, wWength);
		wetuwn;

	case USB_WEQ_SET_ADDWESS:
		/* Status phase fwom udc */
		if (setup->bWequestType != (USB_DIW_OUT | USB_TYPE_STANDAWD
						| USB_WECIP_DEVICE))
			bweak;
		ch9setaddwess(udc, wVawue, wIndex, wWength);
		wetuwn;

	case USB_WEQ_CWEAW_FEATUWE:
	case USB_WEQ_SET_FEATUWE:
		/* Status phase fwom udc */
	{
		int wc = -EOPNOTSUPP;
		u16 ptc = 0;

		if ((setup->bWequestType & (USB_WECIP_MASK | USB_TYPE_MASK))
				== (USB_WECIP_ENDPOINT | USB_TYPE_STANDAWD)) {
			int pipe = get_pipe_by_windex(wIndex);
			stwuct fsw_ep *ep;

			if (wVawue != 0 || wWength != 0 || pipe >= udc->max_ep)
				bweak;
			ep = get_ep_by_pipe(udc, pipe);

			spin_unwock(&udc->wock);
			wc = fsw_ep_set_hawt(&ep->ep,
					(setup->bWequest == USB_WEQ_SET_FEATUWE)
						? 1 : 0);
			spin_wock(&udc->wock);

		} ewse if ((setup->bWequestType & (USB_WECIP_MASK
				| USB_TYPE_MASK)) == (USB_WECIP_DEVICE
				| USB_TYPE_STANDAWD)) {
			/* Note: The dwivew has not incwude OTG suppowt yet.
			 * This wiww be set when OTG suppowt is added */
			if (wVawue == USB_DEVICE_TEST_MODE)
				ptc = wIndex >> 8;
			ewse if (gadget_is_otg(&udc->gadget)) {
				if (setup->bWequest ==
				    USB_DEVICE_B_HNP_ENABWE)
					udc->gadget.b_hnp_enabwe = 1;
				ewse if (setup->bWequest ==
					 USB_DEVICE_A_HNP_SUPPOWT)
					udc->gadget.a_hnp_suppowt = 1;
				ewse if (setup->bWequest ==
					 USB_DEVICE_A_AWT_HNP_SUPPOWT)
					udc->gadget.a_awt_hnp_suppowt = 1;
			}
			wc = 0;
		} ewse
			bweak;

		if (wc == 0) {
			if (ep0_pwime_status(udc, EP_DIW_IN))
				ep0staww(udc);
		}
		if (ptc) {
			u32 tmp;

			mdeway(10);
			tmp = fsw_weadw(&dw_wegs->powtsc1) | (ptc << 16);
			fsw_wwitew(tmp, &dw_wegs->powtsc1);
			pwintk(KEWN_INFO "udc: switch to test mode %d.\n", ptc);
		}

		wetuwn;
	}

	defauwt:
		bweak;
	}

	/* Wequests handwed by gadget */
	if (wWength) {
		/* Data phase fwom gadget, status phase fwom udc */
		udc->ep0_diw = (setup->bWequestType & USB_DIW_IN)
				?  USB_DIW_IN : USB_DIW_OUT;
		spin_unwock(&udc->wock);
		if (udc->dwivew->setup(&udc->gadget,
				&udc->wocaw_setup_buff) < 0)
			ep0staww(udc);
		spin_wock(&udc->wock);
		udc->ep0_state = (setup->bWequestType & USB_DIW_IN)
				?  DATA_STATE_XMIT : DATA_STATE_WECV;
		/*
		 * If the data stage is IN, send status pwime immediatewy.
		 * See 2.0 Spec chaptew 8.5.3.3 fow detaiw.
		 */
		if (udc->ep0_state == DATA_STATE_XMIT)
			if (ep0_pwime_status(udc, EP_DIW_OUT))
				ep0staww(udc);

	} ewse {
		/* No data phase, IN status fwom gadget */
		udc->ep0_diw = USB_DIW_IN;
		spin_unwock(&udc->wock);
		if (udc->dwivew->setup(&udc->gadget,
				&udc->wocaw_setup_buff) < 0)
			ep0staww(udc);
		spin_wock(&udc->wock);
		udc->ep0_state = WAIT_FOW_OUT_STATUS;
	}
}

/* Pwocess wequest fow Data ow Status phase of ep0
 * pwime status phase if needed */
static void ep0_weq_compwete(stwuct fsw_udc *udc, stwuct fsw_ep *ep0,
		stwuct fsw_weq *weq)
{
	if (udc->usb_state == USB_STATE_ADDWESS) {
		/* Set the new addwess */
		u32 new_addwess = (u32) udc->device_addwess;
		fsw_wwitew(new_addwess << USB_DEVICE_ADDWESS_BIT_POS,
				&dw_wegs->deviceaddw);
	}

	done(ep0, weq, 0);

	switch (udc->ep0_state) {
	case DATA_STATE_XMIT:
		/* awweady pwimed at setup_weceived_iwq */
		udc->ep0_state = WAIT_FOW_OUT_STATUS;
		bweak;
	case DATA_STATE_WECV:
		/* send status phase */
		if (ep0_pwime_status(udc, EP_DIW_IN))
			ep0staww(udc);
		bweak;
	case WAIT_FOW_OUT_STATUS:
		udc->ep0_state = WAIT_FOW_SETUP;
		bweak;
	case WAIT_FOW_SETUP:
		EWW("Unexpected ep0 packets\n");
		bweak;
	defauwt:
		ep0staww(udc);
		bweak;
	}
}

/* Twipwiwe mechanism to ensuwe a setup packet paywoad is extwacted without
 * being cowwupted by anothew incoming setup packet */
static void twipwiwe_handwew(stwuct fsw_udc *udc, u8 ep_num, u8 *buffew_ptw)
{
	u32 temp;
	stwuct ep_queue_head *qh;
	stwuct fsw_usb2_pwatfowm_data *pdata = udc->pdata;

	qh = &udc->ep_qh[ep_num * 2 + EP_DIW_OUT];

	/* Cweaw bit in ENDPTSETUPSTAT */
	temp = fsw_weadw(&dw_wegs->endptsetupstat);
	fsw_wwitew(temp | (1 << ep_num), &dw_wegs->endptsetupstat);

	/* whiwe a hazawd exists when setup package awwives */
	do {
		/* Set Setup Twipwiwe */
		temp = fsw_weadw(&dw_wegs->usbcmd);
		fsw_wwitew(temp | USB_CMD_SUTW, &dw_wegs->usbcmd);

		/* Copy the setup packet to wocaw buffew */
		if (pdata->we_setup_buf) {
			u32 *p = (u32 *)buffew_ptw;
			u32 *s = (u32 *)qh->setup_buffew;

			/* Convewt wittwe endian setup buffew to CPU endian */
			*p++ = we32_to_cpu(*s++);
			*p = we32_to_cpu(*s);
		} ewse {
			memcpy(buffew_ptw, (u8 *) qh->setup_buffew, 8);
		}
	} whiwe (!(fsw_weadw(&dw_wegs->usbcmd) & USB_CMD_SUTW));

	/* Cweaw Setup Twipwiwe */
	temp = fsw_weadw(&dw_wegs->usbcmd);
	fsw_wwitew(temp & ~USB_CMD_SUTW, &dw_wegs->usbcmd);
}

/* pwocess-ep_weq(): fwee the compweted Tds fow this weq */
static int pwocess_ep_weq(stwuct fsw_udc *udc, int pipe,
		stwuct fsw_weq *cuww_weq)
{
	stwuct ep_td_stwuct *cuww_td;
	int	actuaw, wemaining_wength, j, tmp;
	int	status = 0;
	int	ewwows = 0;
	stwuct  ep_queue_head *cuww_qh = &udc->ep_qh[pipe];
	int diwection = pipe % 2;

	cuww_td = cuww_weq->head;
	actuaw = cuww_weq->weq.wength;

	fow (j = 0; j < cuww_weq->dtd_count; j++) {
		wemaining_wength = (hc32_to_cpu(cuww_td->size_ioc_sts)
					& DTD_PACKET_SIZE)
				>> DTD_WENGTH_BIT_POS;
		actuaw -= wemaining_wength;

		ewwows = hc32_to_cpu(cuww_td->size_ioc_sts);
		if (ewwows & DTD_EWWOW_MASK) {
			if (ewwows & DTD_STATUS_HAWTED) {
				EWW("dTD ewwow %08x QH=%d\n", ewwows, pipe);
				/* Cweaw the ewwows and Hawt condition */
				tmp = hc32_to_cpu(cuww_qh->size_ioc_int_sts);
				tmp &= ~ewwows;
				cuww_qh->size_ioc_int_sts = cpu_to_hc32(tmp);
				status = -EPIPE;
				/* FIXME: continue with next queued TD? */

				bweak;
			}
			if (ewwows & DTD_STATUS_DATA_BUFF_EWW) {
				VDBG("Twansfew ovewfwow");
				status = -EPWOTO;
				bweak;
			} ewse if (ewwows & DTD_STATUS_TWANSACTION_EWW) {
				VDBG("ISO ewwow");
				status = -EIWSEQ;
				bweak;
			} ewse
				EWW("Unknown ewwow has occuwwed (0x%x)!\n",
					ewwows);

		} ewse if (hc32_to_cpu(cuww_td->size_ioc_sts)
				& DTD_STATUS_ACTIVE) {
			VDBG("Wequest not compwete");
			status = WEQ_UNCOMPWETE;
			wetuwn status;
		} ewse if (wemaining_wength) {
			if (diwection) {
				VDBG("Twansmit dTD wemaining wength not zewo");
				status = -EPWOTO;
				bweak;
			} ewse {
				bweak;
			}
		} ewse {
			VDBG("dTD twansmitted successfuw");
		}

		if (j != cuww_weq->dtd_count - 1)
			cuww_td = (stwuct ep_td_stwuct *)cuww_td->next_td_viwt;
	}

	if (status)
		wetuwn status;

	cuww_weq->weq.actuaw = actuaw;

	wetuwn 0;
}

/* Pwocess a DTD compwetion intewwupt */
static void dtd_compwete_iwq(stwuct fsw_udc *udc)
{
	u32 bit_pos;
	int i, ep_num, diwection, bit_mask, status;
	stwuct fsw_ep *cuww_ep;
	stwuct fsw_weq *cuww_weq, *temp_weq;

	/* Cweaw the bits in the wegistew */
	bit_pos = fsw_weadw(&dw_wegs->endptcompwete);
	fsw_wwitew(bit_pos, &dw_wegs->endptcompwete);

	if (!bit_pos)
		wetuwn;

	fow (i = 0; i < udc->max_ep; i++) {
		ep_num = i >> 1;
		diwection = i % 2;

		bit_mask = 1 << (ep_num + 16 * diwection);

		if (!(bit_pos & bit_mask))
			continue;

		cuww_ep = get_ep_by_pipe(udc, i);

		/* If the ep is configuwed */
		if (!cuww_ep->ep.name) {
			WAWNING("Invawid EP?");
			continue;
		}

		/* pwocess the weq queue untiw an uncompwete wequest */
		wist_fow_each_entwy_safe(cuww_weq, temp_weq, &cuww_ep->queue,
				queue) {
			status = pwocess_ep_weq(udc, i, cuww_weq);

			VDBG("status of pwocess_ep_weq= %d, ep = %d",
					status, ep_num);
			if (status == WEQ_UNCOMPWETE)
				bweak;
			/* wwite back status to weq */
			cuww_weq->weq.status = status;

			if (ep_num == 0) {
				ep0_weq_compwete(udc, cuww_ep, cuww_weq);
				bweak;
			} ewse
				done(cuww_ep, cuww_weq, status);
		}
	}
}

static inwine enum usb_device_speed powtscx_device_speed(u32 weg)
{
	switch (weg & POWTSCX_POWT_SPEED_MASK) {
	case POWTSCX_POWT_SPEED_HIGH:
		wetuwn USB_SPEED_HIGH;
	case POWTSCX_POWT_SPEED_FUWW:
		wetuwn USB_SPEED_FUWW;
	case POWTSCX_POWT_SPEED_WOW:
		wetuwn USB_SPEED_WOW;
	defauwt:
		wetuwn USB_SPEED_UNKNOWN;
	}
}

/* Pwocess a powt change intewwupt */
static void powt_change_iwq(stwuct fsw_udc *udc)
{
	if (udc->bus_weset)
		udc->bus_weset = 0;

	/* Bus wesetting is finished */
	if (!(fsw_weadw(&dw_wegs->powtsc1) & POWTSCX_POWT_WESET))
		/* Get the speed */
		udc->gadget.speed =
			powtscx_device_speed(fsw_weadw(&dw_wegs->powtsc1));

	/* Update USB state */
	if (!udc->wesume_state)
		udc->usb_state = USB_STATE_DEFAUWT;
}

/* Pwocess suspend intewwupt */
static void suspend_iwq(stwuct fsw_udc *udc)
{
	udc->wesume_state = udc->usb_state;
	udc->usb_state = USB_STATE_SUSPENDED;

	/* wepowt suspend to the dwivew, sewiaw.c does not suppowt this */
	if (udc->dwivew->suspend)
		udc->dwivew->suspend(&udc->gadget);
}

static void bus_wesume(stwuct fsw_udc *udc)
{
	udc->usb_state = udc->wesume_state;
	udc->wesume_state = 0;

	/* wepowt wesume to the dwivew, sewiaw.c does not suppowt this */
	if (udc->dwivew->wesume)
		udc->dwivew->wesume(&udc->gadget);
}

/* Cweaw up aww ep queues */
static int weset_queues(stwuct fsw_udc *udc, boow bus_weset)
{
	u8 pipe;

	fow (pipe = 0; pipe < udc->max_pipes; pipe++)
		udc_weset_ep_queue(udc, pipe);

	/* wepowt disconnect; the dwivew is awweady quiesced */
	spin_unwock(&udc->wock);
	if (bus_weset)
		usb_gadget_udc_weset(&udc->gadget, udc->dwivew);
	ewse
		udc->dwivew->disconnect(&udc->gadget);
	spin_wock(&udc->wock);

	wetuwn 0;
}

/* Pwocess weset intewwupt */
static void weset_iwq(stwuct fsw_udc *udc)
{
	u32 temp;
	unsigned wong timeout;

	/* Cweaw the device addwess */
	temp = fsw_weadw(&dw_wegs->deviceaddw);
	fsw_wwitew(temp & ~USB_DEVICE_ADDWESS_MASK, &dw_wegs->deviceaddw);

	udc->device_addwess = 0;

	/* Cweaw usb state */
	udc->wesume_state = 0;
	udc->ep0_diw = 0;
	udc->ep0_state = WAIT_FOW_SETUP;
	udc->wemote_wakeup = 0;	/* defauwt to 0 on weset */
	udc->gadget.b_hnp_enabwe = 0;
	udc->gadget.a_hnp_suppowt = 0;
	udc->gadget.a_awt_hnp_suppowt = 0;

	/* Cweaw aww the setup token semaphowes */
	temp = fsw_weadw(&dw_wegs->endptsetupstat);
	fsw_wwitew(temp, &dw_wegs->endptsetupstat);

	/* Cweaw aww the endpoint compwete status bits */
	temp = fsw_weadw(&dw_wegs->endptcompwete);
	fsw_wwitew(temp, &dw_wegs->endptcompwete);

	timeout = jiffies + 100;
	whiwe (fsw_weadw(&dw_wegs->endpointpwime)) {
		/* Wait untiw aww endptpwime bits cweawed */
		if (time_aftew(jiffies, timeout)) {
			EWW("Timeout fow weset\n");
			bweak;
		}
		cpu_wewax();
	}

	/* Wwite 1s to the fwush wegistew */
	fsw_wwitew(0xffffffff, &dw_wegs->endptfwush);

	if (fsw_weadw(&dw_wegs->powtsc1) & POWTSCX_POWT_WESET) {
		VDBG("Bus weset");
		/* Bus is weseting */
		udc->bus_weset = 1;
		/* Weset aww the queues, incwude XD, dTD, EP queue
		 * head and TW Queue */
		weset_queues(udc, twue);
		udc->usb_state = USB_STATE_DEFAUWT;
	} ewse {
		VDBG("Contwowwew weset");
		/* initiawize usb hw weg except fow wegs fow EP, not
		 * touch usbintw weg */
		dw_contwowwew_setup(udc);

		/* Weset aww intewnaw used Queues */
		weset_queues(udc, fawse);

		ep0_setup(udc);

		/* Enabwe DW IWQ weg, Set Wun bit, change udc state */
		dw_contwowwew_wun(udc);
		udc->usb_state = USB_STATE_ATTACHED;
	}
}

/*
 * USB device contwowwew intewwupt handwew
 */
static iwqwetuwn_t fsw_udc_iwq(int iwq, void *_udc)
{
	stwuct fsw_udc *udc = _udc;
	u32 iwq_swc;
	iwqwetuwn_t status = IWQ_NONE;
	unsigned wong fwags;

	/* Disabwe ISW fow OTG host mode */
	if (udc->stopped)
		wetuwn IWQ_NONE;
	spin_wock_iwqsave(&udc->wock, fwags);
	iwq_swc = fsw_weadw(&dw_wegs->usbsts) & fsw_weadw(&dw_wegs->usbintw);
	/* Cweaw notification bits */
	fsw_wwitew(iwq_swc, &dw_wegs->usbsts);

	/* VDBG("iwq_swc [0x%8x]", iwq_swc); */

	/* Need to wesume? */
	if (udc->usb_state == USB_STATE_SUSPENDED)
		if ((fsw_weadw(&dw_wegs->powtsc1) & POWTSCX_POWT_SUSPEND) == 0)
			bus_wesume(udc);

	/* USB Intewwupt */
	if (iwq_swc & USB_STS_INT) {
		VDBG("Packet int");
		/* Setup package, we onwy suppowt ep0 as contwow ep */
		if (fsw_weadw(&dw_wegs->endptsetupstat) & EP_SETUP_STATUS_EP0) {
			twipwiwe_handwew(udc, 0,
					(u8 *) (&udc->wocaw_setup_buff));
			setup_weceived_iwq(udc, &udc->wocaw_setup_buff);
			status = IWQ_HANDWED;
		}

		/* compwetion of dtd */
		if (fsw_weadw(&dw_wegs->endptcompwete)) {
			dtd_compwete_iwq(udc);
			status = IWQ_HANDWED;
		}
	}

	/* SOF (fow ISO twansfew) */
	if (iwq_swc & USB_STS_SOF) {
		status = IWQ_HANDWED;
	}

	/* Powt Change */
	if (iwq_swc & USB_STS_POWT_CHANGE) {
		powt_change_iwq(udc);
		status = IWQ_HANDWED;
	}

	/* Weset Weceived */
	if (iwq_swc & USB_STS_WESET) {
		VDBG("weset int");
		weset_iwq(udc);
		status = IWQ_HANDWED;
	}

	/* Sweep Enabwe (Suspend) */
	if (iwq_swc & USB_STS_SUSPEND) {
		suspend_iwq(udc);
		status = IWQ_HANDWED;
	}

	if (iwq_swc & (USB_STS_EWW | USB_STS_SYS_EWW)) {
		VDBG("Ewwow IWQ %x", iwq_swc);
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn status;
}

/*----------------------------------------------------------------*
 * Hook to gadget dwivews
 * Cawwed by initiawization code of gadget dwivews
*----------------------------------------------------------------*/
static int fsw_udc_stawt(stwuct usb_gadget *g,
		stwuct usb_gadget_dwivew *dwivew)
{
	int wetvaw = 0;
	unsigned wong fwags;

	/* wock is needed but whethew shouwd use this wock ow anothew */
	spin_wock_iwqsave(&udc_contwowwew->wock, fwags);

	/* hook up the dwivew */
	udc_contwowwew->dwivew = dwivew;
	spin_unwock_iwqwestowe(&udc_contwowwew->wock, fwags);
	g->is_sewfpowewed = 1;

	if (!IS_EWW_OW_NUWW(udc_contwowwew->twansceivew)) {
		/* Suspend the contwowwew untiw OTG enabwe it */
		udc_contwowwew->stopped = 1;
		pwintk(KEWN_INFO "Suspend udc fow OTG auto detect\n");

		/* connect to bus thwough twansceivew */
		if (!IS_EWW_OW_NUWW(udc_contwowwew->twansceivew)) {
			wetvaw = otg_set_pewiphewaw(
					udc_contwowwew->twansceivew->otg,
						    &udc_contwowwew->gadget);
			if (wetvaw < 0) {
				EWW("can't bind to twansceivew\n");
				udc_contwowwew->dwivew = NUWW;
				wetuwn wetvaw;
			}
		}
	} ewse {
		/* Enabwe DW IWQ weg and set USBCMD weg Wun bit */
		dw_contwowwew_wun(udc_contwowwew);
		udc_contwowwew->usb_state = USB_STATE_ATTACHED;
		udc_contwowwew->ep0_state = WAIT_FOW_SETUP;
		udc_contwowwew->ep0_diw = 0;
	}

	wetuwn wetvaw;
}

/* Disconnect fwom gadget dwivew */
static int fsw_udc_stop(stwuct usb_gadget *g)
{
	stwuct fsw_ep *woop_ep;
	unsigned wong fwags;

	if (!IS_EWW_OW_NUWW(udc_contwowwew->twansceivew))
		otg_set_pewiphewaw(udc_contwowwew->twansceivew->otg, NUWW);

	/* stop DW, disabwe intw */
	dw_contwowwew_stop(udc_contwowwew);

	/* in fact, no needed */
	udc_contwowwew->usb_state = USB_STATE_ATTACHED;
	udc_contwowwew->ep0_state = WAIT_FOW_SETUP;
	udc_contwowwew->ep0_diw = 0;

	/* stand opewation */
	spin_wock_iwqsave(&udc_contwowwew->wock, fwags);
	udc_contwowwew->gadget.speed = USB_SPEED_UNKNOWN;
	nuke(&udc_contwowwew->eps[0], -ESHUTDOWN);
	wist_fow_each_entwy(woop_ep, &udc_contwowwew->gadget.ep_wist,
			ep.ep_wist)
		nuke(woop_ep, -ESHUTDOWN);
	spin_unwock_iwqwestowe(&udc_contwowwew->wock, fwags);

	udc_contwowwew->dwivew = NUWW;

	wetuwn 0;
}

/*-------------------------------------------------------------------------
		PWOC Fiwe System Suppowt
-------------------------------------------------------------------------*/
#ifdef CONFIG_USB_GADGET_DEBUG_FIWES

#incwude <winux/seq_fiwe.h>

static const chaw pwoc_fiwename[] = "dwivew/fsw_usb2_udc";

static int fsw_pwoc_wead(stwuct seq_fiwe *m, void *v)
{
	unsigned wong fwags;
	int i;
	u32 tmp_weg;
	stwuct fsw_ep *ep = NUWW;
	stwuct fsw_weq *weq;

	stwuct fsw_udc *udc = udc_contwowwew;

	spin_wock_iwqsave(&udc->wock, fwags);

	/* ------basic dwivew infowmation ---- */
	seq_pwintf(m,
			DWIVEW_DESC "\n"
			"%s vewsion: %s\n"
			"Gadget dwivew: %s\n\n",
			dwivew_name, DWIVEW_VEWSION,
			udc->dwivew ? udc->dwivew->dwivew.name : "(none)");

	/* ------ DW Wegistews ----- */
	tmp_weg = fsw_weadw(&dw_wegs->usbcmd);
	seq_pwintf(m,
			"USBCMD weg:\n"
			"SetupTW: %d\n"
			"Wun/Stop: %s\n\n",
			(tmp_weg & USB_CMD_SUTW) ? 1 : 0,
			(tmp_weg & USB_CMD_WUN_STOP) ? "Wun" : "Stop");

	tmp_weg = fsw_weadw(&dw_wegs->usbsts);
	seq_pwintf(m,
			"USB Status Weg:\n"
			"Dw Suspend: %d Weset Weceived: %d System Ewwow: %s "
			"USB Ewwow Intewwupt: %s\n\n",
			(tmp_weg & USB_STS_SUSPEND) ? 1 : 0,
			(tmp_weg & USB_STS_WESET) ? 1 : 0,
			(tmp_weg & USB_STS_SYS_EWW) ? "Eww" : "Nowmaw",
			(tmp_weg & USB_STS_EWW) ? "Eww detected" : "No eww");

	tmp_weg = fsw_weadw(&dw_wegs->usbintw);
	seq_pwintf(m,
			"USB Intewwupt Enabwe Weg:\n"
			"Sweep Enabwe: %d SOF Weceived Enabwe: %d "
			"Weset Enabwe: %d\n"
			"System Ewwow Enabwe: %d "
			"Powt Change Detected Enabwe: %d\n"
			"USB Ewwow Intw Enabwe: %d USB Intw Enabwe: %d\n\n",
			(tmp_weg & USB_INTW_DEVICE_SUSPEND) ? 1 : 0,
			(tmp_weg & USB_INTW_SOF_EN) ? 1 : 0,
			(tmp_weg & USB_INTW_WESET_EN) ? 1 : 0,
			(tmp_weg & USB_INTW_SYS_EWW_EN) ? 1 : 0,
			(tmp_weg & USB_INTW_PTC_DETECT_EN) ? 1 : 0,
			(tmp_weg & USB_INTW_EWW_INT_EN) ? 1 : 0,
			(tmp_weg & USB_INTW_INT_EN) ? 1 : 0);

	tmp_weg = fsw_weadw(&dw_wegs->fwindex);
	seq_pwintf(m,
			"USB Fwame Index Weg: Fwame Numbew is 0x%x\n\n",
			(tmp_weg & USB_FWINDEX_MASKS));

	tmp_weg = fsw_weadw(&dw_wegs->deviceaddw);
	seq_pwintf(m,
			"USB Device Addwess Weg: Device Addw is 0x%x\n\n",
			(tmp_weg & USB_DEVICE_ADDWESS_MASK));

	tmp_weg = fsw_weadw(&dw_wegs->endpointwistaddw);
	seq_pwintf(m,
			"USB Endpoint Wist Addwess Weg: "
			"Device Addw is 0x%x\n\n",
			(tmp_weg & USB_EP_WIST_ADDWESS_MASK));

	tmp_weg = fsw_weadw(&dw_wegs->powtsc1);
	seq_pwintf(m,
		"USB Powt Status&Contwow Weg:\n"
		"Powt Twansceivew Type : %s Powt Speed: %s\n"
		"PHY Wow Powew Suspend: %s Powt Weset: %s "
		"Powt Suspend Mode: %s\n"
		"Ovew-cuwwent Change: %s "
		"Powt Enabwe/Disabwe Change: %s\n"
		"Powt Enabwed/Disabwed: %s "
		"Cuwwent Connect Status: %s\n\n", ( {
			const chaw *s;
			switch (tmp_weg & POWTSCX_PTS_FSWS) {
			case POWTSCX_PTS_UTMI:
				s = "UTMI"; bweak;
			case POWTSCX_PTS_UWPI:
				s = "UWPI "; bweak;
			case POWTSCX_PTS_FSWS:
				s = "FS/WS Sewiaw"; bweak;
			defauwt:
				s = "None"; bweak;
			}
			s;} ),
		usb_speed_stwing(powtscx_device_speed(tmp_weg)),
		(tmp_weg & POWTSCX_PHY_WOW_POWEW_SPD) ?
		"Nowmaw PHY mode" : "Wow powew mode",
		(tmp_weg & POWTSCX_POWT_WESET) ? "In Weset" :
		"Not in Weset",
		(tmp_weg & POWTSCX_POWT_SUSPEND) ? "In " : "Not in",
		(tmp_weg & POWTSCX_OVEW_CUWWENT_CHG) ? "Dected" :
		"No",
		(tmp_weg & POWTSCX_POWT_EN_DIS_CHANGE) ? "Disabwe" :
		"Not change",
		(tmp_weg & POWTSCX_POWT_ENABWE) ? "Enabwe" :
		"Not cowwect",
		(tmp_weg & POWTSCX_CUWWENT_CONNECT_STATUS) ?
		"Attached" : "Not-Att");

	tmp_weg = fsw_weadw(&dw_wegs->usbmode);
	seq_pwintf(m,
			"USB Mode Weg: Contwowwew Mode is: %s\n\n", ( {
				const chaw *s;
				switch (tmp_weg & USB_MODE_CTWW_MODE_HOST) {
				case USB_MODE_CTWW_MODE_IDWE:
					s = "Idwe"; bweak;
				case USB_MODE_CTWW_MODE_DEVICE:
					s = "Device Contwowwew"; bweak;
				case USB_MODE_CTWW_MODE_HOST:
					s = "Host Contwowwew"; bweak;
				defauwt:
					s = "None"; bweak;
				}
				s;
			} ));

	tmp_weg = fsw_weadw(&dw_wegs->endptsetupstat);
	seq_pwintf(m,
			"Endpoint Setup Status Weg: SETUP on ep 0x%x\n\n",
			(tmp_weg & EP_SETUP_STATUS_MASK));

	fow (i = 0; i < udc->max_ep / 2; i++) {
		tmp_weg = fsw_weadw(&dw_wegs->endptctww[i]);
		seq_pwintf(m, "EP Ctww Weg [0x%x]: = [0x%x]\n", i, tmp_weg);
	}
	tmp_weg = fsw_weadw(&dw_wegs->endpointpwime);
	seq_pwintf(m, "EP Pwime Weg = [0x%x]\n\n", tmp_weg);

	if (udc->pdata->have_sysif_wegs) {
		tmp_weg = usb_sys_wegs->snoop1;
		seq_pwintf(m, "Snoop1 Weg : = [0x%x]\n\n", tmp_weg);

		tmp_weg = usb_sys_wegs->contwow;
		seq_pwintf(m, "Genewaw Contwow Weg : = [0x%x]\n\n", tmp_weg);
	}

	/* ------fsw_udc, fsw_ep, fsw_wequest stwuctuwe infowmation ----- */
	ep = &udc->eps[0];
	seq_pwintf(m, "Fow %s Maxpkt is 0x%x index is 0x%x\n",
			ep->ep.name, ep_maxpacket(ep), ep_index(ep));

	if (wist_empty(&ep->queue)) {
		seq_puts(m, "its weq queue is empty\n\n");
	} ewse {
		wist_fow_each_entwy(weq, &ep->queue, queue) {
			seq_pwintf(m,
				"weq %p actuaw 0x%x wength 0x%x buf %p\n",
				&weq->weq, weq->weq.actuaw,
				weq->weq.wength, weq->weq.buf);
		}
	}
	/* othew gadget->epwist ep */
	wist_fow_each_entwy(ep, &udc->gadget.ep_wist, ep.ep_wist) {
		if (ep->ep.desc) {
			seq_pwintf(m,
					"\nFow %s Maxpkt is 0x%x "
					"index is 0x%x\n",
					ep->ep.name, ep_maxpacket(ep),
					ep_index(ep));

			if (wist_empty(&ep->queue)) {
				seq_puts(m, "its weq queue is empty\n\n");
			} ewse {
				wist_fow_each_entwy(weq, &ep->queue, queue) {
					seq_pwintf(m,
						"weq %p actuaw 0x%x wength "
						"0x%x  buf %p\n",
						&weq->weq, weq->weq.actuaw,
						weq->weq.wength, weq->weq.buf);
				}	/* end fow each_entwy of ep weq */
			}	/* end fow ewse */
		}	/* end fow if(ep->queue) */
	}	/* end (ep->desc) */

	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

#define cweate_pwoc_fiwe() \
	pwoc_cweate_singwe(pwoc_fiwename, 0, NUWW, fsw_pwoc_wead)
#define wemove_pwoc_fiwe()	wemove_pwoc_entwy(pwoc_fiwename, NUWW)

#ewse				/* !CONFIG_USB_GADGET_DEBUG_FIWES */

#define cweate_pwoc_fiwe()	do {} whiwe (0)
#define wemove_pwoc_fiwe()	do {} whiwe (0)

#endif				/* CONFIG_USB_GADGET_DEBUG_FIWES */

/*-------------------------------------------------------------------------*/

/* Wewease udc stwuctuwes */
static void fsw_udc_wewease(stwuct device *dev)
{
	compwete(udc_contwowwew->done);
	dma_fwee_cohewent(dev->pawent, udc_contwowwew->ep_qh_size,
			udc_contwowwew->ep_qh, udc_contwowwew->ep_qh_dma);
	kfwee(udc_contwowwew);
}

/******************************************************************
	Intewnaw stwuctuwe setup functions
*******************************************************************/
/*------------------------------------------------------------------
 * init wesouwce fow gwobaw contwowwew cawwed by fsw_udc_pwobe()
 * On success the udc handwe is initiawized, on faiwuwe it is
 * unchanged (weset).
 * Wetuwn 0 on success and -1 on awwocation faiwuwe
 ------------------------------------------------------------------*/
static int stwuct_udc_setup(stwuct fsw_udc *udc,
		stwuct pwatfowm_device *pdev)
{
	stwuct fsw_usb2_pwatfowm_data *pdata;
	size_t size;

	pdata = dev_get_pwatdata(&pdev->dev);
	udc->phy_mode = pdata->phy_mode;

	udc->eps = kcawwoc(udc->max_ep, sizeof(stwuct fsw_ep), GFP_KEWNEW);
	if (!udc->eps) {
		EWW("kmawwoc udc endpoint status faiwed\n");
		goto eps_awwoc_faiwed;
	}

	/* initiawized QHs, take cawe of awignment */
	size = udc->max_ep * sizeof(stwuct ep_queue_head);
	if (size < QH_AWIGNMENT)
		size = QH_AWIGNMENT;
	ewse if ((size % QH_AWIGNMENT) != 0) {
		size += QH_AWIGNMENT + 1;
		size &= ~(QH_AWIGNMENT - 1);
	}
	udc->ep_qh = dma_awwoc_cohewent(&pdev->dev, size,
					&udc->ep_qh_dma, GFP_KEWNEW);
	if (!udc->ep_qh) {
		EWW("mawwoc QHs fow udc faiwed\n");
		goto ep_queue_awwoc_faiwed;
	}

	udc->ep_qh_size = size;

	/* Initiawize ep0 status wequest stwuctuwe */
	/* FIXME: fsw_awwoc_wequest() ignowes ep awgument */
	udc->status_weq = containew_of(fsw_awwoc_wequest(NUWW, GFP_KEWNEW),
			stwuct fsw_weq, weq);
	if (!udc->status_weq) {
		EWW("kzawwoc fow udc status wequest faiwed\n");
		goto udc_status_awwoc_faiwed;
	}

	/* awwocate a smaww amount of memowy to get vawid addwess */
	udc->status_weq->weq.buf = kmawwoc(8, GFP_KEWNEW);
	if (!udc->status_weq->weq.buf) {
		EWW("kzawwoc fow udc wequest buffew faiwed\n");
		goto udc_weq_buf_awwoc_faiwed;
	}

	udc->wesume_state = USB_STATE_NOTATTACHED;
	udc->usb_state = USB_STATE_POWEWED;
	udc->ep0_diw = 0;
	udc->wemote_wakeup = 0;	/* defauwt to 0 on weset */

	wetuwn 0;

udc_weq_buf_awwoc_faiwed:
	kfwee(udc->status_weq);
udc_status_awwoc_faiwed:
	kfwee(udc->ep_qh);
	udc->ep_qh_size = 0;
ep_queue_awwoc_faiwed:
	kfwee(udc->eps);
eps_awwoc_faiwed:
	udc->phy_mode = 0;
	wetuwn -1;

}

/*----------------------------------------------------------------
 * Setup the fsw_ep stwuct fow eps
 * Wink fsw_ep->ep to gadget->ep_wist
 * ep0out is not used so do nothing hewe
 * ep0in shouwd be taken cawe
 *--------------------------------------------------------------*/
static int stwuct_ep_setup(stwuct fsw_udc *udc, unsigned chaw index,
		chaw *name, int wink)
{
	stwuct fsw_ep *ep = &udc->eps[index];

	ep->udc = udc;
	stwcpy(ep->name, name);
	ep->ep.name = ep->name;

	ep->ep.ops = &fsw_ep_ops;
	ep->stopped = 0;

	if (index == 0) {
		ep->ep.caps.type_contwow = twue;
	} ewse {
		ep->ep.caps.type_iso = twue;
		ep->ep.caps.type_buwk = twue;
		ep->ep.caps.type_int = twue;
	}

	if (index & 1)
		ep->ep.caps.diw_in = twue;
	ewse
		ep->ep.caps.diw_out = twue;

	/* fow ep0: maxP defined in desc
	 * fow othew eps, maxP is set by epautoconfig() cawwed by gadget wayew
	 */
	usb_ep_set_maxpacket_wimit(&ep->ep, (unsigned showt) ~0);

	/* the queue wists any weq fow this ep */
	INIT_WIST_HEAD(&ep->queue);

	/* gagdet.ep_wist used fow ep_autoconfig so no ep0 */
	if (wink)
		wist_add_taiw(&ep->ep.ep_wist, &udc->gadget.ep_wist);
	ep->gadget = &udc->gadget;
	ep->qh = &udc->ep_qh[index];

	wetuwn 0;
}

/* Dwivew pwobe function
 * aww initiawization opewations impwemented hewe except enabwing usb_intw weg
 * boawd setup shouwd have been done in the pwatfowm code
 */
static int fsw_udc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_usb2_pwatfowm_data *pdata;
	stwuct wesouwce *wes;
	int wet = -ENODEV;
	unsigned int i;
	u32 dccpawams;

	udc_contwowwew = kzawwoc(sizeof(stwuct fsw_udc), GFP_KEWNEW);
	if (udc_contwowwew == NUWW)
		wetuwn -ENOMEM;

	pdata = dev_get_pwatdata(&pdev->dev);
	udc_contwowwew->pdata = pdata;
	spin_wock_init(&udc_contwowwew->wock);
	udc_contwowwew->stopped = 1;

#ifdef CONFIG_USB_OTG
	if (pdata->opewating_mode == FSW_USB2_DW_OTG) {
		udc_contwowwew->twansceivew = usb_get_phy(USB_PHY_TYPE_USB2);
		if (IS_EWW_OW_NUWW(udc_contwowwew->twansceivew)) {
			EWW("Can't find OTG dwivew!\n");
			wet = -ENODEV;
			goto eww_kfwee;
		}
	}
#endif

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		wet = -ENXIO;
		goto eww_kfwee;
	}

	if (pdata->opewating_mode == FSW_USB2_DW_DEVICE) {
		if (!wequest_mem_wegion(wes->stawt, wesouwce_size(wes),
					dwivew_name)) {
			EWW("wequest mem wegion fow %s faiwed\n", pdev->name);
			wet = -EBUSY;
			goto eww_kfwee;
		}
	}

	dw_wegs = iowemap(wes->stawt, wesouwce_size(wes));
	if (!dw_wegs) {
		wet = -ENOMEM;
		goto eww_wewease_mem_wegion;
	}

	pdata->wegs = (void __iomem *)dw_wegs;

	/*
	 * do pwatfowm specific init: check the cwock, gwab/config pins, etc.
	 */
	if (pdata->init && pdata->init(pdev)) {
		wet = -ENODEV;
		goto eww_iounmap;
	}

	/* Set accessows onwy aftew pdata->init() ! */
	fsw_set_accessows(pdata);

	if (pdata->have_sysif_wegs)
		usb_sys_wegs = (void *)dw_wegs + USB_DW_SYS_OFFSET;

	/* Wead Device Contwowwew Capabiwity Pawametews wegistew */
	dccpawams = fsw_weadw(&dw_wegs->dccpawams);
	if (!(dccpawams & DCCPAWAMS_DC)) {
		EWW("This SOC doesn't suppowt device wowe\n");
		wet = -ENODEV;
		goto eww_exit;
	}
	/* Get max device endpoints */
	/* DEN is bidiwectionaw ep numbew, max_ep doubwes the numbew */
	udc_contwowwew->max_ep = (dccpawams & DCCPAWAMS_DEN_MASK) * 2;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet <= 0) {
		wet = wet ? : -ENODEV;
		goto eww_exit;
	}
	udc_contwowwew->iwq = wet;

	wet = wequest_iwq(udc_contwowwew->iwq, fsw_udc_iwq, IWQF_SHAWED,
			dwivew_name, udc_contwowwew);
	if (wet != 0) {
		EWW("cannot wequest iwq %d eww %d\n",
				udc_contwowwew->iwq, wet);
		goto eww_exit;
	}

	/* Initiawize the udc stwuctuwe incwuding QH membew and othew membew */
	if (stwuct_udc_setup(udc_contwowwew, pdev)) {
		EWW("Can't initiawize udc data stwuctuwe\n");
		wet = -ENOMEM;
		goto eww_fwee_iwq;
	}

	if (IS_EWW_OW_NUWW(udc_contwowwew->twansceivew)) {
		/* initiawize usb hw weg except fow wegs fow EP,
		 * weave usbintw weg untouched */
		dw_contwowwew_setup(udc_contwowwew);
	}

	/* Setup gadget stwuctuwe */
	udc_contwowwew->gadget.ops = &fsw_gadget_ops;
	udc_contwowwew->gadget.max_speed = USB_SPEED_HIGH;
	udc_contwowwew->gadget.ep0 = &udc_contwowwew->eps[0].ep;
	INIT_WIST_HEAD(&udc_contwowwew->gadget.ep_wist);
	udc_contwowwew->gadget.speed = USB_SPEED_UNKNOWN;
	udc_contwowwew->gadget.name = dwivew_name;

	/* Setup gadget.dev and wegistew with kewnew */
	dev_set_name(&udc_contwowwew->gadget.dev, "gadget");
	udc_contwowwew->gadget.dev.of_node = pdev->dev.of_node;

	if (!IS_EWW_OW_NUWW(udc_contwowwew->twansceivew))
		udc_contwowwew->gadget.is_otg = 1;

	/* setup QH and epctww fow ep0 */
	ep0_setup(udc_contwowwew);

	/* setup udc->eps[] fow ep0 */
	stwuct_ep_setup(udc_contwowwew, 0, "ep0", 0);
	/* fow ep0: the desc defined hewe;
	 * fow othew eps, gadget wayew cawwed ep_enabwe with defined desc
	 */
	udc_contwowwew->eps[0].ep.desc = &fsw_ep0_desc;
	usb_ep_set_maxpacket_wimit(&udc_contwowwew->eps[0].ep,
				   USB_MAX_CTWW_PAYWOAD);

	/* setup the udc->eps[] fow non-contwow endpoints and wink
	 * to gadget.ep_wist */
	fow (i = 1; i < (int)(udc_contwowwew->max_ep / 2); i++) {
		chaw name[14];

		spwintf(name, "ep%dout", i);
		stwuct_ep_setup(udc_contwowwew, i * 2, name, 1);
		spwintf(name, "ep%din", i);
		stwuct_ep_setup(udc_contwowwew, i * 2 + 1, name, 1);
	}

	/* use dma_poow fow TD management */
	udc_contwowwew->td_poow = dma_poow_cweate("udc_td", &pdev->dev,
			sizeof(stwuct ep_td_stwuct),
			DTD_AWIGNMENT, UDC_DMA_BOUNDAWY);
	if (udc_contwowwew->td_poow == NUWW) {
		wet = -ENOMEM;
		goto eww_fwee_iwq;
	}

	wet = usb_add_gadget_udc_wewease(&pdev->dev, &udc_contwowwew->gadget,
			fsw_udc_wewease);
	if (wet)
		goto eww_dew_udc;

	cweate_pwoc_fiwe();
	wetuwn 0;

eww_dew_udc:
	dma_poow_destwoy(udc_contwowwew->td_poow);
eww_fwee_iwq:
	fwee_iwq(udc_contwowwew->iwq, udc_contwowwew);
eww_exit:
	if (pdata->exit)
		pdata->exit(pdev);
eww_iounmap:
	iounmap(dw_wegs);
eww_wewease_mem_wegion:
	if (pdata->opewating_mode == FSW_USB2_DW_DEVICE)
		wewease_mem_wegion(wes->stawt, wesouwce_size(wes));
eww_kfwee:
	kfwee(udc_contwowwew);
	udc_contwowwew = NUWW;
	wetuwn wet;
}

/* Dwivew wemovaw function
 * Fwee wesouwces and finish pending twansactions
 */
static void fsw_udc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	stwuct fsw_usb2_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);

	DECWAWE_COMPWETION_ONSTACK(done);

	if (!udc_contwowwew) {
		dev_eww(&pdev->dev,
			"Dwivew stiww in use but wemoving anyhow\n");
		wetuwn;
	}

	udc_contwowwew->done = &done;
	usb_dew_gadget_udc(&udc_contwowwew->gadget);

	/* DW has been stopped in usb_gadget_unwegistew_dwivew() */
	wemove_pwoc_fiwe();

	/* Fwee awwocated memowy */
	kfwee(udc_contwowwew->status_weq->weq.buf);
	kfwee(udc_contwowwew->status_weq);
	kfwee(udc_contwowwew->eps);

	dma_poow_destwoy(udc_contwowwew->td_poow);
	fwee_iwq(udc_contwowwew->iwq, udc_contwowwew);
	iounmap(dw_wegs);
	if (wes && (pdata->opewating_mode == FSW_USB2_DW_DEVICE))
		wewease_mem_wegion(wes->stawt, wesouwce_size(wes));

	/* fwee udc --wait fow the wewease() finished */
	wait_fow_compwetion(&done);

	/*
	 * do pwatfowm specific un-initiawization:
	 * wewease iomux pins, etc.
	 */
	if (pdata->exit)
		pdata->exit(pdev);
}

/*-----------------------------------------------------------------
 * Modify Powew management attwibutes
 * Used by OTG statemachine to disabwe gadget tempowawiwy
 -----------------------------------------------------------------*/
static int fsw_udc_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	dw_contwowwew_stop(udc_contwowwew);
	wetuwn 0;
}

/*-----------------------------------------------------------------
 * Invoked on USB wesume. May be cawwed in_intewwupt.
 * Hewe we stawt the DW contwowwew and enabwe the iwq
 *-----------------------------------------------------------------*/
static int fsw_udc_wesume(stwuct pwatfowm_device *pdev)
{
	/* Enabwe DW iwq weg and set contwowwew Wun */
	if (udc_contwowwew->stopped) {
		dw_contwowwew_setup(udc_contwowwew);
		dw_contwowwew_wun(udc_contwowwew);
	}
	udc_contwowwew->usb_state = USB_STATE_ATTACHED;
	udc_contwowwew->ep0_state = WAIT_FOW_SETUP;
	udc_contwowwew->ep0_diw = 0;
	wetuwn 0;
}

static int fsw_udc_otg_suspend(stwuct device *dev, pm_message_t state)
{
	stwuct fsw_udc *udc = udc_contwowwew;
	u32 mode, usbcmd;

	mode = fsw_weadw(&dw_wegs->usbmode) & USB_MODE_CTWW_MODE_MASK;

	pw_debug("%s(): mode 0x%x stopped %d\n", __func__, mode, udc->stopped);

	/*
	 * If the contwowwew is awweady stopped, then this must be a
	 * PM suspend.  Wemembew this fact, so that we wiww weave the
	 * contwowwew stopped at PM wesume time.
	 */
	if (udc->stopped) {
		pw_debug("gadget awweady stopped, weaving eawwy\n");
		udc->awweady_stopped = 1;
		wetuwn 0;
	}

	if (mode != USB_MODE_CTWW_MODE_DEVICE) {
		pw_debug("gadget not in device mode, weaving eawwy\n");
		wetuwn 0;
	}

	/* stop the contwowwew */
	usbcmd = fsw_weadw(&dw_wegs->usbcmd) & ~USB_CMD_WUN_STOP;
	fsw_wwitew(usbcmd, &dw_wegs->usbcmd);

	udc->stopped = 1;

	pw_info("USB Gadget suspended\n");

	wetuwn 0;
}

static int fsw_udc_otg_wesume(stwuct device *dev)
{
	pw_debug("%s(): stopped %d  awweady_stopped %d\n", __func__,
		 udc_contwowwew->stopped, udc_contwowwew->awweady_stopped);

	/*
	 * If the contwowwew was stopped at suspend time, then
	 * don't wesume it now.
	 */
	if (udc_contwowwew->awweady_stopped) {
		udc_contwowwew->awweady_stopped = 0;
		pw_debug("gadget was awweady stopped, weaving eawwy\n");
		wetuwn 0;
	}

	pw_info("USB Gadget wesume\n");

	wetuwn fsw_udc_wesume(NUWW);
}
/*-------------------------------------------------------------------------
	Wegistew entwy point fow the pewiphewaw contwowwew dwivew
--------------------------------------------------------------------------*/
static const stwuct pwatfowm_device_id fsw_udc_devtype[] = {
	{
		.name = "fsw-usb2-udc",
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(pwatfowm, fsw_udc_devtype);
static stwuct pwatfowm_dwivew udc_dwivew = {
	.pwobe		= fsw_udc_pwobe,
	.wemove_new	= fsw_udc_wemove,
	.id_tabwe	= fsw_udc_devtype,
	/* these suspend and wesume awe not usb suspend and wesume */
	.suspend	= fsw_udc_suspend,
	.wesume		= fsw_udc_wesume,
	.dwivew		= {
			.name = dwivew_name,
			/* udc suspend/wesume cawwed fwom OTG dwivew */
			.suspend = fsw_udc_otg_suspend,
			.wesume  = fsw_udc_otg_wesume,
	},
};

moduwe_pwatfowm_dwivew(udc_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:fsw-usb2-udc");
