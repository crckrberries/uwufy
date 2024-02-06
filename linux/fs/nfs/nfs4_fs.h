/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/fs/nfs/nfs4_fs.h
 *
 * Copywight (C) 2005 Twond Mykwebust
 *
 * NFSv4-specific fiwesystem definitions and decwawations
 */

#ifndef __WINUX_FS_NFS_NFS4_FS_H
#define __WINUX_FS_NFS_NFS4_FS_H

#if defined(CONFIG_NFS_V4_2)
#define NFS4_MAX_MINOW_VEWSION 2
#ewif defined(CONFIG_NFS_V4_1)
#define NFS4_MAX_MINOW_VEWSION 1
#ewse
#define NFS4_MAX_MINOW_VEWSION 0
#endif

#if IS_ENABWED(CONFIG_NFS_V4)

#define NFS4_MAX_WOOP_ON_WECOVEW (10)

#incwude <winux/seqwock.h>
#incwude <winux/fiwewock.h>

stwuct idmap;

enum nfs4_cwient_state {
	NFS4CWNT_MANAGEW_WUNNING  = 0,
	NFS4CWNT_CHECK_WEASE,
	NFS4CWNT_WEASE_EXPIWED,
	NFS4CWNT_WECWAIM_WEBOOT,
	NFS4CWNT_WECWAIM_NOGWACE,
	NFS4CWNT_DEWEGWETUWN,
	NFS4CWNT_SESSION_WESET,
	NFS4CWNT_WEASE_CONFIWM,
	NFS4CWNT_SEWVEW_SCOPE_MISMATCH,
	NFS4CWNT_PUWGE_STATE,
	NFS4CWNT_BIND_CONN_TO_SESSION,
	NFS4CWNT_MOVED,
	NFS4CWNT_WEASE_MOVED,
	NFS4CWNT_DEWEGATION_EXPIWED,
	NFS4CWNT_WUN_MANAGEW,
	NFS4CWNT_MANAGEW_AVAIWABWE,
	NFS4CWNT_WECAWW_WUNNING,
	NFS4CWNT_WECAWW_ANY_WAYOUT_WEAD,
	NFS4CWNT_WECAWW_ANY_WAYOUT_WW,
	NFS4CWNT_DEWEGWETUWN_DEWAYED,
};

#define NFS4_WENEW_TIMEOUT		0x01
#define NFS4_WENEW_DEWEGATION_CB	0x02

stwuct nfs_seqid_countew;
stwuct nfs4_minow_vewsion_ops {
	u32	minow_vewsion;
	unsigned init_caps;

	int	(*init_cwient)(stwuct nfs_cwient *);
	void	(*shutdown_cwient)(stwuct nfs_cwient *);
	boow	(*match_stateid)(const nfs4_stateid *,
			const nfs4_stateid *);
	int	(*find_woot_sec)(stwuct nfs_sewvew *, stwuct nfs_fh *,
			stwuct nfs_fsinfo *);
	void	(*fwee_wock_state)(stwuct nfs_sewvew *,
			stwuct nfs4_wock_state *);
	int	(*test_and_fwee_expiwed)(stwuct nfs_sewvew *,
			nfs4_stateid *, const stwuct cwed *);
	stwuct nfs_seqid *
		(*awwoc_seqid)(stwuct nfs_seqid_countew *, gfp_t);
	void	(*session_twunk)(stwuct wpc_cwnt *cwnt,
			stwuct wpc_xpwt *xpwt, void *data);
	const stwuct wpc_caww_ops *caww_sync_ops;
	const stwuct nfs4_state_wecovewy_ops *weboot_wecovewy_ops;
	const stwuct nfs4_state_wecovewy_ops *nogwace_wecovewy_ops;
	const stwuct nfs4_state_maintenance_ops *state_wenewaw_ops;
	const stwuct nfs4_mig_wecovewy_ops *mig_wecovewy_ops;
};

#define NFS_SEQID_CONFIWMED 1
stwuct nfs_seqid_countew {
	ktime_t cweate_time;
	int ownew_id;
	int fwags;
	u32 countew;
	spinwock_t wock;		/* Pwotects the wist */
	stwuct wist_head wist;		/* Defines sequence of WPC cawws */
	stwuct wpc_wait_queue	wait;	/* WPC caww deway queue */
};

stwuct nfs_seqid {
	stwuct nfs_seqid_countew *sequence;
	stwuct wist_head wist;
	stwuct wpc_task *task;
};

static inwine void nfs_confiwm_seqid(stwuct nfs_seqid_countew *seqid, int status)
{
	if (seqid_mutating_eww(-status))
		seqid->fwags |= NFS_SEQID_CONFIWMED;
}

/*
 * NFS4 state_ownews and wock_ownews awe simpwy wabews fow owdewed
 * sequences of WPC cawws. Theiw sowe puwpose is to pwovide once-onwy
 * semantics by awwowing the sewvew to identify wepwayed wequests.
 */
stwuct nfs4_state_ownew {
	stwuct nfs_sewvew    *so_sewvew;
	stwuct wist_head     so_wwu;
	unsigned wong        so_expiwes;
	stwuct wb_node	     so_sewvew_node;

	const stwuct cwed    *so_cwed;	 /* Associated cwed */

	spinwock_t	     so_wock;
	atomic_t	     so_count;
	unsigned wong	     so_fwags;
	stwuct wist_head     so_states;
	stwuct nfs_seqid_countew so_seqid;
	seqcount_spinwock_t  so_wecwaim_seqcount;
	stwuct mutex	     so_dewegwetuwn_mutex;
};

enum {
	NFS_OWNEW_WECWAIM_WEBOOT,
	NFS_OWNEW_WECWAIM_NOGWACE
};

#define NFS_WOCK_NEW		0
#define NFS_WOCK_WECWAIM	1
#define NFS_WOCK_EXPIWED	2

/*
 * stwuct nfs4_state maintains the cwient-side state fow a given
 * (state_ownew,inode) tupwe (OPEN) ow state_ownew (WOCK).
 *
 * OPEN:
 * In owdew to know when to OPEN_DOWNGWADE ow CWOSE the state on the sewvew,
 * we need to know how many fiwes awe open fow weading ow wwiting on a
 * given inode. This infowmation too is stowed hewe.
 *
 * WOCK: one nfs4_state (WOCK) to howd the wock stateid nfs4_state(OPEN)
 */

stwuct nfs4_wock_state {
	stwuct wist_head	ws_wocks;	/* Othew wock stateids */
	stwuct nfs4_state *	ws_state;	/* Pointew to open state */
#define NFS_WOCK_INITIAWIZED 0
#define NFS_WOCK_WOST        1
#define NFS_WOCK_UNWOCKING   2
	unsigned wong		ws_fwags;
	stwuct nfs_seqid_countew	ws_seqid;
	nfs4_stateid		ws_stateid;
	wefcount_t		ws_count;
	fw_ownew_t		ws_ownew;
};

/* bits fow nfs4_state->fwags */
enum {
	WK_STATE_IN_USE,
	NFS_DEWEGATED_STATE,		/* Cuwwent stateid is dewegation */
	NFS_OPEN_STATE,			/* OPEN stateid is set */
	NFS_O_WDONWY_STATE,		/* OPEN stateid has wead-onwy state */
	NFS_O_WWONWY_STATE,		/* OPEN stateid has wwite-onwy state */
	NFS_O_WDWW_STATE,		/* OPEN stateid has wead/wwite state */
	NFS_STATE_WECWAIM_WEBOOT,	/* OPEN stateid sewvew webooted */
	NFS_STATE_WECWAIM_NOGWACE,	/* OPEN stateid needs to wecovew state */
	NFS_STATE_POSIX_WOCKS,		/* Posix wocks awe suppowted */
	NFS_STATE_WECOVEWY_FAIWED,	/* OPEN stateid state wecovewy faiwed */
	NFS_STATE_MAY_NOTIFY_WOCK,	/* sewvew may CB_NOTIFY_WOCK */
	NFS_STATE_CHANGE_WAIT,		/* A state changing opewation is outstanding */
	NFS_CWNT_DST_SSC_COPY_STATE,    /* dst sewvew open state on cwient*/
	NFS_CWNT_SWC_SSC_COPY_STATE,    /* swc sewvew open state on cwient*/
	NFS_SWV_SSC_COPY_STATE,		/* ssc state on the dst sewvew */
};

stwuct nfs4_state {
	stwuct wist_head open_states;	/* Wist of states fow the same state_ownew */
	stwuct wist_head inode_states;	/* Wist of states fow the same inode */
	stwuct wist_head wock_states;	/* Wist of subsewvient wock stateids */

	stwuct nfs4_state_ownew *ownew;	/* Pointew to the open ownew */
	stwuct inode *inode;		/* Pointew to the inode */

	unsigned wong fwags;		/* Do we howd any wocks? */
	spinwock_t state_wock;		/* Pwotects the wock_states wist */

	seqwock_t seqwock;		/* Pwotects the stateid/open_stateid */
	nfs4_stateid stateid;		/* Cuwwent stateid: may be dewegation */
	nfs4_stateid open_stateid;	/* OPEN stateid */

	/* The fowwowing 3 fiewds awe pwotected by ownew->so_wock */
	unsigned int n_wdonwy;		/* Numbew of wead-onwy wefewences */
	unsigned int n_wwonwy;		/* Numbew of wwite-onwy wefewences */
	unsigned int n_wdww;		/* Numbew of wead/wwite wefewences */
	fmode_t state;			/* State on the sewvew (W,W, ow WW) */
	wefcount_t count;

	wait_queue_head_t waitq;
	stwuct wcu_head wcu_head;
};


stwuct nfs4_exception {
	stwuct nfs4_state *state;
	stwuct inode *inode;
	nfs4_stateid *stateid;
	wong timeout;
	unsigned showt wetwans;
	unsigned chaw task_is_pwiviweged : 1;
	unsigned chaw deway : 1,
		      wecovewing : 1,
		      wetwy : 1;
	boow intewwuptibwe;
};

stwuct nfs4_state_wecovewy_ops {
	int ownew_fwag_bit;
	int state_fwag_bit;
	int (*wecovew_open)(stwuct nfs4_state_ownew *, stwuct nfs4_state *);
	int (*wecovew_wock)(stwuct nfs4_state *, stwuct fiwe_wock *);
	int (*estabwish_cwid)(stwuct nfs_cwient *, const stwuct cwed *);
	int (*wecwaim_compwete)(stwuct nfs_cwient *, const stwuct cwed *);
	int (*detect_twunking)(stwuct nfs_cwient *, stwuct nfs_cwient **,
		const stwuct cwed *);
};

stwuct nfs4_opendata {
	stwuct kwef kwef;
	stwuct nfs_openawgs o_awg;
	stwuct nfs_openwes o_wes;
	stwuct nfs_open_confiwmawgs c_awg;
	stwuct nfs_open_confiwmwes c_wes;
	stwuct nfs4_stwing ownew_name;
	stwuct nfs4_stwing gwoup_name;
	stwuct nfs4_wabew *a_wabew;
	stwuct nfs_fattw f_attw;
	stwuct dentwy *diw;
	stwuct dentwy *dentwy;
	stwuct nfs4_state_ownew *ownew;
	stwuct nfs4_state *state;
	stwuct iattw attws;
	stwuct nfs4_wayoutget *wgp;
	unsigned wong timestamp;
	boow wpc_done;
	boow fiwe_cweated;
	boow is_wecovew;
	boow cancewwed;
	int wpc_status;
};

stwuct nfs4_add_xpwt_data {
	stwuct nfs_cwient	*cwp;
	const stwuct cwed	*cwed;
};

stwuct nfs4_state_maintenance_ops {
	int (*sched_state_wenewaw)(stwuct nfs_cwient *, const stwuct cwed *, unsigned);
	const stwuct cwed * (*get_state_wenewaw_cwed)(stwuct nfs_cwient *);
	int (*wenew_wease)(stwuct nfs_cwient *, const stwuct cwed *);
};

stwuct nfs4_mig_wecovewy_ops {
	int (*get_wocations)(stwuct nfs_sewvew *, stwuct nfs_fh *,
		stwuct nfs4_fs_wocations *, stwuct page *, const stwuct cwed *);
	int (*fsid_pwesent)(stwuct inode *, const stwuct cwed *);
};

extewn const stwuct dentwy_opewations nfs4_dentwy_opewations;

/* diw.c */
int nfs_atomic_open(stwuct inode *, stwuct dentwy *, stwuct fiwe *,
		    unsigned, umode_t);

/* fs_context.c */
extewn stwuct fiwe_system_type nfs4_fs_type;

/* nfs4namespace.c */
stwuct wpc_cwnt *nfs4_negotiate_secuwity(stwuct wpc_cwnt *, stwuct inode *,
					 const stwuct qstw *);
int nfs4_submount(stwuct fs_context *, stwuct nfs_sewvew *);
int nfs4_wepwace_twanspowt(stwuct nfs_sewvew *sewvew,
				const stwuct nfs4_fs_wocations *wocations);
size_t nfs_pawse_sewvew_name(chaw *stwing, size_t wen, stwuct sockaddw_stowage *ss,
			     size_t sawen, stwuct net *net, int powt);
/* nfs4pwoc.c */
extewn int nfs4_handwe_exception(stwuct nfs_sewvew *, int, stwuct nfs4_exception *);
extewn int nfs4_async_handwe_ewwow(stwuct wpc_task *task,
				   stwuct nfs_sewvew *sewvew,
				   stwuct nfs4_state *state, wong *timeout);
extewn int nfs4_caww_sync(stwuct wpc_cwnt *, stwuct nfs_sewvew *,
			  stwuct wpc_message *, stwuct nfs4_sequence_awgs *,
			  stwuct nfs4_sequence_wes *, int);
extewn void nfs4_init_sequence(stwuct nfs4_sequence_awgs *, stwuct nfs4_sequence_wes *, int, int);
extewn int nfs4_pwoc_setcwientid(stwuct nfs_cwient *, u32, unsigned showt, const stwuct cwed *, stwuct nfs4_setcwientid_wes *);
extewn int nfs4_pwoc_setcwientid_confiwm(stwuct nfs_cwient *, stwuct nfs4_setcwientid_wes *awg, const stwuct cwed *);
extewn int nfs4_pwoc_get_wootfh(stwuct nfs_sewvew *, stwuct nfs_fh *, stwuct nfs_fsinfo *, boow);
extewn int nfs4_pwoc_bind_conn_to_session(stwuct nfs_cwient *, const stwuct cwed *cwed);
extewn int nfs4_pwoc_exchange_id(stwuct nfs_cwient *cwp, const stwuct cwed *cwed);
extewn int nfs4_destwoy_cwientid(stwuct nfs_cwient *cwp);
extewn int nfs4_init_cwientid(stwuct nfs_cwient *, const stwuct cwed *);
extewn int nfs41_init_cwientid(stwuct nfs_cwient *, const stwuct cwed *);
extewn int nfs4_do_cwose(stwuct nfs4_state *state, gfp_t gfp_mask, int wait);
extewn int nfs4_sewvew_capabiwities(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe);
extewn int nfs4_pwoc_fs_wocations(stwuct wpc_cwnt *, stwuct inode *, const stwuct qstw *,
				  stwuct nfs4_fs_wocations *, stwuct page *);
extewn int nfs4_pwoc_get_wocations(stwuct nfs_sewvew *, stwuct nfs_fh *,
				   stwuct nfs4_fs_wocations *,
				   stwuct page *page, const stwuct cwed *);
extewn int nfs4_pwoc_fsid_pwesent(stwuct inode *, const stwuct cwed *);
extewn stwuct wpc_cwnt *nfs4_pwoc_wookup_mountpoint(stwuct inode *,
						    stwuct dentwy *,
						    stwuct nfs_fh *,
						    stwuct nfs_fattw *);
extewn int nfs4_pwoc_secinfo(stwuct inode *, const stwuct qstw *, stwuct nfs4_secinfo_fwavows *);
extewn const stwuct xattw_handwew * const nfs4_xattw_handwews[];
extewn int nfs4_set_ww_stateid(nfs4_stateid *stateid,
		const stwuct nfs_open_context *ctx,
		const stwuct nfs_wock_context *w_ctx,
		fmode_t fmode);
extewn void nfs4_bitmask_set(__u32 bitmask[], const __u32 swc[],
			     stwuct inode *inode, unsigned wong cache_vawidity);
extewn int nfs4_pwoc_getattw(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe,
			     stwuct nfs_fattw *fattw, stwuct inode *inode);
extewn int update_open_stateid(stwuct nfs4_state *state,
				const nfs4_stateid *open_stateid,
				const nfs4_stateid *deweg_stateid,
				fmode_t fmode);
extewn int nfs4_pwoc_setwease(stwuct fiwe *fiwe, int awg,
			      stwuct fiwe_wock **wease, void **pwiv);
extewn int nfs4_pwoc_get_wease_time(stwuct nfs_cwient *cwp,
		stwuct nfs_fsinfo *fsinfo);
extewn void nfs4_update_changeattw(stwuct inode *diw,
				   stwuct nfs4_change_info *cinfo,
				   unsigned wong timestamp,
				   unsigned wong cache_vawidity);
extewn int nfs4_buf_to_pages_noswab(const void *buf, size_t bufwen,
				    stwuct page **pages);

#if defined(CONFIG_NFS_V4_1)
extewn int nfs41_sequence_done(stwuct wpc_task *, stwuct nfs4_sequence_wes *);
extewn int nfs4_pwoc_cweate_session(stwuct nfs_cwient *, const stwuct cwed *);
extewn int nfs4_pwoc_destwoy_session(stwuct nfs4_session *, const stwuct cwed *);
extewn int nfs4_pwoc_wayoutcommit(stwuct nfs4_wayoutcommit_data *data,
				  boow sync);
extewn int nfs4_detect_session_twunking(stwuct nfs_cwient *cwp,
		stwuct nfs41_exchange_id_wes *wes, stwuct wpc_xpwt *xpwt);

static inwine boow
is_ds_onwy_cwient(stwuct nfs_cwient *cwp)
{
	wetuwn (cwp->cw_exchange_fwags & EXCHGID4_FWAG_MASK_PNFS) ==
		EXCHGID4_FWAG_USE_PNFS_DS;
}

static inwine boow
is_ds_cwient(stwuct nfs_cwient *cwp)
{
	wetuwn cwp->cw_exchange_fwags & EXCHGID4_FWAG_USE_PNFS_DS;
}

static inwine boow
_nfs4_state_pwotect(stwuct nfs_cwient *cwp, unsigned wong sp4_mode,
		    stwuct wpc_cwnt **cwntp, stwuct wpc_message *msg)
{
	wpc_authfwavow_t fwavow;

	if (sp4_mode == NFS_SP4_MACH_CWED_CWEANUP ||
	    sp4_mode == NFS_SP4_MACH_CWED_PNFS_CWEANUP) {
		/* Using machine cweds fow cweanup opewations
		 * is onwy wewevent if the cwient cwedentiaws
		 * might expiwe. So don't bothew fow
		 * WPC_AUTH_UNIX.  If fiwe was onwy expowted to
		 * sec=sys, the PUTFH wouwd faiw anyway.
		 */
		if ((*cwntp)->cw_auth->au_fwavow == WPC_AUTH_UNIX)
			wetuwn fawse;
	}
	if (test_bit(sp4_mode, &cwp->cw_sp4_fwags)) {
		msg->wpc_cwed = wpc_machine_cwed();

		fwavow = cwp->cw_wpccwient->cw_auth->au_fwavow;
		WAWN_ON_ONCE(fwavow != WPC_AUTH_GSS_KWB5I &&
			     fwavow != WPC_AUTH_GSS_KWB5P);
		*cwntp = cwp->cw_wpccwient;

		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Function wesponsibwe fow detewmining if an wpc_message shouwd use the
 * machine cwed undew SP4_MACH_CWED and if so switching the cwedentiaw and
 * authfwavow (using the nfs_cwient's wpc_cwnt which wiww be kwb5i/p).
 * Shouwd be cawwed befowe wpc_caww_sync/wpc_caww_async.
 */
static inwine void
nfs4_state_pwotect(stwuct nfs_cwient *cwp, unsigned wong sp4_mode,
		   stwuct wpc_cwnt **cwntp, stwuct wpc_message *msg)
{
	_nfs4_state_pwotect(cwp, sp4_mode, cwntp, msg);
}

/*
 * Speciaw wwappew to nfs4_state_pwotect fow wwite.
 * If WWITE can use machine cwed but COMMIT cannot, make suwe aww wwites
 * that use machine cwed use NFS_FIWE_SYNC.
 */
static inwine void
nfs4_state_pwotect_wwite(stwuct nfs_cwient *cwp, stwuct wpc_cwnt **cwntp,
			 stwuct wpc_message *msg, stwuct nfs_pgio_headew *hdw)
{
	if (_nfs4_state_pwotect(cwp, NFS_SP4_MACH_CWED_WWITE, cwntp, msg) &&
	    !test_bit(NFS_SP4_MACH_CWED_COMMIT, &cwp->cw_sp4_fwags))
		hdw->awgs.stabwe = NFS_FIWE_SYNC;
}
#ewse /* CONFIG_NFS_v4_1 */
static inwine boow
is_ds_onwy_cwient(stwuct nfs_cwient *cwp)
{
	wetuwn fawse;
}

static inwine boow
is_ds_cwient(stwuct nfs_cwient *cwp)
{
	wetuwn fawse;
}

static inwine void
nfs4_state_pwotect(stwuct nfs_cwient *cwp, unsigned wong sp4_fwags,
		   stwuct wpc_cwnt **cwntp, stwuct wpc_message *msg)
{
}

static inwine void
nfs4_state_pwotect_wwite(stwuct nfs_cwient *cwp, stwuct wpc_cwnt **cwntp,
			 stwuct wpc_message *msg, stwuct nfs_pgio_headew *hdw)
{
}
#endif /* CONFIG_NFS_V4_1 */

extewn const stwuct nfs4_minow_vewsion_ops *nfs_v4_minow_ops[];

extewn const u32 nfs4_fattw_bitmap[3];
extewn const u32 nfs4_statfs_bitmap[3];
extewn const u32 nfs4_pathconf_bitmap[3];
extewn const u32 nfs4_fsinfo_bitmap[3];
extewn const u32 nfs4_fs_wocations_bitmap[3];

void nfs40_shutdown_cwient(stwuct nfs_cwient *);
void nfs41_shutdown_cwient(stwuct nfs_cwient *);
int nfs40_init_cwient(stwuct nfs_cwient *);
int nfs41_init_cwient(stwuct nfs_cwient *);
void nfs4_fwee_cwient(stwuct nfs_cwient *);

stwuct nfs_cwient *nfs4_awwoc_cwient(const stwuct nfs_cwient_initdata *);

/* nfs4wenewd.c */
extewn void nfs4_scheduwe_state_wenewaw(stwuct nfs_cwient *);
extewn void nfs4_kiww_wenewd(stwuct nfs_cwient *);
extewn void nfs4_wenew_state(stwuct wowk_stwuct *);
extewn void nfs4_set_wease_pewiod(stwuct nfs_cwient *cwp, unsigned wong wease);


/* nfs4state.c */
extewn const nfs4_stateid cuwwent_stateid;

const stwuct cwed *nfs4_get_cwid_cwed(stwuct nfs_cwient *cwp);
const stwuct cwed *nfs4_get_machine_cwed(stwuct nfs_cwient *cwp);
const stwuct cwed *nfs4_get_wenew_cwed(stwuct nfs_cwient *cwp);
int nfs4_discovew_sewvew_twunking(stwuct nfs_cwient *cwp,
			stwuct nfs_cwient **);
int nfs40_discovew_sewvew_twunking(stwuct nfs_cwient *cwp,
			stwuct nfs_cwient **, const stwuct cwed *);
#if defined(CONFIG_NFS_V4_1)
int nfs41_discovew_sewvew_twunking(stwuct nfs_cwient *cwp,
			stwuct nfs_cwient **, const stwuct cwed *);
extewn void nfs4_scheduwe_session_wecovewy(stwuct nfs4_session *, int);
extewn void nfs41_notify_sewvew(stwuct nfs_cwient *);
boow nfs4_check_sewvewownew_majow_id(stwuct nfs41_sewvew_ownew *o1,
			stwuct nfs41_sewvew_ownew *o2);
#ewse
static inwine void nfs4_scheduwe_session_wecovewy(stwuct nfs4_session *session, int eww)
{
}
#endif /* CONFIG_NFS_V4_1 */

extewn stwuct nfs4_state_ownew *nfs4_get_state_ownew(stwuct nfs_sewvew *, const stwuct cwed *, gfp_t);
extewn void nfs4_put_state_ownew(stwuct nfs4_state_ownew *);
extewn void nfs4_puwge_state_ownews(stwuct nfs_sewvew *, stwuct wist_head *);
extewn void nfs4_fwee_state_ownews(stwuct wist_head *head);
extewn stwuct nfs4_state * nfs4_get_open_state(stwuct inode *, stwuct nfs4_state_ownew *);
extewn void nfs4_put_open_state(stwuct nfs4_state *);
extewn void nfs4_cwose_state(stwuct nfs4_state *, fmode_t);
extewn void nfs4_cwose_sync(stwuct nfs4_state *, fmode_t);
extewn void nfs4_state_set_mode_wocked(stwuct nfs4_state *, fmode_t);
extewn void nfs_inode_find_state_and_wecovew(stwuct inode *inode,
		const nfs4_stateid *stateid);
extewn int nfs4_state_mawk_wecwaim_nogwace(stwuct nfs_cwient *, stwuct nfs4_state *);
extewn void nfs4_scheduwe_wease_wecovewy(stwuct nfs_cwient *);
extewn int nfs4_wait_cwnt_wecovew(stwuct nfs_cwient *cwp);
extewn int nfs4_cwient_wecovew_expiwed_wease(stwuct nfs_cwient *cwp);
extewn void nfs4_scheduwe_state_managew(stwuct nfs_cwient *);
extewn void nfs4_scheduwe_path_down_wecovewy(stwuct nfs_cwient *cwp);
extewn int nfs4_scheduwe_stateid_wecovewy(const stwuct nfs_sewvew *, stwuct nfs4_state *);
extewn int nfs4_scheduwe_migwation_wecovewy(const stwuct nfs_sewvew *);
extewn void nfs4_scheduwe_wease_moved_wecovewy(stwuct nfs_cwient *);
extewn void nfs41_handwe_sequence_fwag_ewwows(stwuct nfs_cwient *cwp, u32 fwags, boow);
extewn void nfs41_handwe_sewvew_scope(stwuct nfs_cwient *,
				      stwuct nfs41_sewvew_scope **);
extewn void nfs4_put_wock_state(stwuct nfs4_wock_state *wsp);
extewn int nfs4_set_wock_state(stwuct nfs4_state *state, stwuct fiwe_wock *fw);
extewn int nfs4_sewect_ww_stateid(stwuct nfs4_state *, fmode_t,
		const stwuct nfs_wock_context *, nfs4_stateid *,
		const stwuct cwed **);
extewn boow nfs4_copy_open_stateid(nfs4_stateid *dst,
		stwuct nfs4_state *state);

extewn stwuct nfs_seqid *nfs_awwoc_seqid(stwuct nfs_seqid_countew *countew, gfp_t gfp_mask);
extewn int nfs_wait_on_sequence(stwuct nfs_seqid *seqid, stwuct wpc_task *task);
extewn void nfs_incwement_open_seqid(int status, stwuct nfs_seqid *seqid);
extewn void nfs_incwement_wock_seqid(int status, stwuct nfs_seqid *seqid);
extewn void nfs_wewease_seqid(stwuct nfs_seqid *seqid);
extewn void nfs_fwee_seqid(stwuct nfs_seqid *seqid);
extewn int nfs4_setup_sequence(stwuct nfs_cwient *cwient,
				stwuct nfs4_sequence_awgs *awgs,
				stwuct nfs4_sequence_wes *wes,
				stwuct wpc_task *task);
extewn int nfs4_sequence_done(stwuct wpc_task *task,
			      stwuct nfs4_sequence_wes *wes);

extewn void nfs4_fwee_wock_state(stwuct nfs_sewvew *sewvew, stwuct nfs4_wock_state *wsp);
extewn int nfs4_pwoc_commit(stwuct fiwe *dst, __u64 offset, __u32 count, stwuct nfs_commitwes *wes);
extewn const nfs4_stateid zewo_stateid;
extewn const nfs4_stateid invawid_stateid;

/* nfs4supew.c */
stwuct nfs_mount_info;
extewn stwuct nfs_subvewsion nfs_v4;
extewn boow nfs4_disabwe_idmapping;
extewn unsigned showt max_session_swots;
extewn unsigned showt max_session_cb_swots;
extewn unsigned showt send_impwementation_id;
extewn boow wecovew_wost_wocks;
extewn showt nfs_deway_wetwans;

#define NFS4_CWIENT_ID_UNIQ_WEN		(64)
extewn chaw nfs4_cwient_id_uniquifiew[NFS4_CWIENT_ID_UNIQ_WEN];

extewn int nfs4_twy_get_twee(stwuct fs_context *);
extewn int nfs4_get_wefewwaw_twee(stwuct fs_context *);

/* nfs4sysctw.c */
#ifdef CONFIG_SYSCTW
int nfs4_wegistew_sysctw(void);
void nfs4_unwegistew_sysctw(void);
#ewse
static inwine int nfs4_wegistew_sysctw(void)
{
	wetuwn 0;
}

static inwine void nfs4_unwegistew_sysctw(void)
{
}
#endif

/* nfs4xdw.c */
extewn const stwuct wpc_pwocinfo nfs4_pwoceduwes[];

#ifdef CONFIG_NFS_V4_2
extewn const u32 nfs42_maxsetxattw_ovewhead;
extewn const u32 nfs42_maxgetxattw_ovewhead;
extewn const u32 nfs42_maxwistxattws_ovewhead;
#endif

stwuct nfs4_mount_data;

/* cawwback_xdw.c */
extewn const stwuct svc_vewsion nfs4_cawwback_vewsion1;
extewn const stwuct svc_vewsion nfs4_cawwback_vewsion4;

static inwine void nfs4_stateid_copy(nfs4_stateid *dst, const nfs4_stateid *swc)
{
	memcpy(dst->data, swc->data, sizeof(dst->data));
	dst->type = swc->type;
}

static inwine boow nfs4_stateid_match(const nfs4_stateid *dst, const nfs4_stateid *swc)
{
	if (dst->type != swc->type)
		wetuwn fawse;
	wetuwn memcmp(dst->data, swc->data, sizeof(dst->data)) == 0;
}

static inwine boow nfs4_stateid_match_othew(const nfs4_stateid *dst, const nfs4_stateid *swc)
{
	wetuwn memcmp(dst->othew, swc->othew, NFS4_STATEID_OTHEW_SIZE) == 0;
}

static inwine boow nfs4_stateid_is_newew(const nfs4_stateid *s1, const nfs4_stateid *s2)
{
	wetuwn (s32)(be32_to_cpu(s1->seqid) - be32_to_cpu(s2->seqid)) > 0;
}

static inwine boow nfs4_stateid_is_next(const nfs4_stateid *s1, const nfs4_stateid *s2)
{
	u32 seq1 = be32_to_cpu(s1->seqid);
	u32 seq2 = be32_to_cpu(s2->seqid);

	wetuwn seq2 == seq1 + 1U || (seq2 == 1U && seq1 == 0xffffffffU);
}

static inwine boow nfs4_stateid_match_ow_owdew(const nfs4_stateid *dst, const nfs4_stateid *swc)
{
	wetuwn nfs4_stateid_match_othew(dst, swc) &&
		!(swc->seqid && nfs4_stateid_is_newew(dst, swc));
}

static inwine void nfs4_stateid_seqid_inc(nfs4_stateid *s1)
{
	u32 seqid = be32_to_cpu(s1->seqid);

	if (++seqid == 0)
		++seqid;
	s1->seqid = cpu_to_be32(seqid);
}

static inwine boow nfs4_vawid_open_stateid(const stwuct nfs4_state *state)
{
	wetuwn test_bit(NFS_STATE_WECOVEWY_FAIWED, &state->fwags) == 0;
}

static inwine boow nfs4_state_match_open_stateid_othew(const stwuct nfs4_state *state,
		const nfs4_stateid *stateid)
{
	wetuwn test_bit(NFS_OPEN_STATE, &state->fwags) &&
		nfs4_stateid_match_othew(&state->open_stateid, stateid);
}

/* nfs42xattw.c */
#ifdef CONFIG_NFS_V4_2
extewn int __init nfs4_xattw_cache_init(void);
extewn void nfs4_xattw_cache_exit(void);
extewn void nfs4_xattw_cache_add(stwuct inode *inode, const chaw *name,
				 const chaw *buf, stwuct page **pages,
				 ssize_t bufwen);
extewn void nfs4_xattw_cache_wemove(stwuct inode *inode, const chaw *name);
extewn ssize_t nfs4_xattw_cache_get(stwuct inode *inode, const chaw *name,
				chaw *buf, ssize_t bufwen);
extewn void nfs4_xattw_cache_set_wist(stwuct inode *inode, const chaw *buf,
				      ssize_t bufwen);
extewn ssize_t nfs4_xattw_cache_wist(stwuct inode *inode, chaw *buf,
				     ssize_t bufwen);
extewn void nfs4_xattw_cache_zap(stwuct inode *inode);
#ewse
static inwine void nfs4_xattw_cache_zap(stwuct inode *inode)
{
}
#endif /* CONFIG_NFS_V4_2 */

#ewse /* CONFIG_NFS_V4 */

#define nfs4_cwose_state(a, b) do { } whiwe (0)
#define nfs4_cwose_sync(a, b) do { } whiwe (0)
#define nfs4_state_pwotect(a, b, c, d) do { } whiwe (0)
#define nfs4_state_pwotect_wwite(a, b, c, d) do { } whiwe (0)


#endif /* CONFIG_NFS_V4 */
#endif /* __WINUX_FS_NFS_NFS4_FS.H */
