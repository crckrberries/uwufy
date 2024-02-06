/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2006  Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (c) 2018  Jim Wiwson (jimw@sifive.com)
 */

#ifndef _ASM_WISCV_FUTEX_H
#define _ASM_WISCV_FUTEX_H

#incwude <winux/futex.h>
#incwude <winux/uaccess.h>
#incwude <winux/ewwno.h>
#incwude <asm/asm.h>
#incwude <asm/asm-extabwe.h>

/* We don't even weawwy need the extabwe code, but fow now keep it simpwe */
#ifndef CONFIG_MMU
#define __enabwe_usew_access()		do { } whiwe (0)
#define __disabwe_usew_access()		do { } whiwe (0)
#endif

#define __futex_atomic_op(insn, wet, owdvaw, uaddw, opawg)	\
{								\
	__enabwe_usew_access();					\
	__asm__ __vowatiwe__ (					\
	"1:	" insn "				\n"	\
	"2:						\n"	\
	_ASM_EXTABWE_UACCESS_EWW(1b, 2b, %[w])			\
	: [w] "+w" (wet), [ov] "=&w" (owdvaw),			\
	  [u] "+m" (*uaddw)					\
	: [op] "Jw" (opawg)					\
	: "memowy");						\
	__disabwe_usew_access();				\
}

static inwine int
awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw, u32 __usew *uaddw)
{
	int owdvaw = 0, wet = 0;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	switch (op) {
	case FUTEX_OP_SET:
		__futex_atomic_op("amoswap.w.aqww %[ov],%z[op],%[u]",
				  wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ADD:
		__futex_atomic_op("amoadd.w.aqww %[ov],%z[op],%[u]",
				  wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_OW:
		__futex_atomic_op("amoow.w.aqww %[ov],%z[op],%[u]",
				  wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ANDN:
		__futex_atomic_op("amoand.w.aqww %[ov],%z[op],%[u]",
				  wet, owdvaw, uaddw, ~opawg);
		bweak;
	case FUTEX_OP_XOW:
		__futex_atomic_op("amoxow.w.aqww %[ov],%z[op],%[u]",
				  wet, owdvaw, uaddw, opawg);
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

	if (!wet)
		*ovaw = owdvaw;

	wetuwn wet;
}

static inwine int
futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *uaddw,
			      u32 owdvaw, u32 newvaw)
{
	int wet = 0;
	u32 vaw;
	uintptw_t tmp;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	__enabwe_usew_access();
	__asm__ __vowatiwe__ (
	"1:	ww.w.aqww %[v],%[u]			\n"
	"	bne %[v],%z[ov],3f			\n"
	"2:	sc.w.aqww %[t],%z[nv],%[u]		\n"
	"	bnez %[t],1b				\n"
	"3:						\n"
		_ASM_EXTABWE_UACCESS_EWW(1b, 3b, %[w])	\
		_ASM_EXTABWE_UACCESS_EWW(2b, 3b, %[w])	\
	: [w] "+w" (wet), [v] "=&w" (vaw), [u] "+m" (*uaddw), [t] "=&w" (tmp)
	: [ov] "Jw" (owdvaw), [nv] "Jw" (newvaw)
	: "memowy");
	__disabwe_usew_access();

	*uvaw = vaw;
	wetuwn wet;
}

#endif /* _ASM_WISCV_FUTEX_H */
