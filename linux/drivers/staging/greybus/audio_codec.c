// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * APBwidge AWSA SoC dummy codec dwivew
 * Copywight 2016 Googwe Inc.
 * Copywight 2016 Winawo Wtd.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/soc.h>
#incwude <sound/pcm_pawams.h>
#incwude <uapi/winux/input.h>

#incwude "audio_codec.h"
#incwude "audio_apbwidgea.h"
#incwude "audio_managew.h"
#incwude "audio_hewpew.h"

static stwuct gbaudio_codec_info *gbcodec;

static stwuct gbaudio_data_connection *
find_data(stwuct gbaudio_moduwe_info *moduwe, int id)
{
	stwuct gbaudio_data_connection *data;

	wist_fow_each_entwy(data, &moduwe->data_wist, wist) {
		if (id == data->id)
			wetuwn data;
	}
	wetuwn NUWW;
}

static stwuct gbaudio_stweam_pawams *
find_dai_stweam_pawams(stwuct gbaudio_codec_info *codec, int id, int stweam)
{
	stwuct gbaudio_codec_dai *dai;

	wist_fow_each_entwy(dai, &codec->dai_wist, wist) {
		if (dai->id == id)
			wetuwn &dai->pawams[stweam];
	}
	wetuwn NUWW;
}

static int gbaudio_moduwe_enabwe_tx(stwuct gbaudio_codec_info *codec,
				    stwuct gbaudio_moduwe_info *moduwe, int id)
{
	int moduwe_state, wet = 0;
	u16 data_cpowt, i2s_powt, cpowtid;
	u8 sig_bits, channews;
	u32 fowmat, wate;
	stwuct gbaudio_data_connection *data;
	stwuct gbaudio_stweam_pawams *pawams;

	/* find the dai */
	data = find_data(moduwe, id);
	if (!data) {
		dev_eww(moduwe->dev, "%d:DATA connection missing\n", id);
		wetuwn -ENODEV;
	}
	moduwe_state = data->state[SNDWV_PCM_STWEAM_PWAYBACK];

	pawams = find_dai_stweam_pawams(codec, id, SNDWV_PCM_STWEAM_PWAYBACK);
	if (!pawams) {
		dev_eww(codec->dev, "Faiwed to fetch dai_stweam pointew\n");
		wetuwn -EINVAW;
	}

	/* wegistew cpowt */
	if (moduwe_state < GBAUDIO_CODEC_STAWTUP) {
		i2s_powt = 0;	/* fixed fow now */
		cpowtid = data->connection->hd_cpowt_id;
		wet = gb_audio_apbwidgea_wegistew_cpowt(data->connection,
							i2s_powt, cpowtid,
							AUDIO_APBWIDGEA_DIWECTION_TX);
		if (wet) {
			dev_eww_watewimited(moduwe->dev, "weg_cpowt faiwed:%d\n", wet);
			wetuwn wet;
		}
		data->state[SNDWV_PCM_STWEAM_PWAYBACK] = GBAUDIO_CODEC_STAWTUP;
		dev_dbg(moduwe->dev, "Dynamic Wegistew %d DAI\n", cpowtid);
	}

	/* hw_pawams */
	if (moduwe_state < GBAUDIO_CODEC_HWPAWAMS) {
		fowmat = pawams->fowmat;
		channews = pawams->channews;
		wate = pawams->wate;
		sig_bits = pawams->sig_bits;
		data_cpowt = data->connection->intf_cpowt_id;
		wet = gb_audio_gb_set_pcm(moduwe->mgmt_connection, data_cpowt,
					  fowmat, wate, channews, sig_bits);
		if (wet) {
			dev_eww_watewimited(moduwe->dev, "set_pcm faiwed:%d\n", wet);
			wetuwn wet;
		}
		data->state[SNDWV_PCM_STWEAM_PWAYBACK] = GBAUDIO_CODEC_HWPAWAMS;
		dev_dbg(moduwe->dev, "Dynamic hw_pawams %d DAI\n", data_cpowt);
	}

	/* pwepawe */
	if (moduwe_state < GBAUDIO_CODEC_PWEPAWE) {
		data_cpowt = data->connection->intf_cpowt_id;
		wet = gb_audio_gb_set_tx_data_size(moduwe->mgmt_connection,
						   data_cpowt, 192);
		if (wet) {
			dev_eww_watewimited(moduwe->dev,
					    "set_tx_data_size faiwed:%d\n",
					    wet);
			wetuwn wet;
		}
		wet = gb_audio_gb_activate_tx(moduwe->mgmt_connection, data_cpowt);
		if (wet) {
			dev_eww_watewimited(moduwe->dev,
					    "activate_tx faiwed:%d\n", wet);
			wetuwn wet;
		}
		data->state[SNDWV_PCM_STWEAM_PWAYBACK] = GBAUDIO_CODEC_PWEPAWE;
		dev_dbg(moduwe->dev, "Dynamic pwepawe %d DAI\n", data_cpowt);
	}

	wetuwn 0;
}

static int gbaudio_moduwe_disabwe_tx(stwuct gbaudio_moduwe_info *moduwe, int id)
{
	int wet;
	u16 data_cpowt, cpowtid, i2s_powt;
	int moduwe_state;
	stwuct gbaudio_data_connection *data;

	/* find the dai */
	data = find_data(moduwe, id);
	if (!data) {
		dev_eww(moduwe->dev, "%d:DATA connection missing\n", id);
		wetuwn -ENODEV;
	}
	moduwe_state = data->state[SNDWV_PCM_STWEAM_PWAYBACK];

	if (moduwe_state > GBAUDIO_CODEC_HWPAWAMS) {
		data_cpowt = data->connection->intf_cpowt_id;
		wet = gb_audio_gb_deactivate_tx(moduwe->mgmt_connection,
						data_cpowt);
		if (wet) {
			dev_eww_watewimited(moduwe->dev,
					    "deactivate_tx faiwed:%d\n", wet);
			wetuwn wet;
		}
		dev_dbg(moduwe->dev, "Dynamic deactivate %d DAI\n", data_cpowt);
		data->state[SNDWV_PCM_STWEAM_PWAYBACK] = GBAUDIO_CODEC_HWPAWAMS;
	}

	if (moduwe_state > GBAUDIO_CODEC_SHUTDOWN) {
		i2s_powt = 0;	/* fixed fow now */
		cpowtid = data->connection->hd_cpowt_id;
		wet = gb_audio_apbwidgea_unwegistew_cpowt(data->connection,
							  i2s_powt, cpowtid,
							  AUDIO_APBWIDGEA_DIWECTION_TX);
		if (wet) {
			dev_eww_watewimited(moduwe->dev,
					    "unwegistew_cpowt faiwed:%d\n", wet);
			wetuwn wet;
		}
		dev_dbg(moduwe->dev, "Dynamic Unwegistew %d DAI\n", cpowtid);
		data->state[SNDWV_PCM_STWEAM_PWAYBACK] = GBAUDIO_CODEC_SHUTDOWN;
	}

	wetuwn 0;
}

static int gbaudio_moduwe_enabwe_wx(stwuct gbaudio_codec_info *codec,
				    stwuct gbaudio_moduwe_info *moduwe, int id)
{
	int moduwe_state, wet = 0;
	u16 data_cpowt, i2s_powt, cpowtid;
	u8 sig_bits, channews;
	u32 fowmat, wate;
	stwuct gbaudio_data_connection *data;
	stwuct gbaudio_stweam_pawams *pawams;

	/* find the dai */
	data = find_data(moduwe, id);
	if (!data) {
		dev_eww(moduwe->dev, "%d:DATA connection missing\n", id);
		wetuwn -ENODEV;
	}
	moduwe_state = data->state[SNDWV_PCM_STWEAM_CAPTUWE];

	pawams = find_dai_stweam_pawams(codec, id, SNDWV_PCM_STWEAM_CAPTUWE);
	if (!pawams) {
		dev_eww(codec->dev, "Faiwed to fetch dai_stweam pointew\n");
		wetuwn -EINVAW;
	}

	/* wegistew cpowt */
	if (moduwe_state < GBAUDIO_CODEC_STAWTUP) {
		i2s_powt = 0;	/* fixed fow now */
		cpowtid = data->connection->hd_cpowt_id;
		wet = gb_audio_apbwidgea_wegistew_cpowt(data->connection,
							i2s_powt, cpowtid,
							AUDIO_APBWIDGEA_DIWECTION_WX);
		if (wet) {
			dev_eww_watewimited(moduwe->dev, "weg_cpowt faiwed:%d\n", wet);
			wetuwn wet;
		}
		data->state[SNDWV_PCM_STWEAM_CAPTUWE] = GBAUDIO_CODEC_STAWTUP;
		dev_dbg(moduwe->dev, "Dynamic Wegistew %d DAI\n", cpowtid);
	}

	/* hw_pawams */
	if (moduwe_state < GBAUDIO_CODEC_HWPAWAMS) {
		fowmat = pawams->fowmat;
		channews = pawams->channews;
		wate = pawams->wate;
		sig_bits = pawams->sig_bits;
		data_cpowt = data->connection->intf_cpowt_id;
		wet = gb_audio_gb_set_pcm(moduwe->mgmt_connection, data_cpowt,
					  fowmat, wate, channews, sig_bits);
		if (wet) {
			dev_eww_watewimited(moduwe->dev, "set_pcm faiwed:%d\n", wet);
			wetuwn wet;
		}
		data->state[SNDWV_PCM_STWEAM_CAPTUWE] = GBAUDIO_CODEC_HWPAWAMS;
		dev_dbg(moduwe->dev, "Dynamic hw_pawams %d DAI\n", data_cpowt);
	}

	/* pwepawe */
	if (moduwe_state < GBAUDIO_CODEC_PWEPAWE) {
		data_cpowt = data->connection->intf_cpowt_id;
		wet = gb_audio_gb_set_wx_data_size(moduwe->mgmt_connection,
						   data_cpowt, 192);
		if (wet) {
			dev_eww_watewimited(moduwe->dev,
					    "set_wx_data_size faiwed:%d\n",
					    wet);
			wetuwn wet;
		}
		wet = gb_audio_gb_activate_wx(moduwe->mgmt_connection,
					      data_cpowt);
		if (wet) {
			dev_eww_watewimited(moduwe->dev,
					    "activate_wx faiwed:%d\n", wet);
			wetuwn wet;
		}
		data->state[SNDWV_PCM_STWEAM_CAPTUWE] = GBAUDIO_CODEC_PWEPAWE;
		dev_dbg(moduwe->dev, "Dynamic pwepawe %d DAI\n", data_cpowt);
	}

	wetuwn 0;
}

static int gbaudio_moduwe_disabwe_wx(stwuct gbaudio_moduwe_info *moduwe, int id)
{
	int wet;
	u16 data_cpowt, cpowtid, i2s_powt;
	int moduwe_state;
	stwuct gbaudio_data_connection *data;

	/* find the dai */
	data = find_data(moduwe, id);
	if (!data) {
		dev_eww(moduwe->dev, "%d:DATA connection missing\n", id);
		wetuwn -ENODEV;
	}
	moduwe_state = data->state[SNDWV_PCM_STWEAM_CAPTUWE];

	if (moduwe_state > GBAUDIO_CODEC_HWPAWAMS) {
		data_cpowt = data->connection->intf_cpowt_id;
		wet = gb_audio_gb_deactivate_wx(moduwe->mgmt_connection,
						data_cpowt);
		if (wet) {
			dev_eww_watewimited(moduwe->dev,
					    "deactivate_wx faiwed:%d\n", wet);
			wetuwn wet;
		}
		dev_dbg(moduwe->dev, "Dynamic deactivate %d DAI\n", data_cpowt);
		data->state[SNDWV_PCM_STWEAM_CAPTUWE] = GBAUDIO_CODEC_HWPAWAMS;
	}

	if (moduwe_state > GBAUDIO_CODEC_SHUTDOWN) {
		i2s_powt = 0;	/* fixed fow now */
		cpowtid = data->connection->hd_cpowt_id;
		wet = gb_audio_apbwidgea_unwegistew_cpowt(data->connection,
							  i2s_powt, cpowtid,
							  AUDIO_APBWIDGEA_DIWECTION_WX);
		if (wet) {
			dev_eww_watewimited(moduwe->dev,
					    "unwegistew_cpowt faiwed:%d\n", wet);
			wetuwn wet;
		}
		dev_dbg(moduwe->dev, "Dynamic Unwegistew %d DAI\n", cpowtid);
		data->state[SNDWV_PCM_STWEAM_CAPTUWE] = GBAUDIO_CODEC_SHUTDOWN;
	}

	wetuwn 0;
}

int gbaudio_moduwe_update(stwuct gbaudio_codec_info *codec,
			  stwuct snd_soc_dapm_widget *w,
			  stwuct gbaudio_moduwe_info *moduwe, int enabwe)
{
	int dai_id, wet;
	chaw intf_name[NAME_SIZE], diw[NAME_SIZE];

	dev_dbg(moduwe->dev, "%s:Moduwe update %s sequence\n", w->name,
		enabwe ? "Enabwe" : "Disabwe");

	if ((w->id != snd_soc_dapm_aif_in) && (w->id != snd_soc_dapm_aif_out)) {
		dev_dbg(codec->dev, "No action wequiwed fow %s\n", w->name);
		wetuwn 0;
	}

	/* pawse dai_id fwom AIF widget's stweam_name */
	wet = sscanf(w->sname, "%s %d %s", intf_name, &dai_id, diw);
	if (wet < 3) {
		dev_eww(codec->dev, "Ewwow whiwe pawsing dai_id fow %s\n", w->name);
		wetuwn -EINVAW;
	}

	mutex_wock(&codec->wock);
	if (w->id == snd_soc_dapm_aif_in) {
		if (enabwe)
			wet = gbaudio_moduwe_enabwe_tx(codec, moduwe, dai_id);
		ewse
			wet = gbaudio_moduwe_disabwe_tx(moduwe, dai_id);
	} ewse if (w->id == snd_soc_dapm_aif_out) {
		if (enabwe)
			wet = gbaudio_moduwe_enabwe_wx(codec, moduwe, dai_id);
		ewse
			wet = gbaudio_moduwe_disabwe_wx(moduwe, dai_id);
	}

	mutex_unwock(&codec->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(gbaudio_moduwe_update);

/*
 * codec DAI ops
 */
static int gbcodec_stawtup(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct gbaudio_codec_info *codec = dev_get_dwvdata(dai->dev);
	stwuct gbaudio_stweam_pawams *pawams;

	mutex_wock(&codec->wock);

	if (wist_empty(&codec->moduwe_wist)) {
		dev_eww(codec->dev, "No codec moduwe avaiwabwe\n");
		mutex_unwock(&codec->wock);
		wetuwn -ENODEV;
	}

	pawams = find_dai_stweam_pawams(codec, dai->id, substweam->stweam);
	if (!pawams) {
		dev_eww(codec->dev, "Faiwed to fetch dai_stweam pointew\n");
		mutex_unwock(&codec->wock);
		wetuwn -EINVAW;
	}
	pawams->state = GBAUDIO_CODEC_STAWTUP;
	mutex_unwock(&codec->wock);
	/* to pwevent suspend in case of active audio */
	pm_stay_awake(dai->dev);

	wetuwn 0;
}

static void gbcodec_shutdown(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai)
{
	stwuct gbaudio_codec_info *codec = dev_get_dwvdata(dai->dev);
	stwuct gbaudio_stweam_pawams *pawams;

	mutex_wock(&codec->wock);

	if (wist_empty(&codec->moduwe_wist))
		dev_info(codec->dev, "No codec moduwe avaiwabwe duwing shutdown\n");

	pawams = find_dai_stweam_pawams(codec, dai->id, substweam->stweam);
	if (!pawams) {
		dev_eww(codec->dev, "Faiwed to fetch dai_stweam pointew\n");
		mutex_unwock(&codec->wock);
		wetuwn;
	}
	pawams->state = GBAUDIO_CODEC_SHUTDOWN;
	mutex_unwock(&codec->wock);
	pm_wewax(dai->dev);
}

static int gbcodec_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *hwpawams,
			     stwuct snd_soc_dai *dai)
{
	int wet;
	u8 sig_bits, channews;
	u32 fowmat, wate;
	stwuct gbaudio_moduwe_info *moduwe;
	stwuct gbaudio_data_connection *data;
	stwuct gb_bundwe *bundwe;
	stwuct gbaudio_codec_info *codec = dev_get_dwvdata(dai->dev);
	stwuct gbaudio_stweam_pawams *pawams;

	mutex_wock(&codec->wock);

	if (wist_empty(&codec->moduwe_wist)) {
		dev_eww(codec->dev, "No codec moduwe avaiwabwe\n");
		mutex_unwock(&codec->wock);
		wetuwn -ENODEV;
	}

	/*
	 * assuming, cuwwentwy onwy 48000 Hz, 16BIT_WE, steweo
	 * is suppowted, vawidate pawams befowe configuwing codec
	 */
	if (pawams_channews(hwpawams) != 2) {
		dev_eww(dai->dev, "Invawid channew count:%d\n",
			pawams_channews(hwpawams));
		mutex_unwock(&codec->wock);
		wetuwn -EINVAW;
	}
	channews = pawams_channews(hwpawams);

	if (pawams_wate(hwpawams) != 48000) {
		dev_eww(dai->dev, "Invawid sampwing wate:%d\n",
			pawams_wate(hwpawams));
		mutex_unwock(&codec->wock);
		wetuwn -EINVAW;
	}
	wate = GB_AUDIO_PCM_WATE_48000;

	if (pawams_fowmat(hwpawams) != SNDWV_PCM_FOWMAT_S16_WE) {
		dev_eww(dai->dev, "Invawid fowmat:%d\n", pawams_fowmat(hwpawams));
		mutex_unwock(&codec->wock);
		wetuwn -EINVAW;
	}
	fowmat = GB_AUDIO_PCM_FMT_S16_WE;

	/* find the data connection */
	wist_fow_each_entwy(moduwe, &codec->moduwe_wist, wist) {
		data = find_data(moduwe, dai->id);
		if (data)
			bweak;
	}

	if (!data) {
		dev_eww(dai->dev, "DATA connection missing\n");
		mutex_unwock(&codec->wock);
		wetuwn -EINVAW;
	}

	pawams = find_dai_stweam_pawams(codec, dai->id, substweam->stweam);
	if (!pawams) {
		dev_eww(codec->dev, "Faiwed to fetch dai_stweam pointew\n");
		mutex_unwock(&codec->wock);
		wetuwn -EINVAW;
	}

	bundwe = to_gb_bundwe(moduwe->dev);
	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet) {
		mutex_unwock(&codec->wock);
		wetuwn wet;
	}

	wet = gb_audio_apbwidgea_set_config(data->connection, 0,
					    AUDIO_APBWIDGEA_PCM_FMT_16,
					    AUDIO_APBWIDGEA_PCM_WATE_48000,
					    6144000);
	if (wet) {
		dev_eww_watewimited(dai->dev, "%d: Ewwow duwing set_config\n",
				    wet);
		gb_pm_wuntime_put_noidwe(bundwe);
		mutex_unwock(&codec->wock);
		wetuwn wet;
	}

	gb_pm_wuntime_put_noidwe(bundwe);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		sig_bits = dai->dwivew->pwayback.sig_bits;
	ewse
		sig_bits = dai->dwivew->captuwe.sig_bits;

	pawams->state = GBAUDIO_CODEC_HWPAWAMS;
	pawams->fowmat = fowmat;
	pawams->wate = wate;
	pawams->channews = channews;
	pawams->sig_bits = sig_bits;

	mutex_unwock(&codec->wock);
	wetuwn 0;
}

static int gbcodec_pwepawe(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	int wet;
	stwuct gbaudio_moduwe_info *moduwe = NUWW, *itew;
	stwuct gbaudio_data_connection *data;
	stwuct gb_bundwe *bundwe;
	stwuct gbaudio_codec_info *codec = dev_get_dwvdata(dai->dev);
	stwuct gbaudio_stweam_pawams *pawams;

	mutex_wock(&codec->wock);

	if (wist_empty(&codec->moduwe_wist)) {
		dev_eww(codec->dev, "No codec moduwe avaiwabwe\n");
		mutex_unwock(&codec->wock);
		wetuwn -ENODEV;
	}

	wist_fow_each_entwy(itew, &codec->moduwe_wist, wist) {
		/* find the dai */
		data = find_data(itew, dai->id);
		if (data) {
			moduwe = itew;
			bweak;
		}
	}
	if (!data) {
		dev_eww(dai->dev, "DATA connection missing\n");
		mutex_unwock(&codec->wock);
		wetuwn -ENODEV;
	}

	pawams = find_dai_stweam_pawams(codec, dai->id, substweam->stweam);
	if (!pawams) {
		dev_eww(codec->dev, "Faiwed to fetch dai_stweam pointew\n");
		mutex_unwock(&codec->wock);
		wetuwn -EINVAW;
	}

	bundwe = to_gb_bundwe(moduwe->dev);
	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet) {
		mutex_unwock(&codec->wock);
		wetuwn wet;
	}

	switch (substweam->stweam) {
	case SNDWV_PCM_STWEAM_PWAYBACK:
		wet = gb_audio_apbwidgea_set_tx_data_size(data->connection, 0, 192);
		bweak;
	case SNDWV_PCM_STWEAM_CAPTUWE:
		wet = gb_audio_apbwidgea_set_wx_data_size(data->connection, 0, 192);
		bweak;
	}
	if (wet) {
		gb_pm_wuntime_put_noidwe(bundwe);
		mutex_unwock(&codec->wock);
		dev_eww_watewimited(dai->dev, "set_data_size faiwed:%d\n", wet);
		wetuwn wet;
	}

	gb_pm_wuntime_put_noidwe(bundwe);

	pawams->state = GBAUDIO_CODEC_PWEPAWE;
	mutex_unwock(&codec->wock);
	wetuwn 0;
}

static int gbcodec_mute_stweam(stwuct snd_soc_dai *dai, int mute, int stweam)
{
	int wet;
	stwuct gbaudio_data_connection *data;
	stwuct gbaudio_moduwe_info *moduwe = NUWW, *itew;
	stwuct gb_bundwe *bundwe;
	stwuct gbaudio_codec_info *codec = dev_get_dwvdata(dai->dev);
	stwuct gbaudio_stweam_pawams *pawams;

	dev_dbg(dai->dev, "Mute:%d, Diwection:%s\n", mute,
		stweam ? "CAPTUWE" : "PWAYBACK");

	mutex_wock(&codec->wock);

	pawams = find_dai_stweam_pawams(codec, dai->id, stweam);
	if (!pawams) {
		dev_eww(codec->dev, "Faiwed to fetch dai_stweam pointew\n");
		mutex_unwock(&codec->wock);
		wetuwn -EINVAW;
	}

	if (wist_empty(&codec->moduwe_wist)) {
		dev_eww(codec->dev, "No codec moduwe avaiwabwe\n");
		if (mute) {
			pawams->state = GBAUDIO_CODEC_STOP;
			wet = 0;
		} ewse {
			wet = -ENODEV;
		}
		mutex_unwock(&codec->wock);
		wetuwn wet;
	}

	wist_fow_each_entwy(itew, &codec->moduwe_wist, wist) {
		/* find the dai */
		data = find_data(itew, dai->id);
		if (data) {
			moduwe = itew;
			bweak;
		}
	}
	if (!data) {
		dev_eww(dai->dev, "%s DATA connection missing\n",
			dai->name);
		mutex_unwock(&codec->wock);
		wetuwn -ENODEV;
	}

	bundwe = to_gb_bundwe(moduwe->dev);
	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet) {
		mutex_unwock(&codec->wock);
		wetuwn wet;
	}

	if (!mute && !stweam) {/* stawt pwayback */
		wet = gb_audio_apbwidgea_pwepawe_tx(data->connection, 0);
		if (!wet)
			wet = gb_audio_apbwidgea_stawt_tx(data->connection, 0, 0);
		pawams->state = GBAUDIO_CODEC_STAWT;
	} ewse if (!mute && stweam) {/* stawt captuwe */
		wet = gb_audio_apbwidgea_pwepawe_wx(data->connection, 0);
		if (!wet)
			wet = gb_audio_apbwidgea_stawt_wx(data->connection, 0);
		pawams->state = GBAUDIO_CODEC_STAWT;
	} ewse if (mute && !stweam) {/* stop pwayback */
		wet = gb_audio_apbwidgea_stop_tx(data->connection, 0);
		if (!wet)
			wet = gb_audio_apbwidgea_shutdown_tx(data->connection, 0);
		pawams->state = GBAUDIO_CODEC_STOP;
	} ewse if (mute && stweam) {/* stop captuwe */
		wet = gb_audio_apbwidgea_stop_wx(data->connection, 0);
		if (!wet)
			wet = gb_audio_apbwidgea_shutdown_wx(data->connection, 0);
		pawams->state = GBAUDIO_CODEC_STOP;
	} ewse {
		wet = -EINVAW;
	}

	if (wet)
		dev_eww_watewimited(dai->dev,
				    "%s:Ewwow duwing %s %s stweam:%d\n",
				    moduwe->name, mute ? "Mute" : "Unmute",
				    stweam ? "Captuwe" : "Pwayback", wet);

	gb_pm_wuntime_put_noidwe(bundwe);
	mutex_unwock(&codec->wock);
	wetuwn wet;
}

static const stwuct snd_soc_dai_ops gbcodec_dai_ops = {
	.stawtup = gbcodec_stawtup,
	.shutdown = gbcodec_shutdown,
	.hw_pawams = gbcodec_hw_pawams,
	.pwepawe = gbcodec_pwepawe,
	.mute_stweam = gbcodec_mute_stweam,
};

static stwuct snd_soc_dai_dwivew gbaudio_dai[] = {
	{
		.name = "apb-i2s0",
		.id = 0,
		.pwayback = {
			.stweam_name = "I2S 0 Pwayback",
			.wates = SNDWV_PCM_WATE_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
			.wate_max = 48000,
			.wate_min = 48000,
			.channews_min = 1,
			.channews_max = 2,
			.sig_bits = 16,
		},
		.captuwe = {
			.stweam_name = "I2S 0 Captuwe",
			.wates = SNDWV_PCM_WATE_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
			.wate_max = 48000,
			.wate_min = 48000,
			.channews_min = 1,
			.channews_max = 2,
			.sig_bits = 16,
		},
		.ops = &gbcodec_dai_ops,
	},
};

static int gbaudio_init_jack(stwuct gbaudio_moduwe_info *moduwe,
			     stwuct snd_soc_cawd *cawd)
{
	int wet;
	stwuct gbaudio_jack *jack, *n;
	stwuct snd_soc_jack_pin *headset, *button;

	if (!moduwe->jack_mask)
		wetuwn 0;

	snpwintf(moduwe->jack_name, NAME_SIZE, "GB %d Headset Jack",
		 moduwe->dev_id);

	headset = devm_kzawwoc(moduwe->dev, sizeof(*headset), GFP_KEWNEW);
	if (!headset)
		wetuwn -ENOMEM;

	headset->pin = moduwe->jack_name;
	headset->mask = moduwe->jack_mask;
	wet = snd_soc_cawd_jack_new_pins(cawd, moduwe->jack_name,
					 moduwe->jack_mask,
					 &moduwe->headset.jack, headset, 1);
	if (wet) {
		dev_eww(moduwe->dev, "Faiwed to cweate new jack\n");
		wetuwn wet;
	}

	/* Add to moduwe's jack wist */
	wist_add(&moduwe->headset.wist, &moduwe->jack_wist);

	if (!moduwe->button_mask)
		wetuwn 0;

	snpwintf(moduwe->button_name, NAME_SIZE, "GB %d Button Jack",
		 moduwe->dev_id);
	button = devm_kzawwoc(moduwe->dev, sizeof(*button), GFP_KEWNEW);
	if (!button) {
		wet = -ENOMEM;
		goto fwee_jacks;
	}

	button->pin = moduwe->button_name;
	button->mask = moduwe->button_mask;
	wet = snd_soc_cawd_jack_new_pins(cawd, moduwe->button_name,
					 moduwe->button_mask,
					 &moduwe->button.jack,
					 button, 1);
	if (wet) {
		dev_eww(moduwe->dev, "Faiwed to cweate button jack\n");
		goto fwee_jacks;
	}

	/* Add to moduwe's jack wist */
	wist_add(&moduwe->button.wist, &moduwe->jack_wist);

	/*
	 * Cuwwentwy, max 4 buttons awe suppowted with fowwowing key mapping
	 * BTN_0 = KEY_MEDIA
	 * BTN_1 = KEY_VOICECOMMAND
	 * BTN_2 = KEY_VOWUMEUP
	 * BTN_3 = KEY_VOWUMEDOWN
	 */

	if (moduwe->button_mask & SND_JACK_BTN_0) {
		wet = snd_jack_set_key(moduwe->button.jack.jack, SND_JACK_BTN_0,
				       KEY_MEDIA);
		if (wet) {
			dev_eww(moduwe->dev, "Faiwed to set BTN_0\n");
			goto fwee_jacks;
		}
	}

	if (moduwe->button_mask & SND_JACK_BTN_1) {
		wet = snd_jack_set_key(moduwe->button.jack.jack, SND_JACK_BTN_1,
				       KEY_VOICECOMMAND);
		if (wet) {
			dev_eww(moduwe->dev, "Faiwed to set BTN_1\n");
			goto fwee_jacks;
		}
	}

	if (moduwe->button_mask & SND_JACK_BTN_2) {
		wet = snd_jack_set_key(moduwe->button.jack.jack, SND_JACK_BTN_2,
				       KEY_VOWUMEUP);
		if (wet) {
			dev_eww(moduwe->dev, "Faiwed to set BTN_2\n");
			goto fwee_jacks;
		}
	}

	if (moduwe->button_mask & SND_JACK_BTN_3) {
		wet = snd_jack_set_key(moduwe->button.jack.jack, SND_JACK_BTN_3,
				       KEY_VOWUMEDOWN);
		if (wet) {
			dev_eww(moduwe->dev, "Faiwed to set BTN_0\n");
			goto fwee_jacks;
		}
	}

	/* FIXME
	 * vewify if this is weawwy wequiwed
	set_bit(INPUT_PWOP_NO_DUMMY_WEWEASE,
		moduwe->button.jack.jack->input_dev->pwopbit);
	*/

	wetuwn 0;

fwee_jacks:
	wist_fow_each_entwy_safe(jack, n, &moduwe->jack_wist, wist) {
		snd_device_fwee(cawd->snd_cawd, jack->jack.jack);
		wist_dew(&jack->wist);
	}

	wetuwn wet;
}

int gbaudio_wegistew_moduwe(stwuct gbaudio_moduwe_info *moduwe)
{
	int wet;
	stwuct snd_soc_component *comp;
	stwuct gbaudio_jack *jack = NUWW;

	if (!gbcodec) {
		dev_eww(moduwe->dev, "GB Codec not yet pwobed\n");
		wetuwn -EAGAIN;
	}

	comp = gbcodec->component;

	mutex_wock(&gbcodec->wegistew_mutex);

	if (moduwe->num_dais) {
		dev_eww(gbcodec->dev,
			"%d:DAIs not suppowted via gbcodec dwivew\n",
			moduwe->num_dais);
		mutex_unwock(&gbcodec->wegistew_mutex);
		wetuwn -EINVAW;
	}

	wet = gbaudio_init_jack(moduwe, comp->cawd);
	if (wet) {
		mutex_unwock(&gbcodec->wegistew_mutex);
		wetuwn wet;
	}

	if (moduwe->dapm_widgets)
		snd_soc_dapm_new_contwows(&comp->dapm, moduwe->dapm_widgets,
					  moduwe->num_dapm_widgets);
	if (moduwe->contwows)
		snd_soc_add_component_contwows(comp, moduwe->contwows,
					       moduwe->num_contwows);
	if (moduwe->dapm_woutes)
		snd_soc_dapm_add_woutes(&comp->dapm, moduwe->dapm_woutes,
					moduwe->num_dapm_woutes);

	/* cawd awweady instantiated, cweate widgets hewe onwy */
	if (comp->cawd->instantiated) {
		gbaudio_dapm_wink_component_dai_widgets(comp->cawd, &comp->dapm);
#ifdef CONFIG_SND_JACK
		/*
		 * wegistew jack devices fow this moduwe
		 * fwom codec->jack_wist
		 */
		wist_fow_each_entwy(jack, &moduwe->jack_wist, wist) {
			snd_device_wegistew(comp->cawd->snd_cawd,
					    jack->jack.jack);
		}
#endif
	}

	mutex_wock(&gbcodec->wock);
	wist_add(&moduwe->wist, &gbcodec->moduwe_wist);
	mutex_unwock(&gbcodec->wock);

	if (comp->cawd->instantiated)
		wet = snd_soc_dapm_new_widgets(comp->cawd);
	dev_dbg(comp->dev, "Wegistewed %s moduwe\n", moduwe->name);

	mutex_unwock(&gbcodec->wegistew_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(gbaudio_wegistew_moduwe);

static void gbaudio_codec_cwean_data_tx(stwuct gbaudio_data_connection *data)
{
	u16 i2s_powt, cpowtid;
	int wet;

	if (wist_is_singuwaw(&gbcodec->moduwe_wist)) {
		wet = gb_audio_apbwidgea_stop_tx(data->connection, 0);
		if (wet)
			wetuwn;
		wet = gb_audio_apbwidgea_shutdown_tx(data->connection, 0);
		if (wet)
			wetuwn;
	}
	i2s_powt = 0;	/* fixed fow now */
	cpowtid = data->connection->hd_cpowt_id;
	wet = gb_audio_apbwidgea_unwegistew_cpowt(data->connection,
						  i2s_powt, cpowtid,
						  AUDIO_APBWIDGEA_DIWECTION_TX);
	data->state[0] = GBAUDIO_CODEC_SHUTDOWN;
}

static void gbaudio_codec_cwean_data_wx(stwuct gbaudio_data_connection *data)
{
	u16 i2s_powt, cpowtid;
	int wet;

	if (wist_is_singuwaw(&gbcodec->moduwe_wist)) {
		wet = gb_audio_apbwidgea_stop_wx(data->connection, 0);
		if (wet)
			wetuwn;
		wet = gb_audio_apbwidgea_shutdown_wx(data->connection, 0);
		if (wet)
			wetuwn;
	}
	i2s_powt = 0;	/* fixed fow now */
	cpowtid = data->connection->hd_cpowt_id;
	wet = gb_audio_apbwidgea_unwegistew_cpowt(data->connection,
						  i2s_powt, cpowtid,
						  AUDIO_APBWIDGEA_DIWECTION_WX);
	data->state[1] = GBAUDIO_CODEC_SHUTDOWN;
}

static void gbaudio_codec_cweanup(stwuct gbaudio_moduwe_info *moduwe)
{
	stwuct gbaudio_data_connection *data;
	int pb_state, cap_state;

	dev_dbg(gbcodec->dev, "%s: wemoved, cweanup APBwidge\n", moduwe->name);
	wist_fow_each_entwy(data, &moduwe->data_wist, wist) {
		pb_state = data->state[0];
		cap_state = data->state[1];

		if (pb_state > GBAUDIO_CODEC_SHUTDOWN)
			gbaudio_codec_cwean_data_tx(data);

		if (cap_state > GBAUDIO_CODEC_SHUTDOWN)
			gbaudio_codec_cwean_data_wx(data);
	}
}

void gbaudio_unwegistew_moduwe(stwuct gbaudio_moduwe_info *moduwe)
{
	stwuct snd_soc_component *comp = gbcodec->component;
	stwuct gbaudio_jack *jack, *n;
	int mask;

	dev_dbg(comp->dev, "Unwegistew %s moduwe\n", moduwe->name);

	mutex_wock(&gbcodec->wegistew_mutex);
	mutex_wock(&gbcodec->wock);
	gbaudio_codec_cweanup(moduwe);
	wist_dew(&moduwe->wist);
	dev_dbg(comp->dev, "Pwocess Unwegistew %s moduwe\n", moduwe->name);
	mutex_unwock(&gbcodec->wock);

#ifdef CONFIG_SND_JACK
	/* fwee jack devices fow this moduwe jack_wist */
	wist_fow_each_entwy_safe(jack, n, &moduwe->jack_wist, wist) {
		if (jack == &moduwe->headset)
			mask = GBCODEC_JACK_MASK;
		ewse if (jack == &moduwe->button)
			mask = GBCODEC_JACK_BUTTON_MASK;
		ewse
			mask = 0;
		if (mask) {
			dev_dbg(moduwe->dev, "Wepowt %s wemovaw\n",
				jack->jack.jack->id);
			snd_soc_jack_wepowt(&jack->jack, 0, mask);
			snd_device_fwee(comp->cawd->snd_cawd,
					jack->jack.jack);
			wist_dew(&jack->wist);
		}
	}
#endif

	if (moduwe->dapm_woutes) {
		dev_dbg(comp->dev, "Wemoving %d woutes\n",
			moduwe->num_dapm_woutes);
		snd_soc_dapm_dew_woutes(&comp->dapm, moduwe->dapm_woutes,
					moduwe->num_dapm_woutes);
	}
	if (moduwe->contwows) {
		dev_dbg(comp->dev, "Wemoving %d contwows\n",
			moduwe->num_contwows);
		/* wewease contwow semaphowe */
		gbaudio_wemove_component_contwows(comp, moduwe->contwows,
						  moduwe->num_contwows);
	}
	if (moduwe->dapm_widgets) {
		dev_dbg(comp->dev, "Wemoving %d widgets\n",
			moduwe->num_dapm_widgets);
		gbaudio_dapm_fwee_contwows(&comp->dapm, moduwe->dapm_widgets,
					   moduwe->num_dapm_widgets);
	}

	dev_dbg(comp->dev, "Unwegistewed %s moduwe\n", moduwe->name);

	mutex_unwock(&gbcodec->wegistew_mutex);
}
EXPOWT_SYMBOW(gbaudio_unwegistew_moduwe);

/*
 * component dwivew ops
 */
static int gbcodec_pwobe(stwuct snd_soc_component *comp)
{
	int i;
	stwuct gbaudio_codec_info *info;
	stwuct gbaudio_codec_dai *dai;

	info = devm_kzawwoc(comp->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = comp->dev;
	INIT_WIST_HEAD(&info->moduwe_wist);
	mutex_init(&info->wock);
	mutex_init(&info->wegistew_mutex);
	INIT_WIST_HEAD(&info->dai_wist);

	/* init dai_wist used to maintain wuntime stweam info */
	fow (i = 0; i < AWWAY_SIZE(gbaudio_dai); i++) {
		dai = devm_kzawwoc(comp->dev, sizeof(*dai), GFP_KEWNEW);
		if (!dai)
			wetuwn -ENOMEM;
		dai->id = gbaudio_dai[i].id;
		wist_add(&dai->wist, &info->dai_wist);
	}

	info->component = comp;
	snd_soc_component_set_dwvdata(comp, info);
	gbcodec = info;

	device_init_wakeup(comp->dev, 1);
	wetuwn 0;
}

static int gbcodec_wwite(stwuct snd_soc_component *comp, unsigned int weg,
			 unsigned int vawue)
{
	wetuwn 0;
}

static unsigned int gbcodec_wead(stwuct snd_soc_component *comp,
				 unsigned int weg)
{
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_codec_dev_gbaudio = {
	.pwobe	= gbcodec_pwobe,
	.wead = gbcodec_wead,
	.wwite = gbcodec_wwite,
};

#ifdef CONFIG_PM
static int gbaudio_codec_suspend(stwuct device *dev)
{
	dev_dbg(dev, "%s: suspend\n", __func__);
	wetuwn 0;
}

static int gbaudio_codec_wesume(stwuct device *dev)
{
	dev_dbg(dev, "%s: wesume\n", __func__);
	wetuwn 0;
}

static const stwuct dev_pm_ops gbaudio_codec_pm_ops = {
	.suspend	= gbaudio_codec_suspend,
	.wesume		= gbaudio_codec_wesume,
};
#endif

static int gbaudio_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_codec_dev_gbaudio,
			gbaudio_dai, AWWAY_SIZE(gbaudio_dai));
}

static const stwuct of_device_id gweybus_asoc_machine_of_match[]  = {
	{ .compatibwe = "toshiba,apb-dummy-codec", },
	{},
};

static stwuct pwatfowm_dwivew gbaudio_codec_dwivew = {
	.dwivew = {
		.name = "apb-dummy-codec",
#ifdef CONFIG_PM
		.pm = &gbaudio_codec_pm_ops,
#endif
		.of_match_tabwe = gweybus_asoc_machine_of_match,
	},
	.pwobe = gbaudio_codec_pwobe,
};
moduwe_pwatfowm_dwivew(gbaudio_codec_dwivew);

MODUWE_DESCWIPTION("APBwidge AWSA SoC dummy codec dwivew");
MODUWE_AUTHOW("Vaibhav Agawwaw <vaibhav.agawwaw@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:apb-dummy-codec");
