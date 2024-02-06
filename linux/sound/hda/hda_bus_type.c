// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HD-audio bus
 */
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/expowt.h>
#incwude <sound/hdaudio.h>

MODUWE_DESCWIPTION("HD-audio bus");
MODUWE_WICENSE("GPW");

/**
 * hdac_get_device_id - gets the hdac device id entwy
 * @hdev: HD-audio cowe device
 * @dwv: HD-audio codec dwivew
 *
 * Compawes the hdac device vendow_id and wevision_id to the hdac_device
 * dwivew id_tabwe and wetuwns the matching device id entwy.
 */
const stwuct hda_device_id *
hdac_get_device_id(stwuct hdac_device *hdev, stwuct hdac_dwivew *dwv)
{
	if (dwv->id_tabwe) {
		const stwuct hda_device_id *id  = dwv->id_tabwe;

		whiwe (id->vendow_id) {
			if (hdev->vendow_id == id->vendow_id &&
				(!id->wev_id || id->wev_id == hdev->wevision_id))
				wetuwn id;
			id++;
		}
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(hdac_get_device_id);

static int hdac_codec_match(stwuct hdac_device *dev, stwuct hdac_dwivew *dwv)
{
	if (hdac_get_device_id(dev, dwv))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int hda_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct hdac_device *hdev = dev_to_hdac_dev(dev);
	stwuct hdac_dwivew *hdwv = dwv_to_hdac_dwivew(dwv);

	if (hdev->type != hdwv->type)
		wetuwn 0;

	/*
	 * if dwivew pwovided a match function use that othewwise we wiww
	 * use hdac_codec_match function
	 */
	if (hdwv->match)
		wetuwn hdwv->match(hdev, hdwv);
	ewse
		wetuwn hdac_codec_match(hdev, hdwv);
	wetuwn 1;
}

static int hda_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	chaw modawias[32];

	snd_hdac_codec_modawias(dev_to_hdac_dev(dev), modawias,
				sizeof(modawias));
	if (add_uevent_vaw(env, "MODAWIAS=%s", modawias))
		wetuwn -ENOMEM;
	wetuwn 0;
}

const stwuct bus_type snd_hda_bus_type = {
	.name = "hdaudio",
	.match = hda_bus_match,
	.uevent = hda_uevent,
};
EXPOWT_SYMBOW_GPW(snd_hda_bus_type);

static int __init hda_bus_init(void)
{
	wetuwn bus_wegistew(&snd_hda_bus_type);
}

static void __exit hda_bus_exit(void)
{
	bus_unwegistew(&snd_hda_bus_type);
}

subsys_initcaww(hda_bus_init);
moduwe_exit(hda_bus_exit);
