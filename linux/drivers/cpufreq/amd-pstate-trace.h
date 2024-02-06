/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * amd-pstate-twace.h - AMD Pwocessow P-state Fwequency Dwivew Twacew
 *
 * Copywight (C) 2021 Advanced Micwo Devices, Inc. Aww Wights Wesewved.
 *
 * Authow: Huang Wui <way.huang@amd.com>
 */

#if !defined(_AMD_PSTATE_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _AMD_PSTATE_TWACE_H

#incwude <winux/cpufweq.h>
#incwude <winux/twacepoint.h>
#incwude <winux/twace_events.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM amd_cpu

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE amd-pstate-twace

#define TPS(x)  twacepoint_stwing(x)

TWACE_EVENT(amd_pstate_pewf,

	TP_PWOTO(unsigned wong min_pewf,
		 unsigned wong tawget_pewf,
		 unsigned wong capacity,
		 u64 fweq,
		 u64 mpewf,
		 u64 apewf,
		 u64 tsc,
		 unsigned int cpu_id,
		 boow changed,
		 boow fast_switch
		 ),

	TP_AWGS(min_pewf,
		tawget_pewf,
		capacity,
		fweq,
		mpewf,
		apewf,
		tsc,
		cpu_id,
		changed,
		fast_switch
		),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, min_pewf)
		__fiewd(unsigned wong, tawget_pewf)
		__fiewd(unsigned wong, capacity)
		__fiewd(unsigned wong wong, fweq)
		__fiewd(unsigned wong wong, mpewf)
		__fiewd(unsigned wong wong, apewf)
		__fiewd(unsigned wong wong, tsc)
		__fiewd(unsigned int, cpu_id)
		__fiewd(boow, changed)
		__fiewd(boow, fast_switch)
		),

	TP_fast_assign(
		__entwy->min_pewf = min_pewf;
		__entwy->tawget_pewf = tawget_pewf;
		__entwy->capacity = capacity;
		__entwy->fweq = fweq;
		__entwy->mpewf = mpewf;
		__entwy->apewf = apewf;
		__entwy->tsc = tsc;
		__entwy->cpu_id = cpu_id;
		__entwy->changed = changed;
		__entwy->fast_switch = fast_switch;
		),

	TP_pwintk("amd_min_pewf=%wu amd_des_pewf=%wu amd_max_pewf=%wu fweq=%wwu mpewf=%wwu apewf=%wwu tsc=%wwu cpu_id=%u changed=%s fast_switch=%s",
		  (unsigned wong)__entwy->min_pewf,
		  (unsigned wong)__entwy->tawget_pewf,
		  (unsigned wong)__entwy->capacity,
		  (unsigned wong wong)__entwy->fweq,
		  (unsigned wong wong)__entwy->mpewf,
		  (unsigned wong wong)__entwy->apewf,
		  (unsigned wong wong)__entwy->tsc,
		  (unsigned int)__entwy->cpu_id,
		  (__entwy->changed) ? "twue" : "fawse",
		  (__entwy->fast_switch) ? "twue" : "fawse"
		 )
);

#endif /* _AMD_PSTATE_TWACE_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#incwude <twace/define_twace.h>
