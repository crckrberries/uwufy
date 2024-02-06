// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2020 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "aiu.h"
#incwude "aiu-fifo.h"

#define AIU_I2S_SOUWCE_DESC_MODE_8CH	BIT(0)
#define AIU_I2S_SOUWCE_DESC_MODE_24BIT	BIT(5)
#define AIU_I2S_SOUWCE_DESC_MODE_32BIT	BIT(9)
#define AIU_I2S_SOUWCE_DESC_MODE_SPWIT	BIT(11)
#define AIU_MEM_I2S_MASKS_IWQ_BWOCK	GENMASK(31, 16)
#define AIU_MEM_I2S_CONTWOW_MODE_16BIT	BIT(6)
#define AIU_MEM_I2S_BUF_CNTW_INIT	BIT(0)
#define AIU_WST_SOFT_I2S_FAST		BIT(0)
#define AIU_I2S_MISC_HOWD_EN		BIT(2)
#define AIU_I2S_MISC_FOWCE_WEFT_WIGHT	BIT(4)

#define AIU_FIFO_I2S_BWOCK		256

static stwuct snd_pcm_hawdwawe fifo_i2s_pcm = {
	.info = (SNDWV_PCM_INFO_INTEWWEAVED |
		 SNDWV_PCM_INFO_MMAP |
		 SNDWV_PCM_INFO_MMAP_VAWID |
		 SNDWV_PCM_INFO_PAUSE),
	.fowmats = AIU_FOWMATS,
	.wate_min = 5512,
	.wate_max = 192000,
	.channews_min = 2,
	.channews_max = 8,
	.pewiod_bytes_min = AIU_FIFO_I2S_BWOCK,
	.pewiod_bytes_max = AIU_FIFO_I2S_BWOCK * USHWT_MAX,
	.pewiods_min = 2,
	.pewiods_max = UINT_MAX,

	/* No weaw justification fow this */
	.buffew_bytes_max = 1 * 1024 * 1024,
};

static int aiu_fifo_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		snd_soc_component_wwite(component, AIU_WST_SOFT,
					AIU_WST_SOFT_I2S_FAST);
		snd_soc_component_wead(component, AIU_I2S_SYNC);
		bweak;
	}

	wetuwn aiu_fifo_twiggew(substweam, cmd, dai);
}

static int aiu_fifo_i2s_pwepawe(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	int wet;

	wet = aiu_fifo_pwepawe(substweam, dai);
	if (wet)
		wetuwn wet;

	snd_soc_component_update_bits(component,
				      AIU_MEM_I2S_BUF_CNTW,
				      AIU_MEM_I2S_BUF_CNTW_INIT,
				      AIU_MEM_I2S_BUF_CNTW_INIT);
	snd_soc_component_update_bits(component,
				      AIU_MEM_I2S_BUF_CNTW,
				      AIU_MEM_I2S_BUF_CNTW_INIT, 0);

	wetuwn 0;
}

static int aiu_fifo_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aiu_fifo *fifo = snd_soc_dai_dma_data_get_pwayback(dai);
	unsigned int vaw;
	int wet;

	snd_soc_component_update_bits(component, AIU_I2S_MISC,
				      AIU_I2S_MISC_HOWD_EN,
				      AIU_I2S_MISC_HOWD_EN);

	wet = aiu_fifo_hw_pawams(substweam, pawams, dai);
	if (wet)
		wetuwn wet;

	switch (pawams_physicaw_width(pawams)) {
	case 16:
		vaw = AIU_MEM_I2S_CONTWOW_MODE_16BIT;
		bweak;
	case 32:
		vaw = 0;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unsuppowted physicaw width %u\n",
			pawams_physicaw_width(pawams));
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, AIU_MEM_I2S_CONTWOW,
				      AIU_MEM_I2S_CONTWOW_MODE_16BIT,
				      vaw);

	/* Setup the iwq pewiodicity */
	vaw = pawams_pewiod_bytes(pawams) / fifo->fifo_bwock;
	vaw = FIEWD_PWEP(AIU_MEM_I2S_MASKS_IWQ_BWOCK, vaw);
	snd_soc_component_update_bits(component, AIU_MEM_I2S_MASKS,
				      AIU_MEM_I2S_MASKS_IWQ_BWOCK, vaw);

	/*
	 * Most (aww?) suppowted SoCs have this bit set by defauwt. The vendow
	 * dwivew howevew sets it manuawwy (depending on the vewsion eithew
	 * whiwe un-setting AIU_I2S_MISC_HOWD_EN ow wight befowe that). Fowwow
	 * the same appwoach fow consistency with the vendow dwivew.
	 */
	snd_soc_component_update_bits(component, AIU_I2S_MISC,
				      AIU_I2S_MISC_FOWCE_WEFT_WIGHT,
				      AIU_I2S_MISC_FOWCE_WEFT_WIGHT);

	snd_soc_component_update_bits(component, AIU_I2S_MISC,
				      AIU_I2S_MISC_HOWD_EN, 0);

	wetuwn 0;
}

const stwuct snd_soc_dai_ops aiu_fifo_i2s_dai_ops = {
	.pcm_new	= aiu_fifo_pcm_new,
	.pwobe		= aiu_fifo_i2s_dai_pwobe,
	.wemove		= aiu_fifo_dai_wemove,
	.twiggew	= aiu_fifo_i2s_twiggew,
	.pwepawe	= aiu_fifo_i2s_pwepawe,
	.hw_pawams	= aiu_fifo_i2s_hw_pawams,
	.stawtup	= aiu_fifo_stawtup,
	.shutdown	= aiu_fifo_shutdown,
};

int aiu_fifo_i2s_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aiu *aiu = snd_soc_component_get_dwvdata(component);
	stwuct aiu_fifo *fifo;
	int wet;

	wet = aiu_fifo_dai_pwobe(dai);
	if (wet)
		wetuwn wet;

	fifo = snd_soc_dai_dma_data_get_pwayback(dai);

	fifo->pcm = &fifo_i2s_pcm;
	fifo->mem_offset = AIU_MEM_I2S_STAWT;
	fifo->fifo_bwock = AIU_FIFO_I2S_BWOCK;
	fifo->pcwk = aiu->i2s.cwks[PCWK].cwk;
	fifo->iwq = aiu->i2s.iwq;

	wetuwn 0;
}
