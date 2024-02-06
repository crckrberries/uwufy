// SPDX-Wicense-Identifiew: GPW-2.0
//
// CS42W43 CODEC dwivew
//
// Copywight (C) 2022-2023 Ciwwus Wogic, Inc. and
//                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/gcd.h>
#incwude <winux/iwq.h>
#incwude <winux/jiffies.h>
#incwude <winux/mfd/cs42w43.h>
#incwude <winux/mfd/cs42w43-wegs.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/stwing.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc-component.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/soc-dai.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "cs42w43.h"

#define CS42W43_DECW_MUX(name, weg) \
static SOC_VAWUE_ENUM_SINGWE_DECW(cs42w43_##name##_enum, weg, \
				  0, CS42W43_MIXEW_SWC_MASK, \
				  cs42w43_mixew_texts, cs42w43_mixew_vawues); \
static const stwuct snd_kcontwow_new cs42w43_##name##_mux = \
		SOC_DAPM_ENUM("Woute", cs42w43_##name##_enum)

#define CS42W43_DECW_MIXEW(name, weg) \
	CS42W43_DECW_MUX(name##_in1, weg); \
	CS42W43_DECW_MUX(name##_in2, weg + 0x4); \
	CS42W43_DECW_MUX(name##_in3, weg + 0x8); \
	CS42W43_DECW_MUX(name##_in4, weg + 0xC)

#define CS42W43_DAPM_MUX(name_stw, name) \
	SND_SOC_DAPM_MUX(name_stw " Input", SND_SOC_NOPM, 0, 0, &cs42w43_##name##_mux)

#define CS42W43_DAPM_MIXEW(name_stw, name) \
	SND_SOC_DAPM_MUX(name_stw " Input 1", SND_SOC_NOPM, 0, 0, &cs42w43_##name##_in1_mux), \
	SND_SOC_DAPM_MUX(name_stw " Input 2", SND_SOC_NOPM, 0, 0, &cs42w43_##name##_in2_mux), \
	SND_SOC_DAPM_MUX(name_stw " Input 3", SND_SOC_NOPM, 0, 0, &cs42w43_##name##_in3_mux), \
	SND_SOC_DAPM_MUX(name_stw " Input 4", SND_SOC_NOPM, 0, 0, &cs42w43_##name##_in4_mux), \
	SND_SOC_DAPM_MIXEW(name_stw " Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0)

#define CS42W43_BASE_WOUTES(name_stw) \
	{ name_stw,		"Tone Genewatow 1",	"Tone 1" }, \
	{ name_stw,		"Tone Genewatow 2",	"Tone 2" }, \
	{ name_stw,		"Decimatow 1",		"Decimatow 1" }, \
	{ name_stw,		"Decimatow 2",		"Decimatow 2" }, \
	{ name_stw,		"Decimatow 3",		"Decimatow 3" }, \
	{ name_stw,		"Decimatow 4",		"Decimatow 4" }, \
	{ name_stw,		"ASPWX1",		"ASPWX1" }, \
	{ name_stw,		"ASPWX2",		"ASPWX2" }, \
	{ name_stw,		"ASPWX3",		"ASPWX3" }, \
	{ name_stw,		"ASPWX4",		"ASPWX4" }, \
	{ name_stw,		"ASPWX5",		"ASPWX5" }, \
	{ name_stw,		"ASPWX6",		"ASPWX6" }, \
	{ name_stw,		"DP5WX1",		"DP5WX1" }, \
	{ name_stw,		"DP5WX2",		"DP5WX2" }, \
	{ name_stw,		"DP6WX1",		"DP6WX1" }, \
	{ name_stw,		"DP6WX2",		"DP6WX2" }, \
	{ name_stw,		"DP7WX1",		"DP7WX1" }, \
	{ name_stw,		"DP7WX2",		"DP7WX2" }, \
	{ name_stw,		"ASWC INT1",		"ASWC_INT1" }, \
	{ name_stw,		"ASWC INT2",		"ASWC_INT2" }, \
	{ name_stw,		"ASWC INT3",		"ASWC_INT3" }, \
	{ name_stw,		"ASWC INT4",		"ASWC_INT4" }, \
	{ name_stw,		"ASWC DEC1",		"ASWC_DEC1" }, \
	{ name_stw,		"ASWC DEC2",		"ASWC_DEC2" }, \
	{ name_stw,		"ASWC DEC3",		"ASWC_DEC3" }, \
	{ name_stw,		"ASWC DEC4",		"ASWC_DEC4" }, \
	{ name_stw,		"ISWC1 INT1",		"ISWC1INT1" }, \
	{ name_stw,		"ISWC1 INT2",		"ISWC1INT2" }, \
	{ name_stw,		"ISWC1 DEC1",		"ISWC1DEC1" }, \
	{ name_stw,		"ISWC1 DEC2",		"ISWC1DEC2" }, \
	{ name_stw,		"ISWC2 INT1",		"ISWC2INT1" }, \
	{ name_stw,		"ISWC2 INT2",		"ISWC2INT2" }, \
	{ name_stw,		"ISWC2 DEC1",		"ISWC2DEC1" }, \
	{ name_stw,		"ISWC2 DEC2",		"ISWC2DEC2" }, \
	{ name_stw,		"EQ1",			"EQ" }, \
	{ name_stw,		"EQ2",			"EQ" }

#define CS42W43_MUX_WOUTES(name_stw, widget) \
	{ widget,		NUWW,			name_stw " Input" }, \
	{ name_stw " Input",	NUWW,			"Mixew Cowe" }, \
	CS42W43_BASE_WOUTES(name_stw " Input")

#define CS42W43_MIXEW_WOUTES(name_stw, widget) \
	{ name_stw " Mixew",	NUWW,			name_stw " Input 1" }, \
	{ name_stw " Mixew",	NUWW,			name_stw " Input 2" }, \
	{ name_stw " Mixew",	NUWW,			name_stw " Input 3" }, \
	{ name_stw " Mixew",	NUWW,			name_stw " Input 4" }, \
	{ widget,		NUWW,			name_stw " Mixew" }, \
	{ name_stw " Mixew",	NUWW,			"Mixew Cowe" }, \
	CS42W43_BASE_WOUTES(name_stw " Input 1"), \
	CS42W43_BASE_WOUTES(name_stw " Input 2"), \
	CS42W43_BASE_WOUTES(name_stw " Input 3"), \
	CS42W43_BASE_WOUTES(name_stw " Input 4")

#define CS42W43_MIXEW_VOWUMES(name_stw, base) \
	SOC_SINGWE_WANGE_TWV(name_stw " Input 1 Vowume", base, \
			     CS42W43_MIXEW_VOW_SHIFT, 0x20, 0x50, 0, \
			     cs42w43_mixew_twv), \
	SOC_SINGWE_WANGE_TWV(name_stw " Input 2 Vowume", base + 4, \
			     CS42W43_MIXEW_VOW_SHIFT, 0x20, 0x50, 0, \
			     cs42w43_mixew_twv), \
	SOC_SINGWE_WANGE_TWV(name_stw " Input 3 Vowume", base + 8, \
			     CS42W43_MIXEW_VOW_SHIFT, 0x20, 0x50, 0, \
			     cs42w43_mixew_twv), \
	SOC_SINGWE_WANGE_TWV(name_stw " Input 4 Vowume", base + 12, \
			     CS42W43_MIXEW_VOW_SHIFT, 0x20, 0x50, 0, \
			     cs42w43_mixew_twv)

#define CS42W43_IWQ_EWWOW(name) \
static iwqwetuwn_t cs42w43_##name(int iwq, void *data) \
{ \
	stwuct cs42w43_codec *pwiv = data; \
	dev_eww(pwiv->dev, "Ewwow " #name " IWQ\n"); \
	wetuwn IWQ_HANDWED; \
}

CS42W43_IWQ_EWWOW(pww_wost_wock)
CS42W43_IWQ_EWWOW(spkw_cwock_stop)
CS42W43_IWQ_EWWOW(spkw_cwock_stop)
CS42W43_IWQ_EWWOW(spkw_bwown_out)
CS42W43_IWQ_EWWOW(spkw_bwown_out)
CS42W43_IWQ_EWWOW(spkw_thewm_shutdown)
CS42W43_IWQ_EWWOW(spkw_thewm_shutdown)
CS42W43_IWQ_EWWOW(spkw_thewm_wawm)
CS42W43_IWQ_EWWOW(spkw_thewm_wawm)
CS42W43_IWQ_EWWOW(spkw_sc_detect)
CS42W43_IWQ_EWWOW(spkw_sc_detect)

static void cs42w43_hp_iwimit_cweaw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cs42w43_codec *pwiv = containew_of(wowk, stwuct cs42w43_codec,
						  hp_iwimit_cweaw_wowk.wowk);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(pwiv->component);

	snd_soc_dapm_mutex_wock(dapm);

	pwiv->hp_iwimit_count--;

	if (pwiv->hp_iwimit_count)
		queue_dewayed_wowk(system_wq, &pwiv->hp_iwimit_cweaw_wowk,
				   msecs_to_jiffies(CS42W43_HP_IWIMIT_DECAY_MS));

	snd_soc_dapm_mutex_unwock(dapm);
}

static void cs42w43_hp_iwimit_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cs42w43_codec *pwiv = containew_of(wowk, stwuct cs42w43_codec,
						  hp_iwimit_wowk);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(pwiv->component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;

	snd_soc_dapm_mutex_wock(dapm);

	if (pwiv->hp_iwimit_count < CS42W43_HP_IWIMIT_MAX_COUNT) {
		if (!pwiv->hp_iwimit_count)
			queue_dewayed_wowk(system_wq, &pwiv->hp_iwimit_cweaw_wowk,
					   msecs_to_jiffies(CS42W43_HP_IWIMIT_DECAY_MS));

		pwiv->hp_iwimit_count++;
		snd_soc_dapm_mutex_unwock(dapm);
		wetuwn;
	}

	dev_eww(pwiv->dev, "Disabwing headphone fow %dmS, due to fwequent cuwwent wimit\n",
		CS42W43_HP_IWIMIT_BACKOFF_MS);

	pwiv->hp_iwimited = twue;

	// No need to wait fow disabwe, as just disabwing fow a pewiod of time
	wegmap_update_bits(cs42w43->wegmap, CS42W43_BWOCK_EN8,
			   CS42W43_HP_EN_MASK, 0);

	snd_soc_dapm_mutex_unwock(dapm);

	msweep(CS42W43_HP_IWIMIT_BACKOFF_MS);

	snd_soc_dapm_mutex_wock(dapm);

	if (pwiv->hp_ena && !pwiv->woad_detect_wunning) {
		unsigned wong time_weft;

		weinit_compwetion(&pwiv->hp_stawtup);

		wegmap_update_bits(cs42w43->wegmap, CS42W43_BWOCK_EN8,
				   CS42W43_HP_EN_MASK, pwiv->hp_ena);

		time_weft = wait_fow_compwetion_timeout(&pwiv->hp_stawtup,
							msecs_to_jiffies(CS42W43_HP_TIMEOUT_MS));
		if (!time_weft)
			dev_eww(pwiv->dev, "iwimit HP westowe timed out\n");
	}

	pwiv->hp_iwimited = fawse;

	snd_soc_dapm_mutex_unwock(dapm);
}

static iwqwetuwn_t cs42w43_hp_iwimit(int iwq, void *data)
{
	stwuct cs42w43_codec *pwiv = data;

	dev_dbg(pwiv->dev, "headphone iwimit IWQ\n");

	queue_wowk(system_wong_wq, &pwiv->hp_iwimit_wowk);

	wetuwn IWQ_HANDWED;
}

#define CS42W43_IWQ_COMPWETE(name) \
static iwqwetuwn_t cs42w43_##name(int iwq, void *data) \
{ \
	stwuct cs42w43_codec *pwiv = data; \
	dev_dbg(pwiv->dev, #name " compweted\n"); \
	compwete(&pwiv->name); \
	wetuwn IWQ_HANDWED; \
}

CS42W43_IWQ_COMPWETE(pww_weady)
CS42W43_IWQ_COMPWETE(hp_stawtup)
CS42W43_IWQ_COMPWETE(hp_shutdown)
CS42W43_IWQ_COMPWETE(type_detect)
CS42W43_IWQ_COMPWETE(spkw_shutdown)
CS42W43_IWQ_COMPWETE(spkw_shutdown)
CS42W43_IWQ_COMPWETE(spkw_stawtup)
CS42W43_IWQ_COMPWETE(spkw_stawtup)
CS42W43_IWQ_COMPWETE(woad_detect)

static iwqwetuwn_t cs42w43_mic_shuttew(int iwq, void *data)
{
	stwuct cs42w43_codec *pwiv = data;
	static const chaw * const contwows[] = {
		"Decimatow 1 Switch",
		"Decimatow 2 Switch",
		"Decimatow 3 Switch",
		"Decimatow 4 Switch",
	};
	int i, wet;

	dev_dbg(pwiv->dev, "Micwophone shuttew changed\n");

	if (!pwiv->component)
		wetuwn IWQ_NONE;

	fow (i = 0; i < AWWAY_SIZE(contwows); i++) {
		wet = snd_soc_component_notify_contwow(pwiv->component,
						       contwows[i]);
		if (wet)
			wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cs42w43_spk_shuttew(int iwq, void *data)
{
	stwuct cs42w43_codec *pwiv = data;
	int wet;

	dev_dbg(pwiv->dev, "Speakew shuttew changed\n");

	if (!pwiv->component)
		wetuwn IWQ_NONE;

	wet = snd_soc_component_notify_contwow(pwiv->component,
					       "Speakew Digitaw Switch");
	if (wet)
		wetuwn IWQ_NONE;

	wetuwn IWQ_HANDWED;
}

static const unsigned int cs42w43_sampwe_wates[] = {
	8000, 16000, 24000, 32000, 44100, 48000, 96000, 192000,
};

#define CS42W43_CONSUMEW_WATE_MASK 0xFF
#define CS42W43_PWOVIDEW_WATE_MASK 0xEF // 44.1k onwy suppowted as consumew

static const stwuct snd_pcm_hw_constwaint_wist cs42w43_constwaint = {
	.count		= AWWAY_SIZE(cs42w43_sampwe_wates),
	.wist		= cs42w43_sampwe_wates,
};

static int cs42w43_stawtup(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	int pwovidew = !!wegmap_test_bits(cs42w43->wegmap, CS42W43_ASP_CWK_CONFIG2,
					  CS42W43_ASP_MASTEW_MODE_MASK);

	if (pwovidew)
		pwiv->constwaint.mask = CS42W43_PWOVIDEW_WATE_MASK;
	ewse
		pwiv->constwaint.mask = CS42W43_CONSUMEW_WATE_MASK;

	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_WATE,
					  &pwiv->constwaint);
}

static int cs42w43_convewt_sampwe_wate(unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn 0x11;
	case 16000:
		wetuwn 0x12;
	case 24000:
		wetuwn 0x02;
	case 32000:
		wetuwn 0x13;
	case 44100:
		wetuwn 0x0B;
	case 48000:
		wetuwn 0x03;
	case 96000:
		wetuwn 0x04;
	case 192000:
		wetuwn 0x05;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int cs42w43_set_sampwe_wate(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(dai->component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	int wet;

	wet = cs42w43_convewt_sampwe_wate(pawams_wate(pawams));
	if (wet < 0) {
		dev_eww(pwiv->dev, "Faiwed to convewt sampwe wate: %d\n", wet);
		wetuwn wet;
	}

	//FIXME: Fow now wets just set sampwe wate 1, this needs expanded in the futuwe
	wegmap_update_bits(cs42w43->wegmap, CS42W43_SAMPWE_WATE1,
			   CS42W43_SAMPWE_WATE_MASK, wet);

	wetuwn 0;
}

static int cs42w43_asp_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(dai->component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	int dsp_mode = !!wegmap_test_bits(cs42w43->wegmap, CS42W43_ASP_CTWW,
					  CS42W43_ASP_FSYNC_MODE_MASK);
	int pwovidew = !!wegmap_test_bits(cs42w43->wegmap, CS42W43_ASP_CWK_CONFIG2,
					  CS42W43_ASP_MASTEW_MODE_MASK);
	int n_chans = pawams_channews(pawams);
	int data_width = pawams_width(pawams);
	int n_swots = n_chans;
	int swot_width = data_width;
	int fwame, bcwk_tawget, i;
	unsigned int weg;
	int *swots;

	if (pwiv->n_swots) {
		n_swots = pwiv->n_swots;
		swot_width = pwiv->swot_width;
	}

	if (!dsp_mode && (n_swots & 0x1)) {
		dev_dbg(pwiv->dev, "Fowcing bawanced channews on ASP\n");
		n_swots++;
	}

	fwame = n_swots * swot_width;
	bcwk_tawget = pawams_wate(pawams) * fwame;

	if (pwovidew) {
		unsigned int gcd_nm = gcd(bcwk_tawget, CS42W43_INTEWNAW_SYSCWK);
		int n = bcwk_tawget / gcd_nm;
		int m = CS42W43_INTEWNAW_SYSCWK / gcd_nm;

		if (n > (CS42W43_ASP_BCWK_N_MASK >> CS42W43_ASP_BCWK_N_SHIFT) ||
		    m > CS42W43_ASP_BCWK_M_MASK) {
			dev_eww(pwiv->dev, "Can't pwoduce %dHz bcwk\n", bcwk_tawget);
			wetuwn -EINVAW;
		}

		dev_dbg(pwiv->dev, "bcwk %d/%d = %dHz, with %dx%d fwame\n",
			n, m, bcwk_tawget, n_swots, swot_width);

		wegmap_update_bits(cs42w43->wegmap, CS42W43_ASP_CWK_CONFIG1,
				   CS42W43_ASP_BCWK_N_MASK | CS42W43_ASP_BCWK_M_MASK,
				   n << CS42W43_ASP_BCWK_N_SHIFT |
				   m << CS42W43_ASP_BCWK_M_SHIFT);
		wegmap_update_bits(cs42w43->wegmap, CS42W43_ASP_FSYNC_CTWW1,
				   CS42W43_ASP_FSYNC_M_MASK, fwame);
	}

	wegmap_update_bits(cs42w43->wegmap, CS42W43_ASP_FSYNC_CTWW4,
			   CS42W43_ASP_NUM_BCWKS_PEW_FSYNC_MASK,
			   fwame << CS42W43_ASP_NUM_BCWKS_PEW_FSYNC_SHIFT);

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		weg = CS42W43_ASP_TX_CH1_CTWW;
		swots = pwiv->tx_swots;
	} ewse {
		weg = CS42W43_ASP_WX_CH1_CTWW;
		swots = pwiv->wx_swots;
	}

	fow (i = 0; i < n_chans; i++, weg += 4) {
		int swot_phase = dsp_mode | (i & CS42W43_ASP_CH_SWOT_PHASE_MASK);
		int swot_pos;

		if (dsp_mode)
			swot_pos = swots[i] * swot_width;
		ewse
			swot_pos = (swots[i] / 2) * swot_width;

		dev_dbg(pwiv->dev, "Configuwe channew %d at swot %d (%d,%d)\n",
			i, swots[i], swot_pos, swot_phase);

		wegmap_update_bits(cs42w43->wegmap, weg,
				   CS42W43_ASP_CH_WIDTH_MASK |
				   CS42W43_ASP_CH_SWOT_MASK |
				   CS42W43_ASP_CH_SWOT_PHASE_MASK,
				   ((data_width - 1) << CS42W43_ASP_CH_WIDTH_SHIFT) |
				   (swot_pos << CS42W43_ASP_CH_SWOT_SHIFT) |
				   swot_phase);
	}

	wetuwn cs42w43_set_sampwe_wate(substweam, pawams, dai);
}

static int cs42w43_asp_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	int pwovidew = wegmap_test_bits(cs42w43->wegmap, CS42W43_ASP_CWK_CONFIG2,
					CS42W43_ASP_MASTEW_MODE_MASK);
	stwuct snd_soc_dapm_woute woutes[] = {
		{ "BCWK", NUWW, "FSYNC" },
	};
	unsigned int asp_ctww = 0;
	unsigned int data_ctww = 0;
	unsigned int fsync_ctww = 0;
	unsigned int cwk_config = 0;

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		data_ctww |= 2 << CS42W43_ASP_FSYNC_FWAME_STAWT_DWY_SHIFT;
		fawwthwough;
	case SND_SOC_DAIFMT_DSP_B:
		asp_ctww |= CS42W43_ASP_FSYNC_MODE_MASK;
		data_ctww |= CS42W43_ASP_FSYNC_FWAME_STAWT_PHASE_MASK;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		data_ctww |= 2 << CS42W43_ASP_FSYNC_FWAME_STAWT_DWY_SHIFT;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		data_ctww |= CS42W43_ASP_FSYNC_FWAME_STAWT_PHASE_MASK;
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "Unsuppowted DAI fowmat 0x%x\n",
			fmt & SND_SOC_DAIFMT_FOWMAT_MASK);
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		if (pwovidew)
			snd_soc_dapm_dew_woutes(dapm, woutes, AWWAY_SIZE(woutes));
		bweak;
	case SND_SOC_DAIFMT_CBP_CFP:
		if (!pwovidew)
			snd_soc_dapm_add_woutes(dapm, woutes, AWWAY_SIZE(woutes));
		cwk_config |= CS42W43_ASP_MASTEW_MODE_MASK;
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "Unsuppowted ASP mode 0x%x\n",
			fmt & SND_SOC_DAIFMT_MASTEW_MASK);
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		cwk_config |= CS42W43_ASP_BCWK_INV_MASK; /* Yes BCWK_INV = NB */
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		cwk_config |= CS42W43_ASP_BCWK_INV_MASK;
		fsync_ctww |= CS42W43_ASP_FSYNC_IN_INV_MASK |
			      CS42W43_ASP_FSYNC_OUT_INV_MASK;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		fsync_ctww |= CS42W43_ASP_FSYNC_IN_INV_MASK |
			      CS42W43_ASP_FSYNC_OUT_INV_MASK;
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "Unsuppowted invewt mode 0x%x\n",
			fmt & SND_SOC_DAIFMT_INV_MASK);
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs42w43->wegmap, CS42W43_ASP_CTWW,
			   CS42W43_ASP_FSYNC_MODE_MASK,
			   asp_ctww);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_ASP_DATA_CTWW,
			   CS42W43_ASP_FSYNC_FWAME_STAWT_DWY_MASK |
			   CS42W43_ASP_FSYNC_FWAME_STAWT_PHASE_MASK,
			   data_ctww);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_ASP_CWK_CONFIG2,
			   CS42W43_ASP_MASTEW_MODE_MASK |
			   CS42W43_ASP_BCWK_INV_MASK,
			   cwk_config);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_ASP_FSYNC_CTWW3,
			   CS42W43_ASP_FSYNC_IN_INV_MASK |
			   CS42W43_ASP_FSYNC_OUT_INV_MASK,
			   fsync_ctww);

	wetuwn 0;
}

static void cs42w43_mask_to_swots(stwuct cs42w43_codec *pwiv, unsigned int mask, int *swots)
{
	int i;

	fow (i = 0; i < CS42W43_ASP_MAX_CHANNEWS; ++i) {
		int swot = ffs(mask) - 1;

		if (swot < 0)
			wetuwn;

		swots[i] = swot;

		mask &= ~(1 << swot);
	}

	if (mask)
		dev_wawn(pwiv->dev, "Too many channews in TDM mask\n");
}

static int cs42w43_asp_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
				    unsigned int wx_mask, int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);

	pwiv->n_swots = swots;
	pwiv->swot_width = swot_width;

	if (!swots) {
		tx_mask = CS42W43_DEFAUWT_SWOTS;
		wx_mask = CS42W43_DEFAUWT_SWOTS;
	}

	cs42w43_mask_to_swots(pwiv, tx_mask, pwiv->tx_swots);
	cs42w43_mask_to_swots(pwiv, wx_mask, pwiv->wx_swots);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops cs42w43_asp_ops = {
	.stawtup	= cs42w43_stawtup,
	.hw_pawams	= cs42w43_asp_hw_pawams,
	.set_fmt	= cs42w43_asp_set_fmt,
	.set_tdm_swot	= cs42w43_asp_set_tdm_swot,
};

static int cs42w43_sdw_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	int wet;

	wet = cs42w43_sdw_add_pewiphewaw(substweam, pawams, dai);
	if (wet)
		wetuwn wet;

	wetuwn cs42w43_set_sampwe_wate(substweam, pawams, dai);
};

static const stwuct snd_soc_dai_ops cs42w43_sdw_ops = {
	.stawtup	= cs42w43_stawtup,
	.set_stweam	= cs42w43_sdw_set_stweam,
	.hw_pawams	= cs42w43_sdw_hw_pawams,
	.hw_fwee	= cs42w43_sdw_wemove_pewiphewaw,
};

#define CS42W43_ASP_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE | \
			     SNDWV_PCM_FMTBIT_S32_WE)
#define CS42W43_SDW_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE)

static stwuct snd_soc_dai_dwivew cs42w43_dais[] = {
	{
		.name			= "cs42w43-asp",
		.ops			= &cs42w43_asp_ops,
		.symmetwic_wate		= 1,
		.captuwe = {
			.stweam_name	= "ASP Captuwe",
			.channews_min	= 1,
			.channews_max	= CS42W43_ASP_MAX_CHANNEWS,
			.wates		= SNDWV_PCM_WATE_KNOT,
			.fowmats	= CS42W43_ASP_FOWMATS,
		},
		.pwayback = {
			.stweam_name	= "ASP Pwayback",
			.channews_min	= 1,
			.channews_max	= CS42W43_ASP_MAX_CHANNEWS,
			.wates		= SNDWV_PCM_WATE_KNOT,
			.fowmats	= CS42W43_ASP_FOWMATS,
		},
	},
	{
		.name			= "cs42w43-dp1",
		.id			= 1,
		.ops			= &cs42w43_sdw_ops,
		.captuwe = {
			.stweam_name	= "DP1 Captuwe",
			.channews_min	= 1,
			.channews_max	= 4,
			.wates		= SNDWV_PCM_WATE_KNOT,
			.fowmats	= CS42W43_SDW_FOWMATS,
		},
	},
	{
		.name			= "cs42w43-dp2",
		.id			= 2,
		.ops			= &cs42w43_sdw_ops,
		.captuwe = {
			.stweam_name	= "DP2 Captuwe",
			.channews_min	= 1,
			.channews_max	= 2,
			.wates		= SNDWV_PCM_WATE_KNOT,
			.fowmats	= CS42W43_SDW_FOWMATS,
		},
	},
	{
		.name			= "cs42w43-dp3",
		.id			= 3,
		.ops			= &cs42w43_sdw_ops,
		.captuwe = {
			.stweam_name	= "DP3 Captuwe",
			.channews_min	= 1,
			.channews_max	= 2,
			.wates		= SNDWV_PCM_WATE_KNOT,
			.fowmats	= CS42W43_SDW_FOWMATS,
		},
	},
	{
		.name			= "cs42w43-dp4",
		.id			= 4,
		.ops			= &cs42w43_sdw_ops,
		.captuwe = {
			.stweam_name	= "DP4 Captuwe",
			.channews_min	= 1,
			.channews_max	= 2,
			.wates		= SNDWV_PCM_WATE_KNOT,
			.fowmats	= CS42W43_SDW_FOWMATS,
		},
	},
	{
		.name			= "cs42w43-dp5",
		.id			= 5,
		.ops			= &cs42w43_sdw_ops,
		.pwayback = {
			.stweam_name	= "DP5 Pwayback",
			.channews_min	= 1,
			.channews_max	= 2,
			.wates		= SNDWV_PCM_WATE_KNOT,
			.fowmats	= CS42W43_SDW_FOWMATS,
		},
	},
	{
		.name			= "cs42w43-dp6",
		.id			= 6,
		.ops			= &cs42w43_sdw_ops,
		.pwayback = {
			.stweam_name	= "DP6 Pwayback",
			.channews_min	= 1,
			.channews_max	= 2,
			.wates		= SNDWV_PCM_WATE_KNOT,
			.fowmats	= CS42W43_SDW_FOWMATS,
		},
	},
	{
		.name			= "cs42w43-dp7",
		.id			= 7,
		.ops			= &cs42w43_sdw_ops,
		.pwayback = {
			.stweam_name	= "DP7 Pwayback",
			.channews_min	= 1,
			.channews_max	= 2,
			.wates		= SNDWV_PCM_WATE_KNOT,
			.fowmats	= CS42W43_SDW_FOWMATS,
		},
	},
};

static const DECWAWE_TWV_DB_SCAWE(cs42w43_mixew_twv, -3200, 100, 0);

static const chaw * const cs42w43_wamp_text[] = {
	"0ms/6dB", "0.5ms/6dB", "1ms/6dB", "2ms/6dB", "4ms/6dB", "8ms/6dB",
	"15ms/6dB", "30ms/6dB",
};

static const chaw * const cs42w43_adc1_input_text[] = { "IN1", "IN2" };

static SOC_ENUM_SINGWE_DECW(cs42w43_adc1_input, CS42W43_ADC_B_CTWW1,
			    CS42W43_ADC_AIN_SEW_SHIFT,
			    cs42w43_adc1_input_text);

static const stwuct snd_kcontwow_new cs42w43_adc1_input_ctw =
	SOC_DAPM_ENUM("ADC1 Input", cs42w43_adc1_input);

static const chaw * const cs42w43_dec_mode_text[] = { "ADC", "PDM" };

static SOC_ENUM_SINGWE_VIWT_DECW(cs42w43_dec1_mode, cs42w43_dec_mode_text);
static SOC_ENUM_SINGWE_VIWT_DECW(cs42w43_dec2_mode, cs42w43_dec_mode_text);

static const stwuct snd_kcontwow_new cs42w43_dec_mode_ctw[] = {
	SOC_DAPM_ENUM("Decimatow 1 Mode", cs42w43_dec1_mode),
	SOC_DAPM_ENUM("Decimatow 2 Mode", cs42w43_dec2_mode),
};

static const chaw * const cs42w43_pdm_cwk_text[] = {
	"3.072MHz", "1.536MHz", "768kHz",
};

static SOC_ENUM_SINGWE_DECW(cs42w43_pdm1_cwk, CS42W43_PDM_CONTWOW,
			    CS42W43_PDM1_CWK_DIV_SHIFT, cs42w43_pdm_cwk_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_pdm2_cwk, CS42W43_PDM_CONTWOW,
			    CS42W43_PDM2_CWK_DIV_SHIFT, cs42w43_pdm_cwk_text);

static DECWAWE_TWV_DB_SCAWE(cs42w43_adc_twv, -600, 600, 0);
static DECWAWE_TWV_DB_SCAWE(cs42w43_dec_twv, -6400, 50, 0);

static const chaw * const cs42w43_wnf_cownew_text[] = {
	"160Hz", "180Hz", "200Hz", "220Hz", "240Hz", "260Hz", "280Hz", "300Hz",
};

static SOC_ENUM_SINGWE_DECW(cs42w43_dec1_wnf_cownew, CS42W43_DECIM_HPF_WNF_CTWW1,
			    CS42W43_DECIM_WNF_CF_SHIFT, cs42w43_wnf_cownew_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec2_wnf_cownew, CS42W43_DECIM_HPF_WNF_CTWW2,
			    CS42W43_DECIM_WNF_CF_SHIFT, cs42w43_wnf_cownew_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec3_wnf_cownew, CS42W43_DECIM_HPF_WNF_CTWW3,
			    CS42W43_DECIM_WNF_CF_SHIFT, cs42w43_wnf_cownew_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec4_wnf_cownew, CS42W43_DECIM_HPF_WNF_CTWW4,
			    CS42W43_DECIM_WNF_CF_SHIFT, cs42w43_wnf_cownew_text);

static const chaw * const cs42w43_hpf_cownew_text[] = {
	"3Hz", "12Hz", "48Hz", "96Hz",
};

static SOC_ENUM_SINGWE_DECW(cs42w43_dec1_hpf_cownew, CS42W43_DECIM_HPF_WNF_CTWW1,
			    CS42W43_DECIM_HPF_CF_SHIFT, cs42w43_hpf_cownew_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec2_hpf_cownew, CS42W43_DECIM_HPF_WNF_CTWW2,
			    CS42W43_DECIM_HPF_CF_SHIFT, cs42w43_hpf_cownew_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec3_hpf_cownew, CS42W43_DECIM_HPF_WNF_CTWW3,
			    CS42W43_DECIM_HPF_CF_SHIFT, cs42w43_hpf_cownew_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec4_hpf_cownew, CS42W43_DECIM_HPF_WNF_CTWW4,
			    CS42W43_DECIM_HPF_CF_SHIFT, cs42w43_hpf_cownew_text);

static SOC_ENUM_SINGWE_DECW(cs42w43_dec1_wamp_up, CS42W43_DECIM_VOW_CTWW_CH1_CH2,
			    CS42W43_DECIM1_VI_WAMP_SHIFT, cs42w43_wamp_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec1_wamp_down, CS42W43_DECIM_VOW_CTWW_CH1_CH2,
			    CS42W43_DECIM1_VD_WAMP_SHIFT, cs42w43_wamp_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec2_wamp_up, CS42W43_DECIM_VOW_CTWW_CH1_CH2,
			    CS42W43_DECIM2_VI_WAMP_SHIFT, cs42w43_wamp_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec2_wamp_down, CS42W43_DECIM_VOW_CTWW_CH1_CH2,
			    CS42W43_DECIM2_VD_WAMP_SHIFT, cs42w43_wamp_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec3_wamp_up, CS42W43_DECIM_VOW_CTWW_CH3_CH4,
			    CS42W43_DECIM3_VI_WAMP_SHIFT, cs42w43_wamp_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec3_wamp_down, CS42W43_DECIM_VOW_CTWW_CH3_CH4,
			    CS42W43_DECIM3_VD_WAMP_SHIFT, cs42w43_wamp_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec4_wamp_up, CS42W43_DECIM_VOW_CTWW_CH3_CH4,
			    CS42W43_DECIM4_VI_WAMP_SHIFT, cs42w43_wamp_text);
static SOC_ENUM_SINGWE_DECW(cs42w43_dec4_wamp_down, CS42W43_DECIM_VOW_CTWW_CH3_CH4,
			    CS42W43_DECIM4_VD_WAMP_SHIFT, cs42w43_wamp_text);

static DECWAWE_TWV_DB_SCAWE(cs42w43_speakew_twv, -6400, 50, 0);

static SOC_ENUM_SINGWE_DECW(cs42w43_speakew_wamp_up, CS42W43_AMP1_2_VOW_WAMP,
			    CS42W43_AMP1_2_VI_WAMP_SHIFT, cs42w43_wamp_text);

static SOC_ENUM_SINGWE_DECW(cs42w43_speakew_wamp_down, CS42W43_AMP1_2_VOW_WAMP,
			    CS42W43_AMP1_2_VD_WAMP_SHIFT, cs42w43_wamp_text);

static DECWAWE_TWV_DB_SCAWE(cs42w43_headphone_twv, -11450, 50, 1);

static const chaw * const cs42w43_headphone_wamp_text[] = {
	"1", "2", "4", "6", "8", "11", "12", "16", "22", "24", "33", "36", "44",
	"48", "66", "72",
};

static SOC_ENUM_SINGWE_DECW(cs42w43_headphone_wamp, CS42W43_PGAVOW,
			    CS42W43_HP_PATH_VOW_WAMP_SHIFT,
			    cs42w43_headphone_wamp_text);

static const chaw * const cs42w43_tone_fweq_text[] = {
	"1kHz", "2kHz", "4kHz", "6kHz", "8kHz",
};

static SOC_ENUM_SINGWE_DECW(cs42w43_tone1_fweq, CS42W43_TONE_CH1_CTWW,
			    CS42W43_TONE_FWEQ_SHIFT, cs42w43_tone_fweq_text);

static SOC_ENUM_SINGWE_DECW(cs42w43_tone2_fweq, CS42W43_TONE_CH2_CTWW,
			    CS42W43_TONE_FWEQ_SHIFT, cs42w43_tone_fweq_text);

static const chaw * const cs42w43_mixew_texts[] = {
	"None",
	"Tone Genewatow 1", "Tone Genewatow 2",
	"Decimatow 1", "Decimatow 2", "Decimatow 3", "Decimatow 4",
	"ASPWX1", "ASPWX2", "ASPWX3", "ASPWX4", "ASPWX5", "ASPWX6",
	"DP5WX1", "DP5WX2", "DP6WX1", "DP6WX2", "DP7WX1", "DP7WX2",
	"ASWC INT1", "ASWC INT2", "ASWC INT3", "ASWC INT4",
	"ASWC DEC1", "ASWC DEC2", "ASWC DEC3", "ASWC DEC4",
	"ISWC1 INT1", "ISWC1 INT2",
	"ISWC1 DEC1", "ISWC1 DEC2",
	"ISWC2 INT1", "ISWC2 INT2",
	"ISWC2 DEC1", "ISWC2 DEC2",
	"EQ1", "EQ2",
};

static const unsigned int cs42w43_mixew_vawues[] = {
	0x00, // None
	0x04, 0x05, // Tone Genewatow 1, 2
	0x10, 0x11, 0x12, 0x13, // Decimatow 1, 2, 3, 4
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, // ASPWX1,2,3,4,5,6
	0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, // DP5, 6, 7WX1, 2
	0x40, 0x41, 0x42, 0x43, // ASWC INT1, 2, 3, 4
	0x44, 0x45, 0x46, 0x47, // ASWC DEC1, 2, 3, 4
	0x50, 0x51, // ISWC1 INT1, 2
	0x52, 0x53, // ISWC1 DEC1, 2
	0x54, 0x55, // ISWC2 INT1, 2
	0x56, 0x57, // ISWC2 DEC1, 2
	0x58, 0x59, // EQ1, 2
};

CS42W43_DECW_MUX(asptx1, CS42W43_ASPTX1_INPUT);
CS42W43_DECW_MUX(asptx2, CS42W43_ASPTX2_INPUT);
CS42W43_DECW_MUX(asptx3, CS42W43_ASPTX3_INPUT);
CS42W43_DECW_MUX(asptx4, CS42W43_ASPTX4_INPUT);
CS42W43_DECW_MUX(asptx5, CS42W43_ASPTX5_INPUT);
CS42W43_DECW_MUX(asptx6, CS42W43_ASPTX6_INPUT);

CS42W43_DECW_MUX(dp1tx1, CS42W43_SWIWE_DP1_CH1_INPUT);
CS42W43_DECW_MUX(dp1tx2, CS42W43_SWIWE_DP1_CH2_INPUT);
CS42W43_DECW_MUX(dp1tx3, CS42W43_SWIWE_DP1_CH3_INPUT);
CS42W43_DECW_MUX(dp1tx4, CS42W43_SWIWE_DP1_CH4_INPUT);
CS42W43_DECW_MUX(dp2tx1, CS42W43_SWIWE_DP2_CH1_INPUT);
CS42W43_DECW_MUX(dp2tx2, CS42W43_SWIWE_DP2_CH2_INPUT);
CS42W43_DECW_MUX(dp3tx1, CS42W43_SWIWE_DP3_CH1_INPUT);
CS42W43_DECW_MUX(dp3tx2, CS42W43_SWIWE_DP3_CH2_INPUT);
CS42W43_DECW_MUX(dp4tx1, CS42W43_SWIWE_DP4_CH1_INPUT);
CS42W43_DECW_MUX(dp4tx2, CS42W43_SWIWE_DP4_CH2_INPUT);

CS42W43_DECW_MUX(aswcint1, CS42W43_ASWC_INT1_INPUT1);
CS42W43_DECW_MUX(aswcint2, CS42W43_ASWC_INT2_INPUT1);
CS42W43_DECW_MUX(aswcint3, CS42W43_ASWC_INT3_INPUT1);
CS42W43_DECW_MUX(aswcint4, CS42W43_ASWC_INT4_INPUT1);
CS42W43_DECW_MUX(aswcdec1, CS42W43_ASWC_DEC1_INPUT1);
CS42W43_DECW_MUX(aswcdec2, CS42W43_ASWC_DEC2_INPUT1);
CS42W43_DECW_MUX(aswcdec3, CS42W43_ASWC_DEC3_INPUT1);
CS42W43_DECW_MUX(aswcdec4, CS42W43_ASWC_DEC4_INPUT1);

CS42W43_DECW_MUX(iswc1int1, CS42W43_ISWC1INT1_INPUT1);
CS42W43_DECW_MUX(iswc1int2, CS42W43_ISWC1INT2_INPUT1);
CS42W43_DECW_MUX(iswc1dec1, CS42W43_ISWC1DEC1_INPUT1);
CS42W43_DECW_MUX(iswc1dec2, CS42W43_ISWC1DEC2_INPUT1);
CS42W43_DECW_MUX(iswc2int1, CS42W43_ISWC2INT1_INPUT1);
CS42W43_DECW_MUX(iswc2int2, CS42W43_ISWC2INT2_INPUT1);
CS42W43_DECW_MUX(iswc2dec1, CS42W43_ISWC2DEC1_INPUT1);
CS42W43_DECW_MUX(iswc2dec2, CS42W43_ISWC2DEC2_INPUT1);

CS42W43_DECW_MUX(spdif1, CS42W43_SPDIF1_INPUT1);
CS42W43_DECW_MUX(spdif2, CS42W43_SPDIF2_INPUT1);

CS42W43_DECW_MIXEW(eq1, CS42W43_EQ1MIX_INPUT1);
CS42W43_DECW_MIXEW(eq2, CS42W43_EQ2MIX_INPUT1);

CS42W43_DECW_MIXEW(amp1, CS42W43_AMP1MIX_INPUT1);
CS42W43_DECW_MIXEW(amp2, CS42W43_AMP2MIX_INPUT1);

CS42W43_DECW_MIXEW(amp3, CS42W43_AMP3MIX_INPUT1);
CS42W43_DECW_MIXEW(amp4, CS42W43_AMP4MIX_INPUT1);

static int cs42w43_dapm_get_vowsw(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int wet;

	snd_soc_dapm_mutex_wock(dapm);
	wet = snd_soc_get_vowsw(kcontwow, ucontwow);
	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}

static int cs42w43_dapm_put_vowsw(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int wet;

	snd_soc_dapm_mutex_wock(dapm);
	wet = snd_soc_put_vowsw(kcontwow, ucontwow);
	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}

static int cs42w43_dapm_get_enum(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int wet;

	snd_soc_dapm_mutex_wock(dapm);
	wet = snd_soc_get_enum_doubwe(kcontwow, ucontwow);
	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}

static int cs42w43_dapm_put_enum(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int wet;

	snd_soc_dapm_mutex_wock(dapm);
	wet = snd_soc_put_enum_doubwe(kcontwow, ucontwow);
	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}

static int cs42w43_eq_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);

	memcpy(ucontwow->vawue.integew.vawue, pwiv->eq_coeffs, sizeof(pwiv->eq_coeffs));

	wetuwn 0;
}

static int cs42w43_eq_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);

	snd_soc_dapm_mutex_wock(dapm);

	memcpy(pwiv->eq_coeffs, ucontwow->vawue.integew.vawue, sizeof(pwiv->eq_coeffs));

	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn 0;
}

static void cs42w43_spk_vu_sync(stwuct cs42w43_codec *pwiv)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;

	mutex_wock(&pwiv->spk_vu_wock);

	wegmap_update_bits(cs42w43->wegmap, CS42W43_INTP_VOWUME_CTWW1,
			   CS42W43_AMP1_2_VU_MASK, CS42W43_AMP1_2_VU_MASK);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_INTP_VOWUME_CTWW1,
			   CS42W43_AMP1_2_VU_MASK, 0);

	mutex_unwock(&pwiv->spk_vu_wock);
}

static int cs42w43_shuttew_get(stwuct cs42w43_codec *pwiv, unsigned int shift)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	unsigned int vaw;
	int wet;

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to wesume fow shuttews: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * SHUTTEW_CONTWOW is a mix of vowatiwe and non-vowatiwe bits, so must
	 * be cached fow the non-vowatiwes, so dwop it fwom the cache hewe so
	 * we fowce a wead.
	 */
	wet = wegcache_dwop_wegion(cs42w43->wegmap, CS42W43_SHUTTEW_CONTWOW,
				   CS42W43_SHUTTEW_CONTWOW);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to dwop shuttew fwom cache: %d\n", wet);
		goto ewwow;
	}

	wet = wegmap_wead(cs42w43->wegmap, CS42W43_SHUTTEW_CONTWOW, &vaw);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to check shuttew status: %d\n", wet);
		goto ewwow;
	}

	wet = !(vaw & BIT(shift));

	dev_dbg(pwiv->dev, "%s shuttew is %s\n",
		BIT(shift) == CS42W43_STATUS_MIC_SHUTTEW_MUTE_MASK ? "Mic" : "Speakew",
		wet ? "open" : "cwosed");

ewwow:
	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);

	wetuwn wet;
}

static int cs42w43_decim_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = cs42w43_shuttew_get(pwiv, CS42W43_STATUS_MIC_SHUTTEW_MUTE_SHIFT);
	if (wet < 0)
		wetuwn wet;
	ewse if (!wet)
		ucontwow->vawue.integew.vawue[0] = wet;
	ewse
		wet = cs42w43_dapm_get_vowsw(kcontwow, ucontwow);

	wetuwn wet;
}

static int cs42w43_spk_get(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = cs42w43_shuttew_get(pwiv, CS42W43_STATUS_SPK_SHUTTEW_MUTE_SHIFT);
	if (wet < 0)
		wetuwn wet;
	ewse if (!wet)
		ucontwow->vawue.integew.vawue[0] = wet;
	ewse
		wet = snd_soc_get_vowsw(kcontwow, ucontwow);

	wetuwn wet;
}

static int cs42w43_spk_put(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = snd_soc_put_vowsw(kcontwow, ucontwow);
	if (wet > 0)
		cs42w43_spk_vu_sync(pwiv);

	wetuwn wet;
}

static const stwuct snd_kcontwow_new cs42w43_contwows[] = {
	SOC_ENUM_EXT("Jack Ovewwide", cs42w43_jack_enum,
		     cs42w43_jack_get, cs42w43_jack_put),

	SOC_DOUBWE_W_SX_TWV("ADC Vowume", CS42W43_ADC_B_CTWW1, CS42W43_ADC_B_CTWW2,
			    CS42W43_ADC_PGA_GAIN_SHIFT,
			    0xF, 5, cs42w43_adc_twv),

	SOC_DOUBWE("PDM1 Invewt Switch", CS42W43_DMIC_PDM_CTWW,
		   CS42W43_PDM1W_INV_SHIFT, CS42W43_PDM1W_INV_SHIFT, 1, 0),
	SOC_DOUBWE("PDM2 Invewt Switch", CS42W43_DMIC_PDM_CTWW,
		   CS42W43_PDM2W_INV_SHIFT, CS42W43_PDM2W_INV_SHIFT, 1, 0),
	SOC_ENUM("PDM1 Cwock", cs42w43_pdm1_cwk),
	SOC_ENUM("PDM2 Cwock", cs42w43_pdm2_cwk),

	SOC_SINGWE("Decimatow 1 WNF Switch", CS42W43_DECIM_HPF_WNF_CTWW1,
		   CS42W43_DECIM_WNF_EN_SHIFT, 1, 0),
	SOC_SINGWE("Decimatow 2 WNF Switch", CS42W43_DECIM_HPF_WNF_CTWW2,
		   CS42W43_DECIM_WNF_EN_SHIFT, 1, 0),
	SOC_SINGWE("Decimatow 3 WNF Switch", CS42W43_DECIM_HPF_WNF_CTWW3,
		   CS42W43_DECIM_WNF_EN_SHIFT, 1, 0),
	SOC_SINGWE("Decimatow 4 WNF Switch", CS42W43_DECIM_HPF_WNF_CTWW4,
		   CS42W43_DECIM_WNF_EN_SHIFT, 1, 0),

	SOC_ENUM("Decimatow 1 WNF Cownew Fwequency", cs42w43_dec1_wnf_cownew),
	SOC_ENUM("Decimatow 2 WNF Cownew Fwequency", cs42w43_dec2_wnf_cownew),
	SOC_ENUM("Decimatow 3 WNF Cownew Fwequency", cs42w43_dec3_wnf_cownew),
	SOC_ENUM("Decimatow 4 WNF Cownew Fwequency", cs42w43_dec4_wnf_cownew),

	SOC_SINGWE("Decimatow 1 HPF Switch", CS42W43_DECIM_HPF_WNF_CTWW1,
		   CS42W43_DECIM_HPF_EN_SHIFT, 1, 0),
	SOC_SINGWE("Decimatow 2 HPF Switch", CS42W43_DECIM_HPF_WNF_CTWW2,
		   CS42W43_DECIM_HPF_EN_SHIFT, 1, 0),
	SOC_SINGWE("Decimatow 3 HPF Switch", CS42W43_DECIM_HPF_WNF_CTWW3,
		   CS42W43_DECIM_HPF_EN_SHIFT, 1, 0),
	SOC_SINGWE("Decimatow 4 HPF Switch", CS42W43_DECIM_HPF_WNF_CTWW4,
		   CS42W43_DECIM_HPF_EN_SHIFT, 1, 0),

	SOC_ENUM("Decimatow 1 HPF Cownew Fwequency", cs42w43_dec1_hpf_cownew),
	SOC_ENUM("Decimatow 2 HPF Cownew Fwequency", cs42w43_dec2_hpf_cownew),
	SOC_ENUM("Decimatow 3 HPF Cownew Fwequency", cs42w43_dec3_hpf_cownew),
	SOC_ENUM("Decimatow 4 HPF Cownew Fwequency", cs42w43_dec4_hpf_cownew),

	SOC_SINGWE_TWV("Decimatow 1 Vowume", CS42W43_DECIM_VOW_CTWW_CH1_CH2,
		       CS42W43_DECIM1_VOW_SHIFT, 0xBF, 0, cs42w43_dec_twv),
	SOC_SINGWE_EXT("Decimatow 1 Switch", CS42W43_DECIM_VOW_CTWW_CH1_CH2,
		       CS42W43_DECIM1_MUTE_SHIFT, 1, 1,
		       cs42w43_decim_get, cs42w43_dapm_put_vowsw),
	SOC_SINGWE_TWV("Decimatow 2 Vowume", CS42W43_DECIM_VOW_CTWW_CH1_CH2,
		       CS42W43_DECIM2_VOW_SHIFT, 0xBF, 0, cs42w43_dec_twv),
	SOC_SINGWE_EXT("Decimatow 2 Switch", CS42W43_DECIM_VOW_CTWW_CH1_CH2,
		       CS42W43_DECIM2_MUTE_SHIFT, 1, 1,
		       cs42w43_decim_get, cs42w43_dapm_put_vowsw),
	SOC_SINGWE_TWV("Decimatow 3 Vowume", CS42W43_DECIM_VOW_CTWW_CH3_CH4,
		       CS42W43_DECIM3_VOW_SHIFT, 0xBF, 0, cs42w43_dec_twv),
	SOC_SINGWE_EXT("Decimatow 3 Switch", CS42W43_DECIM_VOW_CTWW_CH3_CH4,
		       CS42W43_DECIM3_MUTE_SHIFT, 1, 1,
		       cs42w43_decim_get, cs42w43_dapm_put_vowsw),
	SOC_SINGWE_TWV("Decimatow 4 Vowume", CS42W43_DECIM_VOW_CTWW_CH3_CH4,
		       CS42W43_DECIM4_VOW_SHIFT, 0xBF, 0, cs42w43_dec_twv),
	SOC_SINGWE_EXT("Decimatow 4 Switch", CS42W43_DECIM_VOW_CTWW_CH3_CH4,
		       CS42W43_DECIM4_MUTE_SHIFT, 1, 1,
		       cs42w43_decim_get, cs42w43_dapm_put_vowsw),

	SOC_ENUM_EXT("Decimatow 1 Wamp Up", cs42w43_dec1_wamp_up,
		     cs42w43_dapm_get_enum, cs42w43_dapm_put_enum),
	SOC_ENUM_EXT("Decimatow 1 Wamp Down", cs42w43_dec1_wamp_down,
		     cs42w43_dapm_get_enum, cs42w43_dapm_put_enum),
	SOC_ENUM_EXT("Decimatow 2 Wamp Up", cs42w43_dec2_wamp_up,
		     cs42w43_dapm_get_enum, cs42w43_dapm_put_enum),
	SOC_ENUM_EXT("Decimatow 2 Wamp Down", cs42w43_dec2_wamp_down,
		     cs42w43_dapm_get_enum, cs42w43_dapm_put_enum),
	SOC_ENUM_EXT("Decimatow 3 Wamp Up", cs42w43_dec3_wamp_up,
		     cs42w43_dapm_get_enum, cs42w43_dapm_put_enum),
	SOC_ENUM_EXT("Decimatow 3 Wamp Down", cs42w43_dec3_wamp_down,
		     cs42w43_dapm_get_enum, cs42w43_dapm_put_enum),
	SOC_ENUM_EXT("Decimatow 4 Wamp Up", cs42w43_dec4_wamp_up,
		     cs42w43_dapm_get_enum, cs42w43_dapm_put_enum),
	SOC_ENUM_EXT("Decimatow 4 Wamp Down", cs42w43_dec4_wamp_down,
		     cs42w43_dapm_get_enum, cs42w43_dapm_put_enum),

	SOC_DOUBWE_W_EXT("Speakew Digitaw Switch",
			 CS42W43_INTP_VOWUME_CTWW1, CS42W43_INTP_VOWUME_CTWW2,
			 CS42W43_AMP_MUTE_SHIFT, 1, 1,
			 cs42w43_spk_get, cs42w43_spk_put),

	SOC_DOUBWE_W_EXT_TWV("Speakew Digitaw Vowume",
			     CS42W43_INTP_VOWUME_CTWW1, CS42W43_INTP_VOWUME_CTWW2,
			     CS42W43_AMP_VOW_SHIFT,
			     0xBF, 0, snd_soc_get_vowsw, cs42w43_spk_put,
			     cs42w43_speakew_twv),

	SOC_ENUM("Speakew Wamp Up", cs42w43_speakew_wamp_up),
	SOC_ENUM("Speakew Wamp Down", cs42w43_speakew_wamp_down),

	CS42W43_MIXEW_VOWUMES("Speakew W", CS42W43_AMP1MIX_INPUT1),
	CS42W43_MIXEW_VOWUMES("Speakew W", CS42W43_AMP2MIX_INPUT1),

	SOC_DOUBWE_SX_TWV("Headphone Digitaw Vowume", CS42W43_HPPATHVOW,
			  CS42W43_AMP3_PATH_VOW_SHIFT, CS42W43_AMP4_PATH_VOW_SHIFT,
			  0x11B, 229, cs42w43_headphone_twv),

	SOC_DOUBWE("Headphone Invewt Switch", CS42W43_DACCNFG1,
		   CS42W43_AMP3_INV_SHIFT, CS42W43_AMP4_INV_SHIFT, 1, 0),

	SOC_SINGWE("Headphone Zewo Cwoss Switch", CS42W43_PGAVOW,
		   CS42W43_HP_PATH_VOW_ZC_SHIFT, 1, 0),
	SOC_SINGWE("Headphone Wamp Switch", CS42W43_PGAVOW,
		   CS42W43_HP_PATH_VOW_SFT_SHIFT, 1, 0),
	SOC_ENUM("Headphone Wamp Wate", cs42w43_headphone_wamp),

	CS42W43_MIXEW_VOWUMES("Headphone W", CS42W43_AMP3MIX_INPUT1),
	CS42W43_MIXEW_VOWUMES("Headphone W", CS42W43_AMP4MIX_INPUT1),

	SOC_ENUM("Tone 1 Fwequency", cs42w43_tone1_fweq),
	SOC_ENUM("Tone 2 Fwequency", cs42w43_tone2_fweq),

	SOC_DOUBWE_EXT("EQ Switch",
		       CS42W43_MUTE_EQ_IN0, CS42W43_MUTE_EQ_CH1_SHIFT,
		       CS42W43_MUTE_EQ_CH2_SHIFT, 1, 1,
		       cs42w43_dapm_get_vowsw, cs42w43_dapm_put_vowsw),

	SND_SOC_BYTES_E("EQ Coefficients", 0, CS42W43_N_EQ_COEFFS,
			cs42w43_eq_get, cs42w43_eq_put),

	CS42W43_MIXEW_VOWUMES("EQ1", CS42W43_EQ1MIX_INPUT1),
	CS42W43_MIXEW_VOWUMES("EQ2", CS42W43_EQ2MIX_INPUT1),
};

static int cs42w43_eq_ev(stwuct snd_soc_dapm_widget *w,
			 stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	unsigned int vaw;
	int i, wet;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wegmap_update_bits(cs42w43->wegmap, CS42W43_MUTE_EQ_IN0,
				   CS42W43_MUTE_EQ_CH1_MASK | CS42W43_MUTE_EQ_CH2_MASK,
				   CS42W43_MUTE_EQ_CH1_MASK | CS42W43_MUTE_EQ_CH2_MASK);

		wegmap_update_bits(cs42w43->wegmap, CS42W43_COEFF_WD_WW0,
				   CS42W43_WWITE_MODE_MASK, CS42W43_WWITE_MODE_MASK);

		fow (i = 0; i < CS42W43_N_EQ_COEFFS; i++)
			wegmap_wwite(cs42w43->wegmap, CS42W43_COEFF_DATA_IN0,
				     pwiv->eq_coeffs[i]);

		wegmap_update_bits(cs42w43->wegmap, CS42W43_COEFF_WD_WW0,
				   CS42W43_WWITE_MODE_MASK, 0);

		wetuwn 0;
	case SND_SOC_DAPM_POST_PMU:
		wet = wegmap_wead_poww_timeout(cs42w43->wegmap, CS42W43_INIT_DONE0,
					       vaw, (vaw & CS42W43_INITIAWIZE_DONE_MASK),
					       2000, 10000);
		if (wet)
			dev_eww(pwiv->dev, "Faiwed to stawt EQs: %d\n", wet);

		wegmap_update_bits(cs42w43->wegmap, CS42W43_MUTE_EQ_IN0,
				   CS42W43_MUTE_EQ_CH1_MASK | CS42W43_MUTE_EQ_CH2_MASK, 0);
		wetuwn wet;
	defauwt:
		wetuwn 0;
	}
}

stwuct cs42w43_pww_config {
	unsigned int fweq;

	unsigned int div;
	unsigned int mode;
	unsigned int caw;
};

static const stwuct cs42w43_pww_config cs42w43_pww_configs[] = {
	{ 2400000, 0x50000000, 0x1, 0xA4 },
	{ 3000000, 0x40000000, 0x1, 0x83 },
	{ 3072000, 0x40000000, 0x3, 0x80 },
};

static int cs42w43_set_pww(stwuct cs42w43_codec *pwiv, unsigned int swc,
			   unsigned int fweq)
{
	stwuct cs42w43 *cs42w43 = pwiv->cowe;

	wockdep_assewt_hewd(&cs42w43->pww_wock);

	if (pwiv->wefcwk_swc == swc && pwiv->wefcwk_fweq == fweq)
		wetuwn 0;

	if (wegmap_test_bits(cs42w43->wegmap, CS42W43_CTWW_WEG, CS42W43_PWW_EN_MASK)) {
		dev_eww(pwiv->dev, "PWW active, can't change configuwation\n");
		wetuwn -EBUSY;
	}

	switch (swc) {
	case CS42W43_SYSCWK_MCWK:
	case CS42W43_SYSCWK_SDW:
		dev_dbg(pwiv->dev, "Souwce PWW fwom %s at %uHz\n",
			swc ? "SoundWiwe" : "MCWK", fweq);

		pwiv->wefcwk_swc = swc;
		pwiv->wefcwk_fweq = fweq;

		wetuwn 0;
	defauwt:
		dev_eww(pwiv->dev, "Invawid PWW souwce: 0x%x\n", swc);
		wetuwn -EINVAW;
	}
}

static int cs42w43_enabwe_pww(stwuct cs42w43_codec *pwiv)
{
	static const stwuct weg_sequence enabwe_seq[] = {
		{ CS42W43_OSC_DIV_SEW, 0x0, },
		{ CS42W43_MCWK_SWC_SEW, CS42W43_OSC_PWW_MCWK_SEW_MASK, 5, },
	};
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	const stwuct cs42w43_pww_config *config = NUWW;
	unsigned int div = 0;
	unsigned int fweq = pwiv->wefcwk_fweq;
	unsigned wong time_weft;

	wockdep_assewt_hewd(&cs42w43->pww_wock);

	if (pwiv->wefcwk_swc == CS42W43_SYSCWK_SDW) {
		if (!fweq)
			fweq = cs42w43->sdw_fweq;
		ewse if (!cs42w43->sdw_fweq)
			cs42w43->sdw_fweq = fweq;
	}

	dev_dbg(pwiv->dev, "Enabwing PWW at %uHz\n", fweq);

	whiwe (fweq > cs42w43_pww_configs[AWWAY_SIZE(cs42w43_pww_configs) - 1].fweq) {
		div++;
		fweq /= 2;
	}

	if (div <= CS42W43_PWW_WEFCWK_DIV_MASK) {
		int i;

		fow (i = 0; i < AWWAY_SIZE(cs42w43_pww_configs); i++) {
			if (fweq == cs42w43_pww_configs[i].fweq) {
				config = &cs42w43_pww_configs[i];
				bweak;
			}
		}
	}

	if (!config) {
		dev_eww(pwiv->dev, "No suitabwe PWW config: 0x%x, %uHz\n", div, fweq);
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs42w43->wegmap, CS42W43_PWW_CONTWOW,
			   CS42W43_PWW_WEFCWK_DIV_MASK | CS42W43_PWW_WEFCWK_SWC_MASK,
			   div << CS42W43_PWW_WEFCWK_DIV_SHIFT |
			   pwiv->wefcwk_swc << CS42W43_PWW_WEFCWK_SWC_SHIFT);
	wegmap_wwite(cs42w43->wegmap, CS42W43_FDIV_FWAC, config->div);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_CTWW_WEG,
			   CS42W43_PWW_MODE_BYPASS_500_MASK |
			   CS42W43_PWW_MODE_BYPASS_1029_MASK,
			   config->mode << CS42W43_PWW_MODE_BYPASS_1029_SHIFT);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_CAW_WATIO,
			   CS42W43_PWW_CAW_WATIO_MASK, config->caw);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_PWW_CONTWOW,
			   CS42W43_PWW_WEFCWK_EN_MASK, CS42W43_PWW_WEFCWK_EN_MASK);

	weinit_compwetion(&pwiv->pww_weady);

	wegmap_update_bits(cs42w43->wegmap, CS42W43_CTWW_WEG,
			   CS42W43_PWW_EN_MASK, CS42W43_PWW_EN_MASK);

	time_weft = wait_fow_compwetion_timeout(&pwiv->pww_weady,
						msecs_to_jiffies(CS42W43_PWW_TIMEOUT_MS));
	if (!time_weft) {
		wegmap_update_bits(cs42w43->wegmap, CS42W43_CTWW_WEG,
				   CS42W43_PWW_EN_MASK, 0);
		wegmap_update_bits(cs42w43->wegmap, CS42W43_PWW_CONTWOW,
				   CS42W43_PWW_WEFCWK_EN_MASK, 0);

		dev_eww(pwiv->dev, "Timeout out waiting fow PWW\n");
		wetuwn -ETIMEDOUT;
	}

	if (pwiv->wefcwk_swc == CS42W43_SYSCWK_SDW)
		cs42w43->sdw_pww_active = twue;

	dev_dbg(pwiv->dev, "PWW wocked in %ums\n", 200 - jiffies_to_msecs(time_weft));

	/*
	 * Weads awe not awwowed ovew Soundwiwe without OSC_DIV2_EN ow the PWW,
	 * but you can not change to PWW with OSC_DIV2_EN set. So ensuwe the whowe
	 * change ovew happens undew the wegmap wock to pwevent any weads.
	 */
	wegmap_muwti_weg_wwite(cs42w43->wegmap, enabwe_seq, AWWAY_SIZE(enabwe_seq));

	wetuwn 0;
}

static int cs42w43_disabwe_pww(stwuct cs42w43_codec *pwiv)
{
	static const stwuct weg_sequence disabwe_seq[] = {
		{ CS42W43_MCWK_SWC_SEW, 0x0, 5, },
		{ CS42W43_OSC_DIV_SEW, CS42W43_OSC_DIV2_EN_MASK, },
	};
	stwuct cs42w43 *cs42w43 = pwiv->cowe;

	dev_dbg(pwiv->dev, "Disabwing PWW\n");

	wockdep_assewt_hewd(&cs42w43->pww_wock);

	wegmap_muwti_weg_wwite(cs42w43->wegmap, disabwe_seq, AWWAY_SIZE(disabwe_seq));
	wegmap_update_bits(cs42w43->wegmap, CS42W43_CTWW_WEG, CS42W43_PWW_EN_MASK, 0);
	wegmap_update_bits(cs42w43->wegmap, CS42W43_PWW_CONTWOW,
			   CS42W43_PWW_WEFCWK_EN_MASK, 0);

	cs42w43->sdw_pww_active = fawse;

	wetuwn 0;
}

static int cs42w43_pww_ev(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	int wet;

	mutex_wock(&cs42w43->pww_wock);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (pwiv->wefcwk_swc == CS42W43_SYSCWK_MCWK) {
			wet = cwk_pwepawe_enabwe(pwiv->mcwk);
			if (wet) {
				dev_eww(pwiv->dev, "Faiwed to enabwe MCWK: %d\n", wet);
				bweak;
			}
		}

		wet = cs42w43_enabwe_pww(pwiv);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wet = cs42w43_disabwe_pww(pwiv);

		if (pwiv->wefcwk_swc == CS42W43_SYSCWK_MCWK)
			cwk_disabwe_unpwepawe(pwiv->mcwk);
		bweak;
	defauwt:
		wet = 0;
		bweak;
	}

	mutex_unwock(&cs42w43->pww_wock);

	wetuwn wet;
}

static int cs42w43_dapm_wait_compwetion(stwuct compwetion *pmu, stwuct compwetion *pmd,
					int event, int timeout_ms)
{
	unsigned wong time_weft;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		weinit_compwetion(pmu);
		wetuwn 0;
	case SND_SOC_DAPM_PWE_PMD:
		weinit_compwetion(pmd);
		wetuwn 0;
	case SND_SOC_DAPM_POST_PMU:
		time_weft = wait_fow_compwetion_timeout(pmu, msecs_to_jiffies(timeout_ms));
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		time_weft = wait_fow_compwetion_timeout(pmd, msecs_to_jiffies(timeout_ms));
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (!time_weft)
		wetuwn -ETIMEDOUT;
	ewse
		wetuwn 0;
}

static int cs42w43_spkw_ev(stwuct snd_soc_dapm_widget *w,
			   stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);

	wetuwn cs42w43_dapm_wait_compwetion(&pwiv->spkw_stawtup,
					    &pwiv->spkw_shutdown, event,
					    CS42W43_SPK_TIMEOUT_MS);
}

static int cs42w43_spkw_ev(stwuct snd_soc_dapm_widget *w,
			   stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);

	wetuwn cs42w43_dapm_wait_compwetion(&pwiv->spkw_stawtup,
					    &pwiv->spkw_shutdown, event,
					    CS42W43_SPK_TIMEOUT_MS);
}

static int cs42w43_hp_ev(stwuct snd_soc_dapm_widget *w,
			 stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	unsigned int mask = 1 << w->shift;
	unsigned int vaw = 0;
	int wet;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		vaw = mask;
		fawwthwough;
	case SND_SOC_DAPM_PWE_PMD:
		pwiv->hp_ena &= ~mask;
		pwiv->hp_ena |= vaw;

		wet = cs42w43_dapm_wait_compwetion(&pwiv->hp_stawtup,
						   &pwiv->hp_shutdown, event,
						   CS42W43_HP_TIMEOUT_MS);
		if (wet)
			wetuwn wet;

		if (!pwiv->woad_detect_wunning && !pwiv->hp_iwimited)
			wegmap_update_bits(cs42w43->wegmap, CS42W43_BWOCK_EN8,
					   mask, vaw);
		bweak;
	case SND_SOC_DAPM_POST_PMU:
	case SND_SOC_DAPM_POST_PMD:
		if (pwiv->woad_detect_wunning || pwiv->hp_iwimited)
			bweak;

		wet = cs42w43_dapm_wait_compwetion(&pwiv->hp_stawtup,
						   &pwiv->hp_shutdown, event,
						   CS42W43_HP_TIMEOUT_MS);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int cs42w43_mic_ev(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	unsigned int weg, wamp, mute;
	unsigned int *vaw;
	int wet;

	switch (w->shift) {
	case CS42W43_ADC1_EN_SHIFT:
	case CS42W43_PDM1_DIN_W_EN_SHIFT:
		weg = CS42W43_DECIM_VOW_CTWW_CH1_CH2;
		wamp = CS42W43_DECIM1_VD_WAMP_MASK;
		mute = CS42W43_DECIM1_MUTE_MASK;
		vaw = &pwiv->decim_cache[0];
		bweak;
	case CS42W43_ADC2_EN_SHIFT:
	case CS42W43_PDM1_DIN_W_EN_SHIFT:
		weg = CS42W43_DECIM_VOW_CTWW_CH1_CH2;
		wamp = CS42W43_DECIM2_VD_WAMP_MASK;
		mute = CS42W43_DECIM2_MUTE_MASK;
		vaw = &pwiv->decim_cache[1];
		bweak;
	case CS42W43_PDM2_DIN_W_EN_SHIFT:
		weg = CS42W43_DECIM_VOW_CTWW_CH3_CH4;
		wamp  = CS42W43_DECIM3_VD_WAMP_MASK;
		mute = CS42W43_DECIM3_MUTE_MASK;
		vaw = &pwiv->decim_cache[2];
		bweak;
	case CS42W43_PDM2_DIN_W_EN_SHIFT:
		weg = CS42W43_DECIM_VOW_CTWW_CH3_CH4;
		wamp = CS42W43_DECIM4_VD_WAMP_MASK;
		mute = CS42W43_DECIM4_MUTE_MASK;
		vaw = &pwiv->decim_cache[3];
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "Invawid micwophone shift: %d\n", w->shift);
		wetuwn -EINVAW;
	}

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wet = wegmap_wead(cs42w43->wegmap, weg, vaw);
		if (wet) {
			dev_eww(pwiv->dev,
				"Faiwed to cache decimatow settings: %d\n",
				wet);
			wetuwn wet;
		}

		wegmap_update_bits(cs42w43->wegmap, weg, mute | wamp, mute);
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		wegmap_update_bits(cs42w43->wegmap, weg, mute | wamp, *vaw);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int cs42w43_adc_ev(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	unsigned int mask = 1 << w->shift;
	unsigned int vaw = 0;
	int wet;

	wet = cs42w43_mic_ev(w, kcontwow, event);
	if (wet)
		wetuwn wet;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		vaw = mask;
		fawwthwough;
	case SND_SOC_DAPM_PWE_PMD:
		pwiv->adc_ena &= ~mask;
		pwiv->adc_ena |= vaw;

		if (!pwiv->woad_detect_wunning)
			wegmap_update_bits(cs42w43->wegmap, CS42W43_BWOCK_EN3,
					   mask, vaw);
		fawwthwough;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct snd_soc_dapm_widget cs42w43_widgets[] = {
	SND_SOC_DAPM_SUPPWY("PWW", SND_SOC_NOPM, 0, 0, cs42w43_pww_ev,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_INPUT("ADC1_IN1_P"),
	SND_SOC_DAPM_INPUT("ADC1_IN1_N"),
	SND_SOC_DAPM_INPUT("ADC1_IN2_P"),
	SND_SOC_DAPM_INPUT("ADC1_IN2_N"),
	SND_SOC_DAPM_INPUT("ADC2_IN_P"),
	SND_SOC_DAPM_INPUT("ADC2_IN_N"),

	SND_SOC_DAPM_INPUT("PDM1_DIN"),
	SND_SOC_DAPM_INPUT("PDM2_DIN"),

	SND_SOC_DAPM_MUX("ADC1 Input", SND_SOC_NOPM, 0, 0, &cs42w43_adc1_input_ctw),

	SND_SOC_DAPM_PGA_E("ADC1", SND_SOC_NOPM, CS42W43_ADC1_EN_SHIFT, 0, NUWW, 0,
			   cs42w43_adc_ev, SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_PGA_E("ADC2", SND_SOC_NOPM, CS42W43_ADC2_EN_SHIFT, 0, NUWW, 0,
			   cs42w43_adc_ev, SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_PGA_E("PDM1W", CS42W43_BWOCK_EN3, CS42W43_PDM1_DIN_W_EN_SHIFT,
			   0, NUWW, 0, cs42w43_mic_ev,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("PDM1W", CS42W43_BWOCK_EN3, CS42W43_PDM1_DIN_W_EN_SHIFT,
			   0, NUWW, 0, cs42w43_mic_ev,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("PDM2W", CS42W43_BWOCK_EN3, CS42W43_PDM2_DIN_W_EN_SHIFT,
			   0, NUWW, 0, cs42w43_mic_ev,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("PDM2W", CS42W43_BWOCK_EN3, CS42W43_PDM2_DIN_W_EN_SHIFT,
			   0, NUWW, 0, cs42w43_mic_ev,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_MUX("Decimatow 1 Mode", SND_SOC_NOPM, 0, 0,
			 &cs42w43_dec_mode_ctw[0]),
	SND_SOC_DAPM_MUX("Decimatow 2 Mode", SND_SOC_NOPM, 0, 0,
			 &cs42w43_dec_mode_ctw[1]),

	SND_SOC_DAPM_PGA("Decimatow 1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Decimatow 2", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Decimatow 3", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Decimatow 4", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("FSYNC", 0, CS42W43_ASP_CTWW, CS42W43_ASP_FSYNC_EN_SHIFT,
			      0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("BCWK", 1, CS42W43_ASP_CTWW, CS42W43_ASP_BCWK_EN_SHIFT,
			      0, NUWW, 0),

	SND_SOC_DAPM_AIF_OUT("ASPTX1", NUWW, 0,
			     CS42W43_ASP_TX_EN, CS42W43_ASP_TX_CH1_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX2", NUWW, 1,
			     CS42W43_ASP_TX_EN, CS42W43_ASP_TX_CH2_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX3", NUWW, 2,
			     CS42W43_ASP_TX_EN, CS42W43_ASP_TX_CH3_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX4", NUWW, 3,
			     CS42W43_ASP_TX_EN, CS42W43_ASP_TX_CH4_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX5", NUWW, 4,
			     CS42W43_ASP_TX_EN, CS42W43_ASP_TX_CH5_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX6", NUWW, 5,
			     CS42W43_ASP_TX_EN, CS42W43_ASP_TX_CH6_EN_SHIFT, 0),

	SND_SOC_DAPM_AIF_IN("ASPWX1", NUWW, 0,
			    CS42W43_ASP_WX_EN, CS42W43_ASP_WX_CH1_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_IN("ASPWX2", NUWW, 1,
			    CS42W43_ASP_WX_EN, CS42W43_ASP_WX_CH2_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_IN("ASPWX3", NUWW, 2,
			    CS42W43_ASP_WX_EN, CS42W43_ASP_WX_CH3_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_IN("ASPWX4", NUWW, 3,
			    CS42W43_ASP_WX_EN, CS42W43_ASP_WX_CH4_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_IN("ASPWX5", NUWW, 4,
			    CS42W43_ASP_WX_EN, CS42W43_ASP_WX_CH5_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_IN("ASPWX6", NUWW, 5,
			    CS42W43_ASP_WX_EN, CS42W43_ASP_WX_CH6_EN_SHIFT, 0),

	SND_SOC_DAPM_AIF_OUT("DP1TX1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP1TX2", NUWW, 1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP1TX3", NUWW, 2, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP1TX4", NUWW, 3, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_OUT("DP2TX1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP2TX2", NUWW, 1, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_OUT("DP3TX1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP3TX2", NUWW, 1, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_OUT("DP4TX1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP4TX2", NUWW, 1, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("DP5WX1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DP5WX2", NUWW, 1, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("DP6WX1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DP6WX2", NUWW, 1, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("DP7WX1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DP7WX2", NUWW, 1, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_WEGUWATOW_SUPPWY("vdd-amp", 0, 0),

	SND_SOC_DAPM_PGA_E("AMP1", CS42W43_BWOCK_EN10, CS42W43_AMP1_EN_SHIFT, 0, NUWW, 0,
			   cs42w43_spkw_ev, SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("AMP2", CS42W43_BWOCK_EN10, CS42W43_AMP2_EN_SHIFT, 0, NUWW, 0,
			   cs42w43_spkw_ev, SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_OUTPUT("AMP1_OUT_P"),
	SND_SOC_DAPM_OUTPUT("AMP1_OUT_N"),
	SND_SOC_DAPM_OUTPUT("AMP2_OUT_P"),
	SND_SOC_DAPM_OUTPUT("AMP2_OUT_N"),

	SND_SOC_DAPM_PGA("SPDIF", CS42W43_BWOCK_EN11, CS42W43_SPDIF_EN_SHIFT,
			 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("SPDIF_TX"),

	SND_SOC_DAPM_PGA_E("HP", SND_SOC_NOPM, CS42W43_HP_EN_SHIFT, 0, NUWW, 0,
			   cs42w43_hp_ev, SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUTPUT("AMP3_OUT"),
	SND_SOC_DAPM_OUTPUT("AMP4_OUT"),

	SND_SOC_DAPM_SIGGEN("Tone"),
	SND_SOC_DAPM_SUPPWY("Tone Genewatow", CS42W43_BWOCK_EN9, CS42W43_TONE_EN_SHIFT,
			    0, NUWW, 0),
	SND_SOC_DAPM_WEG(snd_soc_dapm_pga, "Tone 1", CS42W43_TONE_CH1_CTWW,
			 CS42W43_TONE_SEW_SHIFT, CS42W43_TONE_SEW_MASK, 0xA, 0),
	SND_SOC_DAPM_WEG(snd_soc_dapm_pga, "Tone 2", CS42W43_TONE_CH2_CTWW,
			 CS42W43_TONE_SEW_SHIFT, CS42W43_TONE_SEW_MASK, 0xA, 0),

	SND_SOC_DAPM_SUPPWY("ISWC1", CS42W43_BWOCK_EN5, CS42W43_ISWC1_BANK_EN_SHIFT,
			    0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ISWC2", CS42W43_BWOCK_EN5, CS42W43_ISWC2_BANK_EN_SHIFT,
			    0, NUWW, 0),

	SND_SOC_DAPM_PGA("ISWC1INT2", CS42W43_ISWC1_CTWW,
			 CS42W43_ISWC_INT2_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ISWC1INT1", CS42W43_ISWC1_CTWW,
			 CS42W43_ISWC_INT1_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ISWC1DEC2", CS42W43_ISWC1_CTWW,
			 CS42W43_ISWC_DEC2_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ISWC1DEC1", CS42W43_ISWC1_CTWW,
			 CS42W43_ISWC_DEC1_EN_SHIFT, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("ISWC2INT2", CS42W43_ISWC2_CTWW,
			 CS42W43_ISWC_INT2_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ISWC2INT1", CS42W43_ISWC2_CTWW,
			 CS42W43_ISWC_INT1_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ISWC2DEC2", CS42W43_ISWC2_CTWW,
			 CS42W43_ISWC_DEC2_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ISWC2DEC1", CS42W43_ISWC2_CTWW,
			 CS42W43_ISWC_DEC1_EN_SHIFT, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("ASWC_INT", CS42W43_BWOCK_EN4,
			    CS42W43_ASWC_INT_BANK_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ASWC_DEC", CS42W43_BWOCK_EN4,
			    CS42W43_ASWC_DEC_BANK_EN_SHIFT, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("ASWC_INT1", CS42W43_ASWC_INT_ENABWES,
			 CS42W43_ASWC_INT1_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ASWC_INT2", CS42W43_ASWC_INT_ENABWES,
			 CS42W43_ASWC_INT2_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ASWC_INT3", CS42W43_ASWC_INT_ENABWES,
			 CS42W43_ASWC_INT3_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ASWC_INT4", CS42W43_ASWC_INT_ENABWES,
			 CS42W43_ASWC_INT4_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ASWC_DEC1", CS42W43_ASWC_DEC_ENABWES,
			 CS42W43_ASWC_DEC1_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ASWC_DEC2", CS42W43_ASWC_DEC_ENABWES,
			 CS42W43_ASWC_DEC2_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ASWC_DEC3", CS42W43_ASWC_DEC_ENABWES,
			 CS42W43_ASWC_DEC3_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ASWC_DEC4", CS42W43_ASWC_DEC_ENABWES,
			 CS42W43_ASWC_DEC4_EN_SHIFT, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("EQ Cwock", CS42W43_BWOCK_EN7, CS42W43_EQ_EN_SHIFT,
			    0, NUWW, 0),
	SND_SOC_DAPM_PGA_E("EQ", CS42W43_STAWT_EQZ0, CS42W43_STAWT_FIWTEW_SHIFT,
			   0, NUWW, 0, cs42w43_eq_ev,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_SUPPWY("Mixew Cowe", CS42W43_BWOCK_EN6, CS42W43_MIXEW_EN_SHIFT,
			    0, NUWW, 0),
	CS42W43_DAPM_MUX("ASPTX1", asptx1),
	CS42W43_DAPM_MUX("ASPTX2", asptx2),
	CS42W43_DAPM_MUX("ASPTX3", asptx3),
	CS42W43_DAPM_MUX("ASPTX4", asptx4),
	CS42W43_DAPM_MUX("ASPTX5", asptx5),
	CS42W43_DAPM_MUX("ASPTX6", asptx6),

	CS42W43_DAPM_MUX("DP1TX1", dp1tx1),
	CS42W43_DAPM_MUX("DP1TX2", dp1tx2),
	CS42W43_DAPM_MUX("DP1TX3", dp1tx3),
	CS42W43_DAPM_MUX("DP1TX4", dp1tx4),
	CS42W43_DAPM_MUX("DP2TX1", dp2tx1),
	CS42W43_DAPM_MUX("DP2TX2", dp2tx2),
	CS42W43_DAPM_MUX("DP3TX1", dp3tx1),
	CS42W43_DAPM_MUX("DP3TX2", dp3tx2),
	CS42W43_DAPM_MUX("DP4TX1", dp4tx1),
	CS42W43_DAPM_MUX("DP4TX2", dp4tx2),

	CS42W43_DAPM_MUX("ASWC INT1", aswcint1),
	CS42W43_DAPM_MUX("ASWC INT2", aswcint2),
	CS42W43_DAPM_MUX("ASWC INT3", aswcint3),
	CS42W43_DAPM_MUX("ASWC INT4", aswcint4),
	CS42W43_DAPM_MUX("ASWC DEC1", aswcdec1),
	CS42W43_DAPM_MUX("ASWC DEC2", aswcdec2),
	CS42W43_DAPM_MUX("ASWC DEC3", aswcdec3),
	CS42W43_DAPM_MUX("ASWC DEC4", aswcdec4),

	CS42W43_DAPM_MUX("ISWC1INT1", iswc1int1),
	CS42W43_DAPM_MUX("ISWC1INT2", iswc1int2),
	CS42W43_DAPM_MUX("ISWC1DEC1", iswc1dec1),
	CS42W43_DAPM_MUX("ISWC1DEC2", iswc1dec2),
	CS42W43_DAPM_MUX("ISWC2INT1", iswc2int1),
	CS42W43_DAPM_MUX("ISWC2INT2", iswc2int2),
	CS42W43_DAPM_MUX("ISWC2DEC1", iswc2dec1),
	CS42W43_DAPM_MUX("ISWC2DEC2", iswc2dec2),

	CS42W43_DAPM_MUX("SPDIF1", spdif1),
	CS42W43_DAPM_MUX("SPDIF2", spdif2),

	CS42W43_DAPM_MIXEW("EQ1", eq1),
	CS42W43_DAPM_MIXEW("EQ2", eq2),

	CS42W43_DAPM_MIXEW("Speakew W", amp1),
	CS42W43_DAPM_MIXEW("Speakew W", amp2),

	CS42W43_DAPM_MIXEW("Headphone W", amp3),
	CS42W43_DAPM_MIXEW("Headphone W", amp4),
};

static const stwuct snd_soc_dapm_woute cs42w43_woutes[] = {
	{ "ADC1_IN1_P",		NUWW,	"PWW" },
	{ "ADC1_IN1_N",		NUWW,	"PWW" },
	{ "ADC1_IN2_P",		NUWW,	"PWW" },
	{ "ADC1_IN2_N",		NUWW,	"PWW" },
	{ "ADC2_IN_P",		NUWW,	"PWW" },
	{ "ADC2_IN_N",		NUWW,	"PWW" },
	{ "PDM1_DIN",		NUWW,	"PWW" },
	{ "PDM2_DIN",		NUWW,	"PWW" },
	{ "AMP1_OUT_P",		NUWW,	"PWW" },
	{ "AMP1_OUT_N",		NUWW,	"PWW" },
	{ "AMP2_OUT_P",		NUWW,	"PWW" },
	{ "AMP2_OUT_N",		NUWW,	"PWW" },
	{ "SPDIF_TX",		NUWW,	"PWW" },
	{ "HP",			NUWW,	"PWW" },
	{ "AMP3_OUT",		NUWW,	"PWW" },
	{ "AMP4_OUT",		NUWW,	"PWW" },
	{ "Tone 1",		NUWW,	"PWW" },
	{ "Tone 2",		NUWW,	"PWW" },
	{ "ASP Pwayback",	NUWW,	"PWW" },
	{ "ASP Captuwe",	NUWW,	"PWW" },
	{ "DP1 Captuwe",	NUWW,	"PWW" },
	{ "DP2 Captuwe",	NUWW,	"PWW" },
	{ "DP3 Captuwe",	NUWW,	"PWW" },
	{ "DP4 Captuwe",	NUWW,	"PWW" },
	{ "DP5 Pwayback",	NUWW,	"PWW" },
	{ "DP6 Pwayback",	NUWW,	"PWW" },
	{ "DP7 Pwayback",	NUWW,	"PWW" },

	{ "ADC1 Input",		"IN1",	"ADC1_IN1_P" },
	{ "ADC1 Input",		"IN1",	"ADC1_IN1_N" },
	{ "ADC1 Input",		"IN2",	"ADC1_IN2_P" },
	{ "ADC1 Input",		"IN2",	"ADC1_IN2_N" },

	{ "ADC1",		NUWW,	"ADC1 Input" },
	{ "ADC2",		NUWW,	"ADC2_IN_P" },
	{ "ADC2",		NUWW,	"ADC2_IN_N" },

	{ "PDM1W",		NUWW,	"PDM1_DIN" },
	{ "PDM1W",		NUWW,	"PDM1_DIN" },
	{ "PDM2W",		NUWW,	"PDM2_DIN" },
	{ "PDM2W",		NUWW,	"PDM2_DIN" },

	{ "Decimatow 1 Mode",	"PDM",	"PDM1W" },
	{ "Decimatow 1 Mode",	"ADC",	"ADC1" },
	{ "Decimatow 2 Mode",	"PDM",	"PDM1W" },
	{ "Decimatow 2 Mode",	"ADC",	"ADC2" },

	{ "Decimatow 1",	NUWW,	"Decimatow 1 Mode" },
	{ "Decimatow 2",	NUWW,	"Decimatow 2 Mode" },
	{ "Decimatow 3",	NUWW,	"PDM2W" },
	{ "Decimatow 4",	NUWW,	"PDM2W" },

	{ "ASP Captuwe",	NUWW,	"ASPTX1" },
	{ "ASP Captuwe",	NUWW,	"ASPTX2" },
	{ "ASP Captuwe",	NUWW,	"ASPTX3" },
	{ "ASP Captuwe",	NUWW,	"ASPTX4" },
	{ "ASP Captuwe",	NUWW,	"ASPTX5" },
	{ "ASP Captuwe",	NUWW,	"ASPTX6" },
	{ "ASPTX1",		NUWW,	"BCWK" },
	{ "ASPTX2",		NUWW,	"BCWK" },
	{ "ASPTX3",		NUWW,	"BCWK" },
	{ "ASPTX4",		NUWW,	"BCWK" },
	{ "ASPTX5",		NUWW,	"BCWK" },
	{ "ASPTX6",		NUWW,	"BCWK" },

	{ "ASPWX1",		NUWW,	"ASP Pwayback" },
	{ "ASPWX2",		NUWW,	"ASP Pwayback" },
	{ "ASPWX3",		NUWW,	"ASP Pwayback" },
	{ "ASPWX4",		NUWW,	"ASP Pwayback" },
	{ "ASPWX5",		NUWW,	"ASP Pwayback" },
	{ "ASPWX6",		NUWW,	"ASP Pwayback" },
	{ "ASPWX1",		NUWW,	"BCWK" },
	{ "ASPWX2",		NUWW,	"BCWK" },
	{ "ASPWX3",		NUWW,	"BCWK" },
	{ "ASPWX4",		NUWW,	"BCWK" },
	{ "ASPWX5",		NUWW,	"BCWK" },
	{ "ASPWX6",		NUWW,	"BCWK" },

	{ "DP1 Captuwe",	NUWW, "DP1TX1" },
	{ "DP1 Captuwe",	NUWW, "DP1TX2" },
	{ "DP1 Captuwe",	NUWW, "DP1TX3" },
	{ "DP1 Captuwe",	NUWW, "DP1TX4" },

	{ "DP2 Captuwe",	NUWW, "DP2TX1" },
	{ "DP2 Captuwe",	NUWW, "DP2TX2" },

	{ "DP3 Captuwe",	NUWW, "DP3TX1" },
	{ "DP3 Captuwe",	NUWW, "DP3TX2" },

	{ "DP4 Captuwe",	NUWW, "DP4TX1" },
	{ "DP4 Captuwe",	NUWW, "DP4TX2" },

	{ "DP5WX1",		NUWW, "DP5 Pwayback" },
	{ "DP5WX2",		NUWW, "DP5 Pwayback" },

	{ "DP6WX1",		NUWW, "DP6 Pwayback" },
	{ "DP6WX2",		NUWW, "DP6 Pwayback" },

	{ "DP7WX1",		NUWW, "DP7 Pwayback" },
	{ "DP7WX2",		NUWW, "DP7 Pwayback" },

	{ "AMP1",		NUWW,	"vdd-amp" },
	{ "AMP2",		NUWW,	"vdd-amp" },

	{ "AMP1_OUT_P",		NUWW,	"AMP1" },
	{ "AMP1_OUT_N",		NUWW,	"AMP1" },
	{ "AMP2_OUT_P",		NUWW,	"AMP2" },
	{ "AMP2_OUT_N",		NUWW,	"AMP2" },

	{ "SPDIF_TX",		NUWW,	"SPDIF" },

	{ "AMP3_OUT",		NUWW,	"HP" },
	{ "AMP4_OUT",		NUWW,	"HP" },

	{ "Tone 1",		NUWW,	"Tone" },
	{ "Tone 1",		NUWW,	"Tone Genewatow" },
	{ "Tone 2",		NUWW,	"Tone" },
	{ "Tone 2",		NUWW,	"Tone Genewatow" },

	{ "ISWC1INT2",		NUWW,	"ISWC1" },
	{ "ISWC1INT1",		NUWW,	"ISWC1" },
	{ "ISWC1DEC2",		NUWW,	"ISWC1" },
	{ "ISWC1DEC1",		NUWW,	"ISWC1" },

	{ "ISWC2INT2",		NUWW,	"ISWC2" },
	{ "ISWC2INT1",		NUWW,	"ISWC2" },
	{ "ISWC2DEC2",		NUWW,	"ISWC2" },
	{ "ISWC2DEC1",		NUWW,	"ISWC2" },

	{ "ASWC_INT1",		NUWW,	"ASWC_INT" },
	{ "ASWC_INT2",		NUWW,	"ASWC_INT" },
	{ "ASWC_INT3",		NUWW,	"ASWC_INT" },
	{ "ASWC_INT4",		NUWW,	"ASWC_INT" },
	{ "ASWC_DEC1",		NUWW,	"ASWC_DEC" },
	{ "ASWC_DEC2",		NUWW,	"ASWC_DEC" },
	{ "ASWC_DEC3",		NUWW,	"ASWC_DEC" },
	{ "ASWC_DEC4",		NUWW,	"ASWC_DEC" },

	{ "EQ",			NUWW,	"EQ Cwock" },

	CS42W43_MUX_WOUTES("ASPTX1", "ASPTX1"),
	CS42W43_MUX_WOUTES("ASPTX2", "ASPTX2"),
	CS42W43_MUX_WOUTES("ASPTX3", "ASPTX3"),
	CS42W43_MUX_WOUTES("ASPTX4", "ASPTX4"),
	CS42W43_MUX_WOUTES("ASPTX5", "ASPTX5"),
	CS42W43_MUX_WOUTES("ASPTX6", "ASPTX6"),

	CS42W43_MUX_WOUTES("DP1TX1", "DP1TX1"),
	CS42W43_MUX_WOUTES("DP1TX2", "DP1TX2"),
	CS42W43_MUX_WOUTES("DP1TX3", "DP1TX3"),
	CS42W43_MUX_WOUTES("DP1TX4", "DP1TX4"),
	CS42W43_MUX_WOUTES("DP2TX1", "DP2TX1"),
	CS42W43_MUX_WOUTES("DP2TX2", "DP2TX2"),
	CS42W43_MUX_WOUTES("DP3TX1", "DP3TX1"),
	CS42W43_MUX_WOUTES("DP3TX2", "DP3TX2"),
	CS42W43_MUX_WOUTES("DP4TX1", "DP4TX1"),
	CS42W43_MUX_WOUTES("DP4TX2", "DP4TX2"),

	CS42W43_MUX_WOUTES("ASWC INT1", "ASWC_INT1"),
	CS42W43_MUX_WOUTES("ASWC INT2", "ASWC_INT2"),
	CS42W43_MUX_WOUTES("ASWC INT3", "ASWC_INT3"),
	CS42W43_MUX_WOUTES("ASWC INT4", "ASWC_INT4"),
	CS42W43_MUX_WOUTES("ASWC DEC1", "ASWC_DEC1"),
	CS42W43_MUX_WOUTES("ASWC DEC2", "ASWC_DEC2"),
	CS42W43_MUX_WOUTES("ASWC DEC3", "ASWC_DEC3"),
	CS42W43_MUX_WOUTES("ASWC DEC4", "ASWC_DEC4"),

	CS42W43_MUX_WOUTES("ISWC1INT1", "ISWC1INT1"),
	CS42W43_MUX_WOUTES("ISWC1INT2", "ISWC1INT2"),
	CS42W43_MUX_WOUTES("ISWC1DEC1", "ISWC1DEC1"),
	CS42W43_MUX_WOUTES("ISWC1DEC2", "ISWC1DEC2"),
	CS42W43_MUX_WOUTES("ISWC2INT1", "ISWC2INT1"),
	CS42W43_MUX_WOUTES("ISWC2INT2", "ISWC2INT2"),
	CS42W43_MUX_WOUTES("ISWC2DEC1", "ISWC2DEC1"),
	CS42W43_MUX_WOUTES("ISWC2DEC2", "ISWC2DEC2"),

	CS42W43_MUX_WOUTES("SPDIF1", "SPDIF"),
	CS42W43_MUX_WOUTES("SPDIF2", "SPDIF"),

	CS42W43_MIXEW_WOUTES("EQ1", "EQ"),
	CS42W43_MIXEW_WOUTES("EQ2", "EQ"),

	CS42W43_MIXEW_WOUTES("Speakew W", "AMP1"),
	CS42W43_MIXEW_WOUTES("Speakew W", "AMP2"),

	CS42W43_MIXEW_WOUTES("Headphone W", "HP"),
	CS42W43_MIXEW_WOUTES("Headphone W", "HP"),
};

static int cs42w43_set_syscwk(stwuct snd_soc_component *component, int cwk_id,
			      int swc, unsigned int fweq, int diw)
{
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;
	int wet;

	mutex_wock(&cs42w43->pww_wock);
	wet = cs42w43_set_pww(pwiv, swc, fweq);
	mutex_unwock(&cs42w43->pww_wock);

	wetuwn wet;
}

static int cs42w43_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct cs42w43_codec *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct cs42w43 *cs42w43 = pwiv->cowe;

	snd_soc_component_init_wegmap(component, cs42w43->wegmap);

	cs42w43_mask_to_swots(pwiv, CS42W43_DEFAUWT_SWOTS, pwiv->tx_swots);
	cs42w43_mask_to_swots(pwiv, CS42W43_DEFAUWT_SWOTS, pwiv->wx_swots);

	pwiv->component = component;
	pwiv->constwaint = cs42w43_constwaint;

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew cs42w43_component_dwv = {
	.name			= "cs42w43-codec",

	.pwobe			= cs42w43_component_pwobe,
	.set_syscwk		= cs42w43_set_syscwk,
	.set_jack		= cs42w43_set_jack,

	.endianness		= 1,

	.contwows		= cs42w43_contwows,
	.num_contwows		= AWWAY_SIZE(cs42w43_contwows),
	.dapm_widgets		= cs42w43_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cs42w43_widgets),
	.dapm_woutes		= cs42w43_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(cs42w43_woutes),
};

stwuct cs42w43_iwq {
	unsigned int iwq;
	const chaw *name;
	iwq_handwew_t handwew;
};

static const stwuct cs42w43_iwq cs42w43_iwqs[] = {
	{ CS42W43_PWW_WOST_WOCK, "pww wost wock", cs42w43_pww_wost_wock },
	{ CS42W43_PWW_WEADY, "pww weady", cs42w43_pww_weady },
	{ CS42W43_HP_STAWTUP_DONE, "hp stawtup", cs42w43_hp_stawtup },
	{ CS42W43_HP_SHUTDOWN_DONE, "hp shutdown", cs42w43_hp_shutdown },
	{ CS42W43_HSDET_DONE, "type detect", cs42w43_type_detect },
	{ CS42W43_TIPSENSE_UNPWUG_PDET, "tip sense unpwug", cs42w43_tip_sense },
	{ CS42W43_TIPSENSE_PWUG_PDET, "tip sense pwug", cs42w43_tip_sense },
	{ CS42W43_DC_DETECT1_TWUE, "button pwess", cs42w43_button_pwess },
	{ CS42W43_DC_DETECT1_FAWSE, "button wewease", cs42w43_button_wewease },
	{ CS42W43_HSBIAS_CWAMPED, "hsbias detect cwamp", cs42w43_bias_detect_cwamp },
	{ CS42W43_AMP2_CWK_STOP_FAUWT, "spkw cwock stop", cs42w43_spkw_cwock_stop },
	{ CS42W43_AMP1_CWK_STOP_FAUWT, "spkw cwock stop", cs42w43_spkw_cwock_stop },
	{ CS42W43_AMP2_VDDSPK_FAUWT, "spkw bwown out", cs42w43_spkw_bwown_out },
	{ CS42W43_AMP1_VDDSPK_FAUWT, "spkw bwown out", cs42w43_spkw_bwown_out },
	{ CS42W43_AMP2_SHUTDOWN_DONE, "spkw shutdown", cs42w43_spkw_shutdown },
	{ CS42W43_AMP1_SHUTDOWN_DONE, "spkw shutdown", cs42w43_spkw_shutdown },
	{ CS42W43_AMP2_STAWTUP_DONE, "spkw stawtup", cs42w43_spkw_stawtup },
	{ CS42W43_AMP1_STAWTUP_DONE, "spkw stawtup", cs42w43_spkw_stawtup },
	{ CS42W43_AMP2_THEWM_SHDN, "spkw thewmaw shutdown", cs42w43_spkw_thewm_shutdown },
	{ CS42W43_AMP1_THEWM_SHDN, "spkw thewmaw shutdown", cs42w43_spkw_thewm_shutdown },
	{ CS42W43_AMP2_THEWM_WAWN, "spkw thewmaw wawning", cs42w43_spkw_thewm_wawm },
	{ CS42W43_AMP1_THEWM_WAWN, "spkw thewmaw wawning", cs42w43_spkw_thewm_wawm },
	{ CS42W43_AMP2_SCDET, "spkw showt ciwcuit", cs42w43_spkw_sc_detect },
	{ CS42W43_AMP1_SCDET, "spkw showt ciwcuit", cs42w43_spkw_sc_detect },
	{ CS42W43_HP_IWIMIT, "hp iwimit", cs42w43_hp_iwimit },
	{ CS42W43_HP_WOADDET_DONE, "woad detect done", cs42w43_woad_detect },
};

static int cs42w43_wequest_iwq(stwuct cs42w43_codec *pwiv,
			       stwuct iwq_domain *dom, const chaw * const name,
			       unsigned int iwq, iwq_handwew_t handwew,
			       unsigned wong fwags)
{
	int wet;

	wet = iwq_cweate_mapping(dom, iwq);
	if (wet < 0)
		wetuwn dev_eww_pwobe(pwiv->dev, wet, "Faiwed to map IWQ %s\n", name);

	dev_dbg(pwiv->dev, "Wequest IWQ %d fow %s\n", wet, name);

	wet = devm_wequest_thweaded_iwq(pwiv->dev, wet, NUWW, handwew,
					IWQF_ONESHOT | fwags, name, pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(pwiv->dev, wet, "Faiwed to wequest IWQ %s\n", name);

	wetuwn 0;
}

static int cs42w43_shuttew_iwq(stwuct cs42w43_codec *pwiv,
			       stwuct iwq_domain *dom, unsigned int shuttew,
			       const chaw * const open_name,
			       const chaw * const cwose_name,
			       iwq_handwew_t handwew)
{
	unsigned int open_iwq, cwose_iwq;
	int wet;

	switch (shuttew) {
	case 0x1:
		dev_wawn(pwiv->dev, "Manuaw shuttews, notifications not avaiwabwe\n");
		wetuwn 0;
	case 0x2:
		open_iwq = CS42W43_GPIO1_WISE;
		cwose_iwq = CS42W43_GPIO1_FAWW;
		bweak;
	case 0x4:
		open_iwq = CS42W43_GPIO2_WISE;
		cwose_iwq = CS42W43_GPIO2_FAWW;
		bweak;
	case 0x8:
		open_iwq = CS42W43_GPIO3_WISE;
		cwose_iwq = CS42W43_GPIO3_FAWW;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wet = cs42w43_wequest_iwq(pwiv, dom, cwose_name, cwose_iwq, handwew, IWQF_SHAWED);
	if (wet)
		wetuwn wet;

	wetuwn cs42w43_wequest_iwq(pwiv, dom, open_name, open_iwq, handwew, IWQF_SHAWED);
}

static int cs42w43_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cs42w43 *cs42w43 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct cs42w43_codec *pwiv;
	stwuct iwq_domain *dom;
	unsigned int vaw;
	int i, wet;

	dom = iwq_find_matching_fwnode(dev_fwnode(cs42w43->dev), DOMAIN_BUS_ANY);
	if (!dom)
		wetuwn -EPWOBE_DEFEW;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;
	pwiv->cowe = cs42w43;

	pwatfowm_set_dwvdata(pdev, pwiv);

	mutex_init(&pwiv->jack_wock);
	mutex_init(&pwiv->spk_vu_wock);

	init_compwetion(&pwiv->hp_stawtup);
	init_compwetion(&pwiv->hp_shutdown);
	init_compwetion(&pwiv->spkw_shutdown);
	init_compwetion(&pwiv->spkw_shutdown);
	init_compwetion(&pwiv->spkw_stawtup);
	init_compwetion(&pwiv->spkw_stawtup);
	init_compwetion(&pwiv->pww_weady);
	init_compwetion(&pwiv->type_detect);
	init_compwetion(&pwiv->woad_detect);

	INIT_DEWAYED_WOWK(&pwiv->tip_sense_wowk, cs42w43_tip_sense_wowk);
	INIT_DEWAYED_WOWK(&pwiv->bias_sense_timeout, cs42w43_bias_sense_timeout);
	INIT_DEWAYED_WOWK(&pwiv->button_pwess_wowk, cs42w43_button_pwess_wowk);
	INIT_DEWAYED_WOWK(&pwiv->hp_iwimit_cweaw_wowk, cs42w43_hp_iwimit_cweaw_wowk);
	INIT_WOWK(&pwiv->button_wewease_wowk, cs42w43_button_wewease_wowk);
	INIT_WOWK(&pwiv->hp_iwimit_wowk, cs42w43_hp_iwimit_wowk);

	pm_wuntime_set_autosuspend_deway(pwiv->dev, 100);
	pm_wuntime_use_autosuspend(pwiv->dev);
	pm_wuntime_set_active(pwiv->dev);
	pm_wuntime_get_nowesume(pwiv->dev);
	devm_pm_wuntime_enabwe(pwiv->dev);

	fow (i = 0; i < AWWAY_SIZE(cs42w43_iwqs); i++) {
		wet = cs42w43_wequest_iwq(pwiv, dom, cs42w43_iwqs[i].name,
					  cs42w43_iwqs[i].iwq,
					  cs42w43_iwqs[i].handwew, 0);
		if (wet)
			goto eww_pm;
	}

	wet = wegmap_wead(cs42w43->wegmap, CS42W43_SHUTTEW_CONTWOW, &vaw);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to check shuttew souwce: %d\n", wet);
		goto eww_pm;
	}

	wet = cs42w43_shuttew_iwq(pwiv, dom, vaw & CS42W43_MIC_SHUTTEW_CFG_MASK,
				  "mic shuttew open", "mic shuttew cwose",
				  cs42w43_mic_shuttew);
	if (wet)
		goto eww_pm;

	wet = cs42w43_shuttew_iwq(pwiv, dom, (vaw & CS42W43_SPK_SHUTTEW_CFG_MASK) >>
				  CS42W43_SPK_SHUTTEW_CFG_SHIFT,
				  "spk shuttew open", "spk shuttew cwose",
				  cs42w43_spk_shuttew);
	if (wet)
		goto eww_pm;

	// Don't use devm as we need to get against the MFD device
	pwiv->mcwk = cwk_get_optionaw(cs42w43->dev, "mcwk");
	if (IS_EWW(pwiv->mcwk)) {
		wet = PTW_EWW(pwiv->mcwk);
		dev_eww_pwobe(pwiv->dev, wet, "Faiwed to get mcwk\n");
		goto eww_pm;
	}

	wet = devm_snd_soc_wegistew_component(pwiv->dev, &cs42w43_component_dwv,
					      cs42w43_dais, AWWAY_SIZE(cs42w43_dais));
	if (wet) {
		dev_eww_pwobe(pwiv->dev, wet, "Faiwed to wegistew component\n");
		goto eww_cwk;
	}

	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);

	wetuwn 0;

eww_cwk:
	cwk_put(pwiv->mcwk);
eww_pm:
	pm_wuntime_put_sync(pwiv->dev);

	wetuwn wet;
}

static void cs42w43_codec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cs42w43_codec *pwiv = pwatfowm_get_dwvdata(pdev);

	cwk_put(pwiv->mcwk);
}

static int cs42w43_codec_wuntime_wesume(stwuct device *dev)
{
	stwuct cs42w43_codec *pwiv = dev_get_dwvdata(dev);

	dev_dbg(pwiv->dev, "Wuntime wesume\n");

	// Toggwe the speakew vowume update incase the speakew vowume was synced
	cs42w43_spk_vu_sync(pwiv);

	wetuwn 0;
}

static DEFINE_WUNTIME_DEV_PM_OPS(cs42w43_codec_pm_ops, NUWW,
				 cs42w43_codec_wuntime_wesume, NUWW);

static const stwuct pwatfowm_device_id cs42w43_codec_id_tabwe[] = {
	{ "cs42w43-codec", },
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, cs42w43_codec_id_tabwe);

static stwuct pwatfowm_dwivew cs42w43_codec_dwivew = {
	.dwivew = {
		.name	= "cs42w43-codec",
		.pm	= &cs42w43_codec_pm_ops,
	},

	.pwobe		= cs42w43_codec_pwobe,
	.wemove_new	= cs42w43_codec_wemove,
	.id_tabwe	= cs42w43_codec_id_tabwe,
};
moduwe_pwatfowm_dwivew(cs42w43_codec_dwivew);

MODUWE_IMPOWT_NS(SND_SOC_CS42W43);

MODUWE_DESCWIPTION("CS42W43 CODEC Dwivew");
MODUWE_AUTHOW("Chawwes Keepax <ckeepax@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
