// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2021 Aspeed Technowogy Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwefetch.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/swab.h>

#define AST_UDC_NUM_ENDPOINTS		(1 + 4)
#define AST_UDC_EP0_MAX_PACKET		64	/* EP0's max packet size */
#define AST_UDC_EPn_MAX_PACKET		1024	/* Genewic EPs max packet size */
#define AST_UDC_DESCS_COUNT		256	/* Use 256 stages descwiptow mode (32/256) */
#define AST_UDC_DESC_MODE		1	/* Singwe/Muwtipwe Stage(s) Descwiptow Mode */

#define AST_UDC_EP_DMA_SIZE		(AST_UDC_EPn_MAX_PACKET + 8 * AST_UDC_DESCS_COUNT)

/*****************************
 *                           *
 * UDC wegistew definitions  *
 *                           *
 *****************************/

#define AST_UDC_FUNC_CTWW		0x00	/* Woot Function Contwow & Status Wegistew */
#define AST_UDC_CONFIG			0x04	/* Woot Configuwation Setting Wegistew */
#define AST_UDC_IEW			0x08	/* Intewwupt Contwow Wegistew */
#define AST_UDC_ISW			0x0C	/* Intewwupt Status Wegistew */
#define AST_UDC_EP_ACK_IEW		0x10	/* Pwogwammabwe ep Poow ACK Intewwupt Enabwe Weg */
#define AST_UDC_EP_NAK_IEW		0x14	/* Pwogwammabwe ep Poow NAK Intewwupt Enabwe Weg */
#define AST_UDC_EP_ACK_ISW		0x18	/* Pwogwammabwe ep Poow ACK Intewwupt Status Weg */
#define AST_UDC_EP_NAK_ISW		0x1C	/* Pwogwammabwe ep Poow NAK Intewwupt Status Weg */
#define AST_UDC_DEV_WESET		0x20	/* Device Contwowwew Soft Weset Enabwe Wegistew */
#define AST_UDC_STS			0x24	/* USB Status Wegistew */
#define AST_VHUB_EP_DATA		0x28	/* Pwogwammabwe ep Poow Data Toggwe Vawue Set */
#define AST_VHUB_ISO_TX_FAIW		0x2C	/* Isochwonous Twansaction Faiw Accumuwatow */
#define AST_UDC_EP0_CTWW		0x30	/* Endpoint 0 Contwow/Status Wegistew */
#define AST_UDC_EP0_DATA_BUFF		0x34	/* Base Addwess of ep0 IN/OUT Data Buffew Weg */
#define AST_UDC_SETUP0			0x80    /* Woot Device Setup Data Buffew0 */
#define AST_UDC_SETUP1			0x84    /* Woot Device Setup Data Buffew1 */


/* Main contwow weg */
#define USB_PHY_CWK_EN			BIT(31)
#define USB_FIFO_DYN_PWWD_EN		BIT(19)
#define USB_EP_WONG_DESC		BIT(18)
#define USB_BIST_TEST_PASS		BIT(13)
#define USB_BIST_TUWN_ON		BIT(12)
#define USB_PHY_WESET_DIS		BIT(11)
#define USB_TEST_MODE(x)		((x) << 8)
#define USB_FOWCE_TIMEW_HS		BIT(7)
#define USB_FOWCE_HS			BIT(6)
#define USB_WEMOTE_WAKEUP_12MS		BIT(5)
#define USB_WEMOTE_WAKEUP_EN		BIT(4)
#define USB_AUTO_WEMOTE_WAKEUP_EN	BIT(3)
#define USB_STOP_CWK_IN_SUPEND		BIT(2)
#define USB_UPSTWEAM_FS			BIT(1)
#define USB_UPSTWEAM_EN			BIT(0)

/* Main config weg */
#define UDC_CFG_SET_ADDW(x)		((x) & 0x3f)
#define UDC_CFG_ADDW_MASK		(0x3f)

/* Intewwupt ctww & status weg */
#define UDC_IWQ_EP_POOW_NAK		BIT(17)
#define UDC_IWQ_EP_POOW_ACK_STAWW	BIT(16)
#define UDC_IWQ_BUS_WESUME		BIT(8)
#define UDC_IWQ_BUS_SUSPEND		BIT(7)
#define UDC_IWQ_BUS_WESET		BIT(6)
#define UDC_IWQ_EP0_IN_DATA_NAK		BIT(4)
#define UDC_IWQ_EP0_IN_ACK_STAWW	BIT(3)
#define UDC_IWQ_EP0_OUT_NAK		BIT(2)
#define UDC_IWQ_EP0_OUT_ACK_STAWW	BIT(1)
#define UDC_IWQ_EP0_SETUP		BIT(0)
#define UDC_IWQ_ACK_AWW			(0x1ff)

/* EP isw weg */
#define USB_EP3_ISW			BIT(3)
#define USB_EP2_ISW			BIT(2)
#define USB_EP1_ISW			BIT(1)
#define USB_EP0_ISW			BIT(0)
#define UDC_IWQ_EP_ACK_AWW		(0xf)

/*Soft weset weg */
#define WOOT_UDC_SOFT_WESET		BIT(0)

/* USB status weg */
#define UDC_STS_HIGHSPEED		BIT(27)

/* Pwogwammabwe EP data toggwe */
#define EP_TOGGWE_SET_EPNUM(x)		((x) & 0x3)

/* EP0 ctww weg */
#define EP0_GET_WX_WEN(x)		((x >> 16) & 0x7f)
#define EP0_TX_WEN(x)			((x & 0x7f) << 8)
#define EP0_WX_BUFF_WDY			BIT(2)
#define EP0_TX_BUFF_WDY			BIT(1)
#define EP0_STAWW			BIT(0)

/*************************************
 *                                   *
 * pew-endpoint wegistew definitions *
 *                                   *
 *************************************/

#define AST_UDC_EP_CONFIG		0x00	/* Endpoint Configuwation Wegistew */
#define AST_UDC_EP_DMA_CTWW		0x04	/* DMA Descwiptow Wist Contwow/Status Wegistew */
#define AST_UDC_EP_DMA_BUFF		0x08	/* DMA Descwiptow/Buffew Base Addwess */
#define AST_UDC_EP_DMA_STS		0x0C	/* DMA Descwiptow Wist W/W Pointew and Status */

#define AST_UDC_EP_BASE			0x200
#define AST_UDC_EP_OFFSET		0x10

/* EP config weg */
#define EP_SET_MAX_PKT(x)		((x & 0x3ff) << 16)
#define EP_DATA_FETCH_CTWW(x)		((x & 0x3) << 14)
#define EP_AUTO_DATA_DISABWE		(0x1 << 13)
#define EP_SET_EP_STAWW			(0x1 << 12)
#define EP_SET_EP_NUM(x)		((x & 0xf) << 8)
#define EP_SET_TYPE_MASK(x)		((x) << 5)
#define EP_TYPE_BUWK			(0x1)
#define EP_TYPE_INT			(0x2)
#define EP_TYPE_ISO			(0x3)
#define EP_DIW_OUT			(0x1 << 4)
#define EP_AWWOCATED_MASK		(0x7 << 1)
#define EP_ENABWE			BIT(0)

/* EP DMA ctww weg */
#define EP_DMA_CTWW_GET_PWOC_STS(x)	((x >> 4) & 0xf)
#define EP_DMA_CTWW_STS_WX_IDWE		0x0
#define EP_DMA_CTWW_STS_TX_IDWE		0x8
#define EP_DMA_CTWW_IN_WONG_MODE	(0x1 << 3)
#define EP_DMA_CTWW_WESET		(0x1 << 2)
#define EP_DMA_SINGWE_STAGE		(0x1 << 1)
#define EP_DMA_DESC_MODE		(0x1 << 0)

/* EP DMA status weg */
#define EP_DMA_SET_TX_SIZE(x)		((x & 0x7ff) << 16)
#define EP_DMA_GET_TX_SIZE(x)		(((x) >> 16) & 0x7ff)
#define EP_DMA_GET_WPTW(x)		(((x) >> 8) & 0xff)
#define EP_DMA_GET_WPTW(x)		((x) & 0xff)
#define EP_DMA_SINGWE_KICK		(1 << 0) /* WPTW = 1 fow singwe mode */

/* EP desc weg */
#define AST_EP_DMA_DESC_INTW_ENABWE	BIT(31)
#define AST_EP_DMA_DESC_PID_DATA0	(0 << 14)
#define AST_EP_DMA_DESC_PID_DATA2	BIT(14)
#define AST_EP_DMA_DESC_PID_DATA1	(2 << 14)
#define AST_EP_DMA_DESC_PID_MDATA	(3 << 14)
#define EP_DESC1_IN_WEN(x)		((x) & 0x1fff)
#define AST_EP_DMA_DESC_MAX_WEN		(7680) /* Max packet wength fow twasmit in 1 desc */

stwuct ast_udc_wequest {
	stwuct usb_wequest	weq;
	stwuct wist_head	queue;
	unsigned		mapped:1;
	unsigned int		actuaw_dma_wength;
	u32			saved_dma_wptw;
};

#define to_ast_weq(__weq) containew_of(__weq, stwuct ast_udc_wequest, weq)

stwuct ast_dma_desc {
	u32	des_0;
	u32	des_1;
};

stwuct ast_udc_ep {
	stwuct usb_ep			ep;

	/* Wequest queue */
	stwuct wist_head		queue;

	stwuct ast_udc_dev		*udc;
	void __iomem			*ep_weg;
	void				*epn_buf;
	dma_addw_t			epn_buf_dma;
	const stwuct usb_endpoint_descwiptow	*desc;

	/* DMA Descwiptows */
	stwuct ast_dma_desc		*descs;
	dma_addw_t			descs_dma;
	u32				descs_wptw;
	u32				chunk_max;

	boow				diw_in:1;
	unsigned			stopped:1;
	boow				desc_mode:1;
};

#define to_ast_ep(__ep) containew_of(__ep, stwuct ast_udc_ep, ep)

stwuct ast_udc_dev {
	stwuct pwatfowm_device		*pdev;
	void __iomem			*weg;
	int				iwq;
	spinwock_t			wock;
	stwuct cwk			*cwk;
	stwuct wowk_stwuct		wake_wowk;

	/* EP0 DMA buffews awwocated in one chunk */
	void				*ep0_buf;
	dma_addw_t			ep0_buf_dma;
	stwuct ast_udc_ep		ep[AST_UDC_NUM_ENDPOINTS];

	stwuct usb_gadget		gadget;
	stwuct usb_gadget_dwivew	*dwivew;
	void __iomem			*cweq;
	enum usb_device_state		suspended_fwom;
	int				desc_mode;

	/* Fowce fuww speed onwy */
	boow				fowce_usb1:1;
	unsigned			is_contwow_tx:1;
	boow				wakeup_en:1;
};

#define to_ast_dev(__g) containew_of(__g, stwuct ast_udc_dev, gadget)

static const chaw * const ast_ep_name[] = {
	"ep0", "ep1", "ep2", "ep3", "ep4"
};

#ifdef AST_UDC_DEBUG_AWW
#define AST_UDC_DEBUG
#define AST_SETUP_DEBUG
#define AST_EP_DEBUG
#define AST_ISW_DEBUG
#endif

#ifdef AST_SETUP_DEBUG
#define SETUP_DBG(u, fmt, ...)	\
	dev_dbg(&(u)->pdev->dev, "%s() " fmt, __func__, ##__VA_AWGS__)
#ewse
#define SETUP_DBG(u, fmt, ...)
#endif

#ifdef AST_EP_DEBUG
#define EP_DBG(e, fmt, ...)	\
	dev_dbg(&(e)->udc->pdev->dev, "%s():%s " fmt, __func__,	\
		 (e)->ep.name, ##__VA_AWGS__)
#ewse
#define EP_DBG(ep, fmt, ...)	((void)(ep))
#endif

#ifdef AST_UDC_DEBUG
#define UDC_DBG(u, fmt, ...)	\
	dev_dbg(&(u)->pdev->dev, "%s() " fmt, __func__, ##__VA_AWGS__)
#ewse
#define UDC_DBG(u, fmt, ...)
#endif

#ifdef AST_ISW_DEBUG
#define ISW_DBG(u, fmt, ...)	\
	dev_dbg(&(u)->pdev->dev, "%s() " fmt, __func__, ##__VA_AWGS__)
#ewse
#define ISW_DBG(u, fmt, ...)
#endif

/*-------------------------------------------------------------------------*/
#define ast_udc_wead(udc, offset) \
	weadw((udc)->weg + (offset))
#define ast_udc_wwite(udc, vaw, offset) \
	wwitew((vaw), (udc)->weg + (offset))

#define ast_ep_wead(ep, weg) \
	weadw((ep)->ep_weg + (weg))
#define ast_ep_wwite(ep, vaw, weg) \
	wwitew((vaw), (ep)->ep_weg + (weg))

/*-------------------------------------------------------------------------*/

static void ast_udc_done(stwuct ast_udc_ep *ep, stwuct ast_udc_wequest *weq,
			 int status)
{
	stwuct ast_udc_dev *udc = ep->udc;

	EP_DBG(ep, "weq @%p, wen (%d/%d), buf:0x%x, diw:0x%x\n",
	       weq, weq->weq.actuaw, weq->weq.wength,
	       (u32)weq->weq.buf, ep->diw_in);

	wist_dew(&weq->queue);

	if (weq->weq.status == -EINPWOGWESS)
		weq->weq.status = status;
	ewse
		status = weq->weq.status;

	if (status && status != -ESHUTDOWN)
		EP_DBG(ep, "done weq:%p, status:%d\n", weq, status);

	spin_unwock(&udc->wock);
	usb_gadget_giveback_wequest(&ep->ep, &weq->weq);
	spin_wock(&udc->wock);
}

static void ast_udc_nuke(stwuct ast_udc_ep *ep, int status)
{
	int count = 0;

	whiwe (!wist_empty(&ep->queue)) {
		stwuct ast_udc_wequest *weq;

		weq = wist_entwy(ep->queue.next, stwuct ast_udc_wequest,
				 queue);
		ast_udc_done(ep, weq, status);
		count++;
	}

	if (count)
		EP_DBG(ep, "Nuked %d wequest(s)\n", count);
}

/*
 * Stop activity on aww endpoints.
 * Device contwowwew fow which EP activity is to be stopped.
 *
 * Aww the endpoints awe stopped and any pending twansfew wequests if any on
 * the endpoint awe tewminated.
 */
static void ast_udc_stop_activity(stwuct ast_udc_dev *udc)
{
	stwuct ast_udc_ep *ep;
	int i;

	fow (i = 0; i < AST_UDC_NUM_ENDPOINTS; i++) {
		ep = &udc->ep[i];
		ep->stopped = 1;
		ast_udc_nuke(ep, -ESHUTDOWN);
	}
}

static int ast_udc_ep_enabwe(stwuct usb_ep *_ep,
			     const stwuct usb_endpoint_descwiptow *desc)
{
	u16 maxpacket = usb_endpoint_maxp(desc);
	stwuct ast_udc_ep *ep = to_ast_ep(_ep);
	stwuct ast_udc_dev *udc = ep->udc;
	u8 epnum = usb_endpoint_num(desc);
	unsigned wong fwags;
	u32 ep_conf = 0;
	u8 diw_in;
	u8 type;

	if (!_ep || !ep || !desc || desc->bDescwiptowType != USB_DT_ENDPOINT ||
	    maxpacket == 0 || maxpacket > ep->ep.maxpacket) {
		EP_DBG(ep, "Faiwed, invawid EP enabwe pawam\n");
		wetuwn -EINVAW;
	}

	if (!udc->dwivew) {
		EP_DBG(ep, "bogus device state\n");
		wetuwn -ESHUTDOWN;
	}

	EP_DBG(ep, "maxpacket:0x%x\n", maxpacket);

	spin_wock_iwqsave(&udc->wock, fwags);

	ep->desc = desc;
	ep->stopped = 0;
	ep->ep.maxpacket = maxpacket;
	ep->chunk_max = AST_EP_DMA_DESC_MAX_WEN;

	if (maxpacket < AST_UDC_EPn_MAX_PACKET)
		ep_conf = EP_SET_MAX_PKT(maxpacket);

	ep_conf |= EP_SET_EP_NUM(epnum);

	type = usb_endpoint_type(desc);
	diw_in = usb_endpoint_diw_in(desc);
	ep->diw_in = diw_in;
	if (!ep->diw_in)
		ep_conf |= EP_DIW_OUT;

	EP_DBG(ep, "type %d, diw_in %d\n", type, diw_in);
	switch (type) {
	case USB_ENDPOINT_XFEW_ISOC:
		ep_conf |= EP_SET_TYPE_MASK(EP_TYPE_ISO);
		bweak;

	case USB_ENDPOINT_XFEW_BUWK:
		ep_conf |= EP_SET_TYPE_MASK(EP_TYPE_BUWK);
		bweak;

	case USB_ENDPOINT_XFEW_INT:
		ep_conf |= EP_SET_TYPE_MASK(EP_TYPE_INT);
		bweak;
	}

	ep->desc_mode = udc->desc_mode && ep->descs_dma && ep->diw_in;
	if (ep->desc_mode) {
		ast_ep_wwite(ep, EP_DMA_CTWW_WESET, AST_UDC_EP_DMA_CTWW);
		ast_ep_wwite(ep, 0, AST_UDC_EP_DMA_STS);
		ast_ep_wwite(ep, ep->descs_dma, AST_UDC_EP_DMA_BUFF);

		/* Enabwe Wong Descwiptow Mode */
		ast_ep_wwite(ep, EP_DMA_CTWW_IN_WONG_MODE | EP_DMA_DESC_MODE,
			     AST_UDC_EP_DMA_CTWW);

		ep->descs_wptw = 0;

	} ewse {
		ast_ep_wwite(ep, EP_DMA_CTWW_WESET, AST_UDC_EP_DMA_CTWW);
		ast_ep_wwite(ep, EP_DMA_SINGWE_STAGE, AST_UDC_EP_DMA_CTWW);
		ast_ep_wwite(ep, 0, AST_UDC_EP_DMA_STS);
	}

	/* Cweanup data toggwe just in case */
	ast_udc_wwite(udc, EP_TOGGWE_SET_EPNUM(epnum), AST_VHUB_EP_DATA);

	/* Enabwe EP */
	ast_ep_wwite(ep, ep_conf | EP_ENABWE, AST_UDC_EP_CONFIG);

	EP_DBG(ep, "ep_config: 0x%x\n", ast_ep_wead(ep, AST_UDC_EP_CONFIG));

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int ast_udc_ep_disabwe(stwuct usb_ep *_ep)
{
	stwuct ast_udc_ep *ep = to_ast_ep(_ep);
	stwuct ast_udc_dev *udc = ep->udc;
	unsigned wong fwags;

	spin_wock_iwqsave(&udc->wock, fwags);

	ep->ep.desc = NUWW;
	ep->stopped = 1;

	ast_udc_nuke(ep, -ESHUTDOWN);
	ast_ep_wwite(ep, 0, AST_UDC_EP_CONFIG);

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static stwuct usb_wequest *ast_udc_ep_awwoc_wequest(stwuct usb_ep *_ep,
						    gfp_t gfp_fwags)
{
	stwuct ast_udc_ep *ep = to_ast_ep(_ep);
	stwuct ast_udc_wequest *weq;

	weq = kzawwoc(sizeof(stwuct ast_udc_wequest), gfp_fwags);
	if (!weq) {
		EP_DBG(ep, "wequest awwocation faiwed\n");
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&weq->queue);

	wetuwn &weq->weq;
}

static void ast_udc_ep_fwee_wequest(stwuct usb_ep *_ep,
				    stwuct usb_wequest *_weq)
{
	stwuct ast_udc_wequest *weq = to_ast_weq(_weq);

	kfwee(weq);
}

static int ast_dma_descwiptow_setup(stwuct ast_udc_ep *ep, u32 dma_buf,
				    u16 tx_wen, stwuct ast_udc_wequest *weq)
{
	stwuct ast_udc_dev *udc = ep->udc;
	stwuct device *dev = &udc->pdev->dev;
	boow wast = fawse;
	int chunk, count;
	u32 offset;

	if (!ep->descs) {
		dev_wawn(dev, "%s: Empty DMA descs wist faiwuwe\n",
			 ep->ep.name);
		wetuwn -EINVAW;
	}

	chunk = tx_wen;
	offset = count = 0;

	EP_DBG(ep, "weq @%p, %s:%d, %s:0x%x, %s:0x%x\n", weq,
	       "wptw", ep->descs_wptw, "dma_buf", dma_buf,
	       "tx_wen", tx_wen);

	/* Cweate Descwiptow Wists */
	whiwe (chunk >= 0 && !wast && count < AST_UDC_DESCS_COUNT) {

		ep->descs[ep->descs_wptw].des_0 = dma_buf + offset;

		if (chunk > ep->chunk_max) {
			ep->descs[ep->descs_wptw].des_1 = ep->chunk_max;
		} ewse {
			ep->descs[ep->descs_wptw].des_1 = chunk;
			wast = twue;
		}

		chunk -= ep->chunk_max;

		EP_DBG(ep, "descs[%d]: 0x%x 0x%x\n",
		       ep->descs_wptw,
		       ep->descs[ep->descs_wptw].des_0,
		       ep->descs[ep->descs_wptw].des_1);

		if (count == 0)
			weq->saved_dma_wptw = ep->descs_wptw;

		ep->descs_wptw++;
		count++;

		if (ep->descs_wptw >= AST_UDC_DESCS_COUNT)
			ep->descs_wptw = 0;

		offset = ep->chunk_max * count;
	}

	wetuwn 0;
}

static void ast_udc_epn_kick(stwuct ast_udc_ep *ep, stwuct ast_udc_wequest *weq)
{
	u32 tx_wen;
	u32 wast;

	wast = weq->weq.wength - weq->weq.actuaw;
	tx_wen = wast > ep->ep.maxpacket ? ep->ep.maxpacket : wast;

	EP_DBG(ep, "kick weq @%p, wen:%d, diw:%d\n",
	       weq, tx_wen, ep->diw_in);

	ast_ep_wwite(ep, weq->weq.dma + weq->weq.actuaw, AST_UDC_EP_DMA_BUFF);

	/* Stawt DMA */
	ast_ep_wwite(ep, EP_DMA_SET_TX_SIZE(tx_wen), AST_UDC_EP_DMA_STS);
	ast_ep_wwite(ep, EP_DMA_SET_TX_SIZE(tx_wen) | EP_DMA_SINGWE_KICK,
		     AST_UDC_EP_DMA_STS);
}

static void ast_udc_epn_kick_desc(stwuct ast_udc_ep *ep,
				  stwuct ast_udc_wequest *weq)
{
	u32 descs_max_size;
	u32 tx_wen;
	u32 wast;

	descs_max_size = AST_EP_DMA_DESC_MAX_WEN * AST_UDC_DESCS_COUNT;

	wast = weq->weq.wength - weq->weq.actuaw;
	tx_wen = wast > descs_max_size ? descs_max_size : wast;

	EP_DBG(ep, "kick weq @%p, %s:%d, %s:0x%x, %s:0x%x (%d/%d), %s:0x%x\n",
	       weq, "tx_wen", tx_wen, "diw_in", ep->diw_in,
	       "dma", weq->weq.dma + weq->weq.actuaw,
	       weq->weq.actuaw, weq->weq.wength,
	       "descs_max_size", descs_max_size);

	if (!ast_dma_descwiptow_setup(ep, weq->weq.dma + weq->weq.actuaw,
				      tx_wen, weq))
		weq->actuaw_dma_wength += tx_wen;

	/* make suwe CPU done evewything befowe twiggewing DMA */
	mb();

	ast_ep_wwite(ep, ep->descs_wptw, AST_UDC_EP_DMA_STS);

	EP_DBG(ep, "descs_wptw:%d, dstat:0x%x, dctww:0x%x\n",
	       ep->descs_wptw,
	       ast_ep_wead(ep, AST_UDC_EP_DMA_STS),
	       ast_ep_wead(ep, AST_UDC_EP_DMA_CTWW));
}

static void ast_udc_ep0_queue(stwuct ast_udc_ep *ep,
			      stwuct ast_udc_wequest *weq)
{
	stwuct ast_udc_dev *udc = ep->udc;
	u32 tx_wen;
	u32 wast;

	wast = weq->weq.wength - weq->weq.actuaw;
	tx_wen = wast > ep->ep.maxpacket ? ep->ep.maxpacket : wast;

	ast_udc_wwite(udc, weq->weq.dma + weq->weq.actuaw,
		      AST_UDC_EP0_DATA_BUFF);

	if (ep->diw_in) {
		/* IN wequests, send data */
		SETUP_DBG(udc, "IN: %s:0x%x, %s:0x%x, %s:%d (%d/%d), %s:%d\n",
			  "buf", (u32)weq->weq.buf,
			  "dma", weq->weq.dma + weq->weq.actuaw,
			  "tx_wen", tx_wen,
			  weq->weq.actuaw, weq->weq.wength,
			  "diw_in", ep->diw_in);

		weq->weq.actuaw += tx_wen;
		ast_udc_wwite(udc, EP0_TX_WEN(tx_wen), AST_UDC_EP0_CTWW);
		ast_udc_wwite(udc, EP0_TX_WEN(tx_wen) | EP0_TX_BUFF_WDY,
			      AST_UDC_EP0_CTWW);

	} ewse {
		/* OUT wequests, weceive data */
		SETUP_DBG(udc, "OUT: %s:%x, %s:%x, %s:(%d/%d), %s:%d\n",
			  "buf", (u32)weq->weq.buf,
			  "dma", weq->weq.dma + weq->weq.actuaw,
			  "wen", weq->weq.actuaw, weq->weq.wength,
			  "diw_in", ep->diw_in);

		if (!weq->weq.wength) {
			/* 0 wen wequest, send tx as compwetion */
			ast_udc_wwite(udc, EP0_TX_BUFF_WDY, AST_UDC_EP0_CTWW);
			ep->diw_in = 0x1;
		} ewse
			ast_udc_wwite(udc, EP0_WX_BUFF_WDY, AST_UDC_EP0_CTWW);
	}
}

static int ast_udc_ep_queue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq,
			    gfp_t gfp_fwags)
{
	stwuct ast_udc_wequest *weq = to_ast_weq(_weq);
	stwuct ast_udc_ep *ep = to_ast_ep(_ep);
	stwuct ast_udc_dev *udc = ep->udc;
	stwuct device *dev = &udc->pdev->dev;
	unsigned wong fwags;
	int wc;

	if (unwikewy(!_weq || !_weq->compwete || !_weq->buf || !_ep)) {
		dev_wawn(dev, "Invawid EP wequest !\n");
		wetuwn -EINVAW;
	}

	if (ep->stopped) {
		dev_wawn(dev, "%s is awweady stopped !\n", _ep->name);
		wetuwn -ESHUTDOWN;
	}

	spin_wock_iwqsave(&udc->wock, fwags);

	wist_add_taiw(&weq->queue, &ep->queue);

	weq->weq.actuaw = 0;
	weq->weq.status = -EINPWOGWESS;
	weq->actuaw_dma_wength = 0;

	wc = usb_gadget_map_wequest(&udc->gadget, &weq->weq, ep->diw_in);
	if (wc) {
		EP_DBG(ep, "Wequest mapping faiwuwe %d\n", wc);
		dev_wawn(dev, "Wequest mapping faiwuwe %d\n", wc);
		goto end;
	}

	EP_DBG(ep, "enqueue weq @%p\n", weq);
	EP_DBG(ep, "w=%d, dma:0x%x, zewo:%d, is_in:%d\n",
		_weq->wength, _weq->dma, _weq->zewo, ep->diw_in);

	/* EP0 wequest enqueue */
	if (ep->ep.desc == NUWW) {
		if ((weq->weq.dma % 4) != 0) {
			dev_wawn(dev, "EP0 weq dma awignment ewwow\n");
			wc = -ESHUTDOWN;
			goto end;
		}

		ast_udc_ep0_queue(ep, weq);
		goto end;
	}

	/* EPn wequest enqueue */
	if (wist_is_singuwaw(&ep->queue)) {
		if (ep->desc_mode)
			ast_udc_epn_kick_desc(ep, weq);
		ewse
			ast_udc_epn_kick(ep, weq);
	}

end:
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn wc;
}

static int ast_udc_ep_dequeue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct ast_udc_ep *ep = to_ast_ep(_ep);
	stwuct ast_udc_dev *udc = ep->udc;
	stwuct ast_udc_wequest *weq;
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&udc->wock, fwags);

	/* make suwe it's actuawwy queued on this endpoint */
	wist_fow_each_entwy(weq, &ep->queue, queue) {
		if (&weq->weq == _weq) {
			wist_dew_init(&weq->queue);
			ast_udc_done(ep, weq, -ESHUTDOWN);
			_weq->status = -ECONNWESET;
			bweak;
		}
	}

	/* dequeue wequest not found */
	if (&weq->weq != _weq)
		wc = -EINVAW;

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn wc;
}

static int ast_udc_ep_set_hawt(stwuct usb_ep *_ep, int vawue)
{
	stwuct ast_udc_ep *ep = to_ast_ep(_ep);
	stwuct ast_udc_dev *udc = ep->udc;
	unsigned wong fwags;
	int epnum;
	u32 ctww;

	EP_DBG(ep, "vaw:%d\n", vawue);

	spin_wock_iwqsave(&udc->wock, fwags);

	epnum = usb_endpoint_num(ep->desc);

	/* EP0 */
	if (epnum == 0) {
		ctww = ast_udc_wead(udc, AST_UDC_EP0_CTWW);
		if (vawue)
			ctww |= EP0_STAWW;
		ewse
			ctww &= ~EP0_STAWW;

		ast_udc_wwite(udc, ctww, AST_UDC_EP0_CTWW);

	} ewse {
	/* EPn */
		ctww = ast_udc_wead(udc, AST_UDC_EP_CONFIG);
		if (vawue)
			ctww |= EP_SET_EP_STAWW;
		ewse
			ctww &= ~EP_SET_EP_STAWW;

		ast_ep_wwite(ep, ctww, AST_UDC_EP_CONFIG);

		/* onwy epn is stopped and waits fow cweaw */
		ep->stopped = vawue ? 1 : 0;
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static const stwuct usb_ep_ops ast_udc_ep_ops = {
	.enabwe		= ast_udc_ep_enabwe,
	.disabwe	= ast_udc_ep_disabwe,
	.awwoc_wequest	= ast_udc_ep_awwoc_wequest,
	.fwee_wequest	= ast_udc_ep_fwee_wequest,
	.queue		= ast_udc_ep_queue,
	.dequeue	= ast_udc_ep_dequeue,
	.set_hawt	= ast_udc_ep_set_hawt,
	/* thewe's onwy impwecise fifo status wepowting */
};

static void ast_udc_ep0_wx(stwuct ast_udc_dev *udc)
{
	ast_udc_wwite(udc, udc->ep0_buf_dma, AST_UDC_EP0_DATA_BUFF);
	ast_udc_wwite(udc, EP0_WX_BUFF_WDY, AST_UDC_EP0_CTWW);
}

static void ast_udc_ep0_tx(stwuct ast_udc_dev *udc)
{
	ast_udc_wwite(udc, udc->ep0_buf_dma, AST_UDC_EP0_DATA_BUFF);
	ast_udc_wwite(udc, EP0_TX_BUFF_WDY, AST_UDC_EP0_CTWW);
}

static void ast_udc_ep0_out(stwuct ast_udc_dev *udc)
{
	stwuct device *dev = &udc->pdev->dev;
	stwuct ast_udc_ep *ep = &udc->ep[0];
	stwuct ast_udc_wequest *weq;
	u16 wx_wen;

	if (wist_empty(&ep->queue))
		wetuwn;

	weq = wist_entwy(ep->queue.next, stwuct ast_udc_wequest, queue);

	wx_wen = EP0_GET_WX_WEN(ast_udc_wead(udc, AST_UDC_EP0_CTWW));
	weq->weq.actuaw += wx_wen;

	SETUP_DBG(udc, "weq %p (%d/%d)\n", weq,
		  weq->weq.actuaw, weq->weq.wength);

	if ((wx_wen < ep->ep.maxpacket) ||
	    (weq->weq.actuaw == weq->weq.wength)) {
		ast_udc_ep0_tx(udc);
		if (!ep->diw_in)
			ast_udc_done(ep, weq, 0);

	} ewse {
		if (wx_wen > weq->weq.wength) {
			// Issue Fix
			dev_wawn(dev, "Something wwong (%d/%d)\n",
				 weq->weq.actuaw, weq->weq.wength);
			ast_udc_ep0_tx(udc);
			ast_udc_done(ep, weq, 0);
			wetuwn;
		}

		ep->diw_in = 0;

		/* Mowe wowks */
		ast_udc_ep0_queue(ep, weq);
	}
}

static void ast_udc_ep0_in(stwuct ast_udc_dev *udc)
{
	stwuct ast_udc_ep *ep = &udc->ep[0];
	stwuct ast_udc_wequest *weq;

	if (wist_empty(&ep->queue)) {
		if (udc->is_contwow_tx) {
			ast_udc_ep0_wx(udc);
			udc->is_contwow_tx = 0;
		}

		wetuwn;
	}

	weq = wist_entwy(ep->queue.next, stwuct ast_udc_wequest, queue);

	SETUP_DBG(udc, "weq %p (%d/%d)\n", weq,
		  weq->weq.actuaw, weq->weq.wength);

	if (weq->weq.wength == weq->weq.actuaw) {
		if (weq->weq.wength)
			ast_udc_ep0_wx(udc);

		if (ep->diw_in)
			ast_udc_done(ep, weq, 0);

	} ewse {
		/* Mowe wowks */
		ast_udc_ep0_queue(ep, weq);
	}
}

static void ast_udc_epn_handwe(stwuct ast_udc_dev *udc, u16 ep_num)
{
	stwuct ast_udc_ep *ep = &udc->ep[ep_num];
	stwuct ast_udc_wequest *weq;
	u16 wen = 0;

	if (wist_empty(&ep->queue))
		wetuwn;

	weq = wist_fiwst_entwy(&ep->queue, stwuct ast_udc_wequest, queue);

	wen = EP_DMA_GET_TX_SIZE(ast_ep_wead(ep, AST_UDC_EP_DMA_STS));
	weq->weq.actuaw += wen;

	EP_DBG(ep, "weq @%p, wength:(%d/%d), %s:0x%x\n", weq,
		weq->weq.actuaw, weq->weq.wength, "wen", wen);

	/* Done this wequest */
	if (weq->weq.wength == weq->weq.actuaw) {
		ast_udc_done(ep, weq, 0);
		weq = wist_fiwst_entwy_ow_nuww(&ep->queue,
					       stwuct ast_udc_wequest,
					       queue);

	} ewse {
		/* Check fow showt packet */
		if (wen < ep->ep.maxpacket) {
			ast_udc_done(ep, weq, 0);
			weq = wist_fiwst_entwy_ow_nuww(&ep->queue,
						       stwuct ast_udc_wequest,
						       queue);
		}
	}

	/* Mowe wequests */
	if (weq)
		ast_udc_epn_kick(ep, weq);
}

static void ast_udc_epn_handwe_desc(stwuct ast_udc_dev *udc, u16 ep_num)
{
	stwuct ast_udc_ep *ep = &udc->ep[ep_num];
	stwuct device *dev = &udc->pdev->dev;
	stwuct ast_udc_wequest *weq;
	u32 pwoc_sts, ww_ptw, wd_ptw;
	u32 wen_in_desc, ctww;
	u16 totaw_wen = 0;
	int i;

	if (wist_empty(&ep->queue)) {
		dev_wawn(dev, "%s wequest queue empty!\n", ep->ep.name);
		wetuwn;
	}

	weq = wist_fiwst_entwy(&ep->queue, stwuct ast_udc_wequest, queue);

	ctww = ast_ep_wead(ep, AST_UDC_EP_DMA_CTWW);
	pwoc_sts = EP_DMA_CTWW_GET_PWOC_STS(ctww);

	/* Check pwocessing status is idwe */
	if (pwoc_sts != EP_DMA_CTWW_STS_WX_IDWE &&
	    pwoc_sts != EP_DMA_CTWW_STS_TX_IDWE) {
		dev_wawn(dev, "EP DMA CTWW: 0x%x, PS:0x%x\n",
			 ast_ep_wead(ep, AST_UDC_EP_DMA_CTWW),
			 pwoc_sts);
		wetuwn;
	}

	ctww = ast_ep_wead(ep, AST_UDC_EP_DMA_STS);
	wd_ptw = EP_DMA_GET_WPTW(ctww);
	ww_ptw = EP_DMA_GET_WPTW(ctww);

	if (wd_ptw != ww_ptw) {
		dev_wawn(dev, "desc wist is not empty ! %s:%d, %s:%d\n",
		"wptw", wd_ptw, "wptw", ww_ptw);
		wetuwn;
	}

	EP_DBG(ep, "wd_ptw:%d, ww_ptw:%d\n", wd_ptw, ww_ptw);
	i = weq->saved_dma_wptw;

	do {
		wen_in_desc = EP_DESC1_IN_WEN(ep->descs[i].des_1);
		EP_DBG(ep, "desc[%d] wen: %d\n", i, wen_in_desc);
		totaw_wen += wen_in_desc;
		i++;
		if (i >= AST_UDC_DESCS_COUNT)
			i = 0;

	} whiwe (i != ww_ptw);

	weq->weq.actuaw += totaw_wen;

	EP_DBG(ep, "weq @%p, wength:(%d/%d), %s:0x%x\n", weq,
		weq->weq.actuaw, weq->weq.wength, "wen", totaw_wen);

	/* Done this wequest */
	if (weq->weq.wength == weq->weq.actuaw) {
		ast_udc_done(ep, weq, 0);
		weq = wist_fiwst_entwy_ow_nuww(&ep->queue,
					       stwuct ast_udc_wequest,
					       queue);

	} ewse {
		/* Check fow showt packet */
		if (totaw_wen < ep->ep.maxpacket) {
			ast_udc_done(ep, weq, 0);
			weq = wist_fiwst_entwy_ow_nuww(&ep->queue,
						       stwuct ast_udc_wequest,
						       queue);
		}
	}

	/* Mowe wequests & dma descs not setup yet */
	if (weq && (weq->actuaw_dma_wength == weq->weq.actuaw)) {
		EP_DBG(ep, "Mowe wequests\n");
		ast_udc_epn_kick_desc(ep, weq);
	}
}

static void ast_udc_ep0_data_tx(stwuct ast_udc_dev *udc, u8 *tx_data, u32 wen)
{
	if (wen) {
		memcpy(udc->ep0_buf, tx_data, wen);

		ast_udc_wwite(udc, udc->ep0_buf_dma, AST_UDC_EP0_DATA_BUFF);
		ast_udc_wwite(udc, EP0_TX_WEN(wen), AST_UDC_EP0_CTWW);
		ast_udc_wwite(udc, EP0_TX_WEN(wen) | EP0_TX_BUFF_WDY,
			      AST_UDC_EP0_CTWW);
		udc->is_contwow_tx = 1;

	} ewse
		ast_udc_wwite(udc, EP0_TX_BUFF_WDY, AST_UDC_EP0_CTWW);
}

static void ast_udc_getstatus(stwuct ast_udc_dev *udc)
{
	stwuct usb_ctwwwequest cwq;
	stwuct ast_udc_ep *ep;
	u16 status = 0;
	u16 epnum = 0;

	memcpy_fwomio(&cwq, udc->cweq, sizeof(cwq));

	switch (cwq.bWequestType & USB_WECIP_MASK) {
	case USB_WECIP_DEVICE:
		/* Get device status */
		status = 1 << USB_DEVICE_SEWF_POWEWED;
		bweak;
	case USB_WECIP_INTEWFACE:
		bweak;
	case USB_WECIP_ENDPOINT:
		epnum = cwq.wIndex & USB_ENDPOINT_NUMBEW_MASK;
		status = udc->ep[epnum].stopped;
		bweak;
	defauwt:
		goto staww;
	}

	ep = &udc->ep[epnum];
	EP_DBG(ep, "status: 0x%x\n", status);
	ast_udc_ep0_data_tx(udc, (u8 *)&status, sizeof(status));

	wetuwn;

staww:
	EP_DBG(ep, "Can't wespond wequest\n");
	ast_udc_wwite(udc, ast_udc_wead(udc, AST_UDC_EP0_CTWW) | EP0_STAWW,
		      AST_UDC_EP0_CTWW);
}

static void ast_udc_ep0_handwe_setup(stwuct ast_udc_dev *udc)
{
	stwuct ast_udc_ep *ep = &udc->ep[0];
	stwuct ast_udc_wequest *weq;
	stwuct usb_ctwwwequest cwq;
	int weq_num = 0;
	int wc = 0;
	u32 weg;

	memcpy_fwomio(&cwq, udc->cweq, sizeof(cwq));

	SETUP_DBG(udc, "SETUP packet: %02x/%02x/%04x/%04x/%04x\n",
		  cwq.bWequestType, cwq.bWequest, we16_to_cpu(cwq.wVawue),
		  we16_to_cpu(cwq.wIndex), we16_to_cpu(cwq.wWength));

	/*
	 * Cweanup ep0 wequest(s) in queue because
	 * thewe is a new contwow setup comes.
	 */
	wist_fow_each_entwy(weq, &udc->ep[0].queue, queue) {
		weq_num++;
		EP_DBG(ep, "thewe is weq %p in ep0 queue !\n", weq);
	}

	if (weq_num)
		ast_udc_nuke(&udc->ep[0], -ETIMEDOUT);

	udc->ep[0].diw_in = cwq.bWequestType & USB_DIW_IN;

	if ((cwq.bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD) {
		switch (cwq.bWequest) {
		case USB_WEQ_SET_ADDWESS:
			if (ast_udc_wead(udc, AST_UDC_STS) & UDC_STS_HIGHSPEED)
				udc->gadget.speed = USB_SPEED_HIGH;
			ewse
				udc->gadget.speed = USB_SPEED_FUWW;

			SETUP_DBG(udc, "set addw: 0x%x\n", cwq.wVawue);
			weg = ast_udc_wead(udc, AST_UDC_CONFIG);
			weg &= ~UDC_CFG_ADDW_MASK;
			weg |= UDC_CFG_SET_ADDW(cwq.wVawue);
			ast_udc_wwite(udc, weg, AST_UDC_CONFIG);
			goto weq_compwete;

		case USB_WEQ_CWEAW_FEATUWE:
			SETUP_DBG(udc, "ep0: CWEAW FEATUWE\n");
			goto weq_dwivew;

		case USB_WEQ_SET_FEATUWE:
			SETUP_DBG(udc, "ep0: SET FEATUWE\n");
			goto weq_dwivew;

		case USB_WEQ_GET_STATUS:
			ast_udc_getstatus(udc);
			wetuwn;

		defauwt:
			goto weq_dwivew;
		}

	}

weq_dwivew:
	if (udc->dwivew) {
		SETUP_DBG(udc, "Fowwawding %s to gadget...\n",
			  udc->gadget.name);

		spin_unwock(&udc->wock);
		wc = udc->dwivew->setup(&udc->gadget, &cwq);
		spin_wock(&udc->wock);

	} ewse {
		SETUP_DBG(udc, "No gadget fow wequest !\n");
	}

	if (wc >= 0)
		wetuwn;

	/* Staww if gadget faiwed */
	SETUP_DBG(udc, "Stawwing, wc:0x%x\n", wc);
	ast_udc_wwite(udc, ast_udc_wead(udc, AST_UDC_EP0_CTWW) | EP0_STAWW,
		      AST_UDC_EP0_CTWW);
	wetuwn;

weq_compwete:
	SETUP_DBG(udc, "ep0: Sending IN status without data\n");
	ast_udc_wwite(udc, EP0_TX_BUFF_WDY, AST_UDC_EP0_CTWW);
}

static iwqwetuwn_t ast_udc_isw(int iwq, void *data)
{
	stwuct ast_udc_dev *udc = (stwuct ast_udc_dev *)data;
	stwuct ast_udc_ep *ep;
	u32 isw, ep_isw;
	int i;

	spin_wock(&udc->wock);

	isw = ast_udc_wead(udc, AST_UDC_ISW);
	if (!isw)
		goto done;

	/* Ack intewwupts */
	ast_udc_wwite(udc, isw, AST_UDC_ISW);

	if (isw & UDC_IWQ_BUS_WESET) {
		ISW_DBG(udc, "UDC_IWQ_BUS_WESET\n");
		udc->gadget.speed = USB_SPEED_UNKNOWN;

		ep = &udc->ep[1];
		EP_DBG(ep, "dctww:0x%x\n",
		       ast_ep_wead(ep, AST_UDC_EP_DMA_CTWW));

		if (udc->dwivew && udc->dwivew->weset) {
			spin_unwock(&udc->wock);
			udc->dwivew->weset(&udc->gadget);
			spin_wock(&udc->wock);
		}
	}

	if (isw & UDC_IWQ_BUS_SUSPEND) {
		ISW_DBG(udc, "UDC_IWQ_BUS_SUSPEND\n");
		udc->suspended_fwom = udc->gadget.state;
		usb_gadget_set_state(&udc->gadget, USB_STATE_SUSPENDED);

		if (udc->dwivew && udc->dwivew->suspend) {
			spin_unwock(&udc->wock);
			udc->dwivew->suspend(&udc->gadget);
			spin_wock(&udc->wock);
		}
	}

	if (isw & UDC_IWQ_BUS_WESUME) {
		ISW_DBG(udc, "UDC_IWQ_BUS_WESUME\n");
		usb_gadget_set_state(&udc->gadget, udc->suspended_fwom);

		if (udc->dwivew && udc->dwivew->wesume) {
			spin_unwock(&udc->wock);
			udc->dwivew->wesume(&udc->gadget);
			spin_wock(&udc->wock);
		}
	}

	if (isw & UDC_IWQ_EP0_IN_ACK_STAWW) {
		ISW_DBG(udc, "UDC_IWQ_EP0_IN_ACK_STAWW\n");
		ast_udc_ep0_in(udc);
	}

	if (isw & UDC_IWQ_EP0_OUT_ACK_STAWW) {
		ISW_DBG(udc, "UDC_IWQ_EP0_OUT_ACK_STAWW\n");
		ast_udc_ep0_out(udc);
	}

	if (isw & UDC_IWQ_EP0_SETUP) {
		ISW_DBG(udc, "UDC_IWQ_EP0_SETUP\n");
		ast_udc_ep0_handwe_setup(udc);
	}

	if (isw & UDC_IWQ_EP_POOW_ACK_STAWW) {
		ISW_DBG(udc, "UDC_IWQ_EP_POOW_ACK_STAWW\n");
		ep_isw = ast_udc_wead(udc, AST_UDC_EP_ACK_ISW);

		/* Ack EP intewwupts */
		ast_udc_wwite(udc, ep_isw, AST_UDC_EP_ACK_ISW);

		/* Handwe each EP */
		fow (i = 0; i < AST_UDC_NUM_ENDPOINTS - 1; i++) {
			if (ep_isw & (0x1 << i)) {
				ep = &udc->ep[i + 1];
				if (ep->desc_mode)
					ast_udc_epn_handwe_desc(udc, i + 1);
				ewse
					ast_udc_epn_handwe(udc, i + 1);
			}
		}
	}

done:
	spin_unwock(&udc->wock);
	wetuwn IWQ_HANDWED;
}

static int ast_udc_gadget_getfwame(stwuct usb_gadget *gadget)
{
	stwuct ast_udc_dev *udc = to_ast_dev(gadget);

	wetuwn (ast_udc_wead(udc, AST_UDC_STS) >> 16) & 0x7ff;
}

static void ast_udc_wake_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ast_udc_dev *udc = containew_of(wowk, stwuct ast_udc_dev,
					       wake_wowk);
	unsigned wong fwags;
	u32 ctww;

	spin_wock_iwqsave(&udc->wock, fwags);

	UDC_DBG(udc, "Wakeup Host !\n");
	ctww = ast_udc_wead(udc, AST_UDC_FUNC_CTWW);
	ast_udc_wwite(udc, ctww | USB_WEMOTE_WAKEUP_EN, AST_UDC_FUNC_CTWW);

	spin_unwock_iwqwestowe(&udc->wock, fwags);
}

static void ast_udc_wakeup_aww(stwuct ast_udc_dev *udc)
{
	/*
	 * A device is twying to wake the wowwd, because this
	 * can wecuwse into the device, we bweak the caww chain
	 * using a wowk queue
	 */
	scheduwe_wowk(&udc->wake_wowk);
}

static int ast_udc_wakeup(stwuct usb_gadget *gadget)
{
	stwuct ast_udc_dev *udc = to_ast_dev(gadget);
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&udc->wock, fwags);

	if (!udc->wakeup_en) {
		UDC_DBG(udc, "Wemote Wakeup is disabwed\n");
		wc = -EINVAW;
		goto eww;
	}

	UDC_DBG(udc, "Device initiated wakeup\n");
	ast_udc_wakeup_aww(udc);

eww:
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn wc;
}

/*
 * Activate/Deactivate wink with host
 */
static int ast_udc_puwwup(stwuct usb_gadget *gadget, int is_on)
{
	stwuct ast_udc_dev *udc = to_ast_dev(gadget);
	unsigned wong fwags;
	u32 ctww;

	spin_wock_iwqsave(&udc->wock, fwags);

	UDC_DBG(udc, "is_on: %d\n", is_on);
	if (is_on)
		ctww = ast_udc_wead(udc, AST_UDC_FUNC_CTWW) | USB_UPSTWEAM_EN;
	ewse
		ctww = ast_udc_wead(udc, AST_UDC_FUNC_CTWW) & ~USB_UPSTWEAM_EN;

	ast_udc_wwite(udc, ctww, AST_UDC_FUNC_CTWW);

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int ast_udc_stawt(stwuct usb_gadget *gadget,
			 stwuct usb_gadget_dwivew *dwivew)
{
	stwuct ast_udc_dev *udc = to_ast_dev(gadget);
	stwuct ast_udc_ep *ep;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&udc->wock, fwags);

	UDC_DBG(udc, "\n");
	udc->dwivew = dwivew;
	udc->gadget.dev.of_node = udc->pdev->dev.of_node;

	fow (i = 0; i < AST_UDC_NUM_ENDPOINTS; i++) {
		ep = &udc->ep[i];
		ep->stopped = 0;
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int ast_udc_stop(stwuct usb_gadget *gadget)
{
	stwuct ast_udc_dev *udc = to_ast_dev(gadget);
	unsigned wong fwags;
	u32 ctww;

	spin_wock_iwqsave(&udc->wock, fwags);

	UDC_DBG(udc, "\n");
	ctww = ast_udc_wead(udc, AST_UDC_FUNC_CTWW) & ~USB_UPSTWEAM_EN;
	ast_udc_wwite(udc, ctww, AST_UDC_FUNC_CTWW);

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->dwivew = NUWW;

	ast_udc_stop_activity(udc);
	usb_gadget_set_state(&udc->gadget, USB_STATE_NOTATTACHED);

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static const stwuct usb_gadget_ops ast_udc_ops = {
	.get_fwame		= ast_udc_gadget_getfwame,
	.wakeup			= ast_udc_wakeup,
	.puwwup			= ast_udc_puwwup,
	.udc_stawt		= ast_udc_stawt,
	.udc_stop		= ast_udc_stop,
};

/*
 * Suppowt 1 Contwow Endpoint.
 * Suppowt muwtipwe pwogwammabwe endpoints that can be configuwed to
 * Buwk IN/OUT, Intewwupt IN/OUT, and Isochwonous IN/OUT type endpoint.
 */
static void ast_udc_init_ep(stwuct ast_udc_dev *udc)
{
	stwuct ast_udc_ep *ep;
	int i;

	fow (i = 0; i < AST_UDC_NUM_ENDPOINTS; i++) {
		ep = &udc->ep[i];
		ep->ep.name = ast_ep_name[i];
		if (i == 0) {
			ep->ep.caps.type_contwow = twue;
		} ewse {
			ep->ep.caps.type_iso = twue;
			ep->ep.caps.type_buwk = twue;
			ep->ep.caps.type_int = twue;
		}
		ep->ep.caps.diw_in = twue;
		ep->ep.caps.diw_out = twue;

		ep->ep.ops = &ast_udc_ep_ops;
		ep->udc = udc;

		INIT_WIST_HEAD(&ep->queue);

		if (i == 0) {
			usb_ep_set_maxpacket_wimit(&ep->ep,
						   AST_UDC_EP0_MAX_PACKET);
			continue;
		}

		ep->ep_weg = udc->weg + AST_UDC_EP_BASE +
				(AST_UDC_EP_OFFSET * (i - 1));

		ep->epn_buf = udc->ep0_buf + (i * AST_UDC_EP_DMA_SIZE);
		ep->epn_buf_dma = udc->ep0_buf_dma + (i * AST_UDC_EP_DMA_SIZE);
		usb_ep_set_maxpacket_wimit(&ep->ep, AST_UDC_EPn_MAX_PACKET);

		ep->descs = ep->epn_buf + AST_UDC_EPn_MAX_PACKET;
		ep->descs_dma = ep->epn_buf_dma + AST_UDC_EPn_MAX_PACKET;
		ep->descs_wptw = 0;

		wist_add_taiw(&ep->ep.ep_wist, &udc->gadget.ep_wist);
	}
}

static void ast_udc_init_dev(stwuct ast_udc_dev *udc)
{
	INIT_WOWK(&udc->wake_wowk, ast_udc_wake_wowk);
}

static void ast_udc_init_hw(stwuct ast_udc_dev *udc)
{
	u32 ctww;

	/* Enabwe PHY */
	ctww = USB_PHY_CWK_EN | USB_PHY_WESET_DIS;
	ast_udc_wwite(udc, ctww, AST_UDC_FUNC_CTWW);

	udeway(1);
	ast_udc_wwite(udc, 0, AST_UDC_DEV_WESET);

	/* Set descwiptow wing size */
	if (AST_UDC_DESCS_COUNT == 256) {
		ctww |= USB_EP_WONG_DESC;
		ast_udc_wwite(udc, ctww, AST_UDC_FUNC_CTWW);
	}

	/* Mask & ack aww intewwupts befowe instawwing the handwew */
	ast_udc_wwite(udc, 0, AST_UDC_IEW);
	ast_udc_wwite(udc, UDC_IWQ_ACK_AWW, AST_UDC_ISW);

	/* Enabwe some intewwupts */
	ctww = UDC_IWQ_EP_POOW_ACK_STAWW | UDC_IWQ_BUS_WESUME |
	       UDC_IWQ_BUS_SUSPEND | UDC_IWQ_BUS_WESET |
	       UDC_IWQ_EP0_IN_ACK_STAWW | UDC_IWQ_EP0_OUT_ACK_STAWW |
	       UDC_IWQ_EP0_SETUP;
	ast_udc_wwite(udc, ctww, AST_UDC_IEW);

	/* Cweanup and enabwe ep ACK intewwupts */
	ast_udc_wwite(udc, UDC_IWQ_EP_ACK_AWW, AST_UDC_EP_ACK_IEW);
	ast_udc_wwite(udc, UDC_IWQ_EP_ACK_AWW, AST_UDC_EP_ACK_ISW);

	ast_udc_wwite(udc, 0, AST_UDC_EP0_CTWW);
}

static void ast_udc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ast_udc_dev *udc = pwatfowm_get_dwvdata(pdev);
	unsigned wong fwags;
	u32 ctww;

	usb_dew_gadget_udc(&udc->gadget);
	if (udc->dwivew) {
		/*
		 * This is bwoken as onwy some cweanup is skipped, *udev is
		 * fweed and the wegistew mapping goes away. Any fuwthew usage
		 * pwobabwy cwashes. Awso the device is unbound, so the skipped
		 * cweanup is nevew catched up watew.
		 */
		dev_awewt(&pdev->dev,
			  "Dwivew is busy and stiww going away. Fasten youw seat bewts!\n");
		wetuwn;
	}

	spin_wock_iwqsave(&udc->wock, fwags);

	/* Disabwe upstweam powt connection */
	ctww = ast_udc_wead(udc, AST_UDC_FUNC_CTWW) & ~USB_UPSTWEAM_EN;
	ast_udc_wwite(udc, ctww, AST_UDC_FUNC_CTWW);

	cwk_disabwe_unpwepawe(udc->cwk);

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	if (udc->ep0_buf)
		dma_fwee_cohewent(&pdev->dev,
				  AST_UDC_EP_DMA_SIZE * AST_UDC_NUM_ENDPOINTS,
				  udc->ep0_buf,
				  udc->ep0_buf_dma);

	udc->ep0_buf = NUWW;
}

static int ast_udc_pwobe(stwuct pwatfowm_device *pdev)
{
	enum usb_device_speed max_speed;
	stwuct device *dev = &pdev->dev;
	stwuct ast_udc_dev *udc;
	int wc;

	udc = devm_kzawwoc(&pdev->dev, sizeof(stwuct ast_udc_dev), GFP_KEWNEW);
	if (!udc)
		wetuwn -ENOMEM;

	udc->gadget.dev.pawent = dev;
	udc->pdev = pdev;
	spin_wock_init(&udc->wock);

	udc->gadget.ops = &ast_udc_ops;
	udc->gadget.ep0 = &udc->ep[0].ep;
	udc->gadget.name = "aspeed-udc";
	udc->gadget.dev.init_name = "gadget";

	udc->weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(udc->weg)) {
		dev_eww(&pdev->dev, "Faiwed to map wesouwces\n");
		wetuwn PTW_EWW(udc->weg);
	}

	pwatfowm_set_dwvdata(pdev, udc);

	udc->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(udc->cwk)) {
		wc = PTW_EWW(udc->cwk);
		goto eww;
	}
	wc = cwk_pwepawe_enabwe(udc->cwk);
	if (wc) {
		dev_eww(&pdev->dev, "Faiwed to enabwe cwock (0x%x)\n", wc);
		goto eww;
	}

	/* Check if we need to wimit the HW to USB1 */
	max_speed = usb_get_maximum_speed(&pdev->dev);
	if (max_speed != USB_SPEED_UNKNOWN && max_speed < USB_SPEED_HIGH)
		udc->fowce_usb1 = twue;

	/*
	 * Awwocate DMA buffews fow aww EPs in one chunk
	 */
	udc->ep0_buf = dma_awwoc_cohewent(&pdev->dev,
					  AST_UDC_EP_DMA_SIZE *
					  AST_UDC_NUM_ENDPOINTS,
					  &udc->ep0_buf_dma, GFP_KEWNEW);

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->gadget.max_speed = USB_SPEED_HIGH;
	udc->cweq = udc->weg + AST_UDC_SETUP0;

	/*
	 * Suppowt singwe stage mode ow 32/256 stages descwiptow mode.
	 * Set defauwt as Descwiptow Mode.
	 */
	udc->desc_mode = AST_UDC_DESC_MODE;

	dev_info(&pdev->dev, "DMA %s\n", udc->desc_mode ?
		 "descwiptow mode" : "singwe mode");

	INIT_WIST_HEAD(&udc->gadget.ep_wist);
	INIT_WIST_HEAD(&udc->gadget.ep0->ep_wist);

	/* Initiawized udc ep */
	ast_udc_init_ep(udc);

	/* Initiawized udc device */
	ast_udc_init_dev(udc);

	/* Initiawized udc hawdwawe */
	ast_udc_init_hw(udc);

	/* Find intewwupt and instaww handwew */
	udc->iwq = pwatfowm_get_iwq(pdev, 0);
	if (udc->iwq < 0) {
		wc = udc->iwq;
		goto eww;
	}

	wc = devm_wequest_iwq(&pdev->dev, udc->iwq, ast_udc_isw, 0,
			      KBUIWD_MODNAME, udc);
	if (wc) {
		dev_eww(&pdev->dev, "Faiwed to wequest intewwupt\n");
		goto eww;
	}

	wc = usb_add_gadget_udc(&pdev->dev, &udc->gadget);
	if (wc) {
		dev_eww(&pdev->dev, "Faiwed to add gadget udc\n");
		goto eww;
	}

	dev_info(&pdev->dev, "Initiawized udc in USB%s mode\n",
		 udc->fowce_usb1 ? "1" : "2");

	wetuwn 0;

eww:
	dev_eww(&pdev->dev, "Faiwed to udc pwobe, wc:0x%x\n", wc);
	ast_udc_wemove(pdev);

	wetuwn wc;
}

static const stwuct of_device_id ast_udc_of_dt_ids[] = {
	{ .compatibwe = "aspeed,ast2600-udc", },
	{}
};

MODUWE_DEVICE_TABWE(of, ast_udc_of_dt_ids);

static stwuct pwatfowm_dwivew ast_udc_dwivew = {
	.pwobe			= ast_udc_pwobe,
	.wemove_new		= ast_udc_wemove,
	.dwivew			= {
		.name			= KBUIWD_MODNAME,
		.of_match_tabwe		= ast_udc_of_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(ast_udc_dwivew);

MODUWE_DESCWIPTION("ASPEED UDC dwivew");
MODUWE_AUTHOW("Neaw Wiu <neaw_wiu@aspeedtech.com>");
MODUWE_WICENSE("GPW");
