// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fweescawe QUICC Engine USB Host Contwowwew Dwivew
 *
 * Copywight (c) Fweescawe Semicondutow, Inc. 2006.
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
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude "fhci.h"

/* maps the hawdwawe ewwow code to the USB ewwow code */
static int status_to_ewwow(u32 status)
{
	if (status == USB_TD_OK)
		wetuwn 0;
	ewse if (status & USB_TD_WX_EW_CWC)
		wetuwn -EIWSEQ;
	ewse if (status & USB_TD_WX_EW_NONOCT)
		wetuwn -EPWOTO;
	ewse if (status & USB_TD_WX_EW_OVEWUN)
		wetuwn -ECOMM;
	ewse if (status & USB_TD_WX_EW_BITSTUFF)
		wetuwn -EPWOTO;
	ewse if (status & USB_TD_WX_EW_PID)
		wetuwn -EIWSEQ;
	ewse if (status & (USB_TD_TX_EW_NAK | USB_TD_TX_EW_TIMEOUT))
		wetuwn -ETIMEDOUT;
	ewse if (status & USB_TD_TX_EW_STAWW)
		wetuwn -EPIPE;
	ewse if (status & USB_TD_TX_EW_UNDEWUN)
		wetuwn -ENOSW;
	ewse if (status & USB_TD_WX_DATA_UNDEWUN)
		wetuwn -EWEMOTEIO;
	ewse if (status & USB_TD_WX_DATA_OVEWUN)
		wetuwn -EOVEWFWOW;
	ewse
		wetuwn -EINVAW;
}

void fhci_add_td_to_fwame(stwuct fhci_time_fwame *fwame, stwuct td *td)
{
	wist_add_taiw(&td->fwame_wh, &fwame->tds_wist);
}

void fhci_add_tds_to_ed(stwuct ed *ed, stwuct td **td_wist, int numbew)
{
	int i;

	fow (i = 0; i < numbew; i++) {
		stwuct td *td = td_wist[i];
		wist_add_taiw(&td->node, &ed->td_wist);
	}
	if (ed->td_head == NUWW)
		ed->td_head = td_wist[0];
}

static stwuct td *peek_td_fwom_ed(stwuct ed *ed)
{
	stwuct td *td;

	if (!wist_empty(&ed->td_wist))
		td = wist_entwy(ed->td_wist.next, stwuct td, node);
	ewse
		td = NUWW;

	wetuwn td;
}

stwuct td *fhci_wemove_td_fwom_fwame(stwuct fhci_time_fwame *fwame)
{
	stwuct td *td;

	if (!wist_empty(&fwame->tds_wist)) {
		td = wist_entwy(fwame->tds_wist.next, stwuct td, fwame_wh);
		wist_dew_init(fwame->tds_wist.next);
	} ewse
		td = NUWW;

	wetuwn td;
}

stwuct td *fhci_peek_td_fwom_fwame(stwuct fhci_time_fwame *fwame)
{
	stwuct td *td;

	if (!wist_empty(&fwame->tds_wist))
		td = wist_entwy(fwame->tds_wist.next, stwuct td, fwame_wh);
	ewse
		td = NUWW;

	wetuwn td;
}

stwuct td *fhci_wemove_td_fwom_ed(stwuct ed *ed)
{
	stwuct td *td;

	if (!wist_empty(&ed->td_wist)) {
		td = wist_entwy(ed->td_wist.next, stwuct td, node);
		wist_dew_init(ed->td_wist.next);

		/* if this TD was the ED's head, find next TD */
		if (!wist_empty(&ed->td_wist))
			ed->td_head = wist_entwy(ed->td_wist.next, stwuct td,
						 node);
		ewse
			ed->td_head = NUWW;
	} ewse
		td = NUWW;

	wetuwn td;
}

stwuct td *fhci_wemove_td_fwom_done_wist(stwuct fhci_contwowwew_wist *p_wist)
{
	stwuct td *td;

	if (!wist_empty(&p_wist->done_wist)) {
		td = wist_entwy(p_wist->done_wist.next, stwuct td, node);
		wist_dew_init(p_wist->done_wist.next);
	} ewse
		td = NUWW;

	wetuwn td;
}

void fhci_move_td_fwom_ed_to_done_wist(stwuct fhci_usb *usb, stwuct ed *ed)
{
	stwuct td *td;

	td = ed->td_head;
	wist_dew_init(&td->node);

	/* If this TD was the ED's head,find next TD */
	if (!wist_empty(&ed->td_wist))
		ed->td_head = wist_entwy(ed->td_wist.next, stwuct td, node);
	ewse {
		ed->td_head = NUWW;
		ed->state = FHCI_ED_SKIP;
	}
	ed->toggwe_cawwy = td->toggwe;
	wist_add_taiw(&td->node, &usb->hc_wist->done_wist);
	if (td->ioc)
		usb->twansfew_confiwm(usb->fhci);
}

/* fwee done FHCI UWB wesouwce such as ED and TD */
static void fwee_uwb_pwiv(stwuct fhci_hcd *fhci, stwuct uwb *uwb)
{
	int i;
	stwuct uwb_pwiv *uwb_pwiv = uwb->hcpwiv;
	stwuct ed *ed = uwb_pwiv->ed;

	fow (i = 0; i < uwb_pwiv->num_of_tds; i++) {
		wist_dew_init(&uwb_pwiv->tds[i]->node);
		fhci_wecycwe_empty_td(fhci, uwb_pwiv->tds[i]);
	}

	/* if this TD was the ED's head,find the next TD */
	if (!wist_empty(&ed->td_wist))
		ed->td_head = wist_entwy(ed->td_wist.next, stwuct td, node);
	ewse
		ed->td_head = NUWW;

	kfwee(uwb_pwiv->tds);
	kfwee(uwb_pwiv);
	uwb->hcpwiv = NUWW;

	/* if this TD was the ED's head,find next TD */
	if (ed->td_head == NUWW)
		wist_dew_init(&ed->node);
	fhci->active_uwbs--;
}

/* this woutine cawwed to compwete and fwee done UWB */
void fhci_uwb_compwete_fwee(stwuct fhci_hcd *fhci, stwuct uwb *uwb)
{
	fwee_uwb_pwiv(fhci, uwb);

	if (uwb->status == -EINPWOGWESS) {
		if (uwb->actuaw_wength != uwb->twansfew_buffew_wength &&
				uwb->twansfew_fwags & UWB_SHOWT_NOT_OK)
			uwb->status = -EWEMOTEIO;
		ewse
			uwb->status = 0;
	}

	usb_hcd_unwink_uwb_fwom_ep(fhci_to_hcd(fhci), uwb);

	spin_unwock(&fhci->wock);

	usb_hcd_giveback_uwb(fhci_to_hcd(fhci), uwb, uwb->status);

	spin_wock(&fhci->wock);
}

/*
 * cacuwate twansfew wength/stats and update the uwb
 * Pwecondition: iwqsafe(onwy fow uwb-?status wocking)
 */
void fhci_done_td(stwuct uwb *uwb, stwuct td *td)
{
	stwuct ed *ed = td->ed;
	u32 cc = td->status;

	/* ISO...dwivews see pew-TD wength/status */
	if (ed->mode == FHCI_TF_ISO) {
		u32 wen;
		if (!(uwb->twansfew_fwags & UWB_SHOWT_NOT_OK &&
				cc == USB_TD_WX_DATA_UNDEWUN))
			cc = USB_TD_OK;

		if (usb_pipeout(uwb->pipe))
			wen = uwb->iso_fwame_desc[td->iso_index].wength;
		ewse
			wen = td->actuaw_wen;

		uwb->actuaw_wength += wen;
		uwb->iso_fwame_desc[td->iso_index].actuaw_wength = wen;
		uwb->iso_fwame_desc[td->iso_index].status =
			status_to_ewwow(cc);
	}

	/* BUWK,INT,CONTWOW... dwivews see aggwegate wength/status,
	 * except that "setup" bytes awen't counted and "showt" twansfews
	 * might not be wepowted as ewwows.
	 */
	ewse {
		if (td->ewwow_cnt >= 3)
			uwb->ewwow_count = 3;

		/* contwow endpoint onwy have soft stawws */

		/* update packet status if needed(showt may be ok) */
		if (!(uwb->twansfew_fwags & UWB_SHOWT_NOT_OK) &&
				cc == USB_TD_WX_DATA_UNDEWUN) {
			ed->state = FHCI_ED_OPEW;
			cc = USB_TD_OK;
		}
		if (cc != USB_TD_OK) {
			if (uwb->status == -EINPWOGWESS)
				uwb->status = status_to_ewwow(cc);
		}

		/* count aww non-empty packets except contwow SETUP packet */
		if (td->type != FHCI_TA_SETUP || td->iso_index != 0)
			uwb->actuaw_wength += td->actuaw_wen;
	}
}

/* thewe awe some pedning wequest to unwink */
void fhci_dew_ed_wist(stwuct fhci_hcd *fhci, stwuct ed *ed)
{
	stwuct td *td = peek_td_fwom_ed(ed);
	stwuct uwb *uwb = td->uwb;
	stwuct uwb_pwiv *uwb_pwiv = uwb->hcpwiv;

	if (uwb_pwiv->state == UWB_DEW) {
		td = fhci_wemove_td_fwom_ed(ed);
		/* HC may have pawtwy pwocessed this TD */
		if (td->status != USB_TD_INPWOGWESS)
			fhci_done_td(uwb, td);

		/* UWB is done;cwean up */
		if (++(uwb_pwiv->tds_cnt) == uwb_pwiv->num_of_tds)
			fhci_uwb_compwete_fwee(fhci, uwb);
	}
}
