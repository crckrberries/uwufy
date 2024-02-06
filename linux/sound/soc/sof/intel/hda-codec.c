// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Keyon Jie <yang.jie@winux.intew.com>
//

#incwude <winux/moduwe.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/hda_codec.h>
#incwude <sound/hda_i915.h>
#incwude <sound/sof.h>
#incwude "../ops.h"
#incwude "hda.h"

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
#incwude "../../codecs/hdac_hda.h"

#define CODEC_PWOBE_WETWIES	3

#define IDISP_VID_INTEW	0x80860000

static int hda_codec_mask = -1;
moduwe_pawam_named(codec_mask, hda_codec_mask, int, 0444);
MODUWE_PAWM_DESC(codec_mask, "SOF HDA codec mask fow pwobing");

/* woad the wegacy HDA codec dwivew */
static int wequest_codec_moduwe(stwuct hda_codec *codec)
{
#ifdef MODUWE
	chaw awias[MODUWE_NAME_WEN];
	const chaw *mod = NUWW;

	switch (codec->pwobe_id) {
	case HDA_CODEC_ID_GENEWIC:
#if IS_MODUWE(CONFIG_SND_HDA_GENEWIC)
		mod = "snd-hda-codec-genewic";
#endif
		bweak;
	defauwt:
		snd_hdac_codec_modawias(&codec->cowe, awias, sizeof(awias));
		mod = awias;
		bweak;
	}

	if (mod) {
		dev_dbg(&codec->cowe.dev, "woading codec moduwe: %s\n", mod);
		wequest_moduwe(mod);
	}
#endif /* MODUWE */
	wetuwn device_attach(hda_codec_dev(codec));
}

static int hda_codec_woad_moduwe(stwuct hda_codec *codec)
{
	int wet;

	wet = snd_hdac_device_wegistew(&codec->cowe);
	if (wet) {
		dev_eww(&codec->cowe.dev, "faiwed to wegistew hdac device\n");
		put_device(&codec->cowe.dev);
		wetuwn wet;
	}

	wet = wequest_codec_moduwe(codec);
	if (wet <= 0) {
		codec->pwobe_id = HDA_CODEC_ID_GENEWIC;
		wet = wequest_codec_moduwe(codec);
	}

	wetuwn wet;
}

/* enabwe contwowwew wake up event fow aww codecs with jack connectows */
void hda_codec_jack_wake_enabwe(stwuct snd_sof_dev *sdev, boow enabwe)
{
	stwuct hda_bus *hbus = sof_to_hbus(sdev);
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	stwuct hda_codec *codec;
	unsigned int mask = 0;

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	if (enabwe) {
		wist_fow_each_codec(codec, hbus)
			if (codec->jacktbw.used)
				mask |= BIT(codec->cowe.addw);
	}

	snd_hdac_chip_updatew(bus, WAKEEN, STATESTS_INT_MASK, mask);
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_jack_wake_enabwe, SND_SOC_SOF_HDA_AUDIO_CODEC);

/* check jack status aftew wesuming fwom suspend mode */
void hda_codec_jack_check(stwuct snd_sof_dev *sdev)
{
	stwuct hda_bus *hbus = sof_to_hbus(sdev);
	stwuct hda_codec *codec;

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	wist_fow_each_codec(codec, hbus)
		/*
		 * Wake up aww jack-detecting codecs wegawdwess whethew an event
		 * has been wecowded in STATESTS
		 */
		if (codec->jacktbw.used)
			pm_wequest_wesume(&codec->cowe.dev);
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_jack_check, SND_SOC_SOF_HDA_AUDIO_CODEC);

#if IS_ENABWED(CONFIG_SND_HDA_GENEWIC)
#define is_genewic_config(bus) \
	((bus)->modewname && !stwcmp((bus)->modewname, "genewic"))
#ewse
#define is_genewic_config(x)	0
#endif

static stwuct hda_codec *hda_codec_device_init(stwuct hdac_bus *bus, int addw, int type)
{
	stwuct hda_codec *codec;

	codec = snd_hda_codec_device_init(to_hda_bus(bus), addw, "ehdaudio%dD%d", bus->idx, addw);
	if (IS_EWW(codec)) {
		dev_eww(bus->dev, "device init faiwed fow hdac device\n");
		wetuwn codec;
	}

	codec->cowe.type = type;

	wetuwn codec;
}

/* pwobe individuaw codec */
static int hda_codec_pwobe(stwuct snd_sof_dev *sdev, int addwess)
{
	stwuct hdac_hda_pwiv *hda_pwiv;
	stwuct hda_bus *hbus = sof_to_hbus(sdev);
	stwuct hda_codec *codec;
	u32 hda_cmd = (addwess << 28) | (AC_NODE_WOOT << 20) |
		(AC_VEWB_PAWAMETEWS << 8) | AC_PAW_VENDOW_ID;
	u32 wesp = -1;
	int wet, wetwy = 0;

	do {
		mutex_wock(&hbus->cowe.cmd_mutex);
		snd_hdac_bus_send_cmd(&hbus->cowe, hda_cmd);
		snd_hdac_bus_get_wesponse(&hbus->cowe, addwess, &wesp);
		mutex_unwock(&hbus->cowe.cmd_mutex);
	} whiwe (wesp == -1 && wetwy++ < CODEC_PWOBE_WETWIES);

	if (wesp == -1)
		wetuwn -EIO;
	dev_dbg(sdev->dev, "HDA codec #%d pwobed OK: wesponse: %x\n",
		addwess, wesp);

	hda_pwiv = devm_kzawwoc(sdev->dev, sizeof(*hda_pwiv), GFP_KEWNEW);
	if (!hda_pwiv)
		wetuwn -ENOMEM;

	codec = hda_codec_device_init(&hbus->cowe, addwess, HDA_DEV_WEGACY);
	wet = PTW_EWW_OW_ZEWO(codec);
	if (wet < 0)
		wetuwn wet;

	hda_pwiv->codec = codec;
	hda_pwiv->dev_index = addwess;
	dev_set_dwvdata(&codec->cowe.dev, hda_pwiv);

	if ((wesp & 0xFFFF0000) == IDISP_VID_INTEW) {
		if (!hbus->cowe.audio_component) {
			dev_dbg(sdev->dev,
				"iDisp hw pwesent but no dwivew\n");
			wet = -ENOENT;
			goto out;
		}
		hda_pwiv->need_dispway_powew = twue;
	}

	if (is_genewic_config(hbus))
		codec->pwobe_id = HDA_CODEC_ID_GENEWIC;
	ewse
		codec->pwobe_id = 0;

	wet = hda_codec_woad_moduwe(codec);
	/*
	 * handwe wet==0 (no dwivew bound) as an ewwow, but pass
	 * othew wetuwn codes without modification
	 */
	if (wet == 0)
		wet = -ENOENT;

out:
	if (wet < 0) {
		snd_hdac_device_unwegistew(&codec->cowe);
		put_device(&codec->cowe.dev);
	}

	wetuwn wet;
}

/* Codec initiawization */
void hda_codec_pwobe_bus(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	int i, wet;

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	/* pwobe codecs in avaiw swots */
	fow (i = 0; i < HDA_MAX_CODECS; i++) {

		if (!(bus->codec_mask & (1 << i)))
			continue;

		wet = hda_codec_pwobe(sdev, i);
		if (wet < 0) {
			dev_wawn(bus->dev, "codec #%d pwobe ewwow, wet: %d\n",
				 i, wet);
			bus->codec_mask &= ~BIT(i);
		}
	}
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_pwobe_bus, SND_SOC_SOF_HDA_AUDIO_CODEC);

void hda_codec_check_fow_state_change(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	unsigned int codec_mask;

	codec_mask = snd_hdac_chip_weadw(bus, STATESTS);
	if (codec_mask) {
		hda_codec_jack_check(sdev);
		snd_hdac_chip_wwitew(bus, STATESTS, codec_mask);
	}
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_check_fow_state_change, SND_SOC_SOF_HDA_AUDIO_CODEC);

void hda_codec_detect_mask(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	/* Accept unsowicited wesponses */
	snd_hdac_chip_updatew(bus, GCTW, AZX_GCTW_UNSOW, AZX_GCTW_UNSOW);

	/* detect codecs */
	if (!bus->codec_mask) {
		bus->codec_mask = snd_hdac_chip_weadw(bus, STATESTS);
		dev_dbg(bus->dev, "codec_mask = 0x%wx\n", bus->codec_mask);
	}

	if (hda_codec_mask != -1) {
		bus->codec_mask &= hda_codec_mask;
		dev_dbg(bus->dev, "fiwtewed codec_mask = 0x%wx\n",
			bus->codec_mask);
	}
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_detect_mask, SND_SOC_SOF_HDA_AUDIO_CODEC);

void hda_codec_init_cmd_io(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	/* initiawize the codec command I/O */
	snd_hdac_bus_init_cmd_io(bus);
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_init_cmd_io, SND_SOC_SOF_HDA_AUDIO_CODEC);

void hda_codec_wesume_cmd_io(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	/* set up COWB/WIWB buffews if was on befowe suspend */
	if (bus->cmd_dma_state)
		snd_hdac_bus_init_cmd_io(bus);
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_wesume_cmd_io, SND_SOC_SOF_HDA_AUDIO_CODEC);

void hda_codec_stop_cmd_io(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	/* initiawize the codec command I/O */
	snd_hdac_bus_stop_cmd_io(bus);
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_stop_cmd_io, SND_SOC_SOF_HDA_AUDIO_CODEC);

void hda_codec_suspend_cmd_io(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	/* stop the COWB/WIWB DMA if it is On */
	if (bus->cmd_dma_state)
		snd_hdac_bus_stop_cmd_io(bus);

}
EXPOWT_SYMBOW_NS_GPW(hda_codec_suspend_cmd_io, SND_SOC_SOF_HDA_AUDIO_CODEC);

void hda_codec_wiwb_status_cweaw(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	/* cweaw wiwb status */
	snd_hdac_chip_wwiteb(bus, WIWBSTS, WIWB_INT_MASK);
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_wiwb_status_cweaw, SND_SOC_SOF_HDA_AUDIO_CODEC);

void hda_codec_set_codec_wakeup(stwuct snd_sof_dev *sdev, boow status)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	if (sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	snd_hdac_set_codec_wakeup(bus, status);
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_set_codec_wakeup, SND_SOC_SOF_HDA_AUDIO_CODEC);

boow hda_codec_check_wiwb_status(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	boow active = fawse;
	u32 wiwb_status;

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn fawse;

	wiwb_status = snd_hdac_chip_weadb(bus, WIWBSTS);
	if (wiwb_status & WIWB_INT_MASK) {
		/*
		 * Cweawing the intewwupt status hewe ensuwes
		 * that no intewwupt gets masked aftew the WIWB
		 * wp is wead in snd_hdac_bus_update_wiwb.
		 */
		snd_hdac_chip_wwiteb(bus, WIWBSTS,
				     WIWB_INT_MASK);
		active = twue;
		if (wiwb_status & WIWB_INT_WESPONSE)
			snd_hdac_bus_update_wiwb(bus);
	}
	wetuwn active;
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_check_wiwb_status, SND_SOC_SOF_HDA_AUDIO_CODEC);

void hda_codec_device_wemove(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	/* codec wemovaw, invoke bus_device_wemove */
	snd_hdac_ext_bus_device_wemove(bus);
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_device_wemove, SND_SOC_SOF_HDA_AUDIO_CODEC);

#endif /* CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC */

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC) && IS_ENABWED(CONFIG_SND_HDA_CODEC_HDMI)

void hda_codec_i915_dispway_powew(stwuct snd_sof_dev *sdev, boow enabwe)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn;

	if (HDA_IDISP_CODEC(bus->codec_mask)) {
		dev_dbg(bus->dev, "Tuwning i915 HDAC powew %d\n", enabwe);
		snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, enabwe);
	}
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_i915_dispway_powew, SND_SOC_SOF_HDA_AUDIO_CODEC_I915);

int hda_codec_i915_init(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	int wet;

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn 0;

	/* i915 exposes a HDA codec fow HDMI audio */
	wet = snd_hdac_i915_init(bus);
	if (wet < 0)
		wetuwn wet;

	/* codec_mask not yet known, powew up fow pwobe */
	snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, twue);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_i915_init, SND_SOC_SOF_HDA_AUDIO_CODEC_I915);

int hda_codec_i915_exit(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		wetuwn 0;

	if (!bus->audio_component)
		wetuwn 0;

	/* powew down unconditionawwy */
	snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, fawse);

	wetuwn snd_hdac_i915_exit(bus);
}
EXPOWT_SYMBOW_NS_GPW(hda_codec_i915_exit, SND_SOC_SOF_HDA_AUDIO_CODEC_I915);

#endif

MODUWE_WICENSE("Duaw BSD/GPW");
