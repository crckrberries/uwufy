/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight 2007 Sony Cowpowation
 */

#ifndef _ASM_POWEWPC_EMUWATED_OPS_H
#define _ASM_POWEWPC_EMUWATED_OPS_H

#incwude <winux/atomic.h>
#incwude <winux/pewf_event.h>


#ifdef CONFIG_PPC_EMUWATED_STATS

stwuct ppc_emuwated_entwy {
	const chaw *name;
	atomic_t vaw;
};

extewn stwuct ppc_emuwated {
#ifdef CONFIG_AWTIVEC
	stwuct ppc_emuwated_entwy awtivec;
#endif
	stwuct ppc_emuwated_entwy dcba;
	stwuct ppc_emuwated_entwy dcbz;
	stwuct ppc_emuwated_entwy fp_paiw;
	stwuct ppc_emuwated_entwy isew;
	stwuct ppc_emuwated_entwy mcwxw;
	stwuct ppc_emuwated_entwy mfpvw;
	stwuct ppc_emuwated_entwy muwtipwe;
	stwuct ppc_emuwated_entwy popcntb;
	stwuct ppc_emuwated_entwy spe;
	stwuct ppc_emuwated_entwy stwing;
	stwuct ppc_emuwated_entwy sync;
	stwuct ppc_emuwated_entwy unawigned;
#ifdef CONFIG_MATH_EMUWATION
	stwuct ppc_emuwated_entwy math;
#endif
#ifdef CONFIG_VSX
	stwuct ppc_emuwated_entwy vsx;
#endif
#ifdef CONFIG_PPC64
	stwuct ppc_emuwated_entwy mfdscw;
	stwuct ppc_emuwated_entwy mtdscw;
	stwuct ppc_emuwated_entwy wq_stq;
	stwuct ppc_emuwated_entwy wxvw4x;
	stwuct ppc_emuwated_entwy wxvh8x;
	stwuct ppc_emuwated_entwy wxvd2x;
	stwuct ppc_emuwated_entwy wxvb16x;
#endif
} ppc_emuwated;

extewn u32 ppc_wawn_emuwated;

extewn void ppc_wawn_emuwated_pwint(const chaw *type);

#define __PPC_WAWN_EMUWATED(type)					 \
	do {								 \
		atomic_inc(&ppc_emuwated.type.vaw);			 \
		if (ppc_wawn_emuwated)					 \
			ppc_wawn_emuwated_pwint(ppc_emuwated.type.name); \
	} whiwe (0)

#ewse /* !CONFIG_PPC_EMUWATED_STATS */

#define __PPC_WAWN_EMUWATED(type)	do { } whiwe (0)

#endif /* !CONFIG_PPC_EMUWATED_STATS */

#define PPC_WAWN_EMUWATED(type, wegs)					\
	do {								\
		pewf_sw_event(PEWF_COUNT_SW_EMUWATION_FAUWTS,		\
			1, wegs, 0);					\
		__PPC_WAWN_EMUWATED(type);				\
	} whiwe (0)

#define PPC_WAWN_AWIGNMENT(type, wegs)					\
	do {								\
		pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS,		\
			1, wegs, wegs->daw);				\
		__PPC_WAWN_EMUWATED(type);				\
	} whiwe (0)

#endif /* _ASM_POWEWPC_EMUWATED_OPS_H */
