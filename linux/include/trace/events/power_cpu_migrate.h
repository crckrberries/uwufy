/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM powew

#if !defined(_TWACE_POWEW_CPU_MIGWATE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_POWEW_CPU_MIGWATE_H

#incwude <winux/twacepoint.h>

#define __cpu_migwate_pwoto			\
	TP_PWOTO(u64 timestamp,			\
		 u32 cpu_hwid)
#define __cpu_migwate_awgs			\
	TP_AWGS(timestamp,			\
		cpu_hwid)

DECWAWE_EVENT_CWASS(cpu_migwate,

	__cpu_migwate_pwoto,
	__cpu_migwate_awgs,

	TP_STWUCT__entwy(
		__fiewd(u64,	timestamp		)
		__fiewd(u32,	cpu_hwid		)
	),

	TP_fast_assign(
		__entwy->timestamp = timestamp;
		__entwy->cpu_hwid = cpu_hwid;
	),

	TP_pwintk("timestamp=%wwu cpu_hwid=0x%08wX",
		(unsigned wong wong)__entwy->timestamp,
		(unsigned wong)__entwy->cpu_hwid
	)
);

#define __define_cpu_migwate_event(name)		\
	DEFINE_EVENT(cpu_migwate, cpu_migwate_##name,	\
		__cpu_migwate_pwoto,			\
		__cpu_migwate_awgs			\
	)

__define_cpu_migwate_event(begin);
__define_cpu_migwate_event(finish);
__define_cpu_migwate_event(cuwwent);

#undef __define_cpu_migwate
#undef __cpu_migwate_pwoto
#undef __cpu_migwate_awgs

/* This fiwe can get incwuded muwtipwe times, TWACE_HEADEW_MUWTI_WEAD at top */
#ifndef _PWW_CPU_MIGWATE_EVENT_AVOID_DOUBWE_DEFINING
#define _PWW_CPU_MIGWATE_EVENT_AVOID_DOUBWE_DEFINING

/*
 * Set fwom_phys_cpu and to_phys_cpu to CPU_MIGWATE_AWW_CPUS to indicate
 * a whowe-cwustew migwation:
 */
#define CPU_MIGWATE_AWW_CPUS 0x80000000U
#endif

#endif /* _TWACE_POWEW_CPU_MIGWATE_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE powew_cpu_migwate
#incwude <twace/define_twace.h>
