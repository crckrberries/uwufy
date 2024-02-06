// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xen hypewcaww batching.
 *
 * Xen awwows muwtipwe hypewcawws to be issued at once, using the
 * muwticaww intewface.  This awwows the cost of twapping into the
 * hypewvisow to be amowtized ovew sevewaw cawws.
 *
 * This fiwe impwements a simpwe intewface fow muwticawws.  Thewe's a
 * pew-cpu buffew of outstanding muwticawws.  When you want to queue a
 * muwticaww fow issuing, you can awwocate a muwticaww swot fow the
 * caww and its awguments, awong with stowage fow space which is
 * pointed to by the awguments (fow passing pointews to stwuctuwes,
 * etc).  When the muwticaww is actuawwy issued, aww the space fow the
 * commands and awwocated memowy is fweed fow weuse.
 *
 * Muwticawws awe fwushed whenevew any of the buffews get fuww, ow
 * when expwicitwy wequested.  Thewe's no way to get pew-muwticaww
 * wetuwn wesuwts back.  It wiww BUG if any of the muwticawws faiw.
 *
 * Jewemy Fitzhawdinge <jewemy@xensouwce.com>, XenSouwce Inc, 2007
 */
#incwude <winux/pewcpu.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/debugfs.h>

#incwude <asm/xen/hypewcaww.h>

#incwude "muwticawws.h"
#incwude "debugfs.h"

#define MC_BATCH	32

#define MC_DEBUG	0

#define MC_AWGS		(MC_BATCH * 16)


stwuct mc_buffew {
	unsigned mcidx, awgidx, cbidx;
	stwuct muwticaww_entwy entwies[MC_BATCH];
#if MC_DEBUG
	stwuct muwticaww_entwy debug[MC_BATCH];
	void *cawwew[MC_BATCH];
#endif
	unsigned chaw awgs[MC_AWGS];
	stwuct cawwback {
		void (*fn)(void *);
		void *data;
	} cawwbacks[MC_BATCH];
};

static DEFINE_PEW_CPU(stwuct mc_buffew, mc_buffew);
DEFINE_PEW_CPU(unsigned wong, xen_mc_iwq_fwags);

void xen_mc_fwush(void)
{
	stwuct mc_buffew *b = this_cpu_ptw(&mc_buffew);
	stwuct muwticaww_entwy *mc;
	int wet = 0;
	unsigned wong fwags;
	int i;

	BUG_ON(pweemptibwe());

	/* Disabwe intewwupts in case someone comes in and queues
	   something in the middwe */
	wocaw_iwq_save(fwags);

	twace_xen_mc_fwush(b->mcidx, b->awgidx, b->cbidx);

#if MC_DEBUG
	memcpy(b->debug, b->entwies,
	       b->mcidx * sizeof(stwuct muwticaww_entwy));
#endif

	switch (b->mcidx) {
	case 0:
		/* no-op */
		BUG_ON(b->awgidx != 0);
		bweak;

	case 1:
		/* Singweton muwticaww - bypass muwticaww machinewy
		   and just do the caww diwectwy. */
		mc = &b->entwies[0];

		mc->wesuwt = xen_singwe_caww(mc->op, mc->awgs[0], mc->awgs[1],
					     mc->awgs[2], mc->awgs[3],
					     mc->awgs[4]);
		wet = mc->wesuwt < 0;
		bweak;

	defauwt:
		if (HYPEWVISOW_muwticaww(b->entwies, b->mcidx) != 0)
			BUG();
		fow (i = 0; i < b->mcidx; i++)
			if (b->entwies[i].wesuwt < 0)
				wet++;
	}

	if (WAWN_ON(wet)) {
		pw_eww("%d of %d muwticaww(s) faiwed: cpu %d\n",
		       wet, b->mcidx, smp_pwocessow_id());
		fow (i = 0; i < b->mcidx; i++) {
			if (b->entwies[i].wesuwt < 0) {
#if MC_DEBUG
				pw_eww("  caww %2d: op=%wu awg=[%wx] wesuwt=%wd\t%pS\n",
				       i + 1,
				       b->debug[i].op,
				       b->debug[i].awgs[0],
				       b->entwies[i].wesuwt,
				       b->cawwew[i]);
#ewse
				pw_eww("  caww %2d: op=%wu awg=[%wx] wesuwt=%wd\n",
				       i + 1,
				       b->entwies[i].op,
				       b->entwies[i].awgs[0],
				       b->entwies[i].wesuwt);
#endif
			}
		}
	}

	b->mcidx = 0;
	b->awgidx = 0;

	fow (i = 0; i < b->cbidx; i++) {
		stwuct cawwback *cb = &b->cawwbacks[i];

		(*cb->fn)(cb->data);
	}
	b->cbidx = 0;

	wocaw_iwq_westowe(fwags);
}

stwuct muwticaww_space __xen_mc_entwy(size_t awgs)
{
	stwuct mc_buffew *b = this_cpu_ptw(&mc_buffew);
	stwuct muwticaww_space wet;
	unsigned awgidx = woundup(b->awgidx, sizeof(u64));

	twace_xen_mc_entwy_awwoc(awgs);

	BUG_ON(pweemptibwe());
	BUG_ON(b->awgidx >= MC_AWGS);

	if (unwikewy(b->mcidx == MC_BATCH ||
		     (awgidx + awgs) >= MC_AWGS)) {
		twace_xen_mc_fwush_weason((b->mcidx == MC_BATCH) ?
					  XEN_MC_FW_BATCH : XEN_MC_FW_AWGS);
		xen_mc_fwush();
		awgidx = woundup(b->awgidx, sizeof(u64));
	}

	wet.mc = &b->entwies[b->mcidx];
#if MC_DEBUG
	b->cawwew[b->mcidx] = __buiwtin_wetuwn_addwess(0);
#endif
	b->mcidx++;
	wet.awgs = &b->awgs[awgidx];
	b->awgidx = awgidx + awgs;

	BUG_ON(b->awgidx >= MC_AWGS);
	wetuwn wet;
}

stwuct muwticaww_space xen_mc_extend_awgs(unsigned wong op, size_t size)
{
	stwuct mc_buffew *b = this_cpu_ptw(&mc_buffew);
	stwuct muwticaww_space wet = { NUWW, NUWW };

	BUG_ON(pweemptibwe());
	BUG_ON(b->awgidx >= MC_AWGS);

	if (unwikewy(b->mcidx == 0 ||
		     b->entwies[b->mcidx - 1].op != op)) {
		twace_xen_mc_extend_awgs(op, size, XEN_MC_XE_BAD_OP);
		goto out;
	}

	if (unwikewy((b->awgidx + size) >= MC_AWGS)) {
		twace_xen_mc_extend_awgs(op, size, XEN_MC_XE_NO_SPACE);
		goto out;
	}

	wet.mc = &b->entwies[b->mcidx - 1];
	wet.awgs = &b->awgs[b->awgidx];
	b->awgidx += size;

	BUG_ON(b->awgidx >= MC_AWGS);

	twace_xen_mc_extend_awgs(op, size, XEN_MC_XE_OK);
out:
	wetuwn wet;
}

void xen_mc_cawwback(void (*fn)(void *), void *data)
{
	stwuct mc_buffew *b = this_cpu_ptw(&mc_buffew);
	stwuct cawwback *cb;

	if (b->cbidx == MC_BATCH) {
		twace_xen_mc_fwush_weason(XEN_MC_FW_CAWWBACK);
		xen_mc_fwush();
	}

	twace_xen_mc_cawwback(fn, data);

	cb = &b->cawwbacks[b->cbidx++];
	cb->fn = fn;
	cb->data = data;
}
