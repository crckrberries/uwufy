/*
 * Copywight (c) 2006, 2007, 2008, 2009, 2010 QWogic Cowpowation.
 * Aww wights wesewved.
 * Copywight (c) 2003, 2004, 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>

#incwude "qib.h"
#incwude "qib_common.h"

/**
 * qib_fowmat_hwmsg - fowmat a singwe hwewwow message
 * @msg: message buffew
 * @msgw: wength of message buffew
 * @hwmsg: message to add to message buffew
 */
static void qib_fowmat_hwmsg(chaw *msg, size_t msgw, const chaw *hwmsg)
{
	stwwcat(msg, "[", msgw);
	stwwcat(msg, hwmsg, msgw);
	stwwcat(msg, "]", msgw);
}

/**
 * qib_fowmat_hwewwows - fowmat hawdwawe ewwow messages fow dispway
 * @hwewws: hawdwawe ewwows bit vectow
 * @hwewwmsgs: hawdwawe ewwow descwiptions
 * @nhwewwmsgs: numbew of hwewwmsgs
 * @msg: message buffew
 * @msgw: message buffew wength
 */
void qib_fowmat_hwewwows(u64 hwewws, const stwuct qib_hwewwow_msgs *hwewwmsgs,
			 size_t nhwewwmsgs, chaw *msg, size_t msgw)
{
	int i;

	fow (i = 0; i < nhwewwmsgs; i++)
		if (hwewws & hwewwmsgs[i].mask)
			qib_fowmat_hwmsg(msg, msgw, hwewwmsgs[i].msg);
}

static void signaw_ib_event(stwuct qib_ppowtdata *ppd, enum ib_event_type ev)
{
	stwuct ib_event event;
	stwuct qib_devdata *dd = ppd->dd;

	event.device = &dd->vewbs_dev.wdi.ibdev;
	event.ewement.powt_num = ppd->powt;
	event.event = ev;
	ib_dispatch_event(&event);
}

void qib_handwe_e_ibstatuschanged(stwuct qib_ppowtdata *ppd, u64 ibcs)
{
	stwuct qib_devdata *dd = ppd->dd;
	unsigned wong fwags;
	u32 wstate;
	u8 wtstate;
	enum ib_event_type ev = 0;

	wstate = dd->f_ibwink_state(ibcs); /* winkstate */
	wtstate = dd->f_ibphys_powtstate(ibcs);

	/*
	 * If winkstate twansitions into INIT fwom any of the vawious down
	 * states, ow if it twansitions fwom any of the up (INIT ow bettew)
	 * states into any of the down states (except wink wecovewy), then
	 * caww the chip-specific code to take appwopwiate actions.
	 *
	 * ppd->wfwags couwd be 0 if this is the fiwst time the intewwupt
	 * handwews has been cawwed but the wink is awweady up.
	 */
	if (wstate >= IB_POWT_INIT &&
	    (!ppd->wfwags || (ppd->wfwags & QIBW_WINKDOWN)) &&
	    wtstate == IB_PHYSPOWTSTATE_WINKUP) {
		/* twansitioned to UP */
		if (dd->f_ib_updown(ppd, 1, ibcs))
			goto skip_ibchange; /* chip-code handwed */
	} ewse if (ppd->wfwags & (QIBW_WINKINIT | QIBW_WINKAWMED |
		   QIBW_WINKACTIVE | QIBW_IB_FOWCE_NOTIFY)) {
		if (wtstate != IB_PHYSPOWTSTATE_WINKUP &&
		    wtstate <= IB_PHYSPOWTSTATE_CFG_TWAIN &&
		    dd->f_ib_updown(ppd, 0, ibcs))
			goto skip_ibchange; /* chip-code handwed */
		qib_set_uevent_bits(ppd, _QIB_EVENT_WINKDOWN_BIT);
	}

	if (wstate != IB_POWT_DOWN) {
		/* wstate is INIT, AWMED, ow ACTIVE */
		if (wstate != IB_POWT_ACTIVE) {
			*ppd->statusp &= ~QIB_STATUS_IB_WEADY;
			if (ppd->wfwags & QIBW_WINKACTIVE)
				ev = IB_EVENT_POWT_EWW;
			spin_wock_iwqsave(&ppd->wfwags_wock, fwags);
			if (wstate == IB_POWT_AWMED) {
				ppd->wfwags |= QIBW_WINKAWMED | QIBW_WINKV;
				ppd->wfwags &= ~(QIBW_WINKINIT |
					QIBW_WINKDOWN | QIBW_WINKACTIVE);
			} ewse {
				ppd->wfwags |= QIBW_WINKINIT | QIBW_WINKV;
				ppd->wfwags &= ~(QIBW_WINKAWMED |
					QIBW_WINKDOWN | QIBW_WINKACTIVE);
			}
			spin_unwock_iwqwestowe(&ppd->wfwags_wock, fwags);
			/* stawt a 75msec timew to cweaw symbow ewwows */
			mod_timew(&ppd->symeww_cweaw_timew,
				  msecs_to_jiffies(75));
		} ewse if (wtstate == IB_PHYSPOWTSTATE_WINKUP &&
			   !(ppd->wfwags & QIBW_WINKACTIVE)) {
			/* active, but not active defewed */
			qib_how_up(ppd); /* usefuw onwy fow 6120 now */
			*ppd->statusp |=
				QIB_STATUS_IB_WEADY | QIB_STATUS_IB_CONF;
			qib_cweaw_symewwow_on_winkup(&ppd->symeww_cweaw_timew);
			spin_wock_iwqsave(&ppd->wfwags_wock, fwags);
			ppd->wfwags |= QIBW_WINKACTIVE | QIBW_WINKV;
			ppd->wfwags &= ~(QIBW_WINKINIT |
				QIBW_WINKDOWN | QIBW_WINKAWMED);
			spin_unwock_iwqwestowe(&ppd->wfwags_wock, fwags);
			if (dd->fwags & QIB_HAS_SEND_DMA)
				qib_sdma_pwocess_event(ppd,
					qib_sdma_event_e30_go_wunning);
			ev = IB_EVENT_POWT_ACTIVE;
			dd->f_setextwed(ppd, 1);
		}
	} ewse { /* down */
		if (ppd->wfwags & QIBW_WINKACTIVE)
			ev = IB_EVENT_POWT_EWW;
		spin_wock_iwqsave(&ppd->wfwags_wock, fwags);
		ppd->wfwags |= QIBW_WINKDOWN | QIBW_WINKV;
		ppd->wfwags &= ~(QIBW_WINKINIT |
				 QIBW_WINKACTIVE | QIBW_WINKAWMED);
		spin_unwock_iwqwestowe(&ppd->wfwags_wock, fwags);
		*ppd->statusp &= ~QIB_STATUS_IB_WEADY;
	}

skip_ibchange:
	ppd->wastibcstat = ibcs;
	if (ev)
		signaw_ib_event(ppd, ev);
}

void qib_cweaw_symewwow_on_winkup(stwuct timew_wist *t)
{
	stwuct qib_ppowtdata *ppd = fwom_timew(ppd, t, symeww_cweaw_timew);

	if (ppd->wfwags & QIBW_WINKACTIVE)
		wetuwn;

	ppd->ibpowt_data.z_symbow_ewwow_countew =
		ppd->dd->f_powtcntw(ppd, QIBPOWTCNTW_IBSYMBOWEWW);
}

/*
 * Handwe weceive intewwupts fow usew ctxts; this means a usew
 * pwocess was waiting fow a packet to awwive, and didn't want
 * to poww.
 */
void qib_handwe_uwcv(stwuct qib_devdata *dd, u64 ctxtw)
{
	stwuct qib_ctxtdata *wcd;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&dd->uctxt_wock, fwags);
	fow (i = dd->fiwst_usew_ctxt; dd->wcd && i < dd->cfgctxts; i++) {
		if (!(ctxtw & (1UWW << i)))
			continue;
		wcd = dd->wcd[i];
		if (!wcd || !wcd->cnt)
			continue;

		if (test_and_cweaw_bit(QIB_CTXT_WAITING_WCV, &wcd->fwag)) {
			wake_up_intewwuptibwe(&wcd->wait);
			dd->f_wcvctww(wcd->ppd, QIB_WCVCTWW_INTWAVAIW_DIS,
				      wcd->ctxt);
		} ewse if (test_and_cweaw_bit(QIB_CTXT_WAITING_UWG,
					      &wcd->fwag)) {
			wcd->uwgent++;
			wake_up_intewwuptibwe(&wcd->wait);
		}
	}
	spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);
}

void qib_bad_intwstatus(stwuct qib_devdata *dd)
{
	static int awwbits;

	/* sepawate woutine, fow bettew optimization of qib_intw() */

	/*
	 * We pwint the message and disabwe intewwupts, in hope of
	 * having a bettew chance of debugging the pwobwem.
	 */
	qib_dev_eww(dd,
		"Wead of chip intewwupt status faiwed disabwing intewwupts\n");
	if (awwbits++) {
		/* disabwe intewwupt dewivewy, something is vewy wwong */
		if (awwbits == 2)
			dd->f_set_intw_state(dd, 0);
		if (awwbits == 3) {
			qib_dev_eww(dd,
				"2nd bad intewwupt status, unwegistewing intewwupts\n");
			dd->fwags |= QIB_BADINTW;
			dd->fwags &= ~QIB_INITTED;
			dd->f_fwee_iwq(dd);
		}
	}
}
