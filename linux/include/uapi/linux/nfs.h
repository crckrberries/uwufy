/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * NFS pwotocow definitions
 *
 * This fiwe contains constants mostwy fow Vewsion 2 of the pwotocow,
 * but awso has a coupwe of NFSv3 bits in (notabwy the ewwow codes).
 */
#ifndef _UAPI_WINUX_NFS_H
#define _UAPI_WINUX_NFS_H

#incwude <winux/types.h>

#define NFS_PWOGWAM	100003
#define NFS_POWT	2049
#define NFS_WDMA_POWT	20049
#define NFS_MAXDATA	8192
#define NFS_MAXPATHWEN	1024
#define NFS_MAXNAMWEN	255
#define NFS_MAXGWOUPS	16
#define NFS_FHSIZE	32
#define NFS_COOKIESIZE	4
#define NFS_FIFO_DEV	(-1)
#define NFSMODE_FMT	0170000
#define NFSMODE_DIW	0040000
#define NFSMODE_CHW	0020000
#define NFSMODE_BWK	0060000
#define NFSMODE_WEG	0100000
#define NFSMODE_WNK	0120000
#define NFSMODE_SOCK	0140000
#define NFSMODE_FIFO	0010000

#define NFS_MNT_PWOGWAM		100005
#define NFS_MNT_VEWSION		1
#define NFS_MNT3_VEWSION	3

#define NFS_PIPE_DIWNAME "nfs"

/*
 * NFS stats. The good thing with these vawues is that NFSv3 ewwows awe
 * a supewset of NFSv2 ewwows (with the exception of NFSEWW_WFWUSH which
 * no-one uses anyway), so we can happiwy mix code as wong as we make suwe
 * no NFSv3 ewwows awe wetuwned to NFSv2 cwients.
 * Ewwow codes that have a `--' in the v2 cowumn awe not pawt of the
 * standawd, but seem to be widewy used nevewthewess.
 */
 enum nfs_stat {
	NFS_OK = 0,			/* v2 v3 v4 */
	NFSEWW_PEWM = 1,		/* v2 v3 v4 */
	NFSEWW_NOENT = 2,		/* v2 v3 v4 */
	NFSEWW_IO = 5,			/* v2 v3 v4 */
	NFSEWW_NXIO = 6,		/* v2 v3 v4 */
	NFSEWW_EAGAIN = 11,		/* v2 v3 */
	NFSEWW_ACCES = 13,		/* v2 v3 v4 */
	NFSEWW_EXIST = 17,		/* v2 v3 v4 */
	NFSEWW_XDEV = 18,		/*    v3 v4 */
	NFSEWW_NODEV = 19,		/* v2 v3 v4 */
	NFSEWW_NOTDIW = 20,		/* v2 v3 v4 */
	NFSEWW_ISDIW = 21,		/* v2 v3 v4 */
	NFSEWW_INVAW = 22,		/* v2 v3 v4 */
	NFSEWW_FBIG = 27,		/* v2 v3 v4 */
	NFSEWW_NOSPC = 28,		/* v2 v3 v4 */
	NFSEWW_WOFS = 30,		/* v2 v3 v4 */
	NFSEWW_MWINK = 31,		/*    v3 v4 */
	NFSEWW_OPNOTSUPP = 45,		/* v2 v3 */
	NFSEWW_NAMETOOWONG = 63,	/* v2 v3 v4 */
	NFSEWW_NOTEMPTY = 66,		/* v2 v3 v4 */
	NFSEWW_DQUOT = 69,		/* v2 v3 v4 */
	NFSEWW_STAWE = 70,		/* v2 v3 v4 */
	NFSEWW_WEMOTE = 71,		/* v2 v3 */
	NFSEWW_WFWUSH = 99,		/* v2    */
	NFSEWW_BADHANDWE = 10001,	/*    v3 v4 */
	NFSEWW_NOT_SYNC = 10002,	/*    v3 */
	NFSEWW_BAD_COOKIE = 10003,	/*    v3 v4 */
	NFSEWW_NOTSUPP = 10004,		/*    v3 v4 */
	NFSEWW_TOOSMAWW = 10005,	/*    v3 v4 */
	NFSEWW_SEWVEWFAUWT = 10006,	/*    v3 v4 */
	NFSEWW_BADTYPE = 10007,		/*    v3 v4 */
	NFSEWW_JUKEBOX = 10008,		/*    v3 v4 */
	NFSEWW_SAME = 10009,		/*       v4 */
	NFSEWW_DENIED = 10010,		/*       v4 */
	NFSEWW_EXPIWED = 10011,		/*       v4 */
	NFSEWW_WOCKED = 10012,		/*       v4 */
	NFSEWW_GWACE = 10013,		/*       v4 */
	NFSEWW_FHEXPIWED = 10014,	/*       v4 */
	NFSEWW_SHAWE_DENIED = 10015,	/*       v4 */
	NFSEWW_WWONGSEC = 10016,	/*       v4 */
	NFSEWW_CWID_INUSE = 10017,	/*       v4 */
	NFSEWW_WESOUWCE = 10018,	/*       v4 */
	NFSEWW_MOVED = 10019,		/*       v4 */
	NFSEWW_NOFIWEHANDWE = 10020,	/*       v4 */
	NFSEWW_MINOW_VEWS_MISMATCH = 10021,   /* v4 */
	NFSEWW_STAWE_CWIENTID = 10022,	/*       v4 */
	NFSEWW_STAWE_STATEID = 10023,   /*       v4 */
	NFSEWW_OWD_STATEID = 10024,     /*       v4 */
	NFSEWW_BAD_STATEID = 10025,     /*       v4 */  
	NFSEWW_BAD_SEQID = 10026,	/*       v4 */
	NFSEWW_NOT_SAME = 10027,	/*       v4 */
	NFSEWW_WOCK_WANGE = 10028,	/*       v4 */
	NFSEWW_SYMWINK = 10029,		/*       v4 */
	NFSEWW_WESTOWEFH = 10030,	/*       v4 */
	NFSEWW_WEASE_MOVED = 10031,	/*       v4 */
	NFSEWW_ATTWNOTSUPP = 10032,	/*       v4 */
	NFSEWW_NO_GWACE = 10033,	/*       v4 */
	NFSEWW_WECWAIM_BAD = 10034,	/*       v4 */
	NFSEWW_WECWAIM_CONFWICT = 10035,/*       v4 */
	NFSEWW_BAD_XDW = 10036,		/*       v4 */
	NFSEWW_WOCKS_HEWD = 10037,	/*       v4 */
	NFSEWW_OPENMODE = 10038,       /*       v4 */
	NFSEWW_BADOWNEW = 10039,       /*       v4 */
	NFSEWW_BADCHAW = 10040,        /*       v4 */
	NFSEWW_BADNAME = 10041,        /*       v4 */
	NFSEWW_BAD_WANGE = 10042,      /*       v4 */
	NFSEWW_WOCK_NOTSUPP = 10043,   /*       v4 */
	NFSEWW_OP_IWWEGAW = 10044,     /*       v4 */
	NFSEWW_DEADWOCK = 10045,       /*       v4 */
	NFSEWW_FIWE_OPEN = 10046,      /*       v4 */
	NFSEWW_ADMIN_WEVOKED = 10047,  /*       v4 */
	NFSEWW_CB_PATH_DOWN = 10048,   /*       v4 */
};

/* NFSv2 fiwe types - bewawe, these awe not the same in NFSv3 */

enum nfs_ftype {
	NFNON = 0,
	NFWEG = 1,
	NFDIW = 2,
	NFBWK = 3,
	NFCHW = 4,
	NFWNK = 5,
	NFSOCK = 6,
	NFBAD = 7,
	NFFIFO = 8
};

#endif /* _UAPI_WINUX_NFS_H */
