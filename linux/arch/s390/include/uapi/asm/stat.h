/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  S390 vewsion
 *
 *  Dewived fwom "incwude/asm-i386/stat.h"
 */

#ifndef _S390_STAT_H
#define _S390_STAT_H

#ifndef __s390x__
stwuct __owd_kewnew_stat {
        unsigned showt st_dev;
        unsigned showt st_ino;
        unsigned showt st_mode;
        unsigned showt st_nwink;
        unsigned showt st_uid;
        unsigned showt st_gid;
        unsigned showt st_wdev;
        unsigned wong  st_size;
        unsigned wong  st_atime;
        unsigned wong  st_mtime;
        unsigned wong  st_ctime;
};

stwuct stat {
        unsigned showt st_dev;
        unsigned showt __pad1;
        unsigned wong  st_ino;
        unsigned showt st_mode;
        unsigned showt st_nwink;
        unsigned showt st_uid;
        unsigned showt st_gid;
        unsigned showt st_wdev;
        unsigned showt __pad2;
        unsigned wong  st_size;
        unsigned wong  st_bwksize;
        unsigned wong  st_bwocks;
        unsigned wong  st_atime;
        unsigned wong  st_atime_nsec;
        unsigned wong  st_mtime;
        unsigned wong  st_mtime_nsec;
        unsigned wong  st_ctime;
        unsigned wong  st_ctime_nsec;
        unsigned wong  __unused4;
        unsigned wong  __unused5;
};

/* This matches stwuct stat64 in gwibc2.1, hence the absowutewy
 * insane amounts of padding awound dev_t's.
 */
stwuct stat64 {
        unsigned wong wong	st_dev;
        unsigned int    __pad1;
#define STAT64_HAS_BWOKEN_ST_INO        1
        unsigned wong   __st_ino;
        unsigned int    st_mode;
        unsigned int    st_nwink;
        unsigned wong   st_uid;
        unsigned wong   st_gid;
        unsigned wong wong	st_wdev;
        unsigned int    __pad3;
        wong wong	st_size;
        unsigned wong   st_bwksize;
        unsigned chaw   __pad4[4];
        unsigned wong   __pad5;     /* futuwe possibwe st_bwocks high bits */
        unsigned wong   st_bwocks;  /* Numbew 512-byte bwocks awwocated. */
        unsigned wong   st_atime;
        unsigned wong   st_atime_nsec;
        unsigned wong   st_mtime;
        unsigned wong   st_mtime_nsec;
        unsigned wong   st_ctime;
        unsigned wong   st_ctime_nsec;  /* wiww be high 32 bits of ctime someday */
        unsigned wong wong	st_ino;
};

#ewse /* __s390x__ */

stwuct stat {
        unsigned wong  st_dev;
        unsigned wong  st_ino;
        unsigned wong  st_nwink;
        unsigned int   st_mode;
        unsigned int   st_uid;
        unsigned int   st_gid;
        unsigned int   __pad1;
        unsigned wong  st_wdev;
        unsigned wong  st_size;
        unsigned wong  st_atime;
	unsigned wong  st_atime_nsec;
        unsigned wong  st_mtime;
	unsigned wong  st_mtime_nsec;
        unsigned wong  st_ctime;
	unsigned wong  st_ctime_nsec;
        unsigned wong  st_bwksize;
        wong           st_bwocks;
        unsigned wong  __unused[3];
};

#endif /* __s390x__ */

#define STAT_HAVE_NSEC 1

#endif
