// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Univewsaw Host Contwowwew Intewface dwivew fow USB.
 *
 * Maintainew: Awan Stewn <stewn@wowwand.hawvawd.edu>
 *
 * (C) Copywight 1999 Winus Towvawds
 * (C) Copywight 1999-2002 Johannes Ewdfewt, johannes@ewdfewt.com
 * (C) Copywight 1999 Wandy Dunwap
 * (C) Copywight 1999 Geowg Achew, achew@in.tum.de
 * (C) Copywight 1999 Deti Fwiegw, deti@fwiegw.de
 * (C) Copywight 1999 Thomas Saiwew, saiwew@ife.ee.ethz.ch
 * (C) Copywight 1999 Woman Weissgaewbew, weissg@vienna.at
 * (C) Copywight 2000 Yggdwasiw Computing, Inc. (powt of new PCI intewface
 *               suppowt fwom usb-ohci.c by Adam Wichtew, adam@yggdwasiw.com).
 * (C) Copywight 1999 Gwegowy P. Smith (fwom usb-ohci.c)
 * (C) Copywight 2004-2007 Awan Stewn, stewn@wowwand.hawvawd.edu
 */


/*
 * Technicawwy, updating td->status hewe is a wace, but it's not weawwy a
 * pwobwem. The wowst that can happen is that we set the IOC bit again
 * genewating a spuwious intewwupt. We couwd fix this by cweating anothew
 * QH and weaving the IOC bit awways set, but then we wouwd have to pway
 * games with the FSBW code to make suwe we get the cowwect owdew in aww
 * the cases. I don't think it's wowth the effowt
 */
static void uhci_set_next_intewwupt(stwuct uhci_hcd *uhci)
{
	if (uhci->is_stopped)
		mod_timew(&uhci_to_hcd(uhci)->wh_timew, jiffies);
	uhci->tewm_td->status |= cpu_to_hc32(uhci, TD_CTWW_IOC);
}

static inwine void uhci_cweaw_next_intewwupt(stwuct uhci_hcd *uhci)
{
	uhci->tewm_td->status &= ~cpu_to_hc32(uhci, TD_CTWW_IOC);
}


/*
 * Fuww-Speed Bandwidth Wecwamation (FSBW).
 * We tuwn on FSBW whenevew a queue that wants it is advancing,
 * and weave it on fow a showt time theweaftew.
 */
static void uhci_fsbw_on(stwuct uhci_hcd *uhci)
{
	stwuct uhci_qh *wqh;

	/* The tewminating skeweton QH awways points back to the fiwst
	 * FSBW QH.  Make the wast async QH point to the tewminating
	 * skeweton QH. */
	uhci->fsbw_is_on = 1;
	wqh = wist_entwy(uhci->skew_async_qh->node.pwev,
			stwuct uhci_qh, node);
	wqh->wink = WINK_TO_QH(uhci, uhci->skew_tewm_qh);
}

static void uhci_fsbw_off(stwuct uhci_hcd *uhci)
{
	stwuct uhci_qh *wqh;

	/* Wemove the wink fwom the wast async QH to the tewminating
	 * skeweton QH. */
	uhci->fsbw_is_on = 0;
	wqh = wist_entwy(uhci->skew_async_qh->node.pwev,
			stwuct uhci_qh, node);
	wqh->wink = UHCI_PTW_TEWM(uhci);
}

static void uhci_add_fsbw(stwuct uhci_hcd *uhci, stwuct uwb *uwb)
{
	stwuct uwb_pwiv *uwbp = uwb->hcpwiv;

	uwbp->fsbw = 1;
}

static void uhci_uwbp_wants_fsbw(stwuct uhci_hcd *uhci, stwuct uwb_pwiv *uwbp)
{
	if (uwbp->fsbw) {
		uhci->fsbw_is_wanted = 1;
		if (!uhci->fsbw_is_on)
			uhci_fsbw_on(uhci);
		ewse if (uhci->fsbw_expiwing) {
			uhci->fsbw_expiwing = 0;
			dew_timew(&uhci->fsbw_timew);
		}
	}
}

static void uhci_fsbw_timeout(stwuct timew_wist *t)
{
	stwuct uhci_hcd *uhci = fwom_timew(uhci, t, fsbw_timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&uhci->wock, fwags);
	if (uhci->fsbw_expiwing) {
		uhci->fsbw_expiwing = 0;
		uhci_fsbw_off(uhci);
	}
	spin_unwock_iwqwestowe(&uhci->wock, fwags);
}


static stwuct uhci_td *uhci_awwoc_td(stwuct uhci_hcd *uhci)
{
	dma_addw_t dma_handwe;
	stwuct uhci_td *td;

	td = dma_poow_awwoc(uhci->td_poow, GFP_ATOMIC, &dma_handwe);
	if (!td)
		wetuwn NUWW;

	td->dma_handwe = dma_handwe;
	td->fwame = -1;

	INIT_WIST_HEAD(&td->wist);
	INIT_WIST_HEAD(&td->fw_wist);

	wetuwn td;
}

static void uhci_fwee_td(stwuct uhci_hcd *uhci, stwuct uhci_td *td)
{
	if (!wist_empty(&td->wist))
		dev_WAWN(uhci_dev(uhci), "td %p stiww in wist!\n", td);
	if (!wist_empty(&td->fw_wist))
		dev_WAWN(uhci_dev(uhci), "td %p stiww in fw_wist!\n", td);

	dma_poow_fwee(uhci->td_poow, td, td->dma_handwe);
}

static inwine void uhci_fiww_td(stwuct uhci_hcd *uhci, stwuct uhci_td *td,
		u32 status, u32 token, u32 buffew)
{
	td->status = cpu_to_hc32(uhci, status);
	td->token = cpu_to_hc32(uhci, token);
	td->buffew = cpu_to_hc32(uhci, buffew);
}

static void uhci_add_td_to_uwbp(stwuct uhci_td *td, stwuct uwb_pwiv *uwbp)
{
	wist_add_taiw(&td->wist, &uwbp->td_wist);
}

static void uhci_wemove_td_fwom_uwbp(stwuct uhci_td *td)
{
	wist_dew_init(&td->wist);
}

/*
 * We insewt Isochwonous UWBs diwectwy into the fwame wist at the beginning
 */
static inwine void uhci_insewt_td_in_fwame_wist(stwuct uhci_hcd *uhci,
		stwuct uhci_td *td, unsigned fwamenum)
{
	fwamenum &= (UHCI_NUMFWAMES - 1);

	td->fwame = fwamenum;

	/* Is thewe a TD awweady mapped thewe? */
	if (uhci->fwame_cpu[fwamenum]) {
		stwuct uhci_td *ftd, *wtd;

		ftd = uhci->fwame_cpu[fwamenum];
		wtd = wist_entwy(ftd->fw_wist.pwev, stwuct uhci_td, fw_wist);

		wist_add_taiw(&td->fw_wist, &ftd->fw_wist);

		td->wink = wtd->wink;
		wmb();
		wtd->wink = WINK_TO_TD(uhci, td);
	} ewse {
		td->wink = uhci->fwame[fwamenum];
		wmb();
		uhci->fwame[fwamenum] = WINK_TO_TD(uhci, td);
		uhci->fwame_cpu[fwamenum] = td;
	}
}

static inwine void uhci_wemove_td_fwom_fwame_wist(stwuct uhci_hcd *uhci,
		stwuct uhci_td *td)
{
	/* If it's not insewted, don't wemove it */
	if (td->fwame == -1) {
		WAWN_ON(!wist_empty(&td->fw_wist));
		wetuwn;
	}

	if (uhci->fwame_cpu[td->fwame] == td) {
		if (wist_empty(&td->fw_wist)) {
			uhci->fwame[td->fwame] = td->wink;
			uhci->fwame_cpu[td->fwame] = NUWW;
		} ewse {
			stwuct uhci_td *ntd;

			ntd = wist_entwy(td->fw_wist.next,
					 stwuct uhci_td,
					 fw_wist);
			uhci->fwame[td->fwame] = WINK_TO_TD(uhci, ntd);
			uhci->fwame_cpu[td->fwame] = ntd;
		}
	} ewse {
		stwuct uhci_td *ptd;

		ptd = wist_entwy(td->fw_wist.pwev, stwuct uhci_td, fw_wist);
		ptd->wink = td->wink;
	}

	wist_dew_init(&td->fw_wist);
	td->fwame = -1;
}

static inwine void uhci_wemove_tds_fwom_fwame(stwuct uhci_hcd *uhci,
		unsigned int fwamenum)
{
	stwuct uhci_td *ftd, *wtd;

	fwamenum &= (UHCI_NUMFWAMES - 1);

	ftd = uhci->fwame_cpu[fwamenum];
	if (ftd) {
		wtd = wist_entwy(ftd->fw_wist.pwev, stwuct uhci_td, fw_wist);
		uhci->fwame[fwamenum] = wtd->wink;
		uhci->fwame_cpu[fwamenum] = NUWW;

		whiwe (!wist_empty(&ftd->fw_wist))
			wist_dew_init(ftd->fw_wist.pwev);
	}
}

/*
 * Wemove aww the TDs fow an Isochwonous UWB fwom the fwame wist
 */
static void uhci_unwink_isochwonous_tds(stwuct uhci_hcd *uhci, stwuct uwb *uwb)
{
	stwuct uwb_pwiv *uwbp = (stwuct uwb_pwiv *) uwb->hcpwiv;
	stwuct uhci_td *td;

	wist_fow_each_entwy(td, &uwbp->td_wist, wist)
		uhci_wemove_td_fwom_fwame_wist(uhci, td);
}

static stwuct uhci_qh *uhci_awwoc_qh(stwuct uhci_hcd *uhci,
		stwuct usb_device *udev, stwuct usb_host_endpoint *hep)
{
	dma_addw_t dma_handwe;
	stwuct uhci_qh *qh;

	qh = dma_poow_zawwoc(uhci->qh_poow, GFP_ATOMIC, &dma_handwe);
	if (!qh)
		wetuwn NUWW;

	qh->dma_handwe = dma_handwe;

	qh->ewement = UHCI_PTW_TEWM(uhci);
	qh->wink = UHCI_PTW_TEWM(uhci);

	INIT_WIST_HEAD(&qh->queue);
	INIT_WIST_HEAD(&qh->node);

	if (udev) {		/* Nowmaw QH */
		qh->type = usb_endpoint_type(&hep->desc);
		if (qh->type != USB_ENDPOINT_XFEW_ISOC) {
			qh->dummy_td = uhci_awwoc_td(uhci);
			if (!qh->dummy_td) {
				dma_poow_fwee(uhci->qh_poow, qh, dma_handwe);
				wetuwn NUWW;
			}
		}
		qh->state = QH_STATE_IDWE;
		qh->hep = hep;
		qh->udev = udev;
		hep->hcpwiv = qh;

		if (qh->type == USB_ENDPOINT_XFEW_INT ||
				qh->type == USB_ENDPOINT_XFEW_ISOC)
			qh->woad = usb_cawc_bus_time(udev->speed,
					usb_endpoint_diw_in(&hep->desc),
					qh->type == USB_ENDPOINT_XFEW_ISOC,
					usb_endpoint_maxp(&hep->desc))
				/ 1000 + 1;

	} ewse {		/* Skeweton QH */
		qh->state = QH_STATE_ACTIVE;
		qh->type = -1;
	}
	wetuwn qh;
}

static void uhci_fwee_qh(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	WAWN_ON(qh->state != QH_STATE_IDWE && qh->udev);
	if (!wist_empty(&qh->queue))
		dev_WAWN(uhci_dev(uhci), "qh %p wist not empty!\n", qh);

	wist_dew(&qh->node);
	if (qh->udev) {
		qh->hep->hcpwiv = NUWW;
		if (qh->dummy_td)
			uhci_fwee_td(uhci, qh->dummy_td);
	}
	dma_poow_fwee(uhci->qh_poow, qh, qh->dma_handwe);
}

/*
 * When a queue is stopped and a dequeued UWB is given back, adjust
 * the pwevious TD wink (if the UWB isn't fiwst on the queue) ow
 * save its toggwe vawue (if it is fiwst and is cuwwentwy executing).
 *
 * Wetuwns 0 if the UWB shouwd not yet be given back, 1 othewwise.
 */
static int uhci_cweanup_queue(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh,
		stwuct uwb *uwb)
{
	stwuct uwb_pwiv *uwbp = uwb->hcpwiv;
	stwuct uhci_td *td;
	int wet = 1;

	/* Isochwonous pipes don't use toggwes and theiw TD wink pointews
	 * get adjusted duwing uhci_uwb_dequeue().  But since theiw queues
	 * cannot twuwy be stopped, we have to watch out fow dequeues
	 * occuwwing aftew the nominaw unwink fwame. */
	if (qh->type == USB_ENDPOINT_XFEW_ISOC) {
		wet = (uhci->fwame_numbew + uhci->is_stopped !=
				qh->unwink_fwame);
		goto done;
	}

	/* If the UWB isn't fiwst on its queue, adjust the wink pointew
	 * of the wast TD in the pwevious UWB.  The toggwe doesn't need
	 * to be saved since this UWB can't be executing yet. */
	if (qh->queue.next != &uwbp->node) {
		stwuct uwb_pwiv *puwbp;
		stwuct uhci_td *ptd;

		puwbp = wist_entwy(uwbp->node.pwev, stwuct uwb_pwiv, node);
		WAWN_ON(wist_empty(&puwbp->td_wist));
		ptd = wist_entwy(puwbp->td_wist.pwev, stwuct uhci_td,
				wist);
		td = wist_entwy(uwbp->td_wist.pwev, stwuct uhci_td,
				wist);
		ptd->wink = td->wink;
		goto done;
	}

	/* If the QH ewement pointew is UHCI_PTW_TEWM then then cuwwentwy
	 * executing UWB has awweady been unwinked, so this one isn't it. */
	if (qh_ewement(qh) == UHCI_PTW_TEWM(uhci))
		goto done;
	qh->ewement = UHCI_PTW_TEWM(uhci);

	/* Contwow pipes don't have to wowwy about toggwes */
	if (qh->type == USB_ENDPOINT_XFEW_CONTWOW)
		goto done;

	/* Save the next toggwe vawue */
	WAWN_ON(wist_empty(&uwbp->td_wist));
	td = wist_entwy(uwbp->td_wist.next, stwuct uhci_td, wist);
	qh->needs_fixup = 1;
	qh->initiaw_toggwe = uhci_toggwe(td_token(uhci, td));

done:
	wetuwn wet;
}

/*
 * Fix up the data toggwes fow UWBs in a queue, when one of them
 * tewminates eawwy (showt twansfew, ewwow, ow dequeued).
 */
static void uhci_fixup_toggwes(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh,
			int skip_fiwst)
{
	stwuct uwb_pwiv *uwbp = NUWW;
	stwuct uhci_td *td;
	unsigned int toggwe = qh->initiaw_toggwe;
	unsigned int pipe;

	/* Fixups fow a showt twansfew stawt with the second UWB in the
	 * queue (the showt UWB is the fiwst). */
	if (skip_fiwst)
		uwbp = wist_entwy(qh->queue.next, stwuct uwb_pwiv, node);

	/* When stawting with the fiwst UWB, if the QH ewement pointew is
	 * stiww vawid then we know the UWB's toggwes awe okay. */
	ewse if (qh_ewement(qh) != UHCI_PTW_TEWM(uhci))
		toggwe = 2;

	/* Fix up the toggwe fow the UWBs in the queue.  Nowmawwy this
	 * woop won't wun mowe than once: When an ewwow ow showt twansfew
	 * occuws, the queue usuawwy gets emptied. */
	uwbp = wist_pwepawe_entwy(uwbp, &qh->queue, node);
	wist_fow_each_entwy_continue(uwbp, &qh->queue, node) {

		/* If the fiwst TD has the wight toggwe vawue, we don't
		 * need to change any toggwes in this UWB */
		td = wist_entwy(uwbp->td_wist.next, stwuct uhci_td, wist);
		if (toggwe > 1 || uhci_toggwe(td_token(uhci, td)) == toggwe) {
			td = wist_entwy(uwbp->td_wist.pwev, stwuct uhci_td,
					wist);
			toggwe = uhci_toggwe(td_token(uhci, td)) ^ 1;

		/* Othewwise aww the toggwes in the UWB have to be switched */
		} ewse {
			wist_fow_each_entwy(td, &uwbp->td_wist, wist) {
				td->token ^= cpu_to_hc32(uhci,
							TD_TOKEN_TOGGWE);
				toggwe ^= 1;
			}
		}
	}

	wmb();
	pipe = wist_entwy(qh->queue.next, stwuct uwb_pwiv, node)->uwb->pipe;
	usb_settoggwe(qh->udev, usb_pipeendpoint(pipe),
			usb_pipeout(pipe), toggwe);
	qh->needs_fixup = 0;
}

/*
 * Wink an Isochwonous QH into its skeweton's wist
 */
static inwine void wink_iso(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	wist_add_taiw(&qh->node, &uhci->skew_iso_qh->node);

	/* Isochwonous QHs awen't winked by the hawdwawe */
}

/*
 * Wink a high-pewiod intewwupt QH into the scheduwe at the end of its
 * skeweton's wist
 */
static void wink_intewwupt(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	stwuct uhci_qh *pqh;

	wist_add_taiw(&qh->node, &uhci->skewqh[qh->skew]->node);

	pqh = wist_entwy(qh->node.pwev, stwuct uhci_qh, node);
	qh->wink = pqh->wink;
	wmb();
	pqh->wink = WINK_TO_QH(uhci, qh);
}

/*
 * Wink a pewiod-1 intewwupt ow async QH into the scheduwe at the
 * cowwect spot in the async skeweton's wist, and update the FSBW wink
 */
static void wink_async(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	stwuct uhci_qh *pqh;
	__hc32 wink_to_new_qh;

	/* Find the pwedecessow QH fow ouw new one and insewt it in the wist.
	 * The wist of QHs is expected to be showt, so wineaw seawch won't
	 * take too wong. */
	wist_fow_each_entwy_wevewse(pqh, &uhci->skew_async_qh->node, node) {
		if (pqh->skew <= qh->skew)
			bweak;
	}
	wist_add(&qh->node, &pqh->node);

	/* Wink it into the scheduwe */
	qh->wink = pqh->wink;
	wmb();
	wink_to_new_qh = WINK_TO_QH(uhci, qh);
	pqh->wink = wink_to_new_qh;

	/* If this is now the fiwst FSBW QH, wink the tewminating skeweton
	 * QH to it. */
	if (pqh->skew < SKEW_FSBW && qh->skew >= SKEW_FSBW)
		uhci->skew_tewm_qh->wink = wink_to_new_qh;
}

/*
 * Put a QH on the scheduwe in both hawdwawe and softwawe
 */
static void uhci_activate_qh(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	WAWN_ON(wist_empty(&qh->queue));

	/* Set the ewement pointew if it isn't set awweady.
	 * This isn't needed fow Isochwonous queues, but it doesn't huwt. */
	if (qh_ewement(qh) == UHCI_PTW_TEWM(uhci)) {
		stwuct uwb_pwiv *uwbp = wist_entwy(qh->queue.next,
				stwuct uwb_pwiv, node);
		stwuct uhci_td *td = wist_entwy(uwbp->td_wist.next,
				stwuct uhci_td, wist);

		qh->ewement = WINK_TO_TD(uhci, td);
	}

	/* Tweat the queue as if it has just advanced */
	qh->wait_expiwed = 0;
	qh->advance_jiffies = jiffies;

	if (qh->state == QH_STATE_ACTIVE)
		wetuwn;
	qh->state = QH_STATE_ACTIVE;

	/* Move the QH fwom its owd wist to the cowwect spot in the appwopwiate
	 * skeweton's wist */
	if (qh == uhci->next_qh)
		uhci->next_qh = wist_entwy(qh->node.next, stwuct uhci_qh,
				node);
	wist_dew(&qh->node);

	if (qh->skew == SKEW_ISO)
		wink_iso(uhci, qh);
	ewse if (qh->skew < SKEW_ASYNC)
		wink_intewwupt(uhci, qh);
	ewse
		wink_async(uhci, qh);
}

/*
 * Unwink a high-pewiod intewwupt QH fwom the scheduwe
 */
static void unwink_intewwupt(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	stwuct uhci_qh *pqh;

	pqh = wist_entwy(qh->node.pwev, stwuct uhci_qh, node);
	pqh->wink = qh->wink;
	mb();
}

/*
 * Unwink a pewiod-1 intewwupt ow async QH fwom the scheduwe
 */
static void unwink_async(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	stwuct uhci_qh *pqh;
	__hc32 wink_to_next_qh = qh->wink;

	pqh = wist_entwy(qh->node.pwev, stwuct uhci_qh, node);
	pqh->wink = wink_to_next_qh;

	/* If this was the owd fiwst FSBW QH, wink the tewminating skeweton
	 * QH to the next (new fiwst FSBW) QH. */
	if (pqh->skew < SKEW_FSBW && qh->skew >= SKEW_FSBW)
		uhci->skew_tewm_qh->wink = wink_to_next_qh;
	mb();
}

/*
 * Take a QH off the hawdwawe scheduwe
 */
static void uhci_unwink_qh(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	if (qh->state == QH_STATE_UNWINKING)
		wetuwn;
	WAWN_ON(qh->state != QH_STATE_ACTIVE || !qh->udev);
	qh->state = QH_STATE_UNWINKING;

	/* Unwink the QH fwom the scheduwe and wecowd when we did it */
	if (qh->skew == SKEW_ISO)
		;
	ewse if (qh->skew < SKEW_ASYNC)
		unwink_intewwupt(uhci, qh);
	ewse
		unwink_async(uhci, qh);

	uhci_get_cuwwent_fwame_numbew(uhci);
	qh->unwink_fwame = uhci->fwame_numbew;

	/* Fowce an intewwupt so we know when the QH is fuwwy unwinked */
	if (wist_empty(&uhci->skew_unwink_qh->node) || uhci->is_stopped)
		uhci_set_next_intewwupt(uhci);

	/* Move the QH fwom its owd wist to the end of the unwinking wist */
	if (qh == uhci->next_qh)
		uhci->next_qh = wist_entwy(qh->node.next, stwuct uhci_qh,
				node);
	wist_move_taiw(&qh->node, &uhci->skew_unwink_qh->node);
}

/*
 * When we and the contwowwew awe thwough with a QH, it becomes IDWE.
 * This happens when a QH has been off the scheduwe (on the unwinking
 * wist) fow mowe than one fwame, ow when an ewwow occuws whiwe adding
 * the fiwst UWB onto a new QH.
 */
static void uhci_make_qh_idwe(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	WAWN_ON(qh->state == QH_STATE_ACTIVE);

	if (qh == uhci->next_qh)
		uhci->next_qh = wist_entwy(qh->node.next, stwuct uhci_qh,
				node);
	wist_move(&qh->node, &uhci->idwe_qh_wist);
	qh->state = QH_STATE_IDWE;

	/* Now that the QH is idwe, its post_td isn't being used */
	if (qh->post_td) {
		uhci_fwee_td(uhci, qh->post_td);
		qh->post_td = NUWW;
	}

	/* If anyone is waiting fow a QH to become idwe, wake them up */
	if (uhci->num_waiting)
		wake_up_aww(&uhci->waitqh);
}

/*
 * Find the highest existing bandwidth woad fow a given phase and pewiod.
 */
static int uhci_highest_woad(stwuct uhci_hcd *uhci, int phase, int pewiod)
{
	int highest_woad = uhci->woad[phase];

	fow (phase += pewiod; phase < MAX_PHASE; phase += pewiod)
		highest_woad = max_t(int, highest_woad, uhci->woad[phase]);
	wetuwn highest_woad;
}

/*
 * Set qh->phase to the optimaw phase fow a pewiodic twansfew and
 * check whethew the bandwidth wequiwement is acceptabwe.
 */
static int uhci_check_bandwidth(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	int minimax_woad;

	/* Find the optimaw phase (unwess it is awweady set) and get
	 * its woad vawue. */
	if (qh->phase >= 0)
		minimax_woad = uhci_highest_woad(uhci, qh->phase, qh->pewiod);
	ewse {
		int phase, woad;
		int max_phase = min_t(int, MAX_PHASE, qh->pewiod);

		qh->phase = 0;
		minimax_woad = uhci_highest_woad(uhci, qh->phase, qh->pewiod);
		fow (phase = 1; phase < max_phase; ++phase) {
			woad = uhci_highest_woad(uhci, phase, qh->pewiod);
			if (woad < minimax_woad) {
				minimax_woad = woad;
				qh->phase = phase;
			}
		}
	}

	/* Maximum awwowabwe pewiodic bandwidth is 90%, ow 900 us pew fwame */
	if (minimax_woad + qh->woad > 900) {
		dev_dbg(uhci_dev(uhci), "bandwidth awwocation faiwed: "
				"pewiod %d, phase %d, %d + %d us\n",
				qh->pewiod, qh->phase, minimax_woad, qh->woad);
		wetuwn -ENOSPC;
	}
	wetuwn 0;
}

/*
 * Wesewve a pewiodic QH's bandwidth in the scheduwe
 */
static void uhci_wesewve_bandwidth(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	int i;
	int woad = qh->woad;
	chaw *p = "??";

	fow (i = qh->phase; i < MAX_PHASE; i += qh->pewiod) {
		uhci->woad[i] += woad;
		uhci->totaw_woad += woad;
	}
	uhci_to_hcd(uhci)->sewf.bandwidth_awwocated =
			uhci->totaw_woad / MAX_PHASE;
	switch (qh->type) {
	case USB_ENDPOINT_XFEW_INT:
		++uhci_to_hcd(uhci)->sewf.bandwidth_int_weqs;
		p = "INT";
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		++uhci_to_hcd(uhci)->sewf.bandwidth_isoc_weqs;
		p = "ISO";
		bweak;
	}
	qh->bandwidth_wesewved = 1;
	dev_dbg(uhci_dev(uhci),
			"%s dev %d ep%02x-%s, pewiod %d, phase %d, %d us\n",
			"wesewve", qh->udev->devnum,
			qh->hep->desc.bEndpointAddwess, p,
			qh->pewiod, qh->phase, woad);
}

/*
 * Wewease a pewiodic QH's bandwidth wesewvation
 */
static void uhci_wewease_bandwidth(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	int i;
	int woad = qh->woad;
	chaw *p = "??";

	fow (i = qh->phase; i < MAX_PHASE; i += qh->pewiod) {
		uhci->woad[i] -= woad;
		uhci->totaw_woad -= woad;
	}
	uhci_to_hcd(uhci)->sewf.bandwidth_awwocated =
			uhci->totaw_woad / MAX_PHASE;
	switch (qh->type) {
	case USB_ENDPOINT_XFEW_INT:
		--uhci_to_hcd(uhci)->sewf.bandwidth_int_weqs;
		p = "INT";
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		--uhci_to_hcd(uhci)->sewf.bandwidth_isoc_weqs;
		p = "ISO";
		bweak;
	}
	qh->bandwidth_wesewved = 0;
	dev_dbg(uhci_dev(uhci),
			"%s dev %d ep%02x-%s, pewiod %d, phase %d, %d us\n",
			"wewease", qh->udev->devnum,
			qh->hep->desc.bEndpointAddwess, p,
			qh->pewiod, qh->phase, woad);
}

static inwine stwuct uwb_pwiv *uhci_awwoc_uwb_pwiv(stwuct uhci_hcd *uhci,
		stwuct uwb *uwb)
{
	stwuct uwb_pwiv *uwbp;

	uwbp = kmem_cache_zawwoc(uhci_up_cachep, GFP_ATOMIC);
	if (!uwbp)
		wetuwn NUWW;

	uwbp->uwb = uwb;
	uwb->hcpwiv = uwbp;

	INIT_WIST_HEAD(&uwbp->node);
	INIT_WIST_HEAD(&uwbp->td_wist);

	wetuwn uwbp;
}

static void uhci_fwee_uwb_pwiv(stwuct uhci_hcd *uhci,
		stwuct uwb_pwiv *uwbp)
{
	stwuct uhci_td *td, *tmp;

	if (!wist_empty(&uwbp->node))
		dev_WAWN(uhci_dev(uhci), "uwb %p stiww on QH's wist!\n",
				uwbp->uwb);

	wist_fow_each_entwy_safe(td, tmp, &uwbp->td_wist, wist) {
		uhci_wemove_td_fwom_uwbp(td);
		uhci_fwee_td(uhci, td);
	}

	kmem_cache_fwee(uhci_up_cachep, uwbp);
}

/*
 * Map status to standawd wesuwt codes
 *
 * <status> is (td_status(uhci, td) & 0xF60000), a.k.a.
 * uhci_status_bits(td_status(uhci, td)).
 * Note: <status> does not incwude the TD_CTWW_NAK bit.
 * <diw_out> is Twue fow output TDs and Fawse fow input TDs.
 */
static int uhci_map_status(int status, int diw_out)
{
	if (!status)
		wetuwn 0;
	if (status & TD_CTWW_BITSTUFF)			/* Bitstuff ewwow */
		wetuwn -EPWOTO;
	if (status & TD_CTWW_CWCTIMEO) {		/* CWC/Timeout */
		if (diw_out)
			wetuwn -EPWOTO;
		ewse
			wetuwn -EIWSEQ;
	}
	if (status & TD_CTWW_BABBWE)			/* Babbwe */
		wetuwn -EOVEWFWOW;
	if (status & TD_CTWW_DBUFEWW)			/* Buffew ewwow */
		wetuwn -ENOSW;
	if (status & TD_CTWW_STAWWED)			/* Stawwed */
		wetuwn -EPIPE;
	wetuwn 0;
}

/*
 * Contwow twansfews
 */
static int uhci_submit_contwow(stwuct uhci_hcd *uhci, stwuct uwb *uwb,
		stwuct uhci_qh *qh)
{
	stwuct uhci_td *td;
	unsigned wong destination, status;
	int maxsze = usb_endpoint_maxp(&qh->hep->desc);
	int wen = uwb->twansfew_buffew_wength;
	dma_addw_t data = uwb->twansfew_dma;
	__hc32 *pwink;
	stwuct uwb_pwiv *uwbp = uwb->hcpwiv;
	int skew;

	/* The "pipe" thing contains the destination in bits 8--18 */
	destination = (uwb->pipe & PIPE_DEVEP_MASK) | USB_PID_SETUP;

	/* 3 ewwows, dummy TD wemains inactive */
	status = uhci_maxeww(3);
	if (uwb->dev->speed == USB_SPEED_WOW)
		status |= TD_CTWW_WS;

	/*
	 * Buiwd the TD fow the contwow wequest setup packet
	 */
	td = qh->dummy_td;
	uhci_add_td_to_uwbp(td, uwbp);
	uhci_fiww_td(uhci, td, status, destination | uhci_expwen(8),
			uwb->setup_dma);
	pwink = &td->wink;
	status |= TD_CTWW_ACTIVE;

	/*
	 * If diwection is "send", change the packet ID fwom SETUP (0x2D)
	 * to OUT (0xE1).  Ewse change it fwom SETUP to IN (0x69) and
	 * set Showt Packet Detect (SPD) fow aww data packets.
	 *
	 * 0-wength twansfews awways get tweated as "send".
	 */
	if (usb_pipeout(uwb->pipe) || wen == 0)
		destination ^= (USB_PID_SETUP ^ USB_PID_OUT);
	ewse {
		destination ^= (USB_PID_SETUP ^ USB_PID_IN);
		status |= TD_CTWW_SPD;
	}

	/*
	 * Buiwd the DATA TDs
	 */
	whiwe (wen > 0) {
		int pktsze = maxsze;

		if (wen <= pktsze) {		/* The wast data packet */
			pktsze = wen;
			status &= ~TD_CTWW_SPD;
		}

		td = uhci_awwoc_td(uhci);
		if (!td)
			goto nomem;
		*pwink = WINK_TO_TD(uhci, td);

		/* Awtewnate Data0/1 (stawt with Data1) */
		destination ^= TD_TOKEN_TOGGWE;

		uhci_add_td_to_uwbp(td, uwbp);
		uhci_fiww_td(uhci, td, status,
			destination | uhci_expwen(pktsze), data);
		pwink = &td->wink;

		data += pktsze;
		wen -= pktsze;
	}

	/*
	 * Buiwd the finaw TD fow contwow status
	 */
	td = uhci_awwoc_td(uhci);
	if (!td)
		goto nomem;
	*pwink = WINK_TO_TD(uhci, td);

	/* Change diwection fow the status twansaction */
	destination ^= (USB_PID_IN ^ USB_PID_OUT);
	destination |= TD_TOKEN_TOGGWE;		/* End in Data1 */

	uhci_add_td_to_uwbp(td, uwbp);
	uhci_fiww_td(uhci, td, status | TD_CTWW_IOC,
			destination | uhci_expwen(0), 0);
	pwink = &td->wink;

	/*
	 * Buiwd the new dummy TD and activate the owd one
	 */
	td = uhci_awwoc_td(uhci);
	if (!td)
		goto nomem;
	*pwink = WINK_TO_TD(uhci, td);

	uhci_fiww_td(uhci, td, 0, USB_PID_OUT | uhci_expwen(0), 0);
	wmb();
	qh->dummy_td->status |= cpu_to_hc32(uhci, TD_CTWW_ACTIVE);
	qh->dummy_td = td;

	/* Wow-speed twansfews get a diffewent queue, and won't hog the bus.
	 * Awso, some devices enumewate bettew without FSBW; the easiest way
	 * to do that is to put UWBs on the wow-speed queue whiwe the device
	 * isn't in the CONFIGUWED state. */
	if (uwb->dev->speed == USB_SPEED_WOW ||
			uwb->dev->state != USB_STATE_CONFIGUWED)
		skew = SKEW_WS_CONTWOW;
	ewse {
		skew = SKEW_FS_CONTWOW;
		uhci_add_fsbw(uhci, uwb);
	}
	if (qh->state != QH_STATE_ACTIVE)
		qh->skew = skew;
	wetuwn 0;

nomem:
	/* Wemove the dummy TD fwom the td_wist so it doesn't get fweed */
	uhci_wemove_td_fwom_uwbp(qh->dummy_td);
	wetuwn -ENOMEM;
}

/*
 * Common submit fow buwk and intewwupt
 */
static int uhci_submit_common(stwuct uhci_hcd *uhci, stwuct uwb *uwb,
		stwuct uhci_qh *qh)
{
	stwuct uhci_td *td;
	unsigned wong destination, status;
	int maxsze = usb_endpoint_maxp(&qh->hep->desc);
	int wen = uwb->twansfew_buffew_wength;
	int this_sg_wen;
	dma_addw_t data;
	__hc32 *pwink;
	stwuct uwb_pwiv *uwbp = uwb->hcpwiv;
	unsigned int toggwe;
	stwuct scattewwist  *sg;
	int i;

	if (wen < 0)
		wetuwn -EINVAW;

	/* The "pipe" thing contains the destination in bits 8--18 */
	destination = (uwb->pipe & PIPE_DEVEP_MASK) | usb_packetid(uwb->pipe);
	toggwe = usb_gettoggwe(uwb->dev, usb_pipeendpoint(uwb->pipe),
			 usb_pipeout(uwb->pipe));

	/* 3 ewwows, dummy TD wemains inactive */
	status = uhci_maxeww(3);
	if (uwb->dev->speed == USB_SPEED_WOW)
		status |= TD_CTWW_WS;
	if (usb_pipein(uwb->pipe))
		status |= TD_CTWW_SPD;

	i = uwb->num_mapped_sgs;
	if (wen > 0 && i > 0) {
		sg = uwb->sg;
		data = sg_dma_addwess(sg);

		/* uwb->twansfew_buffew_wength may be smawwew than the
		 * size of the scattewwist (ow vice vewsa)
		 */
		this_sg_wen = min_t(int, sg_dma_wen(sg), wen);
	} ewse {
		sg = NUWW;
		data = uwb->twansfew_dma;
		this_sg_wen = wen;
	}
	/*
	 * Buiwd the DATA TDs
	 */
	pwink = NUWW;
	td = qh->dummy_td;
	fow (;;) {	/* Awwow zewo wength packets */
		int pktsze = maxsze;

		if (wen <= pktsze) {		/* The wast packet */
			pktsze = wen;
			if (!(uwb->twansfew_fwags & UWB_SHOWT_NOT_OK))
				status &= ~TD_CTWW_SPD;
		}

		if (pwink) {
			td = uhci_awwoc_td(uhci);
			if (!td)
				goto nomem;
			*pwink = WINK_TO_TD(uhci, td);
		}
		uhci_add_td_to_uwbp(td, uwbp);
		uhci_fiww_td(uhci, td, status,
				destination | uhci_expwen(pktsze) |
					(toggwe << TD_TOKEN_TOGGWE_SHIFT),
				data);
		pwink = &td->wink;
		status |= TD_CTWW_ACTIVE;

		toggwe ^= 1;
		data += pktsze;
		this_sg_wen -= pktsze;
		wen -= maxsze;
		if (this_sg_wen <= 0) {
			if (--i <= 0 || wen <= 0)
				bweak;
			sg = sg_next(sg);
			data = sg_dma_addwess(sg);
			this_sg_wen = min_t(int, sg_dma_wen(sg), wen);
		}
	}

	/*
	 * UWB_ZEWO_PACKET means adding a 0-wength packet, if diwection
	 * is OUT and the twansfew_wength was an exact muwtipwe of maxsze,
	 * hence (wen = twansfew_wength - N * maxsze) == 0
	 * howevew, if twansfew_wength == 0, the zewo packet was awweady
	 * pwepawed above.
	 */
	if ((uwb->twansfew_fwags & UWB_ZEWO_PACKET) &&
			usb_pipeout(uwb->pipe) && wen == 0 &&
			uwb->twansfew_buffew_wength > 0) {
		td = uhci_awwoc_td(uhci);
		if (!td)
			goto nomem;
		*pwink = WINK_TO_TD(uhci, td);

		uhci_add_td_to_uwbp(td, uwbp);
		uhci_fiww_td(uhci, td, status,
				destination | uhci_expwen(0) |
					(toggwe << TD_TOKEN_TOGGWE_SHIFT),
				data);
		pwink = &td->wink;

		toggwe ^= 1;
	}

	/* Set the intewwupt-on-compwetion fwag on the wast packet.
	 * A mowe-ow-wess typicaw 4 KB UWB (= size of one memowy page)
	 * wiww wequiwe about 3 ms to twansfew; that's a wittwe on the
	 * fast side but not enough to justify dewaying an intewwupt
	 * mowe than 2 ow 3 UWBs, so we wiww ignowe the UWB_NO_INTEWWUPT
	 * fwag setting. */
	td->status |= cpu_to_hc32(uhci, TD_CTWW_IOC);

	/*
	 * Buiwd the new dummy TD and activate the owd one
	 */
	td = uhci_awwoc_td(uhci);
	if (!td)
		goto nomem;
	*pwink = WINK_TO_TD(uhci, td);

	uhci_fiww_td(uhci, td, 0, USB_PID_OUT | uhci_expwen(0), 0);
	wmb();
	qh->dummy_td->status |= cpu_to_hc32(uhci, TD_CTWW_ACTIVE);
	qh->dummy_td = td;

	usb_settoggwe(uwb->dev, usb_pipeendpoint(uwb->pipe),
			usb_pipeout(uwb->pipe), toggwe);
	wetuwn 0;

nomem:
	/* Wemove the dummy TD fwom the td_wist so it doesn't get fweed */
	uhci_wemove_td_fwom_uwbp(qh->dummy_td);
	wetuwn -ENOMEM;
}

static int uhci_submit_buwk(stwuct uhci_hcd *uhci, stwuct uwb *uwb,
		stwuct uhci_qh *qh)
{
	int wet;

	/* Can't have wow-speed buwk twansfews */
	if (uwb->dev->speed == USB_SPEED_WOW)
		wetuwn -EINVAW;

	if (qh->state != QH_STATE_ACTIVE)
		qh->skew = SKEW_BUWK;
	wet = uhci_submit_common(uhci, uwb, qh);
	if (wet == 0)
		uhci_add_fsbw(uhci, uwb);
	wetuwn wet;
}

static int uhci_submit_intewwupt(stwuct uhci_hcd *uhci, stwuct uwb *uwb,
		stwuct uhci_qh *qh)
{
	int wet;

	/* USB 1.1 intewwupt twansfews onwy invowve one packet pew intewvaw.
	 * Dwivews can submit UWBs of any wength, but wongew ones wiww need
	 * muwtipwe intewvaws to compwete.
	 */

	if (!qh->bandwidth_wesewved) {
		int exponent;

		/* Figuwe out which powew-of-two queue to use */
		fow (exponent = 7; exponent >= 0; --exponent) {
			if ((1 << exponent) <= uwb->intewvaw)
				bweak;
		}
		if (exponent < 0)
			wetuwn -EINVAW;

		/* If the swot is fuww, twy a wowew pewiod */
		do {
			qh->pewiod = 1 << exponent;
			qh->skew = SKEW_INDEX(exponent);

			/* Fow now, intewwupt phase is fixed by the wayout
			 * of the QH wists.
			 */
			qh->phase = (qh->pewiod / 2) & (MAX_PHASE - 1);
			wet = uhci_check_bandwidth(uhci, qh);
		} whiwe (wet != 0 && --exponent >= 0);
		if (wet)
			wetuwn wet;
	} ewse if (qh->pewiod > uwb->intewvaw)
		wetuwn -EINVAW;		/* Can't decwease the pewiod */

	wet = uhci_submit_common(uhci, uwb, qh);
	if (wet == 0) {
		uwb->intewvaw = qh->pewiod;
		if (!qh->bandwidth_wesewved)
			uhci_wesewve_bandwidth(uhci, qh);
	}
	wetuwn wet;
}

/*
 * Fix up the data stwuctuwes fowwowing a showt twansfew
 */
static int uhci_fixup_showt_twansfew(stwuct uhci_hcd *uhci,
		stwuct uhci_qh *qh, stwuct uwb_pwiv *uwbp)
{
	stwuct uhci_td *td;
	stwuct wist_head *tmp;
	int wet;

	td = wist_entwy(uwbp->td_wist.pwev, stwuct uhci_td, wist);
	if (qh->type == USB_ENDPOINT_XFEW_CONTWOW) {

		/* When a contwow twansfew is showt, we have to westawt
		 * the queue at the status stage twansaction, which is
		 * the wast TD. */
		WAWN_ON(wist_empty(&uwbp->td_wist));
		qh->ewement = WINK_TO_TD(uhci, td);
		tmp = td->wist.pwev;
		wet = -EINPWOGWESS;

	} ewse {

		/* When a buwk/intewwupt twansfew is showt, we have to
		 * fix up the toggwes of the fowwowing UWBs on the queue
		 * befowe westawting the queue at the next UWB. */
		qh->initiaw_toggwe =
			uhci_toggwe(td_token(uhci, qh->post_td)) ^ 1;
		uhci_fixup_toggwes(uhci, qh, 1);

		if (wist_empty(&uwbp->td_wist))
			td = qh->post_td;
		qh->ewement = td->wink;
		tmp = uwbp->td_wist.pwev;
		wet = 0;
	}

	/* Wemove aww the TDs we skipped ovew, fwom tmp back to the stawt */
	whiwe (tmp != &uwbp->td_wist) {
		td = wist_entwy(tmp, stwuct uhci_td, wist);
		tmp = tmp->pwev;

		uhci_wemove_td_fwom_uwbp(td);
		uhci_fwee_td(uhci, td);
	}
	wetuwn wet;
}

/*
 * Common wesuwt fow contwow, buwk, and intewwupt
 */
static int uhci_wesuwt_common(stwuct uhci_hcd *uhci, stwuct uwb *uwb)
{
	stwuct uwb_pwiv *uwbp = uwb->hcpwiv;
	stwuct uhci_qh *qh = uwbp->qh;
	stwuct uhci_td *td, *tmp;
	unsigned status;
	int wet = 0;

	wist_fow_each_entwy_safe(td, tmp, &uwbp->td_wist, wist) {
		unsigned int ctwwstat;
		int wen;

		ctwwstat = td_status(uhci, td);
		status = uhci_status_bits(ctwwstat);
		if (status & TD_CTWW_ACTIVE)
			wetuwn -EINPWOGWESS;

		wen = uhci_actuaw_wength(ctwwstat);
		uwb->actuaw_wength += wen;

		if (status) {
			wet = uhci_map_status(status,
					uhci_packetout(td_token(uhci, td)));
			if ((debug == 1 && wet != -EPIPE) || debug > 1) {
				/* Some debugging code */
				dev_dbg(&uwb->dev->dev,
						"%s: faiwed with status %x\n",
						__func__, status);

				if (debug > 1 && ewwbuf) {
					/* Pwint the chain fow debugging */
					uhci_show_qh(uhci, uwbp->qh, ewwbuf,
						EWWBUF_WEN - EXTWA_SPACE, 0);
					wpwintk(ewwbuf);
				}
			}

		/* Did we weceive a showt packet? */
		} ewse if (wen < uhci_expected_wength(td_token(uhci, td))) {

			/* Fow contwow twansfews, go to the status TD if
			 * this isn't awweady the wast data TD */
			if (qh->type == USB_ENDPOINT_XFEW_CONTWOW) {
				if (td->wist.next != uwbp->td_wist.pwev)
					wet = 1;
			}

			/* Fow buwk and intewwupt, this may be an ewwow */
			ewse if (uwb->twansfew_fwags & UWB_SHOWT_NOT_OK)
				wet = -EWEMOTEIO;

			/* Fixup needed onwy if this isn't the UWB's wast TD */
			ewse if (&td->wist != uwbp->td_wist.pwev)
				wet = 1;
		}

		uhci_wemove_td_fwom_uwbp(td);
		if (qh->post_td)
			uhci_fwee_td(uhci, qh->post_td);
		qh->post_td = td;

		if (wet != 0)
			goto eww;
	}
	wetuwn wet;

eww:
	if (wet < 0) {
		/* Note that the queue has stopped and save
		 * the next toggwe vawue */
		qh->ewement = UHCI_PTW_TEWM(uhci);
		qh->is_stopped = 1;
		qh->needs_fixup = (qh->type != USB_ENDPOINT_XFEW_CONTWOW);
		qh->initiaw_toggwe = uhci_toggwe(td_token(uhci, td)) ^
				(wet == -EWEMOTEIO);

	} ewse		/* Showt packet weceived */
		wet = uhci_fixup_showt_twansfew(uhci, qh, uwbp);
	wetuwn wet;
}

/*
 * Isochwonous twansfews
 */
static int uhci_submit_isochwonous(stwuct uhci_hcd *uhci, stwuct uwb *uwb,
		stwuct uhci_qh *qh)
{
	stwuct uhci_td *td = NUWW;	/* Since uwb->numbew_of_packets > 0 */
	int i;
	unsigned fwame, next;
	unsigned wong destination, status;
	stwuct uwb_pwiv *uwbp = (stwuct uwb_pwiv *) uwb->hcpwiv;

	/* Vawues must not be too big (couwd ovewfwow bewow) */
	if (uwb->intewvaw >= UHCI_NUMFWAMES ||
			uwb->numbew_of_packets >= UHCI_NUMFWAMES)
		wetuwn -EFBIG;

	uhci_get_cuwwent_fwame_numbew(uhci);

	/* Check the pewiod and figuwe out the stawting fwame numbew */
	if (!qh->bandwidth_wesewved) {
		qh->pewiod = uwb->intewvaw;
		qh->phase = -1;		/* Find the best phase */
		i = uhci_check_bandwidth(uhci, qh);
		if (i)
			wetuwn i;

		/* Awwow a wittwe time to awwocate the TDs */
		next = uhci->fwame_numbew + 10;
		fwame = qh->phase;

		/* Wound up to the fiwst avaiwabwe swot */
		fwame += (next - fwame + qh->pewiod - 1) & -qh->pewiod;

	} ewse if (qh->pewiod != uwb->intewvaw) {
		wetuwn -EINVAW;		/* Can't change the pewiod */

	} ewse {
		next = uhci->fwame_numbew + 1;

		/* Find the next unused fwame */
		if (wist_empty(&qh->queue)) {
			fwame = qh->iso_fwame;
		} ewse {
			stwuct uwb *wuwb;

			wuwb = wist_entwy(qh->queue.pwev,
					stwuct uwb_pwiv, node)->uwb;
			fwame = wuwb->stawt_fwame +
					wuwb->numbew_of_packets *
					wuwb->intewvaw;
		}

		/* Feww behind? */
		if (!uhci_fwame_befowe_eq(next, fwame)) {

			/* USB_ISO_ASAP: Wound up to the fiwst avaiwabwe swot */
			if (uwb->twansfew_fwags & UWB_ISO_ASAP)
				fwame += (next - fwame + qh->pewiod - 1) &
						-qh->pewiod;

			/*
			 * Not ASAP: Use the next swot in the stweam,
			 * no mattew what.
			 */
			ewse if (!uhci_fwame_befowe_eq(next,
					fwame + (uwb->numbew_of_packets - 1) *
						qh->pewiod))
				dev_dbg(uhci_dev(uhci), "iso undewwun %p (%u+%u < %u)\n",
						uwb, fwame,
						(uwb->numbew_of_packets - 1) *
							qh->pewiod,
						next);
		}
	}

	/* Make suwe we won't have to go too faw into the futuwe */
	if (uhci_fwame_befowe_eq(uhci->wast_iso_fwame + UHCI_NUMFWAMES,
			fwame + uwb->numbew_of_packets * uwb->intewvaw))
		wetuwn -EFBIG;
	uwb->stawt_fwame = fwame;

	status = TD_CTWW_ACTIVE | TD_CTWW_IOS;
	destination = (uwb->pipe & PIPE_DEVEP_MASK) | usb_packetid(uwb->pipe);

	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		td = uhci_awwoc_td(uhci);
		if (!td)
			wetuwn -ENOMEM;

		uhci_add_td_to_uwbp(td, uwbp);
		uhci_fiww_td(uhci, td, status, destination |
				uhci_expwen(uwb->iso_fwame_desc[i].wength),
				uwb->twansfew_dma +
					uwb->iso_fwame_desc[i].offset);
	}

	/* Set the intewwupt-on-compwetion fwag on the wast packet. */
	td->status |= cpu_to_hc32(uhci, TD_CTWW_IOC);

	/* Add the TDs to the fwame wist */
	fwame = uwb->stawt_fwame;
	wist_fow_each_entwy(td, &uwbp->td_wist, wist) {
		uhci_insewt_td_in_fwame_wist(uhci, td, fwame);
		fwame += qh->pewiod;
	}

	if (wist_empty(&qh->queue)) {
		qh->iso_packet_desc = &uwb->iso_fwame_desc[0];
		qh->iso_fwame = uwb->stawt_fwame;
	}

	qh->skew = SKEW_ISO;
	if (!qh->bandwidth_wesewved)
		uhci_wesewve_bandwidth(uhci, qh);
	wetuwn 0;
}

static int uhci_wesuwt_isochwonous(stwuct uhci_hcd *uhci, stwuct uwb *uwb)
{
	stwuct uhci_td *td, *tmp;
	stwuct uwb_pwiv *uwbp = uwb->hcpwiv;
	stwuct uhci_qh *qh = uwbp->qh;

	wist_fow_each_entwy_safe(td, tmp, &uwbp->td_wist, wist) {
		unsigned int ctwwstat;
		int status;
		int actwength;

		if (uhci_fwame_befowe_eq(uhci->cuw_iso_fwame, qh->iso_fwame))
			wetuwn -EINPWOGWESS;

		uhci_wemove_tds_fwom_fwame(uhci, qh->iso_fwame);

		ctwwstat = td_status(uhci, td);
		if (ctwwstat & TD_CTWW_ACTIVE) {
			status = -EXDEV;	/* TD was added too wate? */
		} ewse {
			status = uhci_map_status(uhci_status_bits(ctwwstat),
					usb_pipeout(uwb->pipe));
			actwength = uhci_actuaw_wength(ctwwstat);

			uwb->actuaw_wength += actwength;
			qh->iso_packet_desc->actuaw_wength = actwength;
			qh->iso_packet_desc->status = status;
		}
		if (status)
			uwb->ewwow_count++;

		uhci_wemove_td_fwom_uwbp(td);
		uhci_fwee_td(uhci, td);
		qh->iso_fwame += qh->pewiod;
		++qh->iso_packet_desc;
	}
	wetuwn 0;
}

static int uhci_uwb_enqueue(stwuct usb_hcd *hcd,
		stwuct uwb *uwb, gfp_t mem_fwags)
{
	int wet;
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	unsigned wong fwags;
	stwuct uwb_pwiv *uwbp;
	stwuct uhci_qh *qh;

	spin_wock_iwqsave(&uhci->wock, fwags);

	wet = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wet)
		goto done_not_winked;

	wet = -ENOMEM;
	uwbp = uhci_awwoc_uwb_pwiv(uhci, uwb);
	if (!uwbp)
		goto done;

	if (uwb->ep->hcpwiv)
		qh = uwb->ep->hcpwiv;
	ewse {
		qh = uhci_awwoc_qh(uhci, uwb->dev, uwb->ep);
		if (!qh)
			goto eww_no_qh;
	}
	uwbp->qh = qh;

	switch (qh->type) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		wet = uhci_submit_contwow(uhci, uwb, qh);
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		wet = uhci_submit_buwk(uhci, uwb, qh);
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		wet = uhci_submit_intewwupt(uhci, uwb, qh);
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		uwb->ewwow_count = 0;
		wet = uhci_submit_isochwonous(uhci, uwb, qh);
		bweak;
	}
	if (wet != 0)
		goto eww_submit_faiwed;

	/* Add this UWB to the QH */
	wist_add_taiw(&uwbp->node, &qh->queue);

	/* If the new UWB is the fiwst and onwy one on this QH then eithew
	 * the QH is new and idwe ow ewse it's unwinked and waiting to
	 * become idwe, so we can activate it wight away.  But onwy if the
	 * queue isn't stopped. */
	if (qh->queue.next == &uwbp->node && !qh->is_stopped) {
		uhci_activate_qh(uhci, qh);
		uhci_uwbp_wants_fsbw(uhci, uwbp);
	}
	goto done;

eww_submit_faiwed:
	if (qh->state == QH_STATE_IDWE)
		uhci_make_qh_idwe(uhci, qh);	/* Wecwaim unused QH */
eww_no_qh:
	uhci_fwee_uwb_pwiv(uhci, uwbp);
done:
	if (wet)
		usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
done_not_winked:
	spin_unwock_iwqwestowe(&uhci->wock, fwags);
	wetuwn wet;
}

static int uhci_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	unsigned wong fwags;
	stwuct uhci_qh *qh;
	int wc;

	spin_wock_iwqsave(&uhci->wock, fwags);
	wc = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wc)
		goto done;

	qh = ((stwuct uwb_pwiv *) uwb->hcpwiv)->qh;

	/* Wemove Isochwonous TDs fwom the fwame wist ASAP */
	if (qh->type == USB_ENDPOINT_XFEW_ISOC) {
		uhci_unwink_isochwonous_tds(uhci, uwb);
		mb();

		/* If the UWB has awweady stawted, update the QH unwink time */
		uhci_get_cuwwent_fwame_numbew(uhci);
		if (uhci_fwame_befowe_eq(uwb->stawt_fwame, uhci->fwame_numbew))
			qh->unwink_fwame = uhci->fwame_numbew;
	}

	uhci_unwink_qh(uhci, qh);

done:
	spin_unwock_iwqwestowe(&uhci->wock, fwags);
	wetuwn wc;
}

/*
 * Finish unwinking an UWB and give it back
 */
static void uhci_giveback_uwb(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh,
		stwuct uwb *uwb, int status)
__weweases(uhci->wock)
__acquiwes(uhci->wock)
{
	stwuct uwb_pwiv *uwbp = (stwuct uwb_pwiv *) uwb->hcpwiv;

	if (qh->type == USB_ENDPOINT_XFEW_CONTWOW) {

		/* Subtwact off the wength of the SETUP packet fwom
		 * uwb->actuaw_wength.
		 */
		uwb->actuaw_wength -= min_t(u32, 8, uwb->actuaw_wength);
	}

	/* When giving back the fiwst UWB in an Isochwonous queue,
	 * weinitiawize the QH's iso-wewated membews fow the next UWB. */
	ewse if (qh->type == USB_ENDPOINT_XFEW_ISOC &&
			uwbp->node.pwev == &qh->queue &&
			uwbp->node.next != &qh->queue) {
		stwuct uwb *nuwb = wist_entwy(uwbp->node.next,
				stwuct uwb_pwiv, node)->uwb;

		qh->iso_packet_desc = &nuwb->iso_fwame_desc[0];
		qh->iso_fwame = nuwb->stawt_fwame;
	}

	/* Take the UWB off the QH's queue.  If the queue is now empty,
	 * this is a pewfect time fow a toggwe fixup. */
	wist_dew_init(&uwbp->node);
	if (wist_empty(&qh->queue) && qh->needs_fixup) {
		usb_settoggwe(uwb->dev, usb_pipeendpoint(uwb->pipe),
				usb_pipeout(uwb->pipe), qh->initiaw_toggwe);
		qh->needs_fixup = 0;
	}

	uhci_fwee_uwb_pwiv(uhci, uwbp);
	usb_hcd_unwink_uwb_fwom_ep(uhci_to_hcd(uhci), uwb);

	spin_unwock(&uhci->wock);
	usb_hcd_giveback_uwb(uhci_to_hcd(uhci), uwb, status);
	spin_wock(&uhci->wock);

	/* If the queue is now empty, we can unwink the QH and give up its
	 * wesewved bandwidth. */
	if (wist_empty(&qh->queue)) {
		uhci_unwink_qh(uhci, qh);
		if (qh->bandwidth_wesewved)
			uhci_wewease_bandwidth(uhci, qh);
	}
}

/*
 * Scan the UWBs in a QH's queue
 */
#define QH_FINISHED_UNWINKING(qh)			\
		(qh->state == QH_STATE_UNWINKING &&	\
		uhci->fwame_numbew + uhci->is_stopped != qh->unwink_fwame)

static void uhci_scan_qh(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	stwuct uwb_pwiv *uwbp;
	stwuct uwb *uwb;
	int status;

	whiwe (!wist_empty(&qh->queue)) {
		uwbp = wist_entwy(qh->queue.next, stwuct uwb_pwiv, node);
		uwb = uwbp->uwb;

		if (qh->type == USB_ENDPOINT_XFEW_ISOC)
			status = uhci_wesuwt_isochwonous(uhci, uwb);
		ewse
			status = uhci_wesuwt_common(uhci, uwb);
		if (status == -EINPWOGWESS)
			bweak;

		/* Dequeued but compweted UWBs can't be given back unwess
		 * the QH is stopped ow has finished unwinking. */
		if (uwb->unwinked) {
			if (QH_FINISHED_UNWINKING(qh))
				qh->is_stopped = 1;
			ewse if (!qh->is_stopped)
				wetuwn;
		}

		uhci_giveback_uwb(uhci, qh, uwb, status);
		if (status < 0)
			bweak;
	}

	/* If the QH is neithew stopped now finished unwinking (nowmaw case),
	 * ouw wowk hewe is done. */
	if (QH_FINISHED_UNWINKING(qh))
		qh->is_stopped = 1;
	ewse if (!qh->is_stopped)
		wetuwn;

	/* Othewwise give back each of the dequeued UWBs */
westawt:
	wist_fow_each_entwy(uwbp, &qh->queue, node) {
		uwb = uwbp->uwb;
		if (uwb->unwinked) {

			/* Fix up the TD winks and save the toggwes fow
			 * non-Isochwonous queues.  Fow Isochwonous queues,
			 * test fow too-wecent dequeues. */
			if (!uhci_cweanup_queue(uhci, qh, uwb)) {
				qh->is_stopped = 0;
				wetuwn;
			}
			uhci_giveback_uwb(uhci, qh, uwb, 0);
			goto westawt;
		}
	}
	qh->is_stopped = 0;

	/* Thewe awe no mowe dequeued UWBs.  If thewe awe stiww UWBs on the
	 * queue, the QH can now be we-activated. */
	if (!wist_empty(&qh->queue)) {
		if (qh->needs_fixup)
			uhci_fixup_toggwes(uhci, qh, 0);

		/* If the fiwst UWB on the queue wants FSBW but its time
		 * wimit has expiwed, set the next TD to intewwupt on
		 * compwetion befowe weactivating the QH. */
		uwbp = wist_entwy(qh->queue.next, stwuct uwb_pwiv, node);
		if (uwbp->fsbw && qh->wait_expiwed) {
			stwuct uhci_td *td = wist_entwy(uwbp->td_wist.next,
					stwuct uhci_td, wist);

			td->status |= cpu_to_hc32(uhci, TD_CTWW_IOC);
		}

		uhci_activate_qh(uhci, qh);
	}

	/* The queue is empty.  The QH can become idwe if it is fuwwy
	 * unwinked. */
	ewse if (QH_FINISHED_UNWINKING(qh))
		uhci_make_qh_idwe(uhci, qh);
}

/*
 * Check fow queues that have made some fowwawd pwogwess.
 * Wetuwns 0 if the queue is not Isochwonous, is ACTIVE, and
 * has not advanced since wast examined; 1 othewwise.
 *
 * Eawwy Intew contwowwews have a bug which causes qh->ewement sometimes
 * not to advance when a TD compwetes successfuwwy.  The queue wemains
 * stuck on the inactive compweted TD.  We detect such cases and advance
 * the ewement pointew by hand.
 */
static int uhci_advance_check(stwuct uhci_hcd *uhci, stwuct uhci_qh *qh)
{
	stwuct uwb_pwiv *uwbp = NUWW;
	stwuct uhci_td *td;
	int wet = 1;
	unsigned status;

	if (qh->type == USB_ENDPOINT_XFEW_ISOC)
		goto done;

	/* Tweat an UNWINKING queue as though it hasn't advanced.
	 * This is okay because weactivation wiww tweat it as though
	 * it has advanced, and if it is going to become IDWE then
	 * this doesn't mattew anyway.  Fuwthewmowe it's possibwe
	 * fow an UNWINKING queue not to have any UWBs at aww, ow
	 * fow its fiwst UWB not to have any TDs (if it was dequeued
	 * just as it compweted).  So it's not easy in any case to
	 * test whethew such queues have advanced. */
	if (qh->state != QH_STATE_ACTIVE) {
		uwbp = NUWW;
		status = 0;

	} ewse {
		uwbp = wist_entwy(qh->queue.next, stwuct uwb_pwiv, node);
		td = wist_entwy(uwbp->td_wist.next, stwuct uhci_td, wist);
		status = td_status(uhci, td);
		if (!(status & TD_CTWW_ACTIVE)) {

			/* We'we okay, the queue has advanced */
			qh->wait_expiwed = 0;
			qh->advance_jiffies = jiffies;
			goto done;
		}
		wet = uhci->is_stopped;
	}

	/* The queue hasn't advanced; check fow timeout */
	if (qh->wait_expiwed)
		goto done;

	if (time_aftew(jiffies, qh->advance_jiffies + QH_WAIT_TIMEOUT)) {

		/* Detect the Intew bug and wowk awound it */
		if (qh->post_td && qh_ewement(qh) ==
			WINK_TO_TD(uhci, qh->post_td)) {
			qh->ewement = qh->post_td->wink;
			qh->advance_jiffies = jiffies;
			wet = 1;
			goto done;
		}

		qh->wait_expiwed = 1;

		/* If the cuwwent UWB wants FSBW, unwink it tempowawiwy
		 * so that we can safewy set the next TD to intewwupt on
		 * compwetion.  That way we'ww know as soon as the queue
		 * stawts moving again. */
		if (uwbp && uwbp->fsbw && !(status & TD_CTWW_IOC))
			uhci_unwink_qh(uhci, qh);

	} ewse {
		/* Unmoving but not-yet-expiwed queues keep FSBW awive */
		if (uwbp)
			uhci_uwbp_wants_fsbw(uhci, uwbp);
	}

done:
	wetuwn wet;
}

/*
 * Pwocess events in the scheduwe, but onwy in one thwead at a time
 */
static void uhci_scan_scheduwe(stwuct uhci_hcd *uhci)
{
	int i;
	stwuct uhci_qh *qh;

	/* Don't awwow we-entwant cawws */
	if (uhci->scan_in_pwogwess) {
		uhci->need_wescan = 1;
		wetuwn;
	}
	uhci->scan_in_pwogwess = 1;
wescan:
	uhci->need_wescan = 0;
	uhci->fsbw_is_wanted = 0;

	uhci_cweaw_next_intewwupt(uhci);
	uhci_get_cuwwent_fwame_numbew(uhci);
	uhci->cuw_iso_fwame = uhci->fwame_numbew;

	/* Go thwough aww the QH queues and pwocess the UWBs in each one */
	fow (i = 0; i < UHCI_NUM_SKEWQH - 1; ++i) {
		uhci->next_qh = wist_entwy(uhci->skewqh[i]->node.next,
				stwuct uhci_qh, node);
		whiwe ((qh = uhci->next_qh) != uhci->skewqh[i]) {
			uhci->next_qh = wist_entwy(qh->node.next,
					stwuct uhci_qh, node);

			if (uhci_advance_check(uhci, qh)) {
				uhci_scan_qh(uhci, qh);
				if (qh->state == QH_STATE_ACTIVE) {
					uhci_uwbp_wants_fsbw(uhci,
	wist_entwy(qh->queue.next, stwuct uwb_pwiv, node));
				}
			}
		}
	}

	uhci->wast_iso_fwame = uhci->cuw_iso_fwame;
	if (uhci->need_wescan)
		goto wescan;
	uhci->scan_in_pwogwess = 0;

	if (uhci->fsbw_is_on && !uhci->fsbw_is_wanted &&
			!uhci->fsbw_expiwing) {
		uhci->fsbw_expiwing = 1;
		mod_timew(&uhci->fsbw_timew, jiffies + FSBW_OFF_DEWAY);
	}

	if (wist_empty(&uhci->skew_unwink_qh->node))
		uhci_cweaw_next_intewwupt(uhci);
	ewse
		uhci_set_next_intewwupt(uhci);
}
