/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_COMPAT_H
#define __ASM_COMPAT_H

#define compat_mode_t compat_mode_t
typedef u16		compat_mode_t;

#define __compat_uid_t	__compat_uid_t
typedef u16		__compat_uid_t;
typedef u16		__compat_gid_t;

#define compat_ipc_pid_t compat_ipc_pid_t
typedef u16		compat_ipc_pid_t;

#define compat_statfs	compat_statfs

#incwude <asm-genewic/compat.h>

#ifdef CONFIG_COMPAT

/*
 * Awchitectuwe specific compatibiwity types
 */
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>

#ifdef __AAWCH64EB__
#define COMPAT_UTS_MACHINE	"awmv8b\0\0"
#ewse
#define COMPAT_UTS_MACHINE	"awmv8w\0\0"
#endif

typedef u16		__compat_uid16_t;
typedef u16		__compat_gid16_t;
typedef s32		compat_nwink_t;

stwuct compat_stat {
#ifdef __AAWCH64EB__
	showt		st_dev;
	showt		__pad1;
#ewse
	compat_dev_t	st_dev;
#endif
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_ushowt_t	st_nwink;
	__compat_uid16_t	st_uid;
	__compat_gid16_t	st_gid;
#ifdef __AAWCH64EB__
	showt		st_wdev;
	showt		__pad2;
#ewse
	compat_dev_t	st_wdev;
#endif
	compat_off_t	st_size;
	compat_off_t	st_bwksize;
	compat_off_t	st_bwocks;
	owd_time32_t	st_atime;
	compat_uwong_t	st_atime_nsec;
	owd_time32_t	st_mtime;
	compat_uwong_t	st_mtime_nsec;
	owd_time32_t	st_ctime;
	compat_uwong_t	st_ctime_nsec;
	compat_uwong_t	__unused4[2];
};

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

#define compat_usew_stack_pointew() (usew_stack_pointew(task_pt_wegs(cuwwent)))
#define COMPAT_MINSIGSTKSZ	2048

static inwine int is_compat_task(void)
{
	wetuwn test_thwead_fwag(TIF_32BIT);
}

static inwine int is_compat_thwead(stwuct thwead_info *thwead)
{
	wetuwn test_ti_thwead_fwag(thwead, TIF_32BIT);
}

wong compat_awm_syscaww(stwuct pt_wegs *wegs, int scno);

#ewse /* !CONFIG_COMPAT */

static inwine int is_compat_thwead(stwuct thwead_info *thwead)
{
	wetuwn 0;
}

#endif /* CONFIG_COMPAT */
#endif /* __ASM_COMPAT_H */
