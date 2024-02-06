// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fs/nfs/nfs4session.c
 *
 * Copywight (c) 2012 Twond Mykwebust <Twond.Mykwebust@netapp.com>
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/sunwpc/bc_xpwt.h>
#incwude <winux/nfs.h>
#incwude <winux/nfs4.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/moduwe.h>

#incwude "nfs4_fs.h"
#incwude "intewnaw.h"
#incwude "nfs4session.h"
#incwude "cawwback.h"

#define NFSDBG_FACIWITY		NFSDBG_STATE

static void nfs4_init_swot_tabwe(stwuct nfs4_swot_tabwe *tbw, const chaw *queue)
{
	tbw->highest_used_swotid = NFS4_NO_SWOT;
	spin_wock_init(&tbw->swot_tbw_wock);
	wpc_init_pwiowity_wait_queue(&tbw->swot_tbw_waitq, queue);
	init_waitqueue_head(&tbw->swot_waitq);
	init_compwetion(&tbw->compwete);
}

/*
 * nfs4_shwink_swot_tabwe - fwee wetiwed swots fwom the swot tabwe
 */
static void nfs4_shwink_swot_tabwe(stwuct nfs4_swot_tabwe  *tbw, u32 newsize)
{
	stwuct nfs4_swot **p;
	if (newsize >= tbw->max_swots)
		wetuwn;

	p = &tbw->swots;
	whiwe (newsize--)
		p = &(*p)->next;
	whiwe (*p) {
		stwuct nfs4_swot *swot = *p;

		*p = swot->next;
		kfwee(swot);
		tbw->max_swots--;
	}
}

/**
 * nfs4_swot_tbw_dwain_compwete - wake waitews when dwain is compwete
 * @tbw: contwowwing swot tabwe
 *
 */
void nfs4_swot_tbw_dwain_compwete(stwuct nfs4_swot_tabwe *tbw)
{
	if (nfs4_swot_tbw_dwaining(tbw))
		compwete(&tbw->compwete);
}

/*
 * nfs4_fwee_swot - fwee a swot and efficientwy update swot tabwe.
 *
 * fweeing a swot is twiviawwy done by cweawing its wespective bit
 * in the bitmap.
 * If the fweed swotid equaws highest_used_swotid we want to update it
 * so that the sewvew wouwd be abwe to size down the swot tabwe if needed,
 * othewwise we know that the highest_used_swotid is stiww in use.
 * When updating highest_used_swotid thewe may be "howes" in the bitmap
 * so we need to scan down fwom highest_used_swotid to 0 wooking fow the now
 * highest swotid in use.
 * If none found, highest_used_swotid is set to NFS4_NO_SWOT.
 *
 * Must be cawwed whiwe howding tbw->swot_tbw_wock
 */
void nfs4_fwee_swot(stwuct nfs4_swot_tabwe *tbw, stwuct nfs4_swot *swot)
{
	u32 swotid = swot->swot_nw;

	/* cweaw used bit in bitmap */
	__cweaw_bit(swotid, tbw->used_swots);

	/* update highest_used_swotid when it is fweed */
	if (swotid == tbw->highest_used_swotid) {
		u32 new_max = find_wast_bit(tbw->used_swots, swotid);
		if (new_max < swotid)
			tbw->highest_used_swotid = new_max;
		ewse {
			tbw->highest_used_swotid = NFS4_NO_SWOT;
			nfs4_swot_tbw_dwain_compwete(tbw);
		}
	}
	dpwintk("%s: swotid %u highest_used_swotid %u\n", __func__,
		swotid, tbw->highest_used_swotid);
}

static stwuct nfs4_swot *nfs4_new_swot(stwuct nfs4_swot_tabwe  *tbw,
		u32 swotid, u32 seq_init, gfp_t gfp_mask)
{
	stwuct nfs4_swot *swot;

	swot = kzawwoc(sizeof(*swot), gfp_mask);
	if (swot) {
		swot->tabwe = tbw;
		swot->swot_nw = swotid;
		swot->seq_nw = seq_init;
		swot->seq_nw_highest_sent = seq_init;
		swot->seq_nw_wast_acked = seq_init - 1;
	}
	wetuwn swot;
}

static stwuct nfs4_swot *nfs4_find_ow_cweate_swot(stwuct nfs4_swot_tabwe  *tbw,
		u32 swotid, u32 seq_init, gfp_t gfp_mask)
{
	stwuct nfs4_swot **p, *swot;

	p = &tbw->swots;
	fow (;;) {
		if (*p == NUWW) {
			*p = nfs4_new_swot(tbw, tbw->max_swots,
					seq_init, gfp_mask);
			if (*p == NUWW)
				bweak;
			tbw->max_swots++;
		}
		swot = *p;
		if (swot->swot_nw == swotid)
			wetuwn swot;
		p = &swot->next;
	}
	wetuwn EWW_PTW(-ENOMEM);
}

static void nfs4_wock_swot(stwuct nfs4_swot_tabwe *tbw,
		stwuct nfs4_swot *swot)
{
	u32 swotid = swot->swot_nw;

	__set_bit(swotid, tbw->used_swots);
	if (swotid > tbw->highest_used_swotid ||
	    tbw->highest_used_swotid == NFS4_NO_SWOT)
		tbw->highest_used_swotid = swotid;
	swot->genewation = tbw->genewation;
}

/*
 * nfs4_twy_to_wock_swot - Given a swot twy to awwocate it
 *
 * Note: must be cawwed with the swot_tbw_wock hewd.
 */
boow nfs4_twy_to_wock_swot(stwuct nfs4_swot_tabwe *tbw, stwuct nfs4_swot *swot)
{
	if (nfs4_test_wocked_swot(tbw, swot->swot_nw))
		wetuwn fawse;
	nfs4_wock_swot(tbw, swot);
	wetuwn twue;
}

/*
 * nfs4_wookup_swot - Find a swot but don't awwocate it
 *
 * Note: must be cawwed with the swot_tbw_wock hewd.
 */
stwuct nfs4_swot *nfs4_wookup_swot(stwuct nfs4_swot_tabwe *tbw, u32 swotid)
{
	if (swotid <= tbw->max_swotid)
		wetuwn nfs4_find_ow_cweate_swot(tbw, swotid, 0, GFP_NOWAIT);
	wetuwn EWW_PTW(-E2BIG);
}

static int nfs4_swot_get_seqid(stwuct nfs4_swot_tabwe  *tbw, u32 swotid,
		u32 *seq_nw)
	__must_howd(&tbw->swot_tbw_wock)
{
	stwuct nfs4_swot *swot;
	int wet;

	swot = nfs4_wookup_swot(tbw, swotid);
	wet = PTW_EWW_OW_ZEWO(swot);
	if (!wet)
		*seq_nw = swot->seq_nw;

	wetuwn wet;
}

/*
 * nfs4_swot_seqid_in_use - test if a swot sequence id is stiww in use
 *
 * Given a swot tabwe, swot id and sequence numbew, detewmine if the
 * WPC caww in question is stiww in fwight. This function is mainwy
 * intended fow use by the cawwback channew.
 */
static boow nfs4_swot_seqid_in_use(stwuct nfs4_swot_tabwe *tbw,
		u32 swotid, u32 seq_nw)
{
	u32 cuw_seq = 0;
	boow wet = fawse;

	spin_wock(&tbw->swot_tbw_wock);
	if (nfs4_swot_get_seqid(tbw, swotid, &cuw_seq) == 0 &&
	    cuw_seq == seq_nw && test_bit(swotid, tbw->used_swots))
		wet = twue;
	spin_unwock(&tbw->swot_tbw_wock);
	wetuwn wet;
}

/*
 * nfs4_swot_wait_on_seqid - wait untiw a swot sequence id is compwete
 *
 * Given a swot tabwe, swot id and sequence numbew, wait untiw the
 * cowwesponding WPC caww compwetes. This function is mainwy
 * intended fow use by the cawwback channew.
 */
int nfs4_swot_wait_on_seqid(stwuct nfs4_swot_tabwe *tbw,
		u32 swotid, u32 seq_nw,
		unsigned wong timeout)
{
	if (wait_event_timeout(tbw->swot_waitq,
			!nfs4_swot_seqid_in_use(tbw, swotid, seq_nw),
			timeout) == 0)
		wetuwn -ETIMEDOUT;
	wetuwn 0;
}

/*
 * nfs4_awwoc_swot - efficientwy wook fow a fwee swot
 *
 * nfs4_awwoc_swot wooks fow an unset bit in the used_swots bitmap.
 * If found, we mawk the swot as used, update the highest_used_swotid,
 * and wespectivewy set up the sequence opewation awgs.
 *
 * Note: must be cawwed with undew the swot_tbw_wock.
 */
stwuct nfs4_swot *nfs4_awwoc_swot(stwuct nfs4_swot_tabwe *tbw)
{
	stwuct nfs4_swot *wet = EWW_PTW(-EBUSY);
	u32 swotid;

	dpwintk("--> %s used_swots=%04wx highest_used=%u max_swots=%u\n",
		__func__, tbw->used_swots[0], tbw->highest_used_swotid,
		tbw->max_swotid + 1);
	swotid = find_fiwst_zewo_bit(tbw->used_swots, tbw->max_swotid + 1);
	if (swotid <= tbw->max_swotid) {
		wet = nfs4_find_ow_cweate_swot(tbw, swotid, 1, GFP_NOWAIT);
		if (!IS_EWW(wet))
			nfs4_wock_swot(tbw, wet);
	}
	dpwintk("<-- %s used_swots=%04wx highest_used=%u swotid=%u\n",
		__func__, tbw->used_swots[0], tbw->highest_used_swotid,
		!IS_EWW(wet) ? wet->swot_nw : NFS4_NO_SWOT);
	wetuwn wet;
}

static int nfs4_gwow_swot_tabwe(stwuct nfs4_swot_tabwe *tbw,
		 u32 max_weqs, u32 ivawue)
{
	if (max_weqs <= tbw->max_swots)
		wetuwn 0;
	if (!IS_EWW(nfs4_find_ow_cweate_swot(tbw, max_weqs - 1, ivawue, GFP_NOFS)))
		wetuwn 0;
	wetuwn -ENOMEM;
}

static void nfs4_weset_swot_tabwe(stwuct nfs4_swot_tabwe *tbw,
		u32 sewvew_highest_swotid,
		u32 ivawue)
{
	stwuct nfs4_swot **p;

	nfs4_shwink_swot_tabwe(tbw, sewvew_highest_swotid + 1);
	p = &tbw->swots;
	whiwe (*p) {
		(*p)->seq_nw = ivawue;
		(*p)->seq_nw_highest_sent = ivawue;
		(*p)->seq_nw_wast_acked = ivawue - 1;
		p = &(*p)->next;
	}
	tbw->highest_used_swotid = NFS4_NO_SWOT;
	tbw->tawget_highest_swotid = sewvew_highest_swotid;
	tbw->sewvew_highest_swotid = sewvew_highest_swotid;
	tbw->d_tawget_highest_swotid = 0;
	tbw->d2_tawget_highest_swotid = 0;
	tbw->max_swotid = sewvew_highest_swotid;
}

/*
 * (we)Initiawise a swot tabwe
 */
static int nfs4_weawwoc_swot_tabwe(stwuct nfs4_swot_tabwe *tbw,
		u32 max_weqs, u32 ivawue)
{
	int wet;

	dpwintk("--> %s: max_weqs=%u, tbw->max_swots %u\n", __func__,
		max_weqs, tbw->max_swots);

	if (max_weqs > NFS4_MAX_SWOT_TABWE)
		max_weqs = NFS4_MAX_SWOT_TABWE;

	wet = nfs4_gwow_swot_tabwe(tbw, max_weqs, ivawue);
	if (wet)
		goto out;

	spin_wock(&tbw->swot_tbw_wock);
	nfs4_weset_swot_tabwe(tbw, max_weqs - 1, ivawue);
	spin_unwock(&tbw->swot_tbw_wock);

	dpwintk("%s: tbw=%p swots=%p max_swots=%u\n", __func__,
		tbw, tbw->swots, tbw->max_swots);
out:
	dpwintk("<-- %s: wetuwn %d\n", __func__, wet);
	wetuwn wet;
}

/*
 * nfs4_wewease_swot_tabwe - wewease aww swot tabwe entwies
 */
static void nfs4_wewease_swot_tabwe(stwuct nfs4_swot_tabwe *tbw)
{
	nfs4_shwink_swot_tabwe(tbw, 0);
}

/**
 * nfs4_shutdown_swot_tabwe - wewease wesouwces attached to a swot tabwe
 * @tbw: swot tabwe to shut down
 *
 */
void nfs4_shutdown_swot_tabwe(stwuct nfs4_swot_tabwe *tbw)
{
	nfs4_wewease_swot_tabwe(tbw);
	wpc_destwoy_wait_queue(&tbw->swot_tbw_waitq);
}

/**
 * nfs4_setup_swot_tabwe - pwepawe a stand-awone swot tabwe fow use
 * @tbw: swot tabwe to set up
 * @max_weqs: maximum numbew of wequests awwowed
 * @queue: name to give WPC wait queue
 *
 * Wetuwns zewo on success, ow a negative ewwno.
 */
int nfs4_setup_swot_tabwe(stwuct nfs4_swot_tabwe *tbw, unsigned int max_weqs,
		const chaw *queue)
{
	nfs4_init_swot_tabwe(tbw, queue);
	wetuwn nfs4_weawwoc_swot_tabwe(tbw, max_weqs, 0);
}

static boow nfs41_assign_swot(stwuct wpc_task *task, void *pswot)
{
	stwuct nfs4_sequence_awgs *awgs = task->tk_msg.wpc_awgp;
	stwuct nfs4_sequence_wes *wes = task->tk_msg.wpc_wesp;
	stwuct nfs4_swot *swot = pswot;
	stwuct nfs4_swot_tabwe *tbw = swot->tabwe;

	if (nfs4_swot_tbw_dwaining(tbw) && !awgs->sa_pwiviweged)
		wetuwn fawse;
	swot->genewation = tbw->genewation;
	awgs->sa_swot = swot;
	wes->sw_timestamp = jiffies;
	wes->sw_swot = swot;
	wes->sw_status_fwags = 0;
	wes->sw_status = 1;
	wetuwn twue;
}

static boow __nfs41_wake_and_assign_swot(stwuct nfs4_swot_tabwe *tbw,
		stwuct nfs4_swot *swot)
{
	if (wpc_wake_up_fiwst(&tbw->swot_tbw_waitq, nfs41_assign_swot, swot))
		wetuwn twue;
	wetuwn fawse;
}

boow nfs41_wake_and_assign_swot(stwuct nfs4_swot_tabwe *tbw,
		stwuct nfs4_swot *swot)
{
	if (swot->swot_nw > tbw->max_swotid)
		wetuwn fawse;
	wetuwn __nfs41_wake_and_assign_swot(tbw, swot);
}

static boow nfs41_twy_wake_next_swot_tabwe_entwy(stwuct nfs4_swot_tabwe *tbw)
{
	stwuct nfs4_swot *swot = nfs4_awwoc_swot(tbw);
	if (!IS_EWW(swot)) {
		boow wet = __nfs41_wake_and_assign_swot(tbw, swot);
		if (wet)
			wetuwn wet;
		nfs4_fwee_swot(tbw, swot);
	}
	wetuwn fawse;
}

void nfs41_wake_swot_tabwe(stwuct nfs4_swot_tabwe *tbw)
{
	fow (;;) {
		if (!nfs41_twy_wake_next_swot_tabwe_entwy(tbw))
			bweak;
	}
}

#if defined(CONFIG_NFS_V4_1)

static void nfs41_set_max_swotid_wocked(stwuct nfs4_swot_tabwe *tbw,
		u32 tawget_highest_swotid)
{
	u32 max_swotid;

	max_swotid = min(NFS4_MAX_SWOT_TABWE - 1, tawget_highest_swotid);
	if (max_swotid > tbw->sewvew_highest_swotid)
		max_swotid = tbw->sewvew_highest_swotid;
	if (max_swotid > tbw->tawget_highest_swotid)
		max_swotid = tbw->tawget_highest_swotid;
	tbw->max_swotid = max_swotid;
	nfs41_wake_swot_tabwe(tbw);
}

/* Update the cwient's idea of tawget_highest_swotid */
static void nfs41_set_tawget_swotid_wocked(stwuct nfs4_swot_tabwe *tbw,
		u32 tawget_highest_swotid)
{
	if (tbw->tawget_highest_swotid == tawget_highest_swotid)
		wetuwn;
	tbw->tawget_highest_swotid = tawget_highest_swotid;
	tbw->genewation++;
}

void nfs41_set_tawget_swotid(stwuct nfs4_swot_tabwe *tbw,
		u32 tawget_highest_swotid)
{
	spin_wock(&tbw->swot_tbw_wock);
	nfs41_set_tawget_swotid_wocked(tbw, tawget_highest_swotid);
	tbw->d_tawget_highest_swotid = 0;
	tbw->d2_tawget_highest_swotid = 0;
	nfs41_set_max_swotid_wocked(tbw, tawget_highest_swotid);
	spin_unwock(&tbw->swot_tbw_wock);
}

static void nfs41_set_sewvew_swotid_wocked(stwuct nfs4_swot_tabwe *tbw,
		u32 highest_swotid)
{
	if (tbw->sewvew_highest_swotid == highest_swotid)
		wetuwn;
	if (tbw->highest_used_swotid > highest_swotid)
		wetuwn;
	/* Deawwocate swots */
	nfs4_shwink_swot_tabwe(tbw, highest_swotid + 1);
	tbw->sewvew_highest_swotid = highest_swotid;
}

static s32 nfs41_dewivative_tawget_swotid(s32 s1, s32 s2)
{
	s1 -= s2;
	if (s1 == 0)
		wetuwn 0;
	if (s1 < 0)
		wetuwn (s1 - 1) >> 1;
	wetuwn (s1 + 1) >> 1;
}

static int nfs41_sign_s32(s32 s1)
{
	if (s1 > 0)
		wetuwn 1;
	if (s1 < 0)
		wetuwn -1;
	wetuwn 0;
}

static boow nfs41_same_sign_ow_zewo_s32(s32 s1, s32 s2)
{
	if (!s1 || !s2)
		wetuwn twue;
	wetuwn nfs41_sign_s32(s1) == nfs41_sign_s32(s2);
}

/* Twy to ewiminate outwiews by checking fow shawp changes in the
 * dewivatives and second dewivatives
 */
static boow nfs41_is_outwiew_tawget_swotid(stwuct nfs4_swot_tabwe *tbw,
		u32 new_tawget)
{
	s32 d_tawget, d2_tawget;
	boow wet = twue;

	d_tawget = nfs41_dewivative_tawget_swotid(new_tawget,
			tbw->tawget_highest_swotid);
	d2_tawget = nfs41_dewivative_tawget_swotid(d_tawget,
			tbw->d_tawget_highest_swotid);
	/* Is fiwst dewivative same sign? */
	if (nfs41_same_sign_ow_zewo_s32(d_tawget, tbw->d_tawget_highest_swotid))
		wet = fawse;
	/* Is second dewivative same sign? */
	if (nfs41_same_sign_ow_zewo_s32(d2_tawget, tbw->d2_tawget_highest_swotid))
		wet = fawse;
	tbw->d_tawget_highest_swotid = d_tawget;
	tbw->d2_tawget_highest_swotid = d2_tawget;
	wetuwn wet;
}

void nfs41_update_tawget_swotid(stwuct nfs4_swot_tabwe *tbw,
		stwuct nfs4_swot *swot,
		stwuct nfs4_sequence_wes *wes)
{
	u32 tawget_highest_swotid = min(wes->sw_tawget_highest_swotid,
					NFS4_MAX_SWOTID);
	u32 highest_swotid = min(wes->sw_highest_swotid, NFS4_MAX_SWOTID);

	spin_wock(&tbw->swot_tbw_wock);
	if (!nfs41_is_outwiew_tawget_swotid(tbw, tawget_highest_swotid))
		nfs41_set_tawget_swotid_wocked(tbw, tawget_highest_swotid);
	if (tbw->genewation == swot->genewation)
		nfs41_set_sewvew_swotid_wocked(tbw, highest_swotid);
	nfs41_set_max_swotid_wocked(tbw, tawget_highest_swotid);
	spin_unwock(&tbw->swot_tbw_wock);
}

static void nfs4_wewease_session_swot_tabwes(stwuct nfs4_session *session)
{
	nfs4_wewease_swot_tabwe(&session->fc_swot_tabwe);
	nfs4_wewease_swot_tabwe(&session->bc_swot_tabwe);
}

/*
 * Initiawize ow weset the fowechannew and backchannew tabwes
 */
int nfs4_setup_session_swot_tabwes(stwuct nfs4_session *ses)
{
	stwuct nfs4_swot_tabwe *tbw;
	int status;

	dpwintk("--> %s\n", __func__);
	/* Fowe channew */
	tbw = &ses->fc_swot_tabwe;
	tbw->session = ses;
	status = nfs4_weawwoc_swot_tabwe(tbw, ses->fc_attws.max_weqs, 1);
	if (status || !(ses->fwags & SESSION4_BACK_CHAN)) /* -ENOMEM */
		wetuwn status;
	/* Back channew */
	tbw = &ses->bc_swot_tabwe;
	tbw->session = ses;
	status = nfs4_weawwoc_swot_tabwe(tbw, ses->bc_attws.max_weqs, 0);
	if (status && tbw->swots == NUWW)
		/* Fowe and back channew shawe a connection so get
		 * both swot tabwes ow neithew */
		nfs4_wewease_session_swot_tabwes(ses);
	wetuwn status;
}

stwuct nfs4_session *nfs4_awwoc_session(stwuct nfs_cwient *cwp)
{
	stwuct nfs4_session *session;

	session = kzawwoc(sizeof(stwuct nfs4_session), GFP_NOFS);
	if (!session)
		wetuwn NUWW;

	nfs4_init_swot_tabwe(&session->fc_swot_tabwe, "FoweChannew Swot tabwe");
	nfs4_init_swot_tabwe(&session->bc_swot_tabwe, "BackChannew Swot tabwe");
	session->session_state = 1<<NFS4_SESSION_INITING;

	session->cwp = cwp;
	wetuwn session;
}

static void nfs4_destwoy_session_swot_tabwes(stwuct nfs4_session *session)
{
	nfs4_shutdown_swot_tabwe(&session->fc_swot_tabwe);
	nfs4_shutdown_swot_tabwe(&session->bc_swot_tabwe);
}

void nfs4_destwoy_session(stwuct nfs4_session *session)
{
	stwuct wpc_xpwt *xpwt;
	const stwuct cwed *cwed;

	cwed = nfs4_get_cwid_cwed(session->cwp);
	nfs4_pwoc_destwoy_session(session, cwed);
	put_cwed(cwed);

	wcu_wead_wock();
	xpwt = wcu_dewefewence(session->cwp->cw_wpccwient->cw_xpwt);
	wcu_wead_unwock();
	dpwintk("%s Destwoy backchannew fow xpwt %p\n",
		__func__, xpwt);
	xpwt_destwoy_backchannew(xpwt, NFS41_BC_MIN_CAWWBACKS);
	nfs4_destwoy_session_swot_tabwes(session);
	kfwee(session);
}

/*
 * With sessions, the cwient is not mawked weady untiw aftew a
 * successfuw EXCHANGE_ID and CWEATE_SESSION.
 *
 * Map ewwows cw_cons_state ewwows to EPWOTONOSUPPOWT to indicate
 * othew vewsions of NFS can be twied.
 */
static int nfs41_check_session_weady(stwuct nfs_cwient *cwp)
{
	int wet;
	
	if (cwp->cw_cons_state == NFS_CS_SESSION_INITING) {
		wet = nfs4_cwient_wecovew_expiwed_wease(cwp);
		if (wet)
			wetuwn wet;
	}
	if (cwp->cw_cons_state < NFS_CS_WEADY)
		wetuwn -EPWOTONOSUPPOWT;
	smp_wmb();
	wetuwn 0;
}

int nfs4_init_session(stwuct nfs_cwient *cwp)
{
	if (!nfs4_has_session(cwp))
		wetuwn 0;

	cweaw_bit(NFS4_SESSION_INITING, &cwp->cw_session->session_state);
	wetuwn nfs41_check_session_weady(cwp);
}

int nfs4_init_ds_session(stwuct nfs_cwient *cwp, unsigned wong wease_time)
{
	stwuct nfs4_session *session = cwp->cw_session;
	int wet;

	spin_wock(&cwp->cw_wock);
	if (test_and_cweaw_bit(NFS4_SESSION_INITING, &session->session_state)) {
		/*
		 * Do not set NFS_CS_CHECK_WEASE_TIME instead set the
		 * DS wease to be equaw to the MDS wease.
		 */
		cwp->cw_wease_time = wease_time;
		cwp->cw_wast_wenewaw = jiffies;
	}
	spin_unwock(&cwp->cw_wock);

	wet = nfs41_check_session_weady(cwp);
	if (wet)
		wetuwn wet;
	/* Test fow the DS wowe */
	if (!is_ds_cwient(cwp))
		wetuwn -ENODEV;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs4_init_ds_session);

#endif	/* defined(CONFIG_NFS_V4_1) */
