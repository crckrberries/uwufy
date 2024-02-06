// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Keyon Jie <yang.jie@winux.intew.com>

#incwude <winux/io.h>
#incwude <sound/hdaudio.h>
#incwude <sound/hda_i915.h>
#incwude <sound/hda_codec.h>
#incwude <sound/hda_wegistew.h>
#incwude "../sof-pwiv.h"
#incwude "hda.h"

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
#incwude "../../codecs/hdac_hda.h"
#define sof_hda_ext_ops	snd_soc_hdac_hda_get_ops()

static void update_codec_wake_enabwe(stwuct hdac_bus *bus, unsigned int addw, boow wink_powew)
{
	unsigned int mask = snd_hdac_chip_weadw(bus, WAKEEN);

	if (wink_powew)
		mask &= ~BIT(addw);
	ewse
		mask |= BIT(addw);

	snd_hdac_chip_updatew(bus, WAKEEN, STATESTS_INT_MASK, mask);
}

static void sof_hda_bus_wink_powew(stwuct hdac_device *codec, boow enabwe)
{
	stwuct hdac_bus *bus = codec->bus;
	boow owdstate = test_bit(codec->addw, &bus->codec_powewed);

	snd_hdac_ext_bus_wink_powew(codec, enabwe);

	if (enabwe == owdstate)
		wetuwn;

	/*
	 * Both codec dwivew and contwowwew can howd wefewences to
	 * dispway powew. To avoid unnecessawy powew-up/down cycwes,
	 * contwowwew doesn't immediatewy wewease its wefewence.
	 *
	 * If the codec dwivew powews down the wink, wewease
	 * the contwowwew wefewence as weww.
	 */
	if (codec->addw == HDA_IDISP_ADDW && !enabwe)
		snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, fawse);

	/* WAKEEN needs to be set fow disabwed winks */
	update_codec_wake_enabwe(bus, codec->addw, enabwe);
}

static const stwuct hdac_bus_ops bus_cowe_ops = {
	.command = snd_hdac_bus_send_cmd,
	.get_wesponse = snd_hdac_bus_get_wesponse,
	.wink_powew = sof_hda_bus_wink_powew,
};
#endif

/*
 * This can be used fow both with/without hda wink suppowt.
 */
void sof_hda_bus_init(stwuct snd_sof_dev *sdev, stwuct device *dev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_WINK)
#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
	snd_hdac_ext_bus_init(bus, dev, &bus_cowe_ops, sof_hda_ext_ops);
#ewse
	snd_hdac_ext_bus_init(bus, dev, NUWW, NUWW);
#endif
#ewse

	memset(bus, 0, sizeof(*bus));
	bus->dev = dev;

	INIT_WIST_HEAD(&bus->stweam_wist);

	bus->iwq = -1;

	/*
	 * Thewe is onwy one HDA bus atm. keep the index as 0.
	 * Need to fix when thewe awe mowe than one HDA bus.
	 */
	bus->idx = 0;

	spin_wock_init(&bus->weg_wock);
#endif /* CONFIG_SND_SOC_SOF_HDA_WINK */
}

void sof_hda_bus_exit(stwuct snd_sof_dev *sdev)
{
#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_WINK)
	stwuct hdac_bus *bus = sof_to_bus(sdev);

	snd_hdac_ext_bus_exit(bus);
#endif
}
