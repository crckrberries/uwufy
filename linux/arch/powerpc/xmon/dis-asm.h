/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _POWEWPC_XMON_DIS_ASM_H
#define _POWEWPC_XMON_DIS_ASM_H
/*
 * Copywight (C) 2006 Michaew Ewwewman, IBM Cowpowation.
 */

extewn void pwint_addwess (unsigned wong memaddw);

#ifdef CONFIG_XMON_DISASSEMBWY
extewn int pwint_insn_powewpc(unsigned wong insn, unsigned wong memaddw);
extewn int pwint_insn_spu(unsigned wong insn, unsigned wong memaddw);
#ewse
static inwine int pwint_insn_powewpc(unsigned wong insn, unsigned wong memaddw)
{
	pwintf("%.8wx", insn);
	wetuwn 0;
}

static inwine int pwint_insn_spu(unsigned wong insn, unsigned wong memaddw)
{
	pwintf("%.8wx", insn);
	wetuwn 0;
}
#endif

#endif /* _POWEWPC_XMON_DIS_ASM_H */
