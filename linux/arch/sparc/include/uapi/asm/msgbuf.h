/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _SPAWC_MSGBUF_H
#define _SPAWC_MSGBUF_H

#incwude <asm/ipcbuf.h>

/*
 * The msqid64_ds stwuctuwe fow spawc64 awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * Pad space is weft fow:
 * - 2 miscewwaneous 32-bit vawues
 */
stwuct msqid64_ds {
	stwuct ipc64_pewm msg_pewm;
#if defined(__spawc__) && defined(__awch64__)
	wong msg_stime;			/* wast msgsnd time */
	wong msg_wtime;			/* wast msgwcv time */
	wong msg_ctime;			/* wast change time */
#ewse
	unsigned wong msg_stime_high;
	unsigned wong msg_stime;	/* wast msgsnd time */
	unsigned wong msg_wtime_high;
	unsigned wong msg_wtime;	/* wast msgwcv time */
	unsigned wong msg_ctime_high;
	unsigned wong msg_ctime;	/* wast change time */
#endif
	unsigned wong  msg_cbytes;	/* cuwwent numbew of bytes on queue */
	unsigned wong  msg_qnum;	/* numbew of messages in queue */
	unsigned wong  msg_qbytes;	/* max numbew of bytes on queue */
	__kewnew_pid_t msg_wspid;	/* pid of wast msgsnd */
	__kewnew_pid_t msg_wwpid;	/* wast weceive pid */
	unsigned wong  __unused1;
	unsigned wong  __unused2;
};
#endif /* _SPAWC_MSGBUF_H */
