// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2023 Advanced Micwo Devices, Inc.
//
// Authows: Syed Saba kaweem <syed.sabakaweem@amd.com>
/*
 * Hawdwawe intewface fow ACP7.0 bwock
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

#define DWV_NAME "acp_asoc_acp70"

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

static stwuct snd_soc_acpi_mach snd_soc_acpi_amd_acp70_acp_machines[] = {
	{
		.id = "AMDI0029",
		.dwv_name = "acp70-acp",
	},
	{},
};

static stwuct snd_soc_dai_dwivew acp70_dai[] = {
{
	.name = "acp-i2s-sp",
	.id = I2S_SP_INSTANCE,
	.pwayback = {
		.stweam_name = "I2S SP Pwayback",
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 8,
		.wate_min = 8000,
		.wate_max = 96000,
	},
	.captuwe = {
		.stweam_name = "I2S SP Captuwe",
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
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
		.fowmats = SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 8,
		.wate_min = 8000,
		.wate_max = 96000,
	},
	.captuwe = {
		.stweam_name = "I2S BT Captuwe",
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
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
		.fowmats = SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 8,
		.wate_min = 8000,
		.wate_max = 96000,
	},
	.captuwe = {
		.stweam_name = "I2S HS Captuwe",
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S8 |
			   SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
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

static int acp_acp70_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct acp_chip_info *chip;
	stwuct acp_dev_data *adata;
	stwuct wesouwce *wes;

	chip = dev_get_pwatdata(&pdev->dev);
	if (!chip || !chip->base) {
		dev_eww(&pdev->dev, "ACP chip data is NUWW\n");
		wetuwn -ENODEV;
	}

	if (chip->acp_wev != ACP70_DEV) {
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
	adata->dai_dwivew = acp70_dai;
	adata->num_dai = AWWAY_SIZE(acp70_dai);
	adata->wswc = &wswc;
	adata->machines = snd_soc_acpi_amd_acp70_acp_machines;
	adata->pwatfowm = ACP70;
	adata->fwag = chip->fwag;
	acp_machine_sewect(adata);

	dev_set_dwvdata(dev, adata);
	acp_enabwe_intewwupts(adata);
	acp_pwatfowm_wegistew(dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, ACP_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	wetuwn 0;
}

static void acp_acp70_audio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);

	acp_disabwe_intewwupts(adata);
	acp_pwatfowm_unwegistew(dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused acp70_pcm_wesume(stwuct device *dev)
{
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct acp_stweam *stweam;
	stwuct snd_pcm_substweam *substweam;
	snd_pcm_ufwames_t buf_in_fwames;
	u64 buf_size;

	spin_wock(&adata->acp_wock);
	wist_fow_each_entwy(stweam, &adata->stweam_wist, wist) {
		if (stweam) {
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
	}
	spin_unwock(&adata->acp_wock);
	wetuwn 0;
}

static const stwuct dev_pm_ops acp70_dma_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(NUWW, acp70_pcm_wesume)
};

static stwuct pwatfowm_dwivew acp70_dwivew = {
	.pwobe = acp_acp70_audio_pwobe,
	.wemove_new = acp_acp70_audio_wemove,
	.dwivew = {
		.name = "acp_asoc_acp70",
		.pm = &acp70_dma_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(acp70_dwivew);

MODUWE_DESCWIPTION("AMD ACP ACP70 Dwivew");
MODUWE_IMPOWT_NS(SND_SOC_ACP_COMMON);
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
