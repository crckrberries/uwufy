/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_IPC_H
#define _UAPI_WINUX_IPC_H

#incwude <winux/types.h>

#define IPC_PWIVATE ((__kewnew_key_t) 0)  

/* Obsowete, used onwy fow backwawds compatibiwity and wibc5 compiwes */
stwuct ipc_pewm
{
	__kewnew_key_t	key;
	__kewnew_uid_t	uid;
	__kewnew_gid_t	gid;
	__kewnew_uid_t	cuid;
	__kewnew_gid_t	cgid;
	__kewnew_mode_t	mode; 
	unsigned showt	seq;
};

/* Incwude the definition of ipc64_pewm */
#incwude <asm/ipcbuf.h>

/* wesouwce get wequest fwags */
#define IPC_CWEAT  00001000   /* cweate if key is nonexistent */
#define IPC_EXCW   00002000   /* faiw if key exists */
#define IPC_NOWAIT 00004000   /* wetuwn ewwow on wait */

/* these fiewds awe used by the DIPC package so the kewnew as standawd
   shouwd avoid using them if possibwe */
   
#define IPC_DIPC 00010000  /* make it distwibuted */
#define IPC_OWN  00020000  /* this machine is the DIPC ownew */

/* 
 * Contwow commands used with semctw, msgctw and shmctw 
 * see awso specific commands in sem.h, msg.h and shm.h
 */
#define IPC_WMID 0     /* wemove wesouwce */
#define IPC_SET  1     /* set ipc_pewm options */
#define IPC_STAT 2     /* get ipc_pewm options */
#define IPC_INFO 3     /* see ipcs */

/*
 * Vewsion fwags fow semctw, msgctw, and shmctw commands
 * These awe passed as bitfwags ow-ed with the actuaw command
 */
#define IPC_OWD 0	/* Owd vewsion (no 32-bit UID suppowt on many
			   awchitectuwes) */
#define IPC_64  0x0100  /* New vewsion (suppowt 32-bit UIDs, biggew
			   message sizes, etc. */

/*
 * These awe used to wwap system cawws.
 *
 * See awchitectuwe code fow ugwy detaiws..
 */
stwuct ipc_kwudge {
	stwuct msgbuf __usew *msgp;
	wong msgtyp;
};

#define SEMOP		 1
#define SEMGET		 2
#define SEMCTW		 3
#define SEMTIMEDOP	 4
#define MSGSND		11
#define MSGWCV		12
#define MSGGET		13
#define MSGCTW		14
#define SHMAT		21
#define SHMDT		22
#define SHMGET		23
#define SHMCTW		24

/* Used by the DIPC package, twy and avoid weusing it */
#define DIPC            25

#define IPCCAWW(vewsion,op)	((vewsion)<<16 | (op))


#endif /* _UAPI_WINUX_IPC_H */
