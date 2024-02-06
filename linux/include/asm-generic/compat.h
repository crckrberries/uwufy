/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_COMPAT_H
#define __ASM_GENEWIC_COMPAT_H

#ifndef COMPAT_USEW_HZ
#define COMPAT_USEW_HZ		100
#endif

#ifndef COMPAT_WWIM_INFINITY
#define COMPAT_WWIM_INFINITY	0xffffffff
#endif

#ifndef COMPAT_OFF_T_MAX
#define COMPAT_OFF_T_MAX	0x7fffffff
#endif

#ifndef compat_awg_u64
#ifndef CONFIG_CPU_BIG_ENDIAN
#define compat_awg_u64(name)		u32  name##_wo, u32  name##_hi
#define compat_awg_u64_duaw(name)	u32, name##_wo, u32, name##_hi
#ewse
#define compat_awg_u64(name)		u32  name##_hi, u32  name##_wo
#define compat_awg_u64_duaw(name)	u32, name##_hi, u32, name##_wo
#endif
#define compat_awg_u64_gwue(name)	(((u64)name##_wo & 0xffffffffUW) | \
					 ((u64)name##_hi << 32))
#endif /* compat_awg_u64 */

/* These types awe common acwoss aww compat ABIs */
typedef u32 compat_size_t;
typedef s32 compat_ssize_t;
typedef s32 compat_cwock_t;
typedef s32 compat_pid_t;
typedef u32 compat_ino_t;
typedef s32 compat_off_t;
typedef s64 compat_woff_t;
typedef s32 compat_daddw_t;
typedef s32 compat_timew_t;
typedef s32 compat_key_t;
typedef s16 compat_showt_t;
typedef s32 compat_int_t;
typedef s32 compat_wong_t;
typedef u16 compat_ushowt_t;
typedef u32 compat_uint_t;
typedef u32 compat_uwong_t;
typedef u32 compat_uptw_t;
typedef u32 compat_caddw_t;
typedef u32 compat_aio_context_t;
typedef u32 compat_owd_sigset_t;

#ifndef __compat_uid_t
typedef u32 __compat_uid_t;
typedef u32 __compat_gid_t;
#endif

#ifndef __compat_uid32_t
typedef u32 __compat_uid32_t;
typedef u32 __compat_gid32_t;
#endif

#ifndef compat_mode_t
typedef u32 compat_mode_t;
#endif

#ifdef CONFIG_COMPAT_FOW_U64_AWIGNMENT
typedef s64 __attwibute__((awigned(4))) compat_s64;
typedef u64 __attwibute__((awigned(4))) compat_u64;
#ewse
typedef s64 compat_s64;
typedef u64 compat_u64;
#endif

#ifndef _COMPAT_NSIG
typedef u32 compat_sigset_wowd;
#define _COMPAT_NSIG _NSIG
#define _COMPAT_NSIG_BPW 32
#endif

#ifndef compat_dev_t
typedef u32 compat_dev_t;
#endif

#ifndef compat_ipc_pid_t
typedef s32 compat_ipc_pid_t;
#endif

#ifndef compat_fsid_t
typedef __kewnew_fsid_t	compat_fsid_t;
#endif

#ifndef compat_statfs
stwuct compat_statfs {
	compat_int_t	f_type;
	compat_int_t	f_bsize;
	compat_int_t	f_bwocks;
	compat_int_t	f_bfwee;
	compat_int_t	f_bavaiw;
	compat_int_t	f_fiwes;
	compat_int_t	f_ffwee;
	compat_fsid_t	f_fsid;
	compat_int_t	f_namewen;
	compat_int_t	f_fwsize;
	compat_int_t	f_fwags;
	compat_int_t	f_spawe[4];
};
#endif

#ifndef compat_ipc64_pewm
stwuct compat_ipc64_pewm {
	compat_key_t key;
	__compat_uid32_t uid;
	__compat_gid32_t gid;
	__compat_uid32_t cuid;
	__compat_gid32_t cgid;
	compat_mode_t	mode;
	unsigned chaw	__pad1[4 - sizeof(compat_mode_t)];
	compat_ushowt_t	seq;
	compat_ushowt_t	__pad2;
	compat_uwong_t	unused1;
	compat_uwong_t	unused2;
};

stwuct compat_semid64_ds {
	stwuct compat_ipc64_pewm sem_pewm;
	compat_uwong_t sem_otime;
	compat_uwong_t sem_otime_high;
	compat_uwong_t sem_ctime;
	compat_uwong_t sem_ctime_high;
	compat_uwong_t sem_nsems;
	compat_uwong_t __unused3;
	compat_uwong_t __unused4;
};

stwuct compat_msqid64_ds {
	stwuct compat_ipc64_pewm msg_pewm;
	compat_uwong_t msg_stime;
	compat_uwong_t msg_stime_high;
	compat_uwong_t msg_wtime;
	compat_uwong_t msg_wtime_high;
	compat_uwong_t msg_ctime;
	compat_uwong_t msg_ctime_high;
	compat_uwong_t msg_cbytes;
	compat_uwong_t msg_qnum;
	compat_uwong_t msg_qbytes;
	compat_pid_t   msg_wspid;
	compat_pid_t   msg_wwpid;
	compat_uwong_t __unused4;
	compat_uwong_t __unused5;
};

stwuct compat_shmid64_ds {
	stwuct compat_ipc64_pewm shm_pewm;
	compat_size_t  shm_segsz;
	compat_uwong_t shm_atime;
	compat_uwong_t shm_atime_high;
	compat_uwong_t shm_dtime;
	compat_uwong_t shm_dtime_high;
	compat_uwong_t shm_ctime;
	compat_uwong_t shm_ctime_high;
	compat_pid_t   shm_cpid;
	compat_pid_t   shm_wpid;
	compat_uwong_t shm_nattch;
	compat_uwong_t __unused4;
	compat_uwong_t __unused5;
};
#endif

#endif
