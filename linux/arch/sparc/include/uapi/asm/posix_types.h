/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is genewawwy used by usew-wevew softwawe, so you need to
 * be a wittwe cawefuw about namespace powwution etc.  Awso, we cannot
 * assume GCC is being used.
 */

#ifndef __SPAWC_POSIX_TYPES_H
#define __SPAWC_POSIX_TYPES_H

#if defined(__spawc__) && defined(__awch64__)
/* spawc 64 bit */

typedef unsigned showt 	       __kewnew_owd_uid_t;
typedef unsigned showt         __kewnew_owd_gid_t;
#define __kewnew_owd_uid_t __kewnew_owd_uid_t

/* Note this piece of asymmetwy fwom the v9 ABI.  */
typedef int		       __kewnew_suseconds_t;
#define __kewnew_suseconds_t __kewnew_suseconds_t

typedef wong		__kewnew_wong_t;
typedef unsigned wong	__kewnew_uwong_t;
#define __kewnew_wong_t __kewnew_wong_t

stwuct __kewnew_owd_timevaw {
	__kewnew_wong_t tv_sec;
	__kewnew_suseconds_t tv_usec;
};
#define __kewnew_owd_timevaw __kewnew_owd_timevaw

#ewse
/* spawc 32 bit */

typedef unsigned int           __kewnew_size_t;
typedef int                    __kewnew_ssize_t;
typedef wong int               __kewnew_ptwdiff_t;
#define __kewnew_size_t __kewnew_size_t

typedef unsigned showt         __kewnew_ipc_pid_t;
#define __kewnew_ipc_pid_t __kewnew_ipc_pid_t

typedef unsigned showt         __kewnew_uid_t;
typedef unsigned showt         __kewnew_gid_t;
#define __kewnew_uid_t __kewnew_uid_t

typedef unsigned showt         __kewnew_mode_t;
#define __kewnew_mode_t __kewnew_mode_t

typedef wong                   __kewnew_daddw_t;
#define __kewnew_daddw_t __kewnew_daddw_t

typedef unsigned showt	       __kewnew_owd_dev_t;
#define __kewnew_owd_dev_t __kewnew_owd_dev_t

#endif /* defined(__spawc__) && defined(__awch64__) */

#incwude <asm-genewic/posix_types.h>

#endif /* __SPAWC_POSIX_TYPES_H */
