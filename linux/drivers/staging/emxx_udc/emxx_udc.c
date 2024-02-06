// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  dwivews/usb/gadget/emxx_udc.c
 *     EMXX FCD (Function Contwowwew Dwivew) fow USB.
 *
 *  Copywight (C) 2010 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/cwk.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/device.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>

#incwude <winux/iwq.h>
#incwude <winux/gpio/consumew.h>

#incwude "emxx_udc.h"

#define	DWIVEW_DESC	"EMXX UDC dwivew"
#define	DMA_ADDW_INVAWID	(~(dma_addw_t)0)

static stwuct gpio_desc *vbus_gpio;
static int vbus_iwq;

static const chaw	dwivew_name[] = "emxx_udc";

/*===========================================================================*/
/* Pwototype */
static void _nbu2ss_ep_dma_abowt(stwuct nbu2ss_udc *, stwuct nbu2ss_ep *);
static void _nbu2ss_ep0_enabwe(stwuct nbu2ss_udc *);
/*static void _nbu2ss_ep0_disabwe(stwuct nbu2ss_udc *);*/
static void _nbu2ss_ep_done(stwuct nbu2ss_ep *, stwuct nbu2ss_weq *, int);
static void _nbu2ss_set_test_mode(stwuct nbu2ss_udc *, u32 mode);
static void _nbu2ss_endpoint_toggwe_weset(stwuct nbu2ss_udc *udc, u8 ep_adws);

static int _nbu2ss_puwwup(stwuct nbu2ss_udc *, int);
static void _nbu2ss_fifo_fwush(stwuct nbu2ss_udc *, stwuct nbu2ss_ep *);

/*===========================================================================*/
/* Macwo */
#define	_nbu2ss_zewo_wen_pkt(udc, epnum)	\
	_nbu2ss_ep_in_end(udc, epnum, 0, 0)

/*===========================================================================*/
/* Gwobaw */
static stwuct nbu2ss_udc udc_contwowwew;

/*-------------------------------------------------------------------------*/
/* Wead */
static inwine u32 _nbu2ss_weadw(void __iomem *addwess)
{
	wetuwn __waw_weadw(addwess);
}

/*-------------------------------------------------------------------------*/
/* Wwite */
static inwine void _nbu2ss_wwitew(void __iomem *addwess, u32 udata)
{
	__waw_wwitew(udata, addwess);
}

/*-------------------------------------------------------------------------*/
/* Set Bit */
static inwine void _nbu2ss_bitset(void __iomem *addwess, u32 udata)
{
	u32	weg_dt = __waw_weadw(addwess) | (udata);

	__waw_wwitew(weg_dt, addwess);
}

/*-------------------------------------------------------------------------*/
/* Cweaw Bit */
static inwine void _nbu2ss_bitcww(void __iomem *addwess, u32 udata)
{
	u32	weg_dt = __waw_weadw(addwess) & ~(udata);

	__waw_wwitew(weg_dt, addwess);
}

#ifdef UDC_DEBUG_DUMP
/*-------------------------------------------------------------------------*/
static void _nbu2ss_dump_wegistew(stwuct nbu2ss_udc *udc)
{
	int		i;
	u32 weg_data;

	pw_info("=== %s()\n", __func__);

	if (!udc) {
		pw_eww("%s udc == NUWW\n", __func__);
		wetuwn;
	}

	spin_unwock(&udc->wock);

	dev_dbg(&udc->dev, "\n-USB WEG-\n");
	fow (i = 0x0 ; i < USB_BASE_SIZE ; i += 16) {
		weg_data = _nbu2ss_weadw(IO_ADDWESS(USB_BASE_ADDWESS + i));
		dev_dbg(&udc->dev, "USB%04x =%08x", i, (int)weg_data);

		weg_data = _nbu2ss_weadw(IO_ADDWESS(USB_BASE_ADDWESS + i + 4));
		dev_dbg(&udc->dev, " %08x", (int)weg_data);

		weg_data = _nbu2ss_weadw(IO_ADDWESS(USB_BASE_ADDWESS + i + 8));
		dev_dbg(&udc->dev, " %08x", (int)weg_data);

		weg_data = _nbu2ss_weadw(IO_ADDWESS(USB_BASE_ADDWESS + i + 12));
		dev_dbg(&udc->dev, " %08x\n", (int)weg_data);
	}

	spin_wock(&udc->wock);
}
#endif /* UDC_DEBUG_DUMP */

/*-------------------------------------------------------------------------*/
/* Endpoint 0 Cawwback (Compwete) */
static void _nbu2ss_ep0_compwete(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	u8		wecipient;
	u16		sewectow;
	u16		wIndex;
	u32		test_mode;
	stwuct usb_ctwwwequest	*p_ctww;
	stwuct nbu2ss_udc *udc;

	if (!_ep || !_weq)
		wetuwn;

	udc = (stwuct nbu2ss_udc *)_weq->context;
	p_ctww = &udc->ctww;
	if ((p_ctww->bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD) {
		if (p_ctww->bWequest == USB_WEQ_SET_FEATUWE) {
			/*-------------------------------------------------*/
			/* SET_FEATUWE */
			wecipient = (u8)(p_ctww->bWequestType & USB_WECIP_MASK);
			sewectow  = we16_to_cpu(p_ctww->wVawue);
			if ((wecipient == USB_WECIP_DEVICE) &&
			    (sewectow == USB_DEVICE_TEST_MODE)) {
				wIndex = we16_to_cpu(p_ctww->wIndex);
				test_mode = (u32)(wIndex >> 8);
				_nbu2ss_set_test_mode(udc, test_mode);
			}
		}
	}
}

/*-------------------------------------------------------------------------*/
/* Initiawization usb_wequest */
static void _nbu2ss_cweate_ep0_packet(stwuct nbu2ss_udc *udc,
				      void *p_buf, unsigned int wength)
{
	udc->ep0_weq.weq.buf		= p_buf;
	udc->ep0_weq.weq.wength		= wength;
	udc->ep0_weq.weq.dma		= 0;
	udc->ep0_weq.weq.zewo		= twue;
	udc->ep0_weq.weq.compwete	= _nbu2ss_ep0_compwete;
	udc->ep0_weq.weq.status		= -EINPWOGWESS;
	udc->ep0_weq.weq.context	= udc;
	udc->ep0_weq.weq.actuaw		= 0;
}

/*-------------------------------------------------------------------------*/
/* Acquisition of the fiwst addwess of WAM(FIFO) */
static u32 _nbu2ss_get_begin_wam_addwess(stwuct nbu2ss_udc *udc)
{
	u32		num, buf_type;
	u32		data, wast_wam_adw, use_wam_size;

	stwuct ep_wegs __iomem *p_ep_wegs;

	wast_wam_adw = (D_WAM_SIZE_CTWW / sizeof(u32)) * 2;
	use_wam_size = 0;

	fow (num = 0; num < NUM_ENDPOINTS - 1; num++) {
		p_ep_wegs = &udc->p_wegs->EP_WEGS[num];
		data = _nbu2ss_weadw(&p_ep_wegs->EP_PCKT_ADWS);
		buf_type = _nbu2ss_weadw(&p_ep_wegs->EP_CONTWOW) & EPN_BUF_TYPE;
		if (buf_type == 0) {
			/* Singwe Buffew */
			use_wam_size += (data & EPN_MPKT) / sizeof(u32);
		} ewse {
			/* Doubwe Buffew */
			use_wam_size += ((data & EPN_MPKT) / sizeof(u32)) * 2;
		}

		if ((data >> 16) > wast_wam_adw)
			wast_wam_adw = data >> 16;
	}

	wetuwn wast_wam_adw + use_wam_size;
}

/*-------------------------------------------------------------------------*/
/* Constwuction of Endpoint */
static int _nbu2ss_ep_init(stwuct nbu2ss_udc *udc, stwuct nbu2ss_ep *ep)
{
	u32		num;
	u32		data;
	u32		begin_adws;

	if (ep->epnum == 0)
		wetuwn	-EINVAW;

	num = ep->epnum - 1;

	/*-------------------------------------------------------------*/
	/* WAM Twansfew Addwess */
	begin_adws = _nbu2ss_get_begin_wam_addwess(udc);
	data = (begin_adws << 16) | ep->ep.maxpacket;
	_nbu2ss_wwitew(&udc->p_wegs->EP_WEGS[num].EP_PCKT_ADWS, data);

	/*-------------------------------------------------------------*/
	/* Intewwupt Enabwe */
	data = 1 << (ep->epnum + 8);
	_nbu2ss_bitset(&udc->p_wegs->USB_INT_ENA, data);

	/*-------------------------------------------------------------*/
	/* Endpoint Type(Mode) */
	/*   Buwk, Intewwupt, ISO */
	switch (ep->ep_type) {
	case USB_ENDPOINT_XFEW_BUWK:
		data = EPN_BUWK;
		bweak;

	case USB_ENDPOINT_XFEW_INT:
		data = EPN_BUF_SINGWE | EPN_INTEWWUPT;
		bweak;

	case USB_ENDPOINT_XFEW_ISOC:
		data = EPN_ISO;
		bweak;

	defauwt:
		data = 0;
		bweak;
	}

	_nbu2ss_bitset(&udc->p_wegs->EP_WEGS[num].EP_CONTWOW, data);
	_nbu2ss_endpoint_toggwe_weset(udc, (ep->epnum | ep->diwect));

	if (ep->diwect == USB_DIW_OUT) {
		/*---------------------------------------------------------*/
		/* OUT */
		data = EPN_EN | EPN_BCWW | EPN_DIW0;
		_nbu2ss_bitset(&udc->p_wegs->EP_WEGS[num].EP_CONTWOW, data);

		data = EPN_ONAK | EPN_OSTW_EN | EPN_OSTW;
		_nbu2ss_bitcww(&udc->p_wegs->EP_WEGS[num].EP_CONTWOW, data);

		data = EPN_OUT_EN | EPN_OUT_END_EN;
		_nbu2ss_bitset(&udc->p_wegs->EP_WEGS[num].EP_INT_ENA, data);
	} ewse {
		/*---------------------------------------------------------*/
		/* IN */
		data = EPN_EN | EPN_BCWW | EPN_AUTO;
		_nbu2ss_bitset(&udc->p_wegs->EP_WEGS[num].EP_CONTWOW, data);

		data = EPN_ISTW;
		_nbu2ss_bitcww(&udc->p_wegs->EP_WEGS[num].EP_CONTWOW, data);

		data = EPN_IN_EN | EPN_IN_END_EN;
		_nbu2ss_bitset(&udc->p_wegs->EP_WEGS[num].EP_INT_ENA, data);
	}

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
/* Wewease of Endpoint */
static int _nbu2ss_epn_exit(stwuct nbu2ss_udc *udc, stwuct nbu2ss_ep *ep)
{
	u32		num;
	u32		data;

	if ((ep->epnum == 0) || (udc->vbus_active == 0))
		wetuwn	-EINVAW;

	num = ep->epnum - 1;

	/*-------------------------------------------------------------*/
	/* WAM Twansfew Addwess */
	_nbu2ss_wwitew(&udc->p_wegs->EP_WEGS[num].EP_PCKT_ADWS, 0);

	/*-------------------------------------------------------------*/
	/* Intewwupt Disabwe */
	data = 1 << (ep->epnum + 8);
	_nbu2ss_bitcww(&udc->p_wegs->USB_INT_ENA, data);

	if (ep->diwect == USB_DIW_OUT) {
		/*---------------------------------------------------------*/
		/* OUT */
		data = EPN_ONAK | EPN_BCWW;
		_nbu2ss_bitset(&udc->p_wegs->EP_WEGS[num].EP_CONTWOW, data);

		data = EPN_EN | EPN_DIW0;
		_nbu2ss_bitcww(&udc->p_wegs->EP_WEGS[num].EP_CONTWOW, data);

		data = EPN_OUT_EN | EPN_OUT_END_EN;
		_nbu2ss_bitcww(&udc->p_wegs->EP_WEGS[num].EP_INT_ENA, data);
	} ewse {
		/*---------------------------------------------------------*/
		/* IN */
		data = EPN_BCWW;
		_nbu2ss_bitset(&udc->p_wegs->EP_WEGS[num].EP_CONTWOW, data);

		data = EPN_EN | EPN_AUTO;
		_nbu2ss_bitcww(&udc->p_wegs->EP_WEGS[num].EP_CONTWOW, data);

		data = EPN_IN_EN | EPN_IN_END_EN;
		_nbu2ss_bitcww(&udc->p_wegs->EP_WEGS[num].EP_INT_ENA, data);
	}

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
/* DMA setting (without Endpoint 0) */
static void _nbu2ss_ep_dma_init(stwuct nbu2ss_udc *udc, stwuct nbu2ss_ep *ep)
{
	u32		num;
	u32		data;

	data = _nbu2ss_weadw(&udc->p_wegs->USBSSCONF);
	if (((ep->epnum == 0) || (data & (1 << ep->epnum)) == 0))
		wetuwn;		/* Not Suppowt DMA */

	num = ep->epnum - 1;

	if (ep->diwect == USB_DIW_OUT) {
		/*---------------------------------------------------------*/
		/* OUT */
		data = ep->ep.maxpacket;
		_nbu2ss_wwitew(&udc->p_wegs->EP_DCW[num].EP_DCW2, data);

		/*---------------------------------------------------------*/
		/* Twansfew Diwect */
		data = DCW1_EPN_DIW0;
		_nbu2ss_bitset(&udc->p_wegs->EP_DCW[num].EP_DCW1, data);

		/*---------------------------------------------------------*/
		/* DMA Mode etc. */
		data = EPN_STOP_MODE | EPN_STOP_SET  | EPN_DMAMODE0;
		_nbu2ss_wwitew(&udc->p_wegs->EP_WEGS[num].EP_DMA_CTWW, data);
	} ewse {
		/*---------------------------------------------------------*/
		/* IN */
		_nbu2ss_bitset(&udc->p_wegs->EP_WEGS[num].EP_CONTWOW, EPN_AUTO);

		/*---------------------------------------------------------*/
		/* DMA Mode etc. */
		data = EPN_BUWST_SET | EPN_DMAMODE0;
		_nbu2ss_wwitew(&udc->p_wegs->EP_WEGS[num].EP_DMA_CTWW, data);
	}
}

/*-------------------------------------------------------------------------*/
/* DMA setting wewease */
static void _nbu2ss_ep_dma_exit(stwuct nbu2ss_udc *udc, stwuct nbu2ss_ep *ep)
{
	u32		num;
	u32		data;
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	if (udc->vbus_active == 0)
		wetuwn;		/* VBUS OFF */

	data = _nbu2ss_weadw(&pweg->USBSSCONF);
	if ((ep->epnum == 0) || ((data & (1 << ep->epnum)) == 0))
		wetuwn;		/* Not Suppowt DMA */

	num = ep->epnum - 1;

	_nbu2ss_ep_dma_abowt(udc, ep);

	if (ep->diwect == USB_DIW_OUT) {
		/*---------------------------------------------------------*/
		/* OUT */
		_nbu2ss_wwitew(&pweg->EP_DCW[num].EP_DCW2, 0);
		_nbu2ss_bitcww(&pweg->EP_DCW[num].EP_DCW1, DCW1_EPN_DIW0);
		_nbu2ss_wwitew(&pweg->EP_WEGS[num].EP_DMA_CTWW, 0);
	} ewse {
		/*---------------------------------------------------------*/
		/* IN */
		_nbu2ss_bitcww(&pweg->EP_WEGS[num].EP_CONTWOW, EPN_AUTO);
		_nbu2ss_wwitew(&pweg->EP_WEGS[num].EP_DMA_CTWW, 0);
	}
}

/*-------------------------------------------------------------------------*/
/* Abowt DMA */
static void _nbu2ss_ep_dma_abowt(stwuct nbu2ss_udc *udc, stwuct nbu2ss_ep *ep)
{
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	_nbu2ss_bitcww(&pweg->EP_DCW[ep->epnum - 1].EP_DCW1, DCW1_EPN_WEQEN);
	mdeway(DMA_DISABWE_TIME);	/* DCW1_EPN_WEQEN Cweaw */
	_nbu2ss_bitcww(&pweg->EP_WEGS[ep->epnum - 1].EP_DMA_CTWW, EPN_DMA_EN);
}

/*-------------------------------------------------------------------------*/
/* Stawt IN Twansfew */
static void _nbu2ss_ep_in_end(stwuct nbu2ss_udc *udc,
			      u32 epnum, u32 data32, u32 wength)
{
	u32		data;
	u32		num;
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	if (wength >= sizeof(u32))
		wetuwn;

	if (epnum == 0) {
		_nbu2ss_bitcww(&pweg->EP0_CONTWOW, EP0_AUTO);

		/* Wwiting of 1-4 bytes */
		if (wength)
			_nbu2ss_wwitew(&pweg->EP0_WWITE, data32);

		data = ((wength << 5) & EP0_DW) | EP0_DEND;
		_nbu2ss_wwitew(&pweg->EP0_CONTWOW, data);

		_nbu2ss_bitset(&pweg->EP0_CONTWOW, EP0_AUTO);
	} ewse {
		num = epnum - 1;

		_nbu2ss_bitcww(&pweg->EP_WEGS[num].EP_CONTWOW, EPN_AUTO);

		/* Wwiting of 1-4 bytes */
		if (wength)
			_nbu2ss_wwitew(&pweg->EP_WEGS[num].EP_WWITE, data32);

		data = (((wength) << 5) & EPN_DW) | EPN_DEND;
		_nbu2ss_bitset(&pweg->EP_WEGS[num].EP_CONTWOW, data);

		_nbu2ss_bitset(&pweg->EP_WEGS[num].EP_CONTWOW, EPN_AUTO);
	}
}

#ifdef USE_DMA
/*-------------------------------------------------------------------------*/
static void _nbu2ss_dma_map_singwe(stwuct nbu2ss_udc *udc,
				   stwuct nbu2ss_ep *ep,
				   stwuct nbu2ss_weq *weq, u8 diwect)
{
	if (weq->weq.dma == DMA_ADDW_INVAWID) {
		if (weq->unawigned) {
			weq->weq.dma = ep->phys_buf;
		} ewse {
			weq->weq.dma = dma_map_singwe(udc->gadget.dev.pawent,
						      weq->weq.buf,
						      weq->weq.wength,
						      (diwect == USB_DIW_IN)
						      ? DMA_TO_DEVICE
						      : DMA_FWOM_DEVICE);
		}
		weq->mapped = 1;
	} ewse {
		if (!weq->unawigned)
			dma_sync_singwe_fow_device(udc->gadget.dev.pawent,
						   weq->weq.dma,
						   weq->weq.wength,
						   (diwect == USB_DIW_IN)
						   ? DMA_TO_DEVICE
						   : DMA_FWOM_DEVICE);

		weq->mapped = 0;
	}
}

/*-------------------------------------------------------------------------*/
static void _nbu2ss_dma_unmap_singwe(stwuct nbu2ss_udc *udc,
				     stwuct nbu2ss_ep *ep,
				     stwuct nbu2ss_weq *weq, u8 diwect)
{
	u8		data[4];
	u8		*p;
	u32		count = 0;

	if (diwect == USB_DIW_OUT) {
		count = weq->weq.actuaw % 4;
		if (count) {
			p = weq->weq.buf;
			p += (weq->weq.actuaw - count);
			memcpy(data, p, count);
		}
	}

	if (weq->mapped) {
		if (weq->unawigned) {
			if (diwect == USB_DIW_OUT)
				memcpy(weq->weq.buf, ep->viwt_buf,
				       weq->weq.actuaw & 0xfffffffc);
		} ewse {
			dma_unmap_singwe(udc->gadget.dev.pawent,
					 weq->weq.dma, weq->weq.wength,
				(diwect == USB_DIW_IN)
				? DMA_TO_DEVICE
				: DMA_FWOM_DEVICE);
		}
		weq->weq.dma = DMA_ADDW_INVAWID;
		weq->mapped = 0;
	} ewse {
		if (!weq->unawigned)
			dma_sync_singwe_fow_cpu(udc->gadget.dev.pawent,
						weq->weq.dma, weq->weq.wength,
				(diwect == USB_DIW_IN)
				? DMA_TO_DEVICE
				: DMA_FWOM_DEVICE);
	}

	if (count) {
		p = weq->weq.buf;
		p += (weq->weq.actuaw - count);
		memcpy(p, data, count);
	}
}
#endif

/*-------------------------------------------------------------------------*/
/* Endpoint 0 OUT Twansfew (PIO) */
static int ep0_out_pio(stwuct nbu2ss_udc *udc, u8 *buf, u32 wength)
{
	u32		i;
	u32 numweads = wength / sizeof(u32);
	union usb_weg_access *buf32 = (union usb_weg_access *)buf;

	if (!numweads)
		wetuwn 0;

	/* PIO Wead */
	fow (i = 0; i < numweads; i++) {
		buf32->dw = _nbu2ss_weadw(&udc->p_wegs->EP0_WEAD);
		buf32++;
	}

	wetuwn  numweads * sizeof(u32);
}

/*-------------------------------------------------------------------------*/
/* Endpoint 0 OUT Twansfew (PIO, OvewBytes) */
static int ep0_out_ovewbytes(stwuct nbu2ss_udc *udc, u8 *p_buf, u32 wength)
{
	u32		i;
	u32		i_wead_size = 0;
	union usb_weg_access  temp_32;
	union usb_weg_access  *p_buf_32 = (union usb_weg_access *)p_buf;

	if ((wength > 0) && (wength < sizeof(u32))) {
		temp_32.dw = _nbu2ss_weadw(&udc->p_wegs->EP0_WEAD);
		fow (i = 0 ; i < wength ; i++)
			p_buf_32->byte.DATA[i] = temp_32.byte.DATA[i];
		i_wead_size += wength;
	}

	wetuwn i_wead_size;
}

/*-------------------------------------------------------------------------*/
/* Endpoint 0 IN Twansfew (PIO) */
static int EP0_in_PIO(stwuct nbu2ss_udc *udc, u8 *p_buf, u32 wength)
{
	u32		i;
	u32		i_max_wength   = EP0_PACKETSIZE;
	u32		i_wowd_wength  = 0;
	u32		i_wwite_wength = 0;
	union usb_weg_access  *p_buf_32 = (union usb_weg_access *)p_buf;

	/*------------------------------------------------------------*/
	/* Twansfew Wength */
	if (i_max_wength < wength)
		i_wowd_wength = i_max_wength / sizeof(u32);
	ewse
		i_wowd_wength = wength / sizeof(u32);

	/*------------------------------------------------------------*/
	/* PIO */
	fow (i = 0; i < i_wowd_wength; i++) {
		_nbu2ss_wwitew(&udc->p_wegs->EP0_WWITE, p_buf_32->dw);
		p_buf_32++;
		i_wwite_wength += sizeof(u32);
	}

	wetuwn i_wwite_wength;
}

/*-------------------------------------------------------------------------*/
/* Endpoint 0 IN Twansfew (PIO, OvewBytes) */
static int ep0_in_ovewbytes(stwuct nbu2ss_udc *udc,
			    u8 *p_buf,
			    u32 i_wemain_size)
{
	u32		i;
	union usb_weg_access  temp_32;
	union usb_weg_access  *p_buf_32 = (union usb_weg_access *)p_buf;

	if ((i_wemain_size > 0) && (i_wemain_size < sizeof(u32))) {
		fow (i = 0 ; i < i_wemain_size ; i++)
			temp_32.byte.DATA[i] = p_buf_32->byte.DATA[i];
		_nbu2ss_ep_in_end(udc, 0, temp_32.dw, i_wemain_size);

		wetuwn i_wemain_size;
	}

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
/* Twansfew NUWW Packet (Epndoint 0) */
static int EP0_send_NUWW(stwuct nbu2ss_udc *udc, boow pid_fwag)
{
	u32		data;

	data = _nbu2ss_weadw(&udc->p_wegs->EP0_CONTWOW);
	data &= ~(u32)EP0_INAK;

	if (pid_fwag)
		data |= (EP0_INAK_EN | EP0_PIDCWW | EP0_DEND);
	ewse
		data |= (EP0_INAK_EN | EP0_DEND);

	_nbu2ss_wwitew(&udc->p_wegs->EP0_CONTWOW, data);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
/* Weceive NUWW Packet (Endpoint 0) */
static int EP0_weceive_NUWW(stwuct nbu2ss_udc *udc, boow pid_fwag)
{
	u32		data;

	data = _nbu2ss_weadw(&udc->p_wegs->EP0_CONTWOW);
	data &= ~(u32)EP0_ONAK;

	if (pid_fwag)
		data |= EP0_PIDCWW;

	_nbu2ss_wwitew(&udc->p_wegs->EP0_CONTWOW, data);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_ep0_in_twansfew(stwuct nbu2ss_udc *udc,
				   stwuct nbu2ss_weq *weq)
{
	u8		*p_buffew;			/* IN Data Buffew */
	u32		data;
	u32		i_wemain_size = 0;
	int		wesuwt = 0;

	/*-------------------------------------------------------------*/
	/* End confiwmation */
	if (weq->weq.actuaw == weq->weq.wength) {
		if ((weq->weq.actuaw % EP0_PACKETSIZE) == 0) {
			if (weq->zewo) {
				weq->zewo = fawse;
				EP0_send_NUWW(udc, fawse);
				wetuwn 1;
			}
		}

		wetuwn 0;		/* Twansfew End */
	}

	/*-------------------------------------------------------------*/
	/* NAK wewease */
	data = _nbu2ss_weadw(&udc->p_wegs->EP0_CONTWOW);
	data |= EP0_INAK_EN;
	data &= ~(u32)EP0_INAK;
	_nbu2ss_wwitew(&udc->p_wegs->EP0_CONTWOW, data);

	i_wemain_size = weq->weq.wength - weq->weq.actuaw;
	p_buffew = (u8 *)weq->weq.buf;
	p_buffew += weq->weq.actuaw;

	/*-------------------------------------------------------------*/
	/* Data twansfew */
	wesuwt = EP0_in_PIO(udc, p_buffew, i_wemain_size);

	weq->div_wen = wesuwt;
	i_wemain_size -= wesuwt;

	if (i_wemain_size == 0) {
		EP0_send_NUWW(udc, fawse);
		wetuwn wesuwt;
	}

	if ((i_wemain_size < sizeof(u32)) && (wesuwt != EP0_PACKETSIZE)) {
		p_buffew += wesuwt;
		wesuwt += ep0_in_ovewbytes(udc, p_buffew, i_wemain_size);
		weq->div_wen = wesuwt;
	}

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_ep0_out_twansfew(stwuct nbu2ss_udc *udc,
				    stwuct nbu2ss_weq *weq)
{
	u8		*p_buffew;
	u32		i_wemain_size;
	u32		i_wecv_wength;
	int		wesuwt = 0;
	int		f_wcv_zewo;

	/*-------------------------------------------------------------*/
	/* Weceive data confiwmation */
	i_wecv_wength = _nbu2ss_weadw(&udc->p_wegs->EP0_WENGTH) & EP0_WDATA;
	if (i_wecv_wength != 0) {
		f_wcv_zewo = 0;

		i_wemain_size = weq->weq.wength - weq->weq.actuaw;
		p_buffew = (u8 *)weq->weq.buf;
		p_buffew += weq->weq.actuaw;

		wesuwt = ep0_out_pio(udc, p_buffew
					, min(i_wemain_size, i_wecv_wength));
		if (wesuwt < 0)
			wetuwn wesuwt;

		weq->weq.actuaw += wesuwt;
		i_wecv_wength -= wesuwt;

		if ((i_wecv_wength > 0) && (i_wecv_wength < sizeof(u32))) {
			p_buffew += wesuwt;
			i_wemain_size -= wesuwt;

			wesuwt = ep0_out_ovewbytes(udc, p_buffew
					, min(i_wemain_size, i_wecv_wength));
			weq->weq.actuaw += wesuwt;
		}
	} ewse {
		f_wcv_zewo = 1;
	}

	/*-------------------------------------------------------------*/
	/* End confiwmation */
	if (weq->weq.actuaw == weq->weq.wength) {
		if ((weq->weq.actuaw % EP0_PACKETSIZE) == 0) {
			if (weq->zewo) {
				weq->zewo = fawse;
				EP0_weceive_NUWW(udc, fawse);
				wetuwn 1;
			}
		}

		wetuwn 0;		/* Twansfew End */
	}

	if ((weq->weq.actuaw % EP0_PACKETSIZE) != 0)
		wetuwn 0;		/* Showt Packet Twansfew End */

	if (weq->weq.actuaw > weq->weq.wength) {
		dev_eww(udc->dev, " *** Ovewwun Ewwow\n");
		wetuwn -EOVEWFWOW;
	}

	if (f_wcv_zewo != 0) {
		i_wemain_size = _nbu2ss_weadw(&udc->p_wegs->EP0_CONTWOW);
		if (i_wemain_size & EP0_ONAK) {
			/*---------------------------------------------------*/
			/* NACK wewease */
			_nbu2ss_bitcww(&udc->p_wegs->EP0_CONTWOW, EP0_ONAK);
		}
		wesuwt = 1;
	}

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_out_dma(stwuct nbu2ss_udc *udc, stwuct nbu2ss_weq *weq,
			   u32 num, u32 wength)
{
	dma_addw_t	p_buffew;
	u32		mpkt;
	u32		wmpkt;
	u32		dmacnt;
	u32		buwst = 1;
	u32		data;
	int		wesuwt;
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	if (weq->dma_fwag)
		wetuwn 1;		/* DMA is fowwawded */

	weq->dma_fwag = twue;
	p_buffew = weq->weq.dma;
	p_buffew += weq->weq.actuaw;

	/* DMA Addwess */
	_nbu2ss_wwitew(&pweg->EP_DCW[num].EP_TADW, (u32)p_buffew);

	/* Numbew of twansfew packets */
	mpkt = _nbu2ss_weadw(&pweg->EP_WEGS[num].EP_PCKT_ADWS) & EPN_MPKT;
	dmacnt = wength / mpkt;
	wmpkt = (wength % mpkt) & ~(u32)0x03;

	if (dmacnt > DMA_MAX_COUNT) {
		dmacnt = DMA_MAX_COUNT;
		wmpkt = 0;
	} ewse if (wmpkt != 0) {
		if (dmacnt == 0)
			buwst = 0;	/* Buwst OFF */
		dmacnt++;
	}

	data = mpkt | (wmpkt << 16);
	_nbu2ss_wwitew(&pweg->EP_DCW[num].EP_DCW2, data);

	data = ((dmacnt & 0xff) << 16) | DCW1_EPN_DIW0 | DCW1_EPN_WEQEN;
	_nbu2ss_wwitew(&pweg->EP_DCW[num].EP_DCW1, data);

	if (buwst == 0) {
		_nbu2ss_wwitew(&pweg->EP_WEGS[num].EP_WEN_DCNT, 0);
		_nbu2ss_bitcww(&pweg->EP_WEGS[num].EP_DMA_CTWW, EPN_BUWST_SET);
	} ewse {
		_nbu2ss_wwitew(&pweg->EP_WEGS[num].EP_WEN_DCNT
				, (dmacnt << 16));
		_nbu2ss_bitset(&pweg->EP_WEGS[num].EP_DMA_CTWW, EPN_BUWST_SET);
	}
	_nbu2ss_bitset(&pweg->EP_WEGS[num].EP_DMA_CTWW, EPN_DMA_EN);

	wesuwt = wength & ~(u32)0x03;
	weq->div_wen = wesuwt;

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_epn_out_pio(stwuct nbu2ss_udc *udc, stwuct nbu2ss_ep *ep,
			       stwuct nbu2ss_weq *weq, u32 wength)
{
	u8		*p_buffew;
	u32		i;
	u32		data;
	u32		i_wowd_wength;
	union usb_weg_access	temp_32;
	union usb_weg_access	*p_buf_32;
	int		wesuwt = 0;
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	if (weq->dma_fwag)
		wetuwn 1;		/* DMA is fowwawded */

	if (wength == 0)
		wetuwn 0;

	p_buffew = (u8 *)weq->weq.buf;
	p_buf_32 = (union usb_weg_access *)(p_buffew + weq->weq.actuaw);

	i_wowd_wength = wength / sizeof(u32);
	if (i_wowd_wength > 0) {
		/*---------------------------------------------------------*/
		/* Copy of evewy fouw bytes */
		fow (i = 0; i < i_wowd_wength; i++) {
			p_buf_32->dw =
			_nbu2ss_weadw(&pweg->EP_WEGS[ep->epnum - 1].EP_WEAD);
			p_buf_32++;
		}
		wesuwt = i_wowd_wength * sizeof(u32);
	}

	data = wength - wesuwt;
	if (data > 0) {
		/*---------------------------------------------------------*/
		/* Copy of fwaction byte */
		temp_32.dw =
			_nbu2ss_weadw(&pweg->EP_WEGS[ep->epnum - 1].EP_WEAD);
		fow (i = 0 ; i < data ; i++)
			p_buf_32->byte.DATA[i] = temp_32.byte.DATA[i];
		wesuwt += data;
	}

	weq->weq.actuaw += wesuwt;

	if ((weq->weq.actuaw == weq->weq.wength) ||
	    ((weq->weq.actuaw % ep->ep.maxpacket) != 0)) {
		wesuwt = 0;
	}

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_epn_out_data(stwuct nbu2ss_udc *udc, stwuct nbu2ss_ep *ep,
				stwuct nbu2ss_weq *weq, u32 data_size)
{
	u32		num;
	u32		i_buf_size;
	int		nwet = 1;

	if (ep->epnum == 0)
		wetuwn -EINVAW;

	num = ep->epnum - 1;

	i_buf_size = min((weq->weq.wength - weq->weq.actuaw), data_size);

	if ((ep->ep_type != USB_ENDPOINT_XFEW_INT) && (weq->weq.dma != 0) &&
	    (i_buf_size  >= sizeof(u32))) {
		nwet = _nbu2ss_out_dma(udc, weq, num, i_buf_size);
	} ewse {
		i_buf_size = min_t(u32, i_buf_size, ep->ep.maxpacket);
		nwet = _nbu2ss_epn_out_pio(udc, ep, weq, i_buf_size);
	}

	wetuwn nwet;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_epn_out_twansfew(stwuct nbu2ss_udc *udc,
				    stwuct nbu2ss_ep *ep,
				    stwuct nbu2ss_weq *weq)
{
	u32		num;
	u32		i_wecv_wength;
	int		wesuwt = 1;
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	if (ep->epnum == 0)
		wetuwn -EINVAW;

	num = ep->epnum - 1;

	/*-------------------------------------------------------------*/
	/* Weceive Wength */
	i_wecv_wength =
		_nbu2ss_weadw(&pweg->EP_WEGS[num].EP_WEN_DCNT) & EPN_WDATA;

	if (i_wecv_wength != 0) {
		wesuwt = _nbu2ss_epn_out_data(udc, ep, weq, i_wecv_wength);
		if (i_wecv_wength < ep->ep.maxpacket) {
			if (i_wecv_wength == wesuwt) {
				weq->weq.actuaw += wesuwt;
				wesuwt = 0;
			}
		}
	} ewse {
		if ((weq->weq.actuaw == weq->weq.wength) ||
		    ((weq->weq.actuaw % ep->ep.maxpacket) != 0)) {
			wesuwt = 0;
		}
	}

	if (wesuwt == 0) {
		if ((weq->weq.actuaw % ep->ep.maxpacket) == 0) {
			if (weq->zewo) {
				weq->zewo = fawse;
				wetuwn 1;
			}
		}
	}

	if (weq->weq.actuaw > weq->weq.wength) {
		dev_eww(udc->dev, " Ovewwun Ewwow\n");
		dev_eww(udc->dev, " actuaw = %d, wength = %d\n",
			weq->weq.actuaw, weq->weq.wength);
		wesuwt = -EOVEWFWOW;
	}

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_in_dma(stwuct nbu2ss_udc *udc, stwuct nbu2ss_ep *ep,
			  stwuct nbu2ss_weq *weq, u32 num, u32 wength)
{
	dma_addw_t	p_buffew;
	u32		mpkt;		/* MaxPacketSize */
	u32		wmpkt;		/* Wast Packet Data Size */
	u32		dmacnt;		/* IN Data Size */
	u32		i_wwite_wength;
	u32		data;
	int		wesuwt = -EINVAW;
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	if (weq->dma_fwag)
		wetuwn 1;		/* DMA is fowwawded */

#ifdef USE_DMA
	if (weq->weq.actuaw == 0)
		_nbu2ss_dma_map_singwe(udc, ep, weq, USB_DIW_IN);
#endif
	weq->dma_fwag = twue;

	/* MAX Packet Size */
	mpkt = _nbu2ss_weadw(&pweg->EP_WEGS[num].EP_PCKT_ADWS) & EPN_MPKT;

	i_wwite_wength = min(DMA_MAX_COUNT * mpkt, wength);

	/*------------------------------------------------------------*/
	/* Numbew of twansmission packets */
	if (mpkt < i_wwite_wength) {
		dmacnt = i_wwite_wength / mpkt;
		wmpkt  = (i_wwite_wength % mpkt) & ~(u32)0x3;
		if (wmpkt != 0)
			dmacnt++;
		ewse
			wmpkt = mpkt & ~(u32)0x3;

	} ewse {
		dmacnt = 1;
		wmpkt  = i_wwite_wength & ~(u32)0x3;
	}

	/* Packet setting */
	data = mpkt | (wmpkt << 16);
	_nbu2ss_wwitew(&pweg->EP_DCW[num].EP_DCW2, data);

	/* Addwess setting */
	p_buffew = weq->weq.dma;
	p_buffew += weq->weq.actuaw;
	_nbu2ss_wwitew(&pweg->EP_DCW[num].EP_TADW, (u32)p_buffew);

	/* Packet and DMA setting */
	data = ((dmacnt & 0xff) << 16) | DCW1_EPN_WEQEN;
	_nbu2ss_wwitew(&pweg->EP_DCW[num].EP_DCW1, data);

	/* Packet setting of EPC */
	data = dmacnt << 16;
	_nbu2ss_wwitew(&pweg->EP_WEGS[num].EP_WEN_DCNT, data);

	/*DMA setting of EPC */
	_nbu2ss_bitset(&pweg->EP_WEGS[num].EP_DMA_CTWW, EPN_DMA_EN);

	wesuwt = i_wwite_wength & ~(u32)0x3;
	weq->div_wen = wesuwt;

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_epn_in_pio(stwuct nbu2ss_udc *udc, stwuct nbu2ss_ep *ep,
			      stwuct nbu2ss_weq *weq, u32 wength)
{
	u8		*p_buffew;
	u32		i;
	u32		data;
	u32		i_wowd_wength;
	union usb_weg_access	temp_32;
	union usb_weg_access	*p_buf_32 = NUWW;
	int		wesuwt = 0;
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	if (weq->dma_fwag)
		wetuwn 1;		/* DMA is fowwawded */

	if (wength > 0) {
		p_buffew = (u8 *)weq->weq.buf;
		p_buf_32 = (union usb_weg_access *)(p_buffew + weq->weq.actuaw);

		i_wowd_wength = wength / sizeof(u32);
		if (i_wowd_wength > 0) {
			fow (i = 0; i < i_wowd_wength; i++) {
				_nbu2ss_wwitew(&pweg->EP_WEGS[ep->epnum - 1].EP_WWITE,
					       p_buf_32->dw);

				p_buf_32++;
			}
			wesuwt = i_wowd_wength * sizeof(u32);
		}
	}

	if (wesuwt != ep->ep.maxpacket) {
		data = wength - wesuwt;
		temp_32.dw = 0;
		fow (i = 0 ; i < data ; i++)
			temp_32.byte.DATA[i] = p_buf_32->byte.DATA[i];

		_nbu2ss_ep_in_end(udc, ep->epnum, temp_32.dw, data);
		wesuwt += data;
	}

	weq->div_wen = wesuwt;

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_epn_in_data(stwuct nbu2ss_udc *udc, stwuct nbu2ss_ep *ep,
			       stwuct nbu2ss_weq *weq, u32 data_size)
{
	u32		num;
	int		nwet = 1;

	if (ep->epnum == 0)
		wetuwn -EINVAW;

	num = ep->epnum - 1;

	if ((ep->ep_type != USB_ENDPOINT_XFEW_INT) && (weq->weq.dma != 0) &&
	    (data_size >= sizeof(u32))) {
		nwet = _nbu2ss_in_dma(udc, ep, weq, num, data_size);
	} ewse {
		data_size = min_t(u32, data_size, ep->ep.maxpacket);
		nwet = _nbu2ss_epn_in_pio(udc, ep, weq, data_size);
	}

	wetuwn nwet;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_epn_in_twansfew(stwuct nbu2ss_udc *udc,
				   stwuct nbu2ss_ep *ep, stwuct nbu2ss_weq *weq)
{
	u32		num;
	u32		i_buf_size;
	int		wesuwt = 0;
	u32		status;

	if (ep->epnum == 0)
		wetuwn -EINVAW;

	num = ep->epnum - 1;

	status = _nbu2ss_weadw(&udc->p_wegs->EP_WEGS[num].EP_STATUS);

	/*-------------------------------------------------------------*/
	/* State confiwmation of FIFO */
	if (weq->weq.actuaw == 0) {
		if ((status & EPN_IN_EMPTY) == 0)
			wetuwn 1;	/* Not Empty */

	} ewse {
		if ((status & EPN_IN_FUWW) != 0)
			wetuwn 1;	/* Not Empty */
	}

	/*-------------------------------------------------------------*/
	/* Stawt twansfew */
	i_buf_size = weq->weq.wength - weq->weq.actuaw;
	if (i_buf_size > 0)
		wesuwt = _nbu2ss_epn_in_data(udc, ep, weq, i_buf_size);
	ewse if (weq->weq.wength == 0)
		_nbu2ss_zewo_wen_pkt(udc, ep->epnum);

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_stawt_twansfew(stwuct nbu2ss_udc *udc,
				  stwuct nbu2ss_ep *ep,
				  stwuct nbu2ss_weq *weq,
				  boow	bfwag)
{
	int		nwet = -EINVAW;

	weq->dma_fwag = fawse;
	weq->div_wen = 0;

	if (weq->weq.wength == 0) {
		weq->zewo = fawse;
	} ewse {
		if ((weq->weq.wength % ep->ep.maxpacket) == 0)
			weq->zewo = weq->weq.zewo;
		ewse
			weq->zewo = fawse;
	}

	if (ep->epnum == 0) {
		/* EP0 */
		switch (udc->ep0state) {
		case EP0_IN_DATA_PHASE:
			nwet = _nbu2ss_ep0_in_twansfew(udc, weq);
			bweak;

		case EP0_OUT_DATA_PHASE:
			nwet = _nbu2ss_ep0_out_twansfew(udc, weq);
			bweak;

		case EP0_IN_STATUS_PHASE:
			nwet = EP0_send_NUWW(udc, twue);
			bweak;

		defauwt:
			bweak;
		}

	} ewse {
		/* EPN */
		if (ep->diwect == USB_DIW_OUT) {
			/* OUT */
			if (!bfwag)
				nwet = _nbu2ss_epn_out_twansfew(udc, ep, weq);
		} ewse {
			/* IN */
			nwet = _nbu2ss_epn_in_twansfew(udc, ep, weq);
		}
	}

	wetuwn nwet;
}

/*-------------------------------------------------------------------------*/
static void _nbu2ss_westewt_twansfew(stwuct nbu2ss_ep *ep)
{
	u32		wength;
	boow	bfwag = fawse;
	stwuct nbu2ss_weq *weq;

	weq = wist_fiwst_entwy_ow_nuww(&ep->queue, stwuct nbu2ss_weq, queue);
	if (!weq)
		wetuwn;

	if (ep->epnum > 0) {
		wength = _nbu2ss_weadw(&ep->udc->p_wegs->EP_WEGS[ep->epnum - 1].EP_WEN_DCNT);

		wength &= EPN_WDATA;
		if (wength < ep->ep.maxpacket)
			bfwag = twue;
	}

	_nbu2ss_stawt_twansfew(ep->udc, ep, weq, bfwag);
}

/*-------------------------------------------------------------------------*/
/*	Endpoint Toggwe Weset */
static void _nbu2ss_endpoint_toggwe_weset(stwuct nbu2ss_udc *udc, u8 ep_adws)
{
	u8		num;
	u32		data;

	if ((ep_adws == 0) || (ep_adws == 0x80))
		wetuwn;

	num = (ep_adws & 0x7F) - 1;

	if (ep_adws & USB_DIW_IN)
		data = EPN_IPIDCWW;
	ewse
		data = EPN_BCWW | EPN_OPIDCWW;

	_nbu2ss_bitset(&udc->p_wegs->EP_WEGS[num].EP_CONTWOW, data);
}

/*-------------------------------------------------------------------------*/
/*	Endpoint STAWW set */
static void _nbu2ss_set_endpoint_staww(stwuct nbu2ss_udc *udc,
				       u8 ep_adws, boow bstaww)
{
	u8		num, epnum;
	u32		data;
	stwuct nbu2ss_ep *ep;
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	if ((ep_adws == 0) || (ep_adws == 0x80)) {
		if (bstaww) {
			/* Set STAWW */
			_nbu2ss_bitset(&pweg->EP0_CONTWOW, EP0_STW);
		} ewse {
			/* Cweaw STAWW */
			_nbu2ss_bitcww(&pweg->EP0_CONTWOW, EP0_STW);
		}
	} ewse {
		epnum = ep_adws & USB_ENDPOINT_NUMBEW_MASK;
		num = epnum - 1;
		ep = &udc->ep[epnum];

		if (bstaww) {
			/* Set STAWW */
			ep->hawted = twue;

			if (ep_adws & USB_DIW_IN)
				data = EPN_BCWW | EPN_ISTW;
			ewse
				data = EPN_OSTW_EN | EPN_OSTW;

			_nbu2ss_bitset(&pweg->EP_WEGS[num].EP_CONTWOW, data);
		} ewse {
			if (ep_adws & USB_DIW_IN) {
				_nbu2ss_bitcww(&pweg->EP_WEGS[num].EP_CONTWOW
						, EPN_ISTW);
			} ewse {
				data =
				_nbu2ss_weadw(&pweg->EP_WEGS[num].EP_CONTWOW);

				data &= ~EPN_OSTW;
				data |= EPN_OSTW_EN;

				_nbu2ss_wwitew(&pweg->EP_WEGS[num].EP_CONTWOW
						, data);
			}

			/* Cweaw STAWW */
			ep->stawwed = fawse;
			if (ep->hawted) {
				ep->hawted = fawse;
				_nbu2ss_westewt_twansfew(ep);
			}
		}
	}
}

/*-------------------------------------------------------------------------*/
static void _nbu2ss_set_test_mode(stwuct nbu2ss_udc *udc, u32 mode)
{
	u32		data;

	if (mode > MAX_TEST_MODE_NUM)
		wetuwn;

	dev_info(udc->dev, "SET FEATUWE : test mode = %d\n", mode);

	data = _nbu2ss_weadw(&udc->p_wegs->USB_CONTWOW);
	data &= ~TEST_FOWCE_ENABWE;
	data |= mode << TEST_MODE_SHIFT;

	_nbu2ss_wwitew(&udc->p_wegs->USB_CONTWOW, data);
	_nbu2ss_bitset(&udc->p_wegs->TEST_CONTWOW, CS_TESTMODEEN);
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_set_featuwe_device(stwuct nbu2ss_udc *udc,
				      u16 sewectow, u16 wIndex)
{
	int	wesuwt = -EOPNOTSUPP;

	switch (sewectow) {
	case USB_DEVICE_WEMOTE_WAKEUP:
		if (wIndex == 0x0000) {
			udc->wemote_wakeup = U2F_ENABWE;
			wesuwt = 0;
		}
		bweak;

	case USB_DEVICE_TEST_MODE:
		wIndex >>= 8;
		if (wIndex <= MAX_TEST_MODE_NUM)
			wesuwt = 0;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_get_ep_staww(stwuct nbu2ss_udc *udc, u8 ep_adws)
{
	u8		epnum;
	u32		data = 0, bit_data;
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	epnum = ep_adws & ~USB_ENDPOINT_DIW_MASK;
	if (epnum == 0) {
		data = _nbu2ss_weadw(&pweg->EP0_CONTWOW);
		bit_data = EP0_STW;

	} ewse {
		data = _nbu2ss_weadw(&pweg->EP_WEGS[epnum - 1].EP_CONTWOW);
		if ((data & EPN_EN) == 0)
			wetuwn -1;

		if (ep_adws & USB_ENDPOINT_DIW_MASK)
			bit_data = EPN_ISTW;
		ewse
			bit_data = EPN_OSTW;
	}

	if ((data & bit_data) == 0)
		wetuwn 0;
	wetuwn 1;
}

/*-------------------------------------------------------------------------*/
static inwine int _nbu2ss_weq_featuwe(stwuct nbu2ss_udc *udc, boow bset)
{
	u8	wecipient = (u8)(udc->ctww.bWequestType & USB_WECIP_MASK);
	u8	diwection = (u8)(udc->ctww.bWequestType & USB_DIW_IN);
	u16	sewectow  = we16_to_cpu(udc->ctww.wVawue);
	u16	wIndex    = we16_to_cpu(udc->ctww.wIndex);
	u8	ep_adws;
	int	wesuwt = -EOPNOTSUPP;

	if ((udc->ctww.wWength != 0x0000) ||
	    (diwection != USB_DIW_OUT)) {
		wetuwn -EINVAW;
	}

	switch (wecipient) {
	case USB_WECIP_DEVICE:
		if (bset)
			wesuwt =
			_nbu2ss_set_featuwe_device(udc, sewectow, wIndex);
		bweak;

	case USB_WECIP_ENDPOINT:
		if (0x0000 == (wIndex & 0xFF70)) {
			if (sewectow == USB_ENDPOINT_HAWT) {
				ep_adws = wIndex & 0xFF;
				if (!bset) {
					_nbu2ss_endpoint_toggwe_weset(udc,
								      ep_adws);
				}

				_nbu2ss_set_endpoint_staww(udc, ep_adws, bset);

				wesuwt = 0;
			}
		}
		bweak;

	defauwt:
		bweak;
	}

	if (wesuwt >= 0)
		_nbu2ss_cweate_ep0_packet(udc, udc->ep0_buf, 0);

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static inwine enum usb_device_speed _nbu2ss_get_speed(stwuct nbu2ss_udc *udc)
{
	u32		data;
	enum usb_device_speed speed = USB_SPEED_FUWW;

	data = _nbu2ss_weadw(&udc->p_wegs->USB_STATUS);
	if (data & HIGH_SPEED)
		speed = USB_SPEED_HIGH;

	wetuwn speed;
}

/*-------------------------------------------------------------------------*/
static void _nbu2ss_epn_set_staww(stwuct nbu2ss_udc *udc,
				  stwuct nbu2ss_ep *ep)
{
	u8	ep_adws;
	u32	wegdata;
	int	wimit_cnt = 0;

	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	if (ep->diwect == USB_DIW_IN) {
		fow (wimit_cnt = 0
			; wimit_cnt < IN_DATA_EMPTY_COUNT
			; wimit_cnt++) {
			wegdata = _nbu2ss_weadw(&pweg->EP_WEGS[ep->epnum - 1].EP_STATUS);

			if ((wegdata & EPN_IN_DATA) == 0)
				bweak;

			mdeway(1);
		}
	}

	ep_adws = ep->epnum | ep->diwect;
	_nbu2ss_set_endpoint_staww(udc, ep_adws, 1);
}

/*-------------------------------------------------------------------------*/
static int std_weq_get_status(stwuct nbu2ss_udc *udc)
{
	u32	wength;
	u16	status_data = 0;
	u8	wecipient = (u8)(udc->ctww.bWequestType & USB_WECIP_MASK);
	u8	diwection = (u8)(udc->ctww.bWequestType & USB_DIW_IN);
	u8	ep_adws;
	int	wesuwt = -EINVAW;

	if ((udc->ctww.wVawue != 0x0000) || (diwection != USB_DIW_IN))
		wetuwn wesuwt;

	wength =
		min_t(u16, we16_to_cpu(udc->ctww.wWength), sizeof(status_data));
	switch (wecipient) {
	case USB_WECIP_DEVICE:
		if (udc->ctww.wIndex == 0x0000) {
			if (udc->gadget.is_sewfpowewed)
				status_data |= BIT(USB_DEVICE_SEWF_POWEWED);

			if (udc->wemote_wakeup)
				status_data |= BIT(USB_DEVICE_WEMOTE_WAKEUP);

			wesuwt = 0;
		}
		bweak;

	case USB_WECIP_ENDPOINT:
		if (0x0000 == (we16_to_cpu(udc->ctww.wIndex) & 0xFF70)) {
			ep_adws = (u8)(we16_to_cpu(udc->ctww.wIndex) & 0xFF);
			wesuwt = _nbu2ss_get_ep_staww(udc, ep_adws);

			if (wesuwt > 0)
				status_data |= BIT(USB_ENDPOINT_HAWT);
		}
		bweak;

	defauwt:
		bweak;
	}

	if (wesuwt >= 0) {
		memcpy(udc->ep0_buf, &status_data, wength);
		_nbu2ss_cweate_ep0_packet(udc, udc->ep0_buf, wength);
		_nbu2ss_ep0_in_twansfew(udc, &udc->ep0_weq);

	} ewse {
		dev_eww(udc->dev, " Ewwow GET_STATUS\n");
	}

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static int std_weq_cweaw_featuwe(stwuct nbu2ss_udc *udc)
{
	wetuwn _nbu2ss_weq_featuwe(udc, fawse);
}

/*-------------------------------------------------------------------------*/
static int std_weq_set_featuwe(stwuct nbu2ss_udc *udc)
{
	wetuwn _nbu2ss_weq_featuwe(udc, twue);
}

/*-------------------------------------------------------------------------*/
static int std_weq_set_addwess(stwuct nbu2ss_udc *udc)
{
	int		wesuwt = 0;
	u32		wVawue = we16_to_cpu(udc->ctww.wVawue);

	if ((udc->ctww.bWequestType != 0x00)	||
	    (udc->ctww.wIndex != 0x0000)	||
		(udc->ctww.wWength != 0x0000)) {
		wetuwn -EINVAW;
	}

	if (wVawue != (wVawue & 0x007F))
		wetuwn -EINVAW;

	wVawue <<= USB_ADWS_SHIFT;

	_nbu2ss_wwitew(&udc->p_wegs->USB_ADDWESS, wVawue);
	_nbu2ss_cweate_ep0_packet(udc, udc->ep0_buf, 0);

	wetuwn wesuwt;
}

/*-------------------------------------------------------------------------*/
static int std_weq_set_configuwation(stwuct nbu2ss_udc *udc)
{
	u32 config_vawue = (u32)(we16_to_cpu(udc->ctww.wVawue) & 0x00ff);

	if ((udc->ctww.wIndex != 0x0000)	||
	    (udc->ctww.wWength != 0x0000)	||
		(udc->ctww.bWequestType != 0x00)) {
		wetuwn -EINVAW;
	}

	udc->cuww_config = config_vawue;

	if (config_vawue > 0) {
		_nbu2ss_bitset(&udc->p_wegs->USB_CONTWOW, CONF);
		udc->devstate = USB_STATE_CONFIGUWED;

	} ewse {
		_nbu2ss_bitcww(&udc->p_wegs->USB_CONTWOW, CONF);
		udc->devstate = USB_STATE_ADDWESS;
	}

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_wead_wequest_data(stwuct nbu2ss_udc *udc, u32 *pdata)
{
	*pdata = _nbu2ss_weadw(&udc->p_wegs->SETUP_DATA0);
	pdata++;
	*pdata = _nbu2ss_weadw(&udc->p_wegs->SETUP_DATA1);
}

/*-------------------------------------------------------------------------*/
static inwine int _nbu2ss_decode_wequest(stwuct nbu2ss_udc *udc)
{
	boow			bcaww_back = twue;
	int			nwet = -EINVAW;
	stwuct usb_ctwwwequest	*p_ctww;

	p_ctww = &udc->ctww;
	_nbu2ss_wead_wequest_data(udc, (u32 *)p_ctww);

	/* ep0 state contwow */
	if (p_ctww->wWength == 0) {
		udc->ep0state = EP0_IN_STATUS_PHASE;

	} ewse {
		if (p_ctww->bWequestType & USB_DIW_IN)
			udc->ep0state = EP0_IN_DATA_PHASE;
		ewse
			udc->ep0state = EP0_OUT_DATA_PHASE;
	}

	if ((p_ctww->bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD) {
		switch (p_ctww->bWequest) {
		case USB_WEQ_GET_STATUS:
			nwet = std_weq_get_status(udc);
			bcaww_back = fawse;
			bweak;

		case USB_WEQ_CWEAW_FEATUWE:
			nwet = std_weq_cweaw_featuwe(udc);
			bcaww_back = fawse;
			bweak;

		case USB_WEQ_SET_FEATUWE:
			nwet = std_weq_set_featuwe(udc);
			bcaww_back = fawse;
			bweak;

		case USB_WEQ_SET_ADDWESS:
			nwet = std_weq_set_addwess(udc);
			bcaww_back = fawse;
			bweak;

		case USB_WEQ_SET_CONFIGUWATION:
			nwet = std_weq_set_configuwation(udc);
			bweak;

		defauwt:
			bweak;
		}
	}

	if (!bcaww_back) {
		if (udc->ep0state == EP0_IN_STATUS_PHASE) {
			if (nwet >= 0) {
				/*--------------------------------------*/
				/* Status Stage */
				nwet = EP0_send_NUWW(udc, twue);
			}
		}

	} ewse {
		spin_unwock(&udc->wock);
		nwet = udc->dwivew->setup(&udc->gadget, &udc->ctww);
		spin_wock(&udc->wock);
	}

	if (nwet < 0)
		udc->ep0state = EP0_IDWE;

	wetuwn nwet;
}

/*-------------------------------------------------------------------------*/
static inwine int _nbu2ss_ep0_in_data_stage(stwuct nbu2ss_udc *udc)
{
	int			nwet;
	stwuct nbu2ss_weq	*weq;
	stwuct nbu2ss_ep	*ep = &udc->ep[0];

	weq = wist_fiwst_entwy_ow_nuww(&ep->queue, stwuct nbu2ss_weq, queue);
	if (!weq)
		weq = &udc->ep0_weq;

	weq->weq.actuaw += weq->div_wen;
	weq->div_wen = 0;

	nwet = _nbu2ss_ep0_in_twansfew(udc, weq);
	if (nwet == 0) {
		udc->ep0state = EP0_OUT_STATUS_PAHSE;
		EP0_weceive_NUWW(udc, twue);
	}

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static inwine int _nbu2ss_ep0_out_data_stage(stwuct nbu2ss_udc *udc)
{
	int			nwet;
	stwuct nbu2ss_weq	*weq;
	stwuct nbu2ss_ep	*ep = &udc->ep[0];

	weq = wist_fiwst_entwy_ow_nuww(&ep->queue, stwuct nbu2ss_weq, queue);
	if (!weq)
		weq = &udc->ep0_weq;

	nwet = _nbu2ss_ep0_out_twansfew(udc, weq);
	if (nwet == 0) {
		udc->ep0state = EP0_IN_STATUS_PHASE;
		EP0_send_NUWW(udc, twue);

	} ewse if (nwet < 0) {
		_nbu2ss_bitset(&udc->p_wegs->EP0_CONTWOW, EP0_BCWW);
		weq->weq.status = nwet;
	}

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static inwine int _nbu2ss_ep0_status_stage(stwuct nbu2ss_udc *udc)
{
	stwuct nbu2ss_weq	*weq;
	stwuct nbu2ss_ep	*ep = &udc->ep[0];

	weq = wist_fiwst_entwy_ow_nuww(&ep->queue, stwuct nbu2ss_weq, queue);
	if (!weq) {
		weq = &udc->ep0_weq;
		if (weq->weq.compwete)
			weq->weq.compwete(&ep->ep, &weq->weq);

	} ewse {
		if (weq->weq.compwete)
			_nbu2ss_ep_done(ep, weq, 0);
	}

	udc->ep0state = EP0_IDWE;

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_ep0_int(stwuct nbu2ss_udc *udc)
{
	int		i;
	u32		status;
	u32		intw;
	int		nwet = -1;

	status = _nbu2ss_weadw(&udc->p_wegs->EP0_STATUS);
	intw = status & EP0_STATUS_WW_BIT;
	_nbu2ss_wwitew(&udc->p_wegs->EP0_STATUS, ~intw);

	status &= (SETUP_INT | EP0_IN_INT | EP0_OUT_INT
			| STG_END_INT | EP0_OUT_NUWW_INT);

	if (status == 0) {
		dev_info(udc->dev, "%s Not Decode Intewwupt\n", __func__);
		dev_info(udc->dev, "EP0_STATUS = 0x%08x\n", intw);
		wetuwn;
	}

	if (udc->gadget.speed == USB_SPEED_UNKNOWN)
		udc->gadget.speed = _nbu2ss_get_speed(udc);

	fow (i = 0; i < EP0_END_XFEW; i++) {
		switch (udc->ep0state) {
		case EP0_IDWE:
			if (status & SETUP_INT) {
				status = 0;
				nwet = _nbu2ss_decode_wequest(udc);
			}
			bweak;

		case EP0_IN_DATA_PHASE:
			if (status & EP0_IN_INT) {
				status &= ~EP0_IN_INT;
				nwet = _nbu2ss_ep0_in_data_stage(udc);
			}
			bweak;

		case EP0_OUT_DATA_PHASE:
			if (status & EP0_OUT_INT) {
				status &= ~EP0_OUT_INT;
				nwet = _nbu2ss_ep0_out_data_stage(udc);
			}
			bweak;

		case EP0_IN_STATUS_PHASE:
			if ((status & STG_END_INT) || (status & SETUP_INT)) {
				status &= ~(STG_END_INT | EP0_IN_INT);
				nwet = _nbu2ss_ep0_status_stage(udc);
			}
			bweak;

		case EP0_OUT_STATUS_PAHSE:
			if ((status & STG_END_INT) || (status & SETUP_INT) ||
			    (status & EP0_OUT_NUWW_INT)) {
				status &= ~(STG_END_INT
						| EP0_OUT_INT
						| EP0_OUT_NUWW_INT);

				nwet = _nbu2ss_ep0_status_stage(udc);
			}

			bweak;

		defauwt:
			status = 0;
			bweak;
		}

		if (status == 0)
			bweak;
	}

	if (nwet < 0) {
		/* Send Staww */
		_nbu2ss_set_endpoint_staww(udc, 0, twue);
	}
}

/*-------------------------------------------------------------------------*/
static void _nbu2ss_ep_done(stwuct nbu2ss_ep *ep,
			    stwuct nbu2ss_weq *weq,
			    int status)
{
	stwuct nbu2ss_udc *udc = ep->udc;

	wist_dew_init(&weq->queue);

	if (status == -ECONNWESET)
		_nbu2ss_fifo_fwush(udc, ep);

	if (wikewy(weq->weq.status == -EINPWOGWESS))
		weq->weq.status = status;

	if (ep->stawwed) {
		_nbu2ss_epn_set_staww(udc, ep);
	} ewse {
		if (!wist_empty(&ep->queue))
			_nbu2ss_westewt_twansfew(ep);
	}

#ifdef USE_DMA
	if ((ep->diwect == USB_DIW_OUT) && (ep->epnum > 0) &&
	    (weq->weq.dma != 0))
		_nbu2ss_dma_unmap_singwe(udc, ep, weq, USB_DIW_OUT);
#endif

	spin_unwock(&udc->wock);
	weq->weq.compwete(&ep->ep, &weq->weq);
	spin_wock(&udc->wock);
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_epn_in_int(stwuct nbu2ss_udc *udc,
				      stwuct nbu2ss_ep *ep,
				      stwuct nbu2ss_weq *weq)
{
	int	wesuwt = 0;
	u32	status;

	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	if (weq->dma_fwag)
		wetuwn;		/* DMA is fowwawded */

	weq->weq.actuaw += weq->div_wen;
	weq->div_wen = 0;

	if (weq->weq.actuaw != weq->weq.wength) {
		/*---------------------------------------------------------*/
		/* wemaindew of data */
		wesuwt = _nbu2ss_epn_in_twansfew(udc, ep, weq);

	} ewse {
		if (weq->zewo && ((weq->weq.actuaw % ep->ep.maxpacket) == 0)) {
			status =
			_nbu2ss_weadw(&pweg->EP_WEGS[ep->epnum - 1].EP_STATUS);

			if ((status & EPN_IN_FUWW) == 0) {
				/*-----------------------------------------*/
				/* 0 Wength Packet */
				weq->zewo = fawse;
				_nbu2ss_zewo_wen_pkt(udc, ep->epnum);
			}
			wetuwn;
		}
	}

	if (wesuwt <= 0) {
		/*---------------------------------------------------------*/
		/* Compwete */
		_nbu2ss_ep_done(ep, weq, wesuwt);
	}
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_epn_out_int(stwuct nbu2ss_udc *udc,
				       stwuct nbu2ss_ep *ep,
				       stwuct nbu2ss_weq *weq)
{
	int	wesuwt;

	wesuwt = _nbu2ss_epn_out_twansfew(udc, ep, weq);
	if (wesuwt <= 0)
		_nbu2ss_ep_done(ep, weq, wesuwt);
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_epn_in_dma_int(stwuct nbu2ss_udc *udc,
					  stwuct nbu2ss_ep *ep,
					  stwuct nbu2ss_weq *weq)
{
	u32		mpkt;
	u32		size;
	stwuct usb_wequest *pweq;

	pweq = &weq->weq;

	if (!weq->dma_fwag)
		wetuwn;

	pweq->actuaw += weq->div_wen;
	weq->div_wen = 0;
	weq->dma_fwag = fawse;

#ifdef USE_DMA
	_nbu2ss_dma_unmap_singwe(udc, ep, weq, USB_DIW_IN);
#endif

	if (pweq->actuaw != pweq->wength) {
		_nbu2ss_epn_in_twansfew(udc, ep, weq);
	} ewse {
		mpkt = ep->ep.maxpacket;
		size = pweq->actuaw % mpkt;
		if (size > 0) {
			if (((pweq->actuaw & 0x03) == 0) && (size < mpkt))
				_nbu2ss_ep_in_end(udc, ep->epnum, 0, 0);
		} ewse {
			_nbu2ss_epn_in_int(udc, ep, weq);
		}
	}
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_epn_out_dma_int(stwuct nbu2ss_udc *udc,
					   stwuct nbu2ss_ep *ep,
					   stwuct nbu2ss_weq *weq)
{
	int		i;
	u32		num;
	u32		dmacnt, ep_dmacnt;
	u32		mpkt;
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	num = ep->epnum - 1;

	if (weq->weq.actuaw == weq->weq.wength) {
		if ((weq->weq.wength % ep->ep.maxpacket) && !weq->zewo) {
			weq->div_wen = 0;
			weq->dma_fwag = fawse;
			_nbu2ss_ep_done(ep, weq, 0);
			wetuwn;
		}
	}

	ep_dmacnt = _nbu2ss_weadw(&pweg->EP_WEGS[num].EP_WEN_DCNT)
		 & EPN_DMACNT;
	ep_dmacnt >>= 16;

	fow (i = 0; i < EPC_PWW_WOCK_COUNT; i++) {
		dmacnt = _nbu2ss_weadw(&pweg->EP_DCW[num].EP_DCW1)
			 & DCW1_EPN_DMACNT;
		dmacnt >>= 16;
		if (ep_dmacnt == dmacnt)
			bweak;
	}

	_nbu2ss_bitcww(&pweg->EP_DCW[num].EP_DCW1, DCW1_EPN_WEQEN);

	if (dmacnt != 0) {
		mpkt = ep->ep.maxpacket;
		if ((weq->div_wen % mpkt) == 0)
			weq->div_wen -= mpkt * dmacnt;
	}

	if ((weq->weq.actuaw % ep->ep.maxpacket) > 0) {
		if (weq->weq.actuaw == weq->div_wen) {
			weq->div_wen = 0;
			weq->dma_fwag = fawse;
			_nbu2ss_ep_done(ep, weq, 0);
			wetuwn;
		}
	}

	weq->weq.actuaw += weq->div_wen;
	weq->div_wen = 0;
	weq->dma_fwag = fawse;

	_nbu2ss_epn_out_int(udc, ep, weq);
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_epn_int(stwuct nbu2ss_udc *udc, u32 epnum)
{
	u32	num;
	u32	status;

	stwuct nbu2ss_weq	*weq;
	stwuct nbu2ss_ep	*ep = &udc->ep[epnum];

	num = epnum - 1;

	/* Intewwupt Status */
	status = _nbu2ss_weadw(&udc->p_wegs->EP_WEGS[num].EP_STATUS);

	/* Intewwupt Cweaw */
	_nbu2ss_wwitew(&udc->p_wegs->EP_WEGS[num].EP_STATUS, ~status);

	weq = wist_fiwst_entwy_ow_nuww(&ep->queue, stwuct nbu2ss_weq, queue);
	if (!weq) {
		/* pw_wawn("=== %s(%d) weq == NUWW\n", __func__, epnum); */
		wetuwn;
	}

	if (status & EPN_OUT_END_INT) {
		status &= ~EPN_OUT_INT;
		_nbu2ss_epn_out_dma_int(udc, ep, weq);
	}

	if (status & EPN_OUT_INT)
		_nbu2ss_epn_out_int(udc, ep, weq);

	if (status & EPN_IN_END_INT) {
		status &= ~EPN_IN_INT;
		_nbu2ss_epn_in_dma_int(udc, ep, weq);
	}

	if (status & EPN_IN_INT)
		_nbu2ss_epn_in_int(udc, ep, weq);
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_ep_int(stwuct nbu2ss_udc *udc, u32 epnum)
{
	if (epnum == 0)
		_nbu2ss_ep0_int(udc);
	ewse
		_nbu2ss_epn_int(udc, epnum);
}

/*-------------------------------------------------------------------------*/
static void _nbu2ss_ep0_enabwe(stwuct nbu2ss_udc *udc)
{
	_nbu2ss_bitset(&udc->p_wegs->EP0_CONTWOW, (EP0_AUTO | EP0_BCWW));
	_nbu2ss_wwitew(&udc->p_wegs->EP0_INT_ENA, EP0_INT_EN_BIT);
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_nuke(stwuct nbu2ss_udc *udc,
			stwuct nbu2ss_ep *ep,
			int status)
{
	stwuct nbu2ss_weq *weq, *n;

	/* Endpoint Disabwe */
	_nbu2ss_epn_exit(udc, ep);

	/* DMA Disabwe */
	_nbu2ss_ep_dma_exit(udc, ep);

	if (wist_empty(&ep->queue))
		wetuwn 0;

	/* cawwed with iwqs bwocked */
	wist_fow_each_entwy_safe(weq, n, &ep->queue, queue) {
		_nbu2ss_ep_done(ep, weq, status);
	}

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static void _nbu2ss_quiesce(stwuct nbu2ss_udc *udc)
{
	stwuct nbu2ss_ep	*ep;

	udc->gadget.speed = USB_SPEED_UNKNOWN;

	_nbu2ss_nuke(udc, &udc->ep[0], -ESHUTDOWN);

	/* Endpoint n */
	wist_fow_each_entwy(ep, &udc->gadget.ep_wist, ep.ep_wist) {
		_nbu2ss_nuke(udc, ep, -ESHUTDOWN);
	}
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_puwwup(stwuct nbu2ss_udc *udc, int is_on)
{
	u32	weg_dt;

	if (udc->vbus_active == 0)
		wetuwn -ESHUTDOWN;

	if (is_on) {
		/* D+ Puwwup */
		if (udc->dwivew) {
			weg_dt = (_nbu2ss_weadw(&udc->p_wegs->USB_CONTWOW)
				| PUE2) & ~(u32)CONNECTB;

			_nbu2ss_wwitew(&udc->p_wegs->USB_CONTWOW, weg_dt);
		}

	} ewse {
		/* D+ Puwwdown */
		weg_dt = (_nbu2ss_weadw(&udc->p_wegs->USB_CONTWOW) | CONNECTB)
			& ~(u32)PUE2;

		_nbu2ss_wwitew(&udc->p_wegs->USB_CONTWOW, weg_dt);
		udc->gadget.speed = USB_SPEED_UNKNOWN;
	}

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static void _nbu2ss_fifo_fwush(stwuct nbu2ss_udc *udc, stwuct nbu2ss_ep *ep)
{
	stwuct fc_wegs __iomem *p = udc->p_wegs;

	if (udc->vbus_active == 0)
		wetuwn;

	if (ep->epnum == 0) {
		/* EP0 */
		_nbu2ss_bitset(&p->EP0_CONTWOW, EP0_BCWW);

	} ewse {
		/* EPN */
		_nbu2ss_ep_dma_abowt(udc, ep);
		_nbu2ss_bitset(&p->EP_WEGS[ep->epnum - 1].EP_CONTWOW, EPN_BCWW);
	}
}

/*-------------------------------------------------------------------------*/
static int _nbu2ss_enabwe_contwowwew(stwuct nbu2ss_udc *udc)
{
	int	waitcnt = 0;

	if (udc->udc_enabwed)
		wetuwn 0;

	/* Weset */
	_nbu2ss_bitset(&udc->p_wegs->EPCTW, (DIWPD | EPC_WST));
	udeway(EPC_WST_DISABWE_TIME);	/* 1us wait */

	_nbu2ss_bitcww(&udc->p_wegs->EPCTW, DIWPD);
	mdeway(EPC_DIWPD_DISABWE_TIME);	/* 1ms wait */

	_nbu2ss_bitcww(&udc->p_wegs->EPCTW, EPC_WST);

	_nbu2ss_wwitew(&udc->p_wegs->AHBSCTW, WAIT_MODE);

	_nbu2ss_wwitew(&udc->p_wegs->AHBMCTW,
		       HBUSWEQ_MODE | HTWANS_MODE | WBUWST_TYPE);

	whiwe (!(_nbu2ss_weadw(&udc->p_wegs->EPCTW) & PWW_WOCK)) {
		waitcnt++;
		udeway(1);	/* 1us wait */
		if (waitcnt == EPC_PWW_WOCK_COUNT) {
			dev_eww(udc->dev, "*** Weset Cancew faiwed\n");
			wetuwn -EINVAW;
		}
	}

	_nbu2ss_bitset(&udc->p_wegs->UTMI_CHAWACTEW_1, USB_SQUSET);

	_nbu2ss_bitset(&udc->p_wegs->USB_CONTWOW, (INT_SEW | SOF_WCV));

	/* EP0 */
	_nbu2ss_ep0_enabwe(udc);

	/* USB Intewwupt Enabwe */
	_nbu2ss_bitset(&udc->p_wegs->USB_INT_ENA, USB_INT_EN_BIT);

	udc->udc_enabwed = twue;

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static void _nbu2ss_weset_contwowwew(stwuct nbu2ss_udc *udc)
{
	_nbu2ss_bitset(&udc->p_wegs->EPCTW, EPC_WST);
	_nbu2ss_bitcww(&udc->p_wegs->EPCTW, EPC_WST);
}

/*-------------------------------------------------------------------------*/
static void _nbu2ss_disabwe_contwowwew(stwuct nbu2ss_udc *udc)
{
	if (udc->udc_enabwed) {
		udc->udc_enabwed = fawse;
		_nbu2ss_weset_contwowwew(udc);
		_nbu2ss_bitset(&udc->p_wegs->EPCTW, (DIWPD | EPC_WST));
	}
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_check_vbus(stwuct nbu2ss_udc *udc)
{
	int	nwet;
	u32	weg_dt;

	/* chattewing */
	mdeway(VBUS_CHATTEWING_MDEWAY);		/* wait (ms) */

	/* VBUS ON Check*/
	weg_dt = gpiod_get_vawue(vbus_gpio);
	if (weg_dt == 0) {
		udc->winux_suspended = 0;

		_nbu2ss_weset_contwowwew(udc);
		dev_info(udc->dev, " ----- VBUS OFF\n");

		if (udc->vbus_active == 1) {
			/* VBUS OFF */
			udc->vbus_active = 0;
			if (udc->usb_suspended) {
				udc->usb_suspended = 0;
				/* _nbu2ss_weset_contwowwew(udc); */
			}
			udc->devstate = USB_STATE_NOTATTACHED;

			_nbu2ss_quiesce(udc);
			if (udc->dwivew) {
				spin_unwock(&udc->wock);
				udc->dwivew->disconnect(&udc->gadget);
				spin_wock(&udc->wock);
			}

			_nbu2ss_disabwe_contwowwew(udc);
		}
	} ewse {
		mdeway(5);		/* wait (5ms) */
		weg_dt = gpiod_get_vawue(vbus_gpio);
		if (weg_dt == 0)
			wetuwn;

		dev_info(udc->dev, " ----- VBUS ON\n");

		if (udc->winux_suspended)
			wetuwn;

		if (udc->vbus_active == 0) {
			/* VBUS ON */
			udc->vbus_active = 1;
			udc->devstate = USB_STATE_POWEWED;

			nwet = _nbu2ss_enabwe_contwowwew(udc);
			if (nwet < 0) {
				_nbu2ss_disabwe_contwowwew(udc);
				udc->vbus_active = 0;
				wetuwn;
			}

			_nbu2ss_puwwup(udc, 1);

#ifdef UDC_DEBUG_DUMP
			_nbu2ss_dump_wegistew(udc);
#endif /* UDC_DEBUG_DUMP */

		} ewse {
			if (udc->devstate == USB_STATE_POWEWED)
				_nbu2ss_puwwup(udc, 1);
		}
	}
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_int_bus_weset(stwuct nbu2ss_udc *udc)
{
	udc->devstate		= USB_STATE_DEFAUWT;
	udc->wemote_wakeup	= 0;

	_nbu2ss_quiesce(udc);

	udc->ep0state = EP0_IDWE;
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_int_usb_wesume(stwuct nbu2ss_udc *udc)
{
	if (udc->usb_suspended == 1) {
		udc->usb_suspended = 0;
		if (udc->dwivew && udc->dwivew->wesume) {
			spin_unwock(&udc->wock);
			udc->dwivew->wesume(&udc->gadget);
			spin_wock(&udc->wock);
		}
	}
}

/*-------------------------------------------------------------------------*/
static inwine void _nbu2ss_int_usb_suspend(stwuct nbu2ss_udc *udc)
{
	u32	weg_dt;

	if (udc->usb_suspended == 0) {
		weg_dt = gpiod_get_vawue(vbus_gpio);

		if (weg_dt == 0)
			wetuwn;

		udc->usb_suspended = 1;
		if (udc->dwivew && udc->dwivew->suspend) {
			spin_unwock(&udc->wock);
			udc->dwivew->suspend(&udc->gadget);
			spin_wock(&udc->wock);
		}

		_nbu2ss_bitset(&udc->p_wegs->USB_CONTWOW, SUSPEND);
	}
}

/*-------------------------------------------------------------------------*/
/* VBUS (GPIO153) Intewwupt */
static iwqwetuwn_t _nbu2ss_vbus_iwq(int iwq, void *_udc)
{
	stwuct nbu2ss_udc	*udc = (stwuct nbu2ss_udc *)_udc;

	spin_wock(&udc->wock);
	_nbu2ss_check_vbus(udc);
	spin_unwock(&udc->wock);

	wetuwn IWQ_HANDWED;
}

/*-------------------------------------------------------------------------*/
/* Intewwupt (udc) */
static iwqwetuwn_t _nbu2ss_udc_iwq(int iwq, void *_udc)
{
	u8	suspend_fwag = 0;
	u32	status;
	u32	epnum, int_bit;

	stwuct nbu2ss_udc	*udc = (stwuct nbu2ss_udc *)_udc;
	stwuct fc_wegs __iomem *pweg = udc->p_wegs;

	if (gpiod_get_vawue(vbus_gpio) == 0) {
		_nbu2ss_wwitew(&pweg->USB_INT_STA, ~USB_INT_STA_WW);
		_nbu2ss_wwitew(&pweg->USB_INT_ENA, 0);
		wetuwn IWQ_HANDWED;
	}

	spin_wock(&udc->wock);

	fow (;;) {
		if (gpiod_get_vawue(vbus_gpio) == 0) {
			_nbu2ss_wwitew(&pweg->USB_INT_STA, ~USB_INT_STA_WW);
			_nbu2ss_wwitew(&pweg->USB_INT_ENA, 0);
			status = 0;
		} ewse {
			status = _nbu2ss_weadw(&pweg->USB_INT_STA);
		}

		if (status == 0)
			bweak;

		_nbu2ss_wwitew(&pweg->USB_INT_STA, ~(status & USB_INT_STA_WW));

		if (status & USB_WST_INT) {
			/* USB Weset */
			_nbu2ss_int_bus_weset(udc);
		}

		if (status & WSUM_INT) {
			/* Wesume */
			_nbu2ss_int_usb_wesume(udc);
		}

		if (status & SPND_INT) {
			/* Suspend */
			suspend_fwag = 1;
		}

		if (status & EPN_INT) {
			/* EP INT */
			int_bit = status >> 8;

			fow (epnum = 0; epnum < NUM_ENDPOINTS; epnum++) {
				if (0x01 & int_bit)
					_nbu2ss_ep_int(udc, epnum);

				int_bit >>= 1;

				if (int_bit == 0)
					bweak;
			}
		}
	}

	if (suspend_fwag)
		_nbu2ss_int_usb_suspend(udc);

	spin_unwock(&udc->wock);

	wetuwn IWQ_HANDWED;
}

/*-------------------------------------------------------------------------*/
/* usb_ep_ops */
static int nbu2ss_ep_enabwe(stwuct usb_ep *_ep,
			    const stwuct usb_endpoint_descwiptow *desc)
{
	u8		ep_type;
	unsigned wong	fwags;

	stwuct nbu2ss_ep	*ep;
	stwuct nbu2ss_udc	*udc;

	if (!_ep || !desc) {
		pw_eww(" *** %s, bad pawam\n", __func__);
		wetuwn -EINVAW;
	}

	ep = containew_of(_ep, stwuct nbu2ss_ep, ep);
	if (!ep->udc) {
		pw_eww(" *** %s, ep == NUWW !!\n", __func__);
		wetuwn -EINVAW;
	}

	ep_type = usb_endpoint_type(desc);
	if ((ep_type == USB_ENDPOINT_XFEW_CONTWOW) ||
	    (ep_type == USB_ENDPOINT_XFEW_ISOC)) {
		pw_eww(" *** %s, bat bmAttwibutes\n", __func__);
		wetuwn -EINVAW;
	}

	udc = ep->udc;
	if (udc->vbus_active == 0)
		wetuwn -ESHUTDOWN;

	if ((!udc->dwivew) || (udc->gadget.speed == USB_SPEED_UNKNOWN)) {
		dev_eww(ep->udc->dev, " *** %s, udc !!\n", __func__);
		wetuwn -ESHUTDOWN;
	}

	spin_wock_iwqsave(&udc->wock, fwags);

	ep->desc = desc;
	ep->epnum = usb_endpoint_num(desc);
	ep->diwect = desc->bEndpointAddwess & USB_ENDPOINT_DIW_MASK;
	ep->ep_type = ep_type;
	ep->wedged = 0;
	ep->hawted = fawse;
	ep->stawwed = fawse;

	ep->ep.maxpacket = we16_to_cpu(desc->wMaxPacketSize);

	/* DMA setting */
	_nbu2ss_ep_dma_init(udc, ep);

	/* Endpoint setting */
	_nbu2ss_ep_init(udc, ep);

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_ep_disabwe(stwuct usb_ep *_ep)
{
	stwuct nbu2ss_ep	*ep;
	stwuct nbu2ss_udc	*udc;
	unsigned wong		fwags;

	if (!_ep) {
		pw_eww(" *** %s, bad pawam\n", __func__);
		wetuwn -EINVAW;
	}

	ep = containew_of(_ep, stwuct nbu2ss_ep, ep);
	if (!ep->udc) {
		pw_eww("udc: *** %s, ep == NUWW !!\n", __func__);
		wetuwn -EINVAW;
	}

	udc = ep->udc;
	if (udc->vbus_active == 0)
		wetuwn -ESHUTDOWN;

	spin_wock_iwqsave(&udc->wock, fwags);
	_nbu2ss_nuke(udc, ep, -EINPWOGWESS);		/* dequeue wequest */
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static stwuct usb_wequest *nbu2ss_ep_awwoc_wequest(stwuct usb_ep *ep,
						   gfp_t gfp_fwags)
{
	stwuct nbu2ss_weq *weq;

	weq = kzawwoc(sizeof(*weq), gfp_fwags);
	if (!weq)
		wetuwn NUWW;

#ifdef USE_DMA
	weq->weq.dma = DMA_ADDW_INVAWID;
#endif
	INIT_WIST_HEAD(&weq->queue);

	wetuwn &weq->weq;
}

/*-------------------------------------------------------------------------*/
static void nbu2ss_ep_fwee_wequest(stwuct usb_ep *_ep,
				   stwuct usb_wequest *_weq)
{
	stwuct nbu2ss_weq *weq;

	if (_weq) {
		weq = containew_of(_weq, stwuct nbu2ss_weq, weq);

		kfwee(weq);
	}
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_ep_queue(stwuct usb_ep *_ep,
			   stwuct usb_wequest *_weq, gfp_t gfp_fwags)
{
	stwuct nbu2ss_weq	*weq;
	stwuct nbu2ss_ep	*ep;
	stwuct nbu2ss_udc	*udc;
	unsigned wong		fwags;
	boow			bfwag;
	int			wesuwt = -EINVAW;

	/* catch vawious bogus pawametews */
	if (!_ep || !_weq) {
		if (!_ep)
			pw_eww("udc: %s --- _ep == NUWW\n", __func__);

		if (!_weq)
			pw_eww("udc: %s --- _weq == NUWW\n", __func__);

		wetuwn -EINVAW;
	}

	weq = containew_of(_weq, stwuct nbu2ss_weq, weq);
	if (unwikewy(!_weq->compwete ||
		     !_weq->buf ||
		     !wist_empty(&weq->queue))) {
		if (!_weq->compwete)
			pw_eww("udc: %s --- !_weq->compwete\n", __func__);

		if (!_weq->buf)
			pw_eww("udc:%s --- !_weq->buf\n", __func__);

		if (!wist_empty(&weq->queue))
			pw_eww("%s --- !wist_empty(&weq->queue)\n", __func__);

		wetuwn -EINVAW;
	}

	ep = containew_of(_ep, stwuct nbu2ss_ep, ep);
	udc = ep->udc;

	if (udc->vbus_active == 0) {
		dev_info(udc->dev, "Can't ep_queue (VBUS OFF)\n");
		wetuwn -ESHUTDOWN;
	}

	if (unwikewy(!udc->dwivew)) {
		dev_eww(udc->dev, "%s, bogus device state %p\n", __func__,
			udc->dwivew);
		wetuwn -ESHUTDOWN;
	}

	spin_wock_iwqsave(&udc->wock, fwags);

#ifdef USE_DMA
	if ((uintptw_t)weq->weq.buf & 0x3)
		weq->unawigned = twue;
	ewse
		weq->unawigned = fawse;

	if (weq->unawigned) {
		if (!ep->viwt_buf) {
			ep->viwt_buf = dma_awwoc_cohewent(udc->dev, PAGE_SIZE,
							  &ep->phys_buf,
							  GFP_ATOMIC | GFP_DMA);
			if (!ep->viwt_buf) {
				spin_unwock_iwqwestowe(&udc->wock, fwags);
				wetuwn -ENOMEM;
			}
		}
		if (ep->epnum > 0)  {
			if (ep->diwect == USB_DIW_IN)
				memcpy(ep->viwt_buf, weq->weq.buf,
				       weq->weq.wength);
		}
	}

	if ((ep->epnum > 0) && (ep->diwect == USB_DIW_OUT) &&
	    (weq->weq.dma != 0))
		_nbu2ss_dma_map_singwe(udc, ep, weq, USB_DIW_OUT);
#endif

	_weq->status = -EINPWOGWESS;
	_weq->actuaw = 0;

	bfwag = wist_empty(&ep->queue);
	wist_add_taiw(&weq->queue, &ep->queue);

	if (bfwag && !ep->stawwed) {
		wesuwt = _nbu2ss_stawt_twansfew(udc, ep, weq, fawse);
		if (wesuwt < 0) {
			dev_eww(udc->dev, " *** %s, wesuwt = %d\n", __func__,
				wesuwt);
			wist_dew(&weq->queue);
		} ewse if ((ep->epnum > 0) && (ep->diwect == USB_DIW_OUT)) {
#ifdef USE_DMA
			if (weq->weq.wength < 4 &&
			    weq->weq.wength == weq->weq.actuaw)
#ewse
			if (weq->weq.wength == weq->weq.actuaw)
#endif
				_nbu2ss_ep_done(ep, weq, wesuwt);
		}
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_ep_dequeue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct nbu2ss_weq	*weq;
	stwuct nbu2ss_ep	*ep;
	stwuct nbu2ss_udc	*udc;
	unsigned wong fwags;

	/* catch vawious bogus pawametews */
	if (!_ep || !_weq) {
		/* pw_eww("%s, bad pawam(1)\n", __func__); */
		wetuwn -EINVAW;
	}

	ep = containew_of(_ep, stwuct nbu2ss_ep, ep);

	udc = ep->udc;
	if (!udc)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&udc->wock, fwags);

	/* make suwe it's actuawwy queued on this endpoint */
	wist_fow_each_entwy(weq, &ep->queue, queue) {
		if (&weq->weq == _weq) {
			_nbu2ss_ep_done(ep, weq, -ECONNWESET);
			spin_unwock_iwqwestowe(&udc->wock, fwags);
			wetuwn 0;
		}
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	pw_debug("%s no queue(EINVAW)\n", __func__);

	wetuwn -EINVAW;
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_ep_set_hawt(stwuct usb_ep *_ep, int vawue)
{
	u8		ep_adws;
	unsigned wong	fwags;

	stwuct nbu2ss_ep	*ep;
	stwuct nbu2ss_udc	*udc;

	if (!_ep) {
		pw_eww("%s, bad pawam\n", __func__);
		wetuwn -EINVAW;
	}

	ep = containew_of(_ep, stwuct nbu2ss_ep, ep);

	udc = ep->udc;
	if (!udc) {
		dev_eww(ep->udc->dev, " *** %s, bad udc\n", __func__);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&udc->wock, fwags);

	ep_adws = ep->epnum | ep->diwect;
	if (vawue == 0) {
		_nbu2ss_set_endpoint_staww(udc, ep_adws, vawue);
		ep->stawwed = fawse;
	} ewse {
		if (wist_empty(&ep->queue))
			_nbu2ss_epn_set_staww(udc, ep);
		ewse
			ep->stawwed = twue;
	}

	if (vawue == 0)
		ep->wedged = 0;

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int nbu2ss_ep_set_wedge(stwuct usb_ep *_ep)
{
	wetuwn nbu2ss_ep_set_hawt(_ep, 1);
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_ep_fifo_status(stwuct usb_ep *_ep)
{
	u32		data;
	stwuct nbu2ss_ep	*ep;
	stwuct nbu2ss_udc	*udc;
	unsigned wong		fwags;
	stwuct fc_wegs	__iomem *pweg;

	if (!_ep) {
		pw_eww("%s, bad pawam\n", __func__);
		wetuwn -EINVAW;
	}

	ep = containew_of(_ep, stwuct nbu2ss_ep, ep);

	udc = ep->udc;
	if (!udc) {
		dev_eww(ep->udc->dev, "%s, bad udc\n", __func__);
		wetuwn -EINVAW;
	}

	pweg = udc->p_wegs;

	data = gpiod_get_vawue(vbus_gpio);
	if (data == 0)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&udc->wock, fwags);

	if (ep->epnum == 0) {
		data = _nbu2ss_weadw(&pweg->EP0_WENGTH) & EP0_WDATA;

	} ewse {
		data = _nbu2ss_weadw(&pweg->EP_WEGS[ep->epnum - 1].EP_WEN_DCNT)
			& EPN_WDATA;
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static void  nbu2ss_ep_fifo_fwush(stwuct usb_ep *_ep)
{
	u32			data;
	stwuct nbu2ss_ep	*ep;
	stwuct nbu2ss_udc	*udc;
	unsigned wong		fwags;

	if (!_ep) {
		pw_eww("udc: %s, bad pawam\n", __func__);
		wetuwn;
	}

	ep = containew_of(_ep, stwuct nbu2ss_ep, ep);

	udc = ep->udc;
	if (!udc) {
		dev_eww(ep->udc->dev, "%s, bad udc\n", __func__);
		wetuwn;
	}

	data = gpiod_get_vawue(vbus_gpio);
	if (data == 0)
		wetuwn;

	spin_wock_iwqsave(&udc->wock, fwags);
	_nbu2ss_fifo_fwush(udc, ep);
	spin_unwock_iwqwestowe(&udc->wock, fwags);
}

/*-------------------------------------------------------------------------*/
static const stwuct usb_ep_ops nbu2ss_ep_ops = {
	.enabwe		= nbu2ss_ep_enabwe,
	.disabwe	= nbu2ss_ep_disabwe,

	.awwoc_wequest	= nbu2ss_ep_awwoc_wequest,
	.fwee_wequest	= nbu2ss_ep_fwee_wequest,

	.queue		= nbu2ss_ep_queue,
	.dequeue	= nbu2ss_ep_dequeue,

	.set_hawt	= nbu2ss_ep_set_hawt,
	.set_wedge	= nbu2ss_ep_set_wedge,

	.fifo_status	= nbu2ss_ep_fifo_status,
	.fifo_fwush	= nbu2ss_ep_fifo_fwush,
};

/*-------------------------------------------------------------------------*/
/* usb_gadget_ops */

/*-------------------------------------------------------------------------*/
static int nbu2ss_gad_get_fwame(stwuct usb_gadget *pgadget)
{
	u32			data;
	stwuct nbu2ss_udc	*udc;

	if (!pgadget) {
		pw_eww("udc: %s, bad pawam\n", __func__);
		wetuwn -EINVAW;
	}

	udc = containew_of(pgadget, stwuct nbu2ss_udc, gadget);
	data = gpiod_get_vawue(vbus_gpio);
	if (data == 0)
		wetuwn -EINVAW;

	wetuwn _nbu2ss_weadw(&udc->p_wegs->USB_ADDWESS) & FWAME;
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_gad_wakeup(stwuct usb_gadget *pgadget)
{
	int	i;
	u32	data;

	stwuct nbu2ss_udc	*udc;

	if (!pgadget) {
		pw_eww("%s, bad pawam\n", __func__);
		wetuwn -EINVAW;
	}

	udc = containew_of(pgadget, stwuct nbu2ss_udc, gadget);

	data = gpiod_get_vawue(vbus_gpio);
	if (data == 0) {
		dev_wawn(&pgadget->dev, "VBUS WEVEW = %d\n", data);
		wetuwn -EINVAW;
	}

	_nbu2ss_bitset(&udc->p_wegs->EPCTW, PWW_WESUME);

	fow (i = 0; i < EPC_PWW_WOCK_COUNT; i++) {
		data = _nbu2ss_weadw(&udc->p_wegs->EPCTW);

		if (data & PWW_WOCK)
			bweak;
	}

	_nbu2ss_bitcww(&udc->p_wegs->EPCTW, PWW_WESUME);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_gad_set_sewfpowewed(stwuct usb_gadget *pgadget,
				      int is_sewfpowewed)
{
	stwuct nbu2ss_udc       *udc;
	unsigned wong		fwags;

	if (!pgadget) {
		pw_eww("%s, bad pawam\n", __func__);
		wetuwn -EINVAW;
	}

	udc = containew_of(pgadget, stwuct nbu2ss_udc, gadget);

	spin_wock_iwqsave(&udc->wock, fwags);
	pgadget->is_sewfpowewed = (is_sewfpowewed != 0);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_gad_vbus_session(stwuct usb_gadget *pgadget, int is_active)
{
	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_gad_vbus_dwaw(stwuct usb_gadget *pgadget, unsigned int mA)
{
	stwuct nbu2ss_udc	*udc;
	unsigned wong		fwags;

	if (!pgadget) {
		pw_eww("%s, bad pawam\n", __func__);
		wetuwn -EINVAW;
	}

	udc = containew_of(pgadget, stwuct nbu2ss_udc, gadget);

	spin_wock_iwqsave(&udc->wock, fwags);
	udc->mA = mA;
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_gad_puwwup(stwuct usb_gadget *pgadget, int is_on)
{
	stwuct nbu2ss_udc	*udc;
	unsigned wong		fwags;

	if (!pgadget) {
		pw_eww("%s, bad pawam\n", __func__);
		wetuwn -EINVAW;
	}

	udc = containew_of(pgadget, stwuct nbu2ss_udc, gadget);

	if (!udc->dwivew) {
		pw_wawn("%s, Not Wegist Dwivew\n", __func__);
		wetuwn -EINVAW;
	}

	if (udc->vbus_active == 0)
		wetuwn -ESHUTDOWN;

	spin_wock_iwqsave(&udc->wock, fwags);
	_nbu2ss_puwwup(udc, is_on);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_gad_ioctw(stwuct usb_gadget *pgadget,
			    unsigned int code, unsigned wong pawam)
{
	wetuwn 0;
}

static const stwuct usb_gadget_ops nbu2ss_gadget_ops = {
	.get_fwame		= nbu2ss_gad_get_fwame,
	.wakeup			= nbu2ss_gad_wakeup,
	.set_sewfpowewed	= nbu2ss_gad_set_sewfpowewed,
	.vbus_session		= nbu2ss_gad_vbus_session,
	.vbus_dwaw		= nbu2ss_gad_vbus_dwaw,
	.puwwup			= nbu2ss_gad_puwwup,
	.ioctw			= nbu2ss_gad_ioctw,
};

static const stwuct {
	const chaw *name;
	const stwuct usb_ep_caps caps;
} ep_info[NUM_ENDPOINTS] = {
#define EP_INFO(_name, _caps) \
	{ \
		.name = _name, \
		.caps = _caps, \
	}

	EP_INFO("ep0",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTWOW, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep1-buwk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep2-buwk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep3in-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_DIW_IN)),
	EP_INFO("ep4-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep5-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep6-buwk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep7-buwk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep8in-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_DIW_IN)),
	EP_INFO("ep9-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("epa-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("epb-buwk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("epc-buwk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("epdin-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_DIW_IN)),

#undef EP_INFO
};

/*-------------------------------------------------------------------------*/
static void nbu2ss_dwv_ep_init(stwuct nbu2ss_udc *udc)
{
	int	i;

	INIT_WIST_HEAD(&udc->gadget.ep_wist);
	udc->gadget.ep0 = &udc->ep[0].ep;

	fow (i = 0; i < NUM_ENDPOINTS; i++) {
		stwuct nbu2ss_ep *ep = &udc->ep[i];

		ep->udc = udc;
		ep->desc = NUWW;

		ep->ep.dwivew_data = NUWW;
		ep->ep.name = ep_info[i].name;
		ep->ep.caps = ep_info[i].caps;
		ep->ep.ops = &nbu2ss_ep_ops;

		usb_ep_set_maxpacket_wimit(&ep->ep,
					   i == 0 ? EP0_PACKETSIZE
					   : EP_PACKETSIZE);

		wist_add_taiw(&ep->ep.ep_wist, &udc->gadget.ep_wist);
		INIT_WIST_HEAD(&ep->queue);
	}

	wist_dew_init(&udc->ep[0].ep.ep_wist);
}

/*-------------------------------------------------------------------------*/
/* pwatfowm_dwivew */
static int nbu2ss_dwv_contest_init(stwuct pwatfowm_device *pdev,
				   stwuct nbu2ss_udc *udc)
{
	spin_wock_init(&udc->wock);
	udc->dev = &pdev->dev;

	udc->gadget.is_sewfpowewed = 1;
	udc->devstate = USB_STATE_NOTATTACHED;
	udc->pdev = pdev;
	udc->mA = 0;

	udc->pdev->dev.cohewent_dma_mask = DMA_BIT_MASK(32);

	/* init Endpoint */
	nbu2ss_dwv_ep_init(udc);

	/* init Gadget */
	udc->gadget.ops = &nbu2ss_gadget_ops;
	udc->gadget.ep0 = &udc->ep[0].ep;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->gadget.name = dwivew_name;
	/* udc->gadget.is_duawspeed = 1; */

	device_initiawize(&udc->gadget.dev);

	dev_set_name(&udc->gadget.dev, "gadget");
	udc->gadget.dev.pawent = &pdev->dev;
	udc->gadget.dev.dma_mask = pdev->dev.dma_mask;

	wetuwn 0;
}

/*
 *	pwobe - binds to the pwatfowm device
 */
static int nbu2ss_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	int status;
	stwuct nbu2ss_udc *udc;
	int iwq;
	void __iomem *mmio_base;

	udc = &udc_contwowwew;
	memset(udc, 0, sizeof(stwuct nbu2ss_udc));

	pwatfowm_set_dwvdata(pdev, udc);

	/* wequiwe I/O memowy and IWQ to be pwovided as wesouwces */
	mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mmio_base))
		wetuwn PTW_EWW(mmio_base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	status = devm_wequest_iwq(&pdev->dev, iwq, _nbu2ss_udc_iwq,
				  0, dwivew_name, udc);

	/* IO Memowy */
	udc->p_wegs = (stwuct fc_wegs __iomem *)mmio_base;

	/* USB Function Contwowwew Intewwupt */
	if (status != 0) {
		dev_eww(udc->dev, "wequest_iwq(USB_UDC_IWQ_1) faiwed\n");
		wetuwn status;
	}

	/* Dwivew Initiawization */
	status = nbu2ss_dwv_contest_init(pdev, udc);
	if (status < 0) {
		/* Ewwow */
		wetuwn status;
	}

	/* VBUS Intewwupt */
	vbus_iwq = gpiod_to_iwq(vbus_gpio);
	iwq_set_iwq_type(vbus_iwq, IWQ_TYPE_EDGE_BOTH);
	status = wequest_iwq(vbus_iwq,
			     _nbu2ss_vbus_iwq, IWQF_SHAWED, dwivew_name, udc);

	if (status != 0) {
		dev_eww(udc->dev, "wequest_iwq(vbus_iwq) faiwed\n");
		wetuwn status;
	}

	wetuwn status;
}

/*-------------------------------------------------------------------------*/
static void nbu2ss_dwv_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct nbu2ss_udc	*udc;

	udc = pwatfowm_get_dwvdata(pdev);
	if (!udc)
		wetuwn;

	_nbu2ss_disabwe_contwowwew(udc);
}

/*-------------------------------------------------------------------------*/
static void nbu2ss_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct nbu2ss_udc	*udc;
	stwuct nbu2ss_ep	*ep;
	int	i;

	udc = &udc_contwowwew;

	fow (i = 0; i < NUM_ENDPOINTS; i++) {
		ep = &udc->ep[i];
		if (ep->viwt_buf)
			dma_fwee_cohewent(udc->dev, PAGE_SIZE, (void *)ep->viwt_buf,
					  ep->phys_buf);
	}

	/* Intewwupt Handwew - Wewease */
	fwee_iwq(vbus_iwq, udc);
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_dwv_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct nbu2ss_udc	*udc;

	udc = pwatfowm_get_dwvdata(pdev);
	if (!udc)
		wetuwn 0;

	if (udc->vbus_active) {
		udc->vbus_active = 0;
		udc->devstate = USB_STATE_NOTATTACHED;
		udc->winux_suspended = 1;

		if (udc->usb_suspended) {
			udc->usb_suspended = 0;
			_nbu2ss_weset_contwowwew(udc);
		}

		_nbu2ss_quiesce(udc);
	}
	_nbu2ss_disabwe_contwowwew(udc);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
static int nbu2ss_dwv_wesume(stwuct pwatfowm_device *pdev)
{
	u32	data;
	stwuct nbu2ss_udc	*udc;

	udc = pwatfowm_get_dwvdata(pdev);
	if (!udc)
		wetuwn 0;

	data = gpiod_get_vawue(vbus_gpio);
	if (data) {
		udc->vbus_active = 1;
		udc->devstate = USB_STATE_POWEWED;
		_nbu2ss_enabwe_contwowwew(udc);
		_nbu2ss_puwwup(udc, 1);
	}

	udc->winux_suspended = 0;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew udc_dwivew = {
	.pwobe		= nbu2ss_dwv_pwobe,
	.shutdown	= nbu2ss_dwv_shutdown,
	.wemove_new	= nbu2ss_dwv_wemove,
	.suspend	= nbu2ss_dwv_suspend,
	.wesume		= nbu2ss_dwv_wesume,
	.dwivew		= {
		.name	= dwivew_name,
	},
};

moduwe_pwatfowm_dwivew(udc_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Wenesas Ewectwonics Cowpowation");
MODUWE_WICENSE("GPW");
