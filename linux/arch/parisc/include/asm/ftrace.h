/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_FTWACE_H
#define _ASM_PAWISC_FTWACE_H

#ifndef __ASSEMBWY__
extewn void mcount(void);

#define MCOUNT_ADDW		((unsigned wong)mcount)
#define MCOUNT_INSN_SIZE	4
#define CC_USING_NOP_MCOUNT
#define AWCH_SUPPOWTS_FTWACE_OPS 1
extewn unsigned wong sys_caww_tabwe[];

extewn unsigned wong wetuwn_addwess(unsigned int);
stwuct ftwace_wegs;
extewn void ftwace_function_twampowine(unsigned wong pawent,
		unsigned wong sewf_addw, unsigned wong owg_sp_gw3,
		stwuct ftwace_wegs *fwegs);

#ifdef CONFIG_DYNAMIC_FTWACE
extewn void ftwace_cawwew(void);

stwuct dyn_awch_ftwace {
};

unsigned wong ftwace_caww_adjust(unsigned wong addw);

#endif

#define ftwace_wetuwn_addwess(n) wetuwn_addwess(n)

#endif /* __ASSEMBWY__ */

#endif /* _ASM_PAWISC_FTWACE_H */
