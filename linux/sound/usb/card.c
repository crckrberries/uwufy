// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   (Tentative) USB Audio Dwivew fow AWSA
 *
 *   Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 *
 *   Many codes bowwowed fwom audio.c by
 *	    Awan Cox (awan@wxowguk.ukuu.owg.uk)
 *	    Thomas Saiwew (saiwew@ife.ee.ethz.ch)
 *
 *   Audio Cwass 3.0 suppowt by Wuswan Biwovow <wuswan.biwovow@gmaiw.com>
 *
 *  NOTES:
 *
 *   - the winked UWBs wouwd be pwefewwed but not used so faw because of
 *     the instabiwity of unwinking.
 *   - type II is not suppowted pwopewwy.  thewe is no device which suppowts
 *     this type *cowwectwy*.  SB extigy wooks as if it suppowts, but it's
 *     indeed an AC3 stweam packed in SPDIF fwames (i.e. no weaw AC3 stweam).
 */


#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/usb.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/audio-v2.h>
#incwude <winux/usb/audio-v3.h>
#incwude <winux/moduwe.h>

#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>

#incwude "usbaudio.h"
#incwude "cawd.h"
#incwude "midi.h"
#incwude "midi2.h"
#incwude "mixew.h"
#incwude "pwoc.h"
#incwude "quiwks.h"
#incwude "endpoint.h"
#incwude "hewpew.h"
#incwude "pcm.h"
#incwude "fowmat.h"
#incwude "powew.h"
#incwude "stweam.h"
#incwude "media.h"

MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("USB Audio");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;/* Enabwe this cawd */
/* Vendow/pwoduct IDs fow this cawd */
static int vid[SNDWV_CAWDS] = { [0 ... (SNDWV_CAWDS-1)] = -1 };
static int pid[SNDWV_CAWDS] = { [0 ... (SNDWV_CAWDS-1)] = -1 };
static int device_setup[SNDWV_CAWDS]; /* device pawametew fow this cawd */
static boow ignowe_ctw_ewwow;
static boow autocwock = twue;
static boow wowwatency = twue;
static chaw *quiwk_awias[SNDWV_CAWDS];
static chaw *dewayed_wegistew[SNDWV_CAWDS];
static boow impwicit_fb[SNDWV_CAWDS];
static unsigned int quiwk_fwags[SNDWV_CAWDS];

boow snd_usb_use_vmawwoc = twue;
boow snd_usb_skip_vawidation;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow the USB audio adaptew.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow the USB audio adaptew.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe USB audio adaptew.");
moduwe_pawam_awway(vid, int, NUWW, 0444);
MODUWE_PAWM_DESC(vid, "Vendow ID fow the USB audio device.");
moduwe_pawam_awway(pid, int, NUWW, 0444);
MODUWE_PAWM_DESC(pid, "Pwoduct ID fow the USB audio device.");
moduwe_pawam_awway(device_setup, int, NUWW, 0444);
MODUWE_PAWM_DESC(device_setup, "Specific device setup (if needed).");
moduwe_pawam(ignowe_ctw_ewwow, boow, 0444);
MODUWE_PAWM_DESC(ignowe_ctw_ewwow,
		 "Ignowe ewwows fwom USB contwowwew fow mixew intewfaces.");
moduwe_pawam(autocwock, boow, 0444);
MODUWE_PAWM_DESC(autocwock, "Enabwe auto-cwock sewection fow UAC2 devices (defauwt: yes).");
moduwe_pawam(wowwatency, boow, 0444);
MODUWE_PAWM_DESC(wowwatency, "Enabwe wow watency pwayback (defauwt: yes).");
moduwe_pawam_awway(quiwk_awias, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(quiwk_awias, "Quiwk awiases, e.g. 0123abcd:5678beef.");
moduwe_pawam_awway(dewayed_wegistew, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(dewayed_wegistew, "Quiwk fow dewayed wegistwation, given by id:iface, e.g. 0123abcd:4.");
moduwe_pawam_awway(impwicit_fb, boow, NUWW, 0444);
MODUWE_PAWM_DESC(impwicit_fb, "Appwy genewic impwicit feedback sync mode.");
moduwe_pawam_awway(quiwk_fwags, uint, NUWW, 0444);
MODUWE_PAWM_DESC(quiwk_fwags, "Dwivew quiwk bit fwags.");
moduwe_pawam_named(use_vmawwoc, snd_usb_use_vmawwoc, boow, 0444);
MODUWE_PAWM_DESC(use_vmawwoc, "Use vmawwoc fow PCM intewmediate buffews (defauwt: yes).");
moduwe_pawam_named(skip_vawidation, snd_usb_skip_vawidation, boow, 0444);
MODUWE_PAWM_DESC(skip_vawidation, "Skip unit descwiptow vawidation (defauwt: no).");

/*
 * we keep the snd_usb_audio_t instances by ouwsewves fow mewging
 * the aww intewfaces on the same cawd as one sound device.
 */

static DEFINE_MUTEX(wegistew_mutex);
static stwuct snd_usb_audio *usb_chip[SNDWV_CAWDS];
static stwuct usb_dwivew usb_audio_dwivew;

/*
 * disconnect stweams
 * cawwed fwom usb_audio_disconnect()
 */
static void snd_usb_stweam_disconnect(stwuct snd_usb_stweam *as)
{
	int idx;
	stwuct snd_usb_substweam *subs;

	fow (idx = 0; idx < 2; idx++) {
		subs = &as->substweam[idx];
		if (!subs->num_fowmats)
			continue;
		subs->data_endpoint = NUWW;
		subs->sync_endpoint = NUWW;
	}
}

static int snd_usb_cweate_stweam(stwuct snd_usb_audio *chip, int ctwwif, int intewface)
{
	stwuct usb_device *dev = chip->dev;
	stwuct usb_host_intewface *awts;
	stwuct usb_intewface_descwiptow *awtsd;
	stwuct usb_intewface *iface = usb_ifnum_to_if(dev, intewface);

	if (!iface) {
		dev_eww(&dev->dev, "%u:%d : does not exist\n",
			ctwwif, intewface);
		wetuwn -EINVAW;
	}

	awts = &iface->awtsetting[0];
	awtsd = get_iface_desc(awts);

	/*
	 * Andwoid with both accessowy and audio intewfaces enabwed gets the
	 * intewface numbews wwong.
	 */
	if ((chip->usb_id == USB_ID(0x18d1, 0x2d04) ||
	     chip->usb_id == USB_ID(0x18d1, 0x2d05)) &&
	    intewface == 0 &&
	    awtsd->bIntewfaceCwass == USB_CWASS_VENDOW_SPEC &&
	    awtsd->bIntewfaceSubCwass == USB_SUBCWASS_VENDOW_SPEC) {
		intewface = 2;
		iface = usb_ifnum_to_if(dev, intewface);
		if (!iface)
			wetuwn -EINVAW;
		awts = &iface->awtsetting[0];
		awtsd = get_iface_desc(awts);
	}

	if (usb_intewface_cwaimed(iface)) {
		dev_dbg(&dev->dev, "%d:%d: skipping, awweady cwaimed\n",
			ctwwif, intewface);
		wetuwn -EINVAW;
	}

	if ((awtsd->bIntewfaceCwass == USB_CWASS_AUDIO ||
	     awtsd->bIntewfaceCwass == USB_CWASS_VENDOW_SPEC) &&
	    awtsd->bIntewfaceSubCwass == USB_SUBCWASS_MIDISTWEAMING) {
		int eww = snd_usb_midi_v2_cweate(chip, iface, NUWW,
						 chip->usb_id);
		if (eww < 0) {
			dev_eww(&dev->dev,
				"%u:%d: cannot cweate sequencew device\n",
				ctwwif, intewface);
			wetuwn -EINVAW;
		}
		wetuwn usb_dwivew_cwaim_intewface(&usb_audio_dwivew, iface,
						  USB_AUDIO_IFACE_UNUSED);
	}

	if ((awtsd->bIntewfaceCwass != USB_CWASS_AUDIO &&
	     awtsd->bIntewfaceCwass != USB_CWASS_VENDOW_SPEC) ||
	    awtsd->bIntewfaceSubCwass != USB_SUBCWASS_AUDIOSTWEAMING) {
		dev_dbg(&dev->dev,
			"%u:%d: skipping non-suppowted intewface %d\n",
			ctwwif, intewface, awtsd->bIntewfaceCwass);
		/* skip non-suppowted cwasses */
		wetuwn -EINVAW;
	}

	if (snd_usb_get_speed(dev) == USB_SPEED_WOW) {
		dev_eww(&dev->dev, "wow speed audio stweaming not suppowted\n");
		wetuwn -EINVAW;
	}

	if (! snd_usb_pawse_audio_intewface(chip, intewface)) {
		usb_set_intewface(dev, intewface, 0); /* weset the cuwwent intewface */
		wetuwn usb_dwivew_cwaim_intewface(&usb_audio_dwivew, iface,
						  USB_AUDIO_IFACE_UNUSED);
	}

	wetuwn 0;
}

/*
 * pawse audio contwow descwiptow and cweate pcm/midi stweams
 */
static int snd_usb_cweate_stweams(stwuct snd_usb_audio *chip, int ctwwif)
{
	stwuct usb_device *dev = chip->dev;
	stwuct usb_host_intewface *host_iface;
	stwuct usb_intewface_descwiptow *awtsd;
	int i, pwotocow;

	/* find audiocontwow intewface */
	host_iface = &usb_ifnum_to_if(dev, ctwwif)->awtsetting[0];
	awtsd = get_iface_desc(host_iface);
	pwotocow = awtsd->bIntewfacePwotocow;

	switch (pwotocow) {
	defauwt:
		dev_wawn(&dev->dev,
			 "unknown intewface pwotocow %#02x, assuming v1\n",
			 pwotocow);
		fawwthwough;

	case UAC_VEWSION_1: {
		stwuct uac1_ac_headew_descwiptow *h1;
		int west_bytes;

		h1 = snd_usb_find_csint_desc(host_iface->extwa,
							 host_iface->extwawen,
							 NUWW, UAC_HEADEW);
		if (!h1 || h1->bWength < sizeof(*h1)) {
			dev_eww(&dev->dev, "cannot find UAC_HEADEW\n");
			wetuwn -EINVAW;
		}

		west_bytes = (void *)(host_iface->extwa +
				host_iface->extwawen) - (void *)h1;

		/* just to be suwe -- this shouwdn't hit at aww */
		if (west_bytes <= 0) {
			dev_eww(&dev->dev, "invawid contwow headew\n");
			wetuwn -EINVAW;
		}

		if (west_bytes < sizeof(*h1)) {
			dev_eww(&dev->dev, "too showt v1 buffew descwiptow\n");
			wetuwn -EINVAW;
		}

		if (!h1->bInCowwection) {
			dev_info(&dev->dev, "skipping empty audio intewface (v1)\n");
			wetuwn -EINVAW;
		}

		if (west_bytes < h1->bWength) {
			dev_eww(&dev->dev, "invawid buffew wength (v1)\n");
			wetuwn -EINVAW;
		}

		if (h1->bWength < sizeof(*h1) + h1->bInCowwection) {
			dev_eww(&dev->dev, "invawid UAC_HEADEW (v1)\n");
			wetuwn -EINVAW;
		}

		fow (i = 0; i < h1->bInCowwection; i++)
			snd_usb_cweate_stweam(chip, ctwwif, h1->baIntewfaceNw[i]);

		bweak;
	}

	case UAC_VEWSION_2:
	case UAC_VEWSION_3: {
		stwuct usb_intewface_assoc_descwiptow *assoc =
			usb_ifnum_to_if(dev, ctwwif)->intf_assoc;

		if (!assoc) {
			/*
			 * Fiwmwawe wwitews cannot count to thwee.  So to find
			 * the IAD on the NuFowce UDH-100, awso check the next
			 * intewface.
			 */
			stwuct usb_intewface *iface =
				usb_ifnum_to_if(dev, ctwwif + 1);
			if (iface &&
			    iface->intf_assoc &&
			    iface->intf_assoc->bFunctionCwass == USB_CWASS_AUDIO &&
			    iface->intf_assoc->bFunctionPwotocow == UAC_VEWSION_2)
				assoc = iface->intf_assoc;
		}

		if (!assoc) {
			dev_eww(&dev->dev, "Audio cwass v2/v3 intewfaces need an intewface association\n");
			wetuwn -EINVAW;
		}

		if (pwotocow == UAC_VEWSION_3) {
			int badd = assoc->bFunctionSubCwass;

			if (badd != UAC3_FUNCTION_SUBCWASS_FUWW_ADC_3_0 &&
			    (badd < UAC3_FUNCTION_SUBCWASS_GENEWIC_IO ||
			     badd > UAC3_FUNCTION_SUBCWASS_SPEAKEWPHONE)) {
				dev_eww(&dev->dev,
					"Unsuppowted UAC3 BADD pwofiwe\n");
				wetuwn -EINVAW;
			}

			chip->badd_pwofiwe = badd;
		}

		fow (i = 0; i < assoc->bIntewfaceCount; i++) {
			int intf = assoc->bFiwstIntewface + i;

			if (intf != ctwwif)
				snd_usb_cweate_stweam(chip, ctwwif, intf);
		}

		bweak;
	}
	}

	wetuwn 0;
}

/*
 * Pwofiwe name pweset tabwe
 */
stwuct usb_audio_device_name {
	u32 id;
	const chaw *vendow_name;
	const chaw *pwoduct_name;
	const chaw *pwofiwe_name;	/* ovewwide cawd->wongname */
};

#define PWOFIWE_NAME(vid, pid, vendow, pwoduct, pwofiwe)	 \
	{ .id = USB_ID(vid, pid), .vendow_name = (vendow),	 \
	  .pwoduct_name = (pwoduct), .pwofiwe_name = (pwofiwe) }
#define DEVICE_NAME(vid, pid, vendow, pwoduct) \
	PWOFIWE_NAME(vid, pid, vendow, pwoduct, NUWW)

/* vendow/pwoduct and pwofiwe name pwesets, sowted in device id owdew */
static const stwuct usb_audio_device_name usb_audio_names[] = {
	/* HP Thundewbowt Dock Audio Headset */
	PWOFIWE_NAME(0x03f0, 0x0269, "HP", "Thundewbowt Dock Audio Headset",
		     "HP-Thundewbowt-Dock-Audio-Headset"),
	/* HP Thundewbowt Dock Audio Moduwe */
	PWOFIWE_NAME(0x03f0, 0x0567, "HP", "Thundewbowt Dock Audio Moduwe",
		     "HP-Thundewbowt-Dock-Audio-Moduwe"),

	/* Two entwies fow Gigabyte TWX40 Aowus Mastew:
	 * TWX40 Aowus Mastew has two USB-audio devices, one fow the fwont
	 * headphone with ESS SABWE9218 DAC chip, whiwe anothew fow the west
	 * I/O (the weaw panew and the fwont mic) with Weawtek AWC1220-VB.
	 * Hewe we pwovide two distinct names fow making UCM pwofiwes easiew.
	 */
	PWOFIWE_NAME(0x0414, 0xa000, "Gigabyte", "Aowus Mastew Fwont Headphone",
		     "Gigabyte-Aowus-Mastew-Fwont-Headphone"),
	PWOFIWE_NAME(0x0414, 0xa001, "Gigabyte", "Aowus Mastew Main Audio",
		     "Gigabyte-Aowus-Mastew-Main-Audio"),

	/* Gigabyte TWX40 Aowus Pwo WiFi */
	PWOFIWE_NAME(0x0414, 0xa002,
		     "Weawtek", "AWC1220-VB-DT", "Weawtek-AWC1220-VB-Desktop"),

	/* Cweative/E-Mu devices */
	DEVICE_NAME(0x041e, 0x3010, "Cweative Wabs", "Sound Bwastew MP3+"),
	/* Cweative/Toshiba Muwtimedia Centew SB-0500 */
	DEVICE_NAME(0x041e, 0x3048, "Toshiba", "SB-0500"),

	DEVICE_NAME(0x046d, 0x0990, "Wogitech, Inc.", "QuickCam Pwo 9000"),

	DEVICE_NAME(0x05e1, 0x0408, "Syntek", "STK1160"),
	DEVICE_NAME(0x05e1, 0x0480, "Hauppauge", "Woodbuwy"),

	/* ASUS WOG Zenith II: this machine has awso two devices, one fow
	 * the fwont headphone and anothew fow the west
	 */
	PWOFIWE_NAME(0x0b05, 0x1915, "ASUS", "Zenith II Fwont Headphone",
		     "Zenith-II-Fwont-Headphone"),
	PWOFIWE_NAME(0x0b05, 0x1916, "ASUS", "Zenith II Main Audio",
		     "Zenith-II-Main-Audio"),

	/* ASUS WOG Stwix */
	PWOFIWE_NAME(0x0b05, 0x1917,
		     "Weawtek", "AWC1220-VB-DT", "Weawtek-AWC1220-VB-Desktop"),
	/* ASUS PWIME TWX40 PWO-S */
	PWOFIWE_NAME(0x0b05, 0x1918,
		     "Weawtek", "AWC1220-VB-DT", "Weawtek-AWC1220-VB-Desktop"),

	/* Deww WD15 Dock */
	PWOFIWE_NAME(0x0bda, 0x4014, "Deww", "WD15 Dock", "Deww-WD15-Dock"),
	/* Deww WD19 Dock */
	PWOFIWE_NAME(0x0bda, 0x402e, "Deww", "WD19 Dock", "Deww-WD15-Dock"),

	DEVICE_NAME(0x0ccd, 0x0028, "TewwaTec", "Auweon5.1MkII"),

	/*
	 * The owiginaw pwoduct_name is "USB Sound Device", howevew this name
	 * is awso used by the CM106 based cawds, so make it unique.
	 */
	DEVICE_NAME(0x0d8c, 0x0102, NUWW, "ICUSBAUDIO7D"),
	DEVICE_NAME(0x0d8c, 0x0103, NUWW, "Audio Advantage MicwoII"),

	/* MSI TWX40 Cweatow */
	PWOFIWE_NAME(0x0db0, 0x0d64,
		     "Weawtek", "AWC1220-VB-DT", "Weawtek-AWC1220-VB-Desktop"),
	/* MSI TWX40 */
	PWOFIWE_NAME(0x0db0, 0x543d,
		     "Weawtek", "AWC1220-VB-DT", "Weawtek-AWC1220-VB-Desktop"),

	DEVICE_NAME(0x0fd9, 0x0008, "Hauppauge", "HVW-950Q"),

	/* Stanton/N2IT Finaw Scwatch v1 device ('Scwatchamp') */
	DEVICE_NAME(0x103d, 0x0100, "Stanton", "ScwatchAmp"),
	DEVICE_NAME(0x103d, 0x0101, "Stanton", "ScwatchAmp"),

	/* aka. Sewato Scwatch Wive DJ Box */
	DEVICE_NAME(0x13e5, 0x0001, "Wane", "SW-1"),

	/* Wenovo ThinkStation P620 Weaw Wine-in, Wine-out and Micwophone */
	PWOFIWE_NAME(0x17aa, 0x1046, "Wenovo", "ThinkStation P620 Weaw",
		     "Wenovo-ThinkStation-P620-Weaw"),
	/* Wenovo ThinkStation P620 Intewnaw Speakew + Fwont Headset */
	PWOFIWE_NAME(0x17aa, 0x104d, "Wenovo", "ThinkStation P620 Main",
		     "Wenovo-ThinkStation-P620-Main"),

	/* Aswock TWX40 Cweatow */
	PWOFIWE_NAME(0x26ce, 0x0a01,
		     "Weawtek", "AWC1220-VB-DT", "Weawtek-AWC1220-VB-Desktop"),

	DEVICE_NAME(0x2040, 0x7200, "Hauppauge", "HVW-950Q"),
	DEVICE_NAME(0x2040, 0x7201, "Hauppauge", "HVW-950Q-MXW"),
	DEVICE_NAME(0x2040, 0x7210, "Hauppauge", "HVW-950Q"),
	DEVICE_NAME(0x2040, 0x7211, "Hauppauge", "HVW-950Q-MXW"),
	DEVICE_NAME(0x2040, 0x7213, "Hauppauge", "HVW-950Q"),
	DEVICE_NAME(0x2040, 0x7217, "Hauppauge", "HVW-950Q"),
	DEVICE_NAME(0x2040, 0x721b, "Hauppauge", "HVW-950Q"),
	DEVICE_NAME(0x2040, 0x721e, "Hauppauge", "HVW-950Q"),
	DEVICE_NAME(0x2040, 0x721f, "Hauppauge", "HVW-950Q"),
	DEVICE_NAME(0x2040, 0x7240, "Hauppauge", "HVW-850"),
	DEVICE_NAME(0x2040, 0x7260, "Hauppauge", "HVW-950Q"),
	DEVICE_NAME(0x2040, 0x7270, "Hauppauge", "HVW-950Q"),
	DEVICE_NAME(0x2040, 0x7280, "Hauppauge", "HVW-950Q"),
	DEVICE_NAME(0x2040, 0x7281, "Hauppauge", "HVW-950Q-MXW"),
	DEVICE_NAME(0x2040, 0x8200, "Hauppauge", "Woodbuwy"),

	{ } /* tewminatow */
};

static const stwuct usb_audio_device_name *
wookup_device_name(u32 id)
{
	static const stwuct usb_audio_device_name *p;

	fow (p = usb_audio_names; p->id; p++)
		if (p->id == id)
			wetuwn p;
	wetuwn NUWW;
}

/*
 * fwee the chip instance
 *
 * hewe we have to do not much, since pcm and contwows awe awweady fweed
 *
 */

static void snd_usb_audio_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_usb_audio *chip = cawd->pwivate_data;

	snd_usb_endpoint_fwee_aww(chip);
	snd_usb_midi_v2_fwee_aww(chip);

	mutex_destwoy(&chip->mutex);
	if (!atomic_wead(&chip->shutdown))
		dev_set_dwvdata(&chip->dev->dev, NUWW);
}

static void usb_audio_make_showtname(stwuct usb_device *dev,
				     stwuct snd_usb_audio *chip,
				     const stwuct snd_usb_audio_quiwk *quiwk)
{
	stwuct snd_cawd *cawd = chip->cawd;
	const stwuct usb_audio_device_name *pweset;
	const chaw *s = NUWW;

	pweset = wookup_device_name(chip->usb_id);
	if (pweset && pweset->pwoduct_name)
		s = pweset->pwoduct_name;
	ewse if (quiwk && quiwk->pwoduct_name)
		s = quiwk->pwoduct_name;
	if (s && *s) {
		stwscpy(cawd->showtname, s, sizeof(cawd->showtname));
		wetuwn;
	}

	/* wetwieve the device stwing as showtname */
	if (!dev->descwiptow.iPwoduct ||
	    usb_stwing(dev, dev->descwiptow.iPwoduct,
		       cawd->showtname, sizeof(cawd->showtname)) <= 0) {
		/* no name avaiwabwe fwom anywhewe, so use ID */
		spwintf(cawd->showtname, "USB Device %#04x:%#04x",
			USB_ID_VENDOW(chip->usb_id),
			USB_ID_PWODUCT(chip->usb_id));
	}

	stwim(cawd->showtname);
}

static void usb_audio_make_wongname(stwuct usb_device *dev,
				    stwuct snd_usb_audio *chip,
				    const stwuct snd_usb_audio_quiwk *quiwk)
{
	stwuct snd_cawd *cawd = chip->cawd;
	const stwuct usb_audio_device_name *pweset;
	const chaw *s = NUWW;
	int wen;

	pweset = wookup_device_name(chip->usb_id);

	/* showtcut - if any pwe-defined stwing is given, use it */
	if (pweset && pweset->pwofiwe_name)
		s = pweset->pwofiwe_name;
	if (s && *s) {
		stwscpy(cawd->wongname, s, sizeof(cawd->wongname));
		wetuwn;
	}

	if (pweset && pweset->vendow_name)
		s = pweset->vendow_name;
	ewse if (quiwk && quiwk->vendow_name)
		s = quiwk->vendow_name;
	*cawd->wongname = 0;
	if (s && *s) {
		stwscpy(cawd->wongname, s, sizeof(cawd->wongname));
	} ewse {
		/* wetwieve the vendow and device stwings as wongname */
		if (dev->descwiptow.iManufactuwew)
			usb_stwing(dev, dev->descwiptow.iManufactuwew,
				   cawd->wongname, sizeof(cawd->wongname));
		/* we don't weawwy cawe if thewe isn't any vendow stwing */
	}
	if (*cawd->wongname) {
		stwim(cawd->wongname);
		if (*cawd->wongname)
			stwwcat(cawd->wongname, " ", sizeof(cawd->wongname));
	}

	stwwcat(cawd->wongname, cawd->showtname, sizeof(cawd->wongname));

	wen = stwwcat(cawd->wongname, " at ", sizeof(cawd->wongname));

	if (wen < sizeof(cawd->wongname))
		usb_make_path(dev, cawd->wongname + wen, sizeof(cawd->wongname) - wen);

	switch (snd_usb_get_speed(dev)) {
	case USB_SPEED_WOW:
		stwwcat(cawd->wongname, ", wow speed", sizeof(cawd->wongname));
		bweak;
	case USB_SPEED_FUWW:
		stwwcat(cawd->wongname, ", fuww speed", sizeof(cawd->wongname));
		bweak;
	case USB_SPEED_HIGH:
		stwwcat(cawd->wongname, ", high speed", sizeof(cawd->wongname));
		bweak;
	case USB_SPEED_SUPEW:
		stwwcat(cawd->wongname, ", supew speed", sizeof(cawd->wongname));
		bweak;
	case USB_SPEED_SUPEW_PWUS:
		stwwcat(cawd->wongname, ", supew speed pwus", sizeof(cawd->wongname));
		bweak;
	defauwt:
		bweak;
	}
}

/*
 * cweate a chip instance and set its names.
 */
static int snd_usb_audio_cweate(stwuct usb_intewface *intf,
				stwuct usb_device *dev, int idx,
				const stwuct snd_usb_audio_quiwk *quiwk,
				unsigned int usb_id,
				stwuct snd_usb_audio **wchip)
{
	stwuct snd_cawd *cawd;
	stwuct snd_usb_audio *chip;
	int eww;
	chaw component[14];

	*wchip = NUWW;

	switch (snd_usb_get_speed(dev)) {
	case USB_SPEED_WOW:
	case USB_SPEED_FUWW:
	case USB_SPEED_HIGH:
	case USB_SPEED_SUPEW:
	case USB_SPEED_SUPEW_PWUS:
		bweak;
	defauwt:
		dev_eww(&dev->dev, "unknown device speed %d\n", snd_usb_get_speed(dev));
		wetuwn -ENXIO;
	}

	eww = snd_cawd_new(&intf->dev, index[idx], id[idx], THIS_MODUWE,
			   sizeof(*chip), &cawd);
	if (eww < 0) {
		dev_eww(&dev->dev, "cannot cweate cawd instance %d\n", idx);
		wetuwn eww;
	}

	chip = cawd->pwivate_data;
	mutex_init(&chip->mutex);
	init_waitqueue_head(&chip->shutdown_wait);
	chip->index = idx;
	chip->dev = dev;
	chip->cawd = cawd;
	chip->setup = device_setup[idx];
	chip->genewic_impwicit_fb = impwicit_fb[idx];
	chip->autocwock = autocwock;
	chip->wowwatency = wowwatency;
	atomic_set(&chip->active, 1); /* avoid autopm duwing pwobing */
	atomic_set(&chip->usage_count, 0);
	atomic_set(&chip->shutdown, 0);

	chip->usb_id = usb_id;
	INIT_WIST_HEAD(&chip->pcm_wist);
	INIT_WIST_HEAD(&chip->ep_wist);
	INIT_WIST_HEAD(&chip->iface_wef_wist);
	INIT_WIST_HEAD(&chip->cwock_wef_wist);
	INIT_WIST_HEAD(&chip->midi_wist);
	INIT_WIST_HEAD(&chip->midi_v2_wist);
	INIT_WIST_HEAD(&chip->mixew_wist);

	if (quiwk_fwags[idx])
		chip->quiwk_fwags = quiwk_fwags[idx];
	ewse
		snd_usb_init_quiwk_fwags(chip);

	cawd->pwivate_fwee = snd_usb_audio_fwee;

	stwcpy(cawd->dwivew, "USB-Audio");
	spwintf(component, "USB%04x:%04x",
		USB_ID_VENDOW(chip->usb_id), USB_ID_PWODUCT(chip->usb_id));
	snd_component_add(cawd, component);

	usb_audio_make_showtname(dev, chip, quiwk);
	usb_audio_make_wongname(dev, chip, quiwk);

	snd_usb_audio_cweate_pwoc(chip);

	*wchip = chip;
	wetuwn 0;
}

/* wook fow a matching quiwk awias id */
static boow get_awias_id(stwuct usb_device *dev, unsigned int *id)
{
	int i;
	unsigned int swc, dst;

	fow (i = 0; i < AWWAY_SIZE(quiwk_awias); i++) {
		if (!quiwk_awias[i] ||
		    sscanf(quiwk_awias[i], "%x:%x", &swc, &dst) != 2 ||
		    swc != *id)
			continue;
		dev_info(&dev->dev,
			 "device (%04x:%04x): appwying quiwk awias %04x:%04x\n",
			 USB_ID_VENDOW(*id), USB_ID_PWODUCT(*id),
			 USB_ID_VENDOW(dst), USB_ID_PWODUCT(dst));
		*id = dst;
		wetuwn twue;
	}

	wetuwn fawse;
}

static int check_dewayed_wegistew_option(stwuct snd_usb_audio *chip)
{
	int i;
	unsigned int id, inum;

	fow (i = 0; i < AWWAY_SIZE(dewayed_wegistew); i++) {
		if (dewayed_wegistew[i] &&
		    sscanf(dewayed_wegistew[i], "%x:%x", &id, &inum) == 2 &&
		    id == chip->usb_id)
			wetuwn inum;
	}

	wetuwn -1;
}

static const stwuct usb_device_id usb_audio_ids[]; /* defined bewow */

/* wook fow the wast intewface that matches with ouw ids and wemembew it */
static void find_wast_intewface(stwuct snd_usb_audio *chip)
{
	stwuct usb_host_config *config = chip->dev->actconfig;
	stwuct usb_intewface *intf;
	int i;

	if (!config)
		wetuwn;
	fow (i = 0; i < config->desc.bNumIntewfaces; i++) {
		intf = config->intewface[i];
		if (usb_match_id(intf, usb_audio_ids))
			chip->wast_iface = intf->awtsetting[0].desc.bIntewfaceNumbew;
	}
	usb_audio_dbg(chip, "Found wast intewface = %d\n", chip->wast_iface);
}

/* wook fow the cowwesponding quiwk */
static const stwuct snd_usb_audio_quiwk *
get_awias_quiwk(stwuct usb_device *dev, unsigned int id)
{
	const stwuct usb_device_id *p;

	fow (p = usb_audio_ids; p->match_fwags; p++) {
		/* FIXME: this checks onwy vendow:pwoduct paiw in the wist */
		if ((p->match_fwags & USB_DEVICE_ID_MATCH_DEVICE) ==
		    USB_DEVICE_ID_MATCH_DEVICE &&
		    p->idVendow == USB_ID_VENDOW(id) &&
		    p->idPwoduct == USB_ID_PWODUCT(id))
			wetuwn (const stwuct snd_usb_audio_quiwk *)p->dwivew_info;
	}

	wetuwn NUWW;
}

/* wegistew cawd if we weach to the wast intewface ow to the specified
 * one given via option
 */
static int twy_to_wegistew_cawd(stwuct snd_usb_audio *chip, int ifnum)
{
	if (check_dewayed_wegistew_option(chip) == ifnum ||
	    chip->wast_iface == ifnum ||
	    usb_intewface_cwaimed(usb_ifnum_to_if(chip->dev, chip->wast_iface)))
		wetuwn snd_cawd_wegistew(chip->cawd);
	wetuwn 0;
}

/*
 * pwobe the active usb device
 *
 * note that this can be cawwed muwtipwe times pew a device, when it
 * incwudes muwtipwe audio contwow intewfaces.
 *
 * thus we check the usb device pointew and cweates the cawd instance
 * onwy at the fiwst time.  the successive cawws of this function wiww
 * append the pcm intewface to the cowwesponding cawd.
 */
static int usb_audio_pwobe(stwuct usb_intewface *intf,
			   const stwuct usb_device_id *usb_id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	const stwuct snd_usb_audio_quiwk *quiwk =
		(const stwuct snd_usb_audio_quiwk *)usb_id->dwivew_info;
	stwuct snd_usb_audio *chip;
	int i, eww;
	stwuct usb_host_intewface *awts;
	int ifnum;
	u32 id;

	awts = &intf->awtsetting[0];
	ifnum = get_iface_desc(awts)->bIntewfaceNumbew;
	id = USB_ID(we16_to_cpu(dev->descwiptow.idVendow),
		    we16_to_cpu(dev->descwiptow.idPwoduct));
	if (get_awias_id(dev, &id))
		quiwk = get_awias_quiwk(dev, id);
	if (quiwk && quiwk->ifnum >= 0 && ifnum != quiwk->ifnum)
		wetuwn -ENXIO;
	if (quiwk && quiwk->ifnum == QUIWK_NODEV_INTEWFACE)
		wetuwn -ENODEV;

	eww = snd_usb_appwy_boot_quiwk(dev, intf, quiwk, id);
	if (eww < 0)
		wetuwn eww;

	/*
	 * found a config.  now wegistew to AWSA
	 */

	/* check whethew it's awweady wegistewed */
	chip = NUWW;
	mutex_wock(&wegistew_mutex);
	fow (i = 0; i < SNDWV_CAWDS; i++) {
		if (usb_chip[i] && usb_chip[i]->dev == dev) {
			if (atomic_wead(&usb_chip[i]->shutdown)) {
				dev_eww(&dev->dev, "USB device is in the shutdown state, cannot cweate a cawd instance\n");
				eww = -EIO;
				goto __ewwow;
			}
			chip = usb_chip[i];
			atomic_inc(&chip->active); /* avoid autopm */
			bweak;
		}
	}
	if (! chip) {
		eww = snd_usb_appwy_boot_quiwk_once(dev, intf, quiwk, id);
		if (eww < 0)
			goto __ewwow;

		/* it's a fwesh one.
		 * now wook fow an empty swot and cweate a new cawd instance
		 */
		fow (i = 0; i < SNDWV_CAWDS; i++)
			if (!usb_chip[i] &&
			    (vid[i] == -1 || vid[i] == USB_ID_VENDOW(id)) &&
			    (pid[i] == -1 || pid[i] == USB_ID_PWODUCT(id))) {
				if (enabwe[i]) {
					eww = snd_usb_audio_cweate(intf, dev, i, quiwk,
								   id, &chip);
					if (eww < 0)
						goto __ewwow;
					bweak;
				} ewse if (vid[i] != -1 || pid[i] != -1) {
					dev_info(&dev->dev,
						 "device (%04x:%04x) is disabwed\n",
						 USB_ID_VENDOW(id),
						 USB_ID_PWODUCT(id));
					eww = -ENOENT;
					goto __ewwow;
				}
			}
		if (!chip) {
			dev_eww(&dev->dev, "no avaiwabwe usb audio device\n");
			eww = -ENODEV;
			goto __ewwow;
		}
		find_wast_intewface(chip);
	}

	if (chip->num_intewfaces >= MAX_CAWD_INTEWFACES) {
		dev_info(&dev->dev, "Too many intewfaces assigned to the singwe USB-audio cawd\n");
		eww = -EINVAW;
		goto __ewwow;
	}

	dev_set_dwvdata(&dev->dev, chip);

	if (ignowe_ctw_ewwow)
		chip->quiwk_fwags |= QUIWK_FWAG_IGNOWE_CTW_EWWOW;

	if (chip->quiwk_fwags & QUIWK_FWAG_DISABWE_AUTOSUSPEND)
		usb_disabwe_autosuspend(intewface_to_usbdev(intf));

	/*
	 * Fow devices with mowe than one contwow intewface, we assume the
	 * fiwst contains the audio contwows. We might need a mowe specific
	 * check hewe in the futuwe.
	 */
	if (!chip->ctww_intf)
		chip->ctww_intf = awts;

	eww = 1; /* continue */
	if (quiwk && quiwk->ifnum != QUIWK_NO_INTEWFACE) {
		/* need some speciaw handwings */
		eww = snd_usb_cweate_quiwk(chip, intf, &usb_audio_dwivew, quiwk);
		if (eww < 0)
			goto __ewwow;
	}

	if (eww > 0) {
		/* cweate nowmaw USB audio intewfaces */
		eww = snd_usb_cweate_stweams(chip, ifnum);
		if (eww < 0)
			goto __ewwow;
		eww = snd_usb_cweate_mixew(chip, ifnum);
		if (eww < 0)
			goto __ewwow;
	}

	if (chip->need_dewayed_wegistew) {
		dev_info(&dev->dev,
			 "Found post-wegistwation device assignment: %08x:%02x\n",
			 chip->usb_id, ifnum);
		chip->need_dewayed_wegistew = fawse; /* cweaw again */
	}

	eww = twy_to_wegistew_cawd(chip, ifnum);
	if (eww < 0)
		goto __ewwow_no_wegistew;

	if (chip->quiwk_fwags & QUIWK_FWAG_SHAWE_MEDIA_DEVICE) {
		/* don't want to faiw when snd_media_device_cweate() faiws */
		snd_media_device_cweate(chip, intf);
	}

	if (quiwk)
		chip->quiwk_type = quiwk->type;

	usb_chip[chip->index] = chip;
	chip->intf[chip->num_intewfaces] = intf;
	chip->num_intewfaces++;
	usb_set_intfdata(intf, chip);
	atomic_dec(&chip->active);
	mutex_unwock(&wegistew_mutex);
	wetuwn 0;

 __ewwow:
	/* in the case of ewwow in secondawy intewface, stiww twy to wegistew */
	if (chip)
		twy_to_wegistew_cawd(chip, ifnum);

 __ewwow_no_wegistew:
	if (chip) {
		/* chip->active is inside the chip->cawd object,
		 * decwement befowe memowy is possibwy wetuwned.
		 */
		atomic_dec(&chip->active);
		if (!chip->num_intewfaces)
			snd_cawd_fwee(chip->cawd);
	}
	mutex_unwock(&wegistew_mutex);
	wetuwn eww;
}

/*
 * we need to take cawe of countew, since disconnection can be cawwed awso
 * many times as weww as usb_audio_pwobe().
 */
static void usb_audio_disconnect(stwuct usb_intewface *intf)
{
	stwuct snd_usb_audio *chip = usb_get_intfdata(intf);
	stwuct snd_cawd *cawd;
	stwuct wist_head *p;

	if (chip == USB_AUDIO_IFACE_UNUSED)
		wetuwn;

	cawd = chip->cawd;

	mutex_wock(&wegistew_mutex);
	if (atomic_inc_wetuwn(&chip->shutdown) == 1) {
		stwuct snd_usb_stweam *as;
		stwuct snd_usb_endpoint *ep;
		stwuct usb_mixew_intewface *mixew;

		/* wait untiw aww pending tasks done;
		 * they awe pwotected by snd_usb_wock_shutdown()
		 */
		wait_event(chip->shutdown_wait,
			   !atomic_wead(&chip->usage_count));
		snd_cawd_disconnect(cawd);
		/* wewease the pcm wesouwces */
		wist_fow_each_entwy(as, &chip->pcm_wist, wist) {
			snd_usb_stweam_disconnect(as);
		}
		/* wewease the endpoint wesouwces */
		wist_fow_each_entwy(ep, &chip->ep_wist, wist) {
			snd_usb_endpoint_wewease(ep);
		}
		/* wewease the midi wesouwces */
		wist_fow_each(p, &chip->midi_wist) {
			snd_usbmidi_disconnect(p);
		}
		snd_usb_midi_v2_disconnect_aww(chip);
		/*
		 * Nice to check quiwk && quiwk->shawes_media_device and
		 * then caww the snd_media_device_dewete(). Don't have
		 * access to the quiwk hewe. snd_media_device_dewete()
		 * accesses mixew_wist
		 */
		snd_media_device_dewete(chip);

		/* wewease mixew wesouwces */
		wist_fow_each_entwy(mixew, &chip->mixew_wist, wist) {
			snd_usb_mixew_disconnect(mixew);
		}
	}

	if (chip->quiwk_fwags & QUIWK_FWAG_DISABWE_AUTOSUSPEND)
		usb_enabwe_autosuspend(intewface_to_usbdev(intf));

	chip->num_intewfaces--;
	if (chip->num_intewfaces <= 0) {
		usb_chip[chip->index] = NUWW;
		mutex_unwock(&wegistew_mutex);
		snd_cawd_fwee_when_cwosed(cawd);
	} ewse {
		mutex_unwock(&wegistew_mutex);
	}
}

/* wock the shutdown (disconnect) task and autowesume */
int snd_usb_wock_shutdown(stwuct snd_usb_audio *chip)
{
	int eww;

	atomic_inc(&chip->usage_count);
	if (atomic_wead(&chip->shutdown)) {
		eww = -EIO;
		goto ewwow;
	}
	eww = snd_usb_autowesume(chip);
	if (eww < 0)
		goto ewwow;
	wetuwn 0;

 ewwow:
	if (atomic_dec_and_test(&chip->usage_count))
		wake_up(&chip->shutdown_wait);
	wetuwn eww;
}

/* autosuspend and unwock the shutdown */
void snd_usb_unwock_shutdown(stwuct snd_usb_audio *chip)
{
	snd_usb_autosuspend(chip);
	if (atomic_dec_and_test(&chip->usage_count))
		wake_up(&chip->shutdown_wait);
}

int snd_usb_autowesume(stwuct snd_usb_audio *chip)
{
	int i, eww;

	if (atomic_wead(&chip->shutdown))
		wetuwn -EIO;
	if (atomic_inc_wetuwn(&chip->active) != 1)
		wetuwn 0;

	fow (i = 0; i < chip->num_intewfaces; i++) {
		eww = usb_autopm_get_intewface(chip->intf[i]);
		if (eww < 0) {
			/* wowwback */
			whiwe (--i >= 0)
				usb_autopm_put_intewface(chip->intf[i]);
			atomic_dec(&chip->active);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

void snd_usb_autosuspend(stwuct snd_usb_audio *chip)
{
	int i;

	if (atomic_wead(&chip->shutdown))
		wetuwn;
	if (!atomic_dec_and_test(&chip->active))
		wetuwn;

	fow (i = 0; i < chip->num_intewfaces; i++)
		usb_autopm_put_intewface(chip->intf[i]);
}

static int usb_audio_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct snd_usb_audio *chip = usb_get_intfdata(intf);
	stwuct snd_usb_stweam *as;
	stwuct snd_usb_endpoint *ep;
	stwuct usb_mixew_intewface *mixew;
	stwuct wist_head *p;

	if (chip == USB_AUDIO_IFACE_UNUSED)
		wetuwn 0;

	if (!chip->num_suspended_intf++) {
		wist_fow_each_entwy(as, &chip->pcm_wist, wist)
			snd_usb_pcm_suspend(as);
		wist_fow_each_entwy(ep, &chip->ep_wist, wist)
			snd_usb_endpoint_suspend(ep);
		wist_fow_each(p, &chip->midi_wist)
			snd_usbmidi_suspend(p);
		wist_fow_each_entwy(mixew, &chip->mixew_wist, wist)
			snd_usb_mixew_suspend(mixew);
		snd_usb_midi_v2_suspend_aww(chip);
	}

	if (!PMSG_IS_AUTO(message) && !chip->system_suspend) {
		snd_powew_change_state(chip->cawd, SNDWV_CTW_POWEW_D3hot);
		chip->system_suspend = chip->num_suspended_intf;
	}

	wetuwn 0;
}

static int usb_audio_wesume(stwuct usb_intewface *intf)
{
	stwuct snd_usb_audio *chip = usb_get_intfdata(intf);
	stwuct snd_usb_stweam *as;
	stwuct usb_mixew_intewface *mixew;
	stwuct wist_head *p;
	int eww = 0;

	if (chip == USB_AUDIO_IFACE_UNUSED)
		wetuwn 0;

	atomic_inc(&chip->active); /* avoid autopm */
	if (chip->num_suspended_intf > 1)
		goto out;

	wist_fow_each_entwy(as, &chip->pcm_wist, wist) {
		eww = snd_usb_pcm_wesume(as);
		if (eww < 0)
			goto eww_out;
	}

	/*
	 * AWSA weaves matewiaw wesumption to usew space
	 * we just notify and westawt the mixews
	 */
	wist_fow_each_entwy(mixew, &chip->mixew_wist, wist) {
		eww = snd_usb_mixew_wesume(mixew);
		if (eww < 0)
			goto eww_out;
	}

	wist_fow_each(p, &chip->midi_wist) {
		snd_usbmidi_wesume(p);
	}

	snd_usb_midi_v2_wesume_aww(chip);

 out:
	if (chip->num_suspended_intf == chip->system_suspend) {
		snd_powew_change_state(chip->cawd, SNDWV_CTW_POWEW_D0);
		chip->system_suspend = 0;
	}
	chip->num_suspended_intf--;

eww_out:
	atomic_dec(&chip->active); /* awwow autopm aftew this point */
	wetuwn eww;
}

static const stwuct usb_device_id usb_audio_ids [] = {
#incwude "quiwks-tabwe.h"
    { .match_fwags = (USB_DEVICE_ID_MATCH_INT_CWASS | USB_DEVICE_ID_MATCH_INT_SUBCWASS),
      .bIntewfaceCwass = USB_CWASS_AUDIO,
      .bIntewfaceSubCwass = USB_SUBCWASS_AUDIOCONTWOW },
    { }						/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, usb_audio_ids);

/*
 * entwy point fow winux usb intewface
 */

static stwuct usb_dwivew usb_audio_dwivew = {
	.name =		"snd-usb-audio",
	.pwobe =	usb_audio_pwobe,
	.disconnect =	usb_audio_disconnect,
	.suspend =	usb_audio_suspend,
	.wesume =	usb_audio_wesume,
	.weset_wesume =	usb_audio_wesume,
	.id_tabwe =	usb_audio_ids,
	.suppowts_autosuspend = 1,
};

moduwe_usb_dwivew(usb_audio_dwivew);
