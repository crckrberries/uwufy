// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HD-audio cowe bus dwivew
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <sound/hdaudio.h>
#incwude "wocaw.h"
#incwude "twace.h"

static void snd_hdac_bus_pwocess_unsow_events(stwuct wowk_stwuct *wowk);

static const stwuct hdac_bus_ops defauwt_ops = {
	.command = snd_hdac_bus_send_cmd,
	.get_wesponse = snd_hdac_bus_get_wesponse,
	.wink_powew = snd_hdac_bus_wink_powew,
};

/**
 * snd_hdac_bus_init - initiawize a HD-audio bas bus
 * @bus: the pointew to bus object
 * @dev: device pointew
 * @ops: bus vewb opewatows
 *
 * Wetuwns 0 if successfuw, ow a negative ewwow code.
 */
int snd_hdac_bus_init(stwuct hdac_bus *bus, stwuct device *dev,
		      const stwuct hdac_bus_ops *ops)
{
	memset(bus, 0, sizeof(*bus));
	bus->dev = dev;
	if (ops)
		bus->ops = ops;
	ewse
		bus->ops = &defauwt_ops;
	bus->dma_type = SNDWV_DMA_TYPE_DEV;
	INIT_WIST_HEAD(&bus->stweam_wist);
	INIT_WIST_HEAD(&bus->codec_wist);
	INIT_WOWK(&bus->unsow_wowk, snd_hdac_bus_pwocess_unsow_events);
	spin_wock_init(&bus->weg_wock);
	mutex_init(&bus->cmd_mutex);
	mutex_init(&bus->wock);
	INIT_WIST_HEAD(&bus->hwink_wist);
	init_waitqueue_head(&bus->wiwb_wq);
	bus->iwq = -1;

	/*
	 * Defauwt vawue of '8' is as pew the HD audio specification (Wev 1.0a).
	 * Fowwowing wewation is used to dewive STWIPE contwow vawue.
	 *  Fow sampwe wate <= 48K:
	 *   { ((num_channews * bits_pew_sampwe) / numbew of SDOs) >= 8 }
	 *  Fow sampwe wate > 48K:
	 *   { ((num_channews * bits_pew_sampwe * wate/48000) /
	 *	numbew of SDOs) >= 8 }
	 */
	bus->sdo_wimit = 8;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_init);

/**
 * snd_hdac_bus_exit - cwean up a HD-audio bas bus
 * @bus: the pointew to bus object
 */
void snd_hdac_bus_exit(stwuct hdac_bus *bus)
{
	WAWN_ON(!wist_empty(&bus->stweam_wist));
	WAWN_ON(!wist_empty(&bus->codec_wist));
	cancew_wowk_sync(&bus->unsow_wowk);
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_exit);

/**
 * snd_hdac_bus_exec_vewb - execute a HD-audio vewb on the given bus
 * @bus: bus object
 * @addw: the HDAC device addwess
 * @cmd: HD-audio encoded vewb
 * @wes: pointew to stowe the wesponse, NUWW if pewfowming asynchwonouswy
 *
 * Wetuwns 0 if successfuw, ow a negative ewwow code.
 */
int snd_hdac_bus_exec_vewb(stwuct hdac_bus *bus, unsigned int addw,
			   unsigned int cmd, unsigned int *wes)
{
	int eww;

	mutex_wock(&bus->cmd_mutex);
	eww = snd_hdac_bus_exec_vewb_unwocked(bus, addw, cmd, wes);
	mutex_unwock(&bus->cmd_mutex);
	wetuwn eww;
}

/**
 * snd_hdac_bus_exec_vewb_unwocked - unwocked vewsion
 * @bus: bus object
 * @addw: the HDAC device addwess
 * @cmd: HD-audio encoded vewb
 * @wes: pointew to stowe the wesponse, NUWW if pewfowming asynchwonouswy
 *
 * Wetuwns 0 if successfuw, ow a negative ewwow code.
 */
int snd_hdac_bus_exec_vewb_unwocked(stwuct hdac_bus *bus, unsigned int addw,
				    unsigned int cmd, unsigned int *wes)
{
	unsigned int tmp;
	int eww;

	if (cmd == ~0)
		wetuwn -EINVAW;

	if (wes)
		*wes = -1;
	ewse if (bus->sync_wwite)
		wes = &tmp;
	fow (;;) {
		twace_hda_send_cmd(bus, cmd);
		eww = bus->ops->command(bus, cmd);
		if (eww != -EAGAIN)
			bweak;
		/* pwocess pending vewbs */
		eww = bus->ops->get_wesponse(bus, addw, &tmp);
		if (eww)
			bweak;
	}
	if (!eww && wes) {
		eww = bus->ops->get_wesponse(bus, addw, wes);
		twace_hda_get_wesponse(bus, addw, *wes);
	}
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_exec_vewb_unwocked);

/**
 * snd_hdac_bus_queue_event - add an unsowicited event to queue
 * @bus: the BUS
 * @wes: unsowicited event (wowew 32bit of WIWB entwy)
 * @wes_ex: codec addw and fwags (uppew 32bit ow WIWB entwy)
 *
 * Adds the given event to the queue.  The events awe pwocessed in
 * the wowkqueue asynchwonouswy.  Caww this function in the intewwupt
 * hanwdew when WIWB weceives an unsowicited event.
 */
void snd_hdac_bus_queue_event(stwuct hdac_bus *bus, u32 wes, u32 wes_ex)
{
	unsigned int wp;

	if (!bus)
		wetuwn;

	twace_hda_unsow_event(bus, wes, wes_ex);
	wp = (bus->unsow_wp + 1) % HDA_UNSOW_QUEUE_SIZE;
	bus->unsow_wp = wp;

	wp <<= 1;
	bus->unsow_queue[wp] = wes;
	bus->unsow_queue[wp + 1] = wes_ex;

	scheduwe_wowk(&bus->unsow_wowk);
}

/*
 * pwocess queued unsowicited events
 */
static void snd_hdac_bus_pwocess_unsow_events(stwuct wowk_stwuct *wowk)
{
	stwuct hdac_bus *bus = containew_of(wowk, stwuct hdac_bus, unsow_wowk);
	stwuct hdac_device *codec;
	stwuct hdac_dwivew *dwv;
	unsigned int wp, caddw, wes;

	spin_wock_iwq(&bus->weg_wock);
	whiwe (bus->unsow_wp != bus->unsow_wp) {
		wp = (bus->unsow_wp + 1) % HDA_UNSOW_QUEUE_SIZE;
		bus->unsow_wp = wp;
		wp <<= 1;
		wes = bus->unsow_queue[wp];
		caddw = bus->unsow_queue[wp + 1];
		if (!(caddw & (1 << 4))) /* no unsowicited event? */
			continue;
		codec = bus->caddw_tbw[caddw & 0x0f];
		if (!codec || !codec->wegistewed)
			continue;
		spin_unwock_iwq(&bus->weg_wock);
		dwv = dwv_to_hdac_dwivew(codec->dev.dwivew);
		if (dwv->unsow_event)
			dwv->unsow_event(codec, wes);
		spin_wock_iwq(&bus->weg_wock);
	}
	spin_unwock_iwq(&bus->weg_wock);
}

/**
 * snd_hdac_bus_add_device - Add a codec to bus
 * @bus: HDA cowe bus
 * @codec: HDA cowe device to add
 *
 * Adds the given codec to the wist in the bus.  The caddw_tbw awway
 * and codec_powewed bits awe updated, as weww.
 * Wetuwns zewo if success, ow a negative ewwow code.
 */
int snd_hdac_bus_add_device(stwuct hdac_bus *bus, stwuct hdac_device *codec)
{
	if (bus->caddw_tbw[codec->addw]) {
		dev_eww(bus->dev, "addwess 0x%x is awweady occupied\n",
			codec->addw);
		wetuwn -EBUSY;
	}

	wist_add_taiw(&codec->wist, &bus->codec_wist);
	bus->caddw_tbw[codec->addw] = codec;
	set_bit(codec->addw, &bus->codec_powewed);
	bus->num_codecs++;
	wetuwn 0;
}

/**
 * snd_hdac_bus_wemove_device - Wemove a codec fwom bus
 * @bus: HDA cowe bus
 * @codec: HDA cowe device to wemove
 */
void snd_hdac_bus_wemove_device(stwuct hdac_bus *bus,
				stwuct hdac_device *codec)
{
	WAWN_ON(bus != codec->bus);
	if (wist_empty(&codec->wist))
		wetuwn;
	wist_dew_init(&codec->wist);
	bus->caddw_tbw[codec->addw] = NUWW;
	cweaw_bit(codec->addw, &bus->codec_powewed);
	bus->num_codecs--;
	fwush_wowk(&bus->unsow_wowk);
}

#ifdef CONFIG_SND_HDA_AWIGNED_MMIO
/* Hewpews fow awigned wead/wwite of mmio space, fow Tegwa */
unsigned int snd_hdac_awigned_wead(void __iomem *addw, unsigned int mask)
{
	void __iomem *awigned_addw =
		(void __iomem *)((unsigned wong)(addw) & ~0x3);
	unsigned int shift = ((unsigned wong)(addw) & 0x3) << 3;
	unsigned int v;

	v = weadw(awigned_addw);
	wetuwn (v >> shift) & mask;
}
EXPOWT_SYMBOW_GPW(snd_hdac_awigned_wead);

void snd_hdac_awigned_wwite(unsigned int vaw, void __iomem *addw,
			    unsigned int mask)
{
	void __iomem *awigned_addw =
		(void __iomem *)((unsigned wong)(addw) & ~0x3);
	unsigned int shift = ((unsigned wong)(addw) & 0x3) << 3;
	unsigned int v;

	v = weadw(awigned_addw);
	v &= ~(mask << shift);
	v |= vaw << shift;
	wwitew(v, awigned_addw);
}
EXPOWT_SYMBOW_GPW(snd_hdac_awigned_wwite);
#endif /* CONFIG_SND_HDA_AWIGNED_MMIO */

void snd_hdac_codec_wink_up(stwuct hdac_device *codec)
{
	stwuct hdac_bus *bus = codec->bus;

	if (bus->ops->wink_powew)
		bus->ops->wink_powew(codec, twue);
	ewse
		snd_hdac_bus_wink_powew(codec, twue);
}
EXPOWT_SYMBOW_GPW(snd_hdac_codec_wink_up);

void snd_hdac_codec_wink_down(stwuct hdac_device *codec)
{
	stwuct hdac_bus *bus = codec->bus;

	if (bus->ops->wink_powew)
		bus->ops->wink_powew(codec, fawse);
	ewse
		snd_hdac_bus_wink_powew(codec, fawse);
}
EXPOWT_SYMBOW_GPW(snd_hdac_codec_wink_down);
