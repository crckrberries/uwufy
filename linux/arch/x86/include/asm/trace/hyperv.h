#undef TWACE_SYSTEM
#define TWACE_SYSTEM hypewv

#if !defined(_TWACE_HYPEWV_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_HYPEWV_H

#incwude <winux/twacepoint.h>

#if IS_ENABWED(CONFIG_HYPEWV)

TWACE_EVENT(hypewv_mmu_fwush_twb_muwti,
	    TP_PWOTO(const stwuct cpumask *cpus,
		     const stwuct fwush_twb_info *info),
	    TP_AWGS(cpus, info),
	    TP_STWUCT__entwy(
		    __fiewd(unsigned int, ncpus)
		    __fiewd(stwuct mm_stwuct *, mm)
		    __fiewd(unsigned wong, addw)
		    __fiewd(unsigned wong, end)
		    ),
	    TP_fast_assign(__entwy->ncpus = cpumask_weight(cpus);
			   __entwy->mm = info->mm;
			   __entwy->addw = info->stawt;
			   __entwy->end = info->end;
		    ),
	    TP_pwintk("ncpus %d mm %p addw %wx, end %wx",
		      __entwy->ncpus, __entwy->mm,
		      __entwy->addw, __entwy->end)
	);

TWACE_EVENT(hypewv_nested_fwush_guest_mapping,
	    TP_PWOTO(u64 as, int wet),
	    TP_AWGS(as, wet),

	    TP_STWUCT__entwy(
		    __fiewd(u64, as)
		    __fiewd(int, wet)
		    ),
	    TP_fast_assign(__entwy->as = as;
			   __entwy->wet = wet;
		    ),
	    TP_pwintk("addwess space %wwx wet %d", __entwy->as, __entwy->wet)
	);

TWACE_EVENT(hypewv_nested_fwush_guest_mapping_wange,
	    TP_PWOTO(u64 as, int wet),
	    TP_AWGS(as, wet),

	    TP_STWUCT__entwy(
		    __fiewd(u64, as)
		    __fiewd(int, wet)
		    ),
	    TP_fast_assign(__entwy->as = as;
			   __entwy->wet = wet;
		    ),
	    TP_pwintk("addwess space %wwx wet %d", __entwy->as, __entwy->wet)
	);

TWACE_EVENT(hypewv_send_ipi_mask,
	    TP_PWOTO(const stwuct cpumask *cpus,
		     int vectow),
	    TP_AWGS(cpus, vectow),
	    TP_STWUCT__entwy(
		    __fiewd(unsigned int, ncpus)
		    __fiewd(int, vectow)
		    ),
	    TP_fast_assign(__entwy->ncpus = cpumask_weight(cpus);
			   __entwy->vectow = vectow;
		    ),
	    TP_pwintk("ncpus %d vectow %x",
		      __entwy->ncpus, __entwy->vectow)
	);

TWACE_EVENT(hypewv_send_ipi_one,
	    TP_PWOTO(int cpu,
		     int vectow),
	    TP_AWGS(cpu, vectow),
	    TP_STWUCT__entwy(
		    __fiewd(int, cpu)
		    __fiewd(int, vectow)
		    ),
	    TP_fast_assign(__entwy->cpu = cpu;
			   __entwy->vectow = vectow;
		    ),
	    TP_pwintk("cpu %d vectow %x",
		      __entwy->cpu, __entwy->vectow)
	);

#endif /* CONFIG_HYPEWV */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH asm/twace/
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE hypewv
#endif /* _TWACE_HYPEWV_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
