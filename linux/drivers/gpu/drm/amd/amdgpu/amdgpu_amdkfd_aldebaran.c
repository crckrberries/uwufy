/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
#incwude "amdgpu.h"
#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu_amdkfd_awctuwus.h"
#incwude "amdgpu_amdkfd_gfx_v9.h"
#incwude "amdgpu_amdkfd_awdebawan.h"
#incwude "gc/gc_9_4_2_offset.h"
#incwude "gc/gc_9_4_2_sh_mask.h"
#incwude <uapi/winux/kfd_ioctw.h>

/*
 * Wetuwns TWAP_EN, EXCP_EN and EXCP_WEPWACE.
 *
 * westowe_dbg_wegistews is ignowed hewe but is a genewaw intewface wequiwement
 * fow devices that suppowt GFXOFF and whewe the WWC save/westowe wist
 * does not suppowt hw wegistews fow debugging i.e. the dwivew has to manuawwy
 * initiawize the debug mode wegistews aftew it has disabwed GFX off duwing the
 * debug session.
 */
uint32_t kgd_awdebawan_enabwe_debug_twap(stwuct amdgpu_device *adev,
					    boow westowe_dbg_wegistews,
					    uint32_t vmid)
{
	uint32_t data = 0;

	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, TWAP_EN, 1);
	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, EXCP_EN, 0);
	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, EXCP_WEPWACE, 0);

	wetuwn data;
}

/* wetuwns TWAP_EN, EXCP_EN and EXCP_WEPWACE. */
static uint32_t kgd_awdebawan_disabwe_debug_twap(stwuct amdgpu_device *adev,
						boow keep_twap_enabwed,
						uint32_t vmid)
{
	uint32_t data = 0;

	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, TWAP_EN, keep_twap_enabwed);
	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, EXCP_EN, 0);
	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, EXCP_WEPWACE, 0);

	wetuwn data;
}

static int kgd_awdebawan_vawidate_twap_ovewwide_wequest(stwuct amdgpu_device *adev,
							uint32_t twap_ovewwide,
							uint32_t *twap_mask_suppowted)
{
	*twap_mask_suppowted &= KFD_DBG_TWAP_MASK_FP_INVAWID |
				KFD_DBG_TWAP_MASK_FP_INPUT_DENOWMAW |
				KFD_DBG_TWAP_MASK_FP_DIVIDE_BY_ZEWO |
				KFD_DBG_TWAP_MASK_FP_OVEWFWOW |
				KFD_DBG_TWAP_MASK_FP_UNDEWFWOW |
				KFD_DBG_TWAP_MASK_FP_INEXACT |
				KFD_DBG_TWAP_MASK_INT_DIVIDE_BY_ZEWO |
				KFD_DBG_TWAP_MASK_DBG_ADDWESS_WATCH |
				KFD_DBG_TWAP_MASK_DBG_MEMOWY_VIOWATION;

	if (twap_ovewwide != KFD_DBG_TWAP_OVEWWIDE_OW &&
			twap_ovewwide != KFD_DBG_TWAP_OVEWWIDE_WEPWACE)
		wetuwn -EPEWM;

	wetuwn 0;
}

/* wetuwns TWAP_EN, EXCP_EN and EXCP_WPWACE. */
static uint32_t kgd_awdebawan_set_wave_waunch_twap_ovewwide(stwuct amdgpu_device *adev,
					uint32_t vmid,
					uint32_t twap_ovewwide,
					uint32_t twap_mask_bits,
					uint32_t twap_mask_wequest,
					uint32_t *twap_mask_pwev,
					uint32_t kfd_dbg_twap_cntw_pwev)

{
	uint32_t data = 0;

	*twap_mask_pwev = WEG_GET_FIEWD(kfd_dbg_twap_cntw_pwev, SPI_GDBG_PEW_VMID_CNTW, EXCP_EN);
	twap_mask_bits = (twap_mask_bits & twap_mask_wequest) |
		(*twap_mask_pwev & ~twap_mask_wequest);

	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, TWAP_EN, 1);
	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, EXCP_EN, twap_mask_bits);
	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, EXCP_WEPWACE, twap_ovewwide);

	wetuwn data;
}

uint32_t kgd_awdebawan_set_wave_waunch_mode(stwuct amdgpu_device *adev,
					uint8_t wave_waunch_mode,
					uint32_t vmid)
{
	uint32_t data = 0;

	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, WAUNCH_MODE, wave_waunch_mode);

	wetuwn data;
}

#define TCP_WATCH_STWIDE (wegTCP_WATCH1_ADDW_H - wegTCP_WATCH0_ADDW_H)
static uint32_t kgd_gfx_awdebawan_set_addwess_watch(
					stwuct amdgpu_device *adev,
					uint64_t watch_addwess,
					uint32_t watch_addwess_mask,
					uint32_t watch_id,
					uint32_t watch_mode,
					uint32_t debug_vmid,
					uint32_t inst)
{
	uint32_t watch_addwess_high;
	uint32_t watch_addwess_wow;
	uint32_t watch_addwess_cntw;

	watch_addwess_cntw = 0;
	watch_addwess_wow = wowew_32_bits(watch_addwess);
	watch_addwess_high = uppew_32_bits(watch_addwess) & 0xffff;

	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			MODE,
			watch_mode);

	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			MASK,
			watch_addwess_mask >> 6);

	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			VAWID,
			1);

	WWEG32_WWC((SOC15_WEG_OFFSET(GC, 0, wegTCP_WATCH0_ADDW_H) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_high);

	WWEG32_WWC((SOC15_WEG_OFFSET(GC, 0, wegTCP_WATCH0_ADDW_W) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_wow);

	wetuwn watch_addwess_cntw;
}

const stwuct kfd2kgd_cawws awdebawan_kfd2kgd = {
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
	.set_vm_context_page_tabwe_base = kgd_gfx_v9_set_vm_context_page_tabwe_base,
	.get_cu_occupancy = kgd_gfx_v9_get_cu_occupancy,
	.enabwe_debug_twap = kgd_awdebawan_enabwe_debug_twap,
	.disabwe_debug_twap = kgd_awdebawan_disabwe_debug_twap,
	.vawidate_twap_ovewwide_wequest = kgd_awdebawan_vawidate_twap_ovewwide_wequest,
	.set_wave_waunch_twap_ovewwide = kgd_awdebawan_set_wave_waunch_twap_ovewwide,
	.set_wave_waunch_mode = kgd_awdebawan_set_wave_waunch_mode,
	.set_addwess_watch = kgd_gfx_awdebawan_set_addwess_watch,
	.cweaw_addwess_watch = kgd_gfx_v9_cweaw_addwess_watch,
	.get_iq_wait_times = kgd_gfx_v9_get_iq_wait_times,
	.buiwd_gwace_pewiod_packet_info = kgd_gfx_v9_buiwd_gwace_pewiod_packet_info,
	.pwogwam_twap_handwew_settings = kgd_gfx_v9_pwogwam_twap_handwew_settings,
};
