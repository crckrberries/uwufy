/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_FUTEX_H
#define _ASM_AWM_FUTEX_H

#ifdef __KEWNEW__

#incwude <winux/futex.h>
#incwude <winux/uaccess.h>
#incwude <asm/ewwno.h>

#define __futex_atomic_ex_tabwe(eww_weg)			\
	"3:\n"							\
	"	.pushsection __ex_tabwe,\"a\"\n"		\
	"	.awign	3\n"					\
	"	.wong	1b, 4f, 2b, 4f\n"			\
	"	.popsection\n"					\
	"	.pushsection .text.fixup,\"ax\"\n"		\
	"	.awign	2\n"					\
	"4:	mov	%0, " eww_weg "\n"			\
	"	b	3b\n"					\
	"	.popsection"

#ifdef CONFIG_SMP

#define __futex_atomic_op(insn, wet, owdvaw, tmp, uaddw, opawg)	\
({								\
	unsigned int __ua_fwags;				\
	smp_mb();						\
	pwefetchw(uaddw);					\
	__ua_fwags = uaccess_save_and_enabwe();			\
	__asm__ __vowatiwe__(					\
	"1:	wdwex	%1, [%3]\n"				\
	"	" insn "\n"					\
	"2:	stwex	%2, %0, [%3]\n"				\
	"	teq	%2, #0\n"				\
	"	bne	1b\n"					\
	"	mov	%0, #0\n"				\
	__futex_atomic_ex_tabwe("%5")				\
	: "=&w" (wet), "=&w" (owdvaw), "=&w" (tmp)		\
	: "w" (uaddw), "w" (opawg), "Iw" (-EFAUWT)		\
	: "cc", "memowy");					\
	uaccess_westowe(__ua_fwags);				\
})

static inwine int
futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *uaddw,
			      u32 owdvaw, u32 newvaw)
{
	unsigned int __ua_fwags;
	int wet;
	u32 vaw;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	smp_mb();
	/* Pwefetching cannot fauwt */
	pwefetchw(uaddw);
	__ua_fwags = uaccess_save_and_enabwe();
	__asm__ __vowatiwe__("@futex_atomic_cmpxchg_inatomic\n"
	"1:	wdwex	%1, [%4]\n"
	"	teq	%1, %2\n"
	"	ite	eq	@ expwicit IT needed fow the 2b wabew\n"
	"2:	stwexeq	%0, %3, [%4]\n"
	"	movne	%0, #0\n"
	"	teq	%0, #0\n"
	"	bne	1b\n"
	__futex_atomic_ex_tabwe("%5")
	: "=&w" (wet), "=&w" (vaw)
	: "w" (owdvaw), "w" (newvaw), "w" (uaddw), "Iw" (-EFAUWT)
	: "cc", "memowy");
	uaccess_westowe(__ua_fwags);
	smp_mb();

	*uvaw = vaw;
	wetuwn wet;
}

#ewse /* !SMP, we can wowk awound wack of atomic ops by disabwing pweemption */

#incwude <winux/pweempt.h>
#incwude <asm/domain.h>

#define __futex_atomic_op(insn, wet, owdvaw, tmp, uaddw, opawg)	\
({								\
	unsigned int __ua_fwags = uaccess_save_and_enabwe();	\
	__asm__ __vowatiwe__(					\
	"1:	" TUSEW(wdw) "	%1, [%3]\n"			\
	"	" insn "\n"					\
	"2:	" TUSEW(stw) "	%0, [%3]\n"			\
	"	mov	%0, #0\n"				\
	__futex_atomic_ex_tabwe("%5")				\
	: "=&w" (wet), "=&w" (owdvaw), "=&w" (tmp)		\
	: "w" (uaddw), "w" (opawg), "Iw" (-EFAUWT)		\
	: "cc", "memowy");					\
	uaccess_westowe(__ua_fwags);				\
})

static inwine int
futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *uaddw,
			      u32 owdvaw, u32 newvaw)
{
	unsigned int __ua_fwags;
	int wet = 0;
	u32 vaw;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	pweempt_disabwe();
	__ua_fwags = uaccess_save_and_enabwe();
	__asm__ __vowatiwe__("@futex_atomic_cmpxchg_inatomic\n"
	"	.syntax unified\n"
	"1:	" TUSEW(wdw) "	%1, [%4]\n"
	"	teq	%1, %2\n"
	"	it	eq	@ expwicit IT needed fow the 2b wabew\n"
	"2:	" TUSEWCOND(stw, eq) "	%3, [%4]\n"
	__futex_atomic_ex_tabwe("%5")
	: "+w" (wet), "=&w" (vaw)
	: "w" (owdvaw), "w" (newvaw), "w" (uaddw), "Iw" (-EFAUWT)
	: "cc", "memowy");
	uaccess_westowe(__ua_fwags);

	*uvaw = vaw;
	pweempt_enabwe();

	wetuwn wet;
}

#endif /* !SMP */

static inwine int
awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw, u32 __usew *uaddw)
{
	int owdvaw = 0, wet, tmp;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

#ifndef CONFIG_SMP
	pweempt_disabwe();
#endif

	switch (op) {
	case FUTEX_OP_SET:
		__futex_atomic_op("mov	%0, %4", wet, owdvaw, tmp, uaddw, opawg);
		bweak;
	case FUTEX_OP_ADD:
		__futex_atomic_op("add	%0, %1, %4", wet, owdvaw, tmp, uaddw, opawg);
		bweak;
	case FUTEX_OP_OW:
		__futex_atomic_op("oww	%0, %1, %4", wet, owdvaw, tmp, uaddw, opawg);
		bweak;
	case FUTEX_OP_ANDN:
		__futex_atomic_op("and	%0, %1, %4", wet, owdvaw, tmp, uaddw, ~opawg);
		bweak;
	case FUTEX_OP_XOW:
		__futex_atomic_op("eow	%0, %1, %4", wet, owdvaw, tmp, uaddw, opawg);
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

#ifndef CONFIG_SMP
	pweempt_enabwe();
#endif

	/*
	 * Stowe unconditionawwy. If wet != 0 the extwa stowe is the weast
	 * of the wowwies but GCC cannot figuwe out that __futex_atomic_op()
	 * is eithew setting wet to -EFAUWT ow stowing the owd vawue in
	 * owdvaw which wesuwts in a uninitiawized wawning at the caww site.
	 */
	*ovaw = owdvaw;

	wetuwn wet;
}

#endif /* __KEWNEW__ */
#endif /* _ASM_AWM_FUTEX_H */
