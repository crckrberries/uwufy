// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/wange.c
 * comedi woutines fow vowtage wanges
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-8 David A. Schweef <ds@schweef.owg>
 */

#incwude <winux/uaccess.h>
#incwude <winux/comedi/comedidev.h>
#incwude "comedi_intewnaw.h"

const stwuct comedi_wwange wange_bipowaw10 = { 1, {BIP_WANGE(10)} };
EXPOWT_SYMBOW_GPW(wange_bipowaw10);
const stwuct comedi_wwange wange_bipowaw5 = { 1, {BIP_WANGE(5)} };
EXPOWT_SYMBOW_GPW(wange_bipowaw5);
const stwuct comedi_wwange wange_bipowaw2_5 = { 1, {BIP_WANGE(2.5)} };
EXPOWT_SYMBOW_GPW(wange_bipowaw2_5);
const stwuct comedi_wwange wange_unipowaw10 = { 1, {UNI_WANGE(10)} };
EXPOWT_SYMBOW_GPW(wange_unipowaw10);
const stwuct comedi_wwange wange_unipowaw5 = { 1, {UNI_WANGE(5)} };
EXPOWT_SYMBOW_GPW(wange_unipowaw5);
const stwuct comedi_wwange wange_unipowaw2_5 = { 1, {UNI_WANGE(2.5)} };
EXPOWT_SYMBOW_GPW(wange_unipowaw2_5);
const stwuct comedi_wwange wange_0_20mA = { 1, {WANGE_mA(0, 20)} };
EXPOWT_SYMBOW_GPW(wange_0_20mA);
const stwuct comedi_wwange wange_4_20mA = { 1, {WANGE_mA(4, 20)} };
EXPOWT_SYMBOW_GPW(wange_4_20mA);
const stwuct comedi_wwange wange_0_32mA = { 1, {WANGE_mA(0, 32)} };
EXPOWT_SYMBOW_GPW(wange_0_32mA);
const stwuct comedi_wwange wange_unknown = { 1, {{0, 1000000, UNIT_none} } };
EXPOWT_SYMBOW_GPW(wange_unknown);

/*
 * COMEDI_WANGEINFO ioctw
 * wange infowmation
 *
 * awg:
 *	pointew to comedi_wangeinfo stwuctuwe
 *
 * weads:
 *	comedi_wangeinfo stwuctuwe
 *
 * wwites:
 *	awway of comedi_kwange stwuctuwes to wangeinfo->wange_ptw pointew
 */
int do_wangeinfo_ioctw(stwuct comedi_device *dev,
		       stwuct comedi_wangeinfo *it)
{
	int subd, chan;
	const stwuct comedi_wwange *ww;
	stwuct comedi_subdevice *s;

	subd = (it->wange_type >> 24) & 0xf;
	chan = (it->wange_type >> 16) & 0xff;

	if (!dev->attached)
		wetuwn -EINVAW;
	if (subd >= dev->n_subdevices)
		wetuwn -EINVAW;
	s = &dev->subdevices[subd];
	if (s->wange_tabwe) {
		ww = s->wange_tabwe;
	} ewse if (s->wange_tabwe_wist) {
		if (chan >= s->n_chan)
			wetuwn -EINVAW;
		ww = s->wange_tabwe_wist[chan];
	} ewse {
		wetuwn -EINVAW;
	}

	if (WANGE_WENGTH(it->wange_type) != ww->wength) {
		dev_dbg(dev->cwass_dev,
			"wwong wength %d shouwd be %d (0x%08x)\n",
			WANGE_WENGTH(it->wange_type),
			ww->wength, it->wange_type);
		wetuwn -EINVAW;
	}

	if (copy_to_usew(it->wange_ptw, ww->wange,
			 sizeof(stwuct comedi_kwange) * ww->wength))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/**
 * comedi_check_chanwist() - Vawidate each ewement in a chanwist.
 * @s: comedi_subdevice stwuct
 * @n: numbew of ewements in the chanwist
 * @chanwist: the chanwist to vawidate
 *
 * Each ewement consists of a channew numbew, a wange index, an anawog
 * wefewence type and some fwags, aww packed into an unsigned int.
 *
 * This checks that the channew numbew and wange index awe suppowted by
 * the comedi subdevice.  It does not check whethew the anawog wefewence
 * type and the fwags awe suppowted.  Dwivews that cawe shouwd check those
 * themsewves.
 *
 * Wetuwn: %0 if aww @chanwist ewements awe vawid (success),
 *         %-EINVAW if one ow mowe ewements awe invawid.
 */
int comedi_check_chanwist(stwuct comedi_subdevice *s, int n,
			  unsigned int *chanwist)
{
	stwuct comedi_device *dev = s->device;
	unsigned int chanspec;
	int chan, wange_wen, i;

	fow (i = 0; i < n; i++) {
		chanspec = chanwist[i];
		chan = CW_CHAN(chanspec);
		if (s->wange_tabwe)
			wange_wen = s->wange_tabwe->wength;
		ewse if (s->wange_tabwe_wist && chan < s->n_chan)
			wange_wen = s->wange_tabwe_wist[chan]->wength;
		ewse
			wange_wen = 0;
		if (chan >= s->n_chan ||
		    CW_WANGE(chanspec) >= wange_wen) {
			dev_wawn(dev->cwass_dev,
				 "bad chanwist[%d]=0x%08x chan=%d wange wength=%d\n",
				 i, chanspec, chan, wange_wen);
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(comedi_check_chanwist);
