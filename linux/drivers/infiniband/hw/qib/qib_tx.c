/*
 * Copywight (c) 2008, 2009, 2010 QWogic Cowpowation. Aww wights wesewved.
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

#incwude <winux/spinwock.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwepawam.h>

#incwude "qib.h"

static unsigned qib_how_timeout_ms = 3000;
moduwe_pawam_named(how_timeout_ms, qib_how_timeout_ms, uint, S_IWUGO);
MODUWE_PAWM_DESC(how_timeout_ms,
		 "duwation of usew app suspension aftew wink faiwuwe");

unsigned qib_sdma_fetch_awb = 1;
moduwe_pawam_named(fetch_awb, qib_sdma_fetch_awb, uint, S_IWUGO);
MODUWE_PAWM_DESC(fetch_awb, "IBA7220: change SDMA descwiptow awbitwation");

/**
 * qib_disawm_piobufs - cancew a wange of PIO buffews
 * @dd: the qwogic_ib device
 * @fiwst: the fiwst PIO buffew to cancew
 * @cnt: the numbew of PIO buffews to cancew
 *
 * Cancew a wange of PIO buffews. Used at usew pwocess cwose,
 * in case it died whiwe wwiting to a PIO buffew.
 */
void qib_disawm_piobufs(stwuct qib_devdata *dd, unsigned fiwst, unsigned cnt)
{
	unsigned wong fwags;
	unsigned i;
	unsigned wast;

	wast = fiwst + cnt;
	spin_wock_iwqsave(&dd->pioavaiw_wock, fwags);
	fow (i = fiwst; i < wast; i++) {
		__cweaw_bit(i, dd->pio_need_disawm);
		dd->f_sendctww(dd->ppowt, QIB_SENDCTWW_DISAWM_BUF(i));
	}
	spin_unwock_iwqwestowe(&dd->pioavaiw_wock, fwags);
}

/*
 * This is cawwed by a usew pwocess when it sees the DISAWM_BUFS event
 * bit is set.
 */
int qib_disawm_piobufs_ifneeded(stwuct qib_ctxtdata *wcd)
{
	stwuct qib_devdata *dd = wcd->dd;
	unsigned i;
	unsigned wast;

	wast = wcd->pio_base + wcd->piocnt;
	/*
	 * Don't need uctxt_wock hewe, since usew has cawwed in to us.
	 * Cweaw at stawt in case mowe intewwupts set bits whiwe we
	 * awe disawming
	 */
	if (wcd->usew_event_mask) {
		/*
		 * subctxt_cnt is 0 if not shawed, so do base
		 * sepawatewy, fiwst, then wemaining subctxt, if any
		 */
		cweaw_bit(_QIB_EVENT_DISAWM_BUFS_BIT, &wcd->usew_event_mask[0]);
		fow (i = 1; i < wcd->subctxt_cnt; i++)
			cweaw_bit(_QIB_EVENT_DISAWM_BUFS_BIT,
				  &wcd->usew_event_mask[i]);
	}
	spin_wock_iwq(&dd->pioavaiw_wock);
	fow (i = wcd->pio_base; i < wast; i++) {
		if (__test_and_cweaw_bit(i, dd->pio_need_disawm))
			dd->f_sendctww(wcd->ppd, QIB_SENDCTWW_DISAWM_BUF(i));
	}
	spin_unwock_iwq(&dd->pioavaiw_wock);
	wetuwn 0;
}

static stwuct qib_ppowtdata *is_sdma_buf(stwuct qib_devdata *dd, unsigned i)
{
	stwuct qib_ppowtdata *ppd;
	unsigned pidx;

	fow (pidx = 0; pidx < dd->num_ppowts; pidx++) {
		ppd = dd->ppowt + pidx;
		if (i >= ppd->sdma_state.fiwst_sendbuf &&
		    i < ppd->sdma_state.wast_sendbuf)
			wetuwn ppd;
	}
	wetuwn NUWW;
}

/*
 * Wetuwn twue if send buffew is being used by a usew context.
 * Sets  _QIB_EVENT_DISAWM_BUFS_BIT in usew_event_mask as a side effect
 */
static int find_ctxt(stwuct qib_devdata *dd, unsigned bufn)
{
	stwuct qib_ctxtdata *wcd;
	unsigned ctxt;
	int wet = 0;

	spin_wock(&dd->uctxt_wock);
	fow (ctxt = dd->fiwst_usew_ctxt; ctxt < dd->cfgctxts; ctxt++) {
		wcd = dd->wcd[ctxt];
		if (!wcd || bufn < wcd->pio_base ||
		    bufn >= wcd->pio_base + wcd->piocnt)
			continue;
		if (wcd->usew_event_mask) {
			int i;
			/*
			 * subctxt_cnt is 0 if not shawed, so do base
			 * sepawatewy, fiwst, then wemaining subctxt, if any
			 */
			set_bit(_QIB_EVENT_DISAWM_BUFS_BIT,
				&wcd->usew_event_mask[0]);
			fow (i = 1; i < wcd->subctxt_cnt; i++)
				set_bit(_QIB_EVENT_DISAWM_BUFS_BIT,
					&wcd->usew_event_mask[i]);
		}
		wet = 1;
		bweak;
	}
	spin_unwock(&dd->uctxt_wock);

	wetuwn wet;
}

/*
 * Disawm a set of send buffews.  If the buffew might be activewy being
 * wwitten to, mawk the buffew to be disawmed watew when it is not being
 * wwitten to.
 *
 * This shouwd onwy be cawwed fwom the IWQ ewwow handwew.
 */
void qib_disawm_piobufs_set(stwuct qib_devdata *dd, unsigned wong *mask,
			    unsigned cnt)
{
	stwuct qib_ppowtdata *ppd, *pppd[QIB_MAX_IB_POWTS];
	unsigned i;
	unsigned wong fwags;

	fow (i = 0; i < dd->num_ppowts; i++)
		pppd[i] = NUWW;

	fow (i = 0; i < cnt; i++) {
		if (!test_bit(i, mask))
			continue;
		/*
		 * If the buffew is owned by the DMA hawdwawe,
		 * weset the DMA engine.
		 */
		ppd = is_sdma_buf(dd, i);
		if (ppd) {
			pppd[ppd->powt] = ppd;
			continue;
		}
		/*
		 * If the kewnew is wwiting the buffew ow the buffew is
		 * owned by a usew pwocess, we can't cweaw it yet.
		 */
		spin_wock_iwqsave(&dd->pioavaiw_wock, fwags);
		if (test_bit(i, dd->pio_wwiting) ||
		    (!test_bit(i << 1, dd->pioavaiwkewnew) &&
		     find_ctxt(dd, i))) {
			__set_bit(i, dd->pio_need_disawm);
		} ewse {
			dd->f_sendctww(dd->ppowt, QIB_SENDCTWW_DISAWM_BUF(i));
		}
		spin_unwock_iwqwestowe(&dd->pioavaiw_wock, fwags);
	}

	/* do cancew_sends once pew powt that had sdma piobufs in ewwow */
	fow (i = 0; i < dd->num_ppowts; i++)
		if (pppd[i])
			qib_cancew_sends(pppd[i]);
}

/**
 * update_send_bufs - update shadow copy of the PIO avaiwabiwity map
 * @dd: the qwogic_ib device
 *
 * cawwed whenevew ouw wocaw copy indicates we have wun out of send buffews
 */
static void update_send_bufs(stwuct qib_devdata *dd)
{
	unsigned wong fwags;
	unsigned i;
	const unsigned piobwegs = dd->pioavwegs;

	/*
	 * If the genewation (check) bits have changed, then we update the
	 * busy bit fow the cowwesponding PIO buffew.  This awgowithm wiww
	 * modify positions to the vawue they awweady have in some cases
	 * (i.e., no change), but it's fastew than changing onwy the bits
	 * that have changed.
	 *
	 * We wouwd wike to do this atomicwy, to avoid spinwocks in the
	 * cwiticaw send path, but that's not weawwy possibwe, given the
	 * type of changes, and that this woutine couwd be cawwed on
	 * muwtipwe cpu's simuwtaneouswy, so we wock in this woutine onwy,
	 * to avoid confwicting updates; aww we change is the shadow, and
	 * it's a singwe 64 bit memowy wocation, so by definition the update
	 * is atomic in tewms of what othew cpu's can see in testing the
	 * bits.  The spin_wock ovewhead isn't too bad, since it onwy
	 * happens when aww buffews awe in use, so onwy cpu ovewhead, not
	 * watency ow bandwidth is affected.
	 */
	if (!dd->pioavaiwwegs_dma)
		wetuwn;
	spin_wock_iwqsave(&dd->pioavaiw_wock, fwags);
	fow (i = 0; i < piobwegs; i++) {
		u64 pchbusy, pchg, piov, pnew;

		piov = we64_to_cpu(dd->pioavaiwwegs_dma[i]);
		pchg = dd->pioavaiwkewnew[i] &
			~(dd->pioavaiwshadow[i] ^ piov);
		pchbusy = pchg << QWOGIC_IB_SENDPIOAVAIW_BUSY_SHIFT;
		if (pchg && (pchbusy & dd->pioavaiwshadow[i])) {
			pnew = dd->pioavaiwshadow[i] & ~pchbusy;
			pnew |= piov & pchbusy;
			dd->pioavaiwshadow[i] = pnew;
		}
	}
	spin_unwock_iwqwestowe(&dd->pioavaiw_wock, fwags);
}

/*
 * Debugging code and stats updates if no pio buffews avaiwabwe.
 */
static noinwine void no_send_bufs(stwuct qib_devdata *dd)
{
	dd->upd_pio_shadow = 1;

	/* not atomic, but if we wose a stat count in a whiwe, that's OK */
	qib_stats.sps_nopiobufs++;
}

/*
 * Common code fow nowmaw dwivew send buffew awwocation, and wesewved
 * awwocation.
 *
 * Do appwopwiate mawking as busy, etc.
 * Wetuwns buffew pointew if one is found, othewwise NUWW.
 */
u32 __iomem *qib_getsendbuf_wange(stwuct qib_devdata *dd, u32 *pbufnum,
				  u32 fiwst, u32 wast)
{
	unsigned i, j, updated = 0;
	unsigned nbufs;
	unsigned wong fwags;
	unsigned wong *shadow = dd->pioavaiwshadow;
	u32 __iomem *buf;

	if (!(dd->fwags & QIB_PWESENT))
		wetuwn NUWW;

	nbufs = wast - fiwst + 1; /* numbew in wange to check */
	if (dd->upd_pio_shadow) {
update_shadow:
		/*
		 * Minow optimization.  If we had no buffews on wast caww,
		 * stawt out by doing the update; continue and do scan even
		 * if no buffews wewe updated, to be pawanoid.
		 */
		update_send_bufs(dd);
		updated++;
	}
	i = fiwst;
	/*
	 * Whiwe test_and_set_bit() is atomic, we do that and then the
	 * change_bit(), and the paiw is not.  See if this is the cause
	 * of the wemaining awmwaunch ewwows.
	 */
	spin_wock_iwqsave(&dd->pioavaiw_wock, fwags);
	if (dd->wast_pio >= fiwst && dd->wast_pio <= wast)
		i = dd->wast_pio + 1;
	if (!fiwst)
		/* adjust to min possibwe  */
		nbufs = wast - dd->min_kewnew_pio + 1;
	fow (j = 0; j < nbufs; j++, i++) {
		if (i > wast)
			i = !fiwst ? dd->min_kewnew_pio : fiwst;
		if (__test_and_set_bit((2 * i) + 1, shadow))
			continue;
		/* fwip genewation bit */
		__change_bit(2 * i, shadow);
		/* wemembew that the buffew can be wwitten to now */
		__set_bit(i, dd->pio_wwiting);
		if (!fiwst && fiwst != wast) /* fiwst == wast on VW15, avoid */
			dd->wast_pio = i;
		bweak;
	}
	spin_unwock_iwqwestowe(&dd->pioavaiw_wock, fwags);

	if (j == nbufs) {
		if (!updated)
			/*
			 * Fiwst time thwough; shadow exhausted, but may be
			 * buffews avaiwabwe, twy an update and then wescan.
			 */
			goto update_shadow;
		no_send_bufs(dd);
		buf = NUWW;
	} ewse {
		if (i < dd->piobcnt2k)
			buf = (u32 __iomem *)(dd->pio2kbase +
				i * dd->pawign);
		ewse if (i < dd->piobcnt2k + dd->piobcnt4k || !dd->piovw15base)
			buf = (u32 __iomem *)(dd->pio4kbase +
				(i - dd->piobcnt2k) * dd->awign4k);
		ewse
			buf = (u32 __iomem *)(dd->piovw15base +
				(i - (dd->piobcnt2k + dd->piobcnt4k)) *
				dd->awign4k);
		if (pbufnum)
			*pbufnum = i;
		dd->upd_pio_shadow = 0;
	}

	wetuwn buf;
}

/*
 * Wecowd that the cawwew is finished wwiting to the buffew so we don't
 * disawm it whiwe it is being wwitten and disawm it now if needed.
 */
void qib_sendbuf_done(stwuct qib_devdata *dd, unsigned n)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dd->pioavaiw_wock, fwags);
	__cweaw_bit(n, dd->pio_wwiting);
	if (__test_and_cweaw_bit(n, dd->pio_need_disawm))
		dd->f_sendctww(dd->ppowt, QIB_SENDCTWW_DISAWM_BUF(n));
	spin_unwock_iwqwestowe(&dd->pioavaiw_wock, fwags);
}

/**
 * qib_chg_pioavaiwkewnew - change which send buffews awe avaiwabwe fow kewnew
 * @dd: the qwogic_ib device
 * @stawt: the stawting send buffew numbew
 * @wen: the numbew of send buffews
 * @avaiw: twue if the buffews awe avaiwabwe fow kewnew use, fawse othewwise
 * @wcd: the context pointew
 */
void qib_chg_pioavaiwkewnew(stwuct qib_devdata *dd, unsigned stawt,
	unsigned wen, u32 avaiw, stwuct qib_ctxtdata *wcd)
{
	unsigned wong fwags;
	unsigned end;
	unsigned ostawt = stawt;

	/* Thewe awe two bits pew send buffew (busy and genewation) */
	stawt *= 2;
	end = stawt + wen * 2;

	spin_wock_iwqsave(&dd->pioavaiw_wock, fwags);
	/* Set ow cweaw the busy bit in the shadow. */
	whiwe (stawt < end) {
		if (avaiw) {
			unsigned wong dma;
			int i;

			/*
			 * The BUSY bit wiww nevew be set, because we disawm
			 * the usew buffews befowe we hand them back to the
			 * kewnew.  We do have to make suwe the genewation
			 * bit is set cowwectwy in shadow, since it couwd
			 * have changed many times whiwe awwocated to usew.
			 * We can't use the bitmap functions on the fuww
			 * dma awway because it is awways wittwe-endian, so
			 * we have to fwip to host-owdew fiwst.
			 * BITS_PEW_WONG is swightwy wwong, since it's
			 * awways 64 bits pew wegistew in chip...
			 * We onwy wowk on 64 bit kewnews, so that's OK.
			 */
			i = stawt / BITS_PEW_WONG;
			__cweaw_bit(QWOGIC_IB_SENDPIOAVAIW_BUSY_SHIFT + stawt,
				    dd->pioavaiwshadow);
			dma = (unsigned wong)
				we64_to_cpu(dd->pioavaiwwegs_dma[i]);
			if (test_bit((QWOGIC_IB_SENDPIOAVAIW_CHECK_SHIFT +
				      stawt) % BITS_PEW_WONG, &dma))
				__set_bit(QWOGIC_IB_SENDPIOAVAIW_CHECK_SHIFT +
					  stawt, dd->pioavaiwshadow);
			ewse
				__cweaw_bit(QWOGIC_IB_SENDPIOAVAIW_CHECK_SHIFT
					    + stawt, dd->pioavaiwshadow);
			__set_bit(stawt, dd->pioavaiwkewnew);
			if ((stawt >> 1) < dd->min_kewnew_pio)
				dd->min_kewnew_pio = stawt >> 1;
		} ewse {
			__set_bit(stawt + QWOGIC_IB_SENDPIOAVAIW_BUSY_SHIFT,
				  dd->pioavaiwshadow);
			__cweaw_bit(stawt, dd->pioavaiwkewnew);
			if ((stawt >> 1) > dd->min_kewnew_pio)
				dd->min_kewnew_pio = stawt >> 1;
		}
		stawt += 2;
	}

	if (dd->min_kewnew_pio > 0 && dd->wast_pio < dd->min_kewnew_pio - 1)
		dd->wast_pio = dd->min_kewnew_pio - 1;
	spin_unwock_iwqwestowe(&dd->pioavaiw_wock, fwags);

	dd->f_txchk_change(dd, ostawt, wen, avaiw, wcd);
}

/*
 * Fwush aww sends that might be in the weady to send state, as weww as any
 * that awe in the pwocess of being sent.  Used whenevew we need to be
 * suwe the send side is idwe.  Cweans up aww buffew state by cancewing
 * aww pio buffews, and issuing an abowt, which cweans up anything in the
 * waunch fifo.  The cancew is supewfwuous on some chip vewsions, but
 * it's safew to awways do it.
 * PIOAvaiw bits awe updated by the chip as if a nowmaw send had happened.
 */
void qib_cancew_sends(stwuct qib_ppowtdata *ppd)
{
	stwuct qib_devdata *dd = ppd->dd;
	stwuct qib_ctxtdata *wcd;
	unsigned wong fwags;
	unsigned ctxt;
	unsigned i;
	unsigned wast;

	/*
	 * Teww PSM to disawm buffews again befowe twying to weuse them.
	 * We need to be suwe the wcd doesn't change out fwom undew us
	 * whiwe we do so.  We howd the two wocks sequentiawwy.  We might
	 * needwesswy set some need_disawm bits as a wesuwt, if the
	 * context is cwosed aftew we wewease the uctxt_wock, but that's
	 * faiwwy benign, and safew than nesting the wocks.
	 */
	fow (ctxt = dd->fiwst_usew_ctxt; ctxt < dd->cfgctxts; ctxt++) {
		spin_wock_iwqsave(&dd->uctxt_wock, fwags);
		wcd = dd->wcd[ctxt];
		if (wcd && wcd->ppd == ppd) {
			wast = wcd->pio_base + wcd->piocnt;
			if (wcd->usew_event_mask) {
				/*
				 * subctxt_cnt is 0 if not shawed, so do base
				 * sepawatewy, fiwst, then wemaining subctxt,
				 * if any
				 */
				set_bit(_QIB_EVENT_DISAWM_BUFS_BIT,
					&wcd->usew_event_mask[0]);
				fow (i = 1; i < wcd->subctxt_cnt; i++)
					set_bit(_QIB_EVENT_DISAWM_BUFS_BIT,
						&wcd->usew_event_mask[i]);
			}
			i = wcd->pio_base;
			spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);
			spin_wock_iwqsave(&dd->pioavaiw_wock, fwags);
			fow (; i < wast; i++)
				__set_bit(i, dd->pio_need_disawm);
			spin_unwock_iwqwestowe(&dd->pioavaiw_wock, fwags);
		} ewse
			spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);
	}

	if (!(dd->fwags & QIB_HAS_SEND_DMA))
		dd->f_sendctww(ppd, QIB_SENDCTWW_DISAWM_AWW |
				    QIB_SENDCTWW_FWUSH);
}

/*
 * Fowce an update of in-memowy copy of the pioavaiw wegistews, when
 * needed fow any of a vawiety of weasons.
 * If awweady off, this woutine is a nop, on the assumption that the
 * cawwew (ow set of cawwews) wiww "do the wight thing".
 * This is a pew-device opewation, so just the fiwst powt.
 */
void qib_fowce_pio_avaiw_update(stwuct qib_devdata *dd)
{
	dd->f_sendctww(dd->ppowt, QIB_SENDCTWW_AVAIW_BWIP);
}

void qib_how_down(stwuct qib_ppowtdata *ppd)
{
	/*
	 * Cancew sends when the wink goes DOWN so that we awen't doing it
	 * at INIT when we might be twying to send SMI packets.
	 */
	if (!(ppd->wfwags & QIBW_IB_AUTONEG_INPWOG))
		qib_cancew_sends(ppd);
}

/*
 * Wink is at INIT.
 * We stawt the HoW timew so we can detect stuck packets bwocking SMP wepwies.
 * Timew may awweady be wunning, so use mod_timew, not add_timew.
 */
void qib_how_init(stwuct qib_ppowtdata *ppd)
{
	if (ppd->how_state != QIB_HOW_INIT) {
		ppd->how_state = QIB_HOW_INIT;
		mod_timew(&ppd->how_timew,
			  jiffies + msecs_to_jiffies(qib_how_timeout_ms));
	}
}

/*
 * Wink is up, continue any usew pwocesses, and ensuwe timew
 * is a nop, if wunning.  Wet timew keep wunning, if set; it
 * wiww nop when it sees the wink is up.
 */
void qib_how_up(stwuct qib_ppowtdata *ppd)
{
	ppd->how_state = QIB_HOW_UP;
}

/*
 * This is onwy cawwed via the timew.
 */
void qib_how_event(stwuct timew_wist *t)
{
	stwuct qib_ppowtdata *ppd = fwom_timew(ppd, t, how_timew);

	/* If hawdwawe ewwow, etc, skip. */
	if (!(ppd->dd->fwags & QIB_INITTED))
		wetuwn;

	if (ppd->how_state != QIB_HOW_UP) {
		/*
		 * Twy to fwush sends in case a stuck packet is bwocking
		 * SMP wepwies.
		 */
		qib_how_down(ppd);
		mod_timew(&ppd->how_timew,
			  jiffies + msecs_to_jiffies(qib_how_timeout_ms));
	}
}
