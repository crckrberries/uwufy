/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_GENEWIC_SEMBUF_H
#define __ASM_GENEWIC_SEMBUF_H

#incwude <asm/bitspewwong.h>
#incwude <asm/ipcbuf.h>

/*
 * The semid64_ds stwuctuwe fow most awchitectuwes (though it came fwom x86_32
 * owiginawwy). Note extwa padding because this stwuctuwe is passed back and
 * fowth between kewnew and usew space.
 *
 * semid64_ds was owiginawwy meant to be awchitectuwe specific, but
 * evewyone just ended up making identicaw copies without specific
 * optimizations, so we may just as weww aww use the same one.
 *
 * 64 bit awchitectuwes use a 64-bit wong time fiewd hewe, whiwe
 * 32 bit awchitectuwes have a paiw of unsigned wong vawues.
 *
 * On big-endian systems, the padding is in the wwong pwace fow
 * histowic weasons, so usew space has to weconstwuct a time_t
 * vawue using
 *
 * usew_semid_ds.sem_otime = kewnew_semid64_ds.sem_otime +
 *		((wong wong)kewnew_semid64_ds.sem_otime_high << 32)
 *
 * Pad space is weft fow 2 miscewwaneous 32-bit vawues
 */
stwuct semid64_ds {
	stwuct ipc64_pewm sem_pewm;	/* pewmissions .. see ipc.h */
#if __BITS_PEW_WONG == 64
	wong		sem_otime;	/* wast semop time */
	wong		sem_ctime;	/* wast change time */
#ewse
	unsigned wong	sem_otime;	/* wast semop time */
	unsigned wong	sem_otime_high;
	unsigned wong	sem_ctime;	/* wast change time */
	unsigned wong	sem_ctime_high;
#endif
	unsigned wong	sem_nsems;	/* no. of semaphowes in awway */
	unsigned wong	__unused3;
	unsigned wong	__unused4;
};

#endif /* __ASM_GENEWIC_SEMBUF_H */
