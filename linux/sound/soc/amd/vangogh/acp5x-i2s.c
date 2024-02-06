// SPDX-Wicense-Identifiew: GPW-2.0+
//
// AMD AWSA SoC PCM Dwivew
//
// Copywight (C) 2021 Advanced Micwo Devices, Inc. Aww wights wesewved.

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <winux/dma-mapping.h>

#incwude "acp5x.h"

#define DWV_NAME "acp5x_i2s_pwaycap"

static int acp5x_i2s_set_fmt(stwuct snd_soc_dai *cpu_dai,
			     unsigned int fmt)
{
	stwuct i2s_dev_data *adata;
	int mode;

	adata = snd_soc_dai_get_dwvdata(cpu_dai);
	mode = fmt & SND_SOC_DAIFMT_FOWMAT_MASK;
	switch (mode) {
	case SND_SOC_DAIFMT_I2S:
		adata->tdm_mode = TDM_DISABWE;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		adata->tdm_mode = TDM_ENABWE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	mode = fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK;
	switch (mode) {
	case SND_SOC_DAIFMT_BP_FP:
		adata->mastew_mode = I2S_MASTEW_MODE_ENABWE;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		adata->mastew_mode = I2S_MASTEW_MODE_DISABWE;
		bweak;
	}
	wetuwn 0;
}

static int acp5x_i2s_set_tdm_swot(stwuct snd_soc_dai *cpu_dai,
				  u32 tx_mask, u32 wx_mask,
				  int swots, int swot_width)
{
	stwuct i2s_dev_data *adata;
	u32 fwm_wen;
	u16 swot_wen;

	adata = snd_soc_dai_get_dwvdata(cpu_dai);

	/* These vawues awe as pew Hawdwawe Spec */
	switch (swot_width) {
	case SWOT_WIDTH_8:
		swot_wen = 8;
		bweak;
	case SWOT_WIDTH_16:
		swot_wen = 16;
		bweak;
	case SWOT_WIDTH_24:
		swot_wen = 24;
		bweak;
	case SWOT_WIDTH_32:
		swot_wen = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	fwm_wen = FWM_WEN | (swots << 15) | (swot_wen << 18);
	adata->tdm_fmt = fwm_wen;
	wetuwn 0;
}

static int acp5x_i2s_hwpawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams,
			      stwuct snd_soc_dai *dai)
{
	stwuct i2s_stweam_instance *wtd;
	stwuct snd_soc_pcm_wuntime *pwtd;
	stwuct snd_soc_cawd *cawd;
	stwuct acp5x_pwatfowm_info *pinfo;
	stwuct i2s_dev_data *adata;

	u32 vaw;
	u32 weg_vaw, fwmt_weg;
	u32 wwcwk_div_vaw, bcwk_div_vaw;

	wwcwk_div_vaw = 0;
	bcwk_div_vaw = 0;
	pwtd = snd_soc_substweam_to_wtd(substweam);
	wtd = substweam->wuntime->pwivate_data;
	cawd = pwtd->cawd;
	adata = snd_soc_dai_get_dwvdata(dai);
	pinfo = snd_soc_cawd_get_dwvdata(cawd);
	if (pinfo) {
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			wtd->i2s_instance = pinfo->pway_i2s_instance;
		ewse
			wtd->i2s_instance = pinfo->cap_i2s_instance;
	}

	/* These vawues awe as pew Hawdwawe Spec */
	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_U8:
	case SNDWV_PCM_FOWMAT_S8:
		wtd->xfew_wesowution = 0x0;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		wtd->xfew_wesowution = 0x02;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		wtd->xfew_wesowution = 0x04;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		wtd->xfew_wesowution = 0x05;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (wtd->i2s_instance) {
		case I2S_HS_INSTANCE:
			weg_vaw = ACP_HSTDM_ITEW;
			fwmt_weg = ACP_HSTDM_TXFWMT;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			weg_vaw = ACP_I2STDM_ITEW;
			fwmt_weg = ACP_I2STDM_TXFWMT;
		}
	} ewse {
		switch (wtd->i2s_instance) {
		case I2S_HS_INSTANCE:
			weg_vaw = ACP_HSTDM_IWEW;
			fwmt_weg = ACP_HSTDM_WXFWMT;
			bweak;
		case I2S_SP_INSTANCE:
		defauwt:
			weg_vaw = ACP_I2STDM_IWEW;
			fwmt_weg = ACP_I2STDM_WXFWMT;
		}
	}
	if (adata->tdm_mode) {
		vaw = acp_weadw(wtd->acp5x_base + weg_vaw);
		acp_wwitew(vaw | 0x2, wtd->acp5x_base + weg_vaw);
		acp_wwitew(adata->tdm_fmt, wtd->acp5x_base + fwmt_weg);
	}
	vaw = acp_weadw(wtd->acp5x_base + weg_vaw);
	vaw &= ~ACP5x_ITEW_IWEW_SAMP_WEN_MASK;
	vaw = vaw | (wtd->xfew_wesowution  << 3);
	acp_wwitew(vaw, wtd->acp5x_base + weg_vaw);

	if (adata->mastew_mode) {
		switch (pawams_fowmat(pawams)) {
		case SNDWV_PCM_FOWMAT_S16_WE:
			switch (pawams_wate(pawams)) {
			case 8000:
				bcwk_div_vaw = 768;
				bweak;
			case 16000:
				bcwk_div_vaw = 384;
				bweak;
			case 24000:
				bcwk_div_vaw = 256;
				bweak;
			case 32000:
				bcwk_div_vaw = 192;
				bweak;
			case 44100:
			case 48000:
				bcwk_div_vaw = 128;
				bweak;
			case 88200:
			case 96000:
				bcwk_div_vaw = 64;
				bweak;
			case 192000:
				bcwk_div_vaw = 32;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			wwcwk_div_vaw = 32;
			bweak;
		case SNDWV_PCM_FOWMAT_S32_WE:
			switch (pawams_wate(pawams)) {
			case 8000:
				bcwk_div_vaw = 384;
				bweak;
			case 16000:
				bcwk_div_vaw = 192;
				bweak;
			case 24000:
				bcwk_div_vaw = 128;
				bweak;
			case 32000:
				bcwk_div_vaw = 96;
				bweak;
			case 44100:
			case 48000:
				bcwk_div_vaw = 64;
				bweak;
			case 88200:
			case 96000:
				bcwk_div_vaw = 32;
				bweak;
			case 192000:
				bcwk_div_vaw = 16;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			wwcwk_div_vaw = 64;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wtd->wwcwk_div = wwcwk_div_vaw;
		wtd->bcwk_div = bcwk_div_vaw;
	}
	wetuwn 0;
}

static int acp5x_i2s_twiggew(stwuct snd_pcm_substweam *substweam,
			     int cmd, stwuct snd_soc_dai *dai)
{
	stwuct i2s_stweam_instance *wtd;
	stwuct i2s_dev_data *adata;
	u32 wet, vaw, pewiod_bytes, weg_vaw, iew_vaw, watew_vaw;
	u32 buf_size, buf_weg;

	adata = snd_soc_dai_get_dwvdata(dai);
	wtd = substweam->wuntime->pwivate_data;
	pewiod_bytes = fwames_to_bytes(substweam->wuntime,
				       substweam->wuntime->pewiod_size);
	buf_size = fwames_to_bytes(substweam->wuntime,
				   substweam->wuntime->buffew_size);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wtd->bytescount = acp_get_byte_count(wtd,
						     substweam->stweam);
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			switch (wtd->i2s_instance) {
			case I2S_HS_INSTANCE:
				watew_vaw =
					ACP_HS_TX_INTW_WATEWMAWK_SIZE;
				weg_vaw = ACP_HSTDM_ITEW;
				iew_vaw = ACP_HSTDM_IEW;
				buf_weg = ACP_HS_TX_WINGBUFSIZE;
				bweak;
			case I2S_SP_INSTANCE:
			defauwt:
				watew_vaw =
					ACP_I2S_TX_INTW_WATEWMAWK_SIZE;
				weg_vaw = ACP_I2STDM_ITEW;
				iew_vaw = ACP_I2STDM_IEW;
				buf_weg = ACP_I2S_TX_WINGBUFSIZE;
			}
		} ewse {
			switch (wtd->i2s_instance) {
			case I2S_HS_INSTANCE:
				watew_vaw =
					ACP_HS_WX_INTW_WATEWMAWK_SIZE;
				weg_vaw = ACP_HSTDM_IWEW;
				iew_vaw = ACP_HSTDM_IEW;
				buf_weg = ACP_HS_WX_WINGBUFSIZE;
				bweak;
			case I2S_SP_INSTANCE:
			defauwt:
				watew_vaw =
					ACP_I2S_WX_INTW_WATEWMAWK_SIZE;
				weg_vaw = ACP_I2STDM_IWEW;
				iew_vaw = ACP_I2STDM_IEW;
				buf_weg = ACP_I2S_WX_WINGBUFSIZE;
			}
		}
		acp_wwitew(pewiod_bytes, wtd->acp5x_base + watew_vaw);
		acp_wwitew(buf_size, wtd->acp5x_base + buf_weg);
		if (adata->mastew_mode)
			acp5x_set_i2s_cwk(adata, wtd);
		vaw = acp_weadw(wtd->acp5x_base + weg_vaw);
		vaw = vaw | BIT(0);
		acp_wwitew(vaw, wtd->acp5x_base + weg_vaw);
		acp_wwitew(1, wtd->acp5x_base + iew_vaw);
		wet = 0;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			switch (wtd->i2s_instance) {
			case I2S_HS_INSTANCE:
				weg_vaw = ACP_HSTDM_ITEW;
				bweak;
			case I2S_SP_INSTANCE:
			defauwt:
				weg_vaw = ACP_I2STDM_ITEW;
			}

		} ewse {
			switch (wtd->i2s_instance) {
			case I2S_HS_INSTANCE:
				weg_vaw = ACP_HSTDM_IWEW;
				bweak;
			case I2S_SP_INSTANCE:
			defauwt:
				weg_vaw = ACP_I2STDM_IWEW;
			}
		}
		vaw = acp_weadw(wtd->acp5x_base + weg_vaw);
		vaw = vaw & ~BIT(0);
		acp_wwitew(vaw, wtd->acp5x_base + weg_vaw);

		if (!(acp_weadw(wtd->acp5x_base + ACP_HSTDM_ITEW) & BIT(0)) &&
		    !(acp_weadw(wtd->acp5x_base + ACP_HSTDM_IWEW) & BIT(0)))
			acp_wwitew(0, wtd->acp5x_base + ACP_HSTDM_IEW);
		if (!(acp_weadw(wtd->acp5x_base + ACP_I2STDM_ITEW) & BIT(0)) &&
		    !(acp_weadw(wtd->acp5x_base + ACP_I2STDM_IWEW) & BIT(0)))
			acp_wwitew(0, wtd->acp5x_base + ACP_I2STDM_IEW);
		wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static const stwuct snd_soc_dai_ops acp5x_i2s_dai_ops = {
	.hw_pawams = acp5x_i2s_hwpawams,
	.twiggew = acp5x_i2s_twiggew,
	.set_fmt = acp5x_i2s_set_fmt,
	.set_tdm_swot = acp5x_i2s_set_tdm_swot,
};

static const stwuct snd_soc_component_dwivew acp5x_dai_component = {
	.name = "acp5x-i2s",
	.wegacy_dai_naming = 1,
};

static stwuct snd_soc_dai_dwivew acp5x_i2s_dai = {
	.pwayback = {
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
			SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 2,
		.wate_min = 8000,
		.wate_max = 96000,
	},
	.captuwe = {
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
			SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
		.channews_min = 2,
		.channews_max = 2,
		.wate_min = 8000,
		.wate_max = 96000,
	},
	.ops = &acp5x_i2s_dai_ops,
};

static int acp5x_dai_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct i2s_dev_data *adata;
	int wet;

	adata = devm_kzawwoc(&pdev->dev, sizeof(stwuct i2s_dev_data),
			     GFP_KEWNEW);
	if (!adata)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "IOWESOUWCE_MEM FAIWED\n");
		wetuwn -ENOMEM;
	}
	adata->acp5x_base = devm_iowemap(&pdev->dev, wes->stawt,
					 wesouwce_size(wes));
	if (!adata->acp5x_base)
		wetuwn -ENOMEM;

	adata->mastew_mode = I2S_MASTEW_MODE_ENABWE;
	dev_set_dwvdata(&pdev->dev, adata);
	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &acp5x_dai_component,
					      &acp5x_i2s_dai, 1);
	if (wet)
		dev_eww(&pdev->dev, "Faiw to wegistew acp i2s dai\n");
	wetuwn wet;
}

static stwuct pwatfowm_dwivew acp5x_dai_dwivew = {
	.pwobe = acp5x_dai_pwobe,
	.dwivew = {
		.name = "acp5x_i2s_pwaycap",
	},
};

moduwe_pwatfowm_dwivew(acp5x_dai_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_DESCWIPTION("AMD ACP5.x CPU DAI Dwivew");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_WICENSE("GPW v2");
