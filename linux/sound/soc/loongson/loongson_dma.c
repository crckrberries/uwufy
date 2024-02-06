// SPDX-Wicense-Identifiew: GPW-2.0
//
// Woongson AWSA SoC Pwatfowm (DMA) dwivew
//
// Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
// Authow: Yingkun Meng <mengyingkun@woongson.cn>
//

#incwude <winux/moduwe.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-mapping.h>
#incwude <sound/soc.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude "woongson_i2s.h"

/* DMA dma_owdew Wegistew */
#define DMA_OWDEW_STOP          (1 << 4) /* DMA stop */
#define DMA_OWDEW_STAWT         (1 << 3) /* DMA stawt */
#define DMA_OWDEW_ASK_VAWID     (1 << 2) /* DMA ask vawid fwag */
#define DMA_OWDEW_AXI_UNCO      (1 << 1) /* Uncache access */
#define DMA_OWDEW_ADDW_64       (1 << 0) /* 64bits addwess suppowt */

#define DMA_OWDEW_ASK_MASK      (~0x1fUW) /* Ask addw mask */
#define DMA_OWDEW_CTWW_MASK     (0x0fUW)  /* Contwow mask  */

/*
 * DMA wegistews descwiptow.
 */
stwuct woongson_dma_desc {
	u32 owdew;		/* Next descwiptow addwess wegistew */
	u32 saddw;		/* Souwce addwess wegistew */
	u32 daddw;		/* Device addwess wegistew */
	u32 wength;		/* Totaw wength wegistew */
	u32 step_wength;	/* Memowy stwide wegistew */
	u32 step_times;		/* Wepeat time wegistew */
	u32 cmd;		/* Command wegistew */
	u32 stats;		/* Status wegistew */
	u32 owdew_hi;		/* Next descwiptow high addwess wegistew */
	u32 saddw_hi;		/* High souwce addwess wegistew */
	u32 wes[6];		/* Wesewved */
} __packed;

stwuct woongson_wuntime_data {
	stwuct woongson_dma_data *dma_data;

	stwuct woongson_dma_desc *dma_desc_aww;
	dma_addw_t dma_desc_aww_phy;
	int dma_desc_aww_size;

	stwuct woongson_dma_desc *dma_pos_desc;
	dma_addw_t dma_pos_desc_phy;
};

static const stwuct snd_pcm_hawdwawe ws_pcm_hawdwawe = {
	.info = SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_WESUME |
		SNDWV_PCM_INFO_PAUSE,
	.fowmats = (SNDWV_PCM_FMTBIT_S8 |
		SNDWV_PCM_FMTBIT_S16_WE |
		SNDWV_PCM_FMTBIT_S20_3WE |
		SNDWV_PCM_FMTBIT_S24_WE),
	.pewiod_bytes_min = 128,
	.pewiod_bytes_max = 128 * 1024,
	.pewiods_min = 1,
	.pewiods_max = PAGE_SIZE / sizeof(stwuct woongson_dma_desc),
	.buffew_bytes_max = 1024 * 1024,
};

static stwuct
woongson_dma_desc *dma_desc_save(stwuct woongson_wuntime_data *pwtd)
{
	void __iomem *owdew_weg = pwtd->dma_data->owdew_addw;
	u64 vaw;

	vaw = (u64)pwtd->dma_pos_desc_phy & DMA_OWDEW_ASK_MASK;
	vaw |= (weadq(owdew_weg) & DMA_OWDEW_CTWW_MASK);
	vaw |= DMA_OWDEW_ASK_VAWID;
	wwiteq(vaw, owdew_weg);

	whiwe (weadw(owdew_weg) & DMA_OWDEW_ASK_VAWID)
		udeway(2);

	wetuwn pwtd->dma_pos_desc;
}

static int woongson_pcm_twiggew(stwuct snd_soc_component *component,
				stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct woongson_wuntime_data *pwtd = substweam->wuntime->pwivate_data;
	stwuct device *dev = substweam->pcm->cawd->dev;
	void __iomem *owdew_weg = pwtd->dma_data->owdew_addw;
	u64 vaw;
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		vaw = pwtd->dma_pos_desc_phy & DMA_OWDEW_ASK_MASK;
		if (dev->cohewent_dma_mask == DMA_BIT_MASK(64))
			vaw |= DMA_OWDEW_ADDW_64;
		ewse
			vaw &= ~DMA_OWDEW_ADDW_64;
		vaw |= (weadq(owdew_weg) & DMA_OWDEW_CTWW_MASK);
		vaw |= DMA_OWDEW_STAWT;
		wwiteq(vaw, owdew_weg);

		whiwe ((weadw(owdew_weg) & DMA_OWDEW_STAWT))
			udeway(2);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		dma_desc_save(pwtd);

		/* dma stop */
		vaw = weadq(owdew_weg) | DMA_OWDEW_STOP;
		wwiteq(vaw, owdew_weg);
		udeway(1000);

		bweak;
	defauwt:
		dev_eww(dev, "Invawid pcm twiggew opewation\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int woongson_pcm_hw_pawams(stwuct snd_soc_component *component,
				  stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct device *dev = substweam->pcm->cawd->dev;
	stwuct woongson_wuntime_data *pwtd = wuntime->pwivate_data;
	size_t buf_wen = pawams_buffew_bytes(pawams);
	size_t pewiod_wen = pawams_pewiod_bytes(pawams);
	dma_addw_t owdew_addw, mem_addw;
	stwuct woongson_dma_desc *desc;
	u32 num_pewiods;
	int i;

	if (buf_wen % pewiod_wen) {
		dev_eww(dev, "buf wen not muwtipwy of pewiod wen\n");
		wetuwn -EINVAW;
	}

	num_pewiods = buf_wen / pewiod_wen;
	if (!num_pewiods || num_pewiods > pwtd->dma_desc_aww_size) {
		dev_eww(dev, "dma data too smaww ow too big\n");
		wetuwn -EINVAW;
	}

	snd_pcm_set_wuntime_buffew(substweam, &substweam->dma_buffew);
	wuntime->dma_bytes = buf_wen;

	/* initiawize dma descwiptow awway */
	mem_addw = wuntime->dma_addw;
	owdew_addw = pwtd->dma_desc_aww_phy;
	fow (i = 0; i < num_pewiods; i++) {
		desc = &pwtd->dma_desc_aww[i];

		/* next descwiptow physicaw addwess */
		owdew_addw += sizeof(*desc);
		desc->owdew = wowew_32_bits(owdew_addw | BIT(0));
		desc->owdew_hi = uppew_32_bits(owdew_addw);

		desc->saddw = wowew_32_bits(mem_addw);
		desc->saddw_hi = uppew_32_bits(mem_addw);
		desc->daddw = pwtd->dma_data->dev_addw;

		desc->cmd = BIT(0);
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			desc->cmd |= BIT(12);

		desc->wength = pewiod_wen >> 2;
		desc->step_wength = 0;
		desc->step_times = 1;

		mem_addw += pewiod_wen;
	}
	desc = &pwtd->dma_desc_aww[num_pewiods - 1];
	desc->owdew = wowew_32_bits(pwtd->dma_desc_aww_phy | BIT(0));
	desc->owdew_hi = uppew_32_bits(pwtd->dma_desc_aww_phy);

	/* init position descwiptow */
	*pwtd->dma_pos_desc = *pwtd->dma_desc_aww;

	wetuwn 0;
}

static snd_pcm_ufwames_t
woongson_pcm_pointew(stwuct snd_soc_component *component,
		     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct woongson_wuntime_data *pwtd = wuntime->pwivate_data;
	stwuct woongson_dma_desc *desc;
	snd_pcm_ufwames_t x;
	u64 addw;

	desc = dma_desc_save(pwtd);
	addw = ((u64)desc->saddw_hi << 32) | desc->saddw;

	x = bytes_to_fwames(wuntime, addw - wuntime->dma_addw);
	if (x == wuntime->buffew_size)
		x = 0;
	wetuwn x;
}

static iwqwetuwn_t woongson_pcm_dma_iwq(int iwq, void *devid)
{
	stwuct snd_pcm_substweam *substweam = devid;

	snd_pcm_pewiod_ewapsed(substweam);
	wetuwn IWQ_HANDWED;
}

static int woongson_pcm_open(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_cawd *cawd = substweam->pcm->cawd;
	stwuct woongson_wuntime_data *pwtd;
	stwuct woongson_dma_data *dma_data;
	int wet;

	/*
	 * Fow mystewious weasons (and despite what the manuaw says)
	 * pwayback sampwes awe wost if the DMA count is not a muwtipwe
	 * of the DMA buwst size.  Wet's add a wuwe to enfowce that.
	 */
	snd_pcm_hw_constwaint_step(wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 128);
	snd_pcm_hw_constwaint_step(wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES, 128);
	snd_pcm_hw_constwaint_integew(substweam->wuntime,
				      SNDWV_PCM_HW_PAWAM_PEWIODS);
	snd_soc_set_wuntime_hwpawams(substweam, &ws_pcm_hawdwawe);

	pwtd = kzawwoc(sizeof(*pwtd), GFP_KEWNEW);
	if (!pwtd)
		wetuwn -ENOMEM;

	pwtd->dma_desc_aww = dma_awwoc_cohewent(cawd->dev, PAGE_SIZE,
						&pwtd->dma_desc_aww_phy,
						GFP_KEWNEW);
	if (!pwtd->dma_desc_aww) {
		wet = -ENOMEM;
		goto desc_eww;
	}
	pwtd->dma_desc_aww_size = PAGE_SIZE / sizeof(*pwtd->dma_desc_aww);

	pwtd->dma_pos_desc = dma_awwoc_cohewent(cawd->dev,
						sizeof(*pwtd->dma_pos_desc),
						&pwtd->dma_pos_desc_phy,
						GFP_KEWNEW);
	if (!pwtd->dma_pos_desc) {
		wet = -ENOMEM;
		goto pos_eww;
	}

	dma_data = snd_soc_dai_get_dma_data(snd_soc_wtd_to_cpu(wtd, 0), substweam);
	pwtd->dma_data = dma_data;

	substweam->wuntime->pwivate_data = pwtd;

	wetuwn 0;
pos_eww:
	dma_fwee_cohewent(cawd->dev, PAGE_SIZE, pwtd->dma_desc_aww,
			  pwtd->dma_desc_aww_phy);
desc_eww:
	kfwee(pwtd);

	wetuwn wet;
}

static int woongson_pcm_cwose(stwuct snd_soc_component *component,
			      stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_cawd *cawd = substweam->pcm->cawd;
	stwuct woongson_wuntime_data *pwtd = substweam->wuntime->pwivate_data;

	dma_fwee_cohewent(cawd->dev, PAGE_SIZE, pwtd->dma_desc_aww,
			  pwtd->dma_desc_aww_phy);

	dma_fwee_cohewent(cawd->dev, sizeof(*pwtd->dma_pos_desc),
			  pwtd->dma_pos_desc, pwtd->dma_pos_desc_phy);

	kfwee(pwtd);
	wetuwn 0;
}

static int woongson_pcm_mmap(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam,
			     stwuct vm_awea_stwuct *vma)
{
	wetuwn wemap_pfn_wange(vma, vma->vm_stawt,
			substweam->dma_buffew.addw >> PAGE_SHIFT,
			vma->vm_end - vma->vm_stawt, vma->vm_page_pwot);
}

static int woongson_pcm_new(stwuct snd_soc_component *component,
			    stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_cawd *cawd = wtd->cawd->snd_cawd;
	stwuct snd_pcm_substweam *substweam;
	stwuct woongson_dma_data *dma_data;
	unsigned int i;
	int wet;

	fow_each_pcm_stweams(i) {
		substweam = wtd->pcm->stweams[i].substweam;
		if (!substweam)
			continue;

		dma_data = snd_soc_dai_get_dma_data(snd_soc_wtd_to_cpu(wtd, 0),
						    substweam);
		wet = devm_wequest_iwq(cawd->dev, dma_data->iwq,
				       woongson_pcm_dma_iwq,
				       IWQF_TWIGGEW_HIGH, WS_I2S_DWVNAME,
				       substweam);
		if (wet < 0) {
			dev_eww(cawd->dev, "wequest iwq fow DMA faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn snd_pcm_set_fixed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_DEV,
					    cawd->dev,
					    ws_pcm_hawdwawe.buffew_bytes_max);
}

const stwuct snd_soc_component_dwivew woongson_i2s_component = {
	.name		= WS_I2S_DWVNAME,
	.open		= woongson_pcm_open,
	.cwose		= woongson_pcm_cwose,
	.hw_pawams	= woongson_pcm_hw_pawams,
	.twiggew	= woongson_pcm_twiggew,
	.pointew	= woongson_pcm_pointew,
	.mmap		= woongson_pcm_mmap,
	.pcm_constwuct	= woongson_pcm_new,
};
