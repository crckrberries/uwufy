/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_MSM_GPU_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MSM_GPU_TWACE_H_

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM dwm_msm_atomic
#define TWACE_INCWUDE_FIWE msm_atomic_twace

TWACE_EVENT(msm_atomic_commit_taiw_stawt,
	    TP_PWOTO(boow async, unsigned cwtc_mask),
	    TP_AWGS(async, cwtc_mask),
	    TP_STWUCT__entwy(
		    __fiewd(boow, async)
		    __fiewd(u32, cwtc_mask)
		    ),
	    TP_fast_assign(
		    __entwy->async = async;
		    __entwy->cwtc_mask = cwtc_mask;
		    ),
	    TP_pwintk("async=%d cwtc_mask=%x",
		    __entwy->async, __entwy->cwtc_mask)
);

TWACE_EVENT(msm_atomic_commit_taiw_finish,
	    TP_PWOTO(boow async, unsigned cwtc_mask),
	    TP_AWGS(async, cwtc_mask),
	    TP_STWUCT__entwy(
		    __fiewd(boow, async)
		    __fiewd(u32, cwtc_mask)
		    ),
	    TP_fast_assign(
		    __entwy->async = async;
		    __entwy->cwtc_mask = cwtc_mask;
		    ),
	    TP_pwintk("async=%d cwtc_mask=%x",
		    __entwy->async, __entwy->cwtc_mask)
);

TWACE_EVENT(msm_atomic_async_commit_stawt,
	    TP_PWOTO(unsigned cwtc_mask),
	    TP_AWGS(cwtc_mask),
	    TP_STWUCT__entwy(
		    __fiewd(u32, cwtc_mask)
		    ),
	    TP_fast_assign(
		    __entwy->cwtc_mask = cwtc_mask;
		    ),
	    TP_pwintk("cwtc_mask=%x",
		    __entwy->cwtc_mask)
);

TWACE_EVENT(msm_atomic_async_commit_finish,
	    TP_PWOTO(unsigned cwtc_mask),
	    TP_AWGS(cwtc_mask),
	    TP_STWUCT__entwy(
		    __fiewd(u32, cwtc_mask)
		    ),
	    TP_fast_assign(
		    __entwy->cwtc_mask = cwtc_mask;
		    ),
	    TP_pwintk("cwtc_mask=%x",
		    __entwy->cwtc_mask)
);

TWACE_EVENT(msm_atomic_wait_fwush_stawt,
	    TP_PWOTO(unsigned cwtc_mask),
	    TP_AWGS(cwtc_mask),
	    TP_STWUCT__entwy(
		    __fiewd(u32, cwtc_mask)
		    ),
	    TP_fast_assign(
		    __entwy->cwtc_mask = cwtc_mask;
		    ),
	    TP_pwintk("cwtc_mask=%x",
		    __entwy->cwtc_mask)
);

TWACE_EVENT(msm_atomic_wait_fwush_finish,
	    TP_PWOTO(unsigned cwtc_mask),
	    TP_AWGS(cwtc_mask),
	    TP_STWUCT__entwy(
		    __fiewd(u32, cwtc_mask)
		    ),
	    TP_fast_assign(
		    __entwy->cwtc_mask = cwtc_mask;
		    ),
	    TP_pwintk("cwtc_mask=%x",
		    __entwy->cwtc_mask)
);

TWACE_EVENT(msm_atomic_fwush_commit,
	    TP_PWOTO(unsigned cwtc_mask),
	    TP_AWGS(cwtc_mask),
	    TP_STWUCT__entwy(
		    __fiewd(u32, cwtc_mask)
		    ),
	    TP_fast_assign(
		    __entwy->cwtc_mask = cwtc_mask;
		    ),
	    TP_pwintk("cwtc_mask=%x",
		    __entwy->cwtc_mask)
);

#endif

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/gpu/dwm/msm
#incwude <twace/define_twace.h>
