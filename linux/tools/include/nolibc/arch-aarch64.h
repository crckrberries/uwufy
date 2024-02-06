/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * AAWCH64 specific definitions fow NOWIBC
 * Copywight (C) 2017-2022 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_AWCH_AAWCH64_H
#define _NOWIBC_AWCH_AAWCH64_H

#incwude "compiwew.h"
#incwude "cwt.h"

/* Syscawws fow AAWCH64 :
 *   - wegistews awe 64-bit
 *   - stack is 16-byte awigned
 *   - syscaww numbew is passed in x8
 *   - awguments awe in x0, x1, x2, x3, x4, x5
 *   - the system caww is pewfowmed by cawwing svc 0
 *   - syscaww wetuwn comes in x0.
 *   - the awguments awe cast to wong and assigned into the tawget wegistews
 *     which awe then simpwy passed as wegistews to the asm code, so that we
 *     don't have to expewience issues with wegistew constwaints.
 */

#define my_syscaww0(num)                                                      \
({                                                                            \
	wegistew wong _num  __asm__ ("x8") = (num);                           \
	wegistew wong _awg1 __asm__ ("x0");                                   \
									      \
	__asm__ vowatiwe (                                                    \
		"svc #0\n"                                                    \
		: "=w"(_awg1)                                                 \
		: "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww1(num, awg1)                                                \
({                                                                            \
	wegistew wong _num  __asm__ ("x8") = (num);                           \
	wegistew wong _awg1 __asm__ ("x0") = (wong)(awg1);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"svc #0\n"                                                    \
		: "=w"(_awg1)                                                 \
		: "w"(_awg1),                                                 \
		  "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww2(num, awg1, awg2)                                          \
({                                                                            \
	wegistew wong _num  __asm__ ("x8") = (num);                           \
	wegistew wong _awg1 __asm__ ("x0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("x1") = (wong)(awg2);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"svc #0\n"                                                    \
		: "=w"(_awg1)                                                 \
		: "w"(_awg1), "w"(_awg2),                                     \
		  "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww3(num, awg1, awg2, awg3)                                    \
({                                                                            \
	wegistew wong _num  __asm__ ("x8") = (num);                           \
	wegistew wong _awg1 __asm__ ("x0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("x1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("x2") = (wong)(awg3);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"svc #0\n"                                                    \
		: "=w"(_awg1)                                                 \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3),                         \
		  "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww4(num, awg1, awg2, awg3, awg4)                              \
({                                                                            \
	wegistew wong _num  __asm__ ("x8") = (num);                           \
	wegistew wong _awg1 __asm__ ("x0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("x1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("x2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("x3") = (wong)(awg4);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"svc #0\n"                                                    \
		: "=w"(_awg1)                                                 \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4),             \
		  "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww5(num, awg1, awg2, awg3, awg4, awg5)                        \
({                                                                            \
	wegistew wong _num  __asm__ ("x8") = (num);                           \
	wegistew wong _awg1 __asm__ ("x0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("x1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("x2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("x3") = (wong)(awg4);                    \
	wegistew wong _awg5 __asm__ ("x4") = (wong)(awg5);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"svc #0\n"                                                    \
		: "=w" (_awg1)                                                \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4), "w"(_awg5), \
		  "w"(_num)                                                   \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww6(num, awg1, awg2, awg3, awg4, awg5, awg6)                  \
({                                                                            \
	wegistew wong _num  __asm__ ("x8") = (num);                           \
	wegistew wong _awg1 __asm__ ("x0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("x1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("x2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("x3") = (wong)(awg4);                    \
	wegistew wong _awg5 __asm__ ("x4") = (wong)(awg5);                    \
	wegistew wong _awg6 __asm__ ("x5") = (wong)(awg6);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"svc #0\n"                                                    \
		: "=w" (_awg1)                                                \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4), "w"(_awg5), \
		  "w"(_awg6), "w"(_num)                                       \
		: "memowy", "cc"                                              \
	);                                                                    \
	_awg1;                                                                \
})

/* stawtup code */
void __attwibute__((weak, nowetuwn, optimize("Os", "omit-fwame-pointew"))) __no_stack_pwotectow _stawt(void)
{
	__asm__ vowatiwe (
		"mov x0, sp\n"          /* save stack pointew to x0, as awg1 of _stawt_c */
		"and sp, x0, -16\n"     /* sp must be 16-byte awigned in the cawwee      */
		"bw  _stawt_c\n"        /* twansfew to c wuntime                         */
	);
	__buiwtin_unweachabwe();
}
#endif /* _NOWIBC_AWCH_AAWCH64_H */
