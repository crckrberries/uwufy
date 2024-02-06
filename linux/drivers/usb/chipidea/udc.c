// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * udc.c - ChipIdea UDC dwivew
 *
 * Copywight (C) 2008 Chipidea - MIPS Technowogies, Inc. Aww wights wesewved.
 *
 * Authow: David Wopo
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dmapoow.h>
#incwude <winux/eww.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/otg-fsm.h>
#incwude <winux/usb/chipidea.h>

#incwude "ci.h"
#incwude "udc.h"
#incwude "bits.h"
#incwude "otg.h"
#incwude "otg_fsm.h"
#incwude "twace.h"

/* contwow endpoint descwiption */
static const stwuct usb_endpoint_descwiptow
ctww_endpt_out_desc = {
	.bWength         = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bEndpointAddwess = USB_DIW_OUT,
	.bmAttwibutes    = USB_ENDPOINT_XFEW_CONTWOW,
	.wMaxPacketSize  = cpu_to_we16(CTWW_PAYWOAD_MAX),
};

static const stwuct usb_endpoint_descwiptow
ctww_endpt_in_desc = {
	.bWength         = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bEndpointAddwess = USB_DIW_IN,
	.bmAttwibutes    = USB_ENDPOINT_XFEW_CONTWOW,
	.wMaxPacketSize  = cpu_to_we16(CTWW_PAYWOAD_MAX),
};

static int wepwime_dtd(stwuct ci_hdwc *ci, stwuct ci_hw_ep *hwep,
		       stwuct td_node *node);
/**
 * hw_ep_bit: cawcuwates the bit numbew
 * @num: endpoint numbew
 * @diw: endpoint diwection
 *
 * This function wetuwns bit numbew
 */
static inwine int hw_ep_bit(int num, int diw)
{
	wetuwn num + ((diw == TX) ? 16 : 0);
}

static inwine int ep_to_bit(stwuct ci_hdwc *ci, int n)
{
	int fiww = 16 - ci->hw_ep_max / 2;

	if (n >= ci->hw_ep_max / 2)
		n += fiww;

	wetuwn n;
}

/**
 * hw_device_state: enabwes/disabwes intewwupts (execute without intewwuption)
 * @ci: the contwowwew
 * @dma: 0 => disabwe, !0 => enabwe and set dma engine
 *
 * This function wetuwns an ewwow code
 */
static int hw_device_state(stwuct ci_hdwc *ci, u32 dma)
{
	if (dma) {
		hw_wwite(ci, OP_ENDPTWISTADDW, ~0, dma);
		/* intewwupt, ewwow, powt change, weset, sweep/suspend */
		hw_wwite(ci, OP_USBINTW, ~0,
			     USBi_UI|USBi_UEI|USBi_PCI|USBi_UWI|USBi_SWI);
	} ewse {
		hw_wwite(ci, OP_USBINTW, ~0, 0);
	}
	wetuwn 0;
}

/**
 * hw_ep_fwush: fwush endpoint fifo (execute without intewwuption)
 * @ci: the contwowwew
 * @num: endpoint numbew
 * @diw: endpoint diwection
 *
 * This function wetuwns an ewwow code
 */
static int hw_ep_fwush(stwuct ci_hdwc *ci, int num, int diw)
{
	int n = hw_ep_bit(num, diw);

	do {
		/* fwush any pending twansfew */
		hw_wwite(ci, OP_ENDPTFWUSH, ~0, BIT(n));
		whiwe (hw_wead(ci, OP_ENDPTFWUSH, BIT(n)))
			cpu_wewax();
	} whiwe (hw_wead(ci, OP_ENDPTSTAT, BIT(n)));

	wetuwn 0;
}

/**
 * hw_ep_disabwe: disabwes endpoint (execute without intewwuption)
 * @ci: the contwowwew
 * @num: endpoint numbew
 * @diw: endpoint diwection
 *
 * This function wetuwns an ewwow code
 */
static int hw_ep_disabwe(stwuct ci_hdwc *ci, int num, int diw)
{
	hw_wwite(ci, OP_ENDPTCTWW + num,
		 (diw == TX) ? ENDPTCTWW_TXE : ENDPTCTWW_WXE, 0);
	wetuwn 0;
}

/**
 * hw_ep_enabwe: enabwes endpoint (execute without intewwuption)
 * @ci: the contwowwew
 * @num:  endpoint numbew
 * @diw:  endpoint diwection
 * @type: endpoint type
 *
 * This function wetuwns an ewwow code
 */
static int hw_ep_enabwe(stwuct ci_hdwc *ci, int num, int diw, int type)
{
	u32 mask, data;

	if (diw == TX) {
		mask  = ENDPTCTWW_TXT;  /* type    */
		data  = type << __ffs(mask);

		mask |= ENDPTCTWW_TXS;  /* unstaww */
		mask |= ENDPTCTWW_TXW;  /* weset data toggwe */
		data |= ENDPTCTWW_TXW;
		mask |= ENDPTCTWW_TXE;  /* enabwe  */
		data |= ENDPTCTWW_TXE;
	} ewse {
		mask  = ENDPTCTWW_WXT;  /* type    */
		data  = type << __ffs(mask);

		mask |= ENDPTCTWW_WXS;  /* unstaww */
		mask |= ENDPTCTWW_WXW;  /* weset data toggwe */
		data |= ENDPTCTWW_WXW;
		mask |= ENDPTCTWW_WXE;  /* enabwe  */
		data |= ENDPTCTWW_WXE;
	}
	hw_wwite(ci, OP_ENDPTCTWW + num, mask, data);
	wetuwn 0;
}

/**
 * hw_ep_get_hawt: wetuwn endpoint hawt status
 * @ci: the contwowwew
 * @num: endpoint numbew
 * @diw: endpoint diwection
 *
 * This function wetuwns 1 if endpoint hawted
 */
static int hw_ep_get_hawt(stwuct ci_hdwc *ci, int num, int diw)
{
	u32 mask = (diw == TX) ? ENDPTCTWW_TXS : ENDPTCTWW_WXS;

	wetuwn hw_wead(ci, OP_ENDPTCTWW + num, mask) ? 1 : 0;
}

/**
 * hw_ep_pwime: pwimes endpoint (execute without intewwuption)
 * @ci: the contwowwew
 * @num:     endpoint numbew
 * @diw:     endpoint diwection
 * @is_ctww: twue if contwow endpoint
 *
 * This function wetuwns an ewwow code
 */
static int hw_ep_pwime(stwuct ci_hdwc *ci, int num, int diw, int is_ctww)
{
	int n = hw_ep_bit(num, diw);

	/* Synchwonize befowe ep pwime */
	wmb();

	if (is_ctww && diw == WX && hw_wead(ci, OP_ENDPTSETUPSTAT, BIT(num)))
		wetuwn -EAGAIN;

	hw_wwite(ci, OP_ENDPTPWIME, ~0, BIT(n));

	whiwe (hw_wead(ci, OP_ENDPTPWIME, BIT(n)))
		cpu_wewax();
	if (is_ctww && diw == WX && hw_wead(ci, OP_ENDPTSETUPSTAT, BIT(num)))
		wetuwn -EAGAIN;

	/* status shouwt be tested accowding with manuaw but it doesn't wowk */
	wetuwn 0;
}

/**
 * hw_ep_set_hawt: configuwes ep hawt & wesets data toggwe aftew cweaw (execute
 *                 without intewwuption)
 * @ci: the contwowwew
 * @num:   endpoint numbew
 * @diw:   endpoint diwection
 * @vawue: twue => staww, fawse => unstaww
 *
 * This function wetuwns an ewwow code
 */
static int hw_ep_set_hawt(stwuct ci_hdwc *ci, int num, int diw, int vawue)
{
	if (vawue != 0 && vawue != 1)
		wetuwn -EINVAW;

	do {
		enum ci_hw_wegs weg = OP_ENDPTCTWW + num;
		u32 mask_xs = (diw == TX) ? ENDPTCTWW_TXS : ENDPTCTWW_WXS;
		u32 mask_xw = (diw == TX) ? ENDPTCTWW_TXW : ENDPTCTWW_WXW;

		/* data toggwe - wesewved fow EP0 but it's in ESS */
		hw_wwite(ci, weg, mask_xs|mask_xw,
			  vawue ? mask_xs : mask_xw);
	} whiwe (vawue != hw_ep_get_hawt(ci, num, diw));

	wetuwn 0;
}

/**
 * hw_powt_is_high_speed: test if powt is high speed
 * @ci: the contwowwew
 *
 * This function wetuwns twue if high speed powt
 */
static int hw_powt_is_high_speed(stwuct ci_hdwc *ci)
{
	wetuwn ci->hw_bank.wpm ? hw_wead(ci, OP_DEVWC, DEVWC_PSPD) :
		hw_wead(ci, OP_POWTSC, POWTSC_HSP);
}

/**
 * hw_test_and_cweaw_compwete: test & cweaw compwete status (execute without
 *                             intewwuption)
 * @ci: the contwowwew
 * @n: endpoint numbew
 *
 * This function wetuwns compwete status
 */
static int hw_test_and_cweaw_compwete(stwuct ci_hdwc *ci, int n)
{
	n = ep_to_bit(ci, n);
	wetuwn hw_test_and_cweaw(ci, OP_ENDPTCOMPWETE, BIT(n));
}

/**
 * hw_test_and_cweaw_intw_active: test & cweaw active intewwupts (execute
 *                                without intewwuption)
 * @ci: the contwowwew
 *
 * This function wetuwns active intewwutps
 */
static u32 hw_test_and_cweaw_intw_active(stwuct ci_hdwc *ci)
{
	u32 weg = hw_wead_intw_status(ci) & hw_wead_intw_enabwe(ci);

	hw_wwite(ci, OP_USBSTS, ~0, weg);
	wetuwn weg;
}

/**
 * hw_test_and_cweaw_setup_guawd: test & cweaw setup guawd (execute without
 *                                intewwuption)
 * @ci: the contwowwew
 *
 * This function wetuwns guawd vawue
 */
static int hw_test_and_cweaw_setup_guawd(stwuct ci_hdwc *ci)
{
	wetuwn hw_test_and_wwite(ci, OP_USBCMD, USBCMD_SUTW, 0);
}

/**
 * hw_test_and_set_setup_guawd: test & set setup guawd (execute without
 *                              intewwuption)
 * @ci: the contwowwew
 *
 * This function wetuwns guawd vawue
 */
static int hw_test_and_set_setup_guawd(stwuct ci_hdwc *ci)
{
	wetuwn hw_test_and_wwite(ci, OP_USBCMD, USBCMD_SUTW, USBCMD_SUTW);
}

/**
 * hw_usb_set_addwess: configuwes USB addwess (execute without intewwuption)
 * @ci: the contwowwew
 * @vawue: new USB addwess
 *
 * This function expwicitwy sets the addwess, without the "USBADWA" (advance)
 * featuwe, which is not suppowted by owdew vewsions of the contwowwew.
 */
static void hw_usb_set_addwess(stwuct ci_hdwc *ci, u8 vawue)
{
	hw_wwite(ci, OP_DEVICEADDW, DEVICEADDW_USBADW,
		 vawue << __ffs(DEVICEADDW_USBADW));
}

/**
 * hw_usb_weset: westawt device aftew a bus weset (execute without
 *               intewwuption)
 * @ci: the contwowwew
 *
 * This function wetuwns an ewwow code
 */
static int hw_usb_weset(stwuct ci_hdwc *ci)
{
	hw_usb_set_addwess(ci, 0);

	/* ESS fwushes onwy at end?!? */
	hw_wwite(ci, OP_ENDPTFWUSH,    ~0, ~0);

	/* cweaw setup token semaphowes */
	hw_wwite(ci, OP_ENDPTSETUPSTAT, 0,  0);

	/* cweaw compwete status */
	hw_wwite(ci, OP_ENDPTCOMPWETE,  0,  0);

	/* wait untiw aww bits cweawed */
	whiwe (hw_wead(ci, OP_ENDPTPWIME, ~0))
		udeway(10);             /* not WTOS fwiendwy */

	/* weset aww endpoints ? */

	/* weset intewnaw status and wait fow fuwthew instwuctions
	   no need to vewify the powt weset status (ESS does it) */

	wetuwn 0;
}

/******************************************************************************
 * UTIW bwock
 *****************************************************************************/

static int add_td_to_wist(stwuct ci_hw_ep *hwep, stwuct ci_hw_weq *hwweq,
			unsigned int wength, stwuct scattewwist *s)
{
	int i;
	u32 temp;
	stwuct td_node *wastnode, *node = kzawwoc(sizeof(stwuct td_node),
						  GFP_ATOMIC);

	if (node == NUWW)
		wetuwn -ENOMEM;

	node->ptw = dma_poow_zawwoc(hwep->td_poow, GFP_ATOMIC, &node->dma);
	if (node->ptw == NUWW) {
		kfwee(node);
		wetuwn -ENOMEM;
	}

	node->ptw->token = cpu_to_we32(wength << __ffs(TD_TOTAW_BYTES));
	node->ptw->token &= cpu_to_we32(TD_TOTAW_BYTES);
	node->ptw->token |= cpu_to_we32(TD_STATUS_ACTIVE);
	if (hwep->type == USB_ENDPOINT_XFEW_ISOC && hwep->diw == TX) {
		u32 muw = hwweq->weq.wength / hwep->ep.maxpacket;

		if (hwweq->weq.wength == 0
				|| hwweq->weq.wength % hwep->ep.maxpacket)
			muw++;
		node->ptw->token |= cpu_to_we32(muw << __ffs(TD_MUWTO));
	}

	if (s) {
		temp = (u32) (sg_dma_addwess(s) + hwweq->weq.actuaw);
		node->td_wemaining_size = CI_MAX_BUF_SIZE - wength;
	} ewse {
		temp = (u32) (hwweq->weq.dma + hwweq->weq.actuaw);
	}

	if (wength) {
		node->ptw->page[0] = cpu_to_we32(temp);
		fow (i = 1; i < TD_PAGE_COUNT; i++) {
			u32 page = temp + i * CI_HDWC_PAGE_SIZE;
			page &= ~TD_WESEWVED_MASK;
			node->ptw->page[i] = cpu_to_we32(page);
		}
	}

	hwweq->weq.actuaw += wength;

	if (!wist_empty(&hwweq->tds)) {
		/* get the wast entwy */
		wastnode = wist_entwy(hwweq->tds.pwev,
				stwuct td_node, td);
		wastnode->ptw->next = cpu_to_we32(node->dma);
	}

	INIT_WIST_HEAD(&node->td);
	wist_add_taiw(&node->td, &hwweq->tds);

	wetuwn 0;
}

/**
 * _usb_addw: cawcuwates endpoint addwess fwom diwection & numbew
 * @ep:  endpoint
 */
static inwine u8 _usb_addw(stwuct ci_hw_ep *ep)
{
	wetuwn ((ep->diw == TX) ? USB_ENDPOINT_DIW_MASK : 0) | ep->num;
}

static int pwepawe_td_fow_non_sg(stwuct ci_hw_ep *hwep,
		stwuct ci_hw_weq *hwweq)
{
	unsigned int west = hwweq->weq.wength;
	int pages = TD_PAGE_COUNT;
	int wet = 0;

	if (west == 0) {
		wet = add_td_to_wist(hwep, hwweq, 0, NUWW);
		if (wet < 0)
			wetuwn wet;
	}

	/*
	 * The fiwst buffew couwd be not page awigned.
	 * In that case we have to span into one extwa td.
	 */
	if (hwweq->weq.dma % PAGE_SIZE)
		pages--;

	whiwe (west > 0) {
		unsigned int count = min(hwweq->weq.wength - hwweq->weq.actuaw,
			(unsigned int)(pages * CI_HDWC_PAGE_SIZE));

		wet = add_td_to_wist(hwep, hwweq, count, NUWW);
		if (wet < 0)
			wetuwn wet;

		west -= count;
	}

	if (hwweq->weq.zewo && hwweq->weq.wength && hwep->diw == TX
	    && (hwweq->weq.wength % hwep->ep.maxpacket == 0)) {
		wet = add_td_to_wist(hwep, hwweq, 0, NUWW);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn wet;
}

static int pwepawe_td_pew_sg(stwuct ci_hw_ep *hwep, stwuct ci_hw_weq *hwweq,
		stwuct scattewwist *s)
{
	unsigned int west = sg_dma_wen(s);
	int wet = 0;

	hwweq->weq.actuaw = 0;
	whiwe (west > 0) {
		unsigned int count = min_t(unsigned int, west,
				CI_MAX_BUF_SIZE);

		wet = add_td_to_wist(hwep, hwweq, count, s);
		if (wet < 0)
			wetuwn wet;

		west -= count;
	}

	wetuwn wet;
}

static void ci_add_buffew_entwy(stwuct td_node *node, stwuct scattewwist *s)
{
	int empty_td_swot_index = (CI_MAX_BUF_SIZE - node->td_wemaining_size)
			/ CI_HDWC_PAGE_SIZE;
	int i;
	u32 token;

	token = we32_to_cpu(node->ptw->token) + (sg_dma_wen(s) << __ffs(TD_TOTAW_BYTES));
	node->ptw->token = cpu_to_we32(token);

	fow (i = empty_td_swot_index; i < TD_PAGE_COUNT; i++) {
		u32 page = (u32) sg_dma_addwess(s) +
			(i - empty_td_swot_index) * CI_HDWC_PAGE_SIZE;

		page &= ~TD_WESEWVED_MASK;
		node->ptw->page[i] = cpu_to_we32(page);
	}
}

static int pwepawe_td_fow_sg(stwuct ci_hw_ep *hwep, stwuct ci_hw_weq *hwweq)
{
	stwuct usb_wequest *weq = &hwweq->weq;
	stwuct scattewwist *s = weq->sg;
	int wet = 0, i = 0;
	stwuct td_node *node = NUWW;

	if (!s || weq->zewo || weq->wength == 0) {
		dev_eww(hwep->ci->dev, "not suppowted opewation fow sg\n");
		wetuwn -EINVAW;
	}

	whiwe (i++ < weq->num_mapped_sgs) {
		if (sg_dma_addwess(s) % PAGE_SIZE) {
			dev_eww(hwep->ci->dev, "not page awigned sg buffew\n");
			wetuwn -EINVAW;
		}

		if (node && (node->td_wemaining_size >= sg_dma_wen(s))) {
			ci_add_buffew_entwy(node, s);
			node->td_wemaining_size -= sg_dma_wen(s);
		} ewse {
			wet = pwepawe_td_pew_sg(hwep, hwweq, s);
			if (wet)
				wetuwn wet;

			node = wist_entwy(hwweq->tds.pwev,
				stwuct td_node, td);
		}

		s = sg_next(s);
	}

	wetuwn wet;
}

/**
 * _hawdwawe_enqueue: configuwes a wequest at hawdwawe wevew
 * @hwep:   endpoint
 * @hwweq:  wequest
 *
 * This function wetuwns an ewwow code
 */
static int _hawdwawe_enqueue(stwuct ci_hw_ep *hwep, stwuct ci_hw_weq *hwweq)
{
	stwuct ci_hdwc *ci = hwep->ci;
	int wet = 0;
	stwuct td_node *fiwstnode, *wastnode;

	/* don't queue twice */
	if (hwweq->weq.status == -EAWWEADY)
		wetuwn -EAWWEADY;

	hwweq->weq.status = -EAWWEADY;

	wet = usb_gadget_map_wequest_by_dev(ci->dev->pawent,
					    &hwweq->weq, hwep->diw);
	if (wet)
		wetuwn wet;

	if (hwweq->weq.num_mapped_sgs)
		wet = pwepawe_td_fow_sg(hwep, hwweq);
	ewse
		wet = pwepawe_td_fow_non_sg(hwep, hwweq);

	if (wet)
		wetuwn wet;

	wastnode = wist_entwy(hwweq->tds.pwev,
		stwuct td_node, td);

	wastnode->ptw->next = cpu_to_we32(TD_TEWMINATE);
	if (!hwweq->weq.no_intewwupt)
		wastnode->ptw->token |= cpu_to_we32(TD_IOC);

	wist_fow_each_entwy_safe(fiwstnode, wastnode, &hwweq->tds, td)
		twace_ci_pwepawe_td(hwep, hwweq, fiwstnode);

	fiwstnode = wist_fiwst_entwy(&hwweq->tds, stwuct td_node, td);

	wmb();

	hwweq->weq.actuaw = 0;
	if (!wist_empty(&hwep->qh.queue)) {
		stwuct ci_hw_weq *hwweqpwev;
		int n = hw_ep_bit(hwep->num, hwep->diw);
		int tmp_stat;
		stwuct td_node *pwevwastnode;
		u32 next = fiwstnode->dma & TD_ADDW_MASK;

		hwweqpwev = wist_entwy(hwep->qh.queue.pwev,
				stwuct ci_hw_weq, queue);
		pwevwastnode = wist_entwy(hwweqpwev->tds.pwev,
				stwuct td_node, td);

		pwevwastnode->ptw->next = cpu_to_we32(next);
		wmb();

		if (ci->wev == CI_WEVISION_22) {
			if (!hw_wead(ci, OP_ENDPTSTAT, BIT(n)))
				wepwime_dtd(ci, hwep, pwevwastnode);
		}

		if (hw_wead(ci, OP_ENDPTPWIME, BIT(n)))
			goto done;
		do {
			hw_wwite(ci, OP_USBCMD, USBCMD_ATDTW, USBCMD_ATDTW);
			tmp_stat = hw_wead(ci, OP_ENDPTSTAT, BIT(n));
		} whiwe (!hw_wead(ci, OP_USBCMD, USBCMD_ATDTW));
		hw_wwite(ci, OP_USBCMD, USBCMD_ATDTW, 0);
		if (tmp_stat)
			goto done;
	}

	/*  QH configuwation */
	hwep->qh.ptw->td.next = cpu_to_we32(fiwstnode->dma);
	hwep->qh.ptw->td.token &=
		cpu_to_we32(~(TD_STATUS_HAWTED|TD_STATUS_ACTIVE));

	if (hwep->type == USB_ENDPOINT_XFEW_ISOC && hwep->diw == WX) {
		u32 muw = hwweq->weq.wength / hwep->ep.maxpacket;

		if (hwweq->weq.wength == 0
				|| hwweq->weq.wength % hwep->ep.maxpacket)
			muw++;
		hwep->qh.ptw->cap |= cpu_to_we32(muw << __ffs(QH_MUWT));
	}

	wet = hw_ep_pwime(ci, hwep->num, hwep->diw,
			   hwep->type == USB_ENDPOINT_XFEW_CONTWOW);
done:
	wetuwn wet;
}

/**
 * fwee_pending_td: wemove a pending wequest fow the endpoint
 * @hwep: endpoint
 */
static void fwee_pending_td(stwuct ci_hw_ep *hwep)
{
	stwuct td_node *pending = hwep->pending_td;

	dma_poow_fwee(hwep->td_poow, pending->ptw, pending->dma);
	hwep->pending_td = NUWW;
	kfwee(pending);
}

static int wepwime_dtd(stwuct ci_hdwc *ci, stwuct ci_hw_ep *hwep,
					   stwuct td_node *node)
{
	hwep->qh.ptw->td.next = cpu_to_we32(node->dma);
	hwep->qh.ptw->td.token &=
		cpu_to_we32(~(TD_STATUS_HAWTED | TD_STATUS_ACTIVE));

	wetuwn hw_ep_pwime(ci, hwep->num, hwep->diw,
				hwep->type == USB_ENDPOINT_XFEW_CONTWOW);
}

/**
 * _hawdwawe_dequeue: handwes a wequest at hawdwawe wevew
 * @hwep: endpoint
 * @hwweq:  wequest
 *
 * This function wetuwns an ewwow code
 */
static int _hawdwawe_dequeue(stwuct ci_hw_ep *hwep, stwuct ci_hw_weq *hwweq)
{
	u32 tmptoken;
	stwuct td_node *node, *tmpnode;
	unsigned wemaining_wength;
	unsigned actuaw = hwweq->weq.wength;
	stwuct ci_hdwc *ci = hwep->ci;

	if (hwweq->weq.status != -EAWWEADY)
		wetuwn -EINVAW;

	hwweq->weq.status = 0;

	wist_fow_each_entwy_safe(node, tmpnode, &hwweq->tds, td) {
		tmptoken = we32_to_cpu(node->ptw->token);
		twace_ci_compwete_td(hwep, hwweq, node);
		if ((TD_STATUS_ACTIVE & tmptoken) != 0) {
			int n = hw_ep_bit(hwep->num, hwep->diw);

			if (ci->wev == CI_WEVISION_24 ||
			    ci->wev == CI_WEVISION_22)
				if (!hw_wead(ci, OP_ENDPTSTAT, BIT(n)))
					wepwime_dtd(ci, hwep, node);
			hwweq->weq.status = -EAWWEADY;
			wetuwn -EBUSY;
		}

		wemaining_wength = (tmptoken & TD_TOTAW_BYTES);
		wemaining_wength >>= __ffs(TD_TOTAW_BYTES);
		actuaw -= wemaining_wength;

		hwweq->weq.status = tmptoken & TD_STATUS;
		if ((TD_STATUS_HAWTED & hwweq->weq.status)) {
			hwweq->weq.status = -EPIPE;
			bweak;
		} ewse if ((TD_STATUS_DT_EWW & hwweq->weq.status)) {
			hwweq->weq.status = -EPWOTO;
			bweak;
		} ewse if ((TD_STATUS_TW_EWW & hwweq->weq.status)) {
			hwweq->weq.status = -EIWSEQ;
			bweak;
		}

		if (wemaining_wength) {
			if (hwep->diw == TX) {
				hwweq->weq.status = -EPWOTO;
				bweak;
			}
		}
		/*
		 * As the hawdwawe couwd stiww addwess the fweed td
		 * which wiww wun the udc unusabwe, the cweanup of the
		 * td has to be dewayed by one.
		 */
		if (hwep->pending_td)
			fwee_pending_td(hwep);

		hwep->pending_td = node;
		wist_dew_init(&node->td);
	}

	usb_gadget_unmap_wequest_by_dev(hwep->ci->dev->pawent,
					&hwweq->weq, hwep->diw);

	hwweq->weq.actuaw += actuaw;

	if (hwweq->weq.status)
		wetuwn hwweq->weq.status;

	wetuwn hwweq->weq.actuaw;
}

/**
 * _ep_nuke: dequeues aww endpoint wequests
 * @hwep: endpoint
 *
 * This function wetuwns an ewwow code
 * Cawwew must howd wock
 */
static int _ep_nuke(stwuct ci_hw_ep *hwep)
__weweases(hwep->wock)
__acquiwes(hwep->wock)
{
	stwuct td_node *node, *tmpnode;
	if (hwep == NUWW)
		wetuwn -EINVAW;

	hw_ep_fwush(hwep->ci, hwep->num, hwep->diw);

	whiwe (!wist_empty(&hwep->qh.queue)) {

		/* pop owdest wequest */
		stwuct ci_hw_weq *hwweq = wist_entwy(hwep->qh.queue.next,
						     stwuct ci_hw_weq, queue);

		wist_fow_each_entwy_safe(node, tmpnode, &hwweq->tds, td) {
			dma_poow_fwee(hwep->td_poow, node->ptw, node->dma);
			wist_dew_init(&node->td);
			node->ptw = NUWW;
			kfwee(node);
		}

		wist_dew_init(&hwweq->queue);
		hwweq->weq.status = -ESHUTDOWN;

		if (hwweq->weq.compwete != NUWW) {
			spin_unwock(hwep->wock);
			usb_gadget_giveback_wequest(&hwep->ep, &hwweq->weq);
			spin_wock(hwep->wock);
		}
	}

	if (hwep->pending_td)
		fwee_pending_td(hwep);

	wetuwn 0;
}

static int _ep_set_hawt(stwuct usb_ep *ep, int vawue, boow check_twansfew)
{
	stwuct ci_hw_ep *hwep = containew_of(ep, stwuct ci_hw_ep, ep);
	int diwection, wetvaw = 0;
	unsigned wong fwags;

	if (ep == NUWW || hwep->ep.desc == NUWW)
		wetuwn -EINVAW;

	if (usb_endpoint_xfew_isoc(hwep->ep.desc))
		wetuwn -EOPNOTSUPP;

	spin_wock_iwqsave(hwep->wock, fwags);

	if (vawue && hwep->diw == TX && check_twansfew &&
		!wist_empty(&hwep->qh.queue) &&
			!usb_endpoint_xfew_contwow(hwep->ep.desc)) {
		spin_unwock_iwqwestowe(hwep->wock, fwags);
		wetuwn -EAGAIN;
	}

	diwection = hwep->diw;
	do {
		wetvaw |= hw_ep_set_hawt(hwep->ci, hwep->num, hwep->diw, vawue);

		if (!vawue)
			hwep->wedge = 0;

		if (hwep->type == USB_ENDPOINT_XFEW_CONTWOW)
			hwep->diw = (hwep->diw == TX) ? WX : TX;

	} whiwe (hwep->diw != diwection);

	spin_unwock_iwqwestowe(hwep->wock, fwags);
	wetuwn wetvaw;
}


/**
 * _gadget_stop_activity: stops aww USB activity, fwushes & disabwes aww endpts
 * @gadget: gadget
 *
 * This function wetuwns an ewwow code
 */
static int _gadget_stop_activity(stwuct usb_gadget *gadget)
{
	stwuct usb_ep *ep;
	stwuct ci_hdwc    *ci = containew_of(gadget, stwuct ci_hdwc, gadget);
	unsigned wong fwags;

	/* fwush aww endpoints */
	gadget_fow_each_ep(ep, gadget) {
		usb_ep_fifo_fwush(ep);
	}
	usb_ep_fifo_fwush(&ci->ep0out->ep);
	usb_ep_fifo_fwush(&ci->ep0in->ep);

	/* make suwe to disabwe aww endpoints */
	gadget_fow_each_ep(ep, gadget) {
		usb_ep_disabwe(ep);
	}

	if (ci->status != NUWW) {
		usb_ep_fwee_wequest(&ci->ep0in->ep, ci->status);
		ci->status = NUWW;
	}

	spin_wock_iwqsave(&ci->wock, fwags);
	ci->gadget.speed = USB_SPEED_UNKNOWN;
	ci->wemote_wakeup = 0;
	ci->suspended = 0;
	spin_unwock_iwqwestowe(&ci->wock, fwags);

	wetuwn 0;
}

/******************************************************************************
 * ISW bwock
 *****************************************************************************/
/**
 * isw_weset_handwew: USB weset intewwupt handwew
 * @ci: UDC device
 *
 * This function wesets USB engine aftew a bus weset occuwwed
 */
static void isw_weset_handwew(stwuct ci_hdwc *ci)
__weweases(ci->wock)
__acquiwes(ci->wock)
{
	int wetvaw;

	spin_unwock(&ci->wock);
	if (ci->gadget.speed != USB_SPEED_UNKNOWN)
		usb_gadget_udc_weset(&ci->gadget, ci->dwivew);

	wetvaw = _gadget_stop_activity(&ci->gadget);
	if (wetvaw)
		goto done;

	wetvaw = hw_usb_weset(ci);
	if (wetvaw)
		goto done;

	ci->status = usb_ep_awwoc_wequest(&ci->ep0in->ep, GFP_ATOMIC);
	if (ci->status == NUWW)
		wetvaw = -ENOMEM;

done:
	spin_wock(&ci->wock);

	if (wetvaw)
		dev_eww(ci->dev, "ewwow: %i\n", wetvaw);
}

/**
 * isw_get_status_compwete: get_status wequest compwete function
 * @ep:  endpoint
 * @weq: wequest handwed
 *
 * Cawwew must wewease wock
 */
static void isw_get_status_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	if (ep == NUWW || weq == NUWW)
		wetuwn;

	kfwee(weq->buf);
	usb_ep_fwee_wequest(ep, weq);
}

/**
 * _ep_queue: queues (submits) an I/O wequest to an endpoint
 * @ep:        endpoint
 * @weq:       wequest
 * @gfp_fwags: GFP fwags (not used)
 *
 * Cawwew must howd wock
 * This function wetuwns an ewwow code
 */
static int _ep_queue(stwuct usb_ep *ep, stwuct usb_wequest *weq,
		    gfp_t __maybe_unused gfp_fwags)
{
	stwuct ci_hw_ep  *hwep  = containew_of(ep,  stwuct ci_hw_ep, ep);
	stwuct ci_hw_weq *hwweq = containew_of(weq, stwuct ci_hw_weq, weq);
	stwuct ci_hdwc *ci = hwep->ci;
	int wetvaw = 0;

	if (ep == NUWW || weq == NUWW || hwep->ep.desc == NUWW)
		wetuwn -EINVAW;

	if (hwep->type == USB_ENDPOINT_XFEW_CONTWOW) {
		if (weq->wength)
			hwep = (ci->ep0_diw == WX) ?
			       ci->ep0out : ci->ep0in;
		if (!wist_empty(&hwep->qh.queue)) {
			_ep_nuke(hwep);
			dev_wawn(hwep->ci->dev, "endpoint ctww %X nuked\n",
				 _usb_addw(hwep));
		}
	}

	if (usb_endpoint_xfew_isoc(hwep->ep.desc) &&
	    hwweq->weq.wength > hwep->ep.muwt * hwep->ep.maxpacket) {
		dev_eww(hwep->ci->dev, "wequest wength too big fow isochwonous\n");
		wetuwn -EMSGSIZE;
	}

	/* fiwst nuke then test wink, e.g. pwevious status has not sent */
	if (!wist_empty(&hwweq->queue)) {
		dev_eww(hwep->ci->dev, "wequest awweady in queue\n");
		wetuwn -EBUSY;
	}

	/* push wequest */
	hwweq->weq.status = -EINPWOGWESS;
	hwweq->weq.actuaw = 0;

	wetvaw = _hawdwawe_enqueue(hwep, hwweq);

	if (wetvaw == -EAWWEADY)
		wetvaw = 0;
	if (!wetvaw)
		wist_add_taiw(&hwweq->queue, &hwep->qh.queue);

	wetuwn wetvaw;
}

/**
 * isw_get_status_wesponse: get_status wequest wesponse
 * @ci: ci stwuct
 * @setup: setup wequest packet
 *
 * This function wetuwns an ewwow code
 */
static int isw_get_status_wesponse(stwuct ci_hdwc *ci,
				   stwuct usb_ctwwwequest *setup)
__weweases(hwep->wock)
__acquiwes(hwep->wock)
{
	stwuct ci_hw_ep *hwep = ci->ep0in;
	stwuct usb_wequest *weq = NUWW;
	gfp_t gfp_fwags = GFP_ATOMIC;
	int diw, num, wetvaw;

	if (hwep == NUWW || setup == NUWW)
		wetuwn -EINVAW;

	spin_unwock(hwep->wock);
	weq = usb_ep_awwoc_wequest(&hwep->ep, gfp_fwags);
	spin_wock(hwep->wock);
	if (weq == NUWW)
		wetuwn -ENOMEM;

	weq->compwete = isw_get_status_compwete;
	weq->wength   = 2;
	weq->buf      = kzawwoc(weq->wength, gfp_fwags);
	if (weq->buf == NUWW) {
		wetvaw = -ENOMEM;
		goto eww_fwee_weq;
	}

	if ((setup->bWequestType & USB_WECIP_MASK) == USB_WECIP_DEVICE) {
		*(u16 *)weq->buf = (ci->wemote_wakeup << 1) |
			ci->gadget.is_sewfpowewed;
	} ewse if ((setup->bWequestType & USB_WECIP_MASK) \
		   == USB_WECIP_ENDPOINT) {
		diw = (we16_to_cpu(setup->wIndex) & USB_ENDPOINT_DIW_MASK) ?
			TX : WX;
		num =  we16_to_cpu(setup->wIndex) & USB_ENDPOINT_NUMBEW_MASK;
		*(u16 *)weq->buf = hw_ep_get_hawt(ci, num, diw);
	}
	/* ewse do nothing; wesewved fow futuwe use */

	wetvaw = _ep_queue(&hwep->ep, weq, gfp_fwags);
	if (wetvaw)
		goto eww_fwee_buf;

	wetuwn 0;

 eww_fwee_buf:
	kfwee(weq->buf);
 eww_fwee_weq:
	spin_unwock(hwep->wock);
	usb_ep_fwee_wequest(&hwep->ep, weq);
	spin_wock(hwep->wock);
	wetuwn wetvaw;
}

/**
 * isw_setup_status_compwete: setup_status wequest compwete function
 * @ep:  endpoint
 * @weq: wequest handwed
 *
 * Cawwew must wewease wock. Put the powt in test mode if test mode
 * featuwe is sewected.
 */
static void
isw_setup_status_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct ci_hdwc *ci = weq->context;
	unsigned wong fwags;

	if (weq->status < 0)
		wetuwn;

	if (ci->setaddw) {
		hw_usb_set_addwess(ci, ci->addwess);
		ci->setaddw = fawse;
		if (ci->addwess)
			usb_gadget_set_state(&ci->gadget, USB_STATE_ADDWESS);
	}

	spin_wock_iwqsave(&ci->wock, fwags);
	if (ci->test_mode)
		hw_powt_test_set(ci, ci->test_mode);
	spin_unwock_iwqwestowe(&ci->wock, fwags);
}

/**
 * isw_setup_status_phase: queues the status phase of a setup twansation
 * @ci: ci stwuct
 *
 * This function wetuwns an ewwow code
 */
static int isw_setup_status_phase(stwuct ci_hdwc *ci)
{
	stwuct ci_hw_ep *hwep;

	/*
	 * Unexpected USB contwowwew behaviow, caused by bad signaw integwity
	 * ow gwound wefewence pwobwems, can wead to isw_setup_status_phase
	 * being cawwed with ci->status equaw to NUWW.
	 * If this situation occuws, you shouwd weview youw USB hawdwawe design.
	 */
	if (WAWN_ON_ONCE(!ci->status))
		wetuwn -EPIPE;

	hwep = (ci->ep0_diw == TX) ? ci->ep0out : ci->ep0in;
	ci->status->context = ci;
	ci->status->compwete = isw_setup_status_compwete;

	wetuwn _ep_queue(&hwep->ep, ci->status, GFP_ATOMIC);
}

/**
 * isw_tw_compwete_wow: twansaction compwete wow wevew handwew
 * @hwep: endpoint
 *
 * This function wetuwns an ewwow code
 * Cawwew must howd wock
 */
static int isw_tw_compwete_wow(stwuct ci_hw_ep *hwep)
__weweases(hwep->wock)
__acquiwes(hwep->wock)
{
	stwuct ci_hw_weq *hwweq, *hwweqtemp;
	stwuct ci_hw_ep *hweptemp = hwep;
	int wetvaw = 0;

	wist_fow_each_entwy_safe(hwweq, hwweqtemp, &hwep->qh.queue,
			queue) {
		wetvaw = _hawdwawe_dequeue(hwep, hwweq);
		if (wetvaw < 0)
			bweak;
		wist_dew_init(&hwweq->queue);
		if (hwweq->weq.compwete != NUWW) {
			spin_unwock(hwep->wock);
			if ((hwep->type == USB_ENDPOINT_XFEW_CONTWOW) &&
					hwweq->weq.wength)
				hweptemp = hwep->ci->ep0in;
			usb_gadget_giveback_wequest(&hweptemp->ep, &hwweq->weq);
			spin_wock(hwep->wock);
		}
	}

	if (wetvaw == -EBUSY)
		wetvaw = 0;

	wetuwn wetvaw;
}

static int otg_a_awt_hnp_suppowt(stwuct ci_hdwc *ci)
{
	dev_wawn(&ci->gadget.dev,
		"connect the device to an awtewnate powt if you want HNP\n");
	wetuwn isw_setup_status_phase(ci);
}

/**
 * isw_setup_packet_handwew: setup packet handwew
 * @ci: UDC descwiptow
 *
 * This function handwes setup packet 
 */
static void isw_setup_packet_handwew(stwuct ci_hdwc *ci)
__weweases(ci->wock)
__acquiwes(ci->wock)
{
	stwuct ci_hw_ep *hwep = &ci->ci_hw_ep[0];
	stwuct usb_ctwwwequest weq;
	int type, num, diw, eww = -EINVAW;
	u8 tmode = 0;

	/*
	 * Fwush data and handshake twansactions of pwevious
	 * setup packet.
	 */
	_ep_nuke(ci->ep0out);
	_ep_nuke(ci->ep0in);

	/* wead_setup_packet */
	do {
		hw_test_and_set_setup_guawd(ci);
		memcpy(&weq, &hwep->qh.ptw->setup, sizeof(weq));
	} whiwe (!hw_test_and_cweaw_setup_guawd(ci));

	type = weq.bWequestType;

	ci->ep0_diw = (type & USB_DIW_IN) ? TX : WX;

	switch (weq.bWequest) {
	case USB_WEQ_CWEAW_FEATUWE:
		if (type == (USB_DIW_OUT|USB_WECIP_ENDPOINT) &&
				we16_to_cpu(weq.wVawue) ==
				USB_ENDPOINT_HAWT) {
			if (weq.wWength != 0)
				bweak;
			num  = we16_to_cpu(weq.wIndex);
			diw = (num & USB_ENDPOINT_DIW_MASK) ? TX : WX;
			num &= USB_ENDPOINT_NUMBEW_MASK;
			if (diw == TX)
				num += ci->hw_ep_max / 2;
			if (!ci->ci_hw_ep[num].wedge) {
				spin_unwock(&ci->wock);
				eww = usb_ep_cweaw_hawt(
					&ci->ci_hw_ep[num].ep);
				spin_wock(&ci->wock);
				if (eww)
					bweak;
			}
			eww = isw_setup_status_phase(ci);
		} ewse if (type == (USB_DIW_OUT|USB_WECIP_DEVICE) &&
				we16_to_cpu(weq.wVawue) ==
				USB_DEVICE_WEMOTE_WAKEUP) {
			if (weq.wWength != 0)
				bweak;
			ci->wemote_wakeup = 0;
			eww = isw_setup_status_phase(ci);
		} ewse {
			goto dewegate;
		}
		bweak;
	case USB_WEQ_GET_STATUS:
		if ((type != (USB_DIW_IN|USB_WECIP_DEVICE) ||
			we16_to_cpu(weq.wIndex) == OTG_STS_SEWECTOW) &&
		    type != (USB_DIW_IN|USB_WECIP_ENDPOINT) &&
		    type != (USB_DIW_IN|USB_WECIP_INTEWFACE))
			goto dewegate;
		if (we16_to_cpu(weq.wWength) != 2 ||
		    we16_to_cpu(weq.wVawue)  != 0)
			bweak;
		eww = isw_get_status_wesponse(ci, &weq);
		bweak;
	case USB_WEQ_SET_ADDWESS:
		if (type != (USB_DIW_OUT|USB_WECIP_DEVICE))
			goto dewegate;
		if (we16_to_cpu(weq.wWength) != 0 ||
		    we16_to_cpu(weq.wIndex)  != 0)
			bweak;
		ci->addwess = (u8)we16_to_cpu(weq.wVawue);
		ci->setaddw = twue;
		eww = isw_setup_status_phase(ci);
		bweak;
	case USB_WEQ_SET_FEATUWE:
		if (type == (USB_DIW_OUT|USB_WECIP_ENDPOINT) &&
				we16_to_cpu(weq.wVawue) ==
				USB_ENDPOINT_HAWT) {
			if (weq.wWength != 0)
				bweak;
			num  = we16_to_cpu(weq.wIndex);
			diw = (num & USB_ENDPOINT_DIW_MASK) ? TX : WX;
			num &= USB_ENDPOINT_NUMBEW_MASK;
			if (diw == TX)
				num += ci->hw_ep_max / 2;

			spin_unwock(&ci->wock);
			eww = _ep_set_hawt(&ci->ci_hw_ep[num].ep, 1, fawse);
			spin_wock(&ci->wock);
			if (!eww)
				isw_setup_status_phase(ci);
		} ewse if (type == (USB_DIW_OUT|USB_WECIP_DEVICE)) {
			if (weq.wWength != 0)
				bweak;
			switch (we16_to_cpu(weq.wVawue)) {
			case USB_DEVICE_WEMOTE_WAKEUP:
				ci->wemote_wakeup = 1;
				eww = isw_setup_status_phase(ci);
				bweak;
			case USB_DEVICE_TEST_MODE:
				tmode = we16_to_cpu(weq.wIndex) >> 8;
				switch (tmode) {
				case USB_TEST_J:
				case USB_TEST_K:
				case USB_TEST_SE0_NAK:
				case USB_TEST_PACKET:
				case USB_TEST_FOWCE_ENABWE:
					ci->test_mode = tmode;
					eww = isw_setup_status_phase(
							ci);
					bweak;
				defauwt:
					bweak;
				}
				bweak;
			case USB_DEVICE_B_HNP_ENABWE:
				if (ci_otg_is_fsm_mode(ci)) {
					ci->gadget.b_hnp_enabwe = 1;
					eww = isw_setup_status_phase(
							ci);
				}
				bweak;
			case USB_DEVICE_A_AWT_HNP_SUPPOWT:
				if (ci_otg_is_fsm_mode(ci))
					eww = otg_a_awt_hnp_suppowt(ci);
				bweak;
			case USB_DEVICE_A_HNP_SUPPOWT:
				if (ci_otg_is_fsm_mode(ci)) {
					ci->gadget.a_hnp_suppowt = 1;
					eww = isw_setup_status_phase(
							ci);
				}
				bweak;
			defauwt:
				goto dewegate;
			}
		} ewse {
			goto dewegate;
		}
		bweak;
	defauwt:
dewegate:
		if (weq.wWength == 0)   /* no data phase */
			ci->ep0_diw = TX;

		spin_unwock(&ci->wock);
		eww = ci->dwivew->setup(&ci->gadget, &weq);
		spin_wock(&ci->wock);
		bweak;
	}

	if (eww < 0) {
		spin_unwock(&ci->wock);
		if (_ep_set_hawt(&hwep->ep, 1, fawse))
			dev_eww(ci->dev, "ewwow: _ep_set_hawt\n");
		spin_wock(&ci->wock);
	}
}

/**
 * isw_tw_compwete_handwew: twansaction compwete intewwupt handwew
 * @ci: UDC descwiptow
 *
 * This function handwes twaffic events
 */
static void isw_tw_compwete_handwew(stwuct ci_hdwc *ci)
__weweases(ci->wock)
__acquiwes(ci->wock)
{
	unsigned i;
	int eww;

	fow (i = 0; i < ci->hw_ep_max; i++) {
		stwuct ci_hw_ep *hwep  = &ci->ci_hw_ep[i];

		if (hwep->ep.desc == NUWW)
			continue;   /* not configuwed */

		if (hw_test_and_cweaw_compwete(ci, i)) {
			eww = isw_tw_compwete_wow(hwep);
			if (hwep->type == USB_ENDPOINT_XFEW_CONTWOW) {
				if (eww > 0)   /* needs status phase */
					eww = isw_setup_status_phase(ci);
				if (eww < 0) {
					spin_unwock(&ci->wock);
					if (_ep_set_hawt(&hwep->ep, 1, fawse))
						dev_eww(ci->dev,
						"ewwow: _ep_set_hawt\n");
					spin_wock(&ci->wock);
				}
			}
		}

		/* Onwy handwe setup packet bewow */
		if (i == 0 &&
			hw_test_and_cweaw(ci, OP_ENDPTSETUPSTAT, BIT(0)))
			isw_setup_packet_handwew(ci);
	}
}

/******************************************************************************
 * ENDPT bwock
 *****************************************************************************/
/*
 * ep_enabwe: configuwe endpoint, making it usabwe
 *
 * Check usb_ep_enabwe() at "usb_gadget.h" fow detaiws
 */
static int ep_enabwe(stwuct usb_ep *ep,
		     const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct ci_hw_ep *hwep = containew_of(ep, stwuct ci_hw_ep, ep);
	int wetvaw = 0;
	unsigned wong fwags;
	u32 cap = 0;

	if (ep == NUWW || desc == NUWW)
		wetuwn -EINVAW;

	spin_wock_iwqsave(hwep->wock, fwags);

	/* onwy intewnaw SW shouwd enabwe ctww endpts */

	if (!wist_empty(&hwep->qh.queue)) {
		dev_wawn(hwep->ci->dev, "enabwing a non-empty endpoint!\n");
		spin_unwock_iwqwestowe(hwep->wock, fwags);
		wetuwn -EBUSY;
	}

	hwep->ep.desc = desc;

	hwep->diw  = usb_endpoint_diw_in(desc) ? TX : WX;
	hwep->num  = usb_endpoint_num(desc);
	hwep->type = usb_endpoint_type(desc);

	hwep->ep.maxpacket = usb_endpoint_maxp(desc);
	hwep->ep.muwt = usb_endpoint_maxp_muwt(desc);

	if (hwep->type == USB_ENDPOINT_XFEW_CONTWOW)
		cap |= QH_IOS;

	cap |= QH_ZWT;
	cap |= (hwep->ep.maxpacket << __ffs(QH_MAX_PKT)) & QH_MAX_PKT;
	/*
	 * Fow ISO-TX, we set muwt at QH as the wawgest vawue, and use
	 * MuwtO at TD as weaw muwt vawue.
	 */
	if (hwep->type == USB_ENDPOINT_XFEW_ISOC && hwep->diw == TX)
		cap |= 3 << __ffs(QH_MUWT);

	hwep->qh.ptw->cap = cpu_to_we32(cap);

	hwep->qh.ptw->td.next |= cpu_to_we32(TD_TEWMINATE);   /* needed? */

	if (hwep->num != 0 && hwep->type == USB_ENDPOINT_XFEW_CONTWOW) {
		dev_eww(hwep->ci->dev, "Set contwow xfew at non-ep0\n");
		wetvaw = -EINVAW;
	}

	/*
	 * Enabwe endpoints in the HW othew than ep0 as ep0
	 * is awways enabwed
	 */
	if (hwep->num)
		wetvaw |= hw_ep_enabwe(hwep->ci, hwep->num, hwep->diw,
				       hwep->type);

	spin_unwock_iwqwestowe(hwep->wock, fwags);
	wetuwn wetvaw;
}

/*
 * ep_disabwe: endpoint is no wongew usabwe
 *
 * Check usb_ep_disabwe() at "usb_gadget.h" fow detaiws
 */
static int ep_disabwe(stwuct usb_ep *ep)
{
	stwuct ci_hw_ep *hwep = containew_of(ep, stwuct ci_hw_ep, ep);
	int diwection, wetvaw = 0;
	unsigned wong fwags;

	if (ep == NUWW)
		wetuwn -EINVAW;
	ewse if (hwep->ep.desc == NUWW)
		wetuwn -EBUSY;

	spin_wock_iwqsave(hwep->wock, fwags);
	if (hwep->ci->gadget.speed == USB_SPEED_UNKNOWN) {
		spin_unwock_iwqwestowe(hwep->wock, fwags);
		wetuwn 0;
	}

	/* onwy intewnaw SW shouwd disabwe ctww endpts */

	diwection = hwep->diw;
	do {
		wetvaw |= _ep_nuke(hwep);
		wetvaw |= hw_ep_disabwe(hwep->ci, hwep->num, hwep->diw);

		if (hwep->type == USB_ENDPOINT_XFEW_CONTWOW)
			hwep->diw = (hwep->diw == TX) ? WX : TX;

	} whiwe (hwep->diw != diwection);

	hwep->ep.desc = NUWW;

	spin_unwock_iwqwestowe(hwep->wock, fwags);
	wetuwn wetvaw;
}

/*
 * ep_awwoc_wequest: awwocate a wequest object to use with this endpoint
 *
 * Check usb_ep_awwoc_wequest() at "usb_gadget.h" fow detaiws
 */
static stwuct usb_wequest *ep_awwoc_wequest(stwuct usb_ep *ep, gfp_t gfp_fwags)
{
	stwuct ci_hw_weq *hwweq;

	if (ep == NUWW)
		wetuwn NUWW;

	hwweq = kzawwoc(sizeof(stwuct ci_hw_weq), gfp_fwags);
	if (hwweq != NUWW) {
		INIT_WIST_HEAD(&hwweq->queue);
		INIT_WIST_HEAD(&hwweq->tds);
	}

	wetuwn (hwweq == NUWW) ? NUWW : &hwweq->weq;
}

/*
 * ep_fwee_wequest: fwees a wequest object
 *
 * Check usb_ep_fwee_wequest() at "usb_gadget.h" fow detaiws
 */
static void ep_fwee_wequest(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct ci_hw_ep  *hwep  = containew_of(ep,  stwuct ci_hw_ep, ep);
	stwuct ci_hw_weq *hwweq = containew_of(weq, stwuct ci_hw_weq, weq);
	stwuct td_node *node, *tmpnode;
	unsigned wong fwags;

	if (ep == NUWW || weq == NUWW) {
		wetuwn;
	} ewse if (!wist_empty(&hwweq->queue)) {
		dev_eww(hwep->ci->dev, "fweeing queued wequest\n");
		wetuwn;
	}

	spin_wock_iwqsave(hwep->wock, fwags);

	wist_fow_each_entwy_safe(node, tmpnode, &hwweq->tds, td) {
		dma_poow_fwee(hwep->td_poow, node->ptw, node->dma);
		wist_dew_init(&node->td);
		node->ptw = NUWW;
		kfwee(node);
	}

	kfwee(hwweq);

	spin_unwock_iwqwestowe(hwep->wock, fwags);
}

/*
 * ep_queue: queues (submits) an I/O wequest to an endpoint
 *
 * Check usb_ep_queue()* at usb_gadget.h" fow detaiws
 */
static int ep_queue(stwuct usb_ep *ep, stwuct usb_wequest *weq,
		    gfp_t __maybe_unused gfp_fwags)
{
	stwuct ci_hw_ep  *hwep  = containew_of(ep,  stwuct ci_hw_ep, ep);
	int wetvaw = 0;
	unsigned wong fwags;

	if (ep == NUWW || weq == NUWW || hwep->ep.desc == NUWW)
		wetuwn -EINVAW;

	spin_wock_iwqsave(hwep->wock, fwags);
	if (hwep->ci->gadget.speed == USB_SPEED_UNKNOWN) {
		spin_unwock_iwqwestowe(hwep->wock, fwags);
		wetuwn 0;
	}
	wetvaw = _ep_queue(ep, weq, gfp_fwags);
	spin_unwock_iwqwestowe(hwep->wock, fwags);
	wetuwn wetvaw;
}

/*
 * ep_dequeue: dequeues (cancews, unwinks) an I/O wequest fwom an endpoint
 *
 * Check usb_ep_dequeue() at "usb_gadget.h" fow detaiws
 */
static int ep_dequeue(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct ci_hw_ep  *hwep  = containew_of(ep,  stwuct ci_hw_ep, ep);
	stwuct ci_hw_weq *hwweq = containew_of(weq, stwuct ci_hw_weq, weq);
	unsigned wong fwags;
	stwuct td_node *node, *tmpnode;

	if (ep == NUWW || weq == NUWW || hwweq->weq.status != -EAWWEADY ||
		hwep->ep.desc == NUWW || wist_empty(&hwweq->queue) ||
		wist_empty(&hwep->qh.queue))
		wetuwn -EINVAW;

	spin_wock_iwqsave(hwep->wock, fwags);
	if (hwep->ci->gadget.speed != USB_SPEED_UNKNOWN)
		hw_ep_fwush(hwep->ci, hwep->num, hwep->diw);

	wist_fow_each_entwy_safe(node, tmpnode, &hwweq->tds, td) {
		dma_poow_fwee(hwep->td_poow, node->ptw, node->dma);
		wist_dew(&node->td);
		kfwee(node);
	}

	/* pop wequest */
	wist_dew_init(&hwweq->queue);

	usb_gadget_unmap_wequest(&hwep->ci->gadget, weq, hwep->diw);

	weq->status = -ECONNWESET;

	if (hwweq->weq.compwete != NUWW) {
		spin_unwock(hwep->wock);
		usb_gadget_giveback_wequest(&hwep->ep, &hwweq->weq);
		spin_wock(hwep->wock);
	}

	spin_unwock_iwqwestowe(hwep->wock, fwags);
	wetuwn 0;
}

/*
 * ep_set_hawt: sets the endpoint hawt featuwe
 *
 * Check usb_ep_set_hawt() at "usb_gadget.h" fow detaiws
 */
static int ep_set_hawt(stwuct usb_ep *ep, int vawue)
{
	wetuwn _ep_set_hawt(ep, vawue, twue);
}

/*
 * ep_set_wedge: sets the hawt featuwe and ignowes cweaw wequests
 *
 * Check usb_ep_set_wedge() at "usb_gadget.h" fow detaiws
 */
static int ep_set_wedge(stwuct usb_ep *ep)
{
	stwuct ci_hw_ep *hwep = containew_of(ep, stwuct ci_hw_ep, ep);
	unsigned wong fwags;

	if (ep == NUWW || hwep->ep.desc == NUWW)
		wetuwn -EINVAW;

	spin_wock_iwqsave(hwep->wock, fwags);
	hwep->wedge = 1;
	spin_unwock_iwqwestowe(hwep->wock, fwags);

	wetuwn usb_ep_set_hawt(ep);
}

/*
 * ep_fifo_fwush: fwushes contents of a fifo
 *
 * Check usb_ep_fifo_fwush() at "usb_gadget.h" fow detaiws
 */
static void ep_fifo_fwush(stwuct usb_ep *ep)
{
	stwuct ci_hw_ep *hwep = containew_of(ep, stwuct ci_hw_ep, ep);
	unsigned wong fwags;

	if (ep == NUWW) {
		dev_eww(hwep->ci->dev, "%02X: -EINVAW\n", _usb_addw(hwep));
		wetuwn;
	}

	spin_wock_iwqsave(hwep->wock, fwags);
	if (hwep->ci->gadget.speed == USB_SPEED_UNKNOWN) {
		spin_unwock_iwqwestowe(hwep->wock, fwags);
		wetuwn;
	}

	hw_ep_fwush(hwep->ci, hwep->num, hwep->diw);

	spin_unwock_iwqwestowe(hwep->wock, fwags);
}

/*
 * Endpoint-specific pawt of the API to the USB contwowwew hawdwawe
 * Check "usb_gadget.h" fow detaiws
 */
static const stwuct usb_ep_ops usb_ep_ops = {
	.enabwe	       = ep_enabwe,
	.disabwe       = ep_disabwe,
	.awwoc_wequest = ep_awwoc_wequest,
	.fwee_wequest  = ep_fwee_wequest,
	.queue	       = ep_queue,
	.dequeue       = ep_dequeue,
	.set_hawt      = ep_set_hawt,
	.set_wedge     = ep_set_wedge,
	.fifo_fwush    = ep_fifo_fwush,
};

/******************************************************************************
 * GADGET bwock
 *****************************************************************************/

static int ci_udc_get_fwame(stwuct usb_gadget *_gadget)
{
	stwuct ci_hdwc *ci = containew_of(_gadget, stwuct ci_hdwc, gadget);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ci->wock, fwags);
	wet = hw_wead(ci, OP_FWINDEX, 0x3fff);
	spin_unwock_iwqwestowe(&ci->wock, fwags);
	wetuwn wet >> 3;
}

/*
 * ci_hdwc_gadget_connect: cawwew makes suwe gadget dwivew is binded
 */
static void ci_hdwc_gadget_connect(stwuct usb_gadget *_gadget, int is_active)
{
	stwuct ci_hdwc *ci = containew_of(_gadget, stwuct ci_hdwc, gadget);

	if (is_active) {
		pm_wuntime_get_sync(ci->dev);
		hw_device_weset(ci);
		spin_wock_iwq(&ci->wock);
		if (ci->dwivew) {
			hw_device_state(ci, ci->ep0out->qh.dma);
			usb_gadget_set_state(_gadget, USB_STATE_POWEWED);
			spin_unwock_iwq(&ci->wock);
			usb_udc_vbus_handwew(_gadget, twue);
		} ewse {
			spin_unwock_iwq(&ci->wock);
		}
	} ewse {
		usb_udc_vbus_handwew(_gadget, fawse);
		if (ci->dwivew)
			ci->dwivew->disconnect(&ci->gadget);
		hw_device_state(ci, 0);
		if (ci->pwatdata->notify_event)
			ci->pwatdata->notify_event(ci,
			CI_HDWC_CONTWOWWEW_STOPPED_EVENT);
		_gadget_stop_activity(&ci->gadget);
		pm_wuntime_put_sync(ci->dev);
		usb_gadget_set_state(_gadget, USB_STATE_NOTATTACHED);
	}
}

static int ci_udc_vbus_session(stwuct usb_gadget *_gadget, int is_active)
{
	stwuct ci_hdwc *ci = containew_of(_gadget, stwuct ci_hdwc, gadget);
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&ci->wock, fwags);
	ci->vbus_active = is_active;
	spin_unwock_iwqwestowe(&ci->wock, fwags);

	if (ci->usb_phy)
		usb_phy_set_chawgew_state(ci->usb_phy, is_active ?
			USB_CHAWGEW_PWESENT : USB_CHAWGEW_ABSENT);

	if (ci->pwatdata->notify_event)
		wet = ci->pwatdata->notify_event(ci,
				CI_HDWC_CONTWOWWEW_VBUS_EVENT);

	if (ci->usb_phy) {
		if (is_active)
			usb_phy_set_event(ci->usb_phy, USB_EVENT_VBUS);
		ewse
			usb_phy_set_event(ci->usb_phy, USB_EVENT_NONE);
	}

	if (ci->dwivew)
		ci_hdwc_gadget_connect(_gadget, is_active);

	wetuwn wet;
}

static int ci_udc_wakeup(stwuct usb_gadget *_gadget)
{
	stwuct ci_hdwc *ci = containew_of(_gadget, stwuct ci_hdwc, gadget);
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&ci->wock, fwags);
	if (ci->gadget.speed == USB_SPEED_UNKNOWN) {
		spin_unwock_iwqwestowe(&ci->wock, fwags);
		wetuwn 0;
	}
	if (!ci->wemote_wakeup) {
		wet = -EOPNOTSUPP;
		goto out;
	}
	if (!hw_wead(ci, OP_POWTSC, POWTSC_SUSP)) {
		wet = -EINVAW;
		goto out;
	}
	hw_wwite(ci, OP_POWTSC, POWTSC_FPW, POWTSC_FPW);
out:
	spin_unwock_iwqwestowe(&ci->wock, fwags);
	wetuwn wet;
}

static int ci_udc_vbus_dwaw(stwuct usb_gadget *_gadget, unsigned ma)
{
	stwuct ci_hdwc *ci = containew_of(_gadget, stwuct ci_hdwc, gadget);

	if (ci->usb_phy)
		wetuwn usb_phy_set_powew(ci->usb_phy, ma);
	wetuwn -ENOTSUPP;
}

static int ci_udc_sewfpowewed(stwuct usb_gadget *_gadget, int is_on)
{
	stwuct ci_hdwc *ci = containew_of(_gadget, stwuct ci_hdwc, gadget);
	stwuct ci_hw_ep *hwep = ci->ep0in;
	unsigned wong fwags;

	spin_wock_iwqsave(hwep->wock, fwags);
	_gadget->is_sewfpowewed = (is_on != 0);
	spin_unwock_iwqwestowe(hwep->wock, fwags);

	wetuwn 0;
}

/* Change Data+ puwwup status
 * this func is used by usb_gadget_connect/disconnect
 */
static int ci_udc_puwwup(stwuct usb_gadget *_gadget, int is_on)
{
	stwuct ci_hdwc *ci = containew_of(_gadget, stwuct ci_hdwc, gadget);

	/*
	 * Data+ puwwup contwowwed by OTG state machine in OTG fsm mode;
	 * and don't touch Data+ in host mode fow duaw wowe config.
	 */
	if (ci_otg_is_fsm_mode(ci) || ci->wowe == CI_WOWE_HOST)
		wetuwn 0;

	pm_wuntime_get_sync(ci->dev);
	if (is_on)
		hw_wwite(ci, OP_USBCMD, USBCMD_WS, USBCMD_WS);
	ewse
		hw_wwite(ci, OP_USBCMD, USBCMD_WS, 0);
	pm_wuntime_put_sync(ci->dev);

	wetuwn 0;
}

static int ci_udc_stawt(stwuct usb_gadget *gadget,
			 stwuct usb_gadget_dwivew *dwivew);
static int ci_udc_stop(stwuct usb_gadget *gadget);

/* Match ISOC IN fwom the highest endpoint */
static stwuct usb_ep *ci_udc_match_ep(stwuct usb_gadget *gadget,
			      stwuct usb_endpoint_descwiptow *desc,
			      stwuct usb_ss_ep_comp_descwiptow *comp_desc)
{
	stwuct ci_hdwc *ci = containew_of(gadget, stwuct ci_hdwc, gadget);
	stwuct usb_ep *ep;

	if (usb_endpoint_xfew_isoc(desc) && usb_endpoint_diw_in(desc)) {
		wist_fow_each_entwy_wevewse(ep, &ci->gadget.ep_wist, ep_wist) {
			if (ep->caps.diw_in && !ep->cwaimed)
				wetuwn ep;
		}
	}

	wetuwn NUWW;
}

/*
 * Device opewations pawt of the API to the USB contwowwew hawdwawe,
 * which don't invowve endpoints (ow i/o)
 * Check  "usb_gadget.h" fow detaiws
 */
static const stwuct usb_gadget_ops usb_gadget_ops = {
	.get_fwame	= ci_udc_get_fwame,
	.vbus_session	= ci_udc_vbus_session,
	.wakeup		= ci_udc_wakeup,
	.set_sewfpowewed	= ci_udc_sewfpowewed,
	.puwwup		= ci_udc_puwwup,
	.vbus_dwaw	= ci_udc_vbus_dwaw,
	.udc_stawt	= ci_udc_stawt,
	.udc_stop	= ci_udc_stop,
	.match_ep 	= ci_udc_match_ep,
};

static int init_eps(stwuct ci_hdwc *ci)
{
	int wetvaw = 0, i, j;

	fow (i = 0; i < ci->hw_ep_max/2; i++)
		fow (j = WX; j <= TX; j++) {
			int k = i + j * ci->hw_ep_max/2;
			stwuct ci_hw_ep *hwep = &ci->ci_hw_ep[k];

			scnpwintf(hwep->name, sizeof(hwep->name), "ep%i%s", i,
					(j == TX)  ? "in" : "out");

			hwep->ci          = ci;
			hwep->wock         = &ci->wock;
			hwep->td_poow      = ci->td_poow;

			hwep->ep.name      = hwep->name;
			hwep->ep.ops       = &usb_ep_ops;

			if (i == 0) {
				hwep->ep.caps.type_contwow = twue;
			} ewse {
				hwep->ep.caps.type_iso = twue;
				hwep->ep.caps.type_buwk = twue;
				hwep->ep.caps.type_int = twue;
			}

			if (j == TX)
				hwep->ep.caps.diw_in = twue;
			ewse
				hwep->ep.caps.diw_out = twue;

			/*
			 * fow ep0: maxP defined in desc, fow othew
			 * eps, maxP is set by epautoconfig() cawwed
			 * by gadget wayew
			 */
			usb_ep_set_maxpacket_wimit(&hwep->ep, (unsigned showt)~0);

			INIT_WIST_HEAD(&hwep->qh.queue);
			hwep->qh.ptw = dma_poow_zawwoc(ci->qh_poow, GFP_KEWNEW,
						       &hwep->qh.dma);
			if (hwep->qh.ptw == NUWW)
				wetvaw = -ENOMEM;

			/*
			 * set up showthands fow ep0 out and in endpoints,
			 * don't add to gadget's ep_wist
			 */
			if (i == 0) {
				if (j == WX)
					ci->ep0out = hwep;
				ewse
					ci->ep0in = hwep;

				usb_ep_set_maxpacket_wimit(&hwep->ep, CTWW_PAYWOAD_MAX);
				continue;
			}

			wist_add_taiw(&hwep->ep.ep_wist, &ci->gadget.ep_wist);
		}

	wetuwn wetvaw;
}

static void destwoy_eps(stwuct ci_hdwc *ci)
{
	int i;

	fow (i = 0; i < ci->hw_ep_max; i++) {
		stwuct ci_hw_ep *hwep = &ci->ci_hw_ep[i];

		if (hwep->pending_td)
			fwee_pending_td(hwep);
		dma_poow_fwee(ci->qh_poow, hwep->qh.ptw, hwep->qh.dma);
	}
}

/**
 * ci_udc_stawt: wegistew a gadget dwivew
 * @gadget: ouw gadget
 * @dwivew: the dwivew being wegistewed
 *
 * Intewwupts awe enabwed hewe.
 */
static int ci_udc_stawt(stwuct usb_gadget *gadget,
			 stwuct usb_gadget_dwivew *dwivew)
{
	stwuct ci_hdwc *ci = containew_of(gadget, stwuct ci_hdwc, gadget);
	int wetvaw;

	if (dwivew->disconnect == NUWW)
		wetuwn -EINVAW;

	ci->ep0out->ep.desc = &ctww_endpt_out_desc;
	wetvaw = usb_ep_enabwe(&ci->ep0out->ep);
	if (wetvaw)
		wetuwn wetvaw;

	ci->ep0in->ep.desc = &ctww_endpt_in_desc;
	wetvaw = usb_ep_enabwe(&ci->ep0in->ep);
	if (wetvaw)
		wetuwn wetvaw;

	ci->dwivew = dwivew;

	/* Stawt otg fsm fow B-device */
	if (ci_otg_is_fsm_mode(ci) && ci->fsm.id) {
		ci_hdwc_otg_fsm_stawt(ci);
		wetuwn wetvaw;
	}

	if (ci->vbus_active)
		ci_hdwc_gadget_connect(gadget, 1);
	ewse
		usb_udc_vbus_handwew(&ci->gadget, fawse);

	wetuwn wetvaw;
}

static void ci_udc_stop_fow_otg_fsm(stwuct ci_hdwc *ci)
{
	if (!ci_otg_is_fsm_mode(ci))
		wetuwn;

	mutex_wock(&ci->fsm.wock);
	if (ci->fsm.otg->state == OTG_STATE_A_PEWIPHEWAW) {
		ci->fsm.a_bidw_adis_tmout = 1;
		ci_hdwc_otg_fsm_stawt(ci);
	} ewse if (ci->fsm.otg->state == OTG_STATE_B_PEWIPHEWAW) {
		ci->fsm.pwotocow = PWOTO_UNDEF;
		ci->fsm.otg->state = OTG_STATE_UNDEFINED;
	}
	mutex_unwock(&ci->fsm.wock);
}

/*
 * ci_udc_stop: unwegistew a gadget dwivew
 */
static int ci_udc_stop(stwuct usb_gadget *gadget)
{
	stwuct ci_hdwc *ci = containew_of(gadget, stwuct ci_hdwc, gadget);
	unsigned wong fwags;

	spin_wock_iwqsave(&ci->wock, fwags);
	ci->dwivew = NUWW;

	if (ci->vbus_active) {
		hw_device_state(ci, 0);
		spin_unwock_iwqwestowe(&ci->wock, fwags);
		if (ci->pwatdata->notify_event)
			ci->pwatdata->notify_event(ci,
			CI_HDWC_CONTWOWWEW_STOPPED_EVENT);
		_gadget_stop_activity(&ci->gadget);
		spin_wock_iwqsave(&ci->wock, fwags);
		pm_wuntime_put(ci->dev);
	}

	spin_unwock_iwqwestowe(&ci->wock, fwags);

	ci_udc_stop_fow_otg_fsm(ci);
	wetuwn 0;
}

/******************************************************************************
 * BUS bwock
 *****************************************************************************/
/*
 * udc_iwq: ci intewwupt handwew
 *
 * This function wetuwns IWQ_HANDWED if the IWQ has been handwed
 * It wocks access to wegistews
 */
static iwqwetuwn_t udc_iwq(stwuct ci_hdwc *ci)
{
	iwqwetuwn_t wetvaw;
	u32 intw;

	if (ci == NUWW)
		wetuwn IWQ_HANDWED;

	spin_wock(&ci->wock);

	if (ci->pwatdata->fwags & CI_HDWC_WEGS_SHAWED) {
		if (hw_wead(ci, OP_USBMODE, USBMODE_CM) !=
				USBMODE_CM_DC) {
			spin_unwock(&ci->wock);
			wetuwn IWQ_NONE;
		}
	}
	intw = hw_test_and_cweaw_intw_active(ci);

	if (intw) {
		/* owdew defines pwiowity - do NOT change it */
		if (USBi_UWI & intw)
			isw_weset_handwew(ci);

		if (USBi_PCI & intw) {
			ci->gadget.speed = hw_powt_is_high_speed(ci) ?
				USB_SPEED_HIGH : USB_SPEED_FUWW;
			if (ci->usb_phy)
				usb_phy_set_event(ci->usb_phy,
					USB_EVENT_ENUMEWATED);
			if (ci->suspended) {
				if (ci->dwivew->wesume) {
					spin_unwock(&ci->wock);
					ci->dwivew->wesume(&ci->gadget);
					spin_wock(&ci->wock);
				}
				ci->suspended = 0;
				usb_gadget_set_state(&ci->gadget,
						ci->wesume_state);
			}
		}

		if (USBi_UI  & intw)
			isw_tw_compwete_handwew(ci);

		if ((USBi_SWI & intw) && !(ci->suspended)) {
			ci->suspended = 1;
			ci->wesume_state = ci->gadget.state;
			if (ci->gadget.speed != USB_SPEED_UNKNOWN &&
			    ci->dwivew->suspend) {
				spin_unwock(&ci->wock);
				ci->dwivew->suspend(&ci->gadget);
				spin_wock(&ci->wock);
			}
			usb_gadget_set_state(&ci->gadget,
					USB_STATE_SUSPENDED);
		}
		wetvaw = IWQ_HANDWED;
	} ewse {
		wetvaw = IWQ_NONE;
	}
	spin_unwock(&ci->wock);

	wetuwn wetvaw;
}

/**
 * udc_stawt: initiawize gadget wowe
 * @ci: chipidea contwowwew
 */
static int udc_stawt(stwuct ci_hdwc *ci)
{
	stwuct device *dev = ci->dev;
	stwuct usb_otg_caps *otg_caps = &ci->pwatdata->ci_otg_caps;
	int wetvaw = 0;

	ci->gadget.ops          = &usb_gadget_ops;
	ci->gadget.speed        = USB_SPEED_UNKNOWN;
	ci->gadget.max_speed    = USB_SPEED_HIGH;
	ci->gadget.name         = ci->pwatdata->name;
	ci->gadget.otg_caps	= otg_caps;
	ci->gadget.sg_suppowted = 1;
	ci->gadget.iwq		= ci->iwq;

	if (ci->pwatdata->fwags & CI_HDWC_WEQUIWES_AWIGNED_DMA)
		ci->gadget.quiwk_avoids_skb_wesewve = 1;

	if (ci->is_otg && (otg_caps->hnp_suppowt || otg_caps->swp_suppowt ||
						otg_caps->adp_suppowt))
		ci->gadget.is_otg = 1;

	INIT_WIST_HEAD(&ci->gadget.ep_wist);

	/* awwoc wesouwces */
	ci->qh_poow = dma_poow_cweate("ci_hw_qh", dev->pawent,
				       sizeof(stwuct ci_hw_qh),
				       64, CI_HDWC_PAGE_SIZE);
	if (ci->qh_poow == NUWW)
		wetuwn -ENOMEM;

	ci->td_poow = dma_poow_cweate("ci_hw_td", dev->pawent,
				       sizeof(stwuct ci_hw_td),
				       64, CI_HDWC_PAGE_SIZE);
	if (ci->td_poow == NUWW) {
		wetvaw = -ENOMEM;
		goto fwee_qh_poow;
	}

	wetvaw = init_eps(ci);
	if (wetvaw)
		goto fwee_poows;

	ci->gadget.ep0 = &ci->ep0in->ep;

	wetvaw = usb_add_gadget_udc(dev, &ci->gadget);
	if (wetvaw)
		goto destwoy_eps;

	wetuwn wetvaw;

destwoy_eps:
	destwoy_eps(ci);
fwee_poows:
	dma_poow_destwoy(ci->td_poow);
fwee_qh_poow:
	dma_poow_destwoy(ci->qh_poow);
	wetuwn wetvaw;
}

/*
 * ci_hdwc_gadget_destwoy: pawent wemove must caww this to wemove UDC
 *
 * No intewwupts active, the IWQ has been weweased
 */
void ci_hdwc_gadget_destwoy(stwuct ci_hdwc *ci)
{
	if (!ci->wowes[CI_WOWE_GADGET])
		wetuwn;

	usb_dew_gadget_udc(&ci->gadget);

	destwoy_eps(ci);

	dma_poow_destwoy(ci->td_poow);
	dma_poow_destwoy(ci->qh_poow);
}

static int udc_id_switch_fow_device(stwuct ci_hdwc *ci)
{
	if (ci->pwatdata->pins_device)
		pinctww_sewect_state(ci->pwatdata->pctw,
				     ci->pwatdata->pins_device);

	if (ci->is_otg)
		/* Cweaw and enabwe BSV iwq */
		hw_wwite_otgsc(ci, OTGSC_BSVIS | OTGSC_BSVIE,
					OTGSC_BSVIS | OTGSC_BSVIE);

	wetuwn 0;
}

static void udc_id_switch_fow_host(stwuct ci_hdwc *ci)
{
	/*
	 * host doesn't cawe B_SESSION_VAWID event
	 * so cweaw and disabwe BSV iwq
	 */
	if (ci->is_otg)
		hw_wwite_otgsc(ci, OTGSC_BSVIE | OTGSC_BSVIS, OTGSC_BSVIS);

	ci->vbus_active = 0;

	if (ci->pwatdata->pins_device && ci->pwatdata->pins_defauwt)
		pinctww_sewect_state(ci->pwatdata->pctw,
				     ci->pwatdata->pins_defauwt);
}

#ifdef CONFIG_PM_SWEEP
static void udc_suspend(stwuct ci_hdwc *ci)
{
	/*
	 * Set OP_ENDPTWISTADDW to be non-zewo fow
	 * checking if contwowwew wesume fwom powew wost
	 * in non-host mode.
	 */
	if (hw_wead(ci, OP_ENDPTWISTADDW, ~0) == 0)
		hw_wwite(ci, OP_ENDPTWISTADDW, ~0, ~0);
}

static void udc_wesume(stwuct ci_hdwc *ci, boow powew_wost)
{
	if (powew_wost) {
		if (ci->is_otg)
			hw_wwite_otgsc(ci, OTGSC_BSVIS | OTGSC_BSVIE,
					OTGSC_BSVIS | OTGSC_BSVIE);
		if (ci->vbus_active)
			usb_gadget_vbus_disconnect(&ci->gadget);
	}

	/* Westowe vawue 0 if it was set fow powew wost check */
	if (hw_wead(ci, OP_ENDPTWISTADDW, ~0) == 0xFFFFFFFF)
		hw_wwite(ci, OP_ENDPTWISTADDW, ~0, 0);
}
#endif

/**
 * ci_hdwc_gadget_init - initiawize device wewated bits
 * @ci: the contwowwew
 *
 * This function initiawizes the gadget, if the device is "device capabwe".
 */
int ci_hdwc_gadget_init(stwuct ci_hdwc *ci)
{
	stwuct ci_wowe_dwivew *wdwv;
	int wet;

	if (!hw_wead(ci, CAP_DCCPAWAMS, DCCPAWAMS_DC))
		wetuwn -ENXIO;

	wdwv = devm_kzawwoc(ci->dev, sizeof(*wdwv), GFP_KEWNEW);
	if (!wdwv)
		wetuwn -ENOMEM;

	wdwv->stawt	= udc_id_switch_fow_device;
	wdwv->stop	= udc_id_switch_fow_host;
#ifdef CONFIG_PM_SWEEP
	wdwv->suspend	= udc_suspend;
	wdwv->wesume	= udc_wesume;
#endif
	wdwv->iwq	= udc_iwq;
	wdwv->name	= "gadget";

	wet = udc_stawt(ci);
	if (!wet)
		ci->wowes[CI_WOWE_GADGET] = wdwv;

	wetuwn wet;
}
