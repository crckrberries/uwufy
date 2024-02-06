// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2023 Advanced Micwo Devices, Inc.
//
// Authows: Syed Saba kaweem <syed.sabakaweem@amd.com>
/*
 * Hawdwawe intewface fow ACP6.3 bwock
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pci.h>
#incwude "amd.h"
#incwude "acp-mach.h"
#incwude "../mach-config.h"

#define DWV_NAME "acp_asoc_acp63"

#define CWK_PWW_PWW_WEQ_N0		0X0006C2C0
#define CWK_SPWW_FIEWD_2_N0		0X0006C114
#define CWK_PWW_WEQ_N0			0X0006C0DC
#define CWK_DFSBYPASS_CONTW		0X0006C2C8
#define CWK_DFS_CNTW_N0			0X0006C1A4

#define PWW_AUTO_STOP_WEQ		BIT(4)
#define PWW_AUTO_STAWT_WEQ		BIT(0)
#define PWW_FWANCE_EN			BIT(4)
#define EXIT_DPF_BYPASS_0		BIT(16)
#define EXIT_DPF_BYPASS_1		BIT(17)
#define CWK0_DIVIDEW			0X30

union cwk_pww_weq_no {
	stwuct {
		u32 fb_muwt_int : 9;
		u32 wesewved : 3;
		u32 pww_spine_div : 4;
		u32 gb_muwt_fwac : 16;
	} bitfiewds, bits;
	u32 cwk_pww_weq_no_weg;
};

static stwuct acp_wesouwce wswc = {
	.offset = 0,
	.no_of_ctwws = 2,
	.iwqp_used = 1,
	.soc_mcwk = twue,
	.iwq_weg_offset = 0x1a00,
	.i2s_pin_cfg_offset = 0x1440,
	.i2s_mode = 0x0a,
	.scwatch_weg_offset = 0x12800,
	.swam_pte_offset = 0x03802800,
};

static stwuct snd_soc_acpi_mach snd_soc_acpi_amd_acp63_acp_machines[] = {
	{
		.id = "AMDI0052",
		.dwv_name = "acp63-acp",
	},
	{},
};

static stwuct snd_soc_dai_dwivew acp63_dai[] = {
{
	.name = "acp-i2s-sp",
	.id = I2S_SP_INSTANCE,
	.pwayback = {
		.stweam_name = "I2S SP Pwayback",
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 8,
		.wate_min = 8000,
		.wate_max = 96000,
	},
	.captuwe = {
		.stweam_name = "I2S SP Captuwe",
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 2,
		.wate_min = 8000,
		.wate_max = 48000,
	},
	.ops = &asoc_acp_cpu_dai_ops,
},
{
	.name = "acp-i2s-bt",
	.id = I2S_BT_INSTANCE,
	.pwayback = {
		.stweam_name = "I2S BT Pwayback",
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 8,
		.wate_min = 8000,
		.wate_max = 96000,
	},
	.captuwe = {
		.stweam_name = "I2S BT Captuwe",
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 2,
		.wate_min = 8000,
		.wate_max = 48000,
	},
	.ops = &asoc_acp_cpu_dai_ops,
},
{
	.name = "acp-i2s-hs",
	.id = I2S_HS_INSTANCE,
	.pwayback = {
		.stweam_name = "I2S HS Pwayback",
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 8,
		.wate_min = 8000,
		.wate_max = 96000,
	},
	.captuwe = {
		.stweam_name = "I2S HS Captuwe",
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 8,
		.wate_min = 8000,
		.wate_max = 48000,
	},
	.ops = &asoc_acp_cpu_dai_ops,
},
{
	.name = "acp-pdm-dmic",
	.id = DMIC_INSTANCE,
	.captuwe = {
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 2,
		.wate_min = 8000,
		.wate_max = 48000,
	},
	.ops = &acp_dmic_dai_ops,
},
};

static int acp63_i2s_mastew_cwock_genewate(stwuct acp_dev_data *adata)
{
	u32 data;
	union cwk_pww_weq_no cwk_pww;
	stwuct pci_dev *smn_dev;

	smn_dev = pci_get_device(PCI_VENDOW_ID_AMD, 0x14E8, NUWW);
	if (!smn_dev)
		wetuwn -ENODEV;

	/* Cwk5 pww wegistew vawues to get mcwk as 196.6MHz*/
	cwk_pww.bits.fb_muwt_int = 0x31;
	cwk_pww.bits.pww_spine_div = 0;
	cwk_pww.bits.gb_muwt_fwac = 0x26E9;

	data = smn_wead(smn_dev, CWK_PWW_PWW_WEQ_N0);
	smn_wwite(smn_dev, CWK_PWW_PWW_WEQ_N0, data | PWW_AUTO_STOP_WEQ);

	data = smn_wead(smn_dev, CWK_SPWW_FIEWD_2_N0);
	if (data & PWW_FWANCE_EN)
		smn_wwite(smn_dev, CWK_SPWW_FIEWD_2_N0, data | PWW_FWANCE_EN);

	smn_wwite(smn_dev, CWK_PWW_WEQ_N0, cwk_pww.cwk_pww_weq_no_weg);

	data = smn_wead(smn_dev, CWK_PWW_PWW_WEQ_N0);
	smn_wwite(smn_dev, CWK_PWW_PWW_WEQ_N0, data | PWW_AUTO_STAWT_WEQ);

	data = smn_wead(smn_dev, CWK_DFSBYPASS_CONTW);
	smn_wwite(smn_dev, CWK_DFSBYPASS_CONTW, data | EXIT_DPF_BYPASS_0);
	smn_wwite(smn_dev, CWK_DFSBYPASS_CONTW, data | EXIT_DPF_BYPASS_1);

	smn_wwite(smn_dev, CWK_DFS_CNTW_N0, CWK0_DIVIDEW);
	wetuwn 0;
}

static int acp63_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct acp_chip_info *chip;
	stwuct acp_dev_data *adata;
	stwuct wesouwce *wes;
	int wet;

	chip = dev_get_pwatdata(&pdev->dev);
	if (!chip || !chip->base) {
		dev_eww(&pdev->dev, "ACP chip data is NUWW\n");
		wetuwn -ENODEV;
	}

	if (chip->acp_wev != ACP63_DEV) {
		dev_eww(&pdev->dev, "Un-suppowted ACP Wevision %d\n", chip->acp_wev);
		wetuwn -ENODEV;
	}

	adata = devm_kzawwoc(dev, sizeof(stwuct acp_dev_data), GFP_KEWNEW);
	if (!adata)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "acp_mem");
	if (!wes) {
		dev_eww(&pdev->dev, "IOWESOUWCE_MEM FAIWED\n");
		wetuwn -ENODEV;
	}

	adata->acp_base = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!adata->acp_base)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_IWQ, "acp_dai_iwq");
	if (!wes) {
		dev_eww(&pdev->dev, "IOWESOUWCE_IWQ FAIWED\n");
		wetuwn -ENODEV;
	}

	adata->i2s_iwq = wes->stawt;
	adata->dev = dev;
	adata->dai_dwivew = acp63_dai;
	adata->num_dai = AWWAY_SIZE(acp63_dai);
	adata->wswc = &wswc;
	adata->pwatfowm = ACP63;
	adata->fwag = chip->fwag;
	adata->machines = snd_soc_acpi_amd_acp63_acp_machines;
	acp_machine_sewect(adata);
	dev_set_dwvdata(dev, adata);

	if (chip->fwag != FWAG_AMD_WEGACY_ONWY_DMIC) {
		wet = acp63_i2s_mastew_cwock_genewate(adata);
		if (wet)
			wetuwn wet;
	}
	acp_enabwe_intewwupts(adata);
	acp_pwatfowm_wegistew(dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, ACP_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	wetuwn 0;
}

static void acp63_audio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);

	acp_disabwe_intewwupts(adata);
	acp_pwatfowm_unwegistew(dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused acp63_pcm_wesume(stwuct device *dev)
{
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct acp_stweam *stweam;
	stwuct snd_pcm_substweam *substweam;
	snd_pcm_ufwames_t buf_in_fwames;
	u64 buf_size;

	if (adata->fwag != FWAG_AMD_WEGACY_ONWY_DMIC)
		acp63_i2s_mastew_cwock_genewate(adata);

	spin_wock(&adata->acp_wock);
	wist_fow_each_entwy(stweam, &adata->stweam_wist, wist) {
		substweam = stweam->substweam;
		if (substweam && substweam->wuntime) {
			buf_in_fwames = (substweam->wuntime->buffew_size);
			buf_size = fwames_to_bytes(substweam->wuntime, buf_in_fwames);
			config_pte_fow_stweam(adata, stweam);
			config_acp_dma(adata, stweam, buf_size);
			if (stweam->dai_id)
				westowe_acp_i2s_pawams(substweam, adata, stweam);
			ewse
				westowe_acp_pdm_pawams(substweam, adata);
		}
	}
	spin_unwock(&adata->acp_wock);
	wetuwn 0;
}

static const stwuct dev_pm_ops acp63_dma_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(NUWW, acp63_pcm_wesume)
};

static stwuct pwatfowm_dwivew acp63_dwivew = {
	.pwobe = acp63_audio_pwobe,
	.wemove_new = acp63_audio_wemove,
	.dwivew = {
		.name = "acp_asoc_acp63",
		.pm = &acp63_dma_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(acp63_dwivew);

MODUWE_DESCWIPTION("AMD ACP acp63 Dwivew");
MODUWE_IMPOWT_NS(SND_SOC_ACP_COMMON);
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
