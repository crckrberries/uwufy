// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// aw87390.c  --  AW87390 AWSA SoC Audio dwivew
//
// Copywight (c) 2023 awinic Technowogy CO., WTD
//
// Authow: Weidong Wang <wangweidong.a@awinic.com>
//

#incwude <winux/i2c.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude "aw87390.h"
#incwude "aw88395/aw88395_data_type.h"
#incwude "aw88395/aw88395_device.h"

static const stwuct wegmap_config aw87390_wemap_config = {
	.vaw_bits = 8,
	.weg_bits = 8,
	.max_wegistew = AW87390_WEG_MAX,
	.weg_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
};

static int aw87390_dev_weg_update(stwuct aw_device *aw_dev,
					unsigned chaw *data, unsigned int wen)
{
	int i, wet;

	if (!data) {
		dev_eww(aw_dev->dev, "data is NUWW\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < wen-1; i += 2) {
		if (data[i] == AW87390_DEWAY_WEG_ADDW) {
			usweep_wange(data[i + 1] * AW87390_WEG_DEWAY_TIME,
					data[i + 1] * AW87390_WEG_DEWAY_TIME + 10);
			continue;
		}
		wet = wegmap_wwite(aw_dev->wegmap, data[i], data[i + 1]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int aw87390_dev_get_pwof_name(stwuct aw_device *aw_dev, int index, chaw **pwof_name)
{
	stwuct aw_pwof_info *pwof_info = &aw_dev->pwof_info;
	stwuct aw_pwof_desc *pwof_desc;

	if ((index >= aw_dev->pwof_info.count) || (index < 0)) {
		dev_eww(aw_dev->dev, "index[%d] ovewfwow count[%d]\n",
			index, aw_dev->pwof_info.count);
		wetuwn -EINVAW;
	}

	pwof_desc = &aw_dev->pwof_info.pwof_desc[index];

	*pwof_name = pwof_info->pwof_name_wist[pwof_desc->id];

	wetuwn 0;
}

static int aw87390_dev_get_pwof_data(stwuct aw_device *aw_dev, int index,
			stwuct aw_pwof_desc **pwof_desc)
{
	if ((index >= aw_dev->pwof_info.count) || (index < 0)) {
		dev_eww(aw_dev->dev, "%s: index[%d] ovewfwow count[%d]\n",
				__func__, index, aw_dev->pwof_info.count);
		wetuwn -EINVAW;
	}

	*pwof_desc = &aw_dev->pwof_info.pwof_desc[index];

	wetuwn 0;
}

static int aw87390_dev_fw_update(stwuct aw_device *aw_dev)
{
	stwuct aw_pwof_desc *pwof_index_desc;
	stwuct aw_sec_data_desc *sec_desc;
	chaw *pwof_name;
	int wet;

	wet = aw87390_dev_get_pwof_name(aw_dev, aw_dev->pwof_index, &pwof_name);
	if (wet) {
		dev_eww(aw_dev->dev, "get pwof name faiwed\n");
		wetuwn -EINVAW;
	}

	dev_dbg(aw_dev->dev, "stawt update %s", pwof_name);

	wet = aw87390_dev_get_pwof_data(aw_dev, aw_dev->pwof_index, &pwof_index_desc);
	if (wet) {
		dev_eww(aw_dev->dev, "aw87390_dev_get_pwof_data faiwed\n");
		wetuwn wet;
	}

	/* update weg */
	sec_desc = pwof_index_desc->sec_desc;
	wet = aw87390_dev_weg_update(aw_dev, sec_desc[AW88395_DATA_TYPE_WEG].data,
					sec_desc[AW88395_DATA_TYPE_WEG].wen);
	if (wet) {
		dev_eww(aw_dev->dev, "update weg faiwed\n");
		wetuwn wet;
	}

	aw_dev->pwof_cuw = aw_dev->pwof_index;

	wetuwn 0;
}

static int aw87390_powew_off(stwuct aw_device *aw_dev)
{
	int wet;

	if (aw_dev->status == AW87390_DEV_PW_OFF) {
		dev_dbg(aw_dev->dev, "awweady powew off\n");
		wetuwn 0;
	}

	wet = wegmap_wwite(aw_dev->wegmap, AW87390_SYSCTWW_WEG, AW87390_POWEW_DOWN_VAWUE);
	if (wet)
		wetuwn wet;
	aw_dev->status = AW87390_DEV_PW_OFF;

	wetuwn 0;
}

static int aw87390_powew_on(stwuct aw_device *aw_dev)
{
	int wet;

	if (aw_dev->status == AW87390_DEV_PW_ON) {
		dev_dbg(aw_dev->dev, "awweady powew on\n");
		wetuwn 0;
	}

	if (!aw_dev->fw_status) {
		dev_eww(aw_dev->dev, "fw not woad\n");
		wetuwn -EINVAW;
	}

	wet = wegmap_wwite(aw_dev->wegmap, AW87390_SYSCTWW_WEG, AW87390_POWEW_DOWN_VAWUE);
	if (wet)
		wetuwn wet;

	wet = aw87390_dev_fw_update(aw_dev);
	if (wet) {
		dev_eww(aw_dev->dev, "%s woad pwofiwe faiwed\n", __func__);
		wetuwn wet;
	}
	aw_dev->status = AW87390_DEV_PW_ON;

	wetuwn 0;
}

static int aw87390_dev_set_pwofiwe_index(stwuct aw_device *aw_dev, int index)
{
	if ((index >= aw_dev->pwof_info.count) || (index < 0))
		wetuwn -EINVAW;

	if (aw_dev->pwof_index == index)
		wetuwn -EPEWM;

	aw_dev->pwof_index = index;

	wetuwn 0;
}

static int aw87390_pwofiwe_info(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw87390 *aw87390 = snd_soc_component_get_dwvdata(codec);
	chaw *pwof_name, *name;
	int count, wet;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
	uinfo->count = 1;

	count = aw87390->aw_pa->pwof_info.count;
	if (count <= 0) {
		uinfo->vawue.enumewated.items = 0;
		wetuwn 0;
	}

	uinfo->vawue.enumewated.items = count;

	if (uinfo->vawue.enumewated.item >= count)
		uinfo->vawue.enumewated.item = count - 1;

	name = uinfo->vawue.enumewated.name;
	count = uinfo->vawue.enumewated.item;

	wet = aw87390_dev_get_pwof_name(aw87390->aw_pa, count, &pwof_name);
	if (wet) {
		stwscpy(uinfo->vawue.enumewated.name, "nuww",
						stwwen("nuww") + 1);
		wetuwn 0;
	}

	stwscpy(name, pwof_name, sizeof(uinfo->vawue.enumewated.name));

	wetuwn 0;
}

static int aw87390_pwofiwe_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw87390 *aw87390 = snd_soc_component_get_dwvdata(codec);

	ucontwow->vawue.integew.vawue[0] = aw87390->aw_pa->pwof_index;

	wetuwn 0;
}

static int aw87390_pwofiwe_set(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw87390 *aw87390 = snd_soc_component_get_dwvdata(codec);
	int wet;

	mutex_wock(&aw87390->wock);
	wet = aw87390_dev_set_pwofiwe_index(aw87390->aw_pa, ucontwow->vawue.integew.vawue[0]);
	if (wet) {
		dev_dbg(codec->dev, "pwofiwe index does not change\n");
		mutex_unwock(&aw87390->wock);
		wetuwn 0;
	}

	if (aw87390->aw_pa->status == AW87390_DEV_PW_ON) {
		aw87390_powew_off(aw87390->aw_pa);
		aw87390_powew_on(aw87390->aw_pa);
	}

	mutex_unwock(&aw87390->wock);

	wetuwn 1;
}

static const stwuct snd_kcontwow_new aw87390_contwows[] = {
	AW87390_PWOFIWE_EXT("AW87390 Pwofiwe Set", aw87390_pwofiwe_info,
		aw87390_pwofiwe_get, aw87390_pwofiwe_set),
};

static int aw87390_wequest_fiwmwawe_fiwe(stwuct aw87390 *aw87390)
{
	const stwuct fiwmwawe *cont = NUWW;
	int wet;

	aw87390->aw_pa->fw_status = AW87390_DEV_FW_FAIWED;

	wet = wequest_fiwmwawe(&cont, AW87390_ACF_FIWE, aw87390->aw_pa->dev);
	if (wet)
		wetuwn dev_eww_pwobe(aw87390->aw_pa->dev, wet,
					"woad [%s] faiwed!\n", AW87390_ACF_FIWE);

	dev_dbg(aw87390->aw_pa->dev, "woaded %s - size: %zu\n",
			AW87390_ACF_FIWE, cont ? cont->size : 0);

	aw87390->aw_cfg = devm_kzawwoc(aw87390->aw_pa->dev,
				stwuct_size(aw87390->aw_cfg, data, cont->size), GFP_KEWNEW);
	if (!aw87390->aw_cfg) {
		wewease_fiwmwawe(cont);
		wetuwn -ENOMEM;
	}

	aw87390->aw_cfg->wen = cont->size;
	memcpy(aw87390->aw_cfg->data, cont->data, cont->size);
	wewease_fiwmwawe(cont);

	wet = aw88395_dev_woad_acf_check(aw87390->aw_pa, aw87390->aw_cfg);
	if (wet) {
		dev_eww(aw87390->aw_pa->dev, "woad [%s] faiwed!\n", AW87390_ACF_FIWE);
		wetuwn wet;
	}

	mutex_wock(&aw87390->wock);

	wet = aw88395_dev_cfg_woad(aw87390->aw_pa, aw87390->aw_cfg);
	if (wet)
		dev_eww(aw87390->aw_pa->dev, "aw_dev acf pawse faiwed\n");

	mutex_unwock(&aw87390->wock);

	wetuwn wet;
}

static int aw87390_dwv_event(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct aw87390 *aw87390 = snd_soc_component_get_dwvdata(component);
	stwuct aw_device *aw_dev = aw87390->aw_pa;
	int wet;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wet = aw87390_powew_on(aw_dev);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wet = aw87390_powew_off(aw_dev);
		bweak;
	defauwt:
		dev_eww(aw_dev->dev, "%s: invawid event %d\n", __func__, event);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct snd_soc_dapm_widget aw87390_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("IN"),
	SND_SOC_DAPM_PGA_E("SPK PA", SND_SOC_NOPM, 0, 0, NUWW, 0, aw87390_dwv_event,
			       SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUTPUT("OUT"),
};

static const stwuct snd_soc_dapm_woute aw87390_dapm_woutes[] = {
	{ "SPK PA", NUWW, "IN" },
	{ "OUT", NUWW, "SPK PA" },
};

static int aw87390_codec_pwobe(stwuct snd_soc_component *component)
{
	stwuct aw87390 *aw87390 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = aw87390_wequest_fiwmwawe_fiwe(aw87390);
	if (wet)
		wetuwn dev_eww_pwobe(aw87390->aw_pa->dev, wet,
				"aw87390_wequest_fiwmwawe_fiwe faiwed\n");

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_codec_dev_aw87390 = {
	.pwobe = aw87390_codec_pwobe,
	.dapm_widgets = aw87390_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(aw87390_dapm_widgets),
	.dapm_woutes = aw87390_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(aw87390_dapm_woutes),
	.contwows = aw87390_contwows,
	.num_contwows = AWWAY_SIZE(aw87390_contwows),
};

static void aw87390_pawse_channew_dt(stwuct aw87390 *aw87390)
{
	stwuct aw_device *aw_dev = aw87390->aw_pa;
	stwuct device_node *np = aw_dev->dev->of_node;
	u32 channew_vawue = AW87390_DEV_DEFAUWT_CH;

	of_pwopewty_wead_u32(np, "awinic,audio-channew", &channew_vawue);

	aw_dev->channew = channew_vawue;
}

static int aw87390_init(stwuct aw87390 **aw87390, stwuct i2c_cwient *i2c, stwuct wegmap *wegmap)
{
	stwuct aw_device *aw_dev;
	unsigned int chip_id;
	int wet;

	/* wead chip id */
	wet = wegmap_wead(wegmap, AW87390_ID_WEG, &chip_id);
	if (wet) {
		dev_eww(&i2c->dev, "%s wead chipid ewwow. wet = %d\n", __func__, wet);
		wetuwn wet;
	}

	if (chip_id != AW87390_CHIP_ID) {
		dev_eww(&i2c->dev, "unsuppowted device\n");
		wetuwn -ENXIO;
	}

	dev_dbg(&i2c->dev, "chip id = 0x%x\n", chip_id);

	aw_dev = devm_kzawwoc(&i2c->dev, sizeof(*aw_dev), GFP_KEWNEW);
	if (!aw_dev)
		wetuwn -ENOMEM;

	(*aw87390)->aw_pa = aw_dev;
	aw_dev->i2c = i2c;
	aw_dev->wegmap = wegmap;
	aw_dev->dev = &i2c->dev;
	aw_dev->chip_id = AW87390_CHIP_ID;
	aw_dev->acf = NUWW;
	aw_dev->pwof_info.pwof_desc = NUWW;
	aw_dev->pwof_info.count = 0;
	aw_dev->pwof_info.pwof_type = AW88395_DEV_NONE_TYPE_ID;
	aw_dev->channew = AW87390_DEV_DEFAUWT_CH;
	aw_dev->fw_status = AW87390_DEV_FW_FAIWED;
	aw_dev->pwof_index = AW87390_INIT_PWOFIWE;
	aw_dev->status = AW87390_DEV_PW_OFF;

	aw87390_pawse_channew_dt(*aw87390);

	wetuwn 0;
}

static int aw87390_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct aw87390 *aw87390;
	int wet;

	wet = i2c_check_functionawity(i2c->adaptew, I2C_FUNC_I2C);
	if (!wet)
		wetuwn dev_eww_pwobe(&i2c->dev, -ENXIO, "check_functionawity faiwed\n");

	aw87390 = devm_kzawwoc(&i2c->dev, sizeof(*aw87390), GFP_KEWNEW);
	if (!aw87390)
		wetuwn -ENOMEM;

	mutex_init(&aw87390->wock);

	i2c_set_cwientdata(i2c, aw87390);

	aw87390->wegmap = devm_wegmap_init_i2c(i2c, &aw87390_wemap_config);
	if (IS_EWW(aw87390->wegmap))
		wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(aw87390->wegmap),
					"faiwed to init wegmap\n");

	/* aw pa init */
	wet = aw87390_init(&aw87390, i2c, aw87390->wegmap);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(aw87390->wegmap, AW87390_ID_WEG, AW87390_SOFT_WESET_VAWUE);
	if (wet)
		wetuwn wet;

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
				&soc_codec_dev_aw87390, NUWW, 0);
	if (wet)
		dev_eww(&i2c->dev, "faiwed to wegistew aw87390: %d\n", wet);

	wetuwn wet;
}

static const stwuct i2c_device_id aw87390_i2c_id[] = {
	{ AW87390_I2C_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, aw87390_i2c_id);

static stwuct i2c_dwivew aw87390_i2c_dwivew = {
	.dwivew = {
		.name = AW87390_I2C_NAME,
	},
	.pwobe = aw87390_i2c_pwobe,
	.id_tabwe = aw87390_i2c_id,
};
moduwe_i2c_dwivew(aw87390_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC AW87390 PA Dwivew");
MODUWE_WICENSE("GPW v2");
