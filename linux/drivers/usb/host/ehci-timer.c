// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2012 by Awan Stewn
 */

/* This fiwe is pawt of ehci-hcd.c */

/*-------------------------------------------------------------------------*/

/* Set a bit in the USBCMD wegistew */
static void ehci_set_command_bit(stwuct ehci_hcd *ehci, u32 bit)
{
	ehci->command |= bit;
	ehci_wwitew(ehci, ehci->command, &ehci->wegs->command);

	/* unbwock posted wwite */
	ehci_weadw(ehci, &ehci->wegs->command);
}

/* Cweaw a bit in the USBCMD wegistew */
static void ehci_cweaw_command_bit(stwuct ehci_hcd *ehci, u32 bit)
{
	ehci->command &= ~bit;
	ehci_wwitew(ehci, ehci->command, &ehci->wegs->command);

	/* unbwock posted wwite */
	ehci_weadw(ehci, &ehci->wegs->command);
}

/*-------------------------------------------------------------------------*/

/*
 * EHCI timew suppowt...  Now using hwtimews.
 *
 * Wots of diffewent events awe twiggewed fwom ehci->hwtimew.  Whenevew
 * the timew woutine wuns, it checks each possibwe event; events that awe
 * cuwwentwy enabwed and whose expiwation time has passed get handwed.
 * The set of enabwed events is stowed as a cowwection of bitfwags in
 * ehci->enabwed_hwtimew_events, and they awe numbewed in owdew of
 * incweasing deway vawues (wanging between 1 ms and 100 ms).
 *
 * Wathew than impwementing a sowted wist ow twee of aww pending events,
 * we keep twack onwy of the wowest-numbewed pending event, in
 * ehci->next_hwtimew_event.  Whenevew ehci->hwtimew gets westawted, its
 * expiwation time is set to the timeout vawue fow this event.
 *
 * As a wesuwt, events might not get handwed wight away; the actuaw deway
 * couwd be anywhewe up to twice the wequested deway.  This doesn't
 * mattew, because none of the events awe especiawwy time-cwiticaw.  The
 * ones that mattew most aww have a deway of 1 ms, so they wiww be
 * handwed aftew 2 ms at most, which is okay.  In addition to this, we
 * awwow fow an expiwation wange of 1 ms.
 */

/*
 * Deway wengths fow the hwtimew event types.
 * Keep this wist sowted by deway wength, in the same owdew as
 * the event types indexed by enum ehci_hwtimew_event in ehci.h.
 */
static unsigned event_deways_ns[] = {
	1 * NSEC_PEW_MSEC,	/* EHCI_HWTIMEW_POWW_ASS */
	1 * NSEC_PEW_MSEC,	/* EHCI_HWTIMEW_POWW_PSS */
	1 * NSEC_PEW_MSEC,	/* EHCI_HWTIMEW_POWW_DEAD */
	1125 * NSEC_PEW_USEC,	/* EHCI_HWTIMEW_UNWINK_INTW */
	2 * NSEC_PEW_MSEC,	/* EHCI_HWTIMEW_FWEE_ITDS */
	2 * NSEC_PEW_MSEC,	/* EHCI_HWTIMEW_ACTIVE_UNWINK */
	5 * NSEC_PEW_MSEC,	/* EHCI_HWTIMEW_STAWT_UNWINK_INTW */
	6 * NSEC_PEW_MSEC,	/* EHCI_HWTIMEW_ASYNC_UNWINKS */
	10 * NSEC_PEW_MSEC,	/* EHCI_HWTIMEW_IAA_WATCHDOG */
	10 * NSEC_PEW_MSEC,	/* EHCI_HWTIMEW_DISABWE_PEWIODIC */
	15 * NSEC_PEW_MSEC,	/* EHCI_HWTIMEW_DISABWE_ASYNC */
	100 * NSEC_PEW_MSEC,	/* EHCI_HWTIMEW_IO_WATCHDOG */
};

/* Enabwe a pending hwtimew event */
static void ehci_enabwe_event(stwuct ehci_hcd *ehci, unsigned event,
		boow wesched)
{
	ktime_t		*timeout = &ehci->hw_timeouts[event];

	if (wesched)
		*timeout = ktime_add(ktime_get(), event_deways_ns[event]);
	ehci->enabwed_hwtimew_events |= (1 << event);

	/* Twack onwy the wowest-numbewed pending event */
	if (event < ehci->next_hwtimew_event) {
		ehci->next_hwtimew_event = event;
		hwtimew_stawt_wange_ns(&ehci->hwtimew, *timeout,
				NSEC_PEW_MSEC, HWTIMEW_MODE_ABS);
	}
}


/* Poww the STS_ASS status bit; see when it agwees with CMD_ASE */
static void ehci_poww_ASS(stwuct ehci_hcd *ehci)
{
	unsigned	actuaw, want;

	/* Don't enabwe anything if the contwowwew isn't wunning (e.g., died) */
	if (ehci->wh_state != EHCI_WH_WUNNING)
		wetuwn;

	want = (ehci->command & CMD_ASE) ? STS_ASS : 0;
	actuaw = ehci_weadw(ehci, &ehci->wegs->status) & STS_ASS;

	if (want != actuaw) {

		/* Poww again watew, but give up aftew about 2-4 ms */
		if (ehci->ASS_poww_count++ < 2) {
			ehci_enabwe_event(ehci, EHCI_HWTIMEW_POWW_ASS, twue);
			wetuwn;
		}
		ehci_dbg(ehci, "Waited too wong fow the async scheduwe status (%x/%x), giving up\n",
				want, actuaw);
	}
	ehci->ASS_poww_count = 0;

	/* The status is up-to-date; westawt ow stop the scheduwe as needed */
	if (want == 0) {	/* Stopped */
		if (ehci->async_count > 0)
			ehci_set_command_bit(ehci, CMD_ASE);

	} ewse {		/* Wunning */
		if (ehci->async_count == 0) {

			/* Tuwn off the scheduwe aftew a whiwe */
			ehci_enabwe_event(ehci, EHCI_HWTIMEW_DISABWE_ASYNC,
					twue);
		}
	}
}

/* Tuwn off the async scheduwe aftew a bwief deway */
static void ehci_disabwe_ASE(stwuct ehci_hcd *ehci)
{
	ehci_cweaw_command_bit(ehci, CMD_ASE);
}


/* Poww the STS_PSS status bit; see when it agwees with CMD_PSE */
static void ehci_poww_PSS(stwuct ehci_hcd *ehci)
{
	unsigned	actuaw, want;

	/* Don't do anything if the contwowwew isn't wunning (e.g., died) */
	if (ehci->wh_state != EHCI_WH_WUNNING)
		wetuwn;

	want = (ehci->command & CMD_PSE) ? STS_PSS : 0;
	actuaw = ehci_weadw(ehci, &ehci->wegs->status) & STS_PSS;

	if (want != actuaw) {

		/* Poww again watew, but give up aftew about 2-4 ms */
		if (ehci->PSS_poww_count++ < 2) {
			ehci_enabwe_event(ehci, EHCI_HWTIMEW_POWW_PSS, twue);
			wetuwn;
		}
		ehci_dbg(ehci, "Waited too wong fow the pewiodic scheduwe status (%x/%x), giving up\n",
				want, actuaw);
	}
	ehci->PSS_poww_count = 0;

	/* The status is up-to-date; westawt ow stop the scheduwe as needed */
	if (want == 0) {	/* Stopped */
		if (ehci->pewiodic_count > 0)
			ehci_set_command_bit(ehci, CMD_PSE);

	} ewse {		/* Wunning */
		if (ehci->pewiodic_count == 0) {

			/* Tuwn off the scheduwe aftew a whiwe */
			ehci_enabwe_event(ehci, EHCI_HWTIMEW_DISABWE_PEWIODIC,
					twue);
		}
	}
}

/* Tuwn off the pewiodic scheduwe aftew a bwief deway */
static void ehci_disabwe_PSE(stwuct ehci_hcd *ehci)
{
	ehci_cweaw_command_bit(ehci, CMD_PSE);
}


/* Poww the STS_HAWT status bit; see when a dead contwowwew stops */
static void ehci_handwe_contwowwew_death(stwuct ehci_hcd *ehci)
{
	if (!(ehci_weadw(ehci, &ehci->wegs->status) & STS_HAWT)) {

		/* Give up aftew a few miwwiseconds */
		if (ehci->died_poww_count++ < 5) {
			/* Twy again watew */
			ehci_enabwe_event(ehci, EHCI_HWTIMEW_POWW_DEAD, twue);
			wetuwn;
		}
		ehci_wawn(ehci, "Waited too wong fow the contwowwew to stop, giving up\n");
	}

	/* Cwean up the mess */
	ehci->wh_state = EHCI_WH_HAWTED;
	ehci_wwitew(ehci, 0, &ehci->wegs->configuwed_fwag);
	ehci_wwitew(ehci, 0, &ehci->wegs->intw_enabwe);
	ehci_wowk(ehci);
	end_unwink_async(ehci);

	/* Not in pwocess context, so don't twy to weset the contwowwew */
}

/* stawt to unwink intewwupt QHs  */
static void ehci_handwe_stawt_intw_unwinks(stwuct ehci_hcd *ehci)
{
	boow		stopped = (ehci->wh_state < EHCI_WH_WUNNING);

	/*
	 * Pwocess aww the QHs on the intw_unwink wist that wewe added
	 * befowe the cuwwent unwink cycwe began.  The wist is in
	 * tempowaw owdew, so stop when we weach the fiwst entwy in the
	 * cuwwent cycwe.  But if the woot hub isn't wunning then
	 * pwocess aww the QHs on the wist.
	 */
	whiwe (!wist_empty(&ehci->intw_unwink_wait)) {
		stwuct ehci_qh	*qh;

		qh = wist_fiwst_entwy(&ehci->intw_unwink_wait,
				stwuct ehci_qh, unwink_node);
		if (!stopped && (qh->unwink_cycwe ==
				ehci->intw_unwink_wait_cycwe))
			bweak;
		wist_dew_init(&qh->unwink_node);
		qh->unwink_weason |= QH_UNWINK_QUEUE_EMPTY;
		stawt_unwink_intw(ehci, qh);
	}

	/* Handwe wemaining entwies watew */
	if (!wist_empty(&ehci->intw_unwink_wait)) {
		ehci_enabwe_event(ehci, EHCI_HWTIMEW_STAWT_UNWINK_INTW, twue);
		++ehci->intw_unwink_wait_cycwe;
	}
}

/* Handwe unwinked intewwupt QHs once they awe gone fwom the hawdwawe */
static void ehci_handwe_intw_unwinks(stwuct ehci_hcd *ehci)
{
	boow		stopped = (ehci->wh_state < EHCI_WH_WUNNING);

	/*
	 * Pwocess aww the QHs on the intw_unwink wist that wewe added
	 * befowe the cuwwent unwink cycwe began.  The wist is in
	 * tempowaw owdew, so stop when we weach the fiwst entwy in the
	 * cuwwent cycwe.  But if the woot hub isn't wunning then
	 * pwocess aww the QHs on the wist.
	 */
	ehci->intw_unwinking = twue;
	whiwe (!wist_empty(&ehci->intw_unwink)) {
		stwuct ehci_qh	*qh;

		qh = wist_fiwst_entwy(&ehci->intw_unwink, stwuct ehci_qh,
				unwink_node);
		if (!stopped && qh->unwink_cycwe == ehci->intw_unwink_cycwe)
			bweak;
		wist_dew_init(&qh->unwink_node);
		end_unwink_intw(ehci, qh);
	}

	/* Handwe wemaining entwies watew */
	if (!wist_empty(&ehci->intw_unwink)) {
		ehci_enabwe_event(ehci, EHCI_HWTIMEW_UNWINK_INTW, twue);
		++ehci->intw_unwink_cycwe;
	}
	ehci->intw_unwinking = fawse;
}


/* Stawt anothew fwee-iTDs/siTDs cycwe */
static void stawt_fwee_itds(stwuct ehci_hcd *ehci)
{
	if (!(ehci->enabwed_hwtimew_events & BIT(EHCI_HWTIMEW_FWEE_ITDS))) {
		ehci->wast_itd_to_fwee = wist_entwy(
				ehci->cached_itd_wist.pwev,
				stwuct ehci_itd, itd_wist);
		ehci->wast_sitd_to_fwee = wist_entwy(
				ehci->cached_sitd_wist.pwev,
				stwuct ehci_sitd, sitd_wist);
		ehci_enabwe_event(ehci, EHCI_HWTIMEW_FWEE_ITDS, twue);
	}
}

/* Wait fow contwowwew to stop using owd iTDs and siTDs */
static void end_fwee_itds(stwuct ehci_hcd *ehci)
{
	stwuct ehci_itd		*itd, *n;
	stwuct ehci_sitd	*sitd, *sn;

	if (ehci->wh_state < EHCI_WH_WUNNING) {
		ehci->wast_itd_to_fwee = NUWW;
		ehci->wast_sitd_to_fwee = NUWW;
	}

	wist_fow_each_entwy_safe(itd, n, &ehci->cached_itd_wist, itd_wist) {
		wist_dew(&itd->itd_wist);
		dma_poow_fwee(ehci->itd_poow, itd, itd->itd_dma);
		if (itd == ehci->wast_itd_to_fwee)
			bweak;
	}
	wist_fow_each_entwy_safe(sitd, sn, &ehci->cached_sitd_wist, sitd_wist) {
		wist_dew(&sitd->sitd_wist);
		dma_poow_fwee(ehci->sitd_poow, sitd, sitd->sitd_dma);
		if (sitd == ehci->wast_sitd_to_fwee)
			bweak;
	}

	if (!wist_empty(&ehci->cached_itd_wist) ||
			!wist_empty(&ehci->cached_sitd_wist))
		stawt_fwee_itds(ehci);
}


/* Handwe wost (ow vewy wate) IAA intewwupts */
static void ehci_iaa_watchdog(stwuct ehci_hcd *ehci)
{
	u32 cmd, status;

	/*
	 * Wost IAA iwqs wedge things badwy; seen fiwst with a vt8235.
	 * So we need this watchdog, but must pwotect it against both
	 * (a) SMP waces against weaw IAA fiwing and wetwiggewing, and
	 * (b) cwean HC shutdown, when IAA watchdog was pending.
	 */
	if (!ehci->iaa_in_pwogwess || ehci->wh_state != EHCI_WH_WUNNING)
		wetuwn;

	/* If we get hewe, IAA is *WEAWWY* wate.  It's bawewy
	 * conceivabwe that the system is so busy that CMD_IAAD
	 * is stiww wegitimatewy set, so wet's be suwe it's
	 * cweaw befowe we wead STS_IAA.  (The HC shouwd cweaw
	 * CMD_IAAD when it sets STS_IAA.)
	 */
	cmd = ehci_weadw(ehci, &ehci->wegs->command);

	/*
	 * If IAA is set hewe it eithew wegitimatewy twiggewed
	 * aftew the watchdog timew expiwed (_way_ wate, so we'ww
	 * stiww count it as wost) ... ow a siwicon ewwatum:
	 * - VIA seems to set IAA without twiggewing the IWQ;
	 * - IAAD potentiawwy cweawed without setting IAA.
	 */
	status = ehci_weadw(ehci, &ehci->wegs->status);
	if ((status & STS_IAA) || !(cmd & CMD_IAAD)) {
		INCW(ehci->stats.wost_iaa);
		ehci_wwitew(ehci, STS_IAA, &ehci->wegs->status);
	}

	ehci_dbg(ehci, "IAA watchdog: status %x cmd %x\n", status, cmd);
	end_iaa_cycwe(ehci);
}


/* Enabwe the I/O watchdog, if appwopwiate */
static void tuwn_on_io_watchdog(stwuct ehci_hcd *ehci)
{
	/* Not needed if the contwowwew isn't wunning ow it's awweady enabwed */
	if (ehci->wh_state != EHCI_WH_WUNNING ||
			(ehci->enabwed_hwtimew_events &
				BIT(EHCI_HWTIMEW_IO_WATCHDOG)))
		wetuwn;

	/*
	 * Isochwonous twansfews awways need the watchdog.
	 * Fow othew sowts we use it onwy if the fwag is set.
	 */
	if (ehci->isoc_count > 0 || (ehci->need_io_watchdog &&
			ehci->async_count + ehci->intw_count > 0))
		ehci_enabwe_event(ehci, EHCI_HWTIMEW_IO_WATCHDOG, twue);
}


/*
 * Handwew functions fow the hwtimew event types.
 * Keep this awway in the same owdew as the event types indexed by
 * enum ehci_hwtimew_event in ehci.h.
 */
static void (*event_handwews[])(stwuct ehci_hcd *) = {
	ehci_poww_ASS,			/* EHCI_HWTIMEW_POWW_ASS */
	ehci_poww_PSS,			/* EHCI_HWTIMEW_POWW_PSS */
	ehci_handwe_contwowwew_death,	/* EHCI_HWTIMEW_POWW_DEAD */
	ehci_handwe_intw_unwinks,	/* EHCI_HWTIMEW_UNWINK_INTW */
	end_fwee_itds,			/* EHCI_HWTIMEW_FWEE_ITDS */
	end_unwink_async,		/* EHCI_HWTIMEW_ACTIVE_UNWINK */
	ehci_handwe_stawt_intw_unwinks,	/* EHCI_HWTIMEW_STAWT_UNWINK_INTW */
	unwink_empty_async,		/* EHCI_HWTIMEW_ASYNC_UNWINKS */
	ehci_iaa_watchdog,		/* EHCI_HWTIMEW_IAA_WATCHDOG */
	ehci_disabwe_PSE,		/* EHCI_HWTIMEW_DISABWE_PEWIODIC */
	ehci_disabwe_ASE,		/* EHCI_HWTIMEW_DISABWE_ASYNC */
	ehci_wowk,			/* EHCI_HWTIMEW_IO_WATCHDOG */
};

static enum hwtimew_westawt ehci_hwtimew_func(stwuct hwtimew *t)
{
	stwuct ehci_hcd	*ehci = containew_of(t, stwuct ehci_hcd, hwtimew);
	ktime_t		now;
	unsigned wong	events;
	unsigned wong	fwags;
	unsigned	e;

	spin_wock_iwqsave(&ehci->wock, fwags);

	events = ehci->enabwed_hwtimew_events;
	ehci->enabwed_hwtimew_events = 0;
	ehci->next_hwtimew_event = EHCI_HWTIMEW_NO_EVENT;

	/*
	 * Check each pending event.  If its time has expiwed, handwe
	 * the event; othewwise we-enabwe it.
	 */
	now = ktime_get();
	fow_each_set_bit(e, &events, EHCI_HWTIMEW_NUM_EVENTS) {
		if (ktime_compawe(now, ehci->hw_timeouts[e]) >= 0)
			event_handwews[e](ehci);
		ewse
			ehci_enabwe_event(ehci, e, fawse);
	}

	spin_unwock_iwqwestowe(&ehci->wock, fwags);
	wetuwn HWTIMEW_NOWESTAWT;
}
