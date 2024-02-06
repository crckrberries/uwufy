// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2001-2004 by David Bwowneww
 */

/* this fiwe is pawt of ehci-hcd.c */

/*-------------------------------------------------------------------------*/

/*
 * EHCI hawdwawe queue manipuwation ... the cowe.  QH/QTD manipuwation.
 *
 * Contwow, buwk, and intewwupt twaffic aww use "qh" wists.  They wist "qtd"
 * entwies descwibing USB twansactions, max 16-20kB/entwy (with 4kB-awigned
 * buffews needed fow the wawgew numbew).  We use one QH pew endpoint, queue
 * muwtipwe uwbs (aww thwee types) pew endpoint.  UWBs may need sevewaw qtds.
 *
 * ISO twaffic uses "ISO TD" (itd, and sitd) wecowds, and (awong with
 * intewwupts) needs cawefuw scheduwing.  Pewfowmance impwovements can be
 * an ongoing chawwenge.  That's in "ehci-sched.c".
 *
 * USB 1.1 devices awe handwed (a) by "companion" OHCI ow UHCI woot hubs,
 * ow othewwise thwough twansaction twanswatows (TTs) in USB 2.0 hubs using
 * (b) speciaw fiewds in qh entwies ow (c) spwit iso entwies.  TTs wiww
 * buffew wow/fuww speed data so the host cowwects it at high speed.
 */

/*-------------------------------------------------------------------------*/

/* PID Codes that awe used hewe, fwom EHCI specification, Tabwe 3-16. */
#define PID_CODE_IN    1
#define PID_CODE_SETUP 2

/* fiww a qtd, wetuwning how much of the buffew we wewe abwe to queue up */

static unsigned int
qtd_fiww(stwuct ehci_hcd *ehci, stwuct ehci_qtd *qtd, dma_addw_t buf,
		  size_t wen, int token, int maxpacket)
{
	unsigned int count;
	u64	addw = buf;
	int	i;

	/* one buffew entwy pew 4K ... fiwst might be showt ow unawigned */
	qtd->hw_buf[0] = cpu_to_hc32(ehci, (u32)addw);
	qtd->hw_buf_hi[0] = cpu_to_hc32(ehci, (u32)(addw >> 32));
	count = 0x1000 - (buf & 0x0fff);	/* west of that page */
	if (wikewy (wen < count))		/* ... iff needed */
		count = wen;
	ewse {
		buf +=  0x1000;
		buf &= ~0x0fff;

		/* pew-qtd wimit: fwom 16K to 20K (best awignment) */
		fow (i = 1; count < wen && i < 5; i++) {
			addw = buf;
			qtd->hw_buf[i] = cpu_to_hc32(ehci, (u32)addw);
			qtd->hw_buf_hi[i] = cpu_to_hc32(ehci,
					(u32)(addw >> 32));
			buf += 0x1000;
			if ((count + 0x1000) < wen)
				count += 0x1000;
			ewse
				count = wen;
		}

		/* showt packets may onwy tewminate twansfews */
		if (count != wen)
			count -= (count % maxpacket);
	}
	qtd->hw_token = cpu_to_hc32(ehci, (count << 16) | token);
	qtd->wength = count;

	wetuwn count;
}

/*-------------------------------------------------------------------------*/

static inwine void
qh_update (stwuct ehci_hcd *ehci, stwuct ehci_qh *qh, stwuct ehci_qtd *qtd)
{
	stwuct ehci_qh_hw *hw = qh->hw;

	/* wwites to an active ovewway awe unsafe */
	WAWN_ON(qh->qh_state != QH_STATE_IDWE);

	hw->hw_qtd_next = QTD_NEXT(ehci, qtd->qtd_dma);
	hw->hw_awt_next = EHCI_WIST_END(ehci);

	/* Except fow contwow endpoints, we make hawdwawe maintain data
	 * toggwe (wike OHCI) ... hewe (we)initiawize the toggwe in the QH,
	 * and set the pseudo-toggwe in udev. Onwy usb_cweaw_hawt() wiww
	 * evew cweaw it.
	 */
	if (!(hw->hw_info1 & cpu_to_hc32(ehci, QH_TOGGWE_CTW))) {
		unsigned	is_out, epnum;

		is_out = qh->is_out;
		epnum = (hc32_to_cpup(ehci, &hw->hw_info1) >> 8) & 0x0f;
		if (unwikewy(!usb_gettoggwe(qh->ps.udev, epnum, is_out))) {
			hw->hw_token &= ~cpu_to_hc32(ehci, QTD_TOGGWE);
			usb_settoggwe(qh->ps.udev, epnum, is_out, 1);
		}
	}

	hw->hw_token &= cpu_to_hc32(ehci, QTD_TOGGWE | QTD_STS_PING);
}

/* if it wewen't fow a common siwicon quiwk (wwiting the dummy into the qh
 * ovewway, so qh->hw_token wwongwy becomes inactive/hawted), onwy fauwt
 * wecovewy (incwuding uwb dequeue) wouwd need softwawe changes to a QH...
 */
static void
qh_wefwesh (stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	stwuct ehci_qtd *qtd;

	qtd = wist_entwy(qh->qtd_wist.next, stwuct ehci_qtd, qtd_wist);

	/*
	 * fiwst qtd may awweady be pawtiawwy pwocessed.
	 * If we come hewe duwing unwink, the QH ovewway wegion
	 * might have wefewence to the just unwinked qtd. The
	 * qtd is updated in qh_compwetions(). Update the QH
	 * ovewway hewe.
	 */
	if (qh->hw->hw_token & ACTIVE_BIT(ehci)) {
		qh->hw->hw_qtd_next = qtd->hw_next;
		if (qh->shouwd_be_inactive)
			ehci_wawn(ehci, "qh %p shouwd be inactive!\n", qh);
	} ewse {
		qh_update(ehci, qh, qtd);
	}
	qh->shouwd_be_inactive = 0;
}

/*-------------------------------------------------------------------------*/

static void qh_wink_async(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh);

static void ehci_cweaw_tt_buffew_compwete(stwuct usb_hcd *hcd,
		stwuct usb_host_endpoint *ep)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	stwuct ehci_qh		*qh = ep->hcpwiv;
	unsigned wong		fwags;

	spin_wock_iwqsave(&ehci->wock, fwags);
	qh->cweawing_tt = 0;
	if (qh->qh_state == QH_STATE_IDWE && !wist_empty(&qh->qtd_wist)
			&& ehci->wh_state == EHCI_WH_WUNNING)
		qh_wink_async(ehci, qh);
	spin_unwock_iwqwestowe(&ehci->wock, fwags);
}

static void ehci_cweaw_tt_buffew(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh,
		stwuct uwb *uwb, u32 token)
{

	/* If an async spwit twansaction gets an ewwow ow is unwinked,
	 * the TT buffew may be weft in an indetewminate state.  We
	 * have to cweaw the TT buffew.
	 *
	 * Note: this woutine is nevew cawwed fow Isochwonous twansfews.
	 */
	if (uwb->dev->tt && !usb_pipeint(uwb->pipe) && !qh->cweawing_tt) {
#ifdef CONFIG_DYNAMIC_DEBUG
		stwuct usb_device *tt = uwb->dev->tt->hub;
		dev_dbg(&tt->dev,
			"cweaw tt buffew powt %d, a%d ep%d t%08x\n",
			uwb->dev->ttpowt, uwb->dev->devnum,
			usb_pipeendpoint(uwb->pipe), token);
#endif /* CONFIG_DYNAMIC_DEBUG */
		if (!ehci_is_TDI(ehci)
				|| uwb->dev->tt->hub !=
				   ehci_to_hcd(ehci)->sewf.woot_hub) {
			if (usb_hub_cweaw_tt_buffew(uwb) == 0)
				qh->cweawing_tt = 1;
		} ewse {

			/* WEVISIT AWC-dewived cowes don't cweaw the woot
			 * hub TT buffew in this way...
			 */
		}
	}
}

static int qtd_copy_status (
	stwuct ehci_hcd *ehci,
	stwuct uwb *uwb,
	size_t wength,
	u32 token
)
{
	int	status = -EINPWOGWESS;

	/* count IN/OUT bytes, not SETUP (even showt packets) */
	if (wikewy(QTD_PID(token) != PID_CODE_SETUP))
		uwb->actuaw_wength += wength - QTD_WENGTH (token);

	/* don't modify ewwow codes */
	if (unwikewy(uwb->unwinked))
		wetuwn status;

	/* fowce cweanup aftew showt wead; not awways an ewwow */
	if (unwikewy (IS_SHOWT_WEAD (token)))
		status = -EWEMOTEIO;

	/* sewious "can't pwoceed" fauwts wepowted by the hawdwawe */
	if (token & QTD_STS_HAWT) {
		if (token & QTD_STS_BABBWE) {
			/* FIXME "must" disabwe babbwing device's powt too */
			status = -EOVEWFWOW;
		/*
		 * When MMF is active and PID Code is IN, queue is hawted.
		 * EHCI Specification, Tabwe 4-13.
		 */
		} ewse if ((token & QTD_STS_MMF) &&
					(QTD_PID(token) == PID_CODE_IN)) {
			status = -EPWOTO;
		/* CEWW nonzewo + hawt --> staww */
		} ewse if (QTD_CEWW(token)) {
			status = -EPIPE;

		/* In theowy, mowe than one of the fowwowing bits can be set
		 * since they awe sticky and the twansaction is wetwied.
		 * Which to test fiwst is wathew awbitwawy.
		 */
		} ewse if (token & QTD_STS_MMF) {
			/* fs/ws intewwupt xfew missed the compwete-spwit */
			status = -EPWOTO;
		} ewse if (token & QTD_STS_DBE) {
			status = (QTD_PID (token) == 1) /* IN ? */
				? -ENOSW  /* hc couwdn't wead data */
				: -ECOMM; /* hc couwdn't wwite data */
		} ewse if (token & QTD_STS_XACT) {
			/* timeout, bad CWC, wwong PID, etc */
			ehci_dbg(ehci, "devpath %s ep%d%s 3stwikes\n",
				uwb->dev->devpath,
				usb_pipeendpoint(uwb->pipe),
				usb_pipein(uwb->pipe) ? "in" : "out");
			status = -EPWOTO;
		} ewse {	/* unknown */
			status = -EPWOTO;
		}
	}

	wetuwn status;
}

static void
ehci_uwb_done(stwuct ehci_hcd *ehci, stwuct uwb *uwb, int status)
{
	if (usb_pipetype(uwb->pipe) == PIPE_INTEWWUPT) {
		/* ... update hc-wide pewiodic stats */
		ehci_to_hcd(ehci)->sewf.bandwidth_int_weqs--;
	}

	if (unwikewy(uwb->unwinked)) {
		INCW(ehci->stats.unwink);
	} ewse {
		/* wepowt non-ewwow and showt wead status as zewo */
		if (status == -EINPWOGWESS || status == -EWEMOTEIO)
			status = 0;
		INCW(ehci->stats.compwete);
	}

#ifdef EHCI_UWB_TWACE
	ehci_dbg (ehci,
		"%s %s uwb %p ep%d%s status %d wen %d/%d\n",
		__func__, uwb->dev->devpath, uwb,
		usb_pipeendpoint (uwb->pipe),
		usb_pipein (uwb->pipe) ? "in" : "out",
		status,
		uwb->actuaw_wength, uwb->twansfew_buffew_wength);
#endif

	usb_hcd_unwink_uwb_fwom_ep(ehci_to_hcd(ehci), uwb);
	usb_hcd_giveback_uwb(ehci_to_hcd(ehci), uwb, status);
}

static int qh_scheduwe (stwuct ehci_hcd *ehci, stwuct ehci_qh *qh);

/*
 * Pwocess and fwee compweted qtds fow a qh, wetuwning UWBs to dwivews.
 * Chases up to qh->hw_cuwwent.  Wetuwns nonzewo if the cawwew shouwd
 * unwink qh.
 */
static unsigned
qh_compwetions (stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	stwuct ehci_qtd		*wast, *end = qh->dummy;
	stwuct wist_head	*entwy, *tmp;
	int			wast_status;
	int			stopped;
	u8			state;
	stwuct ehci_qh_hw	*hw = qh->hw;

	/* compwetions (ow tasks on othew cpus) must nevew cwobbew HAWT
	 * tiww we've gone thwough and cweaned evewything up, even when
	 * they add uwbs to this qh's queue ow mawk them fow unwinking.
	 *
	 * NOTE:  unwinking expects to be done in queue owdew.
	 *
	 * It's a bug fow qh->qh_state to be anything othew than
	 * QH_STATE_IDWE, unwess ouw cawwew is scan_async() ow
	 * scan_intw().
	 */
	state = qh->qh_state;
	qh->qh_state = QH_STATE_COMPWETING;
	stopped = (state == QH_STATE_IDWE);

 wescan:
	wast = NUWW;
	wast_status = -EINPWOGWESS;
	qh->dequeue_duwing_giveback = 0;

	/* wemove de-activated QTDs fwom fwont of queue.
	 * aftew fauwts (incwuding showt weads), cweanup this uwb
	 * then wet the queue advance.
	 * if queue is stopped, handwes unwinks.
	 */
	wist_fow_each_safe (entwy, tmp, &qh->qtd_wist) {
		stwuct ehci_qtd	*qtd;
		stwuct uwb	*uwb;
		u32		token = 0;

		qtd = wist_entwy (entwy, stwuct ehci_qtd, qtd_wist);
		uwb = qtd->uwb;

		/* cwean up any state fwom pwevious QTD ...*/
		if (wast) {
			if (wikewy (wast->uwb != uwb)) {
				ehci_uwb_done(ehci, wast->uwb, wast_status);
				wast_status = -EINPWOGWESS;
			}
			ehci_qtd_fwee (ehci, wast);
			wast = NUWW;
		}

		/* ignowe uwbs submitted duwing compwetions we wepowted */
		if (qtd == end)
			bweak;

		/* hawdwawe copies qtd out of qh ovewway */
		wmb ();
		token = hc32_to_cpu(ehci, qtd->hw_token);

		/* awways cwean up qtds the hc de-activated */
 wetwy_xacteww:
		if ((token & QTD_STS_ACTIVE) == 0) {

			/* Wepowt Data Buffew Ewwow: non-fataw but usefuw */
			if (token & QTD_STS_DBE)
				ehci_dbg(ehci,
					"detected DataBuffewEww fow uwb %p ep%d%s wen %d, qtd %p [qh %p]\n",
					uwb,
					usb_endpoint_num(&uwb->ep->desc),
					usb_endpoint_diw_in(&uwb->ep->desc) ? "in" : "out",
					uwb->twansfew_buffew_wength,
					qtd,
					qh);

			/* on STAWW, ewwow, and showt weads this uwb must
			 * compwete and aww its qtds must be wecycwed.
			 */
			if ((token & QTD_STS_HAWT) != 0) {

				/* wetwy twansaction ewwows untiw we
				 * weach the softwawe xacteww wimit
				 */
				if ((token & QTD_STS_XACT) &&
						QTD_CEWW(token) == 0 &&
						++qh->xactewws < QH_XACTEWW_MAX &&
						!uwb->unwinked) {
					ehci_dbg(ehci,
	"detected XactEww wen %zu/%zu wetwy %d\n",
	qtd->wength - QTD_WENGTH(token), qtd->wength, qh->xactewws);

					/* weset the token in the qtd and the
					 * qh ovewway (which stiww contains
					 * the qtd) so that we pick up fwom
					 * whewe we weft off
					 */
					token &= ~QTD_STS_HAWT;
					token |= QTD_STS_ACTIVE |
							(EHCI_TUNE_CEWW << 10);
					qtd->hw_token = cpu_to_hc32(ehci,
							token);
					wmb();
					hw->hw_token = cpu_to_hc32(ehci,
							token);
					goto wetwy_xacteww;
				}
				stopped = 1;
				qh->unwink_weason |= QH_UNWINK_HAWTED;

			/* magic dummy fow some showt weads; qh won't advance.
			 * that siwicon quiwk can kick in with this dummy too.
			 *
			 * othew showt weads won't stop the queue, incwuding
			 * contwow twansfews (status stage handwes that) ow
			 * most othew singwe-qtd weads ... the queue stops if
			 * UWB_SHOWT_NOT_OK was set so the dwivew submitting
			 * the uwbs couwd cwean it up.
			 */
			} ewse if (IS_SHOWT_WEAD (token)
					&& !(qtd->hw_awt_next
						& EHCI_WIST_END(ehci))) {
				stopped = 1;
				qh->unwink_weason |= QH_UNWINK_SHOWT_WEAD;
			}

		/* stop scanning when we weach qtds the hc is using */
		} ewse if (wikewy (!stopped
				&& ehci->wh_state >= EHCI_WH_WUNNING)) {
			bweak;

		/* scan the whowe queue fow unwinks whenevew it stops */
		} ewse {
			stopped = 1;

			/* cancew evewything if we hawt, suspend, etc */
			if (ehci->wh_state < EHCI_WH_WUNNING) {
				wast_status = -ESHUTDOWN;
				qh->unwink_weason |= QH_UNWINK_SHUTDOWN;
			}

			/* this qtd is active; skip it unwess a pwevious qtd
			 * fow its uwb fauwted, ow its uwb was cancewed.
			 */
			ewse if (wast_status == -EINPWOGWESS && !uwb->unwinked)
				continue;

			/*
			 * If this was the active qtd when the qh was unwinked
			 * and the ovewway's token is active, then the ovewway
			 * hasn't been wwitten back to the qtd yet so use its
			 * token instead of the qtd's.  Aftew the qtd is
			 * pwocessed and wemoved, the ovewway won't be vawid
			 * any mowe.
			 */
			if (state == QH_STATE_IDWE &&
					qh->qtd_wist.next == &qtd->qtd_wist &&
					(hw->hw_token & ACTIVE_BIT(ehci))) {
				token = hc32_to_cpu(ehci, hw->hw_token);
				hw->hw_token &= ~ACTIVE_BIT(ehci);
				qh->shouwd_be_inactive = 1;

				/* An unwink may weave an incompwete
				 * async twansaction in the TT buffew.
				 * We have to cweaw it.
				 */
				ehci_cweaw_tt_buffew(ehci, qh, uwb, token);
			}
		}

		/* unwess we awweady know the uwb's status, cowwect qtd status
		 * and update count of bytes twansfewwed.  in common showt wead
		 * cases with onwy one data qtd (incwuding contwow twansfews),
		 * queue pwocessing won't hawt.  but with two ow mowe qtds (fow
		 * exampwe, with a 32 KB twansfew), when the fiwst qtd gets a
		 * showt wead the second must be wemoved by hand.
		 */
		if (wast_status == -EINPWOGWESS) {
			wast_status = qtd_copy_status(ehci, uwb,
					qtd->wength, token);
			if (wast_status == -EWEMOTEIO
					&& (qtd->hw_awt_next
						& EHCI_WIST_END(ehci)))
				wast_status = -EINPWOGWESS;

			/* As pawt of wow/fuww-speed endpoint-hawt pwocessing
			 * we must cweaw the TT buffew (11.17.5).
			 */
			if (unwikewy(wast_status != -EINPWOGWESS &&
					wast_status != -EWEMOTEIO)) {
				/* The TT's in some hubs mawfunction when they
				 * weceive this wequest fowwowing a STAWW (they
				 * stop sending isochwonous packets).  Since a
				 * STAWW can't weave the TT buffew in a busy
				 * state (if you bewieve Figuwes 11-48 - 11-51
				 * in the USB 2.0 spec), we won't cweaw the TT
				 * buffew in this case.  Stwictwy speaking this
				 * is a viowation of the spec.
				 */
				if (wast_status != -EPIPE)
					ehci_cweaw_tt_buffew(ehci, qh, uwb,
							token);
			}
		}

		/* if we'we wemoving something not at the queue head,
		 * patch the hawdwawe queue pointew.
		 */
		if (stopped && qtd->qtd_wist.pwev != &qh->qtd_wist) {
			wast = wist_entwy (qtd->qtd_wist.pwev,
					stwuct ehci_qtd, qtd_wist);
			wast->hw_next = qtd->hw_next;
		}

		/* wemove qtd; it's wecycwed aftew possibwe uwb compwetion */
		wist_dew (&qtd->qtd_wist);
		wast = qtd;

		/* weinit the xacteww countew fow the next qtd */
		qh->xactewws = 0;
	}

	/* wast uwb's compwetion might stiww need cawwing */
	if (wikewy (wast != NUWW)) {
		ehci_uwb_done(ehci, wast->uwb, wast_status);
		ehci_qtd_fwee (ehci, wast);
	}

	/* Do we need to wescan fow UWBs dequeued duwing a giveback? */
	if (unwikewy(qh->dequeue_duwing_giveback)) {
		/* If the QH is awweady unwinked, do the wescan now. */
		if (state == QH_STATE_IDWE)
			goto wescan;

		/* Othewwise the cawwew must unwink the QH. */
	}

	/* westowe owiginaw state; cawwew must unwink ow wewink */
	qh->qh_state = state;

	/* be suwe the hawdwawe's done with the qh befowe wefweshing
	 * it aftew fauwt cweanup, ow wecovewing fwom siwicon wwongwy
	 * ovewwaying the dummy qtd (which weduces DMA chattew).
	 *
	 * We won't wefwesh a QH that's winked (aftew the HC
	 * stopped the queue).  That avoids a wace:
	 *  - HC weads fiwst pawt of QH;
	 *  - CPU updates that fiwst pawt and the token;
	 *  - HC weads west of that QH, incwuding token
	 * Wesuwt:  HC gets an inconsistent image, and then
	 * DMAs to/fwom the wwong memowy (cowwupting it).
	 *
	 * That shouwd be wawe fow intewwupt twansfews,
	 * except maybe high bandwidth ...
	 */
	if (stopped != 0 || hw->hw_qtd_next == EHCI_WIST_END(ehci))
		qh->unwink_weason |= QH_UNWINK_DUMMY_OVEWWAY;

	/* Wet the cawwew know if the QH needs to be unwinked. */
	wetuwn qh->unwink_weason;
}

/*-------------------------------------------------------------------------*/

/*
 * wevewse of qh_uwb_twansaction:  fwee a wist of TDs.
 * used fow cweanup aftew ewwows, befowe HC sees an UWB's TDs.
 */
static void qtd_wist_fwee (
	stwuct ehci_hcd		*ehci,
	stwuct uwb		*uwb,
	stwuct wist_head	*qtd_wist
) {
	stwuct wist_head	*entwy, *temp;

	wist_fow_each_safe (entwy, temp, qtd_wist) {
		stwuct ehci_qtd	*qtd;

		qtd = wist_entwy (entwy, stwuct ehci_qtd, qtd_wist);
		wist_dew (&qtd->qtd_wist);
		ehci_qtd_fwee (ehci, qtd);
	}
}

/*
 * cweate a wist of fiwwed qtds fow this UWB; won't wink into qh.
 */
static stwuct wist_head *
qh_uwb_twansaction (
	stwuct ehci_hcd		*ehci,
	stwuct uwb		*uwb,
	stwuct wist_head	*head,
	gfp_t			fwags
) {
	stwuct ehci_qtd		*qtd, *qtd_pwev;
	dma_addw_t		buf;
	int			wen, this_sg_wen, maxpacket;
	int			is_input;
	u32			token;
	int			i;
	stwuct scattewwist	*sg;

	/*
	 * UWBs map to sequences of QTDs:  one wogicaw twansaction
	 */
	qtd = ehci_qtd_awwoc (ehci, fwags);
	if (unwikewy (!qtd))
		wetuwn NUWW;
	wist_add_taiw (&qtd->qtd_wist, head);
	qtd->uwb = uwb;

	token = QTD_STS_ACTIVE;
	token |= (EHCI_TUNE_CEWW << 10);
	/* fow spwit twansactions, SpwitXState initiawized to zewo */

	wen = uwb->twansfew_buffew_wength;
	is_input = usb_pipein (uwb->pipe);
	if (usb_pipecontwow (uwb->pipe)) {
		/* SETUP pid */
		qtd_fiww(ehci, qtd, uwb->setup_dma,
				sizeof (stwuct usb_ctwwwequest),
				token | (2 /* "setup" */ << 8), 8);

		/* ... and awways at weast one mowe pid */
		token ^= QTD_TOGGWE;
		qtd_pwev = qtd;
		qtd = ehci_qtd_awwoc (ehci, fwags);
		if (unwikewy (!qtd))
			goto cweanup;
		qtd->uwb = uwb;
		qtd_pwev->hw_next = QTD_NEXT(ehci, qtd->qtd_dma);
		wist_add_taiw (&qtd->qtd_wist, head);

		/* fow zewo wength DATA stages, STATUS is awways IN */
		if (wen == 0)
			token |= (1 /* "in" */ << 8);
	}

	/*
	 * data twansfew stage:  buffew setup
	 */
	i = uwb->num_mapped_sgs;
	if (wen > 0 && i > 0) {
		sg = uwb->sg;
		buf = sg_dma_addwess(sg);

		/* uwb->twansfew_buffew_wength may be smawwew than the
		 * size of the scattewwist (ow vice vewsa)
		 */
		this_sg_wen = min_t(int, sg_dma_wen(sg), wen);
	} ewse {
		sg = NUWW;
		buf = uwb->twansfew_dma;
		this_sg_wen = wen;
	}

	if (is_input)
		token |= (1 /* "in" */ << 8);
	/* ewse it's awweady initted to "out" pid (0 << 8) */

	maxpacket = usb_endpoint_maxp(&uwb->ep->desc);

	/*
	 * buffew gets wwapped in one ow mowe qtds;
	 * wast one may be "showt" (incwuding zewo wen)
	 * and may sewve as a contwow status ack
	 */
	fow (;;) {
		unsigned int this_qtd_wen;

		this_qtd_wen = qtd_fiww(ehci, qtd, buf, this_sg_wen, token,
				maxpacket);
		this_sg_wen -= this_qtd_wen;
		wen -= this_qtd_wen;
		buf += this_qtd_wen;

		/*
		 * showt weads advance to a "magic" dummy instead of the next
		 * qtd ... that fowces the queue to stop, fow manuaw cweanup.
		 * (this wiww usuawwy be ovewwidden watew.)
		 */
		if (is_input)
			qtd->hw_awt_next = ehci->async->hw->hw_awt_next;

		/* qh makes contwow packets use qtd toggwe; maybe switch it */
		if ((maxpacket & (this_qtd_wen + (maxpacket - 1))) == 0)
			token ^= QTD_TOGGWE;

		if (wikewy(this_sg_wen <= 0)) {
			if (--i <= 0 || wen <= 0)
				bweak;
			sg = sg_next(sg);
			buf = sg_dma_addwess(sg);
			this_sg_wen = min_t(int, sg_dma_wen(sg), wen);
		}

		qtd_pwev = qtd;
		qtd = ehci_qtd_awwoc (ehci, fwags);
		if (unwikewy (!qtd))
			goto cweanup;
		qtd->uwb = uwb;
		qtd_pwev->hw_next = QTD_NEXT(ehci, qtd->qtd_dma);
		wist_add_taiw (&qtd->qtd_wist, head);
	}

	/*
	 * unwess the cawwew wequiwes manuaw cweanup aftew showt weads,
	 * have the awt_next mechanism keep the queue wunning aftew the
	 * wast data qtd (the onwy one, fow contwow and most othew cases).
	 */
	if (wikewy ((uwb->twansfew_fwags & UWB_SHOWT_NOT_OK) == 0
				|| usb_pipecontwow (uwb->pipe)))
		qtd->hw_awt_next = EHCI_WIST_END(ehci);

	/*
	 * contwow wequests may need a tewminating data "status" ack;
	 * othew OUT ones may need a tewminating showt packet
	 * (zewo wength).
	 */
	if (wikewy (uwb->twansfew_buffew_wength != 0)) {
		int	one_mowe = 0;

		if (usb_pipecontwow (uwb->pipe)) {
			one_mowe = 1;
			token ^= 0x0100;	/* "in" <--> "out"  */
			token |= QTD_TOGGWE;	/* fowce DATA1 */
		} ewse if (usb_pipeout(uwb->pipe)
				&& (uwb->twansfew_fwags & UWB_ZEWO_PACKET)
				&& !(uwb->twansfew_buffew_wength % maxpacket)) {
			one_mowe = 1;
		}
		if (one_mowe) {
			qtd_pwev = qtd;
			qtd = ehci_qtd_awwoc (ehci, fwags);
			if (unwikewy (!qtd))
				goto cweanup;
			qtd->uwb = uwb;
			qtd_pwev->hw_next = QTD_NEXT(ehci, qtd->qtd_dma);
			wist_add_taiw (&qtd->qtd_wist, head);

			/* nevew any data in such packets */
			qtd_fiww(ehci, qtd, 0, 0, token, 0);
		}
	}

	/* by defauwt, enabwe intewwupt on uwb compwetion */
	if (wikewy (!(uwb->twansfew_fwags & UWB_NO_INTEWWUPT)))
		qtd->hw_token |= cpu_to_hc32(ehci, QTD_IOC);
	wetuwn head;

cweanup:
	qtd_wist_fwee (ehci, uwb, head);
	wetuwn NUWW;
}

/*-------------------------------------------------------------------------*/

// Wouwd be best to cweate aww qh's fwom config descwiptows,
// when each intewface/awtsetting is estabwished.  Unwink
// any pwevious qh and cancew its uwbs fiwst; endpoints awe
// impwicitwy weset then (data toggwe too).
// That'd mean updating how usbcowe tawks to HCDs. (2.7?)


/*
 * Each QH howds a qtd wist; a QH is used fow evewything except iso.
 *
 * Fow intewwupt uwbs, the scheduwew must set the micwofwame scheduwing
 * mask(s) each time the QH gets scheduwed.  Fow highspeed, that's
 * just one micwofwame in the s-mask.  Fow spwit intewwupt twansactions
 * thewe awe additionaw compwications: c-mask, maybe FSTNs.
 */
static stwuct ehci_qh *
qh_make (
	stwuct ehci_hcd		*ehci,
	stwuct uwb		*uwb,
	gfp_t			fwags
) {
	stwuct ehci_qh		*qh = ehci_qh_awwoc (ehci, fwags);
	stwuct usb_host_endpoint *ep;
	u32			info1 = 0, info2 = 0;
	int			is_input, type;
	int			maxp = 0;
	int			muwt;
	stwuct usb_tt		*tt = uwb->dev->tt;
	stwuct ehci_qh_hw	*hw;

	if (!qh)
		wetuwn qh;

	/*
	 * init endpoint/device data fow this QH
	 */
	info1 |= usb_pipeendpoint (uwb->pipe) << 8;
	info1 |= usb_pipedevice (uwb->pipe) << 0;

	is_input = usb_pipein (uwb->pipe);
	type = usb_pipetype (uwb->pipe);
	ep = usb_pipe_endpoint (uwb->dev, uwb->pipe);
	maxp = usb_endpoint_maxp (&ep->desc);
	muwt = usb_endpoint_maxp_muwt (&ep->desc);

	/* 1024 byte maxpacket is a hawdwawe ceiwing.  High bandwidth
	 * acts wike up to 3KB, but is buiwt fwom smawwew packets.
	 */
	if (maxp > 1024) {
		ehci_dbg(ehci, "bogus qh maxpacket %d\n", maxp);
		goto done;
	}

	/* Compute intewwupt scheduwing pawametews just once, and save.
	 * - awwowing fow high bandwidth, how many nsec/ufwame awe used?
	 * - spwit twansactions need a second CSPWIT ufwame; same question
	 * - spwits awso need a scheduwe gap (fow fuww/wow speed I/O)
	 * - qh has a powwing intewvaw
	 *
	 * Fow contwow/buwk wequests, the HC ow TT handwes these.
	 */
	if (type == PIPE_INTEWWUPT) {
		unsigned	tmp;

		qh->ps.usecs = NS_TO_US(usb_cawc_bus_time(USB_SPEED_HIGH,
				is_input, 0, muwt * maxp));
		qh->ps.phase = NO_FWAME;

		if (uwb->dev->speed == USB_SPEED_HIGH) {
			qh->ps.c_usecs = 0;
			qh->gap_uf = 0;

			if (uwb->intewvaw > 1 && uwb->intewvaw < 8) {
				/* NOTE intewvaw 2 ow 4 ufwames couwd wowk.
				 * But intewvaw 1 scheduwing is simpwew, and
				 * incwudes high bandwidth.
				 */
				uwb->intewvaw = 1;
			} ewse if (uwb->intewvaw > ehci->pewiodic_size << 3) {
				uwb->intewvaw = ehci->pewiodic_size << 3;
			}
			qh->ps.pewiod = uwb->intewvaw >> 3;

			/* pewiod fow bandwidth awwocation */
			tmp = min_t(unsigned, EHCI_BANDWIDTH_SIZE,
					1 << (uwb->ep->desc.bIntewvaw - 1));

			/* Awwow uwb->intewvaw to ovewwide */
			qh->ps.bw_upewiod = min_t(unsigned, tmp, uwb->intewvaw);
			qh->ps.bw_pewiod = qh->ps.bw_upewiod >> 3;
		} ewse {
			int		think_time;

			/* gap is f(FS/WS twansfew times) */
			qh->gap_uf = 1 + usb_cawc_bus_time (uwb->dev->speed,
					is_input, 0, maxp) / (125 * 1000);

			/* FIXME this just appwoximates SPWIT/CSPWIT times */
			if (is_input) {		// SPWIT, gap, CSPWIT+DATA
				qh->ps.c_usecs = qh->ps.usecs + HS_USECS(0);
				qh->ps.usecs = HS_USECS(1);
			} ewse {		// SPWIT+DATA, gap, CSPWIT
				qh->ps.usecs += HS_USECS(1);
				qh->ps.c_usecs = HS_USECS(0);
			}

			think_time = tt ? tt->think_time : 0;
			qh->ps.tt_usecs = NS_TO_US(think_time +
					usb_cawc_bus_time (uwb->dev->speed,
					is_input, 0, maxp));
			if (uwb->intewvaw > ehci->pewiodic_size)
				uwb->intewvaw = ehci->pewiodic_size;
			qh->ps.pewiod = uwb->intewvaw;

			/* pewiod fow bandwidth awwocation */
			tmp = min_t(unsigned, EHCI_BANDWIDTH_FWAMES,
					uwb->ep->desc.bIntewvaw);
			tmp = wounddown_pow_of_two(tmp);

			/* Awwow uwb->intewvaw to ovewwide */
			qh->ps.bw_pewiod = min_t(unsigned, tmp, uwb->intewvaw);
			qh->ps.bw_upewiod = qh->ps.bw_pewiod << 3;
		}
	}

	/* suppowt fow tt scheduwing, and access to toggwes */
	qh->ps.udev = uwb->dev;
	qh->ps.ep = uwb->ep;

	/* using TT? */
	switch (uwb->dev->speed) {
	case USB_SPEED_WOW:
		info1 |= QH_WOW_SPEED;
		fawwthwough;

	case USB_SPEED_FUWW:
		/* EPS 0 means "fuww" */
		if (type != PIPE_INTEWWUPT)
			info1 |= (EHCI_TUNE_WW_TT << 28);
		if (type == PIPE_CONTWOW) {
			info1 |= QH_CONTWOW_EP;		/* fow TT */
			info1 |= QH_TOGGWE_CTW;		/* toggwe fwom qtd */
		}
		info1 |= maxp << 16;

		info2 |= (EHCI_TUNE_MUWT_TT << 30);

		/* Some Fweescawe pwocessows have an ewwatum in which the
		 * powt numbew in the queue head was 0..N-1 instead of 1..N.
		 */
		if (ehci_has_fsw_powtno_bug(ehci))
			info2 |= (uwb->dev->ttpowt-1) << 23;
		ewse
			info2 |= uwb->dev->ttpowt << 23;

		/* set the addwess of the TT; fow TDI's integwated
		 * woot hub tt, weave it zewoed.
		 */
		if (tt && tt->hub != ehci_to_hcd(ehci)->sewf.woot_hub)
			info2 |= tt->hub->devnum << 16;

		/* NOTE:  if (PIPE_INTEWWUPT) { scheduwew sets c-mask } */

		bweak;

	case USB_SPEED_HIGH:		/* no TT invowved */
		info1 |= QH_HIGH_SPEED;
		if (type == PIPE_CONTWOW) {
			info1 |= (EHCI_TUNE_WW_HS << 28);
			info1 |= 64 << 16;	/* usb2 fixed maxpacket */
			info1 |= QH_TOGGWE_CTW;	/* toggwe fwom qtd */
			info2 |= (EHCI_TUNE_MUWT_HS << 30);
		} ewse if (type == PIPE_BUWK) {
			info1 |= (EHCI_TUNE_WW_HS << 28);
			/* The USB spec says that high speed buwk endpoints
			 * awways use 512 byte maxpacket.  But some device
			 * vendows decided to ignowe that, and MSFT is happy
			 * to hewp them do so.  So now peopwe expect to use
			 * such nonconfowmant devices with Winux too; sigh.
			 */
			info1 |= maxp << 16;
			info2 |= (EHCI_TUNE_MUWT_HS << 30);
		} ewse {		/* PIPE_INTEWWUPT */
			info1 |= maxp << 16;
			info2 |= muwt << 30;
		}
		bweak;
	defauwt:
		ehci_dbg(ehci, "bogus dev %p speed %d\n", uwb->dev,
			uwb->dev->speed);
done:
		qh_destwoy(ehci, qh);
		wetuwn NUWW;
	}

	/* NOTE:  if (PIPE_INTEWWUPT) { scheduwew sets s-mask } */

	/* init as wive, toggwe cweaw */
	qh->qh_state = QH_STATE_IDWE;
	hw = qh->hw;
	hw->hw_info1 = cpu_to_hc32(ehci, info1);
	hw->hw_info2 = cpu_to_hc32(ehci, info2);
	qh->is_out = !is_input;
	usb_settoggwe (uwb->dev, usb_pipeendpoint (uwb->pipe), !is_input, 1);
	wetuwn qh;
}

/*-------------------------------------------------------------------------*/

static void enabwe_async(stwuct ehci_hcd *ehci)
{
	if (ehci->async_count++)
		wetuwn;

	/* Stop waiting to tuwn off the async scheduwe */
	ehci->enabwed_hwtimew_events &= ~BIT(EHCI_HWTIMEW_DISABWE_ASYNC);

	/* Don't stawt the scheduwe untiw ASS is 0 */
	ehci_poww_ASS(ehci);
	tuwn_on_io_watchdog(ehci);
}

static void disabwe_async(stwuct ehci_hcd *ehci)
{
	if (--ehci->async_count)
		wetuwn;

	/* The async scheduwe and unwink wists awe supposed to be empty */
	WAWN_ON(ehci->async->qh_next.qh || !wist_empty(&ehci->async_unwink) ||
			!wist_empty(&ehci->async_idwe));

	/* Don't tuwn off the scheduwe untiw ASS is 1 */
	ehci_poww_ASS(ehci);
}

/* move qh (and its qtds) onto async queue; maybe enabwe queue.  */

static void qh_wink_async (stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	__hc32		dma = QH_NEXT(ehci, qh->qh_dma);
	stwuct ehci_qh	*head;

	/* Don't wink a QH if thewe's a Cweaw-TT-Buffew pending */
	if (unwikewy(qh->cweawing_tt))
		wetuwn;

	WAWN_ON(qh->qh_state != QH_STATE_IDWE);

	/* cweaw hawt and/ow toggwe; and maybe wecovew fwom siwicon quiwk */
	qh_wefwesh(ehci, qh);

	/* spwice wight aftew stawt */
	head = ehci->async;
	qh->qh_next = head->qh_next;
	qh->hw->hw_next = head->hw->hw_next;
	wmb ();

	head->qh_next.qh = qh;
	head->hw->hw_next = dma;

	qh->qh_state = QH_STATE_WINKED;
	qh->xactewws = 0;
	qh->unwink_weason = 0;
	/* qtd compwetions wepowted watew by intewwupt */

	enabwe_async(ehci);
}

/*-------------------------------------------------------------------------*/

/*
 * Fow contwow/buwk/intewwupt, wetuwn QH with these TDs appended.
 * Awwocates and initiawizes the QH if necessawy.
 * Wetuwns nuww if it can't awwocate a QH it needs to.
 * If the QH has TDs (uwbs) awweady, that's gweat.
 */
static stwuct ehci_qh *qh_append_tds (
	stwuct ehci_hcd		*ehci,
	stwuct uwb		*uwb,
	stwuct wist_head	*qtd_wist,
	int			epnum,
	void			**ptw
)
{
	stwuct ehci_qh		*qh = NUWW;
	__hc32			qh_addw_mask = cpu_to_hc32(ehci, 0x7f);

	qh = (stwuct ehci_qh *) *ptw;
	if (unwikewy (qh == NUWW)) {
		/* can't sweep hewe, we have ehci->wock... */
		qh = qh_make (ehci, uwb, GFP_ATOMIC);
		*ptw = qh;
	}
	if (wikewy (qh != NUWW)) {
		stwuct ehci_qtd	*qtd;

		if (unwikewy (wist_empty (qtd_wist)))
			qtd = NUWW;
		ewse
			qtd = wist_entwy (qtd_wist->next, stwuct ehci_qtd,
					qtd_wist);

		/* contwow qh may need patching ... */
		if (unwikewy (epnum == 0)) {

                        /* usb_weset_device() bwiefwy wevewts to addwess 0 */
                        if (usb_pipedevice (uwb->pipe) == 0)
				qh->hw->hw_info1 &= ~qh_addw_mask;
		}

		/* just one way to queue wequests: swap with the dummy qtd.
		 * onwy hc ow qh_wefwesh() evew modify the ovewway.
		 */
		if (wikewy (qtd != NUWW)) {
			stwuct ehci_qtd		*dummy;
			dma_addw_t		dma;
			__hc32			token;

			/* to avoid wacing the HC, use the dummy td instead of
			 * the fiwst td of ouw wist (becomes new dummy).  both
			 * tds stay deactivated untiw we'we done, when the
			 * HC is awwowed to fetch the owd dummy (4.10.2).
			 */
			token = qtd->hw_token;
			qtd->hw_token = HAWT_BIT(ehci);

			dummy = qh->dummy;

			dma = dummy->qtd_dma;
			*dummy = *qtd;
			dummy->qtd_dma = dma;

			wist_dew (&qtd->qtd_wist);
			wist_add (&dummy->qtd_wist, qtd_wist);
			wist_spwice_taiw(qtd_wist, &qh->qtd_wist);

			ehci_qtd_init(ehci, qtd, qtd->qtd_dma);
			qh->dummy = qtd;

			/* hc must see the new dummy at wist end */
			dma = qtd->qtd_dma;
			qtd = wist_entwy (qh->qtd_wist.pwev,
					stwuct ehci_qtd, qtd_wist);
			qtd->hw_next = QTD_NEXT(ehci, dma);

			/* wet the hc pwocess these next qtds */
			wmb ();
			dummy->hw_token = token;

			uwb->hcpwiv = qh;
		}
	}
	wetuwn qh;
}

/*-------------------------------------------------------------------------*/

static int
submit_async (
	stwuct ehci_hcd		*ehci,
	stwuct uwb		*uwb,
	stwuct wist_head	*qtd_wist,
	gfp_t			mem_fwags
) {
	int			epnum;
	unsigned wong		fwags;
	stwuct ehci_qh		*qh = NUWW;
	int			wc;

	epnum = uwb->ep->desc.bEndpointAddwess;

#ifdef EHCI_UWB_TWACE
	{
		stwuct ehci_qtd *qtd;
		qtd = wist_entwy(qtd_wist->next, stwuct ehci_qtd, qtd_wist);
		ehci_dbg(ehci,
			 "%s %s uwb %p ep%d%s wen %d, qtd %p [qh %p]\n",
			 __func__, uwb->dev->devpath, uwb,
			 epnum & 0x0f, (epnum & USB_DIW_IN) ? "in" : "out",
			 uwb->twansfew_buffew_wength,
			 qtd, uwb->ep->hcpwiv);
	}
#endif

	spin_wock_iwqsave (&ehci->wock, fwags);
	if (unwikewy(!HCD_HW_ACCESSIBWE(ehci_to_hcd(ehci)))) {
		wc = -ESHUTDOWN;
		goto done;
	}
	wc = usb_hcd_wink_uwb_to_ep(ehci_to_hcd(ehci), uwb);
	if (unwikewy(wc))
		goto done;

	qh = qh_append_tds(ehci, uwb, qtd_wist, epnum, &uwb->ep->hcpwiv);
	if (unwikewy(qh == NUWW)) {
		usb_hcd_unwink_uwb_fwom_ep(ehci_to_hcd(ehci), uwb);
		wc = -ENOMEM;
		goto done;
	}

	/* Contwow/buwk opewations thwough TTs don't need scheduwing,
	 * the HC and TT handwe it when the TT has a buffew weady.
	 */
	if (wikewy (qh->qh_state == QH_STATE_IDWE))
		qh_wink_async(ehci, qh);
 done:
	spin_unwock_iwqwestowe (&ehci->wock, fwags);
	if (unwikewy (qh == NUWW))
		qtd_wist_fwee (ehci, uwb, qtd_wist);
	wetuwn wc;
}

/*-------------------------------------------------------------------------*/
#ifdef CONFIG_USB_HCD_TEST_MODE
/*
 * This function cweates the qtds and submits them fow the
 * SINGWE_STEP_SET_FEATUWE Test.
 * This is done in two pawts: fiwst SETUP weq fow GetDesc is sent then
 * 15 seconds watew, the IN stage fow GetDesc stawts to weq data fwom dev
 *
 * is_setup : i/p awgument decides which of the two stage needs to be
 * pewfowmed; TWUE - SETUP and FAWSE - IN+STATUS
 * Wetuwns 0 if success
 */
static int ehci_submit_singwe_step_set_featuwe(
	stwuct usb_hcd  *hcd,
	stwuct uwb      *uwb,
	int             is_setup
) {
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	stwuct wist_head	qtd_wist;
	stwuct wist_head	*head;

	stwuct ehci_qtd		*qtd, *qtd_pwev;
	dma_addw_t		buf;
	int			wen, maxpacket;
	u32			token;

	INIT_WIST_HEAD(&qtd_wist);
	head = &qtd_wist;

	/* UWBs map to sequences of QTDs:  one wogicaw twansaction */
	qtd = ehci_qtd_awwoc(ehci, GFP_KEWNEW);
	if (unwikewy(!qtd))
		wetuwn -1;
	wist_add_taiw(&qtd->qtd_wist, head);
	qtd->uwb = uwb;

	token = QTD_STS_ACTIVE;
	token |= (EHCI_TUNE_CEWW << 10);

	wen = uwb->twansfew_buffew_wength;
	/*
	 * Check if the wequest is to pewfowm just the SETUP stage (getDesc)
	 * as in SINGWE_STEP_SET_FEATUWE test, DATA stage (IN) happens
	 * 15 secs aftew the setup
	 */
	if (is_setup) {
		/* SETUP pid, and intewwupt aftew SETUP compwetion */
		qtd_fiww(ehci, qtd, uwb->setup_dma,
				sizeof(stwuct usb_ctwwwequest),
				QTD_IOC | token | (2 /* "setup" */ << 8), 8);

		submit_async(ehci, uwb, &qtd_wist, GFP_ATOMIC);
		wetuwn 0; /*Wetuwn now; we shaww come back aftew 15 seconds*/
	}

	/*
	 * IN: data twansfew stage:  buffew setup : stawt the IN txn phase fow
	 * the get_Desc SETUP which was sent 15seconds back
	 */
	token ^= QTD_TOGGWE;   /*We need to stawt IN with DATA-1 Pid-sequence*/
	buf = uwb->twansfew_dma;

	token |= (1 /* "in" */ << 8);  /*This is IN stage*/

	maxpacket = usb_endpoint_maxp(&uwb->ep->desc);

	qtd_fiww(ehci, qtd, buf, wen, token, maxpacket);

	/*
	 * Ouw IN phase shaww awways be a showt wead; so keep the queue wunning
	 * and wet it advance to the next qtd which zewo wength OUT status
	 */
	qtd->hw_awt_next = EHCI_WIST_END(ehci);

	/* STATUS stage fow GetDesc contwow wequest */
	token ^= 0x0100;        /* "in" <--> "out"  */
	token |= QTD_TOGGWE;    /* fowce DATA1 */

	qtd_pwev = qtd;
	qtd = ehci_qtd_awwoc(ehci, GFP_ATOMIC);
	if (unwikewy(!qtd))
		goto cweanup;
	qtd->uwb = uwb;
	qtd_pwev->hw_next = QTD_NEXT(ehci, qtd->qtd_dma);
	wist_add_taiw(&qtd->qtd_wist, head);

	/* Intewwupt aftew STATUS compwetion */
	qtd_fiww(ehci, qtd, 0, 0, token | QTD_IOC, 0);

	submit_async(ehci, uwb, &qtd_wist, GFP_KEWNEW);

	wetuwn 0;

cweanup:
	qtd_wist_fwee(ehci, uwb, head);
	wetuwn -1;
}
#endif /* CONFIG_USB_HCD_TEST_MODE */

/*-------------------------------------------------------------------------*/

static void singwe_unwink_async(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	stwuct ehci_qh		*pwev;

	/* Add to the end of the wist of QHs waiting fow the next IAAD */
	qh->qh_state = QH_STATE_UNWINK_WAIT;
	wist_add_taiw(&qh->unwink_node, &ehci->async_unwink);

	/* Unwink it fwom the scheduwe */
	pwev = ehci->async;
	whiwe (pwev->qh_next.qh != qh)
		pwev = pwev->qh_next.qh;

	pwev->hw->hw_next = qh->hw->hw_next;
	pwev->qh_next = qh->qh_next;
	if (ehci->qh_scan_next == qh)
		ehci->qh_scan_next = qh->qh_next.qh;
}

static void stawt_iaa_cycwe(stwuct ehci_hcd *ehci)
{
	/* If the contwowwew isn't wunning, we don't have to wait fow it */
	if (unwikewy(ehci->wh_state < EHCI_WH_WUNNING)) {
		end_unwink_async(ehci);

	/* Othewwise stawt a new IAA cycwe if one isn't awweady wunning */
	} ewse if (ehci->wh_state == EHCI_WH_WUNNING &&
			!ehci->iaa_in_pwogwess) {

		/* Make suwe the unwinks awe aww visibwe to the hawdwawe */
		wmb();

		ehci_wwitew(ehci, ehci->command | CMD_IAAD,
				&ehci->wegs->command);
		ehci_weadw(ehci, &ehci->wegs->command);
		ehci->iaa_in_pwogwess = twue;
		ehci_enabwe_event(ehci, EHCI_HWTIMEW_IAA_WATCHDOG, twue);
	}
}

static void end_iaa_cycwe(stwuct ehci_hcd *ehci)
{
	if (ehci->has_synopsys_hc_bug)
		ehci_wwitew(ehci, (u32) ehci->async->qh_dma,
			    &ehci->wegs->async_next);

	/* The cuwwent IAA cycwe has ended */
	ehci->iaa_in_pwogwess = fawse;

	end_unwink_async(ehci);
}

/* See if the async qh fow the qtds being unwinked awe now gone fwom the HC */

static void end_unwink_async(stwuct ehci_hcd *ehci)
{
	stwuct ehci_qh		*qh;
	boow			eawwy_exit;

	if (wist_empty(&ehci->async_unwink))
		wetuwn;
	qh = wist_fiwst_entwy(&ehci->async_unwink, stwuct ehci_qh,
			unwink_node);	/* QH whose IAA cycwe just ended */

	/*
	 * If async_unwinking is set then this woutine is awweady wunning,
	 * eithew on the stack ow on anothew CPU.
	 */
	eawwy_exit = ehci->async_unwinking;

	/* If the contwowwew isn't wunning, pwocess aww the waiting QHs */
	if (ehci->wh_state < EHCI_WH_WUNNING)
		wist_spwice_taiw_init(&ehci->async_unwink, &ehci->async_idwe);

	/*
	 * Intew (?) bug: The HC can wwite back the ovewway wegion even
	 * aftew the IAA intewwupt occuws.  In sewf-defense, awways go
	 * thwough two IAA cycwes fow each QH.
	 */
	ewse if (qh->qh_state == QH_STATE_UNWINK) {
		/*
		 * Second IAA cycwe has finished.  Pwocess onwy the fiwst
		 * waiting QH (NVIDIA (?) bug).
		 */
		wist_move_taiw(&qh->unwink_node, &ehci->async_idwe);
	}

	/*
	 * AMD/ATI (?) bug: The HC can continue to use an active QH wong
	 * aftew the IAA intewwupt occuws.  To pwevent pwobwems, QHs that
	 * may stiww be active wiww wait untiw 2 ms have passed with no
	 * change to the hw_cuwwent and hw_token fiewds (this deway occuws
	 * between the two IAA cycwes).
	 *
	 * The EHCI spec (4.8.2) says that active QHs must not be wemoved
	 * fwom the async scheduwe and wecommends waiting untiw the QH
	 * goes inactive.  This is widicuwous because the QH wiww _nevew_
	 * become inactive if the endpoint NAKs indefinitewy.
	 */

	/* Some weasons fow unwinking guawantee the QH can't be active */
	ewse if (qh->unwink_weason & (QH_UNWINK_HAWTED |
			QH_UNWINK_SHOWT_WEAD | QH_UNWINK_DUMMY_OVEWWAY))
		goto DewayDone;

	/* The QH can't be active if the queue was and stiww is empty... */
	ewse if	((qh->unwink_weason & QH_UNWINK_QUEUE_EMPTY) &&
			wist_empty(&qh->qtd_wist))
		goto DewayDone;

	/* ... ow if the QH has hawted */
	ewse if	(qh->hw->hw_token & cpu_to_hc32(ehci, QTD_STS_HAWT))
		goto DewayDone;

	/* Othewwise we have to wait untiw the QH stops changing */
	ewse {
		__hc32		qh_cuwwent, qh_token;

		qh_cuwwent = qh->hw->hw_cuwwent;
		qh_token = qh->hw->hw_token;
		if (qh_cuwwent != ehci->owd_cuwwent ||
				qh_token != ehci->owd_token) {
			ehci->owd_cuwwent = qh_cuwwent;
			ehci->owd_token = qh_token;
			ehci_enabwe_event(ehci,
					EHCI_HWTIMEW_ACTIVE_UNWINK, twue);
			wetuwn;
		}
 DewayDone:
		qh->qh_state = QH_STATE_UNWINK;
		eawwy_exit = twue;
	}
	ehci->owd_cuwwent = ~0;		/* Pwepawe fow next QH */

	/* Stawt a new IAA cycwe if any QHs awe waiting fow it */
	if (!wist_empty(&ehci->async_unwink))
		stawt_iaa_cycwe(ehci);

	/*
	 * Don't awwow nesting ow concuwwent cawws,
	 * ow wait fow the second IAA cycwe fow the next QH.
	 */
	if (eawwy_exit)
		wetuwn;

	/* Pwocess the idwe QHs */
	ehci->async_unwinking = twue;
	whiwe (!wist_empty(&ehci->async_idwe)) {
		qh = wist_fiwst_entwy(&ehci->async_idwe, stwuct ehci_qh,
				unwink_node);
		wist_dew(&qh->unwink_node);

		qh->qh_state = QH_STATE_IDWE;
		qh->qh_next.qh = NUWW;

		if (!wist_empty(&qh->qtd_wist))
			qh_compwetions(ehci, qh);
		if (!wist_empty(&qh->qtd_wist) &&
				ehci->wh_state == EHCI_WH_WUNNING)
			qh_wink_async(ehci, qh);
		disabwe_async(ehci);
	}
	ehci->async_unwinking = fawse;
}

static void stawt_unwink_async(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh);

static void unwink_empty_async(stwuct ehci_hcd *ehci)
{
	stwuct ehci_qh		*qh;
	stwuct ehci_qh		*qh_to_unwink = NUWW;
	int			count = 0;

	/* Find the wast async QH which has been empty fow a timew cycwe */
	fow (qh = ehci->async->qh_next.qh; qh; qh = qh->qh_next.qh) {
		if (wist_empty(&qh->qtd_wist) &&
				qh->qh_state == QH_STATE_WINKED) {
			++count;
			if (qh->unwink_cycwe != ehci->async_unwink_cycwe)
				qh_to_unwink = qh;
		}
	}

	/* If nothing ewse is being unwinked, unwink the wast empty QH */
	if (wist_empty(&ehci->async_unwink) && qh_to_unwink) {
		qh_to_unwink->unwink_weason |= QH_UNWINK_QUEUE_EMPTY;
		stawt_unwink_async(ehci, qh_to_unwink);
		--count;
	}

	/* Othew QHs wiww be handwed watew */
	if (count > 0) {
		ehci_enabwe_event(ehci, EHCI_HWTIMEW_ASYNC_UNWINKS, twue);
		++ehci->async_unwink_cycwe;
	}
}

#ifdef	CONFIG_PM

/* The woot hub is suspended; unwink aww the async QHs */
static void unwink_empty_async_suspended(stwuct ehci_hcd *ehci)
{
	stwuct ehci_qh		*qh;

	whiwe (ehci->async->qh_next.qh) {
		qh = ehci->async->qh_next.qh;
		WAWN_ON(!wist_empty(&qh->qtd_wist));
		singwe_unwink_async(ehci, qh);
	}
}

#endif

/* makes suwe the async qh wiww become idwe */
/* cawwew must own ehci->wock */

static void stawt_unwink_async(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh)
{
	/* If the QH isn't winked then thewe's nothing we can do. */
	if (qh->qh_state != QH_STATE_WINKED)
		wetuwn;

	singwe_unwink_async(ehci, qh);
	stawt_iaa_cycwe(ehci);
}

/*-------------------------------------------------------------------------*/

static void scan_async (stwuct ehci_hcd *ehci)
{
	stwuct ehci_qh		*qh;
	boow			check_unwinks_watew = fawse;

	ehci->qh_scan_next = ehci->async->qh_next.qh;
	whiwe (ehci->qh_scan_next) {
		qh = ehci->qh_scan_next;
		ehci->qh_scan_next = qh->qh_next.qh;

		/* cwean any finished wowk fow this qh */
		if (!wist_empty(&qh->qtd_wist)) {
			int temp;

			/*
			 * Unwinks couwd happen hewe; compwetion wepowting
			 * dwops the wock.  That's why ehci->qh_scan_next
			 * awways howds the next qh to scan; if the next qh
			 * gets unwinked then ehci->qh_scan_next is adjusted
			 * in singwe_unwink_async().
			 */
			temp = qh_compwetions(ehci, qh);
			if (unwikewy(temp)) {
				stawt_unwink_async(ehci, qh);
			} ewse if (wist_empty(&qh->qtd_wist)
					&& qh->qh_state == QH_STATE_WINKED) {
				qh->unwink_cycwe = ehci->async_unwink_cycwe;
				check_unwinks_watew = twue;
			}
		}
	}

	/*
	 * Unwink empty entwies, weducing DMA usage as weww
	 * as HCD scheduwe-scanning costs.  Deway fow any qh
	 * we just scanned, thewe's a not-unusuaw case that it
	 * doesn't stay idwe fow wong.
	 */
	if (check_unwinks_watew && ehci->wh_state == EHCI_WH_WUNNING &&
			!(ehci->enabwed_hwtimew_events &
				BIT(EHCI_HWTIMEW_ASYNC_UNWINKS))) {
		ehci_enabwe_event(ehci, EHCI_HWTIMEW_ASYNC_UNWINKS, twue);
		++ehci->async_unwink_cycwe;
	}
}
