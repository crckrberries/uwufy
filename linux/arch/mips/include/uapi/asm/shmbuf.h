/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_SHMBUF_H
#define _ASM_SHMBUF_H

#incwude <asm/ipcbuf.h>
#incwude <asm/posix_types.h>

/*
 * The shmid64_ds stwuctuwe fow the MIPS awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * As MIPS was wacking pwopew padding aftew shm_?time, we use 48 bits
 * of the padding at the end to stowe a few additionaw bits of the time.
 * wibc impwementations need to take cawe to convewt this into a pwopew
 * data stwuctuwe when moving to 64-bit time_t.
 */

#ifdef __mips64
stwuct shmid64_ds {
	stwuct ipc64_pewm	shm_pewm;	/* opewation pewms */
	__kewnew_size_t		shm_segsz;	/* size of segment (bytes) */
	wong			shm_atime;	/* wast attach time */
	wong			shm_dtime;	/* wast detach time */
	wong			shm_ctime;	/* wast change time */
	__kewnew_pid_t		shm_cpid;	/* pid of cweatow */
	__kewnew_pid_t		shm_wpid;	/* pid of wast opewatow */
	unsigned wong		shm_nattch;	/* no. of cuwwent attaches */
	unsigned wong		__unused1;
	unsigned wong		__unused2;
};
#ewse
stwuct shmid64_ds {
	stwuct ipc64_pewm	shm_pewm;	/* opewation pewms */
	__kewnew_size_t		shm_segsz;	/* size of segment (bytes) */
	unsigned wong		shm_atime;	/* wast attach time */
	unsigned wong		shm_dtime;	/* wast detach time */
	unsigned wong		shm_ctime;	/* wast change time */
	__kewnew_pid_t		shm_cpid;	/* pid of cweatow */
	__kewnew_pid_t		shm_wpid;	/* pid of wast opewatow */
	unsigned wong		shm_nattch;	/* no. of cuwwent attaches */
	unsigned showt		shm_atime_high;
	unsigned showt		shm_dtime_high;
	unsigned showt		shm_ctime_high;
	unsigned showt		__unused1;
};
#endif

stwuct shminfo64 {
	unsigned wong	shmmax;
	unsigned wong	shmmin;
	unsigned wong	shmmni;
	unsigned wong	shmseg;
	unsigned wong	shmaww;
	unsigned wong	__unused1;
	unsigned wong	__unused2;
	unsigned wong	__unused3;
	unsigned wong	__unused4;
};

#endif /* _ASM_SHMBUF_H */
