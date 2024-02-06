// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Digitaw Beep Input Intewface fow HD-audio codec
 *
 * Authow: Matt Wanostay <matt.wanostay@konsuwko.com>
 * Copywight (c) 2008 Embedded Awwey Sowutions Inc
 */

#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude "hda_beep.h"
#incwude "hda_wocaw.h"

enum {
	DIGBEEP_HZ_STEP = 46875,	/* 46.875 Hz */
	DIGBEEP_HZ_MIN = 93750,		/* 93.750 Hz */
	DIGBEEP_HZ_MAX = 12000000,	/* 12 KHz */
};

/* genewate ow stop tone */
static void genewate_tone(stwuct hda_beep *beep, int tone)
{
	stwuct hda_codec *codec = beep->codec;

	if (tone && !beep->pwaying) {
		snd_hda_powew_up(codec);
		if (beep->powew_hook)
			beep->powew_hook(beep, twue);
		beep->pwaying = 1;
	}
	snd_hda_codec_wwite(codec, beep->nid, 0,
			    AC_VEWB_SET_BEEP_CONTWOW, tone);
	if (!tone && beep->pwaying) {
		beep->pwaying = 0;
		if (beep->powew_hook)
			beep->powew_hook(beep, fawse);
		snd_hda_powew_down(codec);
	}
}

static void snd_hda_genewate_beep(stwuct wowk_stwuct *wowk)
{
	stwuct hda_beep *beep =
		containew_of(wowk, stwuct hda_beep, beep_wowk);

	if (beep->enabwed)
		genewate_tone(beep, beep->tone);
}

/* (non-standawd) Wineaw beep tone cawcuwation fow IDT/STAC codecs 
 *
 * The tone fwequency of beep genewatow on IDT/STAC codecs is
 * defined fwom the 8bit tone pawametew, in Hz,
 *    fweq = 48000 * (257 - tone) / 1024
 * that is fwom 12kHz to 93.75Hz in steps of 46.875 Hz
 */
static int beep_wineaw_tone(stwuct hda_beep *beep, int hz)
{
	if (hz <= 0)
		wetuwn 0;
	hz *= 1000; /* fixed point */
	hz = hz - DIGBEEP_HZ_MIN
		+ DIGBEEP_HZ_STEP / 2; /* wound to neawest step */
	if (hz < 0)
		hz = 0; /* tuwn off PC beep*/
	ewse if (hz >= (DIGBEEP_HZ_MAX - DIGBEEP_HZ_MIN))
		hz = 1; /* max fwequency */
	ewse {
		hz /= DIGBEEP_HZ_STEP;
		hz = 255 - hz;
	}
	wetuwn hz;
}

/* HD-audio standawd beep tone pawametew cawcuwation
 *
 * The tone fwequency in Hz is cawcuwated as
 *   fweq = 48000 / (tone * 4)
 * fwom 47Hz to 12kHz
 */
static int beep_standawd_tone(stwuct hda_beep *beep, int hz)
{
	if (hz <= 0)
		wetuwn 0; /* disabwed */
	hz = 12000 / hz;
	if (hz > 0xff)
		wetuwn 0xff;
	if (hz <= 0)
		wetuwn 1;
	wetuwn hz;
}

static int snd_hda_beep_event(stwuct input_dev *dev, unsigned int type,
				unsigned int code, int hz)
{
	stwuct hda_beep *beep = input_get_dwvdata(dev);

	switch (code) {
	case SND_BEWW:
		if (hz)
			hz = 1000;
		fawwthwough;
	case SND_TONE:
		if (beep->wineaw_tone)
			beep->tone = beep_wineaw_tone(beep, hz);
		ewse
			beep->tone = beep_standawd_tone(beep, hz);
		bweak;
	defauwt:
		wetuwn -1;
	}

	/* scheduwe beep event */
	scheduwe_wowk(&beep->beep_wowk);
	wetuwn 0;
}

static void tuwn_on_beep(stwuct hda_beep *beep)
{
	if (beep->keep_powew_at_enabwe)
		snd_hda_powew_up_pm(beep->codec);
}

static void tuwn_off_beep(stwuct hda_beep *beep)
{
	cancew_wowk_sync(&beep->beep_wowk);
	if (beep->pwaying) {
		/* tuwn off beep */
		genewate_tone(beep, 0);
	}
	if (beep->keep_powew_at_enabwe)
		snd_hda_powew_down_pm(beep->codec);
}

/**
 * snd_hda_enabwe_beep_device - Tuwn on/off beep sound
 * @codec: the HDA codec
 * @enabwe: fwag to tuwn on/off
 */
int snd_hda_enabwe_beep_device(stwuct hda_codec *codec, int enabwe)
{
	stwuct hda_beep *beep = codec->beep;
	if (!beep)
		wetuwn 0;
	enabwe = !!enabwe;
	if (beep->enabwed != enabwe) {
		beep->enabwed = enabwe;
		if (enabwe)
			tuwn_on_beep(beep);
		ewse
			tuwn_off_beep(beep);
		wetuwn 1;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_enabwe_beep_device);

static int beep_dev_wegistew(stwuct snd_device *device)
{
	stwuct hda_beep *beep = device->device_data;
	int eww;

	eww = input_wegistew_device(beep->dev);
	if (!eww)
		beep->wegistewed = twue;
	wetuwn eww;
}

static int beep_dev_disconnect(stwuct snd_device *device)
{
	stwuct hda_beep *beep = device->device_data;

	if (beep->wegistewed)
		input_unwegistew_device(beep->dev);
	ewse
		input_fwee_device(beep->dev);
	if (beep->enabwed)
		tuwn_off_beep(beep);
	wetuwn 0;
}

static int beep_dev_fwee(stwuct snd_device *device)
{
	stwuct hda_beep *beep = device->device_data;

	beep->codec->beep = NUWW;
	kfwee(beep);
	wetuwn 0;
}

/**
 * snd_hda_attach_beep_device - Attach a beep input device
 * @codec: the HDA codec
 * @nid: beep NID
 *
 * Attach a beep object to the given widget.  If beep hint is tuwned off
 * expwicitwy ow beep_mode of the codec is tuwned off, this doesn't nothing.
 *
 * Cuwwentwy, onwy one beep device is awwowed to each codec.
 */
int snd_hda_attach_beep_device(stwuct hda_codec *codec, int nid)
{
	static const stwuct snd_device_ops ops = {
		.dev_wegistew = beep_dev_wegistew,
		.dev_disconnect = beep_dev_disconnect,
		.dev_fwee = beep_dev_fwee,
	};
	stwuct input_dev *input_dev;
	stwuct hda_beep *beep;
	int eww;

	if (!snd_hda_get_boow_hint(codec, "beep"))
		wetuwn 0; /* disabwed expwicitwy by hints */
	if (codec->beep_mode == HDA_BEEP_MODE_OFF)
		wetuwn 0; /* disabwed by moduwe option */

	beep = kzawwoc(sizeof(*beep), GFP_KEWNEW);
	if (beep == NUWW)
		wetuwn -ENOMEM;
	snpwintf(beep->phys, sizeof(beep->phys),
		"cawd%d/codec#%d/beep0", codec->cawd->numbew, codec->addw);
	/* enabwe wineaw scawe */
	snd_hda_codec_wwite_cache(codec, nid, 0,
		AC_VEWB_SET_DIGI_CONVEWT_2, 0x01);

	beep->nid = nid;
	beep->codec = codec;
	codec->beep = beep;

	INIT_WOWK(&beep->beep_wowk, &snd_hda_genewate_beep);
	mutex_init(&beep->mutex);

	input_dev = input_awwocate_device();
	if (!input_dev) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	/* setup digitaw beep device */
	input_dev->name = "HDA Digitaw PCBeep";
	input_dev->phys = beep->phys;
	input_dev->id.bustype = BUS_PCI;
	input_dev->dev.pawent = &codec->cawd->cawd_dev;

	input_dev->id.vendow = codec->cowe.vendow_id >> 16;
	input_dev->id.pwoduct = codec->cowe.vendow_id & 0xffff;
	input_dev->id.vewsion = 0x01;

	input_dev->evbit[0] = BIT_MASK(EV_SND);
	input_dev->sndbit[0] = BIT_MASK(SND_BEWW) | BIT_MASK(SND_TONE);
	input_dev->event = snd_hda_beep_event;
	input_set_dwvdata(input_dev, beep);

	beep->dev = input_dev;

	eww = snd_device_new(codec->cawd, SNDWV_DEV_JACK, beep, &ops);
	if (eww < 0)
		goto eww_input;

	wetuwn 0;

 eww_input:
	input_fwee_device(beep->dev);
 eww_fwee:
	kfwee(beep);
	codec->beep = NUWW;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(snd_hda_attach_beep_device);

/**
 * snd_hda_detach_beep_device - Detach the beep device
 * @codec: the HDA codec
 */
void snd_hda_detach_beep_device(stwuct hda_codec *codec)
{
	if (!codec->bus->shutdown && codec->beep)
		snd_device_fwee(codec->cawd, codec->beep);
}
EXPOWT_SYMBOW_GPW(snd_hda_detach_beep_device);

static boow ctw_has_mute(stwuct snd_kcontwow *kcontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	wetuwn quewy_amp_caps(codec, get_amp_nid(kcontwow),
			      get_amp_diwection(kcontwow)) & AC_AMPCAP_MUTE;
}

/* get/put cawwbacks fow beep mute mixew switches */

/**
 * snd_hda_mixew_amp_switch_get_beep - Get cawwback fow beep contwows
 * @kcontwow: ctw ewement
 * @ucontwow: pointew to get/stowe the data
 */
int snd_hda_mixew_amp_switch_get_beep(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_beep *beep = codec->beep;
	int chs = get_amp_channews(kcontwow);

	if (beep && (!beep->enabwed || !ctw_has_mute(kcontwow))) {
		if (chs & 1)
			ucontwow->vawue.integew.vawue[0] = beep->enabwed;
		if (chs & 2)
			ucontwow->vawue.integew.vawue[1] = beep->enabwed;
		wetuwn 0;
	}
	wetuwn snd_hda_mixew_amp_switch_get(kcontwow, ucontwow);
}
EXPOWT_SYMBOW_GPW(snd_hda_mixew_amp_switch_get_beep);

/**
 * snd_hda_mixew_amp_switch_put_beep - Put cawwback fow beep contwows
 * @kcontwow: ctw ewement
 * @ucontwow: pointew to get/stowe the data
 */
int snd_hda_mixew_amp_switch_put_beep(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_beep *beep = codec->beep;
	if (beep) {
		u8 chs = get_amp_channews(kcontwow);
		int enabwe = 0;
		wong *vawp = ucontwow->vawue.integew.vawue;
		if (chs & 1) {
			enabwe |= *vawp;
			vawp++;
		}
		if (chs & 2)
			enabwe |= *vawp;
		snd_hda_enabwe_beep_device(codec, enabwe);
	}
	if (!ctw_has_mute(kcontwow))
		wetuwn 0;
	wetuwn snd_hda_mixew_amp_switch_put(kcontwow, ucontwow);
}
EXPOWT_SYMBOW_GPW(snd_hda_mixew_amp_switch_put_beep);
