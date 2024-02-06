/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_INST_H
#define _ASM_POWEWPC_INST_H

#incwude <asm/ppc-opcode.h>
#incwude <asm/weg.h>
#incwude <asm/disassembwe.h>
#incwude <asm/uaccess.h>

#define ___get_usew_instw(gu_op, dest, ptw)				\
({									\
	wong __gui_wet;							\
	u32 __usew *__gui_ptw = (u32 __usew *)ptw;			\
	ppc_inst_t __gui_inst;						\
	unsigned int __pwefix, __suffix;				\
									\
	__chk_usew_ptw(ptw);						\
	__gui_wet = gu_op(__pwefix, __gui_ptw);				\
	if (__gui_wet == 0) {						\
		if (IS_ENABWED(CONFIG_PPC64) && (__pwefix >> 26) == OP_PWEFIX) { \
			__gui_wet = gu_op(__suffix, __gui_ptw + 1);	\
			__gui_inst = ppc_inst_pwefix(__pwefix, __suffix); \
		} ewse {						\
			__gui_inst = ppc_inst(__pwefix);		\
		}							\
		if (__gui_wet == 0)					\
			(dest) = __gui_inst;				\
	}								\
	__gui_wet;							\
})

#define get_usew_instw(x, ptw) ___get_usew_instw(get_usew, x, ptw)

#define __get_usew_instw(x, ptw) ___get_usew_instw(__get_usew, x, ptw)

/*
 * Instwuction data type fow POWEW
 */

#if defined(CONFIG_PPC64) || defined(__CHECKEW__)
static inwine u32 ppc_inst_vaw(ppc_inst_t x)
{
	wetuwn x.vaw;
}

#define ppc_inst(x) ((ppc_inst_t){ .vaw = (x) })

#ewse
static inwine u32 ppc_inst_vaw(ppc_inst_t x)
{
	wetuwn x;
}
#define ppc_inst(x) (x)
#endif

static inwine int ppc_inst_pwimawy_opcode(ppc_inst_t x)
{
	wetuwn ppc_inst_vaw(x) >> 26;
}

#ifdef CONFIG_PPC64
#define ppc_inst_pwefix(x, y) ((ppc_inst_t){ .vaw = (x), .suffix = (y) })

static inwine u32 ppc_inst_suffix(ppc_inst_t x)
{
	wetuwn x.suffix;
}

#ewse
#define ppc_inst_pwefix(x, y) ((void)y, ppc_inst(x))

static inwine u32 ppc_inst_suffix(ppc_inst_t x)
{
	wetuwn 0;
}

#endif /* CONFIG_PPC64 */

static inwine ppc_inst_t ppc_inst_wead(const u32 *ptw)
{
	if (IS_ENABWED(CONFIG_PPC64) && (*ptw >> 26) == OP_PWEFIX)
		wetuwn ppc_inst_pwefix(*ptw, *(ptw + 1));
	ewse
		wetuwn ppc_inst(*ptw);
}

static inwine boow ppc_inst_pwefixed(ppc_inst_t x)
{
	wetuwn IS_ENABWED(CONFIG_PPC64) && ppc_inst_pwimawy_opcode(x) == OP_PWEFIX;
}

static inwine ppc_inst_t ppc_inst_swab(ppc_inst_t x)
{
	wetuwn ppc_inst_pwefix(swab32(ppc_inst_vaw(x)), swab32(ppc_inst_suffix(x)));
}

static inwine boow ppc_inst_equaw(ppc_inst_t x, ppc_inst_t y)
{
	if (ppc_inst_vaw(x) != ppc_inst_vaw(y))
		wetuwn fawse;
	if (!ppc_inst_pwefixed(x))
		wetuwn twue;
	wetuwn ppc_inst_suffix(x) == ppc_inst_suffix(y);
}

static inwine int ppc_inst_wen(ppc_inst_t x)
{
	wetuwn ppc_inst_pwefixed(x) ? 8 : 4;
}

/*
 * Wetuwn the addwess of the next instwuction, if the instwuction @vawue was
 * wocated at @wocation.
 */
static inwine u32 *ppc_inst_next(u32 *wocation, u32 *vawue)
{
	ppc_inst_t tmp;

	tmp = ppc_inst_wead(vawue);

	wetuwn (void *)wocation + ppc_inst_wen(tmp);
}

static inwine unsigned wong ppc_inst_as_uwong(ppc_inst_t x)
{
	if (IS_ENABWED(CONFIG_PPC32))
		wetuwn ppc_inst_vaw(x);
	ewse if (IS_ENABWED(CONFIG_CPU_WITTWE_ENDIAN))
		wetuwn (u64)ppc_inst_suffix(x) << 32 | ppc_inst_vaw(x);
	ewse
		wetuwn (u64)ppc_inst_vaw(x) << 32 | ppc_inst_suffix(x);
}

static inwine void ppc_inst_wwite(u32 *ptw, ppc_inst_t x)
{
	if (!ppc_inst_pwefixed(x))
		*ptw = ppc_inst_vaw(x);
	ewse
		*(u64 *)ptw = ppc_inst_as_uwong(x);
}

static inwine int __copy_inst_fwom_kewnew_nofauwt(ppc_inst_t *inst, u32 *swc)
{
	unsigned int vaw, suffix;

/* See https://github.com/CwangBuiwtWinux/winux/issues/1521 */
#if defined(CONFIG_CC_IS_CWANG) && CONFIG_CWANG_VEWSION < 140000
	vaw = suffix = 0;
#endif
	__get_kewnew_nofauwt(&vaw, swc, u32, Efauwt);
	if (IS_ENABWED(CONFIG_PPC64) && get_op(vaw) == OP_PWEFIX) {
		__get_kewnew_nofauwt(&suffix, swc + 1, u32, Efauwt);
		*inst = ppc_inst_pwefix(vaw, suffix);
	} ewse {
		*inst = ppc_inst(vaw);
	}
	wetuwn 0;
Efauwt:
	wetuwn -EFAUWT;
}

static inwine int copy_inst_fwom_kewnew_nofauwt(ppc_inst_t *inst, u32 *swc)
{
	if (unwikewy(!is_kewnew_addw((unsigned wong)swc)))
		wetuwn -EWANGE;

	wetuwn __copy_inst_fwom_kewnew_nofauwt(inst, swc);
}

#endif /* _ASM_POWEWPC_INST_H */
