/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#incwude <winux/fiwmwawe.h>
#incwude "amdgpu.h"
#incwude "amdgpu_vcn.h"
#incwude "amdgpu_pm.h"
#incwude "amdgpu_cs.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "vcn_v2_0.h"
#incwude "mmsch_v3_0.h"
#incwude "vcn_sw_wing.h"

#incwude "vcn/vcn_3_0_0_offset.h"
#incwude "vcn/vcn_3_0_0_sh_mask.h"
#incwude "ivswcid/vcn/iwqswcs_vcn_2_0.h"

#incwude <dwm/dwm_dwv.h>

#define VCN_VID_SOC_ADDWESS_2_0					0x1fa00
#define VCN1_VID_SOC_ADDWESS_3_0				0x48200

#define mmUVD_CONTEXT_ID_INTEWNAW_OFFSET			0x27
#define mmUVD_GPCOM_VCPU_CMD_INTEWNAW_OFFSET			0x0f
#define mmUVD_GPCOM_VCPU_DATA0_INTEWNAW_OFFSET			0x10
#define mmUVD_GPCOM_VCPU_DATA1_INTEWNAW_OFFSET			0x11
#define mmUVD_NO_OP_INTEWNAW_OFFSET				0x29
#define mmUVD_GP_SCWATCH8_INTEWNAW_OFFSET			0x66
#define mmUVD_SCWATCH9_INTEWNAW_OFFSET				0xc01d

#define mmUVD_WMI_WBC_IB_VMID_INTEWNAW_OFFSET			0x431
#define mmUVD_WMI_WBC_IB_64BIT_BAW_WOW_INTEWNAW_OFFSET		0x3b4
#define mmUVD_WMI_WBC_IB_64BIT_BAW_HIGH_INTEWNAW_OFFSET		0x3b5
#define mmUVD_WBC_IB_SIZE_INTEWNAW_OFFSET			0x25c

#define VCN_INSTANCES_SIENNA_CICHWID				2
#define DEC_SW_WING_ENABWED					FAWSE

#define WDECODE_MSG_CWEATE					0x00000000
#define WDECODE_MESSAGE_CWEATE					0x00000001

static int amdgpu_ih_cwientid_vcns[] = {
	SOC15_IH_CWIENTID_VCN,
	SOC15_IH_CWIENTID_VCN1
};

static int vcn_v3_0_stawt_swiov(stwuct amdgpu_device *adev);
static void vcn_v3_0_set_dec_wing_funcs(stwuct amdgpu_device *adev);
static void vcn_v3_0_set_enc_wing_funcs(stwuct amdgpu_device *adev);
static void vcn_v3_0_set_iwq_funcs(stwuct amdgpu_device *adev);
static int vcn_v3_0_set_powewgating_state(void *handwe,
			enum amd_powewgating_state state);
static int vcn_v3_0_pause_dpg_mode(stwuct amdgpu_device *adev,
			int inst_idx, stwuct dpg_pause_state *new_state);

static void vcn_v3_0_dec_wing_set_wptw(stwuct amdgpu_wing *wing);
static void vcn_v3_0_enc_wing_set_wptw(stwuct amdgpu_wing *wing);

/**
 * vcn_v3_0_eawwy_init - set function pointews and woad micwocode
 *
 * @handwe: amdgpu_device pointew
 *
 * Set wing and iwq function pointews
 * Woad micwocode fwom fiwesystem
 */
static int vcn_v3_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev)) {
		adev->vcn.num_vcn_inst = VCN_INSTANCES_SIENNA_CICHWID;
		adev->vcn.hawvest_config = 0;
		adev->vcn.num_enc_wings = 1;

	} ewse {
		if (adev->vcn.hawvest_config == (AMDGPU_VCN_HAWVEST_VCN0 |
						 AMDGPU_VCN_HAWVEST_VCN1))
			/* both instances awe hawvested, disabwe the bwock */
			wetuwn -ENOENT;

		if (amdgpu_ip_vewsion(adev, UVD_HWIP, 0) ==
		    IP_VEWSION(3, 0, 33))
			adev->vcn.num_enc_wings = 0;
		ewse
			adev->vcn.num_enc_wings = 2;
	}

	vcn_v3_0_set_dec_wing_funcs(adev);
	vcn_v3_0_set_enc_wing_funcs(adev);
	vcn_v3_0_set_iwq_funcs(adev);

	wetuwn amdgpu_vcn_eawwy_init(adev);
}

/**
 * vcn_v3_0_sw_init - sw init fow VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Woad fiwmwawe and sw initiawization
 */
static int vcn_v3_0_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	int i, j, w;
	int vcn_doowbeww_index = 0;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_vcn_sw_init(adev);
	if (w)
		wetuwn w;

	amdgpu_vcn_setup_ucode(adev);

	w = amdgpu_vcn_wesume(adev);
	if (w)
		wetuwn w;

	/*
	 * Note: doowbeww assignment is fixed fow SWIOV muwtipwe VCN engines
	 * Fowmuwa:
	 *   vcn_db_base  = adev->doowbeww_index.vcn.vcn_wing0_1 << 1;
	 *   dec_wing_i   = vcn_db_base + i * (adev->vcn.num_enc_wings + 1)
	 *   enc_wing_i,j = vcn_db_base + i * (adev->vcn.num_enc_wings + 1) + 1 + j
	 */
	if (amdgpu_swiov_vf(adev)) {
		vcn_doowbeww_index = adev->doowbeww_index.vcn.vcn_wing0_1;
		/* get DWOWD offset */
		vcn_doowbeww_index = vcn_doowbeww_index << 1;
	}

	fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
		vowatiwe stwuct amdgpu_fw_shawed *fw_shawed;

		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		adev->vcn.intewnaw.context_id = mmUVD_CONTEXT_ID_INTEWNAW_OFFSET;
		adev->vcn.intewnaw.ib_vmid = mmUVD_WMI_WBC_IB_VMID_INTEWNAW_OFFSET;
		adev->vcn.intewnaw.ib_baw_wow = mmUVD_WMI_WBC_IB_64BIT_BAW_WOW_INTEWNAW_OFFSET;
		adev->vcn.intewnaw.ib_baw_high = mmUVD_WMI_WBC_IB_64BIT_BAW_HIGH_INTEWNAW_OFFSET;
		adev->vcn.intewnaw.ib_size = mmUVD_WBC_IB_SIZE_INTEWNAW_OFFSET;
		adev->vcn.intewnaw.gp_scwatch8 = mmUVD_GP_SCWATCH8_INTEWNAW_OFFSET;

		adev->vcn.intewnaw.scwatch9 = mmUVD_SCWATCH9_INTEWNAW_OFFSET;
		adev->vcn.inst[i].extewnaw.scwatch9 = SOC15_WEG_OFFSET(VCN, i, mmUVD_SCWATCH9);
		adev->vcn.intewnaw.data0 = mmUVD_GPCOM_VCPU_DATA0_INTEWNAW_OFFSET;
		adev->vcn.inst[i].extewnaw.data0 = SOC15_WEG_OFFSET(VCN, i, mmUVD_GPCOM_VCPU_DATA0);
		adev->vcn.intewnaw.data1 = mmUVD_GPCOM_VCPU_DATA1_INTEWNAW_OFFSET;
		adev->vcn.inst[i].extewnaw.data1 = SOC15_WEG_OFFSET(VCN, i, mmUVD_GPCOM_VCPU_DATA1);
		adev->vcn.intewnaw.cmd = mmUVD_GPCOM_VCPU_CMD_INTEWNAW_OFFSET;
		adev->vcn.inst[i].extewnaw.cmd = SOC15_WEG_OFFSET(VCN, i, mmUVD_GPCOM_VCPU_CMD);
		adev->vcn.intewnaw.nop = mmUVD_NO_OP_INTEWNAW_OFFSET;
		adev->vcn.inst[i].extewnaw.nop = SOC15_WEG_OFFSET(VCN, i, mmUVD_NO_OP);

		/* VCN DEC TWAP */
		w = amdgpu_iwq_add_id(adev, amdgpu_ih_cwientid_vcns[i],
				VCN_2_0__SWCID__UVD_SYSTEM_MESSAGE_INTEWWUPT, &adev->vcn.inst[i].iwq);
		if (w)
			wetuwn w;

		atomic_set(&adev->vcn.inst[i].sched_scowe, 0);

		wing = &adev->vcn.inst[i].wing_dec;
		wing->use_doowbeww = twue;
		if (amdgpu_swiov_vf(adev)) {
			wing->doowbeww_index = vcn_doowbeww_index + i * (adev->vcn.num_enc_wings + 1);
		} ewse {
			wing->doowbeww_index = (adev->doowbeww_index.vcn.vcn_wing0_1 << 1) + 8 * i;
		}
		wing->vm_hub = AMDGPU_MMHUB0(0);
		spwintf(wing->name, "vcn_dec_%d", i);
		w = amdgpu_wing_init(adev, wing, 512, &adev->vcn.inst[i].iwq, 0,
				     AMDGPU_WING_PWIO_DEFAUWT,
				     &adev->vcn.inst[i].sched_scowe);
		if (w)
			wetuwn w;

		fow (j = 0; j < adev->vcn.num_enc_wings; ++j) {
			enum amdgpu_wing_pwiowity_wevew hw_pwio = amdgpu_vcn_get_enc_wing_pwio(j);

			/* VCN ENC TWAP */
			w = amdgpu_iwq_add_id(adev, amdgpu_ih_cwientid_vcns[i],
				j + VCN_2_0__SWCID__UVD_ENC_GENEWAW_PUWPOSE, &adev->vcn.inst[i].iwq);
			if (w)
				wetuwn w;

			wing = &adev->vcn.inst[i].wing_enc[j];
			wing->use_doowbeww = twue;
			if (amdgpu_swiov_vf(adev)) {
				wing->doowbeww_index = vcn_doowbeww_index + i * (adev->vcn.num_enc_wings + 1) + 1 + j;
			} ewse {
				wing->doowbeww_index = (adev->doowbeww_index.vcn.vcn_wing0_1 << 1) + 2 + j + 8 * i;
			}
			wing->vm_hub = AMDGPU_MMHUB0(0);
			spwintf(wing->name, "vcn_enc_%d.%d", i, j);
			w = amdgpu_wing_init(adev, wing, 512, &adev->vcn.inst[i].iwq, 0,
					     hw_pwio, &adev->vcn.inst[i].sched_scowe);
			if (w)
				wetuwn w;
		}

		fw_shawed = adev->vcn.inst[i].fw_shawed.cpu_addw;
		fw_shawed->pwesent_fwag_0 |= cpu_to_we32(AMDGPU_VCN_SW_WING_FWAG) |
					     cpu_to_we32(AMDGPU_VCN_MUWTI_QUEUE_FWAG) |
					     cpu_to_we32(AMDGPU_VCN_FW_SHAWED_FWAG_0_WB);
		fw_shawed->sw_wing.is_enabwed = cpu_to_we32(DEC_SW_WING_ENABWED);
		fw_shawed->pwesent_fwag_0 |= AMDGPU_VCN_SMU_VEWSION_INFO_FWAG;
		if (amdgpu_ip_vewsion(adev, UVD_HWIP, 0) == IP_VEWSION(3, 1, 2))
			fw_shawed->smu_intewface_info.smu_intewface_type = 2;
		ewse if (amdgpu_ip_vewsion(adev, UVD_HWIP, 0) ==
			 IP_VEWSION(3, 1, 1))
			fw_shawed->smu_intewface_info.smu_intewface_type = 1;

		if (amdgpu_vcnfw_wog)
			amdgpu_vcn_fwwog_init(&adev->vcn.inst[i]);
	}

	if (amdgpu_swiov_vf(adev)) {
		w = amdgpu_viwt_awwoc_mm_tabwe(adev);
		if (w)
			wetuwn w;
	}
	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG)
		adev->vcn.pause_dpg_mode = vcn_v3_0_pause_dpg_mode;

	wetuwn 0;
}

/**
 * vcn_v3_0_sw_fini - sw fini fow VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * VCN suspend and fwee up sw awwocation
 */
static int vcn_v3_0_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, w, idx;

	if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
		fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			vowatiwe stwuct amdgpu_fw_shawed *fw_shawed;

			if (adev->vcn.hawvest_config & (1 << i))
				continue;
			fw_shawed = adev->vcn.inst[i].fw_shawed.cpu_addw;
			fw_shawed->pwesent_fwag_0 = 0;
			fw_shawed->sw_wing.is_enabwed = fawse;
		}

		dwm_dev_exit(idx);
	}

	if (amdgpu_swiov_vf(adev))
		amdgpu_viwt_fwee_mm_tabwe(adev);

	w = amdgpu_vcn_suspend(adev);
	if (w)
		wetuwn w;

	w = amdgpu_vcn_sw_fini(adev);

	wetuwn w;
}

/**
 * vcn_v3_0_hw_init - stawt and test VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Initiawize the hawdwawe, boot up the VCPU and do some testing
 */
static int vcn_v3_0_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;
	int i, j, w;

	if (amdgpu_swiov_vf(adev)) {
		w = vcn_v3_0_stawt_swiov(adev);
		if (w)
			goto done;

		/* initiawize VCN dec and enc wing buffews */
		fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
			if (adev->vcn.hawvest_config & (1 << i))
				continue;

			wing = &adev->vcn.inst[i].wing_dec;
			if (amdgpu_vcn_is_disabwed_vcn(adev, VCN_DECODE_WING, i)) {
				wing->sched.weady = fawse;
				wing->no_scheduwew = twue;
				dev_info(adev->dev, "wing %s is disabwed by hypewvisow\n", wing->name);
			} ewse {
				wing->wptw = 0;
				wing->wptw_owd = 0;
				vcn_v3_0_dec_wing_set_wptw(wing);
				wing->sched.weady = twue;
			}

			fow (j = 0; j < adev->vcn.num_enc_wings; ++j) {
				wing = &adev->vcn.inst[i].wing_enc[j];
				if (amdgpu_vcn_is_disabwed_vcn(adev, VCN_ENCODE_WING, i)) {
					wing->sched.weady = fawse;
					wing->no_scheduwew = twue;
					dev_info(adev->dev, "wing %s is disabwed by hypewvisow\n", wing->name);
				} ewse {
					wing->wptw = 0;
					wing->wptw_owd = 0;
					vcn_v3_0_enc_wing_set_wptw(wing);
					wing->sched.weady = twue;
				}
			}
		}
	} ewse {
		fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
			if (adev->vcn.hawvest_config & (1 << i))
				continue;

			wing = &adev->vcn.inst[i].wing_dec;

			adev->nbio.funcs->vcn_doowbeww_wange(adev, wing->use_doowbeww,
						     wing->doowbeww_index, i);

			w = amdgpu_wing_test_hewpew(wing);
			if (w)
				goto done;

			fow (j = 0; j < adev->vcn.num_enc_wings; ++j) {
				wing = &adev->vcn.inst[i].wing_enc[j];
				w = amdgpu_wing_test_hewpew(wing);
				if (w)
					goto done;
			}
		}
	}

done:
	if (!w)
		DWM_INFO("VCN decode and encode initiawized successfuwwy(undew %s).\n",
			(adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG)?"DPG Mode":"SPG Mode");

	wetuwn w;
}

/**
 * vcn_v3_0_hw_fini - stop the hawdwawe bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Stop the VCN bwock, mawk wing as not weady any mowe
 */
static int vcn_v3_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i;

	cancew_dewayed_wowk_sync(&adev->vcn.idwe_wowk);

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		if (!amdgpu_swiov_vf(adev)) {
			if ((adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) ||
					(adev->vcn.cuw_state != AMD_PG_STATE_GATE &&
					 WWEG32_SOC15(VCN, i, mmUVD_STATUS))) {
				vcn_v3_0_set_powewgating_state(adev, AMD_PG_STATE_GATE);
			}
		}
	}

	wetuwn 0;
}

/**
 * vcn_v3_0_suspend - suspend VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * HW fini and suspend VCN bwock
 */
static int vcn_v3_0_suspend(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = vcn_v3_0_hw_fini(adev);
	if (w)
		wetuwn w;

	w = amdgpu_vcn_suspend(adev);

	wetuwn w;
}

/**
 * vcn_v3_0_wesume - wesume VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Wesume fiwmwawe and hw init VCN bwock
 */
static int vcn_v3_0_wesume(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_vcn_wesume(adev);
	if (w)
		wetuwn w;

	w = vcn_v3_0_hw_init(adev);

	wetuwn w;
}

/**
 * vcn_v3_0_mc_wesume - memowy contwowwew pwogwamming
 *
 * @adev: amdgpu_device pointew
 * @inst: instance numbew
 *
 * Wet the VCN memowy contwowwew know it's offsets
 */
static void vcn_v3_0_mc_wesume(stwuct amdgpu_device *adev, int inst)
{
	uint32_t size = AMDGPU_GPU_PAGE_AWIGN(adev->vcn.fw->size + 4);
	uint32_t offset;

	/* cache window 0: fw */
	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		WWEG32_SOC15(VCN, inst, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
			(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + inst].tmw_mc_addw_wo));
		WWEG32_SOC15(VCN, inst, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
			(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + inst].tmw_mc_addw_hi));
		WWEG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_OFFSET0, 0);
		offset = 0;
	} ewse {
		WWEG32_SOC15(VCN, inst, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
			wowew_32_bits(adev->vcn.inst[inst].gpu_addw));
		WWEG32_SOC15(VCN, inst, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
			uppew_32_bits(adev->vcn.inst[inst].gpu_addw));
		offset = size;
		WWEG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_OFFSET0,
			AMDGPU_UVD_FIWMWAWE_OFFSET >> 3);
	}
	WWEG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_SIZE0, size);

	/* cache window 1: stack */
	WWEG32_SOC15(VCN, inst, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW,
		wowew_32_bits(adev->vcn.inst[inst].gpu_addw + offset));
	WWEG32_SOC15(VCN, inst, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH,
		uppew_32_bits(adev->vcn.inst[inst].gpu_addw + offset));
	WWEG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_OFFSET1, 0);
	WWEG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_SIZE1, AMDGPU_VCN_STACK_SIZE);

	/* cache window 2: context */
	WWEG32_SOC15(VCN, inst, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW,
		wowew_32_bits(adev->vcn.inst[inst].gpu_addw + offset + AMDGPU_VCN_STACK_SIZE));
	WWEG32_SOC15(VCN, inst, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH,
		uppew_32_bits(adev->vcn.inst[inst].gpu_addw + offset + AMDGPU_VCN_STACK_SIZE));
	WWEG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_OFFSET2, 0);
	WWEG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_SIZE2, AMDGPU_VCN_CONTEXT_SIZE);

	/* non-cache window */
	WWEG32_SOC15(VCN, inst, mmUVD_WMI_VCPU_NC0_64BIT_BAW_WOW,
		wowew_32_bits(adev->vcn.inst[inst].fw_shawed.gpu_addw));
	WWEG32_SOC15(VCN, inst, mmUVD_WMI_VCPU_NC0_64BIT_BAW_HIGH,
		uppew_32_bits(adev->vcn.inst[inst].fw_shawed.gpu_addw));
	WWEG32_SOC15(VCN, inst, mmUVD_VCPU_NONCACHE_OFFSET0, 0);
	WWEG32_SOC15(VCN, inst, mmUVD_VCPU_NONCACHE_SIZE0,
		AMDGPU_GPU_PAGE_AWIGN(sizeof(stwuct amdgpu_fw_shawed)));
}

static void vcn_v3_0_mc_wesume_dpg_mode(stwuct amdgpu_device *adev, int inst_idx, boow indiwect)
{
	uint32_t size = AMDGPU_GPU_PAGE_AWIGN(adev->vcn.fw->size + 4);
	uint32_t offset;

	/* cache window 0: fw */
	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		if (!indiwect) {
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
				(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + inst_idx].tmw_mc_addw_wo), 0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
				(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + inst_idx].tmw_mc_addw_hi), 0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET0), 0, 0, indiwect);
		} ewse {
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW), 0, 0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH), 0, 0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET0), 0, 0, indiwect);
		}
		offset = 0;
	} ewse {
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
			wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw), 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
			uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw), 0, indiwect);
		offset = size;
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET0),
			AMDGPU_UVD_FIWMWAWE_OFFSET >> 3, 0, indiwect);
	}

	if (!indiwect)
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_SIZE0), size, 0, indiwect);
	ewse
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_SIZE0), 0, 0, indiwect);

	/* cache window 1: stack */
	if (!indiwect) {
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW),
			wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset), 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH),
			uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset), 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET1), 0, 0, indiwect);
	} ewse {
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW), 0, 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH), 0, 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET1), 0, 0, indiwect);
	}
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_SIZE1), AMDGPU_VCN_STACK_SIZE, 0, indiwect);

	/* cache window 2: context */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW),
			wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset + AMDGPU_VCN_STACK_SIZE), 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH),
			uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset + AMDGPU_VCN_STACK_SIZE), 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET2), 0, 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_SIZE2), AMDGPU_VCN_CONTEXT_SIZE, 0, indiwect);

	/* non-cache window */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_WMI_VCPU_NC0_64BIT_BAW_WOW),
			wowew_32_bits(adev->vcn.inst[inst_idx].fw_shawed.gpu_addw), 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_WMI_VCPU_NC0_64BIT_BAW_HIGH),
			uppew_32_bits(adev->vcn.inst[inst_idx].fw_shawed.gpu_addw), 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_NONCACHE_OFFSET0), 0, 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_NONCACHE_SIZE0),
			AMDGPU_GPU_PAGE_AWIGN(sizeof(stwuct amdgpu_fw_shawed)), 0, indiwect);

	/* VCN gwobaw tiwing wegistews */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		UVD, inst_idx, mmUVD_GFX10_ADDW_CONFIG), adev->gfx.config.gb_addw_config, 0, indiwect);
}

static void vcn_v3_0_disabwe_static_powew_gating(stwuct amdgpu_device *adev, int inst)
{
	uint32_t data = 0;

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN) {
		data = (1 << UVD_PGFSM_CONFIG__UVDM_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDU_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDF_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDC_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDB_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIWW_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDWM_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTD_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTE_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDE_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDAB_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDATD_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDNA_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDNB_PWW_CONFIG__SHIFT);

		WWEG32_SOC15(VCN, inst, mmUVD_PGFSM_CONFIG, data);
		SOC15_WAIT_ON_WWEG(VCN, inst, mmUVD_PGFSM_STATUS,
			UVD_PGFSM_STATUS__UVDM_UVDU_UVDWM_PWW_ON_3_0, 0x3F3FFFFF);
	} ewse {
		data = (1 << UVD_PGFSM_CONFIG__UVDM_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDU_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDF_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDC_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDB_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDIWW_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDWM_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDTD_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDTE_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDE_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDAB_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDATD_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDNA_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDNB_PWW_CONFIG__SHIFT);
		WWEG32_SOC15(VCN, inst, mmUVD_PGFSM_CONFIG, data);
		SOC15_WAIT_ON_WWEG(VCN, inst, mmUVD_PGFSM_STATUS, 0,  0x3F3FFFFF);
	}

	data = WWEG32_SOC15(VCN, inst, mmUVD_POWEW_STATUS);
	data &= ~0x103;
	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN)
		data |= UVD_PGFSM_CONFIG__UVDM_UVDU_PWW_ON |
			UVD_POWEW_STATUS__UVD_PG_EN_MASK;

	WWEG32_SOC15(VCN, inst, mmUVD_POWEW_STATUS, data);
}

static void vcn_v3_0_enabwe_static_powew_gating(stwuct amdgpu_device *adev, int inst)
{
	uint32_t data;

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN) {
		/* Befowe powew off, this indicatow has to be tuwned on */
		data = WWEG32_SOC15(VCN, inst, mmUVD_POWEW_STATUS);
		data &= ~UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK;
		data |= UVD_POWEW_STATUS__UVD_POWEW_STATUS_TIWES_OFF;
		WWEG32_SOC15(VCN, inst, mmUVD_POWEW_STATUS, data);

		data = (2 << UVD_PGFSM_CONFIG__UVDM_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDU_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDF_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDC_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDB_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIWW_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDWM_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTD_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTE_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDE_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDAB_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDATD_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDNA_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDNB_PWW_CONFIG__SHIFT);
		WWEG32_SOC15(VCN, inst, mmUVD_PGFSM_CONFIG, data);

		data = (2 << UVD_PGFSM_STATUS__UVDM_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDU_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDF_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDC_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDB_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDIWW_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDWM_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDTD_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDTE_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDE_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDAB_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDATD_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDNA_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDNB_PWW_STATUS__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, mmUVD_PGFSM_STATUS, data, 0x3F3FFFFF);
	}
}

/**
 * vcn_v3_0_disabwe_cwock_gating - disabwe VCN cwock gating
 *
 * @adev: amdgpu_device pointew
 * @inst: instance numbew
 *
 * Disabwe cwock gating fow VCN bwock
 */
static void vcn_v3_0_disabwe_cwock_gating(stwuct amdgpu_device *adev, int inst)
{
	uint32_t data;

	/* VCN disabwe CGC */
	data = WWEG32_SOC15(VCN, inst, mmUVD_CGC_CTWW);
	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		data |= 1 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	ewse
		data &= ~UVD_CGC_CTWW__DYN_CWOCK_MODE_MASK;
	data |= 1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(VCN, inst, mmUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, inst, mmUVD_CGC_GATE);
	data &= ~(UVD_CGC_GATE__SYS_MASK
		| UVD_CGC_GATE__UDEC_MASK
		| UVD_CGC_GATE__MPEG2_MASK
		| UVD_CGC_GATE__WEGS_MASK
		| UVD_CGC_GATE__WBC_MASK
		| UVD_CGC_GATE__WMI_MC_MASK
		| UVD_CGC_GATE__WMI_UMC_MASK
		| UVD_CGC_GATE__IDCT_MASK
		| UVD_CGC_GATE__MPWD_MASK
		| UVD_CGC_GATE__MPC_MASK
		| UVD_CGC_GATE__WBSI_MASK
		| UVD_CGC_GATE__WWBBM_MASK
		| UVD_CGC_GATE__UDEC_WE_MASK
		| UVD_CGC_GATE__UDEC_CM_MASK
		| UVD_CGC_GATE__UDEC_IT_MASK
		| UVD_CGC_GATE__UDEC_DB_MASK
		| UVD_CGC_GATE__UDEC_MP_MASK
		| UVD_CGC_GATE__WCB_MASK
		| UVD_CGC_GATE__VCPU_MASK
		| UVD_CGC_GATE__MMSCH_MASK);

	WWEG32_SOC15(VCN, inst, mmUVD_CGC_GATE, data);

	SOC15_WAIT_ON_WWEG(VCN, inst, mmUVD_CGC_GATE, 0,  0xFFFFFFFF);

	data = WWEG32_SOC15(VCN, inst, mmUVD_CGC_CTWW);
	data &= ~(UVD_CGC_CTWW__UDEC_WE_MODE_MASK
		| UVD_CGC_CTWW__UDEC_CM_MODE_MASK
		| UVD_CGC_CTWW__UDEC_IT_MODE_MASK
		| UVD_CGC_CTWW__UDEC_DB_MODE_MASK
		| UVD_CGC_CTWW__UDEC_MP_MODE_MASK
		| UVD_CGC_CTWW__SYS_MODE_MASK
		| UVD_CGC_CTWW__UDEC_MODE_MASK
		| UVD_CGC_CTWW__MPEG2_MODE_MASK
		| UVD_CGC_CTWW__WEGS_MODE_MASK
		| UVD_CGC_CTWW__WBC_MODE_MASK
		| UVD_CGC_CTWW__WMI_MC_MODE_MASK
		| UVD_CGC_CTWW__WMI_UMC_MODE_MASK
		| UVD_CGC_CTWW__IDCT_MODE_MASK
		| UVD_CGC_CTWW__MPWD_MODE_MASK
		| UVD_CGC_CTWW__MPC_MODE_MASK
		| UVD_CGC_CTWW__WBSI_MODE_MASK
		| UVD_CGC_CTWW__WWBBM_MODE_MASK
		| UVD_CGC_CTWW__WCB_MODE_MASK
		| UVD_CGC_CTWW__VCPU_MODE_MASK
		| UVD_CGC_CTWW__MMSCH_MODE_MASK);
	WWEG32_SOC15(VCN, inst, mmUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_GATE);
	data |= (UVD_SUVD_CGC_GATE__SWE_MASK
		| UVD_SUVD_CGC_GATE__SIT_MASK
		| UVD_SUVD_CGC_GATE__SMP_MASK
		| UVD_SUVD_CGC_GATE__SCM_MASK
		| UVD_SUVD_CGC_GATE__SDB_MASK
		| UVD_SUVD_CGC_GATE__SWE_H264_MASK
		| UVD_SUVD_CGC_GATE__SWE_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SIT_H264_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SCM_H264_MASK
		| UVD_SUVD_CGC_GATE__SCM_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SDB_H264_MASK
		| UVD_SUVD_CGC_GATE__SDB_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SCWW_MASK
		| UVD_SUVD_CGC_GATE__ENT_MASK
		| UVD_SUVD_CGC_GATE__IME_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_DEC_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_ENC_MASK
		| UVD_SUVD_CGC_GATE__SITE_MASK
		| UVD_SUVD_CGC_GATE__SWE_VP9_MASK
		| UVD_SUVD_CGC_GATE__SCM_VP9_MASK
		| UVD_SUVD_CGC_GATE__SIT_VP9_DEC_MASK
		| UVD_SUVD_CGC_GATE__SDB_VP9_MASK
		| UVD_SUVD_CGC_GATE__IME_HEVC_MASK
		| UVD_SUVD_CGC_GATE__EFC_MASK
		| UVD_SUVD_CGC_GATE__SAOE_MASK
		| UVD_SUVD_CGC_GATE__SWE_AV1_MASK
		| UVD_SUVD_CGC_GATE__FBC_PCWK_MASK
		| UVD_SUVD_CGC_GATE__FBC_CCWK_MASK
		| UVD_SUVD_CGC_GATE__SCM_AV1_MASK
		| UVD_SUVD_CGC_GATE__SMPA_MASK);
	WWEG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_GATE, data);

	data = WWEG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_GATE2);
	data |= (UVD_SUVD_CGC_GATE2__MPBE0_MASK
		| UVD_SUVD_CGC_GATE2__MPBE1_MASK
		| UVD_SUVD_CGC_GATE2__SIT_AV1_MASK
		| UVD_SUVD_CGC_GATE2__SDB_AV1_MASK
		| UVD_SUVD_CGC_GATE2__MPC1_MASK);
	WWEG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_GATE2, data);

	data = WWEG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_CTWW);
	data &= ~(UVD_SUVD_CGC_CTWW__SWE_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SIT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SMP_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SCM_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SDB_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SCWW_MODE_MASK
		| UVD_SUVD_CGC_CTWW__ENT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__IME_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SITE_MODE_MASK
		| UVD_SUVD_CGC_CTWW__EFC_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SAOE_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SMPA_MODE_MASK
		| UVD_SUVD_CGC_CTWW__MPBE0_MODE_MASK
		| UVD_SUVD_CGC_CTWW__MPBE1_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SIT_AV1_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SDB_AV1_MODE_MASK
		| UVD_SUVD_CGC_CTWW__MPC1_MODE_MASK
		| UVD_SUVD_CGC_CTWW__FBC_PCWK_MASK
		| UVD_SUVD_CGC_CTWW__FBC_CCWK_MASK);
	WWEG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_CTWW, data);
}

static void vcn_v3_0_cwock_gating_dpg_mode(stwuct amdgpu_device *adev,
		uint8_t swam_sew, int inst_idx, uint8_t indiwect)
{
	uint32_t weg_data = 0;

	/* enabwe sw cwock gating contwow */
	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		weg_data = 1 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	ewse
		weg_data = 0 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	weg_data |= 1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	weg_data |= 4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	weg_data &= ~(UVD_CGC_CTWW__UDEC_WE_MODE_MASK |
		 UVD_CGC_CTWW__UDEC_CM_MODE_MASK |
		 UVD_CGC_CTWW__UDEC_IT_MODE_MASK |
		 UVD_CGC_CTWW__UDEC_DB_MODE_MASK |
		 UVD_CGC_CTWW__UDEC_MP_MODE_MASK |
		 UVD_CGC_CTWW__SYS_MODE_MASK |
		 UVD_CGC_CTWW__UDEC_MODE_MASK |
		 UVD_CGC_CTWW__MPEG2_MODE_MASK |
		 UVD_CGC_CTWW__WEGS_MODE_MASK |
		 UVD_CGC_CTWW__WBC_MODE_MASK |
		 UVD_CGC_CTWW__WMI_MC_MODE_MASK |
		 UVD_CGC_CTWW__WMI_UMC_MODE_MASK |
		 UVD_CGC_CTWW__IDCT_MODE_MASK |
		 UVD_CGC_CTWW__MPWD_MODE_MASK |
		 UVD_CGC_CTWW__MPC_MODE_MASK |
		 UVD_CGC_CTWW__WBSI_MODE_MASK |
		 UVD_CGC_CTWW__WWBBM_MODE_MASK |
		 UVD_CGC_CTWW__WCB_MODE_MASK |
		 UVD_CGC_CTWW__VCPU_MODE_MASK |
		 UVD_CGC_CTWW__MMSCH_MODE_MASK);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_CGC_CTWW), weg_data, swam_sew, indiwect);

	/* tuwn off cwock gating */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_CGC_GATE), 0, swam_sew, indiwect);

	/* tuwn on SUVD cwock gating */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_SUVD_CGC_GATE), 1, swam_sew, indiwect);

	/* tuwn on sw mode in UVD_SUVD_CGC_CTWW */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_SUVD_CGC_CTWW), 0, swam_sew, indiwect);
}

/**
 * vcn_v3_0_enabwe_cwock_gating - enabwe VCN cwock gating
 *
 * @adev: amdgpu_device pointew
 * @inst: instance numbew
 *
 * Enabwe cwock gating fow VCN bwock
 */
static void vcn_v3_0_enabwe_cwock_gating(stwuct amdgpu_device *adev, int inst)
{
	uint32_t data;

	/* enabwe VCN CGC */
	data = WWEG32_SOC15(VCN, inst, mmUVD_CGC_CTWW);
	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		data |= 1 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	ewse
		data |= 0 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	data |= 1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(VCN, inst, mmUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, inst, mmUVD_CGC_CTWW);
	data |= (UVD_CGC_CTWW__UDEC_WE_MODE_MASK
		| UVD_CGC_CTWW__UDEC_CM_MODE_MASK
		| UVD_CGC_CTWW__UDEC_IT_MODE_MASK
		| UVD_CGC_CTWW__UDEC_DB_MODE_MASK
		| UVD_CGC_CTWW__UDEC_MP_MODE_MASK
		| UVD_CGC_CTWW__SYS_MODE_MASK
		| UVD_CGC_CTWW__UDEC_MODE_MASK
		| UVD_CGC_CTWW__MPEG2_MODE_MASK
		| UVD_CGC_CTWW__WEGS_MODE_MASK
		| UVD_CGC_CTWW__WBC_MODE_MASK
		| UVD_CGC_CTWW__WMI_MC_MODE_MASK
		| UVD_CGC_CTWW__WMI_UMC_MODE_MASK
		| UVD_CGC_CTWW__IDCT_MODE_MASK
		| UVD_CGC_CTWW__MPWD_MODE_MASK
		| UVD_CGC_CTWW__MPC_MODE_MASK
		| UVD_CGC_CTWW__WBSI_MODE_MASK
		| UVD_CGC_CTWW__WWBBM_MODE_MASK
		| UVD_CGC_CTWW__WCB_MODE_MASK
		| UVD_CGC_CTWW__VCPU_MODE_MASK
		| UVD_CGC_CTWW__MMSCH_MODE_MASK);
	WWEG32_SOC15(VCN, inst, mmUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_CTWW);
	data |= (UVD_SUVD_CGC_CTWW__SWE_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SIT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SMP_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SCM_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SDB_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SCWW_MODE_MASK
		| UVD_SUVD_CGC_CTWW__ENT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__IME_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SITE_MODE_MASK
		| UVD_SUVD_CGC_CTWW__EFC_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SAOE_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SMPA_MODE_MASK
		| UVD_SUVD_CGC_CTWW__MPBE0_MODE_MASK
		| UVD_SUVD_CGC_CTWW__MPBE1_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SIT_AV1_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SDB_AV1_MODE_MASK
		| UVD_SUVD_CGC_CTWW__MPC1_MODE_MASK
		| UVD_SUVD_CGC_CTWW__FBC_PCWK_MASK
		| UVD_SUVD_CGC_CTWW__FBC_CCWK_MASK);
	WWEG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_CTWW, data);
}

static int vcn_v3_0_stawt_dpg_mode(stwuct amdgpu_device *adev, int inst_idx, boow indiwect)
{
	vowatiwe stwuct amdgpu_fw_shawed *fw_shawed = adev->vcn.inst[inst_idx].fw_shawed.cpu_addw;
	stwuct amdgpu_wing *wing;
	uint32_t wb_bufsz, tmp;

	/* disabwe wegistew anti-hang mechanism */
	WWEG32_P(SOC15_WEG_OFFSET(VCN, inst_idx, mmUVD_POWEW_STATUS), 1,
		~UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);
	/* enabwe dynamic powew gating mode */
	tmp = WWEG32_SOC15(VCN, inst_idx, mmUVD_POWEW_STATUS);
	tmp |= UVD_POWEW_STATUS__UVD_PG_MODE_MASK;
	tmp |= UVD_POWEW_STATUS__UVD_PG_EN_MASK;
	WWEG32_SOC15(VCN, inst_idx, mmUVD_POWEW_STATUS, tmp);

	if (indiwect)
		adev->vcn.inst[inst_idx].dpg_swam_cuww_addw = (uint32_t *)adev->vcn.inst[inst_idx].dpg_swam_cpu_addw;

	/* enabwe cwock gating */
	vcn_v3_0_cwock_gating_dpg_mode(adev, 0, inst_idx, indiwect);

	/* enabwe VCPU cwock */
	tmp = (0xFF << UVD_VCPU_CNTW__PWB_TIMEOUT_VAW__SHIFT);
	tmp |= UVD_VCPU_CNTW__CWK_EN_MASK;
	tmp |= UVD_VCPU_CNTW__BWK_WST_MASK;
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_VCPU_CNTW), tmp, 0, indiwect);

	/* disabwe mastew intewupt */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MASTINT_EN), 0, 0, indiwect);

	/* setup mmUVD_WMI_CTWW */
	tmp = (0x8 | UVD_WMI_CTWW__WWITE_CWEAN_TIMEW_EN_MASK |
		UVD_WMI_CTWW__WEQ_MODE_MASK |
		UVD_WMI_CTWW__CWC_WESET_MASK |
		UVD_WMI_CTWW__MASK_MC_UWGENT_MASK |
		UVD_WMI_CTWW__DATA_COHEWENCY_EN_MASK |
		UVD_WMI_CTWW__VCPU_DATA_COHEWENCY_EN_MASK |
		(8 << UVD_WMI_CTWW__WWITE_CWEAN_TIMEW__SHIFT) |
		0x00100000W);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_WMI_CTWW), tmp, 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MPC_CNTW),
		0x2 << UVD_MPC_CNTW__WEPWACEMENT_MODE__SHIFT, 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MPC_SET_MUXA0),
		((0x1 << UVD_MPC_SET_MUXA0__VAWA_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXA0__VAWA_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXA0__VAWA_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXA0__VAWA_4__SHIFT)), 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MPC_SET_MUXB0),
		 ((0x1 << UVD_MPC_SET_MUXB0__VAWB_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXB0__VAWB_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXB0__VAWB_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXB0__VAWB_4__SHIFT)), 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MPC_SET_MUX),
		((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
		 (0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)), 0, indiwect);

	vcn_v3_0_mc_wesume_dpg_mode(adev, inst_idx, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_WEG_XX_MASK), 0x10, 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_WBC_XX_IB_WEG_CHECK), 0x3, 0, indiwect);

	/* enabwe WMI MC and UMC channews */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_WMI_CTWW2), 0, 0, indiwect);

	/* unbwock VCPU wegistew access */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_WB_AWB_CTWW), 0, 0, indiwect);

	tmp = (0xFF << UVD_VCPU_CNTW__PWB_TIMEOUT_VAW__SHIFT);
	tmp |= UVD_VCPU_CNTW__CWK_EN_MASK;
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_VCPU_CNTW), tmp, 0, indiwect);

	/* enabwe mastew intewwupt */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MASTINT_EN),
		UVD_MASTINT_EN__VCPU_EN_MASK, 0, indiwect);

	/* add nop to wowkawound PSP size check */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_VCPU_CNTW), tmp, 0, indiwect);

	if (indiwect)
		amdgpu_vcn_psp_update_swam(adev, inst_idx, 0);

	wing = &adev->vcn.inst[inst_idx].wing_dec;
	/* fowce WBC into idwe state */
	wb_bufsz = owdew_base_2(wing->wing_size);
	tmp = WEG_SET_FIEWD(0, UVD_WBC_WB_CNTW, WB_BUFSZ, wb_bufsz);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_BWKSZ, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_FETCH, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_UPDATE, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_WPTW_WW_EN, 1);
	WWEG32_SOC15(VCN, inst_idx, mmUVD_WBC_WB_CNTW, tmp);

	/* Staww DPG befowe WPTW/WPTW weset */
	WWEG32_P(SOC15_WEG_OFFSET(VCN, inst_idx, mmUVD_POWEW_STATUS),
		UVD_POWEW_STATUS__STAWW_DPG_POWEW_UP_MASK,
		~UVD_POWEW_STATUS__STAWW_DPG_POWEW_UP_MASK);
	fw_shawed->muwti_queue.decode_queue_mode |= cpu_to_we32(FW_QUEUE_WING_WESET);

	/* set the wwite pointew deway */
	WWEG32_SOC15(VCN, inst_idx, mmUVD_WBC_WB_WPTW_CNTW, 0);

	/* set the wb addwess */
	WWEG32_SOC15(VCN, inst_idx, mmUVD_WBC_WB_WPTW_ADDW,
		(uppew_32_bits(wing->gpu_addw) >> 2));

	/* pwogwamm the WB_BASE fow wing buffew */
	WWEG32_SOC15(VCN, inst_idx, mmUVD_WMI_WBC_WB_64BIT_BAW_WOW,
		wowew_32_bits(wing->gpu_addw));
	WWEG32_SOC15(VCN, inst_idx, mmUVD_WMI_WBC_WB_64BIT_BAW_HIGH,
		uppew_32_bits(wing->gpu_addw));

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32_SOC15(VCN, inst_idx, mmUVD_WBC_WB_WPTW, 0);

	WWEG32_SOC15(VCN, inst_idx, mmUVD_SCWATCH2, 0);

	wing->wptw = WWEG32_SOC15(VCN, inst_idx, mmUVD_WBC_WB_WPTW);
	WWEG32_SOC15(VCN, inst_idx, mmUVD_WBC_WB_WPTW,
		wowew_32_bits(wing->wptw));

	/* Weset FW shawed memowy WBC WPTW/WPTW */
	fw_shawed->wb.wptw = 0;
	fw_shawed->wb.wptw = wowew_32_bits(wing->wptw);

	/*wesetting done, fw can check WB wing */
	fw_shawed->muwti_queue.decode_queue_mode &= cpu_to_we32(~FW_QUEUE_WING_WESET);

	/* Unstaww DPG */
	WWEG32_P(SOC15_WEG_OFFSET(VCN, inst_idx, mmUVD_POWEW_STATUS),
		0, ~UVD_POWEW_STATUS__STAWW_DPG_POWEW_UP_MASK);

	wetuwn 0;
}

static int vcn_v3_0_stawt(stwuct amdgpu_device *adev)
{
	vowatiwe stwuct amdgpu_fw_shawed *fw_shawed;
	stwuct amdgpu_wing *wing;
	uint32_t wb_bufsz, tmp;
	int i, j, k, w;

	if (adev->pm.dpm_enabwed)
		amdgpu_dpm_enabwe_uvd(adev, twue);

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) {
			w = vcn_v3_0_stawt_dpg_mode(adev, i, adev->vcn.indiwect_swam);
			continue;
		}

		/* disabwe VCN powew gating */
		vcn_v3_0_disabwe_static_powew_gating(adev, i);

		/* set VCN status busy */
		tmp = WWEG32_SOC15(VCN, i, mmUVD_STATUS) | UVD_STATUS__UVD_BUSY;
		WWEG32_SOC15(VCN, i, mmUVD_STATUS, tmp);

		/*SW cwock gating */
		vcn_v3_0_disabwe_cwock_gating(adev, i);

		/* enabwe VCPU cwock */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_VCPU_CNTW),
			UVD_VCPU_CNTW__CWK_EN_MASK, ~UVD_VCPU_CNTW__CWK_EN_MASK);

		/* disabwe mastew intewwupt */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_MASTINT_EN), 0,
			~UVD_MASTINT_EN__VCPU_EN_MASK);

		/* enabwe WMI MC and UMC channews */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_WMI_CTWW2), 0,
			~UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK);

		tmp = WWEG32_SOC15(VCN, i, mmUVD_SOFT_WESET);
		tmp &= ~UVD_SOFT_WESET__WMI_SOFT_WESET_MASK;
		tmp &= ~UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK;
		WWEG32_SOC15(VCN, i, mmUVD_SOFT_WESET, tmp);

		/* setup mmUVD_WMI_CTWW */
		tmp = WWEG32_SOC15(VCN, i, mmUVD_WMI_CTWW);
		WWEG32_SOC15(VCN, i, mmUVD_WMI_CTWW, tmp |
			UVD_WMI_CTWW__WWITE_CWEAN_TIMEW_EN_MASK	|
			UVD_WMI_CTWW__MASK_MC_UWGENT_MASK |
			UVD_WMI_CTWW__DATA_COHEWENCY_EN_MASK |
			UVD_WMI_CTWW__VCPU_DATA_COHEWENCY_EN_MASK);

		/* setup mmUVD_MPC_CNTW */
		tmp = WWEG32_SOC15(VCN, i, mmUVD_MPC_CNTW);
		tmp &= ~UVD_MPC_CNTW__WEPWACEMENT_MODE_MASK;
		tmp |= 0x2 << UVD_MPC_CNTW__WEPWACEMENT_MODE__SHIFT;
		WWEG32_SOC15(VCN, i, mmUVD_MPC_CNTW, tmp);

		/* setup UVD_MPC_SET_MUXA0 */
		WWEG32_SOC15(VCN, i, mmUVD_MPC_SET_MUXA0,
			((0x1 << UVD_MPC_SET_MUXA0__VAWA_1__SHIFT) |
			(0x2 << UVD_MPC_SET_MUXA0__VAWA_2__SHIFT) |
			(0x3 << UVD_MPC_SET_MUXA0__VAWA_3__SHIFT) |
			(0x4 << UVD_MPC_SET_MUXA0__VAWA_4__SHIFT)));

		/* setup UVD_MPC_SET_MUXB0 */
		WWEG32_SOC15(VCN, i, mmUVD_MPC_SET_MUXB0,
			((0x1 << UVD_MPC_SET_MUXB0__VAWB_1__SHIFT) |
			(0x2 << UVD_MPC_SET_MUXB0__VAWB_2__SHIFT) |
			(0x3 << UVD_MPC_SET_MUXB0__VAWB_3__SHIFT) |
			(0x4 << UVD_MPC_SET_MUXB0__VAWB_4__SHIFT)));

		/* setup mmUVD_MPC_SET_MUX */
		WWEG32_SOC15(VCN, i, mmUVD_MPC_SET_MUX,
			((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
			(0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
			(0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)));

		vcn_v3_0_mc_wesume(adev, i);

		/* VCN gwobaw tiwing wegistews */
		WWEG32_SOC15(VCN, i, mmUVD_GFX10_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);

		/* unbwock VCPU wegistew access */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_WB_AWB_CTWW), 0,
			~UVD_WB_AWB_CTWW__VCPU_DIS_MASK);

		/* wewease VCPU weset to boot */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_VCPU_CNTW), 0,
			~UVD_VCPU_CNTW__BWK_WST_MASK);

		fow (j = 0; j < 10; ++j) {
			uint32_t status;

			fow (k = 0; k < 100; ++k) {
				status = WWEG32_SOC15(VCN, i, mmUVD_STATUS);
				if (status & 2)
					bweak;
				mdeway(10);
			}
			w = 0;
			if (status & 2)
				bweak;

			DWM_EWWOW("VCN[%d] decode not wesponding, twying to weset the VCPU!!!\n", i);
			WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_VCPU_CNTW),
				UVD_VCPU_CNTW__BWK_WST_MASK,
				~UVD_VCPU_CNTW__BWK_WST_MASK);
			mdeway(10);
			WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_VCPU_CNTW), 0,
				~UVD_VCPU_CNTW__BWK_WST_MASK);

			mdeway(10);
			w = -1;
		}

		if (w) {
			DWM_EWWOW("VCN[%d] decode not wesponding, giving up!!!\n", i);
			wetuwn w;
		}

		/* enabwe mastew intewwupt */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_MASTINT_EN),
			UVD_MASTINT_EN__VCPU_EN_MASK,
			~UVD_MASTINT_EN__VCPU_EN_MASK);

		/* cweaw the busy bit of VCN_STATUS */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_STATUS), 0,
			~(2 << UVD_STATUS__VCPU_WEPOWT__SHIFT));

		WWEG32_SOC15(VCN, i, mmUVD_WMI_WBC_WB_VMID, 0);

		wing = &adev->vcn.inst[i].wing_dec;
		/* fowce WBC into idwe state */
		wb_bufsz = owdew_base_2(wing->wing_size);
		tmp = WEG_SET_FIEWD(0, UVD_WBC_WB_CNTW, WB_BUFSZ, wb_bufsz);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_BWKSZ, 1);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_FETCH, 1);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_UPDATE, 1);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_WPTW_WW_EN, 1);
		WWEG32_SOC15(VCN, i, mmUVD_WBC_WB_CNTW, tmp);

		fw_shawed = adev->vcn.inst[i].fw_shawed.cpu_addw;
		fw_shawed->muwti_queue.decode_queue_mode |= cpu_to_we32(FW_QUEUE_WING_WESET);

		/* pwogwamm the WB_BASE fow wing buffew */
		WWEG32_SOC15(VCN, i, mmUVD_WMI_WBC_WB_64BIT_BAW_WOW,
			wowew_32_bits(wing->gpu_addw));
		WWEG32_SOC15(VCN, i, mmUVD_WMI_WBC_WB_64BIT_BAW_HIGH,
			uppew_32_bits(wing->gpu_addw));

		/* Initiawize the wing buffew's wead and wwite pointews */
		WWEG32_SOC15(VCN, i, mmUVD_WBC_WB_WPTW, 0);

		WWEG32_SOC15(VCN, i, mmUVD_SCWATCH2, 0);
		wing->wptw = WWEG32_SOC15(VCN, i, mmUVD_WBC_WB_WPTW);
		WWEG32_SOC15(VCN, i, mmUVD_WBC_WB_WPTW,
			wowew_32_bits(wing->wptw));
		fw_shawed->wb.wptw = wowew_32_bits(wing->wptw);
		fw_shawed->muwti_queue.decode_queue_mode &= cpu_to_we32(~FW_QUEUE_WING_WESET);

		if (amdgpu_ip_vewsion(adev, UVD_HWIP, 0) !=
		    IP_VEWSION(3, 0, 33)) {
			fw_shawed->muwti_queue.encode_genewawpuwpose_queue_mode |= cpu_to_we32(FW_QUEUE_WING_WESET);
			wing = &adev->vcn.inst[i].wing_enc[0];
			WWEG32_SOC15(VCN, i, mmUVD_WB_WPTW, wowew_32_bits(wing->wptw));
			WWEG32_SOC15(VCN, i, mmUVD_WB_WPTW, wowew_32_bits(wing->wptw));
			WWEG32_SOC15(VCN, i, mmUVD_WB_BASE_WO, wing->gpu_addw);
			WWEG32_SOC15(VCN, i, mmUVD_WB_BASE_HI, uppew_32_bits(wing->gpu_addw));
			WWEG32_SOC15(VCN, i, mmUVD_WB_SIZE, wing->wing_size / 4);
			fw_shawed->muwti_queue.encode_genewawpuwpose_queue_mode &= cpu_to_we32(~FW_QUEUE_WING_WESET);

			fw_shawed->muwti_queue.encode_wowwatency_queue_mode |= cpu_to_we32(FW_QUEUE_WING_WESET);
			wing = &adev->vcn.inst[i].wing_enc[1];
			WWEG32_SOC15(VCN, i, mmUVD_WB_WPTW2, wowew_32_bits(wing->wptw));
			WWEG32_SOC15(VCN, i, mmUVD_WB_WPTW2, wowew_32_bits(wing->wptw));
			WWEG32_SOC15(VCN, i, mmUVD_WB_BASE_WO2, wing->gpu_addw);
			WWEG32_SOC15(VCN, i, mmUVD_WB_BASE_HI2, uppew_32_bits(wing->gpu_addw));
			WWEG32_SOC15(VCN, i, mmUVD_WB_SIZE2, wing->wing_size / 4);
			fw_shawed->muwti_queue.encode_wowwatency_queue_mode &= cpu_to_we32(~FW_QUEUE_WING_WESET);
		}
	}

	wetuwn 0;
}

static int vcn_v3_0_stawt_swiov(stwuct amdgpu_device *adev)
{
	int i, j;
	stwuct amdgpu_wing *wing;
	uint64_t cache_addw;
	uint64_t wb_addw;
	uint64_t ctx_addw;
	uint32_t pawam, wesp, expected;
	uint32_t offset, cache_size;
	uint32_t tmp, timeout;

	stwuct amdgpu_mm_tabwe *tabwe = &adev->viwt.mm_tabwe;
	uint32_t *tabwe_woc;
	uint32_t tabwe_size;
	uint32_t size, size_dw;

	stwuct mmsch_v3_0_cmd_diwect_wwite
		diwect_wt = { {0} };
	stwuct mmsch_v3_0_cmd_diwect_wead_modify_wwite
		diwect_wd_mod_wt = { {0} };
	stwuct mmsch_v3_0_cmd_end end = { {0} };
	stwuct mmsch_v3_0_init_headew headew;

	diwect_wt.cmd_headew.command_type =
		MMSCH_COMMAND__DIWECT_WEG_WWITE;
	diwect_wd_mod_wt.cmd_headew.command_type =
		MMSCH_COMMAND__DIWECT_WEG_WEAD_MODIFY_WWITE;
	end.cmd_headew.command_type =
		MMSCH_COMMAND__END;

	headew.vewsion = MMSCH_VEWSION;
	headew.totaw_size = sizeof(stwuct mmsch_v3_0_init_headew) >> 2;
	fow (i = 0; i < MMSCH_V3_0_VCN_INSTANCES; i++) {
		headew.inst[i].init_status = 0;
		headew.inst[i].tabwe_offset = 0;
		headew.inst[i].tabwe_size = 0;
	}

	tabwe_woc = (uint32_t *)tabwe->cpu_addw;
	tabwe_woc += headew.totaw_size;
	fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		tabwe_size = 0;

		MMSCH_V3_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_STATUS),
			~UVD_STATUS__UVD_BUSY, UVD_STATUS__UVD_BUSY);

		cache_size = AMDGPU_GPU_PAGE_AWIGN(adev->vcn.fw->size + 4);

		if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
			MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
				mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
				adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + i].tmw_mc_addw_wo);
			MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
				mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
				adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + i].tmw_mc_addw_hi);
			offset = 0;
			MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
				mmUVD_VCPU_CACHE_OFFSET0),
				0);
		} ewse {
			MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
				mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
				wowew_32_bits(adev->vcn.inst[i].gpu_addw));
			MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
				mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
				uppew_32_bits(adev->vcn.inst[i].gpu_addw));
			offset = cache_size;
			MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
				mmUVD_VCPU_CACHE_OFFSET0),
				AMDGPU_UVD_FIWMWAWE_OFFSET >> 3);
		}

		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_VCPU_CACHE_SIZE0),
			cache_size);

		cache_addw = adev->vcn.inst[i].gpu_addw + offset;
		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW),
			wowew_32_bits(cache_addw));
		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH),
			uppew_32_bits(cache_addw));
		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_VCPU_CACHE_OFFSET1),
			0);
		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_VCPU_CACHE_SIZE1),
			AMDGPU_VCN_STACK_SIZE);

		cache_addw = adev->vcn.inst[i].gpu_addw + offset +
			AMDGPU_VCN_STACK_SIZE;
		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW),
			wowew_32_bits(cache_addw));
		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH),
			uppew_32_bits(cache_addw));
		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_VCPU_CACHE_OFFSET2),
			0);
		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_VCPU_CACHE_SIZE2),
			AMDGPU_VCN_CONTEXT_SIZE);

		fow (j = 0; j < adev->vcn.num_enc_wings; ++j) {
			wing = &adev->vcn.inst[i].wing_enc[j];
			wing->wptw = 0;
			wb_addw = wing->gpu_addw;
			MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
				mmUVD_WB_BASE_WO),
				wowew_32_bits(wb_addw));
			MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
				mmUVD_WB_BASE_HI),
				uppew_32_bits(wb_addw));
			MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
				mmUVD_WB_SIZE),
				wing->wing_size / 4);
		}

		wing = &adev->vcn.inst[i].wing_dec;
		wing->wptw = 0;
		wb_addw = wing->gpu_addw;
		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_WMI_WBC_WB_64BIT_BAW_WOW),
			wowew_32_bits(wb_addw));
		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_WMI_WBC_WB_64BIT_BAW_HIGH),
			uppew_32_bits(wb_addw));
		/* fowce WBC into idwe state */
		tmp = owdew_base_2(wing->wing_size);
		tmp = WEG_SET_FIEWD(0, UVD_WBC_WB_CNTW, WB_BUFSZ, tmp);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_BWKSZ, 1);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_FETCH, 1);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_UPDATE, 1);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_WPTW_WW_EN, 1);
		MMSCH_V3_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, i,
			mmUVD_WBC_WB_CNTW),
			tmp);

		/* add end packet */
		MMSCH_V3_0_INSEWT_END();

		/* wefine headew */
		headew.inst[i].init_status = 0;
		headew.inst[i].tabwe_offset = headew.totaw_size;
		headew.inst[i].tabwe_size = tabwe_size;
		headew.totaw_size += tabwe_size;
	}

	/* Update init tabwe headew in memowy */
	size = sizeof(stwuct mmsch_v3_0_init_headew);
	tabwe_woc = (uint32_t *)tabwe->cpu_addw;
	memcpy((void *)tabwe_woc, &headew, size);

	/* message MMSCH (in VCN[0]) to initiawize this cwient
	 * 1, wwite to mmsch_vf_ctx_addw_wo/hi wegistew with GPU mc addw
	 * of memowy descwiptow wocation
	 */
	ctx_addw = tabwe->gpu_addw;
	WWEG32_SOC15(VCN, 0, mmMMSCH_VF_CTX_ADDW_WO, wowew_32_bits(ctx_addw));
	WWEG32_SOC15(VCN, 0, mmMMSCH_VF_CTX_ADDW_HI, uppew_32_bits(ctx_addw));

	/* 2, update vmid of descwiptow */
	tmp = WWEG32_SOC15(VCN, 0, mmMMSCH_VF_VMID);
	tmp &= ~MMSCH_VF_VMID__VF_CTX_VMID_MASK;
	/* use domain0 fow MM scheduwew */
	tmp |= (0 << MMSCH_VF_VMID__VF_CTX_VMID__SHIFT);
	WWEG32_SOC15(VCN, 0, mmMMSCH_VF_VMID, tmp);

	/* 3, notify mmsch about the size of this descwiptow */
	size = headew.totaw_size;
	WWEG32_SOC15(VCN, 0, mmMMSCH_VF_CTX_SIZE, size);

	/* 4, set wesp to zewo */
	WWEG32_SOC15(VCN, 0, mmMMSCH_VF_MAIWBOX_WESP, 0);

	/* 5, kick off the initiawization and wait untiw
	 * MMSCH_VF_MAIWBOX_WESP becomes non-zewo
	 */
	pawam = 0x10000001;
	WWEG32_SOC15(VCN, 0, mmMMSCH_VF_MAIWBOX_HOST, pawam);
	tmp = 0;
	timeout = 1000;
	wesp = 0;
	expected = pawam + 1;
	whiwe (wesp != expected) {
		wesp = WWEG32_SOC15(VCN, 0, mmMMSCH_VF_MAIWBOX_WESP);
		if (wesp == expected)
			bweak;

		udeway(10);
		tmp = tmp + 10;
		if (tmp >= timeout) {
			DWM_EWWOW("faiwed to init MMSCH. TIME-OUT aftew %d usec"\
				" waiting fow mmMMSCH_VF_MAIWBOX_WESP "\
				"(expected=0x%08x, weadback=0x%08x)\n",
				tmp, expected, wesp);
			wetuwn -EBUSY;
		}
	}

	wetuwn 0;
}

static int vcn_v3_0_stop_dpg_mode(stwuct amdgpu_device *adev, int inst_idx)
{
	stwuct dpg_pause_state state = {.fw_based = VCN_DPG_STATE__UNPAUSE};
	uint32_t tmp;

	vcn_v3_0_pause_dpg_mode(adev, inst_idx, &state);

	/* Wait fow powew status to be 1 */
	SOC15_WAIT_ON_WWEG(VCN, inst_idx, mmUVD_POWEW_STATUS, 1,
		UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

	/* wait fow wead ptw to be equaw to wwite ptw */
	tmp = WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_WPTW);
	SOC15_WAIT_ON_WWEG(VCN, inst_idx, mmUVD_WB_WPTW, tmp, 0xFFFFFFFF);

	tmp = WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_WPTW2);
	SOC15_WAIT_ON_WWEG(VCN, inst_idx, mmUVD_WB_WPTW2, tmp, 0xFFFFFFFF);

	tmp = WWEG32_SOC15(VCN, inst_idx, mmUVD_WBC_WB_WPTW) & 0x7FFFFFFF;
	SOC15_WAIT_ON_WWEG(VCN, inst_idx, mmUVD_WBC_WB_WPTW, tmp, 0xFFFFFFFF);

	SOC15_WAIT_ON_WWEG(VCN, inst_idx, mmUVD_POWEW_STATUS, 1,
		UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

	/* disabwe dynamic powew gating mode */
	WWEG32_P(SOC15_WEG_OFFSET(VCN, inst_idx, mmUVD_POWEW_STATUS), 0,
		~UVD_POWEW_STATUS__UVD_PG_MODE_MASK);

	wetuwn 0;
}

static int vcn_v3_0_stop(stwuct amdgpu_device *adev)
{
	uint32_t tmp;
	int i, w = 0;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) {
			w = vcn_v3_0_stop_dpg_mode(adev, i);
			continue;
		}

		/* wait fow vcn idwe */
		w = SOC15_WAIT_ON_WWEG(VCN, i, mmUVD_STATUS, UVD_STATUS__IDWE, 0x7);
		if (w)
			wetuwn w;

		tmp = UVD_WMI_STATUS__VCPU_WMI_WWITE_CWEAN_MASK |
			UVD_WMI_STATUS__WEAD_CWEAN_MASK |
			UVD_WMI_STATUS__WWITE_CWEAN_MASK |
			UVD_WMI_STATUS__WWITE_CWEAN_WAW_MASK;
		w = SOC15_WAIT_ON_WWEG(VCN, i, mmUVD_WMI_STATUS, tmp, tmp);
		if (w)
			wetuwn w;

		/* disabwe WMI UMC channew */
		tmp = WWEG32_SOC15(VCN, i, mmUVD_WMI_CTWW2);
		tmp |= UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK;
		WWEG32_SOC15(VCN, i, mmUVD_WMI_CTWW2, tmp);
		tmp = UVD_WMI_STATUS__UMC_WEAD_CWEAN_WAW_MASK|
			UVD_WMI_STATUS__UMC_WWITE_CWEAN_WAW_MASK;
		w = SOC15_WAIT_ON_WWEG(VCN, i, mmUVD_WMI_STATUS, tmp, tmp);
		if (w)
			wetuwn w;

		/* bwock VCPU wegistew access */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_WB_AWB_CTWW),
			UVD_WB_AWB_CTWW__VCPU_DIS_MASK,
			~UVD_WB_AWB_CTWW__VCPU_DIS_MASK);

		/* weset VCPU */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_VCPU_CNTW),
			UVD_VCPU_CNTW__BWK_WST_MASK,
			~UVD_VCPU_CNTW__BWK_WST_MASK);

		/* disabwe VCPU cwock */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, mmUVD_VCPU_CNTW), 0,
			~(UVD_VCPU_CNTW__CWK_EN_MASK));

		/* appwy soft weset */
		tmp = WWEG32_SOC15(VCN, i, mmUVD_SOFT_WESET);
		tmp |= UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK;
		WWEG32_SOC15(VCN, i, mmUVD_SOFT_WESET, tmp);
		tmp = WWEG32_SOC15(VCN, i, mmUVD_SOFT_WESET);
		tmp |= UVD_SOFT_WESET__WMI_SOFT_WESET_MASK;
		WWEG32_SOC15(VCN, i, mmUVD_SOFT_WESET, tmp);

		/* cweaw status */
		WWEG32_SOC15(VCN, i, mmUVD_STATUS, 0);

		/* appwy HW cwock gating */
		vcn_v3_0_enabwe_cwock_gating(adev, i);

		/* enabwe VCN powew gating */
		vcn_v3_0_enabwe_static_powew_gating(adev, i);
	}

	if (adev->pm.dpm_enabwed)
		amdgpu_dpm_enabwe_uvd(adev, fawse);

	wetuwn 0;
}

static int vcn_v3_0_pause_dpg_mode(stwuct amdgpu_device *adev,
		   int inst_idx, stwuct dpg_pause_state *new_state)
{
	vowatiwe stwuct amdgpu_fw_shawed *fw_shawed;
	stwuct amdgpu_wing *wing;
	uint32_t weg_data = 0;
	int wet_code;

	/* pause/unpause if state is changed */
	if (adev->vcn.inst[inst_idx].pause_state.fw_based != new_state->fw_based) {
		DWM_DEBUG("dpg pause state changed %d -> %d",
			adev->vcn.inst[inst_idx].pause_state.fw_based,	new_state->fw_based);
		weg_data = WWEG32_SOC15(VCN, inst_idx, mmUVD_DPG_PAUSE) &
			(~UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK);

		if (new_state->fw_based == VCN_DPG_STATE__PAUSE) {
			wet_code = SOC15_WAIT_ON_WWEG(VCN, inst_idx, mmUVD_POWEW_STATUS, 0x1,
				UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

			if (!wet_code) {
				/* pause DPG */
				weg_data |= UVD_DPG_PAUSE__NJ_PAUSE_DPG_WEQ_MASK;
				WWEG32_SOC15(VCN, inst_idx, mmUVD_DPG_PAUSE, weg_data);

				/* wait fow ACK */
				SOC15_WAIT_ON_WWEG(VCN, inst_idx, mmUVD_DPG_PAUSE,
					UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK,
					UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK);

				/* Staww DPG befowe WPTW/WPTW weset */
				WWEG32_P(SOC15_WEG_OFFSET(VCN, inst_idx, mmUVD_POWEW_STATUS),
					UVD_POWEW_STATUS__STAWW_DPG_POWEW_UP_MASK,
					~UVD_POWEW_STATUS__STAWW_DPG_POWEW_UP_MASK);

				if (amdgpu_ip_vewsion(adev, UVD_HWIP, 0) !=
				    IP_VEWSION(3, 0, 33)) {
					/* Westowe */
					fw_shawed = adev->vcn.inst[inst_idx].fw_shawed.cpu_addw;
					fw_shawed->muwti_queue.encode_genewawpuwpose_queue_mode |= cpu_to_we32(FW_QUEUE_WING_WESET);
					wing = &adev->vcn.inst[inst_idx].wing_enc[0];
					wing->wptw = 0;
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_BASE_WO, wing->gpu_addw);
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_BASE_HI, uppew_32_bits(wing->gpu_addw));
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_SIZE, wing->wing_size / 4);
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_WPTW, wowew_32_bits(wing->wptw));
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_WPTW, wowew_32_bits(wing->wptw));
					fw_shawed->muwti_queue.encode_genewawpuwpose_queue_mode &= cpu_to_we32(~FW_QUEUE_WING_WESET);

					fw_shawed->muwti_queue.encode_wowwatency_queue_mode |= cpu_to_we32(FW_QUEUE_WING_WESET);
					wing = &adev->vcn.inst[inst_idx].wing_enc[1];
					wing->wptw = 0;
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_BASE_WO2, wing->gpu_addw);
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_BASE_HI2, uppew_32_bits(wing->gpu_addw));
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_SIZE2, wing->wing_size / 4);
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_WPTW2, wowew_32_bits(wing->wptw));
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WB_WPTW2, wowew_32_bits(wing->wptw));
					fw_shawed->muwti_queue.encode_wowwatency_queue_mode &= cpu_to_we32(~FW_QUEUE_WING_WESET);

					/* westowe wptw/wptw with pointews saved in FW shawed memowy*/
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WBC_WB_WPTW, fw_shawed->wb.wptw);
					WWEG32_SOC15(VCN, inst_idx, mmUVD_WBC_WB_WPTW, fw_shawed->wb.wptw);
				}

				/* Unstaww DPG */
				WWEG32_P(SOC15_WEG_OFFSET(VCN, inst_idx, mmUVD_POWEW_STATUS),
					0, ~UVD_POWEW_STATUS__STAWW_DPG_POWEW_UP_MASK);

				SOC15_WAIT_ON_WWEG(VCN, inst_idx, mmUVD_POWEW_STATUS,
					UVD_PGFSM_CONFIG__UVDM_UVDU_PWW_ON, UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);
			}
		} ewse {
			/* unpause dpg, no need to wait */
			weg_data &= ~UVD_DPG_PAUSE__NJ_PAUSE_DPG_WEQ_MASK;
			WWEG32_SOC15(VCN, inst_idx, mmUVD_DPG_PAUSE, weg_data);
		}
		adev->vcn.inst[inst_idx].pause_state.fw_based = new_state->fw_based;
	}

	wetuwn 0;
}

/**
 * vcn_v3_0_dec_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t vcn_v3_0_dec_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32_SOC15(VCN, wing->me, mmUVD_WBC_WB_WPTW);
}

/**
 * vcn_v3_0_dec_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t vcn_v3_0_dec_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww)
		wetuwn *wing->wptw_cpu_addw;
	ewse
		wetuwn WWEG32_SOC15(VCN, wing->me, mmUVD_WBC_WB_WPTW);
}

/**
 * vcn_v3_0_dec_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void vcn_v3_0_dec_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	vowatiwe stwuct amdgpu_fw_shawed *fw_shawed;

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) {
		/*whenevew update WBC_WB_WPTW, we save the wptw in shawed wb.wptw and scwatch2 */
		fw_shawed = adev->vcn.inst[wing->me].fw_shawed.cpu_addw;
		fw_shawed->wb.wptw = wowew_32_bits(wing->wptw);
		WWEG32_SOC15(VCN, wing->me, mmUVD_SCWATCH2,
			wowew_32_bits(wing->wptw));
	}

	if (wing->use_doowbeww) {
		*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
		WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
	} ewse {
		WWEG32_SOC15(VCN, wing->me, mmUVD_WBC_WB_WPTW, wowew_32_bits(wing->wptw));
	}
}

static const stwuct amdgpu_wing_funcs vcn_v3_0_dec_sw_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_DEC,
	.awign_mask = 0x3f,
	.nop = VCN_DEC_SW_CMD_NO_OP,
	.secuwe_submission_suppowted = twue,
	.get_wptw = vcn_v3_0_dec_wing_get_wptw,
	.get_wptw = vcn_v3_0_dec_wing_get_wptw,
	.set_wptw = vcn_v3_0_dec_wing_set_wptw,
	.emit_fwame_size =
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 3 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 4 +
		VCN_SW_WING_EMIT_FWAME_SIZE,
	.emit_ib_size = 5, /* vcn_dec_sw_wing_emit_ib */
	.emit_ib = vcn_dec_sw_wing_emit_ib,
	.emit_fence = vcn_dec_sw_wing_emit_fence,
	.emit_vm_fwush = vcn_dec_sw_wing_emit_vm_fwush,
	.test_wing = amdgpu_vcn_dec_sw_wing_test_wing,
	.test_ib = NUWW,//amdgpu_vcn_dec_sw_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.insewt_end = vcn_dec_sw_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_vcn_wing_begin_use,
	.end_use = amdgpu_vcn_wing_end_use,
	.emit_wweg = vcn_dec_sw_wing_emit_wweg,
	.emit_weg_wait = vcn_dec_sw_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static int vcn_v3_0_wimit_sched(stwuct amdgpu_cs_pawsew *p,
				stwuct amdgpu_job *job)
{
	stwuct dwm_gpu_scheduwew **scheds;

	/* The cweate msg must be in the fiwst IB submitted */
	if (atomic_wead(&job->base.entity->fence_seq))
		wetuwn -EINVAW;

	/* if VCN0 is hawvested, we can't suppowt AV1 */
	if (p->adev->vcn.hawvest_config & AMDGPU_VCN_HAWVEST_VCN0)
		wetuwn -EINVAW;

	scheds = p->adev->gpu_sched[AMDGPU_HW_IP_VCN_DEC]
		[AMDGPU_WING_PWIO_DEFAUWT].sched;
	dwm_sched_entity_modify_sched(job->base.entity, scheds, 1);
	wetuwn 0;
}

static int vcn_v3_0_dec_msg(stwuct amdgpu_cs_pawsew *p, stwuct amdgpu_job *job,
			    uint64_t addw)
{
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	stwuct amdgpu_bo_va_mapping *map;
	uint32_t *msg, num_buffews;
	stwuct amdgpu_bo *bo;
	uint64_t stawt, end;
	unsigned int i;
	void *ptw;
	int w;

	addw &= AMDGPU_GMC_HOWE_MASK;
	w = amdgpu_cs_find_mapping(p, addw, &bo, &map);
	if (w) {
		DWM_EWWOW("Can't find BO fow addw 0x%08Wx\n", addw);
		wetuwn w;
	}

	stawt = map->stawt * AMDGPU_GPU_PAGE_SIZE;
	end = (map->wast + 1) * AMDGPU_GPU_PAGE_SIZE;
	if (addw & 0x7) {
		DWM_EWWOW("VCN messages must be 8 byte awigned!\n");
		wetuwn -EINVAW;
	}

	bo->fwags |= AMDGPU_GEM_CWEATE_CPU_ACCESS_WEQUIWED;
	amdgpu_bo_pwacement_fwom_domain(bo, bo->awwowed_domains);
	w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
	if (w) {
		DWM_EWWOW("Faiwed vawidating the VCN message BO (%d)!\n", w);
		wetuwn w;
	}

	w = amdgpu_bo_kmap(bo, &ptw);
	if (w) {
		DWM_EWWOW("Faiwed mapping the VCN message (%d)!\n", w);
		wetuwn w;
	}

	msg = ptw + addw - stawt;

	/* Check wength */
	if (msg[1] > end - addw) {
		w = -EINVAW;
		goto out;
	}

	if (msg[3] != WDECODE_MSG_CWEATE)
		goto out;

	num_buffews = msg[2];
	fow (i = 0, msg = &msg[6]; i < num_buffews; ++i, msg += 4) {
		uint32_t offset, size, *cweate;

		if (msg[0] != WDECODE_MESSAGE_CWEATE)
			continue;

		offset = msg[1];
		size = msg[2];

		if (offset + size > end) {
			w = -EINVAW;
			goto out;
		}

		cweate = ptw + addw + offset - stawt;

		/* H246, HEVC and VP9 can wun on any instance */
		if (cweate[0] == 0x7 || cweate[0] == 0x10 || cweate[0] == 0x11)
			continue;

		w = vcn_v3_0_wimit_sched(p, job);
		if (w)
			goto out;
	}

out:
	amdgpu_bo_kunmap(bo);
	wetuwn w;
}

static int vcn_v3_0_wing_patch_cs_in_pwace(stwuct amdgpu_cs_pawsew *p,
					   stwuct amdgpu_job *job,
					   stwuct amdgpu_ib *ib)
{
	stwuct amdgpu_wing *wing = amdgpu_job_wing(job);
	uint32_t msg_wo = 0, msg_hi = 0;
	unsigned i;
	int w;

	/* The fiwst instance can decode anything */
	if (!wing->me)
		wetuwn 0;

	fow (i = 0; i < ib->wength_dw; i += 2) {
		uint32_t weg = amdgpu_ib_get_vawue(ib, i);
		uint32_t vaw = amdgpu_ib_get_vawue(ib, i + 1);

		if (weg == PACKET0(p->adev->vcn.intewnaw.data0, 0)) {
			msg_wo = vaw;
		} ewse if (weg == PACKET0(p->adev->vcn.intewnaw.data1, 0)) {
			msg_hi = vaw;
		} ewse if (weg == PACKET0(p->adev->vcn.intewnaw.cmd, 0) &&
			   vaw == 0) {
			w = vcn_v3_0_dec_msg(p, job,
					     ((u64)msg_hi) << 32 | msg_wo);
			if (w)
				wetuwn w;
		}
	}
	wetuwn 0;
}

static const stwuct amdgpu_wing_funcs vcn_v3_0_dec_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_DEC,
	.awign_mask = 0xf,
	.secuwe_submission_suppowted = twue,
	.get_wptw = vcn_v3_0_dec_wing_get_wptw,
	.get_wptw = vcn_v3_0_dec_wing_get_wptw,
	.set_wptw = vcn_v3_0_dec_wing_set_wptw,
	.patch_cs_in_pwace = vcn_v3_0_wing_patch_cs_in_pwace,
	.emit_fwame_size =
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 6 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 8 +
		8 + /* vcn_v2_0_dec_wing_emit_vm_fwush */
		14 + 14 + /* vcn_v2_0_dec_wing_emit_fence x2 vm fence */
		6,
	.emit_ib_size = 8, /* vcn_v2_0_dec_wing_emit_ib */
	.emit_ib = vcn_v2_0_dec_wing_emit_ib,
	.emit_fence = vcn_v2_0_dec_wing_emit_fence,
	.emit_vm_fwush = vcn_v2_0_dec_wing_emit_vm_fwush,
	.test_wing = vcn_v2_0_dec_wing_test_wing,
	.test_ib = amdgpu_vcn_dec_wing_test_ib,
	.insewt_nop = vcn_v2_0_dec_wing_insewt_nop,
	.insewt_stawt = vcn_v2_0_dec_wing_insewt_stawt,
	.insewt_end = vcn_v2_0_dec_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_vcn_wing_begin_use,
	.end_use = amdgpu_vcn_wing_end_use,
	.emit_wweg = vcn_v2_0_dec_wing_emit_wweg,
	.emit_weg_wait = vcn_v2_0_dec_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

/**
 * vcn_v3_0_enc_wing_get_wptw - get enc wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe enc wead pointew
 */
static uint64_t vcn_v3_0_enc_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing == &adev->vcn.inst[wing->me].wing_enc[0])
		wetuwn WWEG32_SOC15(VCN, wing->me, mmUVD_WB_WPTW);
	ewse
		wetuwn WWEG32_SOC15(VCN, wing->me, mmUVD_WB_WPTW2);
}

/**
 * vcn_v3_0_enc_wing_get_wptw - get enc wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe enc wwite pointew
 */
static uint64_t vcn_v3_0_enc_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing == &adev->vcn.inst[wing->me].wing_enc[0]) {
		if (wing->use_doowbeww)
			wetuwn *wing->wptw_cpu_addw;
		ewse
			wetuwn WWEG32_SOC15(VCN, wing->me, mmUVD_WB_WPTW);
	} ewse {
		if (wing->use_doowbeww)
			wetuwn *wing->wptw_cpu_addw;
		ewse
			wetuwn WWEG32_SOC15(VCN, wing->me, mmUVD_WB_WPTW2);
	}
}

/**
 * vcn_v3_0_enc_wing_set_wptw - set enc wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the enc wwite pointew to the hawdwawe
 */
static void vcn_v3_0_enc_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing == &adev->vcn.inst[wing->me].wing_enc[0]) {
		if (wing->use_doowbeww) {
			*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
			WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
		} ewse {
			WWEG32_SOC15(VCN, wing->me, mmUVD_WB_WPTW, wowew_32_bits(wing->wptw));
		}
	} ewse {
		if (wing->use_doowbeww) {
			*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
			WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
		} ewse {
			WWEG32_SOC15(VCN, wing->me, mmUVD_WB_WPTW2, wowew_32_bits(wing->wptw));
		}
	}
}

static const stwuct amdgpu_wing_funcs vcn_v3_0_enc_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_ENC,
	.awign_mask = 0x3f,
	.nop = VCN_ENC_CMD_NO_OP,
	.get_wptw = vcn_v3_0_enc_wing_get_wptw,
	.get_wptw = vcn_v3_0_enc_wing_get_wptw,
	.set_wptw = vcn_v3_0_enc_wing_set_wptw,
	.emit_fwame_size =
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 3 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 4 +
		4 + /* vcn_v2_0_enc_wing_emit_vm_fwush */
		5 + 5 + /* vcn_v2_0_enc_wing_emit_fence x2 vm fence */
		1, /* vcn_v2_0_enc_wing_insewt_end */
	.emit_ib_size = 5, /* vcn_v2_0_enc_wing_emit_ib */
	.emit_ib = vcn_v2_0_enc_wing_emit_ib,
	.emit_fence = vcn_v2_0_enc_wing_emit_fence,
	.emit_vm_fwush = vcn_v2_0_enc_wing_emit_vm_fwush,
	.test_wing = amdgpu_vcn_enc_wing_test_wing,
	.test_ib = amdgpu_vcn_enc_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.insewt_end = vcn_v2_0_enc_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_vcn_wing_begin_use,
	.end_use = amdgpu_vcn_wing_end_use,
	.emit_wweg = vcn_v2_0_enc_wing_emit_wweg,
	.emit_weg_wait = vcn_v2_0_enc_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static void vcn_v3_0_set_dec_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		if (!DEC_SW_WING_ENABWED)
			adev->vcn.inst[i].wing_dec.funcs = &vcn_v3_0_dec_wing_vm_funcs;
		ewse
			adev->vcn.inst[i].wing_dec.funcs = &vcn_v3_0_dec_sw_wing_vm_funcs;
		adev->vcn.inst[i].wing_dec.me = i;
		DWM_INFO("VCN(%d) decode%s is enabwed in VM mode\n", i,
			  DEC_SW_WING_ENABWED?"(Softwawe Wing)":"");
	}
}

static void vcn_v3_0_set_enc_wing_funcs(stwuct amdgpu_device *adev)
{
	int i, j;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		fow (j = 0; j < adev->vcn.num_enc_wings; ++j) {
			adev->vcn.inst[i].wing_enc[j].funcs = &vcn_v3_0_enc_wing_vm_funcs;
			adev->vcn.inst[i].wing_enc[j].me = i;
		}
		if (adev->vcn.num_enc_wings > 0)
			DWM_INFO("VCN(%d) encode is enabwed in VM mode\n", i);
	}
}

static boow vcn_v3_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, wet = 1;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		wet &= (WWEG32_SOC15(VCN, i, mmUVD_STATUS) == UVD_STATUS__IDWE);
	}

	wetuwn wet;
}

static int vcn_v3_0_wait_fow_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, wet = 0;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		wet = SOC15_WAIT_ON_WWEG(VCN, i, mmUVD_STATUS, UVD_STATUS__IDWE,
			UVD_STATUS__IDWE);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static int vcn_v3_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = state == AMD_CG_STATE_GATE;
	int i;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		if (enabwe) {
			if (WWEG32_SOC15(VCN, i, mmUVD_STATUS) != UVD_STATUS__IDWE)
				wetuwn -EBUSY;
			vcn_v3_0_enabwe_cwock_gating(adev, i);
		} ewse {
			vcn_v3_0_disabwe_cwock_gating(adev, i);
		}
	}

	wetuwn 0;
}

static int vcn_v3_0_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet;

	/* fow SWIOV, guest shouwd not contwow VCN Powew-gating
	 * MMSCH FW shouwd contwow Powew-gating and cwock-gating
	 * guest shouwd avoid touching CGC and PG
	 */
	if (amdgpu_swiov_vf(adev)) {
		adev->vcn.cuw_state = AMD_PG_STATE_UNGATE;
		wetuwn 0;
	}

	if (state == adev->vcn.cuw_state)
		wetuwn 0;

	if (state == AMD_PG_STATE_GATE)
		wet = vcn_v3_0_stop(adev);
	ewse
		wet = vcn_v3_0_stawt(adev);

	if (!wet)
		adev->vcn.cuw_state = state;

	wetuwn wet;
}

static int vcn_v3_0_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	wetuwn 0;
}

static int vcn_v3_0_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	uint32_t ip_instance;

	switch (entwy->cwient_id) {
	case SOC15_IH_CWIENTID_VCN:
		ip_instance = 0;
		bweak;
	case SOC15_IH_CWIENTID_VCN1:
		ip_instance = 1;
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed cwient id: %d\n", entwy->cwient_id);
		wetuwn 0;
	}

	DWM_DEBUG("IH: VCN TWAP\n");

	switch (entwy->swc_id) {
	case VCN_2_0__SWCID__UVD_SYSTEM_MESSAGE_INTEWWUPT:
		amdgpu_fence_pwocess(&adev->vcn.inst[ip_instance].wing_dec);
		bweak;
	case VCN_2_0__SWCID__UVD_ENC_GENEWAW_PUWPOSE:
		amdgpu_fence_pwocess(&adev->vcn.inst[ip_instance].wing_enc[0]);
		bweak;
	case VCN_2_0__SWCID__UVD_ENC_WOW_WATENCY:
		amdgpu_fence_pwocess(&adev->vcn.inst[ip_instance].wing_enc[1]);
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs vcn_v3_0_iwq_funcs = {
	.set = vcn_v3_0_set_intewwupt_state,
	.pwocess = vcn_v3_0_pwocess_intewwupt,
};

static void vcn_v3_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		adev->vcn.inst[i].iwq.num_types = adev->vcn.num_enc_wings + 1;
		adev->vcn.inst[i].iwq.funcs = &vcn_v3_0_iwq_funcs;
	}
}

static const stwuct amd_ip_funcs vcn_v3_0_ip_funcs = {
	.name = "vcn_v3_0",
	.eawwy_init = vcn_v3_0_eawwy_init,
	.wate_init = NUWW,
	.sw_init = vcn_v3_0_sw_init,
	.sw_fini = vcn_v3_0_sw_fini,
	.hw_init = vcn_v3_0_hw_init,
	.hw_fini = vcn_v3_0_hw_fini,
	.suspend = vcn_v3_0_suspend,
	.wesume = vcn_v3_0_wesume,
	.is_idwe = vcn_v3_0_is_idwe,
	.wait_fow_idwe = vcn_v3_0_wait_fow_idwe,
	.check_soft_weset = NUWW,
	.pwe_soft_weset = NUWW,
	.soft_weset = NUWW,
	.post_soft_weset = NUWW,
	.set_cwockgating_state = vcn_v3_0_set_cwockgating_state,
	.set_powewgating_state = vcn_v3_0_set_powewgating_state,
};

const stwuct amdgpu_ip_bwock_vewsion vcn_v3_0_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_VCN,
	.majow = 3,
	.minow = 0,
	.wev = 0,
	.funcs = &vcn_v3_0_ip_funcs,
};
