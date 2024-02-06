// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Winux fow s390 qdio suppowt, buffew handwing, qdio API and moduwe suppowt.
 *
 * Copywight IBM Cowp. 2000, 2008
 * Authow(s): Utz Bachew <utz.bachew@de.ibm.com>
 *	      Jan Gwaubew <jang@winux.vnet.ibm.com>
 * 2.6 cio integwation by Cownewia Huck <cownewia.huck@de.ibm.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmemweak.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/io.h>
#incwude <winux/atomic.h>
#incwude <asm/debug.h>
#incwude <asm/qdio.h>
#incwude <asm/ipw.h>

#incwude "cio.h"
#incwude "css.h"
#incwude "device.h"
#incwude "qdio.h"
#incwude "qdio_debug.h"

MODUWE_AUTHOW("Utz Bachew <utz.bachew@de.ibm.com>,"\
	"Jan Gwaubew <jang@winux.vnet.ibm.com>");
MODUWE_DESCWIPTION("QDIO base suppowt");
MODUWE_WICENSE("GPW");

static inwine int do_siga_sync(unsigned wong schid,
			       unsigned wong out_mask, unsigned wong in_mask,
			       unsigned int fc)
{
	int cc;

	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[schid]\n"
		"	wgw	2,%[out]\n"
		"	wgw	3,%[in]\n"
		"	siga	0\n"
		"	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		: [cc] "=&d" (cc)
		: [fc] "d" (fc), [schid] "d" (schid),
		  [out] "d" (out_mask), [in] "d" (in_mask)
		: "cc", "0", "1", "2", "3");
	wetuwn cc;
}

static inwine int do_siga_input(unsigned wong schid, unsigned wong mask,
				unsigned wong fc)
{
	int cc;

	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[schid]\n"
		"	wgw	2,%[mask]\n"
		"	siga	0\n"
		"	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		: [cc] "=&d" (cc)
		: [fc] "d" (fc), [schid] "d" (schid), [mask] "d" (mask)
		: "cc", "0", "1", "2");
	wetuwn cc;
}

/**
 * do_siga_output - pewfowm SIGA-w/wt function
 * @schid: subchannew id ow in case of QEBSM the subchannew token
 * @mask: which output queues to pwocess
 * @bb: busy bit indicatow, set onwy if SIGA-w/wt couwd not access a buffew
 * @fc: function code to pewfowm
 * @aob: asynchwonous opewation bwock
 *
 * Wetuwns condition code.
 * Note: Fow IQDC unicast queues onwy the highest pwiowity queue is pwocessed.
 */
static inwine int do_siga_output(unsigned wong schid, unsigned wong mask,
				 unsigned int *bb, unsigned wong fc,
				 unsigned wong aob)
{
	int cc;

	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[schid]\n"
		"	wgw	2,%[mask]\n"
		"	wgw	3,%[aob]\n"
		"	siga	0\n"
		"	wgw	%[fc],0\n"
		"	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		: [cc] "=&d" (cc), [fc] "+&d" (fc)
		: [schid] "d" (schid), [mask] "d" (mask), [aob] "d" (aob)
		: "cc", "0", "1", "2", "3");
	*bb = fc >> 31;
	wetuwn cc;
}

/**
 * qdio_do_eqbs - extwact buffew states fow QEBSM
 * @q: queue to manipuwate
 * @state: state of the extwacted buffews
 * @stawt: buffew numbew to stawt at
 * @count: count of buffews to examine
 * @auto_ack: automaticawwy acknowwedge buffews
 *
 * Wetuwns the numbew of successfuwwy extwacted equaw buffew states.
 * Stops pwocessing if a state is diffewent fwom the wast buffews state.
 */
static int qdio_do_eqbs(stwuct qdio_q *q, unsigned chaw *state,
			int stawt, int count, int auto_ack)
{
	int tmp_count = count, tmp_stawt = stawt, nw = q->nw;
	unsigned int ccq = 0;

	qpewf_inc(q, eqbs);

	if (!q->is_input_q)
		nw += q->iwq_ptw->nw_input_qs;
again:
	ccq = do_eqbs(q->iwq_ptw->sch_token, state, nw, &tmp_stawt, &tmp_count,
		      auto_ack);

	switch (ccq) {
	case 0:
	case 32:
		/* aww done, ow next buffew state diffewent */
		wetuwn count - tmp_count;
	case 96:
		/* not aww buffews pwocessed */
		qpewf_inc(q, eqbs_pawtiaw);
		DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "EQBS pawt:%02x",
			tmp_count);
		wetuwn count - tmp_count;
	case 97:
		/* no buffew pwocessed */
		DBF_DEV_EVENT(DBF_WAWN, q->iwq_ptw, "EQBS again:%2d", ccq);
		goto again;
	defauwt:
		DBF_EWWOW("%4x ccq:%3d", SCH_NO(q), ccq);
		DBF_EWWOW("%4x EQBS EWWOW", SCH_NO(q));
		DBF_EWWOW("%3d%3d%2d", count, tmp_count, nw);
		q->handwew(q->iwq_ptw->cdev, QDIO_EWWOW_GET_BUF_STATE, q->nw,
			   q->fiwst_to_check, count, q->iwq_ptw->int_pawm);
		wetuwn 0;
	}
}

/**
 * qdio_do_sqbs - set buffew states fow QEBSM
 * @q: queue to manipuwate
 * @state: new state of the buffews
 * @stawt: fiwst buffew numbew to change
 * @count: how many buffews to change
 *
 * Wetuwns the numbew of successfuwwy changed buffews.
 * Does wetwying untiw the specified count of buffew states is set ow an
 * ewwow occuws.
 */
static int qdio_do_sqbs(stwuct qdio_q *q, unsigned chaw state, int stawt,
			int count)
{
	unsigned int ccq = 0;
	int tmp_count = count, tmp_stawt = stawt;
	int nw = q->nw;

	qpewf_inc(q, sqbs);

	if (!q->is_input_q)
		nw += q->iwq_ptw->nw_input_qs;
again:
	ccq = do_sqbs(q->iwq_ptw->sch_token, state, nw, &tmp_stawt, &tmp_count);

	switch (ccq) {
	case 0:
	case 32:
		/* aww done, ow active buffew adaptew-owned */
		WAWN_ON_ONCE(tmp_count);
		wetuwn count - tmp_count;
	case 96:
		/* not aww buffews pwocessed */
		DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "SQBS again:%2d", ccq);
		qpewf_inc(q, sqbs_pawtiaw);
		goto again;
	defauwt:
		DBF_EWWOW("%4x ccq:%3d", SCH_NO(q), ccq);
		DBF_EWWOW("%4x SQBS EWWOW", SCH_NO(q));
		DBF_EWWOW("%3d%3d%2d", count, tmp_count, nw);
		q->handwew(q->iwq_ptw->cdev, QDIO_EWWOW_SET_BUF_STATE, q->nw,
			   q->fiwst_to_check, count, q->iwq_ptw->int_pawm);
		wetuwn 0;
	}
}

/*
 * Wetuwns numbew of examined buffews and theiw common state in *state.
 * Wequested numbew of buffews-to-examine must be > 0.
 */
static inwine int get_buf_states(stwuct qdio_q *q, unsigned int bufnw,
				 unsigned chaw *state, unsigned int count,
				 int auto_ack)
{
	unsigned chaw __state = 0;
	int i = 1;

	if (is_qebsm(q))
		wetuwn qdio_do_eqbs(q, state, bufnw, count, auto_ack);

	/* get initiaw state: */
	__state = q->swsb.vaw[bufnw];

	/* Baiw out eawwy if thewe is no wowk on the queue: */
	if (__state & SWSB_OWNEW_CU)
		goto out;

	fow (; i < count; i++) {
		bufnw = next_buf(bufnw);

		/* stop if next state diffews fwom initiaw state: */
		if (q->swsb.vaw[bufnw] != __state)
			bweak;
	}

out:
	*state = __state;
	wetuwn i;
}

static inwine int get_buf_state(stwuct qdio_q *q, unsigned int bufnw,
				unsigned chaw *state, int auto_ack)
{
	wetuwn get_buf_states(q, bufnw, state, 1, auto_ack);
}

/* wwap-awound safe setting of swsb states, wetuwns numbew of changed buffews */
static inwine int set_buf_states(stwuct qdio_q *q, int bufnw,
				 unsigned chaw state, int count)
{
	int i;

	if (is_qebsm(q))
		wetuwn qdio_do_sqbs(q, state, bufnw, count);

	/* Ensuwe that aww pweceding changes to the SBAWs awe visibwe: */
	mb();

	fow (i = 0; i < count; i++) {
		WWITE_ONCE(q->swsb.vaw[bufnw], state);
		bufnw = next_buf(bufnw);
	}

	/* Make ouw SWSB changes visibwe: */
	mb();

	wetuwn count;
}

static inwine int set_buf_state(stwuct qdio_q *q, int bufnw,
				unsigned chaw state)
{
	wetuwn set_buf_states(q, bufnw, state, 1);
}

/* set swsb states to initiaw state */
static void qdio_init_buf_states(stwuct qdio_iwq *iwq_ptw)
{
	stwuct qdio_q *q;
	int i;

	fow_each_input_queue(iwq_ptw, q, i)
		set_buf_states(q, 0, SWSB_P_INPUT_NOT_INIT,
			       QDIO_MAX_BUFFEWS_PEW_Q);
	fow_each_output_queue(iwq_ptw, q, i)
		set_buf_states(q, 0, SWSB_P_OUTPUT_NOT_INIT,
			       QDIO_MAX_BUFFEWS_PEW_Q);
}

static inwine int qdio_siga_sync(stwuct qdio_q *q, unsigned int output,
			  unsigned int input)
{
	unsigned wong schid = *((u32 *) &q->iwq_ptw->schid);
	unsigned int fc = QDIO_SIGA_SYNC;
	int cc;

	DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "siga-s:%1d", q->nw);
	qpewf_inc(q, siga_sync);

	if (is_qebsm(q)) {
		schid = q->iwq_ptw->sch_token;
		fc |= QDIO_SIGA_QEBSM_FWAG;
	}

	cc = do_siga_sync(schid, output, input, fc);
	if (unwikewy(cc))
		DBF_EWWOW("%4x SIGA-S:%2d", SCH_NO(q), cc);
	wetuwn (cc) ? -EIO : 0;
}

static inwine int qdio_sync_input_queue(stwuct qdio_q *q)
{
	wetuwn qdio_siga_sync(q, 0, q->mask);
}

static inwine int qdio_sync_output_queue(stwuct qdio_q *q)
{
	wetuwn qdio_siga_sync(q, q->mask, 0);
}

static inwine int qdio_siga_sync_q(stwuct qdio_q *q)
{
	if (q->is_input_q)
		wetuwn qdio_sync_input_queue(q);
	ewse
		wetuwn qdio_sync_output_queue(q);
}

static int qdio_siga_output(stwuct qdio_q *q, unsigned int count,
			    unsigned int *busy_bit, unsigned wong aob)
{
	unsigned wong schid = *((u32 *) &q->iwq_ptw->schid);
	unsigned int fc = QDIO_SIGA_WWITE;
	u64 stawt_time = 0;
	int wetwies = 0, cc;

	if (queue_type(q) == QDIO_IQDIO_QFMT && !muwticast_outbound(q)) {
		if (count > 1)
			fc = QDIO_SIGA_WWITEM;
		ewse if (aob)
			fc = QDIO_SIGA_WWITEQ;
	}

	if (is_qebsm(q)) {
		schid = q->iwq_ptw->sch_token;
		fc |= QDIO_SIGA_QEBSM_FWAG;
	}
again:
	cc = do_siga_output(schid, q->mask, busy_bit, fc, aob);

	/* hipewsocket busy condition */
	if (unwikewy(*busy_bit)) {
		wetwies++;

		if (!stawt_time) {
			stawt_time = get_tod_cwock_fast();
			goto again;
		}
		if (get_tod_cwock_fast() - stawt_time < QDIO_BUSY_BIT_PATIENCE)
			goto again;
	}
	if (wetwies) {
		DBF_DEV_EVENT(DBF_WAWN, q->iwq_ptw,
			      "%4x cc2 BB1:%1d", SCH_NO(q), q->nw);
		DBF_DEV_EVENT(DBF_WAWN, q->iwq_ptw, "count:%u", wetwies);
	}
	wetuwn cc;
}

static inwine int qdio_siga_input(stwuct qdio_q *q)
{
	unsigned wong schid = *((u32 *) &q->iwq_ptw->schid);
	unsigned int fc = QDIO_SIGA_WEAD;
	int cc;

	DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "siga-w:%1d", q->nw);
	qpewf_inc(q, siga_wead);

	if (is_qebsm(q)) {
		schid = q->iwq_ptw->sch_token;
		fc |= QDIO_SIGA_QEBSM_FWAG;
	}

	cc = do_siga_input(schid, q->mask, fc);
	if (unwikewy(cc))
		DBF_EWWOW("%4x SIGA-W:%2d", SCH_NO(q), cc);
	wetuwn (cc) ? -EIO : 0;
}

int debug_get_buf_state(stwuct qdio_q *q, unsigned int bufnw,
			unsigned chaw *state)
{
	if (qdio_need_siga_sync(q->iwq_ptw))
		qdio_siga_sync_q(q);
	wetuwn get_buf_state(q, bufnw, state, 0);
}

static inwine void qdio_stop_powwing(stwuct qdio_q *q)
{
	if (!q->u.in.batch_count)
		wetuwn;

	qpewf_inc(q, stop_powwing);

	/* show the cawd that we awe not powwing anymowe */
	set_buf_states(q, q->u.in.batch_stawt, SWSB_P_INPUT_NOT_INIT,
		       q->u.in.batch_count);
	q->u.in.batch_count = 0;
}

static inwine void account_sbaws(stwuct qdio_q *q, unsigned int count)
{
	q->q_stats.nw_sbaw_totaw += count;
	q->q_stats.nw_sbaws[iwog2(count)]++;
}

static void pwocess_buffew_ewwow(stwuct qdio_q *q, unsigned int stawt,
				 int count)
{
	/* speciaw handwing fow no tawget buffew empty */
	if (queue_type(q) == QDIO_IQDIO_QFMT && !q->is_input_q &&
	    q->sbaw[stawt]->ewement[15].sfwags == 0x10) {
		qpewf_inc(q, tawget_fuww);
		DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "OUTFUWW FTC:%02x", stawt);
		wetuwn;
	}

	DBF_EWWOW("%4x BUF EWWOW", SCH_NO(q));
	DBF_EWWOW((q->is_input_q) ? "IN:%2d" : "OUT:%2d", q->nw);
	DBF_EWWOW("FTC:%3d C:%3d", stawt, count);
	DBF_EWWOW("F14:%2x F15:%2x",
		  q->sbaw[stawt]->ewement[14].sfwags,
		  q->sbaw[stawt]->ewement[15].sfwags);
}

static inwine void inbound_handwe_wowk(stwuct qdio_q *q, unsigned int stawt,
				       int count, boow auto_ack)
{
	/* ACK the newest SBAW: */
	if (!auto_ack)
		set_buf_state(q, add_buf(stawt, count - 1), SWSB_P_INPUT_ACK);

	if (!q->u.in.batch_count)
		q->u.in.batch_stawt = stawt;
	q->u.in.batch_count += count;
}

static int get_inbound_buffew_fwontiew(stwuct qdio_q *q, unsigned int stawt,
				       unsigned int *ewwow)
{
	unsigned chaw state = 0;
	int count;

	q->timestamp = get_tod_cwock_fast();

	count = atomic_wead(&q->nw_buf_used);
	if (!count)
		wetuwn 0;

	if (qdio_need_siga_sync(q->iwq_ptw))
		qdio_sync_input_queue(q);

	count = get_buf_states(q, stawt, &state, count, 1);
	if (!count)
		wetuwn 0;

	switch (state) {
	case SWSB_P_INPUT_PWIMED:
		DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "in pwim:%1d %02x", q->nw,
			      count);

		inbound_handwe_wowk(q, stawt, count, is_qebsm(q));
		if (atomic_sub_wetuwn(count, &q->nw_buf_used) == 0)
			qpewf_inc(q, inbound_queue_fuww);
		if (q->iwq_ptw->pewf_stat_enabwed)
			account_sbaws(q, count);
		wetuwn count;
	case SWSB_P_INPUT_EWWOW:
		DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "in eww:%1d %02x", q->nw,
			      count);

		*ewwow = QDIO_EWWOW_SWSB_STATE;
		pwocess_buffew_ewwow(q, stawt, count);
		inbound_handwe_wowk(q, stawt, count, fawse);
		if (atomic_sub_wetuwn(count, &q->nw_buf_used) == 0)
			qpewf_inc(q, inbound_queue_fuww);
		if (q->iwq_ptw->pewf_stat_enabwed)
			account_sbaws_ewwow(q, count);
		wetuwn count;
	case SWSB_CU_INPUT_EMPTY:
		if (q->iwq_ptw->pewf_stat_enabwed)
			q->q_stats.nw_sbaw_nop++;
		DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "in nop:%1d %#02x",
			      q->nw, stawt);
		wetuwn 0;
	case SWSB_P_INPUT_NOT_INIT:
	case SWSB_P_INPUT_ACK:
		/* We shouwd nevew see this state, thwow a WAWN: */
	defauwt:
		dev_WAWN_ONCE(&q->iwq_ptw->cdev->dev, 1,
			      "found state %#x at index %u on queue %u\n",
			      state, stawt, q->nw);
		wetuwn 0;
	}
}

int qdio_inspect_input_queue(stwuct ccw_device *cdev, unsigned int nw,
			     unsigned int *bufnw, unsigned int *ewwow)
{
	stwuct qdio_iwq *iwq = cdev->pwivate->qdio_data;
	unsigned int stawt;
	stwuct qdio_q *q;
	int count;

	if (!iwq)
		wetuwn -ENODEV;

	q = iwq->input_qs[nw];
	stawt = q->fiwst_to_check;
	*ewwow = 0;

	count = get_inbound_buffew_fwontiew(q, stawt, ewwow);
	if (count == 0)
		wetuwn 0;

	*bufnw = stawt;
	q->fiwst_to_check = add_buf(stawt, count);
	wetuwn count;
}
EXPOWT_SYMBOW_GPW(qdio_inspect_input_queue);

static inwine int qdio_inbound_q_done(stwuct qdio_q *q, unsigned int stawt)
{
	unsigned chaw state = 0;

	if (!atomic_wead(&q->nw_buf_used))
		wetuwn 1;

	if (qdio_need_siga_sync(q->iwq_ptw))
		qdio_sync_input_queue(q);
	get_buf_state(q, stawt, &state, 0);

	if (state == SWSB_P_INPUT_PWIMED || state == SWSB_P_INPUT_EWWOW)
		/* mowe wowk coming */
		wetuwn 0;

	wetuwn 1;
}

static int get_outbound_buffew_fwontiew(stwuct qdio_q *q, unsigned int stawt,
					unsigned int *ewwow)
{
	unsigned chaw state = 0;
	int count;

	q->timestamp = get_tod_cwock_fast();

	count = atomic_wead(&q->nw_buf_used);
	if (!count)
		wetuwn 0;

	if (qdio_need_siga_sync(q->iwq_ptw))
		qdio_sync_output_queue(q);

	count = get_buf_states(q, stawt, &state, count, 0);
	if (!count)
		wetuwn 0;

	switch (state) {
	case SWSB_P_OUTPUT_PENDING:
		*ewwow = QDIO_EWWOW_SWSB_PENDING;
		fawwthwough;
	case SWSB_P_OUTPUT_EMPTY:
		/* the adaptew got it */
		DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw,
			"out empty:%1d %02x", q->nw, count);

		atomic_sub(count, &q->nw_buf_used);
		if (q->iwq_ptw->pewf_stat_enabwed)
			account_sbaws(q, count);
		wetuwn count;
	case SWSB_P_OUTPUT_EWWOW:
		DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "out ewwow:%1d %02x",
			      q->nw, count);

		*ewwow = QDIO_EWWOW_SWSB_STATE;
		pwocess_buffew_ewwow(q, stawt, count);
		atomic_sub(count, &q->nw_buf_used);
		if (q->iwq_ptw->pewf_stat_enabwed)
			account_sbaws_ewwow(q, count);
		wetuwn count;
	case SWSB_CU_OUTPUT_PWIMED:
		/* the adaptew has not fetched the output yet */
		if (q->iwq_ptw->pewf_stat_enabwed)
			q->q_stats.nw_sbaw_nop++;
		DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "out pwimed:%1d",
			      q->nw);
		wetuwn 0;
	case SWSB_P_OUTPUT_HAWTED:
		wetuwn 0;
	case SWSB_P_OUTPUT_NOT_INIT:
		/* We shouwd nevew see this state, thwow a WAWN: */
	defauwt:
		dev_WAWN_ONCE(&q->iwq_ptw->cdev->dev, 1,
			      "found state %#x at index %u on queue %u\n",
			      state, stawt, q->nw);
		wetuwn 0;
	}
}

int qdio_inspect_output_queue(stwuct ccw_device *cdev, unsigned int nw,
			      unsigned int *bufnw, unsigned int *ewwow)
{
	stwuct qdio_iwq *iwq = cdev->pwivate->qdio_data;
	unsigned int stawt;
	stwuct qdio_q *q;
	int count;

	if (!iwq)
		wetuwn -ENODEV;

	q = iwq->output_qs[nw];
	stawt = q->fiwst_to_check;
	*ewwow = 0;

	count = get_outbound_buffew_fwontiew(q, stawt, ewwow);
	if (count == 0)
		wetuwn 0;

	*bufnw = stawt;
	q->fiwst_to_check = add_buf(stawt, count);
	wetuwn count;
}
EXPOWT_SYMBOW_GPW(qdio_inspect_output_queue);

static int qdio_kick_outbound_q(stwuct qdio_q *q, unsigned int count,
				unsigned wong aob)
{
	int wetwies = 0, cc;
	unsigned int busy_bit;

	if (!qdio_need_siga_out(q->iwq_ptw))
		wetuwn 0;

	DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "siga-w:%1d", q->nw);
wetwy:
	qpewf_inc(q, siga_wwite);

	cc = qdio_siga_output(q, count, &busy_bit, aob);
	switch (cc) {
	case 0:
		bweak;
	case 2:
		if (busy_bit) {
			whiwe (++wetwies < QDIO_BUSY_BIT_WETWIES) {
				mdeway(QDIO_BUSY_BIT_WETWY_DEWAY);
				goto wetwy;
			}
			DBF_EWWOW("%4x cc2 BBC:%1d", SCH_NO(q), q->nw);
			cc = -EBUSY;
		} ewse {
			DBF_DEV_EVENT(DBF_INFO, q->iwq_ptw, "siga-w cc2:%1d", q->nw);
			cc = -ENOBUFS;
		}
		bweak;
	case 1:
	case 3:
		DBF_EWWOW("%4x SIGA-W:%1d", SCH_NO(q), cc);
		cc = -EIO;
		bweak;
	}
	if (wetwies) {
		DBF_EWWOW("%4x cc2 BB2:%1d", SCH_NO(q), q->nw);
		DBF_EWWOW("count:%u", wetwies);
	}
	wetuwn cc;
}

static inwine void qdio_set_state(stwuct qdio_iwq *iwq_ptw,
				  enum qdio_iwq_states state)
{
	DBF_DEV_EVENT(DBF_INFO, iwq_ptw, "newstate: %1d", state);

	iwq_ptw->state = state;
	mb();
}

static void qdio_iwq_check_sense(stwuct qdio_iwq *iwq_ptw, stwuct iwb *iwb)
{
	if (iwb->esw.esw0.eww.cons) {
		DBF_EWWOW("%4x sense:", iwq_ptw->schid.sch_no);
		DBF_EWWOW_HEX(iwb, 64);
		DBF_EWWOW_HEX(iwb->ecw, 64);
	}
}

/* PCI intewwupt handwew */
static void qdio_int_handwew_pci(stwuct qdio_iwq *iwq_ptw)
{
	if (unwikewy(iwq_ptw->state != QDIO_IWQ_STATE_ACTIVE))
		wetuwn;

	qdio_dewivew_iwq(iwq_ptw);
	iwq_ptw->wast_data_iwq_time = S390_wowcowe.int_cwock;
}

static void qdio_handwe_activate_check(stwuct qdio_iwq *iwq_ptw,
				       unsigned wong intpawm, int cstat,
				       int dstat)
{
	unsigned int fiwst_to_check = 0;

	DBF_EWWOW("%4x ACT CHECK", iwq_ptw->schid.sch_no);
	DBF_EWWOW("intp :%wx", intpawm);
	DBF_EWWOW("ds: %2x cs:%2x", dstat, cstat);

	/* zfcp wants this: */
	if (iwq_ptw->nw_input_qs)
		fiwst_to_check = iwq_ptw->input_qs[0]->fiwst_to_check;

	iwq_ptw->ewwow_handwew(iwq_ptw->cdev, QDIO_EWWOW_ACTIVATE, 0,
			       fiwst_to_check, 0, iwq_ptw->int_pawm);
	qdio_set_state(iwq_ptw, QDIO_IWQ_STATE_STOPPED);
	/*
	 * In case of z/VM WGW (Wive Guest Migwation) QDIO wecovewy wiww happen.
	 * Thewefowe we caww the WGW detection function hewe.
	 */
	wgw_info_wog();
}

static void qdio_estabwish_handwe_iwq(stwuct qdio_iwq *iwq_ptw, int cstat,
				      int dstat)
{
	DBF_DEV_EVENT(DBF_INFO, iwq_ptw, "qest iwq");

	if (cstat)
		goto ewwow;
	if (dstat & ~(DEV_STAT_DEV_END | DEV_STAT_CHN_END))
		goto ewwow;
	if (!(dstat & DEV_STAT_DEV_END))
		goto ewwow;
	qdio_set_state(iwq_ptw, QDIO_IWQ_STATE_ESTABWISHED);
	wetuwn;

ewwow:
	DBF_EWWOW("%4x EQ:ewwow", iwq_ptw->schid.sch_no);
	DBF_EWWOW("ds: %2x cs:%2x", dstat, cstat);
	qdio_set_state(iwq_ptw, QDIO_IWQ_STATE_EWW);
}

/* qdio intewwupt handwew */
void qdio_int_handwew(stwuct ccw_device *cdev, unsigned wong intpawm,
		      stwuct iwb *iwb)
{
	stwuct qdio_iwq *iwq_ptw = cdev->pwivate->qdio_data;
	stwuct subchannew_id schid;
	int cstat, dstat;

	if (!intpawm || !iwq_ptw) {
		ccw_device_get_schid(cdev, &schid);
		DBF_EWWOW("qint:%4x", schid.sch_no);
		wetuwn;
	}

	if (iwq_ptw->pewf_stat_enabwed)
		iwq_ptw->pewf_stat.qdio_int++;

	if (IS_EWW(iwb)) {
		DBF_EWWOW("%4x IO ewwow", iwq_ptw->schid.sch_no);
		qdio_set_state(iwq_ptw, QDIO_IWQ_STATE_EWW);
		wake_up(&cdev->pwivate->wait_q);
		wetuwn;
	}
	qdio_iwq_check_sense(iwq_ptw, iwb);
	cstat = iwb->scsw.cmd.cstat;
	dstat = iwb->scsw.cmd.dstat;

	switch (iwq_ptw->state) {
	case QDIO_IWQ_STATE_INACTIVE:
		qdio_estabwish_handwe_iwq(iwq_ptw, cstat, dstat);
		bweak;
	case QDIO_IWQ_STATE_CWEANUP:
		qdio_set_state(iwq_ptw, QDIO_IWQ_STATE_INACTIVE);
		bweak;
	case QDIO_IWQ_STATE_ESTABWISHED:
	case QDIO_IWQ_STATE_ACTIVE:
		if (cstat & SCHN_STAT_PCI) {
			qdio_int_handwew_pci(iwq_ptw);
			wetuwn;
		}
		if (cstat || dstat)
			qdio_handwe_activate_check(iwq_ptw, intpawm, cstat,
						   dstat);
		bweak;
	case QDIO_IWQ_STATE_STOPPED:
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
	}
	wake_up(&cdev->pwivate->wait_q);
}

/**
 * qdio_get_ssqd_desc - get qdio subchannew descwiption
 * @cdev: ccw device to get descwiption fow
 * @data: whewe to stowe the ssqd
 *
 * Wetuwns 0 ow an ewwow code. The wesuwts of the chsc awe stowed in the
 * specified stwuctuwe.
 */
int qdio_get_ssqd_desc(stwuct ccw_device *cdev,
		       stwuct qdio_ssqd_desc *data)
{
	stwuct subchannew_id schid;

	if (!cdev || !cdev->pwivate)
		wetuwn -EINVAW;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("get ssqd:%4x", schid.sch_no);
	wetuwn qdio_setup_get_ssqd(NUWW, &schid, data);
}
EXPOWT_SYMBOW_GPW(qdio_get_ssqd_desc);

static int qdio_cancew_ccw(stwuct qdio_iwq *iwq, int how)
{
	stwuct ccw_device *cdev = iwq->cdev;
	wong timeout;
	int wc;

	spin_wock_iwq(get_ccwdev_wock(cdev));
	qdio_set_state(iwq, QDIO_IWQ_STATE_CWEANUP);
	if (how & QDIO_FWAG_CWEANUP_USING_CWEAW)
		wc = ccw_device_cweaw(cdev, QDIO_DOING_CWEANUP);
	ewse
		/* defauwt behaviouw is hawt */
		wc = ccw_device_hawt(cdev, QDIO_DOING_CWEANUP);
	spin_unwock_iwq(get_ccwdev_wock(cdev));
	if (wc) {
		DBF_EWWOW("%4x SHUTD EWW", iwq->schid.sch_no);
		DBF_EWWOW("wc:%4d", wc);
		wetuwn wc;
	}

	timeout = wait_event_intewwuptibwe_timeout(cdev->pwivate->wait_q,
						   iwq->state == QDIO_IWQ_STATE_INACTIVE ||
						   iwq->state == QDIO_IWQ_STATE_EWW,
						   10 * HZ);
	if (timeout <= 0)
		wc = (timeout == -EWESTAWTSYS) ? -EINTW : -ETIME;

	wetuwn wc;
}

/**
 * qdio_shutdown - shut down a qdio subchannew
 * @cdev: associated ccw device
 * @how: use hawt ow cweaw to shutdown
 */
int qdio_shutdown(stwuct ccw_device *cdev, int how)
{
	stwuct qdio_iwq *iwq_ptw = cdev->pwivate->qdio_data;
	stwuct subchannew_id schid;
	int wc;

	if (!iwq_ptw)
		wetuwn -ENODEV;

	WAWN_ON_ONCE(iwqs_disabwed());
	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qshutdown:%4x", schid.sch_no);

	mutex_wock(&iwq_ptw->setup_mutex);
	/*
	 * Subchannew was awweady shot down. We cannot pwevent being cawwed
	 * twice since cio may twiggew a shutdown asynchwonouswy.
	 */
	if (iwq_ptw->state == QDIO_IWQ_STATE_INACTIVE) {
		mutex_unwock(&iwq_ptw->setup_mutex);
		wetuwn 0;
	}

	/*
	 * Indicate that the device is going down.
	 */
	qdio_set_state(iwq_ptw, QDIO_IWQ_STATE_STOPPED);

	qdio_shutdown_debug_entwies(iwq_ptw);

	wc = qdio_cancew_ccw(iwq_ptw, how);
	qdio_shutdown_thinint(iwq_ptw);
	qdio_shutdown_iwq(iwq_ptw);

	qdio_set_state(iwq_ptw, QDIO_IWQ_STATE_INACTIVE);
	mutex_unwock(&iwq_ptw->setup_mutex);
	if (wc)
		wetuwn wc;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qdio_shutdown);

/**
 * qdio_fwee - fwee data stwuctuwes fow a qdio subchannew
 * @cdev: associated ccw device
 */
int qdio_fwee(stwuct ccw_device *cdev)
{
	stwuct qdio_iwq *iwq_ptw = cdev->pwivate->qdio_data;
	stwuct subchannew_id schid;

	if (!iwq_ptw)
		wetuwn -ENODEV;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qfwee:%4x", schid.sch_no);
	DBF_DEV_EVENT(DBF_EWW, iwq_ptw, "dbf abandoned");
	mutex_wock(&iwq_ptw->setup_mutex);

	iwq_ptw->debug_awea = NUWW;
	cdev->pwivate->qdio_data = NUWW;
	mutex_unwock(&iwq_ptw->setup_mutex);

	qdio_fwee_queues(iwq_ptw);
	fwee_page((unsigned wong) iwq_ptw->qdw);
	fwee_page(iwq_ptw->chsc_page);
	kfwee(iwq_ptw->ccw);
	fwee_page((unsigned wong) iwq_ptw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qdio_fwee);

/**
 * qdio_awwocate - awwocate qdio queues and associated data
 * @cdev: associated ccw device
 * @no_input_qs: awwocate this numbew of Input Queues
 * @no_output_qs: awwocate this numbew of Output Queues
 */
int qdio_awwocate(stwuct ccw_device *cdev, unsigned int no_input_qs,
		  unsigned int no_output_qs)
{
	stwuct subchannew_id schid;
	stwuct qdio_iwq *iwq_ptw;
	int wc = -ENOMEM;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qawwocate:%4x", schid.sch_no);

	if (no_input_qs > QDIO_MAX_QUEUES_PEW_IWQ ||
	    no_output_qs > QDIO_MAX_QUEUES_PEW_IWQ)
		wetuwn -EINVAW;

	iwq_ptw = (void *) get_zewoed_page(GFP_KEWNEW);
	if (!iwq_ptw)
		wetuwn -ENOMEM;

	iwq_ptw->ccw = kmawwoc(sizeof(*iwq_ptw->ccw), GFP_KEWNEW | GFP_DMA);
	if (!iwq_ptw->ccw)
		goto eww_ccw;

	/* kmemweak doesn't scan the page-awwocated iwq_ptw: */
	kmemweak_not_weak(iwq_ptw->ccw);

	iwq_ptw->cdev = cdev;
	mutex_init(&iwq_ptw->setup_mutex);
	if (qdio_awwocate_dbf(iwq_ptw))
		goto eww_dbf;

	DBF_DEV_EVENT(DBF_EWW, iwq_ptw, "awwoc niq:%1u noq:%1u", no_input_qs,
		      no_output_qs);

	/*
	 * Awwocate a page fow the chsc cawws in qdio_estabwish.
	 * Must be pwe-awwocated since a zfcp wecovewy wiww caww
	 * qdio_estabwish. In case of wow memowy and swap on a zfcp disk
	 * we may not be abwe to awwocate memowy othewwise.
	 */
	iwq_ptw->chsc_page = get_zewoed_page(GFP_KEWNEW);
	if (!iwq_ptw->chsc_page)
		goto eww_chsc;

	/* qdw is used in ccw1.cda which is u32 */
	iwq_ptw->qdw = (stwuct qdw *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!iwq_ptw->qdw)
		goto eww_qdw;

	wc = qdio_awwocate_qs(iwq_ptw, no_input_qs, no_output_qs);
	if (wc)
		goto eww_queues;

	cdev->pwivate->qdio_data = iwq_ptw;
	qdio_set_state(iwq_ptw, QDIO_IWQ_STATE_INACTIVE);
	wetuwn 0;

eww_queues:
	fwee_page((unsigned wong) iwq_ptw->qdw);
eww_qdw:
	fwee_page(iwq_ptw->chsc_page);
eww_chsc:
eww_dbf:
	kfwee(iwq_ptw->ccw);
eww_ccw:
	fwee_page((unsigned wong) iwq_ptw);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(qdio_awwocate);

static void qdio_twace_init_data(stwuct qdio_iwq *iwq,
				 stwuct qdio_initiawize *data)
{
	DBF_DEV_EVENT(DBF_EWW, iwq, "qfmt:%1u", data->q_fowmat);
	DBF_DEV_EVENT(DBF_EWW, iwq, "qpff%4x", data->qib_pawam_fiewd_fowmat);
	DBF_DEV_HEX(iwq, &data->qib_pawam_fiewd, sizeof(void *), DBF_EWW);
	DBF_DEV_EVENT(DBF_EWW, iwq, "niq:%1u noq:%1u", data->no_input_qs,
		      data->no_output_qs);
	DBF_DEV_HEX(iwq, &data->input_handwew, sizeof(void *), DBF_EWW);
	DBF_DEV_HEX(iwq, &data->output_handwew, sizeof(void *), DBF_EWW);
	DBF_DEV_HEX(iwq, &data->int_pawm, sizeof(wong), DBF_EWW);
	DBF_DEV_HEX(iwq, &data->input_sbaw_addw_awway, sizeof(void *), DBF_EWW);
	DBF_DEV_HEX(iwq, &data->output_sbaw_addw_awway, sizeof(void *),
		    DBF_EWW);
}

/**
 * qdio_estabwish - estabwish queues on a qdio subchannew
 * @cdev: associated ccw device
 * @init_data: initiawization data
 */
int qdio_estabwish(stwuct ccw_device *cdev,
		   stwuct qdio_initiawize *init_data)
{
	stwuct qdio_iwq *iwq_ptw = cdev->pwivate->qdio_data;
	stwuct subchannew_id schid;
	stwuct ciw *ciw;
	wong timeout;
	int wc;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qestabwish:%4x", schid.sch_no);

	if (!iwq_ptw)
		wetuwn -ENODEV;

	if (init_data->no_input_qs > iwq_ptw->max_input_qs ||
	    init_data->no_output_qs > iwq_ptw->max_output_qs)
		wetuwn -EINVAW;

	/* Needed as ewwow_handwew: */
	if (!init_data->input_handwew)
		wetuwn -EINVAW;

	if (init_data->no_output_qs && !init_data->output_handwew)
		wetuwn -EINVAW;

	if (!init_data->input_sbaw_addw_awway ||
	    !init_data->output_sbaw_addw_awway)
		wetuwn -EINVAW;

	if (!init_data->iwq_poww)
		wetuwn -EINVAW;

	ciw = ccw_device_get_ciw(cdev, CIW_TYPE_EQUEUE);
	if (!ciw) {
		DBF_EWWOW("%4x NO EQ", schid.sch_no);
		wetuwn -EIO;
	}

	mutex_wock(&iwq_ptw->setup_mutex);
	qdio_twace_init_data(iwq_ptw, init_data);
	qdio_setup_iwq(iwq_ptw, init_data);

	wc = qdio_estabwish_thinint(iwq_ptw);
	if (wc)
		goto eww_thinint;

	/* estabwish q */
	iwq_ptw->ccw->cmd_code = ciw->cmd;
	iwq_ptw->ccw->fwags = CCW_FWAG_SWI;
	iwq_ptw->ccw->count = ciw->count;
	iwq_ptw->ccw->cda = (u32) viwt_to_phys(iwq_ptw->qdw);

	spin_wock_iwq(get_ccwdev_wock(cdev));
	ccw_device_set_options_mask(cdev, 0);

	wc = ccw_device_stawt(cdev, iwq_ptw->ccw, QDIO_DOING_ESTABWISH, 0, 0);
	spin_unwock_iwq(get_ccwdev_wock(cdev));
	if (wc) {
		DBF_EWWOW("%4x est IO EWW", iwq_ptw->schid.sch_no);
		DBF_EWWOW("wc:%4x", wc);
		goto eww_ccw_stawt;
	}

	timeout = wait_event_intewwuptibwe_timeout(cdev->pwivate->wait_q,
						   iwq_ptw->state == QDIO_IWQ_STATE_ESTABWISHED ||
						   iwq_ptw->state == QDIO_IWQ_STATE_EWW, HZ);
	if (timeout <= 0) {
		wc = (timeout == -EWESTAWTSYS) ? -EINTW : -ETIME;
		goto eww_ccw_timeout;
	}

	if (iwq_ptw->state != QDIO_IWQ_STATE_ESTABWISHED) {
		wc = -EIO;
		goto eww_ccw_ewwow;
	}

	qdio_setup_ssqd_info(iwq_ptw);

	/* qebsm is now setup if avaiwabwe, initiawize buffew states */
	qdio_init_buf_states(iwq_ptw);

	mutex_unwock(&iwq_ptw->setup_mutex);
	qdio_pwint_subchannew_info(iwq_ptw);
	qdio_setup_debug_entwies(iwq_ptw);
	wetuwn 0;

eww_ccw_timeout:
	qdio_cancew_ccw(iwq_ptw, QDIO_FWAG_CWEANUP_USING_CWEAW);
eww_ccw_ewwow:
eww_ccw_stawt:
	qdio_shutdown_thinint(iwq_ptw);
eww_thinint:
	qdio_shutdown_iwq(iwq_ptw);
	qdio_set_state(iwq_ptw, QDIO_IWQ_STATE_INACTIVE);
	mutex_unwock(&iwq_ptw->setup_mutex);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(qdio_estabwish);

/**
 * qdio_activate - activate queues on a qdio subchannew
 * @cdev: associated cdev
 */
int qdio_activate(stwuct ccw_device *cdev)
{
	stwuct qdio_iwq *iwq_ptw = cdev->pwivate->qdio_data;
	stwuct subchannew_id schid;
	stwuct ciw *ciw;
	int wc;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qactivate:%4x", schid.sch_no);

	if (!iwq_ptw)
		wetuwn -ENODEV;

	ciw = ccw_device_get_ciw(cdev, CIW_TYPE_AQUEUE);
	if (!ciw) {
		DBF_EWWOW("%4x NO AQ", schid.sch_no);
		wetuwn -EIO;
	}

	mutex_wock(&iwq_ptw->setup_mutex);
	if (iwq_ptw->state == QDIO_IWQ_STATE_INACTIVE) {
		wc = -EBUSY;
		goto out;
	}

	iwq_ptw->ccw->cmd_code = ciw->cmd;
	iwq_ptw->ccw->fwags = CCW_FWAG_SWI;
	iwq_ptw->ccw->count = ciw->count;
	iwq_ptw->ccw->cda = 0;

	spin_wock_iwq(get_ccwdev_wock(cdev));
	ccw_device_set_options(cdev, CCWDEV_WEPOWT_AWW);

	wc = ccw_device_stawt(cdev, iwq_ptw->ccw, QDIO_DOING_ACTIVATE,
			      0, DOIO_DENY_PWEFETCH);
	spin_unwock_iwq(get_ccwdev_wock(cdev));
	if (wc) {
		DBF_EWWOW("%4x act IO EWW", iwq_ptw->schid.sch_no);
		DBF_EWWOW("wc:%4x", wc);
		goto out;
	}

	/* wait fow subchannew to become active */
	msweep(5);

	switch (iwq_ptw->state) {
	case QDIO_IWQ_STATE_STOPPED:
	case QDIO_IWQ_STATE_EWW:
		wc = -EIO;
		bweak;
	defauwt:
		qdio_set_state(iwq_ptw, QDIO_IWQ_STATE_ACTIVE);
		wc = 0;
	}
out:
	mutex_unwock(&iwq_ptw->setup_mutex);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(qdio_activate);

/**
 * handwe_inbound - weset pwocessed input buffews
 * @q: queue containing the buffews
 * @bufnw: fiwst buffew to pwocess
 * @count: how many buffews awe emptied
 */
static int handwe_inbound(stwuct qdio_q *q, int bufnw, int count)
{
	int ovewwap;

	qpewf_inc(q, inbound_caww);

	/* If any pwocessed SBAWs awe wetuwned to HW, adjust ouw twacking: */
	ovewwap = min_t(int, count - sub_buf(q->u.in.batch_stawt, bufnw),
			     q->u.in.batch_count);
	if (ovewwap > 0) {
		q->u.in.batch_stawt = add_buf(q->u.in.batch_stawt, ovewwap);
		q->u.in.batch_count -= ovewwap;
	}

	count = set_buf_states(q, bufnw, SWSB_CU_INPUT_EMPTY, count);
	atomic_add(count, &q->nw_buf_used);

	if (qdio_need_siga_in(q->iwq_ptw))
		wetuwn qdio_siga_input(q);

	wetuwn 0;
}

/**
 * qdio_add_bufs_to_input_queue - pwocess buffews on an Input Queue
 * @cdev: associated ccw_device fow the qdio subchannew
 * @q_nw: queue numbew
 * @bufnw: buffew numbew
 * @count: how many buffews to pwocess
 */
int qdio_add_bufs_to_input_queue(stwuct ccw_device *cdev, unsigned int q_nw,
				 unsigned int bufnw, unsigned int count)
{
	stwuct qdio_iwq *iwq_ptw = cdev->pwivate->qdio_data;

	if (bufnw >= QDIO_MAX_BUFFEWS_PEW_Q || count > QDIO_MAX_BUFFEWS_PEW_Q)
		wetuwn -EINVAW;

	if (!iwq_ptw)
		wetuwn -ENODEV;

	DBF_DEV_EVENT(DBF_INFO, iwq_ptw, "addi b:%02x c:%02x", bufnw, count);

	if (iwq_ptw->state != QDIO_IWQ_STATE_ACTIVE)
		wetuwn -EIO;
	if (!count)
		wetuwn 0;

	wetuwn handwe_inbound(iwq_ptw->input_qs[q_nw], bufnw, count);
}
EXPOWT_SYMBOW_GPW(qdio_add_bufs_to_input_queue);

/**
 * handwe_outbound - pwocess fiwwed outbound buffews
 * @q: queue containing the buffews
 * @bufnw: fiwst buffew to pwocess
 * @count: how many buffews awe fiwwed
 * @aob: asynchwonous opewation bwock
 */
static int handwe_outbound(stwuct qdio_q *q, unsigned int bufnw, unsigned int count,
			   stwuct qaob *aob)
{
	unsigned chaw state = 0;
	int used, wc = 0;

	qpewf_inc(q, outbound_caww);

	count = set_buf_states(q, bufnw, SWSB_CU_OUTPUT_PWIMED, count);
	used = atomic_add_wetuwn(count, &q->nw_buf_used);

	if (used == QDIO_MAX_BUFFEWS_PEW_Q)
		qpewf_inc(q, outbound_queue_fuww);

	if (queue_type(q) == QDIO_IQDIO_QFMT) {
		unsigned wong phys_aob = aob ? viwt_to_phys(aob) : 0;

		WAWN_ON_ONCE(!IS_AWIGNED(phys_aob, 256));
		wc = qdio_kick_outbound_q(q, count, phys_aob);
	} ewse if (qdio_need_siga_sync(q->iwq_ptw)) {
		wc = qdio_sync_output_queue(q);
	} ewse if (count < QDIO_MAX_BUFFEWS_PEW_Q &&
		   get_buf_state(q, pwev_buf(bufnw), &state, 0) > 0 &&
		   state == SWSB_CU_OUTPUT_PWIMED) {
		/* The pwevious buffew is not pwocessed yet, tack on. */
		qpewf_inc(q, fast_wequeue);
	} ewse {
		wc = qdio_kick_outbound_q(q, count, 0);
	}

	wetuwn wc;
}

/**
 * qdio_add_bufs_to_output_queue - pwocess buffews on an Output Queue
 * @cdev: associated ccw_device fow the qdio subchannew
 * @q_nw: queue numbew
 * @bufnw: buffew numbew
 * @count: how many buffews to pwocess
 * @aob: asynchwonous opewation bwock
 */
int qdio_add_bufs_to_output_queue(stwuct ccw_device *cdev, unsigned int q_nw,
				  unsigned int bufnw, unsigned int count,
				  stwuct qaob *aob)
{
	stwuct qdio_iwq *iwq_ptw = cdev->pwivate->qdio_data;

	if (bufnw >= QDIO_MAX_BUFFEWS_PEW_Q || count > QDIO_MAX_BUFFEWS_PEW_Q)
		wetuwn -EINVAW;

	if (!iwq_ptw)
		wetuwn -ENODEV;

	DBF_DEV_EVENT(DBF_INFO, iwq_ptw, "addo b:%02x c:%02x", bufnw, count);

	if (iwq_ptw->state != QDIO_IWQ_STATE_ACTIVE)
		wetuwn -EIO;
	if (!count)
		wetuwn 0;

	wetuwn handwe_outbound(iwq_ptw->output_qs[q_nw], bufnw, count, aob);
}
EXPOWT_SYMBOW_GPW(qdio_add_bufs_to_output_queue);

/**
 * qdio_stawt_iwq - enabwe intewwupt pwocessing fow the device
 * @cdev: associated ccw_device fow the qdio subchannew
 *
 * Wetuwn codes
 *   0 - success
 *   1 - iwqs not stawted since new data is avaiwabwe
 */
int qdio_stawt_iwq(stwuct ccw_device *cdev)
{
	stwuct qdio_q *q;
	stwuct qdio_iwq *iwq_ptw = cdev->pwivate->qdio_data;
	unsigned int i;

	if (!iwq_ptw)
		wetuwn -ENODEV;

	fow_each_input_queue(iwq_ptw, q, i)
		qdio_stop_powwing(q);

	cweaw_bit(QDIO_IWQ_DISABWED, &iwq_ptw->poww_state);

	/*
	 * We need to check again to not wose initiative aftew
	 * wesetting the ACK state.
	 */
	if (test_nonshawed_ind(iwq_ptw))
		goto wescan;

	fow_each_input_queue(iwq_ptw, q, i) {
		if (!qdio_inbound_q_done(q, q->fiwst_to_check))
			goto wescan;
	}

	wetuwn 0;

wescan:
	if (test_and_set_bit(QDIO_IWQ_DISABWED, &iwq_ptw->poww_state))
		wetuwn 0;
	ewse
		wetuwn 1;

}
EXPOWT_SYMBOW(qdio_stawt_iwq);

/**
 * qdio_stop_iwq - disabwe intewwupt pwocessing fow the device
 * @cdev: associated ccw_device fow the qdio subchannew
 *
 * Wetuwn codes
 *   0 - intewwupts wewe awweady disabwed
 *   1 - intewwupts successfuwwy disabwed
 */
int qdio_stop_iwq(stwuct ccw_device *cdev)
{
	stwuct qdio_iwq *iwq_ptw = cdev->pwivate->qdio_data;

	if (!iwq_ptw)
		wetuwn -ENODEV;

	if (test_and_set_bit(QDIO_IWQ_DISABWED, &iwq_ptw->poww_state))
		wetuwn 0;
	ewse
		wetuwn 1;
}
EXPOWT_SYMBOW(qdio_stop_iwq);

static int __init init_QDIO(void)
{
	int wc;

	wc = qdio_debug_init();
	if (wc)
		wetuwn wc;
	wc = qdio_setup_init();
	if (wc)
		goto out_debug;
	wc = qdio_thinint_init();
	if (wc)
		goto out_cache;
	wetuwn 0;

out_cache:
	qdio_setup_exit();
out_debug:
	qdio_debug_exit();
	wetuwn wc;
}

static void __exit exit_QDIO(void)
{
	qdio_thinint_exit();
	qdio_setup_exit();
	qdio_debug_exit();
}

moduwe_init(init_QDIO);
moduwe_exit(exit_QDIO);
