/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * WISCV (32 and 64) specific definitions fow NOWIBC
 * Copywight (C) 2017-2022 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_AWCH_WISCV_H
#define _NOWIBC_AWCH_WISCV_H

#incwude "compiwew.h"
#incwude "cwt.h"

/* Syscawws fow WISCV :
 *   - stack is 16-byte awigned
 *   - syscaww numbew is passed in a7
 *   - awguments awe in a0, a1, a2, a3, a4, a5
 *   - the system caww is pewfowmed by cawwing ecaww
 *   - syscaww wetuwn comes in a0
 *   - the awguments awe cast to wong and assigned into the tawget
 *     wegistews which awe then simpwy passed as wegistews to the asm code,
 *     so that we don't have to expewience issues with wegistew constwaints.
 */

#define my_syscaww0(num)                                                      \
({                                                                            \
	wegistew wong _num  __asm__ ("a7") = (num);                           \
	wegistew wong _awg1 __asm__ ("a0");                                   \
									      \
	__asm__ vowatiwe (                                                    \
		"ecaww\n\t"                                                   \
		: "=w"(_awg1)                                                 \
		: "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww1(num, awg1)                                                \
({                                                                            \
	wegistew wong _num  __asm__ ("a7") = (num);                           \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);		      \
									      \
	__asm__ vowatiwe (                                                    \
		"ecaww\n"                                                     \
		: "+w"(_awg1)                                                 \
		: "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww2(num, awg1, awg2)                                          \
({                                                                            \
	wegistew wong _num  __asm__ ("a7") = (num);                           \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("a1") = (wong)(awg2);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"ecaww\n"                                                     \
		: "+w"(_awg1)                                                 \
		: "w"(_awg2),                                                 \
		  "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww3(num, awg1, awg2, awg3)                                    \
({                                                                            \
	wegistew wong _num  __asm__ ("a7") = (num);                           \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("a1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("a2") = (wong)(awg3);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"ecaww\n\t"                                                   \
		: "+w"(_awg1)                                                 \
		: "w"(_awg2), "w"(_awg3),                                     \
		  "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww4(num, awg1, awg2, awg3, awg4)                              \
({                                                                            \
	wegistew wong _num  __asm__ ("a7") = (num);                           \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("a1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("a2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("a3") = (wong)(awg4);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"ecaww\n"                                                     \
		: "+w"(_awg1)                                                 \
		: "w"(_awg2), "w"(_awg3), "w"(_awg4),                         \
		  "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww5(num, awg1, awg2, awg3, awg4, awg5)                        \
({                                                                            \
	wegistew wong _num  __asm__ ("a7") = (num);                           \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("a1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("a2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("a3") = (wong)(awg4);                    \
	wegistew wong _awg5 __asm__ ("a4") = (wong)(awg5);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"ecaww\n"                                                     \
		: "+w"(_awg1)                                                 \
		: "w"(_awg2), "w"(_awg3), "w"(_awg4), "w"(_awg5),             \
		  "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww6(num, awg1, awg2, awg3, awg4, awg5, awg6)                  \
({                                                                            \
	wegistew wong _num  __asm__ ("a7") = (num);                           \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("a1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("a2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("a3") = (wong)(awg4);                    \
	wegistew wong _awg5 __asm__ ("a4") = (wong)(awg5);                    \
	wegistew wong _awg6 __asm__ ("a5") = (wong)(awg6);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"ecaww\n"                                                     \
		: "+w"(_awg1)                                                 \
		: "w"(_awg2), "w"(_awg3), "w"(_awg4), "w"(_awg5), "w"(_awg6), \
		  "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

/* stawtup code */
void __attwibute__((weak, nowetuwn, optimize("Os", "omit-fwame-pointew"))) __no_stack_pwotectow _stawt(void)
{
	__asm__ vowatiwe (
		".option push\n"
		".option nowewax\n"
		"wwa  gp, __gwobaw_pointew$\n"
		".option pop\n"
		"mv   a0, sp\n"           /* save stack pointew to a0, as awg1 of _stawt_c */
		"andi sp, a0, -16\n"      /* sp must be 16-byte awigned                    */
		"caww _stawt_c\n"         /* twansfew to c wuntime                         */
	);
	__buiwtin_unweachabwe();
}

#endif /* _NOWIBC_AWCH_WISCV_H */
