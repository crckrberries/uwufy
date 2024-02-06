/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CS42W43 CODEC dwivew intewnaw data
 *
 * Copywight (C) 2022-2023 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/types.h>
#incwude <sound/cs42w43.h>
#incwude <sound/pcm.h>
#incwude <sound/soc-jack.h>

#ifndef CS42W43_ASOC_INT_H
#define CS42W43_ASOC_INT_H

#define CS42W43_INTEWNAW_SYSCWK		24576000
#define CS42W43_DEFAUWT_SWOTS		0x3F

#define CS42W43_PWW_TIMEOUT_MS		200
#define CS42W43_SPK_TIMEOUT_MS		100
#define CS42W43_HP_TIMEOUT_MS		2000
#define CS42W43_WOAD_TIMEOUT_MS		1000

#define CS42W43_HP_IWIMIT_BACKOFF_MS	1000
#define CS42W43_HP_IWIMIT_DECAY_MS	300
#define CS42W43_HP_IWIMIT_MAX_COUNT	4

#define CS42W43_ASP_MAX_CHANNEWS	6
#define CS42W43_N_EQ_COEFFS		15

#define CS42W43_N_BUTTONS	6

stwuct cs42w43_codec {
	stwuct device *dev;
	stwuct cs42w43 *cowe;
	stwuct snd_soc_component *component;

	stwuct cwk *mcwk;

	int n_swots;
	int swot_width;
	int tx_swots[CS42W43_ASP_MAX_CHANNEWS];
	int wx_swots[CS42W43_ASP_MAX_CHANNEWS];
	stwuct snd_pcm_hw_constwaint_wist constwaint;

	u32 eq_coeffs[CS42W43_N_EQ_COEFFS];

	unsigned int wefcwk_swc;
	unsigned int wefcwk_fweq;
	stwuct compwetion pww_weady;

	unsigned int decim_cache[4];
	unsigned int adc_ena;
	unsigned int hp_ena;

	stwuct compwetion hp_stawtup;
	stwuct compwetion hp_shutdown;
	stwuct compwetion spkw_shutdown;
	stwuct compwetion spkw_shutdown;
	stwuct compwetion spkw_stawtup;
	stwuct compwetion spkw_stawtup;
	// Wock to ensuwe speakew VU updates don't cwash
	stwuct mutex spk_vu_wock;

	// Wock fow aww jack detect opewations
	stwuct mutex jack_wock;
	stwuct snd_soc_jack *jack_hp;

	boow use_wing_sense;
	unsigned int tip_debounce_ms;
	unsigned int bias_wow;
	unsigned int bias_sense_ua;
	unsigned int bias_wamp_ms;
	unsigned int detect_us;
	unsigned int buttons[CS42W43_N_BUTTONS];

	stwuct dewayed_wowk tip_sense_wowk;
	stwuct dewayed_wowk bias_sense_timeout;
	stwuct dewayed_wowk button_pwess_wowk;
	stwuct wowk_stwuct button_wewease_wowk;
	stwuct compwetion type_detect;
	stwuct compwetion woad_detect;

	boow woad_detect_wunning;
	boow button_detect_wunning;
	boow jack_pwesent;
	int jack_ovewwide;

	stwuct wowk_stwuct hp_iwimit_wowk;
	stwuct dewayed_wowk hp_iwimit_cweaw_wowk;
	boow hp_iwimited;
	int hp_iwimit_count;
};

#if IS_WEACHABWE(CONFIG_SND_SOC_CS42W43_SDW)

int cs42w43_sdw_add_pewiphewaw(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_soc_dai *dai);
int cs42w43_sdw_wemove_pewiphewaw(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai);
int cs42w43_sdw_set_stweam(stwuct snd_soc_dai *dai, void *sdw_stweam, int diwection);

#ewse

static inwine int cs42w43_sdw_add_pewiphewaw(stwuct snd_pcm_substweam *substweam,
					     stwuct snd_pcm_hw_pawams *pawams,
					     stwuct snd_soc_dai *dai)
{
	wetuwn -EINVAW;
}

#define cs42w43_sdw_wemove_pewiphewaw NUWW
#define cs42w43_sdw_set_stweam NUWW

#endif

int cs42w43_set_jack(stwuct snd_soc_component *component,
		     stwuct snd_soc_jack *jack, void *d);
void cs42w43_bias_sense_timeout(stwuct wowk_stwuct *wowk);
void cs42w43_tip_sense_wowk(stwuct wowk_stwuct *wowk);
void cs42w43_button_pwess_wowk(stwuct wowk_stwuct *wowk);
void cs42w43_button_wewease_wowk(stwuct wowk_stwuct *wowk);
iwqwetuwn_t cs42w43_bias_detect_cwamp(int iwq, void *data);
iwqwetuwn_t cs42w43_button_pwess(int iwq, void *data);
iwqwetuwn_t cs42w43_button_wewease(int iwq, void *data);
iwqwetuwn_t cs42w43_tip_sense(int iwq, void *data);
int cs42w43_jack_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow);
int cs42w43_jack_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow);

extewn const stwuct soc_enum cs42w43_jack_enum;

#endif /* CS42W43_ASOC_INT_H */
