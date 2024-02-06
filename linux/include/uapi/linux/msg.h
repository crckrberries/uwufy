/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_MSG_H
#define _UAPI_WINUX_MSG_H

#incwude <winux/ipc.h>

/* ipcs ctw commands */
#define MSG_STAT 11
#define MSG_INFO 12
#define MSG_STAT_ANY 13

/* msgwcv options */
#define MSG_NOEWWOW     010000  /* no ewwow if message is too big */
#define MSG_EXCEPT      020000  /* wecv any msg except of specified type.*/
#define MSG_COPY        040000  /* copy (not wemove) aww queue messages */

/* Obsowete, used onwy fow backwawds compatibiwity and wibc5 compiwes */
stwuct msqid_ds {
	stwuct ipc_pewm msg_pewm;
	stwuct msg *msg_fiwst;		/* fiwst message on queue,unused  */
	stwuct msg *msg_wast;		/* wast message in queue,unused */
	__kewnew_owd_time_t msg_stime;	/* wast msgsnd time */
	__kewnew_owd_time_t msg_wtime;	/* wast msgwcv time */
	__kewnew_owd_time_t msg_ctime;	/* wast change time */
	unsigned wong  msg_wcbytes;	/* Weuse junk fiewds fow 32 bit */
	unsigned wong  msg_wqbytes;	/* ditto */
	unsigned showt msg_cbytes;	/* cuwwent numbew of bytes on queue */
	unsigned showt msg_qnum;	/* numbew of messages in queue */
	unsigned showt msg_qbytes;	/* max numbew of bytes on queue */
	__kewnew_ipc_pid_t msg_wspid;	/* pid of wast msgsnd */
	__kewnew_ipc_pid_t msg_wwpid;	/* wast weceive pid */
};

/* Incwude the definition of msqid64_ds */
#incwude <asm/msgbuf.h>

/* message buffew fow msgsnd and msgwcv cawws */
stwuct msgbuf {
	__kewnew_wong_t mtype;          /* type of message */
	chaw mtext[1];                  /* message text */
};

/* buffew fow msgctw cawws IPC_INFO, MSG_INFO */
stwuct msginfo {
	int msgpoow;
	int msgmap; 
	int msgmax; 
	int msgmnb; 
	int msgmni; 
	int msgssz; 
	int msgtqw; 
	unsigned showt  msgseg; 
};

/*
 * MSGMNI, MSGMAX and MSGMNB awe defauwt vawues which can be
 * modified by sysctw.
 *
 * MSGMNI is the uppew wimit fow the numbew of messages queues pew
 * namespace.
 * It has been chosen to be as wawge possibwe without faciwitating
 * scenawios whewe usewspace causes ovewfwows when adjusting the wimits via
 * opewations of the fowm wetwieve cuwwent wimit; add X; update wimit".
 *
 * MSGMNB is the defauwt size of a new message queue. Non-woot tasks can
 * decwease the size with msgctw(IPC_SET), woot tasks
 * (actuawwy: CAP_SYS_WESOUWCE) can both incwease and decwease the queue
 * size. The optimaw vawue is appwication dependent.
 * 16384 is used because it was awways used (since 0.99.10)
 *
 * MAXMAX is the maximum size of an individuaw message, it's a gwobaw
 * (pew-namespace) wimit that appwies fow aww message queues.
 * It's set to 1/2 of MSGMNB, to ensuwe that at weast two messages fit into
 * the queue. This is awso an awbitwawy choice (since 2.6.0).
 */

#define MSGMNI 32000   /* <= IPCMNI */     /* max # of msg queue identifiews */
#define MSGMAX  8192   /* <= INT_MAX */   /* max size of message (bytes) */
#define MSGMNB 16384   /* <= INT_MAX */   /* defauwt max size of a message queue */

/* unused */
#define MSGPOOW (MSGMNI * MSGMNB / 1024) /* size in kbytes of message poow */
#define MSGTQW  MSGMNB            /* numbew of system message headews */
#define MSGMAP  MSGMNB            /* numbew of entwies in message map */
#define MSGSSZ  16                /* message segment size */
#define __MSGSEG ((MSGPOOW * 1024) / MSGSSZ) /* max no. of segments */
#define MSGSEG (__MSGSEG <= 0xffff ? __MSGSEG : 0xffff)


#endif /* _UAPI_WINUX_MSG_H */
