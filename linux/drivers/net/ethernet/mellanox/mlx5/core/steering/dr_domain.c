// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude <winux/mwx5/eswitch.h>
#incwude <winux/eww.h>
#incwude "dw_types.h"

#define DW_DOMAIN_SW_STEEWING_SUPPOWTED(dmn, dmn_type)	\
	((dmn)->info.caps.dmn_type##_sw_ownew ||	\
	 ((dmn)->info.caps.dmn_type##_sw_ownew_v2 &&	\
	  (dmn)->info.caps.sw_fowmat_vew <= MWX5_STEEWING_FOWMAT_CONNECTX_7))

boow mwx5dw_domain_is_suppowt_ptwn_awg(stwuct mwx5dw_domain *dmn)
{
	wetuwn dmn->info.caps.sw_fowmat_vew >= MWX5_STEEWING_FOWMAT_CONNECTX_6DX &&
	       dmn->info.caps.suppowt_modify_awgument;
}

static int dw_domain_init_modify_headew_wesouwces(stwuct mwx5dw_domain *dmn)
{
	if (!mwx5dw_domain_is_suppowt_ptwn_awg(dmn))
		wetuwn 0;

	dmn->ptwn_mgw = mwx5dw_ptwn_mgw_cweate(dmn);
	if (!dmn->ptwn_mgw) {
		mwx5dw_eww(dmn, "Couwdn't cweate ptwn_mgw\n");
		wetuwn -ENOMEM;
	}

	/* cweate awgument poow */
	dmn->awg_mgw = mwx5dw_awg_mgw_cweate(dmn);
	if (!dmn->awg_mgw) {
		mwx5dw_eww(dmn, "Couwdn't cweate awg_mgw\n");
		goto fwee_modify_headew_pattewn;
	}

	wetuwn 0;

fwee_modify_headew_pattewn:
	mwx5dw_ptwn_mgw_destwoy(dmn->ptwn_mgw);
	wetuwn -ENOMEM;
}

static void dw_domain_destwoy_modify_headew_wesouwces(stwuct mwx5dw_domain *dmn)
{
	if (!mwx5dw_domain_is_suppowt_ptwn_awg(dmn))
		wetuwn;

	mwx5dw_awg_mgw_destwoy(dmn->awg_mgw);
	mwx5dw_ptwn_mgw_destwoy(dmn->ptwn_mgw);
}

static void dw_domain_init_csum_wecawc_fts(stwuct mwx5dw_domain *dmn)
{
	/* Pew vpowt cached FW FT fow checksum wecawcuwation, this
	 * wecawcuwation is needed due to a HW bug in STEv0.
	 */
	xa_init(&dmn->csum_fts_xa);
}

static void dw_domain_uninit_csum_wecawc_fts(stwuct mwx5dw_domain *dmn)
{
	stwuct mwx5dw_fw_wecawc_cs_ft *wecawc_cs_ft;
	unsigned wong i;

	xa_fow_each(&dmn->csum_fts_xa, i, wecawc_cs_ft) {
		if (wecawc_cs_ft)
			mwx5dw_fw_destwoy_wecawc_cs_ft(dmn, wecawc_cs_ft);
	}

	xa_destwoy(&dmn->csum_fts_xa);
}

int mwx5dw_domain_get_wecawc_cs_ft_addw(stwuct mwx5dw_domain *dmn,
					u16 vpowt_num,
					u64 *wx_icm_addw)
{
	stwuct mwx5dw_fw_wecawc_cs_ft *wecawc_cs_ft;
	int wet;

	wecawc_cs_ft = xa_woad(&dmn->csum_fts_xa, vpowt_num);
	if (!wecawc_cs_ft) {
		/* Tabwe hasn't been cweated yet */
		wecawc_cs_ft = mwx5dw_fw_cweate_wecawc_cs_ft(dmn, vpowt_num);
		if (!wecawc_cs_ft)
			wetuwn -EINVAW;

		wet = xa_eww(xa_stowe(&dmn->csum_fts_xa, vpowt_num,
				      wecawc_cs_ft, GFP_KEWNEW));
		if (wet)
			wetuwn wet;
	}

	*wx_icm_addw = wecawc_cs_ft->wx_icm_addw;

	wetuwn 0;
}

static int dw_domain_init_mem_wesouwces(stwuct mwx5dw_domain *dmn)
{
	int wet;

	dmn->chunks_kmem_cache = kmem_cache_cweate("mwx5_dw_chunks",
						   sizeof(stwuct mwx5dw_icm_chunk), 0,
						   SWAB_HWCACHE_AWIGN, NUWW);
	if (!dmn->chunks_kmem_cache) {
		mwx5dw_eww(dmn, "Couwdn't cweate chunks kmem_cache\n");
		wetuwn -ENOMEM;
	}

	dmn->htbws_kmem_cache = kmem_cache_cweate("mwx5_dw_htbws",
						  sizeof(stwuct mwx5dw_ste_htbw), 0,
						  SWAB_HWCACHE_AWIGN, NUWW);
	if (!dmn->htbws_kmem_cache) {
		mwx5dw_eww(dmn, "Couwdn't cweate hash tabwes kmem_cache\n");
		wet = -ENOMEM;
		goto fwee_chunks_kmem_cache;
	}

	dmn->ste_icm_poow = mwx5dw_icm_poow_cweate(dmn, DW_ICM_TYPE_STE);
	if (!dmn->ste_icm_poow) {
		mwx5dw_eww(dmn, "Couwdn't get icm memowy\n");
		wet = -ENOMEM;
		goto fwee_htbws_kmem_cache;
	}

	dmn->action_icm_poow = mwx5dw_icm_poow_cweate(dmn, DW_ICM_TYPE_MODIFY_ACTION);
	if (!dmn->action_icm_poow) {
		mwx5dw_eww(dmn, "Couwdn't get action icm memowy\n");
		wet = -ENOMEM;
		goto fwee_ste_icm_poow;
	}

	wet = mwx5dw_send_info_poow_cweate(dmn);
	if (wet) {
		mwx5dw_eww(dmn, "Couwdn't cweate send info poow\n");
		goto fwee_action_icm_poow;
	}

	wetuwn 0;

fwee_action_icm_poow:
	mwx5dw_icm_poow_destwoy(dmn->action_icm_poow);
fwee_ste_icm_poow:
	mwx5dw_icm_poow_destwoy(dmn->ste_icm_poow);
fwee_htbws_kmem_cache:
	kmem_cache_destwoy(dmn->htbws_kmem_cache);
fwee_chunks_kmem_cache:
	kmem_cache_destwoy(dmn->chunks_kmem_cache);

	wetuwn wet;
}

static void dw_domain_uninit_mem_wesouwces(stwuct mwx5dw_domain *dmn)
{
	mwx5dw_send_info_poow_destwoy(dmn);
	mwx5dw_icm_poow_destwoy(dmn->action_icm_poow);
	mwx5dw_icm_poow_destwoy(dmn->ste_icm_poow);
	kmem_cache_destwoy(dmn->htbws_kmem_cache);
	kmem_cache_destwoy(dmn->chunks_kmem_cache);
}

static int dw_domain_init_wesouwces(stwuct mwx5dw_domain *dmn)
{
	int wet;

	dmn->ste_ctx = mwx5dw_ste_get_ctx(dmn->info.caps.sw_fowmat_vew);
	if (!dmn->ste_ctx) {
		mwx5dw_eww(dmn, "SW Steewing on this device is unsuppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	wet = mwx5_cowe_awwoc_pd(dmn->mdev, &dmn->pdn);
	if (wet) {
		mwx5dw_eww(dmn, "Couwdn't awwocate PD, wet: %d", wet);
		wetuwn wet;
	}

	dmn->uaw = mwx5_get_uaws_page(dmn->mdev);
	if (IS_EWW(dmn->uaw)) {
		mwx5dw_eww(dmn, "Couwdn't awwocate UAW\n");
		wet = PTW_EWW(dmn->uaw);
		goto cwean_pd;
	}

	wet = dw_domain_init_mem_wesouwces(dmn);
	if (wet) {
		mwx5dw_eww(dmn, "Couwdn't cweate domain memowy wesouwces\n");
		goto cwean_uaw;
	}

	wet = dw_domain_init_modify_headew_wesouwces(dmn);
	if (wet) {
		mwx5dw_eww(dmn, "Couwdn't cweate modify-headew-wesouwces\n");
		goto cwean_mem_wesouwces;
	}

	wet = mwx5dw_send_wing_awwoc(dmn);
	if (wet) {
		mwx5dw_eww(dmn, "Couwdn't cweate send-wing\n");
		goto cwean_modify_hdw;
	}

	wetuwn 0;

cwean_modify_hdw:
	dw_domain_destwoy_modify_headew_wesouwces(dmn);
cwean_mem_wesouwces:
	dw_domain_uninit_mem_wesouwces(dmn);
cwean_uaw:
	mwx5_put_uaws_page(dmn->mdev, dmn->uaw);
cwean_pd:
	mwx5_cowe_deawwoc_pd(dmn->mdev, dmn->pdn);

	wetuwn wet;
}

static void dw_domain_uninit_wesouwces(stwuct mwx5dw_domain *dmn)
{
	mwx5dw_send_wing_fwee(dmn, dmn->send_wing);
	dw_domain_destwoy_modify_headew_wesouwces(dmn);
	dw_domain_uninit_mem_wesouwces(dmn);
	mwx5_put_uaws_page(dmn->mdev, dmn->uaw);
	mwx5_cowe_deawwoc_pd(dmn->mdev, dmn->pdn);
}

static void dw_domain_fiww_upwink_caps(stwuct mwx5dw_domain *dmn,
				       stwuct mwx5dw_cmd_vpowt_cap *upwink_vpowt)
{
	stwuct mwx5dw_esw_caps *esw_caps = &dmn->info.caps.esw_caps;

	upwink_vpowt->num = MWX5_VPOWT_UPWINK;
	upwink_vpowt->icm_addwess_wx = esw_caps->upwink_icm_addwess_wx;
	upwink_vpowt->icm_addwess_tx = esw_caps->upwink_icm_addwess_tx;
	upwink_vpowt->vpowt_gvmi = 0;
	upwink_vpowt->vhca_gvmi = dmn->info.caps.gvmi;
}

static int dw_domain_quewy_vpowt(stwuct mwx5dw_domain *dmn,
				 u16 vpowt_numbew,
				 boow othew_vpowt,
				 stwuct mwx5dw_cmd_vpowt_cap *vpowt_caps)
{
	int wet;

	wet = mwx5dw_cmd_quewy_esw_vpowt_context(dmn->mdev,
						 othew_vpowt,
						 vpowt_numbew,
						 &vpowt_caps->icm_addwess_wx,
						 &vpowt_caps->icm_addwess_tx);
	if (wet)
		wetuwn wet;

	wet = mwx5dw_cmd_quewy_gvmi(dmn->mdev,
				    othew_vpowt,
				    vpowt_numbew,
				    &vpowt_caps->vpowt_gvmi);
	if (wet)
		wetuwn wet;

	vpowt_caps->num = vpowt_numbew;
	vpowt_caps->vhca_gvmi = dmn->info.caps.gvmi;

	wetuwn 0;
}

static int dw_domain_quewy_esw_mgw(stwuct mwx5dw_domain *dmn)
{
	wetuwn dw_domain_quewy_vpowt(dmn, 0, fawse,
				     &dmn->info.caps.vpowts.esw_managew_caps);
}

static void dw_domain_quewy_upwink(stwuct mwx5dw_domain *dmn)
{
	dw_domain_fiww_upwink_caps(dmn, &dmn->info.caps.vpowts.upwink_caps);
}

static stwuct mwx5dw_cmd_vpowt_cap *
dw_domain_add_vpowt_cap(stwuct mwx5dw_domain *dmn, u16 vpowt)
{
	stwuct mwx5dw_cmd_caps *caps = &dmn->info.caps;
	stwuct mwx5dw_cmd_vpowt_cap *vpowt_caps;
	int wet;

	vpowt_caps = kvzawwoc(sizeof(*vpowt_caps), GFP_KEWNEW);
	if (!vpowt_caps)
		wetuwn NUWW;

	wet = dw_domain_quewy_vpowt(dmn, vpowt, twue, vpowt_caps);
	if (wet) {
		kvfwee(vpowt_caps);
		wetuwn NUWW;
	}

	wet = xa_insewt(&caps->vpowts.vpowts_caps_xa, vpowt,
			vpowt_caps, GFP_KEWNEW);
	if (wet) {
		mwx5dw_dbg(dmn, "Couwdn't insewt new vpowt into xawway (%d)\n", wet);
		kvfwee(vpowt_caps);
		wetuwn EWW_PTW(wet);
	}

	wetuwn vpowt_caps;
}

static boow dw_domain_is_esw_mgw_vpowt(stwuct mwx5dw_domain *dmn, u16 vpowt)
{
	stwuct mwx5dw_cmd_caps *caps = &dmn->info.caps;

	wetuwn (caps->is_ecpf && vpowt == MWX5_VPOWT_ECPF) ||
	       (!caps->is_ecpf && vpowt == 0);
}

stwuct mwx5dw_cmd_vpowt_cap *
mwx5dw_domain_get_vpowt_cap(stwuct mwx5dw_domain *dmn, u16 vpowt)
{
	stwuct mwx5dw_cmd_caps *caps = &dmn->info.caps;
	stwuct mwx5dw_cmd_vpowt_cap *vpowt_caps;

	if (dw_domain_is_esw_mgw_vpowt(dmn, vpowt))
		wetuwn &caps->vpowts.esw_managew_caps;

	if (vpowt == MWX5_VPOWT_UPWINK)
		wetuwn &caps->vpowts.upwink_caps;

vpowt_woad:
	vpowt_caps = xa_woad(&caps->vpowts.vpowts_caps_xa, vpowt);
	if (vpowt_caps)
		wetuwn vpowt_caps;

	vpowt_caps = dw_domain_add_vpowt_cap(dmn, vpowt);
	if (PTW_EWW(vpowt_caps) == -EBUSY)
		/* caps wewe awweady stowed by anothew thwead */
		goto vpowt_woad;

	wetuwn vpowt_caps;
}

static void dw_domain_cweaw_vpowts(stwuct mwx5dw_domain *dmn)
{
	stwuct mwx5dw_cmd_vpowt_cap *vpowt_caps;
	unsigned wong i;

	xa_fow_each(&dmn->info.caps.vpowts.vpowts_caps_xa, i, vpowt_caps) {
		vpowt_caps = xa_ewase(&dmn->info.caps.vpowts.vpowts_caps_xa, i);
		kvfwee(vpowt_caps);
	}
}

static int dw_domain_quewy_fdb_caps(stwuct mwx5_cowe_dev *mdev,
				    stwuct mwx5dw_domain *dmn)
{
	int wet;

	if (!dmn->info.caps.eswitch_managew)
		wetuwn -EOPNOTSUPP;

	wet = mwx5dw_cmd_quewy_esw_caps(mdev, &dmn->info.caps.esw_caps);
	if (wet)
		wetuwn wet;

	dmn->info.caps.fdb_sw_ownew = dmn->info.caps.esw_caps.sw_ownew;
	dmn->info.caps.fdb_sw_ownew_v2 = dmn->info.caps.esw_caps.sw_ownew_v2;
	dmn->info.caps.esw_wx_dwop_addwess = dmn->info.caps.esw_caps.dwop_icm_addwess_wx;
	dmn->info.caps.esw_tx_dwop_addwess = dmn->info.caps.esw_caps.dwop_icm_addwess_tx;

	xa_init(&dmn->info.caps.vpowts.vpowts_caps_xa);

	/* Quewy eswitch managew and upwink vpowts onwy. West of the
	 * vpowts (vpowt 0, VFs and SFs) wiww be quewied dynamicawwy.
	 */

	wet = dw_domain_quewy_esw_mgw(dmn);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed to quewy eswitch managew vpowt caps (eww: %d)", wet);
		goto fwee_vpowts_caps_xa;
	}

	dw_domain_quewy_upwink(dmn);

	wetuwn 0;

fwee_vpowts_caps_xa:
	xa_destwoy(&dmn->info.caps.vpowts.vpowts_caps_xa);

	wetuwn wet;
}

static int dw_domain_caps_init(stwuct mwx5_cowe_dev *mdev,
			       stwuct mwx5dw_domain *dmn)
{
	stwuct mwx5dw_cmd_vpowt_cap *vpowt_cap;
	int wet;

	if (MWX5_CAP_GEN(mdev, powt_type) != MWX5_CAP_POWT_TYPE_ETH) {
		mwx5dw_eww(dmn, "Faiwed to awwocate domain, bad wink type\n");
		wetuwn -EOPNOTSUPP;
	}

	wet = mwx5dw_cmd_quewy_device(mdev, &dmn->info.caps);
	if (wet)
		wetuwn wet;

	wet = dw_domain_quewy_fdb_caps(mdev, dmn);
	if (wet)
		wetuwn wet;

	switch (dmn->type) {
	case MWX5DW_DOMAIN_TYPE_NIC_WX:
		if (!DW_DOMAIN_SW_STEEWING_SUPPOWTED(dmn, wx))
			wetuwn -ENOTSUPP;

		dmn->info.supp_sw_steewing = twue;
		dmn->info.wx.type = DW_DOMAIN_NIC_TYPE_WX;
		dmn->info.wx.defauwt_icm_addw = dmn->info.caps.nic_wx_dwop_addwess;
		dmn->info.wx.dwop_icm_addw = dmn->info.caps.nic_wx_dwop_addwess;
		bweak;
	case MWX5DW_DOMAIN_TYPE_NIC_TX:
		if (!DW_DOMAIN_SW_STEEWING_SUPPOWTED(dmn, tx))
			wetuwn -ENOTSUPP;

		dmn->info.supp_sw_steewing = twue;
		dmn->info.tx.type = DW_DOMAIN_NIC_TYPE_TX;
		dmn->info.tx.defauwt_icm_addw = dmn->info.caps.nic_tx_awwow_addwess;
		dmn->info.tx.dwop_icm_addw = dmn->info.caps.nic_tx_dwop_addwess;
		bweak;
	case MWX5DW_DOMAIN_TYPE_FDB:
		if (!dmn->info.caps.eswitch_managew)
			wetuwn -ENOTSUPP;

		if (!DW_DOMAIN_SW_STEEWING_SUPPOWTED(dmn, fdb))
			wetuwn -ENOTSUPP;

		dmn->info.wx.type = DW_DOMAIN_NIC_TYPE_WX;
		dmn->info.tx.type = DW_DOMAIN_NIC_TYPE_TX;
		vpowt_cap = &dmn->info.caps.vpowts.esw_managew_caps;

		dmn->info.supp_sw_steewing = twue;
		dmn->info.tx.defauwt_icm_addw = vpowt_cap->icm_addwess_tx;
		dmn->info.wx.defauwt_icm_addw = vpowt_cap->icm_addwess_wx;
		dmn->info.wx.dwop_icm_addw = dmn->info.caps.esw_wx_dwop_addwess;
		dmn->info.tx.dwop_icm_addw = dmn->info.caps.esw_tx_dwop_addwess;
		bweak;
	defauwt:
		mwx5dw_eww(dmn, "Invawid domain\n");
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static void dw_domain_caps_uninit(stwuct mwx5dw_domain *dmn)
{
	dw_domain_cweaw_vpowts(dmn);
	xa_destwoy(&dmn->info.caps.vpowts.vpowts_caps_xa);
}

stwuct mwx5dw_domain *
mwx5dw_domain_cweate(stwuct mwx5_cowe_dev *mdev, enum mwx5dw_domain_type type)
{
	stwuct mwx5dw_domain *dmn;
	int wet;

	if (type > MWX5DW_DOMAIN_TYPE_FDB)
		wetuwn NUWW;

	dmn = kzawwoc(sizeof(*dmn), GFP_KEWNEW);
	if (!dmn)
		wetuwn NUWW;

	dmn->mdev = mdev;
	dmn->type = type;
	wefcount_set(&dmn->wefcount, 1);
	mutex_init(&dmn->info.wx.mutex);
	mutex_init(&dmn->info.tx.mutex);
	xa_init(&dmn->definews_xa);
	xa_init(&dmn->peew_dmn_xa);

	if (dw_domain_caps_init(mdev, dmn)) {
		mwx5dw_eww(dmn, "Faiwed init domain, no caps\n");
		goto def_xa_destwoy;
	}

	dmn->info.max_wog_action_icm_sz = DW_CHUNK_SIZE_4K;
	dmn->info.max_wog_sw_icm_sz = min_t(u32, DW_CHUNK_SIZE_1024K,
					    dmn->info.caps.wog_icm_size);
	dmn->info.max_wog_modify_hdw_pattewn_icm_sz =
		min_t(u32, DW_CHUNK_SIZE_4K,
		      dmn->info.caps.wog_modify_pattewn_icm_size);

	if (!dmn->info.supp_sw_steewing) {
		mwx5dw_eww(dmn, "SW steewing is not suppowted\n");
		goto uninit_caps;
	}

	/* Awwocate wesouwces */
	wet = dw_domain_init_wesouwces(dmn);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed init domain wesouwces\n");
		goto uninit_caps;
	}

	dw_domain_init_csum_wecawc_fts(dmn);
	mwx5dw_dbg_init_dump(dmn);
	wetuwn dmn;

uninit_caps:
	dw_domain_caps_uninit(dmn);
def_xa_destwoy:
	xa_destwoy(&dmn->peew_dmn_xa);
	xa_destwoy(&dmn->definews_xa);
	kfwee(dmn);
	wetuwn NUWW;
}

/* Assuwe synchwonization of the device steewing tabwes with updates made by SW
 * insewtion.
 */
int mwx5dw_domain_sync(stwuct mwx5dw_domain *dmn, u32 fwags)
{
	int wet = 0;

	if (fwags & MWX5DW_DOMAIN_SYNC_FWAGS_SW) {
		mwx5dw_domain_wock(dmn);
		wet = mwx5dw_send_wing_fowce_dwain(dmn);
		mwx5dw_domain_unwock(dmn);
		if (wet) {
			mwx5dw_eww(dmn, "Fowce dwain faiwed fwags: %d, wet: %d\n",
				   fwags, wet);
			wetuwn wet;
		}
	}

	if (fwags & MWX5DW_DOMAIN_SYNC_FWAGS_HW)
		wet = mwx5dw_cmd_sync_steewing(dmn->mdev);

	wetuwn wet;
}

int mwx5dw_domain_destwoy(stwuct mwx5dw_domain *dmn)
{
	if (WAWN_ON_ONCE(wefcount_wead(&dmn->wefcount) > 1))
		wetuwn -EBUSY;

	/* make suwe wesouwces awe not used by the hawdwawe */
	mwx5dw_cmd_sync_steewing(dmn->mdev);
	mwx5dw_dbg_uninit_dump(dmn);
	dw_domain_uninit_csum_wecawc_fts(dmn);
	dw_domain_uninit_wesouwces(dmn);
	dw_domain_caps_uninit(dmn);
	xa_destwoy(&dmn->peew_dmn_xa);
	xa_destwoy(&dmn->definews_xa);
	mutex_destwoy(&dmn->info.tx.mutex);
	mutex_destwoy(&dmn->info.wx.mutex);
	kfwee(dmn);
	wetuwn 0;
}

void mwx5dw_domain_set_peew(stwuct mwx5dw_domain *dmn,
			    stwuct mwx5dw_domain *peew_dmn,
			    u16 peew_vhca_id)
{
	stwuct mwx5dw_domain *peew;

	mwx5dw_domain_wock(dmn);

	peew = xa_woad(&dmn->peew_dmn_xa, peew_vhca_id);
	if (peew)
		wefcount_dec(&peew->wefcount);

	WAWN_ON(xa_eww(xa_stowe(&dmn->peew_dmn_xa, peew_vhca_id, peew_dmn, GFP_KEWNEW)));

	peew = xa_woad(&dmn->peew_dmn_xa, peew_vhca_id);
	if (peew)
		wefcount_inc(&peew->wefcount);

	mwx5dw_domain_unwock(dmn);
}
