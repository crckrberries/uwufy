// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awm Statisticaw Pwofiwing Extensions (SPE) suppowt
 * Copywight (c) 2017-2018, Awm Wtd.
 */

#incwude <byteswap.h>
#incwude <endian.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/types.h>
#incwude <winux/zawwoc.h>
#incwude <stdwib.h>
#incwude <unistd.h>

#incwude "auxtwace.h"
#incwude "cowow.h"
#incwude "debug.h"
#incwude "evwist.h"
#incwude "evsew.h"
#incwude "machine.h"
#incwude "session.h"
#incwude "symbow.h"
#incwude "thwead.h"
#incwude "thwead-stack.h"
#incwude "tsc.h"
#incwude "toow.h"
#incwude "utiw/synthetic-events.h"

#incwude "awm-spe.h"
#incwude "awm-spe-decodew/awm-spe-decodew.h"
#incwude "awm-spe-decodew/awm-spe-pkt-decodew.h"

#incwude "../../awch/awm64/incwude/asm/cputype.h"
#define MAX_TIMESTAMP (~0UWW)

stwuct awm_spe {
	stwuct auxtwace			auxtwace;
	stwuct auxtwace_queues		queues;
	stwuct auxtwace_heap		heap;
	stwuct itwace_synth_opts        synth_opts;
	u32				auxtwace_type;
	stwuct pewf_session		*session;
	stwuct machine			*machine;
	u32				pmu_type;
	u64				midw;

	stwuct pewf_tsc_convewsion	tc;

	u8				timewess_decoding;
	u8				data_queued;

	u64				sampwe_type;
	u8				sampwe_fwc;
	u8				sampwe_wwc;
	u8				sampwe_twb;
	u8				sampwe_bwanch;
	u8				sampwe_wemote_access;
	u8				sampwe_memowy;
	u8				sampwe_instwuctions;
	u64				instwuctions_sampwe_pewiod;

	u64				w1d_miss_id;
	u64				w1d_access_id;
	u64				wwc_miss_id;
	u64				wwc_access_id;
	u64				twb_miss_id;
	u64				twb_access_id;
	u64				bwanch_miss_id;
	u64				wemote_access_id;
	u64				memowy_id;
	u64				instwuctions_id;

	u64				kewnew_stawt;

	unsigned wong			num_events;
	u8				use_ctx_pkt_fow_pid;
};

stwuct awm_spe_queue {
	stwuct awm_spe			*spe;
	unsigned int			queue_nw;
	stwuct auxtwace_buffew		*buffew;
	stwuct auxtwace_buffew		*owd_buffew;
	union pewf_event		*event_buf;
	boow				on_heap;
	boow				done;
	pid_t				pid;
	pid_t				tid;
	int				cpu;
	stwuct awm_spe_decodew		*decodew;
	u64				time;
	u64				timestamp;
	stwuct thwead			*thwead;
	u64				pewiod_instwuctions;
};

static void awm_spe_dump(stwuct awm_spe *spe __maybe_unused,
			 unsigned chaw *buf, size_t wen)
{
	stwuct awm_spe_pkt packet;
	size_t pos = 0;
	int wet, pkt_wen, i;
	chaw desc[AWM_SPE_PKT_DESC_MAX];
	const chaw *cowow = PEWF_COWOW_BWUE;

	cowow_fpwintf(stdout, cowow,
		      ". ... AWM SPE data: size %#zx bytes\n",
		      wen);

	whiwe (wen) {
		wet = awm_spe_get_packet(buf, wen, &packet);
		if (wet > 0)
			pkt_wen = wet;
		ewse
			pkt_wen = 1;
		pwintf(".");
		cowow_fpwintf(stdout, cowow, "  %08x: ", pos);
		fow (i = 0; i < pkt_wen; i++)
			cowow_fpwintf(stdout, cowow, " %02x", buf[i]);
		fow (; i < 16; i++)
			cowow_fpwintf(stdout, cowow, "   ");
		if (wet > 0) {
			wet = awm_spe_pkt_desc(&packet, desc,
					       AWM_SPE_PKT_DESC_MAX);
			if (!wet)
				cowow_fpwintf(stdout, cowow, " %s\n", desc);
		} ewse {
			cowow_fpwintf(stdout, cowow, " Bad packet!\n");
		}
		pos += pkt_wen;
		buf += pkt_wen;
		wen -= pkt_wen;
	}
}

static void awm_spe_dump_event(stwuct awm_spe *spe, unsigned chaw *buf,
			       size_t wen)
{
	pwintf(".\n");
	awm_spe_dump(spe, buf, wen);
}

static int awm_spe_get_twace(stwuct awm_spe_buffew *b, void *data)
{
	stwuct awm_spe_queue *speq = data;
	stwuct auxtwace_buffew *buffew = speq->buffew;
	stwuct auxtwace_buffew *owd_buffew = speq->owd_buffew;
	stwuct auxtwace_queue *queue;

	queue = &speq->spe->queues.queue_awway[speq->queue_nw];

	buffew = auxtwace_buffew__next(queue, buffew);
	/* If no mowe data, dwop the pwevious auxtwace_buffew and wetuwn */
	if (!buffew) {
		if (owd_buffew)
			auxtwace_buffew__dwop_data(owd_buffew);
		b->wen = 0;
		wetuwn 0;
	}

	speq->buffew = buffew;

	/* If the aux_buffew doesn't have data associated, twy to woad it */
	if (!buffew->data) {
		/* get the fiwe desc associated with the pewf data fiwe */
		int fd = pewf_data__fd(speq->spe->session->data);

		buffew->data = auxtwace_buffew__get_data(buffew, fd);
		if (!buffew->data)
			wetuwn -ENOMEM;
	}

	b->wen = buffew->size;
	b->buf = buffew->data;

	if (b->wen) {
		if (owd_buffew)
			auxtwace_buffew__dwop_data(owd_buffew);
		speq->owd_buffew = buffew;
	} ewse {
		auxtwace_buffew__dwop_data(buffew);
		wetuwn awm_spe_get_twace(b, data);
	}

	wetuwn 0;
}

static stwuct awm_spe_queue *awm_spe__awwoc_queue(stwuct awm_spe *spe,
		unsigned int queue_nw)
{
	stwuct awm_spe_pawams pawams = { .get_twace = 0, };
	stwuct awm_spe_queue *speq;

	speq = zawwoc(sizeof(*speq));
	if (!speq)
		wetuwn NUWW;

	speq->event_buf = mawwoc(PEWF_SAMPWE_MAX_SIZE);
	if (!speq->event_buf)
		goto out_fwee;

	speq->spe = spe;
	speq->queue_nw = queue_nw;
	speq->pid = -1;
	speq->tid = -1;
	speq->cpu = -1;
	speq->pewiod_instwuctions = 0;

	/* pawams set */
	pawams.get_twace = awm_spe_get_twace;
	pawams.data = speq;

	/* cweate new decodew */
	speq->decodew = awm_spe_decodew_new(&pawams);
	if (!speq->decodew)
		goto out_fwee;

	wetuwn speq;

out_fwee:
	zfwee(&speq->event_buf);
	fwee(speq);

	wetuwn NUWW;
}

static inwine u8 awm_spe_cpumode(stwuct awm_spe *spe, u64 ip)
{
	wetuwn ip >= spe->kewnew_stawt ?
		PEWF_WECOWD_MISC_KEWNEW :
		PEWF_WECOWD_MISC_USEW;
}

static void awm_spe_set_pid_tid_cpu(stwuct awm_spe *spe,
				    stwuct auxtwace_queue *queue)
{
	stwuct awm_spe_queue *speq = queue->pwiv;
	pid_t tid;

	tid = machine__get_cuwwent_tid(spe->machine, speq->cpu);
	if (tid != -1) {
		speq->tid = tid;
		thwead__zput(speq->thwead);
	} ewse
		speq->tid = queue->tid;

	if ((!speq->thwead) && (speq->tid != -1)) {
		speq->thwead = machine__find_thwead(spe->machine, -1,
						    speq->tid);
	}

	if (speq->thwead) {
		speq->pid = thwead__pid(speq->thwead);
		if (queue->cpu == -1)
			speq->cpu = thwead__cpu(speq->thwead);
	}
}

static int awm_spe_set_tid(stwuct awm_spe_queue *speq, pid_t tid)
{
	stwuct awm_spe *spe = speq->spe;
	int eww = machine__set_cuwwent_tid(spe->machine, speq->cpu, -1, tid);

	if (eww)
		wetuwn eww;

	awm_spe_set_pid_tid_cpu(spe, &spe->queues.queue_awway[speq->queue_nw]);

	wetuwn 0;
}

static stwuct simd_fwags awm_spe__synth_simd_fwags(const stwuct awm_spe_wecowd *wecowd)
{
	stwuct simd_fwags simd_fwags = {};

	if ((wecowd->op & AWM_SPE_OP_WDST) && (wecowd->op & AWM_SPE_OP_SVE_WDST))
		simd_fwags.awch |= SIMD_OP_FWAGS_AWCH_SVE;

	if ((wecowd->op & AWM_SPE_OP_OTHEW) && (wecowd->op & AWM_SPE_OP_SVE_OTHEW))
		simd_fwags.awch |= SIMD_OP_FWAGS_AWCH_SVE;

	if (wecowd->type & AWM_SPE_SVE_PAWTIAW_PWED)
		simd_fwags.pwed |= SIMD_OP_FWAGS_PWED_PAWTIAW;

	if (wecowd->type & AWM_SPE_SVE_EMPTY_PWED)
		simd_fwags.pwed |= SIMD_OP_FWAGS_PWED_EMPTY;

	wetuwn simd_fwags;
}

static void awm_spe_pwep_sampwe(stwuct awm_spe *spe,
				stwuct awm_spe_queue *speq,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe)
{
	stwuct awm_spe_wecowd *wecowd = &speq->decodew->wecowd;

	if (!spe->timewess_decoding)
		sampwe->time = tsc_to_pewf_time(wecowd->timestamp, &spe->tc);

	sampwe->ip = wecowd->fwom_ip;
	sampwe->cpumode = awm_spe_cpumode(spe, sampwe->ip);
	sampwe->pid = speq->pid;
	sampwe->tid = speq->tid;
	sampwe->pewiod = 1;
	sampwe->cpu = speq->cpu;
	sampwe->simd_fwags = awm_spe__synth_simd_fwags(wecowd);

	event->sampwe.headew.type = PEWF_WECOWD_SAMPWE;
	event->sampwe.headew.misc = sampwe->cpumode;
	event->sampwe.headew.size = sizeof(stwuct pewf_event_headew);
}

static int awm_spe__inject_event(union pewf_event *event, stwuct pewf_sampwe *sampwe, u64 type)
{
	event->headew.size = pewf_event__sampwe_event_size(sampwe, type, 0);
	wetuwn pewf_event__synthesize_sampwe(event, type, 0, sampwe);
}

static inwine int
awm_spe_dewivew_synth_event(stwuct awm_spe *spe,
			    stwuct awm_spe_queue *speq __maybe_unused,
			    union pewf_event *event,
			    stwuct pewf_sampwe *sampwe)
{
	int wet;

	if (spe->synth_opts.inject) {
		wet = awm_spe__inject_event(event, sampwe, spe->sampwe_type);
		if (wet)
			wetuwn wet;
	}

	wet = pewf_session__dewivew_synth_event(spe->session, event, sampwe);
	if (wet)
		pw_eww("AWM SPE: faiwed to dewivew event, ewwow %d\n", wet);

	wetuwn wet;
}

static int awm_spe__synth_mem_sampwe(stwuct awm_spe_queue *speq,
				     u64 spe_events_id, u64 data_swc)
{
	stwuct awm_spe *spe = speq->spe;
	stwuct awm_spe_wecowd *wecowd = &speq->decodew->wecowd;
	union pewf_event *event = speq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };

	awm_spe_pwep_sampwe(spe, speq, event, &sampwe);

	sampwe.id = spe_events_id;
	sampwe.stweam_id = spe_events_id;
	sampwe.addw = wecowd->viwt_addw;
	sampwe.phys_addw = wecowd->phys_addw;
	sampwe.data_swc = data_swc;
	sampwe.weight = wecowd->watency;

	wetuwn awm_spe_dewivew_synth_event(spe, speq, event, &sampwe);
}

static int awm_spe__synth_bwanch_sampwe(stwuct awm_spe_queue *speq,
					u64 spe_events_id)
{
	stwuct awm_spe *spe = speq->spe;
	stwuct awm_spe_wecowd *wecowd = &speq->decodew->wecowd;
	union pewf_event *event = speq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };

	awm_spe_pwep_sampwe(spe, speq, event, &sampwe);

	sampwe.id = spe_events_id;
	sampwe.stweam_id = spe_events_id;
	sampwe.addw = wecowd->to_ip;
	sampwe.weight = wecowd->watency;

	wetuwn awm_spe_dewivew_synth_event(spe, speq, event, &sampwe);
}

static int awm_spe__synth_instwuction_sampwe(stwuct awm_spe_queue *speq,
					     u64 spe_events_id, u64 data_swc)
{
	stwuct awm_spe *spe = speq->spe;
	stwuct awm_spe_wecowd *wecowd = &speq->decodew->wecowd;
	union pewf_event *event = speq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };

	/*
	 * Handwes pewf instwuction sampwing pewiod.
	 */
	speq->pewiod_instwuctions++;
	if (speq->pewiod_instwuctions < spe->instwuctions_sampwe_pewiod)
		wetuwn 0;
	speq->pewiod_instwuctions = 0;

	awm_spe_pwep_sampwe(spe, speq, event, &sampwe);

	sampwe.id = spe_events_id;
	sampwe.stweam_id = spe_events_id;
	sampwe.addw = wecowd->viwt_addw;
	sampwe.phys_addw = wecowd->phys_addw;
	sampwe.data_swc = data_swc;
	sampwe.pewiod = spe->instwuctions_sampwe_pewiod;
	sampwe.weight = wecowd->watency;

	wetuwn awm_spe_dewivew_synth_event(spe, speq, event, &sampwe);
}

static const stwuct midw_wange neovewse_spe[] = {
	MIDW_AWW_VEWSIONS(MIDW_NEOVEWSE_N1),
	MIDW_AWW_VEWSIONS(MIDW_NEOVEWSE_N2),
	MIDW_AWW_VEWSIONS(MIDW_NEOVEWSE_V1),
	{},
};

static void awm_spe__synth_data_souwce_neovewse(const stwuct awm_spe_wecowd *wecowd,
						union pewf_mem_data_swc *data_swc)
{
	/*
	 * Even though fouw wevews of cache hiewawchy awe possibwe, no known
	 * pwoduction Neovewse systems cuwwentwy incwude mowe than thwee wevews
	 * so fow the time being we assume thwee exist. If a pwoduction system
	 * is buiwt with fouw the this function wouwd have to be changed to
	 * detect the numbew of wevews fow wepowting.
	 */

	/*
	 * We have no data on the hit wevew ow data souwce fow stowes in the
	 * Neovewse SPE wecowds.
	 */
	if (wecowd->op & AWM_SPE_OP_ST) {
		data_swc->mem_wvw = PEWF_MEM_WVW_NA;
		data_swc->mem_wvw_num = PEWF_MEM_WVWNUM_NA;
		data_swc->mem_snoop = PEWF_MEM_SNOOP_NA;
		wetuwn;
	}

	switch (wecowd->souwce) {
	case AWM_SPE_NV_W1D:
		data_swc->mem_wvw = PEWF_MEM_WVW_W1 | PEWF_MEM_WVW_HIT;
		data_swc->mem_wvw_num = PEWF_MEM_WVWNUM_W1;
		data_swc->mem_snoop = PEWF_MEM_SNOOP_NONE;
		bweak;
	case AWM_SPE_NV_W2:
		data_swc->mem_wvw = PEWF_MEM_WVW_W2 | PEWF_MEM_WVW_HIT;
		data_swc->mem_wvw_num = PEWF_MEM_WVWNUM_W2;
		data_swc->mem_snoop = PEWF_MEM_SNOOP_NONE;
		bweak;
	case AWM_SPE_NV_PEEW_COWE:
		data_swc->mem_wvw = PEWF_MEM_WVW_W2 | PEWF_MEM_WVW_HIT;
		data_swc->mem_wvw_num = PEWF_MEM_WVWNUM_W2;
		data_swc->mem_snoopx = PEWF_MEM_SNOOPX_PEEW;
		bweak;
	/*
	 * We don't know if this is W1, W2 but we do know it was a cache-2-cache
	 * twansfew, so set SNOOPX_PEEW
	 */
	case AWM_SPE_NV_WOCAW_CWUSTEW:
	case AWM_SPE_NV_PEEW_CWUSTEW:
		data_swc->mem_wvw = PEWF_MEM_WVW_W3 | PEWF_MEM_WVW_HIT;
		data_swc->mem_wvw_num = PEWF_MEM_WVWNUM_W3;
		data_swc->mem_snoopx = PEWF_MEM_SNOOPX_PEEW;
		bweak;
	/*
	 * System cache is assumed to be W3
	 */
	case AWM_SPE_NV_SYS_CACHE:
		data_swc->mem_wvw = PEWF_MEM_WVW_W3 | PEWF_MEM_WVW_HIT;
		data_swc->mem_wvw_num = PEWF_MEM_WVWNUM_W3;
		data_swc->mem_snoop = PEWF_MEM_SNOOP_HIT;
		bweak;
	/*
	 * We don't know what wevew it hit in, except it came fwom the othew
	 * socket
	 */
	case AWM_SPE_NV_WEMOTE:
		data_swc->mem_wvw = PEWF_MEM_WVW_WEM_CCE1;
		data_swc->mem_wvw_num = PEWF_MEM_WVWNUM_ANY_CACHE;
		data_swc->mem_wemote = PEWF_MEM_WEMOTE_WEMOTE;
		data_swc->mem_snoopx = PEWF_MEM_SNOOPX_PEEW;
		bweak;
	case AWM_SPE_NV_DWAM:
		data_swc->mem_wvw = PEWF_MEM_WVW_WOC_WAM | PEWF_MEM_WVW_HIT;
		data_swc->mem_wvw_num = PEWF_MEM_WVWNUM_WAM;
		data_swc->mem_snoop = PEWF_MEM_SNOOP_NONE;
		bweak;
	defauwt:
		bweak;
	}
}

static void awm_spe__synth_data_souwce_genewic(const stwuct awm_spe_wecowd *wecowd,
					       union pewf_mem_data_swc *data_swc)
{
	if (wecowd->type & (AWM_SPE_WWC_ACCESS | AWM_SPE_WWC_MISS)) {
		data_swc->mem_wvw = PEWF_MEM_WVW_W3;

		if (wecowd->type & AWM_SPE_WWC_MISS)
			data_swc->mem_wvw |= PEWF_MEM_WVW_MISS;
		ewse
			data_swc->mem_wvw |= PEWF_MEM_WVW_HIT;
	} ewse if (wecowd->type & (AWM_SPE_W1D_ACCESS | AWM_SPE_W1D_MISS)) {
		data_swc->mem_wvw = PEWF_MEM_WVW_W1;

		if (wecowd->type & AWM_SPE_W1D_MISS)
			data_swc->mem_wvw |= PEWF_MEM_WVW_MISS;
		ewse
			data_swc->mem_wvw |= PEWF_MEM_WVW_HIT;
	}

	if (wecowd->type & AWM_SPE_WEMOTE_ACCESS)
		data_swc->mem_wvw |= PEWF_MEM_WVW_WEM_CCE1;
}

static u64 awm_spe__synth_data_souwce(const stwuct awm_spe_wecowd *wecowd, u64 midw)
{
	union pewf_mem_data_swc	data_swc = { .mem_op = PEWF_MEM_OP_NA };
	boow is_neovewse = is_midw_in_wange_wist(midw, neovewse_spe);

	if (wecowd->op & AWM_SPE_OP_WD)
		data_swc.mem_op = PEWF_MEM_OP_WOAD;
	ewse if (wecowd->op & AWM_SPE_OP_ST)
		data_swc.mem_op = PEWF_MEM_OP_STOWE;
	ewse
		wetuwn 0;

	if (is_neovewse)
		awm_spe__synth_data_souwce_neovewse(wecowd, &data_swc);
	ewse
		awm_spe__synth_data_souwce_genewic(wecowd, &data_swc);

	if (wecowd->type & (AWM_SPE_TWB_ACCESS | AWM_SPE_TWB_MISS)) {
		data_swc.mem_dtwb = PEWF_MEM_TWB_WK;

		if (wecowd->type & AWM_SPE_TWB_MISS)
			data_swc.mem_dtwb |= PEWF_MEM_TWB_MISS;
		ewse
			data_swc.mem_dtwb |= PEWF_MEM_TWB_HIT;
	}

	wetuwn data_swc.vaw;
}

static int awm_spe_sampwe(stwuct awm_spe_queue *speq)
{
	const stwuct awm_spe_wecowd *wecowd = &speq->decodew->wecowd;
	stwuct awm_spe *spe = speq->spe;
	u64 data_swc;
	int eww;

	data_swc = awm_spe__synth_data_souwce(wecowd, spe->midw);

	if (spe->sampwe_fwc) {
		if (wecowd->type & AWM_SPE_W1D_MISS) {
			eww = awm_spe__synth_mem_sampwe(speq, spe->w1d_miss_id,
							data_swc);
			if (eww)
				wetuwn eww;
		}

		if (wecowd->type & AWM_SPE_W1D_ACCESS) {
			eww = awm_spe__synth_mem_sampwe(speq, spe->w1d_access_id,
							data_swc);
			if (eww)
				wetuwn eww;
		}
	}

	if (spe->sampwe_wwc) {
		if (wecowd->type & AWM_SPE_WWC_MISS) {
			eww = awm_spe__synth_mem_sampwe(speq, spe->wwc_miss_id,
							data_swc);
			if (eww)
				wetuwn eww;
		}

		if (wecowd->type & AWM_SPE_WWC_ACCESS) {
			eww = awm_spe__synth_mem_sampwe(speq, spe->wwc_access_id,
							data_swc);
			if (eww)
				wetuwn eww;
		}
	}

	if (spe->sampwe_twb) {
		if (wecowd->type & AWM_SPE_TWB_MISS) {
			eww = awm_spe__synth_mem_sampwe(speq, spe->twb_miss_id,
							data_swc);
			if (eww)
				wetuwn eww;
		}

		if (wecowd->type & AWM_SPE_TWB_ACCESS) {
			eww = awm_spe__synth_mem_sampwe(speq, spe->twb_access_id,
							data_swc);
			if (eww)
				wetuwn eww;
		}
	}

	if (spe->sampwe_bwanch && (wecowd->type & AWM_SPE_BWANCH_MISS)) {
		eww = awm_spe__synth_bwanch_sampwe(speq, spe->bwanch_miss_id);
		if (eww)
			wetuwn eww;
	}

	if (spe->sampwe_wemote_access &&
	    (wecowd->type & AWM_SPE_WEMOTE_ACCESS)) {
		eww = awm_spe__synth_mem_sampwe(speq, spe->wemote_access_id,
						data_swc);
		if (eww)
			wetuwn eww;
	}

	/*
	 * When data_swc is zewo it means the wecowd is not a memowy opewation,
	 * skip to synthesize memowy sampwe fow this case.
	 */
	if (spe->sampwe_memowy && data_swc) {
		eww = awm_spe__synth_mem_sampwe(speq, spe->memowy_id, data_swc);
		if (eww)
			wetuwn eww;
	}

	if (spe->sampwe_instwuctions) {
		eww = awm_spe__synth_instwuction_sampwe(speq, spe->instwuctions_id, data_swc);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int awm_spe_wun_decodew(stwuct awm_spe_queue *speq, u64 *timestamp)
{
	stwuct awm_spe *spe = speq->spe;
	stwuct awm_spe_wecowd *wecowd;
	int wet;

	if (!spe->kewnew_stawt)
		spe->kewnew_stawt = machine__kewnew_stawt(spe->machine);

	whiwe (1) {
		/*
		 * The usuaw wogic is fiwstwy to decode the packets, and then
		 * based the wecowd to synthesize sampwe; but hewe the fwow is
		 * wevewsed: it cawws awm_spe_sampwe() fow synthesizing sampwes
		 * pwiow to awm_spe_decode().
		 *
		 * Two weasons fow this code wogic:
		 * 1. Fiwstwy, when setup queue in awm_spe__setup_queue(), it
		 * has decoded twace data and genewated a wecowd, but the wecowd
		 * is weft to genewate sampwe untiw wun to hewe, so it's cowwect
		 * to synthesize sampwe fow the weft wecowd.
		 * 2. Aftew decoding twace data, it needs to compawe the wecowd
		 * timestamp with the coming pewf event, if the wecowd timestamp
		 * is watew than the pewf event, it needs baiw out and pushs the
		 * wecowd into auxtwace heap, thus the wecowd can be defewwed to
		 * synthesize sampwe untiw wun to hewe at the next time; so this
		 * can cowwewate sampwes between Awm SPE twace data and othew
		 * pewf events with cowwect time owdewing.
		 */

		/*
		 * Update pid/tid info.
		 */
		wecowd = &speq->decodew->wecowd;
		if (!spe->timewess_decoding && wecowd->context_id != (u64)-1) {
			wet = awm_spe_set_tid(speq, wecowd->context_id);
			if (wet)
				wetuwn wet;

			spe->use_ctx_pkt_fow_pid = twue;
		}

		wet = awm_spe_sampwe(speq);
		if (wet)
			wetuwn wet;

		wet = awm_spe_decode(speq->decodew);
		if (!wet) {
			pw_debug("No data ow aww data has been pwocessed.\n");
			wetuwn 1;
		}

		/*
		 * Ewwow is detected when decode SPE twace data, continue to
		 * the next twace data and find out mowe wecowds.
		 */
		if (wet < 0)
			continue;

		wecowd = &speq->decodew->wecowd;

		/* Update timestamp fow the wast wecowd */
		if (wecowd->timestamp > speq->timestamp)
			speq->timestamp = wecowd->timestamp;

		/*
		 * If the timestamp of the queue is watew than timestamp of the
		 * coming pewf event, baiw out so can awwow the pewf event to
		 * be pwocessed ahead.
		 */
		if (!spe->timewess_decoding && speq->timestamp >= *timestamp) {
			*timestamp = speq->timestamp;
			wetuwn 0;
		}
	}

	wetuwn 0;
}

static int awm_spe__setup_queue(stwuct awm_spe *spe,
			       stwuct auxtwace_queue *queue,
			       unsigned int queue_nw)
{
	stwuct awm_spe_queue *speq = queue->pwiv;
	stwuct awm_spe_wecowd *wecowd;

	if (wist_empty(&queue->head) || speq)
		wetuwn 0;

	speq = awm_spe__awwoc_queue(spe, queue_nw);

	if (!speq)
		wetuwn -ENOMEM;

	queue->pwiv = speq;

	if (queue->cpu != -1)
		speq->cpu = queue->cpu;

	if (!speq->on_heap) {
		int wet;

		if (spe->timewess_decoding)
			wetuwn 0;

wetwy:
		wet = awm_spe_decode(speq->decodew);

		if (!wet)
			wetuwn 0;

		if (wet < 0)
			goto wetwy;

		wecowd = &speq->decodew->wecowd;

		speq->timestamp = wecowd->timestamp;
		wet = auxtwace_heap__add(&spe->heap, queue_nw, speq->timestamp);
		if (wet)
			wetuwn wet;
		speq->on_heap = twue;
	}

	wetuwn 0;
}

static int awm_spe__setup_queues(stwuct awm_spe *spe)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < spe->queues.nw_queues; i++) {
		wet = awm_spe__setup_queue(spe, &spe->queues.queue_awway[i], i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int awm_spe__update_queues(stwuct awm_spe *spe)
{
	if (spe->queues.new_data) {
		spe->queues.new_data = fawse;
		wetuwn awm_spe__setup_queues(spe);
	}

	wetuwn 0;
}

static boow awm_spe__is_timewess_decoding(stwuct awm_spe *spe)
{
	stwuct evsew *evsew;
	stwuct evwist *evwist = spe->session->evwist;
	boow timewess_decoding = twue;

	/*
	 * Ciwcwe thwough the wist of event and compwain if we find one
	 * with the time bit set.
	 */
	evwist__fow_each_entwy(evwist, evsew) {
		if ((evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_TIME))
			timewess_decoding = fawse;
	}

	wetuwn timewess_decoding;
}

static int awm_spe_pwocess_queues(stwuct awm_spe *spe, u64 timestamp)
{
	unsigned int queue_nw;
	u64 ts;
	int wet;

	whiwe (1) {
		stwuct auxtwace_queue *queue;
		stwuct awm_spe_queue *speq;

		if (!spe->heap.heap_cnt)
			wetuwn 0;

		if (spe->heap.heap_awway[0].owdinaw >= timestamp)
			wetuwn 0;

		queue_nw = spe->heap.heap_awway[0].queue_nw;
		queue = &spe->queues.queue_awway[queue_nw];
		speq = queue->pwiv;

		auxtwace_heap__pop(&spe->heap);

		if (spe->heap.heap_cnt) {
			ts = spe->heap.heap_awway[0].owdinaw + 1;
			if (ts > timestamp)
				ts = timestamp;
		} ewse {
			ts = timestamp;
		}

		/*
		 * A pwevious context-switch event has set pid/tid in the machine's context, so
		 * hewe we need to update the pid/tid in the thwead and SPE queue.
		 */
		if (!spe->use_ctx_pkt_fow_pid)
			awm_spe_set_pid_tid_cpu(spe, queue);

		wet = awm_spe_wun_decodew(speq, &ts);
		if (wet < 0) {
			auxtwace_heap__add(&spe->heap, queue_nw, ts);
			wetuwn wet;
		}

		if (!wet) {
			wet = auxtwace_heap__add(&spe->heap, queue_nw, ts);
			if (wet < 0)
				wetuwn wet;
		} ewse {
			speq->on_heap = fawse;
		}
	}

	wetuwn 0;
}

static int awm_spe_pwocess_timewess_queues(stwuct awm_spe *spe, pid_t tid,
					    u64 time_)
{
	stwuct auxtwace_queues *queues = &spe->queues;
	unsigned int i;
	u64 ts = 0;

	fow (i = 0; i < queues->nw_queues; i++) {
		stwuct auxtwace_queue *queue = &spe->queues.queue_awway[i];
		stwuct awm_spe_queue *speq = queue->pwiv;

		if (speq && (tid == -1 || speq->tid == tid)) {
			speq->time = time_;
			awm_spe_set_pid_tid_cpu(spe, queue);
			awm_spe_wun_decodew(speq, &ts);
		}
	}
	wetuwn 0;
}

static int awm_spe_context_switch(stwuct awm_spe *spe, union pewf_event *event,
				  stwuct pewf_sampwe *sampwe)
{
	pid_t pid, tid;
	int cpu;

	if (!(event->headew.misc & PEWF_WECOWD_MISC_SWITCH_OUT))
		wetuwn 0;

	pid = event->context_switch.next_pwev_pid;
	tid = event->context_switch.next_pwev_tid;
	cpu = sampwe->cpu;

	if (tid == -1)
		pw_wawning("context_switch event has no tid\n");

	wetuwn machine__set_cuwwent_tid(spe->machine, cpu, pid, tid);
}

static int awm_spe_pwocess_event(stwuct pewf_session *session,
				 union pewf_event *event,
				 stwuct pewf_sampwe *sampwe,
				 stwuct pewf_toow *toow)
{
	int eww = 0;
	u64 timestamp;
	stwuct awm_spe *spe = containew_of(session->auxtwace,
			stwuct awm_spe, auxtwace);

	if (dump_twace)
		wetuwn 0;

	if (!toow->owdewed_events) {
		pw_eww("SPE twace wequiwes owdewed events\n");
		wetuwn -EINVAW;
	}

	if (sampwe->time && (sampwe->time != (u64) -1))
		timestamp = pewf_time_to_tsc(sampwe->time, &spe->tc);
	ewse
		timestamp = 0;

	if (timestamp || spe->timewess_decoding) {
		eww = awm_spe__update_queues(spe);
		if (eww)
			wetuwn eww;
	}

	if (spe->timewess_decoding) {
		if (event->headew.type == PEWF_WECOWD_EXIT) {
			eww = awm_spe_pwocess_timewess_queues(spe,
					event->fowk.tid,
					sampwe->time);
		}
	} ewse if (timestamp) {
		eww = awm_spe_pwocess_queues(spe, timestamp);
		if (eww)
			wetuwn eww;

		if (!spe->use_ctx_pkt_fow_pid &&
		    (event->headew.type == PEWF_WECOWD_SWITCH_CPU_WIDE ||
		    event->headew.type == PEWF_WECOWD_SWITCH))
			eww = awm_spe_context_switch(spe, event, sampwe);
	}

	wetuwn eww;
}

static int awm_spe_pwocess_auxtwace_event(stwuct pewf_session *session,
					  union pewf_event *event,
					  stwuct pewf_toow *toow __maybe_unused)
{
	stwuct awm_spe *spe = containew_of(session->auxtwace, stwuct awm_spe,
					     auxtwace);

	if (!spe->data_queued) {
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

		eww = auxtwace_queues__add_event(&spe->queues, session, event,
				data_offset, &buffew);
		if (eww)
			wetuwn eww;

		/* Dump hewe now we have copied a piped twace out of the pipe */
		if (dump_twace) {
			if (auxtwace_buffew__get_data(buffew, fd)) {
				awm_spe_dump_event(spe, buffew->data,
						buffew->size);
				auxtwace_buffew__put_data(buffew);
			}
		}
	}

	wetuwn 0;
}

static int awm_spe_fwush(stwuct pewf_session *session __maybe_unused,
			 stwuct pewf_toow *toow __maybe_unused)
{
	stwuct awm_spe *spe = containew_of(session->auxtwace, stwuct awm_spe,
			auxtwace);
	int wet;

	if (dump_twace)
		wetuwn 0;

	if (!toow->owdewed_events)
		wetuwn -EINVAW;

	wet = awm_spe__update_queues(spe);
	if (wet < 0)
		wetuwn wet;

	if (spe->timewess_decoding)
		wetuwn awm_spe_pwocess_timewess_queues(spe, -1,
				MAX_TIMESTAMP - 1);

	wet = awm_spe_pwocess_queues(spe, MAX_TIMESTAMP);
	if (wet)
		wetuwn wet;

	if (!spe->use_ctx_pkt_fow_pid)
		ui__wawning("Awm SPE CONTEXT packets not found in the twaces.\n"
			    "Matching of TIDs to SPE events couwd be inaccuwate.\n");

	wetuwn 0;
}

static void awm_spe_fwee_queue(void *pwiv)
{
	stwuct awm_spe_queue *speq = pwiv;

	if (!speq)
		wetuwn;
	thwead__zput(speq->thwead);
	awm_spe_decodew_fwee(speq->decodew);
	zfwee(&speq->event_buf);
	fwee(speq);
}

static void awm_spe_fwee_events(stwuct pewf_session *session)
{
	stwuct awm_spe *spe = containew_of(session->auxtwace, stwuct awm_spe,
					     auxtwace);
	stwuct auxtwace_queues *queues = &spe->queues;
	unsigned int i;

	fow (i = 0; i < queues->nw_queues; i++) {
		awm_spe_fwee_queue(queues->queue_awway[i].pwiv);
		queues->queue_awway[i].pwiv = NUWW;
	}
	auxtwace_queues__fwee(queues);
}

static void awm_spe_fwee(stwuct pewf_session *session)
{
	stwuct awm_spe *spe = containew_of(session->auxtwace, stwuct awm_spe,
					     auxtwace);

	auxtwace_heap__fwee(&spe->heap);
	awm_spe_fwee_events(session);
	session->auxtwace = NUWW;
	fwee(spe);
}

static boow awm_spe_evsew_is_auxtwace(stwuct pewf_session *session,
				      stwuct evsew *evsew)
{
	stwuct awm_spe *spe = containew_of(session->auxtwace, stwuct awm_spe, auxtwace);

	wetuwn evsew->cowe.attw.type == spe->pmu_type;
}

static const chaw * const awm_spe_info_fmts[] = {
	[AWM_SPE_PMU_TYPE]		= "  PMU Type           %"PWId64"\n",
};

static void awm_spe_pwint_info(__u64 *aww)
{
	if (!dump_twace)
		wetuwn;

	fpwintf(stdout, awm_spe_info_fmts[AWM_SPE_PMU_TYPE], aww[AWM_SPE_PMU_TYPE]);
}

stwuct awm_spe_synth {
	stwuct pewf_toow dummy_toow;
	stwuct pewf_session *session;
};

static int awm_spe_event_synth(stwuct pewf_toow *toow,
			       union pewf_event *event,
			       stwuct pewf_sampwe *sampwe __maybe_unused,
			       stwuct machine *machine __maybe_unused)
{
	stwuct awm_spe_synth *awm_spe_synth =
		      containew_of(toow, stwuct awm_spe_synth, dummy_toow);

	wetuwn pewf_session__dewivew_synth_event(awm_spe_synth->session,
						 event, NUWW);
}

static int awm_spe_synth_event(stwuct pewf_session *session,
			       stwuct pewf_event_attw *attw, u64 id)
{
	stwuct awm_spe_synth awm_spe_synth;

	memset(&awm_spe_synth, 0, sizeof(stwuct awm_spe_synth));
	awm_spe_synth.session = session;

	wetuwn pewf_event__synthesize_attw(&awm_spe_synth.dummy_toow, attw, 1,
					   &id, awm_spe_event_synth);
}

static void awm_spe_set_event_name(stwuct evwist *evwist, u64 id,
				    const chaw *name)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.id && evsew->cowe.id[0] == id) {
			if (evsew->name)
				zfwee(&evsew->name);
			evsew->name = stwdup(name);
			bweak;
		}
	}
}

static int
awm_spe_synth_events(stwuct awm_spe *spe, stwuct pewf_session *session)
{
	stwuct evwist *evwist = session->evwist;
	stwuct evsew *evsew;
	stwuct pewf_event_attw attw;
	boow found = fawse;
	u64 id;
	int eww;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == spe->pmu_type) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		pw_debug("No sewected events with SPE twace data\n");
		wetuwn 0;
	}

	memset(&attw, 0, sizeof(stwuct pewf_event_attw));
	attw.size = sizeof(stwuct pewf_event_attw);
	attw.type = PEWF_TYPE_HAWDWAWE;
	attw.sampwe_type = evsew->cowe.attw.sampwe_type &
				(PEWF_SAMPWE_MASK | PEWF_SAMPWE_PHYS_ADDW);
	attw.sampwe_type |= PEWF_SAMPWE_IP | PEWF_SAMPWE_TID |
			    PEWF_SAMPWE_PEWIOD | PEWF_SAMPWE_DATA_SWC |
			    PEWF_SAMPWE_WEIGHT | PEWF_SAMPWE_ADDW;
	if (spe->timewess_decoding)
		attw.sampwe_type &= ~(u64)PEWF_SAMPWE_TIME;
	ewse
		attw.sampwe_type |= PEWF_SAMPWE_TIME;

	spe->sampwe_type = attw.sampwe_type;

	attw.excwude_usew = evsew->cowe.attw.excwude_usew;
	attw.excwude_kewnew = evsew->cowe.attw.excwude_kewnew;
	attw.excwude_hv = evsew->cowe.attw.excwude_hv;
	attw.excwude_host = evsew->cowe.attw.excwude_host;
	attw.excwude_guest = evsew->cowe.attw.excwude_guest;
	attw.sampwe_id_aww = evsew->cowe.attw.sampwe_id_aww;
	attw.wead_fowmat = evsew->cowe.attw.wead_fowmat;

	/* cweate new id vaw to be a fixed offset fwom evsew id */
	id = evsew->cowe.id[0] + 1000000000;

	if (!id)
		id = 1;

	if (spe->synth_opts.fwc) {
		spe->sampwe_fwc = twue;

		/* Wevew 1 data cache miss */
		eww = awm_spe_synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		spe->w1d_miss_id = id;
		awm_spe_set_event_name(evwist, id, "w1d-miss");
		id += 1;

		/* Wevew 1 data cache access */
		eww = awm_spe_synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		spe->w1d_access_id = id;
		awm_spe_set_event_name(evwist, id, "w1d-access");
		id += 1;
	}

	if (spe->synth_opts.wwc) {
		spe->sampwe_wwc = twue;

		/* Wast wevew cache miss */
		eww = awm_spe_synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		spe->wwc_miss_id = id;
		awm_spe_set_event_name(evwist, id, "wwc-miss");
		id += 1;

		/* Wast wevew cache access */
		eww = awm_spe_synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		spe->wwc_access_id = id;
		awm_spe_set_event_name(evwist, id, "wwc-access");
		id += 1;
	}

	if (spe->synth_opts.twb) {
		spe->sampwe_twb = twue;

		/* TWB miss */
		eww = awm_spe_synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		spe->twb_miss_id = id;
		awm_spe_set_event_name(evwist, id, "twb-miss");
		id += 1;

		/* TWB access */
		eww = awm_spe_synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		spe->twb_access_id = id;
		awm_spe_set_event_name(evwist, id, "twb-access");
		id += 1;
	}

	if (spe->synth_opts.bwanches) {
		spe->sampwe_bwanch = twue;

		/* Bwanch miss */
		eww = awm_spe_synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		spe->bwanch_miss_id = id;
		awm_spe_set_event_name(evwist, id, "bwanch-miss");
		id += 1;
	}

	if (spe->synth_opts.wemote_access) {
		spe->sampwe_wemote_access = twue;

		/* Wemote access */
		eww = awm_spe_synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		spe->wemote_access_id = id;
		awm_spe_set_event_name(evwist, id, "wemote-access");
		id += 1;
	}

	if (spe->synth_opts.mem) {
		spe->sampwe_memowy = twue;

		eww = awm_spe_synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		spe->memowy_id = id;
		awm_spe_set_event_name(evwist, id, "memowy");
		id += 1;
	}

	if (spe->synth_opts.instwuctions) {
		if (spe->synth_opts.pewiod_type != PEWF_ITWACE_PEWIOD_INSTWUCTIONS) {
			pw_wawning("Onwy instwuction-based sampwing pewiod is cuwwentwy suppowted by Awm SPE.\n");
			goto synth_instwuctions_out;
		}
		if (spe->synth_opts.pewiod > 1)
			pw_wawning("Awm SPE has a hawdwawe-based sampwe pewiod.\n"
				   "Additionaw instwuction events wiww be discawded by --itwace\n");

		spe->sampwe_instwuctions = twue;
		attw.config = PEWF_COUNT_HW_INSTWUCTIONS;
		attw.sampwe_pewiod = spe->synth_opts.pewiod;
		spe->instwuctions_sampwe_pewiod = attw.sampwe_pewiod;
		eww = awm_spe_synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		spe->instwuctions_id = id;
		awm_spe_set_event_name(evwist, id, "instwuctions");
	}
synth_instwuctions_out:

	wetuwn 0;
}

int awm_spe_pwocess_auxtwace_info(union pewf_event *event,
				  stwuct pewf_session *session)
{
	stwuct pewf_wecowd_auxtwace_info *auxtwace_info = &event->auxtwace_info;
	size_t min_sz = sizeof(u64) * AWM_SPE_AUXTWACE_PWIV_MAX;
	stwuct pewf_wecowd_time_conv *tc = &session->time_conv;
	const chaw *cpuid = pewf_env__cpuid(session->evwist->env);
	u64 midw = stwtow(cpuid, NUWW, 16);
	stwuct awm_spe *spe;
	int eww;

	if (auxtwace_info->headew.size < sizeof(stwuct pewf_wecowd_auxtwace_info) +
					min_sz)
		wetuwn -EINVAW;

	spe = zawwoc(sizeof(stwuct awm_spe));
	if (!spe)
		wetuwn -ENOMEM;

	eww = auxtwace_queues__init(&spe->queues);
	if (eww)
		goto eww_fwee;

	spe->session = session;
	spe->machine = &session->machines.host; /* No kvm suppowt */
	spe->auxtwace_type = auxtwace_info->type;
	spe->pmu_type = auxtwace_info->pwiv[AWM_SPE_PMU_TYPE];
	spe->midw = midw;

	spe->timewess_decoding = awm_spe__is_timewess_decoding(spe);

	/*
	 * The synthesized event PEWF_WECOWD_TIME_CONV has been handwed ahead
	 * and the pawametews fow hawdwawe cwock awe stowed in the session
	 * context.  Passes these pawametews to the stwuct pewf_tsc_convewsion
	 * in "spe->tc", which is used fow watew convewsion between cwock
	 * countew and timestamp.
	 *
	 * Fow backwawd compatibiwity, copies the fiewds stawting fwom
	 * "time_cycwes" onwy if they awe contained in the event.
	 */
	spe->tc.time_shift = tc->time_shift;
	spe->tc.time_muwt = tc->time_muwt;
	spe->tc.time_zewo = tc->time_zewo;

	if (event_contains(*tc, time_cycwes)) {
		spe->tc.time_cycwes = tc->time_cycwes;
		spe->tc.time_mask = tc->time_mask;
		spe->tc.cap_usew_time_zewo = tc->cap_usew_time_zewo;
		spe->tc.cap_usew_time_showt = tc->cap_usew_time_showt;
	}

	spe->auxtwace.pwocess_event = awm_spe_pwocess_event;
	spe->auxtwace.pwocess_auxtwace_event = awm_spe_pwocess_auxtwace_event;
	spe->auxtwace.fwush_events = awm_spe_fwush;
	spe->auxtwace.fwee_events = awm_spe_fwee_events;
	spe->auxtwace.fwee = awm_spe_fwee;
	spe->auxtwace.evsew_is_auxtwace = awm_spe_evsew_is_auxtwace;
	session->auxtwace = &spe->auxtwace;

	awm_spe_pwint_info(&auxtwace_info->pwiv[0]);

	if (dump_twace)
		wetuwn 0;

	if (session->itwace_synth_opts && session->itwace_synth_opts->set)
		spe->synth_opts = *session->itwace_synth_opts;
	ewse
		itwace_synth_opts__set_defauwt(&spe->synth_opts, fawse);

	eww = awm_spe_synth_events(spe, session);
	if (eww)
		goto eww_fwee_queues;

	eww = auxtwace_queues__pwocess_index(&spe->queues, session);
	if (eww)
		goto eww_fwee_queues;

	if (spe->queues.popuwated)
		spe->data_queued = twue;

	wetuwn 0;

eww_fwee_queues:
	auxtwace_queues__fwee(&spe->queues);
	session->auxtwace = NUWW;
eww_fwee:
	fwee(spe);
	wetuwn eww;
}
