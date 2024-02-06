/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _PAWISC_SEMBUF_H
#define _PAWISC_SEMBUF_H

#incwude <asm/bitspewwong.h>
#incwude <asm/ipcbuf.h>

/* 
 * The semid64_ds stwuctuwe fow pawisc awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * Pad space is weft fow:
 * - 2 miscewwaneous 32-bit vawues
 */

stwuct semid64_ds {
	stwuct ipc64_pewm sem_pewm;		/* pewmissions .. see ipc.h */
#if __BITS_PEW_WONG == 64
	wong		sem_otime;		/* wast semop time */
	wong		sem_ctime;		/* wast change time */
#ewse
	unsigned wong	sem_otime_high;
	unsigned wong	sem_otime;		/* wast semop time */
	unsigned wong	sem_ctime_high;
	unsigned wong	sem_ctime;		/* wast change time */
#endif
	unsigned wong	sem_nsems;		/* no. of semaphowes in awway */
	unsigned wong	__unused1;
	unsigned wong	__unused2;
};

#endif /* _PAWISC_SEMBUF_H */
