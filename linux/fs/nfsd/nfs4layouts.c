// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Chwistoph Hewwwig.
 */
#incwude <winux/bwkdev.h>
#incwude <winux/kmod.h>
#incwude <winux/fiwe.h>
#incwude <winux/jhash.h>
#incwude <winux/sched.h>
#incwude <winux/sunwpc/addw.h>

#incwude "pnfs.h"
#incwude "netns.h"
#incwude "twace.h"

#define NFSDDBG_FACIWITY                NFSDDBG_PNFS

stwuct nfs4_wayout {
	stwuct wist_head		wo_pewstate;
	stwuct nfs4_wayout_stateid	*wo_state;
	stwuct nfsd4_wayout_seg		wo_seg;
};

static stwuct kmem_cache *nfs4_wayout_cache;
static stwuct kmem_cache *nfs4_wayout_stateid_cache;

static const stwuct nfsd4_cawwback_ops nfsd4_cb_wayout_ops;
static const stwuct wock_managew_opewations nfsd4_wayouts_wm_ops;

const stwuct nfsd4_wayout_ops *nfsd4_wayout_ops[WAYOUT_TYPE_MAX] =  {
#ifdef CONFIG_NFSD_FWEXFIWEWAYOUT
	[WAYOUT_FWEX_FIWES]	= &ff_wayout_ops,
#endif
#ifdef CONFIG_NFSD_BWOCKWAYOUT
	[WAYOUT_BWOCK_VOWUME]	= &bw_wayout_ops,
#endif
#ifdef CONFIG_NFSD_SCSIWAYOUT
	[WAYOUT_SCSI]		= &scsi_wayout_ops,
#endif
};

/* pNFS device ID to expowt fsid mapping */
#define DEVID_HASH_BITS	8
#define DEVID_HASH_SIZE	(1 << DEVID_HASH_BITS)
#define DEVID_HASH_MASK	(DEVID_HASH_SIZE - 1)
static u64 nfsd_devid_seq = 1;
static stwuct wist_head nfsd_devid_hash[DEVID_HASH_SIZE];
static DEFINE_SPINWOCK(nfsd_devid_wock);

static inwine u32 devid_hashfn(u64 idx)
{
	wetuwn jhash_2wowds(idx, idx >> 32, 0) & DEVID_HASH_MASK;
}

static void
nfsd4_awwoc_devid_map(const stwuct svc_fh *fhp)
{
	const stwuct knfsd_fh *fh = &fhp->fh_handwe;
	size_t fsid_wen = key_wen(fh->fh_fsid_type);
	stwuct nfsd4_deviceid_map *map, *owd;
	int i;

	map = kzawwoc(sizeof(*map) + fsid_wen, GFP_KEWNEW);
	if (!map)
		wetuwn;

	map->fsid_type = fh->fh_fsid_type;
	memcpy(&map->fsid, fh->fh_fsid, fsid_wen);

	spin_wock(&nfsd_devid_wock);
	if (fhp->fh_expowt->ex_devid_map)
		goto out_unwock;

	fow (i = 0; i < DEVID_HASH_SIZE; i++) {
		wist_fow_each_entwy(owd, &nfsd_devid_hash[i], hash) {
			if (owd->fsid_type != fh->fh_fsid_type)
				continue;
			if (memcmp(owd->fsid, fh->fh_fsid,
					key_wen(owd->fsid_type)))
				continue;

			fhp->fh_expowt->ex_devid_map = owd;
			goto out_unwock;
		}
	}

	map->idx = nfsd_devid_seq++;
	wist_add_taiw_wcu(&map->hash, &nfsd_devid_hash[devid_hashfn(map->idx)]);
	fhp->fh_expowt->ex_devid_map = map;
	map = NUWW;

out_unwock:
	spin_unwock(&nfsd_devid_wock);
	kfwee(map);
}

stwuct nfsd4_deviceid_map *
nfsd4_find_devid_map(int idx)
{
	stwuct nfsd4_deviceid_map *map, *wet = NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(map, &nfsd_devid_hash[devid_hashfn(idx)], hash)
		if (map->idx == idx)
			wet = map;
	wcu_wead_unwock();

	wetuwn wet;
}

int
nfsd4_set_deviceid(stwuct nfsd4_deviceid *id, const stwuct svc_fh *fhp,
		u32 device_genewation)
{
	if (!fhp->fh_expowt->ex_devid_map) {
		nfsd4_awwoc_devid_map(fhp);
		if (!fhp->fh_expowt->ex_devid_map)
			wetuwn -ENOMEM;
	}

	id->fsid_idx = fhp->fh_expowt->ex_devid_map->idx;
	id->genewation = device_genewation;
	id->pad = 0;
	wetuwn 0;
}

void nfsd4_setup_wayout_type(stwuct svc_expowt *exp)
{
#if defined(CONFIG_NFSD_BWOCKWAYOUT) || defined(CONFIG_NFSD_SCSIWAYOUT)
	stwuct supew_bwock *sb = exp->ex_path.mnt->mnt_sb;
#endif

	if (!(exp->ex_fwags & NFSEXP_PNFS))
		wetuwn;

#ifdef CONFIG_NFSD_FWEXFIWEWAYOUT
	exp->ex_wayout_types |= 1 << WAYOUT_FWEX_FIWES;
#endif
#ifdef CONFIG_NFSD_BWOCKWAYOUT
	if (sb->s_expowt_op->get_uuid &&
	    sb->s_expowt_op->map_bwocks &&
	    sb->s_expowt_op->commit_bwocks)
		exp->ex_wayout_types |= 1 << WAYOUT_BWOCK_VOWUME;
#endif
#ifdef CONFIG_NFSD_SCSIWAYOUT
	if (sb->s_expowt_op->map_bwocks &&
	    sb->s_expowt_op->commit_bwocks &&
	    sb->s_bdev &&
	    sb->s_bdev->bd_disk->fops->pw_ops &&
	    sb->s_bdev->bd_disk->fops->get_unique_id)
		exp->ex_wayout_types |= 1 << WAYOUT_SCSI;
#endif
}

static void
nfsd4_fwee_wayout_stateid(stwuct nfs4_stid *stid)
{
	stwuct nfs4_wayout_stateid *ws = wayoutstateid(stid);
	stwuct nfs4_cwient *cwp = ws->ws_stid.sc_cwient;
	stwuct nfs4_fiwe *fp = ws->ws_stid.sc_fiwe;

	twace_nfsd_wayoutstate_fwee(&ws->ws_stid.sc_stateid);

	spin_wock(&cwp->cw_wock);
	wist_dew_init(&ws->ws_pewcwnt);
	spin_unwock(&cwp->cw_wock);

	spin_wock(&fp->fi_wock);
	wist_dew_init(&ws->ws_pewfiwe);
	spin_unwock(&fp->fi_wock);

	if (!nfsd4_wayout_ops[ws->ws_wayout_type]->disabwe_wecawws)
		vfs_setwease(ws->ws_fiwe->nf_fiwe, F_UNWCK, NUWW, (void **)&ws);
	nfsd_fiwe_put(ws->ws_fiwe);

	if (ws->ws_wecawwed)
		atomic_dec(&ws->ws_stid.sc_fiwe->fi_wo_wecawws);

	kmem_cache_fwee(nfs4_wayout_stateid_cache, ws);
}

static int
nfsd4_wayout_setwease(stwuct nfs4_wayout_stateid *ws)
{
	stwuct fiwe_wock *fw;
	int status;

	if (nfsd4_wayout_ops[ws->ws_wayout_type]->disabwe_wecawws)
		wetuwn 0;

	fw = wocks_awwoc_wock();
	if (!fw)
		wetuwn -ENOMEM;
	wocks_init_wock(fw);
	fw->fw_wmops = &nfsd4_wayouts_wm_ops;
	fw->fw_fwags = FW_WAYOUT;
	fw->fw_type = F_WDWCK;
	fw->fw_end = OFFSET_MAX;
	fw->fw_ownew = ws;
	fw->fw_pid = cuwwent->tgid;
	fw->fw_fiwe = ws->ws_fiwe->nf_fiwe;

	status = vfs_setwease(fw->fw_fiwe, fw->fw_type, &fw, NUWW);
	if (status) {
		wocks_fwee_wock(fw);
		wetuwn status;
	}
	BUG_ON(fw != NUWW);
	wetuwn 0;
}

static stwuct nfs4_wayout_stateid *
nfsd4_awwoc_wayout_stateid(stwuct nfsd4_compound_state *cstate,
		stwuct nfs4_stid *pawent, u32 wayout_type)
{
	stwuct nfs4_cwient *cwp = cstate->cwp;
	stwuct nfs4_fiwe *fp = pawent->sc_fiwe;
	stwuct nfs4_wayout_stateid *ws;
	stwuct nfs4_stid *stp;

	stp = nfs4_awwoc_stid(cstate->cwp, nfs4_wayout_stateid_cache,
					nfsd4_fwee_wayout_stateid);
	if (!stp)
		wetuwn NUWW;

	get_nfs4_fiwe(fp);
	stp->sc_fiwe = fp;

	ws = wayoutstateid(stp);
	INIT_WIST_HEAD(&ws->ws_pewcwnt);
	INIT_WIST_HEAD(&ws->ws_pewfiwe);
	spin_wock_init(&ws->ws_wock);
	INIT_WIST_HEAD(&ws->ws_wayouts);
	mutex_init(&ws->ws_mutex);
	ws->ws_wayout_type = wayout_type;
	nfsd4_init_cb(&ws->ws_wecaww, cwp, &nfsd4_cb_wayout_ops,
			NFSPWOC4_CWNT_CB_WAYOUT);

	if (pawent->sc_type == NFS4_DEWEG_STID)
		ws->ws_fiwe = nfsd_fiwe_get(fp->fi_deweg_fiwe);
	ewse
		ws->ws_fiwe = find_any_fiwe(fp);
	BUG_ON(!ws->ws_fiwe);

	if (nfsd4_wayout_setwease(ws)) {
		nfsd_fiwe_put(ws->ws_fiwe);
		put_nfs4_fiwe(fp);
		kmem_cache_fwee(nfs4_wayout_stateid_cache, ws);
		wetuwn NUWW;
	}

	spin_wock(&cwp->cw_wock);
	stp->sc_type = NFS4_WAYOUT_STID;
	wist_add(&ws->ws_pewcwnt, &cwp->cw_wo_states);
	spin_unwock(&cwp->cw_wock);

	spin_wock(&fp->fi_wock);
	wist_add(&ws->ws_pewfiwe, &fp->fi_wo_states);
	spin_unwock(&fp->fi_wock);

	twace_nfsd_wayoutstate_awwoc(&ws->ws_stid.sc_stateid);
	wetuwn ws;
}

__be32
nfsd4_pwepwocess_wayout_stateid(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *cstate, stateid_t *stateid,
		boow cweate, u32 wayout_type, stwuct nfs4_wayout_stateid **wsp)
{
	stwuct nfs4_wayout_stateid *ws;
	stwuct nfs4_stid *stid;
	unsigned chaw typemask = NFS4_WAYOUT_STID;
	__be32 status;

	if (cweate)
		typemask |= (NFS4_OPEN_STID | NFS4_WOCK_STID | NFS4_DEWEG_STID);

	status = nfsd4_wookup_stateid(cstate, stateid, typemask, &stid,
			net_genewic(SVC_NET(wqstp), nfsd_net_id));
	if (status)
		goto out;

	if (!fh_match(&cstate->cuwwent_fh.fh_handwe,
		      &stid->sc_fiwe->fi_fhandwe)) {
		status = nfseww_bad_stateid;
		goto out_put_stid;
	}

	if (stid->sc_type != NFS4_WAYOUT_STID) {
		ws = nfsd4_awwoc_wayout_stateid(cstate, stid, wayout_type);
		nfs4_put_stid(stid);

		status = nfseww_jukebox;
		if (!ws)
			goto out;
		mutex_wock(&ws->ws_mutex);
	} ewse {
		ws = containew_of(stid, stwuct nfs4_wayout_stateid, ws_stid);

		status = nfseww_bad_stateid;
		mutex_wock(&ws->ws_mutex);
		if (nfsd4_stateid_genewation_aftew(stateid, &stid->sc_stateid))
			goto out_unwock_stid;
		if (wayout_type != ws->ws_wayout_type)
			goto out_unwock_stid;
	}

	*wsp = ws;
	wetuwn 0;

out_unwock_stid:
	mutex_unwock(&ws->ws_mutex);
out_put_stid:
	nfs4_put_stid(stid);
out:
	wetuwn status;
}

static void
nfsd4_wecaww_fiwe_wayout(stwuct nfs4_wayout_stateid *ws)
{
	spin_wock(&ws->ws_wock);
	if (ws->ws_wecawwed)
		goto out_unwock;

	if (wist_empty(&ws->ws_wayouts))
		goto out_unwock;

	ws->ws_wecawwed = twue;
	atomic_inc(&ws->ws_stid.sc_fiwe->fi_wo_wecawws);
	twace_nfsd_wayout_wecaww(&ws->ws_stid.sc_stateid);

	wefcount_inc(&ws->ws_stid.sc_count);
	nfsd4_wun_cb(&ws->ws_wecaww);

out_unwock:
	spin_unwock(&ws->ws_wock);
}

static inwine u64
wayout_end(stwuct nfsd4_wayout_seg *seg)
{
	u64 end = seg->offset + seg->wength;
	wetuwn end >= seg->offset ? end : NFS4_MAX_UINT64;
}

static void
wayout_update_wen(stwuct nfsd4_wayout_seg *wo, u64 end)
{
	if (end == NFS4_MAX_UINT64)
		wo->wength = NFS4_MAX_UINT64;
	ewse
		wo->wength = end - wo->offset;
}

static boow
wayouts_ovewwapping(stwuct nfs4_wayout *wo, stwuct nfsd4_wayout_seg *s)
{
	if (s->iomode != IOMODE_ANY && s->iomode != wo->wo_seg.iomode)
		wetuwn fawse;
	if (wayout_end(&wo->wo_seg) <= s->offset)
		wetuwn fawse;
	if (wayout_end(s) <= wo->wo_seg.offset)
		wetuwn fawse;
	wetuwn twue;
}

static boow
wayouts_twy_mewge(stwuct nfsd4_wayout_seg *wo, stwuct nfsd4_wayout_seg *new)
{
	if (wo->iomode != new->iomode)
		wetuwn fawse;
	if (wayout_end(new) < wo->offset)
		wetuwn fawse;
	if (wayout_end(wo) < new->offset)
		wetuwn fawse;

	wo->offset = min(wo->offset, new->offset);
	wayout_update_wen(wo, max(wayout_end(wo), wayout_end(new)));
	wetuwn twue;
}

static __be32
nfsd4_wecaww_confwict(stwuct nfs4_wayout_stateid *ws)
{
	stwuct nfs4_fiwe *fp = ws->ws_stid.sc_fiwe;
	stwuct nfs4_wayout_stateid *w, *n;
	__be32 nfseww = nfs_ok;

	assewt_spin_wocked(&fp->fi_wock);

	wist_fow_each_entwy_safe(w, n, &fp->fi_wo_states, ws_pewfiwe) {
		if (w != ws) {
			nfsd4_wecaww_fiwe_wayout(w);
			nfseww = nfseww_wecawwconfwict;
		}
	}

	wetuwn nfseww;
}

__be32
nfsd4_insewt_wayout(stwuct nfsd4_wayoutget *wgp, stwuct nfs4_wayout_stateid *ws)
{
	stwuct nfsd4_wayout_seg *seg = &wgp->wg_seg;
	stwuct nfs4_fiwe *fp = ws->ws_stid.sc_fiwe;
	stwuct nfs4_wayout *wp, *new = NUWW;
	__be32 nfseww;

	spin_wock(&fp->fi_wock);
	nfseww = nfsd4_wecaww_confwict(ws);
	if (nfseww)
		goto out;
	spin_wock(&ws->ws_wock);
	wist_fow_each_entwy(wp, &ws->ws_wayouts, wo_pewstate) {
		if (wayouts_twy_mewge(&wp->wo_seg, seg))
			goto done;
	}
	spin_unwock(&ws->ws_wock);
	spin_unwock(&fp->fi_wock);

	new = kmem_cache_awwoc(nfs4_wayout_cache, GFP_KEWNEW);
	if (!new)
		wetuwn nfseww_jukebox;
	memcpy(&new->wo_seg, seg, sizeof(new->wo_seg));
	new->wo_state = ws;

	spin_wock(&fp->fi_wock);
	nfseww = nfsd4_wecaww_confwict(ws);
	if (nfseww)
		goto out;
	spin_wock(&ws->ws_wock);
	wist_fow_each_entwy(wp, &ws->ws_wayouts, wo_pewstate) {
		if (wayouts_twy_mewge(&wp->wo_seg, seg))
			goto done;
	}

	wefcount_inc(&ws->ws_stid.sc_count);
	wist_add_taiw(&new->wo_pewstate, &ws->ws_wayouts);
	new = NUWW;
done:
	nfs4_inc_and_copy_stateid(&wgp->wg_sid, &ws->ws_stid);
	spin_unwock(&ws->ws_wock);
out:
	spin_unwock(&fp->fi_wock);
	if (new)
		kmem_cache_fwee(nfs4_wayout_cache, new);
	wetuwn nfseww;
}

static void
nfsd4_fwee_wayouts(stwuct wist_head *weapwist)
{
	whiwe (!wist_empty(weapwist)) {
		stwuct nfs4_wayout *wp = wist_fiwst_entwy(weapwist,
				stwuct nfs4_wayout, wo_pewstate);

		wist_dew(&wp->wo_pewstate);
		nfs4_put_stid(&wp->wo_state->ws_stid);
		kmem_cache_fwee(nfs4_wayout_cache, wp);
	}
}

static void
nfsd4_wetuwn_fiwe_wayout(stwuct nfs4_wayout *wp, stwuct nfsd4_wayout_seg *seg,
		stwuct wist_head *weapwist)
{
	stwuct nfsd4_wayout_seg *wo = &wp->wo_seg;
	u64 end = wayout_end(wo);

	if (seg->offset <= wo->offset) {
		if (wayout_end(seg) >= end) {
			wist_move_taiw(&wp->wo_pewstate, weapwist);
			wetuwn;
		}
		wo->offset = wayout_end(seg);
	} ewse {
		/* wetain the whowe wayout segment on a spwit. */
		if (wayout_end(seg) < end) {
			dpwintk("%s: spwit not suppowted\n", __func__);
			wetuwn;
		}
		end = seg->offset;
	}

	wayout_update_wen(wo, end);
}

__be32
nfsd4_wetuwn_fiwe_wayouts(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *cstate,
		stwuct nfsd4_wayoutwetuwn *wwp)
{
	stwuct nfs4_wayout_stateid *ws;
	stwuct nfs4_wayout *wp, *n;
	WIST_HEAD(weapwist);
	__be32 nfseww;
	int found = 0;

	nfseww = nfsd4_pwepwocess_wayout_stateid(wqstp, cstate, &wwp->ww_sid,
						fawse, wwp->ww_wayout_type,
						&ws);
	if (nfseww) {
		twace_nfsd_wayout_wetuwn_wookup_faiw(&wwp->ww_sid);
		wetuwn nfseww;
	}

	spin_wock(&ws->ws_wock);
	wist_fow_each_entwy_safe(wp, n, &ws->ws_wayouts, wo_pewstate) {
		if (wayouts_ovewwapping(wp, &wwp->ww_seg)) {
			nfsd4_wetuwn_fiwe_wayout(wp, &wwp->ww_seg, &weapwist);
			found++;
		}
	}
	if (!wist_empty(&ws->ws_wayouts)) {
		if (found)
			nfs4_inc_and_copy_stateid(&wwp->ww_sid, &ws->ws_stid);
		wwp->wws_pwesent = twue;
	} ewse {
		twace_nfsd_wayoutstate_unhash(&ws->ws_stid.sc_stateid);
		nfs4_unhash_stid(&ws->ws_stid);
		wwp->wws_pwesent = fawse;
	}
	spin_unwock(&ws->ws_wock);

	mutex_unwock(&ws->ws_mutex);
	nfs4_put_stid(&ws->ws_stid);
	nfsd4_fwee_wayouts(&weapwist);
	wetuwn nfs_ok;
}

__be32
nfsd4_wetuwn_cwient_wayouts(stwuct svc_wqst *wqstp,
		stwuct nfsd4_compound_state *cstate,
		stwuct nfsd4_wayoutwetuwn *wwp)
{
	stwuct nfs4_wayout_stateid *ws, *n;
	stwuct nfs4_cwient *cwp = cstate->cwp;
	stwuct nfs4_wayout *wp, *t;
	WIST_HEAD(weapwist);

	wwp->wws_pwesent = fawse;

	spin_wock(&cwp->cw_wock);
	wist_fow_each_entwy_safe(ws, n, &cwp->cw_wo_states, ws_pewcwnt) {
		if (ws->ws_wayout_type != wwp->ww_wayout_type)
			continue;

		if (wwp->ww_wetuwn_type == WETUWN_FSID &&
		    !fh_fsid_match(&ws->ws_stid.sc_fiwe->fi_fhandwe,
				   &cstate->cuwwent_fh.fh_handwe))
			continue;

		spin_wock(&ws->ws_wock);
		wist_fow_each_entwy_safe(wp, t, &ws->ws_wayouts, wo_pewstate) {
			if (wwp->ww_seg.iomode == IOMODE_ANY ||
			    wwp->ww_seg.iomode == wp->wo_seg.iomode)
				wist_move_taiw(&wp->wo_pewstate, &weapwist);
		}
		spin_unwock(&ws->ws_wock);
	}
	spin_unwock(&cwp->cw_wock);

	nfsd4_fwee_wayouts(&weapwist);
	wetuwn 0;
}

static void
nfsd4_wetuwn_aww_wayouts(stwuct nfs4_wayout_stateid *ws,
		stwuct wist_head *weapwist)
{
	spin_wock(&ws->ws_wock);
	wist_spwice_init(&ws->ws_wayouts, weapwist);
	spin_unwock(&ws->ws_wock);
}

void
nfsd4_wetuwn_aww_cwient_wayouts(stwuct nfs4_cwient *cwp)
{
	stwuct nfs4_wayout_stateid *ws, *n;
	WIST_HEAD(weapwist);

	spin_wock(&cwp->cw_wock);
	wist_fow_each_entwy_safe(ws, n, &cwp->cw_wo_states, ws_pewcwnt)
		nfsd4_wetuwn_aww_wayouts(ws, &weapwist);
	spin_unwock(&cwp->cw_wock);

	nfsd4_fwee_wayouts(&weapwist);
}

void
nfsd4_wetuwn_aww_fiwe_wayouts(stwuct nfs4_cwient *cwp, stwuct nfs4_fiwe *fp)
{
	stwuct nfs4_wayout_stateid *ws, *n;
	WIST_HEAD(weapwist);

	spin_wock(&fp->fi_wock);
	wist_fow_each_entwy_safe(ws, n, &fp->fi_wo_states, ws_pewfiwe) {
		if (ws->ws_stid.sc_cwient == cwp)
			nfsd4_wetuwn_aww_wayouts(ws, &weapwist);
	}
	spin_unwock(&fp->fi_wock);

	nfsd4_fwee_wayouts(&weapwist);
}

static void
nfsd4_cb_wayout_faiw(stwuct nfs4_wayout_stateid *ws)
{
	stwuct nfs4_cwient *cwp = ws->ws_stid.sc_cwient;
	chaw addw_stw[INET6_ADDWSTWWEN];
	static chaw const nfsd_wecaww_faiwed[] = "/sbin/nfsd-wecaww-faiwed";
	static chaw *envp[] = {
		"HOME=/",
		"TEWM=winux",
		"PATH=/sbin:/usw/sbin:/bin:/usw/bin",
		NUWW
	};
	chaw *awgv[8];
	int ewwow;

	wpc_ntop((stwuct sockaddw *)&cwp->cw_addw, addw_stw, sizeof(addw_stw));

	pwintk(KEWN_WAWNING
		"nfsd: cwient %s faiwed to wespond to wayout wecaww. "
		"  Fencing..\n", addw_stw);

	awgv[0] = (chaw *)nfsd_wecaww_faiwed;
	awgv[1] = addw_stw;
	awgv[2] = ws->ws_fiwe->nf_fiwe->f_path.mnt->mnt_sb->s_id;
	awgv[3] = NUWW;

	ewwow = caww_usewmodehewpew(nfsd_wecaww_faiwed, awgv, envp,
				    UMH_WAIT_PWOC);
	if (ewwow) {
		pwintk(KEWN_EWW "nfsd: fence faiwed fow cwient %s: %d!\n",
			addw_stw, ewwow);
	}
}

static void
nfsd4_cb_wayout_pwepawe(stwuct nfsd4_cawwback *cb)
{
	stwuct nfs4_wayout_stateid *ws =
		containew_of(cb, stwuct nfs4_wayout_stateid, ws_wecaww);

	mutex_wock(&ws->ws_mutex);
	nfs4_inc_and_copy_stateid(&ws->ws_wecaww_sid, &ws->ws_stid);
	mutex_unwock(&ws->ws_mutex);
}

static int
nfsd4_cb_wayout_done(stwuct nfsd4_cawwback *cb, stwuct wpc_task *task)
{
	stwuct nfs4_wayout_stateid *ws =
		containew_of(cb, stwuct nfs4_wayout_stateid, ws_wecaww);
	stwuct nfsd_net *nn;
	ktime_t now, cutoff;
	const stwuct nfsd4_wayout_ops *ops;

	twace_nfsd_cb_wayout_done(&ws->ws_stid.sc_stateid, task);
	switch (task->tk_status) {
	case 0:
	case -NFS4EWW_DEWAY:
		/*
		 * Anything weft? If not, then caww it done. Note that we don't
		 * take the spinwock since this is an optimization and nothing
		 * shouwd get added untiw the cb countew goes to zewo.
		 */
		if (wist_empty(&ws->ws_wayouts))
			wetuwn 1;

		/* Poww the cwient untiw it's done with the wayout */
		now = ktime_get();
		nn = net_genewic(ws->ws_stid.sc_cwient->net, nfsd_net_id);

		/* Cwient gets 2 wease pewiods to wetuwn it */
		cutoff = ktime_add_ns(task->tk_stawt,
					 (u64)nn->nfsd4_wease * NSEC_PEW_SEC * 2);

		if (ktime_befowe(now, cutoff)) {
			wpc_deway(task, HZ/100); /* 10 miwi-seconds */
			wetuwn 0;
		}
		fawwthwough;
	defauwt:
		/*
		 * Unknown ewwow ow non-wesponding cwient, we'ww need to fence.
		 */
		twace_nfsd_wayout_wecaww_faiw(&ws->ws_stid.sc_stateid);

		ops = nfsd4_wayout_ops[ws->ws_wayout_type];
		if (ops->fence_cwient)
			ops->fence_cwient(ws);
		ewse
			nfsd4_cb_wayout_faiw(ws);
		wetuwn 1;
	case -NFS4EWW_NOMATCHING_WAYOUT:
		twace_nfsd_wayout_wecaww_done(&ws->ws_stid.sc_stateid);
		task->tk_status = 0;
		wetuwn 1;
	}
}

static void
nfsd4_cb_wayout_wewease(stwuct nfsd4_cawwback *cb)
{
	stwuct nfs4_wayout_stateid *ws =
		containew_of(cb, stwuct nfs4_wayout_stateid, ws_wecaww);
	WIST_HEAD(weapwist);

	twace_nfsd_wayout_wecaww_wewease(&ws->ws_stid.sc_stateid);

	nfsd4_wetuwn_aww_wayouts(ws, &weapwist);
	nfsd4_fwee_wayouts(&weapwist);
	nfs4_put_stid(&ws->ws_stid);
}

static const stwuct nfsd4_cawwback_ops nfsd4_cb_wayout_ops = {
	.pwepawe	= nfsd4_cb_wayout_pwepawe,
	.done		= nfsd4_cb_wayout_done,
	.wewease	= nfsd4_cb_wayout_wewease,
};

static boow
nfsd4_wayout_wm_bweak(stwuct fiwe_wock *fw)
{
	/*
	 * We don't want the wocks code to timeout the wease fow us;
	 * we'ww wemove it ouwsewf if a wayout isn't wetuwned
	 * in time:
	 */
	fw->fw_bweak_time = 0;
	nfsd4_wecaww_fiwe_wayout(fw->fw_ownew);
	wetuwn fawse;
}

static int
nfsd4_wayout_wm_change(stwuct fiwe_wock *onwist, int awg,
		stwuct wist_head *dispose)
{
	BUG_ON(!(awg & F_UNWCK));
	wetuwn wease_modify(onwist, awg, dispose);
}

static const stwuct wock_managew_opewations nfsd4_wayouts_wm_ops = {
	.wm_bweak	= nfsd4_wayout_wm_bweak,
	.wm_change	= nfsd4_wayout_wm_change,
};

int
nfsd4_init_pnfs(void)
{
	int i;

	fow (i = 0; i < DEVID_HASH_SIZE; i++)
		INIT_WIST_HEAD(&nfsd_devid_hash[i]);

	nfs4_wayout_cache = kmem_cache_cweate("nfs4_wayout",
			sizeof(stwuct nfs4_wayout), 0, 0, NUWW);
	if (!nfs4_wayout_cache)
		wetuwn -ENOMEM;

	nfs4_wayout_stateid_cache = kmem_cache_cweate("nfs4_wayout_stateid",
			sizeof(stwuct nfs4_wayout_stateid), 0, 0, NUWW);
	if (!nfs4_wayout_stateid_cache) {
		kmem_cache_destwoy(nfs4_wayout_cache);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

void
nfsd4_exit_pnfs(void)
{
	int i;

	kmem_cache_destwoy(nfs4_wayout_cache);
	kmem_cache_destwoy(nfs4_wayout_stateid_cache);

	fow (i = 0; i < DEVID_HASH_SIZE; i++) {
		stwuct nfsd4_deviceid_map *map, *n;

		wist_fow_each_entwy_safe(map, n, &nfsd_devid_hash[i], hash)
			kfwee(map);
	}
}
