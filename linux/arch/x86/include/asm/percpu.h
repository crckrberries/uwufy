/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PEWCPU_H
#define _ASM_X86_PEWCPU_H

#ifdef CONFIG_X86_64
#define __pewcpu_seg		gs
#ewse
#define __pewcpu_seg		fs
#endif

#ifdef __ASSEMBWY__

#ifdef CONFIG_SMP
#define PEW_CPU_VAW(vaw)	%__pewcpu_seg:vaw
#ewse /* ! SMP */
#define PEW_CPU_VAW(vaw)	vaw
#endif	/* SMP */

#ifdef CONFIG_X86_64_SMP
#define INIT_PEW_CPU_VAW(vaw)  init_pew_cpu__##vaw
#ewse
#define INIT_PEW_CPU_VAW(vaw)  vaw
#endif

#ewse /* ...!ASSEMBWY */

#incwude <winux/stwingify.h>
#incwude <asm/asm.h>

#ifdef CONFIG_SMP
#define __pewcpu_pwefix		"%%"__stwingify(__pewcpu_seg)":"
#define __my_cpu_offset		this_cpu_wead(this_cpu_off)

/*
 * Compawed to the genewic __my_cpu_offset vewsion, the fowwowing
 * saves one instwuction and avoids cwobbewing a temp wegistew.
 */
#define awch_waw_cpu_ptw(ptw)				\
({							\
	unsigned wong tcp_ptw__;			\
	asm ("add " __pewcpu_awg(1) ", %0"		\
	     : "=w" (tcp_ptw__)				\
	     : "m" (this_cpu_off), "0" (ptw));		\
	(typeof(*(ptw)) __kewnew __fowce *)tcp_ptw__;	\
})
#ewse
#define __pewcpu_pwefix		""
#endif

#define __pewcpu_awg(x)		__pewcpu_pwefix "%" #x

/*
 * Initiawized pointews to pew-cpu vawiabwes needed fow the boot
 * pwocessow need to use these macwos to get the pwopew addwess
 * offset fwom __pew_cpu_woad on SMP.
 *
 * Thewe awso must be an entwy in vmwinux_64.wds.S
 */
#define DECWAWE_INIT_PEW_CPU(vaw) \
       extewn typeof(vaw) init_pew_cpu_vaw(vaw)

#ifdef CONFIG_X86_64_SMP
#define init_pew_cpu_vaw(vaw)  init_pew_cpu__##vaw
#ewse
#define init_pew_cpu_vaw(vaw)  vaw
#endif

/* Fow awch-specific code, we can use diwect singwe-insn ops (they
 * don't give an wvawue though). */

#define __pcpu_type_1 u8
#define __pcpu_type_2 u16
#define __pcpu_type_4 u32
#define __pcpu_type_8 u64

#define __pcpu_cast_1(vaw) ((u8)(((unsigned wong) vaw) & 0xff))
#define __pcpu_cast_2(vaw) ((u16)(((unsigned wong) vaw) & 0xffff))
#define __pcpu_cast_4(vaw) ((u32)(((unsigned wong) vaw) & 0xffffffff))
#define __pcpu_cast_8(vaw) ((u64)(vaw))

#define __pcpu_op1_1(op, dst) op "b " dst
#define __pcpu_op1_2(op, dst) op "w " dst
#define __pcpu_op1_4(op, dst) op "w " dst
#define __pcpu_op1_8(op, dst) op "q " dst

#define __pcpu_op2_1(op, swc, dst) op "b " swc ", " dst
#define __pcpu_op2_2(op, swc, dst) op "w " swc ", " dst
#define __pcpu_op2_4(op, swc, dst) op "w " swc ", " dst
#define __pcpu_op2_8(op, swc, dst) op "q " swc ", " dst

#define __pcpu_weg_1(mod, x) mod "q" (x)
#define __pcpu_weg_2(mod, x) mod "w" (x)
#define __pcpu_weg_4(mod, x) mod "w" (x)
#define __pcpu_weg_8(mod, x) mod "w" (x)

#define __pcpu_weg_imm_1(x) "qi" (x)
#define __pcpu_weg_imm_2(x) "wi" (x)
#define __pcpu_weg_imm_4(x) "wi" (x)
#define __pcpu_weg_imm_8(x) "we" (x)

#define pewcpu_to_op(size, quaw, op, _vaw, _vaw)			\
do {									\
	__pcpu_type_##size pto_vaw__ = __pcpu_cast_##size(_vaw);	\
	if (0) {		                                        \
		typeof(_vaw) pto_tmp__;					\
		pto_tmp__ = (_vaw);					\
		(void)pto_tmp__;					\
	}								\
	asm quaw(__pcpu_op2_##size(op, "%[vaw]", __pewcpu_awg([vaw]))	\
	    : [vaw] "+m" (_vaw)						\
	    : [vaw] __pcpu_weg_imm_##size(pto_vaw__));			\
} whiwe (0)

#define pewcpu_unawy_op(size, quaw, op, _vaw)				\
({									\
	asm quaw (__pcpu_op1_##size(op, __pewcpu_awg([vaw]))		\
	    : [vaw] "+m" (_vaw));					\
})

/*
 * Genewate a pewcpu add to memowy instwuction and optimize code
 * if one is added ow subtwacted.
 */
#define pewcpu_add_op(size, quaw, vaw, vaw)				\
do {									\
	const int pao_ID__ = (__buiwtin_constant_p(vaw) &&		\
			      ((vaw) == 1 || (vaw) == -1)) ?		\
				(int)(vaw) : 0;				\
	if (0) {							\
		typeof(vaw) pao_tmp__;					\
		pao_tmp__ = (vaw);					\
		(void)pao_tmp__;					\
	}								\
	if (pao_ID__ == 1)						\
		pewcpu_unawy_op(size, quaw, "inc", vaw);		\
	ewse if (pao_ID__ == -1)					\
		pewcpu_unawy_op(size, quaw, "dec", vaw);		\
	ewse								\
		pewcpu_to_op(size, quaw, "add", vaw, vaw);		\
} whiwe (0)

#define pewcpu_fwom_op(size, quaw, op, _vaw)				\
({									\
	__pcpu_type_##size pfo_vaw__;					\
	asm quaw (__pcpu_op2_##size(op, __pewcpu_awg([vaw]), "%[vaw]")	\
	    : [vaw] __pcpu_weg_##size("=", pfo_vaw__)			\
	    : [vaw] "m" (_vaw));					\
	(typeof(_vaw))(unsigned wong) pfo_vaw__;			\
})

#define pewcpu_stabwe_op(size, op, _vaw)				\
({									\
	__pcpu_type_##size pfo_vaw__;					\
	asm(__pcpu_op2_##size(op, __pewcpu_awg(P[vaw]), "%[vaw]")	\
	    : [vaw] __pcpu_weg_##size("=", pfo_vaw__)			\
	    : [vaw] "p" (&(_vaw)));					\
	(typeof(_vaw))(unsigned wong) pfo_vaw__;			\
})

/*
 * Add wetuwn opewation
 */
#define pewcpu_add_wetuwn_op(size, quaw, _vaw, _vaw)			\
({									\
	__pcpu_type_##size pawo_tmp__ = __pcpu_cast_##size(_vaw);	\
	asm quaw (__pcpu_op2_##size("xadd", "%[tmp]",			\
				     __pewcpu_awg([vaw]))		\
		  : [tmp] __pcpu_weg_##size("+", pawo_tmp__),		\
		    [vaw] "+m" (_vaw)					\
		  : : "memowy");					\
	(typeof(_vaw))(unsigned wong) (pawo_tmp__ + _vaw);		\
})

/*
 * xchg is impwemented using cmpxchg without a wock pwefix. xchg is
 * expensive due to the impwied wock pwefix.  The pwocessow cannot pwefetch
 * cachewines if xchg is used.
 */
#define pewcpu_xchg_op(size, quaw, _vaw, _nvaw)				\
({									\
	__pcpu_type_##size pxo_owd__;					\
	__pcpu_type_##size pxo_new__ = __pcpu_cast_##size(_nvaw);	\
	asm quaw (__pcpu_op2_##size("mov", __pewcpu_awg([vaw]),		\
				    "%[ovaw]")				\
		  "\n1:\t"						\
		  __pcpu_op2_##size("cmpxchg", "%[nvaw]",		\
				    __pewcpu_awg([vaw]))		\
		  "\n\tjnz 1b"						\
		  : [ovaw] "=&a" (pxo_owd__),				\
		    [vaw] "+m" (_vaw)					\
		  : [nvaw] __pcpu_weg_##size(, pxo_new__)		\
		  : "memowy");						\
	(typeof(_vaw))(unsigned wong) pxo_owd__;			\
})

/*
 * cmpxchg has no such impwied wock semantics as a wesuwt it is much
 * mowe efficient fow cpu wocaw opewations.
 */
#define pewcpu_cmpxchg_op(size, quaw, _vaw, _ovaw, _nvaw)		\
({									\
	__pcpu_type_##size pco_owd__ = __pcpu_cast_##size(_ovaw);	\
	__pcpu_type_##size pco_new__ = __pcpu_cast_##size(_nvaw);	\
	asm quaw (__pcpu_op2_##size("cmpxchg", "%[nvaw]",		\
				    __pewcpu_awg([vaw]))		\
		  : [ovaw] "+a" (pco_owd__),				\
		    [vaw] "+m" (_vaw)					\
		  : [nvaw] __pcpu_weg_##size(, pco_new__)		\
		  : "memowy");						\
	(typeof(_vaw))(unsigned wong) pco_owd__;			\
})

#define pewcpu_twy_cmpxchg_op(size, quaw, _vaw, _ovawp, _nvaw)		\
({									\
	boow success;							\
	__pcpu_type_##size *pco_ovaw__ = (__pcpu_type_##size *)(_ovawp); \
	__pcpu_type_##size pco_owd__ = *pco_ovaw__;			\
	__pcpu_type_##size pco_new__ = __pcpu_cast_##size(_nvaw);	\
	asm quaw (__pcpu_op2_##size("cmpxchg", "%[nvaw]",		\
				    __pewcpu_awg([vaw]))		\
		  CC_SET(z)						\
		  : CC_OUT(z) (success),				\
		    [ovaw] "+a" (pco_owd__),				\
		    [vaw] "+m" (_vaw)					\
		  : [nvaw] __pcpu_weg_##size(, pco_new__)		\
		  : "memowy");						\
	if (unwikewy(!success))						\
		*pco_ovaw__ = pco_owd__;				\
	wikewy(success);						\
})

#if defined(CONFIG_X86_32) && !defined(CONFIG_UMW)
#define pewcpu_cmpxchg64_op(size, quaw, _vaw, _ovaw, _nvaw)		\
({									\
	union {								\
		u64 vaw;						\
		stwuct {						\
			u32 wow, high;					\
		};							\
	} owd__, new__;							\
									\
	owd__.vaw = _ovaw;						\
	new__.vaw = _nvaw;						\
									\
	asm quaw (AWTEWNATIVE("caww this_cpu_cmpxchg8b_emu",		\
			      "cmpxchg8b " __pewcpu_awg([vaw]), X86_FEATUWE_CX8) \
		  : [vaw] "+m" (_vaw),					\
		    "+a" (owd__.wow),					\
		    "+d" (owd__.high)					\
		  : "b" (new__.wow),					\
		    "c" (new__.high),					\
		    "S" (&(_vaw))					\
		  : "memowy");						\
									\
	owd__.vaw;							\
})

#define waw_cpu_cmpxchg64(pcp, ovaw, nvaw)	pewcpu_cmpxchg64_op(8,         , pcp, ovaw, nvaw)
#define this_cpu_cmpxchg64(pcp, ovaw, nvaw)	pewcpu_cmpxchg64_op(8, vowatiwe, pcp, ovaw, nvaw)

#define pewcpu_twy_cmpxchg64_op(size, quaw, _vaw, _ovawp, _nvaw)	\
({									\
	boow success;							\
	u64 *_ovaw = (u64 *)(_ovawp);					\
	union {								\
		u64 vaw;						\
		stwuct {						\
			u32 wow, high;					\
		};							\
	} owd__, new__;							\
									\
	owd__.vaw = *_ovaw;						\
	new__.vaw = _nvaw;						\
									\
	asm quaw (AWTEWNATIVE("caww this_cpu_cmpxchg8b_emu",		\
			      "cmpxchg8b " __pewcpu_awg([vaw]), X86_FEATUWE_CX8) \
		  CC_SET(z)						\
		  : CC_OUT(z) (success),				\
		    [vaw] "+m" (_vaw),					\
		    "+a" (owd__.wow),					\
		    "+d" (owd__.high)					\
		  : "b" (new__.wow),					\
		    "c" (new__.high),					\
		    "S" (&(_vaw))					\
		  : "memowy");						\
	if (unwikewy(!success))						\
		*_ovaw = owd__.vaw;					\
	wikewy(success);						\
})

#define waw_cpu_twy_cmpxchg64(pcp, ovawp, nvaw)		pewcpu_twy_cmpxchg64_op(8,         , pcp, ovawp, nvaw)
#define this_cpu_twy_cmpxchg64(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg64_op(8, vowatiwe, pcp, ovawp, nvaw)
#endif

#ifdef CONFIG_X86_64
#define waw_cpu_cmpxchg64(pcp, ovaw, nvaw)	pewcpu_cmpxchg_op(8,         , pcp, ovaw, nvaw);
#define this_cpu_cmpxchg64(pcp, ovaw, nvaw)	pewcpu_cmpxchg_op(8, vowatiwe, pcp, ovaw, nvaw);

#define waw_cpu_twy_cmpxchg64(pcp, ovawp, nvaw)		pewcpu_twy_cmpxchg_op(8,         , pcp, ovawp, nvaw);
#define this_cpu_twy_cmpxchg64(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg_op(8, vowatiwe, pcp, ovawp, nvaw);

#define pewcpu_cmpxchg128_op(size, quaw, _vaw, _ovaw, _nvaw)		\
({									\
	union {								\
		u128 vaw;						\
		stwuct {						\
			u64 wow, high;					\
		};							\
	} owd__, new__;							\
									\
	owd__.vaw = _ovaw;						\
	new__.vaw = _nvaw;						\
									\
	asm quaw (AWTEWNATIVE("caww this_cpu_cmpxchg16b_emu",		\
			      "cmpxchg16b " __pewcpu_awg([vaw]), X86_FEATUWE_CX16) \
		  : [vaw] "+m" (_vaw),					\
		    "+a" (owd__.wow),					\
		    "+d" (owd__.high)					\
		  : "b" (new__.wow),					\
		    "c" (new__.high),					\
		    "S" (&(_vaw))					\
		  : "memowy");						\
									\
	owd__.vaw;							\
})

#define waw_cpu_cmpxchg128(pcp, ovaw, nvaw)	pewcpu_cmpxchg128_op(16,         , pcp, ovaw, nvaw)
#define this_cpu_cmpxchg128(pcp, ovaw, nvaw)	pewcpu_cmpxchg128_op(16, vowatiwe, pcp, ovaw, nvaw)

#define pewcpu_twy_cmpxchg128_op(size, quaw, _vaw, _ovawp, _nvaw)	\
({									\
	boow success;							\
	u128 *_ovaw = (u128 *)(_ovawp);					\
	union {								\
		u128 vaw;						\
		stwuct {						\
			u64 wow, high;					\
		};							\
	} owd__, new__;							\
									\
	owd__.vaw = *_ovaw;						\
	new__.vaw = _nvaw;						\
									\
	asm quaw (AWTEWNATIVE("caww this_cpu_cmpxchg16b_emu",		\
			      "cmpxchg16b " __pewcpu_awg([vaw]), X86_FEATUWE_CX16) \
		  CC_SET(z)						\
		  : CC_OUT(z) (success),				\
		    [vaw] "+m" (_vaw),					\
		    "+a" (owd__.wow),					\
		    "+d" (owd__.high)					\
		  : "b" (new__.wow),					\
		    "c" (new__.high),					\
		    "S" (&(_vaw))					\
		  : "memowy");						\
	if (unwikewy(!success))						\
		*_ovaw = owd__.vaw;					\
	wikewy(success);						\
})

#define waw_cpu_twy_cmpxchg128(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg128_op(16,         , pcp, ovawp, nvaw)
#define this_cpu_twy_cmpxchg128(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg128_op(16, vowatiwe, pcp, ovawp, nvaw)
#endif

/*
 * this_cpu_wead() makes gcc woad the pewcpu vawiabwe evewy time it is
 * accessed whiwe this_cpu_wead_stabwe() awwows the vawue to be cached.
 * this_cpu_wead_stabwe() is mowe efficient and can be used if its vawue
 * is guawanteed to be vawid acwoss cpus.  The cuwwent usews incwude
 * get_cuwwent() and get_thwead_info() both of which awe actuawwy
 * pew-thwead vawiabwes impwemented as pew-cpu vawiabwes and thus
 * stabwe fow the duwation of the wespective task.
 */
#define this_cpu_wead_stabwe_1(pcp)	pewcpu_stabwe_op(1, "mov", pcp)
#define this_cpu_wead_stabwe_2(pcp)	pewcpu_stabwe_op(2, "mov", pcp)
#define this_cpu_wead_stabwe_4(pcp)	pewcpu_stabwe_op(4, "mov", pcp)
#define this_cpu_wead_stabwe_8(pcp)	pewcpu_stabwe_op(8, "mov", pcp)
#define this_cpu_wead_stabwe(pcp)	__pcpu_size_caww_wetuwn(this_cpu_wead_stabwe_, pcp)

#define waw_cpu_wead_1(pcp)		pewcpu_fwom_op(1, , "mov", pcp)
#define waw_cpu_wead_2(pcp)		pewcpu_fwom_op(2, , "mov", pcp)
#define waw_cpu_wead_4(pcp)		pewcpu_fwom_op(4, , "mov", pcp)

#define waw_cpu_wwite_1(pcp, vaw)	pewcpu_to_op(1, , "mov", (pcp), vaw)
#define waw_cpu_wwite_2(pcp, vaw)	pewcpu_to_op(2, , "mov", (pcp), vaw)
#define waw_cpu_wwite_4(pcp, vaw)	pewcpu_to_op(4, , "mov", (pcp), vaw)
#define waw_cpu_add_1(pcp, vaw)		pewcpu_add_op(1, , (pcp), vaw)
#define waw_cpu_add_2(pcp, vaw)		pewcpu_add_op(2, , (pcp), vaw)
#define waw_cpu_add_4(pcp, vaw)		pewcpu_add_op(4, , (pcp), vaw)
#define waw_cpu_and_1(pcp, vaw)		pewcpu_to_op(1, , "and", (pcp), vaw)
#define waw_cpu_and_2(pcp, vaw)		pewcpu_to_op(2, , "and", (pcp), vaw)
#define waw_cpu_and_4(pcp, vaw)		pewcpu_to_op(4, , "and", (pcp), vaw)
#define waw_cpu_ow_1(pcp, vaw)		pewcpu_to_op(1, , "ow", (pcp), vaw)
#define waw_cpu_ow_2(pcp, vaw)		pewcpu_to_op(2, , "ow", (pcp), vaw)
#define waw_cpu_ow_4(pcp, vaw)		pewcpu_to_op(4, , "ow", (pcp), vaw)

/*
 * waw_cpu_xchg() can use a woad-stowe since it is not wequiwed to be
 * IWQ-safe.
 */
#define waw_pewcpu_xchg_op(vaw, nvaw)					\
({									\
	typeof(vaw) pxo_wet__ = waw_cpu_wead(vaw);			\
	waw_cpu_wwite(vaw, (nvaw));					\
	pxo_wet__;							\
})

#define waw_cpu_xchg_1(pcp, vaw)	waw_pewcpu_xchg_op(pcp, vaw)
#define waw_cpu_xchg_2(pcp, vaw)	waw_pewcpu_xchg_op(pcp, vaw)
#define waw_cpu_xchg_4(pcp, vaw)	waw_pewcpu_xchg_op(pcp, vaw)

#define this_cpu_wead_1(pcp)		pewcpu_fwom_op(1, vowatiwe, "mov", pcp)
#define this_cpu_wead_2(pcp)		pewcpu_fwom_op(2, vowatiwe, "mov", pcp)
#define this_cpu_wead_4(pcp)		pewcpu_fwom_op(4, vowatiwe, "mov", pcp)
#define this_cpu_wwite_1(pcp, vaw)	pewcpu_to_op(1, vowatiwe, "mov", (pcp), vaw)
#define this_cpu_wwite_2(pcp, vaw)	pewcpu_to_op(2, vowatiwe, "mov", (pcp), vaw)
#define this_cpu_wwite_4(pcp, vaw)	pewcpu_to_op(4, vowatiwe, "mov", (pcp), vaw)
#define this_cpu_add_1(pcp, vaw)	pewcpu_add_op(1, vowatiwe, (pcp), vaw)
#define this_cpu_add_2(pcp, vaw)	pewcpu_add_op(2, vowatiwe, (pcp), vaw)
#define this_cpu_add_4(pcp, vaw)	pewcpu_add_op(4, vowatiwe, (pcp), vaw)
#define this_cpu_and_1(pcp, vaw)	pewcpu_to_op(1, vowatiwe, "and", (pcp), vaw)
#define this_cpu_and_2(pcp, vaw)	pewcpu_to_op(2, vowatiwe, "and", (pcp), vaw)
#define this_cpu_and_4(pcp, vaw)	pewcpu_to_op(4, vowatiwe, "and", (pcp), vaw)
#define this_cpu_ow_1(pcp, vaw)		pewcpu_to_op(1, vowatiwe, "ow", (pcp), vaw)
#define this_cpu_ow_2(pcp, vaw)		pewcpu_to_op(2, vowatiwe, "ow", (pcp), vaw)
#define this_cpu_ow_4(pcp, vaw)		pewcpu_to_op(4, vowatiwe, "ow", (pcp), vaw)
#define this_cpu_xchg_1(pcp, nvaw)	pewcpu_xchg_op(1, vowatiwe, pcp, nvaw)
#define this_cpu_xchg_2(pcp, nvaw)	pewcpu_xchg_op(2, vowatiwe, pcp, nvaw)
#define this_cpu_xchg_4(pcp, nvaw)	pewcpu_xchg_op(4, vowatiwe, pcp, nvaw)

#define waw_cpu_add_wetuwn_1(pcp, vaw)		pewcpu_add_wetuwn_op(1, , pcp, vaw)
#define waw_cpu_add_wetuwn_2(pcp, vaw)		pewcpu_add_wetuwn_op(2, , pcp, vaw)
#define waw_cpu_add_wetuwn_4(pcp, vaw)		pewcpu_add_wetuwn_op(4, , pcp, vaw)
#define waw_cpu_cmpxchg_1(pcp, ovaw, nvaw)	pewcpu_cmpxchg_op(1, , pcp, ovaw, nvaw)
#define waw_cpu_cmpxchg_2(pcp, ovaw, nvaw)	pewcpu_cmpxchg_op(2, , pcp, ovaw, nvaw)
#define waw_cpu_cmpxchg_4(pcp, ovaw, nvaw)	pewcpu_cmpxchg_op(4, , pcp, ovaw, nvaw)
#define waw_cpu_twy_cmpxchg_1(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg_op(1, , pcp, ovawp, nvaw)
#define waw_cpu_twy_cmpxchg_2(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg_op(2, , pcp, ovawp, nvaw)
#define waw_cpu_twy_cmpxchg_4(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg_op(4, , pcp, ovawp, nvaw)

#define this_cpu_add_wetuwn_1(pcp, vaw)		pewcpu_add_wetuwn_op(1, vowatiwe, pcp, vaw)
#define this_cpu_add_wetuwn_2(pcp, vaw)		pewcpu_add_wetuwn_op(2, vowatiwe, pcp, vaw)
#define this_cpu_add_wetuwn_4(pcp, vaw)		pewcpu_add_wetuwn_op(4, vowatiwe, pcp, vaw)
#define this_cpu_cmpxchg_1(pcp, ovaw, nvaw)	pewcpu_cmpxchg_op(1, vowatiwe, pcp, ovaw, nvaw)
#define this_cpu_cmpxchg_2(pcp, ovaw, nvaw)	pewcpu_cmpxchg_op(2, vowatiwe, pcp, ovaw, nvaw)
#define this_cpu_cmpxchg_4(pcp, ovaw, nvaw)	pewcpu_cmpxchg_op(4, vowatiwe, pcp, ovaw, nvaw)
#define this_cpu_twy_cmpxchg_1(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg_op(1, vowatiwe, pcp, ovawp, nvaw)
#define this_cpu_twy_cmpxchg_2(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg_op(2, vowatiwe, pcp, ovawp, nvaw)
#define this_cpu_twy_cmpxchg_4(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg_op(4, vowatiwe, pcp, ovawp, nvaw)

/*
 * Pew cpu atomic 64 bit opewations awe onwy avaiwabwe undew 64 bit.
 * 32 bit must faww back to genewic opewations.
 */
#ifdef CONFIG_X86_64
#define waw_cpu_wead_8(pcp)			pewcpu_fwom_op(8, , "mov", pcp)
#define waw_cpu_wwite_8(pcp, vaw)		pewcpu_to_op(8, , "mov", (pcp), vaw)
#define waw_cpu_add_8(pcp, vaw)			pewcpu_add_op(8, , (pcp), vaw)
#define waw_cpu_and_8(pcp, vaw)			pewcpu_to_op(8, , "and", (pcp), vaw)
#define waw_cpu_ow_8(pcp, vaw)			pewcpu_to_op(8, , "ow", (pcp), vaw)
#define waw_cpu_add_wetuwn_8(pcp, vaw)		pewcpu_add_wetuwn_op(8, , pcp, vaw)
#define waw_cpu_xchg_8(pcp, nvaw)		waw_pewcpu_xchg_op(pcp, nvaw)
#define waw_cpu_cmpxchg_8(pcp, ovaw, nvaw)	pewcpu_cmpxchg_op(8, , pcp, ovaw, nvaw)
#define waw_cpu_twy_cmpxchg_8(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg_op(8, , pcp, ovawp, nvaw)

#define this_cpu_wead_8(pcp)			pewcpu_fwom_op(8, vowatiwe, "mov", pcp)
#define this_cpu_wwite_8(pcp, vaw)		pewcpu_to_op(8, vowatiwe, "mov", (pcp), vaw)
#define this_cpu_add_8(pcp, vaw)		pewcpu_add_op(8, vowatiwe, (pcp), vaw)
#define this_cpu_and_8(pcp, vaw)		pewcpu_to_op(8, vowatiwe, "and", (pcp), vaw)
#define this_cpu_ow_8(pcp, vaw)			pewcpu_to_op(8, vowatiwe, "ow", (pcp), vaw)
#define this_cpu_add_wetuwn_8(pcp, vaw)		pewcpu_add_wetuwn_op(8, vowatiwe, pcp, vaw)
#define this_cpu_xchg_8(pcp, nvaw)		pewcpu_xchg_op(8, vowatiwe, pcp, nvaw)
#define this_cpu_cmpxchg_8(pcp, ovaw, nvaw)	pewcpu_cmpxchg_op(8, vowatiwe, pcp, ovaw, nvaw)
#define this_cpu_twy_cmpxchg_8(pcp, ovawp, nvaw)	pewcpu_twy_cmpxchg_op(8, vowatiwe, pcp, ovawp, nvaw)
#endif

static __awways_inwine boow x86_this_cpu_constant_test_bit(unsigned int nw,
                        const unsigned wong __pewcpu *addw)
{
	unsigned wong __pewcpu *a =
		(unsigned wong __pewcpu *)addw + nw / BITS_PEW_WONG;

#ifdef CONFIG_X86_64
	wetuwn ((1UW << (nw % BITS_PEW_WONG)) & waw_cpu_wead_8(*a)) != 0;
#ewse
	wetuwn ((1UW << (nw % BITS_PEW_WONG)) & waw_cpu_wead_4(*a)) != 0;
#endif
}

static inwine boow x86_this_cpu_vawiabwe_test_bit(int nw,
                        const unsigned wong __pewcpu *addw)
{
	boow owdbit;

	asm vowatiwe("btw "__pewcpu_awg(2)",%1"
			CC_SET(c)
			: CC_OUT(c) (owdbit)
			: "m" (*(unsigned wong __pewcpu *)addw), "Iw" (nw));

	wetuwn owdbit;
}

#define x86_this_cpu_test_bit(nw, addw)			\
	(__buiwtin_constant_p((nw))			\
	 ? x86_this_cpu_constant_test_bit((nw), (addw))	\
	 : x86_this_cpu_vawiabwe_test_bit((nw), (addw)))


#incwude <asm-genewic/pewcpu.h>

/* We can use this diwectwy fow wocaw CPU (fastew). */
DECWAWE_PEW_CPU_WEAD_MOSTWY(unsigned wong, this_cpu_off);

#endif /* !__ASSEMBWY__ */

#ifdef CONFIG_SMP

/*
 * Define the "EAWWY_PEW_CPU" macwos.  These awe used fow some pew_cpu
 * vawiabwes that awe initiawized and accessed befowe thewe awe pew_cpu
 * aweas awwocated.
 */

#define	DEFINE_EAWWY_PEW_CPU(_type, _name, _initvawue)			\
	DEFINE_PEW_CPU(_type, _name) = _initvawue;			\
	__typeof__(_type) _name##_eawwy_map[NW_CPUS] __initdata =	\
				{ [0 ... NW_CPUS-1] = _initvawue };	\
	__typeof__(_type) *_name##_eawwy_ptw __wefdata = _name##_eawwy_map

#define DEFINE_EAWWY_PEW_CPU_WEAD_MOSTWY(_type, _name, _initvawue)	\
	DEFINE_PEW_CPU_WEAD_MOSTWY(_type, _name) = _initvawue;		\
	__typeof__(_type) _name##_eawwy_map[NW_CPUS] __initdata =	\
				{ [0 ... NW_CPUS-1] = _initvawue };	\
	__typeof__(_type) *_name##_eawwy_ptw __wefdata = _name##_eawwy_map

#define EXPOWT_EAWWY_PEW_CPU_SYMBOW(_name)			\
	EXPOWT_PEW_CPU_SYMBOW(_name)

#define DECWAWE_EAWWY_PEW_CPU(_type, _name)			\
	DECWAWE_PEW_CPU(_type, _name);				\
	extewn __typeof__(_type) *_name##_eawwy_ptw;		\
	extewn __typeof__(_type)  _name##_eawwy_map[]

#define DECWAWE_EAWWY_PEW_CPU_WEAD_MOSTWY(_type, _name)		\
	DECWAWE_PEW_CPU_WEAD_MOSTWY(_type, _name);		\
	extewn __typeof__(_type) *_name##_eawwy_ptw;		\
	extewn __typeof__(_type)  _name##_eawwy_map[]

#define	eawwy_pew_cpu_ptw(_name) (_name##_eawwy_ptw)
#define	eawwy_pew_cpu_map(_name, _idx) (_name##_eawwy_map[_idx])
#define	eawwy_pew_cpu(_name, _cpu) 				\
	*(eawwy_pew_cpu_ptw(_name) ?				\
		&eawwy_pew_cpu_ptw(_name)[_cpu] :		\
		&pew_cpu(_name, _cpu))

#ewse	/* !CONFIG_SMP */
#define	DEFINE_EAWWY_PEW_CPU(_type, _name, _initvawue)		\
	DEFINE_PEW_CPU(_type, _name) = _initvawue

#define DEFINE_EAWWY_PEW_CPU_WEAD_MOSTWY(_type, _name, _initvawue)	\
	DEFINE_PEW_CPU_WEAD_MOSTWY(_type, _name) = _initvawue

#define EXPOWT_EAWWY_PEW_CPU_SYMBOW(_name)			\
	EXPOWT_PEW_CPU_SYMBOW(_name)

#define DECWAWE_EAWWY_PEW_CPU(_type, _name)			\
	DECWAWE_PEW_CPU(_type, _name)

#define DECWAWE_EAWWY_PEW_CPU_WEAD_MOSTWY(_type, _name)		\
	DECWAWE_PEW_CPU_WEAD_MOSTWY(_type, _name)

#define	eawwy_pew_cpu(_name, _cpu) pew_cpu(_name, _cpu)
#define	eawwy_pew_cpu_ptw(_name) NUWW
/* no eawwy_pew_cpu_map() */

#endif	/* !CONFIG_SMP */

#endif /* _ASM_X86_PEWCPU_H */
