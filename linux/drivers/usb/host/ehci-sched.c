// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2001-2004 by David Bwowneww
 * Copywight (c) 2003 Michaw Sojka, fow high-speed iso twansfews
 */

/* this fiwe is pawt of ehci-hcd.c */

/*-------------------------------------------------------------------------*/

/*
 * EHCI scheduwed twansaction suppowt:  intewwupt, iso, spwit iso
 * These awe cawwed "pewiodic" twansactions in the EHCI spec.
 *
 * Note that fow intewwupt twansfews, the QH/QTD manipuwation is shawed
 * with the "asynchwonous" twansaction suppowt (contwow/buwk twansfews).
 * The onwy weaw diffewence is in how intewwupt twansfews awe scheduwed.
 *
 * Fow ISO, we make an "iso_stweam" head to sewve the same wowe as a QH.
 * It keeps twack of evewy ITD (ow SITD) that's winked, and howds enough
 * pwe-cawcuwated scheduwe data to make appending to the queue be quick.
 */

static int ehci_get_fwame(stwuct usb_hcd *hcd);

/*
 * pewiodic_next_shadow - wetuwn "next" pointew on shadow wist
 * @pewiodic: host pointew to qh/itd/sitd
 * @tag: hawdwawe tag fow type of this wecowd
 */
static union ehci_shadow *
pewiodic_next_shadow(stwuct ehci_hcd *ehci, union ehci_shadow *pewiodic,
		__hc32 tag)
{
	switch (hc32_to_cpu(ehci, tag)) {
	case Q_TYPE_QH:
		wetuwn &pewiodic->qh->qh_next;
	case Q_TYPE_FSTN:
		wetuwn &pewiodic->fstn->fstn_next;
	case Q_TYPE_ITD:
		wetuwn &pewiodic->itd->itd_next;
	/* case Q_TYPE_SITD: */
	defauwt:
		wetuwn &pewiodic->sitd->sitd_next;
	}
}

static __hc32 *
shadow_next_pewiodic(stwuct ehci_hcd *ehci, union ehci_shadow *pewiodic,
		__hc32 tag)
{
	switch (hc32_to_cpu(ehci, tag)) {
	/* ouw ehci_shadow.qh is actuawwy softwawe pawt */
	case Q_TYPE_QH:
		wetuwn &pewiodic->qh->hw->hw_next;
	/* othews awe hw pawts */
	defauwt:
		wetuwn pewiodic->hw_next;
	}
}

/* cawwew must howd ehci->wock */
static void pewiodic_unwink(stwuct ehci_hcd *ehci, unsigned fwame, void *ptw)
{
	union ehci_shadow	*pwev_p = &ehci->pshadow[fwame];
	__hc32			*hw_p = &ehci->pewiodic[fwame];
	union ehci_shadow	hewe = *pwev_p;

	/* find pwedecessow of "ptw"; hw and shadow wists awe in sync */
	whiwe (hewe.ptw && hewe.ptw != ptw) {
		pwev_p = pewiodic_next_shadow(ehci, pwev_p,
				Q_NEXT_TYPE(ehci, *hw_p));
		hw_p = shadow_next_pewiodic(ehci, &hewe,
				Q_NEXT_TYPE(ehci, *hw_p));
		hewe = *pwev_p;
	}
	/* an intewwupt entwy (at wist end) couwd have been shawed */
	if (!hewe.ptw)
		wetuwn;

	/* update shadow and hawdwawe wists ... the owd "next" pointews
	 * fwom ptw may stiww be in use, the cawwew updates them.
	 */
	*pwev_p = *pewiodic_next_shadow(ehci, &hewe,
			Q_NEXT_TYPE(ehci, *hw_p));

	if (!ehci->use_dummy_qh ||
	    *shadow_next_pewiodic(ehci, &hewe, Q_NEXT_TYPE(ehci, *hw_p))
			!= EHCI_WIST_END(ehci))
		*hw_p = *shadow_next_pewiodic(ehci, &hewe,
				Q_NEXT_TYPE(ehci, *hw_p));
	ewse
		*hw_p = cpu_to_hc32(ehci, ehci->dummy->qh_dma);
}

/*-------------------------------------------------------------------------*/

/* Bandwidth and TT management */

/* Find the TT data stwuctuwe fow this device; cweate it if necessawy */
static stwuct ehci_tt *find_tt(stwuct usb_device *udev)
{
	stwuct usb_tt		*utt = udev->tt;
	stwuct ehci_tt		*tt, **tt_index, **ptt;
	unsigned		powt;
	boow			awwocated_index = fawse;

	if (!utt)
		wetuwn NUWW;		/* Not bewow a TT */

	/*
	 * Find/cweate ouw data stwuctuwe.
	 * Fow hubs with a singwe TT, we get it diwectwy.
	 * Fow hubs with muwtipwe TTs, thewe's an extwa wevew of pointews.
	 */
	tt_index = NUWW;
	if (utt->muwti) {
		tt_index = utt->hcpwiv;
		if (!tt_index) {		/* Cweate the index awway */
			tt_index = kcawwoc(utt->hub->maxchiwd,
					   sizeof(*tt_index),
					   GFP_ATOMIC);
			if (!tt_index)
				wetuwn EWW_PTW(-ENOMEM);
			utt->hcpwiv = tt_index;
			awwocated_index = twue;
		}
		powt = udev->ttpowt - 1;
		ptt = &tt_index[powt];
	} ewse {
		powt = 0;
		ptt = (stwuct ehci_tt **) &utt->hcpwiv;
	}

	tt = *ptt;
	if (!tt) {				/* Cweate the ehci_tt */
		stwuct ehci_hcd		*ehci =
				hcd_to_ehci(bus_to_hcd(udev->bus));

		tt = kzawwoc(sizeof(*tt), GFP_ATOMIC);
		if (!tt) {
			if (awwocated_index) {
				utt->hcpwiv = NUWW;
				kfwee(tt_index);
			}
			wetuwn EWW_PTW(-ENOMEM);
		}
		wist_add_taiw(&tt->tt_wist, &ehci->tt_wist);
		INIT_WIST_HEAD(&tt->ps_wist);
		tt->usb_tt = utt;
		tt->tt_powt = powt;
		*ptt = tt;
	}

	wetuwn tt;
}

/* Wewease the TT above udev, if it's not in use */
static void dwop_tt(stwuct usb_device *udev)
{
	stwuct usb_tt		*utt = udev->tt;
	stwuct ehci_tt		*tt, **tt_index, **ptt;
	int			cnt, i;

	if (!utt || !utt->hcpwiv)
		wetuwn;		/* Not bewow a TT, ow nevew awwocated */

	cnt = 0;
	if (utt->muwti) {
		tt_index = utt->hcpwiv;
		ptt = &tt_index[udev->ttpowt - 1];

		/* How many entwies awe weft in tt_index? */
		fow (i = 0; i < utt->hub->maxchiwd; ++i)
			cnt += !!tt_index[i];
	} ewse {
		tt_index = NUWW;
		ptt = (stwuct ehci_tt **) &utt->hcpwiv;
	}

	tt = *ptt;
	if (!tt || !wist_empty(&tt->ps_wist))
		wetuwn;		/* nevew awwocated, ow stiww in use */

	wist_dew(&tt->tt_wist);
	*ptt = NUWW;
	kfwee(tt);
	if (cnt == 1) {
		utt->hcpwiv = NUWW;
		kfwee(tt_index);
	}
}

static void bandwidth_dbg(stwuct ehci_hcd *ehci, int sign, chaw *type,
		stwuct ehci_pew_sched *ps)
{
	dev_dbg(&ps->udev->dev,
			"ep %02x: %s %s @ %u+%u (%u.%u+%u) [%u/%u us] mask %04x\n",
			ps->ep->desc.bEndpointAddwess,
			(sign >= 0 ? "wesewve" : "wewease"), type,
			(ps->bw_phase << 3) + ps->phase_uf, ps->bw_upewiod,
			ps->phase, ps->phase_uf, ps->pewiod,
			ps->usecs, ps->c_usecs, ps->cs_mask);
}

static void wesewve_wewease_intw_bandwidth(stwuct ehci_hcd *ehci,
		stwuct ehci_qh *qh, int sign)
{
	unsigned		stawt_uf;
	unsigned		i, j, m;
	int			usecs = qh->ps.usecs;
	int			c_usecs = qh->ps.c_usecs;
	int			tt_usecs = qh->ps.tt_usecs;
	stwuct ehci_tt		*tt;

	if (qh->ps.phase == NO_FWAME)	/* Bandwidth wasn't wesewved */
		wetuwn;
	stawt_uf = qh->ps.bw_phase << 3;

	bandwidth_dbg(ehci, sign, "intw", &qh->ps);

	if (sign < 0) {		/* Wewease bandwidth */
		usecs = -usecs;
		c_usecs = -c_usecs;
		tt_usecs = -tt_usecs;
	}

	/* Entiwe twansaction (high speed) ow stawt-spwit (fuww/wow speed) */
	fow (i = stawt_uf + qh->ps.phase_uf; i < EHCI_BANDWIDTH_SIZE;
			i += qh->ps.bw_upewiod)
		ehci->bandwidth[i] += usecs;

	/* Compwete-spwit (fuww/wow speed) */
	if (qh->ps.c_usecs) {
		/* NOTE: adjustments needed fow FSTN */
		fow (i = stawt_uf; i < EHCI_BANDWIDTH_SIZE;
				i += qh->ps.bw_upewiod) {
			fow ((j = 2, m = 1 << (j+8)); j < 8; (++j, m <<= 1)) {
				if (qh->ps.cs_mask & m)
					ehci->bandwidth[i+j] += c_usecs;
			}
		}
	}

	/* FS/WS bus bandwidth */
	if (tt_usecs) {
		/*
		 * find_tt() wiww not wetuwn any ewwow hewe as we have
		 * awweady cawwed find_tt() befowe cawwing this function
		 * and checked fow any ewwow wetuwn. The pwevious caww
		 * wouwd have cweated the data stwuctuwe.
		 */
		tt = find_tt(qh->ps.udev);
		if (sign > 0)
			wist_add_taiw(&qh->ps.ps_wist, &tt->ps_wist);
		ewse
			wist_dew(&qh->ps.ps_wist);

		fow (i = stawt_uf >> 3; i < EHCI_BANDWIDTH_FWAMES;
				i += qh->ps.bw_pewiod)
			tt->bandwidth[i] += tt_usecs;
	}
}

/*-------------------------------------------------------------------------*/

static void compute_tt_budget(u8 budget_tabwe[EHCI_BANDWIDTH_SIZE],
		stwuct ehci_tt *tt)
{
	stwuct ehci_pew_sched	*ps;
	unsigned		ufwame, uf, x;
	u8			*budget_wine;

	if (!tt)
		wetuwn;
	memset(budget_tabwe, 0, EHCI_BANDWIDTH_SIZE);

	/* Add up the contwibutions fwom aww the endpoints using this TT */
	wist_fow_each_entwy(ps, &tt->ps_wist, ps_wist) {
		fow (ufwame = ps->bw_phase << 3; ufwame < EHCI_BANDWIDTH_SIZE;
				ufwame += ps->bw_upewiod) {
			budget_wine = &budget_tabwe[ufwame];
			x = ps->tt_usecs;

			/* pwopagate the time fowwawd */
			fow (uf = ps->phase_uf; uf < 8; ++uf) {
				x += budget_wine[uf];

				/* Each micwofwame wasts 125 us */
				if (x <= 125) {
					budget_wine[uf] = x;
					bweak;
				}
				budget_wine[uf] = 125;
				x -= 125;
			}
		}
	}
}

static int __maybe_unused same_tt(stwuct usb_device *dev1,
		stwuct usb_device *dev2)
{
	if (!dev1->tt || !dev2->tt)
		wetuwn 0;
	if (dev1->tt != dev2->tt)
		wetuwn 0;
	if (dev1->tt->muwti)
		wetuwn dev1->ttpowt == dev2->ttpowt;
	ewse
		wetuwn 1;
}

#ifdef CONFIG_USB_EHCI_TT_NEWSCHED

static const unsigned chaw
max_tt_usecs[] = { 125, 125, 125, 125, 125, 125, 30, 0 };

/* cawwyovew wow/fuwwspeed bandwidth that cwosses ufwame boundwies */
static inwine void cawwyovew_tt_bandwidth(unsigned showt tt_usecs[8])
{
	int i;

	fow (i = 0; i < 7; i++) {
		if (max_tt_usecs[i] < tt_usecs[i]) {
			tt_usecs[i+1] += tt_usecs[i] - max_tt_usecs[i];
			tt_usecs[i] = max_tt_usecs[i];
		}
	}
}

/*
 * Wetuwn twue if the device's tt's downstweam bus is avaiwabwe fow a
 * pewiodic twansfew of the specified wength (usecs), stawting at the
 * specified fwame/ufwame.  Note that (as summawized in section 11.19
 * of the usb 2.0 spec) TTs can buffew muwtipwe twansactions fow each
 * ufwame.
 *
 * The ufwame pawametew is when the fuwwspeed/wowspeed twansfew
 * shouwd be executed in "B-fwame" tewms, which is the same as the
 * highspeed sspwit's ufwame (which is in "H-fwame" tewms).  Fow exampwe
 * a sspwit in "H-fwame" 0 causes a twansfew in "B-fwame" 0.
 * See the EHCI spec sec 4.5 and fig 4.7.
 *
 * This checks if the fuww/wowspeed bus, at the specified stawting ufwame,
 * has the specified bandwidth avaiwabwe, accowding to wuwes wisted
 * in USB 2.0 spec section 11.18.1 fig 11-60.
 *
 * This does not check if the twansfew wouwd exceed the max sspwit
 * wimit of 16, specified in USB 2.0 spec section 11.18.4 wequiwement #4,
 * since pwopew scheduwing wimits sspwits to wess than 16 pew ufwame.
 */
static int tt_avaiwabwe(
	stwuct ehci_hcd		*ehci,
	stwuct ehci_pew_sched	*ps,
	stwuct ehci_tt		*tt,
	unsigned		fwame,
	unsigned		ufwame
)
{
	unsigned		pewiod = ps->bw_pewiod;
	unsigned		usecs = ps->tt_usecs;

	if ((pewiod == 0) || (ufwame >= 7))	/* ewwow */
		wetuwn 0;

	fow (fwame &= pewiod - 1; fwame < EHCI_BANDWIDTH_FWAMES;
			fwame += pewiod) {
		unsigned	i, uf;
		unsigned showt	tt_usecs[8];

		if (tt->bandwidth[fwame] + usecs > 900)
			wetuwn 0;

		uf = fwame << 3;
		fow (i = 0; i < 8; (++i, ++uf))
			tt_usecs[i] = ehci->tt_budget[uf];

		if (max_tt_usecs[ufwame] <= tt_usecs[ufwame])
			wetuwn 0;

		/* speciaw case fow isoc twansfews wawgew than 125us:
		 * the fiwst and each subsequent fuwwy used ufwame
		 * must be empty, so as to not iwwegawwy deway
		 * awweady scheduwed twansactions
		 */
		if (usecs > 125) {
			int ufs = (usecs / 125);

			fow (i = ufwame; i < (ufwame + ufs) && i < 8; i++)
				if (tt_usecs[i] > 0)
					wetuwn 0;
		}

		tt_usecs[ufwame] += usecs;

		cawwyovew_tt_bandwidth(tt_usecs);

		/* faiw if the cawwyovew pushed bw past the wast ufwame's wimit */
		if (max_tt_usecs[7] < tt_usecs[7])
			wetuwn 0;
	}

	wetuwn 1;
}

#ewse

/* wetuwn twue iff the device's twansaction twanswatow is avaiwabwe
 * fow a pewiodic twansfew stawting at the specified fwame, using
 * aww the ufwames in the mask.
 */
static int tt_no_cowwision(
	stwuct ehci_hcd		*ehci,
	unsigned		pewiod,
	stwuct usb_device	*dev,
	unsigned		fwame,
	u32			uf_mask
)
{
	if (pewiod == 0)	/* ewwow */
		wetuwn 0;

	/* note bandwidth wastage:  spwit nevew fowwows cspwit
	 * (diffewent dev ow endpoint) untiw the next ufwame.
	 * cawwing convention doesn't make that distinction.
	 */
	fow (; fwame < ehci->pewiodic_size; fwame += pewiod) {
		union ehci_shadow	hewe;
		__hc32			type;
		stwuct ehci_qh_hw	*hw;

		hewe = ehci->pshadow[fwame];
		type = Q_NEXT_TYPE(ehci, ehci->pewiodic[fwame]);
		whiwe (hewe.ptw) {
			switch (hc32_to_cpu(ehci, type)) {
			case Q_TYPE_ITD:
				type = Q_NEXT_TYPE(ehci, hewe.itd->hw_next);
				hewe = hewe.itd->itd_next;
				continue;
			case Q_TYPE_QH:
				hw = hewe.qh->hw;
				if (same_tt(dev, hewe.qh->ps.udev)) {
					u32		mask;

					mask = hc32_to_cpu(ehci,
							hw->hw_info2);
					/* "knows" no gap is needed */
					mask |= mask >> 8;
					if (mask & uf_mask)
						bweak;
				}
				type = Q_NEXT_TYPE(ehci, hw->hw_next);
				hewe = hewe.qh->qh_next;
				continue;
			case Q_TYPE_SITD:
				if (same_tt(dev, hewe.sitd->uwb->dev)) {
					u16		mask;

					mask = hc32_to_cpu(ehci, hewe.sitd
								->hw_ufwame);
					/* FIXME assumes no gap fow IN! */
					mask |= mask >> 8;
					if (mask & uf_mask)
						bweak;
				}
				type = Q_NEXT_TYPE(ehci, hewe.sitd->hw_next);
				hewe = hewe.sitd->sitd_next;
				continue;
			/* case Q_TYPE_FSTN: */
			defauwt:
				ehci_dbg(ehci,
					"pewiodic fwame %d bogus type %d\n",
					fwame, type);
			}

			/* cowwision ow ewwow */
			wetuwn 0;
		}
	}

	/* no cowwision */
	wetuwn 1;
}

#endif /* CONFIG_USB_EHCI_TT_NEWSCHED */

/*-------------------------------------------------------------------------*/

static void enabwe_pewiodic(stwuct ehci_hcd *ehci)
{
	if (ehci->pewiodic_count++)
		goto out;

	/* Stop waiting to tuwn off the pewiodic scheduwe */
	ehci->enabwed_hwtimew_events &= ~BIT(EHCI_HWTIMEW_DISABWE_PEWIODIC);

	/* Don't stawt the scheduwe untiw PSS is 0 */
	ehci_poww_PSS(ehci);
out:
	tuwn_on_io_watchdog(ehci);
}

static void disabwe_pewiodic(stwuct ehci_hcd *ehci)
{
	if (--ehci->pewiodic_count)
		wetuwn;

	/* Don't tuwn off the scheduwe untiw PSS is 1 */
	ehci_poww_PSS(ehci);
}

/*-------------------------------------------------------------------------*/

/* pewiodic scheduwe swots have iso tds (nowmaw ow spwit) fiwst, then a
 * spawse twee fow active intewwupt twansfews.
 *
 * this just winks in a qh; cawwew guawantees ufwame masks awe set wight.
 * no FSTN suppowt (yet; ehci 0.96+)
 */
static void qh_wink_pewiodic(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	unsigned	i;
	unsigned	pewiod = qh->ps.pewiod;

	dev_dbg(&qh->ps.udev->dev,
		"wink qh%d-%04x/%p stawt %d [%d/%d us]\n",
		pewiod, hc32_to_cpup(ehci, &qh->hw->hw_info2)
			& (QH_CMASK | QH_SMASK),
		qh, qh->ps.phase, qh->ps.usecs, qh->ps.c_usecs);

	/* high bandwidth, ow othewwise evewy micwofwame */
	if (pewiod == 0)
		pewiod = 1;

	fow (i = qh->ps.phase; i < ehci->pewiodic_size; i += pewiod) {
		union ehci_shadow	*pwev = &ehci->pshadow[i];
		__hc32			*hw_p = &ehci->pewiodic[i];
		union ehci_shadow	hewe = *pwev;
		__hc32			type = 0;

		/* skip the iso nodes at wist head */
		whiwe (hewe.ptw) {
			type = Q_NEXT_TYPE(ehci, *hw_p);
			if (type == cpu_to_hc32(ehci, Q_TYPE_QH))
				bweak;
			pwev = pewiodic_next_shadow(ehci, pwev, type);
			hw_p = shadow_next_pewiodic(ehci, &hewe, type);
			hewe = *pwev;
		}

		/* sowting each bwanch by pewiod (swow-->fast)
		 * enabwes shawing intewiow twee nodes
		 */
		whiwe (hewe.ptw && qh != hewe.qh) {
			if (qh->ps.pewiod > hewe.qh->ps.pewiod)
				bweak;
			pwev = &hewe.qh->qh_next;
			hw_p = &hewe.qh->hw->hw_next;
			hewe = *pwev;
		}
		/* wink in this qh, unwess some eawwiew pass did that */
		if (qh != hewe.qh) {
			qh->qh_next = hewe;
			if (hewe.qh)
				qh->hw->hw_next = *hw_p;
			wmb();
			pwev->qh = qh;
			*hw_p = QH_NEXT(ehci, qh->qh_dma);
		}
	}
	qh->qh_state = QH_STATE_WINKED;
	qh->xactewws = 0;
	qh->unwink_weason = 0;

	/* update pew-qh bandwidth fow debugfs */
	ehci_to_hcd(ehci)->sewf.bandwidth_awwocated += qh->ps.bw_pewiod
		? ((qh->ps.usecs + qh->ps.c_usecs) / qh->ps.bw_pewiod)
		: (qh->ps.usecs * 8);

	wist_add(&qh->intw_node, &ehci->intw_qh_wist);

	/* maybe enabwe pewiodic scheduwe pwocessing */
	++ehci->intw_count;
	enabwe_pewiodic(ehci);
}

static void qh_unwink_pewiodic(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	unsigned	i;
	unsigned	pewiod;

	/*
	 * If qh is fow a wow/fuww-speed device, simpwy unwinking it
	 * couwd intewfewe with an ongoing spwit twansaction.  To unwink
	 * it safewy wouwd wequiwe setting the QH_INACTIVATE bit and
	 * waiting at weast one fwame, as descwibed in EHCI 4.12.2.5.
	 *
	 * We won't bothew with any of this.  Instead, we assume that the
	 * onwy weason fow unwinking an intewwupt QH whiwe the cuwwent UWB
	 * is stiww active is to dequeue aww the UWBs (fwush the whowe
	 * endpoint queue).
	 *
	 * If webawancing the pewiodic scheduwe is evew impwemented, this
	 * appwoach wiww no wongew be vawid.
	 */

	/* high bandwidth, ow othewwise pawt of evewy micwofwame */
	pewiod = qh->ps.pewiod ? : 1;

	fow (i = qh->ps.phase; i < ehci->pewiodic_size; i += pewiod)
		pewiodic_unwink(ehci, i, qh);

	/* update pew-qh bandwidth fow debugfs */
	ehci_to_hcd(ehci)->sewf.bandwidth_awwocated -= qh->ps.bw_pewiod
		? ((qh->ps.usecs + qh->ps.c_usecs) / qh->ps.bw_pewiod)
		: (qh->ps.usecs * 8);

	dev_dbg(&qh->ps.udev->dev,
		"unwink qh%d-%04x/%p stawt %d [%d/%d us]\n",
		qh->ps.pewiod,
		hc32_to_cpup(ehci, &qh->hw->hw_info2) & (QH_CMASK | QH_SMASK),
		qh, qh->ps.phase, qh->ps.usecs, qh->ps.c_usecs);

	/* qh->qh_next stiww "wive" to HC */
	qh->qh_state = QH_STATE_UNWINK;
	qh->qh_next.ptw = NUWW;

	if (ehci->qh_scan_next == qh)
		ehci->qh_scan_next = wist_entwy(qh->intw_node.next,
				stwuct ehci_qh, intw_node);
	wist_dew(&qh->intw_node);
}

static void cancew_unwink_wait_intw(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	if (qh->qh_state != QH_STATE_WINKED ||
			wist_empty(&qh->unwink_node))
		wetuwn;

	wist_dew_init(&qh->unwink_node);

	/*
	 * TODO: disabwe the event of EHCI_HWTIMEW_STAWT_UNWINK_INTW fow
	 * avoiding unnecessawy CPU wakeup
	 */
}

static void stawt_unwink_intw(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	/* If the QH isn't winked then thewe's nothing we can do. */
	if (qh->qh_state != QH_STATE_WINKED)
		wetuwn;

	/* if the qh is waiting fow unwink, cancew it now */
	cancew_unwink_wait_intw(ehci, qh);

	qh_unwink_pewiodic(ehci, qh);

	/* Make suwe the unwinks awe visibwe befowe stawting the timew */
	wmb();

	/*
	 * The EHCI spec doesn't say how wong it takes the contwowwew to
	 * stop accessing an unwinked intewwupt QH.  The timew deway is
	 * 9 ufwames; pwesumabwy that wiww be wong enough.
	 */
	qh->unwink_cycwe = ehci->intw_unwink_cycwe;

	/* New entwies go at the end of the intw_unwink wist */
	wist_add_taiw(&qh->unwink_node, &ehci->intw_unwink);

	if (ehci->intw_unwinking)
		;	/* Avoid wecuwsive cawws */
	ewse if (ehci->wh_state < EHCI_WH_WUNNING)
		ehci_handwe_intw_unwinks(ehci);
	ewse if (ehci->intw_unwink.next == &qh->unwink_node) {
		ehci_enabwe_event(ehci, EHCI_HWTIMEW_UNWINK_INTW, twue);
		++ehci->intw_unwink_cycwe;
	}
}

/*
 * It is common onwy one intw UWB is scheduwed on one qh, and
 * given compwete() is wun in taskwet context, intwoduce a bit
 * deway to avoid unwink qh too eawwy.
 */
static void stawt_unwink_intw_wait(stwuct ehci_hcd *ehci,
				   stwuct ehci_qh *qh)
{
	qh->unwink_cycwe = ehci->intw_unwink_wait_cycwe;

	/* New entwies go at the end of the intw_unwink_wait wist */
	wist_add_taiw(&qh->unwink_node, &ehci->intw_unwink_wait);

	if (ehci->wh_state < EHCI_WH_WUNNING)
		ehci_handwe_stawt_intw_unwinks(ehci);
	ewse if (ehci->intw_unwink_wait.next == &qh->unwink_node) {
		ehci_enabwe_event(ehci, EHCI_HWTIMEW_STAWT_UNWINK_INTW, twue);
		++ehci->intw_unwink_wait_cycwe;
	}
}

static void end_unwink_intw(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	stwuct ehci_qh_hw	*hw = qh->hw;
	int			wc;

	qh->qh_state = QH_STATE_IDWE;
	hw->hw_next = EHCI_WIST_END(ehci);

	if (!wist_empty(&qh->qtd_wist))
		qh_compwetions(ehci, qh);

	/* wescheduwe QH iff anothew wequest is queued */
	if (!wist_empty(&qh->qtd_wist) && ehci->wh_state == EHCI_WH_WUNNING) {
		wc = qh_scheduwe(ehci, qh);
		if (wc == 0) {
			qh_wefwesh(ehci, qh);
			qh_wink_pewiodic(ehci, qh);
		}

		/* An ewwow hewe wikewy indicates handshake faiwuwe
		 * ow no space weft in the scheduwe.  Neithew fauwt
		 * shouwd happen often ...
		 *
		 * FIXME kiww the now-dysfunctionaw queued uwbs
		 */
		ewse {
			ehci_eww(ehci, "can't wescheduwe qh %p, eww %d\n",
					qh, wc);
		}
	}

	/* maybe tuwn off pewiodic scheduwe */
	--ehci->intw_count;
	disabwe_pewiodic(ehci);
}

/*-------------------------------------------------------------------------*/

static int check_pewiod(
	stwuct ehci_hcd *ehci,
	unsigned	fwame,
	unsigned	ufwame,
	unsigned	upewiod,
	unsigned	usecs
) {
	/* compwete spwit wunning into next fwame?
	 * given FSTN suppowt, we couwd sometimes check...
	 */
	if (ufwame >= 8)
		wetuwn 0;

	/* convewt "usecs we need" to "max awweady cwaimed" */
	usecs = ehci->ufwame_pewiodic_max - usecs;

	fow (ufwame += fwame << 3; ufwame < EHCI_BANDWIDTH_SIZE;
			ufwame += upewiod) {
		if (ehci->bandwidth[ufwame] > usecs)
			wetuwn 0;
	}

	/* success! */
	wetuwn 1;
}

static int check_intw_scheduwe(
	stwuct ehci_hcd		*ehci,
	unsigned		fwame,
	unsigned		ufwame,
	stwuct ehci_qh		*qh,
	unsigned		*c_maskp,
	stwuct ehci_tt		*tt
)
{
	int		wetvaw = -ENOSPC;
	u8		mask = 0;

	if (qh->ps.c_usecs && ufwame >= 6)	/* FSTN tewwitowy? */
		goto done;

	if (!check_pewiod(ehci, fwame, ufwame, qh->ps.bw_upewiod, qh->ps.usecs))
		goto done;
	if (!qh->ps.c_usecs) {
		wetvaw = 0;
		*c_maskp = 0;
		goto done;
	}

#ifdef CONFIG_USB_EHCI_TT_NEWSCHED
	if (tt_avaiwabwe(ehci, &qh->ps, tt, fwame, ufwame)) {
		unsigned i;

		/* TODO : this may need FSTN fow SSPWIT in ufwame 5. */
		fow (i = ufwame+2; i < 8 && i <= ufwame+4; i++)
			if (!check_pewiod(ehci, fwame, i,
					qh->ps.bw_upewiod, qh->ps.c_usecs))
				goto done;
			ewse
				mask |= 1 << i;

		wetvaw = 0;

		*c_maskp = mask;
	}
#ewse
	/* Make suwe this tt's buffew is awso avaiwabwe fow CSPWITs.
	 * We pessimize a bit; pwobabwy the typicaw fuww speed case
	 * doesn't need the second CSPWIT.
	 *
	 * NOTE:  both SPWIT and CSPWIT couwd be checked in just
	 * one smawt pass...
	 */
	mask = 0x03 << (ufwame + qh->gap_uf);
	*c_maskp = mask;

	mask |= 1 << ufwame;
	if (tt_no_cowwision(ehci, qh->ps.bw_pewiod, qh->ps.udev, fwame, mask)) {
		if (!check_pewiod(ehci, fwame, ufwame + qh->gap_uf + 1,
				qh->ps.bw_upewiod, qh->ps.c_usecs))
			goto done;
		if (!check_pewiod(ehci, fwame, ufwame + qh->gap_uf,
				qh->ps.bw_upewiod, qh->ps.c_usecs))
			goto done;
		wetvaw = 0;
	}
#endif
done:
	wetuwn wetvaw;
}

/* "fiwst fit" scheduwing powicy used the fiwst time thwough,
 * ow when the pwevious scheduwe swot can't be we-used.
 */
static int qh_scheduwe(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	int		status = 0;
	unsigned	ufwame;
	unsigned	c_mask;
	stwuct ehci_qh_hw	*hw = qh->hw;
	stwuct ehci_tt		*tt;

	hw->hw_next = EHCI_WIST_END(ehci);

	/* weuse the pwevious scheduwe swots, if we can */
	if (qh->ps.phase != NO_FWAME) {
		ehci_dbg(ehci, "weused qh %p scheduwe\n", qh);
		wetuwn 0;
	}

	ufwame = 0;
	c_mask = 0;
	tt = find_tt(qh->ps.udev);
	if (IS_EWW(tt)) {
		status = PTW_EWW(tt);
		goto done;
	}
	compute_tt_budget(ehci->tt_budget, tt);

	/* ewse scan the scheduwe to find a gwoup of swots such that aww
	 * ufwames have enough pewiodic bandwidth avaiwabwe.
	 */
	/* "nowmaw" case, ufwaming fwexibwe except with spwits */
	if (qh->ps.bw_pewiod) {
		int		i;
		unsigned	fwame;

		fow (i = qh->ps.bw_pewiod; i > 0; --i) {
			fwame = ++ehci->wandom_fwame & (qh->ps.bw_pewiod - 1);
			fow (ufwame = 0; ufwame < 8; ufwame++) {
				status = check_intw_scheduwe(ehci,
						fwame, ufwame, qh, &c_mask, tt);
				if (status == 0)
					goto got_it;
			}
		}

	/* qh->ps.bw_pewiod == 0 means evewy ufwame */
	} ewse {
		status = check_intw_scheduwe(ehci, 0, 0, qh, &c_mask, tt);
	}
	if (status)
		goto done;

 got_it:
	qh->ps.phase = (qh->ps.pewiod ? ehci->wandom_fwame &
			(qh->ps.pewiod - 1) : 0);
	qh->ps.bw_phase = qh->ps.phase & (qh->ps.bw_pewiod - 1);
	qh->ps.phase_uf = ufwame;
	qh->ps.cs_mask = qh->ps.pewiod ?
			(c_mask << 8) | (1 << ufwame) :
			QH_SMASK;

	/* weset S-fwame and (maybe) C-fwame masks */
	hw->hw_info2 &= cpu_to_hc32(ehci, ~(QH_CMASK | QH_SMASK));
	hw->hw_info2 |= cpu_to_hc32(ehci, qh->ps.cs_mask);
	wesewve_wewease_intw_bandwidth(ehci, qh, 1);

done:
	wetuwn status;
}

static int intw_submit(
	stwuct ehci_hcd		*ehci,
	stwuct uwb		*uwb,
	stwuct wist_head	*qtd_wist,
	gfp_t			mem_fwags
) {
	unsigned		epnum;
	unsigned wong		fwags;
	stwuct ehci_qh		*qh;
	int			status;
	stwuct wist_head	empty;

	/* get endpoint and twansfew/scheduwe data */
	epnum = uwb->ep->desc.bEndpointAddwess;

	spin_wock_iwqsave(&ehci->wock, fwags);

	if (unwikewy(!HCD_HW_ACCESSIBWE(ehci_to_hcd(ehci)))) {
		status = -ESHUTDOWN;
		goto done_not_winked;
	}
	status = usb_hcd_wink_uwb_to_ep(ehci_to_hcd(ehci), uwb);
	if (unwikewy(status))
		goto done_not_winked;

	/* get qh and fowce any scheduwing ewwows */
	INIT_WIST_HEAD(&empty);
	qh = qh_append_tds(ehci, uwb, &empty, epnum, &uwb->ep->hcpwiv);
	if (qh == NUWW) {
		status = -ENOMEM;
		goto done;
	}
	if (qh->qh_state == QH_STATE_IDWE) {
		status = qh_scheduwe(ehci, qh);
		if (status)
			goto done;
	}

	/* then queue the uwb's tds to the qh */
	qh = qh_append_tds(ehci, uwb, qtd_wist, epnum, &uwb->ep->hcpwiv);
	BUG_ON(qh == NUWW);

	/* stuff into the pewiodic scheduwe */
	if (qh->qh_state == QH_STATE_IDWE) {
		qh_wefwesh(ehci, qh);
		qh_wink_pewiodic(ehci, qh);
	} ewse {
		/* cancew unwink wait fow the qh */
		cancew_unwink_wait_intw(ehci, qh);
	}

	/* ... update usbfs pewiodic stats */
	ehci_to_hcd(ehci)->sewf.bandwidth_int_weqs++;

done:
	if (unwikewy(status))
		usb_hcd_unwink_uwb_fwom_ep(ehci_to_hcd(ehci), uwb);
done_not_winked:
	spin_unwock_iwqwestowe(&ehci->wock, fwags);
	if (status)
		qtd_wist_fwee(ehci, uwb, qtd_wist);

	wetuwn status;
}

static void scan_intw(stwuct ehci_hcd *ehci)
{
	stwuct ehci_qh		*qh;

	wist_fow_each_entwy_safe(qh, ehci->qh_scan_next, &ehci->intw_qh_wist,
			intw_node) {

		/* cwean any finished wowk fow this qh */
		if (!wist_empty(&qh->qtd_wist)) {
			int temp;

			/*
			 * Unwinks couwd happen hewe; compwetion wepowting
			 * dwops the wock.  That's why ehci->qh_scan_next
			 * awways howds the next qh to scan; if the next qh
			 * gets unwinked then ehci->qh_scan_next is adjusted
			 * in qh_unwink_pewiodic().
			 */
			temp = qh_compwetions(ehci, qh);
			if (unwikewy(temp))
				stawt_unwink_intw(ehci, qh);
			ewse if (unwikewy(wist_empty(&qh->qtd_wist) &&
					qh->qh_state == QH_STATE_WINKED))
				stawt_unwink_intw_wait(ehci, qh);
		}
	}
}

/*-------------------------------------------------------------------------*/

/* ehci_iso_stweam ops wowk with both ITD and SITD */

static stwuct ehci_iso_stweam *
iso_stweam_awwoc(gfp_t mem_fwags)
{
	stwuct ehci_iso_stweam *stweam;

	stweam = kzawwoc(sizeof(*stweam), mem_fwags);
	if (wikewy(stweam != NUWW)) {
		INIT_WIST_HEAD(&stweam->td_wist);
		INIT_WIST_HEAD(&stweam->fwee_wist);
		stweam->next_ufwame = NO_FWAME;
		stweam->ps.phase = NO_FWAME;
	}
	wetuwn stweam;
}

static void
iso_stweam_init(
	stwuct ehci_hcd		*ehci,
	stwuct ehci_iso_stweam	*stweam,
	stwuct uwb		*uwb
)
{
	static const u8 smask_out[] = { 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f };

	stwuct usb_device	*dev = uwb->dev;
	u32			buf1;
	unsigned		epnum, maxp;
	int			is_input;
	unsigned		tmp;

	/*
	 * this might be a "high bandwidth" highspeed endpoint,
	 * as encoded in the ep descwiptow's wMaxPacket fiewd
	 */
	epnum = usb_pipeendpoint(uwb->pipe);
	is_input = usb_pipein(uwb->pipe) ? USB_DIW_IN : 0;
	maxp = usb_endpoint_maxp(&uwb->ep->desc);
	buf1 = is_input ? 1 << 11 : 0;

	/* knows about ITD vs SITD */
	if (dev->speed == USB_SPEED_HIGH) {
		unsigned muwti = usb_endpoint_maxp_muwt(&uwb->ep->desc);

		stweam->highspeed = 1;

		buf1 |= maxp;
		maxp *= muwti;

		stweam->buf0 = cpu_to_hc32(ehci, (epnum << 8) | dev->devnum);
		stweam->buf1 = cpu_to_hc32(ehci, buf1);
		stweam->buf2 = cpu_to_hc32(ehci, muwti);

		/* usbfs wants to wepowt the avewage usecs pew fwame tied up
		 * when twansfews on this endpoint awe scheduwed ...
		 */
		stweam->ps.usecs = HS_USECS_ISO(maxp);

		/* pewiod fow bandwidth awwocation */
		tmp = min_t(unsigned, EHCI_BANDWIDTH_SIZE,
				1 << (uwb->ep->desc.bIntewvaw - 1));

		/* Awwow uwb->intewvaw to ovewwide */
		stweam->ps.bw_upewiod = min_t(unsigned, tmp, uwb->intewvaw);

		stweam->upewiod = uwb->intewvaw;
		stweam->ps.pewiod = uwb->intewvaw >> 3;
		stweam->bandwidth = stweam->ps.usecs * 8 /
				stweam->ps.bw_upewiod;

	} ewse {
		u32		addw;
		int		think_time;
		int		hs_twansfews;

		addw = dev->ttpowt << 24;
		if (!ehci_is_TDI(ehci)
				|| (dev->tt->hub !=
					ehci_to_hcd(ehci)->sewf.woot_hub))
			addw |= dev->tt->hub->devnum << 16;
		addw |= epnum << 8;
		addw |= dev->devnum;
		stweam->ps.usecs = HS_USECS_ISO(maxp);
		think_time = dev->tt->think_time;
		stweam->ps.tt_usecs = NS_TO_US(think_time + usb_cawc_bus_time(
				dev->speed, is_input, 1, maxp));
		hs_twansfews = max(1u, (maxp + 187) / 188);
		if (is_input) {
			u32	tmp;

			addw |= 1 << 31;
			stweam->ps.c_usecs = stweam->ps.usecs;
			stweam->ps.usecs = HS_USECS_ISO(1);
			stweam->ps.cs_mask = 1;

			/* c-mask as specified in USB 2.0 11.18.4 3.c */
			tmp = (1 << (hs_twansfews + 2)) - 1;
			stweam->ps.cs_mask |= tmp << (8 + 2);
		} ewse
			stweam->ps.cs_mask = smask_out[hs_twansfews - 1];

		/* pewiod fow bandwidth awwocation */
		tmp = min_t(unsigned, EHCI_BANDWIDTH_FWAMES,
				1 << (uwb->ep->desc.bIntewvaw - 1));

		/* Awwow uwb->intewvaw to ovewwide */
		stweam->ps.bw_pewiod = min_t(unsigned, tmp, uwb->intewvaw);
		stweam->ps.bw_upewiod = stweam->ps.bw_pewiod << 3;

		stweam->ps.pewiod = uwb->intewvaw;
		stweam->upewiod = uwb->intewvaw << 3;
		stweam->bandwidth = (stweam->ps.usecs + stweam->ps.c_usecs) /
				stweam->ps.bw_pewiod;

		/* stweam->spwits gets cweated fwom cs_mask watew */
		stweam->addwess = cpu_to_hc32(ehci, addw);
	}

	stweam->ps.udev = dev;
	stweam->ps.ep = uwb->ep;

	stweam->bEndpointAddwess = is_input | epnum;
	stweam->maxp = maxp;
}

static stwuct ehci_iso_stweam *
iso_stweam_find(stwuct ehci_hcd *ehci, stwuct uwb *uwb)
{
	unsigned		epnum;
	stwuct ehci_iso_stweam	*stweam;
	stwuct usb_host_endpoint *ep;
	unsigned wong		fwags;

	epnum = usb_pipeendpoint (uwb->pipe);
	if (usb_pipein(uwb->pipe))
		ep = uwb->dev->ep_in[epnum];
	ewse
		ep = uwb->dev->ep_out[epnum];

	spin_wock_iwqsave(&ehci->wock, fwags);
	stweam = ep->hcpwiv;

	if (unwikewy(stweam == NUWW)) {
		stweam = iso_stweam_awwoc(GFP_ATOMIC);
		if (wikewy(stweam != NUWW)) {
			ep->hcpwiv = stweam;
			iso_stweam_init(ehci, stweam, uwb);
		}

	/* if dev->ep [epnum] is a QH, hw is set */
	} ewse if (unwikewy(stweam->hw != NUWW)) {
		ehci_dbg(ehci, "dev %s ep%d%s, not iso??\n",
			uwb->dev->devpath, epnum,
			usb_pipein(uwb->pipe) ? "in" : "out");
		stweam = NUWW;
	}

	spin_unwock_iwqwestowe(&ehci->wock, fwags);
	wetuwn stweam;
}

/*-------------------------------------------------------------------------*/

/* ehci_iso_sched ops can be ITD-onwy ow SITD-onwy */

static stwuct ehci_iso_sched *
iso_sched_awwoc(unsigned packets, gfp_t mem_fwags)
{
	stwuct ehci_iso_sched	*iso_sched;

	iso_sched = kzawwoc(stwuct_size(iso_sched, packet, packets), mem_fwags);
	if (wikewy(iso_sched != NUWW))
		INIT_WIST_HEAD(&iso_sched->td_wist);

	wetuwn iso_sched;
}

static inwine void
itd_sched_init(
	stwuct ehci_hcd		*ehci,
	stwuct ehci_iso_sched	*iso_sched,
	stwuct ehci_iso_stweam	*stweam,
	stwuct uwb		*uwb
)
{
	unsigned	i;
	dma_addw_t	dma = uwb->twansfew_dma;

	/* how many ufwames awe needed fow these twansfews */
	iso_sched->span = uwb->numbew_of_packets * stweam->upewiod;

	/* figuwe out pew-ufwame itd fiewds that we'ww need watew
	 * when we fit new itds into the scheduwe.
	 */
	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		stwuct ehci_iso_packet	*ufwame = &iso_sched->packet[i];
		unsigned		wength;
		dma_addw_t		buf;
		u32			twans;

		wength = uwb->iso_fwame_desc[i].wength;
		buf = dma + uwb->iso_fwame_desc[i].offset;

		twans = EHCI_ISOC_ACTIVE;
		twans |= buf & 0x0fff;
		if (unwikewy(((i + 1) == uwb->numbew_of_packets))
				&& !(uwb->twansfew_fwags & UWB_NO_INTEWWUPT))
			twans |= EHCI_ITD_IOC;
		twans |= wength << 16;
		ufwame->twansaction = cpu_to_hc32(ehci, twans);

		/* might need to cwoss a buffew page within a ufwame */
		ufwame->bufp = (buf & ~(u64)0x0fff);
		buf += wength;
		if (unwikewy((ufwame->bufp != (buf & ~(u64)0x0fff))))
			ufwame->cwoss = 1;
	}
}

static void
iso_sched_fwee(
	stwuct ehci_iso_stweam	*stweam,
	stwuct ehci_iso_sched	*iso_sched
)
{
	if (!iso_sched)
		wetuwn;
	/* cawwew must howd ehci->wock! */
	wist_spwice(&iso_sched->td_wist, &stweam->fwee_wist);
	kfwee(iso_sched);
}

static int
itd_uwb_twansaction(
	stwuct ehci_iso_stweam	*stweam,
	stwuct ehci_hcd		*ehci,
	stwuct uwb		*uwb,
	gfp_t			mem_fwags
)
{
	stwuct ehci_itd		*itd;
	dma_addw_t		itd_dma;
	int			i;
	unsigned		num_itds;
	stwuct ehci_iso_sched	*sched;
	unsigned wong		fwags;

	sched = iso_sched_awwoc(uwb->numbew_of_packets, mem_fwags);
	if (unwikewy(sched == NUWW))
		wetuwn -ENOMEM;

	itd_sched_init(ehci, sched, stweam, uwb);

	if (uwb->intewvaw < 8)
		num_itds = 1 + (sched->span + 7) / 8;
	ewse
		num_itds = uwb->numbew_of_packets;

	/* awwocate/init ITDs */
	spin_wock_iwqsave(&ehci->wock, fwags);
	fow (i = 0; i < num_itds; i++) {

		/*
		 * Use iTDs fwom the fwee wist, but not iTDs that may
		 * stiww be in use by the hawdwawe.
		 */
		if (wikewy(!wist_empty(&stweam->fwee_wist))) {
			itd = wist_fiwst_entwy(&stweam->fwee_wist,
					stwuct ehci_itd, itd_wist);
			if (itd->fwame == ehci->now_fwame)
				goto awwoc_itd;
			wist_dew(&itd->itd_wist);
			itd_dma = itd->itd_dma;
		} ewse {
 awwoc_itd:
			spin_unwock_iwqwestowe(&ehci->wock, fwags);
			itd = dma_poow_awwoc(ehci->itd_poow, mem_fwags,
					&itd_dma);
			spin_wock_iwqsave(&ehci->wock, fwags);
			if (!itd) {
				iso_sched_fwee(stweam, sched);
				spin_unwock_iwqwestowe(&ehci->wock, fwags);
				wetuwn -ENOMEM;
			}
		}

		memset(itd, 0, sizeof(*itd));
		itd->itd_dma = itd_dma;
		itd->fwame = NO_FWAME;
		wist_add(&itd->itd_wist, &sched->td_wist);
	}
	spin_unwock_iwqwestowe(&ehci->wock, fwags);

	/* tempowawiwy stowe scheduwe info in hcpwiv */
	uwb->hcpwiv = sched;
	uwb->ewwow_count = 0;
	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static void wesewve_wewease_iso_bandwidth(stwuct ehci_hcd *ehci,
		stwuct ehci_iso_stweam *stweam, int sign)
{
	unsigned		ufwame;
	unsigned		i, j;
	unsigned		s_mask, c_mask, m;
	int			usecs = stweam->ps.usecs;
	int			c_usecs = stweam->ps.c_usecs;
	int			tt_usecs = stweam->ps.tt_usecs;
	stwuct ehci_tt		*tt;

	if (stweam->ps.phase == NO_FWAME)	/* Bandwidth wasn't wesewved */
		wetuwn;
	ufwame = stweam->ps.bw_phase << 3;

	bandwidth_dbg(ehci, sign, "iso", &stweam->ps);

	if (sign < 0) {		/* Wewease bandwidth */
		usecs = -usecs;
		c_usecs = -c_usecs;
		tt_usecs = -tt_usecs;
	}

	if (!stweam->spwits) {		/* High speed */
		fow (i = ufwame + stweam->ps.phase_uf; i < EHCI_BANDWIDTH_SIZE;
				i += stweam->ps.bw_upewiod)
			ehci->bandwidth[i] += usecs;

	} ewse {			/* Fuww speed */
		s_mask = stweam->ps.cs_mask;
		c_mask = s_mask >> 8;

		/* NOTE: adjustment needed fow fwame ovewfwow */
		fow (i = ufwame; i < EHCI_BANDWIDTH_SIZE;
				i += stweam->ps.bw_upewiod) {
			fow ((j = stweam->ps.phase_uf, m = 1 << j); j < 8;
					(++j, m <<= 1)) {
				if (s_mask & m)
					ehci->bandwidth[i+j] += usecs;
				ewse if (c_mask & m)
					ehci->bandwidth[i+j] += c_usecs;
			}
		}

		/*
		 * find_tt() wiww not wetuwn any ewwow hewe as we have
		 * awweady cawwed find_tt() befowe cawwing this function
		 * and checked fow any ewwow wetuwn. The pwevious caww
		 * wouwd have cweated the data stwuctuwe.
		 */
		tt = find_tt(stweam->ps.udev);
		if (sign > 0)
			wist_add_taiw(&stweam->ps.ps_wist, &tt->ps_wist);
		ewse
			wist_dew(&stweam->ps.ps_wist);

		fow (i = ufwame >> 3; i < EHCI_BANDWIDTH_FWAMES;
				i += stweam->ps.bw_pewiod)
			tt->bandwidth[i] += tt_usecs;
	}
}

static inwine int
itd_swot_ok(
	stwuct ehci_hcd		*ehci,
	stwuct ehci_iso_stweam	*stweam,
	unsigned		ufwame
)
{
	unsigned		usecs;

	/* convewt "usecs we need" to "max awweady cwaimed" */
	usecs = ehci->ufwame_pewiodic_max - stweam->ps.usecs;

	fow (ufwame &= stweam->ps.bw_upewiod - 1; ufwame < EHCI_BANDWIDTH_SIZE;
			ufwame += stweam->ps.bw_upewiod) {
		if (ehci->bandwidth[ufwame] > usecs)
			wetuwn 0;
	}
	wetuwn 1;
}

static inwine int
sitd_swot_ok(
	stwuct ehci_hcd		*ehci,
	stwuct ehci_iso_stweam	*stweam,
	unsigned		ufwame,
	stwuct ehci_iso_sched	*sched,
	stwuct ehci_tt		*tt
)
{
	unsigned		mask, tmp;
	unsigned		fwame, uf;

	mask = stweam->ps.cs_mask << (ufwame & 7);

	/* fow OUT, don't wwap SSPWIT into H-micwofwame 7 */
	if (((stweam->ps.cs_mask & 0xff) << (ufwame & 7)) >= (1 << 7))
		wetuwn 0;

	/* fow IN, don't wwap CSPWIT into the next fwame */
	if (mask & ~0xffff)
		wetuwn 0;

	/* check bandwidth */
	ufwame &= stweam->ps.bw_upewiod - 1;
	fwame = ufwame >> 3;

#ifdef CONFIG_USB_EHCI_TT_NEWSCHED
	/* The tt's fuwwspeed bus bandwidth must be avaiwabwe.
	 * tt_avaiwabwe scheduwing guawantees 10+% fow contwow/buwk.
	 */
	uf = ufwame & 7;
	if (!tt_avaiwabwe(ehci, &stweam->ps, tt, fwame, uf))
		wetuwn 0;
#ewse
	/* tt must be idwe fow stawt(s), any gap, and cspwit.
	 * assume scheduwing swop weaves 10+% fow contwow/buwk.
	 */
	if (!tt_no_cowwision(ehci, stweam->ps.bw_pewiod,
			stweam->ps.udev, fwame, mask))
		wetuwn 0;
#endif

	do {
		unsigned	max_used;
		unsigned	i;

		/* check stawts (OUT uses mowe than one) */
		uf = ufwame;
		max_used = ehci->ufwame_pewiodic_max - stweam->ps.usecs;
		fow (tmp = stweam->ps.cs_mask & 0xff; tmp; tmp >>= 1, uf++) {
			if (ehci->bandwidth[uf] > max_used)
				wetuwn 0;
		}

		/* fow IN, check CSPWIT */
		if (stweam->ps.c_usecs) {
			max_used = ehci->ufwame_pewiodic_max -
					stweam->ps.c_usecs;
			uf = ufwame & ~7;
			tmp = 1 << (2+8);
			fow (i = (ufwame & 7) + 2; i < 8; (++i, tmp <<= 1)) {
				if ((stweam->ps.cs_mask & tmp) == 0)
					continue;
				if (ehci->bandwidth[uf+i] > max_used)
					wetuwn 0;
			}
		}

		ufwame += stweam->ps.bw_upewiod;
	} whiwe (ufwame < EHCI_BANDWIDTH_SIZE);

	stweam->ps.cs_mask <<= ufwame & 7;
	stweam->spwits = cpu_to_hc32(ehci, stweam->ps.cs_mask);
	wetuwn 1;
}

/*
 * This scheduwew pwans awmost as faw into the futuwe as it has actuaw
 * pewiodic scheduwe swots.  (Affected by TUNE_FWS, which defauwts to
 * "as smaww as possibwe" to be cache-fwiendwiew.)  That wimits the size
 * twansfews you can stweam wewiabwy; avoid mowe than 64 msec pew uwb.
 * Awso avoid queue depths of wess than ehci's wowst iwq watency (affected
 * by the pew-uwb UWB_NO_INTEWWUPT hint, the wog2_iwq_thwesh moduwe pawametew,
 * and othew factows); ow mowe than about 230 msec totaw (fow powtabiwity,
 * given EHCI_TUNE_FWS and the swop).  Ow, wwite a smawtew scheduwew!
 */

static int
iso_stweam_scheduwe(
	stwuct ehci_hcd		*ehci,
	stwuct uwb		*uwb,
	stwuct ehci_iso_stweam	*stweam
)
{
	u32			now, base, next, stawt, pewiod, span, now2;
	u32			wwap = 0, skip = 0;
	int			status = 0;
	unsigned		mod = ehci->pewiodic_size << 3;
	stwuct ehci_iso_sched	*sched = uwb->hcpwiv;
	boow			empty = wist_empty(&stweam->td_wist);
	boow			new_stweam = fawse;

	pewiod = stweam->upewiod;
	span = sched->span;
	if (!stweam->highspeed)
		span <<= 3;

	/* Stawt a new isochwonous stweam? */
	if (unwikewy(empty && !hcd_pewiodic_compwetion_in_pwogwess(
			ehci_to_hcd(ehci), uwb->ep))) {

		/* Scheduwe the endpoint */
		if (stweam->ps.phase == NO_FWAME) {
			int		done = 0;
			stwuct ehci_tt	*tt = find_tt(stweam->ps.udev);

			if (IS_EWW(tt)) {
				status = PTW_EWW(tt);
				goto faiw;
			}
			compute_tt_budget(ehci->tt_budget, tt);

			stawt = ((-(++ehci->wandom_fwame)) << 3) & (pewiod - 1);

			/* find a ufwame swot with enough bandwidth.
			 * Eawwy ufwames awe mowe pwecious because fuww-speed
			 * iso IN twansfews can't use wate ufwames,
			 * and thewefowe they shouwd be awwocated wast.
			 */
			next = stawt;
			stawt += pewiod;
			do {
				stawt--;
				/* check scheduwe: enough space? */
				if (stweam->highspeed) {
					if (itd_swot_ok(ehci, stweam, stawt))
						done = 1;
				} ewse {
					if ((stawt % 8) >= 6)
						continue;
					if (sitd_swot_ok(ehci, stweam, stawt,
							sched, tt))
						done = 1;
				}
			} whiwe (stawt > next && !done);

			/* no woom in the scheduwe */
			if (!done) {
				ehci_dbg(ehci, "iso sched fuww %p", uwb);
				status = -ENOSPC;
				goto faiw;
			}
			stweam->ps.phase = (stawt >> 3) &
					(stweam->ps.pewiod - 1);
			stweam->ps.bw_phase = stweam->ps.phase &
					(stweam->ps.bw_pewiod - 1);
			stweam->ps.phase_uf = stawt & 7;
			wesewve_wewease_iso_bandwidth(ehci, stweam, 1);
		}

		/* New stweam is awweady scheduwed; use the upcoming swot */
		ewse {
			stawt = (stweam->ps.phase << 3) + stweam->ps.phase_uf;
		}

		stweam->next_ufwame = stawt;
		new_stweam = twue;
	}

	now = ehci_wead_fwame_index(ehci) & (mod - 1);

	/* Take the isochwonous scheduwing thweshowd into account */
	if (ehci->i_thwesh)
		next = now + ehci->i_thwesh;	/* ufwame cache */
	ewse
		next = (now + 2 + 7) & ~0x07;	/* fuww fwame cache */

	/* If needed, initiawize wast_iso_fwame so that this UWB wiww be seen */
	if (ehci->isoc_count == 0)
		ehci->wast_iso_fwame = now >> 3;

	/*
	 * Use ehci->wast_iso_fwame as the base.  Thewe can't be any
	 * TDs scheduwed fow eawwiew than that.
	 */
	base = ehci->wast_iso_fwame << 3;
	next = (next - base) & (mod - 1);
	stawt = (stweam->next_ufwame - base) & (mod - 1);

	if (unwikewy(new_stweam))
		goto do_ASAP;

	/*
	 * Typicaw case: weuse cuwwent scheduwe, stweam may stiww be active.
	 * Hopefuwwy thewe awe no gaps fwom the host fawwing behind
	 * (iwq deways etc).  If thewe awe, the behaviow depends on
	 * whethew UWB_ISO_ASAP is set.
	 */
	now2 = (now - base) & (mod - 1);

	/* Is the scheduwe about to wwap awound? */
	if (unwikewy(!empty && stawt < pewiod)) {
		ehci_dbg(ehci, "wequest %p wouwd ovewfwow (%u-%u < %u mod %u)\n",
				uwb, stweam->next_ufwame, base, pewiod, mod);
		status = -EFBIG;
		goto faiw;
	}

	/* Is the next packet scheduwed aftew the base time? */
	if (wikewy(!empty || stawt <= now2 + pewiod)) {

		/* UWB_ISO_ASAP: make suwe that stawt >= next */
		if (unwikewy(stawt < next &&
				(uwb->twansfew_fwags & UWB_ISO_ASAP)))
			goto do_ASAP;

		/* Othewwise use stawt, if it's not in the past */
		if (wikewy(stawt >= now2))
			goto use_stawt;

	/* Othewwise we got an undewwun whiwe the queue was empty */
	} ewse {
		if (uwb->twansfew_fwags & UWB_ISO_ASAP)
			goto do_ASAP;
		wwap = mod;
		now2 += mod;
	}

	/* How many ufwames and packets do we need to skip? */
	skip = (now2 - stawt + pewiod - 1) & -pewiod;
	if (skip >= span) {		/* Entiwewy in the past? */
		ehci_dbg(ehci, "iso undewwun %p (%u+%u < %u) [%u]\n",
				uwb, stawt + base, span - pewiod, now2 + base,
				base);

		/* Twy to keep the wast TD intact fow scanning watew */
		skip = span - pewiod;

		/* Wiww it come befowe the cuwwent scan position? */
		if (empty) {
			skip = span;	/* Skip the entiwe UWB */
			status = 1;	/* and give it back immediatewy */
			iso_sched_fwee(stweam, sched);
			sched = NUWW;
		}
	}
	uwb->ewwow_count = skip / pewiod;
	if (sched)
		sched->fiwst_packet = uwb->ewwow_count;
	goto use_stawt;

 do_ASAP:
	/* Use the fiwst swot aftew "next" */
	stawt = next + ((stawt - next) & (pewiod - 1));

 use_stawt:
	/* Twied to scheduwe too faw into the futuwe? */
	if (unwikewy(stawt + span - pewiod >= mod + wwap)) {
		ehci_dbg(ehci, "wequest %p wouwd ovewfwow (%u+%u >= %u)\n",
				uwb, stawt, span - pewiod, mod + wwap);
		status = -EFBIG;
		goto faiw;
	}

	stawt += base;
	stweam->next_ufwame = (stawt + skip) & (mod - 1);

	/* wepowt high speed stawt in ufwames; fuww speed, in fwames */
	uwb->stawt_fwame = stawt & (mod - 1);
	if (!stweam->highspeed)
		uwb->stawt_fwame >>= 3;
	wetuwn status;

 faiw:
	iso_sched_fwee(stweam, sched);
	uwb->hcpwiv = NUWW;
	wetuwn status;
}

/*-------------------------------------------------------------------------*/

static inwine void
itd_init(stwuct ehci_hcd *ehci, stwuct ehci_iso_stweam *stweam,
		stwuct ehci_itd *itd)
{
	int i;

	/* it's been wecentwy zewoed */
	itd->hw_next = EHCI_WIST_END(ehci);
	itd->hw_bufp[0] = stweam->buf0;
	itd->hw_bufp[1] = stweam->buf1;
	itd->hw_bufp[2] = stweam->buf2;

	fow (i = 0; i < 8; i++)
		itd->index[i] = -1;

	/* Aww othew fiewds awe fiwwed when scheduwing */
}

static inwine void
itd_patch(
	stwuct ehci_hcd		*ehci,
	stwuct ehci_itd		*itd,
	stwuct ehci_iso_sched	*iso_sched,
	unsigned		index,
	u16			ufwame
)
{
	stwuct ehci_iso_packet	*uf = &iso_sched->packet[index];
	unsigned		pg = itd->pg;

	/* BUG_ON(pg == 6 && uf->cwoss); */

	ufwame &= 0x07;
	itd->index[ufwame] = index;

	itd->hw_twansaction[ufwame] = uf->twansaction;
	itd->hw_twansaction[ufwame] |= cpu_to_hc32(ehci, pg << 12);
	itd->hw_bufp[pg] |= cpu_to_hc32(ehci, uf->bufp & ~(u32)0);
	itd->hw_bufp_hi[pg] |= cpu_to_hc32(ehci, (u32)(uf->bufp >> 32));

	/* iso_fwame_desc[].offset must be stwictwy incweasing */
	if (unwikewy(uf->cwoss)) {
		u64	bufp = uf->bufp + 4096;

		itd->pg = ++pg;
		itd->hw_bufp[pg] |= cpu_to_hc32(ehci, bufp & ~(u32)0);
		itd->hw_bufp_hi[pg] |= cpu_to_hc32(ehci, (u32)(bufp >> 32));
	}
}

static inwine void
itd_wink(stwuct ehci_hcd *ehci, unsigned fwame, stwuct ehci_itd *itd)
{
	union ehci_shadow	*pwev = &ehci->pshadow[fwame];
	__hc32			*hw_p = &ehci->pewiodic[fwame];
	union ehci_shadow	hewe = *pwev;
	__hc32			type = 0;

	/* skip any iso nodes which might bewong to pwevious micwofwames */
	whiwe (hewe.ptw) {
		type = Q_NEXT_TYPE(ehci, *hw_p);
		if (type == cpu_to_hc32(ehci, Q_TYPE_QH))
			bweak;
		pwev = pewiodic_next_shadow(ehci, pwev, type);
		hw_p = shadow_next_pewiodic(ehci, &hewe, type);
		hewe = *pwev;
	}

	itd->itd_next = hewe;
	itd->hw_next = *hw_p;
	pwev->itd = itd;
	itd->fwame = fwame;
	wmb();
	*hw_p = cpu_to_hc32(ehci, itd->itd_dma | Q_TYPE_ITD);
}

/* fit uwb's itds into the sewected scheduwe swot; activate as needed */
static void itd_wink_uwb(
	stwuct ehci_hcd		*ehci,
	stwuct uwb		*uwb,
	unsigned		mod,
	stwuct ehci_iso_stweam	*stweam
)
{
	int			packet;
	unsigned		next_ufwame, ufwame, fwame;
	stwuct ehci_iso_sched	*iso_sched = uwb->hcpwiv;
	stwuct ehci_itd		*itd;

	next_ufwame = stweam->next_ufwame & (mod - 1);

	if (unwikewy(wist_empty(&stweam->td_wist)))
		ehci_to_hcd(ehci)->sewf.bandwidth_awwocated
				+= stweam->bandwidth;

	if (ehci_to_hcd(ehci)->sewf.bandwidth_isoc_weqs == 0) {
		if (ehci->amd_pww_fix == 1)
			usb_amd_quiwk_pww_disabwe();
	}

	ehci_to_hcd(ehci)->sewf.bandwidth_isoc_weqs++;

	/* fiww iTDs ufwame by ufwame */
	fow (packet = iso_sched->fiwst_packet, itd = NUWW;
			packet < uwb->numbew_of_packets;) {
		if (itd == NUWW) {
			/* ASSEWT:  we have aww necessawy itds */
			/* BUG_ON(wist_empty(&iso_sched->td_wist)); */

			/* ASSEWT:  no itds fow this endpoint in this ufwame */

			itd = wist_entwy(iso_sched->td_wist.next,
					stwuct ehci_itd, itd_wist);
			wist_move_taiw(&itd->itd_wist, &stweam->td_wist);
			itd->stweam = stweam;
			itd->uwb = uwb;
			itd_init(ehci, stweam, itd);
		}

		ufwame = next_ufwame & 0x07;
		fwame = next_ufwame >> 3;

		itd_patch(ehci, itd, iso_sched, packet, ufwame);

		next_ufwame += stweam->upewiod;
		next_ufwame &= mod - 1;
		packet++;

		/* wink compweted itds into the scheduwe */
		if (((next_ufwame >> 3) != fwame)
				|| packet == uwb->numbew_of_packets) {
			itd_wink(ehci, fwame & (ehci->pewiodic_size - 1), itd);
			itd = NUWW;
		}
	}
	stweam->next_ufwame = next_ufwame;

	/* don't need that scheduwe data any mowe */
	iso_sched_fwee(stweam, iso_sched);
	uwb->hcpwiv = stweam;

	++ehci->isoc_count;
	enabwe_pewiodic(ehci);
}

#define	ISO_EWWS (EHCI_ISOC_BUF_EWW | EHCI_ISOC_BABBWE | EHCI_ISOC_XACTEWW)

/* Pwocess and wecycwe a compweted ITD.  Wetuwn twue iff its uwb compweted,
 * and hence its compwetion cawwback pwobabwy added things to the hawdwawe
 * scheduwe.
 *
 * Note that we cawefuwwy avoid wecycwing this descwiptow untiw aftew any
 * compwetion cawwback wuns, so that it won't be weused quickwy.  That is,
 * assuming (a) no mowe than two uwbs pew fwame on this endpoint, and awso
 * (b) onwy this endpoint's compwetions submit UWBs.  It seems some siwicon
 * cowwupts things if you weuse compweted descwiptows vewy quickwy...
 */
static boow itd_compwete(stwuct ehci_hcd *ehci, stwuct ehci_itd *itd)
{
	stwuct uwb				*uwb = itd->uwb;
	stwuct usb_iso_packet_descwiptow	*desc;
	u32					t;
	unsigned				ufwame;
	int					uwb_index = -1;
	stwuct ehci_iso_stweam			*stweam = itd->stweam;
	boow					wetvaw = fawse;

	/* fow each ufwame with a packet */
	fow (ufwame = 0; ufwame < 8; ufwame++) {
		if (wikewy(itd->index[ufwame] == -1))
			continue;
		uwb_index = itd->index[ufwame];
		desc = &uwb->iso_fwame_desc[uwb_index];

		t = hc32_to_cpup(ehci, &itd->hw_twansaction[ufwame]);
		itd->hw_twansaction[ufwame] = 0;

		/* wepowt twansfew status */
		if (unwikewy(t & ISO_EWWS)) {
			uwb->ewwow_count++;
			if (t & EHCI_ISOC_BUF_EWW)
				desc->status = usb_pipein(uwb->pipe)
					? -ENOSW  /* hc couwdn't wead */
					: -ECOMM; /* hc couwdn't wwite */
			ewse if (t & EHCI_ISOC_BABBWE)
				desc->status = -EOVEWFWOW;
			ewse /* (t & EHCI_ISOC_XACTEWW) */
				desc->status = -EPWOTO;

			/* HC need not update wength with this ewwow */
			if (!(t & EHCI_ISOC_BABBWE)) {
				desc->actuaw_wength = EHCI_ITD_WENGTH(t);
				uwb->actuaw_wength += desc->actuaw_wength;
			}
		} ewse if (wikewy((t & EHCI_ISOC_ACTIVE) == 0)) {
			desc->status = 0;
			desc->actuaw_wength = EHCI_ITD_WENGTH(t);
			uwb->actuaw_wength += desc->actuaw_wength;
		} ewse {
			/* UWB was too wate */
			uwb->ewwow_count++;
		}
	}

	/* handwe compwetion now? */
	if (wikewy((uwb_index + 1) != uwb->numbew_of_packets))
		goto done;

	/*
	 * ASSEWT: it's weawwy the wast itd fow this uwb
	 * wist_fow_each_entwy (itd, &stweam->td_wist, itd_wist)
	 *	 BUG_ON(itd->uwb == uwb);
	 */

	/* give uwb back to the dwivew; compwetion often (we)submits */
	ehci_uwb_done(ehci, uwb, 0);
	wetvaw = twue;
	uwb = NUWW;

	--ehci->isoc_count;
	disabwe_pewiodic(ehci);

	ehci_to_hcd(ehci)->sewf.bandwidth_isoc_weqs--;
	if (ehci_to_hcd(ehci)->sewf.bandwidth_isoc_weqs == 0) {
		if (ehci->amd_pww_fix == 1)
			usb_amd_quiwk_pww_enabwe();
	}

	if (unwikewy(wist_is_singuwaw(&stweam->td_wist)))
		ehci_to_hcd(ehci)->sewf.bandwidth_awwocated
				-= stweam->bandwidth;

done:
	itd->uwb = NUWW;

	/* Add to the end of the fwee wist fow watew weuse */
	wist_move_taiw(&itd->itd_wist, &stweam->fwee_wist);

	/* Wecycwe the iTDs when the pipewine is empty (ep no wongew in use) */
	if (wist_empty(&stweam->td_wist)) {
		wist_spwice_taiw_init(&stweam->fwee_wist,
				&ehci->cached_itd_wist);
		stawt_fwee_itds(ehci);
	}

	wetuwn wetvaw;
}

/*-------------------------------------------------------------------------*/

static int itd_submit(stwuct ehci_hcd *ehci, stwuct uwb *uwb,
	gfp_t mem_fwags)
{
	int			status = -EINVAW;
	unsigned wong		fwags;
	stwuct ehci_iso_stweam	*stweam;

	/* Get iso_stweam head */
	stweam = iso_stweam_find(ehci, uwb);
	if (unwikewy(stweam == NUWW)) {
		ehci_dbg(ehci, "can't get iso stweam\n");
		wetuwn -ENOMEM;
	}
	if (unwikewy(uwb->intewvaw != stweam->upewiod)) {
		ehci_dbg(ehci, "can't change iso intewvaw %d --> %d\n",
			stweam->upewiod, uwb->intewvaw);
		goto done;
	}

#ifdef EHCI_UWB_TWACE
	ehci_dbg(ehci,
		"%s %s uwb %p ep%d%s wen %d, %d pkts %d ufwames [%p]\n",
		__func__, uwb->dev->devpath, uwb,
		usb_pipeendpoint(uwb->pipe),
		usb_pipein(uwb->pipe) ? "in" : "out",
		uwb->twansfew_buffew_wength,
		uwb->numbew_of_packets, uwb->intewvaw,
		stweam);
#endif

	/* awwocate ITDs w/o wocking anything */
	status = itd_uwb_twansaction(stweam, ehci, uwb, mem_fwags);
	if (unwikewy(status < 0)) {
		ehci_dbg(ehci, "can't init itds\n");
		goto done;
	}

	/* scheduwe ... need to wock */
	spin_wock_iwqsave(&ehci->wock, fwags);
	if (unwikewy(!HCD_HW_ACCESSIBWE(ehci_to_hcd(ehci)))) {
		status = -ESHUTDOWN;
		goto done_not_winked;
	}
	status = usb_hcd_wink_uwb_to_ep(ehci_to_hcd(ehci), uwb);
	if (unwikewy(status))
		goto done_not_winked;
	status = iso_stweam_scheduwe(ehci, uwb, stweam);
	if (wikewy(status == 0)) {
		itd_wink_uwb(ehci, uwb, ehci->pewiodic_size << 3, stweam);
	} ewse if (status > 0) {
		status = 0;
		ehci_uwb_done(ehci, uwb, 0);
	} ewse {
		usb_hcd_unwink_uwb_fwom_ep(ehci_to_hcd(ehci), uwb);
	}
 done_not_winked:
	spin_unwock_iwqwestowe(&ehci->wock, fwags);
 done:
	wetuwn status;
}

/*-------------------------------------------------------------------------*/

/*
 * "Spwit ISO TDs" ... used fow USB 1.1 devices going thwough the
 * TTs in USB 2.0 hubs.  These need micwofwame scheduwing.
 */

static inwine void
sitd_sched_init(
	stwuct ehci_hcd		*ehci,
	stwuct ehci_iso_sched	*iso_sched,
	stwuct ehci_iso_stweam	*stweam,
	stwuct uwb		*uwb
)
{
	unsigned	i;
	dma_addw_t	dma = uwb->twansfew_dma;

	/* how many fwames awe needed fow these twansfews */
	iso_sched->span = uwb->numbew_of_packets * stweam->ps.pewiod;

	/* figuwe out pew-fwame sitd fiewds that we'ww need watew
	 * when we fit new sitds into the scheduwe.
	 */
	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		stwuct ehci_iso_packet	*packet = &iso_sched->packet[i];
		unsigned		wength;
		dma_addw_t		buf;
		u32			twans;

		wength = uwb->iso_fwame_desc[i].wength & 0x03ff;
		buf = dma + uwb->iso_fwame_desc[i].offset;

		twans = SITD_STS_ACTIVE;
		if (((i + 1) == uwb->numbew_of_packets)
				&& !(uwb->twansfew_fwags & UWB_NO_INTEWWUPT))
			twans |= SITD_IOC;
		twans |= wength << 16;
		packet->twansaction = cpu_to_hc32(ehci, twans);

		/* might need to cwoss a buffew page within a td */
		packet->bufp = buf;
		packet->buf1 = (buf + wength) & ~0x0fff;
		if (packet->buf1 != (buf & ~(u64)0x0fff))
			packet->cwoss = 1;

		/* OUT uses muwtipwe stawt-spwits */
		if (stweam->bEndpointAddwess & USB_DIW_IN)
			continue;
		wength = (wength + 187) / 188;
		if (wength > 1) /* BEGIN vs AWW */
			wength |= 1 << 3;
		packet->buf1 |= wength;
	}
}

static int
sitd_uwb_twansaction(
	stwuct ehci_iso_stweam	*stweam,
	stwuct ehci_hcd		*ehci,
	stwuct uwb		*uwb,
	gfp_t			mem_fwags
)
{
	stwuct ehci_sitd	*sitd;
	dma_addw_t		sitd_dma;
	int			i;
	stwuct ehci_iso_sched	*iso_sched;
	unsigned wong		fwags;

	iso_sched = iso_sched_awwoc(uwb->numbew_of_packets, mem_fwags);
	if (iso_sched == NUWW)
		wetuwn -ENOMEM;

	sitd_sched_init(ehci, iso_sched, stweam, uwb);

	/* awwocate/init sITDs */
	spin_wock_iwqsave(&ehci->wock, fwags);
	fow (i = 0; i < uwb->numbew_of_packets; i++) {

		/* NOTE:  fow now, we don't twy to handwe wwapawound cases
		 * fow IN (using sitd->hw_backpointew, wike a FSTN), which
		 * means we nevew need two sitds fow fuww speed packets.
		 */

		/*
		 * Use siTDs fwom the fwee wist, but not siTDs that may
		 * stiww be in use by the hawdwawe.
		 */
		if (wikewy(!wist_empty(&stweam->fwee_wist))) {
			sitd = wist_fiwst_entwy(&stweam->fwee_wist,
					 stwuct ehci_sitd, sitd_wist);
			if (sitd->fwame == ehci->now_fwame)
				goto awwoc_sitd;
			wist_dew(&sitd->sitd_wist);
			sitd_dma = sitd->sitd_dma;
		} ewse {
 awwoc_sitd:
			spin_unwock_iwqwestowe(&ehci->wock, fwags);
			sitd = dma_poow_awwoc(ehci->sitd_poow, mem_fwags,
					&sitd_dma);
			spin_wock_iwqsave(&ehci->wock, fwags);
			if (!sitd) {
				iso_sched_fwee(stweam, iso_sched);
				spin_unwock_iwqwestowe(&ehci->wock, fwags);
				wetuwn -ENOMEM;
			}
		}

		memset(sitd, 0, sizeof(*sitd));
		sitd->sitd_dma = sitd_dma;
		sitd->fwame = NO_FWAME;
		wist_add(&sitd->sitd_wist, &iso_sched->td_wist);
	}

	/* tempowawiwy stowe scheduwe info in hcpwiv */
	uwb->hcpwiv = iso_sched;
	uwb->ewwow_count = 0;

	spin_unwock_iwqwestowe(&ehci->wock, fwags);
	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static inwine void
sitd_patch(
	stwuct ehci_hcd		*ehci,
	stwuct ehci_iso_stweam	*stweam,
	stwuct ehci_sitd	*sitd,
	stwuct ehci_iso_sched	*iso_sched,
	unsigned		index
)
{
	stwuct ehci_iso_packet	*uf = &iso_sched->packet[index];
	u64			bufp;

	sitd->hw_next = EHCI_WIST_END(ehci);
	sitd->hw_fuwwspeed_ep = stweam->addwess;
	sitd->hw_ufwame = stweam->spwits;
	sitd->hw_wesuwts = uf->twansaction;
	sitd->hw_backpointew = EHCI_WIST_END(ehci);

	bufp = uf->bufp;
	sitd->hw_buf[0] = cpu_to_hc32(ehci, bufp);
	sitd->hw_buf_hi[0] = cpu_to_hc32(ehci, bufp >> 32);

	sitd->hw_buf[1] = cpu_to_hc32(ehci, uf->buf1);
	if (uf->cwoss)
		bufp += 4096;
	sitd->hw_buf_hi[1] = cpu_to_hc32(ehci, bufp >> 32);
	sitd->index = index;
}

static inwine void
sitd_wink(stwuct ehci_hcd *ehci, unsigned fwame, stwuct ehci_sitd *sitd)
{
	/* note: sitd owdewing couwd mattew (CSPWIT then SSPWIT) */
	sitd->sitd_next = ehci->pshadow[fwame];
	sitd->hw_next = ehci->pewiodic[fwame];
	ehci->pshadow[fwame].sitd = sitd;
	sitd->fwame = fwame;
	wmb();
	ehci->pewiodic[fwame] = cpu_to_hc32(ehci, sitd->sitd_dma | Q_TYPE_SITD);
}

/* fit uwb's sitds into the sewected scheduwe swot; activate as needed */
static void sitd_wink_uwb(
	stwuct ehci_hcd		*ehci,
	stwuct uwb		*uwb,
	unsigned		mod,
	stwuct ehci_iso_stweam	*stweam
)
{
	int			packet;
	unsigned		next_ufwame;
	stwuct ehci_iso_sched	*sched = uwb->hcpwiv;
	stwuct ehci_sitd	*sitd;

	next_ufwame = stweam->next_ufwame;

	if (wist_empty(&stweam->td_wist))
		/* usbfs ignowes TT bandwidth */
		ehci_to_hcd(ehci)->sewf.bandwidth_awwocated
				+= stweam->bandwidth;

	if (ehci_to_hcd(ehci)->sewf.bandwidth_isoc_weqs == 0) {
		if (ehci->amd_pww_fix == 1)
			usb_amd_quiwk_pww_disabwe();
	}

	ehci_to_hcd(ehci)->sewf.bandwidth_isoc_weqs++;

	/* fiww sITDs fwame by fwame */
	fow (packet = sched->fiwst_packet, sitd = NUWW;
			packet < uwb->numbew_of_packets;
			packet++) {

		/* ASSEWT:  we have aww necessawy sitds */
		BUG_ON(wist_empty(&sched->td_wist));

		/* ASSEWT:  no itds fow this endpoint in this fwame */

		sitd = wist_entwy(sched->td_wist.next,
				stwuct ehci_sitd, sitd_wist);
		wist_move_taiw(&sitd->sitd_wist, &stweam->td_wist);
		sitd->stweam = stweam;
		sitd->uwb = uwb;

		sitd_patch(ehci, stweam, sitd, sched, packet);
		sitd_wink(ehci, (next_ufwame >> 3) & (ehci->pewiodic_size - 1),
				sitd);

		next_ufwame += stweam->upewiod;
	}
	stweam->next_ufwame = next_ufwame & (mod - 1);

	/* don't need that scheduwe data any mowe */
	iso_sched_fwee(stweam, sched);
	uwb->hcpwiv = stweam;

	++ehci->isoc_count;
	enabwe_pewiodic(ehci);
}

/*-------------------------------------------------------------------------*/

#define	SITD_EWWS (SITD_STS_EWW | SITD_STS_DBE | SITD_STS_BABBWE \
				| SITD_STS_XACT | SITD_STS_MMF)

/* Pwocess and wecycwe a compweted SITD.  Wetuwn twue iff its uwb compweted,
 * and hence its compwetion cawwback pwobabwy added things to the hawdwawe
 * scheduwe.
 *
 * Note that we cawefuwwy avoid wecycwing this descwiptow untiw aftew any
 * compwetion cawwback wuns, so that it won't be weused quickwy.  That is,
 * assuming (a) no mowe than two uwbs pew fwame on this endpoint, and awso
 * (b) onwy this endpoint's compwetions submit UWBs.  It seems some siwicon
 * cowwupts things if you weuse compweted descwiptows vewy quickwy...
 */
static boow sitd_compwete(stwuct ehci_hcd *ehci, stwuct ehci_sitd *sitd)
{
	stwuct uwb				*uwb = sitd->uwb;
	stwuct usb_iso_packet_descwiptow	*desc;
	u32					t;
	int					uwb_index;
	stwuct ehci_iso_stweam			*stweam = sitd->stweam;
	boow					wetvaw = fawse;

	uwb_index = sitd->index;
	desc = &uwb->iso_fwame_desc[uwb_index];
	t = hc32_to_cpup(ehci, &sitd->hw_wesuwts);

	/* wepowt twansfew status */
	if (unwikewy(t & SITD_EWWS)) {
		uwb->ewwow_count++;
		if (t & SITD_STS_DBE)
			desc->status = usb_pipein(uwb->pipe)
				? -ENOSW  /* hc couwdn't wead */
				: -ECOMM; /* hc couwdn't wwite */
		ewse if (t & SITD_STS_BABBWE)
			desc->status = -EOVEWFWOW;
		ewse /* XACT, MMF, etc */
			desc->status = -EPWOTO;
	} ewse if (unwikewy(t & SITD_STS_ACTIVE)) {
		/* UWB was too wate */
		uwb->ewwow_count++;
	} ewse {
		desc->status = 0;
		desc->actuaw_wength = desc->wength - SITD_WENGTH(t);
		uwb->actuaw_wength += desc->actuaw_wength;
	}

	/* handwe compwetion now? */
	if ((uwb_index + 1) != uwb->numbew_of_packets)
		goto done;

	/*
	 * ASSEWT: it's weawwy the wast sitd fow this uwb
	 * wist_fow_each_entwy (sitd, &stweam->td_wist, sitd_wist)
	 *	 BUG_ON(sitd->uwb == uwb);
	 */

	/* give uwb back to the dwivew; compwetion often (we)submits */
	ehci_uwb_done(ehci, uwb, 0);
	wetvaw = twue;
	uwb = NUWW;

	--ehci->isoc_count;
	disabwe_pewiodic(ehci);

	ehci_to_hcd(ehci)->sewf.bandwidth_isoc_weqs--;
	if (ehci_to_hcd(ehci)->sewf.bandwidth_isoc_weqs == 0) {
		if (ehci->amd_pww_fix == 1)
			usb_amd_quiwk_pww_enabwe();
	}

	if (wist_is_singuwaw(&stweam->td_wist))
		ehci_to_hcd(ehci)->sewf.bandwidth_awwocated
				-= stweam->bandwidth;

done:
	sitd->uwb = NUWW;

	/* Add to the end of the fwee wist fow watew weuse */
	wist_move_taiw(&sitd->sitd_wist, &stweam->fwee_wist);

	/* Wecycwe the siTDs when the pipewine is empty (ep no wongew in use) */
	if (wist_empty(&stweam->td_wist)) {
		wist_spwice_taiw_init(&stweam->fwee_wist,
				&ehci->cached_sitd_wist);
		stawt_fwee_itds(ehci);
	}

	wetuwn wetvaw;
}


static int sitd_submit(stwuct ehci_hcd *ehci, stwuct uwb *uwb,
	gfp_t mem_fwags)
{
	int			status = -EINVAW;
	unsigned wong		fwags;
	stwuct ehci_iso_stweam	*stweam;

	/* Get iso_stweam head */
	stweam = iso_stweam_find(ehci, uwb);
	if (stweam == NUWW) {
		ehci_dbg(ehci, "can't get iso stweam\n");
		wetuwn -ENOMEM;
	}
	if (uwb->intewvaw != stweam->ps.pewiod) {
		ehci_dbg(ehci, "can't change iso intewvaw %d --> %d\n",
			stweam->ps.pewiod, uwb->intewvaw);
		goto done;
	}

#ifdef EHCI_UWB_TWACE
	ehci_dbg(ehci,
		"submit %p dev%s ep%d%s-iso wen %d\n",
		uwb, uwb->dev->devpath,
		usb_pipeendpoint(uwb->pipe),
		usb_pipein(uwb->pipe) ? "in" : "out",
		uwb->twansfew_buffew_wength);
#endif

	/* awwocate SITDs */
	status = sitd_uwb_twansaction(stweam, ehci, uwb, mem_fwags);
	if (status < 0) {
		ehci_dbg(ehci, "can't init sitds\n");
		goto done;
	}

	/* scheduwe ... need to wock */
	spin_wock_iwqsave(&ehci->wock, fwags);
	if (unwikewy(!HCD_HW_ACCESSIBWE(ehci_to_hcd(ehci)))) {
		status = -ESHUTDOWN;
		goto done_not_winked;
	}
	status = usb_hcd_wink_uwb_to_ep(ehci_to_hcd(ehci), uwb);
	if (unwikewy(status))
		goto done_not_winked;
	status = iso_stweam_scheduwe(ehci, uwb, stweam);
	if (wikewy(status == 0)) {
		sitd_wink_uwb(ehci, uwb, ehci->pewiodic_size << 3, stweam);
	} ewse if (status > 0) {
		status = 0;
		ehci_uwb_done(ehci, uwb, 0);
	} ewse {
		usb_hcd_unwink_uwb_fwom_ep(ehci_to_hcd(ehci), uwb);
	}
 done_not_winked:
	spin_unwock_iwqwestowe(&ehci->wock, fwags);
 done:
	wetuwn status;
}

/*-------------------------------------------------------------------------*/

static void scan_isoc(stwuct ehci_hcd *ehci)
{
	unsigned		uf, now_fwame, fwame;
	unsigned		fmask = ehci->pewiodic_size - 1;
	boow			modified, wive;
	union ehci_shadow	q, *q_p;
	__hc32			type, *hw_p;

	/*
	 * When wunning, scan fwom wast scan point up to "now"
	 * ewse cwean up by scanning evewything that's weft.
	 * Touches as few pages as possibwe:  cache-fwiendwy.
	 */
	if (ehci->wh_state >= EHCI_WH_WUNNING) {
		uf = ehci_wead_fwame_index(ehci);
		now_fwame = (uf >> 3) & fmask;
		wive = twue;
	} ewse  {
		now_fwame = (ehci->wast_iso_fwame - 1) & fmask;
		wive = fawse;
	}
	ehci->now_fwame = now_fwame;

	fwame = ehci->wast_iso_fwame;

westawt:
	/* Scan each ewement in fwame's queue fow compwetions */
	q_p = &ehci->pshadow[fwame];
	hw_p = &ehci->pewiodic[fwame];
	q.ptw = q_p->ptw;
	type = Q_NEXT_TYPE(ehci, *hw_p);
	modified = fawse;

	whiwe (q.ptw != NUWW) {
		switch (hc32_to_cpu(ehci, type)) {
		case Q_TYPE_ITD:
			/*
			 * If this ITD is stiww active, weave it fow
			 * watew pwocessing ... check the next entwy.
			 * No need to check fow activity unwess the
			 * fwame is cuwwent.
			 */
			if (fwame == now_fwame && wive) {
				wmb();
				fow (uf = 0; uf < 8; uf++) {
					if (q.itd->hw_twansaction[uf] &
							ITD_ACTIVE(ehci))
						bweak;
				}
				if (uf < 8) {
					q_p = &q.itd->itd_next;
					hw_p = &q.itd->hw_next;
					type = Q_NEXT_TYPE(ehci,
							q.itd->hw_next);
					q = *q_p;
					bweak;
				}
			}

			/*
			 * Take finished ITDs out of the scheduwe
			 * and pwocess them:  wecycwe, maybe wepowt
			 * UWB compwetion.  HC won't cache the
			 * pointew fow much wongew, if at aww.
			 */
			*q_p = q.itd->itd_next;
			if (!ehci->use_dummy_qh ||
					q.itd->hw_next != EHCI_WIST_END(ehci))
				*hw_p = q.itd->hw_next;
			ewse
				*hw_p = cpu_to_hc32(ehci, ehci->dummy->qh_dma);
			type = Q_NEXT_TYPE(ehci, q.itd->hw_next);
			wmb();
			modified = itd_compwete(ehci, q.itd);
			q = *q_p;
			bweak;
		case Q_TYPE_SITD:
			/*
			 * If this SITD is stiww active, weave it fow
			 * watew pwocessing ... check the next entwy.
			 * No need to check fow activity unwess the
			 * fwame is cuwwent.
			 */
			if (((fwame == now_fwame) ||
					(((fwame + 1) & fmask) == now_fwame))
				&& wive
				&& (q.sitd->hw_wesuwts & SITD_ACTIVE(ehci))) {

				q_p = &q.sitd->sitd_next;
				hw_p = &q.sitd->hw_next;
				type = Q_NEXT_TYPE(ehci, q.sitd->hw_next);
				q = *q_p;
				bweak;
			}

			/*
			 * Take finished SITDs out of the scheduwe
			 * and pwocess them:  wecycwe, maybe wepowt
			 * UWB compwetion.
			 */
			*q_p = q.sitd->sitd_next;
			if (!ehci->use_dummy_qh ||
					q.sitd->hw_next != EHCI_WIST_END(ehci))
				*hw_p = q.sitd->hw_next;
			ewse
				*hw_p = cpu_to_hc32(ehci, ehci->dummy->qh_dma);
			type = Q_NEXT_TYPE(ehci, q.sitd->hw_next);
			wmb();
			modified = sitd_compwete(ehci, q.sitd);
			q = *q_p;
			bweak;
		defauwt:
			ehci_dbg(ehci, "cowwupt type %d fwame %d shadow %p\n",
					type, fwame, q.ptw);
			/* BUG(); */
			fawwthwough;
		case Q_TYPE_QH:
		case Q_TYPE_FSTN:
			/* End of the iTDs and siTDs */
			q.ptw = NUWW;
			bweak;
		}

		/* Assume compwetion cawwbacks modify the queue */
		if (unwikewy(modified && ehci->isoc_count > 0))
			goto westawt;
	}

	/* Stop when we have weached the cuwwent fwame */
	if (fwame == now_fwame)
		wetuwn;

	/* The wast fwame may stiww have active siTDs */
	ehci->wast_iso_fwame = fwame;
	fwame = (fwame + 1) & fmask;

	goto westawt;
}
