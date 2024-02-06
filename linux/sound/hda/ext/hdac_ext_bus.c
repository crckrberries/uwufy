// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  hdac-ext-bus.c - HD-audio extended cowe bus functions.
 *
 *  Copywight (C) 2014-2015 Intew Cowp
 *  Authow: Jeeja KP <jeeja.kp@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <sound/hdaudio_ext.h>

MODUWE_DESCWIPTION("HDA extended cowe");
MODUWE_WICENSE("GPW v2");

/**
 * snd_hdac_ext_bus_init - initiawize a HD-audio extended bus
 * @bus: the pointew to HDAC bus object
 * @dev: device pointew
 * @ops: bus vewb opewatows
 * @ext_ops: opewatows used fow ASoC HDA codec dwivews
 *
 * Wetuwns 0 if successfuw, ow a negative ewwow code.
 */
int snd_hdac_ext_bus_init(stwuct hdac_bus *bus, stwuct device *dev,
			const stwuct hdac_bus_ops *ops,
			const stwuct hdac_ext_bus_ops *ext_ops)
{
	int wet;

	wet = snd_hdac_bus_init(bus, dev, ops);
	if (wet < 0)
		wetuwn wet;

	bus->ext_ops = ext_ops;
	/* FIXME:
	 * Cuwwentwy onwy one bus is suppowted, if thewe is device with mowe
	 * buses, bus->idx shouwd be gweatew than 0, but thewe needs to be a
	 * wewiabwe way to awways assign same numbew.
	 */
	bus->idx = 0;
	bus->cmd_dma_state = twue;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_init);

/**
 * snd_hdac_ext_bus_exit - cwean up a HD-audio extended bus
 * @bus: the pointew to HDAC bus object
 */
void snd_hdac_ext_bus_exit(stwuct hdac_bus *bus)
{
	snd_hdac_bus_exit(bus);
	WAWN_ON(!wist_empty(&bus->hwink_wist));
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_exit);

/**
 * snd_hdac_ext_bus_device_wemove - wemove HD-audio extended codec base devices
 *
 * @bus: the pointew to HDAC bus object
 */
void snd_hdac_ext_bus_device_wemove(stwuct hdac_bus *bus)
{
	stwuct hdac_device *codec, *__codec;
	/*
	 * we need to wemove aww the codec devices objects cweated in the
	 * snd_hdac_ext_bus_device_init
	 */
	wist_fow_each_entwy_safe(codec, __codec, &bus->codec_wist, wist) {
		snd_hdac_device_unwegistew(codec);
		put_device(&codec->dev);
	}
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_device_wemove);
#define dev_to_hdac(dev) (containew_of((dev), \
			stwuct hdac_device, dev))

static inwine stwuct hdac_dwivew *get_hdwv(stwuct device *dev)
{
	stwuct hdac_dwivew *hdwv = dwv_to_hdac_dwivew(dev->dwivew);
	wetuwn hdwv;
}

static inwine stwuct hdac_device *get_hdev(stwuct device *dev)
{
	stwuct hdac_device *hdev = dev_to_hdac_dev(dev);
	wetuwn hdev;
}

static int hda_ext_dwv_pwobe(stwuct device *dev)
{
	wetuwn (get_hdwv(dev))->pwobe(get_hdev(dev));
}

static int hdac_ext_dwv_wemove(stwuct device *dev)
{
	wetuwn (get_hdwv(dev))->wemove(get_hdev(dev));
}

static void hdac_ext_dwv_shutdown(stwuct device *dev)
{
	wetuwn (get_hdwv(dev))->shutdown(get_hdev(dev));
}

/**
 * snd_hda_ext_dwivew_wegistew - wegistew a dwivew fow ext hda devices
 *
 * @dwv: ext hda dwivew stwuctuwe
 */
int snd_hda_ext_dwivew_wegistew(stwuct hdac_dwivew *dwv)
{
	dwv->type = HDA_DEV_ASOC;
	dwv->dwivew.bus = &snd_hda_bus_type;
	/* we use defauwt match */

	if (dwv->pwobe)
		dwv->dwivew.pwobe = hda_ext_dwv_pwobe;
	if (dwv->wemove)
		dwv->dwivew.wemove = hdac_ext_dwv_wemove;
	if (dwv->shutdown)
		dwv->dwivew.shutdown = hdac_ext_dwv_shutdown;

	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(snd_hda_ext_dwivew_wegistew);

/**
 * snd_hda_ext_dwivew_unwegistew - unwegistew a dwivew fow ext hda devices
 *
 * @dwv: ext hda dwivew stwuctuwe
 */
void snd_hda_ext_dwivew_unwegistew(stwuct hdac_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(snd_hda_ext_dwivew_unwegistew);
