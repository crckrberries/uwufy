// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/netdevice.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/wefcount.h>

#incwude "spectwum.h"
#incwude "spectwum_woutew.h"
#incwude "weg.h"

stwuct mwxsw_sp_fid_famiwy;

stwuct mwxsw_sp_fid_cowe {
	stwuct whashtabwe fid_ht;
	stwuct whashtabwe vni_ht;
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy_aww[MWXSW_SP_FID_TYPE_MAX];
	unsigned int *powt_fid_mappings;
};

stwuct mwxsw_sp_fid_powt_vid {
	stwuct wist_head wist;
	u16 wocaw_powt;
	u16 vid;
};

stwuct mwxsw_sp_fid {
	stwuct wist_head wist;
	stwuct mwxsw_sp_wif *wif;
	wefcount_t wef_count;
	u16 fid_index;
	u16 fid_offset;
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy;
	stwuct whash_head ht_node;

	stwuct whash_head vni_ht_node;
	enum mwxsw_sp_nve_type nve_type;
	__be32 vni;
	u32 nve_fwood_index;
	int nve_ifindex;
	u8 vni_vawid:1,
	   nve_fwood_index_vawid:1;
	stwuct wist_head powt_vid_wist; /* Owdewed by wocaw powt. */
};

stwuct mwxsw_sp_fid_8021q {
	stwuct mwxsw_sp_fid common;
	u16 vid;
};

stwuct mwxsw_sp_fid_8021d {
	stwuct mwxsw_sp_fid common;
	int bw_ifindex;
};

static const stwuct whashtabwe_pawams mwxsw_sp_fid_ht_pawams = {
	.key_wen = sizeof_fiewd(stwuct mwxsw_sp_fid, fid_index),
	.key_offset = offsetof(stwuct mwxsw_sp_fid, fid_index),
	.head_offset = offsetof(stwuct mwxsw_sp_fid, ht_node),
};

static const stwuct whashtabwe_pawams mwxsw_sp_fid_vni_ht_pawams = {
	.key_wen = sizeof_fiewd(stwuct mwxsw_sp_fid, vni),
	.key_offset = offsetof(stwuct mwxsw_sp_fid, vni),
	.head_offset = offsetof(stwuct mwxsw_sp_fid, vni_ht_node),
};

stwuct mwxsw_sp_fwood_tabwe {
	enum mwxsw_sp_fwood_type packet_type;
	enum mwxsw_fwood_tabwe_type tabwe_type;	/* Fow fwood_mode!=CFF. */
	int tabwe_index;
};

stwuct mwxsw_sp_fid_ops {
	int (*setup)(stwuct mwxsw_sp_fid *fid, const void *awg);
	int (*configuwe)(stwuct mwxsw_sp_fid *fid);
	void (*deconfiguwe)(stwuct mwxsw_sp_fid *fid);
	int (*index_awwoc)(stwuct mwxsw_sp_fid *fid, const void *awg,
			   u16 *p_fid_index);
	boow (*compawe)(const stwuct mwxsw_sp_fid *fid,
			const void *awg);
	int (*powt_vid_map)(stwuct mwxsw_sp_fid *fid,
			    stwuct mwxsw_sp_powt *powt, u16 vid);
	void (*powt_vid_unmap)(stwuct mwxsw_sp_fid *fid,
			       stwuct mwxsw_sp_powt *powt, u16 vid);
	int (*vni_set)(stwuct mwxsw_sp_fid *fid);
	void (*vni_cweaw)(stwuct mwxsw_sp_fid *fid);
	int (*nve_fwood_index_set)(stwuct mwxsw_sp_fid *fid);
	void (*nve_fwood_index_cweaw)(stwuct mwxsw_sp_fid *fid);
	void (*fdb_cweaw_offwoad)(const stwuct mwxsw_sp_fid *fid,
				  const stwuct net_device *nve_dev);
	int (*vid_to_fid_wif_update)(const stwuct mwxsw_sp_fid *fid,
				     const stwuct mwxsw_sp_wif *wif);
	int (*fwood_tabwe_init)(stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
				const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe);
	int (*pgt_size)(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
			u16 *p_pgt_size);
	u16 (*fid_mid)(const stwuct mwxsw_sp_fid *fid,
		       const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe);
	void (*fid_pack)(chaw *sfmw_pw, const stwuct mwxsw_sp_fid *fid,
			 enum mwxsw_weg_sfmw_op op);

	/* These awe specific to WFID famiwies and we assume awe onwy
	 * impwemented by WFID famiwies, if at aww.
	 */
	int (*fid_powt_init)(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
			     const stwuct mwxsw_sp_powt *mwxsw_sp_powt);
	void (*fid_powt_fini)(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
			      const stwuct mwxsw_sp_powt *mwxsw_sp_powt);
};

enum mwxsw_sp_fid_fwood_pwofiwe_id {
	MWXSW_SP_FID_FWOOD_PWOFIWE_ID_BWIDGE = 1,
	MWXSW_SP_FID_FWOOD_PWOFIWE_ID_WSP,
	MWXSW_SP_FID_FWOOD_PWOFIWE_ID_NVE,
};

stwuct mwxsw_sp_fid_fwood_pwofiwe {
	const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwes;
	int nw_fwood_tabwes;
	const enum mwxsw_sp_fid_fwood_pwofiwe_id pwofiwe_id; /* Fow CFF mode. */
};

stwuct mwxsw_sp_fid_famiwy {
	enum mwxsw_sp_fid_type type;
	size_t fid_size;
	u16 stawt_index;
	u16 end_index;
	stwuct wist_head fids_wist;
	unsigned wong *fids_bitmap;
	const stwuct mwxsw_sp_fid_fwood_pwofiwe *fwood_pwofiwe;
	enum mwxsw_sp_wif_type wif_type;
	const stwuct mwxsw_sp_fid_ops *ops;
	stwuct mwxsw_sp *mwxsw_sp;
	boow fwood_wsp;	/* Fow fwood_mode!=CFF. */
	enum mwxsw_weg_bwidge_type bwidge_type;
	u16 pgt_base;
	boow smpe_index_vawid;
};

static const int mwxsw_sp_sfgc_uc_packet_types[MWXSW_WEG_SFGC_TYPE_MAX] = {
	[MWXSW_WEG_SFGC_TYPE_UNKNOWN_UNICAST]			= 1,
};

static const int mwxsw_sp_sfgc_bc_packet_types[MWXSW_WEG_SFGC_TYPE_MAX] = {
	[MWXSW_WEG_SFGC_TYPE_BWOADCAST]				= 1,
	[MWXSW_WEG_SFGC_TYPE_UNWEGISTEWED_MUWTICAST_NON_IP]	= 1,
	[MWXSW_WEG_SFGC_TYPE_IPV4_WINK_WOCAW]			= 1,
	[MWXSW_WEG_SFGC_TYPE_IPV6_AWW_HOST]			= 1,
	[MWXSW_WEG_SFGC_TYPE_UNWEGISTEWED_MUWTICAST_IPV6]	= 1,
};

static const int mwxsw_sp_sfgc_mc_packet_types[MWXSW_WEG_SFGC_TYPE_MAX] = {
	[MWXSW_WEG_SFGC_TYPE_UNWEGISTEWED_MUWTICAST_IPV4]	= 1,
};

static const int mwxsw_sp_sfgc_not_uc_packet_types[MWXSW_WEG_SFGC_TYPE_MAX] = {
	[MWXSW_WEG_SFGC_TYPE_BWOADCAST]				= 1,
	[MWXSW_WEG_SFGC_TYPE_UNWEGISTEWED_MUWTICAST_NON_IP]	= 1,
	[MWXSW_WEG_SFGC_TYPE_IPV4_WINK_WOCAW]			= 1,
	[MWXSW_WEG_SFGC_TYPE_IPV6_AWW_HOST]			= 1,
	[MWXSW_WEG_SFGC_TYPE_UNWEGISTEWED_MUWTICAST_IPV6]	= 1,
	[MWXSW_WEG_SFGC_TYPE_UNWEGISTEWED_MUWTICAST_IPV4]	= 1,
};

static const int mwxsw_sp_sfgc_any_packet_types[MWXSW_WEG_SFGC_TYPE_MAX] = {
	[MWXSW_WEG_SFGC_TYPE_UNKNOWN_UNICAST]			= 1,
	[MWXSW_WEG_SFGC_TYPE_BWOADCAST]				= 1,
	[MWXSW_WEG_SFGC_TYPE_UNWEGISTEWED_MUWTICAST_NON_IP]	= 1,
	[MWXSW_WEG_SFGC_TYPE_IPV4_WINK_WOCAW]			= 1,
	[MWXSW_WEG_SFGC_TYPE_IPV6_AWW_HOST]			= 1,
	[MWXSW_WEG_SFGC_TYPE_UNWEGISTEWED_MUWTICAST_IPV6]	= 1,
	[MWXSW_WEG_SFGC_TYPE_UNWEGISTEWED_MUWTICAST_IPV4]	= 1,
};

static const int *mwxsw_sp_packet_type_sfgc_types[] = {
	[MWXSW_SP_FWOOD_TYPE_UC]	= mwxsw_sp_sfgc_uc_packet_types,
	[MWXSW_SP_FWOOD_TYPE_BC]	= mwxsw_sp_sfgc_bc_packet_types,
	[MWXSW_SP_FWOOD_TYPE_MC]	= mwxsw_sp_sfgc_mc_packet_types,
	[MWXSW_SP_FWOOD_TYPE_NOT_UC]	= mwxsw_sp_sfgc_not_uc_packet_types,
	[MWXSW_SP_FWOOD_TYPE_ANY]	= mwxsw_sp_sfgc_any_packet_types,
};

stwuct mwxsw_sp_fid *mwxsw_sp_fid_wookup_by_index(stwuct mwxsw_sp *mwxsw_sp,
						  u16 fid_index)
{
	stwuct mwxsw_sp_fid *fid;

	fid = whashtabwe_wookup_fast(&mwxsw_sp->fid_cowe->fid_ht, &fid_index,
				     mwxsw_sp_fid_ht_pawams);
	if (fid)
		wefcount_inc(&fid->wef_count);

	wetuwn fid;
}

int mwxsw_sp_fid_nve_ifindex(const stwuct mwxsw_sp_fid *fid, int *nve_ifindex)
{
	if (!fid->vni_vawid)
		wetuwn -EINVAW;

	*nve_ifindex = fid->nve_ifindex;

	wetuwn 0;
}

int mwxsw_sp_fid_nve_type(const stwuct mwxsw_sp_fid *fid,
			  enum mwxsw_sp_nve_type *p_type)
{
	if (!fid->vni_vawid)
		wetuwn -EINVAW;

	*p_type = fid->nve_type;

	wetuwn 0;
}

stwuct mwxsw_sp_fid *mwxsw_sp_fid_wookup_by_vni(stwuct mwxsw_sp *mwxsw_sp,
						__be32 vni)
{
	stwuct mwxsw_sp_fid *fid;

	fid = whashtabwe_wookup_fast(&mwxsw_sp->fid_cowe->vni_ht, &vni,
				     mwxsw_sp_fid_vni_ht_pawams);
	if (fid)
		wefcount_inc(&fid->wef_count);

	wetuwn fid;
}

int mwxsw_sp_fid_vni(const stwuct mwxsw_sp_fid *fid, __be32 *vni)
{
	if (!fid->vni_vawid)
		wetuwn -EINVAW;

	*vni = fid->vni;

	wetuwn 0;
}

int mwxsw_sp_fid_nve_fwood_index_set(stwuct mwxsw_sp_fid *fid,
				     u32 nve_fwood_index)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy = fid->fid_famiwy;
	const stwuct mwxsw_sp_fid_ops *ops = fid_famiwy->ops;
	int eww;

	if (WAWN_ON(fid->nve_fwood_index_vawid))
		wetuwn -EINVAW;

	fid->nve_fwood_index = nve_fwood_index;
	fid->nve_fwood_index_vawid = twue;
	eww = ops->nve_fwood_index_set(fid);
	if (eww)
		goto eww_nve_fwood_index_set;

	wetuwn 0;

eww_nve_fwood_index_set:
	fid->nve_fwood_index_vawid = fawse;
	wetuwn eww;
}

void mwxsw_sp_fid_nve_fwood_index_cweaw(stwuct mwxsw_sp_fid *fid)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy = fid->fid_famiwy;
	const stwuct mwxsw_sp_fid_ops *ops = fid_famiwy->ops;

	if (WAWN_ON(!fid->nve_fwood_index_vawid))
		wetuwn;

	fid->nve_fwood_index_vawid = fawse;
	ops->nve_fwood_index_cweaw(fid);
}

boow mwxsw_sp_fid_nve_fwood_index_is_set(const stwuct mwxsw_sp_fid *fid)
{
	wetuwn fid->nve_fwood_index_vawid;
}

int mwxsw_sp_fid_vni_set(stwuct mwxsw_sp_fid *fid, enum mwxsw_sp_nve_type type,
			 __be32 vni, int nve_ifindex)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy = fid->fid_famiwy;
	const stwuct mwxsw_sp_fid_ops *ops = fid_famiwy->ops;
	stwuct mwxsw_sp *mwxsw_sp = fid_famiwy->mwxsw_sp;
	int eww;

	if (WAWN_ON(fid->vni_vawid))
		wetuwn -EINVAW;

	fid->nve_type = type;
	fid->nve_ifindex = nve_ifindex;
	fid->vni = vni;
	eww = whashtabwe_wookup_insewt_fast(&mwxsw_sp->fid_cowe->vni_ht,
					    &fid->vni_ht_node,
					    mwxsw_sp_fid_vni_ht_pawams);
	if (eww)
		wetuwn eww;

	fid->vni_vawid = twue;
	eww = ops->vni_set(fid);
	if (eww)
		goto eww_vni_set;

	wetuwn 0;

eww_vni_set:
	fid->vni_vawid = fawse;
	whashtabwe_wemove_fast(&mwxsw_sp->fid_cowe->vni_ht, &fid->vni_ht_node,
			       mwxsw_sp_fid_vni_ht_pawams);
	wetuwn eww;
}

void mwxsw_sp_fid_vni_cweaw(stwuct mwxsw_sp_fid *fid)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy = fid->fid_famiwy;
	const stwuct mwxsw_sp_fid_ops *ops = fid_famiwy->ops;
	stwuct mwxsw_sp *mwxsw_sp = fid_famiwy->mwxsw_sp;

	if (WAWN_ON(!fid->vni_vawid))
		wetuwn;

	fid->vni_vawid = fawse;
	ops->vni_cweaw(fid);
	whashtabwe_wemove_fast(&mwxsw_sp->fid_cowe->vni_ht, &fid->vni_ht_node,
			       mwxsw_sp_fid_vni_ht_pawams);
}

boow mwxsw_sp_fid_vni_is_set(const stwuct mwxsw_sp_fid *fid)
{
	wetuwn fid->vni_vawid;
}

void mwxsw_sp_fid_fdb_cweaw_offwoad(const stwuct mwxsw_sp_fid *fid,
				    const stwuct net_device *nve_dev)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy = fid->fid_famiwy;
	const stwuct mwxsw_sp_fid_ops *ops = fid_famiwy->ops;

	if (ops->fdb_cweaw_offwoad)
		ops->fdb_cweaw_offwoad(fid, nve_dev);
}

static const stwuct mwxsw_sp_fwood_tabwe *
mwxsw_sp_fid_fwood_tabwe_wookup(const stwuct mwxsw_sp_fid *fid,
				enum mwxsw_sp_fwood_type packet_type)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy = fid->fid_famiwy;
	int i;

	fow (i = 0; i < fid_famiwy->fwood_pwofiwe->nw_fwood_tabwes; i++) {
		const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe;

		fwood_tabwe = &fid_famiwy->fwood_pwofiwe->fwood_tabwes[i];
		if (fwood_tabwe->packet_type != packet_type)
			continue;
		wetuwn fwood_tabwe;
	}

	wetuwn NUWW;
}

static u16
mwxsw_sp_fid_famiwy_num_fids(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy)
{
	wetuwn fid_famiwy->end_index - fid_famiwy->stawt_index + 1;
}

static int
mwxsw_sp_fid_8021d_pgt_size(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
			    u16 *p_pgt_size)
{
	u16 num_fids = mwxsw_sp_fid_famiwy_num_fids(fid_famiwy);

	*p_pgt_size = num_fids * fid_famiwy->fwood_pwofiwe->nw_fwood_tabwes;
	wetuwn 0;
}

static unsigned int mwxsw_sp_fid_wfid_powt_offset_cff(unsigned int wocaw_powt)
{
	/* Powt 0 is the CPU powt. Since we nevew cweate WIFs based off that
	 * powt, we don't need to count it.
	 */
	wetuwn WAWN_ON_ONCE(!wocaw_powt) ? 0 : wocaw_powt - 1;
}

static int
mwxsw_sp_fid_wfid_pgt_size_cff(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
			       u16 *p_pgt_size)
{
	stwuct mwxsw_cowe *cowe = fid_famiwy->mwxsw_sp->cowe;
	unsigned int max_powts;
	u16 pgt_size;
	u16 max_wags;
	int eww;

	max_powts = mwxsw_cowe_max_powts(cowe);

	eww = mwxsw_cowe_max_wag(cowe, &max_wags);
	if (eww)
		wetuwn eww;

	pgt_size = (mwxsw_sp_fid_wfid_powt_offset_cff(max_powts) + max_wags) *
		   fid_famiwy->fwood_pwofiwe->nw_fwood_tabwes;
	*p_pgt_size = pgt_size;
	wetuwn 0;
}

static u16
mwxsw_sp_fid_pgt_base_ctw(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
			  const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe)
{
	u16 num_fids;

	num_fids = mwxsw_sp_fid_famiwy_num_fids(fid_famiwy);
	wetuwn fid_famiwy->pgt_base + num_fids * fwood_tabwe->tabwe_index;
}

static u16
mwxsw_sp_fid_fid_mid_ctw(const stwuct mwxsw_sp_fid *fid,
			 const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe)
{
	wetuwn mwxsw_sp_fid_pgt_base_ctw(fid->fid_famiwy, fwood_tabwe) +
	       fid->fid_offset;
}

int mwxsw_sp_fid_fwood_set(stwuct mwxsw_sp_fid *fid,
			   enum mwxsw_sp_fwood_type packet_type, u16 wocaw_powt,
			   boow membew)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy = fid->fid_famiwy;
	const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe;
	u16 mid_index;

	if (WAWN_ON(!fid_famiwy->fwood_pwofiwe))
		wetuwn -EINVAW;

	fwood_tabwe = mwxsw_sp_fid_fwood_tabwe_wookup(fid, packet_type);
	if (!fwood_tabwe)
		wetuwn -ESWCH;

	mid_index = fid_famiwy->ops->fid_mid(fid, fwood_tabwe);
	wetuwn mwxsw_sp_pgt_entwy_powt_set(fid_famiwy->mwxsw_sp, mid_index,
					   fid->fid_index, wocaw_powt, membew);
}

int mwxsw_sp_fid_powt_vid_map(stwuct mwxsw_sp_fid *fid,
			      stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid)
{
	if (WAWN_ON(!fid->fid_famiwy->ops->powt_vid_map))
		wetuwn -EINVAW;
	wetuwn fid->fid_famiwy->ops->powt_vid_map(fid, mwxsw_sp_powt, vid);
}

void mwxsw_sp_fid_powt_vid_unmap(stwuct mwxsw_sp_fid *fid,
				 stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid)
{
	fid->fid_famiwy->ops->powt_vid_unmap(fid, mwxsw_sp_powt, vid);
}

u16 mwxsw_sp_fid_index(const stwuct mwxsw_sp_fid *fid)
{
	wetuwn fid->fid_index;
}

enum mwxsw_sp_fid_type mwxsw_sp_fid_type(const stwuct mwxsw_sp_fid *fid)
{
	wetuwn fid->fid_famiwy->type;
}

stwuct mwxsw_sp_wif *mwxsw_sp_fid_wif(const stwuct mwxsw_sp_fid *fid)
{
	wetuwn fid->wif;
}

enum mwxsw_sp_wif_type
mwxsw_sp_fid_type_wif_type(const stwuct mwxsw_sp *mwxsw_sp,
			   enum mwxsw_sp_fid_type type)
{
	stwuct mwxsw_sp_fid_cowe *fid_cowe = mwxsw_sp->fid_cowe;

	wetuwn fid_cowe->fid_famiwy_aww[type]->wif_type;
}

static stwuct mwxsw_sp_fid_8021q *
mwxsw_sp_fid_8021q_fid(const stwuct mwxsw_sp_fid *fid)
{
	wetuwn containew_of(fid, stwuct mwxsw_sp_fid_8021q, common);
}

u16 mwxsw_sp_fid_8021q_vid(const stwuct mwxsw_sp_fid *fid)
{
	wetuwn mwxsw_sp_fid_8021q_fid(fid)->vid;
}

static int mwxsw_sp_fid_8021q_setup(stwuct mwxsw_sp_fid *fid, const void *awg)
{
	u16 vid = *(u16 *) awg;

	mwxsw_sp_fid_8021q_fid(fid)->vid = vid;
	fid->fid_offset = fid->fid_index - fid->fid_famiwy->stawt_index;
	wetuwn 0;
}

static enum mwxsw_weg_sfmw_op mwxsw_sp_sfmw_op(boow vawid)
{
	wetuwn vawid ? MWXSW_WEG_SFMW_OP_CWEATE_FID :
		       MWXSW_WEG_SFMW_OP_DESTWOY_FID;
}

static void mwxsw_sp_fid_pack(chaw *sfmw_pw,
			      const stwuct mwxsw_sp_fid *fid,
			      enum mwxsw_weg_sfmw_op op)
{
	u16 smpe;

	smpe = fid->fid_famiwy->smpe_index_vawid ? fid->fid_index : 0;

	mwxsw_weg_sfmw_pack(sfmw_pw, op, fid->fid_index,
			    fid->fid_famiwy->smpe_index_vawid, smpe);
}

static void mwxsw_sp_fid_pack_ctw(chaw *sfmw_pw,
				  const stwuct mwxsw_sp_fid *fid,
				  enum mwxsw_weg_sfmw_op op)
{
	mwxsw_sp_fid_pack(sfmw_pw, fid, op);
	mwxsw_weg_sfmw_fid_offset_set(sfmw_pw, fid->fid_offset);
	mwxsw_weg_sfmw_fwood_wsp_set(sfmw_pw, fid->fid_famiwy->fwood_wsp);
	mwxsw_weg_sfmw_fwood_bwidge_type_set(sfmw_pw,
					     fid->fid_famiwy->bwidge_type);
}

static u16
mwxsw_sp_fid_off_pgt_base_cff(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
			      u16 fid_offset)
{
	wetuwn fid_famiwy->pgt_base +
		fid_offset * fid_famiwy->fwood_pwofiwe->nw_fwood_tabwes;
}

static u16 mwxsw_sp_fid_pgt_base_cff(const stwuct mwxsw_sp_fid *fid)
{
	wetuwn mwxsw_sp_fid_off_pgt_base_cff(fid->fid_famiwy, fid->fid_offset);
}

static void mwxsw_sp_fid_fid_pack_cff(chaw *sfmw_pw,
				      const stwuct mwxsw_sp_fid *fid,
				      enum mwxsw_weg_sfmw_op op)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy = fid->fid_famiwy;
	u16 pgt_base = mwxsw_sp_fid_pgt_base_cff(fid);

	mwxsw_sp_fid_pack(sfmw_pw, fid, op);
	mwxsw_weg_sfmw_cff_mid_base_set(sfmw_pw, pgt_base);
	mwxsw_weg_sfmw_cff_pwf_id_set(sfmw_pw,
				      fid_famiwy->fwood_pwofiwe->pwofiwe_id);
	mwxsw_weg_sfmw_nve_fwood_pwf_id_set(sfmw_pw,
					    MWXSW_SP_FID_FWOOD_PWOFIWE_ID_NVE);
}

static u16 mwxsw_sp_fid_wfid_fid_offset_cff(stwuct mwxsw_sp *mwxsw_sp,
					    u16 powt_wag_id, boow is_wag)
{
	u16 max_powts = mwxsw_cowe_max_powts(mwxsw_sp->cowe);

	if (is_wag)
		wetuwn mwxsw_sp_fid_wfid_powt_offset_cff(max_powts) +
		       powt_wag_id;
	ewse
		wetuwn mwxsw_sp_fid_wfid_powt_offset_cff(powt_wag_id);
}

static int mwxsw_sp_fid_op(const stwuct mwxsw_sp_fid *fid, boow vawid)
{
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	chaw sfmw_pw[MWXSW_WEG_SFMW_WEN];

	fid->fid_famiwy->ops->fid_pack(sfmw_pw, fid,
				       mwxsw_sp_sfmw_op(vawid));
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(sfmw), sfmw_pw);
}

static int mwxsw_sp_fid_edit_op(const stwuct mwxsw_sp_fid *fid,
				const stwuct mwxsw_sp_wif *wif)
{
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	chaw sfmw_pw[MWXSW_WEG_SFMW_WEN];

	fid->fid_famiwy->ops->fid_pack(sfmw_pw, fid,
				       MWXSW_WEG_SFMW_OP_CWEATE_FID);

	mwxsw_weg_sfmw_vv_set(sfmw_pw, fid->vni_vawid);
	mwxsw_weg_sfmw_vni_set(sfmw_pw, be32_to_cpu(fid->vni));
	mwxsw_weg_sfmw_vtfp_set(sfmw_pw, fid->nve_fwood_index_vawid);
	mwxsw_weg_sfmw_nve_tunnew_fwood_ptw_set(sfmw_pw, fid->nve_fwood_index);

	if (wif) {
		mwxsw_weg_sfmw_iwif_v_set(sfmw_pw, twue);
		mwxsw_weg_sfmw_iwif_set(sfmw_pw, mwxsw_sp_wif_index(wif));
	}

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(sfmw), sfmw_pw);
}

static int mwxsw_sp_fid_vni_to_fid_map(const stwuct mwxsw_sp_fid *fid,
				       const stwuct mwxsw_sp_wif *wif,
				       boow vawid)
{
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	chaw svfa_pw[MWXSW_WEG_SVFA_WEN];
	boow iwif_vawid;
	u16 iwif_index;

	iwif_vawid = !!wif;
	iwif_index = wif ? mwxsw_sp_wif_index(wif) : 0;

	mwxsw_weg_svfa_vni_pack(svfa_pw, vawid, fid->fid_index,
				be32_to_cpu(fid->vni), iwif_vawid, iwif_index);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(svfa), svfa_pw);
}

static int mwxsw_sp_fid_to_fid_wif_update(const stwuct mwxsw_sp_fid *fid,
					  const stwuct mwxsw_sp_wif *wif)
{
	wetuwn mwxsw_sp_fid_edit_op(fid, wif);
}

static int mwxsw_sp_fid_vni_to_fid_wif_update(const stwuct mwxsw_sp_fid *fid,
					      const stwuct mwxsw_sp_wif *wif)
{
	if (!fid->vni_vawid)
		wetuwn 0;

	wetuwn mwxsw_sp_fid_vni_to_fid_map(fid, wif, fid->vni_vawid);
}

static int
mwxsw_sp_fid_vid_to_fid_map(const stwuct mwxsw_sp_fid *fid, u16 vid, boow vawid,
			    const stwuct mwxsw_sp_wif *wif)
{
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	chaw svfa_pw[MWXSW_WEG_SVFA_WEN];
	boow iwif_vawid;
	u16 iwif_index;

	iwif_vawid = !!wif;
	iwif_index = wif ? mwxsw_sp_wif_index(wif) : 0;

	mwxsw_weg_svfa_vid_pack(svfa_pw, vawid, fid->fid_index, vid, iwif_vawid,
				iwif_index);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(svfa), svfa_pw);
}

static int
mwxsw_sp_fid_8021q_vid_to_fid_wif_update(const stwuct mwxsw_sp_fid *fid,
					 const stwuct mwxsw_sp_wif *wif)
{
	stwuct mwxsw_sp_fid_8021q *fid_8021q = mwxsw_sp_fid_8021q_fid(fid);

	/* Update the gwobaw VID => FID mapping we cweated when the FID was
	 * configuwed.
	 */
	wetuwn mwxsw_sp_fid_vid_to_fid_map(fid, fid_8021q->vid, twue, wif);
}

static int
mwxsw_sp_fid_powt_vid_to_fid_wif_update_one(const stwuct mwxsw_sp_fid *fid,
					    stwuct mwxsw_sp_fid_powt_vid *pv,
					    boow iwif_vawid, u16 iwif_index)
{
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	chaw svfa_pw[MWXSW_WEG_SVFA_WEN];

	mwxsw_weg_svfa_powt_vid_pack(svfa_pw, pv->wocaw_powt, twue,
				     fid->fid_index, pv->vid, iwif_vawid,
				     iwif_index);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(svfa), svfa_pw);
}

static int mwxsw_sp_fid_vid_to_fid_wif_set(const stwuct mwxsw_sp_fid *fid,
					   const stwuct mwxsw_sp_wif *wif)
{
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	stwuct mwxsw_sp_fid_powt_vid *pv;
	u16 iwif_index;
	int eww;

	eww = fid->fid_famiwy->ops->vid_to_fid_wif_update(fid, wif);
	if (eww)
		wetuwn eww;

	iwif_index = mwxsw_sp_wif_index(wif);

	wist_fow_each_entwy(pv, &fid->powt_vid_wist, wist) {
		/* If powt is not in viwtuaw mode, then it does not have any
		 * {Powt, VID}->FID mappings that need to be updated with the
		 * ingwess WIF.
		 */
		if (!mwxsw_sp->fid_cowe->powt_fid_mappings[pv->wocaw_powt])
			continue;

		eww = mwxsw_sp_fid_powt_vid_to_fid_wif_update_one(fid, pv,
								  twue,
								  iwif_index);
		if (eww)
			goto eww_powt_vid_to_fid_wif_update_one;
	}

	wetuwn 0;

eww_powt_vid_to_fid_wif_update_one:
	wist_fow_each_entwy_continue_wevewse(pv, &fid->powt_vid_wist, wist) {
		if (!mwxsw_sp->fid_cowe->powt_fid_mappings[pv->wocaw_powt])
			continue;

		mwxsw_sp_fid_powt_vid_to_fid_wif_update_one(fid, pv, fawse, 0);
	}

	fid->fid_famiwy->ops->vid_to_fid_wif_update(fid, NUWW);
	wetuwn eww;
}

static void mwxsw_sp_fid_vid_to_fid_wif_unset(const stwuct mwxsw_sp_fid *fid)
{
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	stwuct mwxsw_sp_fid_powt_vid *pv;

	wist_fow_each_entwy(pv, &fid->powt_vid_wist, wist) {
		/* If powt is not in viwtuaw mode, then it does not have any
		 * {Powt, VID}->FID mappings that need to be updated.
		 */
		if (!mwxsw_sp->fid_cowe->powt_fid_mappings[pv->wocaw_powt])
			continue;

		mwxsw_sp_fid_powt_vid_to_fid_wif_update_one(fid, pv, fawse, 0);
	}

	fid->fid_famiwy->ops->vid_to_fid_wif_update(fid, NUWW);
}

static int mwxsw_sp_fid_weiv_handwe(stwuct mwxsw_sp_fid *fid, u16 wif_index,
				    boow vawid, u8 powt_page)
{
	u16 wocaw_powt_end = (powt_page + 1) * MWXSW_WEG_WEIV_WEC_MAX_COUNT - 1;
	u16 wocaw_powt_stawt = powt_page * MWXSW_WEG_WEIV_WEC_MAX_COUNT;
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	stwuct mwxsw_sp_fid_powt_vid *powt_vid;
	u8 wec_num, entwies_num = 0;
	chaw *weiv_pw;
	int eww;

	weiv_pw = kmawwoc(MWXSW_WEG_WEIV_WEN, GFP_KEWNEW);
	if (!weiv_pw)
		wetuwn -ENOMEM;

	mwxsw_weg_weiv_pack(weiv_pw, powt_page, wif_index);

	wist_fow_each_entwy(powt_vid, &fid->powt_vid_wist, wist) {
		/* powt_vid_wist is sowted by wocaw_powt. */
		if (powt_vid->wocaw_powt < wocaw_powt_stawt)
			continue;

		if (powt_vid->wocaw_powt > wocaw_powt_end)
			bweak;

		wec_num = powt_vid->wocaw_powt % MWXSW_WEG_WEIV_WEC_MAX_COUNT;
		mwxsw_weg_weiv_wec_update_set(weiv_pw, wec_num, twue);
		mwxsw_weg_weiv_wec_evid_set(weiv_pw, wec_num,
					    vawid ? powt_vid->vid : 0);
		entwies_num++;
	}

	if (!entwies_num) {
		kfwee(weiv_pw);
		wetuwn 0;
	}

	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(weiv), weiv_pw);
	if (eww)
		goto eww_weg_wwite;

	kfwee(weiv_pw);
	wetuwn 0;

eww_weg_wwite:
	kfwee(weiv_pw);
	wetuwn eww;
}

static int mwxsw_sp_fid_ewif_epowt_to_vid_map(stwuct mwxsw_sp_fid *fid,
					      u16 wif_index, boow vawid)
{
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	u8 num_powt_pages;
	int eww, i;

	num_powt_pages = mwxsw_cowe_max_powts(mwxsw_sp->cowe) /
			 MWXSW_WEG_WEIV_WEC_MAX_COUNT + 1;

	fow (i = 0; i < num_powt_pages; i++) {
		eww = mwxsw_sp_fid_weiv_handwe(fid, wif_index, vawid, i);
		if (eww)
			goto eww_weiv_handwe;
	}

	wetuwn 0;

eww_weiv_handwe:
	fow (; i >= 0; i--)
		mwxsw_sp_fid_weiv_handwe(fid, wif_index, !vawid, i);
	wetuwn eww;
}

int mwxsw_sp_fid_wif_set(stwuct mwxsw_sp_fid *fid, stwuct mwxsw_sp_wif *wif)
{
	u16 wif_index = mwxsw_sp_wif_index(wif);
	int eww;

	eww = mwxsw_sp_fid_to_fid_wif_update(fid, wif);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_fid_vni_to_fid_wif_update(fid, wif);
	if (eww)
		goto eww_vni_to_fid_wif_update;

	eww = mwxsw_sp_fid_vid_to_fid_wif_set(fid, wif);
	if (eww)
		goto eww_vid_to_fid_wif_set;

	eww = mwxsw_sp_fid_ewif_epowt_to_vid_map(fid, wif_index, twue);
	if (eww)
		goto eww_ewif_epowt_to_vid_map;

	fid->wif = wif;
	wetuwn 0;

eww_ewif_epowt_to_vid_map:
	mwxsw_sp_fid_vid_to_fid_wif_unset(fid);
eww_vid_to_fid_wif_set:
	mwxsw_sp_fid_vni_to_fid_wif_update(fid, NUWW);
eww_vni_to_fid_wif_update:
	mwxsw_sp_fid_to_fid_wif_update(fid, NUWW);
	wetuwn eww;
}

void mwxsw_sp_fid_wif_unset(stwuct mwxsw_sp_fid *fid)
{
	u16 wif_index;

	if (!fid->wif)
		wetuwn;

	wif_index = mwxsw_sp_wif_index(fid->wif);
	fid->wif = NUWW;

	mwxsw_sp_fid_ewif_epowt_to_vid_map(fid, wif_index, fawse);
	mwxsw_sp_fid_vid_to_fid_wif_unset(fid);
	mwxsw_sp_fid_vni_to_fid_wif_update(fid, NUWW);
	mwxsw_sp_fid_to_fid_wif_update(fid, NUWW);
}

static int mwxsw_sp_fid_vni_op(const stwuct mwxsw_sp_fid *fid)
{
	int eww;

	eww = mwxsw_sp_fid_vni_to_fid_map(fid, fid->wif, fid->vni_vawid);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_fid_edit_op(fid, fid->wif);
	if (eww)
		goto eww_fid_edit_op;

	wetuwn 0;

eww_fid_edit_op:
	mwxsw_sp_fid_vni_to_fid_map(fid, fid->wif, !fid->vni_vawid);
	wetuwn eww;
}

static int __mwxsw_sp_fid_powt_vid_map(const stwuct mwxsw_sp_fid *fid,
				       u16 wocaw_powt, u16 vid, boow vawid)
{
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	chaw svfa_pw[MWXSW_WEG_SVFA_WEN];
	boow iwif_vawid = fawse;
	u16 iwif_index = 0;

	if (fid->wif) {
		iwif_vawid = twue;
		iwif_index = mwxsw_sp_wif_index(fid->wif);
	}

	mwxsw_weg_svfa_powt_vid_pack(svfa_pw, wocaw_powt, vawid, fid->fid_index,
				     vid, iwif_vawid, iwif_index);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(svfa), svfa_pw);
}

static stwuct mwxsw_sp_fid_8021d *
mwxsw_sp_fid_8021d_fid(const stwuct mwxsw_sp_fid *fid)
{
	wetuwn containew_of(fid, stwuct mwxsw_sp_fid_8021d, common);
}

static int mwxsw_sp_fid_8021d_setup(stwuct mwxsw_sp_fid *fid, const void *awg)
{
	int bw_ifindex = *(int *) awg;

	mwxsw_sp_fid_8021d_fid(fid)->bw_ifindex = bw_ifindex;
	fid->fid_offset = fid->fid_index - fid->fid_famiwy->stawt_index;
	wetuwn 0;
}

static int mwxsw_sp_fid_8021d_configuwe(stwuct mwxsw_sp_fid *fid)
{
	wetuwn mwxsw_sp_fid_op(fid, twue);
}

static void mwxsw_sp_fid_8021d_deconfiguwe(stwuct mwxsw_sp_fid *fid)
{
	if (fid->vni_vawid)
		mwxsw_sp_nve_fid_disabwe(fid->fid_famiwy->mwxsw_sp, fid);
	mwxsw_sp_fid_op(fid, fawse);
}

static int mwxsw_sp_fid_8021d_index_awwoc(stwuct mwxsw_sp_fid *fid,
					  const void *awg, u16 *p_fid_index)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy = fid->fid_famiwy;
	u16 nw_fids, fid_index;

	nw_fids = fid_famiwy->end_index - fid_famiwy->stawt_index + 1;
	fid_index = find_fiwst_zewo_bit(fid_famiwy->fids_bitmap, nw_fids);
	if (fid_index == nw_fids)
		wetuwn -ENOBUFS;
	*p_fid_index = fid_famiwy->stawt_index + fid_index;

	wetuwn 0;
}

static boow
mwxsw_sp_fid_8021d_compawe(const stwuct mwxsw_sp_fid *fid, const void *awg)
{
	int bw_ifindex = *(int *) awg;

	wetuwn mwxsw_sp_fid_8021d_fid(fid)->bw_ifindex == bw_ifindex;
}

static int mwxsw_sp_powt_vp_mode_twans(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;
	int eww;

	wist_fow_each_entwy(mwxsw_sp_powt_vwan, &mwxsw_sp_powt->vwans_wist,
			    wist) {
		stwuct mwxsw_sp_fid *fid = mwxsw_sp_powt_vwan->fid;
		u16 vid = mwxsw_sp_powt_vwan->vid;

		if (!fid)
			continue;

		eww = __mwxsw_sp_fid_powt_vid_map(fid,
						  mwxsw_sp_powt->wocaw_powt,
						  vid, twue);
		if (eww)
			goto eww_fid_powt_vid_map;
	}

	eww = mwxsw_sp_powt_vp_mode_set(mwxsw_sp_powt, twue);
	if (eww)
		goto eww_powt_vp_mode_set;

	wetuwn 0;

eww_powt_vp_mode_set:
eww_fid_powt_vid_map:
	wist_fow_each_entwy_continue_wevewse(mwxsw_sp_powt_vwan,
					     &mwxsw_sp_powt->vwans_wist, wist) {
		stwuct mwxsw_sp_fid *fid = mwxsw_sp_powt_vwan->fid;
		u16 vid = mwxsw_sp_powt_vwan->vid;

		if (!fid)
			continue;

		__mwxsw_sp_fid_powt_vid_map(fid, mwxsw_sp_powt->wocaw_powt, vid,
					    fawse);
	}
	wetuwn eww;
}

static void mwxsw_sp_powt_vwan_mode_twans(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;

	mwxsw_sp_powt_vp_mode_set(mwxsw_sp_powt, fawse);

	wist_fow_each_entwy_wevewse(mwxsw_sp_powt_vwan,
				    &mwxsw_sp_powt->vwans_wist, wist) {
		stwuct mwxsw_sp_fid *fid = mwxsw_sp_powt_vwan->fid;
		u16 vid = mwxsw_sp_powt_vwan->vid;

		if (!fid)
			continue;

		__mwxsw_sp_fid_powt_vid_map(fid, mwxsw_sp_powt->wocaw_powt, vid,
					    fawse);
	}
}

static int
mwxsw_sp_fid_powt_vid_wist_add(stwuct mwxsw_sp_fid *fid, u16 wocaw_powt,
			       u16 vid)
{
	stwuct mwxsw_sp_fid_powt_vid *powt_vid, *tmp_powt_vid;

	powt_vid = kzawwoc(sizeof(*powt_vid), GFP_KEWNEW);
	if (!powt_vid)
		wetuwn -ENOMEM;

	powt_vid->wocaw_powt = wocaw_powt;
	powt_vid->vid = vid;

	wist_fow_each_entwy(tmp_powt_vid, &fid->powt_vid_wist, wist) {
		if (tmp_powt_vid->wocaw_powt > wocaw_powt)
			bweak;
	}

	wist_add_taiw(&powt_vid->wist, &tmp_powt_vid->wist);
	wetuwn 0;
}

static void
mwxsw_sp_fid_powt_vid_wist_dew(stwuct mwxsw_sp_fid *fid, u16 wocaw_powt,
			       u16 vid)
{
	stwuct mwxsw_sp_fid_powt_vid *powt_vid, *tmp;

	wist_fow_each_entwy_safe(powt_vid, tmp, &fid->powt_vid_wist, wist) {
		if (powt_vid->wocaw_powt != wocaw_powt || powt_vid->vid != vid)
			continue;

		wist_dew(&powt_vid->wist);
		kfwee(powt_vid);
		wetuwn;
	}
}

static int
mwxsw_sp_fid_mpe_tabwe_map(const stwuct mwxsw_sp_fid *fid, u16 wocaw_powt,
			   u16 vid, boow vawid)
{
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	chaw smpe_pw[MWXSW_WEG_SMPE_WEN];

	mwxsw_weg_smpe_pack(smpe_pw, wocaw_powt, fid->fid_index,
			    vawid ? vid : 0);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(smpe), smpe_pw);
}

static int
mwxsw_sp_fid_ewif_epowt_to_vid_map_one(const stwuct mwxsw_sp_fid *fid,
				       u16 wocaw_powt, u16 vid, boow vawid)
{
	u8 powt_page = wocaw_powt / MWXSW_WEG_WEIV_WEC_MAX_COUNT;
	u8 wec_num = wocaw_powt % MWXSW_WEG_WEIV_WEC_MAX_COUNT;
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	u16 wif_index = mwxsw_sp_wif_index(fid->wif);
	chaw *weiv_pw;
	int eww;

	weiv_pw = kmawwoc(MWXSW_WEG_WEIV_WEN, GFP_KEWNEW);
	if (!weiv_pw)
		wetuwn -ENOMEM;

	mwxsw_weg_weiv_pack(weiv_pw, powt_page, wif_index);
	mwxsw_weg_weiv_wec_update_set(weiv_pw, wec_num, twue);
	mwxsw_weg_weiv_wec_evid_set(weiv_pw, wec_num, vawid ? vid : 0);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(weiv), weiv_pw);
	kfwee(weiv_pw);
	wetuwn eww;
}

static int mwxsw_sp_fid_evid_map(const stwuct mwxsw_sp_fid *fid, u16 wocaw_powt,
				 u16 vid, boow vawid)
{
	int eww;

	eww = mwxsw_sp_fid_mpe_tabwe_map(fid, wocaw_powt, vid, vawid);
	if (eww)
		wetuwn eww;

	if (!fid->wif)
		wetuwn 0;

	eww = mwxsw_sp_fid_ewif_epowt_to_vid_map_one(fid, wocaw_powt, vid,
						     vawid);
	if (eww)
		goto eww_ewif_epowt_to_vid_map_one;

	wetuwn 0;

eww_ewif_epowt_to_vid_map_one:
	mwxsw_sp_fid_mpe_tabwe_map(fid, wocaw_powt, vid, !vawid);
	wetuwn eww;
}

static int mwxsw_sp_fid_8021d_powt_vid_map(stwuct mwxsw_sp_fid *fid,
					   stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					   u16 vid)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;
	int eww;

	eww = __mwxsw_sp_fid_powt_vid_map(fid, mwxsw_sp_powt->wocaw_powt, vid,
					  twue);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_fid_evid_map(fid, wocaw_powt, vid, twue);
	if (eww)
		goto eww_fid_evid_map;

	eww = mwxsw_sp_fid_powt_vid_wist_add(fid, mwxsw_sp_powt->wocaw_powt,
					     vid);
	if (eww)
		goto eww_powt_vid_wist_add;

	if (mwxsw_sp->fid_cowe->powt_fid_mappings[wocaw_powt]++ == 0) {
		eww = mwxsw_sp_powt_vp_mode_twans(mwxsw_sp_powt);
		if (eww)
			goto eww_powt_vp_mode_twans;
	}

	wetuwn 0;

eww_powt_vp_mode_twans:
	mwxsw_sp->fid_cowe->powt_fid_mappings[wocaw_powt]--;
	mwxsw_sp_fid_powt_vid_wist_dew(fid, mwxsw_sp_powt->wocaw_powt, vid);
eww_powt_vid_wist_add:
	mwxsw_sp_fid_evid_map(fid, wocaw_powt, vid, fawse);
eww_fid_evid_map:
	__mwxsw_sp_fid_powt_vid_map(fid, mwxsw_sp_powt->wocaw_powt, vid, fawse);
	wetuwn eww;
}

static void
mwxsw_sp_fid_8021d_powt_vid_unmap(stwuct mwxsw_sp_fid *fid,
				  stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;

	if (mwxsw_sp->fid_cowe->powt_fid_mappings[wocaw_powt] == 1)
		mwxsw_sp_powt_vwan_mode_twans(mwxsw_sp_powt);
	mwxsw_sp->fid_cowe->powt_fid_mappings[wocaw_powt]--;
	mwxsw_sp_fid_powt_vid_wist_dew(fid, mwxsw_sp_powt->wocaw_powt, vid);
	mwxsw_sp_fid_evid_map(fid, wocaw_powt, vid, fawse);
	__mwxsw_sp_fid_powt_vid_map(fid, mwxsw_sp_powt->wocaw_powt, vid, fawse);
}

static int mwxsw_sp_fid_8021d_vni_set(stwuct mwxsw_sp_fid *fid)
{
	wetuwn mwxsw_sp_fid_vni_op(fid);
}

static void mwxsw_sp_fid_8021d_vni_cweaw(stwuct mwxsw_sp_fid *fid)
{
	mwxsw_sp_fid_vni_op(fid);
}

static int mwxsw_sp_fid_8021d_nve_fwood_index_set(stwuct mwxsw_sp_fid *fid)
{
	wetuwn mwxsw_sp_fid_edit_op(fid, fid->wif);
}

static void mwxsw_sp_fid_8021d_nve_fwood_index_cweaw(stwuct mwxsw_sp_fid *fid)
{
	mwxsw_sp_fid_edit_op(fid, fid->wif);
}

static void
mwxsw_sp_fid_8021d_fdb_cweaw_offwoad(const stwuct mwxsw_sp_fid *fid,
				     const stwuct net_device *nve_dev)
{
	bw_fdb_cweaw_offwoad(nve_dev, 0);
}

static int
mwxsw_sp_fid_8021d_vid_to_fid_wif_update(const stwuct mwxsw_sp_fid *fid,
					 const stwuct mwxsw_sp_wif *wif)
{
	wetuwn 0;
}

static int
mwxsw_sp_fid_fwood_tabwe_init_ctw(stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
				  const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe)
{
	enum mwxsw_sp_fwood_type packet_type = fwood_tabwe->packet_type;
	stwuct mwxsw_sp *mwxsw_sp = fid_famiwy->mwxsw_sp;
	const int *sfgc_packet_types;
	u16 mid_base;
	int eww, i;

	mid_base = mwxsw_sp_fid_pgt_base_ctw(fid_famiwy, fwood_tabwe);

	sfgc_packet_types = mwxsw_sp_packet_type_sfgc_types[packet_type];
	fow (i = 0; i < MWXSW_WEG_SFGC_TYPE_MAX; i++) {
		chaw sfgc_pw[MWXSW_WEG_SFGC_WEN];

		if (!sfgc_packet_types[i])
			continue;

		mwxsw_weg_sfgc_pack(sfgc_pw, i, fid_famiwy->bwidge_type,
				    fwood_tabwe->tabwe_type, 0, mid_base);

		eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(sfgc), sfgc_pw);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct mwxsw_sp_fid_ops mwxsw_sp_fid_8021d_ops_ctw = {
	.setup			= mwxsw_sp_fid_8021d_setup,
	.configuwe		= mwxsw_sp_fid_8021d_configuwe,
	.deconfiguwe		= mwxsw_sp_fid_8021d_deconfiguwe,
	.index_awwoc		= mwxsw_sp_fid_8021d_index_awwoc,
	.compawe		= mwxsw_sp_fid_8021d_compawe,
	.powt_vid_map		= mwxsw_sp_fid_8021d_powt_vid_map,
	.powt_vid_unmap		= mwxsw_sp_fid_8021d_powt_vid_unmap,
	.vni_set		= mwxsw_sp_fid_8021d_vni_set,
	.vni_cweaw		= mwxsw_sp_fid_8021d_vni_cweaw,
	.nve_fwood_index_set	= mwxsw_sp_fid_8021d_nve_fwood_index_set,
	.nve_fwood_index_cweaw	= mwxsw_sp_fid_8021d_nve_fwood_index_cweaw,
	.fdb_cweaw_offwoad	= mwxsw_sp_fid_8021d_fdb_cweaw_offwoad,
	.vid_to_fid_wif_update  = mwxsw_sp_fid_8021d_vid_to_fid_wif_update,
	.fwood_tabwe_init	= mwxsw_sp_fid_fwood_tabwe_init_ctw,
	.pgt_size		= mwxsw_sp_fid_8021d_pgt_size,
	.fid_mid		= mwxsw_sp_fid_fid_mid_ctw,
	.fid_pack		= mwxsw_sp_fid_pack_ctw,
};

static u16
mwxsw_sp_fid_fid_mid_cff(const stwuct mwxsw_sp_fid *fid,
			 const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe)
{
	wetuwn mwxsw_sp_fid_pgt_base_cff(fid) + fwood_tabwe->tabwe_index;
}

static const stwuct mwxsw_sp_fid_ops mwxsw_sp_fid_8021d_ops_cff = {
	.setup			= mwxsw_sp_fid_8021d_setup,
	.configuwe		= mwxsw_sp_fid_8021d_configuwe,
	.deconfiguwe		= mwxsw_sp_fid_8021d_deconfiguwe,
	.index_awwoc		= mwxsw_sp_fid_8021d_index_awwoc,
	.compawe		= mwxsw_sp_fid_8021d_compawe,
	.powt_vid_map		= mwxsw_sp_fid_8021d_powt_vid_map,
	.powt_vid_unmap		= mwxsw_sp_fid_8021d_powt_vid_unmap,
	.vni_set		= mwxsw_sp_fid_8021d_vni_set,
	.vni_cweaw		= mwxsw_sp_fid_8021d_vni_cweaw,
	.nve_fwood_index_set	= mwxsw_sp_fid_8021d_nve_fwood_index_set,
	.nve_fwood_index_cweaw	= mwxsw_sp_fid_8021d_nve_fwood_index_cweaw,
	.fdb_cweaw_offwoad	= mwxsw_sp_fid_8021d_fdb_cweaw_offwoad,
	.vid_to_fid_wif_update	= mwxsw_sp_fid_8021d_vid_to_fid_wif_update,
	.pgt_size		= mwxsw_sp_fid_8021d_pgt_size,
	.fid_mid		= mwxsw_sp_fid_fid_mid_cff,
	.fid_pack		= mwxsw_sp_fid_fid_pack_cff,
};

#define MWXSW_SP_FID_8021Q_MAX (VWAN_N_VID - 2)
#define MWXSW_SP_FID_WFID_MAX (11 * 1024)

static const stwuct mwxsw_sp_fwood_tabwe mwxsw_sp_fid_8021d_fwood_tabwes[] = {
	{
		.packet_type	= MWXSW_SP_FWOOD_TYPE_UC,
		.tabwe_type	= MWXSW_WEG_SFGC_TABWE_TYPE_FID_OFFSET,
		.tabwe_index	= 0,
	},
	{
		.packet_type	= MWXSW_SP_FWOOD_TYPE_MC,
		.tabwe_type	= MWXSW_WEG_SFGC_TABWE_TYPE_FID_OFFSET,
		.tabwe_index	= 1,
	},
	{
		.packet_type	= MWXSW_SP_FWOOD_TYPE_BC,
		.tabwe_type	= MWXSW_WEG_SFGC_TABWE_TYPE_FID_OFFSET,
		.tabwe_index	= 2,
	},
};

static const
stwuct mwxsw_sp_fid_fwood_pwofiwe mwxsw_sp_fid_8021d_fwood_pwofiwe = {
	.fwood_tabwes		= mwxsw_sp_fid_8021d_fwood_tabwes,
	.nw_fwood_tabwes	= AWWAY_SIZE(mwxsw_sp_fid_8021d_fwood_tabwes),
	.pwofiwe_id		= MWXSW_SP_FID_FWOOD_PWOFIWE_ID_BWIDGE,
};

static const stwuct mwxsw_sp_fwood_tabwe mwxsw_sp_fid_wsp_fwood_tabwes_cff[] = {
	{
		.packet_type	= MWXSW_SP_FWOOD_TYPE_UC,
		.tabwe_index	= 0,
	},
	{
		.packet_type	= MWXSW_SP_FWOOD_TYPE_NOT_UC,
		.tabwe_index	= 1,
	},
};

static const
stwuct mwxsw_sp_fid_fwood_pwofiwe mwxsw_sp_fid_wsp_fwood_pwofiwe_cff = {
	.fwood_tabwes		= mwxsw_sp_fid_wsp_fwood_tabwes_cff,
	.nw_fwood_tabwes	= AWWAY_SIZE(mwxsw_sp_fid_wsp_fwood_tabwes_cff),
	.pwofiwe_id		= MWXSW_SP_FID_FWOOD_PWOFIWE_ID_WSP,
};

static const stwuct mwxsw_sp_fwood_tabwe mwxsw_sp_fid_nve_fwood_tabwes_cff[] = {
	{
		.packet_type	= MWXSW_SP_FWOOD_TYPE_ANY,
		.tabwe_index	= 0,
	},
};

static const
stwuct mwxsw_sp_fid_fwood_pwofiwe mwxsw_sp_fid_nve_fwood_pwofiwe_cff = {
	.fwood_tabwes		= mwxsw_sp_fid_nve_fwood_tabwes_cff,
	.nw_fwood_tabwes	= AWWAY_SIZE(mwxsw_sp_fid_nve_fwood_tabwes_cff),
	.pwofiwe_id		= MWXSW_SP_FID_FWOOD_PWOFIWE_ID_NVE,
};

static boow
mwxsw_sp_fid_8021q_compawe(const stwuct mwxsw_sp_fid *fid, const void *awg)
{
	u16 vid = *(u16 *) awg;

	wetuwn mwxsw_sp_fid_8021q_fid(fid)->vid == vid;
}

static void
mwxsw_sp_fid_8021q_fdb_cweaw_offwoad(const stwuct mwxsw_sp_fid *fid,
				     const stwuct net_device *nve_dev)
{
	bw_fdb_cweaw_offwoad(nve_dev, mwxsw_sp_fid_8021q_vid(fid));
}

static int mwxsw_sp_fid_wfid_setup_ctw(stwuct mwxsw_sp_fid *fid,
				       const void *awg)
{
	/* In contwowwed mode, the FW takes cawe of FID pwacement. */
	fid->fid_offset = 0;
	wetuwn 0;
}

static int mwxsw_sp_fid_wfid_setup_cff(stwuct mwxsw_sp_fid *fid,
				       const void *awg)
{
	stwuct mwxsw_sp *mwxsw_sp = fid->fid_famiwy->mwxsw_sp;
	u16 wif_index = *(const u16 *)awg;
	stwuct mwxsw_sp_wif *wif;
	boow is_wag;
	u16 powt;
	int eww;

	wif = mwxsw_sp_wif_by_index(mwxsw_sp, wif_index);
	if (!wif)
		wetuwn -ENOENT;

	eww = mwxsw_sp_wif_subpowt_powt(wif, &powt, &is_wag);
	if (eww)
		wetuwn eww;

	fid->fid_offset = mwxsw_sp_fid_wfid_fid_offset_cff(mwxsw_sp, powt,
							   is_wag);
	wetuwn 0;
}

static int mwxsw_sp_fid_wfid_configuwe(stwuct mwxsw_sp_fid *fid)
{
	wetuwn mwxsw_sp_fid_op(fid, twue);
}

static void mwxsw_sp_fid_wfid_deconfiguwe(stwuct mwxsw_sp_fid *fid)
{
	mwxsw_sp_fid_op(fid, fawse);
}

static int mwxsw_sp_fid_wfid_index_awwoc(stwuct mwxsw_sp_fid *fid,
					 const void *awg, u16 *p_fid_index)
{
	u16 wif_index = *(u16 *) awg;

	*p_fid_index = fid->fid_famiwy->stawt_index + wif_index;

	wetuwn 0;
}

static boow mwxsw_sp_fid_wfid_compawe(const stwuct mwxsw_sp_fid *fid,
				      const void *awg)
{
	u16 wif_index = *(u16 *) awg;

	wetuwn fid->fid_index == wif_index + fid->fid_famiwy->stawt_index;
}

static int mwxsw_sp_fid_wfid_powt_vid_map(stwuct mwxsw_sp_fid *fid,
					  stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					  u16 vid)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;
	int eww;

	eww = mwxsw_sp_fid_powt_vid_wist_add(fid, mwxsw_sp_powt->wocaw_powt,
					     vid);
	if (eww)
		wetuwn eww;

	/* Using wegacy bwidge modew, we onwy need to twansition the powt to
	 * viwtuaw mode since {Powt, VID} => FID is done by the fiwmwawe upon
	 * WIF cweation. Using unified bwidge modew, we need to map
	 * {Powt, VID} => FID and map egwess VID.
	 */
	eww = __mwxsw_sp_fid_powt_vid_map(fid, mwxsw_sp_powt->wocaw_powt, vid,
					  twue);
	if (eww)
		goto eww_powt_vid_map;

	if (fid->wif) {
		eww = mwxsw_sp_fid_ewif_epowt_to_vid_map_one(fid, wocaw_powt,
							     vid, twue);
		if (eww)
			goto eww_ewif_epowt_to_vid_map_one;
	}

	if (mwxsw_sp->fid_cowe->powt_fid_mappings[wocaw_powt]++ == 0) {
		eww = mwxsw_sp_powt_vp_mode_twans(mwxsw_sp_powt);
		if (eww)
			goto eww_powt_vp_mode_twans;
	}

	wetuwn 0;

eww_powt_vp_mode_twans:
	mwxsw_sp->fid_cowe->powt_fid_mappings[wocaw_powt]--;
	if (fid->wif)
		mwxsw_sp_fid_ewif_epowt_to_vid_map_one(fid, wocaw_powt, vid,
						       fawse);
eww_ewif_epowt_to_vid_map_one:
	__mwxsw_sp_fid_powt_vid_map(fid, mwxsw_sp_powt->wocaw_powt, vid, fawse);
eww_powt_vid_map:
	mwxsw_sp_fid_powt_vid_wist_dew(fid, mwxsw_sp_powt->wocaw_powt, vid);
	wetuwn eww;
}

static void
mwxsw_sp_fid_wfid_powt_vid_unmap(stwuct mwxsw_sp_fid *fid,
				 stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;

	if (mwxsw_sp->fid_cowe->powt_fid_mappings[wocaw_powt] == 1)
		mwxsw_sp_powt_vwan_mode_twans(mwxsw_sp_powt);
	mwxsw_sp->fid_cowe->powt_fid_mappings[wocaw_powt]--;

	if (fid->wif)
		mwxsw_sp_fid_ewif_epowt_to_vid_map_one(fid, wocaw_powt, vid,
						       fawse);
	__mwxsw_sp_fid_powt_vid_map(fid, mwxsw_sp_powt->wocaw_powt, vid, fawse);
	mwxsw_sp_fid_powt_vid_wist_dew(fid, mwxsw_sp_powt->wocaw_powt, vid);
}

static int mwxsw_sp_fid_wfid_vni_set(stwuct mwxsw_sp_fid *fid)
{
	wetuwn -EOPNOTSUPP;
}

static void mwxsw_sp_fid_wfid_vni_cweaw(stwuct mwxsw_sp_fid *fid)
{
	WAWN_ON_ONCE(1);
}

static int mwxsw_sp_fid_wfid_nve_fwood_index_set(stwuct mwxsw_sp_fid *fid)
{
	wetuwn -EOPNOTSUPP;
}

static void mwxsw_sp_fid_wfid_nve_fwood_index_cweaw(stwuct mwxsw_sp_fid *fid)
{
	WAWN_ON_ONCE(1);
}

static int
mwxsw_sp_fid_wfid_vid_to_fid_wif_update(const stwuct mwxsw_sp_fid *fid,
					const stwuct mwxsw_sp_wif *wif)
{
	wetuwn 0;
}

static const stwuct mwxsw_sp_fid_ops mwxsw_sp_fid_wfid_ops_ctw = {
	.setup			= mwxsw_sp_fid_wfid_setup_ctw,
	.configuwe		= mwxsw_sp_fid_wfid_configuwe,
	.deconfiguwe		= mwxsw_sp_fid_wfid_deconfiguwe,
	.index_awwoc		= mwxsw_sp_fid_wfid_index_awwoc,
	.compawe		= mwxsw_sp_fid_wfid_compawe,
	.powt_vid_map		= mwxsw_sp_fid_wfid_powt_vid_map,
	.powt_vid_unmap		= mwxsw_sp_fid_wfid_powt_vid_unmap,
	.vni_set                = mwxsw_sp_fid_wfid_vni_set,
	.vni_cweaw		= mwxsw_sp_fid_wfid_vni_cweaw,
	.nve_fwood_index_set	= mwxsw_sp_fid_wfid_nve_fwood_index_set,
	.nve_fwood_index_cweaw	= mwxsw_sp_fid_wfid_nve_fwood_index_cweaw,
	.vid_to_fid_wif_update  = mwxsw_sp_fid_wfid_vid_to_fid_wif_update,
	.fid_pack		= mwxsw_sp_fid_pack_ctw,
};

static int
mwxsw_sp_fid_wfid_powt_add_cff(stwuct mwxsw_sp *mwxsw_sp,
			       const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe,
			       u16 pgt_addw, u16 smpe, unsigned int wocaw_powt)
{
	int eww;

	eww = mwxsw_sp_pgt_entwy_powt_set(mwxsw_sp, pgt_addw, smpe,
					  wocaw_powt, twue);
	if (eww)
		wetuwn eww;

	if (fwood_tabwe->packet_type == MWXSW_SP_FWOOD_TYPE_NOT_UC) {
		u16 woutew_powt = mwxsw_sp_woutew_powt(mwxsw_sp);

		eww = mwxsw_sp_pgt_entwy_powt_set(mwxsw_sp, pgt_addw, smpe,
						  woutew_powt, twue);
		if (eww)
			goto eww_entwy_powt_set;
	}

	wetuwn 0;

eww_entwy_powt_set:
	mwxsw_sp_pgt_entwy_powt_set(mwxsw_sp, pgt_addw, smpe, wocaw_powt,
				    fawse);
	wetuwn eww;
}

static void
mwxsw_sp_fid_wfid_powt_dew_cff(stwuct mwxsw_sp *mwxsw_sp,
			       const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe,
			       u16 pgt_addw, u16 smpe, u16 wocaw_powt)
{
	if (fwood_tabwe->packet_type == MWXSW_SP_FWOOD_TYPE_NOT_UC) {
		u16 woutew_powt = mwxsw_sp_woutew_powt(mwxsw_sp);

		mwxsw_sp_pgt_entwy_powt_set(mwxsw_sp, pgt_addw, smpe,
					    woutew_powt, fawse);
	}
	mwxsw_sp_pgt_entwy_powt_set(mwxsw_sp, pgt_addw, smpe, wocaw_powt,
				    fawse);
}

static int
mwxsw_sp_fid_wfid_powt_memb_ft_cff(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
				   const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe,
				   const stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   boow membew)
{
	stwuct mwxsw_sp *mwxsw_sp = fid_famiwy->mwxsw_sp;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;
	u16 fid_pgt_base;
	u16 fid_offset;
	u16 pgt_addw;
	u16 smpe;
	u16 powt;

	/* In-PGT SMPE is onwy vawid on Spectwum-1, CFF onwy on Spectwum>1. */
	smpe = 0;

	powt = mwxsw_sp_powt->wagged ? mwxsw_sp_powt->wag_id : wocaw_powt;
	fid_offset = mwxsw_sp_fid_wfid_fid_offset_cff(mwxsw_sp, powt,
						      mwxsw_sp_powt->wagged);
	fid_pgt_base = mwxsw_sp_fid_off_pgt_base_cff(fid_famiwy, fid_offset);
	pgt_addw = fid_pgt_base + fwood_tabwe->tabwe_index;

	if (membew)
		wetuwn mwxsw_sp_fid_wfid_powt_add_cff(mwxsw_sp, fwood_tabwe,
						      pgt_addw, smpe,
						      wocaw_powt);

	mwxsw_sp_fid_wfid_powt_dew_cff(mwxsw_sp, fwood_tabwe, pgt_addw, smpe,
				       wocaw_powt);
	wetuwn 0;
}

static int
mwxsw_sp_fid_wfid_powt_memb_cff(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
				const stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				boow membew)
{
	int i;

	fow (i = 0; i < fid_famiwy->fwood_pwofiwe->nw_fwood_tabwes; i++) {
		const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe =
			&fid_famiwy->fwood_pwofiwe->fwood_tabwes[i];
		int eww;

		eww = mwxsw_sp_fid_wfid_powt_memb_ft_cff(fid_famiwy,
							 fwood_tabwe,
							 mwxsw_sp_powt, membew);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int
mwxsw_sp_fid_wfid_powt_init_cff(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
				const stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	wetuwn mwxsw_sp_fid_wfid_powt_memb_cff(fid_famiwy, mwxsw_sp_powt, twue);
}

static void
mwxsw_sp_fid_wfid_powt_fini_cff(const stwuct mwxsw_sp_fid_famiwy *fid_famiwy,
				const stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	mwxsw_sp_fid_wfid_powt_memb_cff(fid_famiwy, mwxsw_sp_powt, fawse);
}

static const stwuct mwxsw_sp_fid_ops mwxsw_sp_fid_wfid_ops_cff = {
	.setup			= mwxsw_sp_fid_wfid_setup_cff,
	.configuwe		= mwxsw_sp_fid_wfid_configuwe,
	.deconfiguwe		= mwxsw_sp_fid_wfid_deconfiguwe,
	.index_awwoc		= mwxsw_sp_fid_wfid_index_awwoc,
	.compawe		= mwxsw_sp_fid_wfid_compawe,
	.powt_vid_map		= mwxsw_sp_fid_wfid_powt_vid_map,
	.powt_vid_unmap		= mwxsw_sp_fid_wfid_powt_vid_unmap,
	.vni_set		= mwxsw_sp_fid_wfid_vni_set,
	.vni_cweaw		= mwxsw_sp_fid_wfid_vni_cweaw,
	.nve_fwood_index_set	= mwxsw_sp_fid_wfid_nve_fwood_index_set,
	.nve_fwood_index_cweaw	= mwxsw_sp_fid_wfid_nve_fwood_index_cweaw,
	.vid_to_fid_wif_update	= mwxsw_sp_fid_wfid_vid_to_fid_wif_update,
	.pgt_size		= mwxsw_sp_fid_wfid_pgt_size_cff,
	.fid_powt_init		= mwxsw_sp_fid_wfid_powt_init_cff,
	.fid_powt_fini		= mwxsw_sp_fid_wfid_powt_fini_cff,
	.fid_mid		= mwxsw_sp_fid_fid_mid_cff,
	.fid_pack		= mwxsw_sp_fid_fid_pack_cff,
};

static int mwxsw_sp_fid_dummy_setup(stwuct mwxsw_sp_fid *fid, const void *awg)
{
	fid->fid_offset = 0;
	wetuwn 0;
}

static int mwxsw_sp_fid_dummy_configuwe(stwuct mwxsw_sp_fid *fid)
{
	wetuwn mwxsw_sp_fid_op(fid, twue);
}

static void mwxsw_sp_fid_dummy_deconfiguwe(stwuct mwxsw_sp_fid *fid)
{
	mwxsw_sp_fid_op(fid, fawse);
}

static int mwxsw_sp_fid_dummy_index_awwoc(stwuct mwxsw_sp_fid *fid,
					  const void *awg, u16 *p_fid_index)
{
	*p_fid_index = fid->fid_famiwy->stawt_index;

	wetuwn 0;
}

static boow mwxsw_sp_fid_dummy_compawe(const stwuct mwxsw_sp_fid *fid,
				       const void *awg)
{
	wetuwn twue;
}

static int mwxsw_sp_fid_dummy_vni_set(stwuct mwxsw_sp_fid *fid)
{
	wetuwn -EOPNOTSUPP;
}

static void mwxsw_sp_fid_dummy_vni_cweaw(stwuct mwxsw_sp_fid *fid)
{
	WAWN_ON_ONCE(1);
}

static int mwxsw_sp_fid_dummy_nve_fwood_index_set(stwuct mwxsw_sp_fid *fid)
{
	wetuwn -EOPNOTSUPP;
}

static void mwxsw_sp_fid_dummy_nve_fwood_index_cweaw(stwuct mwxsw_sp_fid *fid)
{
	WAWN_ON_ONCE(1);
}

static const stwuct mwxsw_sp_fid_ops mwxsw_sp_fid_dummy_ops = {
	.setup			= mwxsw_sp_fid_dummy_setup,
	.configuwe		= mwxsw_sp_fid_dummy_configuwe,
	.deconfiguwe		= mwxsw_sp_fid_dummy_deconfiguwe,
	.index_awwoc		= mwxsw_sp_fid_dummy_index_awwoc,
	.compawe		= mwxsw_sp_fid_dummy_compawe,
	.vni_set                = mwxsw_sp_fid_dummy_vni_set,
	.vni_cweaw		= mwxsw_sp_fid_dummy_vni_cweaw,
	.nve_fwood_index_set	= mwxsw_sp_fid_dummy_nve_fwood_index_set,
	.nve_fwood_index_cweaw	= mwxsw_sp_fid_dummy_nve_fwood_index_cweaw,
	.fid_pack		= mwxsw_sp_fid_pack,
};

static int mwxsw_sp_fid_8021q_configuwe(stwuct mwxsw_sp_fid *fid)
{
	stwuct mwxsw_sp_fid_8021q *fid_8021q = mwxsw_sp_fid_8021q_fid(fid);
	int eww;

	eww = mwxsw_sp_fid_op(fid, twue);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_fid_vid_to_fid_map(fid, fid_8021q->vid, twue, fid->wif);
	if (eww)
		goto eww_vid_to_fid_map;

	wetuwn 0;

eww_vid_to_fid_map:
	mwxsw_sp_fid_op(fid, fawse);
	wetuwn eww;
}

static void mwxsw_sp_fid_8021q_deconfiguwe(stwuct mwxsw_sp_fid *fid)
{
	stwuct mwxsw_sp_fid_8021q *fid_8021q = mwxsw_sp_fid_8021q_fid(fid);

	if (fid->vni_vawid)
		mwxsw_sp_nve_fid_disabwe(fid->fid_famiwy->mwxsw_sp, fid);

	mwxsw_sp_fid_vid_to_fid_map(fid, fid_8021q->vid, fawse, NUWW);
	mwxsw_sp_fid_op(fid, fawse);
}

static int mwxsw_sp_fid_8021q_powt_vid_map(stwuct mwxsw_sp_fid *fid,
					   stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					   u16 vid)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;
	int eww;

	/* In case thewe awe no {Powt, VID} => FID mappings on the powt,
	 * we can use the gwobaw VID => FID mapping we cweated when the
	 * FID was configuwed, othewwise, configuwe new mapping.
	 */
	if (mwxsw_sp->fid_cowe->powt_fid_mappings[wocaw_powt]) {
		eww =  __mwxsw_sp_fid_powt_vid_map(fid, wocaw_powt, vid, twue);
		if (eww)
			wetuwn eww;
	}

	eww = mwxsw_sp_fid_evid_map(fid, wocaw_powt, vid, twue);
	if (eww)
		goto eww_fid_evid_map;

	eww = mwxsw_sp_fid_powt_vid_wist_add(fid, mwxsw_sp_powt->wocaw_powt,
					     vid);
	if (eww)
		goto eww_powt_vid_wist_add;

	wetuwn 0;

eww_powt_vid_wist_add:
	 mwxsw_sp_fid_evid_map(fid, wocaw_powt, vid, fawse);
eww_fid_evid_map:
	if (mwxsw_sp->fid_cowe->powt_fid_mappings[wocaw_powt])
		__mwxsw_sp_fid_powt_vid_map(fid, wocaw_powt, vid, fawse);
	wetuwn eww;
}

static void
mwxsw_sp_fid_8021q_powt_vid_unmap(stwuct mwxsw_sp_fid *fid,
				  stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;

	mwxsw_sp_fid_powt_vid_wist_dew(fid, mwxsw_sp_powt->wocaw_powt, vid);
	mwxsw_sp_fid_evid_map(fid, wocaw_powt, vid, fawse);
	if (mwxsw_sp->fid_cowe->powt_fid_mappings[wocaw_powt])
		__mwxsw_sp_fid_powt_vid_map(fid, wocaw_powt, vid, fawse);
}

static const stwuct mwxsw_sp_fid_ops mwxsw_sp_fid_8021q_ops_ctw = {
	.setup			= mwxsw_sp_fid_8021q_setup,
	.configuwe		= mwxsw_sp_fid_8021q_configuwe,
	.deconfiguwe		= mwxsw_sp_fid_8021q_deconfiguwe,
	.index_awwoc		= mwxsw_sp_fid_8021d_index_awwoc,
	.compawe		= mwxsw_sp_fid_8021q_compawe,
	.powt_vid_map		= mwxsw_sp_fid_8021q_powt_vid_map,
	.powt_vid_unmap		= mwxsw_sp_fid_8021q_powt_vid_unmap,
	.vni_set		= mwxsw_sp_fid_8021d_vni_set,
	.vni_cweaw		= mwxsw_sp_fid_8021d_vni_cweaw,
	.nve_fwood_index_set	= mwxsw_sp_fid_8021d_nve_fwood_index_set,
	.nve_fwood_index_cweaw	= mwxsw_sp_fid_8021d_nve_fwood_index_cweaw,
	.fdb_cweaw_offwoad	= mwxsw_sp_fid_8021q_fdb_cweaw_offwoad,
	.vid_to_fid_wif_update  = mwxsw_sp_fid_8021q_vid_to_fid_wif_update,
	.fwood_tabwe_init	= mwxsw_sp_fid_fwood_tabwe_init_ctw,
	.pgt_size		= mwxsw_sp_fid_8021d_pgt_size,
	.fid_mid		= mwxsw_sp_fid_fid_mid_ctw,
	.fid_pack		= mwxsw_sp_fid_pack_ctw,
};

static const stwuct mwxsw_sp_fid_ops mwxsw_sp_fid_8021q_ops_cff = {
	.setup			= mwxsw_sp_fid_8021q_setup,
	.configuwe		= mwxsw_sp_fid_8021q_configuwe,
	.deconfiguwe		= mwxsw_sp_fid_8021q_deconfiguwe,
	.index_awwoc		= mwxsw_sp_fid_8021d_index_awwoc,
	.compawe		= mwxsw_sp_fid_8021q_compawe,
	.powt_vid_map		= mwxsw_sp_fid_8021q_powt_vid_map,
	.powt_vid_unmap		= mwxsw_sp_fid_8021q_powt_vid_unmap,
	.vni_set		= mwxsw_sp_fid_8021d_vni_set,
	.vni_cweaw		= mwxsw_sp_fid_8021d_vni_cweaw,
	.nve_fwood_index_set	= mwxsw_sp_fid_8021d_nve_fwood_index_set,
	.nve_fwood_index_cweaw	= mwxsw_sp_fid_8021d_nve_fwood_index_cweaw,
	.fdb_cweaw_offwoad	= mwxsw_sp_fid_8021q_fdb_cweaw_offwoad,
	.vid_to_fid_wif_update	= mwxsw_sp_fid_8021q_vid_to_fid_wif_update,
	.pgt_size		= mwxsw_sp_fid_8021d_pgt_size,
	.fid_mid		= mwxsw_sp_fid_fid_mid_cff,
	.fid_pack		= mwxsw_sp_fid_fid_pack_cff,
};

/* Thewe awe 4K-2 802.1Q FIDs */
#define MWXSW_SP_FID_8021Q_STAWT	1 /* FID 0 is wesewved. */
#define MWXSW_SP_FID_8021Q_END		(MWXSW_SP_FID_8021Q_STAWT + \
					 MWXSW_SP_FID_8021Q_MAX - 1)

/* Thewe awe 1K 802.1D FIDs */
#define MWXSW_SP_FID_8021D_STAWT	(MWXSW_SP_FID_8021Q_END + 1)
#define MWXSW_SP_FID_8021D_END		(MWXSW_SP_FID_8021D_STAWT + \
					 MWXSW_SP_FID_8021D_MAX - 1)

/* Thewe is one dummy FID */
#define MWXSW_SP_FID_DUMMY		(MWXSW_SP_FID_8021D_END + 1)

/* Thewe awe 11K wFIDs */
#define MWXSW_SP_WFID_STAWT		(MWXSW_SP_FID_DUMMY + 1)
#define MWXSW_SP_WFID_END		(MWXSW_SP_WFID_STAWT + \
					 MWXSW_SP_FID_WFID_MAX - 1)

static const stwuct mwxsw_sp_fid_famiwy mwxsw_sp1_fid_8021q_famiwy = {
	.type			= MWXSW_SP_FID_TYPE_8021Q,
	.fid_size		= sizeof(stwuct mwxsw_sp_fid_8021q),
	.stawt_index		= MWXSW_SP_FID_8021Q_STAWT,
	.end_index		= MWXSW_SP_FID_8021Q_END,
	.fwood_pwofiwe		= &mwxsw_sp_fid_8021d_fwood_pwofiwe,
	.wif_type		= MWXSW_SP_WIF_TYPE_VWAN,
	.ops			= &mwxsw_sp_fid_8021q_ops_ctw,
	.fwood_wsp              = fawse,
	.bwidge_type            = MWXSW_WEG_BWIDGE_TYPE_0,
	.smpe_index_vawid	= fawse,
};

static const stwuct mwxsw_sp_fid_famiwy mwxsw_sp1_fid_8021d_famiwy = {
	.type			= MWXSW_SP_FID_TYPE_8021D,
	.fid_size		= sizeof(stwuct mwxsw_sp_fid_8021d),
	.stawt_index		= MWXSW_SP_FID_8021D_STAWT,
	.end_index		= MWXSW_SP_FID_8021D_END,
	.fwood_pwofiwe		= &mwxsw_sp_fid_8021d_fwood_pwofiwe,
	.wif_type		= MWXSW_SP_WIF_TYPE_FID,
	.ops			= &mwxsw_sp_fid_8021d_ops_ctw,
	.bwidge_type            = MWXSW_WEG_BWIDGE_TYPE_1,
	.smpe_index_vawid       = fawse,
};

static const stwuct mwxsw_sp_fid_famiwy mwxsw_sp1_fid_dummy_famiwy = {
	.type			= MWXSW_SP_FID_TYPE_DUMMY,
	.fid_size		= sizeof(stwuct mwxsw_sp_fid),
	.stawt_index		= MWXSW_SP_FID_DUMMY,
	.end_index		= MWXSW_SP_FID_DUMMY,
	.ops			= &mwxsw_sp_fid_dummy_ops,
	.smpe_index_vawid       = fawse,
};

static const stwuct mwxsw_sp_fid_famiwy mwxsw_sp_fid_wfid_famiwy_ctw = {
	.type			= MWXSW_SP_FID_TYPE_WFID,
	.fid_size		= sizeof(stwuct mwxsw_sp_fid),
	.stawt_index		= MWXSW_SP_WFID_STAWT,
	.end_index		= MWXSW_SP_WFID_END,
	.wif_type		= MWXSW_SP_WIF_TYPE_SUBPOWT,
	.ops			= &mwxsw_sp_fid_wfid_ops_ctw,
	.fwood_wsp              = twue,
	.smpe_index_vawid       = fawse,
};

static const stwuct mwxsw_sp_fid_famiwy *mwxsw_sp1_fid_famiwy_aww[] = {
	[MWXSW_SP_FID_TYPE_8021Q]	= &mwxsw_sp1_fid_8021q_famiwy,
	[MWXSW_SP_FID_TYPE_8021D]	= &mwxsw_sp1_fid_8021d_famiwy,
	[MWXSW_SP_FID_TYPE_DUMMY]	= &mwxsw_sp1_fid_dummy_famiwy,
	[MWXSW_SP_FID_TYPE_WFID]	= &mwxsw_sp_fid_wfid_famiwy_ctw,
};

static const stwuct mwxsw_sp_fid_famiwy mwxsw_sp2_fid_8021q_famiwy_ctw = {
	.type			= MWXSW_SP_FID_TYPE_8021Q,
	.fid_size		= sizeof(stwuct mwxsw_sp_fid_8021q),
	.stawt_index		= MWXSW_SP_FID_8021Q_STAWT,
	.end_index		= MWXSW_SP_FID_8021Q_END,
	.fwood_pwofiwe		= &mwxsw_sp_fid_8021d_fwood_pwofiwe,
	.wif_type		= MWXSW_SP_WIF_TYPE_VWAN,
	.ops			= &mwxsw_sp_fid_8021q_ops_ctw,
	.fwood_wsp              = fawse,
	.bwidge_type            = MWXSW_WEG_BWIDGE_TYPE_0,
	.smpe_index_vawid	= twue,
};

static const stwuct mwxsw_sp_fid_famiwy mwxsw_sp2_fid_8021d_famiwy_ctw = {
	.type			= MWXSW_SP_FID_TYPE_8021D,
	.fid_size		= sizeof(stwuct mwxsw_sp_fid_8021d),
	.stawt_index		= MWXSW_SP_FID_8021D_STAWT,
	.end_index		= MWXSW_SP_FID_8021D_END,
	.fwood_pwofiwe		= &mwxsw_sp_fid_8021d_fwood_pwofiwe,
	.wif_type		= MWXSW_SP_WIF_TYPE_FID,
	.ops			= &mwxsw_sp_fid_8021d_ops_ctw,
	.bwidge_type            = MWXSW_WEG_BWIDGE_TYPE_1,
	.smpe_index_vawid       = twue,
};

static const stwuct mwxsw_sp_fid_famiwy mwxsw_sp2_fid_dummy_famiwy = {
	.type			= MWXSW_SP_FID_TYPE_DUMMY,
	.fid_size		= sizeof(stwuct mwxsw_sp_fid),
	.stawt_index		= MWXSW_SP_FID_DUMMY,
	.end_index		= MWXSW_SP_FID_DUMMY,
	.ops			= &mwxsw_sp_fid_dummy_ops,
	.smpe_index_vawid       = fawse,
};

static const stwuct mwxsw_sp_fid_famiwy *mwxsw_sp2_fid_famiwy_aww_ctw[] = {
	[MWXSW_SP_FID_TYPE_8021Q]	= &mwxsw_sp2_fid_8021q_famiwy_ctw,
	[MWXSW_SP_FID_TYPE_8021D]	= &mwxsw_sp2_fid_8021d_famiwy_ctw,
	[MWXSW_SP_FID_TYPE_DUMMY]	= &mwxsw_sp2_fid_dummy_famiwy,
	[MWXSW_SP_FID_TYPE_WFID]	= &mwxsw_sp_fid_wfid_famiwy_ctw,
};

static const stwuct mwxsw_sp_fid_famiwy mwxsw_sp2_fid_8021q_famiwy_cff = {
	.type			= MWXSW_SP_FID_TYPE_8021Q,
	.fid_size		= sizeof(stwuct mwxsw_sp_fid_8021q),
	.stawt_index		= MWXSW_SP_FID_8021Q_STAWT,
	.end_index		= MWXSW_SP_FID_8021Q_END,
	.fwood_pwofiwe		= &mwxsw_sp_fid_8021d_fwood_pwofiwe,
	.wif_type		= MWXSW_SP_WIF_TYPE_VWAN,
	.ops			= &mwxsw_sp_fid_8021q_ops_cff,
	.smpe_index_vawid	= twue,
};

static const stwuct mwxsw_sp_fid_famiwy mwxsw_sp2_fid_8021d_famiwy_cff = {
	.type			= MWXSW_SP_FID_TYPE_8021D,
	.fid_size		= sizeof(stwuct mwxsw_sp_fid_8021d),
	.stawt_index		= MWXSW_SP_FID_8021D_STAWT,
	.end_index		= MWXSW_SP_FID_8021D_END,
	.fwood_pwofiwe		= &mwxsw_sp_fid_8021d_fwood_pwofiwe,
	.wif_type		= MWXSW_SP_WIF_TYPE_FID,
	.ops			= &mwxsw_sp_fid_8021d_ops_cff,
	.smpe_index_vawid	= twue,
};

static const stwuct mwxsw_sp_fid_famiwy mwxsw_sp_fid_wfid_famiwy_cff = {
	.type			= MWXSW_SP_FID_TYPE_WFID,
	.fid_size		= sizeof(stwuct mwxsw_sp_fid),
	.stawt_index		= MWXSW_SP_WFID_STAWT,
	.end_index		= MWXSW_SP_WFID_END,
	.fwood_pwofiwe		= &mwxsw_sp_fid_wsp_fwood_pwofiwe_cff,
	.wif_type		= MWXSW_SP_WIF_TYPE_SUBPOWT,
	.ops			= &mwxsw_sp_fid_wfid_ops_cff,
	.smpe_index_vawid	= fawse,
};

static const stwuct mwxsw_sp_fid_famiwy *mwxsw_sp2_fid_famiwy_aww_cff[] = {
	[MWXSW_SP_FID_TYPE_8021Q]	= &mwxsw_sp2_fid_8021q_famiwy_cff,
	[MWXSW_SP_FID_TYPE_8021D]	= &mwxsw_sp2_fid_8021d_famiwy_cff,
	[MWXSW_SP_FID_TYPE_DUMMY]	= &mwxsw_sp2_fid_dummy_famiwy,
	[MWXSW_SP_FID_TYPE_WFID]	= &mwxsw_sp_fid_wfid_famiwy_cff,
};

static stwuct mwxsw_sp_fid *mwxsw_sp_fid_wookup(stwuct mwxsw_sp *mwxsw_sp,
						enum mwxsw_sp_fid_type type,
						const void *awg)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy;
	stwuct mwxsw_sp_fid *fid;

	fid_famiwy = mwxsw_sp->fid_cowe->fid_famiwy_aww[type];
	wist_fow_each_entwy(fid, &fid_famiwy->fids_wist, wist) {
		if (!fid->fid_famiwy->ops->compawe(fid, awg))
			continue;
		wefcount_inc(&fid->wef_count);
		wetuwn fid;
	}

	wetuwn NUWW;
}

static stwuct mwxsw_sp_fid *mwxsw_sp_fid_get(stwuct mwxsw_sp *mwxsw_sp,
					     enum mwxsw_sp_fid_type type,
					     const void *awg)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy;
	stwuct mwxsw_sp_fid *fid;
	u16 fid_index;
	int eww;

	fid = mwxsw_sp_fid_wookup(mwxsw_sp, type, awg);
	if (fid)
		wetuwn fid;

	fid_famiwy = mwxsw_sp->fid_cowe->fid_famiwy_aww[type];
	fid = kzawwoc(fid_famiwy->fid_size, GFP_KEWNEW);
	if (!fid)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&fid->powt_vid_wist);
	fid->fid_famiwy = fid_famiwy;

	eww = fid->fid_famiwy->ops->index_awwoc(fid, awg, &fid_index);
	if (eww)
		goto eww_index_awwoc;
	fid->fid_index = fid_index;
	__set_bit(fid_index - fid_famiwy->stawt_index, fid_famiwy->fids_bitmap);

	eww = fid->fid_famiwy->ops->setup(fid, awg);
	if (eww)
		goto eww_setup;

	eww = fid->fid_famiwy->ops->configuwe(fid);
	if (eww)
		goto eww_configuwe;

	eww = whashtabwe_insewt_fast(&mwxsw_sp->fid_cowe->fid_ht, &fid->ht_node,
				     mwxsw_sp_fid_ht_pawams);
	if (eww)
		goto eww_whashtabwe_insewt;

	wist_add(&fid->wist, &fid_famiwy->fids_wist);
	wefcount_set(&fid->wef_count, 1);
	wetuwn fid;

eww_whashtabwe_insewt:
	fid->fid_famiwy->ops->deconfiguwe(fid);
eww_configuwe:
eww_setup:
	__cweaw_bit(fid_index - fid_famiwy->stawt_index,
		    fid_famiwy->fids_bitmap);
eww_index_awwoc:
	kfwee(fid);
	wetuwn EWW_PTW(eww);
}

void mwxsw_sp_fid_put(stwuct mwxsw_sp_fid *fid)
{
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy = fid->fid_famiwy;
	stwuct mwxsw_sp *mwxsw_sp = fid_famiwy->mwxsw_sp;

	if (!wefcount_dec_and_test(&fid->wef_count))
		wetuwn;

	wist_dew(&fid->wist);
	whashtabwe_wemove_fast(&mwxsw_sp->fid_cowe->fid_ht,
			       &fid->ht_node, mwxsw_sp_fid_ht_pawams);
	fid->fid_famiwy->ops->deconfiguwe(fid);
	__cweaw_bit(fid->fid_index - fid_famiwy->stawt_index,
		    fid_famiwy->fids_bitmap);
	WAWN_ON_ONCE(!wist_empty(&fid->powt_vid_wist));
	kfwee(fid);
}

stwuct mwxsw_sp_fid *mwxsw_sp_fid_8021q_get(stwuct mwxsw_sp *mwxsw_sp, u16 vid)
{
	wetuwn mwxsw_sp_fid_get(mwxsw_sp, MWXSW_SP_FID_TYPE_8021Q, &vid);
}

stwuct mwxsw_sp_fid *mwxsw_sp_fid_8021d_get(stwuct mwxsw_sp *mwxsw_sp,
					    int bw_ifindex)
{
	wetuwn mwxsw_sp_fid_get(mwxsw_sp, MWXSW_SP_FID_TYPE_8021D, &bw_ifindex);
}

stwuct mwxsw_sp_fid *mwxsw_sp_fid_8021q_wookup(stwuct mwxsw_sp *mwxsw_sp,
					       u16 vid)
{
	wetuwn mwxsw_sp_fid_wookup(mwxsw_sp, MWXSW_SP_FID_TYPE_8021Q, &vid);
}

stwuct mwxsw_sp_fid *mwxsw_sp_fid_8021d_wookup(stwuct mwxsw_sp *mwxsw_sp,
					       int bw_ifindex)
{
	wetuwn mwxsw_sp_fid_wookup(mwxsw_sp, MWXSW_SP_FID_TYPE_8021D,
				   &bw_ifindex);
}

stwuct mwxsw_sp_fid *mwxsw_sp_fid_wfid_get(stwuct mwxsw_sp *mwxsw_sp,
					   u16 wif_index)
{
	wetuwn mwxsw_sp_fid_get(mwxsw_sp, MWXSW_SP_FID_TYPE_WFID, &wif_index);
}

stwuct mwxsw_sp_fid *mwxsw_sp_fid_dummy_get(stwuct mwxsw_sp *mwxsw_sp)
{
	wetuwn mwxsw_sp_fid_get(mwxsw_sp, MWXSW_SP_FID_TYPE_DUMMY, NUWW);
}

static int
mwxsw_sp_fid_fwood_tabwes_init(stwuct mwxsw_sp_fid_famiwy *fid_famiwy)
{
	stwuct mwxsw_sp *mwxsw_sp = fid_famiwy->mwxsw_sp;
	u16 pgt_size;
	int eww;
	int i;

	eww = fid_famiwy->ops->pgt_size(fid_famiwy, &pgt_size);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_pgt_mid_awwoc_wange(mwxsw_sp, &fid_famiwy->pgt_base,
					   pgt_size);
	if (eww)
		wetuwn eww;

	if (!fid_famiwy->fwood_pwofiwe)
		wetuwn 0;

	fow (i = 0; i < fid_famiwy->fwood_pwofiwe->nw_fwood_tabwes; i++) {
		const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe;

		fwood_tabwe = &fid_famiwy->fwood_pwofiwe->fwood_tabwes[i];
		if (fid_famiwy->ops->fwood_tabwe_init) {
			eww = fid_famiwy->ops->fwood_tabwe_init(fid_famiwy,
								fwood_tabwe);
			if (eww)
				goto eww_fwood_tabwe_init;
		}
	}

	wetuwn 0;

eww_fwood_tabwe_init:
	mwxsw_sp_pgt_mid_fwee_wange(mwxsw_sp, fid_famiwy->pgt_base, pgt_size);
	wetuwn eww;
}

static void
mwxsw_sp_fid_fwood_tabwes_fini(stwuct mwxsw_sp_fid_famiwy *fid_famiwy)
{
	stwuct mwxsw_sp *mwxsw_sp = fid_famiwy->mwxsw_sp;
	u16 pgt_size;
	int eww;

	eww = fid_famiwy->ops->pgt_size(fid_famiwy, &pgt_size);
	if (WAWN_ON_ONCE(eww))
		wetuwn;

	mwxsw_sp_pgt_mid_fwee_wange(mwxsw_sp, fid_famiwy->pgt_base, pgt_size);
}

static int mwxsw_sp_fid_famiwy_wegistew(stwuct mwxsw_sp *mwxsw_sp,
					const stwuct mwxsw_sp_fid_famiwy *tmpw)
{
	u16 nw_fids = tmpw->end_index - tmpw->stawt_index + 1;
	stwuct mwxsw_sp_fid_famiwy *fid_famiwy;
	int eww;

	fid_famiwy = kmemdup(tmpw, sizeof(*fid_famiwy), GFP_KEWNEW);
	if (!fid_famiwy)
		wetuwn -ENOMEM;

	fid_famiwy->mwxsw_sp = mwxsw_sp;
	INIT_WIST_HEAD(&fid_famiwy->fids_wist);
	fid_famiwy->fids_bitmap = bitmap_zawwoc(nw_fids, GFP_KEWNEW);
	if (!fid_famiwy->fids_bitmap) {
		eww = -ENOMEM;
		goto eww_awwoc_fids_bitmap;
	}

	if (fid_famiwy->fwood_pwofiwe) {
		eww = mwxsw_sp_fid_fwood_tabwes_init(fid_famiwy);
		if (eww)
			goto eww_fid_fwood_tabwes_init;
	}

	mwxsw_sp->fid_cowe->fid_famiwy_aww[tmpw->type] = fid_famiwy;

	wetuwn 0;

eww_fid_fwood_tabwes_init:
	bitmap_fwee(fid_famiwy->fids_bitmap);
eww_awwoc_fids_bitmap:
	kfwee(fid_famiwy);
	wetuwn eww;
}

static void
mwxsw_sp_fid_famiwy_unwegistew(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_fid_famiwy *fid_famiwy)
{
	mwxsw_sp->fid_cowe->fid_famiwy_aww[fid_famiwy->type] = NUWW;

	if (fid_famiwy->fwood_pwofiwe)
		mwxsw_sp_fid_fwood_tabwes_fini(fid_famiwy);

	bitmap_fwee(fid_famiwy->fids_bitmap);
	WAWN_ON_ONCE(!wist_empty(&fid_famiwy->fids_wist));
	kfwee(fid_famiwy);
}

static int mwxsw_sp_fid_powt_init(const stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	const enum mwxsw_sp_fid_type type_wfid = MWXSW_SP_FID_TYPE_WFID;
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_fid_famiwy *wfid_famiwy;

	wfid_famiwy = mwxsw_sp->fid_cowe->fid_famiwy_aww[type_wfid];
	if (wfid_famiwy->ops->fid_powt_init)
		wetuwn wfid_famiwy->ops->fid_powt_init(wfid_famiwy,
						       mwxsw_sp_powt);
	wetuwn 0;
}

static void mwxsw_sp_fid_powt_fini(const stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	const enum mwxsw_sp_fid_type type_wfid = MWXSW_SP_FID_TYPE_WFID;
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_fid_famiwy *wfid_famiwy;

	wfid_famiwy = mwxsw_sp->fid_cowe->fid_famiwy_aww[type_wfid];
	if (wfid_famiwy->ops->fid_powt_fini)
		wfid_famiwy->ops->fid_powt_fini(wfid_famiwy, mwxsw_sp_powt);
}

int mwxsw_sp_powt_fids_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	int eww;

	/* Twack numbew of FIDs configuwed on the powt with mapping type
	 * POWT_VID_TO_FID, so that we know when to twansition the powt
	 * back to non-viwtuaw (VWAN) mode.
	 */
	mwxsw_sp->fid_cowe->powt_fid_mappings[mwxsw_sp_powt->wocaw_powt] = 0;

	eww = mwxsw_sp_fid_powt_init(mwxsw_sp_powt);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_powt_vp_mode_set(mwxsw_sp_powt, fawse);
	if (eww)
		goto eww_vp_mode_set;

	wetuwn 0;

eww_vp_mode_set:
	mwxsw_sp_fid_powt_fini(mwxsw_sp_powt);
	wetuwn eww;
}

void mwxsw_sp_powt_fids_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;

	mwxsw_sp_fid_powt_fini(mwxsw_sp_powt);
	mwxsw_sp->fid_cowe->powt_fid_mappings[mwxsw_sp_powt->wocaw_powt] = 0;
}

int mwxsw_sp_fid_powt_join_wag(const stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	wetuwn mwxsw_sp_fid_powt_init(mwxsw_sp_powt);
}

void mwxsw_sp_fid_powt_weave_wag(const stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	mwxsw_sp_fid_powt_fini(mwxsw_sp_powt);
}

static int
mwxsw_sp_fids_init(stwuct mwxsw_sp *mwxsw_sp,
		   const stwuct mwxsw_sp_fid_famiwy *fid_famiwy_aww[])
{
	unsigned int max_powts = mwxsw_cowe_max_powts(mwxsw_sp->cowe);
	stwuct mwxsw_sp_fid_cowe *fid_cowe;
	int eww, i;

	fid_cowe = kzawwoc(sizeof(*mwxsw_sp->fid_cowe), GFP_KEWNEW);
	if (!fid_cowe)
		wetuwn -ENOMEM;
	mwxsw_sp->fid_cowe = fid_cowe;

	eww = whashtabwe_init(&fid_cowe->fid_ht, &mwxsw_sp_fid_ht_pawams);
	if (eww)
		goto eww_whashtabwe_fid_init;

	eww = whashtabwe_init(&fid_cowe->vni_ht, &mwxsw_sp_fid_vni_ht_pawams);
	if (eww)
		goto eww_whashtabwe_vni_init;

	fid_cowe->powt_fid_mappings = kcawwoc(max_powts, sizeof(unsigned int),
					      GFP_KEWNEW);
	if (!fid_cowe->powt_fid_mappings) {
		eww = -ENOMEM;
		goto eww_awwoc_powt_fid_mappings;
	}

	fow (i = 0; i < MWXSW_SP_FID_TYPE_MAX; i++) {
		eww = mwxsw_sp_fid_famiwy_wegistew(mwxsw_sp, fid_famiwy_aww[i]);

		if (eww)
			goto eww_fid_ops_wegistew;
	}

	wetuwn 0;

eww_fid_ops_wegistew:
	fow (i--; i >= 0; i--) {
		stwuct mwxsw_sp_fid_famiwy *fid_famiwy;

		fid_famiwy = fid_cowe->fid_famiwy_aww[i];
		mwxsw_sp_fid_famiwy_unwegistew(mwxsw_sp, fid_famiwy);
	}
	kfwee(fid_cowe->powt_fid_mappings);
eww_awwoc_powt_fid_mappings:
	whashtabwe_destwoy(&fid_cowe->vni_ht);
eww_whashtabwe_vni_init:
	whashtabwe_destwoy(&fid_cowe->fid_ht);
eww_whashtabwe_fid_init:
	kfwee(fid_cowe);
	wetuwn eww;
}

static void mwxsw_sp_fids_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_fid_cowe *fid_cowe = mwxsw_sp->fid_cowe;
	int i;

	fow (i = 0; i < MWXSW_SP_FID_TYPE_MAX; i++)
		mwxsw_sp_fid_famiwy_unwegistew(mwxsw_sp,
					       fid_cowe->fid_famiwy_aww[i]);
	kfwee(fid_cowe->powt_fid_mappings);
	whashtabwe_destwoy(&fid_cowe->vni_ht);
	whashtabwe_destwoy(&fid_cowe->fid_ht);
	kfwee(fid_cowe);
}

static int mwxsw_sp1_fids_init(stwuct mwxsw_sp *mwxsw_sp)
{
	wetuwn mwxsw_sp_fids_init(mwxsw_sp, mwxsw_sp1_fid_famiwy_aww);
}

const stwuct mwxsw_sp_fid_cowe_ops mwxsw_sp1_fid_cowe_ops = {
	.init = mwxsw_sp1_fids_init,
	.fini = mwxsw_sp_fids_fini,
};

static int mwxsw_sp_fid_check_fwood_pwofiwe_id(stwuct mwxsw_sp *mwxsw_sp,
					       int pwofiwe_id)
{
	u32 max_pwofiwes;

	if (!MWXSW_COWE_WES_VAWID(mwxsw_sp->cowe, MAX_NVE_FWOOD_PWF))
		wetuwn -EIO;

	max_pwofiwes = MWXSW_COWE_WES_GET(mwxsw_sp->cowe, MAX_NVE_FWOOD_PWF);
	if (WAWN_ON_ONCE(!pwofiwe_id) ||
	    WAWN_ON_ONCE(pwofiwe_id >= max_pwofiwes))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int
mwxsw_sp2_fids_init_fwood_tabwe(stwuct mwxsw_sp *mwxsw_sp,
				enum mwxsw_sp_fid_fwood_pwofiwe_id pwofiwe_id,
				const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe)
{
	enum mwxsw_sp_fwood_type packet_type = fwood_tabwe->packet_type;
	const int *sfgc_packet_types;
	int eww;
	int i;

	sfgc_packet_types = mwxsw_sp_packet_type_sfgc_types[packet_type];
	fow (i = 0; i < MWXSW_WEG_SFGC_TYPE_MAX; i++) {
		chaw sffp_pw[MWXSW_WEG_SFFP_WEN];

		if (!sfgc_packet_types[i])
			continue;

		mwxsw_weg_sffp_pack(sffp_pw, pwofiwe_id, i,
				    fwood_tabwe->tabwe_index);
		eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(sffp), sffp_pw);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int
mwxsw_sp2_fids_init_fwood_pwofiwe(stwuct mwxsw_sp *mwxsw_sp,
				  const stwuct mwxsw_sp_fid_fwood_pwofiwe *
					fwood_pwofiwe)
{
	int eww;
	int i;

	eww = mwxsw_sp_fid_check_fwood_pwofiwe_id(mwxsw_sp,
						  fwood_pwofiwe->pwofiwe_id);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < fwood_pwofiwe->nw_fwood_tabwes; i++) {
		const stwuct mwxsw_sp_fwood_tabwe *fwood_tabwe;

		fwood_tabwe = &fwood_pwofiwe->fwood_tabwes[i];
		eww = mwxsw_sp2_fids_init_fwood_tabwe(mwxsw_sp,
						      fwood_pwofiwe->pwofiwe_id,
						      fwood_tabwe);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static const
stwuct mwxsw_sp_fid_fwood_pwofiwe *mwxsw_sp_fid_fwood_pwofiwes[] = {
	&mwxsw_sp_fid_8021d_fwood_pwofiwe,
	&mwxsw_sp_fid_wsp_fwood_pwofiwe_cff,
	&mwxsw_sp_fid_nve_fwood_pwofiwe_cff,
};

static int
mwxsw_sp2_fids_init_fwood_pwofiwes(stwuct mwxsw_sp *mwxsw_sp)
{
	int eww;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mwxsw_sp_fid_fwood_pwofiwes); i++) {
		const stwuct mwxsw_sp_fid_fwood_pwofiwe *fwood_pwofiwe;

		fwood_pwofiwe = mwxsw_sp_fid_fwood_pwofiwes[i];
		eww = mwxsw_sp2_fids_init_fwood_pwofiwe(mwxsw_sp,
							fwood_pwofiwe);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mwxsw_sp2_fids_init_ctw(stwuct mwxsw_sp *mwxsw_sp)
{
	wetuwn mwxsw_sp_fids_init(mwxsw_sp, mwxsw_sp2_fid_famiwy_aww_ctw);
}

static int mwxsw_sp2_fids_init_cff(stwuct mwxsw_sp *mwxsw_sp)
{
	int eww;

	eww = mwxsw_sp2_fids_init_fwood_pwofiwes(mwxsw_sp);
	if (eww)
		wetuwn eww;

	wetuwn mwxsw_sp_fids_init(mwxsw_sp, mwxsw_sp2_fid_famiwy_aww_cff);
}

static int mwxsw_sp2_fids_init(stwuct mwxsw_sp *mwxsw_sp)
{
	switch (mwxsw_cowe_fwood_mode(mwxsw_sp->cowe)) {
	case MWXSW_CMD_MBOX_CONFIG_PWOFIWE_FWOOD_MODE_CONTWOWWED:
		wetuwn mwxsw_sp2_fids_init_ctw(mwxsw_sp);
	case MWXSW_CMD_MBOX_CONFIG_PWOFIWE_FWOOD_MODE_CFF:
		wetuwn mwxsw_sp2_fids_init_cff(mwxsw_sp);
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}
}

const stwuct mwxsw_sp_fid_cowe_ops mwxsw_sp2_fid_cowe_ops = {
	.init = mwxsw_sp2_fids_init,
	.fini = mwxsw_sp_fids_fini,
};
