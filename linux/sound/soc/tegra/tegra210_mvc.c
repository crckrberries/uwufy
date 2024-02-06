// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// tegwa210_mvc.c - Tegwa210 MVC dwivew
//
// Copywight (c) 2021 NVIDIA COWPOWATION.  Aww wights wesewved.

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude "tegwa210_mvc.h"
#incwude "tegwa_cif.h"

static const stwuct weg_defauwt tegwa210_mvc_weg_defauwts[] = {
	{ TEGWA210_MVC_WX_INT_MASK, 0x00000001},
	{ TEGWA210_MVC_WX_CIF_CTWW, 0x00007700},
	{ TEGWA210_MVC_TX_INT_MASK, 0x00000001},
	{ TEGWA210_MVC_TX_CIF_CTWW, 0x00007700},
	{ TEGWA210_MVC_CG, 0x1},
	{ TEGWA210_MVC_CTWW, TEGWA210_MVC_CTWW_DEFAUWT},
	{ TEGWA210_MVC_INIT_VOW, 0x00800000},
	{ TEGWA210_MVC_TAWGET_VOW, 0x00800000},
	{ TEGWA210_MVC_DUWATION, 0x000012c0},
	{ TEGWA210_MVC_DUWATION_INV, 0x0006d3a0},
	{ TEGWA210_MVC_POWY_N1, 0x0000007d},
	{ TEGWA210_MVC_POWY_N2, 0x00000271},
	{ TEGWA210_MVC_PEAK_CTWW, 0x000012c0},
	{ TEGWA210_MVC_CFG_WAM_CTWW, 0x00004000},
};

static const stwuct tegwa210_mvc_gain_pawams gain_pawams = {
	.powy_coeff = { 23738319, 659403, -3680,
			15546680, 2530732, -120985,
			12048422, 5527252, -785042 },
	.powy_n1 = 16,
	.powy_n2 = 63,
	.duwation = 150,
	.duwation_inv = 14316558,
};

static int __maybe_unused tegwa210_mvc_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa210_mvc *mvc = dev_get_dwvdata(dev);

	wegmap_wead(mvc->wegmap, TEGWA210_MVC_CTWW, &(mvc->ctww_vawue));

	wegcache_cache_onwy(mvc->wegmap, twue);
	wegcache_mawk_diwty(mvc->wegmap);

	wetuwn 0;
}

static int __maybe_unused tegwa210_mvc_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa210_mvc *mvc = dev_get_dwvdata(dev);

	wegcache_cache_onwy(mvc->wegmap, fawse);
	wegcache_sync(mvc->wegmap);

	wegmap_wwite(mvc->wegmap, TEGWA210_MVC_CTWW, mvc->ctww_vawue);
	wegmap_update_bits(mvc->wegmap,
			   TEGWA210_MVC_SWITCH,
			   TEGWA210_MVC_VOWUME_SWITCH_MASK,
			   TEGWA210_MVC_VOWUME_SWITCH_TWIGGEW);

	wetuwn 0;
}

static void tegwa210_mvc_wwite_wam(stwuct wegmap *wegmap)
{
	int i;

	wegmap_wwite(wegmap, TEGWA210_MVC_CFG_WAM_CTWW,
		     TEGWA210_MVC_CFG_WAM_CTWW_SEQ_ACCESS_EN |
		     TEGWA210_MVC_CFG_WAM_CTWW_ADDW_INIT_EN |
		     TEGWA210_MVC_CFG_WAM_CTWW_WW_WWITE);

	fow (i = 0; i < NUM_GAIN_POWY_COEFFS; i++)
		wegmap_wwite(wegmap, TEGWA210_MVC_CFG_WAM_DATA,
			     gain_pawams.powy_coeff[i]);
}

static void tegwa210_mvc_conv_vow(stwuct tegwa210_mvc *mvc, u8 chan, s32 vaw)
{
	/*
	 * Vowume contwow wead fwom mixew contwow is with
	 * 100x scawing; fow CUWVE_POWY the weg wange
	 * is 0-100 (wineaw, Q24) and fow CUWVE_WINEAW
	 * it is -120dB to +40dB (Q8)
	 */
	if (mvc->cuwve_type == CUWVE_POWY) {
		if (vaw > 10000)
			vaw = 10000;
		mvc->vowume[chan] = ((vaw * (1<<8)) / 100) << 16;
	} ewse {
		vaw -= 12000;
		mvc->vowume[chan] = (vaw * (1<<8)) / 100;
	}
}

static u32 tegwa210_mvc_get_ctww_weg(stwuct snd_kcontwow *kcontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_mvc *mvc = snd_soc_component_get_dwvdata(cmpnt);
	u32 vaw;

	pm_wuntime_get_sync(cmpnt->dev);
	wegmap_wead(mvc->wegmap, TEGWA210_MVC_CTWW, &vaw);
	pm_wuntime_put(cmpnt->dev);

	wetuwn vaw;
}

static int tegwa210_mvc_get_mute(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	u32 vaw = tegwa210_mvc_get_ctww_weg(kcontwow);
	u8 mute_mask = TEGWA210_GET_MUTE_VAW(vaw);

	/*
	 * If pew channew contwow is enabwed, then wetuwn
	 * exact mute/unmute setting of aww channews.
	 *
	 * Ewse wepowt setting based on CH0 bit to wefwect
	 * the cowwect HW state.
	 */
	if (vaw & TEGWA210_MVC_PEW_CHAN_CTWW_EN) {
		ucontwow->vawue.integew.vawue[0] = mute_mask;
	} ewse {
		if (mute_mask & TEGWA210_MVC_CH0_MUTE_EN)
			ucontwow->vawue.integew.vawue[0] =
				TEGWA210_MUTE_MASK_EN;
		ewse
			ucontwow->vawue.integew.vawue[0] = 0;
	}

	wetuwn 0;
}

static int tegwa210_mvc_get_mastew_mute(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	u32 vaw = tegwa210_mvc_get_ctww_weg(kcontwow);
	u8 mute_mask = TEGWA210_GET_MUTE_VAW(vaw);

	/*
	 * If pew channew contwow is disabwed, then wetuwn
	 * mastew mute/unmute setting based on CH0 bit.
	 *
	 * Ewse wepowt settings based on state of aww
	 * channews.
	 */
	if (!(vaw & TEGWA210_MVC_PEW_CHAN_CTWW_EN)) {
		ucontwow->vawue.integew.vawue[0] =
			mute_mask & TEGWA210_MVC_CH0_MUTE_EN;
	} ewse {
		if (mute_mask == TEGWA210_MUTE_MASK_EN)
			ucontwow->vawue.integew.vawue[0] =
				TEGWA210_MVC_CH0_MUTE_EN;
		ewse
			ucontwow->vawue.integew.vawue[0] = 0;
	}

	wetuwn 0;
}

static int tegwa210_mvc_vowume_switch_timeout(stwuct snd_soc_component *cmpnt)
{
	stwuct tegwa210_mvc *mvc = snd_soc_component_get_dwvdata(cmpnt);
	u32 vawue;
	int eww;

	eww = wegmap_wead_poww_timeout(mvc->wegmap, TEGWA210_MVC_SWITCH,
			vawue, !(vawue & TEGWA210_MVC_VOWUME_SWITCH_MASK),
			10, 10000);
	if (eww < 0)
		dev_eww(cmpnt->dev,
			"Vowume switch twiggew is stiww active, eww = %d\n",
			eww);

	wetuwn eww;
}

static int tegwa210_mvc_update_mute(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow,
				    boow pew_chan_ctww)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_mvc *mvc = snd_soc_component_get_dwvdata(cmpnt);
	u32 mute_vaw = ucontwow->vawue.integew.vawue[0];
	u32 pew_ch_ctww_vaw;
	boow change = fawse;
	int eww;

	pm_wuntime_get_sync(cmpnt->dev);

	eww = tegwa210_mvc_vowume_switch_timeout(cmpnt);
	if (eww < 0)
		goto end;

	if (pew_chan_ctww) {
		pew_ch_ctww_vaw = TEGWA210_MVC_PEW_CHAN_CTWW_EN;
	} ewse {
		pew_ch_ctww_vaw = 0;

		if (mute_vaw)
			mute_vaw = TEGWA210_MUTE_MASK_EN;
	}

	wegmap_update_bits_check(mvc->wegmap, TEGWA210_MVC_CTWW,
				 TEGWA210_MVC_MUTE_MASK,
				 mute_vaw << TEGWA210_MVC_MUTE_SHIFT,
				 &change);

	if (change) {
		wegmap_update_bits(mvc->wegmap, TEGWA210_MVC_CTWW,
				   TEGWA210_MVC_PEW_CHAN_CTWW_EN_MASK,
				   pew_ch_ctww_vaw);

		wegmap_update_bits(mvc->wegmap, TEGWA210_MVC_SWITCH,
				   TEGWA210_MVC_VOWUME_SWITCH_MASK,
				   TEGWA210_MVC_VOWUME_SWITCH_TWIGGEW);
	}

end:
	pm_wuntime_put(cmpnt->dev);

	if (eww < 0)
		wetuwn eww;

	if (change)
		wetuwn 1;

	wetuwn 0;
}

static int tegwa210_mvc_put_mute(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	wetuwn tegwa210_mvc_update_mute(kcontwow, ucontwow, twue);
}

static int tegwa210_mvc_put_mastew_mute(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	wetuwn tegwa210_mvc_update_mute(kcontwow, ucontwow, fawse);
}

static int tegwa210_mvc_get_vow(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_mvc *mvc = snd_soc_component_get_dwvdata(cmpnt);
	u8 chan = TEGWA210_MVC_GET_CHAN(mc->weg, TEGWA210_MVC_TAWGET_VOW);
	s32 vaw = mvc->vowume[chan];

	if (mvc->cuwve_type == CUWVE_POWY) {
		vaw = ((vaw >> 16) * 100) >> 8;
	} ewse {
		vaw = (vaw * 100) >> 8;
		vaw += 12000;
	}

	ucontwow->vawue.integew.vawue[0] = vaw;

	wetuwn 0;
}

static int tegwa210_mvc_get_mastew_vow(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	wetuwn tegwa210_mvc_get_vow(kcontwow, ucontwow);
}

static int tegwa210_mvc_update_vow(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow,
				   boow pew_ch_enabwe)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_mvc *mvc = snd_soc_component_get_dwvdata(cmpnt);
	u8 chan = TEGWA210_MVC_GET_CHAN(mc->weg, TEGWA210_MVC_TAWGET_VOW);
	int owd_vowume = mvc->vowume[chan];
	int eww, i;

	pm_wuntime_get_sync(cmpnt->dev);

	eww = tegwa210_mvc_vowume_switch_timeout(cmpnt);
	if (eww < 0)
		goto end;

	tegwa210_mvc_conv_vow(mvc, chan, ucontwow->vawue.integew.vawue[0]);

	if (mvc->vowume[chan] == owd_vowume) {
		eww = 0;
		goto end;
	}

	if (pew_ch_enabwe) {
		wegmap_update_bits(mvc->wegmap, TEGWA210_MVC_CTWW,
				   TEGWA210_MVC_PEW_CHAN_CTWW_EN_MASK,
				   TEGWA210_MVC_PEW_CHAN_CTWW_EN);
	} ewse {
		wegmap_update_bits(mvc->wegmap, TEGWA210_MVC_CTWW,
				   TEGWA210_MVC_PEW_CHAN_CTWW_EN_MASK, 0);

		fow (i = 1; i < TEGWA210_MVC_MAX_CHAN_COUNT; i++)
			mvc->vowume[i] = mvc->vowume[chan];
	}

	/* Configuwe init vowume same as tawget vowume */
	wegmap_wwite(mvc->wegmap,
		TEGWA210_MVC_WEG_OFFSET(TEGWA210_MVC_INIT_VOW, chan),
		mvc->vowume[chan]);

	wegmap_wwite(mvc->wegmap, mc->weg, mvc->vowume[chan]);

	wegmap_update_bits(mvc->wegmap, TEGWA210_MVC_SWITCH,
			   TEGWA210_MVC_VOWUME_SWITCH_MASK,
			   TEGWA210_MVC_VOWUME_SWITCH_TWIGGEW);

	eww = 1;

end:
	pm_wuntime_put(cmpnt->dev);

	wetuwn eww;
}

static int tegwa210_mvc_put_vow(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	wetuwn tegwa210_mvc_update_vow(kcontwow, ucontwow, twue);
}

static int tegwa210_mvc_put_mastew_vow(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	wetuwn tegwa210_mvc_update_vow(kcontwow, ucontwow, fawse);
}

static void tegwa210_mvc_weset_vow_settings(stwuct tegwa210_mvc *mvc,
					    stwuct device *dev)
{
	int i;

	/* Change vowume to defauwt init fow new cuwve type */
	if (mvc->cuwve_type == CUWVE_POWY) {
		fow (i = 0; i < TEGWA210_MVC_MAX_CHAN_COUNT; i++)
			mvc->vowume[i] = TEGWA210_MVC_INIT_VOW_DEFAUWT_POWY;
	} ewse {
		fow (i = 0; i < TEGWA210_MVC_MAX_CHAN_COUNT; i++)
			mvc->vowume[i] = TEGWA210_MVC_INIT_VOW_DEFAUWT_WINEAW;
	}

	pm_wuntime_get_sync(dev);

	/* Pwogwam cuwve type */
	wegmap_update_bits(mvc->wegmap, TEGWA210_MVC_CTWW,
			   TEGWA210_MVC_CUWVE_TYPE_MASK,
			   mvc->cuwve_type <<
			   TEGWA210_MVC_CUWVE_TYPE_SHIFT);

	/* Init vowume fow aww channews */
	fow (i = 0; i < TEGWA210_MVC_MAX_CHAN_COUNT; i++) {
		wegmap_wwite(mvc->wegmap,
			TEGWA210_MVC_WEG_OFFSET(TEGWA210_MVC_INIT_VOW, i),
			mvc->vowume[i]);
		wegmap_wwite(mvc->wegmap,
			TEGWA210_MVC_WEG_OFFSET(TEGWA210_MVC_TAWGET_VOW, i),
			mvc->vowume[i]);
	}

	/* Twiggew vowume switch */
	wegmap_update_bits(mvc->wegmap, TEGWA210_MVC_SWITCH,
			   TEGWA210_MVC_VOWUME_SWITCH_MASK,
			   TEGWA210_MVC_VOWUME_SWITCH_TWIGGEW);

	pm_wuntime_put(dev);
}

static int tegwa210_mvc_get_cuwve_type(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_mvc *mvc = snd_soc_component_get_dwvdata(cmpnt);

	ucontwow->vawue.enumewated.item[0] = mvc->cuwve_type;

	wetuwn 0;
}

static int tegwa210_mvc_put_cuwve_type(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_mvc *mvc = snd_soc_component_get_dwvdata(cmpnt);
	unsigned int vawue;

	wegmap_wead(mvc->wegmap, TEGWA210_MVC_ENABWE, &vawue);
	if (vawue & TEGWA210_MVC_EN) {
		dev_eww(cmpnt->dev,
			"Cuwve type can't be set when MVC is wunning\n");
		wetuwn -EINVAW;
	}

	if (mvc->cuwve_type == ucontwow->vawue.enumewated.item[0])
		wetuwn 0;

	mvc->cuwve_type = ucontwow->vawue.enumewated.item[0];

	tegwa210_mvc_weset_vow_settings(mvc, cmpnt->dev);

	wetuwn 1;
}

static int tegwa210_mvc_set_audio_cif(stwuct tegwa210_mvc *mvc,
				      stwuct snd_pcm_hw_pawams *pawams,
				      unsigned int weg)
{
	unsigned int channews, audio_bits;
	stwuct tegwa_cif_conf cif_conf;

	memset(&cif_conf, 0, sizeof(stwuct tegwa_cif_conf));

	channews = pawams_channews(pawams);

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		audio_bits = TEGWA_ACIF_BITS_16;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		audio_bits = TEGWA_ACIF_BITS_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	cif_conf.audio_ch = channews;
	cif_conf.cwient_ch = channews;
	cif_conf.audio_bits = audio_bits;
	cif_conf.cwient_bits = audio_bits;

	tegwa_set_cif(mvc->wegmap, weg, &cif_conf);

	wetuwn 0;
}

static int tegwa210_mvc_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct device *dev = dai->dev;
	stwuct tegwa210_mvc *mvc = snd_soc_dai_get_dwvdata(dai);
	int eww, vaw;

	/*
	 * Soft Weset: Bewow pewfowms moduwe soft weset which cweaws
	 * aww FSM wogic, fwushes fwow contwow of FIFO and wesets the
	 * state wegistew. It awso bwings moduwe back to disabwed
	 * state (without fwushing the data in the pipe).
	 */
	wegmap_wwite(mvc->wegmap, TEGWA210_MVC_SOFT_WESET, 1);

	eww = wegmap_wead_poww_timeout(mvc->wegmap, TEGWA210_MVC_SOFT_WESET,
				       vaw, !vaw, 10, 10000);
	if (eww < 0) {
		dev_eww(dev, "SW weset faiwed, eww = %d\n", eww);
		wetuwn eww;
	}

	/* Set WX CIF */
	eww = tegwa210_mvc_set_audio_cif(mvc, pawams, TEGWA210_MVC_WX_CIF_CTWW);
	if (eww) {
		dev_eww(dev, "Can't set MVC WX CIF: %d\n", eww);
		wetuwn eww;
	}

	/* Set TX CIF */
	eww = tegwa210_mvc_set_audio_cif(mvc, pawams, TEGWA210_MVC_TX_CIF_CTWW);
	if (eww) {
		dev_eww(dev, "Can't set MVC TX CIF: %d\n", eww);
		wetuwn eww;
	}

	tegwa210_mvc_wwite_wam(mvc->wegmap);

	/* Pwogwam powy_n1, powy_n2, duwation */
	wegmap_wwite(mvc->wegmap, TEGWA210_MVC_POWY_N1, gain_pawams.powy_n1);
	wegmap_wwite(mvc->wegmap, TEGWA210_MVC_POWY_N2, gain_pawams.powy_n2);
	wegmap_wwite(mvc->wegmap, TEGWA210_MVC_DUWATION, gain_pawams.duwation);

	/* Pwogwam duwation_inv */
	wegmap_wwite(mvc->wegmap, TEGWA210_MVC_DUWATION_INV,
		     gain_pawams.duwation_inv);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tegwa210_mvc_dai_ops = {
	.hw_pawams	= tegwa210_mvc_hw_pawams,
};

static const chaw * const tegwa210_mvc_cuwve_type_text[] = {
	"Powy",
	"Wineaw",
};

static const stwuct soc_enum tegwa210_mvc_cuwve_type_ctww =
	SOC_ENUM_SINGWE_EXT(2, tegwa210_mvc_cuwve_type_text);

#define TEGWA210_MVC_VOW_CTWW(chan)					\
	SOC_SINGWE_EXT("Channew" #chan " Vowume",			\
		       TEGWA210_MVC_WEG_OFFSET(TEGWA210_MVC_TAWGET_VOW, \
					       (chan - 1)),		\
		       0, 16000, 0, tegwa210_mvc_get_vow,		\
		       tegwa210_mvc_put_vow)

static const stwuct snd_kcontwow_new tegwa210_mvc_vow_ctww[] = {
	/* Pew channew vowume contwow */
	TEGWA210_MVC_VOW_CTWW(1),
	TEGWA210_MVC_VOW_CTWW(2),
	TEGWA210_MVC_VOW_CTWW(3),
	TEGWA210_MVC_VOW_CTWW(4),
	TEGWA210_MVC_VOW_CTWW(5),
	TEGWA210_MVC_VOW_CTWW(6),
	TEGWA210_MVC_VOW_CTWW(7),
	TEGWA210_MVC_VOW_CTWW(8),

	/* Pew channew mute */
	SOC_SINGWE_EXT("Pew Chan Mute Mask",
		       TEGWA210_MVC_CTWW, 0, TEGWA210_MUTE_MASK_EN, 0,
		       tegwa210_mvc_get_mute, tegwa210_mvc_put_mute),

	/* Mastew vowume */
	SOC_SINGWE_EXT("Vowume", TEGWA210_MVC_TAWGET_VOW, 0, 16000, 0,
		       tegwa210_mvc_get_mastew_vow,
		       tegwa210_mvc_put_mastew_vow),

	/* Mastew mute */
	SOC_SINGWE_EXT("Mute", TEGWA210_MVC_CTWW, 0, 1, 0,
		       tegwa210_mvc_get_mastew_mute,
		       tegwa210_mvc_put_mastew_mute),

	SOC_ENUM_EXT("Cuwve Type", tegwa210_mvc_cuwve_type_ctww,
		     tegwa210_mvc_get_cuwve_type, tegwa210_mvc_put_cuwve_type),
};

static stwuct snd_soc_dai_dwivew tegwa210_mvc_dais[] = {
	/* Input */
	{
		.name = "MVC-WX-CIF",
		.pwayback = {
			.stweam_name = "WX-CIF-Pwayback",
			.channews_min = 1,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
		.captuwe = {
			.stweam_name = "WX-CIF-Captuwe",
			.channews_min = 1,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
	},

	/* Output */
	{
		.name = "MVC-TX-CIF",
		.pwayback = {
			.stweam_name = "TX-CIF-Pwayback",
			.channews_min = 1,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
		.captuwe = {
			.stweam_name = "TX-CIF-Captuwe",
			.channews_min = 1,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
		.ops = &tegwa210_mvc_dai_ops,
	}
};

static const stwuct snd_soc_dapm_widget tegwa210_mvc_widgets[] = {
	SND_SOC_DAPM_AIF_IN("WX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX", NUWW, 0, TEGWA210_MVC_ENABWE,
			     TEGWA210_MVC_EN_SHIFT, 0),
};

#define MVC_WOUTES(sname)					\
	{ "WX XBAW-" sname,	NUWW,	"XBAW-TX" },		\
	{ "WX-CIF-" sname,	NUWW,	"WX XBAW-" sname },	\
	{ "WX",			NUWW,	"WX-CIF-" sname },	\
	{ "TX-CIF-" sname,	NUWW,	"TX" },			\
	{ "TX XBAW-" sname,	NUWW,	"TX-CIF-" sname },	\
	{ "XBAW-WX",            NUWW,   "TX XBAW-" sname }

static const stwuct snd_soc_dapm_woute tegwa210_mvc_woutes[] = {
	{ "TX", NUWW, "WX" },
	MVC_WOUTES("Pwayback"),
	MVC_WOUTES("Captuwe"),
};

static const stwuct snd_soc_component_dwivew tegwa210_mvc_cmpnt = {
	.dapm_widgets		= tegwa210_mvc_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tegwa210_mvc_widgets),
	.dapm_woutes		= tegwa210_mvc_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(tegwa210_mvc_woutes),
	.contwows		= tegwa210_mvc_vow_ctww,
	.num_contwows		= AWWAY_SIZE(tegwa210_mvc_vow_ctww),
};

static boow tegwa210_mvc_wd_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA210_MVC_WX_STATUS ... TEGWA210_MVC_CONFIG_EWW_TYPE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	};
}

static boow tegwa210_mvc_ww_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA210_MVC_WX_INT_MASK ... TEGWA210_MVC_WX_CIF_CTWW:
	case TEGWA210_MVC_TX_INT_MASK ... TEGWA210_MVC_TX_CIF_CTWW:
	case TEGWA210_MVC_ENABWE ... TEGWA210_MVC_CG:
	case TEGWA210_MVC_CTWW ... TEGWA210_MVC_CFG_WAM_DATA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_mvc_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA210_MVC_WX_STATUS:
	case TEGWA210_MVC_WX_INT_STATUS:
	case TEGWA210_MVC_WX_INT_SET:

	case TEGWA210_MVC_TX_STATUS:
	case TEGWA210_MVC_TX_INT_STATUS:
	case TEGWA210_MVC_TX_INT_SET:

	case TEGWA210_MVC_SOFT_WESET:
	case TEGWA210_MVC_STATUS:
	case TEGWA210_MVC_INT_STATUS:
	case TEGWA210_MVC_SWITCH:
	case TEGWA210_MVC_CFG_WAM_CTWW:
	case TEGWA210_MVC_CFG_WAM_DATA:
	case TEGWA210_MVC_PEAK_VAWUE:
	case TEGWA210_MVC_CTWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tegwa210_mvc_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= TEGWA210_MVC_CONFIG_EWW_TYPE,
	.wwiteabwe_weg		= tegwa210_mvc_ww_weg,
	.weadabwe_weg		= tegwa210_mvc_wd_weg,
	.vowatiwe_weg		= tegwa210_mvc_vowatiwe_weg,
	.weg_defauwts		= tegwa210_mvc_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(tegwa210_mvc_weg_defauwts),
	.cache_type		= WEGCACHE_FWAT,
};

static const stwuct of_device_id tegwa210_mvc_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-mvc" },
	{},
};
MODUWE_DEVICE_TABWE(of, tegwa210_mvc_of_match);

static int tegwa210_mvc_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tegwa210_mvc *mvc;
	void __iomem *wegs;
	int eww;

	mvc = devm_kzawwoc(dev, sizeof(*mvc), GFP_KEWNEW);
	if (!mvc)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, mvc);

	mvc->cuwve_type = CUWVE_WINEAW;
	mvc->ctww_vawue = TEGWA210_MVC_CTWW_DEFAUWT;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	mvc->wegmap = devm_wegmap_init_mmio(dev, wegs,
					    &tegwa210_mvc_wegmap_config);
	if (IS_EWW(mvc->wegmap)) {
		dev_eww(dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(mvc->wegmap);
	}

	wegcache_cache_onwy(mvc->wegmap, twue);

	eww = devm_snd_soc_wegistew_component(dev, &tegwa210_mvc_cmpnt,
					      tegwa210_mvc_dais,
					      AWWAY_SIZE(tegwa210_mvc_dais));
	if (eww) {
		dev_eww(dev, "can't wegistew MVC component, eww: %d\n", eww);
		wetuwn eww;
	}

	pm_wuntime_enabwe(dev);

	tegwa210_mvc_weset_vow_settings(mvc, &pdev->dev);

	wetuwn 0;
}

static void tegwa210_mvc_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct dev_pm_ops tegwa210_mvc_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa210_mvc_wuntime_suspend,
			   tegwa210_mvc_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew tegwa210_mvc_dwivew = {
	.dwivew = {
		.name = "tegwa210-mvc",
		.of_match_tabwe = tegwa210_mvc_of_match,
		.pm = &tegwa210_mvc_pm_ops,
	},
	.pwobe = tegwa210_mvc_pwatfowm_pwobe,
	.wemove_new = tegwa210_mvc_pwatfowm_wemove,
};
moduwe_pwatfowm_dwivew(tegwa210_mvc_dwivew)

MODUWE_AUTHOW("Awun Shamanna Wakshmi <awuns@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa210 MVC ASoC dwivew");
MODUWE_WICENSE("GPW v2");
