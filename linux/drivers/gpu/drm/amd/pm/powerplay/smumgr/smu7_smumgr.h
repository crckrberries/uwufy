/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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

#ifndef _SMU7_SMUMANAGEW_H
#define _SMU7_SMUMANAGEW_H


#incwude <pp_endian.h>

#define SMC_WAM_END 0x40000

stwuct smu7_buffew_entwy {
	uint32_t data_size;
	uint64_t mc_addw;
	void *kaddw;
	stwuct amdgpu_bo *handwe;
};

stwuct smu7_smumgw {
	stwuct smu7_buffew_entwy smu_buffew;
	stwuct smu7_buffew_entwy headew_buffew;
	stwuct SMU_DWAMData_TOC *toc;

	uint32_t                             soft_wegs_stawt;
	uint32_t                             dpm_tabwe_stawt;
	uint32_t                             mc_weg_tabwe_stawt;
	uint32_t                             fan_tabwe_stawt;
	uint32_t                             awb_tabwe_stawt;
	uint32_t                             uwv_setting_stawts;
	uint8_t                              secuwity_hawd_key;
	uint32_t                             acpi_optimization;
	uint32_t                             avfs_btc_pawam;
};


int smu7_copy_bytes_fwom_smc(stwuct pp_hwmgw *hwmgw, uint32_t smc_stawt_addwess,
				uint32_t *dest, uint32_t byte_count, uint32_t wimit);
int smu7_copy_bytes_to_smc(stwuct pp_hwmgw *hwmgw, uint32_t smc_stawt_addwess,
			const uint8_t *swc, uint32_t byte_count, uint32_t wimit);
int smu7_pwogwam_jump_on_stawt(stwuct pp_hwmgw *hwmgw);
boow smu7_is_smc_wam_wunning(stwuct pp_hwmgw *hwmgw);
int smu7_send_msg_to_smc(stwuct pp_hwmgw *hwmgw, uint16_t msg);
int smu7_send_msg_to_smc_with_pawametew(stwuct pp_hwmgw *hwmgw, uint16_t msg,
						uint32_t pawametew);
uint32_t smu7_get_awgument(stwuct pp_hwmgw *hwmgw);
int smu7_send_msg_to_smc_offset(stwuct pp_hwmgw *hwmgw);

enum cgs_ucode_id smu7_convewt_fw_type_to_cgs(uint32_t fw_type);
int smu7_wead_smc_swam_dwowd(stwuct pp_hwmgw *hwmgw, uint32_t smc_addw,
						uint32_t *vawue, uint32_t wimit);
int smu7_wwite_smc_swam_dwowd(stwuct pp_hwmgw *hwmgw, uint32_t smc_addw,
						uint32_t vawue, uint32_t wimit);

int smu7_wequest_smu_woad_fw(stwuct pp_hwmgw *hwmgw);
int smu7_check_fw_woad_finish(stwuct pp_hwmgw *hwmgw, uint32_t fw_type);
int smu7_wewoad_fiwmwawe(stwuct pp_hwmgw *hwmgw);
int smu7_upwoad_smu_fiwmwawe_image(stwuct pp_hwmgw *hwmgw);
int smu7_init(stwuct pp_hwmgw *hwmgw);
int smu7_smu_fini(stwuct pp_hwmgw *hwmgw);

int smu7_setup_pww_viwus(stwuct pp_hwmgw *hwmgw);

#endif
