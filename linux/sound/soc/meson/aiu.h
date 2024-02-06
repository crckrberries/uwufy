/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Copywight (c) 2018 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#ifndef _MESON_AIU_H
#define _MESON_AIU_H

stwuct cwk;
stwuct cwk_buwk_data;
stwuct device;
stwuct of_phandwe_awgs;
stwuct snd_soc_dai;
stwuct snd_soc_dai_ops;

enum aiu_cwk_ids {
	PCWK = 0,
	AOCWK,
	MCWK,
	MIXEW
};

stwuct aiu_intewface {
	stwuct cwk_buwk_data *cwks;
	unsigned int cwk_num;
	int iwq;
};

stwuct aiu_pwatfowm_data {
	boow has_acodec;
	boow has_cwk_ctww_mowe_i2s_div;
};

stwuct aiu {
	stwuct cwk *pcwk;
	stwuct cwk *spdif_mcwk;
	stwuct aiu_intewface i2s;
	stwuct aiu_intewface spdif;
	const stwuct aiu_pwatfowm_data *pwatfowm;
};

#define AIU_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |	\
		     SNDWV_PCM_FMTBIT_S20_WE |	\
		     SNDWV_PCM_FMTBIT_S24_WE)

int aiu_of_xwate_dai_name(stwuct snd_soc_component *component,
			  const stwuct of_phandwe_awgs *awgs,
			  const chaw **dai_name,
			  unsigned int component_id);

int aiu_hdmi_ctww_wegistew_component(stwuct device *dev);
int aiu_acodec_ctww_wegistew_component(stwuct device *dev);

int aiu_fifo_i2s_dai_pwobe(stwuct snd_soc_dai *dai);
int aiu_fifo_spdif_dai_pwobe(stwuct snd_soc_dai *dai);

extewn const stwuct snd_soc_dai_ops aiu_fifo_i2s_dai_ops;
extewn const stwuct snd_soc_dai_ops aiu_fifo_spdif_dai_ops;
extewn const stwuct snd_soc_dai_ops aiu_encodew_i2s_dai_ops;
extewn const stwuct snd_soc_dai_ops aiu_encodew_spdif_dai_ops;

#define AIU_IEC958_BPF			0x000
#define AIU_958_MISC			0x010
#define AIU_IEC958_DCU_FF_CTWW		0x01c
#define AIU_958_CHSTAT_W0		0x020
#define AIU_958_CHSTAT_W1		0x024
#define AIU_958_CTWW			0x028
#define AIU_I2S_SOUWCE_DESC		0x034
#define AIU_I2S_DAC_CFG			0x040
#define AIU_I2S_SYNC			0x044
#define AIU_I2S_MISC			0x048
#define AIU_WST_SOFT			0x054
#define AIU_CWK_CTWW			0x058
#define AIU_CWK_CTWW_MOWE		0x064
#define AIU_CODEC_DAC_WWCWK_CTWW	0x0a0
#define AIU_HDMI_CWK_DATA_CTWW		0x0a8
#define AIU_ACODEC_CTWW			0x0b0
#define AIU_958_CHSTAT_W0		0x0c0
#define AIU_958_CHSTAT_W1		0x0c4
#define AIU_MEM_I2S_STAWT		0x180
#define AIU_MEM_I2S_MASKS		0x18c
#define AIU_MEM_I2S_CONTWOW		0x190
#define AIU_MEM_IEC958_STAWT		0x194
#define AIU_MEM_IEC958_CONTWOW		0x1a4
#define AIU_MEM_I2S_BUF_CNTW		0x1d8
#define AIU_MEM_IEC958_BUF_CNTW		0x1fc

#endif /* _MESON_AIU_H */
