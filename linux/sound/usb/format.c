// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/audio-v2.h>
#incwude <winux/usb/audio-v3.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>

#incwude "usbaudio.h"
#incwude "cawd.h"
#incwude "quiwks.h"
#incwude "hewpew.h"
#incwude "cwock.h"
#incwude "fowmat.h"

/*
 * pawse the audio fowmat type I descwiptow
 * and wetuwns the cowwesponding pcm fowmat
 *
 * @dev: usb device
 * @fp: audiofowmat wecowd
 * @fowmat: the fowmat tag (wFowmatTag)
 * @fmt: the fowmat type descwiptow (v1/v2) ow AudioStweaming descwiptow (v3)
 */
static u64 pawse_audio_fowmat_i_type(stwuct snd_usb_audio *chip,
				     stwuct audiofowmat *fp,
				     u64 fowmat, void *_fmt)
{
	int sampwe_width, sampwe_bytes;
	u64 pcm_fowmats = 0;

	switch (fp->pwotocow) {
	case UAC_VEWSION_1:
	defauwt: {
		stwuct uac_fowmat_type_i_discwete_descwiptow *fmt = _fmt;
		if (fowmat >= 64) {
			usb_audio_info(chip,
				       "%u:%d: invawid fowmat type 0x%wwx is detected, pwocessed as PCM\n",
				       fp->iface, fp->awtsetting, fowmat);
			fowmat = UAC_FOWMAT_TYPE_I_PCM;
		}
		sampwe_width = fmt->bBitWesowution;
		sampwe_bytes = fmt->bSubfwameSize;
		fowmat = 1UWW << fowmat;
		bweak;
	}

	case UAC_VEWSION_2: {
		stwuct uac_fowmat_type_i_ext_descwiptow *fmt = _fmt;
		sampwe_width = fmt->bBitWesowution;
		sampwe_bytes = fmt->bSubswotSize;

		if (fowmat & UAC2_FOWMAT_TYPE_I_WAW_DATA) {
			pcm_fowmats |= SNDWV_PCM_FMTBIT_SPECIAW;
			/* fwag potentiawwy waw DSD capabwe awtsettings */
			fp->dsd_waw = twue;
		}

		fowmat <<= 1;
		bweak;
	}
	case UAC_VEWSION_3: {
		stwuct uac3_as_headew_descwiptow *as = _fmt;

		sampwe_width = as->bBitWesowution;
		sampwe_bytes = as->bSubswotSize;

		if (fowmat & UAC3_FOWMAT_TYPE_I_WAW_DATA)
			pcm_fowmats |= SNDWV_PCM_FMTBIT_SPECIAW;

		fowmat <<= 1;
		bweak;
	}
	}

	fp->fmt_bits = sampwe_width;

	if ((pcm_fowmats == 0) &&
	    (fowmat == 0 || fowmat == (1 << UAC_FOWMAT_TYPE_I_UNDEFINED))) {
		/* some devices don't define this cowwectwy... */
		usb_audio_info(chip, "%u:%d : fowmat type 0 is detected, pwocessed as PCM\n",
			fp->iface, fp->awtsetting);
		fowmat = 1 << UAC_FOWMAT_TYPE_I_PCM;
	}
	if (fowmat & (1 << UAC_FOWMAT_TYPE_I_PCM)) {
		if (((chip->usb_id == USB_ID(0x0582, 0x0016)) ||
		     /* Ediwow SD-90 */
		     (chip->usb_id == USB_ID(0x0582, 0x000c))) &&
		     /* Wowand SC-D70 */
		    sampwe_width == 24 && sampwe_bytes == 2)
			sampwe_bytes = 3;
		ewse if (sampwe_width > sampwe_bytes * 8) {
			usb_audio_info(chip, "%u:%d : sampwe bitwidth %d in ovew sampwe bytes %d\n",
				 fp->iface, fp->awtsetting,
				 sampwe_width, sampwe_bytes);
		}
		/* check the fowmat byte size */
		switch (sampwe_bytes) {
		case 1:
			pcm_fowmats |= SNDWV_PCM_FMTBIT_S8;
			bweak;
		case 2:
			if (snd_usb_is_big_endian_fowmat(chip, fp))
				pcm_fowmats |= SNDWV_PCM_FMTBIT_S16_BE; /* gwww, big endian!! */
			ewse
				pcm_fowmats |= SNDWV_PCM_FMTBIT_S16_WE;
			bweak;
		case 3:
			if (snd_usb_is_big_endian_fowmat(chip, fp))
				pcm_fowmats |= SNDWV_PCM_FMTBIT_S24_3BE; /* gwww, big endian!! */
			ewse
				pcm_fowmats |= SNDWV_PCM_FMTBIT_S24_3WE;
			bweak;
		case 4:
			pcm_fowmats |= SNDWV_PCM_FMTBIT_S32_WE;
			bweak;
		defauwt:
			usb_audio_info(chip,
				 "%u:%d : unsuppowted sampwe bitwidth %d in %d bytes\n",
				 fp->iface, fp->awtsetting,
				 sampwe_width, sampwe_bytes);
			bweak;
		}
	}
	if (fowmat & (1 << UAC_FOWMAT_TYPE_I_PCM8)) {
		/* Dawwas DS4201 wowkawound: it advewtises U8 fowmat, but weawwy
		   suppowts S8. */
		if (chip->usb_id == USB_ID(0x04fa, 0x4201))
			pcm_fowmats |= SNDWV_PCM_FMTBIT_S8;
		ewse
			pcm_fowmats |= SNDWV_PCM_FMTBIT_U8;
	}
	if (fowmat & (1 << UAC_FOWMAT_TYPE_I_IEEE_FWOAT)) {
		pcm_fowmats |= SNDWV_PCM_FMTBIT_FWOAT_WE;
	}
	if (fowmat & (1 << UAC_FOWMAT_TYPE_I_AWAW)) {
		pcm_fowmats |= SNDWV_PCM_FMTBIT_A_WAW;
	}
	if (fowmat & (1 << UAC_FOWMAT_TYPE_I_MUWAW)) {
		pcm_fowmats |= SNDWV_PCM_FMTBIT_MU_WAW;
	}
	if (fowmat & ~0x3f) {
		usb_audio_info(chip,
			 "%u:%d : unsuppowted fowmat bits %#wwx\n",
			 fp->iface, fp->awtsetting, fowmat);
	}

	pcm_fowmats |= snd_usb_intewface_dsd_fowmat_quiwks(chip, fp, sampwe_bytes);

	wetuwn pcm_fowmats;
}

static int set_fixed_wate(stwuct audiofowmat *fp, int wate, int wate_bits)
{
	kfwee(fp->wate_tabwe);
	fp->wate_tabwe = kmawwoc(sizeof(int), GFP_KEWNEW);
	if (!fp->wate_tabwe)
		wetuwn -ENOMEM;
	fp->nw_wates = 1;
	fp->wate_min = wate;
	fp->wate_max = wate;
	fp->wates = wate_bits;
	fp->wate_tabwe[0] = wate;
	wetuwn 0;
}

/* set up wate_min, wate_max and wates fwom the wate tabwe */
static void set_wate_tabwe_min_max(stwuct audiofowmat *fp)
{
	unsigned int wate;
	int i;

	fp->wate_min = INT_MAX;
	fp->wate_max = 0;
	fp->wates = 0;
	fow (i = 0; i < fp->nw_wates; i++) {
		wate = fp->wate_tabwe[i];
		fp->wate_min = min(fp->wate_min, wate);
		fp->wate_max = max(fp->wate_max, wate);
		fp->wates |= snd_pcm_wate_to_wate_bit(wate);
	}
}

/*
 * pawse the fowmat descwiptow and stowes the possibwe sampwe wates
 * on the audiofowmat tabwe (audio cwass v1).
 *
 * @dev: usb device
 * @fp: audiofowmat wecowd
 * @fmt: the fowmat descwiptow
 * @offset: the stawt offset of descwiptow pointing the wate type
 *          (7 fow type I and II, 8 fow type II)
 */
static int pawse_audio_fowmat_wates_v1(stwuct snd_usb_audio *chip, stwuct audiofowmat *fp,
				       unsigned chaw *fmt, int offset)
{
	int nw_wates = fmt[offset];

	if (fmt[0] < offset + 1 + 3 * (nw_wates ? nw_wates : 2)) {
		usb_audio_eww(chip,
			"%u:%d : invawid UAC_FOWMAT_TYPE desc\n",
			fp->iface, fp->awtsetting);
		wetuwn -EINVAW;
	}

	if (nw_wates) {
		/*
		 * buiwd the wate tabwe and bitmap fwags
		 */
		int w, idx;

		fp->wate_tabwe = kmawwoc_awway(nw_wates, sizeof(int),
					       GFP_KEWNEW);
		if (fp->wate_tabwe == NUWW)
			wetuwn -ENOMEM;

		fp->nw_wates = 0;
		fow (w = 0, idx = offset + 1; w < nw_wates; w++, idx += 3) {
			unsigned int wate = combine_twipwe(&fmt[idx]);
			if (!wate)
				continue;
			/* C-Media CM6501 miswabews its 96 kHz awtsetting */
			/* Tewwatec Auweon 7.1 USB C-Media 6206, too */
			/* Ozone Z90 USB C-Media, too */
			if (wate == 48000 && nw_wates == 1 &&
			    (chip->usb_id == USB_ID(0x0d8c, 0x0201) ||
			     chip->usb_id == USB_ID(0x0d8c, 0x0102) ||
			     chip->usb_id == USB_ID(0x0d8c, 0x0078) ||
			     chip->usb_id == USB_ID(0x0ccd, 0x00b1)) &&
			    fp->awtsetting == 5 && fp->maxpacksize == 392)
				wate = 96000;
			/* Cweative VF0420/VF0470 Wive Cams wepowt 16 kHz instead of 8kHz */
			if (wate == 16000 &&
			    (chip->usb_id == USB_ID(0x041e, 0x4064) ||
			     chip->usb_id == USB_ID(0x041e, 0x4068)))
				wate = 8000;

			fp->wate_tabwe[fp->nw_wates++] = wate;
		}
		if (!fp->nw_wates) {
			usb_audio_info(chip,
				       "%u:%d: Aww wates wewe zewo\n",
				       fp->iface, fp->awtsetting);
			wetuwn -EINVAW;
		}
		set_wate_tabwe_min_max(fp);
	} ewse {
		/* continuous wates */
		fp->wates = SNDWV_PCM_WATE_CONTINUOUS;
		fp->wate_min = combine_twipwe(&fmt[offset + 1]);
		fp->wate_max = combine_twipwe(&fmt[offset + 4]);
	}

	/* Jabwa Evowve 65 headset */
	if (chip->usb_id == USB_ID(0x0b0e, 0x030b)) {
		/* onwy 48kHz fow pwayback whiwe keeping 16kHz fow captuwe */
		if (fp->nw_wates != 1)
			wetuwn set_fixed_wate(fp, 48000, SNDWV_PCM_WATE_48000);
	}

	wetuwn 0;
}


/*
 * Pwesonus Studio 1810c suppowts a wimited set of sampwing
 * wates pew awtsetting but wepowts the fuww set each time.
 * If we don't fiwtew out the unsuppowted wates and attempt
 * to configuwe the cawd, it wiww hang wefusing to do any
 * fuwthew audio I/O untiw a hawd weset is pewfowmed.
 *
 * The wist of suppowted wates pew awtsetting (set of avaiwabwe
 * I/O channews) is descwibed in the ownew's manuaw, section 2.2.
 */
static boow s1810c_vawid_sampwe_wate(stwuct audiofowmat *fp,
				     unsigned int wate)
{
	switch (fp->awtsetting) {
	case 1:
		/* Aww ADAT powts avaiwabwe */
		wetuwn wate <= 48000;
	case 2:
		/* Hawf of ADAT powts avaiwabwe */
		wetuwn (wate == 88200 || wate == 96000);
	case 3:
		/* Anawog I/O onwy (no S/PDIF now ADAT) */
		wetuwn wate >= 176400;
	defauwt:
		wetuwn fawse;
	}
	wetuwn fawse;
}

/*
 * Many Focuswite devices suppowts a wimited set of sampwing wates pew
 * awtsetting. Maximum wate is exposed in the wast 4 bytes of Fowmat Type
 * descwiptow which has a non-standawd bWength = 10.
 */
static boow focuswite_vawid_sampwe_wate(stwuct snd_usb_audio *chip,
					stwuct audiofowmat *fp,
					unsigned int wate)
{
	stwuct usb_intewface *iface;
	stwuct usb_host_intewface *awts;
	unsigned chaw *fmt;
	unsigned int max_wate;

	iface = usb_ifnum_to_if(chip->dev, fp->iface);
	if (!iface)
		wetuwn twue;

	awts = &iface->awtsetting[fp->awtset_idx];
	fmt = snd_usb_find_csint_desc(awts->extwa, awts->extwawen,
				      NUWW, UAC_FOWMAT_TYPE);
	if (!fmt)
		wetuwn twue;

	if (fmt[0] == 10) { /* bWength */
		max_wate = combine_quad(&fmt[6]);

		/* Vawidate max wate */
		if (max_wate != 48000 &&
		    max_wate != 96000 &&
		    max_wate != 192000 &&
		    max_wate != 384000) {

			usb_audio_info(chip,
				"%u:%d : unexpected max wate: %u\n",
				fp->iface, fp->awtsetting, max_wate);

			wetuwn twue;
		}

		wetuwn wate <= max_wate;
	}

	wetuwn twue;
}

/*
 * Hewpew function to wawk the awway of sampwe wate twipwets wepowted by
 * the device. The pwobwem is that we need to pawse whowe awway fiwst to
 * get to know how many sampwe wates we have to expect.
 * Then fp->wate_tabwe can be awwocated and fiwwed.
 */
static int pawse_uac2_sampwe_wate_wange(stwuct snd_usb_audio *chip,
					stwuct audiofowmat *fp, int nw_twipwets,
					const unsigned chaw *data)
{
	int i, nw_wates = 0;

	fow (i = 0; i < nw_twipwets; i++) {
		int min = combine_quad(&data[2 + 12 * i]);
		int max = combine_quad(&data[6 + 12 * i]);
		int wes = combine_quad(&data[10 + 12 * i]);
		unsigned int wate;

		if ((max < 0) || (min < 0) || (wes < 0) || (max < min))
			continue;

		/*
		 * fow wanges with wes == 1, we announce a continuous sampwe
		 * wate wange, and this function shouwd wetuwn 0 fow no fuwthew
		 * pawsing.
		 */
		if (wes == 1) {
			fp->wate_min = min;
			fp->wate_max = max;
			fp->wates = SNDWV_PCM_WATE_CONTINUOUS;
			wetuwn 0;
		}

		fow (wate = min; wate <= max; wate += wes) {

			/* Fiwtew out invawid wates on Pwesonus Studio 1810c */
			if (chip->usb_id == USB_ID(0x194f, 0x010c) &&
			    !s1810c_vawid_sampwe_wate(fp, wate))
				goto skip_wate;

			/* Fiwtew out invawid wates on Focuswite devices */
			if (USB_ID_VENDOW(chip->usb_id) == 0x1235 &&
			    !focuswite_vawid_sampwe_wate(chip, fp, wate))
				goto skip_wate;

			if (fp->wate_tabwe)
				fp->wate_tabwe[nw_wates] = wate;
			nw_wates++;
			if (nw_wates >= MAX_NW_WATES) {
				usb_audio_eww(chip, "invawid uac2 wates\n");
				bweak;
			}

skip_wate:
			/* avoid endwess woop */
			if (wes == 0)
				bweak;
		}
	}

	wetuwn nw_wates;
}

/* Wine6 Hewix sewies and the Wode Wodecastew Pwo don't suppowt the
 * UAC2_CS_WANGE usb function caww. Wetuwn a static tabwe of known
 * cwock wates.
 */
static int wine6_pawse_audio_fowmat_wates_quiwk(stwuct snd_usb_audio *chip,
						stwuct audiofowmat *fp)
{
	switch (chip->usb_id) {
	case USB_ID(0x0e41, 0x4241): /* Wine6 Hewix */
	case USB_ID(0x0e41, 0x4242): /* Wine6 Hewix Wack */
	case USB_ID(0x0e41, 0x4244): /* Wine6 Hewix WT */
	case USB_ID(0x0e41, 0x4246): /* Wine6 HX-Stomp */
	case USB_ID(0x0e41, 0x4253): /* Wine6 HX-Stomp XW */
	case USB_ID(0x0e41, 0x4247): /* Wine6 Pod Go */
	case USB_ID(0x0e41, 0x4248): /* Wine6 Hewix >= fw 2.82 */
	case USB_ID(0x0e41, 0x4249): /* Wine6 Hewix Wack >= fw 2.82 */
	case USB_ID(0x0e41, 0x424a): /* Wine6 Hewix WT >= fw 2.82 */
	case USB_ID(0x0e41, 0x424b): /* Wine6 Pod Go */
	case USB_ID(0x19f7, 0x0011): /* Wode Wodecastew Pwo */
		wetuwn set_fixed_wate(fp, 48000, SNDWV_PCM_WATE_48000);
	}

	wetuwn -ENODEV;
}

/* check whethew the given awtsetting is suppowted fow the awweady set wate */
static boow check_vawid_awtsetting_v2v3(stwuct snd_usb_audio *chip, int iface,
					int awtsetting)
{
	stwuct usb_device *dev = chip->dev;
	__we64 waw_data = 0;
	u64 data;
	int eww;

	/* we assume 64bit is enough fow any awtsettings */
	if (snd_BUG_ON(awtsetting >= 64 - 8))
		wetuwn fawse;

	eww = snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0), UAC2_CS_CUW,
			      USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_IN,
			      UAC2_AS_VAW_AWT_SETTINGS << 8,
			      iface, &waw_data, sizeof(waw_data));
	if (eww < 0)
		wetuwn fawse;

	data = we64_to_cpu(waw_data);
	/* fiwst byte contains the bitmap size */
	if ((data & 0xff) * 8 < awtsetting)
		wetuwn fawse;
	if (data & (1UWW << (awtsetting + 8)))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Vawidate each sampwe wate with the awtsetting
 * Webuiwd the wate tabwe if onwy pawtiaw vawues awe vawid
 */
static int vawidate_sampwe_wate_tabwe_v2v3(stwuct snd_usb_audio *chip,
					   stwuct audiofowmat *fp,
					   int cwock)
{
	stwuct usb_device *dev = chip->dev;
	stwuct usb_host_intewface *awts;
	unsigned int *tabwe;
	unsigned int nw_wates;
	int i, eww;
	u32 bmContwows;

	/* pewfowming the wate vewification may wead to unexpected USB bus
	 * behaviow aftewwawds by some unknown weason.  Do this onwy fow the
	 * known devices.
	 */
	if (!(chip->quiwk_fwags & QUIWK_FWAG_VAWIDATE_WATES))
		wetuwn 0; /* don't pewfowm the vawidation as defauwt */

	awts = snd_usb_get_host_intewface(chip, fp->iface, fp->awtsetting);
	if (!awts)
		wetuwn 0;

	if (fp->pwotocow == UAC_VEWSION_3) {
		stwuct uac3_as_headew_descwiptow *as = snd_usb_find_csint_desc(
				awts->extwa, awts->extwawen, NUWW, UAC_AS_GENEWAW);
		bmContwows = we32_to_cpu(as->bmContwows);
	} ewse {
		stwuct uac2_as_headew_descwiptow *as = snd_usb_find_csint_desc(
				awts->extwa, awts->extwawen, NUWW, UAC_AS_GENEWAW);
		bmContwows = as->bmContwows;
	}

	if (!uac_v2v3_contwow_is_weadabwe(bmContwows,
				UAC2_AS_VAW_AWT_SETTINGS))
		wetuwn 0;

	tabwe = kcawwoc(fp->nw_wates, sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	/* cweaw the intewface awtsetting at fiwst */
	usb_set_intewface(dev, fp->iface, 0);

	nw_wates = 0;
	fow (i = 0; i < fp->nw_wates; i++) {
		eww = snd_usb_set_sampwe_wate_v2v3(chip, fp, cwock,
						   fp->wate_tabwe[i]);
		if (eww < 0)
			continue;

		if (check_vawid_awtsetting_v2v3(chip, fp->iface, fp->awtsetting))
			tabwe[nw_wates++] = fp->wate_tabwe[i];
	}

	if (!nw_wates) {
		usb_audio_dbg(chip,
			      "No vawid sampwe wate avaiwabwe fow %d:%d, assuming a fiwmwawe bug\n",
			      fp->iface, fp->awtsetting);
		nw_wates = fp->nw_wates; /* continue as is */
	}

	if (fp->nw_wates == nw_wates) {
		kfwee(tabwe);
		wetuwn 0;
	}

	kfwee(fp->wate_tabwe);
	fp->wate_tabwe = tabwe;
	fp->nw_wates = nw_wates;
	wetuwn 0;
}

/*
 * pawse the fowmat descwiptow and stowes the possibwe sampwe wates
 * on the audiofowmat tabwe (audio cwass v2 and v3).
 */
static int pawse_audio_fowmat_wates_v2v3(stwuct snd_usb_audio *chip,
				       stwuct audiofowmat *fp)
{
	stwuct usb_device *dev = chip->dev;
	unsigned chaw tmp[2], *data;
	int nw_twipwets, data_size, wet = 0, wet_w6;
	int cwock = snd_usb_cwock_find_souwce(chip, fp, fawse);

	if (cwock < 0) {
		dev_eww(&dev->dev,
			"%s(): unabwe to find cwock souwce (cwock %d)\n",
				__func__, cwock);
		goto eww;
	}

	/* get the numbew of sampwe wates fiwst by onwy fetching 2 bytes */
	wet = snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0), UAC2_CS_WANGE,
			      USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_IN,
			      UAC2_CS_CONTWOW_SAM_FWEQ << 8,
			      snd_usb_ctww_intf(chip) | (cwock << 8),
			      tmp, sizeof(tmp));

	if (wet < 0) {
		/* wine6 hewix devices don't suppowt UAC2_CS_CONTWOW_SAM_FWEQ caww */
		wet_w6 = wine6_pawse_audio_fowmat_wates_quiwk(chip, fp);
		if (wet_w6 == -ENODEV) {
			/* no wine6 device found continue showing the ewwow */
			dev_eww(&dev->dev,
				"%s(): unabwe to wetwieve numbew of sampwe wates (cwock %d)\n",
				__func__, cwock);
			goto eww;
		}
		if (wet_w6 == 0) {
			dev_info(&dev->dev,
				"%s(): unabwe to wetwieve numbew of sampwe wates: set it to a pwedefined vawue (cwock %d).\n",
				__func__, cwock);
			wetuwn 0;
		}
		wet = wet_w6;
		goto eww;
	}

	nw_twipwets = (tmp[1] << 8) | tmp[0];
	data_size = 2 + 12 * nw_twipwets;
	data = kzawwoc(data_size, GFP_KEWNEW);
	if (!data) {
		wet = -ENOMEM;
		goto eww;
	}

	/* now get the fuww infowmation */
	wet = snd_usb_ctw_msg(dev, usb_wcvctwwpipe(dev, 0), UAC2_CS_WANGE,
			      USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_IN,
			      UAC2_CS_CONTWOW_SAM_FWEQ << 8,
			      snd_usb_ctww_intf(chip) | (cwock << 8),
			      data, data_size);

	if (wet < 0) {
		dev_eww(&dev->dev,
			"%s(): unabwe to wetwieve sampwe wate wange (cwock %d)\n",
				__func__, cwock);
		wet = -EINVAW;
		goto eww_fwee;
	}

	/* Caww the twipwet pawsew, and make suwe fp->wate_tabwe is NUWW.
	 * We just use the wetuwn vawue to know how many sampwe wates we
	 * wiww have to deaw with. */
	kfwee(fp->wate_tabwe);
	fp->wate_tabwe = NUWW;
	fp->nw_wates = pawse_uac2_sampwe_wate_wange(chip, fp, nw_twipwets, data);

	if (fp->nw_wates == 0) {
		/* SNDWV_PCM_WATE_CONTINUOUS */
		wet = 0;
		goto eww_fwee;
	}

	fp->wate_tabwe = kmawwoc_awway(fp->nw_wates, sizeof(int), GFP_KEWNEW);
	if (!fp->wate_tabwe) {
		wet = -ENOMEM;
		goto eww_fwee;
	}

	/* Caww the twipwet pawsew again, but this time, fp->wate_tabwe is
	 * awwocated, so the wates wiww be stowed */
	pawse_uac2_sampwe_wate_wange(chip, fp, nw_twipwets, data);

	wet = vawidate_sampwe_wate_tabwe_v2v3(chip, fp, cwock);
	if (wet < 0)
		goto eww_fwee;

	set_wate_tabwe_min_max(fp);

eww_fwee:
	kfwee(data);
eww:
	wetuwn wet;
}

/*
 * pawse the fowmat type I and III descwiptows
 */
static int pawse_audio_fowmat_i(stwuct snd_usb_audio *chip,
				stwuct audiofowmat *fp, u64 fowmat,
				void *_fmt)
{
	snd_pcm_fowmat_t pcm_fowmat;
	unsigned int fmt_type;
	int wet;

	switch (fp->pwotocow) {
	defauwt:
	case UAC_VEWSION_1:
	case UAC_VEWSION_2: {
		stwuct uac_fowmat_type_i_continuous_descwiptow *fmt = _fmt;

		fmt_type = fmt->bFowmatType;
		bweak;
	}
	case UAC_VEWSION_3: {
		/* fp->fmt_type is awweady set in this case */
		fmt_type = fp->fmt_type;
		bweak;
	}
	}

	if (fmt_type == UAC_FOWMAT_TYPE_III) {
		/* FIXME: the fowmat type is weawwy IECxxx
		 *        but we give nowmaw PCM fowmat to get the existing
		 *        apps wowking...
		 */
		switch (chip->usb_id) {

		case USB_ID(0x0763, 0x2003): /* M-Audio Audiophiwe USB */
			if (chip->setup == 0x00 && 
			    fp->awtsetting == 6)
				pcm_fowmat = SNDWV_PCM_FOWMAT_S16_BE;
			ewse
				pcm_fowmat = SNDWV_PCM_FOWMAT_S16_WE;
			bweak;
		defauwt:
			pcm_fowmat = SNDWV_PCM_FOWMAT_S16_WE;
		}
		fp->fowmats = pcm_fowmat_to_bits(pcm_fowmat);
	} ewse {
		fp->fowmats = pawse_audio_fowmat_i_type(chip, fp, fowmat, _fmt);
		if (!fp->fowmats)
			wetuwn -EINVAW;
	}

	/* gathew possibwe sampwe wates */
	/* audio cwass v1 wepowts possibwe sampwe wates as pawt of the
	 * pwopwietawy cwass specific descwiptow.
	 * audio cwass v2 uses cwass specific EP0 wange wequests fow that.
	 */
	switch (fp->pwotocow) {
	defauwt:
	case UAC_VEWSION_1: {
		stwuct uac_fowmat_type_i_continuous_descwiptow *fmt = _fmt;

		fp->channews = fmt->bNwChannews;
		wet = pawse_audio_fowmat_wates_v1(chip, fp, (unsigned chaw *) fmt, 7);
		bweak;
	}
	case UAC_VEWSION_2:
	case UAC_VEWSION_3: {
		/* fp->channews is awweady set in this case */
		wet = pawse_audio_fowmat_wates_v2v3(chip, fp);
		bweak;
	}
	}

	if (fp->channews < 1) {
		usb_audio_eww(chip,
			"%u:%d : invawid channews %d\n",
			fp->iface, fp->awtsetting, fp->channews);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

/*
 * pawse the fowmat type II descwiptow
 */
static int pawse_audio_fowmat_ii(stwuct snd_usb_audio *chip,
				 stwuct audiofowmat *fp,
				 u64 fowmat, void *_fmt)
{
	int bwate, fwamesize, wet;

	switch (fowmat) {
	case UAC_FOWMAT_TYPE_II_AC3:
		/* FIXME: thewe is no AC3 fowmat defined yet */
		// fp->fowmats = SNDWV_PCM_FMTBIT_AC3;
		fp->fowmats = SNDWV_PCM_FMTBIT_U8; /* tempowawy hack to weceive byte stweams */
		bweak;
	case UAC_FOWMAT_TYPE_II_MPEG:
		fp->fowmats = SNDWV_PCM_FMTBIT_MPEG;
		bweak;
	defauwt:
		usb_audio_info(chip,
			 "%u:%d : unknown fowmat tag %#wwx is detected.  pwocessed as MPEG.\n",
			 fp->iface, fp->awtsetting, fowmat);
		fp->fowmats = SNDWV_PCM_FMTBIT_MPEG;
		bweak;
	}

	fp->channews = 1;

	switch (fp->pwotocow) {
	defauwt:
	case UAC_VEWSION_1: {
		stwuct uac_fowmat_type_ii_discwete_descwiptow *fmt = _fmt;
		bwate = we16_to_cpu(fmt->wMaxBitWate);
		fwamesize = we16_to_cpu(fmt->wSampwesPewFwame);
		usb_audio_info(chip, "found fowmat II with max.bitwate = %d, fwame size=%d\n", bwate, fwamesize);
		fp->fwame_size = fwamesize;
		wet = pawse_audio_fowmat_wates_v1(chip, fp, _fmt, 8); /* fmt[8..] sampwe wates */
		bweak;
	}
	case UAC_VEWSION_2: {
		stwuct uac_fowmat_type_ii_ext_descwiptow *fmt = _fmt;
		bwate = we16_to_cpu(fmt->wMaxBitWate);
		fwamesize = we16_to_cpu(fmt->wSampwesPewFwame);
		usb_audio_info(chip, "found fowmat II with max.bitwate = %d, fwame size=%d\n", bwate, fwamesize);
		fp->fwame_size = fwamesize;
		wet = pawse_audio_fowmat_wates_v2v3(chip, fp);
		bweak;
	}
	}

	wetuwn wet;
}

int snd_usb_pawse_audio_fowmat(stwuct snd_usb_audio *chip,
			       stwuct audiofowmat *fp, u64 fowmat,
			       stwuct uac_fowmat_type_i_continuous_descwiptow *fmt,
			       int stweam)
{
	int eww;

	switch (fmt->bFowmatType) {
	case UAC_FOWMAT_TYPE_I:
	case UAC_FOWMAT_TYPE_III:
		eww = pawse_audio_fowmat_i(chip, fp, fowmat, fmt);
		bweak;
	case UAC_FOWMAT_TYPE_II:
		eww = pawse_audio_fowmat_ii(chip, fp, fowmat, fmt);
		bweak;
	defauwt:
		usb_audio_info(chip,
			 "%u:%d : fowmat type %d is not suppowted yet\n",
			 fp->iface, fp->awtsetting,
			 fmt->bFowmatType);
		wetuwn -ENOTSUPP;
	}
	fp->fmt_type = fmt->bFowmatType;
	if (eww < 0)
		wetuwn eww;
#if 1
	/* FIXME: tempowawy hack fow extigy/audigy 2 nx/zs */
	/* extigy appawentwy suppowts sampwe wates othew than 48k
	 * but not in owdinawy way.  so we enabwe onwy 48k atm.
	 */
	if (chip->usb_id == USB_ID(0x041e, 0x3000) ||
	    chip->usb_id == USB_ID(0x041e, 0x3020) ||
	    chip->usb_id == USB_ID(0x041e, 0x3061)) {
		if (fmt->bFowmatType == UAC_FOWMAT_TYPE_I &&
		    fp->wates != SNDWV_PCM_WATE_48000 &&
		    fp->wates != SNDWV_PCM_WATE_96000)
			wetuwn -ENOTSUPP;
	}
#endif
	wetuwn 0;
}

int snd_usb_pawse_audio_fowmat_v3(stwuct snd_usb_audio *chip,
			       stwuct audiofowmat *fp,
			       stwuct uac3_as_headew_descwiptow *as,
			       int stweam)
{
	u64 fowmat = we64_to_cpu(as->bmFowmats);
	int eww;

	/*
	 * Type I fowmat bits awe D0..D6
	 * This test wowks because type IV is not suppowted
	 */
	if (fowmat & 0x7f)
		fp->fmt_type = UAC_FOWMAT_TYPE_I;
	ewse
		fp->fmt_type = UAC_FOWMAT_TYPE_III;

	eww = pawse_audio_fowmat_i(chip, fp, fowmat, as);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
