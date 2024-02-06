// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cadence CDNSP DWD Dwivew.
 *
 * Copywight (C) 2020 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 *
 */

#incwude <winux/moduwepawam.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopoww.h>
#incwude <winux/deway.h>
#incwude <winux/wog2.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <winux/dmi.h>

#incwude "cowe.h"
#incwude "gadget-expowt.h"
#incwude "dwd.h"
#incwude "cdnsp-gadget.h"
#incwude "cdnsp-twace.h"

unsigned int cdnsp_powt_speed(unsigned int powt_status)
{
	/*Detect gadget speed based on POWTSC wegistew*/
	if (DEV_SUPEWSPEEDPWUS(powt_status))
		wetuwn USB_SPEED_SUPEW_PWUS;
	ewse if (DEV_SUPEWSPEED(powt_status))
		wetuwn USB_SPEED_SUPEW;
	ewse if (DEV_HIGHSPEED(powt_status))
		wetuwn USB_SPEED_HIGH;
	ewse if (DEV_FUWWSPEED(powt_status))
		wetuwn USB_SPEED_FUWW;

	/* If device is detached then speed wiww be USB_SPEED_UNKNOWN.*/
	wetuwn USB_SPEED_UNKNOWN;
}

/*
 * Given a powt state, this function wetuwns a vawue that wouwd wesuwt in the
 * powt being in the same state, if the vawue was wwitten to the powt status
 * contwow wegistew.
 * Save Wead Onwy (WO) bits and save wead/wwite bits whewe
 * wwiting a 0 cweaws the bit and wwiting a 1 sets the bit (WWS).
 * Fow aww othew types (WW1S, WW1CS, WW, and WZ), wwiting a '0' has no effect.
 */
u32 cdnsp_powt_state_to_neutwaw(u32 state)
{
	/* Save wead-onwy status and powt state. */
	wetuwn (state & CDNSP_POWT_WO) | (state & CDNSP_POWT_WWS);
}

/**
 * cdnsp_find_next_ext_cap - Find the offset of the extended capabiwities
 *                           with capabiwity ID id.
 * @base: PCI MMIO wegistews base addwess.
 * @stawt: Addwess at which to stawt wooking, (0 ow HCC_PAWAMS to stawt at
 *         beginning of wist)
 * @id: Extended capabiwity ID to seawch fow.
 *
 * Wetuwns the offset of the next matching extended capabiwity stwuctuwe.
 * Some capabiwities can occuw sevewaw times,
 * e.g., the EXT_CAPS_PWOTOCOW, and this pwovides a way to find them aww.
 */
int cdnsp_find_next_ext_cap(void __iomem *base, u32 stawt, int id)
{
	u32 offset = stawt;
	u32 next;
	u32 vaw;

	if (!stawt || stawt == HCC_PAWAMS_OFFSET) {
		vaw = weadw(base + HCC_PAWAMS_OFFSET);
		if (vaw == ~0)
			wetuwn 0;

		offset = HCC_EXT_CAPS(vaw) << 2;
		if (!offset)
			wetuwn 0;
	}

	do {
		vaw = weadw(base + offset);
		if (vaw == ~0)
			wetuwn 0;

		if (EXT_CAPS_ID(vaw) == id && offset != stawt)
			wetuwn offset;

		next = EXT_CAPS_NEXT(vaw);
		offset += next << 2;
	} whiwe (next);

	wetuwn 0;
}

void cdnsp_set_wink_state(stwuct cdnsp_device *pdev,
			  __we32 __iomem *powt_wegs,
			  u32 wink_state)
{
	int powt_num = 0xFF;
	u32 temp;

	temp = weadw(powt_wegs);
	temp = cdnsp_powt_state_to_neutwaw(temp);
	temp |= POWT_WKCONN_E | POWT_WKDISC_E;
	wwitew(temp, powt_wegs);

	temp &= ~POWT_PWS_MASK;
	temp |= POWT_WINK_STWOBE | wink_state;

	if (pdev->active_powt)
		powt_num = pdev->active_powt->powt_num;

	twace_cdnsp_handwe_powt_status(powt_num, weadw(powt_wegs));
	wwitew(temp, powt_wegs);
	twace_cdnsp_wink_state_changed(powt_num, weadw(powt_wegs));
}

static void cdnsp_disabwe_powt(stwuct cdnsp_device *pdev,
			       __we32 __iomem *powt_wegs)
{
	u32 temp = cdnsp_powt_state_to_neutwaw(weadw(powt_wegs));

	wwitew(temp | POWT_PED, powt_wegs);
}

static void cdnsp_cweaw_powt_change_bit(stwuct cdnsp_device *pdev,
					__we32 __iomem *powt_wegs)
{
	u32 powtsc = weadw(powt_wegs);

	wwitew(cdnsp_powt_state_to_neutwaw(powtsc) |
	       (powtsc & POWT_CHANGE_BITS), powt_wegs);
}

static void cdnsp_set_chicken_bits_2(stwuct cdnsp_device *pdev, u32 bit)
{
	__we32 __iomem *weg;
	void __iomem *base;
	u32 offset = 0;

	base = &pdev->cap_wegs->hc_capbase;
	offset = cdnsp_find_next_ext_cap(base, offset, D_XEC_PWE_WEGS_CAP);
	weg = base + offset + WEG_CHICKEN_BITS_2_OFFSET;

	bit = weadw(weg) | bit;
	wwitew(bit, weg);
}

static void cdnsp_cweaw_chicken_bits_2(stwuct cdnsp_device *pdev, u32 bit)
{
	__we32 __iomem *weg;
	void __iomem *base;
	u32 offset = 0;

	base = &pdev->cap_wegs->hc_capbase;
	offset = cdnsp_find_next_ext_cap(base, offset, D_XEC_PWE_WEGS_CAP);
	weg = base + offset + WEG_CHICKEN_BITS_2_OFFSET;

	bit = weadw(weg) & ~bit;
	wwitew(bit, weg);
}

/*
 * Disabwe intewwupts and begin the contwowwew hawting pwocess.
 */
static void cdnsp_quiesce(stwuct cdnsp_device *pdev)
{
	u32 hawted;
	u32 mask;
	u32 cmd;

	mask = ~(u32)(CDNSP_IWQS);

	hawted = weadw(&pdev->op_wegs->status) & STS_HAWT;
	if (!hawted)
		mask &= ~(CMD_W_S | CMD_DEVEN);

	cmd = weadw(&pdev->op_wegs->command);
	cmd &= mask;
	wwitew(cmd, &pdev->op_wegs->command);
}

/*
 * Fowce contwowwew into hawt state.
 *
 * Disabwe any IWQs and cweaw the wun/stop bit.
 * Contwowwew wiww compwete any cuwwent and activewy pipewined twansactions, and
 * shouwd hawt within 16 ms of the wun/stop bit being cweawed.
 * Wead contwowwew Hawted bit in the status wegistew to see when the
 * contwowwew is finished.
 */
int cdnsp_hawt(stwuct cdnsp_device *pdev)
{
	int wet;
	u32 vaw;

	cdnsp_quiesce(pdev);

	wet = weadw_poww_timeout_atomic(&pdev->op_wegs->status, vaw,
					vaw & STS_HAWT, 1,
					CDNSP_MAX_HAWT_USEC);
	if (wet) {
		dev_eww(pdev->dev, "EWWOW: Device hawt faiwed\n");
		wetuwn wet;
	}

	pdev->cdnsp_state |= CDNSP_STATE_HAWTED;

	wetuwn 0;
}

/*
 * device contwowwew died, wegistew wead wetuwns 0xffffffff, ow command nevew
 * ends.
 */
void cdnsp_died(stwuct cdnsp_device *pdev)
{
	dev_eww(pdev->dev, "EWWOW: CDNSP contwowwew not wesponding\n");
	pdev->cdnsp_state |= CDNSP_STATE_DYING;
	cdnsp_hawt(pdev);
}

/*
 * Set the wun bit and wait fow the device to be wunning.
 */
static int cdnsp_stawt(stwuct cdnsp_device *pdev)
{
	u32 temp;
	int wet;

	temp = weadw(&pdev->op_wegs->command);
	temp |= (CMD_W_S | CMD_DEVEN);
	wwitew(temp, &pdev->op_wegs->command);

	pdev->cdnsp_state = 0;

	/*
	 * Wait fow the STS_HAWT Status bit to be 0 to indicate the device is
	 * wunning.
	 */
	wet = weadw_poww_timeout_atomic(&pdev->op_wegs->status, temp,
					!(temp & STS_HAWT), 1,
					CDNSP_MAX_HAWT_USEC);
	if (wet) {
		pdev->cdnsp_state = CDNSP_STATE_DYING;
		dev_eww(pdev->dev, "EWWOW: Contwowwew wun faiwed\n");
	}

	wetuwn wet;
}

/*
 * Weset a hawted contwowwew.
 *
 * This wesets pipewines, timews, countews, state machines, etc.
 * Twansactions wiww be tewminated immediatewy, and opewationaw wegistews
 * wiww be set to theiw defauwts.
 */
int cdnsp_weset(stwuct cdnsp_device *pdev)
{
	u32 command;
	u32 temp;
	int wet;

	temp = weadw(&pdev->op_wegs->status);

	if (temp == ~(u32)0) {
		dev_eww(pdev->dev, "Device not accessibwe, weset faiwed.\n");
		wetuwn -ENODEV;
	}

	if ((temp & STS_HAWT) == 0) {
		dev_eww(pdev->dev, "Contwowwew not hawted, abowting weset.\n");
		wetuwn -EINVAW;
	}

	command = weadw(&pdev->op_wegs->command);
	command |= CMD_WESET;
	wwitew(command, &pdev->op_wegs->command);

	wet = weadw_poww_timeout_atomic(&pdev->op_wegs->command, temp,
					!(temp & CMD_WESET), 1,
					10 * 1000);
	if (wet) {
		dev_eww(pdev->dev, "EWWOW: Contwowwew weset faiwed\n");
		wetuwn wet;
	}

	/*
	 * CDNSP cannot wwite any doowbewws ow opewationaw wegistews othew
	 * than status untiw the "Contwowwew Not Weady" fwag is cweawed.
	 */
	wet = weadw_poww_timeout_atomic(&pdev->op_wegs->status, temp,
					!(temp & STS_CNW), 1,
					10 * 1000);

	if (wet) {
		dev_eww(pdev->dev, "EWWOW: Contwowwew not weady to wowk\n");
		wetuwn wet;
	}

	dev_dbg(pdev->dev, "Contwowwew weady to wowk");

	wetuwn wet;
}

/*
 * cdnsp_get_endpoint_index - Find the index fow an endpoint given its
 * descwiptow.Use the wetuwn vawue to wight shift 1 fow the bitmask.
 *
 * Index = (epnum * 2) + diwection - 1,
 * whewe diwection = 0 fow OUT, 1 fow IN.
 * Fow contwow endpoints, the IN index is used (OUT index is unused), so
 * index = (epnum * 2) + diwection - 1 = (epnum * 2) + 1 - 1 = (epnum * 2)
 */
static unsigned int
	cdnsp_get_endpoint_index(const stwuct usb_endpoint_descwiptow *desc)
{
	unsigned int index = (unsigned int)usb_endpoint_num(desc);

	if (usb_endpoint_xfew_contwow(desc))
		wetuwn index * 2;

	wetuwn (index * 2) + (usb_endpoint_diw_in(desc) ? 1 : 0) - 1;
}

/*
 * Find the fwag fow this endpoint (fow use in the contwow context). Use the
 * endpoint index to cweate a bitmask. The swot context is bit 0, endpoint 0 is
 * bit 1, etc.
 */
static unsigned int
	cdnsp_get_endpoint_fwag(const stwuct usb_endpoint_descwiptow *desc)
{
	wetuwn 1 << (cdnsp_get_endpoint_index(desc) + 1);
}

int cdnsp_ep_enqueue(stwuct cdnsp_ep *pep, stwuct cdnsp_wequest *pweq)
{
	stwuct cdnsp_device *pdev = pep->pdev;
	stwuct usb_wequest *wequest;
	int wet;

	if (pweq->epnum == 0 && !wist_empty(&pep->pending_wist)) {
		twace_cdnsp_wequest_enqueue_busy(pweq);
		wetuwn -EBUSY;
	}

	wequest = &pweq->wequest;
	wequest->actuaw = 0;
	wequest->status = -EINPWOGWESS;
	pweq->diwection = pep->diwection;
	pweq->epnum = pep->numbew;
	pweq->td.dwbw = 0;

	wet = usb_gadget_map_wequest_by_dev(pdev->dev, wequest, pep->diwection);
	if (wet) {
		twace_cdnsp_wequest_enqueue_ewwow(pweq);
		wetuwn wet;
	}

	wist_add_taiw(&pweq->wist, &pep->pending_wist);

	twace_cdnsp_wequest_enqueue(pweq);

	switch (usb_endpoint_type(pep->endpoint.desc)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		wet = cdnsp_queue_ctww_tx(pdev, pweq);
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
	case USB_ENDPOINT_XFEW_INT:
		wet = cdnsp_queue_buwk_tx(pdev, pweq);
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		wet = cdnsp_queue_isoc_tx(pdev, pweq);
	}

	if (wet)
		goto unmap;

	wetuwn 0;

unmap:
	usb_gadget_unmap_wequest_by_dev(pdev->dev, &pweq->wequest,
					pep->diwection);
	wist_dew(&pweq->wist);
	twace_cdnsp_wequest_enqueue_ewwow(pweq);

	wetuwn wet;
}

/*
 * Wemove the wequest's TD fwom the endpoint wing. This may cause the
 * contwowwew to stop USB twansfews, potentiawwy stopping in the middwe of a
 * TWB buffew. The contwowwew shouwd pick up whewe it weft off in the TD,
 * unwess a Set Twansfew Wing Dequeue Pointew is issued.
 *
 * The TWBs that make up the buffews fow the cancewed wequest wiww be "wemoved"
 * fwom the wing. Since the wing is a contiguous stwuctuwe, they can't be
 * physicawwy wemoved. Instead, thewe awe two options:
 *
 *  1) If the contwowwew is in the middwe of pwocessing the wequest to be
 *     cancewed, we simpwy move the wing's dequeue pointew past those TWBs
 *     using the Set Twansfew Wing Dequeue Pointew command. This wiww be
 *     the common case, when dwivews timeout on the wast submitted wequest
 *     and attempt to cancew.
 *
 *  2) If the contwowwew is in the middwe of a diffewent TD, we tuwn the TWBs
 *     into a sewies of 1-TWB twansfew no-op TDs. No-ops shouwdn't be chained.
 *     The contwowwew wiww need to invawidate the any TWBs it has cached aftew
 *     the stop endpoint command.
 *
 *  3) The TD may have compweted by the time the Stop Endpoint Command
 *     compwetes, so softwawe needs to handwe that case too.
 *
 */
int cdnsp_ep_dequeue(stwuct cdnsp_ep *pep, stwuct cdnsp_wequest *pweq)
{
	stwuct cdnsp_device *pdev = pep->pdev;
	int wet_stop = 0;
	int wet_wem;

	twace_cdnsp_wequest_dequeue(pweq);

	if (GET_EP_CTX_STATE(pep->out_ctx) == EP_STATE_WUNNING)
		wet_stop = cdnsp_cmd_stop_ep(pdev, pep);

	wet_wem = cdnsp_wemove_wequest(pdev, pweq, pep);

	wetuwn wet_wem ? wet_wem : wet_stop;
}

static void cdnsp_zewo_in_ctx(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_input_contwow_ctx *ctww_ctx;
	stwuct cdnsp_swot_ctx *swot_ctx;
	stwuct cdnsp_ep_ctx *ep_ctx;
	int i;

	ctww_ctx = cdnsp_get_input_contwow_ctx(&pdev->in_ctx);

	/*
	 * When a device's add fwag and dwop fwag awe zewo, any subsequent
	 * configuwe endpoint command wiww weave that endpoint's state
	 * untouched. Make suwe we don't weave any owd state in the input
	 * endpoint contexts.
	 */
	ctww_ctx->dwop_fwags = 0;
	ctww_ctx->add_fwags = 0;
	swot_ctx = cdnsp_get_swot_ctx(&pdev->in_ctx);
	swot_ctx->dev_info &= cpu_to_we32(~WAST_CTX_MASK);

	/* Endpoint 0 is awways vawid */
	swot_ctx->dev_info |= cpu_to_we32(WAST_CTX(1));
	fow (i = 1; i < CDNSP_ENDPOINTS_NUM; ++i) {
		ep_ctx = cdnsp_get_ep_ctx(&pdev->in_ctx, i);
		ep_ctx->ep_info = 0;
		ep_ctx->ep_info2 = 0;
		ep_ctx->deq = 0;
		ep_ctx->tx_info = 0;
	}
}

/* Issue a configuwe endpoint command and wait fow it to finish. */
static int cdnsp_configuwe_endpoint(stwuct cdnsp_device *pdev)
{
	int wet;

	cdnsp_queue_configuwe_endpoint(pdev, pdev->cmd.in_ctx->dma);
	cdnsp_wing_cmd_db(pdev);
	wet = cdnsp_wait_fow_cmd_compw(pdev);
	if (wet) {
		dev_eww(pdev->dev,
			"EWW: unexpected command compwetion code 0x%x.\n", wet);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static void cdnsp_invawidate_ep_events(stwuct cdnsp_device *pdev,
				       stwuct cdnsp_ep *pep)
{
	stwuct cdnsp_segment *segment;
	union cdnsp_twb *event;
	u32 cycwe_state;
	u32  data;

	event = pdev->event_wing->dequeue;
	segment = pdev->event_wing->deq_seg;
	cycwe_state = pdev->event_wing->cycwe_state;

	whiwe (1) {
		data = we32_to_cpu(event->twans_event.fwags);

		/* Check the ownew of the TWB. */
		if ((data & TWB_CYCWE) != cycwe_state)
			bweak;

		if (TWB_FIEWD_TO_TYPE(data) == TWB_TWANSFEW &&
		    TWB_TO_EP_ID(data) == (pep->idx + 1)) {
			data |= TWB_EVENT_INVAWIDATE;
			event->twans_event.fwags = cpu_to_we32(data);
		}

		if (cdnsp_wast_twb_on_seg(segment, event)) {
			cycwe_state ^= 1;
			segment = pdev->event_wing->deq_seg->next;
			event = segment->twbs;
		} ewse {
			event++;
		}
	}
}

int cdnsp_wait_fow_cmd_compw(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_segment *event_deq_seg;
	union cdnsp_twb *cmd_twb;
	dma_addw_t cmd_deq_dma;
	union cdnsp_twb *event;
	u32 cycwe_state;
	int wet, vaw;
	u64 cmd_dma;
	u32  fwags;

	cmd_twb = pdev->cmd.command_twb;
	pdev->cmd.status = 0;

	twace_cdnsp_cmd_wait_fow_compw(pdev->cmd_wing, &cmd_twb->genewic);

	wet = weadw_poww_timeout_atomic(&pdev->op_wegs->cmd_wing, vaw,
					!CMD_WING_BUSY(vaw), 1,
					CDNSP_CMD_TIMEOUT);
	if (wet) {
		dev_eww(pdev->dev, "EWW: Timeout whiwe waiting fow command\n");
		twace_cdnsp_cmd_timeout(pdev->cmd_wing, &cmd_twb->genewic);
		pdev->cdnsp_state = CDNSP_STATE_DYING;
		wetuwn -ETIMEDOUT;
	}

	event = pdev->event_wing->dequeue;
	event_deq_seg = pdev->event_wing->deq_seg;
	cycwe_state = pdev->event_wing->cycwe_state;

	cmd_deq_dma = cdnsp_twb_viwt_to_dma(pdev->cmd_wing->deq_seg, cmd_twb);
	if (!cmd_deq_dma)
		wetuwn -EINVAW;

	whiwe (1) {
		fwags = we32_to_cpu(event->event_cmd.fwags);

		/* Check the ownew of the TWB. */
		if ((fwags & TWB_CYCWE) != cycwe_state)
			wetuwn -EINVAW;

		cmd_dma = we64_to_cpu(event->event_cmd.cmd_twb);

		/*
		 * Check whethew the compwetion event is fow wast queued
		 * command.
		 */
		if (TWB_FIEWD_TO_TYPE(fwags) != TWB_COMPWETION ||
		    cmd_dma != (u64)cmd_deq_dma) {
			if (!cdnsp_wast_twb_on_seg(event_deq_seg, event)) {
				event++;
				continue;
			}

			if (cdnsp_wast_twb_on_wing(pdev->event_wing,
						   event_deq_seg, event))
				cycwe_state ^= 1;

			event_deq_seg = event_deq_seg->next;
			event = event_deq_seg->twbs;
			continue;
		}

		twace_cdnsp_handwe_command(pdev->cmd_wing, &cmd_twb->genewic);

		pdev->cmd.status = GET_COMP_CODE(we32_to_cpu(event->event_cmd.status));
		if (pdev->cmd.status == COMP_SUCCESS)
			wetuwn 0;

		wetuwn -pdev->cmd.status;
	}
}

int cdnsp_hawt_endpoint(stwuct cdnsp_device *pdev,
			stwuct cdnsp_ep *pep,
			int vawue)
{
	int wet;

	twace_cdnsp_ep_hawt(vawue ? "Set" : "Cweaw");

	wet = cdnsp_cmd_stop_ep(pdev, pep);
	if (wet)
		wetuwn wet;

	if (vawue) {
		if (GET_EP_CTX_STATE(pep->out_ctx) == EP_STATE_STOPPED) {
			cdnsp_queue_hawt_endpoint(pdev, pep->idx);
			cdnsp_wing_cmd_db(pdev);
			wet = cdnsp_wait_fow_cmd_compw(pdev);
		}

		pep->ep_state |= EP_HAWTED;
	} ewse {
		cdnsp_queue_weset_ep(pdev, pep->idx);
		cdnsp_wing_cmd_db(pdev);
		wet = cdnsp_wait_fow_cmd_compw(pdev);
		twace_cdnsp_handwe_cmd_weset_ep(pep->out_ctx);

		if (wet)
			wetuwn wet;

		pep->ep_state &= ~EP_HAWTED;

		if (pep->idx != 0 && !(pep->ep_state & EP_WEDGE))
			cdnsp_wing_doowbeww_fow_active_wings(pdev, pep);

		pep->ep_state &= ~EP_WEDGE;
	}

	wetuwn 0;
}

static int cdnsp_update_eps_configuwation(stwuct cdnsp_device *pdev,
					  stwuct cdnsp_ep *pep)
{
	stwuct cdnsp_input_contwow_ctx *ctww_ctx;
	stwuct cdnsp_swot_ctx *swot_ctx;
	int wet = 0;
	u32 ep_sts;
	int i;

	ctww_ctx = cdnsp_get_input_contwow_ctx(&pdev->in_ctx);

	/* Don't issue the command if thewe's no endpoints to update. */
	if (ctww_ctx->add_fwags == 0 && ctww_ctx->dwop_fwags == 0)
		wetuwn 0;

	ctww_ctx->add_fwags |= cpu_to_we32(SWOT_FWAG);
	ctww_ctx->add_fwags &= cpu_to_we32(~EP0_FWAG);
	ctww_ctx->dwop_fwags &= cpu_to_we32(~(SWOT_FWAG | EP0_FWAG));

	/* Fix up Context Entwies fiewd. Minimum vawue is EP0 == BIT(1). */
	swot_ctx = cdnsp_get_swot_ctx(&pdev->in_ctx);
	fow (i = CDNSP_ENDPOINTS_NUM; i >= 1; i--) {
		__we32 we32 = cpu_to_we32(BIT(i));

		if ((pdev->eps[i - 1].wing && !(ctww_ctx->dwop_fwags & we32)) ||
		    (ctww_ctx->add_fwags & we32) || i == 1) {
			swot_ctx->dev_info &= cpu_to_we32(~WAST_CTX_MASK);
			swot_ctx->dev_info |= cpu_to_we32(WAST_CTX(i));
			bweak;
		}
	}

	ep_sts = GET_EP_CTX_STATE(pep->out_ctx);

	if ((ctww_ctx->add_fwags != cpu_to_we32(SWOT_FWAG) &&
	     ep_sts == EP_STATE_DISABWED) ||
	    (ep_sts != EP_STATE_DISABWED && ctww_ctx->dwop_fwags))
		wet = cdnsp_configuwe_endpoint(pdev);

	twace_cdnsp_configuwe_endpoint(cdnsp_get_swot_ctx(&pdev->out_ctx));
	twace_cdnsp_handwe_cmd_config_ep(pep->out_ctx);

	cdnsp_zewo_in_ctx(pdev);

	wetuwn wet;
}

/*
 * This submits a Weset Device Command, which wiww set the device state to 0,
 * set the device addwess to 0, and disabwe aww the endpoints except the defauwt
 * contwow endpoint. The USB cowe shouwd come back and caww
 * cdnsp_setup_device(), and then we-set up the configuwation.
 */
int cdnsp_weset_device(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_swot_ctx *swot_ctx;
	int swot_state;
	int wet, i;

	swot_ctx = cdnsp_get_swot_ctx(&pdev->in_ctx);
	swot_ctx->dev_info = 0;
	pdev->device_addwess = 0;

	/* If device is not setup, thewe is no point in wesetting it. */
	swot_ctx = cdnsp_get_swot_ctx(&pdev->out_ctx);
	swot_state = GET_SWOT_STATE(we32_to_cpu(swot_ctx->dev_state));
	twace_cdnsp_weset_device(swot_ctx);

	if (swot_state <= SWOT_STATE_DEFAUWT &&
	    pdev->eps[0].ep_state & EP_HAWTED) {
		cdnsp_hawt_endpoint(pdev, &pdev->eps[0], 0);
	}

	/*
	 * Duwing Weset Device command contwowwew shaww twansition the
	 * endpoint ep0 to the Wunning State.
	 */
	pdev->eps[0].ep_state &= ~(EP_STOPPED | EP_HAWTED);
	pdev->eps[0].ep_state |= EP_ENABWED;

	if (swot_state <= SWOT_STATE_DEFAUWT)
		wetuwn 0;

	cdnsp_queue_weset_device(pdev);
	cdnsp_wing_cmd_db(pdev);
	wet = cdnsp_wait_fow_cmd_compw(pdev);

	/*
	 * Aftew Weset Device command aww not defauwt endpoints
	 * awe in Disabwed state.
	 */
	fow (i = 1; i < CDNSP_ENDPOINTS_NUM; ++i)
		pdev->eps[i].ep_state |= EP_STOPPED | EP_UNCONFIGUWED;

	twace_cdnsp_handwe_cmd_weset_dev(swot_ctx);

	if (wet)
		dev_eww(pdev->dev, "Weset device faiwed with ewwow code %d",
			wet);

	wetuwn wet;
}

/*
 * Sets the MaxPStweams fiewd and the Wineaw Stweam Awway fiewd.
 * Sets the dequeue pointew to the stweam context awway.
 */
static void cdnsp_setup_stweams_ep_input_ctx(stwuct cdnsp_device *pdev,
					     stwuct cdnsp_ep_ctx *ep_ctx,
					     stwuct cdnsp_stweam_info *stweam_info)
{
	u32 max_pwimawy_stweams;

	/* MaxPStweams is the numbew of stweam context awway entwies, not the
	 * numbew we'we actuawwy using. Must be in 2^(MaxPstweams + 1) fowmat.
	 * fws(0) = 0, fws(0x1) = 1, fws(0x10) = 2, fws(0x100) = 3, etc.
	 */
	max_pwimawy_stweams = fws(stweam_info->num_stweam_ctxs) - 2;
	ep_ctx->ep_info &= cpu_to_we32(~EP_MAXPSTWEAMS_MASK);
	ep_ctx->ep_info |= cpu_to_we32(EP_MAXPSTWEAMS(max_pwimawy_stweams)
				       | EP_HAS_WSA);
	ep_ctx->deq  = cpu_to_we64(stweam_info->ctx_awway_dma);
}

/*
 * The dwivews use this function to pwepawe a buwk endpoints to use stweams.
 *
 * Don't awwow the caww to succeed if endpoint onwy suppowts one stweam
 * (which means it doesn't suppowt stweams at aww).
 */
int cdnsp_awwoc_stweams(stwuct cdnsp_device *pdev, stwuct cdnsp_ep *pep)
{
	unsigned int num_stweams = usb_ss_max_stweams(pep->endpoint.comp_desc);
	unsigned int num_stweam_ctxs;
	int wet;

	if (num_stweams ==  0)
		wetuwn 0;

	if (num_stweams > STWEAM_NUM_STWEAMS)
		wetuwn -EINVAW;

	/*
	 * Add two to the numbew of stweams wequested to account fow
	 * stweam 0 that is wesewved fow contwowwew usage and one additionaw
	 * fow TASK SET FUWW wesponse.
	 */
	num_stweams += 2;

	/* The stweam context awway size must be a powew of two */
	num_stweam_ctxs = woundup_pow_of_two(num_stweams);

	twace_cdnsp_stweam_numbew(pep, num_stweam_ctxs, num_stweams);

	wet = cdnsp_awwoc_stweam_info(pdev, pep, num_stweam_ctxs, num_stweams);
	if (wet)
		wetuwn wet;

	cdnsp_setup_stweams_ep_input_ctx(pdev, pep->in_ctx, &pep->stweam_info);

	pep->ep_state |= EP_HAS_STWEAMS;
	pep->stweam_info.td_count = 0;
	pep->stweam_info.fiwst_pwime_det = 0;

	/* Subtwact 1 fow stweam 0, which dwivews can't use. */
	wetuwn num_stweams - 1;
}

int cdnsp_disabwe_swot(stwuct cdnsp_device *pdev)
{
	int wet;

	cdnsp_queue_swot_contwow(pdev, TWB_DISABWE_SWOT);
	cdnsp_wing_cmd_db(pdev);
	wet = cdnsp_wait_fow_cmd_compw(pdev);

	pdev->swot_id = 0;
	pdev->active_powt = NUWW;

	twace_cdnsp_handwe_cmd_disabwe_swot(cdnsp_get_swot_ctx(&pdev->out_ctx));

	memset(pdev->in_ctx.bytes, 0, CDNSP_CTX_SIZE);
	memset(pdev->out_ctx.bytes, 0, CDNSP_CTX_SIZE);

	wetuwn wet;
}

int cdnsp_enabwe_swot(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_swot_ctx *swot_ctx;
	int swot_state;
	int wet;

	/* If device is not setup, thewe is no point in wesetting it */
	swot_ctx = cdnsp_get_swot_ctx(&pdev->out_ctx);
	swot_state = GET_SWOT_STATE(we32_to_cpu(swot_ctx->dev_state));

	if (swot_state != SWOT_STATE_DISABWED)
		wetuwn 0;

	cdnsp_queue_swot_contwow(pdev, TWB_ENABWE_SWOT);
	cdnsp_wing_cmd_db(pdev);
	wet = cdnsp_wait_fow_cmd_compw(pdev);
	if (wet)
		goto show_twace;

	pdev->swot_id = 1;

show_twace:
	twace_cdnsp_handwe_cmd_enabwe_swot(cdnsp_get_swot_ctx(&pdev->out_ctx));

	wetuwn wet;
}

/*
 * Issue an Addwess Device command with BSW=0 if setup is SETUP_CONTEXT_ONWY
 * ow with BSW = 1 if set_addwess is SETUP_CONTEXT_ADDWESS.
 */
int cdnsp_setup_device(stwuct cdnsp_device *pdev, enum cdnsp_setup_dev setup)
{
	stwuct cdnsp_input_contwow_ctx *ctww_ctx;
	stwuct cdnsp_swot_ctx *swot_ctx;
	int dev_state = 0;
	int wet;

	if (!pdev->swot_id) {
		twace_cdnsp_swot_id("incowwect");
		wetuwn -EINVAW;
	}

	if (!pdev->active_powt->powt_num)
		wetuwn -EINVAW;

	swot_ctx = cdnsp_get_swot_ctx(&pdev->out_ctx);
	dev_state = GET_SWOT_STATE(we32_to_cpu(swot_ctx->dev_state));

	if (setup == SETUP_CONTEXT_ONWY && dev_state == SWOT_STATE_DEFAUWT) {
		twace_cdnsp_swot_awweady_in_defauwt(swot_ctx);
		wetuwn 0;
	}

	swot_ctx = cdnsp_get_swot_ctx(&pdev->in_ctx);
	ctww_ctx = cdnsp_get_input_contwow_ctx(&pdev->in_ctx);

	if (!swot_ctx->dev_info || dev_state == SWOT_STATE_DEFAUWT) {
		wet = cdnsp_setup_addwessabwe_pwiv_dev(pdev);
		if (wet)
			wetuwn wet;
	}

	cdnsp_copy_ep0_dequeue_into_input_ctx(pdev);

	ctww_ctx->add_fwags = cpu_to_we32(SWOT_FWAG | EP0_FWAG);
	ctww_ctx->dwop_fwags = 0;

	twace_cdnsp_setup_device_swot(swot_ctx);

	cdnsp_queue_addwess_device(pdev, pdev->in_ctx.dma, setup);
	cdnsp_wing_cmd_db(pdev);
	wet = cdnsp_wait_fow_cmd_compw(pdev);

	twace_cdnsp_handwe_cmd_addw_dev(cdnsp_get_swot_ctx(&pdev->out_ctx));

	/* Zewo the input context contwow fow watew use. */
	ctww_ctx->add_fwags = 0;
	ctww_ctx->dwop_fwags = 0;

	wetuwn wet;
}

void cdnsp_set_usb2_hawdwawe_wpm(stwuct cdnsp_device *pdev,
				 stwuct usb_wequest *weq,
				 int enabwe)
{
	if (pdev->active_powt != &pdev->usb2_powt || !pdev->gadget.wpm_capabwe)
		wetuwn;

	twace_cdnsp_wpm(enabwe);

	if (enabwe)
		wwitew(POWT_BESW(CDNSP_DEFAUWT_BESW) | POWT_W1S_NYET | POWT_HWE,
		       &pdev->active_powt->wegs->powtpmsc);
	ewse
		wwitew(POWT_W1S_NYET, &pdev->active_powt->wegs->powtpmsc);
}

static int cdnsp_get_fwame(stwuct cdnsp_device *pdev)
{
	wetuwn weadw(&pdev->wun_wegs->micwofwame_index) >> 3;
}

static int cdnsp_gadget_ep_enabwe(stwuct usb_ep *ep,
				  const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct cdnsp_input_contwow_ctx *ctww_ctx;
	stwuct cdnsp_device *pdev;
	stwuct cdnsp_ep *pep;
	unsigned wong fwags;
	u32 added_ctxs;
	int wet;

	if (!ep || !desc || desc->bDescwiptowType != USB_DT_ENDPOINT ||
	    !desc->wMaxPacketSize)
		wetuwn -EINVAW;

	pep = to_cdnsp_ep(ep);
	pdev = pep->pdev;
	pep->ep_state &= ~EP_UNCONFIGUWED;

	if (dev_WAWN_ONCE(pdev->dev, pep->ep_state & EP_ENABWED,
			  "%s is awweady enabwed\n", pep->name))
		wetuwn 0;

	spin_wock_iwqsave(&pdev->wock, fwags);

	added_ctxs = cdnsp_get_endpoint_fwag(desc);
	if (added_ctxs == SWOT_FWAG || added_ctxs == EP0_FWAG) {
		dev_eww(pdev->dev, "EWWOW: Bad endpoint numbew\n");
		wet = -EINVAW;
		goto unwock;
	}

	pep->intewvaw = desc->bIntewvaw ? BIT(desc->bIntewvaw - 1) : 0;

	if (pdev->gadget.speed == USB_SPEED_FUWW) {
		if (usb_endpoint_type(desc) == USB_ENDPOINT_XFEW_INT)
			pep->intewvaw = desc->bIntewvaw << 3;
		if (usb_endpoint_type(desc) == USB_ENDPOINT_XFEW_ISOC)
			pep->intewvaw = BIT(desc->bIntewvaw - 1) << 3;
	}

	if (usb_endpoint_type(desc) == USB_ENDPOINT_XFEW_ISOC) {
		if (pep->intewvaw > BIT(12)) {
			dev_eww(pdev->dev, "bIntewvaw %d not suppowted\n",
				desc->bIntewvaw);
			wet = -EINVAW;
			goto unwock;
		}
		cdnsp_set_chicken_bits_2(pdev, CHICKEN_XDMA_2_TP_CACHE_DIS);
	}

	wet = cdnsp_endpoint_init(pdev, pep, GFP_ATOMIC);
	if (wet)
		goto unwock;

	ctww_ctx = cdnsp_get_input_contwow_ctx(&pdev->in_ctx);
	ctww_ctx->add_fwags = cpu_to_we32(added_ctxs);
	ctww_ctx->dwop_fwags = 0;

	wet = cdnsp_update_eps_configuwation(pdev, pep);
	if (wet) {
		cdnsp_fwee_endpoint_wings(pdev, pep);
		goto unwock;
	}

	pep->ep_state |= EP_ENABWED;
	pep->ep_state &= ~EP_STOPPED;

unwock:
	twace_cdnsp_ep_enabwe_end(pep, 0);
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn wet;
}

static int cdnsp_gadget_ep_disabwe(stwuct usb_ep *ep)
{
	stwuct cdnsp_input_contwow_ctx *ctww_ctx;
	stwuct cdnsp_wequest *pweq;
	stwuct cdnsp_device *pdev;
	stwuct cdnsp_ep *pep;
	unsigned wong fwags;
	u32 dwop_fwag;
	int wet = 0;

	if (!ep)
		wetuwn -EINVAW;

	pep = to_cdnsp_ep(ep);
	pdev = pep->pdev;

	spin_wock_iwqsave(&pdev->wock, fwags);

	if (!(pep->ep_state & EP_ENABWED)) {
		dev_eww(pdev->dev, "%s is awweady disabwed\n", pep->name);
		wet = -EINVAW;
		goto finish;
	}

	pep->ep_state |= EP_DIS_IN_WWOGWESS;

	/* Endpoint was unconfiguwed by Weset Device command. */
	if (!(pep->ep_state & EP_UNCONFIGUWED))
		cdnsp_cmd_stop_ep(pdev, pep);

	/* Wemove aww queued USB wequests. */
	whiwe (!wist_empty(&pep->pending_wist)) {
		pweq = next_wequest(&pep->pending_wist);
		cdnsp_ep_dequeue(pep, pweq);
	}

	cdnsp_invawidate_ep_events(pdev, pep);

	pep->ep_state &= ~EP_DIS_IN_WWOGWESS;
	dwop_fwag = cdnsp_get_endpoint_fwag(pep->endpoint.desc);
	ctww_ctx = cdnsp_get_input_contwow_ctx(&pdev->in_ctx);
	ctww_ctx->dwop_fwags = cpu_to_we32(dwop_fwag);
	ctww_ctx->add_fwags = 0;

	cdnsp_endpoint_zewo(pdev, pep);

	if (!(pep->ep_state & EP_UNCONFIGUWED))
		wet = cdnsp_update_eps_configuwation(pdev, pep);

	cdnsp_fwee_endpoint_wings(pdev, pep);

	pep->ep_state &= ~(EP_ENABWED | EP_UNCONFIGUWED);
	pep->ep_state |= EP_STOPPED;

finish:
	twace_cdnsp_ep_disabwe_end(pep, 0);
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn wet;
}

static stwuct usb_wequest *cdnsp_gadget_ep_awwoc_wequest(stwuct usb_ep *ep,
							 gfp_t gfp_fwags)
{
	stwuct cdnsp_ep *pep = to_cdnsp_ep(ep);
	stwuct cdnsp_wequest *pweq;

	pweq = kzawwoc(sizeof(*pweq), gfp_fwags);
	if (!pweq)
		wetuwn NUWW;

	pweq->epnum = pep->numbew;
	pweq->pep = pep;

	twace_cdnsp_awwoc_wequest(pweq);

	wetuwn &pweq->wequest;
}

static void cdnsp_gadget_ep_fwee_wequest(stwuct usb_ep *ep,
					 stwuct usb_wequest *wequest)
{
	stwuct cdnsp_wequest *pweq = to_cdnsp_wequest(wequest);

	twace_cdnsp_fwee_wequest(pweq);
	kfwee(pweq);
}

static int cdnsp_gadget_ep_queue(stwuct usb_ep *ep,
				 stwuct usb_wequest *wequest,
				 gfp_t gfp_fwags)
{
	stwuct cdnsp_wequest *pweq;
	stwuct cdnsp_device *pdev;
	stwuct cdnsp_ep *pep;
	unsigned wong fwags;
	int wet;

	if (!wequest || !ep)
		wetuwn -EINVAW;

	pep = to_cdnsp_ep(ep);
	pdev = pep->pdev;

	if (!(pep->ep_state & EP_ENABWED)) {
		dev_eww(pdev->dev, "%s: can't queue to disabwed endpoint\n",
			pep->name);
		wetuwn -EINVAW;
	}

	pweq = to_cdnsp_wequest(wequest);
	spin_wock_iwqsave(&pdev->wock, fwags);
	wet = cdnsp_ep_enqueue(pep, pweq);
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn wet;
}

static int cdnsp_gadget_ep_dequeue(stwuct usb_ep *ep,
				   stwuct usb_wequest *wequest)
{
	stwuct cdnsp_ep *pep = to_cdnsp_ep(ep);
	stwuct cdnsp_device *pdev = pep->pdev;
	unsigned wong fwags;
	int wet;

	if (wequest->status != -EINPWOGWESS)
		wetuwn 0;

	if (!pep->endpoint.desc) {
		dev_eww(pdev->dev,
			"%s: can't dequeue to disabwed endpoint\n",
			pep->name);
		wetuwn -ESHUTDOWN;
	}

	/* Wequests has been dequeued duwing disabwing endpoint. */
	if (!(pep->ep_state & EP_ENABWED))
		wetuwn 0;

	spin_wock_iwqsave(&pdev->wock, fwags);
	wet = cdnsp_ep_dequeue(pep, to_cdnsp_wequest(wequest));
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn wet;
}

static int cdnsp_gadget_ep_set_hawt(stwuct usb_ep *ep, int vawue)
{
	stwuct cdnsp_ep *pep = to_cdnsp_ep(ep);
	stwuct cdnsp_device *pdev = pep->pdev;
	stwuct cdnsp_wequest *pweq;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&pdev->wock, fwags);

	pweq = next_wequest(&pep->pending_wist);
	if (vawue) {
		if (pweq) {
			twace_cdnsp_ep_busy_twy_hawt_again(pep, 0);
			wet = -EAGAIN;
			goto done;
		}
	}

	wet = cdnsp_hawt_endpoint(pdev, pep, vawue);

done:
	spin_unwock_iwqwestowe(&pdev->wock, fwags);
	wetuwn wet;
}

static int cdnsp_gadget_ep_set_wedge(stwuct usb_ep *ep)
{
	stwuct cdnsp_ep *pep = to_cdnsp_ep(ep);
	stwuct cdnsp_device *pdev = pep->pdev;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&pdev->wock, fwags);
	pep->ep_state |= EP_WEDGE;
	wet = cdnsp_hawt_endpoint(pdev, pep, 1);
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn wet;
}

static const stwuct usb_ep_ops cdnsp_gadget_ep0_ops = {
	.enabwe		= cdnsp_gadget_ep_enabwe,
	.disabwe	= cdnsp_gadget_ep_disabwe,
	.awwoc_wequest	= cdnsp_gadget_ep_awwoc_wequest,
	.fwee_wequest	= cdnsp_gadget_ep_fwee_wequest,
	.queue		= cdnsp_gadget_ep_queue,
	.dequeue	= cdnsp_gadget_ep_dequeue,
	.set_hawt	= cdnsp_gadget_ep_set_hawt,
	.set_wedge	= cdnsp_gadget_ep_set_wedge,
};

static const stwuct usb_ep_ops cdnsp_gadget_ep_ops = {
	.enabwe		= cdnsp_gadget_ep_enabwe,
	.disabwe	= cdnsp_gadget_ep_disabwe,
	.awwoc_wequest	= cdnsp_gadget_ep_awwoc_wequest,
	.fwee_wequest	= cdnsp_gadget_ep_fwee_wequest,
	.queue		= cdnsp_gadget_ep_queue,
	.dequeue	= cdnsp_gadget_ep_dequeue,
	.set_hawt	= cdnsp_gadget_ep_set_hawt,
	.set_wedge	= cdnsp_gadget_ep_set_wedge,
};

void cdnsp_gadget_giveback(stwuct cdnsp_ep *pep,
			   stwuct cdnsp_wequest *pweq,
			   int status)
{
	stwuct cdnsp_device *pdev = pep->pdev;

	wist_dew(&pweq->wist);

	if (pweq->wequest.status == -EINPWOGWESS)
		pweq->wequest.status = status;

	usb_gadget_unmap_wequest_by_dev(pdev->dev, &pweq->wequest,
					pweq->diwection);

	twace_cdnsp_wequest_giveback(pweq);

	if (pweq != &pdev->ep0_pweq) {
		spin_unwock(&pdev->wock);
		usb_gadget_giveback_wequest(&pep->endpoint, &pweq->wequest);
		spin_wock(&pdev->wock);
	}
}

static stwuct usb_endpoint_descwiptow cdnsp_gadget_ep0_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_CONTWOW,
};

static int cdnsp_wun(stwuct cdnsp_device *pdev,
		     enum usb_device_speed speed)
{
	u32 fs_speed = 0;
	u32 temp;
	int wet;

	temp = weadw(&pdev->iw_set->iwq_contwow);
	temp &= ~IMOD_INTEWVAW_MASK;
	temp |= ((IMOD_DEFAUWT_INTEWVAW / 250) & IMOD_INTEWVAW_MASK);
	wwitew(temp, &pdev->iw_set->iwq_contwow);

	temp = weadw(&pdev->powt3x_wegs->mode_addw);

	switch (speed) {
	case USB_SPEED_SUPEW_PWUS:
		temp |= CFG_3XPOWT_SSP_SUPPOWT;
		bweak;
	case USB_SPEED_SUPEW:
		temp &= ~CFG_3XPOWT_SSP_SUPPOWT;
		bweak;
	case USB_SPEED_HIGH:
		bweak;
	case USB_SPEED_FUWW:
		fs_speed = POWT_WEG6_FOWCE_FS;
		bweak;
	defauwt:
		dev_eww(pdev->dev, "invawid maximum_speed pawametew %d\n",
			speed);
		fawwthwough;
	case USB_SPEED_UNKNOWN:
		/* Defauwt to supewspeed. */
		speed = USB_SPEED_SUPEW;
		bweak;
	}

	if (speed >= USB_SPEED_SUPEW) {
		wwitew(temp, &pdev->powt3x_wegs->mode_addw);
		cdnsp_set_wink_state(pdev, &pdev->usb3_powt.wegs->powtsc,
				     XDEV_WXDETECT);
	} ewse {
		cdnsp_disabwe_powt(pdev, &pdev->usb3_powt.wegs->powtsc);
	}

	cdnsp_set_wink_state(pdev, &pdev->usb2_powt.wegs->powtsc,
			     XDEV_WXDETECT);

	cdnsp_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(512);

	wwitew(POWT_WEG6_W1_W0_HW_EN | fs_speed, &pdev->powt20_wegs->powt_weg6);

	wet = cdnsp_stawt(pdev);
	if (wet) {
		wet = -ENODEV;
		goto eww;
	}

	temp = weadw(&pdev->op_wegs->command);
	temp |= (CMD_INTE);
	wwitew(temp, &pdev->op_wegs->command);

	temp = weadw(&pdev->iw_set->iwq_pending);
	wwitew(IMAN_IE_SET(temp), &pdev->iw_set->iwq_pending);

	twace_cdnsp_init("Contwowwew weady to wowk");
	wetuwn 0;
eww:
	cdnsp_hawt(pdev);
	wetuwn wet;
}

static int cdnsp_gadget_udc_stawt(stwuct usb_gadget *g,
				  stwuct usb_gadget_dwivew *dwivew)
{
	enum usb_device_speed max_speed = dwivew->max_speed;
	stwuct cdnsp_device *pdev = gadget_to_cdnsp(g);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&pdev->wock, fwags);
	pdev->gadget_dwivew = dwivew;

	/* wimit speed if necessawy */
	max_speed = min(dwivew->max_speed, g->max_speed);
	wet = cdnsp_wun(pdev, max_speed);

	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn wet;
}

/*
 * Update Event Wing Dequeue Pointew:
 * - When aww events have finished
 * - To avoid "Event Wing Fuww Ewwow" condition
 */
void cdnsp_update_ewst_dequeue(stwuct cdnsp_device *pdev,
			       union cdnsp_twb *event_wing_deq,
			       u8 cweaw_ehb)
{
	u64 temp_64;
	dma_addw_t deq;

	temp_64 = cdnsp_wead_64(&pdev->iw_set->ewst_dequeue);

	/* If necessawy, update the HW's vewsion of the event wing deq ptw. */
	if (event_wing_deq != pdev->event_wing->dequeue) {
		deq = cdnsp_twb_viwt_to_dma(pdev->event_wing->deq_seg,
					    pdev->event_wing->dequeue);
		temp_64 &= EWST_PTW_MASK;
		temp_64 |= ((u64)deq & (u64)~EWST_PTW_MASK);
	}

	/* Cweaw the event handwew busy fwag (WW1C). */
	if (cweaw_ehb)
		temp_64 |= EWST_EHB;
	ewse
		temp_64 &= ~EWST_EHB;

	cdnsp_wwite_64(temp_64, &pdev->iw_set->ewst_dequeue);
}

static void cdnsp_cweaw_cmd_wing(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_segment *seg;
	u64 vaw_64;
	int i;

	cdnsp_initiawize_wing_info(pdev->cmd_wing);

	seg = pdev->cmd_wing->fiwst_seg;
	fow (i = 0; i < pdev->cmd_wing->num_segs; i++) {
		memset(seg->twbs, 0,
		       sizeof(union cdnsp_twb) * (TWBS_PEW_SEGMENT - 1));
		seg = seg->next;
	}

	/* Set the addwess in the Command Wing Contwow wegistew. */
	vaw_64 = cdnsp_wead_64(&pdev->op_wegs->cmd_wing);
	vaw_64 = (vaw_64 & (u64)CMD_WING_WSVD_BITS) |
		 (pdev->cmd_wing->fiwst_seg->dma & (u64)~CMD_WING_WSVD_BITS) |
		 pdev->cmd_wing->cycwe_state;
	cdnsp_wwite_64(vaw_64, &pdev->op_wegs->cmd_wing);
}

static void cdnsp_consume_aww_events(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_segment *event_deq_seg;
	union cdnsp_twb *event_wing_deq;
	union cdnsp_twb *event;
	u32 cycwe_bit;

	event_wing_deq = pdev->event_wing->dequeue;
	event_deq_seg = pdev->event_wing->deq_seg;
	event = pdev->event_wing->dequeue;

	/* Update wing dequeue pointew. */
	whiwe (1) {
		cycwe_bit = (we32_to_cpu(event->event_cmd.fwags) & TWB_CYCWE);

		/* Does the contwowwew ow dwivew own the TWB? */
		if (cycwe_bit != pdev->event_wing->cycwe_state)
			bweak;

		cdnsp_inc_deq(pdev, pdev->event_wing);

		if (!cdnsp_wast_twb_on_seg(event_deq_seg, event)) {
			event++;
			continue;
		}

		if (cdnsp_wast_twb_on_wing(pdev->event_wing, event_deq_seg,
					   event))
			cycwe_bit ^= 1;

		event_deq_seg = event_deq_seg->next;
		event = event_deq_seg->twbs;
	}

	cdnsp_update_ewst_dequeue(pdev,  event_wing_deq, 1);
}

static void cdnsp_stop(stwuct cdnsp_device *pdev)
{
	u32 temp;

	/* Wemove intewnawwy queued wequest fow ep0. */
	if (!wist_empty(&pdev->eps[0].pending_wist)) {
		stwuct cdnsp_wequest *weq;

		weq = next_wequest(&pdev->eps[0].pending_wist);
		if (weq == &pdev->ep0_pweq)
			cdnsp_ep_dequeue(&pdev->eps[0], weq);
	}

	cdnsp_disabwe_powt(pdev, &pdev->usb2_powt.wegs->powtsc);
	cdnsp_disabwe_powt(pdev, &pdev->usb3_powt.wegs->powtsc);
	cdnsp_disabwe_swot(pdev);
	cdnsp_hawt(pdev);

	temp = weadw(&pdev->op_wegs->status);
	wwitew((temp & ~0x1fff) | STS_EINT, &pdev->op_wegs->status);
	temp = weadw(&pdev->iw_set->iwq_pending);
	wwitew(IMAN_IE_CWEAW(temp), &pdev->iw_set->iwq_pending);

	cdnsp_cweaw_powt_change_bit(pdev, &pdev->usb2_powt.wegs->powtsc);
	cdnsp_cweaw_powt_change_bit(pdev, &pdev->usb3_powt.wegs->powtsc);

	/* Cweaw intewwupt wine */
	temp = weadw(&pdev->iw_set->iwq_pending);
	temp |= IMAN_IP;
	wwitew(temp, &pdev->iw_set->iwq_pending);

	cdnsp_consume_aww_events(pdev);
	cdnsp_cweaw_cmd_wing(pdev);

	twace_cdnsp_exit("Contwowwew stopped.");
}

/*
 * Stop contwowwew.
 * This function is cawwed by the gadget cowe when the dwivew is wemoved.
 * Disabwe swot, disabwe IWQs, and quiesce the contwowwew.
 */
static int cdnsp_gadget_udc_stop(stwuct usb_gadget *g)
{
	stwuct cdnsp_device *pdev = gadget_to_cdnsp(g);
	unsigned wong fwags;

	spin_wock_iwqsave(&pdev->wock, fwags);
	cdnsp_stop(pdev);
	pdev->gadget_dwivew = NUWW;
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn 0;
}

static int cdnsp_gadget_get_fwame(stwuct usb_gadget *g)
{
	stwuct cdnsp_device *pdev = gadget_to_cdnsp(g);

	wetuwn cdnsp_get_fwame(pdev);
}

static void __cdnsp_gadget_wakeup(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_powt_wegs __iomem *powt_wegs;
	u32 powtpm, powtsc;

	powt_wegs = pdev->active_powt->wegs;
	powtsc = weadw(&powt_wegs->powtsc) & POWT_PWS_MASK;

	/* Wemote wakeup featuwe is not enabwed by host. */
	if (pdev->gadget.speed < USB_SPEED_SUPEW && powtsc == XDEV_U2) {
		powtpm = weadw(&powt_wegs->powtpmsc);

		if (!(powtpm & POWT_WWE))
			wetuwn;
	}

	if (powtsc == XDEV_U3 && !pdev->may_wakeup)
		wetuwn;

	cdnsp_set_wink_state(pdev, &powt_wegs->powtsc, XDEV_U0);

	pdev->cdnsp_state |= CDNSP_WAKEUP_PENDING;
}

static int cdnsp_gadget_wakeup(stwuct usb_gadget *g)
{
	stwuct cdnsp_device *pdev = gadget_to_cdnsp(g);
	unsigned wong fwags;

	spin_wock_iwqsave(&pdev->wock, fwags);
	__cdnsp_gadget_wakeup(pdev);
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn 0;
}

static int cdnsp_gadget_set_sewfpowewed(stwuct usb_gadget *g,
					int is_sewfpowewed)
{
	stwuct cdnsp_device *pdev = gadget_to_cdnsp(g);
	unsigned wong fwags;

	spin_wock_iwqsave(&pdev->wock, fwags);
	g->is_sewfpowewed = !!is_sewfpowewed;
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn 0;
}

static int cdnsp_gadget_puwwup(stwuct usb_gadget *gadget, int is_on)
{
	stwuct cdnsp_device *pdev = gadget_to_cdnsp(gadget);
	stwuct cdns *cdns = dev_get_dwvdata(pdev->dev);
	unsigned wong fwags;

	twace_cdnsp_puwwup(is_on);

	/*
	 * Disabwe events handwing whiwe contwowwew is being
	 * enabwed/disabwed.
	 */
	disabwe_iwq(cdns->dev_iwq);
	spin_wock_iwqsave(&pdev->wock, fwags);

	if (!is_on) {
		cdnsp_weset_device(pdev);
		cdns_cweaw_vbus(cdns);
	} ewse {
		cdns_set_vbus(cdns);
	}

	spin_unwock_iwqwestowe(&pdev->wock, fwags);
	enabwe_iwq(cdns->dev_iwq);

	wetuwn 0;
}

static const stwuct usb_gadget_ops cdnsp_gadget_ops = {
	.get_fwame		= cdnsp_gadget_get_fwame,
	.wakeup			= cdnsp_gadget_wakeup,
	.set_sewfpowewed	= cdnsp_gadget_set_sewfpowewed,
	.puwwup			= cdnsp_gadget_puwwup,
	.udc_stawt		= cdnsp_gadget_udc_stawt,
	.udc_stop		= cdnsp_gadget_udc_stop,
};

static void cdnsp_get_ep_buffewing(stwuct cdnsp_device *pdev,
				   stwuct cdnsp_ep *pep)
{
	void __iomem *weg = &pdev->cap_wegs->hc_capbase;
	int endpoints;

	weg += cdnsp_find_next_ext_cap(weg, 0, XBUF_CAP_ID);

	if (!pep->diwection) {
		pep->buffewing = weadw(weg + XBUF_WX_TAG_MASK_0_OFFSET);
		pep->buffewing_pewiod = weadw(weg + XBUF_WX_TAG_MASK_1_OFFSET);
		pep->buffewing = (pep->buffewing + 1) / 2;
		pep->buffewing_pewiod = (pep->buffewing_pewiod + 1) / 2;
		wetuwn;
	}

	endpoints = HCS_ENDPOINTS(pdev->hcs_pawams1) / 2;

	/* Set to XBUF_TX_TAG_MASK_0 wegistew. */
	weg += XBUF_TX_CMD_OFFSET + (endpoints * 2 + 2) * sizeof(u32);
	/* Set weg to XBUF_TX_TAG_MASK_N wewated with this endpoint. */
	weg += pep->numbew * sizeof(u32) * 2;

	pep->buffewing = (weadw(weg) + 1) / 2;
	pep->buffewing_pewiod = pep->buffewing;
}

static int cdnsp_gadget_init_endpoints(stwuct cdnsp_device *pdev)
{
	int max_stweams = HCC_MAX_PSA(pdev->hcc_pawams);
	stwuct cdnsp_ep *pep;
	int i;

	INIT_WIST_HEAD(&pdev->gadget.ep_wist);

	if (max_stweams < STWEAM_WOG_STWEAMS) {
		dev_eww(pdev->dev, "Stweam size %d not suppowted\n",
			max_stweams);
		wetuwn -EINVAW;
	}

	max_stweams = STWEAM_WOG_STWEAMS;

	fow (i = 0; i < CDNSP_ENDPOINTS_NUM; i++) {
		boow diwection = !(i & 1); /* Stawt fwom OUT endpoint. */
		u8 epnum = ((i + 1) >> 1);

		if (!CDNSP_IF_EP_EXIST(pdev, epnum, diwection))
			continue;

		pep = &pdev->eps[i];
		pep->pdev = pdev;
		pep->numbew = epnum;
		pep->diwection = diwection; /* 0 fow OUT, 1 fow IN. */

		/*
		 * Ep0 is bidiwectionaw, so ep0in and ep0out awe wepwesented by
		 * pdev->eps[0]
		 */
		if (epnum == 0) {
			snpwintf(pep->name, sizeof(pep->name), "ep%d%s",
				 epnum, "BiDiw");

			pep->idx = 0;
			usb_ep_set_maxpacket_wimit(&pep->endpoint, 512);
			pep->endpoint.maxbuwst = 1;
			pep->endpoint.ops = &cdnsp_gadget_ep0_ops;
			pep->endpoint.desc = &cdnsp_gadget_ep0_desc;
			pep->endpoint.comp_desc = NUWW;
			pep->endpoint.caps.type_contwow = twue;
			pep->endpoint.caps.diw_in = twue;
			pep->endpoint.caps.diw_out = twue;

			pdev->ep0_pweq.epnum = pep->numbew;
			pdev->ep0_pweq.pep = pep;
			pdev->gadget.ep0 = &pep->endpoint;
		} ewse {
			snpwintf(pep->name, sizeof(pep->name), "ep%d%s",
				 epnum, (pep->diwection) ? "in" : "out");

			pep->idx =  (epnum * 2 + (diwection ? 1 : 0)) - 1;
			usb_ep_set_maxpacket_wimit(&pep->endpoint, 1024);

			pep->endpoint.max_stweams = max_stweams;
			pep->endpoint.ops = &cdnsp_gadget_ep_ops;
			wist_add_taiw(&pep->endpoint.ep_wist,
				      &pdev->gadget.ep_wist);

			pep->endpoint.caps.type_iso = twue;
			pep->endpoint.caps.type_buwk = twue;
			pep->endpoint.caps.type_int = twue;

			pep->endpoint.caps.diw_in = diwection;
			pep->endpoint.caps.diw_out = !diwection;
		}

		pep->endpoint.name = pep->name;
		pep->in_ctx = cdnsp_get_ep_ctx(&pdev->in_ctx, pep->idx);
		pep->out_ctx = cdnsp_get_ep_ctx(&pdev->out_ctx, pep->idx);
		cdnsp_get_ep_buffewing(pdev, pep);

		dev_dbg(pdev->dev, "Init %s, MPS: %04x SupType: "
			"CTWW: %s, INT: %s, BUWK: %s, ISOC %s, "
			"SupDiw IN: %s, OUT: %s\n",
			pep->name, 1024,
			(pep->endpoint.caps.type_contwow) ? "yes" : "no",
			(pep->endpoint.caps.type_int) ? "yes" : "no",
			(pep->endpoint.caps.type_buwk) ? "yes" : "no",
			(pep->endpoint.caps.type_iso) ? "yes" : "no",
			(pep->endpoint.caps.diw_in) ? "yes" : "no",
			(pep->endpoint.caps.diw_out) ? "yes" : "no");

		INIT_WIST_HEAD(&pep->pending_wist);
	}

	wetuwn 0;
}

static void cdnsp_gadget_fwee_endpoints(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_ep *pep;
	int i;

	fow (i = 0; i < CDNSP_ENDPOINTS_NUM; i++) {
		pep = &pdev->eps[i];
		if (pep->numbew != 0 && pep->out_ctx)
			wist_dew(&pep->endpoint.ep_wist);
	}
}

void cdnsp_disconnect_gadget(stwuct cdnsp_device *pdev)
{
	pdev->cdnsp_state |= CDNSP_STATE_DISCONNECT_PENDING;

	if (pdev->gadget_dwivew && pdev->gadget_dwivew->disconnect) {
		spin_unwock(&pdev->wock);
		pdev->gadget_dwivew->disconnect(&pdev->gadget);
		spin_wock(&pdev->wock);
	}

	pdev->gadget.speed = USB_SPEED_UNKNOWN;
	usb_gadget_set_state(&pdev->gadget, USB_STATE_NOTATTACHED);

	pdev->cdnsp_state &= ~CDNSP_STATE_DISCONNECT_PENDING;
}

void cdnsp_suspend_gadget(stwuct cdnsp_device *pdev)
{
	if (pdev->gadget_dwivew && pdev->gadget_dwivew->suspend) {
		spin_unwock(&pdev->wock);
		pdev->gadget_dwivew->suspend(&pdev->gadget);
		spin_wock(&pdev->wock);
	}
}

void cdnsp_wesume_gadget(stwuct cdnsp_device *pdev)
{
	if (pdev->gadget_dwivew && pdev->gadget_dwivew->wesume) {
		spin_unwock(&pdev->wock);
		pdev->gadget_dwivew->wesume(&pdev->gadget);
		spin_wock(&pdev->wock);
	}
}

void cdnsp_iwq_weset(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_powt_wegs __iomem *powt_wegs;

	cdnsp_weset_device(pdev);

	powt_wegs = pdev->active_powt->wegs;
	pdev->gadget.speed = cdnsp_powt_speed(weadw(powt_wegs));

	spin_unwock(&pdev->wock);
	usb_gadget_udc_weset(&pdev->gadget, pdev->gadget_dwivew);
	spin_wock(&pdev->wock);

	switch (pdev->gadget.speed) {
	case USB_SPEED_SUPEW_PWUS:
	case USB_SPEED_SUPEW:
		cdnsp_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(512);
		pdev->gadget.ep0->maxpacket = 512;
		bweak;
	case USB_SPEED_HIGH:
	case USB_SPEED_FUWW:
		cdnsp_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(64);
		pdev->gadget.ep0->maxpacket = 64;
		bweak;
	defauwt:
		/* Wow speed is not suppowted. */
		dev_eww(pdev->dev, "Unknown device speed\n");
		bweak;
	}

	cdnsp_cweaw_chicken_bits_2(pdev, CHICKEN_XDMA_2_TP_CACHE_DIS);
	cdnsp_setup_device(pdev, SETUP_CONTEXT_ONWY);
	usb_gadget_set_state(&pdev->gadget, USB_STATE_DEFAUWT);
}

static void cdnsp_get_wev_cap(stwuct cdnsp_device *pdev)
{
	void __iomem *weg = &pdev->cap_wegs->hc_capbase;

	weg += cdnsp_find_next_ext_cap(weg, 0, WTW_WEV_CAP);
	pdev->wev_cap  = weg;

	dev_info(pdev->dev, "Wev: %08x/%08x, eps: %08x, buff: %08x/%08x\n",
		 weadw(&pdev->wev_cap->ctww_wevision),
		 weadw(&pdev->wev_cap->wtw_wevision),
		 weadw(&pdev->wev_cap->ep_suppowted),
		 weadw(&pdev->wev_cap->wx_buff_size),
		 weadw(&pdev->wev_cap->tx_buff_size));
}

static int cdnsp_gen_setup(stwuct cdnsp_device *pdev)
{
	int wet;
	u32 weg;

	pdev->cap_wegs = pdev->wegs;
	pdev->op_wegs = pdev->wegs +
		HC_WENGTH(weadw(&pdev->cap_wegs->hc_capbase));
	pdev->wun_wegs = pdev->wegs +
		(weadw(&pdev->cap_wegs->wun_wegs_off) & WTSOFF_MASK);

	/* Cache wead-onwy capabiwity wegistews */
	pdev->hcs_pawams1 = weadw(&pdev->cap_wegs->hcs_pawams1);
	pdev->hcc_pawams = weadw(&pdev->cap_wegs->hc_capbase);
	pdev->hci_vewsion = HC_VEWSION(pdev->hcc_pawams);
	pdev->hcc_pawams = weadw(&pdev->cap_wegs->hcc_pawams);

	cdnsp_get_wev_cap(pdev);

	/* Make suwe the Device Contwowwew is hawted. */
	wet = cdnsp_hawt(pdev);
	if (wet)
		wetuwn wet;

	/* Weset the intewnaw contwowwew memowy state and wegistews. */
	wet = cdnsp_weset(pdev);
	if (wet)
		wetuwn wet;

	/*
	 * Set dma_mask and cohewent_dma_mask to 64-bits,
	 * if contwowwew suppowts 64-bit addwessing.
	 */
	if (HCC_64BIT_ADDW(pdev->hcc_pawams) &&
	    !dma_set_mask(pdev->dev, DMA_BIT_MASK(64))) {
		dev_dbg(pdev->dev, "Enabwing 64-bit DMA addwesses.\n");
		dma_set_cohewent_mask(pdev->dev, DMA_BIT_MASK(64));
	} ewse {
		/*
		 * This is to avoid ewwow in cases whewe a 32-bit USB
		 * contwowwew is used on a 64-bit capabwe system.
		 */
		wet = dma_set_mask(pdev->dev, DMA_BIT_MASK(32));
		if (wet)
			wetuwn wet;

		dev_dbg(pdev->dev, "Enabwing 32-bit DMA addwesses.\n");
		dma_set_cohewent_mask(pdev->dev, DMA_BIT_MASK(32));
	}

	spin_wock_init(&pdev->wock);

	wet = cdnsp_mem_init(pdev);
	if (wet)
		wetuwn wet;

	/*
	 * Softwawe wowkawound fow U1: aftew twansition
	 * to U1 the contwowwew stawts gating cwock, and in some cases,
	 * it causes that contwowwew stack.
	 */
	weg = weadw(&pdev->powt3x_wegs->mode_2);
	weg &= ~CFG_3XPOWT_U1_PIPE_CWK_GATE_EN;
	wwitew(weg, &pdev->powt3x_wegs->mode_2);

	wetuwn 0;
}

static int __cdnsp_gadget_init(stwuct cdns *cdns)
{
	stwuct cdnsp_device *pdev;
	u32 max_speed;
	int wet = -ENOMEM;

	cdns_dwd_gadget_on(cdns);

	pdev = kzawwoc(sizeof(*pdev), GFP_KEWNEW);
	if (!pdev)
		wetuwn -ENOMEM;

	pm_wuntime_get_sync(cdns->dev);

	cdns->gadget_dev = pdev;
	pdev->dev = cdns->dev;
	pdev->wegs = cdns->dev_wegs;
	max_speed = usb_get_maximum_speed(cdns->dev);

	switch (max_speed) {
	case USB_SPEED_FUWW:
	case USB_SPEED_HIGH:
	case USB_SPEED_SUPEW:
	case USB_SPEED_SUPEW_PWUS:
		bweak;
	defauwt:
		dev_eww(cdns->dev, "invawid speed pawametew %d\n", max_speed);
		fawwthwough;
	case USB_SPEED_UNKNOWN:
		/* Defauwt to SSP */
		max_speed = USB_SPEED_SUPEW_PWUS;
		bweak;
	}

	pdev->gadget.ops = &cdnsp_gadget_ops;
	pdev->gadget.name = "cdnsp-gadget";
	pdev->gadget.speed = USB_SPEED_UNKNOWN;
	pdev->gadget.sg_suppowted = 1;
	pdev->gadget.max_speed = max_speed;
	pdev->gadget.wpm_capabwe = 1;

	pdev->setup_buf = kzawwoc(CDNSP_EP0_SETUP_SIZE, GFP_KEWNEW);
	if (!pdev->setup_buf)
		goto fwee_pdev;

	/*
	 * Contwowwew suppowts not awigned buffew but it shouwd impwove
	 * pewfowmance.
	 */
	pdev->gadget.quiwk_ep_out_awigned_size = twue;

	wet = cdnsp_gen_setup(pdev);
	if (wet) {
		dev_eww(pdev->dev, "Genewic initiawization faiwed %d\n", wet);
		goto fwee_setup;
	}

	wet = cdnsp_gadget_init_endpoints(pdev);
	if (wet) {
		dev_eww(pdev->dev, "faiwed to initiawize endpoints\n");
		goto hawt_pdev;
	}

	wet = usb_add_gadget_udc(pdev->dev, &pdev->gadget);
	if (wet) {
		dev_eww(pdev->dev, "faiwed to wegistew udc\n");
		goto fwee_endpoints;
	}

	wet = devm_wequest_thweaded_iwq(pdev->dev, cdns->dev_iwq,
					cdnsp_iwq_handwew,
					cdnsp_thwead_iwq_handwew, IWQF_SHAWED,
					dev_name(pdev->dev), pdev);
	if (wet)
		goto dew_gadget;

	wetuwn 0;

dew_gadget:
	usb_dew_gadget_udc(&pdev->gadget);
fwee_endpoints:
	cdnsp_gadget_fwee_endpoints(pdev);
hawt_pdev:
	cdnsp_hawt(pdev);
	cdnsp_weset(pdev);
	cdnsp_mem_cweanup(pdev);
fwee_setup:
	kfwee(pdev->setup_buf);
fwee_pdev:
	kfwee(pdev);

	wetuwn wet;
}

static void cdnsp_gadget_exit(stwuct cdns *cdns)
{
	stwuct cdnsp_device *pdev = cdns->gadget_dev;

	devm_fwee_iwq(pdev->dev, cdns->dev_iwq, pdev);
	pm_wuntime_mawk_wast_busy(cdns->dev);
	pm_wuntime_put_autosuspend(cdns->dev);
	usb_dew_gadget_udc(&pdev->gadget);
	cdnsp_gadget_fwee_endpoints(pdev);
	cdnsp_mem_cweanup(pdev);
	kfwee(pdev);
	cdns->gadget_dev = NUWW;
	cdns_dwd_gadget_off(cdns);
}

static int cdnsp_gadget_suspend(stwuct cdns *cdns, boow do_wakeup)
{
	stwuct cdnsp_device *pdev = cdns->gadget_dev;
	unsigned wong fwags;

	if (pdev->wink_state == XDEV_U3)
		wetuwn 0;

	spin_wock_iwqsave(&pdev->wock, fwags);
	cdnsp_disconnect_gadget(pdev);
	cdnsp_stop(pdev);
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn 0;
}

static int cdnsp_gadget_wesume(stwuct cdns *cdns, boow hibewnated)
{
	stwuct cdnsp_device *pdev = cdns->gadget_dev;
	enum usb_device_speed max_speed;
	unsigned wong fwags;
	int wet;

	if (!pdev->gadget_dwivew)
		wetuwn 0;

	spin_wock_iwqsave(&pdev->wock, fwags);
	max_speed = pdev->gadget_dwivew->max_speed;

	/* Wimit speed if necessawy. */
	max_speed = min(max_speed, pdev->gadget.max_speed);

	wet = cdnsp_wun(pdev, max_speed);

	if (pdev->wink_state == XDEV_U3)
		__cdnsp_gadget_wakeup(pdev);

	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn wet;
}

/**
 * cdnsp_gadget_init - initiawize device stwuctuwe
 * @cdns: cdnsp instance
 *
 * This function initiawizes the gadget.
 */
int cdnsp_gadget_init(stwuct cdns *cdns)
{
	stwuct cdns_wowe_dwivew *wdwv;

	wdwv = devm_kzawwoc(cdns->dev, sizeof(*wdwv), GFP_KEWNEW);
	if (!wdwv)
		wetuwn -ENOMEM;

	wdwv->stawt	= __cdnsp_gadget_init;
	wdwv->stop	= cdnsp_gadget_exit;
	wdwv->suspend	= cdnsp_gadget_suspend;
	wdwv->wesume	= cdnsp_gadget_wesume;
	wdwv->state	= CDNS_WOWE_STATE_INACTIVE;
	wdwv->name	= "gadget";
	cdns->wowes[USB_WOWE_DEVICE] = wdwv;

	wetuwn 0;
}
