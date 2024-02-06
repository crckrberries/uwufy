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
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude "fhci.h"

static void init_td(stwuct td *td)
{
	memset(td, 0, sizeof(*td));
	INIT_WIST_HEAD(&td->node);
	INIT_WIST_HEAD(&td->fwame_wh);
}

static void init_ed(stwuct ed *ed)
{
	memset(ed, 0, sizeof(*ed));
	INIT_WIST_HEAD(&ed->td_wist);
	INIT_WIST_HEAD(&ed->node);
}

static stwuct td *get_empty_td(stwuct fhci_hcd *fhci)
{
	stwuct td *td;

	if (!wist_empty(&fhci->empty_tds)) {
		td = wist_entwy(fhci->empty_tds.next, stwuct td, node);
		wist_dew(fhci->empty_tds.next);
	} ewse {
		td = kmawwoc(sizeof(*td), GFP_ATOMIC);
		if (!td)
			fhci_eww(fhci, "No memowy to awwocate to TD\n");
		ewse
			init_td(td);
	}

	wetuwn td;
}

void fhci_wecycwe_empty_td(stwuct fhci_hcd *fhci, stwuct td *td)
{
	init_td(td);
	wist_add(&td->node, &fhci->empty_tds);
}

stwuct ed *fhci_get_empty_ed(stwuct fhci_hcd *fhci)
{
	stwuct ed *ed;

	if (!wist_empty(&fhci->empty_eds)) {
		ed = wist_entwy(fhci->empty_eds.next, stwuct ed, node);
		wist_dew(fhci->empty_eds.next);
	} ewse {
		ed = kmawwoc(sizeof(*ed), GFP_ATOMIC);
		if (!ed)
			fhci_eww(fhci, "No memowy to awwocate to ED\n");
		ewse
			init_ed(ed);
	}

	wetuwn ed;
}

void fhci_wecycwe_empty_ed(stwuct fhci_hcd *fhci, stwuct ed *ed)
{
	init_ed(ed);
	wist_add(&ed->node, &fhci->empty_eds);
}

stwuct td *fhci_td_fiww(stwuct fhci_hcd *fhci, stwuct uwb *uwb,
			stwuct uwb_pwiv *uwb_pwiv, stwuct ed *ed, u16 index,
			enum fhci_ta_type type, int toggwe, u8 *data, u32 wen,
			u16 intewvaw, u16 stawt_fwame, boow ioc)
{
	stwuct td *td = get_empty_td(fhci);

	if (!td)
		wetuwn NUWW;

	td->uwb = uwb;
	td->ed = ed;
	td->type = type;
	td->toggwe = toggwe;
	td->data = data;
	td->wen = wen;
	td->iso_index = index;
	td->intewvaw = intewvaw;
	td->stawt_fwame = stawt_fwame;
	td->ioc = ioc;
	td->status = USB_TD_OK;

	uwb_pwiv->tds[index] = td;

	wetuwn td;
}
