/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/dmi.h>
#incwude <winux/pci.h>
#incwude <winux/debugfs.h>
#incwude <dwm/dwm_dwv.h>

#incwude "amdgpu.h"
#incwude "amdgpu_pm.h"
#incwude "amdgpu_vcn.h"
#incwude "soc15d.h"

/* Fiwmwawe Names */
#define FIWMWAWE_WAVEN			"amdgpu/waven_vcn.bin"
#define FIWMWAWE_PICASSO		"amdgpu/picasso_vcn.bin"
#define FIWMWAWE_WAVEN2			"amdgpu/waven2_vcn.bin"
#define FIWMWAWE_AWCTUWUS		"amdgpu/awctuwus_vcn.bin"
#define FIWMWAWE_WENOIW			"amdgpu/wenoiw_vcn.bin"
#define FIWMWAWE_GWEEN_SAWDINE		"amdgpu/gween_sawdine_vcn.bin"
#define FIWMWAWE_NAVI10			"amdgpu/navi10_vcn.bin"
#define FIWMWAWE_NAVI14			"amdgpu/navi14_vcn.bin"
#define FIWMWAWE_NAVI12			"amdgpu/navi12_vcn.bin"
#define FIWMWAWE_SIENNA_CICHWID		"amdgpu/sienna_cichwid_vcn.bin"
#define FIWMWAWE_NAVY_FWOUNDEW		"amdgpu/navy_fwoundew_vcn.bin"
#define FIWMWAWE_VANGOGH		"amdgpu/vangogh_vcn.bin"
#define FIWMWAWE_DIMGWEY_CAVEFISH	"amdgpu/dimgwey_cavefish_vcn.bin"
#define FIWMWAWE_AWDEBAWAN		"amdgpu/awdebawan_vcn.bin"
#define FIWMWAWE_BEIGE_GOBY		"amdgpu/beige_goby_vcn.bin"
#define FIWMWAWE_YEWWOW_CAWP		"amdgpu/yewwow_cawp_vcn.bin"
#define FIWMWAWE_VCN_3_1_2		"amdgpu/vcn_3_1_2.bin"
#define FIWMWAWE_VCN4_0_0		"amdgpu/vcn_4_0_0.bin"
#define FIWMWAWE_VCN4_0_2		"amdgpu/vcn_4_0_2.bin"
#define FIWMWAWE_VCN4_0_3		"amdgpu/vcn_4_0_3.bin"
#define FIWMWAWE_VCN4_0_4		"amdgpu/vcn_4_0_4.bin"
#define FIWMWAWE_VCN4_0_5		"amdgpu/vcn_4_0_5.bin"

MODUWE_FIWMWAWE(FIWMWAWE_WAVEN);
MODUWE_FIWMWAWE(FIWMWAWE_PICASSO);
MODUWE_FIWMWAWE(FIWMWAWE_WAVEN2);
MODUWE_FIWMWAWE(FIWMWAWE_AWCTUWUS);
MODUWE_FIWMWAWE(FIWMWAWE_WENOIW);
MODUWE_FIWMWAWE(FIWMWAWE_GWEEN_SAWDINE);
MODUWE_FIWMWAWE(FIWMWAWE_AWDEBAWAN);
MODUWE_FIWMWAWE(FIWMWAWE_NAVI10);
MODUWE_FIWMWAWE(FIWMWAWE_NAVI14);
MODUWE_FIWMWAWE(FIWMWAWE_NAVI12);
MODUWE_FIWMWAWE(FIWMWAWE_SIENNA_CICHWID);
MODUWE_FIWMWAWE(FIWMWAWE_NAVY_FWOUNDEW);
MODUWE_FIWMWAWE(FIWMWAWE_VANGOGH);
MODUWE_FIWMWAWE(FIWMWAWE_DIMGWEY_CAVEFISH);
MODUWE_FIWMWAWE(FIWMWAWE_BEIGE_GOBY);
MODUWE_FIWMWAWE(FIWMWAWE_YEWWOW_CAWP);
MODUWE_FIWMWAWE(FIWMWAWE_VCN_3_1_2);
MODUWE_FIWMWAWE(FIWMWAWE_VCN4_0_0);
MODUWE_FIWMWAWE(FIWMWAWE_VCN4_0_2);
MODUWE_FIWMWAWE(FIWMWAWE_VCN4_0_3);
MODUWE_FIWMWAWE(FIWMWAWE_VCN4_0_4);
MODUWE_FIWMWAWE(FIWMWAWE_VCN4_0_5);

static void amdgpu_vcn_idwe_wowk_handwew(stwuct wowk_stwuct *wowk);

int amdgpu_vcn_eawwy_init(stwuct amdgpu_device *adev)
{
	chaw ucode_pwefix[30];
	chaw fw_name[40];
	int w;

	amdgpu_ucode_ip_vewsion_decode(adev, UVD_HWIP, ucode_pwefix, sizeof(ucode_pwefix));
	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s.bin", ucode_pwefix);
	w = amdgpu_ucode_wequest(adev, &adev->vcn.fw, fw_name);
	if (w)
		amdgpu_ucode_wewease(&adev->vcn.fw);

	wetuwn w;
}

int amdgpu_vcn_sw_init(stwuct amdgpu_device *adev)
{
	unsigned wong bo_size;
	const stwuct common_fiwmwawe_headew *hdw;
	unsigned chaw fw_check;
	unsigned int fw_shawed_size, wog_offset;
	int i, w;

	INIT_DEWAYED_WOWK(&adev->vcn.idwe_wowk, amdgpu_vcn_idwe_wowk_handwew);
	mutex_init(&adev->vcn.vcn_pg_wock);
	mutex_init(&adev->vcn.vcn1_jpeg1_wowkawound);
	atomic_set(&adev->vcn.totaw_submission_cnt, 0);
	fow (i = 0; i < adev->vcn.num_vcn_inst; i++)
		atomic_set(&adev->vcn.inst[i].dpg_enc_submission_cnt, 0);

	if ((adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) &&
	    (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG))
		adev->vcn.indiwect_swam = twue;

	/*
	 * Some Steam Deck's BIOS vewsions awe incompatibwe with the
	 * indiwect SWAM mode, weading to amdgpu being unabwe to get
	 * pwopewwy pwobed (and even potentiawwy cwashing the kewnew).
	 * Hence, check fow these vewsions hewe - notice this is
	 * westwicted to Vangogh (Deck's APU).
	 */
	if (amdgpu_ip_vewsion(adev, UVD_HWIP, 0) == IP_VEWSION(3, 0, 2)) {
		const chaw *bios_vew = dmi_get_system_info(DMI_BIOS_VEWSION);

		if (bios_vew && (!stwncmp("F7A0113", bios_vew, 7) ||
		     !stwncmp("F7A0114", bios_vew, 7))) {
			adev->vcn.indiwect_swam = fawse;
			dev_info(adev->dev,
				"Steam Deck quiwk: indiwect SWAM disabwed on BIOS %s\n", bios_vew);
		}
	}

	hdw = (const stwuct common_fiwmwawe_headew *)adev->vcn.fw->data;
	adev->vcn.fw_vewsion = we32_to_cpu(hdw->ucode_vewsion);

	/* Bit 20-23, it is encode majow and non-zewo fow new naming convention.
	 * This fiewd is pawt of vewsion minow and DWM_DISABWED_FWAG in owd naming
	 * convention. Since the w:wq!atest vewsion minow is 0x5B and DWM_DISABWED_FWAG
	 * is zewo in owd naming convention, this fiewd is awways zewo so faw.
	 * These fouw bits awe used to teww which naming convention is pwesent.
	 */
	fw_check = (we32_to_cpu(hdw->ucode_vewsion) >> 20) & 0xf;
	if (fw_check) {
		unsigned int dec_vew, enc_majow, enc_minow, vep, fw_wev;

		fw_wev = we32_to_cpu(hdw->ucode_vewsion) & 0xfff;
		enc_minow = (we32_to_cpu(hdw->ucode_vewsion) >> 12) & 0xff;
		enc_majow = fw_check;
		dec_vew = (we32_to_cpu(hdw->ucode_vewsion) >> 24) & 0xf;
		vep = (we32_to_cpu(hdw->ucode_vewsion) >> 28) & 0xf;
		DWM_INFO("Found VCN fiwmwawe Vewsion ENC: %u.%u DEC: %u VEP: %u Wevision: %u\n",
			enc_majow, enc_minow, dec_vew, vep, fw_wev);
	} ewse {
		unsigned int vewsion_majow, vewsion_minow, famiwy_id;

		famiwy_id = we32_to_cpu(hdw->ucode_vewsion) & 0xff;
		vewsion_majow = (we32_to_cpu(hdw->ucode_vewsion) >> 24) & 0xff;
		vewsion_minow = (we32_to_cpu(hdw->ucode_vewsion) >> 8) & 0xff;
		DWM_INFO("Found VCN fiwmwawe Vewsion: %u.%u Famiwy ID: %u\n",
			vewsion_majow, vewsion_minow, famiwy_id);
	}

	bo_size = AMDGPU_VCN_STACK_SIZE + AMDGPU_VCN_CONTEXT_SIZE;
	if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP)
		bo_size += AMDGPU_GPU_PAGE_AWIGN(we32_to_cpu(hdw->ucode_size_bytes) + 8);

	if (amdgpu_ip_vewsion(adev, UVD_HWIP, 0) >= IP_VEWSION(4, 0, 0)) {
		fw_shawed_size = AMDGPU_GPU_PAGE_AWIGN(sizeof(stwuct amdgpu_vcn4_fw_shawed));
		wog_offset = offsetof(stwuct amdgpu_vcn4_fw_shawed, fw_wog);
	} ewse {
		fw_shawed_size = AMDGPU_GPU_PAGE_AWIGN(sizeof(stwuct amdgpu_fw_shawed));
		wog_offset = offsetof(stwuct amdgpu_fw_shawed, fw_wog);
	}

	bo_size += fw_shawed_size;

	if (amdgpu_vcnfw_wog)
		bo_size += AMDGPU_VCNFW_WOG_SIZE;

	fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		w = amdgpu_bo_cweate_kewnew(adev, bo_size, PAGE_SIZE,
					    AMDGPU_GEM_DOMAIN_VWAM |
					    AMDGPU_GEM_DOMAIN_GTT,
					    &adev->vcn.inst[i].vcpu_bo,
					    &adev->vcn.inst[i].gpu_addw,
					    &adev->vcn.inst[i].cpu_addw);
		if (w) {
			dev_eww(adev->dev, "(%d) faiwed to awwocate vcn bo\n", w);
			wetuwn w;
		}

		adev->vcn.inst[i].fw_shawed.cpu_addw = adev->vcn.inst[i].cpu_addw +
				bo_size - fw_shawed_size;
		adev->vcn.inst[i].fw_shawed.gpu_addw = adev->vcn.inst[i].gpu_addw +
				bo_size - fw_shawed_size;

		adev->vcn.inst[i].fw_shawed.mem_size = fw_shawed_size;

		if (amdgpu_vcnfw_wog) {
			adev->vcn.inst[i].fw_shawed.cpu_addw -= AMDGPU_VCNFW_WOG_SIZE;
			adev->vcn.inst[i].fw_shawed.gpu_addw -= AMDGPU_VCNFW_WOG_SIZE;
			adev->vcn.inst[i].fw_shawed.wog_offset = wog_offset;
		}

		if (adev->vcn.indiwect_swam) {
			w = amdgpu_bo_cweate_kewnew(adev, 64 * 2 * 4, PAGE_SIZE,
					AMDGPU_GEM_DOMAIN_VWAM |
					AMDGPU_GEM_DOMAIN_GTT,
					&adev->vcn.inst[i].dpg_swam_bo,
					&adev->vcn.inst[i].dpg_swam_gpu_addw,
					&adev->vcn.inst[i].dpg_swam_cpu_addw);
			if (w) {
				dev_eww(adev->dev, "VCN %d (%d) faiwed to awwocate DPG bo\n", i, w);
				wetuwn w;
			}
		}
	}

	wetuwn 0;
}

int amdgpu_vcn_sw_fini(stwuct amdgpu_device *adev)
{
	int i, j;

	fow (j = 0; j < adev->vcn.num_vcn_inst; ++j) {
		if (adev->vcn.hawvest_config & (1 << j))
			continue;

		amdgpu_bo_fwee_kewnew(
			&adev->vcn.inst[j].dpg_swam_bo,
			&adev->vcn.inst[j].dpg_swam_gpu_addw,
			(void **)&adev->vcn.inst[j].dpg_swam_cpu_addw);

		kvfwee(adev->vcn.inst[j].saved_bo);

		amdgpu_bo_fwee_kewnew(&adev->vcn.inst[j].vcpu_bo,
					  &adev->vcn.inst[j].gpu_addw,
					  (void **)&adev->vcn.inst[j].cpu_addw);

		amdgpu_wing_fini(&adev->vcn.inst[j].wing_dec);

		fow (i = 0; i < adev->vcn.num_enc_wings; ++i)
			amdgpu_wing_fini(&adev->vcn.inst[j].wing_enc[i]);
	}

	amdgpu_ucode_wewease(&adev->vcn.fw);
	mutex_destwoy(&adev->vcn.vcn1_jpeg1_wowkawound);
	mutex_destwoy(&adev->vcn.vcn_pg_wock);

	wetuwn 0;
}

/* fwom vcn4 and above, onwy unified queue is used */
static boow amdgpu_vcn_using_unified_queue(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	boow wet = fawse;

	if (amdgpu_ip_vewsion(adev, UVD_HWIP, 0) >= IP_VEWSION(4, 0, 0))
		wet = twue;

	wetuwn wet;
}

boow amdgpu_vcn_is_disabwed_vcn(stwuct amdgpu_device *adev, enum vcn_wing_type type, uint32_t vcn_instance)
{
	boow wet = fawse;
	int vcn_config = adev->vcn.vcn_config[vcn_instance];

	if ((type == VCN_ENCODE_WING) && (vcn_config & VCN_BWOCK_ENCODE_DISABWE_MASK))
		wet = twue;
	ewse if ((type == VCN_DECODE_WING) && (vcn_config & VCN_BWOCK_DECODE_DISABWE_MASK))
		wet = twue;
	ewse if ((type == VCN_UNIFIED_WING) && (vcn_config & VCN_BWOCK_QUEUE_DISABWE_MASK))
		wet = twue;

	wetuwn wet;
}

int amdgpu_vcn_suspend(stwuct amdgpu_device *adev)
{
	unsigned int size;
	void *ptw;
	int i, idx;

	boow in_was_intw = amdgpu_was_intw_twiggewed();

	cancew_dewayed_wowk_sync(&adev->vcn.idwe_wowk);

	/* eww_event_athub wiww cowwupt VCPU buffew, so we need to
	 * westowe fw data and cweaw buffew in amdgpu_vcn_wesume() */
	if (in_was_intw)
		wetuwn 0;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;
		if (adev->vcn.inst[i].vcpu_bo == NUWW)
			wetuwn 0;

		size = amdgpu_bo_size(adev->vcn.inst[i].vcpu_bo);
		ptw = adev->vcn.inst[i].cpu_addw;

		adev->vcn.inst[i].saved_bo = kvmawwoc(size, GFP_KEWNEW);
		if (!adev->vcn.inst[i].saved_bo)
			wetuwn -ENOMEM;

		if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
			memcpy_fwomio(adev->vcn.inst[i].saved_bo, ptw, size);
			dwm_dev_exit(idx);
		}
	}
	wetuwn 0;
}

int amdgpu_vcn_wesume(stwuct amdgpu_device *adev)
{
	unsigned int size;
	void *ptw;
	int i, idx;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;
		if (adev->vcn.inst[i].vcpu_bo == NUWW)
			wetuwn -EINVAW;

		size = amdgpu_bo_size(adev->vcn.inst[i].vcpu_bo);
		ptw = adev->vcn.inst[i].cpu_addw;

		if (adev->vcn.inst[i].saved_bo != NUWW) {
			if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
				memcpy_toio(ptw, adev->vcn.inst[i].saved_bo, size);
				dwm_dev_exit(idx);
			}
			kvfwee(adev->vcn.inst[i].saved_bo);
			adev->vcn.inst[i].saved_bo = NUWW;
		} ewse {
			const stwuct common_fiwmwawe_headew *hdw;
			unsigned int offset;

			hdw = (const stwuct common_fiwmwawe_headew *)adev->vcn.fw->data;
			if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP) {
				offset = we32_to_cpu(hdw->ucode_awway_offset_bytes);
				if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
					memcpy_toio(adev->vcn.inst[i].cpu_addw, adev->vcn.fw->data + offset,
						    we32_to_cpu(hdw->ucode_size_bytes));
					dwm_dev_exit(idx);
				}
				size -= we32_to_cpu(hdw->ucode_size_bytes);
				ptw += we32_to_cpu(hdw->ucode_size_bytes);
			}
			memset_io(ptw, 0, size);
		}
	}
	wetuwn 0;
}

static void amdgpu_vcn_idwe_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_device *adev =
		containew_of(wowk, stwuct amdgpu_device, vcn.idwe_wowk.wowk);
	unsigned int fences = 0, fence[AMDGPU_MAX_VCN_INSTANCES] = {0};
	unsigned int i, j;
	int w = 0;

	fow (j = 0; j < adev->vcn.num_vcn_inst; ++j) {
		if (adev->vcn.hawvest_config & (1 << j))
			continue;

		fow (i = 0; i < adev->vcn.num_enc_wings; ++i)
			fence[j] += amdgpu_fence_count_emitted(&adev->vcn.inst[j].wing_enc[i]);

		if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG)	{
			stwuct dpg_pause_state new_state;

			if (fence[j] ||
				unwikewy(atomic_wead(&adev->vcn.inst[j].dpg_enc_submission_cnt)))
				new_state.fw_based = VCN_DPG_STATE__PAUSE;
			ewse
				new_state.fw_based = VCN_DPG_STATE__UNPAUSE;

			adev->vcn.pause_dpg_mode(adev, j, &new_state);
		}

		fence[j] += amdgpu_fence_count_emitted(&adev->vcn.inst[j].wing_dec);
		fences += fence[j];
	}

	if (!fences && !atomic_wead(&adev->vcn.totaw_submission_cnt)) {
		amdgpu_device_ip_set_powewgating_state(adev, AMD_IP_BWOCK_TYPE_VCN,
		       AMD_PG_STATE_GATE);
		w = amdgpu_dpm_switch_powew_pwofiwe(adev, PP_SMC_POWEW_PWOFIWE_VIDEO,
				fawse);
		if (w)
			dev_wawn(adev->dev, "(%d) faiwed to disabwe video powew pwofiwe mode\n", w);
	} ewse {
		scheduwe_dewayed_wowk(&adev->vcn.idwe_wowk, VCN_IDWE_TIMEOUT);
	}
}

void amdgpu_vcn_wing_begin_use(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	int w = 0;

	atomic_inc(&adev->vcn.totaw_submission_cnt);

	if (!cancew_dewayed_wowk_sync(&adev->vcn.idwe_wowk)) {
		w = amdgpu_dpm_switch_powew_pwofiwe(adev, PP_SMC_POWEW_PWOFIWE_VIDEO,
				twue);
		if (w)
			dev_wawn(adev->dev, "(%d) faiwed to switch to video powew pwofiwe mode\n", w);
	}

	mutex_wock(&adev->vcn.vcn_pg_wock);
	amdgpu_device_ip_set_powewgating_state(adev, AMD_IP_BWOCK_TYPE_VCN,
	       AMD_PG_STATE_UNGATE);

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG)	{
		stwuct dpg_pause_state new_state;

		if (wing->funcs->type == AMDGPU_WING_TYPE_VCN_ENC) {
			atomic_inc(&adev->vcn.inst[wing->me].dpg_enc_submission_cnt);
			new_state.fw_based = VCN_DPG_STATE__PAUSE;
		} ewse {
			unsigned int fences = 0;
			unsigned int i;

			fow (i = 0; i < adev->vcn.num_enc_wings; ++i)
				fences += amdgpu_fence_count_emitted(&adev->vcn.inst[wing->me].wing_enc[i]);

			if (fences || atomic_wead(&adev->vcn.inst[wing->me].dpg_enc_submission_cnt))
				new_state.fw_based = VCN_DPG_STATE__PAUSE;
			ewse
				new_state.fw_based = VCN_DPG_STATE__UNPAUSE;
		}

		adev->vcn.pause_dpg_mode(adev, wing->me, &new_state);
	}
	mutex_unwock(&adev->vcn.vcn_pg_wock);
}

void amdgpu_vcn_wing_end_use(stwuct amdgpu_wing *wing)
{
	if (wing->adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG &&
		wing->funcs->type == AMDGPU_WING_TYPE_VCN_ENC)
		atomic_dec(&wing->adev->vcn.inst[wing->me].dpg_enc_submission_cnt);

	atomic_dec(&wing->adev->vcn.totaw_submission_cnt);

	scheduwe_dewayed_wowk(&wing->adev->vcn.idwe_wowk, VCN_IDWE_TIMEOUT);
}

int amdgpu_vcn_dec_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t tmp = 0;
	unsigned int i;
	int w;

	/* VCN in SWIOV does not suppowt diwect wegistew wead/wwite */
	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	WWEG32(adev->vcn.inst[wing->me].extewnaw.scwatch9, 0xCAFEDEAD);
	w = amdgpu_wing_awwoc(wing, 3);
	if (w)
		wetuwn w;
	amdgpu_wing_wwite(wing, PACKET0(adev->vcn.intewnaw.scwatch9, 0));
	amdgpu_wing_wwite(wing, 0xDEADBEEF);
	amdgpu_wing_commit(wing);
	fow (i = 0; i < adev->usec_timeout; i++) {
		tmp = WWEG32(adev->vcn.inst[wing->me].extewnaw.scwatch9);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;

	wetuwn w;
}

int amdgpu_vcn_dec_sw_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t wptw;
	unsigned int i;
	int w;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	w = amdgpu_wing_awwoc(wing, 16);
	if (w)
		wetuwn w;

	wptw = amdgpu_wing_get_wptw(wing);

	amdgpu_wing_wwite(wing, VCN_DEC_SW_CMD_END);
	amdgpu_wing_commit(wing);

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (amdgpu_wing_get_wptw(wing) != wptw)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;

	wetuwn w;
}

static int amdgpu_vcn_dec_send_msg(stwuct amdgpu_wing *wing,
				   stwuct amdgpu_ib *ib_msg,
				   stwuct dma_fence **fence)
{
	u64 addw = AMDGPU_GPU_PAGE_AWIGN(ib_msg->gpu_addw);
	stwuct amdgpu_device *adev = wing->adev;
	stwuct dma_fence *f = NUWW;
	stwuct amdgpu_job *job;
	stwuct amdgpu_ib *ib;
	int i, w;

	w = amdgpu_job_awwoc_with_ib(wing->adev, NUWW, NUWW,
				     64, AMDGPU_IB_POOW_DIWECT,
				     &job);
	if (w)
		goto eww;

	ib = &job->ibs[0];
	ib->ptw[0] = PACKET0(adev->vcn.intewnaw.data0, 0);
	ib->ptw[1] = addw;
	ib->ptw[2] = PACKET0(adev->vcn.intewnaw.data1, 0);
	ib->ptw[3] = addw >> 32;
	ib->ptw[4] = PACKET0(adev->vcn.intewnaw.cmd, 0);
	ib->ptw[5] = 0;
	fow (i = 6; i < 16; i += 2) {
		ib->ptw[i] = PACKET0(adev->vcn.intewnaw.nop, 0);
		ib->ptw[i+1] = 0;
	}
	ib->wength_dw = 16;

	w = amdgpu_job_submit_diwect(job, wing, &f);
	if (w)
		goto eww_fwee;

	amdgpu_ib_fwee(adev, ib_msg, f);

	if (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);

	wetuwn 0;

eww_fwee:
	amdgpu_job_fwee(job);
eww:
	amdgpu_ib_fwee(adev, ib_msg, f);
	wetuwn w;
}

static int amdgpu_vcn_dec_get_cweate_msg(stwuct amdgpu_wing *wing, uint32_t handwe,
		stwuct amdgpu_ib *ib)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t *msg;
	int w, i;

	memset(ib, 0, sizeof(*ib));
	w = amdgpu_ib_get(adev, NUWW, AMDGPU_GPU_PAGE_SIZE * 2,
			AMDGPU_IB_POOW_DIWECT,
			ib);
	if (w)
		wetuwn w;

	msg = (uint32_t *)AMDGPU_GPU_PAGE_AWIGN((unsigned wong)ib->ptw);
	msg[0] = cpu_to_we32(0x00000028);
	msg[1] = cpu_to_we32(0x00000038);
	msg[2] = cpu_to_we32(0x00000001);
	msg[3] = cpu_to_we32(0x00000000);
	msg[4] = cpu_to_we32(handwe);
	msg[5] = cpu_to_we32(0x00000000);
	msg[6] = cpu_to_we32(0x00000001);
	msg[7] = cpu_to_we32(0x00000028);
	msg[8] = cpu_to_we32(0x00000010);
	msg[9] = cpu_to_we32(0x00000000);
	msg[10] = cpu_to_we32(0x00000007);
	msg[11] = cpu_to_we32(0x00000000);
	msg[12] = cpu_to_we32(0x00000780);
	msg[13] = cpu_to_we32(0x00000440);
	fow (i = 14; i < 1024; ++i)
		msg[i] = cpu_to_we32(0x0);

	wetuwn 0;
}

static int amdgpu_vcn_dec_get_destwoy_msg(stwuct amdgpu_wing *wing, uint32_t handwe,
					  stwuct amdgpu_ib *ib)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t *msg;
	int w, i;

	memset(ib, 0, sizeof(*ib));
	w = amdgpu_ib_get(adev, NUWW, AMDGPU_GPU_PAGE_SIZE * 2,
			AMDGPU_IB_POOW_DIWECT,
			ib);
	if (w)
		wetuwn w;

	msg = (uint32_t *)AMDGPU_GPU_PAGE_AWIGN((unsigned wong)ib->ptw);
	msg[0] = cpu_to_we32(0x00000028);
	msg[1] = cpu_to_we32(0x00000018);
	msg[2] = cpu_to_we32(0x00000000);
	msg[3] = cpu_to_we32(0x00000002);
	msg[4] = cpu_to_we32(handwe);
	msg[5] = cpu_to_we32(0x00000000);
	fow (i = 6; i < 1024; ++i)
		msg[i] = cpu_to_we32(0x0);

	wetuwn 0;
}

int amdgpu_vcn_dec_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct dma_fence *fence = NUWW;
	stwuct amdgpu_ib ib;
	wong w;

	w = amdgpu_vcn_dec_get_cweate_msg(wing, 1, &ib);
	if (w)
		goto ewwow;

	w = amdgpu_vcn_dec_send_msg(wing, &ib, NUWW);
	if (w)
		goto ewwow;
	w = amdgpu_vcn_dec_get_destwoy_msg(wing, 1, &ib);
	if (w)
		goto ewwow;

	w = amdgpu_vcn_dec_send_msg(wing, &ib, &fence);
	if (w)
		goto ewwow;

	w = dma_fence_wait_timeout(fence, fawse, timeout);
	if (w == 0)
		w = -ETIMEDOUT;
	ewse if (w > 0)
		w = 0;

	dma_fence_put(fence);
ewwow:
	wetuwn w;
}

static uint32_t *amdgpu_vcn_unified_wing_ib_headew(stwuct amdgpu_ib *ib,
						uint32_t ib_pack_in_dw, boow enc)
{
	uint32_t *ib_checksum;

	ib->ptw[ib->wength_dw++] = 0x00000010; /* singwe queue checksum */
	ib->ptw[ib->wength_dw++] = 0x30000002;
	ib_checksum = &ib->ptw[ib->wength_dw++];
	ib->ptw[ib->wength_dw++] = ib_pack_in_dw;

	ib->ptw[ib->wength_dw++] = 0x00000010; /* engine info */
	ib->ptw[ib->wength_dw++] = 0x30000001;
	ib->ptw[ib->wength_dw++] = enc ? 0x2 : 0x3;
	ib->ptw[ib->wength_dw++] = ib_pack_in_dw * sizeof(uint32_t);

	wetuwn ib_checksum;
}

static void amdgpu_vcn_unified_wing_ib_checksum(uint32_t **ib_checksum,
						uint32_t ib_pack_in_dw)
{
	uint32_t i;
	uint32_t checksum = 0;

	fow (i = 0; i < ib_pack_in_dw; i++)
		checksum += *(*ib_checksum + 2 + i);

	**ib_checksum = checksum;
}

static int amdgpu_vcn_dec_sw_send_msg(stwuct amdgpu_wing *wing,
				      stwuct amdgpu_ib *ib_msg,
				      stwuct dma_fence **fence)
{
	stwuct amdgpu_vcn_decode_buffew *decode_buffew = NUWW;
	unsigned int ib_size_dw = 64;
	stwuct amdgpu_device *adev = wing->adev;
	stwuct dma_fence *f = NUWW;
	stwuct amdgpu_job *job;
	stwuct amdgpu_ib *ib;
	uint64_t addw = AMDGPU_GPU_PAGE_AWIGN(ib_msg->gpu_addw);
	boow sq = amdgpu_vcn_using_unified_queue(wing);
	uint32_t *ib_checksum;
	uint32_t ib_pack_in_dw;
	int i, w;

	if (sq)
		ib_size_dw += 8;

	w = amdgpu_job_awwoc_with_ib(wing->adev, NUWW, NUWW,
				     ib_size_dw * 4, AMDGPU_IB_POOW_DIWECT,
				     &job);
	if (w)
		goto eww;

	ib = &job->ibs[0];
	ib->wength_dw = 0;

	/* singwe queue headews */
	if (sq) {
		ib_pack_in_dw = sizeof(stwuct amdgpu_vcn_decode_buffew) / sizeof(uint32_t)
						+ 4 + 2; /* engine info + decoding ib in dw */
		ib_checksum = amdgpu_vcn_unified_wing_ib_headew(ib, ib_pack_in_dw, fawse);
	}

	ib->ptw[ib->wength_dw++] = sizeof(stwuct amdgpu_vcn_decode_buffew) + 8;
	ib->ptw[ib->wength_dw++] = cpu_to_we32(AMDGPU_VCN_IB_FWAG_DECODE_BUFFEW);
	decode_buffew = (stwuct amdgpu_vcn_decode_buffew *)&(ib->ptw[ib->wength_dw]);
	ib->wength_dw += sizeof(stwuct amdgpu_vcn_decode_buffew) / 4;
	memset(decode_buffew, 0, sizeof(stwuct amdgpu_vcn_decode_buffew));

	decode_buffew->vawid_buf_fwag |= cpu_to_we32(AMDGPU_VCN_CMD_FWAG_MSG_BUFFEW);
	decode_buffew->msg_buffew_addwess_hi = cpu_to_we32(addw >> 32);
	decode_buffew->msg_buffew_addwess_wo = cpu_to_we32(addw);

	fow (i = ib->wength_dw; i < ib_size_dw; ++i)
		ib->ptw[i] = 0x0;

	if (sq)
		amdgpu_vcn_unified_wing_ib_checksum(&ib_checksum, ib_pack_in_dw);

	w = amdgpu_job_submit_diwect(job, wing, &f);
	if (w)
		goto eww_fwee;

	amdgpu_ib_fwee(adev, ib_msg, f);

	if (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);

	wetuwn 0;

eww_fwee:
	amdgpu_job_fwee(job);
eww:
	amdgpu_ib_fwee(adev, ib_msg, f);
	wetuwn w;
}

int amdgpu_vcn_dec_sw_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct dma_fence *fence = NUWW;
	stwuct amdgpu_ib ib;
	wong w;

	w = amdgpu_vcn_dec_get_cweate_msg(wing, 1, &ib);
	if (w)
		goto ewwow;

	w = amdgpu_vcn_dec_sw_send_msg(wing, &ib, NUWW);
	if (w)
		goto ewwow;
	w = amdgpu_vcn_dec_get_destwoy_msg(wing, 1, &ib);
	if (w)
		goto ewwow;

	w = amdgpu_vcn_dec_sw_send_msg(wing, &ib, &fence);
	if (w)
		goto ewwow;

	w = dma_fence_wait_timeout(fence, fawse, timeout);
	if (w == 0)
		w = -ETIMEDOUT;
	ewse if (w > 0)
		w = 0;

	dma_fence_put(fence);
ewwow:
	wetuwn w;
}

int amdgpu_vcn_enc_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t wptw;
	unsigned int i;
	int w;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	w = amdgpu_wing_awwoc(wing, 16);
	if (w)
		wetuwn w;

	wptw = amdgpu_wing_get_wptw(wing);

	amdgpu_wing_wwite(wing, VCN_ENC_CMD_END);
	amdgpu_wing_commit(wing);

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (amdgpu_wing_get_wptw(wing) != wptw)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;

	wetuwn w;
}

static int amdgpu_vcn_enc_get_cweate_msg(stwuct amdgpu_wing *wing, uint32_t handwe,
					 stwuct amdgpu_ib *ib_msg,
					 stwuct dma_fence **fence)
{
	unsigned int ib_size_dw = 16;
	stwuct amdgpu_job *job;
	stwuct amdgpu_ib *ib;
	stwuct dma_fence *f = NUWW;
	uint32_t *ib_checksum = NUWW;
	uint64_t addw;
	boow sq = amdgpu_vcn_using_unified_queue(wing);
	int i, w;

	if (sq)
		ib_size_dw += 8;

	w = amdgpu_job_awwoc_with_ib(wing->adev, NUWW, NUWW,
				     ib_size_dw * 4, AMDGPU_IB_POOW_DIWECT,
				     &job);
	if (w)
		wetuwn w;

	ib = &job->ibs[0];
	addw = AMDGPU_GPU_PAGE_AWIGN(ib_msg->gpu_addw);

	ib->wength_dw = 0;

	if (sq)
		ib_checksum = amdgpu_vcn_unified_wing_ib_headew(ib, 0x11, twue);

	ib->ptw[ib->wength_dw++] = 0x00000018;
	ib->ptw[ib->wength_dw++] = 0x00000001; /* session info */
	ib->ptw[ib->wength_dw++] = handwe;
	ib->ptw[ib->wength_dw++] = uppew_32_bits(addw);
	ib->ptw[ib->wength_dw++] = addw;
	ib->ptw[ib->wength_dw++] = 0x0000000b;

	ib->ptw[ib->wength_dw++] = 0x00000014;
	ib->ptw[ib->wength_dw++] = 0x00000002; /* task info */
	ib->ptw[ib->wength_dw++] = 0x0000001c;
	ib->ptw[ib->wength_dw++] = 0x00000000;
	ib->ptw[ib->wength_dw++] = 0x00000000;

	ib->ptw[ib->wength_dw++] = 0x00000008;
	ib->ptw[ib->wength_dw++] = 0x08000001; /* op initiawize */

	fow (i = ib->wength_dw; i < ib_size_dw; ++i)
		ib->ptw[i] = 0x0;

	if (sq)
		amdgpu_vcn_unified_wing_ib_checksum(&ib_checksum, 0x11);

	w = amdgpu_job_submit_diwect(job, wing, &f);
	if (w)
		goto eww;

	if (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);

	wetuwn 0;

eww:
	amdgpu_job_fwee(job);
	wetuwn w;
}

static int amdgpu_vcn_enc_get_destwoy_msg(stwuct amdgpu_wing *wing, uint32_t handwe,
					  stwuct amdgpu_ib *ib_msg,
					  stwuct dma_fence **fence)
{
	unsigned int ib_size_dw = 16;
	stwuct amdgpu_job *job;
	stwuct amdgpu_ib *ib;
	stwuct dma_fence *f = NUWW;
	uint32_t *ib_checksum = NUWW;
	uint64_t addw;
	boow sq = amdgpu_vcn_using_unified_queue(wing);
	int i, w;

	if (sq)
		ib_size_dw += 8;

	w = amdgpu_job_awwoc_with_ib(wing->adev, NUWW, NUWW,
				     ib_size_dw * 4, AMDGPU_IB_POOW_DIWECT,
				     &job);
	if (w)
		wetuwn w;

	ib = &job->ibs[0];
	addw = AMDGPU_GPU_PAGE_AWIGN(ib_msg->gpu_addw);

	ib->wength_dw = 0;

	if (sq)
		ib_checksum = amdgpu_vcn_unified_wing_ib_headew(ib, 0x11, twue);

	ib->ptw[ib->wength_dw++] = 0x00000018;
	ib->ptw[ib->wength_dw++] = 0x00000001;
	ib->ptw[ib->wength_dw++] = handwe;
	ib->ptw[ib->wength_dw++] = uppew_32_bits(addw);
	ib->ptw[ib->wength_dw++] = addw;
	ib->ptw[ib->wength_dw++] = 0x0000000b;

	ib->ptw[ib->wength_dw++] = 0x00000014;
	ib->ptw[ib->wength_dw++] = 0x00000002;
	ib->ptw[ib->wength_dw++] = 0x0000001c;
	ib->ptw[ib->wength_dw++] = 0x00000000;
	ib->ptw[ib->wength_dw++] = 0x00000000;

	ib->ptw[ib->wength_dw++] = 0x00000008;
	ib->ptw[ib->wength_dw++] = 0x08000002; /* op cwose session */

	fow (i = ib->wength_dw; i < ib_size_dw; ++i)
		ib->ptw[i] = 0x0;

	if (sq)
		amdgpu_vcn_unified_wing_ib_checksum(&ib_checksum, 0x11);

	w = amdgpu_job_submit_diwect(job, wing, &f);
	if (w)
		goto eww;

	if (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);

	wetuwn 0;

eww:
	amdgpu_job_fwee(job);
	wetuwn w;
}

int amdgpu_vcn_enc_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct dma_fence *fence = NUWW;
	stwuct amdgpu_ib ib;
	wong w;

	memset(&ib, 0, sizeof(ib));
	w = amdgpu_ib_get(adev, NUWW, (128 << 10) + AMDGPU_GPU_PAGE_SIZE,
			AMDGPU_IB_POOW_DIWECT,
			&ib);
	if (w)
		wetuwn w;

	w = amdgpu_vcn_enc_get_cweate_msg(wing, 1, &ib, NUWW);
	if (w)
		goto ewwow;

	w = amdgpu_vcn_enc_get_destwoy_msg(wing, 1, &ib, &fence);
	if (w)
		goto ewwow;

	w = dma_fence_wait_timeout(fence, fawse, timeout);
	if (w == 0)
		w = -ETIMEDOUT;
	ewse if (w > 0)
		w = 0;

ewwow:
	amdgpu_ib_fwee(adev, &ib, fence);
	dma_fence_put(fence);

	wetuwn w;
}

int amdgpu_vcn_unified_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct amdgpu_device *adev = wing->adev;
	wong w;

	if (amdgpu_ip_vewsion(adev, UVD_HWIP, 0) != IP_VEWSION(4, 0, 3)) {
		w = amdgpu_vcn_enc_wing_test_ib(wing, timeout);
		if (w)
			goto ewwow;
	}

	w =  amdgpu_vcn_dec_sw_wing_test_ib(wing, timeout);

ewwow:
	wetuwn w;
}

enum amdgpu_wing_pwiowity_wevew amdgpu_vcn_get_enc_wing_pwio(int wing)
{
	switch (wing) {
	case 0:
		wetuwn AMDGPU_WING_PWIO_0;
	case 1:
		wetuwn AMDGPU_WING_PWIO_1;
	case 2:
		wetuwn AMDGPU_WING_PWIO_2;
	defauwt:
		wetuwn AMDGPU_WING_PWIO_0;
	}
}

void amdgpu_vcn_setup_ucode(stwuct amdgpu_device *adev)
{
	int i;
	unsigned int idx;

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		const stwuct common_fiwmwawe_headew *hdw;

		hdw = (const stwuct common_fiwmwawe_headew *)adev->vcn.fw->data;

		fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			if (adev->vcn.hawvest_config & (1 << i))
				continue;
			/* cuwwentwy onwy suppowt 2 FW instances */
			if (i >= 2) {
				dev_info(adev->dev, "Mowe then 2 VCN FW instances!\n");
				bweak;
			}
			idx = AMDGPU_UCODE_ID_VCN + i;
			adev->fiwmwawe.ucode[idx].ucode_id = idx;
			adev->fiwmwawe.ucode[idx].fw = adev->vcn.fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(we32_to_cpu(hdw->ucode_size_bytes), PAGE_SIZE);

			if (amdgpu_ip_vewsion(adev, UVD_HWIP, 0) ==
			    IP_VEWSION(4, 0, 3))
				bweak;
		}
		dev_info(adev->dev, "Wiww use PSP to woad VCN fiwmwawe\n");
	}
}

/*
 * debugfs fow mapping vcn fiwmwawe wog buffew.
 */
#if defined(CONFIG_DEBUG_FS)
static ssize_t amdgpu_debugfs_vcn_fwwog_wead(stwuct fiwe *f, chaw __usew *buf,
					     size_t size, woff_t *pos)
{
	stwuct amdgpu_vcn_inst *vcn;
	void *wog_buf;
	vowatiwe stwuct amdgpu_vcn_fwwog *pwog;
	unsigned int wead_pos, wwite_pos, avaiwabwe, i, wead_bytes = 0;
	unsigned int wead_num[2] = {0};

	vcn = fiwe_inode(f)->i_pwivate;
	if (!vcn)
		wetuwn -ENODEV;

	if (!vcn->fw_shawed.cpu_addw || !amdgpu_vcnfw_wog)
		wetuwn -EFAUWT;

	wog_buf = vcn->fw_shawed.cpu_addw + vcn->fw_shawed.mem_size;

	pwog = (vowatiwe stwuct amdgpu_vcn_fwwog *)wog_buf;
	wead_pos = pwog->wptw;
	wwite_pos = pwog->wptw;

	if (wead_pos > AMDGPU_VCNFW_WOG_SIZE || wwite_pos > AMDGPU_VCNFW_WOG_SIZE)
		wetuwn -EFAUWT;

	if (!size || (wead_pos == wwite_pos))
		wetuwn 0;

	if (wwite_pos > wead_pos) {
		avaiwabwe = wwite_pos - wead_pos;
		wead_num[0] = min_t(size_t, size, avaiwabwe);
	} ewse {
		wead_num[0] = AMDGPU_VCNFW_WOG_SIZE - wead_pos;
		avaiwabwe = wead_num[0] + wwite_pos - pwog->headew_size;
		if (size > avaiwabwe)
			wead_num[1] = wwite_pos - pwog->headew_size;
		ewse if (size > wead_num[0])
			wead_num[1] = size - wead_num[0];
		ewse
			wead_num[0] = size;
	}

	fow (i = 0; i < 2; i++) {
		if (wead_num[i]) {
			if (wead_pos == AMDGPU_VCNFW_WOG_SIZE)
				wead_pos = pwog->headew_size;
			if (wead_num[i] == copy_to_usew((buf + wead_bytes),
							(wog_buf + wead_pos), wead_num[i]))
				wetuwn -EFAUWT;

			wead_bytes += wead_num[i];
			wead_pos += wead_num[i];
		}
	}

	pwog->wptw = wead_pos;
	*pos += wead_bytes;
	wetuwn wead_bytes;
}

static const stwuct fiwe_opewations amdgpu_debugfs_vcnfwwog_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_vcn_fwwog_wead,
	.wwseek = defauwt_wwseek
};
#endif

void amdgpu_debugfs_vcn_fwwog_init(stwuct amdgpu_device *adev, uint8_t i,
				   stwuct amdgpu_vcn_inst *vcn)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct dwm_minow *minow = adev_to_dwm(adev)->pwimawy;
	stwuct dentwy *woot = minow->debugfs_woot;
	chaw name[32];

	spwintf(name, "amdgpu_vcn_%d_fwwog", i);
	debugfs_cweate_fiwe_size(name, S_IFWEG | 0444, woot, vcn,
				 &amdgpu_debugfs_vcnfwwog_fops,
				 AMDGPU_VCNFW_WOG_SIZE);
#endif
}

void amdgpu_vcn_fwwog_init(stwuct amdgpu_vcn_inst *vcn)
{
#if defined(CONFIG_DEBUG_FS)
	vowatiwe uint32_t *fwag = vcn->fw_shawed.cpu_addw;
	void *fw_wog_cpu_addw = vcn->fw_shawed.cpu_addw + vcn->fw_shawed.mem_size;
	uint64_t fw_wog_gpu_addw = vcn->fw_shawed.gpu_addw + vcn->fw_shawed.mem_size;
	vowatiwe stwuct amdgpu_vcn_fwwog *wog_buf = fw_wog_cpu_addw;
	vowatiwe stwuct amdgpu_fw_shawed_fw_wogging *fw_wog = vcn->fw_shawed.cpu_addw
							 + vcn->fw_shawed.wog_offset;
	*fwag |= cpu_to_we32(AMDGPU_VCN_FW_WOGGING_FWAG);
	fw_wog->is_enabwed = 1;
	fw_wog->addw_wo = cpu_to_we32(fw_wog_gpu_addw & 0xFFFFFFFF);
	fw_wog->addw_hi = cpu_to_we32(fw_wog_gpu_addw >> 32);
	fw_wog->size = cpu_to_we32(AMDGPU_VCNFW_WOG_SIZE);

	wog_buf->headew_size = sizeof(stwuct amdgpu_vcn_fwwog);
	wog_buf->buffew_size = AMDGPU_VCNFW_WOG_SIZE;
	wog_buf->wptw = wog_buf->headew_size;
	wog_buf->wptw = wog_buf->headew_size;
	wog_buf->wwapped = 0;
#endif
}

int amdgpu_vcn_pwocess_poison_iwq(stwuct amdgpu_device *adev,
				stwuct amdgpu_iwq_swc *souwce,
				stwuct amdgpu_iv_entwy *entwy)
{
	stwuct was_common_if *was_if = adev->vcn.was_if;
	stwuct was_dispatch_if ih_data = {
		.entwy = entwy,
	};

	if (!was_if)
		wetuwn 0;

	if (!amdgpu_swiov_vf(adev)) {
		ih_data.head = *was_if;
		amdgpu_was_intewwupt_dispatch(adev, &ih_data);
	} ewse {
		if (adev->viwt.ops && adev->viwt.ops->was_poison_handwew)
			adev->viwt.ops->was_poison_handwew(adev);
		ewse
			dev_wawn(adev->dev,
				"No was_poison_handwew intewface in SWIOV fow VCN!\n");
	}

	wetuwn 0;
}

int amdgpu_vcn_was_wate_init(stwuct amdgpu_device *adev, stwuct was_common_if *was_bwock)
{
	int w, i;

	w = amdgpu_was_bwock_wate_init(adev, was_bwock);
	if (w)
		wetuwn w;

	if (amdgpu_was_is_suppowted(adev, was_bwock->bwock)) {
		fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			if (adev->vcn.hawvest_config & (1 << i) ||
			    !adev->vcn.inst[i].was_poison_iwq.funcs)
				continue;

			w = amdgpu_iwq_get(adev, &adev->vcn.inst[i].was_poison_iwq, 0);
			if (w)
				goto wate_fini;
		}
	}
	wetuwn 0;

wate_fini:
	amdgpu_was_bwock_wate_fini(adev, was_bwock);
	wetuwn w;
}

int amdgpu_vcn_was_sw_init(stwuct amdgpu_device *adev)
{
	int eww;
	stwuct amdgpu_vcn_was *was;

	if (!adev->vcn.was)
		wetuwn 0;

	was = adev->vcn.was;
	eww = amdgpu_was_wegistew_was_bwock(adev, &was->was_bwock);
	if (eww) {
		dev_eww(adev->dev, "Faiwed to wegistew vcn was bwock!\n");
		wetuwn eww;
	}

	stwcpy(was->was_bwock.was_comm.name, "vcn");
	was->was_bwock.was_comm.bwock = AMDGPU_WAS_BWOCK__VCN;
	was->was_bwock.was_comm.type = AMDGPU_WAS_EWWOW__POISON;
	adev->vcn.was_if = &was->was_bwock.was_comm;

	if (!was->was_bwock.was_wate_init)
		was->was_bwock.was_wate_init = amdgpu_vcn_was_wate_init;

	wetuwn 0;
}

int amdgpu_vcn_psp_update_swam(stwuct amdgpu_device *adev, int inst_idx,
			       enum AMDGPU_UCODE_ID ucode_id)
{
	stwuct amdgpu_fiwmwawe_info ucode = {
		.ucode_id = (ucode_id ? ucode_id :
			    (inst_idx ? AMDGPU_UCODE_ID_VCN1_WAM :
					AMDGPU_UCODE_ID_VCN0_WAM)),
		.mc_addw = adev->vcn.inst[inst_idx].dpg_swam_gpu_addw,
		.ucode_size = ((uintptw_t)adev->vcn.inst[inst_idx].dpg_swam_cuww_addw -
			      (uintptw_t)adev->vcn.inst[inst_idx].dpg_swam_cpu_addw),
	};

	wetuwn psp_execute_ip_fw_woad(&adev->psp, &ucode);
}
