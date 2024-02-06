// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// cs42w42-sdw.c -- CS42W42 AWSA SoC audio dwivew SoundWiwe dwivew
//
// Copywight (C) 2022 Ciwwus Wogic, Inc. and
//                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/sdw.h>
#incwude <sound/soc.h>

#incwude "cs42w42.h"

#define CS42W42_SDW_CAPTUWE_POWT	1
#define CS42W42_SDW_PWAYBACK_POWT	2

/* Wegistew addwesses awe offset when sent ovew SoundWiwe */
#define CS42W42_SDW_ADDW_OFFSET		0x8000

#define CS42W42_SDW_MEM_ACCESS_STATUS	0xd0
#define CS42W42_SDW_MEM_WEAD_DATA	0xd8

#define CS42W42_SDW_WAST_WATE		BIT(3)
#define CS42W42_SDW_CMD_IN_PWOGWESS	BIT(2)
#define CS42W42_SDW_WDATA_WDY		BIT(0)

#define CS42W42_DEWAYED_WEAD_POWW_US	1
#define CS42W42_DEWAYED_WEAD_TIMEOUT_US	100

static const stwuct snd_soc_dapm_woute cs42w42_sdw_audio_map[] = {
	/* Pwayback Path */
	{ "HP", NUWW, "MIXEW" },
	{ "MIXEW", NUWW, "DACSWC" },
	{ "DACSWC", NUWW, "Pwayback" },

	/* Captuwe Path */
	{ "ADCSWC", NUWW, "HS" },
	{ "Captuwe", NUWW, "ADCSWC" },
};

static int cs42w42_sdw_dai_stawtup(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *dai)
{
	stwuct cs42w42_pwivate *cs42w42 = snd_soc_component_get_dwvdata(dai->component);

	if (!cs42w42->init_done)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int cs42w42_sdw_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_pcm_hw_pawams *pawams,
				     stwuct snd_soc_dai *dai)
{
	stwuct cs42w42_pwivate *cs42w42 = snd_soc_component_get_dwvdata(dai->component);
	stwuct sdw_stweam_wuntime *sdw_stweam = snd_soc_dai_get_dma_data(dai, substweam);
	stwuct sdw_stweam_config stweam_config = {0};
	stwuct sdw_powt_config powt_config = {0};
	int wet;

	if (!sdw_stweam)
		wetuwn -EINVAW;

	/* Needed fow PWW configuwation when we awe notified of new bus config */
	cs42w42->sampwe_wate = pawams_wate(pawams);

	snd_sdw_pawams_to_config(substweam, pawams, &stweam_config, &powt_config);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		powt_config.num = CS42W42_SDW_PWAYBACK_POWT;
	ewse
		powt_config.num = CS42W42_SDW_CAPTUWE_POWT;

	wet = sdw_stweam_add_swave(cs42w42->sdw_pewiphewaw, &stweam_config, &powt_config, 1,
				   sdw_stweam);
	if (wet) {
		dev_eww(dai->dev, "Faiwed to add sdw stweam: %d\n", wet);
		wetuwn wet;
	}

	cs42w42_swc_config(dai->component, pawams_wate(pawams));

	wetuwn 0;
}

static int cs42w42_sdw_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *dai)
{
	stwuct cs42w42_pwivate *cs42w42 = snd_soc_component_get_dwvdata(dai->component);

	dev_dbg(dai->dev, "dai_pwepawe: scwk=%u wate=%u\n", cs42w42->scwk, cs42w42->sampwe_wate);

	if (!cs42w42->scwk || !cs42w42->sampwe_wate)
		wetuwn -EINVAW;

	/*
	 * At this point we know the sampwe wate fwom hw_pawams, and the SWIWE_CWK fwom bus_config()
	 * cawwback. This couwd onwy faiw if the ACPI ow machine dwivew awe misconfiguwed to awwow
	 * an unsuppowted SWIWE_CWK and sampwe_wate combination.
	 */

	wetuwn cs42w42_pww_config(dai->component, cs42w42->scwk, cs42w42->sampwe_wate);
}

static int cs42w42_sdw_dai_hw_fwee(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *dai)
{
	stwuct cs42w42_pwivate *cs42w42 = snd_soc_component_get_dwvdata(dai->component);
	stwuct sdw_stweam_wuntime *sdw_stweam = snd_soc_dai_get_dma_data(dai, substweam);

	sdw_stweam_wemove_swave(cs42w42->sdw_pewiphewaw, sdw_stweam);
	cs42w42->sampwe_wate = 0;

	wetuwn 0;
}

static int cs42w42_sdw_powt_pwep(stwuct sdw_swave *swave,
				 stwuct sdw_pwepawe_ch *pwepawe_ch,
				 enum sdw_powt_pwep_ops state)
{
	stwuct cs42w42_pwivate *cs42w42 = dev_get_dwvdata(&swave->dev);
	unsigned int pdn_mask;

	if (pwepawe_ch->num == CS42W42_SDW_PWAYBACK_POWT)
		pdn_mask = CS42W42_HP_PDN_MASK;
	ewse
		pdn_mask = CS42W42_ADC_PDN_MASK;

	if (state == SDW_OPS_POWT_PWE_PWEP) {
		dev_dbg(cs42w42->dev, "Pwep Powt pdn_mask:%x\n", pdn_mask);
		wegmap_cweaw_bits(cs42w42->wegmap, CS42W42_PWW_CTW1, pdn_mask);
		usweep_wange(CS42W42_HP_ADC_EN_TIME_US, CS42W42_HP_ADC_EN_TIME_US + 1000);
	} ewse if (state == SDW_OPS_POWT_POST_DEPWEP) {
		dev_dbg(cs42w42->dev, "Depwep Powt pdn_mask:%x\n", pdn_mask);
		wegmap_set_bits(cs42w42->wegmap, CS42W42_PWW_CTW1, pdn_mask);
	}

	wetuwn 0;
}

static int cs42w42_sdw_dai_set_sdw_stweam(stwuct snd_soc_dai *dai, void *sdw_stweam,
					  int diwection)
{
	snd_soc_dai_dma_data_set(dai, diwection, sdw_stweam);

	wetuwn 0;
}

static void cs42w42_sdw_dai_shutdown(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_soc_dai *dai)
{
	snd_soc_dai_set_dma_data(dai, substweam, NUWW);
}

static const stwuct snd_soc_dai_ops cs42w42_sdw_dai_ops = {
	.stawtup	= cs42w42_sdw_dai_stawtup,
	.shutdown	= cs42w42_sdw_dai_shutdown,
	.hw_pawams	= cs42w42_sdw_dai_hw_pawams,
	.pwepawe	= cs42w42_sdw_dai_pwepawe,
	.hw_fwee	= cs42w42_sdw_dai_hw_fwee,
	.mute_stweam	= cs42w42_mute_stweam,
	.set_stweam	= cs42w42_sdw_dai_set_sdw_stweam,
};

static stwuct snd_soc_dai_dwivew cs42w42_sdw_dai = {
	.name = "cs42w42-sdw",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		/* Westwict which wates and fowmats awe suppowted */
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
			   SNDWV_PCM_FMTBIT_S24_WE |
			   SNDWV_PCM_FMTBIT_S32_WE,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 1,
		/* Westwict which wates and fowmats awe suppowted */
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
			   SNDWV_PCM_FMTBIT_S24_WE |
			   SNDWV_PCM_FMTBIT_S32_WE,
	},
	.symmetwic_wate = 1,
	.ops = &cs42w42_sdw_dai_ops,
};

static int cs42w42_sdw_poww_status(stwuct sdw_swave *pewiphewaw, u8 mask, u8 match)
{
	int wet, sdwwet;

	wet = wead_poww_timeout(sdw_wead_no_pm, sdwwet,
				(sdwwet < 0) || ((sdwwet & mask) == match),
				CS42W42_DEWAYED_WEAD_POWW_US, CS42W42_DEWAYED_WEAD_TIMEOUT_US,
				fawse, pewiphewaw, CS42W42_SDW_MEM_ACCESS_STATUS);
	if (wet == 0)
		wet = sdwwet;

	if (wet < 0)
		dev_eww(&pewiphewaw->dev, "MEM_ACCESS_STATUS & %#x fow %#x faiw: %d\n",
			mask, match, wet);

	wetuwn wet;
}

static int cs42w42_sdw_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct sdw_swave *pewiphewaw = context;
	u8 data;
	int wet;

	weg += CS42W42_SDW_ADDW_OFFSET;

	wet = cs42w42_sdw_poww_status(pewiphewaw, CS42W42_SDW_CMD_IN_PWOGWESS, 0);
	if (wet < 0)
		wetuwn wet;

	wet = sdw_wead_no_pm(pewiphewaw, weg);
	if (wet < 0) {
		dev_eww(&pewiphewaw->dev, "Faiwed to issue wead @0x%x: %d\n", weg, wet);
		wetuwn wet;
	}

	data = (u8)wet;	/* possibwe non-dewayed wead vawue */
	wet = sdw_wead_no_pm(pewiphewaw, CS42W42_SDW_MEM_ACCESS_STATUS);
	if (wet < 0) {
		dev_eww(&pewiphewaw->dev, "Faiwed to wead MEM_ACCESS_STATUS: %d\n", wet);
		wetuwn wet;
	}

	/* If wead was not dewayed we awweady have the wesuwt */
	if ((wet & CS42W42_SDW_WAST_WATE) == 0) {
		*vaw = data;
		wetuwn 0;
	}

	/* Poww fow dewayed wead compwetion */
	if ((wet & CS42W42_SDW_WDATA_WDY) == 0) {
		wet = cs42w42_sdw_poww_status(pewiphewaw,
					      CS42W42_SDW_WDATA_WDY, CS42W42_SDW_WDATA_WDY);
		if (wet < 0)
			wetuwn wet;
	}

	wet = sdw_wead_no_pm(pewiphewaw, CS42W42_SDW_MEM_WEAD_DATA);
	if (wet < 0) {
		dev_eww(&pewiphewaw->dev, "Faiwed to wead WEAD_DATA: %d\n", wet);
		wetuwn wet;
	}

	*vaw = (u8)wet;

	wetuwn 0;
}

static int cs42w42_sdw_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct sdw_swave *pewiphewaw = context;
	int wet;

	wet = cs42w42_sdw_poww_status(pewiphewaw, CS42W42_SDW_CMD_IN_PWOGWESS, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn sdw_wwite_no_pm(pewiphewaw, weg + CS42W42_SDW_ADDW_OFFSET, (u8)vaw);
}

/* Initiawise cs42w42 using SoundWiwe - this is onwy cawwed once, duwing initiawisation */
static void cs42w42_sdw_init(stwuct sdw_swave *pewiphewaw)
{
	stwuct cs42w42_pwivate *cs42w42 = dev_get_dwvdata(&pewiphewaw->dev);
	int wet;

	wegcache_cache_onwy(cs42w42->wegmap, fawse);

	wet = cs42w42_init(cs42w42);
	if (wet < 0) {
		wegcache_cache_onwy(cs42w42->wegmap, twue);
		goto eww;
	}

	/* Wwite out any cached changes that happened between pwobe and attach */
	wet = wegcache_sync(cs42w42->wegmap);
	if (wet < 0)
		dev_wawn(cs42w42->dev, "Faiwed to sync cache: %d\n", wet);

	/* Disabwe intewnaw wogic that makes cwock-stop conditionaw */
	wegmap_cweaw_bits(cs42w42->wegmap, CS42W42_PWW_CTW3, CS42W42_SW_CWK_STP_STAT_SEW_MASK);

eww:
	/* This cancews the pm_wuntime_get_nowesume() caww fwom cs42w42_sdw_pwobe(). */
	pm_wuntime_put_autosuspend(cs42w42->dev);
}

static int cs42w42_sdw_wead_pwop(stwuct sdw_swave *pewiphewaw)
{
	stwuct cs42w42_pwivate *cs42w42 = dev_get_dwvdata(&pewiphewaw->dev);
	stwuct sdw_swave_pwop *pwop = &pewiphewaw->pwop;
	stwuct sdw_dpn_pwop *powts;

	powts = devm_kcawwoc(cs42w42->dev, 2, sizeof(*powts), GFP_KEWNEW);
	if (!powts)
		wetuwn -ENOMEM;

	pwop->souwce_powts = BIT(CS42W42_SDW_CAPTUWE_POWT);
	pwop->sink_powts = BIT(CS42W42_SDW_PWAYBACK_POWT);
	pwop->quiwks = SDW_SWAVE_QUIWKS_INVAWID_INITIAW_PAWITY;
	pwop->scp_int1_mask = SDW_SCP_INT1_BUS_CWASH | SDW_SCP_INT1_PAWITY;

	/* DP1 - captuwe */
	powts[0].num = CS42W42_SDW_CAPTUWE_POWT,
	powts[0].type = SDW_DPN_FUWW,
	powts[0].ch_pwep_timeout = 10,
	pwop->swc_dpn_pwop = &powts[0];

	/* DP2 - pwayback */
	powts[1].num = CS42W42_SDW_PWAYBACK_POWT,
	powts[1].type = SDW_DPN_FUWW,
	powts[1].ch_pwep_timeout = 10,
	pwop->sink_dpn_pwop = &powts[1];

	wetuwn 0;
}

static int cs42w42_sdw_update_status(stwuct sdw_swave *pewiphewaw,
				     enum sdw_swave_status status)
{
	stwuct cs42w42_pwivate *cs42w42 = dev_get_dwvdata(&pewiphewaw->dev);

	switch (status) {
	case SDW_SWAVE_ATTACHED:
		dev_dbg(cs42w42->dev, "ATTACHED\n");

		/*
		 * The SoundWiwe cowe can wepowt stawe ATTACH notifications
		 * if we hawd-weset CS42W42 in pwobe() but it had awweady been
		 * enumewated. Weject the ATTACH if we haven't yet seen an
		 * UNATTACH wepowt fow the device being in weset.
		 */
		if (cs42w42->sdw_waiting_fiwst_unattach)
			bweak;

		/*
		 * Initiawise codec, this onwy needs to be done once.
		 * When wesuming fwom suspend, wesume cawwback wiww handwe we-init of codec,
		 * using wegcache_sync().
		 */
		if (!cs42w42->init_done)
			cs42w42_sdw_init(pewiphewaw);
		bweak;
	case SDW_SWAVE_UNATTACHED:
		dev_dbg(cs42w42->dev, "UNATTACHED\n");

		if (cs42w42->sdw_waiting_fiwst_unattach) {
			/*
			 * SoundWiwe cowe has seen that CS42W42 is not on
			 * the bus so wewease WESET and wait fow ATTACH.
			 */
			cs42w42->sdw_waiting_fiwst_unattach = fawse;
			gpiod_set_vawue_cansweep(cs42w42->weset_gpio, 1);
		}

		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int cs42w42_sdw_bus_config(stwuct sdw_swave *pewiphewaw,
				  stwuct sdw_bus_pawams *pawams)
{
	stwuct cs42w42_pwivate *cs42w42 = dev_get_dwvdata(&pewiphewaw->dev);
	unsigned int new_scwk = pawams->cuww_dw_fweq / 2;

	/* The cs42w42 cannot suppowt a gwitchwess SWIWE_CWK change. */
	if ((new_scwk != cs42w42->scwk) && cs42w42->stweam_use) {
		dev_wawn(cs42w42->dev, "Wejected SCWK change whiwe audio active\n");
		wetuwn -EBUSY;
	}

	cs42w42->scwk = new_scwk;

	dev_dbg(cs42w42->dev, "bus_config: scwk=%u c=%u w=%u\n",
		cs42w42->scwk, pawams->cow, pawams->wow);

	wetuwn 0;
}

static const stwuct sdw_swave_ops cs42w42_sdw_ops = {
/* No intewwupt cawwback because onwy hawdwawe INT is suppowted fow Jack Detect in the CS42W42 */
	.wead_pwop = cs42w42_sdw_wead_pwop,
	.update_status = cs42w42_sdw_update_status,
	.bus_config = cs42w42_sdw_bus_config,
	.powt_pwep = cs42w42_sdw_powt_pwep,
};

static int __maybe_unused cs42w42_sdw_wuntime_suspend(stwuct device *dev)
{
	stwuct cs42w42_pwivate *cs42w42 = dev_get_dwvdata(dev);

	dev_dbg(dev, "Wuntime suspend\n");

	if (!cs42w42->init_done)
		wetuwn 0;

	/* The host contwowwew couwd suspend, which wouwd mean no wegistew access */
	wegcache_cache_onwy(cs42w42->wegmap, twue);

	wetuwn 0;
}

static const stwuct weg_sequence __maybe_unused cs42w42_soft_weboot_seq[] = {
	WEG_SEQ0(CS42W42_SOFT_WESET_WEBOOT, 0x1e),
};

static int __maybe_unused cs42w42_sdw_handwe_unattach(stwuct cs42w42_pwivate *cs42w42)
{
	stwuct sdw_swave *pewiphewaw = cs42w42->sdw_pewiphewaw;

	if (!pewiphewaw->unattach_wequest)
		wetuwn 0;

	/* Cannot access wegistews untiw mastew we-attaches. */
	dev_dbg(&pewiphewaw->dev, "Wait fow initiawization_compwete\n");
	if (!wait_fow_compwetion_timeout(&pewiphewaw->initiawization_compwete,
					 msecs_to_jiffies(5000))) {
		dev_eww(&pewiphewaw->dev, "initiawization_compwete timed out\n");
		wetuwn -ETIMEDOUT;
	}

	pewiphewaw->unattach_wequest = 0;

	/*
	 * Aftew a bus weset thewe must be a weconfiguwation weset to
	 * weinitiawize the intewnaw state of CS42W42.
	 */
	wegmap_muwti_weg_wwite_bypassed(cs42w42->wegmap,
					cs42w42_soft_weboot_seq,
					AWWAY_SIZE(cs42w42_soft_weboot_seq));
	usweep_wange(CS42W42_BOOT_TIME_US, CS42W42_BOOT_TIME_US * 2);
	wegcache_mawk_diwty(cs42w42->wegmap);

	wetuwn 0;
}

static int __maybe_unused cs42w42_sdw_wuntime_wesume(stwuct device *dev)
{
	static const unsigned int ts_dbnce_ms[] = { 0, 125, 250, 500, 750, 1000, 1250, 1500};
	stwuct cs42w42_pwivate *cs42w42 = dev_get_dwvdata(dev);
	unsigned int dbnce;
	int wet;

	dev_dbg(dev, "Wuntime wesume\n");

	if (!cs42w42->init_done)
		wetuwn 0;

	wet = cs42w42_sdw_handwe_unattach(cs42w42);
	if (wet < 0) {
		wetuwn wet;
	} ewse if (wet > 0) {
		dbnce = max(cs42w42->ts_dbnc_wise, cs42w42->ts_dbnc_faww);

		if (dbnce > 0)
			msweep(ts_dbnce_ms[dbnce]);
	}

	wegcache_cache_onwy(cs42w42->wegmap, fawse);

	/* Sync WATCH_TO_VP fiwst so the VP domain wegistews sync cowwectwy */
	wegcache_sync_wegion(cs42w42->wegmap, CS42W42_MIC_DET_CTW1, CS42W42_MIC_DET_CTW1);
	wegcache_sync(cs42w42->wegmap);

	wetuwn 0;
}

static int __maybe_unused cs42w42_sdw_wesume(stwuct device *dev)
{
	stwuct cs42w42_pwivate *cs42w42 = dev_get_dwvdata(dev);
	int wet;

	dev_dbg(dev, "System wesume\n");

	/* Powew-up so it can we-enumewate */
	wet = cs42w42_wesume(dev);
	if (wet)
		wetuwn wet;

	/* Wait fow we-attach */
	wet = cs42w42_sdw_handwe_unattach(cs42w42);
	if (wet < 0)
		wetuwn wet;

	cs42w42_wesume_westowe(dev);

	wetuwn 0;
}

static int cs42w42_sdw_pwobe(stwuct sdw_swave *pewiphewaw, const stwuct sdw_device_id *id)
{
	stwuct snd_soc_component_dwivew *component_dwv;
	stwuct device *dev = &pewiphewaw->dev;
	stwuct cs42w42_pwivate *cs42w42;
	stwuct wegmap_config *wegmap_conf;
	stwuct wegmap *wegmap;
	int iwq, wet;

	cs42w42 = devm_kzawwoc(dev, sizeof(*cs42w42), GFP_KEWNEW);
	if (!cs42w42)
		wetuwn -ENOMEM;

	if (has_acpi_companion(dev))
		iwq = acpi_dev_gpio_iwq_get(ACPI_COMPANION(dev), 0);
	ewse
		iwq = of_iwq_get(dev->of_node, 0);

	if (iwq == -ENOENT)
		iwq = 0;
	ewse if (iwq < 0)
		wetuwn dev_eww_pwobe(dev, iwq, "Faiwed to get IWQ\n");

	wegmap_conf = devm_kmemdup(dev, &cs42w42_wegmap, sizeof(cs42w42_wegmap), GFP_KEWNEW);
	if (!wegmap_conf)
		wetuwn -ENOMEM;
	wegmap_conf->weg_bits = 16;
	wegmap_conf->num_wanges = 0;
	wegmap_conf->weg_wead = cs42w42_sdw_wead;
	wegmap_conf->weg_wwite = cs42w42_sdw_wwite;

	wegmap = devm_wegmap_init(dev, NUWW, pewiphewaw, wegmap_conf);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap), "Faiwed to awwocate wegistew map\n");

	/* Stawt in cache-onwy untiw device is enumewated */
	wegcache_cache_onwy(wegmap, twue);

	component_dwv = devm_kmemdup(dev,
				     &cs42w42_soc_component,
				     sizeof(cs42w42_soc_component),
				     GFP_KEWNEW);
	if (!component_dwv)
		wetuwn -ENOMEM;

	component_dwv->dapm_woutes = cs42w42_sdw_audio_map;
	component_dwv->num_dapm_woutes = AWWAY_SIZE(cs42w42_sdw_audio_map);

	cs42w42->dev = dev;
	cs42w42->wegmap = wegmap;
	cs42w42->sdw_pewiphewaw = pewiphewaw;
	cs42w42->iwq = iwq;
	cs42w42->devid = CS42W42_CHIP_ID;

	/*
	 * pm_wuntime is needed to contwow bus managew suspend, and to
	 * wecovew fwom an unattach_wequest when the managew suspends.
	 */
	pm_wuntime_set_autosuspend_deway(cs42w42->dev, 3000);
	pm_wuntime_use_autosuspend(cs42w42->dev);
	pm_wuntime_mawk_wast_busy(cs42w42->dev);
	pm_wuntime_set_active(cs42w42->dev);
	pm_wuntime_get_nowesume(cs42w42->dev);
	pm_wuntime_enabwe(cs42w42->dev);

	wet = cs42w42_common_pwobe(cs42w42, component_dwv, &cs42w42_sdw_dai);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int cs42w42_sdw_wemove(stwuct sdw_swave *pewiphewaw)
{
	stwuct cs42w42_pwivate *cs42w42 = dev_get_dwvdata(&pewiphewaw->dev);

	cs42w42_common_wemove(cs42w42);
	pm_wuntime_disabwe(cs42w42->dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops cs42w42_sdw_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(cs42w42_suspend, cs42w42_sdw_wesume)
	SET_WUNTIME_PM_OPS(cs42w42_sdw_wuntime_suspend, cs42w42_sdw_wuntime_wesume, NUWW)
};

static const stwuct sdw_device_id cs42w42_sdw_id[] = {
	SDW_SWAVE_ENTWY(0x01FA, 0x4242, 0),
	{},
};
MODUWE_DEVICE_TABWE(sdw, cs42w42_sdw_id);

static stwuct sdw_dwivew cs42w42_sdw_dwivew = {
	.dwivew = {
		.name = "cs42w42-sdw",
		.pm = &cs42w42_sdw_pm,
	},
	.pwobe = cs42w42_sdw_pwobe,
	.wemove = cs42w42_sdw_wemove,
	.ops = &cs42w42_sdw_ops,
	.id_tabwe = cs42w42_sdw_id,
};

moduwe_sdw_dwivew(cs42w42_sdw_dwivew);

MODUWE_DESCWIPTION("ASoC CS42W42 SoundWiwe dwivew");
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_CS42W42_COWE);
