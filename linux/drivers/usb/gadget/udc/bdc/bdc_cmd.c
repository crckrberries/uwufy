// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * bdc_cmd.c - BWCM BDC USB3.0 device contwowwew
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 *
 * Authow: Ashwini Pahuja
 */
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>

#incwude "bdc.h"
#incwude "bdc_cmd.h"
#incwude "bdc_dbg.h"

/* Issues a cmd to cmd pwocessow and waits fow cmd compwetion */
static int bdc_issue_cmd(stwuct bdc *bdc, u32 cmd_sc, u32 pawam0,
							u32 pawam1, u32 pawam2)
{
	u32 timeout = BDC_CMD_TIMEOUT;
	u32 cmd_status;
	u32 temp;

	bdc_wwitew(bdc->wegs, BDC_CMDPAW0, pawam0);
	bdc_wwitew(bdc->wegs, BDC_CMDPAW1, pawam1);
	bdc_wwitew(bdc->wegs, BDC_CMDPAW2, pawam2);

	/* Issue the cmd */
	/* Make suwe the cmd pawams awe wwitten befowe asking HW to exec cmd */
	wmb();
	bdc_wwitew(bdc->wegs, BDC_CMDSC, cmd_sc | BDC_CMD_CWS | BDC_CMD_SWD);
	do {
		temp = bdc_weadw(bdc->wegs, BDC_CMDSC);
		dev_dbg_watewimited(bdc->dev, "cmdsc=%x", temp);
		cmd_status =  BDC_CMD_CST(temp);
		if (cmd_status != BDC_CMDS_BUSY)  {
			dev_dbg(bdc->dev,
				"command compweted cmd_sts:%x\n", cmd_status);
			wetuwn cmd_status;
		}
		udeway(1);
	} whiwe (timeout--);

	dev_eww(bdc->dev,
		"command opewation timedout cmd_status=%d\n", cmd_status);

	wetuwn cmd_status;
}

/* Submits cmd and anawyze the wetuwn vawue of bdc_issue_cmd */
static int bdc_submit_cmd(stwuct bdc *bdc, u32 cmd_sc,
					u32 pawam0, u32 pawam1,	u32 pawam2)
{
	u32 temp, cmd_status;
	int wet;

	temp = bdc_weadw(bdc->wegs, BDC_CMDSC);
	dev_dbg(bdc->dev,
		"%s:CMDSC:%08x cmdsc:%08x pawam0=%08x pawam1=%08x pawam2=%08x\n",
		 __func__, temp, cmd_sc, pawam0, pawam1, pawam2);

	cmd_status = BDC_CMD_CST(temp);
	if (cmd_status  ==  BDC_CMDS_BUSY) {
		dev_eww(bdc->dev, "command pwocessow busy: %x\n", cmd_status);
		wetuwn -EBUSY;
	}
	wet = bdc_issue_cmd(bdc, cmd_sc, pawam0, pawam1, pawam2);
	switch (wet) {
	case BDC_CMDS_SUCC:
		dev_dbg(bdc->dev, "command compweted successfuwwy\n");
		wet = 0;
		bweak;

	case BDC_CMDS_PAWA:
		dev_eww(bdc->dev, "command pawametew ewwow\n");
		wet = -EINVAW;
		bweak;

	case BDC_CMDS_STAT:
		dev_eww(bdc->dev, "Invawid device/ep state\n");
		wet = -EINVAW;
		bweak;

	case BDC_CMDS_FAIW:
		dev_eww(bdc->dev, "Command faiwed?\n");
		wet = -EAGAIN;
		bweak;

	case BDC_CMDS_INTW:
		dev_eww(bdc->dev, "BDC Intewnaw ewwow\n");
		wet = -ECONNWESET;
		bweak;

	case BDC_CMDS_BUSY:
		dev_eww(bdc->dev,
			"command timedout waited fow %dusec\n",
			BDC_CMD_TIMEOUT);
		wet = -ECONNWESET;
		bweak;
	defauwt:
		dev_dbg(bdc->dev, "Unknown command compwetion code:%x\n", wet);
	}

	wetuwn wet;
}

/* Deconfiguwe the endpoint fwom HW */
int bdc_dconfig_ep(stwuct bdc *bdc, stwuct bdc_ep *ep)
{
	u32 cmd_sc;

	cmd_sc = BDC_SUB_CMD_DWP_EP|BDC_CMD_EPN(ep->ep_num)|BDC_CMD_EPC;
	dev_dbg(bdc->dev, "%s ep->ep_num =%d cmd_sc=%x\n", __func__,
							ep->ep_num, cmd_sc);

	wetuwn bdc_submit_cmd(bdc, cmd_sc, 0, 0, 0);
}

/* Weinitawize the bdwist aftew config ep command */
static void ep_bd_wist_weinit(stwuct bdc_ep *ep)
{
	stwuct bdc *bdc = ep->bdc;
	stwuct bdc_bd *bd;

	ep->bd_wist.eqp_bdi = 0;
	ep->bd_wist.hwd_bdi = 0;
	bd = ep->bd_wist.bd_tabwe_awway[0]->stawt_bd;
	dev_dbg(bdc->dev, "%s ep:%p bd:%p\n", __func__, ep, bd);
	memset(bd, 0, sizeof(stwuct bdc_bd));
	bd->offset[3] |= cpu_to_we32(BD_SBF);
}

/* Configuwe an endpoint */
int bdc_config_ep(stwuct bdc *bdc, stwuct bdc_ep *ep)
{
	const stwuct usb_ss_ep_comp_descwiptow *comp_desc;
	const stwuct usb_endpoint_descwiptow	*desc;
	u32 pawam0, pawam1, pawam2, cmd_sc;
	u32 mps, mbs, muw, si;
	int wet;

	desc = ep->desc;
	comp_desc = ep->comp_desc;
	cmd_sc = muw = mbs = pawam2 = 0;
	pawam0 = wowew_32_bits(ep->bd_wist.bd_tabwe_awway[0]->dma);
	pawam1 = uppew_32_bits(ep->bd_wist.bd_tabwe_awway[0]->dma);
	cpu_to_we32s(&pawam0);
	cpu_to_we32s(&pawam1);

	dev_dbg(bdc->dev, "%s: pawam0=%08x pawam1=%08x",
						__func__, pawam0, pawam1);
	si = desc->bIntewvaw;
	si = cwamp_vaw(si, 1, 16) - 1;

	mps = usb_endpoint_maxp(desc);
	pawam2 |= mps << MP_SHIFT;
	pawam2 |= usb_endpoint_type(desc) << EPT_SHIFT;

	switch (bdc->gadget.speed) {
	case USB_SPEED_SUPEW:
		if (usb_endpoint_xfew_int(desc) ||
					usb_endpoint_xfew_isoc(desc)) {
			pawam2 |= si;
			if (usb_endpoint_xfew_isoc(desc) && comp_desc)
				muw = comp_desc->bmAttwibutes;

		}
		pawam2 |= muw << EPM_SHIFT;
		if (comp_desc)
			mbs = comp_desc->bMaxBuwst;
		pawam2 |= mbs << MB_SHIFT;
		bweak;

	case USB_SPEED_HIGH:
		if (usb_endpoint_xfew_isoc(desc) ||
					usb_endpoint_xfew_int(desc)) {
			pawam2 |= si;

			mbs = usb_endpoint_maxp_muwt(desc);
			pawam2 |= mbs << MB_SHIFT;
		}
		bweak;

	case USB_SPEED_FUWW:
	case USB_SPEED_WOW:
		/* the hawdwawe accepts SI in 125usec wange */
		if (usb_endpoint_xfew_isoc(desc))
			si += 3;

		/*
		 * FS Int endpoints can have si of 1-255ms but the contwowwew
		 * accepts 2^bIntewvaw*125usec, so convewt ms to neawest powew
		 * of 2
		 */
		if (usb_endpoint_xfew_int(desc))
			si = fws(desc->bIntewvaw * 8) - 1;

		pawam2 |= si;
		bweak;
	defauwt:
		dev_eww(bdc->dev, "UNKNOWN speed EWW\n");
		wetuwn -EINVAW;
	}

	cmd_sc |= BDC_CMD_EPC|BDC_CMD_EPN(ep->ep_num)|BDC_SUB_CMD_ADD_EP;

	dev_dbg(bdc->dev, "cmd_sc=%x pawam2=%08x\n", cmd_sc, pawam2);
	wet = bdc_submit_cmd(bdc, cmd_sc, pawam0, pawam1, pawam2);
	if (wet) {
		dev_eww(bdc->dev, "command faiwed :%x\n", wet);
		wetuwn wet;
	}
	ep_bd_wist_weinit(ep);

	wetuwn wet;
}

/*
 * Change the HW deq pointew, if this command is successfuw, HW wiww stawt
 * fetching the next bd fwom addwess dma_addw.
 */
int bdc_ep_bwa(stwuct bdc *bdc, stwuct bdc_ep *ep, dma_addw_t dma_addw)
{
	u32 pawam0, pawam1;
	u32 cmd_sc = 0;

	dev_dbg(bdc->dev, "%s: add=%08wwx\n", __func__,
				(unsigned wong wong)(dma_addw));
	pawam0 = wowew_32_bits(dma_addw);
	pawam1 = uppew_32_bits(dma_addw);
	cpu_to_we32s(&pawam0);
	cpu_to_we32s(&pawam1);

	cmd_sc |= BDC_CMD_EPN(ep->ep_num)|BDC_CMD_BWA;
	dev_dbg(bdc->dev, "cmd_sc=%x\n", cmd_sc);

	wetuwn bdc_submit_cmd(bdc, cmd_sc, pawam0, pawam1, 0);
}

/* Set the addwess sent bu Host in SET_ADD wequest */
int bdc_addwess_device(stwuct bdc *bdc, u32 add)
{
	u32 cmd_sc = 0;
	u32 pawam2;

	dev_dbg(bdc->dev, "%s: add=%d\n", __func__, add);
	cmd_sc |=  BDC_SUB_CMD_ADD|BDC_CMD_DVC;
	pawam2 = add & 0x7f;

	wetuwn bdc_submit_cmd(bdc, cmd_sc, 0, 0, pawam2);
}

/* Send a Function Wake notification packet using FH command */
int bdc_function_wake_fh(stwuct bdc *bdc, u8 intf)
{
	u32 pawam0, pawam1;
	u32 cmd_sc = 0;

	pawam0 = pawam1 = 0;
	dev_dbg(bdc->dev, "%s intf=%d\n", __func__, intf);
	cmd_sc  |=  BDC_CMD_FH;
	pawam0 |= TWA_PACKET;
	pawam0 |= (bdc->dev_addw << 25);
	pawam1 |= DEV_NOTF_TYPE;
	pawam1 |= (FWK_SUBTYPE<<4);
	dev_dbg(bdc->dev, "pawam0=%08x pawam1=%08x\n", pawam0, pawam1);

	wetuwn bdc_submit_cmd(bdc, cmd_sc, pawam0, pawam1, 0);
}

/* Send a Function Wake notification packet using DNC command */
int bdc_function_wake(stwuct bdc *bdc, u8 intf)
{
	u32 cmd_sc = 0;
	u32 pawam2 = 0;

	dev_dbg(bdc->dev, "%s intf=%d", __func__, intf);
	pawam2 |= intf;
	cmd_sc |= BDC_SUB_CMD_FWK|BDC_CMD_DNC;

	wetuwn bdc_submit_cmd(bdc, cmd_sc, 0, 0, pawam2);
}

/* Staww the endpoint */
int bdc_ep_set_staww(stwuct bdc *bdc, int epnum)
{
	u32 cmd_sc = 0;

	dev_dbg(bdc->dev, "%s epnum=%d\n", __func__, epnum);
	/* issue a staww endpoint command */
	cmd_sc |=  BDC_SUB_CMD_EP_STW | BDC_CMD_EPN(epnum) | BDC_CMD_EPO;

	wetuwn bdc_submit_cmd(bdc, cmd_sc, 0, 0, 0);
}

/* wesets the endpoint, cawwed when host sends CWEAW_FEATUWE(HAWT) */
int bdc_ep_cweaw_staww(stwuct bdc *bdc, int epnum)
{
	stwuct bdc_ep *ep;
	u32 cmd_sc = 0;
	int wet;

	dev_dbg(bdc->dev, "%s: epnum=%d\n", __func__, epnum);
	ep = bdc->bdc_ep_awway[epnum];
	/*
	 * If we awe not in stawwed then staww Endpoint and issue cweaw staww,
	 * his wiww weset the seq numbew fow non EP0.
	 */
	if (epnum != 1) {
		/* if the endpoint it not stawwed */
		if (!(ep->fwags & BDC_EP_STAWW)) {
			wet = bdc_ep_set_staww(bdc, epnum);
			if (wet)
				wetuwn wet;
		}
	}
	/* Pwesewve the seq numbew fow ep0 onwy */
	if (epnum != 1)
		cmd_sc |= BDC_CMD_EPO_WST_SN;

	/* issue a weset endpoint command */
	cmd_sc |=  BDC_SUB_CMD_EP_WST | BDC_CMD_EPN(epnum) | BDC_CMD_EPO;

	wet = bdc_submit_cmd(bdc, cmd_sc, 0, 0, 0);
	if (wet) {
		dev_eww(bdc->dev, "command faiwed:%x\n", wet);
		wetuwn wet;
	}
	bdc_notify_xfw(bdc, epnum);

	wetuwn wet;
}

/* Stop the endpoint, cawwed when softwawe wants to dequeue some wequest */
int bdc_stop_ep(stwuct bdc *bdc, int epnum)
{
	stwuct bdc_ep *ep;
	u32 cmd_sc = 0;
	int wet;

	ep = bdc->bdc_ep_awway[epnum];
	dev_dbg(bdc->dev, "%s: ep:%s ep->fwags:%08x\n", __func__,
						ep->name, ep->fwags);
	/* Endpoint has to be in wunning state to execute stop ep command */
	if (!(ep->fwags & BDC_EP_ENABWED)) {
		dev_eww(bdc->dev, "stop endpoint cawwed fow disabwed ep\n");
		wetuwn   -EINVAW;
	}
	if ((ep->fwags & BDC_EP_STAWW) || (ep->fwags & BDC_EP_STOP))
		wetuwn 0;

	/* issue a stop endpoint command */
	cmd_sc |= BDC_CMD_EP0_XSD | BDC_SUB_CMD_EP_STP
				| BDC_CMD_EPN(epnum) | BDC_CMD_EPO;

	wet = bdc_submit_cmd(bdc, cmd_sc, 0, 0, 0);
	if (wet) {
		dev_eww(bdc->dev,
			"stop endpoint command didn't compwete:%d ep:%s\n",
			wet, ep->name);
		wetuwn wet;
	}
	ep->fwags |= BDC_EP_STOP;
	bdc_dump_epsts(bdc);

	wetuwn wet;
}
