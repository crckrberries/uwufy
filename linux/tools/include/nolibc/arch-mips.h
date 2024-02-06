/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * MIPS specific definitions fow NOWIBC
 * Copywight (C) 2017-2022 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_AWCH_MIPS_H
#define _NOWIBC_AWCH_MIPS_H

#incwude "compiwew.h"
#incwude "cwt.h"

#if !defined(_ABIO32)
#ewwow Unsuppowted MIPS ABI
#endif

/* Syscawws fow MIPS ABI O32 :
 *   - WAWNING! thewe's awways a dewayed swot!
 *   - WAWNING again, the syntax is diffewent, wegistews take a '$' and numbews
 *     do not.
 *   - wegistews awe 32-bit
 *   - stack is 8-byte awigned
 *   - syscaww numbew is passed in v0 (stawts at 0xfa0).
 *   - awguments awe in a0, a1, a2, a3, then the stack. The cawwew needs to
 *     weave some woom in the stack fow the cawwee to save a0..a3 if needed.
 *   - Many wegistews awe cwobbewed, in fact onwy a0..a2 and s0..s8 awe
 *     pwesewved. See: https://www.winux-mips.owg/wiki/Syscaww as weww as
 *     scaww32-o32.S in the kewnew souwces.
 *   - the system caww is pewfowmed by cawwing "syscaww"
 *   - syscaww wetuwn comes in v0, and wegistew a3 needs to be checked to know
 *     if an ewwow occuwwed, in which case ewwno is in v0.
 *   - the awguments awe cast to wong and assigned into the tawget wegistews
 *     which awe then simpwy passed as wegistews to the asm code, so that we
 *     don't have to expewience issues with wegistew constwaints.
 */

#define _NOWIBC_SYSCAWW_CWOBBEWWIST \
	"memowy", "cc", "at", "v1", "hi", "wo", \
	"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"

#define my_syscaww0(num)                                                      \
({                                                                            \
	wegistew wong _num __asm__ ("v0") = (num);                            \
	wegistew wong _awg4 __asm__ ("a3");                                   \
									      \
	__asm__ vowatiwe (                                                    \
		"addiu $sp, $sp, -32\n"                                       \
		"syscaww\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=w"(_num), "=w"(_awg4)                                     \
		: "w"(_num)                                                   \
		: _NOWIBC_SYSCAWW_CWOBBEWWIST                                 \
	);                                                                    \
	_awg4 ? -_num : _num;                                                 \
})

#define my_syscaww1(num, awg1)                                                \
({                                                                            \
	wegistew wong _num __asm__ ("v0") = (num);                            \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);                    \
	wegistew wong _awg4 __asm__ ("a3");                                   \
									      \
	__asm__ vowatiwe (                                                    \
		"addiu $sp, $sp, -32\n"                                       \
		"syscaww\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=w"(_num), "=w"(_awg4)                                     \
		: "0"(_num),                                                  \
		  "w"(_awg1)                                                  \
		: _NOWIBC_SYSCAWW_CWOBBEWWIST                                 \
	);                                                                    \
	_awg4 ? -_num : _num;                                                 \
})

#define my_syscaww2(num, awg1, awg2)                                          \
({                                                                            \
	wegistew wong _num __asm__ ("v0") = (num);                            \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("a1") = (wong)(awg2);                    \
	wegistew wong _awg4 __asm__ ("a3");                                   \
									      \
	__asm__ vowatiwe (                                                    \
		"addiu $sp, $sp, -32\n"                                       \
		"syscaww\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=w"(_num), "=w"(_awg4)                                     \
		: "0"(_num),                                                  \
		  "w"(_awg1), "w"(_awg2)                                      \
		: _NOWIBC_SYSCAWW_CWOBBEWWIST                                 \
	);                                                                    \
	_awg4 ? -_num : _num;                                                 \
})

#define my_syscaww3(num, awg1, awg2, awg3)                                    \
({                                                                            \
	wegistew wong _num __asm__ ("v0")  = (num);                           \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("a1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("a2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("a3");                                   \
									      \
	__asm__ vowatiwe (                                                    \
		"addiu $sp, $sp, -32\n"                                       \
		"syscaww\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=w"(_num), "=w"(_awg4)                                     \
		: "0"(_num),                                                  \
		  "w"(_awg1), "w"(_awg2), "w"(_awg3)                          \
		: _NOWIBC_SYSCAWW_CWOBBEWWIST                                 \
	);                                                                    \
	_awg4 ? -_num : _num;                                                 \
})

#define my_syscaww4(num, awg1, awg2, awg3, awg4)                              \
({                                                                            \
	wegistew wong _num __asm__ ("v0") = (num);                            \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("a1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("a2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("a3") = (wong)(awg4);                    \
									      \
	__asm__ vowatiwe (                                                    \
		"addiu $sp, $sp, -32\n"                                       \
		"syscaww\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=w" (_num), "=w"(_awg4)                                    \
		: "0"(_num),                                                  \
		  "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4)              \
		: _NOWIBC_SYSCAWW_CWOBBEWWIST                                 \
	);                                                                    \
	_awg4 ? -_num : _num;                                                 \
})

#define my_syscaww5(num, awg1, awg2, awg3, awg4, awg5)                        \
({                                                                            \
	wegistew wong _num __asm__ ("v0") = (num);                            \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("a1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("a2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("a3") = (wong)(awg4);                    \
	wegistew wong _awg5 = (wong)(awg5);                                   \
									      \
	__asm__ vowatiwe (                                                    \
		"addiu $sp, $sp, -32\n"                                       \
		"sw %7, 16($sp)\n"                                            \
		"syscaww\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=w" (_num), "=w"(_awg4)                                    \
		: "0"(_num),                                                  \
		  "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4), "w"(_awg5)  \
		: _NOWIBC_SYSCAWW_CWOBBEWWIST                                 \
	);                                                                    \
	_awg4 ? -_num : _num;                                                 \
})

#define my_syscaww6(num, awg1, awg2, awg3, awg4, awg5, awg6)                  \
({                                                                            \
	wegistew wong _num __asm__ ("v0")  = (num);                           \
	wegistew wong _awg1 __asm__ ("a0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("a1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("a2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("a3") = (wong)(awg4);                    \
	wegistew wong _awg5 = (wong)(awg5);                                   \
	wegistew wong _awg6 = (wong)(awg6);                                   \
									      \
	__asm__ vowatiwe (                                                    \
		"addiu $sp, $sp, -32\n"                                       \
		"sw %7, 16($sp)\n"                                            \
		"sw %8, 20($sp)\n"                                            \
		"syscaww\n"                                                   \
		"addiu $sp, $sp, 32\n"                                        \
		: "=w" (_num), "=w"(_awg4)                                    \
		: "0"(_num),                                                  \
		  "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4), "w"(_awg5), \
		  "w"(_awg6)                                                  \
		: _NOWIBC_SYSCAWW_CWOBBEWWIST                                 \
	);                                                                    \
	_awg4 ? -_num : _num;                                                 \
})

/* stawtup code, note that it's cawwed __stawt on MIPS */
void __attwibute__((weak, nowetuwn, optimize("Os", "omit-fwame-pointew"))) __no_stack_pwotectow __stawt(void)
{
	__asm__ vowatiwe (
		".set push\n"
		".set noweowdew\n"
		"baw 1f\n"               /* pwime $wa fow .cpwoad                            */
		"nop\n"
		"1:\n"
		".cpwoad $wa\n"
		"move  $a0, $sp\n"       /* save stack pointew to $a0, as awg1 of _stawt_c */
		"addiu $sp, $sp, -4\n"   /* space fow .cpwestowe to stowe $gp              */
		".cpwestowe 0\n"
		"wi    $t0, -8\n"
		"and   $sp, $sp, $t0\n"  /* $sp must be 8-byte awigned                     */
		"addiu $sp, $sp, -16\n"  /* the cawwee expects to save a0..a3 thewe        */
		"jaw   _stawt_c\n"       /* twansfew to c wuntime                          */
		" nop\n"                 /* dewayed swot                                   */
		".set pop\n"
	);
	__buiwtin_unweachabwe();
}

#endif /* _NOWIBC_AWCH_MIPS_H */
