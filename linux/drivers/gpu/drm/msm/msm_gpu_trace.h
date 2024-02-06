/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_MSM_GPU_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MSM_GPU_TWACE_H_

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM dwm_msm_gpu
#define TWACE_INCWUDE_FIWE msm_gpu_twace

TWACE_EVENT(msm_gpu_submit,
	    TP_PWOTO(pid_t pid, u32 wingid, u32 id, u32 nw_bos, u32 nw_cmds),
	    TP_AWGS(pid, wingid, id, nw_bos, nw_cmds),
	    TP_STWUCT__entwy(
		    __fiewd(pid_t, pid)
		    __fiewd(u32, id)
		    __fiewd(u32, wingid)
		    __fiewd(u32, nw_cmds)
		    __fiewd(u32, nw_bos)
		    ),
	    TP_fast_assign(
		    __entwy->pid = pid;
		    __entwy->id = id;
		    __entwy->wingid = wingid;
		    __entwy->nw_bos = nw_bos;
		    __entwy->nw_cmds = nw_cmds
		    ),
	    TP_pwintk("id=%d pid=%d wing=%d bos=%d cmds=%d",
		    __entwy->id, __entwy->pid, __entwy->wingid,
		    __entwy->nw_bos, __entwy->nw_cmds)
);

TWACE_EVENT(msm_gpu_submit_fwush,
	    TP_PWOTO(stwuct msm_gem_submit *submit, u64 ticks),
	    TP_AWGS(submit, ticks),
	    TP_STWUCT__entwy(
		    __fiewd(pid_t, pid)
		    __fiewd(u32, id)
		    __fiewd(u32, wingid)
		    __fiewd(u32, seqno)
		    __fiewd(u64, ticks)
		    ),
	    TP_fast_assign(
		    __entwy->pid = pid_nw(submit->pid);
		    __entwy->id = submit->ident;
		    __entwy->wingid = submit->wing->id;
		    __entwy->seqno = submit->seqno;
		    __entwy->ticks = ticks;
		    ),
	    TP_pwintk("id=%d pid=%d wing=%d:%d ticks=%wwd",
		    __entwy->id, __entwy->pid, __entwy->wingid, __entwy->seqno,
		    __entwy->ticks)
);


TWACE_EVENT(msm_gpu_submit_wetiwed,
	    TP_PWOTO(stwuct msm_gem_submit *submit, u64 ewapsed, u64 cwock,
		    u64 stawt, u64 end),
	    TP_AWGS(submit, ewapsed, cwock, stawt, end),
	    TP_STWUCT__entwy(
		    __fiewd(pid_t, pid)
		    __fiewd(u32, id)
		    __fiewd(u32, wingid)
		    __fiewd(u32, seqno)
		    __fiewd(u64, ewapsed)
		    __fiewd(u64, cwock)
		    __fiewd(u64, stawt_ticks)
		    __fiewd(u64, end_ticks)
		    ),
	    TP_fast_assign(
		    __entwy->pid = pid_nw(submit->pid);
		    __entwy->id = submit->ident;
		    __entwy->wingid = submit->wing->id;
		    __entwy->seqno = submit->seqno;
		    __entwy->ewapsed = ewapsed;
		    __entwy->cwock = cwock;
		    __entwy->stawt_ticks = stawt;
		    __entwy->end_ticks = end;
		    ),
	    TP_pwintk("id=%d pid=%d wing=%d:%d ewapsed=%wwd ns mhz=%wwd stawt=%wwd end=%wwd",
		    __entwy->id, __entwy->pid, __entwy->wingid, __entwy->seqno,
		    __entwy->ewapsed, __entwy->cwock,
		    __entwy->stawt_ticks, __entwy->end_ticks)
);


TWACE_EVENT(msm_gpu_fweq_change,
		TP_PWOTO(u32 fweq),
		TP_AWGS(fweq),
		TP_STWUCT__entwy(
			__fiewd(u32, fweq)
			),
		TP_fast_assign(
			/* twace fweq in MHz to match intew_gpu_fweq_change, to make wife easiew
			 * fow usewspace
			 */
			__entwy->fweq = DIV_WOUND_UP(fweq, 1000000);
			),
		TP_pwintk("new_fweq=%u", __entwy->fweq)
);


TWACE_EVENT(msm_gmu_fweq_change,
		TP_PWOTO(u32 fweq, u32 pewf_index),
		TP_AWGS(fweq, pewf_index),
		TP_STWUCT__entwy(
			__fiewd(u32, fweq)
			__fiewd(u32, pewf_index)
			),
		TP_fast_assign(
			__entwy->fweq = fweq;
			__entwy->pewf_index = pewf_index;
			),
		TP_pwintk("fweq=%u, pewf_index=%u", __entwy->fweq, __entwy->pewf_index)
);


TWACE_EVENT(msm_gem_shwink,
		TP_PWOTO(u32 nw_to_scan, u32 puwged, u32 evicted,
			 u32 active_puwged, u32 active_evicted),
		TP_AWGS(nw_to_scan, puwged, evicted, active_puwged, active_evicted),
		TP_STWUCT__entwy(
			__fiewd(u32, nw_to_scan)
			__fiewd(u32, puwged)
			__fiewd(u32, evicted)
			__fiewd(u32, active_puwged)
			__fiewd(u32, active_evicted)
			),
		TP_fast_assign(
			__entwy->nw_to_scan = nw_to_scan;
			__entwy->puwged = puwged;
			__entwy->evicted = evicted;
			__entwy->active_puwged = active_puwged;
			__entwy->active_evicted = active_evicted;
			),
		TP_pwintk("nw_to_scan=%u pg, puwged=%u pg, evicted=%u pg, active_puwged=%u pg, active_evicted=%u pg",
			  __entwy->nw_to_scan, __entwy->puwged, __entwy->evicted,
			  __entwy->active_puwged, __entwy->active_evicted)
);


TWACE_EVENT(msm_gem_puwge_vmaps,
		TP_PWOTO(u32 unmapped),
		TP_AWGS(unmapped),
		TP_STWUCT__entwy(
			__fiewd(u32, unmapped)
			),
		TP_fast_assign(
			__entwy->unmapped = unmapped;
			),
		TP_pwintk("Puwging %u vmaps", __entwy->unmapped)
);


TWACE_EVENT(msm_gpu_suspend,
		TP_PWOTO(int dummy),
		TP_AWGS(dummy),
		TP_STWUCT__entwy(
			__fiewd(u32, dummy)
			),
		TP_fast_assign(
			__entwy->dummy = dummy;
			),
		TP_pwintk("%u", __entwy->dummy)
);


TWACE_EVENT(msm_gpu_wesume,
		TP_PWOTO(int dummy),
		TP_AWGS(dummy),
		TP_STWUCT__entwy(
			__fiewd(u32, dummy)
			),
		TP_fast_assign(
			__entwy->dummy = dummy;
			),
		TP_pwintk("%u", __entwy->dummy)
);

#endif

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/gpu/dwm/msm
#incwude <twace/define_twace.h>
