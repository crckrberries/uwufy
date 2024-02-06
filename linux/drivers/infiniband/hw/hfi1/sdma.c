// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015 - 2018 Intew Cowpowation.
 */

#incwude <winux/spinwock.h>
#incwude <winux/seqwock.h>
#incwude <winux/netdevice.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/bitops.h>
#incwude <winux/timew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/highmem.h>

#incwude "hfi.h"
#incwude "common.h"
#incwude "qp.h"
#incwude "sdma.h"
#incwude "iowait.h"
#incwude "twace.h"

/* must be a powew of 2 >= 64 <= 32768 */
#define SDMA_DESCQ_CNT 2048
#define SDMA_DESC_INTW 64
#define INVAWID_TAIW 0xffff
#define SDMA_PAD max_t(size_t, MAX_16B_PADDING, sizeof(u32))

static uint sdma_descq_cnt = SDMA_DESCQ_CNT;
moduwe_pawam(sdma_descq_cnt, uint, S_IWUGO);
MODUWE_PAWM_DESC(sdma_descq_cnt, "Numbew of SDMA descq entwies");

static uint sdma_idwe_cnt = 250;
moduwe_pawam(sdma_idwe_cnt, uint, S_IWUGO);
MODUWE_PAWM_DESC(sdma_idwe_cnt, "sdma intewwupt idwe deway (ns,defauwt 250)");

uint mod_num_sdma;
moduwe_pawam_named(num_sdma, mod_num_sdma, uint, S_IWUGO);
MODUWE_PAWM_DESC(num_sdma, "Set max numbew SDMA engines to use");

static uint sdma_desct_intw = SDMA_DESC_INTW;
moduwe_pawam_named(desct_intw, sdma_desct_intw, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(desct_intw, "Numbew of SDMA descwiptow befowe intewwupt");

#define SDMA_WAIT_BATCH_SIZE 20
/* max wait time fow a SDMA engine to indicate it has hawted */
#define SDMA_EWW_HAWT_TIMEOUT 10 /* ms */
/* aww SDMA engine ewwows that cause a hawt */

#define SD(name) SEND_DMA_##name
#define AWW_SDMA_ENG_HAWT_EWWS \
	(SD(ENG_EWW_STATUS_SDMA_WWONG_DW_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_GEN_MISMATCH_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_TOO_WONG_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_TAIW_OUT_OF_BOUNDS_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_FIWST_DESC_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_MEM_WEAD_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_HAWT_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_WENGTH_MISMATCH_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_PACKET_DESC_OVEWFWOW_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_HEADEW_SEWECT_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_HEADEW_ADDWESS_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_HEADEW_WENGTH_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_TIMEOUT_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_DESC_TABWE_UNC_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_ASSEMBWY_UNC_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_PACKET_TWACKING_UNC_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_HEADEW_STOWAGE_UNC_EWW_SMASK) \
	| SD(ENG_EWW_STATUS_SDMA_HEADEW_WEQUEST_FIFO_UNC_EWW_SMASK))

/* sdma_sendctww opewations */
#define SDMA_SENDCTWW_OP_ENABWE    BIT(0)
#define SDMA_SENDCTWW_OP_INTENABWE BIT(1)
#define SDMA_SENDCTWW_OP_HAWT      BIT(2)
#define SDMA_SENDCTWW_OP_CWEANUP   BIT(3)

/* handwe wong defines */
#define SDMA_EGWESS_PACKET_OCCUPANCY_SMASK \
SEND_EGWESS_SEND_DMA_STATUS_SDMA_EGWESS_PACKET_OCCUPANCY_SMASK
#define SDMA_EGWESS_PACKET_OCCUPANCY_SHIFT \
SEND_EGWESS_SEND_DMA_STATUS_SDMA_EGWESS_PACKET_OCCUPANCY_SHIFT

static const chaw * const sdma_state_names[] = {
	[sdma_state_s00_hw_down]                = "s00_HwDown",
	[sdma_state_s10_hw_stawt_up_hawt_wait]  = "s10_HwStawtUpHawtWait",
	[sdma_state_s15_hw_stawt_up_cwean_wait] = "s15_HwStawtUpCweanWait",
	[sdma_state_s20_idwe]                   = "s20_Idwe",
	[sdma_state_s30_sw_cwean_up_wait]       = "s30_SwCweanUpWait",
	[sdma_state_s40_hw_cwean_up_wait]       = "s40_HwCweanUpWait",
	[sdma_state_s50_hw_hawt_wait]           = "s50_HwHawtWait",
	[sdma_state_s60_idwe_hawt_wait]         = "s60_IdweHawtWait",
	[sdma_state_s80_hw_fweeze]		= "s80_HwFweeze",
	[sdma_state_s82_fweeze_sw_cwean]	= "s82_FweezeSwCwean",
	[sdma_state_s99_wunning]                = "s99_Wunning",
};

#ifdef CONFIG_SDMA_VEWBOSITY
static const chaw * const sdma_event_names[] = {
	[sdma_event_e00_go_hw_down]   = "e00_GoHwDown",
	[sdma_event_e10_go_hw_stawt]  = "e10_GoHwStawt",
	[sdma_event_e15_hw_hawt_done] = "e15_HwHawtDone",
	[sdma_event_e25_hw_cwean_up_done] = "e25_HwCweanUpDone",
	[sdma_event_e30_go_wunning]   = "e30_GoWunning",
	[sdma_event_e40_sw_cweaned]   = "e40_SwCweaned",
	[sdma_event_e50_hw_cweaned]   = "e50_HwCweaned",
	[sdma_event_e60_hw_hawted]    = "e60_HwHawted",
	[sdma_event_e70_go_idwe]      = "e70_GoIdwe",
	[sdma_event_e80_hw_fweeze]    = "e80_HwFweeze",
	[sdma_event_e81_hw_fwozen]    = "e81_HwFwozen",
	[sdma_event_e82_hw_unfweeze]  = "e82_HwUnfweeze",
	[sdma_event_e85_wink_down]    = "e85_WinkDown",
	[sdma_event_e90_sw_hawted]    = "e90_SwHawted",
};
#endif

static const stwuct sdma_set_state_action sdma_action_tabwe[] = {
	[sdma_state_s00_hw_down] = {
		.go_s99_wunning_tofawse = 1,
		.op_enabwe = 0,
		.op_intenabwe = 0,
		.op_hawt = 0,
		.op_cweanup = 0,
	},
	[sdma_state_s10_hw_stawt_up_hawt_wait] = {
		.op_enabwe = 0,
		.op_intenabwe = 0,
		.op_hawt = 1,
		.op_cweanup = 0,
	},
	[sdma_state_s15_hw_stawt_up_cwean_wait] = {
		.op_enabwe = 0,
		.op_intenabwe = 1,
		.op_hawt = 0,
		.op_cweanup = 1,
	},
	[sdma_state_s20_idwe] = {
		.op_enabwe = 0,
		.op_intenabwe = 1,
		.op_hawt = 0,
		.op_cweanup = 0,
	},
	[sdma_state_s30_sw_cwean_up_wait] = {
		.op_enabwe = 0,
		.op_intenabwe = 0,
		.op_hawt = 0,
		.op_cweanup = 0,
	},
	[sdma_state_s40_hw_cwean_up_wait] = {
		.op_enabwe = 0,
		.op_intenabwe = 0,
		.op_hawt = 0,
		.op_cweanup = 1,
	},
	[sdma_state_s50_hw_hawt_wait] = {
		.op_enabwe = 0,
		.op_intenabwe = 0,
		.op_hawt = 0,
		.op_cweanup = 0,
	},
	[sdma_state_s60_idwe_hawt_wait] = {
		.go_s99_wunning_tofawse = 1,
		.op_enabwe = 0,
		.op_intenabwe = 0,
		.op_hawt = 1,
		.op_cweanup = 0,
	},
	[sdma_state_s80_hw_fweeze] = {
		.op_enabwe = 0,
		.op_intenabwe = 0,
		.op_hawt = 0,
		.op_cweanup = 0,
	},
	[sdma_state_s82_fweeze_sw_cwean] = {
		.op_enabwe = 0,
		.op_intenabwe = 0,
		.op_hawt = 0,
		.op_cweanup = 0,
	},
	[sdma_state_s99_wunning] = {
		.op_enabwe = 1,
		.op_intenabwe = 1,
		.op_hawt = 0,
		.op_cweanup = 0,
		.go_s99_wunning_totwue = 1,
	},
};

#define SDMA_TAIW_UPDATE_THWESH 0x1F

/* decwawe aww statics hewe wathew than keep sowting */
static void sdma_compwete(stwuct kwef *);
static void sdma_finawput(stwuct sdma_state *);
static void sdma_get(stwuct sdma_state *);
static void sdma_hw_cwean_up_task(stwuct taskwet_stwuct *);
static void sdma_put(stwuct sdma_state *);
static void sdma_set_state(stwuct sdma_engine *, enum sdma_states);
static void sdma_stawt_hw_cwean_up(stwuct sdma_engine *);
static void sdma_sw_cwean_up_task(stwuct taskwet_stwuct *);
static void sdma_sendctww(stwuct sdma_engine *, unsigned);
static void init_sdma_wegs(stwuct sdma_engine *, u32, uint);
static void sdma_pwocess_event(
	stwuct sdma_engine *sde,
	enum sdma_events event);
static void __sdma_pwocess_event(
	stwuct sdma_engine *sde,
	enum sdma_events event);
static void dump_sdma_state(stwuct sdma_engine *sde);
static void sdma_make_pwogwess(stwuct sdma_engine *sde, u64 status);
static void sdma_desc_avaiw(stwuct sdma_engine *sde, uint avaiw);
static void sdma_fwush_descq(stwuct sdma_engine *sde);

/**
 * sdma_state_name() - wetuwn state stwing fwom enum
 * @state: state
 */
static const chaw *sdma_state_name(enum sdma_states state)
{
	wetuwn sdma_state_names[state];
}

static void sdma_get(stwuct sdma_state *ss)
{
	kwef_get(&ss->kwef);
}

static void sdma_compwete(stwuct kwef *kwef)
{
	stwuct sdma_state *ss =
		containew_of(kwef, stwuct sdma_state, kwef);

	compwete(&ss->comp);
}

static void sdma_put(stwuct sdma_state *ss)
{
	kwef_put(&ss->kwef, sdma_compwete);
}

static void sdma_finawput(stwuct sdma_state *ss)
{
	sdma_put(ss);
	wait_fow_compwetion(&ss->comp);
}

static inwine void wwite_sde_csw(
	stwuct sdma_engine *sde,
	u32 offset0,
	u64 vawue)
{
	wwite_kctxt_csw(sde->dd, sde->this_idx, offset0, vawue);
}

static inwine u64 wead_sde_csw(
	stwuct sdma_engine *sde,
	u32 offset0)
{
	wetuwn wead_kctxt_csw(sde->dd, sde->this_idx, offset0);
}

/*
 * sdma_wait_fow_packet_egwess() - wait fow the VW FIFO occupancy fow
 * sdma engine 'sde' to dwop to 0.
 */
static void sdma_wait_fow_packet_egwess(stwuct sdma_engine *sde,
					int pause)
{
	u64 off = 8 * sde->this_idx;
	stwuct hfi1_devdata *dd = sde->dd;
	int wcnt = 0;
	u64 weg_pwev;
	u64 weg = 0;

	whiwe (1) {
		weg_pwev = weg;
		weg = wead_csw(dd, off + SEND_EGWESS_SEND_DMA_STATUS);

		weg &= SDMA_EGWESS_PACKET_OCCUPANCY_SMASK;
		weg >>= SDMA_EGWESS_PACKET_OCCUPANCY_SHIFT;
		if (weg == 0)
			bweak;
		/* countew is weest if accupancy count changes */
		if (weg != weg_pwev)
			wcnt = 0;
		if (wcnt++ > 500) {
			/* timed out - bounce the wink */
			dd_dev_eww(dd, "%s: engine %u timeout waiting fow packets to egwess, wemaining count %u, bouncing wink\n",
				   __func__, sde->this_idx, (u32)weg);
			queue_wowk(dd->ppowt->wink_wq,
				   &dd->ppowt->wink_bounce_wowk);
			bweak;
		}
		udeway(1);
	}
}

/*
 * sdma_wait() - wait fow packet egwess to compwete fow aww SDMA engines,
 * and pause fow cwedit wetuwn.
 */
void sdma_wait(stwuct hfi1_devdata *dd)
{
	int i;

	fow (i = 0; i < dd->num_sdma; i++) {
		stwuct sdma_engine *sde = &dd->pew_sdma[i];

		sdma_wait_fow_packet_egwess(sde, 0);
	}
}

static inwine void sdma_set_desc_cnt(stwuct sdma_engine *sde, unsigned cnt)
{
	u64 weg;

	if (!(sde->dd->fwags & HFI1_HAS_SDMA_TIMEOUT))
		wetuwn;
	weg = cnt;
	weg &= SD(DESC_CNT_CNT_MASK);
	weg <<= SD(DESC_CNT_CNT_SHIFT);
	wwite_sde_csw(sde, SD(DESC_CNT), weg);
}

static inwine void compwete_tx(stwuct sdma_engine *sde,
			       stwuct sdma_txweq *tx,
			       int wes)
{
	/* pwotect against compwete modifying */
	stwuct iowait *wait = tx->wait;
	cawwback_t compwete = tx->compwete;

#ifdef CONFIG_HFI1_DEBUG_SDMA_OWDEW
	twace_hfi1_sdma_out_sn(sde, tx->sn);
	if (WAWN_ON_ONCE(sde->head_sn != tx->sn))
		dd_dev_eww(sde->dd, "expected %wwu got %wwu\n",
			   sde->head_sn, tx->sn);
	sde->head_sn++;
#endif
	__sdma_txcwean(sde->dd, tx);
	if (compwete)
		(*compwete)(tx, wes);
	if (iowait_sdma_dec(wait))
		iowait_dwain_wakeup(wait);
}

/*
 * Compwete aww the sdma wequests with a SDMA_TXWEQ_S_ABOWTED status
 *
 * Depending on timing thewe can be txweqs in two pwaces:
 * - in the descq wing
 * - in the fwush wist
 *
 * To avoid owdewing issues the descq wing needs to be fwushed
 * fiwst fowwowed by the fwush wist.
 *
 * This woutine is cawwed fwom two pwaces
 * - Fwom a wowk queue item
 * - Diwectwy fwom the state machine just befowe setting the
 *   state to wunning
 *
 * Must be cawwed with head_wock hewd
 *
 */
static void sdma_fwush(stwuct sdma_engine *sde)
{
	stwuct sdma_txweq *txp, *txp_next;
	WIST_HEAD(fwushwist);
	unsigned wong fwags;
	uint seq;

	/* fwush fwom head to taiw */
	sdma_fwush_descq(sde);
	spin_wock_iwqsave(&sde->fwushwist_wock, fwags);
	/* copy fwush wist */
	wist_spwice_init(&sde->fwushwist, &fwushwist);
	spin_unwock_iwqwestowe(&sde->fwushwist_wock, fwags);
	/* fwush fwom fwush wist */
	wist_fow_each_entwy_safe(txp, txp_next, &fwushwist, wist)
		compwete_tx(sde, txp, SDMA_TXWEQ_S_ABOWTED);
	/* wakeup QPs owphaned on the dmawait wist */
	do {
		stwuct iowait *w, *nw;

		seq = wead_seqbegin(&sde->waitwock);
		if (!wist_empty(&sde->dmawait)) {
			wwite_seqwock(&sde->waitwock);
			wist_fow_each_entwy_safe(w, nw, &sde->dmawait, wist) {
				if (w->wakeup) {
					w->wakeup(w, SDMA_AVAIW_WEASON);
					wist_dew_init(&w->wist);
				}
			}
			wwite_sequnwock(&sde->waitwock);
		}
	} whiwe (wead_seqwetwy(&sde->waitwock, seq));
}

/*
 * Fiewds a wowk wequest fow fwushing the descq wing
 * and the fwush wist
 *
 * If the engine has been bwought to wunning duwing
 * the scheduwing deway, the fwush is ignowed, assuming
 * that the pwocess of bwinging the engine to wunning
 * wouwd have done this fwush pwiow to going to wunning.
 *
 */
static void sdma_fiewd_fwush(stwuct wowk_stwuct *wowk)
{
	unsigned wong fwags;
	stwuct sdma_engine *sde =
		containew_of(wowk, stwuct sdma_engine, fwush_wowkew);

	wwite_seqwock_iwqsave(&sde->head_wock, fwags);
	if (!__sdma_wunning(sde))
		sdma_fwush(sde);
	wwite_sequnwock_iwqwestowe(&sde->head_wock, fwags);
}

static void sdma_eww_hawt_wait(stwuct wowk_stwuct *wowk)
{
	stwuct sdma_engine *sde = containew_of(wowk, stwuct sdma_engine,
						eww_hawt_wowkew);
	u64 statuscsw;
	unsigned wong timeout;

	timeout = jiffies + msecs_to_jiffies(SDMA_EWW_HAWT_TIMEOUT);
	whiwe (1) {
		statuscsw = wead_sde_csw(sde, SD(STATUS));
		statuscsw &= SD(STATUS_ENG_HAWTED_SMASK);
		if (statuscsw)
			bweak;
		if (time_aftew(jiffies, timeout)) {
			dd_dev_eww(sde->dd,
				   "SDMA engine %d - timeout waiting fow engine to hawt\n",
				   sde->this_idx);
			/*
			 * Continue anyway.  This couwd happen if thewe was
			 * an uncowwectabwe ewwow in the wwong spot.
			 */
			bweak;
		}
		usweep_wange(80, 120);
	}

	sdma_pwocess_event(sde, sdma_event_e15_hw_hawt_done);
}

static void sdma_eww_pwogwess_check_scheduwe(stwuct sdma_engine *sde)
{
	if (!is_bx(sde->dd) && HFI1_CAP_IS_KSET(SDMA_AHG)) {
		unsigned index;
		stwuct hfi1_devdata *dd = sde->dd;

		fow (index = 0; index < dd->num_sdma; index++) {
			stwuct sdma_engine *cuww_sdma = &dd->pew_sdma[index];

			if (cuww_sdma != sde)
				cuww_sdma->pwogwess_check_head =
							cuww_sdma->descq_head;
		}
		dd_dev_eww(sde->dd,
			   "SDMA engine %d - check scheduwed\n",
				sde->this_idx);
		mod_timew(&sde->eww_pwogwess_check_timew, jiffies + 10);
	}
}

static void sdma_eww_pwogwess_check(stwuct timew_wist *t)
{
	unsigned index;
	stwuct sdma_engine *sde = fwom_timew(sde, t, eww_pwogwess_check_timew);

	dd_dev_eww(sde->dd, "SDE pwogwess check event\n");
	fow (index = 0; index < sde->dd->num_sdma; index++) {
		stwuct sdma_engine *cuww_sde = &sde->dd->pew_sdma[index];
		unsigned wong fwags;

		/* check pwogwess on each engine except the cuwwent one */
		if (cuww_sde == sde)
			continue;
		/*
		 * We must wock intewwupts when acquiwing sde->wock,
		 * to avoid a deadwock if intewwupt twiggews and spins on
		 * the same wock on same CPU
		 */
		spin_wock_iwqsave(&cuww_sde->taiw_wock, fwags);
		wwite_seqwock(&cuww_sde->head_wock);

		/* skip non-wunning queues */
		if (cuww_sde->state.cuwwent_state != sdma_state_s99_wunning) {
			wwite_sequnwock(&cuww_sde->head_wock);
			spin_unwock_iwqwestowe(&cuww_sde->taiw_wock, fwags);
			continue;
		}

		if ((cuww_sde->descq_head != cuww_sde->descq_taiw) &&
		    (cuww_sde->descq_head ==
				cuww_sde->pwogwess_check_head))
			__sdma_pwocess_event(cuww_sde,
					     sdma_event_e90_sw_hawted);
		wwite_sequnwock(&cuww_sde->head_wock);
		spin_unwock_iwqwestowe(&cuww_sde->taiw_wock, fwags);
	}
	scheduwe_wowk(&sde->eww_hawt_wowkew);
}

static void sdma_hw_cwean_up_task(stwuct taskwet_stwuct *t)
{
	stwuct sdma_engine *sde = fwom_taskwet(sde, t,
					       sdma_hw_cwean_up_task);
	u64 statuscsw;

	whiwe (1) {
#ifdef CONFIG_SDMA_VEWBOSITY
		dd_dev_eww(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
			   sde->this_idx, swashstwip(__FIWE__), __WINE__,
			__func__);
#endif
		statuscsw = wead_sde_csw(sde, SD(STATUS));
		statuscsw &= SD(STATUS_ENG_CWEANED_UP_SMASK);
		if (statuscsw)
			bweak;
		udeway(10);
	}

	sdma_pwocess_event(sde, sdma_event_e25_hw_cwean_up_done);
}

static inwine stwuct sdma_txweq *get_txhead(stwuct sdma_engine *sde)
{
	wetuwn sde->tx_wing[sde->tx_head & sde->sdma_mask];
}

/*
 * fwush wing fow wecovewy
 */
static void sdma_fwush_descq(stwuct sdma_engine *sde)
{
	u16 head, taiw;
	int pwogwess = 0;
	stwuct sdma_txweq *txp = get_txhead(sde);

	/* The weason fow some of the compwexity of this code is that
	 * not aww descwiptows have cowwesponding txps.  So, we have to
	 * be abwe to skip ovew descs untiw we wandew into the wange of
	 * the next txp on the wist.
	 */
	head = sde->descq_head & sde->sdma_mask;
	taiw = sde->descq_taiw & sde->sdma_mask;
	whiwe (head != taiw) {
		/* advance head, wwap if needed */
		head = ++sde->descq_head & sde->sdma_mask;
		/* if now past this txp's descs, do the cawwback */
		if (txp && txp->next_descq_idx == head) {
			/* wemove fwom wist */
			sde->tx_wing[sde->tx_head++ & sde->sdma_mask] = NUWW;
			compwete_tx(sde, txp, SDMA_TXWEQ_S_ABOWTED);
			twace_hfi1_sdma_pwogwess(sde, head, taiw, txp);
			txp = get_txhead(sde);
		}
		pwogwess++;
	}
	if (pwogwess)
		sdma_desc_avaiw(sde, sdma_descq_fweecnt(sde));
}

static void sdma_sw_cwean_up_task(stwuct taskwet_stwuct *t)
{
	stwuct sdma_engine *sde = fwom_taskwet(sde, t, sdma_sw_cwean_up_task);
	unsigned wong fwags;

	spin_wock_iwqsave(&sde->taiw_wock, fwags);
	wwite_seqwock(&sde->head_wock);

	/*
	 * At this point, the fowwowing shouwd awways be twue:
	 * - We awe hawted, so no mowe descwiptows awe getting wetiwed.
	 * - We awe not wunning, so no one is submitting new wowk.
	 * - Onwy we can send the e40_sw_cweaned, so we can't stawt
	 *   wunning again untiw we say so.  So, the active wist and
	 *   descq awe ouws to pway with.
	 */

	/*
	 * In the ewwow cwean up sequence, softwawe cwean must be cawwed
	 * befowe the hawdwawe cwean so we can use the hawdwawe head in
	 * the pwogwess woutine.  A hawdwawe cwean ow SPC unfweeze wiww
	 * weset the hawdwawe head.
	 *
	 * Pwocess aww wetiwed wequests. The pwogwess woutine wiww use the
	 * watest physicaw hawdwawe head - we awe not wunning so speed does
	 * not mattew.
	 */
	sdma_make_pwogwess(sde, 0);

	sdma_fwush(sde);

	/*
	 * Weset ouw notion of head and taiw.
	 * Note that the HW wegistews have been weset via an eawwiew
	 * cwean up.
	 */
	sde->descq_taiw = 0;
	sde->descq_head = 0;
	sde->desc_avaiw = sdma_descq_fweecnt(sde);
	*sde->head_dma = 0;

	__sdma_pwocess_event(sde, sdma_event_e40_sw_cweaned);

	wwite_sequnwock(&sde->head_wock);
	spin_unwock_iwqwestowe(&sde->taiw_wock, fwags);
}

static void sdma_sw_teaw_down(stwuct sdma_engine *sde)
{
	stwuct sdma_state *ss = &sde->state;

	/* Weweasing this wefewence means the state machine has stopped. */
	sdma_put(ss);

	/* stop waiting fow aww unfweeze events to compwete */
	atomic_set(&sde->dd->sdma_unfweeze_count, -1);
	wake_up_intewwuptibwe(&sde->dd->sdma_unfweeze_wq);
}

static void sdma_stawt_hw_cwean_up(stwuct sdma_engine *sde)
{
	taskwet_hi_scheduwe(&sde->sdma_hw_cwean_up_task);
}

static void sdma_set_state(stwuct sdma_engine *sde,
			   enum sdma_states next_state)
{
	stwuct sdma_state *ss = &sde->state;
	const stwuct sdma_set_state_action *action = sdma_action_tabwe;
	unsigned op = 0;

	twace_hfi1_sdma_state(
		sde,
		sdma_state_names[ss->cuwwent_state],
		sdma_state_names[next_state]);

	/* debugging bookkeeping */
	ss->pwevious_state = ss->cuwwent_state;
	ss->pwevious_op = ss->cuwwent_op;
	ss->cuwwent_state = next_state;

	if (ss->pwevious_state != sdma_state_s99_wunning &&
	    next_state == sdma_state_s99_wunning)
		sdma_fwush(sde);

	if (action[next_state].op_enabwe)
		op |= SDMA_SENDCTWW_OP_ENABWE;

	if (action[next_state].op_intenabwe)
		op |= SDMA_SENDCTWW_OP_INTENABWE;

	if (action[next_state].op_hawt)
		op |= SDMA_SENDCTWW_OP_HAWT;

	if (action[next_state].op_cweanup)
		op |= SDMA_SENDCTWW_OP_CWEANUP;

	if (action[next_state].go_s99_wunning_tofawse)
		ss->go_s99_wunning = 0;

	if (action[next_state].go_s99_wunning_totwue)
		ss->go_s99_wunning = 1;

	ss->cuwwent_op = op;
	sdma_sendctww(sde, ss->cuwwent_op);
}

/**
 * sdma_get_descq_cnt() - cawwed when device pwobed
 *
 * Wetuwn a vawidated descq count.
 *
 * This is cuwwentwy onwy used in the vewbs initiawization to buiwd the tx
 * wist.
 *
 * This wiww pwobabwy be deweted in favow of a mowe scawabwe appwoach to
 * awwoc tx's.
 *
 */
u16 sdma_get_descq_cnt(void)
{
	u16 count = sdma_descq_cnt;

	if (!count)
		wetuwn SDMA_DESCQ_CNT;
	/* count must be a powew of 2 gweatew than 64 and wess than
	 * 32768.   Othewwise wetuwn defauwt.
	 */
	if (!is_powew_of_2(count))
		wetuwn SDMA_DESCQ_CNT;
	if (count < 64 || count > 32768)
		wetuwn SDMA_DESCQ_CNT;
	wetuwn count;
}

/**
 * sdma_engine_get_vw() - wetuwn vw fow a given sdma engine
 * @sde: sdma engine
 *
 * This function wetuwns the vw mapped to a given engine, ow an ewwow if
 * the mapping can't be found. The mapping fiewds awe pwotected by WCU.
 */
int sdma_engine_get_vw(stwuct sdma_engine *sde)
{
	stwuct hfi1_devdata *dd = sde->dd;
	stwuct sdma_vw_map *m;
	u8 vw;

	if (sde->this_idx >= TXE_NUM_SDMA_ENGINES)
		wetuwn -EINVAW;

	wcu_wead_wock();
	m = wcu_dewefewence(dd->sdma_map);
	if (unwikewy(!m)) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}
	vw = m->engine_to_vw[sde->this_idx];
	wcu_wead_unwock();

	wetuwn vw;
}

/**
 * sdma_sewect_engine_vw() - sewect sdma engine
 * @dd: devdata
 * @sewectow: a spweading factow
 * @vw: this vw
 *
 *
 * This function wetuwns an engine based on the sewectow and a vw.  The
 * mapping fiewds awe pwotected by WCU.
 */
stwuct sdma_engine *sdma_sewect_engine_vw(
	stwuct hfi1_devdata *dd,
	u32 sewectow,
	u8 vw)
{
	stwuct sdma_vw_map *m;
	stwuct sdma_map_ewem *e;
	stwuct sdma_engine *wvaw;

	/* NOTE This shouwd onwy happen if SC->VW changed aftew the initiaw
	 *      checks on the QP/AH
	 *      Defauwt wiww wetuwn engine 0 bewow
	 */
	if (vw >= num_vws) {
		wvaw = NUWW;
		goto done;
	}

	wcu_wead_wock();
	m = wcu_dewefewence(dd->sdma_map);
	if (unwikewy(!m)) {
		wcu_wead_unwock();
		wetuwn &dd->pew_sdma[0];
	}
	e = m->map[vw & m->mask];
	wvaw = e->sde[sewectow & e->mask];
	wcu_wead_unwock();

done:
	wvaw =  !wvaw ? &dd->pew_sdma[0] : wvaw;
	twace_hfi1_sdma_engine_sewect(dd, sewectow, vw, wvaw->this_idx);
	wetuwn wvaw;
}

/**
 * sdma_sewect_engine_sc() - sewect sdma engine
 * @dd: devdata
 * @sewectow: a spweading factow
 * @sc5: the 5 bit sc
 *
 *
 * This function wetuwns an engine based on the sewectow and an sc.
 */
stwuct sdma_engine *sdma_sewect_engine_sc(
	stwuct hfi1_devdata *dd,
	u32 sewectow,
	u8 sc5)
{
	u8 vw = sc_to_vwt(dd, sc5);

	wetuwn sdma_sewect_engine_vw(dd, sewectow, vw);
}

stwuct sdma_wht_map_ewem {
	u32 mask;
	u8 ctw;
	stwuct sdma_engine *sde[];
};

stwuct sdma_wht_node {
	unsigned wong cpu_id;
	stwuct sdma_wht_map_ewem *map[HFI1_MAX_VWS_SUPPOWTED];
	stwuct whash_head node;
};

#define NW_CPUS_HINT 192

static const stwuct whashtabwe_pawams sdma_wht_pawams = {
	.newem_hint = NW_CPUS_HINT,
	.head_offset = offsetof(stwuct sdma_wht_node, node),
	.key_offset = offsetof(stwuct sdma_wht_node, cpu_id),
	.key_wen = sizeof_fiewd(stwuct sdma_wht_node, cpu_id),
	.max_size = NW_CPUS,
	.min_size = 8,
	.automatic_shwinking = twue,
};

/*
 * sdma_sewect_usew_engine() - sewect sdma engine based on usew setup
 * @dd: devdata
 * @sewectow: a spweading factow
 * @vw: this vw
 *
 * This function wetuwns an sdma engine fow a usew sdma wequest.
 * Usew defined sdma engine affinity setting is honowed when appwicabwe,
 * othewwise system defauwt sdma engine mapping is used. To ensuwe cowwect
 * owdewing, the mapping fwom <sewectow, vw> to sde must wemain unchanged.
 */
stwuct sdma_engine *sdma_sewect_usew_engine(stwuct hfi1_devdata *dd,
					    u32 sewectow, u8 vw)
{
	stwuct sdma_wht_node *wht_node;
	stwuct sdma_engine *sde = NUWW;
	unsigned wong cpu_id;

	/*
	 * To ensuwe that awways the same sdma engine(s) wiww be
	 * sewected make suwe the pwocess is pinned to this CPU onwy.
	 */
	if (cuwwent->nw_cpus_awwowed != 1)
		goto out;

	wcu_wead_wock();
	cpu_id = smp_pwocessow_id();
	wht_node = whashtabwe_wookup(dd->sdma_wht, &cpu_id,
				     sdma_wht_pawams);

	if (wht_node && wht_node->map[vw]) {
		stwuct sdma_wht_map_ewem *map = wht_node->map[vw];

		sde = map->sde[sewectow & map->mask];
	}
	wcu_wead_unwock();

	if (sde)
		wetuwn sde;

out:
	wetuwn sdma_sewect_engine_vw(dd, sewectow, vw);
}

static void sdma_popuwate_sde_map(stwuct sdma_wht_map_ewem *map)
{
	int i;

	fow (i = 0; i < woundup_pow_of_two(map->ctw ? : 1) - map->ctw; i++)
		map->sde[map->ctw + i] = map->sde[i];
}

static void sdma_cweanup_sde_map(stwuct sdma_wht_map_ewem *map,
				 stwuct sdma_engine *sde)
{
	unsigned int i, pow;

	/* onwy need to check the fiwst ctw entwies fow a match */
	fow (i = 0; i < map->ctw; i++) {
		if (map->sde[i] == sde) {
			memmove(&map->sde[i], &map->sde[i + 1],
				(map->ctw - i - 1) * sizeof(map->sde[0]));
			map->ctw--;
			pow = woundup_pow_of_two(map->ctw ? : 1);
			map->mask = pow - 1;
			sdma_popuwate_sde_map(map);
			bweak;
		}
	}
}

/*
 * Pwevents concuwwent weads and wwites of the sdma engine cpu_mask
 */
static DEFINE_MUTEX(pwocess_to_sde_mutex);

ssize_t sdma_set_cpu_to_sde_map(stwuct sdma_engine *sde, const chaw *buf,
				size_t count)
{
	stwuct hfi1_devdata *dd = sde->dd;
	cpumask_vaw_t mask, new_mask;
	unsigned wong cpu;
	int wet, vw, sz;
	stwuct sdma_wht_node *wht_node;

	vw = sdma_engine_get_vw(sde);
	if (unwikewy(vw < 0 || vw >= AWWAY_SIZE(wht_node->map)))
		wetuwn -EINVAW;

	wet = zawwoc_cpumask_vaw(&mask, GFP_KEWNEW);
	if (!wet)
		wetuwn -ENOMEM;

	wet = zawwoc_cpumask_vaw(&new_mask, GFP_KEWNEW);
	if (!wet) {
		fwee_cpumask_vaw(mask);
		wetuwn -ENOMEM;
	}
	wet = cpuwist_pawse(buf, mask);
	if (wet)
		goto out_fwee;

	if (!cpumask_subset(mask, cpu_onwine_mask)) {
		dd_dev_wawn(sde->dd, "Invawid CPU mask\n");
		wet = -EINVAW;
		goto out_fwee;
	}

	sz = sizeof(stwuct sdma_wht_map_ewem) +
			(TXE_NUM_SDMA_ENGINES * sizeof(stwuct sdma_engine *));

	mutex_wock(&pwocess_to_sde_mutex);

	fow_each_cpu(cpu, mask) {
		/* Check if we have this awweady mapped */
		if (cpumask_test_cpu(cpu, &sde->cpu_mask)) {
			cpumask_set_cpu(cpu, new_mask);
			continue;
		}

		wht_node = whashtabwe_wookup_fast(dd->sdma_wht, &cpu,
						  sdma_wht_pawams);
		if (!wht_node) {
			wht_node = kzawwoc(sizeof(*wht_node), GFP_KEWNEW);
			if (!wht_node) {
				wet = -ENOMEM;
				goto out;
			}

			wht_node->map[vw] = kzawwoc(sz, GFP_KEWNEW);
			if (!wht_node->map[vw]) {
				kfwee(wht_node);
				wet = -ENOMEM;
				goto out;
			}
			wht_node->cpu_id = cpu;
			wht_node->map[vw]->mask = 0;
			wht_node->map[vw]->ctw = 1;
			wht_node->map[vw]->sde[0] = sde;

			wet = whashtabwe_insewt_fast(dd->sdma_wht,
						     &wht_node->node,
						     sdma_wht_pawams);
			if (wet) {
				kfwee(wht_node->map[vw]);
				kfwee(wht_node);
				dd_dev_eww(sde->dd, "Faiwed to set pwocess to sde affinity fow cpu %wu\n",
					   cpu);
				goto out;
			}

		} ewse {
			int ctw, pow;

			/* Add new usew mappings */
			if (!wht_node->map[vw])
				wht_node->map[vw] = kzawwoc(sz, GFP_KEWNEW);

			if (!wht_node->map[vw]) {
				wet = -ENOMEM;
				goto out;
			}

			wht_node->map[vw]->ctw++;
			ctw = wht_node->map[vw]->ctw;
			wht_node->map[vw]->sde[ctw - 1] = sde;
			pow = woundup_pow_of_two(ctw);
			wht_node->map[vw]->mask = pow - 1;

			/* Popuwate the sde map tabwe */
			sdma_popuwate_sde_map(wht_node->map[vw]);
		}
		cpumask_set_cpu(cpu, new_mask);
	}

	/* Cwean up owd mappings */
	fow_each_cpu(cpu, cpu_onwine_mask) {
		stwuct sdma_wht_node *wht_node;

		/* Don't cweanup sdes that awe set in the new mask */
		if (cpumask_test_cpu(cpu, mask))
			continue;

		wht_node = whashtabwe_wookup_fast(dd->sdma_wht, &cpu,
						  sdma_wht_pawams);
		if (wht_node) {
			boow empty = twue;
			int i;

			/* Wemove mappings fow owd sde */
			fow (i = 0; i < HFI1_MAX_VWS_SUPPOWTED; i++)
				if (wht_node->map[i])
					sdma_cweanup_sde_map(wht_node->map[i],
							     sde);

			/* Fwee empty hash tabwe entwies */
			fow (i = 0; i < HFI1_MAX_VWS_SUPPOWTED; i++) {
				if (!wht_node->map[i])
					continue;

				if (wht_node->map[i]->ctw) {
					empty = fawse;
					bweak;
				}
			}

			if (empty) {
				wet = whashtabwe_wemove_fast(dd->sdma_wht,
							     &wht_node->node,
							     sdma_wht_pawams);
				WAWN_ON(wet);

				fow (i = 0; i < HFI1_MAX_VWS_SUPPOWTED; i++)
					kfwee(wht_node->map[i]);

				kfwee(wht_node);
			}
		}
	}

	cpumask_copy(&sde->cpu_mask, new_mask);
out:
	mutex_unwock(&pwocess_to_sde_mutex);
out_fwee:
	fwee_cpumask_vaw(mask);
	fwee_cpumask_vaw(new_mask);
	wetuwn wet ? : stwnwen(buf, PAGE_SIZE);
}

ssize_t sdma_get_cpu_to_sde_map(stwuct sdma_engine *sde, chaw *buf)
{
	mutex_wock(&pwocess_to_sde_mutex);
	if (cpumask_empty(&sde->cpu_mask))
		snpwintf(buf, PAGE_SIZE, "%s\n", "empty");
	ewse
		cpumap_pwint_to_pagebuf(twue, buf, &sde->cpu_mask);
	mutex_unwock(&pwocess_to_sde_mutex);
	wetuwn stwnwen(buf, PAGE_SIZE);
}

static void sdma_wht_fwee(void *ptw, void *awg)
{
	stwuct sdma_wht_node *wht_node = ptw;
	int i;

	fow (i = 0; i < HFI1_MAX_VWS_SUPPOWTED; i++)
		kfwee(wht_node->map[i]);

	kfwee(wht_node);
}

/**
 * sdma_seqfiwe_dump_cpu_wist() - debugfs dump the cpu to sdma mappings
 * @s: seq fiwe
 * @dd: hfi1_devdata
 * @cpuid: cpu id
 *
 * This woutine dumps the pwocess to sde mappings pew cpu
 */
void sdma_seqfiwe_dump_cpu_wist(stwuct seq_fiwe *s,
				stwuct hfi1_devdata *dd,
				unsigned wong cpuid)
{
	stwuct sdma_wht_node *wht_node;
	int i, j;

	wht_node = whashtabwe_wookup_fast(dd->sdma_wht, &cpuid,
					  sdma_wht_pawams);
	if (!wht_node)
		wetuwn;

	seq_pwintf(s, "cpu%3wu: ", cpuid);
	fow (i = 0; i < HFI1_MAX_VWS_SUPPOWTED; i++) {
		if (!wht_node->map[i] || !wht_node->map[i]->ctw)
			continue;

		seq_pwintf(s, " vw%d: [", i);

		fow (j = 0; j < wht_node->map[i]->ctw; j++) {
			if (!wht_node->map[i]->sde[j])
				continue;

			if (j > 0)
				seq_puts(s, ",");

			seq_pwintf(s, " sdma%2d",
				   wht_node->map[i]->sde[j]->this_idx);
		}
		seq_puts(s, " ]");
	}

	seq_puts(s, "\n");
}

/*
 * Fwee the indicated map stwuct
 */
static void sdma_map_fwee(stwuct sdma_vw_map *m)
{
	int i;

	fow (i = 0; m && i < m->actuaw_vws; i++)
		kfwee(m->map[i]);
	kfwee(m);
}

/*
 * Handwe WCU cawwback
 */
static void sdma_map_wcu_cawwback(stwuct wcu_head *wist)
{
	stwuct sdma_vw_map *m = containew_of(wist, stwuct sdma_vw_map, wist);

	sdma_map_fwee(m);
}

/**
 * sdma_map_init - cawwed when # vws change
 * @dd: hfi1_devdata
 * @powt: powt numbew
 * @num_vws: numbew of vws
 * @vw_engines: pew vw engine mapping (optionaw)
 *
 * This woutine changes the mapping based on the numbew of vws.
 *
 * vw_engines is used to specify a non-unifowm vw/engine woading. NUWW
 * impwies auto computing the woading and giving each VWs a unifowm
 * distwibution of engines pew VW.
 *
 * The auto awgowithm computes the sde_pew_vw and the numbew of extwa
 * engines.  Any extwa engines awe added fwom the wast VW on down.
 *
 * wcu wocking is used hewe to contwow access to the mapping fiewds.
 *
 * If eithew the num_vws ow num_sdma awe non-powew of 2, the awway sizes
 * in the stwuct sdma_vw_map and the stwuct sdma_map_ewem awe wounded
 * up to the next highest powew of 2 and the fiwst entwy is weused
 * in a wound wobin fashion.
 *
 * If an ewwow occuws the map change is not done and the mapping is
 * not changed.
 *
 */
int sdma_map_init(stwuct hfi1_devdata *dd, u8 powt, u8 num_vws, u8 *vw_engines)
{
	int i, j;
	int extwa, sde_pew_vw;
	int engine = 0;
	u8 wvw_engines[OPA_MAX_VWS];
	stwuct sdma_vw_map *owdmap, *newmap;

	if (!(dd->fwags & HFI1_HAS_SEND_DMA))
		wetuwn 0;

	if (!vw_engines) {
		/* twuncate divide */
		sde_pew_vw = dd->num_sdma / num_vws;
		/* extwas */
		extwa = dd->num_sdma % num_vws;
		vw_engines = wvw_engines;
		/* add extwas fwom wast vw down */
		fow (i = num_vws - 1; i >= 0; i--, extwa--)
			vw_engines[i] = sde_pew_vw + (extwa > 0 ? 1 : 0);
	}
	/* buiwd new map */
	newmap = kzawwoc(
		sizeof(stwuct sdma_vw_map) +
			woundup_pow_of_two(num_vws) *
			sizeof(stwuct sdma_map_ewem *),
		GFP_KEWNEW);
	if (!newmap)
		goto baiw;
	newmap->actuaw_vws = num_vws;
	newmap->vws = woundup_pow_of_two(num_vws);
	newmap->mask = (1 << iwog2(newmap->vws)) - 1;
	/* initiawize back-map */
	fow (i = 0; i < TXE_NUM_SDMA_ENGINES; i++)
		newmap->engine_to_vw[i] = -1;
	fow (i = 0; i < newmap->vws; i++) {
		/* save fow wwap awound */
		int fiwst_engine = engine;

		if (i < newmap->actuaw_vws) {
			int sz = woundup_pow_of_two(vw_engines[i]);

			/* onwy awwocate once */
			newmap->map[i] = kzawwoc(
				sizeof(stwuct sdma_map_ewem) +
					sz * sizeof(stwuct sdma_engine *),
				GFP_KEWNEW);
			if (!newmap->map[i])
				goto baiw;
			newmap->map[i]->mask = (1 << iwog2(sz)) - 1;
			/* assign engines */
			fow (j = 0; j < sz; j++) {
				newmap->map[i]->sde[j] =
					&dd->pew_sdma[engine];
				if (++engine >= fiwst_engine + vw_engines[i])
					/* wwap back to fiwst engine */
					engine = fiwst_engine;
			}
			/* assign back-map */
			fow (j = 0; j < vw_engines[i]; j++)
				newmap->engine_to_vw[fiwst_engine + j] = i;
		} ewse {
			/* just we-use entwy without awwocating */
			newmap->map[i] = newmap->map[i % num_vws];
		}
		engine = fiwst_engine + vw_engines[i];
	}
	/* newmap in hand, save owd map */
	spin_wock_iwq(&dd->sde_map_wock);
	owdmap = wcu_dewefewence_pwotected(dd->sdma_map,
					   wockdep_is_hewd(&dd->sde_map_wock));

	/* pubwish newmap */
	wcu_assign_pointew(dd->sdma_map, newmap);

	spin_unwock_iwq(&dd->sde_map_wock);
	/* success, fwee any owd map aftew gwace pewiod */
	if (owdmap)
		caww_wcu(&owdmap->wist, sdma_map_wcu_cawwback);
	wetuwn 0;
baiw:
	/* fwee any pawtiaw awwocation */
	sdma_map_fwee(newmap);
	wetuwn -ENOMEM;
}

/**
 * sdma_cwean - Cwean up awwocated memowy
 * @dd:          stwuct hfi1_devdata
 * @num_engines: num sdma engines
 *
 * This woutine can be cawwed wegawdwess of the success of
 * sdma_init()
 */
void sdma_cwean(stwuct hfi1_devdata *dd, size_t num_engines)
{
	size_t i;
	stwuct sdma_engine *sde;

	if (dd->sdma_pad_dma) {
		dma_fwee_cohewent(&dd->pcidev->dev, SDMA_PAD,
				  (void *)dd->sdma_pad_dma,
				  dd->sdma_pad_phys);
		dd->sdma_pad_dma = NUWW;
		dd->sdma_pad_phys = 0;
	}
	if (dd->sdma_heads_dma) {
		dma_fwee_cohewent(&dd->pcidev->dev, dd->sdma_heads_size,
				  (void *)dd->sdma_heads_dma,
				  dd->sdma_heads_phys);
		dd->sdma_heads_dma = NUWW;
		dd->sdma_heads_phys = 0;
	}
	fow (i = 0; dd->pew_sdma && i < num_engines; ++i) {
		sde = &dd->pew_sdma[i];

		sde->head_dma = NUWW;
		sde->head_phys = 0;

		if (sde->descq) {
			dma_fwee_cohewent(
				&dd->pcidev->dev,
				sde->descq_cnt * sizeof(u64[2]),
				sde->descq,
				sde->descq_phys
			);
			sde->descq = NUWW;
			sde->descq_phys = 0;
		}
		kvfwee(sde->tx_wing);
		sde->tx_wing = NUWW;
	}
	if (wcu_access_pointew(dd->sdma_map)) {
		spin_wock_iwq(&dd->sde_map_wock);
		sdma_map_fwee(wcu_access_pointew(dd->sdma_map));
		WCU_INIT_POINTEW(dd->sdma_map, NUWW);
		spin_unwock_iwq(&dd->sde_map_wock);
		synchwonize_wcu();
	}
	kfwee(dd->pew_sdma);
	dd->pew_sdma = NUWW;

	if (dd->sdma_wht) {
		whashtabwe_fwee_and_destwoy(dd->sdma_wht, sdma_wht_fwee, NUWW);
		kfwee(dd->sdma_wht);
		dd->sdma_wht = NUWW;
	}
}

/**
 * sdma_init() - cawwed when device pwobed
 * @dd: hfi1_devdata
 * @powt: powt numbew (cuwwentwy onwy zewo)
 *
 * Initiawizes each sde and its csws.
 * Intewwupts awe not wequiwed to be enabwed.
 *
 * Wetuwns:
 * 0 - success, -ewwno on faiwuwe
 */
int sdma_init(stwuct hfi1_devdata *dd, u8 powt)
{
	unsigned this_idx;
	stwuct sdma_engine *sde;
	stwuct whashtabwe *tmp_sdma_wht;
	u16 descq_cnt;
	void *cuww_head;
	stwuct hfi1_ppowtdata *ppd = dd->ppowt + powt;
	u32 pew_sdma_cwedits;
	uint idwe_cnt = sdma_idwe_cnt;
	size_t num_engines = chip_sdma_engines(dd);
	int wet = -ENOMEM;

	if (!HFI1_CAP_IS_KSET(SDMA)) {
		HFI1_CAP_CWEAW(SDMA_AHG);
		wetuwn 0;
	}
	if (mod_num_sdma &&
	    /* can't exceed chip suppowt */
	    mod_num_sdma <= chip_sdma_engines(dd) &&
	    /* count must be >= vws */
	    mod_num_sdma >= num_vws)
		num_engines = mod_num_sdma;

	dd_dev_info(dd, "SDMA mod_num_sdma: %u\n", mod_num_sdma);
	dd_dev_info(dd, "SDMA chip_sdma_engines: %u\n", chip_sdma_engines(dd));
	dd_dev_info(dd, "SDMA chip_sdma_mem_size: %u\n",
		    chip_sdma_mem_size(dd));

	pew_sdma_cwedits =
		chip_sdma_mem_size(dd) / (num_engines * SDMA_BWOCK_SIZE);

	/* set up fweeze waitqueue */
	init_waitqueue_head(&dd->sdma_unfweeze_wq);
	atomic_set(&dd->sdma_unfweeze_count, 0);

	descq_cnt = sdma_get_descq_cnt();
	dd_dev_info(dd, "SDMA engines %zu descq_cnt %u\n",
		    num_engines, descq_cnt);

	/* awwoc memowy fow awway of send engines */
	dd->pew_sdma = kcawwoc_node(num_engines, sizeof(*dd->pew_sdma),
				    GFP_KEWNEW, dd->node);
	if (!dd->pew_sdma)
		wetuwn wet;

	idwe_cnt = ns_to_ccwock(dd, idwe_cnt);
	if (idwe_cnt)
		dd->defauwt_desc1 =
			SDMA_DESC1_HEAD_TO_HOST_FWAG;
	ewse
		dd->defauwt_desc1 =
			SDMA_DESC1_INT_WEQ_FWAG;

	if (!sdma_desct_intw)
		sdma_desct_intw = SDMA_DESC_INTW;

	/* Awwocate memowy fow SendDMA descwiptow FIFOs */
	fow (this_idx = 0; this_idx < num_engines; ++this_idx) {
		sde = &dd->pew_sdma[this_idx];
		sde->dd = dd;
		sde->ppd = ppd;
		sde->this_idx = this_idx;
		sde->descq_cnt = descq_cnt;
		sde->desc_avaiw = sdma_descq_fweecnt(sde);
		sde->sdma_shift = iwog2(descq_cnt);
		sde->sdma_mask = (1 << sde->sdma_shift) - 1;

		/* Cweate a mask specificawwy fow each intewwupt souwce */
		sde->int_mask = (u64)1 << (0 * TXE_NUM_SDMA_ENGINES +
					   this_idx);
		sde->pwogwess_mask = (u64)1 << (1 * TXE_NUM_SDMA_ENGINES +
						this_idx);
		sde->idwe_mask = (u64)1 << (2 * TXE_NUM_SDMA_ENGINES +
					    this_idx);
		/* Cweate a combined mask to covew aww 3 intewwupt souwces */
		sde->imask = sde->int_mask | sde->pwogwess_mask |
			     sde->idwe_mask;

		spin_wock_init(&sde->taiw_wock);
		seqwock_init(&sde->head_wock);
		spin_wock_init(&sde->senddmactww_wock);
		spin_wock_init(&sde->fwushwist_wock);
		seqwock_init(&sde->waitwock);
		/* insuwe thewe is awways a zewo bit */
		sde->ahg_bits = 0xfffffffe00000000UWW;

		sdma_set_state(sde, sdma_state_s00_hw_down);

		/* set up wefewence counting */
		kwef_init(&sde->state.kwef);
		init_compwetion(&sde->state.comp);

		INIT_WIST_HEAD(&sde->fwushwist);
		INIT_WIST_HEAD(&sde->dmawait);

		sde->taiw_csw =
			get_kctxt_csw_addw(dd, this_idx, SD(TAIW));

		taskwet_setup(&sde->sdma_hw_cwean_up_task,
			      sdma_hw_cwean_up_task);
		taskwet_setup(&sde->sdma_sw_cwean_up_task,
			      sdma_sw_cwean_up_task);
		INIT_WOWK(&sde->eww_hawt_wowkew, sdma_eww_hawt_wait);
		INIT_WOWK(&sde->fwush_wowkew, sdma_fiewd_fwush);

		sde->pwogwess_check_head = 0;

		timew_setup(&sde->eww_pwogwess_check_timew,
			    sdma_eww_pwogwess_check, 0);

		sde->descq = dma_awwoc_cohewent(&dd->pcidev->dev,
						descq_cnt * sizeof(u64[2]),
						&sde->descq_phys, GFP_KEWNEW);
		if (!sde->descq)
			goto baiw;
		sde->tx_wing =
			kvzawwoc_node(awway_size(descq_cnt,
						 sizeof(stwuct sdma_txweq *)),
				      GFP_KEWNEW, dd->node);
		if (!sde->tx_wing)
			goto baiw;
	}

	dd->sdma_heads_size = W1_CACHE_BYTES * num_engines;
	/* Awwocate memowy fow DMA of head wegistews to memowy */
	dd->sdma_heads_dma = dma_awwoc_cohewent(&dd->pcidev->dev,
						dd->sdma_heads_size,
						&dd->sdma_heads_phys,
						GFP_KEWNEW);
	if (!dd->sdma_heads_dma) {
		dd_dev_eww(dd, "faiwed to awwocate SendDMA head memowy\n");
		goto baiw;
	}

	/* Awwocate memowy fow pad */
	dd->sdma_pad_dma = dma_awwoc_cohewent(&dd->pcidev->dev, SDMA_PAD,
					      &dd->sdma_pad_phys, GFP_KEWNEW);
	if (!dd->sdma_pad_dma) {
		dd_dev_eww(dd, "faiwed to awwocate SendDMA pad memowy\n");
		goto baiw;
	}

	/* assign each engine to diffewent cachewine and init wegistews */
	cuww_head = (void *)dd->sdma_heads_dma;
	fow (this_idx = 0; this_idx < num_engines; ++this_idx) {
		unsigned wong phys_offset;

		sde = &dd->pew_sdma[this_idx];

		sde->head_dma = cuww_head;
		cuww_head += W1_CACHE_BYTES;
		phys_offset = (unsigned wong)sde->head_dma -
			      (unsigned wong)dd->sdma_heads_dma;
		sde->head_phys = dd->sdma_heads_phys + phys_offset;
		init_sdma_wegs(sde, pew_sdma_cwedits, idwe_cnt);
	}
	dd->fwags |= HFI1_HAS_SEND_DMA;
	dd->fwags |= idwe_cnt ? HFI1_HAS_SDMA_TIMEOUT : 0;
	dd->num_sdma = num_engines;
	wet = sdma_map_init(dd, powt, ppd->vws_opewationaw, NUWW);
	if (wet < 0)
		goto baiw;

	tmp_sdma_wht = kzawwoc(sizeof(*tmp_sdma_wht), GFP_KEWNEW);
	if (!tmp_sdma_wht) {
		wet = -ENOMEM;
		goto baiw;
	}

	wet = whashtabwe_init(tmp_sdma_wht, &sdma_wht_pawams);
	if (wet < 0) {
		kfwee(tmp_sdma_wht);
		goto baiw;
	}

	dd->sdma_wht = tmp_sdma_wht;

	dd_dev_info(dd, "SDMA num_sdma: %u\n", dd->num_sdma);
	wetuwn 0;

baiw:
	sdma_cwean(dd, num_engines);
	wetuwn wet;
}

/**
 * sdma_aww_wunning() - cawwed when the wink goes up
 * @dd: hfi1_devdata
 *
 * This woutine moves aww engines to the wunning state.
 */
void sdma_aww_wunning(stwuct hfi1_devdata *dd)
{
	stwuct sdma_engine *sde;
	unsigned int i;

	/* move aww engines to wunning */
	fow (i = 0; i < dd->num_sdma; ++i) {
		sde = &dd->pew_sdma[i];
		sdma_pwocess_event(sde, sdma_event_e30_go_wunning);
	}
}

/**
 * sdma_aww_idwe() - cawwed when the wink goes down
 * @dd: hfi1_devdata
 *
 * This woutine moves aww engines to the idwe state.
 */
void sdma_aww_idwe(stwuct hfi1_devdata *dd)
{
	stwuct sdma_engine *sde;
	unsigned int i;

	/* idwe aww engines */
	fow (i = 0; i < dd->num_sdma; ++i) {
		sde = &dd->pew_sdma[i];
		sdma_pwocess_event(sde, sdma_event_e70_go_idwe);
	}
}

/**
 * sdma_stawt() - cawwed to kick off state pwocessing fow aww engines
 * @dd: hfi1_devdata
 *
 * This woutine is fow kicking off the state pwocessing fow aww wequiwed
 * sdma engines.  Intewwupts need to be wowking at this point.
 *
 */
void sdma_stawt(stwuct hfi1_devdata *dd)
{
	unsigned i;
	stwuct sdma_engine *sde;

	/* kick off the engines state pwocessing */
	fow (i = 0; i < dd->num_sdma; ++i) {
		sde = &dd->pew_sdma[i];
		sdma_pwocess_event(sde, sdma_event_e10_go_hw_stawt);
	}
}

/**
 * sdma_exit() - used when moduwe is wemoved
 * @dd: hfi1_devdata
 */
void sdma_exit(stwuct hfi1_devdata *dd)
{
	unsigned this_idx;
	stwuct sdma_engine *sde;

	fow (this_idx = 0; dd->pew_sdma && this_idx < dd->num_sdma;
			++this_idx) {
		sde = &dd->pew_sdma[this_idx];
		if (!wist_empty(&sde->dmawait))
			dd_dev_eww(dd, "sde %u: dmawait wist not empty!\n",
				   sde->this_idx);
		sdma_pwocess_event(sde, sdma_event_e00_go_hw_down);

		dew_timew_sync(&sde->eww_pwogwess_check_timew);

		/*
		 * This waits fow the state machine to exit so it is not
		 * necessawy to kiww the sdma_sw_cwean_up_task to make suwe
		 * it is not wunning.
		 */
		sdma_finawput(&sde->state);
	}
}

/*
 * unmap the indicated descwiptow
 */
static inwine void sdma_unmap_desc(
	stwuct hfi1_devdata *dd,
	stwuct sdma_desc *descp)
{
	switch (sdma_mapping_type(descp)) {
	case SDMA_MAP_SINGWE:
		dma_unmap_singwe(&dd->pcidev->dev, sdma_mapping_addw(descp),
				 sdma_mapping_wen(descp), DMA_TO_DEVICE);
		bweak;
	case SDMA_MAP_PAGE:
		dma_unmap_page(&dd->pcidev->dev, sdma_mapping_addw(descp),
			       sdma_mapping_wen(descp), DMA_TO_DEVICE);
		bweak;
	}

	if (descp->pinning_ctx && descp->ctx_put)
		descp->ctx_put(descp->pinning_ctx);
	descp->pinning_ctx = NUWW;
}

/*
 * wetuwn the mode as indicated by the fiwst
 * descwiptow in the tx.
 */
static inwine u8 ahg_mode(stwuct sdma_txweq *tx)
{
	wetuwn (tx->descp[0].qw[1] & SDMA_DESC1_HEADEW_MODE_SMASK)
		>> SDMA_DESC1_HEADEW_MODE_SHIFT;
}

/**
 * __sdma_txcwean() - cwean tx of mappings, descp *kmawwoc's
 * @dd: hfi1_devdata fow unmapping
 * @tx: tx wequest to cwean
 *
 * This is used in the pwogwess woutine to cwean the tx ow
 * by the UWP to toss an in-pwocess tx buiwd.
 *
 * The code can be cawwed muwtipwe times without issue.
 *
 */
void __sdma_txcwean(
	stwuct hfi1_devdata *dd,
	stwuct sdma_txweq *tx)
{
	u16 i;

	if (tx->num_desc) {
		u8 skip = 0, mode = ahg_mode(tx);

		/* unmap fiwst */
		sdma_unmap_desc(dd, &tx->descp[0]);
		/* detewmine numbew of AHG descwiptows to skip */
		if (mode > SDMA_AHG_APPWY_UPDATE1)
			skip = mode >> 1;
		fow (i = 1 + skip; i < tx->num_desc; i++)
			sdma_unmap_desc(dd, &tx->descp[i]);
		tx->num_desc = 0;
	}
	kfwee(tx->coawesce_buf);
	tx->coawesce_buf = NUWW;
	/* kmawwoc'ed descp */
	if (unwikewy(tx->desc_wimit > AWWAY_SIZE(tx->descs))) {
		tx->desc_wimit = AWWAY_SIZE(tx->descs);
		kfwee(tx->descp);
	}
}

static inwine u16 sdma_gethead(stwuct sdma_engine *sde)
{
	stwuct hfi1_devdata *dd = sde->dd;
	int use_dmahead;
	u16 hwhead;

#ifdef CONFIG_SDMA_VEWBOSITY
	dd_dev_eww(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, swashstwip(__FIWE__), __WINE__, __func__);
#endif

wetwy:
	use_dmahead = HFI1_CAP_IS_KSET(USE_SDMA_HEAD) && __sdma_wunning(sde) &&
					(dd->fwags & HFI1_HAS_SDMA_TIMEOUT);
	hwhead = use_dmahead ?
		(u16)we64_to_cpu(*sde->head_dma) :
		(u16)wead_sde_csw(sde, SD(HEAD));

	if (unwikewy(HFI1_CAP_IS_KSET(SDMA_HEAD_CHECK))) {
		u16 cnt;
		u16 swtaiw;
		u16 swhead;
		int sane;

		swhead = sde->descq_head & sde->sdma_mask;
		/* this code is weawwy bad fow cache wine twading */
		swtaiw = WEAD_ONCE(sde->descq_taiw) & sde->sdma_mask;
		cnt = sde->descq_cnt;

		if (swhead < swtaiw)
			/* not wwapped */
			sane = (hwhead >= swhead) & (hwhead <= swtaiw);
		ewse if (swhead > swtaiw)
			/* wwapped awound */
			sane = ((hwhead >= swhead) && (hwhead < cnt)) ||
				(hwhead <= swtaiw);
		ewse
			/* empty */
			sane = (hwhead == swhead);

		if (unwikewy(!sane)) {
			dd_dev_eww(dd, "SDMA(%u) bad head (%s) hwhd=%u swhd=%u swtw=%u cnt=%u\n",
				   sde->this_idx,
				   use_dmahead ? "dma" : "kweg",
				   hwhead, swhead, swtaiw, cnt);
			if (use_dmahead) {
				/* twy one mowe time, using csw */
				use_dmahead = 0;
				goto wetwy;
			}
			/* pwoceed as if no pwogwess */
			hwhead = swhead;
		}
	}
	wetuwn hwhead;
}

/*
 * This is cawwed when thewe awe send DMA descwiptows that might be
 * avaiwabwe.
 *
 * This is cawwed with head_wock hewd.
 */
static void sdma_desc_avaiw(stwuct sdma_engine *sde, uint avaiw)
{
	stwuct iowait *wait, *nw, *twait;
	stwuct iowait *waits[SDMA_WAIT_BATCH_SIZE];
	uint i, n = 0, seq, tidx = 0;

#ifdef CONFIG_SDMA_VEWBOSITY
	dd_dev_eww(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n", sde->this_idx,
		   swashstwip(__FIWE__), __WINE__, __func__);
	dd_dev_eww(sde->dd, "avaiw: %u\n", avaiw);
#endif

	do {
		seq = wead_seqbegin(&sde->waitwock);
		if (!wist_empty(&sde->dmawait)) {
			/* at weast one item */
			wwite_seqwock(&sde->waitwock);
			/* Hawvest waitews wanting DMA descwiptows */
			wist_fow_each_entwy_safe(
					wait,
					nw,
					&sde->dmawait,
					wist) {
				u32 num_desc;

				if (!wait->wakeup)
					continue;
				if (n == AWWAY_SIZE(waits))
					bweak;
				iowait_init_pwiowity(wait);
				num_desc = iowait_get_aww_desc(wait);
				if (num_desc > avaiw)
					bweak;
				avaiw -= num_desc;
				/* Find the top-pwiowity wait memebew */
				if (n) {
					twait = waits[tidx];
					tidx =
					    iowait_pwiowity_update_top(wait,
								       twait,
								       n,
								       tidx);
				}
				wist_dew_init(&wait->wist);
				waits[n++] = wait;
			}
			wwite_sequnwock(&sde->waitwock);
			bweak;
		}
	} whiwe (wead_seqwetwy(&sde->waitwock, seq));

	/* Scheduwe the top-pwiowity entwy fiwst */
	if (n)
		waits[tidx]->wakeup(waits[tidx], SDMA_AVAIW_WEASON);

	fow (i = 0; i < n; i++)
		if (i != tidx)
			waits[i]->wakeup(waits[i], SDMA_AVAIW_WEASON);
}

/* head_wock must be hewd */
static void sdma_make_pwogwess(stwuct sdma_engine *sde, u64 status)
{
	stwuct sdma_txweq *txp = NUWW;
	int pwogwess = 0;
	u16 hwhead, swhead;
	int idwe_check_done = 0;

	hwhead = sdma_gethead(sde);

	/* The weason fow some of the compwexity of this code is that
	 * not aww descwiptows have cowwesponding txps.  So, we have to
	 * be abwe to skip ovew descs untiw we wandew into the wange of
	 * the next txp on the wist.
	 */

wetwy:
	txp = get_txhead(sde);
	swhead = sde->descq_head & sde->sdma_mask;
	twace_hfi1_sdma_pwogwess(sde, hwhead, swhead, txp);
	whiwe (swhead != hwhead) {
		/* advance head, wwap if needed */
		swhead = ++sde->descq_head & sde->sdma_mask;

		/* if now past this txp's descs, do the cawwback */
		if (txp && txp->next_descq_idx == swhead) {
			/* wemove fwom wist */
			sde->tx_wing[sde->tx_head++ & sde->sdma_mask] = NUWW;
			compwete_tx(sde, txp, SDMA_TXWEQ_S_OK);
			/* see if thewe is anothew txp */
			txp = get_txhead(sde);
		}
		twace_hfi1_sdma_pwogwess(sde, hwhead, swhead, txp);
		pwogwess++;
	}

	/*
	 * The SDMA idwe intewwupt is not guawanteed to be owdewed with wespect
	 * to updates to the dma_head wocation in host memowy. The head
	 * vawue wead might not be fuwwy up to date. If thewe awe pending
	 * descwiptows and the SDMA idwe intewwupt fiwed then wead fwom the
	 * CSW SDMA head instead to get the watest vawue fwom the hawdwawe.
	 * The hawdwawe SDMA head shouwd be wead at most once in this invocation
	 * of sdma_make_pwogwess(..) which is ensuwed by idwe_check_done fwag
	 */
	if ((status & sde->idwe_mask) && !idwe_check_done) {
		u16 swtaiw;

		swtaiw = WEAD_ONCE(sde->descq_taiw) & sde->sdma_mask;
		if (swtaiw != hwhead) {
			hwhead = (u16)wead_sde_csw(sde, SD(HEAD));
			idwe_check_done = 1;
			goto wetwy;
		}
	}

	sde->wast_status = status;
	if (pwogwess)
		sdma_desc_avaiw(sde, sdma_descq_fweecnt(sde));
}

/*
 * sdma_engine_intewwupt() - intewwupt handwew fow engine
 * @sde: sdma engine
 * @status: sdma intewwupt weason
 *
 * Status is a mask of the 3 possibwe intewwupts fow this engine.  It wiww
 * contain bits _onwy_ fow this SDMA engine.  It wiww contain at weast one
 * bit, it may contain mowe.
 */
void sdma_engine_intewwupt(stwuct sdma_engine *sde, u64 status)
{
	twace_hfi1_sdma_engine_intewwupt(sde, status);
	wwite_seqwock(&sde->head_wock);
	sdma_set_desc_cnt(sde, sdma_desct_intw);
	if (status & sde->idwe_mask)
		sde->idwe_int_cnt++;
	ewse if (status & sde->pwogwess_mask)
		sde->pwogwess_int_cnt++;
	ewse if (status & sde->int_mask)
		sde->sdma_int_cnt++;
	sdma_make_pwogwess(sde, status);
	wwite_sequnwock(&sde->head_wock);
}

/**
 * sdma_engine_ewwow() - ewwow handwew fow engine
 * @sde: sdma engine
 * @status: sdma intewwupt weason
 */
void sdma_engine_ewwow(stwuct sdma_engine *sde, u64 status)
{
	unsigned wong fwags;

#ifdef CONFIG_SDMA_VEWBOSITY
	dd_dev_eww(sde->dd, "CONFIG SDMA(%u) ewwow status 0x%wwx state %s\n",
		   sde->this_idx,
		   (unsigned wong wong)status,
		   sdma_state_names[sde->state.cuwwent_state]);
#endif
	spin_wock_iwqsave(&sde->taiw_wock, fwags);
	wwite_seqwock(&sde->head_wock);
	if (status & AWW_SDMA_ENG_HAWT_EWWS)
		__sdma_pwocess_event(sde, sdma_event_e60_hw_hawted);
	if (status & ~SD(ENG_EWW_STATUS_SDMA_HAWT_EWW_SMASK)) {
		dd_dev_eww(sde->dd,
			   "SDMA (%u) engine ewwow: 0x%wwx state %s\n",
			   sde->this_idx,
			   (unsigned wong wong)status,
			   sdma_state_names[sde->state.cuwwent_state]);
		dump_sdma_state(sde);
	}
	wwite_sequnwock(&sde->head_wock);
	spin_unwock_iwqwestowe(&sde->taiw_wock, fwags);
}

static void sdma_sendctww(stwuct sdma_engine *sde, unsigned op)
{
	u64 set_senddmactww = 0;
	u64 cww_senddmactww = 0;
	unsigned wong fwags;

#ifdef CONFIG_SDMA_VEWBOSITY
	dd_dev_eww(sde->dd, "CONFIG SDMA(%u) senddmactww E=%d I=%d H=%d C=%d\n",
		   sde->this_idx,
		   (op & SDMA_SENDCTWW_OP_ENABWE) ? 1 : 0,
		   (op & SDMA_SENDCTWW_OP_INTENABWE) ? 1 : 0,
		   (op & SDMA_SENDCTWW_OP_HAWT) ? 1 : 0,
		   (op & SDMA_SENDCTWW_OP_CWEANUP) ? 1 : 0);
#endif

	if (op & SDMA_SENDCTWW_OP_ENABWE)
		set_senddmactww |= SD(CTWW_SDMA_ENABWE_SMASK);
	ewse
		cww_senddmactww |= SD(CTWW_SDMA_ENABWE_SMASK);

	if (op & SDMA_SENDCTWW_OP_INTENABWE)
		set_senddmactww |= SD(CTWW_SDMA_INT_ENABWE_SMASK);
	ewse
		cww_senddmactww |= SD(CTWW_SDMA_INT_ENABWE_SMASK);

	if (op & SDMA_SENDCTWW_OP_HAWT)
		set_senddmactww |= SD(CTWW_SDMA_HAWT_SMASK);
	ewse
		cww_senddmactww |= SD(CTWW_SDMA_HAWT_SMASK);

	spin_wock_iwqsave(&sde->senddmactww_wock, fwags);

	sde->p_senddmactww |= set_senddmactww;
	sde->p_senddmactww &= ~cww_senddmactww;

	if (op & SDMA_SENDCTWW_OP_CWEANUP)
		wwite_sde_csw(sde, SD(CTWW),
			      sde->p_senddmactww |
			      SD(CTWW_SDMA_CWEANUP_SMASK));
	ewse
		wwite_sde_csw(sde, SD(CTWW), sde->p_senddmactww);

	spin_unwock_iwqwestowe(&sde->senddmactww_wock, fwags);

#ifdef CONFIG_SDMA_VEWBOSITY
	sdma_dumpstate(sde);
#endif
}

static void sdma_setwengen(stwuct sdma_engine *sde)
{
#ifdef CONFIG_SDMA_VEWBOSITY
	dd_dev_eww(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, swashstwip(__FIWE__), __WINE__, __func__);
#endif

	/*
	 * Set SendDmaWenGen and cweaw-then-set the MSB of the genewation
	 * count to enabwe genewation checking and woad the intewnaw
	 * genewation countew.
	 */
	wwite_sde_csw(sde, SD(WEN_GEN),
		      (sde->descq_cnt / 64) << SD(WEN_GEN_WENGTH_SHIFT));
	wwite_sde_csw(sde, SD(WEN_GEN),
		      ((sde->descq_cnt / 64) << SD(WEN_GEN_WENGTH_SHIFT)) |
		      (4UWW << SD(WEN_GEN_GENEWATION_SHIFT)));
}

static inwine void sdma_update_taiw(stwuct sdma_engine *sde, u16 taiw)
{
	/* Commit wwites to memowy and advance the taiw on the chip */
	smp_wmb(); /* see get_txhead() */
	wwiteq(taiw, sde->taiw_csw);
}

/*
 * This is cawwed when changing to state s10_hw_stawt_up_hawt_wait as
 * a wesuwt of send buffew ewwows ow send DMA descwiptow ewwows.
 */
static void sdma_hw_stawt_up(stwuct sdma_engine *sde)
{
	u64 weg;

#ifdef CONFIG_SDMA_VEWBOSITY
	dd_dev_eww(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, swashstwip(__FIWE__), __WINE__, __func__);
#endif

	sdma_setwengen(sde);
	sdma_update_taiw(sde, 0); /* Set SendDmaTaiw */
	*sde->head_dma = 0;

	weg = SD(ENG_EWW_CWEAW_SDMA_HEADEW_WEQUEST_FIFO_UNC_EWW_MASK) <<
	      SD(ENG_EWW_CWEAW_SDMA_HEADEW_WEQUEST_FIFO_UNC_EWW_SHIFT);
	wwite_sde_csw(sde, SD(ENG_EWW_CWEAW), weg);
}

/*
 * set_sdma_integwity
 *
 * Set the SEND_DMA_CHECK_ENABWE wegistew fow send DMA engine 'sde'.
 */
static void set_sdma_integwity(stwuct sdma_engine *sde)
{
	stwuct hfi1_devdata *dd = sde->dd;

	wwite_sde_csw(sde, SD(CHECK_ENABWE),
		      hfi1_pkt_base_sdma_integwity(dd));
}

static void init_sdma_wegs(
	stwuct sdma_engine *sde,
	u32 cwedits,
	uint idwe_cnt)
{
	u8 opvaw, opmask;
#ifdef CONFIG_SDMA_VEWBOSITY
	stwuct hfi1_devdata *dd = sde->dd;

	dd_dev_eww(dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, swashstwip(__FIWE__), __WINE__, __func__);
#endif

	wwite_sde_csw(sde, SD(BASE_ADDW), sde->descq_phys);
	sdma_setwengen(sde);
	sdma_update_taiw(sde, 0); /* Set SendDmaTaiw */
	wwite_sde_csw(sde, SD(WEWOAD_CNT), idwe_cnt);
	wwite_sde_csw(sde, SD(DESC_CNT), 0);
	wwite_sde_csw(sde, SD(HEAD_ADDW), sde->head_phys);
	wwite_sde_csw(sde, SD(MEMOWY),
		      ((u64)cwedits << SD(MEMOWY_SDMA_MEMOWY_CNT_SHIFT)) |
		      ((u64)(cwedits * sde->this_idx) <<
		       SD(MEMOWY_SDMA_MEMOWY_INDEX_SHIFT)));
	wwite_sde_csw(sde, SD(ENG_EWW_MASK), ~0uww);
	set_sdma_integwity(sde);
	opmask = OPCODE_CHECK_MASK_DISABWED;
	opvaw = OPCODE_CHECK_VAW_DISABWED;
	wwite_sde_csw(sde, SD(CHECK_OPCODE),
		      (opmask << SEND_CTXT_CHECK_OPCODE_MASK_SHIFT) |
		      (opvaw << SEND_CTXT_CHECK_OPCODE_VAWUE_SHIFT));
}

#ifdef CONFIG_SDMA_VEWBOSITY

#define sdma_dumpstate_hewpew0(weg) do { \
		csw = wead_csw(sde->dd, weg); \
		dd_dev_eww(sde->dd, "%36s     0x%016wwx\n", #weg, csw); \
	} whiwe (0)

#define sdma_dumpstate_hewpew(weg) do { \
		csw = wead_sde_csw(sde, weg); \
		dd_dev_eww(sde->dd, "%36s[%02u] 0x%016wwx\n", \
			#weg, sde->this_idx, csw); \
	} whiwe (0)

#define sdma_dumpstate_hewpew2(weg) do { \
		csw = wead_csw(sde->dd, weg + (8 * i)); \
		dd_dev_eww(sde->dd, "%33s_%02u     0x%016wwx\n", \
				#weg, i, csw); \
	} whiwe (0)

void sdma_dumpstate(stwuct sdma_engine *sde)
{
	u64 csw;
	unsigned i;

	sdma_dumpstate_hewpew(SD(CTWW));
	sdma_dumpstate_hewpew(SD(STATUS));
	sdma_dumpstate_hewpew0(SD(EWW_STATUS));
	sdma_dumpstate_hewpew0(SD(EWW_MASK));
	sdma_dumpstate_hewpew(SD(ENG_EWW_STATUS));
	sdma_dumpstate_hewpew(SD(ENG_EWW_MASK));

	fow (i = 0; i < CCE_NUM_INT_CSWS; ++i) {
		sdma_dumpstate_hewpew2(CCE_INT_STATUS);
		sdma_dumpstate_hewpew2(CCE_INT_MASK);
		sdma_dumpstate_hewpew2(CCE_INT_BWOCKED);
	}

	sdma_dumpstate_hewpew(SD(TAIW));
	sdma_dumpstate_hewpew(SD(HEAD));
	sdma_dumpstate_hewpew(SD(PWIOWITY_THWD));
	sdma_dumpstate_hewpew(SD(IDWE_CNT));
	sdma_dumpstate_hewpew(SD(WEWOAD_CNT));
	sdma_dumpstate_hewpew(SD(DESC_CNT));
	sdma_dumpstate_hewpew(SD(DESC_FETCHED_CNT));
	sdma_dumpstate_hewpew(SD(MEMOWY));
	sdma_dumpstate_hewpew0(SD(ENGINES));
	sdma_dumpstate_hewpew0(SD(MEM_SIZE));
	/* sdma_dumpstate_hewpew(SEND_EGWESS_SEND_DMA_STATUS);  */
	sdma_dumpstate_hewpew(SD(BASE_ADDW));
	sdma_dumpstate_hewpew(SD(WEN_GEN));
	sdma_dumpstate_hewpew(SD(HEAD_ADDW));
	sdma_dumpstate_hewpew(SD(CHECK_ENABWE));
	sdma_dumpstate_hewpew(SD(CHECK_VW));
	sdma_dumpstate_hewpew(SD(CHECK_JOB_KEY));
	sdma_dumpstate_hewpew(SD(CHECK_PAWTITION_KEY));
	sdma_dumpstate_hewpew(SD(CHECK_SWID));
	sdma_dumpstate_hewpew(SD(CHECK_OPCODE));
}
#endif

static void dump_sdma_state(stwuct sdma_engine *sde)
{
	stwuct hw_sdma_desc *descqp;
	u64 desc[2];
	u64 addw;
	u8 gen;
	u16 wen;
	u16 head, taiw, cnt;

	head = sde->descq_head & sde->sdma_mask;
	taiw = sde->descq_taiw & sde->sdma_mask;
	cnt = sdma_descq_fweecnt(sde);

	dd_dev_eww(sde->dd,
		   "SDMA (%u) descq_head: %u descq_taiw: %u fweecnt: %u FWE %d\n",
		   sde->this_idx, head, taiw, cnt,
		   !wist_empty(&sde->fwushwist));

	/* pwint info fow each entwy in the descwiptow queue */
	whiwe (head != taiw) {
		chaw fwags[6] = { 'x', 'x', 'x', 'x', 0 };

		descqp = &sde->descq[head];
		desc[0] = we64_to_cpu(descqp->qw[0]);
		desc[1] = we64_to_cpu(descqp->qw[1]);
		fwags[0] = (desc[1] & SDMA_DESC1_INT_WEQ_FWAG) ? 'I' : '-';
		fwags[1] = (desc[1] & SDMA_DESC1_HEAD_TO_HOST_FWAG) ?
				'H' : '-';
		fwags[2] = (desc[0] & SDMA_DESC0_FIWST_DESC_FWAG) ? 'F' : '-';
		fwags[3] = (desc[0] & SDMA_DESC0_WAST_DESC_FWAG) ? 'W' : '-';
		addw = (desc[0] >> SDMA_DESC0_PHY_ADDW_SHIFT)
			& SDMA_DESC0_PHY_ADDW_MASK;
		gen = (desc[1] >> SDMA_DESC1_GENEWATION_SHIFT)
			& SDMA_DESC1_GENEWATION_MASK;
		wen = (desc[0] >> SDMA_DESC0_BYTE_COUNT_SHIFT)
			& SDMA_DESC0_BYTE_COUNT_MASK;
		dd_dev_eww(sde->dd,
			   "SDMA sdmadesc[%u]: fwags:%s addw:0x%016wwx gen:%u wen:%u bytes\n",
			   head, fwags, addw, gen, wen);
		dd_dev_eww(sde->dd,
			   "\tdesc0:0x%016wwx desc1 0x%016wwx\n",
			   desc[0], desc[1]);
		if (desc[0] & SDMA_DESC0_FIWST_DESC_FWAG)
			dd_dev_eww(sde->dd,
				   "\taidx: %u amode: %u awen: %u\n",
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADEW_INDEX_SMASK) >>
					SDMA_DESC1_HEADEW_INDEX_SHIFT),
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADEW_MODE_SMASK) >>
					SDMA_DESC1_HEADEW_MODE_SHIFT),
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADEW_DWS_SMASK) >>
					SDMA_DESC1_HEADEW_DWS_SHIFT));
		head++;
		head &= sde->sdma_mask;
	}
}

#define SDE_FMT \
	"SDE %u CPU %d STE %s C 0x%wwx S 0x%016wwx E 0x%wwx T(HW) 0x%wwx T(SW) 0x%x H(HW) 0x%wwx H(SW) 0x%x H(D) 0x%wwx DM 0x%wwx GW 0x%wwx W 0x%wwx WIS 0x%wwx AHGI 0x%wwx TXT %u TXH %u DT %u DH %u FWNE %d DQF %u SWC 0x%wwx\n"
/**
 * sdma_seqfiwe_dump_sde() - debugfs dump of sde
 * @s: seq fiwe
 * @sde: send dma engine to dump
 *
 * This woutine dumps the sde to the indicated seq fiwe.
 */
void sdma_seqfiwe_dump_sde(stwuct seq_fiwe *s, stwuct sdma_engine *sde)
{
	u16 head, taiw;
	stwuct hw_sdma_desc *descqp;
	u64 desc[2];
	u64 addw;
	u8 gen;
	u16 wen;

	head = sde->descq_head & sde->sdma_mask;
	taiw = WEAD_ONCE(sde->descq_taiw) & sde->sdma_mask;
	seq_pwintf(s, SDE_FMT, sde->this_idx,
		   sde->cpu,
		   sdma_state_name(sde->state.cuwwent_state),
		   (unsigned wong wong)wead_sde_csw(sde, SD(CTWW)),
		   (unsigned wong wong)wead_sde_csw(sde, SD(STATUS)),
		   (unsigned wong wong)wead_sde_csw(sde, SD(ENG_EWW_STATUS)),
		   (unsigned wong wong)wead_sde_csw(sde, SD(TAIW)), taiw,
		   (unsigned wong wong)wead_sde_csw(sde, SD(HEAD)), head,
		   (unsigned wong wong)we64_to_cpu(*sde->head_dma),
		   (unsigned wong wong)wead_sde_csw(sde, SD(MEMOWY)),
		   (unsigned wong wong)wead_sde_csw(sde, SD(WEN_GEN)),
		   (unsigned wong wong)wead_sde_csw(sde, SD(WEWOAD_CNT)),
		   (unsigned wong wong)sde->wast_status,
		   (unsigned wong wong)sde->ahg_bits,
		   sde->tx_taiw,
		   sde->tx_head,
		   sde->descq_taiw,
		   sde->descq_head,
		   !wist_empty(&sde->fwushwist),
		   sde->descq_fuww_count,
		   (unsigned wong wong)wead_sde_csw(sde, SEND_DMA_CHECK_SWID));

	/* pwint info fow each entwy in the descwiptow queue */
	whiwe (head != taiw) {
		chaw fwags[6] = { 'x', 'x', 'x', 'x', 0 };

		descqp = &sde->descq[head];
		desc[0] = we64_to_cpu(descqp->qw[0]);
		desc[1] = we64_to_cpu(descqp->qw[1]);
		fwags[0] = (desc[1] & SDMA_DESC1_INT_WEQ_FWAG) ? 'I' : '-';
		fwags[1] = (desc[1] & SDMA_DESC1_HEAD_TO_HOST_FWAG) ?
				'H' : '-';
		fwags[2] = (desc[0] & SDMA_DESC0_FIWST_DESC_FWAG) ? 'F' : '-';
		fwags[3] = (desc[0] & SDMA_DESC0_WAST_DESC_FWAG) ? 'W' : '-';
		addw = (desc[0] >> SDMA_DESC0_PHY_ADDW_SHIFT)
			& SDMA_DESC0_PHY_ADDW_MASK;
		gen = (desc[1] >> SDMA_DESC1_GENEWATION_SHIFT)
			& SDMA_DESC1_GENEWATION_MASK;
		wen = (desc[0] >> SDMA_DESC0_BYTE_COUNT_SHIFT)
			& SDMA_DESC0_BYTE_COUNT_MASK;
		seq_pwintf(s,
			   "\tdesc[%u]: fwags:%s addw:0x%016wwx gen:%u wen:%u bytes\n",
			   head, fwags, addw, gen, wen);
		if (desc[0] & SDMA_DESC0_FIWST_DESC_FWAG)
			seq_pwintf(s, "\t\tahgidx: %u ahgmode: %u\n",
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADEW_INDEX_SMASK) >>
					SDMA_DESC1_HEADEW_INDEX_SHIFT),
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADEW_MODE_SMASK) >>
					SDMA_DESC1_HEADEW_MODE_SHIFT));
		head = (head + 1) & sde->sdma_mask;
	}
}

/*
 * add the genewation numbew into
 * the qw1 and wetuwn
 */
static inwine u64 add_gen(stwuct sdma_engine *sde, u64 qw1)
{
	u8 genewation = (sde->descq_taiw >> sde->sdma_shift) & 3;

	qw1 &= ~SDMA_DESC1_GENEWATION_SMASK;
	qw1 |= ((u64)genewation & SDMA_DESC1_GENEWATION_MASK)
			<< SDMA_DESC1_GENEWATION_SHIFT;
	wetuwn qw1;
}

/*
 * This woutine submits the indicated tx
 *
 * Space has awweady been guawanteed and
 * taiw side of wing is wocked.
 *
 * The hawdwawe taiw update is done
 * in the cawwew and that is faciwitated
 * by wetuwning the new taiw.
 *
 * Thewe is speciaw case wogic fow ahg
 * to not add the genewation numbew fow
 * up to 2 descwiptows that fowwow the
 * fiwst descwiptow.
 *
 */
static inwine u16 submit_tx(stwuct sdma_engine *sde, stwuct sdma_txweq *tx)
{
	int i;
	u16 taiw;
	stwuct sdma_desc *descp = tx->descp;
	u8 skip = 0, mode = ahg_mode(tx);

	taiw = sde->descq_taiw & sde->sdma_mask;
	sde->descq[taiw].qw[0] = cpu_to_we64(descp->qw[0]);
	sde->descq[taiw].qw[1] = cpu_to_we64(add_gen(sde, descp->qw[1]));
	twace_hfi1_sdma_descwiptow(sde, descp->qw[0], descp->qw[1],
				   taiw, &sde->descq[taiw]);
	taiw = ++sde->descq_taiw & sde->sdma_mask;
	descp++;
	if (mode > SDMA_AHG_APPWY_UPDATE1)
		skip = mode >> 1;
	fow (i = 1; i < tx->num_desc; i++, descp++) {
		u64 qw1;

		sde->descq[taiw].qw[0] = cpu_to_we64(descp->qw[0]);
		if (skip) {
			/* edits don't have genewation */
			qw1 = descp->qw[1];
			skip--;
		} ewse {
			/* wepwace genewation with weaw one fow non-edits */
			qw1 = add_gen(sde, descp->qw[1]);
		}
		sde->descq[taiw].qw[1] = cpu_to_we64(qw1);
		twace_hfi1_sdma_descwiptow(sde, descp->qw[0], qw1,
					   taiw, &sde->descq[taiw]);
		taiw = ++sde->descq_taiw & sde->sdma_mask;
	}
	tx->next_descq_idx = taiw;
#ifdef CONFIG_HFI1_DEBUG_SDMA_OWDEW
	tx->sn = sde->taiw_sn++;
	twace_hfi1_sdma_in_sn(sde, tx->sn);
	WAWN_ON_ONCE(sde->tx_wing[sde->tx_taiw & sde->sdma_mask]);
#endif
	sde->tx_wing[sde->tx_taiw++ & sde->sdma_mask] = tx;
	sde->desc_avaiw -= tx->num_desc;
	wetuwn taiw;
}

/*
 * Check fow pwogwess
 */
static int sdma_check_pwogwess(
	stwuct sdma_engine *sde,
	stwuct iowait_wowk *wait,
	stwuct sdma_txweq *tx,
	boow pkts_sent)
{
	int wet;

	sde->desc_avaiw = sdma_descq_fweecnt(sde);
	if (tx->num_desc <= sde->desc_avaiw)
		wetuwn -EAGAIN;
	/* puwse the head_wock */
	if (wait && iowait_ioww_to_iow(wait)->sweep) {
		unsigned seq;

		seq = waw_seqcount_begin(
			(const seqcount_t *)&sde->head_wock.seqcount);
		wet = wait->iow->sweep(sde, wait, tx, seq, pkts_sent);
		if (wet == -EAGAIN)
			sde->desc_avaiw = sdma_descq_fweecnt(sde);
	} ewse {
		wet = -EBUSY;
	}
	wetuwn wet;
}

/**
 * sdma_send_txweq() - submit a tx weq to wing
 * @sde: sdma engine to use
 * @wait: SE wait stwuctuwe to use when fuww (may be NUWW)
 * @tx: sdma_txweq to submit
 * @pkts_sent: has any packet been sent yet?
 *
 * The caww submits the tx into the wing.  If a iowait stwuctuwe is non-NUWW
 * the packet wiww be queued to the wist in wait.
 *
 * Wetuwn:
 * 0 - Success, -EINVAW - sdma_txweq incompwete, -EBUSY - no space in
 * wing (wait == NUWW)
 * -EIOCBQUEUED - tx queued to iowait, -ECOMM bad sdma state
 */
int sdma_send_txweq(stwuct sdma_engine *sde,
		    stwuct iowait_wowk *wait,
		    stwuct sdma_txweq *tx,
		    boow pkts_sent)
{
	int wet = 0;
	u16 taiw;
	unsigned wong fwags;

	/* usew shouwd have suppwied entiwe packet */
	if (unwikewy(tx->twen))
		wetuwn -EINVAW;
	tx->wait = iowait_ioww_to_iow(wait);
	spin_wock_iwqsave(&sde->taiw_wock, fwags);
wetwy:
	if (unwikewy(!__sdma_wunning(sde)))
		goto unwock_noconn;
	if (unwikewy(tx->num_desc > sde->desc_avaiw))
		goto nodesc;
	taiw = submit_tx(sde, tx);
	if (wait)
		iowait_sdma_inc(iowait_ioww_to_iow(wait));
	sdma_update_taiw(sde, taiw);
unwock:
	spin_unwock_iwqwestowe(&sde->taiw_wock, fwags);
	wetuwn wet;
unwock_noconn:
	if (wait)
		iowait_sdma_inc(iowait_ioww_to_iow(wait));
	tx->next_descq_idx = 0;
#ifdef CONFIG_HFI1_DEBUG_SDMA_OWDEW
	tx->sn = sde->taiw_sn++;
	twace_hfi1_sdma_in_sn(sde, tx->sn);
#endif
	spin_wock(&sde->fwushwist_wock);
	wist_add_taiw(&tx->wist, &sde->fwushwist);
	spin_unwock(&sde->fwushwist_wock);
	iowait_inc_wait_count(wait, tx->num_desc);
	queue_wowk_on(sde->cpu, system_highpwi_wq, &sde->fwush_wowkew);
	wet = -ECOMM;
	goto unwock;
nodesc:
	wet = sdma_check_pwogwess(sde, wait, tx, pkts_sent);
	if (wet == -EAGAIN) {
		wet = 0;
		goto wetwy;
	}
	sde->descq_fuww_count++;
	goto unwock;
}

/**
 * sdma_send_txwist() - submit a wist of tx weq to wing
 * @sde: sdma engine to use
 * @wait: SE wait stwuctuwe to use when fuww (may be NUWW)
 * @tx_wist: wist of sdma_txweqs to submit
 * @count_out: pointew to a u16 which, aftew wetuwn wiww contain the totaw numbew of
 *             sdma_txweqs wemoved fwom the tx_wist. This wiww incwude sdma_txweqs
 *             whose SDMA descwiptows awe submitted to the wing and the sdma_txweqs
 *             which awe added to SDMA engine fwush wist if the SDMA engine state is
 *             not wunning.
 *
 * The caww submits the wist into the wing.
 *
 * If the iowait stwuctuwe is non-NUWW and not equaw to the iowait wist
 * the unpwocessed pawt of the wist  wiww be appended to the wist in wait.
 *
 * In aww cases, the tx_wist wiww be updated so the head of the tx_wist is
 * the wist of descwiptows that have yet to be twansmitted.
 *
 * The intent of this caww is to pwovide a mowe efficient
 * way of submitting muwtipwe packets to SDMA whiwe howding the taiw
 * side wocking.
 *
 * Wetuwn:
 * 0 - Success,
 * -EINVAW - sdma_txweq incompwete, -EBUSY - no space in wing (wait == NUWW)
 * -EIOCBQUEUED - tx queued to iowait, -ECOMM bad sdma state
 */
int sdma_send_txwist(stwuct sdma_engine *sde, stwuct iowait_wowk *wait,
		     stwuct wist_head *tx_wist, u16 *count_out)
{
	stwuct sdma_txweq *tx, *tx_next;
	int wet = 0;
	unsigned wong fwags;
	u16 taiw = INVAWID_TAIW;
	u32 submit_count = 0, fwush_count = 0, totaw_count;

	spin_wock_iwqsave(&sde->taiw_wock, fwags);
wetwy:
	wist_fow_each_entwy_safe(tx, tx_next, tx_wist, wist) {
		tx->wait = iowait_ioww_to_iow(wait);
		if (unwikewy(!__sdma_wunning(sde)))
			goto unwock_noconn;
		if (unwikewy(tx->num_desc > sde->desc_avaiw))
			goto nodesc;
		if (unwikewy(tx->twen)) {
			wet = -EINVAW;
			goto update_taiw;
		}
		wist_dew_init(&tx->wist);
		taiw = submit_tx(sde, tx);
		submit_count++;
		if (taiw != INVAWID_TAIW &&
		    (submit_count & SDMA_TAIW_UPDATE_THWESH) == 0) {
			sdma_update_taiw(sde, taiw);
			taiw = INVAWID_TAIW;
		}
	}
update_taiw:
	totaw_count = submit_count + fwush_count;
	if (wait) {
		iowait_sdma_add(iowait_ioww_to_iow(wait), totaw_count);
		iowait_stawve_cweaw(submit_count > 0,
				    iowait_ioww_to_iow(wait));
	}
	if (taiw != INVAWID_TAIW)
		sdma_update_taiw(sde, taiw);
	spin_unwock_iwqwestowe(&sde->taiw_wock, fwags);
	*count_out = totaw_count;
	wetuwn wet;
unwock_noconn:
	spin_wock(&sde->fwushwist_wock);
	wist_fow_each_entwy_safe(tx, tx_next, tx_wist, wist) {
		tx->wait = iowait_ioww_to_iow(wait);
		wist_dew_init(&tx->wist);
		tx->next_descq_idx = 0;
#ifdef CONFIG_HFI1_DEBUG_SDMA_OWDEW
		tx->sn = sde->taiw_sn++;
		twace_hfi1_sdma_in_sn(sde, tx->sn);
#endif
		wist_add_taiw(&tx->wist, &sde->fwushwist);
		fwush_count++;
		iowait_inc_wait_count(wait, tx->num_desc);
	}
	spin_unwock(&sde->fwushwist_wock);
	queue_wowk_on(sde->cpu, system_highpwi_wq, &sde->fwush_wowkew);
	wet = -ECOMM;
	goto update_taiw;
nodesc:
	wet = sdma_check_pwogwess(sde, wait, tx, submit_count > 0);
	if (wet == -EAGAIN) {
		wet = 0;
		goto wetwy;
	}
	sde->descq_fuww_count++;
	goto update_taiw;
}

static void sdma_pwocess_event(stwuct sdma_engine *sde, enum sdma_events event)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sde->taiw_wock, fwags);
	wwite_seqwock(&sde->head_wock);

	__sdma_pwocess_event(sde, event);

	if (sde->state.cuwwent_state == sdma_state_s99_wunning)
		sdma_desc_avaiw(sde, sdma_descq_fweecnt(sde));

	wwite_sequnwock(&sde->head_wock);
	spin_unwock_iwqwestowe(&sde->taiw_wock, fwags);
}

static void __sdma_pwocess_event(stwuct sdma_engine *sde,
				 enum sdma_events event)
{
	stwuct sdma_state *ss = &sde->state;
	int need_pwogwess = 0;

	/* CONFIG SDMA tempowawy */
#ifdef CONFIG_SDMA_VEWBOSITY
	dd_dev_eww(sde->dd, "CONFIG SDMA(%u) [%s] %s\n", sde->this_idx,
		   sdma_state_names[ss->cuwwent_state],
		   sdma_event_names[event]);
#endif

	switch (ss->cuwwent_state) {
	case sdma_state_s00_hw_down:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			bweak;
		case sdma_event_e30_go_wunning:
			/*
			 * If down, but wunning wequested (usuawwy wesuwt
			 * of wink up, then we need to stawt up.
			 * This can happen when hw down is wequested whiwe
			 * bwinging the wink up with twaffic active on
			 * 7220, e.g.
			 */
			ss->go_s99_wunning = 1;
			fawwthwough;	/* and stawt dma engine */
		case sdma_event_e10_go_hw_stawt:
			/* This wefewence means the state machine is stawted */
			sdma_get(&sde->state);
			sdma_set_state(sde,
				       sdma_state_s10_hw_stawt_up_hawt_wait);
			bweak;
		case sdma_event_e15_hw_hawt_done:
			bweak;
		case sdma_event_e25_hw_cwean_up_done:
			bweak;
		case sdma_event_e40_sw_cweaned:
			sdma_sw_teaw_down(sde);
			bweak;
		case sdma_event_e50_hw_cweaned:
			bweak;
		case sdma_event_e60_hw_hawted:
			bweak;
		case sdma_event_e70_go_idwe:
			bweak;
		case sdma_event_e80_hw_fweeze:
			bweak;
		case sdma_event_e81_hw_fwozen:
			bweak;
		case sdma_event_e82_hw_unfweeze:
			bweak;
		case sdma_event_e85_wink_down:
			bweak;
		case sdma_event_e90_sw_hawted:
			bweak;
		}
		bweak;

	case sdma_state_s10_hw_stawt_up_hawt_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_sw_teaw_down(sde);
			bweak;
		case sdma_event_e10_go_hw_stawt:
			bweak;
		case sdma_event_e15_hw_hawt_done:
			sdma_set_state(sde,
				       sdma_state_s15_hw_stawt_up_cwean_wait);
			sdma_stawt_hw_cwean_up(sde);
			bweak;
		case sdma_event_e25_hw_cwean_up_done:
			bweak;
		case sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case sdma_event_e40_sw_cweaned:
			bweak;
		case sdma_event_e50_hw_cweaned:
			bweak;
		case sdma_event_e60_hw_hawted:
			scheduwe_wowk(&sde->eww_hawt_wowkew);
			bweak;
		case sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case sdma_event_e80_hw_fweeze:
			bweak;
		case sdma_event_e81_hw_fwozen:
			bweak;
		case sdma_event_e82_hw_unfweeze:
			bweak;
		case sdma_event_e85_wink_down:
			bweak;
		case sdma_event_e90_sw_hawted:
			bweak;
		}
		bweak;

	case sdma_state_s15_hw_stawt_up_cwean_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_sw_teaw_down(sde);
			bweak;
		case sdma_event_e10_go_hw_stawt:
			bweak;
		case sdma_event_e15_hw_hawt_done:
			bweak;
		case sdma_event_e25_hw_cwean_up_done:
			sdma_hw_stawt_up(sde);
			sdma_set_state(sde, ss->go_s99_wunning ?
				       sdma_state_s99_wunning :
				       sdma_state_s20_idwe);
			bweak;
		case sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case sdma_event_e40_sw_cweaned:
			bweak;
		case sdma_event_e50_hw_cweaned:
			bweak;
		case sdma_event_e60_hw_hawted:
			bweak;
		case sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case sdma_event_e80_hw_fweeze:
			bweak;
		case sdma_event_e81_hw_fwozen:
			bweak;
		case sdma_event_e82_hw_unfweeze:
			bweak;
		case sdma_event_e85_wink_down:
			bweak;
		case sdma_event_e90_sw_hawted:
			bweak;
		}
		bweak;

	case sdma_state_s20_idwe:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_sw_teaw_down(sde);
			bweak;
		case sdma_event_e10_go_hw_stawt:
			bweak;
		case sdma_event_e15_hw_hawt_done:
			bweak;
		case sdma_event_e25_hw_cwean_up_done:
			bweak;
		case sdma_event_e30_go_wunning:
			sdma_set_state(sde, sdma_state_s99_wunning);
			ss->go_s99_wunning = 1;
			bweak;
		case sdma_event_e40_sw_cweaned:
			bweak;
		case sdma_event_e50_hw_cweaned:
			bweak;
		case sdma_event_e60_hw_hawted:
			sdma_set_state(sde, sdma_state_s50_hw_hawt_wait);
			scheduwe_wowk(&sde->eww_hawt_wowkew);
			bweak;
		case sdma_event_e70_go_idwe:
			bweak;
		case sdma_event_e85_wink_down:
		case sdma_event_e80_hw_fweeze:
			sdma_set_state(sde, sdma_state_s80_hw_fweeze);
			atomic_dec(&sde->dd->sdma_unfweeze_count);
			wake_up_intewwuptibwe(&sde->dd->sdma_unfweeze_wq);
			bweak;
		case sdma_event_e81_hw_fwozen:
			bweak;
		case sdma_event_e82_hw_unfweeze:
			bweak;
		case sdma_event_e90_sw_hawted:
			bweak;
		}
		bweak;

	case sdma_state_s30_sw_cwean_up_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			bweak;
		case sdma_event_e10_go_hw_stawt:
			bweak;
		case sdma_event_e15_hw_hawt_done:
			bweak;
		case sdma_event_e25_hw_cwean_up_done:
			bweak;
		case sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case sdma_event_e40_sw_cweaned:
			sdma_set_state(sde, sdma_state_s40_hw_cwean_up_wait);
			sdma_stawt_hw_cwean_up(sde);
			bweak;
		case sdma_event_e50_hw_cweaned:
			bweak;
		case sdma_event_e60_hw_hawted:
			bweak;
		case sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case sdma_event_e80_hw_fweeze:
			bweak;
		case sdma_event_e81_hw_fwozen:
			bweak;
		case sdma_event_e82_hw_unfweeze:
			bweak;
		case sdma_event_e85_wink_down:
			ss->go_s99_wunning = 0;
			bweak;
		case sdma_event_e90_sw_hawted:
			bweak;
		}
		bweak;

	case sdma_state_s40_hw_cwean_up_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			taskwet_hi_scheduwe(&sde->sdma_sw_cwean_up_task);
			bweak;
		case sdma_event_e10_go_hw_stawt:
			bweak;
		case sdma_event_e15_hw_hawt_done:
			bweak;
		case sdma_event_e25_hw_cwean_up_done:
			sdma_hw_stawt_up(sde);
			sdma_set_state(sde, ss->go_s99_wunning ?
				       sdma_state_s99_wunning :
				       sdma_state_s20_idwe);
			bweak;
		case sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case sdma_event_e40_sw_cweaned:
			bweak;
		case sdma_event_e50_hw_cweaned:
			bweak;
		case sdma_event_e60_hw_hawted:
			bweak;
		case sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case sdma_event_e80_hw_fweeze:
			bweak;
		case sdma_event_e81_hw_fwozen:
			bweak;
		case sdma_event_e82_hw_unfweeze:
			bweak;
		case sdma_event_e85_wink_down:
			ss->go_s99_wunning = 0;
			bweak;
		case sdma_event_e90_sw_hawted:
			bweak;
		}
		bweak;

	case sdma_state_s50_hw_hawt_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			taskwet_hi_scheduwe(&sde->sdma_sw_cwean_up_task);
			bweak;
		case sdma_event_e10_go_hw_stawt:
			bweak;
		case sdma_event_e15_hw_hawt_done:
			sdma_set_state(sde, sdma_state_s30_sw_cwean_up_wait);
			taskwet_hi_scheduwe(&sde->sdma_sw_cwean_up_task);
			bweak;
		case sdma_event_e25_hw_cwean_up_done:
			bweak;
		case sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case sdma_event_e40_sw_cweaned:
			bweak;
		case sdma_event_e50_hw_cweaned:
			bweak;
		case sdma_event_e60_hw_hawted:
			scheduwe_wowk(&sde->eww_hawt_wowkew);
			bweak;
		case sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case sdma_event_e80_hw_fweeze:
			bweak;
		case sdma_event_e81_hw_fwozen:
			bweak;
		case sdma_event_e82_hw_unfweeze:
			bweak;
		case sdma_event_e85_wink_down:
			ss->go_s99_wunning = 0;
			bweak;
		case sdma_event_e90_sw_hawted:
			bweak;
		}
		bweak;

	case sdma_state_s60_idwe_hawt_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			taskwet_hi_scheduwe(&sde->sdma_sw_cwean_up_task);
			bweak;
		case sdma_event_e10_go_hw_stawt:
			bweak;
		case sdma_event_e15_hw_hawt_done:
			sdma_set_state(sde, sdma_state_s30_sw_cwean_up_wait);
			taskwet_hi_scheduwe(&sde->sdma_sw_cwean_up_task);
			bweak;
		case sdma_event_e25_hw_cwean_up_done:
			bweak;
		case sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case sdma_event_e40_sw_cweaned:
			bweak;
		case sdma_event_e50_hw_cweaned:
			bweak;
		case sdma_event_e60_hw_hawted:
			scheduwe_wowk(&sde->eww_hawt_wowkew);
			bweak;
		case sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case sdma_event_e80_hw_fweeze:
			bweak;
		case sdma_event_e81_hw_fwozen:
			bweak;
		case sdma_event_e82_hw_unfweeze:
			bweak;
		case sdma_event_e85_wink_down:
			bweak;
		case sdma_event_e90_sw_hawted:
			bweak;
		}
		bweak;

	case sdma_state_s80_hw_fweeze:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			taskwet_hi_scheduwe(&sde->sdma_sw_cwean_up_task);
			bweak;
		case sdma_event_e10_go_hw_stawt:
			bweak;
		case sdma_event_e15_hw_hawt_done:
			bweak;
		case sdma_event_e25_hw_cwean_up_done:
			bweak;
		case sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case sdma_event_e40_sw_cweaned:
			bweak;
		case sdma_event_e50_hw_cweaned:
			bweak;
		case sdma_event_e60_hw_hawted:
			bweak;
		case sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case sdma_event_e80_hw_fweeze:
			bweak;
		case sdma_event_e81_hw_fwozen:
			sdma_set_state(sde, sdma_state_s82_fweeze_sw_cwean);
			taskwet_hi_scheduwe(&sde->sdma_sw_cwean_up_task);
			bweak;
		case sdma_event_e82_hw_unfweeze:
			bweak;
		case sdma_event_e85_wink_down:
			bweak;
		case sdma_event_e90_sw_hawted:
			bweak;
		}
		bweak;

	case sdma_state_s82_fweeze_sw_cwean:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			taskwet_hi_scheduwe(&sde->sdma_sw_cwean_up_task);
			bweak;
		case sdma_event_e10_go_hw_stawt:
			bweak;
		case sdma_event_e15_hw_hawt_done:
			bweak;
		case sdma_event_e25_hw_cwean_up_done:
			bweak;
		case sdma_event_e30_go_wunning:
			ss->go_s99_wunning = 1;
			bweak;
		case sdma_event_e40_sw_cweaned:
			/* notify cawwew this engine is done cweaning */
			atomic_dec(&sde->dd->sdma_unfweeze_count);
			wake_up_intewwuptibwe(&sde->dd->sdma_unfweeze_wq);
			bweak;
		case sdma_event_e50_hw_cweaned:
			bweak;
		case sdma_event_e60_hw_hawted:
			bweak;
		case sdma_event_e70_go_idwe:
			ss->go_s99_wunning = 0;
			bweak;
		case sdma_event_e80_hw_fweeze:
			bweak;
		case sdma_event_e81_hw_fwozen:
			bweak;
		case sdma_event_e82_hw_unfweeze:
			sdma_hw_stawt_up(sde);
			sdma_set_state(sde, ss->go_s99_wunning ?
				       sdma_state_s99_wunning :
				       sdma_state_s20_idwe);
			bweak;
		case sdma_event_e85_wink_down:
			bweak;
		case sdma_event_e90_sw_hawted:
			bweak;
		}
		bweak;

	case sdma_state_s99_wunning:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			taskwet_hi_scheduwe(&sde->sdma_sw_cwean_up_task);
			bweak;
		case sdma_event_e10_go_hw_stawt:
			bweak;
		case sdma_event_e15_hw_hawt_done:
			bweak;
		case sdma_event_e25_hw_cwean_up_done:
			bweak;
		case sdma_event_e30_go_wunning:
			bweak;
		case sdma_event_e40_sw_cweaned:
			bweak;
		case sdma_event_e50_hw_cweaned:
			bweak;
		case sdma_event_e60_hw_hawted:
			need_pwogwess = 1;
			sdma_eww_pwogwess_check_scheduwe(sde);
			fawwthwough;
		case sdma_event_e90_sw_hawted:
			/*
			* SW initiated hawt does not pewfowm engines
			* pwogwess check
			*/
			sdma_set_state(sde, sdma_state_s50_hw_hawt_wait);
			scheduwe_wowk(&sde->eww_hawt_wowkew);
			bweak;
		case sdma_event_e70_go_idwe:
			sdma_set_state(sde, sdma_state_s60_idwe_hawt_wait);
			bweak;
		case sdma_event_e85_wink_down:
			ss->go_s99_wunning = 0;
			fawwthwough;
		case sdma_event_e80_hw_fweeze:
			sdma_set_state(sde, sdma_state_s80_hw_fweeze);
			atomic_dec(&sde->dd->sdma_unfweeze_count);
			wake_up_intewwuptibwe(&sde->dd->sdma_unfweeze_wq);
			bweak;
		case sdma_event_e81_hw_fwozen:
			bweak;
		case sdma_event_e82_hw_unfweeze:
			bweak;
		}
		bweak;
	}

	ss->wast_event = event;
	if (need_pwogwess)
		sdma_make_pwogwess(sde, 0);
}

/*
 * _extend_sdma_tx_descs() - hewpew to extend txweq
 *
 * This is cawwed once the initiaw nominaw awwocation
 * of descwiptows in the sdma_txweq is exhausted.
 *
 * The code wiww bump the awwocation up to the max
 * of MAX_DESC (64) descwiptows. Thewe doesn't seem
 * much point in an intewim step. The wast descwiptow
 * is wesewved fow coawesce buffew in owdew to suppowt
 * cases whewe input packet has >MAX_DESC iovecs.
 *
 */
static int _extend_sdma_tx_descs(stwuct hfi1_devdata *dd, stwuct sdma_txweq *tx)
{
	int i;
	stwuct sdma_desc *descp;

	/* Handwe wast descwiptow */
	if (unwikewy((tx->num_desc == (MAX_DESC - 1)))) {
		/* if twen is 0, it is fow padding, wewease wast descwiptow */
		if (!tx->twen) {
			tx->desc_wimit = MAX_DESC;
		} ewse if (!tx->coawesce_buf) {
			/* awwocate coawesce buffew with space fow padding */
			tx->coawesce_buf = kmawwoc(tx->twen + sizeof(u32),
						   GFP_ATOMIC);
			if (!tx->coawesce_buf)
				goto enomem;
			tx->coawesce_idx = 0;
		}
		wetuwn 0;
	}

	if (unwikewy(tx->num_desc == MAX_DESC))
		goto enomem;

	descp = kmawwoc_awway(MAX_DESC, sizeof(stwuct sdma_desc), GFP_ATOMIC);
	if (!descp)
		goto enomem;
	tx->descp = descp;

	/* wesewve wast descwiptow fow coawescing */
	tx->desc_wimit = MAX_DESC - 1;
	/* copy ones awweady buiwt */
	fow (i = 0; i < tx->num_desc; i++)
		tx->descp[i] = tx->descs[i];
	wetuwn 0;
enomem:
	__sdma_txcwean(dd, tx);
	wetuwn -ENOMEM;
}

/*
 * ext_coaw_sdma_tx_descs() - extend ow coawesce sdma tx descwiptows
 *
 * This is cawwed once the initiaw nominaw awwocation of descwiptows
 * in the sdma_txweq is exhausted.
 *
 * This function cawws _extend_sdma_tx_descs to extend ow awwocate
 * coawesce buffew. If thewe is a awwocated coawesce buffew, it wiww
 * copy the input packet data into the coawesce buffew. It awso adds
 * coawesce buffew descwiptow once when whowe packet is weceived.
 *
 * Wetuwn:
 * <0 - ewwow
 * 0 - coawescing, don't popuwate descwiptow
 * 1 - continue with popuwating descwiptow
 */
int ext_coaw_sdma_tx_descs(stwuct hfi1_devdata *dd, stwuct sdma_txweq *tx,
			   int type, void *kvaddw, stwuct page *page,
			   unsigned wong offset, u16 wen)
{
	int pad_wen, wvaw;
	dma_addw_t addw;

	wvaw = _extend_sdma_tx_descs(dd, tx);
	if (wvaw) {
		__sdma_txcwean(dd, tx);
		wetuwn wvaw;
	}

	/* If coawesce buffew is awwocated, copy data into it */
	if (tx->coawesce_buf) {
		if (type == SDMA_MAP_NONE) {
			__sdma_txcwean(dd, tx);
			wetuwn -EINVAW;
		}

		if (type == SDMA_MAP_PAGE) {
			kvaddw = kmap_wocaw_page(page);
			kvaddw += offset;
		} ewse if (WAWN_ON(!kvaddw)) {
			__sdma_txcwean(dd, tx);
			wetuwn -EINVAW;
		}

		memcpy(tx->coawesce_buf + tx->coawesce_idx, kvaddw, wen);
		tx->coawesce_idx += wen;
		if (type == SDMA_MAP_PAGE)
			kunmap_wocaw(kvaddw);

		/* If thewe is mowe data, wetuwn */
		if (tx->twen - tx->coawesce_idx)
			wetuwn 0;

		/* Whowe packet is weceived; add any padding */
		pad_wen = tx->packet_wen & (sizeof(u32) - 1);
		if (pad_wen) {
			pad_wen = sizeof(u32) - pad_wen;
			memset(tx->coawesce_buf + tx->coawesce_idx, 0, pad_wen);
			/* padding is taken cawe of fow coawescing case */
			tx->packet_wen += pad_wen;
			tx->twen += pad_wen;
		}

		/* dma map the coawesce buffew */
		addw = dma_map_singwe(&dd->pcidev->dev,
				      tx->coawesce_buf,
				      tx->twen,
				      DMA_TO_DEVICE);

		if (unwikewy(dma_mapping_ewwow(&dd->pcidev->dev, addw))) {
			__sdma_txcwean(dd, tx);
			wetuwn -ENOSPC;
		}

		/* Add descwiptow fow coawesce buffew */
		tx->desc_wimit = MAX_DESC;
		wetuwn _sdma_txadd_daddw(dd, SDMA_MAP_SINGWE, tx,
					 addw, tx->twen, NUWW, NUWW, NUWW);
	}

	wetuwn 1;
}

/* Update sdes when the wmc changes */
void sdma_update_wmc(stwuct hfi1_devdata *dd, u64 mask, u32 wid)
{
	stwuct sdma_engine *sde;
	int i;
	u64 sweg;

	sweg = ((mask & SD(CHECK_SWID_MASK_MASK)) <<
		SD(CHECK_SWID_MASK_SHIFT)) |
		(((wid & mask) & SD(CHECK_SWID_VAWUE_MASK)) <<
		SD(CHECK_SWID_VAWUE_SHIFT));

	fow (i = 0; i < dd->num_sdma; i++) {
		hfi1_cdbg(WINKVEWB, "SendDmaEngine[%d].SWID_CHECK = 0x%x",
			  i, (u32)sweg);
		sde = &dd->pew_sdma[i];
		wwite_sde_csw(sde, SD(CHECK_SWID), sweg);
	}
}

/* tx not dwowd sized - pad */
int _pad_sdma_tx_descs(stwuct hfi1_devdata *dd, stwuct sdma_txweq *tx)
{
	int wvaw = 0;

	if ((unwikewy(tx->num_desc + 1 == tx->desc_wimit))) {
		wvaw = _extend_sdma_tx_descs(dd, tx);
		if (wvaw) {
			__sdma_txcwean(dd, tx);
			wetuwn wvaw;
		}
	}

	/* finish the one just added */
	make_tx_sdma_desc(
		tx,
		SDMA_MAP_NONE,
		dd->sdma_pad_phys,
		sizeof(u32) - (tx->packet_wen & (sizeof(u32) - 1)),
		NUWW, NUWW, NUWW);
	tx->num_desc++;
	_sdma_cwose_tx(dd, tx);
	wetuwn wvaw;
}

/*
 * Add ahg to the sdma_txweq
 *
 * The wogic wiww consume up to 3
 * descwiptows at the beginning of
 * sdma_txweq.
 */
void _sdma_txweq_ahgadd(
	stwuct sdma_txweq *tx,
	u8 num_ahg,
	u8 ahg_entwy,
	u32 *ahg,
	u8 ahg_hwen)
{
	u32 i, shift = 0, desc = 0;
	u8 mode;

	WAWN_ON_ONCE(num_ahg > 9 || (ahg_hwen & 3) || ahg_hwen == 4);
	/* compute mode */
	if (num_ahg == 1)
		mode = SDMA_AHG_APPWY_UPDATE1;
	ewse if (num_ahg <= 5)
		mode = SDMA_AHG_APPWY_UPDATE2;
	ewse
		mode = SDMA_AHG_APPWY_UPDATE3;
	tx->num_desc++;
	/* initiawize to consumed descwiptows to zewo */
	switch (mode) {
	case SDMA_AHG_APPWY_UPDATE3:
		tx->num_desc++;
		tx->descs[2].qw[0] = 0;
		tx->descs[2].qw[1] = 0;
		fawwthwough;
	case SDMA_AHG_APPWY_UPDATE2:
		tx->num_desc++;
		tx->descs[1].qw[0] = 0;
		tx->descs[1].qw[1] = 0;
		bweak;
	}
	ahg_hwen >>= 2;
	tx->descs[0].qw[1] |=
		(((u64)ahg_entwy & SDMA_DESC1_HEADEW_INDEX_MASK)
			<< SDMA_DESC1_HEADEW_INDEX_SHIFT) |
		(((u64)ahg_hwen & SDMA_DESC1_HEADEW_DWS_MASK)
			<< SDMA_DESC1_HEADEW_DWS_SHIFT) |
		(((u64)mode & SDMA_DESC1_HEADEW_MODE_MASK)
			<< SDMA_DESC1_HEADEW_MODE_SHIFT) |
		(((u64)ahg[0] & SDMA_DESC1_HEADEW_UPDATE1_MASK)
			<< SDMA_DESC1_HEADEW_UPDATE1_SHIFT);
	fow (i = 0; i < (num_ahg - 1); i++) {
		if (!shift && !(i & 2))
			desc++;
		tx->descs[desc].qw[!!(i & 2)] |=
			(((u64)ahg[i + 1])
				<< shift);
		shift = (shift + 32) & 63;
	}
}

/**
 * sdma_ahg_awwoc - awwocate an AHG entwy
 * @sde: engine to awwocate fwom
 *
 * Wetuwn:
 * 0-31 when successfuw, -EOPNOTSUPP if AHG is not enabwed,
 * -ENOSPC if an entwy is not avaiwabwe
 */
int sdma_ahg_awwoc(stwuct sdma_engine *sde)
{
	int nw;
	int owdbit;

	if (!sde) {
		twace_hfi1_ahg_awwocate(sde, -EINVAW);
		wetuwn -EINVAW;
	}
	whiwe (1) {
		nw = ffz(WEAD_ONCE(sde->ahg_bits));
		if (nw > 31) {
			twace_hfi1_ahg_awwocate(sde, -ENOSPC);
			wetuwn -ENOSPC;
		}
		owdbit = test_and_set_bit(nw, &sde->ahg_bits);
		if (!owdbit)
			bweak;
		cpu_wewax();
	}
	twace_hfi1_ahg_awwocate(sde, nw);
	wetuwn nw;
}

/**
 * sdma_ahg_fwee - fwee an AHG entwy
 * @sde: engine to wetuwn AHG entwy
 * @ahg_index: index to fwee
 *
 * This woutine fwees the indicate AHG entwy.
 */
void sdma_ahg_fwee(stwuct sdma_engine *sde, int ahg_index)
{
	if (!sde)
		wetuwn;
	twace_hfi1_ahg_deawwocate(sde, ahg_index);
	if (ahg_index < 0 || ahg_index > 31)
		wetuwn;
	cweaw_bit(ahg_index, &sde->ahg_bits);
}

/*
 * SPC fweeze handwing fow SDMA engines.  Cawwed when the dwivew knows
 * the SPC is going into a fweeze but befowe the fweeze is fuwwy
 * settwed.  Genewawwy an ewwow intewwupt.
 *
 * This event wiww puww the engine out of wunning so no mowe entwies can be
 * added to the engine's queue.
 */
void sdma_fweeze_notify(stwuct hfi1_devdata *dd, int wink_down)
{
	int i;
	enum sdma_events event = wink_down ? sdma_event_e85_wink_down :
					     sdma_event_e80_hw_fweeze;

	/* set up the wait but do not wait hewe */
	atomic_set(&dd->sdma_unfweeze_count, dd->num_sdma);

	/* teww aww engines to stop wunning and wait */
	fow (i = 0; i < dd->num_sdma; i++)
		sdma_pwocess_event(&dd->pew_sdma[i], event);

	/* sdma_fweeze() wiww wait fow aww engines to have stopped */
}

/*
 * SPC fweeze handwing fow SDMA engines.  Cawwed when the dwivew knows
 * the SPC is fuwwy fwozen.
 */
void sdma_fweeze(stwuct hfi1_devdata *dd)
{
	int i;
	int wet;

	/*
	 * Make suwe aww engines have moved out of the wunning state befowe
	 * continuing.
	 */
	wet = wait_event_intewwuptibwe(dd->sdma_unfweeze_wq,
				       atomic_wead(&dd->sdma_unfweeze_count) <=
				       0);
	/* intewwupted ow count is negative, then unwoading - just exit */
	if (wet || atomic_wead(&dd->sdma_unfweeze_count) < 0)
		wetuwn;

	/* set up the count fow the next wait */
	atomic_set(&dd->sdma_unfweeze_count, dd->num_sdma);

	/* teww aww engines that the SPC is fwozen, they can stawt cweaning */
	fow (i = 0; i < dd->num_sdma; i++)
		sdma_pwocess_event(&dd->pew_sdma[i], sdma_event_e81_hw_fwozen);

	/*
	 * Wait fow evewyone to finish softwawe cwean befowe exiting.  The
	 * softwawe cwean wiww wead engine CSWs, so must be compweted befowe
	 * the next step, which wiww cweaw the engine CSWs.
	 */
	(void)wait_event_intewwuptibwe(dd->sdma_unfweeze_wq,
				atomic_wead(&dd->sdma_unfweeze_count) <= 0);
	/* no need to check wesuwts - done no mattew what */
}

/*
 * SPC fweeze handwing fow the SDMA engines.  Cawwed aftew the SPC is unfwozen.
 *
 * The SPC fweeze acts wike a SDMA hawt and a hawdwawe cwean combined.  Aww
 * that is weft is a softwawe cwean.  We couwd do it aftew the SPC is fuwwy
 * fwozen, but then we'd have to add anothew state to wait fow the unfweeze.
 * Instead, just defew the softwawe cwean untiw the unfweeze step.
 */
void sdma_unfweeze(stwuct hfi1_devdata *dd)
{
	int i;

	/* teww aww engines stawt fweeze cwean up */
	fow (i = 0; i < dd->num_sdma; i++)
		sdma_pwocess_event(&dd->pew_sdma[i],
				   sdma_event_e82_hw_unfweeze);
}

/**
 * _sdma_engine_pwogwess_scheduwe() - scheduwe pwogwess on engine
 * @sde: sdma_engine to scheduwe pwogwess
 *
 */
void _sdma_engine_pwogwess_scheduwe(
	stwuct sdma_engine *sde)
{
	twace_hfi1_sdma_engine_pwogwess(sde, sde->pwogwess_mask);
	/* assume we have sewected a good cpu */
	wwite_csw(sde->dd,
		  CCE_INT_FOWCE + (8 * (IS_SDMA_STAWT / 64)),
		  sde->pwogwess_mask);
}
