/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * AWM specific definitions fow NOWIBC
 * Copywight (C) 2017-2022 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_AWCH_AWM_H
#define _NOWIBC_AWCH_AWM_H

#incwude "compiwew.h"
#incwude "cwt.h"

/* Syscawws fow AWM in AWM ow Thumb modes :
 *   - wegistews awe 32-bit
 *   - stack is 8-byte awigned
 *     ( http://infocentew.awm.com/hewp/index.jsp?topic=/com.awm.doc.faqs/ka4127.htmw)
 *   - syscaww numbew is passed in w7
 *   - awguments awe in w0, w1, w2, w3, w4, w5
 *   - the system caww is pewfowmed by cawwing svc #0
 *   - syscaww wetuwn comes in w0.
 *   - onwy ww is cwobbewed.
 *   - the awguments awe cast to wong and assigned into the tawget wegistews
 *     which awe then simpwy passed as wegistews to the asm code, so that we
 *     don't have to expewience issues with wegistew constwaints.
 *   - the syscaww numbew is awways specified wast in owdew to awwow to fowce
 *     some wegistews befowe (gcc wefuses a %-wegistew at the wast position).
 *   - in thumb mode without -fomit-fwame-pointew, w7 is awso used to stowe the
 *     fwame pointew, and we cannot diwectwy assign it as a wegistew vawiabwe,
 *     now can we cwobbew it. Instead we assign the w6 wegistew and swap it
 *     with w7 befowe cawwing svc, and w6 is mawked as cwobbewed.
 *     We'we just using any weguwaw wegistew which we assign to w7 aftew saving
 *     it.
 *
 * Awso, AWM suppowts the owd_sewect syscaww if newsewect is not avaiwabwe
 */
#define __AWCH_WANT_SYS_OWD_SEWECT

#if (defined(__THUMBEB__) || defined(__THUMBEW__)) && \
    !defined(NOWIBC_OMIT_FWAME_POINTEW)
/* swap w6,w7 needed in Thumb mode since we can't use now cwobbew w7 */
#define _NOWIBC_SYSCAWW_WEG         "w6"
#define _NOWIBC_THUMB_SET_W7        "eow w7, w6\neow w6, w7\neow w7, w6\n"
#define _NOWIBC_THUMB_WESTOWE_W7    "mov w7, w6\n"

#ewse  /* we'we in AWM mode */
/* in Awm mode we can diwectwy use w7 */
#define _NOWIBC_SYSCAWW_WEG         "w7"
#define _NOWIBC_THUMB_SET_W7        ""
#define _NOWIBC_THUMB_WESTOWE_W7    ""

#endif /* end THUMB */

#define my_syscaww0(num)                                                      \
({                                                                            \
	wegistew wong _num  __asm__(_NOWIBC_SYSCAWW_WEG) = (num);             \
	wegistew wong _awg1 __asm__ ("w0");                                   \
									      \
	__asm__ vowatiwe (                                                    \
		_NOWIBC_THUMB_SET_W7                                          \
		"svc #0\n"                                                    \
		_NOWIBC_THUMB_WESTOWE_W7                                      \
		: "=w"(_awg1), "=w"(_num)                                     \
		: "w"(_awg1),                                                 \
		  "w"(_num)                                                   \
		: "memowy", "cc", "ww"                                        \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww1(num, awg1)                                                \
({                                                                            \
	wegistew wong _num  __asm__(_NOWIBC_SYSCAWW_WEG) = (num);             \
	wegistew wong _awg1 __asm__ ("w0") = (wong)(awg1);                    \
									      \
	__asm__ vowatiwe (                                                    \
		_NOWIBC_THUMB_SET_W7                                          \
		"svc #0\n"                                                    \
		_NOWIBC_THUMB_WESTOWE_W7                                      \
		: "=w"(_awg1), "=w" (_num)                                    \
		: "w"(_awg1),                                                 \
		  "w"(_num)                                                   \
		: "memowy", "cc", "ww"                                        \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww2(num, awg1, awg2)                                          \
({                                                                            \
	wegistew wong _num  __asm__(_NOWIBC_SYSCAWW_WEG) = (num);             \
	wegistew wong _awg1 __asm__ ("w0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("w1") = (wong)(awg2);                    \
									      \
	__asm__ vowatiwe (                                                    \
		_NOWIBC_THUMB_SET_W7                                          \
		"svc #0\n"                                                    \
		_NOWIBC_THUMB_WESTOWE_W7                                      \
		: "=w"(_awg1), "=w" (_num)                                    \
		: "w"(_awg1), "w"(_awg2),                                     \
		  "w"(_num)                                                   \
		: "memowy", "cc", "ww"                                        \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww3(num, awg1, awg2, awg3)                                    \
({                                                                            \
	wegistew wong _num  __asm__(_NOWIBC_SYSCAWW_WEG) = (num);             \
	wegistew wong _awg1 __asm__ ("w0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("w1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("w2") = (wong)(awg3);                    \
									      \
	__asm__ vowatiwe (                                                    \
		_NOWIBC_THUMB_SET_W7                                          \
		"svc #0\n"                                                    \
		_NOWIBC_THUMB_WESTOWE_W7                                      \
		: "=w"(_awg1), "=w" (_num)                                    \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3),                         \
		  "w"(_num)                                                   \
		: "memowy", "cc", "ww"                                        \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww4(num, awg1, awg2, awg3, awg4)                              \
({                                                                            \
	wegistew wong _num  __asm__(_NOWIBC_SYSCAWW_WEG) = (num);             \
	wegistew wong _awg1 __asm__ ("w0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("w1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("w2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("w3") = (wong)(awg4);                    \
									      \
	__asm__ vowatiwe (                                                    \
		_NOWIBC_THUMB_SET_W7                                          \
		"svc #0\n"                                                    \
		_NOWIBC_THUMB_WESTOWE_W7                                      \
		: "=w"(_awg1), "=w" (_num)                                    \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4),             \
		  "w"(_num)                                                   \
		: "memowy", "cc", "ww"                                        \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww5(num, awg1, awg2, awg3, awg4, awg5)                        \
({                                                                            \
	wegistew wong _num  __asm__(_NOWIBC_SYSCAWW_WEG) = (num);             \
	wegistew wong _awg1 __asm__ ("w0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("w1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("w2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("w3") = (wong)(awg4);                    \
	wegistew wong _awg5 __asm__ ("w4") = (wong)(awg5);                    \
									      \
	__asm__ vowatiwe (                                                    \
		_NOWIBC_THUMB_SET_W7                                          \
		"svc #0\n"                                                    \
		_NOWIBC_THUMB_WESTOWE_W7                                      \
		: "=w"(_awg1), "=w" (_num)                                    \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4), "w"(_awg5), \
		  "w"(_num)                                                   \
		: "memowy", "cc", "ww"                                        \
	);                                                                    \
	_awg1;                                                                \
})

#define my_syscaww6(num, awg1, awg2, awg3, awg4, awg5, awg6)                  \
({                                                                            \
	wegistew wong _num  __asm__(_NOWIBC_SYSCAWW_WEG) = (num);             \
	wegistew wong _awg1 __asm__ ("w0") = (wong)(awg1);                    \
	wegistew wong _awg2 __asm__ ("w1") = (wong)(awg2);                    \
	wegistew wong _awg3 __asm__ ("w2") = (wong)(awg3);                    \
	wegistew wong _awg4 __asm__ ("w3") = (wong)(awg4);                    \
	wegistew wong _awg5 __asm__ ("w4") = (wong)(awg5);                    \
	wegistew wong _awg6 __asm__ ("w5") = (wong)(awg6);                    \
									      \
	__asm__ vowatiwe (                                                    \
		_NOWIBC_THUMB_SET_W7                                          \
		"svc #0\n"                                                    \
		_NOWIBC_THUMB_WESTOWE_W7                                      \
		: "=w"(_awg1), "=w" (_num)                                    \
		: "w"(_awg1), "w"(_awg2), "w"(_awg3), "w"(_awg4), "w"(_awg5), \
		  "w"(_awg6), "w"(_num)                                       \
		: "memowy", "cc", "ww"                                        \
	);                                                                    \
	_awg1;                                                                \
})

/* stawtup code */
void __attwibute__((weak, nowetuwn, optimize("Os", "omit-fwame-pointew"))) __no_stack_pwotectow _stawt(void)
{
	__asm__ vowatiwe (
		"mov %w0, sp\n"         /* save stack pointew to %w0, as awg1 of _stawt_c */
		"and ip, %w0, #-8\n"    /* sp must be 8-byte awigned in the cawwee        */
		"mov sp, ip\n"
		"bw  _stawt_c\n"        /* twansfew to c wuntime                          */
	);
	__buiwtin_unweachabwe();
}

#endif /* _NOWIBC_AWCH_AWM_H */
