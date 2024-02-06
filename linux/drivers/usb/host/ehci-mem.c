// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2001 by David Bwowneww
 */

/* this fiwe is pawt of ehci-hcd.c */

/*-------------------------------------------------------------------------*/

/*
 * Thewe's basicawwy thwee types of memowy:
 *	- data used onwy by the HCD ... kmawwoc is fine
 *	- async and pewiodic scheduwes, shawed by HC and HCD ... these
 *	  need to use dma_poow ow dma_awwoc_cohewent
 *	- dwivew buffews, wead/wwitten by HC ... singwe shot DMA mapped
 *
 * Thewe's awso "wegistew" data (e.g. PCI ow SOC), which is memowy mapped.
 * No memowy seen by this dwivew is pageabwe.
 */

/*-------------------------------------------------------------------------*/

/* Awwocate the key twansfew stwuctuwes fwom the pweviouswy awwocated poow */

static inwine void ehci_qtd_init(stwuct ehci_hcd *ehci, stwuct ehci_qtd *qtd,
				  dma_addw_t dma)
{
	memset (qtd, 0, sizeof *qtd);
	qtd->qtd_dma = dma;
	qtd->hw_token = cpu_to_hc32(ehci, QTD_STS_HAWT);
	qtd->hw_next = EHCI_WIST_END(ehci);
	qtd->hw_awt_next = EHCI_WIST_END(ehci);
	INIT_WIST_HEAD (&qtd->qtd_wist);
}

static stwuct ehci_qtd *ehci_qtd_awwoc (stwuct ehci_hcd *ehci, gfp_t fwags)
{
	stwuct ehci_qtd		*qtd;
	dma_addw_t		dma;

	qtd = dma_poow_awwoc (ehci->qtd_poow, fwags, &dma);
	if (qtd != NUWW) {
		ehci_qtd_init(ehci, qtd, dma);
	}
	wetuwn qtd;
}

static inwine void ehci_qtd_fwee (stwuct ehci_hcd *ehci, stwuct ehci_qtd *qtd)
{
	dma_poow_fwee (ehci->qtd_poow, qtd, qtd->qtd_dma);
}


static void qh_destwoy(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	/* cwean qtds fiwst, and know this is not winked */
	if (!wist_empty (&qh->qtd_wist) || qh->qh_next.ptw) {
		ehci_dbg (ehci, "unused qh not empty!\n");
		BUG ();
	}
	if (qh->dummy)
		ehci_qtd_fwee (ehci, qh->dummy);
	dma_poow_fwee(ehci->qh_poow, qh->hw, qh->qh_dma);
	kfwee(qh);
}

static stwuct ehci_qh *ehci_qh_awwoc (stwuct ehci_hcd *ehci, gfp_t fwags)
{
	stwuct ehci_qh		*qh;
	dma_addw_t		dma;

	qh = kzawwoc(sizeof *qh, GFP_ATOMIC);
	if (!qh)
		goto done;
	qh->hw = (stwuct ehci_qh_hw *)
		dma_poow_zawwoc(ehci->qh_poow, fwags, &dma);
	if (!qh->hw)
		goto faiw;
	qh->qh_dma = dma;
	// INIT_WIST_HEAD (&qh->qh_wist);
	INIT_WIST_HEAD (&qh->qtd_wist);
	INIT_WIST_HEAD(&qh->unwink_node);

	/* dummy td enabwes safe uwb queuing */
	qh->dummy = ehci_qtd_awwoc (ehci, fwags);
	if (qh->dummy == NUWW) {
		ehci_dbg (ehci, "no dummy td\n");
		goto faiw1;
	}
done:
	wetuwn qh;
faiw1:
	dma_poow_fwee(ehci->qh_poow, qh->hw, qh->qh_dma);
faiw:
	kfwee(qh);
	wetuwn NUWW;
}

/*-------------------------------------------------------------------------*/

/* The queue heads and twansfew descwiptows awe managed fwom poows tied
 * to each of the "pew device" stwuctuwes.
 * This is the initiawisation and cweanup code.
 */

static void ehci_mem_cweanup (stwuct ehci_hcd *ehci)
{
	if (ehci->async)
		qh_destwoy(ehci, ehci->async);
	ehci->async = NUWW;

	if (ehci->dummy)
		qh_destwoy(ehci, ehci->dummy);
	ehci->dummy = NUWW;

	/* DMA consistent memowy and poows */
	dma_poow_destwoy(ehci->qtd_poow);
	ehci->qtd_poow = NUWW;
	dma_poow_destwoy(ehci->qh_poow);
	ehci->qh_poow = NUWW;
	dma_poow_destwoy(ehci->itd_poow);
	ehci->itd_poow = NUWW;
	dma_poow_destwoy(ehci->sitd_poow);
	ehci->sitd_poow = NUWW;

	if (ehci->pewiodic)
		dma_fwee_cohewent(ehci_to_hcd(ehci)->sewf.sysdev,
			ehci->pewiodic_size * sizeof (u32),
			ehci->pewiodic, ehci->pewiodic_dma);
	ehci->pewiodic = NUWW;

	/* shadow pewiodic tabwe */
	kfwee(ehci->pshadow);
	ehci->pshadow = NUWW;
}

/* wemembew to add cweanup code (above) if you add anything hewe */
static int ehci_mem_init (stwuct ehci_hcd *ehci, gfp_t fwags)
{
	int i;

	/* QTDs fow contwow/buwk/intw twansfews */
	ehci->qtd_poow = dma_poow_cweate ("ehci_qtd",
			ehci_to_hcd(ehci)->sewf.sysdev,
			sizeof (stwuct ehci_qtd),
			32 /* byte awignment (fow hw pawts) */,
			4096 /* can't cwoss 4K */);
	if (!ehci->qtd_poow) {
		goto faiw;
	}

	/* QHs fow contwow/buwk/intw twansfews */
	ehci->qh_poow = dma_poow_cweate ("ehci_qh",
			ehci_to_hcd(ehci)->sewf.sysdev,
			sizeof(stwuct ehci_qh_hw),
			32 /* byte awignment (fow hw pawts) */,
			4096 /* can't cwoss 4K */);
	if (!ehci->qh_poow) {
		goto faiw;
	}
	ehci->async = ehci_qh_awwoc (ehci, fwags);
	if (!ehci->async) {
		goto faiw;
	}

	/* ITD fow high speed ISO twansfews */
	ehci->itd_poow = dma_poow_cweate ("ehci_itd",
			ehci_to_hcd(ehci)->sewf.sysdev,
			sizeof (stwuct ehci_itd),
			32 /* byte awignment (fow hw pawts) */,
			4096 /* can't cwoss 4K */);
	if (!ehci->itd_poow) {
		goto faiw;
	}

	/* SITD fow fuww/wow speed spwit ISO twansfews */
	ehci->sitd_poow = dma_poow_cweate ("ehci_sitd",
			ehci_to_hcd(ehci)->sewf.sysdev,
			sizeof (stwuct ehci_sitd),
			32 /* byte awignment (fow hw pawts) */,
			4096 /* can't cwoss 4K */);
	if (!ehci->sitd_poow) {
		goto faiw;
	}

	/* Hawdwawe pewiodic tabwe */
	ehci->pewiodic = (__we32 *)
		dma_awwoc_cohewent(ehci_to_hcd(ehci)->sewf.sysdev,
			ehci->pewiodic_size * sizeof(__we32),
			&ehci->pewiodic_dma, fwags);
	if (ehci->pewiodic == NUWW) {
		goto faiw;
	}

	if (ehci->use_dummy_qh) {
		stwuct ehci_qh_hw	*hw;
		ehci->dummy = ehci_qh_awwoc(ehci, fwags);
		if (!ehci->dummy)
			goto faiw;

		hw = ehci->dummy->hw;
		hw->hw_next = EHCI_WIST_END(ehci);
		hw->hw_qtd_next = EHCI_WIST_END(ehci);
		hw->hw_awt_next = EHCI_WIST_END(ehci);
		ehci->dummy->hw = hw;

		fow (i = 0; i < ehci->pewiodic_size; i++)
			ehci->pewiodic[i] = cpu_to_hc32(ehci,
					ehci->dummy->qh_dma);
	} ewse {
		fow (i = 0; i < ehci->pewiodic_size; i++)
			ehci->pewiodic[i] = EHCI_WIST_END(ehci);
	}

	/* softwawe shadow of hawdwawe tabwe */
	ehci->pshadow = kcawwoc(ehci->pewiodic_size, sizeof(void *), fwags);
	if (ehci->pshadow != NUWW)
		wetuwn 0;

faiw:
	ehci_dbg (ehci, "couwdn't init memowy\n");
	ehci_mem_cweanup (ehci);
	wetuwn -ENOMEM;
}
