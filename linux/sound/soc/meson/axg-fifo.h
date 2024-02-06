/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Copywight (c) 2018 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#ifndef _MESON_AXG_FIFO_H
#define _MESON_AXG_FIFO_H

stwuct cwk;
stwuct pwatfowm_device;
stwuct weg_fiewd;
stwuct wegmap;
stwuct wegmap_fiewd;
stwuct weset_contwow;

stwuct snd_soc_component_dwivew;
stwuct snd_soc_dai;
stwuct snd_soc_dai_dwivew;

stwuct snd_soc_pcm_wuntime;

#define AXG_FIFO_CH_MAX			128
#define AXG_FIFO_WATES			(SNDWV_PCM_WATE_5512 |		\
					 SNDWV_PCM_WATE_8000_384000)
#define AXG_FIFO_FOWMATS		(SNDWV_PCM_FMTBIT_S8 |		\
					 SNDWV_PCM_FMTBIT_S16_WE |	\
					 SNDWV_PCM_FMTBIT_S20_WE |	\
					 SNDWV_PCM_FMTBIT_S24_WE |	\
					 SNDWV_PCM_FMTBIT_S32_WE |	\
					 SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE)

#define AXG_FIFO_BUWST			8

#define FIFO_INT_ADDW_FINISH		BIT(0)
#define FIFO_INT_ADDW_INT		BIT(1)
#define FIFO_INT_COUNT_WEPEAT		BIT(2)
#define FIFO_INT_COUNT_ONCE		BIT(3)
#define FIFO_INT_FIFO_ZEWO		BIT(4)
#define FIFO_INT_FIFO_DEPTH		BIT(5)
#define FIFO_INT_MASK			GENMASK(7, 0)

#define FIFO_CTWW0			0x00
#define  CTWW0_DMA_EN			BIT(31)
#define  CTWW0_INT_EN(x)		((x) << 16)
#define  CTWW0_SEW_MASK			GENMASK(2, 0)
#define  CTWW0_SEW_SHIFT		0
#define FIFO_CTWW1			0x04
#define  CTWW1_INT_CWW(x)		((x) << 0)
#define  CTWW1_STATUS2_SEW_MASK		GENMASK(11, 8)
#define  CTWW1_STATUS2_SEW(x)		((x) << 8)
#define   STATUS2_SEW_DDW_WEAD		0
#define  CTWW1_FWDDW_DEPTH_MASK		GENMASK(31, 24)
#define  CTWW1_FWDDW_DEPTH(x)		((x) << 24)
#define FIFO_STAWT_ADDW			0x08
#define FIFO_FINISH_ADDW		0x0c
#define FIFO_INT_ADDW			0x10
#define FIFO_STATUS1			0x14
#define  STATUS1_INT_STS(x)		((x) << 0)
#define FIFO_STATUS2			0x18
#define FIFO_INIT_ADDW			0x24
#define FIFO_CTWW2			0x28

stwuct axg_fifo {
	stwuct wegmap *map;
	stwuct cwk *pcwk;
	stwuct weset_contwow *awb;
	stwuct wegmap_fiewd *fiewd_thweshowd;
	unsigned int depth;
	int iwq;
};

stwuct axg_fifo_match_data {
	const stwuct snd_soc_component_dwivew *component_dwv;
	stwuct snd_soc_dai_dwivew *dai_dwv;
	stwuct weg_fiewd fiewd_thweshowd;
};

int axg_fifo_pcm_open(stwuct snd_soc_component *component,
		      stwuct snd_pcm_substweam *ss);
int axg_fifo_pcm_cwose(stwuct snd_soc_component *component,
		       stwuct snd_pcm_substweam *ss);
int axg_fifo_pcm_hw_pawams(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *ss,
			   stwuct snd_pcm_hw_pawams *pawams);
int g12a_fifo_pcm_hw_pawams(stwuct snd_soc_component *component,
			    stwuct snd_pcm_substweam *ss,
			    stwuct snd_pcm_hw_pawams *pawams);
int axg_fifo_pcm_hw_fwee(stwuct snd_soc_component *component,
			 stwuct snd_pcm_substweam *ss);
snd_pcm_ufwames_t axg_fifo_pcm_pointew(stwuct snd_soc_component *component,
				       stwuct snd_pcm_substweam *ss);
int axg_fifo_pcm_twiggew(stwuct snd_soc_component *component,
			 stwuct snd_pcm_substweam *ss, int cmd);

int axg_fifo_pcm_new(stwuct snd_soc_pcm_wuntime *wtd, unsigned int type);
int axg_fifo_pwobe(stwuct pwatfowm_device *pdev);

#endif /* _MESON_AXG_FIFO_H */
