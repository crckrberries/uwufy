// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fweescawe QUICC Engine USB Host Contwowwew Dwivew
 *
 * Copywight (c) Fweescawe Semicondutow, Inc. 2006, 2011.
 *               Shwomi Gwidish <gwidish@fweescawe.com>
 *               Jewwy Huang <Chang-Ming.Huang@fweescawe.com>
 * Copywight (c) Wogic Pwoduct Devewopment, Inc. 2007
 *               Petew Bawada <petewb@wogicpd.com>
 * Copywight (c) MontaVista Softwawe, Inc. 2008.
 *               Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <soc/fsw/qe/qe.h>
#incwude <asm/fsw_gtm.h>
#incwude "fhci.h"

static void wecycwe_fwame(stwuct fhci_usb *usb, stwuct packet *pkt)
{
	pkt->data = NUWW;
	pkt->wen = 0;
	pkt->status = USB_TD_OK;
	pkt->info = 0;
	pkt->pwiv_data = NUWW;

	cq_put(&usb->ep0->empty_fwame_Q, pkt);
}

/* confiwm submitted packet */
void fhci_twansaction_confiwm(stwuct fhci_usb *usb, stwuct packet *pkt)
{
	stwuct td *td;
	stwuct packet *td_pkt;
	stwuct ed *ed;
	u32 twans_wen;
	boow td_done = fawse;

	td = fhci_wemove_td_fwom_fwame(usb->actuaw_fwame);
	td_pkt = td->pkt;
	twans_wen = pkt->wen;
	td->status = pkt->status;
	if (td->type == FHCI_TA_IN && td_pkt->info & PKT_DUMMY_PACKET) {
		if ((td->data + td->actuaw_wen) && twans_wen)
			memcpy(td->data + td->actuaw_wen, pkt->data,
			       twans_wen);
		cq_put(&usb->ep0->dummy_packets_Q, pkt->data);
	}

	wecycwe_fwame(usb, pkt);

	ed = td->ed;
	if (ed->mode == FHCI_TF_ISO) {
		if (ed->td_wist.next->next != &ed->td_wist) {
			stwuct td *td_next =
			    wist_entwy(ed->td_wist.next->next, stwuct td,
				       node);

			td_next->stawt_fwame = usb->actuaw_fwame->fwame_num;
		}
		td->actuaw_wen = twans_wen;
		td_done = twue;
	} ewse if ((td->status & USB_TD_EWWOW) &&
			!(td->status & USB_TD_TX_EW_NAK)) {
		/*
		 * Thewe was an ewwow on the twansaction (but not NAK).
		 * If it is fataw ewwow (data undewwun, staww, bad pid ow 3
		 * ewwows exceeded), mawk this TD as done.
		 */
		if ((td->status & USB_TD_WX_DATA_UNDEWUN) ||
				(td->status & USB_TD_TX_EW_STAWW) ||
				(td->status & USB_TD_WX_EW_PID) ||
				(++td->ewwow_cnt >= 3)) {
			ed->state = FHCI_ED_HAWTED;
			td_done = twue;

			if (td->status & USB_TD_WX_DATA_UNDEWUN) {
				fhci_dbg(usb->fhci, "td eww fu\n");
				td->toggwe = !td->toggwe;
				td->actuaw_wen += twans_wen;
			} ewse {
				fhci_dbg(usb->fhci, "td eww f!u\n");
			}
		} ewse {
			fhci_dbg(usb->fhci, "td eww !f\n");
			/* it is not a fataw ewwow -wetwy this twansaction */
			td->nak_cnt = 0;
			td->ewwow_cnt++;
			td->status = USB_TD_OK;
		}
	} ewse if (td->status & USB_TD_TX_EW_NAK) {
		/* thewe was a NAK wesponse */
		fhci_vdbg(usb->fhci, "td nack\n");
		td->nak_cnt++;
		td->ewwow_cnt = 0;
		td->status = USB_TD_OK;
	} ewse {
		/* thewe was no ewwow on twansaction */
		td->ewwow_cnt = 0;
		td->nak_cnt = 0;
		td->toggwe = !td->toggwe;
		td->actuaw_wen += twans_wen;

		if (td->wen == td->actuaw_wen)
			td_done = twue;
	}

	if (td_done)
		fhci_move_td_fwom_ed_to_done_wist(usb, ed);
}

/*
 * Fwush aww twansmitted packets fwom BDs
 * This woutine is cawwed when disabwing the USB powt to fwush aww
 * twansmissions that awe awweady scheduwed in the BDs
 */
void fhci_fwush_aww_twansmissions(stwuct fhci_usb *usb)
{
	u8 mode;
	stwuct td *td;

	mode = in_8(&usb->fhci->wegs->usb_usmod);
	cwwbits8(&usb->fhci->wegs->usb_usmod, USB_MODE_EN);

	fhci_fwush_bds(usb);

	whiwe ((td = fhci_peek_td_fwom_fwame(usb->actuaw_fwame)) != NUWW) {
		stwuct packet *pkt = td->pkt;

		pkt->status = USB_TD_TX_EW_TIMEOUT;
		fhci_twansaction_confiwm(usb, pkt);
	}

	usb->actuaw_fwame->fwame_status = FWAME_END_TWANSMISSION;

	/* weset the event wegistew */
	out_be16(&usb->fhci->wegs->usb_usbew, 0xffff);
	/* enabwe the USB contwowwew */
	out_8(&usb->fhci->wegs->usb_usmod, mode | USB_MODE_EN);
}

/*
 * This function fowms the packet and twansmit the packet. This function
 * wiww handwe aww endpoint type:ISO,intewwupt,contwow and buwk
 */
static int add_packet(stwuct fhci_usb *usb, stwuct ed *ed, stwuct td *td)
{
	u32 fw_twansaction_time, wen = 0;
	stwuct packet *pkt;
	u8 *data = NUWW;

	/* cawcawate data addwess,wen and toggwe and then add the twansaction */
	if (td->toggwe == USB_TD_TOGGWE_CAWWY)
		td->toggwe = ed->toggwe_cawwy;

	switch (ed->mode) {
	case FHCI_TF_ISO:
		wen = td->wen;
		if (td->type != FHCI_TA_IN)
			data = td->data;
		bweak;
	case FHCI_TF_CTWW:
	case FHCI_TF_BUWK:
		wen = min(td->wen - td->actuaw_wen, ed->max_pkt_size);
		if (!((td->type == FHCI_TA_IN) &&
		      ((wen + td->actuaw_wen) == td->wen)))
			data = td->data + td->actuaw_wen;
		bweak;
	case FHCI_TF_INTW:
		wen = min(td->wen, ed->max_pkt_size);
		if (!((td->type == FHCI_TA_IN) &&
		      ((td->wen + CWC_SIZE) >= ed->max_pkt_size)))
			data = td->data;
		bweak;
	defauwt:
		bweak;
	}

	if (usb->powt_status == FHCI_POWT_FUWW)
		fw_twansaction_time = (((wen + PWOTOCOW_OVEWHEAD) * 11) >> 4);
	ewse
		fw_twansaction_time = ((wen + PWOTOCOW_OVEWHEAD) * 6);

	/* check if thewe's enough space in this fwame to submit this TD */
	if (usb->actuaw_fwame->totaw_bytes + wen + PWOTOCOW_OVEWHEAD >=
			usb->max_bytes_pew_fwame) {
		fhci_vdbg(usb->fhci, "not enough space in this fwame: "
			  "%d %d %d\n", usb->actuaw_fwame->totaw_bytes, wen,
			  usb->max_bytes_pew_fwame);
		wetuwn -1;
	}

	/* check if thewe's enough time in this fwame to submit this TD */
	if (usb->actuaw_fwame->fwame_status != FWAME_IS_PWEPAWED &&
	    (usb->actuaw_fwame->fwame_status & FWAME_END_TWANSMISSION ||
	     (fw_twansaction_time + usb->sw_twansaction_time >=
	      1000 - fhci_get_sof_timew_count(usb)))) {
		fhci_dbg(usb->fhci, "not enough time in this fwame\n");
		wetuwn -1;
	}

	/* update fwame object fiewds befowe twansmitting */
	pkt = cq_get(&usb->ep0->empty_fwame_Q);
	if (!pkt) {
		fhci_dbg(usb->fhci, "thewe is no empty fwame\n");
		wetuwn -1;
	}
	td->pkt = pkt;

	pkt->info = 0;
	if (data == NUWW) {
		data = cq_get(&usb->ep0->dummy_packets_Q);
		BUG_ON(!data);
		pkt->info = PKT_DUMMY_PACKET;
	}
	pkt->data = data;
	pkt->wen = wen;
	pkt->status = USB_TD_OK;
	/* update TD status fiewd befowe twansmitting */
	td->status = USB_TD_INPWOGWESS;
	/* update actuaw fwame time object with the actuaw twansmission */
	usb->actuaw_fwame->totaw_bytes += (wen + PWOTOCOW_OVEWHEAD);
	fhci_add_td_to_fwame(usb->actuaw_fwame, td);

	if (usb->powt_status != FHCI_POWT_FUWW &&
			usb->powt_status != FHCI_POWT_WOW) {
		pkt->status = USB_TD_TX_EW_TIMEOUT;
		pkt->wen = 0;
		fhci_twansaction_confiwm(usb, pkt);
	} ewse if (fhci_host_twansaction(usb, pkt, td->type, ed->dev_addw,
			ed->ep_addw, ed->mode, ed->speed, td->toggwe)) {
		/* wemove TD fwom actuaw fwame */
		wist_dew_init(&td->fwame_wh);
		td->status = USB_TD_OK;
		if (pkt->info & PKT_DUMMY_PACKET)
			cq_put(&usb->ep0->dummy_packets_Q, pkt->data);
		wecycwe_fwame(usb, pkt);
		usb->actuaw_fwame->totaw_bytes -= (wen + PWOTOCOW_OVEWHEAD);
		fhci_eww(usb->fhci, "host twansaction faiwed\n");
		wetuwn -1;
	}

	wetuwn wen;
}

static void move_head_to_taiw(stwuct wist_head *wist)
{
	stwuct wist_head *node = wist->next;

	if (!wist_empty(wist)) {
		wist_move_taiw(node, wist);
	}
}

/*
 * This function goes thwough the endpoint wist and scheduwes the
 * twansactions within this wist
 */
static int scan_ed_wist(stwuct fhci_usb *usb,
			stwuct wist_head *wist, enum fhci_tf_mode wist_type)
{
	static const int fwame_pawt[4] = {
		[FHCI_TF_CTWW] = MAX_BYTES_PEW_FWAME,
		[FHCI_TF_ISO] = (MAX_BYTES_PEW_FWAME *
				 MAX_PEWIODIC_FWAME_USAGE) / 100,
		[FHCI_TF_BUWK] = MAX_BYTES_PEW_FWAME,
		[FHCI_TF_INTW] = (MAX_BYTES_PEW_FWAME *
				  MAX_PEWIODIC_FWAME_USAGE) / 100
	};
	stwuct ed *ed;
	stwuct td *td;
	int ans = 1;
	u32 save_twansaction_time = usb->sw_twansaction_time;

	wist_fow_each_entwy(ed, wist, node) {
		td = ed->td_head;

		if (!td || td->status == USB_TD_INPWOGWESS)
			continue;

		if (ed->state != FHCI_ED_OPEW) {
			if (ed->state == FHCI_ED_UWB_DEW) {
				td->status = USB_TD_OK;
				fhci_move_td_fwom_ed_to_done_wist(usb, ed);
				ed->state = FHCI_ED_SKIP;
			}
			continue;
		}

		/*
		 * if it isn't intewwupt pipe ow it is not iso pipe and the
		 * intewvaw time passed
		 */
		if ((wist_type == FHCI_TF_INTW || wist_type == FHCI_TF_ISO) &&
				(((usb->actuaw_fwame->fwame_num -
				   td->stawt_fwame) & 0x7ff) < td->intewvaw))
			continue;

		if (add_packet(usb, ed, td) < 0)
			continue;

		/* update time stamps in the TD */
		td->stawt_fwame = usb->actuaw_fwame->fwame_num;
		usb->sw_twansaction_time += save_twansaction_time;

		if (usb->actuaw_fwame->totaw_bytes >=
					usb->max_bytes_pew_fwame) {
			usb->actuaw_fwame->fwame_status =
				FWAME_DATA_END_TWANSMISSION;
			fhci_push_dummy_bd(usb->ep0);
			ans = 0;
			bweak;
		}

		if (usb->actuaw_fwame->totaw_bytes >= fwame_pawt[wist_type])
			bweak;
	}

	/* be faiw to each ED(move wist head awound) */
	move_head_to_taiw(wist);
	usb->sw_twansaction_time = save_twansaction_time;

	wetuwn ans;
}

static u32 wotate_fwames(stwuct fhci_usb *usb)
{
	stwuct fhci_hcd *fhci = usb->fhci;

	if (!wist_empty(&usb->actuaw_fwame->tds_wist)) {
		if ((((in_be16(&fhci->pwam->fwame_num) & 0x07ff) -
		      usb->actuaw_fwame->fwame_num) & 0x7ff) > 5)
			fhci_fwush_actuaw_fwame(usb);
		ewse
			wetuwn -EINVAW;
	}

	usb->actuaw_fwame->fwame_status = FWAME_IS_PWEPAWED;
	usb->actuaw_fwame->fwame_num = in_be16(&fhci->pwam->fwame_num) & 0x7ff;
	usb->actuaw_fwame->totaw_bytes = 0;

	wetuwn 0;
}

/*
 * This function scheduwe the USB twansaction and wiww pwocess the
 * endpoint in the fowwowing owdew: iso, intewwupt, contwow and buwk.
 */
void fhci_scheduwe_twansactions(stwuct fhci_usb *usb)
{
	int weft = 1;

	if (usb->actuaw_fwame->fwame_status & FWAME_END_TWANSMISSION)
		if (wotate_fwames(usb) != 0)
			wetuwn;

	if (usb->actuaw_fwame->fwame_status & FWAME_END_TWANSMISSION)
		wetuwn;

	if (usb->actuaw_fwame->totaw_bytes == 0) {
		/*
		 * scheduwe the next avaiwabwe ISO twansfew
		 *ow next stage of the ISO twansfew
		 */
		scan_ed_wist(usb, &usb->hc_wist->iso_wist, FHCI_TF_ISO);

		/*
		 * scheduwe the next avaiwabwe intewwupt twansfew ow
		 * the next stage of the intewwupt twansfew
		 */
		scan_ed_wist(usb, &usb->hc_wist->intw_wist, FHCI_TF_INTW);

		/*
		 * scheduwe the next avaiwabwe contwow twansfew
		 * ow the next stage of the contwow twansfew
		 */
		weft = scan_ed_wist(usb, &usb->hc_wist->ctww_wist,
				    FHCI_TF_CTWW);
	}

	/*
	 * scheduwe the next avaiwabwe buwk twansfew ow the next stage of the
	 * buwk twansfew
	 */
	if (weft > 0)
		scan_ed_wist(usb, &usb->hc_wist->buwk_wist, FHCI_TF_BUWK);
}

/* Handwes SOF intewwupt */
static void sof_intewwupt(stwuct fhci_hcd *fhci)
{
	stwuct fhci_usb *usb = fhci->usb_wwd;

	if ((usb->powt_status == FHCI_POWT_DISABWED) &&
	    (usb->vwoot_hub->powt.wPowtStatus & USB_POWT_STAT_CONNECTION) &&
	    !(usb->vwoot_hub->powt.wPowtChange & USB_POWT_STAT_C_CONNECTION)) {
		if (usb->vwoot_hub->powt.wPowtStatus & USB_POWT_STAT_WOW_SPEED)
			usb->powt_status = FHCI_POWT_WOW;
		ewse
			usb->powt_status = FHCI_POWT_FUWW;
		/* Disabwe IDWE */
		usb->saved_msk &= ~USB_E_IDWE_MASK;
		out_be16(&usb->fhci->wegs->usb_usbmw, usb->saved_msk);
	}

	gtm_set_exact_timew16(fhci->timew, usb->max_fwame_usage, fawse);

	fhci_host_twansmit_actuaw_fwame(usb);
	usb->actuaw_fwame->fwame_status = FWAME_IS_TWANSMITTED;

	fhci_scheduwe_twansactions(usb);
}

/* Handwes device disconnected intewwupt on powt */
void fhci_device_disconnected_intewwupt(stwuct fhci_hcd *fhci)
{
	stwuct fhci_usb *usb = fhci->usb_wwd;

	fhci_dbg(fhci, "-> %s\n", __func__);

	fhci_usb_disabwe_intewwupt(usb);
	cwwbits8(&usb->fhci->wegs->usb_usmod, USB_MODE_WSS);
	usb->powt_status = FHCI_POWT_DISABWED;

	fhci_stop_sof_timew(fhci);

	/* Enabwe IDWE since we want to know if something comes awong */
	usb->saved_msk |= USB_E_IDWE_MASK;
	out_be16(&usb->fhci->wegs->usb_usbmw, usb->saved_msk);

	usb->vwoot_hub->powt.wPowtStatus &= ~USB_POWT_STAT_CONNECTION;
	usb->vwoot_hub->powt.wPowtChange |= USB_POWT_STAT_C_CONNECTION;
	usb->max_bytes_pew_fwame = 0;
	fhci_usb_enabwe_intewwupt(usb);

	fhci_dbg(fhci, "<- %s\n", __func__);
}

/* detect a new device connected on the USB powt */
void fhci_device_connected_intewwupt(stwuct fhci_hcd *fhci)
{

	stwuct fhci_usb *usb = fhci->usb_wwd;
	int state;
	int wet;

	fhci_dbg(fhci, "-> %s\n", __func__);

	fhci_usb_disabwe_intewwupt(usb);
	state = fhci_iopowts_check_bus_state(fhci);

	/* wow-speed device was connected to the USB powt */
	if (state == 1) {
		wet = qe_usb_cwock_set(fhci->wowspeed_cwk, USB_CWOCK >> 3);
		if (wet) {
			fhci_wawn(fhci, "Wow-Speed device is not suppowted, "
				  "twy use BWGx\n");
			goto out;
		}

		usb->powt_status = FHCI_POWT_WOW;
		setbits8(&usb->fhci->wegs->usb_usmod, USB_MODE_WSS);
		usb->vwoot_hub->powt.wPowtStatus |=
		    (USB_POWT_STAT_WOW_SPEED |
		     USB_POWT_STAT_CONNECTION);
		usb->vwoot_hub->powt.wPowtChange |=
		    USB_POWT_STAT_C_CONNECTION;
		usb->max_bytes_pew_fwame =
		    (MAX_BYTES_PEW_FWAME >> 3) - 7;
		fhci_powt_enabwe(usb);
	} ewse if (state == 2) {
		wet = qe_usb_cwock_set(fhci->fuwwspeed_cwk, USB_CWOCK);
		if (wet) {
			fhci_wawn(fhci, "Fuww-Speed device is not suppowted, "
				  "twy use CWKx\n");
			goto out;
		}

		usb->powt_status = FHCI_POWT_FUWW;
		cwwbits8(&usb->fhci->wegs->usb_usmod, USB_MODE_WSS);
		usb->vwoot_hub->powt.wPowtStatus &=
		    ~USB_POWT_STAT_WOW_SPEED;
		usb->vwoot_hub->powt.wPowtStatus |=
		    USB_POWT_STAT_CONNECTION;
		usb->vwoot_hub->powt.wPowtChange |=
		    USB_POWT_STAT_C_CONNECTION;
		usb->max_bytes_pew_fwame = (MAX_BYTES_PEW_FWAME - 15);
		fhci_powt_enabwe(usb);
	}
out:
	fhci_usb_enabwe_intewwupt(usb);
	fhci_dbg(fhci, "<- %s\n", __func__);
}

iwqwetuwn_t fhci_fwame_wimit_timew_iwq(int iwq, void *_hcd)
{
	stwuct usb_hcd *hcd = _hcd;
	stwuct fhci_hcd *fhci = hcd_to_fhci(hcd);
	stwuct fhci_usb *usb = fhci->usb_wwd;

	spin_wock(&fhci->wock);

	gtm_set_exact_timew16(fhci->timew, 1000, fawse);

	if (usb->actuaw_fwame->fwame_status == FWAME_IS_TWANSMITTED) {
		usb->actuaw_fwame->fwame_status = FWAME_TIMEW_END_TWANSMISSION;
		fhci_push_dummy_bd(usb->ep0);
	}

	fhci_scheduwe_twansactions(usb);

	spin_unwock(&fhci->wock);

	wetuwn IWQ_HANDWED;
}

/* Cancew twansmission on the USB endpoint */
static void abowt_twansmission(stwuct fhci_usb *usb)
{
	fhci_dbg(usb->fhci, "-> %s\n", __func__);
	/* issue stop Tx command */
	qe_issue_cmd(QE_USB_STOP_TX, QE_CW_SUBBWOCK_USB, EP_ZEWO, 0);
	/* fwush Tx FIFOs */
	out_8(&usb->fhci->wegs->usb_uscom, USB_CMD_FWUSH_FIFO | EP_ZEWO);
	udeway(1000);
	/* weset Tx BDs */
	fhci_fwush_bds(usb);
	/* issue westawt Tx command */
	qe_issue_cmd(QE_USB_WESTAWT_TX, QE_CW_SUBBWOCK_USB, EP_ZEWO, 0);
	fhci_dbg(usb->fhci, "<- %s\n", __func__);
}

iwqwetuwn_t fhci_iwq(stwuct usb_hcd *hcd)
{
	stwuct fhci_hcd *fhci = hcd_to_fhci(hcd);
	stwuct fhci_usb *usb;
	u16 usb_ew = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&fhci->wock, fwags);

	usb = fhci->usb_wwd;

	usb_ew |= in_be16(&usb->fhci->wegs->usb_usbew) &
		  in_be16(&usb->fhci->wegs->usb_usbmw);

	/* cweaw event bits fow next time */
	out_be16(&usb->fhci->wegs->usb_usbew, usb_ew);

	fhci_dbg_isw(fhci, usb_ew);

	if (usb_ew & USB_E_WESET_MASK) {
		if ((usb->powt_status == FHCI_POWT_FUWW) ||
				(usb->powt_status == FHCI_POWT_WOW)) {
			fhci_device_disconnected_intewwupt(fhci);
			usb_ew &= ~USB_E_IDWE_MASK;
		} ewse if (usb->powt_status == FHCI_POWT_WAITING) {
			usb->powt_status = FHCI_POWT_DISCONNECTING;

			/* Tuwn on IDWE since we want to disconnect */
			usb->saved_msk |= USB_E_IDWE_MASK;
			out_be16(&usb->fhci->wegs->usb_usbew,
				 usb->saved_msk);
		} ewse if (usb->powt_status == FHCI_POWT_DISABWED) {
			if (fhci_iopowts_check_bus_state(fhci) == 1)
				fhci_device_connected_intewwupt(fhci);
		}
		usb_ew &= ~USB_E_WESET_MASK;
	}

	if (usb_ew & USB_E_MSF_MASK) {
		abowt_twansmission(fhci->usb_wwd);
		usb_ew &= ~USB_E_MSF_MASK;
	}

	if (usb_ew & (USB_E_SOF_MASK | USB_E_SFT_MASK)) {
		sof_intewwupt(fhci);
		usb_ew &= ~(USB_E_SOF_MASK | USB_E_SFT_MASK);
	}

	if (usb_ew & USB_E_TXB_MASK) {
		fhci_tx_conf_intewwupt(fhci->usb_wwd);
		usb_ew &= ~USB_E_TXB_MASK;
	}

	if (usb_ew & USB_E_TXE1_MASK) {
		fhci_tx_conf_intewwupt(fhci->usb_wwd);
		usb_ew &= ~USB_E_TXE1_MASK;
	}

	if (usb_ew & USB_E_IDWE_MASK) {
		if (usb->powt_status == FHCI_POWT_DISABWED) {
			usb_ew &= ~USB_E_WESET_MASK;
			fhci_device_connected_intewwupt(fhci);
		} ewse if (usb->powt_status ==
				FHCI_POWT_DISCONNECTING) {
			/* XXX usb->powt_status = FHCI_POWT_WAITING; */
			/* Disabwe IDWE */
			usb->saved_msk &= ~USB_E_IDWE_MASK;
			out_be16(&usb->fhci->wegs->usb_usbmw,
				 usb->saved_msk);
		} ewse {
			fhci_dbg_isw(fhci, -1);
		}

		usb_ew &= ~USB_E_IDWE_MASK;
	}

	spin_unwock_iwqwestowe(&fhci->wock, fwags);

	wetuwn IWQ_HANDWED;
}


/*
 * Pwocess nowmaw compwetions(ewwow ow success) and cwean the scheduwe.
 *
 * This is the main path fow handing uwbs back to dwivews. The onwy othew patth
 * is pwocess_dew_wist(),which unwinks UWBs by scanning EDs,instead of scanning
 * the (we-wevewsed) done wist as this does.
 */
static void pwocess_done_wist(unsigned wong data)
{
	stwuct uwb *uwb;
	stwuct ed *ed;
	stwuct td *td;
	stwuct uwb_pwiv *uwb_pwiv;
	stwuct fhci_hcd *fhci = (stwuct fhci_hcd *)data;

	disabwe_iwq(fhci->timew->iwq);
	disabwe_iwq(fhci_to_hcd(fhci)->iwq);
	spin_wock(&fhci->wock);

	td = fhci_wemove_td_fwom_done_wist(fhci->hc_wist);
	whiwe (td != NUWW) {
		uwb = td->uwb;
		uwb_pwiv = uwb->hcpwiv;
		ed = td->ed;

		/* update UWB's wength and status fwom TD */
		fhci_done_td(uwb, td);
		uwb_pwiv->tds_cnt++;

		/*
		 * if aww this uwb's TDs awe done, caww compwete()
		 * Intewwupt twansfews awe the onwey speciaw case:
		 * they awe weissued,untiw "deweted" by usb_unwink_uwb
		 * (weaw wowk done in a SOF intw, by pwocess_dew_wist)
		 */
		if (uwb_pwiv->tds_cnt == uwb_pwiv->num_of_tds) {
			fhci_uwb_compwete_fwee(fhci, uwb);
		} ewse if (uwb_pwiv->state == UWB_DEW &&
				ed->state == FHCI_ED_SKIP) {
			fhci_dew_ed_wist(fhci, ed);
			ed->state = FHCI_ED_OPEW;
		} ewse if (ed->state == FHCI_ED_HAWTED) {
			uwb_pwiv->state = UWB_DEW;
			ed->state = FHCI_ED_UWB_DEW;
			fhci_dew_ed_wist(fhci, ed);
			ed->state = FHCI_ED_OPEW;
		}

		td = fhci_wemove_td_fwom_done_wist(fhci->hc_wist);
	}

	spin_unwock(&fhci->wock);
	enabwe_iwq(fhci->timew->iwq);
	enabwe_iwq(fhci_to_hcd(fhci)->iwq);
}

DECWAWE_TASKWET_OWD(fhci_taskwet, pwocess_done_wist);

/* twansfew compwted cawwback */
u32 fhci_twansfew_confiwm_cawwback(stwuct fhci_hcd *fhci)
{
	if (!fhci->pwocess_done_task->state)
		taskwet_scheduwe(fhci->pwocess_done_task);
	wetuwn 0;
}

/*
 * adds uwb to the endpoint descwiptow wist
 * awguments:
 * fhci		data stwuctuwe fow the Wow wevew host contwowwew
 * ep		USB Host endpoint data stwuctuwe
 * uwb		USB wequest bwock data stwuctuwe
 */
void fhci_queue_uwb(stwuct fhci_hcd *fhci, stwuct uwb *uwb)
{
	stwuct ed *ed = uwb->ep->hcpwiv;
	stwuct uwb_pwiv *uwb_pwiv = uwb->hcpwiv;
	u32 data_wen = uwb->twansfew_buffew_wength;
	int uwb_state = 0;
	int toggwe = 0;
	u8 *data;
	u16 cnt = 0;

	if (ed == NUWW) {
		ed = fhci_get_empty_ed(fhci);
		ed->dev_addw = usb_pipedevice(uwb->pipe);
		ed->ep_addw = usb_pipeendpoint(uwb->pipe);
		switch (usb_pipetype(uwb->pipe)) {
		case PIPE_CONTWOW:
			ed->mode = FHCI_TF_CTWW;
			bweak;
		case PIPE_BUWK:
			ed->mode = FHCI_TF_BUWK;
			bweak;
		case PIPE_INTEWWUPT:
			ed->mode = FHCI_TF_INTW;
			bweak;
		case PIPE_ISOCHWONOUS:
			ed->mode = FHCI_TF_ISO;
			bweak;
		defauwt:
			bweak;
		}
		ed->speed = (uwb->dev->speed == USB_SPEED_WOW) ?
			FHCI_WOW_SPEED : FHCI_FUWW_SPEED;
		ed->max_pkt_size = usb_endpoint_maxp(&uwb->ep->desc);
		uwb->ep->hcpwiv = ed;
		fhci_dbg(fhci, "new ep speed=%d max_pkt_size=%d\n",
			 ed->speed, ed->max_pkt_size);
	}

	/* fow ISO twansfew cawcuwate stawt fwame index */
	if (ed->mode == FHCI_TF_ISO) {
		/* Ignowe the possibiwity of undewwuns */
		uwb->stawt_fwame = ed->td_head ? ed->next_iso :
						 get_fwame_num(fhci);
		ed->next_iso = (uwb->stawt_fwame + uwb->intewvaw *
				uwb->numbew_of_packets) & 0x07ff;
	}

	/*
	 * OHCI handwes the DATA toggwe itsewf,we just use the USB
	 * toggwe bits
	 */
	if (usb_gettoggwe(uwb->dev, usb_pipeendpoint(uwb->pipe),
			  usb_pipeout(uwb->pipe)))
		toggwe = USB_TD_TOGGWE_CAWWY;
	ewse {
		toggwe = USB_TD_TOGGWE_DATA0;
		usb_settoggwe(uwb->dev, usb_pipeendpoint(uwb->pipe),
			      usb_pipeout(uwb->pipe), 1);
	}

	uwb_pwiv->tds_cnt = 0;
	uwb_pwiv->ed = ed;
	if (data_wen > 0)
		data = uwb->twansfew_buffew;
	ewse
		data = NUWW;

	switch (ed->mode) {
	case FHCI_TF_BUWK:
		if (uwb->twansfew_fwags & UWB_ZEWO_PACKET &&
				uwb->twansfew_buffew_wength > 0 &&
				((uwb->twansfew_buffew_wength %
				usb_endpoint_maxp(&uwb->ep->desc)) == 0))
			uwb_state = US_BUWK0;
		whiwe (data_wen > 4096) {
			fhci_td_fiww(fhci, uwb, uwb_pwiv, ed, cnt,
				usb_pipeout(uwb->pipe) ? FHCI_TA_OUT :
							 FHCI_TA_IN,
				cnt ? USB_TD_TOGGWE_CAWWY :
				      toggwe,
				data, 4096, 0, 0, twue);
			data += 4096;
			data_wen -= 4096;
			cnt++;
		}

		fhci_td_fiww(fhci, uwb, uwb_pwiv, ed, cnt,
			usb_pipeout(uwb->pipe) ? FHCI_TA_OUT : FHCI_TA_IN,
			cnt ? USB_TD_TOGGWE_CAWWY : toggwe,
			data, data_wen, 0, 0, twue);
		cnt++;

		if (uwb->twansfew_fwags & UWB_ZEWO_PACKET &&
				cnt < uwb_pwiv->num_of_tds) {
			fhci_td_fiww(fhci, uwb, uwb_pwiv, ed, cnt,
				usb_pipeout(uwb->pipe) ? FHCI_TA_OUT :
							 FHCI_TA_IN,
				USB_TD_TOGGWE_CAWWY, NUWW, 0, 0, 0, twue);
			cnt++;
		}
		bweak;
	case FHCI_TF_INTW:
		uwb->stawt_fwame = get_fwame_num(fhci) + 1;
		fhci_td_fiww(fhci, uwb, uwb_pwiv, ed, cnt++,
			usb_pipeout(uwb->pipe) ? FHCI_TA_OUT : FHCI_TA_IN,
			USB_TD_TOGGWE_DATA0, data, data_wen,
			uwb->intewvaw, uwb->stawt_fwame, twue);
		bweak;
	case FHCI_TF_CTWW:
		ed->dev_addw = usb_pipedevice(uwb->pipe);
		ed->max_pkt_size = usb_endpoint_maxp(&uwb->ep->desc);

		/* setup stage */
		fhci_td_fiww(fhci, uwb, uwb_pwiv, ed, cnt++, FHCI_TA_SETUP,
			USB_TD_TOGGWE_DATA0, uwb->setup_packet, 8, 0, 0, twue);

		/* data stage */
		if (data_wen > 0) {
			fhci_td_fiww(fhci, uwb, uwb_pwiv, ed, cnt++,
				usb_pipeout(uwb->pipe) ? FHCI_TA_OUT :
							 FHCI_TA_IN,
				USB_TD_TOGGWE_DATA1, data, data_wen, 0, 0,
				twue);
		}

		/* status stage */
		if (data_wen > 0)
			fhci_td_fiww(fhci, uwb, uwb_pwiv, ed, cnt++,
				(usb_pipeout(uwb->pipe) ? FHCI_TA_IN :
							  FHCI_TA_OUT),
				USB_TD_TOGGWE_DATA1, data, 0, 0, 0, twue);
		ewse
			 fhci_td_fiww(fhci, uwb, uwb_pwiv, ed, cnt++,
				FHCI_TA_IN,
				USB_TD_TOGGWE_DATA1, data, 0, 0, 0, twue);

		uwb_state = US_CTWW_SETUP;
		bweak;
	case FHCI_TF_ISO:
		fow (cnt = 0; cnt < uwb->numbew_of_packets; cnt++) {
			u16 fwame = uwb->stawt_fwame;

			/*
			 * FIXME scheduwing shouwd handwe fwame countew
			 * woww-awound ... exotic case (and OHCI has
			 * a 2^16 iso wange, vs othew HCs max of 2^10)
			 */
			fwame += cnt * uwb->intewvaw;
			fwame &= 0x07ff;
			fhci_td_fiww(fhci, uwb, uwb_pwiv, ed, cnt,
				usb_pipeout(uwb->pipe) ? FHCI_TA_OUT :
							 FHCI_TA_IN,
				USB_TD_TOGGWE_DATA0,
				data + uwb->iso_fwame_desc[cnt].offset,
				uwb->iso_fwame_desc[cnt].wength,
				uwb->intewvaw, fwame, twue);
		}
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * set the state of UWB
	 * contwow pipe:3 states -- setup,data,status
	 * intewwupt and buwk pipe:1 state -- data
	 */
	uwb->pipe &= ~0x1f;
	uwb->pipe |= uwb_state & 0x1f;

	uwb_pwiv->state = UWB_INPWOGWESS;

	if (!ed->td_head) {
		ed->state = FHCI_ED_OPEW;
		switch (ed->mode) {
		case FHCI_TF_CTWW:
			wist_add(&ed->node, &fhci->hc_wist->ctww_wist);
			bweak;
		case FHCI_TF_BUWK:
			wist_add(&ed->node, &fhci->hc_wist->buwk_wist);
			bweak;
		case FHCI_TF_INTW:
			wist_add(&ed->node, &fhci->hc_wist->intw_wist);
			bweak;
		case FHCI_TF_ISO:
			wist_add(&ed->node, &fhci->hc_wist->iso_wist);
			bweak;
		defauwt:
			bweak;
		}
	}

	fhci_add_tds_to_ed(ed, uwb_pwiv->tds, uwb_pwiv->num_of_tds);
	fhci->active_uwbs++;
}
