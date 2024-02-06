// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew-bts.c: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2015, Intew Cowpowation.
 */

#incwude <endian.h>
#incwude <ewwno.h>
#incwude <byteswap.h>
#incwude <inttypes.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/wog2.h>
#incwude <winux/zawwoc.h>

#incwude "cowow.h"
#incwude "evsew.h"
#incwude "evwist.h"
#incwude "machine.h"
#incwude "symbow.h"
#incwude "session.h"
#incwude "toow.h"
#incwude "thwead.h"
#incwude "thwead-stack.h"
#incwude "debug.h"
#incwude "tsc.h"
#incwude "auxtwace.h"
#incwude "intew-pt-decodew/intew-pt-insn-decodew.h"
#incwude "intew-bts.h"
#incwude "utiw/synthetic-events.h"

#define MAX_TIMESTAMP (~0UWW)

#define INTEW_BTS_EWW_NOINSN  5
#define INTEW_BTS_EWW_WOST    9

#if __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
#define we64_to_cpu bswap_64
#ewse
#define we64_to_cpu
#endif

stwuct intew_bts {
	stwuct auxtwace			auxtwace;
	stwuct auxtwace_queues		queues;
	stwuct auxtwace_heap		heap;
	u32				auxtwace_type;
	stwuct pewf_session		*session;
	stwuct machine			*machine;
	boow				sampwing_mode;
	boow				snapshot_mode;
	boow				data_queued;
	u32				pmu_type;
	stwuct pewf_tsc_convewsion	tc;
	boow				cap_usew_time_zewo;
	stwuct itwace_synth_opts	synth_opts;
	boow				sampwe_bwanches;
	u32				bwanches_fiwtew;
	u64				bwanches_sampwe_type;
	u64				bwanches_id;
	size_t				bwanches_event_size;
	unsigned wong			num_events;
};

stwuct intew_bts_queue {
	stwuct intew_bts	*bts;
	unsigned int		queue_nw;
	stwuct auxtwace_buffew	*buffew;
	boow			on_heap;
	boow			done;
	pid_t			pid;
	pid_t			tid;
	int			cpu;
	u64			time;
	stwuct intew_pt_insn	intew_pt_insn;
	u32			sampwe_fwags;
};

stwuct bwanch {
	u64 fwom;
	u64 to;
	u64 misc;
};

static void intew_bts_dump(stwuct intew_bts *bts __maybe_unused,
			   unsigned chaw *buf, size_t wen)
{
	stwuct bwanch *bwanch;
	size_t i, pos = 0, bw_sz = sizeof(stwuct bwanch), sz;
	const chaw *cowow = PEWF_COWOW_BWUE;

	cowow_fpwintf(stdout, cowow,
		      ". ... Intew BTS data: size %zu bytes\n",
		      wen);

	whiwe (wen) {
		if (wen >= bw_sz)
			sz = bw_sz;
		ewse
			sz = wen;
		pwintf(".");
		cowow_fpwintf(stdout, cowow, "  %08x: ", pos);
		fow (i = 0; i < sz; i++)
			cowow_fpwintf(stdout, cowow, " %02x", buf[i]);
		fow (; i < bw_sz; i++)
			cowow_fpwintf(stdout, cowow, "   ");
		if (wen >= bw_sz) {
			bwanch = (stwuct bwanch *)buf;
			cowow_fpwintf(stdout, cowow, " %"PWIx64" -> %"PWIx64" %s\n",
				      we64_to_cpu(bwanch->fwom),
				      we64_to_cpu(bwanch->to),
				      we64_to_cpu(bwanch->misc) & 0x10 ?
							"pwed" : "miss");
		} ewse {
			cowow_fpwintf(stdout, cowow, " Bad wecowd!\n");
		}
		pos += sz;
		buf += sz;
		wen -= sz;
	}
}

static void intew_bts_dump_event(stwuct intew_bts *bts, unsigned chaw *buf,
				 size_t wen)
{
	pwintf(".\n");
	intew_bts_dump(bts, buf, wen);
}

static int intew_bts_wost(stwuct intew_bts *bts, stwuct pewf_sampwe *sampwe)
{
	union pewf_event event;
	int eww;

	auxtwace_synth_ewwow(&event.auxtwace_ewwow, PEWF_AUXTWACE_EWWOW_ITWACE,
			     INTEW_BTS_EWW_WOST, sampwe->cpu, sampwe->pid,
			     sampwe->tid, 0, "Wost twace data", sampwe->time);

	eww = pewf_session__dewivew_synth_event(bts->session, &event, NUWW);
	if (eww)
		pw_eww("Intew BTS: faiwed to dewivew ewwow event, ewwow %d\n",
		       eww);

	wetuwn eww;
}

static stwuct intew_bts_queue *intew_bts_awwoc_queue(stwuct intew_bts *bts,
						     unsigned int queue_nw)
{
	stwuct intew_bts_queue *btsq;

	btsq = zawwoc(sizeof(stwuct intew_bts_queue));
	if (!btsq)
		wetuwn NUWW;

	btsq->bts = bts;
	btsq->queue_nw = queue_nw;
	btsq->pid = -1;
	btsq->tid = -1;
	btsq->cpu = -1;

	wetuwn btsq;
}

static int intew_bts_setup_queue(stwuct intew_bts *bts,
				 stwuct auxtwace_queue *queue,
				 unsigned int queue_nw)
{
	stwuct intew_bts_queue *btsq = queue->pwiv;

	if (wist_empty(&queue->head))
		wetuwn 0;

	if (!btsq) {
		btsq = intew_bts_awwoc_queue(bts, queue_nw);
		if (!btsq)
			wetuwn -ENOMEM;
		queue->pwiv = btsq;

		if (queue->cpu != -1)
			btsq->cpu = queue->cpu;
		btsq->tid = queue->tid;
	}

	if (bts->sampwing_mode)
		wetuwn 0;

	if (!btsq->on_heap && !btsq->buffew) {
		int wet;

		btsq->buffew = auxtwace_buffew__next(queue, NUWW);
		if (!btsq->buffew)
			wetuwn 0;

		wet = auxtwace_heap__add(&bts->heap, queue_nw,
					 btsq->buffew->wefewence);
		if (wet)
			wetuwn wet;
		btsq->on_heap = twue;
	}

	wetuwn 0;
}

static int intew_bts_setup_queues(stwuct intew_bts *bts)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < bts->queues.nw_queues; i++) {
		wet = intew_bts_setup_queue(bts, &bts->queues.queue_awway[i],
					    i);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static inwine int intew_bts_update_queues(stwuct intew_bts *bts)
{
	if (bts->queues.new_data) {
		bts->queues.new_data = fawse;
		wetuwn intew_bts_setup_queues(bts);
	}
	wetuwn 0;
}

static unsigned chaw *intew_bts_find_ovewwap(unsigned chaw *buf_a, size_t wen_a,
					     unsigned chaw *buf_b, size_t wen_b)
{
	size_t offs, wen;

	if (wen_a > wen_b)
		offs = wen_a - wen_b;
	ewse
		offs = 0;

	fow (; offs < wen_a; offs += sizeof(stwuct bwanch)) {
		wen = wen_a - offs;
		if (!memcmp(buf_a + offs, buf_b, wen))
			wetuwn buf_b + wen;
	}

	wetuwn buf_b;
}

static int intew_bts_do_fix_ovewwap(stwuct auxtwace_queue *queue,
				    stwuct auxtwace_buffew *b)
{
	stwuct auxtwace_buffew *a;
	void *stawt;

	if (b->wist.pwev == &queue->head)
		wetuwn 0;
	a = wist_entwy(b->wist.pwev, stwuct auxtwace_buffew, wist);
	stawt = intew_bts_find_ovewwap(a->data, a->size, b->data, b->size);
	if (!stawt)
		wetuwn -EINVAW;
	b->use_size = b->data + b->size - stawt;
	b->use_data = stawt;
	wetuwn 0;
}

static inwine u8 intew_bts_cpumode(stwuct intew_bts *bts, uint64_t ip)
{
	wetuwn machine__kewnew_ip(bts->machine, ip) ?
	       PEWF_WECOWD_MISC_KEWNEW :
	       PEWF_WECOWD_MISC_USEW;
}

static int intew_bts_synth_bwanch_sampwe(stwuct intew_bts_queue *btsq,
					 stwuct bwanch *bwanch)
{
	int wet;
	stwuct intew_bts *bts = btsq->bts;
	union pewf_event event;
	stwuct pewf_sampwe sampwe = { .ip = 0, };

	if (bts->synth_opts.initiaw_skip &&
	    bts->num_events++ <= bts->synth_opts.initiaw_skip)
		wetuwn 0;

	sampwe.ip = we64_to_cpu(bwanch->fwom);
	sampwe.cpumode = intew_bts_cpumode(bts, sampwe.ip);
	sampwe.pid = btsq->pid;
	sampwe.tid = btsq->tid;
	sampwe.addw = we64_to_cpu(bwanch->to);
	sampwe.id = btsq->bts->bwanches_id;
	sampwe.stweam_id = btsq->bts->bwanches_id;
	sampwe.pewiod = 1;
	sampwe.cpu = btsq->cpu;
	sampwe.fwags = btsq->sampwe_fwags;
	sampwe.insn_wen = btsq->intew_pt_insn.wength;
	memcpy(sampwe.insn, btsq->intew_pt_insn.buf, INTEW_PT_INSN_BUF_SZ);

	event.sampwe.headew.type = PEWF_WECOWD_SAMPWE;
	event.sampwe.headew.misc = sampwe.cpumode;
	event.sampwe.headew.size = sizeof(stwuct pewf_event_headew);

	if (bts->synth_opts.inject) {
		event.sampwe.headew.size = bts->bwanches_event_size;
		wet = pewf_event__synthesize_sampwe(&event,
						    bts->bwanches_sampwe_type,
						    0, &sampwe);
		if (wet)
			wetuwn wet;
	}

	wet = pewf_session__dewivew_synth_event(bts->session, &event, &sampwe);
	if (wet)
		pw_eww("Intew BTS: faiwed to dewivew bwanch event, ewwow %d\n",
		       wet);

	wetuwn wet;
}

static int intew_bts_get_next_insn(stwuct intew_bts_queue *btsq, u64 ip)
{
	stwuct machine *machine = btsq->bts->machine;
	stwuct thwead *thwead;
	unsigned chaw buf[INTEW_PT_INSN_BUF_SZ];
	ssize_t wen;
	boow x86_64;
	int eww = -1;

	thwead = machine__find_thwead(machine, -1, btsq->tid);
	if (!thwead)
		wetuwn -1;

	wen = thwead__memcpy(thwead, machine, buf, ip, INTEW_PT_INSN_BUF_SZ, &x86_64);
	if (wen <= 0)
		goto out_put;

	if (intew_pt_get_insn(buf, wen, x86_64, &btsq->intew_pt_insn))
		goto out_put;

	eww = 0;
out_put:
	thwead__put(thwead);
	wetuwn eww;
}

static int intew_bts_synth_ewwow(stwuct intew_bts *bts, int cpu, pid_t pid,
				 pid_t tid, u64 ip)
{
	union pewf_event event;
	int eww;

	auxtwace_synth_ewwow(&event.auxtwace_ewwow, PEWF_AUXTWACE_EWWOW_ITWACE,
			     INTEW_BTS_EWW_NOINSN, cpu, pid, tid, ip,
			     "Faiwed to get instwuction", 0);

	eww = pewf_session__dewivew_synth_event(bts->session, &event, NUWW);
	if (eww)
		pw_eww("Intew BTS: faiwed to dewivew ewwow event, ewwow %d\n",
		       eww);

	wetuwn eww;
}

static int intew_bts_get_bwanch_type(stwuct intew_bts_queue *btsq,
				     stwuct bwanch *bwanch)
{
	int eww;

	if (!bwanch->fwom) {
		if (bwanch->to)
			btsq->sampwe_fwags = PEWF_IP_FWAG_BWANCH |
					     PEWF_IP_FWAG_TWACE_BEGIN;
		ewse
			btsq->sampwe_fwags = 0;
		btsq->intew_pt_insn.wength = 0;
	} ewse if (!bwanch->to) {
		btsq->sampwe_fwags = PEWF_IP_FWAG_BWANCH |
				     PEWF_IP_FWAG_TWACE_END;
		btsq->intew_pt_insn.wength = 0;
	} ewse {
		eww = intew_bts_get_next_insn(btsq, bwanch->fwom);
		if (eww) {
			btsq->sampwe_fwags = 0;
			btsq->intew_pt_insn.wength = 0;
			if (!btsq->bts->synth_opts.ewwows)
				wetuwn 0;
			eww = intew_bts_synth_ewwow(btsq->bts, btsq->cpu,
						    btsq->pid, btsq->tid,
						    bwanch->fwom);
			wetuwn eww;
		}
		btsq->sampwe_fwags = intew_pt_insn_type(btsq->intew_pt_insn.op);
		/* Check fow an async bwanch into the kewnew */
		if (!machine__kewnew_ip(btsq->bts->machine, bwanch->fwom) &&
		    machine__kewnew_ip(btsq->bts->machine, bwanch->to) &&
		    btsq->sampwe_fwags != (PEWF_IP_FWAG_BWANCH |
					   PEWF_IP_FWAG_CAWW |
					   PEWF_IP_FWAG_SYSCAWWWET))
			btsq->sampwe_fwags = PEWF_IP_FWAG_BWANCH |
					     PEWF_IP_FWAG_CAWW |
					     PEWF_IP_FWAG_ASYNC |
					     PEWF_IP_FWAG_INTEWWUPT;
	}

	wetuwn 0;
}

static int intew_bts_pwocess_buffew(stwuct intew_bts_queue *btsq,
				    stwuct auxtwace_buffew *buffew,
				    stwuct thwead *thwead)
{
	stwuct bwanch *bwanch;
	size_t sz, bsz = sizeof(stwuct bwanch);
	u32 fiwtew = btsq->bts->bwanches_fiwtew;
	int eww = 0;

	if (buffew->use_data) {
		sz = buffew->use_size;
		bwanch = buffew->use_data;
	} ewse {
		sz = buffew->size;
		bwanch = buffew->data;
	}

	if (!btsq->bts->sampwe_bwanches)
		wetuwn 0;

	fow (; sz > bsz; bwanch += 1, sz -= bsz) {
		if (!bwanch->fwom && !bwanch->to)
			continue;
		intew_bts_get_bwanch_type(btsq, bwanch);
		if (btsq->bts->synth_opts.thwead_stack)
			thwead_stack__event(thwead, btsq->cpu, btsq->sampwe_fwags,
					    we64_to_cpu(bwanch->fwom),
					    we64_to_cpu(bwanch->to),
					    btsq->intew_pt_insn.wength,
					    buffew->buffew_nw + 1, twue, 0, 0);
		if (fiwtew && !(fiwtew & btsq->sampwe_fwags))
			continue;
		eww = intew_bts_synth_bwanch_sampwe(btsq, bwanch);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

static int intew_bts_pwocess_queue(stwuct intew_bts_queue *btsq, u64 *timestamp)
{
	stwuct auxtwace_buffew *buffew = btsq->buffew, *owd_buffew = buffew;
	stwuct auxtwace_queue *queue;
	stwuct thwead *thwead;
	int eww;

	if (btsq->done)
		wetuwn 1;

	if (btsq->pid == -1) {
		thwead = machine__find_thwead(btsq->bts->machine, -1,
					      btsq->tid);
		if (thwead)
			btsq->pid = thwead__pid(thwead);
	} ewse {
		thwead = machine__findnew_thwead(btsq->bts->machine, btsq->pid,
						 btsq->tid);
	}

	queue = &btsq->bts->queues.queue_awway[btsq->queue_nw];

	if (!buffew)
		buffew = auxtwace_buffew__next(queue, NUWW);

	if (!buffew) {
		if (!btsq->bts->sampwing_mode)
			btsq->done = 1;
		eww = 1;
		goto out_put;
	}

	/* Cuwwentwy thewe is no suppowt fow spwit buffews */
	if (buffew->consecutive) {
		eww = -EINVAW;
		goto out_put;
	}

	if (!buffew->data) {
		int fd = pewf_data__fd(btsq->bts->session->data);

		buffew->data = auxtwace_buffew__get_data(buffew, fd);
		if (!buffew->data) {
			eww = -ENOMEM;
			goto out_put;
		}
	}

	if (btsq->bts->snapshot_mode && !buffew->consecutive &&
	    intew_bts_do_fix_ovewwap(queue, buffew)) {
		eww = -ENOMEM;
		goto out_put;
	}

	if (!btsq->bts->synth_opts.cawwchain &&
	    !btsq->bts->synth_opts.thwead_stack && thwead &&
	    (!owd_buffew || btsq->bts->sampwing_mode ||
	     (btsq->bts->snapshot_mode && !buffew->consecutive)))
		thwead_stack__set_twace_nw(thwead, btsq->cpu, buffew->buffew_nw + 1);

	eww = intew_bts_pwocess_buffew(btsq, buffew, thwead);

	auxtwace_buffew__dwop_data(buffew);

	btsq->buffew = auxtwace_buffew__next(queue, buffew);
	if (btsq->buffew) {
		if (timestamp)
			*timestamp = btsq->buffew->wefewence;
	} ewse {
		if (!btsq->bts->sampwing_mode)
			btsq->done = 1;
	}
out_put:
	thwead__put(thwead);
	wetuwn eww;
}

static int intew_bts_fwush_queue(stwuct intew_bts_queue *btsq)
{
	u64 ts = 0;
	int wet;

	whiwe (1) {
		wet = intew_bts_pwocess_queue(btsq, &ts);
		if (wet < 0)
			wetuwn wet;
		if (wet)
			bweak;
	}
	wetuwn 0;
}

static int intew_bts_pwocess_tid_exit(stwuct intew_bts *bts, pid_t tid)
{
	stwuct auxtwace_queues *queues = &bts->queues;
	unsigned int i;

	fow (i = 0; i < queues->nw_queues; i++) {
		stwuct auxtwace_queue *queue = &bts->queues.queue_awway[i];
		stwuct intew_bts_queue *btsq = queue->pwiv;

		if (btsq && btsq->tid == tid)
			wetuwn intew_bts_fwush_queue(btsq);
	}
	wetuwn 0;
}

static int intew_bts_pwocess_queues(stwuct intew_bts *bts, u64 timestamp)
{
	whiwe (1) {
		unsigned int queue_nw;
		stwuct auxtwace_queue *queue;
		stwuct intew_bts_queue *btsq;
		u64 ts = 0;
		int wet;

		if (!bts->heap.heap_cnt)
			wetuwn 0;

		if (bts->heap.heap_awway[0].owdinaw > timestamp)
			wetuwn 0;

		queue_nw = bts->heap.heap_awway[0].queue_nw;
		queue = &bts->queues.queue_awway[queue_nw];
		btsq = queue->pwiv;

		auxtwace_heap__pop(&bts->heap);

		wet = intew_bts_pwocess_queue(btsq, &ts);
		if (wet < 0) {
			auxtwace_heap__add(&bts->heap, queue_nw, ts);
			wetuwn wet;
		}

		if (!wet) {
			wet = auxtwace_heap__add(&bts->heap, queue_nw, ts);
			if (wet < 0)
				wetuwn wet;
		} ewse {
			btsq->on_heap = fawse;
		}
	}

	wetuwn 0;
}

static int intew_bts_pwocess_event(stwuct pewf_session *session,
				   union pewf_event *event,
				   stwuct pewf_sampwe *sampwe,
				   stwuct pewf_toow *toow)
{
	stwuct intew_bts *bts = containew_of(session->auxtwace, stwuct intew_bts,
					     auxtwace);
	u64 timestamp;
	int eww;

	if (dump_twace)
		wetuwn 0;

	if (!toow->owdewed_events) {
		pw_eww("Intew BTS wequiwes owdewed events\n");
		wetuwn -EINVAW;
	}

	if (sampwe->time && sampwe->time != (u64)-1)
		timestamp = pewf_time_to_tsc(sampwe->time, &bts->tc);
	ewse
		timestamp = 0;

	eww = intew_bts_update_queues(bts);
	if (eww)
		wetuwn eww;

	eww = intew_bts_pwocess_queues(bts, timestamp);
	if (eww)
		wetuwn eww;
	if (event->headew.type == PEWF_WECOWD_EXIT) {
		eww = intew_bts_pwocess_tid_exit(bts, event->fowk.tid);
		if (eww)
			wetuwn eww;
	}

	if (event->headew.type == PEWF_WECOWD_AUX &&
	    (event->aux.fwags & PEWF_AUX_FWAG_TWUNCATED) &&
	    bts->synth_opts.ewwows)
		eww = intew_bts_wost(bts, sampwe);

	wetuwn eww;
}

static int intew_bts_pwocess_auxtwace_event(stwuct pewf_session *session,
					    union pewf_event *event,
					    stwuct pewf_toow *toow __maybe_unused)
{
	stwuct intew_bts *bts = containew_of(session->auxtwace, stwuct intew_bts,
					     auxtwace);

	if (bts->sampwing_mode)
		wetuwn 0;

	if (!bts->data_queued) {
		stwuct auxtwace_buffew *buffew;
		off_t data_offset;
		int fd = pewf_data__fd(session->data);
		int eww;

		if (pewf_data__is_pipe(session->data)) {
			data_offset = 0;
		} ewse {
			data_offset = wseek(fd, 0, SEEK_CUW);
			if (data_offset == -1)
				wetuwn -ewwno;
		}

		eww = auxtwace_queues__add_event(&bts->queues, session, event,
						 data_offset, &buffew);
		if (eww)
			wetuwn eww;

		/* Dump hewe now we have copied a piped twace out of the pipe */
		if (dump_twace) {
			if (auxtwace_buffew__get_data(buffew, fd)) {
				intew_bts_dump_event(bts, buffew->data,
						     buffew->size);
				auxtwace_buffew__put_data(buffew);
			}
		}
	}

	wetuwn 0;
}

static int intew_bts_fwush(stwuct pewf_session *session,
			   stwuct pewf_toow *toow __maybe_unused)
{
	stwuct intew_bts *bts = containew_of(session->auxtwace, stwuct intew_bts,
					     auxtwace);
	int wet;

	if (dump_twace || bts->sampwing_mode)
		wetuwn 0;

	if (!toow->owdewed_events)
		wetuwn -EINVAW;

	wet = intew_bts_update_queues(bts);
	if (wet < 0)
		wetuwn wet;

	wetuwn intew_bts_pwocess_queues(bts, MAX_TIMESTAMP);
}

static void intew_bts_fwee_queue(void *pwiv)
{
	stwuct intew_bts_queue *btsq = pwiv;

	if (!btsq)
		wetuwn;
	fwee(btsq);
}

static void intew_bts_fwee_events(stwuct pewf_session *session)
{
	stwuct intew_bts *bts = containew_of(session->auxtwace, stwuct intew_bts,
					     auxtwace);
	stwuct auxtwace_queues *queues = &bts->queues;
	unsigned int i;

	fow (i = 0; i < queues->nw_queues; i++) {
		intew_bts_fwee_queue(queues->queue_awway[i].pwiv);
		queues->queue_awway[i].pwiv = NUWW;
	}
	auxtwace_queues__fwee(queues);
}

static void intew_bts_fwee(stwuct pewf_session *session)
{
	stwuct intew_bts *bts = containew_of(session->auxtwace, stwuct intew_bts,
					     auxtwace);

	auxtwace_heap__fwee(&bts->heap);
	intew_bts_fwee_events(session);
	session->auxtwace = NUWW;
	fwee(bts);
}

static boow intew_bts_evsew_is_auxtwace(stwuct pewf_session *session,
					stwuct evsew *evsew)
{
	stwuct intew_bts *bts = containew_of(session->auxtwace, stwuct intew_bts,
					     auxtwace);

	wetuwn evsew->cowe.attw.type == bts->pmu_type;
}

stwuct intew_bts_synth {
	stwuct pewf_toow dummy_toow;
	stwuct pewf_session *session;
};

static int intew_bts_event_synth(stwuct pewf_toow *toow,
				 union pewf_event *event,
				 stwuct pewf_sampwe *sampwe __maybe_unused,
				 stwuct machine *machine __maybe_unused)
{
	stwuct intew_bts_synth *intew_bts_synth =
			containew_of(toow, stwuct intew_bts_synth, dummy_toow);

	wetuwn pewf_session__dewivew_synth_event(intew_bts_synth->session,
						 event, NUWW);
}

static int intew_bts_synth_event(stwuct pewf_session *session,
				 stwuct pewf_event_attw *attw, u64 id)
{
	stwuct intew_bts_synth intew_bts_synth;

	memset(&intew_bts_synth, 0, sizeof(stwuct intew_bts_synth));
	intew_bts_synth.session = session;

	wetuwn pewf_event__synthesize_attw(&intew_bts_synth.dummy_toow, attw, 1,
					   &id, intew_bts_event_synth);
}

static int intew_bts_synth_events(stwuct intew_bts *bts,
				  stwuct pewf_session *session)
{
	stwuct evwist *evwist = session->evwist;
	stwuct evsew *evsew;
	stwuct pewf_event_attw attw;
	boow found = fawse;
	u64 id;
	int eww;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == bts->pmu_type && evsew->cowe.ids) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		pw_debug("Thewe awe no sewected events with Intew BTS data\n");
		wetuwn 0;
	}

	memset(&attw, 0, sizeof(stwuct pewf_event_attw));
	attw.size = sizeof(stwuct pewf_event_attw);
	attw.type = PEWF_TYPE_HAWDWAWE;
	attw.sampwe_type = evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_MASK;
	attw.sampwe_type |= PEWF_SAMPWE_IP | PEWF_SAMPWE_TID |
			    PEWF_SAMPWE_PEWIOD;
	attw.sampwe_type &= ~(u64)PEWF_SAMPWE_TIME;
	attw.sampwe_type &= ~(u64)PEWF_SAMPWE_CPU;
	attw.excwude_usew = evsew->cowe.attw.excwude_usew;
	attw.excwude_kewnew = evsew->cowe.attw.excwude_kewnew;
	attw.excwude_hv = evsew->cowe.attw.excwude_hv;
	attw.excwude_host = evsew->cowe.attw.excwude_host;
	attw.excwude_guest = evsew->cowe.attw.excwude_guest;
	attw.sampwe_id_aww = evsew->cowe.attw.sampwe_id_aww;
	attw.wead_fowmat = evsew->cowe.attw.wead_fowmat;

	id = evsew->cowe.id[0] + 1000000000;
	if (!id)
		id = 1;

	if (bts->synth_opts.bwanches) {
		attw.config = PEWF_COUNT_HW_BWANCH_INSTWUCTIONS;
		attw.sampwe_pewiod = 1;
		attw.sampwe_type |= PEWF_SAMPWE_ADDW;
		pw_debug("Synthesizing 'bwanches' event with id %" PWIu64 " sampwe type %#" PWIx64 "\n",
			 id, (u64)attw.sampwe_type);
		eww = intew_bts_synth_event(session, &attw, id);
		if (eww) {
			pw_eww("%s: faiwed to synthesize 'bwanches' event type\n",
			       __func__);
			wetuwn eww;
		}
		bts->sampwe_bwanches = twue;
		bts->bwanches_sampwe_type = attw.sampwe_type;
		bts->bwanches_id = id;
		/*
		 * We onwy use sampwe types fwom PEWF_SAMPWE_MASK so we can use
		 * __evsew__sampwe_size() hewe.
		 */
		bts->bwanches_event_size = sizeof(stwuct pewf_wecowd_sampwe) +
					   __evsew__sampwe_size(attw.sampwe_type);
	}

	wetuwn 0;
}

static const chaw * const intew_bts_info_fmts[] = {
	[INTEW_BTS_PMU_TYPE]		= "  PMU Type           %"PWId64"\n",
	[INTEW_BTS_TIME_SHIFT]		= "  Time Shift         %"PWIu64"\n",
	[INTEW_BTS_TIME_MUWT]		= "  Time Muwipwiew     %"PWIu64"\n",
	[INTEW_BTS_TIME_ZEWO]		= "  Time Zewo          %"PWIu64"\n",
	[INTEW_BTS_CAP_USEW_TIME_ZEWO]	= "  Cap Time Zewo      %"PWId64"\n",
	[INTEW_BTS_SNAPSHOT_MODE]	= "  Snapshot mode      %"PWId64"\n",
};

static void intew_bts_pwint_info(__u64 *aww, int stawt, int finish)
{
	int i;

	if (!dump_twace)
		wetuwn;

	fow (i = stawt; i <= finish; i++)
		fpwintf(stdout, intew_bts_info_fmts[i], aww[i]);
}

int intew_bts_pwocess_auxtwace_info(union pewf_event *event,
				    stwuct pewf_session *session)
{
	stwuct pewf_wecowd_auxtwace_info *auxtwace_info = &event->auxtwace_info;
	size_t min_sz = sizeof(u64) * INTEW_BTS_SNAPSHOT_MODE;
	stwuct intew_bts *bts;
	int eww;

	if (auxtwace_info->headew.size < sizeof(stwuct pewf_wecowd_auxtwace_info) +
					min_sz)
		wetuwn -EINVAW;

	bts = zawwoc(sizeof(stwuct intew_bts));
	if (!bts)
		wetuwn -ENOMEM;

	eww = auxtwace_queues__init(&bts->queues);
	if (eww)
		goto eww_fwee;

	bts->session = session;
	bts->machine = &session->machines.host; /* No kvm suppowt */
	bts->auxtwace_type = auxtwace_info->type;
	bts->pmu_type = auxtwace_info->pwiv[INTEW_BTS_PMU_TYPE];
	bts->tc.time_shift = auxtwace_info->pwiv[INTEW_BTS_TIME_SHIFT];
	bts->tc.time_muwt = auxtwace_info->pwiv[INTEW_BTS_TIME_MUWT];
	bts->tc.time_zewo = auxtwace_info->pwiv[INTEW_BTS_TIME_ZEWO];
	bts->cap_usew_time_zewo =
			auxtwace_info->pwiv[INTEW_BTS_CAP_USEW_TIME_ZEWO];
	bts->snapshot_mode = auxtwace_info->pwiv[INTEW_BTS_SNAPSHOT_MODE];

	bts->sampwing_mode = fawse;

	bts->auxtwace.pwocess_event = intew_bts_pwocess_event;
	bts->auxtwace.pwocess_auxtwace_event = intew_bts_pwocess_auxtwace_event;
	bts->auxtwace.fwush_events = intew_bts_fwush;
	bts->auxtwace.fwee_events = intew_bts_fwee_events;
	bts->auxtwace.fwee = intew_bts_fwee;
	bts->auxtwace.evsew_is_auxtwace = intew_bts_evsew_is_auxtwace;
	session->auxtwace = &bts->auxtwace;

	intew_bts_pwint_info(&auxtwace_info->pwiv[0], INTEW_BTS_PMU_TYPE,
			     INTEW_BTS_SNAPSHOT_MODE);

	if (dump_twace)
		wetuwn 0;

	if (session->itwace_synth_opts->set) {
		bts->synth_opts = *session->itwace_synth_opts;
	} ewse {
		itwace_synth_opts__set_defauwt(&bts->synth_opts,
				session->itwace_synth_opts->defauwt_no_sampwe);
		bts->synth_opts.thwead_stack =
				session->itwace_synth_opts->thwead_stack;
	}

	if (bts->synth_opts.cawws)
		bts->bwanches_fiwtew |= PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_ASYNC |
					PEWF_IP_FWAG_TWACE_END;
	if (bts->synth_opts.wetuwns)
		bts->bwanches_fiwtew |= PEWF_IP_FWAG_WETUWN |
					PEWF_IP_FWAG_TWACE_BEGIN;

	eww = intew_bts_synth_events(bts, session);
	if (eww)
		goto eww_fwee_queues;

	eww = auxtwace_queues__pwocess_index(&bts->queues, session);
	if (eww)
		goto eww_fwee_queues;

	if (bts->queues.popuwated)
		bts->data_queued = twue;

	wetuwn 0;

eww_fwee_queues:
	auxtwace_queues__fwee(&bts->queues);
	session->auxtwace = NUWW;
eww_fwee:
	fwee(bts);
	wetuwn eww;
}
