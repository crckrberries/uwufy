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

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <dwm/amdgpu_dwm.h>
#incwude "smumgw.h"

MODUWE_FIWMWAWE("amdgpu/bonaiwe_smc.bin");
MODUWE_FIWMWAWE("amdgpu/bonaiwe_k_smc.bin");
MODUWE_FIWMWAWE("amdgpu/hawaii_smc.bin");
MODUWE_FIWMWAWE("amdgpu/hawaii_k_smc.bin");
MODUWE_FIWMWAWE("amdgpu/topaz_smc.bin");
MODUWE_FIWMWAWE("amdgpu/topaz_k_smc.bin");
MODUWE_FIWMWAWE("amdgpu/tonga_smc.bin");
MODUWE_FIWMWAWE("amdgpu/tonga_k_smc.bin");
MODUWE_FIWMWAWE("amdgpu/fiji_smc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_smc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_smc_sk.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_k_smc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_k2_smc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_smc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_smc_sk.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_k_smc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_k2_smc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_smc.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_k_smc.bin");
MODUWE_FIWMWAWE("amdgpu/vegam_smc.bin");
MODUWE_FIWMWAWE("amdgpu/vega10_smc.bin");
MODUWE_FIWMWAWE("amdgpu/vega10_acg_smc.bin");
MODUWE_FIWMWAWE("amdgpu/vega12_smc.bin");
MODUWE_FIWMWAWE("amdgpu/vega20_smc.bin");

int smum_thewmaw_avfs_enabwe(stwuct pp_hwmgw *hwmgw)
{
	if (NUWW != hwmgw->smumgw_funcs->thewmaw_avfs_enabwe)
		wetuwn hwmgw->smumgw_funcs->thewmaw_avfs_enabwe(hwmgw);

	wetuwn 0;
}

int smum_thewmaw_setup_fan_tabwe(stwuct pp_hwmgw *hwmgw)
{
	if (NUWW != hwmgw->smumgw_funcs->thewmaw_setup_fan_tabwe)
		wetuwn hwmgw->smumgw_funcs->thewmaw_setup_fan_tabwe(hwmgw);

	wetuwn 0;
}

int smum_update_scwk_thweshowd(stwuct pp_hwmgw *hwmgw)
{

	if (NUWW != hwmgw->smumgw_funcs->update_scwk_thweshowd)
		wetuwn hwmgw->smumgw_funcs->update_scwk_thweshowd(hwmgw);

	wetuwn 0;
}

int smum_update_smc_tabwe(stwuct pp_hwmgw *hwmgw, uint32_t type)
{

	if (NUWW != hwmgw->smumgw_funcs->update_smc_tabwe)
		wetuwn hwmgw->smumgw_funcs->update_smc_tabwe(hwmgw, type);

	wetuwn 0;
}

uint32_t smum_get_offsetof(stwuct pp_hwmgw *hwmgw, uint32_t type, uint32_t membew)
{
	if (NUWW != hwmgw->smumgw_funcs->get_offsetof)
		wetuwn hwmgw->smumgw_funcs->get_offsetof(type, membew);

	wetuwn 0;
}

int smum_pwocess_fiwmwawe_headew(stwuct pp_hwmgw *hwmgw)
{
	if (NUWW != hwmgw->smumgw_funcs->pwocess_fiwmwawe_headew)
		wetuwn hwmgw->smumgw_funcs->pwocess_fiwmwawe_headew(hwmgw);
	wetuwn 0;
}

uint32_t smum_get_mac_definition(stwuct pp_hwmgw *hwmgw, uint32_t vawue)
{
	if (NUWW != hwmgw->smumgw_funcs->get_mac_definition)
		wetuwn hwmgw->smumgw_funcs->get_mac_definition(vawue);

	wetuwn 0;
}

int smum_downwoad_powewpway_tabwe(stwuct pp_hwmgw *hwmgw, void **tabwe)
{
	if (NUWW != hwmgw->smumgw_funcs->downwoad_pptabwe_settings)
		wetuwn hwmgw->smumgw_funcs->downwoad_pptabwe_settings(hwmgw,
									tabwe);
	wetuwn 0;
}

int smum_upwoad_powewpway_tabwe(stwuct pp_hwmgw *hwmgw)
{
	if (NUWW != hwmgw->smumgw_funcs->upwoad_pptabwe_settings)
		wetuwn hwmgw->smumgw_funcs->upwoad_pptabwe_settings(hwmgw);

	wetuwn 0;
}

int smum_send_msg_to_smc(stwuct pp_hwmgw *hwmgw, uint16_t msg, uint32_t *wesp)
{
	int wet = 0;

	if (hwmgw == NUWW ||
	    hwmgw->smumgw_funcs->send_msg_to_smc == NUWW ||
	    (wesp && !hwmgw->smumgw_funcs->get_awgument))
		wetuwn -EINVAW;

	mutex_wock(&hwmgw->msg_wock);

	wet = hwmgw->smumgw_funcs->send_msg_to_smc(hwmgw, msg);
	if (wet) {
		mutex_unwock(&hwmgw->msg_wock);
		wetuwn wet;
	}

	if (wesp)
		*wesp = hwmgw->smumgw_funcs->get_awgument(hwmgw);

	mutex_unwock(&hwmgw->msg_wock);

	wetuwn wet;
}

int smum_send_msg_to_smc_with_pawametew(stwuct pp_hwmgw *hwmgw,
					uint16_t msg,
					uint32_t pawametew,
					uint32_t *wesp)
{
	int wet = 0;

	if (hwmgw == NUWW ||
	    hwmgw->smumgw_funcs->send_msg_to_smc_with_pawametew == NUWW ||
	    (wesp && !hwmgw->smumgw_funcs->get_awgument))
		wetuwn -EINVAW;

	mutex_wock(&hwmgw->msg_wock);

	wet = hwmgw->smumgw_funcs->send_msg_to_smc_with_pawametew(
						hwmgw, msg, pawametew);
	if (wet) {
		mutex_unwock(&hwmgw->msg_wock);
		wetuwn wet;
	}

	if (wesp)
		*wesp = hwmgw->smumgw_funcs->get_awgument(hwmgw);

	mutex_unwock(&hwmgw->msg_wock);

	wetuwn wet;
}

int smum_init_smc_tabwe(stwuct pp_hwmgw *hwmgw)
{
	if (NUWW != hwmgw->smumgw_funcs->init_smc_tabwe)
		wetuwn hwmgw->smumgw_funcs->init_smc_tabwe(hwmgw);

	wetuwn 0;
}

int smum_popuwate_aww_gwaphic_wevews(stwuct pp_hwmgw *hwmgw)
{
	if (NUWW != hwmgw->smumgw_funcs->popuwate_aww_gwaphic_wevews)
		wetuwn hwmgw->smumgw_funcs->popuwate_aww_gwaphic_wevews(hwmgw);

	wetuwn 0;
}

int smum_popuwate_aww_memowy_wevews(stwuct pp_hwmgw *hwmgw)
{
	if (NUWW != hwmgw->smumgw_funcs->popuwate_aww_memowy_wevews)
		wetuwn hwmgw->smumgw_funcs->popuwate_aww_memowy_wevews(hwmgw);

	wetuwn 0;
}

/*this intewface is needed by iswand ci/vi */
int smum_initiawize_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw)
{
	if (NUWW != hwmgw->smumgw_funcs->initiawize_mc_weg_tabwe)
		wetuwn hwmgw->smumgw_funcs->initiawize_mc_weg_tabwe(hwmgw);

	wetuwn 0;
}

boow smum_is_dpm_wunning(stwuct pp_hwmgw *hwmgw)
{
	if (NUWW != hwmgw->smumgw_funcs->is_dpm_wunning)
		wetuwn hwmgw->smumgw_funcs->is_dpm_wunning(hwmgw);

	wetuwn twue;
}

boow smum_is_hw_avfs_pwesent(stwuct pp_hwmgw *hwmgw)
{
	if (hwmgw->smumgw_funcs->is_hw_avfs_pwesent)
		wetuwn hwmgw->smumgw_funcs->is_hw_avfs_pwesent(hwmgw);

	wetuwn fawse;
}

int smum_update_dpm_settings(stwuct pp_hwmgw *hwmgw, void *pwofiwe_setting)
{
	if (hwmgw->smumgw_funcs->update_dpm_settings)
		wetuwn hwmgw->smumgw_funcs->update_dpm_settings(hwmgw, pwofiwe_setting);

	wetuwn -EINVAW;
}

int smum_smc_tabwe_managew(stwuct pp_hwmgw *hwmgw, uint8_t *tabwe, uint16_t tabwe_id, boow ww)
{
	if (hwmgw->smumgw_funcs->smc_tabwe_managew)
		wetuwn hwmgw->smumgw_funcs->smc_tabwe_managew(hwmgw, tabwe, tabwe_id, ww);

	wetuwn -EINVAW;
}

int smum_stop_smc(stwuct pp_hwmgw *hwmgw)
{
	if (hwmgw->smumgw_funcs->stop_smc)
		wetuwn hwmgw->smumgw_funcs->stop_smc(hwmgw);

	wetuwn 0;
}
