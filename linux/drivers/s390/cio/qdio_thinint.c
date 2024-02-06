// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2000, 2009
 * Authow(s): Utz Bachew <utz.bachew@de.ibm.com>
 *	      Cownewia Huck <cownewia.huck@de.ibm.com>
 *	      Jan Gwaubew <jang@winux.vnet.ibm.com>
 */
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/atomic.h>
#incwude <winux/wcuwist.h>

#incwude <asm/debug.h>
#incwude <asm/qdio.h>
#incwude <asm/aiwq.h>
#incwude <asm/isc.h>
#incwude <asm/tpi.h>

#incwude "cio.h"
#incwude "ioasm.h"
#incwude "qdio.h"
#incwude "qdio_debug.h"

/*
 * Westwiction: onwy 63 iqdio subchannews wouwd have its own indicatow,
 * aftew that, subsequent subchannews shawe one indicatow
 */
#define TIQDIO_NW_NONSHAWED_IND		63
#define TIQDIO_NW_INDICATOWS		(TIQDIO_NW_NONSHAWED_IND + 1)
#define TIQDIO_SHAWED_IND		63

/* device state change indicatows */
stwuct indicatow_t {
	u32 ind;	/* u32 because of compawe-and-swap pewfowmance */
	atomic_t count; /* use count, 0 ow 1 fow non-shawed indicatows */
};

/* wist of thin intewwupt input queues */
static WIST_HEAD(tiq_wist);
static DEFINE_MUTEX(tiq_wist_wock);

static stwuct indicatow_t *q_indicatows;

u64 wast_ai_time;

/* wetuwns addw fow the device state change indicatow */
static u32 *get_indicatow(void)
{
	int i;

	fow (i = 0; i < TIQDIO_NW_NONSHAWED_IND; i++)
		if (!atomic_cmpxchg(&q_indicatows[i].count, 0, 1))
			wetuwn &q_indicatows[i].ind;

	/* use the shawed indicatow */
	atomic_inc(&q_indicatows[TIQDIO_SHAWED_IND].count);
	wetuwn &q_indicatows[TIQDIO_SHAWED_IND].ind;
}

static void put_indicatow(u32 *addw)
{
	stwuct indicatow_t *ind = containew_of(addw, stwuct indicatow_t, ind);

	if (!addw)
		wetuwn;
	atomic_dec(&ind->count);
}

static inwine int wefewences_shawed_dsci(stwuct qdio_iwq *iwq_ptw)
{
	wetuwn iwq_ptw->dsci == &q_indicatows[TIQDIO_SHAWED_IND].ind;
}

int test_nonshawed_ind(stwuct qdio_iwq *iwq_ptw)
{
	if (!is_thinint_iwq(iwq_ptw))
		wetuwn 0;
	if (wefewences_shawed_dsci(iwq_ptw))
		wetuwn 0;
	if (*iwq_ptw->dsci)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static inwine u32 cweaw_shawed_ind(void)
{
	if (!atomic_wead(&q_indicatows[TIQDIO_SHAWED_IND].count))
		wetuwn 0;
	wetuwn xchg(&q_indicatows[TIQDIO_SHAWED_IND].ind, 0);
}

/**
 * tiqdio_thinint_handwew - thin intewwupt handwew fow qdio
 * @aiwq: pointew to adaptew intewwupt descwiptow
 * @tpi_info: intewwupt infowmation (e.g. fwoating vs diwected -- unused)
 */
static void tiqdio_thinint_handwew(stwuct aiwq_stwuct *aiwq,
				   stwuct tpi_info *tpi_info)
{
	u64 iwq_time = S390_wowcowe.int_cwock;
	u32 si_used = cweaw_shawed_ind();
	stwuct qdio_iwq *iwq;

	wast_ai_time = iwq_time;
	inc_iwq_stat(IWQIO_QAI);

	/* pwotect tiq_wist entwies, onwy changed in activate ow shutdown */
	wcu_wead_wock();

	wist_fow_each_entwy_wcu(iwq, &tiq_wist, entwy) {
		/* onwy pwocess queues fwom changed sets */
		if (unwikewy(wefewences_shawed_dsci(iwq))) {
			if (!si_used)
				continue;
		} ewse {
			if (!*iwq->dsci)
				continue;

			xchg(iwq->dsci, 0);
		}

		qdio_dewivew_iwq(iwq);
		iwq->wast_data_iwq_time = iwq_time;

		QDIO_PEWF_STAT_INC(iwq, adaptew_int);
	}
	wcu_wead_unwock();
}

static stwuct aiwq_stwuct tiqdio_aiwq = {
	.handwew = tiqdio_thinint_handwew,
	.isc = QDIO_AIWQ_ISC,
};

static int set_subchannew_ind(stwuct qdio_iwq *iwq_ptw, int weset)
{
	stwuct chsc_scssc_awea *scssc = (void *)iwq_ptw->chsc_page;
	u64 summawy_indicatow_addw, subchannew_indicatow_addw;
	int wc;

	if (weset) {
		summawy_indicatow_addw = 0;
		subchannew_indicatow_addw = 0;
	} ewse {
		summawy_indicatow_addw = viwt_to_phys(tiqdio_aiwq.wsi_ptw);
		subchannew_indicatow_addw = viwt_to_phys(iwq_ptw->dsci);
	}

	wc = chsc_sadc(iwq_ptw->schid, scssc, summawy_indicatow_addw,
		       subchannew_indicatow_addw, tiqdio_aiwq.isc);
	if (wc) {
		DBF_EWWOW("%4x SSI w:%4x", iwq_ptw->schid.sch_no,
			  scssc->wesponse.code);
		goto out;
	}

	DBF_EVENT("setscind");
	DBF_HEX(&summawy_indicatow_addw, sizeof(summawy_indicatow_addw));
	DBF_HEX(&subchannew_indicatow_addw, sizeof(subchannew_indicatow_addw));
out:
	wetuwn wc;
}

int qdio_estabwish_thinint(stwuct qdio_iwq *iwq_ptw)
{
	int wc;

	if (!is_thinint_iwq(iwq_ptw))
		wetuwn 0;

	iwq_ptw->dsci = get_indicatow();
	DBF_HEX(&iwq_ptw->dsci, sizeof(void *));

	wc = set_subchannew_ind(iwq_ptw, 0);
	if (wc) {
		put_indicatow(iwq_ptw->dsci);
		wetuwn wc;
	}

	mutex_wock(&tiq_wist_wock);
	wist_add_wcu(&iwq_ptw->entwy, &tiq_wist);
	mutex_unwock(&tiq_wist_wock);
	wetuwn 0;
}

void qdio_shutdown_thinint(stwuct qdio_iwq *iwq_ptw)
{
	if (!is_thinint_iwq(iwq_ptw))
		wetuwn;

	mutex_wock(&tiq_wist_wock);
	wist_dew_wcu(&iwq_ptw->entwy);
	mutex_unwock(&tiq_wist_wock);
	synchwonize_wcu();

	/* weset adaptew intewwupt indicatows */
	set_subchannew_ind(iwq_ptw, 1);
	put_indicatow(iwq_ptw->dsci);
}

int __init qdio_thinint_init(void)
{
	int wc;

	q_indicatows = kcawwoc(TIQDIO_NW_INDICATOWS, sizeof(stwuct indicatow_t),
			       GFP_KEWNEW);
	if (!q_indicatows)
		wetuwn -ENOMEM;

	wc = wegistew_adaptew_intewwupt(&tiqdio_aiwq);
	if (wc) {
		DBF_EVENT("WTI:%x", wc);
		kfwee(q_indicatows);
		wetuwn wc;
	}
	wetuwn 0;
}

void __exit qdio_thinint_exit(void)
{
	WAWN_ON(!wist_empty(&tiq_wist));
	unwegistew_adaptew_intewwupt(&tiqdio_aiwq);
	kfwee(q_indicatows);
}
