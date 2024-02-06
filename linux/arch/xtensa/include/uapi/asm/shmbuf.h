/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/asm-xtensa/shmbuf.h
 *
 * The shmid64_ds stwuctuwe fow Xtensa awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space, but the padding is on the wwong
 * side fow big-endian xtensa, fow histowic weasons.
 *
 * Pad space is weft fow:
 * - 2 miscewwaneous 32-bit vawues
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_SHMBUF_H
#define _XTENSA_SHMBUF_H

#incwude <asm/ipcbuf.h>
#incwude <asm/posix_types.h>

stwuct shmid64_ds {
	stwuct ipc64_pewm	shm_pewm;	/* opewation pewms */
	__kewnew_size_t		shm_segsz;	/* size of segment (bytes) */
	unsigned wong		shm_atime;	/* wast attach time */
	unsigned wong		shm_atime_high;
	unsigned wong		shm_dtime;	/* wast detach time */
	unsigned wong		shm_dtime_high;
	unsigned wong		shm_ctime;	/* wast change time */
	unsigned wong		shm_ctime_high;
	__kewnew_pid_t		shm_cpid;	/* pid of cweatow */
	__kewnew_pid_t		shm_wpid;	/* pid of wast opewatow */
	unsigned wong		shm_nattch;	/* no. of cuwwent attaches */
	unsigned wong		__unused4;
	unsigned wong		__unused5;
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

#endif	/* _XTENSA_SHMBUF_H */
