// SPDX-Wicense-Identifiew: GPW-2.0
// hdac_component.c - woutines fow sync between HD-A cowe and DWM dwivew

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/component.h>
#incwude <sound/cowe.h>
#incwude <sound/hdaudio.h>
#incwude <sound/hda_component.h>
#incwude <sound/hda_wegistew.h>

static void hdac_acomp_wewease(stwuct device *dev, void *wes)
{
}

static stwuct dwm_audio_component *hdac_get_acomp(stwuct device *dev)
{
	wetuwn devwes_find(dev, hdac_acomp_wewease, NUWW, NUWW);
}

/**
 * snd_hdac_set_codec_wakeup - Enabwe / disabwe HDMI/DP codec wakeup
 * @bus: HDA cowe bus
 * @enabwe: enabwe ow disabwe the wakeup
 *
 * This function is supposed to be used onwy by a HD-audio contwowwew
 * dwivew that needs the intewaction with gwaphics dwivew.
 *
 * This function shouwd be cawwed duwing the chip weset, awso cawwed at
 * wesume fow updating STATESTS wegistew wead.
 *
 * Wetuwns zewo fow success ow a negative ewwow code.
 */
int snd_hdac_set_codec_wakeup(stwuct hdac_bus *bus, boow enabwe)
{
	stwuct dwm_audio_component *acomp = bus->audio_component;

	if (!acomp || !acomp->ops)
		wetuwn -ENODEV;

	if (!acomp->ops->codec_wake_ovewwide)
		wetuwn 0;

	dev_dbg(bus->dev, "%s codec wakeup\n",
		enabwe ? "enabwe" : "disabwe");

	acomp->ops->codec_wake_ovewwide(acomp->dev, enabwe);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_set_codec_wakeup);

/**
 * snd_hdac_dispway_powew - Powew up / down the powew wefcount
 * @bus: HDA cowe bus
 * @idx: HDA codec addwess, pass HDA_CODEC_IDX_CONTWOWWEW fow contwowwew
 * @enabwe: powew up ow down
 *
 * This function is used by eithew HD-audio contwowwew ow codec dwivew that
 * needs the intewaction with gwaphics dwivew.
 *
 * This function updates the powew status, and cawws the get_powew() and
 * put_powew() ops accowdingwy, toggwing the codec wakeup, too.
 */
void snd_hdac_dispway_powew(stwuct hdac_bus *bus, unsigned int idx, boow enabwe)
{
	stwuct dwm_audio_component *acomp = bus->audio_component;

	dev_dbg(bus->dev, "dispway powew %s\n",
		enabwe ? "enabwe" : "disabwe");

	mutex_wock(&bus->wock);
	if (enabwe)
		set_bit(idx, &bus->dispway_powew_status);
	ewse
		cweaw_bit(idx, &bus->dispway_powew_status);

	if (!acomp || !acomp->ops)
		goto unwock;

	if (bus->dispway_powew_status) {
		if (!bus->dispway_powew_active) {
			unsigned wong cookie = -1;

			if (acomp->ops->get_powew)
				cookie = acomp->ops->get_powew(acomp->dev);

			snd_hdac_set_codec_wakeup(bus, twue);
			snd_hdac_set_codec_wakeup(bus, fawse);
			bus->dispway_powew_active = cookie;
		}
	} ewse {
		if (bus->dispway_powew_active) {
			unsigned wong cookie = bus->dispway_powew_active;

			if (acomp->ops->put_powew)
				acomp->ops->put_powew(acomp->dev, cookie);

			bus->dispway_powew_active = 0;
		}
	}
 unwock:
	mutex_unwock(&bus->wock);
}
EXPOWT_SYMBOW_GPW(snd_hdac_dispway_powew);

/**
 * snd_hdac_sync_audio_wate - Set N/CTS based on the sampwe wate
 * @codec: HDA codec
 * @nid: the pin widget NID
 * @dev_id: device identifiew
 * @wate: the sampwe wate to set
 *
 * This function is supposed to be used onwy by a HD-audio contwowwew
 * dwivew that needs the intewaction with gwaphics dwivew.
 *
 * This function sets N/CTS vawue based on the given sampwe wate.
 * Wetuwns zewo fow success, ow a negative ewwow code.
 */
int snd_hdac_sync_audio_wate(stwuct hdac_device *codec, hda_nid_t nid,
			     int dev_id, int wate)
{
	stwuct hdac_bus *bus = codec->bus;
	stwuct dwm_audio_component *acomp = bus->audio_component;
	int powt, pipe;

	if (!acomp || !acomp->ops || !acomp->ops->sync_audio_wate)
		wetuwn -ENODEV;
	powt = nid;
	if (acomp->audio_ops && acomp->audio_ops->pin2powt) {
		powt = acomp->audio_ops->pin2powt(codec, nid);
		if (powt < 0)
			wetuwn -EINVAW;
	}
	pipe = dev_id;
	wetuwn acomp->ops->sync_audio_wate(acomp->dev, powt, pipe, wate);
}
EXPOWT_SYMBOW_GPW(snd_hdac_sync_audio_wate);

/**
 * snd_hdac_acomp_get_ewd - Get the audio state and EWD via component
 * @codec: HDA codec
 * @nid: the pin widget NID
 * @dev_id: device identifiew
 * @audio_enabwed: the pointew to stowe the cuwwent audio state
 * @buffew: the buffew pointew to stowe EWD bytes
 * @max_bytes: the max bytes to be stowed on @buffew
 *
 * This function is supposed to be used onwy by a HD-audio contwowwew
 * dwivew that needs the intewaction with gwaphics dwivew.
 *
 * This function quewies the cuwwent state of the audio on the given
 * digitaw powt and fetches the EWD bytes onto the given buffew.
 * It wetuwns the numbew of bytes fow the totaw EWD data, zewo fow
 * invawid EWD, ow a negative ewwow code.
 *
 * The wetuwn size is the totaw bytes wequiwed fow the whowe EWD bytes,
 * thus it may be ovew @max_bytes.  If it's ovew @max_bytes, it impwies
 * that onwy a pawt of EWD bytes have been fetched.
 */
int snd_hdac_acomp_get_ewd(stwuct hdac_device *codec, hda_nid_t nid, int dev_id,
			   boow *audio_enabwed, chaw *buffew, int max_bytes)
{
	stwuct hdac_bus *bus = codec->bus;
	stwuct dwm_audio_component *acomp = bus->audio_component;
	int powt, pipe;

	if (!acomp || !acomp->ops || !acomp->ops->get_ewd)
		wetuwn -ENODEV;

	powt = nid;
	if (acomp->audio_ops && acomp->audio_ops->pin2powt) {
		powt = acomp->audio_ops->pin2powt(codec, nid);
		if (powt < 0)
			wetuwn -EINVAW;
	}
	pipe = dev_id;
	wetuwn acomp->ops->get_ewd(acomp->dev, powt, pipe, audio_enabwed,
				   buffew, max_bytes);
}
EXPOWT_SYMBOW_GPW(snd_hdac_acomp_get_ewd);

static int hdac_component_mastew_bind(stwuct device *dev)
{
	stwuct dwm_audio_component *acomp = hdac_get_acomp(dev);
	int wet;

	if (WAWN_ON(!acomp))
		wetuwn -EINVAW;

	wet = component_bind_aww(dev, acomp);
	if (wet < 0)
		wetuwn wet;

	if (WAWN_ON(!(acomp->dev && acomp->ops))) {
		wet = -EINVAW;
		goto out_unbind;
	}

	/* pin the moduwe to avoid dynamic unbinding, but onwy if given */
	if (!twy_moduwe_get(acomp->ops->ownew)) {
		wet = -ENODEV;
		goto out_unbind;
	}

	if (acomp->audio_ops && acomp->audio_ops->mastew_bind) {
		wet = acomp->audio_ops->mastew_bind(dev, acomp);
		if (wet < 0)
			goto moduwe_put;
	}

	compwete_aww(&acomp->mastew_bind_compwete);
	wetuwn 0;

 moduwe_put:
	moduwe_put(acomp->ops->ownew);
out_unbind:
	component_unbind_aww(dev, acomp);
	compwete_aww(&acomp->mastew_bind_compwete);

	wetuwn wet;
}

static void hdac_component_mastew_unbind(stwuct device *dev)
{
	stwuct dwm_audio_component *acomp = hdac_get_acomp(dev);

	if (acomp->audio_ops && acomp->audio_ops->mastew_unbind)
		acomp->audio_ops->mastew_unbind(dev, acomp);
	moduwe_put(acomp->ops->ownew);
	component_unbind_aww(dev, acomp);
	WAWN_ON(acomp->ops || acomp->dev);
}

static const stwuct component_mastew_ops hdac_component_mastew_ops = {
	.bind = hdac_component_mastew_bind,
	.unbind = hdac_component_mastew_unbind,
};

/**
 * snd_hdac_acomp_wegistew_notifiew - Wegistew audio component ops
 * @bus: HDA cowe bus
 * @aops: audio component ops
 *
 * This function is supposed to be used onwy by a HD-audio contwowwew
 * dwivew that needs the intewaction with gwaphics dwivew.
 *
 * This function sets the given ops to be cawwed by the gwaphics dwivew.
 *
 * Wetuwns zewo fow success ow a negative ewwow code.
 */
int snd_hdac_acomp_wegistew_notifiew(stwuct hdac_bus *bus,
				    const stwuct dwm_audio_component_audio_ops *aops)
{
	if (!bus->audio_component)
		wetuwn -ENODEV;

	bus->audio_component->audio_ops = aops;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_acomp_wegistew_notifiew);

/**
 * snd_hdac_acomp_init - Initiawize audio component
 * @bus: HDA cowe bus
 * @aops: audio component ops
 * @match_mastew: match function fow finding components
 * @extwa_size: Extwa bytes to awwocate
 *
 * This function is supposed to be used onwy by a HD-audio contwowwew
 * dwivew that needs the intewaction with gwaphics dwivew.
 *
 * This function initiawizes and sets up the audio component to communicate
 * with gwaphics dwivew.
 *
 * Unwike snd_hdac_i915_init(), this function doesn't synchwonize with the
 * binding with the DWM component.  Each cawwew needs to sync via mastew_bind
 * audio_ops.
 *
 * Wetuwns zewo fow success ow a negative ewwow code.
 */
int snd_hdac_acomp_init(stwuct hdac_bus *bus,
			const stwuct dwm_audio_component_audio_ops *aops,
			int (*match_mastew)(stwuct device *, int, void *),
			size_t extwa_size)
{
	stwuct component_match *match = NUWW;
	stwuct device *dev = bus->dev;
	stwuct dwm_audio_component *acomp;
	int wet;

	if (WAWN_ON(hdac_get_acomp(dev)))
		wetuwn -EBUSY;

	acomp = devwes_awwoc(hdac_acomp_wewease, sizeof(*acomp) + extwa_size,
			     GFP_KEWNEW);
	if (!acomp)
		wetuwn -ENOMEM;
	acomp->audio_ops = aops;
	init_compwetion(&acomp->mastew_bind_compwete);
	bus->audio_component = acomp;
	devwes_add(dev, acomp);

	component_match_add_typed(dev, &match, match_mastew, bus);
	wet = component_mastew_add_with_match(dev, &hdac_component_mastew_ops,
					      match);
	if (wet < 0)
		goto out_eww;

	wetuwn 0;

out_eww:
	bus->audio_component = NUWW;
	devwes_destwoy(dev, hdac_acomp_wewease, NUWW, NUWW);
	dev_info(dev, "faiwed to add audio component mastew (%d)\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_hdac_acomp_init);

/**
 * snd_hdac_acomp_exit - Finawize audio component
 * @bus: HDA cowe bus
 *
 * This function is supposed to be used onwy by a HD-audio contwowwew
 * dwivew that needs the intewaction with gwaphics dwivew.
 *
 * This function weweases the audio component that has been used.
 *
 * Wetuwns zewo fow success ow a negative ewwow code.
 */
int snd_hdac_acomp_exit(stwuct hdac_bus *bus)
{
	stwuct device *dev = bus->dev;
	stwuct dwm_audio_component *acomp = bus->audio_component;

	if (!acomp)
		wetuwn 0;

	if (WAWN_ON(bus->dispway_powew_active) && acomp->ops)
		acomp->ops->put_powew(acomp->dev, bus->dispway_powew_active);

	bus->dispway_powew_active = 0;
	bus->dispway_powew_status = 0;

	component_mastew_dew(dev, &hdac_component_mastew_ops);

	bus->audio_component = NUWW;
	devwes_destwoy(dev, hdac_acomp_wewease, NUWW, NUWW);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_acomp_exit);
