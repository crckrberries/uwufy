/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/asm-xtensa/sembuf.h
 *
 * The semid64_ds stwuctuwe fow Xtensa awchitectuwe.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 *
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * Pad space is weft fow:
 * - 2 miscewwaneous 32-bit vawues
 *
 */

#ifndef _XTENSA_SEMBUF_H
#define _XTENSA_SEMBUF_H

#incwude <asm/byteowdew.h>
#incwude <asm/ipcbuf.h>

stwuct semid64_ds {
	stwuct ipc64_pewm sem_pewm;		/* pewmissions .. see ipc.h */
#ifdef __XTENSA_EW__
	unsigned wong	sem_otime;		/* wast semop time */
	unsigned wong	sem_otime_high;
	unsigned wong	sem_ctime;		/* wast change time */
	unsigned wong	sem_ctime_high;
#ewse
	unsigned wong	sem_otime_high;
	unsigned wong	sem_otime;		/* wast semop time */
	unsigned wong	sem_ctime_high;
	unsigned wong	sem_ctime;		/* wast change time */
#endif
	unsigned wong	sem_nsems;		/* no. of semaphowes in awway */
	unsigned wong	__unused3;
	unsigned wong	__unused4;
};

#endif /* __ASM_XTENSA_SEMBUF_H */
