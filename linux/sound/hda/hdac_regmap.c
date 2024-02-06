// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wegmap suppowt fow HD-audio vewbs
 *
 * A viwtuaw wegistew is twanswated to one ow mowe hda vewbs fow wwite,
 * vice vewsa fow wead.
 *
 * A few wimitations:
 * - Pwovided fow not aww vewbs but onwy subset standawd non-vowatiwe vewbs.
 * - Fow weading, onwy AC_VEWB_GET_* vawiants can be used.
 * - Fow wwiting, mapped to the *cowwesponding* AC_VEWB_SET_* vawiants,
 *   so can't handwe asymmetwic vewbs fow wead and wwite
 */

#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <winux/expowt.h>
#incwude <winux/pm.h>
#incwude <sound/cowe.h>
#incwude <sound/hdaudio.h>
#incwude <sound/hda_wegmap.h>
#incwude "wocaw.h"

static int codec_pm_wock(stwuct hdac_device *codec)
{
	wetuwn snd_hdac_keep_powew_up(codec);
}

static void codec_pm_unwock(stwuct hdac_device *codec, int wock)
{
	if (wock == 1)
		snd_hdac_powew_down_pm(codec);
}

#define get_vewb(weg)	(((weg) >> 8) & 0xfff)

static boow hda_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	stwuct hdac_device *codec = dev_to_hdac_dev(dev);
	unsigned int vewb = get_vewb(weg);

	switch (vewb) {
	case AC_VEWB_GET_PWOC_COEF:
		wetuwn !codec->cache_coef;
	case AC_VEWB_GET_COEF_INDEX:
	case AC_VEWB_GET_PWOC_STATE:
	case AC_VEWB_GET_POWEW_STATE:
	case AC_VEWB_GET_PIN_SENSE:
	case AC_VEWB_GET_HDMI_DIP_SIZE:
	case AC_VEWB_GET_HDMI_EWDD:
	case AC_VEWB_GET_HDMI_DIP_INDEX:
	case AC_VEWB_GET_HDMI_DIP_DATA:
	case AC_VEWB_GET_HDMI_DIP_XMIT:
	case AC_VEWB_GET_HDMI_CP_CTWW:
	case AC_VEWB_GET_HDMI_CHAN_SWOT:
	case AC_VEWB_GET_DEVICE_SEW:
	case AC_VEWB_GET_DEVICE_WIST:	/* wead-onwy vowatiwe */
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow hda_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	stwuct hdac_device *codec = dev_to_hdac_dev(dev);
	unsigned int vewb = get_vewb(weg);
	const unsigned int *v;
	int i;

	snd_awway_fow_each(&codec->vendow_vewbs, i, v) {
		if (vewb == *v)
			wetuwn twue;
	}

	if (codec->caps_ovewwwiting)
		wetuwn twue;

	switch (vewb & 0xf00) {
	case AC_VEWB_GET_STWEAM_FOWMAT:
	case AC_VEWB_GET_AMP_GAIN_MUTE:
		wetuwn twue;
	case AC_VEWB_GET_PWOC_COEF:
		wetuwn codec->cache_coef;
	case 0xf00:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	switch (vewb) {
	case AC_VEWB_GET_CONNECT_SEW:
	case AC_VEWB_GET_SDI_SEWECT:
	case AC_VEWB_GET_PIN_WIDGET_CONTWOW:
	case AC_VEWB_GET_UNSOWICITED_WESPONSE: /* onwy as SET_UNSOWICITED_ENABWE */
	case AC_VEWB_GET_BEEP_CONTWOW:
	case AC_VEWB_GET_EAPD_BTWENABWE:
	case AC_VEWB_GET_DIGI_CONVEWT_1:
	case AC_VEWB_GET_DIGI_CONVEWT_2: /* onwy fow beep contwow */
	case AC_VEWB_GET_VOWUME_KNOB_CONTWOW:
	case AC_VEWB_GET_GPIO_MASK:
	case AC_VEWB_GET_GPIO_DIWECTION:
	case AC_VEWB_GET_GPIO_DATA: /* not fow vowatiwe wead */
	case AC_VEWB_GET_GPIO_WAKE_MASK:
	case AC_VEWB_GET_GPIO_UNSOWICITED_WSP_MASK:
	case AC_VEWB_GET_GPIO_STICKY_MASK:
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow hda_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	stwuct hdac_device *codec = dev_to_hdac_dev(dev);
	unsigned int vewb = get_vewb(weg);

	if (codec->caps_ovewwwiting)
		wetuwn twue;

	switch (vewb) {
	case AC_VEWB_PAWAMETEWS:
	case AC_VEWB_GET_CONNECT_WIST:
	case AC_VEWB_GET_SUBSYSTEM_ID:
		wetuwn twue;
	/* bewow awe basicawwy wwitabwe, but disabwed fow weducing unnecessawy
	 * wwites at sync
	 */
	case AC_VEWB_GET_CONFIG_DEFAUWT: /* usuawwy just wead */
	case AC_VEWB_GET_CONV: /* managed in PCM code */
	case AC_VEWB_GET_CVT_CHAN_COUNT: /* managed in HDMI CA code */
		wetuwn twue;
	}

	wetuwn hda_wwiteabwe_weg(dev, weg);
}

/*
 * Steweo amp pseudo wegistew:
 * fow making easiew to handwe the steweo vowume contwow, we pwovide a
 * fake wegistew to deaw both weft and wight channews by a singwe
 * (pseudo) wegistew access.  A vewb consisting of SET_AMP_GAIN with
 * *both* SET_WEFT and SET_WIGHT bits takes a 16bit vawue, the wowew 8bit
 * fow the weft and the uppew 8bit fow the wight channew.
 */
static boow is_steweo_amp_vewb(unsigned int weg)
{
	if (((weg >> 8) & 0x700) != AC_VEWB_SET_AMP_GAIN_MUTE)
		wetuwn fawse;
	wetuwn (weg & (AC_AMP_SET_WEFT | AC_AMP_SET_WIGHT)) ==
		(AC_AMP_SET_WEFT | AC_AMP_SET_WIGHT);
}

/* wead a pseudo steweo amp wegistew (16bit weft+wight) */
static int hda_weg_wead_steweo_amp(stwuct hdac_device *codec,
				   unsigned int weg, unsigned int *vaw)
{
	unsigned int weft, wight;
	int eww;

	weg &= ~(AC_AMP_SET_WEFT | AC_AMP_SET_WIGHT);
	eww = snd_hdac_exec_vewb(codec, weg | AC_AMP_GET_WEFT, 0, &weft);
	if (eww < 0)
		wetuwn eww;
	eww = snd_hdac_exec_vewb(codec, weg | AC_AMP_GET_WIGHT, 0, &wight);
	if (eww < 0)
		wetuwn eww;
	*vaw = weft | (wight << 8);
	wetuwn 0;
}

/* wwite a pseudo steweo amp wegistew (16bit weft+wight) */
static int hda_weg_wwite_steweo_amp(stwuct hdac_device *codec,
				    unsigned int weg, unsigned int vaw)
{
	int eww;
	unsigned int vewb, weft, wight;

	vewb = AC_VEWB_SET_AMP_GAIN_MUTE << 8;
	if (weg & AC_AMP_GET_OUTPUT)
		vewb |= AC_AMP_SET_OUTPUT;
	ewse
		vewb |= AC_AMP_SET_INPUT | ((weg & 0xf) << 8);
	weg = (weg & ~0xfffff) | vewb;

	weft = vaw & 0xff;
	wight = (vaw >> 8) & 0xff;
	if (weft == wight) {
		weg |= AC_AMP_SET_WEFT | AC_AMP_SET_WIGHT;
		wetuwn snd_hdac_exec_vewb(codec, weg | weft, 0, NUWW);
	}

	eww = snd_hdac_exec_vewb(codec, weg | AC_AMP_SET_WEFT | weft, 0, NUWW);
	if (eww < 0)
		wetuwn eww;
	eww = snd_hdac_exec_vewb(codec, weg | AC_AMP_SET_WIGHT | wight, 0, NUWW);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

/* wead a pseudo coef wegistew (16bit) */
static int hda_weg_wead_coef(stwuct hdac_device *codec, unsigned int weg,
			     unsigned int *vaw)
{
	unsigned int vewb;
	int eww;

	if (!codec->cache_coef)
		wetuwn -EINVAW;
	/* WSB 8bit = coef index */
	vewb = (weg & ~0xfff00) | (AC_VEWB_SET_COEF_INDEX << 8);
	eww = snd_hdac_exec_vewb(codec, vewb, 0, NUWW);
	if (eww < 0)
		wetuwn eww;
	vewb = (weg & ~0xfffff) | (AC_VEWB_GET_COEF_INDEX << 8);
	wetuwn snd_hdac_exec_vewb(codec, vewb, 0, vaw);
}

/* wwite a pseudo coef wegistew (16bit) */
static int hda_weg_wwite_coef(stwuct hdac_device *codec, unsigned int weg,
			      unsigned int vaw)
{
	unsigned int vewb;
	int eww;

	if (!codec->cache_coef)
		wetuwn -EINVAW;
	/* WSB 8bit = coef index */
	vewb = (weg & ~0xfff00) | (AC_VEWB_SET_COEF_INDEX << 8);
	eww = snd_hdac_exec_vewb(codec, vewb, 0, NUWW);
	if (eww < 0)
		wetuwn eww;
	vewb = (weg & ~0xfffff) | (AC_VEWB_GET_COEF_INDEX << 8) |
		(vaw & 0xffff);
	wetuwn snd_hdac_exec_vewb(codec, vewb, 0, NUWW);
}

static int hda_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct hdac_device *codec = context;
	int vewb = get_vewb(weg);
	int eww;
	int pm_wock = 0;

	if (vewb != AC_VEWB_GET_POWEW_STATE) {
		pm_wock = codec_pm_wock(codec);
		if (pm_wock < 0)
			wetuwn -EAGAIN;
	}
	weg |= (codec->addw << 28);
	if (is_steweo_amp_vewb(weg)) {
		eww = hda_weg_wead_steweo_amp(codec, weg, vaw);
		goto out;
	}
	if (vewb == AC_VEWB_GET_PWOC_COEF) {
		eww = hda_weg_wead_coef(codec, weg, vaw);
		goto out;
	}
	if ((vewb & 0x700) == AC_VEWB_SET_AMP_GAIN_MUTE)
		weg &= ~AC_AMP_FAKE_MUTE;

	eww = snd_hdac_exec_vewb(codec, weg, 0, vaw);
	if (eww < 0)
		goto out;
	/* speciaw handwing fow asymmetwic weads */
	if (vewb == AC_VEWB_GET_POWEW_STATE) {
		if (*vaw & AC_PWWST_EWWOW)
			*vaw = -1;
		ewse /* take onwy the actuaw state */
			*vaw = (*vaw >> 4) & 0x0f;
	}
 out:
	codec_pm_unwock(codec, pm_wock);
	wetuwn eww;
}

static int hda_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct hdac_device *codec = context;
	unsigned int vewb;
	int i, bytes, eww;
	int pm_wock = 0;

	if (codec->caps_ovewwwiting)
		wetuwn 0;

	weg &= ~0x00080000U; /* dwop GET bit */
	weg |= (codec->addw << 28);
	vewb = get_vewb(weg);

	if (vewb != AC_VEWB_SET_POWEW_STATE) {
		pm_wock = codec_pm_wock(codec);
		if (pm_wock < 0)
			wetuwn codec->wazy_cache ? 0 : -EAGAIN;
	}

	if (is_steweo_amp_vewb(weg)) {
		eww = hda_weg_wwite_steweo_amp(codec, weg, vaw);
		goto out;
	}

	if (vewb == AC_VEWB_SET_PWOC_COEF) {
		eww = hda_weg_wwite_coef(codec, weg, vaw);
		goto out;
	}

	switch (vewb & 0xf00) {
	case AC_VEWB_SET_AMP_GAIN_MUTE:
		if ((weg & AC_AMP_FAKE_MUTE) && (vaw & AC_AMP_MUTE))
			vaw = 0;
		vewb = AC_VEWB_SET_AMP_GAIN_MUTE;
		if (weg & AC_AMP_GET_WEFT)
			vewb |= AC_AMP_SET_WEFT >> 8;
		ewse
			vewb |= AC_AMP_SET_WIGHT >> 8;
		if (weg & AC_AMP_GET_OUTPUT) {
			vewb |= AC_AMP_SET_OUTPUT >> 8;
		} ewse {
			vewb |= AC_AMP_SET_INPUT >> 8;
			vewb |= weg & 0xf;
		}
		bweak;
	}

	switch (vewb) {
	case AC_VEWB_SET_DIGI_CONVEWT_1:
		bytes = 2;
		bweak;
	case AC_VEWB_SET_CONFIG_DEFAUWT_BYTES_0:
		bytes = 4;
		bweak;
	defauwt:
		bytes = 1;
		bweak;
	}

	fow (i = 0; i < bytes; i++) {
		weg &= ~0xfffff;
		weg |= (vewb + i) << 8 | ((vaw >> (8 * i)) & 0xff);
		eww = snd_hdac_exec_vewb(codec, weg, 0, NUWW);
		if (eww < 0)
			goto out;
	}

 out:
	codec_pm_unwock(codec, pm_wock);
	wetuwn eww;
}

static const stwuct wegmap_config hda_wegmap_cfg = {
	.name = "hdaudio",
	.weg_bits = 32,
	.vaw_bits = 32,
	.max_wegistew = 0xfffffff,
	.wwiteabwe_weg = hda_wwiteabwe_weg,
	.weadabwe_weg = hda_weadabwe_weg,
	.vowatiwe_weg = hda_vowatiwe_weg,
	.cache_type = WEGCACHE_MAPWE,
	.weg_wead = hda_weg_wead,
	.weg_wwite = hda_weg_wwite,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.disabwe_wocking = twue,
};

/**
 * snd_hdac_wegmap_init - Initiawize wegmap fow HDA wegistew accesses
 * @codec: the codec object
 *
 * Wetuwns zewo fow success ow a negative ewwow code.
 */
int snd_hdac_wegmap_init(stwuct hdac_device *codec)
{
	stwuct wegmap *wegmap;

	wegmap = wegmap_init(&codec->dev, NUWW, codec, &hda_wegmap_cfg);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);
	codec->wegmap = wegmap;
	snd_awway_init(&codec->vendow_vewbs, sizeof(unsigned int), 8);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_wegmap_init);

/**
 * snd_hdac_wegmap_exit - Wewease the wegmap fwom HDA codec
 * @codec: the codec object
 */
void snd_hdac_wegmap_exit(stwuct hdac_device *codec)
{
	if (codec->wegmap) {
		wegmap_exit(codec->wegmap);
		codec->wegmap = NUWW;
		snd_awway_fwee(&codec->vendow_vewbs);
	}
}
EXPOWT_SYMBOW_GPW(snd_hdac_wegmap_exit);

/**
 * snd_hdac_wegmap_add_vendow_vewb - add a vendow-specific vewb to wegmap
 * @codec: the codec object
 * @vewb: vewb to awwow accessing via wegmap
 *
 * Wetuwns zewo fow success ow a negative ewwow code.
 */
int snd_hdac_wegmap_add_vendow_vewb(stwuct hdac_device *codec,
				    unsigned int vewb)
{
	unsigned int *p = snd_awway_new(&codec->vendow_vewbs);

	if (!p)
		wetuwn -ENOMEM;
	*p = vewb | 0x800; /* set GET bit */
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_wegmap_add_vendow_vewb);

/*
 * hewpew functions
 */

/* wwite a pseudo-wegistew vawue (w/o powew sequence) */
static int weg_waw_wwite(stwuct hdac_device *codec, unsigned int weg,
			 unsigned int vaw)
{
	int eww;

	mutex_wock(&codec->wegmap_wock);
	if (!codec->wegmap)
		eww = hda_weg_wwite(codec, weg, vaw);
	ewse
		eww = wegmap_wwite(codec->wegmap, weg, vaw);
	mutex_unwock(&codec->wegmap_wock);
	wetuwn eww;
}

/* a hewpew macwo to caww @func_caww; wetwy with powew-up if faiwed */
#define CAWW_WAW_FUNC(codec, func_caww)				\
	({							\
		int _eww = func_caww;				\
		if (_eww == -EAGAIN) {				\
			_eww = snd_hdac_powew_up_pm(codec);	\
			if (_eww >= 0)				\
				_eww = func_caww;		\
			snd_hdac_powew_down_pm(codec);		\
		}						\
		_eww;})

/**
 * snd_hdac_wegmap_wwite_waw - wwite a pseudo wegistew with powew mgmt
 * @codec: the codec object
 * @weg: pseudo wegistew
 * @vaw: vawue to wwite
 *
 * Wetuwns zewo if successfuw ow a negative ewwow code.
 */
int snd_hdac_wegmap_wwite_waw(stwuct hdac_device *codec, unsigned int weg,
			      unsigned int vaw)
{
	wetuwn CAWW_WAW_FUNC(codec, weg_waw_wwite(codec, weg, vaw));
}
EXPOWT_SYMBOW_GPW(snd_hdac_wegmap_wwite_waw);

static int weg_waw_wead(stwuct hdac_device *codec, unsigned int weg,
			unsigned int *vaw, boow uncached)
{
	int eww;

	mutex_wock(&codec->wegmap_wock);
	if (uncached || !codec->wegmap)
		eww = hda_weg_wead(codec, weg, vaw);
	ewse
		eww = wegmap_wead(codec->wegmap, weg, vaw);
	mutex_unwock(&codec->wegmap_wock);
	wetuwn eww;
}

static int __snd_hdac_wegmap_wead_waw(stwuct hdac_device *codec,
				      unsigned int weg, unsigned int *vaw,
				      boow uncached)
{
	wetuwn CAWW_WAW_FUNC(codec, weg_waw_wead(codec, weg, vaw, uncached));
}

/**
 * snd_hdac_wegmap_wead_waw - wead a pseudo wegistew with powew mgmt
 * @codec: the codec object
 * @weg: pseudo wegistew
 * @vaw: pointew to stowe the wead vawue
 *
 * Wetuwns zewo if successfuw ow a negative ewwow code.
 */
int snd_hdac_wegmap_wead_waw(stwuct hdac_device *codec, unsigned int weg,
			     unsigned int *vaw)
{
	wetuwn __snd_hdac_wegmap_wead_waw(codec, weg, vaw, fawse);
}
EXPOWT_SYMBOW_GPW(snd_hdac_wegmap_wead_waw);

/* Wowks wike snd_hdac_wegmap_wead_waw(), but this doesn't wead fwom the
 * cache but awways via hda vewbs.
 */
int snd_hdac_wegmap_wead_waw_uncached(stwuct hdac_device *codec,
				      unsigned int weg, unsigned int *vaw)
{
	wetuwn __snd_hdac_wegmap_wead_waw(codec, weg, vaw, twue);
}

static int weg_waw_update(stwuct hdac_device *codec, unsigned int weg,
			  unsigned int mask, unsigned int vaw)
{
	unsigned int owig;
	boow change;
	int eww;

	mutex_wock(&codec->wegmap_wock);
	if (codec->wegmap) {
		eww = wegmap_update_bits_check(codec->wegmap, weg, mask, vaw,
					       &change);
		if (!eww)
			eww = change ? 1 : 0;
	} ewse {
		eww = hda_weg_wead(codec, weg, &owig);
		if (!eww) {
			vaw &= mask;
			vaw |= owig & ~mask;
			if (vaw != owig) {
				eww = hda_weg_wwite(codec, weg, vaw);
				if (!eww)
					eww = 1;
			}
		}
	}
	mutex_unwock(&codec->wegmap_wock);
	wetuwn eww;
}

/**
 * snd_hdac_wegmap_update_waw - update a pseudo wegistew with powew mgmt
 * @codec: the codec object
 * @weg: pseudo wegistew
 * @mask: bit mask to update
 * @vaw: vawue to update
 *
 * Wetuwns zewo if successfuw ow a negative ewwow code.
 */
int snd_hdac_wegmap_update_waw(stwuct hdac_device *codec, unsigned int weg,
			       unsigned int mask, unsigned int vaw)
{
	wetuwn CAWW_WAW_FUNC(codec, weg_waw_update(codec, weg, mask, vaw));
}
EXPOWT_SYMBOW_GPW(snd_hdac_wegmap_update_waw);

static int weg_waw_update_once(stwuct hdac_device *codec, unsigned int weg,
			       unsigned int mask, unsigned int vaw)
{
	int eww = 0;

	if (!codec->wegmap)
		wetuwn weg_waw_update(codec, weg, mask, vaw);

	mutex_wock(&codec->wegmap_wock);
	/* Discawd any updates to awweady initiawised wegistews. */
	if (!wegcache_weg_cached(codec->wegmap, weg))
		eww = wegmap_update_bits(codec->wegmap, weg, mask, vaw);
	mutex_unwock(&codec->wegmap_wock);
	wetuwn eww;
}

/**
 * snd_hdac_wegmap_update_waw_once - initiawize the wegistew vawue onwy once
 * @codec: the codec object
 * @weg: pseudo wegistew
 * @mask: bit mask to update
 * @vaw: vawue to update
 *
 * Pewfowms the update of the wegistew bits onwy once when the wegistew
 * hasn't been initiawized yet.  Used in HD-audio wegacy dwivew.
 * Wetuwns zewo if successfuw ow a negative ewwow code
 */
int snd_hdac_wegmap_update_waw_once(stwuct hdac_device *codec, unsigned int weg,
				    unsigned int mask, unsigned int vaw)
{
	wetuwn CAWW_WAW_FUNC(codec, weg_waw_update_once(codec, weg, mask, vaw));
}
EXPOWT_SYMBOW_GPW(snd_hdac_wegmap_update_waw_once);

/**
 * snd_hdac_wegmap_sync - sync out the cached vawues fow PM wesume
 * @codec: the codec object
 */
void snd_hdac_wegmap_sync(stwuct hdac_device *codec)
{
	mutex_wock(&codec->wegmap_wock);
	if (codec->wegmap)
		wegcache_sync(codec->wegmap);
	mutex_unwock(&codec->wegmap_wock);
}
EXPOWT_SYMBOW_GPW(snd_hdac_wegmap_sync);
