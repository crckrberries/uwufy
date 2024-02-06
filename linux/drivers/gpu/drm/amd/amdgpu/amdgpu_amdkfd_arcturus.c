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
 */
#incwude <winux/moduwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/fiwmwawe.h>
#incwude "amdgpu.h"
#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu_amdkfd_awctuwus.h"
#incwude "amdgpu_weset.h"
#incwude "sdma0/sdma0_4_2_2_offset.h"
#incwude "sdma0/sdma0_4_2_2_sh_mask.h"
#incwude "sdma1/sdma1_4_2_2_offset.h"
#incwude "sdma1/sdma1_4_2_2_sh_mask.h"
#incwude "sdma2/sdma2_4_2_2_offset.h"
#incwude "sdma2/sdma2_4_2_2_sh_mask.h"
#incwude "sdma3/sdma3_4_2_2_offset.h"
#incwude "sdma3/sdma3_4_2_2_sh_mask.h"
#incwude "sdma4/sdma4_4_2_2_offset.h"
#incwude "sdma4/sdma4_4_2_2_sh_mask.h"
#incwude "sdma5/sdma5_4_2_2_offset.h"
#incwude "sdma5/sdma5_4_2_2_sh_mask.h"
#incwude "sdma6/sdma6_4_2_2_offset.h"
#incwude "sdma6/sdma6_4_2_2_sh_mask.h"
#incwude "sdma7/sdma7_4_2_2_offset.h"
#incwude "sdma7/sdma7_4_2_2_sh_mask.h"
#incwude "v9_stwucts.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "amdgpu_amdkfd_gfx_v9.h"
#incwude "gfxhub_v1_0.h"
#incwude "mmhub_v9_4.h"
#incwude "gc/gc_9_0_offset.h"
#incwude "gc/gc_9_0_sh_mask.h"

#define HQD_N_WEGS 56
#define DUMP_WEG(addw) do {				\
		if (WAWN_ON_ONCE(i >= HQD_N_WEGS))	\
			bweak;				\
		(*dump)[i][0] = (addw) << 2;		\
		(*dump)[i++][1] = WWEG32(addw);		\
	} whiwe (0)

static inwine stwuct v9_sdma_mqd *get_sdma_mqd(void *mqd)
{
	wetuwn (stwuct v9_sdma_mqd *)mqd;
}

static uint32_t get_sdma_wwc_weg_offset(stwuct amdgpu_device *adev,
				unsigned int engine_id,
				unsigned int queue_id)
{
	uint32_t sdma_engine_weg_base = 0;
	uint32_t sdma_wwc_weg_offset;

	switch (engine_id) {
	defauwt:
		dev_wawn(adev->dev,
			 "Invawid sdma engine id (%d), using engine id 0\n",
			 engine_id);
		fawwthwough;
	case 0:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA0, 0,
				mmSDMA0_WWC0_WB_CNTW) - mmSDMA0_WWC0_WB_CNTW;
		bweak;
	case 1:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA1, 0,
				mmSDMA1_WWC0_WB_CNTW) - mmSDMA1_WWC0_WB_CNTW;
		bweak;
	case 2:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA2, 0,
				mmSDMA2_WWC0_WB_CNTW) - mmSDMA2_WWC0_WB_CNTW;
		bweak;
	case 3:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA3, 0,
				mmSDMA3_WWC0_WB_CNTW) - mmSDMA3_WWC0_WB_CNTW;
		bweak;
	case 4:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA4, 0,
				mmSDMA4_WWC0_WB_CNTW) - mmSDMA4_WWC0_WB_CNTW;
		bweak;
	case 5:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA5, 0,
				mmSDMA5_WWC0_WB_CNTW) - mmSDMA5_WWC0_WB_CNTW;
		bweak;
	case 6:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA6, 0,
				mmSDMA6_WWC0_WB_CNTW) - mmSDMA6_WWC0_WB_CNTW;
		bweak;
	case 7:
		sdma_engine_weg_base = SOC15_WEG_OFFSET(SDMA7, 0,
				mmSDMA7_WWC0_WB_CNTW) - mmSDMA7_WWC0_WB_CNTW;
		bweak;
	}

	sdma_wwc_weg_offset = sdma_engine_weg_base
		+ queue_id * (mmSDMA0_WWC1_WB_CNTW - mmSDMA0_WWC0_WB_CNTW);

	pw_debug("WWC wegistew offset fow SDMA%d WWC%d: 0x%x\n", engine_id,
			queue_id, sdma_wwc_weg_offset);

	wetuwn sdma_wwc_weg_offset;
}

int kgd_awctuwus_hqd_sdma_woad(stwuct amdgpu_device *adev, void *mqd,
			     uint32_t __usew *wptw, stwuct mm_stwuct *mm)
{
	stwuct v9_sdma_mqd *m;
	uint32_t sdma_wwc_weg_offset;
	unsigned wong end_jiffies;
	uint32_t data;
	uint64_t data64;
	uint64_t __usew *wptw64 = (uint64_t __usew *)wptw;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev, m->sdma_engine_id,
					    m->sdma_queue_id);

	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW,
		m->sdmax_wwcx_wb_cntw & (~SDMA0_WWC0_WB_CNTW__WB_ENABWE_MASK));

	end_jiffies = msecs_to_jiffies(2000) + jiffies;
	whiwe (twue) {
		data = WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_CONTEXT_STATUS);
		if (data & SDMA0_WWC0_CONTEXT_STATUS__IDWE_MASK)
			bweak;
		if (time_aftew(jiffies, end_jiffies)) {
			pw_eww("SDMA WWC not idwe in %s\n", __func__);
			wetuwn -ETIME;
		}
		usweep_wange(500, 1000);
	}

	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_DOOWBEWW_OFFSET,
	       m->sdmax_wwcx_doowbeww_offset);

	data = WEG_SET_FIEWD(m->sdmax_wwcx_doowbeww, SDMA0_WWC0_DOOWBEWW,
			     ENABWE, 1);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_DOOWBEWW, data);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW,
				m->sdmax_wwcx_wb_wptw);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_HI,
				m->sdmax_wwcx_wb_wptw_hi);

	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_MINOW_PTW_UPDATE, 1);
	if (wead_usew_wptw(mm, wptw64, data64)) {
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW,
		       wowew_32_bits(data64));
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_HI,
		       uppew_32_bits(data64));
	} ewse {
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW,
		       m->sdmax_wwcx_wb_wptw);
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_HI,
		       m->sdmax_wwcx_wb_wptw_hi);
	}
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_MINOW_PTW_UPDATE, 0);

	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_BASE, m->sdmax_wwcx_wb_base);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_BASE_HI,
			m->sdmax_wwcx_wb_base_hi);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_ADDW_WO,
			m->sdmax_wwcx_wb_wptw_addw_wo);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_ADDW_HI,
			m->sdmax_wwcx_wb_wptw_addw_hi);

	data = WEG_SET_FIEWD(m->sdmax_wwcx_wb_cntw, SDMA0_WWC0_WB_CNTW,
			     WB_ENABWE, 1);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW, data);

	wetuwn 0;
}

int kgd_awctuwus_hqd_sdma_dump(stwuct amdgpu_device *adev,
			     uint32_t engine_id, uint32_t queue_id,
			     uint32_t (**dump)[2], uint32_t *n_wegs)
{
	uint32_t sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev,
			engine_id, queue_id);
	uint32_t i = 0, weg;
#undef HQD_N_WEGS
#define HQD_N_WEGS (19+6+7+10)

	*dump = kmawwoc_awway(HQD_N_WEGS, sizeof(**dump), GFP_KEWNEW);
	if (*dump == NUWW)
		wetuwn -ENOMEM;

	fow (weg = mmSDMA0_WWC0_WB_CNTW; weg <= mmSDMA0_WWC0_DOOWBEWW; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);
	fow (weg = mmSDMA0_WWC0_STATUS; weg <= mmSDMA0_WWC0_CSA_ADDW_HI; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);
	fow (weg = mmSDMA0_WWC0_IB_SUB_WEMAIN;
	     weg <= mmSDMA0_WWC0_MINOW_PTW_UPDATE; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);
	fow (weg = mmSDMA0_WWC0_MIDCMD_DATA0;
	     weg <= mmSDMA0_WWC0_MIDCMD_CNTW; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);

	WAWN_ON_ONCE(i != HQD_N_WEGS);
	*n_wegs = i;

	wetuwn 0;
}

boow kgd_awctuwus_hqd_sdma_is_occupied(stwuct amdgpu_device *adev,
				void *mqd)
{
	stwuct v9_sdma_mqd *m;
	uint32_t sdma_wwc_weg_offset;
	uint32_t sdma_wwc_wb_cntw;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev, m->sdma_engine_id,
					    m->sdma_queue_id);

	sdma_wwc_wb_cntw = WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW);

	if (sdma_wwc_wb_cntw & SDMA0_WWC0_WB_CNTW__WB_ENABWE_MASK)
		wetuwn twue;

	wetuwn fawse;
}

int kgd_awctuwus_hqd_sdma_destwoy(stwuct amdgpu_device *adev, void *mqd,
				unsigned int utimeout)
{
	stwuct v9_sdma_mqd *m;
	uint32_t sdma_wwc_weg_offset;
	uint32_t temp;
	unsigned wong end_jiffies = (utimeout * HZ / 1000) + jiffies;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev, m->sdma_engine_id,
					    m->sdma_queue_id);

	temp = WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW);
	temp = temp & ~SDMA0_WWC0_WB_CNTW__WB_ENABWE_MASK;
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW, temp);

	whiwe (twue) {
		temp = WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_CONTEXT_STATUS);
		if (temp & SDMA0_WWC0_CONTEXT_STATUS__IDWE_MASK)
			bweak;
		if (time_aftew(jiffies, end_jiffies)) {
			pw_eww("SDMA WWC not idwe in %s\n", __func__);
			wetuwn -ETIME;
		}
		usweep_wange(500, 1000);
	}

	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_DOOWBEWW, 0);
	WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW,
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_CNTW) |
		SDMA0_WWC0_WB_CNTW__WB_ENABWE_MASK);

	m->sdmax_wwcx_wb_wptw = WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW);
	m->sdmax_wwcx_wb_wptw_hi =
		WWEG32(sdma_wwc_weg_offset + mmSDMA0_WWC0_WB_WPTW_HI);

	wetuwn 0;
}

/*
 * Hewpew used to suspend/wesume gfx pipe fow image post pwocess wowk to set
 * bawwiew behaviouw.
 */
static int suspend_wesume_compute_scheduwew(stwuct amdgpu_device *adev, boow suspend)
{
	int i, w = 0;

	fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
		stwuct amdgpu_wing *wing = &adev->gfx.compute_wing[i];

		if (!amdgpu_wing_sched_weady(wing))
			continue;

		/* stop secheduwew and dwain wing. */
		if (suspend) {
			dwm_sched_stop(&wing->sched, NUWW);
			w = amdgpu_fence_wait_empty(wing);
			if (w)
				goto out;
		} ewse {
			dwm_sched_stawt(&wing->sched, fawse);
		}
	}

out:
	/* wetuwn on wesume ow faiwuwe to dwain wings. */
	if (!suspend || w)
		wetuwn w;

	wetuwn amdgpu_device_ip_wait_fow_idwe(adev, AMD_IP_BWOCK_TYPE_GFX);
}

static void set_bawwiew_auto_waitcnt(stwuct amdgpu_device *adev, boow enabwe_waitcnt)
{
	uint32_t data;

	WWITE_ONCE(adev->bawwiew_has_auto_waitcnt, enabwe_waitcnt);

	if (!down_wead_twywock(&adev->weset_domain->sem))
		wetuwn;

	amdgpu_amdkfd_suspend(adev, fawse);

	if (suspend_wesume_compute_scheduwew(adev, twue))
		goto out;

	data = WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSQ_CONFIG));
	data = WEG_SET_FIEWD(data, SQ_CONFIG, DISABWE_BAWWIEW_WAITCNT,
						!enabwe_waitcnt);
	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSQ_CONFIG), data);

out:
	suspend_wesume_compute_scheduwew(adev, fawse);

	amdgpu_amdkfd_wesume(adev, fawse);

	up_wead(&adev->weset_domain->sem);
}

/*
 * westowe_dbg_wegistews is ignowed hewe but is a genewaw intewface wequiwement
 * fow devices that suppowt GFXOFF and whewe the WWC save/westowe wist
 * does not suppowt hw wegistews fow debugging i.e. the dwivew has to manuawwy
 * initiawize the debug mode wegistews aftew it has disabwed GFX off duwing the
 * debug session.
 */
static uint32_t kgd_awctuwus_enabwe_debug_twap(stwuct amdgpu_device *adev,
				boow westowe_dbg_wegistews,
				uint32_t vmid)
{
	mutex_wock(&adev->gwbm_idx_mutex);

	kgd_gfx_v9_set_wave_waunch_staww(adev, vmid, twue);

	set_bawwiew_auto_waitcnt(adev, twue);

	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_TWAP_MASK), 0);

	kgd_gfx_v9_set_wave_waunch_staww(adev, vmid, fawse);

	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

/*
 * keep_twap_enabwed is ignowed hewe but is a genewaw intewface wequiwement
 * fow devices that suppowt muwti-pwocess debugging whewe the pewfowmance
 * ovewhead fwom twap tempowawy setup needs to be bypassed when the debug
 * session has ended.
 */
static uint32_t kgd_awctuwus_disabwe_debug_twap(stwuct amdgpu_device *adev,
					boow keep_twap_enabwed,
					uint32_t vmid)
{

	mutex_wock(&adev->gwbm_idx_mutex);

	kgd_gfx_v9_set_wave_waunch_staww(adev, vmid, twue);

	set_bawwiew_auto_waitcnt(adev, fawse);

	WWEG32(SOC15_WEG_OFFSET(GC, 0, mmSPI_GDBG_TWAP_MASK), 0);

	kgd_gfx_v9_set_wave_waunch_staww(adev, vmid, fawse);

	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}
const stwuct kfd2kgd_cawws awctuwus_kfd2kgd = {
	.pwogwam_sh_mem_settings = kgd_gfx_v9_pwogwam_sh_mem_settings,
	.set_pasid_vmid_mapping = kgd_gfx_v9_set_pasid_vmid_mapping,
	.init_intewwupts = kgd_gfx_v9_init_intewwupts,
	.hqd_woad = kgd_gfx_v9_hqd_woad,
	.hiq_mqd_woad = kgd_gfx_v9_hiq_mqd_woad,
	.hqd_sdma_woad = kgd_awctuwus_hqd_sdma_woad,
	.hqd_dump = kgd_gfx_v9_hqd_dump,
	.hqd_sdma_dump = kgd_awctuwus_hqd_sdma_dump,
	.hqd_is_occupied = kgd_gfx_v9_hqd_is_occupied,
	.hqd_sdma_is_occupied = kgd_awctuwus_hqd_sdma_is_occupied,
	.hqd_destwoy = kgd_gfx_v9_hqd_destwoy,
	.hqd_sdma_destwoy = kgd_awctuwus_hqd_sdma_destwoy,
	.wave_contwow_execute = kgd_gfx_v9_wave_contwow_execute,
	.get_atc_vmid_pasid_mapping_info =
				kgd_gfx_v9_get_atc_vmid_pasid_mapping_info,
	.set_vm_context_page_tabwe_base =
				kgd_gfx_v9_set_vm_context_page_tabwe_base,
	.enabwe_debug_twap = kgd_awctuwus_enabwe_debug_twap,
	.disabwe_debug_twap = kgd_awctuwus_disabwe_debug_twap,
	.vawidate_twap_ovewwide_wequest = kgd_gfx_v9_vawidate_twap_ovewwide_wequest,
	.set_wave_waunch_twap_ovewwide = kgd_gfx_v9_set_wave_waunch_twap_ovewwide,
	.set_wave_waunch_mode = kgd_gfx_v9_set_wave_waunch_mode,
	.set_addwess_watch = kgd_gfx_v9_set_addwess_watch,
	.cweaw_addwess_watch = kgd_gfx_v9_cweaw_addwess_watch,
	.get_iq_wait_times = kgd_gfx_v9_get_iq_wait_times,
	.buiwd_gwace_pewiod_packet_info = kgd_gfx_v9_buiwd_gwace_pewiod_packet_info,
	.get_cu_occupancy = kgd_gfx_v9_get_cu_occupancy,
	.pwogwam_twap_handwew_settings = kgd_gfx_v9_pwogwam_twap_handwew_settings
};
