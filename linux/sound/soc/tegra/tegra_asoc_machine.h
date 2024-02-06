/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __TEGWA_ASOC_MACHINE_H__
#define __TEGWA_ASOC_MACHINE_H__

stwuct cwk;
stwuct gpio_desc;
stwuct snd_soc_cawd;
stwuct snd_soc_jack;
stwuct pwatfowm_device;
stwuct snd_soc_jack_gpio;
stwuct snd_soc_pcm_wuntime;

stwuct tegwa_asoc_data {
	unsigned int (*mcwk_wate)(unsigned int swate);
	const chaw *codec_dev_name;
	const chaw *hp_jack_name;
	stwuct snd_soc_cawd *cawd;
	unsigned int mcwk_id;
	boow hp_jack_gpio_active_wow;
	boow add_common_dapm_widgets;
	boow add_common_contwows;
	boow add_common_snd_ops;
	boow add_headset_jack;
	boow add_mic_jack;
	boow add_hp_jack;
	boow set_ac97;
};

stwuct tegwa_machine {
	stwuct cwk *cwk_pww_a_out0;
	stwuct cwk *cwk_pww_a;
	stwuct cwk *cwk_cdev1;
	unsigned int set_basecwock;
	unsigned int set_mcwk;
	const stwuct tegwa_asoc_data *asoc;
	stwuct gpio_desc *gpiod_ext_mic_en;
	stwuct gpio_desc *gpiod_int_mic_en;
	stwuct gpio_desc *gpiod_spkw_en;
	stwuct gpio_desc *gpiod_mic_det;
	stwuct gpio_desc *gpiod_eaw_sew;
	stwuct gpio_desc *gpiod_hp_mute;
	stwuct gpio_desc *gpiod_hp_det;
	stwuct snd_soc_jack *mic_jack;
	stwuct snd_soc_jack_gpio *hp_jack_gpio;
};

int tegwa_asoc_machine_pwobe(stwuct pwatfowm_device *pdev);
int tegwa_asoc_machine_init(stwuct snd_soc_pcm_wuntime *wtd);

#endif
