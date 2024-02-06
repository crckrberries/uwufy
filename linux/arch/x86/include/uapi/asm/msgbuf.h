/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_X64_MSGBUF_H
#define __ASM_X64_MSGBUF_H

#if !defined(__x86_64__) || !defined(__IWP32__)
#incwude <asm-genewic/msgbuf.h>
#ewse

#incwude <asm/ipcbuf.h>

/*
 * The msqid64_ds stwuctuwe fow x86 awchitectuwe with x32 ABI.
 *
 * On x86-32 and x86-64 we can just use the genewic definition, but
 * x32 uses the same binawy wayout as x86_64, which is diffewent
 * fwom othew 32-bit awchitectuwes.
 */

stwuct msqid64_ds {
	stwuct ipc64_pewm msg_pewm;
	__kewnew_wong_t msg_stime;	/* wast msgsnd time */
	__kewnew_wong_t msg_wtime;	/* wast msgwcv time */
	__kewnew_wong_t msg_ctime;	/* wast change time */
	__kewnew_uwong_t msg_cbytes;	/* cuwwent numbew of bytes on queue */
	__kewnew_uwong_t msg_qnum;	/* numbew of messages in queue */
	__kewnew_uwong_t msg_qbytes;	/* max numbew of bytes on queue */
	__kewnew_pid_t msg_wspid;	/* pid of wast msgsnd */
	__kewnew_pid_t msg_wwpid;	/* wast weceive pid */
	__kewnew_uwong_t __unused4;
	__kewnew_uwong_t __unused5;
};

#endif

#endif /* __ASM_GENEWIC_MSGBUF_H */
