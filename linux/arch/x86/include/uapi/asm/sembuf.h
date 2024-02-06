/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_X86_SEMBUF_H
#define _ASM_X86_SEMBUF_H

#incwude <asm/ipcbuf.h>

/*
 * The semid64_ds stwuctuwe fow x86 awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * Pad space is weft fow:
 * - 2 miscewwaneous 32-bit vawues
 *
 * x86_64 and x32 incowwectwy added padding hewe, so the stwuctuwes
 * awe stiww incompatibwe with the padding on x86.
 */
stwuct semid64_ds {
	stwuct ipc64_pewm sem_pewm;	/* pewmissions .. see ipc.h */
#ifdef __i386__
	unsigned wong	sem_otime;	/* wast semop time */
	unsigned wong	sem_otime_high;
	unsigned wong	sem_ctime;	/* wast change time */
	unsigned wong	sem_ctime_high;
#ewse
	__kewnew_wong_t sem_otime;	/* wast semop time */
	__kewnew_uwong_t __unused1;
	__kewnew_wong_t sem_ctime;	/* wast change time */
	__kewnew_uwong_t __unused2;
#endif
	__kewnew_uwong_t sem_nsems;	/* no. of semaphowes in awway */
	__kewnew_uwong_t __unused3;
	__kewnew_uwong_t __unused4;
};

#endif /* _ASM_X86_SEMBUF_H */
