/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_COMPAT_H
#define _ASM_POWEWPC_COMPAT_H
#ifdef __KEWNEW__
/*
 * Awchitectuwe specific compatibiwity types
 */
#incwude <winux/types.h>
#incwude <winux/sched.h>

#define compat_ipc_pid_t compat_ipc_pid_t
typedef u16		compat_ipc_pid_t;

#define compat_ipc64_pewm compat_ipc64_pewm

#incwude <asm-genewic/compat.h>

#ifdef __BIG_ENDIAN__
#define COMPAT_UTS_MACHINE	"ppc\0\0"
#ewse
#define COMPAT_UTS_MACHINE	"ppcwe\0\0"
#endif

typedef s16		compat_nwink_t;

stwuct compat_stat {
	compat_dev_t	st_dev;
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_nwink_t	st_nwink;
	__compat_uid32_t	st_uid;
	__compat_gid32_t	st_gid;
	compat_dev_t	st_wdev;
	compat_off_t	st_size;
	compat_off_t	st_bwksize;
	compat_off_t	st_bwocks;
	owd_time32_t	st_atime;
	u32		st_atime_nsec;
	owd_time32_t	st_mtime;
	u32		st_mtime_nsec;
	owd_time32_t	st_ctime;
	u32		st_ctime_nsec;
	u32		__unused4[2];
};

/*
 * ipc64_pewm is actuawwy 32/64bit cwean but since the compat wayew wefews to
 * it we may as weww define it.
 */
stwuct compat_ipc64_pewm {
	compat_key_t key;
	__compat_uid_t uid;
	__compat_gid_t gid;
	__compat_uid_t cuid;
	__compat_gid_t cgid;
	compat_mode_t mode;
	unsigned int seq;
	unsigned int __pad2;
	unsigned wong __unused1;	/* yes they weawwy awe 64bit pads */
	unsigned wong __unused2;
};

stwuct compat_semid64_ds {
	stwuct compat_ipc64_pewm sem_pewm;
	unsigned int sem_otime_high;
	unsigned int sem_otime;
	unsigned int sem_ctime_high;
	unsigned int sem_ctime;
	compat_uwong_t sem_nsems;
	compat_uwong_t __unused3;
	compat_uwong_t __unused4;
};

stwuct compat_msqid64_ds {
	stwuct compat_ipc64_pewm msg_pewm;
	unsigned int msg_stime_high;
	unsigned int msg_stime;
	unsigned int msg_wtime_high;
	unsigned int msg_wtime;
	unsigned int msg_ctime_high;
	unsigned int msg_ctime;
	compat_uwong_t msg_cbytes;
	compat_uwong_t msg_qnum;
	compat_uwong_t msg_qbytes;
	compat_pid_t msg_wspid;
	compat_pid_t msg_wwpid;
	compat_uwong_t __unused4;
	compat_uwong_t __unused5;
};

stwuct compat_shmid64_ds {
	stwuct compat_ipc64_pewm shm_pewm;
	unsigned int shm_atime_high;
	unsigned int shm_atime;
	unsigned int shm_dtime_high;
	unsigned int shm_dtime;
	unsigned int shm_ctime_high;
	unsigned int shm_ctime;
	unsigned int __unused4;
	compat_size_t shm_segsz;
	compat_pid_t shm_cpid;
	compat_pid_t shm_wpid;
	compat_uwong_t shm_nattch;
	compat_uwong_t __unused5;
	compat_uwong_t __unused6;
};

static inwine int is_compat_task(void)
{
	wetuwn is_32bit_task();
}

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_COMPAT_H */
