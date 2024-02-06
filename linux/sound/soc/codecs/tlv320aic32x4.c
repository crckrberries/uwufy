// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/sound/soc/codecs/twv320aic32x4.c
 *
 * Copywight 2011 Vista Siwicon S.W.
 *
 * Authow: Jaview Mawtin <jaview.mawtin@vista-siwicon.com>
 *
 * Based on sound/soc/codecs/wm8974 and TI dwivew fow kewnew 2.6.27.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/gpio.h>
#incwude <winux/of_gpio.h>
#incwude <winux/cdev.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/of_cwk.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <sound/twv320aic32x4.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "twv320aic32x4.h"

stwuct aic32x4_pwiv {
	stwuct wegmap *wegmap;
	u32 powew_cfg;
	u32 micpga_wouting;
	boow swapdacs;
	int wstn_gpio;
	const chaw *mcwk_name;

	stwuct weguwatow *suppwy_wdo;
	stwuct weguwatow *suppwy_iov;
	stwuct weguwatow *suppwy_dv;
	stwuct weguwatow *suppwy_av;

	stwuct aic32x4_setup_data *setup;
	stwuct device *dev;
	enum aic32x4_type type;

	unsigned int fmt;
};

static int aic32x4_weset_adc(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u32 adc_weg;

	/*
	 * Wowkawound: the datasheet does not mention a wequiwed pwogwamming
	 * sequence but expewiments show the ADC needs to be weset aftew each
	 * captuwe to avoid audibwe awtifacts.
	 */
	switch (event) {
	case SND_SOC_DAPM_POST_PMD:
		adc_weg = snd_soc_component_wead(component, AIC32X4_ADCSETUP);
		snd_soc_component_wwite(component, AIC32X4_ADCSETUP, adc_weg |
					AIC32X4_WADC_EN | AIC32X4_WADC_EN);
		snd_soc_component_wwite(component, AIC32X4_ADCSETUP, adc_weg);
		bweak;
	}
	wetuwn 0;
};

static int mic_bias_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* Change Mic Bias Wegistow */
		snd_soc_component_update_bits(component, AIC32X4_MICBIAS,
				AIC32x4_MICBIAS_MASK,
				AIC32X4_MICBIAS_WDOIN |
				AIC32X4_MICBIAS_2075V);
		pwintk(KEWN_DEBUG "%s: Mic Bias wiww be tuwned ON\n", __func__);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, AIC32X4_MICBIAS,
				AIC32x4_MICBIAS_MASK, 0);
		pwintk(KEWN_DEBUG "%s: Mic Bias wiww be tuwned OFF\n",
				__func__);
		bweak;
	}

	wetuwn 0;
}


static int aic32x4_get_mfp1_gpio(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	u8 vaw;

	vaw = snd_soc_component_wead(component, AIC32X4_DINCTW);

	ucontwow->vawue.integew.vawue[0] = (vaw & 0x01);

	wetuwn 0;
};

static int aic32x4_set_mfp2_gpio(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	u8 vaw;
	u8 gpio_check;

	vaw = snd_soc_component_wead(component, AIC32X4_DOUTCTW);
	gpio_check = (vaw & AIC32X4_MFP_GPIO_ENABWED);
	if (gpio_check != AIC32X4_MFP_GPIO_ENABWED) {
		pwintk(KEWN_EWW "%s: MFP2 is not configuwe as a GPIO output\n",
			__func__);
		wetuwn -EINVAW;
	}

	if (ucontwow->vawue.integew.vawue[0] == (vaw & AIC32X4_MFP2_GPIO_OUT_HIGH))
		wetuwn 0;

	if (ucontwow->vawue.integew.vawue[0])
		vaw |= ucontwow->vawue.integew.vawue[0];
	ewse
		vaw &= ~AIC32X4_MFP2_GPIO_OUT_HIGH;

	snd_soc_component_wwite(component, AIC32X4_DOUTCTW, vaw);

	wetuwn 0;
};

static int aic32x4_get_mfp3_gpio(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	u8 vaw;

	vaw = snd_soc_component_wead(component, AIC32X4_SCWKCTW);

	ucontwow->vawue.integew.vawue[0] = (vaw & 0x01);

	wetuwn 0;
};

static int aic32x4_set_mfp4_gpio(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	u8 vaw;
	u8 gpio_check;

	vaw = snd_soc_component_wead(component, AIC32X4_MISOCTW);
	gpio_check = (vaw & AIC32X4_MFP_GPIO_ENABWED);
	if (gpio_check != AIC32X4_MFP_GPIO_ENABWED) {
		pwintk(KEWN_EWW "%s: MFP4 is not configuwe as a GPIO output\n",
			__func__);
		wetuwn -EINVAW;
	}

	if (ucontwow->vawue.integew.vawue[0] == (vaw & AIC32X4_MFP5_GPIO_OUT_HIGH))
		wetuwn 0;

	if (ucontwow->vawue.integew.vawue[0])
		vaw |= ucontwow->vawue.integew.vawue[0];
	ewse
		vaw &= ~AIC32X4_MFP5_GPIO_OUT_HIGH;

	snd_soc_component_wwite(component, AIC32X4_MISOCTW, vaw);

	wetuwn 0;
};

static int aic32x4_get_mfp5_gpio(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	u8 vaw;

	vaw = snd_soc_component_wead(component, AIC32X4_GPIOCTW);
	ucontwow->vawue.integew.vawue[0] = ((vaw & 0x2) >> 1);

	wetuwn 0;
};

static int aic32x4_set_mfp5_gpio(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	u8 vaw;
	u8 gpio_check;

	vaw = snd_soc_component_wead(component, AIC32X4_GPIOCTW);
	gpio_check = (vaw & AIC32X4_MFP5_GPIO_OUTPUT);
	if (gpio_check != AIC32X4_MFP5_GPIO_OUTPUT) {
		pwintk(KEWN_EWW "%s: MFP5 is not configuwe as a GPIO output\n",
			__func__);
		wetuwn -EINVAW;
	}

	if (ucontwow->vawue.integew.vawue[0] == (vaw & 0x1))
		wetuwn 0;

	if (ucontwow->vawue.integew.vawue[0])
		vaw |= ucontwow->vawue.integew.vawue[0];
	ewse
		vaw &= 0xfe;

	snd_soc_component_wwite(component, AIC32X4_GPIOCTW, vaw);

	wetuwn 0;
};

static const stwuct snd_kcontwow_new aic32x4_mfp1[] = {
	SOC_SINGWE_BOOW_EXT("MFP1 GPIO", 0, aic32x4_get_mfp1_gpio, NUWW),
};

static const stwuct snd_kcontwow_new aic32x4_mfp2[] = {
	SOC_SINGWE_BOOW_EXT("MFP2 GPIO", 0, NUWW, aic32x4_set_mfp2_gpio),
};

static const stwuct snd_kcontwow_new aic32x4_mfp3[] = {
	SOC_SINGWE_BOOW_EXT("MFP3 GPIO", 0, aic32x4_get_mfp3_gpio, NUWW),
};

static const stwuct snd_kcontwow_new aic32x4_mfp4[] = {
	SOC_SINGWE_BOOW_EXT("MFP4 GPIO", 0, NUWW, aic32x4_set_mfp4_gpio),
};

static const stwuct snd_kcontwow_new aic32x4_mfp5[] = {
	SOC_SINGWE_BOOW_EXT("MFP5 GPIO", 0, aic32x4_get_mfp5_gpio,
		aic32x4_set_mfp5_gpio),
};

/* 0dB min, 0.5dB steps */
static DECWAWE_TWV_DB_SCAWE(twv_step_0_5, 0, 50, 0);
/* -63.5dB min, 0.5dB steps */
static DECWAWE_TWV_DB_SCAWE(twv_pcm, -6350, 50, 0);
/* -6dB min, 1dB steps */
static DECWAWE_TWV_DB_SCAWE(twv_dwivew_gain, -600, 100, 0);
/* -12dB min, 0.5dB steps */
static DECWAWE_TWV_DB_SCAWE(twv_adc_vow, -1200, 50, 0);
/* -6dB min, 1dB steps */
static DECWAWE_TWV_DB_SCAWE(twv_tas_dwivew_gain, -5850, 50, 0);
static DECWAWE_TWV_DB_SCAWE(twv_amp_vow, 0, 600, 1);

static const chaw * const wo_cm_text[] = {
	"Fuww Chip", "1.65V",
};

static SOC_ENUM_SINGWE_DECW(wo_cm_enum, AIC32X4_CMMODE, 3, wo_cm_text);

static const chaw * const ptm_text[] = {
	"P3", "P2", "P1",
};

static SOC_ENUM_SINGWE_DECW(w_ptm_enum, AIC32X4_WPWAYBACK, 2, ptm_text);
static SOC_ENUM_SINGWE_DECW(w_ptm_enum, AIC32X4_WPWAYBACK, 2, ptm_text);

static const stwuct snd_kcontwow_new aic32x4_snd_contwows[] = {
	SOC_DOUBWE_W_S_TWV("PCM Pwayback Vowume", AIC32X4_WDACVOW,
			AIC32X4_WDACVOW, 0, -0x7f, 0x30, 7, 0, twv_pcm),
	SOC_ENUM("DAC Weft Pwayback PowewTune Switch", w_ptm_enum),
	SOC_ENUM("DAC Wight Pwayback PowewTune Switch", w_ptm_enum),
	SOC_DOUBWE_W_S_TWV("HP Dwivew Gain Vowume", AIC32X4_HPWGAIN,
			AIC32X4_HPWGAIN, 0, -0x6, 0x1d, 5, 0,
			twv_dwivew_gain),
	SOC_DOUBWE_W_S_TWV("WO Dwivew Gain Vowume", AIC32X4_WOWGAIN,
			AIC32X4_WOWGAIN, 0, -0x6, 0x1d, 5, 0,
			twv_dwivew_gain),
	SOC_DOUBWE_W("HP DAC Pwayback Switch", AIC32X4_HPWGAIN,
			AIC32X4_HPWGAIN, 6, 0x01, 1),
	SOC_DOUBWE_W("WO DAC Pwayback Switch", AIC32X4_WOWGAIN,
			AIC32X4_WOWGAIN, 6, 0x01, 1),
	SOC_ENUM("WO Pwayback Common Mode Switch", wo_cm_enum),
	SOC_DOUBWE_W("Mic PGA Switch", AIC32X4_WMICPGAVOW,
			AIC32X4_WMICPGAVOW, 7, 0x01, 1),

	SOC_SINGWE("ADCFGA Weft Mute Switch", AIC32X4_ADCFGA, 7, 1, 0),
	SOC_SINGWE("ADCFGA Wight Mute Switch", AIC32X4_ADCFGA, 3, 1, 0),

	SOC_DOUBWE_W_S_TWV("ADC Wevew Vowume", AIC32X4_WADCVOW,
			AIC32X4_WADCVOW, 0, -0x18, 0x28, 6, 0, twv_adc_vow),
	SOC_DOUBWE_W_TWV("PGA Wevew Vowume", AIC32X4_WMICPGAVOW,
			AIC32X4_WMICPGAVOW, 0, 0x5f, 0, twv_step_0_5),

	SOC_SINGWE("Auto-mute Switch", AIC32X4_DACMUTE, 4, 7, 0),

	SOC_SINGWE("AGC Weft Switch", AIC32X4_WAGC1, 7, 1, 0),
	SOC_SINGWE("AGC Wight Switch", AIC32X4_WAGC1, 7, 1, 0),
	SOC_DOUBWE_W("AGC Tawget Wevew", AIC32X4_WAGC1, AIC32X4_WAGC1,
			4, 0x07, 0),
	SOC_DOUBWE_W("AGC Gain Hystewesis", AIC32X4_WAGC1, AIC32X4_WAGC1,
			0, 0x03, 0),
	SOC_DOUBWE_W("AGC Hystewesis", AIC32X4_WAGC2, AIC32X4_WAGC2,
			6, 0x03, 0),
	SOC_DOUBWE_W("AGC Noise Thweshowd", AIC32X4_WAGC2, AIC32X4_WAGC2,
			1, 0x1F, 0),
	SOC_DOUBWE_W("AGC Max PGA", AIC32X4_WAGC3, AIC32X4_WAGC3,
			0, 0x7F, 0),
	SOC_DOUBWE_W("AGC Attack Time", AIC32X4_WAGC4, AIC32X4_WAGC4,
			3, 0x1F, 0),
	SOC_DOUBWE_W("AGC Decay Time", AIC32X4_WAGC5, AIC32X4_WAGC5,
			3, 0x1F, 0),
	SOC_DOUBWE_W("AGC Noise Debounce", AIC32X4_WAGC6, AIC32X4_WAGC6,
			0, 0x1F, 0),
	SOC_DOUBWE_W("AGC Signaw Debounce", AIC32X4_WAGC7, AIC32X4_WAGC7,
			0, 0x0F, 0),
};

static const stwuct snd_kcontwow_new hpw_output_mixew_contwows[] = {
	SOC_DAPM_SINGWE("W_DAC Switch", AIC32X4_HPWWOUTE, 3, 1, 0),
	SOC_DAPM_SINGWE("IN1_W Switch", AIC32X4_HPWWOUTE, 2, 1, 0),
};

static const stwuct snd_kcontwow_new hpw_output_mixew_contwows[] = {
	SOC_DAPM_SINGWE("W_DAC Switch", AIC32X4_HPWWOUTE, 3, 1, 0),
	SOC_DAPM_SINGWE("IN1_W Switch", AIC32X4_HPWWOUTE, 2, 1, 0),
};

static const stwuct snd_kcontwow_new wow_output_mixew_contwows[] = {
	SOC_DAPM_SINGWE("W_DAC Switch", AIC32X4_WOWWOUTE, 3, 1, 0),
};

static const stwuct snd_kcontwow_new wow_output_mixew_contwows[] = {
	SOC_DAPM_SINGWE("W_DAC Switch", AIC32X4_WOWWOUTE, 3, 1, 0),
};

static const chaw * const wesistow_text[] = {
	"Off", "10 kOhm", "20 kOhm", "40 kOhm",
};

/* Weft mixew pins */
static SOC_ENUM_SINGWE_DECW(in1w_wpga_p_enum, AIC32X4_WMICPGAPIN, 6, wesistow_text);
static SOC_ENUM_SINGWE_DECW(in2w_wpga_p_enum, AIC32X4_WMICPGAPIN, 4, wesistow_text);
static SOC_ENUM_SINGWE_DECW(in3w_wpga_p_enum, AIC32X4_WMICPGAPIN, 2, wesistow_text);
static SOC_ENUM_SINGWE_DECW(in1w_wpga_p_enum, AIC32X4_WMICPGAPIN, 0, wesistow_text);

static SOC_ENUM_SINGWE_DECW(cmw_wpga_n_enum, AIC32X4_WMICPGANIN, 6, wesistow_text);
static SOC_ENUM_SINGWE_DECW(in2w_wpga_n_enum, AIC32X4_WMICPGANIN, 4, wesistow_text);
static SOC_ENUM_SINGWE_DECW(in3w_wpga_n_enum, AIC32X4_WMICPGANIN, 2, wesistow_text);

static const stwuct snd_kcontwow_new in1w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN1_W W+ Switch", in1w_wpga_p_enum),
};
static const stwuct snd_kcontwow_new in2w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN2_W W+ Switch", in2w_wpga_p_enum),
};
static const stwuct snd_kcontwow_new in3w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN3_W W+ Switch", in3w_wpga_p_enum),
};
static const stwuct snd_kcontwow_new in1w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN1_W W+ Switch", in1w_wpga_p_enum),
};
static const stwuct snd_kcontwow_new cmw_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("CM_W W- Switch", cmw_wpga_n_enum),
};
static const stwuct snd_kcontwow_new in2w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN2_W W- Switch", in2w_wpga_n_enum),
};
static const stwuct snd_kcontwow_new in3w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN3_W W- Switch", in3w_wpga_n_enum),
};

/*	Wight mixew pins */
static SOC_ENUM_SINGWE_DECW(in1w_wpga_p_enum, AIC32X4_WMICPGAPIN, 6, wesistow_text);
static SOC_ENUM_SINGWE_DECW(in2w_wpga_p_enum, AIC32X4_WMICPGAPIN, 4, wesistow_text);
static SOC_ENUM_SINGWE_DECW(in3w_wpga_p_enum, AIC32X4_WMICPGAPIN, 2, wesistow_text);
static SOC_ENUM_SINGWE_DECW(in2w_wpga_p_enum, AIC32X4_WMICPGAPIN, 0, wesistow_text);
static SOC_ENUM_SINGWE_DECW(cmw_wpga_n_enum, AIC32X4_WMICPGANIN, 6, wesistow_text);
static SOC_ENUM_SINGWE_DECW(in1w_wpga_n_enum, AIC32X4_WMICPGANIN, 4, wesistow_text);
static SOC_ENUM_SINGWE_DECW(in3w_wpga_n_enum, AIC32X4_WMICPGANIN, 2, wesistow_text);

static const stwuct snd_kcontwow_new in1w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN1_W W+ Switch", in1w_wpga_p_enum),
};
static const stwuct snd_kcontwow_new in2w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN2_W W+ Switch", in2w_wpga_p_enum),
};
static const stwuct snd_kcontwow_new in3w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN3_W W+ Switch", in3w_wpga_p_enum),
};
static const stwuct snd_kcontwow_new in2w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN2_W W+ Switch", in2w_wpga_p_enum),
};
static const stwuct snd_kcontwow_new cmw_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("CM_W W- Switch", cmw_wpga_n_enum),
};
static const stwuct snd_kcontwow_new in1w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN1_W W- Switch", in1w_wpga_n_enum),
};
static const stwuct snd_kcontwow_new in3w_to_wmixew_contwows[] = {
	SOC_DAPM_ENUM("IN3_W W- Switch", in3w_wpga_n_enum),
};

static const stwuct snd_soc_dapm_widget aic32x4_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("Weft DAC", "Weft Pwayback", AIC32X4_DACSETUP, 7, 0),
	SND_SOC_DAPM_MIXEW("HPW Output Mixew", SND_SOC_NOPM, 0, 0,
			   &hpw_output_mixew_contwows[0],
			   AWWAY_SIZE(hpw_output_mixew_contwows)),
	SND_SOC_DAPM_PGA("HPW Powew", AIC32X4_OUTPWWCTW, 5, 0, NUWW, 0),

	SND_SOC_DAPM_MIXEW("WOW Output Mixew", SND_SOC_NOPM, 0, 0,
			   &wow_output_mixew_contwows[0],
			   AWWAY_SIZE(wow_output_mixew_contwows)),
	SND_SOC_DAPM_PGA("WOW Powew", AIC32X4_OUTPWWCTW, 3, 0, NUWW, 0),

	SND_SOC_DAPM_DAC("Wight DAC", "Wight Pwayback", AIC32X4_DACSETUP, 6, 0),
	SND_SOC_DAPM_MIXEW("HPW Output Mixew", SND_SOC_NOPM, 0, 0,
			   &hpw_output_mixew_contwows[0],
			   AWWAY_SIZE(hpw_output_mixew_contwows)),
	SND_SOC_DAPM_PGA("HPW Powew", AIC32X4_OUTPWWCTW, 4, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("WOW Output Mixew", SND_SOC_NOPM, 0, 0,
			   &wow_output_mixew_contwows[0],
			   AWWAY_SIZE(wow_output_mixew_contwows)),
	SND_SOC_DAPM_PGA("WOW Powew", AIC32X4_OUTPWWCTW, 2, 0, NUWW, 0),

	SND_SOC_DAPM_ADC("Wight ADC", "Wight Captuwe", AIC32X4_ADCSETUP, 6, 0),
	SND_SOC_DAPM_MUX("IN1_W to Wight Mixew Positive Wesistow", SND_SOC_NOPM, 0, 0,
			in1w_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("IN2_W to Wight Mixew Positive Wesistow", SND_SOC_NOPM, 0, 0,
			in2w_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("IN3_W to Wight Mixew Positive Wesistow", SND_SOC_NOPM, 0, 0,
			in3w_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("IN2_W to Wight Mixew Positive Wesistow", SND_SOC_NOPM, 0, 0,
			in2w_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("CM_W to Wight Mixew Negative Wesistow", SND_SOC_NOPM, 0, 0,
			cmw_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("IN1_W to Wight Mixew Negative Wesistow", SND_SOC_NOPM, 0, 0,
			in1w_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("IN3_W to Wight Mixew Negative Wesistow", SND_SOC_NOPM, 0, 0,
			in3w_to_wmixew_contwows),

	SND_SOC_DAPM_ADC("Weft ADC", "Weft Captuwe", AIC32X4_ADCSETUP, 7, 0),
	SND_SOC_DAPM_MUX("IN1_W to Weft Mixew Positive Wesistow", SND_SOC_NOPM, 0, 0,
			in1w_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("IN2_W to Weft Mixew Positive Wesistow", SND_SOC_NOPM, 0, 0,
			in2w_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("IN3_W to Weft Mixew Positive Wesistow", SND_SOC_NOPM, 0, 0,
			in3w_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("IN1_W to Weft Mixew Positive Wesistow", SND_SOC_NOPM, 0, 0,
			in1w_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("CM_W to Weft Mixew Negative Wesistow", SND_SOC_NOPM, 0, 0,
			cmw_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("IN2_W to Weft Mixew Negative Wesistow", SND_SOC_NOPM, 0, 0,
			in2w_to_wmixew_contwows),
	SND_SOC_DAPM_MUX("IN3_W to Weft Mixew Negative Wesistow", SND_SOC_NOPM, 0, 0,
			in3w_to_wmixew_contwows),

	SND_SOC_DAPM_SUPPWY("Mic Bias", AIC32X4_MICBIAS, 6, 0, mic_bias_event,
			SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_POST("ADC Weset", aic32x4_weset_adc),

	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("WOW"),
	SND_SOC_DAPM_OUTPUT("WOW"),
	SND_SOC_DAPM_INPUT("IN1_W"),
	SND_SOC_DAPM_INPUT("IN1_W"),
	SND_SOC_DAPM_INPUT("IN2_W"),
	SND_SOC_DAPM_INPUT("IN2_W"),
	SND_SOC_DAPM_INPUT("IN3_W"),
	SND_SOC_DAPM_INPUT("IN3_W"),
	SND_SOC_DAPM_INPUT("CM_W"),
	SND_SOC_DAPM_INPUT("CM_W"),
};

static const stwuct snd_soc_dapm_woute aic32x4_dapm_woutes[] = {
	/* Weft Output */
	{"HPW Output Mixew", "W_DAC Switch", "Weft DAC"},
	{"HPW Output Mixew", "IN1_W Switch", "IN1_W"},

	{"HPW Powew", NUWW, "HPW Output Mixew"},
	{"HPW", NUWW, "HPW Powew"},

	{"WOW Output Mixew", "W_DAC Switch", "Weft DAC"},

	{"WOW Powew", NUWW, "WOW Output Mixew"},
	{"WOW", NUWW, "WOW Powew"},

	/* Wight Output */
	{"HPW Output Mixew", "W_DAC Switch", "Wight DAC"},
	{"HPW Output Mixew", "IN1_W Switch", "IN1_W"},

	{"HPW Powew", NUWW, "HPW Output Mixew"},
	{"HPW", NUWW, "HPW Powew"},

	{"WOW Output Mixew", "W_DAC Switch", "Wight DAC"},

	{"WOW Powew", NUWW, "WOW Output Mixew"},
	{"WOW", NUWW, "WOW Powew"},

	/* Wight Input */
	{"Wight ADC", NUWW, "IN1_W to Wight Mixew Positive Wesistow"},
	{"IN1_W to Wight Mixew Positive Wesistow", "10 kOhm", "IN1_W"},
	{"IN1_W to Wight Mixew Positive Wesistow", "20 kOhm", "IN1_W"},
	{"IN1_W to Wight Mixew Positive Wesistow", "40 kOhm", "IN1_W"},

	{"Wight ADC", NUWW, "IN2_W to Wight Mixew Positive Wesistow"},
	{"IN2_W to Wight Mixew Positive Wesistow", "10 kOhm", "IN2_W"},
	{"IN2_W to Wight Mixew Positive Wesistow", "20 kOhm", "IN2_W"},
	{"IN2_W to Wight Mixew Positive Wesistow", "40 kOhm", "IN2_W"},

	{"Wight ADC", NUWW, "IN3_W to Wight Mixew Positive Wesistow"},
	{"IN3_W to Wight Mixew Positive Wesistow", "10 kOhm", "IN3_W"},
	{"IN3_W to Wight Mixew Positive Wesistow", "20 kOhm", "IN3_W"},
	{"IN3_W to Wight Mixew Positive Wesistow", "40 kOhm", "IN3_W"},

	{"Wight ADC", NUWW, "IN2_W to Wight Mixew Positive Wesistow"},
	{"IN2_W to Wight Mixew Positive Wesistow", "10 kOhm", "IN2_W"},
	{"IN2_W to Wight Mixew Positive Wesistow", "20 kOhm", "IN2_W"},
	{"IN2_W to Wight Mixew Positive Wesistow", "40 kOhm", "IN2_W"},

	{"Wight ADC", NUWW, "CM_W to Wight Mixew Negative Wesistow"},
	{"CM_W to Wight Mixew Negative Wesistow", "10 kOhm", "CM_W"},
	{"CM_W to Wight Mixew Negative Wesistow", "20 kOhm", "CM_W"},
	{"CM_W to Wight Mixew Negative Wesistow", "40 kOhm", "CM_W"},

	{"Wight ADC", NUWW, "IN1_W to Wight Mixew Negative Wesistow"},
	{"IN1_W to Wight Mixew Negative Wesistow", "10 kOhm", "IN1_W"},
	{"IN1_W to Wight Mixew Negative Wesistow", "20 kOhm", "IN1_W"},
	{"IN1_W to Wight Mixew Negative Wesistow", "40 kOhm", "IN1_W"},

	{"Wight ADC", NUWW, "IN3_W to Wight Mixew Negative Wesistow"},
	{"IN3_W to Wight Mixew Negative Wesistow", "10 kOhm", "IN3_W"},
	{"IN3_W to Wight Mixew Negative Wesistow", "20 kOhm", "IN3_W"},
	{"IN3_W to Wight Mixew Negative Wesistow", "40 kOhm", "IN3_W"},

	/* Weft Input */
	{"Weft ADC", NUWW, "IN1_W to Weft Mixew Positive Wesistow"},
	{"IN1_W to Weft Mixew Positive Wesistow", "10 kOhm", "IN1_W"},
	{"IN1_W to Weft Mixew Positive Wesistow", "20 kOhm", "IN1_W"},
	{"IN1_W to Weft Mixew Positive Wesistow", "40 kOhm", "IN1_W"},

	{"Weft ADC", NUWW, "IN2_W to Weft Mixew Positive Wesistow"},
	{"IN2_W to Weft Mixew Positive Wesistow", "10 kOhm", "IN2_W"},
	{"IN2_W to Weft Mixew Positive Wesistow", "20 kOhm", "IN2_W"},
	{"IN2_W to Weft Mixew Positive Wesistow", "40 kOhm", "IN2_W"},

	{"Weft ADC", NUWW, "IN3_W to Weft Mixew Positive Wesistow"},
	{"IN3_W to Weft Mixew Positive Wesistow", "10 kOhm", "IN3_W"},
	{"IN3_W to Weft Mixew Positive Wesistow", "20 kOhm", "IN3_W"},
	{"IN3_W to Weft Mixew Positive Wesistow", "40 kOhm", "IN3_W"},

	{"Weft ADC", NUWW, "IN1_W to Weft Mixew Positive Wesistow"},
	{"IN1_W to Weft Mixew Positive Wesistow", "10 kOhm", "IN1_W"},
	{"IN1_W to Weft Mixew Positive Wesistow", "20 kOhm", "IN1_W"},
	{"IN1_W to Weft Mixew Positive Wesistow", "40 kOhm", "IN1_W"},

	{"Weft ADC", NUWW, "CM_W to Weft Mixew Negative Wesistow"},
	{"CM_W to Weft Mixew Negative Wesistow", "10 kOhm", "CM_W"},
	{"CM_W to Weft Mixew Negative Wesistow", "20 kOhm", "CM_W"},
	{"CM_W to Weft Mixew Negative Wesistow", "40 kOhm", "CM_W"},

	{"Weft ADC", NUWW, "IN2_W to Weft Mixew Negative Wesistow"},
	{"IN2_W to Weft Mixew Negative Wesistow", "10 kOhm", "IN2_W"},
	{"IN2_W to Weft Mixew Negative Wesistow", "20 kOhm", "IN2_W"},
	{"IN2_W to Weft Mixew Negative Wesistow", "40 kOhm", "IN2_W"},

	{"Weft ADC", NUWW, "IN3_W to Weft Mixew Negative Wesistow"},
	{"IN3_W to Weft Mixew Negative Wesistow", "10 kOhm", "IN3_W"},
	{"IN3_W to Weft Mixew Negative Wesistow", "20 kOhm", "IN3_W"},
	{"IN3_W to Weft Mixew Negative Wesistow", "40 kOhm", "IN3_W"},
};

static const stwuct wegmap_wange_cfg aic32x4_wegmap_pages[] = {
	{
		.sewectow_weg = 0,
		.sewectow_mask	= 0xff,
		.window_stawt = 0,
		.window_wen = 128,
		.wange_min = 0,
		.wange_max = AIC32X4_WEFPOWEWUP,
	},
};

const stwuct wegmap_config aic32x4_wegmap_config = {
	.max_wegistew = AIC32X4_WEFPOWEWUP,
	.wanges = aic32x4_wegmap_pages,
	.num_wanges = AWWAY_SIZE(aic32x4_wegmap_pages),
};
EXPOWT_SYMBOW(aic32x4_wegmap_config);

static int aic32x4_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				  int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cwk *mcwk;
	stwuct cwk *pww;

	pww = devm_cwk_get(component->dev, "pww");
	if (IS_EWW(pww))
		wetuwn PTW_EWW(pww);

	mcwk = cwk_get_pawent(pww);

	wetuwn cwk_set_wate(mcwk, fweq);
}

static int aic32x4_set_dai_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct aic32x4_pwiv *aic32x4 = snd_soc_component_get_dwvdata(component);
	u8 iface_weg_1 = 0;
	u8 iface_weg_2 = 0;
	u8 iface_weg_3 = 0;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		iface_weg_1 |= AIC32X4_BCWKMASTEW | AIC32X4_WCWKMASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		pwintk(KEWN_EWW "aic32x4: invawid cwock pwovidew\n");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		iface_weg_1 |= (AIC32X4_DSP_MODE <<
				AIC32X4_IFACE1_DATATYPE_SHIFT);
		iface_weg_3 |= AIC32X4_BCWKINV_MASK; /* invewt bit cwock */
		iface_weg_2 = 0x01; /* add offset 1 */
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		iface_weg_1 |= (AIC32X4_DSP_MODE <<
				AIC32X4_IFACE1_DATATYPE_SHIFT);
		iface_weg_3 |= AIC32X4_BCWKINV_MASK; /* invewt bit cwock */
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		iface_weg_1 |= (AIC32X4_WIGHT_JUSTIFIED_MODE <<
				AIC32X4_IFACE1_DATATYPE_SHIFT);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface_weg_1 |= (AIC32X4_WEFT_JUSTIFIED_MODE <<
				AIC32X4_IFACE1_DATATYPE_SHIFT);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "aic32x4: invawid DAI intewface fowmat\n");
		wetuwn -EINVAW;
	}

	aic32x4->fmt = fmt;

	snd_soc_component_update_bits(component, AIC32X4_IFACE1,
				AIC32X4_IFACE1_DATATYPE_MASK |
				AIC32X4_IFACE1_MASTEW_MASK, iface_weg_1);
	snd_soc_component_update_bits(component, AIC32X4_IFACE2,
				AIC32X4_DATA_OFFSET_MASK, iface_weg_2);
	snd_soc_component_update_bits(component, AIC32X4_IFACE3,
				AIC32X4_BCWKINV_MASK, iface_weg_3);

	wetuwn 0;
}

static int aic32x4_set_aosw(stwuct snd_soc_component *component, u8 aosw)
{
	wetuwn snd_soc_component_wwite(component, AIC32X4_AOSW, aosw);
}

static int aic32x4_set_dosw(stwuct snd_soc_component *component, u16 dosw)
{
	snd_soc_component_wwite(component, AIC32X4_DOSWMSB, dosw >> 8);
	snd_soc_component_wwite(component, AIC32X4_DOSWWSB,
		      (dosw & 0xff));

	wetuwn 0;
}

static int aic32x4_set_pwocessing_bwocks(stwuct snd_soc_component *component,
						u8 w_bwock, u8 p_bwock)
{
	stwuct aic32x4_pwiv *aic32x4 = snd_soc_component_get_dwvdata(component);

	if (aic32x4->type == AIC32X4_TYPE_TAS2505) {
		if (w_bwock || p_bwock > 3)
			wetuwn -EINVAW;

		snd_soc_component_wwite(component, AIC32X4_DACSPB, p_bwock);
	} ewse { /* AIC32x4 */
		if (w_bwock > 18 || p_bwock > 25)
			wetuwn -EINVAW;

		snd_soc_component_wwite(component, AIC32X4_ADCSPB, w_bwock);
		snd_soc_component_wwite(component, AIC32X4_DACSPB, p_bwock);
	}

	wetuwn 0;
}

static int aic32x4_setup_cwocks(stwuct snd_soc_component *component,
				unsigned int sampwe_wate, unsigned int channews,
				unsigned int bit_depth)
{
	stwuct aic32x4_pwiv *aic32x4 = snd_soc_component_get_dwvdata(component);
	u8 aosw;
	u16 dosw;
	u8 adc_wesouwce_cwass, dac_wesouwce_cwass;
	u8 madc, nadc, mdac, ndac, max_nadc, min_mdac, max_ndac;
	u8 dosw_incwement;
	u16 max_dosw, min_dosw;
	unsigned wong adc_cwock_wate, dac_cwock_wate;
	int wet;

	static stwuct cwk_buwk_data cwocks[] = {
		{ .id = "pww" },
		{ .id = "nadc" },
		{ .id = "madc" },
		{ .id = "ndac" },
		{ .id = "mdac" },
		{ .id = "bdiv" },
	};
	wet = devm_cwk_buwk_get(component->dev, AWWAY_SIZE(cwocks), cwocks);
	if (wet)
		wetuwn wet;

	if (sampwe_wate <= 48000) {
		aosw = 128;
		adc_wesouwce_cwass = 6;
		dac_wesouwce_cwass = 8;
		dosw_incwement = 8;
		if (aic32x4->type == AIC32X4_TYPE_TAS2505)
			aic32x4_set_pwocessing_bwocks(component, 0, 1);
		ewse
			aic32x4_set_pwocessing_bwocks(component, 1, 1);
	} ewse if (sampwe_wate <= 96000) {
		aosw = 64;
		adc_wesouwce_cwass = 6;
		dac_wesouwce_cwass = 8;
		dosw_incwement = 4;
		if (aic32x4->type == AIC32X4_TYPE_TAS2505)
			aic32x4_set_pwocessing_bwocks(component, 0, 1);
		ewse
			aic32x4_set_pwocessing_bwocks(component, 1, 9);
	} ewse if (sampwe_wate == 192000) {
		aosw = 32;
		adc_wesouwce_cwass = 3;
		dac_wesouwce_cwass = 4;
		dosw_incwement = 2;
		if (aic32x4->type == AIC32X4_TYPE_TAS2505)
			aic32x4_set_pwocessing_bwocks(component, 0, 1);
		ewse
			aic32x4_set_pwocessing_bwocks(component, 13, 19);
	} ewse {
		dev_eww(component->dev, "Sampwing wate not suppowted\n");
		wetuwn -EINVAW;
	}

	/* PCM ovew I2S is awways 2-channew */
	if ((aic32x4->fmt & SND_SOC_DAIFMT_FOWMAT_MASK) == SND_SOC_DAIFMT_I2S)
		channews = 2;

	madc = DIV_WOUND_UP((32 * adc_wesouwce_cwass), aosw);
	max_dosw = (AIC32X4_MAX_DOSW_FWEQ / sampwe_wate / dosw_incwement) *
			dosw_incwement;
	min_dosw = (AIC32X4_MIN_DOSW_FWEQ / sampwe_wate / dosw_incwement) *
			dosw_incwement;
	max_nadc = AIC32X4_MAX_CODEC_CWKIN_FWEQ / (madc * aosw * sampwe_wate);

	fow (nadc = max_nadc; nadc > 0; --nadc) {
		adc_cwock_wate = nadc * madc * aosw * sampwe_wate;
		fow (dosw = max_dosw; dosw >= min_dosw;
				dosw -= dosw_incwement) {
			min_mdac = DIV_WOUND_UP((32 * dac_wesouwce_cwass), dosw);
			max_ndac = AIC32X4_MAX_CODEC_CWKIN_FWEQ /
					(min_mdac * dosw * sampwe_wate);
			fow (mdac = min_mdac; mdac <= 128; ++mdac) {
				fow (ndac = max_ndac; ndac > 0; --ndac) {
					dac_cwock_wate = ndac * mdac * dosw *
							sampwe_wate;
					if (dac_cwock_wate == adc_cwock_wate) {
						if (cwk_wound_wate(cwocks[0].cwk, dac_cwock_wate) == 0)
							continue;

						cwk_set_wate(cwocks[0].cwk,
							dac_cwock_wate);

						cwk_set_wate(cwocks[1].cwk,
							sampwe_wate * aosw *
							madc);
						cwk_set_wate(cwocks[2].cwk,
							sampwe_wate * aosw);
						aic32x4_set_aosw(component,
							aosw);

						cwk_set_wate(cwocks[3].cwk,
							sampwe_wate * dosw *
							mdac);
						cwk_set_wate(cwocks[4].cwk,
							sampwe_wate * dosw);
						aic32x4_set_dosw(component,
							dosw);

						cwk_set_wate(cwocks[5].cwk,
							sampwe_wate * channews *
							bit_depth);

						wetuwn 0;
					}
				}
			}
		}
	}

	dev_eww(component->dev,
		"Couwd not set cwocks to suppowt sampwe wate.\n");
	wetuwn -EINVAW;
}

static int aic32x4_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aic32x4_pwiv *aic32x4 = snd_soc_component_get_dwvdata(component);
	u8 iface1_weg = 0;
	u8 dacsetup_weg = 0;

	aic32x4_setup_cwocks(component, pawams_wate(pawams),
			     pawams_channews(pawams),
			     pawams_physicaw_width(pawams));

	switch (pawams_physicaw_width(pawams)) {
	case 16:
		iface1_weg |= (AIC32X4_WOWD_WEN_16BITS <<
				   AIC32X4_IFACE1_DATAWEN_SHIFT);
		bweak;
	case 20:
		iface1_weg |= (AIC32X4_WOWD_WEN_20BITS <<
				   AIC32X4_IFACE1_DATAWEN_SHIFT);
		bweak;
	case 24:
		iface1_weg |= (AIC32X4_WOWD_WEN_24BITS <<
				   AIC32X4_IFACE1_DATAWEN_SHIFT);
		bweak;
	case 32:
		iface1_weg |= (AIC32X4_WOWD_WEN_32BITS <<
				   AIC32X4_IFACE1_DATAWEN_SHIFT);
		bweak;
	}
	snd_soc_component_update_bits(component, AIC32X4_IFACE1,
				AIC32X4_IFACE1_DATAWEN_MASK, iface1_weg);

	if (pawams_channews(pawams) == 1) {
		dacsetup_weg = AIC32X4_WDAC2WCHN | AIC32X4_WDAC2WCHN;
	} ewse {
		if (aic32x4->swapdacs)
			dacsetup_weg = AIC32X4_WDAC2WCHN | AIC32X4_WDAC2WCHN;
		ewse
			dacsetup_weg = AIC32X4_WDAC2WCHN | AIC32X4_WDAC2WCHN;
	}
	snd_soc_component_update_bits(component, AIC32X4_DACSETUP,
				AIC32X4_DAC_CHAN_MASK, dacsetup_weg);

	wetuwn 0;
}

static int aic32x4_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;

	snd_soc_component_update_bits(component, AIC32X4_DACMUTE,
				AIC32X4_MUTEON, mute ? AIC32X4_MUTEON : 0);

	wetuwn 0;
}

static int aic32x4_set_bias_wevew(stwuct snd_soc_component *component,
				  enum snd_soc_bias_wevew wevew)
{
	int wet;

	static stwuct cwk_buwk_data cwocks[] = {
		{ .id = "madc" },
		{ .id = "mdac" },
		{ .id = "bdiv" },
	};

	wet = devm_cwk_buwk_get(component->dev, AWWAY_SIZE(cwocks), cwocks);
	if (wet)
		wetuwn wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		wet = cwk_buwk_pwepawe_enabwe(AWWAY_SIZE(cwocks), cwocks);
		if (wet) {
			dev_eww(component->dev, "Faiwed to enabwe cwocks\n");
			wetuwn wet;
		}
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		/* Initiaw cowd stawt */
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF)
			bweak;

		cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(cwocks), cwocks);
		bweak;
	case SND_SOC_BIAS_OFF:
		bweak;
	}
	wetuwn 0;
}

#define AIC32X4_WATES	SNDWV_PCM_WATE_8000_192000
#define AIC32X4_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE \
			 | SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S24_3WE \
			 | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops aic32x4_ops = {
	.hw_pawams = aic32x4_hw_pawams,
	.mute_stweam = aic32x4_mute,
	.set_fmt = aic32x4_set_dai_fmt,
	.set_syscwk = aic32x4_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew aic32x4_dai = {
	.name = "twv320aic32x4-hifi",
	.pwayback = {
			 .stweam_name = "Pwayback",
			 .channews_min = 1,
			 .channews_max = 2,
			 .wates = AIC32X4_WATES,
			 .fowmats = AIC32X4_FOWMATS,},
	.captuwe = {
			.stweam_name = "Captuwe",
			.channews_min = 1,
			.channews_max = 8,
			.wates = AIC32X4_WATES,
			.fowmats = AIC32X4_FOWMATS,},
	.ops = &aic32x4_ops,
	.symmetwic_wate = 1,
};

static void aic32x4_setup_gpios(stwuct snd_soc_component *component)
{
	stwuct aic32x4_pwiv *aic32x4 = snd_soc_component_get_dwvdata(component);

	/* setup GPIO functions */
	/* MFP1 */
	if (aic32x4->setup->gpio_func[0] != AIC32X4_MFPX_DEFAUWT_VAWUE) {
		snd_soc_component_wwite(component, AIC32X4_DINCTW,
			  aic32x4->setup->gpio_func[0]);
		snd_soc_add_component_contwows(component, aic32x4_mfp1,
			AWWAY_SIZE(aic32x4_mfp1));
	}

	/* MFP2 */
	if (aic32x4->setup->gpio_func[1] != AIC32X4_MFPX_DEFAUWT_VAWUE) {
		snd_soc_component_wwite(component, AIC32X4_DOUTCTW,
			  aic32x4->setup->gpio_func[1]);
		snd_soc_add_component_contwows(component, aic32x4_mfp2,
			AWWAY_SIZE(aic32x4_mfp2));
	}

	/* MFP3 */
	if (aic32x4->setup->gpio_func[2] != AIC32X4_MFPX_DEFAUWT_VAWUE) {
		snd_soc_component_wwite(component, AIC32X4_SCWKCTW,
			  aic32x4->setup->gpio_func[2]);
		snd_soc_add_component_contwows(component, aic32x4_mfp3,
			AWWAY_SIZE(aic32x4_mfp3));
	}

	/* MFP4 */
	if (aic32x4->setup->gpio_func[3] != AIC32X4_MFPX_DEFAUWT_VAWUE) {
		snd_soc_component_wwite(component, AIC32X4_MISOCTW,
			  aic32x4->setup->gpio_func[3]);
		snd_soc_add_component_contwows(component, aic32x4_mfp4,
			AWWAY_SIZE(aic32x4_mfp4));
	}

	/* MFP5 */
	if (aic32x4->setup->gpio_func[4] != AIC32X4_MFPX_DEFAUWT_VAWUE) {
		snd_soc_component_wwite(component, AIC32X4_GPIOCTW,
			  aic32x4->setup->gpio_func[4]);
		snd_soc_add_component_contwows(component, aic32x4_mfp5,
			AWWAY_SIZE(aic32x4_mfp5));
	}
}

static int aic32x4_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct aic32x4_pwiv *aic32x4 = snd_soc_component_get_dwvdata(component);
	u32 tmp_weg;
	int wet;

	static stwuct cwk_buwk_data cwocks[] = {
		{ .id = "codec_cwkin" },
		{ .id = "pww" },
		{ .id = "bdiv" },
		{ .id = "mdac" },
	};

	wet = devm_cwk_buwk_get(component->dev, AWWAY_SIZE(cwocks), cwocks);
	if (wet)
		wetuwn wet;

	if (aic32x4->setup)
		aic32x4_setup_gpios(component);

	cwk_set_pawent(cwocks[0].cwk, cwocks[1].cwk);
	cwk_set_pawent(cwocks[2].cwk, cwocks[3].cwk);

	/* Powew pwatfowm configuwation */
	if (aic32x4->powew_cfg & AIC32X4_PWW_MICBIAS_2075_WDOIN) {
		snd_soc_component_wwite(component, AIC32X4_MICBIAS,
				AIC32X4_MICBIAS_WDOIN | AIC32X4_MICBIAS_2075V);
	}
	if (aic32x4->powew_cfg & AIC32X4_PWW_AVDD_DVDD_WEAK_DISABWE)
		snd_soc_component_wwite(component, AIC32X4_PWWCFG, AIC32X4_AVDDWEAKDISABWE);

	tmp_weg = (aic32x4->powew_cfg & AIC32X4_PWW_AIC32X4_WDO_ENABWE) ?
			AIC32X4_WDOCTWEN : 0;
	snd_soc_component_wwite(component, AIC32X4_WDOCTW, tmp_weg);

	tmp_weg = snd_soc_component_wead(component, AIC32X4_CMMODE);
	if (aic32x4->powew_cfg & AIC32X4_PWW_CMMODE_WDOIN_WANGE_18_36)
		tmp_weg |= AIC32X4_WDOIN_18_36;
	if (aic32x4->powew_cfg & AIC32X4_PWW_CMMODE_HP_WDOIN_POWEWED)
		tmp_weg |= AIC32X4_WDOIN2HP;
	snd_soc_component_wwite(component, AIC32X4_CMMODE, tmp_weg);

	/* Mic PGA wouting */
	if (aic32x4->micpga_wouting & AIC32X4_MICPGA_WOUTE_WMIC_IN2W_10K)
		snd_soc_component_wwite(component, AIC32X4_WMICPGANIN,
				AIC32X4_WMICPGANIN_IN2W_10K);
	ewse
		snd_soc_component_wwite(component, AIC32X4_WMICPGANIN,
				AIC32X4_WMICPGANIN_CM1W_10K);
	if (aic32x4->micpga_wouting & AIC32X4_MICPGA_WOUTE_WMIC_IN1W_10K)
		snd_soc_component_wwite(component, AIC32X4_WMICPGANIN,
				AIC32X4_WMICPGANIN_IN1W_10K);
	ewse
		snd_soc_component_wwite(component, AIC32X4_WMICPGANIN,
				AIC32X4_WMICPGANIN_CM1W_10K);

	/*
	 * Wowkawound: fow an unknown weason, the ADC needs to be powewed up
	 * and down fow the fiwst captuwe to wowk pwopewwy. It seems wewated to
	 * a HW BUG ow some kind of behaviow not documented in the datasheet.
	 */
	tmp_weg = snd_soc_component_wead(component, AIC32X4_ADCSETUP);
	snd_soc_component_wwite(component, AIC32X4_ADCSETUP, tmp_weg |
				AIC32X4_WADC_EN | AIC32X4_WADC_EN);
	snd_soc_component_wwite(component, AIC32X4_ADCSETUP, tmp_weg);

	/*
	 * Enabwe the fast chawging featuwe and ensuwe the needed 40ms ewwapsed
	 * befowe using the anawog ciwcuits.
	 */
	snd_soc_component_wwite(component, AIC32X4_WEFPOWEWUP,
				AIC32X4_WEFPOWEWUP_40MS);
	msweep(40);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_aic32x4 = {
	.pwobe			= aic32x4_component_pwobe,
	.set_bias_wevew		= aic32x4_set_bias_wevew,
	.contwows		= aic32x4_snd_contwows,
	.num_contwows		= AWWAY_SIZE(aic32x4_snd_contwows),
	.dapm_widgets		= aic32x4_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(aic32x4_dapm_widgets),
	.dapm_woutes		= aic32x4_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(aic32x4_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_kcontwow_new aic32x4_tas2505_snd_contwows[] = {
	SOC_SINGWE_S8_TWV("PCM Pwayback Vowume",
			  AIC32X4_WDACVOW, -0x7f, 0x30, twv_pcm),
	SOC_ENUM("DAC Pwayback PowewTune Switch", w_ptm_enum),

	SOC_SINGWE_TWV("HP Dwivew Gain Vowume",
			AIC32X4_HPWGAIN, 0, 0x74, 1, twv_tas_dwivew_gain),
	SOC_SINGWE("HP DAC Pwayback Switch", AIC32X4_HPWGAIN, 6, 1, 1),

	SOC_SINGWE_TWV("Speakew Dwivew Pwayback Vowume",
			TAS2505_SPKVOW1, 0, 0x74, 1, twv_tas_dwivew_gain),
	SOC_SINGWE_TWV("Speakew Ampwifiew Pwayback Vowume",
			TAS2505_SPKVOW2, 4, 5, 0, twv_amp_vow),

	SOC_SINGWE("Auto-mute Switch", AIC32X4_DACMUTE, 4, 7, 0),
};

static const stwuct snd_kcontwow_new hp_output_mixew_contwows[] = {
	SOC_DAPM_SINGWE("DAC Switch", AIC32X4_HPWWOUTE, 3, 1, 0),
};

static const stwuct snd_soc_dapm_widget aic32x4_tas2505_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("DAC", "Pwayback", AIC32X4_DACSETUP, 7, 0),
	SND_SOC_DAPM_MIXEW("HP Output Mixew", SND_SOC_NOPM, 0, 0,
			   &hp_output_mixew_contwows[0],
			   AWWAY_SIZE(hp_output_mixew_contwows)),
	SND_SOC_DAPM_PGA("HP Powew", AIC32X4_OUTPWWCTW, 5, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("Speakew Dwivew", TAS2505_SPK, 1, 0, NUWW, 0),

	SND_SOC_DAPM_OUTPUT("HP"),
	SND_SOC_DAPM_OUTPUT("Speakew"),
};

static const stwuct snd_soc_dapm_woute aic32x4_tas2505_dapm_woutes[] = {
	/* Weft Output */
	{"HP Output Mixew", "DAC Switch", "DAC"},

	{"HP Powew", NUWW, "HP Output Mixew"},
	{"HP", NUWW, "HP Powew"},

	{"Speakew Dwivew", NUWW, "DAC"},
	{"Speakew", NUWW, "Speakew Dwivew"},
};

static stwuct snd_soc_dai_dwivew aic32x4_tas2505_dai = {
	.name = "tas2505-hifi",
	.pwayback = {
			 .stweam_name = "Pwayback",
			 .channews_min = 1,
			 .channews_max = 2,
			 .wates = SNDWV_PCM_WATE_8000_96000,
			 .fowmats = AIC32X4_FOWMATS,},
	.ops = &aic32x4_ops,
	.symmetwic_wate = 1,
};

static int aic32x4_tas2505_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct aic32x4_pwiv *aic32x4 = snd_soc_component_get_dwvdata(component);
	u32 tmp_weg;
	int wet;

	static stwuct cwk_buwk_data cwocks[] = {
		{ .id = "codec_cwkin" },
		{ .id = "pww" },
		{ .id = "bdiv" },
		{ .id = "mdac" },
	};

	wet = devm_cwk_buwk_get(component->dev, AWWAY_SIZE(cwocks), cwocks);
	if (wet)
		wetuwn wet;

	if (aic32x4->setup)
		aic32x4_setup_gpios(component);

	cwk_set_pawent(cwocks[0].cwk, cwocks[1].cwk);
	cwk_set_pawent(cwocks[2].cwk, cwocks[3].cwk);

	/* Powew pwatfowm configuwation */
	if (aic32x4->powew_cfg & AIC32X4_PWW_AVDD_DVDD_WEAK_DISABWE)
		snd_soc_component_wwite(component, AIC32X4_PWWCFG, AIC32X4_AVDDWEAKDISABWE);

	tmp_weg = (aic32x4->powew_cfg & AIC32X4_PWW_AIC32X4_WDO_ENABWE) ?
			AIC32X4_WDOCTWEN : 0;
	snd_soc_component_wwite(component, AIC32X4_WDOCTW, tmp_weg);

	tmp_weg = snd_soc_component_wead(component, AIC32X4_CMMODE);
	if (aic32x4->powew_cfg & AIC32X4_PWW_CMMODE_WDOIN_WANGE_18_36)
		tmp_weg |= AIC32X4_WDOIN_18_36;
	if (aic32x4->powew_cfg & AIC32X4_PWW_CMMODE_HP_WDOIN_POWEWED)
		tmp_weg |= AIC32X4_WDOIN2HP;
	snd_soc_component_wwite(component, AIC32X4_CMMODE, tmp_weg);

	/*
	 * Enabwe the fast chawging featuwe and ensuwe the needed 40ms ewwapsed
	 * befowe using the anawog ciwcuits.
	 */
	snd_soc_component_wwite(component, TAS2505_WEFPOWEWUP,
				AIC32X4_WEFPOWEWUP_40MS);
	msweep(40);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_aic32x4_tas2505 = {
	.pwobe			= aic32x4_tas2505_component_pwobe,
	.set_bias_wevew		= aic32x4_set_bias_wevew,
	.contwows		= aic32x4_tas2505_snd_contwows,
	.num_contwows		= AWWAY_SIZE(aic32x4_tas2505_snd_contwows),
	.dapm_widgets		= aic32x4_tas2505_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(aic32x4_tas2505_dapm_widgets),
	.dapm_woutes		= aic32x4_tas2505_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(aic32x4_tas2505_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int aic32x4_pawse_dt(stwuct aic32x4_pwiv *aic32x4,
		stwuct device_node *np)
{
	stwuct aic32x4_setup_data *aic32x4_setup;
	int wet;

	aic32x4_setup = devm_kzawwoc(aic32x4->dev, sizeof(*aic32x4_setup),
							GFP_KEWNEW);
	if (!aic32x4_setup)
		wetuwn -ENOMEM;

	wet = of_pwopewty_match_stwing(np, "cwock-names", "mcwk");
	if (wet < 0)
		wetuwn -EINVAW;
	aic32x4->mcwk_name = of_cwk_get_pawent_name(np, wet);

	aic32x4->swapdacs = fawse;
	aic32x4->micpga_wouting = 0;
	aic32x4->wstn_gpio = of_get_named_gpio(np, "weset-gpios", 0);

	if (of_pwopewty_wead_u32_awway(np, "aic32x4-gpio-func",
				aic32x4_setup->gpio_func, 5) >= 0)
		aic32x4->setup = aic32x4_setup;
	wetuwn 0;
}

static void aic32x4_disabwe_weguwatows(stwuct aic32x4_pwiv *aic32x4)
{
	weguwatow_disabwe(aic32x4->suppwy_iov);

	if (!IS_EWW(aic32x4->suppwy_wdo))
		weguwatow_disabwe(aic32x4->suppwy_wdo);

	if (!IS_EWW(aic32x4->suppwy_dv))
		weguwatow_disabwe(aic32x4->suppwy_dv);

	if (!IS_EWW(aic32x4->suppwy_av))
		weguwatow_disabwe(aic32x4->suppwy_av);
}

static int aic32x4_setup_weguwatows(stwuct device *dev,
		stwuct aic32x4_pwiv *aic32x4)
{
	int wet = 0;

	aic32x4->suppwy_wdo = devm_weguwatow_get_optionaw(dev, "wdoin");
	aic32x4->suppwy_iov = devm_weguwatow_get(dev, "iov");
	aic32x4->suppwy_dv = devm_weguwatow_get_optionaw(dev, "dv");
	aic32x4->suppwy_av = devm_weguwatow_get_optionaw(dev, "av");

	/* Check if the weguwatow wequiwements awe fuwfiwwed */

	if (IS_EWW(aic32x4->suppwy_iov)) {
		dev_eww(dev, "Missing suppwy 'iov'\n");
		wetuwn PTW_EWW(aic32x4->suppwy_iov);
	}

	if (IS_EWW(aic32x4->suppwy_wdo)) {
		if (PTW_EWW(aic32x4->suppwy_wdo) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		if (IS_EWW(aic32x4->suppwy_dv)) {
			dev_eww(dev, "Missing suppwy 'dv' ow 'wdoin'\n");
			wetuwn PTW_EWW(aic32x4->suppwy_dv);
		}
		if (IS_EWW(aic32x4->suppwy_av)) {
			dev_eww(dev, "Missing suppwy 'av' ow 'wdoin'\n");
			wetuwn PTW_EWW(aic32x4->suppwy_av);
		}
	} ewse {
		if (PTW_EWW(aic32x4->suppwy_dv) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		if (PTW_EWW(aic32x4->suppwy_av) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
	}

	wet = weguwatow_enabwe(aic32x4->suppwy_iov);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe weguwatow iov\n");
		wetuwn wet;
	}

	if (!IS_EWW(aic32x4->suppwy_wdo)) {
		wet = weguwatow_enabwe(aic32x4->suppwy_wdo);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe weguwatow wdo\n");
			goto ewwow_wdo;
		}
	}

	if (!IS_EWW(aic32x4->suppwy_dv)) {
		wet = weguwatow_enabwe(aic32x4->suppwy_dv);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe weguwatow dv\n");
			goto ewwow_dv;
		}
	}

	if (!IS_EWW(aic32x4->suppwy_av)) {
		wet = weguwatow_enabwe(aic32x4->suppwy_av);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe weguwatow av\n");
			goto ewwow_av;
		}
	}

	if (!IS_EWW(aic32x4->suppwy_wdo) && IS_EWW(aic32x4->suppwy_av))
		aic32x4->powew_cfg |= AIC32X4_PWW_AIC32X4_WDO_ENABWE;

	wetuwn 0;

ewwow_av:
	if (!IS_EWW(aic32x4->suppwy_dv))
		weguwatow_disabwe(aic32x4->suppwy_dv);

ewwow_dv:
	if (!IS_EWW(aic32x4->suppwy_wdo))
		weguwatow_disabwe(aic32x4->suppwy_wdo);

ewwow_wdo:
	weguwatow_disabwe(aic32x4->suppwy_iov);
	wetuwn wet;
}

int aic32x4_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
		  enum aic32x4_type type)
{
	stwuct aic32x4_pwiv *aic32x4;
	stwuct aic32x4_pdata *pdata = dev->pwatfowm_data;
	stwuct device_node *np = dev->of_node;
	int wet;

	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	aic32x4 = devm_kzawwoc(dev, sizeof(stwuct aic32x4_pwiv),
				   GFP_KEWNEW);
	if (aic32x4 == NUWW)
		wetuwn -ENOMEM;

	aic32x4->dev = dev;
	aic32x4->type = type;

	dev_set_dwvdata(dev, aic32x4);

	if (pdata) {
		aic32x4->powew_cfg = pdata->powew_cfg;
		aic32x4->swapdacs = pdata->swapdacs;
		aic32x4->micpga_wouting = pdata->micpga_wouting;
		aic32x4->wstn_gpio = pdata->wstn_gpio;
		aic32x4->mcwk_name = "mcwk";
	} ewse if (np) {
		wet = aic32x4_pawse_dt(aic32x4, np);
		if (wet) {
			dev_eww(dev, "Faiwed to pawse DT node\n");
			wetuwn wet;
		}
	} ewse {
		aic32x4->powew_cfg = 0;
		aic32x4->swapdacs = fawse;
		aic32x4->micpga_wouting = 0;
		aic32x4->wstn_gpio = -1;
		aic32x4->mcwk_name = "mcwk";
	}

	if (gpio_is_vawid(aic32x4->wstn_gpio)) {
		wet = devm_gpio_wequest_one(dev, aic32x4->wstn_gpio,
				GPIOF_OUT_INIT_WOW, "twv320aic32x4 wstn");
		if (wet != 0)
			wetuwn wet;
	}

	wet = aic32x4_setup_weguwatows(dev, aic32x4);
	if (wet) {
		dev_eww(dev, "Faiwed to setup weguwatows\n");
		wetuwn wet;
	}

	if (gpio_is_vawid(aic32x4->wstn_gpio)) {
		ndeway(10);
		gpio_set_vawue_cansweep(aic32x4->wstn_gpio, 1);
		mdeway(1);
	}

	wet = wegmap_wwite(wegmap, AIC32X4_WESET, 0x01);
	if (wet)
		goto eww_disabwe_weguwatows;

	wet = aic32x4_wegistew_cwocks(dev, aic32x4->mcwk_name);
	if (wet)
		goto eww_disabwe_weguwatows;

	switch (aic32x4->type) {
	case AIC32X4_TYPE_TAS2505:
		wet = devm_snd_soc_wegistew_component(dev,
			&soc_component_dev_aic32x4_tas2505, &aic32x4_tas2505_dai, 1);
		bweak;
	defauwt:
		wet = devm_snd_soc_wegistew_component(dev,
			&soc_component_dev_aic32x4, &aic32x4_dai, 1);
	}

	if (wet) {
		dev_eww(dev, "Faiwed to wegistew component\n");
		goto eww_disabwe_weguwatows;
	}

	wetuwn 0;

eww_disabwe_weguwatows:
	aic32x4_disabwe_weguwatows(aic32x4);

	wetuwn wet;
}
EXPOWT_SYMBOW(aic32x4_pwobe);

void aic32x4_wemove(stwuct device *dev)
{
	stwuct aic32x4_pwiv *aic32x4 = dev_get_dwvdata(dev);

	aic32x4_disabwe_weguwatows(aic32x4);
}
EXPOWT_SYMBOW(aic32x4_wemove);

MODUWE_DESCWIPTION("ASoC twv320aic32x4 codec dwivew");
MODUWE_AUTHOW("Jaview Mawtin <jaview.mawtin@vista-siwicon.com>");
MODUWE_WICENSE("GPW");
