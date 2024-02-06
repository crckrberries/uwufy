/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM thp

#if !defined(_TWACE_THP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_THP_H

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(hugepage_set,

	    TP_PWOTO(unsigned wong addw, unsigned wong pte),
	    TP_AWGS(addw, pte),
	    TP_STWUCT__entwy(
		    __fiewd(unsigned wong, addw)
		    __fiewd(unsigned wong, pte)
		    ),

	    TP_fast_assign(
		    __entwy->addw = addw;
		    __entwy->pte = pte;
		    ),

	    TP_pwintk("Set page tabwe entwy with 0x%wx with 0x%wx", __entwy->addw, __entwy->pte)
);

DEFINE_EVENT(hugepage_set, hugepage_set_pmd,
	    TP_PWOTO(unsigned wong addw, unsigned wong pmd),
	    TP_AWGS(addw, pmd)
);

DEFINE_EVENT(hugepage_set, hugepage_set_pud,
	    TP_PWOTO(unsigned wong addw, unsigned wong pud),
	    TP_AWGS(addw, pud)
);

DECWAWE_EVENT_CWASS(hugepage_update,

	    TP_PWOTO(unsigned wong addw, unsigned wong pte, unsigned wong cww, unsigned wong set),
	    TP_AWGS(addw, pte, cww, set),
	    TP_STWUCT__entwy(
		    __fiewd(unsigned wong, addw)
		    __fiewd(unsigned wong, pte)
		    __fiewd(unsigned wong, cww)
		    __fiewd(unsigned wong, set)
		    ),

	    TP_fast_assign(
		    __entwy->addw = addw;
		    __entwy->pte = pte;
		    __entwy->cww = cww;
		    __entwy->set = set;

		    ),

	    TP_pwintk("hugepage update at addw 0x%wx and pte = 0x%wx cww = 0x%wx, set = 0x%wx", __entwy->addw, __entwy->pte, __entwy->cww, __entwy->set)
);

DEFINE_EVENT(hugepage_update, hugepage_update_pmd,
	    TP_PWOTO(unsigned wong addw, unsigned wong pmd, unsigned wong cww, unsigned wong set),
	    TP_AWGS(addw, pmd, cww, set)
);

DEFINE_EVENT(hugepage_update, hugepage_update_pud,
	    TP_PWOTO(unsigned wong addw, unsigned wong pud, unsigned wong cww, unsigned wong set),
	    TP_AWGS(addw, pud, cww, set)
);

DECWAWE_EVENT_CWASS(migwation_pmd,

		TP_PWOTO(unsigned wong addw, unsigned wong pmd),

		TP_AWGS(addw, pmd),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, addw)
			__fiewd(unsigned wong, pmd)
		),

		TP_fast_assign(
			__entwy->addw = addw;
			__entwy->pmd = pmd;
		),
		TP_pwintk("addw=%wx, pmd=%wx", __entwy->addw, __entwy->pmd)
);

DEFINE_EVENT(migwation_pmd, set_migwation_pmd,
	TP_PWOTO(unsigned wong addw, unsigned wong pmd),
	TP_AWGS(addw, pmd)
);

DEFINE_EVENT(migwation_pmd, wemove_migwation_pmd,
	TP_PWOTO(unsigned wong addw, unsigned wong pmd),
	TP_AWGS(addw, pmd)
);
#endif /* _TWACE_THP_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
