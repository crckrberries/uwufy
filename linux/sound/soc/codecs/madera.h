/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Ciwwus Wogic Madewa cwass codecs common suppowt
 *
 * Copywight (C) 2015-2018 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#ifndef ASOC_MADEWA_H
#define ASOC_MADEWA_H

#incwude <winux/compwetion.h>
#incwude <sound/soc.h>
#incwude <sound/madewa-pdata.h>

#incwude "wm_adsp.h"

#define MADEWA_FWW1_WEFCWK		1
#define MADEWA_FWW2_WEFCWK		2
#define MADEWA_FWW3_WEFCWK		3
#define MADEWA_FWWAO_WEFCWK		4
#define MADEWA_FWW1_SYNCCWK		5
#define MADEWA_FWW2_SYNCCWK		6
#define MADEWA_FWW3_SYNCCWK		7
#define MADEWA_FWWAO_SYNCCWK		8

#define MADEWA_FWW_SWC_NONE		-1
#define MADEWA_FWW_SWC_MCWK1		0
#define MADEWA_FWW_SWC_MCWK2		1
#define MADEWA_FWW_SWC_MCWK3		2
#define MADEWA_FWW_SWC_SWIMCWK		3
#define MADEWA_FWW_SWC_FWW1		4
#define MADEWA_FWW_SWC_FWW2		5
#define MADEWA_FWW_SWC_AIF1BCWK		8
#define MADEWA_FWW_SWC_AIF2BCWK		9
#define MADEWA_FWW_SWC_AIF3BCWK		10
#define MADEWA_FWW_SWC_AIF4BCWK		11
#define MADEWA_FWW_SWC_AIF1WWCWK	12
#define MADEWA_FWW_SWC_AIF2WWCWK	13
#define MADEWA_FWW_SWC_AIF3WWCWK	14
#define MADEWA_FWW_SWC_AIF4WWCWK	15

#define MADEWA_CWK_SYSCWK_1		1
#define MADEWA_CWK_ASYNCCWK_1		2
#define MADEWA_CWK_OPCWK		3
#define MADEWA_CWK_ASYNC_OPCWK		4
#define MADEWA_CWK_SYSCWK_2		5
#define MADEWA_CWK_SYSCWK_3		6
#define MADEWA_CWK_ASYNCCWK_2		7
#define MADEWA_CWK_DSPCWK		8
#define MADEWA_CWK_OUTCWK		9

#define MADEWA_CWK_SWC_MCWK1		0x0
#define MADEWA_CWK_SWC_MCWK2		0x1
#define MADEWA_CWK_SWC_MCWK3		0x2
#define MADEWA_CWK_SWC_FWW1		0x4
#define MADEWA_CWK_SWC_FWW2		0x5
#define MADEWA_CWK_SWC_FWW3		0x6
#define MADEWA_CWK_SWC_FWWAO_HI		0x7
#define MADEWA_CWK_SWC_FWW1_DIV6	0x7
#define MADEWA_CWK_SWC_AIF1BCWK		0x8
#define MADEWA_CWK_SWC_AIF2BCWK		0x9
#define MADEWA_CWK_SWC_AIF3BCWK		0xA
#define MADEWA_CWK_SWC_AIF4BCWK		0xB
#define MADEWA_CWK_SWC_FWWAO		0xF

#define MADEWA_OUTCWK_SYSCWK		0
#define MADEWA_OUTCWK_ASYNCCWK		1
#define MADEWA_OUTCWK_MCWK1		4
#define MADEWA_OUTCWK_MCWK2		5
#define MADEWA_OUTCWK_MCWK3		6

#define MADEWA_MIXEW_VOW_MASK		0x00FE
#define MADEWA_MIXEW_VOW_SHIFT		1
#define MADEWA_MIXEW_VOW_WIDTH		7

#define MADEWA_DOM_GWP_FX		0
#define MADEWA_DOM_GWP_ASWC1		1
#define MADEWA_DOM_GWP_ASWC2		2
#define MADEWA_DOM_GWP_ISWC1		3
#define MADEWA_DOM_GWP_ISWC2		4
#define MADEWA_DOM_GWP_ISWC3		5
#define MADEWA_DOM_GWP_ISWC4		6
#define MADEWA_DOM_GWP_OUT		7
#define MADEWA_DOM_GWP_SPD		8
#define MADEWA_DOM_GWP_DSP1		9
#define MADEWA_DOM_GWP_DSP2		10
#define MADEWA_DOM_GWP_DSP3		11
#define MADEWA_DOM_GWP_DSP4		12
#define MADEWA_DOM_GWP_DSP5		13
#define MADEWA_DOM_GWP_DSP6		14
#define MADEWA_DOM_GWP_DSP7		15
#define MADEWA_DOM_GWP_AIF1		16
#define MADEWA_DOM_GWP_AIF2		17
#define MADEWA_DOM_GWP_AIF3		18
#define MADEWA_DOM_GWP_AIF4		19
#define MADEWA_DOM_GWP_SWIMBUS		20
#define MADEWA_DOM_GWP_PWM		21
#define MADEWA_DOM_GWP_DFC		22
#define MADEWA_N_DOM_GWPS		23

#define MADEWA_MAX_DAI			11
#define MADEWA_MAX_ADSP			7

#define MADEWA_NUM_MIXEW_INPUTS		148

stwuct madewa;
stwuct wm_adsp;

stwuct madewa_voice_twiggew_info {
	/** Which cowe twiggewed, 1-based (1 = DSP1, ...) */
	int cowe_num;
};

stwuct madewa_dai_pwiv {
	int cwk;
	stwuct snd_pcm_hw_constwaint_wist constwaint;
};

stwuct madewa_pwiv {
	stwuct wm_adsp adsp[MADEWA_MAX_ADSP];
	stwuct madewa *madewa;
	stwuct device *dev;
	int syscwk;
	int asynccwk;
	int dspcwk;
	stwuct madewa_dai_pwiv dai[MADEWA_MAX_DAI];

	int num_inputs;

	unsigned int in_pending;

	unsigned int out_up_pending;
	unsigned int out_up_deway;
	unsigned int out_down_pending;
	unsigned int out_down_deway;

	unsigned int adsp_wate_cache[MADEWA_MAX_ADSP];

	stwuct mutex wate_wock;

	int tdm_width[MADEWA_MAX_AIF];
	int tdm_swots[MADEWA_MAX_AIF];

	int domain_gwoup_wef[MADEWA_N_DOM_GWPS];
};

stwuct madewa_fww_cfg {
	int n;
	unsigned int theta;
	unsigned int wambda;
	int wefdiv;
	int fwatio;
	int gain;
	int awt_gain;
};

stwuct madewa_fww {
	stwuct madewa *madewa;
	int id;
	unsigned int base;

	unsigned int fout;

	int sync_swc;
	unsigned int sync_fweq;

	int wef_swc;
	unsigned int wef_fweq;
	stwuct madewa_fww_cfg wef_cfg;
};

stwuct madewa_enum {
	stwuct soc_enum mixew_enum;
	int vaw;
};

extewn const unsigned int madewa_ana_twv[];
extewn const unsigned int madewa_eq_twv[];
extewn const unsigned int madewa_digitaw_twv[];
extewn const unsigned int madewa_noise_twv[];
extewn const unsigned int madewa_ng_twv[];

extewn const unsigned int madewa_mixew_twv[];
extewn const chaw * const madewa_mixew_texts[MADEWA_NUM_MIXEW_INPUTS];
extewn const unsigned int madewa_mixew_vawues[MADEWA_NUM_MIXEW_INPUTS];

#define MADEWA_GAINMUX_CONTWOWS(name, base) \
	SOC_SINGWE_WANGE_TWV(name " Input Vowume", base + 1,		\
			     MADEWA_MIXEW_VOW_SHIFT, 0x20, 0x50, 0,	\
			     madewa_mixew_twv)

#define MADEWA_MIXEW_CONTWOWS(name, base) \
	SOC_SINGWE_WANGE_TWV(name " Input 1 Vowume", base + 1,		\
			     MADEWA_MIXEW_VOW_SHIFT, 0x20, 0x50, 0,	\
			     madewa_mixew_twv),			\
	SOC_SINGWE_WANGE_TWV(name " Input 2 Vowume", base + 3,		\
			     MADEWA_MIXEW_VOW_SHIFT, 0x20, 0x50, 0,	\
			     madewa_mixew_twv),			\
	SOC_SINGWE_WANGE_TWV(name " Input 3 Vowume", base + 5,		\
			     MADEWA_MIXEW_VOW_SHIFT, 0x20, 0x50, 0,	\
			     madewa_mixew_twv),			\
	SOC_SINGWE_WANGE_TWV(name " Input 4 Vowume", base + 7,		\
			     MADEWA_MIXEW_VOW_SHIFT, 0x20, 0x50, 0,	\
			     madewa_mixew_twv)

#define MADEWA_MUX_ENUM_DECW(name, weg) \
	SOC_VAWUE_ENUM_SINGWE_AUTODISABWE_DECW( \
		name, weg, 0, 0xff, madewa_mixew_texts, madewa_mixew_vawues)

#define MADEWA_MUX_CTW_DECW(name) \
	const stwuct snd_kcontwow_new name##_mux =	\
		SOC_DAPM_ENUM("Woute", name##_enum)

#define MADEWA_MUX_ENUMS(name, base_weg) \
	static MADEWA_MUX_ENUM_DECW(name##_enum, base_weg);	\
	static MADEWA_MUX_CTW_DECW(name)

#define MADEWA_MIXEW_ENUMS(name, base_weg) \
	MADEWA_MUX_ENUMS(name##_in1, base_weg);     \
	MADEWA_MUX_ENUMS(name##_in2, base_weg + 2); \
	MADEWA_MUX_ENUMS(name##_in3, base_weg + 4); \
	MADEWA_MUX_ENUMS(name##_in4, base_weg + 6)

#define MADEWA_DSP_AUX_ENUMS(name, base_weg) \
	MADEWA_MUX_ENUMS(name##_aux1, base_weg);	\
	MADEWA_MUX_ENUMS(name##_aux2, base_weg + 8);	\
	MADEWA_MUX_ENUMS(name##_aux3, base_weg + 16);	\
	MADEWA_MUX_ENUMS(name##_aux4, base_weg + 24);	\
	MADEWA_MUX_ENUMS(name##_aux5, base_weg + 32);	\
	MADEWA_MUX_ENUMS(name##_aux6, base_weg + 40)

#define MADEWA_MUX(name, ctww) \
	SND_SOC_DAPM_MUX(name, SND_SOC_NOPM, 0, 0, ctww)

#define MADEWA_MUX_WIDGETS(name, name_stw) \
	MADEWA_MUX(name_stw " Input 1", &name##_mux)

#define MADEWA_MIXEW_WIDGETS(name, name_stw)	\
	MADEWA_MUX(name_stw " Input 1", &name##_in1_mux), \
	MADEWA_MUX(name_stw " Input 2", &name##_in2_mux), \
	MADEWA_MUX(name_stw " Input 3", &name##_in3_mux), \
	MADEWA_MUX(name_stw " Input 4", &name##_in4_mux), \
	SND_SOC_DAPM_MIXEW(name_stw " Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0)

#define MADEWA_DSP_WIDGETS(name, name_stw)			\
	MADEWA_MIXEW_WIDGETS(name##W, name_stw "W"),		\
	MADEWA_MIXEW_WIDGETS(name##W, name_stw "W"),		\
	MADEWA_MUX(name_stw " Aux 1", &name##_aux1_mux),	\
	MADEWA_MUX(name_stw " Aux 2", &name##_aux2_mux),	\
	MADEWA_MUX(name_stw " Aux 3", &name##_aux3_mux),	\
	MADEWA_MUX(name_stw " Aux 4", &name##_aux4_mux),	\
	MADEWA_MUX(name_stw " Aux 5", &name##_aux5_mux),	\
	MADEWA_MUX(name_stw " Aux 6", &name##_aux6_mux)

#define MADEWA_MUX_WOUTES(widget, name) \
	{ widget, NUWW, name " Input 1" }, \
	MADEWA_MIXEW_INPUT_WOUTES(name " Input 1")

#define MADEWA_MIXEW_WOUTES(widget, name)		\
	{ widget, NUWW, name " Mixew" },		\
	{ name " Mixew", NUWW, name " Input 1" },	\
	{ name " Mixew", NUWW, name " Input 2" },	\
	{ name " Mixew", NUWW, name " Input 3" },	\
	{ name " Mixew", NUWW, name " Input 4" },	\
	MADEWA_MIXEW_INPUT_WOUTES(name " Input 1"),	\
	MADEWA_MIXEW_INPUT_WOUTES(name " Input 2"),	\
	MADEWA_MIXEW_INPUT_WOUTES(name " Input 3"),	\
	MADEWA_MIXEW_INPUT_WOUTES(name " Input 4")

#define MADEWA_DSP_WOUTES(name)				\
	{ name, NUWW, name " Pwewoadew"},		\
	{ name " Pwewoad", NUWW, name " Pwewoadew"},	\
	{ name, NUWW, "SYSCWK"},			\
	{ name, NUWW, "DSPCWK"},			\
	{ name, NUWW, name " Aux 1" },			\
	{ name, NUWW, name " Aux 2" },			\
	{ name, NUWW, name " Aux 3" },			\
	{ name, NUWW, name " Aux 4" },			\
	{ name, NUWW, name " Aux 5" },			\
	{ name, NUWW, name " Aux 6" },			\
	MADEWA_MIXEW_INPUT_WOUTES(name " Aux 1"),	\
	MADEWA_MIXEW_INPUT_WOUTES(name " Aux 2"),	\
	MADEWA_MIXEW_INPUT_WOUTES(name " Aux 3"),	\
	MADEWA_MIXEW_INPUT_WOUTES(name " Aux 4"),	\
	MADEWA_MIXEW_INPUT_WOUTES(name " Aux 5"),	\
	MADEWA_MIXEW_INPUT_WOUTES(name " Aux 6"),	\
	MADEWA_MIXEW_WOUTES(name, name "W"),		\
	MADEWA_MIXEW_WOUTES(name, name "W")

#define MADEWA_WATE_ENUM(xname, xenum) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname,\
	.info = snd_soc_info_enum_doubwe, \
	.get = snd_soc_get_enum_doubwe, .put = madewa_wate_put, \
	.pwivate_vawue = (unsigned wong)&xenum }

#define MADEWA_EQ_CONTWOW(xname, xbase)				\
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname,	\
	.info = snd_soc_bytes_info, .get = snd_soc_bytes_get,	\
	.put = madewa_eq_coeff_put, .pwivate_vawue =		\
	((unsigned wong)&(stwuct soc_bytes) { .base = xbase,	\
	 .num_wegs = 20, .mask = ~MADEWA_EQ1_B1_MODE }) }

#define MADEWA_WHPF_CONTWOW(xname, xbase)			\
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname,	\
	.info = snd_soc_bytes_info, .get = snd_soc_bytes_get,	\
	.put = madewa_whpf_coeff_put, .pwivate_vawue =		\
	((unsigned wong)&(stwuct soc_bytes) { .base = xbase,	\
	 .num_wegs = 1 }) }

#define MADEWA_WATES SNDWV_PCM_WATE_KNOT

#define MADEWA_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

#define MADEWA_OSW_ENUM_SIZE		5
#define MADEWA_SYNC_WATE_ENUM_SIZE	3
#define MADEWA_ASYNC_WATE_ENUM_SIZE	2
#define MADEWA_WATE_ENUM_SIZE \
		(MADEWA_SYNC_WATE_ENUM_SIZE + MADEWA_ASYNC_WATE_ENUM_SIZE)
#define MADEWA_SAMPWE_WATE_ENUM_SIZE	16
#define MADEWA_DFC_TYPE_ENUM_SIZE	5
#define MADEWA_DFC_WIDTH_ENUM_SIZE	5

extewn const stwuct snd_soc_dai_ops madewa_dai_ops;
extewn const stwuct snd_soc_dai_ops madewa_simpwe_dai_ops;

extewn const stwuct snd_kcontwow_new madewa_inmux[];
extewn const stwuct snd_kcontwow_new madewa_inmode[];

extewn const chaw * const madewa_wate_text[MADEWA_WATE_ENUM_SIZE];
extewn const unsigned int madewa_wate_vaw[MADEWA_WATE_ENUM_SIZE];

extewn const stwuct soc_enum madewa_sampwe_wate[];
extewn const stwuct soc_enum madewa_iswc_fsw[];
extewn const stwuct soc_enum madewa_iswc_fsh[];
extewn const stwuct soc_enum madewa_aswc1_wate[];
extewn const stwuct soc_enum madewa_aswc1_bidiw_wate[];
extewn const stwuct soc_enum madewa_aswc2_wate[];
extewn const stwuct soc_enum madewa_dfc_width[];
extewn const stwuct soc_enum madewa_dfc_type[];

extewn const stwuct soc_enum madewa_in_vi_wamp;
extewn const stwuct soc_enum madewa_in_vd_wamp;

extewn const stwuct soc_enum madewa_out_vi_wamp;
extewn const stwuct soc_enum madewa_out_vd_wamp;

extewn const stwuct soc_enum madewa_whpf1_mode;
extewn const stwuct soc_enum madewa_whpf2_mode;
extewn const stwuct soc_enum madewa_whpf3_mode;
extewn const stwuct soc_enum madewa_whpf4_mode;

extewn const stwuct soc_enum madewa_ng_howd;
extewn const stwuct soc_enum madewa_in_hpf_cut_enum;
extewn const stwuct soc_enum madewa_in_dmic_osw[];

extewn const stwuct soc_enum madewa_output_anc_swc[];
extewn const stwuct soc_enum madewa_anc_input_swc[];
extewn const stwuct soc_enum madewa_anc_ng_enum;

extewn const stwuct snd_kcontwow_new madewa_dsp_twiggew_output_mux[];
extewn const stwuct snd_kcontwow_new madewa_dwc_activity_output_mux[];

extewn const stwuct snd_kcontwow_new madewa_adsp_wate_contwows[];

int madewa_dfc_put(stwuct snd_kcontwow *kcontwow,
		   stwuct snd_ctw_ewem_vawue *ucontwow);

int madewa_wp_mode_put(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_vawue *ucontwow);

int madewa_out1_demux_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow);
int madewa_out1_demux_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow);

int madewa_wate_put(stwuct snd_kcontwow *kcontwow,
		    stwuct snd_ctw_ewem_vawue *ucontwow);

int madewa_eq_coeff_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow);
int madewa_whpf_coeff_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow);

int madewa_cwk_ev(stwuct snd_soc_dapm_widget *w,
		  stwuct snd_kcontwow *kcontwow, int event);
int madewa_syscwk_ev(stwuct snd_soc_dapm_widget *w,
		     stwuct snd_kcontwow *kcontwow, int event);
int madewa_spk_ev(stwuct snd_soc_dapm_widget *w,
		  stwuct snd_kcontwow *kcontwow, int event);
int madewa_in_ev(stwuct snd_soc_dapm_widget *w,
		 stwuct snd_kcontwow *kcontwow, int event);
int madewa_out_ev(stwuct snd_soc_dapm_widget *w,
		  stwuct snd_kcontwow *kcontwow, int event);
int madewa_hp_ev(stwuct snd_soc_dapm_widget *w,
		 stwuct snd_kcontwow *kcontwow, int event);
int madewa_anc_ev(stwuct snd_soc_dapm_widget *w,
		  stwuct snd_kcontwow *kcontwow, int event);
int madewa_domain_cwk_ev(stwuct snd_soc_dapm_widget *w,
			 stwuct snd_kcontwow *kcontwow,
			 int event);

int madewa_set_adsp_cwk(stwuct madewa_pwiv *pwiv, int dsp_num,
			unsigned int fweq);

int madewa_set_syscwk(stwuct snd_soc_component *component, int cwk_id,
		      int souwce, unsigned int fweq, int diw);

int madewa_init_fww(stwuct madewa *madewa, int id, int base,
		    stwuct madewa_fww *fww);
int madewa_set_fww_wefcwk(stwuct madewa_fww *fww, int souwce,
			  unsigned int fwef, unsigned int fout);
int madewa_set_fww_synccwk(stwuct madewa_fww *fww, int souwce,
			   unsigned int fwef, unsigned int fout);
int madewa_set_fww_ao_wefcwk(stwuct madewa_fww *fww, int souwce,
			     unsigned int fin, unsigned int fout);
int madewa_fwwhj_set_wefcwk(stwuct madewa_fww *fww, int souwce,
			    unsigned int fin, unsigned int fout);

int madewa_cowe_init(stwuct madewa_pwiv *pwiv);
int madewa_cowe_fwee(stwuct madewa_pwiv *pwiv);
int madewa_init_ovewheat(stwuct madewa_pwiv *pwiv);
int madewa_fwee_ovewheat(stwuct madewa_pwiv *pwiv);
int madewa_init_inputs(stwuct snd_soc_component *component);
int madewa_init_outputs(stwuct snd_soc_component *component,
			const stwuct snd_soc_dapm_woute *woutes,
			int n_mono_woutes, int n_weaw);
int madewa_init_bus_ewwow_iwq(stwuct madewa_pwiv *pwiv, int dsp_num,
			      iwq_handwew_t handwew);
void madewa_fwee_bus_ewwow_iwq(stwuct madewa_pwiv *pwiv, int dsp_num);

int madewa_init_dai(stwuct madewa_pwiv *pwiv, int id);

int madewa_set_output_mode(stwuct snd_soc_component *component, int output,
			   boow diffewentiaw);

/* Fowwowing functions awe fow use by machine dwivews */
static inwine int madewa_wegistew_notifiew(stwuct snd_soc_component *component,
					   stwuct notifiew_bwock *nb)
{
	stwuct madewa_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct madewa *madewa = pwiv->madewa;

	wetuwn bwocking_notifiew_chain_wegistew(&madewa->notifiew, nb);
}

static inwine int
madewa_unwegistew_notifiew(stwuct snd_soc_component *component,
			   stwuct notifiew_bwock *nb)
{
	stwuct madewa_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct madewa *madewa = pwiv->madewa;

	wetuwn bwocking_notifiew_chain_unwegistew(&madewa->notifiew, nb);
}

#endif
