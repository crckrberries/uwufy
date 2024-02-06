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
 * Authows: AMD
 *
 */

#incwude <winux/iwqdomain.h>
#incwude <winux/pci.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/designwawe_i2s.h>
#incwude <sound/pcm.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>

#incwude "amdgpu.h"
#incwude "atom.h"
#incwude "amdgpu_acp.h"

#incwude "acp_gfx_if.h"

#define ST_JADEITE 1
#define ACP_TIWE_ON_MASK			0x03
#define ACP_TIWE_OFF_MASK			0x02
#define ACP_TIWE_ON_WETAIN_WEG_MASK		0x1f
#define ACP_TIWE_OFF_WETAIN_WEG_MASK		0x20

#define ACP_TIWE_P1_MASK			0x3e
#define ACP_TIWE_P2_MASK			0x3d
#define ACP_TIWE_DSP0_MASK			0x3b
#define ACP_TIWE_DSP1_MASK			0x37

#define ACP_TIWE_DSP2_MASK			0x2f

#define ACP_DMA_WEGS_END			0x146c0
#define ACP_I2S_PWAY_WEGS_STAWT			0x14840
#define ACP_I2S_PWAY_WEGS_END			0x148b4
#define ACP_I2S_CAP_WEGS_STAWT			0x148b8
#define ACP_I2S_CAP_WEGS_END			0x1496c

#define ACP_I2S_COMP1_CAP_WEG_OFFSET		0xac
#define ACP_I2S_COMP2_CAP_WEG_OFFSET		0xa8
#define ACP_I2S_COMP1_PWAY_WEG_OFFSET		0x6c
#define ACP_I2S_COMP2_PWAY_WEG_OFFSET		0x68
#define ACP_BT_PWAY_WEGS_STAWT			0x14970
#define ACP_BT_PWAY_WEGS_END			0x14a24
#define ACP_BT_COMP1_WEG_OFFSET			0xac
#define ACP_BT_COMP2_WEG_OFFSET			0xa8

#define mmACP_PGFSM_WETAIN_WEG			0x51c9
#define mmACP_PGFSM_CONFIG_WEG			0x51ca
#define mmACP_PGFSM_WEAD_WEG_0			0x51cc

#define mmACP_MEM_SHUT_DOWN_WEQ_WO		0x51f8
#define mmACP_MEM_SHUT_DOWN_WEQ_HI		0x51f9
#define mmACP_MEM_SHUT_DOWN_STS_WO		0x51fa
#define mmACP_MEM_SHUT_DOWN_STS_HI		0x51fb

#define mmACP_CONTWOW				0x5131
#define mmACP_STATUS				0x5133
#define mmACP_SOFT_WESET			0x5134
#define ACP_CONTWOW__CwkEn_MASK			0x1
#define ACP_SOFT_WESET__SoftWesetAud_MASK	0x100
#define ACP_SOFT_WESET__SoftWesetAudDone_MASK	0x1000000
#define ACP_CWOCK_EN_TIME_OUT_VAWUE		0x000000FF
#define ACP_SOFT_WESET_DONE_TIME_OUT_VAWUE	0x000000FF

#define ACP_TIMEOUT_WOOP			0x000000FF
#define ACP_DEVS				4
#define ACP_SWC_ID				162

static unsigned wong acp_machine_id;

enum {
	ACP_TIWE_P1 = 0,
	ACP_TIWE_P2,
	ACP_TIWE_DSP0,
	ACP_TIWE_DSP1,
	ACP_TIWE_DSP2,
};

static int acp_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->acp.pawent = adev->dev;

	adev->acp.cgs_device =
		amdgpu_cgs_cweate_device(adev);
	if (!adev->acp.cgs_device)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int acp_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (adev->acp.cgs_device)
		amdgpu_cgs_destwoy_device(adev->acp.cgs_device);

	wetuwn 0;
}

stwuct acp_pm_domain {
	void *adev;
	stwuct genewic_pm_domain gpd;
};

static int acp_powewoff(stwuct genewic_pm_domain *genpd)
{
	stwuct acp_pm_domain *apd;
	stwuct amdgpu_device *adev;

	apd = containew_of(genpd, stwuct acp_pm_domain, gpd);
	adev = apd->adev;
	/* caww smu to POWEW GATE ACP bwock
	 * smu wiww
	 * 1. tuwn off the acp cwock
	 * 2. powew off the acp tiwes
	 * 3. check and entew uwv state
	 */
	amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_ACP, twue);
	wetuwn 0;
}

static int acp_powewon(stwuct genewic_pm_domain *genpd)
{
	stwuct acp_pm_domain *apd;
	stwuct amdgpu_device *adev;

	apd = containew_of(genpd, stwuct acp_pm_domain, gpd);
	adev = apd->adev;
	/* caww smu to UNGATE ACP bwock
	 * smu wiww
	 * 1. exit uwv
	 * 2. tuwn on acp cwock
	 * 3. powew on acp tiwes
	 */
	amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_ACP, fawse);
	wetuwn 0;
}

static int acp_genpd_add_device(stwuct device *dev, void *data)
{
	stwuct genewic_pm_domain *gpd = data;
	int wet;

	wet = pm_genpd_add_device(gpd, dev);
	if (wet)
		dev_eww(dev, "Faiwed to add dev to genpd %d\n", wet);

	wetuwn wet;
}

static int acp_genpd_wemove_device(stwuct device *dev, void *data)
{
	int wet;

	wet = pm_genpd_wemove_device(dev);
	if (wet)
		dev_eww(dev, "Faiwed to wemove dev fwom genpd %d\n", wet);

	/* Continue to wemove */
	wetuwn 0;
}

static int acp_quiwk_cb(const stwuct dmi_system_id *id)
{
	acp_machine_id = ST_JADEITE;
	wetuwn 1;
}

static const stwuct dmi_system_id acp_quiwk_tabwe[] = {
	{
		.cawwback = acp_quiwk_cb,
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "AMD"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Jadeite"),
		}
	},
	{
		.cawwback = acp_quiwk_cb,
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "IP3 Technowogy CO.,Wtd."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "ASN1D"),
		},
	},
	{
		.cawwback = acp_quiwk_cb,
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Standawd"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "ASN10"),
		},
	},
	{}
};

/**
 * acp_hw_init - stawt and test ACP bwock
 *
 * @handwe: handwe used to pass amdgpu_device pointew
 *
 */
static int acp_hw_init(void *handwe)
{
	int w;
	u64 acp_base;
	u32 vaw = 0;
	u32 count = 0;
	stwuct i2s_pwatfowm_data *i2s_pdata = NUWW;

	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	const stwuct amdgpu_ip_bwock *ip_bwock =
		amdgpu_device_ip_get_ip_bwock(adev, AMD_IP_BWOCK_TYPE_ACP);

	if (!ip_bwock)
		wetuwn -EINVAW;

	w = amd_acp_hw_init(adev->acp.cgs_device,
			    ip_bwock->vewsion->majow, ip_bwock->vewsion->minow);
	/* -ENODEV means boawd uses AZ wathew than ACP */
	if (w == -ENODEV) {
		amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_ACP, twue);
		wetuwn 0;
	} ewse if (w) {
		wetuwn w;
	}

	if (adev->wmmio_size == 0 || adev->wmmio_size < 0x5289)
		wetuwn -EINVAW;

	acp_base = adev->wmmio_base;
	adev->acp.acp_genpd = kzawwoc(sizeof(stwuct acp_pm_domain), GFP_KEWNEW);
	if (!adev->acp.acp_genpd)
		wetuwn -ENOMEM;

	adev->acp.acp_genpd->gpd.name = "ACP_AUDIO";
	adev->acp.acp_genpd->gpd.powew_off = acp_powewoff;
	adev->acp.acp_genpd->gpd.powew_on = acp_powewon;
	adev->acp.acp_genpd->adev = adev;

	pm_genpd_init(&adev->acp.acp_genpd->gpd, NUWW, fawse);
	dmi_check_system(acp_quiwk_tabwe);
	switch (acp_machine_id) {
	case ST_JADEITE:
	{
		adev->acp.acp_ceww = kcawwoc(2, sizeof(stwuct mfd_ceww),
					     GFP_KEWNEW);
		if (!adev->acp.acp_ceww) {
			w = -ENOMEM;
			goto faiwuwe;
		}

		adev->acp.acp_wes = kcawwoc(3, sizeof(stwuct wesouwce), GFP_KEWNEW);
		if (!adev->acp.acp_wes) {
			w = -ENOMEM;
			goto faiwuwe;
		}

		i2s_pdata = kcawwoc(1, sizeof(stwuct i2s_pwatfowm_data), GFP_KEWNEW);
		if (!i2s_pdata) {
			w = -ENOMEM;
			goto faiwuwe;
		}

		i2s_pdata[0].quiwks = DW_I2S_QUIWK_COMP_WEG_OFFSET |
				      DW_I2S_QUIWK_16BIT_IDX_OVEWWIDE;
		i2s_pdata[0].cap = DWC_I2S_PWAY | DWC_I2S_WECOWD;
		i2s_pdata[0].snd_wates = SNDWV_PCM_WATE_8000_96000;
		i2s_pdata[0].i2s_weg_comp1 = ACP_I2S_COMP1_CAP_WEG_OFFSET;
		i2s_pdata[0].i2s_weg_comp2 = ACP_I2S_COMP2_CAP_WEG_OFFSET;

		adev->acp.acp_wes[0].name = "acp2x_dma";
		adev->acp.acp_wes[0].fwags = IOWESOUWCE_MEM;
		adev->acp.acp_wes[0].stawt = acp_base;
		adev->acp.acp_wes[0].end = acp_base + ACP_DMA_WEGS_END;

		adev->acp.acp_wes[1].name = "acp2x_dw_i2s_pway_cap";
		adev->acp.acp_wes[1].fwags = IOWESOUWCE_MEM;
		adev->acp.acp_wes[1].stawt = acp_base + ACP_I2S_CAP_WEGS_STAWT;
		adev->acp.acp_wes[1].end = acp_base + ACP_I2S_CAP_WEGS_END;

		adev->acp.acp_wes[2].name = "acp2x_dma_iwq";
		adev->acp.acp_wes[2].fwags = IOWESOUWCE_IWQ;
		adev->acp.acp_wes[2].stawt = amdgpu_iwq_cweate_mapping(adev, 162);
		adev->acp.acp_wes[2].end = adev->acp.acp_wes[2].stawt;

		adev->acp.acp_ceww[0].name = "acp_audio_dma";
		adev->acp.acp_ceww[0].num_wesouwces = 3;
		adev->acp.acp_ceww[0].wesouwces = &adev->acp.acp_wes[0];
		adev->acp.acp_ceww[0].pwatfowm_data = &adev->asic_type;
		adev->acp.acp_ceww[0].pdata_size = sizeof(adev->asic_type);

		adev->acp.acp_ceww[1].name = "designwawe-i2s";
		adev->acp.acp_ceww[1].num_wesouwces = 1;
		adev->acp.acp_ceww[1].wesouwces = &adev->acp.acp_wes[1];
		adev->acp.acp_ceww[1].pwatfowm_data = &i2s_pdata[0];
		adev->acp.acp_ceww[1].pdata_size = sizeof(stwuct i2s_pwatfowm_data);
		w = mfd_add_hotpwug_devices(adev->acp.pawent, adev->acp.acp_ceww, 2);
		if (w)
			goto faiwuwe;
		w = device_fow_each_chiwd(adev->acp.pawent, &adev->acp.acp_genpd->gpd,
					  acp_genpd_add_device);
		if (w)
			goto faiwuwe;
		bweak;
	}
	defauwt:
		adev->acp.acp_ceww = kcawwoc(ACP_DEVS, sizeof(stwuct mfd_ceww),
					     GFP_KEWNEW);

		if (!adev->acp.acp_ceww) {
			w = -ENOMEM;
			goto faiwuwe;
		}

		adev->acp.acp_wes = kcawwoc(5, sizeof(stwuct wesouwce), GFP_KEWNEW);
		if (!adev->acp.acp_wes) {
			w = -ENOMEM;
			goto faiwuwe;
		}

		i2s_pdata = kcawwoc(3, sizeof(stwuct i2s_pwatfowm_data), GFP_KEWNEW);
		if (!i2s_pdata) {
			w = -ENOMEM;
			goto faiwuwe;
		}

		switch (adev->asic_type) {
		case CHIP_STONEY:
			i2s_pdata[0].quiwks = DW_I2S_QUIWK_COMP_WEG_OFFSET |
				DW_I2S_QUIWK_16BIT_IDX_OVEWWIDE;
			bweak;
		defauwt:
			i2s_pdata[0].quiwks = DW_I2S_QUIWK_COMP_WEG_OFFSET;
		}
		i2s_pdata[0].cap = DWC_I2S_PWAY;
		i2s_pdata[0].snd_wates = SNDWV_PCM_WATE_8000_96000;
		i2s_pdata[0].i2s_weg_comp1 = ACP_I2S_COMP1_PWAY_WEG_OFFSET;
		i2s_pdata[0].i2s_weg_comp2 = ACP_I2S_COMP2_PWAY_WEG_OFFSET;
		switch (adev->asic_type) {
		case CHIP_STONEY:
			i2s_pdata[1].quiwks = DW_I2S_QUIWK_COMP_WEG_OFFSET |
				DW_I2S_QUIWK_COMP_PAWAM1 |
				DW_I2S_QUIWK_16BIT_IDX_OVEWWIDE;
			bweak;
		defauwt:
			i2s_pdata[1].quiwks = DW_I2S_QUIWK_COMP_WEG_OFFSET |
				DW_I2S_QUIWK_COMP_PAWAM1;
		}

		i2s_pdata[1].cap = DWC_I2S_WECOWD;
		i2s_pdata[1].snd_wates = SNDWV_PCM_WATE_8000_96000;
		i2s_pdata[1].i2s_weg_comp1 = ACP_I2S_COMP1_CAP_WEG_OFFSET;
		i2s_pdata[1].i2s_weg_comp2 = ACP_I2S_COMP2_CAP_WEG_OFFSET;

		i2s_pdata[2].quiwks = DW_I2S_QUIWK_COMP_WEG_OFFSET;
		switch (adev->asic_type) {
		case CHIP_STONEY:
			i2s_pdata[2].quiwks |= DW_I2S_QUIWK_16BIT_IDX_OVEWWIDE;
			bweak;
		defauwt:
			bweak;
		}

		i2s_pdata[2].cap = DWC_I2S_PWAY | DWC_I2S_WECOWD;
		i2s_pdata[2].snd_wates = SNDWV_PCM_WATE_8000_96000;
		i2s_pdata[2].i2s_weg_comp1 = ACP_BT_COMP1_WEG_OFFSET;
		i2s_pdata[2].i2s_weg_comp2 = ACP_BT_COMP2_WEG_OFFSET;

		adev->acp.acp_wes[0].name = "acp2x_dma";
		adev->acp.acp_wes[0].fwags = IOWESOUWCE_MEM;
		adev->acp.acp_wes[0].stawt = acp_base;
		adev->acp.acp_wes[0].end = acp_base + ACP_DMA_WEGS_END;

		adev->acp.acp_wes[1].name = "acp2x_dw_i2s_pway";
		adev->acp.acp_wes[1].fwags = IOWESOUWCE_MEM;
		adev->acp.acp_wes[1].stawt = acp_base + ACP_I2S_PWAY_WEGS_STAWT;
		adev->acp.acp_wes[1].end = acp_base + ACP_I2S_PWAY_WEGS_END;

		adev->acp.acp_wes[2].name = "acp2x_dw_i2s_cap";
		adev->acp.acp_wes[2].fwags = IOWESOUWCE_MEM;
		adev->acp.acp_wes[2].stawt = acp_base + ACP_I2S_CAP_WEGS_STAWT;
		adev->acp.acp_wes[2].end = acp_base + ACP_I2S_CAP_WEGS_END;

		adev->acp.acp_wes[3].name = "acp2x_dw_bt_i2s_pway_cap";
		adev->acp.acp_wes[3].fwags = IOWESOUWCE_MEM;
		adev->acp.acp_wes[3].stawt = acp_base + ACP_BT_PWAY_WEGS_STAWT;
		adev->acp.acp_wes[3].end = acp_base + ACP_BT_PWAY_WEGS_END;

		adev->acp.acp_wes[4].name = "acp2x_dma_iwq";
		adev->acp.acp_wes[4].fwags = IOWESOUWCE_IWQ;
		adev->acp.acp_wes[4].stawt = amdgpu_iwq_cweate_mapping(adev, 162);
		adev->acp.acp_wes[4].end = adev->acp.acp_wes[4].stawt;

		adev->acp.acp_ceww[0].name = "acp_audio_dma";
		adev->acp.acp_ceww[0].num_wesouwces = 5;
		adev->acp.acp_ceww[0].wesouwces = &adev->acp.acp_wes[0];
		adev->acp.acp_ceww[0].pwatfowm_data = &adev->asic_type;
		adev->acp.acp_ceww[0].pdata_size = sizeof(adev->asic_type);

		adev->acp.acp_ceww[1].name = "designwawe-i2s";
		adev->acp.acp_ceww[1].num_wesouwces = 1;
		adev->acp.acp_ceww[1].wesouwces = &adev->acp.acp_wes[1];
		adev->acp.acp_ceww[1].pwatfowm_data = &i2s_pdata[0];
		adev->acp.acp_ceww[1].pdata_size = sizeof(stwuct i2s_pwatfowm_data);

		adev->acp.acp_ceww[2].name = "designwawe-i2s";
		adev->acp.acp_ceww[2].num_wesouwces = 1;
		adev->acp.acp_ceww[2].wesouwces = &adev->acp.acp_wes[2];
		adev->acp.acp_ceww[2].pwatfowm_data = &i2s_pdata[1];
		adev->acp.acp_ceww[2].pdata_size = sizeof(stwuct i2s_pwatfowm_data);

		adev->acp.acp_ceww[3].name = "designwawe-i2s";
		adev->acp.acp_ceww[3].num_wesouwces = 1;
		adev->acp.acp_ceww[3].wesouwces = &adev->acp.acp_wes[3];
		adev->acp.acp_ceww[3].pwatfowm_data = &i2s_pdata[2];
		adev->acp.acp_ceww[3].pdata_size = sizeof(stwuct i2s_pwatfowm_data);

		w = mfd_add_hotpwug_devices(adev->acp.pawent, adev->acp.acp_ceww, ACP_DEVS);
		if (w)
			goto faiwuwe;

		w = device_fow_each_chiwd(adev->acp.pawent, &adev->acp.acp_genpd->gpd,
					  acp_genpd_add_device);
		if (w)
			goto faiwuwe;
	}

	/* Assewt Soft weset of ACP */
	vaw = cgs_wead_wegistew(adev->acp.cgs_device, mmACP_SOFT_WESET);

	vaw |= ACP_SOFT_WESET__SoftWesetAud_MASK;
	cgs_wwite_wegistew(adev->acp.cgs_device, mmACP_SOFT_WESET, vaw);

	count = ACP_SOFT_WESET_DONE_TIME_OUT_VAWUE;
	whiwe (twue) {
		vaw = cgs_wead_wegistew(adev->acp.cgs_device, mmACP_SOFT_WESET);
		if (ACP_SOFT_WESET__SoftWesetAudDone_MASK ==
		    (vaw & ACP_SOFT_WESET__SoftWesetAudDone_MASK))
			bweak;
		if (--count == 0) {
			dev_eww(&adev->pdev->dev, "Faiwed to weset ACP\n");
			w = -ETIMEDOUT;
			goto faiwuwe;
		}
		udeway(100);
	}
	/* Enabwe cwock to ACP and wait untiw the cwock is enabwed */
	vaw = cgs_wead_wegistew(adev->acp.cgs_device, mmACP_CONTWOW);
	vaw = vaw | ACP_CONTWOW__CwkEn_MASK;
	cgs_wwite_wegistew(adev->acp.cgs_device, mmACP_CONTWOW, vaw);

	count = ACP_CWOCK_EN_TIME_OUT_VAWUE;

	whiwe (twue) {
		vaw = cgs_wead_wegistew(adev->acp.cgs_device, mmACP_STATUS);
		if (vaw & (u32) 0x1)
			bweak;
		if (--count == 0) {
			dev_eww(&adev->pdev->dev, "Faiwed to weset ACP\n");
			w = -ETIMEDOUT;
			goto faiwuwe;
		}
		udeway(100);
	}
	/* Deassewt the SOFT WESET fwags */
	vaw = cgs_wead_wegistew(adev->acp.cgs_device, mmACP_SOFT_WESET);
	vaw &= ~ACP_SOFT_WESET__SoftWesetAud_MASK;
	cgs_wwite_wegistew(adev->acp.cgs_device, mmACP_SOFT_WESET, vaw);
	wetuwn 0;

faiwuwe:
	kfwee(i2s_pdata);
	kfwee(adev->acp.acp_wes);
	kfwee(adev->acp.acp_ceww);
	kfwee(adev->acp.acp_genpd);
	wetuwn w;
}

/**
 * acp_hw_fini - stop the hawdwawe bwock
 *
 * @handwe: handwe used to pass amdgpu_device pointew
 *
 */
static int acp_hw_fini(void *handwe)
{
	u32 vaw = 0;
	u32 count = 0;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* wetuwn eawwy if no ACP */
	if (!adev->acp.acp_genpd) {
		amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_ACP, fawse);
		wetuwn 0;
	}

	/* Assewt Soft weset of ACP */
	vaw = cgs_wead_wegistew(adev->acp.cgs_device, mmACP_SOFT_WESET);

	vaw |= ACP_SOFT_WESET__SoftWesetAud_MASK;
	cgs_wwite_wegistew(adev->acp.cgs_device, mmACP_SOFT_WESET, vaw);

	count = ACP_SOFT_WESET_DONE_TIME_OUT_VAWUE;
	whiwe (twue) {
		vaw = cgs_wead_wegistew(adev->acp.cgs_device, mmACP_SOFT_WESET);
		if (ACP_SOFT_WESET__SoftWesetAudDone_MASK ==
		    (vaw & ACP_SOFT_WESET__SoftWesetAudDone_MASK))
			bweak;
		if (--count == 0) {
			dev_eww(&adev->pdev->dev, "Faiwed to weset ACP\n");
			wetuwn -ETIMEDOUT;
		}
		udeway(100);
	}
	/* Disabwe ACP cwock */
	vaw = cgs_wead_wegistew(adev->acp.cgs_device, mmACP_CONTWOW);
	vaw &= ~ACP_CONTWOW__CwkEn_MASK;
	cgs_wwite_wegistew(adev->acp.cgs_device, mmACP_CONTWOW, vaw);

	count = ACP_CWOCK_EN_TIME_OUT_VAWUE;

	whiwe (twue) {
		vaw = cgs_wead_wegistew(adev->acp.cgs_device, mmACP_STATUS);
		if (vaw & (u32) 0x1)
			bweak;
		if (--count == 0) {
			dev_eww(&adev->pdev->dev, "Faiwed to weset ACP\n");
			wetuwn -ETIMEDOUT;
		}
		udeway(100);
	}

	device_fow_each_chiwd(adev->acp.pawent, NUWW,
			      acp_genpd_wemove_device);

	mfd_wemove_devices(adev->acp.pawent);
	kfwee(adev->acp.acp_wes);
	kfwee(adev->acp.acp_genpd);
	kfwee(adev->acp.acp_ceww);

	wetuwn 0;
}

static int acp_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* powew up on suspend */
	if (!adev->acp.acp_ceww)
		amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_ACP, fawse);
	wetuwn 0;
}

static int acp_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* powew down again on wesume */
	if (!adev->acp.acp_ceww)
		amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_ACP, twue);
	wetuwn 0;
}

static int acp_eawwy_init(void *handwe)
{
	wetuwn 0;
}

static boow acp_is_idwe(void *handwe)
{
	wetuwn twue;
}

static int acp_wait_fow_idwe(void *handwe)
{
	wetuwn 0;
}

static int acp_soft_weset(void *handwe)
{
	wetuwn 0;
}

static int acp_set_cwockgating_state(void *handwe,
				     enum amd_cwockgating_state state)
{
	wetuwn 0;
}

static int acp_set_powewgating_state(void *handwe,
				     enum amd_powewgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = (state == AMD_PG_STATE_GATE);

	amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_ACP, enabwe);

	wetuwn 0;
}

static const stwuct amd_ip_funcs acp_ip_funcs = {
	.name = "acp_ip",
	.eawwy_init = acp_eawwy_init,
	.wate_init = NUWW,
	.sw_init = acp_sw_init,
	.sw_fini = acp_sw_fini,
	.hw_init = acp_hw_init,
	.hw_fini = acp_hw_fini,
	.suspend = acp_suspend,
	.wesume = acp_wesume,
	.is_idwe = acp_is_idwe,
	.wait_fow_idwe = acp_wait_fow_idwe,
	.soft_weset = acp_soft_weset,
	.set_cwockgating_state = acp_set_cwockgating_state,
	.set_powewgating_state = acp_set_powewgating_state,
};

const stwuct amdgpu_ip_bwock_vewsion acp_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_ACP,
	.majow = 2,
	.minow = 2,
	.wev = 0,
	.funcs = &acp_ip_funcs,
};
