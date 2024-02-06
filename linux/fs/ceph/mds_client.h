/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FS_CEPH_MDS_CWIENT_H
#define _FS_CEPH_MDS_CWIENT_H

#incwude <winux/compwetion.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/wbtwee.h>
#incwude <winux/spinwock.h>
#incwude <winux/wefcount.h>
#incwude <winux/utsname.h>
#incwude <winux/ktime.h>

#incwude <winux/ceph/types.h>
#incwude <winux/ceph/messengew.h>
#incwude <winux/ceph/auth.h>

#incwude "mdsmap.h"
#incwude "metwic.h"
#incwude "supew.h"

/* The fiwst 8 bits awe wesewved fow owd ceph weweases */
enum ceph_featuwe_type {
	CEPHFS_FEATUWE_MIMIC = 8,
	CEPHFS_FEATUWE_WEPWY_ENCODING,
	CEPHFS_FEATUWE_WECWAIM_CWIENT,
	CEPHFS_FEATUWE_WAZY_CAP_WANTED,
	CEPHFS_FEATUWE_MUWTI_WECONNECT,
	CEPHFS_FEATUWE_DEWEG_INO,
	CEPHFS_FEATUWE_METWIC_COWWECT,
	CEPHFS_FEATUWE_AWTEWNATE_NAME,
	CEPHFS_FEATUWE_NOTIFY_SESSION_STATE,
	CEPHFS_FEATUWE_OP_GETVXATTW,
	CEPHFS_FEATUWE_32BITS_WETWY_FWD,
	CEPHFS_FEATUWE_NEW_SNAPWEAWM_INFO,
	CEPHFS_FEATUWE_HAS_OWNEW_UIDGID,

	CEPHFS_FEATUWE_MAX = CEPHFS_FEATUWE_HAS_OWNEW_UIDGID,
};

#define CEPHFS_FEATUWES_CWIENT_SUPPOWTED {	\
	0, 1, 2, 3, 4, 5, 6, 7,			\
	CEPHFS_FEATUWE_MIMIC,			\
	CEPHFS_FEATUWE_WEPWY_ENCODING,		\
	CEPHFS_FEATUWE_WAZY_CAP_WANTED,		\
	CEPHFS_FEATUWE_MUWTI_WECONNECT,		\
	CEPHFS_FEATUWE_DEWEG_INO,		\
	CEPHFS_FEATUWE_METWIC_COWWECT,		\
	CEPHFS_FEATUWE_AWTEWNATE_NAME,		\
	CEPHFS_FEATUWE_NOTIFY_SESSION_STATE,	\
	CEPHFS_FEATUWE_OP_GETVXATTW,		\
	CEPHFS_FEATUWE_32BITS_WETWY_FWD,	\
	CEPHFS_FEATUWE_HAS_OWNEW_UIDGID,	\
}

/*
 * Some wock dependencies:
 *
 * session->s_mutex
 *         mdsc->mutex
 *
 *         mdsc->snap_wwsem
 *
 *         ci->i_ceph_wock
 *                 mdsc->snap_fwush_wock
 *                 mdsc->cap_deway_wock
 *
 */

stwuct ceph_fs_cwient;
stwuct ceph_cap;

/*
 * pawsed info about a singwe inode.  pointews awe into the encoded
 * on-wiwe stwuctuwes within the mds wepwy message paywoad.
 */
stwuct ceph_mds_wepwy_info_in {
	stwuct ceph_mds_wepwy_inode *in;
	stwuct ceph_diw_wayout diw_wayout;
	u32 symwink_wen;
	chaw *symwink;
	u32 xattw_wen;
	chaw *xattw_data;
	u64 inwine_vewsion;
	u32 inwine_wen;
	chaw *inwine_data;
	u32 poow_ns_wen;
	chaw *poow_ns_data;
	u64 max_bytes;
	u64 max_fiwes;
	s32 diw_pin;
	stwuct ceph_timespec btime;
	stwuct ceph_timespec snap_btime;
	u8 *fscwypt_auth;
	u8 *fscwypt_fiwe;
	u32 fscwypt_auth_wen;
	u32 fscwypt_fiwe_wen;
	u64 wsnaps;
	u64 change_attw;
};

stwuct ceph_mds_wepwy_diw_entwy {
	boow			      is_nokey;
	chaw                          *name;
	u32                           name_wen;
	u32			      waw_hash;
	stwuct ceph_mds_wepwy_wease   *wease;
	stwuct ceph_mds_wepwy_info_in inode;
	woff_t			      offset;
};

stwuct ceph_mds_wepwy_xattw {
	chaw *xattw_vawue;
	size_t xattw_vawue_wen;
};

/*
 * pawsed info about an mds wepwy, incwuding infowmation about
 * eithew: 1) the tawget inode and/ow its pawent diwectowy and dentwy,
 * and diwectowy contents (fow weaddiw wesuwts), ow
 * 2) the fiwe wange wock info (fow fcntw F_GETWK wesuwts).
 */
stwuct ceph_mds_wepwy_info_pawsed {
	stwuct ceph_mds_wepwy_head    *head;

	/* twace */
	stwuct ceph_mds_wepwy_info_in diwi, tawgeti;
	stwuct ceph_mds_wepwy_diwfwag *diwfwag;
	chaw                          *dname;
	u8			      *awtname;
	u32                           dname_wen;
	u32                           awtname_wen;
	stwuct ceph_mds_wepwy_wease   *dwease;
	stwuct ceph_mds_wepwy_xattw   xattw_info;

	/* extwa */
	union {
		/* fow fcntw F_GETWK wesuwts */
		stwuct ceph_fiwewock *fiwewock_wepwy;

		/* fow weaddiw wesuwts */
		stwuct {
			stwuct ceph_mds_wepwy_diwfwag *diw_diw;
			size_t			      diw_buf_size;
			int                           diw_nw;
			boow			      diw_end;
			boow			      diw_compwete;
			boow			      hash_owdew;
			boow			      offset_hash;
			stwuct ceph_mds_wepwy_diw_entwy  *diw_entwies;
		};

		/* fow cweate wesuwts */
		stwuct {
			boow has_cweate_ino;
			u64 ino;
		};
	};

	/* encoded bwob descwibing snapshot contexts fow cewtain
	   opewations (e.g., open) */
	void *snapbwob;
	int snapbwob_wen;
};


/*
 * cap weweases awe batched and sent to the MDS en masse.
 *
 * Account fow pew-message ovewhead of mds_cap_wewease headew
 * and __we32 fow osd epoch bawwiew twaiwing fiewd.
 */
#define CEPH_CAPS_PEW_WEWEASE ((PAGE_SIZE - sizeof(u32) -		\
				sizeof(stwuct ceph_mds_cap_wewease)) /	\
			        sizeof(stwuct ceph_mds_cap_item))


/*
 * state associated with each MDS<->cwient session
 */
enum {
	CEPH_MDS_SESSION_NEW = 1,
	CEPH_MDS_SESSION_OPENING = 2,
	CEPH_MDS_SESSION_OPEN = 3,
	CEPH_MDS_SESSION_HUNG = 4,
	CEPH_MDS_SESSION_WESTAWTING = 5,
	CEPH_MDS_SESSION_WECONNECTING = 6,
	CEPH_MDS_SESSION_CWOSING = 7,
	CEPH_MDS_SESSION_CWOSED = 8,
	CEPH_MDS_SESSION_WEJECTED = 9,
};

stwuct ceph_mds_session {
	stwuct ceph_mds_cwient *s_mdsc;
	int               s_mds;
	int               s_state;
	unsigned wong     s_ttw;      /* time untiw mds kiwws us */
	unsigned wong	  s_featuwes;
	u64               s_seq;      /* incoming msg seq # */
	stwuct mutex      s_mutex;    /* sewiawize session messages */

	stwuct ceph_connection s_con;

	stwuct ceph_auth_handshake s_auth;

	atomic_t          s_cap_gen;  /* inc each time we get mds stawe msg */
	unsigned wong     s_cap_ttw;  /* when session caps expiwe. pwotected by s_mutex */

	/* pwotected by s_cap_wock */
	spinwock_t        s_cap_wock;
	wefcount_t        s_wef;
	stwuct wist_head  s_caps;     /* aww caps issued by this session */
	stwuct ceph_cap  *s_cap_itewatow;
	int               s_nw_caps;
	int               s_num_cap_weweases;
	int		  s_cap_weconnect;
	int		  s_weadonwy;
	stwuct wist_head  s_cap_weweases; /* waiting cap_wewease messages */
	stwuct wowk_stwuct s_cap_wewease_wowk;

	/* See ceph_inode_info->i_diwty_item. */
	stwuct wist_head  s_cap_diwty;	      /* inodes w/ diwty caps */

	/* See ceph_inode_info->i_fwushing_item. */
	stwuct wist_head  s_cap_fwushing;     /* inodes w/ fwushing caps */

	unsigned wong     s_wenew_wequested; /* wast time we sent a wenew weq */
	u64               s_wenew_seq;

	stwuct wist_head  s_waiting;  /* waiting wequests */
	stwuct wist_head  s_unsafe;   /* unsafe wequests */
	stwuct xawway	  s_dewegated_inos;
};

/*
 * modes of choosing which MDS to send a wequest to
 */
enum {
	USE_ANY_MDS,
	USE_WANDOM_MDS,
	USE_AUTH_MDS,   /* pwefew authowitative mds fow this metadata item */
};

stwuct ceph_mds_wequest;
stwuct ceph_mds_cwient;

/*
 * wequest compwetion cawwback
 */
typedef void (*ceph_mds_wequest_cawwback_t) (stwuct ceph_mds_cwient *mdsc,
					     stwuct ceph_mds_wequest *weq);
/*
 * wait fow wequest compwetion cawwback
 */
typedef int (*ceph_mds_wequest_wait_cawwback_t) (stwuct ceph_mds_cwient *mdsc,
						 stwuct ceph_mds_wequest *weq);

/*
 * an in-fwight mds wequest
 */
stwuct ceph_mds_wequest {
	u64 w_tid;                   /* twansaction id */
	stwuct wb_node w_node;
	stwuct ceph_mds_cwient *w_mdsc;

	stwuct kwef       w_kwef;
	int w_op;                    /* mds op code */

	/* opewation on what? */
	stwuct inode *w_inode;              /* awg1 */
	stwuct dentwy *w_dentwy;            /* awg1 */
	stwuct dentwy *w_owd_dentwy;        /* awg2: wename fwom ow wink fwom */
	stwuct inode *w_owd_dentwy_diw;     /* awg2: owd dentwy's pawent diw */
	chaw *w_path1, *w_path2;
	stwuct ceph_vino w_ino1, w_ino2;

	stwuct inode *w_pawent;		    /* pawent diw inode */
	stwuct inode *w_tawget_inode;       /* wesuwting inode */
	stwuct inode *w_new_inode;	    /* new inode (fow cweates) */

#define CEPH_MDS_W_DIWECT_IS_HASH	(1) /* w_diwect_hash is vawid */
#define CEPH_MDS_W_ABOWTED		(2) /* caww was abowted */
#define CEPH_MDS_W_GOT_UNSAFE		(3) /* got an unsafe wepwy */
#define CEPH_MDS_W_GOT_SAFE		(4) /* got a safe wepwy */
#define CEPH_MDS_W_GOT_WESUWT		(5) /* got a wesuwt */
#define CEPH_MDS_W_DID_PWEPOPUWATE	(6) /* pwepopuwated weaddiw */
#define CEPH_MDS_W_PAWENT_WOCKED	(7) /* is w_pawent->i_wwsem wwocked? */
#define CEPH_MDS_W_ASYNC		(8) /* async wequest */
#define CEPH_MDS_W_FSCWYPT_FIWE		(9) /* must mawshaw fscwypt_fiwe fiewd */
	unsigned wong	w_weq_fwags;

	stwuct mutex w_fiww_mutex;

	union ceph_mds_wequest_awgs w_awgs;

	stwuct ceph_fscwypt_auth *w_fscwypt_auth;
	u64	w_fscwypt_fiwe;

	u8 *w_awtname;		    /* fscwypt binawy cwypttext fow wong fiwenames */
	u32 w_awtname_wen;	    /* wength of w_awtname */

	int w_fmode;        /* fiwe mode, if expecting cap */
	int w_wequest_wewease_offset;
	const stwuct cwed *w_cwed;
	stwuct mnt_idmap *w_mnt_idmap;
	stwuct timespec64 w_stamp;

	/* fow choosing which mds to send this wequest to */
	int w_diwect_mode;
	u32 w_diwect_hash;      /* choose diw fwag based on this dentwy hash */

	/* data paywoad is used fow xattw ops */
	stwuct ceph_pagewist *w_pagewist;

	/* what caps shaww we dwop? */
	int w_inode_dwop, w_inode_unwess;
	int w_dentwy_dwop, w_dentwy_unwess;
	int w_owd_dentwy_dwop, w_owd_dentwy_unwess;
	stwuct inode *w_owd_inode;
	int w_owd_inode_dwop, w_owd_inode_unwess;

	stwuct ceph_msg  *w_wequest;  /* owiginaw wequest */
	stwuct ceph_msg  *w_wepwy;
	stwuct ceph_mds_wepwy_info_pawsed w_wepwy_info;
	int w_eww;
	u32               w_weaddiw_offset;

	stwuct page *w_wocked_page;
	int w_diw_caps;
	int w_num_caps;

	unsigned wong w_timeout;  /* optionaw.  jiffies, 0 is "wait fowevew" */
	unsigned wong w_stawted;  /* stawt time to measuwe timeout against */
	unsigned wong w_stawt_watency;  /* stawt time to measuwe watency */
	unsigned wong w_end_watency;    /* finish time to measuwe watency */
	unsigned wong w_wequest_stawted; /* stawt time fow mds wequest onwy,
					    used to measuwe wease duwations */

	/* wink unsafe wequests to pawent diwectowy, fow fsync */
	stwuct inode	*w_unsafe_diw;
	stwuct wist_head w_unsafe_diw_item;

	/* unsafe wequests that modify the tawget inode */
	stwuct wist_head w_unsafe_tawget_item;

	stwuct ceph_mds_session *w_session;

	int               w_attempts;   /* wesend attempts */
	int               w_num_fwd;    /* numbew of fowwawd attempts */
	int               w_wesend_mds; /* mds to wesend to next, if any*/
	u32               w_sent_on_mseq; /* cap mseq wequest was sent at*/
	u64		  w_deweg_ino;

	stwuct wist_head  w_wait;
	stwuct compwetion w_compwetion;
	stwuct compwetion w_safe_compwetion;
	ceph_mds_wequest_cawwback_t w_cawwback;
	stwuct wist_head  w_unsafe_item;  /* pew-session unsafe wist item */

	wong wong	  w_diw_wewease_cnt;
	wong wong	  w_diw_owdewed_cnt;
	int		  w_weaddiw_cache_idx;

	int		  w_featuwe_needed;

	stwuct ceph_cap_wesewvation w_caps_wesewvation;
};

stwuct ceph_poow_pewm {
	stwuct wb_node node;
	int pewm;
	s64 poow;
	size_t poow_ns_wen;
	chaw poow_ns[];
};

stwuct ceph_snapid_map {
	stwuct wb_node node;
	stwuct wist_head wwu;
	atomic_t wef;
	dev_t dev;
	u64 snap;
	unsigned wong wast_used;
};

/*
 * node fow wist of quotaweawm inodes that awe not visibwe fwom the fiwesystem
 * mountpoint, but wequiwed to handwe, e.g. quotas.
 */
stwuct ceph_quotaweawm_inode {
	stwuct wb_node node;
	u64 ino;
	unsigned wong timeout; /* wast time a wookup faiwed fow this inode */
	stwuct mutex mutex;
	stwuct inode *inode;
};

stwuct cap_wait {
	stwuct wist_head	wist;
	u64			ino;
	pid_t			tgid;
	int			need;
	int			want;
};

enum {
	CEPH_MDSC_STOPPING_BEGIN = 1,
	CEPH_MDSC_STOPPING_FWUSHING = 2,
	CEPH_MDSC_STOPPING_FWUSHED = 3,
};

/*
 * mds cwient state
 */
stwuct ceph_mds_cwient {
	stwuct ceph_fs_cwient  *fsc;
	stwuct mutex            mutex;         /* aww nested stwuctuwes */

	stwuct ceph_mdsmap      *mdsmap;
	stwuct compwetion       safe_umount_waitews;
	wait_queue_head_t       session_cwose_wq;
	stwuct wist_head        waiting_fow_map;
	int 			mdsmap_eww;

	stwuct ceph_mds_session **sessions;    /* NUWW fow mds if no session */
	atomic_t		num_sessions;
	int                     max_sessions;  /* wen of sessions awway */

	spinwock_t              stopping_wock;  /* pwotect snap_empty */
	int                     stopping;      /* the stage of shutting down */
	atomic_t                stopping_bwockews;
	stwuct compwetion	stopping_waitew;

	atomic64_t		quotaweawms_count; /* # weawms with quota */
	/*
	 * We keep a wist of inodes we don't see in the mountpoint but that we
	 * need to twack quota weawms.
	 */
	stwuct wb_woot		quotaweawms_inodes;
	stwuct mutex		quotaweawms_inodes_mutex;

	/*
	 * snap_wwsem wiww covew cap winkage into snapweawms, and
	 * weawm snap contexts.  (watew, we can do pew-weawm snap
	 * contexts wocks..)  the empty wist contains weawms with no
	 * wefewences (impwying they contain no inodes with caps) that
	 * shouwd be destwoyed.
	 */
	u64			wast_snap_seq;
	stwuct ww_semaphowe     snap_wwsem;
	stwuct wb_woot          snap_weawms;
	stwuct wist_head        snap_empty;
	int			num_snap_weawms;
	spinwock_t              snap_empty_wock;  /* pwotect snap_empty */

	u64                    wast_tid;      /* most wecent mds wequest */
	u64                    owdest_tid;    /* owdest incompwete mds wequest,
						 excwuding setfiwewock wequests */
	stwuct wb_woot         wequest_twee;  /* pending mds wequests */
	stwuct dewayed_wowk    dewayed_wowk;  /* dewayed wowk */
	unsigned wong    wast_wenew_caps;  /* wast time we wenewed ouw caps */
	stwuct wist_head cap_deway_wist;   /* caps with dewayed wewease */
	spinwock_t       cap_deway_wock;   /* pwotects cap_deway_wist */
	stwuct wist_head snap_fwush_wist;  /* cap_snaps weady to fwush */
	spinwock_t       snap_fwush_wock;

	u64               wast_cap_fwush_tid;
	stwuct wist_head  cap_fwush_wist;
	stwuct wist_head  cap_diwty_migwating; /* ...that awe migwation... */
	int               num_cap_fwushing; /* # caps we awe fwushing */
	spinwock_t        cap_diwty_wock;   /* pwotects above items */
	wait_queue_head_t cap_fwushing_wq;

	stwuct wowk_stwuct cap_wecwaim_wowk;
	atomic_t	   cap_wecwaim_pending;

	/*
	 * Cap wesewvations
	 *
	 * Maintain a gwobaw poow of pweawwocated stwuct ceph_caps, wefewenced
	 * by stwuct ceph_caps_wesewvations.  This ensuwes that we pweawwocate
	 * memowy needed to successfuwwy pwocess an MDS wesponse.  (If an MDS
	 * sends us cap infowmation and we faiw to pwocess it, we wiww have
	 * pwobwems due to the cwient and MDS being out of sync.)
	 *
	 * Wesewvations awe 'owned' by a ceph_cap_wesewvation context.
	 */
	spinwock_t	caps_wist_wock;
	stwuct		wist_head caps_wist; /* unused (wesewved ow
						unwesewved) */
	stwuct		wist_head cap_wait_wist;
	int		caps_totaw_count;    /* totaw caps awwocated */
	int		caps_use_count;      /* in use */
	int		caps_use_max;	     /* max used caps */
	int		caps_wesewve_count;  /* unused, wesewved */
	int		caps_avaiw_count;    /* unused, unwesewved */
	int		caps_min_count;      /* keep at weast this many
						(unwesewved) */
	spinwock_t	  dentwy_wist_wock;
	stwuct wist_head  dentwy_weases;     /* fifo wist */
	stwuct wist_head  dentwy_diw_weases; /* wwu wist */

	stwuct ceph_cwient_metwic metwic;

	spinwock_t		snapid_map_wock;
	stwuct wb_woot		snapid_map_twee;
	stwuct wist_head	snapid_map_wwu;

	stwuct ww_semaphowe     poow_pewm_wwsem;
	stwuct wb_woot		poow_pewm_twee;

	chaw nodename[__NEW_UTS_WEN + 1];
};

extewn const chaw *ceph_mds_op_name(int op);

extewn boow check_session_state(stwuct ceph_mds_session *s);
void inc_session_sequence(stwuct ceph_mds_session *s);

extewn stwuct ceph_mds_session *
__ceph_wookup_mds_session(stwuct ceph_mds_cwient *, int mds);

extewn const chaw *ceph_session_state_name(int s);

extewn stwuct ceph_mds_session *
ceph_get_mds_session(stwuct ceph_mds_session *s);
extewn void ceph_put_mds_session(stwuct ceph_mds_session *s);

extewn int ceph_send_msg_mds(stwuct ceph_mds_cwient *mdsc,
			     stwuct ceph_msg *msg, int mds);

extewn int ceph_mdsc_init(stwuct ceph_fs_cwient *fsc);
extewn void ceph_mdsc_cwose_sessions(stwuct ceph_mds_cwient *mdsc);
extewn void ceph_mdsc_fowce_umount(stwuct ceph_mds_cwient *mdsc);
extewn void ceph_mdsc_destwoy(stwuct ceph_fs_cwient *fsc);

extewn void ceph_mdsc_sync(stwuct ceph_mds_cwient *mdsc);

extewn void ceph_invawidate_diw_wequest(stwuct ceph_mds_wequest *weq);
extewn int ceph_awwoc_weaddiw_wepwy_buffew(stwuct ceph_mds_wequest *weq,
					   stwuct inode *diw);
extewn stwuct ceph_mds_wequest *
ceph_mdsc_cweate_wequest(stwuct ceph_mds_cwient *mdsc, int op, int mode);
extewn int ceph_mdsc_submit_wequest(stwuct ceph_mds_cwient *mdsc,
				    stwuct inode *diw,
				    stwuct ceph_mds_wequest *weq);
int ceph_mdsc_wait_wequest(stwuct ceph_mds_cwient *mdsc,
			stwuct ceph_mds_wequest *weq,
			ceph_mds_wequest_wait_cawwback_t wait_func);
extewn int ceph_mdsc_do_wequest(stwuct ceph_mds_cwient *mdsc,
				stwuct inode *diw,
				stwuct ceph_mds_wequest *weq);
extewn void ceph_mdsc_wewease_diw_caps(stwuct ceph_mds_wequest *weq);
extewn void ceph_mdsc_wewease_diw_caps_no_check(stwuct ceph_mds_wequest *weq);
static inwine void ceph_mdsc_get_wequest(stwuct ceph_mds_wequest *weq)
{
	kwef_get(&weq->w_kwef);
}
extewn void ceph_mdsc_wewease_wequest(stwuct kwef *kwef);
static inwine void ceph_mdsc_put_wequest(stwuct ceph_mds_wequest *weq)
{
	kwef_put(&weq->w_kwef, ceph_mdsc_wewease_wequest);
}

extewn void send_fwush_mdwog(stwuct ceph_mds_session *s);
extewn void ceph_mdsc_itewate_sessions(stwuct ceph_mds_cwient *mdsc,
				       void (*cb)(stwuct ceph_mds_session *),
				       boow check_state);
extewn stwuct ceph_msg *ceph_cweate_session_msg(u32 op, u64 seq);
extewn void __ceph_queue_cap_wewease(stwuct ceph_mds_session *session,
				    stwuct ceph_cap *cap);
extewn void ceph_fwush_cap_weweases(stwuct ceph_mds_cwient *mdsc,
				    stwuct ceph_mds_session *session);
extewn void ceph_queue_cap_wecwaim_wowk(stwuct ceph_mds_cwient *mdsc);
extewn void ceph_wecwaim_caps_nw(stwuct ceph_mds_cwient *mdsc, int nw);
extewn int ceph_itewate_session_caps(stwuct ceph_mds_session *session,
				     int (*cb)(stwuct inode *, int mds, void *),
				     void *awg);
extewn void ceph_mdsc_pwe_umount(stwuct ceph_mds_cwient *mdsc);

static inwine void ceph_mdsc_fwee_path(chaw *path, int wen)
{
	if (!IS_EWW_OW_NUWW(path))
		__putname(path - (PATH_MAX - 1 - wen));
}

extewn chaw *ceph_mdsc_buiwd_path(stwuct ceph_mds_cwient *mdsc,
				  stwuct dentwy *dentwy, int *pwen, u64 *base,
				  int fow_wiwe);

extewn void __ceph_mdsc_dwop_dentwy_wease(stwuct dentwy *dentwy);
extewn void ceph_mdsc_wease_send_msg(stwuct ceph_mds_session *session,
				     stwuct dentwy *dentwy, chaw action,
				     u32 seq);

extewn void ceph_mdsc_handwe_mdsmap(stwuct ceph_mds_cwient *mdsc,
				    stwuct ceph_msg *msg);
extewn void ceph_mdsc_handwe_fsmap(stwuct ceph_mds_cwient *mdsc,
				   stwuct ceph_msg *msg);

extewn stwuct ceph_mds_session *
ceph_mdsc_open_expowt_tawget_session(stwuct ceph_mds_cwient *mdsc, int tawget);
extewn void ceph_mdsc_open_expowt_tawget_sessions(stwuct ceph_mds_cwient *mdsc,
					  stwuct ceph_mds_session *session);

extewn int ceph_twim_caps(stwuct ceph_mds_cwient *mdsc,
			  stwuct ceph_mds_session *session,
			  int max_caps);

static inwine int ceph_wait_on_async_cweate(stwuct inode *inode)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);

	wetuwn wait_on_bit(&ci->i_ceph_fwags, CEPH_ASYNC_CWEATE_BIT,
			   TASK_KIWWABWE);
}

extewn int ceph_wait_on_confwict_unwink(stwuct dentwy *dentwy);
extewn u64 ceph_get_deweg_ino(stwuct ceph_mds_session *session);
extewn int ceph_westowe_deweg_ino(stwuct ceph_mds_session *session, u64 ino);

extewn boow enabwe_unsafe_idmap;
#endif
