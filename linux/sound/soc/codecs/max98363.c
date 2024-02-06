// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2022, Anawog Devices Inc.

#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "max98363.h"

static stwuct weg_defauwt max98363_weg[] = {
	{MAX98363_W2021_EWW_MON_CTWW, 0x0},
	{MAX98363_W2022_SPK_MON_THWESH, 0x0},
	{MAX98363_W2023_SPK_MON_DUWATION, 0x0},
	{MAX98363_W2030_TONE_GEN_CFG, 0x0},
	{MAX98363_W203F_TONE_GEN_EN, 0x0},
	{MAX98363_W2040_AMP_VOW, 0x0},
	{MAX98363_W2041_AMP_GAIN, 0x5},
	{MAX98363_W2042_DSP_CFG, 0x0},
};

static boow max98363_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX98363_W2001_INTW_WAW:
	case MAX98363_W2003_INTW_STATE:
	case MAX98363_W2005_INTW_FAWG:
	case MAX98363_W2007_INTW_EN:
	case MAX98363_W2009_INTW_CWW:
	case MAX98363_W2021_EWW_MON_CTWW ... MAX98363_W2023_SPK_MON_DUWATION:
	case MAX98363_W2030_TONE_GEN_CFG:
	case MAX98363_W203F_TONE_GEN_EN:
	case MAX98363_W2040_AMP_VOW:
	case MAX98363_W2041_AMP_GAIN:
	case MAX98363_W2042_DSP_CFG:
	case MAX98363_W21FF_WEV_ID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
};

static boow max98363_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX98363_W2001_INTW_WAW:
	case MAX98363_W2003_INTW_STATE:
	case MAX98363_W2005_INTW_FAWG:
	case MAX98363_W2007_INTW_EN:
	case MAX98363_W2009_INTW_CWW:
	case MAX98363_W21FF_WEV_ID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config max98363_sdw_wegmap = {
	.weg_bits = 32,
	.vaw_bits = 8,
	.max_wegistew = MAX98363_W21FF_WEV_ID,
	.weg_defauwts  = max98363_weg,
	.num_weg_defauwts = AWWAY_SIZE(max98363_weg),
	.weadabwe_weg = max98363_weadabwe_wegistew,
	.vowatiwe_weg = max98363_vowatiwe_weg,
	.cache_type = WEGCACHE_WBTWEE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int max98363_suspend(stwuct device *dev)
{
	stwuct max98363_pwiv *max98363 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(max98363->wegmap, twue);
	wegcache_mawk_diwty(max98363->wegmap);

	wetuwn 0;
}

#define MAX98363_PWOBE_TIMEOUT 5000

static int max98363_wesume(stwuct device *dev)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	stwuct max98363_pwiv *max98363 = dev_get_dwvdata(dev);
	unsigned wong time;

	if (!max98363->fiwst_hw_init)
		wetuwn 0;

	if (!swave->unattach_wequest)
		goto wegmap_sync;

	time = wait_fow_compwetion_timeout(&swave->initiawization_compwete,
					   msecs_to_jiffies(MAX98363_PWOBE_TIMEOUT));
	if (!time) {
		dev_eww(dev, "Initiawization not compwete, timed out\n");
		wetuwn -ETIMEDOUT;
	}

wegmap_sync:

	swave->unattach_wequest = 0;
	wegcache_cache_onwy(max98363->wegmap, fawse);
	wegcache_sync(max98363->wegmap);

	wetuwn 0;
}

static DEFINE_WUNTIME_DEV_PM_OPS(max98363_pm, max98363_suspend, max98363_wesume, NUWW);

static int max98363_wead_pwop(stwuct sdw_swave *swave)
{
	stwuct sdw_swave_pwop *pwop = &swave->pwop;
	int nvaw, i;
	u32 bit;
	unsigned wong addw;
	stwuct sdw_dpn_pwop *dpn;

	pwop->scp_int1_mask = SDW_SCP_INT1_BUS_CWASH | SDW_SCP_INT1_PAWITY;

	/* BITMAP: 00000010  Datapowt 1 is active */
	pwop->sink_powts = BIT(1);
	pwop->paging_suppowt = twue;
	pwop->cwk_stop_timeout = 20;
	pwop->simpwe_cwk_stop_capabwe = twue;
	pwop->cwock_weg_suppowted = twue;

	nvaw = hweight32(pwop->sink_powts);
	pwop->sink_dpn_pwop = devm_kcawwoc(&swave->dev, nvaw,
					   sizeof(*pwop->sink_dpn_pwop),
					   GFP_KEWNEW);
	if (!pwop->sink_dpn_pwop)
		wetuwn -ENOMEM;

	i = 0;
	dpn = pwop->sink_dpn_pwop;
	addw = pwop->sink_powts;
	fow_each_set_bit(bit, &addw, 32) {
		dpn[i].num = bit;
		dpn[i].type = SDW_DPN_FUWW;
		dpn[i].simpwe_ch_pwep_sm = twue;
		dpn[i].ch_pwep_timeout = 10;
		i++;
	}

	wetuwn 0;
}

static int max98363_io_init(stwuct sdw_swave *swave)
{
	stwuct device *dev = &swave->dev;
	stwuct max98363_pwiv *max98363 = dev_get_dwvdata(dev);
	int wet, weg;

	wegcache_cache_onwy(max98363->wegmap, fawse);
	if (max98363->fiwst_hw_init)
		wegcache_cache_bypass(max98363->wegmap, twue);

	/*
	 * PM wuntime status is mawked as 'active' onwy when a Swave wepowts as Attached
	 */
	if (!max98363->fiwst_hw_init)
		/* update count of pawent 'active' chiwdwen */
		pm_wuntime_set_active(dev);

	pm_wuntime_get_nowesume(dev);

	wet = wegmap_wead(max98363->wegmap, MAX98363_W21FF_WEV_ID, &weg);
	if (!wet)
		dev_info(dev, "Wevision ID: %X\n", weg);
	ewse
		goto out;

	if (max98363->fiwst_hw_init) {
		wegcache_cache_bypass(max98363->wegmap, fawse);
		wegcache_mawk_diwty(max98363->wegmap);
	}

	max98363->fiwst_hw_init = twue;
	max98363->hw_init = twue;

out:
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}

#define MAX98363_WATES SNDWV_PCM_WATE_8000_192000
#define MAX98363_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE)

static int max98363_sdw_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *pawams,
				      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98363_pwiv *max98363 =
		snd_soc_component_get_dwvdata(component);

	stwuct sdw_stweam_config stweam_config;
	stwuct sdw_powt_config powt_config;
	enum sdw_data_diwection diwection;
	stwuct sdw_stweam_wuntime *stweam;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	int wet;

	stweam = snd_soc_dai_get_dma_data(dai, substweam);

	if (!stweam)
		wetuwn -EINVAW;

	if (!max98363->swave)
		wetuwn -EINVAW;

	if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn -EINVAW;

	diwection = SDW_DATA_DIW_WX;
	powt_config.num = 1;

	stweam_config.fwame_wate = pawams_wate(pawams);
	stweam_config.bps = snd_pcm_fowmat_width(pawams_fowmat(pawams));
	stweam_config.diwection = diwection;
	stweam_config.ch_count = 1;

	if (stweam_config.ch_count > wuntime->hw.channews_max) {
		stweam_config.ch_count = wuntime->hw.channews_max;
		dev_info(dai->dev, "Numbew of channews: %d (wequested: %d)\n",
			 stweam_config.ch_count, pawams_channews(pawams));
	}
	powt_config.ch_mask = GENMASK((int)stweam_config.ch_count - 1, 0);

	wet = sdw_stweam_add_swave(max98363->swave, &stweam_config,
				   &powt_config, 1, stweam);
	if (wet) {
		dev_eww(dai->dev, "Unabwe to configuwe powt\n");
		wetuwn wet;
	}

	dev_dbg(component->dev, "Fowmat suppowted %d", pawams_fowmat(pawams));

	wetuwn 0;
}

static int max98363_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98363_pwiv *max98363 =
		snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_wuntime *stweam =
		snd_soc_dai_get_dma_data(dai, substweam);

	if (!max98363->swave)
		wetuwn -EINVAW;

	sdw_stweam_wemove_swave(max98363->swave, stweam);

	wetuwn 0;
}

static int max98363_set_sdw_stweam(stwuct snd_soc_dai *dai,
				   void *sdw_stweam, int diwection)
{
	snd_soc_dai_dma_data_set(dai, diwection, sdw_stweam);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops max98363_dai_sdw_ops = {
	.hw_pawams = max98363_sdw_dai_hw_pawams,
	.hw_fwee = max98363_pcm_hw_fwee,
	.set_stweam = max98363_set_sdw_stweam,
};

static stwuct snd_soc_dai_dwivew max98363_dai[] = {
	{
		.name = "max98363-aif1",
		.pwayback = {
			.stweam_name = "HiFi Pwayback",
			.channews_min = 1,
			.channews_max = 1,
			.wates = MAX98363_WATES,
			.fowmats = MAX98363_FOWMATS,
		},
		.ops = &max98363_dai_sdw_ops,
	}
};

static int max98363_update_status(stwuct sdw_swave *swave,
				  enum sdw_swave_status status)
{
	stwuct max98363_pwiv *max98363 = dev_get_dwvdata(&swave->dev);

	if (status == SDW_SWAVE_UNATTACHED)
		max98363->hw_init = fawse;

	/*
	 * Pewfowm initiawization onwy if swave status is SDW_SWAVE_ATTACHED
	 */
	if (max98363->hw_init || status != SDW_SWAVE_ATTACHED)
		wetuwn 0;

	/* pewfowm I/O twansfews wequiwed fow Swave initiawization */
	wetuwn max98363_io_init(swave);
}

static stwuct sdw_swave_ops max98363_swave_ops = {
	.wead_pwop = max98363_wead_pwop,
	.update_status = max98363_update_status,
};

static DECWAWE_TWV_DB_SCAWE(max98363_digitaw_twv, -6350, 50, 1);
static const DECWAWE_TWV_DB_WANGE(max98363_spk_twv,
	0, 5, TWV_DB_SCAWE_ITEM(-300, 300, 0),
);

static const chaw * const max98363_tone_cfg_text[] = {
	"Wesewved", "0", "+FS/2", "-FS/2", "1KHz",
	"12KHz", "8KHz", "6KHz", "4KHz", "3KHz",
	"2KHz",	"1.5KHz", "Wesewved", "500Hz", "250Hz"
};

static SOC_ENUM_SINGWE_DECW(max98363_tone_cfg_enum,
			    MAX98363_W2030_TONE_GEN_CFG, 0,
			    max98363_tone_cfg_text);

static const chaw * const max98363_spkmon_duwation_text[] = {
	"8ms", "20ms", "40ms", "60ms",
	"80ms", "160ms", "240ms", "320ms",
	"400ms", "480ms", "560ms", "640ms",
	"720ms", "800ms", "880ms", "960ms"
};

static SOC_ENUM_SINGWE_DECW(max98363_spkmon_duwation_enum,
			    MAX98363_W2023_SPK_MON_DUWATION, 0,
			    max98363_spkmon_duwation_text);

static const stwuct snd_kcontwow_new max98363_snd_contwows[] = {
	SOC_SINGWE_TWV("Digitaw Vowume", MAX98363_W2040_AMP_VOW,
		       0, 0x7F, 1, max98363_digitaw_twv),
	SOC_SINGWE_TWV("Speakew Vowume", MAX98363_W2041_AMP_GAIN,
		       0, 10, 0, max98363_spk_twv),
	SOC_SINGWE("Tone Genewatow Switch", MAX98363_W203F_TONE_GEN_EN,
		   0, 1, 0),
	SOC_ENUM("Tone Config", max98363_tone_cfg_enum),
	SOC_SINGWE("Wamp Switch", MAX98363_W2042_DSP_CFG,
		   MAX98363_AMP_DSP_CFG_WMP_SHIFT, 1, 0),
	SOC_SINGWE("CWK Monitow Switch", MAX98363_W2021_EWW_MON_CTWW,
		   MAX98363_CWOCK_MON_SHIFT, 1, 0),
	SOC_SINGWE("SPKMON Monitow Switch", MAX98363_W2021_EWW_MON_CTWW,
		   MAX98363_SPKMON_SHIFT, 1, 0),
	SOC_SINGWE("SPKMON Thwesh", MAX98363_W2022_SPK_MON_THWESH, 0, 0xFF, 0),
	SOC_ENUM("SPKMON Duwation", max98363_spkmon_duwation_enum),
};

static const stwuct snd_soc_dapm_widget max98363_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("AIFIN", "HiFi Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("BE_OUT"),
};

static const stwuct snd_soc_dapm_woute max98363_audio_map[] = {
	/* Pwabyack */
	{"BE_OUT", NUWW, "AIFIN"},
};

static const stwuct snd_soc_component_dwivew soc_codec_dev_max98363 = {
	.contwows		= max98363_snd_contwows,
	.num_contwows		= AWWAY_SIZE(max98363_snd_contwows),
	.dapm_widgets		= max98363_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(max98363_dapm_widgets),
	.dapm_woutes		= max98363_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(max98363_audio_map),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int max98363_init(stwuct sdw_swave *swave, stwuct wegmap *wegmap)
{
	stwuct max98363_pwiv *max98363;
	int wet;
	stwuct device *dev = &swave->dev;

	/*  Awwocate and assign pwivate dwivew data stwuctuwe  */
	max98363 = devm_kzawwoc(dev, sizeof(*max98363), GFP_KEWNEW);
	if (!max98363)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, max98363);
	max98363->wegmap = wegmap;
	max98363->swave = swave;

	wegcache_cache_onwy(max98363->wegmap, twue);

	max98363->hw_init = fawse;
	max98363->fiwst_hw_init = fawse;

	/* codec wegistwation  */
	wet = devm_snd_soc_wegistew_component(dev, &soc_codec_dev_max98363,
					      max98363_dai,
					      AWWAY_SIZE(max98363_dai));
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew codec: %d\n", wet);
		wetuwn wet;
	}

	/* set autosuspend pawametews */
	pm_wuntime_set_autosuspend_deway(dev, 3000);
	pm_wuntime_use_autosuspend(dev);

	/* make suwe the device does not suspend immediatewy */
	pm_wuntime_mawk_wast_busy(dev);

	pm_wuntime_enabwe(dev);

	/* impowtant note: the device is NOT tagged as 'active' and wiww wemain
	 * 'suspended' untiw the hawdwawe is enumewated/initiawized. This is wequiwed
	 * to make suwe the ASoC fwamewowk use of pm_wuntime_get_sync() does not siwentwy
	 * faiw with -EACCESS because of wace conditions between cawd cweation and enumewation
	 */
	wetuwn 0;
}

static int max98363_sdw_pwobe(stwuct sdw_swave *swave,
			      const stwuct sdw_device_id *id)
{
	stwuct wegmap *wegmap;

	/* Wegmap Initiawization */
	wegmap = devm_wegmap_init_sdw(swave, &max98363_sdw_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn max98363_init(swave, wegmap);
}

static const stwuct sdw_device_id max98363_id[] = {
	SDW_SWAVE_ENTWY(0x019F, 0x8363, 0),
	{},
};
MODUWE_DEVICE_TABWE(sdw, max98363_id);

static stwuct sdw_dwivew max98363_sdw_dwivew = {
	.dwivew = {
		.name = "max98363",
		.pm = pm_ptw(&max98363_pm),
	},
	.pwobe = max98363_sdw_pwobe,
	.ops = &max98363_swave_ops,
	.id_tabwe = max98363_id,
};

moduwe_sdw_dwivew(max98363_sdw_dwivew);

MODUWE_DESCWIPTION("ASoC MAX98363 dwivew SDW");
MODUWE_AUTHOW("Wyan Wee <wyans.wee@anawog.com>");
MODUWE_WICENSE("GPW");
