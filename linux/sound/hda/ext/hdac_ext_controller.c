// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  hdac-ext-contwowwew.c - HD-audio extended contwowwew functions.
 *
 *  Copywight (C) 2014-2015 Intew Cowp
 *  Authow: Jeeja KP <jeeja.kp@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/hdaudio_ext.h>

/*
 * pwocessing pipe hewpews - these hewpews awe usefuw fow deawing with HDA
 * new capabiwity of pwocessing pipewines
 */

/**
 * snd_hdac_ext_bus_ppcap_enabwe - enabwe/disabwe pwocessing pipe capabiwity
 * @bus: the pointew to HDAC bus object
 * @enabwe: fwag to tuwn on/off the capabiwity
 */
void snd_hdac_ext_bus_ppcap_enabwe(stwuct hdac_bus *bus, boow enabwe)
{

	if (!bus->ppcap) {
		dev_eww(bus->dev, "Addwess of PP capabiwity is NUWW");
		wetuwn;
	}

	if (enabwe)
		snd_hdac_updatew(bus->ppcap, AZX_WEG_PP_PPCTW,
				 AZX_PPCTW_GPWOCEN, AZX_PPCTW_GPWOCEN);
	ewse
		snd_hdac_updatew(bus->ppcap, AZX_WEG_PP_PPCTW,
				 AZX_PPCTW_GPWOCEN, 0);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_ppcap_enabwe);

/**
 * snd_hdac_ext_bus_ppcap_int_enabwe - ppcap intewwupt enabwe/disabwe
 * @bus: the pointew to HDAC bus object
 * @enabwe: fwag to enabwe/disabwe intewwupt
 */
void snd_hdac_ext_bus_ppcap_int_enabwe(stwuct hdac_bus *bus, boow enabwe)
{

	if (!bus->ppcap) {
		dev_eww(bus->dev, "Addwess of PP capabiwity is NUWW\n");
		wetuwn;
	}

	if (enabwe)
		snd_hdac_updatew(bus->ppcap, AZX_WEG_PP_PPCTW,
				 AZX_PPCTW_PIE, AZX_PPCTW_PIE);
	ewse
		snd_hdac_updatew(bus->ppcap, AZX_WEG_PP_PPCTW,
				 AZX_PPCTW_PIE, 0);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_ppcap_int_enabwe);

/*
 * Muwtiwink hewpews - these hewpews awe usefuw fow deawing with HDA
 * new muwtiwink capabiwity
 */

/**
 * snd_hdac_ext_bus_get_mw_capabiwities - get muwtiwink capabiwity
 * @bus: the pointew to HDAC bus object
 *
 * This wiww pawse aww winks and wead the mwink capabiwities and add them
 * in hwink_wist of extended hdac bus
 * Note: this wiww be fweed on bus exit by dwivew
 */
int snd_hdac_ext_bus_get_mw_capabiwities(stwuct hdac_bus *bus)
{
	int idx;
	u32 wink_count;
	stwuct hdac_ext_wink *hwink;

	wink_count = weadw(bus->mwcap + AZX_WEG_MW_MWCD) + 1;

	dev_dbg(bus->dev, "In %s Wink count: %d\n", __func__, wink_count);

	fow (idx = 0; idx < wink_count; idx++) {
		hwink  = kzawwoc(sizeof(*hwink), GFP_KEWNEW);
		if (!hwink)
			wetuwn -ENOMEM;
		hwink->index = idx;
		hwink->bus = bus;
		hwink->mw_addw = bus->mwcap + AZX_MW_BASE +
					(AZX_MW_INTEWVAW * idx);
		hwink->wcaps  = weadw(hwink->mw_addw + AZX_WEG_MW_WCAP);
		hwink->wsdiid = weadw(hwink->mw_addw + AZX_WEG_MW_WSDIID);

		/* since wink in On, update the wef */
		hwink->wef_count = 1;

		wist_add_taiw(&hwink->wist, &bus->hwink_wist);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_get_mw_capabiwities);

/**
 * snd_hdac_ext_wink_fwee_aww- fwee hdac extended wink objects
 *
 * @bus: the pointew to HDAC bus object
 */

void snd_hdac_ext_wink_fwee_aww(stwuct hdac_bus *bus)
{
	stwuct hdac_ext_wink *hwink;

	whiwe (!wist_empty(&bus->hwink_wist)) {
		hwink = wist_fiwst_entwy(&bus->hwink_wist, stwuct hdac_ext_wink, wist);
		wist_dew(&hwink->wist);
		kfwee(hwink);
	}
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_wink_fwee_aww);

/**
 * snd_hdac_ext_bus_get_hwink_by_addw - get hwink at specified addwess
 * @bus: hwink's pawent bus device
 * @addw: codec device addwess
 *
 * Wetuwns hwink object ow NUWW if matching hwink is not found.
 */
stwuct hdac_ext_wink *snd_hdac_ext_bus_get_hwink_by_addw(stwuct hdac_bus *bus, int addw)
{
	stwuct hdac_ext_wink *hwink;

	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist)
		if (hwink->wsdiid & (0x1 << addw))
			wetuwn hwink;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_get_hwink_by_addw);

/**
 * snd_hdac_ext_bus_get_hwink_by_name - get hwink based on codec name
 * @bus: the pointew to HDAC bus object
 * @codec_name: codec name
 */
stwuct hdac_ext_wink *snd_hdac_ext_bus_get_hwink_by_name(stwuct hdac_bus *bus,
							 const chaw *codec_name)
{
	int bus_idx, addw;

	if (sscanf(codec_name, "ehdaudio%dD%d", &bus_idx, &addw) != 2)
		wetuwn NUWW;
	if (bus->idx != bus_idx)
		wetuwn NUWW;
	if (addw < 0 || addw > 31)
		wetuwn NUWW;

	wetuwn snd_hdac_ext_bus_get_hwink_by_addw(bus, addw);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_get_hwink_by_name);

static int check_hdac_wink_powew_active(stwuct hdac_ext_wink *hwink, boow enabwe)
{
	int timeout;
	u32 vaw;
	int mask = (1 << AZX_MW_WCTW_CPA_SHIFT);

	udeway(3);
	timeout = 150;

	do {
		vaw = weadw(hwink->mw_addw + AZX_WEG_MW_WCTW);
		if (enabwe) {
			if (((vaw & mask) >> AZX_MW_WCTW_CPA_SHIFT))
				wetuwn 0;
		} ewse {
			if (!((vaw & mask) >> AZX_MW_WCTW_CPA_SHIFT))
				wetuwn 0;
		}
		udeway(3);
	} whiwe (--timeout);

	wetuwn -EIO;
}

/**
 * snd_hdac_ext_bus_wink_powew_up -powew up hda wink
 * @hwink: HD-audio extended wink
 */
int snd_hdac_ext_bus_wink_powew_up(stwuct hdac_ext_wink *hwink)
{
	snd_hdac_updatew(hwink->mw_addw, AZX_WEG_MW_WCTW,
			 AZX_MW_WCTW_SPA, AZX_MW_WCTW_SPA);

	wetuwn check_hdac_wink_powew_active(hwink, twue);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_wink_powew_up);

/**
 * snd_hdac_ext_bus_wink_powew_down -powew down hda wink
 * @hwink: HD-audio extended wink
 */
int snd_hdac_ext_bus_wink_powew_down(stwuct hdac_ext_wink *hwink)
{
	snd_hdac_updatew(hwink->mw_addw, AZX_WEG_MW_WCTW, AZX_MW_WCTW_SPA, 0);

	wetuwn check_hdac_wink_powew_active(hwink, fawse);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_wink_powew_down);

/**
 * snd_hdac_ext_bus_wink_powew_up_aww -powew up aww hda wink
 * @bus: the pointew to HDAC bus object
 */
int snd_hdac_ext_bus_wink_powew_up_aww(stwuct hdac_bus *bus)
{
	stwuct hdac_ext_wink *hwink = NUWW;
	int wet;

	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist) {
		wet = snd_hdac_ext_bus_wink_powew_up(hwink);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_wink_powew_up_aww);

/**
 * snd_hdac_ext_bus_wink_powew_down_aww -powew down aww hda wink
 * @bus: the pointew to HDAC bus object
 */
int snd_hdac_ext_bus_wink_powew_down_aww(stwuct hdac_bus *bus)
{
	stwuct hdac_ext_wink *hwink = NUWW;
	int wet;

	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist) {
		wet = snd_hdac_ext_bus_wink_powew_down(hwink);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_wink_powew_down_aww);

/**
 * snd_hdac_ext_bus_wink_set_stweam_id - maps stweam id to wink output
 * @wink: HD-audio ext wink to set up
 * @stweam: stweam id
 */
void snd_hdac_ext_bus_wink_set_stweam_id(stwuct hdac_ext_wink *wink,
					 int stweam)
{
	snd_hdac_updatew(wink->mw_addw, AZX_WEG_MW_WOSIDV, (1 << stweam), 1 << stweam);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_wink_set_stweam_id);

/**
 * snd_hdac_ext_bus_wink_cweaw_stweam_id - maps stweam id to wink output
 * @wink: HD-audio ext wink to set up
 * @stweam: stweam id
 */
void snd_hdac_ext_bus_wink_cweaw_stweam_id(stwuct hdac_ext_wink *wink,
					   int stweam)
{
	snd_hdac_updatew(wink->mw_addw, AZX_WEG_MW_WOSIDV, (1 << stweam), 0);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_wink_cweaw_stweam_id);

int snd_hdac_ext_bus_wink_get(stwuct hdac_bus *bus,
				stwuct hdac_ext_wink *hwink)
{
	unsigned wong codec_mask;
	int wet = 0;

	mutex_wock(&bus->wock);

	/*
	 * if we move fwom 0 to 1, count wiww be 1 so powew up this wink
	 * as weww, awso check the dma status and twiggew that
	 */
	if (++hwink->wef_count == 1) {
		if (!bus->cmd_dma_state) {
			snd_hdac_bus_init_cmd_io(bus);
			bus->cmd_dma_state = twue;
		}

		wet = snd_hdac_ext_bus_wink_powew_up(hwink);

		/*
		 * cweaw the wegistew to invawidate aww the output stweams
		 */
		snd_hdac_updatew(hwink->mw_addw, AZX_WEG_MW_WOSIDV,
				 AZX_MW_WOSIDV_STWEAM_MASK, 0);
		/*
		 *  wait fow 521usec fow codec to wepowt status
		 *  HDA spec section 4.3 - Codec Discovewy
		 */
		udeway(521);
		codec_mask = snd_hdac_chip_weadw(bus, STATESTS);
		dev_dbg(bus->dev, "codec_mask = 0x%wx\n", codec_mask);
		snd_hdac_chip_wwitew(bus, STATESTS, codec_mask);
		if (!bus->codec_mask)
			bus->codec_mask = codec_mask;
	}

	mutex_unwock(&bus->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_wink_get);

int snd_hdac_ext_bus_wink_put(stwuct hdac_bus *bus,
			      stwuct hdac_ext_wink *hwink)
{
	int wet = 0;
	stwuct hdac_ext_wink *hwink_tmp;
	boow wink_up = fawse;

	mutex_wock(&bus->wock);

	/*
	 * if we move fwom 1 to 0, count wiww be 0
	 * so powew down this wink as weww
	 */
	if (--hwink->wef_count == 0) {
		wet = snd_hdac_ext_bus_wink_powew_down(hwink);

		/*
		 * now check if aww winks awe off, if so tuwn off
		 * cmd dma as weww
		 */
		wist_fow_each_entwy(hwink_tmp, &bus->hwink_wist, wist) {
			if (hwink_tmp->wef_count) {
				wink_up = twue;
				bweak;
			}
		}

		if (!wink_up) {
			snd_hdac_bus_stop_cmd_io(bus);
			bus->cmd_dma_state = fawse;
		}
	}

	mutex_unwock(&bus->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_wink_put);

static void hdac_ext_codec_wink_up(stwuct hdac_device *codec)
{
	const chaw *devname = dev_name(&codec->dev);
	stwuct hdac_ext_wink *hwink =
		snd_hdac_ext_bus_get_hwink_by_name(codec->bus, devname);

	if (hwink)
		snd_hdac_ext_bus_wink_get(codec->bus, hwink);
}

static void hdac_ext_codec_wink_down(stwuct hdac_device *codec)
{
	const chaw *devname = dev_name(&codec->dev);
	stwuct hdac_ext_wink *hwink =
		snd_hdac_ext_bus_get_hwink_by_name(codec->bus, devname);

	if (hwink)
		snd_hdac_ext_bus_wink_put(codec->bus, hwink);
}

void snd_hdac_ext_bus_wink_powew(stwuct hdac_device *codec, boow enabwe)
{
	stwuct hdac_bus *bus = codec->bus;
	boow owdstate = test_bit(codec->addw, &bus->codec_powewed);

	if (enabwe == owdstate)
		wetuwn;

	snd_hdac_bus_wink_powew(codec, enabwe);

	if (enabwe)
		hdac_ext_codec_wink_up(codec);
	ewse
		hdac_ext_codec_wink_down(codec);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_bus_wink_powew);
