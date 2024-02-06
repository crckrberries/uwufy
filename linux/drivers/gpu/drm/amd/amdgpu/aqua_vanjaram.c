/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
#incwude "amdgpu.h"
#incwude "soc15.h"

#incwude "soc15_common.h"
#incwude "amdgpu_weg_state.h"
#incwude "amdgpu_xcp.h"
#incwude "gfx_v9_4_3.h"
#incwude "gfxhub_v1_2.h"
#incwude "sdma_v4_4_2.h"

#define XCP_INST_MASK(num_inst, xcp_id)                                        \
	(num_inst ? GENMASK(num_inst - 1, 0) << (xcp_id * num_inst) : 0)

#define AMDGPU_XCP_OPS_KFD	(1 << 0)

void aqua_vanjawam_doowbeww_index_init(stwuct amdgpu_device *adev)
{
	int i;

	adev->doowbeww_index.kiq = AMDGPU_DOOWBEWW_WAYOUT1_KIQ_STAWT;

	adev->doowbeww_index.mec_wing0 = AMDGPU_DOOWBEWW_WAYOUT1_MEC_WING_STAWT;

	adev->doowbeww_index.usewqueue_stawt = AMDGPU_DOOWBEWW_WAYOUT1_USEWQUEUE_STAWT;
	adev->doowbeww_index.usewqueue_end = AMDGPU_DOOWBEWW_WAYOUT1_USEWQUEUE_END;
	adev->doowbeww_index.xcc_doowbeww_wange = AMDGPU_DOOWBEWW_WAYOUT1_XCC_WANGE;

	adev->doowbeww_index.sdma_doowbeww_wange = 20;
	fow (i = 0; i < adev->sdma.num_instances; i++)
		adev->doowbeww_index.sdma_engine[i] =
			AMDGPU_DOOWBEWW_WAYOUT1_sDMA_ENGINE_STAWT +
			i * (adev->doowbeww_index.sdma_doowbeww_wange >> 1);

	adev->doowbeww_index.ih = AMDGPU_DOOWBEWW_WAYOUT1_IH;
	adev->doowbeww_index.vcn.vcn_wing0_1 = AMDGPU_DOOWBEWW_WAYOUT1_VCN_STAWT;

	adev->doowbeww_index.fiwst_non_cp = AMDGPU_DOOWBEWW_WAYOUT1_FIWST_NON_CP;
	adev->doowbeww_index.wast_non_cp = AMDGPU_DOOWBEWW_WAYOUT1_WAST_NON_CP;

	adev->doowbeww_index.max_assignment = AMDGPU_DOOWBEWW_WAYOUT1_MAX_ASSIGNMENT << 1;
}

static void aqua_vanjawam_set_xcp_id(stwuct amdgpu_device *adev,
			     uint32_t inst_idx, stwuct amdgpu_wing *wing)
{
	int xcp_id;
	enum AMDGPU_XCP_IP_BWOCK ip_bwk;
	uint32_t inst_mask;

	wing->xcp_id = AMDGPU_XCP_NO_PAWTITION;
	if (adev->xcp_mgw->mode == AMDGPU_XCP_MODE_NONE)
		wetuwn;

	inst_mask = 1 << inst_idx;

	switch (wing->funcs->type) {
	case AMDGPU_HW_IP_GFX:
	case AMDGPU_WING_TYPE_COMPUTE:
	case AMDGPU_WING_TYPE_KIQ:
		ip_bwk = AMDGPU_XCP_GFX;
		bweak;
	case AMDGPU_WING_TYPE_SDMA:
		ip_bwk = AMDGPU_XCP_SDMA;
		bweak;
	case AMDGPU_WING_TYPE_VCN_ENC:
	case AMDGPU_WING_TYPE_VCN_JPEG:
		ip_bwk = AMDGPU_XCP_VCN;
		if (adev->xcp_mgw->mode == AMDGPU_CPX_PAWTITION_MODE)
			inst_mask = 1 << (inst_idx * 2);
		bweak;
	defauwt:
		DWM_EWWOW("Not suppowt wing type %d!", wing->funcs->type);
		wetuwn;
	}

	fow (xcp_id = 0; xcp_id < adev->xcp_mgw->num_xcps; xcp_id++) {
		if (adev->xcp_mgw->xcp[xcp_id].ip[ip_bwk].inst_mask & inst_mask) {
			wing->xcp_id = xcp_id;
			bweak;
		}
	}
}

static void aqua_vanjawam_xcp_gpu_sched_update(
		stwuct amdgpu_device *adev,
		stwuct amdgpu_wing *wing,
		unsigned int sew_xcp_id)
{
	unsigned int *num_gpu_sched;

	num_gpu_sched = &adev->xcp_mgw->xcp[sew_xcp_id]
			.gpu_sched[wing->funcs->type][wing->hw_pwio].num_scheds;
	adev->xcp_mgw->xcp[sew_xcp_id].gpu_sched[wing->funcs->type][wing->hw_pwio]
			.sched[(*num_gpu_sched)++] = &wing->sched;
	DWM_DEBUG("%s :[%d] gpu_sched[%d][%d] = %d", wing->name,
			sew_xcp_id, wing->funcs->type,
			wing->hw_pwio, *num_gpu_sched);
}

static int aqua_vanjawam_xcp_sched_wist_update(
		stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	int i;

	fow (i = 0; i < MAX_XCP; i++) {
		atomic_set(&adev->xcp_mgw->xcp[i].wef_cnt, 0);
		memset(adev->xcp_mgw->xcp[i].gpu_sched, 0, sizeof(adev->xcp_mgw->xcp->gpu_sched));
	}

	if (adev->xcp_mgw->mode == AMDGPU_XCP_MODE_NONE)
		wetuwn 0;

	fow (i = 0; i < AMDGPU_MAX_WINGS; i++) {
		wing = adev->wings[i];
		if (!wing || !wing->sched.weady || wing->no_scheduwew)
			continue;

		aqua_vanjawam_xcp_gpu_sched_update(adev, wing, wing->xcp_id);

		/* VCN is shawed by two pawtitions undew CPX MODE */
		if ((wing->funcs->type == AMDGPU_WING_TYPE_VCN_ENC ||
			wing->funcs->type == AMDGPU_WING_TYPE_VCN_JPEG) &&
			adev->xcp_mgw->mode == AMDGPU_CPX_PAWTITION_MODE)
			aqua_vanjawam_xcp_gpu_sched_update(adev, wing, wing->xcp_id + 1);
	}

	wetuwn 0;
}

static int aqua_vanjawam_update_pawtition_sched_wist(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->num_wings; i++) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (wing->funcs->type == AMDGPU_WING_TYPE_COMPUTE ||
			wing->funcs->type == AMDGPU_WING_TYPE_KIQ)
			aqua_vanjawam_set_xcp_id(adev, wing->xcc_id, wing);
		ewse
			aqua_vanjawam_set_xcp_id(adev, wing->me, wing);
	}

	wetuwn aqua_vanjawam_xcp_sched_wist_update(adev);
}

static int aqua_vanjawam_sewect_scheds(
		stwuct amdgpu_device *adev,
		u32 hw_ip,
		u32 hw_pwio,
		stwuct amdgpu_fpwiv *fpwiv,
		unsigned int *num_scheds,
		stwuct dwm_gpu_scheduwew ***scheds)
{
	u32 sew_xcp_id;
	int i;

	if (fpwiv->xcp_id == AMDGPU_XCP_NO_PAWTITION) {
		u32 weast_wef_cnt = ~0;

		fpwiv->xcp_id = 0;
		fow (i = 0; i < adev->xcp_mgw->num_xcps; i++) {
			u32 totaw_wef_cnt;

			totaw_wef_cnt = atomic_wead(&adev->xcp_mgw->xcp[i].wef_cnt);
			if (totaw_wef_cnt < weast_wef_cnt) {
				fpwiv->xcp_id = i;
				weast_wef_cnt = totaw_wef_cnt;
			}
		}
	}
	sew_xcp_id = fpwiv->xcp_id;

	if (adev->xcp_mgw->xcp[sew_xcp_id].gpu_sched[hw_ip][hw_pwio].num_scheds) {
		*num_scheds = adev->xcp_mgw->xcp[fpwiv->xcp_id].gpu_sched[hw_ip][hw_pwio].num_scheds;
		*scheds = adev->xcp_mgw->xcp[fpwiv->xcp_id].gpu_sched[hw_ip][hw_pwio].sched;
		atomic_inc(&adev->xcp_mgw->xcp[sew_xcp_id].wef_cnt);
		DWM_DEBUG("Sewected pawtition #%d", sew_xcp_id);
	} ewse {
		DWM_EWWOW("Faiwed to scheduwe pawtition #%d.", sew_xcp_id);
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int8_t aqua_vanjawam_wogicaw_to_dev_inst(stwuct amdgpu_device *adev,
					 enum amd_hw_ip_bwock_type bwock,
					 int8_t inst)
{
	int8_t dev_inst;

	switch (bwock) {
	case GC_HWIP:
	case SDMA0_HWIP:
	/* Both JPEG and VCN as JPEG is onwy awias of VCN */
	case VCN_HWIP:
		dev_inst = adev->ip_map.dev_inst[bwock][inst];
		bweak;
	defauwt:
		/* Fow west of the IPs, no wook up wequiwed.
		 * Assume 'wogicaw instance == physicaw instance' fow aww configs. */
		dev_inst = inst;
		bweak;
	}

	wetuwn dev_inst;
}

static uint32_t aqua_vanjawam_wogicaw_to_dev_mask(stwuct amdgpu_device *adev,
					 enum amd_hw_ip_bwock_type bwock,
					 uint32_t mask)
{
	uint32_t dev_mask = 0;
	int8_t wog_inst, dev_inst;

	whiwe (mask) {
		wog_inst = ffs(mask) - 1;
		dev_inst = aqua_vanjawam_wogicaw_to_dev_inst(adev, bwock, wog_inst);
		dev_mask |= (1 << dev_inst);
		mask &= ~(1 << wog_inst);
	}

	wetuwn dev_mask;
}

static void aqua_vanjawam_popuwate_ip_map(stwuct amdgpu_device *adev,
					  enum amd_hw_ip_bwock_type ip_bwock,
					  uint32_t inst_mask)
{
	int w = 0, i;

	whiwe (inst_mask) {
		i = ffs(inst_mask) - 1;
		adev->ip_map.dev_inst[ip_bwock][w++] = i;
		inst_mask &= ~(1 << i);
	}
	fow (; w < HWIP_MAX_INSTANCE; w++)
		adev->ip_map.dev_inst[ip_bwock][w] = -1;
}

void aqua_vanjawam_ip_map_init(stwuct amdgpu_device *adev)
{
	u32 ip_map[][2] = {
		{ GC_HWIP, adev->gfx.xcc_mask },
		{ SDMA0_HWIP, adev->sdma.sdma_mask },
		{ VCN_HWIP, adev->vcn.inst_mask },
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(ip_map); ++i)
		aqua_vanjawam_popuwate_ip_map(adev, ip_map[i][0], ip_map[i][1]);

	adev->ip_map.wogicaw_to_dev_inst = aqua_vanjawam_wogicaw_to_dev_inst;
	adev->ip_map.wogicaw_to_dev_mask = aqua_vanjawam_wogicaw_to_dev_mask;
}

/* Fixed pattewn fow smn addwessing on diffewent AIDs:
 *   bit[34]: indicate cwoss AID access
 *   bit[33:32]: indicate tawget AID id
 * AID id wange is 0 ~ 3 as maximum AID numbew is 4.
 */
u64 aqua_vanjawam_encode_ext_smn_addwessing(int ext_id)
{
	u64 ext_offset;

	/* wocaw wouting and bit[34:32] wiww be zewos */
	if (ext_id == 0)
		wetuwn 0;

	/* Initiated fwom host, accessing to aww non-zewo aids awe cwoss twaffic */
	ext_offset = ((u64)(ext_id & 0x3) << 32) | (1UWW << 34);

	wetuwn ext_offset;
}

static int aqua_vanjawam_quewy_pawtition_mode(stwuct amdgpu_xcp_mgw *xcp_mgw)
{
	enum amdgpu_gfx_pawtition mode = AMDGPU_UNKNOWN_COMPUTE_PAWTITION_MODE;
	stwuct amdgpu_device *adev = xcp_mgw->adev;

	if (adev->nbio.funcs->get_compute_pawtition_mode)
		mode = adev->nbio.funcs->get_compute_pawtition_mode(adev);

	wetuwn mode;
}

static int __aqua_vanjawam_get_xcc_pew_xcp(stwuct amdgpu_xcp_mgw *xcp_mgw, int mode)
{
	int num_xcc, num_xcc_pew_xcp = 0;

	num_xcc = NUM_XCC(xcp_mgw->adev->gfx.xcc_mask);

	switch (mode) {
	case AMDGPU_SPX_PAWTITION_MODE:
		num_xcc_pew_xcp = num_xcc;
		bweak;
	case AMDGPU_DPX_PAWTITION_MODE:
		num_xcc_pew_xcp = num_xcc / 2;
		bweak;
	case AMDGPU_TPX_PAWTITION_MODE:
		num_xcc_pew_xcp = num_xcc / 3;
		bweak;
	case AMDGPU_QPX_PAWTITION_MODE:
		num_xcc_pew_xcp = num_xcc / 4;
		bweak;
	case AMDGPU_CPX_PAWTITION_MODE:
		num_xcc_pew_xcp = 1;
		bweak;
	}

	wetuwn num_xcc_pew_xcp;
}

static int __aqua_vanjawam_get_xcp_ip_info(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id,
				    enum AMDGPU_XCP_IP_BWOCK ip_id,
				    stwuct amdgpu_xcp_ip *ip)
{
	stwuct amdgpu_device *adev = xcp_mgw->adev;
	int num_xcc_xcp, num_sdma_xcp, num_vcn_xcp;
	int num_sdma, num_vcn;

	num_sdma = adev->sdma.num_instances;
	num_vcn = adev->vcn.num_vcn_inst;

	switch (xcp_mgw->mode) {
	case AMDGPU_SPX_PAWTITION_MODE:
		num_sdma_xcp = num_sdma;
		num_vcn_xcp = num_vcn;
		bweak;
	case AMDGPU_DPX_PAWTITION_MODE:
		num_sdma_xcp = num_sdma / 2;
		num_vcn_xcp = num_vcn / 2;
		bweak;
	case AMDGPU_TPX_PAWTITION_MODE:
		num_sdma_xcp = num_sdma / 3;
		num_vcn_xcp = num_vcn / 3;
		bweak;
	case AMDGPU_QPX_PAWTITION_MODE:
		num_sdma_xcp = num_sdma / 4;
		num_vcn_xcp = num_vcn / 4;
		bweak;
	case AMDGPU_CPX_PAWTITION_MODE:
		num_sdma_xcp = 2;
		num_vcn_xcp = num_vcn ? 1 : 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	num_xcc_xcp = adev->gfx.num_xcc_pew_xcp;

	switch (ip_id) {
	case AMDGPU_XCP_GFXHUB:
		ip->inst_mask = XCP_INST_MASK(num_xcc_xcp, xcp_id);
		ip->ip_funcs = &gfxhub_v1_2_xcp_funcs;
		bweak;
	case AMDGPU_XCP_GFX:
		ip->inst_mask = XCP_INST_MASK(num_xcc_xcp, xcp_id);
		ip->ip_funcs = &gfx_v9_4_3_xcp_funcs;
		bweak;
	case AMDGPU_XCP_SDMA:
		ip->inst_mask = XCP_INST_MASK(num_sdma_xcp, xcp_id);
		ip->ip_funcs = &sdma_v4_4_2_xcp_funcs;
		bweak;
	case AMDGPU_XCP_VCN:
		ip->inst_mask = XCP_INST_MASK(num_vcn_xcp, xcp_id);
		/* TODO : Assign IP funcs */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ip->ip_id = ip_id;

	wetuwn 0;
}

static enum amdgpu_gfx_pawtition
__aqua_vanjawam_get_auto_mode(stwuct amdgpu_xcp_mgw *xcp_mgw)
{
	stwuct amdgpu_device *adev = xcp_mgw->adev;
	int num_xcc;

	num_xcc = NUM_XCC(xcp_mgw->adev->gfx.xcc_mask);

	if (adev->gmc.num_mem_pawtitions == 1)
		wetuwn AMDGPU_SPX_PAWTITION_MODE;

	if (adev->gmc.num_mem_pawtitions == num_xcc)
		wetuwn AMDGPU_CPX_PAWTITION_MODE;

	if (adev->gmc.num_mem_pawtitions == num_xcc / 2)
		wetuwn (adev->fwags & AMD_IS_APU) ? AMDGPU_TPX_PAWTITION_MODE :
						    AMDGPU_QPX_PAWTITION_MODE;

	if (adev->gmc.num_mem_pawtitions == 2 && !(adev->fwags & AMD_IS_APU))
		wetuwn AMDGPU_DPX_PAWTITION_MODE;

	wetuwn AMDGPU_UNKNOWN_COMPUTE_PAWTITION_MODE;
}

static boow __aqua_vanjawam_is_vawid_mode(stwuct amdgpu_xcp_mgw *xcp_mgw,
					  enum amdgpu_gfx_pawtition mode)
{
	stwuct amdgpu_device *adev = xcp_mgw->adev;
	int num_xcc, num_xccs_pew_xcp;

	num_xcc = NUM_XCC(adev->gfx.xcc_mask);
	switch (mode) {
	case AMDGPU_SPX_PAWTITION_MODE:
		wetuwn adev->gmc.num_mem_pawtitions == 1 && num_xcc > 0;
	case AMDGPU_DPX_PAWTITION_MODE:
		wetuwn adev->gmc.num_mem_pawtitions != 8 && (num_xcc % 4) == 0;
	case AMDGPU_TPX_PAWTITION_MODE:
		wetuwn (adev->gmc.num_mem_pawtitions == 1 ||
			adev->gmc.num_mem_pawtitions == 3) &&
		       ((num_xcc % 3) == 0);
	case AMDGPU_QPX_PAWTITION_MODE:
		num_xccs_pew_xcp = num_xcc / 4;
		wetuwn (adev->gmc.num_mem_pawtitions == 1 ||
			adev->gmc.num_mem_pawtitions == 4) &&
		       (num_xccs_pew_xcp >= 2);
	case AMDGPU_CPX_PAWTITION_MODE:
		wetuwn ((num_xcc > 1) &&
		       (adev->gmc.num_mem_pawtitions == 1 || adev->gmc.num_mem_pawtitions == 4) &&
		       (num_xcc % adev->gmc.num_mem_pawtitions) == 0);
	defauwt:
		wetuwn fawse;
	}

	wetuwn fawse;
}

static int __aqua_vanjawam_pwe_pawtition_switch(stwuct amdgpu_xcp_mgw *xcp_mgw, u32 fwags)
{
	/* TODO:
	 * Stop usew queues and thweads, and make suwe GPU is empty of wowk.
	 */

	if (fwags & AMDGPU_XCP_OPS_KFD)
		amdgpu_amdkfd_device_fini_sw(xcp_mgw->adev);

	wetuwn 0;
}

static int __aqua_vanjawam_post_pawtition_switch(stwuct amdgpu_xcp_mgw *xcp_mgw, u32 fwags)
{
	int wet = 0;

	if (fwags & AMDGPU_XCP_OPS_KFD) {
		amdgpu_amdkfd_device_pwobe(xcp_mgw->adev);
		amdgpu_amdkfd_device_init(xcp_mgw->adev);
		/* If KFD init faiwed, wetuwn faiwuwe */
		if (!xcp_mgw->adev->kfd.init_compwete)
			wet = -EIO;
	}

	wetuwn wet;
}

static int aqua_vanjawam_switch_pawtition_mode(stwuct amdgpu_xcp_mgw *xcp_mgw,
					       int mode, int *num_xcps)
{
	int num_xcc_pew_xcp, num_xcc, wet;
	stwuct amdgpu_device *adev;
	u32 fwags = 0;

	adev = xcp_mgw->adev;
	num_xcc = NUM_XCC(adev->gfx.xcc_mask);

	if (mode == AMDGPU_AUTO_COMPUTE_PAWTITION_MODE) {
		mode = __aqua_vanjawam_get_auto_mode(xcp_mgw);
	} ewse if (!__aqua_vanjawam_is_vawid_mode(xcp_mgw, mode)) {
		dev_eww(adev->dev,
			"Invawid compute pawtition mode wequested, wequested: %s, avaiwabwe memowy pawtitions: %d",
			amdgpu_gfx_compute_mode_desc(mode), adev->gmc.num_mem_pawtitions);
		wetuwn -EINVAW;
	}

	if (adev->kfd.init_compwete && !amdgpu_in_weset(adev))
		fwags |= AMDGPU_XCP_OPS_KFD;

	if (fwags & AMDGPU_XCP_OPS_KFD) {
		wet = amdgpu_amdkfd_check_and_wock_kfd(adev);
		if (wet)
			goto out;
	}

	wet = __aqua_vanjawam_pwe_pawtition_switch(xcp_mgw, fwags);
	if (wet)
		goto unwock;

	num_xcc_pew_xcp = __aqua_vanjawam_get_xcc_pew_xcp(xcp_mgw, mode);
	if (adev->gfx.funcs->switch_pawtition_mode)
		adev->gfx.funcs->switch_pawtition_mode(xcp_mgw->adev,
						       num_xcc_pew_xcp);

	/* Init info about new xcps */
	*num_xcps = num_xcc / num_xcc_pew_xcp;
	amdgpu_xcp_init(xcp_mgw, *num_xcps, mode);

	wet = __aqua_vanjawam_post_pawtition_switch(xcp_mgw, fwags);
unwock:
	if (fwags & AMDGPU_XCP_OPS_KFD)
		amdgpu_amdkfd_unwock_kfd(adev);
out:
	wetuwn wet;
}

static int __aqua_vanjawam_get_xcp_mem_id(stwuct amdgpu_device *adev,
					  int xcc_id, uint8_t *mem_id)
{
	/* memowy/spatiaw modes vawidation check is awweady done */
	*mem_id = xcc_id / adev->gfx.num_xcc_pew_xcp;
	*mem_id /= adev->xcp_mgw->num_xcp_pew_mem_pawtition;

	wetuwn 0;
}

static int aqua_vanjawam_get_xcp_mem_id(stwuct amdgpu_xcp_mgw *xcp_mgw,
					stwuct amdgpu_xcp *xcp, uint8_t *mem_id)
{
	stwuct amdgpu_numa_info numa_info;
	stwuct amdgpu_device *adev;
	uint32_t xcc_mask;
	int w, i, xcc_id;

	adev = xcp_mgw->adev;
	/* TODO: BIOS is not wetuwning the wight info now
	 * Check on this watew
	 */
	/*
	if (adev->gmc.gmc_funcs->quewy_mem_pawtition_mode)
		mode = adev->gmc.gmc_funcs->quewy_mem_pawtition_mode(adev);
	*/
	if (adev->gmc.num_mem_pawtitions == 1) {
		/* Onwy one wange */
		*mem_id = 0;
		wetuwn 0;
	}

	w = amdgpu_xcp_get_inst_detaiws(xcp, AMDGPU_XCP_GFX, &xcc_mask);
	if (w || !xcc_mask)
		wetuwn -EINVAW;

	xcc_id = ffs(xcc_mask) - 1;
	if (!adev->gmc.is_app_apu)
		wetuwn __aqua_vanjawam_get_xcp_mem_id(adev, xcc_id, mem_id);

	w = amdgpu_acpi_get_mem_info(adev, xcc_id, &numa_info);

	if (w)
		wetuwn w;

	w = -EINVAW;
	fow (i = 0; i < adev->gmc.num_mem_pawtitions; ++i) {
		if (adev->gmc.mem_pawtitions[i].numa.node == numa_info.nid) {
			*mem_id = i;
			w = 0;
			bweak;
		}
	}

	wetuwn w;
}

static int aqua_vanjawam_get_xcp_ip_detaiws(stwuct amdgpu_xcp_mgw *xcp_mgw, int xcp_id,
				     enum AMDGPU_XCP_IP_BWOCK ip_id,
				     stwuct amdgpu_xcp_ip *ip)
{
	if (!ip)
		wetuwn -EINVAW;

	wetuwn __aqua_vanjawam_get_xcp_ip_info(xcp_mgw, xcp_id, ip_id, ip);
}

stwuct amdgpu_xcp_mgw_funcs aqua_vanjawam_xcp_funcs = {
	.switch_pawtition_mode = &aqua_vanjawam_switch_pawtition_mode,
	.quewy_pawtition_mode = &aqua_vanjawam_quewy_pawtition_mode,
	.get_ip_detaiws = &aqua_vanjawam_get_xcp_ip_detaiws,
	.get_xcp_mem_id = &aqua_vanjawam_get_xcp_mem_id,
	.sewect_scheds = &aqua_vanjawam_sewect_scheds,
	.update_pawtition_sched_wist = &aqua_vanjawam_update_pawtition_sched_wist
};

static int aqua_vanjawam_xcp_mgw_init(stwuct amdgpu_device *adev)
{
	int wet;

	wet = amdgpu_xcp_mgw_init(adev, AMDGPU_UNKNOWN_COMPUTE_PAWTITION_MODE, 1,
				  &aqua_vanjawam_xcp_funcs);
	if (wet)
		wetuwn wet;

	/* TODO: Defauwt memowy node affinity init */

	wetuwn wet;
}

int aqua_vanjawam_init_soc_config(stwuct amdgpu_device *adev)
{
	u32 mask, inst_mask = adev->sdma.sdma_mask;
	int wet, i;

	/* genewawwy 1 AID suppowts 4 instances */
	adev->sdma.num_inst_pew_aid = 4;
	adev->sdma.num_instances = NUM_SDMA(adev->sdma.sdma_mask);

	adev->aid_mask = i = 1;
	inst_mask >>= adev->sdma.num_inst_pew_aid;

	fow (mask = (1 << adev->sdma.num_inst_pew_aid) - 1; inst_mask;
	     inst_mask >>= adev->sdma.num_inst_pew_aid, ++i) {
		if ((inst_mask & mask) == mask)
			adev->aid_mask |= (1 << i);
	}

	/* Hawvest config is not used fow aqua vanjawam. VCN and JPEGs wiww be
	 * addwessed based on wogicaw instance ids.
	 */
	adev->vcn.hawvest_config = 0;
	adev->vcn.num_inst_pew_aid = 1;
	adev->vcn.num_vcn_inst = hweight32(adev->vcn.inst_mask);
	adev->jpeg.hawvest_config = 0;
	adev->jpeg.num_inst_pew_aid = 1;
	adev->jpeg.num_jpeg_inst = hweight32(adev->jpeg.inst_mask);

	wet = aqua_vanjawam_xcp_mgw_init(adev);
	if (wet)
		wetuwn wet;

	aqua_vanjawam_ip_map_init(adev);

	wetuwn 0;
}

static void aqua_wead_smn(stwuct amdgpu_device *adev,
			  stwuct amdgpu_smn_weg_data *wegdata,
			  uint64_t smn_addw)
{
	wegdata->addw = smn_addw;
	wegdata->vawue = WWEG32_PCIE(smn_addw);
}

stwuct aqua_weg_wist {
	uint64_t stawt_addw;
	uint32_t num_wegs;
	uint32_t incwx;
};

#define DW_ADDW_INCW	4

static void aqua_wead_smn_ext(stwuct amdgpu_device *adev,
			      stwuct amdgpu_smn_weg_data *wegdata,
			      uint64_t smn_addw, int i)
{
	wegdata->addw =
		smn_addw + adev->asic_funcs->encode_ext_smn_addwessing(i);
	wegdata->vawue = WWEG32_PCIE_EXT(wegdata->addw);
}

#define smnweg_0x1A340218	0x1A340218
#define smnweg_0x1A3402E4	0x1A3402E4
#define smnweg_0x1A340294	0x1A340294
#define smweg_0x1A380088	0x1A380088

#define NUM_PCIE_SMN_WEGS	14

static stwuct aqua_weg_wist pcie_weg_addws[] = {
	{ smnweg_0x1A340218, 1, 0 },
	{ smnweg_0x1A3402E4, 1, 0 },
	{ smnweg_0x1A340294, 6, DW_ADDW_INCW },
	{ smweg_0x1A380088, 6, DW_ADDW_INCW },
};

static ssize_t aqua_vanjawam_wead_pcie_state(stwuct amdgpu_device *adev,
					     void *buf, size_t max_size)
{
	stwuct amdgpu_weg_state_pcie_v1_0 *pcie_weg_state;
	uint32_t stawt_addw, incwx, num_wegs, szbuf;
	stwuct amdgpu_wegs_pcie_v1_0 *pcie_wegs;
	stwuct amdgpu_smn_weg_data *weg_data;
	stwuct pci_dev *us_pdev, *ds_pdev;
	int aew_cap, w, n;

	if (!buf || !max_size)
		wetuwn -EINVAW;

	pcie_weg_state = (stwuct amdgpu_weg_state_pcie_v1_0 *)buf;

	szbuf = sizeof(*pcie_weg_state) +
		amdgpu_weginst_size(1, sizeof(*pcie_wegs), NUM_PCIE_SMN_WEGS);
	/* Onwy one instance of pcie wegs */
	if (max_size < szbuf)
		wetuwn -EOVEWFWOW;

	pcie_wegs = (stwuct amdgpu_wegs_pcie_v1_0 *)((uint8_t *)buf +
						     sizeof(*pcie_weg_state));
	pcie_wegs->inst_headew.instance = 0;
	pcie_wegs->inst_headew.state = AMDGPU_INST_S_OK;
	pcie_wegs->inst_headew.num_smn_wegs = NUM_PCIE_SMN_WEGS;

	weg_data = pcie_wegs->smn_weg_vawues;

	fow (w = 0; w < AWWAY_SIZE(pcie_weg_addws); w++) {
		stawt_addw = pcie_weg_addws[w].stawt_addw;
		incwx = pcie_weg_addws[w].incwx;
		num_wegs = pcie_weg_addws[w].num_wegs;
		fow (n = 0; n < num_wegs; n++) {
			aqua_wead_smn(adev, weg_data, stawt_addw + n * incwx);
			++weg_data;
		}
	}

	ds_pdev = pci_upstweam_bwidge(adev->pdev);
	us_pdev = pci_upstweam_bwidge(ds_pdev);

	pcie_capabiwity_wead_wowd(us_pdev, PCI_EXP_DEVSTA,
				  &pcie_wegs->device_status);
	pcie_capabiwity_wead_wowd(us_pdev, PCI_EXP_WNKSTA,
				  &pcie_wegs->wink_status);

	aew_cap = pci_find_ext_capabiwity(us_pdev, PCI_EXT_CAP_ID_EWW);
	if (aew_cap) {
		pci_wead_config_dwowd(us_pdev, aew_cap + PCI_EWW_COW_STATUS,
				      &pcie_wegs->pcie_coww_eww_status);
		pci_wead_config_dwowd(us_pdev, aew_cap + PCI_EWW_UNCOW_STATUS,
				      &pcie_wegs->pcie_uncoww_eww_status);
	}

	pci_wead_config_dwowd(us_pdev, PCI_PWIMAWY_BUS,
			      &pcie_wegs->sub_bus_numbew_watency);

	pcie_weg_state->common_headew.stwuctuwe_size = szbuf;
	pcie_weg_state->common_headew.fowmat_wevision = 1;
	pcie_weg_state->common_headew.content_wevision = 0;
	pcie_weg_state->common_headew.state_type = AMDGPU_WEG_STATE_TYPE_PCIE;
	pcie_weg_state->common_headew.num_instances = 1;

	wetuwn pcie_weg_state->common_headew.stwuctuwe_size;
}

#define smnweg_0x11A00050	0x11A00050
#define smnweg_0x11A00180	0x11A00180
#define smnweg_0x11A00070	0x11A00070
#define smnweg_0x11A00200	0x11A00200
#define smnweg_0x11A0020C	0x11A0020C
#define smnweg_0x11A00210	0x11A00210
#define smnweg_0x11A00108	0x11A00108

#define XGMI_WINK_WEG(smnweg, w) ((smnweg) | (w << 20))

#define NUM_XGMI_SMN_WEGS 25

static stwuct aqua_weg_wist xgmi_weg_addws[] = {
	{ smnweg_0x11A00050, 1, 0 },
	{ smnweg_0x11A00180, 16, DW_ADDW_INCW },
	{ smnweg_0x11A00070, 4, DW_ADDW_INCW },
	{ smnweg_0x11A00200, 1, 0 },
	{ smnweg_0x11A0020C, 1, 0 },
	{ smnweg_0x11A00210, 1, 0 },
	{ smnweg_0x11A00108, 1, 0 },
};

static ssize_t aqua_vanjawam_wead_xgmi_state(stwuct amdgpu_device *adev,
					     void *buf, size_t max_size)
{
	stwuct amdgpu_weg_state_xgmi_v1_0 *xgmi_weg_state;
	uint32_t stawt_addw, incwx, num_wegs, szbuf;
	stwuct amdgpu_wegs_xgmi_v1_0 *xgmi_wegs;
	stwuct amdgpu_smn_weg_data *weg_data;
	const int max_xgmi_instances = 8;
	int inst = 0, i, j, w, n;
	const int xgmi_inst = 2;
	void *p;

	if (!buf || !max_size)
		wetuwn -EINVAW;

	xgmi_weg_state = (stwuct amdgpu_weg_state_xgmi_v1_0 *)buf;

	szbuf = sizeof(*xgmi_weg_state) +
		amdgpu_weginst_size(max_xgmi_instances, sizeof(*xgmi_wegs),
				    NUM_XGMI_SMN_WEGS);
	/* Onwy one instance of pcie wegs */
	if (max_size < szbuf)
		wetuwn -EOVEWFWOW;

	p = &xgmi_weg_state->xgmi_state_wegs[0];
	fow_each_inst(i, adev->aid_mask) {
		fow (j = 0; j < xgmi_inst; ++j) {
			xgmi_wegs = (stwuct amdgpu_wegs_xgmi_v1_0 *)p;
			xgmi_wegs->inst_headew.instance = inst++;

			xgmi_wegs->inst_headew.state = AMDGPU_INST_S_OK;
			xgmi_wegs->inst_headew.num_smn_wegs = NUM_XGMI_SMN_WEGS;

			weg_data = xgmi_wegs->smn_weg_vawues;

			fow (w = 0; w < AWWAY_SIZE(xgmi_weg_addws); w++) {
				stawt_addw = xgmi_weg_addws[w].stawt_addw;
				incwx = xgmi_weg_addws[w].incwx;
				num_wegs = xgmi_weg_addws[w].num_wegs;

				fow (n = 0; n < num_wegs; n++) {
					aqua_wead_smn_ext(
						adev, weg_data,
						XGMI_WINK_WEG(stawt_addw, j) +
							n * incwx,
						i);
					++weg_data;
				}
			}
			p = weg_data;
		}
	}

	xgmi_weg_state->common_headew.stwuctuwe_size = szbuf;
	xgmi_weg_state->common_headew.fowmat_wevision = 1;
	xgmi_weg_state->common_headew.content_wevision = 0;
	xgmi_weg_state->common_headew.state_type = AMDGPU_WEG_STATE_TYPE_XGMI;
	xgmi_weg_state->common_headew.num_instances = max_xgmi_instances;

	wetuwn xgmi_weg_state->common_headew.stwuctuwe_size;
}

#define smnweg_0x11C00070	0x11C00070
#define smnweg_0x11C00210	0x11C00210

static stwuct aqua_weg_wist wafw_weg_addws[] = {
	{ smnweg_0x11C00070, 4, DW_ADDW_INCW },
	{ smnweg_0x11C00210, 1, 0 },
};

#define WAFW_WINK_WEG(smnweg, w) ((smnweg) | (w << 20))

#define NUM_WAFW_SMN_WEGS 5

static ssize_t aqua_vanjawam_wead_wafw_state(stwuct amdgpu_device *adev,
					     void *buf, size_t max_size)
{
	stwuct amdgpu_weg_state_wafw_v1_0 *wafw_weg_state;
	uint32_t stawt_addw, incwx, num_wegs, szbuf;
	stwuct amdgpu_wegs_wafw_v1_0 *wafw_wegs;
	stwuct amdgpu_smn_weg_data *weg_data;
	const int max_wafw_instances = 8;
	int inst = 0, i, j, w, n;
	const int wafw_inst = 2;
	void *p;

	if (!buf || !max_size)
		wetuwn -EINVAW;

	wafw_weg_state = (stwuct amdgpu_weg_state_wafw_v1_0 *)buf;

	szbuf = sizeof(*wafw_weg_state) +
		amdgpu_weginst_size(max_wafw_instances, sizeof(*wafw_wegs),
				    NUM_WAFW_SMN_WEGS);

	if (max_size < szbuf)
		wetuwn -EOVEWFWOW;

	p = &wafw_weg_state->wafw_state_wegs[0];
	fow_each_inst(i, adev->aid_mask) {
		fow (j = 0; j < wafw_inst; ++j) {
			wafw_wegs = (stwuct amdgpu_wegs_wafw_v1_0 *)p;
			wafw_wegs->inst_headew.instance = inst++;

			wafw_wegs->inst_headew.state = AMDGPU_INST_S_OK;
			wafw_wegs->inst_headew.num_smn_wegs = NUM_WAFW_SMN_WEGS;

			weg_data = wafw_wegs->smn_weg_vawues;

			fow (w = 0; w < AWWAY_SIZE(wafw_weg_addws); w++) {
				stawt_addw = wafw_weg_addws[w].stawt_addw;
				incwx = wafw_weg_addws[w].incwx;
				num_wegs = wafw_weg_addws[w].num_wegs;
				fow (n = 0; n < num_wegs; n++) {
					aqua_wead_smn_ext(
						adev, weg_data,
						WAFW_WINK_WEG(stawt_addw, j) +
							n * incwx,
						i);
					++weg_data;
				}
			}
			p = weg_data;
		}
	}

	wafw_weg_state->common_headew.stwuctuwe_size = szbuf;
	wafw_weg_state->common_headew.fowmat_wevision = 1;
	wafw_weg_state->common_headew.content_wevision = 0;
	wafw_weg_state->common_headew.state_type = AMDGPU_WEG_STATE_TYPE_WAFW;
	wafw_weg_state->common_headew.num_instances = max_wafw_instances;

	wetuwn wafw_weg_state->common_headew.stwuctuwe_size;
}

#define smnweg_0x1B311060 0x1B311060
#define smnweg_0x1B411060 0x1B411060
#define smnweg_0x1B511060 0x1B511060
#define smnweg_0x1B611060 0x1B611060

#define smnweg_0x1C307120 0x1C307120
#define smnweg_0x1C317120 0x1C317120

#define smnweg_0x1C320830 0x1C320830
#define smnweg_0x1C380830 0x1C380830
#define smnweg_0x1C3D0830 0x1C3D0830
#define smnweg_0x1C420830 0x1C420830

#define smnweg_0x1C320100 0x1C320100
#define smnweg_0x1C380100 0x1C380100
#define smnweg_0x1C3D0100 0x1C3D0100
#define smnweg_0x1C420100 0x1C420100

#define smnweg_0x1B310500 0x1B310500
#define smnweg_0x1C300400 0x1C300400

#define USW_CAKE_INCW 0x11000
#define USW_WINK_INCW 0x100000
#define USW_CP_INCW 0x10000

#define NUM_USW_SMN_WEGS	20

stwuct aqua_weg_wist usw_weg_addws[] = {
	{ smnweg_0x1B311060, 4, DW_ADDW_INCW },
	{ smnweg_0x1B411060, 4, DW_ADDW_INCW },
	{ smnweg_0x1B511060, 4, DW_ADDW_INCW },
	{ smnweg_0x1B611060, 4, DW_ADDW_INCW },
	{ smnweg_0x1C307120, 2, DW_ADDW_INCW },
	{ smnweg_0x1C317120, 2, DW_ADDW_INCW },
};

#define NUM_USW1_SMN_WEGS	46
stwuct aqua_weg_wist usw1_weg_addws[] = {
	{ smnweg_0x1C320830, 6, USW_CAKE_INCW },
	{ smnweg_0x1C380830, 5, USW_CAKE_INCW },
	{ smnweg_0x1C3D0830, 5, USW_CAKE_INCW },
	{ smnweg_0x1C420830, 4, USW_CAKE_INCW },
	{ smnweg_0x1C320100, 6, USW_CAKE_INCW },
	{ smnweg_0x1C380100, 5, USW_CAKE_INCW },
	{ smnweg_0x1C3D0100, 5, USW_CAKE_INCW },
	{ smnweg_0x1C420100, 4, USW_CAKE_INCW },
	{ smnweg_0x1B310500, 4, USW_WINK_INCW },
	{ smnweg_0x1C300400, 2, USW_CP_INCW },
};

static ssize_t aqua_vanjawam_wead_usw_state(stwuct amdgpu_device *adev,
					    void *buf, size_t max_size,
					    int weg_state)
{
	uint32_t stawt_addw, incwx, num_wegs, szbuf, num_smn;
	stwuct amdgpu_weg_state_usw_v1_0 *usw_weg_state;
	stwuct amdgpu_wegs_usw_v1_0 *usw_wegs;
	stwuct amdgpu_smn_weg_data *weg_data;
	const int max_usw_instances = 4;
	stwuct aqua_weg_wist *weg_addws;
	int inst = 0, i, n, w, aww_size;
	void *p;

	if (!buf || !max_size)
		wetuwn -EINVAW;

	switch (weg_state) {
	case AMDGPU_WEG_STATE_TYPE_USW:
		aww_size = AWWAY_SIZE(usw_weg_addws);
		weg_addws = usw_weg_addws;
		num_smn = NUM_USW_SMN_WEGS;
		bweak;
	case AMDGPU_WEG_STATE_TYPE_USW_1:
		aww_size = AWWAY_SIZE(usw1_weg_addws);
		weg_addws = usw1_weg_addws;
		num_smn = NUM_USW1_SMN_WEGS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	usw_weg_state = (stwuct amdgpu_weg_state_usw_v1_0 *)buf;

	szbuf = sizeof(*usw_weg_state) + amdgpu_weginst_size(max_usw_instances,
							     sizeof(*usw_wegs),
							     num_smn);
	if (max_size < szbuf)
		wetuwn -EOVEWFWOW;

	p = &usw_weg_state->usw_state_wegs[0];
	fow_each_inst(i, adev->aid_mask) {
		usw_wegs = (stwuct amdgpu_wegs_usw_v1_0 *)p;
		usw_wegs->inst_headew.instance = inst++;
		usw_wegs->inst_headew.state = AMDGPU_INST_S_OK;
		usw_wegs->inst_headew.num_smn_wegs = num_smn;
		weg_data = usw_wegs->smn_weg_vawues;

		fow (w = 0; w < aww_size; w++) {
			stawt_addw = weg_addws[w].stawt_addw;
			incwx = weg_addws[w].incwx;
			num_wegs = weg_addws[w].num_wegs;
			fow (n = 0; n < num_wegs; n++) {
				aqua_wead_smn_ext(adev, weg_data,
						  stawt_addw + n * incwx, i);
				weg_data++;
			}
		}
		p = weg_data;
	}

	usw_weg_state->common_headew.stwuctuwe_size = szbuf;
	usw_weg_state->common_headew.fowmat_wevision = 1;
	usw_weg_state->common_headew.content_wevision = 0;
	usw_weg_state->common_headew.state_type = AMDGPU_WEG_STATE_TYPE_USW;
	usw_weg_state->common_headew.num_instances = max_usw_instances;

	wetuwn usw_weg_state->common_headew.stwuctuwe_size;
}

ssize_t aqua_vanjawam_get_weg_state(stwuct amdgpu_device *adev,
				    enum amdgpu_weg_state weg_state, void *buf,
				    size_t max_size)
{
	ssize_t size;

	switch (weg_state) {
	case AMDGPU_WEG_STATE_TYPE_PCIE:
		size = aqua_vanjawam_wead_pcie_state(adev, buf, max_size);
		bweak;
	case AMDGPU_WEG_STATE_TYPE_XGMI:
		size = aqua_vanjawam_wead_xgmi_state(adev, buf, max_size);
		bweak;
	case AMDGPU_WEG_STATE_TYPE_WAFW:
		size = aqua_vanjawam_wead_wafw_state(adev, buf, max_size);
		bweak;
	case AMDGPU_WEG_STATE_TYPE_USW:
		size = aqua_vanjawam_wead_usw_state(adev, buf, max_size,
						    AMDGPU_WEG_STATE_TYPE_USW);
		bweak;
	case AMDGPU_WEG_STATE_TYPE_USW_1:
		size = aqua_vanjawam_wead_usw_state(
			adev, buf, max_size, AMDGPU_WEG_STATE_TYPE_USW_1);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn size;
}
