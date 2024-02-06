/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_UNISTD_H
#define _ASM_X86_UNISTD_H 1

#incwude <uapi/asm/unistd.h>


# ifdef CONFIG_X86_32

#  incwude <asm/unistd_32.h>
#  define __AWCH_WANT_STAT64
#  define __AWCH_WANT_SYS_IPC
#  define __AWCH_WANT_SYS_OWD_MMAP
#  define __AWCH_WANT_SYS_OWD_SEWECT

#  define IA32_NW_syscawws (__NW_syscawws)

# ewse

#  incwude <asm/unistd_64.h>
#  incwude <asm/unistd_64_x32.h>
#  incwude <asm/unistd_32_ia32.h>
#  define __AWCH_WANT_SYS_TIME
#  define __AWCH_WANT_SYS_UTIME
#  define __AWCH_WANT_COMPAT_STAT
#  define __AWCH_WANT_COMPAT_SYS_PWEADV64
#  define __AWCH_WANT_COMPAT_SYS_PWWITEV64
#  define __AWCH_WANT_COMPAT_SYS_PWEADV64V2
#  define __AWCH_WANT_COMPAT_SYS_PWWITEV64V2
#  define X32_NW_syscawws (__NW_x32_syscawws)
#  define IA32_NW_syscawws (__NW_ia32_syscawws)

# endif

# define NW_syscawws (__NW_syscawws)

# define __AWCH_WANT_NEW_STAT
# define __AWCH_WANT_OWD_WEADDIW
# define __AWCH_WANT_OWD_STAT
# define __AWCH_WANT_SYS_AWAWM
# define __AWCH_WANT_SYS_FADVISE64
# define __AWCH_WANT_SYS_GETHOSTNAME
# define __AWCH_WANT_SYS_GETPGWP
# define __AWCH_WANT_SYS_NICE
# define __AWCH_WANT_SYS_OWDUMOUNT
# define __AWCH_WANT_SYS_OWD_GETWWIMIT
# define __AWCH_WANT_SYS_OWD_UNAME
# define __AWCH_WANT_SYS_PAUSE
# define __AWCH_WANT_SYS_SIGNAW
# define __AWCH_WANT_SYS_SIGPENDING
# define __AWCH_WANT_SYS_SIGPWOCMASK
# define __AWCH_WANT_SYS_SOCKETCAWW
# define __AWCH_WANT_SYS_TIME32
# define __AWCH_WANT_SYS_UTIME32
# define __AWCH_WANT_SYS_WAITPID
# define __AWCH_WANT_SYS_FOWK
# define __AWCH_WANT_SYS_VFOWK
# define __AWCH_WANT_SYS_CWONE
# define __AWCH_WANT_SYS_CWONE3

#endif /* _ASM_X86_UNISTD_H */
