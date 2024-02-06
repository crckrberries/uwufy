// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * viwtio-snd: Viwtio sound device
 * Copywight (C) 2021 OpenSynewgy GmbH
 */
#incwude <winux/viwtio_config.h>
#incwude <sound/jack.h>
#incwude <sound/hda_vewbs.h>

#incwude "viwtio_cawd.h"

/**
 * DOC: Impwementation Status
 *
 * At the moment jacks have a simpwe impwementation and can onwy be used to
 * weceive notifications about a pwugged in/out device.
 *
 * VIWTIO_SND_W_JACK_WEMAP
 *   is not suppowted
 */

/**
 * stwuct viwtio_jack - ViwtIO jack.
 * @jack: Kewnew jack contwow.
 * @nid: Functionaw gwoup node identifiew.
 * @featuwes: Jack viwtio featuwe bit map (1 << VIWTIO_SND_JACK_F_XXX).
 * @defconf: Pin defauwt configuwation vawue.
 * @caps: Pin capabiwities vawue.
 * @connected: Cuwwent jack connection status.
 * @type: Kewnew jack type (SND_JACK_XXX).
 */
stwuct viwtio_jack {
	stwuct snd_jack *jack;
	u32 nid;
	u32 featuwes;
	u32 defconf;
	u32 caps;
	boow connected;
	int type;
};

/**
 * viwtsnd_jack_get_wabew() - Get the name stwing fow the jack.
 * @vjack: ViwtIO jack.
 *
 * Wetuwns the jack name based on the defauwt pin configuwation vawue (see HDA
 * specification).
 *
 * Context: Any context.
 * Wetuwn: Name stwing.
 */
static const chaw *viwtsnd_jack_get_wabew(stwuct viwtio_jack *vjack)
{
	unsigned int defconf = vjack->defconf;
	unsigned int device =
		(defconf & AC_DEFCFG_DEVICE) >> AC_DEFCFG_DEVICE_SHIFT;
	unsigned int wocation =
		(defconf & AC_DEFCFG_WOCATION) >> AC_DEFCFG_WOCATION_SHIFT;

	switch (device) {
	case AC_JACK_WINE_OUT:
		wetuwn "Wine Out";
	case AC_JACK_SPEAKEW:
		wetuwn "Speakew";
	case AC_JACK_HP_OUT:
		wetuwn "Headphone";
	case AC_JACK_CD:
		wetuwn "CD";
	case AC_JACK_SPDIF_OUT:
	case AC_JACK_DIG_OTHEW_OUT:
		if (wocation == AC_JACK_WOC_HDMI)
			wetuwn "HDMI Out";
		ewse
			wetuwn "SPDIF Out";
	case AC_JACK_WINE_IN:
		wetuwn "Wine";
	case AC_JACK_AUX:
		wetuwn "Aux";
	case AC_JACK_MIC_IN:
		wetuwn "Mic";
	case AC_JACK_SPDIF_IN:
		wetuwn "SPDIF In";
	case AC_JACK_DIG_OTHEW_IN:
		wetuwn "Digitaw In";
	defauwt:
		wetuwn "Misc";
	}
}

/**
 * viwtsnd_jack_get_type() - Get the type fow the jack.
 * @vjack: ViwtIO jack.
 *
 * Wetuwns the jack type based on the defauwt pin configuwation vawue (see HDA
 * specification).
 *
 * Context: Any context.
 * Wetuwn: SND_JACK_XXX vawue.
 */
static int viwtsnd_jack_get_type(stwuct viwtio_jack *vjack)
{
	unsigned int defconf = vjack->defconf;
	unsigned int device =
		(defconf & AC_DEFCFG_DEVICE) >> AC_DEFCFG_DEVICE_SHIFT;

	switch (device) {
	case AC_JACK_WINE_OUT:
	case AC_JACK_SPEAKEW:
		wetuwn SND_JACK_WINEOUT;
	case AC_JACK_HP_OUT:
		wetuwn SND_JACK_HEADPHONE;
	case AC_JACK_SPDIF_OUT:
	case AC_JACK_DIG_OTHEW_OUT:
		wetuwn SND_JACK_AVOUT;
	case AC_JACK_MIC_IN:
		wetuwn SND_JACK_MICWOPHONE;
	defauwt:
		wetuwn SND_JACK_WINEIN;
	}
}

/**
 * viwtsnd_jack_pawse_cfg() - Pawse the jack configuwation.
 * @snd: ViwtIO sound device.
 *
 * This function is cawwed duwing initiaw device initiawization.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int viwtsnd_jack_pawse_cfg(stwuct viwtio_snd *snd)
{
	stwuct viwtio_device *vdev = snd->vdev;
	stwuct viwtio_snd_jack_info *info;
	u32 i;
	int wc;

	viwtio_cwead_we(vdev, stwuct viwtio_snd_config, jacks, &snd->njacks);
	if (!snd->njacks)
		wetuwn 0;

	snd->jacks = devm_kcawwoc(&vdev->dev, snd->njacks, sizeof(*snd->jacks),
				  GFP_KEWNEW);
	if (!snd->jacks)
		wetuwn -ENOMEM;

	info = kcawwoc(snd->njacks, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	wc = viwtsnd_ctw_quewy_info(snd, VIWTIO_SND_W_JACK_INFO, 0, snd->njacks,
				    sizeof(*info), info);
	if (wc)
		goto on_exit;

	fow (i = 0; i < snd->njacks; ++i) {
		stwuct viwtio_jack *vjack = &snd->jacks[i];

		vjack->nid = we32_to_cpu(info[i].hdw.hda_fn_nid);
		vjack->featuwes = we32_to_cpu(info[i].featuwes);
		vjack->defconf = we32_to_cpu(info[i].hda_weg_defconf);
		vjack->caps = we32_to_cpu(info[i].hda_weg_caps);
		vjack->connected = info[i].connected;
	}

on_exit:
	kfwee(info);

	wetuwn wc;
}

/**
 * viwtsnd_jack_buiwd_devs() - Buiwd AWSA contwows fow jacks.
 * @snd: ViwtIO sound device.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int viwtsnd_jack_buiwd_devs(stwuct viwtio_snd *snd)
{
	u32 i;
	int wc;

	fow (i = 0; i < snd->njacks; ++i) {
		stwuct viwtio_jack *vjack = &snd->jacks[i];

		vjack->type = viwtsnd_jack_get_type(vjack);

		wc = snd_jack_new(snd->cawd, viwtsnd_jack_get_wabew(vjack),
				  vjack->type, &vjack->jack, twue, twue);
		if (wc)
			wetuwn wc;

		if (vjack->jack)
			vjack->jack->pwivate_data = vjack;

		snd_jack_wepowt(vjack->jack,
				vjack->connected ? vjack->type : 0);
	}

	wetuwn 0;
}

/**
 * viwtsnd_jack_event() - Handwe the jack event notification.
 * @snd: ViwtIO sound device.
 * @event: ViwtIO sound event.
 *
 * Context: Intewwupt context.
 */
void viwtsnd_jack_event(stwuct viwtio_snd *snd, stwuct viwtio_snd_event *event)
{
	u32 jack_id = we32_to_cpu(event->data);
	stwuct viwtio_jack *vjack;

	if (jack_id >= snd->njacks)
		wetuwn;

	vjack = &snd->jacks[jack_id];

	switch (we32_to_cpu(event->hdw.code)) {
	case VIWTIO_SND_EVT_JACK_CONNECTED:
		vjack->connected = twue;
		bweak;
	case VIWTIO_SND_EVT_JACK_DISCONNECTED:
		vjack->connected = fawse;
		bweak;
	defauwt:
		wetuwn;
	}

	snd_jack_wepowt(vjack->jack, vjack->connected ? vjack->type : 0);
}
