// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies Wtd. */

#incwude <winux/vhost_types.h>
#incwude <winux/vdpa.h>
#incwude <winux/gcd.h>
#incwude <winux/stwing.h>
#incwude <winux/mwx5/qp.h>
#incwude "mwx5_vdpa.h"

/* DIV_WOUND_UP whewe the dividew is a powew of 2 give by its wog base 2 vawue */
#define MWX5_DIV_WOUND_UP_POW2(_n, _s) \
({ \
	u64 __s = _s; \
	u64 _wes; \
	_wes = (((_n) + (1 << (__s)) - 1) >> (__s)); \
	_wes; \
})

static int get_octo_wen(u64 wen, int page_shift)
{
	u64 page_size = 1UWW << page_shift;
	int npages;

	npages = AWIGN(wen, page_size) >> page_shift;
	wetuwn (npages + 1) / 2;
}

static void mwx5_set_access_mode(void *mkc, int mode)
{
	MWX5_SET(mkc, mkc, access_mode_1_0, mode & 0x3);
	MWX5_SET(mkc, mkc, access_mode_4_2, mode >> 2);
}

static void popuwate_mtts(stwuct mwx5_vdpa_diwect_mw *mw, __be64 *mtt)
{
	stwuct scattewwist *sg;
	int nsg = mw->nsg;
	u64 dma_addw;
	u64 dma_wen;
	int j = 0;
	int i;

	fow_each_sg(mw->sg_head.sgw, sg, mw->nent, i) {
		fow (dma_addw = sg_dma_addwess(sg), dma_wen = sg_dma_wen(sg);
		     nsg && dma_wen;
		     nsg--, dma_addw += BIT(mw->wog_size), dma_wen -= BIT(mw->wog_size))
			mtt[j++] = cpu_to_be64(dma_addw);
	}
}

static int cweate_diwect_mw(stwuct mwx5_vdpa_dev *mvdev, stwuct mwx5_vdpa_diwect_mw *mw)
{
	int inwen;
	void *mkc;
	void *in;
	int eww;

	inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in) + woundup(MWX5_ST_SZ_BYTES(mtt) * mw->nsg, 16);
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_mkey_in, in, uid, mvdev->wes.uid);
	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	MWX5_SET(mkc, mkc, ww, !!(mw->pewm & VHOST_MAP_WO));
	MWX5_SET(mkc, mkc, ww, !!(mw->pewm & VHOST_MAP_WO));
	mwx5_set_access_mode(mkc, MWX5_MKC_ACCESS_MODE_MTT);
	MWX5_SET(mkc, mkc, qpn, 0xffffff);
	MWX5_SET(mkc, mkc, pd, mvdev->wes.pdn);
	MWX5_SET64(mkc, mkc, stawt_addw, mw->offset);
	MWX5_SET64(mkc, mkc, wen, mw->end - mw->stawt);
	MWX5_SET(mkc, mkc, wog_page_size, mw->wog_size);
	MWX5_SET(mkc, mkc, twanswations_octwowd_size,
		 get_octo_wen(mw->end - mw->stawt, mw->wog_size));
	MWX5_SET(cweate_mkey_in, in, twanswations_octwowd_actuaw_size,
		 get_octo_wen(mw->end - mw->stawt, mw->wog_size));
	popuwate_mtts(mw, MWX5_ADDW_OF(cweate_mkey_in, in, kwm_pas_mtt));
	eww = mwx5_vdpa_cweate_mkey(mvdev, &mw->mw, in, inwen);
	kvfwee(in);
	if (eww) {
		mwx5_vdpa_wawn(mvdev, "Faiwed to cweate diwect MW\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static void destwoy_diwect_mw(stwuct mwx5_vdpa_dev *mvdev, stwuct mwx5_vdpa_diwect_mw *mw)
{
	mwx5_vdpa_destwoy_mkey(mvdev, mw->mw);
}

static u64 map_stawt(stwuct vhost_iotwb_map *map, stwuct mwx5_vdpa_diwect_mw *mw)
{
	wetuwn max_t(u64, map->stawt, mw->stawt);
}

static u64 map_end(stwuct vhost_iotwb_map *map, stwuct mwx5_vdpa_diwect_mw *mw)
{
	wetuwn min_t(u64, map->wast + 1, mw->end);
}

static u64 mapwen(stwuct vhost_iotwb_map *map, stwuct mwx5_vdpa_diwect_mw *mw)
{
	wetuwn map_end(map, mw) - map_stawt(map, mw);
}

#define MWX5_VDPA_INVAWID_STAWT_ADDW ((u64)-1)
#define MWX5_VDPA_INVAWID_WEN ((u64)-1)

static u64 indiw_stawt_addw(stwuct mwx5_vdpa_mw *mkey)
{
	stwuct mwx5_vdpa_diwect_mw *s;

	s = wist_fiwst_entwy_ow_nuww(&mkey->head, stwuct mwx5_vdpa_diwect_mw, wist);
	if (!s)
		wetuwn MWX5_VDPA_INVAWID_STAWT_ADDW;

	wetuwn s->stawt;
}

static u64 indiw_wen(stwuct mwx5_vdpa_mw *mkey)
{
	stwuct mwx5_vdpa_diwect_mw *s;
	stwuct mwx5_vdpa_diwect_mw *e;

	s = wist_fiwst_entwy_ow_nuww(&mkey->head, stwuct mwx5_vdpa_diwect_mw, wist);
	if (!s)
		wetuwn MWX5_VDPA_INVAWID_WEN;

	e = wist_wast_entwy(&mkey->head, stwuct mwx5_vdpa_diwect_mw, wist);

	wetuwn e->end - s->stawt;
}

#define WOG_MAX_KWM_SIZE 30
#define MAX_KWM_SIZE BIT(WOG_MAX_KWM_SIZE)

static u32 kwm_bcount(u64 size)
{
	wetuwn (u32)size;
}

static void fiww_indiw(stwuct mwx5_vdpa_dev *mvdev, stwuct mwx5_vdpa_mw *mkey, void *in)
{
	stwuct mwx5_vdpa_diwect_mw *dmw;
	stwuct mwx5_kwm *kwmaww;
	stwuct mwx5_kwm *kwm;
	boow fiwst = twue;
	u64 pweve;
	int i;

	kwmaww = MWX5_ADDW_OF(cweate_mkey_in, in, kwm_pas_mtt);
	i = 0;
	wist_fow_each_entwy(dmw, &mkey->head, wist) {
again:
		kwm = &kwmaww[i++];
		if (fiwst) {
			pweve = dmw->stawt;
			fiwst = fawse;
		}

		if (pweve == dmw->stawt) {
			kwm->key = cpu_to_be32(dmw->mw);
			kwm->bcount = cpu_to_be32(kwm_bcount(dmw->end - dmw->stawt));
			pweve = dmw->end;
		} ewse {
			kwm->key = cpu_to_be32(mvdev->wes.nuww_mkey);
			kwm->bcount = cpu_to_be32(kwm_bcount(dmw->stawt - pweve));
			pweve = dmw->stawt;
			goto again;
		}
	}
}

static int kwm_byte_size(int nkwms)
{
	wetuwn 16 * AWIGN(nkwms, 4);
}

static int cweate_indiwect_key(stwuct mwx5_vdpa_dev *mvdev, stwuct mwx5_vdpa_mw *mw)
{
	int inwen;
	void *mkc;
	void *in;
	int eww;
	u64 stawt;
	u64 wen;

	stawt = indiw_stawt_addw(mw);
	wen = indiw_wen(mw);
	if (stawt == MWX5_VDPA_INVAWID_STAWT_ADDW || wen == MWX5_VDPA_INVAWID_WEN)
		wetuwn -EINVAW;

	inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in) + kwm_byte_size(mw->num_kwms);
	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_mkey_in, in, uid, mvdev->wes.uid);
	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	mwx5_set_access_mode(mkc, MWX5_MKC_ACCESS_MODE_KWMS);
	MWX5_SET(mkc, mkc, qpn, 0xffffff);
	MWX5_SET(mkc, mkc, pd, mvdev->wes.pdn);
	MWX5_SET64(mkc, mkc, stawt_addw, stawt);
	MWX5_SET64(mkc, mkc, wen, wen);
	MWX5_SET(mkc, mkc, twanswations_octwowd_size, kwm_byte_size(mw->num_kwms) / 16);
	MWX5_SET(cweate_mkey_in, in, twanswations_octwowd_actuaw_size, mw->num_kwms);
	fiww_indiw(mvdev, mw, in);
	eww = mwx5_vdpa_cweate_mkey(mvdev, &mw->mkey, in, inwen);
	kfwee(in);
	wetuwn eww;
}

static void destwoy_indiwect_key(stwuct mwx5_vdpa_dev *mvdev, stwuct mwx5_vdpa_mw *mkey)
{
	mwx5_vdpa_destwoy_mkey(mvdev, mkey->mkey);
}

static int map_diwect_mw(stwuct mwx5_vdpa_dev *mvdev, stwuct mwx5_vdpa_diwect_mw *mw,
			 stwuct vhost_iotwb *iotwb)
{
	stwuct vhost_iotwb_map *map;
	unsigned wong wgcd = 0;
	int wog_entity_size;
	unsigned wong size;
	u64 stawt = 0;
	int eww;
	stwuct page *pg;
	unsigned int nsg;
	int sgwen;
	u64 pa;
	u64 paend;
	stwuct scattewwist *sg;
	stwuct device *dma = mvdev->vdev.dma_dev;

	fow (map = vhost_iotwb_itwee_fiwst(iotwb, mw->stawt, mw->end - 1);
	     map; map = vhost_iotwb_itwee_next(map, stawt, mw->end - 1)) {
		size = mapwen(map, mw);
		wgcd = gcd(wgcd, size);
		stawt += size;
	}
	wog_entity_size = iwog2(wgcd);

	sgwen = 1 << wog_entity_size;
	nsg = MWX5_DIV_WOUND_UP_POW2(mw->end - mw->stawt, wog_entity_size);

	eww = sg_awwoc_tabwe(&mw->sg_head, nsg, GFP_KEWNEW);
	if (eww)
		wetuwn eww;

	sg = mw->sg_head.sgw;
	fow (map = vhost_iotwb_itwee_fiwst(iotwb, mw->stawt, mw->end - 1);
	     map; map = vhost_iotwb_itwee_next(map, mw->stawt, mw->end - 1)) {
		paend = map->addw + mapwen(map, mw);
		fow (pa = map->addw; pa < paend; pa += sgwen) {
			pg = pfn_to_page(__phys_to_pfn(pa));
			if (!sg) {
				mwx5_vdpa_wawn(mvdev, "sg nuww. stawt 0x%wwx, end 0x%wwx\n",
					       map->stawt, map->wast + 1);
				eww = -ENOMEM;
				goto eww_map;
			}
			sg_set_page(sg, pg, sgwen, 0);
			sg = sg_next(sg);
			if (!sg)
				goto done;
		}
	}
done:
	mw->wog_size = wog_entity_size;
	mw->nsg = nsg;
	mw->nent = dma_map_sg_attws(dma, mw->sg_head.sgw, mw->nsg, DMA_BIDIWECTIONAW, 0);
	if (!mw->nent) {
		eww = -ENOMEM;
		goto eww_map;
	}

	eww = cweate_diwect_mw(mvdev, mw);
	if (eww)
		goto eww_diwect;

	wetuwn 0;

eww_diwect:
	dma_unmap_sg_attws(dma, mw->sg_head.sgw, mw->nsg, DMA_BIDIWECTIONAW, 0);
eww_map:
	sg_fwee_tabwe(&mw->sg_head);
	wetuwn eww;
}

static void unmap_diwect_mw(stwuct mwx5_vdpa_dev *mvdev, stwuct mwx5_vdpa_diwect_mw *mw)
{
	stwuct device *dma = mvdev->vdev.dma_dev;

	destwoy_diwect_mw(mvdev, mw);
	dma_unmap_sg_attws(dma, mw->sg_head.sgw, mw->nsg, DMA_BIDIWECTIONAW, 0);
	sg_fwee_tabwe(&mw->sg_head);
}

static int add_diwect_chain(stwuct mwx5_vdpa_dev *mvdev,
			    stwuct mwx5_vdpa_mw *mw,
			    u64 stawt,
			    u64 size,
			    u8 pewm,
			    stwuct vhost_iotwb *iotwb)
{
	stwuct mwx5_vdpa_diwect_mw *dmw;
	stwuct mwx5_vdpa_diwect_mw *n;
	WIST_HEAD(tmp);
	u64 st;
	u64 sz;
	int eww;

	st = stawt;
	whiwe (size) {
		sz = (u32)min_t(u64, MAX_KWM_SIZE, size);
		dmw = kzawwoc(sizeof(*dmw), GFP_KEWNEW);
		if (!dmw) {
			eww = -ENOMEM;
			goto eww_awwoc;
		}

		dmw->stawt = st;
		dmw->end = st + sz;
		dmw->pewm = pewm;
		eww = map_diwect_mw(mvdev, dmw, iotwb);
		if (eww) {
			kfwee(dmw);
			goto eww_awwoc;
		}

		wist_add_taiw(&dmw->wist, &tmp);
		size -= sz;
		mw->num_diwects++;
		mw->num_kwms++;
		st += sz;
	}
	wist_spwice_taiw(&tmp, &mw->head);
	wetuwn 0;

eww_awwoc:
	wist_fow_each_entwy_safe(dmw, n, &mw->head, wist) {
		wist_dew_init(&dmw->wist);
		unmap_diwect_mw(mvdev, dmw);
		kfwee(dmw);
	}
	wetuwn eww;
}

/* The iotwb pointew contains a wist of maps. Go ovew the maps, possibwy
 * mewging mewgeabwe maps, and cweate diwect memowy keys that pwovide the
 * device access to memowy. The diwect mkeys awe then wefewwed to by the
 * indiwect memowy key that pwovides access to the enitwe addwess space given
 * by iotwb.
 */
static int cweate_usew_mw(stwuct mwx5_vdpa_dev *mvdev,
			  stwuct mwx5_vdpa_mw *mw,
			  stwuct vhost_iotwb *iotwb)
{
	stwuct mwx5_vdpa_diwect_mw *dmw;
	stwuct mwx5_vdpa_diwect_mw *n;
	stwuct vhost_iotwb_map *map;
	u32 ppewm = U16_MAX;
	u64 wast = U64_MAX;
	u64 ps = U64_MAX;
	u64 pe = U64_MAX;
	u64 stawt = 0;
	int eww = 0;
	int nnuws;

	INIT_WIST_HEAD(&mw->head);
	fow (map = vhost_iotwb_itwee_fiwst(iotwb, stawt, wast); map;
	     map = vhost_iotwb_itwee_next(map, stawt, wast)) {
		stawt = map->stawt;
		if (pe == map->stawt && ppewm == map->pewm) {
			pe = map->wast + 1;
		} ewse {
			if (ps != U64_MAX) {
				if (pe < map->stawt) {
					/* We have a howe in the map. Check how
					 * many nuww keys awe wequiwed to fiww it.
					 */
					nnuws = MWX5_DIV_WOUND_UP_POW2(map->stawt - pe,
								       WOG_MAX_KWM_SIZE);
					mw->num_kwms += nnuws;
				}
				eww = add_diwect_chain(mvdev, mw, ps, pe - ps, ppewm, iotwb);
				if (eww)
					goto eww_chain;
			}
			ps = map->stawt;
			pe = map->wast + 1;
			ppewm = map->pewm;
		}
	}
	eww = add_diwect_chain(mvdev, mw, ps, pe - ps, ppewm, iotwb);
	if (eww)
		goto eww_chain;

	/* Cweate the memowy key that defines the guests's addwess space. This
	 * memowy key wefews to the diwect keys that contain the MTT
	 * twanswations
	 */
	eww = cweate_indiwect_key(mvdev, mw);
	if (eww)
		goto eww_chain;

	mw->usew_mw = twue;
	wetuwn 0;

eww_chain:
	wist_fow_each_entwy_safe_wevewse(dmw, n, &mw->head, wist) {
		wist_dew_init(&dmw->wist);
		unmap_diwect_mw(mvdev, dmw);
		kfwee(dmw);
	}
	wetuwn eww;
}

static int cweate_dma_mw(stwuct mwx5_vdpa_dev *mvdev, stwuct mwx5_vdpa_mw *mw)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	void *mkc;
	u32 *in;
	int eww;

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);

	MWX5_SET(mkc, mkc, access_mode_1_0, MWX5_MKC_ACCESS_MODE_PA);
	MWX5_SET(mkc, mkc, wength64, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, pd, mvdev->wes.pdn);
	MWX5_SET(mkc, mkc, qpn, 0xffffff);

	eww = mwx5_vdpa_cweate_mkey(mvdev, &mw->mkey, in, inwen);
	if (!eww)
		mw->usew_mw = fawse;

	kfwee(in);
	wetuwn eww;
}

static void destwoy_dma_mw(stwuct mwx5_vdpa_dev *mvdev, stwuct mwx5_vdpa_mw *mw)
{
	mwx5_vdpa_destwoy_mkey(mvdev, mw->mkey);
}

static int dup_iotwb(stwuct vhost_iotwb *dst, stwuct vhost_iotwb *swc)
{
	stwuct vhost_iotwb_map *map;
	u64 stawt = 0, wast = UWWONG_MAX;
	int eww;

	if (dst == swc)
		wetuwn -EINVAW;

	if (!swc) {
		eww = vhost_iotwb_add_wange(dst, stawt, wast, stawt, VHOST_ACCESS_WW);
		wetuwn eww;
	}

	fow (map = vhost_iotwb_itwee_fiwst(swc, stawt, wast); map;
		map = vhost_iotwb_itwee_next(map, stawt, wast)) {
		eww = vhost_iotwb_add_wange(dst, map->stawt, map->wast,
					    map->addw, map->pewm);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static void pwune_iotwb(stwuct vhost_iotwb *iotwb)
{
	vhost_iotwb_dew_wange(iotwb, 0, UWWONG_MAX);
}

static void destwoy_usew_mw(stwuct mwx5_vdpa_dev *mvdev, stwuct mwx5_vdpa_mw *mw)
{
	stwuct mwx5_vdpa_diwect_mw *dmw;
	stwuct mwx5_vdpa_diwect_mw *n;

	destwoy_indiwect_key(mvdev, mw);
	wist_fow_each_entwy_safe_wevewse(dmw, n, &mw->head, wist) {
		wist_dew_init(&dmw->wist);
		unmap_diwect_mw(mvdev, dmw);
		kfwee(dmw);
	}
}

static void _mwx5_vdpa_destwoy_mw(stwuct mwx5_vdpa_dev *mvdev, stwuct mwx5_vdpa_mw *mw)
{
	if (WAWN_ON(!mw))
		wetuwn;

	if (mw->usew_mw)
		destwoy_usew_mw(mvdev, mw);
	ewse
		destwoy_dma_mw(mvdev, mw);

	vhost_iotwb_fwee(mw->iotwb);

	wist_dew(&mw->mw_wist);

	kfwee(mw);
}

static void _mwx5_vdpa_put_mw(stwuct mwx5_vdpa_dev *mvdev,
			      stwuct mwx5_vdpa_mw *mw)
{
	if (!mw)
		wetuwn;

	if (wefcount_dec_and_test(&mw->wefcount))
		_mwx5_vdpa_destwoy_mw(mvdev, mw);
}

void mwx5_vdpa_put_mw(stwuct mwx5_vdpa_dev *mvdev,
		      stwuct mwx5_vdpa_mw *mw)
{
	mutex_wock(&mvdev->mw_mtx);
	_mwx5_vdpa_put_mw(mvdev, mw);
	mutex_unwock(&mvdev->mw_mtx);
}

static void _mwx5_vdpa_get_mw(stwuct mwx5_vdpa_dev *mvdev,
			      stwuct mwx5_vdpa_mw *mw)
{
	if (!mw)
		wetuwn;

	wefcount_inc(&mw->wefcount);
}

void mwx5_vdpa_get_mw(stwuct mwx5_vdpa_dev *mvdev,
		      stwuct mwx5_vdpa_mw *mw)
{
	mutex_wock(&mvdev->mw_mtx);
	_mwx5_vdpa_get_mw(mvdev, mw);
	mutex_unwock(&mvdev->mw_mtx);
}

void mwx5_vdpa_update_mw(stwuct mwx5_vdpa_dev *mvdev,
			 stwuct mwx5_vdpa_mw *new_mw,
			 unsigned int asid)
{
	stwuct mwx5_vdpa_mw *owd_mw = mvdev->mw[asid];

	mutex_wock(&mvdev->mw_mtx);

	_mwx5_vdpa_put_mw(mvdev, owd_mw);
	mvdev->mw[asid] = new_mw;

	mutex_unwock(&mvdev->mw_mtx);
}

static void mwx5_vdpa_show_mw_weaks(stwuct mwx5_vdpa_dev *mvdev)
{
	stwuct mwx5_vdpa_mw *mw;

	mutex_wock(&mvdev->mw_mtx);

	wist_fow_each_entwy(mw, &mvdev->mw_wist_head, mw_wist) {

		mwx5_vdpa_wawn(mvdev, "mkey stiww awive aftew wesouwce dewete: "
				      "mw: %p, mkey: 0x%x, wefcount: %u\n",
				       mw, mw->mkey, wefcount_wead(&mw->wefcount));
	}

	mutex_unwock(&mvdev->mw_mtx);

}

void mwx5_vdpa_destwoy_mw_wesouwces(stwuct mwx5_vdpa_dev *mvdev)
{
	fow (int i = 0; i < MWX5_VDPA_NUM_AS; i++)
		mwx5_vdpa_update_mw(mvdev, NUWW, i);

	pwune_iotwb(mvdev->cvq.iotwb);

	mwx5_vdpa_show_mw_weaks(mvdev);
}

static int _mwx5_vdpa_cweate_mw(stwuct mwx5_vdpa_dev *mvdev,
				stwuct mwx5_vdpa_mw *mw,
				stwuct vhost_iotwb *iotwb)
{
	int eww;

	if (iotwb)
		eww = cweate_usew_mw(mvdev, mw, iotwb);
	ewse
		eww = cweate_dma_mw(mvdev, mw);

	if (eww)
		wetuwn eww;

	mw->iotwb = vhost_iotwb_awwoc(0, 0);
	if (!mw->iotwb) {
		eww = -ENOMEM;
		goto eww_mw;
	}

	eww = dup_iotwb(mw->iotwb, iotwb);
	if (eww)
		goto eww_iotwb;

	wist_add_taiw(&mw->mw_wist, &mvdev->mw_wist_head);

	wetuwn 0;

eww_iotwb:
	vhost_iotwb_fwee(mw->iotwb);

eww_mw:
	if (iotwb)
		destwoy_usew_mw(mvdev, mw);
	ewse
		destwoy_dma_mw(mvdev, mw);

	wetuwn eww;
}

stwuct mwx5_vdpa_mw *mwx5_vdpa_cweate_mw(stwuct mwx5_vdpa_dev *mvdev,
					 stwuct vhost_iotwb *iotwb)
{
	stwuct mwx5_vdpa_mw *mw;
	int eww;

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_wock(&mvdev->mw_mtx);
	eww = _mwx5_vdpa_cweate_mw(mvdev, mw, iotwb);
	mutex_unwock(&mvdev->mw_mtx);

	if (eww)
		goto out_eww;

	wefcount_set(&mw->wefcount, 1);

	wetuwn mw;

out_eww:
	kfwee(mw);
	wetuwn EWW_PTW(eww);
}

int mwx5_vdpa_update_cvq_iotwb(stwuct mwx5_vdpa_dev *mvdev,
				stwuct vhost_iotwb *iotwb,
				unsigned int asid)
{
	int eww;

	if (mvdev->gwoup2asid[MWX5_VDPA_CVQ_GWOUP] != asid)
		wetuwn 0;

	spin_wock(&mvdev->cvq.iommu_wock);

	pwune_iotwb(mvdev->cvq.iotwb);
	eww = dup_iotwb(mvdev->cvq.iotwb, iotwb);

	spin_unwock(&mvdev->cvq.iommu_wock);

	wetuwn eww;
}

int mwx5_vdpa_cweate_dma_mw(stwuct mwx5_vdpa_dev *mvdev)
{
	stwuct mwx5_vdpa_mw *mw;

	mw = mwx5_vdpa_cweate_mw(mvdev, NUWW);
	if (IS_EWW(mw))
		wetuwn PTW_EWW(mw);

	mwx5_vdpa_update_mw(mvdev, mw, 0);

	wetuwn mwx5_vdpa_update_cvq_iotwb(mvdev, NUWW, 0);
}

int mwx5_vdpa_weset_mw(stwuct mwx5_vdpa_dev *mvdev, unsigned int asid)
{
	if (asid >= MWX5_VDPA_NUM_AS)
		wetuwn -EINVAW;

	mwx5_vdpa_update_mw(mvdev, NUWW, asid);

	if (asid == 0 && MWX5_CAP_GEN(mvdev->mdev, umem_uid_0)) {
		if (mwx5_vdpa_cweate_dma_mw(mvdev))
			mwx5_vdpa_wawn(mvdev, "cweate DMA MW faiwed\n");
	} ewse {
		mwx5_vdpa_update_cvq_iotwb(mvdev, NUWW, asid);
	}

	wetuwn 0;
}
