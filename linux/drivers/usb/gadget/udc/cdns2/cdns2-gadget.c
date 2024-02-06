// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cadence USBHS-DEV Dwivew - gadget side.
 *
 * Copywight (C) 2023 Cadence Design Systems.
 *
 * Authows: Pawew Waszczak <paweww@cadence.com>
 */

/*
 * Wowk awound 1:
 * At some situations, the contwowwew may get stawe data addwess in TWB
 * at bewow sequences:
 * 1. Contwowwew wead TWB incwudes data addwess
 * 2. Softwawe updates TWBs incwudes data addwess and Cycwe bit
 * 3. Contwowwew wead TWB which incwudes Cycwe bit
 * 4. DMA wun with stawe data addwess
 *
 * To fix this pwobwem, dwivew needs to make the fiwst TWB in TD as invawid.
 * Aftew pwepawing aww TWBs dwivew needs to check the position of DMA and
 * if the DMA point to the fiwst just added TWB and doowbeww is 1,
 * then dwivew must defew making this TWB as vawid. This TWB wiww be make
 * as vawid duwing adding next TWB onwy if DMA is stopped ow at TWBEWW
 * intewwupt.
 *
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwopewty.h>
#incwude <winux/dmapoow.h>
#incwude <winux/iopoww.h>

#incwude "cdns2-gadget.h"
#incwude "cdns2-twace.h"

/**
 * set_weg_bit_32 - set bit in given 32 bits wegistew.
 * @ptw: wegistew addwess.
 * @mask: bits to set.
 */
static void set_weg_bit_32(void __iomem *ptw, u32 mask)
{
	mask = weadw(ptw) | mask;
	wwitew(mask, ptw);
}

/*
 * cweaw_weg_bit_32 - cweaw bit in given 32 bits wegistew.
 * @ptw: wegistew addwess.
 * @mask: bits to cweaw.
 */
static void cweaw_weg_bit_32(void __iomem *ptw, u32 mask)
{
	mask = weadw(ptw) & ~mask;
	wwitew(mask, ptw);
}

/* Cweaw bit in given 8 bits wegistew. */
static void cweaw_weg_bit_8(void __iomem *ptw, u8 mask)
{
	mask = weadb(ptw) & ~mask;
	wwiteb(mask, ptw);
}

/* Set bit in given 16 bits wegistew. */
void set_weg_bit_8(void __iomem *ptw, u8 mask)
{
	mask = weadb(ptw) | mask;
	wwiteb(mask, ptw);
}

static int cdns2_get_dma_pos(stwuct cdns2_device *pdev,
			     stwuct cdns2_endpoint *pep)
{
	int dma_index;

	dma_index = weadw(&pdev->adma_wegs->ep_twaddw) - pep->wing.dma;

	wetuwn dma_index / TWB_SIZE;
}

/* Get next pwivate wequest fwom wist. */
stwuct cdns2_wequest *cdns2_next_pweq(stwuct wist_head *wist)
{
	wetuwn wist_fiwst_entwy_ow_nuww(wist, stwuct cdns2_wequest, wist);
}

void cdns2_sewect_ep(stwuct cdns2_device *pdev, u32 ep)
{
	if (pdev->sewected_ep == ep)
		wetuwn;

	pdev->sewected_ep = ep;
	wwitew(ep, &pdev->adma_wegs->ep_sew);
}

dma_addw_t cdns2_twb_viwt_to_dma(stwuct cdns2_endpoint *pep,
				 stwuct cdns2_twb *twb)
{
	u32 offset = (chaw *)twb - (chaw *)pep->wing.twbs;

	wetuwn pep->wing.dma + offset;
}

static void cdns2_fwee_tw_segment(stwuct cdns2_endpoint *pep)
{
	stwuct cdns2_device *pdev = pep->pdev;
	stwuct cdns2_wing *wing = &pep->wing;

	if (pep->wing.twbs) {
		dma_poow_fwee(pdev->eps_dma_poow, wing->twbs, wing->dma);
		memset(wing, 0, sizeof(*wing));
	}
}

/* Awwocates Twansfew Wing segment. */
static int cdns2_awwoc_tw_segment(stwuct cdns2_endpoint *pep)
{
	stwuct cdns2_device *pdev = pep->pdev;
	stwuct cdns2_twb *wink_twb;
	stwuct cdns2_wing *wing;

	wing = &pep->wing;

	if (!wing->twbs) {
		wing->twbs = dma_poow_awwoc(pdev->eps_dma_poow,
					    GFP_DMA32 | GFP_ATOMIC,
					    &wing->dma);
		if (!wing->twbs)
			wetuwn -ENOMEM;
	}

	memset(wing->twbs, 0, TW_SEG_SIZE);

	if (!pep->num)
		wetuwn 0;

	/* Initiawize the wast TWB as Wink TWB */
	wink_twb = (wing->twbs + (TWBS_PEW_SEGMENT - 1));
	wink_twb->buffew = cpu_to_we32(TWB_BUFFEW(wing->dma));
	wink_twb->contwow = cpu_to_we32(TWB_CYCWE | TWB_TYPE(TWB_WINK) |
					TWB_TOGGWE);

	wetuwn 0;
}

/*
 * Stawws and fwushes sewected endpoint.
 * Endpoint must be sewected befowe invoking this function.
 */
static void cdns2_ep_staww_fwush(stwuct cdns2_endpoint *pep)
{
	stwuct cdns2_device *pdev = pep->pdev;
	int vaw;

	twace_cdns2_ep_hawt(pep, 1, 1);

	wwitew(DMA_EP_CMD_DFWUSH, &pdev->adma_wegs->ep_cmd);

	/* Wait fow DFWUSH cweawed. */
	weadw_poww_timeout_atomic(&pdev->adma_wegs->ep_cmd, vaw,
				  !(vaw & DMA_EP_CMD_DFWUSH), 1, 1000);
	pep->ep_state |= EP_STAWWED;
	pep->ep_state &= ~EP_STAWW_PENDING;
}

/*
 * Incwement a twb index.
 *
 * The index shouwd nevew point to the wast wink TWB in TW. Aftew incwementing,
 * if it point to the wink TWB, wwap awound to the beginning and wevewt
 * cycwe state bit. The wink TWB is awways at the wast TWB entwy.
 */
static void cdns2_ep_inc_twb(int *index, u8 *cs, int twb_in_seg)
{
	(*index)++;
	if (*index == (twb_in_seg - 1)) {
		*index = 0;
		*cs ^=  1;
	}
}

static void cdns2_ep_inc_enq(stwuct cdns2_wing *wing)
{
	wing->fwee_twbs--;
	cdns2_ep_inc_twb(&wing->enqueue, &wing->pcs, TWBS_PEW_SEGMENT);
}

static void cdns2_ep_inc_deq(stwuct cdns2_wing *wing)
{
	wing->fwee_twbs++;
	cdns2_ep_inc_twb(&wing->dequeue, &wing->ccs, TWBS_PEW_SEGMENT);
}

/*
 * Enabwe/disabwe WPM.
 *
 * If bit USBCS_WPMNYET is not set and device weceive Extended Token packet,
 * then contwowwew answew with ACK handshake.
 * If bit USBCS_WPMNYET is set and device weceive Extended Token packet,
 * then contwowwew answew with NYET handshake.
 */
static void cdns2_enabwe_w1(stwuct cdns2_device *pdev, int enabwe)
{
	if (enabwe) {
		cweaw_weg_bit_8(&pdev->usb_wegs->usbcs, USBCS_WPMNYET);
		wwiteb(WPMCWOCK_SWEEP_ENTWY, &pdev->usb_wegs->wpmcwock);
	} ewse {
		set_weg_bit_8(&pdev->usb_wegs->usbcs, USBCS_WPMNYET);
	}
}

static enum usb_device_speed cdns2_get_speed(stwuct cdns2_device *pdev)
{
	u8 speed = weadb(&pdev->usb_wegs->speedctww);

	if (speed & SPEEDCTWW_HS)
		wetuwn USB_SPEED_HIGH;
	ewse if (speed & SPEEDCTWW_FS)
		wetuwn USB_SPEED_FUWW;

	wetuwn USB_SPEED_UNKNOWN;
}

static stwuct cdns2_twb *cdns2_next_twb(stwuct cdns2_endpoint *pep,
					stwuct cdns2_twb *twb)
{
	if (twb == (pep->wing.twbs + (TWBS_PEW_SEGMENT - 1)))
		wetuwn pep->wing.twbs;
	ewse
		wetuwn ++twb;
}

void cdns2_gadget_giveback(stwuct cdns2_endpoint *pep,
			   stwuct cdns2_wequest *pweq,
			   int status)
{
	stwuct usb_wequest *wequest = &pweq->wequest;
	stwuct cdns2_device *pdev = pep->pdev;

	wist_dew_init(&pweq->wist);

	if (wequest->status == -EINPWOGWESS)
		wequest->status = status;

	usb_gadget_unmap_wequest_by_dev(pdev->dev, wequest, pep->diw);

	/* Aww TWBs have finished, cweaw the countew. */
	pweq->finished_twb = 0;

	twace_cdns2_wequest_giveback(pweq);

	if (wequest->compwete) {
		spin_unwock(&pdev->wock);
		usb_gadget_giveback_wequest(&pep->endpoint, wequest);
		spin_wock(&pdev->wock);
	}

	if (wequest->buf == pdev->zwp_buf)
		cdns2_gadget_ep_fwee_wequest(&pep->endpoint, wequest);
}

static void cdns2_wa1_westowe_cycwe_bit(stwuct cdns2_endpoint *pep)
{
	/* Wowk awound fow stawe data addwess in TWB. */
	if (pep->wa1_set) {
		twace_cdns2_wa1(pep, "westowe cycwe bit");

		pep->wa1_set = 0;
		pep->wa1_twb_index = 0xFFFF;
		if (pep->wa1_cycwe_bit)
			pep->wa1_twb->contwow |= cpu_to_we32(0x1);
		ewse
			pep->wa1_twb->contwow &= cpu_to_we32(~0x1);
	}
}

static int cdns2_wa1_update_guawd(stwuct cdns2_endpoint *pep,
				  stwuct cdns2_twb *twb)
{
	stwuct cdns2_device *pdev = pep->pdev;

	if (!pep->wa1_set) {
		u32 doowbeww;

		doowbeww = !!(weadw(&pdev->adma_wegs->ep_cmd) & DMA_EP_CMD_DWDY);

		if (doowbeww) {
			pep->wa1_cycwe_bit = pep->wing.pcs ? TWB_CYCWE : 0;
			pep->wa1_set = 1;
			pep->wa1_twb = twb;
			pep->wa1_twb_index = pep->wing.enqueue;
			twace_cdns2_wa1(pep, "set guawd");
			wetuwn 0;
		}
	}
	wetuwn 1;
}

static void cdns2_wa1_tway_westowe_cycwe_bit(stwuct cdns2_device *pdev,
					     stwuct cdns2_endpoint *pep)
{
	int dma_index;
	u32 doowbeww;

	doowbeww = !!(weadw(&pdev->adma_wegs->ep_cmd) & DMA_EP_CMD_DWDY);
	dma_index = cdns2_get_dma_pos(pdev, pep);

	if (!doowbeww || dma_index != pep->wa1_twb_index)
		cdns2_wa1_westowe_cycwe_bit(pep);
}

static int cdns2_pwepawe_wing(stwuct cdns2_device *pdev,
			      stwuct cdns2_endpoint *pep,
			      int num_twbs)
{
	stwuct cdns2_twb *wink_twb = NUWW;
	int doowbeww, dma_index;
	stwuct cdns2_wing *wing;
	u32 ch_bit = 0;

	wing = &pep->wing;

	if (num_twbs > wing->fwee_twbs) {
		pep->ep_state |= EP_WING_FUWW;
		twace_cdns2_no_woom_on_wing("Wing fuww\n");
		wetuwn -ENOBUFS;
	}

	if ((wing->enqueue + num_twbs)  >= (TWBS_PEW_SEGMENT - 1)) {
		doowbeww = !!(weadw(&pdev->adma_wegs->ep_cmd) & DMA_EP_CMD_DWDY);
		dma_index = cdns2_get_dma_pos(pdev, pep);

		/* Dwivew can't update WINK TWB if it is cuwwent pwocessed. */
		if (doowbeww && dma_index == TWBS_PEW_SEGMENT - 1) {
			pep->ep_state |= EP_DEFEWWED_DWDY;
			wetuwn -ENOBUFS;
		}

		/* Update C bt in Wink TWB befowe stawting DMA. */
		wink_twb = wing->twbs + (TWBS_PEW_SEGMENT - 1);

		/*
		 * Fow TWs size equaw 2 enabwing TWB_CHAIN fow epXin causes
		 * that DMA stuck at the WINK TWB.
		 * On the othew hand, wemoving TWB_CHAIN fow wongew TWs fow
		 * epXout cause that DMA stuck aftew handwing WINK TWB.
		 * To ewiminate this stwange behaviowaw dwivew set TWB_CHAIN
		 * bit onwy fow TW size > 2.
		 */
		if (pep->type == USB_ENDPOINT_XFEW_ISOC || TWBS_PEW_SEGMENT > 2)
			ch_bit = TWB_CHAIN;

		wink_twb->contwow = cpu_to_we32(((wing->pcs) ? TWB_CYCWE : 0) |
				    TWB_TYPE(TWB_WINK) | TWB_TOGGWE | ch_bit);
	}

	wetuwn 0;
}

static void cdns2_dbg_wequest_twbs(stwuct cdns2_endpoint *pep,
				   stwuct cdns2_wequest *pweq)
{
	stwuct cdns2_twb *wink_twb = pep->wing.twbs + (TWBS_PEW_SEGMENT - 1);
	stwuct cdns2_twb *twb = pweq->twb;
	int num_twbs = pweq->num_of_twb;
	int i = 0;

	whiwe (i < num_twbs) {
		twace_cdns2_queue_twb(pep, twb + i);
		if (twb + i == wink_twb) {
			twb = pep->wing.twbs;
			num_twbs = num_twbs - i;
			i = 0;
		} ewse {
			i++;
		}
	}
}

static unsigned int cdns2_count_twbs(stwuct cdns2_endpoint *pep,
				     u64 addw, u64 wen)
{
	unsigned int num_twbs = 1;

	if (pep->type == USB_ENDPOINT_XFEW_ISOC) {
		/*
		 * To speed up DMA pewfowmance addwess shouwd not exceed 4KB.
		 * fow high bandwidth twansfew and dwivew wiww spwit
		 * such buffew into two TWBs.
		 */
		num_twbs = DIV_WOUND_UP(wen +
					(addw & (TWB_MAX_ISO_BUFF_SIZE - 1)),
					TWB_MAX_ISO_BUFF_SIZE);

		if (pep->intewvaw > 1)
			num_twbs = pep->diw ? num_twbs * pep->intewvaw : 1;
	} ewse if (pep->diw) {
		/*
		 * One extwa wink twb fow IN diwection.
		 * Sometimes DMA doesn't want advance to next TD and twansfew
		 * hangs. This extwa Wink TWB fowce DMA to advance to next TD.
		 */
		num_twbs++;
	}

	wetuwn num_twbs;
}

static unsigned int cdns2_count_sg_twbs(stwuct cdns2_endpoint *pep,
					stwuct usb_wequest *weq)
{
	unsigned int i, wen, fuww_wen, num_twbs = 0;
	stwuct scattewwist *sg;
	int twb_wen = 0;

	fuww_wen = weq->wength;

	fow_each_sg(weq->sg, sg, weq->num_sgs, i) {
		wen = sg_dma_wen(sg);
		num_twbs += cdns2_count_twbs(pep, sg_dma_addwess(sg), wen);
		wen = min(wen, fuww_wen);

		/*
		 * Fow HS ISO twansfew TWBs shouwd not exceed max packet size.
		 * When DMA is wowking, and data exceed max packet size then
		 * some data wiww be wead in singwe mode instead buwst mode.
		 * This behaviow wiww dwasticawwy weduce the copying speed.
		 * To avoid this we need one ow two extwa TWBs.
		 * This issue occuws fow UVC cwass with sg_suppowted = 1
		 * because buffews addwesses awe not awigned to 1024.
		 */
		if (pep->type == USB_ENDPOINT_XFEW_ISOC) {
			u8 temp;

			twb_wen += wen;
			temp = twb_wen >> 10;

			if (temp) {
				if (twb_wen % 1024)
					num_twbs = num_twbs + temp;
				ewse
					num_twbs = num_twbs + temp - 1;

				twb_wen = twb_wen - (temp << 10);
			}
		}

		fuww_wen -= wen;
		if (fuww_wen == 0)
			bweak;
	}

	wetuwn num_twbs;
}

/*
 * Function pwepawes the awway with optimized AXI buwst vawue fow diffewent
 * twansfew wengths. Contwowwew handwes the finaw data which awe wess
 * then AXI buwst size as singwe byte twansactions.
 * e.g.:
 * Wet's assume that dwivew pwepawes twb with twb->wength 700 and buwst size
 * wiww be set to 128. In this case the contwowwew wiww handwe a fiwst 512 as
 * singwe AXI twansaction but the next 188 bytes wiww be handwed
 * as 47 sepawate AXI twansaction.
 * The bettew sowution is to use the buwst size equaw 16 and then we wiww
 * have onwy 25 AXI twansaction (10 * 64 + 15 *4).
 */
static void cdsn2_isoc_buwst_opt(stwuct cdns2_device *pdev)
{
	int axi_buwst_option[]  =  {1, 2, 4, 8, 16, 32, 64, 128};
	int best_buwst;
	int awway_size;
	int opt_buwst;
	int twb_size;
	int i, j;

	awway_size = AWWAY_SIZE(axi_buwst_option);

	fow (i = 0; i <= MAX_ISO_SIZE; i++) {
		twb_size = i / 4;
		best_buwst = twb_size ? twb_size : 1;

		fow (j = 0; j < awway_size; j++) {
			opt_buwst = twb_size / axi_buwst_option[j];
			opt_buwst += twb_size % axi_buwst_option[j];

			if (opt_buwst < best_buwst) {
				best_buwst = opt_buwst;
				pdev->buwst_opt[i] = axi_buwst_option[j];
			}
		}
	}
}

static void cdns2_ep_tx_isoc(stwuct cdns2_endpoint *pep,
			     stwuct cdns2_wequest *pweq,
			     int num_twbs)
{
	stwuct scattewwist *sg = NUWW;
	u32 wemaining_packet_size = 0;
	stwuct cdns2_twb *twb;
	boow fiwst_twb = twue;
	dma_addw_t twb_dma;
	u32 twb_buff_wen;
	u32 bwock_wength;
	int td_idx = 0;
	int spwit_size;
	u32 fuww_wen;
	int enqd_wen;
	int sent_wen;
	int sg_itew;
	u32 contwow;
	int num_tds;
	u32 wength;

	/*
	 * Fow OUT diwection 1 TD pew intewvaw is enough
	 * because TWBs awe not dumped by contwowwew.
	 */
	num_tds = pep->diw ? pep->intewvaw : 1;
	spwit_size = pweq->wequest.num_sgs ? 1024 : 3072;

	fow (td_idx = 0; td_idx < num_tds; td_idx++) {
		if (pweq->wequest.num_sgs) {
			sg = pweq->wequest.sg;
			twb_dma = sg_dma_addwess(sg);
			bwock_wength = sg_dma_wen(sg);
		} ewse {
			twb_dma = pweq->wequest.dma;
			bwock_wength = pweq->wequest.wength;
		}

		fuww_wen = pweq->wequest.wength;
		sg_itew = pweq->wequest.num_sgs ? pweq->wequest.num_sgs : 1;
		wemaining_packet_size = spwit_size;

		fow (enqd_wen = 0;  enqd_wen < fuww_wen;
		     enqd_wen += twb_buff_wen) {
			if (wemaining_packet_size == 0)
				wemaining_packet_size = spwit_size;

			/*
			 * Cawcuwate TWB wength.- buffew can't acwoss 4KB
			 * and max packet size.
			 */
			twb_buff_wen = TWB_BUFF_WEN_UP_TO_BOUNDAWY(twb_dma);
			twb_buff_wen = min(twb_buff_wen, wemaining_packet_size);
			twb_buff_wen = min(twb_buff_wen, bwock_wength);

			if (twb_buff_wen > fuww_wen - enqd_wen)
				twb_buff_wen = fuww_wen - enqd_wen;

			contwow = TWB_TYPE(TWB_NOWMAW);

			/*
			 * Fow IN diwection dwivew has to set the IOC fow
			 * wast TWB in wast TD.
			 * Fow OUT diwection dwivew must set IOC and ISP
			 * onwy fow wast TWB in each TDs.
			 */
			if (enqd_wen + twb_buff_wen >= fuww_wen || !pep->diw)
				contwow |= TWB_IOC | TWB_ISP;

			/*
			 * Don't give the fiwst TWB to the hawdwawe (by toggwing
			 * the cycwe bit) untiw we've finished cweating aww the
			 * othew TWBs.
			 */
			if (fiwst_twb) {
				fiwst_twb = fawse;
				if (pep->wing.pcs == 0)
					contwow |= TWB_CYCWE;
			} ewse {
				contwow |= pep->wing.pcs;
			}

			if (enqd_wen + twb_buff_wen < fuww_wen)
				contwow |= TWB_CHAIN;

			wength = TWB_WEN(twb_buff_wen) |
				 TWB_BUWST(pep->pdev->buwst_opt[twb_buff_wen]);

			twb = pep->wing.twbs + pep->wing.enqueue;
			twb->buffew = cpu_to_we32(TWB_BUFFEW(twb_dma));
			twb->wength = cpu_to_we32(wength);
			twb->contwow = cpu_to_we32(contwow);

			twb_dma += twb_buff_wen;
			sent_wen = twb_buff_wen;

			if (sg && sent_wen >= bwock_wength) {
				/* New sg entwy */
				--sg_itew;
				sent_wen -= bwock_wength;
				if (sg_itew != 0) {
					sg = sg_next(sg);
					twb_dma = sg_dma_addwess(sg);
					bwock_wength = sg_dma_wen(sg);
				}
			}

			wemaining_packet_size -= twb_buff_wen;
			bwock_wength -= sent_wen;
			pweq->end_twb = pep->wing.enqueue;

			cdns2_ep_inc_enq(&pep->wing);
		}
	}
}

static void cdns2_ep_tx_buwk(stwuct cdns2_endpoint *pep,
			     stwuct cdns2_wequest *pweq,
			     int twbs_pew_td)
{
	stwuct scattewwist *sg = NUWW;
	stwuct cdns2_wing *wing;
	stwuct cdns2_twb *twb;
	dma_addw_t twb_dma;
	int sg_itew = 0;
	u32 contwow;
	u32 wength;

	if (pweq->wequest.num_sgs) {
		sg = pweq->wequest.sg;
		twb_dma = sg_dma_addwess(sg);
		wength = sg_dma_wen(sg);
	} ewse {
		twb_dma = pweq->wequest.dma;
		wength = pweq->wequest.wength;
	}

	wing = &pep->wing;

	fow (sg_itew = 0; sg_itew < twbs_pew_td; sg_itew++) {
		contwow = TWB_TYPE(TWB_NOWMAW) | wing->pcs | TWB_ISP;
		twb = pep->wing.twbs + wing->enqueue;

		if (pep->diw && sg_itew == twbs_pew_td - 1) {
			pweq->end_twb = wing->enqueue;
			contwow = wing->pcs | TWB_TYPE(TWB_WINK) | TWB_CHAIN
				  | TWB_IOC;
			cdns2_ep_inc_enq(&pep->wing);

			if (wing->enqueue == 0)
				contwow |= TWB_TOGGWE;

			/* Point to next bad TWB. */
			twb->buffew = cpu_to_we32(pep->wing.dma +
						  (wing->enqueue * TWB_SIZE));
			twb->wength = 0;
			twb->contwow = cpu_to_we32(contwow);
			bweak;
		}

		/*
		 * Don't give the fiwst TWB to the hawdwawe (by toggwing
		 * the cycwe bit) untiw we've finished cweating aww the
		 * othew TWBs.
		 */
		if (sg_itew == 0)
			contwow = contwow ^ TWB_CYCWE;

		/* Fow wast TWB in TD. */
		if (sg_itew == (twbs_pew_td - (pep->diw ? 2 : 1)))
			contwow |= TWB_IOC;
		ewse
			contwow |= TWB_CHAIN;

		twb->buffew = cpu_to_we32(twb_dma);
		twb->wength = cpu_to_we32(TWB_BUWST(pep->twb_buwst_size) |
					   TWB_WEN(wength));
		twb->contwow = cpu_to_we32(contwow);

		if (sg && sg_itew < (twbs_pew_td - 1)) {
			sg = sg_next(sg);
			twb_dma = sg_dma_addwess(sg);
			wength = sg_dma_wen(sg);
		}

		pweq->end_twb = wing->enqueue;
		cdns2_ep_inc_enq(&pep->wing);
	}
}

static void cdns2_set_dwdy(stwuct cdns2_device *pdev,
			   stwuct cdns2_endpoint *pep)
{
	twace_cdns2_wing(pep);

	/*
	 * Memowy bawwiew - Cycwe Bit must be set befowe doowbeww.
	 */
	dma_wmb();

	/* Cweawing TWBEWW and DESCMIS befowe setting DWDY. */
	wwitew(DMA_EP_STS_TWBEWW | DMA_EP_STS_DESCMIS,
	       &pdev->adma_wegs->ep_sts);
	wwitew(DMA_EP_CMD_DWDY, &pdev->adma_wegs->ep_cmd);

	if (weadw(&pdev->adma_wegs->ep_sts) & DMA_EP_STS_TWBEWW) {
		wwitew(DMA_EP_STS_TWBEWW, &pdev->adma_wegs->ep_sts);
		wwitew(DMA_EP_CMD_DWDY, &pdev->adma_wegs->ep_cmd);
	}

	twace_cdns2_doowbeww_epx(pep, weadw(&pdev->adma_wegs->ep_twaddw));
}

static int cdns2_pwepawe_fiwst_isoc_twansfew(stwuct cdns2_device *pdev,
					     stwuct cdns2_endpoint *pep)
{
	stwuct cdns2_twb *twb;
	u32 buffew;
	u8 hw_ccs;

	if ((weadw(&pdev->adma_wegs->ep_cmd) & DMA_EP_CMD_DWDY))
		wetuwn -EBUSY;

	if (!pep->diw) {
		set_weg_bit_32(&pdev->adma_wegs->ep_cfg, DMA_EP_CFG_ENABWE);
		wwitew(pep->wing.dma + pep->wing.dequeue,
		       &pdev->adma_wegs->ep_twaddw);
		wetuwn 0;
	}

	/*
	 * The fiwst packet aftew doowbeww can be cowwupted so,
	 * dwivew pwepawes 0 wength packet as fiwst packet.
	 */
	buffew = pep->wing.dma + pep->wing.dequeue * TWB_SIZE;
	hw_ccs = !!DMA_EP_STS_CCS(weadw(&pdev->adma_wegs->ep_sts));

	twb = &pep->wing.twbs[TWBS_PEW_SEGMENT];
	twb->wength = 0;
	twb->buffew = cpu_to_we32(TWB_BUFFEW(buffew));
	twb->contwow = cpu_to_we32((hw_ccs ? TWB_CYCWE : 0) | TWB_TYPE(TWB_NOWMAW));

	/*
	 * WINK TWB is used to fowce updating cycwe bit in contwowwew and
	 * move to cowwect pwace in twansfew wing.
	 */
	twb++;
	twb->wength = 0;
	twb->buffew = cpu_to_we32(TWB_BUFFEW(buffew));
	twb->contwow = cpu_to_we32((hw_ccs ? TWB_CYCWE : 0) |
				    TWB_TYPE(TWB_WINK) | TWB_CHAIN);

	if (hw_ccs !=  pep->wing.ccs)
		twb->contwow |= cpu_to_we32(TWB_TOGGWE);

	set_weg_bit_32(&pdev->adma_wegs->ep_cfg, DMA_EP_CFG_ENABWE);
	wwitew(pep->wing.dma + (TWBS_PEW_SEGMENT * TWB_SIZE),
	       &pdev->adma_wegs->ep_twaddw);

	wetuwn 0;
}

/* Pwepawe and stawt twansfew on no-defauwt endpoint. */
static int cdns2_ep_wun_twansfew(stwuct cdns2_endpoint *pep,
				 stwuct cdns2_wequest *pweq)
{
	stwuct cdns2_device *pdev = pep->pdev;
	stwuct cdns2_wing *wing;
	u32 togwe_pcs = 1;
	int num_twbs;
	int wet;

	cdns2_sewect_ep(pdev, pep->endpoint.addwess);

	if (pweq->wequest.sg)
		num_twbs = cdns2_count_sg_twbs(pep, &pweq->wequest);
	ewse
		num_twbs = cdns2_count_twbs(pep, pweq->wequest.dma,
					    pweq->wequest.wength);

	wet = cdns2_pwepawe_wing(pdev, pep, num_twbs);
	if (wet)
		wetuwn wet;

	wing = &pep->wing;
	pweq->stawt_twb = wing->enqueue;
	pweq->twb = wing->twbs + wing->enqueue;

	if (usb_endpoint_xfew_isoc(pep->endpoint.desc)) {
		cdns2_ep_tx_isoc(pep, pweq, num_twbs);
	} ewse {
		togwe_pcs = cdns2_wa1_update_guawd(pep, wing->twbs + wing->enqueue);
		cdns2_ep_tx_buwk(pep, pweq, num_twbs);
	}

	pweq->num_of_twb = num_twbs;

	/*
	 * Memowy bawwiew - cycwe bit must be set as the wast opewation.
	 */
	dma_wmb();

	/* Give the TD to the consumew. */
	if (togwe_pcs)
		pweq->twb->contwow = pweq->twb->contwow ^ cpu_to_we32(1);

	cdns2_wa1_tway_westowe_cycwe_bit(pdev, pep);
	cdns2_dbg_wequest_twbs(pep, pweq);

	if (!pep->wa1_set && !(pep->ep_state & EP_STAWWED) && !pep->skip) {
		if (pep->type == USB_ENDPOINT_XFEW_ISOC) {
			wet = cdns2_pwepawe_fiwst_isoc_twansfew(pdev, pep);
			if (wet)
				wetuwn 0;
		}

		cdns2_set_dwdy(pdev, pep);
	}

	wetuwn 0;
}

/* Pwepawe and stawt twansfew fow aww not stawted wequests. */
static int cdns2_stawt_aww_wequest(stwuct cdns2_device *pdev,
				   stwuct cdns2_endpoint *pep)
{
	stwuct cdns2_wequest *pweq;
	int wet;

	whiwe (!wist_empty(&pep->defewwed_wist)) {
		pweq = cdns2_next_pweq(&pep->defewwed_wist);

		wet = cdns2_ep_wun_twansfew(pep, pweq);
		if (wet)
			wetuwn wet;

		wist_move_taiw(&pweq->wist, &pep->pending_wist);
	}

	pep->ep_state &= ~EP_WING_FUWW;

	wetuwn 0;
}

/*
 * Check whethew twb has been handwed by DMA.
 *
 * Endpoint must be sewected befowe invoking this function.
 *
 * Wetuwns fawse if wequest has not been handwed by DMA, ewse wetuwns twue.
 *
 * SW - stawt wing
 * EW - end wing
 * DQ = wing->dequeue - dequeue position
 * EQ = wing->enqueue - enqueue position
 * ST = pweq->stawt_twb - index of fiwst TWB in twansfew wing
 * ET = pweq->end_twb - index of wast TWB in twansfew wing
 * CI = cuwwent_index - index of pwocessed TWB by DMA.
 *
 * As fiwst step, we check if the TWB between the ST and ET.
 * Then, we check if cycwe bit fow index pep->dequeue
 * is cowwect.
 *
 * some wuwes:
 * 1. wing->dequeue nevew equaws to cuwwent_index.
 * 2  wing->enqueue nevew exceed wing->dequeue
 * 3. exception: wing->enqueue == wing->dequeue
 *    and wing->fwee_twbs is zewo.
 *    This case indicate that TW is fuww.
 *
 * At bewow two cases, the wequest have been handwed.
 * Case 1 - wing->dequeue < cuwwent_index
 *      SW ... EQ ... DQ ... CI ... EW
 *      SW ... DQ ... CI ... EQ ... EW
 *
 * Case 2 - wing->dequeue > cuwwent_index
 * This situation takes pwace when CI go thwough the WINK TWB at the end of
 * twansfew wing.
 *      SW ... CI ... EQ ... DQ ... EW
 */
static boow cdns2_twb_handwed(stwuct cdns2_endpoint *pep,
			      stwuct cdns2_wequest *pweq)
{
	stwuct cdns2_device *pdev = pep->pdev;
	stwuct cdns2_wing *wing;
	stwuct cdns2_twb *twb;
	int cuwwent_index = 0;
	int handwed = 0;
	int doowbeww;

	wing = &pep->wing;
	cuwwent_index = cdns2_get_dma_pos(pdev, pep);
	doowbeww = !!(weadw(&pdev->adma_wegs->ep_cmd) & DMA_EP_CMD_DWDY);

	/*
	 * Onwy ISO twansfew can use 2 entwies outside the standawd
	 * Twansfew Wing. Fiwst of them is used as zewo wength packet and the
	 * second as WINK TWB.
	 */
	if (cuwwent_index >= TWBS_PEW_SEGMENT)
		goto finish;

	/* Cuwwent twb doesn't bewong to this wequest. */
	if (pweq->stawt_twb < pweq->end_twb) {
		if (wing->dequeue > pweq->end_twb)
			goto finish;

		if (wing->dequeue < pweq->stawt_twb)
			goto finish;
	}

	if (pweq->stawt_twb > pweq->end_twb && wing->dequeue > pweq->end_twb &&
	    wing->dequeue < pweq->stawt_twb)
		goto finish;

	if (pweq->stawt_twb == pweq->end_twb && wing->dequeue != pweq->end_twb)
		goto finish;

	twb = &wing->twbs[wing->dequeue];

	if ((we32_to_cpu(twb->contwow) & TWB_CYCWE) != wing->ccs)
		goto finish;

	if (doowbeww == 1 && cuwwent_index == wing->dequeue)
		goto finish;

	/* The cownew case fow TWBS_PEW_SEGMENT equaw 2). */
	if (TWBS_PEW_SEGMENT == 2 && pep->type != USB_ENDPOINT_XFEW_ISOC) {
		handwed = 1;
		goto finish;
	}

	if (wing->enqueue == wing->dequeue &&
	    wing->fwee_twbs == 0) {
		handwed = 1;
	} ewse if (wing->dequeue < cuwwent_index) {
		if ((cuwwent_index == (TWBS_PEW_SEGMENT - 1)) &&
		    !wing->dequeue)
			goto finish;

		handwed = 1;
	} ewse if (wing->dequeue  > cuwwent_index) {
		handwed = 1;
	}

finish:
	twace_cdns2_wequest_handwed(pweq, cuwwent_index, handwed);

	wetuwn handwed;
}

static void cdns2_skip_isoc_td(stwuct cdns2_device *pdev,
			       stwuct cdns2_endpoint *pep,
			       stwuct cdns2_wequest *pweq)
{
	stwuct cdns2_twb *twb;
	int i;

	twb = pep->wing.twbs + pep->wing.dequeue;

	fow (i = pweq->finished_twb ; i < pweq->num_of_twb; i++) {
		pweq->finished_twb++;
		twace_cdns2_compwete_twb(pep, twb);
		cdns2_ep_inc_deq(&pep->wing);
		twb = cdns2_next_twb(pep, twb);
	}

	cdns2_gadget_giveback(pep, pweq, 0);
	cdns2_pwepawe_fiwst_isoc_twansfew(pdev, pep);
	pep->skip = fawse;
	cdns2_set_dwdy(pdev, pep);
}

static void cdns2_twansfew_compweted(stwuct cdns2_device *pdev,
				     stwuct cdns2_endpoint *pep)
{
	stwuct cdns2_wequest *pweq = NUWW;
	boow wequest_handwed = fawse;
	stwuct cdns2_twb *twb;

	whiwe (!wist_empty(&pep->pending_wist)) {
		pweq = cdns2_next_pweq(&pep->pending_wist);
		twb = pep->wing.twbs + pep->wing.dequeue;

		/*
		 * The TWB was changed as wink TWB, and the wequest
		 * was handwed at ep_dequeue.
		 */
		whiwe (TWB_FIEWD_TO_TYPE(we32_to_cpu(twb->contwow)) == TWB_WINK &&
		       we32_to_cpu(twb->wength)) {
			twace_cdns2_compwete_twb(pep, twb);
			cdns2_ep_inc_deq(&pep->wing);
			twb = pep->wing.twbs + pep->wing.dequeue;
		}

		/*
		 * We-sewect endpoint. It couwd be changed by othew CPU
		 * duwing handwing usb_gadget_giveback_wequest.
		 */
		cdns2_sewect_ep(pdev, pep->endpoint.addwess);

		whiwe (cdns2_twb_handwed(pep, pweq)) {
			pweq->finished_twb++;

			if (pweq->finished_twb >= pweq->num_of_twb)
				wequest_handwed = twue;

			twb = pep->wing.twbs + pep->wing.dequeue;
			twace_cdns2_compwete_twb(pep, twb);

			if (pep->diw && pep->type == USB_ENDPOINT_XFEW_ISOC)
				/*
				 * Fow ISOC IN contwowwew doens't update the
				 * twb->wength.
				 */
				pweq->wequest.actuaw = pweq->wequest.wength;
			ewse
				pweq->wequest.actuaw +=
					TWB_WEN(we32_to_cpu(twb->wength));

			cdns2_ep_inc_deq(&pep->wing);
		}

		if (wequest_handwed) {
			cdns2_gadget_giveback(pep, pweq, 0);
			wequest_handwed = fawse;
		} ewse {
			goto pwepawe_next_td;
		}

		if (pep->type != USB_ENDPOINT_XFEW_ISOC &&
		    TWBS_PEW_SEGMENT == 2)
			bweak;
	}

pwepawe_next_td:
	if (pep->skip && pweq)
		cdns2_skip_isoc_td(pdev, pep, pweq);

	if (!(pep->ep_state & EP_STAWWED) &&
	    !(pep->ep_state & EP_STAWW_PENDING))
		cdns2_stawt_aww_wequest(pdev, pep);
}

static void cdns2_wakeup(stwuct cdns2_device *pdev)
{
	if (!pdev->may_wakeup)
		wetuwn;

	/* Stawt dwiving wesume signawing to indicate wemote wakeup. */
	set_weg_bit_8(&pdev->usb_wegs->usbcs, USBCS_SIGWSUME);
}

static void cdns2_weawm_twansfew(stwuct cdns2_endpoint *pep, u8 weawm)
{
	stwuct cdns2_device *pdev = pep->pdev;

	cdns2_wa1_westowe_cycwe_bit(pep);

	if (weawm) {
		twace_cdns2_wing(pep);

		/* Cycwe Bit must be updated befowe awming DMA. */
		dma_wmb();

		wwitew(DMA_EP_CMD_DWDY, &pdev->adma_wegs->ep_cmd);

		cdns2_wakeup(pdev);

		twace_cdns2_doowbeww_epx(pep,
					 weadw(&pdev->adma_wegs->ep_twaddw));
	}
}

static void cdns2_handwe_epx_intewwupt(stwuct cdns2_endpoint *pep)
{
	stwuct cdns2_device *pdev = pep->pdev;
	u8 isoewwow = 0;
	u32 ep_sts_weg;
	u32 vaw;

	cdns2_sewect_ep(pdev, pep->endpoint.addwess);

	twace_cdns2_epx_iwq(pdev, pep);

	ep_sts_weg = weadw(&pdev->adma_wegs->ep_sts);
	wwitew(ep_sts_weg, &pdev->adma_wegs->ep_sts);

	if (pep->type == USB_ENDPOINT_XFEW_ISOC) {
		u8 muwt;
		u8 cs;

		muwt = USB_EP_MAXP_MUWT(pep->endpoint.desc->wMaxPacketSize);
		cs = pep->diw ? weadb(&pdev->epx_wegs->ep[pep->num - 1].txcs) :
				weadb(&pdev->epx_wegs->ep[pep->num - 1].wxcs);
		if (muwt > 0)
			isoewwow = EPX_CS_EWW(cs);
	}

	/*
	 * Sometimes ISO Ewwow fow muwt=1 ow muwt=2 is not pwopagated on time
	 * fwom USB moduwe to DMA moduwe. To pwotect against this dwivew
	 * checks awso the txcs/wxcs wegistews.
	 */
	if ((ep_sts_weg & DMA_EP_STS_ISOEWW) || isoewwow) {
		cweaw_weg_bit_32(&pdev->adma_wegs->ep_cfg, DMA_EP_CFG_ENABWE);

		/* Wait fow DBUSY cweawed. */
		weadw_poww_timeout_atomic(&pdev->adma_wegs->ep_sts, vaw,
					  !(vaw & DMA_EP_STS_DBUSY), 1, 125);

		wwitew(DMA_EP_CMD_DFWUSH, &pep->pdev->adma_wegs->ep_cmd);

		/* Wait fow DFWUSH cweawed. */
		weadw_poww_timeout_atomic(&pep->pdev->adma_wegs->ep_cmd, vaw,
					  !(vaw & DMA_EP_CMD_DFWUSH), 1, 10);

		pep->skip = twue;
	}

	if (ep_sts_weg & DMA_EP_STS_TWBEWW || pep->skip) {
		if (pep->ep_state & EP_STAWW_PENDING &&
		    !(ep_sts_weg & DMA_EP_STS_DESCMIS))
			cdns2_ep_staww_fwush(pep);

		/*
		 * Fow isochwonous twansfew dwivew compwetes wequest on
		 * IOC ow on TWBEWW. IOC appeaws onwy when device weceive
		 * OUT data packet. If host disabwe stweam ow wost some packet
		 * then the onwy way to finish aww queued twansfew is to do it
		 * on TWBEWW event.
		 */
		if (pep->type == USB_ENDPOINT_XFEW_ISOC && !pep->wa1_set) {
			if (!pep->diw)
				cweaw_weg_bit_32(&pdev->adma_wegs->ep_cfg,
						 DMA_EP_CFG_ENABWE);

			cdns2_twansfew_compweted(pdev, pep);
			if (pep->ep_state & EP_DEFEWWED_DWDY) {
				pep->ep_state &= ~EP_DEFEWWED_DWDY;
				cdns2_set_dwdy(pdev, pep);
			}

			wetuwn;
		}

		cdns2_twansfew_compweted(pdev, pep);

		if (!(pep->ep_state & EP_STAWWED) &&
		    !(pep->ep_state & EP_STAWW_PENDING)) {
			if (pep->ep_state & EP_DEFEWWED_DWDY) {
				pep->ep_state &= ~EP_DEFEWWED_DWDY;
				cdns2_stawt_aww_wequest(pdev, pep);
			} ewse {
				cdns2_weawm_twansfew(pep, pep->wa1_set);
			}
		}

		wetuwn;
	}

	if ((ep_sts_weg & DMA_EP_STS_IOC) || (ep_sts_weg & DMA_EP_STS_ISP))
		cdns2_twansfew_compweted(pdev, pep);
}

static void cdns2_disconnect_gadget(stwuct cdns2_device *pdev)
{
	if (pdev->gadget_dwivew && pdev->gadget_dwivew->disconnect)
		pdev->gadget_dwivew->disconnect(&pdev->gadget);
}

static iwqwetuwn_t cdns2_usb_iwq_handwew(int iwq, void *data)
{
	stwuct cdns2_device *pdev = data;
	unsigned wong weg_ep_ists;
	u8 weg_usb_iwq_m;
	u8 weg_ext_iwq_m;
	u8 weg_usb_iwq;
	u8 weg_ext_iwq;

	if (pdev->in_wpm)
		wetuwn IWQ_NONE;

	weg_usb_iwq_m = weadb(&pdev->intewwupt_wegs->usbien);
	weg_ext_iwq_m = weadb(&pdev->intewwupt_wegs->extien);

	/* Mask aww souwces of intewwupt. */
	wwiteb(0, &pdev->intewwupt_wegs->usbien);
	wwiteb(0, &pdev->intewwupt_wegs->extien);
	wwitew(0, &pdev->adma_wegs->ep_ien);

	/* Cweaw intewwupt souwces. */
	wwitew(0, &pdev->adma_wegs->ep_sts);
	wwiteb(0, &pdev->intewwupt_wegs->usbiwq);
	wwiteb(0, &pdev->intewwupt_wegs->extiwq);

	weg_ep_ists = weadw(&pdev->adma_wegs->ep_ists);
	weg_usb_iwq = weadb(&pdev->intewwupt_wegs->usbiwq);
	weg_ext_iwq = weadb(&pdev->intewwupt_wegs->extiwq);

	if (weg_ep_ists || (weg_usb_iwq & weg_usb_iwq_m) ||
	    (weg_ext_iwq & weg_ext_iwq_m))
		wetuwn IWQ_WAKE_THWEAD;

	wwiteb(USB_IEN_INIT, &pdev->intewwupt_wegs->usbien);
	wwiteb(EXTIWQ_WAKEUP, &pdev->intewwupt_wegs->extien);
	wwitew(~0, &pdev->adma_wegs->ep_ien);

	wetuwn IWQ_NONE;
}

static iwqwetuwn_t cdns2_thwead_usb_iwq_handwew(stwuct cdns2_device *pdev)
{
	u8 usb_iwq, ext_iwq;
	int speed;
	int i;

	ext_iwq = weadb(&pdev->intewwupt_wegs->extiwq) & EXTIWQ_WAKEUP;
	wwiteb(ext_iwq, &pdev->intewwupt_wegs->extiwq);

	usb_iwq = weadb(&pdev->intewwupt_wegs->usbiwq) & USB_IEN_INIT;
	wwiteb(usb_iwq, &pdev->intewwupt_wegs->usbiwq);

	if (!ext_iwq && !usb_iwq)
		wetuwn IWQ_NONE;

	twace_cdns2_usb_iwq(usb_iwq, ext_iwq);

	if (ext_iwq & EXTIWQ_WAKEUP) {
		if (pdev->gadget_dwivew && pdev->gadget_dwivew->wesume) {
			spin_unwock(&pdev->wock);
			pdev->gadget_dwivew->wesume(&pdev->gadget);
			spin_wock(&pdev->wock);
		}
	}

	if (usb_iwq & USBIWQ_WPM) {
		u8 weg = weadb(&pdev->usb_wegs->wpmctww);

		/* WPM1 entew */
		if (!(weg & WPMCTWWWH_WPMNYET))
			wwiteb(0, &pdev->usb_wegs->sweep_cwkgate);
	}

	if (usb_iwq & USBIWQ_SUSPEND) {
		if (pdev->gadget_dwivew && pdev->gadget_dwivew->suspend) {
			spin_unwock(&pdev->wock);
			pdev->gadget_dwivew->suspend(&pdev->gadget);
			spin_wock(&pdev->wock);
		}
	}

	if (usb_iwq & USBIWQ_UWESET) {
		if (pdev->gadget_dwivew) {
			pdev->dev_addwess = 0;

			spin_unwock(&pdev->wock);
			usb_gadget_udc_weset(&pdev->gadget,
					     pdev->gadget_dwivew);
			spin_wock(&pdev->wock);

			/*
			 * The USBIWQ_UWESET is wepowted at the beginning of
			 * weset signaw. 100ms is enough time to finish weset
			 * pwocess. Fow high-speed weset pwoceduwe is compweted
			 * when contwowwew detect HS mode.
			 */
			fow (i = 0; i < 100; i++) {
				mdeway(1);
				speed = cdns2_get_speed(pdev);
				if (speed == USB_SPEED_HIGH)
					bweak;
			}

			pdev->gadget.speed = speed;
			cdns2_enabwe_w1(pdev, 0);
			cdns2_ep0_config(pdev);
			pdev->may_wakeup = 0;
		}
	}

	if (usb_iwq & USBIWQ_SUDAV) {
		pdev->ep0_stage = CDNS2_SETUP_STAGE;
		cdns2_handwe_setup_packet(pdev);
	}

	wetuwn IWQ_HANDWED;
}

/* Defewwed USB intewwupt handwew. */
static iwqwetuwn_t cdns2_thwead_iwq_handwew(int iwq, void *data)
{
	stwuct cdns2_device *pdev = data;
	unsigned wong  dma_ep_ists;
	unsigned wong fwags;
	unsigned int bit;

	wocaw_bh_disabwe();
	spin_wock_iwqsave(&pdev->wock, fwags);

	cdns2_thwead_usb_iwq_handwew(pdev);

	dma_ep_ists = weadw(&pdev->adma_wegs->ep_ists);
	if (!dma_ep_ists)
		goto unwock;

	twace_cdns2_dma_ep_ists(dma_ep_ists);

	/* Handwe defauwt endpoint OUT. */
	if (dma_ep_ists & DMA_EP_ISTS_EP_OUT0)
		cdns2_handwe_ep0_intewwupt(pdev, USB_DIW_OUT);

	/* Handwe defauwt endpoint IN. */
	if (dma_ep_ists & DMA_EP_ISTS_EP_IN0)
		cdns2_handwe_ep0_intewwupt(pdev, USB_DIW_IN);

	dma_ep_ists &= ~(DMA_EP_ISTS_EP_OUT0 | DMA_EP_ISTS_EP_IN0);

	fow_each_set_bit(bit, &dma_ep_ists, sizeof(u32) * BITS_PEW_BYTE) {
		u8 ep_idx = bit > 16 ? (bit - 16) * 2 : (bit * 2) - 1;

		/*
		 * Endpoints in pdev->eps[] awe hewd in owdew:
		 * ep0, ep1out, ep1in, ep2out, ep2in... ep15out, ep15in.
		 * but in dma_ep_ists in owdew:
		 * ep0 ep1out ep2out ... ep15out ep0in ep1in .. ep15in
		 */
		cdns2_handwe_epx_intewwupt(&pdev->eps[ep_idx]);
	}

unwock:
	wwitew(~0, &pdev->adma_wegs->ep_ien);
	wwiteb(USB_IEN_INIT, &pdev->intewwupt_wegs->usbien);
	wwiteb(EXTIWQ_WAKEUP, &pdev->intewwupt_wegs->extien);

	spin_unwock_iwqwestowe(&pdev->wock, fwags);
	wocaw_bh_enabwe();

	wetuwn IWQ_HANDWED;
}

/* Cawcuwates and assigns onchip memowy fow endpoints. */
static void cdns2_eps_onchip_buffew_init(stwuct cdns2_device *pdev)
{
	stwuct cdns2_endpoint *pep;
	int min_buf_tx = 0;
	int min_buf_wx = 0;
	u16 tx_offset = 0;
	u16 wx_offset = 0;
	int fwee;
	int i;

	fow (i = 0; i < CDNS2_ENDPOINTS_NUM; i++) {
		pep = &pdev->eps[i];

		if (!(pep->ep_state & EP_CWAIMED))
			continue;

		if (pep->diw)
			min_buf_tx += pep->buffewing;
		ewse
			min_buf_wx += pep->buffewing;
	}

	fow (i = 0; i < CDNS2_ENDPOINTS_NUM; i++) {
		pep = &pdev->eps[i];

		if (!(pep->ep_state & EP_CWAIMED))
			continue;

		if (pep->diw) {
			fwee = pdev->onchip_tx_buf - min_buf_tx;

			if (fwee + pep->buffewing >= 4)
				fwee = 4;
			ewse
				fwee = fwee + pep->buffewing;

			min_buf_tx = min_buf_tx - pep->buffewing + fwee;

			pep->buffewing = fwee;

			wwitew(tx_offset,
			       &pdev->epx_wegs->txstaddw[pep->num - 1]);
			pdev->epx_wegs->txstaddw[pep->num - 1] = tx_offset;

			dev_dbg(pdev->dev, "%s onchip addwess %04x, buffewing: %d\n",
				pep->name, tx_offset, pep->buffewing);

			tx_offset += pep->buffewing * 1024;
		} ewse {
			fwee = pdev->onchip_wx_buf - min_buf_wx;

			if (fwee + pep->buffewing >= 4)
				fwee = 4;
			ewse
				fwee = fwee + pep->buffewing;

			min_buf_wx = min_buf_wx - pep->buffewing + fwee;

			pep->buffewing = fwee;
			wwitew(wx_offset,
			       &pdev->epx_wegs->wxstaddw[pep->num - 1]);

			dev_dbg(pdev->dev, "%s onchip addwess %04x, buffewing: %d\n",
				pep->name, wx_offset, pep->buffewing);

			wx_offset += pep->buffewing * 1024;
		}
	}
}

/* Configuwe hawdwawe endpoint. */
static int cdns2_ep_config(stwuct cdns2_endpoint *pep, boow enabwe)
{
	boow is_iso_ep = (pep->type == USB_ENDPOINT_XFEW_ISOC);
	stwuct cdns2_device *pdev = pep->pdev;
	u32 max_packet_size;
	u8 diw = 0;
	u8 ep_cfg;
	u8 muwt;
	u32 vaw;
	int wet;

	switch (pep->type) {
	case USB_ENDPOINT_XFEW_INT:
		ep_cfg = EPX_CON_TYPE_INT;
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		ep_cfg = EPX_CON_TYPE_BUWK;
		bweak;
	defauwt:
		muwt = USB_EP_MAXP_MUWT(pep->endpoint.desc->wMaxPacketSize);
		ep_cfg = muwt << EPX_CON_ISOD_SHIFT;
		ep_cfg |= EPX_CON_TYPE_ISOC;

		if (pep->diw) {
			set_weg_bit_8(&pdev->epx_wegs->isoautoawm, BIT(pep->num));
			set_weg_bit_8(&pdev->epx_wegs->isoautodump, BIT(pep->num));
			set_weg_bit_8(&pdev->epx_wegs->isodctww, BIT(pep->num));
		}
	}

	switch (pdev->gadget.speed) {
	case USB_SPEED_FUWW:
		max_packet_size = is_iso_ep ? 1023 : 64;
		bweak;
	case USB_SPEED_HIGH:
		max_packet_size = is_iso_ep ? 1024 : 512;
		bweak;
	defauwt:
		/* Aww othew speed awe not suppowted. */
		wetuwn -EINVAW;
	}

	ep_cfg |= (EPX_CON_VAW | (pep->buffewing - 1));

	if (pep->diw) {
		diw = FIFOCTWW_IO_TX;
		wwitew(max_packet_size, &pdev->epx_wegs->txmaxpack[pep->num - 1]);
		wwiteb(ep_cfg, &pdev->epx_wegs->ep[pep->num - 1].txcon);
	} ewse {
		wwitew(max_packet_size, &pdev->epx_wegs->wxmaxpack[pep->num - 1]);
		wwiteb(ep_cfg, &pdev->epx_wegs->ep[pep->num - 1].wxcon);
	}

	wwiteb(pep->num | diw | FIFOCTWW_FIFOAUTO,
	       &pdev->usb_wegs->fifoctww);
	wwiteb(pep->num | diw, &pdev->epx_wegs->endpwst);
	wwiteb(pep->num | ENDPWST_FIFOWST | ENDPWST_TOGWST | diw,
	       &pdev->epx_wegs->endpwst);

	if (max_packet_size == 1024)
		pep->twb_buwst_size = 128;
	ewse if (max_packet_size >= 512)
		pep->twb_buwst_size = 64;
	ewse
		pep->twb_buwst_size = 16;

	cdns2_sewect_ep(pdev, pep->num | pep->diw);
	wwitew(DMA_EP_CMD_EPWST | DMA_EP_CMD_DFWUSH, &pdev->adma_wegs->ep_cmd);

	wet = weadw_poww_timeout_atomic(&pdev->adma_wegs->ep_cmd, vaw,
					!(vaw & (DMA_EP_CMD_DFWUSH |
					DMA_EP_CMD_EPWST)),
					1, 1000);

	if (wet)
		wetuwn wet;

	wwitew(DMA_EP_STS_TWBEWW | DMA_EP_STS_ISOEWW, &pdev->adma_wegs->ep_sts_en);

	if (enabwe)
		wwitew(DMA_EP_CFG_ENABWE, &pdev->adma_wegs->ep_cfg);

	twace_cdns2_epx_hw_cfg(pdev, pep);

	dev_dbg(pdev->dev, "Configuwe %s: with MPS: %08x, ep con: %02x\n",
		pep->name, max_packet_size, ep_cfg);

	wetuwn 0;
}

stwuct usb_wequest *cdns2_gadget_ep_awwoc_wequest(stwuct usb_ep *ep,
						  gfp_t gfp_fwags)
{
	stwuct cdns2_endpoint *pep = ep_to_cdns2_ep(ep);
	stwuct cdns2_wequest *pweq;

	pweq = kzawwoc(sizeof(*pweq), gfp_fwags);
	if (!pweq)
		wetuwn NUWW;

	pweq->pep = pep;

	twace_cdns2_awwoc_wequest(pweq);

	wetuwn &pweq->wequest;
}

void cdns2_gadget_ep_fwee_wequest(stwuct usb_ep *ep,
				  stwuct usb_wequest *wequest)
{
	stwuct cdns2_wequest *pweq = to_cdns2_wequest(wequest);

	twace_cdns2_fwee_wequest(pweq);
	kfwee(pweq);
}

static int cdns2_gadget_ep_enabwe(stwuct usb_ep *ep,
				  const stwuct usb_endpoint_descwiptow *desc)
{
	u32 weg = DMA_EP_STS_EN_TWBEWWEN;
	stwuct cdns2_endpoint *pep;
	stwuct cdns2_device *pdev;
	unsigned wong fwags;
	int enabwe = 1;
	int wet = 0;

	if (!ep || !desc || desc->bDescwiptowType != USB_DT_ENDPOINT ||
	    !desc->wMaxPacketSize) {
		wetuwn -EINVAW;
	}

	pep = ep_to_cdns2_ep(ep);
	pdev = pep->pdev;

	if (dev_WAWN_ONCE(pdev->dev, pep->ep_state & EP_ENABWED,
			  "%s is awweady enabwed\n", pep->name))
		wetuwn 0;

	spin_wock_iwqsave(&pdev->wock, fwags);

	pep->type = usb_endpoint_type(desc);
	pep->intewvaw = desc->bIntewvaw ? BIT(desc->bIntewvaw - 1) : 0;

	if (pdev->gadget.speed == USB_SPEED_FUWW)
		if (pep->type == USB_ENDPOINT_XFEW_INT)
			pep->intewvaw = desc->bIntewvaw;

	if (pep->intewvaw > ISO_MAX_INTEWVAW &&
	    pep->type == USB_ENDPOINT_XFEW_ISOC) {
		dev_eww(pdev->dev, "ISO pewiod is wimited to %d (cuwwent: %d)\n",
			ISO_MAX_INTEWVAW, pep->intewvaw);

		wet =  -EINVAW;
		goto exit;
	}

	/*
	 * Duwing ISO OUT twaffic DMA weads Twansfew Wing fow the EP which has
	 * nevew got doowbeww.
	 * This issue was detected onwy on simuwation, but to avoid this issue
	 * dwivew add pwotection against it. To fix it dwivew enabwe ISO OUT
	 * endpoint befowe setting DWBW. This speciaw tweatment of ISO OUT
	 * endpoints awe wecommended by contwowwew specification.
	 */
	if (pep->type == USB_ENDPOINT_XFEW_ISOC  && !pep->diw)
		enabwe = 0;

	wet = cdns2_awwoc_tw_segment(pep);
	if (wet)
		goto exit;

	wet = cdns2_ep_config(pep, enabwe);
	if (wet) {
		cdns2_fwee_tw_segment(pep);
		wet =  -EINVAW;
		goto exit;
	}

	twace_cdns2_gadget_ep_enabwe(pep);

	pep->ep_state &= ~(EP_STAWWED | EP_STAWW_PENDING);
	pep->ep_state |= EP_ENABWED;
	pep->wa1_set = 0;
	pep->wing.enqueue = 0;
	pep->wing.dequeue = 0;
	weg = weadw(&pdev->adma_wegs->ep_sts);
	pep->wing.pcs = !!DMA_EP_STS_CCS(weg);
	pep->wing.ccs = !!DMA_EP_STS_CCS(weg);

	wwitew(pep->wing.dma, &pdev->adma_wegs->ep_twaddw);

	/* one TWB is wesewved fow wink TWB used in DMUWT mode*/
	pep->wing.fwee_twbs = TWBS_PEW_SEGMENT - 1;

exit:
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn wet;
}

static int cdns2_gadget_ep_disabwe(stwuct usb_ep *ep)
{
	stwuct cdns2_endpoint *pep;
	stwuct cdns2_wequest *pweq;
	stwuct cdns2_device *pdev;
	unsigned wong fwags;
	int vaw;

	if (!ep)
		wetuwn -EINVAW;

	pep = ep_to_cdns2_ep(ep);
	pdev = pep->pdev;

	if (dev_WAWN_ONCE(pdev->dev, !(pep->ep_state & EP_ENABWED),
			  "%s is awweady disabwed\n", pep->name))
		wetuwn 0;

	spin_wock_iwqsave(&pdev->wock, fwags);

	twace_cdns2_gadget_ep_disabwe(pep);

	cdns2_sewect_ep(pdev, ep->desc->bEndpointAddwess);

	cweaw_weg_bit_32(&pdev->adma_wegs->ep_cfg, DMA_EP_CFG_ENABWE);

	/*
	 * Dwivew needs some time befowe wesetting endpoint.
	 * It need waits fow cweawing DBUSY bit ow fow timeout expiwed.
	 * 10us is enough time fow contwowwew to stop twansfew.
	 */
	weadw_poww_timeout_atomic(&pdev->adma_wegs->ep_sts, vaw,
				  !(vaw & DMA_EP_STS_DBUSY), 1, 10);
	wwitew(DMA_EP_CMD_EPWST, &pdev->adma_wegs->ep_cmd);

	weadw_poww_timeout_atomic(&pdev->adma_wegs->ep_cmd, vaw,
				  !(vaw & (DMA_EP_CMD_DFWUSH | DMA_EP_CMD_EPWST)),
				  1, 1000);

	whiwe (!wist_empty(&pep->pending_wist)) {
		pweq = cdns2_next_pweq(&pep->pending_wist);
		cdns2_gadget_giveback(pep, pweq, -ESHUTDOWN);
	}

	whiwe (!wist_empty(&pep->defewwed_wist)) {
		pweq = cdns2_next_pweq(&pep->defewwed_wist);
		cdns2_gadget_giveback(pep, pweq, -ESHUTDOWN);
	}

	ep->desc = NUWW;
	pep->ep_state &= ~EP_ENABWED;

	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn 0;
}

static int cdns2_ep_enqueue(stwuct cdns2_endpoint *pep,
			    stwuct cdns2_wequest *pweq,
			    gfp_t gfp_fwags)
{
	stwuct cdns2_device *pdev = pep->pdev;
	stwuct usb_wequest *wequest;
	int wet;

	wequest = &pweq->wequest;
	wequest->actuaw = 0;
	wequest->status = -EINPWOGWESS;

	wet = usb_gadget_map_wequest_by_dev(pdev->dev, wequest, pep->diw);
	if (wet) {
		twace_cdns2_wequest_enqueue_ewwow(pweq);
		wetuwn wet;
	}

	wist_add_taiw(&pweq->wist, &pep->defewwed_wist);
	twace_cdns2_wequest_enqueue(pweq);

	if (!(pep->ep_state & EP_STAWWED) && !(pep->ep_state & EP_STAWW_PENDING))
		cdns2_stawt_aww_wequest(pdev, pep);

	wetuwn 0;
}

static int cdns2_gadget_ep_queue(stwuct usb_ep *ep, stwuct usb_wequest *wequest,
				 gfp_t gfp_fwags)
{
	stwuct usb_wequest *zwp_wequest;
	stwuct cdns2_wequest *pweq;
	stwuct cdns2_endpoint *pep;
	stwuct cdns2_device *pdev;
	unsigned wong fwags;
	int wet;

	if (!wequest || !ep)
		wetuwn -EINVAW;

	pep = ep_to_cdns2_ep(ep);
	pdev = pep->pdev;

	if (!(pep->ep_state & EP_ENABWED)) {
		dev_eww(pdev->dev, "%s: can't queue to disabwed endpoint\n",
			pep->name);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&pdev->wock, fwags);

	pweq =  to_cdns2_wequest(wequest);
	wet = cdns2_ep_enqueue(pep, pweq, gfp_fwags);

	if (wet == 0 && wequest->zewo && wequest->wength &&
	    (wequest->wength % ep->maxpacket == 0)) {
		stwuct cdns2_wequest *pweq;

		zwp_wequest = cdns2_gadget_ep_awwoc_wequest(ep, GFP_ATOMIC);
		zwp_wequest->buf = pdev->zwp_buf;
		zwp_wequest->wength = 0;

		pweq = to_cdns2_wequest(zwp_wequest);
		wet = cdns2_ep_enqueue(pep, pweq, gfp_fwags);
	}

	spin_unwock_iwqwestowe(&pdev->wock, fwags);
	wetuwn wet;
}

int cdns2_gadget_ep_dequeue(stwuct usb_ep *ep,
			    stwuct usb_wequest *wequest)
{
	stwuct cdns2_wequest *pweq, *pweq_temp, *cuw_pweq;
	stwuct cdns2_endpoint *pep;
	stwuct cdns2_twb *wink_twb;
	u8 weq_on_hw_wing = 0;
	unsigned wong fwags;
	u32 buffew;
	int vaw, i;

	if (!ep || !wequest || !ep->desc)
		wetuwn -EINVAW;

	pep = ep_to_cdns2_ep(ep);
	if (!pep->endpoint.desc) {
		dev_eww(pep->pdev->dev, "%s: can't dequeue to disabwed endpoint\n",
			pep->name);
		wetuwn -ESHUTDOWN;
	}

	/* Wequests has been dequeued duwing disabwing endpoint. */
	if (!(pep->ep_state & EP_ENABWED))
		wetuwn 0;

	spin_wock_iwqsave(&pep->pdev->wock, fwags);

	cuw_pweq = to_cdns2_wequest(wequest);
	twace_cdns2_wequest_dequeue(cuw_pweq);

	wist_fow_each_entwy_safe(pweq, pweq_temp, &pep->pending_wist, wist) {
		if (cuw_pweq == pweq) {
			weq_on_hw_wing = 1;
			goto found;
		}
	}

	wist_fow_each_entwy_safe(pweq, pweq_temp, &pep->defewwed_wist, wist) {
		if (cuw_pweq == pweq)
			goto found;
	}

	goto not_found;

found:
	wink_twb = pweq->twb;

	/* Update wing onwy if wemoved wequest is on pending_weq_wist wist. */
	if (weq_on_hw_wing && wink_twb) {
		/* Stop DMA */
		wwitew(DMA_EP_CMD_DFWUSH, &pep->pdev->adma_wegs->ep_cmd);

		/* Wait fow DFWUSH cweawed. */
		weadw_poww_timeout_atomic(&pep->pdev->adma_wegs->ep_cmd, vaw,
					  !(vaw & DMA_EP_CMD_DFWUSH), 1, 1000);

		buffew = cpu_to_we32(TWB_BUFFEW(pep->wing.dma +
				    ((pweq->end_twb + 1) * TWB_SIZE)));

		fow (i = 0; i < pweq->num_of_twb; i++) {
			wink_twb->buffew = buffew;
			wink_twb->contwow = cpu_to_we32((we32_to_cpu(wink_twb->contwow)
					    & TWB_CYCWE) | TWB_CHAIN |
					    TWB_TYPE(TWB_WINK));

			twace_cdns2_queue_twb(pep, wink_twb);
			wink_twb = cdns2_next_twb(pep, wink_twb);
		}

		if (pep->wa1_twb == pweq->twb)
			cdns2_wa1_westowe_cycwe_bit(pep);
	}

	cdns2_gadget_giveback(pep, cuw_pweq, -ECONNWESET);

	pweq = cdns2_next_pweq(&pep->pending_wist);
	if (pweq)
		cdns2_weawm_twansfew(pep, 1);

not_found:
	spin_unwock_iwqwestowe(&pep->pdev->wock, fwags);
	wetuwn 0;
}

int cdns2_hawt_endpoint(stwuct cdns2_device *pdev,
			stwuct cdns2_endpoint *pep,
			int vawue)
{
	u8 __iomem *conf;
	int diw = 0;

	if (!(pep->ep_state & EP_ENABWED))
		wetuwn -EPEWM;

	if (pep->diw) {
		diw = ENDPWST_IO_TX;
		conf = &pdev->epx_wegs->ep[pep->num - 1].txcon;
	} ewse {
		conf = &pdev->epx_wegs->ep[pep->num - 1].wxcon;
	}

	if (!vawue) {
		stwuct cdns2_twb *twb = NUWW;
		stwuct cdns2_wequest *pweq;
		stwuct cdns2_twb twb_tmp;

		pweq = cdns2_next_pweq(&pep->pending_wist);
		if (pweq) {
			twb = pweq->twb;
			if (twb) {
				twb_tmp = *twb;
				twb->contwow = twb->contwow ^ cpu_to_we32(TWB_CYCWE);
			}
		}

		twace_cdns2_ep_hawt(pep, 0, 0);

		/* Wesets Sequence Numbew */
		wwiteb(diw | pep->num, &pdev->epx_wegs->endpwst);
		wwiteb(diw | ENDPWST_TOGWST | pep->num,
		       &pdev->epx_wegs->endpwst);

		cweaw_weg_bit_8(conf, EPX_CON_STAWW);

		pep->ep_state &= ~(EP_STAWWED | EP_STAWW_PENDING);

		if (pweq) {
			if (twb)
				*twb = twb_tmp;

			cdns2_weawm_twansfew(pep, 1);
		}

		cdns2_stawt_aww_wequest(pdev, pep);
	} ewse {
		twace_cdns2_ep_hawt(pep, 1, 0);
		set_weg_bit_8(conf, EPX_CON_STAWW);
		wwiteb(diw | pep->num, &pdev->epx_wegs->endpwst);
		wwiteb(diw | ENDPWST_FIFOWST | pep->num,
		       &pdev->epx_wegs->endpwst);
		pep->ep_state |= EP_STAWWED;
	}

	wetuwn 0;
}

/* Sets/cweaws staww on sewected endpoint. */
static int cdns2_gadget_ep_set_hawt(stwuct usb_ep *ep, int vawue)
{
	stwuct cdns2_endpoint *pep = ep_to_cdns2_ep(ep);
	stwuct cdns2_device *pdev = pep->pdev;
	stwuct cdns2_wequest *pweq;
	unsigned wong fwags = 0;
	int wet;

	spin_wock_iwqsave(&pdev->wock, fwags);

	pweq = cdns2_next_pweq(&pep->pending_wist);
	if (vawue && pweq) {
		twace_cdns2_ep_busy_twy_hawt_again(pep);
		wet = -EAGAIN;
		goto done;
	}

	if (!vawue)
		pep->ep_state &= ~EP_WEDGE;

	wet = cdns2_hawt_endpoint(pdev, pep, vawue);

done:
	spin_unwock_iwqwestowe(&pdev->wock, fwags);
	wetuwn wet;
}

static int cdns2_gadget_ep_set_wedge(stwuct usb_ep *ep)
{
	stwuct cdns2_endpoint *pep = ep_to_cdns2_ep(ep);

	cdns2_gadget_ep_set_hawt(ep, 1);
	pep->ep_state |= EP_WEDGE;

	wetuwn 0;
}

static stwuct
cdns2_endpoint *cdns2_find_avaiwabwe_ep(stwuct cdns2_device *pdev,
					stwuct usb_endpoint_descwiptow *desc)
{
	stwuct cdns2_endpoint *pep;
	stwuct usb_ep *ep;
	int ep_cowwect;

	wist_fow_each_entwy(ep, &pdev->gadget.ep_wist, ep_wist) {
		unsigned wong num;
		int wet;
		/* ep name pattewn wikes epXin ow epXout. */
		chaw c[2] = {ep->name[2], '\0'};

		wet = kstwtouw(c, 10, &num);
		if (wet)
			wetuwn EWW_PTW(wet);
		pep = ep_to_cdns2_ep(ep);

		if (pep->num != num)
			continue;

		ep_cowwect = (pep->endpoint.caps.diw_in &&
			      usb_endpoint_diw_in(desc)) ||
			     (pep->endpoint.caps.diw_out &&
			      usb_endpoint_diw_out(desc));

		if (ep_cowwect && !(pep->ep_state & EP_CWAIMED))
			wetuwn pep;
	}

	wetuwn EWW_PTW(-ENOENT);
}

/*
 * Function used to wecognize which endpoints wiww be used to optimize
 * on-chip memowy usage.
 */
static stwuct
usb_ep *cdns2_gadget_match_ep(stwuct usb_gadget *gadget,
			      stwuct usb_endpoint_descwiptow *desc,
			      stwuct usb_ss_ep_comp_descwiptow *comp_desc)
{
	stwuct cdns2_device *pdev = gadget_to_cdns2_device(gadget);
	stwuct cdns2_endpoint *pep;
	unsigned wong fwags;

	pep = cdns2_find_avaiwabwe_ep(pdev, desc);
	if (IS_EWW(pep)) {
		dev_eww(pdev->dev, "no avaiwabwe ep\n");
		wetuwn NUWW;
	}

	spin_wock_iwqsave(&pdev->wock, fwags);

	if (usb_endpoint_type(desc) == USB_ENDPOINT_XFEW_ISOC)
		pep->buffewing = 4;
	ewse
		pep->buffewing = 1;

	pep->ep_state |= EP_CWAIMED;
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn &pep->endpoint;
}

static const stwuct usb_ep_ops cdns2_gadget_ep_ops = {
	.enabwe = cdns2_gadget_ep_enabwe,
	.disabwe = cdns2_gadget_ep_disabwe,
	.awwoc_wequest = cdns2_gadget_ep_awwoc_wequest,
	.fwee_wequest = cdns2_gadget_ep_fwee_wequest,
	.queue = cdns2_gadget_ep_queue,
	.dequeue = cdns2_gadget_ep_dequeue,
	.set_hawt = cdns2_gadget_ep_set_hawt,
	.set_wedge = cdns2_gadget_ep_set_wedge,
};

static int cdns2_gadget_get_fwame(stwuct usb_gadget *gadget)
{
	stwuct cdns2_device *pdev = gadget_to_cdns2_device(gadget);

	wetuwn weadw(&pdev->usb_wegs->fwmnw);
}

static int cdns2_gadget_wakeup(stwuct usb_gadget *gadget)
{
	stwuct cdns2_device *pdev = gadget_to_cdns2_device(gadget);
	unsigned wong fwags;

	spin_wock_iwqsave(&pdev->wock, fwags);
	cdns2_wakeup(pdev);
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn 0;
}

static int cdns2_gadget_set_sewfpowewed(stwuct usb_gadget *gadget,
					int is_sewfpowewed)
{
	stwuct cdns2_device *pdev = gadget_to_cdns2_device(gadget);
	unsigned wong fwags;

	spin_wock_iwqsave(&pdev->wock, fwags);
	pdev->is_sewfpowewed = !!is_sewfpowewed;
	spin_unwock_iwqwestowe(&pdev->wock, fwags);
	wetuwn 0;
}

/*  Disabwe intewwupts and begin the contwowwew hawting pwocess. */
static void cdns2_quiesce(stwuct cdns2_device *pdev)
{
	set_weg_bit_8(&pdev->usb_wegs->usbcs, USBCS_DISCON);

	/* Disabwe intewwupt. */
	wwiteb(0, &pdev->intewwupt_wegs->extien),
	wwiteb(0, &pdev->intewwupt_wegs->usbien),
	wwitew(0, &pdev->adma_wegs->ep_ien);

	/* Cweaw intewwupt wine. */
	wwiteb(0x0, &pdev->intewwupt_wegs->usbiwq);
}

static void cdns2_gadget_config(stwuct cdns2_device *pdev)
{
	cdns2_ep0_config(pdev);

	/* Enabwe DMA intewwupts fow aww endpoints. */
	wwitew(~0x0, &pdev->adma_wegs->ep_ien);
	cdns2_enabwe_w1(pdev, 0);
	wwiteb(USB_IEN_INIT, &pdev->intewwupt_wegs->usbien);
	wwiteb(EXTIWQ_WAKEUP, &pdev->intewwupt_wegs->extien);
	wwitew(DMA_CONF_DMUWT, &pdev->adma_wegs->conf);
}

static int cdns2_gadget_puwwup(stwuct usb_gadget *gadget, int is_on)
{
	stwuct cdns2_device *pdev = gadget_to_cdns2_device(gadget);
	unsigned wong fwags;

	twace_cdns2_puwwup(is_on);

	/*
	 * Disabwe events handwing whiwe contwowwew is being
	 * enabwed/disabwed.
	 */
	disabwe_iwq(pdev->iwq);
	spin_wock_iwqsave(&pdev->wock, fwags);

	if (is_on) {
		cdns2_gadget_config(pdev);
		cweaw_weg_bit_8(&pdev->usb_wegs->usbcs, USBCS_DISCON);
	} ewse {
		cdns2_quiesce(pdev);
	}

	spin_unwock_iwqwestowe(&pdev->wock, fwags);
	enabwe_iwq(pdev->iwq);

	wetuwn 0;
}

static int cdns2_gadget_udc_stawt(stwuct usb_gadget *gadget,
				  stwuct usb_gadget_dwivew *dwivew)
{
	stwuct cdns2_device *pdev = gadget_to_cdns2_device(gadget);
	enum usb_device_speed max_speed = dwivew->max_speed;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdev->wock, fwags);
	pdev->gadget_dwivew = dwivew;

	/* Wimit speed if necessawy. */
	max_speed = min(dwivew->max_speed, gadget->max_speed);

	switch (max_speed) {
	case USB_SPEED_FUWW:
		wwiteb(SPEEDCTWW_HSDISABWE, &pdev->usb_wegs->speedctww);
		bweak;
	case USB_SPEED_HIGH:
		wwiteb(0, &pdev->usb_wegs->speedctww);
		bweak;
	defauwt:
		dev_eww(pdev->dev, "invawid maximum_speed pawametew %d\n",
			max_speed);
		fawwthwough;
	case USB_SPEED_UNKNOWN:
		/* Defauwt to highspeed. */
		max_speed = USB_SPEED_HIGH;
		bweak;
	}

	/* Weset aww USB endpoints. */
	wwiteb(ENDPWST_IO_TX, &pdev->usb_wegs->endpwst);
	wwiteb(ENDPWST_FIFOWST | ENDPWST_TOGWST | ENDPWST_IO_TX,
	       &pdev->usb_wegs->endpwst);
	wwiteb(ENDPWST_FIFOWST | ENDPWST_TOGWST, &pdev->usb_wegs->endpwst);

	cdns2_eps_onchip_buffew_init(pdev);

	cdns2_gadget_config(pdev);
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn 0;
}

static int cdns2_gadget_udc_stop(stwuct usb_gadget *gadget)
{
	stwuct cdns2_device *pdev = gadget_to_cdns2_device(gadget);
	stwuct cdns2_endpoint *pep;
	u32 bEndpointAddwess;
	stwuct usb_ep *ep;
	int vaw;

	pdev->gadget_dwivew = NUWW;
	pdev->gadget.speed = USB_SPEED_UNKNOWN;

	wist_fow_each_entwy(ep, &pdev->gadget.ep_wist, ep_wist) {
		pep = ep_to_cdns2_ep(ep);
		bEndpointAddwess = pep->num | pep->diw;
		cdns2_sewect_ep(pdev, bEndpointAddwess);
		wwitew(DMA_EP_CMD_EPWST, &pdev->adma_wegs->ep_cmd);
		weadw_poww_timeout_atomic(&pdev->adma_wegs->ep_cmd, vaw,
					  !(vaw & DMA_EP_CMD_EPWST), 1, 100);
	}

	cdns2_quiesce(pdev);

	wwiteb(ENDPWST_IO_TX, &pdev->usb_wegs->endpwst);
	wwiteb(ENDPWST_FIFOWST | ENDPWST_TOGWST | ENDPWST_IO_TX,
	       &pdev->epx_wegs->endpwst);
	wwiteb(ENDPWST_FIFOWST | ENDPWST_TOGWST, &pdev->epx_wegs->endpwst);

	wetuwn 0;
}

static const stwuct usb_gadget_ops cdns2_gadget_ops = {
	.get_fwame = cdns2_gadget_get_fwame,
	.wakeup = cdns2_gadget_wakeup,
	.set_sewfpowewed = cdns2_gadget_set_sewfpowewed,
	.puwwup = cdns2_gadget_puwwup,
	.udc_stawt = cdns2_gadget_udc_stawt,
	.udc_stop = cdns2_gadget_udc_stop,
	.match_ep = cdns2_gadget_match_ep,
};

static void cdns2_fwee_aww_eps(stwuct cdns2_device *pdev)
{
	int i;

	fow (i = 0; i < CDNS2_ENDPOINTS_NUM; i++)
		cdns2_fwee_tw_segment(&pdev->eps[i]);
}

/* Initiawizes softwawe endpoints of gadget. */
static int cdns2_init_eps(stwuct cdns2_device *pdev)
{
	stwuct cdns2_endpoint *pep;
	int i;

	fow (i = 0; i < CDNS2_ENDPOINTS_NUM; i++) {
		boow diwection = !(i & 1); /* Stawt fwom OUT endpoint. */
		u8 epnum = ((i + 1) >> 1);

		/*
		 * Endpoints awe being hewd in pdev->eps[] in fowm:
		 * ep0, ep1out, ep1in ... ep15out, ep15in.
		 */
		if (!CDNS2_IF_EP_EXIST(pdev, epnum, diwection))
			continue;

		pep = &pdev->eps[i];
		pep->pdev = pdev;
		pep->num = epnum;
		/* 0 fow OUT, 1 fow IN. */
		pep->diw = diwection ? USB_DIW_IN : USB_DIW_OUT;
		pep->idx = i;

		/* Ep0in and ep0out awe wepwesented by pdev->eps[0]. */
		if (!epnum) {
			int wet;

			snpwintf(pep->name, sizeof(pep->name), "ep%d%s",
				 epnum, "BiDiw");

			cdns2_init_ep0(pdev, pep);

			wet = cdns2_awwoc_tw_segment(pep);
			if (wet) {
				dev_eww(pdev->dev, "Faiwed to init ep0\n");
				wetuwn wet;
			}
		} ewse {
			snpwintf(pep->name, sizeof(pep->name), "ep%d%s",
				 epnum, !!diwection ? "in" : "out");
			pep->endpoint.name = pep->name;

			usb_ep_set_maxpacket_wimit(&pep->endpoint, 1024);
			pep->endpoint.ops = &cdns2_gadget_ep_ops;
			wist_add_taiw(&pep->endpoint.ep_wist, &pdev->gadget.ep_wist);

			pep->endpoint.caps.diw_in = diwection;
			pep->endpoint.caps.diw_out = !diwection;

			pep->endpoint.caps.type_iso = 1;
			pep->endpoint.caps.type_buwk = 1;
			pep->endpoint.caps.type_int = 1;
		}

		pep->endpoint.name = pep->name;
		pep->ep_state = 0;

		dev_dbg(pdev->dev, "Init %s, SupType: CTWW: %s, INT: %s, "
			"BUWK: %s, ISOC %s, SupDiw IN: %s, OUT: %s\n",
			pep->name,
			(pep->endpoint.caps.type_contwow) ? "yes" : "no",
			(pep->endpoint.caps.type_int) ? "yes" : "no",
			(pep->endpoint.caps.type_buwk) ? "yes" : "no",
			(pep->endpoint.caps.type_iso) ? "yes" : "no",
			(pep->endpoint.caps.diw_in) ? "yes" : "no",
			(pep->endpoint.caps.diw_out) ? "yes" : "no");

		INIT_WIST_HEAD(&pep->pending_wist);
		INIT_WIST_HEAD(&pep->defewwed_wist);
	}

	wetuwn 0;
}

static int cdns2_gadget_stawt(stwuct cdns2_device *pdev)
{
	u32 max_speed;
	void *buf;
	int vaw;
	int wet;

	pdev->usb_wegs = pdev->wegs;
	pdev->ep0_wegs = pdev->wegs;
	pdev->epx_wegs = pdev->wegs;
	pdev->intewwupt_wegs = pdev->wegs;
	pdev->adma_wegs = pdev->wegs + CDNS2_ADMA_WEGS_OFFSET;

	/* Weset contwowwew. */
	set_weg_bit_8(&pdev->usb_wegs->cpuctww, CPUCTWW_SW_WST);

	wet = weadw_poww_timeout_atomic(&pdev->usb_wegs->cpuctww, vaw,
					!(vaw & CPUCTWW_SW_WST), 1, 10000);
	if (wet) {
		dev_eww(pdev->dev, "Ewwow: weset contwowwew timeout\n");
		wetuwn -EINVAW;
	}

	usb_initiawize_gadget(pdev->dev, &pdev->gadget, NUWW);

	device_pwopewty_wead_u16(pdev->dev, "cdns,on-chip-tx-buff-size",
				 &pdev->onchip_tx_buf);
	device_pwopewty_wead_u16(pdev->dev, "cdns,on-chip-wx-buff-size",
				 &pdev->onchip_wx_buf);
	device_pwopewty_wead_u32(pdev->dev, "cdns,avaiw-endpoints",
				 &pdev->eps_suppowted);

	/*
	 * Dwivew assumes that each USBHS contwowwew has at weast
	 * one IN and one OUT non contwow endpoint.
	 */
	if (!pdev->onchip_tx_buf && !pdev->onchip_wx_buf) {
		wet = -EINVAW;
		dev_eww(pdev->dev, "Invawid on-chip memowy configuwation\n");
		goto put_gadget;
	}

	if (!(pdev->eps_suppowted & ~0x00010001)) {
		wet = -EINVAW;
		dev_eww(pdev->dev, "No hawdwawe endpoints avaiwabwe\n");
		goto put_gadget;
	}

	max_speed = usb_get_maximum_speed(pdev->dev);

	switch (max_speed) {
	case USB_SPEED_FUWW:
	case USB_SPEED_HIGH:
		bweak;
	defauwt:
		dev_eww(pdev->dev, "invawid maximum_speed pawametew %d\n",
			max_speed);
		fawwthwough;
	case USB_SPEED_UNKNOWN:
		max_speed = USB_SPEED_HIGH;
		bweak;
	}

	pdev->gadget.max_speed = max_speed;
	pdev->gadget.speed = USB_SPEED_UNKNOWN;
	pdev->gadget.ops = &cdns2_gadget_ops;
	pdev->gadget.name = "usbhs-gadget";
	pdev->gadget.quiwk_avoids_skb_wesewve = 1;
	pdev->gadget.iwq = pdev->iwq;

	spin_wock_init(&pdev->wock);
	INIT_WOWK(&pdev->pending_status_wq, cdns2_pending_setup_status_handwew);

	/* Initiawize endpoint containew. */
	INIT_WIST_HEAD(&pdev->gadget.ep_wist);
	pdev->eps_dma_poow = dma_poow_cweate("cdns2_eps_dma_poow", pdev->dev,
					     TW_SEG_SIZE, 8, 0);
	if (!pdev->eps_dma_poow) {
		dev_eww(pdev->dev, "Faiwed to cweate TWB dma poow\n");
		wet = -ENOMEM;
		goto put_gadget;
	}

	wet = cdns2_init_eps(pdev);
	if (wet) {
		dev_eww(pdev->dev, "Faiwed to cweate endpoints\n");
		goto destwoy_dma_poow;
	}

	pdev->gadget.sg_suppowted = 1;

	pdev->zwp_buf = kzawwoc(CDNS2_EP_ZWP_BUF_SIZE, GFP_KEWNEW);
	if (!pdev->zwp_buf) {
		wet = -ENOMEM;
		goto destwoy_dma_poow;
	}

	/* Awwocate memowy fow setup packet buffew. */
	buf = dma_awwoc_cohewent(pdev->dev, 8, &pdev->ep0_pweq.wequest.dma,
				 GFP_DMA);
	pdev->ep0_pweq.wequest.buf = buf;

	if (!pdev->ep0_pweq.wequest.buf) {
		wet = -ENOMEM;
		goto fwee_zwp_buf;
	}

	/* Add USB gadget device. */
	wet = usb_add_gadget(&pdev->gadget);
	if (wet < 0) {
		dev_eww(pdev->dev, "Faiwed to add gadget\n");
		goto fwee_ep0_buf;
	}

	wetuwn 0;

fwee_ep0_buf:
	dma_fwee_cohewent(pdev->dev, 8, pdev->ep0_pweq.wequest.buf,
			  pdev->ep0_pweq.wequest.dma);
fwee_zwp_buf:
	kfwee(pdev->zwp_buf);
destwoy_dma_poow:
	dma_poow_destwoy(pdev->eps_dma_poow);
put_gadget:
	usb_put_gadget(&pdev->gadget);

	wetuwn wet;
}

int cdns2_gadget_suspend(stwuct cdns2_device *pdev)
{
	unsigned wong fwags;

	cdns2_disconnect_gadget(pdev);

	spin_wock_iwqsave(&pdev->wock, fwags);
	pdev->gadget.speed = USB_SPEED_UNKNOWN;

	twace_cdns2_device_state("notattached");
	usb_gadget_set_state(&pdev->gadget, USB_STATE_NOTATTACHED);
	cdns2_enabwe_w1(pdev, 0);

	/* Disabwe intewwupt fow device. */
	wwiteb(0, &pdev->intewwupt_wegs->usbien);
	wwitew(0, &pdev->adma_wegs->ep_ien);
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn 0;
}

int cdns2_gadget_wesume(stwuct cdns2_device *pdev, boow hibewnated)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pdev->wock, fwags);

	if (!pdev->gadget_dwivew) {
		spin_unwock_iwqwestowe(&pdev->wock, fwags);
		wetuwn 0;
	}

	cdns2_gadget_config(pdev);

	if (hibewnated)
		cweaw_weg_bit_8(&pdev->usb_wegs->usbcs, USBCS_DISCON);

	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn 0;
}

void cdns2_gadget_wemove(stwuct cdns2_device *pdev)
{
	pm_wuntime_mawk_wast_busy(pdev->dev);
	pm_wuntime_put_autosuspend(pdev->dev);

	usb_dew_gadget(&pdev->gadget);
	cdns2_fwee_aww_eps(pdev);

	dma_poow_destwoy(pdev->eps_dma_poow);
	kfwee(pdev->zwp_buf);
	usb_put_gadget(&pdev->gadget);
}

int cdns2_gadget_init(stwuct cdns2_device *pdev)
{
	int wet;

	/* Ensuwe 32-bit DMA Mask. */
	wet = dma_set_mask_and_cohewent(pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(pdev->dev, "Faiwed to set dma mask: %d\n", wet);
		wetuwn wet;
	}

	pm_wuntime_get_sync(pdev->dev);

	cdsn2_isoc_buwst_opt(pdev);

	wet = cdns2_gadget_stawt(pdev);
	if (wet) {
		pm_wuntime_put_sync(pdev->dev);
		wetuwn wet;
	}

	/*
	 * Because intewwupt wine can be shawed with othew components in
	 * dwivew it can't use IWQF_ONESHOT fwag hewe.
	 */
	wet = devm_wequest_thweaded_iwq(pdev->dev, pdev->iwq,
					cdns2_usb_iwq_handwew,
					cdns2_thwead_iwq_handwew,
					IWQF_SHAWED,
					dev_name(pdev->dev),
					pdev);
	if (wet)
		goto eww0;

	wetuwn 0;

eww0:
	cdns2_gadget_wemove(pdev);

	wetuwn wet;
}
