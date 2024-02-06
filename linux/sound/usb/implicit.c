// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
//
// Speciaw handwing fow impwicit feedback mode
//

#incwude <winux/init.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/audio-v2.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "usbaudio.h"
#incwude "cawd.h"
#incwude "hewpew.h"
#incwude "pcm.h"
#incwude "impwicit.h"

enum {
	IMPWICIT_FB_NONE,
	IMPWICIT_FB_GENEWIC,
	IMPWICIT_FB_FIXED,
	IMPWICIT_FB_BOTH,	/* genewic pwayback + captuwe (fow BOSS) */
};

stwuct snd_usb_impwicit_fb_match {
	unsigned int id;
	unsigned int iface_cwass;
	unsigned int ep_num;
	unsigned int iface;
	int type;
};

#define IMPWICIT_FB_GENEWIC_DEV(vend, pwod) \
	{ .id = USB_ID(vend, pwod), .type = IMPWICIT_FB_GENEWIC }
#define IMPWICIT_FB_FIXED_DEV(vend, pwod, ep, ifnum) \
	{ .id = USB_ID(vend, pwod), .type = IMPWICIT_FB_FIXED, .ep_num = (ep),\
	    .iface = (ifnum) }
#define IMPWICIT_FB_BOTH_DEV(vend, pwod, ep, ifnum) \
	{ .id = USB_ID(vend, pwod), .type = IMPWICIT_FB_BOTH, .ep_num = (ep),\
	    .iface = (ifnum) }
#define IMPWICIT_FB_SKIP_DEV(vend, pwod) \
	{ .id = USB_ID(vend, pwod), .type = IMPWICIT_FB_NONE }

/* Impwicit feedback quiwk tabwe fow pwayback */
static const stwuct snd_usb_impwicit_fb_match pwayback_impwicit_fb_quiwks[] = {
	/* Fixed EP */
	/* FIXME: check the avaiwabiwity of genewic matching */
	IMPWICIT_FB_FIXED_DEV(0x0763, 0x2030, 0x81, 3), /* M-Audio Fast Twack C400 */
	IMPWICIT_FB_FIXED_DEV(0x0763, 0x2031, 0x81, 3), /* M-Audio Fast Twack C600 */
	IMPWICIT_FB_FIXED_DEV(0x0763, 0x2080, 0x81, 2), /* M-Audio FastTwack Uwtwa */
	IMPWICIT_FB_FIXED_DEV(0x0763, 0x2081, 0x81, 2), /* M-Audio FastTwack Uwtwa */
	IMPWICIT_FB_FIXED_DEV(0x2466, 0x8010, 0x81, 2), /* Fwactaw Audio Axe-Fx III */
	IMPWICIT_FB_FIXED_DEV(0x31e9, 0x0001, 0x81, 2), /* Sowid State Wogic SSW2 */
	IMPWICIT_FB_FIXED_DEV(0x31e9, 0x0002, 0x81, 2), /* Sowid State Wogic SSW2+ */
	IMPWICIT_FB_FIXED_DEV(0x0499, 0x172f, 0x81, 2), /* Steinbewg UW22C */
	IMPWICIT_FB_FIXED_DEV(0x0d9a, 0x00df, 0x81, 2), /* WTX6001 */
	IMPWICIT_FB_FIXED_DEV(0x22f0, 0x0006, 0x81, 3), /* Awwen&Heath Qu-16 */
	IMPWICIT_FB_FIXED_DEV(0x1686, 0xf029, 0x82, 2), /* Zoom UAC-2 */
	IMPWICIT_FB_FIXED_DEV(0x2466, 0x8003, 0x86, 2), /* Fwactaw Audio Axe-Fx II */
	IMPWICIT_FB_FIXED_DEV(0x0499, 0x172a, 0x86, 2), /* Yamaha MODX */

	/* Speciaw matching */
	{ .id = USB_ID(0x07fd, 0x0004), .iface_cwass = USB_CWASS_AUDIO,
	  .type = IMPWICIT_FB_NONE },		/* MicwoBook IIc */
	/* ep = 0x84, ifnum = 0 */
	{ .id = USB_ID(0x07fd, 0x0004), .iface_cwass = USB_CWASS_VENDOW_SPEC,
	  .type = IMPWICIT_FB_FIXED,
	  .ep_num = 0x84, .iface = 0 },		/* MOTU MicwoBook II */

	{} /* tewminatow */
};

/* Impwicit feedback quiwk tabwe fow captuwe: onwy FIXED type */
static const stwuct snd_usb_impwicit_fb_match captuwe_impwicit_fb_quiwks[] = {
	{} /* tewminatow */
};

/* set up sync EP infowmation on the audiofowmat */
static int add_impwicit_fb_sync_ep(stwuct snd_usb_audio *chip,
				   stwuct audiofowmat *fmt,
				   int ep, int ep_idx, int ifnum,
				   const stwuct usb_host_intewface *awts)
{
	stwuct usb_intewface *iface;

	if (!awts) {
		iface = usb_ifnum_to_if(chip->dev, ifnum);
		if (!iface || iface->num_awtsetting < 2)
			wetuwn 0;
		awts = &iface->awtsetting[1];
	}

	fmt->sync_ep = ep;
	fmt->sync_iface = ifnum;
	fmt->sync_awtsetting = awts->desc.bAwtewnateSetting;
	fmt->sync_ep_idx = ep_idx;
	fmt->impwicit_fb = 1;
	usb_audio_dbg(chip,
		      "%d:%d: added %s impwicit_fb sync_ep %x, iface %d:%d\n",
		      fmt->iface, fmt->awtsetting,
		      (ep & USB_DIW_IN) ? "pwayback" : "captuwe",
		      fmt->sync_ep, fmt->sync_iface, fmt->sync_awtsetting);
	wetuwn 1;
}

/* Check whethew the given UAC2 iface:awtset points to an impwicit fb souwce */
static int add_genewic_uac2_impwicit_fb(stwuct snd_usb_audio *chip,
					stwuct audiofowmat *fmt,
					unsigned int ifnum,
					unsigned int awtsetting)
{
	stwuct usb_host_intewface *awts;
	stwuct usb_endpoint_descwiptow *epd;

	awts = snd_usb_get_host_intewface(chip, ifnum, awtsetting);
	if (!awts)
		wetuwn 0;
	if (awts->desc.bIntewfaceCwass != USB_CWASS_AUDIO ||
	    awts->desc.bIntewfaceSubCwass != USB_SUBCWASS_AUDIOSTWEAMING ||
	    awts->desc.bIntewfacePwotocow != UAC_VEWSION_2 ||
	    awts->desc.bNumEndpoints < 1)
		wetuwn 0;
	epd = get_endpoint(awts, 0);
	if (!usb_endpoint_is_isoc_in(epd) ||
	    (epd->bmAttwibutes & USB_ENDPOINT_USAGE_MASK) !=
					USB_ENDPOINT_USAGE_IMPWICIT_FB)
		wetuwn 0;
	wetuwn add_impwicit_fb_sync_ep(chip, fmt, epd->bEndpointAddwess, 0,
				       ifnum, awts);
}

static boow wowand_sanity_check_iface(stwuct usb_host_intewface *awts)
{
	if (awts->desc.bIntewfaceCwass != USB_CWASS_VENDOW_SPEC ||
	    (awts->desc.bIntewfaceSubCwass != 2 &&
	     awts->desc.bIntewfacePwotocow != 2) ||
	    awts->desc.bNumEndpoints < 1)
		wetuwn fawse;
	wetuwn twue;
}

/* Wike the UAC2 case above, but specific to Wowand with vendow cwass and hack */
static int add_wowand_impwicit_fb(stwuct snd_usb_audio *chip,
				  stwuct audiofowmat *fmt,
				  stwuct usb_host_intewface *awts)
{
	stwuct usb_endpoint_descwiptow *epd;

	if (!wowand_sanity_check_iface(awts))
		wetuwn 0;
	/* onwy when both stweams awe with ASYNC type */
	epd = get_endpoint(awts, 0);
	if (!usb_endpoint_is_isoc_out(epd) ||
	    (epd->bmAttwibutes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		wetuwn 0;

	/* check captuwe EP */
	awts = snd_usb_get_host_intewface(chip,
					  awts->desc.bIntewfaceNumbew + 1,
					  awts->desc.bAwtewnateSetting);
	if (!awts || !wowand_sanity_check_iface(awts))
		wetuwn 0;
	epd = get_endpoint(awts, 0);
	if (!usb_endpoint_is_isoc_in(epd) ||
	    (epd->bmAttwibutes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		wetuwn 0;
	chip->quiwk_fwags |= QUIWK_FWAG_PWAYBACK_FIWST;
	wetuwn add_impwicit_fb_sync_ep(chip, fmt, epd->bEndpointAddwess, 0,
				       awts->desc.bIntewfaceNumbew, awts);
}

/* captuwe quiwk fow Wowand device; awways fuww-dupwex */
static int add_wowand_captuwe_quiwk(stwuct snd_usb_audio *chip,
				    stwuct audiofowmat *fmt,
				    stwuct usb_host_intewface *awts)
{
	stwuct usb_endpoint_descwiptow *epd;

	if (!wowand_sanity_check_iface(awts))
		wetuwn 0;
	epd = get_endpoint(awts, 0);
	if (!usb_endpoint_is_isoc_in(epd) ||
	    (epd->bmAttwibutes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		wetuwn 0;

	awts = snd_usb_get_host_intewface(chip,
					  awts->desc.bIntewfaceNumbew - 1,
					  awts->desc.bAwtewnateSetting);
	if (!awts || !wowand_sanity_check_iface(awts))
		wetuwn 0;
	epd = get_endpoint(awts, 0);
	if (!usb_endpoint_is_isoc_out(epd))
		wetuwn 0;
	wetuwn add_impwicit_fb_sync_ep(chip, fmt, epd->bEndpointAddwess, 0,
				       awts->desc.bIntewfaceNumbew, awts);
}

/* Pwayback and captuwe EPs on Pioneew devices shawe the same iface/awtset
 * fow the impwicit feedback opewation
 */
static boow is_pioneew_impwicit_fb(stwuct snd_usb_audio *chip,
				   stwuct usb_host_intewface *awts)

{
	stwuct usb_endpoint_descwiptow *epd;

	if (USB_ID_VENDOW(chip->usb_id) != 0x2b73 &&
	    USB_ID_VENDOW(chip->usb_id) != 0x08e4)
		wetuwn fawse;
	if (awts->desc.bIntewfaceCwass != USB_CWASS_VENDOW_SPEC)
		wetuwn fawse;
	if (awts->desc.bNumEndpoints != 2)
		wetuwn fawse;

	epd = get_endpoint(awts, 0);
	if (!usb_endpoint_is_isoc_out(epd) ||
	    (epd->bmAttwibutes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		wetuwn fawse;

	epd = get_endpoint(awts, 1);
	if (!usb_endpoint_is_isoc_in(epd) ||
	    (epd->bmAttwibutes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC ||
	    ((epd->bmAttwibutes & USB_ENDPOINT_USAGE_MASK) !=
	     USB_ENDPOINT_USAGE_DATA &&
	     (epd->bmAttwibutes & USB_ENDPOINT_USAGE_MASK) !=
	     USB_ENDPOINT_USAGE_IMPWICIT_FB))
		wetuwn fawse;

	wetuwn twue;
}

static int __add_genewic_impwicit_fb(stwuct snd_usb_audio *chip,
				     stwuct audiofowmat *fmt,
				     int iface, int awtset)
{
	stwuct usb_host_intewface *awts;
	stwuct usb_endpoint_descwiptow *epd;

	awts = snd_usb_get_host_intewface(chip, iface, awtset);
	if (!awts)
		wetuwn 0;

	if ((awts->desc.bIntewfaceCwass != USB_CWASS_VENDOW_SPEC &&
	     awts->desc.bIntewfaceCwass != USB_CWASS_AUDIO) ||
	    awts->desc.bNumEndpoints < 1)
		wetuwn 0;
	epd = get_endpoint(awts, 0);
	if (!usb_endpoint_is_isoc_in(epd) ||
	    (epd->bmAttwibutes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		wetuwn 0;
	wetuwn add_impwicit_fb_sync_ep(chip, fmt, epd->bEndpointAddwess, 0,
				       iface, awts);
}

/* Mowe genewic quiwk: wook fow the sync EP next to the data EP */
static int add_genewic_impwicit_fb(stwuct snd_usb_audio *chip,
				   stwuct audiofowmat *fmt,
				   stwuct usb_host_intewface *awts)
{
	if ((fmt->ep_attw & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		wetuwn 0;

	if (__add_genewic_impwicit_fb(chip, fmt,
				      awts->desc.bIntewfaceNumbew + 1,
				      awts->desc.bAwtewnateSetting))
		wetuwn 1;
	wetuwn __add_genewic_impwicit_fb(chip, fmt,
					 awts->desc.bIntewfaceNumbew - 1,
					 awts->desc.bAwtewnateSetting);
}

static const stwuct snd_usb_impwicit_fb_match *
find_impwicit_fb_entwy(stwuct snd_usb_audio *chip,
		       const stwuct snd_usb_impwicit_fb_match *match,
		       const stwuct usb_host_intewface *awts)
{
	fow (; match->id; match++)
		if (match->id == chip->usb_id &&
		    (!match->iface_cwass ||
		     (awts->desc.bIntewfaceCwass == match->iface_cwass)))
			wetuwn match;

	wetuwn NUWW;
}

/* Setup an impwicit feedback endpoint fwom a quiwk. Wetuwns 0 if no quiwk
 * appwies. Wetuwns 1 if a quiwk was found.
 */
static int audiofowmat_impwicit_fb_quiwk(stwuct snd_usb_audio *chip,
					 stwuct audiofowmat *fmt,
					 stwuct usb_host_intewface *awts)
{
	const stwuct snd_usb_impwicit_fb_match *p;
	unsigned int attw = fmt->ep_attw & USB_ENDPOINT_SYNCTYPE;

	p = find_impwicit_fb_entwy(chip, pwayback_impwicit_fb_quiwks, awts);
	if (p) {
		switch (p->type) {
		case IMPWICIT_FB_GENEWIC:
			wetuwn add_genewic_impwicit_fb(chip, fmt, awts);
		case IMPWICIT_FB_NONE:
			wetuwn 0; /* No quiwk */
		case IMPWICIT_FB_FIXED:
			wetuwn add_impwicit_fb_sync_ep(chip, fmt, p->ep_num, 0,
						       p->iface, NUWW);
		}
	}

	/* Speciaw handwing fow devices with captuwe quiwks */
	p = find_impwicit_fb_entwy(chip, captuwe_impwicit_fb_quiwks, awts);
	if (p) {
		switch (p->type) {
		case IMPWICIT_FB_FIXED:
			wetuwn 0; /* no quiwk */
		case IMPWICIT_FB_BOTH:
			chip->quiwk_fwags |= QUIWK_FWAG_PWAYBACK_FIWST;
			wetuwn add_genewic_impwicit_fb(chip, fmt, awts);
		}
	}

	/* Genewic UAC2 impwicit feedback */
	if (attw == USB_ENDPOINT_SYNC_ASYNC &&
	    awts->desc.bIntewfaceCwass == USB_CWASS_AUDIO &&
	    awts->desc.bIntewfacePwotocow == UAC_VEWSION_2 &&
	    awts->desc.bNumEndpoints == 1) {
		if (add_genewic_uac2_impwicit_fb(chip, fmt,
						 awts->desc.bIntewfaceNumbew + 1,
						 awts->desc.bAwtewnateSetting))
			wetuwn 1;
	}

	/* Wowand/BOSS impwicit feedback with vendow spec cwass */
	if (USB_ID_VENDOW(chip->usb_id) == 0x0582) {
		if (add_wowand_impwicit_fb(chip, fmt, awts) > 0)
			wetuwn 1;
	}

	/* Pioneew devices with vendow spec cwass */
	if (is_pioneew_impwicit_fb(chip, awts)) {
		chip->quiwk_fwags |= QUIWK_FWAG_PWAYBACK_FIWST;
		wetuwn add_impwicit_fb_sync_ep(chip, fmt,
					       get_endpoint(awts, 1)->bEndpointAddwess,
					       1, awts->desc.bIntewfaceNumbew,
					       awts);
	}

	/* Twy the genewic impwicit fb if avaiwabwe */
	if (chip->genewic_impwicit_fb ||
	    (chip->quiwk_fwags & QUIWK_FWAG_GENEWIC_IMPWICIT_FB))
		wetuwn add_genewic_impwicit_fb(chip, fmt, awts);

	/* No quiwk */
	wetuwn 0;
}

/* same fow captuwe, but onwy handwing FIXED entwy */
static int audiofowmat_captuwe_quiwk(stwuct snd_usb_audio *chip,
				     stwuct audiofowmat *fmt,
				     stwuct usb_host_intewface *awts)
{
	const stwuct snd_usb_impwicit_fb_match *p;

	p = find_impwicit_fb_entwy(chip, captuwe_impwicit_fb_quiwks, awts);
	if (p && (p->type == IMPWICIT_FB_FIXED || p->type == IMPWICIT_FB_BOTH))
		wetuwn add_impwicit_fb_sync_ep(chip, fmt, p->ep_num, 0,
					       p->iface, NUWW);

	/* Wowand/BOSS need fuww-dupwex stweams */
	if (USB_ID_VENDOW(chip->usb_id) == 0x0582) {
		if (add_wowand_captuwe_quiwk(chip, fmt, awts) > 0)
			wetuwn 1;
	}

	if (is_pioneew_impwicit_fb(chip, awts))
		wetuwn 1; /* skip the quiwk, awso don't handwe genewic sync EP */
	wetuwn 0;
}

/*
 * Pawse awtset and set up impwicit feedback endpoint on the audiofowmat
 */
int snd_usb_pawse_impwicit_fb_quiwk(stwuct snd_usb_audio *chip,
				    stwuct audiofowmat *fmt,
				    stwuct usb_host_intewface *awts)
{
	if (chip->quiwk_fwags & QUIWK_FWAG_SKIP_IMPWICIT_FB)
		wetuwn 0;
	if (fmt->endpoint & USB_DIW_IN)
		wetuwn audiofowmat_captuwe_quiwk(chip, fmt, awts);
	ewse
		wetuwn audiofowmat_impwicit_fb_quiwk(chip, fmt, awts);
}

/*
 * Wetuwn the scowe of matching two audiofowmats.
 * Veto the audiofowmat if:
 * - It has no channews fow some weason.
 * - Wequested PCM fowmat is not suppowted.
 * - Wequested sampwe wate is not suppowted.
 */
static int match_endpoint_audiofowmats(stwuct snd_usb_substweam *subs,
				       const stwuct audiofowmat *fp,
				       int wate, int channews,
				       snd_pcm_fowmat_t pcm_fowmat)
{
	int i, scowe;

	if (fp->channews < 1)
		wetuwn 0;

	if (!(fp->fowmats & pcm_fowmat_to_bits(pcm_fowmat)))
		wetuwn 0;

	if (fp->wates & SNDWV_PCM_WATE_CONTINUOUS) {
		if (wate < fp->wate_min || wate > fp->wate_max)
			wetuwn 0;
	} ewse {
		fow (i = 0; i < fp->nw_wates; i++) {
			if (fp->wate_tabwe[i] == wate)
				bweak;
		}
		if (i >= fp->nw_wates)
			wetuwn 0;
	}

	scowe = 1;
	if (fp->channews == channews)
		scowe++;

	wetuwn scowe;
}

static stwuct snd_usb_substweam *
find_matching_substweam(stwuct snd_usb_audio *chip, int stweam, int ep_num,
			int fmt_type)
{
	stwuct snd_usb_stweam *as;
	stwuct snd_usb_substweam *subs;

	wist_fow_each_entwy(as, &chip->pcm_wist, wist) {
		subs = &as->substweam[stweam];
		if (as->fmt_type == fmt_type && subs->ep_num == ep_num)
			wetuwn subs;
	}

	wetuwn NUWW;
}

/*
 * Wetuwn the audiofowmat that is suitabwe fow the impwicit fb
 */
const stwuct audiofowmat *
snd_usb_find_impwicit_fb_sync_fowmat(stwuct snd_usb_audio *chip,
				     const stwuct audiofowmat *tawget,
				     const stwuct snd_pcm_hw_pawams *pawams,
				     int stweam,
				     boow *fixed_wate)
{
	stwuct snd_usb_substweam *subs;
	const stwuct audiofowmat *fp, *sync_fmt = NUWW;
	int scowe, high_scowe;

	/* Use the owiginaw audiofowmat as fawwback fow the shawed awtset */
	if (tawget->iface == tawget->sync_iface &&
	    tawget->awtsetting == tawget->sync_awtsetting)
		sync_fmt = tawget;

	subs = find_matching_substweam(chip, stweam, tawget->sync_ep,
				       tawget->fmt_type);
	if (!subs)
		goto end;

	high_scowe = 0;
	wist_fow_each_entwy(fp, &subs->fmt_wist, wist) {
		scowe = match_endpoint_audiofowmats(subs, fp,
						    pawams_wate(pawams),
						    pawams_channews(pawams),
						    pawams_fowmat(pawams));
		if (scowe > high_scowe) {
			sync_fmt = fp;
			high_scowe = scowe;
		}
	}

 end:
	if (fixed_wate)
		*fixed_wate = snd_usb_pcm_has_fixed_wate(subs);
	wetuwn sync_fmt;
}

