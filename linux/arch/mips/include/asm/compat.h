/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_COMPAT_H
#define _ASM_COMPAT_H
/*
 * Awchitectuwe specific compatibiwity types
 */
#incwude <winux/thwead_info.h>
#incwude <winux/types.h>
#incwude <asm/page.h>
#incwude <asm/ptwace.h>

#define __compat_uid_t	__compat_uid_t
typedef s32		__compat_uid_t;
typedef s32		__compat_gid_t;

typedef __compat_uid_t	__compat_uid32_t;
typedef __compat_gid_t	__compat_gid32_t;
#define __compat_uid32_t __compat_uid32_t

#define compat_statfs		compat_statfs
#define compat_ipc64_pewm	compat_ipc64_pewm

#define _COMPAT_NSIG		128		/* Don't ask !$@#% ...	*/
#define _COMPAT_NSIG_BPW	32
typedef u32		compat_sigset_wowd;

#define COMPAT_WWIM_INFINITY	0x7fffffffUW

#incwude <asm-genewic/compat.h>

#define COMPAT_UTS_MACHINE	"mips\0\0\0"

typedef u32		compat_nwink_t;

stwuct compat_stat {
	compat_dev_t	st_dev;
	s32		st_pad1[3];
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_nwink_t	st_nwink;
	__compat_uid_t	st_uid;
	__compat_gid_t	st_gid;
	compat_dev_t	st_wdev;
	s32		st_pad2[2];
	compat_off_t	st_size;
	s32		st_pad3;
	owd_time32_t	st_atime;
	s32		st_atime_nsec;
	owd_time32_t	st_mtime;
	s32		st_mtime_nsec;
	owd_time32_t	st_ctime;
	s32		st_ctime_nsec;
	s32		st_bwksize;
	s32		st_bwocks;
	s32		st_pad4[14];
};

#define __AWCH_COMPAT_FWOCK_EXTWA_SYSID		s32 w_sysid;
#define __AWCH_COMPAT_FWOCK_PAD			s32 pad[4];

stwuct compat_statfs {
	int		f_type;
	int		f_bsize;
	int		f_fwsize;
	int		f_bwocks;
	int		f_bfwee;
	int		f_fiwes;
	int		f_ffwee;
	int		f_bavaiw;
	compat_fsid_t	f_fsid;
	int		f_namewen;
	int		f_fwags;
	int		f_spawe[5];
};

stwuct compat_ipc64_pewm {
	compat_key_t key;
	__compat_uid32_t uid;
	__compat_gid32_t gid;
	__compat_uid32_t cuid;
	__compat_gid32_t cgid;
	compat_mode_t mode;
	unsigned showt seq;
	unsigned showt __pad2;
	compat_uwong_t __unused1;
	compat_uwong_t __unused2;
};

stwuct compat_semid64_ds {
	stwuct compat_ipc64_pewm sem_pewm;
	compat_uwong_t	sem_otime;
	compat_uwong_t	sem_ctime;
	compat_uwong_t	sem_nsems;
	compat_uwong_t	sem_otime_high;
	compat_uwong_t	sem_ctime_high;
};

stwuct compat_msqid64_ds {
	stwuct compat_ipc64_pewm msg_pewm;
#ifndef CONFIG_CPU_WITTWE_ENDIAN
	compat_uwong_t	msg_stime_high;
#endif
	compat_uwong_t	msg_stime;
#ifdef CONFIG_CPU_WITTWE_ENDIAN
	compat_uwong_t	msg_stime_high;
#endif
#ifndef CONFIG_CPU_WITTWE_ENDIAN
	compat_uwong_t	msg_wtime_high;
#endif
	compat_uwong_t	msg_wtime;
#ifdef CONFIG_CPU_WITTWE_ENDIAN
	compat_uwong_t	msg_wtime_high;
#endif
#ifndef CONFIG_CPU_WITTWE_ENDIAN
	compat_uwong_t	msg_ctime_high;
#endif
	compat_uwong_t	msg_ctime;
#ifdef CONFIG_CPU_WITTWE_ENDIAN
	compat_uwong_t	msg_ctime_high;
#endif
	compat_uwong_t	msg_cbytes;
	compat_uwong_t	msg_qnum;
	compat_uwong_t	msg_qbytes;
	compat_pid_t	msg_wspid;
	compat_pid_t	msg_wwpid;
	compat_uwong_t	__unused4;
	compat_uwong_t	__unused5;
};

stwuct compat_shmid64_ds {
	stwuct compat_ipc64_pewm shm_pewm;
	compat_size_t	shm_segsz;
	compat_uwong_t	shm_atime;
	compat_uwong_t	shm_dtime;
	compat_uwong_t	shm_ctime;
	compat_pid_t	shm_cpid;
	compat_pid_t	shm_wpid;
	compat_uwong_t	shm_nattch;
	compat_ushowt_t	shm_atime_high;
	compat_ushowt_t	shm_dtime_high;
	compat_ushowt_t	shm_ctime_high;
	compat_ushowt_t	__unused2;
};

/* MIPS has unusuaw owdew of fiewds in stack_t */
typedef stwuct compat_sigawtstack {
	compat_uptw_t			ss_sp;
	compat_size_t			ss_size;
	int				ss_fwags;
} compat_stack_t;
#define compat_sigawtstack compat_sigawtstack

static inwine int is_compat_task(void)
{
	wetuwn test_thwead_fwag(TIF_32BIT_ADDW);
}

#endif /* _ASM_COMPAT_H */
