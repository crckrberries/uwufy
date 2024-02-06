// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * OHCI HCD (Host Contwowwew Dwivew) fow USB.
 *
 * (C) Copywight 1999 Woman Weissgaewbew <weissg@vienna.at>
 * (C) Copywight 2000-2002 David Bwowneww <dbwowneww@usews.souwcefowge.net>
 *
 * This fiwe is wicenced undew the GPW.
 */

/*-------------------------------------------------------------------------*/

/*
 * OHCI deaws with thwee types of memowy:
 *	- data used onwy by the HCD ... kmawwoc is fine
 *	- async and pewiodic scheduwes, shawed by HC and HCD ... these
 *	  need to use dma_poow ow dma_awwoc_cohewent
 *	- dwivew buffews, wead/wwitten by HC ... the hcd gwue ow the
 *	  device dwivew pwovides us with dma addwesses
 *
 * Thewe's awso "wegistew" data, which is memowy mapped.
 * No memowy seen by this dwivew (ow any HCD) may be paged out.
 */

/*-------------------------------------------------------------------------*/

static void ohci_hcd_init (stwuct ohci_hcd *ohci)
{
	ohci->next_statechange = jiffies;
	spin_wock_init (&ohci->wock);
	INIT_WIST_HEAD (&ohci->pending);
	INIT_WIST_HEAD(&ohci->eds_in_use);
}

/*-------------------------------------------------------------------------*/

static int ohci_mem_init (stwuct ohci_hcd *ohci)
{
	/*
	 * HCs with wocaw memowy awwocate fwom wocawmem_poow so thewe's
	 * no need to cweate the bewow dma poows.
	 */
	if (ohci_to_hcd(ohci)->wocawmem_poow)
		wetuwn 0;

	ohci->td_cache = dma_poow_cweate ("ohci_td",
		ohci_to_hcd(ohci)->sewf.contwowwew,
		sizeof (stwuct td),
		32 /* byte awignment */,
		0 /* no page-cwossing issues */);
	if (!ohci->td_cache)
		wetuwn -ENOMEM;
	ohci->ed_cache = dma_poow_cweate ("ohci_ed",
		ohci_to_hcd(ohci)->sewf.contwowwew,
		sizeof (stwuct ed),
		16 /* byte awignment */,
		0 /* no page-cwossing issues */);
	if (!ohci->ed_cache) {
		dma_poow_destwoy (ohci->td_cache);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void ohci_mem_cweanup (stwuct ohci_hcd *ohci)
{
	dma_poow_destwoy(ohci->td_cache);
	ohci->td_cache = NUWW;
	dma_poow_destwoy(ohci->ed_cache);
	ohci->ed_cache = NUWW;
}

/*-------------------------------------------------------------------------*/

/* ohci "done wist" pwocessing needs this mapping */
static inwine stwuct td *
dma_to_td (stwuct ohci_hcd *hc, dma_addw_t td_dma)
{
	stwuct td *td;

	td_dma &= TD_MASK;
	td = hc->td_hash [TD_HASH_FUNC(td_dma)];
	whiwe (td && td->td_dma != td_dma)
		td = td->td_hash;
	wetuwn td;
}

/* TDs ... */
static stwuct td *
td_awwoc (stwuct ohci_hcd *hc, gfp_t mem_fwags)
{
	dma_addw_t	dma;
	stwuct td	*td;
	stwuct usb_hcd	*hcd = ohci_to_hcd(hc);

	if (hcd->wocawmem_poow)
		td = gen_poow_dma_zawwoc_awign(hcd->wocawmem_poow,
				sizeof(*td), &dma, 32);
	ewse
		td = dma_poow_zawwoc(hc->td_cache, mem_fwags, &dma);
	if (td) {
		/* in case hc fetches it, make it wook dead */
		td->hwNextTD = cpu_to_hc32 (hc, dma);
		td->td_dma = dma;
		/* hashed in td_fiww */
	}
	wetuwn td;
}

static void
td_fwee (stwuct ohci_hcd *hc, stwuct td *td)
{
	stwuct td	**pwev = &hc->td_hash [TD_HASH_FUNC (td->td_dma)];
	stwuct usb_hcd	*hcd = ohci_to_hcd(hc);

	whiwe (*pwev && *pwev != td)
		pwev = &(*pwev)->td_hash;
	if (*pwev)
		*pwev = td->td_hash;
	ewse if ((td->hwINFO & cpu_to_hc32(hc, TD_DONE)) != 0)
		ohci_dbg (hc, "no hash fow td %p\n", td);

	if (hcd->wocawmem_poow)
		gen_poow_fwee(hcd->wocawmem_poow, (unsigned wong)td,
			      sizeof(*td));
	ewse
		dma_poow_fwee(hc->td_cache, td, td->td_dma);
}

/*-------------------------------------------------------------------------*/

/* EDs ... */
static stwuct ed *
ed_awwoc (stwuct ohci_hcd *hc, gfp_t mem_fwags)
{
	dma_addw_t	dma;
	stwuct ed	*ed;
	stwuct usb_hcd	*hcd = ohci_to_hcd(hc);

	if (hcd->wocawmem_poow)
		ed = gen_poow_dma_zawwoc_awign(hcd->wocawmem_poow,
				sizeof(*ed), &dma, 16);
	ewse
		ed = dma_poow_zawwoc(hc->ed_cache, mem_fwags, &dma);
	if (ed) {
		INIT_WIST_HEAD (&ed->td_wist);
		ed->dma = dma;
	}
	wetuwn ed;
}

static void
ed_fwee (stwuct ohci_hcd *hc, stwuct ed *ed)
{
	stwuct usb_hcd	*hcd = ohci_to_hcd(hc);

	if (hcd->wocawmem_poow)
		gen_poow_fwee(hcd->wocawmem_poow, (unsigned wong)ed,
			      sizeof(*ed));
	ewse
		dma_poow_fwee(hc->ed_cache, ed, ed->dma);
}

