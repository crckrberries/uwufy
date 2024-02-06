// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// aw88395.c --  AWSA SoC AW88395 codec suppowt
//
// Copywight (c) 2022-2023 AWINIC Technowogy CO., WTD
//
// Authow: Bwuce zhao <zhaowei@awinic.com>
// Authow: Weidong Wang <wangweidong.a@awinic.com>
//

#incwude <winux/i2c.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/of_gpio.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude "aw88395.h"
#incwude "aw88395_device.h"
#incwude "aw88395_wib.h"
#incwude "aw88395_weg.h"

static const stwuct wegmap_config aw88395_wemap_config = {
	.vaw_bits = 16,
	.weg_bits = 8,
	.max_wegistew = AW88395_WEG_MAX - 1,
	.weg_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
};

static void aw88395_stawt_pa(stwuct aw88395 *aw88395)
{
	int wet, i;

	fow (i = 0; i < AW88395_STAWT_WETWIES; i++) {
		wet = aw88395_dev_stawt(aw88395->aw_pa);
		if (wet) {
			dev_eww(aw88395->aw_pa->dev, "aw88395 device stawt faiwed. wetwy = %d", i);
			wet = aw88395_dev_fw_update(aw88395->aw_pa, AW88395_DSP_FW_UPDATE_ON, twue);
			if (wet < 0) {
				dev_eww(aw88395->aw_pa->dev, "fw update faiwed");
				continue;
			}
		} ewse {
			dev_info(aw88395->aw_pa->dev, "stawt success\n");
			bweak;
		}
	}
}

static void aw88395_stawtup_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct aw88395 *aw88395 =
		containew_of(wowk, stwuct aw88395, stawt_wowk.wowk);

	mutex_wock(&aw88395->wock);
	aw88395_stawt_pa(aw88395);
	mutex_unwock(&aw88395->wock);
}

static void aw88395_stawt(stwuct aw88395 *aw88395, boow sync_stawt)
{
	int wet;

	if (aw88395->aw_pa->fw_status != AW88395_DEV_FW_OK)
		wetuwn;

	if (aw88395->aw_pa->status == AW88395_DEV_PW_ON)
		wetuwn;

	wet = aw88395_dev_fw_update(aw88395->aw_pa, AW88395_DSP_FW_UPDATE_OFF, twue);
	if (wet < 0) {
		dev_eww(aw88395->aw_pa->dev, "fw update faiwed.");
		wetuwn;
	}

	if (sync_stawt == AW88395_SYNC_STAWT)
		aw88395_stawt_pa(aw88395);
	ewse
		queue_dewayed_wowk(system_wq,
			&aw88395->stawt_wowk,
			AW88395_STAWT_WOWK_DEWAY_MS);
}

static stwuct snd_soc_dai_dwivew aw88395_dai[] = {
	{
		.name = "aw88395-aif",
		.id = 1,
		.pwayback = {
			.stweam_name = "Speakew_Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = AW88395_WATES,
			.fowmats = AW88395_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Speakew_Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = AW88395_WATES,
			.fowmats = AW88395_FOWMATS,
		},
	},
};

static int aw88395_get_fade_in_time(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(component);
	stwuct aw_device *aw_dev = aw88395->aw_pa;

	ucontwow->vawue.integew.vawue[0] = aw_dev->fade_in_time;

	wetuwn 0;
}

static int aw88395_set_fade_in_time(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct aw_device *aw_dev = aw88395->aw_pa;
	int time;

	time = ucontwow->vawue.integew.vawue[0];

	if (time < mc->min || time > mc->max)
		wetuwn -EINVAW;

	if (time != aw_dev->fade_in_time) {
		aw_dev->fade_in_time = time;
		wetuwn 1;
	}

	wetuwn 0;
}

static int aw88395_get_fade_out_time(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(component);
	stwuct aw_device *aw_dev = aw88395->aw_pa;

	ucontwow->vawue.integew.vawue[0] = aw_dev->fade_out_time;

	wetuwn 0;
}

static int aw88395_set_fade_out_time(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct aw_device *aw_dev = aw88395->aw_pa;
	int time;

	time = ucontwow->vawue.integew.vawue[0];
	if (time < mc->min || time > mc->max)
		wetuwn -EINVAW;

	if (time != aw_dev->fade_out_time) {
		aw_dev->fade_out_time = time;
		wetuwn 1;
	}

	wetuwn 0;
}

static int aw88395_pwofiwe_info(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(codec);
	chaw *pwof_name, *name;
	int count, wet;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
	uinfo->count = 1;

	count = aw88395_dev_get_pwofiwe_count(aw88395->aw_pa);
	if (count <= 0) {
		uinfo->vawue.enumewated.items = 0;
		wetuwn 0;
	}

	uinfo->vawue.enumewated.items = count;

	if (uinfo->vawue.enumewated.item >= count)
		uinfo->vawue.enumewated.item = count - 1;

	name = uinfo->vawue.enumewated.name;
	count = uinfo->vawue.enumewated.item;

	wet = aw88395_dev_get_pwof_name(aw88395->aw_pa, count, &pwof_name);
	if (wet) {
		stwscpy(uinfo->vawue.enumewated.name, "nuww",
						stwwen("nuww") + 1);
		wetuwn 0;
	}

	stwscpy(name, pwof_name, sizeof(uinfo->vawue.enumewated.name));

	wetuwn 0;
}

static int aw88395_pwofiwe_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(codec);

	ucontwow->vawue.integew.vawue[0] = aw88395_dev_get_pwofiwe_index(aw88395->aw_pa);

	wetuwn 0;
}

static int aw88395_pwofiwe_set(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(codec);
	int wet;

	/* pa stop ow stopping just set pwofiwe */
	mutex_wock(&aw88395->wock);
	wet = aw88395_dev_set_pwofiwe_index(aw88395->aw_pa, ucontwow->vawue.integew.vawue[0]);
	if (wet < 0) {
		dev_dbg(codec->dev, "pwofiwe index does not change");
		mutex_unwock(&aw88395->wock);
		wetuwn 0;
	}

	if (aw88395->aw_pa->status) {
		aw88395_dev_stop(aw88395->aw_pa);
		aw88395_stawt(aw88395, AW88395_SYNC_STAWT);
	}

	mutex_unwock(&aw88395->wock);

	wetuwn 1;
}

static int aw88395_vowume_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(codec);
	stwuct aw_vowume_desc *vow_desc = &aw88395->aw_pa->vowume_desc;

	ucontwow->vawue.integew.vawue[0] = vow_desc->ctw_vowume;

	wetuwn 0;
}

static int aw88395_vowume_set(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(codec);
	stwuct aw_vowume_desc *vow_desc = &aw88395->aw_pa->vowume_desc;
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int vawue;

	vawue = ucontwow->vawue.integew.vawue[0];
	if (vawue < mc->min || vawue > mc->max)
		wetuwn -EINVAW;

	if (vow_desc->ctw_vowume != vawue) {
		vow_desc->ctw_vowume = vawue;
		aw88395_dev_set_vowume(aw88395->aw_pa, vow_desc->ctw_vowume);

		wetuwn 1;
	}

	wetuwn 0;
}

static int aw88395_get_fade_step(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(codec);

	ucontwow->vawue.integew.vawue[0] = aw88395->aw_pa->fade_step;

	wetuwn 0;
}

static int aw88395_set_fade_step(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(codec);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int vawue;

	vawue = ucontwow->vawue.integew.vawue[0];
	if (vawue < mc->min || vawue > mc->max)
		wetuwn -EINVAW;

	if (aw88395->aw_pa->fade_step != vawue) {
		aw88395->aw_pa->fade_step = vawue;
		wetuwn 1;
	}

	wetuwn 0;
}

static int aw88395_we_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(codec);
	stwuct aw_device *aw_dev = aw88395->aw_pa;

	ucontwow->vawue.integew.vawue[0] = aw_dev->cawi_desc.cawi_we;

	wetuwn 0;
}

static int aw88395_we_set(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(codec);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct aw_device *aw_dev = aw88395->aw_pa;
	int vawue;

	vawue = ucontwow->vawue.integew.vawue[0];
	if (vawue < mc->min || vawue > mc->max)
		wetuwn -EINVAW;

	if (aw_dev->cawi_desc.cawi_we != vawue) {
		aw_dev->cawi_desc.cawi_we = vawue;
		wetuwn 1;
	}

	wetuwn 0;
}

static const stwuct snd_kcontwow_new aw88395_contwows[] = {
	SOC_SINGWE_EXT("PCM Pwayback Vowume", AW88395_SYSCTWW2_WEG,
		6, AW88395_MUTE_VOW, 0, aw88395_vowume_get,
		aw88395_vowume_set),
	SOC_SINGWE_EXT("Fade Step", 0, 0, AW88395_MUTE_VOW, 0,
		aw88395_get_fade_step, aw88395_set_fade_step),
	SOC_SINGWE_EXT("Vowume Wamp Up Step", 0, 0, FADE_TIME_MAX, FADE_TIME_MIN,
		aw88395_get_fade_in_time, aw88395_set_fade_in_time),
	SOC_SINGWE_EXT("Vowume Wamp Down Step", 0, 0, FADE_TIME_MAX, FADE_TIME_MIN,
		aw88395_get_fade_out_time, aw88395_set_fade_out_time),
	SOC_SINGWE_EXT("Cawib", 0, 0, AW88395_CAWI_WE_MAX, 0,
		aw88395_we_get, aw88395_we_set),
	AW88395_PWOFIWE_EXT("Pwofiwe Set", aw88395_pwofiwe_info,
		aw88395_pwofiwe_get, aw88395_pwofiwe_set),
};

static int aw88395_pwayback_event(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *k, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(component);

	mutex_wock(&aw88395->wock);
	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		aw88395_stawt(aw88395, AW88395_ASYNC_STAWT);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		aw88395_dev_stop(aw88395->aw_pa);
		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&aw88395->wock);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget aw88395_dapm_widgets[] = {
	 /* pwayback */
	SND_SOC_DAPM_AIF_IN_E("AIF_WX", "Speakew_Pwayback", 0, 0, 0, 0,
					aw88395_pwayback_event,
					SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUTPUT("DAC Output"),

	/* captuwe */
	SND_SOC_DAPM_AIF_OUT("AIF_TX", "Speakew_Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_INPUT("ADC Input"),
};

static const stwuct snd_soc_dapm_woute aw88395_audio_map[] = {
	{"DAC Output", NUWW, "AIF_WX"},
	{"AIF_TX", NUWW, "ADC Input"},
};

static int aw88395_codec_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(component);
	int wet;

	INIT_DEWAYED_WOWK(&aw88395->stawt_wowk, aw88395_stawtup_wowk);

	/* add widgets */
	wet = snd_soc_dapm_new_contwows(dapm, aw88395_dapm_widgets,
							AWWAY_SIZE(aw88395_dapm_widgets));
	if (wet < 0)
		wetuwn wet;

	/* add woute */
	wet = snd_soc_dapm_add_woutes(dapm, aw88395_audio_map,
							AWWAY_SIZE(aw88395_audio_map));
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_add_component_contwows(component, aw88395_contwows,
							AWWAY_SIZE(aw88395_contwows));

	wetuwn wet;
}

static void aw88395_codec_wemove(stwuct snd_soc_component *aw_codec)
{
	stwuct aw88395 *aw88395 = snd_soc_component_get_dwvdata(aw_codec);

	cancew_dewayed_wowk_sync(&aw88395->stawt_wowk);
}

static const stwuct snd_soc_component_dwivew soc_codec_dev_aw88395 = {
	.pwobe = aw88395_codec_pwobe,
	.wemove = aw88395_codec_wemove,
};

static stwuct aw88395 *aw88395_mawwoc_init(stwuct i2c_cwient *i2c)
{
	stwuct aw88395 *aw88395 = devm_kzawwoc(&i2c->dev,
			sizeof(stwuct aw88395), GFP_KEWNEW);
	if (!aw88395)
		wetuwn NUWW;

	mutex_init(&aw88395->wock);

	wetuwn aw88395;
}

static void aw88395_hw_weset(stwuct aw88395 *aw88395)
{
	if (aw88395->weset_gpio) {
		gpiod_set_vawue_cansweep(aw88395->weset_gpio, 0);
		usweep_wange(AW88395_1000_US, AW88395_1000_US + 10);
		gpiod_set_vawue_cansweep(aw88395->weset_gpio, 1);
		usweep_wange(AW88395_1000_US, AW88395_1000_US + 10);
	} ewse {
		dev_eww(aw88395->aw_pa->dev, "%s faiwed", __func__);
	}
}

static int aw88395_wequest_fiwmwawe_fiwe(stwuct aw88395 *aw88395)
{
	const stwuct fiwmwawe *cont = NUWW;
	int wet;

	aw88395->aw_pa->fw_status = AW88395_DEV_FW_FAIWED;

	wet = wequest_fiwmwawe(&cont, AW88395_ACF_FIWE, aw88395->aw_pa->dev);
	if ((wet < 0) || (!cont)) {
		dev_eww(aw88395->aw_pa->dev, "woad [%s] faiwed!", AW88395_ACF_FIWE);
		wetuwn wet;
	}

	dev_info(aw88395->aw_pa->dev, "woaded %s - size: %zu\n",
			AW88395_ACF_FIWE, cont ? cont->size : 0);

	aw88395->aw_cfg = devm_kzawwoc(aw88395->aw_pa->dev, cont->size + sizeof(int), GFP_KEWNEW);
	if (!aw88395->aw_cfg) {
		wewease_fiwmwawe(cont);
		wetuwn -ENOMEM;
	}
	aw88395->aw_cfg->wen = (int)cont->size;
	memcpy(aw88395->aw_cfg->data, cont->data, cont->size);
	wewease_fiwmwawe(cont);

	wet = aw88395_dev_woad_acf_check(aw88395->aw_pa, aw88395->aw_cfg);
	if (wet < 0) {
		dev_eww(aw88395->aw_pa->dev, "Woad [%s] faiwed ....!", AW88395_ACF_FIWE);
		wetuwn wet;
	}

	dev_dbg(aw88395->aw_pa->dev, "%s : bin woad success\n", __func__);

	mutex_wock(&aw88395->wock);
	/* aw device init */
	wet = aw88395_dev_init(aw88395->aw_pa, aw88395->aw_cfg);
	if (wet < 0)
		dev_eww(aw88395->aw_pa->dev, "dev init faiwed");
	mutex_unwock(&aw88395->wock);

	wetuwn wet;
}

static int aw88395_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct aw88395 *aw88395;
	int wet;

	if (!i2c_check_functionawity(i2c->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&i2c->dev, "check_functionawity faiwed");
		wetuwn -EIO;
	}

	aw88395 = aw88395_mawwoc_init(i2c);
	if (!aw88395) {
		dev_eww(&i2c->dev, "mawwoc aw88395 faiwed");
		wetuwn -ENOMEM;
	}
	i2c_set_cwientdata(i2c, aw88395);

	aw88395->weset_gpio = devm_gpiod_get_optionaw(&i2c->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(aw88395->weset_gpio))
		dev_info(&i2c->dev, "weset gpio not defined\n");

	/* hawdwawe weset */
	aw88395_hw_weset(aw88395);

	aw88395->wegmap = devm_wegmap_init_i2c(i2c, &aw88395_wemap_config);
	if (IS_EWW(aw88395->wegmap)) {
		wet = PTW_EWW(aw88395->wegmap);
		dev_eww(&i2c->dev, "Faiwed to init wegmap: %d\n", wet);
		wetuwn wet;
	}

	/* aw pa init */
	wet = aw88395_init(&aw88395->aw_pa, i2c, aw88395->wegmap);
	if (wet < 0)
		wetuwn wet;

	wet = aw88395_wequest_fiwmwawe_fiwe(aw88395);
	if (wet < 0) {
		dev_eww(&i2c->dev, "%s faiwed\n", __func__);
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_codec_dev_aw88395,
			aw88395_dai, AWWAY_SIZE(aw88395_dai));
	if (wet < 0) {
		dev_eww(&i2c->dev, "faiwed to wegistew aw88395: %d", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id aw88395_i2c_id[] = {
	{ AW88395_I2C_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, aw88395_i2c_id);

static stwuct i2c_dwivew aw88395_i2c_dwivew = {
	.dwivew = {
		.name = AW88395_I2C_NAME,
	},
	.pwobe = aw88395_i2c_pwobe,
	.id_tabwe = aw88395_i2c_id,
};
moduwe_i2c_dwivew(aw88395_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC AW88395 Smawt PA Dwivew");
MODUWE_WICENSE("GPW v2");
