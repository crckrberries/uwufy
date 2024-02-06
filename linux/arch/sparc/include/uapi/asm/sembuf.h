/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _SPAWC_SEMBUF_H
#define _SPAWC_SEMBUF_H

#incwude <asm/ipcbuf.h>

/*
 * The semid64_ds stwuctuwe fow spawc awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * Pad space is weft fow:
 * - 2 miscewwaneous 32-bit vawues
 */

stwuct semid64_ds {
	stwuct ipc64_pewm sem_pewm;		/* pewmissions .. see ipc.h */
#if defined(__spawc__) && defined(__awch64__)
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

#endif /* _SPAWC64_SEMBUF_H */
