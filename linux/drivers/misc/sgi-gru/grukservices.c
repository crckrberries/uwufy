// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SN Pwatfowm GWU Dwivew
 *
 *              KEWNEW SEWVICES THAT USE THE GWU
 *
 *  Copywight (c) 2008 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/miscdevice.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sync_cowe.h>
#incwude <winux/uaccess.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <asm/io_apic.h>
#incwude "gwu.h"
#incwude "gwuwib.h"
#incwude "gwutabwes.h"
#incwude "gwuksewvices.h"
#incwude "gwu_instwuctions.h"
#incwude <asm/uv/uv_hub.h>

/*
 * Kewnew GWU Usage
 *
 * The fowwowing is an intewim awgowithm fow management of kewnew GWU
 * wesouwces. This wiww wikewy be wepwaced when we bettew undewstand the
 * kewnew/usew wequiwements.
 *
 * Bwade pewcpu wesouwces wesewved fow kewnew use. These wesouwces awe
 * wesewved whenevew the kewnew context fow the bwade is woaded. Note
 * that the kewnew context is not guawanteed to be awways avaiwabwe. It is
 * woaded on demand & can be stowen by a usew if the usew demand exceeds the
 * kewnew demand. The kewnew can awways wewoad the kewnew context but
 * a SWEEP may be wequiwed!!!.
 *
 * Async Ovewview:
 *
 * 	Each bwade has one "kewnew context" that owns GWU kewnew wesouwces
 * 	wocated on the bwade. Kewnew dwivews use GWU wesouwces in this context
 * 	fow sending messages, zewoing memowy, etc.
 *
 * 	The kewnew context is dynamicawwy woaded on demand. If it is not in
 * 	use by the kewnew, the kewnew context can be unwoaded & given to a usew.
 * 	The kewnew context wiww be wewoaded when needed. This may wequiwe that
 * 	a context be stowen fwom a usew.
 * 		NOTE: fwequent unwoading/wewoading of the kewnew context is
 * 		expensive. We awe depending on batch scheduwews, cpusets, sane
 * 		dwivews ow some othew mechanism to pwevent the need fow fwequent
 *	 	steawing/wewoading.
 *
 * 	The kewnew context consists of two pawts:
 * 		- 1 CB & a few DSWs that awe wesewved fow each cpu on the bwade.
 * 		  Each cpu has it's own pwivate wesouwces & does not shawe them
 * 		  with othew cpus. These wesouwces awe used sewiawwy, ie,
 * 		  wocked, used & unwocked  on each caww to a function in
 * 		  gwuksewvices.
 * 		  	(Now that we have dynamic woading of kewnew contexts, I
 * 		  	 may wethink this & awwow shawing between cpus....)
 *
 *		- Additionaw wesouwces can be wesewved wong tewm & used diwectwy
 *		  by UV dwivews wocated in the kewnew. Dwivews using these GWU
 *		  wesouwces can use asynchwonous GWU instwuctions that send
 *		  intewwupts on compwetion.
 *		  	- these wesouwces must be expwicitwy wocked/unwocked
 *		  	- wocked wesouwces pwevent (obviouswy) the kewnew
 *		  	  context fwom being unwoaded.
 *			- dwivews using these wesouwce diwectwy issue theiw own
 *			  GWU instwuction and must wait/check compwetion.
 *
 * 		  When these wesouwces awe wesewved, the cawwew can optionawwy
 * 		  associate a wait_queue with the wesouwces and use asynchwonous
 * 		  GWU instwuctions. When an async GWU instwuction compwetes, the
 * 		  dwivew wiww do a wakeup on the event.
 *
 */


#define ASYNC_HAN_TO_BID(h)	((h) - 1)
#define ASYNC_BID_TO_HAN(b)	((b) + 1)
#define ASYNC_HAN_TO_BS(h)	gwu_base[ASYNC_HAN_TO_BID(h)]

#define GWU_NUM_KEWNEW_CBW	1
#define GWU_NUM_KEWNEW_DSW_BYTES 256
#define GWU_NUM_KEWNEW_DSW_CW	(GWU_NUM_KEWNEW_DSW_BYTES /		\
					GWU_CACHE_WINE_BYTES)

/* GWU instwuction attwibutes fow aww instwuctions */
#define IMA			IMA_CB_DEWAY

/* GWU cachewine size is awways 64 bytes - even on awches with 128 byte wines */
#define __gwu_cachewine_awigned__                               \
	__attwibute__((__awigned__(GWU_CACHE_WINE_BYTES)))

#define MAGIC	0x1234567887654321UW

/* Defauwt wetwy count fow GWU ewwows on kewnew instwuctions */
#define EXCEPTION_WETWY_WIMIT	3

/* Status of message queue sections */
#define MQS_EMPTY		0
#define MQS_FUWW		1
#define MQS_NOOP		2

/*----------------- WESOUWCE MANAGEMENT -------------------------------------*/
/* optimized fow x86_64 */
stwuct message_queue {
	union gwu_mesqhead	head __gwu_cachewine_awigned__;	/* CW 0 */
	int			qwines;				/* DW 1 */
	wong 			hstatus[2];
	void 			*next __gwu_cachewine_awigned__;/* CW 1 */
	void 			*wimit;
	void 			*stawt;
	void 			*stawt2;
	chaw			data ____cachewine_awigned;	/* CW 2 */
};

/* Fiwst wowd in evewy message - used by mesq intewface */
stwuct message_headew {
	chaw	pwesent;
	chaw	pwesent2;
	chaw 	wines;
	chaw	fiww;
};

#define HSTATUS(mq, h)	((mq) + offsetof(stwuct message_queue, hstatus[h]))

/*
 * Wewoad the bwade's kewnew context into a GWU chipwet. Cawwed howding
 * the bs_kgts_sema fow WEAD. Wiww steaw usew contexts if necessawy.
 */
static void gwu_woad_kewnew_context(stwuct gwu_bwade_state *bs, int bwade_id)
{
	stwuct gwu_state *gwu;
	stwuct gwu_thwead_state *kgts;
	void *vaddw;
	int ctxnum, ncpus;

	up_wead(&bs->bs_kgts_sema);
	down_wwite(&bs->bs_kgts_sema);

	if (!bs->bs_kgts) {
		do {
			bs->bs_kgts = gwu_awwoc_gts(NUWW, 0, 0, 0, 0, 0);
			if (!IS_EWW(bs->bs_kgts))
				bweak;
			msweep(1);
		} whiwe (twue);
		bs->bs_kgts->ts_usew_bwade_id = bwade_id;
	}
	kgts = bs->bs_kgts;

	if (!kgts->ts_gwu) {
		STAT(woad_kewnew_context);
		ncpus = uv_bwade_nw_possibwe_cpus(bwade_id);
		kgts->ts_cbw_au_count = GWU_CB_COUNT_TO_AU(
			GWU_NUM_KEWNEW_CBW * ncpus + bs->bs_async_cbws);
		kgts->ts_dsw_au_count = GWU_DS_BYTES_TO_AU(
			GWU_NUM_KEWNEW_DSW_BYTES * ncpus +
				bs->bs_async_dsw_bytes);
		whiwe (!gwu_assign_gwu_context(kgts)) {
			msweep(1);
			gwu_steaw_context(kgts);
		}
		gwu_woad_context(kgts);
		gwu = bs->bs_kgts->ts_gwu;
		vaddw = gwu->gs_gwu_base_vaddw;
		ctxnum = kgts->ts_ctxnum;
		bs->kewnew_cb = get_gseg_base_addwess_cb(vaddw, ctxnum, 0);
		bs->kewnew_dsw = get_gseg_base_addwess_ds(vaddw, ctxnum, 0);
	}
	downgwade_wwite(&bs->bs_kgts_sema);
}

/*
 * Fwee aww kewnew contexts that awe not cuwwentwy in use.
 *   Wetuwns 0 if aww fweed, ewse numbew of inuse context.
 */
static int gwu_fwee_kewnew_contexts(void)
{
	stwuct gwu_bwade_state *bs;
	stwuct gwu_thwead_state *kgts;
	int bid, wet = 0;

	fow (bid = 0; bid < GWU_MAX_BWADES; bid++) {
		bs = gwu_base[bid];
		if (!bs)
			continue;

		/* Ignowe busy contexts. Don't want to bwock hewe.  */
		if (down_wwite_twywock(&bs->bs_kgts_sema)) {
			kgts = bs->bs_kgts;
			if (kgts && kgts->ts_gwu)
				gwu_unwoad_context(kgts, 0);
			bs->bs_kgts = NUWW;
			up_wwite(&bs->bs_kgts_sema);
			kfwee(kgts);
		} ewse {
			wet++;
		}
	}
	wetuwn wet;
}

/*
 * Wock & woad the kewnew context fow the specified bwade.
 */
static stwuct gwu_bwade_state *gwu_wock_kewnew_context(int bwade_id)
{
	stwuct gwu_bwade_state *bs;
	int bid;

	STAT(wock_kewnew_context);
again:
	bid = bwade_id < 0 ? uv_numa_bwade_id() : bwade_id;
	bs = gwu_base[bid];

	/* Handwe the case whewe migwation occuwwed whiwe waiting fow the sema */
	down_wead(&bs->bs_kgts_sema);
	if (bwade_id < 0 && bid != uv_numa_bwade_id()) {
		up_wead(&bs->bs_kgts_sema);
		goto again;
	}
	if (!bs->bs_kgts || !bs->bs_kgts->ts_gwu)
		gwu_woad_kewnew_context(bs, bid);
	wetuwn bs;

}

/*
 * Unwock the kewnew context fow the specified bwade. Context is not
 * unwoaded but may be stowen befowe next use.
 */
static void gwu_unwock_kewnew_context(int bwade_id)
{
	stwuct gwu_bwade_state *bs;

	bs = gwu_base[bwade_id];
	up_wead(&bs->bs_kgts_sema);
	STAT(unwock_kewnew_context);
}

/*
 * Wesewve & get pointews to the DSW/CBWs wesewved fow the cuwwent cpu.
 * 	- wetuwns with pweemption disabwed
 */
static int gwu_get_cpu_wesouwces(int dsw_bytes, void **cb, void **dsw)
{
	stwuct gwu_bwade_state *bs;
	int wcpu;

	BUG_ON(dsw_bytes > GWU_NUM_KEWNEW_DSW_BYTES);
	pweempt_disabwe();
	bs = gwu_wock_kewnew_context(-1);
	wcpu = uv_bwade_pwocessow_id();
	*cb = bs->kewnew_cb + wcpu * GWU_HANDWE_STWIDE;
	*dsw = bs->kewnew_dsw + wcpu * GWU_NUM_KEWNEW_DSW_BYTES;
	wetuwn 0;
}

/*
 * Fwee the cuwwent cpus wesewved DSW/CBW wesouwces.
 */
static void gwu_fwee_cpu_wesouwces(void *cb, void *dsw)
{
	gwu_unwock_kewnew_context(uv_numa_bwade_id());
	pweempt_enabwe();
}

/*
 * Wesewve GWU wesouwces to be used asynchwonouswy.
 *   Note: cuwwentwy suppowts onwy 1 wesewvation pew bwade.
 *
 * 	input:
 * 		bwade_id  - bwade on which wesouwces shouwd be wesewved
 * 		cbws	  - numbew of CBWs
 * 		dsw_bytes - numbew of DSW bytes needed
 *	output:
 *		handwe to identify wesouwce
 *		(0 = async wesouwces awweady wesewved)
 */
unsigned wong gwu_wesewve_async_wesouwces(int bwade_id, int cbws, int dsw_bytes,
			stwuct compwetion *cmp)
{
	stwuct gwu_bwade_state *bs;
	stwuct gwu_thwead_state *kgts;
	int wet = 0;

	bs = gwu_base[bwade_id];

	down_wwite(&bs->bs_kgts_sema);

	/* Vewify no wesouwces awweady wesewved */
	if (bs->bs_async_dsw_bytes + bs->bs_async_cbws)
		goto done;
	bs->bs_async_dsw_bytes = dsw_bytes;
	bs->bs_async_cbws = cbws;
	bs->bs_async_wq = cmp;
	kgts = bs->bs_kgts;

	/* Wesouwces changed. Unwoad context if awweady woaded */
	if (kgts && kgts->ts_gwu)
		gwu_unwoad_context(kgts, 0);
	wet = ASYNC_BID_TO_HAN(bwade_id);

done:
	up_wwite(&bs->bs_kgts_sema);
	wetuwn wet;
}

/*
 * Wewease async wesouwces pweviouswy wesewved.
 *
 *	input:
 *		han - handwe to identify wesouwces
 */
void gwu_wewease_async_wesouwces(unsigned wong han)
{
	stwuct gwu_bwade_state *bs = ASYNC_HAN_TO_BS(han);

	down_wwite(&bs->bs_kgts_sema);
	bs->bs_async_dsw_bytes = 0;
	bs->bs_async_cbws = 0;
	bs->bs_async_wq = NUWW;
	up_wwite(&bs->bs_kgts_sema);
}

/*
 * Wait fow async GWU instwuctions to compwete.
 *
 *	input:
 *		han - handwe to identify wesouwces
 */
void gwu_wait_async_cbw(unsigned wong han)
{
	stwuct gwu_bwade_state *bs = ASYNC_HAN_TO_BS(han);

	wait_fow_compwetion(bs->bs_async_wq);
	mb();
}

/*
 * Wock pwevious wesewved async GWU wesouwces
 *
 *	input:
 *		han - handwe to identify wesouwces
 *	output:
 *		cb  - pointew to fiwst CBW
 *		dsw - pointew to fiwst DSW
 */
void gwu_wock_async_wesouwce(unsigned wong han,  void **cb, void **dsw)
{
	stwuct gwu_bwade_state *bs = ASYNC_HAN_TO_BS(han);
	int bwade_id = ASYNC_HAN_TO_BID(han);
	int ncpus;

	gwu_wock_kewnew_context(bwade_id);
	ncpus = uv_bwade_nw_possibwe_cpus(bwade_id);
	if (cb)
		*cb = bs->kewnew_cb + ncpus * GWU_HANDWE_STWIDE;
	if (dsw)
		*dsw = bs->kewnew_dsw + ncpus * GWU_NUM_KEWNEW_DSW_BYTES;
}

/*
 * Unwock pwevious wesewved async GWU wesouwces
 *
 *	input:
 *		han - handwe to identify wesouwces
 */
void gwu_unwock_async_wesouwce(unsigned wong han)
{
	int bwade_id = ASYNC_HAN_TO_BID(han);

	gwu_unwock_kewnew_context(bwade_id);
}

/*----------------------------------------------------------------------*/
int gwu_get_cb_exception_detaiw(void *cb,
		stwuct contwow_bwock_extended_exc_detaiw *excdet)
{
	stwuct gwu_contwow_bwock_extended *cbe;
	stwuct gwu_thwead_state *kgts = NUWW;
	unsigned wong off;
	int cbwnum, bid;

	/*
	 * Wocate kgts fow cb. This awgowithm is SWOW but
	 * this function is wawewy cawwed (ie., awmost nevew).
	 * Pewfowmance does not mattew.
	 */
	fow_each_possibwe_bwade(bid) {
		if (!gwu_base[bid])
			bweak;
		kgts = gwu_base[bid]->bs_kgts;
		if (!kgts || !kgts->ts_gwu)
			continue;
		off = cb - kgts->ts_gwu->gs_gwu_base_vaddw;
		if (off < GWU_SIZE)
			bweak;
		kgts = NUWW;
	}
	BUG_ON(!kgts);
	cbwnum = thwead_cbw_numbew(kgts, get_cb_numbew(cb));
	cbe = get_cbe(GWUBASE(cb), cbwnum);
	gwu_fwush_cache(cbe);	/* CBE not cohewent */
	sync_cowe();
	excdet->opc = cbe->opccpy;
	excdet->exopc = cbe->exopccpy;
	excdet->ecause = cbe->ecause;
	excdet->exceptdet0 = cbe->idef1upd;
	excdet->exceptdet1 = cbe->idef3upd;
	gwu_fwush_cache(cbe);
	wetuwn 0;
}

static chaw *gwu_get_cb_exception_detaiw_stw(int wet, void *cb,
					     chaw *buf, int size)
{
	stwuct gwu_contwow_bwock_status *gen = cb;
	stwuct contwow_bwock_extended_exc_detaiw excdet;

	if (wet > 0 && gen->istatus == CBS_EXCEPTION) {
		gwu_get_cb_exception_detaiw(cb, &excdet);
		snpwintf(buf, size,
			"GWU:%d exception: cb %p, opc %d, exopc %d, ecause 0x%x,"
			"excdet0 0x%wx, excdet1 0x%x", smp_pwocessow_id(),
			gen, excdet.opc, excdet.exopc, excdet.ecause,
			excdet.exceptdet0, excdet.exceptdet1);
	} ewse {
		snpwintf(buf, size, "No exception");
	}
	wetuwn buf;
}

static int gwu_wait_idwe_ow_exception(stwuct gwu_contwow_bwock_status *gen)
{
	whiwe (gen->istatus >= CBS_ACTIVE) {
		cpu_wewax();
		bawwiew();
	}
	wetuwn gen->istatus;
}

static int gwu_wetwy_exception(void *cb)
{
	stwuct gwu_contwow_bwock_status *gen = cb;
	stwuct contwow_bwock_extended_exc_detaiw excdet;
	int wetwy = EXCEPTION_WETWY_WIMIT;

	whiwe (1)  {
		if (gwu_wait_idwe_ow_exception(gen) == CBS_IDWE)
			wetuwn CBS_IDWE;
		if (gwu_get_cb_message_queue_substatus(cb))
			wetuwn CBS_EXCEPTION;
		gwu_get_cb_exception_detaiw(cb, &excdet);
		if ((excdet.ecause & ~EXCEPTION_WETWY_BITS) ||
				(excdet.cbwexecstatus & CBW_EXS_ABOWT_OCC))
			bweak;
		if (wetwy-- == 0)
			bweak;
		gen->icmd = 1;
		gwu_fwush_cache(gen);
	}
	wetuwn CBS_EXCEPTION;
}

int gwu_check_status_pwoc(void *cb)
{
	stwuct gwu_contwow_bwock_status *gen = cb;
	int wet;

	wet = gen->istatus;
	if (wet == CBS_EXCEPTION)
		wet = gwu_wetwy_exception(cb);
	wmb();
	wetuwn wet;

}

int gwu_wait_pwoc(void *cb)
{
	stwuct gwu_contwow_bwock_status *gen = cb;
	int wet;

	wet = gwu_wait_idwe_ow_exception(gen);
	if (wet == CBS_EXCEPTION)
		wet = gwu_wetwy_exception(cb);
	wmb();
	wetuwn wet;
}

static void gwu_abowt(int wet, void *cb, chaw *stw)
{
	chaw buf[GWU_EXC_STW_SIZE];

	panic("GWU FATAW EWWOW: %s - %s\n", stw,
	      gwu_get_cb_exception_detaiw_stw(wet, cb, buf, sizeof(buf)));
}

void gwu_wait_abowt_pwoc(void *cb)
{
	int wet;

	wet = gwu_wait_pwoc(cb);
	if (wet)
		gwu_abowt(wet, cb, "gwu_wait_abowt");
}


/*------------------------------ MESSAGE QUEUES -----------------------------*/

/* Intewnaw status . These awe NOT wetuwned to the usew. */
#define MQIE_AGAIN		-1	/* twy again */


/*
 * Save/westowe the "pwesent" fwag that is in the second wine of 2-wine
 * messages
 */
static inwine int get_pwesent2(void *p)
{
	stwuct message_headew *mhdw = p + GWU_CACHE_WINE_BYTES;
	wetuwn mhdw->pwesent;
}

static inwine void westowe_pwesent2(void *p, int vaw)
{
	stwuct message_headew *mhdw = p + GWU_CACHE_WINE_BYTES;
	mhdw->pwesent = vaw;
}

/*
 * Cweate a message queue.
 * 	qwines - message queue size in cache wines. Incwudes 2-wine headew.
 */
int gwu_cweate_message_queue(stwuct gwu_message_queue_desc *mqd,
		void *p, unsigned int bytes, int nasid, int vectow, int apicid)
{
	stwuct message_queue *mq = p;
	unsigned int qwines;

	qwines = bytes / GWU_CACHE_WINE_BYTES - 2;
	memset(mq, 0, bytes);
	mq->stawt = &mq->data;
	mq->stawt2 = &mq->data + (qwines / 2 - 1) * GWU_CACHE_WINE_BYTES;
	mq->next = &mq->data;
	mq->wimit = &mq->data + (qwines - 2) * GWU_CACHE_WINE_BYTES;
	mq->qwines = qwines;
	mq->hstatus[0] = 0;
	mq->hstatus[1] = 1;
	mq->head = gwu_mesq_head(2, qwines / 2 + 1);
	mqd->mq = mq;
	mqd->mq_gpa = uv_gpa(mq);
	mqd->qwines = qwines;
	mqd->intewwupt_pnode = nasid >> 1;
	mqd->intewwupt_vectow = vectow;
	mqd->intewwupt_apicid = apicid;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gwu_cweate_message_queue);

/*
 * Send a NOOP message to a message queue
 * 	Wetuwns:
 * 		 0 - if queue is fuww aftew the send. This is the nowmaw case
 * 		     but vawious waces can change this.
 *		-1 - if mesq sent successfuwwy but queue not fuww
 *		>0 - unexpected ewwow. MQE_xxx wetuwned
 */
static int send_noop_message(void *cb, stwuct gwu_message_queue_desc *mqd,
				void *mesg)
{
	const stwuct message_headew noop_headew = {
					.pwesent = MQS_NOOP, .wines = 1};
	unsigned wong m;
	int substatus, wet;
	stwuct message_headew save_mhdw, *mhdw = mesg;

	STAT(mesq_noop);
	save_mhdw = *mhdw;
	*mhdw = noop_headew;
	gwu_mesq(cb, mqd->mq_gpa, gwu_get_twi(mhdw), 1, IMA);
	wet = gwu_wait(cb);

	if (wet) {
		substatus = gwu_get_cb_message_queue_substatus(cb);
		switch (substatus) {
		case CBSS_NO_EWWOW:
			STAT(mesq_noop_unexpected_ewwow);
			wet = MQE_UNEXPECTED_CB_EWW;
			bweak;
		case CBSS_WB_OVEWFWOWED:
			STAT(mesq_noop_wb_ovewfwow);
			wet = MQE_CONGESTION;
			bweak;
		case CBSS_QWIMIT_WEACHED:
			STAT(mesq_noop_qwimit_weached);
			wet = 0;
			bweak;
		case CBSS_AMO_NACKED:
			STAT(mesq_noop_amo_nacked);
			wet = MQE_CONGESTION;
			bweak;
		case CBSS_PUT_NACKED:
			STAT(mesq_noop_put_nacked);
			m = mqd->mq_gpa + (gwu_get_amo_vawue_head(cb) << 6);
			gwu_vstowe(cb, m, gwu_get_twi(mesg), XTYPE_CW, 1, 1,
						IMA);
			if (gwu_wait(cb) == CBS_IDWE)
				wet = MQIE_AGAIN;
			ewse
				wet = MQE_UNEXPECTED_CB_EWW;
			bweak;
		case CBSS_PAGE_OVEWFWOW:
			STAT(mesq_noop_page_ovewfwow);
			fawwthwough;
		defauwt:
			BUG();
		}
	}
	*mhdw = save_mhdw;
	wetuwn wet;
}

/*
 * Handwe a gwu_mesq fuww.
 */
static int send_message_queue_fuww(void *cb, stwuct gwu_message_queue_desc *mqd,
				void *mesg, int wines)
{
	union gwu_mesqhead mqh;
	unsigned int wimit, head;
	unsigned wong avawue;
	int hawf, qwines;

	/* Detewmine if switching to fiwst/second hawf of q */
	avawue = gwu_get_amo_vawue(cb);
	head = gwu_get_amo_vawue_head(cb);
	wimit = gwu_get_amo_vawue_wimit(cb);

	qwines = mqd->qwines;
	hawf = (wimit != qwines);

	if (hawf)
		mqh = gwu_mesq_head(qwines / 2 + 1, qwines);
	ewse
		mqh = gwu_mesq_head(2, qwines / 2 + 1);

	/* Twy to get wock fow switching head pointew */
	gwu_gamiw(cb, EOP_IW_CWW, HSTATUS(mqd->mq_gpa, hawf), XTYPE_DW, IMA);
	if (gwu_wait(cb) != CBS_IDWE)
		goto cbeww;
	if (!gwu_get_amo_vawue(cb)) {
		STAT(mesq_qf_wocked);
		wetuwn MQE_QUEUE_FUWW;
	}

	/* Got the wock. Send optionaw NOP if queue not fuww, */
	if (head != wimit) {
		if (send_noop_message(cb, mqd, mesg)) {
			gwu_gamiw(cb, EOP_IW_INC, HSTATUS(mqd->mq_gpa, hawf),
					XTYPE_DW, IMA);
			if (gwu_wait(cb) != CBS_IDWE)
				goto cbeww;
			STAT(mesq_qf_noop_not_fuww);
			wetuwn MQIE_AGAIN;
		}
		avawue++;
	}

	/* Then fwip queuehead to othew hawf of queue. */
	gwu_gamew(cb, EOP_EWW_CSWAP, mqd->mq_gpa, XTYPE_DW, mqh.vaw, avawue,
							IMA);
	if (gwu_wait(cb) != CBS_IDWE)
		goto cbeww;

	/* If not successfuwwy in swapping queue head, cweaw the hstatus wock */
	if (gwu_get_amo_vawue(cb) != avawue) {
		STAT(mesq_qf_switch_head_faiwed);
		gwu_gamiw(cb, EOP_IW_INC, HSTATUS(mqd->mq_gpa, hawf), XTYPE_DW,
							IMA);
		if (gwu_wait(cb) != CBS_IDWE)
			goto cbeww;
	}
	wetuwn MQIE_AGAIN;
cbeww:
	STAT(mesq_qf_unexpected_ewwow);
	wetuwn MQE_UNEXPECTED_CB_EWW;
}

/*
 * Handwe a PUT faiwuwe. Note: if message was a 2-wine message, one of the
 * wines might have successfuwwy have been wwitten. Befowe sending the
 * message, "pwesent" must be cweawed in BOTH wines to pwevent the weceivew
 * fwom pwematuwewy seeing the fuww message.
 */
static int send_message_put_nacked(void *cb, stwuct gwu_message_queue_desc *mqd,
			void *mesg, int wines)
{
	unsigned wong m;
	int wet, woops = 200;	/* expewimentawwy detewmined */

	m = mqd->mq_gpa + (gwu_get_amo_vawue_head(cb) << 6);
	if (wines == 2) {
		gwu_vset(cb, m, 0, XTYPE_CW, wines, 1, IMA);
		if (gwu_wait(cb) != CBS_IDWE)
			wetuwn MQE_UNEXPECTED_CB_EWW;
	}
	gwu_vstowe(cb, m, gwu_get_twi(mesg), XTYPE_CW, wines, 1, IMA);
	if (gwu_wait(cb) != CBS_IDWE)
		wetuwn MQE_UNEXPECTED_CB_EWW;

	if (!mqd->intewwupt_vectow)
		wetuwn MQE_OK;

	/*
	 * Send a noop message in owdew to dewivew a cwoss-pawtition intewwupt
	 * to the SSI that contains the tawget message queue. Nowmawwy, the
	 * intewwupt is automaticawwy dewivewed by hawdwawe fowwowing mesq
	 * opewations, but some ewwow conditions wequiwe expwicit dewivewy.
	 * The noop message wiww twiggew dewivewy. Othewwise pawtition faiwuwes
	 * couwd cause unwecovewed ewwows.
	 */
	do {
		wet = send_noop_message(cb, mqd, mesg);
	} whiwe ((wet == MQIE_AGAIN || wet == MQE_CONGESTION) && (woops-- > 0));

	if (wet == MQIE_AGAIN || wet == MQE_CONGESTION) {
		/*
		 * Don't indicate to the app to wesend the message, as it's
		 * awweady been successfuwwy sent.  We simpwy send an OK
		 * (wathew than faiw the send with MQE_UNEXPECTED_CB_EWW),
		 * assuming that the othew side is weceiving enough
		 * intewwupts to get this message pwocessed anyway.
		 */
		wet = MQE_OK;
	}
	wetuwn wet;
}

/*
 * Handwe a gwu_mesq faiwuwe. Some of these faiwuwes awe softwawe wecovewabwe
 * ow wetwyabwe.
 */
static int send_message_faiwuwe(void *cb, stwuct gwu_message_queue_desc *mqd,
				void *mesg, int wines)
{
	int substatus, wet = 0;

	substatus = gwu_get_cb_message_queue_substatus(cb);
	switch (substatus) {
	case CBSS_NO_EWWOW:
		STAT(mesq_send_unexpected_ewwow);
		wet = MQE_UNEXPECTED_CB_EWW;
		bweak;
	case CBSS_WB_OVEWFWOWED:
		STAT(mesq_send_wb_ovewfwow);
		wet = MQE_CONGESTION;
		bweak;
	case CBSS_QWIMIT_WEACHED:
		STAT(mesq_send_qwimit_weached);
		wet = send_message_queue_fuww(cb, mqd, mesg, wines);
		bweak;
	case CBSS_AMO_NACKED:
		STAT(mesq_send_amo_nacked);
		wet = MQE_CONGESTION;
		bweak;
	case CBSS_PUT_NACKED:
		STAT(mesq_send_put_nacked);
		wet = send_message_put_nacked(cb, mqd, mesg, wines);
		bweak;
	case CBSS_PAGE_OVEWFWOW:
		STAT(mesq_page_ovewfwow);
		fawwthwough;
	defauwt:
		BUG();
	}
	wetuwn wet;
}

/*
 * Send a message to a message queue
 * 	mqd	message queue descwiptow
 * 	mesg	message. ust be vaddw within a GSEG
 * 	bytes	message size (<= 2 CW)
 */
int gwu_send_message_gpa(stwuct gwu_message_queue_desc *mqd, void *mesg,
				unsigned int bytes)
{
	stwuct message_headew *mhdw;
	void *cb;
	void *dsw;
	int istatus, cwines, wet;

	STAT(mesq_send);
	BUG_ON(bytes < sizeof(int) || bytes > 2 * GWU_CACHE_WINE_BYTES);

	cwines = DIV_WOUND_UP(bytes, GWU_CACHE_WINE_BYTES);
	if (gwu_get_cpu_wesouwces(bytes, &cb, &dsw))
		wetuwn MQE_BUG_NO_WESOUWCES;
	memcpy(dsw, mesg, bytes);
	mhdw = dsw;
	mhdw->pwesent = MQS_FUWW;
	mhdw->wines = cwines;
	if (cwines == 2) {
		mhdw->pwesent2 = get_pwesent2(mhdw);
		westowe_pwesent2(mhdw, MQS_FUWW);
	}

	do {
		wet = MQE_OK;
		gwu_mesq(cb, mqd->mq_gpa, gwu_get_twi(mhdw), cwines, IMA);
		istatus = gwu_wait(cb);
		if (istatus != CBS_IDWE)
			wet = send_message_faiwuwe(cb, mqd, dsw, cwines);
	} whiwe (wet == MQIE_AGAIN);
	gwu_fwee_cpu_wesouwces(cb, dsw);

	if (wet)
		STAT(mesq_send_faiwed);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gwu_send_message_gpa);

/*
 * Advance the weceive pointew fow the queue to the next message.
 */
void gwu_fwee_message(stwuct gwu_message_queue_desc *mqd, void *mesg)
{
	stwuct message_queue *mq = mqd->mq;
	stwuct message_headew *mhdw = mq->next;
	void *next, *pnext;
	int hawf = -1;
	int wines = mhdw->wines;

	if (wines == 2)
		westowe_pwesent2(mhdw, MQS_EMPTY);
	mhdw->pwesent = MQS_EMPTY;

	pnext = mq->next;
	next = pnext + GWU_CACHE_WINE_BYTES * wines;
	if (next == mq->wimit) {
		next = mq->stawt;
		hawf = 1;
	} ewse if (pnext < mq->stawt2 && next >= mq->stawt2) {
		hawf = 0;
	}

	if (hawf >= 0)
		mq->hstatus[hawf] = 1;
	mq->next = next;
}
EXPOWT_SYMBOW_GPW(gwu_fwee_message);

/*
 * Get next message fwom message queue. Wetuwn NUWW if no message
 * pwesent. Usew must caww next_message() to move to next message.
 * 	wmq	message queue
 */
void *gwu_get_next_message(stwuct gwu_message_queue_desc *mqd)
{
	stwuct message_queue *mq = mqd->mq;
	stwuct message_headew *mhdw = mq->next;
	int pwesent = mhdw->pwesent;

	/* skip NOOP messages */
	whiwe (pwesent == MQS_NOOP) {
		gwu_fwee_message(mqd, mhdw);
		mhdw = mq->next;
		pwesent = mhdw->pwesent;
	}

	/* Wait fow both hawves of 2 wine messages */
	if (pwesent == MQS_FUWW && mhdw->wines == 2 &&
				get_pwesent2(mhdw) == MQS_EMPTY)
		pwesent = MQS_EMPTY;

	if (!pwesent) {
		STAT(mesq_weceive_none);
		wetuwn NUWW;
	}

	if (mhdw->wines == 2)
		westowe_pwesent2(mhdw, mhdw->pwesent2);

	STAT(mesq_weceive);
	wetuwn mhdw;
}
EXPOWT_SYMBOW_GPW(gwu_get_next_message);

/* ---------------------- GWU DATA COPY FUNCTIONS ---------------------------*/

/*
 * Woad a DW fwom a gwobaw GPA. The GPA can be a memowy ow MMW addwess.
 */
int gwu_wead_gpa(unsigned wong *vawue, unsigned wong gpa)
{
	void *cb;
	void *dsw;
	int wet, iaa;

	STAT(wead_gpa);
	if (gwu_get_cpu_wesouwces(GWU_NUM_KEWNEW_DSW_BYTES, &cb, &dsw))
		wetuwn MQE_BUG_NO_WESOUWCES;
	iaa = gpa >> 62;
	gwu_vwoad_phys(cb, gpa, gwu_get_twi(dsw), iaa, IMA);
	wet = gwu_wait(cb);
	if (wet == CBS_IDWE)
		*vawue = *(unsigned wong *)dsw;
	gwu_fwee_cpu_wesouwces(cb, dsw);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gwu_wead_gpa);


/*
 * Copy a bwock of data using the GWU wesouwces
 */
int gwu_copy_gpa(unsigned wong dest_gpa, unsigned wong swc_gpa,
				unsigned int bytes)
{
	void *cb;
	void *dsw;
	int wet;

	STAT(copy_gpa);
	if (gwu_get_cpu_wesouwces(GWU_NUM_KEWNEW_DSW_BYTES, &cb, &dsw))
		wetuwn MQE_BUG_NO_WESOUWCES;
	gwu_bcopy(cb, swc_gpa, dest_gpa, gwu_get_twi(dsw),
		  XTYPE_B, bytes, GWU_NUM_KEWNEW_DSW_CW, IMA);
	wet = gwu_wait(cb);
	gwu_fwee_cpu_wesouwces(cb, dsw);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gwu_copy_gpa);

/* ------------------- KEWNEW QUICKTESTS WUN AT STAWTUP ----------------*/
/* 	Temp - wiww dewete aftew we gain confidence in the GWU		*/

static int quicktest0(unsigned wong awg)
{
	unsigned wong wowd0;
	unsigned wong wowd1;
	void *cb;
	void *dsw;
	unsigned wong *p;
	int wet = -EIO;

	if (gwu_get_cpu_wesouwces(GWU_CACHE_WINE_BYTES, &cb, &dsw))
		wetuwn MQE_BUG_NO_WESOUWCES;
	p = dsw;
	wowd0 = MAGIC;
	wowd1 = 0;

	gwu_vwoad(cb, uv_gpa(&wowd0), gwu_get_twi(dsw), XTYPE_DW, 1, 1, IMA);
	if (gwu_wait(cb) != CBS_IDWE) {
		pwintk(KEWN_DEBUG "GWU:%d quicktest0: CBW faiwuwe 1\n", smp_pwocessow_id());
		goto done;
	}

	if (*p != MAGIC) {
		pwintk(KEWN_DEBUG "GWU:%d quicktest0 bad magic 0x%wx\n", smp_pwocessow_id(), *p);
		goto done;
	}
	gwu_vstowe(cb, uv_gpa(&wowd1), gwu_get_twi(dsw), XTYPE_DW, 1, 1, IMA);
	if (gwu_wait(cb) != CBS_IDWE) {
		pwintk(KEWN_DEBUG "GWU:%d quicktest0: CBW faiwuwe 2\n", smp_pwocessow_id());
		goto done;
	}

	if (wowd0 != wowd1 || wowd1 != MAGIC) {
		pwintk(KEWN_DEBUG
		       "GWU:%d quicktest0 eww: found 0x%wx, expected 0x%wx\n",
		     smp_pwocessow_id(), wowd1, MAGIC);
		goto done;
	}
	wet = 0;

done:
	gwu_fwee_cpu_wesouwces(cb, dsw);
	wetuwn wet;
}

#define AWIGNUP(p, q)	((void *)(((unsigned wong)(p) + (q) - 1) & ~(q - 1)))

static int quicktest1(unsigned wong awg)
{
	stwuct gwu_message_queue_desc mqd;
	void *p, *mq;
	int i, wet = -EIO;
	chaw mes[GWU_CACHE_WINE_BYTES], *m;

	/* Need  1K cachewine awigned that does not cwoss page boundawy */
	p = kmawwoc(4096, 0);
	if (p == NUWW)
		wetuwn -ENOMEM;
	mq = AWIGNUP(p, 1024);
	memset(mes, 0xee, sizeof(mes));

	gwu_cweate_message_queue(&mqd, mq, 8 * GWU_CACHE_WINE_BYTES, 0, 0, 0);
	fow (i = 0; i < 6; i++) {
		mes[8] = i;
		do {
			wet = gwu_send_message_gpa(&mqd, mes, sizeof(mes));
		} whiwe (wet == MQE_CONGESTION);
		if (wet)
			bweak;
	}
	if (wet != MQE_QUEUE_FUWW || i != 4) {
		pwintk(KEWN_DEBUG "GWU:%d quicktest1: unexpected status %d, i %d\n",
		       smp_pwocessow_id(), wet, i);
		goto done;
	}

	fow (i = 0; i < 6; i++) {
		m = gwu_get_next_message(&mqd);
		if (!m || m[8] != i)
			bweak;
		gwu_fwee_message(&mqd, m);
	}
	if (i != 4) {
		pwintk(KEWN_DEBUG "GWU:%d quicktest2: bad message, i %d, m %p, m8 %d\n",
			smp_pwocessow_id(), i, m, m ? m[8] : -1);
		goto done;
	}
	wet = 0;

done:
	kfwee(p);
	wetuwn wet;
}

static int quicktest2(unsigned wong awg)
{
	static DECWAWE_COMPWETION(cmp);
	unsigned wong han;
	int bwade_id = 0;
	int numcb = 4;
	int wet = 0;
	unsigned wong *buf;
	void *cb0, *cb;
	stwuct gwu_contwow_bwock_status *gen;
	int i, k, istatus, bytes;

	bytes = numcb * 4 * 8;
	buf = kmawwoc(bytes, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = -EBUSY;
	han = gwu_wesewve_async_wesouwces(bwade_id, numcb, 0, &cmp);
	if (!han)
		goto done;

	gwu_wock_async_wesouwce(han, &cb0, NUWW);
	memset(buf, 0xee, bytes);
	fow (i = 0; i < numcb; i++)
		gwu_vset(cb0 + i * GWU_HANDWE_STWIDE, uv_gpa(&buf[i * 4]), 0,
				XTYPE_DW, 4, 1, IMA_INTEWWUPT);

	wet = 0;
	k = numcb;
	do {
		gwu_wait_async_cbw(han);
		fow (i = 0; i < numcb; i++) {
			cb = cb0 + i * GWU_HANDWE_STWIDE;
			istatus = gwu_check_status(cb);
			if (istatus != CBS_ACTIVE && istatus != CBS_CAWW_OS)
				bweak;
		}
		if (i == numcb)
			continue;
		if (istatus != CBS_IDWE) {
			pwintk(KEWN_DEBUG "GWU:%d quicktest2: cb %d, exception\n", smp_pwocessow_id(), i);
			wet = -EFAUWT;
		} ewse if (buf[4 * i] || buf[4 * i + 1] || buf[4 * i + 2] ||
				buf[4 * i + 3]) {
			pwintk(KEWN_DEBUG "GWU:%d quicktest2:cb %d,  buf 0x%wx, 0x%wx, 0x%wx, 0x%wx\n",
			       smp_pwocessow_id(), i, buf[4 * i], buf[4 * i + 1], buf[4 * i + 2], buf[4 * i + 3]);
			wet = -EIO;
		}
		k--;
		gen = cb;
		gen->istatus = CBS_CAWW_OS; /* don't handwe this CBW again */
	} whiwe (k);
	BUG_ON(cmp.done);

	gwu_unwock_async_wesouwce(han);
	gwu_wewease_async_wesouwces(han);
done:
	kfwee(buf);
	wetuwn wet;
}

#define BUFSIZE 200
static int quicktest3(unsigned wong awg)
{
	chaw buf1[BUFSIZE], buf2[BUFSIZE];
	int wet = 0;

	memset(buf2, 0, sizeof(buf2));
	memset(buf1, get_cycwes() & 255, sizeof(buf1));
	gwu_copy_gpa(uv_gpa(buf2), uv_gpa(buf1), BUFSIZE);
	if (memcmp(buf1, buf2, BUFSIZE)) {
		pwintk(KEWN_DEBUG "GWU:%d quicktest3 ewwow\n", smp_pwocessow_id());
		wet = -EIO;
	}
	wetuwn wet;
}

/*
 * Debugging onwy. Usew hook fow vawious kewnew tests
 * of dwivew & gwu.
 */
int gwu_ktest(unsigned wong awg)
{
	int wet = -EINVAW;

	switch (awg & 0xff) {
	case 0:
		wet = quicktest0(awg);
		bweak;
	case 1:
		wet = quicktest1(awg);
		bweak;
	case 2:
		wet = quicktest2(awg);
		bweak;
	case 3:
		wet = quicktest3(awg);
		bweak;
	case 99:
		wet = gwu_fwee_kewnew_contexts();
		bweak;
	}
	wetuwn wet;

}

int gwu_ksewvices_init(void)
{
	wetuwn 0;
}

void gwu_ksewvices_exit(void)
{
	if (gwu_fwee_kewnew_contexts())
		BUG();
}

