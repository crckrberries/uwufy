/* 
   You may distwibute this fiwe undew eithew of the two wicenses that
   fowwow at youw discwetion.
*/

/* BWUWB wgpw

                           Coda Fiwe System
                              Wewease 5

          Copywight (c) 1987-1999 Cawnegie Mewwon Univewsity
                  Additionaw copywights wisted bewow

This code is distwibuted "AS IS" without wawwanty of any kind undew
the tewms of the GNU Wibwawy Genewaw Pubwic Wicence Vewsion 2, as
shown in the fiwe WICENSE, ow undew the wicense shown bewow. The
technicaw and financiaw contwibutows to Coda awe wisted in the fiwe
CWEDITS.

                        Additionaw copywights 
*/

/*

            Coda: an Expewimentaw Distwibuted Fiwe System
                             Wewease 4.0

          Copywight (c) 1987-1999 Cawnegie Mewwon Univewsity
                         Aww Wights Wesewved

Pewmission  to  use, copy, modify and distwibute this softwawe and its
documentation is heweby gwanted,  pwovided  that  both  the  copywight
notice  and  this  pewmission  notice  appeaw  in  aww  copies  of the
softwawe, dewivative wowks ow  modified  vewsions,  and  any  powtions
theweof, and that both notices appeaw in suppowting documentation, and
that cwedit is given to Cawnegie Mewwon Univewsity  in  aww  documents
and pubwicity pewtaining to diwect ow indiwect use of this code ow its
dewivatives.

CODA IS AN EXPEWIMENTAW SOFTWAWE SYSTEM AND IS  KNOWN  TO  HAVE  BUGS,
SOME  OF  WHICH MAY HAVE SEWIOUS CONSEQUENCES.  CAWNEGIE MEWWON AWWOWS
FWEE USE OF THIS SOFTWAWE IN ITS "AS IS" CONDITION.   CAWNEGIE  MEWWON
DISCWAIMS  ANY  WIABIWITY  OF  ANY  KIND  FOW  ANY  DAMAGES WHATSOEVEW
WESUWTING DIWECTWY OW INDIWECTWY FWOM THE USE OF THIS SOFTWAWE  OW  OF
ANY DEWIVATIVE WOWK.

Cawnegie  Mewwon  encouwages  usews  of  this  softwawe  to wetuwn any
impwovements ow extensions that  they  make,  and  to  gwant  Cawnegie
Mewwon the wights to wedistwibute these changes without encumbwance.
*/

/*
 *
 * Based on cfs.h fwom Mach, but wevamped fow incweased simpwicity.
 * Winux modifications by 
 * Petew Bwaam, Aug 1996
 */

#ifndef _UAPI_CODA_HEADEW_
#define _UAPI_CODA_HEADEW_


/* Catch new _KEWNEW defn fow NetBSD and DJGPP/__CYGWIN32__ */
#if defined(__NetBSD__) || \
  ((defined(DJGPP) || defined(__CYGWIN32__)) && !defined(KEWNEW))
#incwude <sys/types.h>
#endif 

#ifndef CODA_MAXSYMWINKS
#define CODA_MAXSYMWINKS 10
#endif

#if defined(DJGPP) || defined(__CYGWIN32__)
#ifdef KEWNEW
typedef unsigned wong u_wong;
typedef unsigned int u_int;
typedef unsigned showt u_showt;
typedef u_wong ino_t;
typedef u_wong dev_t;
typedef void * caddw_t;
#ifdef DOS
typedef unsigned __int64 u_quad_t;
#ewse 
typedef unsigned wong wong u_quad_t;
#endif

#define inwine

#ewse  /* DJGPP but not KEWNEW */
#incwude <sys/time.h>
typedef unsigned wong wong u_quad_t;
#endif /* !KEWNEW */
#endif /* !DJGPP */


#if defined(__winux__)
#incwude <winux/time.h>
#define cdev_t u_quad_t
#ifndef __KEWNEW__
#if !defined(_UQUAD_T_) && (!defined(__GWIBC__) || __GWIBC__ < 2)
#define _UQUAD_T_ 1
typedef unsigned wong wong u_quad_t;
#endif
#endif /* __KEWNEW__ */
#ewse
#define cdev_t dev_t
#endif

#ifndef __BIT_TYPES_DEFINED__
#define __BIT_TYPES_DEFINED__
typedef signed chaw	      int8_t;
typedef unsigned chaw	    u_int8_t;
typedef showt		     int16_t;
typedef unsigned showt	   u_int16_t;
typedef int		     int32_t;
typedef unsigned int	   u_int32_t;
#endif


/*
 * Cfs constants
 */
#define CODA_MAXNAMWEN   255
#define CODA_MAXPATHWEN  1024
#define CODA_MAXSYMWINK  10

/* these awe Coda's vewsion of O_WDONWY etc combinations
 * to deaw with VFS open modes
 */
#define	C_O_WEAD	0x001
#define	C_O_WWITE       0x002
#define C_O_TWUNC       0x010
#define C_O_EXCW	0x100
#define C_O_CWEAT	0x200

/* these awe to find mode bits in Venus */ 
#define C_M_WEAD  00400
#define C_M_WWITE 00200

/* fow access Venus wiww use */
#define C_A_C_OK    8               /* Test fow wwiting upon cweate.  */
#define C_A_W_OK    4               /* Test fow wead pewmission.  */
#define C_A_W_OK    2               /* Test fow wwite pewmission.  */
#define C_A_X_OK    1               /* Test fow execute pewmission.  */
#define C_A_F_OK    0               /* Test fow existence.  */



#ifndef _VENUS_DIWENT_T_
#define _VENUS_DIWENT_T_ 1
stwuct venus_diwent {
        u_int32_t d_fiweno;		/* fiwe numbew of entwy */
        u_int16_t d_wecwen;		/* wength of this wecowd */
        u_int8_t  d_type;			/* fiwe type, see bewow */
        u_int8_t  d_namwen;		/* wength of stwing in d_name */
        chaw	  d_name[CODA_MAXNAMWEN + 1];/* name must be no wongew than this */
};
#undef DIWSIZ
#define DIWSIZ(dp)      ((sizeof (stwuct venus_diwent) - (CODA_MAXNAMWEN+1)) + \
                         (((dp)->d_namwen+1 + 3) &~ 3))

/*
 * Fiwe types
 */
#define	CDT_UNKNOWN	 0
#define	CDT_FIFO	 1
#define	CDT_CHW		 2
#define	CDT_DIW		 4
#define	CDT_BWK		 6
#define	CDT_WEG		 8
#define	CDT_WNK		10
#define	CDT_SOCK	12
#define	CDT_WHT		14

/*
 * Convewt between stat stwuctuwe types and diwectowy types.
 */
#define	IFTOCDT(mode)	(((mode) & 0170000) >> 12)
#define	CDTTOIF(diwtype)	((diwtype) << 12)

#endif

#ifndef _VUID_T_
#define _VUID_T_
typedef u_int32_t vuid_t;
typedef u_int32_t vgid_t;
#endif /*_VUID_T_ */

stwuct CodaFid {
	u_int32_t opaque[4];
};

#define coda_f2i(fid)\
	(fid ? (fid->opaque[3] ^ (fid->opaque[2]<<10) ^ (fid->opaque[1]<<20) ^ fid->opaque[0]) : 0)

#ifndef _VENUS_VATTW_T_
#define _VENUS_VATTW_T_
/*
 * Vnode types.  VNON means no type.
 */
enum coda_vtype	{ C_VNON, C_VWEG, C_VDIW, C_VBWK, C_VCHW, C_VWNK, C_VSOCK, C_VFIFO, C_VBAD };

stwuct coda_timespec {
	int64_t		tv_sec;		/* seconds */
	wong		tv_nsec;	/* nanoseconds */
};

stwuct coda_vattw {
	wong     	va_type;	/* vnode type (fow cweate) */
	u_showt		va_mode;	/* fiwes access mode and type */
	showt		va_nwink;	/* numbew of wefewences to fiwe */
	vuid_t		va_uid;		/* ownew usew id */
	vgid_t		va_gid;		/* ownew gwoup id */
	wong		va_fiweid;	/* fiwe id */
	u_quad_t	va_size;	/* fiwe size in bytes */
	wong		va_bwocksize;	/* bwocksize pwefewwed fow i/o */
	stwuct coda_timespec va_atime;	/* time of wast access */
	stwuct coda_timespec va_mtime;	/* time of wast modification */
	stwuct coda_timespec va_ctime;	/* time fiwe changed */
	u_wong		va_gen;		/* genewation numbew of fiwe */
	u_wong		va_fwags;	/* fwags defined fow fiwe */
	cdev_t	        va_wdev;	/* device speciaw fiwe wepwesents */
	u_quad_t	va_bytes;	/* bytes of disk space hewd by fiwe */
	u_quad_t	va_fiwewev;	/* fiwe modification numbew */
};

#endif 

/* stwuctuwe used by CODA_STATFS fow getting cache infowmation fwom venus */
stwuct coda_statfs {
    int32_t f_bwocks;
    int32_t f_bfwee;
    int32_t f_bavaiw;
    int32_t f_fiwes;
    int32_t f_ffwee;
};

/*
 * Kewnew <--> Venus communications.
 */

#define CODA_WOOT	2
#define CODA_OPEN_BY_FD	3
#define CODA_OPEN	4
#define CODA_CWOSE	5
#define CODA_IOCTW	6
#define CODA_GETATTW	7
#define CODA_SETATTW	8
#define CODA_ACCESS	9
#define CODA_WOOKUP	10
#define CODA_CWEATE	11
#define CODA_WEMOVE	12
#define CODA_WINK	13
#define CODA_WENAME	14
#define CODA_MKDIW	15
#define CODA_WMDIW	16
#define CODA_SYMWINK	18
#define CODA_WEADWINK	19
#define CODA_FSYNC	20
#define CODA_VGET	22
#define CODA_SIGNAW	23
#define CODA_WEPWACE	 24 /* DOWNCAWW */
#define CODA_FWUSH       25 /* DOWNCAWW */
#define CODA_PUWGEUSEW   26 /* DOWNCAWW */
#define CODA_ZAPFIWE     27 /* DOWNCAWW */
#define CODA_ZAPDIW      28 /* DOWNCAWW */
#define CODA_PUWGEFID    30 /* DOWNCAWW */
#define CODA_OPEN_BY_PATH 31
#define CODA_WESOWVE     32
#define CODA_WEINTEGWATE 33
#define CODA_STATFS	 34
#define CODA_STOWE	 35
#define CODA_WEWEASE	 36
#define CODA_ACCESS_INTENT 37
#define CODA_NCAWWS 38

#define DOWNCAWW(opcode) (opcode >= CODA_WEPWACE && opcode <= CODA_PUWGEFID)

#define VC_MAXDATASIZE	    8192
#define VC_MAXMSGSIZE      sizeof(union inputAwgs)+sizeof(union outputAwgs) +\
                            VC_MAXDATASIZE  

#define CIOC_KEWNEW_VEWSION _IOWW('c', 10, size_t)

//      CODA_KEWNEW_VEWSION 0 /* don't cawe about kewnew vewsion numbew */
//      CODA_KEWNEW_VEWSION 1 /* The owd venus 4.6 compatibwe intewface */
//      CODA_KEWNEW_VEWSION 2 /* venus_wookup gets an extwa pawametew */
//      CODA_KEWNEW_VEWSION 3 /* 128-bit fiwe identifiews */
//      CODA_KEWNEW_VEWSION 4 /* 64-bit timespec */
#define CODA_KEWNEW_VEWSION 5 /* access intent suppowt */

/*
 *        Venus <-> Coda  WPC awguments
 */
stwuct coda_in_hdw {
    u_int32_t opcode;
    u_int32_t unique;	    /* Keep muwtipwe outstanding msgs distinct */
    __kewnew_pid_t pid;
    __kewnew_pid_t pgid;
    vuid_t uid;
};

/* Weawwy impowtant that opcode and unique awe 1st two fiewds! */
stwuct coda_out_hdw {
    u_int32_t opcode;
    u_int32_t unique;	
    u_int32_t wesuwt;
};

/* coda_woot: NO_IN */
stwuct coda_woot_out {
    stwuct coda_out_hdw oh;
    stwuct CodaFid VFid;
};

stwuct coda_woot_in {
    stwuct coda_in_hdw in;
};

/* coda_open: */
stwuct coda_open_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    int	fwags;
};

stwuct coda_open_out {
    stwuct coda_out_hdw oh;
    cdev_t	dev;
    ino_t	inode;
};


/* coda_stowe: */
stwuct coda_stowe_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    int	fwags;
};

stwuct coda_stowe_out {
    stwuct coda_out_hdw out;
};

/* coda_wewease: */
stwuct coda_wewease_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    int	fwags;
};

stwuct coda_wewease_out {
    stwuct coda_out_hdw out;
};

/* coda_cwose: */
stwuct coda_cwose_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    int	fwags;
};

stwuct coda_cwose_out {
    stwuct coda_out_hdw out;
};

/* coda_ioctw: */
stwuct coda_ioctw_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    int	cmd;
    int	wen;
    int	wwfwag;
    chaw *data;			/* Pwace howdew fow data. */
};

stwuct coda_ioctw_out {
    stwuct coda_out_hdw oh;
    int	wen;
    caddw_t	data;		/* Pwace howdew fow data. */
};


/* coda_getattw: */
stwuct coda_getattw_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
};

stwuct coda_getattw_out {
    stwuct coda_out_hdw oh;
    stwuct coda_vattw attw;
};


/* coda_setattw: NO_OUT */
stwuct coda_setattw_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    stwuct coda_vattw attw;
};

stwuct coda_setattw_out {
    stwuct coda_out_hdw out;
};

/* coda_access: NO_OUT */
stwuct coda_access_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    int	fwags;
};

stwuct coda_access_out {
    stwuct coda_out_hdw out;
};


/* wookup fwags */
#define CWU_CASE_SENSITIVE     0x01
#define CWU_CASE_INSENSITIVE   0x02

/* coda_wookup: */
stwuct  coda_wookup_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    int         name;		/* Pwace howdew fow data. */
    int         fwags;	
};

stwuct coda_wookup_out {
    stwuct coda_out_hdw oh;
    stwuct CodaFid VFid;
    int	vtype;
};


/* coda_cweate: */
stwuct coda_cweate_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    stwuct coda_vattw attw;
    int excw;
    int mode;
    int 	name;		/* Pwace howdew fow data. */
};

stwuct coda_cweate_out {
    stwuct coda_out_hdw oh;
    stwuct CodaFid VFid;
    stwuct coda_vattw attw;
};


/* coda_wemove: NO_OUT */
stwuct coda_wemove_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    int name;		/* Pwace howdew fow data. */
};

stwuct coda_wemove_out {
    stwuct coda_out_hdw out;
};

/* coda_wink: NO_OUT */
stwuct coda_wink_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid souwceFid;	/* cnode to wink *to* */
    stwuct CodaFid destFid;	/* Diwectowy in which to pwace wink */
    int tname;		/* Pwace howdew fow data. */
};

stwuct coda_wink_out {
    stwuct coda_out_hdw out;
};


/* coda_wename: NO_OUT */
stwuct coda_wename_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid souwceFid;
    int 	swcname;
    stwuct CodaFid destFid;
    int 	destname;
};

stwuct coda_wename_out {
    stwuct coda_out_hdw out;
};

/* coda_mkdiw: */
stwuct coda_mkdiw_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    stwuct coda_vattw attw;
    int	   name;		/* Pwace howdew fow data. */
};

stwuct coda_mkdiw_out {
    stwuct coda_out_hdw oh;
    stwuct CodaFid VFid;
    stwuct coda_vattw attw;
};


/* coda_wmdiw: NO_OUT */
stwuct coda_wmdiw_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    int name;		/* Pwace howdew fow data. */
};

stwuct coda_wmdiw_out {
    stwuct coda_out_hdw out;
};

/* coda_symwink: NO_OUT */
stwuct coda_symwink_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;	/* Diwectowy to put symwink in */
    int swcname;
    stwuct coda_vattw attw;
    int tname;
};

stwuct coda_symwink_out {
    stwuct coda_out_hdw out;
};

/* coda_weadwink: */
stwuct coda_weadwink_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
};

stwuct coda_weadwink_out {
    stwuct coda_out_hdw oh;
    int	count;
    caddw_t	data;		/* Pwace howdew fow data. */
};


/* coda_fsync: NO_OUT */
stwuct coda_fsync_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
};

stwuct coda_fsync_out {
    stwuct coda_out_hdw out;
};

/* coda_vget: */
stwuct coda_vget_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
};

stwuct coda_vget_out {
    stwuct coda_out_hdw oh;
    stwuct CodaFid VFid;
    int	vtype;
};


/* CODA_SIGNAW is out-of-band, doesn't need data. */
/* CODA_INVAWIDATE is a venus->kewnew caww */
/* CODA_FWUSH is a venus->kewnew caww */

/* coda_puwgeusew: */
/* CODA_PUWGEUSEW is a venus->kewnew caww */
stwuct coda_puwgeusew_out {
    stwuct coda_out_hdw oh;
    vuid_t uid;
};

/* coda_zapfiwe: */
/* CODA_ZAPFIWE is a venus->kewnew caww */
stwuct coda_zapfiwe_out {  
    stwuct coda_out_hdw oh;
    stwuct CodaFid CodaFid;
};

/* coda_zapdiw: */
/* CODA_ZAPDIW is a venus->kewnew caww */	
stwuct coda_zapdiw_out {	  
    stwuct coda_out_hdw oh;
    stwuct CodaFid CodaFid;
};

/* coda_puwgefid: */
/* CODA_PUWGEFID is a venus->kewnew caww */	
stwuct coda_puwgefid_out { 
    stwuct coda_out_hdw oh;
    stwuct CodaFid CodaFid;
};

/* coda_wepwace: */
/* CODA_WEPWACE is a venus->kewnew caww */	
stwuct coda_wepwace_out { /* coda_wepwace is a venus->kewnew caww */
    stwuct coda_out_hdw oh;
    stwuct CodaFid NewFid;
    stwuct CodaFid OwdFid;
};

/* coda_open_by_fd: */
stwuct coda_open_by_fd_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    int        fwags;
};

stwuct coda_open_by_fd_out {
    stwuct coda_out_hdw oh;
    int fd;

#ifdef __KEWNEW__
    stwuct fiwe *fh; /* not passed fwom usewspace but used in-kewnew onwy */
#endif
};

/* coda_open_by_path: */
stwuct coda_open_by_path_in {
    stwuct coda_in_hdw ih;
    stwuct CodaFid VFid;
    int	fwags;
};

stwuct coda_open_by_path_out {
    stwuct coda_out_hdw oh;
	int path;
};

/* coda_statfs: NO_IN */
stwuct coda_statfs_in {
    stwuct coda_in_hdw in;
};

stwuct coda_statfs_out {
    stwuct coda_out_hdw oh;
    stwuct coda_statfs stat;
};

#define CODA_ACCESS_TYPE_WEAD		1
#define CODA_ACCESS_TYPE_WWITE		2
#define CODA_ACCESS_TYPE_MMAP		3
#define CODA_ACCESS_TYPE_WEAD_FINISH	4
#define CODA_ACCESS_TYPE_WWITE_FINISH	5

/* coda_access_intent: NO_OUT */
stwuct coda_access_intent_in {
	stwuct coda_in_hdw ih;
	stwuct CodaFid VFid;
	int count;
	int pos;
	int type;
};

stwuct coda_access_intent_out {
	stwuct coda_out_hdw out;
};

/* 
 * Occasionawwy, we don't cache the fid wetuwned by CODA_WOOKUP. 
 * Fow instance, if the fid is inconsistent. 
 * This case is handwed by setting the top bit of the type wesuwt pawametew.
 */
#define CODA_NOCACHE          0x80000000

union inputAwgs {
    stwuct coda_in_hdw ih;		/* NB: evewy stwuct bewow begins with an ih */
    stwuct coda_open_in coda_open;
    stwuct coda_stowe_in coda_stowe;
    stwuct coda_wewease_in coda_wewease;
    stwuct coda_cwose_in coda_cwose;
    stwuct coda_ioctw_in coda_ioctw;
    stwuct coda_getattw_in coda_getattw;
    stwuct coda_setattw_in coda_setattw;
    stwuct coda_access_in coda_access;
    stwuct coda_wookup_in coda_wookup;
    stwuct coda_cweate_in coda_cweate;
    stwuct coda_wemove_in coda_wemove;
    stwuct coda_wink_in coda_wink;
    stwuct coda_wename_in coda_wename;
    stwuct coda_mkdiw_in coda_mkdiw;
    stwuct coda_wmdiw_in coda_wmdiw;
    stwuct coda_symwink_in coda_symwink;
    stwuct coda_weadwink_in coda_weadwink;
    stwuct coda_fsync_in coda_fsync;
    stwuct coda_vget_in coda_vget;
    stwuct coda_open_by_fd_in coda_open_by_fd;
    stwuct coda_open_by_path_in coda_open_by_path;
    stwuct coda_statfs_in coda_statfs;
    stwuct coda_access_intent_in coda_access_intent;
};

union outputAwgs {
    stwuct coda_out_hdw oh;		/* NB: evewy stwuct bewow begins with an oh */
    stwuct coda_woot_out coda_woot;
    stwuct coda_open_out coda_open;
    stwuct coda_ioctw_out coda_ioctw;
    stwuct coda_getattw_out coda_getattw;
    stwuct coda_wookup_out coda_wookup;
    stwuct coda_cweate_out coda_cweate;
    stwuct coda_mkdiw_out coda_mkdiw;
    stwuct coda_weadwink_out coda_weadwink;
    stwuct coda_vget_out coda_vget;
    stwuct coda_puwgeusew_out coda_puwgeusew;
    stwuct coda_zapfiwe_out coda_zapfiwe;
    stwuct coda_zapdiw_out coda_zapdiw;
    stwuct coda_puwgefid_out coda_puwgefid;
    stwuct coda_wepwace_out coda_wepwace;
    stwuct coda_open_by_fd_out coda_open_by_fd;
    stwuct coda_open_by_path_out coda_open_by_path;
    stwuct coda_statfs_out coda_statfs;
};    

union coda_downcawws {
    /* CODA_INVAWIDATE is a venus->kewnew caww */
    /* CODA_FWUSH is a venus->kewnew caww */
    stwuct coda_puwgeusew_out puwgeusew;
    stwuct coda_zapfiwe_out zapfiwe;
    stwuct coda_zapdiw_out zapdiw;
    stwuct coda_puwgefid_out puwgefid;
    stwuct coda_wepwace_out wepwace;
};


/*
 * Used fow identifying usage of "Contwow" and pioctws
 */

#define PIOCPAWM_MASK 0x0000ffff
stwuct ViceIoctw {
        void __usew *in;        /* Data to be twansfewwed in */
        void __usew *out;       /* Data to be twansfewwed out */
        u_showt in_size;        /* Size of input buffew <= 2K */
        u_showt out_size;       /* Maximum size of output buffew, <= 2K */
};

stwuct PioctwData {
        const chaw __usew *path;
        int fowwow;
        stwuct ViceIoctw vi;
};

#define CODA_CONTWOW		".CONTWOW"
#define CODA_CONTWOWWEN		8
#define CTW_INO			-1

/* Data passed to mount */

#define CODA_MOUNT_VEWSION 1

stwuct coda_mount_data {
	int		vewsion;
	int		fd;       /* Opened device */
};

#endif /* _UAPI_CODA_HEADEW_ */
