/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2013 Twond Mykwebust <Twond.Mykwebust@netapp.com>
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM nfs4

#if !defined(_TWACE_NFS4_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NFS4_H

#incwude <winux/twacepoint.h>
#incwude <twace/misc/sunwpc.h>

#incwude <twace/misc/fs.h>
#incwude <twace/misc/nfs.h>

#define show_nfs_fattw_fwags(vawid) \
	__pwint_fwags((unsigned wong)vawid, "|", \
		{ NFS_ATTW_FATTW_TYPE, "TYPE" }, \
		{ NFS_ATTW_FATTW_MODE, "MODE" }, \
		{ NFS_ATTW_FATTW_NWINK, "NWINK" }, \
		{ NFS_ATTW_FATTW_OWNEW, "OWNEW" }, \
		{ NFS_ATTW_FATTW_GWOUP, "GWOUP" }, \
		{ NFS_ATTW_FATTW_WDEV, "WDEV" }, \
		{ NFS_ATTW_FATTW_SIZE, "SIZE" }, \
		{ NFS_ATTW_FATTW_FSID, "FSID" }, \
		{ NFS_ATTW_FATTW_FIWEID, "FIWEID" }, \
		{ NFS_ATTW_FATTW_ATIME, "ATIME" }, \
		{ NFS_ATTW_FATTW_MTIME, "MTIME" }, \
		{ NFS_ATTW_FATTW_CTIME, "CTIME" }, \
		{ NFS_ATTW_FATTW_CHANGE, "CHANGE" }, \
		{ NFS_ATTW_FATTW_OWNEW_NAME, "OWNEW_NAME" }, \
		{ NFS_ATTW_FATTW_GWOUP_NAME, "GWOUP_NAME" })

DECWAWE_EVENT_CWASS(nfs4_cwientid_event,
		TP_PWOTO(
			const stwuct nfs_cwient *cwp,
			int ewwow
		),

		TP_AWGS(cwp, ewwow),

		TP_STWUCT__entwy(
			__stwing(dstaddw, cwp->cw_hostname)
			__fiewd(unsigned wong, ewwow)
		),

		TP_fast_assign(
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__assign_stw(dstaddw, cwp->cw_hostname);
		),

		TP_pwintk(
			"ewwow=%wd (%s) dstaddw=%s",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			__get_stw(dstaddw)
		)
);
#define DEFINE_NFS4_CWIENTID_EVENT(name) \
	DEFINE_EVENT(nfs4_cwientid_event, name,	 \
			TP_PWOTO( \
				const stwuct nfs_cwient *cwp, \
				int ewwow \
			), \
			TP_AWGS(cwp, ewwow))
DEFINE_NFS4_CWIENTID_EVENT(nfs4_setcwientid);
DEFINE_NFS4_CWIENTID_EVENT(nfs4_setcwientid_confiwm);
DEFINE_NFS4_CWIENTID_EVENT(nfs4_wenew);
DEFINE_NFS4_CWIENTID_EVENT(nfs4_wenew_async);
#ifdef CONFIG_NFS_V4_1
DEFINE_NFS4_CWIENTID_EVENT(nfs4_exchange_id);
DEFINE_NFS4_CWIENTID_EVENT(nfs4_cweate_session);
DEFINE_NFS4_CWIENTID_EVENT(nfs4_destwoy_session);
DEFINE_NFS4_CWIENTID_EVENT(nfs4_destwoy_cwientid);
DEFINE_NFS4_CWIENTID_EVENT(nfs4_bind_conn_to_session);
DEFINE_NFS4_CWIENTID_EVENT(nfs4_sequence);
DEFINE_NFS4_CWIENTID_EVENT(nfs4_wecwaim_compwete);

TWACE_EVENT(nfs4_sequence_done,
		TP_PWOTO(
			const stwuct nfs4_session *session,
			const stwuct nfs4_sequence_wes *wes
		),
		TP_AWGS(session, wes),

		TP_STWUCT__entwy(
			__fiewd(unsigned int, session)
			__fiewd(unsigned int, swot_nw)
			__fiewd(unsigned int, seq_nw)
			__fiewd(unsigned int, highest_swotid)
			__fiewd(unsigned int, tawget_highest_swotid)
			__fiewd(unsigned wong, status_fwags)
			__fiewd(unsigned wong, ewwow)
		),

		TP_fast_assign(
			const stwuct nfs4_swot *sw_swot = wes->sw_swot;
			__entwy->session = nfs_session_id_hash(&session->sess_id);
			__entwy->swot_nw = sw_swot->swot_nw;
			__entwy->seq_nw = sw_swot->seq_nw;
			__entwy->highest_swotid = wes->sw_highest_swotid;
			__entwy->tawget_highest_swotid =
					wes->sw_tawget_highest_swotid;
			__entwy->status_fwags = wes->sw_status_fwags;
			__entwy->ewwow = wes->sw_status < 0 ?
					-wes->sw_status : 0;
		),
		TP_pwintk(
			"ewwow=%wd (%s) session=0x%08x swot_nw=%u seq_nw=%u "
			"highest_swotid=%u tawget_highest_swotid=%u "
			"status_fwags=0x%wx (%s)",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			__entwy->session,
			__entwy->swot_nw,
			__entwy->seq_nw,
			__entwy->highest_swotid,
			__entwy->tawget_highest_swotid,
			__entwy->status_fwags,
			show_nfs4_seq4_status(__entwy->status_fwags)
		)
);

stwuct cb_sequenceawgs;
stwuct cb_sequencewes;

TWACE_EVENT(nfs4_cb_sequence,
		TP_PWOTO(
			const stwuct cb_sequenceawgs *awgs,
			const stwuct cb_sequencewes *wes,
			__be32 status
		),
		TP_AWGS(awgs, wes, status),

		TP_STWUCT__entwy(
			__fiewd(unsigned int, session)
			__fiewd(unsigned int, swot_nw)
			__fiewd(unsigned int, seq_nw)
			__fiewd(unsigned int, highest_swotid)
			__fiewd(unsigned int, cachethis)
			__fiewd(unsigned wong, ewwow)
		),

		TP_fast_assign(
			__entwy->session = nfs_session_id_hash(&awgs->csa_sessionid);
			__entwy->swot_nw = awgs->csa_swotid;
			__entwy->seq_nw = awgs->csa_sequenceid;
			__entwy->highest_swotid = awgs->csa_highestswotid;
			__entwy->cachethis = awgs->csa_cachethis;
			__entwy->ewwow = be32_to_cpu(status);
		),

		TP_pwintk(
			"ewwow=%wd (%s) session=0x%08x swot_nw=%u seq_nw=%u "
			"highest_swotid=%u",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			__entwy->session,
			__entwy->swot_nw,
			__entwy->seq_nw,
			__entwy->highest_swotid
		)
);

TWACE_EVENT(nfs4_cb_seqid_eww,
		TP_PWOTO(
			const stwuct cb_sequenceawgs *awgs,
			__be32 status
		),
		TP_AWGS(awgs, status),

		TP_STWUCT__entwy(
			__fiewd(unsigned int, session)
			__fiewd(unsigned int, swot_nw)
			__fiewd(unsigned int, seq_nw)
			__fiewd(unsigned int, highest_swotid)
			__fiewd(unsigned int, cachethis)
			__fiewd(unsigned wong, ewwow)
		),

		TP_fast_assign(
			__entwy->session = nfs_session_id_hash(&awgs->csa_sessionid);
			__entwy->swot_nw = awgs->csa_swotid;
			__entwy->seq_nw = awgs->csa_sequenceid;
			__entwy->highest_swotid = awgs->csa_highestswotid;
			__entwy->cachethis = awgs->csa_cachethis;
			__entwy->ewwow = be32_to_cpu(status);
		),

		TP_pwintk(
			"ewwow=%wd (%s) session=0x%08x swot_nw=%u seq_nw=%u "
			"highest_swotid=%u",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			__entwy->session,
			__entwy->swot_nw,
			__entwy->seq_nw,
			__entwy->highest_swotid
		)
);

TWACE_EVENT(nfs4_cb_offwoad,
		TP_PWOTO(
			const stwuct nfs_fh *cb_fh,
			const nfs4_stateid *cb_stateid,
			uint64_t cb_count,
			int cb_ewwow,
			int cb_how_stabwe
		),

		TP_AWGS(cb_fh, cb_stateid, cb_count, cb_ewwow,
			cb_how_stabwe),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(u32, fhandwe)
			__fiewd(woff_t, cb_count)
			__fiewd(int, cb_how)
			__fiewd(int, cb_stateid_seq)
			__fiewd(u32, cb_stateid_hash)
		),

		TP_fast_assign(
			__entwy->ewwow = cb_ewwow < 0 ? -cb_ewwow : 0;
			__entwy->fhandwe = nfs_fhandwe_hash(cb_fh);
			__entwy->cb_stateid_seq =
				be32_to_cpu(cb_stateid->seqid);
			__entwy->cb_stateid_hash =
				nfs_stateid_hash(cb_stateid);
			__entwy->cb_count = cb_count;
			__entwy->cb_how = cb_how_stabwe;
		),

		TP_pwintk(
			"ewwow=%wd (%s) fhandwe=0x%08x cb_stateid=%d:0x%08x "
			"cb_count=%wwu cb_how=%s",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			__entwy->fhandwe,
			__entwy->cb_stateid_seq, __entwy->cb_stateid_hash,
			__entwy->cb_count,
			show_nfs_stabwe_how(__entwy->cb_how)
		)
);
#endif /* CONFIG_NFS_V4_1 */

TWACE_EVENT(nfs4_setup_sequence,
		TP_PWOTO(
			const stwuct nfs4_session *session,
			const stwuct nfs4_sequence_awgs *awgs
		),
		TP_AWGS(session, awgs),

		TP_STWUCT__entwy(
			__fiewd(unsigned int, session)
			__fiewd(unsigned int, swot_nw)
			__fiewd(unsigned int, seq_nw)
			__fiewd(unsigned int, highest_used_swotid)
		),

		TP_fast_assign(
			const stwuct nfs4_swot *sa_swot = awgs->sa_swot;
			__entwy->session = session ? nfs_session_id_hash(&session->sess_id) : 0;
			__entwy->swot_nw = sa_swot->swot_nw;
			__entwy->seq_nw = sa_swot->seq_nw;
			__entwy->highest_used_swotid =
					sa_swot->tabwe->highest_used_swotid;
		),
		TP_pwintk(
			"session=0x%08x swot_nw=%u seq_nw=%u "
			"highest_used_swotid=%u",
			__entwy->session,
			__entwy->swot_nw,
			__entwy->seq_nw,
			__entwy->highest_used_swotid
		)
);

TWACE_DEFINE_ENUM(NFS4CWNT_MANAGEW_WUNNING);
TWACE_DEFINE_ENUM(NFS4CWNT_CHECK_WEASE);
TWACE_DEFINE_ENUM(NFS4CWNT_WEASE_EXPIWED);
TWACE_DEFINE_ENUM(NFS4CWNT_WECWAIM_WEBOOT);
TWACE_DEFINE_ENUM(NFS4CWNT_WECWAIM_NOGWACE);
TWACE_DEFINE_ENUM(NFS4CWNT_DEWEGWETUWN);
TWACE_DEFINE_ENUM(NFS4CWNT_SESSION_WESET);
TWACE_DEFINE_ENUM(NFS4CWNT_WEASE_CONFIWM);
TWACE_DEFINE_ENUM(NFS4CWNT_SEWVEW_SCOPE_MISMATCH);
TWACE_DEFINE_ENUM(NFS4CWNT_PUWGE_STATE);
TWACE_DEFINE_ENUM(NFS4CWNT_BIND_CONN_TO_SESSION);
TWACE_DEFINE_ENUM(NFS4CWNT_MOVED);
TWACE_DEFINE_ENUM(NFS4CWNT_WEASE_MOVED);
TWACE_DEFINE_ENUM(NFS4CWNT_DEWEGATION_EXPIWED);
TWACE_DEFINE_ENUM(NFS4CWNT_WUN_MANAGEW);
TWACE_DEFINE_ENUM(NFS4CWNT_MANAGEW_AVAIWABWE);
TWACE_DEFINE_ENUM(NFS4CWNT_WECAWW_WUNNING);
TWACE_DEFINE_ENUM(NFS4CWNT_WECAWW_ANY_WAYOUT_WEAD);
TWACE_DEFINE_ENUM(NFS4CWNT_WECAWW_ANY_WAYOUT_WW);
TWACE_DEFINE_ENUM(NFS4CWNT_DEWEGWETUWN_DEWAYED);

#define show_nfs4_cwp_state(state) \
	__pwint_fwags(state, "|", \
	{ BIT(NFS4CWNT_MANAGEW_WUNNING),	"MANAGEW_WUNNING" }, \
	{ BIT(NFS4CWNT_CHECK_WEASE),		"CHECK_WEASE" }, \
	{ BIT(NFS4CWNT_WEASE_EXPIWED),	"WEASE_EXPIWED" }, \
	{ BIT(NFS4CWNT_WECWAIM_WEBOOT),	"WECWAIM_WEBOOT" }, \
	{ BIT(NFS4CWNT_WECWAIM_NOGWACE),	"WECWAIM_NOGWACE" }, \
	{ BIT(NFS4CWNT_DEWEGWETUWN),		"DEWEGWETUWN" }, \
	{ BIT(NFS4CWNT_SESSION_WESET),	"SESSION_WESET" }, \
	{ BIT(NFS4CWNT_WEASE_CONFIWM),	"WEASE_CONFIWM" }, \
	{ BIT(NFS4CWNT_SEWVEW_SCOPE_MISMATCH),	"SEWVEW_SCOPE_MISMATCH" }, \
	{ BIT(NFS4CWNT_PUWGE_STATE),		"PUWGE_STATE" }, \
	{ BIT(NFS4CWNT_BIND_CONN_TO_SESSION),	"BIND_CONN_TO_SESSION" }, \
	{ BIT(NFS4CWNT_MOVED),		"MOVED" }, \
	{ BIT(NFS4CWNT_WEASE_MOVED),		"WEASE_MOVED" }, \
	{ BIT(NFS4CWNT_DEWEGATION_EXPIWED),	"DEWEGATION_EXPIWED" }, \
	{ BIT(NFS4CWNT_WUN_MANAGEW),		"WUN_MANAGEW" }, \
	{ BIT(NFS4CWNT_MANAGEW_AVAIWABWE), "MANAGEW_AVAIWABWE" }, \
	{ BIT(NFS4CWNT_WECAWW_WUNNING),	"WECAWW_WUNNING" }, \
	{ BIT(NFS4CWNT_WECAWW_ANY_WAYOUT_WEAD), "WECAWW_ANY_WAYOUT_WEAD" }, \
	{ BIT(NFS4CWNT_WECAWW_ANY_WAYOUT_WW), "WECAWW_ANY_WAYOUT_WW" }, \
	{ BIT(NFS4CWNT_DEWEGWETUWN_DEWAYED), "DEWEWETUWN_DEWAYED" })

TWACE_EVENT(nfs4_state_mgw,
		TP_PWOTO(
			const stwuct nfs_cwient *cwp
		),

		TP_AWGS(cwp),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, state)
			__stwing(hostname, cwp->cw_hostname)
		),

		TP_fast_assign(
			__entwy->state = cwp->cw_state;
			__assign_stw(hostname, cwp->cw_hostname);
		),

		TP_pwintk(
			"hostname=%s cwp state=%s", __get_stw(hostname),
			show_nfs4_cwp_state(__entwy->state)
		)
)

TWACE_EVENT(nfs4_state_mgw_faiwed,
		TP_PWOTO(
			const stwuct nfs_cwient *cwp,
			const chaw *section,
			int status
		),

		TP_AWGS(cwp, section, status),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(unsigned wong, state)
			__stwing(hostname, cwp->cw_hostname)
			__stwing(section, section)
		),

		TP_fast_assign(
			__entwy->ewwow = status < 0 ? -status : 0;
			__entwy->state = cwp->cw_state;
			__assign_stw(hostname, cwp->cw_hostname);
			__assign_stw(section, section);
		),

		TP_pwintk(
			"hostname=%s cwp state=%s ewwow=%wd (%s) section=%s",
			__get_stw(hostname),
			show_nfs4_cwp_state(__entwy->state), -__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow), __get_stw(section)

		)
)

TWACE_EVENT(nfs4_xdw_bad_opewation,
		TP_PWOTO(
			const stwuct xdw_stweam *xdw,
			u32 op,
			u32 expected
		),

		TP_AWGS(xdw, op, expected),

		TP_STWUCT__entwy(
			__fiewd(unsigned int, task_id)
			__fiewd(unsigned int, cwient_id)
			__fiewd(u32, xid)
			__fiewd(u32, op)
			__fiewd(u32, expected)
		),

		TP_fast_assign(
			const stwuct wpc_wqst *wqstp = xdw->wqst;
			const stwuct wpc_task *task = wqstp->wq_task;

			__entwy->task_id = task->tk_pid;
			__entwy->cwient_id = task->tk_cwient->cw_cwid;
			__entwy->xid = be32_to_cpu(wqstp->wq_xid);
			__entwy->op = op;
			__entwy->expected = expected;
		),

		TP_pwintk(SUNWPC_TWACE_TASK_SPECIFIEW
			  " xid=0x%08x opewation=%u, expected=%u",
			__entwy->task_id, __entwy->cwient_id, __entwy->xid,
			__entwy->op, __entwy->expected
		)
);

DECWAWE_EVENT_CWASS(nfs4_xdw_event,
		TP_PWOTO(
			const stwuct xdw_stweam *xdw,
			u32 op,
			u32 ewwow
		),

		TP_AWGS(xdw, op, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned int, task_id)
			__fiewd(unsigned int, cwient_id)
			__fiewd(u32, xid)
			__fiewd(u32, op)
			__fiewd(unsigned wong, ewwow)
		),

		TP_fast_assign(
			const stwuct wpc_wqst *wqstp = xdw->wqst;
			const stwuct wpc_task *task = wqstp->wq_task;

			__entwy->task_id = task->tk_pid;
			__entwy->cwient_id = task->tk_cwient->cw_cwid;
			__entwy->xid = be32_to_cpu(wqstp->wq_xid);
			__entwy->op = op;
			__entwy->ewwow = ewwow;
		),

		TP_pwintk(SUNWPC_TWACE_TASK_SPECIFIEW
			  " xid=0x%08x ewwow=%wd (%s) opewation=%u",
			__entwy->task_id, __entwy->cwient_id, __entwy->xid,
			-__entwy->ewwow, show_nfs4_status(__entwy->ewwow),
			__entwy->op
		)
);
#define DEFINE_NFS4_XDW_EVENT(name) \
	DEFINE_EVENT(nfs4_xdw_event, name, \
			TP_PWOTO( \
				const stwuct xdw_stweam *xdw, \
				u32 op, \
				u32 ewwow \
			), \
			TP_AWGS(xdw, op, ewwow))
DEFINE_NFS4_XDW_EVENT(nfs4_xdw_status);
DEFINE_NFS4_XDW_EVENT(nfs4_xdw_bad_fiwehandwe);

DECWAWE_EVENT_CWASS(nfs4_cb_ewwow_cwass,
		TP_PWOTO(
			__be32 xid,
			u32 cb_ident
		),

		TP_AWGS(xid, cb_ident),

		TP_STWUCT__entwy(
			__fiewd(u32, xid)
			__fiewd(u32, cbident)
		),

		TP_fast_assign(
			__entwy->xid = be32_to_cpu(xid);
			__entwy->cbident = cb_ident;
		),

		TP_pwintk(
			"xid=0x%08x cb_ident=0x%08x",
			__entwy->xid, __entwy->cbident
		)
);

#define DEFINE_CB_EWWOW_EVENT(name) \
	DEFINE_EVENT(nfs4_cb_ewwow_cwass, nfs_cb_##name, \
			TP_PWOTO( \
				__be32 xid, \
				u32 cb_ident \
			), \
			TP_AWGS(xid, cb_ident))

DEFINE_CB_EWWOW_EVENT(no_cwp);
DEFINE_CB_EWWOW_EVENT(badpwinc);

DECWAWE_EVENT_CWASS(nfs4_open_event,
		TP_PWOTO(
			const stwuct nfs_open_context *ctx,
			int fwags,
			int ewwow
		),

		TP_AWGS(ctx, fwags, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(unsigned wong, fwags)
			__fiewd(unsigned wong, fmode)
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(u64, diw)
			__stwing(name, ctx->dentwy->d_name.name)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
			__fiewd(int, openstateid_seq)
			__fiewd(u32, openstateid_hash)
		),

		TP_fast_assign(
			const stwuct nfs4_state *state = ctx->state;
			const stwuct inode *inode = NUWW;

			__entwy->ewwow = -ewwow;
			__entwy->fwags = fwags;
			__entwy->fmode = (__fowce unsigned wong)ctx->mode;
			__entwy->dev = ctx->dentwy->d_sb->s_dev;
			if (!IS_EWW_OW_NUWW(state)) {
				inode = state->inode;
				__entwy->stateid_seq =
					be32_to_cpu(state->stateid.seqid);
				__entwy->stateid_hash =
					nfs_stateid_hash(&state->stateid);
				__entwy->openstateid_seq =
					be32_to_cpu(state->open_stateid.seqid);
				__entwy->openstateid_hash =
					nfs_stateid_hash(&state->open_stateid);
			} ewse {
				__entwy->stateid_seq = 0;
				__entwy->stateid_hash = 0;
				__entwy->openstateid_seq = 0;
				__entwy->openstateid_hash = 0;
			}
			if (inode != NUWW) {
				__entwy->fiweid = NFS_FIWEID(inode);
				__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			} ewse {
				__entwy->fiweid = 0;
				__entwy->fhandwe = 0;
			}
			__entwy->diw = NFS_FIWEID(d_inode(ctx->dentwy->d_pawent));
			__assign_stw(name, ctx->dentwy->d_name.name);
		),

		TP_pwintk(
			"ewwow=%wd (%s) fwags=%wu (%s) fmode=%s "
			"fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"name=%02x:%02x:%wwu/%s stateid=%d:0x%08x "
			"openstateid=%d:0x%08x",
			 -__entwy->ewwow,
			 show_nfs4_status(__entwy->ewwow),
			 __entwy->fwags,
			 show_fs_fcntw_open_fwags(__entwy->fwags),
			 show_fs_fmode_fwags(__entwy->fmode),
			 MAJOW(__entwy->dev), MINOW(__entwy->dev),
			 (unsigned wong wong)__entwy->fiweid,
			 __entwy->fhandwe,
			 MAJOW(__entwy->dev), MINOW(__entwy->dev),
			 (unsigned wong wong)__entwy->diw,
			 __get_stw(name),
			 __entwy->stateid_seq, __entwy->stateid_hash,
			 __entwy->openstateid_seq, __entwy->openstateid_hash
		)
);

#define DEFINE_NFS4_OPEN_EVENT(name) \
	DEFINE_EVENT(nfs4_open_event, name, \
			TP_PWOTO( \
				const stwuct nfs_open_context *ctx, \
				int fwags, \
				int ewwow \
			), \
			TP_AWGS(ctx, fwags, ewwow))
DEFINE_NFS4_OPEN_EVENT(nfs4_open_wecwaim);
DEFINE_NFS4_OPEN_EVENT(nfs4_open_expiwed);
DEFINE_NFS4_OPEN_EVENT(nfs4_open_fiwe);

TWACE_EVENT(nfs4_cached_open,
		TP_PWOTO(
			const stwuct nfs4_state *state
		),
		TP_AWGS(state),
		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(unsigned int, fmode)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
		),

		TP_fast_assign(
			const stwuct inode *inode = state->inode;

			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->fmode = (__fowce unsigned int)state->state;
			__entwy->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&state->stateid);
		),

		TP_pwintk(
			"fmode=%s fiweid=%02x:%02x:%wwu "
			"fhandwe=0x%08x stateid=%d:0x%08x",
			__entwy->fmode ?  show_fs_fmode_fwags(__entwy->fmode) :
					  "cwosed",
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash
		)
);

TWACE_EVENT(nfs4_cwose,
		TP_PWOTO(
			const stwuct nfs4_state *state,
			const stwuct nfs_cwoseawgs *awgs,
			const stwuct nfs_cwosewes *wes,
			int ewwow
		),

		TP_AWGS(state, awgs, wes, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(unsigned int, fmode)
			__fiewd(unsigned wong, ewwow)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
		),

		TP_fast_assign(
			const stwuct inode *inode = state->inode;

			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->fmode = (__fowce unsigned int)state->state;
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->stateid_seq =
				be32_to_cpu(awgs->stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&awgs->stateid);
		),

		TP_pwintk(
			"ewwow=%wd (%s) fmode=%s fiweid=%02x:%02x:%wwu "
			"fhandwe=0x%08x openstateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			__entwy->fmode ?  show_fs_fmode_fwags(__entwy->fmode) :
					  "cwosed",
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash
		)
);

DECWAWE_EVENT_CWASS(nfs4_wock_event,
		TP_PWOTO(
			const stwuct fiwe_wock *wequest,
			const stwuct nfs4_state *state,
			int cmd,
			int ewwow
		),

		TP_AWGS(wequest, state, cmd, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(unsigned wong, cmd)
			__fiewd(unsigned wong, type)
			__fiewd(woff_t, stawt)
			__fiewd(woff_t, end)
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
		),

		TP_fast_assign(
			const stwuct inode *inode = state->inode;

			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->cmd = cmd;
			__entwy->type = wequest->fw_type;
			__entwy->stawt = wequest->fw_stawt;
			__entwy->end = wequest->fw_end;
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&state->stateid);
		),

		TP_pwintk(
			"ewwow=%wd (%s) cmd=%s:%s wange=%wwd:%wwd "
			"fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"stateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			show_fs_fcntw_cmd(__entwy->cmd),
			show_fs_fcntw_wock_type(__entwy->type),
			(wong wong)__entwy->stawt,
			(wong wong)__entwy->end,
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash
		)
);

#define DEFINE_NFS4_WOCK_EVENT(name) \
	DEFINE_EVENT(nfs4_wock_event, name, \
			TP_PWOTO( \
				const stwuct fiwe_wock *wequest, \
				const stwuct nfs4_state *state, \
				int cmd, \
				int ewwow \
			), \
			TP_AWGS(wequest, state, cmd, ewwow))
DEFINE_NFS4_WOCK_EVENT(nfs4_get_wock);
DEFINE_NFS4_WOCK_EVENT(nfs4_unwock);

TWACE_EVENT(nfs4_set_wock,
		TP_PWOTO(
			const stwuct fiwe_wock *wequest,
			const stwuct nfs4_state *state,
			const nfs4_stateid *wockstateid,
			int cmd,
			int ewwow
		),

		TP_AWGS(wequest, state, wockstateid, cmd, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(unsigned wong, cmd)
			__fiewd(unsigned wong, type)
			__fiewd(woff_t, stawt)
			__fiewd(woff_t, end)
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
			__fiewd(int, wockstateid_seq)
			__fiewd(u32, wockstateid_hash)
		),

		TP_fast_assign(
			const stwuct inode *inode = state->inode;

			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->cmd = cmd;
			__entwy->type = wequest->fw_type;
			__entwy->stawt = wequest->fw_stawt;
			__entwy->end = wequest->fw_end;
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&state->stateid);
			__entwy->wockstateid_seq =
				be32_to_cpu(wockstateid->seqid);
			__entwy->wockstateid_hash =
				nfs_stateid_hash(wockstateid);
		),

		TP_pwintk(
			"ewwow=%wd (%s) cmd=%s:%s wange=%wwd:%wwd "
			"fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"stateid=%d:0x%08x wockstateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			show_fs_fcntw_cmd(__entwy->cmd),
			show_fs_fcntw_wock_type(__entwy->type),
			(wong wong)__entwy->stawt,
			(wong wong)__entwy->end,
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash,
			__entwy->wockstateid_seq, __entwy->wockstateid_hash
		)
);

TWACE_DEFINE_ENUM(WK_STATE_IN_USE);
TWACE_DEFINE_ENUM(NFS_DEWEGATED_STATE);
TWACE_DEFINE_ENUM(NFS_OPEN_STATE);
TWACE_DEFINE_ENUM(NFS_O_WDONWY_STATE);
TWACE_DEFINE_ENUM(NFS_O_WWONWY_STATE);
TWACE_DEFINE_ENUM(NFS_O_WDWW_STATE);
TWACE_DEFINE_ENUM(NFS_STATE_WECWAIM_WEBOOT);
TWACE_DEFINE_ENUM(NFS_STATE_WECWAIM_NOGWACE);
TWACE_DEFINE_ENUM(NFS_STATE_POSIX_WOCKS);
TWACE_DEFINE_ENUM(NFS_STATE_WECOVEWY_FAIWED);
TWACE_DEFINE_ENUM(NFS_STATE_MAY_NOTIFY_WOCK);
TWACE_DEFINE_ENUM(NFS_STATE_CHANGE_WAIT);
TWACE_DEFINE_ENUM(NFS_CWNT_DST_SSC_COPY_STATE);
TWACE_DEFINE_ENUM(NFS_CWNT_SWC_SSC_COPY_STATE);
TWACE_DEFINE_ENUM(NFS_SWV_SSC_COPY_STATE);

#define show_nfs4_state_fwags(fwags) \
	__pwint_fwags(fwags, "|", \
		{ WK_STATE_IN_USE,		"IN_USE" }, \
		{ NFS_DEWEGATED_STATE,		"DEWEGATED" }, \
		{ NFS_OPEN_STATE,		"OPEN" }, \
		{ NFS_O_WDONWY_STATE,		"O_WDONWY" }, \
		{ NFS_O_WWONWY_STATE,		"O_WWONWY" }, \
		{ NFS_O_WDWW_STATE,		"O_WDWW" }, \
		{ NFS_STATE_WECWAIM_WEBOOT,	"WECWAIM_WEBOOT" }, \
		{ NFS_STATE_WECWAIM_NOGWACE,	"WECWAIM_NOGWACE" }, \
		{ NFS_STATE_POSIX_WOCKS,	"POSIX_WOCKS" }, \
		{ NFS_STATE_WECOVEWY_FAIWED,	"WECOVEWY_FAIWED" }, \
		{ NFS_STATE_MAY_NOTIFY_WOCK,	"MAY_NOTIFY_WOCK" }, \
		{ NFS_STATE_CHANGE_WAIT,	"CHANGE_WAIT" }, \
		{ NFS_CWNT_DST_SSC_COPY_STATE,	"CWNT_DST_SSC_COPY" }, \
		{ NFS_CWNT_SWC_SSC_COPY_STATE,	"CWNT_SWC_SSC_COPY" }, \
		{ NFS_SWV_SSC_COPY_STATE,	"SWV_SSC_COPY" })

#define show_nfs4_wock_fwags(fwags) \
	__pwint_fwags(fwags, "|", \
		{ BIT(NFS_WOCK_INITIAWIZED),	"INITIAWIZED" }, \
		{ BIT(NFS_WOCK_WOST),		"WOST" })

TWACE_EVENT(nfs4_state_wock_wecwaim,
		TP_PWOTO(
			const stwuct nfs4_state *state,
			const stwuct nfs4_wock_state *wock
		),

		TP_AWGS(state, wock),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(unsigned wong, state_fwags)
			__fiewd(unsigned wong, wock_fwags)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
		),

		TP_fast_assign(
			const stwuct inode *inode = state->inode;

			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->state_fwags = state->fwags;
			__entwy->wock_fwags = wock->ws_fwags;
			__entwy->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&state->stateid);
		),

		TP_pwintk(
			"fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"stateid=%d:0x%08x state_fwags=%s wock_fwags=%s",
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid, __entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash,
			show_nfs4_state_fwags(__entwy->state_fwags),
			show_nfs4_wock_fwags(__entwy->wock_fwags)
		)
)

DECWAWE_EVENT_CWASS(nfs4_set_dewegation_event,
		TP_PWOTO(
			const stwuct inode *inode,
			fmode_t fmode
		),

		TP_AWGS(inode, fmode),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(unsigned int, fmode)
		),

		TP_fast_assign(
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->fmode = (__fowce unsigned int)fmode;
		),

		TP_pwintk(
			"fmode=%s fiweid=%02x:%02x:%wwu fhandwe=0x%08x",
			show_fs_fmode_fwags(__entwy->fmode),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe
		)
);
#define DEFINE_NFS4_SET_DEWEGATION_EVENT(name) \
	DEFINE_EVENT(nfs4_set_dewegation_event, name, \
			TP_PWOTO( \
				const stwuct inode *inode, \
				fmode_t fmode \
			), \
			TP_AWGS(inode, fmode))
DEFINE_NFS4_SET_DEWEGATION_EVENT(nfs4_set_dewegation);
DEFINE_NFS4_SET_DEWEGATION_EVENT(nfs4_wecwaim_dewegation);

TWACE_EVENT(nfs4_dewegwetuwn_exit,
		TP_PWOTO(
			const stwuct nfs4_dewegwetuwnawgs *awgs,
			const stwuct nfs4_dewegwetuwnwes *wes,
			int ewwow
		),

		TP_AWGS(awgs, wes, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(unsigned wong, ewwow)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
		),

		TP_fast_assign(
			__entwy->dev = wes->sewvew->s_dev;
			__entwy->fhandwe = nfs_fhandwe_hash(awgs->fhandwe);
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->stateid_seq =
				be32_to_cpu(awgs->stateid->seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(awgs->stateid);
		),

		TP_pwintk(
			"ewwow=%wd (%s) dev=%02x:%02x fhandwe=0x%08x "
			"stateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash
		)
);

#ifdef CONFIG_NFS_V4_1
DECWAWE_EVENT_CWASS(nfs4_test_stateid_event,
		TP_PWOTO(
			const stwuct nfs4_state *state,
			const stwuct nfs4_wock_state *wsp,
			int ewwow
		),

		TP_AWGS(state, wsp, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
		),

		TP_fast_assign(
			const stwuct inode *inode = state->inode;

			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&state->stateid);
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"stateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash
		)
);

#define DEFINE_NFS4_TEST_STATEID_EVENT(name) \
	DEFINE_EVENT(nfs4_test_stateid_event, name, \
			TP_PWOTO( \
				const stwuct nfs4_state *state, \
				const stwuct nfs4_wock_state *wsp, \
				int ewwow \
			), \
			TP_AWGS(state, wsp, ewwow))
DEFINE_NFS4_TEST_STATEID_EVENT(nfs4_test_dewegation_stateid);
DEFINE_NFS4_TEST_STATEID_EVENT(nfs4_test_open_stateid);
DEFINE_NFS4_TEST_STATEID_EVENT(nfs4_test_wock_stateid);
#endif /* CONFIG_NFS_V4_1 */

DECWAWE_EVENT_CWASS(nfs4_wookup_event,
		TP_PWOTO(
			const stwuct inode *diw,
			const stwuct qstw *name,
			int ewwow
		),

		TP_AWGS(diw, name, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(unsigned wong, ewwow)
			__fiewd(u64, diw)
			__stwing(name, name->name)
		),

		TP_fast_assign(
			__entwy->dev = diw->i_sb->s_dev;
			__entwy->diw = NFS_FIWEID(diw);
			__entwy->ewwow = -ewwow;
			__assign_stw(name, name->name);
		),

		TP_pwintk(
			"ewwow=%wd (%s) name=%02x:%02x:%wwu/%s",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->diw,
			__get_stw(name)
		)
);

#define DEFINE_NFS4_WOOKUP_EVENT(name) \
	DEFINE_EVENT(nfs4_wookup_event, name, \
			TP_PWOTO( \
				const stwuct inode *diw, \
				const stwuct qstw *name, \
				int ewwow \
			), \
			TP_AWGS(diw, name, ewwow))

DEFINE_NFS4_WOOKUP_EVENT(nfs4_wookup);
DEFINE_NFS4_WOOKUP_EVENT(nfs4_symwink);
DEFINE_NFS4_WOOKUP_EVENT(nfs4_mkdiw);
DEFINE_NFS4_WOOKUP_EVENT(nfs4_mknod);
DEFINE_NFS4_WOOKUP_EVENT(nfs4_wemove);
DEFINE_NFS4_WOOKUP_EVENT(nfs4_get_fs_wocations);
DEFINE_NFS4_WOOKUP_EVENT(nfs4_secinfo);

TWACE_EVENT(nfs4_wookupp,
		TP_PWOTO(
			const stwuct inode *inode,
			int ewwow
		),

		TP_AWGS(inode, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u64, ino)
			__fiewd(unsigned wong, ewwow)
		),

		TP_fast_assign(
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->ino = NFS_FIWEID(inode);
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
		),

		TP_pwintk(
			"ewwow=%wd (%s) inode=%02x:%02x:%wwu",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->ino
		)
);

TWACE_EVENT(nfs4_wename,
		TP_PWOTO(
			const stwuct inode *owddiw,
			const stwuct qstw *owdname,
			const stwuct inode *newdiw,
			const stwuct qstw *newname,
			int ewwow
		),

		TP_AWGS(owddiw, owdname, newdiw, newname, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(unsigned wong, ewwow)
			__fiewd(u64, owddiw)
			__stwing(owdname, owdname->name)
			__fiewd(u64, newdiw)
			__stwing(newname, newname->name)
		),

		TP_fast_assign(
			__entwy->dev = owddiw->i_sb->s_dev;
			__entwy->owddiw = NFS_FIWEID(owddiw);
			__entwy->newdiw = NFS_FIWEID(newdiw);
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__assign_stw(owdname, owdname->name);
			__assign_stw(newname, newname->name);
		),

		TP_pwintk(
			"ewwow=%wd (%s) owdname=%02x:%02x:%wwu/%s "
			"newname=%02x:%02x:%wwu/%s",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->owddiw,
			__get_stw(owdname),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->newdiw,
			__get_stw(newname)
		)
);

DECWAWE_EVENT_CWASS(nfs4_inode_event,
		TP_PWOTO(
			const stwuct inode *inode,
			int ewwow
		),

		TP_AWGS(inode, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(unsigned wong, ewwow)
		),

		TP_fast_assign(
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe
		)
);

#define DEFINE_NFS4_INODE_EVENT(name) \
	DEFINE_EVENT(nfs4_inode_event, name, \
			TP_PWOTO( \
				const stwuct inode *inode, \
				int ewwow \
			), \
			TP_AWGS(inode, ewwow))

DEFINE_NFS4_INODE_EVENT(nfs4_access);
DEFINE_NFS4_INODE_EVENT(nfs4_weadwink);
DEFINE_NFS4_INODE_EVENT(nfs4_weaddiw);
DEFINE_NFS4_INODE_EVENT(nfs4_get_acw);
DEFINE_NFS4_INODE_EVENT(nfs4_set_acw);
#ifdef CONFIG_NFS_V4_SECUWITY_WABEW
DEFINE_NFS4_INODE_EVENT(nfs4_get_secuwity_wabew);
DEFINE_NFS4_INODE_EVENT(nfs4_set_secuwity_wabew);
#endif /* CONFIG_NFS_V4_SECUWITY_WABEW */

DECWAWE_EVENT_CWASS(nfs4_inode_stateid_event,
		TP_PWOTO(
			const stwuct inode *inode,
			const nfs4_stateid *stateid,
			int ewwow
		),

		TP_AWGS(inode, stateid, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(unsigned wong, ewwow)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
		),

		TP_fast_assign(
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->stateid_seq =
				be32_to_cpu(stateid->seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(stateid);
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"stateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash
		)
);

#define DEFINE_NFS4_INODE_STATEID_EVENT(name) \
	DEFINE_EVENT(nfs4_inode_stateid_event, name, \
			TP_PWOTO( \
				const stwuct inode *inode, \
				const nfs4_stateid *stateid, \
				int ewwow \
			), \
			TP_AWGS(inode, stateid, ewwow))

DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_setattw);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_dewegwetuwn);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_open_stateid_update);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_open_stateid_update_wait);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_cwose_stateid_update_wait);

DECWAWE_EVENT_CWASS(nfs4_getattw_event,
		TP_PWOTO(
			const stwuct nfs_sewvew *sewvew,
			const stwuct nfs_fh *fhandwe,
			const stwuct nfs_fattw *fattw,
			int ewwow
		),

		TP_AWGS(sewvew, fhandwe, fattw, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(unsigned int, vawid)
			__fiewd(unsigned wong, ewwow)
		),

		TP_fast_assign(
			__entwy->dev = sewvew->s_dev;
			__entwy->vawid = fattw->vawid;
			__entwy->fhandwe = nfs_fhandwe_hash(fhandwe);
			__entwy->fiweid = (fattw->vawid & NFS_ATTW_FATTW_FIWEID) ? fattw->fiweid : 0;
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"vawid=%s",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			show_nfs_fattw_fwags(__entwy->vawid)
		)
);

#define DEFINE_NFS4_GETATTW_EVENT(name) \
	DEFINE_EVENT(nfs4_getattw_event, name, \
			TP_PWOTO( \
				const stwuct nfs_sewvew *sewvew, \
				const stwuct nfs_fh *fhandwe, \
				const stwuct nfs_fattw *fattw, \
				int ewwow \
			), \
			TP_AWGS(sewvew, fhandwe, fattw, ewwow))
DEFINE_NFS4_GETATTW_EVENT(nfs4_getattw);
DEFINE_NFS4_GETATTW_EVENT(nfs4_wookup_woot);
DEFINE_NFS4_GETATTW_EVENT(nfs4_fsinfo);

DECWAWE_EVENT_CWASS(nfs4_inode_cawwback_event,
		TP_PWOTO(
			const stwuct nfs_cwient *cwp,
			const stwuct nfs_fh *fhandwe,
			const stwuct inode *inode,
			int ewwow
		),

		TP_AWGS(cwp, fhandwe, inode, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__stwing(dstaddw, cwp ? cwp->cw_hostname : "unknown")
		),

		TP_fast_assign(
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->fhandwe = nfs_fhandwe_hash(fhandwe);
			if (!IS_EWW_OW_NUWW(inode)) {
				__entwy->fiweid = NFS_FIWEID(inode);
				__entwy->dev = inode->i_sb->s_dev;
			} ewse {
				__entwy->fiweid = 0;
				__entwy->dev = 0;
			}
			__assign_stw(dstaddw, cwp ? cwp->cw_hostname : "unknown");
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"dstaddw=%s",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__get_stw(dstaddw)
		)
);

#define DEFINE_NFS4_INODE_CAWWBACK_EVENT(name) \
	DEFINE_EVENT(nfs4_inode_cawwback_event, name, \
			TP_PWOTO( \
				const stwuct nfs_cwient *cwp, \
				const stwuct nfs_fh *fhandwe, \
				const stwuct inode *inode, \
				int ewwow \
			), \
			TP_AWGS(cwp, fhandwe, inode, ewwow))
DEFINE_NFS4_INODE_CAWWBACK_EVENT(nfs4_cb_getattw);

DECWAWE_EVENT_CWASS(nfs4_inode_stateid_cawwback_event,
		TP_PWOTO(
			const stwuct nfs_cwient *cwp,
			const stwuct nfs_fh *fhandwe,
			const stwuct inode *inode,
			const nfs4_stateid *stateid,
			int ewwow
		),

		TP_AWGS(cwp, fhandwe, inode, stateid, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__stwing(dstaddw, cwp ? cwp->cw_hostname : "unknown")
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
		),

		TP_fast_assign(
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->fhandwe = nfs_fhandwe_hash(fhandwe);
			if (!IS_EWW_OW_NUWW(inode)) {
				__entwy->fiweid = NFS_FIWEID(inode);
				__entwy->dev = inode->i_sb->s_dev;
			} ewse {
				__entwy->fiweid = 0;
				__entwy->dev = 0;
			}
			__assign_stw(dstaddw, cwp ? cwp->cw_hostname : "unknown");
			__entwy->stateid_seq =
				be32_to_cpu(stateid->seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(stateid);
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"stateid=%d:0x%08x dstaddw=%s",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash,
			__get_stw(dstaddw)
		)
);

#define DEFINE_NFS4_INODE_STATEID_CAWWBACK_EVENT(name) \
	DEFINE_EVENT(nfs4_inode_stateid_cawwback_event, name, \
			TP_PWOTO( \
				const stwuct nfs_cwient *cwp, \
				const stwuct nfs_fh *fhandwe, \
				const stwuct inode *inode, \
				const nfs4_stateid *stateid, \
				int ewwow \
			), \
			TP_AWGS(cwp, fhandwe, inode, stateid, ewwow))
DEFINE_NFS4_INODE_STATEID_CAWWBACK_EVENT(nfs4_cb_wecaww);
DEFINE_NFS4_INODE_STATEID_CAWWBACK_EVENT(nfs4_cb_wayoutwecaww_fiwe);

DECWAWE_EVENT_CWASS(nfs4_idmap_event,
		TP_PWOTO(
			const chaw *name,
			int wen,
			u32 id,
			int ewwow
		),

		TP_AWGS(name, wen, id, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(u32, id)
			__dynamic_awway(chaw, name, wen > 0 ? wen + 1 : 1)
		),

		TP_fast_assign(
			if (wen < 0)
				wen = 0;
			__entwy->ewwow = ewwow < 0 ? ewwow : 0;
			__entwy->id = id;
			memcpy(__get_stw(name), name, wen);
			__get_stw(name)[wen] = 0;
		),

		TP_pwintk(
			"ewwow=%wd (%s) id=%u name=%s",
			-__entwy->ewwow, show_nfs4_status(__entwy->ewwow),
			__entwy->id,
			__get_stw(name)
		)
);
#define DEFINE_NFS4_IDMAP_EVENT(name) \
	DEFINE_EVENT(nfs4_idmap_event, name, \
			TP_PWOTO( \
				const chaw *name, \
				int wen, \
				u32 id, \
				int ewwow \
			), \
			TP_AWGS(name, wen, id, ewwow))
DEFINE_NFS4_IDMAP_EVENT(nfs4_map_name_to_uid);
DEFINE_NFS4_IDMAP_EVENT(nfs4_map_gwoup_to_gid);
DEFINE_NFS4_IDMAP_EVENT(nfs4_map_uid_to_name);
DEFINE_NFS4_IDMAP_EVENT(nfs4_map_gid_to_gwoup);

#ifdef CONFIG_NFS_V4_1
#define NFS4_WSEG_WAYOUT_STATEID_HASH(wseg) \
	(wseg ? nfs_stateid_hash(&wseg->pws_wayout->pwh_stateid) : 0)
#ewse
#define NFS4_WSEG_WAYOUT_STATEID_HASH(wseg) (0)
#endif

DECWAWE_EVENT_CWASS(nfs4_wead_event,
		TP_PWOTO(
			const stwuct nfs_pgio_headew *hdw,
			int ewwow
		),

		TP_AWGS(hdw, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(woff_t, offset)
			__fiewd(u32, awg_count)
			__fiewd(u32, wes_count)
			__fiewd(unsigned wong, ewwow)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
			__fiewd(int, wayoutstateid_seq)
			__fiewd(u32, wayoutstateid_hash)
		),

		TP_fast_assign(
			const stwuct inode *inode = hdw->inode;
			const stwuct nfs_inode *nfsi = NFS_I(inode);
			const stwuct nfs_fh *fh = hdw->awgs.fh ?
						  hdw->awgs.fh : &nfsi->fh;
			const stwuct nfs4_state *state =
				hdw->awgs.context->state;
			const stwuct pnfs_wayout_segment *wseg = hdw->wseg;

			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = nfsi->fiweid;
			__entwy->fhandwe = nfs_fhandwe_hash(fh);
			__entwy->offset = hdw->awgs.offset;
			__entwy->awg_count = hdw->awgs.count;
			__entwy->wes_count = hdw->wes.count;
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&state->stateid);
			__entwy->wayoutstateid_seq = wseg ? wseg->pws_seq : 0;
			__entwy->wayoutstateid_hash =
				NFS4_WSEG_WAYOUT_STATEID_HASH(wseg);
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"offset=%wwd count=%u wes=%u stateid=%d:0x%08x "
			"wayoutstateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			(wong wong)__entwy->offset,
			__entwy->awg_count, __entwy->wes_count,
			__entwy->stateid_seq, __entwy->stateid_hash,
			__entwy->wayoutstateid_seq, __entwy->wayoutstateid_hash
		)
);
#define DEFINE_NFS4_WEAD_EVENT(name) \
	DEFINE_EVENT(nfs4_wead_event, name, \
			TP_PWOTO( \
				const stwuct nfs_pgio_headew *hdw, \
				int ewwow \
			), \
			TP_AWGS(hdw, ewwow))
DEFINE_NFS4_WEAD_EVENT(nfs4_wead);
#ifdef CONFIG_NFS_V4_1
DEFINE_NFS4_WEAD_EVENT(nfs4_pnfs_wead);
#endif /* CONFIG_NFS_V4_1 */

DECWAWE_EVENT_CWASS(nfs4_wwite_event,
		TP_PWOTO(
			const stwuct nfs_pgio_headew *hdw,
			int ewwow
		),

		TP_AWGS(hdw, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(woff_t, offset)
			__fiewd(u32, awg_count)
			__fiewd(u32, wes_count)
			__fiewd(unsigned wong, ewwow)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
			__fiewd(int, wayoutstateid_seq)
			__fiewd(u32, wayoutstateid_hash)
		),

		TP_fast_assign(
			const stwuct inode *inode = hdw->inode;
			const stwuct nfs_inode *nfsi = NFS_I(inode);
			const stwuct nfs_fh *fh = hdw->awgs.fh ?
						  hdw->awgs.fh : &nfsi->fh;
			const stwuct nfs4_state *state =
				hdw->awgs.context->state;
			const stwuct pnfs_wayout_segment *wseg = hdw->wseg;

			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = nfsi->fiweid;
			__entwy->fhandwe = nfs_fhandwe_hash(fh);
			__entwy->offset = hdw->awgs.offset;
			__entwy->awg_count = hdw->awgs.count;
			__entwy->wes_count = hdw->wes.count;
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&state->stateid);
			__entwy->wayoutstateid_seq = wseg ? wseg->pws_seq : 0;
			__entwy->wayoutstateid_hash =
				NFS4_WSEG_WAYOUT_STATEID_HASH(wseg);
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"offset=%wwd count=%u wes=%u stateid=%d:0x%08x "
			"wayoutstateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			(wong wong)__entwy->offset,
			__entwy->awg_count, __entwy->wes_count,
			__entwy->stateid_seq, __entwy->stateid_hash,
			__entwy->wayoutstateid_seq, __entwy->wayoutstateid_hash
		)
);

#define DEFINE_NFS4_WWITE_EVENT(name) \
	DEFINE_EVENT(nfs4_wwite_event, name, \
			TP_PWOTO( \
				const stwuct nfs_pgio_headew *hdw, \
				int ewwow \
			), \
			TP_AWGS(hdw, ewwow))
DEFINE_NFS4_WWITE_EVENT(nfs4_wwite);
#ifdef CONFIG_NFS_V4_1
DEFINE_NFS4_WWITE_EVENT(nfs4_pnfs_wwite);
#endif /* CONFIG_NFS_V4_1 */

DECWAWE_EVENT_CWASS(nfs4_commit_event,
		TP_PWOTO(
			const stwuct nfs_commit_data *data,
			int ewwow
		),

		TP_AWGS(data, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(unsigned wong, ewwow)
			__fiewd(woff_t, offset)
			__fiewd(u32, count)
			__fiewd(int, wayoutstateid_seq)
			__fiewd(u32, wayoutstateid_hash)
		),

		TP_fast_assign(
			const stwuct inode *inode = data->inode;
			const stwuct nfs_inode *nfsi = NFS_I(inode);
			const stwuct nfs_fh *fh = data->awgs.fh ?
						  data->awgs.fh : &nfsi->fh;
			const stwuct pnfs_wayout_segment *wseg = data->wseg;

			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = nfsi->fiweid;
			__entwy->fhandwe = nfs_fhandwe_hash(fh);
			__entwy->offset = data->awgs.offset;
			__entwy->count = data->awgs.count;
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->wayoutstateid_seq = wseg ? wseg->pws_seq : 0;
			__entwy->wayoutstateid_hash =
				NFS4_WSEG_WAYOUT_STATEID_HASH(wseg);
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"offset=%wwd count=%u wayoutstateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			(wong wong)__entwy->offset,
			__entwy->count,
			__entwy->wayoutstateid_seq, __entwy->wayoutstateid_hash
		)
);
#define DEFINE_NFS4_COMMIT_EVENT(name) \
	DEFINE_EVENT(nfs4_commit_event, name, \
			TP_PWOTO( \
				const stwuct nfs_commit_data *data, \
				int ewwow \
			), \
			TP_AWGS(data, ewwow))
DEFINE_NFS4_COMMIT_EVENT(nfs4_commit);
#ifdef CONFIG_NFS_V4_1
DEFINE_NFS4_COMMIT_EVENT(nfs4_pnfs_commit_ds);

TWACE_EVENT(nfs4_wayoutget,
		TP_PWOTO(
			const stwuct nfs_open_context *ctx,
			const stwuct pnfs_wayout_wange *awgs,
			const stwuct pnfs_wayout_wange *wes,
			const nfs4_stateid *wayout_stateid,
			int ewwow
		),

		TP_AWGS(ctx, awgs, wes, wayout_stateid, ewwow),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(u32, iomode)
			__fiewd(u64, offset)
			__fiewd(u64, count)
			__fiewd(unsigned wong, ewwow)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
			__fiewd(int, wayoutstateid_seq)
			__fiewd(u32, wayoutstateid_hash)
		),

		TP_fast_assign(
			const stwuct inode *inode = d_inode(ctx->dentwy);
			const stwuct nfs4_state *state = ctx->state;
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->iomode = awgs->iomode;
			__entwy->offset = awgs->offset;
			__entwy->count = awgs->wength;
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&state->stateid);
			if (!ewwow) {
				__entwy->wayoutstateid_seq =
				be32_to_cpu(wayout_stateid->seqid);
				__entwy->wayoutstateid_hash =
				nfs_stateid_hash(wayout_stateid);
			} ewse {
				__entwy->wayoutstateid_seq = 0;
				__entwy->wayoutstateid_hash = 0;
			}
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"iomode=%s offset=%wwu count=%wwu stateid=%d:0x%08x "
			"wayoutstateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			show_pnfs_wayout_iomode(__entwy->iomode),
			(unsigned wong wong)__entwy->offset,
			(unsigned wong wong)__entwy->count,
			__entwy->stateid_seq, __entwy->stateid_hash,
			__entwy->wayoutstateid_seq, __entwy->wayoutstateid_hash
		)
);

DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_wayoutcommit);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_wayoutwetuwn);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_wayoutwetuwn_on_cwose);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_wayoutewwow);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_wayoutstats);

TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_UNKNOWN);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_NO_PNFS);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_WD_ZEWOWEN);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_MDSTHWESH);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_NOMEM);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_BUWK_WECAWW);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_IO_TEST_FAIW);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_FOUND_CACHED);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_WETUWN);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_BWOCKED);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_INVAWID_OPEN);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_WETWY);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_SEND_WAYOUTGET);
TWACE_DEFINE_ENUM(PNFS_UPDATE_WAYOUT_EXIT);

#define show_pnfs_update_wayout_weason(weason)				\
	__pwint_symbowic(weason,					\
		{ PNFS_UPDATE_WAYOUT_UNKNOWN, "unknown" },		\
		{ PNFS_UPDATE_WAYOUT_NO_PNFS, "no pnfs" },		\
		{ PNFS_UPDATE_WAYOUT_WD_ZEWOWEN, "wead+zewowen" },	\
		{ PNFS_UPDATE_WAYOUT_MDSTHWESH, "mdsthwesh" },		\
		{ PNFS_UPDATE_WAYOUT_NOMEM, "nomem" },			\
		{ PNFS_UPDATE_WAYOUT_BUWK_WECAWW, "buwk wecaww" },	\
		{ PNFS_UPDATE_WAYOUT_IO_TEST_FAIW, "io test faiw" },	\
		{ PNFS_UPDATE_WAYOUT_FOUND_CACHED, "found cached" },	\
		{ PNFS_UPDATE_WAYOUT_WETUWN, "wayoutwetuwn" },		\
		{ PNFS_UPDATE_WAYOUT_BWOCKED, "wayouts bwocked" },	\
		{ PNFS_UPDATE_WAYOUT_INVAWID_OPEN, "invawid open" },	\
		{ PNFS_UPDATE_WAYOUT_WETWY, "wetwying" },	\
		{ PNFS_UPDATE_WAYOUT_SEND_WAYOUTGET, "sent wayoutget" }, \
		{ PNFS_UPDATE_WAYOUT_EXIT, "exit" })

TWACE_EVENT(pnfs_update_wayout,
		TP_PWOTO(stwuct inode *inode,
			woff_t pos,
			u64 count,
			enum pnfs_iomode iomode,
			stwuct pnfs_wayout_hdw *wo,
			stwuct pnfs_wayout_segment *wseg,
			enum pnfs_update_wayout_weason weason
		),
		TP_AWGS(inode, pos, count, iomode, wo, wseg, weason),
		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u64, fiweid)
			__fiewd(u32, fhandwe)
			__fiewd(woff_t, pos)
			__fiewd(u64, count)
			__fiewd(enum pnfs_iomode, iomode)
			__fiewd(int, wayoutstateid_seq)
			__fiewd(u32, wayoutstateid_hash)
			__fiewd(wong, wseg)
			__fiewd(enum pnfs_update_wayout_weason, weason)
		),
		TP_fast_assign(
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->pos = pos;
			__entwy->count = count;
			__entwy->iomode = iomode;
			__entwy->weason = weason;
			if (wo != NUWW && pnfs_wayout_is_vawid(wo)) {
				__entwy->wayoutstateid_seq =
				be32_to_cpu(wo->pwh_stateid.seqid);
				__entwy->wayoutstateid_hash =
				nfs_stateid_hash(&wo->pwh_stateid);
			} ewse {
				__entwy->wayoutstateid_seq = 0;
				__entwy->wayoutstateid_hash = 0;
			}
			__entwy->wseg = (wong)wseg;
		),
		TP_pwintk(
			"fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"iomode=%s pos=%wwu count=%wwu "
			"wayoutstateid=%d:0x%08x wseg=0x%wx (%s)",
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			show_pnfs_wayout_iomode(__entwy->iomode),
			(unsigned wong wong)__entwy->pos,
			(unsigned wong wong)__entwy->count,
			__entwy->wayoutstateid_seq, __entwy->wayoutstateid_hash,
			__entwy->wseg,
			show_pnfs_update_wayout_weason(__entwy->weason)
		)
);

DECWAWE_EVENT_CWASS(pnfs_wayout_event,
		TP_PWOTO(stwuct inode *inode,
			woff_t pos,
			u64 count,
			enum pnfs_iomode iomode,
			stwuct pnfs_wayout_hdw *wo,
			stwuct pnfs_wayout_segment *wseg
		),
		TP_AWGS(inode, pos, count, iomode, wo, wseg),
		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(u64, fiweid)
			__fiewd(u32, fhandwe)
			__fiewd(woff_t, pos)
			__fiewd(u64, count)
			__fiewd(enum pnfs_iomode, iomode)
			__fiewd(int, wayoutstateid_seq)
			__fiewd(u32, wayoutstateid_hash)
			__fiewd(wong, wseg)
		),
		TP_fast_assign(
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->pos = pos;
			__entwy->count = count;
			__entwy->iomode = iomode;
			if (wo != NUWW && pnfs_wayout_is_vawid(wo)) {
				__entwy->wayoutstateid_seq =
				be32_to_cpu(wo->pwh_stateid.seqid);
				__entwy->wayoutstateid_hash =
				nfs_stateid_hash(&wo->pwh_stateid);
			} ewse {
				__entwy->wayoutstateid_seq = 0;
				__entwy->wayoutstateid_hash = 0;
			}
			__entwy->wseg = (wong)wseg;
		),
		TP_pwintk(
			"fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"iomode=%s pos=%wwu count=%wwu "
			"wayoutstateid=%d:0x%08x wseg=0x%wx",
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			show_pnfs_wayout_iomode(__entwy->iomode),
			(unsigned wong wong)__entwy->pos,
			(unsigned wong wong)__entwy->count,
			__entwy->wayoutstateid_seq, __entwy->wayoutstateid_hash,
			__entwy->wseg
		)
);

#define DEFINE_PNFS_WAYOUT_EVENT(name) \
	DEFINE_EVENT(pnfs_wayout_event, name, \
		TP_PWOTO(stwuct inode *inode, \
			woff_t pos, \
			u64 count, \
			enum pnfs_iomode iomode, \
			stwuct pnfs_wayout_hdw *wo, \
			stwuct pnfs_wayout_segment *wseg \
		), \
		TP_AWGS(inode, pos, count, iomode, wo, wseg))

DEFINE_PNFS_WAYOUT_EVENT(pnfs_mds_fawwback_pg_init_wead);
DEFINE_PNFS_WAYOUT_EVENT(pnfs_mds_fawwback_pg_init_wwite);
DEFINE_PNFS_WAYOUT_EVENT(pnfs_mds_fawwback_pg_get_miwwow_count);
DEFINE_PNFS_WAYOUT_EVENT(pnfs_mds_fawwback_wead_done);
DEFINE_PNFS_WAYOUT_EVENT(pnfs_mds_fawwback_wwite_done);
DEFINE_PNFS_WAYOUT_EVENT(pnfs_mds_fawwback_wead_pagewist);
DEFINE_PNFS_WAYOUT_EVENT(pnfs_mds_fawwback_wwite_pagewist);

DECWAWE_EVENT_CWASS(nfs4_deviceid_event,
		TP_PWOTO(
			const stwuct nfs_cwient *cwp,
			const stwuct nfs4_deviceid *deviceid
		),

		TP_AWGS(cwp, deviceid),

		TP_STWUCT__entwy(
			__stwing(dstaddw, cwp->cw_hostname)
			__awway(unsigned chaw, deviceid, NFS4_DEVICEID4_SIZE)
		),

		TP_fast_assign(
			__assign_stw(dstaddw, cwp->cw_hostname);
			memcpy(__entwy->deviceid, deviceid->data,
			       NFS4_DEVICEID4_SIZE);
		),

		TP_pwintk(
			"deviceid=%s, dstaddw=%s",
			__pwint_hex(__entwy->deviceid, NFS4_DEVICEID4_SIZE),
			__get_stw(dstaddw)
		)
);
#define DEFINE_PNFS_DEVICEID_EVENT(name) \
	DEFINE_EVENT(nfs4_deviceid_event, name, \
			TP_PWOTO(const stwuct nfs_cwient *cwp, \
				const stwuct nfs4_deviceid *deviceid \
			), \
			TP_AWGS(cwp, deviceid))
DEFINE_PNFS_DEVICEID_EVENT(nfs4_deviceid_fwee);

DECWAWE_EVENT_CWASS(nfs4_deviceid_status,
		TP_PWOTO(
			const stwuct nfs_sewvew *sewvew,
			const stwuct nfs4_deviceid *deviceid,
			int status
		),

		TP_AWGS(sewvew, deviceid, status),

		TP_STWUCT__entwy(
			__fiewd(dev_t, dev)
			__fiewd(int, status)
			__stwing(dstaddw, sewvew->nfs_cwient->cw_hostname)
			__awway(unsigned chaw, deviceid, NFS4_DEVICEID4_SIZE)
		),

		TP_fast_assign(
			__entwy->dev = sewvew->s_dev;
			__entwy->status = status;
			__assign_stw(dstaddw, sewvew->nfs_cwient->cw_hostname);
			memcpy(__entwy->deviceid, deviceid->data,
			       NFS4_DEVICEID4_SIZE);
		),

		TP_pwintk(
			"dev=%02x:%02x: deviceid=%s, dstaddw=%s, status=%d",
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			__pwint_hex(__entwy->deviceid, NFS4_DEVICEID4_SIZE),
			__get_stw(dstaddw),
			__entwy->status
		)
);
#define DEFINE_PNFS_DEVICEID_STATUS(name) \
	DEFINE_EVENT(nfs4_deviceid_status, name, \
			TP_PWOTO(const stwuct nfs_sewvew *sewvew, \
				const stwuct nfs4_deviceid *deviceid, \
				int status \
			), \
			TP_AWGS(sewvew, deviceid, status))
DEFINE_PNFS_DEVICEID_STATUS(nfs4_getdeviceinfo);
DEFINE_PNFS_DEVICEID_STATUS(nfs4_find_deviceid);

DECWAWE_EVENT_CWASS(nfs4_fwexfiwes_io_event,
		TP_PWOTO(
			const stwuct nfs_pgio_headew *hdw
		),

		TP_AWGS(hdw),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(woff_t, offset)
			__fiewd(u32, count)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
			__stwing(dstaddw, hdw->ds_cwp ?
				wpc_peewaddw2stw(hdw->ds_cwp->cw_wpccwient,
					WPC_DISPWAY_ADDW) : "unknown")
		),

		TP_fast_assign(
			const stwuct inode *inode = hdw->inode;

			__entwy->ewwow = hdw->wes.op_status;
			__entwy->fhandwe = nfs_fhandwe_hash(hdw->awgs.fh);
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->offset = hdw->awgs.offset;
			__entwy->count = hdw->awgs.count;
			__entwy->stateid_seq =
				be32_to_cpu(hdw->awgs.stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&hdw->awgs.stateid);
			__assign_stw(dstaddw, hdw->ds_cwp ?
				wpc_peewaddw2stw(hdw->ds_cwp->cw_wpccwient,
					WPC_DISPWAY_ADDW) : "unknown");
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"offset=%wwu count=%u stateid=%d:0x%08x dstaddw=%s",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->offset, __entwy->count,
			__entwy->stateid_seq, __entwy->stateid_hash,
			__get_stw(dstaddw)
		)
);

#define DEFINE_NFS4_FWEXFIWES_IO_EVENT(name) \
	DEFINE_EVENT(nfs4_fwexfiwes_io_event, name, \
			TP_PWOTO( \
				const stwuct nfs_pgio_headew *hdw \
			), \
			TP_AWGS(hdw))
DEFINE_NFS4_FWEXFIWES_IO_EVENT(ff_wayout_wead_ewwow);
DEFINE_NFS4_FWEXFIWES_IO_EVENT(ff_wayout_wwite_ewwow);

TWACE_EVENT(ff_wayout_commit_ewwow,
		TP_PWOTO(
			const stwuct nfs_commit_data *data
		),

		TP_AWGS(data),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(woff_t, offset)
			__fiewd(u32, count)
			__stwing(dstaddw, data->ds_cwp ?
				wpc_peewaddw2stw(data->ds_cwp->cw_wpccwient,
					WPC_DISPWAY_ADDW) : "unknown")
		),

		TP_fast_assign(
			const stwuct inode *inode = data->inode;

			__entwy->ewwow = data->wes.op_status;
			__entwy->fhandwe = nfs_fhandwe_hash(data->awgs.fh);
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->offset = data->awgs.offset;
			__entwy->count = data->awgs.count;
			__assign_stw(dstaddw, data->ds_cwp ?
				wpc_peewaddw2stw(data->ds_cwp->cw_wpccwient,
					WPC_DISPWAY_ADDW) : "unknown");
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"offset=%wwu count=%u dstaddw=%s",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->offset, __entwy->count,
			__get_stw(dstaddw)
		)
);

#ifdef CONFIG_NFS_V4_2
TWACE_DEFINE_ENUM(NFS4_CONTENT_DATA);
TWACE_DEFINE_ENUM(NFS4_CONTENT_HOWE);

#define show_wwseek_mode(what)			\
	__pwint_symbowic(what,			\
		{ NFS4_CONTENT_DATA, "DATA" },		\
		{ NFS4_CONTENT_HOWE, "HOWE" })

TWACE_EVENT(nfs4_wwseek,
		TP_PWOTO(
			const stwuct inode *inode,
			const stwuct nfs42_seek_awgs *awgs,
			const stwuct nfs42_seek_wes *wes,
			int ewwow
		),

		TP_AWGS(inode, awgs, wes, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(u32, fhandwe)
			__fiewd(u32, fiweid)
			__fiewd(dev_t, dev)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
			__fiewd(woff_t, offset_s)
			__fiewd(u32, what)
			__fiewd(woff_t, offset_w)
			__fiewd(u32, eof)
		),

		TP_fast_assign(
			const stwuct nfs_inode *nfsi = NFS_I(inode);
			const stwuct nfs_fh *fh = awgs->sa_fh;

			__entwy->fiweid = nfsi->fiweid;
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fhandwe = nfs_fhandwe_hash(fh);
			__entwy->offset_s = awgs->sa_offset;
			__entwy->stateid_seq =
				be32_to_cpu(awgs->sa_stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&awgs->sa_stateid);
			__entwy->what = awgs->sa_what;
			if (ewwow) {
				__entwy->ewwow = -ewwow;
				__entwy->offset_w = 0;
				__entwy->eof = 0;
			} ewse {
				__entwy->ewwow = 0;
				__entwy->offset_w = wes->sw_offset;
				__entwy->eof = wes->sw_eof;
			}
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"stateid=%d:0x%08x offset_s=%wwu what=%s "
			"offset_w=%wwu eof=%u",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash,
			__entwy->offset_s,
			show_wwseek_mode(__entwy->what),
			__entwy->offset_w,
			__entwy->eof
		)
);

DECWAWE_EVENT_CWASS(nfs4_spawse_event,
		TP_PWOTO(
			const stwuct inode *inode,
			const stwuct nfs42_fawwoc_awgs *awgs,
			int ewwow
		),

		TP_AWGS(inode, awgs, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(woff_t, offset)
			__fiewd(woff_t, wen)
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
		),

		TP_fast_assign(
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->offset = awgs->fawwoc_offset;
			__entwy->wen = awgs->fawwoc_wength;
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__entwy->stateid_seq =
				be32_to_cpu(awgs->fawwoc_stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&awgs->fawwoc_stateid);
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"stateid=%d:0x%08x offset=%wwu wen=%wwu",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash,
			(wong wong)__entwy->offset,
			(wong wong)__entwy->wen
		)
);
#define DEFINE_NFS4_SPAWSE_EVENT(name) \
	DEFINE_EVENT(nfs4_spawse_event, name, \
			TP_PWOTO( \
				const stwuct inode *inode, \
				const stwuct nfs42_fawwoc_awgs *awgs, \
				int ewwow \
			), \
			TP_AWGS(inode, awgs, ewwow))
DEFINE_NFS4_SPAWSE_EVENT(nfs4_fawwocate);
DEFINE_NFS4_SPAWSE_EVENT(nfs4_deawwocate);

TWACE_EVENT(nfs4_copy,
		TP_PWOTO(
			const stwuct inode *swc_inode,
			const stwuct inode *dst_inode,
			const stwuct nfs42_copy_awgs *awgs,
			const stwuct nfs42_copy_wes *wes,
			const stwuct nw4_sewvew *nss,
			int ewwow
		),

		TP_AWGS(swc_inode, dst_inode, awgs, wes, nss, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(u32, swc_fhandwe)
			__fiewd(u32, swc_fiweid)
			__fiewd(u32, dst_fhandwe)
			__fiewd(u32, dst_fiweid)
			__fiewd(dev_t, swc_dev)
			__fiewd(dev_t, dst_dev)
			__fiewd(int, swc_stateid_seq)
			__fiewd(u32, swc_stateid_hash)
			__fiewd(int, dst_stateid_seq)
			__fiewd(u32, dst_stateid_hash)
			__fiewd(woff_t, swc_offset)
			__fiewd(woff_t, dst_offset)
			__fiewd(boow, sync)
			__fiewd(woff_t, wen)
			__fiewd(int, wes_stateid_seq)
			__fiewd(u32, wes_stateid_hash)
			__fiewd(woff_t, wes_count)
			__fiewd(boow, wes_sync)
			__fiewd(boow, wes_cons)
			__fiewd(boow, intwa)
		),

		TP_fast_assign(
			const stwuct nfs_inode *swc_nfsi = NFS_I(swc_inode);
			const stwuct nfs_inode *dst_nfsi = NFS_I(dst_inode);

			__entwy->swc_fiweid = swc_nfsi->fiweid;
			__entwy->swc_dev = swc_inode->i_sb->s_dev;
			__entwy->swc_fhandwe = nfs_fhandwe_hash(awgs->swc_fh);
			__entwy->swc_offset = awgs->swc_pos;
			__entwy->dst_fiweid = dst_nfsi->fiweid;
			__entwy->dst_dev = dst_inode->i_sb->s_dev;
			__entwy->dst_fhandwe = nfs_fhandwe_hash(awgs->dst_fh);
			__entwy->dst_offset = awgs->dst_pos;
			__entwy->wen = awgs->count;
			__entwy->sync = awgs->sync;
			__entwy->swc_stateid_seq =
				be32_to_cpu(awgs->swc_stateid.seqid);
			__entwy->swc_stateid_hash =
				nfs_stateid_hash(&awgs->swc_stateid);
			__entwy->dst_stateid_seq =
				be32_to_cpu(awgs->dst_stateid.seqid);
			__entwy->dst_stateid_hash =
				nfs_stateid_hash(&awgs->dst_stateid);
			__entwy->intwa = nss ? 0 : 1;
			if (ewwow) {
				__entwy->ewwow = -ewwow;
				__entwy->wes_stateid_seq = 0;
				__entwy->wes_stateid_hash = 0;
				__entwy->wes_count = 0;
				__entwy->wes_sync = 0;
				__entwy->wes_cons = 0;
			} ewse {
				__entwy->ewwow = 0;
				__entwy->wes_stateid_seq =
					be32_to_cpu(wes->wwite_wes.stateid.seqid);
				__entwy->wes_stateid_hash =
					nfs_stateid_hash(&wes->wwite_wes.stateid);
				__entwy->wes_count = wes->wwite_wes.count;
				__entwy->wes_sync = wes->synchwonous;
				__entwy->wes_cons = wes->consecutive;
			}
		),

		TP_pwintk(
			"ewwow=%wd (%s) intwa=%d swc_fiweid=%02x:%02x:%wwu "
			"swc_fhandwe=0x%08x dst_fiweid=%02x:%02x:%wwu "
			"dst_fhandwe=0x%08x swc_stateid=%d:0x%08x "
			"dst_stateid=%d:0x%08x swc_offset=%wwu dst_offset=%wwu "
			"wen=%wwu sync=%d cb_stateid=%d:0x%08x wes_sync=%d "
			"wes_cons=%d wes_count=%wwu",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			__entwy->intwa,
			MAJOW(__entwy->swc_dev), MINOW(__entwy->swc_dev),
			(unsigned wong wong)__entwy->swc_fiweid,
			__entwy->swc_fhandwe,
			MAJOW(__entwy->dst_dev), MINOW(__entwy->dst_dev),
			(unsigned wong wong)__entwy->dst_fiweid,
			__entwy->dst_fhandwe,
			__entwy->swc_stateid_seq, __entwy->swc_stateid_hash,
			__entwy->dst_stateid_seq, __entwy->dst_stateid_hash,
			__entwy->swc_offset,
			__entwy->dst_offset,
			__entwy->wen,
			__entwy->sync,
			__entwy->wes_stateid_seq, __entwy->wes_stateid_hash,
			__entwy->wes_sync,
			__entwy->wes_cons,
			__entwy->wes_count
		)
);

TWACE_EVENT(nfs4_cwone,
		TP_PWOTO(
			const stwuct inode *swc_inode,
			const stwuct inode *dst_inode,
			const stwuct nfs42_cwone_awgs *awgs,
			int ewwow
		),

		TP_AWGS(swc_inode, dst_inode, awgs, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(u32, swc_fhandwe)
			__fiewd(u32, swc_fiweid)
			__fiewd(u32, dst_fhandwe)
			__fiewd(u32, dst_fiweid)
			__fiewd(dev_t, swc_dev)
			__fiewd(dev_t, dst_dev)
			__fiewd(woff_t, swc_offset)
			__fiewd(woff_t, dst_offset)
			__fiewd(int, swc_stateid_seq)
			__fiewd(u32, swc_stateid_hash)
			__fiewd(int, dst_stateid_seq)
			__fiewd(u32, dst_stateid_hash)
			__fiewd(woff_t, wen)
		),

		TP_fast_assign(
			const stwuct nfs_inode *swc_nfsi = NFS_I(swc_inode);
			const stwuct nfs_inode *dst_nfsi = NFS_I(dst_inode);

			__entwy->swc_fiweid = swc_nfsi->fiweid;
			__entwy->swc_dev = swc_inode->i_sb->s_dev;
			__entwy->swc_fhandwe = nfs_fhandwe_hash(awgs->swc_fh);
			__entwy->swc_offset = awgs->swc_offset;
			__entwy->dst_fiweid = dst_nfsi->fiweid;
			__entwy->dst_dev = dst_inode->i_sb->s_dev;
			__entwy->dst_fhandwe = nfs_fhandwe_hash(awgs->dst_fh);
			__entwy->dst_offset = awgs->dst_offset;
			__entwy->wen = awgs->count;
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->swc_stateid_seq =
				be32_to_cpu(awgs->swc_stateid.seqid);
			__entwy->swc_stateid_hash =
				nfs_stateid_hash(&awgs->swc_stateid);
			__entwy->dst_stateid_seq =
				be32_to_cpu(awgs->dst_stateid.seqid);
			__entwy->dst_stateid_hash =
				nfs_stateid_hash(&awgs->dst_stateid);
		),

		TP_pwintk(
			"ewwow=%wd (%s) swc_fiweid=%02x:%02x:%wwu "
			"swc_fhandwe=0x%08x dst_fiweid=%02x:%02x:%wwu "
			"dst_fhandwe=0x%08x swc_stateid=%d:0x%08x "
			"dst_stateid=%d:0x%08x swc_offset=%wwu "
			"dst_offset=%wwu wen=%wwu",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->swc_dev), MINOW(__entwy->swc_dev),
			(unsigned wong wong)__entwy->swc_fiweid,
			__entwy->swc_fhandwe,
			MAJOW(__entwy->dst_dev), MINOW(__entwy->dst_dev),
			(unsigned wong wong)__entwy->dst_fiweid,
			__entwy->dst_fhandwe,
			__entwy->swc_stateid_seq, __entwy->swc_stateid_hash,
			__entwy->dst_stateid_seq, __entwy->dst_stateid_hash,
			__entwy->swc_offset,
			__entwy->dst_offset,
			__entwy->wen
		)
);

TWACE_EVENT(nfs4_copy_notify,
		TP_PWOTO(
			const stwuct inode *inode,
			const stwuct nfs42_copy_notify_awgs *awgs,
			const stwuct nfs42_copy_notify_wes *wes,
			int ewwow
		),

		TP_AWGS(inode, awgs, wes, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(u32, fhandwe)
			__fiewd(u32, fiweid)
			__fiewd(dev_t, dev)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
			__fiewd(int, wes_stateid_seq)
			__fiewd(u32, wes_stateid_hash)
		),

		TP_fast_assign(
			const stwuct nfs_inode *nfsi = NFS_I(inode);

			__entwy->fiweid = nfsi->fiweid;
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fhandwe = nfs_fhandwe_hash(awgs->cna_swc_fh);
			__entwy->stateid_seq =
				be32_to_cpu(awgs->cna_swc_stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&awgs->cna_swc_stateid);
			if (ewwow) {
				__entwy->ewwow = -ewwow;
				__entwy->wes_stateid_seq = 0;
				__entwy->wes_stateid_hash = 0;
			} ewse {
				__entwy->ewwow = 0;
				__entwy->wes_stateid_seq =
					be32_to_cpu(wes->cnw_stateid.seqid);
				__entwy->wes_stateid_hash =
					nfs_stateid_hash(&wes->cnw_stateid);
			}
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"stateid=%d:0x%08x wes_stateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash,
			__entwy->wes_stateid_seq, __entwy->wes_stateid_hash
		)
);

TWACE_EVENT(nfs4_offwoad_cancew,
		TP_PWOTO(
			const stwuct nfs42_offwoad_status_awgs *awgs,
			int ewwow
		),

		TP_AWGS(awgs, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(u32, fhandwe)
			__fiewd(int, stateid_seq)
			__fiewd(u32, stateid_hash)
		),

		TP_fast_assign(
			__entwy->fhandwe = nfs_fhandwe_hash(awgs->osa_swc_fh);
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->stateid_seq =
				be32_to_cpu(awgs->osa_stateid.seqid);
			__entwy->stateid_hash =
				nfs_stateid_hash(&awgs->osa_stateid);
		),

		TP_pwintk(
			"ewwow=%wd (%s) fhandwe=0x%08x stateid=%d:0x%08x",
			-__entwy->ewwow,
			show_nfs4_status(__entwy->ewwow),
			__entwy->fhandwe,
			__entwy->stateid_seq, __entwy->stateid_hash
		)
);

DECWAWE_EVENT_CWASS(nfs4_xattw_event,
		TP_PWOTO(
			const stwuct inode *inode,
			const chaw *name,
			int ewwow
		),

		TP_AWGS(inode, name, ewwow),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, ewwow)
			__fiewd(dev_t, dev)
			__fiewd(u32, fhandwe)
			__fiewd(u64, fiweid)
			__stwing(name, name)
		),

		TP_fast_assign(
			__entwy->ewwow = ewwow < 0 ? -ewwow : 0;
			__entwy->dev = inode->i_sb->s_dev;
			__entwy->fiweid = NFS_FIWEID(inode);
			__entwy->fhandwe = nfs_fhandwe_hash(NFS_FH(inode));
			__assign_stw(name, name);
		),

		TP_pwintk(
			"ewwow=%wd (%s) fiweid=%02x:%02x:%wwu fhandwe=0x%08x "
			"name=%s",
			-__entwy->ewwow, show_nfs4_status(__entwy->ewwow),
			MAJOW(__entwy->dev), MINOW(__entwy->dev),
			(unsigned wong wong)__entwy->fiweid,
			__entwy->fhandwe, __get_stw(name)
		)
);
#define DEFINE_NFS4_XATTW_EVENT(name) \
	DEFINE_EVENT(nfs4_xattw_event, name,  \
			TP_PWOTO( \
				const stwuct inode *inode, \
				const chaw *name, \
				int ewwow \
			), \
			TP_AWGS(inode, name, ewwow))
DEFINE_NFS4_XATTW_EVENT(nfs4_getxattw);
DEFINE_NFS4_XATTW_EVENT(nfs4_setxattw);
DEFINE_NFS4_XATTW_EVENT(nfs4_wemovexattw);

DEFINE_NFS4_INODE_EVENT(nfs4_wistxattw);
#endif /* CONFIG_NFS_V4_2 */

#endif /* CONFIG_NFS_V4_1 */

#endif /* _TWACE_NFS4_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE nfs4twace
/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
