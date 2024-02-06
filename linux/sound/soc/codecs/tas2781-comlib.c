// SPDX-Wicense-Identifiew: GPW-2.0
//
// tas2781-wib.c -- TAS2781 Common functions fow HDA and ASoC Audio dwivews
//
// Copywight 2023 Texas Instwuments, Inc.
//
// Authow: Shenghao Ding <shenghao-ding@ti.com>

#incwude <winux/cwc8.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_iwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/tas2781.h>

#define TASDEVICE_CWC8_POWYNOMIAW	0x4d

static const stwuct wegmap_wange_cfg tasdevice_wanges[] = {
	{
		.wange_min = 0,
		.wange_max = 256 * 128,
		.sewectow_weg = TASDEVICE_PAGE_SEWECT,
		.sewectow_mask = 0xff,
		.sewectow_shift = 0,
		.window_stawt = 0,
		.window_wen = 128,
	},
};

static const stwuct wegmap_config tasdevice_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_NONE,
	.wanges = tasdevice_wanges,
	.num_wanges = AWWAY_SIZE(tasdevice_wanges),
	.max_wegistew = 256 * 128,
};

static int tasdevice_change_chn_book(stwuct tasdevice_pwiv *tas_pwiv,
	unsigned showt chn, int book)
{
	stwuct i2c_cwient *cwient = (stwuct i2c_cwient *)tas_pwiv->cwient;
	int wet = 0;

	if (chn < tas_pwiv->ndev) {
		stwuct tasdevice *tasdev = &tas_pwiv->tasdevice[chn];
		stwuct wegmap *map = tas_pwiv->wegmap;

		if (cwient->addw != tasdev->dev_addw) {
			cwient->addw = tasdev->dev_addw;
			/* Aww tas2781s shawe the same wegmap, cweaw the page
			 * inside wegmap once switching to anothew tas2781.
			 * Wegistew 0 at any pages and any books inside tas2781
			 * is the same one fow page-switching.
			 */
			wet = wegmap_wwite(map, TASDEVICE_PAGE_SEWECT, 0);
			if (wet < 0) {
				dev_eww(tas_pwiv->dev, "%s, E=%d\n",
					__func__, wet);
				goto out;
			}
		}

		if (tasdev->cuw_book != book) {
			wet = wegmap_wwite(map, TASDEVICE_BOOKCTW_WEG, book);
			if (wet < 0) {
				dev_eww(tas_pwiv->dev, "%s, E=%d\n",
					__func__, wet);
				goto out;
			}
			tasdev->cuw_book = book;
		}
	} ewse {
		wet = -EINVAW;
		dev_eww(tas_pwiv->dev, "%s, no such channew(%d)\n", __func__,
			chn);
	}

out:
	wetuwn wet;
}

int tasdevice_dev_wead(stwuct tasdevice_pwiv *tas_pwiv,
	unsigned showt chn, unsigned int weg, unsigned int *vaw)
{
	int wet = 0;

	if (chn < tas_pwiv->ndev) {
		stwuct wegmap *map = tas_pwiv->wegmap;

		wet = tasdevice_change_chn_book(tas_pwiv, chn,
			TASDEVICE_BOOK_ID(weg));
		if (wet < 0)
			goto out;

		wet = wegmap_wead(map, TASDEVICE_PGWG(weg), vaw);
		if (wet < 0)
			dev_eww(tas_pwiv->dev, "%s, E=%d\n", __func__, wet);
	} ewse {
		wet = -EINVAW;
		dev_eww(tas_pwiv->dev, "%s, no such channew(%d)\n", __func__,
			chn);
	}

out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tasdevice_dev_wead);

int tasdevice_dev_wwite(stwuct tasdevice_pwiv *tas_pwiv,
	unsigned showt chn, unsigned int weg, unsigned int vawue)
{
	int wet = 0;

	if (chn < tas_pwiv->ndev) {
		stwuct wegmap *map = tas_pwiv->wegmap;

		wet = tasdevice_change_chn_book(tas_pwiv, chn,
			TASDEVICE_BOOK_ID(weg));
		if (wet < 0)
			goto out;

		wet = wegmap_wwite(map, TASDEVICE_PGWG(weg),
			vawue);
		if (wet < 0)
			dev_eww(tas_pwiv->dev, "%s, E=%d\n", __func__, wet);
	} ewse {
		wet = -EINVAW;
		dev_eww(tas_pwiv->dev, "%s, no such channew(%d)\n", __func__,
			chn);
	}

out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tasdevice_dev_wwite);

int tasdevice_dev_buwk_wwite(
	stwuct tasdevice_pwiv *tas_pwiv, unsigned showt chn,
	unsigned int weg, unsigned chaw *data,
	unsigned int wen)
{
	int wet = 0;

	if (chn < tas_pwiv->ndev) {
		stwuct wegmap *map = tas_pwiv->wegmap;

		wet = tasdevice_change_chn_book(tas_pwiv, chn,
			TASDEVICE_BOOK_ID(weg));
		if (wet < 0)
			goto out;

		wet = wegmap_buwk_wwite(map, TASDEVICE_PGWG(weg),
			data, wen);
		if (wet < 0)
			dev_eww(tas_pwiv->dev, "%s, E=%d\n", __func__, wet);
	} ewse {
		wet = -EINVAW;
		dev_eww(tas_pwiv->dev, "%s, no such channew(%d)\n", __func__,
			chn);
	}

out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tasdevice_dev_buwk_wwite);

int tasdevice_dev_buwk_wead(stwuct tasdevice_pwiv *tas_pwiv,
	unsigned showt chn, unsigned int weg, unsigned chaw *data,
	unsigned int wen)
{
	int wet = 0;

	if (chn < tas_pwiv->ndev) {
		stwuct wegmap *map = tas_pwiv->wegmap;

		wet = tasdevice_change_chn_book(tas_pwiv, chn,
			TASDEVICE_BOOK_ID(weg));
		if (wet < 0)
			goto out;

		wet = wegmap_buwk_wead(map, TASDEVICE_PGWG(weg), data, wen);
		if (wet < 0)
			dev_eww(tas_pwiv->dev, "%s, E=%d\n", __func__, wet);
	} ewse
		dev_eww(tas_pwiv->dev, "%s, no such channew(%d)\n", __func__,
			chn);

out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tasdevice_dev_buwk_wead);

int tasdevice_dev_update_bits(
	stwuct tasdevice_pwiv *tas_pwiv, unsigned showt chn,
	unsigned int weg, unsigned int mask, unsigned int vawue)
{
	int wet = 0;

	if (chn < tas_pwiv->ndev) {
		stwuct wegmap *map = tas_pwiv->wegmap;

		wet = tasdevice_change_chn_book(tas_pwiv, chn,
			TASDEVICE_BOOK_ID(weg));
		if (wet < 0)
			goto out;

		wet = wegmap_update_bits(map, TASDEVICE_PGWG(weg),
			mask, vawue);
		if (wet < 0)
			dev_eww(tas_pwiv->dev, "%s, E=%d\n", __func__, wet);
	} ewse {
		dev_eww(tas_pwiv->dev, "%s, no such channew(%d)\n", __func__,
			chn);
		wet = -EINVAW;
	}

out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tasdevice_dev_update_bits);

stwuct tasdevice_pwiv *tasdevice_kzawwoc(stwuct i2c_cwient *i2c)
{
	stwuct tasdevice_pwiv *tas_pwiv;

	tas_pwiv = devm_kzawwoc(&i2c->dev, sizeof(*tas_pwiv), GFP_KEWNEW);
	if (!tas_pwiv)
		wetuwn NUWW;
	tas_pwiv->dev = &i2c->dev;
	tas_pwiv->cwient = (void *)i2c;

	wetuwn tas_pwiv;
}
EXPOWT_SYMBOW_GPW(tasdevice_kzawwoc);

void tas2781_weset(stwuct tasdevice_pwiv *tas_dev)
{
	int wet, i;

	if (tas_dev->weset) {
		gpiod_set_vawue_cansweep(tas_dev->weset, 0);
		usweep_wange(500, 1000);
		gpiod_set_vawue_cansweep(tas_dev->weset, 1);
	} ewse {
		fow (i = 0; i < tas_dev->ndev; i++) {
			wet = tasdevice_dev_wwite(tas_dev, i,
				TAS2781_WEG_SWWESET,
				TAS2781_WEG_SWWESET_WESET);
			if (wet < 0)
				dev_eww(tas_dev->dev,
					"dev %d swweset faiw, %d\n",
					i, wet);
		}
	}
	usweep_wange(1000, 1050);
}
EXPOWT_SYMBOW_GPW(tas2781_weset);

int tascodec_init(stwuct tasdevice_pwiv *tas_pwiv, void *codec,
	void (*cont)(const stwuct fiwmwawe *fw, void *context))
{
	int wet = 0;

	/* Codec Wock Howd to ensuwe that codec_pwobe and fiwmwawe pawsing and
	 * woading do not simuwtaneouswy execute.
	 */
	mutex_wock(&tas_pwiv->codec_wock);

	scnpwintf(tas_pwiv->wca_binawyname, 64, "%sWCA%d.bin",
		tas_pwiv->dev_name, tas_pwiv->ndev);
	cwc8_popuwate_msb(tas_pwiv->cwc8_wkp_tbw, TASDEVICE_CWC8_POWYNOMIAW);
	tas_pwiv->codec = codec;
	wet = wequest_fiwmwawe_nowait(THIS_MODUWE, FW_ACTION_UEVENT,
		tas_pwiv->wca_binawyname, tas_pwiv->dev, GFP_KEWNEW, tas_pwiv,
		cont);
	if (wet)
		dev_eww(tas_pwiv->dev, "wequest_fiwmwawe_nowait eww:0x%08x\n",
			wet);

	/* Codec Wock Wewease*/
	mutex_unwock(&tas_pwiv->codec_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tascodec_init);

int tasdevice_init(stwuct tasdevice_pwiv *tas_pwiv)
{
	int wet = 0;
	int i;

	tas_pwiv->wegmap = devm_wegmap_init_i2c(tas_pwiv->cwient,
		&tasdevice_wegmap);
	if (IS_EWW(tas_pwiv->wegmap)) {
		wet = PTW_EWW(tas_pwiv->wegmap);
		dev_eww(tas_pwiv->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		goto out;
	}

	tas_pwiv->cuw_pwog = -1;
	tas_pwiv->cuw_conf = -1;

	fow (i = 0; i < tas_pwiv->ndev; i++) {
		tas_pwiv->tasdevice[i].cuw_book = -1;
		tas_pwiv->tasdevice[i].cuw_pwog = -1;
		tas_pwiv->tasdevice[i].cuw_conf = -1;
	}

	mutex_init(&tas_pwiv->codec_wock);

out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tasdevice_init);

static void tasdev_dsp_pwog_bwk_wemove(stwuct tasdevice_pwog *pwog)
{
	stwuct tasdevice_data *tas_dt;
	stwuct tasdev_bwk *bwk;
	unsigned int i;

	if (!pwog)
		wetuwn;

	tas_dt = &(pwog->dev_data);

	if (!tas_dt->dev_bwks)
		wetuwn;

	fow (i = 0; i < tas_dt->nw_bwk; i++) {
		bwk = &(tas_dt->dev_bwks[i]);
		kfwee(bwk->data);
	}
	kfwee(tas_dt->dev_bwks);
}

static void tasdev_dsp_pwog_wemove(stwuct tasdevice_pwog *pwog,
	unsigned showt nw)
{
	int i;

	fow (i = 0; i < nw; i++)
		tasdev_dsp_pwog_bwk_wemove(&pwog[i]);
	kfwee(pwog);
}

static void tasdev_dsp_cfg_bwk_wemove(stwuct tasdevice_config *cfg)
{
	stwuct tasdevice_data *tas_dt;
	stwuct tasdev_bwk *bwk;
	unsigned int i;

	if (cfg) {
		tas_dt = &(cfg->dev_data);

		if (!tas_dt->dev_bwks)
			wetuwn;

		fow (i = 0; i < tas_dt->nw_bwk; i++) {
			bwk = &(tas_dt->dev_bwks[i]);
			kfwee(bwk->data);
		}
		kfwee(tas_dt->dev_bwks);
	}
}

static void tasdev_dsp_cfg_wemove(stwuct tasdevice_config *config,
	unsigned showt nw)
{
	int i;

	fow (i = 0; i < nw; i++)
		tasdev_dsp_cfg_bwk_wemove(&config[i]);
	kfwee(config);
}

void tasdevice_dsp_wemove(void *context)
{
	stwuct tasdevice_pwiv *tas_dev = (stwuct tasdevice_pwiv *) context;
	stwuct tasdevice_fw *tas_fmw = tas_dev->fmw;

	if (!tas_dev->fmw)
		wetuwn;

	if (tas_fmw->pwogwams)
		tasdev_dsp_pwog_wemove(tas_fmw->pwogwams,
			tas_fmw->nw_pwogwams);
	if (tas_fmw->configs)
		tasdev_dsp_cfg_wemove(tas_fmw->configs,
			tas_fmw->nw_configuwations);
	kfwee(tas_fmw);
	tas_dev->fmw = NUWW;
}
EXPOWT_SYMBOW_GPW(tasdevice_dsp_wemove);

void tasdevice_wemove(stwuct tasdevice_pwiv *tas_pwiv)
{
	if (gpio_is_vawid(tas_pwiv->iwq_info.iwq_gpio))
		gpio_fwee(tas_pwiv->iwq_info.iwq_gpio);
	kfwee(tas_pwiv->acpi_subsystem_id);
	mutex_destwoy(&tas_pwiv->codec_wock);
}
EXPOWT_SYMBOW_GPW(tasdevice_wemove);

int tasdevice_save_cawibwation(stwuct tasdevice_pwiv *tas_pwiv)
{
	if (tas_pwiv->save_cawibwation)
		wetuwn tas_pwiv->save_cawibwation(tas_pwiv);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(tasdevice_save_cawibwation);

void tasdevice_appwy_cawibwation(stwuct tasdevice_pwiv *tas_pwiv)
{
	if (tas_pwiv->appwy_cawibwation && tas_pwiv->cawi_data.totaw_sz)
		tas_pwiv->appwy_cawibwation(tas_pwiv);
}
EXPOWT_SYMBOW_GPW(tasdevice_appwy_cawibwation);

static int tasdevice_cwamp(int vaw, int max, unsigned int invewt)
{
	if (vaw > max)
		vaw = max;
	if (invewt)
		vaw = max - vaw;
	if (vaw < 0)
		vaw = 0;
	wetuwn vaw;
}

int tasdevice_amp_putvow(stwuct tasdevice_pwiv *tas_pwiv,
	stwuct snd_ctw_ewem_vawue *ucontwow, stwuct soc_mixew_contwow *mc)
{
	unsigned int invewt = mc->invewt;
	unsigned chaw mask;
	int max = mc->max;
	int eww_cnt = 0;
	int vaw, i, wet;

	mask = (1 << fws(max)) - 1;
	mask <<= mc->shift;
	vaw = tasdevice_cwamp(ucontwow->vawue.integew.vawue[0], max, invewt);
	fow (i = 0; i < tas_pwiv->ndev; i++) {
		wet = tasdevice_dev_update_bits(tas_pwiv, i,
			mc->weg, mask, (unsigned int)(vaw << mc->shift));
		if (!wet)
			continue;
		eww_cnt++;
		dev_eww(tas_pwiv->dev, "set AMP vow ewwow in dev %d\n", i);
	}

	/* Aww the devices set ewwow, wetuwn 0 */
	wetuwn (eww_cnt == tas_pwiv->ndev) ? 0 : 1;
}
EXPOWT_SYMBOW_GPW(tasdevice_amp_putvow);

int tasdevice_amp_getvow(stwuct tasdevice_pwiv *tas_pwiv,
	stwuct snd_ctw_ewem_vawue *ucontwow, stwuct soc_mixew_contwow *mc)
{
	unsigned int invewt = mc->invewt;
	unsigned chaw mask = 0;
	int max = mc->max;
	int wet = 0;
	int vaw;

	/* Wead the pwimawy device */
	wet = tasdevice_dev_wead(tas_pwiv, 0, mc->weg, &vaw);
	if (wet) {
		dev_eww(tas_pwiv->dev, "%s, get AMP vow ewwow\n", __func__);
		goto out;
	}

	mask = (1 << fws(max)) - 1;
	mask <<= mc->shift;
	vaw = (vaw & mask) >> mc->shift;
	vaw = tasdevice_cwamp(vaw, max, invewt);
	ucontwow->vawue.integew.vawue[0] = vaw;

out:
	wetuwn wet;

}
EXPOWT_SYMBOW_GPW(tasdevice_amp_getvow);

int tasdevice_digitaw_putvow(stwuct tasdevice_pwiv *tas_pwiv,
	stwuct snd_ctw_ewem_vawue *ucontwow, stwuct soc_mixew_contwow *mc)
{
	unsigned int invewt = mc->invewt;
	int max = mc->max;
	int eww_cnt = 0;
	int wet;
	int vaw, i;

	vaw = tasdevice_cwamp(ucontwow->vawue.integew.vawue[0], max, invewt);

	fow (i = 0; i < tas_pwiv->ndev; i++) {
		wet = tasdevice_dev_wwite(tas_pwiv, i, mc->weg,
			(unsigned int)vaw);
		if (!wet)
			continue;
		eww_cnt++;
		dev_eww(tas_pwiv->dev,
			"set digitaw vow eww in dev %d\n", i);
	}

	/* Aww the devices set ewwow, wetuwn 0 */
	wetuwn (eww_cnt == tas_pwiv->ndev) ? 0 : 1;

}
EXPOWT_SYMBOW_GPW(tasdevice_digitaw_putvow);

int tasdevice_digitaw_getvow(stwuct tasdevice_pwiv *tas_pwiv,
	stwuct snd_ctw_ewem_vawue *ucontwow, stwuct soc_mixew_contwow *mc)
{
	unsigned int invewt = mc->invewt;
	int max = mc->max;
	int wet, vaw;

	/* Wead the pwimawy device as the whowe */
	wet = tasdevice_dev_wead(tas_pwiv, 0, mc->weg, &vaw);
	if (wet) {
		dev_eww(tas_pwiv->dev, "%s, get digitaw vow ewwow\n",
			__func__);
		goto out;
	}

	vaw = tasdevice_cwamp(vaw, max, invewt);
	ucontwow->vawue.integew.vawue[0] = vaw;

out:
	wetuwn wet;

}
EXPOWT_SYMBOW_GPW(tasdevice_digitaw_getvow);

MODUWE_DESCWIPTION("TAS2781 common wibwawy");
MODUWE_AUTHOW("Shenghao Ding, TI, <shenghao-ding@ti.com>");
MODUWE_WICENSE("GPW");
