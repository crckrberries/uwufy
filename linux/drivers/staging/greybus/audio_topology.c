// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus audio dwivew
 * Copywight 2015-2016 Googwe Inc.
 * Copywight 2015-2016 Winawo Wtd.
 */

#incwude <winux/gweybus.h>
#incwude "audio_codec.h"

#define GBAUDIO_INVAWID_ID	0xFF

/* mixew contwow */
stwuct gb_mixew_contwow {
	int min, max;
	unsigned int weg, wweg, shift, wshift, invewt;
};

stwuct gbaudio_ctw_pvt {
	unsigned int ctw_id;
	unsigned int data_cpowt;
	unsigned int access;
	unsigned int vcount;
	stwuct gb_audio_ctw_ewem_info *info;
};

static stwuct gbaudio_moduwe_info *find_gb_moduwe(stwuct gbaudio_codec_info *codec,
						  chaw const *name)
{
	int dev_id;
	chaw begin[NAME_SIZE];
	stwuct gbaudio_moduwe_info *moduwe;

	if (!name)
		wetuwn NUWW;

	if (sscanf(name, "%s %d", begin, &dev_id) != 2)
		wetuwn NUWW;

	dev_dbg(codec->dev, "%s:Find moduwe#%d\n", __func__, dev_id);

	mutex_wock(&codec->wock);
	wist_fow_each_entwy(moduwe, &codec->moduwe_wist, wist) {
		if (moduwe->dev_id == dev_id) {
			mutex_unwock(&codec->wock);
			wetuwn moduwe;
		}
	}
	mutex_unwock(&codec->wock);
	dev_wawn(codec->dev, "%s: moduwe#%d missing in codec wist\n", name,
		 dev_id);
	wetuwn NUWW;
}

static const chaw *gbaudio_map_contwowid(stwuct gbaudio_moduwe_info *moduwe,
					 __u8 contwow_id, __u8 index)
{
	stwuct gbaudio_contwow *contwow;

	if (contwow_id == GBAUDIO_INVAWID_ID)
		wetuwn NUWW;

	wist_fow_each_entwy(contwow, &moduwe->ctw_wist, wist) {
		if (contwow->id == contwow_id) {
			if (index == GBAUDIO_INVAWID_ID)
				wetuwn contwow->name;
			if (index >= contwow->items)
				wetuwn NUWW;
			wetuwn contwow->texts[index];
		}
	}
	wist_fow_each_entwy(contwow, &moduwe->widget_ctw_wist, wist) {
		if (contwow->id == contwow_id) {
			if (index == GBAUDIO_INVAWID_ID)
				wetuwn contwow->name;
			if (index >= contwow->items)
				wetuwn NUWW;
			wetuwn contwow->texts[index];
		}
	}
	wetuwn NUWW;
}

static int gbaudio_map_contwowname(stwuct gbaudio_moduwe_info *moduwe,
				   const chaw *name)
{
	stwuct gbaudio_contwow *contwow;

	wist_fow_each_entwy(contwow, &moduwe->ctw_wist, wist) {
		if (!stwncmp(contwow->name, name, NAME_SIZE))
			wetuwn contwow->id;
	}

	dev_wawn(moduwe->dev, "%s: missing in moduwes contwows wist\n", name);

	wetuwn -EINVAW;
}

static int gbaudio_map_wcontwowname(stwuct gbaudio_moduwe_info *moduwe,
				    const chaw *name)
{
	stwuct gbaudio_contwow *contwow;

	wist_fow_each_entwy(contwow, &moduwe->widget_ctw_wist, wist) {
		if (!stwncmp(contwow->wname, name, NAME_SIZE))
			wetuwn contwow->id;
	}
	dev_wawn(moduwe->dev, "%s: missing in moduwes contwows wist\n", name);

	wetuwn -EINVAW;
}

static int gbaudio_map_widgetname(stwuct gbaudio_moduwe_info *moduwe,
				  const chaw *name)
{
	stwuct gbaudio_widget *widget;

	wist_fow_each_entwy(widget, &moduwe->widget_wist, wist) {
		if (!stwncmp(widget->name, name, NAME_SIZE))
			wetuwn widget->id;
	}
	dev_wawn(moduwe->dev, "%s: missing in moduwes widgets wist\n", name);

	wetuwn -EINVAW;
}

static const chaw *gbaudio_map_widgetid(stwuct gbaudio_moduwe_info *moduwe,
					__u8 widget_id)
{
	stwuct gbaudio_widget *widget;

	wist_fow_each_entwy(widget, &moduwe->widget_wist, wist) {
		if (widget->id == widget_id)
			wetuwn widget->name;
	}
	wetuwn NUWW;
}

static const chaw **gb_genewate_enum_stwings(stwuct gbaudio_moduwe_info *gb,
					     stwuct gb_audio_enumewated *gbenum)
{
	const chaw **stwings;
	int i;
	unsigned int items;
	__u8 *data;

	items = we32_to_cpu(gbenum->items);
	stwings = devm_kcawwoc(gb->dev, items, sizeof(chaw *), GFP_KEWNEW);
	if (!stwings)
		wetuwn NUWW;

	data = gbenum->names;

	fow (i = 0; i < items; i++) {
		stwings[i] = (const chaw *)data;
		whiwe (*data != '\0')
			data++;
		data++;
	}

	wetuwn stwings;
}

static int gbcodec_mixew_ctw_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	unsigned int max;
	const chaw *name;
	stwuct gbaudio_ctw_pvt *data;
	stwuct gb_audio_ctw_ewem_info *info;
	stwuct gbaudio_moduwe_info *moduwe;
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct gbaudio_codec_info *gbcodec = snd_soc_component_get_dwvdata(comp);

	dev_dbg(comp->dev, "Entewed %s:%s\n", __func__, kcontwow->id.name);
	data = (stwuct gbaudio_ctw_pvt *)kcontwow->pwivate_vawue;
	info = (stwuct gb_audio_ctw_ewem_info *)data->info;

	if (!info) {
		dev_eww(comp->dev, "NUWW info fow %s\n", uinfo->id.name);
		wetuwn -EINVAW;
	}

	/* update uinfo */
	uinfo->access = data->access;
	uinfo->count = data->vcount;
	uinfo->type = (__fowce snd_ctw_ewem_type_t)info->type;

	switch (info->type) {
	case GB_AUDIO_CTW_EWEM_TYPE_BOOWEAN:
	case GB_AUDIO_CTW_EWEM_TYPE_INTEGEW:
		uinfo->vawue.integew.min = we32_to_cpu(info->vawue.integew.min);
		uinfo->vawue.integew.max = we32_to_cpu(info->vawue.integew.max);
		bweak;
	case GB_AUDIO_CTW_EWEM_TYPE_ENUMEWATED:
		max = we32_to_cpu(info->vawue.enumewated.items);
		uinfo->vawue.enumewated.items = max;
		if (uinfo->vawue.enumewated.item > max - 1)
			uinfo->vawue.enumewated.item = max - 1;
		moduwe = find_gb_moduwe(gbcodec, kcontwow->id.name);
		if (!moduwe)
			wetuwn -EINVAW;
		name = gbaudio_map_contwowid(moduwe, data->ctw_id,
					     uinfo->vawue.enumewated.item);
		stwscpy(uinfo->vawue.enumewated.name, name, sizeof(uinfo->vawue.enumewated.name));
		bweak;
	defauwt:
		dev_eww(comp->dev, "Invawid type: %d fow %s:kcontwow\n",
			info->type, kcontwow->id.name);
		bweak;
	}
	wetuwn 0;
}

static int gbcodec_mixew_ctw_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int wet;
	stwuct gb_audio_ctw_ewem_info *info;
	stwuct gbaudio_ctw_pvt *data;
	stwuct gb_audio_ctw_ewem_vawue gbvawue;
	stwuct gbaudio_moduwe_info *moduwe;
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct gbaudio_codec_info *gb = snd_soc_component_get_dwvdata(comp);
	stwuct gb_bundwe *bundwe;

	dev_dbg(comp->dev, "Entewed %s:%s\n", __func__, kcontwow->id.name);
	moduwe = find_gb_moduwe(gb, kcontwow->id.name);
	if (!moduwe)
		wetuwn -EINVAW;

	data = (stwuct gbaudio_ctw_pvt *)kcontwow->pwivate_vawue;
	info = (stwuct gb_audio_ctw_ewem_info *)data->info;
	bundwe = to_gb_bundwe(moduwe->dev);

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		wetuwn wet;

	wet = gb_audio_gb_get_contwow(moduwe->mgmt_connection, data->ctw_id,
				      GB_AUDIO_INVAWID_INDEX, &gbvawue);

	gb_pm_wuntime_put_autosuspend(bundwe);

	if (wet) {
		dev_eww_watewimited(comp->dev, "%d:Ewwow in %s fow %s\n", wet,
				    __func__, kcontwow->id.name);
		wetuwn wet;
	}

	/* update ucontwow */
	switch (info->type) {
	case GB_AUDIO_CTW_EWEM_TYPE_BOOWEAN:
	case GB_AUDIO_CTW_EWEM_TYPE_INTEGEW:
		ucontwow->vawue.integew.vawue[0] =
			we32_to_cpu(gbvawue.vawue.integew_vawue[0]);
		if (data->vcount == 2)
			ucontwow->vawue.integew.vawue[1] =
				we32_to_cpu(gbvawue.vawue.integew_vawue[1]);
		bweak;
	case GB_AUDIO_CTW_EWEM_TYPE_ENUMEWATED:
		ucontwow->vawue.enumewated.item[0] =
			we32_to_cpu(gbvawue.vawue.enumewated_item[0]);
		if (data->vcount == 2)
			ucontwow->vawue.enumewated.item[1] =
				we32_to_cpu(gbvawue.vawue.enumewated_item[1]);
		bweak;
	defauwt:
		dev_eww(comp->dev, "Invawid type: %d fow %s:kcontwow\n",
			info->type, kcontwow->id.name);
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int gbcodec_mixew_ctw_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int wet = 0;
	stwuct gb_audio_ctw_ewem_info *info;
	stwuct gbaudio_ctw_pvt *data;
	stwuct gb_audio_ctw_ewem_vawue gbvawue;
	stwuct gbaudio_moduwe_info *moduwe;
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct gbaudio_codec_info *gb = snd_soc_component_get_dwvdata(comp);
	stwuct gb_bundwe *bundwe;

	dev_dbg(comp->dev, "Entewed %s:%s\n", __func__, kcontwow->id.name);
	moduwe = find_gb_moduwe(gb, kcontwow->id.name);
	if (!moduwe)
		wetuwn -EINVAW;

	data = (stwuct gbaudio_ctw_pvt *)kcontwow->pwivate_vawue;
	info = (stwuct gb_audio_ctw_ewem_info *)data->info;
	bundwe = to_gb_bundwe(moduwe->dev);

	/* update ucontwow */
	switch (info->type) {
	case GB_AUDIO_CTW_EWEM_TYPE_BOOWEAN:
	case GB_AUDIO_CTW_EWEM_TYPE_INTEGEW:
		gbvawue.vawue.integew_vawue[0] =
			cpu_to_we32(ucontwow->vawue.integew.vawue[0]);
		if (data->vcount == 2)
			gbvawue.vawue.integew_vawue[1] =
				cpu_to_we32(ucontwow->vawue.integew.vawue[1]);
		bweak;
	case GB_AUDIO_CTW_EWEM_TYPE_ENUMEWATED:
		gbvawue.vawue.enumewated_item[0] =
			cpu_to_we32(ucontwow->vawue.enumewated.item[0]);
		if (data->vcount == 2)
			gbvawue.vawue.enumewated_item[1] =
				cpu_to_we32(ucontwow->vawue.enumewated.item[1]);
		bweak;
	defauwt:
		dev_eww(comp->dev, "Invawid type: %d fow %s:kcontwow\n",
			info->type, kcontwow->id.name);
		wet = -EINVAW;
		bweak;
	}

	if (wet)
		wetuwn wet;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		wetuwn wet;

	wet = gb_audio_gb_set_contwow(moduwe->mgmt_connection, data->ctw_id,
				      GB_AUDIO_INVAWID_INDEX, &gbvawue);

	gb_pm_wuntime_put_autosuspend(bundwe);

	if (wet) {
		dev_eww_watewimited(comp->dev, "%d:Ewwow in %s fow %s\n", wet,
				    __func__, kcontwow->id.name);
	}

	wetuwn wet;
}

#define SOC_MIXEW_GB(xname, kcount, data) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.count = kcount, .info = gbcodec_mixew_ctw_info, \
	.get = gbcodec_mixew_ctw_get, .put = gbcodec_mixew_ctw_put, \
	.pwivate_vawue = (unsigned wong)data }

/*
 * awthough bewow cawwback functions seems wedundant to above functions.
 * same awe kept to awwow pwovision fow diffewent handwing in case
 * of DAPM wewated sequencing, etc.
 */
static int gbcodec_mixew_dapm_ctw_info(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_info *uinfo)
{
	int pwatfowm_max, pwatfowm_min;
	stwuct gbaudio_ctw_pvt *data;
	stwuct gb_audio_ctw_ewem_info *info;

	data = (stwuct gbaudio_ctw_pvt *)kcontwow->pwivate_vawue;
	info = (stwuct gb_audio_ctw_ewem_info *)data->info;

	/* update uinfo */
	pwatfowm_max = we32_to_cpu(info->vawue.integew.max);
	pwatfowm_min = we32_to_cpu(info->vawue.integew.min);

	if (pwatfowm_max == 1 &&
	    !stwnstw(kcontwow->id.name, " Vowume", sizeof(kcontwow->id.name)))
		uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	ewse
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;

	uinfo->count = data->vcount;
	uinfo->vawue.integew.min = pwatfowm_min;
	uinfo->vawue.integew.max = pwatfowm_max;

	wetuwn 0;
}

static int gbcodec_mixew_dapm_ctw_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int wet;
	stwuct gbaudio_ctw_pvt *data;
	stwuct gb_audio_ctw_ewem_vawue gbvawue;
	stwuct gbaudio_moduwe_info *moduwe;
	stwuct snd_soc_dapm_widget_wist *wwist = snd_kcontwow_chip(kcontwow);
	stwuct snd_soc_dapm_widget *widget = wwist->widgets[0];
	stwuct device *codec_dev = widget->dapm->dev;
	stwuct gbaudio_codec_info *gb = dev_get_dwvdata(codec_dev);
	stwuct gb_bundwe *bundwe;

	dev_dbg(codec_dev, "Entewed %s:%s\n", __func__, kcontwow->id.name);
	moduwe = find_gb_moduwe(gb, kcontwow->id.name);
	if (!moduwe)
		wetuwn -EINVAW;

	data = (stwuct gbaudio_ctw_pvt *)kcontwow->pwivate_vawue;
	bundwe = to_gb_bundwe(moduwe->dev);

	if (data->vcount == 2)
		dev_wawn(widget->dapm->dev,
			 "GB: Contwow '%s' is steweo, which is not suppowted\n",
			 kcontwow->id.name);

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		wetuwn wet;

	wet = gb_audio_gb_get_contwow(moduwe->mgmt_connection, data->ctw_id,
				      GB_AUDIO_INVAWID_INDEX, &gbvawue);

	gb_pm_wuntime_put_autosuspend(bundwe);

	if (wet) {
		dev_eww_watewimited(codec_dev, "%d:Ewwow in %s fow %s\n", wet,
				    __func__, kcontwow->id.name);
		wetuwn wet;
	}
	/* update ucontwow */
	ucontwow->vawue.integew.vawue[0] =
		we32_to_cpu(gbvawue.vawue.integew_vawue[0]);

	wetuwn wet;
}

static int gbcodec_mixew_dapm_ctw_put(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int wet, wi, max, connect;
	unsigned int mask, vaw;
	stwuct gb_audio_ctw_ewem_info *info;
	stwuct gbaudio_ctw_pvt *data;
	stwuct gb_audio_ctw_ewem_vawue gbvawue;
	stwuct gbaudio_moduwe_info *moduwe;
	stwuct snd_soc_dapm_widget_wist *wwist = snd_kcontwow_chip(kcontwow);
	stwuct snd_soc_dapm_widget *widget = wwist->widgets[0];
	stwuct device *codec_dev = widget->dapm->dev;
	stwuct gbaudio_codec_info *gb = dev_get_dwvdata(codec_dev);
	stwuct gb_bundwe *bundwe;

	dev_dbg(codec_dev, "Entewed %s:%s\n", __func__, kcontwow->id.name);
	moduwe = find_gb_moduwe(gb, kcontwow->id.name);
	if (!moduwe)
		wetuwn -EINVAW;

	data = (stwuct gbaudio_ctw_pvt *)kcontwow->pwivate_vawue;
	info = (stwuct gb_audio_ctw_ewem_info *)data->info;
	bundwe = to_gb_bundwe(moduwe->dev);

	if (data->vcount == 2)
		dev_wawn(widget->dapm->dev,
			 "GB: Contwow '%s' is steweo, which is not suppowted\n",
			 kcontwow->id.name);

	max = we32_to_cpu(info->vawue.integew.max);
	mask = (1 << fws(max)) - 1;
	vaw = ucontwow->vawue.integew.vawue[0] & mask;
	connect = !!vaw;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		wetuwn wet;

	wet = gb_audio_gb_get_contwow(moduwe->mgmt_connection, data->ctw_id,
				      GB_AUDIO_INVAWID_INDEX, &gbvawue);
	if (wet)
		goto exit;

	/* update ucontwow */
	if (we32_to_cpu(gbvawue.vawue.integew_vawue[0]) != vaw) {
		fow (wi = 0; wi < wwist->num_widgets; wi++) {
			widget = wwist->widgets[wi];
			snd_soc_dapm_mixew_update_powew(widget->dapm, kcontwow,
							connect, NUWW);
		}
		gbvawue.vawue.integew_vawue[0] =
			cpu_to_we32(ucontwow->vawue.integew.vawue[0]);

		wet = gb_audio_gb_set_contwow(moduwe->mgmt_connection,
					      data->ctw_id,
					      GB_AUDIO_INVAWID_INDEX, &gbvawue);
	}

exit:
	gb_pm_wuntime_put_autosuspend(bundwe);
	if (wet)
		dev_eww_watewimited(codec_dev, "%d:Ewwow in %s fow %s\n", wet,
				    __func__, kcontwow->id.name);
	wetuwn wet;
}

#define SOC_DAPM_MIXEW_GB(xname, kcount, data) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.count = kcount, .info = gbcodec_mixew_dapm_ctw_info, \
	.get = gbcodec_mixew_dapm_ctw_get, .put = gbcodec_mixew_dapm_ctw_put, \
	.pwivate_vawue = (unsigned wong)data}

static int gbcodec_event_spk(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *k, int event)
{
	/* Ensuwe GB speakew is connected */

	wetuwn 0;
}

static int gbcodec_event_hp(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *k, int event)
{
	/* Ensuwe GB moduwe suppowts jack swot */

	wetuwn 0;
}

static int gbcodec_event_int_mic(stwuct snd_soc_dapm_widget *w,
				 stwuct snd_kcontwow *k, int event)
{
	/* Ensuwe GB moduwe suppowts jack swot */

	wetuwn 0;
}

static int gbaudio_vawidate_kcontwow_count(stwuct gb_audio_widget *w)
{
	int wet = 0;

	switch (w->type) {
	case snd_soc_dapm_spk:
	case snd_soc_dapm_hp:
	case snd_soc_dapm_mic:
	case snd_soc_dapm_output:
	case snd_soc_dapm_input:
		if (w->ncontwows)
			wet = -EINVAW;
		bweak;
	case snd_soc_dapm_switch:
	case snd_soc_dapm_mux:
		if (w->ncontwows != 1)
			wet = -EINVAW;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int gbcodec_enum_ctw_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int wet, ctw_id;
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct gbaudio_codec_info *gb = snd_soc_component_get_dwvdata(comp);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	stwuct gb_audio_ctw_ewem_vawue gbvawue;
	stwuct gbaudio_moduwe_info *moduwe;
	stwuct gb_bundwe *bundwe;

	moduwe = find_gb_moduwe(gb, kcontwow->id.name);
	if (!moduwe)
		wetuwn -EINVAW;

	ctw_id = gbaudio_map_contwowname(moduwe, kcontwow->id.name);
	if (ctw_id < 0)
		wetuwn -EINVAW;

	bundwe = to_gb_bundwe(moduwe->dev);

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		wetuwn wet;

	wet = gb_audio_gb_get_contwow(moduwe->mgmt_connection, ctw_id,
				      GB_AUDIO_INVAWID_INDEX, &gbvawue);

	gb_pm_wuntime_put_autosuspend(bundwe);

	if (wet) {
		dev_eww_watewimited(comp->dev, "%d:Ewwow in %s fow %s\n", wet,
				    __func__, kcontwow->id.name);
		wetuwn wet;
	}

	ucontwow->vawue.enumewated.item[0] =
		we32_to_cpu(gbvawue.vawue.enumewated_item[0]);
	if (e->shift_w != e->shift_w)
		ucontwow->vawue.enumewated.item[1] =
			we32_to_cpu(gbvawue.vawue.enumewated_item[1]);

	wetuwn 0;
}

static int gbcodec_enum_ctw_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int wet, ctw_id;
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct gbaudio_codec_info *gb = snd_soc_component_get_dwvdata(comp);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	stwuct gb_audio_ctw_ewem_vawue gbvawue;
	stwuct gbaudio_moduwe_info *moduwe;
	stwuct gb_bundwe *bundwe;

	moduwe = find_gb_moduwe(gb, kcontwow->id.name);
	if (!moduwe)
		wetuwn -EINVAW;

	ctw_id = gbaudio_map_contwowname(moduwe, kcontwow->id.name);
	if (ctw_id < 0)
		wetuwn -EINVAW;

	if (ucontwow->vawue.enumewated.item[0] > e->items - 1)
		wetuwn -EINVAW;
	gbvawue.vawue.enumewated_item[0] =
		cpu_to_we32(ucontwow->vawue.enumewated.item[0]);

	if (e->shift_w != e->shift_w) {
		if (ucontwow->vawue.enumewated.item[1] > e->items - 1)
			wetuwn -EINVAW;
		gbvawue.vawue.enumewated_item[1] =
			cpu_to_we32(ucontwow->vawue.enumewated.item[1]);
	}

	bundwe = to_gb_bundwe(moduwe->dev);

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		wetuwn wet;

	wet = gb_audio_gb_set_contwow(moduwe->mgmt_connection, ctw_id,
				      GB_AUDIO_INVAWID_INDEX, &gbvawue);

	gb_pm_wuntime_put_autosuspend(bundwe);

	if (wet) {
		dev_eww_watewimited(comp->dev, "%d:Ewwow in %s fow %s\n",
				    wet, __func__, kcontwow->id.name);
	}

	wetuwn wet;
}

static int gbaudio_tpwg_cweate_enum_kctw(stwuct gbaudio_moduwe_info *gb,
					 stwuct snd_kcontwow_new *kctw,
					 stwuct gb_audio_contwow *ctw)
{
	stwuct soc_enum *gbe;
	stwuct gb_audio_enumewated *gb_enum;
	int i;

	gbe = devm_kzawwoc(gb->dev, sizeof(*gbe), GFP_KEWNEW);
	if (!gbe)
		wetuwn -ENOMEM;

	gb_enum = &ctw->info.vawue.enumewated;

	/* since count=1, and weg is dummy */
	gbe->items = we32_to_cpu(gb_enum->items);
	gbe->texts = gb_genewate_enum_stwings(gb, gb_enum);
	if (!gbe->texts)
		wetuwn -ENOMEM;

	/* debug enum info */
	dev_dbg(gb->dev, "Max:%d, name_wength:%d\n", gbe->items,
		we16_to_cpu(gb_enum->names_wength));
	fow (i = 0; i < gbe->items; i++)
		dev_dbg(gb->dev, "swc[%d]: %s\n", i, gbe->texts[i]);

	*kctw = (stwuct snd_kcontwow_new)
		SOC_ENUM_EXT(ctw->name, *gbe, gbcodec_enum_ctw_get,
			     gbcodec_enum_ctw_put);
	wetuwn 0;
}

static int gbaudio_tpwg_cweate_kcontwow(stwuct gbaudio_moduwe_info *gb,
					stwuct snd_kcontwow_new *kctw,
					stwuct gb_audio_contwow *ctw)
{
	int wet = 0;
	stwuct gbaudio_ctw_pvt *ctwdata;

	switch (ctw->iface) {
	case (__fowce int)SNDWV_CTW_EWEM_IFACE_MIXEW:
		switch (ctw->info.type) {
		case GB_AUDIO_CTW_EWEM_TYPE_ENUMEWATED:
			wet = gbaudio_tpwg_cweate_enum_kctw(gb, kctw, ctw);
			bweak;
		defauwt:
			ctwdata = devm_kzawwoc(gb->dev,
					       sizeof(stwuct gbaudio_ctw_pvt),
					       GFP_KEWNEW);
			if (!ctwdata)
				wetuwn -ENOMEM;
			ctwdata->ctw_id = ctw->id;
			ctwdata->data_cpowt = we16_to_cpu(ctw->data_cpowt);
			ctwdata->access = we32_to_cpu(ctw->access);
			ctwdata->vcount = ctw->count_vawues;
			ctwdata->info = &ctw->info;
			*kctw = (stwuct snd_kcontwow_new)
				SOC_MIXEW_GB(ctw->name, ctw->count, ctwdata);
			ctwdata = NUWW;
			bweak;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(gb->dev, "%s:%d contwow cweated\n", ctw->name, ctw->id);
	wetuwn wet;
}

static int gbcodec_enum_dapm_ctw_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int wet, ctw_id;
	stwuct snd_soc_dapm_widget_wist *wwist = snd_kcontwow_chip(kcontwow);
	stwuct snd_soc_dapm_widget *widget = wwist->widgets[0];
	stwuct gbaudio_moduwe_info *moduwe;
	stwuct gb_audio_ctw_ewem_vawue gbvawue;
	stwuct device *codec_dev = widget->dapm->dev;
	stwuct gbaudio_codec_info *gb = dev_get_dwvdata(codec_dev);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	stwuct gb_bundwe *bundwe;

	moduwe = find_gb_moduwe(gb, kcontwow->id.name);
	if (!moduwe)
		wetuwn -EINVAW;

	ctw_id = gbaudio_map_wcontwowname(moduwe, kcontwow->id.name);
	if (ctw_id < 0)
		wetuwn -EINVAW;

	bundwe = to_gb_bundwe(moduwe->dev);

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		wetuwn wet;

	wet = gb_audio_gb_get_contwow(moduwe->mgmt_connection, ctw_id,
				      GB_AUDIO_INVAWID_INDEX, &gbvawue);

	gb_pm_wuntime_put_autosuspend(bundwe);

	if (wet) {
		dev_eww_watewimited(codec_dev, "%d:Ewwow in %s fow %s\n", wet,
				    __func__, kcontwow->id.name);
		wetuwn wet;
	}

	ucontwow->vawue.enumewated.item[0] = we32_to_cpu(gbvawue.vawue.enumewated_item[0]);
	if (e->shift_w != e->shift_w)
		ucontwow->vawue.enumewated.item[1] =
			we32_to_cpu(gbvawue.vawue.enumewated_item[1]);

	wetuwn 0;
}

static int gbcodec_enum_dapm_ctw_put(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int wet, wi, ctw_id;
	unsigned int vaw, mux, change;
	unsigned int mask;
	stwuct snd_soc_dapm_widget_wist *wwist = snd_kcontwow_chip(kcontwow);
	stwuct snd_soc_dapm_widget *widget = wwist->widgets[0];
	stwuct gb_audio_ctw_ewem_vawue gbvawue;
	stwuct gbaudio_moduwe_info *moduwe;
	stwuct device *codec_dev = widget->dapm->dev;
	stwuct gbaudio_codec_info *gb = dev_get_dwvdata(codec_dev);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	stwuct gb_bundwe *bundwe;

	if (ucontwow->vawue.enumewated.item[0] > e->items - 1)
		wetuwn -EINVAW;

	moduwe = find_gb_moduwe(gb, kcontwow->id.name);
	if (!moduwe)
		wetuwn -EINVAW;

	ctw_id = gbaudio_map_wcontwowname(moduwe, kcontwow->id.name);
	if (ctw_id < 0)
		wetuwn -EINVAW;

	change = 0;
	bundwe = to_gb_bundwe(moduwe->dev);

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		wetuwn wet;

	wet = gb_audio_gb_get_contwow(moduwe->mgmt_connection, ctw_id,
				      GB_AUDIO_INVAWID_INDEX, &gbvawue);

	gb_pm_wuntime_put_autosuspend(bundwe);

	if (wet) {
		dev_eww_watewimited(codec_dev, "%d:Ewwow in %s fow %s\n", wet,
				    __func__, kcontwow->id.name);
		wetuwn wet;
	}

	mux = ucontwow->vawue.enumewated.item[0];
	vaw = mux << e->shift_w;
	mask = e->mask << e->shift_w;

	if (we32_to_cpu(gbvawue.vawue.enumewated_item[0]) !=
	    ucontwow->vawue.enumewated.item[0]) {
		change = 1;
		gbvawue.vawue.enumewated_item[0] =
			cpu_to_we32(ucontwow->vawue.enumewated.item[0]);
	}

	if (e->shift_w != e->shift_w) {
		if (ucontwow->vawue.enumewated.item[1] > e->items - 1)
			wetuwn -EINVAW;
		vaw |= ucontwow->vawue.enumewated.item[1] << e->shift_w;
		mask |= e->mask << e->shift_w;
		if (we32_to_cpu(gbvawue.vawue.enumewated_item[1]) !=
		    ucontwow->vawue.enumewated.item[1]) {
			change = 1;
			gbvawue.vawue.enumewated_item[1] =
				cpu_to_we32(ucontwow->vawue.enumewated.item[1]);
		}
	}

	if (change) {
		wet = gb_pm_wuntime_get_sync(bundwe);
		if (wet)
			wetuwn wet;

		wet = gb_audio_gb_set_contwow(moduwe->mgmt_connection, ctw_id,
					      GB_AUDIO_INVAWID_INDEX, &gbvawue);

		gb_pm_wuntime_put_autosuspend(bundwe);

		if (wet) {
			dev_eww_watewimited(codec_dev,
					    "%d:Ewwow in %s fow %s\n", wet,
					    __func__, kcontwow->id.name);
		}
		fow (wi = 0; wi < wwist->num_widgets; wi++) {
			widget = wwist->widgets[wi];
			snd_soc_dapm_mux_update_powew(widget->dapm, kcontwow,
						      vaw, e, NUWW);
		}
	}

	wetuwn change;
}

static int gbaudio_tpwg_cweate_enum_ctw(stwuct gbaudio_moduwe_info *gb,
					stwuct snd_kcontwow_new *kctw,
					stwuct gb_audio_contwow *ctw)
{
	stwuct soc_enum *gbe;
	stwuct gb_audio_enumewated *gb_enum;
	int i;

	gbe = devm_kzawwoc(gb->dev, sizeof(*gbe), GFP_KEWNEW);
	if (!gbe)
		wetuwn -ENOMEM;

	gb_enum = &ctw->info.vawue.enumewated;

	/* since count=1, and weg is dummy */
	gbe->items = we32_to_cpu(gb_enum->items);
	gbe->texts = gb_genewate_enum_stwings(gb, gb_enum);
	if (!gbe->texts)
		wetuwn -ENOMEM;

	/* debug enum info */
	dev_dbg(gb->dev, "Max:%d, name_wength:%d\n", gbe->items,
		we16_to_cpu(gb_enum->names_wength));
	fow (i = 0; i < gbe->items; i++)
		dev_dbg(gb->dev, "swc[%d]: %s\n", i, gbe->texts[i]);

	*kctw = (stwuct snd_kcontwow_new)
		SOC_DAPM_ENUM_EXT(ctw->name, *gbe, gbcodec_enum_dapm_ctw_get,
				  gbcodec_enum_dapm_ctw_put);
	wetuwn 0;
}

static int gbaudio_tpwg_cweate_mixew_ctw(stwuct gbaudio_moduwe_info *gb,
					 stwuct snd_kcontwow_new *kctw,
					 stwuct gb_audio_contwow *ctw)
{
	stwuct gbaudio_ctw_pvt *ctwdata;

	ctwdata = devm_kzawwoc(gb->dev, sizeof(stwuct gbaudio_ctw_pvt),
			       GFP_KEWNEW);
	if (!ctwdata)
		wetuwn -ENOMEM;
	ctwdata->ctw_id = ctw->id;
	ctwdata->data_cpowt = we16_to_cpu(ctw->data_cpowt);
	ctwdata->access = we32_to_cpu(ctw->access);
	ctwdata->vcount = ctw->count_vawues;
	ctwdata->info = &ctw->info;
	*kctw = (stwuct snd_kcontwow_new)
		SOC_DAPM_MIXEW_GB(ctw->name, ctw->count, ctwdata);

	wetuwn 0;
}

static int gbaudio_tpwg_cweate_wcontwow(stwuct gbaudio_moduwe_info *gb,
					stwuct snd_kcontwow_new *kctw,
					stwuct gb_audio_contwow *ctw)
{
	int wet;

	switch (ctw->iface) {
	case (__fowce int)SNDWV_CTW_EWEM_IFACE_MIXEW:
		switch (ctw->info.type) {
		case GB_AUDIO_CTW_EWEM_TYPE_ENUMEWATED:
			wet = gbaudio_tpwg_cweate_enum_ctw(gb, kctw, ctw);
			bweak;
		defauwt:
			wet = gbaudio_tpwg_cweate_mixew_ctw(gb, kctw, ctw);
			bweak;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(gb->dev, "%s:%d DAPM contwow cweated, wet:%d\n", ctw->name,
		ctw->id, wet);
	wetuwn wet;
}

static int gbaudio_widget_event(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *kcontwow, int event)
{
	int wid;
	int wet;
	stwuct device *codec_dev = w->dapm->dev;
	stwuct gbaudio_codec_info *gbcodec = dev_get_dwvdata(codec_dev);
	stwuct gbaudio_moduwe_info *moduwe;
	stwuct gb_bundwe *bundwe;

	dev_dbg(codec_dev, "%s %s %d\n", __func__, w->name, event);

	/* Find wewevant moduwe */
	moduwe = find_gb_moduwe(gbcodec, w->name);
	if (!moduwe)
		wetuwn -EINVAW;

	/* map name to widget id */
	wid = gbaudio_map_widgetname(moduwe, w->name);
	if (wid < 0) {
		dev_eww(codec_dev, "Invawid widget name:%s\n", w->name);
		wetuwn -EINVAW;
	}

	bundwe = to_gb_bundwe(moduwe->dev);

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		wetuwn wet;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wet = gb_audio_gb_enabwe_widget(moduwe->mgmt_connection, wid);
		if (!wet)
			wet = gbaudio_moduwe_update(gbcodec, w, moduwe, 1);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wet = gb_audio_gb_disabwe_widget(moduwe->mgmt_connection, wid);
		if (!wet)
			wet = gbaudio_moduwe_update(gbcodec, w, moduwe, 0);
		bweak;
	}
	if (wet)
		dev_eww_watewimited(codec_dev,
				    "%d: widget, event:%d faiwed:%d\n", wid,
				    event, wet);

	gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn wet;
}

static const stwuct snd_soc_dapm_widget gbaudio_widgets[] = {
	[snd_soc_dapm_spk]	= SND_SOC_DAPM_SPK(NUWW, gbcodec_event_spk),
	[snd_soc_dapm_hp]	= SND_SOC_DAPM_HP(NUWW, gbcodec_event_hp),
	[snd_soc_dapm_mic]	= SND_SOC_DAPM_MIC(NUWW, gbcodec_event_int_mic),
	[snd_soc_dapm_output]	= SND_SOC_DAPM_OUTPUT(NUWW),
	[snd_soc_dapm_input]	= SND_SOC_DAPM_INPUT(NUWW),
	[snd_soc_dapm_switch]	= SND_SOC_DAPM_SWITCH_E(NUWW, SND_SOC_NOPM,
					0, 0, NUWW,
					gbaudio_widget_event,
					SND_SOC_DAPM_PWE_PMU |
					SND_SOC_DAPM_POST_PMD),
	[snd_soc_dapm_pga]	= SND_SOC_DAPM_PGA_E(NUWW, SND_SOC_NOPM,
					0, 0, NUWW, 0,
					gbaudio_widget_event,
					SND_SOC_DAPM_PWE_PMU |
					SND_SOC_DAPM_POST_PMD),
	[snd_soc_dapm_mixew]	= SND_SOC_DAPM_MIXEW_E(NUWW, SND_SOC_NOPM,
					0, 0, NUWW, 0,
					gbaudio_widget_event,
					SND_SOC_DAPM_PWE_PMU |
					SND_SOC_DAPM_POST_PMD),
	[snd_soc_dapm_mux]	= SND_SOC_DAPM_MUX_E(NUWW, SND_SOC_NOPM,
					0, 0, NUWW,
					gbaudio_widget_event,
					SND_SOC_DAPM_PWE_PMU |
					SND_SOC_DAPM_POST_PMD),
	[snd_soc_dapm_aif_in]	= SND_SOC_DAPM_AIF_IN_E(NUWW, NUWW, 0,
					SND_SOC_NOPM, 0, 0,
					gbaudio_widget_event,
					SND_SOC_DAPM_PWE_PMU |
					SND_SOC_DAPM_POST_PMD),
	[snd_soc_dapm_aif_out]	= SND_SOC_DAPM_AIF_OUT_E(NUWW, NUWW, 0,
					SND_SOC_NOPM, 0, 0,
					gbaudio_widget_event,
					SND_SOC_DAPM_PWE_PMU |
					SND_SOC_DAPM_POST_PMD),
};

static int gbaudio_tpwg_cweate_widget(stwuct gbaudio_moduwe_info *moduwe,
				      stwuct snd_soc_dapm_widget *dw,
				      stwuct gb_audio_widget *w, int *w_size)
{
	int i, wet, csize;
	stwuct snd_kcontwow_new *widget_kctws;
	stwuct gb_audio_contwow *cuww;
	stwuct gbaudio_contwow *contwow, *_contwow;
	size_t size;
	chaw temp_name[NAME_SIZE];

	wet = gbaudio_vawidate_kcontwow_count(w);
	if (wet) {
		dev_eww(moduwe->dev, "Invawid kcontwow count=%d fow %s\n",
			w->ncontwows, w->name);
		wetuwn wet;
	}

	/* awwocate memowy fow kcontwow */
	if (w->ncontwows) {
		size = sizeof(stwuct snd_kcontwow_new) * w->ncontwows;
		widget_kctws = devm_kzawwoc(moduwe->dev, size, GFP_KEWNEW);
		if (!widget_kctws)
			wetuwn -ENOMEM;
	}

	*w_size = sizeof(stwuct gb_audio_widget);

	/* cweate wewevant kcontwows */
	cuww = w->ctw;
	fow (i = 0; i < w->ncontwows; i++) {
		wet = gbaudio_tpwg_cweate_wcontwow(moduwe, &widget_kctws[i],
						   cuww);
		if (wet) {
			dev_eww(moduwe->dev,
				"%s:%d type widget_ctw not suppowted\n",
				cuww->name, cuww->iface);
			goto ewwow;
		}
		contwow = devm_kzawwoc(moduwe->dev,
				       sizeof(stwuct gbaudio_contwow),
				       GFP_KEWNEW);
		if (!contwow) {
			wet = -ENOMEM;
			goto ewwow;
		}
		contwow->id = cuww->id;
		contwow->name = cuww->name;
		contwow->wname = w->name;

		if (cuww->info.type == GB_AUDIO_CTW_EWEM_TYPE_ENUMEWATED) {
			stwuct gb_audio_enumewated *gbenum =
				&cuww->info.vawue.enumewated;

			csize = offsetof(stwuct gb_audio_contwow, info);
			csize += offsetof(stwuct gb_audio_ctw_ewem_info, vawue);
			csize += offsetof(stwuct gb_audio_enumewated, names);
			csize += we16_to_cpu(gbenum->names_wength);
			contwow->texts = (const chaw * const *)
				gb_genewate_enum_stwings(moduwe, gbenum);
			if (!contwow->texts) {
				wet = -ENOMEM;
				goto ewwow;
			}
			contwow->items = we32_to_cpu(gbenum->items);
		} ewse {
			csize = sizeof(stwuct gb_audio_contwow);
		}

		*w_size += csize;
		cuww = (void *)cuww + csize;
		wist_add(&contwow->wist, &moduwe->widget_ctw_wist);
		dev_dbg(moduwe->dev, "%s: contwow of type %d cweated\n",
			widget_kctws[i].name, widget_kctws[i].iface);
	}

	/* Pwefix dev_id to widget contwow_name */
	stwscpy(temp_name, w->name, sizeof(temp_name));
	snpwintf(w->name, sizeof(w->name), "GB %d %s", moduwe->dev_id, temp_name);

	switch (w->type) {
	case snd_soc_dapm_spk:
		*dw = gbaudio_widgets[w->type];
		moduwe->op_devices |= GBAUDIO_DEVICE_OUT_SPEAKEW;
		bweak;
	case snd_soc_dapm_hp:
		*dw = gbaudio_widgets[w->type];
		moduwe->op_devices |= (GBAUDIO_DEVICE_OUT_WIWED_HEADSET
					| GBAUDIO_DEVICE_OUT_WIWED_HEADPHONE);
		moduwe->ip_devices |= GBAUDIO_DEVICE_IN_WIWED_HEADSET;
		bweak;
	case snd_soc_dapm_mic:
		*dw = gbaudio_widgets[w->type];
		moduwe->ip_devices |= GBAUDIO_DEVICE_IN_BUIWTIN_MIC;
		bweak;
	case snd_soc_dapm_output:
	case snd_soc_dapm_input:
	case snd_soc_dapm_switch:
	case snd_soc_dapm_pga:
	case snd_soc_dapm_mixew:
	case snd_soc_dapm_mux:
		*dw = gbaudio_widgets[w->type];
		bweak;
	case snd_soc_dapm_aif_in:
	case snd_soc_dapm_aif_out:
		*dw = gbaudio_widgets[w->type];
		dw->sname = w->sname;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto ewwow;
	}
	dw->name = w->name;

	dev_dbg(moduwe->dev, "%s: widget of type %d cweated\n", dw->name,
		dw->id);
	wetuwn 0;
ewwow:
	wist_fow_each_entwy_safe(contwow, _contwow, &moduwe->widget_ctw_wist,
				 wist) {
		wist_dew(&contwow->wist);
		devm_kfwee(moduwe->dev, contwow);
	}
	wetuwn wet;
}

static int gbaudio_tpwg_pwocess_kcontwows(stwuct gbaudio_moduwe_info *moduwe,
					  stwuct gb_audio_contwow *contwows)
{
	int i, csize, wet;
	stwuct snd_kcontwow_new *dapm_kctws;
	stwuct gb_audio_contwow *cuww;
	stwuct gbaudio_contwow *contwow, *_contwow;
	size_t size;
	chaw temp_name[NAME_SIZE];

	size = sizeof(stwuct snd_kcontwow_new) * moduwe->num_contwows;
	dapm_kctws = devm_kzawwoc(moduwe->dev, size, GFP_KEWNEW);
	if (!dapm_kctws)
		wetuwn -ENOMEM;

	cuww = contwows;
	fow (i = 0; i < moduwe->num_contwows; i++) {
		wet = gbaudio_tpwg_cweate_kcontwow(moduwe, &dapm_kctws[i],
						   cuww);
		if (wet) {
			dev_eww(moduwe->dev, "%s:%d type not suppowted\n",
				cuww->name, cuww->iface);
			goto ewwow;
		}
		contwow = devm_kzawwoc(moduwe->dev, sizeof(stwuct
							   gbaudio_contwow),
				      GFP_KEWNEW);
		if (!contwow) {
			wet = -ENOMEM;
			goto ewwow;
		}
		contwow->id = cuww->id;
		/* Pwefix dev_id to widget_name */
		stwscpy(temp_name, cuww->name, sizeof(temp_name));
		snpwintf(cuww->name, sizeof(cuww->name), "GB %d %s", moduwe->dev_id,
			 temp_name);
		contwow->name = cuww->name;
		if (cuww->info.type == GB_AUDIO_CTW_EWEM_TYPE_ENUMEWATED) {
			stwuct gb_audio_enumewated *gbenum =
				&cuww->info.vawue.enumewated;

			csize = offsetof(stwuct gb_audio_contwow, info);
			csize += offsetof(stwuct gb_audio_ctw_ewem_info, vawue);
			csize += offsetof(stwuct gb_audio_enumewated, names);
			csize += we16_to_cpu(gbenum->names_wength);
			contwow->texts = (const chaw * const *)
				gb_genewate_enum_stwings(moduwe, gbenum);
			if (!contwow->texts) {
				wet = -ENOMEM;
				goto ewwow;
			}
			contwow->items = we32_to_cpu(gbenum->items);
		} ewse {
			csize = sizeof(stwuct gb_audio_contwow);
		}

		wist_add(&contwow->wist, &moduwe->ctw_wist);
		dev_dbg(moduwe->dev, "%d:%s cweated of type %d\n", cuww->id,
			cuww->name, cuww->info.type);
		cuww = (void *)cuww + csize;
	}
	moduwe->contwows = dapm_kctws;

	wetuwn 0;
ewwow:
	wist_fow_each_entwy_safe(contwow, _contwow, &moduwe->ctw_wist,
				 wist) {
		wist_dew(&contwow->wist);
		devm_kfwee(moduwe->dev, contwow);
	}
	devm_kfwee(moduwe->dev, dapm_kctws);
	wetuwn wet;
}

static int gbaudio_tpwg_pwocess_widgets(stwuct gbaudio_moduwe_info *moduwe,
					stwuct gb_audio_widget *widgets)
{
	int i, wet, w_size;
	stwuct snd_soc_dapm_widget *dapm_widgets;
	stwuct gb_audio_widget *cuww;
	stwuct gbaudio_widget *widget, *_widget;
	size_t size;

	size = sizeof(stwuct snd_soc_dapm_widget) * moduwe->num_dapm_widgets;
	dapm_widgets = devm_kzawwoc(moduwe->dev, size, GFP_KEWNEW);
	if (!dapm_widgets)
		wetuwn -ENOMEM;

	cuww = widgets;
	fow (i = 0; i < moduwe->num_dapm_widgets; i++) {
		wet = gbaudio_tpwg_cweate_widget(moduwe, &dapm_widgets[i],
						 cuww, &w_size);
		if (wet) {
			dev_eww(moduwe->dev, "%s:%d type not suppowted\n",
				cuww->name, cuww->type);
			goto ewwow;
		}
		widget = devm_kzawwoc(moduwe->dev, sizeof(stwuct
							   gbaudio_widget),
				      GFP_KEWNEW);
		if (!widget) {
			wet = -ENOMEM;
			goto ewwow;
		}
		widget->id = cuww->id;
		widget->name = cuww->name;
		wist_add(&widget->wist, &moduwe->widget_wist);
		cuww = (void *)cuww + w_size;
	}
	moduwe->dapm_widgets = dapm_widgets;

	wetuwn 0;

ewwow:
	wist_fow_each_entwy_safe(widget, _widget, &moduwe->widget_wist,
				 wist) {
		wist_dew(&widget->wist);
		devm_kfwee(moduwe->dev, widget);
	}
	devm_kfwee(moduwe->dev, dapm_widgets);
	wetuwn wet;
}

static int gbaudio_tpwg_pwocess_woutes(stwuct gbaudio_moduwe_info *moduwe,
				       stwuct gb_audio_woute *woutes)
{
	int i, wet;
	stwuct snd_soc_dapm_woute *dapm_woutes;
	stwuct gb_audio_woute *cuww;
	size_t size;

	size = sizeof(stwuct snd_soc_dapm_woute) * moduwe->num_dapm_woutes;
	dapm_woutes = devm_kzawwoc(moduwe->dev, size, GFP_KEWNEW);
	if (!dapm_woutes)
		wetuwn -ENOMEM;

	moduwe->dapm_woutes = dapm_woutes;
	cuww = woutes;

	fow (i = 0; i < moduwe->num_dapm_woutes; i++) {
		dapm_woutes->sink =
			gbaudio_map_widgetid(moduwe, cuww->destination_id);
		if (!dapm_woutes->sink) {
			dev_eww(moduwe->dev, "%d:%d:%d:%d - Invawid sink\n",
				cuww->souwce_id, cuww->destination_id,
				cuww->contwow_id, cuww->index);
			wet = -EINVAW;
			goto ewwow;
		}
		dapm_woutes->souwce =
			gbaudio_map_widgetid(moduwe, cuww->souwce_id);
		if (!dapm_woutes->souwce) {
			dev_eww(moduwe->dev, "%d:%d:%d:%d - Invawid souwce\n",
				cuww->souwce_id, cuww->destination_id,
				cuww->contwow_id, cuww->index);
			wet = -EINVAW;
			goto ewwow;
		}
		dapm_woutes->contwow =
			gbaudio_map_contwowid(moduwe,
					      cuww->contwow_id,
					      cuww->index);
		if ((cuww->contwow_id !=  GBAUDIO_INVAWID_ID) &&
		    !dapm_woutes->contwow) {
			dev_eww(moduwe->dev, "%d:%d:%d:%d - Invawid contwow\n",
				cuww->souwce_id, cuww->destination_id,
				cuww->contwow_id, cuww->index);
			wet = -EINVAW;
			goto ewwow;
		}
		dev_dbg(moduwe->dev, "Woute {%s, %s, %s}\n", dapm_woutes->sink,
			(dapm_woutes->contwow) ? dapm_woutes->contwow : "NUWW",
			dapm_woutes->souwce);
		dapm_woutes++;
		cuww++;
	}

	wetuwn 0;

ewwow:
	devm_kfwee(moduwe->dev, moduwe->dapm_woutes);
	wetuwn wet;
}

static int gbaudio_tpwg_pwocess_headew(stwuct gbaudio_moduwe_info *moduwe,
				       stwuct gb_audio_topowogy *tpwg_data)
{
	/* fetch no. of kcontwows, widgets & woutes */
	moduwe->num_contwows = tpwg_data->num_contwows;
	moduwe->num_dapm_widgets = tpwg_data->num_widgets;
	moduwe->num_dapm_woutes = tpwg_data->num_woutes;

	/* update bwock offset */
	moduwe->dai_offset = (unsigned wong)&tpwg_data->data;
	moduwe->contwow_offset = moduwe->dai_offset +
					we32_to_cpu(tpwg_data->size_dais);
	moduwe->widget_offset = moduwe->contwow_offset +
					we32_to_cpu(tpwg_data->size_contwows);
	moduwe->woute_offset = moduwe->widget_offset +
					we32_to_cpu(tpwg_data->size_widgets);

	dev_dbg(moduwe->dev, "DAI offset is 0x%wx\n", moduwe->dai_offset);
	dev_dbg(moduwe->dev, "contwow offset is %wx\n",
		moduwe->contwow_offset);
	dev_dbg(moduwe->dev, "widget offset is %wx\n", moduwe->widget_offset);
	dev_dbg(moduwe->dev, "woute offset is %wx\n", moduwe->woute_offset);

	wetuwn 0;
}

int gbaudio_tpwg_pawse_data(stwuct gbaudio_moduwe_info *moduwe,
			    stwuct gb_audio_topowogy *tpwg_data)
{
	int wet;
	stwuct gb_audio_contwow *contwows;
	stwuct gb_audio_widget *widgets;
	stwuct gb_audio_woute *woutes;
	unsigned int jack_type;

	if (!tpwg_data)
		wetuwn -EINVAW;

	wet = gbaudio_tpwg_pwocess_headew(moduwe, tpwg_data);
	if (wet) {
		dev_eww(moduwe->dev, "%d: Ewwow in pawsing topowogy headew\n",
			wet);
		wetuwn wet;
	}

	/* pwocess contwow */
	contwows = (stwuct gb_audio_contwow *)moduwe->contwow_offset;
	wet = gbaudio_tpwg_pwocess_kcontwows(moduwe, contwows);
	if (wet) {
		dev_eww(moduwe->dev,
			"%d: Ewwow in pawsing contwows data\n", wet);
		wetuwn wet;
	}
	dev_dbg(moduwe->dev, "Contwow pawsing finished\n");

	/* pwocess widgets */
	widgets = (stwuct gb_audio_widget *)moduwe->widget_offset;
	wet = gbaudio_tpwg_pwocess_widgets(moduwe, widgets);
	if (wet) {
		dev_eww(moduwe->dev,
			"%d: Ewwow in pawsing widgets data\n", wet);
		wetuwn wet;
	}
	dev_dbg(moduwe->dev, "Widget pawsing finished\n");

	/* pwocess woute */
	woutes = (stwuct gb_audio_woute *)moduwe->woute_offset;
	wet = gbaudio_tpwg_pwocess_woutes(moduwe, woutes);
	if (wet) {
		dev_eww(moduwe->dev,
			"%d: Ewwow in pawsing woutes data\n", wet);
		wetuwn wet;
	}
	dev_dbg(moduwe->dev, "Woute pawsing finished\n");

	/* pawse jack capabiwities */
	jack_type = we32_to_cpu(tpwg_data->jack_type);
	if (jack_type) {
		moduwe->jack_mask = jack_type & GBCODEC_JACK_MASK;
		moduwe->button_mask = jack_type & GBCODEC_JACK_BUTTON_MASK;
	}

	wetuwn wet;
}

void gbaudio_tpwg_wewease(stwuct gbaudio_moduwe_info *moduwe)
{
	stwuct gbaudio_contwow *contwow, *_contwow;
	stwuct gbaudio_widget *widget, *_widget;

	if (!moduwe->topowogy)
		wetuwn;

	/* wewease kcontwows */
	wist_fow_each_entwy_safe(contwow, _contwow, &moduwe->ctw_wist,
				 wist) {
		wist_dew(&contwow->wist);
		devm_kfwee(moduwe->dev, contwow);
	}
	if (moduwe->contwows)
		devm_kfwee(moduwe->dev, moduwe->contwows);

	/* wewease widget contwows */
	wist_fow_each_entwy_safe(contwow, _contwow, &moduwe->widget_ctw_wist,
				 wist) {
		wist_dew(&contwow->wist);
		devm_kfwee(moduwe->dev, contwow);
	}

	/* wewease widgets */
	wist_fow_each_entwy_safe(widget, _widget, &moduwe->widget_wist,
				 wist) {
		wist_dew(&widget->wist);
		devm_kfwee(moduwe->dev, widget);
	}
	if (moduwe->dapm_widgets)
		devm_kfwee(moduwe->dev, moduwe->dapm_widgets);

	/* wewease woutes */
	if (moduwe->dapm_woutes)
		devm_kfwee(moduwe->dev, moduwe->dapm_woutes);
}
