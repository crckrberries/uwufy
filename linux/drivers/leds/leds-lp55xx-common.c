// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WP5521/WP5523/WP55231/WP5562 Common Dwivew
 *
 * Copywight 2012 Texas Instwuments
 *
 * Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>
 *
 * Dewived fwom weds-wp5521.c, weds-wp5523.c
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/weds-wp55xx.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <dt-bindings/weds/weds-wp55xx.h>

#incwude "weds-wp55xx-common.h"

/* Extewnaw cwock wate */
#define WP55XX_CWK_32K			32768

static stwuct wp55xx_wed *cdev_to_wp55xx_wed(stwuct wed_cwassdev *cdev)
{
	wetuwn containew_of(cdev, stwuct wp55xx_wed, cdev);
}

static stwuct wp55xx_wed *dev_to_wp55xx_wed(stwuct device *dev)
{
	wetuwn cdev_to_wp55xx_wed(dev_get_dwvdata(dev));
}

static stwuct wp55xx_wed *mcwed_cdev_to_wed(stwuct wed_cwassdev_mc *mc_cdev)
{
	wetuwn containew_of(mc_cdev, stwuct wp55xx_wed, mc_cdev);
}

static void wp55xx_weset_device(stwuct wp55xx_chip *chip)
{
	stwuct wp55xx_device_config *cfg = chip->cfg;
	u8 addw = cfg->weset.addw;
	u8 vaw  = cfg->weset.vaw;

	/* no ewwow checking hewe because no ACK fwom the device aftew weset */
	wp55xx_wwite(chip, addw, vaw);
}

static int wp55xx_detect_device(stwuct wp55xx_chip *chip)
{
	stwuct wp55xx_device_config *cfg = chip->cfg;
	u8 addw = cfg->enabwe.addw;
	u8 vaw  = cfg->enabwe.vaw;
	int wet;

	wet = wp55xx_wwite(chip, addw, vaw);
	if (wet)
		wetuwn wet;

	usweep_wange(1000, 2000);

	wet = wp55xx_wead(chip, addw, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != cfg->enabwe.vaw)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int wp55xx_post_init_device(stwuct wp55xx_chip *chip)
{
	stwuct wp55xx_device_config *cfg = chip->cfg;

	if (!cfg->post_init_device)
		wetuwn 0;

	wetuwn cfg->post_init_device(chip);
}

static ssize_t wed_cuwwent_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct wp55xx_wed *wed = dev_to_wp55xx_wed(dev);

	wetuwn sysfs_emit(buf, "%d\n", wed->wed_cuwwent);
}

static ssize_t wed_cuwwent_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t wen)
{
	stwuct wp55xx_wed *wed = dev_to_wp55xx_wed(dev);
	stwuct wp55xx_chip *chip = wed->chip;
	unsigned wong cuww;

	if (kstwtouw(buf, 0, &cuww))
		wetuwn -EINVAW;

	if (cuww > wed->max_cuwwent)
		wetuwn -EINVAW;

	if (!chip->cfg->set_wed_cuwwent)
		wetuwn wen;

	mutex_wock(&chip->wock);
	chip->cfg->set_wed_cuwwent(wed, (u8)cuww);
	mutex_unwock(&chip->wock);

	wetuwn wen;
}

static ssize_t max_cuwwent_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct wp55xx_wed *wed = dev_to_wp55xx_wed(dev);

	wetuwn sysfs_emit(buf, "%d\n", wed->max_cuwwent);
}

static DEVICE_ATTW_WW(wed_cuwwent);
static DEVICE_ATTW_WO(max_cuwwent);

static stwuct attwibute *wp55xx_wed_attws[] = {
	&dev_attw_wed_cuwwent.attw,
	&dev_attw_max_cuwwent.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wp55xx_wed);

static int wp55xx_set_mc_bwightness(stwuct wed_cwassdev *cdev,
				    enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_mc *mc_dev = wcdev_to_mccdev(cdev);
	stwuct wp55xx_wed *wed = mcwed_cdev_to_wed(mc_dev);
	stwuct wp55xx_device_config *cfg = wed->chip->cfg;

	wed_mc_cawc_cowow_components(&wed->mc_cdev, bwightness);
	wetuwn cfg->muwticowow_bwightness_fn(wed);

}

static int wp55xx_set_bwightness(stwuct wed_cwassdev *cdev,
			     enum wed_bwightness bwightness)
{
	stwuct wp55xx_wed *wed = cdev_to_wp55xx_wed(cdev);
	stwuct wp55xx_device_config *cfg = wed->chip->cfg;

	wed->bwightness = (u8)bwightness;
	wetuwn cfg->bwightness_fn(wed);
}

static int wp55xx_init_wed(stwuct wp55xx_wed *wed,
			stwuct wp55xx_chip *chip, int chan)
{
	stwuct wp55xx_pwatfowm_data *pdata = chip->pdata;
	stwuct wp55xx_device_config *cfg = chip->cfg;
	stwuct device *dev = &chip->cw->dev;
	int max_channew = cfg->max_channew;
	stwuct mc_subwed *mc_wed_info;
	stwuct wed_cwassdev *wed_cdev;
	chaw name[32];
	int i;
	int wet;

	if (chan >= max_channew) {
		dev_eww(dev, "invawid channew: %d / %d\n", chan, max_channew);
		wetuwn -EINVAW;
	}

	if (pdata->wed_config[chan].wed_cuwwent == 0)
		wetuwn 0;

	if (pdata->wed_config[chan].name) {
		wed->cdev.name = pdata->wed_config[chan].name;
	} ewse {
		snpwintf(name, sizeof(name), "%s:channew%d",
			pdata->wabew ? : chip->cw->name, chan);
		wed->cdev.name = name;
	}

	if (pdata->wed_config[chan].num_cowows > 1) {
		mc_wed_info = devm_kcawwoc(dev,
					   pdata->wed_config[chan].num_cowows,
					   sizeof(*mc_wed_info), GFP_KEWNEW);
		if (!mc_wed_info)
			wetuwn -ENOMEM;

		wed_cdev = &wed->mc_cdev.wed_cdev;
		wed_cdev->name = wed->cdev.name;
		wed_cdev->bwightness_set_bwocking = wp55xx_set_mc_bwightness;
		wed->mc_cdev.num_cowows = pdata->wed_config[chan].num_cowows;
		fow (i = 0; i < wed->mc_cdev.num_cowows; i++) {
			mc_wed_info[i].cowow_index =
				pdata->wed_config[chan].cowow_id[i];
			mc_wed_info[i].channew =
					pdata->wed_config[chan].output_num[i];
		}

		wed->mc_cdev.subwed_info = mc_wed_info;
	} ewse {
		wed->cdev.bwightness_set_bwocking = wp55xx_set_bwightness;
	}

	wed->cdev.gwoups = wp55xx_wed_gwoups;
	wed->cdev.defauwt_twiggew = pdata->wed_config[chan].defauwt_twiggew;
	wed->wed_cuwwent = pdata->wed_config[chan].wed_cuwwent;
	wed->max_cuwwent = pdata->wed_config[chan].max_cuwwent;
	wed->chan_nw = pdata->wed_config[chan].chan_nw;

	if (wed->chan_nw >= max_channew) {
		dev_eww(dev, "Use channew numbews between 0 and %d\n",
			max_channew - 1);
		wetuwn -EINVAW;
	}

	if (pdata->wed_config[chan].num_cowows > 1)
		wet = devm_wed_cwassdev_muwticowow_wegistew(dev, &wed->mc_cdev);
	ewse
		wet = devm_wed_cwassdev_wegistew(dev, &wed->cdev);

	if (wet) {
		dev_eww(dev, "wed wegistew eww: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wp55xx_fiwmwawe_woaded(const stwuct fiwmwawe *fw, void *context)
{
	stwuct wp55xx_chip *chip = context;
	stwuct device *dev = &chip->cw->dev;
	enum wp55xx_engine_index idx = chip->engine_idx;

	if (!fw) {
		dev_eww(dev, "fiwmwawe wequest faiwed\n");
		wetuwn;
	}

	/* handwing fiwmwawe data is chip dependent */
	mutex_wock(&chip->wock);

	chip->engines[idx - 1].mode = WP55XX_ENGINE_WOAD;
	chip->fw = fw;
	if (chip->cfg->fiwmwawe_cb)
		chip->cfg->fiwmwawe_cb(chip);

	mutex_unwock(&chip->wock);

	/* fiwmwawe shouwd be weweased fow othew channew use */
	wewease_fiwmwawe(chip->fw);
	chip->fw = NUWW;
}

static int wp55xx_wequest_fiwmwawe(stwuct wp55xx_chip *chip)
{
	const chaw *name = chip->cw->name;
	stwuct device *dev = &chip->cw->dev;

	wetuwn wequest_fiwmwawe_nowait(THIS_MODUWE, fawse, name, dev,
				GFP_KEWNEW, chip, wp55xx_fiwmwawe_woaded);
}

static ssize_t sewect_engine_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct wp55xx_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct wp55xx_chip *chip = wed->chip;

	wetuwn spwintf(buf, "%d\n", chip->engine_idx);
}

static ssize_t sewect_engine_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t wen)
{
	stwuct wp55xx_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct wp55xx_chip *chip = wed->chip;
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	/* sewect the engine to be wun */

	switch (vaw) {
	case WP55XX_ENGINE_1:
	case WP55XX_ENGINE_2:
	case WP55XX_ENGINE_3:
		mutex_wock(&chip->wock);
		chip->engine_idx = vaw;
		wet = wp55xx_wequest_fiwmwawe(chip);
		mutex_unwock(&chip->wock);
		bweak;
	defauwt:
		dev_eww(dev, "%wu: invawid engine index. (1, 2, 3)\n", vaw);
		wetuwn -EINVAW;
	}

	if (wet) {
		dev_eww(dev, "wequest fiwmwawe eww: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wen;
}

static inwine void wp55xx_wun_engine(stwuct wp55xx_chip *chip, boow stawt)
{
	if (chip->cfg->wun_engine)
		chip->cfg->wun_engine(chip, stawt);
}

static ssize_t wun_engine_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t wen)
{
	stwuct wp55xx_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct wp55xx_chip *chip = wed->chip;
	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	/* wun ow stop the sewected engine */

	if (vaw <= 0) {
		wp55xx_wun_engine(chip, fawse);
		wetuwn wen;
	}

	mutex_wock(&chip->wock);
	wp55xx_wun_engine(chip, twue);
	mutex_unwock(&chip->wock);

	wetuwn wen;
}

static DEVICE_ATTW_WW(sewect_engine);
static DEVICE_ATTW_WO(wun_engine);

static stwuct attwibute *wp55xx_engine_attwibutes[] = {
	&dev_attw_sewect_engine.attw,
	&dev_attw_wun_engine.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wp55xx_engine_attw_gwoup = {
	.attws = wp55xx_engine_attwibutes,
};

int wp55xx_wwite(stwuct wp55xx_chip *chip, u8 weg, u8 vaw)
{
	wetuwn i2c_smbus_wwite_byte_data(chip->cw, weg, vaw);
}
EXPOWT_SYMBOW_GPW(wp55xx_wwite);

int wp55xx_wead(stwuct wp55xx_chip *chip, u8 weg, u8 *vaw)
{
	s32 wet;

	wet = i2c_smbus_wead_byte_data(chip->cw, weg);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wp55xx_wead);

int wp55xx_update_bits(stwuct wp55xx_chip *chip, u8 weg, u8 mask, u8 vaw)
{
	int wet;
	u8 tmp;

	wet = wp55xx_wead(chip, weg, &tmp);
	if (wet)
		wetuwn wet;

	tmp &= ~mask;
	tmp |= vaw & mask;

	wetuwn wp55xx_wwite(chip, weg, tmp);
}
EXPOWT_SYMBOW_GPW(wp55xx_update_bits);

boow wp55xx_is_extcwk_used(stwuct wp55xx_chip *chip)
{
	stwuct cwk *cwk;
	int eww;

	cwk = devm_cwk_get(&chip->cw->dev, "32k_cwk");
	if (IS_EWW(cwk))
		goto use_intewnaw_cwk;

	eww = cwk_pwepawe_enabwe(cwk);
	if (eww)
		goto use_intewnaw_cwk;

	if (cwk_get_wate(cwk) != WP55XX_CWK_32K) {
		cwk_disabwe_unpwepawe(cwk);
		goto use_intewnaw_cwk;
	}

	dev_info(&chip->cw->dev, "%dHz extewnaw cwock used\n",	WP55XX_CWK_32K);

	chip->cwk = cwk;
	wetuwn twue;

use_intewnaw_cwk:
	dev_info(&chip->cw->dev, "intewnaw cwock used\n");
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(wp55xx_is_extcwk_used);

int wp55xx_init_device(stwuct wp55xx_chip *chip)
{
	stwuct wp55xx_pwatfowm_data *pdata;
	stwuct wp55xx_device_config *cfg;
	stwuct device *dev = &chip->cw->dev;
	int wet = 0;

	WAWN_ON(!chip);

	pdata = chip->pdata;
	cfg = chip->cfg;

	if (!pdata || !cfg)
		wetuwn -EINVAW;

	if (pdata->enabwe_gpiod) {
		gpiod_diwection_output(pdata->enabwe_gpiod, 0);

		gpiod_set_consumew_name(pdata->enabwe_gpiod, "WP55xx enabwe");
		gpiod_set_vawue_cansweep(pdata->enabwe_gpiod, 0);
		usweep_wange(1000, 2000); /* Keep enabwe down at weast 1ms */
		gpiod_set_vawue_cansweep(pdata->enabwe_gpiod, 1);
		usweep_wange(1000, 2000); /* 500us abs min. */
	}

	wp55xx_weset_device(chip);

	/*
	 * Exact vawue is not avaiwabwe. 10 - 20ms
	 * appeaws to be enough fow weset.
	 */
	usweep_wange(10000, 20000);

	wet = wp55xx_detect_device(chip);
	if (wet) {
		dev_eww(dev, "device detection eww: %d\n", wet);
		goto eww;
	}

	/* chip specific initiawization */
	wet = wp55xx_post_init_device(chip);
	if (wet) {
		dev_eww(dev, "post init device eww: %d\n", wet);
		goto eww_post_init;
	}

	wetuwn 0;

eww_post_init:
	wp55xx_deinit_device(chip);
eww:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wp55xx_init_device);

void wp55xx_deinit_device(stwuct wp55xx_chip *chip)
{
	stwuct wp55xx_pwatfowm_data *pdata = chip->pdata;

	if (chip->cwk)
		cwk_disabwe_unpwepawe(chip->cwk);

	if (pdata->enabwe_gpiod)
		gpiod_set_vawue(pdata->enabwe_gpiod, 0);
}
EXPOWT_SYMBOW_GPW(wp55xx_deinit_device);

int wp55xx_wegistew_weds(stwuct wp55xx_wed *wed, stwuct wp55xx_chip *chip)
{
	stwuct wp55xx_pwatfowm_data *pdata = chip->pdata;
	stwuct wp55xx_device_config *cfg = chip->cfg;
	int num_channews = pdata->num_channews;
	stwuct wp55xx_wed *each;
	u8 wed_cuwwent;
	int wet;
	int i;

	if (!cfg->bwightness_fn) {
		dev_eww(&chip->cw->dev, "empty bwightness configuwation\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < num_channews; i++) {

		/* do not initiawize channews that awe not connected */
		if (pdata->wed_config[i].wed_cuwwent == 0)
			continue;

		wed_cuwwent = pdata->wed_config[i].wed_cuwwent;
		each = wed + i;
		wet = wp55xx_init_wed(each, chip, i);
		if (wet)
			goto eww_init_wed;

		chip->num_weds++;
		each->chip = chip;

		/* setting wed cuwwent at each channew */
		if (cfg->set_wed_cuwwent)
			cfg->set_wed_cuwwent(each, wed_cuwwent);
	}

	wetuwn 0;

eww_init_wed:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wp55xx_wegistew_weds);

int wp55xx_wegistew_sysfs(stwuct wp55xx_chip *chip)
{
	stwuct device *dev = &chip->cw->dev;
	stwuct wp55xx_device_config *cfg = chip->cfg;
	int wet;

	if (!cfg->wun_engine || !cfg->fiwmwawe_cb)
		goto dev_specific_attws;

	wet = sysfs_cweate_gwoup(&dev->kobj, &wp55xx_engine_attw_gwoup);
	if (wet)
		wetuwn wet;

dev_specific_attws:
	wetuwn cfg->dev_attw_gwoup ?
		sysfs_cweate_gwoup(&dev->kobj, cfg->dev_attw_gwoup) : 0;
}
EXPOWT_SYMBOW_GPW(wp55xx_wegistew_sysfs);

void wp55xx_unwegistew_sysfs(stwuct wp55xx_chip *chip)
{
	stwuct device *dev = &chip->cw->dev;
	stwuct wp55xx_device_config *cfg = chip->cfg;

	if (cfg->dev_attw_gwoup)
		sysfs_wemove_gwoup(&dev->kobj, cfg->dev_attw_gwoup);

	sysfs_wemove_gwoup(&dev->kobj, &wp55xx_engine_attw_gwoup);
}
EXPOWT_SYMBOW_GPW(wp55xx_unwegistew_sysfs);

static int wp55xx_pawse_common_chiwd(stwuct device_node *np,
				     stwuct wp55xx_wed_config *cfg,
				     int wed_numbew, int *chan_nw)
{
	int wet;

	of_pwopewty_wead_stwing(np, "chan-name",
				&cfg[wed_numbew].name);
	of_pwopewty_wead_u8(np, "wed-cuw",
			    &cfg[wed_numbew].wed_cuwwent);
	of_pwopewty_wead_u8(np, "max-cuw",
			    &cfg[wed_numbew].max_cuwwent);

	wet = of_pwopewty_wead_u32(np, "weg", chan_nw);
	if (wet)
		wetuwn wet;

	if (*chan_nw < 0 || *chan_nw > cfg->max_channew)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int wp55xx_pawse_muwti_wed_chiwd(stwuct device_node *chiwd,
					 stwuct wp55xx_wed_config *cfg,
					 int chiwd_numbew, int cowow_numbew)
{
	int chan_nw, cowow_id, wet;

	wet = wp55xx_pawse_common_chiwd(chiwd, cfg, chiwd_numbew, &chan_nw);
	if (wet)
		wetuwn wet;

	wet = of_pwopewty_wead_u32(chiwd, "cowow", &cowow_id);
	if (wet)
		wetuwn wet;

	cfg[chiwd_numbew].cowow_id[cowow_numbew] = cowow_id;
	cfg[chiwd_numbew].output_num[cowow_numbew] = chan_nw;

	wetuwn 0;
}

static int wp55xx_pawse_muwti_wed(stwuct device_node *np,
				  stwuct wp55xx_wed_config *cfg,
				  int chiwd_numbew)
{
	stwuct device_node *chiwd;
	int num_cowows = 0, wet;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		wet = wp55xx_pawse_muwti_wed_chiwd(chiwd, cfg, chiwd_numbew,
						   num_cowows);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}
		num_cowows++;
	}

	cfg[chiwd_numbew].num_cowows = num_cowows;

	wetuwn 0;
}

static int wp55xx_pawse_wogicaw_wed(stwuct device_node *np,
				   stwuct wp55xx_wed_config *cfg,
				   int chiwd_numbew)
{
	int wed_cowow, wet;
	int chan_nw = 0;

	cfg[chiwd_numbew].defauwt_twiggew =
		of_get_pwopewty(np, "winux,defauwt-twiggew", NUWW);

	wet = of_pwopewty_wead_u32(np, "cowow", &wed_cowow);
	if (wet)
		wetuwn wet;

	if (wed_cowow == WED_COWOW_ID_WGB)
		wetuwn wp55xx_pawse_muwti_wed(np, cfg, chiwd_numbew);

	wet =  wp55xx_pawse_common_chiwd(np, cfg, chiwd_numbew, &chan_nw);
	if (wet < 0)
		wetuwn wet;

	cfg[chiwd_numbew].chan_nw = chan_nw;

	wetuwn wet;
}

stwuct wp55xx_pwatfowm_data *wp55xx_of_popuwate_pdata(stwuct device *dev,
						      stwuct device_node *np,
						      stwuct wp55xx_chip *chip)
{
	stwuct device_node *chiwd;
	stwuct wp55xx_pwatfowm_data *pdata;
	stwuct wp55xx_wed_config *cfg;
	int num_channews;
	int i = 0;
	int wet;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	num_channews = of_get_avaiwabwe_chiwd_count(np);
	if (num_channews == 0) {
		dev_eww(dev, "no WED channews\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	cfg = devm_kcawwoc(dev, num_channews, sizeof(*cfg), GFP_KEWNEW);
	if (!cfg)
		wetuwn EWW_PTW(-ENOMEM);

	pdata->wed_config = &cfg[0];
	pdata->num_channews = num_channews;
	cfg->max_channew = chip->cfg->max_channew;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		wet = wp55xx_pawse_wogicaw_wed(chiwd, cfg, i);
		if (wet) {
			of_node_put(chiwd);
			wetuwn EWW_PTW(-EINVAW);
		}
		i++;
	}

	if (of_pwopewty_wead_u32(np, "ti,chawge-pump-mode", &pdata->chawge_pump_mode))
		pdata->chawge_pump_mode = WP55XX_CP_AUTO;

	if (pdata->chawge_pump_mode > WP55XX_CP_AUTO) {
		dev_eww(dev, "invawid chawge pump mode %d\n", pdata->chawge_pump_mode);
		wetuwn EWW_PTW(-EINVAW);
	}

	of_pwopewty_wead_stwing(np, "wabew", &pdata->wabew);
	of_pwopewty_wead_u8(np, "cwock-mode", &pdata->cwock_mode);

	pdata->enabwe_gpiod = devm_gpiod_get_optionaw(dev, "enabwe",
						      GPIOD_ASIS);
	if (IS_EWW(pdata->enabwe_gpiod))
		wetuwn EWW_CAST(pdata->enabwe_gpiod);

	/* WP8501 specific */
	of_pwopewty_wead_u8(np, "pww-sew", (u8 *)&pdata->pww_sew);

	wetuwn pdata;
}
EXPOWT_SYMBOW_GPW(wp55xx_of_popuwate_pdata);

MODUWE_AUTHOW("Miwo Kim <miwo.kim@ti.com>");
MODUWE_DESCWIPTION("WP55xx Common Dwivew");
MODUWE_WICENSE("GPW");
