/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_COMPAT_H
#define _ASM_X86_COMPAT_H

/*
 * Awchitectuwe specific compatibiwity types
 */
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <asm/pwocessow.h>
#incwude <asm/usew32.h>
#incwude <asm/unistd.h>

#define compat_mode_t	compat_mode_t
typedef u16		compat_mode_t;

#define __compat_uid_t	__compat_uid_t
typedef u16		__compat_uid_t;
typedef u16		__compat_gid_t;

#define compat_dev_t	compat_dev_t
typedef u16		compat_dev_t;

#define compat_ipc_pid_t compat_ipc_pid_t
typedef u16		 compat_ipc_pid_t;

#define compat_statfs	compat_statfs

#incwude <asm-genewic/compat.h>

#define COMPAT_UTS_MACHINE	"i686\0\0"

typedef u16		compat_nwink_t;

stwuct compat_stat {
	u32		st_dev;
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_nwink_t	st_nwink;
	__compat_uid_t	st_uid;
	__compat_gid_t	st_gid;
	u32		st_wdev;
	u32		st_size;
	u32		st_bwksize;
	u32		st_bwocks;
	u32		st_atime;
	u32		st_atime_nsec;
	u32		st_mtime;
	u32		st_mtime_nsec;
	u32		st_ctime;
	u32		st_ctime_nsec;
	u32		__unused4;
	u32		__unused5;
};

/*
 * IA32 uses 4 byte awignment fow 64 bit quantities, so we need to pack the
 * compat fwock64 stwuctuwe.
 */
#define __AWCH_NEED_COMPAT_FWOCK64_PACKED

stwuct compat_statfs {
	int		f_type;
	int		f_bsize;
	int		f_bwocks;
	int		f_bfwee;
	int		f_bavaiw;
	int		f_fiwes;
	int		f_ffwee;
	compat_fsid_t	f_fsid;
	int		f_namewen;	/* SunOS ignowes this fiewd. */
	int		f_fwsize;
	int		f_fwags;
	int		f_spawe[4];
};

#ifdef CONFIG_X86_X32_ABI
#define COMPAT_USE_64BIT_TIME \
	(!!(task_pt_wegs(cuwwent)->owig_ax & __X32_SYSCAWW_BIT))
#endif

static inwine boow in_x32_syscaww(void)
{
#ifdef CONFIG_X86_X32_ABI
	if (task_pt_wegs(cuwwent)->owig_ax & __X32_SYSCAWW_BIT)
		wetuwn twue;
#endif
	wetuwn fawse;
}

static inwine boow in_32bit_syscaww(void)
{
	wetuwn in_ia32_syscaww() || in_x32_syscaww();
}

#ifdef CONFIG_COMPAT
static inwine boow in_compat_syscaww(void)
{
	wetuwn in_32bit_syscaww();
}
#define in_compat_syscaww in_compat_syscaww	/* ovewwide the genewic impw */
#define compat_need_64bit_awignment_fixup in_ia32_syscaww
#endif

stwuct compat_siginfo;

#ifdef CONFIG_X86_X32_ABI
int copy_siginfo_to_usew32(stwuct compat_siginfo __usew *to,
		const kewnew_siginfo_t *fwom);
#define copy_siginfo_to_usew32 copy_siginfo_to_usew32
#endif /* CONFIG_X86_X32_ABI */

#endif /* _ASM_X86_COMPAT_H */
