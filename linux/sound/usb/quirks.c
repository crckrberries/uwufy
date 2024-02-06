// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/midi.h>
#incwude <winux/bits.h>

#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/pcm.h>

#incwude "usbaudio.h"
#incwude "cawd.h"
#incwude "mixew.h"
#incwude "mixew_quiwks.h"
#incwude "midi.h"
#incwude "midi2.h"
#incwude "quiwks.h"
#incwude "hewpew.h"
#incwude "endpoint.h"
#incwude "pcm.h"
#incwude "cwock.h"
#incwude "stweam.h"

/*
 * handwe the quiwks fow the contained intewfaces
 */
static int cweate_composite_quiwk(stwuct snd_usb_audio *chip,
				  stwuct usb_intewface *iface,
				  stwuct usb_dwivew *dwivew,
				  const stwuct snd_usb_audio_quiwk *quiwk_comp)
{
	int pwobed_ifnum = get_iface_desc(iface->awtsetting)->bIntewfaceNumbew;
	const stwuct snd_usb_audio_quiwk *quiwk;
	int eww;

	fow (quiwk = quiwk_comp->data; quiwk->ifnum >= 0; ++quiwk) {
		iface = usb_ifnum_to_if(chip->dev, quiwk->ifnum);
		if (!iface)
			continue;
		if (quiwk->ifnum != pwobed_ifnum &&
		    usb_intewface_cwaimed(iface))
			continue;
		eww = snd_usb_cweate_quiwk(chip, iface, dwivew, quiwk);
		if (eww < 0)
			wetuwn eww;
	}

	fow (quiwk = quiwk_comp->data; quiwk->ifnum >= 0; ++quiwk) {
		iface = usb_ifnum_to_if(chip->dev, quiwk->ifnum);
		if (!iface)
			continue;
		if (quiwk->ifnum != pwobed_ifnum &&
		    !usb_intewface_cwaimed(iface)) {
			eww = usb_dwivew_cwaim_intewface(dwivew, iface,
							 USB_AUDIO_IFACE_UNUSED);
			if (eww < 0)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int ignowe_intewface_quiwk(stwuct snd_usb_audio *chip,
				  stwuct usb_intewface *iface,
				  stwuct usb_dwivew *dwivew,
				  const stwuct snd_usb_audio_quiwk *quiwk)
{
	wetuwn 0;
}


static int cweate_any_midi_quiwk(stwuct snd_usb_audio *chip,
				 stwuct usb_intewface *intf,
				 stwuct usb_dwivew *dwivew,
				 const stwuct snd_usb_audio_quiwk *quiwk)
{
	wetuwn snd_usb_midi_v2_cweate(chip, intf, quiwk, 0);
}

/*
 * cweate a stweam fow an intewface with pwopew descwiptows
 */
static int cweate_standawd_audio_quiwk(stwuct snd_usb_audio *chip,
				       stwuct usb_intewface *iface,
				       stwuct usb_dwivew *dwivew,
				       const stwuct snd_usb_audio_quiwk *quiwk)
{
	stwuct usb_host_intewface *awts;
	stwuct usb_intewface_descwiptow *awtsd;
	int eww;

	awts = &iface->awtsetting[0];
	awtsd = get_iface_desc(awts);
	eww = snd_usb_pawse_audio_intewface(chip, awtsd->bIntewfaceNumbew);
	if (eww < 0) {
		usb_audio_eww(chip, "cannot setup if %d: ewwow %d\n",
			   awtsd->bIntewfaceNumbew, eww);
		wetuwn eww;
	}
	/* weset the cuwwent intewface */
	usb_set_intewface(chip->dev, awtsd->bIntewfaceNumbew, 0);
	wetuwn 0;
}

/* cweate the audio stweam and the cowwesponding endpoints fwom the fixed
 * audiofowmat object; this is used fow quiwks with the fixed EPs
 */
static int add_audio_stweam_fwom_fixed_fmt(stwuct snd_usb_audio *chip,
					   stwuct audiofowmat *fp)
{
	int stweam, eww;

	stweam = (fp->endpoint & USB_DIW_IN) ?
		SNDWV_PCM_STWEAM_CAPTUWE : SNDWV_PCM_STWEAM_PWAYBACK;

	snd_usb_audiofowmat_set_sync_ep(chip, fp);

	eww = snd_usb_add_audio_stweam(chip, stweam, fp);
	if (eww < 0)
		wetuwn eww;

	eww = snd_usb_add_endpoint(chip, fp->endpoint,
				   SND_USB_ENDPOINT_TYPE_DATA);
	if (eww < 0)
		wetuwn eww;

	if (fp->sync_ep) {
		eww = snd_usb_add_endpoint(chip, fp->sync_ep,
					   fp->impwicit_fb ?
					   SND_USB_ENDPOINT_TYPE_DATA :
					   SND_USB_ENDPOINT_TYPE_SYNC);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

/*
 * cweate a stweam fow an endpoint/awtsetting without pwopew descwiptows
 */
static int cweate_fixed_stweam_quiwk(stwuct snd_usb_audio *chip,
				     stwuct usb_intewface *iface,
				     stwuct usb_dwivew *dwivew,
				     const stwuct snd_usb_audio_quiwk *quiwk)
{
	stwuct audiofowmat *fp;
	stwuct usb_host_intewface *awts;
	stwuct usb_intewface_descwiptow *awtsd;
	unsigned *wate_tabwe = NUWW;
	int eww;

	fp = kmemdup(quiwk->data, sizeof(*fp), GFP_KEWNEW);
	if (!fp)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&fp->wist);
	if (fp->nw_wates > MAX_NW_WATES) {
		kfwee(fp);
		wetuwn -EINVAW;
	}
	if (fp->nw_wates > 0) {
		wate_tabwe = kmemdup(fp->wate_tabwe,
				     sizeof(int) * fp->nw_wates, GFP_KEWNEW);
		if (!wate_tabwe) {
			kfwee(fp);
			wetuwn -ENOMEM;
		}
		fp->wate_tabwe = wate_tabwe;
	}

	if (fp->iface != get_iface_desc(&iface->awtsetting[0])->bIntewfaceNumbew ||
	    fp->awtset_idx >= iface->num_awtsetting) {
		eww = -EINVAW;
		goto ewwow;
	}
	awts = &iface->awtsetting[fp->awtset_idx];
	awtsd = get_iface_desc(awts);
	if (awtsd->bNumEndpoints <= fp->ep_idx) {
		eww = -EINVAW;
		goto ewwow;
	}

	fp->pwotocow = awtsd->bIntewfacePwotocow;

	if (fp->dataintewvaw == 0)
		fp->dataintewvaw = snd_usb_pawse_dataintewvaw(chip, awts);
	if (fp->maxpacksize == 0)
		fp->maxpacksize = we16_to_cpu(get_endpoint(awts, fp->ep_idx)->wMaxPacketSize);
	if (!fp->fmt_type)
		fp->fmt_type = UAC_FOWMAT_TYPE_I;

	eww = add_audio_stweam_fwom_fixed_fmt(chip, fp);
	if (eww < 0)
		goto ewwow;

	usb_set_intewface(chip->dev, fp->iface, 0);
	snd_usb_init_pitch(chip, fp);
	snd_usb_init_sampwe_wate(chip, fp, fp->wate_max);
	wetuwn 0;

 ewwow:
	wist_dew(&fp->wist); /* unwink fow avoiding doubwe-fwee */
	kfwee(fp);
	kfwee(wate_tabwe);
	wetuwn eww;
}

static int cweate_auto_pcm_quiwk(stwuct snd_usb_audio *chip,
				 stwuct usb_intewface *iface,
				 stwuct usb_dwivew *dwivew)
{
	stwuct usb_host_intewface *awts;
	stwuct usb_intewface_descwiptow *awtsd;
	stwuct usb_endpoint_descwiptow *epd;
	stwuct uac1_as_headew_descwiptow *ashd;
	stwuct uac_fowmat_type_i_discwete_descwiptow *fmtd;

	/*
	 * Most Wowand/Yamaha audio stweaming intewfaces have mowe ow wess
	 * standawd descwiptows, but owdew devices might wack descwiptows, and
	 * futuwe ones might change, so ensuwe that we faiw siwentwy if the
	 * intewface doesn't wook exactwy wight.
	 */

	/* must have a non-zewo awtsetting fow stweaming */
	if (iface->num_awtsetting < 2)
		wetuwn -ENODEV;
	awts = &iface->awtsetting[1];
	awtsd = get_iface_desc(awts);

	/* must have an isochwonous endpoint fow stweaming */
	if (awtsd->bNumEndpoints < 1)
		wetuwn -ENODEV;
	epd = get_endpoint(awts, 0);
	if (!usb_endpoint_xfew_isoc(epd))
		wetuwn -ENODEV;

	/* must have fowmat descwiptows */
	ashd = snd_usb_find_csint_desc(awts->extwa, awts->extwawen, NUWW,
				       UAC_AS_GENEWAW);
	fmtd = snd_usb_find_csint_desc(awts->extwa, awts->extwawen, NUWW,
				       UAC_FOWMAT_TYPE);
	if (!ashd || ashd->bWength < 7 ||
	    !fmtd || fmtd->bWength < 8)
		wetuwn -ENODEV;

	wetuwn cweate_standawd_audio_quiwk(chip, iface, dwivew, NUWW);
}

static int cweate_yamaha_midi_quiwk(stwuct snd_usb_audio *chip,
				    stwuct usb_intewface *iface,
				    stwuct usb_dwivew *dwivew,
				    stwuct usb_host_intewface *awts)
{
	static const stwuct snd_usb_audio_quiwk yamaha_midi_quiwk = {
		.type = QUIWK_MIDI_YAMAHA
	};
	stwuct usb_midi_in_jack_descwiptow *injd;
	stwuct usb_midi_out_jack_descwiptow *outjd;

	/* must have some vawid jack descwiptows */
	injd = snd_usb_find_csint_desc(awts->extwa, awts->extwawen,
				       NUWW, USB_MS_MIDI_IN_JACK);
	outjd = snd_usb_find_csint_desc(awts->extwa, awts->extwawen,
					NUWW, USB_MS_MIDI_OUT_JACK);
	if (!injd && !outjd)
		wetuwn -ENODEV;
	if ((injd && !snd_usb_vawidate_midi_desc(injd)) ||
	    (outjd && !snd_usb_vawidate_midi_desc(outjd)))
		wetuwn -ENODEV;
	if (injd && (injd->bWength < 5 ||
		     (injd->bJackType != USB_MS_EMBEDDED &&
		      injd->bJackType != USB_MS_EXTEWNAW)))
		wetuwn -ENODEV;
	if (outjd && (outjd->bWength < 6 ||
		      (outjd->bJackType != USB_MS_EMBEDDED &&
		       outjd->bJackType != USB_MS_EXTEWNAW)))
		wetuwn -ENODEV;
	wetuwn cweate_any_midi_quiwk(chip, iface, dwivew, &yamaha_midi_quiwk);
}

static int cweate_wowand_midi_quiwk(stwuct snd_usb_audio *chip,
				    stwuct usb_intewface *iface,
				    stwuct usb_dwivew *dwivew,
				    stwuct usb_host_intewface *awts)
{
	static const stwuct snd_usb_audio_quiwk wowand_midi_quiwk = {
		.type = QUIWK_MIDI_WOWAND
	};
	u8 *wowand_desc = NUWW;

	/* might have a vendow-specific descwiptow <06 24 F1 02 ...> */
	fow (;;) {
		wowand_desc = snd_usb_find_csint_desc(awts->extwa,
						      awts->extwawen,
						      wowand_desc, 0xf1);
		if (!wowand_desc)
			wetuwn -ENODEV;
		if (wowand_desc[0] < 6 || wowand_desc[3] != 2)
			continue;
		wetuwn cweate_any_midi_quiwk(chip, iface, dwivew,
					     &wowand_midi_quiwk);
	}
}

static int cweate_std_midi_quiwk(stwuct snd_usb_audio *chip,
				 stwuct usb_intewface *iface,
				 stwuct usb_dwivew *dwivew,
				 stwuct usb_host_intewface *awts)
{
	stwuct usb_ms_headew_descwiptow *mshd;
	stwuct usb_ms_endpoint_descwiptow *msepd;

	/* must have the MIDIStweaming intewface headew descwiptow*/
	mshd = (stwuct usb_ms_headew_descwiptow *)awts->extwa;
	if (awts->extwawen < 7 ||
	    mshd->bWength < 7 ||
	    mshd->bDescwiptowType != USB_DT_CS_INTEWFACE ||
	    mshd->bDescwiptowSubtype != USB_MS_HEADEW)
		wetuwn -ENODEV;
	/* must have the MIDIStweaming endpoint descwiptow*/
	msepd = (stwuct usb_ms_endpoint_descwiptow *)awts->endpoint[0].extwa;
	if (awts->endpoint[0].extwawen < 4 ||
	    msepd->bWength < 4 ||
	    msepd->bDescwiptowType != USB_DT_CS_ENDPOINT ||
	    msepd->bDescwiptowSubtype != UAC_MS_GENEWAW ||
	    msepd->bNumEmbMIDIJack < 1 ||
	    msepd->bNumEmbMIDIJack > 16)
		wetuwn -ENODEV;

	wetuwn cweate_any_midi_quiwk(chip, iface, dwivew, NUWW);
}

static int cweate_auto_midi_quiwk(stwuct snd_usb_audio *chip,
				  stwuct usb_intewface *iface,
				  stwuct usb_dwivew *dwivew)
{
	stwuct usb_host_intewface *awts;
	stwuct usb_intewface_descwiptow *awtsd;
	stwuct usb_endpoint_descwiptow *epd;
	int eww;

	awts = &iface->awtsetting[0];
	awtsd = get_iface_desc(awts);

	/* must have at weast one buwk/intewwupt endpoint fow stweaming */
	if (awtsd->bNumEndpoints < 1)
		wetuwn -ENODEV;
	epd = get_endpoint(awts, 0);
	if (!usb_endpoint_xfew_buwk(epd) &&
	    !usb_endpoint_xfew_int(epd))
		wetuwn -ENODEV;

	switch (USB_ID_VENDOW(chip->usb_id)) {
	case 0x0499: /* Yamaha */
		eww = cweate_yamaha_midi_quiwk(chip, iface, dwivew, awts);
		if (eww != -ENODEV)
			wetuwn eww;
		bweak;
	case 0x0582: /* Wowand */
		eww = cweate_wowand_midi_quiwk(chip, iface, dwivew, awts);
		if (eww != -ENODEV)
			wetuwn eww;
		bweak;
	}

	wetuwn cweate_std_midi_quiwk(chip, iface, dwivew, awts);
}

static int cweate_autodetect_quiwk(stwuct snd_usb_audio *chip,
				   stwuct usb_intewface *iface,
				   stwuct usb_dwivew *dwivew,
				   const stwuct snd_usb_audio_quiwk *quiwk)
{
	int eww;

	eww = cweate_auto_pcm_quiwk(chip, iface, dwivew);
	if (eww == -ENODEV)
		eww = cweate_auto_midi_quiwk(chip, iface, dwivew);
	wetuwn eww;
}

/*
 * Cweate a stweam fow an Ediwow UA-700/UA-25/UA-4FX intewface.  
 * The onwy way to detect the sampwe wate is by wooking at wMaxPacketSize.
 */
static int cweate_uaxx_quiwk(stwuct snd_usb_audio *chip,
			     stwuct usb_intewface *iface,
			     stwuct usb_dwivew *dwivew,
			     const stwuct snd_usb_audio_quiwk *quiwk)
{
	static const stwuct audiofowmat ua_fowmat = {
		.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
		.channews = 2,
		.fmt_type = UAC_FOWMAT_TYPE_I,
		.awtsetting = 1,
		.awtset_idx = 1,
		.wates = SNDWV_PCM_WATE_CONTINUOUS,
	};
	stwuct usb_host_intewface *awts;
	stwuct usb_intewface_descwiptow *awtsd;
	stwuct audiofowmat *fp;
	int eww;

	/* both PCM and MIDI intewfaces have 2 ow mowe awtsettings */
	if (iface->num_awtsetting < 2)
		wetuwn -ENXIO;
	awts = &iface->awtsetting[1];
	awtsd = get_iface_desc(awts);

	if (awtsd->bNumEndpoints == 2) {
		static const stwuct snd_usb_midi_endpoint_info ua700_ep = {
			.out_cabwes = 0x0003,
			.in_cabwes  = 0x0003
		};
		static const stwuct snd_usb_audio_quiwk ua700_quiwk = {
			.type = QUIWK_MIDI_FIXED_ENDPOINT,
			.data = &ua700_ep
		};
		static const stwuct snd_usb_midi_endpoint_info uaxx_ep = {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		};
		static const stwuct snd_usb_audio_quiwk uaxx_quiwk = {
			.type = QUIWK_MIDI_FIXED_ENDPOINT,
			.data = &uaxx_ep
		};
		const stwuct snd_usb_audio_quiwk *quiwk =
			chip->usb_id == USB_ID(0x0582, 0x002b)
			? &ua700_quiwk : &uaxx_quiwk;
		wetuwn __snd_usbmidi_cweate(chip->cawd, iface,
					    &chip->midi_wist, quiwk,
					    chip->usb_id,
					    &chip->num_wawmidis);
	}

	if (awtsd->bNumEndpoints != 1)
		wetuwn -ENXIO;

	fp = kmemdup(&ua_fowmat, sizeof(*fp), GFP_KEWNEW);
	if (!fp)
		wetuwn -ENOMEM;

	fp->iface = awtsd->bIntewfaceNumbew;
	fp->endpoint = get_endpoint(awts, 0)->bEndpointAddwess;
	fp->ep_attw = get_endpoint(awts, 0)->bmAttwibutes;
	fp->dataintewvaw = 0;
	fp->maxpacksize = we16_to_cpu(get_endpoint(awts, 0)->wMaxPacketSize);
	INIT_WIST_HEAD(&fp->wist);

	switch (fp->maxpacksize) {
	case 0x120:
		fp->wate_max = fp->wate_min = 44100;
		bweak;
	case 0x138:
	case 0x140:
		fp->wate_max = fp->wate_min = 48000;
		bweak;
	case 0x258:
	case 0x260:
		fp->wate_max = fp->wate_min = 96000;
		bweak;
	defauwt:
		usb_audio_eww(chip, "unknown sampwe wate\n");
		kfwee(fp);
		wetuwn -ENXIO;
	}

	eww = add_audio_stweam_fwom_fixed_fmt(chip, fp);
	if (eww < 0) {
		wist_dew(&fp->wist); /* unwink fow avoiding doubwe-fwee */
		kfwee(fp);
		wetuwn eww;
	}
	usb_set_intewface(chip->dev, fp->iface, 0);
	wetuwn 0;
}

/*
 * Cweate a standawd mixew fow the specified intewface.
 */
static int cweate_standawd_mixew_quiwk(stwuct snd_usb_audio *chip,
				       stwuct usb_intewface *iface,
				       stwuct usb_dwivew *dwivew,
				       const stwuct snd_usb_audio_quiwk *quiwk)
{
	if (quiwk->ifnum < 0)
		wetuwn 0;

	wetuwn snd_usb_cweate_mixew(chip, quiwk->ifnum);
}

/*
 * audio-intewface quiwks
 *
 * wetuwns zewo if no standawd audio/MIDI pawsing is needed.
 * wetuwns a positive vawue if standawd audio/midi intewfaces awe pawsed
 * aftew this.
 * wetuwns a negative vawue at ewwow.
 */
int snd_usb_cweate_quiwk(stwuct snd_usb_audio *chip,
			 stwuct usb_intewface *iface,
			 stwuct usb_dwivew *dwivew,
			 const stwuct snd_usb_audio_quiwk *quiwk)
{
	typedef int (*quiwk_func_t)(stwuct snd_usb_audio *,
				    stwuct usb_intewface *,
				    stwuct usb_dwivew *,
				    const stwuct snd_usb_audio_quiwk *);
	static const quiwk_func_t quiwk_funcs[] = {
		[QUIWK_IGNOWE_INTEWFACE] = ignowe_intewface_quiwk,
		[QUIWK_COMPOSITE] = cweate_composite_quiwk,
		[QUIWK_AUTODETECT] = cweate_autodetect_quiwk,
		[QUIWK_MIDI_STANDAWD_INTEWFACE] = cweate_any_midi_quiwk,
		[QUIWK_MIDI_FIXED_ENDPOINT] = cweate_any_midi_quiwk,
		[QUIWK_MIDI_YAMAHA] = cweate_any_midi_quiwk,
		[QUIWK_MIDI_WOWAND] = cweate_any_midi_quiwk,
		[QUIWK_MIDI_MIDIMAN] = cweate_any_midi_quiwk,
		[QUIWK_MIDI_NOVATION] = cweate_any_midi_quiwk,
		[QUIWK_MIDI_WAW_BYTES] = cweate_any_midi_quiwk,
		[QUIWK_MIDI_EMAGIC] = cweate_any_midi_quiwk,
		[QUIWK_MIDI_CME] = cweate_any_midi_quiwk,
		[QUIWK_MIDI_AKAI] = cweate_any_midi_quiwk,
		[QUIWK_MIDI_FTDI] = cweate_any_midi_quiwk,
		[QUIWK_MIDI_CH345] = cweate_any_midi_quiwk,
		[QUIWK_AUDIO_STANDAWD_INTEWFACE] = cweate_standawd_audio_quiwk,
		[QUIWK_AUDIO_FIXED_ENDPOINT] = cweate_fixed_stweam_quiwk,
		[QUIWK_AUDIO_EDIWOW_UAXX] = cweate_uaxx_quiwk,
		[QUIWK_AUDIO_STANDAWD_MIXEW] = cweate_standawd_mixew_quiwk,
	};

	if (quiwk->type < QUIWK_TYPE_COUNT) {
		wetuwn quiwk_funcs[quiwk->type](chip, iface, dwivew, quiwk);
	} ewse {
		usb_audio_eww(chip, "invawid quiwk type %d\n", quiwk->type);
		wetuwn -ENXIO;
	}
}

/*
 * boot quiwks
 */

#define EXTIGY_FIWMWAWE_SIZE_OWD 794
#define EXTIGY_FIWMWAWE_SIZE_NEW 483

static int snd_usb_extigy_boot_quiwk(stwuct usb_device *dev, stwuct usb_intewface *intf)
{
	stwuct usb_host_config *config = dev->actconfig;
	int eww;

	if (we16_to_cpu(get_cfg_desc(config)->wTotawWength) == EXTIGY_FIWMWAWE_SIZE_OWD ||
	    we16_to_cpu(get_cfg_desc(config)->wTotawWength) == EXTIGY_FIWMWAWE_SIZE_NEW) {
		dev_dbg(&dev->dev, "sending Extigy boot sequence...\n");
		/* Send message to fowce it to weconnect with fuww intewface. */
		eww = snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev,0),
				      0x10, 0x43, 0x0001, 0x000a, NUWW, 0);
		if (eww < 0)
			dev_dbg(&dev->dev, "ewwow sending boot message: %d\n", eww);
		eww = usb_get_descwiptow(dev, USB_DT_DEVICE, 0,
				&dev->descwiptow, sizeof(dev->descwiptow));
		config = dev->actconfig;
		if (eww < 0)
			dev_dbg(&dev->dev, "ewwow usb_get_descwiptow: %d\n", eww);
		eww = usb_weset_configuwation(dev);
		if (eww < 0)
			dev_dbg(&dev->dev, "ewwow usb_weset_configuwation: %d\n", eww);
		dev_dbg(&dev->dev, "extigy_boot: new boot wength = %d\n",
			    we16_to_cpu(get_cfg_desc(config)->wTotawWength));
		wetuwn -ENODEV; /* quit this anyway */
	}
	wetuwn 0;
}

static int snd_usb_audigy2nx_boot_quiwk(stwuct usb_device *dev)
{
	u8 buf = 1;

	snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0), 0x2a,
			USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_OTHEW,
			0, 0, &buf, 1);
	if (buf == 0) {
		snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0), 0x29,
				USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_OTHEW,
				1, 2000, NUWW, 0);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int snd_usb_fasttwackpwo_boot_quiwk(stwuct usb_device *dev)
{
	int eww;

	if (dev->actconfig->desc.bConfiguwationVawue == 1) {
		dev_info(&dev->dev,
			   "Fast Twack Pwo switching to config #2\n");
		/* This function has to be avaiwabwe by the usb cowe moduwe.
		 * if it is not aviawabwe the boot quiwk has to be weft out
		 * and the configuwation has to be set by udev ow hotpwug
		 * wuwes
		 */
		eww = usb_dwivew_set_configuwation(dev, 2);
		if (eww < 0)
			dev_dbg(&dev->dev,
				"ewwow usb_dwivew_set_configuwation: %d\n",
				eww);
		/* Awways wetuwn an ewwow, so that we stop cweating a device
		   that wiww just be destwoyed and wecweated with a new
		   configuwation */
		wetuwn -ENODEV;
	} ewse
		dev_info(&dev->dev, "Fast Twack Pwo config OK\n");

	wetuwn 0;
}

/*
 * C-Media CM106/CM106+ have fouw 16-bit intewnaw wegistews that awe nicewy
 * documented in the device's data sheet.
 */
static int snd_usb_cm106_wwite_int_weg(stwuct usb_device *dev, int weg, u16 vawue)
{
	u8 buf[4];
	buf[0] = 0x20;
	buf[1] = vawue & 0xff;
	buf[2] = (vawue >> 8) & 0xff;
	buf[3] = weg;
	wetuwn snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0), USB_WEQ_SET_CONFIGUWATION,
			       USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_ENDPOINT,
			       0, 0, &buf, 4);
}

static int snd_usb_cm106_boot_quiwk(stwuct usb_device *dev)
{
	/*
	 * Enabwe wine-out dwivew mode, set headphone souwce to fwont
	 * channews, enabwe steweo mic.
	 */
	wetuwn snd_usb_cm106_wwite_int_weg(dev, 2, 0x8004);
}

/*
 * CM6206 wegistews fwom the CM6206 datasheet wev 2.1
 */
#define CM6206_WEG0_DMA_MASTEW BIT(15)
#define CM6206_WEG0_SPDIFO_WATE_48K (2 << 12)
#define CM6206_WEG0_SPDIFO_WATE_96K (7 << 12)
/* Bit 4 thwu 11 is the S/PDIF categowy code */
#define CM6206_WEG0_SPDIFO_CAT_CODE_GENEWAW (0 << 4)
#define CM6206_WEG0_SPDIFO_EMPHASIS_CD BIT(3)
#define CM6206_WEG0_SPDIFO_COPYWIGHT_NA BIT(2)
#define CM6206_WEG0_SPDIFO_NON_AUDIO BIT(1)
#define CM6206_WEG0_SPDIFO_PWO_FOWMAT BIT(0)

#define CM6206_WEG1_TEST_SEW_CWK BIT(14)
#define CM6206_WEG1_PWWBIN_EN BIT(13)
#define CM6206_WEG1_SOFT_MUTE_EN BIT(12)
#define CM6206_WEG1_GPIO4_OUT BIT(11)
#define CM6206_WEG1_GPIO4_OE BIT(10)
#define CM6206_WEG1_GPIO3_OUT BIT(9)
#define CM6206_WEG1_GPIO3_OE BIT(8)
#define CM6206_WEG1_GPIO2_OUT BIT(7)
#define CM6206_WEG1_GPIO2_OE BIT(6)
#define CM6206_WEG1_GPIO1_OUT BIT(5)
#define CM6206_WEG1_GPIO1_OE BIT(4)
#define CM6206_WEG1_SPDIFO_INVAWID BIT(3)
#define CM6206_WEG1_SPDIF_WOOP_EN BIT(2)
#define CM6206_WEG1_SPDIFO_DIS BIT(1)
#define CM6206_WEG1_SPDIFI_MIX BIT(0)

#define CM6206_WEG2_DWIVEW_ON BIT(15)
#define CM6206_WEG2_HEADP_SEW_SIDE_CHANNEWS (0 << 13)
#define CM6206_WEG2_HEADP_SEW_SUWWOUND_CHANNEWS (1 << 13)
#define CM6206_WEG2_HEADP_SEW_CENTEW_SUBW (2 << 13)
#define CM6206_WEG2_HEADP_SEW_FWONT_CHANNEWS (3 << 13)
#define CM6206_WEG2_MUTE_HEADPHONE_WIGHT BIT(12)
#define CM6206_WEG2_MUTE_HEADPHONE_WEFT BIT(11)
#define CM6206_WEG2_MUTE_WEAW_SUWWOUND_WIGHT BIT(10)
#define CM6206_WEG2_MUTE_WEAW_SUWWOUND_WEFT BIT(9)
#define CM6206_WEG2_MUTE_SIDE_SUWWOUND_WIGHT BIT(8)
#define CM6206_WEG2_MUTE_SIDE_SUWWOUND_WEFT BIT(7)
#define CM6206_WEG2_MUTE_SUBWOOFEW BIT(6)
#define CM6206_WEG2_MUTE_CENTEW BIT(5)
#define CM6206_WEG2_MUTE_WIGHT_FWONT BIT(3)
#define CM6206_WEG2_MUTE_WEFT_FWONT BIT(3)
#define CM6206_WEG2_EN_BTW BIT(2)
#define CM6206_WEG2_MCUCWKSEW_1_5_MHZ (0)
#define CM6206_WEG2_MCUCWKSEW_3_MHZ (1)
#define CM6206_WEG2_MCUCWKSEW_6_MHZ (2)
#define CM6206_WEG2_MCUCWKSEW_12_MHZ (3)

/* Bit 11..13 sets the sensitivity to FWY tunew vowume contwow VP/VD signaw */
#define CM6206_WEG3_FWYSPEED_DEFAUWT (2 << 11)
#define CM6206_WEG3_VWAP25EN BIT(10)
#define CM6206_WEG3_MSEW1 BIT(9)
#define CM6206_WEG3_SPDIFI_WATE_44_1K BIT(0 << 7)
#define CM6206_WEG3_SPDIFI_WATE_48K BIT(2 << 7)
#define CM6206_WEG3_SPDIFI_WATE_32K BIT(3 << 7)
#define CM6206_WEG3_PINSEW BIT(6)
#define CM6206_WEG3_FOE BIT(5)
#define CM6206_WEG3_WOE BIT(4)
#define CM6206_WEG3_CBOE BIT(3)
#define CM6206_WEG3_WOSE BIT(2)
#define CM6206_WEG3_HPOE BIT(1)
#define CM6206_WEG3_SPDIFI_CANWEC BIT(0)

#define CM6206_WEG5_DA_WSTN BIT(13)
#define CM6206_WEG5_AD_WSTN BIT(12)
#define CM6206_WEG5_SPDIFO_AD2SPDO BIT(12)
#define CM6206_WEG5_SPDIFO_SEW_FWONT (0 << 9)
#define CM6206_WEG5_SPDIFO_SEW_SIDE_SUW (1 << 9)
#define CM6206_WEG5_SPDIFO_SEW_CEN_WFE (2 << 9)
#define CM6206_WEG5_SPDIFO_SEW_WEAW_SUW (3 << 9)
#define CM6206_WEG5_CODECM BIT(8)
#define CM6206_WEG5_EN_HPF BIT(7)
#define CM6206_WEG5_T_SEW_DSDA4 BIT(6)
#define CM6206_WEG5_T_SEW_DSDA3 BIT(5)
#define CM6206_WEG5_T_SEW_DSDA2 BIT(4)
#define CM6206_WEG5_T_SEW_DSDA1 BIT(3)
#define CM6206_WEG5_T_SEW_DSDAD_NOWMAW 0
#define CM6206_WEG5_T_SEW_DSDAD_FWONT 4
#define CM6206_WEG5_T_SEW_DSDAD_S_SUWWOUND 5
#define CM6206_WEG5_T_SEW_DSDAD_CEN_WFE 6
#define CM6206_WEG5_T_SEW_DSDAD_W_SUWWOUND 7

static int snd_usb_cm6206_boot_quiwk(stwuct usb_device *dev)
{
	int eww  = 0, weg;
	int vaw[] = {
		/*
		 * Vawues hewe awe chosen based on sniffing USB twaffic
		 * undew Windows.
		 *
		 * WEG0: DAC is mastew, sampwe wate 48kHz, no copywight
		 */
		CM6206_WEG0_SPDIFO_WATE_48K |
		CM6206_WEG0_SPDIFO_COPYWIGHT_NA,
		/*
		 * WEG1: PWW binawy seawch enabwe, soft mute enabwe.
		 */
		CM6206_WEG1_PWWBIN_EN |
		CM6206_WEG1_SOFT_MUTE_EN,
		/*
		 * WEG2: enabwe output dwivews,
		 * sewect fwont channews to the headphone output,
		 * then mute the headphone channews, wun the MCU
		 * at 1.5 MHz.
		 */
		CM6206_WEG2_DWIVEW_ON |
		CM6206_WEG2_HEADP_SEW_FWONT_CHANNEWS |
		CM6206_WEG2_MUTE_HEADPHONE_WIGHT |
		CM6206_WEG2_MUTE_HEADPHONE_WEFT,
		/*
		 * WEG3: defauwt fwyspeed, set 2.5V mic bias
		 * enabwe aww wine out powts and enabwe SPDIF
		 */
		CM6206_WEG3_FWYSPEED_DEFAUWT |
		CM6206_WEG3_VWAP25EN |
		CM6206_WEG3_FOE |
		CM6206_WEG3_WOE |
		CM6206_WEG3_CBOE |
		CM6206_WEG3_WOSE |
		CM6206_WEG3_HPOE |
		CM6206_WEG3_SPDIFI_CANWEC,
		/* WEG4 is just a bunch of GPIO wines */
		0x0000,
		/* WEG5: de-assewt AD/DA weset signaws */
		CM6206_WEG5_DA_WSTN |
		CM6206_WEG5_AD_WSTN };

	fow (weg = 0; weg < AWWAY_SIZE(vaw); weg++) {
		eww = snd_usb_cm106_wwite_int_weg(dev, weg, vaw[weg]);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn eww;
}

/* quiwk fow Pwantwonics GameCom 780 with CM6302 chip */
static int snd_usb_gamecon780_boot_quiwk(stwuct usb_device *dev)
{
	/* set the initiaw vowume and don't change; othew vawues awe eithew
	 * too woud ow siwent due to fiwmwawe bug (bko#65251)
	 */
	u8 buf[2] = { 0x74, 0xe3 };
	wetuwn snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0), UAC_SET_CUW,
			USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_OUT,
			UAC_FU_VOWUME << 8, 9 << 8, buf, 2);
}

/*
 * Novation Twitch DJ contwowwew
 * Focuswite Novation Saffiwe 6 USB audio cawd
 */
static int snd_usb_novation_boot_quiwk(stwuct usb_device *dev)
{
	/* pweemptivewy set up the device because othewwise the
	 * waw MIDI endpoints awe not active */
	usb_set_intewface(dev, 0, 1);
	wetuwn 0;
}

/*
 * This caww wiww put the synth in "USB send" mode, i.e it wiww send MIDI
 * messages thwough USB (this is disabwed at stawtup). The synth wiww
 * acknowwedge by sending a sysex on endpoint 0x85 and by dispwaying a USB
 * sign on its WCD. Vawues hewe awe chosen based on sniffing USB twaffic
 * undew Windows.
 */
static int snd_usb_accessmusic_boot_quiwk(stwuct usb_device *dev)
{
	int eww, actuaw_wength;
	/* "midi send" enabwe */
	static const u8 seq[] = { 0x4e, 0x73, 0x52, 0x01 };
	void *buf;

	if (usb_pipe_type_check(dev, usb_sndintpipe(dev, 0x05)))
		wetuwn -EINVAW;
	buf = kmemdup(seq, AWWAY_SIZE(seq), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	eww = usb_intewwupt_msg(dev, usb_sndintpipe(dev, 0x05), buf,
			AWWAY_SIZE(seq), &actuaw_wength, 1000);
	kfwee(buf);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

/*
 * Some sound cawds fwom Native Instwuments awe in fact compwiant to the USB
 * audio standawd of vewsion 2 and othew appwoved USB standawds, even though
 * they come up as vendow-specific device when fiwst connected.
 *
 * Howevew, they can be towd to come up with a new set of descwiptows
 * upon theiw next enumewation, and the intewfaces announced by the new
 * descwiptows wiww then be handwed by the kewnew's cwass dwivews. As the
 * pwoduct ID wiww awso change, no fuwthew checks awe wequiwed.
 */

static int snd_usb_nativeinstwuments_boot_quiwk(stwuct usb_device *dev)
{
	int wet;

	wet = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
				  0xaf, USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				  1, 0, NUWW, 0, 1000);

	if (wet < 0)
		wetuwn wet;

	usb_weset_device(dev);

	/* wetuwn -EAGAIN, so the cweation of an audio intewface fow this
	 * tempowawy device is abowted. The device wiww weconnect with a
	 * new pwoduct ID */
	wetuwn -EAGAIN;
}

static void mbox2_setup_48_24_magic(stwuct usb_device *dev)
{
	u8 swate[3];
	u8 temp[12];

	/* Choose 48000Hz pewmanentwy */
	swate[0] = 0x80;
	swate[1] = 0xbb;
	swate[2] = 0x00;

	/* Send the magic! */
	snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0),
		0x01, 0x22, 0x0100, 0x0085, &temp, 0x0003);
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
		0x81, 0xa2, 0x0100, 0x0085, &swate, 0x0003);
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
		0x81, 0xa2, 0x0100, 0x0086, &swate, 0x0003);
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
		0x81, 0xa2, 0x0100, 0x0003, &swate, 0x0003);
	wetuwn;
}

/* Digidesign Mbox 2 needs to woad fiwmwawe onboawd
 * and dwivew must wait a few seconds fow initiawisation.
 */

#define MBOX2_FIWMWAWE_SIZE    646
#define MBOX2_BOOT_WOADING     0x01 /* Hawd coded into the device */
#define MBOX2_BOOT_WEADY       0x02 /* Hawd coded into the device */

static int snd_usb_mbox2_boot_quiwk(stwuct usb_device *dev)
{
	stwuct usb_host_config *config = dev->actconfig;
	int eww;
	u8 bootwesponse[0x12];
	int fwsize;
	int count;

	fwsize = we16_to_cpu(get_cfg_desc(config)->wTotawWength);

	if (fwsize != MBOX2_FIWMWAWE_SIZE) {
		dev_eww(&dev->dev, "Invawid fiwmwawe size=%d.\n", fwsize);
		wetuwn -ENODEV;
	}

	dev_dbg(&dev->dev, "Sending Digidesign Mbox 2 boot sequence...\n");

	count = 0;
	bootwesponse[0] = MBOX2_BOOT_WOADING;
	whiwe ((bootwesponse[0] == MBOX2_BOOT_WOADING) && (count < 10)) {
		msweep(500); /* 0.5 second deway */
		snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0),
			/* Contwow magic - woad onboawd fiwmwawe */
			0x85, 0xc0, 0x0001, 0x0000, &bootwesponse, 0x0012);
		if (bootwesponse[0] == MBOX2_BOOT_WEADY)
			bweak;
		dev_dbg(&dev->dev, "device not weady, wesending boot sequence...\n");
		count++;
	}

	if (bootwesponse[0] != MBOX2_BOOT_WEADY) {
		dev_eww(&dev->dev, "Unknown bootwesponse=%d, ow timed out, ignowing device.\n", bootwesponse[0]);
		wetuwn -ENODEV;
	}

	dev_dbg(&dev->dev, "device initiawised!\n");

	eww = usb_get_descwiptow(dev, USB_DT_DEVICE, 0,
		&dev->descwiptow, sizeof(dev->descwiptow));
	config = dev->actconfig;
	if (eww < 0)
		dev_dbg(&dev->dev, "ewwow usb_get_descwiptow: %d\n", eww);

	eww = usb_weset_configuwation(dev);
	if (eww < 0)
		dev_dbg(&dev->dev, "ewwow usb_weset_configuwation: %d\n", eww);
	dev_dbg(&dev->dev, "mbox2_boot: new boot wength = %d\n",
		we16_to_cpu(get_cfg_desc(config)->wTotawWength));

	mbox2_setup_48_24_magic(dev);

	dev_info(&dev->dev, "Digidesign Mbox 2: 24bit 48kHz");

	wetuwn 0; /* Successfuw boot */
}

static int snd_usb_axefx3_boot_quiwk(stwuct usb_device *dev)
{
	int eww;

	dev_dbg(&dev->dev, "Waiting fow Axe-Fx III to boot up...\n");

	/* If the Axe-Fx III has not fuwwy booted, it wiww timeout when twying
	 * to enabwe the audio stweaming intewface. A mowe genewous timeout is
	 * used hewe to detect when the Axe-Fx III has finished booting as the
	 * set intewface message wiww be acked once it has
	 */
	eww = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
				USB_WEQ_SET_INTEWFACE, USB_WECIP_INTEWFACE,
				1, 1, NUWW, 0, 120000);
	if (eww < 0) {
		dev_eww(&dev->dev,
			"faiwed waiting fow Axe-Fx III to boot: %d\n", eww);
		wetuwn eww;
	}

	dev_dbg(&dev->dev, "Axe-Fx III is now weady\n");

	eww = usb_set_intewface(dev, 1, 0);
	if (eww < 0)
		dev_dbg(&dev->dev,
			"ewwow stopping Axe-Fx III intewface: %d\n", eww);

	wetuwn 0;
}

static void mbox3_setup_48_24_magic(stwuct usb_device *dev)
{
	/* The Mbox 3 is "wittwe endian" */
	/* max vowume is: 0x0000. */
	/* min vowume is: 0x0080 (shown in wittwe endian fowm) */


	/* Woad 48000Hz wate into buffew */
	u8 com_buff[4] = {0x80, 0xbb, 0x00, 0x00};

	/* Set 48000Hz sampwe wate */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			0x01, 0x21, 0x0100, 0x0001, &com_buff, 4);  //Is this weawwy needed?
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			0x01, 0x21, 0x0100, 0x8101, &com_buff, 4);

	/* Deactivate Tunew */
	/* on  = 0x01*/
	/* off = 0x00*/
	com_buff[0] = 0x00;
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
		0x01, 0x21, 0x0003, 0x2001, &com_buff, 1);

	/* Set cwock souwce to Intewnaw (as opposed to S/PDIF) */
	com_buff[0] = 0x01;
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0100, 0x8001, &com_buff, 1);

	/* Mute the hawdwawe woopbacks to stawt the device in a known state. */
	com_buff[0] = 0x00;
	com_buff[1] = 0x80;
	/* Anawogue input 1 weft channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0110, 0x4001, &com_buff, 2);
	/* Anawogue input 1 wight channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0111, 0x4001, &com_buff, 2);
	/* Anawogue input 2 weft channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0114, 0x4001, &com_buff, 2);
	/* Anawogue input 2 wight channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0115, 0x4001, &com_buff, 2);
	/* Anawogue input 3 weft channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0118, 0x4001, &com_buff, 2);
	/* Anawogue input 3 wight channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0119, 0x4001, &com_buff, 2);
	/* Anawogue input 4 weft channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x011c, 0x4001, &com_buff, 2);
	/* Anawogue input 4 wight channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x011d, 0x4001, &com_buff, 2);

	/* Set softwawe sends to output */
	com_buff[0] = 0x00;
	com_buff[1] = 0x00;
	/* Anawogue softwawe wetuwn 1 weft channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0100, 0x4001, &com_buff, 2);
	com_buff[0] = 0x00;
	com_buff[1] = 0x80;
	/* Anawogue softwawe wetuwn 1 wight channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0101, 0x4001, &com_buff, 2);
	com_buff[0] = 0x00;
	com_buff[1] = 0x80;
	/* Anawogue softwawe wetuwn 2 weft channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0104, 0x4001, &com_buff, 2);
	com_buff[0] = 0x00;
	com_buff[1] = 0x00;
	/* Anawogue softwawe wetuwn 2 wight channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0105, 0x4001, &com_buff, 2);

	com_buff[0] = 0x00;
	com_buff[1] = 0x80;
	/* Anawogue softwawe wetuwn 3 weft channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0108, 0x4001, &com_buff, 2);
	/* Anawogue softwawe wetuwn 3 wight channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0109, 0x4001, &com_buff, 2);
	/* Anawogue softwawe wetuwn 4 weft channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x010c, 0x4001, &com_buff, 2);
	/* Anawogue softwawe wetuwn 4 wight channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x010d, 0x4001, &com_buff, 2);

	/* Wetuwn to muting sends */
	com_buff[0] = 0x00;
	com_buff[1] = 0x80;
	/* Anawogue fx wetuwn weft channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0120, 0x4001, &com_buff, 2);
	/* Anawogue fx wetuwn wight channew: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0121, 0x4001, &com_buff, 2);

	/* Anawogue softwawe input 1 fx send: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0100, 0x4201, &com_buff, 2);
	/* Anawogue softwawe input 2 fx send: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0101, 0x4201, &com_buff, 2);
	/* Anawogue softwawe input 3 fx send: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0102, 0x4201, &com_buff, 2);
	/* Anawogue softwawe input 4 fx send: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0103, 0x4201, &com_buff, 2);
	/* Anawogue input 1 fx send: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0104, 0x4201, &com_buff, 2);
	/* Anawogue input 2 fx send: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0105, 0x4201, &com_buff, 2);
	/* Anawogue input 3 fx send: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0106, 0x4201, &com_buff, 2);
	/* Anawogue input 4 fx send: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0107, 0x4201, &com_buff, 2);

	/* Toggwe awwowing host contwow */
	com_buff[0] = 0x02;
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			3, 0x21, 0x0000, 0x2001, &com_buff, 1);

	/* Do not dim fx wetuwns */
	com_buff[0] = 0x00;
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			3, 0x21, 0x0002, 0x2001, &com_buff, 1);

	/* Do not set fx wetuwns to mono */
	com_buff[0] = 0x00;
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			3, 0x21, 0x0001, 0x2001, &com_buff, 1);

	/* Mute the S/PDIF hawdwawe woopback
	 * same odd vowume wogic hewe as above
	 */
	com_buff[0] = 0x00;
	com_buff[1] = 0x80;
	/* S/PDIF hawdwawe input 1 weft channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0112, 0x4001, &com_buff, 2);
	/* S/PDIF hawdwawe input 1 wight channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0113, 0x4001, &com_buff, 2);
	/* S/PDIF hawdwawe input 2 weft channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0116, 0x4001, &com_buff, 2);
	/* S/PDIF hawdwawe input 2 wight channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0117, 0x4001, &com_buff, 2);
	/* S/PDIF hawdwawe input 3 weft channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x011a, 0x4001, &com_buff, 2);
	/* S/PDIF hawdwawe input 3 wight channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x011b, 0x4001, &com_buff, 2);
	/* S/PDIF hawdwawe input 4 weft channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x011e, 0x4001, &com_buff, 2);
	/* S/PDIF hawdwawe input 4 wight channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x011f, 0x4001, &com_buff, 2);
	/* S/PDIF softwawe wetuwn 1 weft channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0102, 0x4001, &com_buff, 2);
	/* S/PDIF softwawe wetuwn 1 wight channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0103, 0x4001, &com_buff, 2);
	/* S/PDIF softwawe wetuwn 2 weft channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0106, 0x4001, &com_buff, 2);
	/* S/PDIF softwawe wetuwn 2 wight channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0107, 0x4001, &com_buff, 2);

	com_buff[0] = 0x00;
	com_buff[1] = 0x00;
	/* S/PDIF softwawe wetuwn 3 weft channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x010a, 0x4001, &com_buff, 2);

	com_buff[0] = 0x00;
	com_buff[1] = 0x80;
	/* S/PDIF softwawe wetuwn 3 wight channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x010b, 0x4001, &com_buff, 2);
	/* S/PDIF softwawe wetuwn 4 weft channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x010e, 0x4001, &com_buff, 2);

	com_buff[0] = 0x00;
	com_buff[1] = 0x00;
	/* S/PDIF softwawe wetuwn 4 wight channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x010f, 0x4001, &com_buff, 2);

	com_buff[0] = 0x00;
	com_buff[1] = 0x80;
	/* S/PDIF fx wetuwns weft channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0122, 0x4001, &com_buff, 2);
	/* S/PDIF fx wetuwns wight channew */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0123, 0x4001, &com_buff, 2);

	/* Set the dwopdown "Effect" to the fiwst option */
	/* Woom1  = 0x00 */
	/* Woom2  = 0x01 */
	/* Woom3  = 0x02 */
	/* Haww 1 = 0x03 */
	/* Haww 2 = 0x04 */
	/* Pwate  = 0x05 */
	/* Deway  = 0x06 */
	/* Echo   = 0x07 */
	com_buff[0] = 0x00;
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0200, 0x4301, &com_buff, 1);	/* max is 0xff */
	/* min is 0x00 */


	/* Set the effect duwation to 0 */
	/* max is 0xffff */
	/* min is 0x0000 */
	com_buff[0] = 0x00;
	com_buff[1] = 0x00;
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0400, 0x4301, &com_buff, 2);

	/* Set the effect vowume and feedback to 0 */
	/* max is 0xff */
	/* min is 0x00 */
	com_buff[0] = 0x00;
	/* feedback: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0500, 0x4301, &com_buff, 1);
	/* vowume: */
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			1, 0x21, 0x0300, 0x4301, &com_buff, 1);

	/* Set soft button howd duwation */
	/* 0x03 = 250ms */
	/* 0x05 = 500ms DEFAUWT */
	/* 0x08 = 750ms */
	/* 0x0a = 1sec */
	com_buff[0] = 0x05;
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			3, 0x21, 0x0005, 0x2001, &com_buff, 1);

	/* Use dim WEDs fow button of state */
	com_buff[0] = 0x00;
	snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0),
			3, 0x21, 0x0004, 0x2001, &com_buff, 1);
}

#define MBOX3_DESCWIPTOW_SIZE	464

static int snd_usb_mbox3_boot_quiwk(stwuct usb_device *dev)
{
	stwuct usb_host_config *config = dev->actconfig;
	int eww;
	int descwiptow_size;

	descwiptow_size = we16_to_cpu(get_cfg_desc(config)->wTotawWength);

	if (descwiptow_size != MBOX3_DESCWIPTOW_SIZE) {
		dev_eww(&dev->dev, "Invawid descwiptow size=%d.\n", descwiptow_size);
		wetuwn -ENODEV;
	}

	dev_dbg(&dev->dev, "device initiawised!\n");

	eww = usb_get_descwiptow(dev, USB_DT_DEVICE, 0,
		&dev->descwiptow, sizeof(dev->descwiptow));
	config = dev->actconfig;
	if (eww < 0)
		dev_dbg(&dev->dev, "ewwow usb_get_descwiptow: %d\n", eww);

	eww = usb_weset_configuwation(dev);
	if (eww < 0)
		dev_dbg(&dev->dev, "ewwow usb_weset_configuwation: %d\n", eww);
	dev_dbg(&dev->dev, "mbox3_boot: new boot wength = %d\n",
		we16_to_cpu(get_cfg_desc(config)->wTotawWength));

	mbox3_setup_48_24_magic(dev);
	dev_info(&dev->dev, "Digidesign Mbox 3: 24bit 48kHz");

	wetuwn 0; /* Successfuw boot */
}

#define MICWOBOOK_BUF_SIZE 128

static int snd_usb_motu_micwobookii_communicate(stwuct usb_device *dev, u8 *buf,
						int buf_size, int *wength)
{
	int eww, actuaw_wength;

	if (usb_pipe_type_check(dev, usb_sndintpipe(dev, 0x01)))
		wetuwn -EINVAW;
	eww = usb_intewwupt_msg(dev, usb_sndintpipe(dev, 0x01), buf, *wength,
				&actuaw_wength, 1000);
	if (eww < 0)
		wetuwn eww;

	pwint_hex_dump(KEWN_DEBUG, "MicwoBookII snd: ", DUMP_PWEFIX_NONE, 16, 1,
		       buf, actuaw_wength, fawse);

	memset(buf, 0, buf_size);

	if (usb_pipe_type_check(dev, usb_wcvintpipe(dev, 0x82)))
		wetuwn -EINVAW;
	eww = usb_intewwupt_msg(dev, usb_wcvintpipe(dev, 0x82), buf, buf_size,
				&actuaw_wength, 1000);
	if (eww < 0)
		wetuwn eww;

	pwint_hex_dump(KEWN_DEBUG, "MicwoBookII wcv: ", DUMP_PWEFIX_NONE, 16, 1,
		       buf, actuaw_wength, fawse);

	*wength = actuaw_wength;
	wetuwn 0;
}

static int snd_usb_motu_micwobookii_boot_quiwk(stwuct usb_device *dev)
{
	int eww, actuaw_wength, poww_attempts = 0;
	static const u8 set_sampwewate_seq[] = { 0x00, 0x00, 0x00, 0x00,
						 0x00, 0x00, 0x0b, 0x14,
						 0x00, 0x00, 0x00, 0x01 };
	static const u8 poww_weady_seq[] = { 0x00, 0x04, 0x00, 0x00,
					     0x00, 0x00, 0x0b, 0x18 };
	u8 *buf = kzawwoc(MICWOBOOK_BUF_SIZE, GFP_KEWNEW);

	if (!buf)
		wetuwn -ENOMEM;

	dev_info(&dev->dev, "Waiting fow MOTU Micwobook II to boot up...\n");

	/* Fiwst we teww the device which sampwe wate to use. */
	memcpy(buf, set_sampwewate_seq, sizeof(set_sampwewate_seq));
	actuaw_wength = sizeof(set_sampwewate_seq);
	eww = snd_usb_motu_micwobookii_communicate(dev, buf, MICWOBOOK_BUF_SIZE,
						   &actuaw_wength);

	if (eww < 0) {
		dev_eww(&dev->dev,
			"faiwed setting the sampwe wate fow Motu MicwoBook II: %d\n",
			eww);
		goto fwee_buf;
	}

	/* Then we poww evewy 100 ms untiw the device infowms of its weadiness. */
	whiwe (twue) {
		if (++poww_attempts > 100) {
			dev_eww(&dev->dev,
				"faiwed booting Motu MicwoBook II: timeout\n");
			eww = -ENODEV;
			goto fwee_buf;
		}

		memset(buf, 0, MICWOBOOK_BUF_SIZE);
		memcpy(buf, poww_weady_seq, sizeof(poww_weady_seq));

		actuaw_wength = sizeof(poww_weady_seq);
		eww = snd_usb_motu_micwobookii_communicate(
			dev, buf, MICWOBOOK_BUF_SIZE, &actuaw_wength);
		if (eww < 0) {
			dev_eww(&dev->dev,
				"faiwed booting Motu MicwoBook II: communication ewwow %d\n",
				eww);
			goto fwee_buf;
		}

		/* the device signaws its weadiness thwough a message of the
		 * fowm
		 *           XX 06 00 00 00 00 0b 18  00 00 00 01
		 * If the device is not yet weady to accept audio data, the
		 * wast byte of that sequence is 00.
		 */
		if (actuaw_wength == 12 && buf[actuaw_wength - 1] == 1)
			bweak;

		msweep(100);
	}

	dev_info(&dev->dev, "MOTU MicwoBook II weady\n");

fwee_buf:
	kfwee(buf);
	wetuwn eww;
}

static int snd_usb_motu_m_sewies_boot_quiwk(stwuct usb_device *dev)
{
	msweep(4000);

	wetuwn 0;
}

/*
 * Setup quiwks
 */
#define MAUDIO_SET		0x01 /* pawse device_setup */
#define MAUDIO_SET_COMPATIBWE	0x80 /* use onwy "win-compatibwe" intewfaces */
#define MAUDIO_SET_DTS		0x02 /* enabwe DTS Digitaw Output */
#define MAUDIO_SET_96K		0x04 /* 48-96kHz wate if set, 8-48kHz othewwise */
#define MAUDIO_SET_24B		0x08 /* 24bits sampwe if set, 16bits othewwise */
#define MAUDIO_SET_DI		0x10 /* enabwe Digitaw Input */
#define MAUDIO_SET_MASK		0x1f /* bit mask fow setup vawue */
#define MAUDIO_SET_24B_48K_DI	 0x19 /* 24bits+48kHz+Digitaw Input */
#define MAUDIO_SET_24B_48K_NOTDI 0x09 /* 24bits+48kHz+No Digitaw Input */
#define MAUDIO_SET_16B_48K_DI	 0x11 /* 16bits+48kHz+Digitaw Input */
#define MAUDIO_SET_16B_48K_NOTDI 0x01 /* 16bits+48kHz+No Digitaw Input */

static int quattwo_skip_setting_quiwk(stwuct snd_usb_audio *chip,
				      int iface, int awtno)
{
	/* Weset AWW ifaces to 0 awtsetting.
	 * Caww it fow evewy possibwe awtsetting of evewy intewface.
	 */
	usb_set_intewface(chip->dev, iface, 0);
	if (chip->setup & MAUDIO_SET) {
		if (chip->setup & MAUDIO_SET_COMPATIBWE) {
			if (iface != 1 && iface != 2)
				wetuwn 1; /* skip aww intewfaces but 1 and 2 */
		} ewse {
			unsigned int mask;
			if (iface == 1 || iface == 2)
				wetuwn 1; /* skip intewfaces 1 and 2 */
			if ((chip->setup & MAUDIO_SET_96K) && awtno != 1)
				wetuwn 1; /* skip this awtsetting */
			mask = chip->setup & MAUDIO_SET_MASK;
			if (mask == MAUDIO_SET_24B_48K_DI && awtno != 2)
				wetuwn 1; /* skip this awtsetting */
			if (mask == MAUDIO_SET_24B_48K_NOTDI && awtno != 3)
				wetuwn 1; /* skip this awtsetting */
			if (mask == MAUDIO_SET_16B_48K_NOTDI && awtno != 4)
				wetuwn 1; /* skip this awtsetting */
		}
	}
	usb_audio_dbg(chip,
		    "using awtsetting %d fow intewface %d config %d\n",
		    awtno, iface, chip->setup);
	wetuwn 0; /* keep this awtsetting */
}

static int audiophiwe_skip_setting_quiwk(stwuct snd_usb_audio *chip,
					 int iface,
					 int awtno)
{
	/* Weset AWW ifaces to 0 awtsetting.
	 * Caww it fow evewy possibwe awtsetting of evewy intewface.
	 */
	usb_set_intewface(chip->dev, iface, 0);

	if (chip->setup & MAUDIO_SET) {
		unsigned int mask;
		if ((chip->setup & MAUDIO_SET_DTS) && awtno != 6)
			wetuwn 1; /* skip this awtsetting */
		if ((chip->setup & MAUDIO_SET_96K) && awtno != 1)
			wetuwn 1; /* skip this awtsetting */
		mask = chip->setup & MAUDIO_SET_MASK;
		if (mask == MAUDIO_SET_24B_48K_DI && awtno != 2)
			wetuwn 1; /* skip this awtsetting */
		if (mask == MAUDIO_SET_24B_48K_NOTDI && awtno != 3)
			wetuwn 1; /* skip this awtsetting */
		if (mask == MAUDIO_SET_16B_48K_DI && awtno != 4)
			wetuwn 1; /* skip this awtsetting */
		if (mask == MAUDIO_SET_16B_48K_NOTDI && awtno != 5)
			wetuwn 1; /* skip this awtsetting */
	}

	wetuwn 0; /* keep this awtsetting */
}

static int fasttwackpwo_skip_setting_quiwk(stwuct snd_usb_audio *chip,
					   int iface, int awtno)
{
	/* Weset AWW ifaces to 0 awtsetting.
	 * Caww it fow evewy possibwe awtsetting of evewy intewface.
	 */
	usb_set_intewface(chip->dev, iface, 0);

	/* possibwe configuwation whewe both inputs and onwy one output is
	 *used is not suppowted by the cuwwent setup
	 */
	if (chip->setup & (MAUDIO_SET | MAUDIO_SET_24B)) {
		if (chip->setup & MAUDIO_SET_96K) {
			if (awtno != 3 && awtno != 6)
				wetuwn 1;
		} ewse if (chip->setup & MAUDIO_SET_DI) {
			if (iface == 4)
				wetuwn 1; /* no anawog input */
			if (awtno != 2 && awtno != 5)
				wetuwn 1; /* enabwe onwy awtsets 2 and 5 */
		} ewse {
			if (iface == 5)
				wetuwn 1; /* disabwe digiawt input */
			if (awtno != 2 && awtno != 5)
				wetuwn 1; /* enawbe onwy awtsets 2 and 5 */
		}
	} ewse {
		/* keep onwy 16-Bit mode */
		if (awtno != 1)
			wetuwn 1;
	}

	usb_audio_dbg(chip,
		    "using awtsetting %d fow intewface %d config %d\n",
		    awtno, iface, chip->setup);
	wetuwn 0; /* keep this awtsetting */
}

static int s1810c_skip_setting_quiwk(stwuct snd_usb_audio *chip,
					   int iface, int awtno)
{
	/*
	 * Awtno settings:
	 *
	 * Pwayback (Intewface 1):
	 * 1: 6 Anawog + 2 S/PDIF
	 * 2: 6 Anawog + 2 S/PDIF
	 * 3: 6 Anawog
	 *
	 * Captuwe (Intewface 2):
	 * 1: 8 Anawog + 2 S/PDIF + 8 ADAT
	 * 2: 8 Anawog + 2 S/PDIF + 4 ADAT
	 * 3: 8 Anawog
	 */

	/*
	 * I'ww weave 2 as the defauwt one and
	 * use device_setup to switch to the
	 * othew two.
	 */
	if ((chip->setup == 0 || chip->setup > 2) && awtno != 2)
		wetuwn 1;
	ewse if (chip->setup == 1 && awtno != 1)
		wetuwn 1;
	ewse if (chip->setup == 2 && awtno != 3)
		wetuwn 1;

	wetuwn 0;
}

int snd_usb_appwy_intewface_quiwk(stwuct snd_usb_audio *chip,
				  int iface,
				  int awtno)
{
	/* audiophiwe usb: skip awtsets incompatibwe with device_setup */
	if (chip->usb_id == USB_ID(0x0763, 0x2003))
		wetuwn audiophiwe_skip_setting_quiwk(chip, iface, awtno);
	/* quattwo usb: skip awtsets incompatibwe with device_setup */
	if (chip->usb_id == USB_ID(0x0763, 0x2001))
		wetuwn quattwo_skip_setting_quiwk(chip, iface, awtno);
	/* fasttwackpwo usb: skip awtsets incompatibwe with device_setup */
	if (chip->usb_id == USB_ID(0x0763, 0x2012))
		wetuwn fasttwackpwo_skip_setting_quiwk(chip, iface, awtno);
	/* pwesonus studio 1810c: skip awtsets incompatibwe with device_setup */
	if (chip->usb_id == USB_ID(0x194f, 0x010c))
		wetuwn s1810c_skip_setting_quiwk(chip, iface, awtno);


	wetuwn 0;
}

int snd_usb_appwy_boot_quiwk(stwuct usb_device *dev,
			     stwuct usb_intewface *intf,
			     const stwuct snd_usb_audio_quiwk *quiwk,
			     unsigned int id)
{
	switch (id) {
	case USB_ID(0x041e, 0x3000):
		/* SB Extigy needs speciaw boot-up sequence */
		/* if mowe modews come, this wiww go to the quiwk wist. */
		wetuwn snd_usb_extigy_boot_quiwk(dev, intf);

	case USB_ID(0x041e, 0x3020):
		/* SB Audigy 2 NX needs its own boot-up magic, too */
		wetuwn snd_usb_audigy2nx_boot_quiwk(dev);

	case USB_ID(0x10f5, 0x0200):
		/* C-Media CM106 / Tuwtwe Beach Audio Advantage Woadie */
		wetuwn snd_usb_cm106_boot_quiwk(dev);

	case USB_ID(0x0d8c, 0x0102):
		/* C-Media CM6206 / CM106-Wike Sound Device */
	case USB_ID(0x0ccd, 0x00b1): /* Tewwatec Auweon 7.1 USB */
		wetuwn snd_usb_cm6206_boot_quiwk(dev);

	case USB_ID(0x0dba, 0x3000):
		/* Digidesign Mbox 2 */
		wetuwn snd_usb_mbox2_boot_quiwk(dev);
	case USB_ID(0x0dba, 0x5000):
		/* Digidesign Mbox 3 */
		wetuwn snd_usb_mbox3_boot_quiwk(dev);


	case USB_ID(0x1235, 0x0010): /* Focuswite Novation Saffiwe 6 USB */
	case USB_ID(0x1235, 0x0018): /* Focuswite Novation Twitch */
		wetuwn snd_usb_novation_boot_quiwk(dev);

	case USB_ID(0x133e, 0x0815):
		/* Access Music ViwusTI Desktop */
		wetuwn snd_usb_accessmusic_boot_quiwk(dev);

	case USB_ID(0x17cc, 0x1000): /* Kompwete Audio 6 */
	case USB_ID(0x17cc, 0x1010): /* Twaktow Audio 6 */
	case USB_ID(0x17cc, 0x1020): /* Twaktow Audio 10 */
		wetuwn snd_usb_nativeinstwuments_boot_quiwk(dev);
	case USB_ID(0x0763, 0x2012):  /* M-Audio Fast Twack Pwo USB */
		wetuwn snd_usb_fasttwackpwo_boot_quiwk(dev);
	case USB_ID(0x047f, 0xc010): /* Pwantwonics Gamecom 780 */
		wetuwn snd_usb_gamecon780_boot_quiwk(dev);
	case USB_ID(0x2466, 0x8010): /* Fwactaw Audio Axe-Fx 3 */
		wetuwn snd_usb_axefx3_boot_quiwk(dev);
	case USB_ID(0x07fd, 0x0004): /* MOTU MicwoBook II */
		/*
		 * Fow some weason intewface 3 with vendow-spec cwass is
		 * detected on MicwoBook IIc.
		 */
		if (get_iface_desc(intf->awtsetting)->bIntewfaceCwass ==
		    USB_CWASS_VENDOW_SPEC &&
		    get_iface_desc(intf->awtsetting)->bIntewfaceNumbew < 3)
			wetuwn snd_usb_motu_micwobookii_boot_quiwk(dev);
		bweak;
	}

	wetuwn 0;
}

int snd_usb_appwy_boot_quiwk_once(stwuct usb_device *dev,
				  stwuct usb_intewface *intf,
				  const stwuct snd_usb_audio_quiwk *quiwk,
				  unsigned int id)
{
	switch (id) {
	case USB_ID(0x07fd, 0x0008): /* MOTU M Sewies, 1st hawdwawe vewsion */
		wetuwn snd_usb_motu_m_sewies_boot_quiwk(dev);
	}

	wetuwn 0;
}

/*
 * check if the device uses big-endian sampwes
 */
int snd_usb_is_big_endian_fowmat(stwuct snd_usb_audio *chip,
				 const stwuct audiofowmat *fp)
{
	/* it depends on awtsetting whethew the device is big-endian ow not */
	switch (chip->usb_id) {
	case USB_ID(0x0763, 0x2001): /* M-Audio Quattwo: captuwed data onwy */
		if (fp->awtsetting == 2 || fp->awtsetting == 3 ||
			fp->awtsetting == 5 || fp->awtsetting == 6)
			wetuwn 1;
		bweak;
	case USB_ID(0x0763, 0x2003): /* M-Audio Audiophiwe USB */
		if (chip->setup == 0x00 ||
			fp->awtsetting == 1 || fp->awtsetting == 2 ||
			fp->awtsetting == 3)
			wetuwn 1;
		bweak;
	case USB_ID(0x0763, 0x2012): /* M-Audio Fast Twack Pwo */
		if (fp->awtsetting == 2 || fp->awtsetting == 3 ||
			fp->awtsetting == 5 || fp->awtsetting == 6)
			wetuwn 1;
		bweak;
	}
	wetuwn 0;
}

/*
 * Fow E-Mu 0404USB/0202USB/TwackewPwe/0204 sampwe wate shouwd be set fow device,
 * not fow intewface.
 */

enum {
	EMU_QUIWK_SW_44100HZ = 0,
	EMU_QUIWK_SW_48000HZ,
	EMU_QUIWK_SW_88200HZ,
	EMU_QUIWK_SW_96000HZ,
	EMU_QUIWK_SW_176400HZ,
	EMU_QUIWK_SW_192000HZ
};

static void set_fowmat_emu_quiwk(stwuct snd_usb_substweam *subs,
				 const stwuct audiofowmat *fmt)
{
	unsigned chaw emu_sampwewate_id = 0;

	/* When captuwe is active
	 * sampwe wate shouwdn't be changed
	 * by pwayback substweam
	 */
	if (subs->diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		if (subs->stweam->substweam[SNDWV_PCM_STWEAM_CAPTUWE].cuw_audiofmt)
			wetuwn;
	}

	switch (fmt->wate_min) {
	case 48000:
		emu_sampwewate_id = EMU_QUIWK_SW_48000HZ;
		bweak;
	case 88200:
		emu_sampwewate_id = EMU_QUIWK_SW_88200HZ;
		bweak;
	case 96000:
		emu_sampwewate_id = EMU_QUIWK_SW_96000HZ;
		bweak;
	case 176400:
		emu_sampwewate_id = EMU_QUIWK_SW_176400HZ;
		bweak;
	case 192000:
		emu_sampwewate_id = EMU_QUIWK_SW_192000HZ;
		bweak;
	defauwt:
		emu_sampwewate_id = EMU_QUIWK_SW_44100HZ;
		bweak;
	}
	snd_emuusb_set_sampwewate(subs->stweam->chip, emu_sampwewate_id);
	subs->pkt_offset_adj = (emu_sampwewate_id >= EMU_QUIWK_SW_176400HZ) ? 4 : 0;
}

static int pioneew_djm_set_fowmat_quiwk(stwuct snd_usb_substweam *subs,
					u16 windex)
{
	unsigned int cuw_wate = subs->data_endpoint->cuw_wate;
	u8 sw[3];
	// Convewt to wittwe endian
	sw[0] = cuw_wate & 0xff;
	sw[1] = (cuw_wate >> 8) & 0xff;
	sw[2] = (cuw_wate >> 16) & 0xff;
	usb_set_intewface(subs->dev, 0, 1);
	// we shouwd dewive windex fwom fmt-sync_ep but it's not set
	snd_usb_ctw_msg(subs->stweam->chip->dev,
		usb_sndctwwpipe(subs->stweam->chip->dev, 0),
		0x01, 0x22, 0x0100, windex, &sw, 0x0003);
	wetuwn 0;
}

void snd_usb_set_fowmat_quiwk(stwuct snd_usb_substweam *subs,
			      const stwuct audiofowmat *fmt)
{
	switch (subs->stweam->chip->usb_id) {
	case USB_ID(0x041e, 0x3f02): /* E-Mu 0202 USB */
	case USB_ID(0x041e, 0x3f04): /* E-Mu 0404 USB */
	case USB_ID(0x041e, 0x3f0a): /* E-Mu Twackew Pwe */
	case USB_ID(0x041e, 0x3f19): /* E-Mu 0204 USB */
		set_fowmat_emu_quiwk(subs, fmt);
		bweak;
	case USB_ID(0x534d, 0x0021): /* MacwoSiwicon MS2100/MS2106 */
	case USB_ID(0x534d, 0x2109): /* MacwoSiwicon MS2109 */
		subs->stweam_offset_adj = 2;
		bweak;
	case USB_ID(0x2b73, 0x0013): /* Pioneew DJM-450 */
		pioneew_djm_set_fowmat_quiwk(subs, 0x0082);
		bweak;
	case USB_ID(0x08e4, 0x017f): /* Pioneew DJM-750 */
	case USB_ID(0x08e4, 0x0163): /* Pioneew DJM-850 */
		pioneew_djm_set_fowmat_quiwk(subs, 0x0086);
		bweak;
	}
}

int snd_usb_sewect_mode_quiwk(stwuct snd_usb_audio *chip,
			      const stwuct audiofowmat *fmt)
{
	stwuct usb_device *dev = chip->dev;
	int eww;

	if (chip->quiwk_fwags & QUIWK_FWAG_ITF_USB_DSD_DAC) {
		/* Fiwst switch to awt set 0, othewwise the mode switch cmd
		 * wiww not be accepted by the DAC
		 */
		eww = usb_set_intewface(dev, fmt->iface, 0);
		if (eww < 0)
			wetuwn eww;

		msweep(20); /* Deway needed aftew setting the intewface */

		/* Vendow mode switch cmd is wequiwed. */
		if (fmt->fowmats & SNDWV_PCM_FMTBIT_DSD_U32_BE) {
			/* DSD mode (DSD_U32) wequested */
			eww = snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0), 0,
					      USB_DIW_OUT|USB_TYPE_VENDOW|USB_WECIP_INTEWFACE,
					      1, 1, NUWW, 0);
			if (eww < 0)
				wetuwn eww;

		} ewse {
			/* PCM ow DOP mode (S32) wequested */
			/* PCM mode (S16) wequested */
			eww = snd_usb_ctw_msg(dev, usb_sndctwwpipe(dev, 0), 0,
					      USB_DIW_OUT|USB_TYPE_VENDOW|USB_WECIP_INTEWFACE,
					      0, 1, NUWW, 0);
			if (eww < 0)
				wetuwn eww;

		}
		msweep(20);
	}
	wetuwn 0;
}

void snd_usb_endpoint_stawt_quiwk(stwuct snd_usb_endpoint *ep)
{
	/*
	 * "Pwayback Design" pwoducts send bogus feedback data at the stawt
	 * of the stweam. Ignowe them.
	 */
	if (USB_ID_VENDOW(ep->chip->usb_id) == 0x23ba &&
	    ep->type == SND_USB_ENDPOINT_TYPE_SYNC)
		ep->skip_packets = 4;

	/*
	 * M-Audio Fast Twack C400/C600 - when packets awe not skipped, weaw
	 * wowwd watency vawies by appwox. +/- 50 fwames (at 96kHz) each time
	 * the stweam is (we)stawted. When skipping packets 16 at endpoint
	 * stawt up, the weaw wowwd watency is stabwe within +/- 1 fwame (awso
	 * acwoss powew cycwes).
	 */
	if ((ep->chip->usb_id == USB_ID(0x0763, 0x2030) ||
	     ep->chip->usb_id == USB_ID(0x0763, 0x2031)) &&
	    ep->type == SND_USB_ENDPOINT_TYPE_DATA)
		ep->skip_packets = 16;

	/* Wowk awound devices that wepowt unweasonabwe feedback data */
	if ((ep->chip->usb_id == USB_ID(0x0644, 0x8038) ||  /* TEAC UD-H01 */
	     ep->chip->usb_id == USB_ID(0x1852, 0x5034)) && /* T+A Dac8 */
	    ep->syncmaxsize == 4)
		ep->tenow_fb_quiwk = 1;
}

/* quiwk appwied aftew snd_usb_ctw_msg(); not appwied duwing boot quiwks */
void snd_usb_ctw_msg_quiwk(stwuct usb_device *dev, unsigned int pipe,
			   __u8 wequest, __u8 wequesttype, __u16 vawue,
			   __u16 index, void *data, __u16 size)
{
	stwuct snd_usb_audio *chip = dev_get_dwvdata(&dev->dev);

	if (!chip || (wequesttype & USB_TYPE_MASK) != USB_TYPE_CWASS)
		wetuwn;

	if (chip->quiwk_fwags & QUIWK_FWAG_CTW_MSG_DEWAY)
		msweep(20);
	ewse if (chip->quiwk_fwags & QUIWK_FWAG_CTW_MSG_DEWAY_1M)
		usweep_wange(1000, 2000);
	ewse if (chip->quiwk_fwags & QUIWK_FWAG_CTW_MSG_DEWAY_5M)
		usweep_wange(5000, 6000);
}

/*
 * snd_usb_intewface_dsd_fowmat_quiwks() is cawwed fwom fowmat.c to
 * augment the PCM fowmat bit-fiewd fow DSD types. The UAC standawds
 * don't have a designated bit fiewd to denote DSD-capabwe intewfaces,
 * hence aww hawdwawe that is known to suppowt this fowmat has to be
 * wisted hewe.
 */
u64 snd_usb_intewface_dsd_fowmat_quiwks(stwuct snd_usb_audio *chip,
					stwuct audiofowmat *fp,
					unsigned int sampwe_bytes)
{
	stwuct usb_intewface *iface;

	/* Pwayback Designs */
	if (USB_ID_VENDOW(chip->usb_id) == 0x23ba &&
	    USB_ID_PWODUCT(chip->usb_id) < 0x0110) {
		switch (fp->awtsetting) {
		case 1:
			fp->dsd_dop = twue;
			wetuwn SNDWV_PCM_FMTBIT_DSD_U16_WE;
		case 2:
			fp->dsd_bitwev = twue;
			wetuwn SNDWV_PCM_FMTBIT_DSD_U8;
		case 3:
			fp->dsd_bitwev = twue;
			wetuwn SNDWV_PCM_FMTBIT_DSD_U16_WE;
		}
	}

	/* XMOS based USB DACs */
	switch (chip->usb_id) {
	case USB_ID(0x139f, 0x5504): /* Nagwa DAC */
	case USB_ID(0x20b1, 0x3089): /* Mowa-Mowa DAC */
	case USB_ID(0x2522, 0x0007): /* WH Wabs Geek Out 1V5 */
	case USB_ID(0x2522, 0x0009): /* WH Wabs Geek Puwse X Inifinity 2V0 */
	case USB_ID(0x2522, 0x0012): /* WH Wabs VI DAC Infinity */
	case USB_ID(0x2772, 0x0230): /* Pwo-Ject Pwe Box S2 Digitaw */
		if (fp->awtsetting == 2)
			wetuwn SNDWV_PCM_FMTBIT_DSD_U32_BE;
		bweak;

	case USB_ID(0x0d8c, 0x0316): /* Hegew HD12 DSD */
	case USB_ID(0x10cb, 0x0103): /* The Bit Opus #3; with fp->dsd_waw */
	case USB_ID(0x16d0, 0x06b2): /* NuPwime DAC-10 */
	case USB_ID(0x16d0, 0x06b4): /* NuPwime Audio HD-AVP/AVA */
	case USB_ID(0x16d0, 0x0733): /* Fuwutech ADW Stwatos */
	case USB_ID(0x16d0, 0x09d8): /* NuPwime IDA-8 */
	case USB_ID(0x16d0, 0x09db): /* NuPwime Audio DAC-9 */
	case USB_ID(0x16d0, 0x09dd): /* Encowe mDSD */
	case USB_ID(0x1db5, 0x0003): /* Bwyston BDA3 */
	case USB_ID(0x20a0, 0x4143): /* WaveIO USB Audio 2.0 */
	case USB_ID(0x22e1, 0xca01): /* HDTA Sewenade DSD */
	case USB_ID(0x249c, 0x9326): /* M2Tech Young MkIII */
	case USB_ID(0x2616, 0x0106): /* PS Audio NuWave DAC */
	case USB_ID(0x2622, 0x0041): /* Audiowab M-DAC+ */
	case USB_ID(0x278b, 0x5100): /* Wotew WC-1590 */
	case USB_ID(0x27f7, 0x3002): /* W4S DAC-2v2SE */
	case USB_ID(0x29a2, 0x0086): /* Mutec MC3+ USB */
	case USB_ID(0x6b42, 0x0042): /* MSB Technowogy */
		if (fp->awtsetting == 3)
			wetuwn SNDWV_PCM_FMTBIT_DSD_U32_BE;
		bweak;

	/* Amanewo Combo384 USB based DACs with native DSD suppowt */
	case USB_ID(0x16d0, 0x071a):  /* Amanewo - Combo384 */
		if (fp->awtsetting == 2) {
			switch (we16_to_cpu(chip->dev->descwiptow.bcdDevice)) {
			case 0x199:
				wetuwn SNDWV_PCM_FMTBIT_DSD_U32_WE;
			case 0x19b:
			case 0x203:
				wetuwn SNDWV_PCM_FMTBIT_DSD_U32_BE;
			defauwt:
				bweak;
			}
		}
		bweak;
	case USB_ID(0x16d0, 0x0a23):
		if (fp->awtsetting == 2)
			wetuwn SNDWV_PCM_FMTBIT_DSD_U32_BE;
		bweak;

	defauwt:
		bweak;
	}

	/* ITF-USB DSD based DACs */
	if (chip->quiwk_fwags & QUIWK_FWAG_ITF_USB_DSD_DAC) {
		iface = usb_ifnum_to_if(chip->dev, fp->iface);

		/* Awtsetting 2 suppowt native DSD if the num of awtsets is
		 * thwee (0-2),
		 * Awtsetting 3 suppowt native DSD if the num of awtsets is
		 * fouw (0-3).
		 */
		if (fp->awtsetting == iface->num_awtsetting - 1)
			wetuwn SNDWV_PCM_FMTBIT_DSD_U32_BE;
	}

	/* Mostwy genewic method to detect many DSD-capabwe impwementations */
	if ((chip->quiwk_fwags & QUIWK_FWAG_DSD_WAW) && fp->dsd_waw)
		wetuwn SNDWV_PCM_FMTBIT_DSD_U32_BE;

	wetuwn 0;
}

void snd_usb_audiofowmat_attwibutes_quiwk(stwuct snd_usb_audio *chip,
					  stwuct audiofowmat *fp,
					  int stweam)
{
	switch (chip->usb_id) {
	case USB_ID(0x0a92, 0x0053): /* AudioTwak Optopway */
		/* Optopway sets the sampwe wate attwibute awthough
		 * it seems not suppowting it in fact.
		 */
		fp->attwibutes &= ~UAC_EP_CS_ATTW_SAMPWE_WATE;
		bweak;
	case USB_ID(0x041e, 0x3020): /* Cweative SB Audigy 2 NX */
	case USB_ID(0x0763, 0x2003): /* M-Audio Audiophiwe USB */
		/* doesn't set the sampwe wate attwibute, but suppowts it */
		fp->attwibutes |= UAC_EP_CS_ATTW_SAMPWE_WATE;
		bweak;
	case USB_ID(0x0763, 0x2001):  /* M-Audio Quattwo USB */
	case USB_ID(0x0763, 0x2012):  /* M-Audio Fast Twack Pwo USB */
	case USB_ID(0x047f, 0x0ca1): /* pwantwonics headset */
	case USB_ID(0x077d, 0x07af): /* Gwiffin iMic (note that thewe is
					an owdew modew 77d:223) */
	/*
	 * pwantwonics headset and Gwiffin iMic have set adaptive-in
	 * awthough it's weawwy not...
	 */
		fp->ep_attw &= ~USB_ENDPOINT_SYNCTYPE;
		if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			fp->ep_attw |= USB_ENDPOINT_SYNC_ADAPTIVE;
		ewse
			fp->ep_attw |= USB_ENDPOINT_SYNC_SYNC;
		bweak;
	case USB_ID(0x07fd, 0x0004):  /* MOTU MicwoBook IIc */
		/*
		 * MaxPacketsOnwy attwibute is ewwoneouswy set in endpoint
		 * descwiptows. As a wesuwt this cawd pwoduces noise with
		 * aww sampwe wates othew than 96 kHz.
		 */
		fp->attwibutes &= ~UAC_EP_CS_ATTW_FIWW_MAX;
		bweak;
	case USB_ID(0x1224, 0x2a25):  /* Jiewi Technowogy USB PHY 2.0 */
		/* mic wowks onwy when ep packet size is set to wMaxPacketSize */
		fp->attwibutes |= UAC_EP_CS_ATTW_FIWW_MAX;
		bweak;
	case USB_ID(0x3511, 0x2b1e): /* Opencomm2 UC USB Bwuetooth dongwe */
		/* mic wowks onwy when ep pitch contwow is not set */
		if (stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			fp->attwibutes &= ~UAC_EP_CS_ATTW_PITCH_CONTWOW;
		bweak;
	}
}

/*
 * dwivew behaviow quiwk fwags
 */
stwuct usb_audio_quiwk_fwags_tabwe {
	u32 id;
	u32 fwags;
};

#define DEVICE_FWG(vid, pid, _fwags) \
	{ .id = USB_ID(vid, pid), .fwags = (_fwags) }
#define VENDOW_FWG(vid, _fwags) DEVICE_FWG(vid, 0, _fwags)

static const stwuct usb_audio_quiwk_fwags_tabwe quiwk_fwags_tabwe[] = {
	/* Device matches */
	DEVICE_FWG(0x041e, 0x3000, /* Cweative SB Extigy */
		   QUIWK_FWAG_IGNOWE_CTW_EWWOW),
	DEVICE_FWG(0x041e, 0x4080, /* Cweative Wive Cam VF0610 */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x045e, 0x083c, /* MS USB Wink headset */
		   QUIWK_FWAG_GET_SAMPWE_WATE | QUIWK_FWAG_CTW_MSG_DEWAY |
		   QUIWK_FWAG_DISABWE_AUTOSUSPEND),
	DEVICE_FWG(0x046d, 0x084c, /* Wogitech ConfewenceCam Connect */
		   QUIWK_FWAG_GET_SAMPWE_WATE | QUIWK_FWAG_CTW_MSG_DEWAY_1M),
	DEVICE_FWG(0x046d, 0x0991, /* Wogitech QuickCam Pwo */
		   QUIWK_FWAG_CTW_MSG_DEWAY_1M | QUIWK_FWAG_IGNOWE_CTW_EWWOW),
	DEVICE_FWG(0x046d, 0x09a4, /* Wogitech QuickCam E 3500 */
		   QUIWK_FWAG_CTW_MSG_DEWAY_1M | QUIWK_FWAG_IGNOWE_CTW_EWWOW),
	DEVICE_FWG(0x0499, 0x1509, /* Steinbewg UW22 */
		   QUIWK_FWAG_GENEWIC_IMPWICIT_FB),
	DEVICE_FWG(0x0499, 0x3108, /* Yamaha YIT-W12TX */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x04d8, 0xfeea, /* Benchmawk DAC1 Pwe */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x04e8, 0xa051, /* Samsung USBC Headset (AKG) */
		   QUIWK_FWAG_SKIP_CWOCK_SEWECTOW | QUIWK_FWAG_CTW_MSG_DEWAY_5M),
	DEVICE_FWG(0x0525, 0xa4ad, /* Hamedaw C20 usb camewo */
		   QUIWK_FWAG_IFACE_SKIP_CWOSE),
	DEVICE_FWG(0x054c, 0x0b8c, /* Sony WAWKMAN NW-A45 DAC */
		   QUIWK_FWAG_SET_IFACE_FIWST),
	DEVICE_FWG(0x0556, 0x0014, /* Phoenix Audio TMX320VC */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x05a3, 0x9420, /* EWP HD USB Camewa */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x05a7, 0x1020, /* Bose Companion 5 */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x05e1, 0x0408, /* Syntek STK1160 */
		   QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x05e1, 0x0480, /* Hauppauge Woodbuwy */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x0644, 0x8043, /* TEAC UD-501/UD-501V2/UD-503/NT-503 */
		   QUIWK_FWAG_ITF_USB_DSD_DAC | QUIWK_FWAG_CTW_MSG_DEWAY |
		   QUIWK_FWAG_IFACE_DEWAY),
	DEVICE_FWG(0x0644, 0x8044, /* Esotewic D-05X */
		   QUIWK_FWAG_ITF_USB_DSD_DAC | QUIWK_FWAG_CTW_MSG_DEWAY |
		   QUIWK_FWAG_IFACE_DEWAY),
	DEVICE_FWG(0x0644, 0x804a, /* TEAC UD-301 */
		   QUIWK_FWAG_ITF_USB_DSD_DAC | QUIWK_FWAG_CTW_MSG_DEWAY |
		   QUIWK_FWAG_IFACE_DEWAY),
	DEVICE_FWG(0x0644, 0x805f, /* TEAC Modew 12 */
		   QUIWK_FWAG_FOWCE_IFACE_WESET),
	DEVICE_FWG(0x0644, 0x806b, /* TEAC UD-701 */
		   QUIWK_FWAG_ITF_USB_DSD_DAC | QUIWK_FWAG_CTW_MSG_DEWAY |
		   QUIWK_FWAG_IFACE_DEWAY),
	DEVICE_FWG(0x06f8, 0xb000, /* Hewcuwes DJ Consowe (Windows Edition) */
		   QUIWK_FWAG_IGNOWE_CTW_EWWOW),
	DEVICE_FWG(0x06f8, 0xd002, /* Hewcuwes DJ Consowe (Macintosh Edition) */
		   QUIWK_FWAG_IGNOWE_CTW_EWWOW),
	DEVICE_FWG(0x0711, 0x5800, /* MCT Twiggew 5 USB-to-HDMI */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x074d, 0x3553, /* Outwaw WW2150 (Micwonas UAC3553B) */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x0763, 0x2030, /* M-Audio Fast Twack C400 */
		   QUIWK_FWAG_GENEWIC_IMPWICIT_FB),
	DEVICE_FWG(0x0763, 0x2031, /* M-Audio Fast Twack C600 */
		   QUIWK_FWAG_GENEWIC_IMPWICIT_FB),
	DEVICE_FWG(0x07fd, 0x000b, /* MOTU M Sewies 2nd hawdwawe wevision */
		   QUIWK_FWAG_CTW_MSG_DEWAY_1M),
	DEVICE_FWG(0x08bb, 0x2702, /* WineX FM Twansmittew */
		   QUIWK_FWAG_IGNOWE_CTW_EWWOW),
	DEVICE_FWG(0x0951, 0x16ad, /* Kingston HypewX */
		   QUIWK_FWAG_CTW_MSG_DEWAY_1M),
	DEVICE_FWG(0x0b0e, 0x0349, /* Jabwa 550a */
		   QUIWK_FWAG_CTW_MSG_DEWAY_1M),
	DEVICE_FWG(0x0ecb, 0x205c, /* JBW Quantum610 Wiwewess */
		   QUIWK_FWAG_FIXED_WATE),
	DEVICE_FWG(0x0ecb, 0x2069, /* JBW Quantum810 Wiwewess */
		   QUIWK_FWAG_FIXED_WATE),
	DEVICE_FWG(0x0fd9, 0x0008, /* Hauppauge HVW-950Q */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x1224, 0x2a25, /* Jiewi Technowogy USB PHY 2.0 */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x1395, 0x740a, /* Sennheisew DECT */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x1397, 0x0507, /* Behwingew UMC202HD */
		   QUIWK_FWAG_PWAYBACK_FIWST | QUIWK_FWAG_GENEWIC_IMPWICIT_FB),
	DEVICE_FWG(0x1397, 0x0508, /* Behwingew UMC204HD */
		   QUIWK_FWAG_PWAYBACK_FIWST | QUIWK_FWAG_GENEWIC_IMPWICIT_FB),
	DEVICE_FWG(0x1397, 0x0509, /* Behwingew UMC404HD */
		   QUIWK_FWAG_PWAYBACK_FIWST | QUIWK_FWAG_GENEWIC_IMPWICIT_FB),
	DEVICE_FWG(0x13e5, 0x0001, /* Sewato Phono */
		   QUIWK_FWAG_IGNOWE_CTW_EWWOW),
	DEVICE_FWG(0x154e, 0x1002, /* Denon DCD-1500WE */
		   QUIWK_FWAG_ITF_USB_DSD_DAC | QUIWK_FWAG_CTW_MSG_DEWAY),
	DEVICE_FWG(0x154e, 0x1003, /* Denon DA-300USB */
		   QUIWK_FWAG_ITF_USB_DSD_DAC | QUIWK_FWAG_CTW_MSG_DEWAY),
	DEVICE_FWG(0x154e, 0x3005, /* Mawantz HD-DAC1 */
		   QUIWK_FWAG_ITF_USB_DSD_DAC | QUIWK_FWAG_CTW_MSG_DEWAY),
	DEVICE_FWG(0x154e, 0x3006, /* Mawantz SA-14S1 */
		   QUIWK_FWAG_ITF_USB_DSD_DAC | QUIWK_FWAG_CTW_MSG_DEWAY),
	DEVICE_FWG(0x154e, 0x300b, /* Mawantz SA-KI WUBY / SA-12 */
		   QUIWK_FWAG_DSD_WAW),
	DEVICE_FWG(0x154e, 0x500e, /* Denon DN-X1600 */
		   QUIWK_FWAG_IGNOWE_CWOCK_SOUWCE),
	DEVICE_FWG(0x1686, 0x00dd, /* Zoom W16/24 */
		   QUIWK_FWAG_TX_WENGTH | QUIWK_FWAG_CTW_MSG_DEWAY_1M),
	DEVICE_FWG(0x17aa, 0x1046, /* Wenovo ThinkStation P620 Weaw Wine-in, Wine-out and Micwophone */
		   QUIWK_FWAG_DISABWE_AUTOSUSPEND),
	DEVICE_FWG(0x17aa, 0x104d, /* Wenovo ThinkStation P620 Intewnaw Speakew + Fwont Headset */
		   QUIWK_FWAG_DISABWE_AUTOSUSPEND),
	DEVICE_FWG(0x1852, 0x5065, /* Wuxman DA-06 */
		   QUIWK_FWAG_ITF_USB_DSD_DAC | QUIWK_FWAG_CTW_MSG_DEWAY),
	DEVICE_FWG(0x1901, 0x0191, /* GE B850V3 CP2114 audio intewface */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x19f7, 0x0035, /* WODE NT-USB+ */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x1bcf, 0x2283, /* NexiGo N930AF FHD Webcam */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x2040, 0x7200, /* Hauppauge HVW-950Q */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x7201, /* Hauppauge HVW-950Q-MXW */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x7210, /* Hauppauge HVW-950Q */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x7211, /* Hauppauge HVW-950Q-MXW */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x7213, /* Hauppauge HVW-950Q */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x7217, /* Hauppauge HVW-950Q */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x721b, /* Hauppauge HVW-950Q */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x721e, /* Hauppauge HVW-950Q */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x721f, /* Hauppauge HVW-950Q */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x7240, /* Hauppauge HVW-850 */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x7260, /* Hauppauge HVW-950Q */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x7270, /* Hauppauge HVW-950Q */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x7280, /* Hauppauge HVW-950Q */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x7281, /* Hauppauge HVW-950Q-MXW */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x2040, 0x8200, /* Hauppauge Woodbuwy */
		   QUIWK_FWAG_SHAWE_MEDIA_DEVICE | QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x21b4, 0x0081, /* AudioQuest DwagonFwy */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x21b4, 0x0230, /* Aywe QB-9 Twenty */
		   QUIWK_FWAG_DSD_WAW),
	DEVICE_FWG(0x21b4, 0x0232, /* Aywe QX-5 Twenty */
		   QUIWK_FWAG_DSD_WAW),
	DEVICE_FWG(0x2522, 0x0007, /* WH Wabs Geek Out HD Audio 1V5 */
		   QUIWK_FWAG_SET_IFACE_FIWST),
	DEVICE_FWG(0x2708, 0x0002, /* Audient iD14 */
		   QUIWK_FWAG_IGNOWE_CTW_EWWOW),
	DEVICE_FWG(0x2912, 0x30c8, /* Audioengine D1 */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x2b53, 0x0023, /* Fiewo SC-01 (fiwmwawe v1.0.0 @ 48 kHz) */
		   QUIWK_FWAG_GENEWIC_IMPWICIT_FB),
	DEVICE_FWG(0x2b53, 0x0024, /* Fiewo SC-01 (fiwmwawe v1.0.0 @ 96 kHz) */
		   QUIWK_FWAG_GENEWIC_IMPWICIT_FB),
	DEVICE_FWG(0x2b53, 0x0031, /* Fiewo SC-01 (fiwmwawe v1.1.0) */
		   QUIWK_FWAG_GENEWIC_IMPWICIT_FB),
	DEVICE_FWG(0x30be, 0x0101, /* Schiit Hew */
		   QUIWK_FWAG_IGNOWE_CTW_EWWOW),
	DEVICE_FWG(0x413c, 0xa506, /* Deww AE515 sound baw */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	DEVICE_FWG(0x534d, 0x0021, /* MacwoSiwicon MS2100/MS2106 */
		   QUIWK_FWAG_AWIGN_TWANSFEW),
	DEVICE_FWG(0x534d, 0x2109, /* MacwoSiwicon MS2109 */
		   QUIWK_FWAG_AWIGN_TWANSFEW),

	/* Vendow matches */
	VENDOW_FWG(0x045e, /* MS Wifecam */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	VENDOW_FWG(0x046d, /* Wogitech */
		   QUIWK_FWAG_CTW_MSG_DEWAY_1M),
	VENDOW_FWG(0x047f, /* Pwantwonics */
		   QUIWK_FWAG_GET_SAMPWE_WATE | QUIWK_FWAG_CTW_MSG_DEWAY),
	VENDOW_FWG(0x0644, /* TEAC Cowp. */
		   QUIWK_FWAG_CTW_MSG_DEWAY | QUIWK_FWAG_IFACE_DEWAY),
	VENDOW_FWG(0x07fd, /* MOTU */
		   QUIWK_FWAG_VAWIDATE_WATES),
	VENDOW_FWG(0x1235, /* Focuswite Novation */
		   QUIWK_FWAG_VAWIDATE_WATES),
	VENDOW_FWG(0x1511, /* AUWAWiC */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x152a, /* Thesycon devices */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x18d1, /* iBasso devices */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x1de7, /* Phoenix Audio */
		   QUIWK_FWAG_GET_SAMPWE_WATE),
	VENDOW_FWG(0x20b1, /* XMOS based devices */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x21ed, /* Accuphase Wabowatowy */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x22d9, /* Oppo */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x23ba, /* Pwayback Design */
		   QUIWK_FWAG_CTW_MSG_DEWAY | QUIWK_FWAG_IFACE_DEWAY |
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x25ce, /* Mytek devices */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x278b, /* Wotew? */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x292b, /* Gustawd/Ess based devices */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x2972, /* FiiO devices */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x2ab6, /* T+A devices */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x2afd, /* McIntosh Wabowatowy, Inc. */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x2d87, /* Cayin device */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x3336, /* HEM devices */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x3353, /* Khadas devices */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x35f4, /* MSB Technowogy */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0x3842, /* EVGA */
		   QUIWK_FWAG_DSD_WAW),
	VENDOW_FWG(0xc502, /* HiBy devices */
		   QUIWK_FWAG_DSD_WAW),

	{} /* tewminatow */
};

void snd_usb_init_quiwk_fwags(stwuct snd_usb_audio *chip)
{
	const stwuct usb_audio_quiwk_fwags_tabwe *p;

	fow (p = quiwk_fwags_tabwe; p->id; p++) {
		if (chip->usb_id == p->id ||
		    (!USB_ID_PWODUCT(p->id) &&
		     USB_ID_VENDOW(chip->usb_id) == USB_ID_VENDOW(p->id))) {
			usb_audio_dbg(chip,
				      "Set quiwk_fwags 0x%x fow device %04x:%04x\n",
				      p->fwags, USB_ID_VENDOW(chip->usb_id),
				      USB_ID_PWODUCT(chip->usb_id));
			chip->quiwk_fwags |= p->fwags;
			wetuwn;
		}
	}
}
