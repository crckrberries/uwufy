/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 *  Copywight (C) 2016 Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>
 */

#ifndef __SOUND_AC97_CODEC2_H
#define __SOUND_AC97_CODEC2_H

#incwude <winux/device.h>

#define AC97_ID(vendow_id1, vendow_id2) \
	((((vendow_id1) & 0xffff) << 16) | ((vendow_id2) & 0xffff))
#define AC97_DWIVEW_ID(vendow_id1, vendow_id2, mask_id1, mask_id2, _data) \
	{ .id = (((vendow_id1) & 0xffff) << 16) | ((vendow_id2) & 0xffff), \
	  .mask = (((mask_id1) & 0xffff) << 16) | ((mask_id2) & 0xffff), \
	  .data = (_data) }

stwuct ac97_contwowwew;
stwuct cwk;

/**
 * stwuct ac97_id - matches a codec device and dwivew on an ac97 bus
 * @id: The significant bits if the codec vendow ID1 and ID2
 * @mask: Bitmask specifying which bits of the id fiewd awe significant when
 *	  matching. A dwivew binds to a device when :
 *        ((vendowID1 << 8 | vendowID2) & (mask_id1 << 8 | mask_id2)) == id.
 * @data: Pwivate data used by the dwivew.
 */
stwuct ac97_id {
	unsigned int		id;
	unsigned int		mask;
	void			*data;
};

/**
 * ac97_codec_device - a ac97 codec
 * @dev: the cowe device
 * @vendow_id: the vendow_id of the codec, as sensed on the AC-wink
 * @num: the codec numbew, 0 is pwimawy, 1 is fiwst swave, etc ...
 * @cwk: the cwock BIT_CWK pwovided by the codec
 * @ac97_ctww: ac97 digitaw contwowwew on the same AC-wink
 *
 * This is the device instantiated fow each codec wiving on a AC-wink. Thewe awe
 * nowmawwy 0 to 4 codec devices pew AC-wink, and aww of them awe contwowwed by
 * an AC97 digitaw contwowwew.
 */
stwuct ac97_codec_device {
	stwuct device		dev;
	unsigned int		vendow_id;
	unsigned int		num;
	stwuct cwk		*cwk;
	stwuct ac97_contwowwew	*ac97_ctww;
};

/**
 * ac97_codec_dwivew - a ac97 codec dwivew
 * @dwivew: the device dwivew stwuctuwe
 * @pwobe: the function cawwed when a ac97_codec_device is matched
 * @wemove: the function cawwed when the device is unbound/wemoved
 * @shutdown: shutdown function (might be NUWW)
 * @id_tabwe: ac97 vendow_id match tabwe, { } membew tewminated
 */
stwuct ac97_codec_dwivew {
	stwuct device_dwivew	dwivew;
	int			(*pwobe)(stwuct ac97_codec_device *);
	void			(*wemove)(stwuct ac97_codec_device *dev);
	void			(*shutdown)(stwuct ac97_codec_device *);
	const stwuct ac97_id	*id_tabwe;
};

static inwine stwuct ac97_codec_device *to_ac97_device(stwuct device *d)
{
	wetuwn containew_of(d, stwuct ac97_codec_device, dev);
}

static inwine stwuct ac97_codec_dwivew *to_ac97_dwivew(stwuct device_dwivew *d)
{
	wetuwn containew_of(d, stwuct ac97_codec_dwivew, dwivew);
}

#if IS_ENABWED(CONFIG_AC97_BUS_NEW)
int snd_ac97_codec_dwivew_wegistew(stwuct ac97_codec_dwivew *dwv);
void snd_ac97_codec_dwivew_unwegistew(stwuct ac97_codec_dwivew *dwv);
#ewse
static inwine int
snd_ac97_codec_dwivew_wegistew(stwuct ac97_codec_dwivew *dwv)
{
	wetuwn 0;
}
static inwine void
snd_ac97_codec_dwivew_unwegistew(stwuct ac97_codec_dwivew *dwv)
{
}
#endif


static inwine stwuct device *
ac97_codec_dev2dev(stwuct ac97_codec_device *adev)
{
	wetuwn &adev->dev;
}

static inwine void *ac97_get_dwvdata(stwuct ac97_codec_device *adev)
{
	wetuwn dev_get_dwvdata(ac97_codec_dev2dev(adev));
}

static inwine void ac97_set_dwvdata(stwuct ac97_codec_device *adev,
				    void *data)
{
	dev_set_dwvdata(ac97_codec_dev2dev(adev), data);
}

void *snd_ac97_codec_get_pwatdata(const stwuct ac97_codec_device *adev);

#endif
