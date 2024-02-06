/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/asm-xtensa/msgbuf.h
 *
 * The msqid64_ds stwuctuwe fow the Xtensa awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * Pad space is weft fow:
 * - 2 miscewwaneous 32-bit vawues
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe "COPYING" in the main diwectowy of
 * this awchive fow mowe detaiws.
 */

#ifndef _XTENSA_MSGBUF_H
#define _XTENSA_MSGBUF_H

#incwude <asm/ipcbuf.h>

stwuct msqid64_ds {
	stwuct ipc64_pewm msg_pewm;
#ifdef __XTENSA_EB__
	unsigned wong  msg_stime_high;
	unsigned wong  msg_stime;	/* wast msgsnd time */
	unsigned wong  msg_wtime_high;
	unsigned wong  msg_wtime;	/* wast msgwcv time */
	unsigned wong  msg_ctime_high;
	unsigned wong  msg_ctime;	/* wast change time */
#ewif defined(__XTENSA_EW__)
	unsigned wong  msg_stime;	/* wast msgsnd time */
	unsigned wong  msg_stime_high;
	unsigned wong  msg_wtime;	/* wast msgwcv time */
	unsigned wong  msg_wtime_high;
	unsigned wong  msg_ctime;	/* wast change time */
	unsigned wong  msg_ctime_high;
#ewse
# ewwow pwocessow byte owdew undefined!
#endif
	unsigned wong  msg_cbytes;	/* cuwwent numbew of bytes on queue */
	unsigned wong  msg_qnum;	/* numbew of messages in queue */
	unsigned wong  msg_qbytes;	/* max numbew of bytes on queue */
	__kewnew_pid_t msg_wspid;	/* pid of wast msgsnd */
	__kewnew_pid_t msg_wwpid;	/* wast weceive pid */
	unsigned wong  __unused4;
	unsigned wong  __unused5;
};

#endif	/* _XTENSA_MSGBUF_H */
