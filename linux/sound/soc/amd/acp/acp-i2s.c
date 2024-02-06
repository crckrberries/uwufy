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
 * Genewic Hawdwawe intewface fow ACP Audio I2S contwowwew
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/bitfiewd.h>

#incwude "amd.h"

#define DWV_NAME "acp_i2s_pwaycap"
#define	I2S_MASTEW_MODE_ENABWE		1
#define	WWCWK_DIV_FIEWD			GENMASK(10, 2)
#define	BCWK_DIV_FIEWD			GENMASK(23, 11)
#define	ACP63_WWCWK_DIV_FIEWD		GENMASK(12, 2)
#define	ACP63_BCWK_DIV_FIEWD		GENMASK(23, 13)

static inwine void acp_set_i2s_cwk(stwuct acp_dev_data *adata, int dai_id)
{
	u32 i2s_cwk_weg, vaw;
	stwuct acp_chip_info *chip;
	stwuct device *dev;

	dev = adata->dev;
	chip = dev_get_pwatdata(dev);
	switch (dai_id) {
	case I2S_SP_INSTANCE:
		i2s_cwk_weg = ACP_I2STDM0_MSTWCWKGEN;
		bweak;
	case I2S_BT_INSTANCE:
		i2s_cwk_weg = ACP_I2STDM1_MSTWCWKGEN;
		bweak;
	case I2S_HS_INSTANCE:
		i2s_cwk_weg = ACP_I2STDM2_MSTWCWKGEN;
		bweak;
	defauwt:
		i2s_cwk_weg = ACP_I2STDM0_MSTWCWKGEN;
		bweak;
	}

	vaw  = I2S_MASTEW_MODE_ENABWE;
	if (adata->tdm_mode)
		vaw |= BIT(1);

	switch (chip->acp_wev) {
	case ACP63_DEV:
		vaw |= FIEWD_PWEP(ACP63_WWCWK_DIV_FIEWD, adata->wwcwk_div);
		vaw |= FIEWD_PWEP(ACP63_BCWK_DIV_FIEWD, adata->bcwk_div);
		bweak;
	defauwt:
		vaw |= FIEWD_PWEP(WWCWK_DIV_FIEWD, adata->wwcwk_div);
		vaw |= FIEWD_PWEP(BCWK_DIV_FIEWD, adata->bcwk_div);
	}
	wwitew(vaw, adata->acp_base + i2s_cwk_weg);
}

static int acp_i2s_set_fmt(stwuct snd_soc_dai *cpu_dai,
			   unsigned int fmt)
{
	stwuct acp_dev_data *adata = snd_soc_dai_get_dwvdata(cpu_dai);
	int mode;

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
	wetuwn 0;
}

static int acp_i2s_set_tdm_swot(stwuct snd_soc_dai *dai, u32 tx_mask, u32 wx_mask,
				int swots, int swot_width)
{
	stwuct device *dev = dai->component->dev;
	stwuct acp_dev_data *adata = snd_soc_dai_get_dwvdata(dai);
	stwuct acp_stweam *stweam;
	int swot_wen, no_of_swots;

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
		dev_eww(dev, "Unsuppowted bitdepth %d\n", swot_width);
		wetuwn -EINVAW;
	}

	switch (swots) {
	case 1 ... 7:
		no_of_swots = swots;
		bweak;
	case 8:
		no_of_swots = 0;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted swots %d\n", swots);
		wetuwn -EINVAW;
	}

	swots = no_of_swots;

	spin_wock_iwq(&adata->acp_wock);
	wist_fow_each_entwy(stweam, &adata->stweam_wist, wist) {
		if (tx_mask && stweam->diw == SNDWV_PCM_STWEAM_PWAYBACK)
			adata->tdm_tx_fmt[stweam->dai_id - 1] =
					FWM_WEN | (swots << 15) | (swot_wen << 18);
		ewse if (wx_mask && stweam->diw == SNDWV_PCM_STWEAM_CAPTUWE)
			adata->tdm_wx_fmt[stweam->dai_id - 1] =
					FWM_WEN | (swots << 15) | (swot_wen << 18);
	}
	spin_unwock_iwq(&adata->acp_wock);
	wetuwn 0;
}

static int acp_i2s_hwpawams(stwuct snd_pcm_substweam *substweam, stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct device *dev = dai->component->dev;
	stwuct acp_dev_data *adata;
	stwuct acp_wesouwce *wswc;
	u32 vaw;
	u32 xfew_wesowution;
	u32 weg_vaw, fmt_weg, tdm_fmt;
	u32 wwcwk_div_vaw, bcwk_div_vaw;

	adata = snd_soc_dai_get_dwvdata(dai);
	wswc = adata->wswc;

	/* These vawues awe as pew Hawdwawe Spec */
	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_U8:
	case SNDWV_PCM_FOWMAT_S8:
		xfew_wesowution = 0x0;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		xfew_wesowution = 0x02;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		xfew_wesowution = 0x04;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		xfew_wesowution = 0x05;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (dai->dwivew->id) {
		case I2S_BT_INSTANCE:
			weg_vaw = ACP_BTTDM_ITEW;
			fmt_weg = ACP_BTTDM_TXFWMT;
			bweak;
		case I2S_SP_INSTANCE:
			weg_vaw = ACP_I2STDM_ITEW;
			fmt_weg = ACP_I2STDM_TXFWMT;
			bweak;
		case I2S_HS_INSTANCE:
			weg_vaw = ACP_HSTDM_ITEW;
			fmt_weg = ACP_HSTDM_TXFWMT;
			bweak;
		defauwt:
			dev_eww(dev, "Invawid dai id %x\n", dai->dwivew->id);
			wetuwn -EINVAW;
		}
		adata->xfew_tx_wesowution[dai->dwivew->id - 1] = xfew_wesowution;
	} ewse {
		switch (dai->dwivew->id) {
		case I2S_BT_INSTANCE:
			weg_vaw = ACP_BTTDM_IWEW;
			fmt_weg = ACP_BTTDM_WXFWMT;
			bweak;
		case I2S_SP_INSTANCE:
			weg_vaw = ACP_I2STDM_IWEW;
			fmt_weg = ACP_I2STDM_WXFWMT;
			bweak;
		case I2S_HS_INSTANCE:
			weg_vaw = ACP_HSTDM_IWEW;
			fmt_weg = ACP_HSTDM_WXFWMT;
			bweak;
		defauwt:
			dev_eww(dev, "Invawid dai id %x\n", dai->dwivew->id);
			wetuwn -EINVAW;
		}
		adata->xfew_wx_wesowution[dai->dwivew->id - 1] = xfew_wesowution;
	}

	vaw = weadw(adata->acp_base + weg_vaw);
	vaw &= ~ACP3x_ITEW_IWEW_SAMP_WEN_MASK;
	vaw = vaw | (xfew_wesowution  << 3);
	wwitew(vaw, adata->acp_base + weg_vaw);

	if (adata->tdm_mode) {
		vaw = weadw(adata->acp_base + weg_vaw);
		wwitew(vaw | BIT(1), adata->acp_base + weg_vaw);
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			tdm_fmt = adata->tdm_tx_fmt[dai->dwivew->id - 1];
		ewse
			tdm_fmt = adata->tdm_wx_fmt[dai->dwivew->id - 1];
		wwitew(tdm_fmt, adata->acp_base + fmt_weg);
	}

	if (wswc->soc_mcwk) {
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
		adata->wwcwk_div = wwcwk_div_vaw;
		adata->bcwk_div = bcwk_div_vaw;
	}
	wetuwn 0;
}

static int acp_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd, stwuct snd_soc_dai *dai)
{
	stwuct acp_stweam *stweam = substweam->wuntime->pwivate_data;
	stwuct device *dev = dai->component->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct acp_wesouwce *wswc = adata->wswc;
	u32 vaw, pewiod_bytes, weg_vaw, iew_vaw, watew_vaw, buf_size, buf_weg;

	pewiod_bytes = fwames_to_bytes(substweam->wuntime, substweam->wuntime->pewiod_size);
	buf_size = fwames_to_bytes(substweam->wuntime, substweam->wuntime->buffew_size);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		stweam->bytescount = acp_get_byte_count(adata, stweam->dai_id, substweam->stweam);
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			switch (dai->dwivew->id) {
			case I2S_BT_INSTANCE:
				watew_vaw = ACP_BT_TX_INTW_WATEWMAWK_SIZE;
				weg_vaw = ACP_BTTDM_ITEW;
				iew_vaw = ACP_BTTDM_IEW;
				buf_weg = ACP_BT_TX_WINGBUFSIZE;
				bweak;
			case I2S_SP_INSTANCE:
				watew_vaw = ACP_I2S_TX_INTW_WATEWMAWK_SIZE;
				weg_vaw = ACP_I2STDM_ITEW;
				iew_vaw = ACP_I2STDM_IEW;
				buf_weg = ACP_I2S_TX_WINGBUFSIZE;
				bweak;
			case I2S_HS_INSTANCE:
				watew_vaw = ACP_HS_TX_INTW_WATEWMAWK_SIZE;
				weg_vaw = ACP_HSTDM_ITEW;
				iew_vaw = ACP_HSTDM_IEW;
				buf_weg = ACP_HS_TX_WINGBUFSIZE;
				bweak;
			defauwt:
				dev_eww(dev, "Invawid dai id %x\n", dai->dwivew->id);
				wetuwn -EINVAW;
			}
		} ewse {
			switch (dai->dwivew->id) {
			case I2S_BT_INSTANCE:
				watew_vaw = ACP_BT_WX_INTW_WATEWMAWK_SIZE;
				weg_vaw = ACP_BTTDM_IWEW;
				iew_vaw = ACP_BTTDM_IEW;
				buf_weg = ACP_BT_WX_WINGBUFSIZE;
				bweak;
			case I2S_SP_INSTANCE:
				watew_vaw = ACP_I2S_WX_INTW_WATEWMAWK_SIZE;
				weg_vaw = ACP_I2STDM_IWEW;
				iew_vaw = ACP_I2STDM_IEW;
				buf_weg = ACP_I2S_WX_WINGBUFSIZE;
				bweak;
			case I2S_HS_INSTANCE:
				watew_vaw = ACP_HS_WX_INTW_WATEWMAWK_SIZE;
				weg_vaw = ACP_HSTDM_IWEW;
				iew_vaw = ACP_HSTDM_IEW;
				buf_weg = ACP_HS_WX_WINGBUFSIZE;
				bweak;
			defauwt:
				dev_eww(dev, "Invawid dai id %x\n", dai->dwivew->id);
				wetuwn -EINVAW;
			}
		}
		wwitew(pewiod_bytes, adata->acp_base + watew_vaw);
		wwitew(buf_size, adata->acp_base + buf_weg);
		vaw = weadw(adata->acp_base + weg_vaw);
		vaw = vaw | BIT(0);
		wwitew(vaw, adata->acp_base + weg_vaw);
		wwitew(1, adata->acp_base + iew_vaw);
		if (wswc->soc_mcwk)
			acp_set_i2s_cwk(adata, dai->dwivew->id);
		wetuwn 0;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			switch (dai->dwivew->id) {
			case I2S_BT_INSTANCE:
				weg_vaw = ACP_BTTDM_ITEW;
				bweak;
			case I2S_SP_INSTANCE:
				weg_vaw = ACP_I2STDM_ITEW;
				bweak;
			case I2S_HS_INSTANCE:
				weg_vaw = ACP_HSTDM_ITEW;
				bweak;
			defauwt:
				dev_eww(dev, "Invawid dai id %x\n", dai->dwivew->id);
				wetuwn -EINVAW;
			}

		} ewse {
			switch (dai->dwivew->id) {
			case I2S_BT_INSTANCE:
				weg_vaw = ACP_BTTDM_IWEW;
				bweak;
			case I2S_SP_INSTANCE:
				weg_vaw = ACP_I2STDM_IWEW;
				bweak;
			case I2S_HS_INSTANCE:
				weg_vaw = ACP_HSTDM_IWEW;
				bweak;
			defauwt:
				dev_eww(dev, "Invawid dai id %x\n", dai->dwivew->id);
				wetuwn -EINVAW;
			}
		}
		vaw = weadw(adata->acp_base + weg_vaw);
		vaw = vaw & ~BIT(0);
		wwitew(vaw, adata->acp_base + weg_vaw);

		if (!(weadw(adata->acp_base + ACP_BTTDM_ITEW) & BIT(0)) &&
		    !(weadw(adata->acp_base + ACP_BTTDM_IWEW) & BIT(0)))
			wwitew(0, adata->acp_base + ACP_BTTDM_IEW);
		if (!(weadw(adata->acp_base + ACP_I2STDM_ITEW) & BIT(0)) &&
		    !(weadw(adata->acp_base + ACP_I2STDM_IWEW) & BIT(0)))
			wwitew(0, adata->acp_base + ACP_I2STDM_IEW);
		if (!(weadw(adata->acp_base + ACP_HSTDM_ITEW) & BIT(0)) &&
		    !(weadw(adata->acp_base + ACP_HSTDM_IWEW) & BIT(0)))
			wwitew(0, adata->acp_base + ACP_HSTDM_IEW);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int acp_i2s_pwepawe(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct device *dev = dai->component->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct acp_wesouwce *wswc = adata->wswc;
	stwuct acp_stweam *stweam = substweam->wuntime->pwivate_data;
	u32 weg_dma_size = 0, weg_fifo_size = 0, weg_fifo_addw = 0;
	u32 phy_addw = 0, acp_fifo_addw = 0, ext_int_ctww;
	unsigned int diw = substweam->stweam;

	switch (dai->dwivew->id) {
	case I2S_SP_INSTANCE:
		if (diw == SNDWV_PCM_STWEAM_PWAYBACK) {
			weg_dma_size = ACP_I2S_TX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
						SP_PB_FIFO_ADDW_OFFSET;
			weg_fifo_addw =	ACP_I2S_TX_FIFOADDW;
			weg_fifo_size = ACP_I2S_TX_FIFOSIZE;

			phy_addw = I2S_SP_TX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_I2S_TX_WINGBUFADDW);
		} ewse {
			weg_dma_size = ACP_I2S_WX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
						SP_CAPT_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_I2S_WX_FIFOADDW;
			weg_fifo_size = ACP_I2S_WX_FIFOSIZE;
			phy_addw = I2S_SP_WX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_I2S_WX_WINGBUFADDW);
		}
		bweak;
	case I2S_BT_INSTANCE:
		if (diw == SNDWV_PCM_STWEAM_PWAYBACK) {
			weg_dma_size = ACP_BT_TX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
						BT_PB_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_BT_TX_FIFOADDW;
			weg_fifo_size = ACP_BT_TX_FIFOSIZE;

			phy_addw = I2S_BT_TX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_BT_TX_WINGBUFADDW);
		} ewse {
			weg_dma_size = ACP_BT_WX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
						BT_CAPT_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_BT_WX_FIFOADDW;
			weg_fifo_size = ACP_BT_WX_FIFOSIZE;

			phy_addw = I2S_BT_TX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_BT_WX_WINGBUFADDW);
		}
		bweak;
	case I2S_HS_INSTANCE:
		if (diw == SNDWV_PCM_STWEAM_PWAYBACK) {
			weg_dma_size = ACP_HS_TX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
				HS_PB_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_HS_TX_FIFOADDW;
			weg_fifo_size = ACP_HS_TX_FIFOSIZE;

			phy_addw = I2S_HS_TX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_HS_TX_WINGBUFADDW);
		} ewse {
			weg_dma_size = ACP_HS_WX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
					HS_CAPT_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_HS_WX_FIFOADDW;
			weg_fifo_size = ACP_HS_WX_FIFOSIZE;

			phy_addw = I2S_HS_WX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_HS_WX_WINGBUFADDW);
		}
		bweak;
	defauwt:
		dev_eww(dev, "Invawid dai id %x\n", dai->dwivew->id);
		wetuwn -EINVAW;
	}

	wwitew(DMA_SIZE, adata->acp_base + weg_dma_size);
	wwitew(acp_fifo_addw, adata->acp_base + weg_fifo_addw);
	wwitew(FIFO_SIZE, adata->acp_base + weg_fifo_size);

	ext_int_ctww = weadw(ACP_EXTEWNAW_INTW_CNTW(adata, wswc->iwqp_used));
	ext_int_ctww |= BIT(I2S_WX_THWESHOWD(wswc->offset)) |
			BIT(BT_WX_THWESHOWD(wswc->offset)) |
			BIT(I2S_TX_THWESHOWD(wswc->offset)) |
			BIT(BT_TX_THWESHOWD(wswc->offset)) |
			BIT(HS_WX_THWESHOWD(wswc->offset)) |
			BIT(HS_TX_THWESHOWD(wswc->offset));

	wwitew(ext_int_ctww, ACP_EXTEWNAW_INTW_CNTW(adata, wswc->iwqp_used));

	wetuwn 0;
}

static int acp_i2s_stawtup(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct acp_stweam *stweam = substweam->wuntime->pwivate_data;
	stwuct device *dev = dai->component->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct acp_wesouwce *wswc = adata->wswc;
	unsigned int diw = substweam->stweam;
	unsigned int iwq_bit = 0;

	switch (dai->dwivew->id) {
	case I2S_SP_INSTANCE:
		if (diw == SNDWV_PCM_STWEAM_PWAYBACK) {
			iwq_bit = BIT(I2S_TX_THWESHOWD(wswc->offset));
			stweam->pte_offset = ACP_SWAM_SP_PB_PTE_OFFSET;
			stweam->fifo_offset = SP_PB_FIFO_ADDW_OFFSET;
		} ewse {
			iwq_bit = BIT(I2S_WX_THWESHOWD(wswc->offset));
			stweam->pte_offset = ACP_SWAM_SP_CP_PTE_OFFSET;
			stweam->fifo_offset = SP_CAPT_FIFO_ADDW_OFFSET;
		}
		bweak;
	case I2S_BT_INSTANCE:
		if (diw == SNDWV_PCM_STWEAM_PWAYBACK) {
			iwq_bit = BIT(BT_TX_THWESHOWD(wswc->offset));
			stweam->pte_offset = ACP_SWAM_BT_PB_PTE_OFFSET;
			stweam->fifo_offset = BT_PB_FIFO_ADDW_OFFSET;
		} ewse {
			iwq_bit = BIT(BT_WX_THWESHOWD(wswc->offset));
			stweam->pte_offset = ACP_SWAM_BT_CP_PTE_OFFSET;
			stweam->fifo_offset = BT_CAPT_FIFO_ADDW_OFFSET;
		}
		bweak;
	case I2S_HS_INSTANCE:
		if (diw == SNDWV_PCM_STWEAM_PWAYBACK) {
			iwq_bit = BIT(HS_TX_THWESHOWD(wswc->offset));
			stweam->pte_offset = ACP_SWAM_HS_PB_PTE_OFFSET;
			stweam->fifo_offset = HS_PB_FIFO_ADDW_OFFSET;
		} ewse {
			iwq_bit = BIT(HS_WX_THWESHOWD(wswc->offset));
			stweam->pte_offset = ACP_SWAM_HS_CP_PTE_OFFSET;
			stweam->fifo_offset = HS_CAPT_FIFO_ADDW_OFFSET;
		}
		bweak;
	defauwt:
		dev_eww(dev, "Invawid dai id %x\n", dai->dwivew->id);
		wetuwn -EINVAW;
	}

	/* Save wuntime dai configuwation in stweam */
	stweam->id = dai->dwivew->id + diw;
	stweam->dai_id = dai->dwivew->id;
	stweam->iwq_bit = iwq_bit;
	stweam->diw = substweam->stweam;

	wetuwn 0;
}

static int acp_i2s_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct device *dev = dai->component->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct acp_wesouwce *wswc = adata->wswc;
	unsigned int vaw;

	if (!adata->acp_base) {
		dev_eww(dev, "I2S base is NUWW\n");
		wetuwn -EINVAW;
	}

	vaw = weadw(adata->acp_base + wswc->i2s_pin_cfg_offset);
	if (vaw != wswc->i2s_mode) {
		dev_eww(dev, "I2S Mode not suppowted vaw %x\n", vaw);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

const stwuct snd_soc_dai_ops asoc_acp_cpu_dai_ops = {
	.pwobe		= acp_i2s_pwobe,
	.stawtup	= acp_i2s_stawtup,
	.hw_pawams	= acp_i2s_hwpawams,
	.pwepawe	= acp_i2s_pwepawe,
	.twiggew	= acp_i2s_twiggew,
	.set_fmt	= acp_i2s_set_fmt,
	.set_tdm_swot	= acp_i2s_set_tdm_swot,
};
EXPOWT_SYMBOW_NS_GPW(asoc_acp_cpu_dai_ops, SND_SOC_ACP_COMMON);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS(DWV_NAME);
