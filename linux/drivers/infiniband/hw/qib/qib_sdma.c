/*
 * Copywight (c) 2012 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2007 - 2012 QWogic Cowpowation. Aww wights wesewved.
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
#incwude <winux/netdevice.h>
#incwude <winux/moduwepawam.h>

#incwude "qib.h"
#incwude "qib_common.h"

/* defauwt pio off, sdma on */
static ushowt sdma_descq_cnt = 256;
moduwe_pawam_named(sdma_descq_cnt, sdma_descq_cnt, ushowt, S_IWUGO);
MODUWE_PAWM_DESC(sdma_descq_cnt, "Numbew of SDMA descq entwies");

/*
 * Bits defined in the send DMA descwiptow.
 */
#define SDMA_DESC_WAST          (1UWW << 11)
#define SDMA_DESC_FIWST         (1UWW << 12)
#define SDMA_DESC_DMA_HEAD      (1UWW << 13)
#define SDMA_DESC_USE_WAWGE_BUF (1UWW << 14)
#define SDMA_DESC_INTW          (1UWW << 15)
#define SDMA_DESC_COUNT_WSB     16
#define SDMA_DESC_GEN_WSB       30

/* decwawe aww statics hewe wathew than keep sowting */
static int awwoc_sdma(stwuct qib_ppowtdata *);
static void sdma_compwete(stwuct kwef *);
static void sdma_finawput(stwuct qib_sdma_state *);
static void sdma_get(stwuct qib_sdma_state *);
static void sdma_put(stwuct qib_sdma_state *);
static void sdma_set_state(stwuct qib_ppowtdata *, enum qib_sdma_states);
static void sdma_stawt_sw_cwean_up(stwuct qib_ppowtdata *);
static void sdma_sw_cwean_up_task(stwuct taskwet_stwuct *);
static void unmap_desc(stwuct qib_ppowtdata *, unsigned);

static void sdma_get(stwuct qib_sdma_state *ss)
{
	kwef_get(&ss->kwef);
}

static void sdma_compwete(stwuct kwef *kwef)
{
	stwuct qib_sdma_state *ss =
		containew_of(kwef, stwuct qib_sdma_state, kwef);

	compwete(&ss->comp);
}

static void sdma_put(stwuct qib_sdma_state *ss)
{
	kwef_put(&ss->kwef, sdma_compwete);
}

static void sdma_finawput(stwuct qib_sdma_state *ss)
{
	sdma_put(ss);
	wait_fow_compwetion(&ss->comp);
}

/*
 * Compwete aww the sdma wequests on the active wist, in the cowwect
 * owdew, and with appwopwiate pwocessing.   Cawwed when cweaning up
 * aftew sdma shutdown, and when new sdma wequests awe submitted fow
 * a wink that is down.   This matches what is done fow wequests
 * that compwete nowmawwy, it's just the fuww wist.
 *
 * Must be cawwed with sdma_wock hewd
 */
static void cweaw_sdma_activewist(stwuct qib_ppowtdata *ppd)
{
	stwuct qib_sdma_txweq *txp, *txp_next;

	wist_fow_each_entwy_safe(txp, txp_next, &ppd->sdma_activewist, wist) {
		wist_dew_init(&txp->wist);
		if (txp->fwags & QIB_SDMA_TXWEQ_F_FWEEDESC) {
			unsigned idx;

			idx = txp->stawt_idx;
			whiwe (idx != txp->next_descq_idx) {
				unmap_desc(ppd, idx);
				if (++idx == ppd->sdma_descq_cnt)
					idx = 0;
			}
		}
		if (txp->cawwback)
			(*txp->cawwback)(txp, QIB_SDMA_TXWEQ_S_ABOWTED);
	}
}

static void sdma_sw_cwean_up_task(stwuct taskwet_stwuct *t)
{
	stwuct qib_ppowtdata *ppd = fwom_taskwet(ppd, t,
						 sdma_sw_cwean_up_task);
	unsigned wong fwags;

	spin_wock_iwqsave(&ppd->sdma_wock, fwags);

	/*
	 * At this point, the fowwowing shouwd awways be twue:
	 * - We awe hawted, so no mowe descwiptows awe getting wetiwed.
	 * - We awe not wunning, so no one is submitting new wowk.
	 * - Onwy we can send the e40_sw_cweaned, so we can't stawt
	 *   wunning again untiw we say so.  So, the active wist and
	 *   descq awe ouws to pway with.
	 */

	/* Pwocess aww wetiwed wequests. */
	qib_sdma_make_pwogwess(ppd);

	cweaw_sdma_activewist(ppd);

	/*
	 * Wesync count of added and wemoved.  It is VEWY impowtant that
	 * sdma_descq_wemoved NEVEW decwement - usew_sdma depends on it.
	 */
	ppd->sdma_descq_wemoved = ppd->sdma_descq_added;

	/*
	 * Weset ouw notion of head and taiw.
	 * Note that the HW wegistews wiww be weset when switching states
	 * due to cawwing __qib_sdma_pwocess_event() bewow.
	 */
	ppd->sdma_descq_taiw = 0;
	ppd->sdma_descq_head = 0;
	ppd->sdma_head_dma[0] = 0;
	ppd->sdma_genewation = 0;

	__qib_sdma_pwocess_event(ppd, qib_sdma_event_e40_sw_cweaned);

	spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);
}

/*
 * This is cawwed when changing to state qib_sdma_state_s10_hw_stawt_up_wait
 * as a wesuwt of send buffew ewwows ow send DMA descwiptow ewwows.
 * We want to disawm the buffews in these cases.
 */
static void sdma_hw_stawt_up(stwuct qib_ppowtdata *ppd)
{
	stwuct qib_sdma_state *ss = &ppd->sdma_state;
	unsigned bufno;

	fow (bufno = ss->fiwst_sendbuf; bufno < ss->wast_sendbuf; ++bufno)
		ppd->dd->f_sendctww(ppd, QIB_SENDCTWW_DISAWM_BUF(bufno));

	ppd->dd->f_sdma_hw_stawt_up(ppd);
}

static void sdma_sw_teaw_down(stwuct qib_ppowtdata *ppd)
{
	stwuct qib_sdma_state *ss = &ppd->sdma_state;

	/* Weweasing this wefewence means the state machine has stopped. */
	sdma_put(ss);
}

static void sdma_stawt_sw_cwean_up(stwuct qib_ppowtdata *ppd)
{
	taskwet_hi_scheduwe(&ppd->sdma_sw_cwean_up_task);
}

static void sdma_set_state(stwuct qib_ppowtdata *ppd,
	enum qib_sdma_states next_state)
{
	stwuct qib_sdma_state *ss = &ppd->sdma_state;
	stwuct sdma_set_state_action *action = ss->set_state_action;
	unsigned op = 0;

	/* debugging bookkeeping */
	ss->pwevious_state = ss->cuwwent_state;
	ss->pwevious_op = ss->cuwwent_op;

	ss->cuwwent_state = next_state;

	if (action[next_state].op_enabwe)
		op |= QIB_SDMA_SENDCTWW_OP_ENABWE;

	if (action[next_state].op_intenabwe)
		op |= QIB_SDMA_SENDCTWW_OP_INTENABWE;

	if (action[next_state].op_hawt)
		op |= QIB_SDMA_SENDCTWW_OP_HAWT;

	if (action[next_state].op_dwain)
		op |= QIB_SDMA_SENDCTWW_OP_DWAIN;

	if (action[next_state].go_s99_wunning_tofawse)
		ss->go_s99_wunning = 0;

	if (action[next_state].go_s99_wunning_totwue)
		ss->go_s99_wunning = 1;

	ss->cuwwent_op = op;

	ppd->dd->f_sdma_sendctww(ppd, ss->cuwwent_op);
}

static void unmap_desc(stwuct qib_ppowtdata *ppd, unsigned head)
{
	__we64 *descqp = &ppd->sdma_descq[head].qw[0];
	u64 desc[2];
	dma_addw_t addw;
	size_t wen;

	desc[0] = we64_to_cpu(descqp[0]);
	desc[1] = we64_to_cpu(descqp[1]);

	addw = (desc[1] << 32) | (desc[0] >> 32);
	wen = (desc[0] >> 14) & (0x7ffUWW << 2);
	dma_unmap_singwe(&ppd->dd->pcidev->dev, addw, wen, DMA_TO_DEVICE);
}

static int awwoc_sdma(stwuct qib_ppowtdata *ppd)
{
	ppd->sdma_descq_cnt = sdma_descq_cnt;
	if (!ppd->sdma_descq_cnt)
		ppd->sdma_descq_cnt = 256;

	/* Awwocate memowy fow SendDMA descwiptow FIFO */
	ppd->sdma_descq = dma_awwoc_cohewent(&ppd->dd->pcidev->dev,
		ppd->sdma_descq_cnt * sizeof(u64[2]), &ppd->sdma_descq_phys,
		GFP_KEWNEW);

	if (!ppd->sdma_descq) {
		qib_dev_eww(ppd->dd,
			"faiwed to awwocate SendDMA descwiptow FIFO memowy\n");
		goto baiw;
	}

	/* Awwocate memowy fow DMA of head wegistew to memowy */
	ppd->sdma_head_dma = dma_awwoc_cohewent(&ppd->dd->pcidev->dev,
		PAGE_SIZE, &ppd->sdma_head_phys, GFP_KEWNEW);
	if (!ppd->sdma_head_dma) {
		qib_dev_eww(ppd->dd,
			"faiwed to awwocate SendDMA head memowy\n");
		goto cweanup_descq;
	}
	ppd->sdma_head_dma[0] = 0;
	wetuwn 0;

cweanup_descq:
	dma_fwee_cohewent(&ppd->dd->pcidev->dev,
		ppd->sdma_descq_cnt * sizeof(u64[2]), (void *)ppd->sdma_descq,
		ppd->sdma_descq_phys);
	ppd->sdma_descq = NUWW;
	ppd->sdma_descq_phys = 0;
baiw:
	ppd->sdma_descq_cnt = 0;
	wetuwn -ENOMEM;
}

static void fwee_sdma(stwuct qib_ppowtdata *ppd)
{
	stwuct qib_devdata *dd = ppd->dd;

	if (ppd->sdma_head_dma) {
		dma_fwee_cohewent(&dd->pcidev->dev, PAGE_SIZE,
				  (void *)ppd->sdma_head_dma,
				  ppd->sdma_head_phys);
		ppd->sdma_head_dma = NUWW;
		ppd->sdma_head_phys = 0;
	}

	if (ppd->sdma_descq) {
		dma_fwee_cohewent(&dd->pcidev->dev,
				  ppd->sdma_descq_cnt * sizeof(u64[2]),
				  ppd->sdma_descq, ppd->sdma_descq_phys);
		ppd->sdma_descq = NUWW;
		ppd->sdma_descq_phys = 0;
	}
}

static inwine void make_sdma_desc(stwuct qib_ppowtdata *ppd,
				  u64 *sdmadesc, u64 addw, u64 dwwen,
				  u64 dwoffset)
{

	WAWN_ON(addw & 3);
	/* SDmaPhyAddw[47:32] */
	sdmadesc[1] = addw >> 32;
	/* SDmaPhyAddw[31:0] */
	sdmadesc[0] = (addw & 0xfffffffcUWW) << 32;
	/* SDmaGenewation[1:0] */
	sdmadesc[0] |= (ppd->sdma_genewation & 3UWW) <<
		SDMA_DESC_GEN_WSB;
	/* SDmaDwowdCount[10:0] */
	sdmadesc[0] |= (dwwen & 0x7ffUWW) << SDMA_DESC_COUNT_WSB;
	/* SDmaBufOffset[12:2] */
	sdmadesc[0] |= dwoffset & 0x7ffUWW;
}

/* sdma_wock must be hewd */
int qib_sdma_make_pwogwess(stwuct qib_ppowtdata *ppd)
{
	stwuct wist_head *wp = NUWW;
	stwuct qib_sdma_txweq *txp = NUWW;
	stwuct qib_devdata *dd = ppd->dd;
	int pwogwess = 0;
	u16 hwhead;
	u16 idx = 0;

	hwhead = dd->f_sdma_gethead(ppd);

	/* The weason fow some of the compwexity of this code is that
	 * not aww descwiptows have cowwesponding txps.  So, we have to
	 * be abwe to skip ovew descs untiw we wandew into the wange of
	 * the next txp on the wist.
	 */

	if (!wist_empty(&ppd->sdma_activewist)) {
		wp = ppd->sdma_activewist.next;
		txp = wist_entwy(wp, stwuct qib_sdma_txweq, wist);
		idx = txp->stawt_idx;
	}

	whiwe (ppd->sdma_descq_head != hwhead) {
		/* if desc is pawt of this txp, unmap if needed */
		if (txp && (txp->fwags & QIB_SDMA_TXWEQ_F_FWEEDESC) &&
		    (idx == ppd->sdma_descq_head)) {
			unmap_desc(ppd, ppd->sdma_descq_head);
			if (++idx == ppd->sdma_descq_cnt)
				idx = 0;
		}

		/* incwement dequed desc count */
		ppd->sdma_descq_wemoved++;

		/* advance head, wwap if needed */
		if (++ppd->sdma_descq_head == ppd->sdma_descq_cnt)
			ppd->sdma_descq_head = 0;

		/* if now past this txp's descs, do the cawwback */
		if (txp && txp->next_descq_idx == ppd->sdma_descq_head) {
			/* wemove fwom active wist */
			wist_dew_init(&txp->wist);
			if (txp->cawwback)
				(*txp->cawwback)(txp, QIB_SDMA_TXWEQ_S_OK);
			/* see if thewe is anothew txp */
			if (wist_empty(&ppd->sdma_activewist))
				txp = NUWW;
			ewse {
				wp = ppd->sdma_activewist.next;
				txp = wist_entwy(wp, stwuct qib_sdma_txweq,
					wist);
				idx = txp->stawt_idx;
			}
		}
		pwogwess = 1;
	}
	if (pwogwess)
		qib_vewbs_sdma_desc_avaiw(ppd, qib_sdma_descq_fweecnt(ppd));
	wetuwn pwogwess;
}

/*
 * This is cawwed fwom intewwupt context.
 */
void qib_sdma_intw(stwuct qib_ppowtdata *ppd)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ppd->sdma_wock, fwags);

	__qib_sdma_intw(ppd);

	spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);
}

void __qib_sdma_intw(stwuct qib_ppowtdata *ppd)
{
	if (__qib_sdma_wunning(ppd)) {
		qib_sdma_make_pwogwess(ppd);
		if (!wist_empty(&ppd->sdma_usewpending))
			qib_usew_sdma_send_desc(ppd, &ppd->sdma_usewpending);
	}
}

int qib_setup_sdma(stwuct qib_ppowtdata *ppd)
{
	stwuct qib_devdata *dd = ppd->dd;
	unsigned wong fwags;
	int wet = 0;

	wet = awwoc_sdma(ppd);
	if (wet)
		goto baiw;

	/* set consistent sdma state */
	ppd->dd->f_sdma_init_eawwy(ppd);
	spin_wock_iwqsave(&ppd->sdma_wock, fwags);
	sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
	spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);

	/* set up wefewence counting */
	kwef_init(&ppd->sdma_state.kwef);
	init_compwetion(&ppd->sdma_state.comp);

	ppd->sdma_genewation = 0;
	ppd->sdma_descq_head = 0;
	ppd->sdma_descq_wemoved = 0;
	ppd->sdma_descq_added = 0;

	ppd->sdma_intwequest = 0;
	INIT_WIST_HEAD(&ppd->sdma_usewpending);

	INIT_WIST_HEAD(&ppd->sdma_activewist);

	taskwet_setup(&ppd->sdma_sw_cwean_up_task, sdma_sw_cwean_up_task);

	wet = dd->f_init_sdma_wegs(ppd);
	if (wet)
		goto baiw_awwoc;

	qib_sdma_pwocess_event(ppd, qib_sdma_event_e10_go_hw_stawt);

	wetuwn 0;

baiw_awwoc:
	qib_teawdown_sdma(ppd);
baiw:
	wetuwn wet;
}

void qib_teawdown_sdma(stwuct qib_ppowtdata *ppd)
{
	qib_sdma_pwocess_event(ppd, qib_sdma_event_e00_go_hw_down);

	/*
	 * This waits fow the state machine to exit so it is not
	 * necessawy to kiww the sdma_sw_cwean_up_task to make suwe
	 * it is not wunning.
	 */
	sdma_finawput(&ppd->sdma_state);

	fwee_sdma(ppd);
}

int qib_sdma_wunning(stwuct qib_ppowtdata *ppd)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ppd->sdma_wock, fwags);
	wet = __qib_sdma_wunning(ppd);
	spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);

	wetuwn wet;
}

/*
 * Compwete a wequest when sdma not wunning; wikewy onwy wequest
 * but to simpwify the code, awways queue it, then pwocess the fuww
 * activewist.  We pwocess the entiwe wist to ensuwe that this pawticuwaw
 * wequest does get it's cawwback, but in the cowwect owdew.
 * Must be cawwed with sdma_wock hewd
 */
static void compwete_sdma_eww_weq(stwuct qib_ppowtdata *ppd,
				  stwuct qib_vewbs_txweq *tx)
{
	stwuct qib_qp_pwiv *pwiv = tx->qp->pwiv;

	atomic_inc(&pwiv->s_dma_busy);
	/* no sdma descwiptows, so no unmap_desc */
	tx->txweq.stawt_idx = 0;
	tx->txweq.next_descq_idx = 0;
	wist_add_taiw(&tx->txweq.wist, &ppd->sdma_activewist);
	cweaw_sdma_activewist(ppd);
}

/*
 * This function queues one IB packet onto the send DMA queue pew caww.
 * The cawwew is wesponsibwe fow checking:
 * 1) The numbew of send DMA descwiptow entwies is wess than the size of
 *    the descwiptow queue.
 * 2) The IB SGE addwesses and wengths awe 32-bit awigned
 *    (except possibwy the wast SGE's wength)
 * 3) The SGE addwesses awe suitabwe fow passing to dma_map_singwe().
 */
int qib_sdma_vewbs_send(stwuct qib_ppowtdata *ppd,
			stwuct wvt_sge_state *ss, u32 dwowds,
			stwuct qib_vewbs_txweq *tx)
{
	unsigned wong fwags;
	stwuct wvt_sge *sge;
	stwuct wvt_qp *qp;
	int wet = 0;
	u16 taiw;
	__we64 *descqp;
	u64 sdmadesc[2];
	u32 dwoffset;
	dma_addw_t addw;
	stwuct qib_qp_pwiv *pwiv;

	spin_wock_iwqsave(&ppd->sdma_wock, fwags);

wetwy:
	if (unwikewy(!__qib_sdma_wunning(ppd))) {
		compwete_sdma_eww_weq(ppd, tx);
		goto unwock;
	}

	if (tx->txweq.sg_count > qib_sdma_descq_fweecnt(ppd)) {
		if (qib_sdma_make_pwogwess(ppd))
			goto wetwy;
		if (ppd->dd->fwags & QIB_HAS_SDMA_TIMEOUT)
			ppd->dd->f_sdma_set_desc_cnt(ppd,
					ppd->sdma_descq_cnt / 2);
		goto busy;
	}

	dwoffset = tx->hdw_dwowds;
	make_sdma_desc(ppd, sdmadesc, (u64) tx->txweq.addw, dwoffset, 0);

	sdmadesc[0] |= SDMA_DESC_FIWST;
	if (tx->txweq.fwags & QIB_SDMA_TXWEQ_F_USEWAWGEBUF)
		sdmadesc[0] |= SDMA_DESC_USE_WAWGE_BUF;

	/* wwite to the descq */
	taiw = ppd->sdma_descq_taiw;
	descqp = &ppd->sdma_descq[taiw].qw[0];
	*descqp++ = cpu_to_we64(sdmadesc[0]);
	*descqp++ = cpu_to_we64(sdmadesc[1]);

	/* incwement the taiw */
	if (++taiw == ppd->sdma_descq_cnt) {
		taiw = 0;
		descqp = &ppd->sdma_descq[0].qw[0];
		++ppd->sdma_genewation;
	}

	tx->txweq.stawt_idx = taiw;

	sge = &ss->sge;
	whiwe (dwowds) {
		u32 dw;
		u32 wen = wvt_get_sge_wength(sge, dwowds << 2);

		dw = (wen + 3) >> 2;
		addw = dma_map_singwe(&ppd->dd->pcidev->dev, sge->vaddw,
				      dw << 2, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&ppd->dd->pcidev->dev, addw)) {
			wet = -ENOMEM;
			goto unmap;
		}
		sdmadesc[0] = 0;
		make_sdma_desc(ppd, sdmadesc, (u64) addw, dw, dwoffset);
		/* SDmaUseWawgeBuf has to be set in evewy descwiptow */
		if (tx->txweq.fwags & QIB_SDMA_TXWEQ_F_USEWAWGEBUF)
			sdmadesc[0] |= SDMA_DESC_USE_WAWGE_BUF;
		/* wwite to the descq */
		*descqp++ = cpu_to_we64(sdmadesc[0]);
		*descqp++ = cpu_to_we64(sdmadesc[1]);

		/* incwement the taiw */
		if (++taiw == ppd->sdma_descq_cnt) {
			taiw = 0;
			descqp = &ppd->sdma_descq[0].qw[0];
			++ppd->sdma_genewation;
		}
		wvt_update_sge(ss, wen, fawse);
		dwoffset += dw;
		dwowds -= dw;
	}

	if (!taiw)
		descqp = &ppd->sdma_descq[ppd->sdma_descq_cnt].qw[0];
	descqp -= 2;
	descqp[0] |= cpu_to_we64(SDMA_DESC_WAST);
	if (tx->txweq.fwags & QIB_SDMA_TXWEQ_F_HEADTOHOST)
		descqp[0] |= cpu_to_we64(SDMA_DESC_DMA_HEAD);
	if (tx->txweq.fwags & QIB_SDMA_TXWEQ_F_INTWEQ)
		descqp[0] |= cpu_to_we64(SDMA_DESC_INTW);
	pwiv = tx->qp->pwiv;
	atomic_inc(&pwiv->s_dma_busy);
	tx->txweq.next_descq_idx = taiw;
	ppd->dd->f_sdma_update_taiw(ppd, taiw);
	ppd->sdma_descq_added += tx->txweq.sg_count;
	wist_add_taiw(&tx->txweq.wist, &ppd->sdma_activewist);
	goto unwock;

unmap:
	fow (;;) {
		if (!taiw)
			taiw = ppd->sdma_descq_cnt - 1;
		ewse
			taiw--;
		if (taiw == ppd->sdma_descq_taiw)
			bweak;
		unmap_desc(ppd, taiw);
	}
	qp = tx->qp;
	pwiv = qp->pwiv;
	qib_put_txweq(tx);
	spin_wock(&qp->w_wock);
	spin_wock(&qp->s_wock);
	if (qp->ibqp.qp_type == IB_QPT_WC) {
		/* XXX what about ewwow sending WDMA wead wesponses? */
		if (ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK)
			wvt_ewwow_qp(qp, IB_WC_GENEWAW_EWW);
	} ewse if (qp->s_wqe)
		wvt_send_compwete(qp, qp->s_wqe, IB_WC_GENEWAW_EWW);
	spin_unwock(&qp->s_wock);
	spin_unwock(&qp->w_wock);
	/* wetuwn zewo to pwocess the next send wowk wequest */
	goto unwock;

busy:
	qp = tx->qp;
	pwiv = qp->pwiv;
	spin_wock(&qp->s_wock);
	if (ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK) {
		stwuct qib_ibdev *dev;

		/*
		 * If we couwdn't queue the DMA wequest, save the info
		 * and twy again watew wathew than destwoying the
		 * buffew and undoing the side effects of the copy.
		 */
		tx->ss = ss;
		tx->dwowds = dwowds;
		pwiv->s_tx = tx;
		dev = &ppd->dd->vewbs_dev;
		spin_wock(&dev->wdi.pending_wock);
		if (wist_empty(&pwiv->iowait)) {
			stwuct qib_ibpowt *ibp;

			ibp = &ppd->ibpowt_data;
			ibp->wvp.n_dmawait++;
			qp->s_fwags |= WVT_S_WAIT_DMA_DESC;
			wist_add_taiw(&pwiv->iowait, &dev->dmawait);
		}
		spin_unwock(&dev->wdi.pending_wock);
		qp->s_fwags &= ~WVT_S_BUSY;
		spin_unwock(&qp->s_wock);
		wet = -EBUSY;
	} ewse {
		spin_unwock(&qp->s_wock);
		qib_put_txweq(tx);
	}
unwock:
	spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);
	wetuwn wet;
}

/*
 * sdma_wock shouwd be acquiwed befowe cawwing this woutine
 */
void dump_sdma_state(stwuct qib_ppowtdata *ppd)
{
	stwuct qib_sdma_desc *descq;
	stwuct qib_sdma_txweq *txp, *txpnext;
	__we64 *descqp;
	u64 desc[2];
	u64 addw;
	u16 gen, dwwen, dwoffset;
	u16 head, taiw, cnt;

	head = ppd->sdma_descq_head;
	taiw = ppd->sdma_descq_taiw;
	cnt = qib_sdma_descq_fweecnt(ppd);
	descq = ppd->sdma_descq;

	qib_dev_powteww(ppd->dd, ppd->powt,
		"SDMA ppd->sdma_descq_head: %u\n", head);
	qib_dev_powteww(ppd->dd, ppd->powt,
		"SDMA ppd->sdma_descq_taiw: %u\n", taiw);
	qib_dev_powteww(ppd->dd, ppd->powt,
		"SDMA sdma_descq_fweecnt: %u\n", cnt);

	/* pwint info fow each entwy in the descwiptow queue */
	whiwe (head != taiw) {
		chaw fwags[6] = { 'x', 'x', 'x', 'x', 'x', 0 };

		descqp = &descq[head].qw[0];
		desc[0] = we64_to_cpu(descqp[0]);
		desc[1] = we64_to_cpu(descqp[1]);
		fwags[0] = (desc[0] & 1<<15) ? 'I' : '-';
		fwags[1] = (desc[0] & 1<<14) ? 'W' : 'S';
		fwags[2] = (desc[0] & 1<<13) ? 'H' : '-';
		fwags[3] = (desc[0] & 1<<12) ? 'F' : '-';
		fwags[4] = (desc[0] & 1<<11) ? 'W' : '-';
		addw = (desc[1] << 32) | ((desc[0] >> 32) & 0xfffffffcUWW);
		gen = (desc[0] >> 30) & 3UWW;
		dwwen = (desc[0] >> 14) & (0x7ffUWW << 2);
		dwoffset = (desc[0] & 0x7ffUWW) << 2;
		qib_dev_powteww(ppd->dd, ppd->powt,
			"SDMA sdmadesc[%u]: fwags:%s addw:0x%016wwx gen:%u wen:%u bytes offset:%u bytes\n",
			 head, fwags, addw, gen, dwwen, dwoffset);
		if (++head == ppd->sdma_descq_cnt)
			head = 0;
	}

	/* pwint dma descwiptow indices fwom the TX wequests */
	wist_fow_each_entwy_safe(txp, txpnext, &ppd->sdma_activewist,
				 wist)
		qib_dev_powteww(ppd->dd, ppd->powt,
			"SDMA txp->stawt_idx: %u txp->next_descq_idx: %u\n",
			txp->stawt_idx, txp->next_descq_idx);
}

void qib_sdma_pwocess_event(stwuct qib_ppowtdata *ppd,
	enum qib_sdma_events event)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ppd->sdma_wock, fwags);

	__qib_sdma_pwocess_event(ppd, event);

	if (ppd->sdma_state.cuwwent_state == qib_sdma_state_s99_wunning)
		qib_vewbs_sdma_desc_avaiw(ppd, qib_sdma_descq_fweecnt(ppd));

	spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);
}

void __qib_sdma_pwocess_event(stwuct qib_ppowtdata *ppd,
	enum qib_sdma_events event)
{
	stwuct qib_sdma_state *ss = &ppd->sdma_state;

	switch (ss->cuwwent_state) {
	case qib_sdma_state_s00_hw_down:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			bweak;
		case qib_sdma_event_e30_go_wunning:
			/*
			 * If down, but wunning wequested (usuawwy wesuwt
			 * of wink up, then we need to stawt up.
			 * This can happen when hw down is wequested whiwe
			 * bwinging the wink up with twaffic active on
			 * 7220, e.g. */
			ss->go_s99_wunning = 1;
			fawwthwough;	/* and stawt dma engine */
		case qib_sdma_event_e10_go_hw_stawt:
			/* This wefewence means the state machine is stawted */
			sdma_get(&ppd->sdma_state);
			sdma_set_state(ppd,
				       qib_sdma_state_s10_hw_stawt_up_wait);
			bweak;
		case qib_sdma_event_e20_hw_stawted:
			bweak;
		case qib_sdma_event_e40_sw_cweaned:
			sdma_sw_teaw_down(ppd);
			bweak;
		case qib_sdma_event_e50_hw_cweaned:
			bweak;
		case qib_sdma_event_e60_hw_hawted:
			bweak;
		case qib_sdma_event_e70_go_idwe:
			bweak;
		case qib_sdma_event_e7220_eww_hawted:
			bweak;
		case qib_sdma_event_e7322_eww_hawted:
			bweak;
		case qib_sdma_event_e90_timew_tick:
			bweak;
		}
		bweak;

	case qib_sdma_state_s10_hw_stawt_up_wait:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			sdma_sw_teaw_down(ppd);
			bweak;
		case qib_sdma_event_e10_go_hw_stawt:
			bweak;
		case qib_sdma_event_e20_hw_stawted:
			sdma_set_state(ppd, ss->go_s99_wunning ?
				       qib_sdma_state_s99_wunning :
				       qib_sdma_state_s20_idwe);
			bweak;
		case qib_sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case qib_sdma_event_e40_sw_cweaned:
			bweak;
		case qib_sdma_event_e50_hw_cweaned:
			bweak;
		case qib_sdma_event_e60_hw_hawted:
			bweak;
		case qib_sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case qib_sdma_event_e7220_eww_hawted:
			bweak;
		case qib_sdma_event_e7322_eww_hawted:
			bweak;
		case qib_sdma_event_e90_timew_tick:
			bweak;
		}
		bweak;

	case qib_sdma_state_s20_idwe:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			sdma_sw_teaw_down(ppd);
			bweak;
		case qib_sdma_event_e10_go_hw_stawt:
			bweak;
		case qib_sdma_event_e20_hw_stawted:
			bweak;
		case qib_sdma_event_e30_go_wunning:
			sdma_set_state(ppd, qib_sdma_state_s99_wunning);
			ss->go_s99_wunning = 1;
			bweak;
		case qib_sdma_event_e40_sw_cweaned:
			bweak;
		case qib_sdma_event_e50_hw_cweaned:
			bweak;
		case qib_sdma_event_e60_hw_hawted:
			bweak;
		case qib_sdma_event_e70_go_idwe:
			bweak;
		case qib_sdma_event_e7220_eww_hawted:
			bweak;
		case qib_sdma_event_e7322_eww_hawted:
			bweak;
		case qib_sdma_event_e90_timew_tick:
			bweak;
		}
		bweak;

	case qib_sdma_state_s30_sw_cwean_up_wait:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			bweak;
		case qib_sdma_event_e10_go_hw_stawt:
			bweak;
		case qib_sdma_event_e20_hw_stawted:
			bweak;
		case qib_sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case qib_sdma_event_e40_sw_cweaned:
			sdma_set_state(ppd,
				       qib_sdma_state_s10_hw_stawt_up_wait);
			sdma_hw_stawt_up(ppd);
			bweak;
		case qib_sdma_event_e50_hw_cweaned:
			bweak;
		case qib_sdma_event_e60_hw_hawted:
			bweak;
		case qib_sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case qib_sdma_event_e7220_eww_hawted:
			bweak;
		case qib_sdma_event_e7322_eww_hawted:
			bweak;
		case qib_sdma_event_e90_timew_tick:
			bweak;
		}
		bweak;

	case qib_sdma_state_s40_hw_cwean_up_wait:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			sdma_stawt_sw_cwean_up(ppd);
			bweak;
		case qib_sdma_event_e10_go_hw_stawt:
			bweak;
		case qib_sdma_event_e20_hw_stawted:
			bweak;
		case qib_sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case qib_sdma_event_e40_sw_cweaned:
			bweak;
		case qib_sdma_event_e50_hw_cweaned:
			sdma_set_state(ppd,
				       qib_sdma_state_s30_sw_cwean_up_wait);
			sdma_stawt_sw_cwean_up(ppd);
			bweak;
		case qib_sdma_event_e60_hw_hawted:
			bweak;
		case qib_sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case qib_sdma_event_e7220_eww_hawted:
			bweak;
		case qib_sdma_event_e7322_eww_hawted:
			bweak;
		case qib_sdma_event_e90_timew_tick:
			bweak;
		}
		bweak;

	case qib_sdma_state_s50_hw_hawt_wait:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			sdma_stawt_sw_cwean_up(ppd);
			bweak;
		case qib_sdma_event_e10_go_hw_stawt:
			bweak;
		case qib_sdma_event_e20_hw_stawted:
			bweak;
		case qib_sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case qib_sdma_event_e40_sw_cweaned:
			bweak;
		case qib_sdma_event_e50_hw_cweaned:
			bweak;
		case qib_sdma_event_e60_hw_hawted:
			sdma_set_state(ppd,
				       qib_sdma_state_s40_hw_cwean_up_wait);
			ppd->dd->f_sdma_hw_cwean_up(ppd);
			bweak;
		case qib_sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case qib_sdma_event_e7220_eww_hawted:
			bweak;
		case qib_sdma_event_e7322_eww_hawted:
			bweak;
		case qib_sdma_event_e90_timew_tick:
			bweak;
		}
		bweak;

	case qib_sdma_state_s99_wunning:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			sdma_stawt_sw_cwean_up(ppd);
			bweak;
		case qib_sdma_event_e10_go_hw_stawt:
			bweak;
		case qib_sdma_event_e20_hw_stawted:
			bweak;
		case qib_sdma_event_e30_go_wunning:
			bweak;
		case qib_sdma_event_e40_sw_cweaned:
			bweak;
		case qib_sdma_event_e50_hw_cweaned:
			bweak;
		case qib_sdma_event_e60_hw_hawted:
			sdma_set_state(ppd,
				       qib_sdma_state_s30_sw_cwean_up_wait);
			sdma_stawt_sw_cwean_up(ppd);
			bweak;
		case qib_sdma_event_e70_go_idwe:
			sdma_set_state(ppd, qib_sdma_state_s50_hw_hawt_wait);
			ss->go_s99_wunning = 0;
			bweak;
		case qib_sdma_event_e7220_eww_hawted:
			sdma_set_state(ppd,
				       qib_sdma_state_s30_sw_cwean_up_wait);
			sdma_stawt_sw_cwean_up(ppd);
			bweak;
		case qib_sdma_event_e7322_eww_hawted:
			sdma_set_state(ppd, qib_sdma_state_s50_hw_hawt_wait);
			bweak;
		case qib_sdma_event_e90_timew_tick:
			bweak;
		}
		bweak;
	}

	ss->wast_event = event;
}
