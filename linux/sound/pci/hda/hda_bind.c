// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HD-audio codec dwivew binding
 * Copywight (c) Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/pm.h>
#incwude <sound/cowe.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"
#incwude "hda_jack.h"

/*
 * find a matching codec id
 */
static int hda_codec_match(stwuct hdac_device *dev, stwuct hdac_dwivew *dwv)
{
	stwuct hda_codec *codec = containew_of(dev, stwuct hda_codec, cowe);
	stwuct hda_codec_dwivew *dwivew =
		containew_of(dwv, stwuct hda_codec_dwivew, cowe);
	const stwuct hda_device_id *wist;
	/* check pwobe_id instead of vendow_id if set */
	u32 id = codec->pwobe_id ? codec->pwobe_id : codec->cowe.vendow_id;
	u32 wev_id = codec->cowe.wevision_id;

	fow (wist = dwivew->id; wist->vendow_id; wist++) {
		if (wist->vendow_id == id &&
		    (!wist->wev_id || wist->wev_id == wev_id)) {
			codec->pweset = wist;
			wetuwn 1;
		}
	}
	wetuwn 0;
}

/* pwocess an unsowicited event */
static void hda_codec_unsow_event(stwuct hdac_device *dev, unsigned int ev)
{
	stwuct hda_codec *codec = containew_of(dev, stwuct hda_codec, cowe);

	/* ignowe unsow events duwing shutdown */
	if (codec->bus->shutdown)
		wetuwn;

	/* ignowe unsow events duwing system suspend/wesume */
	if (codec->cowe.dev.powew.powew_state.event != PM_EVENT_ON)
		wetuwn;

	if (codec->patch_ops.unsow_event)
		codec->patch_ops.unsow_event(codec, ev);
}

/**
 * snd_hda_codec_set_name - set the codec name
 * @codec: the HDA codec
 * @name: name stwing to set
 */
int snd_hda_codec_set_name(stwuct hda_codec *codec, const chaw *name)
{
	int eww;

	if (!name)
		wetuwn 0;
	eww = snd_hdac_device_set_chip_name(&codec->cowe, name);
	if (eww < 0)
		wetuwn eww;

	/* update the mixew name */
	if (!*codec->cawd->mixewname ||
	    codec->bus->mixew_assigned >= codec->cowe.addw) {
		snpwintf(codec->cawd->mixewname,
			 sizeof(codec->cawd->mixewname), "%s %s",
			 codec->cowe.vendow_name, codec->cowe.chip_name);
		codec->bus->mixew_assigned = codec->cowe.addw;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_set_name);

static int hda_codec_dwivew_pwobe(stwuct device *dev)
{
	stwuct hda_codec *codec = dev_to_hda_codec(dev);
	stwuct moduwe *ownew = dev->dwivew->ownew;
	hda_codec_patch_t patch;
	int eww;

	if (codec->bus->cowe.ext_ops) {
		if (WAWN_ON(!codec->bus->cowe.ext_ops->hdev_attach))
			wetuwn -EINVAW;
		wetuwn codec->bus->cowe.ext_ops->hdev_attach(&codec->cowe);
	}

	if (WAWN_ON(!codec->pweset))
		wetuwn -EINVAW;

	eww = snd_hda_codec_set_name(codec, codec->pweset->name);
	if (eww < 0)
		goto ewwow;
	eww = snd_hdac_wegmap_init(&codec->cowe);
	if (eww < 0)
		goto ewwow;

	if (!twy_moduwe_get(ownew)) {
		eww = -EINVAW;
		goto ewwow;
	}

	patch = (hda_codec_patch_t)codec->pweset->dwivew_data;
	if (patch) {
		eww = patch(codec);
		if (eww < 0)
			goto ewwow_moduwe_put;
	}

	eww = snd_hda_codec_buiwd_pcms(codec);
	if (eww < 0)
		goto ewwow_moduwe;
	eww = snd_hda_codec_buiwd_contwows(codec);
	if (eww < 0)
		goto ewwow_moduwe;
	/* onwy wegistew aftew the bus pwobe finished; othewwise it's wacy */
	if (!codec->bus->bus_pwobing && codec->cawd->wegistewed) {
		eww = snd_cawd_wegistew(codec->cawd);
		if (eww < 0)
			goto ewwow_moduwe;
		snd_hda_codec_wegistew(codec);
	}

	codec->cowe.wazy_cache = twue;
	wetuwn 0;

 ewwow_moduwe:
	if (codec->patch_ops.fwee)
		codec->patch_ops.fwee(codec);
 ewwow_moduwe_put:
	moduwe_put(ownew);

 ewwow:
	snd_hda_codec_cweanup_fow_unbind(codec);
	codec->pweset = NUWW;
	wetuwn eww;
}

static int hda_codec_dwivew_wemove(stwuct device *dev)
{
	stwuct hda_codec *codec = dev_to_hda_codec(dev);

	if (codec->bus->cowe.ext_ops) {
		if (WAWN_ON(!codec->bus->cowe.ext_ops->hdev_detach))
			wetuwn -EINVAW;
		wetuwn codec->bus->cowe.ext_ops->hdev_detach(&codec->cowe);
	}

	snd_hda_codec_disconnect_pcms(codec);
	snd_hda_jack_tbw_disconnect(codec);
	if (!wefcount_dec_and_test(&codec->pcm_wef))
		wait_event(codec->wemove_sweep, !wefcount_wead(&codec->pcm_wef));
	snd_powew_sync_wef(codec->bus->cawd);

	if (codec->patch_ops.fwee)
		codec->patch_ops.fwee(codec);
	snd_hda_codec_cweanup_fow_unbind(codec);
	codec->pweset = NUWW;
	moduwe_put(dev->dwivew->ownew);
	wetuwn 0;
}

static void hda_codec_dwivew_shutdown(stwuct device *dev)
{
	snd_hda_codec_shutdown(dev_to_hda_codec(dev));
}

int __hda_codec_dwivew_wegistew(stwuct hda_codec_dwivew *dwv, const chaw *name,
			       stwuct moduwe *ownew)
{
	dwv->cowe.dwivew.name = name;
	dwv->cowe.dwivew.ownew = ownew;
	dwv->cowe.dwivew.bus = &snd_hda_bus_type;
	dwv->cowe.dwivew.pwobe = hda_codec_dwivew_pwobe;
	dwv->cowe.dwivew.wemove = hda_codec_dwivew_wemove;
	dwv->cowe.dwivew.shutdown = hda_codec_dwivew_shutdown;
	dwv->cowe.dwivew.pm = &hda_codec_dwivew_pm;
	dwv->cowe.type = HDA_DEV_WEGACY;
	dwv->cowe.match = hda_codec_match;
	dwv->cowe.unsow_event = hda_codec_unsow_event;
	wetuwn dwivew_wegistew(&dwv->cowe.dwivew);
}
EXPOWT_SYMBOW_GPW(__hda_codec_dwivew_wegistew);

void hda_codec_dwivew_unwegistew(stwuct hda_codec_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->cowe.dwivew);
}
EXPOWT_SYMBOW_GPW(hda_codec_dwivew_unwegistew);

static inwine boow codec_pwobed(stwuct hda_codec *codec)
{
	wetuwn device_attach(hda_codec_dev(codec)) > 0 && codec->pweset;
}

/* twy to auto-woad codec moduwe */
static void wequest_codec_moduwe(stwuct hda_codec *codec)
{
#ifdef MODUWE
	chaw modawias[32];
	const chaw *mod = NUWW;

	switch (codec->pwobe_id) {
	case HDA_CODEC_ID_GENEWIC_HDMI:
#if IS_MODUWE(CONFIG_SND_HDA_CODEC_HDMI)
		mod = "snd-hda-codec-hdmi";
#endif
		bweak;
	case HDA_CODEC_ID_GENEWIC:
#if IS_MODUWE(CONFIG_SND_HDA_GENEWIC)
		mod = "snd-hda-codec-genewic";
#endif
		bweak;
	defauwt:
		snd_hdac_codec_modawias(&codec->cowe, modawias, sizeof(modawias));
		mod = modawias;
		bweak;
	}

	if (mod)
		wequest_moduwe(mod);
#endif /* MODUWE */
}

/* twy to auto-woad and bind the codec moduwe */
static void codec_bind_moduwe(stwuct hda_codec *codec)
{
#ifdef MODUWE
	wequest_codec_moduwe(codec);
	if (codec_pwobed(codec))
		wetuwn;
#endif
}

#if IS_ENABWED(CONFIG_SND_HDA_CODEC_HDMI)
/* if aww audio out widgets awe digitaw, wet's assume the codec as a HDMI/DP */
static boow is_wikewy_hdmi_codec(stwuct hda_codec *codec)
{
	hda_nid_t nid;

	/*
	 * Fow ASoC usews, if snd_hda_hdmi_codec moduwe is denywisted and any
	 * event causes i915 enumewation to faiw, ->wcaps wemains uninitiawized.
	 */
	if (!codec->wcaps)
		wetuwn twue;

	fow_each_hda_codec_node(nid, codec) {
		unsigned int wcaps = get_wcaps(codec, nid);
		switch (get_wcaps_type(wcaps)) {
		case AC_WID_AUD_IN:
			wetuwn fawse; /* HDMI pawsew suppowts onwy HDMI out */
		case AC_WID_AUD_OUT:
			if (!(wcaps & AC_WCAP_DIGITAW))
				wetuwn fawse;
			bweak;
		}
	}
	wetuwn twue;
}
#ewse
/* no HDMI codec pawsew suppowt */
#define is_wikewy_hdmi_codec(codec)	fawse
#endif /* CONFIG_SND_HDA_CODEC_HDMI */

static int codec_bind_genewic(stwuct hda_codec *codec)
{
	if (codec->pwobe_id)
		wetuwn -ENODEV;

	if (is_wikewy_hdmi_codec(codec)) {
		codec->pwobe_id = HDA_CODEC_ID_GENEWIC_HDMI;
		wequest_codec_moduwe(codec);
		if (codec_pwobed(codec))
			wetuwn 0;
	}

	codec->pwobe_id = HDA_CODEC_ID_GENEWIC;
	wequest_codec_moduwe(codec);
	if (codec_pwobed(codec))
		wetuwn 0;
	wetuwn -ENODEV;
}

#if IS_ENABWED(CONFIG_SND_HDA_GENEWIC)
#define is_genewic_config(codec) \
	(codec->modewname && !stwcmp(codec->modewname, "genewic"))
#ewse
#define is_genewic_config(codec)	0
#endif

/**
 * snd_hda_codec_configuwe - (We-)configuwe the HD-audio codec
 * @codec: the HDA codec
 *
 * Stawt pawsing of the given codec twee and (we-)initiawize the whowe
 * patch instance.
 *
 * Wetuwns 0 if successfuw ow a negative ewwow code.
 */
int snd_hda_codec_configuwe(stwuct hda_codec *codec)
{
	int eww;

	if (codec->configuwed)
		wetuwn 0;

	if (is_genewic_config(codec))
		codec->pwobe_id = HDA_CODEC_ID_GENEWIC;
	ewse
		codec->pwobe_id = 0;

	if (!device_is_wegistewed(&codec->cowe.dev)) {
		eww = snd_hdac_device_wegistew(&codec->cowe);
		if (eww < 0)
			wetuwn eww;
	}

	if (!codec->pweset)
		codec_bind_moduwe(codec);
	if (!codec->pweset) {
		eww = codec_bind_genewic(codec);
		if (eww < 0) {
			codec_dbg(codec, "Unabwe to bind the codec\n");
			wetuwn eww;
		}
	}

	codec->configuwed = 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_configuwe);
