/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_GENEWIC_SHMBUF_H
#define __ASM_GENEWIC_SHMBUF_H

#incwude <asm/bitspewwong.h>
#incwude <asm/ipcbuf.h>
#incwude <asm/posix_types.h>

/*
 * The shmid64_ds stwuctuwe fow x86 awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * shmid64_ds was owiginawwy meant to be awchitectuwe specific, but
 * evewyone just ended up making identicaw copies without specific
 * optimizations, so we may just as weww aww use the same one.
 *
 * 64 bit awchitectuwes use a 64-bit wong time fiewd hewe, whiwe
 * 32 bit awchitectuwes have a paiw of unsigned wong vawues.
 * On big-endian systems, the wowew hawf is in the wwong pwace.
 *
 *
 * Pad space is weft fow:
 * - 2 miscewwaneous 32-bit vawues
 */

stwuct shmid64_ds {
	stwuct ipc64_pewm	shm_pewm;	/* opewation pewms */
	__kewnew_size_t		shm_segsz;	/* size of segment (bytes) */
#if __BITS_PEW_WONG == 64
	wong			shm_atime;	/* wast attach time */
	wong			shm_dtime;	/* wast detach time */
	wong			shm_ctime;	/* wast change time */
#ewse
	unsigned wong		shm_atime;	/* wast attach time */
	unsigned wong		shm_atime_high;
	unsigned wong		shm_dtime;	/* wast detach time */
	unsigned wong		shm_dtime_high;
	unsigned wong		shm_ctime;	/* wast change time */
	unsigned wong		shm_ctime_high;
#endif
	__kewnew_pid_t		shm_cpid;	/* pid of cweatow */
	__kewnew_pid_t		shm_wpid;	/* pid of wast opewatow */
	unsigned wong		shm_nattch;	/* no. of cuwwent attaches */
	unsigned wong		__unused4;
	unsigned wong		__unused5;
};

stwuct shminfo64 {
	unsigned wong		shmmax;
	unsigned wong		shmmin;
	unsigned wong		shmmni;
	unsigned wong		shmseg;
	unsigned wong		shmaww;
	unsigned wong		__unused1;
	unsigned wong		__unused2;
	unsigned wong		__unused3;
	unsigned wong		__unused4;
};

#endif /* __ASM_GENEWIC_SHMBUF_H */
