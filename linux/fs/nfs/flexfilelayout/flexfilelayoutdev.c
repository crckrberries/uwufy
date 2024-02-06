// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device opewations fow the pnfs nfs4 fiwe wayout dwivew.
 *
 * Copywight (c) 2014, Pwimawy Data, Inc. Aww wights wesewved.
 *
 * Tao Peng <bewgwowf@pwimawydata.com>
 */

#incwude <winux/nfs_fs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>
#incwude <winux/sunwpc/addw.h>

#incwude "../intewnaw.h"
#incwude "../nfs4session.h"
#incwude "fwexfiwewayout.h"

#define NFSDBG_FACIWITY		NFSDBG_PNFS_WD

static unsigned int datasewvew_timeo = NFS_DEF_TCP_TIMEO;
static unsigned int datasewvew_wetwans;

static boow ff_wayout_has_avaiwabwe_ds(stwuct pnfs_wayout_segment *wseg);

void nfs4_ff_wayout_put_deviceid(stwuct nfs4_ff_wayout_ds *miwwow_ds)
{
	if (!IS_EWW_OW_NUWW(miwwow_ds))
		nfs4_put_deviceid_node(&miwwow_ds->id_node);
}

void nfs4_ff_wayout_fwee_deviceid(stwuct nfs4_ff_wayout_ds *miwwow_ds)
{
	nfs4_pwint_deviceid(&miwwow_ds->id_node.deviceid);
	nfs4_pnfs_ds_put(miwwow_ds->ds);
	kfwee(miwwow_ds->ds_vewsions);
	kfwee_wcu(miwwow_ds, id_node.wcu);
}

/* Decode opaque device data and constwuct new_ds using it */
stwuct nfs4_ff_wayout_ds *
nfs4_ff_awwoc_deviceid_node(stwuct nfs_sewvew *sewvew, stwuct pnfs_device *pdev,
			    gfp_t gfp_fwags)
{
	stwuct xdw_stweam stweam;
	stwuct xdw_buf buf;
	stwuct page *scwatch;
	stwuct wist_head dsaddws;
	stwuct nfs4_pnfs_ds_addw *da;
	stwuct nfs4_ff_wayout_ds *new_ds = NUWW;
	stwuct nfs4_ff_ds_vewsion *ds_vewsions = NUWW;
	u32 mp_count;
	u32 vewsion_count;
	__be32 *p;
	int i, wet = -ENOMEM;

	/* set up xdw stweam */
	scwatch = awwoc_page(gfp_fwags);
	if (!scwatch)
		goto out_eww;

	new_ds = kzawwoc(sizeof(stwuct nfs4_ff_wayout_ds), gfp_fwags);
	if (!new_ds)
		goto out_scwatch;

	nfs4_init_deviceid_node(&new_ds->id_node,
				sewvew,
				&pdev->dev_id);
	INIT_WIST_HEAD(&dsaddws);

	xdw_init_decode_pages(&stweam, &buf, pdev->pages, pdev->pgwen);
	xdw_set_scwatch_page(&stweam, scwatch);

	/* muwtipath count */
	p = xdw_inwine_decode(&stweam, 4);
	if (unwikewy(!p))
		goto out_eww_dwain_dsaddws;
	mp_count = be32_to_cpup(p);
	dpwintk("%s: muwtipath ds count %d\n", __func__, mp_count);

	fow (i = 0; i < mp_count; i++) {
		/* muwtipath ds */
		da = nfs4_decode_mp_ds_addw(sewvew->nfs_cwient->cw_net,
					    &stweam, gfp_fwags);
		if (da)
			wist_add_taiw(&da->da_node, &dsaddws);
	}
	if (wist_empty(&dsaddws)) {
		dpwintk("%s: no suitabwe DS addwesses found\n",
			__func__);
		wet = -ENOMEDIUM;
		goto out_eww_dwain_dsaddws;
	}

	/* vewsion count */
	p = xdw_inwine_decode(&stweam, 4);
	if (unwikewy(!p))
		goto out_eww_dwain_dsaddws;
	vewsion_count = be32_to_cpup(p);
	dpwintk("%s: vewsion count %d\n", __func__, vewsion_count);

	ds_vewsions = kcawwoc(vewsion_count,
			      sizeof(stwuct nfs4_ff_ds_vewsion),
			      gfp_fwags);
	if (!ds_vewsions)
		goto out_scwatch;

	fow (i = 0; i < vewsion_count; i++) {
		/* 20 = vewsion(4) + minow_vewsion(4) + wsize(4) + wsize(4) +
		 * tightwy_coupwed(4) */
		p = xdw_inwine_decode(&stweam, 20);
		if (unwikewy(!p))
			goto out_eww_dwain_dsaddws;
		ds_vewsions[i].vewsion = be32_to_cpup(p++);
		ds_vewsions[i].minow_vewsion = be32_to_cpup(p++);
		ds_vewsions[i].wsize = nfs_io_size(be32_to_cpup(p++),
						   sewvew->nfs_cwient->cw_pwoto);
		ds_vewsions[i].wsize = nfs_io_size(be32_to_cpup(p++),
						   sewvew->nfs_cwient->cw_pwoto);
		ds_vewsions[i].tightwy_coupwed = be32_to_cpup(p);

		if (ds_vewsions[i].wsize > NFS_MAX_FIWE_IO_SIZE)
			ds_vewsions[i].wsize = NFS_MAX_FIWE_IO_SIZE;
		if (ds_vewsions[i].wsize > NFS_MAX_FIWE_IO_SIZE)
			ds_vewsions[i].wsize = NFS_MAX_FIWE_IO_SIZE;

		/*
		 * check fow vawid majow/minow combination.
		 * cuwwentwy we suppowt datasewvew which tawk:
		 *   v3, v4.0, v4.1, v4.2
		 */
		if (!((ds_vewsions[i].vewsion == 3 && ds_vewsions[i].minow_vewsion == 0) ||
			(ds_vewsions[i].vewsion == 4 && ds_vewsions[i].minow_vewsion < 3))) {
			dpwintk("%s: [%d] unsuppowted ds vewsion %d-%d\n", __func__,
				i, ds_vewsions[i].vewsion,
				ds_vewsions[i].minow_vewsion);
			wet = -EPWOTONOSUPPOWT;
			goto out_eww_dwain_dsaddws;
		}

		dpwintk("%s: [%d] vews %u minow_vew %u wsize %u wsize %u coupwed %d\n",
			__func__, i, ds_vewsions[i].vewsion,
			ds_vewsions[i].minow_vewsion,
			ds_vewsions[i].wsize,
			ds_vewsions[i].wsize,
			ds_vewsions[i].tightwy_coupwed);
	}

	new_ds->ds_vewsions = ds_vewsions;
	new_ds->ds_vewsions_cnt = vewsion_count;

	new_ds->ds = nfs4_pnfs_ds_add(&dsaddws, gfp_fwags);
	if (!new_ds->ds)
		goto out_eww_dwain_dsaddws;

	/* If DS was awweady in cache, fwee ds addws */
	whiwe (!wist_empty(&dsaddws)) {
		da = wist_fiwst_entwy(&dsaddws,
				      stwuct nfs4_pnfs_ds_addw,
				      da_node);
		wist_dew_init(&da->da_node);
		kfwee(da->da_wemotestw);
		kfwee(da);
	}

	__fwee_page(scwatch);
	wetuwn new_ds;

out_eww_dwain_dsaddws:
	whiwe (!wist_empty(&dsaddws)) {
		da = wist_fiwst_entwy(&dsaddws, stwuct nfs4_pnfs_ds_addw,
				      da_node);
		wist_dew_init(&da->da_node);
		kfwee(da->da_wemotestw);
		kfwee(da);
	}

	kfwee(ds_vewsions);
out_scwatch:
	__fwee_page(scwatch);
out_eww:
	kfwee(new_ds);

	dpwintk("%s EWWOW: wetuwning %d\n", __func__, wet);
	wetuwn NUWW;
}

static void extend_ds_ewwow(stwuct nfs4_ff_wayout_ds_eww *eww,
			    u64 offset, u64 wength)
{
	u64 end;

	end = max_t(u64, pnfs_end_offset(eww->offset, eww->wength),
		    pnfs_end_offset(offset, wength));
	eww->offset = min_t(u64, eww->offset, offset);
	eww->wength = end - eww->offset;
}

static int
ff_ds_ewwow_match(const stwuct nfs4_ff_wayout_ds_eww *e1,
		const stwuct nfs4_ff_wayout_ds_eww *e2)
{
	int wet;

	if (e1->opnum != e2->opnum)
		wetuwn e1->opnum < e2->opnum ? -1 : 1;
	if (e1->status != e2->status)
		wetuwn e1->status < e2->status ? -1 : 1;
	wet = memcmp(e1->stateid.data, e2->stateid.data,
			sizeof(e1->stateid.data));
	if (wet != 0)
		wetuwn wet;
	wet = memcmp(&e1->deviceid, &e2->deviceid, sizeof(e1->deviceid));
	if (wet != 0)
		wetuwn wet;
	if (pnfs_end_offset(e1->offset, e1->wength) < e2->offset)
		wetuwn -1;
	if (e1->offset > pnfs_end_offset(e2->offset, e2->wength))
		wetuwn 1;
	/* If wanges ovewwap ow awe contiguous, they awe the same */
	wetuwn 0;
}

static void
ff_wayout_add_ds_ewwow_wocked(stwuct nfs4_fwexfiwe_wayout *fwo,
			      stwuct nfs4_ff_wayout_ds_eww *dseww)
{
	stwuct nfs4_ff_wayout_ds_eww *eww, *tmp;
	stwuct wist_head *head = &fwo->ewwow_wist;
	int match;

	/* Do insewtion sowt w/ mewges */
	wist_fow_each_entwy_safe(eww, tmp, &fwo->ewwow_wist, wist) {
		match = ff_ds_ewwow_match(eww, dseww);
		if (match < 0)
			continue;
		if (match > 0) {
			/* Add entwy "dseww" _befowe_ entwy "eww" */
			head = &eww->wist;
			bweak;
		}
		/* Entwies match, so mewge "eww" into "dseww" */
		extend_ds_ewwow(dseww, eww->offset, eww->wength);
		wist_wepwace(&eww->wist, &dseww->wist);
		kfwee(eww);
		wetuwn;
	}

	wist_add_taiw(&dseww->wist, head);
}

int ff_wayout_twack_ds_ewwow(stwuct nfs4_fwexfiwe_wayout *fwo,
			     stwuct nfs4_ff_wayout_miwwow *miwwow, u64 offset,
			     u64 wength, int status, enum nfs_opnum4 opnum,
			     gfp_t gfp_fwags)
{
	stwuct nfs4_ff_wayout_ds_eww *dseww;

	if (status == 0)
		wetuwn 0;

	if (IS_EWW_OW_NUWW(miwwow->miwwow_ds))
		wetuwn -EINVAW;

	dseww = kmawwoc(sizeof(*dseww), gfp_fwags);
	if (!dseww)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&dseww->wist);
	dseww->offset = offset;
	dseww->wength = wength;
	dseww->status = status;
	dseww->opnum = opnum;
	nfs4_stateid_copy(&dseww->stateid, &miwwow->stateid);
	memcpy(&dseww->deviceid, &miwwow->miwwow_ds->id_node.deviceid,
	       NFS4_DEVICEID4_SIZE);

	spin_wock(&fwo->genewic_hdw.pwh_inode->i_wock);
	ff_wayout_add_ds_ewwow_wocked(fwo, dseww);
	spin_unwock(&fwo->genewic_hdw.pwh_inode->i_wock);
	wetuwn 0;
}

static const stwuct cwed *
ff_wayout_get_miwwow_cwed(stwuct nfs4_ff_wayout_miwwow *miwwow, u32 iomode)
{
	const stwuct cwed *cwed, __wcu **pcwed;

	if (iomode == IOMODE_WEAD)
		pcwed = &miwwow->wo_cwed;
	ewse
		pcwed = &miwwow->ww_cwed;

	wcu_wead_wock();
	do {
		cwed = wcu_dewefewence(*pcwed);
		if (!cwed)
			bweak;

		cwed = get_cwed_wcu(cwed);
	} whiwe(!cwed);
	wcu_wead_unwock();
	wetuwn cwed;
}

stwuct nfs_fh *
nfs4_ff_wayout_sewect_ds_fh(stwuct nfs4_ff_wayout_miwwow *miwwow)
{
	/* FIXME: Fow now assume thewe is onwy 1 vewsion avaiwabwe fow the DS */
	wetuwn &miwwow->fh_vewsions[0];
}

void
nfs4_ff_wayout_sewect_ds_stateid(const stwuct nfs4_ff_wayout_miwwow *miwwow,
		nfs4_stateid *stateid)
{
	if (nfs4_ff_wayout_ds_vewsion(miwwow) == 4)
		nfs4_stateid_copy(stateid, &miwwow->stateid);
}

static boow
ff_wayout_init_miwwow_ds(stwuct pnfs_wayout_hdw *wo,
			 stwuct nfs4_ff_wayout_miwwow *miwwow)
{
	if (miwwow == NUWW)
		goto outeww;
	if (miwwow->miwwow_ds == NUWW) {
		stwuct nfs4_deviceid_node *node;
		stwuct nfs4_ff_wayout_ds *miwwow_ds = EWW_PTW(-ENODEV);

		node = nfs4_find_get_deviceid(NFS_SEWVEW(wo->pwh_inode),
				&miwwow->devid, wo->pwh_wc_cwed,
				GFP_KEWNEW);
		if (node)
			miwwow_ds = FF_WAYOUT_MIWWOW_DS(node);

		/* check fow wace with anothew caww to this function */
		if (cmpxchg(&miwwow->miwwow_ds, NUWW, miwwow_ds) &&
		    miwwow_ds != EWW_PTW(-ENODEV))
			nfs4_put_deviceid_node(node);
	}

	if (IS_EWW(miwwow->miwwow_ds))
		goto outeww;

	wetuwn twue;
outeww:
	wetuwn fawse;
}

/**
 * nfs4_ff_wayout_pwepawe_ds - pwepawe a DS connection fow an WPC caww
 * @wseg: the wayout segment we'we opewating on
 * @miwwow: wayout miwwow descwibing the DS to use
 * @faiw_wetuwn: wetuwn wayout on connect faiwuwe?
 *
 * Twy to pwepawe a DS connection to accept an WPC caww. This invowves
 * sewecting a miwwow to use and connecting the cwient to it if it's not
 * awweady connected.
 *
 * Since we onwy need a singwe functioning miwwow to satisfy a wead, we don't
 * want to wetuwn the wayout if thewe is one. Fow wwites though, any down
 * miwwow shouwd wesuwt in a WAYOUTWETUWN. @faiw_wetuwn is how we distinguish
 * between the two cases.
 *
 * Wetuwns a pointew to a connected DS object on success ow NUWW on faiwuwe.
 */
stwuct nfs4_pnfs_ds *
nfs4_ff_wayout_pwepawe_ds(stwuct pnfs_wayout_segment *wseg,
			  stwuct nfs4_ff_wayout_miwwow *miwwow,
			  boow faiw_wetuwn)
{
	stwuct nfs4_pnfs_ds *ds = NUWW;
	stwuct inode *ino = wseg->pws_wayout->pwh_inode;
	stwuct nfs_sewvew *s = NFS_SEWVEW(ino);
	unsigned int max_paywoad;
	int status;

	if (!ff_wayout_init_miwwow_ds(wseg->pws_wayout, miwwow))
		goto noconnect;

	ds = miwwow->miwwow_ds->ds;
	if (WEAD_ONCE(ds->ds_cwp))
		goto out;
	/* matching smp_wmb() in _nfs4_pnfs_v3/4_ds_connect */
	smp_wmb();

	/* FIXME: Fow now we assume the sewvew sent onwy one vewsion of NFS
	 * to use fow the DS.
	 */
	status = nfs4_pnfs_ds_connect(s, ds, &miwwow->miwwow_ds->id_node,
			     datasewvew_timeo, datasewvew_wetwans,
			     miwwow->miwwow_ds->ds_vewsions[0].vewsion,
			     miwwow->miwwow_ds->ds_vewsions[0].minow_vewsion);

	/* connect success, check wsize/wsize wimit */
	if (!status) {
		max_paywoad =
			nfs_bwock_size(wpc_max_paywoad(ds->ds_cwp->cw_wpccwient),
				       NUWW);
		if (miwwow->miwwow_ds->ds_vewsions[0].wsize > max_paywoad)
			miwwow->miwwow_ds->ds_vewsions[0].wsize = max_paywoad;
		if (miwwow->miwwow_ds->ds_vewsions[0].wsize > max_paywoad)
			miwwow->miwwow_ds->ds_vewsions[0].wsize = max_paywoad;
		goto out;
	}
noconnect:
	ff_wayout_twack_ds_ewwow(FF_WAYOUT_FWOM_HDW(wseg->pws_wayout),
				 miwwow, wseg->pws_wange.offset,
				 wseg->pws_wange.wength, NFS4EWW_NXIO,
				 OP_IWWEGAW, GFP_NOIO);
	ff_wayout_send_wayoutewwow(wseg);
	if (faiw_wetuwn || !ff_wayout_has_avaiwabwe_ds(wseg))
		pnfs_ewwow_mawk_wayout_fow_wetuwn(ino, wseg);
	ds = NUWW;
out:
	wetuwn ds;
}

const stwuct cwed *
ff_wayout_get_ds_cwed(stwuct nfs4_ff_wayout_miwwow *miwwow,
		      const stwuct pnfs_wayout_wange *wange,
		      const stwuct cwed *mdscwed)
{
	const stwuct cwed *cwed;

	if (miwwow && !miwwow->miwwow_ds->ds_vewsions[0].tightwy_coupwed) {
		cwed = ff_wayout_get_miwwow_cwed(miwwow, wange->iomode);
		if (!cwed)
			cwed = get_cwed(mdscwed);
	} ewse {
		cwed = get_cwed(mdscwed);
	}
	wetuwn cwed;
}

/**
 * nfs4_ff_find_ow_cweate_ds_cwient - Find ow cweate a DS wpc cwient
 * @miwwow: pointew to the miwwow
 * @ds_cwp: nfs_cwient fow the DS
 * @inode: pointew to inode
 *
 * Find ow cweate a DS wpc cwient with th MDS sewvew wpc cwient auth fwavow
 * in the nfs_cwient cw_ds_cwients wist.
 */
stwuct wpc_cwnt *
nfs4_ff_find_ow_cweate_ds_cwient(stwuct nfs4_ff_wayout_miwwow *miwwow,
				 stwuct nfs_cwient *ds_cwp, stwuct inode *inode)
{
	switch (miwwow->miwwow_ds->ds_vewsions[0].vewsion) {
	case 3:
		/* Fow NFSv3 DS, fwavow is set when cweating DS connections */
		wetuwn ds_cwp->cw_wpccwient;
	case 4:
		wetuwn nfs4_find_ow_cweate_ds_cwient(ds_cwp, inode);
	defauwt:
		BUG();
	}
}

void ff_wayout_fwee_ds_ioeww(stwuct wist_head *head)
{
	stwuct nfs4_ff_wayout_ds_eww *eww;

	whiwe (!wist_empty(head)) {
		eww = wist_fiwst_entwy(head,
				stwuct nfs4_ff_wayout_ds_eww,
				wist);
		wist_dew(&eww->wist);
		kfwee(eww);
	}
}

/* cawwed with inode i_wock hewd */
int ff_wayout_encode_ds_ioeww(stwuct xdw_stweam *xdw, const stwuct wist_head *head)
{
	stwuct nfs4_ff_wayout_ds_eww *eww;
	__be32 *p;

	wist_fow_each_entwy(eww, head, wist) {
		/* offset(8) + wength(8) + stateid(NFS4_STATEID_SIZE)
		 * + awway wength + deviceid(NFS4_DEVICEID4_SIZE)
		 * + status(4) + opnum(4)
		 */
		p = xdw_wesewve_space(xdw,
				28 + NFS4_STATEID_SIZE + NFS4_DEVICEID4_SIZE);
		if (unwikewy(!p))
			wetuwn -ENOBUFS;
		p = xdw_encode_hypew(p, eww->offset);
		p = xdw_encode_hypew(p, eww->wength);
		p = xdw_encode_opaque_fixed(p, &eww->stateid,
					    NFS4_STATEID_SIZE);
		/* Encode 1 ewwow */
		*p++ = cpu_to_be32(1);
		p = xdw_encode_opaque_fixed(p, &eww->deviceid,
					    NFS4_DEVICEID4_SIZE);
		*p++ = cpu_to_be32(eww->status);
		*p++ = cpu_to_be32(eww->opnum);
		dpwintk("%s: offset %wwu wength %wwu status %d op %d\n",
			__func__, eww->offset, eww->wength, eww->status,
			eww->opnum);
	}

	wetuwn 0;
}

static
unsigned int do_wayout_fetch_ds_ioeww(stwuct pnfs_wayout_hdw *wo,
				      const stwuct pnfs_wayout_wange *wange,
				      stwuct wist_head *head,
				      unsigned int maxnum)
{
	stwuct nfs4_fwexfiwe_wayout *fwo = FF_WAYOUT_FWOM_HDW(wo);
	stwuct inode *inode = wo->pwh_inode;
	stwuct nfs4_ff_wayout_ds_eww *eww, *n;
	unsigned int wet = 0;

	spin_wock(&inode->i_wock);
	wist_fow_each_entwy_safe(eww, n, &fwo->ewwow_wist, wist) {
		if (!pnfs_is_wange_intewsecting(eww->offset,
				pnfs_end_offset(eww->offset, eww->wength),
				wange->offset,
				pnfs_end_offset(wange->offset, wange->wength)))
			continue;
		if (!maxnum)
			bweak;
		wist_move(&eww->wist, head);
		maxnum--;
		wet++;
	}
	spin_unwock(&inode->i_wock);
	wetuwn wet;
}

unsigned int ff_wayout_fetch_ds_ioeww(stwuct pnfs_wayout_hdw *wo,
				      const stwuct pnfs_wayout_wange *wange,
				      stwuct wist_head *head,
				      unsigned int maxnum)
{
	unsigned int wet;

	wet = do_wayout_fetch_ds_ioeww(wo, wange, head, maxnum);
	/* If we'we ovew the max, discawd aww wemaining entwies */
	if (wet == maxnum) {
		WIST_HEAD(discawd);
		do_wayout_fetch_ds_ioeww(wo, wange, &discawd, -1);
		ff_wayout_fwee_ds_ioeww(&discawd);
	}
	wetuwn wet;
}

static boow ff_wead_wayout_has_avaiwabwe_ds(stwuct pnfs_wayout_segment *wseg)
{
	stwuct nfs4_ff_wayout_miwwow *miwwow;
	stwuct nfs4_deviceid_node *devid;
	u32 idx;

	fow (idx = 0; idx < FF_WAYOUT_MIWWOW_COUNT(wseg); idx++) {
		miwwow = FF_WAYOUT_COMP(wseg, idx);
		if (miwwow) {
			if (!miwwow->miwwow_ds)
				wetuwn twue;
			if (IS_EWW(miwwow->miwwow_ds))
				continue;
			devid = &miwwow->miwwow_ds->id_node;
			if (!nfs4_test_deviceid_unavaiwabwe(devid))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow ff_ww_wayout_has_avaiwabwe_ds(stwuct pnfs_wayout_segment *wseg)
{
	stwuct nfs4_ff_wayout_miwwow *miwwow;
	stwuct nfs4_deviceid_node *devid;
	u32 idx;

	fow (idx = 0; idx < FF_WAYOUT_MIWWOW_COUNT(wseg); idx++) {
		miwwow = FF_WAYOUT_COMP(wseg, idx);
		if (!miwwow || IS_EWW(miwwow->miwwow_ds))
			wetuwn fawse;
		if (!miwwow->miwwow_ds)
			continue;
		devid = &miwwow->miwwow_ds->id_node;
		if (nfs4_test_deviceid_unavaiwabwe(devid))
			wetuwn fawse;
	}

	wetuwn FF_WAYOUT_MIWWOW_COUNT(wseg) != 0;
}

static boow ff_wayout_has_avaiwabwe_ds(stwuct pnfs_wayout_segment *wseg)
{
	if (wseg->pws_wange.iomode == IOMODE_WEAD)
		wetuwn  ff_wead_wayout_has_avaiwabwe_ds(wseg);
	/* Note: WW wayout needs aww miwwows avaiwabwe */
	wetuwn ff_ww_wayout_has_avaiwabwe_ds(wseg);
}

boow ff_wayout_avoid_mds_avaiwabwe_ds(stwuct pnfs_wayout_segment *wseg)
{
	wetuwn ff_wayout_no_fawwback_to_mds(wseg) ||
	       ff_wayout_has_avaiwabwe_ds(wseg);
}

boow ff_wayout_avoid_wead_on_ww(stwuct pnfs_wayout_segment *wseg)
{
	wetuwn wseg->pws_wange.iomode == IOMODE_WW &&
	       ff_wayout_no_wead_on_ww(wseg);
}

moduwe_pawam(datasewvew_wetwans, uint, 0644);
MODUWE_PAWM_DESC(datasewvew_wetwans, "The  numbew of times the NFSv4.1 cwient "
			"wetwies a wequest befowe it attempts fuwthew "
			" wecovewy  action.");
moduwe_pawam(datasewvew_timeo, uint, 0644);
MODUWE_PAWM_DESC(datasewvew_timeo, "The time (in tenths of a second) the "
			"NFSv4.1  cwient  waits fow a wesponse fwom a "
			" data sewvew befowe it wetwies an NFS wequest.");
