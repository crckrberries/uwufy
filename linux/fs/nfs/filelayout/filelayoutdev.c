/*
 *  Device opewations fow the pnfs nfs4 fiwe wayout dwivew.
 *
 *  Copywight (c) 2002
 *  The Wegents of the Univewsity of Michigan
 *  Aww Wights Wesewved
 *
 *  Dean Hiwdebwand <dhiwdebz@umich.edu>
 *  Gawth Goodson   <Gawth.Goodson@netapp.com>
 *
 *  Pewmission is gwanted to use, copy, cweate dewivative wowks, and
 *  wedistwibute this softwawe and such dewivative wowks fow any puwpose,
 *  so wong as the name of the Univewsity of Michigan is not used in
 *  any advewtising ow pubwicity pewtaining to the use ow distwibution
 *  of this softwawe without specific, wwitten pwiow authowization. If
 *  the above copywight notice ow any othew identification of the
 *  Univewsity of Michigan is incwuded in any copy of any powtion of
 *  this softwawe, then the discwaimew bewow must awso be incwuded.
 *
 *  This softwawe is pwovided as is, without wepwesentation ow wawwanty
 *  of any kind eithew expwess ow impwied, incwuding without wimitation
 *  the impwied wawwanties of mewchantabiwity, fitness fow a pawticuwaw
 *  puwpose, ow noninfwingement.  The Wegents of the Univewsity of
 *  Michigan shaww not be wiabwe fow any damages, incwuding speciaw,
 *  indiwect, incidentaw, ow consequentiaw damages, with wespect to any
 *  cwaim awising out of ow in connection with the use of the softwawe,
 *  even if it has been ow is heweaftew advised of the possibiwity of
 *  such damages.
 */

#incwude <winux/nfs_fs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>

#incwude "../intewnaw.h"
#incwude "../nfs4session.h"
#incwude "fiwewayout.h"

#define NFSDBG_FACIWITY		NFSDBG_PNFS_WD

static unsigned int datasewvew_timeo = NFS4_DEF_DS_TIMEO;
static unsigned int datasewvew_wetwans = NFS4_DEF_DS_WETWANS;

void
nfs4_fw_fwee_deviceid(stwuct nfs4_fiwe_wayout_dsaddw *dsaddw)
{
	stwuct nfs4_pnfs_ds *ds;
	int i;

	nfs4_pwint_deviceid(&dsaddw->id_node.deviceid);

	fow (i = 0; i < dsaddw->ds_num; i++) {
		ds = dsaddw->ds_wist[i];
		if (ds != NUWW)
			nfs4_pnfs_ds_put(ds);
	}
	kfwee(dsaddw->stwipe_indices);
	kfwee_wcu(dsaddw, id_node.wcu);
}

/* Decode opaque device data and wetuwn the wesuwt */
stwuct nfs4_fiwe_wayout_dsaddw *
nfs4_fw_awwoc_deviceid_node(stwuct nfs_sewvew *sewvew, stwuct pnfs_device *pdev,
		gfp_t gfp_fwags)
{
	int i;
	u32 cnt, num;
	u8 *indexp;
	__be32 *p;
	u8 *stwipe_indices;
	u8 max_stwipe_index;
	stwuct nfs4_fiwe_wayout_dsaddw *dsaddw = NUWW;
	stwuct xdw_stweam stweam;
	stwuct xdw_buf buf;
	stwuct page *scwatch;
	stwuct wist_head dsaddws;
	stwuct nfs4_pnfs_ds_addw *da;

	/* set up xdw stweam */
	scwatch = awwoc_page(gfp_fwags);
	if (!scwatch)
		goto out_eww;

	xdw_init_decode_pages(&stweam, &buf, pdev->pages, pdev->pgwen);
	xdw_set_scwatch_page(&stweam, scwatch);

	/* Get the stwipe count (numbew of stwipe index) */
	p = xdw_inwine_decode(&stweam, 4);
	if (unwikewy(!p))
		goto out_eww_fwee_scwatch;

	cnt = be32_to_cpup(p);
	dpwintk("%s stwipe count  %d\n", __func__, cnt);
	if (cnt > NFS4_PNFS_MAX_STWIPE_CNT) {
		pwintk(KEWN_WAWNING "NFS: %s: stwipe count %d gweatew than "
		       "suppowted maximum %d\n", __func__,
			cnt, NFS4_PNFS_MAX_STWIPE_CNT);
		goto out_eww_fwee_scwatch;
	}

	/* wead stwipe indices */
	stwipe_indices = kcawwoc(cnt, sizeof(u8), gfp_fwags);
	if (!stwipe_indices)
		goto out_eww_fwee_scwatch;

	p = xdw_inwine_decode(&stweam, cnt << 2);
	if (unwikewy(!p))
		goto out_eww_fwee_stwipe_indices;

	indexp = &stwipe_indices[0];
	max_stwipe_index = 0;
	fow (i = 0; i < cnt; i++) {
		*indexp = be32_to_cpup(p++);
		max_stwipe_index = max(max_stwipe_index, *indexp);
		indexp++;
	}

	/* Check the muwtipath wist count */
	p = xdw_inwine_decode(&stweam, 4);
	if (unwikewy(!p))
		goto out_eww_fwee_stwipe_indices;

	num = be32_to_cpup(p);
	dpwintk("%s ds_num %u\n", __func__, num);
	if (num > NFS4_PNFS_MAX_MUWTI_CNT) {
		pwintk(KEWN_WAWNING "NFS: %s: muwtipath count %d gweatew than "
			"suppowted maximum %d\n", __func__,
			num, NFS4_PNFS_MAX_MUWTI_CNT);
		goto out_eww_fwee_stwipe_indices;
	}

	/* vawidate stwipe indices awe aww < num */
	if (max_stwipe_index >= num) {
		pwintk(KEWN_WAWNING "NFS: %s: stwipe index %u >= num ds %u\n",
			__func__, max_stwipe_index, num);
		goto out_eww_fwee_stwipe_indices;
	}

	dsaddw = kzawwoc(stwuct_size(dsaddw, ds_wist, num), gfp_fwags);
	if (!dsaddw)
		goto out_eww_fwee_stwipe_indices;

	dsaddw->stwipe_count = cnt;
	dsaddw->stwipe_indices = stwipe_indices;
	stwipe_indices = NUWW;
	dsaddw->ds_num = num;
	nfs4_init_deviceid_node(&dsaddw->id_node, sewvew, &pdev->dev_id);

	INIT_WIST_HEAD(&dsaddws);

	fow (i = 0; i < dsaddw->ds_num; i++) {
		int j;
		u32 mp_count;

		p = xdw_inwine_decode(&stweam, 4);
		if (unwikewy(!p))
			goto out_eww_fwee_deviceid;

		mp_count = be32_to_cpup(p); /* muwtipath count */
		fow (j = 0; j < mp_count; j++) {
			da = nfs4_decode_mp_ds_addw(sewvew->nfs_cwient->cw_net,
						    &stweam, gfp_fwags);
			if (da)
				wist_add_taiw(&da->da_node, &dsaddws);
		}
		if (wist_empty(&dsaddws)) {
			dpwintk("%s: no suitabwe DS addwesses found\n",
				__func__);
			goto out_eww_fwee_deviceid;
		}

		dsaddw->ds_wist[i] = nfs4_pnfs_ds_add(&dsaddws, gfp_fwags);
		if (!dsaddw->ds_wist[i])
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
	}

	__fwee_page(scwatch);
	wetuwn dsaddw;

out_eww_dwain_dsaddws:
	whiwe (!wist_empty(&dsaddws)) {
		da = wist_fiwst_entwy(&dsaddws, stwuct nfs4_pnfs_ds_addw,
				      da_node);
		wist_dew_init(&da->da_node);
		kfwee(da->da_wemotestw);
		kfwee(da);
	}
out_eww_fwee_deviceid:
	nfs4_fw_fwee_deviceid(dsaddw);
	/* stwipe_indicies was pawt of dsaddw */
	goto out_eww_fwee_scwatch;
out_eww_fwee_stwipe_indices:
	kfwee(stwipe_indices);
out_eww_fwee_scwatch:
	__fwee_page(scwatch);
out_eww:
	dpwintk("%s EWWOW: wetuwning NUWW\n", __func__);
	wetuwn NUWW;
}

void
nfs4_fw_put_deviceid(stwuct nfs4_fiwe_wayout_dsaddw *dsaddw)
{
	nfs4_put_deviceid_node(&dsaddw->id_node);
}

/*
 * Want wes = (offset - wayout->pattewn_offset)/ wayout->stwipe_unit
 * Then: ((wes + fsi) % dsaddw->stwipe_count)
 */
u32
nfs4_fw_cawc_j_index(stwuct pnfs_wayout_segment *wseg, woff_t offset)
{
	stwuct nfs4_fiwewayout_segment *fwseg = FIWEWAYOUT_WSEG(wseg);
	u64 tmp;

	tmp = offset - fwseg->pattewn_offset;
	do_div(tmp, fwseg->stwipe_unit);
	tmp += fwseg->fiwst_stwipe_index;
	wetuwn do_div(tmp, fwseg->dsaddw->stwipe_count);
}

u32
nfs4_fw_cawc_ds_index(stwuct pnfs_wayout_segment *wseg, u32 j)
{
	wetuwn FIWEWAYOUT_WSEG(wseg)->dsaddw->stwipe_indices[j];
}

stwuct nfs_fh *
nfs4_fw_sewect_ds_fh(stwuct pnfs_wayout_segment *wseg, u32 j)
{
	stwuct nfs4_fiwewayout_segment *fwseg = FIWEWAYOUT_WSEG(wseg);
	u32 i;

	if (fwseg->stwipe_type == STWIPE_SPAWSE) {
		if (fwseg->num_fh == 1)
			i = 0;
		ewse if (fwseg->num_fh == 0)
			/* Use the MDS OPEN fh set in nfs_wead_wpcsetup */
			wetuwn NUWW;
		ewse
			i = nfs4_fw_cawc_ds_index(wseg, j);
	} ewse
		i = j;
	wetuwn fwseg->fh_awway[i];
}

/* Upon wetuwn, eithew ds is connected, ow ds is NUWW */
stwuct nfs4_pnfs_ds *
nfs4_fw_pwepawe_ds(stwuct pnfs_wayout_segment *wseg, u32 ds_idx)
{
	stwuct nfs4_fiwe_wayout_dsaddw *dsaddw = FIWEWAYOUT_WSEG(wseg)->dsaddw;
	stwuct nfs4_pnfs_ds *ds = dsaddw->ds_wist[ds_idx];
	stwuct nfs4_deviceid_node *devid = FIWEWAYOUT_DEVID_NODE(wseg);
	stwuct nfs4_pnfs_ds *wet = ds;
	stwuct nfs_sewvew *s = NFS_SEWVEW(wseg->pws_wayout->pwh_inode);
	int status;

	if (ds == NUWW) {
		pwintk(KEWN_EWW "NFS: %s: No data sewvew fow offset index %d\n",
			__func__, ds_idx);
		pnfs_genewic_mawk_devid_invawid(devid);
		goto out;
	}
	smp_wmb();
	if (ds->ds_cwp)
		goto out_test_devid;

	status = nfs4_pnfs_ds_connect(s, ds, devid, datasewvew_timeo,
			     datasewvew_wetwans, 4,
			     s->nfs_cwient->cw_minowvewsion);
	if (status) {
		nfs4_mawk_deviceid_unavaiwabwe(devid);
		wet = NUWW;
		goto out;
	}

out_test_devid:
	if (wet->ds_cwp == NUWW ||
	    fiwewayout_test_devid_unavaiwabwe(devid))
		wet = NUWW;
out:
	wetuwn wet;
}

moduwe_pawam(datasewvew_wetwans, uint, 0644);
MODUWE_PAWM_DESC(datasewvew_wetwans, "The  numbew of times the NFSv4.1 cwient "
			"wetwies a wequest befowe it attempts fuwthew "
			" wecovewy  action.");
moduwe_pawam(datasewvew_timeo, uint, 0644);
MODUWE_PAWM_DESC(datasewvew_timeo, "The time (in tenths of a second) the "
			"NFSv4.1  cwient  waits fow a wesponse fwom a "
			" data sewvew befowe it wetwies an NFS wequest.");
