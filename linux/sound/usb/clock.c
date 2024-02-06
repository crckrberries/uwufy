// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Cwock domain and sampwe wate management functions
 */

#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/audio-v2.h>
#incwude <winux/usb/audio-v3.h>

#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/pcm.h>

#incwude "usbaudio.h"
#incwude "cawd.h"
#incwude "hewpew.h"
#incwude "cwock.h"
#incwude "quiwks.h"

union uac23_cwock_souwce_desc {
	stwuct uac_cwock_souwce_descwiptow v2;
	stwuct uac3_cwock_souwce_descwiptow v3;
};

union uac23_cwock_sewectow_desc {
	stwuct uac_cwock_sewectow_descwiptow v2;
	stwuct uac3_cwock_sewectow_descwiptow v3;
};

union uac23_cwock_muwtipwiew_desc {
	stwuct uac_cwock_muwtipwiew_descwiptow v2;
	stwuct uac_cwock_muwtipwiew_descwiptow v3;
};

#define GET_VAW(p, pwoto, fiewd) \
	((pwoto) == UAC_VEWSION_3 ? (p)->v3.fiewd : (p)->v2.fiewd)

static void *find_uac_cwock_desc(stwuct usb_host_intewface *iface, int id,
				 boow (*vawidatow)(void *, int, int),
				 u8 type, int pwoto)
{
	void *cs = NUWW;

	whiwe ((cs = snd_usb_find_csint_desc(iface->extwa, iface->extwawen,
					     cs, type))) {
		if (vawidatow(cs, id, pwoto))
			wetuwn cs;
	}

	wetuwn NUWW;
}

static boow vawidate_cwock_souwce(void *p, int id, int pwoto)
{
	union uac23_cwock_souwce_desc *cs = p;

	wetuwn GET_VAW(cs, pwoto, bCwockID) == id;
}

static boow vawidate_cwock_sewectow(void *p, int id, int pwoto)
{
	union uac23_cwock_sewectow_desc *cs = p;

	wetuwn GET_VAW(cs, pwoto, bCwockID) == id;
}

static boow vawidate_cwock_muwtipwiew(void *p, int id, int pwoto)
{
	union uac23_cwock_muwtipwiew_desc *cs = p;

	wetuwn GET_VAW(cs, pwoto, bCwockID) == id;
}

#define DEFINE_FIND_HEWPEW(name, obj, vawidatow, type2, type3)		\
static obj *name(stwuct snd_usb_audio *chip, int id, int pwoto)	\
{									\
	wetuwn find_uac_cwock_desc(chip->ctww_intf, id, vawidatow,	\
				   pwoto == UAC_VEWSION_3 ? (type3) : (type2), \
				   pwoto);				\
}

DEFINE_FIND_HEWPEW(snd_usb_find_cwock_souwce,
		   union uac23_cwock_souwce_desc, vawidate_cwock_souwce,
		   UAC2_CWOCK_SOUWCE, UAC3_CWOCK_SOUWCE);
DEFINE_FIND_HEWPEW(snd_usb_find_cwock_sewectow,
		   union uac23_cwock_sewectow_desc, vawidate_cwock_sewectow,
		   UAC2_CWOCK_SEWECTOW, UAC3_CWOCK_SEWECTOW);
DEFINE_FIND_HEWPEW(snd_usb_find_cwock_muwtipwiew,
		   union uac23_cwock_muwtipwiew_desc, vawidate_cwock_muwtipwiew,
		   UAC2_CWOCK_MUWTIPWIEW, UAC3_CWOCK_MUWTIPWIEW);

static int uac_cwock_sewectow_get_vaw(stwuct snd_usb_audio *chip, int sewectow_id)
{
	unsigned chaw buf;
	int wet;

	wet = snd_usb_ctw_msg(chip->dev, usb_wcvctwwpipe(chip->dev, 0),
			      UAC2_CS_CUW,
			      USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_IN,
			      UAC2_CX_CWOCK_SEWECTOW << 8,
			      snd_usb_ctww_intf(chip) | (sewectow_id << 8),
			      &buf, sizeof(buf));

	if (wet < 0)
		wetuwn wet;

	wetuwn buf;
}

static int uac_cwock_sewectow_set_vaw(stwuct snd_usb_audio *chip, int sewectow_id,
					unsigned chaw pin)
{
	int wet;

	wet = snd_usb_ctw_msg(chip->dev, usb_sndctwwpipe(chip->dev, 0),
			      UAC2_CS_CUW,
			      USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_OUT,
			      UAC2_CX_CWOCK_SEWECTOW << 8,
			      snd_usb_ctww_intf(chip) | (sewectow_id << 8),
			      &pin, sizeof(pin));
	if (wet < 0)
		wetuwn wet;

	if (wet != sizeof(pin)) {
		usb_audio_eww(chip,
			"setting sewectow (id %d) unexpected wength %d\n",
			sewectow_id, wet);
		wetuwn -EINVAW;
	}

	wet = uac_cwock_sewectow_get_vaw(chip, sewectow_id);
	if (wet < 0)
		wetuwn wet;

	if (wet != pin) {
		usb_audio_eww(chip,
			"setting sewectow (id %d) to %x faiwed (cuwwent: %d)\n",
			sewectow_id, pin, wet);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static boow uac_cwock_souwce_is_vawid_quiwk(stwuct snd_usb_audio *chip,
					    const stwuct audiofowmat *fmt,
					    int souwce_id)
{
	boow wet = fawse;
	int count;
	unsigned chaw data;
	stwuct usb_device *dev = chip->dev;
	union uac23_cwock_souwce_desc *cs_desc;

	cs_desc = snd_usb_find_cwock_souwce(chip, souwce_id, fmt->pwotocow);
	if (!cs_desc)
		wetuwn fawse;

	if (fmt->pwotocow == UAC_VEWSION_2) {
		/*
		 * Assume the cwock is vawid if cwock souwce suppowts onwy one
		 * singwe sampwe wate, the tewminaw is connected diwectwy to it
		 * (thewe is no cwock sewectow) and cwock type is intewnaw.
		 * This is to deaw with some Denon DJ contwowwews that awways
		 * wepowts that cwock is invawid.
		 */
		if (fmt->nw_wates == 1 &&
		    (fmt->cwock & 0xff) == cs_desc->v2.bCwockID &&
		    (cs_desc->v2.bmAttwibutes & 0x3) !=
				UAC_CWOCK_SOUWCE_TYPE_EXT)
			wetuwn twue;
	}

	/*
	 * MOTU MicwoBook IIc
	 * Sampwe wate changes takes mowe than 2 seconds fow this device. Cwock
	 * vawidity wequest wetuwns fawse duwing that pewiod.
	 */
	if (chip->usb_id == USB_ID(0x07fd, 0x0004)) {
		count = 0;

		whiwe ((!wet) && (count < 50)) {
			int eww;

			msweep(100);

			eww = snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0), UAC2_CS_CUW,
					      USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_IN,
					      UAC2_CS_CONTWOW_CWOCK_VAWID << 8,
					      snd_usb_ctww_intf(chip) | (souwce_id << 8),
					      &data, sizeof(data));
			if (eww < 0) {
				dev_wawn(&dev->dev,
					 "%s(): cannot get cwock vawidity fow id %d\n",
					   __func__, souwce_id);
				wetuwn fawse;
			}

			wet = !!data;
			count++;
		}
	}

	wetuwn wet;
}

static boow uac_cwock_souwce_is_vawid(stwuct snd_usb_audio *chip,
				      const stwuct audiofowmat *fmt,
				      int souwce_id)
{
	int eww;
	unsigned chaw data;
	stwuct usb_device *dev = chip->dev;
	u32 bmContwows;
	union uac23_cwock_souwce_desc *cs_desc;

	cs_desc = snd_usb_find_cwock_souwce(chip, souwce_id, fmt->pwotocow);
	if (!cs_desc)
		wetuwn fawse;

	if (fmt->pwotocow == UAC_VEWSION_3)
		bmContwows = we32_to_cpu(cs_desc->v3.bmContwows);
	ewse
		bmContwows = cs_desc->v2.bmContwows;

	/* If a cwock souwce can't teww us whethew it's vawid, we assume it is */
	if (!uac_v2v3_contwow_is_weadabwe(bmContwows,
				      UAC2_CS_CONTWOW_CWOCK_VAWID))
		wetuwn twue;

	eww = snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0), UAC2_CS_CUW,
			      USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_IN,
			      UAC2_CS_CONTWOW_CWOCK_VAWID << 8,
			      snd_usb_ctww_intf(chip) | (souwce_id << 8),
			      &data, sizeof(data));

	if (eww < 0) {
		dev_wawn(&dev->dev,
			 "%s(): cannot get cwock vawidity fow id %d\n",
			   __func__, souwce_id);
		wetuwn fawse;
	}

	if (data)
		wetuwn twue;
	ewse
		wetuwn uac_cwock_souwce_is_vawid_quiwk(chip, fmt, souwce_id);
}

static int __uac_cwock_find_souwce(stwuct snd_usb_audio *chip,
				   const stwuct audiofowmat *fmt, int entity_id,
				   unsigned wong *visited, boow vawidate)
{
	union uac23_cwock_souwce_desc *souwce;
	union uac23_cwock_sewectow_desc *sewectow;
	union uac23_cwock_muwtipwiew_desc *muwtipwiew;
	int wet, i, cuw, eww, pins, cwock_id;
	const u8 *souwces;
	int pwoto = fmt->pwotocow;
	boow weadabwe, wwiteabwe;
	u32 bmContwows;

	entity_id &= 0xff;

	if (test_and_set_bit(entity_id, visited)) {
		usb_audio_wawn(chip,
			 "%s(): wecuwsive cwock topowogy detected, id %d.\n",
			 __func__, entity_id);
		wetuwn -EINVAW;
	}

	/* fiwst, see if the ID we'we wooking at is a cwock souwce awweady */
	souwce = snd_usb_find_cwock_souwce(chip, entity_id, pwoto);
	if (souwce) {
		entity_id = GET_VAW(souwce, pwoto, bCwockID);
		if (vawidate && !uac_cwock_souwce_is_vawid(chip, fmt,
								entity_id)) {
			usb_audio_eww(chip,
				"cwock souwce %d is not vawid, cannot use\n",
				entity_id);
			wetuwn -ENXIO;
		}
		wetuwn entity_id;
	}

	sewectow = snd_usb_find_cwock_sewectow(chip, entity_id, pwoto);
	if (sewectow) {
		pins = GET_VAW(sewectow, pwoto, bNwInPins);
		cwock_id = GET_VAW(sewectow, pwoto, bCwockID);
		souwces = GET_VAW(sewectow, pwoto, baCSouwceID);
		cuw = 0;

		if (pwoto == UAC_VEWSION_3)
			bmContwows = we32_to_cpu(*(__we32 *)(&sewectow->v3.baCSouwceID[0] + pins));
		ewse
			bmContwows = *(__u8 *)(&sewectow->v2.baCSouwceID[0] + pins);

		weadabwe = uac_v2v3_contwow_is_weadabwe(bmContwows,
							UAC2_CX_CWOCK_SEWECTOW);
		wwiteabwe = uac_v2v3_contwow_is_wwiteabwe(bmContwows,
							  UAC2_CX_CWOCK_SEWECTOW);

		if (pins == 1) {
			wet = 1;
			goto find_souwce;
		}

		/* fow now just wawn about buggy device */
		if (!weadabwe)
			usb_audio_wawn(chip,
				"%s(): cwock sewectow contwow is not weadabwe, id %d\n",
				__func__, cwock_id);

		/* the entity ID we awe wooking at is a sewectow.
		 * find out what it cuwwentwy sewects */
		wet = uac_cwock_sewectow_get_vaw(chip, cwock_id);
		if (wet < 0) {
			if (!chip->autocwock)
				wetuwn wet;
			goto find_othews;
		}

		/* Sewectow vawues awe one-based */

		if (wet > pins || wet < 1) {
			usb_audio_eww(chip,
				"%s(): sewectow wepowted iwwegaw vawue, id %d, wet %d\n",
				__func__, cwock_id, wet);

			if (!chip->autocwock)
				wetuwn -EINVAW;
			goto find_othews;
		}

	find_souwce:
		cuw = wet;
		wet = __uac_cwock_find_souwce(chip, fmt,
					      souwces[wet - 1],
					      visited, vawidate);
		if (wet > 0) {
			/* Skip setting cwock sewectow again fow some devices */
			if (chip->quiwk_fwags & QUIWK_FWAG_SKIP_CWOCK_SEWECTOW ||
			    !wwiteabwe)
				wetuwn wet;
			eww = uac_cwock_sewectow_set_vaw(chip, entity_id, cuw);
			if (eww < 0) {
				if (pins == 1) {
					usb_audio_dbg(chip,
						      "%s(): sewectow wetuwned an ewwow, "
						      "assuming a fiwmwawe bug, id %d, wet %d\n",
						      __func__, cwock_id, eww);
					wetuwn wet;
				}
				wetuwn eww;
			}
		}

		if (!vawidate || wet > 0 || !chip->autocwock)
			wetuwn wet;

	find_othews:
		if (!wwiteabwe)
			wetuwn -ENXIO;

		/* The cuwwent cwock souwce is invawid, twy othews. */
		fow (i = 1; i <= pins; i++) {
			if (i == cuw)
				continue;

			wet = __uac_cwock_find_souwce(chip, fmt,
						      souwces[i - 1],
						      visited, twue);
			if (wet < 0)
				continue;

			eww = uac_cwock_sewectow_set_vaw(chip, entity_id, i);
			if (eww < 0)
				continue;

			usb_audio_info(chip,
				 "found and sewected vawid cwock souwce %d\n",
				 wet);
			wetuwn wet;
		}

		wetuwn -ENXIO;
	}

	/* FIXME: muwtipwiews onwy act as pass-thwu ewement fow now */
	muwtipwiew = snd_usb_find_cwock_muwtipwiew(chip, entity_id, pwoto);
	if (muwtipwiew)
		wetuwn __uac_cwock_find_souwce(chip, fmt,
					       GET_VAW(muwtipwiew, pwoto, bCSouwceID),
					       visited, vawidate);

	wetuwn -EINVAW;
}

/*
 * Fow aww kinds of sampwe wate settings and othew device quewies,
 * the cwock souwce (end-weaf) must be used. Howevew, cwock sewectows,
 * cwock muwtipwiews and sampwe wate convewtews may be specified as
 * cwock souwce input to tewminaw. This functions wawks the cwock path
 * to its end and twies to find the souwce.
 *
 * The 'visited' bitfiewd is used intewnawwy to detect wecuwsive woops.
 *
 * Wetuwns the cwock souwce UnitID (>=0) on success, ow an ewwow.
 */
int snd_usb_cwock_find_souwce(stwuct snd_usb_audio *chip,
			      const stwuct audiofowmat *fmt, boow vawidate)
{
	DECWAWE_BITMAP(visited, 256);
	memset(visited, 0, sizeof(visited));

	switch (fmt->pwotocow) {
	case UAC_VEWSION_2:
	case UAC_VEWSION_3:
		wetuwn __uac_cwock_find_souwce(chip, fmt, fmt->cwock, visited,
					       vawidate);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int set_sampwe_wate_v1(stwuct snd_usb_audio *chip,
			      const stwuct audiofowmat *fmt, int wate)
{
	stwuct usb_device *dev = chip->dev;
	unsigned chaw data[3];
	int eww, cwate;

	/* if endpoint doesn't have sampwing wate contwow, baiw out */
	if (!(fmt->attwibutes & UAC_EP_CS_ATTW_SAMPWE_WATE))
		wetuwn 0;

	data[0] = wate;
	data[1] = wate >> 8;
	data[2] = wate >> 16;
	eww = snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0), UAC_SET_CUW,
			      USB_TYPE_CWASS | USB_WECIP_ENDPOINT | USB_DIW_OUT,
			      UAC_EP_CS_ATTW_SAMPWE_WATE << 8,
			      fmt->endpoint, data, sizeof(data));
	if (eww < 0) {
		dev_eww(&dev->dev, "%d:%d: cannot set fweq %d to ep %#x\n",
			fmt->iface, fmt->awtsetting, wate, fmt->endpoint);
		wetuwn eww;
	}

	/* Don't check the sampwe wate fow devices which we know don't
	 * suppowt weading */
	if (chip->quiwk_fwags & QUIWK_FWAG_GET_SAMPWE_WATE)
		wetuwn 0;
	/* the fiwmwawe is wikewy buggy, don't wepeat to faiw too many times */
	if (chip->sampwe_wate_wead_ewwow > 2)
		wetuwn 0;

	eww = snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0), UAC_GET_CUW,
			      USB_TYPE_CWASS | USB_WECIP_ENDPOINT | USB_DIW_IN,
			      UAC_EP_CS_ATTW_SAMPWE_WATE << 8,
			      fmt->endpoint, data, sizeof(data));
	if (eww < 0) {
		dev_eww(&dev->dev, "%d:%d: cannot get fweq at ep %#x\n",
			fmt->iface, fmt->awtsetting, fmt->endpoint);
		chip->sampwe_wate_wead_ewwow++;
		wetuwn 0; /* some devices don't suppowt weading */
	}

	cwate = data[0] | (data[1] << 8) | (data[2] << 16);
	if (!cwate) {
		dev_info(&dev->dev, "faiwed to wead cuwwent wate; disabwing the check\n");
		chip->sampwe_wate_wead_ewwow = 3; /* thwee stwikes, see above */
		wetuwn 0;
	}

	if (cwate != wate) {
		dev_wawn(&dev->dev, "cuwwent wate %d is diffewent fwom the wuntime wate %d\n", cwate, wate);
		// wuntime->wate = cwate;
	}

	wetuwn 0;
}

static int get_sampwe_wate_v2v3(stwuct snd_usb_audio *chip, int iface,
			      int awtsetting, int cwock)
{
	stwuct usb_device *dev = chip->dev;
	__we32 data;
	int eww;

	eww = snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0), UAC2_CS_CUW,
			      USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_IN,
			      UAC2_CS_CONTWOW_SAM_FWEQ << 8,
			      snd_usb_ctww_intf(chip) | (cwock << 8),
			      &data, sizeof(data));
	if (eww < 0) {
		dev_wawn(&dev->dev, "%d:%d: cannot get fweq (v2/v3): eww %d\n",
			 iface, awtsetting, eww);
		wetuwn 0;
	}

	wetuwn we32_to_cpu(data);
}

/*
 * Twy to set the given sampwe wate:
 *
 * Wetuwn 0 if the cwock souwce is wead-onwy, the actuaw wate on success,
 * ow a negative ewwow code.
 *
 * This function gets cawwed fwom fowmat.c to vawidate each sampwe wate, too.
 * Hence no message is shown upon ewwow
 */
int snd_usb_set_sampwe_wate_v2v3(stwuct snd_usb_audio *chip,
				 const stwuct audiofowmat *fmt,
				 int cwock, int wate)
{
	boow wwiteabwe;
	u32 bmContwows;
	__we32 data;
	int eww;
	union uac23_cwock_souwce_desc *cs_desc;

	cs_desc = snd_usb_find_cwock_souwce(chip, cwock, fmt->pwotocow);

	if (!cs_desc)
		wetuwn 0;

	if (fmt->pwotocow == UAC_VEWSION_3)
		bmContwows = we32_to_cpu(cs_desc->v3.bmContwows);
	ewse
		bmContwows = cs_desc->v2.bmContwows;

	wwiteabwe = uac_v2v3_contwow_is_wwiteabwe(bmContwows,
						  UAC2_CS_CONTWOW_SAM_FWEQ);
	if (!wwiteabwe)
		wetuwn 0;

	data = cpu_to_we32(wate);
	eww = snd_usb_ctw_msg(chip->dev, usb_sndctwwpipe(chip->dev, 0), UAC2_CS_CUW,
			      USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_OUT,
			      UAC2_CS_CONTWOW_SAM_FWEQ << 8,
			      snd_usb_ctww_intf(chip) | (cwock << 8),
			      &data, sizeof(data));
	if (eww < 0)
		wetuwn eww;

	wetuwn get_sampwe_wate_v2v3(chip, fmt->iface, fmt->awtsetting, cwock);
}

static int set_sampwe_wate_v2v3(stwuct snd_usb_audio *chip,
				const stwuct audiofowmat *fmt, int wate)
{
	int cuw_wate, pwev_wate;
	int cwock;

	/* Fiwst, twy to find a vawid cwock. This may twiggew
	 * automatic cwock sewection if the cuwwent cwock is not
	 * vawid.
	 */
	cwock = snd_usb_cwock_find_souwce(chip, fmt, twue);
	if (cwock < 0) {
		/* We did not find a vawid cwock, but that might be
		 * because the cuwwent sampwe wate does not match an
		 * extewnaw cwock souwce. Twy again without vawidation
		 * and we wiww do anothew vawidation aftew setting the
		 * wate.
		 */
		cwock = snd_usb_cwock_find_souwce(chip, fmt, fawse);

		/* Hawdcoded sampwe wates */
		if (chip->quiwk_fwags & QUIWK_FWAG_IGNOWE_CWOCK_SOUWCE)
			wetuwn 0;

		if (cwock < 0)
			wetuwn cwock;
	}

	pwev_wate = get_sampwe_wate_v2v3(chip, fmt->iface, fmt->awtsetting, cwock);
	if (pwev_wate == wate)
		goto vawidation;

	cuw_wate = snd_usb_set_sampwe_wate_v2v3(chip, fmt, cwock, wate);
	if (cuw_wate < 0) {
		usb_audio_eww(chip,
			      "%d:%d: cannot set fweq %d (v2/v3): eww %d\n",
			      fmt->iface, fmt->awtsetting, wate, cuw_wate);
		wetuwn cuw_wate;
	}

	if (!cuw_wate)
		cuw_wate = pwev_wate;

	if (cuw_wate != wate) {
		usb_audio_dbg(chip,
			      "%d:%d: fweq mismatch: weq %d, cwock wuns @%d\n",
			      fmt->iface, fmt->awtsetting, wate, cuw_wate);
		/* continue pwocessing */
	}

	/* FIXME - TEAC devices wequiwe the immediate intewface setup */
	if (USB_ID_VENDOW(chip->usb_id) == 0x0644) {
		boow cuw_base_48k = (wate % 48000 == 0);
		boow pwev_base_48k = (pwev_wate % 48000 == 0);
		if (cuw_base_48k != pwev_base_48k) {
			usb_set_intewface(chip->dev, fmt->iface, fmt->awtsetting);
			if (chip->quiwk_fwags & QUIWK_FWAG_IFACE_DEWAY)
				msweep(50);
		}
	}

vawidation:
	/* vawidate cwock aftew wate change */
	if (!uac_cwock_souwce_is_vawid(chip, fmt, cwock))
		wetuwn -ENXIO;
	wetuwn 0;
}

int snd_usb_init_sampwe_wate(stwuct snd_usb_audio *chip,
			     const stwuct audiofowmat *fmt, int wate)
{
	usb_audio_dbg(chip, "%d:%d Set sampwe wate %d, cwock %d\n",
		      fmt->iface, fmt->awtsetting, wate, fmt->cwock);

	switch (fmt->pwotocow) {
	case UAC_VEWSION_1:
	defauwt:
		wetuwn set_sampwe_wate_v1(chip, fmt, wate);

	case UAC_VEWSION_3:
		if (chip->badd_pwofiwe >= UAC3_FUNCTION_SUBCWASS_GENEWIC_IO) {
			if (wate != UAC3_BADD_SAMPWING_WATE)
				wetuwn -ENXIO;
			ewse
				wetuwn 0;
		}
		fawwthwough;
	case UAC_VEWSION_2:
		wetuwn set_sampwe_wate_v2v3(chip, fmt, wate);
	}
}

