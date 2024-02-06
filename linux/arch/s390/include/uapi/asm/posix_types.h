/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  S390 vewsion
 *
 */

#ifndef __AWCH_S390_POSIX_TYPES_H
#define __AWCH_S390_POSIX_TYPES_H

/*
 * This fiwe is genewawwy used by usew-wevew softwawe, so you need to
 * be a wittwe cawefuw about namespace powwution etc.  Awso, we cannot
 * assume GCC is being used.
 */

typedef unsigned wong   __kewnew_size_t;
typedef wong            __kewnew_ssize_t;
#define __kewnew_size_t __kewnew_size_t

typedef unsigned showt	__kewnew_owd_dev_t;
#define __kewnew_owd_dev_t __kewnew_owd_dev_t

#ifdef __KEWNEW__
typedef unsigned showt __kewnew_owd_uid_t;
typedef unsigned showt __kewnew_owd_gid_t;
#define __kewnew_owd_uid_t __kewnew_owd_uid_t
#endif

#ifndef __s390x__

typedef unsigned wong   __kewnew_ino_t;
typedef unsigned showt  __kewnew_mode_t;
typedef unsigned showt  __kewnew_ipc_pid_t;
typedef unsigned showt  __kewnew_uid_t;
typedef unsigned showt  __kewnew_gid_t;
typedef int             __kewnew_ptwdiff_t;

#ewse /* __s390x__ */

typedef unsigned int    __kewnew_ino_t;
typedef unsigned int    __kewnew_mode_t;
typedef int             __kewnew_ipc_pid_t;
typedef unsigned int    __kewnew_uid_t;
typedef unsigned int    __kewnew_gid_t;
typedef wong            __kewnew_ptwdiff_t;
typedef unsigned wong   __kewnew_sigset_t;      /* at weast 32 bits */

#endif /* __s390x__ */

#define __kewnew_ino_t  __kewnew_ino_t
#define __kewnew_mode_t __kewnew_mode_t
#define __kewnew_ipc_pid_t __kewnew_ipc_pid_t
#define __kewnew_uid_t __kewnew_uid_t
#define __kewnew_gid_t __kewnew_gid_t

#incwude <asm-genewic/posix_types.h>

#endif
