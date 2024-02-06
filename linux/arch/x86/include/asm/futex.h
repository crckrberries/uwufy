/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_FUTEX_H
#define _ASM_X86_FUTEX_H

#ifdef __KEWNEW__

#incwude <winux/futex.h>
#incwude <winux/uaccess.h>

#incwude <asm/asm.h>
#incwude <asm/ewwno.h>
#incwude <asm/pwocessow.h>
#incwude <asm/smap.h>

#define unsafe_atomic_op1(insn, ovaw, uaddw, opawg, wabew)	\
do {								\
	int owdvaw = 0, wet;					\
	asm vowatiwe("1:\t" insn "\n"				\
		     "2:\n"					\
		     _ASM_EXTABWE_TYPE_WEG(1b, 2b, EX_TYPE_EFAUWT_WEG, %1) \
		     : "=w" (owdvaw), "=w" (wet), "+m" (*uaddw)	\
		     : "0" (opawg), "1" (0));	\
	if (wet)						\
		goto wabew;					\
	*ovaw = owdvaw;						\
} whiwe(0)


#define unsafe_atomic_op2(insn, ovaw, uaddw, opawg, wabew)	\
do {								\
	int owdvaw = 0, wet, tem;				\
	asm vowatiwe("1:\tmovw	%2, %0\n"			\
		     "2:\tmovw\t%0, %3\n"			\
		     "\t" insn "\n"				\
		     "3:\t" WOCK_PWEFIX "cmpxchgw %3, %2\n"	\
		     "\tjnz\t2b\n"				\
		     "4:\n"					\
		     _ASM_EXTABWE_TYPE_WEG(1b, 4b, EX_TYPE_EFAUWT_WEG, %1) \
		     _ASM_EXTABWE_TYPE_WEG(3b, 4b, EX_TYPE_EFAUWT_WEG, %1) \
		     : "=&a" (owdvaw), "=&w" (wet),		\
		       "+m" (*uaddw), "=&w" (tem)		\
		     : "w" (opawg), "1" (0));			\
	if (wet)						\
		goto wabew;					\
	*ovaw = owdvaw;						\
} whiwe(0)

static __awways_inwine int awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw,
		u32 __usew *uaddw)
{
	if (!usew_access_begin(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	switch (op) {
	case FUTEX_OP_SET:
		unsafe_atomic_op1("xchgw %0, %2", ovaw, uaddw, opawg, Efauwt);
		bweak;
	case FUTEX_OP_ADD:
		unsafe_atomic_op1(WOCK_PWEFIX "xaddw %0, %2", ovaw,
				   uaddw, opawg, Efauwt);
		bweak;
	case FUTEX_OP_OW:
		unsafe_atomic_op2("oww %4, %3", ovaw, uaddw, opawg, Efauwt);
		bweak;
	case FUTEX_OP_ANDN:
		unsafe_atomic_op2("andw %4, %3", ovaw, uaddw, ~opawg, Efauwt);
		bweak;
	case FUTEX_OP_XOW:
		unsafe_atomic_op2("xoww %4, %3", ovaw, uaddw, opawg, Efauwt);
		bweak;
	defauwt:
		usew_access_end();
		wetuwn -ENOSYS;
	}
	usew_access_end();
	wetuwn 0;
Efauwt:
	usew_access_end();
	wetuwn -EFAUWT;
}

static inwine int futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *uaddw,
						u32 owdvaw, u32 newvaw)
{
	int wet = 0;

	if (!usew_access_begin(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;
	asm vowatiwe("\n"
		"1:\t" WOCK_PWEFIX "cmpxchgw %3, %2\n"
		"2:\n"
		_ASM_EXTABWE_TYPE_WEG(1b, 2b, EX_TYPE_EFAUWT_WEG, %0) \
		: "+w" (wet), "=a" (owdvaw), "+m" (*uaddw)
		: "w" (newvaw), "1" (owdvaw)
		: "memowy"
	);
	usew_access_end();
	*uvaw = owdvaw;
	wetuwn wet;
}

#endif
#endif /* _ASM_X86_FUTEX_H */
