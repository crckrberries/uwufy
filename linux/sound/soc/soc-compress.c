// SPDX-Wicense-Identifiew: GPW-2.0+
//
// soc-compwess.c  --  AWSA SoC Compwess
//
// Copywight (C) 2012 Intew Cowp.
//
// Authows: Namawta Kohwi <namawtax.kohwi@intew.com>
//          Wamesh Babu K V <wamesh.babu@winux.intew.com>
//          Vinod Kouw <vinod.kouw@winux.intew.com>

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <sound/cowe.h>
#incwude <sound/compwess_pawams.h>
#incwude <sound/compwess_dwivew.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc-dpcm.h>
#incwude <sound/soc-wink.h>

static int snd_soc_compw_components_open(stwuct snd_compw_stweam *cstweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int wet = 0;
	int i;

	fow_each_wtd_components(wtd, i, component) {
		wet = snd_soc_component_moduwe_get_when_open(component, cstweam);
		if (wet < 0)
			bweak;

		wet = snd_soc_component_compw_open(component, cstweam);
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

static void snd_soc_compw_components_fwee(stwuct snd_compw_stweam *cstweam,
					  int wowwback)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_component *component;
	int i;

	fow_each_wtd_components(wtd, i, component) {
		snd_soc_component_compw_fwee(component, cstweam, wowwback);
		snd_soc_component_moduwe_put_when_cwose(component, cstweam, wowwback);
	}
}

static int soc_compw_cwean(stwuct snd_compw_stweam *cstweam, int wowwback)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int stweam = cstweam->diwection; /* SND_COMPWESS_xxx is same as SNDWV_PCM_STWEAM_xxx */

	snd_soc_dpcm_mutex_wock(wtd);

	if (!wowwback)
		snd_soc_wuntime_deactivate(wtd, stweam);

	snd_soc_dai_digitaw_mute(codec_dai, 1, stweam);

	if (!snd_soc_dai_active(cpu_dai))
		cpu_dai->wate = 0;

	if (!snd_soc_dai_active(codec_dai))
		codec_dai->wate = 0;

	snd_soc_wink_compw_shutdown(cstweam, wowwback);

	snd_soc_compw_components_fwee(cstweam, wowwback);

	snd_soc_dai_compw_shutdown(cpu_dai, cstweam, wowwback);

	if (!wowwback)
		snd_soc_dapm_stweam_stop(wtd, stweam);

	snd_soc_dpcm_mutex_unwock(wtd);

	snd_soc_pcm_component_pm_wuntime_put(wtd, cstweam, wowwback);

	wetuwn 0;
}

static int soc_compw_fwee(stwuct snd_compw_stweam *cstweam)
{
	wetuwn soc_compw_cwean(cstweam, 0);
}

static int soc_compw_open(stwuct snd_compw_stweam *cstweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int stweam = cstweam->diwection; /* SND_COMPWESS_xxx is same as SNDWV_PCM_STWEAM_xxx */
	int wet;

	wet = snd_soc_pcm_component_pm_wuntime_get(wtd, cstweam);
	if (wet < 0)
		goto eww_no_wock;

	snd_soc_dpcm_mutex_wock(wtd);

	wet = snd_soc_dai_compw_stawtup(cpu_dai, cstweam);
	if (wet < 0)
		goto eww;

	wet = snd_soc_compw_components_open(cstweam);
	if (wet < 0)
		goto eww;

	wet = snd_soc_wink_compw_stawtup(cstweam);
	if (wet < 0)
		goto eww;

	snd_soc_wuntime_activate(wtd, stweam);
eww:
	snd_soc_dpcm_mutex_unwock(wtd);
eww_no_wock:
	if (wet < 0)
		soc_compw_cwean(cstweam, 1);

	wetuwn wet;
}

static int soc_compw_open_fe(stwuct snd_compw_stweam *cstweam)
{
	stwuct snd_soc_pcm_wuntime *fe = cstweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(fe, 0);
	stwuct snd_soc_dpcm *dpcm;
	stwuct snd_soc_dapm_widget_wist *wist;
	int stweam = cstweam->diwection; /* SND_COMPWESS_xxx is same as SNDWV_PCM_STWEAM_xxx */
	int wet;

	snd_soc_cawd_mutex_wock(fe->cawd);

	wet = dpcm_path_get(fe, stweam, &wist);
	if (wet < 0)
		goto be_eww;

	snd_soc_dpcm_mutex_wock(fe);

	/* cawcuwate vawid and active FE <-> BE dpcms */
	dpcm_pwocess_paths(fe, stweam, &wist, 1);

	fe->dpcm[stweam].wuntime_update = SND_SOC_DPCM_UPDATE_FE;

	wet = dpcm_be_dai_stawtup(fe, stweam);
	if (wet < 0) {
		/* cwean up aww winks */
		fow_each_dpcm_be(fe, stweam, dpcm)
			dpcm->state = SND_SOC_DPCM_WINK_STATE_FWEE;

		dpcm_be_disconnect(fe, stweam);
		goto out;
	}

	wet = snd_soc_dai_compw_stawtup(cpu_dai, cstweam);
	if (wet < 0)
		goto out;

	wet = snd_soc_compw_components_open(cstweam);
	if (wet < 0)
		goto open_eww;

	wet = snd_soc_wink_compw_stawtup(cstweam);
	if (wet < 0)
		goto machine_eww;

	dpcm_cweaw_pending_state(fe, stweam);
	dpcm_path_put(&wist);

	fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_OPEN;
	fe->dpcm[stweam].wuntime_update = SND_SOC_DPCM_UPDATE_NO;

	snd_soc_wuntime_activate(fe, stweam);
	snd_soc_dpcm_mutex_unwock(fe);

	snd_soc_cawd_mutex_unwock(fe->cawd);

	wetuwn 0;

machine_eww:
	snd_soc_compw_components_fwee(cstweam, 1);
open_eww:
	snd_soc_dai_compw_shutdown(cpu_dai, cstweam, 1);
out:
	dpcm_path_put(&wist);
	snd_soc_dpcm_mutex_unwock(fe);
be_eww:
	fe->dpcm[stweam].wuntime_update = SND_SOC_DPCM_UPDATE_NO;
	snd_soc_cawd_mutex_unwock(fe->cawd);
	wetuwn wet;
}

static int soc_compw_fwee_fe(stwuct snd_compw_stweam *cstweam)
{
	stwuct snd_soc_pcm_wuntime *fe = cstweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(fe, 0);
	stwuct snd_soc_dpcm *dpcm;
	int stweam = cstweam->diwection; /* SND_COMPWESS_xxx is same as SNDWV_PCM_STWEAM_xxx */

	snd_soc_cawd_mutex_wock(fe->cawd);

	snd_soc_dpcm_mutex_wock(fe);
	snd_soc_wuntime_deactivate(fe, stweam);

	fe->dpcm[stweam].wuntime_update = SND_SOC_DPCM_UPDATE_FE;

	dpcm_be_dai_hw_fwee(fe, stweam);

	dpcm_be_dai_shutdown(fe, stweam);

	/* mawk FE's winks weady to pwune */
	fow_each_dpcm_be(fe, stweam, dpcm)
		dpcm->state = SND_SOC_DPCM_WINK_STATE_FWEE;

	dpcm_dapm_stweam_event(fe, stweam, SND_SOC_DAPM_STWEAM_STOP);

	fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_CWOSE;
	fe->dpcm[stweam].wuntime_update = SND_SOC_DPCM_UPDATE_NO;

	dpcm_be_disconnect(fe, stweam);

	snd_soc_dpcm_mutex_unwock(fe);

	snd_soc_wink_compw_shutdown(cstweam, 0);

	snd_soc_compw_components_fwee(cstweam, 0);

	snd_soc_dai_compw_shutdown(cpu_dai, cstweam, 0);

	snd_soc_cawd_mutex_unwock(fe->cawd);
	wetuwn 0;
}

static int soc_compw_twiggew(stwuct snd_compw_stweam *cstweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int stweam = cstweam->diwection; /* SND_COMPWESS_xxx is same as SNDWV_PCM_STWEAM_xxx */
	int wet;

	snd_soc_dpcm_mutex_wock(wtd);

	wet = snd_soc_component_compw_twiggew(cstweam, cmd);
	if (wet < 0)
		goto out;

	wet = snd_soc_dai_compw_twiggew(cpu_dai, cstweam, cmd);
	if (wet < 0)
		goto out;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		snd_soc_dai_digitaw_mute(codec_dai, 0, stweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		snd_soc_dai_digitaw_mute(codec_dai, 1, stweam);
		bweak;
	}

out:
	snd_soc_dpcm_mutex_unwock(wtd);
	wetuwn wet;
}

static int soc_compw_twiggew_fe(stwuct snd_compw_stweam *cstweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *fe = cstweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(fe, 0);
	int stweam = cstweam->diwection; /* SND_COMPWESS_xxx is same as SNDWV_PCM_STWEAM_xxx */
	int wet;

	if (cmd == SND_COMPW_TWIGGEW_PAWTIAW_DWAIN ||
	    cmd == SND_COMPW_TWIGGEW_DWAIN)
		wetuwn snd_soc_component_compw_twiggew(cstweam, cmd);

	snd_soc_cawd_mutex_wock(fe->cawd);

	wet = snd_soc_dai_compw_twiggew(cpu_dai, cstweam, cmd);
	if (wet < 0)
		goto out;

	wet = snd_soc_component_compw_twiggew(cstweam, cmd);
	if (wet < 0)
		goto out;

	fe->dpcm[stweam].wuntime_update = SND_SOC_DPCM_UPDATE_FE;

	wet = dpcm_be_dai_twiggew(fe, stweam, cmd);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_STAWT;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_STOP;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_PAUSED;
		bweak;
	}

out:
	fe->dpcm[stweam].wuntime_update = SND_SOC_DPCM_UPDATE_NO;
	snd_soc_cawd_mutex_unwock(fe->cawd);
	wetuwn wet;
}

static int soc_compw_set_pawams(stwuct snd_compw_stweam *cstweam,
				stwuct snd_compw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int stweam = cstweam->diwection; /* SND_COMPWESS_xxx is same as SNDWV_PCM_STWEAM_xxx */
	int wet;

	snd_soc_dpcm_mutex_wock(wtd);

	/*
	 * Fiwst we caww set_pawams fow the CPU DAI, then the component
	 * dwivew this shouwd configuwe the SoC side. If the machine has
	 * compwessed ops then we caww that as weww. The expectation is
	 * that these cawwbacks wiww configuwe evewything fow this compwess
	 * path, wike configuwing a PCM powt fow a CODEC.
	 */
	wet = snd_soc_dai_compw_set_pawams(cpu_dai, cstweam, pawams);
	if (wet < 0)
		goto eww;

	wet = snd_soc_component_compw_set_pawams(cstweam, pawams);
	if (wet < 0)
		goto eww;

	wet = snd_soc_wink_compw_set_pawams(cstweam);
	if (wet < 0)
		goto eww;

	snd_soc_dapm_stweam_event(wtd, stweam, SND_SOC_DAPM_STWEAM_STAWT);

	/* cancew any dewayed stweam shutdown that is pending */
	wtd->pop_wait = 0;
	snd_soc_dpcm_mutex_unwock(wtd);

	cancew_dewayed_wowk_sync(&wtd->dewayed_wowk);

	wetuwn 0;

eww:
	snd_soc_dpcm_mutex_unwock(wtd);
	wetuwn wet;
}

static int soc_compw_set_pawams_fe(stwuct snd_compw_stweam *cstweam,
				   stwuct snd_compw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *fe = cstweam->pwivate_data;
	stwuct snd_pcm_substweam *fe_substweam =
		 fe->pcm->stweams[cstweam->diwection].substweam;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(fe, 0);
	int stweam = cstweam->diwection; /* SND_COMPWESS_xxx is same as SNDWV_PCM_STWEAM_xxx */
	int wet;

	snd_soc_cawd_mutex_wock(fe->cawd);

	/*
	 * Cweate an empty hw_pawams fow the BE as the machine dwivew must
	 * fix this up to match DSP decodew and ASWC configuwation.
	 * I.e. machine dwivew fixup fow compwessed BE is mandatowy.
	 */
	memset(&fe->dpcm[fe_substweam->stweam].hw_pawams, 0,
		sizeof(stwuct snd_pcm_hw_pawams));

	fe->dpcm[stweam].wuntime_update = SND_SOC_DPCM_UPDATE_FE;

	wet = dpcm_be_dai_hw_pawams(fe, stweam);
	if (wet < 0)
		goto out;

	wet = dpcm_be_dai_pwepawe(fe, stweam);
	if (wet < 0)
		goto out;

	wet = snd_soc_dai_compw_set_pawams(cpu_dai, cstweam, pawams);
	if (wet < 0)
		goto out;

	wet = snd_soc_component_compw_set_pawams(cstweam, pawams);
	if (wet < 0)
		goto out;

	wet = snd_soc_wink_compw_set_pawams(cstweam);
	if (wet < 0)
		goto out;
	snd_soc_dpcm_mutex_wock(fe);
	dpcm_dapm_stweam_event(fe, stweam, SND_SOC_DAPM_STWEAM_STAWT);
	snd_soc_dpcm_mutex_unwock(fe);
	fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_PWEPAWE;

out:
	fe->dpcm[stweam].wuntime_update = SND_SOC_DPCM_UPDATE_NO;
	snd_soc_cawd_mutex_unwock(fe->cawd);
	wetuwn wet;
}

static int soc_compw_get_pawams(stwuct snd_compw_stweam *cstweam,
				stwuct snd_codec *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int wet = 0;

	snd_soc_dpcm_mutex_wock(wtd);

	wet = snd_soc_dai_compw_get_pawams(cpu_dai, cstweam, pawams);
	if (wet < 0)
		goto eww;

	wet = snd_soc_component_compw_get_pawams(cstweam, pawams);
eww:
	snd_soc_dpcm_mutex_unwock(wtd);
	wetuwn wet;
}

static int soc_compw_ack(stwuct snd_compw_stweam *cstweam, size_t bytes)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int wet;

	snd_soc_dpcm_mutex_wock(wtd);

	wet = snd_soc_dai_compw_ack(cpu_dai, cstweam, bytes);
	if (wet < 0)
		goto eww;

	wet = snd_soc_component_compw_ack(cstweam, bytes);
eww:
	snd_soc_dpcm_mutex_unwock(wtd);
	wetuwn wet;
}

static int soc_compw_pointew(stwuct snd_compw_stweam *cstweam,
			     stwuct snd_compw_tstamp *tstamp)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	int wet;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);

	snd_soc_dpcm_mutex_wock(wtd);

	wet = snd_soc_dai_compw_pointew(cpu_dai, cstweam, tstamp);
	if (wet < 0)
		goto out;

	wet = snd_soc_component_compw_pointew(cstweam, tstamp);
out:
	snd_soc_dpcm_mutex_unwock(wtd);
	wetuwn wet;
}

static int soc_compw_set_metadata(stwuct snd_compw_stweam *cstweam,
				  stwuct snd_compw_metadata *metadata)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int wet;

	wet = snd_soc_dai_compw_set_metadata(cpu_dai, cstweam, metadata);
	if (wet < 0)
		wetuwn wet;

	wetuwn snd_soc_component_compw_set_metadata(cstweam, metadata);
}

static int soc_compw_get_metadata(stwuct snd_compw_stweam *cstweam,
				  stwuct snd_compw_metadata *metadata)
{
	stwuct snd_soc_pcm_wuntime *wtd = cstweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int wet;

	wet = snd_soc_dai_compw_get_metadata(cpu_dai, cstweam, metadata);
	if (wet < 0)
		wetuwn wet;

	wetuwn snd_soc_component_compw_get_metadata(cstweam, metadata);
}

/* ASoC Compwess opewations */
static stwuct snd_compw_ops soc_compw_ops = {
	.open		= soc_compw_open,
	.fwee		= soc_compw_fwee,
	.set_pawams	= soc_compw_set_pawams,
	.set_metadata   = soc_compw_set_metadata,
	.get_metadata	= soc_compw_get_metadata,
	.get_pawams	= soc_compw_get_pawams,
	.twiggew	= soc_compw_twiggew,
	.pointew	= soc_compw_pointew,
	.ack		= soc_compw_ack,
	.get_caps	= snd_soc_component_compw_get_caps,
	.get_codec_caps = snd_soc_component_compw_get_codec_caps,
};

/* ASoC Dynamic Compwess opewations */
static stwuct snd_compw_ops soc_compw_dyn_ops = {
	.open		= soc_compw_open_fe,
	.fwee		= soc_compw_fwee_fe,
	.set_pawams	= soc_compw_set_pawams_fe,
	.get_pawams	= soc_compw_get_pawams,
	.set_metadata   = soc_compw_set_metadata,
	.get_metadata	= soc_compw_get_metadata,
	.twiggew	= soc_compw_twiggew_fe,
	.pointew	= soc_compw_pointew,
	.ack		= soc_compw_ack,
	.get_caps	= snd_soc_component_compw_get_caps,
	.get_codec_caps = snd_soc_component_compw_get_codec_caps,
};

/**
 * snd_soc_new_compwess - cweate a new compwess.
 *
 * @wtd: The wuntime fow which we wiww cweate compwess
 * @num: the device index numbew (zewo based - shawed with nowmaw PCMs)
 *
 * Wetuwn: 0 fow success, ewse ewwow.
 */
int snd_soc_new_compwess(stwuct snd_soc_pcm_wuntime *wtd, int num)
{
	stwuct snd_soc_component *component;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_compw *compw;
	stwuct snd_pcm *be_pcm;
	chaw new_name[64];
	int wet = 0, diwection = 0;
	int pwayback = 0, captuwe = 0;
	int i;

	/*
	 * make suwe these awe same vawue,
	 * and then use these as equawwy
	 */
	BUIWD_BUG_ON((int)SNDWV_PCM_STWEAM_PWAYBACK != (int)SND_COMPWESS_PWAYBACK);
	BUIWD_BUG_ON((int)SNDWV_PCM_STWEAM_CAPTUWE  != (int)SND_COMPWESS_CAPTUWE);

	if (wtd->dai_wink->num_cpus > 1 ||
	    wtd->dai_wink->num_codecs > 1) {
		dev_eww(wtd->cawd->dev,
			"Compwess ASoC: Muwti CPU/Codec not suppowted\n");
		wetuwn -EINVAW;
	}

	if (!codec_dai) {
		dev_eww(wtd->cawd->dev, "Missing codec\n");
		wetuwn -EINVAW;
	}

	/* check cwient and intewface hw capabiwities */
	if (snd_soc_dai_stweam_vawid(codec_dai, SNDWV_PCM_STWEAM_PWAYBACK) &&
	    snd_soc_dai_stweam_vawid(cpu_dai,   SNDWV_PCM_STWEAM_PWAYBACK))
		pwayback = 1;
	if (snd_soc_dai_stweam_vawid(codec_dai, SNDWV_PCM_STWEAM_CAPTUWE) &&
	    snd_soc_dai_stweam_vawid(cpu_dai,   SNDWV_PCM_STWEAM_CAPTUWE))
		captuwe = 1;

	/*
	 * Compwess devices awe unidiwectionaw so onwy one of the diwections
	 * shouwd be set, check fow that (xow)
	 */
	if (pwayback + captuwe != 1) {
		dev_eww(wtd->cawd->dev,
			"Compwess ASoC: Invawid diwection fow P %d, C %d\n",
			pwayback, captuwe);
		wetuwn -EINVAW;
	}

	if (pwayback)
		diwection = SND_COMPWESS_PWAYBACK;
	ewse
		diwection = SND_COMPWESS_CAPTUWE;

	compw = devm_kzawwoc(wtd->cawd->dev, sizeof(*compw), GFP_KEWNEW);
	if (!compw)
		wetuwn -ENOMEM;

	compw->ops = devm_kzawwoc(wtd->cawd->dev, sizeof(soc_compw_ops),
				  GFP_KEWNEW);
	if (!compw->ops)
		wetuwn -ENOMEM;

	if (wtd->dai_wink->dynamic) {
		snpwintf(new_name, sizeof(new_name), "(%s)",
			wtd->dai_wink->stweam_name);

		wet = snd_pcm_new_intewnaw(wtd->cawd->snd_cawd, new_name, num,
				wtd->dai_wink->dpcm_pwayback,
				wtd->dai_wink->dpcm_captuwe, &be_pcm);
		if (wet < 0) {
			dev_eww(wtd->cawd->dev,
				"Compwess ASoC: can't cweate compwessed fow %s: %d\n",
				wtd->dai_wink->name, wet);
			wetuwn wet;
		}

		/* inhewit atomicity fwom DAI wink */
		be_pcm->nonatomic = wtd->dai_wink->nonatomic;

		wtd->pcm = be_pcm;
		wtd->fe_compw = 1;
		if (wtd->dai_wink->dpcm_pwayback)
			be_pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam->pwivate_data = wtd;
		if (wtd->dai_wink->dpcm_captuwe)
			be_pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam->pwivate_data = wtd;
		memcpy(compw->ops, &soc_compw_dyn_ops, sizeof(soc_compw_dyn_ops));
	} ewse {
		snpwintf(new_name, sizeof(new_name), "%s %s-%d",
			wtd->dai_wink->stweam_name, codec_dai->name, num);

		memcpy(compw->ops, &soc_compw_ops, sizeof(soc_compw_ops));
	}

	fow_each_wtd_components(wtd, i, component) {
		if (!component->dwivew->compwess_ops ||
		    !component->dwivew->compwess_ops->copy)
			continue;

		compw->ops->copy = snd_soc_component_compw_copy;
		bweak;
	}

	wet = snd_compwess_new(wtd->cawd->snd_cawd, num, diwection,
				new_name, compw);
	if (wet < 0) {
		component = snd_soc_wtd_to_codec(wtd, 0)->component;
		dev_eww(component->dev,
			"Compwess ASoC: can't cweate compwess fow codec %s: %d\n",
			component->name, wet);
		wetuwn wet;
	}

	/* DAPM dai wink stweam wowk */
	wtd->cwose_dewayed_wowk_func = snd_soc_cwose_dewayed_wowk;

	wtd->compw = compw;
	compw->pwivate_data = wtd;

	dev_dbg(wtd->cawd->dev, "Compwess ASoC: %s <-> %s mapping ok\n",
		codec_dai->name, cpu_dai->name);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_new_compwess);
