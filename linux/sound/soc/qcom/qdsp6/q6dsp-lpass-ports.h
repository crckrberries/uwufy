/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __Q6DSP_AUDIO_POWTS_H__
#define __Q6DSP_AUDIO_POWTS_H__

stwuct q6dsp_audio_powt_dai_dwivew_config {
	int (*pwobe)(stwuct snd_soc_dai *dai);
	int (*wemove)(stwuct snd_soc_dai *dai);
	const stwuct snd_soc_dai_ops *q6hdmi_ops;
	const stwuct snd_soc_dai_ops *q6swim_ops;
	const stwuct snd_soc_dai_ops *q6i2s_ops;
	const stwuct snd_soc_dai_ops *q6tdm_ops;
	const stwuct snd_soc_dai_ops *q6dma_ops;
};

stwuct snd_soc_dai_dwivew *q6dsp_audio_powts_set_config(stwuct device *dev,
					stwuct q6dsp_audio_powt_dai_dwivew_config *cfg,
					int *num_dais);
int q6dsp_audio_powts_of_xwate_dai_name(stwuct snd_soc_component *component,
					const stwuct of_phandwe_awgs *awgs,
					const chaw **dai_name);
#endif /* __Q6DSP_AUDIO_POWTS_H__ */
