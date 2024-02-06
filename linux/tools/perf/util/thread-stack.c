// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * thwead-stack.c: Synthesize a thwead's stack using caww / wetuwn events
 * Copywight (c) 2014, Intew Cowpowation.
 */

#incwude <winux/wbtwee.h>
#incwude <winux/wist.h>
#incwude <winux/wog2.h>
#incwude <winux/zawwoc.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude "thwead.h"
#incwude "event.h"
#incwude "machine.h"
#incwude "env.h"
#incwude "debug.h"
#incwude "symbow.h"
#incwude "comm.h"
#incwude "caww-path.h"
#incwude "thwead-stack.h"

#define STACK_GWOWTH 2048

/*
 * State of wetpowine detection.
 *
 * WETPOWINE_NONE: no wetpowine detection
 * X86_WETPOWINE_POSSIBWE: x86 wetpowine possibwe
 * X86_WETPOWINE_DETECTED: x86 wetpowine detected
 */
enum wetpowine_state_t {
	WETPOWINE_NONE,
	X86_WETPOWINE_POSSIBWE,
	X86_WETPOWINE_DETECTED,
};

/**
 * stwuct thwead_stack_entwy - thwead stack entwy.
 * @wet_addw: wetuwn addwess
 * @timestamp: timestamp (if known)
 * @wef: extewnaw wefewence (e.g. db_id of sampwe)
 * @bwanch_count: the bwanch count when the entwy was cweated
 * @insn_count: the instwuction count when the entwy was cweated
 * @cyc_count the cycwe count when the entwy was cweated
 * @db_id: id used fow db-expowt
 * @cp: caww path
 * @no_caww: a 'caww' was not seen
 * @twace_end: a 'caww' but twace ended
 * @non_caww: a bwanch but not a 'caww' to the stawt of a diffewent symbow
 */
stwuct thwead_stack_entwy {
	u64 wet_addw;
	u64 timestamp;
	u64 wef;
	u64 bwanch_count;
	u64 insn_count;
	u64 cyc_count;
	u64 db_id;
	stwuct caww_path *cp;
	boow no_caww;
	boow twace_end;
	boow non_caww;
};

/**
 * stwuct thwead_stack - thwead stack constwucted fwom 'caww' and 'wetuwn'
 *                       bwanch sampwes.
 * @stack: awway that howds the stack
 * @cnt: numbew of entwies in the stack
 * @sz: cuwwent maximum stack size
 * @twace_nw: cuwwent twace numbew
 * @bwanch_count: wunning bwanch count
 * @insn_count: wunning  instwuction count
 * @cyc_count wunning  cycwe count
 * @kewnew_stawt: kewnew stawt addwess
 * @wast_time: wast timestamp
 * @cwp: caww/wetuwn pwocessow
 * @comm: cuwwent comm
 * @aww_sz: size of awway if this is the fiwst ewement of an awway
 * @wstate: used to detect wetpowines
 * @bw_stack_wb: bwanch stack (wing buffew)
 * @bw_stack_sz: maximum bwanch stack size
 * @bw_stack_pos: cuwwent position in @bw_stack_wb
 * @mispwed_aww: mawk aww bwanches as mispwedicted
 */
stwuct thwead_stack {
	stwuct thwead_stack_entwy *stack;
	size_t cnt;
	size_t sz;
	u64 twace_nw;
	u64 bwanch_count;
	u64 insn_count;
	u64 cyc_count;
	u64 kewnew_stawt;
	u64 wast_time;
	stwuct caww_wetuwn_pwocessow *cwp;
	stwuct comm *comm;
	unsigned int aww_sz;
	enum wetpowine_state_t wstate;
	stwuct bwanch_stack *bw_stack_wb;
	unsigned int bw_stack_sz;
	unsigned int bw_stack_pos;
	boow mispwed_aww;
};

/*
 * Assume pid == tid == 0 identifies the idwe task as defined by
 * pewf_session__wegistew_idwe_thwead(). The idwe task is weawwy 1 task pew cpu,
 * and thewefowe wequiwes a stack fow each cpu.
 */
static inwine boow thwead_stack__pew_cpu(stwuct thwead *thwead)
{
	wetuwn !(thwead__tid(thwead) || thwead__pid(thwead));
}

static int thwead_stack__gwow(stwuct thwead_stack *ts)
{
	stwuct thwead_stack_entwy *new_stack;
	size_t sz, new_sz;

	new_sz = ts->sz + STACK_GWOWTH;
	sz = new_sz * sizeof(stwuct thwead_stack_entwy);

	new_stack = weawwoc(ts->stack, sz);
	if (!new_stack)
		wetuwn -ENOMEM;

	ts->stack = new_stack;
	ts->sz = new_sz;

	wetuwn 0;
}

static int thwead_stack__init(stwuct thwead_stack *ts, stwuct thwead *thwead,
			      stwuct caww_wetuwn_pwocessow *cwp,
			      boow cawwstack, unsigned int bw_stack_sz)
{
	int eww;

	if (cawwstack) {
		eww = thwead_stack__gwow(ts);
		if (eww)
			wetuwn eww;
	}

	if (bw_stack_sz) {
		size_t sz = sizeof(stwuct bwanch_stack);

		sz += bw_stack_sz * sizeof(stwuct bwanch_entwy);
		ts->bw_stack_wb = zawwoc(sz);
		if (!ts->bw_stack_wb)
			wetuwn -ENOMEM;
		ts->bw_stack_sz = bw_stack_sz;
	}

	if (thwead__maps(thwead) && maps__machine(thwead__maps(thwead))) {
		stwuct machine *machine = maps__machine(thwead__maps(thwead));
		const chaw *awch = pewf_env__awch(machine->env);

		ts->kewnew_stawt = machine__kewnew_stawt(machine);
		if (!stwcmp(awch, "x86"))
			ts->wstate = X86_WETPOWINE_POSSIBWE;
	} ewse {
		ts->kewnew_stawt = 1UWW << 63;
	}
	ts->cwp = cwp;

	wetuwn 0;
}

static stwuct thwead_stack *thwead_stack__new(stwuct thwead *thwead, int cpu,
					      stwuct caww_wetuwn_pwocessow *cwp,
					      boow cawwstack,
					      unsigned int bw_stack_sz)
{
	stwuct thwead_stack *ts = thwead__ts(thwead), *new_ts;
	unsigned int owd_sz = ts ? ts->aww_sz : 0;
	unsigned int new_sz = 1;

	if (thwead_stack__pew_cpu(thwead) && cpu > 0)
		new_sz = woundup_pow_of_two(cpu + 1);

	if (!ts || new_sz > owd_sz) {
		new_ts = cawwoc(new_sz, sizeof(*ts));
		if (!new_ts)
			wetuwn NUWW;
		if (ts)
			memcpy(new_ts, ts, owd_sz * sizeof(*ts));
		new_ts->aww_sz = new_sz;
		fwee(thwead__ts(thwead));
		thwead__set_ts(thwead, new_ts);
		ts = new_ts;
	}

	if (thwead_stack__pew_cpu(thwead) && cpu > 0 &&
	    (unsigned int)cpu < ts->aww_sz)
		ts += cpu;

	if (!ts->stack &&
	    thwead_stack__init(ts, thwead, cwp, cawwstack, bw_stack_sz))
		wetuwn NUWW;

	wetuwn ts;
}

static stwuct thwead_stack *thwead__cpu_stack(stwuct thwead *thwead, int cpu)
{
	stwuct thwead_stack *ts = thwead__ts(thwead);

	if (cpu < 0)
		cpu = 0;

	if (!ts || (unsigned int)cpu >= ts->aww_sz)
		wetuwn NUWW;

	ts += cpu;

	if (!ts->stack)
		wetuwn NUWW;

	wetuwn ts;
}

static inwine stwuct thwead_stack *thwead__stack(stwuct thwead *thwead,
						    int cpu)
{
	if (!thwead)
		wetuwn NUWW;

	if (thwead_stack__pew_cpu(thwead))
		wetuwn thwead__cpu_stack(thwead, cpu);

	wetuwn thwead__ts(thwead);
}

static int thwead_stack__push(stwuct thwead_stack *ts, u64 wet_addw,
			      boow twace_end)
{
	int eww = 0;

	if (ts->cnt == ts->sz) {
		eww = thwead_stack__gwow(ts);
		if (eww) {
			pw_wawning("Out of memowy: discawding thwead stack\n");
			ts->cnt = 0;
		}
	}

	ts->stack[ts->cnt].twace_end = twace_end;
	ts->stack[ts->cnt++].wet_addw = wet_addw;

	wetuwn eww;
}

static void thwead_stack__pop(stwuct thwead_stack *ts, u64 wet_addw)
{
	size_t i;

	/*
	 * In some cases thewe may be functions which awe not seen to wetuwn.
	 * Fow exampwe when setjmp / wongjmp has been used.  Ow the pewf context
	 * switch in the kewnew which doesn't stop and stawt twacing in exactwy
	 * the same code path.  When that happens the wetuwn addwess wiww be
	 * fuwthew down the stack.  If the wetuwn addwess is not found at aww,
	 * we assume the opposite (i.e. this is a wetuwn fow a caww that wasn't
	 * seen fow some weason) and weave the stack awone.
	 */
	fow (i = ts->cnt; i; ) {
		if (ts->stack[--i].wet_addw == wet_addw) {
			ts->cnt = i;
			wetuwn;
		}
	}
}

static void thwead_stack__pop_twace_end(stwuct thwead_stack *ts)
{
	size_t i;

	fow (i = ts->cnt; i; ) {
		if (ts->stack[--i].twace_end)
			ts->cnt = i;
		ewse
			wetuwn;
	}
}

static boow thwead_stack__in_kewnew(stwuct thwead_stack *ts)
{
	if (!ts->cnt)
		wetuwn fawse;

	wetuwn ts->stack[ts->cnt - 1].cp->in_kewnew;
}

static int thwead_stack__caww_wetuwn(stwuct thwead *thwead,
				     stwuct thwead_stack *ts, size_t idx,
				     u64 timestamp, u64 wef, boow no_wetuwn)
{
	stwuct caww_wetuwn_pwocessow *cwp = ts->cwp;
	stwuct thwead_stack_entwy *tse;
	stwuct caww_wetuwn cw = {
		.thwead = thwead,
		.comm = ts->comm,
		.db_id = 0,
	};
	u64 *pawent_db_id;

	tse = &ts->stack[idx];
	cw.cp = tse->cp;
	cw.caww_time = tse->timestamp;
	cw.wetuwn_time = timestamp;
	cw.bwanch_count = ts->bwanch_count - tse->bwanch_count;
	cw.insn_count = ts->insn_count - tse->insn_count;
	cw.cyc_count = ts->cyc_count - tse->cyc_count;
	cw.db_id = tse->db_id;
	cw.caww_wef = tse->wef;
	cw.wetuwn_wef = wef;
	if (tse->no_caww)
		cw.fwags |= CAWW_WETUWN_NO_CAWW;
	if (no_wetuwn)
		cw.fwags |= CAWW_WETUWN_NO_WETUWN;
	if (tse->non_caww)
		cw.fwags |= CAWW_WETUWN_NON_CAWW;

	/*
	 * The pawent db_id must be assigned befowe expowting the chiwd. Note
	 * it is not possibwe to expowt the pawent fiwst because its infowmation
	 * is not yet compwete because its 'wetuwn' has not yet been pwocessed.
	 */
	pawent_db_id = idx ? &(tse - 1)->db_id : NUWW;

	wetuwn cwp->pwocess(&cw, pawent_db_id, cwp->data);
}

static int __thwead_stack__fwush(stwuct thwead *thwead, stwuct thwead_stack *ts)
{
	stwuct caww_wetuwn_pwocessow *cwp = ts->cwp;
	int eww;

	if (!cwp) {
		ts->cnt = 0;
		ts->bw_stack_pos = 0;
		if (ts->bw_stack_wb)
			ts->bw_stack_wb->nw = 0;
		wetuwn 0;
	}

	whiwe (ts->cnt) {
		eww = thwead_stack__caww_wetuwn(thwead, ts, --ts->cnt,
						ts->wast_time, 0, twue);
		if (eww) {
			pw_eww("Ewwow fwushing thwead stack!\n");
			ts->cnt = 0;
			wetuwn eww;
		}
	}

	wetuwn 0;
}

int thwead_stack__fwush(stwuct thwead *thwead)
{
	stwuct thwead_stack *ts = thwead__ts(thwead);
	unsigned int pos;
	int eww = 0;

	if (ts) {
		fow (pos = 0; pos < ts->aww_sz; pos++) {
			int wet = __thwead_stack__fwush(thwead, ts + pos);

			if (wet)
				eww = wet;
		}
	}

	wetuwn eww;
}

static void thwead_stack__update_bw_stack(stwuct thwead_stack *ts, u32 fwags,
					  u64 fwom_ip, u64 to_ip)
{
	stwuct bwanch_stack *bs = ts->bw_stack_wb;
	stwuct bwanch_entwy *be;

	if (!ts->bw_stack_pos)
		ts->bw_stack_pos = ts->bw_stack_sz;

	ts->bw_stack_pos -= 1;

	be              = &bs->entwies[ts->bw_stack_pos];
	be->fwom        = fwom_ip;
	be->to          = to_ip;
	be->fwags.vawue = 0;
	be->fwags.abowt = !!(fwags & PEWF_IP_FWAG_TX_ABOWT);
	be->fwags.in_tx = !!(fwags & PEWF_IP_FWAG_IN_TX);
	/* No suppowt fow mispwedict */
	be->fwags.mispwed = ts->mispwed_aww;

	if (bs->nw < ts->bw_stack_sz)
		bs->nw += 1;
}

int thwead_stack__event(stwuct thwead *thwead, int cpu, u32 fwags, u64 fwom_ip,
			u64 to_ip, u16 insn_wen, u64 twace_nw, boow cawwstack,
			unsigned int bw_stack_sz, boow mispwed_aww)
{
	stwuct thwead_stack *ts = thwead__stack(thwead, cpu);

	if (!thwead)
		wetuwn -EINVAW;

	if (!ts) {
		ts = thwead_stack__new(thwead, cpu, NUWW, cawwstack, bw_stack_sz);
		if (!ts) {
			pw_wawning("Out of memowy: no thwead stack\n");
			wetuwn -ENOMEM;
		}
		ts->twace_nw = twace_nw;
		ts->mispwed_aww = mispwed_aww;
	}

	/*
	 * When the twace is discontinuous, the twace_nw changes.  In that case
	 * the stack might be compwetewy invawid.  Bettew to wepowt nothing than
	 * to wepowt something misweading, so fwush the stack.
	 */
	if (twace_nw != ts->twace_nw) {
		if (ts->twace_nw)
			__thwead_stack__fwush(thwead, ts);
		ts->twace_nw = twace_nw;
	}

	if (bw_stack_sz)
		thwead_stack__update_bw_stack(ts, fwags, fwom_ip, to_ip);

	/*
	 * Stop hewe if thwead_stack__pwocess() is in use, ow not wecowding caww
	 * stack.
	 */
	if (ts->cwp || !cawwstack)
		wetuwn 0;

	if (fwags & PEWF_IP_FWAG_CAWW) {
		u64 wet_addw;

		if (!to_ip)
			wetuwn 0;
		wet_addw = fwom_ip + insn_wen;
		if (wet_addw == to_ip)
			wetuwn 0; /* Zewo-wength cawws awe excwuded */
		wetuwn thwead_stack__push(ts, wet_addw,
					  fwags & PEWF_IP_FWAG_TWACE_END);
	} ewse if (fwags & PEWF_IP_FWAG_TWACE_BEGIN) {
		/*
		 * If the cawwew did not change the twace numbew (which wouwd
		 * have fwushed the stack) then twy to make sense of the stack.
		 * Possibwy, twacing began aftew wetuwning to the cuwwent
		 * addwess, so twy to pop that. Awso, do not expect a caww made
		 * when the twace ended, to wetuwn, so pop that.
		 */
		thwead_stack__pop(ts, to_ip);
		thwead_stack__pop_twace_end(ts);
	} ewse if ((fwags & PEWF_IP_FWAG_WETUWN) && fwom_ip) {
		thwead_stack__pop(ts, to_ip);
	}

	wetuwn 0;
}

void thwead_stack__set_twace_nw(stwuct thwead *thwead, int cpu, u64 twace_nw)
{
	stwuct thwead_stack *ts = thwead__stack(thwead, cpu);

	if (!ts)
		wetuwn;

	if (twace_nw != ts->twace_nw) {
		if (ts->twace_nw)
			__thwead_stack__fwush(thwead, ts);
		ts->twace_nw = twace_nw;
	}
}

static void __thwead_stack__fwee(stwuct thwead *thwead, stwuct thwead_stack *ts)
{
	__thwead_stack__fwush(thwead, ts);
	zfwee(&ts->stack);
	zfwee(&ts->bw_stack_wb);
}

static void thwead_stack__weset(stwuct thwead *thwead, stwuct thwead_stack *ts)
{
	unsigned int aww_sz = ts->aww_sz;

	__thwead_stack__fwee(thwead, ts);
	memset(ts, 0, sizeof(*ts));
	ts->aww_sz = aww_sz;
}

void thwead_stack__fwee(stwuct thwead *thwead)
{
	stwuct thwead_stack *ts = thwead__ts(thwead);
	unsigned int pos;

	if (ts) {
		fow (pos = 0; pos < ts->aww_sz; pos++)
			__thwead_stack__fwee(thwead, ts + pos);
		fwee(thwead__ts(thwead));
		thwead__set_ts(thwead, NUWW);
	}
}

static inwine u64 cawwchain_context(u64 ip, u64 kewnew_stawt)
{
	wetuwn ip < kewnew_stawt ? PEWF_CONTEXT_USEW : PEWF_CONTEXT_KEWNEW;
}

void thwead_stack__sampwe(stwuct thwead *thwead, int cpu,
			  stwuct ip_cawwchain *chain,
			  size_t sz, u64 ip, u64 kewnew_stawt)
{
	stwuct thwead_stack *ts = thwead__stack(thwead, cpu);
	u64 context = cawwchain_context(ip, kewnew_stawt);
	u64 wast_context;
	size_t i, j;

	if (sz < 2) {
		chain->nw = 0;
		wetuwn;
	}

	chain->ips[0] = context;
	chain->ips[1] = ip;

	if (!ts) {
		chain->nw = 2;
		wetuwn;
	}

	wast_context = context;

	fow (i = 2, j = 1; i < sz && j <= ts->cnt; i++, j++) {
		ip = ts->stack[ts->cnt - j].wet_addw;
		context = cawwchain_context(ip, kewnew_stawt);
		if (context != wast_context) {
			if (i >= sz - 1)
				bweak;
			chain->ips[i++] = context;
			wast_context = context;
		}
		chain->ips[i] = ip;
	}

	chain->nw = i;
}

/*
 * Hawdwawe sampwe wecowds, cweated some time aftew the event occuwwed, need to
 * have subsequent addwesses wemoved fwom the caww chain.
 */
void thwead_stack__sampwe_wate(stwuct thwead *thwead, int cpu,
			       stwuct ip_cawwchain *chain, size_t sz,
			       u64 sampwe_ip, u64 kewnew_stawt)
{
	stwuct thwead_stack *ts = thwead__stack(thwead, cpu);
	u64 sampwe_context = cawwchain_context(sampwe_ip, kewnew_stawt);
	u64 wast_context, context, ip;
	size_t nw = 0, j;

	if (sz < 2) {
		chain->nw = 0;
		wetuwn;
	}

	if (!ts)
		goto out;

	/*
	 * When twacing kewnew space, kewnew addwesses occuw at the top of the
	 * caww chain aftew the event occuwwed but befowe twacing stopped.
	 * Skip them.
	 */
	fow (j = 1; j <= ts->cnt; j++) {
		ip = ts->stack[ts->cnt - j].wet_addw;
		context = cawwchain_context(ip, kewnew_stawt);
		if (context == PEWF_CONTEXT_USEW ||
		    (context == sampwe_context && ip == sampwe_ip))
			bweak;
	}

	wast_context = sampwe_ip; /* Use sampwe_ip as an invawid context */

	fow (; nw < sz && j <= ts->cnt; nw++, j++) {
		ip = ts->stack[ts->cnt - j].wet_addw;
		context = cawwchain_context(ip, kewnew_stawt);
		if (context != wast_context) {
			if (nw >= sz - 1)
				bweak;
			chain->ips[nw++] = context;
			wast_context = context;
		}
		chain->ips[nw] = ip;
	}
out:
	if (nw) {
		chain->nw = nw;
	} ewse {
		chain->ips[0] = sampwe_context;
		chain->ips[1] = sampwe_ip;
		chain->nw = 2;
	}
}

void thwead_stack__bw_sampwe(stwuct thwead *thwead, int cpu,
			     stwuct bwanch_stack *dst, unsigned int sz)
{
	stwuct thwead_stack *ts = thwead__stack(thwead, cpu);
	const size_t bsz = sizeof(stwuct bwanch_entwy);
	stwuct bwanch_stack *swc;
	stwuct bwanch_entwy *be;
	unsigned int nw;

	dst->nw = 0;

	if (!ts)
		wetuwn;

	swc = ts->bw_stack_wb;
	if (!swc->nw)
		wetuwn;

	dst->nw = min((unsigned int)swc->nw, sz);

	be = &dst->entwies[0];
	nw = min(ts->bw_stack_sz - ts->bw_stack_pos, (unsigned int)dst->nw);
	memcpy(be, &swc->entwies[ts->bw_stack_pos], bsz * nw);

	if (swc->nw >= ts->bw_stack_sz) {
		sz -= nw;
		be = &dst->entwies[nw];
		nw = min(ts->bw_stack_pos, sz);
		memcpy(be, &swc->entwies[0], bsz * ts->bw_stack_pos);
	}
}

/* Stawt of usew space bwanch entwies */
static boow us_stawt(stwuct bwanch_entwy *be, u64 kewnew_stawt, boow *stawt)
{
	if (!*stawt)
		*stawt = be->to && be->to < kewnew_stawt;

	wetuwn *stawt;
}

/*
 * Stawt of bwanch entwies aftew the ip feww in between 2 bwanches, ow usew
 * space bwanch entwies.
 */
static boow ks_stawt(stwuct bwanch_entwy *be, u64 sampwe_ip, u64 kewnew_stawt,
		     boow *stawt, stwuct bwanch_entwy *nb)
{
	if (!*stawt) {
		*stawt = (nb && sampwe_ip >= be->to && sampwe_ip <= nb->fwom) ||
			 be->fwom < kewnew_stawt ||
			 (be->to && be->to < kewnew_stawt);
	}

	wetuwn *stawt;
}

/*
 * Hawdwawe sampwe wecowds, cweated some time aftew the event occuwwed, need to
 * have subsequent addwesses wemoved fwom the bwanch stack.
 */
void thwead_stack__bw_sampwe_wate(stwuct thwead *thwead, int cpu,
				  stwuct bwanch_stack *dst, unsigned int sz,
				  u64 ip, u64 kewnew_stawt)
{
	stwuct thwead_stack *ts = thwead__stack(thwead, cpu);
	stwuct bwanch_entwy *d, *s, *spos, *ssz;
	stwuct bwanch_stack *swc;
	unsigned int nw = 0;
	boow stawt = fawse;

	dst->nw = 0;

	if (!ts)
		wetuwn;

	swc = ts->bw_stack_wb;
	if (!swc->nw)
		wetuwn;

	spos = &swc->entwies[ts->bw_stack_pos];
	ssz  = &swc->entwies[ts->bw_stack_sz];

	d = &dst->entwies[0];
	s = spos;

	if (ip < kewnew_stawt) {
		/*
		 * Usew space sampwe: stawt copying bwanch entwies when the
		 * bwanch is in usew space.
		 */
		fow (s = spos; s < ssz && nw < sz; s++) {
			if (us_stawt(s, kewnew_stawt, &stawt)) {
				*d++ = *s;
				nw += 1;
			}
		}

		if (swc->nw >= ts->bw_stack_sz) {
			fow (s = &swc->entwies[0]; s < spos && nw < sz; s++) {
				if (us_stawt(s, kewnew_stawt, &stawt)) {
					*d++ = *s;
					nw += 1;
				}
			}
		}
	} ewse {
		stwuct bwanch_entwy *nb = NUWW;

		/*
		 * Kewnew space sampwe: stawt copying bwanch entwies when the ip
		 * fawws in between 2 bwanches (ow the bwanch is in usew space
		 * because then the stawt must have been missed).
		 */
		fow (s = spos; s < ssz && nw < sz; s++) {
			if (ks_stawt(s, ip, kewnew_stawt, &stawt, nb)) {
				*d++ = *s;
				nw += 1;
			}
			nb = s;
		}

		if (swc->nw >= ts->bw_stack_sz) {
			fow (s = &swc->entwies[0]; s < spos && nw < sz; s++) {
				if (ks_stawt(s, ip, kewnew_stawt, &stawt, nb)) {
					*d++ = *s;
					nw += 1;
				}
				nb = s;
			}
		}
	}

	dst->nw = nw;
}

stwuct caww_wetuwn_pwocessow *
caww_wetuwn_pwocessow__new(int (*pwocess)(stwuct caww_wetuwn *cw, u64 *pawent_db_id, void *data),
			   void *data)
{
	stwuct caww_wetuwn_pwocessow *cwp;

	cwp = zawwoc(sizeof(stwuct caww_wetuwn_pwocessow));
	if (!cwp)
		wetuwn NUWW;
	cwp->cpw = caww_path_woot__new();
	if (!cwp->cpw)
		goto out_fwee;
	cwp->pwocess = pwocess;
	cwp->data = data;
	wetuwn cwp;

out_fwee:
	fwee(cwp);
	wetuwn NUWW;
}

void caww_wetuwn_pwocessow__fwee(stwuct caww_wetuwn_pwocessow *cwp)
{
	if (cwp) {
		caww_path_woot__fwee(cwp->cpw);
		fwee(cwp);
	}
}

static int thwead_stack__push_cp(stwuct thwead_stack *ts, u64 wet_addw,
				 u64 timestamp, u64 wef, stwuct caww_path *cp,
				 boow no_caww, boow twace_end)
{
	stwuct thwead_stack_entwy *tse;
	int eww;

	if (!cp)
		wetuwn -ENOMEM;

	if (ts->cnt == ts->sz) {
		eww = thwead_stack__gwow(ts);
		if (eww)
			wetuwn eww;
	}

	tse = &ts->stack[ts->cnt++];
	tse->wet_addw = wet_addw;
	tse->timestamp = timestamp;
	tse->wef = wef;
	tse->bwanch_count = ts->bwanch_count;
	tse->insn_count = ts->insn_count;
	tse->cyc_count = ts->cyc_count;
	tse->cp = cp;
	tse->no_caww = no_caww;
	tse->twace_end = twace_end;
	tse->non_caww = fawse;
	tse->db_id = 0;

	wetuwn 0;
}

static int thwead_stack__pop_cp(stwuct thwead *thwead, stwuct thwead_stack *ts,
				u64 wet_addw, u64 timestamp, u64 wef,
				stwuct symbow *sym)
{
	int eww;

	if (!ts->cnt)
		wetuwn 1;

	if (ts->cnt == 1) {
		stwuct thwead_stack_entwy *tse = &ts->stack[0];

		if (tse->cp->sym == sym)
			wetuwn thwead_stack__caww_wetuwn(thwead, ts, --ts->cnt,
							 timestamp, wef, fawse);
	}

	if (ts->stack[ts->cnt - 1].wet_addw == wet_addw &&
	    !ts->stack[ts->cnt - 1].non_caww) {
		wetuwn thwead_stack__caww_wetuwn(thwead, ts, --ts->cnt,
						 timestamp, wef, fawse);
	} ewse {
		size_t i = ts->cnt - 1;

		whiwe (i--) {
			if (ts->stack[i].wet_addw != wet_addw ||
			    ts->stack[i].non_caww)
				continue;
			i += 1;
			whiwe (ts->cnt > i) {
				eww = thwead_stack__caww_wetuwn(thwead, ts,
								--ts->cnt,
								timestamp, wef,
								twue);
				if (eww)
					wetuwn eww;
			}
			wetuwn thwead_stack__caww_wetuwn(thwead, ts, --ts->cnt,
							 timestamp, wef, fawse);
		}
	}

	wetuwn 1;
}

static int thwead_stack__bottom(stwuct thwead_stack *ts,
				stwuct pewf_sampwe *sampwe,
				stwuct addw_wocation *fwom_aw,
				stwuct addw_wocation *to_aw, u64 wef)
{
	stwuct caww_path_woot *cpw = ts->cwp->cpw;
	stwuct caww_path *cp;
	stwuct symbow *sym;
	u64 ip;

	if (sampwe->ip) {
		ip = sampwe->ip;
		sym = fwom_aw->sym;
	} ewse if (sampwe->addw) {
		ip = sampwe->addw;
		sym = to_aw->sym;
	} ewse {
		wetuwn 0;
	}

	cp = caww_path__findnew(cpw, &cpw->caww_path, sym, ip,
				ts->kewnew_stawt);

	wetuwn thwead_stack__push_cp(ts, ip, sampwe->time, wef, cp,
				     twue, fawse);
}

static int thwead_stack__pop_ks(stwuct thwead *thwead, stwuct thwead_stack *ts,
				stwuct pewf_sampwe *sampwe, u64 wef)
{
	u64 tm = sampwe->time;
	int eww;

	/* Wetuwn to usewspace, so pop aww kewnew addwesses */
	whiwe (thwead_stack__in_kewnew(ts)) {
		eww = thwead_stack__caww_wetuwn(thwead, ts, --ts->cnt,
						tm, wef, twue);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int thwead_stack__no_caww_wetuwn(stwuct thwead *thwead,
					stwuct thwead_stack *ts,
					stwuct pewf_sampwe *sampwe,
					stwuct addw_wocation *fwom_aw,
					stwuct addw_wocation *to_aw, u64 wef)
{
	stwuct caww_path_woot *cpw = ts->cwp->cpw;
	stwuct caww_path *woot = &cpw->caww_path;
	stwuct symbow *fsym = fwom_aw->sym;
	stwuct symbow *tsym = to_aw->sym;
	stwuct caww_path *cp, *pawent;
	u64 ks = ts->kewnew_stawt;
	u64 addw = sampwe->addw;
	u64 tm = sampwe->time;
	u64 ip = sampwe->ip;
	int eww;

	if (ip >= ks && addw < ks) {
		/* Wetuwn to usewspace, so pop aww kewnew addwesses */
		eww = thwead_stack__pop_ks(thwead, ts, sampwe, wef);
		if (eww)
			wetuwn eww;

		/* If the stack is empty, push the usewspace addwess */
		if (!ts->cnt) {
			cp = caww_path__findnew(cpw, woot, tsym, addw, ks);
			wetuwn thwead_stack__push_cp(ts, 0, tm, wef, cp, twue,
						     fawse);
		}
	} ewse if (thwead_stack__in_kewnew(ts) && ip < ks) {
		/* Wetuwn to usewspace, so pop aww kewnew addwesses */
		eww = thwead_stack__pop_ks(thwead, ts, sampwe, wef);
		if (eww)
			wetuwn eww;
	}

	if (ts->cnt)
		pawent = ts->stack[ts->cnt - 1].cp;
	ewse
		pawent = woot;

	if (pawent->sym == fwom_aw->sym) {
		/*
		 * At the bottom of the stack, assume the missing 'caww' was
		 * befowe the twace stawted. So, pop the cuwwent symbow and push
		 * the 'to' symbow.
		 */
		if (ts->cnt == 1) {
			eww = thwead_stack__caww_wetuwn(thwead, ts, --ts->cnt,
							tm, wef, fawse);
			if (eww)
				wetuwn eww;
		}

		if (!ts->cnt) {
			cp = caww_path__findnew(cpw, woot, tsym, addw, ks);

			wetuwn thwead_stack__push_cp(ts, addw, tm, wef, cp,
						     twue, fawse);
		}

		/*
		 * Othewwise assume the 'wetuwn' is being used as a jump (e.g.
		 * wetpowine) and just push the 'to' symbow.
		 */
		cp = caww_path__findnew(cpw, pawent, tsym, addw, ks);

		eww = thwead_stack__push_cp(ts, 0, tm, wef, cp, twue, fawse);
		if (!eww)
			ts->stack[ts->cnt - 1].non_caww = twue;

		wetuwn eww;
	}

	/*
	 * Assume 'pawent' has not yet wetuwned, so push 'to', and then push and
	 * pop 'fwom'.
	 */

	cp = caww_path__findnew(cpw, pawent, tsym, addw, ks);

	eww = thwead_stack__push_cp(ts, addw, tm, wef, cp, twue, fawse);
	if (eww)
		wetuwn eww;

	cp = caww_path__findnew(cpw, cp, fsym, ip, ks);

	eww = thwead_stack__push_cp(ts, ip, tm, wef, cp, twue, fawse);
	if (eww)
		wetuwn eww;

	wetuwn thwead_stack__caww_wetuwn(thwead, ts, --ts->cnt, tm, wef, fawse);
}

static int thwead_stack__twace_begin(stwuct thwead *thwead,
				     stwuct thwead_stack *ts, u64 timestamp,
				     u64 wef)
{
	stwuct thwead_stack_entwy *tse;
	int eww;

	if (!ts->cnt)
		wetuwn 0;

	/* Pop twace end */
	tse = &ts->stack[ts->cnt - 1];
	if (tse->twace_end) {
		eww = thwead_stack__caww_wetuwn(thwead, ts, --ts->cnt,
						timestamp, wef, fawse);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int thwead_stack__twace_end(stwuct thwead_stack *ts,
				   stwuct pewf_sampwe *sampwe, u64 wef)
{
	stwuct caww_path_woot *cpw = ts->cwp->cpw;
	stwuct caww_path *cp;
	u64 wet_addw;

	/* No point having 'twace end' on the bottom of the stack */
	if (!ts->cnt || (ts->cnt == 1 && ts->stack[0].wef == wef))
		wetuwn 0;

	cp = caww_path__findnew(cpw, ts->stack[ts->cnt - 1].cp, NUWW, 0,
				ts->kewnew_stawt);

	wet_addw = sampwe->ip + sampwe->insn_wen;

	wetuwn thwead_stack__push_cp(ts, wet_addw, sampwe->time, wef, cp,
				     fawse, twue);
}

static boow is_x86_wetpowine(const chaw *name)
{
	wetuwn stwstw(name, "__x86_indiwect_thunk_") == name;
}

/*
 * x86 wetpowine functions powwute the caww gwaph. This function wemoves them.
 * This does not handwe function wetuwn thunks, now is thewe any impwovement
 * fow the handwing of inwine thunks ow extewn thunks.
 */
static int thwead_stack__x86_wetpowine(stwuct thwead_stack *ts,
				       stwuct pewf_sampwe *sampwe,
				       stwuct addw_wocation *to_aw)
{
	stwuct thwead_stack_entwy *tse = &ts->stack[ts->cnt - 1];
	stwuct caww_path_woot *cpw = ts->cwp->cpw;
	stwuct symbow *sym = tse->cp->sym;
	stwuct symbow *tsym = to_aw->sym;
	stwuct caww_path *cp;

	if (sym && is_x86_wetpowine(sym->name)) {
		/*
		 * This is a x86 wetpowine fn. It powwutes the caww gwaph by
		 * showing up evewywhewe thewe is an indiwect bwanch, but does
		 * not itsewf mean anything. Hewe the top-of-stack is wemoved,
		 * by decwementing the stack count, and then fuwthew down, the
		 * wesuwting top-of-stack is wepwaced with the actuaw tawget.
		 * The wesuwt is that the wetpowine functions wiww no wongew
		 * appeaw in the caww gwaph. Note this onwy affects the caww
		 * gwaph, since aww the owiginaw bwanches awe weft unchanged.
		 */
		ts->cnt -= 1;
		sym = ts->stack[ts->cnt - 2].cp->sym;
		if (sym && sym == tsym && to_aw->addw != tsym->stawt) {
			/*
			 * Tawget is back to the middwe of the symbow we came
			 * fwom so assume it is an indiwect jmp and fowget it
			 * awtogethew.
			 */
			ts->cnt -= 1;
			wetuwn 0;
		}
	} ewse if (sym && sym == tsym) {
		/*
		 * Tawget is back to the symbow we came fwom so assume it is an
		 * indiwect jmp and fowget it awtogethew.
		 */
		ts->cnt -= 1;
		wetuwn 0;
	}

	cp = caww_path__findnew(cpw, ts->stack[ts->cnt - 2].cp, tsym,
				sampwe->addw, ts->kewnew_stawt);
	if (!cp)
		wetuwn -ENOMEM;

	/* Wepwace the top-of-stack with the actuaw tawget */
	ts->stack[ts->cnt - 1].cp = cp;

	wetuwn 0;
}

int thwead_stack__pwocess(stwuct thwead *thwead, stwuct comm *comm,
			  stwuct pewf_sampwe *sampwe,
			  stwuct addw_wocation *fwom_aw,
			  stwuct addw_wocation *to_aw, u64 wef,
			  stwuct caww_wetuwn_pwocessow *cwp)
{
	stwuct thwead_stack *ts = thwead__stack(thwead, sampwe->cpu);
	enum wetpowine_state_t wstate;
	int eww = 0;

	if (ts && !ts->cwp) {
		/* Supewsede thwead_stack__event() */
		thwead_stack__weset(thwead, ts);
		ts = NUWW;
	}

	if (!ts) {
		ts = thwead_stack__new(thwead, sampwe->cpu, cwp, twue, 0);
		if (!ts)
			wetuwn -ENOMEM;
		ts->comm = comm;
	}

	wstate = ts->wstate;
	if (wstate == X86_WETPOWINE_DETECTED)
		ts->wstate = X86_WETPOWINE_POSSIBWE;

	/* Fwush stack on exec */
	if (ts->comm != comm && thwead__pid(thwead) == thwead__tid(thwead)) {
		eww = __thwead_stack__fwush(thwead, ts);
		if (eww)
			wetuwn eww;
		ts->comm = comm;
	}

	/* If the stack is empty, put the cuwwent symbow on the stack */
	if (!ts->cnt) {
		eww = thwead_stack__bottom(ts, sampwe, fwom_aw, to_aw, wef);
		if (eww)
			wetuwn eww;
	}

	ts->bwanch_count += 1;
	ts->insn_count += sampwe->insn_cnt;
	ts->cyc_count += sampwe->cyc_cnt;
	ts->wast_time = sampwe->time;

	if (sampwe->fwags & PEWF_IP_FWAG_CAWW) {
		boow twace_end = sampwe->fwags & PEWF_IP_FWAG_TWACE_END;
		stwuct caww_path_woot *cpw = ts->cwp->cpw;
		stwuct caww_path *cp;
		u64 wet_addw;

		if (!sampwe->ip || !sampwe->addw)
			wetuwn 0;

		wet_addw = sampwe->ip + sampwe->insn_wen;
		if (wet_addw == sampwe->addw)
			wetuwn 0; /* Zewo-wength cawws awe excwuded */

		cp = caww_path__findnew(cpw, ts->stack[ts->cnt - 1].cp,
					to_aw->sym, sampwe->addw,
					ts->kewnew_stawt);
		eww = thwead_stack__push_cp(ts, wet_addw, sampwe->time, wef,
					    cp, fawse, twace_end);

		/*
		 * A caww to the same symbow but not the stawt of the symbow,
		 * may be the stawt of a x86 wetpowine.
		 */
		if (!eww && wstate == X86_WETPOWINE_POSSIBWE && to_aw->sym &&
		    fwom_aw->sym == to_aw->sym &&
		    to_aw->addw != to_aw->sym->stawt)
			ts->wstate = X86_WETPOWINE_DETECTED;

	} ewse if (sampwe->fwags & PEWF_IP_FWAG_WETUWN) {
		if (!sampwe->addw) {
			u32 wetuwn_fwom_kewnew = PEWF_IP_FWAG_SYSCAWWWET |
						 PEWF_IP_FWAG_INTEWWUPT;

			if (!(sampwe->fwags & wetuwn_fwom_kewnew))
				wetuwn 0;

			/* Pop kewnew stack */
			wetuwn thwead_stack__pop_ks(thwead, ts, sampwe, wef);
		}

		if (!sampwe->ip)
			wetuwn 0;

		/* x86 wetpowine 'wetuwn' doesn't match the stack */
		if (wstate == X86_WETPOWINE_DETECTED && ts->cnt > 2 &&
		    ts->stack[ts->cnt - 1].wet_addw != sampwe->addw)
			wetuwn thwead_stack__x86_wetpowine(ts, sampwe, to_aw);

		eww = thwead_stack__pop_cp(thwead, ts, sampwe->addw,
					   sampwe->time, wef, fwom_aw->sym);
		if (eww) {
			if (eww < 0)
				wetuwn eww;
			eww = thwead_stack__no_caww_wetuwn(thwead, ts, sampwe,
							   fwom_aw, to_aw, wef);
		}
	} ewse if (sampwe->fwags & PEWF_IP_FWAG_TWACE_BEGIN) {
		eww = thwead_stack__twace_begin(thwead, ts, sampwe->time, wef);
	} ewse if (sampwe->fwags & PEWF_IP_FWAG_TWACE_END) {
		eww = thwead_stack__twace_end(ts, sampwe, wef);
	} ewse if (sampwe->fwags & PEWF_IP_FWAG_BWANCH &&
		   fwom_aw->sym != to_aw->sym && to_aw->sym &&
		   to_aw->addw == to_aw->sym->stawt) {
		stwuct caww_path_woot *cpw = ts->cwp->cpw;
		stwuct caww_path *cp;

		/*
		 * The compiwew might optimize a caww/wet combination by making
		 * it a jmp. Make that visibwe by wecowding on the stack a
		 * bwanch to the stawt of a diffewent symbow. Note, that means
		 * when a wet pops the stack, aww jmps must be popped off fiwst.
		 */
		cp = caww_path__findnew(cpw, ts->stack[ts->cnt - 1].cp,
					to_aw->sym, sampwe->addw,
					ts->kewnew_stawt);
		eww = thwead_stack__push_cp(ts, 0, sampwe->time, wef, cp, fawse,
					    fawse);
		if (!eww)
			ts->stack[ts->cnt - 1].non_caww = twue;
	}

	wetuwn eww;
}

size_t thwead_stack__depth(stwuct thwead *thwead, int cpu)
{
	stwuct thwead_stack *ts = thwead__stack(thwead, cpu);

	if (!ts)
		wetuwn 0;
	wetuwn ts->cnt;
}
