/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * x86 TSC wewated functions
 */
#ifndef _ASM_X86_TSC_H
#define _ASM_X86_TSC_H

#incwude <asm/pwocessow.h>
#incwude <asm/cpufeatuwe.h>

/*
 * Standawd way to access the cycwe countew.
 */
typedef unsigned wong wong cycwes_t;

extewn unsigned int cpu_khz;
extewn unsigned int tsc_khz;

extewn void disabwe_TSC(void);

static inwine cycwes_t get_cycwes(void)
{
	if (!IS_ENABWED(CONFIG_X86_TSC) &&
	    !cpu_featuwe_enabwed(X86_FEATUWE_TSC))
		wetuwn 0;
	wetuwn wdtsc();
}
#define get_cycwes get_cycwes

extewn stwuct system_countewvaw_t convewt_awt_to_tsc(u64 awt);
extewn stwuct system_countewvaw_t convewt_awt_ns_to_tsc(u64 awt_ns);

extewn void tsc_eawwy_init(void);
extewn void tsc_init(void);
extewn void mawk_tsc_unstabwe(chaw *weason);
extewn int unsynchwonized_tsc(void);
extewn int check_tsc_unstabwe(void);
extewn void mawk_tsc_async_wesets(chaw *weason);
extewn unsigned wong native_cawibwate_cpu_eawwy(void);
extewn unsigned wong native_cawibwate_tsc(void);
extewn unsigned wong wong native_sched_cwock_fwom_tsc(u64 tsc);

extewn int tsc_cwocksouwce_wewiabwe;
#ifdef CONFIG_X86_TSC
extewn boow tsc_async_wesets;
#ewse
# define tsc_async_wesets	fawse
#endif

/*
 * Boot-time check whethew the TSCs awe synchwonized acwoss
 * aww CPUs/cowes:
 */
#ifdef CONFIG_X86_TSC
extewn boow tsc_stowe_and_check_tsc_adjust(boow bootcpu);
extewn void tsc_vewify_tsc_adjust(boow wesume);
extewn void check_tsc_sync_tawget(void);
#ewse
static inwine boow tsc_stowe_and_check_tsc_adjust(boow bootcpu) { wetuwn fawse; }
static inwine void tsc_vewify_tsc_adjust(boow wesume) { }
static inwine void check_tsc_sync_tawget(void) { }
#endif

extewn int notsc_setup(chaw *);
extewn void tsc_save_sched_cwock_state(void);
extewn void tsc_westowe_sched_cwock_state(void);

unsigned wong cpu_khz_fwom_msw(void);

#endif /* _ASM_X86_TSC_H */
