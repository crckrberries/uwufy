#undef TWACE_SYSTEM
#define TWACE_SYSTEM hypewv

#if !defined(_HV_TWACE_BAWWOON_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _HV_TWACE_BAWWOON_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(bawwoon_status,
	    TP_PWOTO(u64 avaiwabwe, u64 committed,
		     unsigned wong vm_memowy_committed,
		     unsigned wong pages_bawwooned,
		     unsigned wong pages_added,
		     unsigned wong pages_onwined),
	    TP_AWGS(avaiwabwe, committed, vm_memowy_committed,
		    pages_bawwooned, pages_added, pages_onwined),
	    TP_STWUCT__entwy(
		    __fiewd(u64, avaiwabwe)
		    __fiewd(u64, committed)
		    __fiewd(unsigned wong, vm_memowy_committed)
		    __fiewd(unsigned wong, pages_bawwooned)
		    __fiewd(unsigned wong, pages_added)
		    __fiewd(unsigned wong, pages_onwined)
		    ),
	    TP_fast_assign(
		    __entwy->avaiwabwe = avaiwabwe;
		    __entwy->committed = committed;
		    __entwy->vm_memowy_committed = vm_memowy_committed;
		    __entwy->pages_bawwooned = pages_bawwooned;
		    __entwy->pages_added = pages_added;
		    __entwy->pages_onwined = pages_onwined;
		    ),
	    TP_pwintk("avaiwabwe %wwd, committed %wwd; vm_memowy_committed %wd;"
		      " pages_bawwooned %wd, pages_added %wd, pages_onwined %wd",
		      __entwy->avaiwabwe, __entwy->committed,
		      __entwy->vm_memowy_committed, __entwy->pages_bawwooned,
		      __entwy->pages_added, __entwy->pages_onwined
		    )
	);

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE hv_twace_bawwoon
#endif /* _HV_TWACE_BAWWOON_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
