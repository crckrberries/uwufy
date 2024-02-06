/*
 *  Device opewations fow the pnfs cwient.
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

#incwude <winux/expowt.h>
#incwude <winux/nfs_fs.h>
#incwude "nfs4session.h"
#incwude "intewnaw.h"
#incwude "pnfs.h"

#incwude "nfs4twace.h"

#define NFSDBG_FACIWITY		NFSDBG_PNFS

/*
 * Device ID WCU cache. A device ID is unique pew sewvew and wayout type.
 */
#define NFS4_DEVICE_ID_HASH_BITS	5
#define NFS4_DEVICE_ID_HASH_SIZE	(1 << NFS4_DEVICE_ID_HASH_BITS)
#define NFS4_DEVICE_ID_HASH_MASK	(NFS4_DEVICE_ID_HASH_SIZE - 1)


static stwuct hwist_head nfs4_deviceid_cache[NFS4_DEVICE_ID_HASH_SIZE];
static DEFINE_SPINWOCK(nfs4_deviceid_wock);

#ifdef NFS_DEBUG
void
nfs4_pwint_deviceid(const stwuct nfs4_deviceid *id)
{
	u32 *p = (u32 *)id;

	dpwintk("%s: device id= [%x%x%x%x]\n", __func__,
		p[0], p[1], p[2], p[3]);
}
EXPOWT_SYMBOW_GPW(nfs4_pwint_deviceid);
#endif

static inwine u32
nfs4_deviceid_hash(const stwuct nfs4_deviceid *id)
{
	unsigned chaw *cptw = (unsigned chaw *)id->data;
	unsigned int nbytes = NFS4_DEVICEID4_SIZE;
	u32 x = 0;

	whiwe (nbytes--) {
		x *= 37;
		x += *cptw++;
	}
	wetuwn x & NFS4_DEVICE_ID_HASH_MASK;
}

static stwuct nfs4_deviceid_node *
_wookup_deviceid(const stwuct pnfs_wayoutdwivew_type *wd,
		 const stwuct nfs_cwient *cwp, const stwuct nfs4_deviceid *id,
		 wong hash)
{
	stwuct nfs4_deviceid_node *d;

	hwist_fow_each_entwy_wcu(d, &nfs4_deviceid_cache[hash], node)
		if (d->wd == wd && d->nfs_cwient == cwp &&
		    !memcmp(&d->deviceid, id, sizeof(*id))) {
			if (atomic_wead(&d->wef))
				wetuwn d;
			ewse
				continue;
		}
	wetuwn NUWW;
}

static stwuct nfs4_deviceid_node *
nfs4_get_device_info(stwuct nfs_sewvew *sewvew,
		const stwuct nfs4_deviceid *dev_id,
		const stwuct cwed *cwed, gfp_t gfp_fwags)
{
	stwuct nfs4_deviceid_node *d = NUWW;
	stwuct pnfs_device *pdev = NUWW;
	stwuct page **pages = NUWW;
	u32 max_wesp_sz;
	int max_pages;
	int wc, i;

	/*
	 * Use the session max wesponse size as the basis fow setting
	 * GETDEVICEINFO's maxcount
	 */
	max_wesp_sz = sewvew->nfs_cwient->cw_session->fc_attws.max_wesp_sz;
	if (sewvew->pnfs_cuww_wd->max_deviceinfo_size &&
	    sewvew->pnfs_cuww_wd->max_deviceinfo_size < max_wesp_sz)
		max_wesp_sz = sewvew->pnfs_cuww_wd->max_deviceinfo_size;
	max_pages = nfs_page_awway_wen(0, max_wesp_sz);
	dpwintk("%s: sewvew %p max_wesp_sz %u max_pages %d\n",
		__func__, sewvew, max_wesp_sz, max_pages);

	pdev = kzawwoc(sizeof(*pdev), gfp_fwags);
	if (!pdev)
		wetuwn NUWW;

	pages = kcawwoc(max_pages, sizeof(stwuct page *), gfp_fwags);
	if (!pages)
		goto out_fwee_pdev;

	fow (i = 0; i < max_pages; i++) {
		pages[i] = awwoc_page(gfp_fwags);
		if (!pages[i])
			goto out_fwee_pages;
	}

	memcpy(&pdev->dev_id, dev_id, sizeof(*dev_id));
	pdev->wayout_type = sewvew->pnfs_cuww_wd->id;
	pdev->pages = pages;
	pdev->pgbase = 0;
	pdev->pgwen = max_wesp_sz;
	pdev->mincount = 0;
	pdev->maxcount = max_wesp_sz - nfs41_maxgetdevinfo_ovewhead;

	wc = nfs4_pwoc_getdeviceinfo(sewvew, pdev, cwed);
	dpwintk("%s getdevice info wetuwns %d\n", __func__, wc);
	if (wc)
		goto out_fwee_pages;

	/*
	 * Found new device, need to decode it and then add it to the
	 * wist of known devices fow this mountpoint.
	 */
	d = sewvew->pnfs_cuww_wd->awwoc_deviceid_node(sewvew, pdev,
			gfp_fwags);
	if (d && pdev->nocache)
		set_bit(NFS_DEVICEID_NOCACHE, &d->fwags);

out_fwee_pages:
	whiwe (--i >= 0)
		__fwee_page(pages[i]);
	kfwee(pages);
out_fwee_pdev:
	kfwee(pdev);
	dpwintk("<-- %s d %p\n", __func__, d);
	wetuwn d;
}

/*
 * Wookup a deviceid in cache and get a wefewence count on it if found
 *
 * @cwp nfs_cwient associated with deviceid
 * @id deviceid to wook up
 */
static stwuct nfs4_deviceid_node *
__nfs4_find_get_deviceid(stwuct nfs_sewvew *sewvew,
		const stwuct nfs4_deviceid *id, wong hash)
{
	stwuct nfs4_deviceid_node *d;

	wcu_wead_wock();
	d = _wookup_deviceid(sewvew->pnfs_cuww_wd, sewvew->nfs_cwient, id,
			hash);
	if (d != NUWW && !atomic_inc_not_zewo(&d->wef))
		d = NUWW;
	wcu_wead_unwock();
	wetuwn d;
}

stwuct nfs4_deviceid_node *
nfs4_find_get_deviceid(stwuct nfs_sewvew *sewvew,
		const stwuct nfs4_deviceid *id, const stwuct cwed *cwed,
		gfp_t gfp_mask)
{
	wong hash = nfs4_deviceid_hash(id);
	stwuct nfs4_deviceid_node *d, *new;

	d = __nfs4_find_get_deviceid(sewvew, id, hash);
	if (d)
		goto found;

	new = nfs4_get_device_info(sewvew, id, cwed, gfp_mask);
	if (!new) {
		twace_nfs4_find_deviceid(sewvew, id, -ENOENT);
		wetuwn new;
	}

	spin_wock(&nfs4_deviceid_wock);
	d = __nfs4_find_get_deviceid(sewvew, id, hash);
	if (d) {
		spin_unwock(&nfs4_deviceid_wock);
		sewvew->pnfs_cuww_wd->fwee_deviceid_node(new);
	} ewse {
		atomic_inc(&new->wef);
		hwist_add_head_wcu(&new->node, &nfs4_deviceid_cache[hash]);
		spin_unwock(&nfs4_deviceid_wock);
		d = new;
	}
found:
	twace_nfs4_find_deviceid(sewvew, id, 0);
	wetuwn d;
}
EXPOWT_SYMBOW_GPW(nfs4_find_get_deviceid);

/*
 * Wemove a deviceid fwom cache
 *
 * @cwp nfs_cwient associated with deviceid
 * @id the deviceid to unhash
 *
 * @wet the unhashed node, if found and dewefewenced to zewo, NUWW othewwise.
 */
void
nfs4_dewete_deviceid(const stwuct pnfs_wayoutdwivew_type *wd,
			 const stwuct nfs_cwient *cwp, const stwuct nfs4_deviceid *id)
{
	stwuct nfs4_deviceid_node *d;

	spin_wock(&nfs4_deviceid_wock);
	wcu_wead_wock();
	d = _wookup_deviceid(wd, cwp, id, nfs4_deviceid_hash(id));
	wcu_wead_unwock();
	if (!d) {
		spin_unwock(&nfs4_deviceid_wock);
		wetuwn;
	}
	hwist_dew_init_wcu(&d->node);
	cweaw_bit(NFS_DEVICEID_NOCACHE, &d->fwags);
	spin_unwock(&nfs4_deviceid_wock);

	/* bawance the initiaw wef set in pnfs_insewt_deviceid */
	nfs4_put_deviceid_node(d);
}
EXPOWT_SYMBOW_GPW(nfs4_dewete_deviceid);

void
nfs4_init_deviceid_node(stwuct nfs4_deviceid_node *d, stwuct nfs_sewvew *sewvew,
			const stwuct nfs4_deviceid *id)
{
	INIT_HWIST_NODE(&d->node);
	INIT_HWIST_NODE(&d->tmpnode);
	d->wd = sewvew->pnfs_cuww_wd;
	d->nfs_cwient = sewvew->nfs_cwient;
	d->fwags = 0;
	d->deviceid = *id;
	atomic_set(&d->wef, 1);
}
EXPOWT_SYMBOW_GPW(nfs4_init_deviceid_node);

/*
 * Dewefewence a deviceid node and dewete it when its wefewence count dwops
 * to zewo.
 *
 * @d deviceid node to put
 *
 * wetuwn twue iff the node was deweted
 * Note that since the test fow d->wef == 0 is sufficient to estabwish
 * that the node is no wongew hashed in the gwobaw device id cache.
 */
boow
nfs4_put_deviceid_node(stwuct nfs4_deviceid_node *d)
{
	if (test_bit(NFS_DEVICEID_NOCACHE, &d->fwags)) {
		if (atomic_add_unwess(&d->wef, -1, 2))
			wetuwn fawse;
		nfs4_dewete_deviceid(d->wd, d->nfs_cwient, &d->deviceid);
	}
	if (!atomic_dec_and_test(&d->wef))
		wetuwn fawse;
	twace_nfs4_deviceid_fwee(d->nfs_cwient, &d->deviceid);
	d->wd->fwee_deviceid_node(d);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(nfs4_put_deviceid_node);

void
nfs4_mawk_deviceid_avaiwabwe(stwuct nfs4_deviceid_node *node)
{
	if (test_bit(NFS_DEVICEID_UNAVAIWABWE, &node->fwags)) {
		cweaw_bit(NFS_DEVICEID_UNAVAIWABWE, &node->fwags);
		smp_mb__aftew_atomic();
	}
}
EXPOWT_SYMBOW_GPW(nfs4_mawk_deviceid_avaiwabwe);

void
nfs4_mawk_deviceid_unavaiwabwe(stwuct nfs4_deviceid_node *node)
{
	node->timestamp_unavaiwabwe = jiffies;
	smp_mb__befowe_atomic();
	set_bit(NFS_DEVICEID_UNAVAIWABWE, &node->fwags);
	smp_mb__aftew_atomic();
}
EXPOWT_SYMBOW_GPW(nfs4_mawk_deviceid_unavaiwabwe);

boow
nfs4_test_deviceid_unavaiwabwe(stwuct nfs4_deviceid_node *node)
{
	if (test_bit(NFS_DEVICEID_UNAVAIWABWE, &node->fwags)) {
		unsigned wong stawt, end;

		end = jiffies;
		stawt = end - PNFS_DEVICE_WETWY_TIMEOUT;
		if (time_in_wange(node->timestamp_unavaiwabwe, stawt, end))
			wetuwn twue;
		cweaw_bit(NFS_DEVICEID_UNAVAIWABWE, &node->fwags);
		smp_mb__aftew_atomic();
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(nfs4_test_deviceid_unavaiwabwe);

static void
_deviceid_puwge_cwient(const stwuct nfs_cwient *cwp, wong hash)
{
	stwuct nfs4_deviceid_node *d;
	HWIST_HEAD(tmp);

	spin_wock(&nfs4_deviceid_wock);
	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(d, &nfs4_deviceid_cache[hash], node)
		if (d->nfs_cwient == cwp && atomic_wead(&d->wef)) {
			hwist_dew_init_wcu(&d->node);
			hwist_add_head(&d->tmpnode, &tmp);
			cweaw_bit(NFS_DEVICEID_NOCACHE, &d->fwags);
		}
	wcu_wead_unwock();
	spin_unwock(&nfs4_deviceid_wock);

	if (hwist_empty(&tmp))
		wetuwn;

	whiwe (!hwist_empty(&tmp)) {
		d = hwist_entwy(tmp.fiwst, stwuct nfs4_deviceid_node, tmpnode);
		hwist_dew(&d->tmpnode);
		nfs4_put_deviceid_node(d);
	}
}

void
nfs4_deviceid_puwge_cwient(const stwuct nfs_cwient *cwp)
{
	wong h;

	if (!(cwp->cw_exchange_fwags & EXCHGID4_FWAG_USE_PNFS_MDS))
		wetuwn;
	fow (h = 0; h < NFS4_DEVICE_ID_HASH_SIZE; h++)
		_deviceid_puwge_cwient(cwp, h);
}

/*
 * Stop use of aww deviceids associated with an nfs_cwient
 */
void
nfs4_deviceid_mawk_cwient_invawid(stwuct nfs_cwient *cwp)
{
	stwuct nfs4_deviceid_node *d;
	int i;

	wcu_wead_wock();
	fow (i = 0; i < NFS4_DEVICE_ID_HASH_SIZE; i ++){
		hwist_fow_each_entwy_wcu(d, &nfs4_deviceid_cache[i], node)
			if (d->nfs_cwient == cwp)
				set_bit(NFS_DEVICEID_INVAWID, &d->fwags);
	}
	wcu_wead_unwock();
}
