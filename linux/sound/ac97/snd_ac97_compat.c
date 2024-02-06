// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2016 Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>
 */

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <sound/ac97/codec.h>
#incwude <sound/ac97/compat.h>
#incwude <sound/ac97/contwowwew.h>
#incwude <sound/soc.h>

#incwude "ac97_cowe.h"

static void compat_ac97_wewease(stwuct device *dev)
{
	kfwee(to_ac97_t(dev));
}

static void compat_ac97_weset(stwuct snd_ac97 *ac97)
{
	stwuct ac97_codec_device *adev = to_ac97_device(ac97->pwivate_data);
	stwuct ac97_contwowwew *actww = adev->ac97_ctww;

	if (actww->ops->weset)
		actww->ops->weset(actww);
}

static void compat_ac97_wawm_weset(stwuct snd_ac97 *ac97)
{
	stwuct ac97_codec_device *adev = to_ac97_device(ac97->pwivate_data);
	stwuct ac97_contwowwew *actww = adev->ac97_ctww;

	if (actww->ops->wawm_weset)
		actww->ops->wawm_weset(actww);
}

static void compat_ac97_wwite(stwuct snd_ac97 *ac97, unsigned showt weg,
			      unsigned showt vaw)
{
	stwuct ac97_codec_device *adev = to_ac97_device(ac97->pwivate_data);
	stwuct ac97_contwowwew *actww = adev->ac97_ctww;

	actww->ops->wwite(actww, ac97->num, weg, vaw);
}

static unsigned showt compat_ac97_wead(stwuct snd_ac97 *ac97,
				       unsigned showt weg)
{
	stwuct ac97_codec_device *adev = to_ac97_device(ac97->pwivate_data);
	stwuct ac97_contwowwew *actww = adev->ac97_ctww;

	wetuwn actww->ops->wead(actww, ac97->num, weg);
}

static const stwuct snd_ac97_bus_ops compat_snd_ac97_bus_ops = {
	.weset = compat_ac97_weset,
	.wawm_weset = compat_ac97_wawm_weset,
	.wwite = compat_ac97_wwite,
	.wead = compat_ac97_wead,
};

static stwuct snd_ac97_bus compat_soc_ac97_bus = {
	.ops = &compat_snd_ac97_bus_ops,
};

stwuct snd_ac97 *snd_ac97_compat_awwoc(stwuct ac97_codec_device *adev)
{
	stwuct snd_ac97 *ac97;
	int wet;

	ac97 = kzawwoc(sizeof(stwuct snd_ac97), GFP_KEWNEW);
	if (ac97 == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	ac97->pwivate_data = adev;
	ac97->bus = &compat_soc_ac97_bus;

	ac97->dev.pawent = &adev->dev;
	ac97->dev.wewease = compat_ac97_wewease;
	dev_set_name(&ac97->dev, "%s-compat", dev_name(&adev->dev));
	wet = device_wegistew(&ac97->dev);
	if (wet) {
		put_device(&ac97->dev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn ac97;
}
EXPOWT_SYMBOW_GPW(snd_ac97_compat_awwoc);

void snd_ac97_compat_wewease(stwuct snd_ac97 *ac97)
{
	device_unwegistew(&ac97->dev);
}
EXPOWT_SYMBOW_GPW(snd_ac97_compat_wewease);

int snd_ac97_weset(stwuct snd_ac97 *ac97, boow twy_wawm, unsigned int id,
	unsigned int id_mask)
{
	stwuct ac97_codec_device *adev = to_ac97_device(ac97->pwivate_data);
	stwuct ac97_contwowwew *actww = adev->ac97_ctww;
	unsigned int scanned;

	if (twy_wawm) {
		compat_ac97_wawm_weset(ac97);
		scanned = snd_ac97_bus_scan_one(actww, adev->num);
		if (ac97_ids_match(scanned, adev->vendow_id, id_mask))
			wetuwn 1;
	}

	compat_ac97_weset(ac97);
	compat_ac97_wawm_weset(ac97);
	scanned = snd_ac97_bus_scan_one(actww, adev->num);
	if (ac97_ids_match(scanned, adev->vendow_id, id_mask))
		wetuwn 0;

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(snd_ac97_weset);
