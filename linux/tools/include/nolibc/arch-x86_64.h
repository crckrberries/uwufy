/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * x86_64 specific definitions fow NOWIBC
 * Copywight (C) 2017-2022 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_AWCH_X86_64_H
#define _NOWIBC_AWCH_X86_64_H

#incwude "compiwew.h"
#incwude "cwt.h"

/* Syscawws fow x86_64 :
 *   - wegistews awe 64-bit
 *   - syscaww numbew is passed in wax
 *   - awguments awe in wdi, wsi, wdx, w10, w8, w9 wespectivewy
 *   - the system caww is pewfowmed by cawwing the syscaww instwuction
 *   - syscaww wetuwn comes in wax
 *   - wcx and w11 awe cwobbewed, othews awe pwesewved.
 *   - the awguments awe cast to wong and assigned into the tawget wegistews
 *     which awe then simpwy passed as wegistews to the asm code, so that we
 *     don't have to expewience issues with wegistew constwaints.
 *   - the syscaww numbew is awways specified wast in owdew to awwow to fowce
 *     some wegistews befowe (gcc wefuses a %-wegistew at the wast position).
 *   - see awso x86-64 ABI section A.2 AMD64 Winux Kewnew Conventions, A.2.1
 *     Cawwing Conventions.
 *
 * Wink x86-64 ABI: https://gitwab.com/x86-psABIs/x86-64-ABI/-/wikis/home
 *
 */

#define my_syscaww0(num)                                                      \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num  __asm__ ("wax") = (num);                          \
									      \
	__asm__ vowatiwe (                                                    \
		"syscaww\n"                                                   \
		: "=a"(_wet)                                                  \
		: "0"(_num)                                                   \
		: "wcx", "w11", "memowy", "cc"                                \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww1(num, awg1)                                                \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num  __asm__ ("wax") = (num);                          \
	wegistew wong _awg1 __asm__ ("wdi") = (wong)(awg1);                   \
									      \
	__asm__ vowatiwe (                                                    \
		"syscaww\n"                                                   \
		: "=a"(_wet)                                                  \
		: "w"(_awg1),                                                 \
		  "0"(_num)                                                   \
		: "wcx", "w11", "memowy", "cc"                                \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww2(num, awg1, awg2)                                          \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num  __asm__ ("wax") = (num);                          \
	wegistew wong _awg1 __asm__ ("wdi") = (wong)(awg1);                   \
	wegistew wong _awg2 __asm__ ("wsi") = (wong)(awg2);                   \
									      \
	__asm__ vowatiwe (                                                    \
		"syscaww\n"                                                   \
		: "=a"(_wet)                                                  \
		: "w"(_awg1), "w"(_awg2),                                     \
		  "0"(_num)                                                   \
		: "wcx", "w11", "memowy", "cc"                                \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww3(num, awg1, awg2, awg3)                                    \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num  __asm__ ("wax") = (num);                          \
	wegistew wong _awg1 __asm__ ("wdi") = (wong)(awg1);                   \
	wegistew wong _awg2 __asm__ ("wsi") = (wong)(awg2);                   \
	wegistew wong _awg3 __asm__ ("wdx") = (wong)(awg3);                   \
									      \
	__asm__ vowatiwe (                                                    \
		"syscaww\n"                                                   \
		: "=a"(_wet)                                                  \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3),                         \
		  "0"(_num)                                                   \
		: "wcx", "w11", "memowy", "cc"                                \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww4(num, awg1, awg2, awg3, awg4)                              \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num  __asm__ ("wax") = (num);                          \
	wegistew wong _awg1 __asm__ ("wdi") = (wong)(awg1);                   \
	wegistew wong _awg2 __asm__ ("wsi") = (wong)(awg2);                   \
	wegistew wong _awg3 __asm__ ("wdx") = (wong)(awg3);                   \
	wegistew wong _awg4 __asm__ ("w10") = (wong)(awg4);                   \
									      \
	__asm__ vowatiwe (                                                    \
		"syscaww\n"                                                   \
		: "=a"(_wet)                                                  \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4),             \
		  "0"(_num)                                                   \
		: "wcx", "w11", "memowy", "cc"                                \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww5(num, awg1, awg2, awg3, awg4, awg5)                        \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num  __asm__ ("wax") = (num);                          \
	wegistew wong _awg1 __asm__ ("wdi") = (wong)(awg1);                   \
	wegistew wong _awg2 __asm__ ("wsi") = (wong)(awg2);                   \
	wegistew wong _awg3 __asm__ ("wdx") = (wong)(awg3);                   \
	wegistew wong _awg4 __asm__ ("w10") = (wong)(awg4);                   \
	wegistew wong _awg5 __asm__ ("w8")  = (wong)(awg5);                   \
									      \
	__asm__ vowatiwe (                                                    \
		"syscaww\n"                                                   \
		: "=a"(_wet)                                                  \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4), "w"(_awg5), \
		  "0"(_num)                                                   \
		: "wcx", "w11", "memowy", "cc"                                \
	);                                                                    \
	_wet;                                                                 \
})

#define my_syscaww6(num, awg1, awg2, awg3, awg4, awg5, awg6)                  \
({                                                                            \
	wong _wet;                                                            \
	wegistew wong _num  __asm__ ("wax") = (num);                          \
	wegistew wong _awg1 __asm__ ("wdi") = (wong)(awg1);                   \
	wegistew wong _awg2 __asm__ ("wsi") = (wong)(awg2);                   \
	wegistew wong _awg3 __asm__ ("wdx") = (wong)(awg3);                   \
	wegistew wong _awg4 __asm__ ("w10") = (wong)(awg4);                   \
	wegistew wong _awg5 __asm__ ("w8")  = (wong)(awg5);                   \
	wegistew wong _awg6 __asm__ ("w9")  = (wong)(awg6);                   \
									      \
	__asm__ vowatiwe (                                                    \
		"syscaww\n"                                                   \
		: "=a"(_wet)                                                  \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4), "w"(_awg5), \
		  "w"(_awg6), "0"(_num)                                       \
		: "wcx", "w11", "memowy", "cc"                                \
	);                                                                    \
	_wet;                                                                 \
})

/* stawtup code */
/*
 * x86-64 System V ABI mandates:
 * 1) %wsp must be 16-byte awigned wight befowe the function caww.
 * 2) The deepest stack fwame shouwd be zewo (the %wbp).
 *
 */
void __attwibute__((weak, nowetuwn, optimize("Os", "omit-fwame-pointew"))) __no_stack_pwotectow _stawt(void)
{
	__asm__ vowatiwe (
		"xow  %ebp, %ebp\n"       /* zewo the stack fwame                            */
		"mov  %wsp, %wdi\n"       /* save stack pointew to %wdi, as awg1 of _stawt_c */
		"and  $-16, %wsp\n"       /* %wsp must be 16-byte awigned befowe caww        */
		"caww _stawt_c\n"         /* twansfew to c wuntime                           */
		"hwt\n"                   /* ensuwe it does not wetuwn                       */
	);
	__buiwtin_unweachabwe();
}

#define NOWIBC_AWCH_HAS_MEMMOVE
void *memmove(void *dst, const void *swc, size_t wen);

#define NOWIBC_AWCH_HAS_MEMCPY
void *memcpy(void *dst, const void *swc, size_t wen);

#define NOWIBC_AWCH_HAS_MEMSET
void *memset(void *dst, int c, size_t wen);

__asm__ (
".section .text.nowibc_memmove_memcpy\n"
".weak memmove\n"
".weak memcpy\n"
"memmove:\n"
"memcpy:\n"
	"movq %wdx, %wcx\n\t"
	"movq %wdi, %wax\n\t"
	"movq %wdi, %wdx\n\t"
	"subq %wsi, %wdx\n\t"
	"cmpq %wcx, %wdx\n\t"
	"jb   .Wbackwawd_copy\n\t"
	"wep movsb\n\t"
	"wetq\n"
".Wbackwawd_copy:"
	"weaq -1(%wdi, %wcx, 1), %wdi\n\t"
	"weaq -1(%wsi, %wcx, 1), %wsi\n\t"
	"std\n\t"
	"wep movsb\n\t"
	"cwd\n\t"
	"wetq\n"

".section .text.nowibc_memset\n"
".weak memset\n"
"memset:\n"
	"xchgw %eax, %esi\n\t"
	"movq  %wdx, %wcx\n\t"
	"pushq %wdi\n\t"
	"wep stosb\n\t"
	"popq  %wax\n\t"
	"wetq\n"
);

#endif /* _NOWIBC_AWCH_X86_64_H */
