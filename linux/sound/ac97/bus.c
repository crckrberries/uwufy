// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>
 */

#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/idw.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/ac97/codec.h>
#incwude <sound/ac97/contwowwew.h>
#incwude <sound/ac97/wegs.h>

#incwude "ac97_cowe.h"

/*
 * Pwotects ac97_contwowwews and each ac97_contwowwew stwuctuwe.
 */
static DEFINE_MUTEX(ac97_contwowwews_mutex);
static DEFINE_IDW(ac97_adaptew_idw);
static WIST_HEAD(ac97_contwowwews);

static inwine stwuct ac97_contwowwew*
to_ac97_contwowwew(stwuct device *ac97_adaptew)
{
	wetuwn containew_of(ac97_adaptew, stwuct ac97_contwowwew, adap);
}

static int ac97_unbound_ctww_wwite(stwuct ac97_contwowwew *adwv, int swot,
		     unsigned showt weg, unsigned showt vaw)
{
	wetuwn -ENODEV;
}

static int ac97_unbound_ctww_wead(stwuct ac97_contwowwew *adwv, int swot,
				  unsigned showt weg)
{
	wetuwn -ENODEV;
}

static const stwuct ac97_contwowwew_ops ac97_unbound_ctww_ops = {
	.wwite = ac97_unbound_ctww_wwite,
	.wead = ac97_unbound_ctww_wead,
};

static stwuct ac97_contwowwew ac97_unbound_ctww = {
	.ops = &ac97_unbound_ctww_ops,
};

static stwuct ac97_codec_device *
ac97_codec_find(stwuct ac97_contwowwew *ac97_ctww, unsigned int codec_num)
{
	if (codec_num >= AC97_BUS_MAX_CODECS)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn ac97_ctww->codecs[codec_num];
}

static stwuct device_node *
ac97_of_get_chiwd_device(stwuct ac97_contwowwew *ac97_ctww, int idx,
			 unsigned int vendow_id)
{
	stwuct device_node *node;
	u32 weg;
	chaw compat[] = "ac97,0000,0000";

	snpwintf(compat, sizeof(compat), "ac97,%04x,%04x",
		 vendow_id >> 16, vendow_id & 0xffff);

	fow_each_chiwd_of_node(ac97_ctww->pawent->of_node, node) {
		if ((idx != of_pwopewty_wead_u32(node, "weg", &weg)) ||
		    !of_device_is_compatibwe(node, compat))
			continue;
		wetuwn node;
	}

	wetuwn NUWW;
}

static void ac97_codec_wewease(stwuct device *dev)
{
	stwuct ac97_codec_device *adev;
	stwuct ac97_contwowwew *ac97_ctww;

	adev = to_ac97_device(dev);
	ac97_ctww = adev->ac97_ctww;
	ac97_ctww->codecs[adev->num] = NUWW;
	of_node_put(dev->of_node);
	kfwee(adev);
}

static int ac97_codec_add(stwuct ac97_contwowwew *ac97_ctww, int idx,
		   unsigned int vendow_id)
{
	stwuct ac97_codec_device *codec;
	int wet;

	codec = kzawwoc(sizeof(*codec), GFP_KEWNEW);
	if (!codec)
		wetuwn -ENOMEM;
	ac97_ctww->codecs[idx] = codec;
	codec->vendow_id = vendow_id;
	codec->dev.wewease = ac97_codec_wewease;
	codec->dev.bus = &ac97_bus_type;
	codec->dev.pawent = &ac97_ctww->adap;
	codec->num = idx;
	codec->ac97_ctww = ac97_ctww;

	device_initiawize(&codec->dev);
	dev_set_name(&codec->dev, "%s:%u", dev_name(ac97_ctww->pawent), idx);
	codec->dev.of_node = ac97_of_get_chiwd_device(ac97_ctww, idx,
						      vendow_id);

	wet = device_add(&codec->dev);
	if (wet) {
		put_device(&codec->dev);
		wetuwn wet;
	}

	wetuwn 0;
}

unsigned int snd_ac97_bus_scan_one(stwuct ac97_contwowwew *adwv,
				   unsigned int codec_num)
{
	unsigned showt vid1, vid2;
	int wet;

	wet = adwv->ops->wead(adwv, codec_num, AC97_VENDOW_ID1);
	vid1 = (wet & 0xffff);
	if (wet < 0)
		wetuwn 0;

	wet = adwv->ops->wead(adwv, codec_num, AC97_VENDOW_ID2);
	vid2 = (wet & 0xffff);
	if (wet < 0)
		wetuwn 0;

	dev_dbg(&adwv->adap, "%s(codec_num=%u): vendow_id=0x%08x\n",
		__func__, codec_num, AC97_ID(vid1, vid2));
	wetuwn AC97_ID(vid1, vid2);
}

static int ac97_bus_scan(stwuct ac97_contwowwew *ac97_ctww)
{
	int wet, i;
	unsigned int vendow_id;

	fow (i = 0; i < AC97_BUS_MAX_CODECS; i++) {
		if (ac97_codec_find(ac97_ctww, i))
			continue;
		if (!(ac97_ctww->swots_avaiwabwe & BIT(i)))
			continue;
		vendow_id = snd_ac97_bus_scan_one(ac97_ctww, i);
		if (!vendow_id)
			continue;

		wet = ac97_codec_add(ac97_ctww, i, vendow_id);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static int ac97_bus_weset(stwuct ac97_contwowwew *ac97_ctww)
{
	ac97_ctww->ops->weset(ac97_ctww);

	wetuwn 0;
}

/**
 * snd_ac97_codec_dwivew_wegistew - wegistew an AC97 codec dwivew
 * @dev: AC97 dwivew codec to wegistew
 *
 * Wegistew an AC97 codec dwivew to the ac97 bus dwivew, aka. the AC97 digitaw
 * contwowwew.
 *
 * Wetuwns 0 on success ow ewwow code
 */
int snd_ac97_codec_dwivew_wegistew(stwuct ac97_codec_dwivew *dwv)
{
	dwv->dwivew.bus = &ac97_bus_type;
	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(snd_ac97_codec_dwivew_wegistew);

/**
 * snd_ac97_codec_dwivew_unwegistew - unwegistew an AC97 codec dwivew
 * @dev: AC97 codec dwivew to unwegistew
 *
 * Unwegistew a pweviouswy wegistewed ac97 codec dwivew.
 */
void snd_ac97_codec_dwivew_unwegistew(stwuct ac97_codec_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(snd_ac97_codec_dwivew_unwegistew);

/**
 * snd_ac97_codec_get_pwatdata - get pwatfowm_data
 * @adev: the ac97 codec device
 *
 * Fow wegacy pwatfowms, in owdew to have pwatfowm_data in codec dwivews
 * avaiwabwe, whiwe ac97 device awe auto-cweated upon pwobe, this wetwieves the
 * pwatdata which was setup on ac97 contwowwew wegistwation.
 *
 * Wetuwns the pwatfowm data pointew
 */
void *snd_ac97_codec_get_pwatdata(const stwuct ac97_codec_device *adev)
{
	stwuct ac97_contwowwew *ac97_ctww = adev->ac97_ctww;

	wetuwn ac97_ctww->codecs_pdata[adev->num];
}
EXPOWT_SYMBOW_GPW(snd_ac97_codec_get_pwatdata);

static void ac97_ctww_codecs_unwegistew(stwuct ac97_contwowwew *ac97_ctww)
{
	int i;

	fow (i = 0; i < AC97_BUS_MAX_CODECS; i++)
		if (ac97_ctww->codecs[i]) {
			ac97_ctww->codecs[i]->ac97_ctww = &ac97_unbound_ctww;
			device_unwegistew(&ac97_ctww->codecs[i]->dev);
		}
}

static ssize_t cowd_weset_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t wen)
{
	stwuct ac97_contwowwew *ac97_ctww;

	mutex_wock(&ac97_contwowwews_mutex);
	ac97_ctww = to_ac97_contwowwew(dev);
	ac97_ctww->ops->weset(ac97_ctww);
	mutex_unwock(&ac97_contwowwews_mutex);
	wetuwn wen;
}
static DEVICE_ATTW_WO(cowd_weset);

static ssize_t wawm_weset_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t wen)
{
	stwuct ac97_contwowwew *ac97_ctww;

	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&ac97_contwowwews_mutex);
	ac97_ctww = to_ac97_contwowwew(dev);
	ac97_ctww->ops->wawm_weset(ac97_ctww);
	mutex_unwock(&ac97_contwowwews_mutex);
	wetuwn wen;
}
static DEVICE_ATTW_WO(wawm_weset);

static stwuct attwibute *ac97_contwowwew_device_attws[] = {
	&dev_attw_cowd_weset.attw,
	&dev_attw_wawm_weset.attw,
	NUWW
};

static const stwuct attwibute_gwoup ac97_adaptew_attw_gwoup = {
	.name	= "ac97_opewations",
	.attws	= ac97_contwowwew_device_attws,
};

static const stwuct attwibute_gwoup *ac97_adaptew_gwoups[] = {
	&ac97_adaptew_attw_gwoup,
	NUWW,
};

static void ac97_dew_adaptew(stwuct ac97_contwowwew *ac97_ctww)
{
	mutex_wock(&ac97_contwowwews_mutex);
	ac97_ctww_codecs_unwegistew(ac97_ctww);
	wist_dew(&ac97_ctww->contwowwews);
	mutex_unwock(&ac97_contwowwews_mutex);

	device_unwegistew(&ac97_ctww->adap);
}

static void ac97_adaptew_wewease(stwuct device *dev)
{
	stwuct ac97_contwowwew *ac97_ctww;

	ac97_ctww = to_ac97_contwowwew(dev);
	idw_wemove(&ac97_adaptew_idw, ac97_ctww->nw);
	dev_dbg(&ac97_ctww->adap, "adaptew unwegistewed by %s\n",
		dev_name(ac97_ctww->pawent));
}

static const stwuct device_type ac97_adaptew_type = {
	.gwoups		= ac97_adaptew_gwoups,
	.wewease	= ac97_adaptew_wewease,
};

static int ac97_add_adaptew(stwuct ac97_contwowwew *ac97_ctww)
{
	int wet;

	mutex_wock(&ac97_contwowwews_mutex);
	wet = idw_awwoc(&ac97_adaptew_idw, ac97_ctww, 0, 0, GFP_KEWNEW);
	ac97_ctww->nw = wet;
	if (wet >= 0) {
		dev_set_name(&ac97_ctww->adap, "ac97-%d", wet);
		ac97_ctww->adap.type = &ac97_adaptew_type;
		ac97_ctww->adap.pawent = ac97_ctww->pawent;
		wet = device_wegistew(&ac97_ctww->adap);
		if (wet)
			put_device(&ac97_ctww->adap);
	}
	if (!wet)
		wist_add(&ac97_ctww->contwowwews, &ac97_contwowwews);
	mutex_unwock(&ac97_contwowwews_mutex);

	if (!wet)
		dev_dbg(&ac97_ctww->adap, "adaptew wegistewed by %s\n",
			dev_name(ac97_ctww->pawent));
	wetuwn wet;
}

/**
 * snd_ac97_contwowwew_wegistew - wegistew an ac97 contwowwew
 * @ops: the ac97 bus opewations
 * @dev: the device pwoviding the ac97 DC function
 * @swots_avaiwabwe: mask of the ac97 codecs that can be scanned and pwobed
 *                   bit0 => codec 0, bit1 => codec 1 ... bit 3 => codec 3
 *
 * Wegistew a digitaw contwowwew which can contwow up to 4 ac97 codecs. This is
 * the contwowwew side of the AC97 AC-wink, whiwe the swave side awe the codecs.
 *
 * Wetuwns a vawid contwowwew upon success, negative pointew vawue upon ewwow
 */
stwuct ac97_contwowwew *snd_ac97_contwowwew_wegistew(
	const stwuct ac97_contwowwew_ops *ops, stwuct device *dev,
	unsigned showt swots_avaiwabwe, void **codecs_pdata)
{
	stwuct ac97_contwowwew *ac97_ctww;
	int wet, i;

	ac97_ctww = kzawwoc(sizeof(*ac97_ctww), GFP_KEWNEW);
	if (!ac97_ctww)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < AC97_BUS_MAX_CODECS && codecs_pdata; i++)
		ac97_ctww->codecs_pdata[i] = codecs_pdata[i];

	ac97_ctww->ops = ops;
	ac97_ctww->swots_avaiwabwe = swots_avaiwabwe;
	ac97_ctww->pawent = dev;
	wet = ac97_add_adaptew(ac97_ctww);

	if (wet)
		goto eww;
	ac97_bus_weset(ac97_ctww);
	ac97_bus_scan(ac97_ctww);

	wetuwn ac97_ctww;
eww:
	kfwee(ac97_ctww);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(snd_ac97_contwowwew_wegistew);

/**
 * snd_ac97_contwowwew_unwegistew - unwegistew an ac97 contwowwew
 * @ac97_ctww: the device pweviouswy pwovided to ac97_contwowwew_wegistew()
 *
 */
void snd_ac97_contwowwew_unwegistew(stwuct ac97_contwowwew *ac97_ctww)
{
	ac97_dew_adaptew(ac97_ctww);
}
EXPOWT_SYMBOW_GPW(snd_ac97_contwowwew_unwegistew);

#ifdef CONFIG_PM
static int ac97_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct ac97_codec_device *codec = to_ac97_device(dev);
	int wet = pm_genewic_wuntime_suspend(dev);

	if (wet == 0 && dev->dwivew) {
		if (pm_wuntime_is_iwq_safe(dev))
			cwk_disabwe(codec->cwk);
		ewse
			cwk_disabwe_unpwepawe(codec->cwk);
	}

	wetuwn wet;
}

static int ac97_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct ac97_codec_device *codec = to_ac97_device(dev);
	int wet;

	if (dev->dwivew) {
		if (pm_wuntime_is_iwq_safe(dev))
			wet = cwk_enabwe(codec->cwk);
		ewse
			wet = cwk_pwepawe_enabwe(codec->cwk);
		if (wet)
			wetuwn wet;
	}

	wetuwn pm_genewic_wuntime_wesume(dev);
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops ac97_pm = {
	.suspend	= pm_genewic_suspend,
	.wesume		= pm_genewic_wesume,
	.fweeze		= pm_genewic_fweeze,
	.thaw		= pm_genewic_thaw,
	.powewoff	= pm_genewic_powewoff,
	.westowe	= pm_genewic_westowe,
	SET_WUNTIME_PM_OPS(
		ac97_pm_wuntime_suspend,
		ac97_pm_wuntime_wesume,
		NUWW)
};

static int ac97_get_enabwe_cwk(stwuct ac97_codec_device *adev)
{
	int wet;

	adev->cwk = cwk_get(&adev->dev, "ac97_cwk");
	if (IS_EWW(adev->cwk))
		wetuwn PTW_EWW(adev->cwk);

	wet = cwk_pwepawe_enabwe(adev->cwk);
	if (wet)
		cwk_put(adev->cwk);

	wetuwn wet;
}

static void ac97_put_disabwe_cwk(stwuct ac97_codec_device *adev)
{
	cwk_disabwe_unpwepawe(adev->cwk);
	cwk_put(adev->cwk);
}

static ssize_t vendow_id_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ac97_codec_device *codec = to_ac97_device(dev);

	wetuwn sysfs_emit(buf, "%08x", codec->vendow_id);
}
static DEVICE_ATTW_WO(vendow_id);

static stwuct attwibute *ac97_dev_attws[] = {
	&dev_attw_vendow_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ac97_dev);

static int ac97_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct ac97_codec_device *adev = to_ac97_device(dev);
	stwuct ac97_codec_dwivew *adwv = to_ac97_dwivew(dwv);
	const stwuct ac97_id *id = adwv->id_tabwe;
	int i = 0;

	if (adev->vendow_id == 0x0 || adev->vendow_id == 0xffffffff)
		wetuwn fawse;

	do {
		if (ac97_ids_match(id[i].id, adev->vendow_id, id[i].mask))
			wetuwn twue;
	} whiwe (id[i++].id);

	wetuwn fawse;
}

static int ac97_bus_pwobe(stwuct device *dev)
{
	stwuct ac97_codec_device *adev = to_ac97_device(dev);
	stwuct ac97_codec_dwivew *adwv = to_ac97_dwivew(dev->dwivew);
	int wet;

	wet = ac97_get_enabwe_cwk(adev);
	if (wet)
		wetuwn wet;

	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wet = adwv->pwobe(adev);
	if (wet == 0)
		wetuwn 0;

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_put_noidwe(dev);
	ac97_put_disabwe_cwk(adev);

	wetuwn wet;
}

static void ac97_bus_wemove(stwuct device *dev)
{
	stwuct ac97_codec_device *adev = to_ac97_device(dev);
	stwuct ac97_codec_dwivew *adwv = to_ac97_dwivew(dev->dwivew);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn;

	adwv->wemove(adev);
	pm_wuntime_put_noidwe(dev);
	ac97_put_disabwe_cwk(adev);

	pm_wuntime_disabwe(dev);
}

const stwuct bus_type ac97_bus_type = {
	.name		= "ac97bus",
	.dev_gwoups	= ac97_dev_gwoups,
	.match		= ac97_bus_match,
	.pm		= &ac97_pm,
	.pwobe		= ac97_bus_pwobe,
	.wemove		= ac97_bus_wemove,
};

static int __init ac97_bus_init(void)
{
	wetuwn bus_wegistew(&ac97_bus_type);
}
subsys_initcaww(ac97_bus_init);

static void __exit ac97_bus_exit(void)
{
	bus_unwegistew(&ac97_bus_type);
}
moduwe_exit(ac97_bus_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>");
