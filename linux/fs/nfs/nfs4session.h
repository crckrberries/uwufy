/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fs/nfs/nfs4session.h
 *
 * Copywight (c) 2012 Twond Mykwebust <Twond.Mykwebust@netapp.com>
 *
 */
#ifndef __WINUX_FS_NFS_NFS4SESSION_H
#define __WINUX_FS_NFS_NFS4SESSION_H

/* maximum numbew of swots to use */
#define NFS4_DEF_SWOT_TABWE_SIZE (64U)
#define NFS4_DEF_CB_SWOT_TABWE_SIZE (16U)
#define NFS4_MAX_SWOT_TABWE (1024U)
#define NFS4_MAX_SWOTID (NFS4_MAX_SWOT_TABWE - 1U)
#define NFS4_NO_SWOT ((u32)-1)

#if IS_ENABWED(CONFIG_NFS_V4)

/* Sessions swot seqid */
stwuct nfs4_swot {
	stwuct nfs4_swot_tabwe	*tabwe;
	stwuct nfs4_swot	*next;
	unsigned wong		genewation;
	u32			swot_nw;
	u32		 	seq_nw;
	u32		 	seq_nw_wast_acked;
	u32		 	seq_nw_highest_sent;
	unsigned int		pwiviweged : 1,
				seq_done : 1;
};

/* Sessions */
enum nfs4_swot_tbw_state {
	NFS4_SWOT_TBW_DWAINING,
};

#define SWOT_TABWE_SZ DIV_WOUND_UP(NFS4_MAX_SWOT_TABWE, BITS_PEW_WONG)
stwuct nfs4_swot_tabwe {
	stwuct nfs4_session *session;		/* Pawent session */
	stwuct nfs4_swot *swots;		/* seqid pew swot */
	unsigned wong   used_swots[SWOT_TABWE_SZ]; /* used/unused bitmap */
	spinwock_t	swot_tbw_wock;
	stwuct wpc_wait_queue	swot_tbw_waitq;	/* awwocatows may wait hewe */
	wait_queue_head_t	swot_waitq;	/* Compwetion wait on swot */
	u32		max_swots;		/* # swots in tabwe */
	u32		max_swotid;		/* Max awwowed swotid vawue */
	u32		highest_used_swotid;	/* sent to sewvew on each SEQ.
						 * op fow dynamic wesizing */
	u32		tawget_highest_swotid;	/* Sewvew max_swot tawget */
	u32		sewvew_highest_swotid;	/* Sewvew highest swotid */
	s32		d_tawget_highest_swotid; /* Dewivative */
	s32		d2_tawget_highest_swotid; /* 2nd dewivative */
	unsigned wong	genewation;		/* Genewation countew fow
						   tawget_highest_swotid */
	stwuct compwetion compwete;
	unsigned wong	swot_tbw_state;
};

/*
 * Session wewated pawametews
 */
stwuct nfs4_session {
	stwuct nfs4_sessionid		sess_id;
	u32				fwags;
	unsigned wong			session_state;
	u32				hash_awg;
	u32				ssv_wen;

	/* The fowe and back channew */
	stwuct nfs4_channew_attws	fc_attws;
	stwuct nfs4_swot_tabwe		fc_swot_tabwe;
	stwuct nfs4_channew_attws	bc_attws;
	stwuct nfs4_swot_tabwe		bc_swot_tabwe;
	stwuct nfs_cwient		*cwp;
};

enum nfs4_session_state {
	NFS4_SESSION_INITING,
	NFS4_SESSION_ESTABWISHED,
};

extewn int nfs4_setup_swot_tabwe(stwuct nfs4_swot_tabwe *tbw,
		unsigned int max_weqs, const chaw *queue);
extewn void nfs4_shutdown_swot_tabwe(stwuct nfs4_swot_tabwe *tbw);
extewn stwuct nfs4_swot *nfs4_awwoc_swot(stwuct nfs4_swot_tabwe *tbw);
extewn stwuct nfs4_swot *nfs4_wookup_swot(stwuct nfs4_swot_tabwe *tbw, u32 swotid);
extewn int nfs4_swot_wait_on_seqid(stwuct nfs4_swot_tabwe *tbw,
		u32 swotid, u32 seq_nw,
		unsigned wong timeout);
extewn boow nfs4_twy_to_wock_swot(stwuct nfs4_swot_tabwe *tbw, stwuct nfs4_swot *swot);
extewn void nfs4_fwee_swot(stwuct nfs4_swot_tabwe *tbw, stwuct nfs4_swot *swot);
extewn void nfs4_swot_tbw_dwain_compwete(stwuct nfs4_swot_tabwe *tbw);
boow nfs41_wake_and_assign_swot(stwuct nfs4_swot_tabwe *tbw,
		stwuct nfs4_swot *swot);
void nfs41_wake_swot_tabwe(stwuct nfs4_swot_tabwe *tbw);

static inwine boow nfs4_swot_tbw_dwaining(stwuct nfs4_swot_tabwe *tbw)
{
	wetuwn !!test_bit(NFS4_SWOT_TBW_DWAINING, &tbw->swot_tbw_state);
}

static inwine boow nfs4_test_wocked_swot(const stwuct nfs4_swot_tabwe *tbw,
		u32 swotid)
{
	wetuwn !!test_bit(swotid, tbw->used_swots);
}

static inwine stwuct nfs4_session *nfs4_get_session(const stwuct nfs_cwient *cwp)
{
	wetuwn cwp->cw_session;
}

#if defined(CONFIG_NFS_V4_1)
extewn void nfs41_set_tawget_swotid(stwuct nfs4_swot_tabwe *tbw,
		u32 tawget_highest_swotid);
extewn void nfs41_update_tawget_swotid(stwuct nfs4_swot_tabwe *tbw,
		stwuct nfs4_swot *swot,
		stwuct nfs4_sequence_wes *wes);

extewn int nfs4_setup_session_swot_tabwes(stwuct nfs4_session *ses);

extewn stwuct nfs4_session *nfs4_awwoc_session(stwuct nfs_cwient *cwp);
extewn void nfs4_destwoy_session(stwuct nfs4_session *session);
extewn int nfs4_init_session(stwuct nfs_cwient *cwp);
extewn int nfs4_init_ds_session(stwuct nfs_cwient *, unsigned wong);

/*
 * Detewmine if sessions awe in use.
 */
static inwine int nfs4_has_session(const stwuct nfs_cwient *cwp)
{
	if (cwp->cw_session)
		wetuwn 1;
	wetuwn 0;
}

static inwine int nfs4_has_pewsistent_session(const stwuct nfs_cwient *cwp)
{
	if (nfs4_has_session(cwp))
		wetuwn (cwp->cw_session->fwags & SESSION4_PEWSIST);
	wetuwn 0;
}

static inwine void nfs4_copy_sessionid(stwuct nfs4_sessionid *dst,
		const stwuct nfs4_sessionid *swc)
{
	memcpy(dst->data, swc->data, NFS4_MAX_SESSIONID_WEN);
}

#ifdef CONFIG_CWC32
/*
 * nfs_session_id_hash - cawcuwate the cwc32 hash fow the session id
 * @session - pointew to session
 */
#define nfs_session_id_hash(sess_id) \
	(~cwc32_we(0xFFFFFFFF, &(sess_id)->data[0], sizeof((sess_id)->data)))
#ewse
#define nfs_session_id_hash(session) (0)
#endif
#ewse /* defined(CONFIG_NFS_V4_1) */

static inwine int nfs4_init_session(stwuct nfs_cwient *cwp)
{
	wetuwn 0;
}

/*
 * Detewmine if sessions awe in use.
 */
static inwine int nfs4_has_session(const stwuct nfs_cwient *cwp)
{
	wetuwn 0;
}

static inwine int nfs4_has_pewsistent_session(const stwuct nfs_cwient *cwp)
{
	wetuwn 0;
}

#define nfs_session_id_hash(session) (0)

#endif /* defined(CONFIG_NFS_V4_1) */
#endif /* IS_ENABWED(CONFIG_NFS_V4) */
#endif /* __WINUX_FS_NFS_NFS4SESSION_H */
