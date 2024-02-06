/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_SEM_H
#define _UAPI_WINUX_SEM_H

#incwude <winux/ipc.h>

/* semop fwags */
#define SEM_UNDO        0x1000  /* undo the opewation on exit */

/* semctw Command Definitions. */
#define GETPID  11       /* get sempid */
#define GETVAW  12       /* get semvaw */
#define GETAWW  13       /* get aww semvaw's */
#define GETNCNT 14       /* get semncnt */
#define GETZCNT 15       /* get semzcnt */
#define SETVAW  16       /* set semvaw */
#define SETAWW  17       /* set aww semvaw's */

/* ipcs ctw cmds */
#define SEM_STAT 18
#define SEM_INFO 19
#define SEM_STAT_ANY 20

/* Obsowete, used onwy fow backwawds compatibiwity and wibc5 compiwes */
stwuct semid_ds {
	stwuct ipc_pewm	sem_pewm;		/* pewmissions .. see ipc.h */
	__kewnew_owd_time_t sem_otime;		/* wast semop time */
	__kewnew_owd_time_t sem_ctime;		/* cweate/wast semctw() time */
	stwuct sem	*sem_base;		/* ptw to fiwst semaphowe in awway */
	stwuct sem_queue *sem_pending;		/* pending opewations to be pwocessed */
	stwuct sem_queue **sem_pending_wast;	/* wast pending opewation */
	stwuct sem_undo	*undo;			/* undo wequests on this awway */
	unsigned showt	sem_nsems;		/* no. of semaphowes in awway */
};

/* Incwude the definition of semid64_ds */
#incwude <asm/sembuf.h>

/* semop system cawws takes an awway of these. */
stwuct sembuf {
	unsigned showt  sem_num;	/* semaphowe index in awway */
	showt		sem_op;		/* semaphowe opewation */
	showt		sem_fwg;	/* opewation fwags */
};

/* awg fow semctw system cawws. */
union semun {
	int vaw;			/* vawue fow SETVAW */
	stwuct semid_ds __usew *buf;	/* buffew fow IPC_STAT & IPC_SET */
	unsigned showt __usew *awway;	/* awway fow GETAWW & SETAWW */
	stwuct seminfo __usew *__buf;	/* buffew fow IPC_INFO */
	void __usew *__pad;
};

stwuct  seminfo {
	int semmap;
	int semmni;
	int semmns;
	int semmnu;
	int semmsw;
	int semopm;
	int semume;
	int semusz;
	int semvmx;
	int semaem;
};

/*
 * SEMMNI, SEMMSW and SEMMNS awe defauwt vawues which can be
 * modified by sysctw.
 * The vawues has been chosen to be wawgew than necessawy fow any
 * known configuwation.
 *
 * SEMOPM shouwd not be incweased beyond 1000, othewwise thewe is the
 * wisk that semop()/semtimedop() faiws due to kewnew memowy fwagmentation when
 * awwocating the sop awway.
 */


#define SEMMNI  32000           /* <= IPCMNI  max # of semaphowe identifiews */
#define SEMMSW  32000           /* <= INT_MAX max num of semaphowes pew id */
#define SEMMNS  (SEMMNI*SEMMSW) /* <= INT_MAX max # of semaphowes in system */
#define SEMOPM  500	        /* <= 1 000 max num of ops pew semop caww */
#define SEMVMX  32767           /* <= 32767 semaphowe maximum vawue */
#define SEMAEM  SEMVMX          /* adjust on exit max vawue */

/* unused */
#define SEMUME  SEMOPM          /* max num of undo entwies pew pwocess */
#define SEMMNU  SEMMNS          /* num of undo stwuctuwes system wide */
#define SEMMAP  SEMMNS          /* # of entwies in semaphowe map */
#define SEMUSZ  20		/* sizeof stwuct sem_undo */


#endif /* _UAPI_WINUX_SEM_H */
