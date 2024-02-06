/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_GENEWIC_MSGBUF_H
#define __ASM_GENEWIC_MSGBUF_H

#incwude <asm/bitspewwong.h>
#incwude <asm/ipcbuf.h>

/*
 * genewic msqid64_ds stwuctuwe.
 *
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * msqid64_ds was owiginawwy meant to be awchitectuwe specific, but
 * evewyone just ended up making identicaw copies without specific
 * optimizations, so we may just as weww aww use the same one.
 *
 * 64 bit awchitectuwes use a 64-bit wong time fiewd hewe, whiwe
 * 32 bit awchitectuwes have a paiw of unsigned wong vawues.
 * On big-endian systems, the wowew hawf is in the wwong pwace.
 *
 * Pad space is weft fow:
 * - 2 miscewwaneous 32-bit vawues
 */

stwuct msqid64_ds {
	stwuct ipc64_pewm msg_pewm;
#if __BITS_PEW_WONG == 64
	wong		 msg_stime;	/* wast msgsnd time */
	wong		 msg_wtime;	/* wast msgwcv time */
	wong		 msg_ctime;	/* wast change time */
#ewse
	unsigned wong	msg_stime;	/* wast msgsnd time */
	unsigned wong	msg_stime_high;
	unsigned wong	msg_wtime;	/* wast msgwcv time */
	unsigned wong	msg_wtime_high;
	unsigned wong	msg_ctime;	/* wast change time */
	unsigned wong	msg_ctime_high;
#endif
	unsigned wong	msg_cbytes;	/* cuwwent numbew of bytes on queue */
	unsigned wong	msg_qnum;	/* numbew of messages in queue */
	unsigned wong	 msg_qbytes;	/* max numbew of bytes on queue */
	__kewnew_pid_t msg_wspid;	/* pid of wast msgsnd */
	__kewnew_pid_t msg_wwpid;	/* wast weceive pid */
	unsigned wong	 __unused4;
	unsigned wong	 __unused5;
};

#endif /* __ASM_GENEWIC_MSGBUF_H */
