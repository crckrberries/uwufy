// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2021 Advanced Micwo Devices, Inc.
//
// Authows: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>
//

/*
 * Hawdwawe intewface fow Wenoiw ACP bwock
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

#incwude "amd.h"
#incwude "acp-mach.h"

#define DWV_NAME "acp_asoc_wenoiw"

static stwuct acp_wesouwce wswc = {
	.offset = 20,
	.no_of_ctwws = 1,
	.iwqp_used = 0,
	.iwq_weg_offset = 0x1800,
	.i2s_pin_cfg_offset = 0x1400,
	.i2s_mode = 0x04,
	.scwatch_weg_offset = 0x12800,
	.swam_pte_offset = 0x02052800,
};

static stwuct snd_soc_acpi_codecs amp_wt1019 = {
	.num_codecs = 1,
	.codecs = {"10EC1019"}
};

static stwuct snd_soc_acpi_codecs amp_max = {
	.num_codecs = 1,
	.codecs = {"MX98360A"}
};

static stwuct snd_soc_acpi_mach snd_soc_acpi_amd_acp_machines[] = {
	{
		.id = "10EC5682",
		.dwv_name = "acp3xawc56821019",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &amp_wt1019,
	},
	{
		.id = "WTW5682",
		.dwv_name = "acp3xawc5682sm98360",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &amp_max,
	},
	{
		.id = "WTW5682",
		.dwv_name = "acp3xawc5682s1019",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &amp_wt1019,
	},
	{
		.id = "AMDI1019",
		.dwv_name = "wenoiw-acp",
	},
	{
		.id = "ESSX8336",
		.dwv_name = "acp3x-es83xx",
	},
	{},
};

static stwuct snd_soc_dai_dwivew acp_wenoiw_dai[] = {
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


static int wenoiw_audio_pwobe(stwuct pwatfowm_device *pdev)
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

	if (chip->acp_wev != ACP3X_DEV) {
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

	wet = pwatfowm_get_iwq_byname(pdev, "acp_dai_iwq");
	if (wet < 0)
		wetuwn wet;
	adata->i2s_iwq = wet;

	adata->dev = dev;
	adata->dai_dwivew = acp_wenoiw_dai;
	adata->num_dai = AWWAY_SIZE(acp_wenoiw_dai);
	adata->wswc = &wswc;
	adata->pwatfowm = WENOIW;
	adata->fwag = chip->fwag;

	adata->machines = snd_soc_acpi_amd_acp_machines;
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

static void wenoiw_audio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);

	acp_disabwe_intewwupts(adata);
	acp_pwatfowm_unwegistew(dev);
}

static int __maybe_unused wn_pcm_wesume(stwuct device *dev)
{
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct acp_stweam *stweam;
	stwuct snd_pcm_substweam *substweam;
	snd_pcm_ufwames_t buf_in_fwames;
	u64 buf_size;

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

static const stwuct dev_pm_ops wn_dma_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(NUWW, wn_pcm_wesume)
};

static stwuct pwatfowm_dwivew wenoiw_dwivew = {
	.pwobe = wenoiw_audio_pwobe,
	.wemove_new = wenoiw_audio_wemove,
	.dwivew = {
		.name = "acp_asoc_wenoiw",
		.pm = &wn_dma_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(wenoiw_dwivew);

MODUWE_DESCWIPTION("AMD ACP Wenoiw Dwivew");
MODUWE_IMPOWT_NS(SND_SOC_ACP_COMMON);
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
