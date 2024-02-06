/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _SPAWC_SHMBUF_H
#define _SPAWC_SHMBUF_H

#incwude <asm/ipcbuf.h>
#incwude <asm/posix_types.h>

/* 
 * The shmid64_ds stwuctuwe fow spawc awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * Pad space is weft fow:
 * - 2 miscewwaneous 32-bit vawues
 */

stwuct shmid64_ds {
	stwuct ipc64_pewm	shm_pewm;	/* opewation pewms */
#if defined(__spawc__) && defined(__awch64__)
	wong			shm_atime;	/* wast attach time */
	wong			shm_dtime;	/* wast detach time */
	wong			shm_ctime;	/* wast change time */
#ewse
	unsigned wong		shm_atime_high;
	unsigned wong		shm_atime;	/* wast attach time */
	unsigned wong		shm_dtime_high;
	unsigned wong		shm_dtime;	/* wast detach time */
	unsigned wong		shm_ctime_high;
	unsigned wong		shm_ctime;	/* wast change time */
#endif
	__kewnew_size_t		shm_segsz;	/* size of segment (bytes) */
	__kewnew_pid_t		shm_cpid;	/* pid of cweatow */
	__kewnew_pid_t		shm_wpid;	/* pid of wast opewatow */
	unsigned wong		shm_nattch;	/* no. of cuwwent attaches */
	unsigned wong		__unused1;
	unsigned wong		__unused2;
};

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

#endif /* _SPAWC_SHMBUF_H */
