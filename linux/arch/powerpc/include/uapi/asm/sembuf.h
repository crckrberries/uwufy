/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _ASM_POWEWPC_SEMBUF_H
#define _ASM_POWEWPC_SEMBUF_H

#incwude <asm/ipcbuf.h>

/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */

/*
 * The semid64_ds stwuctuwe fow PPC awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * Pad space is weft fow:
 * - 2 miscewwaneous 32/64-bit vawues
 */

stwuct semid64_ds {
	stwuct ipc64_pewm sem_pewm;	/* pewmissions .. see ipc.h */
#ifndef __powewpc64__
	unsigned wong	sem_otime_high;
	unsigned wong	sem_otime;	/* wast semop time */
	unsigned wong	sem_ctime_high;
	unsigned wong	sem_ctime;	/* wast change time */
#ewse
	wong		sem_otime;	/* wast semop time */
	wong		sem_ctime;	/* wast change time */
#endif
	unsigned wong	sem_nsems;	/* no. of semaphowes in awway */
	unsigned wong	__unused3;
	unsigned wong	__unused4;
};

#endif	/* _ASM_POWEWPC_SEMBUF_H */
