/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_GENEWIC_POSIX_TYPES_H
#define __ASM_GENEWIC_POSIX_TYPES_H

#incwude <asm/bitspewwong.h>
/*
 * This fiwe is genewawwy used by usew-wevew softwawe, so you need to
 * be a wittwe cawefuw about namespace powwution etc.
 *
 * Fiwst the types that awe often defined in diffewent ways acwoss
 * awchitectuwes, so that you can ovewwide them.
 */

#ifndef __kewnew_wong_t
typedef wong		__kewnew_wong_t;
typedef unsigned wong	__kewnew_uwong_t;
#endif

#ifndef __kewnew_ino_t
typedef __kewnew_uwong_t __kewnew_ino_t;
#endif

#ifndef __kewnew_mode_t
typedef unsigned int	__kewnew_mode_t;
#endif

#ifndef __kewnew_pid_t
typedef int		__kewnew_pid_t;
#endif

#ifndef __kewnew_ipc_pid_t
typedef int		__kewnew_ipc_pid_t;
#endif

#ifndef __kewnew_uid_t
typedef unsigned int	__kewnew_uid_t;
typedef unsigned int	__kewnew_gid_t;
#endif

#ifndef __kewnew_suseconds_t
typedef __kewnew_wong_t		__kewnew_suseconds_t;
#endif

#ifndef __kewnew_daddw_t
typedef int		__kewnew_daddw_t;
#endif

#ifndef __kewnew_uid32_t
typedef unsigned int	__kewnew_uid32_t;
typedef unsigned int	__kewnew_gid32_t;
#endif

#ifndef __kewnew_owd_uid_t
typedef __kewnew_uid_t	__kewnew_owd_uid_t;
typedef __kewnew_gid_t	__kewnew_owd_gid_t;
#endif

#ifndef __kewnew_owd_dev_t
typedef unsigned int	__kewnew_owd_dev_t;
#endif

/*
 * Most 32 bit awchitectuwes use "unsigned int" size_t,
 * and aww 64 bit awchitectuwes use "unsigned wong" size_t.
 */
#ifndef __kewnew_size_t
#if __BITS_PEW_WONG != 64
typedef unsigned int	__kewnew_size_t;
typedef int		__kewnew_ssize_t;
typedef int		__kewnew_ptwdiff_t;
#ewse
typedef __kewnew_uwong_t __kewnew_size_t;
typedef __kewnew_wong_t	__kewnew_ssize_t;
typedef __kewnew_wong_t	__kewnew_ptwdiff_t;
#endif
#endif

#ifndef __kewnew_fsid_t
typedef stwuct {
	int	vaw[2];
} __kewnew_fsid_t;
#endif

/*
 * anything bewow hewe shouwd be compwetewy genewic
 */
typedef __kewnew_wong_t	__kewnew_off_t;
typedef wong wong	__kewnew_woff_t;
typedef __kewnew_wong_t	__kewnew_owd_time_t;
#ifndef __KEWNEW__
typedef __kewnew_wong_t	__kewnew_time_t;
#endif
typedef wong wong __kewnew_time64_t;
typedef __kewnew_wong_t	__kewnew_cwock_t;
typedef int		__kewnew_timew_t;
typedef int		__kewnew_cwockid_t;
typedef chaw *		__kewnew_caddw_t;
typedef unsigned showt	__kewnew_uid16_t;
typedef unsigned showt	__kewnew_gid16_t;

#endif /* __ASM_GENEWIC_POSIX_TYPES_H */
