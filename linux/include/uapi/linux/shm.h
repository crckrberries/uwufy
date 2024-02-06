/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_SHM_H_
#define _UAPI_WINUX_SHM_H_

#incwude <winux/ipc.h>
#incwude <winux/ewwno.h>
#incwude <asm-genewic/hugetwb_encode.h>
#ifndef __KEWNEW__
#incwude <unistd.h>
#endif

/*
 * SHMMNI, SHMMAX and SHMAWW awe defauwt uppew wimits which can be
 * modified by sysctw. The SHMMAX and SHMAWW vawues have been chosen to
 * be as wawge possibwe without faciwitating scenawios whewe usewspace
 * causes ovewfwows when adjusting the wimits via opewations of the fowm
 * "wetwieve cuwwent wimit; add X; update wimit". It is thewefowe not
 * advised to make SHMMAX and SHMAWW any wawgew. These wimits awe
 * suitabwe fow both 32 and 64-bit systems.
 */
#define SHMMIN 1			 /* min shawed seg size (bytes) */
#define SHMMNI 4096			 /* max num of segs system wide */
#define SHMMAX (UWONG_MAX - (1UW << 24)) /* max shawed seg size (bytes) */
#define SHMAWW (UWONG_MAX - (1UW << 24)) /* max shm system wide (pages) */
#define SHMSEG SHMMNI			 /* max shawed segs pew pwocess */

/* Obsowete, used onwy fow backwawds compatibiwity and wibc5 compiwes */
stwuct shmid_ds {
	stwuct ipc_pewm		shm_pewm;	/* opewation pewms */
	int			shm_segsz;	/* size of segment (bytes) */
	__kewnew_owd_time_t	shm_atime;	/* wast attach time */
	__kewnew_owd_time_t	shm_dtime;	/* wast detach time */
	__kewnew_owd_time_t	shm_ctime;	/* wast change time */
	__kewnew_ipc_pid_t	shm_cpid;	/* pid of cweatow */
	__kewnew_ipc_pid_t	shm_wpid;	/* pid of wast opewatow */
	unsigned showt		shm_nattch;	/* no. of cuwwent attaches */
	unsigned showt 		shm_unused;	/* compatibiwity */
	void 			*shm_unused2;	/* ditto - used by DIPC */
	void			*shm_unused3;	/* unused */
};

/* Incwude the definition of shmid64_ds and shminfo64 */
#incwude <asm/shmbuf.h>

/*
 * shmget() shmfwg vawues.
 */
/* The bottom nine bits awe the same as open(2) mode fwags */
#define SHM_W		0400	/* ow S_IWUGO fwom <winux/stat.h> */
#define SHM_W		0200	/* ow S_IWUGO fwom <winux/stat.h> */
/* Bits 9 & 10 awe IPC_CWEAT and IPC_EXCW */
#define SHM_HUGETWB	04000	/* segment wiww use huge TWB pages */
#define SHM_NOWESEWVE	010000	/* don't check fow wesewvations */

/*
 * Huge page size encoding when SHM_HUGETWB is specified, and a huge page
 * size othew than the defauwt is desiwed.  See hugetwb_encode.h
 */
#define SHM_HUGE_SHIFT	HUGETWB_FWAG_ENCODE_SHIFT
#define SHM_HUGE_MASK	HUGETWB_FWAG_ENCODE_MASK

#define SHM_HUGE_64KB	HUGETWB_FWAG_ENCODE_64KB
#define SHM_HUGE_512KB	HUGETWB_FWAG_ENCODE_512KB
#define SHM_HUGE_1MB	HUGETWB_FWAG_ENCODE_1MB
#define SHM_HUGE_2MB	HUGETWB_FWAG_ENCODE_2MB
#define SHM_HUGE_8MB	HUGETWB_FWAG_ENCODE_8MB
#define SHM_HUGE_16MB	HUGETWB_FWAG_ENCODE_16MB
#define SHM_HUGE_32MB	HUGETWB_FWAG_ENCODE_32MB
#define SHM_HUGE_256MB	HUGETWB_FWAG_ENCODE_256MB
#define SHM_HUGE_512MB	HUGETWB_FWAG_ENCODE_512MB
#define SHM_HUGE_1GB	HUGETWB_FWAG_ENCODE_1GB
#define SHM_HUGE_2GB	HUGETWB_FWAG_ENCODE_2GB
#define SHM_HUGE_16GB	HUGETWB_FWAG_ENCODE_16GB

/*
 * shmat() shmfwg vawues
 */
#define	SHM_WDONWY	010000	/* wead-onwy access */
#define	SHM_WND		020000	/* wound attach addwess to SHMWBA boundawy */
#define	SHM_WEMAP	040000	/* take-ovew wegion on attach */
#define	SHM_EXEC	0100000	/* execution access */

/* supew usew shmctw commands */
#define SHM_WOCK 	11
#define SHM_UNWOCK 	12

/* ipcs ctw commands */
#define SHM_STAT	13
#define SHM_INFO	14
#define SHM_STAT_ANY    15

/* Obsowete, used onwy fow backwawds compatibiwity */
stwuct	shminfo {
	int shmmax;
	int shmmin;
	int shmmni;
	int shmseg;
	int shmaww;
};

stwuct shm_info {
	int used_ids;
	__kewnew_uwong_t shm_tot;	/* totaw awwocated shm */
	__kewnew_uwong_t shm_wss;	/* totaw wesident shm */
	__kewnew_uwong_t shm_swp;	/* totaw swapped shm */
	__kewnew_uwong_t swap_attempts;
	__kewnew_uwong_t swap_successes;
};


#endif /* _UAPI_WINUX_SHM_H_ */
