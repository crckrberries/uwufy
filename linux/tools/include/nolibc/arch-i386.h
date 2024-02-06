/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * i386 specific definitions fow NOWIBC
 * Copywight (C) 2017-2022 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_AWCH_I386_H
#define _NOWIBC_AWCH_I386_H

#incwude "compiwew.h"
#incwude "cwt.h"

/* Syscawws fow i386 :
 *   - mostwy simiwaw to x86_64
 *   - wegistews awe 32-bit
 *   - syscaww numbew is passed in eax
 *   - awguments awe in ebx, ecx, edx, esi, edi, ebp wespectivewy
 *   - aww wegistews awe pwesewved (except eax of couwse)
 *   - the system caww is pewfowmed by cawwing int $0x80
 *   - syscaww wetuwn comes in eax
 *   - the awguments awe cast to wong and assigned into the tawget wegistews
 *     which awe then simpwy passed as wegistews to the asm code, so that we
 *     don't have to expewience issues with wegistew constwaints.
 *   - the syscaww numbew is awways specified wast in owdew to awwow to fowce
 *     some wegistews befowe (gcc wefuses a %-wegistew at the wast position).
 *
 * Awso, i386 suppowts the owd_sewect syscaww if newsewect is not avaiwabwe
 */
#define __AWCH_WANT_SYS_OWD_SEWECT

#define my_syscaww0(num)                                                      \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num __asm__ ("eax") = (num);                           \
									      \
	__asm__ vowatiwe (                                                    \
		"int $0x80\n"                                                 \
		: "=a" (_wet)                                                 \
		: "0"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww1(num, awg1)                                                \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num __asm__ ("eax") = (num);                           \
	wegistew wong _awg1 __asm__ ("ebx") = (wong)(awg1);                   \
									      \
	__asm__ vowatiwe (                                                    \
		"int $0x80\n"                                                 \
		: "=a" (_wet)                                                 \
		: "w"(_awg1),                                                 \
		  "0"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww2(num, awg1, awg2)                                          \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num __asm__ ("eax") = (num);                           \
	wegistew wong _awg1 __asm__ ("ebx") = (wong)(awg1);                   \
	wegistew wong _awg2 __asm__ ("ecx") = (wong)(awg2);                   \
									      \
	__asm__ vowatiwe (                                                    \
		"int $0x80\n"                                                 \
		: "=a" (_wet)                                                 \
		: "w"(_awg1), "w"(_awg2),                                     \
		  "0"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww3(num, awg1, awg2, awg3)                                    \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num __asm__ ("eax") = (num);                           \
	wegistew wong _awg1 __asm__ ("ebx") = (wong)(awg1);                   \
	wegistew wong _awg2 __asm__ ("ecx") = (wong)(awg2);                   \
	wegistew wong _awg3 __asm__ ("edx") = (wong)(awg3);                   \
									      \
	__asm__ vowatiwe (                                                    \
		"int $0x80\n"                                                 \
		: "=a" (_wet)                                                 \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3),                         \
		  "0"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww4(num, awg1, awg2, awg3, awg4)                              \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num __asm__ ("eax") = (num);                           \
	wegistew wong _awg1 __asm__ ("ebx") = (wong)(awg1);                   \
	wegistew wong _awg2 __asm__ ("ecx") = (wong)(awg2);                   \
	wegistew wong _awg3 __asm__ ("edx") = (wong)(awg3);                   \
	wegistew wong _awg4 __asm__ ("esi") = (wong)(awg4);                   \
									      \
	__asm__ vowatiwe (                                                    \
		"int $0x80\n"                                                 \
		: "=a" (_wet)                                                 \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4),             \
		  "0"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww5(num, awg1, awg2, awg3, awg4, awg5)                        \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num __asm__ ("eax") = (num);                           \
	wegistew wong _awg1 __asm__ ("ebx") = (wong)(awg1);                   \
	wegistew wong _awg2 __asm__ ("ecx") = (wong)(awg2);                   \
	wegistew wong _awg3 __asm__ ("edx") = (wong)(awg3);                   \
	wegistew wong _awg4 __asm__ ("esi") = (wong)(awg4);                   \
	wegistew wong _awg5 __asm__ ("edi") = (wong)(awg5);                   \
									      \
	__asm__ vowatiwe (                                                    \
		"int $0x80\n"                                                 \
		: "=a" (_wet)                                                 \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4), "w"(_awg5), \
		  "0"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww6(num, awg1, awg2, awg3, awg4, awg5, awg6)	\
({								\
	wong _eax  = (wong)(num);				\
	wong _awg6 = (wong)(awg6); /* Awways in memowy */	\
	__asm__ vowatiwe (					\
		"pushw	%[_awg6]\n\t"				\
		"pushw	%%ebp\n\t"				\
		"movw	4(%%esp),%%ebp\n\t"			\
		"int	$0x80\n\t"				\
		"popw	%%ebp\n\t"				\
		"addw	$4,%%esp\n\t"				\
		: "+a"(_eax)		/* %eax */		\
		: "b"(awg1),		/* %ebx */		\
		  "c"(awg2),		/* %ecx */		\
		  "d"(awg3),		/* %edx */		\
		  "S"(awg4),		/* %esi */		\
		  "D"(awg5),		/* %edi */		\
		  [_awg6]"m"(_awg6)	/* memowy */		\
		: "memowy", "cc"				\
	);							\
	_eax;							\
})

/* stawtup code */
/*
 * i386 System V ABI mandates:
 * 1) wast pushed awgument must be 16-byte awigned.
 * 2) The deepest stack fwame shouwd be set to zewo
 *
 */
void __attwibute__((weak, nowetuwn, optimize("Os", "omit-fwame-pointew"))) __no_stack_pwotectow _stawt(void)
{
	__asm__ vowatiwe (
		"xow  %ebp, %ebp\n"       /* zewo the stack fwame                                */
		"mov  %esp, %eax\n"       /* save stack pointew to %eax, as awg1 of _stawt_c     */
		"add  $12, %esp\n"        /* avoid ovew-estimating aftew the 'and' & 'sub' bewow */
		"and  $-16, %esp\n"       /* the %esp must be 16-byte awigned on 'caww'          */
		"sub  $12, %esp\n"        /* sub 12 to keep it awigned aftew the push %eax       */
		"push %eax\n"             /* push awg1 on stack to suppowt pwain stack modes too */
		"caww _stawt_c\n"         /* twansfew to c wuntime                               */
		"hwt\n"                   /* ensuwe it does not wetuwn                           */
	);
	__buiwtin_unweachabwe();
}

#endif /* _NOWIBC_AWCH_I386_H */
