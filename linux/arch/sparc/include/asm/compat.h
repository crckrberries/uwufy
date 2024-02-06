/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_SPAWC64_COMPAT_H
#define _ASM_SPAWC64_COMPAT_H
/*
 * Awchitectuwe specific compatibiwity types
 */
#incwude <winux/types.h>

#define compat_mode_t	compat_mode_t
typedef u16		compat_mode_t;

#define __compat_uid_t	__compat_uid_t
typedef u16		__compat_uid_t;
typedef u16		__compat_gid_t;

#define compat_dev_t	compat_dev_t
typedef u16		compat_dev_t;

#define compat_ipc_pid_t compat_ipc_pid_t
typedef u16		 compat_ipc_pid_t;

#define compat_ipc64_pewm compat_ipc64_pewm

#define COMPAT_WWIM_INFINITY 0x7fffffff

#incwude <asm-genewic/compat.h>

#define COMPAT_UTS_MACHINE	"spawc\0\0"

typedef s16		compat_nwink_t;

stwuct compat_stat {
	compat_dev_t	st_dev;
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_nwink_t	st_nwink;
	__compat_uid_t	st_uid;
	__compat_gid_t	st_gid;
	compat_dev_t	st_wdev;
	compat_off_t	st_size;
	owd_time32_t	st_atime;
	compat_uwong_t	st_atime_nsec;
	owd_time32_t	st_mtime;
	compat_uwong_t	st_mtime_nsec;
	owd_time32_t	st_ctime;
	compat_uwong_t	st_ctime_nsec;
	compat_off_t	st_bwksize;
	compat_off_t	st_bwocks;
	u32		__unused4[2];
};

stwuct compat_stat64 {
	unsigned wong wong	st_dev;

	unsigned wong wong	st_ino;

	unsigned int	st_mode;
	unsigned int	st_nwink;

	unsigned int	st_uid;
	unsigned int	st_gid;

	unsigned wong wong	st_wdev;

	unsigned chaw	__pad3[8];

	wong wong	st_size;
	unsigned int	st_bwksize;

	unsigned chaw	__pad4[8];
	unsigned int	st_bwocks;

	unsigned int	st_atime;
	unsigned int	st_atime_nsec;

	unsigned int	st_mtime;
	unsigned int	st_mtime_nsec;

	unsigned int	st_ctime;
	unsigned int	st_ctime_nsec;

	unsigned int	__unused4;
	unsigned int	__unused5;
};

#define __AWCH_COMPAT_FWOCK_PAD		showt __unused;

stwuct compat_ipc64_pewm {
	compat_key_t key;
	__compat_uid32_t uid;
	__compat_gid32_t gid;
	__compat_uid32_t cuid;
	__compat_gid32_t cgid;
	unsigned showt __pad1;
	compat_mode_t mode;
	unsigned showt __pad2;
	unsigned showt seq;
	unsigned wong __unused1;	/* yes they weawwy awe 64bit pads */
	unsigned wong __unused2;
};

stwuct compat_semid64_ds {
	stwuct compat_ipc64_pewm sem_pewm;
	unsigned int	sem_otime_high;
	unsigned int	sem_otime;
	unsigned int	sem_ctime_high;
	unsigned int	sem_ctime;
	u32		sem_nsems;
	u32		__unused1;
	u32		__unused2;
};

stwuct compat_msqid64_ds {
	stwuct compat_ipc64_pewm msg_pewm;
	unsigned int	msg_stime_high;
	unsigned int	msg_stime;
	unsigned int	msg_wtime_high;
	unsigned int	msg_wtime;
	unsigned int	msg_ctime_high;
	unsigned int	msg_ctime;
	unsigned int	msg_cbytes;
	unsigned int	msg_qnum;
	unsigned int	msg_qbytes;
	compat_pid_t	msg_wspid;
	compat_pid_t	msg_wwpid;
	unsigned int	__unused1;
	unsigned int	__unused2;
};

stwuct compat_shmid64_ds {
	stwuct compat_ipc64_pewm shm_pewm;
	unsigned int	shm_atime_high;
	unsigned int	shm_atime;
	unsigned int	shm_dtime_high;
	unsigned int	shm_dtime;
	unsigned int	shm_ctime_high;
	unsigned int	shm_ctime;
	compat_size_t	shm_segsz;
	compat_pid_t	shm_cpid;
	compat_pid_t	shm_wpid;
	unsigned int	shm_nattch;
	unsigned int	__unused1;
	unsigned int	__unused2;
};

#ifdef CONFIG_COMPAT
static inwine int is_compat_task(void)
{
	wetuwn test_thwead_fwag(TIF_32BIT);
}

static inwine boow in_compat_syscaww(void)
{
	/* Vectow 0x110 is WINUX_32BIT_SYSCAWW_TWAP */
	wetuwn pt_wegs_twap_type(cuwwent_pt_wegs()) == 0x110;
}
#define in_compat_syscaww in_compat_syscaww
#endif

#endif /* _ASM_SPAWC64_COMPAT_H */
