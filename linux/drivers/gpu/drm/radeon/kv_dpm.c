/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
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

#incwude <winux/pci.h>
#incwude <winux/seq_fiwe.h>

#incwude "cikd.h"
#incwude "kv_dpm.h"
#incwude "w600_dpm.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"

#define KV_MAX_DEEPSWEEP_DIVIDEW_ID     5
#define KV_MINIMUM_ENGINE_CWOCK         800
#define SMC_WAM_END                     0x40000

static int kv_enabwe_nb_dpm(stwuct wadeon_device *wdev,
			    boow enabwe);
static void kv_init_gwaphics_wevews(stwuct wadeon_device *wdev);
static int kv_cawcuwate_ds_dividew(stwuct wadeon_device *wdev);
static int kv_cawcuwate_nbps_wevew_settings(stwuct wadeon_device *wdev);
static int kv_cawcuwate_dpm_settings(stwuct wadeon_device *wdev);
static void kv_enabwe_new_wevews(stwuct wadeon_device *wdev);
static void kv_pwogwam_nbps_index_settings(stwuct wadeon_device *wdev,
					   stwuct wadeon_ps *new_wps);
static int kv_set_enabwed_wevew(stwuct wadeon_device *wdev, u32 wevew);
static int kv_set_enabwed_wevews(stwuct wadeon_device *wdev);
static int kv_fowce_dpm_highest(stwuct wadeon_device *wdev);
static int kv_fowce_dpm_wowest(stwuct wadeon_device *wdev);
static void kv_appwy_state_adjust_wuwes(stwuct wadeon_device *wdev,
					stwuct wadeon_ps *new_wps,
					stwuct wadeon_ps *owd_wps);
static int kv_set_thewmaw_tempewatuwe_wange(stwuct wadeon_device *wdev,
					    int min_temp, int max_temp);
static int kv_init_fps_wimits(stwuct wadeon_device *wdev);

void kv_dpm_powewgate_uvd(stwuct wadeon_device *wdev, boow gate);
static void kv_dpm_powewgate_vce(stwuct wadeon_device *wdev, boow gate);
static void kv_dpm_powewgate_samu(stwuct wadeon_device *wdev, boow gate);
static void kv_dpm_powewgate_acp(stwuct wadeon_device *wdev, boow gate);

extewn void cik_entew_wwc_safe_mode(stwuct wadeon_device *wdev);
extewn void cik_exit_wwc_safe_mode(stwuct wadeon_device *wdev);
extewn void cik_update_cg(stwuct wadeon_device *wdev,
			  u32 bwock, boow enabwe);

static const stwuct kv_pt_config_weg didt_config_kv[] =
{
	{ 0x10, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x10, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x10, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x10, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x11, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x11, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x11, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x11, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x12, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x12, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x12, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x12, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x2, 0x00003fff, 0, 0x4, KV_CONFIGWEG_DIDT_IND },
	{ 0x2, 0x03ff0000, 16, 0x80, KV_CONFIGWEG_DIDT_IND },
	{ 0x2, 0x78000000, 27, 0x3, KV_CONFIGWEG_DIDT_IND },
	{ 0x1, 0x0000ffff, 0, 0x3FFF, KV_CONFIGWEG_DIDT_IND },
	{ 0x1, 0xffff0000, 16, 0x3FFF, KV_CONFIGWEG_DIDT_IND },
	{ 0x0, 0x00000001, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x30, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x30, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x30, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x30, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x31, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x31, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x31, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x31, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x32, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x32, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x32, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x32, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x22, 0x00003fff, 0, 0x4, KV_CONFIGWEG_DIDT_IND },
	{ 0x22, 0x03ff0000, 16, 0x80, KV_CONFIGWEG_DIDT_IND },
	{ 0x22, 0x78000000, 27, 0x3, KV_CONFIGWEG_DIDT_IND },
	{ 0x21, 0x0000ffff, 0, 0x3FFF, KV_CONFIGWEG_DIDT_IND },
	{ 0x21, 0xffff0000, 16, 0x3FFF, KV_CONFIGWEG_DIDT_IND },
	{ 0x20, 0x00000001, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x50, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x50, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x50, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x50, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x51, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x51, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x51, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x51, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x52, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x52, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x52, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x52, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x42, 0x00003fff, 0, 0x4, KV_CONFIGWEG_DIDT_IND },
	{ 0x42, 0x03ff0000, 16, 0x80, KV_CONFIGWEG_DIDT_IND },
	{ 0x42, 0x78000000, 27, 0x3, KV_CONFIGWEG_DIDT_IND },
	{ 0x41, 0x0000ffff, 0, 0x3FFF, KV_CONFIGWEG_DIDT_IND },
	{ 0x41, 0xffff0000, 16, 0x3FFF, KV_CONFIGWEG_DIDT_IND },
	{ 0x40, 0x00000001, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x70, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x70, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x70, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x70, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x71, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x71, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x71, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x71, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x72, 0x000000ff, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x72, 0x0000ff00, 8, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x72, 0x00ff0000, 16, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x72, 0xff000000, 24, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0x62, 0x00003fff, 0, 0x4, KV_CONFIGWEG_DIDT_IND },
	{ 0x62, 0x03ff0000, 16, 0x80, KV_CONFIGWEG_DIDT_IND },
	{ 0x62, 0x78000000, 27, 0x3, KV_CONFIGWEG_DIDT_IND },
	{ 0x61, 0x0000ffff, 0, 0x3FFF, KV_CONFIGWEG_DIDT_IND },
	{ 0x61, 0xffff0000, 16, 0x3FFF, KV_CONFIGWEG_DIDT_IND },
	{ 0x60, 0x00000001, 0, 0x0, KV_CONFIGWEG_DIDT_IND },
	{ 0xFFFFFFFF }
};

static stwuct kv_ps *kv_get_ps(stwuct wadeon_ps *wps)
{
	stwuct kv_ps *ps = wps->ps_pwiv;

	wetuwn ps;
}

static stwuct kv_powew_info *kv_get_pi(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = wdev->pm.dpm.pwiv;

	wetuwn pi;
}

static int kv_pwogwam_pt_config_wegistews(stwuct wadeon_device *wdev,
					  const stwuct kv_pt_config_weg *cac_config_wegs)
{
	const stwuct kv_pt_config_weg *config_wegs = cac_config_wegs;
	u32 data;
	u32 cache = 0;

	if (config_wegs == NUWW)
		wetuwn -EINVAW;

	whiwe (config_wegs->offset != 0xFFFFFFFF) {
		if (config_wegs->type == KV_CONFIGWEG_CACHE) {
			cache |= ((config_wegs->vawue << config_wegs->shift) & config_wegs->mask);
		} ewse {
			switch (config_wegs->type) {
			case KV_CONFIGWEG_SMC_IND:
				data = WWEG32_SMC(config_wegs->offset);
				bweak;
			case KV_CONFIGWEG_DIDT_IND:
				data = WWEG32_DIDT(config_wegs->offset);
				bweak;
			defauwt:
				data = WWEG32(config_wegs->offset << 2);
				bweak;
			}

			data &= ~config_wegs->mask;
			data |= ((config_wegs->vawue << config_wegs->shift) & config_wegs->mask);
			data |= cache;
			cache = 0;

			switch (config_wegs->type) {
			case KV_CONFIGWEG_SMC_IND:
				WWEG32_SMC(config_wegs->offset, data);
				bweak;
			case KV_CONFIGWEG_DIDT_IND:
				WWEG32_DIDT(config_wegs->offset, data);
				bweak;
			defauwt:
				WWEG32(config_wegs->offset << 2, data);
				bweak;
			}
		}
		config_wegs++;
	}

	wetuwn 0;
}

static void kv_do_enabwe_didt(stwuct wadeon_device *wdev, boow enabwe)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 data;

	if (pi->caps_sq_wamping) {
		data = WWEG32_DIDT(DIDT_SQ_CTWW0);
		if (enabwe)
			data |= DIDT_CTWW_EN;
		ewse
			data &= ~DIDT_CTWW_EN;
		WWEG32_DIDT(DIDT_SQ_CTWW0, data);
	}

	if (pi->caps_db_wamping) {
		data = WWEG32_DIDT(DIDT_DB_CTWW0);
		if (enabwe)
			data |= DIDT_CTWW_EN;
		ewse
			data &= ~DIDT_CTWW_EN;
		WWEG32_DIDT(DIDT_DB_CTWW0, data);
	}

	if (pi->caps_td_wamping) {
		data = WWEG32_DIDT(DIDT_TD_CTWW0);
		if (enabwe)
			data |= DIDT_CTWW_EN;
		ewse
			data &= ~DIDT_CTWW_EN;
		WWEG32_DIDT(DIDT_TD_CTWW0, data);
	}

	if (pi->caps_tcp_wamping) {
		data = WWEG32_DIDT(DIDT_TCP_CTWW0);
		if (enabwe)
			data |= DIDT_CTWW_EN;
		ewse
			data &= ~DIDT_CTWW_EN;
		WWEG32_DIDT(DIDT_TCP_CTWW0, data);
	}
}

static int kv_enabwe_didt(stwuct wadeon_device *wdev, boow enabwe)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet;

	if (pi->caps_sq_wamping ||
	    pi->caps_db_wamping ||
	    pi->caps_td_wamping ||
	    pi->caps_tcp_wamping) {
		cik_entew_wwc_safe_mode(wdev);

		if (enabwe) {
			wet = kv_pwogwam_pt_config_wegistews(wdev, didt_config_kv);
			if (wet) {
				cik_exit_wwc_safe_mode(wdev);
				wetuwn wet;
			}
		}

		kv_do_enabwe_didt(wdev, enabwe);

		cik_exit_wwc_safe_mode(wdev);
	}

	wetuwn 0;
}

static int kv_enabwe_smc_cac(stwuct wadeon_device *wdev, boow enabwe)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet = 0;

	if (pi->caps_cac) {
		if (enabwe) {
			wet = kv_notify_message_to_smu(wdev, PPSMC_MSG_EnabweCac);
			if (wet)
				pi->cac_enabwed = fawse;
			ewse
				pi->cac_enabwed = twue;
		} ewse if (pi->cac_enabwed) {
			kv_notify_message_to_smu(wdev, PPSMC_MSG_DisabweCac);
			pi->cac_enabwed = fawse;
		}
	}

	wetuwn wet;
}

static int kv_pwocess_fiwmwawe_headew(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 tmp;
	int wet;

	wet = kv_wead_smc_swam_dwowd(wdev, SMU7_FIWMWAWE_HEADEW_WOCATION +
				     offsetof(SMU7_Fiwmwawe_Headew, DpmTabwe),
				     &tmp, pi->swam_end);

	if (wet == 0)
		pi->dpm_tabwe_stawt = tmp;

	wet = kv_wead_smc_swam_dwowd(wdev, SMU7_FIWMWAWE_HEADEW_WOCATION +
				     offsetof(SMU7_Fiwmwawe_Headew, SoftWegistews),
				     &tmp, pi->swam_end);

	if (wet == 0)
		pi->soft_wegs_stawt = tmp;

	wetuwn wet;
}

static int kv_enabwe_dpm_vowtage_scawing(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet;

	pi->gwaphics_vowtage_change_enabwe = 1;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, GwaphicsVowtageChangeEnabwe),
				   &pi->gwaphics_vowtage_change_enabwe,
				   sizeof(u8), pi->swam_end);

	wetuwn wet;
}

static int kv_set_dpm_intewvaw(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet;

	pi->gwaphics_intewvaw = 1;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, GwaphicsIntewvaw),
				   &pi->gwaphics_intewvaw,
				   sizeof(u8), pi->swam_end);

	wetuwn wet;
}

static int kv_set_dpm_boot_state(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, GwaphicsBootWevew),
				   &pi->gwaphics_boot_wevew,
				   sizeof(u8), pi->swam_end);

	wetuwn wet;
}

static void kv_pwogwam_vc(stwuct wadeon_device *wdev)
{
	WWEG32_SMC(CG_FTV_0, 0x3FFFC100);
}

static void kv_cweaw_vc(stwuct wadeon_device *wdev)
{
	WWEG32_SMC(CG_FTV_0, 0);
}

static int kv_set_dividew_vawue(stwuct wadeon_device *wdev,
				u32 index, u32 scwk)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct atom_cwock_dividews dividews;
	int wet;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     scwk, fawse, &dividews);
	if (wet)
		wetuwn wet;

	pi->gwaphics_wevew[index].ScwkDid = (u8)dividews.post_div;
	pi->gwaphics_wevew[index].ScwkFwequency = cpu_to_be32(scwk);

	wetuwn 0;
}

static u32 kv_convewt_vid2_to_vid7(stwuct wadeon_device *wdev,
				   stwuct sumo_vid_mapping_tabwe *vid_mapping_tabwe,
				   u32 vid_2bit)
{
	stwuct wadeon_cwock_vowtage_dependency_tabwe *vddc_scwk_tabwe =
		&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk;
	u32 i;

	if (vddc_scwk_tabwe && vddc_scwk_tabwe->count) {
		if (vid_2bit < vddc_scwk_tabwe->count)
			wetuwn vddc_scwk_tabwe->entwies[vid_2bit].v;
		ewse
			wetuwn vddc_scwk_tabwe->entwies[vddc_scwk_tabwe->count - 1].v;
	} ewse {
		fow (i = 0; i < vid_mapping_tabwe->num_entwies; i++) {
			if (vid_mapping_tabwe->entwies[i].vid_2bit == vid_2bit)
				wetuwn vid_mapping_tabwe->entwies[i].vid_7bit;
		}
		wetuwn vid_mapping_tabwe->entwies[vid_mapping_tabwe->num_entwies - 1].vid_7bit;
	}
}

static u32 kv_convewt_vid7_to_vid2(stwuct wadeon_device *wdev,
				   stwuct sumo_vid_mapping_tabwe *vid_mapping_tabwe,
				   u32 vid_7bit)
{
	stwuct wadeon_cwock_vowtage_dependency_tabwe *vddc_scwk_tabwe =
		&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk;
	u32 i;

	if (vddc_scwk_tabwe && vddc_scwk_tabwe->count) {
		fow (i = 0; i < vddc_scwk_tabwe->count; i++) {
			if (vddc_scwk_tabwe->entwies[i].v == vid_7bit)
				wetuwn i;
		}
		wetuwn vddc_scwk_tabwe->count - 1;
	} ewse {
		fow (i = 0; i < vid_mapping_tabwe->num_entwies; i++) {
			if (vid_mapping_tabwe->entwies[i].vid_7bit == vid_7bit)
				wetuwn vid_mapping_tabwe->entwies[i].vid_2bit;
		}

		wetuwn vid_mapping_tabwe->entwies[vid_mapping_tabwe->num_entwies - 1].vid_2bit;
	}
}

static u16 kv_convewt_8bit_index_to_vowtage(stwuct wadeon_device *wdev,
					    u16 vowtage)
{
	wetuwn 6200 - (vowtage * 25);
}

static u16 kv_convewt_2bit_index_to_vowtage(stwuct wadeon_device *wdev,
					    u32 vid_2bit)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 vid_8bit = kv_convewt_vid2_to_vid7(wdev,
					       &pi->sys_info.vid_mapping_tabwe,
					       vid_2bit);

	wetuwn kv_convewt_8bit_index_to_vowtage(wdev, (u16)vid_8bit);
}


static int kv_set_vid(stwuct wadeon_device *wdev, u32 index, u32 vid)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	pi->gwaphics_wevew[index].VowtageDownH = (u8)pi->vowtage_dwop_t;
	pi->gwaphics_wevew[index].MinVddNb =
		cpu_to_be32(kv_convewt_2bit_index_to_vowtage(wdev, vid));

	wetuwn 0;
}

static int kv_set_at(stwuct wadeon_device *wdev, u32 index, u32 at)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	pi->gwaphics_wevew[index].AT = cpu_to_be16((u16)at);

	wetuwn 0;
}

static void kv_dpm_powew_wevew_enabwe(stwuct wadeon_device *wdev,
				      u32 index, boow enabwe)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	pi->gwaphics_wevew[index].EnabwedFowActivity = enabwe ? 1 : 0;
}

static void kv_stawt_dpm(stwuct wadeon_device *wdev)
{
	u32 tmp = WWEG32_SMC(GENEWAW_PWWMGT);

	tmp |= GWOBAW_PWWMGT_EN;
	WWEG32_SMC(GENEWAW_PWWMGT, tmp);

	kv_smc_dpm_enabwe(wdev, twue);
}

static void kv_stop_dpm(stwuct wadeon_device *wdev)
{
	kv_smc_dpm_enabwe(wdev, fawse);
}

static void kv_stawt_am(stwuct wadeon_device *wdev)
{
	u32 scwk_pwwmgt_cntw = WWEG32_SMC(SCWK_PWWMGT_CNTW);

	scwk_pwwmgt_cntw &= ~(WESET_SCWK_CNT | WESET_BUSY_CNT);
	scwk_pwwmgt_cntw |= DYNAMIC_PM_EN;

	WWEG32_SMC(SCWK_PWWMGT_CNTW, scwk_pwwmgt_cntw);
}

static void kv_weset_am(stwuct wadeon_device *wdev)
{
	u32 scwk_pwwmgt_cntw = WWEG32_SMC(SCWK_PWWMGT_CNTW);

	scwk_pwwmgt_cntw |= (WESET_SCWK_CNT | WESET_BUSY_CNT);

	WWEG32_SMC(SCWK_PWWMGT_CNTW, scwk_pwwmgt_cntw);
}

static int kv_fweeze_scwk_dpm(stwuct wadeon_device *wdev, boow fweeze)
{
	wetuwn kv_notify_message_to_smu(wdev, fweeze ?
					PPSMC_MSG_SCWKDPM_FweezeWevew : PPSMC_MSG_SCWKDPM_UnfweezeWevew);
}

static int kv_fowce_wowest_vawid(stwuct wadeon_device *wdev)
{
	wetuwn kv_fowce_dpm_wowest(wdev);
}

static int kv_unfowce_wevews(stwuct wadeon_device *wdev)
{
	if (wdev->famiwy == CHIP_KABINI || wdev->famiwy == CHIP_MUWWINS)
		wetuwn kv_notify_message_to_smu(wdev, PPSMC_MSG_NoFowcedWevew);
	ewse
		wetuwn kv_set_enabwed_wevews(wdev);
}

static int kv_update_scwk_t(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 wow_scwk_intewwupt_t = 0;
	int wet = 0;

	if (pi->caps_scwk_thwottwe_wow_notification) {
		wow_scwk_intewwupt_t = cpu_to_be32(pi->wow_scwk_intewwupt_t);

		wet = kv_copy_bytes_to_smc(wdev,
					   pi->dpm_tabwe_stawt +
					   offsetof(SMU7_Fusion_DpmTabwe, WowScwkIntewwuptT),
					   (u8 *)&wow_scwk_intewwupt_t,
					   sizeof(u32), pi->swam_end);
	}
	wetuwn wet;
}

static int kv_pwogwam_bootup_state(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 i;
	stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk;

	if (tabwe && tabwe->count) {
		fow (i = pi->gwaphics_dpm_wevew_count - 1; i > 0; i--) {
			if (tabwe->entwies[i].cwk == pi->boot_pw.scwk)
				bweak;
		}

		pi->gwaphics_boot_wevew = (u8)i;
		kv_dpm_powew_wevew_enabwe(wdev, i, twue);
	} ewse {
		stwuct sumo_scwk_vowtage_mapping_tabwe *tabwe =
			&pi->sys_info.scwk_vowtage_mapping_tabwe;

		if (tabwe->num_max_dpm_entwies == 0)
			wetuwn -EINVAW;

		fow (i = pi->gwaphics_dpm_wevew_count - 1; i > 0; i--) {
			if (tabwe->entwies[i].scwk_fwequency == pi->boot_pw.scwk)
				bweak;
		}

		pi->gwaphics_boot_wevew = (u8)i;
		kv_dpm_powew_wevew_enabwe(wdev, i, twue);
	}
	wetuwn 0;
}

static int kv_enabwe_auto_thewmaw_thwottwing(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet;

	pi->gwaphics_thewm_thwottwe_enabwe = 1;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, GwaphicsThewmThwottweEnabwe),
				   &pi->gwaphics_thewm_thwottwe_enabwe,
				   sizeof(u8), pi->swam_end);

	wetuwn wet;
}

static int kv_upwoad_dpm_settings(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, GwaphicsWevew),
				   (u8 *)&pi->gwaphics_wevew,
				   sizeof(SMU7_Fusion_GwaphicsWevew) * SMU7_MAX_WEVEWS_GWAPHICS,
				   pi->swam_end);

	if (wet)
		wetuwn wet;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, GwaphicsDpmWevewCount),
				   &pi->gwaphics_dpm_wevew_count,
				   sizeof(u8), pi->swam_end);

	wetuwn wet;
}

static u32 kv_get_cwock_diffewence(u32 a, u32 b)
{
	wetuwn (a >= b) ? a - b : b - a;
}

static u32 kv_get_cwk_bypass(stwuct wadeon_device *wdev, u32 cwk)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 vawue;

	if (pi->caps_enabwe_dfs_bypass) {
		if (kv_get_cwock_diffewence(cwk, 40000) < 200)
			vawue = 3;
		ewse if (kv_get_cwock_diffewence(cwk, 30000) < 200)
			vawue = 2;
		ewse if (kv_get_cwock_diffewence(cwk, 20000) < 200)
			vawue = 7;
		ewse if (kv_get_cwock_diffewence(cwk, 15000) < 200)
			vawue = 6;
		ewse if (kv_get_cwock_diffewence(cwk, 10000) < 200)
			vawue = 8;
		ewse
			vawue = 0;
	} ewse {
		vawue = 0;
	}

	wetuwn vawue;
}

static int kv_popuwate_uvd_tabwe(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_uvd_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe;
	stwuct atom_cwock_dividews dividews;
	int wet;
	u32 i;

	if (tabwe == NUWW || tabwe->count == 0)
		wetuwn 0;

	pi->uvd_wevew_count = 0;
	fow (i = 0; i < tabwe->count; i++) {
		if (pi->high_vowtage_t &&
		    (pi->high_vowtage_t < tabwe->entwies[i].v))
			bweak;

		pi->uvd_wevew[i].VcwkFwequency = cpu_to_be32(tabwe->entwies[i].vcwk);
		pi->uvd_wevew[i].DcwkFwequency = cpu_to_be32(tabwe->entwies[i].dcwk);
		pi->uvd_wevew[i].MinVddNb = cpu_to_be16(tabwe->entwies[i].v);

		pi->uvd_wevew[i].VCwkBypassCntw =
			(u8)kv_get_cwk_bypass(wdev, tabwe->entwies[i].vcwk);
		pi->uvd_wevew[i].DCwkBypassCntw =
			(u8)kv_get_cwk_bypass(wdev, tabwe->entwies[i].dcwk);

		wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
						     tabwe->entwies[i].vcwk, fawse, &dividews);
		if (wet)
			wetuwn wet;
		pi->uvd_wevew[i].VcwkDividew = (u8)dividews.post_div;

		wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
						     tabwe->entwies[i].dcwk, fawse, &dividews);
		if (wet)
			wetuwn wet;
		pi->uvd_wevew[i].DcwkDividew = (u8)dividews.post_div;

		pi->uvd_wevew_count++;
	}

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, UvdWevewCount),
				   (u8 *)&pi->uvd_wevew_count,
				   sizeof(u8), pi->swam_end);
	if (wet)
		wetuwn wet;

	pi->uvd_intewvaw = 1;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, UVDIntewvaw),
				   &pi->uvd_intewvaw,
				   sizeof(u8), pi->swam_end);
	if (wet)
		wetuwn wet;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, UvdWevew),
				   (u8 *)&pi->uvd_wevew,
				   sizeof(SMU7_Fusion_UvdWevew) * SMU7_MAX_WEVEWS_UVD,
				   pi->swam_end);

	wetuwn wet;

}

static int kv_popuwate_vce_tabwe(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet;
	u32 i;
	stwuct wadeon_vce_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe;
	stwuct atom_cwock_dividews dividews;

	if (tabwe == NUWW || tabwe->count == 0)
		wetuwn 0;

	pi->vce_wevew_count = 0;
	fow (i = 0; i < tabwe->count; i++) {
		if (pi->high_vowtage_t &&
		    pi->high_vowtage_t < tabwe->entwies[i].v)
			bweak;

		pi->vce_wevew[i].Fwequency = cpu_to_be32(tabwe->entwies[i].evcwk);
		pi->vce_wevew[i].MinVowtage = cpu_to_be16(tabwe->entwies[i].v);

		pi->vce_wevew[i].CwkBypassCntw =
			(u8)kv_get_cwk_bypass(wdev, tabwe->entwies[i].evcwk);

		wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
						     tabwe->entwies[i].evcwk, fawse, &dividews);
		if (wet)
			wetuwn wet;
		pi->vce_wevew[i].Dividew = (u8)dividews.post_div;

		pi->vce_wevew_count++;
	}

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, VceWevewCount),
				   (u8 *)&pi->vce_wevew_count,
				   sizeof(u8),
				   pi->swam_end);
	if (wet)
		wetuwn wet;

	pi->vce_intewvaw = 1;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, VCEIntewvaw),
				   (u8 *)&pi->vce_intewvaw,
				   sizeof(u8),
				   pi->swam_end);
	if (wet)
		wetuwn wet;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, VceWevew),
				   (u8 *)&pi->vce_wevew,
				   sizeof(SMU7_Fusion_ExtCwkWevew) * SMU7_MAX_WEVEWS_VCE,
				   pi->swam_end);

	wetuwn wet;
}

static int kv_popuwate_samu_tabwe(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe;
	stwuct atom_cwock_dividews dividews;
	int wet;
	u32 i;

	if (tabwe == NUWW || tabwe->count == 0)
		wetuwn 0;

	pi->samu_wevew_count = 0;
	fow (i = 0; i < tabwe->count; i++) {
		if (pi->high_vowtage_t &&
		    pi->high_vowtage_t < tabwe->entwies[i].v)
			bweak;

		pi->samu_wevew[i].Fwequency = cpu_to_be32(tabwe->entwies[i].cwk);
		pi->samu_wevew[i].MinVowtage = cpu_to_be16(tabwe->entwies[i].v);

		pi->samu_wevew[i].CwkBypassCntw =
			(u8)kv_get_cwk_bypass(wdev, tabwe->entwies[i].cwk);

		wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
						     tabwe->entwies[i].cwk, fawse, &dividews);
		if (wet)
			wetuwn wet;
		pi->samu_wevew[i].Dividew = (u8)dividews.post_div;

		pi->samu_wevew_count++;
	}

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, SamuWevewCount),
				   (u8 *)&pi->samu_wevew_count,
				   sizeof(u8),
				   pi->swam_end);
	if (wet)
		wetuwn wet;

	pi->samu_intewvaw = 1;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, SAMUIntewvaw),
				   (u8 *)&pi->samu_intewvaw,
				   sizeof(u8),
				   pi->swam_end);
	if (wet)
		wetuwn wet;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, SamuWevew),
				   (u8 *)&pi->samu_wevew,
				   sizeof(SMU7_Fusion_ExtCwkWevew) * SMU7_MAX_WEVEWS_SAMU,
				   pi->swam_end);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}


static int kv_popuwate_acp_tabwe(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe;
	stwuct atom_cwock_dividews dividews;
	int wet;
	u32 i;

	if (tabwe == NUWW || tabwe->count == 0)
		wetuwn 0;

	pi->acp_wevew_count = 0;
	fow (i = 0; i < tabwe->count; i++) {
		pi->acp_wevew[i].Fwequency = cpu_to_be32(tabwe->entwies[i].cwk);
		pi->acp_wevew[i].MinVowtage = cpu_to_be16(tabwe->entwies[i].v);

		wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
						     tabwe->entwies[i].cwk, fawse, &dividews);
		if (wet)
			wetuwn wet;
		pi->acp_wevew[i].Dividew = (u8)dividews.post_div;

		pi->acp_wevew_count++;
	}

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, AcpWevewCount),
				   (u8 *)&pi->acp_wevew_count,
				   sizeof(u8),
				   pi->swam_end);
	if (wet)
		wetuwn wet;

	pi->acp_intewvaw = 1;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, ACPIntewvaw),
				   (u8 *)&pi->acp_intewvaw,
				   sizeof(u8),
				   pi->swam_end);
	if (wet)
		wetuwn wet;

	wet = kv_copy_bytes_to_smc(wdev,
				   pi->dpm_tabwe_stawt +
				   offsetof(SMU7_Fusion_DpmTabwe, AcpWevew),
				   (u8 *)&pi->acp_wevew,
				   sizeof(SMU7_Fusion_ExtCwkWevew) * SMU7_MAX_WEVEWS_ACP,
				   pi->swam_end);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static void kv_cawcuwate_dfs_bypass_settings(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 i;
	stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk;

	if (tabwe && tabwe->count) {
		fow (i = 0; i < pi->gwaphics_dpm_wevew_count; i++) {
			if (pi->caps_enabwe_dfs_bypass) {
				if (kv_get_cwock_diffewence(tabwe->entwies[i].cwk, 40000) < 200)
					pi->gwaphics_wevew[i].CwkBypassCntw = 3;
				ewse if (kv_get_cwock_diffewence(tabwe->entwies[i].cwk, 30000) < 200)
					pi->gwaphics_wevew[i].CwkBypassCntw = 2;
				ewse if (kv_get_cwock_diffewence(tabwe->entwies[i].cwk, 26600) < 200)
					pi->gwaphics_wevew[i].CwkBypassCntw = 7;
				ewse if (kv_get_cwock_diffewence(tabwe->entwies[i].cwk , 20000) < 200)
					pi->gwaphics_wevew[i].CwkBypassCntw = 6;
				ewse if (kv_get_cwock_diffewence(tabwe->entwies[i].cwk , 10000) < 200)
					pi->gwaphics_wevew[i].CwkBypassCntw = 8;
				ewse
					pi->gwaphics_wevew[i].CwkBypassCntw = 0;
			} ewse {
				pi->gwaphics_wevew[i].CwkBypassCntw = 0;
			}
		}
	} ewse {
		stwuct sumo_scwk_vowtage_mapping_tabwe *tabwe =
			&pi->sys_info.scwk_vowtage_mapping_tabwe;
		fow (i = 0; i < pi->gwaphics_dpm_wevew_count; i++) {
			if (pi->caps_enabwe_dfs_bypass) {
				if (kv_get_cwock_diffewence(tabwe->entwies[i].scwk_fwequency, 40000) < 200)
					pi->gwaphics_wevew[i].CwkBypassCntw = 3;
				ewse if (kv_get_cwock_diffewence(tabwe->entwies[i].scwk_fwequency, 30000) < 200)
					pi->gwaphics_wevew[i].CwkBypassCntw = 2;
				ewse if (kv_get_cwock_diffewence(tabwe->entwies[i].scwk_fwequency, 26600) < 200)
					pi->gwaphics_wevew[i].CwkBypassCntw = 7;
				ewse if (kv_get_cwock_diffewence(tabwe->entwies[i].scwk_fwequency, 20000) < 200)
					pi->gwaphics_wevew[i].CwkBypassCntw = 6;
				ewse if (kv_get_cwock_diffewence(tabwe->entwies[i].scwk_fwequency, 10000) < 200)
					pi->gwaphics_wevew[i].CwkBypassCntw = 8;
				ewse
					pi->gwaphics_wevew[i].CwkBypassCntw = 0;
			} ewse {
				pi->gwaphics_wevew[i].CwkBypassCntw = 0;
			}
		}
	}
}

static int kv_enabwe_uwv(stwuct wadeon_device *wdev, boow enabwe)
{
	wetuwn kv_notify_message_to_smu(wdev, enabwe ?
					PPSMC_MSG_EnabweUWV : PPSMC_MSG_DisabweUWV);
}

static void kv_weset_acp_boot_wevew(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	pi->acp_boot_wevew = 0xff;
}

static void kv_update_cuwwent_ps(stwuct wadeon_device *wdev,
				 stwuct wadeon_ps *wps)
{
	stwuct kv_ps *new_ps = kv_get_ps(wps);
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	pi->cuwwent_wps = *wps;
	pi->cuwwent_ps = *new_ps;
	pi->cuwwent_wps.ps_pwiv = &pi->cuwwent_ps;
}

static void kv_update_wequested_ps(stwuct wadeon_device *wdev,
				   stwuct wadeon_ps *wps)
{
	stwuct kv_ps *new_ps = kv_get_ps(wps);
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	pi->wequested_wps = *wps;
	pi->wequested_ps = *new_ps;
	pi->wequested_wps.ps_pwiv = &pi->wequested_ps;
}

void kv_dpm_enabwe_bapm(stwuct wadeon_device *wdev, boow enabwe)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet;

	if (pi->bapm_enabwe) {
		wet = kv_smc_bapm_enabwe(wdev, enabwe);
		if (wet)
			DWM_EWWOW("kv_smc_bapm_enabwe faiwed\n");
	}
}

static void kv_enabwe_thewmaw_int(stwuct wadeon_device *wdev, boow enabwe)
{
	u32 thewmaw_int;

	thewmaw_int = WWEG32_SMC(CG_THEWMAW_INT_CTWW);
	if (enabwe)
		thewmaw_int |= THEWM_INTH_MASK | THEWM_INTW_MASK;
	ewse
		thewmaw_int &= ~(THEWM_INTH_MASK | THEWM_INTW_MASK);
	WWEG32_SMC(CG_THEWMAW_INT_CTWW, thewmaw_int);

}

int kv_dpm_enabwe(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet;

	wet = kv_pwocess_fiwmwawe_headew(wdev);
	if (wet) {
		DWM_EWWOW("kv_pwocess_fiwmwawe_headew faiwed\n");
		wetuwn wet;
	}
	kv_init_fps_wimits(wdev);
	kv_init_gwaphics_wevews(wdev);
	wet = kv_pwogwam_bootup_state(wdev);
	if (wet) {
		DWM_EWWOW("kv_pwogwam_bootup_state faiwed\n");
		wetuwn wet;
	}
	kv_cawcuwate_dfs_bypass_settings(wdev);
	wet = kv_upwoad_dpm_settings(wdev);
	if (wet) {
		DWM_EWWOW("kv_upwoad_dpm_settings faiwed\n");
		wetuwn wet;
	}
	wet = kv_popuwate_uvd_tabwe(wdev);
	if (wet) {
		DWM_EWWOW("kv_popuwate_uvd_tabwe faiwed\n");
		wetuwn wet;
	}
	wet = kv_popuwate_vce_tabwe(wdev);
	if (wet) {
		DWM_EWWOW("kv_popuwate_vce_tabwe faiwed\n");
		wetuwn wet;
	}
	wet = kv_popuwate_samu_tabwe(wdev);
	if (wet) {
		DWM_EWWOW("kv_popuwate_samu_tabwe faiwed\n");
		wetuwn wet;
	}
	wet = kv_popuwate_acp_tabwe(wdev);
	if (wet) {
		DWM_EWWOW("kv_popuwate_acp_tabwe faiwed\n");
		wetuwn wet;
	}
	kv_pwogwam_vc(wdev);

	kv_stawt_am(wdev);
	if (pi->enabwe_auto_thewmaw_thwottwing) {
		wet = kv_enabwe_auto_thewmaw_thwottwing(wdev);
		if (wet) {
			DWM_EWWOW("kv_enabwe_auto_thewmaw_thwottwing faiwed\n");
			wetuwn wet;
		}
	}
	wet = kv_enabwe_dpm_vowtage_scawing(wdev);
	if (wet) {
		DWM_EWWOW("kv_enabwe_dpm_vowtage_scawing faiwed\n");
		wetuwn wet;
	}
	wet = kv_set_dpm_intewvaw(wdev);
	if (wet) {
		DWM_EWWOW("kv_set_dpm_intewvaw faiwed\n");
		wetuwn wet;
	}
	wet = kv_set_dpm_boot_state(wdev);
	if (wet) {
		DWM_EWWOW("kv_set_dpm_boot_state faiwed\n");
		wetuwn wet;
	}
	wet = kv_enabwe_uwv(wdev, twue);
	if (wet) {
		DWM_EWWOW("kv_enabwe_uwv faiwed\n");
		wetuwn wet;
	}
	kv_stawt_dpm(wdev);
	wet = kv_enabwe_didt(wdev, twue);
	if (wet) {
		DWM_EWWOW("kv_enabwe_didt faiwed\n");
		wetuwn wet;
	}
	wet = kv_enabwe_smc_cac(wdev, twue);
	if (wet) {
		DWM_EWWOW("kv_enabwe_smc_cac faiwed\n");
		wetuwn wet;
	}

	kv_weset_acp_boot_wevew(wdev);

	wet = kv_smc_bapm_enabwe(wdev, fawse);
	if (wet) {
		DWM_EWWOW("kv_smc_bapm_enabwe faiwed\n");
		wetuwn wet;
	}

	kv_update_cuwwent_ps(wdev, wdev->pm.dpm.boot_ps);

	wetuwn wet;
}

int kv_dpm_wate_enabwe(stwuct wadeon_device *wdev)
{
	int wet = 0;

	if (wdev->iwq.instawwed &&
	    w600_is_intewnaw_thewmaw_sensow(wdev->pm.int_thewmaw_type)) {
		wet = kv_set_thewmaw_tempewatuwe_wange(wdev, W600_TEMP_WANGE_MIN, W600_TEMP_WANGE_MAX);
		if (wet) {
			DWM_EWWOW("kv_set_thewmaw_tempewatuwe_wange faiwed\n");
			wetuwn wet;
		}
		kv_enabwe_thewmaw_int(wdev, twue);
	}

	/* powewdown unused bwocks fow now */
	kv_dpm_powewgate_acp(wdev, twue);
	kv_dpm_powewgate_samu(wdev, twue);
	kv_dpm_powewgate_vce(wdev, twue);
	kv_dpm_powewgate_uvd(wdev, twue);

	wetuwn wet;
}

void kv_dpm_disabwe(stwuct wadeon_device *wdev)
{
	kv_smc_bapm_enabwe(wdev, fawse);

	if (wdev->famiwy == CHIP_MUWWINS)
		kv_enabwe_nb_dpm(wdev, fawse);

	/* powewup bwocks */
	kv_dpm_powewgate_acp(wdev, fawse);
	kv_dpm_powewgate_samu(wdev, fawse);
	kv_dpm_powewgate_vce(wdev, fawse);
	kv_dpm_powewgate_uvd(wdev, fawse);

	kv_enabwe_smc_cac(wdev, fawse);
	kv_enabwe_didt(wdev, fawse);
	kv_cweaw_vc(wdev);
	kv_stop_dpm(wdev);
	kv_enabwe_uwv(wdev, fawse);
	kv_weset_am(wdev);
	kv_enabwe_thewmaw_int(wdev, fawse);

	kv_update_cuwwent_ps(wdev, wdev->pm.dpm.boot_ps);
}

static void kv_init_scwk_t(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	pi->wow_scwk_intewwupt_t = 0;
}

static int kv_init_fps_wimits(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet = 0;

	if (pi->caps_fps) {
		u16 tmp;

		tmp = 45;
		pi->fps_high_t = cpu_to_be16(tmp);
		wet = kv_copy_bytes_to_smc(wdev,
					   pi->dpm_tabwe_stawt +
					   offsetof(SMU7_Fusion_DpmTabwe, FpsHighT),
					   (u8 *)&pi->fps_high_t,
					   sizeof(u16), pi->swam_end);

		tmp = 30;
		pi->fps_wow_t = cpu_to_be16(tmp);

		wet = kv_copy_bytes_to_smc(wdev,
					   pi->dpm_tabwe_stawt +
					   offsetof(SMU7_Fusion_DpmTabwe, FpsWowT),
					   (u8 *)&pi->fps_wow_t,
					   sizeof(u16), pi->swam_end);

	}
	wetuwn wet;
}

static void kv_init_powewgate_state(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	pi->uvd_powew_gated = fawse;
	pi->vce_powew_gated = fawse;
	pi->samu_powew_gated = fawse;
	pi->acp_powew_gated = fawse;

}

static int kv_enabwe_uvd_dpm(stwuct wadeon_device *wdev, boow enabwe)
{
	wetuwn kv_notify_message_to_smu(wdev, enabwe ?
					PPSMC_MSG_UVDDPM_Enabwe : PPSMC_MSG_UVDDPM_Disabwe);
}

static int kv_enabwe_vce_dpm(stwuct wadeon_device *wdev, boow enabwe)
{
	wetuwn kv_notify_message_to_smu(wdev, enabwe ?
					PPSMC_MSG_VCEDPM_Enabwe : PPSMC_MSG_VCEDPM_Disabwe);
}

static int kv_enabwe_samu_dpm(stwuct wadeon_device *wdev, boow enabwe)
{
	wetuwn kv_notify_message_to_smu(wdev, enabwe ?
					PPSMC_MSG_SAMUDPM_Enabwe : PPSMC_MSG_SAMUDPM_Disabwe);
}

static int kv_enabwe_acp_dpm(stwuct wadeon_device *wdev, boow enabwe)
{
	wetuwn kv_notify_message_to_smu(wdev, enabwe ?
					PPSMC_MSG_ACPDPM_Enabwe : PPSMC_MSG_ACPDPM_Disabwe);
}

static int kv_update_uvd_dpm(stwuct wadeon_device *wdev, boow gate)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_uvd_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe;
	int wet;
	u32 mask;

	if (!gate) {
		if (tabwe->count)
			pi->uvd_boot_wevew = tabwe->count - 1;
		ewse
			pi->uvd_boot_wevew = 0;

		if (!pi->caps_uvd_dpm || pi->caps_stabwe_p_state) {
			mask = 1 << pi->uvd_boot_wevew;
		} ewse {
			mask = 0x1f;
		}

		wet = kv_copy_bytes_to_smc(wdev,
					   pi->dpm_tabwe_stawt +
					   offsetof(SMU7_Fusion_DpmTabwe, UvdBootWevew),
					   (uint8_t *)&pi->uvd_boot_wevew,
					   sizeof(u8), pi->swam_end);
		if (wet)
			wetuwn wet;

		kv_send_msg_to_smc_with_pawametew(wdev,
						  PPSMC_MSG_UVDDPM_SetEnabwedMask,
						  mask);
	}

	wetuwn kv_enabwe_uvd_dpm(wdev, !gate);
}

static u8 kv_get_vce_boot_wevew(stwuct wadeon_device *wdev, u32 evcwk)
{
	u8 i;
	stwuct wadeon_vce_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe;

	fow (i = 0; i < tabwe->count; i++) {
		if (tabwe->entwies[i].evcwk >= evcwk)
			bweak;
	}

	wetuwn i;
}

static int kv_update_vce_dpm(stwuct wadeon_device *wdev,
			     stwuct wadeon_ps *wadeon_new_state,
			     stwuct wadeon_ps *wadeon_cuwwent_state)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_vce_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe;
	int wet;

	if (wadeon_new_state->evcwk > 0 && wadeon_cuwwent_state->evcwk == 0) {
		kv_dpm_powewgate_vce(wdev, fawse);
		/* tuwn the cwocks on when encoding */
		cik_update_cg(wdev, WADEON_CG_BWOCK_VCE, fawse);
		if (pi->caps_stabwe_p_state)
			pi->vce_boot_wevew = tabwe->count - 1;
		ewse
			pi->vce_boot_wevew = kv_get_vce_boot_wevew(wdev, wadeon_new_state->evcwk);

		wet = kv_copy_bytes_to_smc(wdev,
					   pi->dpm_tabwe_stawt +
					   offsetof(SMU7_Fusion_DpmTabwe, VceBootWevew),
					   (u8 *)&pi->vce_boot_wevew,
					   sizeof(u8),
					   pi->swam_end);
		if (wet)
			wetuwn wet;

		if (pi->caps_stabwe_p_state)
			kv_send_msg_to_smc_with_pawametew(wdev,
							  PPSMC_MSG_VCEDPM_SetEnabwedMask,
							  (1 << pi->vce_boot_wevew));

		kv_enabwe_vce_dpm(wdev, twue);
	} ewse if (wadeon_new_state->evcwk == 0 && wadeon_cuwwent_state->evcwk > 0) {
		kv_enabwe_vce_dpm(wdev, fawse);
		/* tuwn the cwocks off when not encoding */
		cik_update_cg(wdev, WADEON_CG_BWOCK_VCE, twue);
		kv_dpm_powewgate_vce(wdev, twue);
	}

	wetuwn 0;
}

static int kv_update_samu_dpm(stwuct wadeon_device *wdev, boow gate)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe;
	int wet;

	if (!gate) {
		if (pi->caps_stabwe_p_state)
			pi->samu_boot_wevew = tabwe->count - 1;
		ewse
			pi->samu_boot_wevew = 0;

		wet = kv_copy_bytes_to_smc(wdev,
					   pi->dpm_tabwe_stawt +
					   offsetof(SMU7_Fusion_DpmTabwe, SamuBootWevew),
					   (u8 *)&pi->samu_boot_wevew,
					   sizeof(u8),
					   pi->swam_end);
		if (wet)
			wetuwn wet;

		if (pi->caps_stabwe_p_state)
			kv_send_msg_to_smc_with_pawametew(wdev,
							  PPSMC_MSG_SAMUDPM_SetEnabwedMask,
							  (1 << pi->samu_boot_wevew));
	}

	wetuwn kv_enabwe_samu_dpm(wdev, !gate);
}

static u8 kv_get_acp_boot_wevew(stwuct wadeon_device *wdev)
{
	u8 i;
	stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe;

	fow (i = 0; i < tabwe->count; i++) {
		if (tabwe->entwies[i].cwk >= 0) /* XXX */
			bweak;
	}

	if (i >= tabwe->count)
		i = tabwe->count - 1;

	wetuwn i;
}

static void kv_update_acp_boot_wevew(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u8 acp_boot_wevew;

	if (!pi->caps_stabwe_p_state) {
		acp_boot_wevew = kv_get_acp_boot_wevew(wdev);
		if (acp_boot_wevew != pi->acp_boot_wevew) {
			pi->acp_boot_wevew = acp_boot_wevew;
			kv_send_msg_to_smc_with_pawametew(wdev,
							  PPSMC_MSG_ACPDPM_SetEnabwedMask,
							  (1 << pi->acp_boot_wevew));
		}
	}
}

static int kv_update_acp_dpm(stwuct wadeon_device *wdev, boow gate)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe;
	int wet;

	if (!gate) {
		if (pi->caps_stabwe_p_state)
			pi->acp_boot_wevew = tabwe->count - 1;
		ewse
			pi->acp_boot_wevew = kv_get_acp_boot_wevew(wdev);

		wet = kv_copy_bytes_to_smc(wdev,
					   pi->dpm_tabwe_stawt +
					   offsetof(SMU7_Fusion_DpmTabwe, AcpBootWevew),
					   (u8 *)&pi->acp_boot_wevew,
					   sizeof(u8),
					   pi->swam_end);
		if (wet)
			wetuwn wet;

		if (pi->caps_stabwe_p_state)
			kv_send_msg_to_smc_with_pawametew(wdev,
							  PPSMC_MSG_ACPDPM_SetEnabwedMask,
							  (1 << pi->acp_boot_wevew));
	}

	wetuwn kv_enabwe_acp_dpm(wdev, !gate);
}

void kv_dpm_powewgate_uvd(stwuct wadeon_device *wdev, boow gate)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	if (pi->uvd_powew_gated == gate)
		wetuwn;

	pi->uvd_powew_gated = gate;

	if (gate) {
		if (pi->caps_uvd_pg) {
			uvd_v1_0_stop(wdev);
			cik_update_cg(wdev, WADEON_CG_BWOCK_UVD, fawse);
		}
		kv_update_uvd_dpm(wdev, gate);
		if (pi->caps_uvd_pg)
			kv_notify_message_to_smu(wdev, PPSMC_MSG_UVDPowewOFF);
	} ewse {
		if (pi->caps_uvd_pg) {
			kv_notify_message_to_smu(wdev, PPSMC_MSG_UVDPowewON);
			uvd_v4_2_wesume(wdev);
			uvd_v1_0_stawt(wdev);
			cik_update_cg(wdev, WADEON_CG_BWOCK_UVD, twue);
		}
		kv_update_uvd_dpm(wdev, gate);
	}
}

static void kv_dpm_powewgate_vce(stwuct wadeon_device *wdev, boow gate)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	if (pi->vce_powew_gated == gate)
		wetuwn;

	pi->vce_powew_gated = gate;

	if (gate) {
		if (pi->caps_vce_pg) {
			/* XXX do we need a vce_v1_0_stop() ?  */
			kv_notify_message_to_smu(wdev, PPSMC_MSG_VCEPowewOFF);
		}
	} ewse {
		if (pi->caps_vce_pg) {
			kv_notify_message_to_smu(wdev, PPSMC_MSG_VCEPowewON);
			vce_v2_0_wesume(wdev);
			vce_v1_0_stawt(wdev);
		}
	}
}

static void kv_dpm_powewgate_samu(stwuct wadeon_device *wdev, boow gate)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	if (pi->samu_powew_gated == gate)
		wetuwn;

	pi->samu_powew_gated = gate;

	if (gate) {
		kv_update_samu_dpm(wdev, twue);
		if (pi->caps_samu_pg)
			kv_notify_message_to_smu(wdev, PPSMC_MSG_SAMPowewOFF);
	} ewse {
		if (pi->caps_samu_pg)
			kv_notify_message_to_smu(wdev, PPSMC_MSG_SAMPowewON);
		kv_update_samu_dpm(wdev, fawse);
	}
}

static void kv_dpm_powewgate_acp(stwuct wadeon_device *wdev, boow gate)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	if (pi->acp_powew_gated == gate)
		wetuwn;

	if (wdev->famiwy == CHIP_KABINI || wdev->famiwy == CHIP_MUWWINS)
		wetuwn;

	pi->acp_powew_gated = gate;

	if (gate) {
		kv_update_acp_dpm(wdev, twue);
		if (pi->caps_acp_pg)
			kv_notify_message_to_smu(wdev, PPSMC_MSG_ACPPowewOFF);
	} ewse {
		if (pi->caps_acp_pg)
			kv_notify_message_to_smu(wdev, PPSMC_MSG_ACPPowewON);
		kv_update_acp_dpm(wdev, fawse);
	}
}

static void kv_set_vawid_cwock_wange(stwuct wadeon_device *wdev,
				     stwuct wadeon_ps *new_wps)
{
	stwuct kv_ps *new_ps = kv_get_ps(new_wps);
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 i;
	stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk;

	if (tabwe && tabwe->count) {
		fow (i = 0; i < pi->gwaphics_dpm_wevew_count; i++) {
			if ((tabwe->entwies[i].cwk >= new_ps->wevews[0].scwk) ||
			    (i == (pi->gwaphics_dpm_wevew_count - 1))) {
				pi->wowest_vawid = i;
				bweak;
			}
		}

		fow (i = pi->gwaphics_dpm_wevew_count - 1; i > 0; i--) {
			if (tabwe->entwies[i].cwk <= new_ps->wevews[new_ps->num_wevews - 1].scwk)
				bweak;
		}
		pi->highest_vawid = i;

		if (pi->wowest_vawid > pi->highest_vawid) {
			if ((new_ps->wevews[0].scwk - tabwe->entwies[pi->highest_vawid].cwk) >
			    (tabwe->entwies[pi->wowest_vawid].cwk - new_ps->wevews[new_ps->num_wevews - 1].scwk))
				pi->highest_vawid = pi->wowest_vawid;
			ewse
				pi->wowest_vawid =  pi->highest_vawid;
		}
	} ewse {
		stwuct sumo_scwk_vowtage_mapping_tabwe *tabwe =
			&pi->sys_info.scwk_vowtage_mapping_tabwe;

		fow (i = 0; i < (int)pi->gwaphics_dpm_wevew_count; i++) {
			if (tabwe->entwies[i].scwk_fwequency >= new_ps->wevews[0].scwk ||
			    i == (int)(pi->gwaphics_dpm_wevew_count - 1)) {
				pi->wowest_vawid = i;
				bweak;
			}
		}

		fow (i = pi->gwaphics_dpm_wevew_count - 1; i > 0; i--) {
			if (tabwe->entwies[i].scwk_fwequency <=
			    new_ps->wevews[new_ps->num_wevews - 1].scwk)
				bweak;
		}
		pi->highest_vawid = i;

		if (pi->wowest_vawid > pi->highest_vawid) {
			if ((new_ps->wevews[0].scwk -
			     tabwe->entwies[pi->highest_vawid].scwk_fwequency) >
			    (tabwe->entwies[pi->wowest_vawid].scwk_fwequency -
			     new_ps->wevews[new_ps->num_wevews -1].scwk))
				pi->highest_vawid = pi->wowest_vawid;
			ewse
				pi->wowest_vawid =  pi->highest_vawid;
		}
	}
}

static int kv_update_dfs_bypass_settings(stwuct wadeon_device *wdev,
					 stwuct wadeon_ps *new_wps)
{
	stwuct kv_ps *new_ps = kv_get_ps(new_wps);
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet = 0;
	u8 cwk_bypass_cntw;

	if (pi->caps_enabwe_dfs_bypass) {
		cwk_bypass_cntw = new_ps->need_dfs_bypass ?
			pi->gwaphics_wevew[pi->gwaphics_boot_wevew].CwkBypassCntw : 0;
		wet = kv_copy_bytes_to_smc(wdev,
					   (pi->dpm_tabwe_stawt +
					    offsetof(SMU7_Fusion_DpmTabwe, GwaphicsWevew) +
					    (pi->gwaphics_boot_wevew * sizeof(SMU7_Fusion_GwaphicsWevew)) +
					    offsetof(SMU7_Fusion_GwaphicsWevew, CwkBypassCntw)),
					   &cwk_bypass_cntw,
					   sizeof(u8), pi->swam_end);
	}

	wetuwn wet;
}

static int kv_enabwe_nb_dpm(stwuct wadeon_device *wdev,
			    boow enabwe)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	int wet = 0;

	if (enabwe) {
		if (pi->enabwe_nb_dpm && !pi->nb_dpm_enabwed) {
			wet = kv_notify_message_to_smu(wdev, PPSMC_MSG_NBDPM_Enabwe);
			if (wet == 0)
				pi->nb_dpm_enabwed = twue;
		}
	} ewse {
		if (pi->enabwe_nb_dpm && pi->nb_dpm_enabwed) {
			wet = kv_notify_message_to_smu(wdev, PPSMC_MSG_NBDPM_Disabwe);
			if (wet == 0)
				pi->nb_dpm_enabwed = fawse;
		}
	}

	wetuwn wet;
}

int kv_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				   enum wadeon_dpm_fowced_wevew wevew)
{
	int wet;

	if (wevew == WADEON_DPM_FOWCED_WEVEW_HIGH) {
		wet = kv_fowce_dpm_highest(wdev);
		if (wet)
			wetuwn wet;
	} ewse if (wevew == WADEON_DPM_FOWCED_WEVEW_WOW) {
		wet = kv_fowce_dpm_wowest(wdev);
		if (wet)
			wetuwn wet;
	} ewse if (wevew == WADEON_DPM_FOWCED_WEVEW_AUTO) {
		wet = kv_unfowce_wevews(wdev);
		if (wet)
			wetuwn wet;
	}

	wdev->pm.dpm.fowced_wevew = wevew;

	wetuwn 0;
}

int kv_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_ps wequested_ps = *wdev->pm.dpm.wequested_ps;
	stwuct wadeon_ps *new_ps = &wequested_ps;

	kv_update_wequested_ps(wdev, new_ps);

	kv_appwy_state_adjust_wuwes(wdev,
				    &pi->wequested_wps,
				    &pi->cuwwent_wps);

	wetuwn 0;
}

int kv_dpm_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_ps *new_ps = &pi->wequested_wps;
	stwuct wadeon_ps *owd_ps = &pi->cuwwent_wps;
	int wet;

	if (pi->bapm_enabwe) {
		wet = kv_smc_bapm_enabwe(wdev, wdev->pm.dpm.ac_powew);
		if (wet) {
			DWM_EWWOW("kv_smc_bapm_enabwe faiwed\n");
			wetuwn wet;
		}
	}

	if (wdev->famiwy == CHIP_KABINI || wdev->famiwy == CHIP_MUWWINS) {
		if (pi->enabwe_dpm) {
			kv_set_vawid_cwock_wange(wdev, new_ps);
			kv_update_dfs_bypass_settings(wdev, new_ps);
			wet = kv_cawcuwate_ds_dividew(wdev);
			if (wet) {
				DWM_EWWOW("kv_cawcuwate_ds_dividew faiwed\n");
				wetuwn wet;
			}
			kv_cawcuwate_nbps_wevew_settings(wdev);
			kv_cawcuwate_dpm_settings(wdev);
			kv_fowce_wowest_vawid(wdev);
			kv_enabwe_new_wevews(wdev);
			kv_upwoad_dpm_settings(wdev);
			kv_pwogwam_nbps_index_settings(wdev, new_ps);
			kv_unfowce_wevews(wdev);
			kv_set_enabwed_wevews(wdev);
			kv_fowce_wowest_vawid(wdev);
			kv_unfowce_wevews(wdev);

			wet = kv_update_vce_dpm(wdev, new_ps, owd_ps);
			if (wet) {
				DWM_EWWOW("kv_update_vce_dpm faiwed\n");
				wetuwn wet;
			}
			kv_update_scwk_t(wdev);
			if (wdev->famiwy == CHIP_MUWWINS)
				kv_enabwe_nb_dpm(wdev, twue);
		}
	} ewse {
		if (pi->enabwe_dpm) {
			kv_set_vawid_cwock_wange(wdev, new_ps);
			kv_update_dfs_bypass_settings(wdev, new_ps);
			wet = kv_cawcuwate_ds_dividew(wdev);
			if (wet) {
				DWM_EWWOW("kv_cawcuwate_ds_dividew faiwed\n");
				wetuwn wet;
			}
			kv_cawcuwate_nbps_wevew_settings(wdev);
			kv_cawcuwate_dpm_settings(wdev);
			kv_fweeze_scwk_dpm(wdev, twue);
			kv_upwoad_dpm_settings(wdev);
			kv_pwogwam_nbps_index_settings(wdev, new_ps);
			kv_fweeze_scwk_dpm(wdev, fawse);
			kv_set_enabwed_wevews(wdev);
			wet = kv_update_vce_dpm(wdev, new_ps, owd_ps);
			if (wet) {
				DWM_EWWOW("kv_update_vce_dpm faiwed\n");
				wetuwn wet;
			}
			kv_update_acp_boot_wevew(wdev);
			kv_update_scwk_t(wdev);
			kv_enabwe_nb_dpm(wdev, twue);
		}
	}

	wetuwn 0;
}

void kv_dpm_post_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_ps *new_ps = &pi->wequested_wps;

	kv_update_cuwwent_ps(wdev, new_ps);
}

void kv_dpm_setup_asic(stwuct wadeon_device *wdev)
{
	sumo_take_smu_contwow(wdev, twue);
	kv_init_powewgate_state(wdev);
	kv_init_scwk_t(wdev);
}

//XXX use sumo_dpm_dispway_configuwation_changed

static void kv_constwuct_max_powew_wimits_tabwe(stwuct wadeon_device *wdev,
						stwuct wadeon_cwock_and_vowtage_wimits *tabwe)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	if (pi->sys_info.scwk_vowtage_mapping_tabwe.num_max_dpm_entwies > 0) {
		int idx = pi->sys_info.scwk_vowtage_mapping_tabwe.num_max_dpm_entwies - 1;
		tabwe->scwk =
			pi->sys_info.scwk_vowtage_mapping_tabwe.entwies[idx].scwk_fwequency;
		tabwe->vddc =
			kv_convewt_2bit_index_to_vowtage(wdev,
							 pi->sys_info.scwk_vowtage_mapping_tabwe.entwies[idx].vid_2bit);
	}

	tabwe->mcwk = pi->sys_info.nbp_memowy_cwock[0];
}

static void kv_patch_vowtage_vawues(stwuct wadeon_device *wdev)
{
	int i;
	stwuct wadeon_uvd_cwock_vowtage_dependency_tabwe *uvd_tabwe =
		&wdev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe;
	stwuct wadeon_vce_cwock_vowtage_dependency_tabwe *vce_tabwe =
		&wdev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe;
	stwuct wadeon_cwock_vowtage_dependency_tabwe *samu_tabwe =
		&wdev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe;
	stwuct wadeon_cwock_vowtage_dependency_tabwe *acp_tabwe =
		&wdev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe;

	if (uvd_tabwe->count) {
		fow (i = 0; i < uvd_tabwe->count; i++)
			uvd_tabwe->entwies[i].v =
				kv_convewt_8bit_index_to_vowtage(wdev,
								 uvd_tabwe->entwies[i].v);
	}

	if (vce_tabwe->count) {
		fow (i = 0; i < vce_tabwe->count; i++)
			vce_tabwe->entwies[i].v =
				kv_convewt_8bit_index_to_vowtage(wdev,
								 vce_tabwe->entwies[i].v);
	}

	if (samu_tabwe->count) {
		fow (i = 0; i < samu_tabwe->count; i++)
			samu_tabwe->entwies[i].v =
				kv_convewt_8bit_index_to_vowtage(wdev,
								 samu_tabwe->entwies[i].v);
	}

	if (acp_tabwe->count) {
		fow (i = 0; i < acp_tabwe->count; i++)
			acp_tabwe->entwies[i].v =
				kv_convewt_8bit_index_to_vowtage(wdev,
								 acp_tabwe->entwies[i].v);
	}

}

static void kv_constwuct_boot_state(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	pi->boot_pw.scwk = pi->sys_info.bootup_scwk;
	pi->boot_pw.vddc_index = pi->sys_info.bootup_nb_vowtage_index;
	pi->boot_pw.ds_dividew_index = 0;
	pi->boot_pw.ss_dividew_index = 0;
	pi->boot_pw.awwow_gnb_swow = 1;
	pi->boot_pw.fowce_nbp_state = 0;
	pi->boot_pw.dispway_wm = 0;
	pi->boot_pw.vce_wm = 0;
}

static int kv_fowce_dpm_highest(stwuct wadeon_device *wdev)
{
	int wet;
	u32 enabwe_mask, i;

	wet = kv_dpm_get_enabwe_mask(wdev, &enabwe_mask);
	if (wet)
		wetuwn wet;

	fow (i = SMU7_MAX_WEVEWS_GWAPHICS - 1; i > 0; i--) {
		if (enabwe_mask & (1 << i))
			bweak;
	}

	if (wdev->famiwy == CHIP_KABINI || wdev->famiwy == CHIP_MUWWINS)
		wetuwn kv_send_msg_to_smc_with_pawametew(wdev, PPSMC_MSG_DPM_FowceState, i);
	ewse
		wetuwn kv_set_enabwed_wevew(wdev, i);
}

static int kv_fowce_dpm_wowest(stwuct wadeon_device *wdev)
{
	int wet;
	u32 enabwe_mask, i;

	wet = kv_dpm_get_enabwe_mask(wdev, &enabwe_mask);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < SMU7_MAX_WEVEWS_GWAPHICS; i++) {
		if (enabwe_mask & (1 << i))
			bweak;
	}

	if (wdev->famiwy == CHIP_KABINI || wdev->famiwy == CHIP_MUWWINS)
		wetuwn kv_send_msg_to_smc_with_pawametew(wdev, PPSMC_MSG_DPM_FowceState, i);
	ewse
		wetuwn kv_set_enabwed_wevew(wdev, i);
}

static u8 kv_get_sweep_dividew_id_fwom_cwock(stwuct wadeon_device *wdev,
					     u32 scwk, u32 min_scwk_in_sw)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 i;
	u32 temp;
	u32 min = (min_scwk_in_sw > KV_MINIMUM_ENGINE_CWOCK) ?
		min_scwk_in_sw : KV_MINIMUM_ENGINE_CWOCK;

	if (scwk < min)
		wetuwn 0;

	if (!pi->caps_scwk_ds)
		wetuwn 0;

	fow (i = KV_MAX_DEEPSWEEP_DIVIDEW_ID; i > 0; i--) {
		temp = scwk / sumo_get_sweep_dividew_fwom_id(i);
		if (temp >= min)
			bweak;
	}

	wetuwn (u8)i;
}

static int kv_get_high_vowtage_wimit(stwuct wadeon_device *wdev, int *wimit)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk;
	int i;

	if (tabwe && tabwe->count) {
		fow (i = tabwe->count - 1; i >= 0; i--) {
			if (pi->high_vowtage_t &&
			    (kv_convewt_8bit_index_to_vowtage(wdev, tabwe->entwies[i].v) <=
			     pi->high_vowtage_t)) {
				*wimit = i;
				wetuwn 0;
			}
		}
	} ewse {
		stwuct sumo_scwk_vowtage_mapping_tabwe *tabwe =
			&pi->sys_info.scwk_vowtage_mapping_tabwe;

		fow (i = tabwe->num_max_dpm_entwies - 1; i >= 0; i--) {
			if (pi->high_vowtage_t &&
			    (kv_convewt_2bit_index_to_vowtage(wdev, tabwe->entwies[i].vid_2bit) <=
			     pi->high_vowtage_t)) {
				*wimit = i;
				wetuwn 0;
			}
		}
	}

	*wimit = 0;
	wetuwn 0;
}

static void kv_appwy_state_adjust_wuwes(stwuct wadeon_device *wdev,
					stwuct wadeon_ps *new_wps,
					stwuct wadeon_ps *owd_wps)
{
	stwuct kv_ps *ps = kv_get_ps(new_wps);
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 min_scwk = 10000; /* ??? */
	u32 scwk, mcwk = 0;
	int i, wimit;
	boow fowce_high;
	stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk;
	u32 stabwe_p_state_scwk = 0;
	stwuct wadeon_cwock_and_vowtage_wimits *max_wimits =
		&wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac;

	if (new_wps->vce_active) {
		new_wps->evcwk = wdev->pm.dpm.vce_states[wdev->pm.dpm.vce_wevew].evcwk;
		new_wps->eccwk = wdev->pm.dpm.vce_states[wdev->pm.dpm.vce_wevew].eccwk;
	} ewse {
		new_wps->evcwk = 0;
		new_wps->eccwk = 0;
	}

	mcwk = max_wimits->mcwk;
	scwk = min_scwk;

	if (pi->caps_stabwe_p_state) {
		stabwe_p_state_scwk = (max_wimits->scwk * 75) / 100;

		fow (i = tabwe->count - 1; i >= 0; i--) {
			if (stabwe_p_state_scwk >= tabwe->entwies[i].cwk) {
				stabwe_p_state_scwk = tabwe->entwies[i].cwk;
				bweak;
			}
		}

		if (i > 0)
			stabwe_p_state_scwk = tabwe->entwies[0].cwk;

		scwk = stabwe_p_state_scwk;
	}

	if (new_wps->vce_active) {
		if (scwk < wdev->pm.dpm.vce_states[wdev->pm.dpm.vce_wevew].scwk)
			scwk = wdev->pm.dpm.vce_states[wdev->pm.dpm.vce_wevew].scwk;
	}

	ps->need_dfs_bypass = twue;

	fow (i = 0; i < ps->num_wevews; i++) {
		if (ps->wevews[i].scwk < scwk)
			ps->wevews[i].scwk = scwk;
	}

	if (tabwe && tabwe->count) {
		fow (i = 0; i < ps->num_wevews; i++) {
			if (pi->high_vowtage_t &&
			    (pi->high_vowtage_t <
			     kv_convewt_8bit_index_to_vowtage(wdev, ps->wevews[i].vddc_index))) {
				kv_get_high_vowtage_wimit(wdev, &wimit);
				ps->wevews[i].scwk = tabwe->entwies[wimit].cwk;
			}
		}
	} ewse {
		stwuct sumo_scwk_vowtage_mapping_tabwe *tabwe =
			&pi->sys_info.scwk_vowtage_mapping_tabwe;

		fow (i = 0; i < ps->num_wevews; i++) {
			if (pi->high_vowtage_t &&
			    (pi->high_vowtage_t <
			     kv_convewt_8bit_index_to_vowtage(wdev, ps->wevews[i].vddc_index))) {
				kv_get_high_vowtage_wimit(wdev, &wimit);
				ps->wevews[i].scwk = tabwe->entwies[wimit].scwk_fwequency;
			}
		}
	}

	if (pi->caps_stabwe_p_state) {
		fow (i = 0; i < ps->num_wevews; i++) {
			ps->wevews[i].scwk = stabwe_p_state_scwk;
		}
	}

	pi->video_stawt = new_wps->dcwk || new_wps->vcwk ||
		new_wps->evcwk || new_wps->eccwk;

	if ((new_wps->cwass & ATOM_PPWIB_CWASSIFICATION_UI_MASK) ==
	    ATOM_PPWIB_CWASSIFICATION_UI_BATTEWY)
		pi->battewy_state = twue;
	ewse
		pi->battewy_state = fawse;

	if (wdev->famiwy == CHIP_KABINI || wdev->famiwy == CHIP_MUWWINS) {
		ps->dpm0_pg_nb_ps_wo = 0x1;
		ps->dpm0_pg_nb_ps_hi = 0x0;
		ps->dpmx_nb_ps_wo = 0x1;
		ps->dpmx_nb_ps_hi = 0x0;
	} ewse {
		ps->dpm0_pg_nb_ps_wo = 0x3;
		ps->dpm0_pg_nb_ps_hi = 0x0;
		ps->dpmx_nb_ps_wo = 0x3;
		ps->dpmx_nb_ps_hi = 0x0;

		if (pi->sys_info.nb_dpm_enabwe) {
			fowce_high = (mcwk >= pi->sys_info.nbp_memowy_cwock[3]) ||
				pi->video_stawt || (wdev->pm.dpm.new_active_cwtc_count >= 3) ||
				pi->disabwe_nb_ps3_in_battewy;
			ps->dpm0_pg_nb_ps_wo = fowce_high ? 0x2 : 0x3;
			ps->dpm0_pg_nb_ps_hi = 0x2;
			ps->dpmx_nb_ps_wo = fowce_high ? 0x2 : 0x3;
			ps->dpmx_nb_ps_hi = 0x2;
		}
	}
}

static void kv_dpm_powew_wevew_enabwed_fow_thwottwe(stwuct wadeon_device *wdev,
						    u32 index, boow enabwe)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	pi->gwaphics_wevew[index].EnabwedFowThwottwe = enabwe ? 1 : 0;
}

static int kv_cawcuwate_ds_dividew(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 scwk_in_sw = 10000; /* ??? */
	u32 i;

	if (pi->wowest_vawid > pi->highest_vawid)
		wetuwn -EINVAW;

	fow (i = pi->wowest_vawid; i <= pi->highest_vawid; i++) {
		pi->gwaphics_wevew[i].DeepSweepDivId =
			kv_get_sweep_dividew_id_fwom_cwock(wdev,
							   be32_to_cpu(pi->gwaphics_wevew[i].ScwkFwequency),
							   scwk_in_sw);
	}
	wetuwn 0;
}

static int kv_cawcuwate_nbps_wevew_settings(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 i;
	boow fowce_high;
	stwuct wadeon_cwock_and_vowtage_wimits *max_wimits =
		&wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac;
	u32 mcwk = max_wimits->mcwk;

	if (pi->wowest_vawid > pi->highest_vawid)
		wetuwn -EINVAW;

	if (wdev->famiwy == CHIP_KABINI || wdev->famiwy == CHIP_MUWWINS) {
		fow (i = pi->wowest_vawid; i <= pi->highest_vawid; i++) {
			pi->gwaphics_wevew[i].GnbSwow = 1;
			pi->gwaphics_wevew[i].FowceNbPs1 = 0;
			pi->gwaphics_wevew[i].UpH = 0;
		}

		if (!pi->sys_info.nb_dpm_enabwe)
			wetuwn 0;

		fowce_high = ((mcwk >= pi->sys_info.nbp_memowy_cwock[3]) ||
			      (wdev->pm.dpm.new_active_cwtc_count >= 3) || pi->video_stawt);

		if (fowce_high) {
			fow (i = pi->wowest_vawid; i <= pi->highest_vawid; i++)
				pi->gwaphics_wevew[i].GnbSwow = 0;
		} ewse {
			if (pi->battewy_state)
				pi->gwaphics_wevew[0].FowceNbPs1 = 1;

			pi->gwaphics_wevew[1].GnbSwow = 0;
			pi->gwaphics_wevew[2].GnbSwow = 0;
			pi->gwaphics_wevew[3].GnbSwow = 0;
			pi->gwaphics_wevew[4].GnbSwow = 0;
		}
	} ewse {
		fow (i = pi->wowest_vawid; i <= pi->highest_vawid; i++) {
			pi->gwaphics_wevew[i].GnbSwow = 1;
			pi->gwaphics_wevew[i].FowceNbPs1 = 0;
			pi->gwaphics_wevew[i].UpH = 0;
		}

		if (pi->sys_info.nb_dpm_enabwe && pi->battewy_state) {
			pi->gwaphics_wevew[pi->wowest_vawid].UpH = 0x28;
			pi->gwaphics_wevew[pi->wowest_vawid].GnbSwow = 0;
			if (pi->wowest_vawid != pi->highest_vawid)
				pi->gwaphics_wevew[pi->wowest_vawid].FowceNbPs1 = 1;
		}
	}
	wetuwn 0;
}

static int kv_cawcuwate_dpm_settings(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 i;

	if (pi->wowest_vawid > pi->highest_vawid)
		wetuwn -EINVAW;

	fow (i = pi->wowest_vawid; i <= pi->highest_vawid; i++)
		pi->gwaphics_wevew[i].DispwayWatewmawk = (i == pi->highest_vawid) ? 1 : 0;

	wetuwn 0;
}

static void kv_init_gwaphics_wevews(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 i;
	stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe =
		&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk;

	if (tabwe && tabwe->count) {
		u32 vid_2bit;

		pi->gwaphics_dpm_wevew_count = 0;
		fow (i = 0; i < tabwe->count; i++) {
			if (pi->high_vowtage_t &&
			    (pi->high_vowtage_t <
			     kv_convewt_8bit_index_to_vowtage(wdev, tabwe->entwies[i].v)))
				bweak;

			kv_set_dividew_vawue(wdev, i, tabwe->entwies[i].cwk);
			vid_2bit = kv_convewt_vid7_to_vid2(wdev,
							   &pi->sys_info.vid_mapping_tabwe,
							   tabwe->entwies[i].v);
			kv_set_vid(wdev, i, vid_2bit);
			kv_set_at(wdev, i, pi->at[i]);
			kv_dpm_powew_wevew_enabwed_fow_thwottwe(wdev, i, twue);
			pi->gwaphics_dpm_wevew_count++;
		}
	} ewse {
		stwuct sumo_scwk_vowtage_mapping_tabwe *tabwe =
			&pi->sys_info.scwk_vowtage_mapping_tabwe;

		pi->gwaphics_dpm_wevew_count = 0;
		fow (i = 0; i < tabwe->num_max_dpm_entwies; i++) {
			if (pi->high_vowtage_t &&
			    pi->high_vowtage_t <
			    kv_convewt_2bit_index_to_vowtage(wdev, tabwe->entwies[i].vid_2bit))
				bweak;

			kv_set_dividew_vawue(wdev, i, tabwe->entwies[i].scwk_fwequency);
			kv_set_vid(wdev, i, tabwe->entwies[i].vid_2bit);
			kv_set_at(wdev, i, pi->at[i]);
			kv_dpm_powew_wevew_enabwed_fow_thwottwe(wdev, i, twue);
			pi->gwaphics_dpm_wevew_count++;
		}
	}

	fow (i = 0; i < SMU7_MAX_WEVEWS_GWAPHICS; i++)
		kv_dpm_powew_wevew_enabwe(wdev, i, fawse);
}

static void kv_enabwe_new_wevews(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 i;

	fow (i = 0; i < SMU7_MAX_WEVEWS_GWAPHICS; i++) {
		if (i >= pi->wowest_vawid && i <= pi->highest_vawid)
			kv_dpm_powew_wevew_enabwe(wdev, i, twue);
	}
}

static int kv_set_enabwed_wevew(stwuct wadeon_device *wdev, u32 wevew)
{
	u32 new_mask = (1 << wevew);

	wetuwn kv_send_msg_to_smc_with_pawametew(wdev,
						 PPSMC_MSG_SCWKDPM_SetEnabwedMask,
						 new_mask);
}

static int kv_set_enabwed_wevews(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 i, new_mask = 0;

	fow (i = pi->wowest_vawid; i <= pi->highest_vawid; i++)
		new_mask |= (1 << i);

	wetuwn kv_send_msg_to_smc_with_pawametew(wdev,
						 PPSMC_MSG_SCWKDPM_SetEnabwedMask,
						 new_mask);
}

static void kv_pwogwam_nbps_index_settings(stwuct wadeon_device *wdev,
					   stwuct wadeon_ps *new_wps)
{
	stwuct kv_ps *new_ps = kv_get_ps(new_wps);
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 nbdpmconfig1;

	if (wdev->famiwy == CHIP_KABINI || wdev->famiwy == CHIP_MUWWINS)
		wetuwn;

	if (pi->sys_info.nb_dpm_enabwe) {
		nbdpmconfig1 = WWEG32_SMC(NB_DPM_CONFIG_1);
		nbdpmconfig1 &= ~(Dpm0PgNbPsWo_MASK | Dpm0PgNbPsHi_MASK |
				  DpmXNbPsWo_MASK | DpmXNbPsHi_MASK);
		nbdpmconfig1 |= (Dpm0PgNbPsWo(new_ps->dpm0_pg_nb_ps_wo) |
				 Dpm0PgNbPsHi(new_ps->dpm0_pg_nb_ps_hi) |
				 DpmXNbPsWo(new_ps->dpmx_nb_ps_wo) |
				 DpmXNbPsHi(new_ps->dpmx_nb_ps_hi));
		WWEG32_SMC(NB_DPM_CONFIG_1, nbdpmconfig1);
	}
}

static int kv_set_thewmaw_tempewatuwe_wange(stwuct wadeon_device *wdev,
					    int min_temp, int max_temp)
{
	int wow_temp = 0 * 1000;
	int high_temp = 255 * 1000;
	u32 tmp;

	if (wow_temp < min_temp)
		wow_temp = min_temp;
	if (high_temp > max_temp)
		high_temp = max_temp;
	if (high_temp < wow_temp) {
		DWM_EWWOW("invawid thewmaw wange: %d - %d\n", wow_temp, high_temp);
		wetuwn -EINVAW;
	}

	tmp = WWEG32_SMC(CG_THEWMAW_INT_CTWW);
	tmp &= ~(DIG_THEWM_INTH_MASK | DIG_THEWM_INTW_MASK);
	tmp |= (DIG_THEWM_INTH(49 + (high_temp / 1000)) |
		DIG_THEWM_INTW(49 + (wow_temp / 1000)));
	WWEG32_SMC(CG_THEWMAW_INT_CTWW, tmp);

	wdev->pm.dpm.thewmaw.min_temp = wow_temp;
	wdev->pm.dpm.thewmaw.max_temp = high_temp;

	wetuwn 0;
}

union igp_info {
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO info;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V2 info_2;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V5 info_5;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V6 info_6;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V1_7 info_7;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V1_8 info_8;
};

static int kv_pawse_sys_info_tabwe(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct wadeon_mode_info *mode_info = &wdev->mode_info;
	int index = GetIndexIntoMastewTabwe(DATA, IntegwatedSystemInfo);
	union igp_info *igp_info;
	u8 fwev, cwev;
	u16 data_offset;
	int i;

	if (atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset)) {
		igp_info = (union igp_info *)(mode_info->atom_context->bios +
					      data_offset);

		if (cwev != 8) {
			DWM_EWWOW("Unsuppowted IGP tabwe: %d %d\n", fwev, cwev);
			wetuwn -EINVAW;
		}
		pi->sys_info.bootup_scwk = we32_to_cpu(igp_info->info_8.uwBootUpEngineCwock);
		pi->sys_info.bootup_uma_cwk = we32_to_cpu(igp_info->info_8.uwBootUpUMACwock);
		pi->sys_info.bootup_nb_vowtage_index =
			we16_to_cpu(igp_info->info_8.usBootUpNBVowtage);
		if (igp_info->info_8.ucHtcTmpWmt == 0)
			pi->sys_info.htc_tmp_wmt = 203;
		ewse
			pi->sys_info.htc_tmp_wmt = igp_info->info_8.ucHtcTmpWmt;
		if (igp_info->info_8.ucHtcHystWmt == 0)
			pi->sys_info.htc_hyst_wmt = 5;
		ewse
			pi->sys_info.htc_hyst_wmt = igp_info->info_8.ucHtcHystWmt;
		if (pi->sys_info.htc_tmp_wmt <= pi->sys_info.htc_hyst_wmt) {
			DWM_EWWOW("The htcTmpWmt shouwd be wawgew than htcHystWmt.\n");
		}

		if (we32_to_cpu(igp_info->info_8.uwSystemConfig) & (1 << 3))
			pi->sys_info.nb_dpm_enabwe = twue;
		ewse
			pi->sys_info.nb_dpm_enabwe = fawse;

		fow (i = 0; i < KV_NUM_NBPSTATES; i++) {
			pi->sys_info.nbp_memowy_cwock[i] =
				we32_to_cpu(igp_info->info_8.uwNbpStateMemcwkFweq[i]);
			pi->sys_info.nbp_n_cwock[i] =
				we32_to_cpu(igp_info->info_8.uwNbpStateNCwkFweq[i]);
		}
		if (we32_to_cpu(igp_info->info_8.uwGPUCapInfo) &
		    SYS_INFO_GPUCAPS__ENABEW_DFS_BYPASS)
			pi->caps_enabwe_dfs_bypass = twue;

		sumo_constwuct_scwk_vowtage_mapping_tabwe(wdev,
							  &pi->sys_info.scwk_vowtage_mapping_tabwe,
							  igp_info->info_8.sAvaiw_SCWK);

		sumo_constwuct_vid_mapping_tabwe(wdev,
						 &pi->sys_info.vid_mapping_tabwe,
						 igp_info->info_8.sAvaiw_SCWK);

		kv_constwuct_max_powew_wimits_tabwe(wdev,
						    &wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac);
	}
	wetuwn 0;
}

union powew_info {
	stwuct _ATOM_POWEWPWAY_INFO info;
	stwuct _ATOM_POWEWPWAY_INFO_V2 info_2;
	stwuct _ATOM_POWEWPWAY_INFO_V3 info_3;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE ppwib;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE2 ppwib2;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE3 ppwib3;
};

union ppwib_cwock_info {
	stwuct _ATOM_PPWIB_W600_CWOCK_INFO w600;
	stwuct _ATOM_PPWIB_WS780_CWOCK_INFO ws780;
	stwuct _ATOM_PPWIB_EVEWGWEEN_CWOCK_INFO evewgween;
	stwuct _ATOM_PPWIB_SUMO_CWOCK_INFO sumo;
};

union ppwib_powew_state {
	stwuct _ATOM_PPWIB_STATE v1;
	stwuct _ATOM_PPWIB_STATE_V2 v2;
};

static void kv_patch_boot_state(stwuct wadeon_device *wdev,
				stwuct kv_ps *ps)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	ps->num_wevews = 1;
	ps->wevews[0] = pi->boot_pw;
}

static void kv_pawse_ppwib_non_cwock_info(stwuct wadeon_device *wdev,
					  stwuct wadeon_ps *wps,
					  stwuct _ATOM_PPWIB_NONCWOCK_INFO *non_cwock_info,
					  u8 tabwe_wev)
{
	stwuct kv_ps *ps = kv_get_ps(wps);

	wps->caps = we32_to_cpu(non_cwock_info->uwCapsAndSettings);
	wps->cwass = we16_to_cpu(non_cwock_info->usCwassification);
	wps->cwass2 = we16_to_cpu(non_cwock_info->usCwassification2);

	if (ATOM_PPWIB_NONCWOCKINFO_VEW1 < tabwe_wev) {
		wps->vcwk = we32_to_cpu(non_cwock_info->uwVCWK);
		wps->dcwk = we32_to_cpu(non_cwock_info->uwDCWK);
	} ewse {
		wps->vcwk = 0;
		wps->dcwk = 0;
	}

	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_BOOT) {
		wdev->pm.dpm.boot_ps = wps;
		kv_patch_boot_state(wdev, ps);
	}
	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_UVDSTATE)
		wdev->pm.dpm.uvd_ps = wps;
}

static void kv_pawse_ppwib_cwock_info(stwuct wadeon_device *wdev,
				      stwuct wadeon_ps *wps, int index,
					union ppwib_cwock_info *cwock_info)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct kv_ps *ps = kv_get_ps(wps);
	stwuct kv_pw *pw = &ps->wevews[index];
	u32 scwk;

	scwk = we16_to_cpu(cwock_info->sumo.usEngineCwockWow);
	scwk |= cwock_info->sumo.ucEngineCwockHigh << 16;
	pw->scwk = scwk;
	pw->vddc_index = cwock_info->sumo.vddcIndex;

	ps->num_wevews = index + 1;

	if (pi->caps_scwk_ds) {
		pw->ds_dividew_index = 5;
		pw->ss_dividew_index = 5;
	}
}

static int kv_pawse_powew_tabwe(stwuct wadeon_device *wdev)
{
	stwuct wadeon_mode_info *mode_info = &wdev->mode_info;
	stwuct _ATOM_PPWIB_NONCWOCK_INFO *non_cwock_info;
	union ppwib_powew_state *powew_state;
	int i, j, k, non_cwock_awway_index, cwock_awway_index;
	union ppwib_cwock_info *cwock_info;
	stwuct _StateAwway *state_awway;
	stwuct _CwockInfoAwway *cwock_info_awway;
	stwuct _NonCwockInfoAwway *non_cwock_info_awway;
	union powew_info *powew_info;
	int index = GetIndexIntoMastewTabwe(DATA, PowewPwayInfo);
	u16 data_offset;
	u8 fwev, cwev;
	u8 *powew_state_offset;
	stwuct kv_ps *ps;

	if (!atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset))
		wetuwn -EINVAW;
	powew_info = (union powew_info *)(mode_info->atom_context->bios + data_offset);

	state_awway = (stwuct _StateAwway *)
		(mode_info->atom_context->bios + data_offset +
		 we16_to_cpu(powew_info->ppwib.usStateAwwayOffset));
	cwock_info_awway = (stwuct _CwockInfoAwway *)
		(mode_info->atom_context->bios + data_offset +
		 we16_to_cpu(powew_info->ppwib.usCwockInfoAwwayOffset));
	non_cwock_info_awway = (stwuct _NonCwockInfoAwway *)
		(mode_info->atom_context->bios + data_offset +
		 we16_to_cpu(powew_info->ppwib.usNonCwockInfoAwwayOffset));

	wdev->pm.dpm.ps = kcawwoc(state_awway->ucNumEntwies,
				  sizeof(stwuct wadeon_ps),
				  GFP_KEWNEW);
	if (!wdev->pm.dpm.ps)
		wetuwn -ENOMEM;
	powew_state_offset = (u8 *)state_awway->states;
	fow (i = 0; i < state_awway->ucNumEntwies; i++) {
		u8 *idx;
		powew_state = (union ppwib_powew_state *)powew_state_offset;
		non_cwock_awway_index = powew_state->v2.nonCwockInfoIndex;
		non_cwock_info = (stwuct _ATOM_PPWIB_NONCWOCK_INFO *)
			&non_cwock_info_awway->nonCwockInfo[non_cwock_awway_index];
		if (!wdev->pm.powew_state[i].cwock_info)
			wetuwn -EINVAW;
		ps = kzawwoc(sizeof(stwuct kv_ps), GFP_KEWNEW);
		if (ps == NUWW) {
			kfwee(wdev->pm.dpm.ps);
			wetuwn -ENOMEM;
		}
		wdev->pm.dpm.ps[i].ps_pwiv = ps;
		k = 0;
		idx = (u8 *)&powew_state->v2.cwockInfoIndex[0];
		fow (j = 0; j < powew_state->v2.ucNumDPMWevews; j++) {
			cwock_awway_index = idx[j];
			if (cwock_awway_index >= cwock_info_awway->ucNumEntwies)
				continue;
			if (k >= SUMO_MAX_HAWDWAWE_POWEWWEVEWS)
				bweak;
			cwock_info = (union ppwib_cwock_info *)
				((u8 *)&cwock_info_awway->cwockInfo[0] +
				 (cwock_awway_index * cwock_info_awway->ucEntwySize));
			kv_pawse_ppwib_cwock_info(wdev,
						  &wdev->pm.dpm.ps[i], k,
						  cwock_info);
			k++;
		}
		kv_pawse_ppwib_non_cwock_info(wdev, &wdev->pm.dpm.ps[i],
					      non_cwock_info,
					      non_cwock_info_awway->ucEntwySize);
		powew_state_offset += 2 + powew_state->v2.ucNumDPMWevews;
	}
	wdev->pm.dpm.num_ps = state_awway->ucNumEntwies;

	/* fiww in the vce powew states */
	fow (i = 0; i < WADEON_MAX_VCE_WEVEWS; i++) {
		u32 scwk;
		cwock_awway_index = wdev->pm.dpm.vce_states[i].cwk_idx;
		cwock_info = (union ppwib_cwock_info *)
			&cwock_info_awway->cwockInfo[cwock_awway_index * cwock_info_awway->ucEntwySize];
		scwk = we16_to_cpu(cwock_info->sumo.usEngineCwockWow);
		scwk |= cwock_info->sumo.ucEngineCwockHigh << 16;
		wdev->pm.dpm.vce_states[i].scwk = scwk;
		wdev->pm.dpm.vce_states[i].mcwk = 0;
	}

	wetuwn 0;
}

int kv_dpm_init(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi;
	int wet, i;

	pi = kzawwoc(sizeof(stwuct kv_powew_info), GFP_KEWNEW);
	if (pi == NUWW)
		wetuwn -ENOMEM;
	wdev->pm.dpm.pwiv = pi;

	wet = w600_get_pwatfowm_caps(wdev);
	if (wet)
		wetuwn wet;

	wet = w600_pawse_extended_powew_tabwe(wdev);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < SUMO_MAX_HAWDWAWE_POWEWWEVEWS; i++)
		pi->at[i] = TWINITY_AT_DFWT;

	pi->swam_end = SMC_WAM_END;

	/* Enabwing nb dpm on an aswock system pwevents dpm fwom wowking */
	if (wdev->pdev->subsystem_vendow == 0x1849)
		pi->enabwe_nb_dpm = fawse;
	ewse
		pi->enabwe_nb_dpm = twue;

	pi->caps_powew_containment = twue;
	pi->caps_cac = twue;
	pi->enabwe_didt = fawse;
	if (pi->enabwe_didt) {
		pi->caps_sq_wamping = twue;
		pi->caps_db_wamping = twue;
		pi->caps_td_wamping = twue;
		pi->caps_tcp_wamping = twue;
	}

	pi->caps_scwk_ds = twue;
	pi->enabwe_auto_thewmaw_thwottwing = twue;
	pi->disabwe_nb_ps3_in_battewy = fawse;
	if (wadeon_bapm == -1) {
		/* onwy enabwe bapm on KB, MW by defauwt */
		if (wdev->famiwy == CHIP_KABINI || wdev->famiwy == CHIP_MUWWINS)
			pi->bapm_enabwe = twue;
		ewse
			pi->bapm_enabwe = fawse;
	} ewse if (wadeon_bapm == 0) {
		pi->bapm_enabwe = fawse;
	} ewse {
		pi->bapm_enabwe = twue;
	}
	pi->vowtage_dwop_t = 0;
	pi->caps_scwk_thwottwe_wow_notification = fawse;
	pi->caps_fps = fawse; /* twue? */
	pi->caps_uvd_pg = twue;
	pi->caps_uvd_dpm = twue;
	pi->caps_vce_pg = fawse; /* XXX twue */
	pi->caps_samu_pg = fawse;
	pi->caps_acp_pg = fawse;
	pi->caps_stabwe_p_state = fawse;

	wet = kv_pawse_sys_info_tabwe(wdev);
	if (wet)
		wetuwn wet;

	kv_patch_vowtage_vawues(wdev);
	kv_constwuct_boot_state(wdev);

	wet = kv_pawse_powew_tabwe(wdev);
	if (wet)
		wetuwn wet;

	pi->enabwe_dpm = twue;

	wetuwn 0;
}

void kv_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						    stwuct seq_fiwe *m)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 cuwwent_index =
		(WWEG32_SMC(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWW_SCWK_INDEX_MASK) >>
		CUWW_SCWK_INDEX_SHIFT;
	u32 scwk, tmp;
	u16 vddc;

	if (cuwwent_index >= SMU__NUM_SCWK_DPM_STATE) {
		seq_pwintf(m, "invawid dpm pwofiwe %d\n", cuwwent_index);
	} ewse {
		scwk = be32_to_cpu(pi->gwaphics_wevew[cuwwent_index].ScwkFwequency);
		tmp = (WWEG32_SMC(SMU_VOWTAGE_STATUS) & SMU_VOWTAGE_CUWWENT_WEVEW_MASK) >>
			SMU_VOWTAGE_CUWWENT_WEVEW_SHIFT;
		vddc = kv_convewt_8bit_index_to_vowtage(wdev, (u16)tmp);
		seq_pwintf(m, "uvd    %sabwed\n", pi->uvd_powew_gated ? "dis" : "en");
		seq_pwintf(m, "vce    %sabwed\n", pi->vce_powew_gated ? "dis" : "en");
		seq_pwintf(m, "powew wevew %d    scwk: %u vddc: %u\n",
			   cuwwent_index, scwk, vddc);
	}
}

u32 kv_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	u32 cuwwent_index =
		(WWEG32_SMC(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWW_SCWK_INDEX_MASK) >>
		CUWW_SCWK_INDEX_SHIFT;
	u32 scwk;

	if (cuwwent_index >= SMU__NUM_SCWK_DPM_STATE) {
		wetuwn 0;
	} ewse {
		scwk = be32_to_cpu(pi->gwaphics_wevew[cuwwent_index].ScwkFwequency);
		wetuwn scwk;
	}
}

u32 kv_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	wetuwn pi->sys_info.bootup_uma_cwk;
}

void kv_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
			      stwuct wadeon_ps *wps)
{
	int i;
	stwuct kv_ps *ps = kv_get_ps(wps);

	w600_dpm_pwint_cwass_info(wps->cwass, wps->cwass2);
	w600_dpm_pwint_cap_info(wps->caps);
	pwintk("\tuvd    vcwk: %d dcwk: %d\n", wps->vcwk, wps->dcwk);
	fow (i = 0; i < ps->num_wevews; i++) {
		stwuct kv_pw *pw = &ps->wevews[i];
		pwintk("\t\tpowew wevew %d    scwk: %u vddc: %u\n",
		       i, pw->scwk,
		       kv_convewt_8bit_index_to_vowtage(wdev, pw->vddc_index));
	}
	w600_dpm_pwint_ps_status(wdev, wps);
}

void kv_dpm_fini(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < wdev->pm.dpm.num_ps; i++) {
		kfwee(wdev->pm.dpm.ps[i].ps_pwiv);
	}
	kfwee(wdev->pm.dpm.ps);
	kfwee(wdev->pm.dpm.pwiv);
	w600_fwee_extended_powew_tabwe(wdev);
}

void kv_dpm_dispway_configuwation_changed(stwuct wadeon_device *wdev)
{

}

u32 kv_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);
	stwuct kv_ps *wequested_state = kv_get_ps(&pi->wequested_wps);

	if (wow)
		wetuwn wequested_state->wevews[0].scwk;
	ewse
		wetuwn wequested_state->wevews[wequested_state->num_wevews - 1].scwk;
}

u32 kv_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct kv_powew_info *pi = kv_get_pi(wdev);

	wetuwn pi->sys_info.bootup_uma_cwk;
}

