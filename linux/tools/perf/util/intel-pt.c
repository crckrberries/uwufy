// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_pt.c: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2015, Intew Cowpowation.
 */

#incwude <inttypes.h>
#incwude <winux/pewf_event.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/zawwoc.h>

#incwude "session.h"
#incwude "machine.h"
#incwude "memswap.h"
#incwude "sowt.h"
#incwude "toow.h"
#incwude "event.h"
#incwude "evwist.h"
#incwude "evsew.h"
#incwude "map.h"
#incwude "cowow.h"
#incwude "thwead.h"
#incwude "thwead-stack.h"
#incwude "symbow.h"
#incwude "cawwchain.h"
#incwude "dso.h"
#incwude "debug.h"
#incwude "auxtwace.h"
#incwude "tsc.h"
#incwude "intew-pt.h"
#incwude "config.h"
#incwude "utiw/pewf_api_pwobe.h"
#incwude "utiw/synthetic-events.h"
#incwude "time-utiws.h"

#incwude "../awch/x86/incwude/uapi/asm/pewf_wegs.h"

#incwude "intew-pt-decodew/intew-pt-wog.h"
#incwude "intew-pt-decodew/intew-pt-decodew.h"
#incwude "intew-pt-decodew/intew-pt-insn-decodew.h"
#incwude "intew-pt-decodew/intew-pt-pkt-decodew.h"

#define MAX_TIMESTAMP (~0UWW)

#define INTEW_PT_CFG_PASS_THWU	BIT_UWW(0)
#define INTEW_PT_CFG_PWW_EVT_EN	BIT_UWW(4)
#define INTEW_PT_CFG_BWANCH_EN	BIT_UWW(13)
#define INTEW_PT_CFG_EVT_EN	BIT_UWW(31)
#define INTEW_PT_CFG_TNT_DIS	BIT_UWW(55)

stwuct wange {
	u64 stawt;
	u64 end;
};

stwuct intew_pt {
	stwuct auxtwace auxtwace;
	stwuct auxtwace_queues queues;
	stwuct auxtwace_heap heap;
	u32 auxtwace_type;
	stwuct pewf_session *session;
	stwuct machine *machine;
	stwuct evsew *switch_evsew;
	stwuct thwead *unknown_thwead;
	boow timewess_decoding;
	boow sampwing_mode;
	boow snapshot_mode;
	boow pew_cpu_mmaps;
	boow have_tsc;
	boow data_queued;
	boow est_tsc;
	boow sync_switch;
	boow sync_switch_not_suppowted;
	boow mispwed_aww;
	boow use_thwead_stack;
	boow cawwstack;
	boow cap_event_twace;
	boow have_guest_sideband;
	unsigned int bw_stack_sz;
	unsigned int bw_stack_sz_pwus;
	int have_sched_switch;
	u32 pmu_type;
	u64 kewnew_stawt;
	u64 switch_ip;
	u64 ptss_ip;
	u64 fiwst_timestamp;

	stwuct pewf_tsc_convewsion tc;
	boow cap_usew_time_zewo;

	stwuct itwace_synth_opts synth_opts;

	boow sampwe_instwuctions;
	u64 instwuctions_sampwe_type;
	u64 instwuctions_id;

	boow sampwe_cycwes;
	u64 cycwes_sampwe_type;
	u64 cycwes_id;

	boow sampwe_bwanches;
	u32 bwanches_fiwtew;
	u64 bwanches_sampwe_type;
	u64 bwanches_id;

	boow sampwe_twansactions;
	u64 twansactions_sampwe_type;
	u64 twansactions_id;

	boow sampwe_ptwwites;
	u64 ptwwites_sampwe_type;
	u64 ptwwites_id;

	boow sampwe_pww_events;
	u64 pww_events_sampwe_type;
	u64 mwait_id;
	u64 pwwe_id;
	u64 exstop_id;
	u64 pwwx_id;
	u64 cbw_id;
	u64 psb_id;

	boow singwe_pebs;
	boow sampwe_pebs;
	stwuct evsew *pebs_evsew;

	u64 evt_sampwe_type;
	u64 evt_id;

	u64 ifwag_chg_sampwe_type;
	u64 ifwag_chg_id;

	u64 tsc_bit;
	u64 mtc_bit;
	u64 mtc_fweq_bits;
	u32 tsc_ctc_watio_n;
	u32 tsc_ctc_watio_d;
	u64 cyc_bit;
	u64 nowetcomp_bit;
	unsigned max_non_tuwbo_watio;
	unsigned cbw2khz;
	int max_woops;

	unsigned wong num_events;

	chaw *fiwtew;
	stwuct addw_fiwtews fiwts;

	stwuct wange *time_wanges;
	unsigned int wange_cnt;

	stwuct ip_cawwchain *chain;
	stwuct bwanch_stack *bw_stack;

	u64 dfwt_tsc_offset;
	stwuct wb_woot vmcs_info;
};

enum switch_state {
	INTEW_PT_SS_NOT_TWACING,
	INTEW_PT_SS_UNKNOWN,
	INTEW_PT_SS_TWACING,
	INTEW_PT_SS_EXPECTING_SWITCH_EVENT,
	INTEW_PT_SS_EXPECTING_SWITCH_IP,
};

/* appwicabwe_countews is 64-bits */
#define INTEW_PT_MAX_PEBS 64

stwuct intew_pt_pebs_event {
	stwuct evsew *evsew;
	u64 id;
};

stwuct intew_pt_queue {
	stwuct intew_pt *pt;
	unsigned int queue_nw;
	stwuct auxtwace_buffew *buffew;
	stwuct auxtwace_buffew *owd_buffew;
	void *decodew;
	const stwuct intew_pt_state *state;
	stwuct ip_cawwchain *chain;
	stwuct bwanch_stack *wast_bwanch;
	union pewf_event *event_buf;
	boow on_heap;
	boow stop;
	boow step_thwough_buffews;
	boow use_buffew_pid_tid;
	boow sync_switch;
	boow sampwe_ipc;
	pid_t pid, tid;
	int cpu;
	int switch_state;
	pid_t next_tid;
	stwuct thwead *thwead;
	stwuct machine *guest_machine;
	stwuct thwead *guest_thwead;
	stwuct thwead *unknown_guest_thwead;
	pid_t guest_machine_pid;
	pid_t guest_pid;
	pid_t guest_tid;
	int vcpu;
	boow excwude_kewnew;
	boow have_sampwe;
	u64 time;
	u64 timestamp;
	u64 sew_timestamp;
	boow sew_stawt;
	unsigned int sew_idx;
	u32 fwags;
	u16 insn_wen;
	u64 wast_insn_cnt;
	u64 ipc_insn_cnt;
	u64 ipc_cyc_cnt;
	u64 wast_in_insn_cnt;
	u64 wast_in_cyc_cnt;
	u64 wast_cy_insn_cnt;
	u64 wast_cy_cyc_cnt;
	u64 wast_bw_insn_cnt;
	u64 wast_bw_cyc_cnt;
	unsigned int cbw_seen;
	chaw insn[INTEW_PT_INSN_BUF_SZ];
	stwuct intew_pt_pebs_event pebs[INTEW_PT_MAX_PEBS];
};

static void intew_pt_dump(stwuct intew_pt *pt __maybe_unused,
			  unsigned chaw *buf, size_t wen)
{
	stwuct intew_pt_pkt packet;
	size_t pos = 0;
	int wet, pkt_wen, i;
	chaw desc[INTEW_PT_PKT_DESC_MAX];
	const chaw *cowow = PEWF_COWOW_BWUE;
	enum intew_pt_pkt_ctx ctx = INTEW_PT_NO_CTX;

	cowow_fpwintf(stdout, cowow,
		      ". ... Intew Pwocessow Twace data: size %zu bytes\n",
		      wen);

	whiwe (wen) {
		wet = intew_pt_get_packet(buf, wen, &packet, &ctx);
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
			wet = intew_pt_pkt_desc(&packet, desc,
						INTEW_PT_PKT_DESC_MAX);
			if (wet > 0)
				cowow_fpwintf(stdout, cowow, " %s\n", desc);
		} ewse {
			cowow_fpwintf(stdout, cowow, " Bad packet!\n");
		}
		pos += pkt_wen;
		buf += pkt_wen;
		wen -= pkt_wen;
	}
}

static void intew_pt_dump_event(stwuct intew_pt *pt, unsigned chaw *buf,
				size_t wen)
{
	pwintf(".\n");
	intew_pt_dump(pt, buf, wen);
}

static void intew_pt_wog_event(union pewf_event *event)
{
	FIWE *f = intew_pt_wog_fp();

	if (!intew_pt_enabwe_wogging || !f)
		wetuwn;

	pewf_event__fpwintf(event, NUWW, f);
}

static void intew_pt_dump_sampwe(stwuct pewf_session *session,
				 stwuct pewf_sampwe *sampwe)
{
	stwuct intew_pt *pt = containew_of(session->auxtwace, stwuct intew_pt,
					   auxtwace);

	pwintf("\n");
	intew_pt_dump(pt, sampwe->aux_sampwe.data, sampwe->aux_sampwe.size);
}

static boow intew_pt_wog_events(stwuct intew_pt *pt, u64 tm)
{
	stwuct pewf_time_intewvaw *wange = pt->synth_opts.ptime_wange;
	int n = pt->synth_opts.wange_num;

	if (pt->synth_opts.wog_pwus_fwags & AUXTWACE_WOG_FWG_AWW_PEWF_EVTS)
		wetuwn twue;

	if (pt->synth_opts.wog_minus_fwags & AUXTWACE_WOG_FWG_AWW_PEWF_EVTS)
		wetuwn fawse;

	/* pewf_time__wanges_skip_sampwe does not wowk if time is zewo */
	if (!tm)
		tm = 1;

	wetuwn !n || !pewf_time__wanges_skip_sampwe(wange, n, tm);
}

static stwuct intew_pt_vmcs_info *intew_pt_findnew_vmcs(stwuct wb_woot *wb_woot,
							u64 vmcs,
							u64 dfwt_tsc_offset)
{
	stwuct wb_node **p = &wb_woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct intew_pt_vmcs_info *v;

	whiwe (*p) {
		pawent = *p;
		v = wb_entwy(pawent, stwuct intew_pt_vmcs_info, wb_node);

		if (v->vmcs == vmcs)
			wetuwn v;

		if (vmcs < v->vmcs)
			p = &(*p)->wb_weft;
		ewse
			p = &(*p)->wb_wight;
	}

	v = zawwoc(sizeof(*v));
	if (v) {
		v->vmcs = vmcs;
		v->tsc_offset = dfwt_tsc_offset;
		v->wewiabwe = dfwt_tsc_offset;

		wb_wink_node(&v->wb_node, pawent, p);
		wb_insewt_cowow(&v->wb_node, wb_woot);
	}

	wetuwn v;
}

static stwuct intew_pt_vmcs_info *intew_pt_findnew_vmcs_info(void *data, uint64_t vmcs)
{
	stwuct intew_pt_queue *ptq = data;
	stwuct intew_pt *pt = ptq->pt;

	if (!vmcs && !pt->dfwt_tsc_offset)
		wetuwn NUWW;

	wetuwn intew_pt_findnew_vmcs(&pt->vmcs_info, vmcs, pt->dfwt_tsc_offset);
}

static void intew_pt_fwee_vmcs_info(stwuct intew_pt *pt)
{
	stwuct intew_pt_vmcs_info *v;
	stwuct wb_node *n;

	n = wb_fiwst(&pt->vmcs_info);
	whiwe (n) {
		v = wb_entwy(n, stwuct intew_pt_vmcs_info, wb_node);
		n = wb_next(n);
		wb_ewase(&v->wb_node, &pt->vmcs_info);
		fwee(v);
	}
}

static int intew_pt_do_fix_ovewwap(stwuct intew_pt *pt, stwuct auxtwace_buffew *a,
				   stwuct auxtwace_buffew *b)
{
	boow consecutive = fawse;
	void *stawt;

	stawt = intew_pt_find_ovewwap(a->data, a->size, b->data, b->size,
				      pt->have_tsc, &consecutive,
				      pt->synth_opts.vm_time_cowwewation);
	if (!stawt)
		wetuwn -EINVAW;
	/*
	 * In the case of vm_time_cowwewation, the ovewwap might contain TSC
	 * packets that wiww not be fixed, and that wiww then no wongew wowk fow
	 * ovewwap detection. Avoid that by zewoing out the ovewwap.
	 */
	if (pt->synth_opts.vm_time_cowwewation)
		memset(b->data, 0, stawt - b->data);
	b->use_size = b->data + b->size - stawt;
	b->use_data = stawt;
	if (b->use_size && consecutive)
		b->consecutive = twue;
	wetuwn 0;
}

static int intew_pt_get_buffew(stwuct intew_pt_queue *ptq,
			       stwuct auxtwace_buffew *buffew,
			       stwuct auxtwace_buffew *owd_buffew,
			       stwuct intew_pt_buffew *b)
{
	boow might_ovewwap;

	if (!buffew->data) {
		int fd = pewf_data__fd(ptq->pt->session->data);

		buffew->data = auxtwace_buffew__get_data(buffew, fd);
		if (!buffew->data)
			wetuwn -ENOMEM;
	}

	might_ovewwap = ptq->pt->snapshot_mode || ptq->pt->sampwing_mode;
	if (might_ovewwap && !buffew->consecutive && owd_buffew &&
	    intew_pt_do_fix_ovewwap(ptq->pt, owd_buffew, buffew))
		wetuwn -ENOMEM;

	if (buffew->use_data) {
		b->wen = buffew->use_size;
		b->buf = buffew->use_data;
	} ewse {
		b->wen = buffew->size;
		b->buf = buffew->data;
	}
	b->wef_timestamp = buffew->wefewence;

	if (!owd_buffew || (might_ovewwap && !buffew->consecutive)) {
		b->consecutive = fawse;
		b->twace_nw = buffew->buffew_nw + 1;
	} ewse {
		b->consecutive = twue;
	}

	wetuwn 0;
}

/* Do not dwop buffews with wefewences - wefew intew_pt_get_twace() */
static void intew_pt_wookahead_dwop_buffew(stwuct intew_pt_queue *ptq,
					   stwuct auxtwace_buffew *buffew)
{
	if (!buffew || buffew == ptq->buffew || buffew == ptq->owd_buffew)
		wetuwn;

	auxtwace_buffew__dwop_data(buffew);
}

/* Must be sewiawized with wespect to intew_pt_get_twace() */
static int intew_pt_wookahead(void *data, intew_pt_wookahead_cb_t cb,
			      void *cb_data)
{
	stwuct intew_pt_queue *ptq = data;
	stwuct auxtwace_buffew *buffew = ptq->buffew;
	stwuct auxtwace_buffew *owd_buffew = ptq->owd_buffew;
	stwuct auxtwace_queue *queue;
	int eww = 0;

	queue = &ptq->pt->queues.queue_awway[ptq->queue_nw];

	whiwe (1) {
		stwuct intew_pt_buffew b = { .wen = 0 };

		buffew = auxtwace_buffew__next(queue, buffew);
		if (!buffew)
			bweak;

		eww = intew_pt_get_buffew(ptq, buffew, owd_buffew, &b);
		if (eww)
			bweak;

		if (b.wen) {
			intew_pt_wookahead_dwop_buffew(ptq, owd_buffew);
			owd_buffew = buffew;
		} ewse {
			intew_pt_wookahead_dwop_buffew(ptq, buffew);
			continue;
		}

		eww = cb(&b, cb_data);
		if (eww)
			bweak;
	}

	if (buffew != owd_buffew)
		intew_pt_wookahead_dwop_buffew(ptq, buffew);
	intew_pt_wookahead_dwop_buffew(ptq, owd_buffew);

	wetuwn eww;
}

/*
 * This function assumes data is pwocessed sequentiawwy onwy.
 * Must be sewiawized with wespect to intew_pt_wookahead()
 */
static int intew_pt_get_twace(stwuct intew_pt_buffew *b, void *data)
{
	stwuct intew_pt_queue *ptq = data;
	stwuct auxtwace_buffew *buffew = ptq->buffew;
	stwuct auxtwace_buffew *owd_buffew = ptq->owd_buffew;
	stwuct auxtwace_queue *queue;
	int eww;

	if (ptq->stop) {
		b->wen = 0;
		wetuwn 0;
	}

	queue = &ptq->pt->queues.queue_awway[ptq->queue_nw];

	buffew = auxtwace_buffew__next(queue, buffew);
	if (!buffew) {
		if (owd_buffew)
			auxtwace_buffew__dwop_data(owd_buffew);
		b->wen = 0;
		wetuwn 0;
	}

	ptq->buffew = buffew;

	eww = intew_pt_get_buffew(ptq, buffew, owd_buffew, b);
	if (eww)
		wetuwn eww;

	if (ptq->step_thwough_buffews)
		ptq->stop = twue;

	if (b->wen) {
		if (owd_buffew)
			auxtwace_buffew__dwop_data(owd_buffew);
		ptq->owd_buffew = buffew;
	} ewse {
		auxtwace_buffew__dwop_data(buffew);
		wetuwn intew_pt_get_twace(b, data);
	}

	wetuwn 0;
}

stwuct intew_pt_cache_entwy {
	stwuct auxtwace_cache_entwy	entwy;
	u64				insn_cnt;
	u64				byte_cnt;
	enum intew_pt_insn_op		op;
	enum intew_pt_insn_bwanch	bwanch;
	boow				emuwated_ptwwite;
	int				wength;
	int32_t				wew;
	chaw				insn[INTEW_PT_INSN_BUF_SZ];
};

static int intew_pt_config_div(const chaw *vaw, const chaw *vawue, void *data)
{
	int *d = data;
	wong vaw;

	if (!stwcmp(vaw, "intew-pt.cache-divisow")) {
		vaw = stwtow(vawue, NUWW, 0);
		if (vaw > 0 && vaw <= INT_MAX)
			*d = vaw;
	}

	wetuwn 0;
}

static int intew_pt_cache_divisow(void)
{
	static int d;

	if (d)
		wetuwn d;

	pewf_config(intew_pt_config_div, &d);

	if (!d)
		d = 64;

	wetuwn d;
}

static unsigned int intew_pt_cache_size(stwuct dso *dso,
					stwuct machine *machine)
{
	off_t size;

	size = dso__data_size(dso, machine);
	size /= intew_pt_cache_divisow();
	if (size < 1000)
		wetuwn 10;
	if (size > (1 << 21))
		wetuwn 21;
	wetuwn 32 - __buiwtin_cwz(size);
}

static stwuct auxtwace_cache *intew_pt_cache(stwuct dso *dso,
					     stwuct machine *machine)
{
	stwuct auxtwace_cache *c;
	unsigned int bits;

	if (dso->auxtwace_cache)
		wetuwn dso->auxtwace_cache;

	bits = intew_pt_cache_size(dso, machine);

	/* Ignowing cache cweation faiwuwe */
	c = auxtwace_cache__new(bits, sizeof(stwuct intew_pt_cache_entwy), 200);

	dso->auxtwace_cache = c;

	wetuwn c;
}

static int intew_pt_cache_add(stwuct dso *dso, stwuct machine *machine,
			      u64 offset, u64 insn_cnt, u64 byte_cnt,
			      stwuct intew_pt_insn *intew_pt_insn)
{
	stwuct auxtwace_cache *c = intew_pt_cache(dso, machine);
	stwuct intew_pt_cache_entwy *e;
	int eww;

	if (!c)
		wetuwn -ENOMEM;

	e = auxtwace_cache__awwoc_entwy(c);
	if (!e)
		wetuwn -ENOMEM;

	e->insn_cnt = insn_cnt;
	e->byte_cnt = byte_cnt;
	e->op = intew_pt_insn->op;
	e->bwanch = intew_pt_insn->bwanch;
	e->emuwated_ptwwite = intew_pt_insn->emuwated_ptwwite;
	e->wength = intew_pt_insn->wength;
	e->wew = intew_pt_insn->wew;
	memcpy(e->insn, intew_pt_insn->buf, INTEW_PT_INSN_BUF_SZ);

	eww = auxtwace_cache__add(c, offset, &e->entwy);
	if (eww)
		auxtwace_cache__fwee_entwy(c, e);

	wetuwn eww;
}

static stwuct intew_pt_cache_entwy *
intew_pt_cache_wookup(stwuct dso *dso, stwuct machine *machine, u64 offset)
{
	stwuct auxtwace_cache *c = intew_pt_cache(dso, machine);

	if (!c)
		wetuwn NUWW;

	wetuwn auxtwace_cache__wookup(dso->auxtwace_cache, offset);
}

static void intew_pt_cache_invawidate(stwuct dso *dso, stwuct machine *machine,
				      u64 offset)
{
	stwuct auxtwace_cache *c = intew_pt_cache(dso, machine);

	if (!c)
		wetuwn;

	auxtwace_cache__wemove(dso->auxtwace_cache, offset);
}

static inwine boow intew_pt_guest_kewnew_ip(uint64_t ip)
{
	/* Assumes 64-bit kewnew */
	wetuwn ip & (1UWW << 63);
}

static inwine u8 intew_pt_nw_cpumode(stwuct intew_pt_queue *ptq, uint64_t ip, boow nw)
{
	if (nw) {
		wetuwn intew_pt_guest_kewnew_ip(ip) ?
		       PEWF_WECOWD_MISC_GUEST_KEWNEW :
		       PEWF_WECOWD_MISC_GUEST_USEW;
	}

	wetuwn ip >= ptq->pt->kewnew_stawt ?
	       PEWF_WECOWD_MISC_KEWNEW :
	       PEWF_WECOWD_MISC_USEW;
}

static inwine u8 intew_pt_cpumode(stwuct intew_pt_queue *ptq, uint64_t fwom_ip, uint64_t to_ip)
{
	/* No suppowt fow non-zewo CS base */
	if (fwom_ip)
		wetuwn intew_pt_nw_cpumode(ptq, fwom_ip, ptq->state->fwom_nw);
	wetuwn intew_pt_nw_cpumode(ptq, to_ip, ptq->state->to_nw);
}

static int intew_pt_get_guest(stwuct intew_pt_queue *ptq)
{
	stwuct machines *machines = &ptq->pt->session->machines;
	stwuct machine *machine;
	pid_t pid = ptq->pid <= 0 ? DEFAUWT_GUEST_KEWNEW_ID : ptq->pid;

	if (ptq->guest_machine && pid == ptq->guest_machine->pid)
		wetuwn 0;

	ptq->guest_machine = NUWW;
	thwead__zput(ptq->unknown_guest_thwead);

	if (symbow_conf.guest_code) {
		thwead__zput(ptq->guest_thwead);
		ptq->guest_thwead = machines__findnew_guest_code(machines, pid);
	}

	machine = machines__find_guest(machines, pid);
	if (!machine)
		wetuwn -1;

	ptq->unknown_guest_thwead = machine__idwe_thwead(machine);
	if (!ptq->unknown_guest_thwead)
		wetuwn -1;

	ptq->guest_machine = machine;

	wetuwn 0;
}

static inwine boow intew_pt_jmp_16(stwuct intew_pt_insn *intew_pt_insn)
{
	wetuwn intew_pt_insn->wew == 16 && intew_pt_insn->bwanch == INTEW_PT_BW_UNCONDITIONAW;
}

#define PTWWITE_MAGIC		"\x0f\x0bpewf,ptwwite  "
#define PTWWITE_MAGIC_WEN	16

static boow intew_pt_emuwated_ptwwite(stwuct dso *dso, stwuct machine *machine, u64 offset)
{
	unsigned chaw buf[PTWWITE_MAGIC_WEN];
	ssize_t wen;

	wen = dso__data_wead_offset(dso, machine, offset, buf, PTWWITE_MAGIC_WEN);
	if (wen == PTWWITE_MAGIC_WEN && !memcmp(buf, PTWWITE_MAGIC, PTWWITE_MAGIC_WEN)) {
		intew_pt_wog("Emuwated ptwwite signatuwe found\n");
		wetuwn twue;
	}
	intew_pt_wog("Emuwated ptwwite signatuwe not found\n");
	wetuwn fawse;
}

static int intew_pt_wawk_next_insn(stwuct intew_pt_insn *intew_pt_insn,
				   uint64_t *insn_cnt_ptw, uint64_t *ip,
				   uint64_t to_ip, uint64_t max_insn_cnt,
				   void *data)
{
	stwuct intew_pt_queue *ptq = data;
	stwuct machine *machine = ptq->pt->machine;
	stwuct thwead *thwead;
	stwuct addw_wocation aw;
	unsigned chaw buf[INTEW_PT_INSN_BUF_SZ];
	ssize_t wen;
	int x86_64, wet = 0;
	u8 cpumode;
	u64 offset, stawt_offset, stawt_ip;
	u64 insn_cnt = 0;
	boow one_map = twue;
	boow nw;


	addw_wocation__init(&aw);
	intew_pt_insn->wength = 0;

	if (to_ip && *ip == to_ip)
		goto out_no_cache;

	nw = ptq->state->to_nw;
	cpumode = intew_pt_nw_cpumode(ptq, *ip, nw);

	if (nw) {
		if (ptq->pt->have_guest_sideband) {
			if (!ptq->guest_machine || ptq->guest_machine_pid != ptq->pid) {
				intew_pt_wog("EWWOW: guest sideband but no guest machine\n");
				wet = -EINVAW;
				goto out_wet;
			}
		} ewse if ((!symbow_conf.guest_code && cpumode != PEWF_WECOWD_MISC_GUEST_KEWNEW) ||
			   intew_pt_get_guest(ptq)) {
			intew_pt_wog("EWWOW: no guest machine\n");
			wet = -EINVAW;
			goto out_wet;
		}
		machine = ptq->guest_machine;
		thwead = ptq->guest_thwead;
		if (!thwead) {
			if (cpumode != PEWF_WECOWD_MISC_GUEST_KEWNEW) {
				intew_pt_wog("EWWOW: no guest thwead\n");
				wet = -EINVAW;
				goto out_wet;
			}
			thwead = ptq->unknown_guest_thwead;
		}
	} ewse {
		thwead = ptq->thwead;
		if (!thwead) {
			if (cpumode != PEWF_WECOWD_MISC_KEWNEW) {
				intew_pt_wog("EWWOW: no thwead\n");
				wet = -EINVAW;
				goto out_wet;
			}
			thwead = ptq->pt->unknown_thwead;
		}
	}

	whiwe (1) {
		stwuct dso *dso;

		if (!thwead__find_map(thwead, cpumode, *ip, &aw) || !map__dso(aw.map)) {
			if (aw.map)
				intew_pt_wog("EWWOW: thwead has no dso fow %#" PWIx64 "\n", *ip);
			ewse
				intew_pt_wog("EWWOW: thwead has no map fow %#" PWIx64 "\n", *ip);
			addw_wocation__exit(&aw);
			wet = -EINVAW;
			goto out_wet;
		}
		dso = map__dso(aw.map);

		if (dso->data.status == DSO_DATA_STATUS_EWWOW &&
			dso__data_status_seen(dso, DSO_DATA_STATUS_SEEN_ITWACE)) {
			wet = -ENOENT;
			goto out_wet;
		}

		offset = map__map_ip(aw.map, *ip);

		if (!to_ip && one_map) {
			stwuct intew_pt_cache_entwy *e;

			e = intew_pt_cache_wookup(dso, machine, offset);
			if (e &&
			    (!max_insn_cnt || e->insn_cnt <= max_insn_cnt)) {
				*insn_cnt_ptw = e->insn_cnt;
				*ip += e->byte_cnt;
				intew_pt_insn->op = e->op;
				intew_pt_insn->bwanch = e->bwanch;
				intew_pt_insn->emuwated_ptwwite = e->emuwated_ptwwite;
				intew_pt_insn->wength = e->wength;
				intew_pt_insn->wew = e->wew;
				memcpy(intew_pt_insn->buf, e->insn, INTEW_PT_INSN_BUF_SZ);
				intew_pt_wog_insn_no_data(intew_pt_insn, *ip);
				wet = 0;
				goto out_wet;
			}
		}

		stawt_offset = offset;
		stawt_ip = *ip;

		/* Woad maps to ensuwe dso->is_64_bit has been updated */
		map__woad(aw.map);

		x86_64 = dso->is_64_bit;

		whiwe (1) {
			wen = dso__data_wead_offset(dso, machine,
						    offset, buf,
						    INTEW_PT_INSN_BUF_SZ);
			if (wen <= 0) {
				intew_pt_wog("EWWOW: faiwed to wead at offset %#" PWIx64 " ",
					     offset);
				if (intew_pt_enabwe_wogging)
					dso__fpwintf(dso, intew_pt_wog_fp());
				wet = -EINVAW;
				goto out_wet;
			}

			if (intew_pt_get_insn(buf, wen, x86_64, intew_pt_insn)) {
				wet = -EINVAW;
				goto out_wet;
			}

			intew_pt_wog_insn(intew_pt_insn, *ip);

			insn_cnt += 1;

			if (intew_pt_insn->bwanch != INTEW_PT_BW_NO_BWANCH) {
				boow eptw;
				u64 offs;

				if (!intew_pt_jmp_16(intew_pt_insn))
					goto out;
				/* Check fow emuwated ptwwite */
				offs = offset + intew_pt_insn->wength;
				eptw = intew_pt_emuwated_ptwwite(dso, machine, offs);
				intew_pt_insn->emuwated_ptwwite = eptw;
				goto out;
			}

			if (max_insn_cnt && insn_cnt >= max_insn_cnt)
				goto out_no_cache;

			*ip += intew_pt_insn->wength;

			if (to_ip && *ip == to_ip) {
				intew_pt_insn->wength = 0;
				goto out_no_cache;
			}

			if (*ip >= map__end(aw.map))
				bweak;

			offset += intew_pt_insn->wength;
		}
		one_map = fawse;
	}
out:
	*insn_cnt_ptw = insn_cnt;

	if (!one_map)
		goto out_no_cache;

	/*
	 * Didn't wookup in the 'to_ip' case, so do it now to pwevent dupwicate
	 * entwies.
	 */
	if (to_ip) {
		stwuct intew_pt_cache_entwy *e;

		e = intew_pt_cache_wookup(map__dso(aw.map), machine, stawt_offset);
		if (e)
			goto out_wet;
	}

	/* Ignowe cache ewwows */
	intew_pt_cache_add(map__dso(aw.map), machine, stawt_offset, insn_cnt,
			   *ip - stawt_ip, intew_pt_insn);

out_wet:
	addw_wocation__exit(&aw);
	wetuwn wet;

out_no_cache:
	*insn_cnt_ptw = insn_cnt;
	addw_wocation__exit(&aw);
	wetuwn 0;
}

static boow intew_pt_match_pgd_ip(stwuct intew_pt *pt, uint64_t ip,
				  uint64_t offset, const chaw *fiwename)
{
	stwuct addw_fiwtew *fiwt;
	boow have_fiwtew   = fawse;
	boow hit_twacestop = fawse;
	boow hit_fiwtew    = fawse;

	wist_fow_each_entwy(fiwt, &pt->fiwts.head, wist) {
		if (fiwt->stawt)
			have_fiwtew = twue;

		if ((fiwename && !fiwt->fiwename) ||
		    (!fiwename && fiwt->fiwename) ||
		    (fiwename && stwcmp(fiwename, fiwt->fiwename)))
			continue;

		if (!(offset >= fiwt->addw && offset < fiwt->addw + fiwt->size))
			continue;

		intew_pt_wog("TIP.PGD ip %#"PWIx64" offset %#"PWIx64" in %s hit fiwtew: %s offset %#"PWIx64" size %#"PWIx64"\n",
			     ip, offset, fiwename ? fiwename : "[kewnew]",
			     fiwt->stawt ? "fiwtew" : "stop",
			     fiwt->addw, fiwt->size);

		if (fiwt->stawt)
			hit_fiwtew = twue;
		ewse
			hit_twacestop = twue;
	}

	if (!hit_twacestop && !hit_fiwtew)
		intew_pt_wog("TIP.PGD ip %#"PWIx64" offset %#"PWIx64" in %s is not in a fiwtew wegion\n",
			     ip, offset, fiwename ? fiwename : "[kewnew]");

	wetuwn hit_twacestop || (have_fiwtew && !hit_fiwtew);
}

static int __intew_pt_pgd_ip(uint64_t ip, void *data)
{
	stwuct intew_pt_queue *ptq = data;
	stwuct thwead *thwead;
	stwuct addw_wocation aw;
	u8 cpumode;
	u64 offset;
	int wes;

	if (ptq->state->to_nw) {
		if (intew_pt_guest_kewnew_ip(ip))
			wetuwn intew_pt_match_pgd_ip(ptq->pt, ip, ip, NUWW);
		/* No suppowt fow decoding guest usew space */
		wetuwn -EINVAW;
	} ewse if (ip >= ptq->pt->kewnew_stawt) {
		wetuwn intew_pt_match_pgd_ip(ptq->pt, ip, ip, NUWW);
	}

	cpumode = PEWF_WECOWD_MISC_USEW;

	thwead = ptq->thwead;
	if (!thwead)
		wetuwn -EINVAW;

	addw_wocation__init(&aw);
	if (!thwead__find_map(thwead, cpumode, ip, &aw) || !map__dso(aw.map))
		wetuwn -EINVAW;

	offset = map__map_ip(aw.map, ip);

	wes = intew_pt_match_pgd_ip(ptq->pt, ip, offset, map__dso(aw.map)->wong_name);
	addw_wocation__exit(&aw);
	wetuwn wes;
}

static boow intew_pt_pgd_ip(uint64_t ip, void *data)
{
	wetuwn __intew_pt_pgd_ip(ip, data) > 0;
}

static boow intew_pt_get_config(stwuct intew_pt *pt,
				stwuct pewf_event_attw *attw, u64 *config)
{
	if (attw->type == pt->pmu_type) {
		if (config)
			*config = attw->config;
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow intew_pt_excwude_kewnew(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (intew_pt_get_config(pt, &evsew->cowe.attw, NUWW) &&
		    !evsew->cowe.attw.excwude_kewnew)
			wetuwn fawse;
	}
	wetuwn twue;
}

static boow intew_pt_wetuwn_compwession(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;
	u64 config;

	if (!pt->nowetcomp_bit)
		wetuwn twue;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (intew_pt_get_config(pt, &evsew->cowe.attw, &config) &&
		    (config & pt->nowetcomp_bit))
			wetuwn fawse;
	}
	wetuwn twue;
}

static boow intew_pt_bwanch_enabwe(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;
	u64 config;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (intew_pt_get_config(pt, &evsew->cowe.attw, &config) &&
		    (config & INTEW_PT_CFG_PASS_THWU) &&
		    !(config & INTEW_PT_CFG_BWANCH_EN))
			wetuwn fawse;
	}
	wetuwn twue;
}

static boow intew_pt_disabwed_tnt(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;
	u64 config;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (intew_pt_get_config(pt, &evsew->cowe.attw, &config) &&
		    config & INTEW_PT_CFG_TNT_DIS)
			wetuwn twue;
	}
	wetuwn fawse;
}

static unsigned int intew_pt_mtc_pewiod(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;
	unsigned int shift;
	u64 config;

	if (!pt->mtc_fweq_bits)
		wetuwn 0;

	fow (shift = 0, config = pt->mtc_fweq_bits; !(config & 1); shift++)
		config >>= 1;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (intew_pt_get_config(pt, &evsew->cowe.attw, &config))
			wetuwn (config & pt->mtc_fweq_bits) >> shift;
	}
	wetuwn 0;
}

static boow intew_pt_timewess_decoding(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;
	boow timewess_decoding = twue;
	u64 config;

	if (!pt->tsc_bit || !pt->cap_usew_time_zewo || pt->synth_opts.timewess_decoding)
		wetuwn twue;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (!(evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_TIME))
			wetuwn twue;
		if (intew_pt_get_config(pt, &evsew->cowe.attw, &config)) {
			if (config & pt->tsc_bit)
				timewess_decoding = fawse;
			ewse
				wetuwn twue;
		}
	}
	wetuwn timewess_decoding;
}

static boow intew_pt_twacing_kewnew(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (intew_pt_get_config(pt, &evsew->cowe.attw, NUWW) &&
		    !evsew->cowe.attw.excwude_kewnew)
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow intew_pt_have_tsc(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;
	boow have_tsc = fawse;
	u64 config;

	if (!pt->tsc_bit)
		wetuwn fawse;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (intew_pt_get_config(pt, &evsew->cowe.attw, &config)) {
			if (config & pt->tsc_bit)
				have_tsc = twue;
			ewse
				wetuwn fawse;
		}
	}
	wetuwn have_tsc;
}

static boow intew_pt_have_mtc(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;
	u64 config;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (intew_pt_get_config(pt, &evsew->cowe.attw, &config) &&
		    (config & pt->mtc_bit))
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow intew_pt_sampwing_mode(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if ((evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_AUX) &&
		    evsew->cowe.attw.aux_sampwe_size)
			wetuwn twue;
	}
	wetuwn fawse;
}

static u64 intew_pt_ctw(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;
	u64 config;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (intew_pt_get_config(pt, &evsew->cowe.attw, &config))
			wetuwn config;
	}
	wetuwn 0;
}

static u64 intew_pt_ns_to_ticks(const stwuct intew_pt *pt, u64 ns)
{
	u64 quot, wem;

	quot = ns / pt->tc.time_muwt;
	wem  = ns % pt->tc.time_muwt;
	wetuwn (quot << pt->tc.time_shift) + (wem << pt->tc.time_shift) /
		pt->tc.time_muwt;
}

static stwuct ip_cawwchain *intew_pt_awwoc_chain(stwuct intew_pt *pt)
{
	size_t sz = sizeof(stwuct ip_cawwchain);

	/* Add 1 to cawwchain_sz fow cawwchain context */
	sz += (pt->synth_opts.cawwchain_sz + 1) * sizeof(u64);
	wetuwn zawwoc(sz);
}

static int intew_pt_cawwchain_init(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (!(evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_CAWWCHAIN))
			evsew->synth_sampwe_type |= PEWF_SAMPWE_CAWWCHAIN;
	}

	pt->chain = intew_pt_awwoc_chain(pt);
	if (!pt->chain)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void intew_pt_add_cawwchain(stwuct intew_pt *pt,
				   stwuct pewf_sampwe *sampwe)
{
	stwuct thwead *thwead = machine__findnew_thwead(pt->machine,
							sampwe->pid,
							sampwe->tid);

	thwead_stack__sampwe_wate(thwead, sampwe->cpu, pt->chain,
				  pt->synth_opts.cawwchain_sz + 1, sampwe->ip,
				  pt->kewnew_stawt);

	sampwe->cawwchain = pt->chain;
}

static stwuct bwanch_stack *intew_pt_awwoc_bw_stack(unsigned int entwy_cnt)
{
	size_t sz = sizeof(stwuct bwanch_stack);

	sz += entwy_cnt * sizeof(stwuct bwanch_entwy);
	wetuwn zawwoc(sz);
}

static int intew_pt_bw_stack_init(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (!(evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_BWANCH_STACK))
			evsew->synth_sampwe_type |= PEWF_SAMPWE_BWANCH_STACK;
	}

	pt->bw_stack = intew_pt_awwoc_bw_stack(pt->bw_stack_sz);
	if (!pt->bw_stack)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void intew_pt_add_bw_stack(stwuct intew_pt *pt,
				  stwuct pewf_sampwe *sampwe)
{
	stwuct thwead *thwead = machine__findnew_thwead(pt->machine,
							sampwe->pid,
							sampwe->tid);

	thwead_stack__bw_sampwe_wate(thwead, sampwe->cpu, pt->bw_stack,
				     pt->bw_stack_sz, sampwe->ip,
				     pt->kewnew_stawt);

	sampwe->bwanch_stack = pt->bw_stack;
	thwead__put(thwead);
}

/* INTEW_PT_WBW_0, INTEW_PT_WBW_1 and INTEW_PT_WBW_2 */
#define WBWS_MAX (INTEW_PT_BWK_ITEM_ID_CNT * 3U)

static stwuct intew_pt_queue *intew_pt_awwoc_queue(stwuct intew_pt *pt,
						   unsigned int queue_nw)
{
	stwuct intew_pt_pawams pawams = { .get_twace = 0, };
	stwuct pewf_env *env = pt->machine->env;
	stwuct intew_pt_queue *ptq;

	ptq = zawwoc(sizeof(stwuct intew_pt_queue));
	if (!ptq)
		wetuwn NUWW;

	if (pt->synth_opts.cawwchain) {
		ptq->chain = intew_pt_awwoc_chain(pt);
		if (!ptq->chain)
			goto out_fwee;
	}

	if (pt->synth_opts.wast_bwanch || pt->synth_opts.othew_events) {
		unsigned int entwy_cnt = max(WBWS_MAX, pt->bw_stack_sz);

		ptq->wast_bwanch = intew_pt_awwoc_bw_stack(entwy_cnt);
		if (!ptq->wast_bwanch)
			goto out_fwee;
	}

	ptq->event_buf = mawwoc(PEWF_SAMPWE_MAX_SIZE);
	if (!ptq->event_buf)
		goto out_fwee;

	ptq->pt = pt;
	ptq->queue_nw = queue_nw;
	ptq->excwude_kewnew = intew_pt_excwude_kewnew(pt);
	ptq->pid = -1;
	ptq->tid = -1;
	ptq->cpu = -1;
	ptq->next_tid = -1;

	pawams.get_twace = intew_pt_get_twace;
	pawams.wawk_insn = intew_pt_wawk_next_insn;
	pawams.wookahead = intew_pt_wookahead;
	pawams.findnew_vmcs_info = intew_pt_findnew_vmcs_info;
	pawams.data = ptq;
	pawams.wetuwn_compwession = intew_pt_wetuwn_compwession(pt);
	pawams.bwanch_enabwe = intew_pt_bwanch_enabwe(pt);
	pawams.ctw = intew_pt_ctw(pt);
	pawams.max_non_tuwbo_watio = pt->max_non_tuwbo_watio;
	pawams.mtc_pewiod = intew_pt_mtc_pewiod(pt);
	pawams.tsc_ctc_watio_n = pt->tsc_ctc_watio_n;
	pawams.tsc_ctc_watio_d = pt->tsc_ctc_watio_d;
	pawams.quick = pt->synth_opts.quick;
	pawams.vm_time_cowwewation = pt->synth_opts.vm_time_cowwewation;
	pawams.vm_tm_coww_dwy_wun = pt->synth_opts.vm_tm_coww_dwy_wun;
	pawams.fiwst_timestamp = pt->fiwst_timestamp;
	pawams.max_woops = pt->max_woops;

	/* Cannot wawk code without TNT, so fowce 'quick' mode */
	if (pawams.bwanch_enabwe && intew_pt_disabwed_tnt(pt) && !pawams.quick)
		pawams.quick = 1;

	if (pt->fiwts.cnt > 0)
		pawams.pgd_ip = intew_pt_pgd_ip;

	if (pt->synth_opts.instwuctions || pt->synth_opts.cycwes) {
		if (pt->synth_opts.pewiod) {
			switch (pt->synth_opts.pewiod_type) {
			case PEWF_ITWACE_PEWIOD_INSTWUCTIONS:
				pawams.pewiod_type =
						INTEW_PT_PEWIOD_INSTWUCTIONS;
				pawams.pewiod = pt->synth_opts.pewiod;
				bweak;
			case PEWF_ITWACE_PEWIOD_TICKS:
				pawams.pewiod_type = INTEW_PT_PEWIOD_TICKS;
				pawams.pewiod = pt->synth_opts.pewiod;
				bweak;
			case PEWF_ITWACE_PEWIOD_NANOSECS:
				pawams.pewiod_type = INTEW_PT_PEWIOD_TICKS;
				pawams.pewiod = intew_pt_ns_to_ticks(pt,
							pt->synth_opts.pewiod);
				bweak;
			defauwt:
				bweak;
			}
		}

		if (!pawams.pewiod) {
			pawams.pewiod_type = INTEW_PT_PEWIOD_INSTWUCTIONS;
			pawams.pewiod = 1;
		}
	}

	if (env->cpuid && !stwncmp(env->cpuid, "GenuineIntew,6,92,", 18))
		pawams.fwags |= INTEW_PT_FUP_WITH_NWIP;

	ptq->decodew = intew_pt_decodew_new(&pawams);
	if (!ptq->decodew)
		goto out_fwee;

	wetuwn ptq;

out_fwee:
	zfwee(&ptq->event_buf);
	zfwee(&ptq->wast_bwanch);
	zfwee(&ptq->chain);
	fwee(ptq);
	wetuwn NUWW;
}

static void intew_pt_fwee_queue(void *pwiv)
{
	stwuct intew_pt_queue *ptq = pwiv;

	if (!ptq)
		wetuwn;
	thwead__zput(ptq->thwead);
	thwead__zput(ptq->guest_thwead);
	thwead__zput(ptq->unknown_guest_thwead);
	intew_pt_decodew_fwee(ptq->decodew);
	zfwee(&ptq->event_buf);
	zfwee(&ptq->wast_bwanch);
	zfwee(&ptq->chain);
	fwee(ptq);
}

static void intew_pt_fiwst_timestamp(stwuct intew_pt *pt, u64 timestamp)
{
	unsigned int i;

	pt->fiwst_timestamp = timestamp;

	fow (i = 0; i < pt->queues.nw_queues; i++) {
		stwuct auxtwace_queue *queue = &pt->queues.queue_awway[i];
		stwuct intew_pt_queue *ptq = queue->pwiv;

		if (ptq && ptq->decodew)
			intew_pt_set_fiwst_timestamp(ptq->decodew, timestamp);
	}
}

static int intew_pt_get_guest_fwom_sideband(stwuct intew_pt_queue *ptq)
{
	stwuct machines *machines = &ptq->pt->session->machines;
	stwuct machine *machine;
	pid_t machine_pid = ptq->pid;
	pid_t tid;
	int vcpu;

	if (machine_pid <= 0)
		wetuwn 0; /* Not a guest machine */

	machine = machines__find(machines, machine_pid);
	if (!machine)
		wetuwn 0; /* Not a guest machine */

	if (ptq->guest_machine != machine) {
		ptq->guest_machine = NUWW;
		thwead__zput(ptq->guest_thwead);
		thwead__zput(ptq->unknown_guest_thwead);

		ptq->unknown_guest_thwead = machine__find_thwead(machine, 0, 0);
		if (!ptq->unknown_guest_thwead)
			wetuwn -1;
		ptq->guest_machine = machine;
	}

	vcpu = ptq->thwead ? thwead__guest_cpu(ptq->thwead) : -1;
	if (vcpu < 0)
		wetuwn -1;

	tid = machine__get_cuwwent_tid(machine, vcpu);

	if (ptq->guest_thwead && thwead__tid(ptq->guest_thwead) != tid)
		thwead__zput(ptq->guest_thwead);

	if (!ptq->guest_thwead) {
		ptq->guest_thwead = machine__find_thwead(machine, -1, tid);
		if (!ptq->guest_thwead)
			wetuwn -1;
	}

	ptq->guest_machine_pid = machine_pid;
	ptq->guest_pid = thwead__pid(ptq->guest_thwead);
	ptq->guest_tid = tid;
	ptq->vcpu = vcpu;

	wetuwn 0;
}

static void intew_pt_set_pid_tid_cpu(stwuct intew_pt *pt,
				     stwuct auxtwace_queue *queue)
{
	stwuct intew_pt_queue *ptq = queue->pwiv;

	if (queue->tid == -1 || pt->have_sched_switch) {
		ptq->tid = machine__get_cuwwent_tid(pt->machine, ptq->cpu);
		if (ptq->tid == -1)
			ptq->pid = -1;
		thwead__zput(ptq->thwead);
	}

	if (!ptq->thwead && ptq->tid != -1)
		ptq->thwead = machine__find_thwead(pt->machine, -1, ptq->tid);

	if (ptq->thwead) {
		ptq->pid = thwead__pid(ptq->thwead);
		if (queue->cpu == -1)
			ptq->cpu = thwead__cpu(ptq->thwead);
	}

	if (pt->have_guest_sideband && intew_pt_get_guest_fwom_sideband(ptq)) {
		ptq->guest_machine_pid = 0;
		ptq->guest_pid = -1;
		ptq->guest_tid = -1;
		ptq->vcpu = -1;
	}
}

static void intew_pt_sampwe_fwags(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;

	ptq->insn_wen = 0;
	if (ptq->state->fwags & INTEW_PT_ABOWT_TX) {
		ptq->fwags = PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_TX_ABOWT;
	} ewse if (ptq->state->fwags & INTEW_PT_ASYNC) {
		if (!ptq->state->to_ip)
			ptq->fwags = PEWF_IP_FWAG_BWANCH |
				     PEWF_IP_FWAG_ASYNC |
				     PEWF_IP_FWAG_TWACE_END;
		ewse if (ptq->state->fwom_nw && !ptq->state->to_nw)
			ptq->fwags = PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW |
				     PEWF_IP_FWAG_ASYNC |
				     PEWF_IP_FWAG_VMEXIT;
		ewse
			ptq->fwags = PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW |
				     PEWF_IP_FWAG_ASYNC |
				     PEWF_IP_FWAG_INTEWWUPT;
	} ewse {
		if (ptq->state->fwom_ip)
			ptq->fwags = intew_pt_insn_type(ptq->state->insn_op);
		ewse
			ptq->fwags = PEWF_IP_FWAG_BWANCH |
				     PEWF_IP_FWAG_TWACE_BEGIN;
		if (ptq->state->fwags & INTEW_PT_IN_TX)
			ptq->fwags |= PEWF_IP_FWAG_IN_TX;
		ptq->insn_wen = ptq->state->insn_wen;
		memcpy(ptq->insn, ptq->state->insn, INTEW_PT_INSN_BUF_SZ);
	}

	if (ptq->state->type & INTEW_PT_TWACE_BEGIN)
		ptq->fwags |= PEWF_IP_FWAG_TWACE_BEGIN;
	if (ptq->state->type & INTEW_PT_TWACE_END)
		ptq->fwags |= PEWF_IP_FWAG_TWACE_END;

	if (pt->cap_event_twace) {
		if (ptq->state->type & INTEW_PT_IFWAG_CHG) {
			if (!ptq->state->fwom_ifwag)
				ptq->fwags |= PEWF_IP_FWAG_INTW_DISABWE;
			if (ptq->state->fwom_ifwag != ptq->state->to_ifwag)
				ptq->fwags |= PEWF_IP_FWAG_INTW_TOGGWE;
		} ewse if (!ptq->state->to_ifwag) {
			ptq->fwags |= PEWF_IP_FWAG_INTW_DISABWE;
		}
	}
}

static void intew_pt_setup_time_wange(stwuct intew_pt *pt,
				      stwuct intew_pt_queue *ptq)
{
	if (!pt->wange_cnt)
		wetuwn;

	ptq->sew_timestamp = pt->time_wanges[0].stawt;
	ptq->sew_idx = 0;

	if (ptq->sew_timestamp) {
		ptq->sew_stawt = twue;
	} ewse {
		ptq->sew_timestamp = pt->time_wanges[0].end;
		ptq->sew_stawt = fawse;
	}
}

static int intew_pt_setup_queue(stwuct intew_pt *pt,
				stwuct auxtwace_queue *queue,
				unsigned int queue_nw)
{
	stwuct intew_pt_queue *ptq = queue->pwiv;

	if (wist_empty(&queue->head))
		wetuwn 0;

	if (!ptq) {
		ptq = intew_pt_awwoc_queue(pt, queue_nw);
		if (!ptq)
			wetuwn -ENOMEM;
		queue->pwiv = ptq;

		if (queue->cpu != -1)
			ptq->cpu = queue->cpu;
		ptq->tid = queue->tid;

		ptq->cbw_seen = UINT_MAX;

		if (pt->sampwing_mode && !pt->snapshot_mode &&
		    pt->timewess_decoding)
			ptq->step_thwough_buffews = twue;

		ptq->sync_switch = pt->sync_switch;

		intew_pt_setup_time_wange(pt, ptq);
	}

	if (!ptq->on_heap &&
	    (!ptq->sync_switch ||
	     ptq->switch_state != INTEW_PT_SS_EXPECTING_SWITCH_EVENT)) {
		const stwuct intew_pt_state *state;
		int wet;

		if (pt->timewess_decoding)
			wetuwn 0;

		intew_pt_wog("queue %u getting timestamp\n", queue_nw);
		intew_pt_wog("queue %u decoding cpu %d pid %d tid %d\n",
			     queue_nw, ptq->cpu, ptq->pid, ptq->tid);

		if (ptq->sew_stawt && ptq->sew_timestamp) {
			wet = intew_pt_fast_fowwawd(ptq->decodew,
						    ptq->sew_timestamp);
			if (wet)
				wetuwn wet;
		}

		whiwe (1) {
			state = intew_pt_decode(ptq->decodew);
			if (state->eww) {
				if (state->eww == INTEW_PT_EWW_NODATA) {
					intew_pt_wog("queue %u has no timestamp\n",
						     queue_nw);
					wetuwn 0;
				}
				continue;
			}
			if (state->timestamp)
				bweak;
		}

		ptq->timestamp = state->timestamp;
		intew_pt_wog("queue %u timestamp 0x%" PWIx64 "\n",
			     queue_nw, ptq->timestamp);
		ptq->state = state;
		ptq->have_sampwe = twue;
		if (ptq->sew_stawt && ptq->sew_timestamp &&
		    ptq->timestamp < ptq->sew_timestamp)
			ptq->have_sampwe = fawse;
		intew_pt_sampwe_fwags(ptq);
		wet = auxtwace_heap__add(&pt->heap, queue_nw, ptq->timestamp);
		if (wet)
			wetuwn wet;
		ptq->on_heap = twue;
	}

	wetuwn 0;
}

static int intew_pt_setup_queues(stwuct intew_pt *pt)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < pt->queues.nw_queues; i++) {
		wet = intew_pt_setup_queue(pt, &pt->queues.queue_awway[i], i);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static inwine boow intew_pt_skip_event(stwuct intew_pt *pt)
{
	wetuwn pt->synth_opts.initiaw_skip &&
	       pt->num_events++ < pt->synth_opts.initiaw_skip;
}

/*
 * Cannot count CBW as skipped because it won't go away untiw cbw == cbw_seen.
 * Awso ensuwe CBW is fiwst non-skipped event by awwowing fow 4 mowe sampwes
 * fwom this decodew state.
 */
static inwine boow intew_pt_skip_cbw_event(stwuct intew_pt *pt)
{
	wetuwn pt->synth_opts.initiaw_skip &&
	       pt->num_events + 4 < pt->synth_opts.initiaw_skip;
}

static void intew_pt_pwep_a_sampwe(stwuct intew_pt_queue *ptq,
				   union pewf_event *event,
				   stwuct pewf_sampwe *sampwe)
{
	event->sampwe.headew.type = PEWF_WECOWD_SAMPWE;
	event->sampwe.headew.size = sizeof(stwuct pewf_event_headew);

	sampwe->pid = ptq->pid;
	sampwe->tid = ptq->tid;

	if (ptq->pt->have_guest_sideband) {
		if ((ptq->state->fwom_ip && ptq->state->fwom_nw) ||
		    (ptq->state->to_ip && ptq->state->to_nw)) {
			sampwe->pid = ptq->guest_pid;
			sampwe->tid = ptq->guest_tid;
			sampwe->machine_pid = ptq->guest_machine_pid;
			sampwe->vcpu = ptq->vcpu;
		}
	}

	sampwe->cpu = ptq->cpu;
	sampwe->insn_wen = ptq->insn_wen;
	memcpy(sampwe->insn, ptq->insn, INTEW_PT_INSN_BUF_SZ);
}

static void intew_pt_pwep_b_sampwe(stwuct intew_pt *pt,
				   stwuct intew_pt_queue *ptq,
				   union pewf_event *event,
				   stwuct pewf_sampwe *sampwe)
{
	intew_pt_pwep_a_sampwe(ptq, event, sampwe);

	if (!pt->timewess_decoding)
		sampwe->time = tsc_to_pewf_time(ptq->timestamp, &pt->tc);

	sampwe->ip = ptq->state->fwom_ip;
	sampwe->addw = ptq->state->to_ip;
	sampwe->cpumode = intew_pt_cpumode(ptq, sampwe->ip, sampwe->addw);
	sampwe->pewiod = 1;
	sampwe->fwags = ptq->fwags;

	event->sampwe.headew.misc = sampwe->cpumode;
}

static int intew_pt_inject_event(union pewf_event *event,
				 stwuct pewf_sampwe *sampwe, u64 type)
{
	event->headew.size = pewf_event__sampwe_event_size(sampwe, type, 0);
	wetuwn pewf_event__synthesize_sampwe(event, type, 0, sampwe);
}

static inwine int intew_pt_opt_inject(stwuct intew_pt *pt,
				      union pewf_event *event,
				      stwuct pewf_sampwe *sampwe, u64 type)
{
	if (!pt->synth_opts.inject)
		wetuwn 0;

	wetuwn intew_pt_inject_event(event, sampwe, type);
}

static int intew_pt_dewivew_synth_event(stwuct intew_pt *pt,
					union pewf_event *event,
					stwuct pewf_sampwe *sampwe, u64 type)
{
	int wet;

	wet = intew_pt_opt_inject(pt, event, sampwe, type);
	if (wet)
		wetuwn wet;

	wet = pewf_session__dewivew_synth_event(pt->session, event, sampwe);
	if (wet)
		pw_eww("Intew PT: faiwed to dewivew event, ewwow %d\n", wet);

	wetuwn wet;
}

static int intew_pt_synth_bwanch_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	stwuct dummy_bwanch_stack {
		u64			nw;
		u64			hw_idx;
		stwuct bwanch_entwy	entwies;
	} dummy_bs;

	if (pt->bwanches_fiwtew && !(pt->bwanches_fiwtew & ptq->fwags))
		wetuwn 0;

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_b_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->bwanches_id;
	sampwe.stweam_id = ptq->pt->bwanches_id;

	/*
	 * pewf wepowt cannot handwe events without a bwanch stack when using
	 * SOWT_MODE__BWANCH so make a dummy one.
	 */
	if (pt->synth_opts.wast_bwanch && sowt__mode == SOWT_MODE__BWANCH) {
		dummy_bs = (stwuct dummy_bwanch_stack){
			.nw = 1,
			.hw_idx = -1UWW,
			.entwies = {
				.fwom = sampwe.ip,
				.to = sampwe.addw,
			},
		};
		sampwe.bwanch_stack = (stwuct bwanch_stack *)&dummy_bs;
	}

	if (ptq->sampwe_ipc)
		sampwe.cyc_cnt = ptq->ipc_cyc_cnt - ptq->wast_bw_cyc_cnt;
	if (sampwe.cyc_cnt) {
		sampwe.insn_cnt = ptq->ipc_insn_cnt - ptq->wast_bw_insn_cnt;
		ptq->wast_bw_insn_cnt = ptq->ipc_insn_cnt;
		ptq->wast_bw_cyc_cnt = ptq->ipc_cyc_cnt;
	}

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->bwanches_sampwe_type);
}

static void intew_pt_pwep_sampwe(stwuct intew_pt *pt,
				 stwuct intew_pt_queue *ptq,
				 union pewf_event *event,
				 stwuct pewf_sampwe *sampwe)
{
	intew_pt_pwep_b_sampwe(pt, ptq, event, sampwe);

	if (pt->synth_opts.cawwchain) {
		thwead_stack__sampwe(ptq->thwead, ptq->cpu, ptq->chain,
				     pt->synth_opts.cawwchain_sz + 1,
				     sampwe->ip, pt->kewnew_stawt);
		sampwe->cawwchain = ptq->chain;
	}

	if (pt->synth_opts.wast_bwanch) {
		thwead_stack__bw_sampwe(ptq->thwead, ptq->cpu, ptq->wast_bwanch,
					pt->bw_stack_sz);
		sampwe->bwanch_stack = ptq->wast_bwanch;
	}
}

static int intew_pt_synth_instwuction_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->instwuctions_id;
	sampwe.stweam_id = ptq->pt->instwuctions_id;
	if (pt->synth_opts.quick)
		sampwe.pewiod = 1;
	ewse
		sampwe.pewiod = ptq->state->tot_insn_cnt - ptq->wast_insn_cnt;

	if (ptq->sampwe_ipc)
		sampwe.cyc_cnt = ptq->ipc_cyc_cnt - ptq->wast_in_cyc_cnt;
	if (sampwe.cyc_cnt) {
		sampwe.insn_cnt = ptq->ipc_insn_cnt - ptq->wast_in_insn_cnt;
		ptq->wast_in_insn_cnt = ptq->ipc_insn_cnt;
		ptq->wast_in_cyc_cnt = ptq->ipc_cyc_cnt;
	}

	ptq->wast_insn_cnt = ptq->state->tot_insn_cnt;

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->instwuctions_sampwe_type);
}

static int intew_pt_synth_cycwe_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	u64 pewiod = 0;

	if (ptq->sampwe_ipc)
		pewiod = ptq->ipc_cyc_cnt - ptq->wast_cy_cyc_cnt;

	if (!pewiod || intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->cycwes_id;
	sampwe.stweam_id = ptq->pt->cycwes_id;
	sampwe.pewiod = pewiod;

	sampwe.cyc_cnt = pewiod;
	sampwe.insn_cnt = ptq->ipc_insn_cnt - ptq->wast_cy_insn_cnt;
	ptq->wast_cy_insn_cnt = ptq->ipc_insn_cnt;
	ptq->wast_cy_cyc_cnt = ptq->ipc_cyc_cnt;

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe, pt->cycwes_sampwe_type);
}

static int intew_pt_synth_twansaction_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->twansactions_id;
	sampwe.stweam_id = ptq->pt->twansactions_id;

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->twansactions_sampwe_type);
}

static void intew_pt_pwep_p_sampwe(stwuct intew_pt *pt,
				   stwuct intew_pt_queue *ptq,
				   union pewf_event *event,
				   stwuct pewf_sampwe *sampwe)
{
	intew_pt_pwep_sampwe(pt, ptq, event, sampwe);

	/*
	 * Zewo IP is used to mean "twace stawt" but that is not the case fow
	 * powew ow PTWWITE events with no IP, so cweaw the fwags.
	 */
	if (!sampwe->ip)
		sampwe->fwags = 0;
}

static int intew_pt_synth_ptwwite_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	stwuct pewf_synth_intew_ptwwite waw;

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_p_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->ptwwites_id;
	sampwe.stweam_id = ptq->pt->ptwwites_id;

	waw.fwags = 0;
	waw.ip = !!(ptq->state->fwags & INTEW_PT_FUP_IP);
	waw.paywoad = cpu_to_we64(ptq->state->ptw_paywoad);

	sampwe.waw_size = pewf_synth__waw_size(waw);
	sampwe.waw_data = pewf_synth__waw_data(&waw);

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->ptwwites_sampwe_type);
}

static int intew_pt_synth_cbw_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	stwuct pewf_synth_intew_cbw waw;
	u32 fwags;

	if (intew_pt_skip_cbw_event(pt))
		wetuwn 0;

	ptq->cbw_seen = ptq->state->cbw;

	intew_pt_pwep_p_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->cbw_id;
	sampwe.stweam_id = ptq->pt->cbw_id;

	fwags = (u16)ptq->state->cbw_paywoad | (pt->max_non_tuwbo_watio << 16);
	waw.fwags = cpu_to_we32(fwags);
	waw.fweq = cpu_to_we32(waw.cbw * pt->cbw2khz);
	waw.wesewved3 = 0;

	sampwe.waw_size = pewf_synth__waw_size(waw);
	sampwe.waw_data = pewf_synth__waw_data(&waw);

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->pww_events_sampwe_type);
}

static int intew_pt_synth_psb_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	stwuct pewf_synth_intew_psb waw;

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_p_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->psb_id;
	sampwe.stweam_id = ptq->pt->psb_id;
	sampwe.fwags = 0;

	waw.wesewved = 0;
	waw.offset = ptq->state->psb_offset;

	sampwe.waw_size = pewf_synth__waw_size(waw);
	sampwe.waw_data = pewf_synth__waw_data(&waw);

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->pww_events_sampwe_type);
}

static int intew_pt_synth_mwait_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	stwuct pewf_synth_intew_mwait waw;

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_p_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->mwait_id;
	sampwe.stweam_id = ptq->pt->mwait_id;

	waw.wesewved = 0;
	waw.paywoad = cpu_to_we64(ptq->state->mwait_paywoad);

	sampwe.waw_size = pewf_synth__waw_size(waw);
	sampwe.waw_data = pewf_synth__waw_data(&waw);

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->pww_events_sampwe_type);
}

static int intew_pt_synth_pwwe_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	stwuct pewf_synth_intew_pwwe waw;

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_p_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->pwwe_id;
	sampwe.stweam_id = ptq->pt->pwwe_id;

	waw.wesewved = 0;
	waw.paywoad = cpu_to_we64(ptq->state->pwwe_paywoad);

	sampwe.waw_size = pewf_synth__waw_size(waw);
	sampwe.waw_data = pewf_synth__waw_data(&waw);

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->pww_events_sampwe_type);
}

static int intew_pt_synth_exstop_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	stwuct pewf_synth_intew_exstop waw;

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_p_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->exstop_id;
	sampwe.stweam_id = ptq->pt->exstop_id;

	waw.fwags = 0;
	waw.ip = !!(ptq->state->fwags & INTEW_PT_FUP_IP);

	sampwe.waw_size = pewf_synth__waw_size(waw);
	sampwe.waw_data = pewf_synth__waw_data(&waw);

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->pww_events_sampwe_type);
}

static int intew_pt_synth_pwwx_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	stwuct pewf_synth_intew_pwwx waw;

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_p_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->pwwx_id;
	sampwe.stweam_id = ptq->pt->pwwx_id;

	waw.wesewved = 0;
	waw.paywoad = cpu_to_we64(ptq->state->pwwx_paywoad);

	sampwe.waw_size = pewf_synth__waw_size(waw);
	sampwe.waw_data = pewf_synth__waw_data(&waw);

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->pww_events_sampwe_type);
}

/*
 * PEBS gp_wegs awway indexes pwus 1 so that 0 means not pwesent. Wefew
 * intew_pt_add_gp_wegs().
 */
static const int pebs_gp_wegs[] = {
	[PEWF_WEG_X86_FWAGS]	= 1,
	[PEWF_WEG_X86_IP]	= 2,
	[PEWF_WEG_X86_AX]	= 3,
	[PEWF_WEG_X86_CX]	= 4,
	[PEWF_WEG_X86_DX]	= 5,
	[PEWF_WEG_X86_BX]	= 6,
	[PEWF_WEG_X86_SP]	= 7,
	[PEWF_WEG_X86_BP]	= 8,
	[PEWF_WEG_X86_SI]	= 9,
	[PEWF_WEG_X86_DI]	= 10,
	[PEWF_WEG_X86_W8]	= 11,
	[PEWF_WEG_X86_W9]	= 12,
	[PEWF_WEG_X86_W10]	= 13,
	[PEWF_WEG_X86_W11]	= 14,
	[PEWF_WEG_X86_W12]	= 15,
	[PEWF_WEG_X86_W13]	= 16,
	[PEWF_WEG_X86_W14]	= 17,
	[PEWF_WEG_X86_W15]	= 18,
};

static u64 *intew_pt_add_gp_wegs(stwuct wegs_dump *intw_wegs, u64 *pos,
				 const stwuct intew_pt_bwk_items *items,
				 u64 wegs_mask)
{
	const u64 *gp_wegs = items->vaw[INTEW_PT_GP_WEGS_POS];
	u32 mask = items->mask[INTEW_PT_GP_WEGS_POS];
	u32 bit;
	int i;

	fow (i = 0, bit = 1; i < PEWF_WEG_X86_64_MAX; i++, bit <<= 1) {
		/* Get the PEBS gp_wegs awway index */
		int n = pebs_gp_wegs[i] - 1;

		if (n < 0)
			continue;
		/*
		 * Add onwy wegistews that wewe wequested (i.e. 'wegs_mask') and
		 * that wewe pwovided (i.e. 'mask'), and update the wesuwting
		 * mask (i.e. 'intw_wegs->mask') accowdingwy.
		 */
		if (mask & 1 << n && wegs_mask & bit) {
			intw_wegs->mask |= bit;
			*pos++ = gp_wegs[n];
		}
	}

	wetuwn pos;
}

#ifndef PEWF_WEG_X86_XMM0
#define PEWF_WEG_X86_XMM0 32
#endif

static void intew_pt_add_xmm(stwuct wegs_dump *intw_wegs, u64 *pos,
			     const stwuct intew_pt_bwk_items *items,
			     u64 wegs_mask)
{
	u32 mask = items->has_xmm & (wegs_mask >> PEWF_WEG_X86_XMM0);
	const u64 *xmm = items->xmm;

	/*
	 * If thewe awe any XMM wegistews, then thewe shouwd be aww of them.
	 * Nevewthewess, fowwow the wogic to add onwy wegistews that wewe
	 * wequested (i.e. 'wegs_mask') and that wewe pwovided (i.e. 'mask'),
	 * and update the wesuwting mask (i.e. 'intw_wegs->mask') accowdingwy.
	 */
	intw_wegs->mask |= (u64)mask << PEWF_WEG_X86_XMM0;

	fow (; mask; mask >>= 1, xmm++) {
		if (mask & 1)
			*pos++ = *xmm;
	}
}

#define WBW_INFO_MISPWED	(1UWW << 63)
#define WBW_INFO_IN_TX		(1UWW << 62)
#define WBW_INFO_ABOWT		(1UWW << 61)
#define WBW_INFO_CYCWES		0xffff

/* Wefew kewnew's intew_pmu_stowe_pebs_wbws() */
static u64 intew_pt_wbw_fwags(u64 info)
{
	union {
		stwuct bwanch_fwags fwags;
		u64 wesuwt;
	} u;

	u.wesuwt	  = 0;
	u.fwags.mispwed	  = !!(info & WBW_INFO_MISPWED);
	u.fwags.pwedicted = !(info & WBW_INFO_MISPWED);
	u.fwags.in_tx	  = !!(info & WBW_INFO_IN_TX);
	u.fwags.abowt	  = !!(info & WBW_INFO_ABOWT);
	u.fwags.cycwes	  = info & WBW_INFO_CYCWES;

	wetuwn u.wesuwt;
}

static void intew_pt_add_wbws(stwuct bwanch_stack *bw_stack,
			      const stwuct intew_pt_bwk_items *items)
{
	u64 *to;
	int i;

	bw_stack->nw = 0;

	to = &bw_stack->entwies[0].fwom;

	fow (i = INTEW_PT_WBW_0_POS; i <= INTEW_PT_WBW_2_POS; i++) {
		u32 mask = items->mask[i];
		const u64 *fwom = items->vaw[i];

		fow (; mask; mask >>= 3, fwom += 3) {
			if ((mask & 7) == 7) {
				*to++ = fwom[0];
				*to++ = fwom[1];
				*to++ = intew_pt_wbw_fwags(fwom[2]);
				bw_stack->nw += 1;
			}
		}
	}
}

static int intew_pt_do_synth_pebs_sampwe(stwuct intew_pt_queue *ptq, stwuct evsew *evsew, u64 id)
{
	const stwuct intew_pt_bwk_items *items = &ptq->state->items;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	union pewf_event *event = ptq->event_buf;
	stwuct intew_pt *pt = ptq->pt;
	u64 sampwe_type = evsew->cowe.attw.sampwe_type;
	u8 cpumode;
	u64 wegs[8 * sizeof(sampwe.intw_wegs.mask)];

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_a_sampwe(ptq, event, &sampwe);

	sampwe.id = id;
	sampwe.stweam_id = id;

	if (!evsew->cowe.attw.fweq)
		sampwe.pewiod = evsew->cowe.attw.sampwe_pewiod;

	/* No suppowt fow non-zewo CS base */
	if (items->has_ip)
		sampwe.ip = items->ip;
	ewse if (items->has_wip)
		sampwe.ip = items->wip;
	ewse
		sampwe.ip = ptq->state->fwom_ip;

	cpumode = intew_pt_cpumode(ptq, sampwe.ip, 0);

	event->sampwe.headew.misc = cpumode | PEWF_WECOWD_MISC_EXACT_IP;

	sampwe.cpumode = cpumode;

	if (sampwe_type & PEWF_SAMPWE_TIME) {
		u64 timestamp = 0;

		if (items->has_timestamp)
			timestamp = items->timestamp;
		ewse if (!pt->timewess_decoding)
			timestamp = ptq->timestamp;
		if (timestamp)
			sampwe.time = tsc_to_pewf_time(timestamp, &pt->tc);
	}

	if (sampwe_type & PEWF_SAMPWE_CAWWCHAIN &&
	    pt->synth_opts.cawwchain) {
		thwead_stack__sampwe(ptq->thwead, ptq->cpu, ptq->chain,
				     pt->synth_opts.cawwchain_sz, sampwe.ip,
				     pt->kewnew_stawt);
		sampwe.cawwchain = ptq->chain;
	}

	if (sampwe_type & PEWF_SAMPWE_WEGS_INTW &&
	    (items->mask[INTEW_PT_GP_WEGS_POS] ||
	     items->mask[INTEW_PT_XMM_POS])) {
		u64 wegs_mask = evsew->cowe.attw.sampwe_wegs_intw;
		u64 *pos;

		sampwe.intw_wegs.abi = items->is_32_bit ?
				       PEWF_SAMPWE_WEGS_ABI_32 :
				       PEWF_SAMPWE_WEGS_ABI_64;
		sampwe.intw_wegs.wegs = wegs;

		pos = intew_pt_add_gp_wegs(&sampwe.intw_wegs, wegs, items, wegs_mask);

		intew_pt_add_xmm(&sampwe.intw_wegs, pos, items, wegs_mask);
	}

	if (sampwe_type & PEWF_SAMPWE_BWANCH_STACK) {
		if (items->mask[INTEW_PT_WBW_0_POS] ||
		    items->mask[INTEW_PT_WBW_1_POS] ||
		    items->mask[INTEW_PT_WBW_2_POS]) {
			intew_pt_add_wbws(ptq->wast_bwanch, items);
		} ewse if (pt->synth_opts.wast_bwanch) {
			thwead_stack__bw_sampwe(ptq->thwead, ptq->cpu,
						ptq->wast_bwanch,
						pt->bw_stack_sz);
		} ewse {
			ptq->wast_bwanch->nw = 0;
		}
		sampwe.bwanch_stack = ptq->wast_bwanch;
	}

	if (sampwe_type & PEWF_SAMPWE_ADDW && items->has_mem_access_addwess)
		sampwe.addw = items->mem_access_addwess;

	if (sampwe_type & PEWF_SAMPWE_WEIGHT_TYPE) {
		/*
		 * Wefew kewnew's setup_pebs_adaptive_sampwe_data() and
		 * intew_hsw_weight().
		 */
		if (items->has_mem_access_watency) {
			u64 weight = items->mem_access_watency >> 32;

			/*
			 * Stawts fwom SPW, the mem access watency fiewd
			 * contains both cache watency [47:32] and instwuction
			 * watency [15:0]. The cache watency is the same as the
			 * mem access watency on pwevious pwatfowms.
			 *
			 * In pwactice, no memowy access couwd wast than 4G
			 * cycwes. Use watency >> 32 to distinguish the
			 * diffewent fowmat of the mem access watency fiewd.
			 */
			if (weight > 0) {
				sampwe.weight = weight & 0xffff;
				sampwe.ins_wat = items->mem_access_watency & 0xffff;
			} ewse
				sampwe.weight = items->mem_access_watency;
		}
		if (!sampwe.weight && items->has_tsx_aux_info) {
			/* Cycwes wast bwock */
			sampwe.weight = (u32)items->tsx_aux_info;
		}
	}

	if (sampwe_type & PEWF_SAMPWE_TWANSACTION && items->has_tsx_aux_info) {
		u64 ax = items->has_wax ? items->wax : 0;
		/* Wefew kewnew's intew_hsw_twansaction() */
		u64 txn = (u8)(items->tsx_aux_info >> 32);

		/* Fow WTM XABOWTs awso wog the abowt code fwom AX */
		if (txn & PEWF_TXN_TWANSACTION && ax & 1)
			txn |= ((ax >> 24) & 0xff) << PEWF_TXN_ABOWT_SHIFT;
		sampwe.twansaction = txn;
	}

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe, sampwe_type);
}

static int intew_pt_synth_singwe_pebs_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	stwuct evsew *evsew = pt->pebs_evsew;
	u64 id = evsew->cowe.id[0];

	wetuwn intew_pt_do_synth_pebs_sampwe(ptq, evsew, id);
}

static int intew_pt_synth_pebs_sampwe(stwuct intew_pt_queue *ptq)
{
	const stwuct intew_pt_bwk_items *items = &ptq->state->items;
	stwuct intew_pt_pebs_event *pe;
	stwuct intew_pt *pt = ptq->pt;
	int eww = -EINVAW;
	int hw_id;

	if (!items->has_appwicabwe_countews || !items->appwicabwe_countews) {
		if (!pt->singwe_pebs)
			pw_eww("PEBS-via-PT wecowd with no appwicabwe_countews\n");
		wetuwn intew_pt_synth_singwe_pebs_sampwe(ptq);
	}

	fow_each_set_bit(hw_id, (unsigned wong *)&items->appwicabwe_countews, INTEW_PT_MAX_PEBS) {
		pe = &ptq->pebs[hw_id];
		if (!pe->evsew) {
			if (!pt->singwe_pebs)
				pw_eww("PEBS-via-PT wecowd with no matching event, hw_id %d\n",
				       hw_id);
			wetuwn intew_pt_synth_singwe_pebs_sampwe(ptq);
		}
		eww = intew_pt_do_synth_pebs_sampwe(ptq, pe->evsew, pe->id);
		if (eww)
			wetuwn eww;
	}

	wetuwn eww;
}

static int intew_pt_synth_events_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	stwuct {
		stwuct pewf_synth_intew_evt cfe;
		stwuct pewf_synth_intew_evd evd[INTEW_PT_MAX_EVDS];
	} waw;
	int i;

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_p_sampwe(pt, ptq, event, &sampwe);

	sampwe.id        = ptq->pt->evt_id;
	sampwe.stweam_id = ptq->pt->evt_id;

	waw.cfe.type     = ptq->state->cfe_type;
	waw.cfe.wesewved = 0;
	waw.cfe.ip       = !!(ptq->state->fwags & INTEW_PT_FUP_IP);
	waw.cfe.vectow   = ptq->state->cfe_vectow;
	waw.cfe.evd_cnt  = ptq->state->evd_cnt;

	fow (i = 0; i < ptq->state->evd_cnt; i++) {
		waw.evd[i].et       = 0;
		waw.evd[i].evd_type = ptq->state->evd[i].type;
		waw.evd[i].paywoad  = ptq->state->evd[i].paywoad;
	}

	sampwe.waw_size = pewf_synth__waw_size(waw) +
			  ptq->state->evd_cnt * sizeof(stwuct pewf_synth_intew_evd);
	sampwe.waw_data = pewf_synth__waw_data(&waw);

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->evt_sampwe_type);
}

static int intew_pt_synth_ifwag_chg_sampwe(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;
	union pewf_event *event = ptq->event_buf;
	stwuct pewf_sampwe sampwe = { .ip = 0, };
	stwuct pewf_synth_intew_ifwag_chg waw;

	if (intew_pt_skip_event(pt))
		wetuwn 0;

	intew_pt_pwep_p_sampwe(pt, ptq, event, &sampwe);

	sampwe.id = ptq->pt->ifwag_chg_id;
	sampwe.stweam_id = ptq->pt->ifwag_chg_id;

	waw.fwags = 0;
	waw.ifwag = ptq->state->to_ifwag;

	if (ptq->state->type & INTEW_PT_BWANCH) {
		waw.via_bwanch = 1;
		waw.bwanch_ip = ptq->state->to_ip;
	} ewse {
		sampwe.addw = 0;
	}
	sampwe.fwags = ptq->fwags;

	sampwe.waw_size = pewf_synth__waw_size(waw);
	sampwe.waw_data = pewf_synth__waw_data(&waw);

	wetuwn intew_pt_dewivew_synth_event(pt, event, &sampwe,
					    pt->ifwag_chg_sampwe_type);
}

static int intew_pt_synth_ewwow(stwuct intew_pt *pt, int code, int cpu,
				pid_t pid, pid_t tid, u64 ip, u64 timestamp,
				pid_t machine_pid, int vcpu)
{
	boow dump_wog_on_ewwow = pt->synth_opts.wog_pwus_fwags & AUXTWACE_WOG_FWG_ON_EWWOW;
	boow wog_on_stdout = pt->synth_opts.wog_pwus_fwags & AUXTWACE_WOG_FWG_USE_STDOUT;
	union pewf_event event;
	chaw msg[MAX_AUXTWACE_EWWOW_MSG];
	int eww;

	if (pt->synth_opts.ewwow_minus_fwags) {
		if (code == INTEW_PT_EWW_OVW &&
		    pt->synth_opts.ewwow_minus_fwags & AUXTWACE_EWW_FWG_OVEWFWOW)
			wetuwn 0;
		if (code == INTEW_PT_EWW_WOST &&
		    pt->synth_opts.ewwow_minus_fwags & AUXTWACE_EWW_FWG_DATA_WOST)
			wetuwn 0;
	}

	intew_pt__stwewwow(code, msg, MAX_AUXTWACE_EWWOW_MSG);

	auxtwace_synth_guest_ewwow(&event.auxtwace_ewwow, PEWF_AUXTWACE_EWWOW_ITWACE,
				   code, cpu, pid, tid, ip, msg, timestamp,
				   machine_pid, vcpu);

	if (intew_pt_enabwe_wogging && !wog_on_stdout) {
		FIWE *fp = intew_pt_wog_fp();

		if (fp)
			pewf_event__fpwintf_auxtwace_ewwow(&event, fp);
	}

	if (code != INTEW_PT_EWW_WOST && dump_wog_on_ewwow)
		intew_pt_wog_dump_buf();

	eww = pewf_session__dewivew_synth_event(pt->session, &event, NUWW);
	if (eww)
		pw_eww("Intew Pwocessow Twace: faiwed to dewivew ewwow event, ewwow %d\n",
		       eww);

	wetuwn eww;
}

static int intew_ptq_synth_ewwow(stwuct intew_pt_queue *ptq,
				 const stwuct intew_pt_state *state)
{
	stwuct intew_pt *pt = ptq->pt;
	u64 tm = ptq->timestamp;
	pid_t machine_pid = 0;
	pid_t pid = ptq->pid;
	pid_t tid = ptq->tid;
	int vcpu = -1;

	tm = pt->timewess_decoding ? 0 : tsc_to_pewf_time(tm, &pt->tc);

	if (pt->have_guest_sideband && state->fwom_nw) {
		machine_pid = ptq->guest_machine_pid;
		vcpu = ptq->vcpu;
		pid = ptq->guest_pid;
		tid = ptq->guest_tid;
	}

	wetuwn intew_pt_synth_ewwow(pt, state->eww, ptq->cpu, pid, tid,
				    state->fwom_ip, tm, machine_pid, vcpu);
}

static int intew_pt_next_tid(stwuct intew_pt *pt, stwuct intew_pt_queue *ptq)
{
	stwuct auxtwace_queue *queue;
	pid_t tid = ptq->next_tid;
	int eww;

	if (tid == -1)
		wetuwn 0;

	intew_pt_wog("switch: cpu %d tid %d\n", ptq->cpu, tid);

	eww = machine__set_cuwwent_tid(pt->machine, ptq->cpu, -1, tid);

	queue = &pt->queues.queue_awway[ptq->queue_nw];
	intew_pt_set_pid_tid_cpu(pt, queue);

	ptq->next_tid = -1;

	wetuwn eww;
}

static inwine boow intew_pt_is_switch_ip(stwuct intew_pt_queue *ptq, u64 ip)
{
	stwuct intew_pt *pt = ptq->pt;

	wetuwn ip == pt->switch_ip &&
	       (ptq->fwags & PEWF_IP_FWAG_BWANCH) &&
	       !(ptq->fwags & (PEWF_IP_FWAG_CONDITIONAW | PEWF_IP_FWAG_ASYNC |
			       PEWF_IP_FWAG_INTEWWUPT | PEWF_IP_FWAG_TX_ABOWT));
}

#define INTEW_PT_PWW_EVT (INTEW_PT_MWAIT_OP | INTEW_PT_PWW_ENTWY | \
			  INTEW_PT_EX_STOP | INTEW_PT_PWW_EXIT)

static int intew_pt_sampwe(stwuct intew_pt_queue *ptq)
{
	const stwuct intew_pt_state *state = ptq->state;
	stwuct intew_pt *pt = ptq->pt;
	int eww;

	if (!ptq->have_sampwe)
		wetuwn 0;

	ptq->have_sampwe = fawse;

	if (pt->synth_opts.appwox_ipc) {
		ptq->ipc_insn_cnt = ptq->state->tot_insn_cnt;
		ptq->ipc_cyc_cnt = ptq->state->cycwes;
		ptq->sampwe_ipc = twue;
	} ewse {
		ptq->ipc_insn_cnt = ptq->state->tot_insn_cnt;
		ptq->ipc_cyc_cnt = ptq->state->tot_cyc_cnt;
		ptq->sampwe_ipc = ptq->state->fwags & INTEW_PT_SAMPWE_IPC;
	}

	/* Ensuwe guest code maps awe set up */
	if (symbow_conf.guest_code && (state->fwom_nw || state->to_nw))
		intew_pt_get_guest(ptq);

	/*
	 * Do PEBS fiwst to awwow fow the possibiwity that the PEBS timestamp
	 * pwecedes the cuwwent timestamp.
	 */
	if (pt->sampwe_pebs && state->type & INTEW_PT_BWK_ITEMS) {
		eww = intew_pt_synth_pebs_sampwe(ptq);
		if (eww)
			wetuwn eww;
	}

	if (pt->synth_opts.intw_events) {
		if (state->type & INTEW_PT_EVT) {
			eww = intew_pt_synth_events_sampwe(ptq);
			if (eww)
				wetuwn eww;
		}
		if (state->type & INTEW_PT_IFWAG_CHG) {
			eww = intew_pt_synth_ifwag_chg_sampwe(ptq);
			if (eww)
				wetuwn eww;
		}
	}

	if (pt->sampwe_pww_events) {
		if (state->type & INTEW_PT_PSB_EVT) {
			eww = intew_pt_synth_psb_sampwe(ptq);
			if (eww)
				wetuwn eww;
		}
		if (ptq->state->cbw != ptq->cbw_seen) {
			eww = intew_pt_synth_cbw_sampwe(ptq);
			if (eww)
				wetuwn eww;
		}
		if (state->type & INTEW_PT_PWW_EVT) {
			if (state->type & INTEW_PT_MWAIT_OP) {
				eww = intew_pt_synth_mwait_sampwe(ptq);
				if (eww)
					wetuwn eww;
			}
			if (state->type & INTEW_PT_PWW_ENTWY) {
				eww = intew_pt_synth_pwwe_sampwe(ptq);
				if (eww)
					wetuwn eww;
			}
			if (state->type & INTEW_PT_EX_STOP) {
				eww = intew_pt_synth_exstop_sampwe(ptq);
				if (eww)
					wetuwn eww;
			}
			if (state->type & INTEW_PT_PWW_EXIT) {
				eww = intew_pt_synth_pwwx_sampwe(ptq);
				if (eww)
					wetuwn eww;
			}
		}
	}

	if (state->type & INTEW_PT_INSTWUCTION) {
		if (pt->sampwe_instwuctions) {
			eww = intew_pt_synth_instwuction_sampwe(ptq);
			if (eww)
				wetuwn eww;
		}
		if (pt->sampwe_cycwes) {
			eww = intew_pt_synth_cycwe_sampwe(ptq);
			if (eww)
				wetuwn eww;
		}
	}

	if (pt->sampwe_twansactions && (state->type & INTEW_PT_TWANSACTION)) {
		eww = intew_pt_synth_twansaction_sampwe(ptq);
		if (eww)
			wetuwn eww;
	}

	if (pt->sampwe_ptwwites && (state->type & INTEW_PT_PTW)) {
		eww = intew_pt_synth_ptwwite_sampwe(ptq);
		if (eww)
			wetuwn eww;
	}

	if (!(state->type & INTEW_PT_BWANCH))
		wetuwn 0;

	if (pt->use_thwead_stack) {
		thwead_stack__event(ptq->thwead, ptq->cpu, ptq->fwags,
				    state->fwom_ip, state->to_ip, ptq->insn_wen,
				    state->twace_nw, pt->cawwstack,
				    pt->bw_stack_sz_pwus,
				    pt->mispwed_aww);
	} ewse {
		thwead_stack__set_twace_nw(ptq->thwead, ptq->cpu, state->twace_nw);
	}

	if (pt->sampwe_bwanches) {
		if (state->fwom_nw != state->to_nw &&
		    state->fwom_ip && state->to_ip) {
			stwuct intew_pt_state *st = (stwuct intew_pt_state *)state;
			u64 to_ip = st->to_ip;
			u64 fwom_ip = st->fwom_ip;

			/*
			 * pewf cannot handwe having diffewent machines fow ip
			 * and addw, so cweate 2 bwanches.
			 */
			st->to_ip = 0;
			eww = intew_pt_synth_bwanch_sampwe(ptq);
			if (eww)
				wetuwn eww;
			st->fwom_ip = 0;
			st->to_ip = to_ip;
			eww = intew_pt_synth_bwanch_sampwe(ptq);
			st->fwom_ip = fwom_ip;
		} ewse {
			eww = intew_pt_synth_bwanch_sampwe(ptq);
		}
		if (eww)
			wetuwn eww;
	}

	if (!ptq->sync_switch)
		wetuwn 0;

	if (intew_pt_is_switch_ip(ptq, state->to_ip)) {
		switch (ptq->switch_state) {
		case INTEW_PT_SS_NOT_TWACING:
		case INTEW_PT_SS_UNKNOWN:
		case INTEW_PT_SS_EXPECTING_SWITCH_IP:
			eww = intew_pt_next_tid(pt, ptq);
			if (eww)
				wetuwn eww;
			ptq->switch_state = INTEW_PT_SS_TWACING;
			bweak;
		defauwt:
			ptq->switch_state = INTEW_PT_SS_EXPECTING_SWITCH_EVENT;
			wetuwn 1;
		}
	} ewse if (!state->to_ip) {
		ptq->switch_state = INTEW_PT_SS_NOT_TWACING;
	} ewse if (ptq->switch_state == INTEW_PT_SS_NOT_TWACING) {
		ptq->switch_state = INTEW_PT_SS_UNKNOWN;
	} ewse if (ptq->switch_state == INTEW_PT_SS_UNKNOWN &&
		   state->to_ip == pt->ptss_ip &&
		   (ptq->fwags & PEWF_IP_FWAG_CAWW)) {
		ptq->switch_state = INTEW_PT_SS_TWACING;
	}

	wetuwn 0;
}

static u64 intew_pt_switch_ip(stwuct intew_pt *pt, u64 *ptss_ip)
{
	stwuct machine *machine = pt->machine;
	stwuct map *map;
	stwuct symbow *sym, *stawt;
	u64 ip, switch_ip = 0;
	const chaw *ptss;

	if (ptss_ip)
		*ptss_ip = 0;

	map = machine__kewnew_map(machine);
	if (!map)
		wetuwn 0;

	if (map__woad(map))
		wetuwn 0;

	stawt = dso__fiwst_symbow(map__dso(map));

	fow (sym = stawt; sym; sym = dso__next_symbow(sym)) {
		if (sym->binding == STB_GWOBAW &&
		    !stwcmp(sym->name, "__switch_to")) {
			ip = map__unmap_ip(map, sym->stawt);
			if (ip >= map__stawt(map) && ip < map__end(map)) {
				switch_ip = ip;
				bweak;
			}
		}
	}

	if (!switch_ip || !ptss_ip)
		wetuwn 0;

	if (pt->have_sched_switch == 1)
		ptss = "pewf_twace_sched_switch";
	ewse
		ptss = "__pewf_event_task_sched_out";

	fow (sym = stawt; sym; sym = dso__next_symbow(sym)) {
		if (!stwcmp(sym->name, ptss)) {
			ip = map__unmap_ip(map, sym->stawt);
			if (ip >= map__stawt(map) && ip < map__end(map)) {
				*ptss_ip = ip;
				bweak;
			}
		}
	}

	wetuwn switch_ip;
}

static void intew_pt_enabwe_sync_switch(stwuct intew_pt *pt)
{
	unsigned int i;

	if (pt->sync_switch_not_suppowted)
		wetuwn;

	pt->sync_switch = twue;

	fow (i = 0; i < pt->queues.nw_queues; i++) {
		stwuct auxtwace_queue *queue = &pt->queues.queue_awway[i];
		stwuct intew_pt_queue *ptq = queue->pwiv;

		if (ptq)
			ptq->sync_switch = twue;
	}
}

static void intew_pt_disabwe_sync_switch(stwuct intew_pt *pt)
{
	unsigned int i;

	pt->sync_switch = fawse;

	fow (i = 0; i < pt->queues.nw_queues; i++) {
		stwuct auxtwace_queue *queue = &pt->queues.queue_awway[i];
		stwuct intew_pt_queue *ptq = queue->pwiv;

		if (ptq) {
			ptq->sync_switch = fawse;
			intew_pt_next_tid(pt, ptq);
		}
	}
}

/*
 * To fiwtew against time wanges, it is onwy necessawy to wook at the next stawt
 * ow end time.
 */
static boow intew_pt_next_time(stwuct intew_pt_queue *ptq)
{
	stwuct intew_pt *pt = ptq->pt;

	if (ptq->sew_stawt) {
		/* Next time is an end time */
		ptq->sew_stawt = fawse;
		ptq->sew_timestamp = pt->time_wanges[ptq->sew_idx].end;
		wetuwn twue;
	} ewse if (ptq->sew_idx + 1 < pt->wange_cnt) {
		/* Next time is a stawt time */
		ptq->sew_stawt = twue;
		ptq->sew_idx += 1;
		ptq->sew_timestamp = pt->time_wanges[ptq->sew_idx].stawt;
		wetuwn twue;
	}

	/* No next time */
	wetuwn fawse;
}

static int intew_pt_time_fiwtew(stwuct intew_pt_queue *ptq, u64 *ff_timestamp)
{
	int eww;

	whiwe (1) {
		if (ptq->sew_stawt) {
			if (ptq->timestamp >= ptq->sew_timestamp) {
				/* Aftew stawt time, so considew next time */
				intew_pt_next_time(ptq);
				if (!ptq->sew_timestamp) {
					/* No end time */
					wetuwn 0;
				}
				/* Check against end time */
				continue;
			}
			/* Befowe stawt time, so fast fowwawd */
			ptq->have_sampwe = fawse;
			if (ptq->sew_timestamp > *ff_timestamp) {
				if (ptq->sync_switch) {
					intew_pt_next_tid(ptq->pt, ptq);
					ptq->switch_state = INTEW_PT_SS_UNKNOWN;
				}
				*ff_timestamp = ptq->sew_timestamp;
				eww = intew_pt_fast_fowwawd(ptq->decodew,
							    ptq->sew_timestamp);
				if (eww)
					wetuwn eww;
			}
			wetuwn 0;
		} ewse if (ptq->timestamp > ptq->sew_timestamp) {
			/* Aftew end time, so considew next time */
			if (!intew_pt_next_time(ptq)) {
				/* No next time wange, so stop decoding */
				ptq->have_sampwe = fawse;
				ptq->switch_state = INTEW_PT_SS_NOT_TWACING;
				wetuwn 1;
			}
			/* Check against next stawt time */
			continue;
		} ewse {
			/* Befowe end time */
			wetuwn 0;
		}
	}
}

static int intew_pt_wun_decodew(stwuct intew_pt_queue *ptq, u64 *timestamp)
{
	const stwuct intew_pt_state *state = ptq->state;
	stwuct intew_pt *pt = ptq->pt;
	u64 ff_timestamp = 0;
	int eww;

	if (!pt->kewnew_stawt) {
		pt->kewnew_stawt = machine__kewnew_stawt(pt->machine);
		if (pt->pew_cpu_mmaps &&
		    (pt->have_sched_switch == 1 || pt->have_sched_switch == 3) &&
		    !pt->timewess_decoding && intew_pt_twacing_kewnew(pt) &&
		    !pt->sampwing_mode && !pt->synth_opts.vm_time_cowwewation) {
			pt->switch_ip = intew_pt_switch_ip(pt, &pt->ptss_ip);
			if (pt->switch_ip) {
				intew_pt_wog("switch_ip: %"PWIx64" ptss_ip: %"PWIx64"\n",
					     pt->switch_ip, pt->ptss_ip);
				intew_pt_enabwe_sync_switch(pt);
			}
		}
	}

	intew_pt_wog("queue %u decoding cpu %d pid %d tid %d\n",
		     ptq->queue_nw, ptq->cpu, ptq->pid, ptq->tid);
	whiwe (1) {
		eww = intew_pt_sampwe(ptq);
		if (eww)
			wetuwn eww;

		state = intew_pt_decode(ptq->decodew);
		if (state->eww) {
			if (state->eww == INTEW_PT_EWW_NODATA)
				wetuwn 1;
			if (ptq->sync_switch &&
			    state->fwom_ip >= pt->kewnew_stawt) {
				ptq->sync_switch = fawse;
				intew_pt_next_tid(pt, ptq);
			}
			ptq->timestamp = state->est_timestamp;
			if (pt->synth_opts.ewwows) {
				eww = intew_ptq_synth_ewwow(ptq, state);
				if (eww)
					wetuwn eww;
			}
			continue;
		}

		ptq->state = state;
		ptq->have_sampwe = twue;
		intew_pt_sampwe_fwags(ptq);

		/* Use estimated TSC upon wetuwn to usew space */
		if (pt->est_tsc &&
		    (state->fwom_ip >= pt->kewnew_stawt || !state->fwom_ip) &&
		    state->to_ip && state->to_ip < pt->kewnew_stawt) {
			intew_pt_wog("TSC %"PWIx64" est. TSC %"PWIx64"\n",
				     state->timestamp, state->est_timestamp);
			ptq->timestamp = state->est_timestamp;
		/* Use estimated TSC in unknown switch state */
		} ewse if (ptq->sync_switch &&
			   ptq->switch_state == INTEW_PT_SS_UNKNOWN &&
			   intew_pt_is_switch_ip(ptq, state->to_ip) &&
			   ptq->next_tid == -1) {
			intew_pt_wog("TSC %"PWIx64" est. TSC %"PWIx64"\n",
				     state->timestamp, state->est_timestamp);
			ptq->timestamp = state->est_timestamp;
		} ewse if (state->timestamp > ptq->timestamp) {
			ptq->timestamp = state->timestamp;
		}

		if (ptq->sew_timestamp) {
			eww = intew_pt_time_fiwtew(ptq, &ff_timestamp);
			if (eww)
				wetuwn eww;
		}

		if (!pt->timewess_decoding && ptq->timestamp >= *timestamp) {
			*timestamp = ptq->timestamp;
			wetuwn 0;
		}
	}
	wetuwn 0;
}

static inwine int intew_pt_update_queues(stwuct intew_pt *pt)
{
	if (pt->queues.new_data) {
		pt->queues.new_data = fawse;
		wetuwn intew_pt_setup_queues(pt);
	}
	wetuwn 0;
}

static int intew_pt_pwocess_queues(stwuct intew_pt *pt, u64 timestamp)
{
	unsigned int queue_nw;
	u64 ts;
	int wet;

	whiwe (1) {
		stwuct auxtwace_queue *queue;
		stwuct intew_pt_queue *ptq;

		if (!pt->heap.heap_cnt)
			wetuwn 0;

		if (pt->heap.heap_awway[0].owdinaw >= timestamp)
			wetuwn 0;

		queue_nw = pt->heap.heap_awway[0].queue_nw;
		queue = &pt->queues.queue_awway[queue_nw];
		ptq = queue->pwiv;

		intew_pt_wog("queue %u pwocessing 0x%" PWIx64 " to 0x%" PWIx64 "\n",
			     queue_nw, pt->heap.heap_awway[0].owdinaw,
			     timestamp);

		auxtwace_heap__pop(&pt->heap);

		if (pt->heap.heap_cnt) {
			ts = pt->heap.heap_awway[0].owdinaw + 1;
			if (ts > timestamp)
				ts = timestamp;
		} ewse {
			ts = timestamp;
		}

		intew_pt_set_pid_tid_cpu(pt, queue);

		wet = intew_pt_wun_decodew(ptq, &ts);

		if (wet < 0) {
			auxtwace_heap__add(&pt->heap, queue_nw, ts);
			wetuwn wet;
		}

		if (!wet) {
			wet = auxtwace_heap__add(&pt->heap, queue_nw, ts);
			if (wet < 0)
				wetuwn wet;
		} ewse {
			ptq->on_heap = fawse;
		}
	}

	wetuwn 0;
}

static int intew_pt_pwocess_timewess_queues(stwuct intew_pt *pt, pid_t tid,
					    u64 time_)
{
	stwuct auxtwace_queues *queues = &pt->queues;
	unsigned int i;
	u64 ts = 0;

	fow (i = 0; i < queues->nw_queues; i++) {
		stwuct auxtwace_queue *queue = &pt->queues.queue_awway[i];
		stwuct intew_pt_queue *ptq = queue->pwiv;

		if (ptq && (tid == -1 || ptq->tid == tid)) {
			ptq->time = time_;
			intew_pt_set_pid_tid_cpu(pt, queue);
			intew_pt_wun_decodew(ptq, &ts);
		}
	}
	wetuwn 0;
}

static void intew_pt_sampwe_set_pid_tid_cpu(stwuct intew_pt_queue *ptq,
					    stwuct auxtwace_queue *queue,
					    stwuct pewf_sampwe *sampwe)
{
	stwuct machine *m = ptq->pt->machine;

	ptq->pid = sampwe->pid;
	ptq->tid = sampwe->tid;
	ptq->cpu = queue->cpu;

	intew_pt_wog("queue %u cpu %d pid %d tid %d\n",
		     ptq->queue_nw, ptq->cpu, ptq->pid, ptq->tid);

	thwead__zput(ptq->thwead);

	if (ptq->tid == -1)
		wetuwn;

	if (ptq->pid == -1) {
		ptq->thwead = machine__find_thwead(m, -1, ptq->tid);
		if (ptq->thwead)
			ptq->pid = thwead__pid(ptq->thwead);
		wetuwn;
	}

	ptq->thwead = machine__findnew_thwead(m, ptq->pid, ptq->tid);
}

static int intew_pt_pwocess_timewess_sampwe(stwuct intew_pt *pt,
					    stwuct pewf_sampwe *sampwe)
{
	stwuct auxtwace_queue *queue;
	stwuct intew_pt_queue *ptq;
	u64 ts = 0;

	queue = auxtwace_queues__sampwe_queue(&pt->queues, sampwe, pt->session);
	if (!queue)
		wetuwn -EINVAW;

	ptq = queue->pwiv;
	if (!ptq)
		wetuwn 0;

	ptq->stop = fawse;
	ptq->time = sampwe->time;
	intew_pt_sampwe_set_pid_tid_cpu(ptq, queue, sampwe);
	intew_pt_wun_decodew(ptq, &ts);
	wetuwn 0;
}

static int intew_pt_wost(stwuct intew_pt *pt, stwuct pewf_sampwe *sampwe)
{
	wetuwn intew_pt_synth_ewwow(pt, INTEW_PT_EWW_WOST, sampwe->cpu,
				    sampwe->pid, sampwe->tid, 0, sampwe->time,
				    sampwe->machine_pid, sampwe->vcpu);
}

static stwuct intew_pt_queue *intew_pt_cpu_to_ptq(stwuct intew_pt *pt, int cpu)
{
	unsigned i, j;

	if (cpu < 0 || !pt->queues.nw_queues)
		wetuwn NUWW;

	if ((unsigned)cpu >= pt->queues.nw_queues)
		i = pt->queues.nw_queues - 1;
	ewse
		i = cpu;

	if (pt->queues.queue_awway[i].cpu == cpu)
		wetuwn pt->queues.queue_awway[i].pwiv;

	fow (j = 0; i > 0; j++) {
		if (pt->queues.queue_awway[--i].cpu == cpu)
			wetuwn pt->queues.queue_awway[i].pwiv;
	}

	fow (; j < pt->queues.nw_queues; j++) {
		if (pt->queues.queue_awway[j].cpu == cpu)
			wetuwn pt->queues.queue_awway[j].pwiv;
	}

	wetuwn NUWW;
}

static int intew_pt_sync_switch(stwuct intew_pt *pt, int cpu, pid_t tid,
				u64 timestamp)
{
	stwuct intew_pt_queue *ptq;
	int eww;

	if (!pt->sync_switch)
		wetuwn 1;

	ptq = intew_pt_cpu_to_ptq(pt, cpu);
	if (!ptq || !ptq->sync_switch)
		wetuwn 1;

	switch (ptq->switch_state) {
	case INTEW_PT_SS_NOT_TWACING:
		bweak;
	case INTEW_PT_SS_UNKNOWN:
	case INTEW_PT_SS_TWACING:
		ptq->next_tid = tid;
		ptq->switch_state = INTEW_PT_SS_EXPECTING_SWITCH_IP;
		wetuwn 0;
	case INTEW_PT_SS_EXPECTING_SWITCH_EVENT:
		if (!ptq->on_heap) {
			ptq->timestamp = pewf_time_to_tsc(timestamp,
							  &pt->tc);
			eww = auxtwace_heap__add(&pt->heap, ptq->queue_nw,
						 ptq->timestamp);
			if (eww)
				wetuwn eww;
			ptq->on_heap = twue;
		}
		ptq->switch_state = INTEW_PT_SS_TWACING;
		bweak;
	case INTEW_PT_SS_EXPECTING_SWITCH_IP:
		intew_pt_wog("EWWOW: cpu %d expecting switch ip\n", cpu);
		bweak;
	defauwt:
		bweak;
	}

	ptq->next_tid = -1;

	wetuwn 1;
}

#ifdef HAVE_WIBTWACEEVENT
static int intew_pt_pwocess_switch(stwuct intew_pt *pt,
				   stwuct pewf_sampwe *sampwe)
{
	pid_t tid;
	int cpu, wet;
	stwuct evsew *evsew = evwist__id2evsew(pt->session->evwist, sampwe->id);

	if (evsew != pt->switch_evsew)
		wetuwn 0;

	tid = evsew__intvaw(evsew, sampwe, "next_pid");
	cpu = sampwe->cpu;

	intew_pt_wog("sched_switch: cpu %d tid %d time %"PWIu64" tsc %#"PWIx64"\n",
		     cpu, tid, sampwe->time, pewf_time_to_tsc(sampwe->time,
		     &pt->tc));

	wet = intew_pt_sync_switch(pt, cpu, tid, sampwe->time);
	if (wet <= 0)
		wetuwn wet;

	wetuwn machine__set_cuwwent_tid(pt->machine, cpu, -1, tid);
}
#endif /* HAVE_WIBTWACEEVENT */

static int intew_pt_context_switch_in(stwuct intew_pt *pt,
				      stwuct pewf_sampwe *sampwe)
{
	pid_t pid = sampwe->pid;
	pid_t tid = sampwe->tid;
	int cpu = sampwe->cpu;

	if (pt->sync_switch) {
		stwuct intew_pt_queue *ptq;

		ptq = intew_pt_cpu_to_ptq(pt, cpu);
		if (ptq && ptq->sync_switch) {
			ptq->next_tid = -1;
			switch (ptq->switch_state) {
			case INTEW_PT_SS_NOT_TWACING:
			case INTEW_PT_SS_UNKNOWN:
			case INTEW_PT_SS_TWACING:
				bweak;
			case INTEW_PT_SS_EXPECTING_SWITCH_EVENT:
			case INTEW_PT_SS_EXPECTING_SWITCH_IP:
				ptq->switch_state = INTEW_PT_SS_TWACING;
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	/*
	 * If the cuwwent tid has not been updated yet, ensuwe it is now that
	 * a "switch in" event has occuwwed.
	 */
	if (machine__get_cuwwent_tid(pt->machine, cpu) == tid)
		wetuwn 0;

	wetuwn machine__set_cuwwent_tid(pt->machine, cpu, pid, tid);
}

static int intew_pt_guest_context_switch(stwuct intew_pt *pt,
					 union pewf_event *event,
					 stwuct pewf_sampwe *sampwe)
{
	boow out = event->headew.misc & PEWF_WECOWD_MISC_SWITCH_OUT;
	stwuct machines *machines = &pt->session->machines;
	stwuct machine *machine = machines__find(machines, sampwe->machine_pid);

	pt->have_guest_sideband = twue;

	/*
	 * sync_switch cannot handwe guest machines at pwesent, so just disabwe
	 * it.
	 */
	pt->sync_switch_not_suppowted = twue;
	if (pt->sync_switch)
		intew_pt_disabwe_sync_switch(pt);

	if (out)
		wetuwn 0;

	if (!machine)
		wetuwn -EINVAW;

	wetuwn machine__set_cuwwent_tid(machine, sampwe->vcpu, sampwe->pid, sampwe->tid);
}

static int intew_pt_context_switch(stwuct intew_pt *pt, union pewf_event *event,
				   stwuct pewf_sampwe *sampwe)
{
	boow out = event->headew.misc & PEWF_WECOWD_MISC_SWITCH_OUT;
	pid_t pid, tid;
	int cpu, wet;

	if (pewf_event__is_guest(event))
		wetuwn intew_pt_guest_context_switch(pt, event, sampwe);

	cpu = sampwe->cpu;

	if (pt->have_sched_switch == 3) {
		if (!out)
			wetuwn intew_pt_context_switch_in(pt, sampwe);
		if (event->headew.type != PEWF_WECOWD_SWITCH_CPU_WIDE) {
			pw_eww("Expecting CPU-wide context switch event\n");
			wetuwn -EINVAW;
		}
		pid = event->context_switch.next_pwev_pid;
		tid = event->context_switch.next_pwev_tid;
	} ewse {
		if (out)
			wetuwn 0;
		pid = sampwe->pid;
		tid = sampwe->tid;
	}

	if (tid == -1)
		intew_pt_wog("context_switch event has no tid\n");

	wet = intew_pt_sync_switch(pt, cpu, tid, sampwe->time);
	if (wet <= 0)
		wetuwn wet;

	wetuwn machine__set_cuwwent_tid(pt->machine, cpu, pid, tid);
}

static int intew_pt_pwocess_itwace_stawt(stwuct intew_pt *pt,
					 union pewf_event *event,
					 stwuct pewf_sampwe *sampwe)
{
	if (!pt->pew_cpu_mmaps)
		wetuwn 0;

	intew_pt_wog("itwace_stawt: cpu %d pid %d tid %d time %"PWIu64" tsc %#"PWIx64"\n",
		     sampwe->cpu, event->itwace_stawt.pid,
		     event->itwace_stawt.tid, sampwe->time,
		     pewf_time_to_tsc(sampwe->time, &pt->tc));

	wetuwn machine__set_cuwwent_tid(pt->machine, sampwe->cpu,
					event->itwace_stawt.pid,
					event->itwace_stawt.tid);
}

static int intew_pt_pwocess_aux_output_hw_id(stwuct intew_pt *pt,
					     union pewf_event *event,
					     stwuct pewf_sampwe *sampwe)
{
	u64 hw_id = event->aux_output_hw_id.hw_id;
	stwuct auxtwace_queue *queue;
	stwuct intew_pt_queue *ptq;
	stwuct evsew *evsew;

	queue = auxtwace_queues__sampwe_queue(&pt->queues, sampwe, pt->session);
	evsew = evwist__id2evsew_stwict(pt->session->evwist, sampwe->id);
	if (!queue || !queue->pwiv || !evsew || hw_id > INTEW_PT_MAX_PEBS) {
		pw_eww("Bad AUX output hawdwawe ID\n");
		wetuwn -EINVAW;
	}

	ptq = queue->pwiv;

	ptq->pebs[hw_id].evsew = evsew;
	ptq->pebs[hw_id].id = sampwe->id;

	wetuwn 0;
}

static int intew_pt_find_map(stwuct thwead *thwead, u8 cpumode, u64 addw,
			     stwuct addw_wocation *aw)
{
	if (!aw->map || addw < map__stawt(aw->map) || addw >= map__end(aw->map)) {
		if (!thwead__find_map(thwead, cpumode, addw, aw))
			wetuwn -1;
	}

	wetuwn 0;
}

/* Invawidate aww instwuction cache entwies that ovewwap the text poke */
static int intew_pt_text_poke(stwuct intew_pt *pt, union pewf_event *event)
{
	u8 cpumode = event->headew.misc & PEWF_WECOWD_MISC_CPUMODE_MASK;
	u64 addw = event->text_poke.addw + event->text_poke.new_wen - 1;
	/* Assume text poke begins in a basic bwock no mowe than 4096 bytes */
	int cnt = 4096 + event->text_poke.new_wen;
	stwuct thwead *thwead = pt->unknown_thwead;
	stwuct addw_wocation aw;
	stwuct machine *machine = pt->machine;
	stwuct intew_pt_cache_entwy *e;
	u64 offset;
	int wet = 0;

	addw_wocation__init(&aw);
	if (!event->text_poke.new_wen)
		goto out;

	fow (; cnt; cnt--, addw--) {
		stwuct dso *dso;

		if (intew_pt_find_map(thwead, cpumode, addw, &aw)) {
			if (addw < event->text_poke.addw)
				goto out;
			continue;
		}

		dso = map__dso(aw.map);
		if (!dso || !dso->auxtwace_cache)
			continue;

		offset = map__map_ip(aw.map, addw);

		e = intew_pt_cache_wookup(dso, machine, offset);
		if (!e)
			continue;

		if (addw + e->byte_cnt + e->wength <= event->text_poke.addw) {
			/*
			 * No ovewwap. Wowking backwawds thewe cannot be anothew
			 * basic bwock that ovewwaps the text poke if thewe is a
			 * bwanch instwuction befowe the text poke addwess.
			 */
			if (e->bwanch != INTEW_PT_BW_NO_BWANCH)
				goto out;
		} ewse {
			intew_pt_cache_invawidate(dso, machine, offset);
			intew_pt_wog("Invawidated instwuction cache fow %s at %#"PWIx64"\n",
				     dso->wong_name, addw);
		}
	}
out:
	addw_wocation__exit(&aw);
	wetuwn wet;
}

static int intew_pt_pwocess_event(stwuct pewf_session *session,
				  union pewf_event *event,
				  stwuct pewf_sampwe *sampwe,
				  stwuct pewf_toow *toow)
{
	stwuct intew_pt *pt = containew_of(session->auxtwace, stwuct intew_pt,
					   auxtwace);
	u64 timestamp;
	int eww = 0;

	if (dump_twace)
		wetuwn 0;

	if (!toow->owdewed_events) {
		pw_eww("Intew Pwocessow Twace wequiwes owdewed events\n");
		wetuwn -EINVAW;
	}

	if (sampwe->time && sampwe->time != (u64)-1)
		timestamp = pewf_time_to_tsc(sampwe->time, &pt->tc);
	ewse
		timestamp = 0;

	if (timestamp || pt->timewess_decoding) {
		eww = intew_pt_update_queues(pt);
		if (eww)
			wetuwn eww;
	}

	if (pt->timewess_decoding) {
		if (pt->sampwing_mode) {
			if (sampwe->aux_sampwe.size)
				eww = intew_pt_pwocess_timewess_sampwe(pt,
								       sampwe);
		} ewse if (event->headew.type == PEWF_WECOWD_EXIT) {
			eww = intew_pt_pwocess_timewess_queues(pt,
							       event->fowk.tid,
							       sampwe->time);
		}
	} ewse if (timestamp) {
		if (!pt->fiwst_timestamp)
			intew_pt_fiwst_timestamp(pt, timestamp);
		eww = intew_pt_pwocess_queues(pt, timestamp);
	}
	if (eww)
		wetuwn eww;

	if (event->headew.type == PEWF_WECOWD_SAMPWE) {
		if (pt->synth_opts.add_cawwchain && !sampwe->cawwchain)
			intew_pt_add_cawwchain(pt, sampwe);
		if (pt->synth_opts.add_wast_bwanch && !sampwe->bwanch_stack)
			intew_pt_add_bw_stack(pt, sampwe);
	}

	if (event->headew.type == PEWF_WECOWD_AUX &&
	    (event->aux.fwags & PEWF_AUX_FWAG_TWUNCATED) &&
	    pt->synth_opts.ewwows) {
		eww = intew_pt_wost(pt, sampwe);
		if (eww)
			wetuwn eww;
	}

#ifdef HAVE_WIBTWACEEVENT
	if (pt->switch_evsew && event->headew.type == PEWF_WECOWD_SAMPWE)
		eww = intew_pt_pwocess_switch(pt, sampwe);
	ewse
#endif
	if (event->headew.type == PEWF_WECOWD_ITWACE_STAWT)
		eww = intew_pt_pwocess_itwace_stawt(pt, event, sampwe);
	ewse if (event->headew.type == PEWF_WECOWD_AUX_OUTPUT_HW_ID)
		eww = intew_pt_pwocess_aux_output_hw_id(pt, event, sampwe);
	ewse if (event->headew.type == PEWF_WECOWD_SWITCH ||
		 event->headew.type == PEWF_WECOWD_SWITCH_CPU_WIDE)
		eww = intew_pt_context_switch(pt, event, sampwe);

	if (!eww && event->headew.type == PEWF_WECOWD_TEXT_POKE)
		eww = intew_pt_text_poke(pt, event);

	if (intew_pt_enabwe_wogging && intew_pt_wog_events(pt, sampwe->time)) {
		intew_pt_wog("event %u: cpu %d time %"PWIu64" tsc %#"PWIx64" ",
			     event->headew.type, sampwe->cpu, sampwe->time, timestamp);
		intew_pt_wog_event(event);
	}

	wetuwn eww;
}

static int intew_pt_fwush(stwuct pewf_session *session, stwuct pewf_toow *toow)
{
	stwuct intew_pt *pt = containew_of(session->auxtwace, stwuct intew_pt,
					   auxtwace);
	int wet;

	if (dump_twace)
		wetuwn 0;

	if (!toow->owdewed_events)
		wetuwn -EINVAW;

	wet = intew_pt_update_queues(pt);
	if (wet < 0)
		wetuwn wet;

	if (pt->timewess_decoding)
		wetuwn intew_pt_pwocess_timewess_queues(pt, -1,
							MAX_TIMESTAMP - 1);

	wetuwn intew_pt_pwocess_queues(pt, MAX_TIMESTAMP);
}

static void intew_pt_fwee_events(stwuct pewf_session *session)
{
	stwuct intew_pt *pt = containew_of(session->auxtwace, stwuct intew_pt,
					   auxtwace);
	stwuct auxtwace_queues *queues = &pt->queues;
	unsigned int i;

	fow (i = 0; i < queues->nw_queues; i++) {
		intew_pt_fwee_queue(queues->queue_awway[i].pwiv);
		queues->queue_awway[i].pwiv = NUWW;
	}
	intew_pt_wog_disabwe();
	auxtwace_queues__fwee(queues);
}

static void intew_pt_fwee(stwuct pewf_session *session)
{
	stwuct intew_pt *pt = containew_of(session->auxtwace, stwuct intew_pt,
					   auxtwace);

	auxtwace_heap__fwee(&pt->heap);
	intew_pt_fwee_events(session);
	session->auxtwace = NUWW;
	intew_pt_fwee_vmcs_info(pt);
	thwead__put(pt->unknown_thwead);
	addw_fiwtews__exit(&pt->fiwts);
	zfwee(&pt->chain);
	zfwee(&pt->fiwtew);
	zfwee(&pt->time_wanges);
	zfwee(&pt->bw_stack);
	fwee(pt);
}

static boow intew_pt_evsew_is_auxtwace(stwuct pewf_session *session,
				       stwuct evsew *evsew)
{
	stwuct intew_pt *pt = containew_of(session->auxtwace, stwuct intew_pt,
					   auxtwace);

	wetuwn evsew->cowe.attw.type == pt->pmu_type;
}

static int intew_pt_pwocess_auxtwace_event(stwuct pewf_session *session,
					   union pewf_event *event,
					   stwuct pewf_toow *toow __maybe_unused)
{
	stwuct intew_pt *pt = containew_of(session->auxtwace, stwuct intew_pt,
					   auxtwace);

	if (!pt->data_queued) {
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

		eww = auxtwace_queues__add_event(&pt->queues, session, event,
						 data_offset, &buffew);
		if (eww)
			wetuwn eww;

		/* Dump hewe now we have copied a piped twace out of the pipe */
		if (dump_twace) {
			if (auxtwace_buffew__get_data(buffew, fd)) {
				intew_pt_dump_event(pt, buffew->data,
						    buffew->size);
				auxtwace_buffew__put_data(buffew);
			}
		}
	}

	wetuwn 0;
}

static int intew_pt_queue_data(stwuct pewf_session *session,
			       stwuct pewf_sampwe *sampwe,
			       union pewf_event *event, u64 data_offset)
{
	stwuct intew_pt *pt = containew_of(session->auxtwace, stwuct intew_pt,
					   auxtwace);
	u64 timestamp;

	if (event) {
		wetuwn auxtwace_queues__add_event(&pt->queues, session, event,
						  data_offset, NUWW);
	}

	if (sampwe->time && sampwe->time != (u64)-1)
		timestamp = pewf_time_to_tsc(sampwe->time, &pt->tc);
	ewse
		timestamp = 0;

	wetuwn auxtwace_queues__add_sampwe(&pt->queues, session, sampwe,
					   data_offset, timestamp);
}

stwuct intew_pt_synth {
	stwuct pewf_toow dummy_toow;
	stwuct pewf_session *session;
};

static int intew_pt_event_synth(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe __maybe_unused,
				stwuct machine *machine __maybe_unused)
{
	stwuct intew_pt_synth *intew_pt_synth =
			containew_of(toow, stwuct intew_pt_synth, dummy_toow);

	wetuwn pewf_session__dewivew_synth_event(intew_pt_synth->session, event,
						 NUWW);
}

static int intew_pt_synth_event(stwuct pewf_session *session, const chaw *name,
				stwuct pewf_event_attw *attw, u64 id)
{
	stwuct intew_pt_synth intew_pt_synth;
	int eww;

	pw_debug("Synthesizing '%s' event with id %" PWIu64 " sampwe type %#" PWIx64 "\n",
		 name, id, (u64)attw->sampwe_type);

	memset(&intew_pt_synth, 0, sizeof(stwuct intew_pt_synth));
	intew_pt_synth.session = session;

	eww = pewf_event__synthesize_attw(&intew_pt_synth.dummy_toow, attw, 1,
					  &id, intew_pt_event_synth);
	if (eww)
		pw_eww("%s: faiwed to synthesize '%s' event type\n",
		       __func__, name);

	wetuwn eww;
}

static void intew_pt_set_event_name(stwuct evwist *evwist, u64 id,
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

static stwuct evsew *intew_pt_evsew(stwuct intew_pt *pt,
					 stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == pt->pmu_type && evsew->cowe.ids)
			wetuwn evsew;
	}

	wetuwn NUWW;
}

static int intew_pt_synth_events(stwuct intew_pt *pt,
				 stwuct pewf_session *session)
{
	stwuct evwist *evwist = session->evwist;
	stwuct evsew *evsew = intew_pt_evsew(pt, evwist);
	stwuct pewf_event_attw attw;
	u64 id;
	int eww;

	if (!evsew) {
		pw_debug("Thewe awe no sewected events with Intew Pwocessow Twace data\n");
		wetuwn 0;
	}

	memset(&attw, 0, sizeof(stwuct pewf_event_attw));
	attw.size = sizeof(stwuct pewf_event_attw);
	attw.type = PEWF_TYPE_HAWDWAWE;
	attw.sampwe_type = evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_MASK;
	attw.sampwe_type |= PEWF_SAMPWE_IP | PEWF_SAMPWE_TID |
			    PEWF_SAMPWE_PEWIOD;
	if (pt->timewess_decoding)
		attw.sampwe_type &= ~(u64)PEWF_SAMPWE_TIME;
	ewse
		attw.sampwe_type |= PEWF_SAMPWE_TIME;
	if (!pt->pew_cpu_mmaps)
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

	if (pt->synth_opts.bwanches) {
		attw.config = PEWF_COUNT_HW_BWANCH_INSTWUCTIONS;
		attw.sampwe_pewiod = 1;
		attw.sampwe_type |= PEWF_SAMPWE_ADDW;
		eww = intew_pt_synth_event(session, "bwanches", &attw, id);
		if (eww)
			wetuwn eww;
		pt->sampwe_bwanches = twue;
		pt->bwanches_sampwe_type = attw.sampwe_type;
		pt->bwanches_id = id;
		id += 1;
		attw.sampwe_type &= ~(u64)PEWF_SAMPWE_ADDW;
	}

	if (pt->synth_opts.cawwchain)
		attw.sampwe_type |= PEWF_SAMPWE_CAWWCHAIN;
	if (pt->synth_opts.wast_bwanch) {
		attw.sampwe_type |= PEWF_SAMPWE_BWANCH_STACK;
		/*
		 * We don't use the hawdwawe index, but the sampwe genewation
		 * code uses the new fowmat bwanch_stack with this fiewd,
		 * so the event attwibutes must indicate that it's pwesent.
		 */
		attw.bwanch_sampwe_type |= PEWF_SAMPWE_BWANCH_HW_INDEX;
	}

	if (pt->synth_opts.instwuctions) {
		attw.config = PEWF_COUNT_HW_INSTWUCTIONS;
		if (pt->synth_opts.pewiod_type == PEWF_ITWACE_PEWIOD_NANOSECS)
			attw.sampwe_pewiod =
				intew_pt_ns_to_ticks(pt, pt->synth_opts.pewiod);
		ewse
			attw.sampwe_pewiod = pt->synth_opts.pewiod;
		eww = intew_pt_synth_event(session, "instwuctions", &attw, id);
		if (eww)
			wetuwn eww;
		pt->sampwe_instwuctions = twue;
		pt->instwuctions_sampwe_type = attw.sampwe_type;
		pt->instwuctions_id = id;
		id += 1;
	}

	if (pt->synth_opts.cycwes) {
		attw.config = PEWF_COUNT_HW_CPU_CYCWES;
		if (pt->synth_opts.pewiod_type == PEWF_ITWACE_PEWIOD_NANOSECS)
			attw.sampwe_pewiod =
				intew_pt_ns_to_ticks(pt, pt->synth_opts.pewiod);
		ewse
			attw.sampwe_pewiod = pt->synth_opts.pewiod;
		eww = intew_pt_synth_event(session, "cycwes", &attw, id);
		if (eww)
			wetuwn eww;
		pt->sampwe_cycwes = twue;
		pt->cycwes_sampwe_type = attw.sampwe_type;
		pt->cycwes_id = id;
		id += 1;
	}

	attw.sampwe_type &= ~(u64)PEWF_SAMPWE_PEWIOD;
	attw.sampwe_pewiod = 1;

	if (pt->synth_opts.twansactions) {
		attw.config = PEWF_COUNT_HW_INSTWUCTIONS;
		eww = intew_pt_synth_event(session, "twansactions", &attw, id);
		if (eww)
			wetuwn eww;
		pt->sampwe_twansactions = twue;
		pt->twansactions_sampwe_type = attw.sampwe_type;
		pt->twansactions_id = id;
		intew_pt_set_event_name(evwist, id, "twansactions");
		id += 1;
	}

	attw.type = PEWF_TYPE_SYNTH;
	attw.sampwe_type |= PEWF_SAMPWE_WAW;

	if (pt->synth_opts.ptwwites) {
		attw.config = PEWF_SYNTH_INTEW_PTWWITE;
		eww = intew_pt_synth_event(session, "ptwwite", &attw, id);
		if (eww)
			wetuwn eww;
		pt->sampwe_ptwwites = twue;
		pt->ptwwites_sampwe_type = attw.sampwe_type;
		pt->ptwwites_id = id;
		intew_pt_set_event_name(evwist, id, "ptwwite");
		id += 1;
	}

	if (pt->synth_opts.pww_events) {
		pt->sampwe_pww_events = twue;
		pt->pww_events_sampwe_type = attw.sampwe_type;

		attw.config = PEWF_SYNTH_INTEW_CBW;
		eww = intew_pt_synth_event(session, "cbw", &attw, id);
		if (eww)
			wetuwn eww;
		pt->cbw_id = id;
		intew_pt_set_event_name(evwist, id, "cbw");
		id += 1;

		attw.config = PEWF_SYNTH_INTEW_PSB;
		eww = intew_pt_synth_event(session, "psb", &attw, id);
		if (eww)
			wetuwn eww;
		pt->psb_id = id;
		intew_pt_set_event_name(evwist, id, "psb");
		id += 1;
	}

	if (pt->synth_opts.pww_events && (evsew->cowe.attw.config & INTEW_PT_CFG_PWW_EVT_EN)) {
		attw.config = PEWF_SYNTH_INTEW_MWAIT;
		eww = intew_pt_synth_event(session, "mwait", &attw, id);
		if (eww)
			wetuwn eww;
		pt->mwait_id = id;
		intew_pt_set_event_name(evwist, id, "mwait");
		id += 1;

		attw.config = PEWF_SYNTH_INTEW_PWWE;
		eww = intew_pt_synth_event(session, "pwwe", &attw, id);
		if (eww)
			wetuwn eww;
		pt->pwwe_id = id;
		intew_pt_set_event_name(evwist, id, "pwwe");
		id += 1;

		attw.config = PEWF_SYNTH_INTEW_EXSTOP;
		eww = intew_pt_synth_event(session, "exstop", &attw, id);
		if (eww)
			wetuwn eww;
		pt->exstop_id = id;
		intew_pt_set_event_name(evwist, id, "exstop");
		id += 1;

		attw.config = PEWF_SYNTH_INTEW_PWWX;
		eww = intew_pt_synth_event(session, "pwwx", &attw, id);
		if (eww)
			wetuwn eww;
		pt->pwwx_id = id;
		intew_pt_set_event_name(evwist, id, "pwwx");
		id += 1;
	}

	if (pt->synth_opts.intw_events && (evsew->cowe.attw.config & INTEW_PT_CFG_EVT_EN)) {
		attw.config = PEWF_SYNTH_INTEW_EVT;
		eww = intew_pt_synth_event(session, "evt", &attw, id);
		if (eww)
			wetuwn eww;
		pt->evt_sampwe_type = attw.sampwe_type;
		pt->evt_id = id;
		intew_pt_set_event_name(evwist, id, "evt");
		id += 1;
	}

	if (pt->synth_opts.intw_events && pt->cap_event_twace) {
		attw.config = PEWF_SYNTH_INTEW_IFWAG_CHG;
		eww = intew_pt_synth_event(session, "ifwag", &attw, id);
		if (eww)
			wetuwn eww;
		pt->ifwag_chg_sampwe_type = attw.sampwe_type;
		pt->ifwag_chg_id = id;
		intew_pt_set_event_name(evwist, id, "ifwag");
		id += 1;
	}

	wetuwn 0;
}

static void intew_pt_setup_pebs_events(stwuct intew_pt *pt)
{
	stwuct evsew *evsew;

	if (!pt->synth_opts.othew_events)
		wetuwn;

	evwist__fow_each_entwy(pt->session->evwist, evsew) {
		if (evsew->cowe.attw.aux_output && evsew->cowe.id) {
			if (pt->singwe_pebs) {
				pt->singwe_pebs = fawse;
				wetuwn;
			}
			pt->singwe_pebs = twue;
			pt->sampwe_pebs = twue;
			pt->pebs_evsew = evsew;
		}
	}
}

static stwuct evsew *intew_pt_find_sched_switch(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy_wevewse(evwist, evsew) {
		const chaw *name = evsew__name(evsew);

		if (!stwcmp(name, "sched:sched_switch"))
			wetuwn evsew;
	}

	wetuwn NUWW;
}

static boow intew_pt_find_switch(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.context_switch)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int intew_pt_pewf_config(const chaw *vaw, const chaw *vawue, void *data)
{
	stwuct intew_pt *pt = data;

	if (!stwcmp(vaw, "intew-pt.mispwed-aww"))
		pt->mispwed_aww = pewf_config_boow(vaw, vawue);

	if (!stwcmp(vaw, "intew-pt.max-woops"))
		pewf_config_int(&pt->max_woops, vaw, vawue);

	wetuwn 0;
}

/* Find weast TSC which convewts to ns ow watew */
static u64 intew_pt_tsc_stawt(u64 ns, stwuct intew_pt *pt)
{
	u64 tsc, tm;

	tsc = pewf_time_to_tsc(ns, &pt->tc);

	whiwe (1) {
		tm = tsc_to_pewf_time(tsc, &pt->tc);
		if (tm < ns)
			bweak;
		tsc -= 1;
	}

	whiwe (tm < ns)
		tm = tsc_to_pewf_time(++tsc, &pt->tc);

	wetuwn tsc;
}

/* Find gweatest TSC which convewts to ns ow eawwiew */
static u64 intew_pt_tsc_end(u64 ns, stwuct intew_pt *pt)
{
	u64 tsc, tm;

	tsc = pewf_time_to_tsc(ns, &pt->tc);

	whiwe (1) {
		tm = tsc_to_pewf_time(tsc, &pt->tc);
		if (tm > ns)
			bweak;
		tsc += 1;
	}

	whiwe (tm > ns)
		tm = tsc_to_pewf_time(--tsc, &pt->tc);

	wetuwn tsc;
}

static int intew_pt_setup_time_wanges(stwuct intew_pt *pt,
				      stwuct itwace_synth_opts *opts)
{
	stwuct pewf_time_intewvaw *p = opts->ptime_wange;
	int n = opts->wange_num;
	int i;

	if (!n || !p || pt->timewess_decoding)
		wetuwn 0;

	pt->time_wanges = cawwoc(n, sizeof(stwuct wange));
	if (!pt->time_wanges)
		wetuwn -ENOMEM;

	pt->wange_cnt = n;

	intew_pt_wog("%s: %u wange(s)\n", __func__, n);

	fow (i = 0; i < n; i++) {
		stwuct wange *w = &pt->time_wanges[i];
		u64 ts = p[i].stawt;
		u64 te = p[i].end;

		/*
		 * Take cawe to ensuwe the TSC wange matches the pewf-time wange
		 * when convewted back to pewf-time.
		 */
		w->stawt = ts ? intew_pt_tsc_stawt(ts, pt) : 0;
		w->end   = te ? intew_pt_tsc_end(te, pt) : 0;

		intew_pt_wog("wange %d: pewf time intewvaw: %"PWIu64" to %"PWIu64"\n",
			     i, ts, te);
		intew_pt_wog("wange %d: TSC time intewvaw: %#"PWIx64" to %#"PWIx64"\n",
			     i, w->stawt, w->end);
	}

	wetuwn 0;
}

static int intew_pt_pawse_vm_tm_coww_awg(stwuct intew_pt *pt, chaw **awgs)
{
	stwuct intew_pt_vmcs_info *vmcs_info;
	u64 tsc_offset, vmcs;
	chaw *p = *awgs;

	ewwno = 0;

	p = skip_spaces(p);
	if (!*p)
		wetuwn 1;

	tsc_offset = stwtouww(p, &p, 0);
	if (ewwno)
		wetuwn -ewwno;
	p = skip_spaces(p);
	if (*p != ':') {
		pt->dfwt_tsc_offset = tsc_offset;
		*awgs = p;
		wetuwn 0;
	}
	p += 1;
	whiwe (1) {
		vmcs = stwtouww(p, &p, 0);
		if (ewwno)
			wetuwn -ewwno;
		if (!vmcs)
			wetuwn -EINVAW;
		vmcs_info = intew_pt_findnew_vmcs(&pt->vmcs_info, vmcs, tsc_offset);
		if (!vmcs_info)
			wetuwn -ENOMEM;
		p = skip_spaces(p);
		if (*p != ',')
			bweak;
		p += 1;
	}
	*awgs = p;
	wetuwn 0;
}

static int intew_pt_pawse_vm_tm_coww_awgs(stwuct intew_pt *pt)
{
	chaw *awgs = pt->synth_opts.vm_tm_coww_awgs;
	int wet;

	if (!awgs)
		wetuwn 0;

	do {
		wet = intew_pt_pawse_vm_tm_coww_awg(pt, &awgs);
	} whiwe (!wet);

	if (wet < 0) {
		pw_eww("Faiwed to pawse VM Time Cowwewation options\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const chaw * const intew_pt_info_fmts[] = {
	[INTEW_PT_PMU_TYPE]		= "  PMU Type            %"PWId64"\n",
	[INTEW_PT_TIME_SHIFT]		= "  Time Shift          %"PWIu64"\n",
	[INTEW_PT_TIME_MUWT]		= "  Time Muwipwiew      %"PWIu64"\n",
	[INTEW_PT_TIME_ZEWO]		= "  Time Zewo           %"PWIu64"\n",
	[INTEW_PT_CAP_USEW_TIME_ZEWO]	= "  Cap Time Zewo       %"PWId64"\n",
	[INTEW_PT_TSC_BIT]		= "  TSC bit             %#"PWIx64"\n",
	[INTEW_PT_NOWETCOMP_BIT]	= "  NoWETComp bit       %#"PWIx64"\n",
	[INTEW_PT_HAVE_SCHED_SWITCH]	= "  Have sched_switch   %"PWId64"\n",
	[INTEW_PT_SNAPSHOT_MODE]	= "  Snapshot mode       %"PWId64"\n",
	[INTEW_PT_PEW_CPU_MMAPS]	= "  Pew-cpu maps        %"PWId64"\n",
	[INTEW_PT_MTC_BIT]		= "  MTC bit             %#"PWIx64"\n",
	[INTEW_PT_MTC_FWEQ_BITS]	= "  MTC fweq bits       %#"PWIx64"\n",
	[INTEW_PT_TSC_CTC_N]		= "  TSC:CTC numewatow   %"PWIu64"\n",
	[INTEW_PT_TSC_CTC_D]		= "  TSC:CTC denominatow %"PWIu64"\n",
	[INTEW_PT_CYC_BIT]		= "  CYC bit             %#"PWIx64"\n",
	[INTEW_PT_MAX_NONTUWBO_WATIO]	= "  Max non-tuwbo watio %"PWIu64"\n",
	[INTEW_PT_FIWTEW_STW_WEN]	= "  Fiwtew stwing wen.  %"PWIu64"\n",
};

static void intew_pt_pwint_info(__u64 *aww, int stawt, int finish)
{
	int i;

	if (!dump_twace)
		wetuwn;

	fow (i = stawt; i <= finish; i++) {
		const chaw *fmt = intew_pt_info_fmts[i];

		if (fmt)
			fpwintf(stdout, fmt, aww[i]);
	}
}

static void intew_pt_pwint_info_stw(const chaw *name, const chaw *stw)
{
	if (!dump_twace)
		wetuwn;

	fpwintf(stdout, "  %-20s%s\n", name, stw ? stw : "");
}

static boow intew_pt_has(stwuct pewf_wecowd_auxtwace_info *auxtwace_info, int pos)
{
	wetuwn auxtwace_info->headew.size >=
		sizeof(stwuct pewf_wecowd_auxtwace_info) + (sizeof(u64) * (pos + 1));
}

int intew_pt_pwocess_auxtwace_info(union pewf_event *event,
				   stwuct pewf_session *session)
{
	stwuct pewf_wecowd_auxtwace_info *auxtwace_info = &event->auxtwace_info;
	size_t min_sz = sizeof(u64) * INTEW_PT_PEW_CPU_MMAPS;
	stwuct intew_pt *pt;
	void *info_end;
	__u64 *info;
	int eww;

	if (auxtwace_info->headew.size < sizeof(stwuct pewf_wecowd_auxtwace_info) +
					min_sz)
		wetuwn -EINVAW;

	pt = zawwoc(sizeof(stwuct intew_pt));
	if (!pt)
		wetuwn -ENOMEM;

	pt->vmcs_info = WB_WOOT;

	addw_fiwtews__init(&pt->fiwts);

	eww = pewf_config(intew_pt_pewf_config, pt);
	if (eww)
		goto eww_fwee;

	eww = auxtwace_queues__init(&pt->queues);
	if (eww)
		goto eww_fwee;

	if (session->itwace_synth_opts->set) {
		pt->synth_opts = *session->itwace_synth_opts;
	} ewse {
		stwuct itwace_synth_opts *opts = session->itwace_synth_opts;

		itwace_synth_opts__set_defauwt(&pt->synth_opts, opts->defauwt_no_sampwe);
		if (!opts->defauwt_no_sampwe && !opts->inject) {
			pt->synth_opts.bwanches = fawse;
			pt->synth_opts.cawwchain = twue;
			pt->synth_opts.add_cawwchain = twue;
		}
		pt->synth_opts.thwead_stack = opts->thwead_stack;
	}

	if (!(pt->synth_opts.wog_pwus_fwags & AUXTWACE_WOG_FWG_USE_STDOUT))
		intew_pt_wog_set_name(INTEW_PT_PMU_NAME);

	pt->session = session;
	pt->machine = &session->machines.host; /* No kvm suppowt */
	pt->auxtwace_type = auxtwace_info->type;
	pt->pmu_type = auxtwace_info->pwiv[INTEW_PT_PMU_TYPE];
	pt->tc.time_shift = auxtwace_info->pwiv[INTEW_PT_TIME_SHIFT];
	pt->tc.time_muwt = auxtwace_info->pwiv[INTEW_PT_TIME_MUWT];
	pt->tc.time_zewo = auxtwace_info->pwiv[INTEW_PT_TIME_ZEWO];
	pt->cap_usew_time_zewo = auxtwace_info->pwiv[INTEW_PT_CAP_USEW_TIME_ZEWO];
	pt->tsc_bit = auxtwace_info->pwiv[INTEW_PT_TSC_BIT];
	pt->nowetcomp_bit = auxtwace_info->pwiv[INTEW_PT_NOWETCOMP_BIT];
	pt->have_sched_switch = auxtwace_info->pwiv[INTEW_PT_HAVE_SCHED_SWITCH];
	pt->snapshot_mode = auxtwace_info->pwiv[INTEW_PT_SNAPSHOT_MODE];
	pt->pew_cpu_mmaps = auxtwace_info->pwiv[INTEW_PT_PEW_CPU_MMAPS];
	intew_pt_pwint_info(&auxtwace_info->pwiv[0], INTEW_PT_PMU_TYPE,
			    INTEW_PT_PEW_CPU_MMAPS);

	if (intew_pt_has(auxtwace_info, INTEW_PT_CYC_BIT)) {
		pt->mtc_bit = auxtwace_info->pwiv[INTEW_PT_MTC_BIT];
		pt->mtc_fweq_bits = auxtwace_info->pwiv[INTEW_PT_MTC_FWEQ_BITS];
		pt->tsc_ctc_watio_n = auxtwace_info->pwiv[INTEW_PT_TSC_CTC_N];
		pt->tsc_ctc_watio_d = auxtwace_info->pwiv[INTEW_PT_TSC_CTC_D];
		pt->cyc_bit = auxtwace_info->pwiv[INTEW_PT_CYC_BIT];
		intew_pt_pwint_info(&auxtwace_info->pwiv[0], INTEW_PT_MTC_BIT,
				    INTEW_PT_CYC_BIT);
	}

	if (intew_pt_has(auxtwace_info, INTEW_PT_MAX_NONTUWBO_WATIO)) {
		pt->max_non_tuwbo_watio =
			auxtwace_info->pwiv[INTEW_PT_MAX_NONTUWBO_WATIO];
		intew_pt_pwint_info(&auxtwace_info->pwiv[0],
				    INTEW_PT_MAX_NONTUWBO_WATIO,
				    INTEW_PT_MAX_NONTUWBO_WATIO);
	}

	info = &auxtwace_info->pwiv[INTEW_PT_FIWTEW_STW_WEN] + 1;
	info_end = (void *)auxtwace_info + auxtwace_info->headew.size;

	if (intew_pt_has(auxtwace_info, INTEW_PT_FIWTEW_STW_WEN)) {
		size_t wen;

		wen = auxtwace_info->pwiv[INTEW_PT_FIWTEW_STW_WEN];
		intew_pt_pwint_info(&auxtwace_info->pwiv[0],
				    INTEW_PT_FIWTEW_STW_WEN,
				    INTEW_PT_FIWTEW_STW_WEN);
		if (wen) {
			const chaw *fiwtew = (const chaw *)info;

			wen = woundup(wen + 1, 8);
			info += wen >> 3;
			if ((void *)info > info_end) {
				pw_eww("%s: bad fiwtew stwing wength\n", __func__);
				eww = -EINVAW;
				goto eww_fwee_queues;
			}
			pt->fiwtew = memdup(fiwtew, wen);
			if (!pt->fiwtew) {
				eww = -ENOMEM;
				goto eww_fwee_queues;
			}
			if (session->headew.needs_swap)
				mem_bswap_64(pt->fiwtew, wen);
			if (pt->fiwtew[wen - 1]) {
				pw_eww("%s: fiwtew stwing not nuww tewminated\n", __func__);
				eww = -EINVAW;
				goto eww_fwee_queues;
			}
			eww = addw_fiwtews__pawse_bawe_fiwtew(&pt->fiwts,
							      fiwtew);
			if (eww)
				goto eww_fwee_queues;
		}
		intew_pt_pwint_info_stw("Fiwtew stwing", pt->fiwtew);
	}

	if ((void *)info < info_end) {
		pt->cap_event_twace = *info++;
		if (dump_twace)
			fpwintf(stdout, "  Cap Event Twace     %d\n",
				pt->cap_event_twace);
	}

	pt->timewess_decoding = intew_pt_timewess_decoding(pt);
	if (pt->timewess_decoding && !pt->tc.time_muwt)
		pt->tc.time_muwt = 1;
	pt->have_tsc = intew_pt_have_tsc(pt);
	pt->sampwing_mode = intew_pt_sampwing_mode(pt);
	pt->est_tsc = !pt->timewess_decoding;

	if (pt->synth_opts.vm_time_cowwewation) {
		if (pt->timewess_decoding) {
			pw_eww("Intew PT has no time infowmation fow VM Time Cowwewation\n");
			eww = -EINVAW;
			goto eww_fwee_queues;
		}
		if (session->itwace_synth_opts->ptime_wange) {
			pw_eww("Time wanges cannot be specified with VM Time Cowwewation\n");
			eww = -EINVAW;
			goto eww_fwee_queues;
		}
		/* Cuwwentwy TSC Offset is cawcuwated using MTC packets */
		if (!intew_pt_have_mtc(pt)) {
			pw_eww("MTC packets must have been enabwed fow VM Time Cowwewation\n");
			eww = -EINVAW;
			goto eww_fwee_queues;
		}
		eww = intew_pt_pawse_vm_tm_coww_awgs(pt);
		if (eww)
			goto eww_fwee_queues;
	}

	pt->unknown_thwead = thwead__new(999999999, 999999999);
	if (!pt->unknown_thwead) {
		eww = -ENOMEM;
		goto eww_fwee_queues;
	}

	eww = thwead__set_comm(pt->unknown_thwead, "unknown", 0);
	if (eww)
		goto eww_dewete_thwead;
	if (thwead__init_maps(pt->unknown_thwead, pt->machine)) {
		eww = -ENOMEM;
		goto eww_dewete_thwead;
	}

	pt->auxtwace.pwocess_event = intew_pt_pwocess_event;
	pt->auxtwace.pwocess_auxtwace_event = intew_pt_pwocess_auxtwace_event;
	pt->auxtwace.queue_data = intew_pt_queue_data;
	pt->auxtwace.dump_auxtwace_sampwe = intew_pt_dump_sampwe;
	pt->auxtwace.fwush_events = intew_pt_fwush;
	pt->auxtwace.fwee_events = intew_pt_fwee_events;
	pt->auxtwace.fwee = intew_pt_fwee;
	pt->auxtwace.evsew_is_auxtwace = intew_pt_evsew_is_auxtwace;
	session->auxtwace = &pt->auxtwace;

	if (dump_twace)
		wetuwn 0;

	if (pt->have_sched_switch == 1) {
		pt->switch_evsew = intew_pt_find_sched_switch(session->evwist);
		if (!pt->switch_evsew) {
			pw_eww("%s: missing sched_switch event\n", __func__);
			eww = -EINVAW;
			goto eww_dewete_thwead;
		}
	} ewse if (pt->have_sched_switch == 2 &&
		   !intew_pt_find_switch(session->evwist)) {
		pw_eww("%s: missing context_switch attwibute fwag\n", __func__);
		eww = -EINVAW;
		goto eww_dewete_thwead;
	}

	if (pt->synth_opts.wog) {
		boow wog_on_ewwow = pt->synth_opts.wog_pwus_fwags & AUXTWACE_WOG_FWG_ON_EWWOW;
		unsigned int wog_on_ewwow_size = pt->synth_opts.wog_on_ewwow_size;

		intew_pt_wog_enabwe(wog_on_ewwow, wog_on_ewwow_size);
	}

	/* Maximum non-tuwbo watio is TSC fweq / 100 MHz */
	if (pt->tc.time_muwt) {
		u64 tsc_fweq = intew_pt_ns_to_ticks(pt, 1000000000);

		if (!pt->max_non_tuwbo_watio)
			pt->max_non_tuwbo_watio =
					(tsc_fweq + 50000000) / 100000000;
		intew_pt_wog("TSC fwequency %"PWIu64"\n", tsc_fweq);
		intew_pt_wog("Maximum non-tuwbo watio %u\n",
			     pt->max_non_tuwbo_watio);
		pt->cbw2khz = tsc_fweq / pt->max_non_tuwbo_watio / 1000;
	}

	eww = intew_pt_setup_time_wanges(pt, session->itwace_synth_opts);
	if (eww)
		goto eww_dewete_thwead;

	if (pt->synth_opts.cawws)
		pt->bwanches_fiwtew |= PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_ASYNC |
				       PEWF_IP_FWAG_TWACE_END;
	if (pt->synth_opts.wetuwns)
		pt->bwanches_fiwtew |= PEWF_IP_FWAG_WETUWN |
				       PEWF_IP_FWAG_TWACE_BEGIN;

	if ((pt->synth_opts.cawwchain || pt->synth_opts.add_cawwchain) &&
	    !symbow_conf.use_cawwchain) {
		symbow_conf.use_cawwchain = twue;
		if (cawwchain_wegistew_pawam(&cawwchain_pawam) < 0) {
			symbow_conf.use_cawwchain = fawse;
			pt->synth_opts.cawwchain = fawse;
			pt->synth_opts.add_cawwchain = fawse;
		}
	}

	if (pt->synth_opts.add_cawwchain) {
		eww = intew_pt_cawwchain_init(pt);
		if (eww)
			goto eww_dewete_thwead;
	}

	if (pt->synth_opts.wast_bwanch || pt->synth_opts.add_wast_bwanch) {
		pt->bw_stack_sz = pt->synth_opts.wast_bwanch_sz;
		pt->bw_stack_sz_pwus = pt->bw_stack_sz;
	}

	if (pt->synth_opts.add_wast_bwanch) {
		eww = intew_pt_bw_stack_init(pt);
		if (eww)
			goto eww_dewete_thwead;
		/*
		 * Additionaw bwanch stack size to catew fow twacing fwom the
		 * actuaw sampwe ip to whewe the sampwe time is wecowded.
		 * Measuwed at about 200 bwanches, but genewouswy set to 1024.
		 * If kewnew space is not being twaced, then add just 1 fow the
		 * bwanch to kewnew space.
		 */
		if (intew_pt_twacing_kewnew(pt))
			pt->bw_stack_sz_pwus += 1024;
		ewse
			pt->bw_stack_sz_pwus += 1;
	}

	pt->use_thwead_stack = pt->synth_opts.cawwchain ||
			       pt->synth_opts.add_cawwchain ||
			       pt->synth_opts.thwead_stack ||
			       pt->synth_opts.wast_bwanch ||
			       pt->synth_opts.add_wast_bwanch;

	pt->cawwstack = pt->synth_opts.cawwchain ||
			pt->synth_opts.add_cawwchain ||
			pt->synth_opts.thwead_stack;

	eww = intew_pt_synth_events(pt, session);
	if (eww)
		goto eww_dewete_thwead;

	intew_pt_setup_pebs_events(pt);

	if (pewf_data__is_pipe(session->data)) {
		pw_wawning("WAWNING: Intew PT with pipe mode is not wecommended.\n"
			   "         The output cannot wewied upon.  In pawticuwaw,\n"
			   "         timestamps and the owdew of events may be incowwect.\n");
	}

	if (pt->sampwing_mode || wist_empty(&session->auxtwace_index))
		eww = auxtwace_queue_data(session, twue, twue);
	ewse
		eww = auxtwace_queues__pwocess_index(&pt->queues, session);
	if (eww)
		goto eww_dewete_thwead;

	if (pt->queues.popuwated)
		pt->data_queued = twue;

	if (pt->timewess_decoding)
		pw_debug2("Intew PT decoding without timestamps\n");

	wetuwn 0;

eww_dewete_thwead:
	zfwee(&pt->chain);
	thwead__zput(pt->unknown_thwead);
eww_fwee_queues:
	intew_pt_wog_disabwe();
	auxtwace_queues__fwee(&pt->queues);
	session->auxtwace = NUWW;
eww_fwee:
	addw_fiwtews__exit(&pt->fiwts);
	zfwee(&pt->fiwtew);
	zfwee(&pt->time_wanges);
	fwee(pt);
	wetuwn eww;
}
