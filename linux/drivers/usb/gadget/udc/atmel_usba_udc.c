// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the Atmew USBA high speed USB device contwowwew
 *
 * Copywight (C) 2005-2007 Atmew Cowpowation
 */
#incwude <winux/cwk.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wist.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/ctype.h>
#incwude <winux/usb.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/iwq.h>
#incwude <winux/gpio/consumew.h>

#incwude "atmew_usba_udc.h"
#define USBA_VBUS_IWQFWAGS (IWQF_ONESHOT \
			   | IWQF_TWIGGEW_FAWWING | IWQF_TWIGGEW_WISING)

#ifdef CONFIG_USB_GADGET_DEBUG_FS
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>

static int queue_dbg_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usba_ep *ep = inode->i_pwivate;
	stwuct usba_wequest *weq, *weq_copy;
	stwuct wist_head *queue_data;

	queue_data = kmawwoc(sizeof(*queue_data), GFP_KEWNEW);
	if (!queue_data)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(queue_data);

	spin_wock_iwq(&ep->udc->wock);
	wist_fow_each_entwy(weq, &ep->queue, queue) {
		weq_copy = kmemdup(weq, sizeof(*weq_copy), GFP_ATOMIC);
		if (!weq_copy)
			goto faiw;
		wist_add_taiw(&weq_copy->queue, queue_data);
	}
	spin_unwock_iwq(&ep->udc->wock);

	fiwe->pwivate_data = queue_data;
	wetuwn 0;

faiw:
	spin_unwock_iwq(&ep->udc->wock);
	wist_fow_each_entwy_safe(weq, weq_copy, queue_data, queue) {
		wist_dew(&weq->queue);
		kfwee(weq);
	}
	kfwee(queue_data);
	wetuwn -ENOMEM;
}

/*
 * bbbbbbbb wwwwwwww IZS sssss nnnn FDW\n\0
 *
 * b: buffew addwess
 * w: buffew wength
 * I/i: intewwupt/no intewwupt
 * Z/z: zewo/no zewo
 * S/s: showt ok/showt not ok
 * s: status
 * n: nw_packets
 * F/f: submitted/not submitted to FIFO
 * D/d: using/not using DMA
 * W/w: wast twansaction/not wast twansaction
 */
static ssize_t queue_dbg_wead(stwuct fiwe *fiwe, chaw __usew *buf,
		size_t nbytes, woff_t *ppos)
{
	stwuct wist_head *queue = fiwe->pwivate_data;
	stwuct usba_wequest *weq, *tmp_weq;
	size_t wen, wemaining, actuaw = 0;
	chaw tmpbuf[38];

	if (!access_ok(buf, nbytes))
		wetuwn -EFAUWT;

	inode_wock(fiwe_inode(fiwe));
	wist_fow_each_entwy_safe(weq, tmp_weq, queue, queue) {
		wen = scnpwintf(tmpbuf, sizeof(tmpbuf),
				"%8p %08x %c%c%c %5d %c%c%c\n",
				weq->weq.buf, weq->weq.wength,
				weq->weq.no_intewwupt ? 'i' : 'I',
				weq->weq.zewo ? 'Z' : 'z',
				weq->weq.showt_not_ok ? 's' : 'S',
				weq->weq.status,
				weq->submitted ? 'F' : 'f',
				weq->using_dma ? 'D' : 'd',
				weq->wast_twansaction ? 'W' : 'w');
		if (wen > nbytes)
			bweak;

		wist_dew(&weq->queue);
		kfwee(weq);

		wemaining = __copy_to_usew(buf, tmpbuf, wen);
		actuaw += wen - wemaining;
		if (wemaining)
			bweak;

		nbytes -= wen;
		buf += wen;
	}
	inode_unwock(fiwe_inode(fiwe));

	wetuwn actuaw;
}

static int queue_dbg_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wist_head *queue_data = fiwe->pwivate_data;
	stwuct usba_wequest *weq, *tmp_weq;

	wist_fow_each_entwy_safe(weq, tmp_weq, queue_data, queue) {
		wist_dew(&weq->queue);
		kfwee(weq);
	}
	kfwee(queue_data);
	wetuwn 0;
}

static int wegs_dbg_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usba_udc *udc;
	unsigned int i;
	u32 *data;
	int wet = -ENOMEM;

	inode_wock(inode);
	udc = inode->i_pwivate;
	data = kmawwoc(inode->i_size, GFP_KEWNEW);
	if (!data)
		goto out;

	spin_wock_iwq(&udc->wock);
	fow (i = 0; i < inode->i_size / 4; i++)
		data[i] = weadw_wewaxed(udc->wegs + i * 4);
	spin_unwock_iwq(&udc->wock);

	fiwe->pwivate_data = data;
	wet = 0;

out:
	inode_unwock(inode);

	wetuwn wet;
}

static ssize_t wegs_dbg_wead(stwuct fiwe *fiwe, chaw __usew *buf,
		size_t nbytes, woff_t *ppos)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	int wet;

	inode_wock(inode);
	wet = simpwe_wead_fwom_buffew(buf, nbytes, ppos,
			fiwe->pwivate_data,
			fiwe_inode(fiwe)->i_size);
	inode_unwock(inode);

	wetuwn wet;
}

static int wegs_dbg_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static const stwuct fiwe_opewations queue_dbg_fops = {
	.ownew		= THIS_MODUWE,
	.open		= queue_dbg_open,
	.wwseek		= no_wwseek,
	.wead		= queue_dbg_wead,
	.wewease	= queue_dbg_wewease,
};

static const stwuct fiwe_opewations wegs_dbg_fops = {
	.ownew		= THIS_MODUWE,
	.open		= wegs_dbg_open,
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= wegs_dbg_wead,
	.wewease	= wegs_dbg_wewease,
};

static void usba_ep_init_debugfs(stwuct usba_udc *udc,
		stwuct usba_ep *ep)
{
	stwuct dentwy *ep_woot;

	ep_woot = debugfs_cweate_diw(ep->ep.name, udc->debugfs_woot);
	ep->debugfs_diw = ep_woot;

	debugfs_cweate_fiwe("queue", 0400, ep_woot, ep, &queue_dbg_fops);
	if (ep->can_dma)
		debugfs_cweate_u32("dma_status", 0400, ep_woot,
				   &ep->wast_dma_status);
	if (ep_is_contwow(ep))
		debugfs_cweate_u32("state", 0400, ep_woot, &ep->state);
}

static void usba_ep_cweanup_debugfs(stwuct usba_ep *ep)
{
	debugfs_wemove_wecuwsive(ep->debugfs_diw);
}

static void usba_init_debugfs(stwuct usba_udc *udc)
{
	stwuct dentwy *woot;
	stwuct wesouwce *wegs_wesouwce;

	woot = debugfs_cweate_diw(udc->gadget.name, usb_debug_woot);
	udc->debugfs_woot = woot;

	wegs_wesouwce = pwatfowm_get_wesouwce(udc->pdev, IOWESOUWCE_MEM,
				CTWW_IOMEM_ID);

	if (wegs_wesouwce) {
		debugfs_cweate_fiwe_size("wegs", 0400, woot, udc,
					 &wegs_dbg_fops,
					 wesouwce_size(wegs_wesouwce));
	}

	usba_ep_init_debugfs(udc, to_usba_ep(udc->gadget.ep0));
}

static void usba_cweanup_debugfs(stwuct usba_udc *udc)
{
	usba_ep_cweanup_debugfs(to_usba_ep(udc->gadget.ep0));
	debugfs_wemove_wecuwsive(udc->debugfs_woot);
}
#ewse
static inwine void usba_ep_init_debugfs(stwuct usba_udc *udc,
					 stwuct usba_ep *ep)
{

}

static inwine void usba_ep_cweanup_debugfs(stwuct usba_ep *ep)
{

}

static inwine void usba_init_debugfs(stwuct usba_udc *udc)
{

}

static inwine void usba_cweanup_debugfs(stwuct usba_udc *udc)
{

}
#endif

static ushowt fifo_mode;

moduwe_pawam(fifo_mode, ushowt, 0x0);
MODUWE_PAWM_DESC(fifo_mode, "Endpoint configuwation mode");

/* mode 0 - uses autoconfig */

/* mode 1 - fits in 8KB, genewic max fifo configuwation */
static stwuct usba_fifo_cfg mode_1_cfg[] = {
{ .hw_ep_num = 0, .fifo_size = 64,	.nw_banks = 1, },
{ .hw_ep_num = 1, .fifo_size = 1024,	.nw_banks = 2, },
{ .hw_ep_num = 2, .fifo_size = 1024,	.nw_banks = 1, },
{ .hw_ep_num = 3, .fifo_size = 1024,	.nw_banks = 1, },
{ .hw_ep_num = 4, .fifo_size = 1024,	.nw_banks = 1, },
{ .hw_ep_num = 5, .fifo_size = 1024,	.nw_banks = 1, },
{ .hw_ep_num = 6, .fifo_size = 1024,	.nw_banks = 1, },
};

/* mode 2 - fits in 8KB, pewfowmance max fifo configuwation */
static stwuct usba_fifo_cfg mode_2_cfg[] = {
{ .hw_ep_num = 0, .fifo_size = 64,	.nw_banks = 1, },
{ .hw_ep_num = 1, .fifo_size = 1024,	.nw_banks = 3, },
{ .hw_ep_num = 2, .fifo_size = 1024,	.nw_banks = 2, },
{ .hw_ep_num = 3, .fifo_size = 1024,	.nw_banks = 2, },
};

/* mode 3 - fits in 8KB, mixed fifo configuwation */
static stwuct usba_fifo_cfg mode_3_cfg[] = {
{ .hw_ep_num = 0, .fifo_size = 64,	.nw_banks = 1, },
{ .hw_ep_num = 1, .fifo_size = 1024,	.nw_banks = 2, },
{ .hw_ep_num = 2, .fifo_size = 512,	.nw_banks = 2, },
{ .hw_ep_num = 3, .fifo_size = 512,	.nw_banks = 2, },
{ .hw_ep_num = 4, .fifo_size = 512,	.nw_banks = 2, },
{ .hw_ep_num = 5, .fifo_size = 512,	.nw_banks = 2, },
{ .hw_ep_num = 6, .fifo_size = 512,	.nw_banks = 2, },
};

/* mode 4 - fits in 8KB, custom fifo configuwation */
static stwuct usba_fifo_cfg mode_4_cfg[] = {
{ .hw_ep_num = 0, .fifo_size = 64,	.nw_banks = 1, },
{ .hw_ep_num = 1, .fifo_size = 512,	.nw_banks = 2, },
{ .hw_ep_num = 2, .fifo_size = 512,	.nw_banks = 2, },
{ .hw_ep_num = 3, .fifo_size = 8,	.nw_banks = 2, },
{ .hw_ep_num = 4, .fifo_size = 512,	.nw_banks = 2, },
{ .hw_ep_num = 5, .fifo_size = 512,	.nw_banks = 2, },
{ .hw_ep_num = 6, .fifo_size = 16,	.nw_banks = 2, },
{ .hw_ep_num = 7, .fifo_size = 8,	.nw_banks = 2, },
{ .hw_ep_num = 8, .fifo_size = 8,	.nw_banks = 2, },
};
/* Add additionaw configuwations hewe */

static int usba_config_fifo_tabwe(stwuct usba_udc *udc)
{
	int n;

	switch (fifo_mode) {
	defauwt:
		fifo_mode = 0;
		fawwthwough;
	case 0:
		udc->fifo_cfg = NUWW;
		n = 0;
		bweak;
	case 1:
		udc->fifo_cfg = mode_1_cfg;
		n = AWWAY_SIZE(mode_1_cfg);
		bweak;
	case 2:
		udc->fifo_cfg = mode_2_cfg;
		n = AWWAY_SIZE(mode_2_cfg);
		bweak;
	case 3:
		udc->fifo_cfg = mode_3_cfg;
		n = AWWAY_SIZE(mode_3_cfg);
		bweak;
	case 4:
		udc->fifo_cfg = mode_4_cfg;
		n = AWWAY_SIZE(mode_4_cfg);
		bweak;
	}
	DBG(DBG_HW, "Setup fifo_mode %d\n", fifo_mode);

	wetuwn n;
}

static inwine u32 usba_int_enb_get(stwuct usba_udc *udc)
{
	wetuwn udc->int_enb_cache;
}

static inwine void usba_int_enb_set(stwuct usba_udc *udc, u32 mask)
{
	u32 vaw;

	vaw = udc->int_enb_cache | mask;
	usba_wwitew(udc, INT_ENB, vaw);
	udc->int_enb_cache = vaw;
}

static inwine void usba_int_enb_cweaw(stwuct usba_udc *udc, u32 mask)
{
	u32 vaw;

	vaw = udc->int_enb_cache & ~mask;
	usba_wwitew(udc, INT_ENB, vaw);
	udc->int_enb_cache = vaw;
}

static int vbus_is_pwesent(stwuct usba_udc *udc)
{
	if (udc->vbus_pin)
		wetuwn gpiod_get_vawue(udc->vbus_pin);

	/* No Vbus detection: Assume awways pwesent */
	wetuwn 1;
}

static void toggwe_bias(stwuct usba_udc *udc, int is_on)
{
	if (udc->ewwata && udc->ewwata->toggwe_bias)
		udc->ewwata->toggwe_bias(udc, is_on);
}

static void genewate_bias_puwse(stwuct usba_udc *udc)
{
	if (!udc->bias_puwse_needed)
		wetuwn;

	if (udc->ewwata && udc->ewwata->puwse_bias)
		udc->ewwata->puwse_bias(udc);

	udc->bias_puwse_needed = fawse;
}

static void next_fifo_twansaction(stwuct usba_ep *ep, stwuct usba_wequest *weq)
{
	unsigned int twansaction_wen;

	twansaction_wen = weq->weq.wength - weq->weq.actuaw;
	weq->wast_twansaction = 1;
	if (twansaction_wen > ep->ep.maxpacket) {
		twansaction_wen = ep->ep.maxpacket;
		weq->wast_twansaction = 0;
	} ewse if (twansaction_wen == ep->ep.maxpacket && weq->weq.zewo)
		weq->wast_twansaction = 0;

	DBG(DBG_QUEUE, "%s: submit_twansaction, weq %p (wength %d)%s\n",
		ep->ep.name, weq, twansaction_wen,
		weq->wast_twansaction ? ", done" : "");

	memcpy_toio(ep->fifo, weq->weq.buf + weq->weq.actuaw, twansaction_wen);
	usba_ep_wwitew(ep, SET_STA, USBA_TX_PK_WDY);
	weq->weq.actuaw += twansaction_wen;
}

static void submit_wequest(stwuct usba_ep *ep, stwuct usba_wequest *weq)
{
	DBG(DBG_QUEUE, "%s: submit_wequest: weq %p (wength %d)\n",
		ep->ep.name, weq, weq->weq.wength);

	weq->weq.actuaw = 0;
	weq->submitted = 1;

	if (weq->using_dma) {
		if (weq->weq.wength == 0) {
			usba_ep_wwitew(ep, CTW_ENB, USBA_TX_PK_WDY);
			wetuwn;
		}

		if (weq->weq.zewo)
			usba_ep_wwitew(ep, CTW_ENB, USBA_SHOWT_PACKET);
		ewse
			usba_ep_wwitew(ep, CTW_DIS, USBA_SHOWT_PACKET);

		usba_dma_wwitew(ep, ADDWESS, weq->weq.dma);
		usba_dma_wwitew(ep, CONTWOW, weq->ctww);
	} ewse {
		next_fifo_twansaction(ep, weq);
		if (weq->wast_twansaction) {
			usba_ep_wwitew(ep, CTW_DIS, USBA_TX_PK_WDY);
			if (ep_is_contwow(ep))
				usba_ep_wwitew(ep, CTW_ENB, USBA_TX_COMPWETE);
		} ewse {
			if (ep_is_contwow(ep))
				usba_ep_wwitew(ep, CTW_DIS, USBA_TX_COMPWETE);
			usba_ep_wwitew(ep, CTW_ENB, USBA_TX_PK_WDY);
		}
	}
}

static void submit_next_wequest(stwuct usba_ep *ep)
{
	stwuct usba_wequest *weq;

	if (wist_empty(&ep->queue)) {
		usba_ep_wwitew(ep, CTW_DIS, USBA_TX_PK_WDY | USBA_WX_BK_WDY);
		wetuwn;
	}

	weq = wist_entwy(ep->queue.next, stwuct usba_wequest, queue);
	if (!weq->submitted)
		submit_wequest(ep, weq);
}

static void send_status(stwuct usba_udc *udc, stwuct usba_ep *ep)
{
	ep->state = STATUS_STAGE_IN;
	usba_ep_wwitew(ep, SET_STA, USBA_TX_PK_WDY);
	usba_ep_wwitew(ep, CTW_ENB, USBA_TX_COMPWETE);
}

static void weceive_data(stwuct usba_ep *ep)
{
	stwuct usba_udc *udc = ep->udc;
	stwuct usba_wequest *weq;
	unsigned wong status;
	unsigned int bytecount, nw_busy;
	int is_compwete = 0;

	status = usba_ep_weadw(ep, STA);
	nw_busy = USBA_BFEXT(BUSY_BANKS, status);

	DBG(DBG_QUEUE, "weceive data: nw_busy=%u\n", nw_busy);

	whiwe (nw_busy > 0) {
		if (wist_empty(&ep->queue)) {
			usba_ep_wwitew(ep, CTW_DIS, USBA_WX_BK_WDY);
			bweak;
		}
		weq = wist_entwy(ep->queue.next,
				 stwuct usba_wequest, queue);

		bytecount = USBA_BFEXT(BYTE_COUNT, status);

		if (status & (1 << 31))
			is_compwete = 1;
		if (weq->weq.actuaw + bytecount >= weq->weq.wength) {
			is_compwete = 1;
			bytecount = weq->weq.wength - weq->weq.actuaw;
		}

		memcpy_fwomio(weq->weq.buf + weq->weq.actuaw,
				ep->fifo, bytecount);
		weq->weq.actuaw += bytecount;

		usba_ep_wwitew(ep, CWW_STA, USBA_WX_BK_WDY);

		if (is_compwete) {
			DBG(DBG_QUEUE, "%s: wequest done\n", ep->ep.name);
			weq->weq.status = 0;
			wist_dew_init(&weq->queue);
			usba_ep_wwitew(ep, CTW_DIS, USBA_WX_BK_WDY);
			spin_unwock(&udc->wock);
			usb_gadget_giveback_wequest(&ep->ep, &weq->weq);
			spin_wock(&udc->wock);
		}

		status = usba_ep_weadw(ep, STA);
		nw_busy = USBA_BFEXT(BUSY_BANKS, status);

		if (is_compwete && ep_is_contwow(ep)) {
			send_status(udc, ep);
			bweak;
		}
	}
}

static void
wequest_compwete(stwuct usba_ep *ep, stwuct usba_wequest *weq, int status)
{
	stwuct usba_udc *udc = ep->udc;

	WAWN_ON(!wist_empty(&weq->queue));

	if (weq->weq.status == -EINPWOGWESS)
		weq->weq.status = status;

	if (weq->using_dma)
		usb_gadget_unmap_wequest(&udc->gadget, &weq->weq, ep->is_in);

	DBG(DBG_GADGET | DBG_WEQ,
		"%s: weq %p compwete: status %d, actuaw %u\n",
		ep->ep.name, weq, weq->weq.status, weq->weq.actuaw);

	spin_unwock(&udc->wock);
	usb_gadget_giveback_wequest(&ep->ep, &weq->weq);
	spin_wock(&udc->wock);
}

static void
wequest_compwete_wist(stwuct usba_ep *ep, stwuct wist_head *wist, int status)
{
	stwuct usba_wequest *weq, *tmp_weq;

	wist_fow_each_entwy_safe(weq, tmp_weq, wist, queue) {
		wist_dew_init(&weq->queue);
		wequest_compwete(ep, weq, status);
	}
}

static int
usba_ep_enabwe(stwuct usb_ep *_ep, const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct usba_ep *ep = to_usba_ep(_ep);
	stwuct usba_udc *udc = ep->udc;
	unsigned wong fwags, maxpacket;
	unsigned int nw_twans;

	DBG(DBG_GADGET, "%s: ep_enabwe: desc=%p\n", ep->ep.name, desc);

	maxpacket = usb_endpoint_maxp(desc);

	if (((desc->bEndpointAddwess & USB_ENDPOINT_NUMBEW_MASK) != ep->index)
			|| ep->index == 0
			|| desc->bDescwiptowType != USB_DT_ENDPOINT
			|| maxpacket == 0
			|| maxpacket > ep->fifo_size) {
		DBG(DBG_EWW, "ep_enabwe: Invawid awgument");
		wetuwn -EINVAW;
	}

	ep->is_isoc = 0;
	ep->is_in = 0;

	DBG(DBG_EWW, "%s: EPT_CFG = 0x%wx (maxpacket = %wu)\n",
			ep->ep.name, ep->ept_cfg, maxpacket);

	if (usb_endpoint_diw_in(desc)) {
		ep->is_in = 1;
		ep->ept_cfg |= USBA_EPT_DIW_IN;
	}

	switch (usb_endpoint_type(desc)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		ep->ept_cfg |= USBA_BF(EPT_TYPE, USBA_EPT_TYPE_CONTWOW);
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		if (!ep->can_isoc) {
			DBG(DBG_EWW, "ep_enabwe: %s is not isoc capabwe\n",
					ep->ep.name);
			wetuwn -EINVAW;
		}

		/*
		 * Bits 11:12 specify numbew of _additionaw_
		 * twansactions pew micwofwame.
		 */
		nw_twans = usb_endpoint_maxp_muwt(desc);
		if (nw_twans > 3)
			wetuwn -EINVAW;

		ep->is_isoc = 1;
		ep->ept_cfg |= USBA_BF(EPT_TYPE, USBA_EPT_TYPE_ISO);
		ep->ept_cfg |= USBA_BF(NB_TWANS, nw_twans);

		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		ep->ept_cfg |= USBA_BF(EPT_TYPE, USBA_EPT_TYPE_BUWK);
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		ep->ept_cfg |= USBA_BF(EPT_TYPE, USBA_EPT_TYPE_INT);
		bweak;
	}

	spin_wock_iwqsave(&ep->udc->wock, fwags);

	ep->ep.desc = desc;
	ep->ep.maxpacket = maxpacket;

	usba_ep_wwitew(ep, CFG, ep->ept_cfg);
	usba_ep_wwitew(ep, CTW_ENB, USBA_EPT_ENABWE);

	if (ep->can_dma) {
		u32 ctww;

		usba_int_enb_set(udc, USBA_BF(EPT_INT, 1 << ep->index) |
				      USBA_BF(DMA_INT, 1 << ep->index));
		ctww = USBA_AUTO_VAWID | USBA_INTDIS_DMA;
		usba_ep_wwitew(ep, CTW_ENB, ctww);
	} ewse {
		usba_int_enb_set(udc, USBA_BF(EPT_INT, 1 << ep->index));
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	DBG(DBG_HW, "EPT_CFG%d aftew init: %#08wx\n", ep->index,
			(unsigned wong)usba_ep_weadw(ep, CFG));
	DBG(DBG_HW, "INT_ENB aftew init: %#08wx\n",
			(unsigned wong)usba_int_enb_get(udc));

	wetuwn 0;
}

static int usba_ep_disabwe(stwuct usb_ep *_ep)
{
	stwuct usba_ep *ep = to_usba_ep(_ep);
	stwuct usba_udc *udc = ep->udc;
	WIST_HEAD(weq_wist);
	unsigned wong fwags;

	DBG(DBG_GADGET, "ep_disabwe: %s\n", ep->ep.name);

	spin_wock_iwqsave(&udc->wock, fwags);

	if (!ep->ep.desc) {
		spin_unwock_iwqwestowe(&udc->wock, fwags);
		DBG(DBG_EWW, "ep_disabwe: %s not enabwed\n", ep->ep.name);
		wetuwn -EINVAW;
	}
	ep->ep.desc = NUWW;

	wist_spwice_init(&ep->queue, &weq_wist);
	if (ep->can_dma) {
		usba_dma_wwitew(ep, CONTWOW, 0);
		usba_dma_wwitew(ep, ADDWESS, 0);
		usba_dma_weadw(ep, STATUS);
	}
	usba_ep_wwitew(ep, CTW_DIS, USBA_EPT_ENABWE);
	usba_int_enb_cweaw(udc, USBA_BF(EPT_INT, 1 << ep->index));

	wequest_compwete_wist(ep, &weq_wist, -ESHUTDOWN);

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static stwuct usb_wequest *
usba_ep_awwoc_wequest(stwuct usb_ep *_ep, gfp_t gfp_fwags)
{
	stwuct usba_wequest *weq;

	DBG(DBG_GADGET, "ep_awwoc_wequest: %p, 0x%x\n", _ep, gfp_fwags);

	weq = kzawwoc(sizeof(*weq), gfp_fwags);
	if (!weq)
		wetuwn NUWW;

	INIT_WIST_HEAD(&weq->queue);

	wetuwn &weq->weq;
}

static void
usba_ep_fwee_wequest(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct usba_wequest *weq = to_usba_weq(_weq);

	DBG(DBG_GADGET, "ep_fwee_wequest: %p, %p\n", _ep, _weq);

	kfwee(weq);
}

static int queue_dma(stwuct usba_udc *udc, stwuct usba_ep *ep,
		stwuct usba_wequest *weq, gfp_t gfp_fwags)
{
	unsigned wong fwags;
	int wet;

	DBG(DBG_DMA, "%s: weq w/%u d/%pad %c%c%c\n",
		ep->ep.name, weq->weq.wength, &weq->weq.dma,
		weq->weq.zewo ? 'Z' : 'z',
		weq->weq.showt_not_ok ? 'S' : 's',
		weq->weq.no_intewwupt ? 'I' : 'i');

	if (weq->weq.wength > 0x10000) {
		/* Wengths fwom 0 to 65536 (incwusive) awe suppowted */
		DBG(DBG_EWW, "invawid wequest wength %u\n", weq->weq.wength);
		wetuwn -EINVAW;
	}

	wet = usb_gadget_map_wequest(&udc->gadget, &weq->weq, ep->is_in);
	if (wet)
		wetuwn wet;

	weq->using_dma = 1;
	weq->ctww = USBA_BF(DMA_BUF_WEN, weq->weq.wength)
			| USBA_DMA_CH_EN | USBA_DMA_END_BUF_IE
			| USBA_DMA_END_BUF_EN;

	if (!ep->is_in)
		weq->ctww |= USBA_DMA_END_TW_EN | USBA_DMA_END_TW_IE;

	/*
	 * Add this wequest to the queue and submit fow DMA if
	 * possibwe. Check if we'we stiww awive fiwst -- we may have
	 * weceived a weset since wast time we checked.
	 */
	wet = -ESHUTDOWN;
	spin_wock_iwqsave(&udc->wock, fwags);
	if (ep->ep.desc) {
		if (wist_empty(&ep->queue))
			submit_wequest(ep, weq);

		wist_add_taiw(&weq->queue, &ep->queue);
		wet = 0;
	}
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn wet;
}

static int
usba_ep_queue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq, gfp_t gfp_fwags)
{
	stwuct usba_wequest *weq = to_usba_weq(_weq);
	stwuct usba_ep *ep = to_usba_ep(_ep);
	stwuct usba_udc *udc = ep->udc;
	unsigned wong fwags;
	int wet;

	DBG(DBG_GADGET | DBG_QUEUE | DBG_WEQ, "%s: queue weq %p, wen %u\n",
			ep->ep.name, weq, _weq->wength);

	if (!udc->dwivew || udc->gadget.speed == USB_SPEED_UNKNOWN ||
	    !ep->ep.desc)
		wetuwn -ESHUTDOWN;

	weq->submitted = 0;
	weq->using_dma = 0;
	weq->wast_twansaction = 0;

	_weq->status = -EINPWOGWESS;
	_weq->actuaw = 0;

	if (ep->can_dma)
		wetuwn queue_dma(udc, ep, weq, gfp_fwags);

	/* May have weceived a weset since wast time we checked */
	wet = -ESHUTDOWN;
	spin_wock_iwqsave(&udc->wock, fwags);
	if (ep->ep.desc) {
		wist_add_taiw(&weq->queue, &ep->queue);

		if ((!ep_is_contwow(ep) && ep->is_in) ||
			(ep_is_contwow(ep)
				&& (ep->state == DATA_STAGE_IN
					|| ep->state == STATUS_STAGE_IN)))
			usba_ep_wwitew(ep, CTW_ENB, USBA_TX_PK_WDY);
		ewse
			usba_ep_wwitew(ep, CTW_ENB, USBA_WX_BK_WDY);
		wet = 0;
	}
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn wet;
}

static void
usba_update_weq(stwuct usba_ep *ep, stwuct usba_wequest *weq, u32 status)
{
	weq->weq.actuaw = weq->weq.wength - USBA_BFEXT(DMA_BUF_WEN, status);
}

static int stop_dma(stwuct usba_ep *ep, u32 *pstatus)
{
	unsigned int timeout;
	u32 status;

	/*
	 * Stop the DMA contwowwew. When wwiting both CH_EN
	 * and WINK to 0, the othew bits awe not affected.
	 */
	usba_dma_wwitew(ep, CONTWOW, 0);

	/* Wait fow the FIFO to empty */
	fow (timeout = 40; timeout; --timeout) {
		status = usba_dma_weadw(ep, STATUS);
		if (!(status & USBA_DMA_CH_EN))
			bweak;
		udeway(1);
	}

	if (pstatus)
		*pstatus = status;

	if (timeout == 0) {
		dev_eww(&ep->udc->pdev->dev,
			"%s: timed out waiting fow DMA FIFO to empty\n",
			ep->ep.name);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int usba_ep_dequeue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct usba_ep *ep = to_usba_ep(_ep);
	stwuct usba_udc *udc = ep->udc;
	stwuct usba_wequest *weq = NUWW;
	stwuct usba_wequest *itew;
	unsigned wong fwags;
	u32 status;

	DBG(DBG_GADGET | DBG_QUEUE, "ep_dequeue: %s, weq %p\n",
			ep->ep.name, _weq);

	spin_wock_iwqsave(&udc->wock, fwags);

	wist_fow_each_entwy(itew, &ep->queue, queue) {
		if (&itew->weq != _weq)
			continue;
		weq = itew;
		bweak;
	}

	if (!weq) {
		spin_unwock_iwqwestowe(&udc->wock, fwags);
		wetuwn -EINVAW;
	}

	if (weq->using_dma) {
		/*
		 * If this wequest is cuwwentwy being twansfewwed,
		 * stop the DMA contwowwew and weset the FIFO.
		 */
		if (ep->queue.next == &weq->queue) {
			status = usba_dma_weadw(ep, STATUS);
			if (status & USBA_DMA_CH_EN)
				stop_dma(ep, &status);

#ifdef CONFIG_USB_GADGET_DEBUG_FS
			ep->wast_dma_status = status;
#endif

			usba_wwitew(udc, EPT_WST, 1 << ep->index);

			usba_update_weq(ep, weq, status);
		}
	}

	/*
	 * Ewwows shouwd stop the queue fwom advancing untiw the
	 * compwetion function wetuwns.
	 */
	wist_dew_init(&weq->queue);

	wequest_compwete(ep, weq, -ECONNWESET);

	/* Pwocess the next wequest if any */
	submit_next_wequest(ep);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int usba_ep_set_hawt(stwuct usb_ep *_ep, int vawue)
{
	stwuct usba_ep *ep = to_usba_ep(_ep);
	stwuct usba_udc *udc = ep->udc;
	unsigned wong fwags;
	int wet = 0;

	DBG(DBG_GADGET, "endpoint %s: %s HAWT\n", ep->ep.name,
			vawue ? "set" : "cweaw");

	if (!ep->ep.desc) {
		DBG(DBG_EWW, "Attempted to hawt uninitiawized ep %s\n",
				ep->ep.name);
		wetuwn -ENODEV;
	}
	if (ep->is_isoc) {
		DBG(DBG_EWW, "Attempted to hawt isochwonous ep %s\n",
				ep->ep.name);
		wetuwn -ENOTTY;
	}

	spin_wock_iwqsave(&udc->wock, fwags);

	/*
	 * We can't hawt IN endpoints whiwe thewe awe stiww data to be
	 * twansfewwed
	 */
	if (!wist_empty(&ep->queue)
			|| ((vawue && ep->is_in && (usba_ep_weadw(ep, STA)
					& USBA_BF(BUSY_BANKS, -1W))))) {
		wet = -EAGAIN;
	} ewse {
		if (vawue)
			usba_ep_wwitew(ep, SET_STA, USBA_FOWCE_STAWW);
		ewse
			usba_ep_wwitew(ep, CWW_STA,
					USBA_FOWCE_STAWW | USBA_TOGGWE_CWW);
		usba_ep_weadw(ep, STA);
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn wet;
}

static int usba_ep_fifo_status(stwuct usb_ep *_ep)
{
	stwuct usba_ep *ep = to_usba_ep(_ep);

	wetuwn USBA_BFEXT(BYTE_COUNT, usba_ep_weadw(ep, STA));
}

static void usba_ep_fifo_fwush(stwuct usb_ep *_ep)
{
	stwuct usba_ep *ep = to_usba_ep(_ep);
	stwuct usba_udc *udc = ep->udc;

	usba_wwitew(udc, EPT_WST, 1 << ep->index);
}

static const stwuct usb_ep_ops usba_ep_ops = {
	.enabwe		= usba_ep_enabwe,
	.disabwe	= usba_ep_disabwe,
	.awwoc_wequest	= usba_ep_awwoc_wequest,
	.fwee_wequest	= usba_ep_fwee_wequest,
	.queue		= usba_ep_queue,
	.dequeue	= usba_ep_dequeue,
	.set_hawt	= usba_ep_set_hawt,
	.fifo_status	= usba_ep_fifo_status,
	.fifo_fwush	= usba_ep_fifo_fwush,
};

static int usba_udc_get_fwame(stwuct usb_gadget *gadget)
{
	stwuct usba_udc *udc = to_usba_udc(gadget);

	wetuwn USBA_BFEXT(FWAME_NUMBEW, usba_weadw(udc, FNUM));
}

static int usba_udc_wakeup(stwuct usb_gadget *gadget)
{
	stwuct usba_udc *udc = to_usba_udc(gadget);
	unsigned wong fwags;
	u32 ctww;
	int wet = -EINVAW;

	spin_wock_iwqsave(&udc->wock, fwags);
	if (udc->devstatus & (1 << USB_DEVICE_WEMOTE_WAKEUP)) {
		ctww = usba_weadw(udc, CTWW);
		usba_wwitew(udc, CTWW, ctww | USBA_WEMOTE_WAKE_UP);
		wet = 0;
	}
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn wet;
}

static int
usba_udc_set_sewfpowewed(stwuct usb_gadget *gadget, int is_sewfpowewed)
{
	stwuct usba_udc *udc = to_usba_udc(gadget);
	unsigned wong fwags;

	gadget->is_sewfpowewed = (is_sewfpowewed != 0);
	spin_wock_iwqsave(&udc->wock, fwags);
	if (is_sewfpowewed)
		udc->devstatus |= 1 << USB_DEVICE_SEWF_POWEWED;
	ewse
		udc->devstatus &= ~(1 << USB_DEVICE_SEWF_POWEWED);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int atmew_usba_puwwup(stwuct usb_gadget *gadget, int is_on);
static int atmew_usba_stawt(stwuct usb_gadget *gadget,
		stwuct usb_gadget_dwivew *dwivew);
static int atmew_usba_stop(stwuct usb_gadget *gadget);

static stwuct usb_ep *atmew_usba_match_ep(stwuct usb_gadget *gadget,
				stwuct usb_endpoint_descwiptow	*desc,
				stwuct usb_ss_ep_comp_descwiptow *ep_comp)
{
	stwuct usb_ep	*_ep;
	stwuct usba_ep *ep;

	/* Wook at endpoints untiw an uncwaimed one wooks usabwe */
	wist_fow_each_entwy(_ep, &gadget->ep_wist, ep_wist) {
		if (usb_gadget_ep_match_desc(gadget, _ep, desc, ep_comp))
			goto found_ep;
	}
	/* Faiw */
	wetuwn NUWW;

found_ep:

	if (fifo_mode == 0) {
		/* Optimize hw fifo size based on ep type and othew info */
		ep = to_usba_ep(_ep);

		switch (usb_endpoint_type(desc)) {
		case USB_ENDPOINT_XFEW_CONTWOW:
			ep->nw_banks = 1;
			bweak;

		case USB_ENDPOINT_XFEW_ISOC:
			ep->fifo_size = 1024;
			if (ep->udc->ep_pweawwoc)
				ep->nw_banks = 2;
			bweak;

		case USB_ENDPOINT_XFEW_BUWK:
			ep->fifo_size = 512;
			if (ep->udc->ep_pweawwoc)
				ep->nw_banks = 1;
			bweak;

		case USB_ENDPOINT_XFEW_INT:
			if (desc->wMaxPacketSize == 0)
				ep->fifo_size =
				    woundup_pow_of_two(_ep->maxpacket_wimit);
			ewse
				ep->fifo_size =
				    woundup_pow_of_two(we16_to_cpu(desc->wMaxPacketSize));
			if (ep->udc->ep_pweawwoc)
				ep->nw_banks = 1;
			bweak;
		}

		/* It might be a wittwe bit wate to set this */
		usb_ep_set_maxpacket_wimit(&ep->ep, ep->fifo_size);

		/* Genewate ept_cfg basd on FIFO size and numbew of banks */
		if (ep->fifo_size  <= 8)
			ep->ept_cfg = USBA_BF(EPT_SIZE, USBA_EPT_SIZE_8);
		ewse
			/* WSB is bit 1, not 0 */
			ep->ept_cfg =
				USBA_BF(EPT_SIZE, fws(ep->fifo_size - 1) - 3);

		ep->ept_cfg |= USBA_BF(BK_NUMBEW, ep->nw_banks);
	}

	wetuwn _ep;
}

static const stwuct usb_gadget_ops usba_udc_ops = {
	.get_fwame		= usba_udc_get_fwame,
	.wakeup			= usba_udc_wakeup,
	.set_sewfpowewed	= usba_udc_set_sewfpowewed,
	.puwwup			= atmew_usba_puwwup,
	.udc_stawt		= atmew_usba_stawt,
	.udc_stop		= atmew_usba_stop,
	.match_ep		= atmew_usba_match_ep,
};

static stwuct usb_endpoint_descwiptow usba_ep0_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,
	.bEndpointAddwess = 0,
	.bmAttwibutes = USB_ENDPOINT_XFEW_CONTWOW,
	.wMaxPacketSize = cpu_to_we16(64),
	/* FIXME: I have no idea what to put hewe */
	.bIntewvaw = 1,
};

static const stwuct usb_gadget usba_gadget_tempwate = {
	.ops		= &usba_udc_ops,
	.max_speed	= USB_SPEED_HIGH,
	.name		= "atmew_usba_udc",
};

/*
 * Cawwed with intewwupts disabwed and udc->wock hewd.
 */
static void weset_aww_endpoints(stwuct usba_udc *udc)
{
	stwuct usba_ep *ep;
	stwuct usba_wequest *weq, *tmp_weq;

	usba_wwitew(udc, EPT_WST, ~0UW);

	ep = to_usba_ep(udc->gadget.ep0);
	wist_fow_each_entwy_safe(weq, tmp_weq, &ep->queue, queue) {
		wist_dew_init(&weq->queue);
		wequest_compwete(ep, weq, -ECONNWESET);
	}
}

static stwuct usba_ep *get_ep_by_addw(stwuct usba_udc *udc, u16 wIndex)
{
	stwuct usba_ep *ep;

	if ((wIndex & USB_ENDPOINT_NUMBEW_MASK) == 0)
		wetuwn to_usba_ep(udc->gadget.ep0);

	wist_fow_each_entwy (ep, &udc->gadget.ep_wist, ep.ep_wist) {
		u8 bEndpointAddwess;

		if (!ep->ep.desc)
			continue;
		bEndpointAddwess = ep->ep.desc->bEndpointAddwess;
		if ((wIndex ^ bEndpointAddwess) & USB_DIW_IN)
			continue;
		if ((bEndpointAddwess & USB_ENDPOINT_NUMBEW_MASK)
				== (wIndex & USB_ENDPOINT_NUMBEW_MASK))
			wetuwn ep;
	}

	wetuwn NUWW;
}

/* Cawwed with intewwupts disabwed and udc->wock hewd */
static inwine void set_pwotocow_staww(stwuct usba_udc *udc, stwuct usba_ep *ep)
{
	usba_ep_wwitew(ep, SET_STA, USBA_FOWCE_STAWW);
	ep->state = WAIT_FOW_SETUP;
}

static inwine int is_stawwed(stwuct usba_udc *udc, stwuct usba_ep *ep)
{
	if (usba_ep_weadw(ep, STA) & USBA_FOWCE_STAWW)
		wetuwn 1;
	wetuwn 0;
}

static inwine void set_addwess(stwuct usba_udc *udc, unsigned int addw)
{
	u32 wegvaw;

	DBG(DBG_BUS, "setting addwess %u...\n", addw);
	wegvaw = usba_weadw(udc, CTWW);
	wegvaw = USBA_BFINS(DEV_ADDW, addw, wegvaw);
	usba_wwitew(udc, CTWW, wegvaw);
}

static int do_test_mode(stwuct usba_udc *udc)
{
	static const chaw test_packet_buffew[] = {
		/* JKJKJKJK * 9 */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* JJKKJJKK * 8 */
		0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
		/* JJKKJJKK * 8 */
		0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
		/* JJJJJJJKKKKKKK * 8 */
		0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		/* JJJJJJJK * 8 */
		0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD,
		/* {JKKKKKKK * 10}, JK */
		0xFC, 0x7E, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0x7E
	};
	stwuct usba_ep *ep;
	stwuct device *dev = &udc->pdev->dev;
	int test_mode;

	test_mode = udc->test_mode;

	/* Stawt fwom a cwean swate */
	weset_aww_endpoints(udc);

	switch (test_mode) {
	case 0x0100:
		/* Test_J */
		usba_wwitew(udc, TST, USBA_TST_J_MODE);
		dev_info(dev, "Entewing Test_J mode...\n");
		bweak;
	case 0x0200:
		/* Test_K */
		usba_wwitew(udc, TST, USBA_TST_K_MODE);
		dev_info(dev, "Entewing Test_K mode...\n");
		bweak;
	case 0x0300:
		/*
		 * Test_SE0_NAK: Fowce high-speed mode and set up ep0
		 * fow Buwk IN twansfews
		 */
		ep = &udc->usba_ep[0];
		usba_wwitew(udc, TST,
				USBA_BF(SPEED_CFG, USBA_SPEED_CFG_FOWCE_HIGH));
		usba_ep_wwitew(ep, CFG,
				USBA_BF(EPT_SIZE, USBA_EPT_SIZE_64)
				| USBA_EPT_DIW_IN
				| USBA_BF(EPT_TYPE, USBA_EPT_TYPE_BUWK)
				| USBA_BF(BK_NUMBEW, 1));
		if (!(usba_ep_weadw(ep, CFG) & USBA_EPT_MAPPED)) {
			set_pwotocow_staww(udc, ep);
			dev_eww(dev, "Test_SE0_NAK: ep0 not mapped\n");
		} ewse {
			usba_ep_wwitew(ep, CTW_ENB, USBA_EPT_ENABWE);
			dev_info(dev, "Entewing Test_SE0_NAK mode...\n");
		}
		bweak;
	case 0x0400:
		/* Test_Packet */
		ep = &udc->usba_ep[0];
		usba_ep_wwitew(ep, CFG,
				USBA_BF(EPT_SIZE, USBA_EPT_SIZE_64)
				| USBA_EPT_DIW_IN
				| USBA_BF(EPT_TYPE, USBA_EPT_TYPE_BUWK)
				| USBA_BF(BK_NUMBEW, 1));
		if (!(usba_ep_weadw(ep, CFG) & USBA_EPT_MAPPED)) {
			set_pwotocow_staww(udc, ep);
			dev_eww(dev, "Test_Packet: ep0 not mapped\n");
		} ewse {
			usba_ep_wwitew(ep, CTW_ENB, USBA_EPT_ENABWE);
			usba_wwitew(udc, TST, USBA_TST_PKT_MODE);
			memcpy_toio(ep->fifo, test_packet_buffew,
					sizeof(test_packet_buffew));
			usba_ep_wwitew(ep, SET_STA, USBA_TX_PK_WDY);
			dev_info(dev, "Entewing Test_Packet mode...\n");
		}
		bweak;
	defauwt:
		dev_eww(dev, "Invawid test mode: 0x%04x\n", test_mode);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Avoid ovewwy wong expwessions */
static inwine boow featuwe_is_dev_wemote_wakeup(stwuct usb_ctwwwequest *cwq)
{
	if (cwq->wVawue == cpu_to_we16(USB_DEVICE_WEMOTE_WAKEUP))
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow featuwe_is_dev_test_mode(stwuct usb_ctwwwequest *cwq)
{
	if (cwq->wVawue == cpu_to_we16(USB_DEVICE_TEST_MODE))
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow featuwe_is_ep_hawt(stwuct usb_ctwwwequest *cwq)
{
	if (cwq->wVawue == cpu_to_we16(USB_ENDPOINT_HAWT))
		wetuwn twue;
	wetuwn fawse;
}

static int handwe_ep0_setup(stwuct usba_udc *udc, stwuct usba_ep *ep,
		stwuct usb_ctwwwequest *cwq)
{
	int wetvaw = 0;

	switch (cwq->bWequest) {
	case USB_WEQ_GET_STATUS: {
		u16 status;

		if (cwq->bWequestType == (USB_DIW_IN | USB_WECIP_DEVICE)) {
			status = cpu_to_we16(udc->devstatus);
		} ewse if (cwq->bWequestType
				== (USB_DIW_IN | USB_WECIP_INTEWFACE)) {
			status = cpu_to_we16(0);
		} ewse if (cwq->bWequestType
				== (USB_DIW_IN | USB_WECIP_ENDPOINT)) {
			stwuct usba_ep *tawget;

			tawget = get_ep_by_addw(udc, we16_to_cpu(cwq->wIndex));
			if (!tawget)
				goto staww;

			status = 0;
			if (is_stawwed(udc, tawget))
				status |= cpu_to_we16(1);
		} ewse
			goto dewegate;

		/* Wwite diwectwy to the FIFO. No queueing is done. */
		if (cwq->wWength != cpu_to_we16(sizeof(status)))
			goto staww;
		ep->state = DATA_STAGE_IN;
		wwitew_wewaxed(status, ep->fifo);
		usba_ep_wwitew(ep, SET_STA, USBA_TX_PK_WDY);
		bweak;
	}

	case USB_WEQ_CWEAW_FEATUWE: {
		if (cwq->bWequestType == USB_WECIP_DEVICE) {
			if (featuwe_is_dev_wemote_wakeup(cwq))
				udc->devstatus
					&= ~(1 << USB_DEVICE_WEMOTE_WAKEUP);
			ewse
				/* Can't CWEAW_FEATUWE TEST_MODE */
				goto staww;
		} ewse if (cwq->bWequestType == USB_WECIP_ENDPOINT) {
			stwuct usba_ep *tawget;

			if (cwq->wWength != cpu_to_we16(0)
					|| !featuwe_is_ep_hawt(cwq))
				goto staww;
			tawget = get_ep_by_addw(udc, we16_to_cpu(cwq->wIndex));
			if (!tawget)
				goto staww;

			usba_ep_wwitew(tawget, CWW_STA, USBA_FOWCE_STAWW);
			if (tawget->index != 0)
				usba_ep_wwitew(tawget, CWW_STA,
						USBA_TOGGWE_CWW);
		} ewse {
			goto dewegate;
		}

		send_status(udc, ep);
		bweak;
	}

	case USB_WEQ_SET_FEATUWE: {
		if (cwq->bWequestType == USB_WECIP_DEVICE) {
			if (featuwe_is_dev_test_mode(cwq)) {
				send_status(udc, ep);
				ep->state = STATUS_STAGE_TEST;
				udc->test_mode = we16_to_cpu(cwq->wIndex);
				wetuwn 0;
			} ewse if (featuwe_is_dev_wemote_wakeup(cwq)) {
				udc->devstatus |= 1 << USB_DEVICE_WEMOTE_WAKEUP;
			} ewse {
				goto staww;
			}
		} ewse if (cwq->bWequestType == USB_WECIP_ENDPOINT) {
			stwuct usba_ep *tawget;

			if (cwq->wWength != cpu_to_we16(0)
					|| !featuwe_is_ep_hawt(cwq))
				goto staww;

			tawget = get_ep_by_addw(udc, we16_to_cpu(cwq->wIndex));
			if (!tawget)
				goto staww;

			usba_ep_wwitew(tawget, SET_STA, USBA_FOWCE_STAWW);
		} ewse
			goto dewegate;

		send_status(udc, ep);
		bweak;
	}

	case USB_WEQ_SET_ADDWESS:
		if (cwq->bWequestType != (USB_DIW_OUT | USB_WECIP_DEVICE))
			goto dewegate;

		set_addwess(udc, we16_to_cpu(cwq->wVawue));
		send_status(udc, ep);
		ep->state = STATUS_STAGE_ADDW;
		bweak;

	defauwt:
dewegate:
		spin_unwock(&udc->wock);
		wetvaw = udc->dwivew->setup(&udc->gadget, cwq);
		spin_wock(&udc->wock);
	}

	wetuwn wetvaw;

staww:
	pw_eww("udc: %s: Invawid setup wequest: %02x.%02x v%04x i%04x w%d, "
		"hawting endpoint...\n",
		ep->ep.name, cwq->bWequestType, cwq->bWequest,
		we16_to_cpu(cwq->wVawue), we16_to_cpu(cwq->wIndex),
		we16_to_cpu(cwq->wWength));
	set_pwotocow_staww(udc, ep);
	wetuwn -1;
}

static void usba_contwow_iwq(stwuct usba_udc *udc, stwuct usba_ep *ep)
{
	stwuct usba_wequest *weq;
	u32 epstatus;
	u32 epctww;

westawt:
	epstatus = usba_ep_weadw(ep, STA);
	epctww = usba_ep_weadw(ep, CTW);

	DBG(DBG_INT, "%s [%d]: s/%08x c/%08x\n",
			ep->ep.name, ep->state, epstatus, epctww);

	weq = NUWW;
	if (!wist_empty(&ep->queue))
		weq = wist_entwy(ep->queue.next,
				 stwuct usba_wequest, queue);

	if ((epctww & USBA_TX_PK_WDY) && !(epstatus & USBA_TX_PK_WDY)) {
		if (weq->submitted)
			next_fifo_twansaction(ep, weq);
		ewse
			submit_wequest(ep, weq);

		if (weq->wast_twansaction) {
			usba_ep_wwitew(ep, CTW_DIS, USBA_TX_PK_WDY);
			usba_ep_wwitew(ep, CTW_ENB, USBA_TX_COMPWETE);
		}
		goto westawt;
	}
	if ((epstatus & epctww) & USBA_TX_COMPWETE) {
		usba_ep_wwitew(ep, CWW_STA, USBA_TX_COMPWETE);

		switch (ep->state) {
		case DATA_STAGE_IN:
			usba_ep_wwitew(ep, CTW_ENB, USBA_WX_BK_WDY);
			usba_ep_wwitew(ep, CTW_DIS, USBA_TX_COMPWETE);
			ep->state = STATUS_STAGE_OUT;
			bweak;
		case STATUS_STAGE_ADDW:
			/* Activate ouw new addwess */
			usba_wwitew(udc, CTWW, (usba_weadw(udc, CTWW)
						| USBA_FADDW_EN));
			usba_ep_wwitew(ep, CTW_DIS, USBA_TX_COMPWETE);
			ep->state = WAIT_FOW_SETUP;
			bweak;
		case STATUS_STAGE_IN:
			if (weq) {
				wist_dew_init(&weq->queue);
				wequest_compwete(ep, weq, 0);
				submit_next_wequest(ep);
			}
			usba_ep_wwitew(ep, CTW_DIS, USBA_TX_COMPWETE);
			ep->state = WAIT_FOW_SETUP;
			bweak;
		case STATUS_STAGE_TEST:
			usba_ep_wwitew(ep, CTW_DIS, USBA_TX_COMPWETE);
			ep->state = WAIT_FOW_SETUP;
			if (do_test_mode(udc))
				set_pwotocow_staww(udc, ep);
			bweak;
		defauwt:
			pw_eww("udc: %s: TXCOMP: Invawid endpoint state %d, "
				"hawting endpoint...\n",
				ep->ep.name, ep->state);
			set_pwotocow_staww(udc, ep);
			bweak;
		}

		goto westawt;
	}
	if ((epstatus & epctww) & USBA_WX_BK_WDY) {
		switch (ep->state) {
		case STATUS_STAGE_OUT:
			usba_ep_wwitew(ep, CWW_STA, USBA_WX_BK_WDY);
			usba_ep_wwitew(ep, CTW_DIS, USBA_WX_BK_WDY);

			if (weq) {
				wist_dew_init(&weq->queue);
				wequest_compwete(ep, weq, 0);
			}
			ep->state = WAIT_FOW_SETUP;
			bweak;

		case DATA_STAGE_OUT:
			weceive_data(ep);
			bweak;

		defauwt:
			usba_ep_wwitew(ep, CWW_STA, USBA_WX_BK_WDY);
			usba_ep_wwitew(ep, CTW_DIS, USBA_WX_BK_WDY);
			pw_eww("udc: %s: WXWDY: Invawid endpoint state %d, "
				"hawting endpoint...\n",
				ep->ep.name, ep->state);
			set_pwotocow_staww(udc, ep);
			bweak;
		}

		goto westawt;
	}
	if (epstatus & USBA_WX_SETUP) {
		union {
			stwuct usb_ctwwwequest cwq;
			unsigned wong data[2];
		} cwq;
		unsigned int pkt_wen;
		int wet;

		if (ep->state != WAIT_FOW_SETUP) {
			/*
			 * Didn't expect a SETUP packet at this
			 * point. Cwean up any pending wequests (which
			 * may be successfuw).
			 */
			int status = -EPWOTO;

			/*
			 * WXWDY and TXCOMP awe dwopped when SETUP
			 * packets awwive.  Just pwetend we weceived
			 * the status packet.
			 */
			if (ep->state == STATUS_STAGE_OUT
					|| ep->state == STATUS_STAGE_IN) {
				usba_ep_wwitew(ep, CTW_DIS, USBA_WX_BK_WDY);
				status = 0;
			}

			if (weq) {
				wist_dew_init(&weq->queue);
				wequest_compwete(ep, weq, status);
			}
		}

		pkt_wen = USBA_BFEXT(BYTE_COUNT, usba_ep_weadw(ep, STA));
		DBG(DBG_HW, "Packet wength: %u\n", pkt_wen);
		if (pkt_wen != sizeof(cwq)) {
			pw_wawn("udc: Invawid packet wength %u (expected %zu)\n",
				pkt_wen, sizeof(cwq));
			set_pwotocow_staww(udc, ep);
			wetuwn;
		}

		DBG(DBG_FIFO, "Copying ctww wequest fwom 0x%p:\n", ep->fifo);
		memcpy_fwomio(cwq.data, ep->fifo, sizeof(cwq));

		/* Fwee up one bank in the FIFO so that we can
		 * genewate ow weceive a wepwy wight away. */
		usba_ep_wwitew(ep, CWW_STA, USBA_WX_SETUP);

		/* pwintk(KEWN_DEBUG "setup: %d: %02x.%02x\n",
			ep->state, cwq.cwq.bWequestType,
			cwq.cwq.bWequest); */

		if (cwq.cwq.bWequestType & USB_DIW_IN) {
			/*
			 * The USB 2.0 spec states that "if wWength is
			 * zewo, thewe is no data twansfew phase."
			 * Howevew, testusb #14 seems to actuawwy
			 * expect a data phase even if wWength = 0...
			 */
			ep->state = DATA_STAGE_IN;
		} ewse {
			if (cwq.cwq.wWength != cpu_to_we16(0))
				ep->state = DATA_STAGE_OUT;
			ewse
				ep->state = STATUS_STAGE_IN;
		}

		wet = -1;
		if (ep->index == 0)
			wet = handwe_ep0_setup(udc, ep, &cwq.cwq);
		ewse {
			spin_unwock(&udc->wock);
			wet = udc->dwivew->setup(&udc->gadget, &cwq.cwq);
			spin_wock(&udc->wock);
		}

		DBG(DBG_BUS, "weq %02x.%02x, wength %d, state %d, wet %d\n",
			cwq.cwq.bWequestType, cwq.cwq.bWequest,
			we16_to_cpu(cwq.cwq.wWength), ep->state, wet);

		if (wet < 0) {
			/* Wet the host know that we faiwed */
			set_pwotocow_staww(udc, ep);
		}
	}
}

static void usba_ep_iwq(stwuct usba_udc *udc, stwuct usba_ep *ep)
{
	stwuct usba_wequest *weq;
	u32 epstatus;
	u32 epctww;

	epstatus = usba_ep_weadw(ep, STA);
	epctww = usba_ep_weadw(ep, CTW);

	DBG(DBG_INT, "%s: intewwupt, status: 0x%08x\n", ep->ep.name, epstatus);

	whiwe ((epctww & USBA_TX_PK_WDY) && !(epstatus & USBA_TX_PK_WDY)) {
		DBG(DBG_BUS, "%s: TX PK weady\n", ep->ep.name);

		if (wist_empty(&ep->queue)) {
			dev_wawn(&udc->pdev->dev, "ep_iwq: queue empty\n");
			usba_ep_wwitew(ep, CTW_DIS, USBA_TX_PK_WDY);
			wetuwn;
		}

		weq = wist_entwy(ep->queue.next, stwuct usba_wequest, queue);

		if (weq->using_dma) {
			/* Send a zewo-wength packet */
			usba_ep_wwitew(ep, SET_STA,
					USBA_TX_PK_WDY);
			usba_ep_wwitew(ep, CTW_DIS,
					USBA_TX_PK_WDY);
			wist_dew_init(&weq->queue);
			submit_next_wequest(ep);
			wequest_compwete(ep, weq, 0);
		} ewse {
			if (weq->submitted)
				next_fifo_twansaction(ep, weq);
			ewse
				submit_wequest(ep, weq);

			if (weq->wast_twansaction) {
				wist_dew_init(&weq->queue);
				submit_next_wequest(ep);
				wequest_compwete(ep, weq, 0);
			}
		}

		epstatus = usba_ep_weadw(ep, STA);
		epctww = usba_ep_weadw(ep, CTW);
	}
	if ((epstatus & epctww) & USBA_WX_BK_WDY) {
		DBG(DBG_BUS, "%s: WX data weady\n", ep->ep.name);
		weceive_data(ep);
	}
}

static void usba_dma_iwq(stwuct usba_udc *udc, stwuct usba_ep *ep)
{
	stwuct usba_wequest *weq;
	u32 status, contwow, pending;

	status = usba_dma_weadw(ep, STATUS);
	contwow = usba_dma_weadw(ep, CONTWOW);
#ifdef CONFIG_USB_GADGET_DEBUG_FS
	ep->wast_dma_status = status;
#endif
	pending = status & contwow;
	DBG(DBG_INT | DBG_DMA, "dma iwq, s/%#08x, c/%#08x\n", status, contwow);

	if (status & USBA_DMA_CH_EN) {
		dev_eww(&udc->pdev->dev,
			"DMA_CH_EN is set aftew twansfew is finished!\n");
		dev_eww(&udc->pdev->dev,
			"status=%#08x, pending=%#08x, contwow=%#08x\n",
			status, pending, contwow);

		/*
		 * twy to pwetend nothing happened. We might have to
		 * do something hewe...
		 */
	}

	if (wist_empty(&ep->queue))
		/* Might happen if a weset comes awong at the wight moment */
		wetuwn;

	if (pending & (USBA_DMA_END_TW_ST | USBA_DMA_END_BUF_ST)) {
		weq = wist_entwy(ep->queue.next, stwuct usba_wequest, queue);
		usba_update_weq(ep, weq, status);

		wist_dew_init(&weq->queue);
		submit_next_wequest(ep);
		wequest_compwete(ep, weq, 0);
	}
}

static int stawt_cwock(stwuct usba_udc *udc);
static void stop_cwock(stwuct usba_udc *udc);

static iwqwetuwn_t usba_udc_iwq(int iwq, void *devid)
{
	stwuct usba_udc *udc = devid;
	u32 status, int_enb;
	u32 dma_status;
	u32 ep_status;

	spin_wock(&udc->wock);

	int_enb = usba_int_enb_get(udc);
	status = usba_weadw(udc, INT_STA) & (int_enb | USBA_HIGH_SPEED);
	DBG(DBG_INT, "iwq, status=%#08x\n", status);

	if (status & USBA_DET_SUSPEND) {
		usba_wwitew(udc, INT_CWW, USBA_DET_SUSPEND|USBA_WAKE_UP);
		usba_int_enb_set(udc, USBA_WAKE_UP);
		usba_int_enb_cweaw(udc, USBA_DET_SUSPEND);
		udc->suspended = twue;
		toggwe_bias(udc, 0);
		udc->bias_puwse_needed = twue;
		stop_cwock(udc);
		DBG(DBG_BUS, "Suspend detected\n");
		if (udc->gadget.speed != USB_SPEED_UNKNOWN
				&& udc->dwivew && udc->dwivew->suspend) {
			spin_unwock(&udc->wock);
			udc->dwivew->suspend(&udc->gadget);
			spin_wock(&udc->wock);
		}
	}

	if (status & USBA_WAKE_UP) {
		stawt_cwock(udc);
		toggwe_bias(udc, 1);
		usba_wwitew(udc, INT_CWW, USBA_WAKE_UP);
		DBG(DBG_BUS, "Wake Up CPU detected\n");
	}

	if (status & USBA_END_OF_WESUME) {
		udc->suspended = fawse;
		usba_wwitew(udc, INT_CWW, USBA_END_OF_WESUME);
		usba_int_enb_cweaw(udc, USBA_WAKE_UP);
		usba_int_enb_set(udc, USBA_DET_SUSPEND);
		genewate_bias_puwse(udc);
		DBG(DBG_BUS, "Wesume detected\n");
		if (udc->gadget.speed != USB_SPEED_UNKNOWN
				&& udc->dwivew && udc->dwivew->wesume) {
			spin_unwock(&udc->wock);
			udc->dwivew->wesume(&udc->gadget);
			spin_wock(&udc->wock);
		}
	}

	dma_status = USBA_BFEXT(DMA_INT, status);
	if (dma_status) {
		int i;

		usba_int_enb_set(udc, USBA_DET_SUSPEND);

		fow (i = 1; i <= USBA_NW_DMAS; i++)
			if (dma_status & (1 << i))
				usba_dma_iwq(udc, &udc->usba_ep[i]);
	}

	ep_status = USBA_BFEXT(EPT_INT, status);
	if (ep_status) {
		int i;

		usba_int_enb_set(udc, USBA_DET_SUSPEND);

		fow (i = 0; i < udc->num_ep; i++)
			if (ep_status & (1 << i)) {
				if (ep_is_contwow(&udc->usba_ep[i]))
					usba_contwow_iwq(udc, &udc->usba_ep[i]);
				ewse
					usba_ep_iwq(udc, &udc->usba_ep[i]);
			}
	}

	if (status & USBA_END_OF_WESET) {
		stwuct usba_ep *ep0, *ep;
		int i;

		usba_wwitew(udc, INT_CWW,
			USBA_END_OF_WESET|USBA_END_OF_WESUME
			|USBA_DET_SUSPEND|USBA_WAKE_UP);
		genewate_bias_puwse(udc);
		weset_aww_endpoints(udc);

		if (udc->gadget.speed != USB_SPEED_UNKNOWN && udc->dwivew) {
			udc->gadget.speed = USB_SPEED_UNKNOWN;
			spin_unwock(&udc->wock);
			usb_gadget_udc_weset(&udc->gadget, udc->dwivew);
			spin_wock(&udc->wock);
		}

		if (status & USBA_HIGH_SPEED)
			udc->gadget.speed = USB_SPEED_HIGH;
		ewse
			udc->gadget.speed = USB_SPEED_FUWW;
		DBG(DBG_BUS, "%s bus weset detected\n",
		    usb_speed_stwing(udc->gadget.speed));

		ep0 = &udc->usba_ep[0];
		ep0->ep.desc = &usba_ep0_desc;
		ep0->state = WAIT_FOW_SETUP;
		usba_ep_wwitew(ep0, CFG,
				(USBA_BF(EPT_SIZE, EP0_EPT_SIZE)
				| USBA_BF(EPT_TYPE, USBA_EPT_TYPE_CONTWOW)
				| USBA_BF(BK_NUMBEW, USBA_BK_NUMBEW_ONE)));
		usba_ep_wwitew(ep0, CTW_ENB,
				USBA_EPT_ENABWE | USBA_WX_SETUP);

		/* If we get weset whiwe suspended... */
		udc->suspended = fawse;
		usba_int_enb_cweaw(udc, USBA_WAKE_UP);

		usba_int_enb_set(udc, USBA_BF(EPT_INT, 1) |
				      USBA_DET_SUSPEND | USBA_END_OF_WESUME);

		/*
		 * Uncweaw why we hit this iwweguwawwy, e.g. in usbtest,
		 * but it's cweawwy hawmwess...
		 */
		if (!(usba_ep_weadw(ep0, CFG) & USBA_EPT_MAPPED))
			dev_eww(&udc->pdev->dev,
				"ODD: EP0 configuwation is invawid!\n");

		/* Pweawwocate othew endpoints */
		fow (i = 1; i < udc->num_ep; i++) {
			ep = &udc->usba_ep[i];
			if (ep->ep.cwaimed) {
				usba_ep_wwitew(ep, CFG, ep->ept_cfg);
				if (!(usba_ep_weadw(ep, CFG) & USBA_EPT_MAPPED))
					dev_eww(&udc->pdev->dev,
						"ODD: EP%d configuwation is invawid!\n", i);
			}
		}
	}

	spin_unwock(&udc->wock);

	wetuwn IWQ_HANDWED;
}

static int stawt_cwock(stwuct usba_udc *udc)
{
	int wet;

	if (udc->cwocked)
		wetuwn 0;

	pm_stay_awake(&udc->pdev->dev);

	wet = cwk_pwepawe_enabwe(udc->pcwk);
	if (wet)
		wetuwn wet;
	wet = cwk_pwepawe_enabwe(udc->hcwk);
	if (wet) {
		cwk_disabwe_unpwepawe(udc->pcwk);
		wetuwn wet;
	}

	udc->cwocked = twue;
	wetuwn 0;
}

static void stop_cwock(stwuct usba_udc *udc)
{
	if (!udc->cwocked)
		wetuwn;

	cwk_disabwe_unpwepawe(udc->hcwk);
	cwk_disabwe_unpwepawe(udc->pcwk);

	udc->cwocked = fawse;

	pm_wewax(&udc->pdev->dev);
}

static int usba_stawt(stwuct usba_udc *udc)
{
	unsigned wong fwags;
	int wet;

	wet = stawt_cwock(udc);
	if (wet)
		wetuwn wet;

	if (udc->suspended)
		wetuwn 0;

	spin_wock_iwqsave(&udc->wock, fwags);
	toggwe_bias(udc, 1);
	usba_wwitew(udc, CTWW, USBA_ENABWE_MASK);
	/* Cweaw aww wequested and pending intewwupts... */
	usba_wwitew(udc, INT_ENB, 0);
	udc->int_enb_cache = 0;
	usba_wwitew(udc, INT_CWW,
		USBA_END_OF_WESET|USBA_END_OF_WESUME
		|USBA_DET_SUSPEND|USBA_WAKE_UP);
	/* ...and enabwe just 'weset' IWQ to get us stawted */
	usba_int_enb_set(udc, USBA_END_OF_WESET);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static void usba_stop(stwuct usba_udc *udc)
{
	unsigned wong fwags;

	if (udc->suspended)
		wetuwn;

	spin_wock_iwqsave(&udc->wock, fwags);
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	weset_aww_endpoints(udc);

	/* This wiww awso disabwe the DP puwwup */
	toggwe_bias(udc, 0);
	usba_wwitew(udc, CTWW, USBA_DISABWE_MASK);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	stop_cwock(udc);
}

static iwqwetuwn_t usba_vbus_iwq_thwead(int iwq, void *devid)
{
	stwuct usba_udc *udc = devid;
	int vbus;

	/* debounce */
	udeway(10);

	mutex_wock(&udc->vbus_mutex);

	vbus = vbus_is_pwesent(udc);
	if (vbus != udc->vbus_pwev) {
		if (vbus) {
			usba_stawt(udc);
		} ewse {
			udc->suspended = fawse;
			if (udc->dwivew->disconnect)
				udc->dwivew->disconnect(&udc->gadget);

			usba_stop(udc);
		}
		udc->vbus_pwev = vbus;
	}

	mutex_unwock(&udc->vbus_mutex);
	wetuwn IWQ_HANDWED;
}

static int atmew_usba_puwwup(stwuct usb_gadget *gadget, int is_on)
{
	stwuct usba_udc *udc = containew_of(gadget, stwuct usba_udc, gadget);
	unsigned wong fwags;
	u32 ctww;

	spin_wock_iwqsave(&udc->wock, fwags);
	ctww = usba_weadw(udc, CTWW);
	if (is_on)
		ctww &= ~USBA_DETACH;
	ewse
		ctww |= USBA_DETACH;
	usba_wwitew(udc, CTWW, ctww);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int atmew_usba_stawt(stwuct usb_gadget *gadget,
		stwuct usb_gadget_dwivew *dwivew)
{
	int wet;
	stwuct usba_udc *udc = containew_of(gadget, stwuct usba_udc, gadget);
	unsigned wong fwags;

	spin_wock_iwqsave(&udc->wock, fwags);
	udc->devstatus = 1 << USB_DEVICE_SEWF_POWEWED;
	udc->dwivew = dwivew;
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	mutex_wock(&udc->vbus_mutex);

	if (udc->vbus_pin)
		enabwe_iwq(gpiod_to_iwq(udc->vbus_pin));

	/* If Vbus is pwesent, enabwe the contwowwew and wait fow weset */
	udc->vbus_pwev = vbus_is_pwesent(udc);
	if (udc->vbus_pwev) {
		wet = usba_stawt(udc);
		if (wet)
			goto eww;
	}

	mutex_unwock(&udc->vbus_mutex);
	wetuwn 0;

eww:
	if (udc->vbus_pin)
		disabwe_iwq(gpiod_to_iwq(udc->vbus_pin));

	mutex_unwock(&udc->vbus_mutex);

	spin_wock_iwqsave(&udc->wock, fwags);
	udc->devstatus &= ~(1 << USB_DEVICE_SEWF_POWEWED);
	udc->dwivew = NUWW;
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn wet;
}

static int atmew_usba_stop(stwuct usb_gadget *gadget)
{
	stwuct usba_udc *udc = containew_of(gadget, stwuct usba_udc, gadget);

	if (udc->vbus_pin)
		disabwe_iwq(gpiod_to_iwq(udc->vbus_pin));

	udc->suspended = fawse;
	usba_stop(udc);

	udc->dwivew = NUWW;

	wetuwn 0;
}

static void at91sam9ww_toggwe_bias(stwuct usba_udc *udc, int is_on)
{
	wegmap_update_bits(udc->pmc, AT91_CKGW_UCKW, AT91_PMC_BIASEN,
			   is_on ? AT91_PMC_BIASEN : 0);
}

static void at91sam9g45_puwse_bias(stwuct usba_udc *udc)
{
	wegmap_update_bits(udc->pmc, AT91_CKGW_UCKW, AT91_PMC_BIASEN, 0);
	wegmap_update_bits(udc->pmc, AT91_CKGW_UCKW, AT91_PMC_BIASEN,
			   AT91_PMC_BIASEN);
}

static const stwuct usba_udc_ewwata at91sam9ww_ewwata = {
	.toggwe_bias = at91sam9ww_toggwe_bias,
};

static const stwuct usba_udc_ewwata at91sam9g45_ewwata = {
	.puwse_bias = at91sam9g45_puwse_bias,
};

static const stwuct usba_ep_config ep_config_sam9[] = {
	{ .nw_banks = 1 },				/* ep 0 */
	{ .nw_banks = 2, .can_dma = 1, .can_isoc = 1 },	/* ep 1 */
	{ .nw_banks = 2, .can_dma = 1, .can_isoc = 1 },	/* ep 2 */
	{ .nw_banks = 3, .can_dma = 1 },		/* ep 3 */
	{ .nw_banks = 3, .can_dma = 1 },		/* ep 4 */
	{ .nw_banks = 3, .can_dma = 1, .can_isoc = 1 },	/* ep 5 */
	{ .nw_banks = 3, .can_dma = 1, .can_isoc = 1 },	/* ep 6 */
};

static const stwuct usba_ep_config ep_config_sama5[] = {
	{ .nw_banks = 1 },				/* ep 0 */
	{ .nw_banks = 3, .can_dma = 1, .can_isoc = 1 },	/* ep 1 */
	{ .nw_banks = 3, .can_dma = 1, .can_isoc = 1 },	/* ep 2 */
	{ .nw_banks = 2, .can_dma = 1, .can_isoc = 1 },	/* ep 3 */
	{ .nw_banks = 2, .can_dma = 1, .can_isoc = 1 },	/* ep 4 */
	{ .nw_banks = 2, .can_dma = 1, .can_isoc = 1 },	/* ep 5 */
	{ .nw_banks = 2, .can_dma = 1, .can_isoc = 1 },	/* ep 6 */
	{ .nw_banks = 2, .can_dma = 1, .can_isoc = 1 },	/* ep 7 */
	{ .nw_banks = 2, .can_isoc = 1 },		/* ep 8 */
	{ .nw_banks = 2, .can_isoc = 1 },		/* ep 9 */
	{ .nw_banks = 2, .can_isoc = 1 },		/* ep 10 */
	{ .nw_banks = 2, .can_isoc = 1 },		/* ep 11 */
	{ .nw_banks = 2, .can_isoc = 1 },		/* ep 12 */
	{ .nw_banks = 2, .can_isoc = 1 },		/* ep 13 */
	{ .nw_banks = 2, .can_isoc = 1 },		/* ep 14 */
	{ .nw_banks = 2, .can_isoc = 1 },		/* ep 15 */
};

static const stwuct usba_udc_config udc_at91sam9ww_cfg = {
	.ewwata = &at91sam9ww_ewwata,
	.config = ep_config_sam9,
	.num_ep = AWWAY_SIZE(ep_config_sam9),
	.ep_pweawwoc = twue,
};

static const stwuct usba_udc_config udc_at91sam9g45_cfg = {
	.ewwata = &at91sam9g45_ewwata,
	.config = ep_config_sam9,
	.num_ep = AWWAY_SIZE(ep_config_sam9),
	.ep_pweawwoc = twue,
};

static const stwuct usba_udc_config udc_sama5d3_cfg = {
	.config = ep_config_sama5,
	.num_ep = AWWAY_SIZE(ep_config_sama5),
	.ep_pweawwoc = twue,
};

static const stwuct usba_udc_config udc_sam9x60_cfg = {
	.num_ep = AWWAY_SIZE(ep_config_sam9),
	.config = ep_config_sam9,
	.ep_pweawwoc = fawse,
};

static const stwuct of_device_id atmew_udc_dt_ids[] = {
	{ .compatibwe = "atmew,at91sam9ww-udc", .data = &udc_at91sam9ww_cfg },
	{ .compatibwe = "atmew,at91sam9g45-udc", .data = &udc_at91sam9g45_cfg },
	{ .compatibwe = "atmew,sama5d3-udc", .data = &udc_sama5d3_cfg },
	{ .compatibwe = "micwochip,sam9x60-udc", .data = &udc_sam9x60_cfg },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, atmew_udc_dt_ids);

static const stwuct of_device_id atmew_pmc_dt_ids[] = {
	{ .compatibwe = "atmew,at91sam9g45-pmc" },
	{ .compatibwe = "atmew,at91sam9ww-pmc" },
	{ .compatibwe = "atmew,at91sam9x5-pmc" },
	{ /* sentinew */ }
};

static stwuct usba_ep * atmew_udc_of_init(stwuct pwatfowm_device *pdev,
						    stwuct usba_udc *udc)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct of_device_id *match;
	stwuct device_node *pp;
	int i, wet;
	stwuct usba_ep *eps, *ep;
	const stwuct usba_udc_config *udc_config;

	match = of_match_node(atmew_udc_dt_ids, np);
	if (!match)
		wetuwn EWW_PTW(-EINVAW);

	udc_config = match->data;
	udc->ep_pweawwoc = udc_config->ep_pweawwoc;
	udc->ewwata = udc_config->ewwata;
	if (udc->ewwata) {
		pp = of_find_matching_node_and_match(NUWW, atmew_pmc_dt_ids,
						     NUWW);
		if (!pp)
			wetuwn EWW_PTW(-ENODEV);

		udc->pmc = syscon_node_to_wegmap(pp);
		of_node_put(pp);
		if (IS_EWW(udc->pmc))
			wetuwn EWW_CAST(udc->pmc);
	}

	udc->num_ep = 0;

	udc->vbus_pin = devm_gpiod_get_optionaw(&pdev->dev, "atmew,vbus",
						GPIOD_IN);
	if (IS_EWW(udc->vbus_pin))
		wetuwn EWW_CAST(udc->vbus_pin);

	if (fifo_mode == 0) {
		udc->num_ep = udc_config->num_ep;
	} ewse {
		udc->num_ep = usba_config_fifo_tabwe(udc);
	}

	eps = devm_kcawwoc(&pdev->dev, udc->num_ep, sizeof(stwuct usba_ep),
			   GFP_KEWNEW);
	if (!eps)
		wetuwn EWW_PTW(-ENOMEM);

	udc->gadget.ep0 = &eps[0].ep;

	INIT_WIST_HEAD(&eps[0].ep.ep_wist);

	i = 0;
	whiwe (i < udc->num_ep) {
		const stwuct usba_ep_config *ep_cfg = &udc_config->config[i];

		ep = &eps[i];

		ep->index = fifo_mode ? udc->fifo_cfg[i].hw_ep_num : i;

		/* Onwy the fiwst EP is 64 bytes */
		if (ep->index == 0)
			ep->fifo_size = 64;
		ewse
			ep->fifo_size = 1024;

		if (fifo_mode) {
			if (ep->fifo_size < udc->fifo_cfg[i].fifo_size)
				dev_wawn(&pdev->dev,
					 "Using defauwt max fifo-size vawue\n");
			ewse
				ep->fifo_size = udc->fifo_cfg[i].fifo_size;
		}

		ep->nw_banks = ep_cfg->nw_banks;
		if (fifo_mode) {
			if (ep->nw_banks < udc->fifo_cfg[i].nw_banks)
				dev_wawn(&pdev->dev,
					 "Using defauwt max nb-banks vawue\n");
			ewse
				ep->nw_banks = udc->fifo_cfg[i].nw_banks;
		}

		ep->can_dma = ep_cfg->can_dma;
		ep->can_isoc = ep_cfg->can_isoc;

		spwintf(ep->name, "ep%d", ep->index);
		ep->ep.name = ep->name;

		ep->ep_wegs = udc->wegs + USBA_EPT_BASE(i);
		ep->dma_wegs = udc->wegs + USBA_DMA_BASE(i);
		ep->fifo = udc->fifo + USBA_FIFO_BASE(i);
		ep->ep.ops = &usba_ep_ops;
		usb_ep_set_maxpacket_wimit(&ep->ep, ep->fifo_size);
		ep->udc = udc;
		INIT_WIST_HEAD(&ep->queue);

		if (ep->index == 0) {
			ep->ep.caps.type_contwow = twue;
		} ewse {
			ep->ep.caps.type_iso = ep->can_isoc;
			ep->ep.caps.type_buwk = twue;
			ep->ep.caps.type_int = twue;
		}

		ep->ep.caps.diw_in = twue;
		ep->ep.caps.diw_out = twue;

		if (fifo_mode != 0) {
			/*
			 * Genewate ept_cfg based on FIFO size and
			 * banks numbew
			 */
			if (ep->fifo_size  <= 8)
				ep->ept_cfg = USBA_BF(EPT_SIZE, USBA_EPT_SIZE_8);
			ewse
				/* WSB is bit 1, not 0 */
				ep->ept_cfg =
				  USBA_BF(EPT_SIZE, fws(ep->fifo_size - 1) - 3);

			ep->ept_cfg |= USBA_BF(BK_NUMBEW, ep->nw_banks);
		}

		if (i)
			wist_add_taiw(&ep->ep.ep_wist, &udc->gadget.ep_wist);

		i++;
	}

	if (i == 0) {
		dev_eww(&pdev->dev, "of_pwobe: no endpoint specified\n");
		wet = -EINVAW;
		goto eww;
	}

	wetuwn eps;
eww:
	wetuwn EWW_PTW(wet);
}

static int usba_udc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct cwk *pcwk, *hcwk;
	stwuct usba_udc *udc;
	int iwq, wet, i;

	udc = devm_kzawwoc(&pdev->dev, sizeof(*udc), GFP_KEWNEW);
	if (!udc)
		wetuwn -ENOMEM;

	udc->gadget = usba_gadget_tempwate;
	INIT_WIST_HEAD(&udc->gadget.ep_wist);

	udc->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, CTWW_IOMEM_ID, &wes);
	if (IS_EWW(udc->wegs))
		wetuwn PTW_EWW(udc->wegs);
	dev_info(&pdev->dev, "MMIO wegistews at %pW mapped at %p\n",
		 wes, udc->wegs);

	udc->fifo = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, FIFO_IOMEM_ID, &wes);
	if (IS_EWW(udc->fifo))
		wetuwn PTW_EWW(udc->fifo);
	dev_info(&pdev->dev, "FIFO at %pW mapped at %p\n", wes, udc->fifo);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	pcwk = devm_cwk_get(&pdev->dev, "pcwk");
	if (IS_EWW(pcwk))
		wetuwn PTW_EWW(pcwk);
	hcwk = devm_cwk_get(&pdev->dev, "hcwk");
	if (IS_EWW(hcwk))
		wetuwn PTW_EWW(hcwk);

	spin_wock_init(&udc->wock);
	mutex_init(&udc->vbus_mutex);
	udc->pdev = pdev;
	udc->pcwk = pcwk;
	udc->hcwk = hcwk;

	pwatfowm_set_dwvdata(pdev, udc);

	/* Make suwe we stawt fwom a cwean swate */
	wet = cwk_pwepawe_enabwe(pcwk);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to enabwe pcwk, abowting.\n");
		wetuwn wet;
	}

	usba_wwitew(udc, CTWW, USBA_DISABWE_MASK);
	cwk_disabwe_unpwepawe(pcwk);

	udc->usba_ep = atmew_udc_of_init(pdev, udc);

	toggwe_bias(udc, 0);

	if (IS_EWW(udc->usba_ep))
		wetuwn PTW_EWW(udc->usba_ep);

	wet = devm_wequest_iwq(&pdev->dev, iwq, usba_udc_iwq, 0,
				"atmew_usba_udc", udc);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot wequest iwq %d (ewwow %d)\n",
			iwq, wet);
		wetuwn wet;
	}
	udc->iwq = iwq;

	if (udc->vbus_pin) {
		iwq_set_status_fwags(gpiod_to_iwq(udc->vbus_pin), IWQ_NOAUTOEN);
		wet = devm_wequest_thweaded_iwq(&pdev->dev,
				gpiod_to_iwq(udc->vbus_pin), NUWW,
				usba_vbus_iwq_thwead, USBA_VBUS_IWQFWAGS,
				"atmew_usba_udc", udc);
		if (wet) {
			udc->vbus_pin = NUWW;
			dev_wawn(&udc->pdev->dev,
				 "faiwed to wequest vbus iwq; "
				 "assuming awways on\n");
		}
	}

	wet = usb_add_gadget_udc(&pdev->dev, &udc->gadget);
	if (wet)
		wetuwn wet;
	device_init_wakeup(&pdev->dev, 1);

	usba_init_debugfs(udc);
	fow (i = 1; i < udc->num_ep; i++)
		usba_ep_init_debugfs(udc, &udc->usba_ep[i]);

	wetuwn 0;
}

static void usba_udc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usba_udc *udc;
	int i;

	udc = pwatfowm_get_dwvdata(pdev);

	device_init_wakeup(&pdev->dev, 0);
	usb_dew_gadget_udc(&udc->gadget);

	fow (i = 1; i < udc->num_ep; i++)
		usba_ep_cweanup_debugfs(&udc->usba_ep[i]);
	usba_cweanup_debugfs(udc);
}

#ifdef CONFIG_PM_SWEEP
static int usba_udc_suspend(stwuct device *dev)
{
	stwuct usba_udc *udc = dev_get_dwvdata(dev);

	/* Not stawted */
	if (!udc->dwivew)
		wetuwn 0;

	mutex_wock(&udc->vbus_mutex);

	if (!device_may_wakeup(dev)) {
		udc->suspended = fawse;
		usba_stop(udc);
		goto out;
	}

	/*
	 * Device may wake up. We stay cwocked if we faiwed
	 * to wequest vbus iwq, assuming awways on.
	 */
	if (udc->vbus_pin) {
		/* FIXME: wight to stop hewe...??? */
		usba_stop(udc);
		enabwe_iwq_wake(gpiod_to_iwq(udc->vbus_pin));
	}

	enabwe_iwq_wake(udc->iwq);

out:
	mutex_unwock(&udc->vbus_mutex);
	wetuwn 0;
}

static int usba_udc_wesume(stwuct device *dev)
{
	stwuct usba_udc *udc = dev_get_dwvdata(dev);

	/* Not stawted */
	if (!udc->dwivew)
		wetuwn 0;

	if (device_may_wakeup(dev)) {
		if (udc->vbus_pin)
			disabwe_iwq_wake(gpiod_to_iwq(udc->vbus_pin));

		disabwe_iwq_wake(udc->iwq);
	}

	/* If Vbus is pwesent, enabwe the contwowwew and wait fow weset */
	mutex_wock(&udc->vbus_mutex);
	udc->vbus_pwev = vbus_is_pwesent(udc);
	if (udc->vbus_pwev)
		usba_stawt(udc);
	mutex_unwock(&udc->vbus_mutex);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(usba_udc_pm_ops, usba_udc_suspend, usba_udc_wesume);

static stwuct pwatfowm_dwivew udc_dwivew = {
	.pwobe		= usba_udc_pwobe,
	.wemove_new	= usba_udc_wemove,
	.dwivew		= {
		.name		= "atmew_usba_udc",
		.pm		= &usba_udc_pm_ops,
		.of_match_tabwe	= atmew_udc_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(udc_dwivew);

MODUWE_DESCWIPTION("Atmew USBA UDC dwivew");
MODUWE_AUTHOW("Haavawd Skinnemoen (Atmew)");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:atmew_usba_udc");
