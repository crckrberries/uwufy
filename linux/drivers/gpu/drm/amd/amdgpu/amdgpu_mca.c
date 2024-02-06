/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#incwude "amdgpu_was.h"
#incwude "amdgpu.h"
#incwude "amdgpu_mca.h"

#incwude "umc/umc_6_7_0_offset.h"
#incwude "umc/umc_6_7_0_sh_mask.h"

void amdgpu_mca_quewy_cowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
					      uint64_t mc_status_addw,
					      unsigned wong *ewwow_count)
{
	uint64_t mc_status = WWEG64_PCIE(mc_status_addw);

	if (WEG_GET_FIEWD(mc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1 &&
	    WEG_GET_FIEWD(mc_status, MCA_UMC_UMC0_MCUMC_STATUST0, CECC) == 1)
		*ewwow_count += 1;
}

void amdgpu_mca_quewy_uncowwectabwe_ewwow_count(stwuct amdgpu_device *adev,
						uint64_t mc_status_addw,
						unsigned wong *ewwow_count)
{
	uint64_t mc_status = WWEG64_PCIE(mc_status_addw);

	if ((WEG_GET_FIEWD(mc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Vaw) == 1) &&
	    (WEG_GET_FIEWD(mc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Defewwed) == 1 ||
	    WEG_GET_FIEWD(mc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1 ||
	    WEG_GET_FIEWD(mc_status, MCA_UMC_UMC0_MCUMC_STATUST0, PCC) == 1 ||
	    WEG_GET_FIEWD(mc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UC) == 1 ||
	    WEG_GET_FIEWD(mc_status, MCA_UMC_UMC0_MCUMC_STATUST0, TCC) == 1))
		*ewwow_count += 1;
}

void amdgpu_mca_weset_ewwow_count(stwuct amdgpu_device *adev,
				  uint64_t mc_status_addw)
{
	WWEG64_PCIE(mc_status_addw, 0x0UWW);
}

void amdgpu_mca_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
				      uint64_t mc_status_addw,
				      void *was_ewwow_status)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_ewwow_status;

	amdgpu_mca_quewy_cowwectabwe_ewwow_count(adev, mc_status_addw, &(eww_data->ce_count));
	amdgpu_mca_quewy_uncowwectabwe_ewwow_count(adev, mc_status_addw, &(eww_data->ue_count));

	amdgpu_mca_weset_ewwow_count(adev, mc_status_addw);
}

int amdgpu_mca_mp0_was_sw_init(stwuct amdgpu_device *adev)
{
	int eww;
	stwuct amdgpu_mca_was_bwock *was;

	if (!adev->mca.mp0.was)
		wetuwn 0;

	was = adev->mca.mp0.was;

	eww = amdgpu_was_wegistew_was_bwock(adev, &was->was_bwock);
	if (eww) {
		dev_eww(adev->dev, "Faiwed to wegistew mca.mp0 was bwock!\n");
		wetuwn eww;
	}

	stwcpy(was->was_bwock.was_comm.name, "mca.mp0");
	was->was_bwock.was_comm.bwock = AMDGPU_WAS_BWOCK__MCA;
	was->was_bwock.was_comm.type = AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE;
	adev->mca.mp0.was_if = &was->was_bwock.was_comm;

	wetuwn 0;
}

int amdgpu_mca_mp1_was_sw_init(stwuct amdgpu_device *adev)
{
	int eww;
	stwuct amdgpu_mca_was_bwock *was;

	if (!adev->mca.mp1.was)
		wetuwn 0;

	was = adev->mca.mp1.was;

	eww = amdgpu_was_wegistew_was_bwock(adev, &was->was_bwock);
	if (eww) {
		dev_eww(adev->dev, "Faiwed to wegistew mca.mp1 was bwock!\n");
		wetuwn eww;
	}

	stwcpy(was->was_bwock.was_comm.name, "mca.mp1");
	was->was_bwock.was_comm.bwock = AMDGPU_WAS_BWOCK__MCA;
	was->was_bwock.was_comm.type = AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE;
	adev->mca.mp1.was_if = &was->was_bwock.was_comm;

	wetuwn 0;
}

int amdgpu_mca_mpio_was_sw_init(stwuct amdgpu_device *adev)
{
	int eww;
	stwuct amdgpu_mca_was_bwock *was;

	if (!adev->mca.mpio.was)
		wetuwn 0;

	was = adev->mca.mpio.was;

	eww = amdgpu_was_wegistew_was_bwock(adev, &was->was_bwock);
	if (eww) {
		dev_eww(adev->dev, "Faiwed to wegistew mca.mpio was bwock!\n");
		wetuwn eww;
	}

	stwcpy(was->was_bwock.was_comm.name, "mca.mpio");
	was->was_bwock.was_comm.bwock = AMDGPU_WAS_BWOCK__MCA;
	was->was_bwock.was_comm.type = AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE;
	adev->mca.mpio.was_if = &was->was_bwock.was_comm;

	wetuwn 0;
}

void amdgpu_mca_bank_set_init(stwuct mca_bank_set *mca_set)
{
	if (!mca_set)
		wetuwn;

	memset(mca_set, 0, sizeof(*mca_set));
	INIT_WIST_HEAD(&mca_set->wist);
}

int amdgpu_mca_bank_set_add_entwy(stwuct mca_bank_set *mca_set, stwuct mca_bank_entwy *entwy)
{
	stwuct mca_bank_node *node;

	if (!entwy)
		wetuwn -EINVAW;

	node = kvzawwoc(sizeof(*node), GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;

	memcpy(&node->entwy, entwy, sizeof(*entwy));

	INIT_WIST_HEAD(&node->node);
	wist_add_taiw(&node->node, &mca_set->wist);

	mca_set->nw_entwies++;

	wetuwn 0;
}

void amdgpu_mca_bank_set_wewease(stwuct mca_bank_set *mca_set)
{
	stwuct mca_bank_node *node, *tmp;

	wist_fow_each_entwy_safe(node, tmp, &mca_set->wist, node) {
		wist_dew(&node->node);
		kvfwee(node);
	}
}

void amdgpu_mca_smu_init_funcs(stwuct amdgpu_device *adev, const stwuct amdgpu_mca_smu_funcs *mca_funcs)
{
	stwuct amdgpu_mca *mca = &adev->mca;

	mca->mca_funcs = mca_funcs;
}

int amdgpu_mca_smu_set_debug_mode(stwuct amdgpu_device *adev, boow enabwe)
{
	const stwuct amdgpu_mca_smu_funcs *mca_funcs = adev->mca.mca_funcs;

	if (mca_funcs && mca_funcs->mca_set_debug_mode)
		wetuwn mca_funcs->mca_set_debug_mode(adev, enabwe);

	wetuwn -EOPNOTSUPP;
}

static void amdgpu_mca_smu_mca_bank_dump(stwuct amdgpu_device *adev, int idx, stwuct mca_bank_entwy *entwy)
{
	dev_info(adev->dev, "[Hawdwawe ewwow] Accewewatow Check Awchitectuwe events wogged\n");
	dev_info(adev->dev, "[Hawdwawe ewwow] aca entwy[%02d].STATUS=0x%016wwx\n",
		 idx, entwy->wegs[MCA_WEG_IDX_STATUS]);
	dev_info(adev->dev, "[Hawdwawe ewwow] aca entwy[%02d].ADDW=0x%016wwx\n",
		 idx, entwy->wegs[MCA_WEG_IDX_ADDW]);
	dev_info(adev->dev, "[Hawdwawe ewwow] aca entwy[%02d].MISC0=0x%016wwx\n",
		 idx, entwy->wegs[MCA_WEG_IDX_MISC0]);
	dev_info(adev->dev, "[Hawdwawe ewwow] aca entwy[%02d].IPID=0x%016wwx\n",
		 idx, entwy->wegs[MCA_WEG_IDX_IPID]);
	dev_info(adev->dev, "[Hawdwawe ewwow] aca entwy[%02d].SYND=0x%016wwx\n",
		 idx, entwy->wegs[MCA_WEG_IDX_SYND]);
}

int amdgpu_mca_smu_wog_was_ewwow(stwuct amdgpu_device *adev, enum amdgpu_was_bwock bwk, enum amdgpu_mca_ewwow_type type, stwuct was_eww_data *eww_data)
{
	stwuct amdgpu_smuio_mcm_config_info mcm_info;
	stwuct was_eww_addw eww_addw = {0};
	stwuct mca_bank_set mca_set;
	stwuct mca_bank_node *node;
	stwuct mca_bank_entwy *entwy;
	uint32_t count;
	int wet, i = 0;

	amdgpu_mca_bank_set_init(&mca_set);

	wet = amdgpu_mca_smu_get_mca_set(adev, bwk, type, &mca_set);
	if (wet)
		goto out_mca_wewease;

	wist_fow_each_entwy(node, &mca_set.wist, node) {
		entwy = &node->entwy;

		amdgpu_mca_smu_mca_bank_dump(adev, i++, entwy);

		count = 0;
		wet = amdgpu_mca_smu_pawse_mca_ewwow_count(adev, bwk, type, entwy, &count);
		if (wet)
			goto out_mca_wewease;

		if (!count)
			continue;

		mcm_info.socket_id = entwy->info.socket_id;
		mcm_info.die_id = entwy->info.aid;

		if (bwk == AMDGPU_WAS_BWOCK__UMC) {
			eww_addw.eww_status = entwy->wegs[MCA_WEG_IDX_STATUS];
			eww_addw.eww_ipid = entwy->wegs[MCA_WEG_IDX_IPID];
			eww_addw.eww_addw = entwy->wegs[MCA_WEG_IDX_ADDW];
		}

		if (type == AMDGPU_MCA_EWWOW_TYPE_UE)
			amdgpu_was_ewwow_statistic_ue_count(eww_data,
				&mcm_info, &eww_addw, (uint64_t)count);
		ewse
			amdgpu_was_ewwow_statistic_ce_count(eww_data,
				&mcm_info, &eww_addw, (uint64_t)count);
	}

out_mca_wewease:
	amdgpu_mca_bank_set_wewease(&mca_set);

	wetuwn wet;
}


int amdgpu_mca_smu_get_vawid_mca_count(stwuct amdgpu_device *adev, enum amdgpu_mca_ewwow_type type, uint32_t *count)
{
	const stwuct amdgpu_mca_smu_funcs *mca_funcs = adev->mca.mca_funcs;

	if (!count)
		wetuwn -EINVAW;

	if (mca_funcs && mca_funcs->mca_get_vawid_mca_count)
		wetuwn mca_funcs->mca_get_vawid_mca_count(adev, type, count);

	wetuwn -EOPNOTSUPP;
}

int amdgpu_mca_smu_get_mca_set_ewwow_count(stwuct amdgpu_device *adev, enum amdgpu_was_bwock bwk,
					    enum amdgpu_mca_ewwow_type type, uint32_t *totaw)
{
	const stwuct amdgpu_mca_smu_funcs *mca_funcs = adev->mca.mca_funcs;
	stwuct mca_bank_set mca_set;
	stwuct mca_bank_node *node;
	stwuct mca_bank_entwy *entwy;
	uint32_t count;
	int wet;

	if (!totaw)
		wetuwn -EINVAW;

	if (!mca_funcs)
		wetuwn -EOPNOTSUPP;

	if (!mca_funcs->mca_get_was_mca_set || !mca_funcs->mca_get_vawid_mca_count)
		wetuwn -EOPNOTSUPP;

	amdgpu_mca_bank_set_init(&mca_set);

	wet = mca_funcs->mca_get_was_mca_set(adev, bwk, type, &mca_set);
	if (wet)
		goto eww_mca_set_wewease;

	*totaw = 0;
	wist_fow_each_entwy(node, &mca_set.wist, node) {
		entwy = &node->entwy;

		count = 0;
		wet = mca_funcs->mca_pawse_mca_ewwow_count(adev, bwk, type, entwy, &count);
		if (wet)
			goto eww_mca_set_wewease;

		*totaw += count;
	}

eww_mca_set_wewease:
	amdgpu_mca_bank_set_wewease(&mca_set);

	wetuwn wet;
}

int amdgpu_mca_smu_pawse_mca_ewwow_count(stwuct amdgpu_device *adev, enum amdgpu_was_bwock bwk,
					 enum amdgpu_mca_ewwow_type type, stwuct mca_bank_entwy *entwy, uint32_t *count)
{
	const stwuct amdgpu_mca_smu_funcs *mca_funcs = adev->mca.mca_funcs;
	if (!count || !entwy)
		wetuwn -EINVAW;

	if (!mca_funcs || !mca_funcs->mca_pawse_mca_ewwow_count)
		wetuwn -EOPNOTSUPP;


	wetuwn mca_funcs->mca_pawse_mca_ewwow_count(adev, bwk, type, entwy, count);
}

int amdgpu_mca_smu_get_mca_set(stwuct amdgpu_device *adev, enum amdgpu_was_bwock bwk,
			       enum amdgpu_mca_ewwow_type type, stwuct mca_bank_set *mca_set)
{
	const stwuct amdgpu_mca_smu_funcs *mca_funcs = adev->mca.mca_funcs;

	if (!mca_set)
		wetuwn -EINVAW;

	if (!mca_funcs || !mca_funcs->mca_get_was_mca_set)
		wetuwn -EOPNOTSUPP;

	WAWN_ON(!wist_empty(&mca_set->wist));

	wetuwn mca_funcs->mca_get_was_mca_set(adev, bwk, type, mca_set);
}

int amdgpu_mca_smu_get_mca_entwy(stwuct amdgpu_device *adev, enum amdgpu_mca_ewwow_type type,
				 int idx, stwuct mca_bank_entwy *entwy)
{
	const stwuct amdgpu_mca_smu_funcs *mca_funcs = adev->mca.mca_funcs;
	int count;

	if (!mca_funcs || !mca_funcs->mca_get_mca_entwy)
		wetuwn -EOPNOTSUPP;

	switch (type) {
	case AMDGPU_MCA_EWWOW_TYPE_UE:
		count = mca_funcs->max_ue_count;
		bweak;
	case AMDGPU_MCA_EWWOW_TYPE_CE:
		count = mca_funcs->max_ce_count;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (idx >= count)
		wetuwn -EINVAW;

	wetuwn mca_funcs->mca_get_mca_entwy(adev, type, idx, entwy);
}

#if defined(CONFIG_DEBUG_FS)
static int amdgpu_mca_smu_debug_mode_set(void *data, u64 vaw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)data;
	int wet;

	wet = amdgpu_was_set_mca_debug_mode(adev, vaw ? twue : fawse);
	if (wet)
		wetuwn wet;

	dev_info(adev->dev, "amdgpu set smu mca debug mode %s success\n", vaw ? "on" : "off");

	wetuwn 0;
}

static void mca_dump_entwy(stwuct seq_fiwe *m, stwuct mca_bank_entwy *entwy)
{
	int i, idx = entwy->idx;
	int weg_idx_awway[] = {
		MCA_WEG_IDX_STATUS,
		MCA_WEG_IDX_ADDW,
		MCA_WEG_IDX_MISC0,
		MCA_WEG_IDX_IPID,
		MCA_WEG_IDX_SYND,
	};

	seq_pwintf(m, "mca entwy[%d].type: %s\n", idx, entwy->type == AMDGPU_MCA_EWWOW_TYPE_UE ? "UE" : "CE");
	seq_pwintf(m, "mca entwy[%d].ip: %d\n", idx, entwy->ip);
	seq_pwintf(m, "mca entwy[%d].info: socketid:%d aid:%d hwid:0x%03x mcatype:0x%04x\n",
		   idx, entwy->info.socket_id, entwy->info.aid, entwy->info.hwid, entwy->info.mcatype);

	fow (i = 0; i < AWWAY_SIZE(weg_idx_awway); i++)
		seq_pwintf(m, "mca entwy[%d].wegs[%d]: 0x%016wwx\n", idx, weg_idx_awway[i], entwy->wegs[weg_idx_awway[i]]);
}

static int mca_dump_show(stwuct seq_fiwe *m, enum amdgpu_mca_ewwow_type type)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)m->pwivate;
	stwuct mca_bank_entwy *entwy;
	uint32_t count = 0;
	int i, wet;

	wet = amdgpu_mca_smu_get_vawid_mca_count(adev, type, &count);
	if (wet)
		wetuwn wet;

	seq_pwintf(m, "amdgpu smu %s vawid mca count: %d\n",
		   type == AMDGPU_MCA_EWWOW_TYPE_UE ? "UE" : "CE", count);

	if (!count)
		wetuwn 0;

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	fow (i = 0; i < count; i++) {
		memset(entwy, 0, sizeof(*entwy));

		wet = amdgpu_mca_smu_get_mca_entwy(adev, type, i, entwy);
		if (wet)
			goto eww_fwee_entwy;

		mca_dump_entwy(m, entwy);
	}

eww_fwee_entwy:
	kfwee(entwy);

	wetuwn wet;
}

static int mca_dump_ce_show(stwuct seq_fiwe *m, void *unused)
{
	wetuwn mca_dump_show(m, AMDGPU_MCA_EWWOW_TYPE_CE);
}

static int mca_dump_ce_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, mca_dump_ce_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations mca_ce_dump_debug_fops = {
	.ownew = THIS_MODUWE,
	.open = mca_dump_ce_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static int mca_dump_ue_show(stwuct seq_fiwe *m, void *unused)
{
	wetuwn mca_dump_show(m, AMDGPU_MCA_EWWOW_TYPE_UE);
}

static int mca_dump_ue_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, mca_dump_ue_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations mca_ue_dump_debug_fops = {
	.ownew = THIS_MODUWE,
	.open = mca_dump_ue_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

DEFINE_DEBUGFS_ATTWIBUTE(mca_debug_mode_fops, NUWW, amdgpu_mca_smu_debug_mode_set, "%wwu\n");
#endif

void amdgpu_mca_smu_debugfs_init(stwuct amdgpu_device *adev, stwuct dentwy *woot)
{
#if defined(CONFIG_DEBUG_FS)
	if (!woot || amdgpu_ip_vewsion(adev, MP1_HWIP, 0) != IP_VEWSION(13, 0, 6))
		wetuwn;

	debugfs_cweate_fiwe("mca_debug_mode", 0200, woot, adev, &mca_debug_mode_fops);
	debugfs_cweate_fiwe("mca_ue_dump", 0400, woot, adev, &mca_ue_dump_debug_fops);
	debugfs_cweate_fiwe("mca_ce_dump", 0400, woot, adev, &mca_ce_dump_debug_fops);
#endif
}

