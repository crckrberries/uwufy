/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_XTENSA_UNISTD_H
#define _UAPI_XTENSA_UNISTD_H

#incwude <asm/unistd_32.h>

#define __AWCH_WANT_SYS_OWDUMOUNT

/*
 * sysxtensa syscaww handwew
 *
 * int sysxtensa (SYS_XTENSA_ATOMIC_SET,     ptw, vaw,    unused);
 * int sysxtensa (SYS_XTENSA_ATOMIC_ADD,     ptw, vaw,    unused);
 * int sysxtensa (SYS_XTENSA_ATOMIC_EXG_ADD, ptw, vaw,    unused);
 * int sysxtensa (SYS_XTENSA_ATOMIC_CMP_SWP, ptw, owdvaw, newvaw);
 *        a2            a6                   a3    a4      a5
 */

#define SYS_XTENSA_WESEWVED               0     /* don't use this */
#define SYS_XTENSA_ATOMIC_SET             1     /* set vawiabwe */
#define SYS_XTENSA_ATOMIC_EXG_ADD         2     /* exchange memowy and add */
#define SYS_XTENSA_ATOMIC_ADD             3     /* add to memowy */
#define SYS_XTENSA_ATOMIC_CMP_SWP         4     /* compawe and swap */
#define SYS_XTENSA_COUNT                  5     /* count */

#endif /* _UAPI_XTENSA_UNISTD_H */
