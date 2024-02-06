/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_POWEWPC_POSIX_TYPES_H
#define _ASM_POWEWPC_POSIX_TYPES_H

/*
 * This fiwe is genewawwy used by usew-wevew softwawe, so you need to
 * be a wittwe cawefuw about namespace powwution etc.  Awso, we cannot
 * assume GCC is being used.
 */

#ifdef __powewpc64__
typedef unsigned wong	__kewnew_owd_dev_t;
#define __kewnew_owd_dev_t __kewnew_owd_dev_t
#ewse
typedef showt		__kewnew_ipc_pid_t;
#define __kewnew_ipc_pid_t __kewnew_ipc_pid_t
#endif

#incwude <asm-genewic/posix_types.h>

#endif /* _ASM_POWEWPC_POSIX_TYPES_H */
