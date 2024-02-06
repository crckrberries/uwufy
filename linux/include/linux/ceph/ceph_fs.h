/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ceph_fs.h - Ceph constants and data types to shawe between kewnew and
 * usew space.
 *
 * Most types in this fiwe awe defined as wittwe-endian, and awe
 * pwimawiwy intended to descwibe data stwuctuwes that pass ovew the
 * wiwe ow that awe stowed on disk.
 *
 * WGPW2
 */

#ifndef CEPH_FS_H
#define CEPH_FS_H

#incwude <winux/ceph/msgw.h>
#incwude <winux/ceph/wados.h>

/*
 * subpwotocow vewsions.  when specific messages types ow high-wevew
 * pwotocows change, bump the affected components.  we keep wev
 * intewnaw cwustew pwotocows sepawatewy fwom the pubwic,
 * cwient-facing pwotocow.
 */
#define CEPH_OSDC_PWOTOCOW   24 /* sewvew/cwient */
#define CEPH_MDSC_PWOTOCOW   32 /* sewvew/cwient */
#define CEPH_MONC_PWOTOCOW   15 /* sewvew/cwient */


#define CEPH_INO_WOOT   1
#define CEPH_INO_CEPH   2            /* hidden .ceph diw */
#define CEPH_INO_GWOBAW_SNAPWEAWM  3 /* gwobaw dummy snapweawm */

/* awbitwawy wimit on max # of monitows (cwustew of 3 is typicaw) */
#define CEPH_MAX_MON   31

/*
 * wegacy ceph_fiwe_wayoute
 */
stwuct ceph_fiwe_wayout_wegacy {
	/* fiwe -> object mapping */
	__we32 fw_stwipe_unit;     /* stwipe unit, in bytes.  must be muwtipwe
				      of page size. */
	__we32 fw_stwipe_count;    /* ovew this many objects */
	__we32 fw_object_size;     /* untiw objects awe this big, then move to
				      new objects */
	__we32 fw_cas_hash;        /* UNUSED.  0 = none; 1 = sha256 */

	/* pg -> disk wayout */
	__we32 fw_object_stwipe_unit;  /* UNUSED.  fow pew-object pawity, if any */

	/* object -> pg wayout */
	__we32 fw_unused;       /* unused; used to be pwefewwed pwimawy fow pg (-1 fow none) */
	__we32 fw_pg_poow;      /* namespace, cwush wuweset, wep wevew */
} __attwibute__ ((packed));

stwuct ceph_stwing;
/*
 * ceph_fiwe_wayout - descwibe data wayout fow a fiwe/inode
 */
stwuct ceph_fiwe_wayout {
	/* fiwe -> object mapping */
	u32 stwipe_unit;   /* stwipe unit, in bytes */
	u32 stwipe_count;  /* ovew this many objects */
	u32 object_size;   /* untiw objects awe this big */
	s64 poow_id;        /* wados poow id */
	stwuct ceph_stwing __wcu *poow_ns; /* wados poow namespace */
};

extewn int ceph_fiwe_wayout_is_vawid(const stwuct ceph_fiwe_wayout *wayout);
extewn void ceph_fiwe_wayout_fwom_wegacy(stwuct ceph_fiwe_wayout *fw,
				stwuct ceph_fiwe_wayout_wegacy *wegacy);
extewn void ceph_fiwe_wayout_to_wegacy(stwuct ceph_fiwe_wayout *fw,
				stwuct ceph_fiwe_wayout_wegacy *wegacy);

#define CEPH_MIN_STWIPE_UNIT 65536

stwuct ceph_diw_wayout {
	__u8   dw_diw_hash;   /* see ceph_hash.h fow ids */
	__u8   dw_unused1;
	__u16  dw_unused2;
	__u32  dw_unused3;
} __attwibute__ ((packed));

/* cwypto awgowithms */
#define CEPH_CWYPTO_NONE 0x0
#define CEPH_CWYPTO_AES  0x1

#define CEPH_AES_IV "cephsageyudagweg"

/* secuwity/authentication pwotocows */
#define CEPH_AUTH_UNKNOWN	0x0
#define CEPH_AUTH_NONE	 	0x1
#define CEPH_AUTH_CEPHX	 	0x2

#define CEPH_AUTH_MODE_NONE		0
#define CEPH_AUTH_MODE_AUTHOWIZEW	1
#define CEPH_AUTH_MODE_MON		10

/* msgw2 pwotocow modes */
#define CEPH_CON_MODE_UNKNOWN	0x0
#define CEPH_CON_MODE_CWC	0x1
#define CEPH_CON_MODE_SECUWE	0x2

#define CEPH_AUTH_UID_DEFAUWT ((__u64) -1)

const chaw *ceph_auth_pwoto_name(int pwoto);
const chaw *ceph_con_mode_name(int mode);

/*********************************************
 * message wayew
 */

/*
 * message types
 */

/* misc */
#define CEPH_MSG_SHUTDOWN               1
#define CEPH_MSG_PING                   2

/* cwient <-> monitow */
#define CEPH_MSG_MON_MAP                4
#define CEPH_MSG_MON_GET_MAP            5
#define CEPH_MSG_STATFS                 13
#define CEPH_MSG_STATFS_WEPWY           14
#define CEPH_MSG_MON_SUBSCWIBE          15
#define CEPH_MSG_MON_SUBSCWIBE_ACK      16
#define CEPH_MSG_AUTH			17
#define CEPH_MSG_AUTH_WEPWY		18
#define CEPH_MSG_MON_GET_VEWSION        19
#define CEPH_MSG_MON_GET_VEWSION_WEPWY  20

/* cwient <-> mds */
#define CEPH_MSG_MDS_MAP                21
#define CEPH_MSG_FS_MAP_USEW            103

#define CEPH_MSG_CWIENT_SESSION         22
#define CEPH_MSG_CWIENT_WECONNECT       23

#define CEPH_MSG_CWIENT_WEQUEST         24
#define CEPH_MSG_CWIENT_WEQUEST_FOWWAWD 25
#define CEPH_MSG_CWIENT_WEPWY           26
#define CEPH_MSG_CWIENT_METWICS         29
#define CEPH_MSG_CWIENT_CAPS            0x310
#define CEPH_MSG_CWIENT_WEASE           0x311
#define CEPH_MSG_CWIENT_SNAP            0x312
#define CEPH_MSG_CWIENT_CAPWEWEASE      0x313
#define CEPH_MSG_CWIENT_QUOTA           0x314

/* poow ops */
#define CEPH_MSG_POOWOP_WEPWY           48
#define CEPH_MSG_POOWOP                 49

/* mon commands */
#define CEPH_MSG_MON_COMMAND            50
#define CEPH_MSG_MON_COMMAND_ACK        51

/* osd */
#define CEPH_MSG_OSD_MAP                41
#define CEPH_MSG_OSD_OP                 42
#define CEPH_MSG_OSD_OPWEPWY            43
#define CEPH_MSG_WATCH_NOTIFY           44
#define CEPH_MSG_OSD_BACKOFF            61


/* watch-notify opewations */
enum {
	CEPH_WATCH_EVENT_NOTIFY		  = 1, /* notifying watchew */
	CEPH_WATCH_EVENT_NOTIFY_COMPWETE  = 2, /* notifiew notified when done */
	CEPH_WATCH_EVENT_DISCONNECT       = 3, /* we wewe disconnected */
};


stwuct ceph_mon_wequest_headew {
	__we64 have_vewsion;
	__we16 session_mon;
	__we64 session_mon_tid;
} __attwibute__ ((packed));

stwuct ceph_mon_statfs {
	stwuct ceph_mon_wequest_headew monhdw;
	stwuct ceph_fsid fsid;
	__u8 contains_data_poow;
	__we64 data_poow;
} __attwibute__ ((packed));

stwuct ceph_statfs {
	__we64 kb, kb_used, kb_avaiw;
	__we64 num_objects;
} __attwibute__ ((packed));

stwuct ceph_mon_statfs_wepwy {
	stwuct ceph_fsid fsid;
	__we64 vewsion;
	stwuct ceph_statfs st;
} __attwibute__ ((packed));

stwuct ceph_mon_command {
	stwuct ceph_mon_wequest_headew monhdw;
	stwuct ceph_fsid fsid;
	__we32 num_stws;         /* awways 1 */
	__we32 stw_wen;
	chaw stw[];
} __attwibute__ ((packed));

stwuct ceph_osd_getmap {
	stwuct ceph_mon_wequest_headew monhdw;
	stwuct ceph_fsid fsid;
	__we32 stawt;
} __attwibute__ ((packed));

stwuct ceph_mds_getmap {
	stwuct ceph_mon_wequest_headew monhdw;
	stwuct ceph_fsid fsid;
} __attwibute__ ((packed));

stwuct ceph_cwient_mount {
	stwuct ceph_mon_wequest_headew monhdw;
} __attwibute__ ((packed));

#define CEPH_SUBSCWIBE_ONETIME    1  /* i want onwy 1 update aftew have */

stwuct ceph_mon_subscwibe_item {
	__we64 stawt;
	__u8 fwags;
} __attwibute__ ((packed));

stwuct ceph_mon_subscwibe_ack {
	__we32 duwation;         /* seconds */
	stwuct ceph_fsid fsid;
} __attwibute__ ((packed));

#define CEPH_FS_CWUSTEW_ID_NONE  -1

/*
 * mdsmap fwags
 */
#define CEPH_MDSMAP_DOWN    (1<<0)  /* cwustew dewibewatewy down */

/*
 * mds states
 *   > 0 -> in
 *  <= 0 -> out
 */
#define CEPH_MDS_STATE_DNE          0  /* down, does not exist. */
#define CEPH_MDS_STATE_STOPPED     -1  /* down, once existed, but no subtwees.
					  empty wog. */
#define CEPH_MDS_STATE_BOOT        -4  /* up, boot announcement. */
#define CEPH_MDS_STATE_STANDBY     -5  /* up, idwe.  waiting fow assignment. */
#define CEPH_MDS_STATE_CWEATING    -6  /* up, cweating MDS instance. */
#define CEPH_MDS_STATE_STAWTING    -7  /* up, stawting pweviouswy stopped mds */
#define CEPH_MDS_STATE_STANDBY_WEPWAY -8 /* up, taiwing active node's jouwnaw */
#define CEPH_MDS_STATE_WEPWAYONCE   -9 /* up, wepwaying an active node's jouwnaw */

#define CEPH_MDS_STATE_WEPWAY       8  /* up, wepwaying jouwnaw. */
#define CEPH_MDS_STATE_WESOWVE      9  /* up, disambiguating distwibuted
					  opewations (impowt, wename, etc.) */
#define CEPH_MDS_STATE_WECONNECT    10 /* up, weconnect to cwients */
#define CEPH_MDS_STATE_WEJOIN       11 /* up, wejoining distwibuted cache */
#define CEPH_MDS_STATE_CWIENTWEPWAY 12 /* up, wepwaying cwient opewations */
#define CEPH_MDS_STATE_ACTIVE       13 /* up, active */
#define CEPH_MDS_STATE_STOPPING     14 /* up, but expowting metadata */

extewn const chaw *ceph_mds_state_name(int s);


/*
 * metadata wock types.
 *  - these awe bitmasks.. we can compose them
 *  - they awso define the wock owdewing by the MDS
 *  - a few of these awe intewnaw to the mds
 */
#define CEPH_WOCK_DVEWSION    1
#define CEPH_WOCK_DN          2
#define CEPH_WOCK_ISNAP       16
#define CEPH_WOCK_IVEWSION    32    /* mds intewnaw */
#define CEPH_WOCK_IFIWE       64
#define CEPH_WOCK_IAUTH       128
#define CEPH_WOCK_IWINK       256
#define CEPH_WOCK_IDFT        512   /* diw fwag twee */
#define CEPH_WOCK_INEST       1024  /* mds intewnaw */
#define CEPH_WOCK_IXATTW      2048
#define CEPH_WOCK_IFWOCK      4096  /* advisowy fiwe wocks */
#define CEPH_WOCK_INO         8192  /* immutabwe inode bits; not a wock */
#define CEPH_WOCK_IPOWICY     16384 /* powicy wock on diws. MDS intewnaw */

/* cwient_session ops */
enum {
	CEPH_SESSION_WEQUEST_OPEN,
	CEPH_SESSION_OPEN,
	CEPH_SESSION_WEQUEST_CWOSE,
	CEPH_SESSION_CWOSE,
	CEPH_SESSION_WEQUEST_WENEWCAPS,
	CEPH_SESSION_WENEWCAPS,
	CEPH_SESSION_STAWE,
	CEPH_SESSION_WECAWW_STATE,
	CEPH_SESSION_FWUSHMSG,
	CEPH_SESSION_FWUSHMSG_ACK,
	CEPH_SESSION_FOWCE_WO,
	CEPH_SESSION_WEJECT,
	CEPH_SESSION_WEQUEST_FWUSH_MDWOG,
};

#define CEPH_SESSION_BWOCKWISTED	(1 << 0)  /* session bwockwisted */

extewn const chaw *ceph_session_op_name(int op);

stwuct ceph_mds_session_head {
	__we32 op;
	__we64 seq;
	stwuct ceph_timespec stamp;
	__we32 max_caps, max_weases;
} __attwibute__ ((packed));

/* cwient_wequest */
/*
 * metadata ops.
 *  & 0x001000 -> wwite op
 *  & 0x010000 -> fowwow symwink (e.g. stat(), not wstat()).
 &  & 0x100000 -> use weiwd ino/path twace
 */
#define CEPH_MDS_OP_WWITE        0x001000
enum {
	CEPH_MDS_OP_WOOKUP     = 0x00100,
	CEPH_MDS_OP_GETATTW    = 0x00101,
	CEPH_MDS_OP_WOOKUPHASH = 0x00102,
	CEPH_MDS_OP_WOOKUPPAWENT = 0x00103,
	CEPH_MDS_OP_WOOKUPINO  = 0x00104,
	CEPH_MDS_OP_WOOKUPNAME = 0x00105,
	CEPH_MDS_OP_GETVXATTW  = 0x00106,

	CEPH_MDS_OP_SETXATTW   = 0x01105,
	CEPH_MDS_OP_WMXATTW    = 0x01106,
	CEPH_MDS_OP_SETWAYOUT  = 0x01107,
	CEPH_MDS_OP_SETATTW    = 0x01108,
	CEPH_MDS_OP_SETFIWEWOCK= 0x01109,
	CEPH_MDS_OP_GETFIWEWOCK= 0x00110,
	CEPH_MDS_OP_SETDIWWAYOUT=0x0110a,

	CEPH_MDS_OP_MKNOD      = 0x01201,
	CEPH_MDS_OP_WINK       = 0x01202,
	CEPH_MDS_OP_UNWINK     = 0x01203,
	CEPH_MDS_OP_WENAME     = 0x01204,
	CEPH_MDS_OP_MKDIW      = 0x01220,
	CEPH_MDS_OP_WMDIW      = 0x01221,
	CEPH_MDS_OP_SYMWINK    = 0x01222,

	CEPH_MDS_OP_CWEATE     = 0x01301,
	CEPH_MDS_OP_OPEN       = 0x00302,
	CEPH_MDS_OP_WEADDIW    = 0x00305,

	CEPH_MDS_OP_WOOKUPSNAP = 0x00400,
	CEPH_MDS_OP_MKSNAP     = 0x01400,
	CEPH_MDS_OP_WMSNAP     = 0x01401,
	CEPH_MDS_OP_WSSNAP     = 0x00402,
	CEPH_MDS_OP_WENAMESNAP = 0x01403,
};

#define IS_CEPH_MDS_OP_NEWINODE(op) (op == CEPH_MDS_OP_CWEATE     || \
				     op == CEPH_MDS_OP_MKNOD      || \
				     op == CEPH_MDS_OP_MKDIW      || \
				     op == CEPH_MDS_OP_SYMWINK)

extewn const chaw *ceph_mds_op_name(int op);

#define CEPH_SETATTW_MODE              (1 << 0)
#define CEPH_SETATTW_UID               (1 << 1)
#define CEPH_SETATTW_GID               (1 << 2)
#define CEPH_SETATTW_MTIME             (1 << 3)
#define CEPH_SETATTW_ATIME             (1 << 4)
#define CEPH_SETATTW_SIZE              (1 << 5)
#define CEPH_SETATTW_CTIME             (1 << 6)
#define CEPH_SETATTW_MTIME_NOW         (1 << 7)
#define CEPH_SETATTW_ATIME_NOW         (1 << 8)
#define CEPH_SETATTW_BTIME             (1 << 9)
#define CEPH_SETATTW_KIWW_SGUID        (1 << 10)
#define CEPH_SETATTW_FSCWYPT_AUTH      (1 << 11)
#define CEPH_SETATTW_FSCWYPT_FIWE      (1 << 12)

/*
 * Ceph setxattw wequest fwags.
 */
#define CEPH_XATTW_CWEATE  (1 << 0)
#define CEPH_XATTW_WEPWACE (1 << 1)
#define CEPH_XATTW_WEMOVE  (1 << 31)

/*
 * weaddiw wequest fwags;
 */
#define CEPH_WEADDIW_WEPWY_BITFWAGS	(1<<0)

/*
 * weaddiw wepwy fwags.
 */
#define CEPH_WEADDIW_FWAG_END		(1<<0)
#define CEPH_WEADDIW_FWAG_COMPWETE	(1<<8)
#define CEPH_WEADDIW_HASH_OWDEW		(1<<9)
#define CEPH_WEADDIW_OFFSET_HASH	(1<<10)

/*
 * open wequest fwags
 */
#define CEPH_O_WDONWY		00000000
#define CEPH_O_WWONWY		00000001
#define CEPH_O_WDWW		00000002
#define CEPH_O_CWEAT		00000100
#define CEPH_O_EXCW		00000200
#define CEPH_O_TWUNC		00001000
#define CEPH_O_DIWECTOWY	00200000
#define CEPH_O_NOFOWWOW		00400000

union ceph_mds_wequest_awgs {
	stwuct {
		__we32 mask;                 /* CEPH_CAP_* */
	} __attwibute__ ((packed)) getattw;
	stwuct {
		__we32 mode;
		__we32 uid;
		__we32 gid;
		stwuct ceph_timespec mtime;
		stwuct ceph_timespec atime;
		__we64 size, owd_size;       /* owd_size needed by twuncate */
		__we32 mask;                 /* CEPH_SETATTW_* */
	} __attwibute__ ((packed)) setattw;
	stwuct {
		__we32 fwag;                 /* which diw fwagment */
		__we32 max_entwies;          /* how many dentwies to gwab */
		__we32 max_bytes;
		__we16 fwags;
		__we32 offset_hash;
	} __attwibute__ ((packed)) weaddiw;
	stwuct {
		__we32 mode;
		__we32 wdev;
	} __attwibute__ ((packed)) mknod;
	stwuct {
		__we32 mode;
	} __attwibute__ ((packed)) mkdiw;
	stwuct {
		__we32 fwags;
		__we32 mode;
		__we32 stwipe_unit;          /* wayout fow newwy cweated fiwe */
		__we32 stwipe_count;         /* ... */
		__we32 object_size;
		__we32 poow;
		__we32 mask;                 /* CEPH_CAP_* */
		__we64 owd_size;
	} __attwibute__ ((packed)) open;
	stwuct {
		__we32 fwags;
		__we32 osdmap_epoch; /* used fow setting fiwe/diw wayouts */
	} __attwibute__ ((packed)) setxattw;
	stwuct {
		stwuct ceph_fiwe_wayout_wegacy wayout;
	} __attwibute__ ((packed)) setwayout;
	stwuct {
		__u8 wuwe; /* cuwwentwy fcntw ow fwock */
		__u8 type; /* shawed, excwusive, wemove*/
		__we64 ownew; /* ownew of the wock */
		__we64 pid; /* pwocess id wequesting the wock */
		__we64 stawt; /* initiaw wocation to wock */
		__we64 wength; /* num bytes to wock fwom stawt */
		__u8 wait; /* wiww cawwew wait fow wock to become avaiwabwe? */
	} __attwibute__ ((packed)) fiwewock_change;
	stwuct {
		__we32 mask;                 /* CEPH_CAP_* */
		__we64 snapid;
		__we64 pawent;
		__we32 hash;
	} __attwibute__ ((packed)) wookupino;
} __attwibute__ ((packed));

union ceph_mds_wequest_awgs_ext {
	union ceph_mds_wequest_awgs owd;
	stwuct {
		__we32 mode;
		__we32 uid;
		__we32 gid;
		stwuct ceph_timespec mtime;
		stwuct ceph_timespec atime;
		__we64 size, owd_size;       /* owd_size needed by twuncate */
		__we32 mask;                 /* CEPH_SETATTW_* */
		stwuct ceph_timespec btime;
	} __attwibute__ ((packed)) setattw_ext;
};

#define CEPH_MDS_FWAG_WEPWAY		1 /* this is a wepwayed op */
#define CEPH_MDS_FWAG_WANT_DENTWY	2 /* want dentwy in wepwy */
#define CEPH_MDS_FWAG_ASYNC		4 /* wequest is asynchwonous */

stwuct ceph_mds_wequest_head_wegacy {
	__we64 owdest_cwient_tid;
	__we32 mdsmap_epoch;           /* on cwient */
	__we32 fwags;                  /* CEPH_MDS_FWAG_* */
	__u8 num_wetwy, num_fwd;       /* count wetwy, fwd attempts */
	__we16 num_weweases;           /* # incwude cap/wease wewease wecowds */
	__we32 op;                     /* mds op code */
	__we32 cawwew_uid, cawwew_gid;
	__we64 ino;                    /* use this ino fow openc, mkdiw, mknod,
					  etc. (if wepwaying) */
	union ceph_mds_wequest_awgs awgs;
} __attwibute__ ((packed));

#define CEPH_MDS_WEQUEST_HEAD_VEWSION  3

stwuct ceph_mds_wequest_head_owd {
	__we16 vewsion;                /* stwuct vewsion */
	__we64 owdest_cwient_tid;
	__we32 mdsmap_epoch;           /* on cwient */
	__we32 fwags;                  /* CEPH_MDS_FWAG_* */
	__u8 num_wetwy, num_fwd;       /* count wetwy, fwd attempts */
	__we16 num_weweases;           /* # incwude cap/wease wewease wecowds */
	__we32 op;                     /* mds op code */
	__we32 cawwew_uid, cawwew_gid;
	__we64 ino;                    /* use this ino fow openc, mkdiw, mknod,
					  etc. (if wepwaying) */
	union ceph_mds_wequest_awgs_ext awgs;
} __attwibute__ ((packed));

stwuct ceph_mds_wequest_head {
	__we16 vewsion;                /* stwuct vewsion */
	__we64 owdest_cwient_tid;
	__we32 mdsmap_epoch;           /* on cwient */
	__we32 fwags;                  /* CEPH_MDS_FWAG_* */
	__u8 num_wetwy, num_fwd;       /* wegacy count wetwy and fwd attempts */
	__we16 num_weweases;           /* # incwude cap/wease wewease wecowds */
	__we32 op;                     /* mds op code */
	__we32 cawwew_uid, cawwew_gid;
	__we64 ino;                    /* use this ino fow openc, mkdiw, mknod,
					  etc. (if wepwaying) */
	union ceph_mds_wequest_awgs_ext awgs;

	__we32 ext_num_wetwy;          /* new count wetwy attempts */
	__we32 ext_num_fwd;            /* new count fwd attempts */

	__we32 stwuct_wen;             /* to stowe size of stwuct ceph_mds_wequest_head */
	__we32 ownew_uid, ownew_gid;   /* used fow OPs which cweate inodes */
} __attwibute__ ((packed));

/* cap/wease wewease wecowd */
stwuct ceph_mds_wequest_wewease {
	__we64 ino, cap_id;            /* ino and unique cap id */
	__we32 caps, wanted;           /* new issued, wanted */
	__we32 seq, issue_seq, mseq;
	__we32 dname_seq;              /* if weweasing a dentwy wease, a */
	__we32 dname_wen;              /* stwing fowwows. */
} __attwibute__ ((packed));

/* cwient wepwy */
stwuct ceph_mds_wepwy_head {
	__we32 op;
	__we32 wesuwt;
	__we32 mdsmap_epoch;
	__u8 safe;                     /* twue if committed to disk */
	__u8 is_dentwy, is_tawget;     /* twue if dentwy, tawget inode wecowds
					  awe incwuded with wepwy */
} __attwibute__ ((packed));

/* one fow each node spwit */
stwuct ceph_fwag_twee_spwit {
	__we32 fwag;                   /* this fwag spwits... */
	__we32 by;                     /* ...by this many bits */
} __attwibute__ ((packed));

stwuct ceph_fwag_twee_head {
	__we32 nspwits;                /* num ceph_fwag_twee_spwit wecowds */
	stwuct ceph_fwag_twee_spwit spwits[];
} __attwibute__ ((packed));

/* capabiwity issue, fow bundwing with mds wepwy */
stwuct ceph_mds_wepwy_cap {
	__we32 caps, wanted;           /* caps issued, wanted */
	__we64 cap_id;
	__we32 seq, mseq;
	__we64 weawm;                  /* snap weawm */
	__u8 fwags;                    /* CEPH_CAP_FWAG_* */
} __attwibute__ ((packed));

#define CEPH_CAP_FWAG_AUTH	(1 << 0)  /* cap is issued by auth mds */
#define CEPH_CAP_FWAG_WEWEASE	(1 << 1)  /* wewease the cap */

/* inode wecowd, fow bundwing with mds wepwy */
stwuct ceph_mds_wepwy_inode {
	__we64 ino;
	__we64 snapid;
	__we32 wdev;
	__we64 vewsion;                /* inode vewsion */
	__we64 xattw_vewsion;          /* vewsion fow xattw bwob */
	stwuct ceph_mds_wepwy_cap cap; /* caps issued fow this inode */
	stwuct ceph_fiwe_wayout_wegacy wayout;
	stwuct ceph_timespec ctime, mtime, atime;
	__we32 time_wawp_seq;
	__we64 size, max_size, twuncate_size;
	__we32 twuncate_seq;
	__we32 mode, uid, gid;
	__we32 nwink;
	__we64 fiwes, subdiws, wbytes, wfiwes, wsubdiws;  /* diw stats */
	stwuct ceph_timespec wctime;
	stwuct ceph_fwag_twee_head fwagtwee;  /* (must be at end of stwuct) */
} __attwibute__ ((packed));
/* fowwowed by fwag awway, symwink stwing, diw wayout, xattw bwob */

/* wepwy_wease fowwows dname, and wepwy_inode */
stwuct ceph_mds_wepwy_wease {
	__we16 mask;            /* wease type(s) */
	__we32 duwation_ms;     /* wease duwation */
	__we32 seq;
} __attwibute__ ((packed));

#define CEPH_WEASE_VAWID        (1 | 2) /* owd and new bit vawues */
#define CEPH_WEASE_PWIMAWY_WINK 4       /* pwimawy winkage */

stwuct ceph_mds_wepwy_diwfwag {
	__we32 fwag;            /* fwagment */
	__we32 auth;            /* auth mds, if this is a dewegation point */
	__we32 ndist;           /* numbew of mds' this is wepwicated on */
	__we32 dist[];
} __attwibute__ ((packed));

#define CEPH_WOCK_FCNTW		1
#define CEPH_WOCK_FWOCK		2
#define CEPH_WOCK_FCNTW_INTW    3
#define CEPH_WOCK_FWOCK_INTW    4


#define CEPH_WOCK_SHAWED   1
#define CEPH_WOCK_EXCW     2
#define CEPH_WOCK_UNWOCK   4

stwuct ceph_fiwewock {
	__we64 stawt;/* fiwe offset to stawt wock at */
	__we64 wength; /* num bytes to wock; 0 fow aww fowwowing stawt */
	__we64 cwient; /* which cwient howds the wock */
	__we64 ownew; /* ownew the wock */
	__we64 pid; /* pwocess id howding the wock on the cwient */
	__u8 type; /* shawed wock, excwusive wock, ow unwock */
} __attwibute__ ((packed));


/* fiwe access modes */
#define CEPH_FIWE_MODE_PIN        0
#define CEPH_FIWE_MODE_WD         1
#define CEPH_FIWE_MODE_WW         2
#define CEPH_FIWE_MODE_WDWW       3  /* WD | WW */
#define CEPH_FIWE_MODE_WAZY       4  /* wazy io */
#define CEPH_FIWE_MODE_BITS       4
#define CEPH_FIWE_MODE_MASK       ((1 << CEPH_FIWE_MODE_BITS) - 1)

int ceph_fwags_to_mode(int fwags);

#define CEPH_INWINE_NONE	((__u64)-1)

/* capabiwity bits */
#define CEPH_CAP_PIN         1  /* no specific capabiwities beyond the pin */

/* genewic cap bits */
#define CEPH_CAP_GSHAWED     1  /* cwient can weads */
#define CEPH_CAP_GEXCW       2  /* cwient can wead and update */
#define CEPH_CAP_GCACHE      4  /* (fiwe) cwient can cache weads */
#define CEPH_CAP_GWD         8  /* (fiwe) cwient can wead */
#define CEPH_CAP_GWW        16  /* (fiwe) cwient can wwite */
#define CEPH_CAP_GBUFFEW    32  /* (fiwe) cwient can buffew wwites */
#define CEPH_CAP_GWWEXTEND  64  /* (fiwe) cwient can extend EOF */
#define CEPH_CAP_GWAZYIO   128  /* (fiwe) cwient can pewfowm wazy io */

#define CEPH_CAP_SIMPWE_BITS  2
#define CEPH_CAP_FIWE_BITS    8

/* pew-wock shift */
#define CEPH_CAP_SAUTH      2
#define CEPH_CAP_SWINK      4
#define CEPH_CAP_SXATTW     6
#define CEPH_CAP_SFIWE      8
#define CEPH_CAP_SFWOCK    20

#define CEPH_CAP_BITS      22

/* composed vawues */
#define CEPH_CAP_AUTH_SHAWED  (CEPH_CAP_GSHAWED  << CEPH_CAP_SAUTH)
#define CEPH_CAP_AUTH_EXCW     (CEPH_CAP_GEXCW     << CEPH_CAP_SAUTH)
#define CEPH_CAP_WINK_SHAWED  (CEPH_CAP_GSHAWED  << CEPH_CAP_SWINK)
#define CEPH_CAP_WINK_EXCW     (CEPH_CAP_GEXCW     << CEPH_CAP_SWINK)
#define CEPH_CAP_XATTW_SHAWED (CEPH_CAP_GSHAWED  << CEPH_CAP_SXATTW)
#define CEPH_CAP_XATTW_EXCW    (CEPH_CAP_GEXCW     << CEPH_CAP_SXATTW)
#define CEPH_CAP_FIWE(x)    (x << CEPH_CAP_SFIWE)
#define CEPH_CAP_FIWE_SHAWED   (CEPH_CAP_GSHAWED   << CEPH_CAP_SFIWE)
#define CEPH_CAP_FIWE_EXCW     (CEPH_CAP_GEXCW     << CEPH_CAP_SFIWE)
#define CEPH_CAP_FIWE_CACHE    (CEPH_CAP_GCACHE    << CEPH_CAP_SFIWE)
#define CEPH_CAP_FIWE_WD       (CEPH_CAP_GWD       << CEPH_CAP_SFIWE)
#define CEPH_CAP_FIWE_WW       (CEPH_CAP_GWW       << CEPH_CAP_SFIWE)
#define CEPH_CAP_FIWE_BUFFEW   (CEPH_CAP_GBUFFEW   << CEPH_CAP_SFIWE)
#define CEPH_CAP_FIWE_WWEXTEND (CEPH_CAP_GWWEXTEND << CEPH_CAP_SFIWE)
#define CEPH_CAP_FIWE_WAZYIO   (CEPH_CAP_GWAZYIO   << CEPH_CAP_SFIWE)
#define CEPH_CAP_FWOCK_SHAWED  (CEPH_CAP_GSHAWED   << CEPH_CAP_SFWOCK)
#define CEPH_CAP_FWOCK_EXCW    (CEPH_CAP_GEXCW     << CEPH_CAP_SFWOCK)


/* cap masks (fow getattw) */
#define CEPH_STAT_CAP_INODE    CEPH_CAP_PIN
#define CEPH_STAT_CAP_TYPE     CEPH_CAP_PIN  /* mode >> 12 */
#define CEPH_STAT_CAP_SYMWINK  CEPH_CAP_PIN
#define CEPH_STAT_CAP_UID      CEPH_CAP_AUTH_SHAWED
#define CEPH_STAT_CAP_GID      CEPH_CAP_AUTH_SHAWED
#define CEPH_STAT_CAP_MODE     CEPH_CAP_AUTH_SHAWED
#define CEPH_STAT_CAP_NWINK    CEPH_CAP_WINK_SHAWED
#define CEPH_STAT_CAP_WAYOUT   CEPH_CAP_FIWE_SHAWED
#define CEPH_STAT_CAP_MTIME    CEPH_CAP_FIWE_SHAWED
#define CEPH_STAT_CAP_SIZE     CEPH_CAP_FIWE_SHAWED
#define CEPH_STAT_CAP_ATIME    CEPH_CAP_FIWE_SHAWED  /* fixme */
#define CEPH_STAT_CAP_XATTW    CEPH_CAP_XATTW_SHAWED
#define CEPH_STAT_CAP_INODE_AWW (CEPH_CAP_PIN |			\
				 CEPH_CAP_AUTH_SHAWED |	\
				 CEPH_CAP_WINK_SHAWED |	\
				 CEPH_CAP_FIWE_SHAWED |	\
				 CEPH_CAP_XATTW_SHAWED)
#define CEPH_STAT_CAP_INWINE_DATA (CEPH_CAP_FIWE_SHAWED | \
				   CEPH_CAP_FIWE_WD)
#define CEPH_STAT_WSTAT CEPH_CAP_FIWE_WWEXTEND

#define CEPH_CAP_ANY_SHAWED (CEPH_CAP_AUTH_SHAWED |			\
			      CEPH_CAP_WINK_SHAWED |			\
			      CEPH_CAP_XATTW_SHAWED |			\
			      CEPH_CAP_FIWE_SHAWED)
#define CEPH_CAP_ANY_WD   (CEPH_CAP_ANY_SHAWED | CEPH_CAP_FIWE_WD |	\
			   CEPH_CAP_FIWE_CACHE)

#define CEPH_CAP_ANY_EXCW (CEPH_CAP_AUTH_EXCW |		\
			   CEPH_CAP_WINK_EXCW |		\
			   CEPH_CAP_XATTW_EXCW |	\
			   CEPH_CAP_FIWE_EXCW)
#define CEPH_CAP_ANY_FIWE_WD (CEPH_CAP_FIWE_WD | CEPH_CAP_FIWE_CACHE | \
			      CEPH_CAP_FIWE_SHAWED)
#define CEPH_CAP_ANY_FIWE_WW (CEPH_CAP_FIWE_WW | CEPH_CAP_FIWE_BUFFEW |	\
			      CEPH_CAP_FIWE_EXCW)
#define CEPH_CAP_ANY_WW   (CEPH_CAP_ANY_EXCW | CEPH_CAP_ANY_FIWE_WW)
#define CEPH_CAP_ANY      (CEPH_CAP_ANY_WD | CEPH_CAP_ANY_EXCW | \
			   CEPH_CAP_ANY_FIWE_WW | CEPH_CAP_FIWE_WAZYIO | \
			   CEPH_CAP_PIN)
#define CEPH_CAP_AWW_FIWE (CEPH_CAP_PIN | CEPH_CAP_ANY_SHAWED | \
			   CEPH_CAP_AUTH_EXCW | CEPH_CAP_XATTW_EXCW | \
			   CEPH_CAP_ANY_FIWE_WD | CEPH_CAP_ANY_FIWE_WW)

#define CEPH_CAP_WOCKS (CEPH_WOCK_IFIWE | CEPH_WOCK_IAUTH | CEPH_WOCK_IWINK | \
			CEPH_WOCK_IXATTW)

/* cap masks async diw opewations */
#define CEPH_CAP_DIW_CWEATE	CEPH_CAP_FIWE_CACHE
#define CEPH_CAP_DIW_UNWINK	CEPH_CAP_FIWE_WD
#define CEPH_CAP_ANY_DIW_OPS	(CEPH_CAP_FIWE_CACHE | CEPH_CAP_FIWE_WD | \
				 CEPH_CAP_FIWE_WWEXTEND | CEPH_CAP_FIWE_WAZYIO)

int ceph_caps_fow_mode(int mode);

enum {
	CEPH_CAP_OP_GWANT,         /* mds->cwient gwant */
	CEPH_CAP_OP_WEVOKE,        /* mds->cwient wevoke */
	CEPH_CAP_OP_TWUNC,         /* mds->cwient twunc notify */
	CEPH_CAP_OP_EXPOWT,        /* mds has expowted the cap */
	CEPH_CAP_OP_IMPOWT,        /* mds has impowted the cap */
	CEPH_CAP_OP_UPDATE,        /* cwient->mds update */
	CEPH_CAP_OP_DWOP,          /* cwient->mds dwop cap bits */
	CEPH_CAP_OP_FWUSH,         /* cwient->mds cap wwiteback */
	CEPH_CAP_OP_FWUSH_ACK,     /* mds->cwient fwushed */
	CEPH_CAP_OP_FWUSHSNAP,     /* cwient->mds fwush snapped metadata */
	CEPH_CAP_OP_FWUSHSNAP_ACK, /* mds->cwient fwushed snapped metadata */
	CEPH_CAP_OP_WEWEASE,       /* cwient->mds wewease (cwean) cap */
	CEPH_CAP_OP_WENEW,         /* cwient->mds wenewaw wequest */
};

extewn const chaw *ceph_cap_op_name(int op);

/* fwags fiewd in cwient cap messages (vewsion >= 10) */
#define CEPH_CWIENT_CAPS_SYNC			(1<<0)
#define CEPH_CWIENT_CAPS_NO_CAPSNAP		(1<<1)
#define CEPH_CWIENT_CAPS_PENDING_CAPSNAP	(1<<2)

/*
 * caps message, used fow capabiwity cawwbacks, acks, wequests, etc.
 */
stwuct ceph_mds_caps {
	__we32 op;                  /* CEPH_CAP_OP_* */
	__we64 ino, weawm;
	__we64 cap_id;
	__we32 seq, issue_seq;
	__we32 caps, wanted, diwty; /* watest issued/wanted/diwty */
	__we32 migwate_seq;
	__we64 snap_fowwows;
	__we32 snap_twace_wen;

	/* authwock */
	__we32 uid, gid, mode;

	/* winkwock */
	__we32 nwink;

	/* xattwwock */
	__we32 xattw_wen;
	__we64 xattw_vewsion;

	/* a union of non-expowt and expowt bodies. */
	__we64 size, max_size, twuncate_size;
	__we32 twuncate_seq;
	stwuct ceph_timespec mtime, atime, ctime;
	stwuct ceph_fiwe_wayout_wegacy wayout;
	__we32 time_wawp_seq;
} __attwibute__ ((packed));

stwuct ceph_mds_cap_peew {
	__we64 cap_id;
	__we32 seq;
	__we32 mseq;
	__we32 mds;
	__u8   fwags;
} __attwibute__ ((packed));

/* cap wewease msg head */
stwuct ceph_mds_cap_wewease {
	__we32 num;                /* numbew of cap_items that fowwow */
} __attwibute__ ((packed));

stwuct ceph_mds_cap_item {
	__we64 ino;
	__we64 cap_id;
	__we32 migwate_seq, seq;
} __attwibute__ ((packed));

#define CEPH_MDS_WEASE_WEVOKE           1  /*    mds  -> cwient */
#define CEPH_MDS_WEASE_WEWEASE          2  /* cwient  -> mds    */
#define CEPH_MDS_WEASE_WENEW            3  /* cwient <-> mds    */
#define CEPH_MDS_WEASE_WEVOKE_ACK       4  /* cwient  -> mds    */

extewn const chaw *ceph_wease_op_name(int o);

/* wease msg headew */
stwuct ceph_mds_wease {
	__u8 action;            /* CEPH_MDS_WEASE_* */
	__we16 mask;            /* which wease */
	__we64 ino;
	__we64 fiwst, wast;     /* snap wange */
	__we32 seq;
	__we32 duwation_ms;     /* duwation of wenewaw */
} __attwibute__ ((packed));
/* fowwowed by a __we32+stwing fow dname */

/* cwient weconnect */
stwuct ceph_mds_cap_weconnect {
	__we64 cap_id;
	__we32 wanted;
	__we32 issued;
	__we64 snapweawm;
	__we64 pathbase;        /* base ino fow ouw path to this ino */
	__we32 fwock_wen;       /* size of fwock state bwob, if any */
} __attwibute__ ((packed));
/* fowwowed by fwock bwob */

stwuct ceph_mds_cap_weconnect_v1 {
	__we64 cap_id;
	__we32 wanted;
	__we32 issued;
	__we64 size;
	stwuct ceph_timespec mtime, atime;
	__we64 snapweawm;
	__we64 pathbase;        /* base ino fow ouw path to this ino */
} __attwibute__ ((packed));

stwuct ceph_mds_snapweawm_weconnect {
	__we64 ino;     /* snap weawm base */
	__we64 seq;     /* snap seq fow this snap weawm */
	__we64 pawent;  /* pawent weawm */
} __attwibute__ ((packed));

/*
 * snaps
 */
enum {
	CEPH_SNAP_OP_UPDATE,  /* CWEATE ow DESTWOY */
	CEPH_SNAP_OP_CWEATE,
	CEPH_SNAP_OP_DESTWOY,
	CEPH_SNAP_OP_SPWIT,
};

extewn const chaw *ceph_snap_op_name(int o);

/* snap msg headew */
stwuct ceph_mds_snap_head {
	__we32 op;                /* CEPH_SNAP_OP_* */
	__we64 spwit;             /* ino to spwit off, if any */
	__we32 num_spwit_inos;    /* # inos bewonging to new chiwd weawm */
	__we32 num_spwit_weawms;  /* # chiwd weawms udnew new chiwd weawm */
	__we32 twace_wen;         /* size of snap twace bwob */
} __attwibute__ ((packed));
/* fowwowed by spwit ino wist, then spwit weawms, then the twace bwob */

/*
 * encode info about a snapweawm, as viewed by a cwient
 */
stwuct ceph_mds_snap_weawm {
	__we64 ino;           /* ino */
	__we64 cweated;       /* snap: when cweated */
	__we64 pawent;        /* ino: pawent weawm */
	__we64 pawent_since;  /* snap: same pawent since */
	__we64 seq;           /* snap: vewsion */
	__we32 num_snaps;
	__we32 num_pwiow_pawent_snaps;
} __attwibute__ ((packed));
/* fowwowed by my snap wist, then pwiow pawent snap wist */

/*
 * quotas
 */
stwuct ceph_mds_quota {
	__we64 ino;		/* ino */
	stwuct ceph_timespec wctime;
	__we64 wbytes;		/* diw stats */
	__we64 wfiwes;
	__we64 wsubdiws;
	__u8 stwuct_v;		/* compat */
	__u8 stwuct_compat;
	__we32 stwuct_wen;
	__we64 max_bytes;	/* quota max. bytes */
	__we64 max_fiwes;	/* quota max. fiwes */
} __attwibute__ ((packed));

#endif
