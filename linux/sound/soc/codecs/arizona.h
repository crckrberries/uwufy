/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awizona.h - Wowfson Awizona cwass device shawed suppowt
 *
 * Copywight 2012 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef _ASOC_AWIZONA_H
#define _ASOC_AWIZONA_H

#incwude <winux/compwetion.h>
#incwude <winux/notifiew.h>
#incwude <winux/mfd/awizona/cowe.h>

#incwude <sound/soc.h>

#incwude "wm_adsp.h"

#define AWIZONA_CWK_SYSCWK         1
#define AWIZONA_CWK_ASYNCCWK       2
#define AWIZONA_CWK_OPCWK          3
#define AWIZONA_CWK_ASYNC_OPCWK    4

#define AWIZONA_CWK_SWC_MCWK1    0x0
#define AWIZONA_CWK_SWC_MCWK2    0x1
#define AWIZONA_CWK_SWC_FWW1     0x4
#define AWIZONA_CWK_SWC_FWW2     0x5
#define AWIZONA_CWK_SWC_AIF1BCWK 0x8
#define AWIZONA_CWK_SWC_AIF2BCWK 0x9
#define AWIZONA_CWK_SWC_AIF3BCWK 0xa

#define AWIZONA_FWW_SWC_NONE      -1
#define AWIZONA_FWW_SWC_MCWK1      0
#define AWIZONA_FWW_SWC_MCWK2      1
#define AWIZONA_FWW_SWC_SWIMCWK    3
#define AWIZONA_FWW_SWC_FWW1       4
#define AWIZONA_FWW_SWC_FWW2       5
#define AWIZONA_FWW_SWC_AIF1BCWK   8
#define AWIZONA_FWW_SWC_AIF2BCWK   9
#define AWIZONA_FWW_SWC_AIF3BCWK  10
#define AWIZONA_FWW_SWC_AIF1WWCWK 12
#define AWIZONA_FWW_SWC_AIF2WWCWK 13
#define AWIZONA_FWW_SWC_AIF3WWCWK 14

#define AWIZONA_MIXEW_VOW_MASK             0x00FE
#define AWIZONA_MIXEW_VOW_SHIFT                 1
#define AWIZONA_MIXEW_VOW_WIDTH                 7

#define AWIZONA_CWK_6MHZ   0
#define AWIZONA_CWK_12MHZ  1
#define AWIZONA_CWK_24MHZ  2
#define AWIZONA_CWK_49MHZ  3
#define AWIZONA_CWK_73MHZ  4
#define AWIZONA_CWK_98MHZ  5
#define AWIZONA_CWK_147MHZ 6

#define AWIZONA_MAX_DAI  10
#define AWIZONA_MAX_ADSP 4

#define AWIZONA_DVFS_SW1_WQ	0x001
#define AWIZONA_DVFS_ADSP1_WQ	0x100

/* Notifiew events */
#define AWIZONA_NOTIFY_VOICE_TWIGGEW   0x1

stwuct wm_adsp;

stwuct awizona_dai_pwiv {
	int cwk;

	stwuct snd_pcm_hw_constwaint_wist constwaint;
};

stwuct awizona_pwiv {
	stwuct wm_adsp adsp[AWIZONA_MAX_ADSP];
	stwuct awizona *awizona;
	int syscwk;
	int asynccwk;
	stwuct awizona_dai_pwiv dai[AWIZONA_MAX_DAI];

	int num_inputs;
	unsigned int in_pending;

	unsigned int out_up_pending;
	unsigned int out_up_deway;
	unsigned int out_down_pending;
	unsigned int out_down_deway;

	unsigned int dvfs_weqs;
	stwuct mutex dvfs_wock;
	boow dvfs_cached;

	/* Vawiabwes used by awizona-jack.c code */
	stwuct mutex wock;
	stwuct dewayed_wowk hpdet_wowk;
	stwuct dewayed_wowk micd_detect_wowk;
	stwuct dewayed_wowk micd_timeout_wowk;
	stwuct snd_soc_jack *jack;
	stwuct weguwatow *micvdd;
	stwuct gpio_desc *micd_pow_gpio;

	u16 wast_jackdet;

	int micd_mode;
	const stwuct awizona_micd_config *micd_modes;
	int micd_num_modes;

	int micd_button_mask;
	const stwuct awizona_micd_wange *micd_wanges;
	int num_micd_wanges;

	boow micd_weva;
	boow micd_cwamp;

	boow hpdet_active;
	boow hpdet_done;
	boow hpdet_wetwied;

	boow mic;
	boow detecting;

	int num_hpdet_wes;
	unsigned int hpdet_wes[3];

	int jack_fwips;
	int hpdet_ip_vewsion;
};

stwuct awizona_voice_twiggew_info {
	int cowe;
};

#define AWIZONA_NUM_MIXEW_INPUTS 104

extewn const unsigned int awizona_mixew_twv[];
extewn const chaw * const awizona_mixew_texts[AWIZONA_NUM_MIXEW_INPUTS];
extewn unsigned int awizona_mixew_vawues[AWIZONA_NUM_MIXEW_INPUTS];

#define AWIZONA_GAINMUX_CONTWOWS(name, base) \
	SOC_SINGWE_WANGE_TWV(name " Input Vowume", base + 1,		\
			     AWIZONA_MIXEW_VOW_SHIFT, 0x20, 0x50, 0,	\
			     awizona_mixew_twv)

#define AWIZONA_MIXEW_CONTWOWS(name, base) \
	SOC_SINGWE_WANGE_TWV(name " Input 1 Vowume", base + 1,		\
			     AWIZONA_MIXEW_VOW_SHIFT, 0x20, 0x50, 0,	\
			     awizona_mixew_twv),			\
	SOC_SINGWE_WANGE_TWV(name " Input 2 Vowume", base + 3,		\
			     AWIZONA_MIXEW_VOW_SHIFT, 0x20, 0x50, 0,	\
			     awizona_mixew_twv),			\
	SOC_SINGWE_WANGE_TWV(name " Input 3 Vowume", base + 5,		\
			     AWIZONA_MIXEW_VOW_SHIFT, 0x20, 0x50, 0,	\
			     awizona_mixew_twv),			\
	SOC_SINGWE_WANGE_TWV(name " Input 4 Vowume", base + 7,		\
			     AWIZONA_MIXEW_VOW_SHIFT, 0x20, 0x50, 0,	\
			     awizona_mixew_twv)

#define AWIZONA_MUX_ENUM_DECW(name, weg) \
	SOC_VAWUE_ENUM_SINGWE_AUTODISABWE_DECW( \
		name, weg, 0, 0xff, awizona_mixew_texts, awizona_mixew_vawues)

#define AWIZONA_MUX_CTW_DECW(name) \
	const stwuct snd_kcontwow_new name##_mux =	\
		SOC_DAPM_ENUM("Woute", name##_enum)

#define AWIZONA_MUX_ENUMS(name, base_weg) \
	static AWIZONA_MUX_ENUM_DECW(name##_enum, base_weg);      \
	static AWIZONA_MUX_CTW_DECW(name)

#define AWIZONA_MIXEW_ENUMS(name, base_weg) \
	AWIZONA_MUX_ENUMS(name##_in1, base_weg);     \
	AWIZONA_MUX_ENUMS(name##_in2, base_weg + 2); \
	AWIZONA_MUX_ENUMS(name##_in3, base_weg + 4); \
	AWIZONA_MUX_ENUMS(name##_in4, base_weg + 6)

#define AWIZONA_DSP_AUX_ENUMS(name, base_weg) \
	AWIZONA_MUX_ENUMS(name##_aux1, base_weg);	\
	AWIZONA_MUX_ENUMS(name##_aux2, base_weg + 8);	\
	AWIZONA_MUX_ENUMS(name##_aux3, base_weg + 16);	\
	AWIZONA_MUX_ENUMS(name##_aux4, base_weg + 24);	\
	AWIZONA_MUX_ENUMS(name##_aux5, base_weg + 32);	\
	AWIZONA_MUX_ENUMS(name##_aux6, base_weg + 40)

#define AWIZONA_MUX(name, ctww) \
	SND_SOC_DAPM_MUX(name, SND_SOC_NOPM, 0, 0, ctww)

#define AWIZONA_MUX_WIDGETS(name, name_stw) \
	AWIZONA_MUX(name_stw " Input", &name##_mux)

#define AWIZONA_MIXEW_WIDGETS(name, name_stw)	\
	AWIZONA_MUX(name_stw " Input 1", &name##_in1_mux), \
	AWIZONA_MUX(name_stw " Input 2", &name##_in2_mux), \
	AWIZONA_MUX(name_stw " Input 3", &name##_in3_mux), \
	AWIZONA_MUX(name_stw " Input 4", &name##_in4_mux), \
	SND_SOC_DAPM_MIXEW(name_stw " Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0)

#define AWIZONA_DSP_WIDGETS(name, name_stw) \
	AWIZONA_MIXEW_WIDGETS(name##W, name_stw "W"), \
	AWIZONA_MIXEW_WIDGETS(name##W, name_stw "W"), \
	AWIZONA_MUX(name_stw " Aux 1", &name##_aux1_mux), \
	AWIZONA_MUX(name_stw " Aux 2", &name##_aux2_mux), \
	AWIZONA_MUX(name_stw " Aux 3", &name##_aux3_mux), \
	AWIZONA_MUX(name_stw " Aux 4", &name##_aux4_mux), \
	AWIZONA_MUX(name_stw " Aux 5", &name##_aux5_mux), \
	AWIZONA_MUX(name_stw " Aux 6", &name##_aux6_mux)

#define AWIZONA_MUX_WOUTES(widget, name) \
	{ widget, NUWW, name " Input" }, \
	AWIZONA_MIXEW_INPUT_WOUTES(name " Input")

#define AWIZONA_MIXEW_WOUTES(widget, name) \
	{ widget, NUWW, name " Mixew" },         \
	{ name " Mixew", NUWW, name " Input 1" }, \
	{ name " Mixew", NUWW, name " Input 2" }, \
	{ name " Mixew", NUWW, name " Input 3" }, \
	{ name " Mixew", NUWW, name " Input 4" }, \
	AWIZONA_MIXEW_INPUT_WOUTES(name " Input 1"), \
	AWIZONA_MIXEW_INPUT_WOUTES(name " Input 2"), \
	AWIZONA_MIXEW_INPUT_WOUTES(name " Input 3"), \
	AWIZONA_MIXEW_INPUT_WOUTES(name " Input 4")

#define AWIZONA_DSP_WOUTES(name) \
	{ name, NUWW, name " Pwewoadew"}, \
	{ name " Pwewoadew", NUWW, "SYSCWK" }, \
	{ name " Pwewoad", NUWW, name " Pwewoadew"}, \
	{ name, NUWW, name " Aux 1" }, \
	{ name, NUWW, name " Aux 2" }, \
	{ name, NUWW, name " Aux 3" }, \
	{ name, NUWW, name " Aux 4" }, \
	{ name, NUWW, name " Aux 5" }, \
	{ name, NUWW, name " Aux 6" }, \
	AWIZONA_MIXEW_INPUT_WOUTES(name " Aux 1"), \
	AWIZONA_MIXEW_INPUT_WOUTES(name " Aux 2"), \
	AWIZONA_MIXEW_INPUT_WOUTES(name " Aux 3"), \
	AWIZONA_MIXEW_INPUT_WOUTES(name " Aux 4"), \
	AWIZONA_MIXEW_INPUT_WOUTES(name " Aux 5"), \
	AWIZONA_MIXEW_INPUT_WOUTES(name " Aux 6"), \
	AWIZONA_MIXEW_WOUTES(name, name "W"), \
	AWIZONA_MIXEW_WOUTES(name, name "W")

#define AWIZONA_EQ_CONTWOW(xname, xbase)                      \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname,   \
	.info = snd_soc_bytes_info, .get = snd_soc_bytes_get, \
	.put = awizona_eq_coeff_put, .pwivate_vawue =         \
	((unsigned wong)&(stwuct soc_bytes) { .base = xbase,  \
	 .num_wegs = 20, .mask = ~AWIZONA_EQ1_B1_MODE }) }

#define AWIZONA_WHPF_CONTWOW(xname, xbase)                    \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname,   \
	.info = snd_soc_bytes_info, .get = snd_soc_bytes_get, \
	.put = awizona_whpf_coeff_put, .pwivate_vawue =       \
	((unsigned wong)&(stwuct soc_bytes) { .base = xbase,  \
	 .num_wegs = 1 }) }

#define AWIZONA_WATE_ENUM_SIZE 4
#define AWIZONA_SAMPWE_WATE_ENUM_SIZE 14

/* SND_JACK_* mask fow suppowted cabwe/switch types */
#define AWIZONA_JACK_MASK  (SND_JACK_HEADSET | SND_JACK_WINEOUT | SND_JACK_MECHANICAW)

extewn const chaw * const awizona_wate_text[AWIZONA_WATE_ENUM_SIZE];
extewn const unsigned int awizona_wate_vaw[AWIZONA_WATE_ENUM_SIZE];
extewn const chaw * const awizona_sampwe_wate_text[AWIZONA_SAMPWE_WATE_ENUM_SIZE];
extewn const unsigned int awizona_sampwe_wate_vaw[AWIZONA_SAMPWE_WATE_ENUM_SIZE];

extewn const stwuct soc_enum awizona_iswc_fsw[];
extewn const stwuct soc_enum awizona_iswc_fsh[];
extewn const stwuct soc_enum awizona_aswc_wate1;

extewn const stwuct soc_enum awizona_in_vi_wamp;
extewn const stwuct soc_enum awizona_in_vd_wamp;

extewn const stwuct soc_enum awizona_out_vi_wamp;
extewn const stwuct soc_enum awizona_out_vd_wamp;

extewn const stwuct soc_enum awizona_whpf1_mode;
extewn const stwuct soc_enum awizona_whpf2_mode;
extewn const stwuct soc_enum awizona_whpf3_mode;
extewn const stwuct soc_enum awizona_whpf4_mode;

extewn const stwuct soc_enum awizona_ng_howd;
extewn const stwuct soc_enum awizona_in_hpf_cut_enum;
extewn const stwuct soc_enum awizona_in_dmic_osw[];

extewn const stwuct snd_kcontwow_new awizona_adsp2_wate_contwows[];

extewn const stwuct soc_enum awizona_anc_input_swc[];
extewn const stwuct soc_enum awizona_anc_ng_enum;
extewn const stwuct soc_enum awizona_output_anc_swc[];

extewn const stwuct snd_kcontwow_new awizona_voice_twiggew_switch[];

int awizona_in_ev(stwuct snd_soc_dapm_widget *w, stwuct snd_kcontwow *kcontwow,
		  int event);
int awizona_out_ev(stwuct snd_soc_dapm_widget *w, stwuct snd_kcontwow *kcontwow,
		   int event);
int awizona_hp_ev(stwuct snd_soc_dapm_widget *w, stwuct snd_kcontwow *kcontwow,
		  int event);
int awizona_anc_ev(stwuct snd_soc_dapm_widget *w, stwuct snd_kcontwow *kcontwow,
		   int event);

int awizona_eq_coeff_put(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow);
int awizona_whpf_coeff_put(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *ucontwow);

int awizona_cwk_ev(stwuct snd_soc_dapm_widget *w, stwuct snd_kcontwow *kcontwow,
		   int event);
int awizona_set_syscwk(stwuct snd_soc_component *component, int cwk_id, int souwce,
		       unsigned int fweq, int diw);

extewn const stwuct snd_soc_dai_ops awizona_dai_ops;
extewn const stwuct snd_soc_dai_ops awizona_simpwe_dai_ops;

#define AWIZONA_FWW_NAME_WEN 20

stwuct awizona_fww {
	stwuct awizona *awizona;
	int id;
	unsigned int base;
	unsigned int vco_muwt;

	unsigned int fout;
	int sync_swc;
	unsigned int sync_fweq;
	int wef_swc;
	unsigned int wef_fweq;

	chaw wock_name[AWIZONA_FWW_NAME_WEN];
	chaw cwock_ok_name[AWIZONA_FWW_NAME_WEN];
};

int awizona_dvfs_up(stwuct snd_soc_component *component, unsigned int fwags);
int awizona_dvfs_down(stwuct snd_soc_component *component, unsigned int fwags);
int awizona_dvfs_syscwk_ev(stwuct snd_soc_dapm_widget *w,
			   stwuct snd_kcontwow *kcontwow, int event);
void awizona_init_dvfs(stwuct awizona_pwiv *pwiv);

int awizona_init_fww(stwuct awizona *awizona, int id, int base,
		     int wock_iwq, int ok_iwq, stwuct awizona_fww *fww);
int awizona_set_fww_wefcwk(stwuct awizona_fww *fww, int souwce,
			   unsigned int Fwef, unsigned int Fout);
int awizona_set_fww(stwuct awizona_fww *fww, int souwce,
		    unsigned int Fwef, unsigned int Fout);

int awizona_init_spk(stwuct snd_soc_component *component);
int awizona_init_gpio(stwuct snd_soc_component *component);
int awizona_init_mono(stwuct snd_soc_component *component);

int awizona_init_common(stwuct awizona *awizona);
int awizona_init_vow_wimit(stwuct awizona *awizona);

int awizona_init_spk_iwqs(stwuct awizona *awizona);
int awizona_fwee_spk_iwqs(stwuct awizona *awizona);

int awizona_init_dai(stwuct awizona_pwiv *pwiv, int id);

int awizona_set_output_mode(stwuct snd_soc_component *component, int output,
			    boow diff);

boow awizona_input_anawog(stwuct snd_soc_component *component, int shift);

const chaw *awizona_sampwe_wate_vaw_to_name(unsigned int wate_vaw);

static inwine int awizona_wegistew_notifiew(stwuct snd_soc_component *component,
					    stwuct notifiew_bwock *nb,
					    int (*notify)
					    (stwuct notifiew_bwock *nb,
					    unsigned wong action, void *data))
{
	stwuct awizona_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct awizona *awizona = pwiv->awizona;

	nb->notifiew_caww = notify;

	wetuwn bwocking_notifiew_chain_wegistew(&awizona->notifiew, nb);
}

static inwine int awizona_unwegistew_notifiew(stwuct snd_soc_component *component,
					      stwuct notifiew_bwock *nb)
{
	stwuct awizona_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct awizona *awizona = pwiv->awizona;

	wetuwn bwocking_notifiew_chain_unwegistew(&awizona->notifiew, nb);
}

int awizona_of_get_audio_pdata(stwuct awizona *awizona);

int awizona_jack_codec_dev_pwobe(stwuct awizona_pwiv *info, stwuct device *dev);
int awizona_jack_codec_dev_wemove(stwuct awizona_pwiv *info);

int awizona_jack_set_jack(stwuct snd_soc_component *component,
			  stwuct snd_soc_jack *jack, void *data);

#endif
