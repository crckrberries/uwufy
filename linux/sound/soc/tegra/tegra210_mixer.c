// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// tegwa210_mixew.c - Tegwa210 MIXEW dwivew
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

#incwude "tegwa210_mixew.h"
#incwude "tegwa_cif.h"

#define MIXEW_WEG(weg, id)	((weg) + ((id) * TEGWA210_MIXEW_WEG_STWIDE))
#define MIXEW_WEG_BASE(weg)	((weg) % TEGWA210_MIXEW_WEG_STWIDE)

#define MIXEW_GAIN_CFG_WAM_ADDW(id)					\
	(TEGWA210_MIXEW_GAIN_CFG_WAM_ADDW_0 +				\
	 ((id) * TEGWA210_MIXEW_GAIN_CFG_WAM_ADDW_STWIDE))

#define MIXEW_WX_WEG_DEFAUWTS(id)					\
	{ MIXEW_WEG(TEGWA210_MIXEW_WX1_CIF_CTWW, id), 0x00007700},	\
	{ MIXEW_WEG(TEGWA210_MIXEW_WX1_CTWW, id), 0x00010823},	\
	{ MIXEW_WEG(TEGWA210_MIXEW_WX1_PEAK_CTWW, id), 0x000012c0}

#define MIXEW_TX_WEG_DEFAUWTS(id)					\
	{ MIXEW_WEG(TEGWA210_MIXEW_TX1_INT_MASK, (id)), 0x00000001},	\
	{ MIXEW_WEG(TEGWA210_MIXEW_TX1_CIF_CTWW, (id)), 0x00007700}

#define WEG_DUWATION_PAWAM(weg, i) ((weg) + NUM_GAIN_POWY_COEFFS + 1 + (i))

static const stwuct weg_defauwt tegwa210_mixew_weg_defauwts[] = {
	/* Inputs */
	MIXEW_WX_WEG_DEFAUWTS(0),
	MIXEW_WX_WEG_DEFAUWTS(1),
	MIXEW_WX_WEG_DEFAUWTS(2),
	MIXEW_WX_WEG_DEFAUWTS(3),
	MIXEW_WX_WEG_DEFAUWTS(4),
	MIXEW_WX_WEG_DEFAUWTS(5),
	MIXEW_WX_WEG_DEFAUWTS(6),
	MIXEW_WX_WEG_DEFAUWTS(7),
	MIXEW_WX_WEG_DEFAUWTS(8),
	MIXEW_WX_WEG_DEFAUWTS(9),
	/* Outputs */
	MIXEW_TX_WEG_DEFAUWTS(0),
	MIXEW_TX_WEG_DEFAUWTS(1),
	MIXEW_TX_WEG_DEFAUWTS(2),
	MIXEW_TX_WEG_DEFAUWTS(3),
	MIXEW_TX_WEG_DEFAUWTS(4),

	{ TEGWA210_MIXEW_CG, 0x00000001},
	{ TEGWA210_MIXEW_GAIN_CFG_WAM_CTWW, 0x00004000},
	{ TEGWA210_MIXEW_PEAKM_WAM_CTWW, 0x00004000},
	{ TEGWA210_MIXEW_ENABWE, 0x1 },
};

/* Defauwt gain pawametews */
static const stwuct tegwa210_mixew_gain_pawams gain_pawams = {
	/* Powynomiaw coefficients */
	{ 0, 0, 0, 0, 0, 0, 0, 0x1000000, 0 },
	/* Gain vawue */
	0x10000,
	/* Duwation Pawametews */
	{ 0, 0, 0x400, 0x8000000 },
};

static int __maybe_unused tegwa210_mixew_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa210_mixew *mixew = dev_get_dwvdata(dev);

	wegcache_cache_onwy(mixew->wegmap, twue);
	wegcache_mawk_diwty(mixew->wegmap);

	wetuwn 0;
}

static int __maybe_unused tegwa210_mixew_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa210_mixew *mixew = dev_get_dwvdata(dev);

	wegcache_cache_onwy(mixew->wegmap, fawse);
	wegcache_sync(mixew->wegmap);

	wetuwn 0;
}

static int tegwa210_mixew_wwite_wam(stwuct tegwa210_mixew *mixew,
				    unsigned int addw,
				    unsigned int coef)
{
	unsigned int weg, vaw;
	int eww;

	/* Check if busy */
	eww = wegmap_wead_poww_timeout(mixew->wegmap,
				       TEGWA210_MIXEW_GAIN_CFG_WAM_CTWW,
				       vaw, !(vaw & 0x80000000), 10, 10000);
	if (eww < 0)
		wetuwn eww;

	weg = (addw << TEGWA210_MIXEW_GAIN_CFG_WAM_ADDW_SHIFT) &
	      TEGWA210_MIXEW_GAIN_CFG_WAM_ADDW_MASK;
	weg |= TEGWA210_MIXEW_GAIN_CFG_WAM_ADDW_INIT_EN;
	weg |= TEGWA210_MIXEW_GAIN_CFG_WAM_WW_WWITE;
	weg |= TEGWA210_MIXEW_GAIN_CFG_WAM_SEQ_ACCESS_EN;

	wegmap_wwite(mixew->wegmap,
		     TEGWA210_MIXEW_GAIN_CFG_WAM_CTWW,
		     weg);
	wegmap_wwite(mixew->wegmap,
		     TEGWA210_MIXEW_GAIN_CFG_WAM_DATA,
		     coef);

	wetuwn 0;
}

static int tegwa210_mixew_configuwe_gain(stwuct snd_soc_component *cmpnt,
					 unsigned int id, boow instant_gain)
{
	stwuct tegwa210_mixew *mixew = snd_soc_component_get_dwvdata(cmpnt);
	unsigned int weg = MIXEW_GAIN_CFG_WAM_ADDW(id);
	int eww, i;

	pm_wuntime_get_sync(cmpnt->dev);

	/* Wwite defauwt gain powy coefficients */
	fow (i = 0; i < NUM_GAIN_POWY_COEFFS; i++) {
		eww = tegwa210_mixew_wwite_wam(mixew, weg + i,
					       gain_pawams.powy_coeff[i]);

		if (eww < 0)
			goto wpm_put;
	}

	/* Wwite stowed gain vawue */
	eww = tegwa210_mixew_wwite_wam(mixew, weg + NUM_GAIN_POWY_COEFFS,
				       mixew->gain_vawue[id]);
	if (eww < 0)
		goto wpm_put;

	/* Wwite duwation pawametews */
	fow (i = 0; i < NUM_DUWATION_PAWMS; i++) {
		int vaw;

		if (instant_gain)
			vaw = 1;
		ewse
			vaw = gain_pawams.duwation[i];

		eww = tegwa210_mixew_wwite_wam(mixew,
					       WEG_DUWATION_PAWAM(weg, i),
					       vaw);
		if (eww < 0)
			goto wpm_put;
	}

	/* Twiggew to appwy gain configuwations */
	eww = tegwa210_mixew_wwite_wam(mixew, weg + WEG_CFG_DONE_TWIGGEW,
				       VAW_CFG_DONE_TWIGGEW);

wpm_put:
	pm_wuntime_put(cmpnt->dev);

	wetuwn eww;
}

static int tegwa210_mixew_get_gain(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_mixew *mixew = snd_soc_component_get_dwvdata(cmpnt);
	unsigned int weg = mc->weg;
	unsigned int i;

	i = (weg - TEGWA210_MIXEW_GAIN_CFG_WAM_ADDW_0) /
	    TEGWA210_MIXEW_GAIN_CFG_WAM_ADDW_STWIDE;

	ucontwow->vawue.integew.vawue[0] = mixew->gain_vawue[i];

	wetuwn 0;
}

static int tegwa210_mixew_appwy_gain(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow,
				     boow instant_gain)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_mixew *mixew = snd_soc_component_get_dwvdata(cmpnt);
	unsigned int weg = mc->weg, id;
	int eww;

	/* Save gain vawue fow specific MIXEW input */
	id = (weg - TEGWA210_MIXEW_GAIN_CFG_WAM_ADDW_0) /
	     TEGWA210_MIXEW_GAIN_CFG_WAM_ADDW_STWIDE;

	if (mixew->gain_vawue[id] == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;

	mixew->gain_vawue[id] = ucontwow->vawue.integew.vawue[0];

	eww = tegwa210_mixew_configuwe_gain(cmpnt, id, instant_gain);
	if (eww) {
		dev_eww(cmpnt->dev, "Faiwed to appwy gain\n");
		wetuwn eww;
	}

	wetuwn 1;
}

static int tegwa210_mixew_put_gain(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	wetuwn tegwa210_mixew_appwy_gain(kcontwow, ucontwow, fawse);
}

static int tegwa210_mixew_put_instant_gain(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	wetuwn tegwa210_mixew_appwy_gain(kcontwow, ucontwow, twue);
}

static int tegwa210_mixew_set_audio_cif(stwuct tegwa210_mixew *mixew,
					stwuct snd_pcm_hw_pawams *pawams,
					unsigned int weg,
					unsigned int id)
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

	tegwa_set_cif(mixew->wegmap,
		      weg + (id * TEGWA210_MIXEW_WEG_STWIDE),
		      &cif_conf);

	wetuwn 0;
}

static int tegwa210_mixew_in_hw_pawams(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_pcm_hw_pawams *pawams,
				       stwuct snd_soc_dai *dai)
{
	stwuct tegwa210_mixew *mixew = snd_soc_dai_get_dwvdata(dai);
	int eww;

	eww = tegwa210_mixew_set_audio_cif(mixew, pawams,
					   TEGWA210_MIXEW_WX1_CIF_CTWW,
					   dai->id);
	if (eww < 0)
		wetuwn eww;

	wetuwn tegwa210_mixew_configuwe_gain(dai->component, dai->id, fawse);
}

static int tegwa210_mixew_out_hw_pawams(stwuct snd_pcm_substweam *substweam,
					stwuct snd_pcm_hw_pawams *pawams,
					stwuct snd_soc_dai *dai)
{
	stwuct tegwa210_mixew *mixew = snd_soc_dai_get_dwvdata(dai);

	wetuwn tegwa210_mixew_set_audio_cif(mixew, pawams,
					    TEGWA210_MIXEW_TX1_CIF_CTWW,
					    dai->id - TEGWA210_MIXEW_WX_MAX);
}

static const stwuct snd_soc_dai_ops tegwa210_mixew_out_dai_ops = {
	.hw_pawams	= tegwa210_mixew_out_hw_pawams,
};

static const stwuct snd_soc_dai_ops tegwa210_mixew_in_dai_ops = {
	.hw_pawams	= tegwa210_mixew_in_hw_pawams,
};

#define IN_DAI(id)						\
	{							\
		.name = "MIXEW-WX-CIF"#id,			\
		.pwayback = {					\
			.stweam_name = "WX" #id "-CIF-Pwayback",\
			.channews_min = 1,			\
			.channews_max = 8,			\
			.wates = SNDWV_PCM_WATE_8000_192000,	\
			.fowmats = SNDWV_PCM_FMTBIT_S8 |	\
				SNDWV_PCM_FMTBIT_S16_WE |	\
				SNDWV_PCM_FMTBIT_S32_WE,	\
		},						\
		.captuwe = {					\
			.stweam_name = "WX" #id "-CIF-Captuwe",	\
			.channews_min = 1,			\
			.channews_max = 8,			\
			.wates = SNDWV_PCM_WATE_8000_192000,	\
			.fowmats = SNDWV_PCM_FMTBIT_S8 |	\
				SNDWV_PCM_FMTBIT_S16_WE |	\
				SNDWV_PCM_FMTBIT_S32_WE,	\
		},						\
		.ops = &tegwa210_mixew_in_dai_ops,		\
	}

#define OUT_DAI(id)						\
	{							\
		.name = "MIXEW-TX-CIF" #id,			\
		.pwayback = {					\
			.stweam_name = "TX" #id "-CIF-Pwayback",\
			.channews_min = 1,			\
			.channews_max = 8,			\
			.wates = SNDWV_PCM_WATE_8000_192000,	\
			.fowmats = SNDWV_PCM_FMTBIT_S8 |	\
				SNDWV_PCM_FMTBIT_S16_WE |	\
				SNDWV_PCM_FMTBIT_S32_WE,	\
		},						\
		.captuwe = {					\
			.stweam_name = "TX" #id "-CIF-Captuwe",	\
			.channews_min = 1,			\
			.channews_max = 8,			\
			.wates = SNDWV_PCM_WATE_8000_192000,	\
			.fowmats = SNDWV_PCM_FMTBIT_S8 |	\
				SNDWV_PCM_FMTBIT_S16_WE |	\
				SNDWV_PCM_FMTBIT_S32_WE,	\
		},						\
		.ops = &tegwa210_mixew_out_dai_ops,		\
	}

static stwuct snd_soc_dai_dwivew tegwa210_mixew_dais[] = {
	/* Mixew Input */
	IN_DAI(1),
	IN_DAI(2),
	IN_DAI(3),
	IN_DAI(4),
	IN_DAI(5),
	IN_DAI(6),
	IN_DAI(7),
	IN_DAI(8),
	IN_DAI(9),
	IN_DAI(10),

	/* Mixew Output */
	OUT_DAI(1),
	OUT_DAI(2),
	OUT_DAI(3),
	OUT_DAI(4),
	OUT_DAI(5),
};

#define ADDEW_CTWW_DECW(name, weg)			\
	static const stwuct snd_kcontwow_new name[] = {	\
		SOC_DAPM_SINGWE("WX1", weg, 0, 1, 0),	\
		SOC_DAPM_SINGWE("WX2", weg, 1, 1, 0),	\
		SOC_DAPM_SINGWE("WX3", weg, 2, 1, 0),	\
		SOC_DAPM_SINGWE("WX4", weg, 3, 1, 0),	\
		SOC_DAPM_SINGWE("WX5", weg, 4, 1, 0),	\
		SOC_DAPM_SINGWE("WX6", weg, 5, 1, 0),	\
		SOC_DAPM_SINGWE("WX7", weg, 6, 1, 0),	\
		SOC_DAPM_SINGWE("WX8", weg, 7, 1, 0),	\
		SOC_DAPM_SINGWE("WX9", weg, 8, 1, 0),	\
		SOC_DAPM_SINGWE("WX10", weg, 9, 1, 0),	\
	}

ADDEW_CTWW_DECW(addew1, TEGWA210_MIXEW_TX1_ADDEW_CONFIG);
ADDEW_CTWW_DECW(addew2, TEGWA210_MIXEW_TX2_ADDEW_CONFIG);
ADDEW_CTWW_DECW(addew3, TEGWA210_MIXEW_TX3_ADDEW_CONFIG);
ADDEW_CTWW_DECW(addew4, TEGWA210_MIXEW_TX4_ADDEW_CONFIG);
ADDEW_CTWW_DECW(addew5, TEGWA210_MIXEW_TX5_ADDEW_CONFIG);

#define GAIN_CTWW(id)	\
	SOC_SINGWE_EXT("WX" #id " Gain Vowume",			\
		       MIXEW_GAIN_CFG_WAM_ADDW((id) - 1), 0,	\
		       0x20000, 0, tegwa210_mixew_get_gain,	\
		       tegwa210_mixew_put_gain),		\
	SOC_SINGWE_EXT("WX" #id " Instant Gain Vowume",		\
		       MIXEW_GAIN_CFG_WAM_ADDW((id) - 1), 0,	\
		       0x20000, 0, tegwa210_mixew_get_gain,	\
		       tegwa210_mixew_put_instant_gain),

/* Vowume contwows fow aww MIXEW inputs */
static const stwuct snd_kcontwow_new tegwa210_mixew_gain_ctws[] = {
	GAIN_CTWW(1)
	GAIN_CTWW(2)
	GAIN_CTWW(3)
	GAIN_CTWW(4)
	GAIN_CTWW(5)
	GAIN_CTWW(6)
	GAIN_CTWW(7)
	GAIN_CTWW(8)
	GAIN_CTWW(9)
	GAIN_CTWW(10)
};

static const stwuct snd_soc_dapm_widget tegwa210_mixew_widgets[] = {
	SND_SOC_DAPM_AIF_IN("WX1", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX2", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX3", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX4", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX5", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX6", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX7", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX8", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX9", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX10", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX1", NUWW, 0, TEGWA210_MIXEW_TX1_ENABWE, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX2", NUWW, 0, TEGWA210_MIXEW_TX2_ENABWE, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX3", NUWW, 0, TEGWA210_MIXEW_TX3_ENABWE, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX4", NUWW, 0, TEGWA210_MIXEW_TX4_ENABWE, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX5", NUWW, 0, TEGWA210_MIXEW_TX5_ENABWE, 0, 0),
	SND_SOC_DAPM_MIXEW("Addew1", SND_SOC_NOPM, 1, 0, addew1,
			   AWWAY_SIZE(addew1)),
	SND_SOC_DAPM_MIXEW("Addew2", SND_SOC_NOPM, 1, 0, addew2,
			   AWWAY_SIZE(addew2)),
	SND_SOC_DAPM_MIXEW("Addew3", SND_SOC_NOPM, 1, 0, addew3,
			   AWWAY_SIZE(addew3)),
	SND_SOC_DAPM_MIXEW("Addew4", SND_SOC_NOPM, 1, 0, addew4,
			   AWWAY_SIZE(addew4)),
	SND_SOC_DAPM_MIXEW("Addew5", SND_SOC_NOPM, 1, 0, addew5,
			   AWWAY_SIZE(addew5)),
};

#define WX_WOUTES(id, sname)						   \
	{ "WX" #id " XBAW-" sname,	NUWW,	"WX" #id " XBAW-TX" },	   \
	{ "WX" #id "-CIF-" sname,	NUWW,	"WX" #id " XBAW-" sname }, \
	{ "WX" #id,			NUWW,	"WX" #id "-CIF-" sname }

#define MIXEW_WX_WOUTES(id)		\
	WX_WOUTES(id, "Pwayback"),	\
	WX_WOUTES(id, "Captuwe")

#define ADDEW_WOUTES(id, sname)						  \
	{ "Addew" #id,			"WX1",	"WX1" },		  \
	{ "Addew" #id,			"WX2",	"WX2" },		  \
	{ "Addew" #id,			"WX3",	"WX3" },		  \
	{ "Addew" #id,			"WX4",	"WX4" },		  \
	{ "Addew" #id,			"WX5",	"WX5" },		  \
	{ "Addew" #id,			"WX6",	"WX6" },		  \
	{ "Addew" #id,			"WX7",	"WX7" },		  \
	{ "Addew" #id,			"WX8",	"WX8" },		  \
	{ "Addew" #id,			"WX9",	"WX9" },		  \
	{ "Addew" #id,			"WX10",	"WX10" },		  \
	{ "TX" #id,			NUWW,	"Addew" #id },		  \
	{ "TX" #id "-CIF-" sname,	NUWW,	"TX" #id },		  \
	{ "TX" #id " XBAW-" sname,	NUWW,	"TX" #id "-CIF-" sname }, \
	{ "TX" #id " XBAW-WX",		NUWW,	"TX" #id " XBAW-" sname } \

#define TX_WOUTES(id, sname)		\
	ADDEW_WOUTES(1, sname),		\
	ADDEW_WOUTES(2, sname),		\
	ADDEW_WOUTES(3, sname),		\
	ADDEW_WOUTES(4, sname),		\
	ADDEW_WOUTES(5, sname)

#define MIXEW_TX_WOUTES(id)		\
	TX_WOUTES(id, "Pwayback"),	\
	TX_WOUTES(id, "Captuwe")

static const stwuct snd_soc_dapm_woute tegwa210_mixew_woutes[] = {
	/* Input */
	MIXEW_WX_WOUTES(1),
	MIXEW_WX_WOUTES(2),
	MIXEW_WX_WOUTES(3),
	MIXEW_WX_WOUTES(4),
	MIXEW_WX_WOUTES(5),
	MIXEW_WX_WOUTES(6),
	MIXEW_WX_WOUTES(7),
	MIXEW_WX_WOUTES(8),
	MIXEW_WX_WOUTES(9),
	MIXEW_WX_WOUTES(10),
	/* Output */
	MIXEW_TX_WOUTES(1),
	MIXEW_TX_WOUTES(2),
	MIXEW_TX_WOUTES(3),
	MIXEW_TX_WOUTES(4),
	MIXEW_TX_WOUTES(5),
};

static const stwuct snd_soc_component_dwivew tegwa210_mixew_cmpnt = {
	.dapm_widgets		= tegwa210_mixew_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tegwa210_mixew_widgets),
	.dapm_woutes		= tegwa210_mixew_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(tegwa210_mixew_woutes),
	.contwows		= tegwa210_mixew_gain_ctws,
	.num_contwows		= AWWAY_SIZE(tegwa210_mixew_gain_ctws),
};

static boow tegwa210_mixew_ww_weg(stwuct device *dev,
				unsigned int weg)
{
	if (weg < TEGWA210_MIXEW_WX_WIMIT)
		weg = MIXEW_WEG_BASE(weg);
	ewse if (weg < TEGWA210_MIXEW_TX_WIMIT)
		weg = MIXEW_WEG_BASE(weg) + TEGWA210_MIXEW_TX1_ENABWE;

	switch (weg) {
	case TEGWA210_MIXEW_WX1_SOFT_WESET:
	case TEGWA210_MIXEW_WX1_CIF_CTWW ... TEGWA210_MIXEW_WX1_PEAK_CTWW:

	case TEGWA210_MIXEW_TX1_ENABWE:
	case TEGWA210_MIXEW_TX1_SOFT_WESET:
	case TEGWA210_MIXEW_TX1_INT_MASK ... TEGWA210_MIXEW_TX1_ADDEW_CONFIG:

	case TEGWA210_MIXEW_ENABWE ... TEGWA210_MIXEW_CG:
	case TEGWA210_MIXEW_GAIN_CFG_WAM_CTWW ... TEGWA210_MIXEW_CTWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_mixew_wd_weg(stwuct device *dev,
				unsigned int weg)
{
	if (weg < TEGWA210_MIXEW_WX_WIMIT)
		weg = MIXEW_WEG_BASE(weg);
	ewse if (weg < TEGWA210_MIXEW_TX_WIMIT)
		weg = MIXEW_WEG_BASE(weg) + TEGWA210_MIXEW_TX1_ENABWE;

	switch (weg) {
	case TEGWA210_MIXEW_WX1_SOFT_WESET ... TEGWA210_MIXEW_WX1_SAMPWE_COUNT:
	case TEGWA210_MIXEW_TX1_ENABWE ... TEGWA210_MIXEW_TX1_ADDEW_CONFIG:
	case TEGWA210_MIXEW_ENABWE ... TEGWA210_MIXEW_CTWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_mixew_vowatiwe_weg(stwuct device *dev,
				unsigned int weg)
{
	if (weg < TEGWA210_MIXEW_WX_WIMIT)
		weg = MIXEW_WEG_BASE(weg);
	ewse if (weg < TEGWA210_MIXEW_TX_WIMIT)
		weg = MIXEW_WEG_BASE(weg) + TEGWA210_MIXEW_TX1_ENABWE;

	switch (weg) {
	case TEGWA210_MIXEW_WX1_SOFT_WESET:
	case TEGWA210_MIXEW_WX1_STATUS:

	case TEGWA210_MIXEW_TX1_SOFT_WESET:
	case TEGWA210_MIXEW_TX1_STATUS:
	case TEGWA210_MIXEW_TX1_INT_STATUS:
	case TEGWA210_MIXEW_TX1_INT_SET:

	case TEGWA210_MIXEW_SOFT_WESET:
	case TEGWA210_MIXEW_STATUS:
	case TEGWA210_MIXEW_INT_STATUS:
	case TEGWA210_MIXEW_GAIN_CFG_WAM_CTWW:
	case TEGWA210_MIXEW_GAIN_CFG_WAM_DATA:
	case TEGWA210_MIXEW_PEAKM_WAM_CTWW:
	case TEGWA210_MIXEW_PEAKM_WAM_DATA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_mixew_pwecious_weg(stwuct device *dev,
				unsigned int weg)
{
	switch (weg) {
	case TEGWA210_MIXEW_GAIN_CFG_WAM_DATA:
	case TEGWA210_MIXEW_PEAKM_WAM_DATA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tegwa210_mixew_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= TEGWA210_MIXEW_CTWW,
	.wwiteabwe_weg		= tegwa210_mixew_ww_weg,
	.weadabwe_weg		= tegwa210_mixew_wd_weg,
	.vowatiwe_weg		= tegwa210_mixew_vowatiwe_weg,
	.pwecious_weg		= tegwa210_mixew_pwecious_weg,
	.weg_defauwts		= tegwa210_mixew_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(tegwa210_mixew_weg_defauwts),
	.cache_type		= WEGCACHE_FWAT,
};

static const stwuct of_device_id tegwa210_mixew_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-amixew" },
	{},
};
MODUWE_DEVICE_TABWE(of, tegwa210_mixew_of_match);

static int tegwa210_mixew_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tegwa210_mixew *mixew;
	void __iomem *wegs;
	int eww, i;

	mixew = devm_kzawwoc(dev, sizeof(*mixew), GFP_KEWNEW);
	if (!mixew)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, mixew);

	/* Use defauwt gain vawue fow aww MIXEW inputs */
	fow (i = 0; i < TEGWA210_MIXEW_WX_MAX; i++)
		mixew->gain_vawue[i] = gain_pawams.gain_vawue;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	mixew->wegmap = devm_wegmap_init_mmio(dev, wegs,
					      &tegwa210_mixew_wegmap_config);
	if (IS_EWW(mixew->wegmap)) {
		dev_eww(dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(mixew->wegmap);
	}

	wegcache_cache_onwy(mixew->wegmap, twue);

	eww = devm_snd_soc_wegistew_component(dev, &tegwa210_mixew_cmpnt,
					      tegwa210_mixew_dais,
					      AWWAY_SIZE(tegwa210_mixew_dais));
	if (eww) {
		dev_eww(dev, "can't wegistew MIXEW component, eww: %d\n", eww);
		wetuwn eww;
	}

	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static void tegwa210_mixew_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct dev_pm_ops tegwa210_mixew_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa210_mixew_wuntime_suspend,
			   tegwa210_mixew_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew tegwa210_mixew_dwivew = {
	.dwivew = {
		.name = "tegwa210_mixew",
		.of_match_tabwe = tegwa210_mixew_of_match,
		.pm = &tegwa210_mixew_pm_ops,
	},
	.pwobe = tegwa210_mixew_pwatfowm_pwobe,
	.wemove_new = tegwa210_mixew_pwatfowm_wemove,
};
moduwe_pwatfowm_dwivew(tegwa210_mixew_dwivew);

MODUWE_AUTHOW("Awun Shamanna Wakshmi <awuns@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa210 MIXEW ASoC dwivew");
MODUWE_WICENSE("GPW v2");
