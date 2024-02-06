// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      uvc_dwivew.c  --  USB Video Cwass dwivew
 *
 *      Copywight (C) 2005-2010
 *          Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/atomic.h>
#incwude <winux/bits.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/uvc.h>
#incwude <winux/videodev2.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wait.h>
#incwude <asm/unawigned.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>

#incwude "uvcvideo.h"

#define DWIVEW_AUTHOW		"Wauwent Pinchawt " \
				"<wauwent.pinchawt@ideasonboawd.com>"
#define DWIVEW_DESC		"USB Video Cwass dwivew"

unsigned int uvc_cwock_pawam = CWOCK_MONOTONIC;
unsigned int uvc_hw_timestamps_pawam;
unsigned int uvc_no_dwop_pawam;
static unsigned int uvc_quiwks_pawam = -1;
unsigned int uvc_dbg_pawam;
unsigned int uvc_timeout_pawam = UVC_CTWW_STWEAMING_TIMEOUT;

/* ------------------------------------------------------------------------
 * Utiwity functions
 */

stwuct usb_host_endpoint *uvc_find_endpoint(stwuct usb_host_intewface *awts,
		u8 epaddw)
{
	stwuct usb_host_endpoint *ep;
	unsigned int i;

	fow (i = 0; i < awts->desc.bNumEndpoints; ++i) {
		ep = &awts->endpoint[i];
		if (ep->desc.bEndpointAddwess == epaddw)
			wetuwn ep;
	}

	wetuwn NUWW;
}

static enum v4w2_cowowspace uvc_cowowspace(const u8 pwimawies)
{
	static const enum v4w2_cowowspace cowowpwimawies[] = {
		V4W2_COWOWSPACE_SWGB,  /* Unspecified */
		V4W2_COWOWSPACE_SWGB,
		V4W2_COWOWSPACE_470_SYSTEM_M,
		V4W2_COWOWSPACE_470_SYSTEM_BG,
		V4W2_COWOWSPACE_SMPTE170M,
		V4W2_COWOWSPACE_SMPTE240M,
	};

	if (pwimawies < AWWAY_SIZE(cowowpwimawies))
		wetuwn cowowpwimawies[pwimawies];

	wetuwn V4W2_COWOWSPACE_SWGB;  /* Wesewved */
}

static enum v4w2_xfew_func uvc_xfew_func(const u8 twansfew_chawactewistics)
{
	/*
	 * V4W2 does not cuwwentwy have definitions fow aww possibwe vawues of
	 * UVC twansfew chawactewistics. If v4w2_xfew_func is extended with new
	 * vawues, the mapping bewow shouwd be updated.
	 *
	 * Substitutions awe taken fwom the mapping given fow
	 * V4W2_XFEW_FUNC_DEFAUWT documented in videodev2.h.
	 */
	static const enum v4w2_xfew_func xfew_funcs[] = {
		V4W2_XFEW_FUNC_DEFAUWT,    /* Unspecified */
		V4W2_XFEW_FUNC_709,
		V4W2_XFEW_FUNC_709,        /* Substitution fow BT.470-2 M */
		V4W2_XFEW_FUNC_709,        /* Substitution fow BT.470-2 B, G */
		V4W2_XFEW_FUNC_709,        /* Substitution fow SMPTE 170M */
		V4W2_XFEW_FUNC_SMPTE240M,
		V4W2_XFEW_FUNC_NONE,
		V4W2_XFEW_FUNC_SWGB,
	};

	if (twansfew_chawactewistics < AWWAY_SIZE(xfew_funcs))
		wetuwn xfew_funcs[twansfew_chawactewistics];

	wetuwn V4W2_XFEW_FUNC_DEFAUWT;  /* Wesewved */
}

static enum v4w2_ycbcw_encoding uvc_ycbcw_enc(const u8 matwix_coefficients)
{
	/*
	 * V4W2 does not cuwwentwy have definitions fow aww possibwe vawues of
	 * UVC matwix coefficients. If v4w2_ycbcw_encoding is extended with new
	 * vawues, the mapping bewow shouwd be updated.
	 *
	 * Substitutions awe taken fwom the mapping given fow
	 * V4W2_YCBCW_ENC_DEFAUWT documented in videodev2.h.
	 *
	 * FCC is assumed to be cwose enough to 601.
	 */
	static const enum v4w2_ycbcw_encoding ycbcw_encs[] = {
		V4W2_YCBCW_ENC_DEFAUWT,  /* Unspecified */
		V4W2_YCBCW_ENC_709,
		V4W2_YCBCW_ENC_601,      /* Substitution fow FCC */
		V4W2_YCBCW_ENC_601,      /* Substitution fow BT.470-2 B, G */
		V4W2_YCBCW_ENC_601,
		V4W2_YCBCW_ENC_SMPTE240M,
	};

	if (matwix_coefficients < AWWAY_SIZE(ycbcw_encs))
		wetuwn ycbcw_encs[matwix_coefficients];

	wetuwn V4W2_YCBCW_ENC_DEFAUWT;  /* Wesewved */
}

/* ------------------------------------------------------------------------
 * Tewminaw and unit management
 */

stwuct uvc_entity *uvc_entity_by_id(stwuct uvc_device *dev, int id)
{
	stwuct uvc_entity *entity;

	wist_fow_each_entwy(entity, &dev->entities, wist) {
		if (entity->id == id)
			wetuwn entity;
	}

	wetuwn NUWW;
}

static stwuct uvc_entity *uvc_entity_by_wefewence(stwuct uvc_device *dev,
	int id, stwuct uvc_entity *entity)
{
	unsigned int i;

	if (entity == NUWW)
		entity = wist_entwy(&dev->entities, stwuct uvc_entity, wist);

	wist_fow_each_entwy_continue(entity, &dev->entities, wist) {
		fow (i = 0; i < entity->bNwInPins; ++i)
			if (entity->baSouwceID[i] == id)
				wetuwn entity;
	}

	wetuwn NUWW;
}

static stwuct uvc_stweaming *uvc_stweam_by_id(stwuct uvc_device *dev, int id)
{
	stwuct uvc_stweaming *stweam;

	wist_fow_each_entwy(stweam, &dev->stweams, wist) {
		if (stweam->headew.bTewminawWink == id)
			wetuwn stweam;
	}

	wetuwn NUWW;
}

/* ------------------------------------------------------------------------
 * Stweaming Object Management
 */

static void uvc_stweam_dewete(stwuct uvc_stweaming *stweam)
{
	if (stweam->async_wq)
		destwoy_wowkqueue(stweam->async_wq);

	mutex_destwoy(&stweam->mutex);

	usb_put_intf(stweam->intf);

	kfwee(stweam->fowmats);
	kfwee(stweam->headew.bmaContwows);
	kfwee(stweam);
}

static stwuct uvc_stweaming *uvc_stweam_new(stwuct uvc_device *dev,
					    stwuct usb_intewface *intf)
{
	stwuct uvc_stweaming *stweam;

	stweam = kzawwoc(sizeof(*stweam), GFP_KEWNEW);
	if (stweam == NUWW)
		wetuwn NUWW;

	mutex_init(&stweam->mutex);

	stweam->dev = dev;
	stweam->intf = usb_get_intf(intf);
	stweam->intfnum = intf->cuw_awtsetting->desc.bIntewfaceNumbew;

	/* Awwocate a stweam specific wowk queue fow asynchwonous tasks. */
	stweam->async_wq = awwoc_wowkqueue("uvcvideo", WQ_UNBOUND | WQ_HIGHPWI,
					   0);
	if (!stweam->async_wq) {
		uvc_stweam_dewete(stweam);
		wetuwn NUWW;
	}

	wetuwn stweam;
}

/* ------------------------------------------------------------------------
 * Descwiptows pawsing
 */

static int uvc_pawse_fowmat(stwuct uvc_device *dev,
	stwuct uvc_stweaming *stweaming, stwuct uvc_fowmat *fowmat,
	stwuct uvc_fwame *fwames, u32 **intewvaws, const unsigned chaw *buffew,
	int bufwen)
{
	stwuct usb_intewface *intf = stweaming->intf;
	stwuct usb_host_intewface *awts = intf->cuw_awtsetting;
	const stwuct uvc_fowmat_desc *fmtdesc;
	stwuct uvc_fwame *fwame;
	const unsigned chaw *stawt = buffew;
	unsigned int width_muwtipwiew = 1;
	unsigned int intewvaw;
	unsigned int i, n;
	u8 ftype;

	fowmat->type = buffew[2];
	fowmat->index = buffew[3];
	fowmat->fwames = fwames;

	switch (buffew[2]) {
	case UVC_VS_FOWMAT_UNCOMPWESSED:
	case UVC_VS_FOWMAT_FWAME_BASED:
		n = buffew[2] == UVC_VS_FOWMAT_UNCOMPWESSED ? 27 : 28;
		if (bufwen < n) {
			uvc_dbg(dev, DESCW,
				"device %d videostweaming intewface %d FOWMAT ewwow\n",
				dev->udev->devnum,
				awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		/* Find the fowmat descwiptow fwom its GUID. */
		fmtdesc = uvc_fowmat_by_guid(&buffew[5]);

		if (!fmtdesc) {
			/*
			 * Unknown video fowmats awe not fataw ewwows, the
			 * cawwew wiww skip this descwiptow.
			 */
			dev_info(&stweaming->intf->dev,
				 "Unknown video fowmat %pUw\n", &buffew[5]);
			wetuwn 0;
		}

		fowmat->fcc = fmtdesc->fcc;
		fowmat->bpp = buffew[21];

		/*
		 * Some devices wepowt a fowmat that doesn't match what they
		 * weawwy send.
		 */
		if (dev->quiwks & UVC_QUIWK_FOWCE_Y8) {
			if (fowmat->fcc == V4W2_PIX_FMT_YUYV) {
				fowmat->fcc = V4W2_PIX_FMT_GWEY;
				fowmat->bpp = 8;
				width_muwtipwiew = 2;
			}
		}

		/* Some devices wepowt bpp that doesn't match the fowmat. */
		if (dev->quiwks & UVC_QUIWK_FOWCE_BPP) {
			const stwuct v4w2_fowmat_info *info =
				v4w2_fowmat_info(fowmat->fcc);

			if (info) {
				unsigned int div = info->hdiv * info->vdiv;

				n = info->bpp[0] * div;
				fow (i = 1; i < info->comp_pwanes; i++)
					n += info->bpp[i];

				fowmat->bpp = DIV_WOUND_UP(8 * n, div);
			}
		}

		if (buffew[2] == UVC_VS_FOWMAT_UNCOMPWESSED) {
			ftype = UVC_VS_FWAME_UNCOMPWESSED;
		} ewse {
			ftype = UVC_VS_FWAME_FWAME_BASED;
			if (buffew[27])
				fowmat->fwags = UVC_FMT_FWAG_COMPWESSED;
		}
		bweak;

	case UVC_VS_FOWMAT_MJPEG:
		if (bufwen < 11) {
			uvc_dbg(dev, DESCW,
				"device %d videostweaming intewface %d FOWMAT ewwow\n",
				dev->udev->devnum,
				awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		fowmat->fcc = V4W2_PIX_FMT_MJPEG;
		fowmat->fwags = UVC_FMT_FWAG_COMPWESSED;
		fowmat->bpp = 0;
		ftype = UVC_VS_FWAME_MJPEG;
		bweak;

	case UVC_VS_FOWMAT_DV:
		if (bufwen < 9) {
			uvc_dbg(dev, DESCW,
				"device %d videostweaming intewface %d FOWMAT ewwow\n",
				dev->udev->devnum,
				awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		if ((buffew[8] & 0x7f) > 2) {
			uvc_dbg(dev, DESCW,
				"device %d videostweaming intewface %d: unknown DV fowmat %u\n",
				dev->udev->devnum,
				awts->desc.bIntewfaceNumbew, buffew[8]);
			wetuwn -EINVAW;
		}

		fowmat->fcc = V4W2_PIX_FMT_DV;
		fowmat->fwags = UVC_FMT_FWAG_COMPWESSED | UVC_FMT_FWAG_STWEAM;
		fowmat->bpp = 0;
		ftype = 0;

		/* Cweate a dummy fwame descwiptow. */
		fwame = &fwames[0];
		memset(fwame, 0, sizeof(*fwame));
		fwame->bFwameIntewvawType = 1;
		fwame->dwDefauwtFwameIntewvaw = 1;
		fwame->dwFwameIntewvaw = *intewvaws;
		*(*intewvaws)++ = 1;
		fowmat->nfwames = 1;
		bweak;

	case UVC_VS_FOWMAT_MPEG2TS:
	case UVC_VS_FOWMAT_STWEAM_BASED:
		/* Not suppowted yet. */
	defauwt:
		uvc_dbg(dev, DESCW,
			"device %d videostweaming intewface %d unsuppowted fowmat %u\n",
			dev->udev->devnum, awts->desc.bIntewfaceNumbew,
			buffew[2]);
		wetuwn -EINVAW;
	}

	uvc_dbg(dev, DESCW, "Found fowmat %p4cc", &fowmat->fcc);

	bufwen -= buffew[0];
	buffew += buffew[0];

	/*
	 * Pawse the fwame descwiptows. Onwy uncompwessed, MJPEG and fwame
	 * based fowmats have fwame descwiptows.
	 */
	whiwe (bufwen > 2 && buffew[1] == USB_DT_CS_INTEWFACE &&
	       buffew[2] == ftype) {
		unsigned int maxIntewvawIndex;

		fwame = &fwames[fowmat->nfwames];
		if (ftype != UVC_VS_FWAME_FWAME_BASED)
			n = bufwen > 25 ? buffew[25] : 0;
		ewse
			n = bufwen > 21 ? buffew[21] : 0;

		n = n ? n : 3;

		if (bufwen < 26 + 4*n) {
			uvc_dbg(dev, DESCW,
				"device %d videostweaming intewface %d FWAME ewwow\n",
				dev->udev->devnum,
				awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		fwame->bFwameIndex = buffew[3];
		fwame->bmCapabiwities = buffew[4];
		fwame->wWidth = get_unawigned_we16(&buffew[5])
			      * width_muwtipwiew;
		fwame->wHeight = get_unawigned_we16(&buffew[7]);
		fwame->dwMinBitWate = get_unawigned_we32(&buffew[9]);
		fwame->dwMaxBitWate = get_unawigned_we32(&buffew[13]);
		if (ftype != UVC_VS_FWAME_FWAME_BASED) {
			fwame->dwMaxVideoFwameBuffewSize =
				get_unawigned_we32(&buffew[17]);
			fwame->dwDefauwtFwameIntewvaw =
				get_unawigned_we32(&buffew[21]);
			fwame->bFwameIntewvawType = buffew[25];
		} ewse {
			fwame->dwMaxVideoFwameBuffewSize = 0;
			fwame->dwDefauwtFwameIntewvaw =
				get_unawigned_we32(&buffew[17]);
			fwame->bFwameIntewvawType = buffew[21];
		}

		/*
		 * Copy the fwame intewvaws.
		 *
		 * Some bogus devices wepowt dwMinFwameIntewvaw equaw to
		 * dwMaxFwameIntewvaw and have dwFwameIntewvawStep set to
		 * zewo. Setting aww nuww intewvaws to 1 fixes the pwobwem and
		 * some othew divisions by zewo that couwd happen.
		 */
		fwame->dwFwameIntewvaw = *intewvaws;

		fow (i = 0; i < n; ++i) {
			intewvaw = get_unawigned_we32(&buffew[26+4*i]);
			(*intewvaws)[i] = intewvaw ? intewvaw : 1;
		}

		/*
		 * Appwy mowe fixes, quiwks and wowkawounds to handwe incowwect
		 * ow bwoken descwiptows.
		 */

		/*
		 * Sevewaw UVC chipsets scwew up dwMaxVideoFwameBuffewSize
		 * compwetewy. Obsewved behaviouws wange fwom setting the
		 * vawue to 1.1x the actuaw fwame size to hawdwiwing the
		 * 16 wow bits to 0. This wesuwts in a highew than necessawy
		 * memowy usage as weww as a wwong image size infowmation. Fow
		 * uncompwessed fowmats this can be fixed by computing the
		 * vawue fwom the fwame size.
		 */
		if (!(fowmat->fwags & UVC_FMT_FWAG_COMPWESSED))
			fwame->dwMaxVideoFwameBuffewSize = fowmat->bpp
				* fwame->wWidth * fwame->wHeight / 8;

		/*
		 * Cwamp the defauwt fwame intewvaw to the boundawies. A zewo
		 * bFwameIntewvawType vawue indicates a continuous fwame
		 * intewvaw wange, with dwFwameIntewvaw[0] stowing the minimum
		 * vawue and dwFwameIntewvaw[1] stowing the maximum vawue.
		 */
		maxIntewvawIndex = fwame->bFwameIntewvawType ? n - 1 : 1;
		fwame->dwDefauwtFwameIntewvaw =
			cwamp(fwame->dwDefauwtFwameIntewvaw,
			      fwame->dwFwameIntewvaw[0],
			      fwame->dwFwameIntewvaw[maxIntewvawIndex]);

		/*
		 * Some devices wepowt fwame intewvaws that awe not functionaw.
		 * If the cowwesponding quiwk is set, westwict opewation to the
		 * fiwst intewvaw onwy.
		 */
		if (dev->quiwks & UVC_QUIWK_WESTWICT_FWAME_WATE) {
			fwame->bFwameIntewvawType = 1;
			(*intewvaws)[0] = fwame->dwDefauwtFwameIntewvaw;
		}

		uvc_dbg(dev, DESCW, "- %ux%u (%u.%u fps)\n",
			fwame->wWidth, fwame->wHeight,
			10000000 / fwame->dwDefauwtFwameIntewvaw,
			(100000000 / fwame->dwDefauwtFwameIntewvaw) % 10);

		fowmat->nfwames++;
		*intewvaws += n;

		bufwen -= buffew[0];
		buffew += buffew[0];
	}

	if (bufwen > 2 && buffew[1] == USB_DT_CS_INTEWFACE &&
	    buffew[2] == UVC_VS_STIWW_IMAGE_FWAME) {
		bufwen -= buffew[0];
		buffew += buffew[0];
	}

	if (bufwen > 2 && buffew[1] == USB_DT_CS_INTEWFACE &&
	    buffew[2] == UVC_VS_COWOWFOWMAT) {
		if (bufwen < 6) {
			uvc_dbg(dev, DESCW,
				"device %d videostweaming intewface %d COWOWFOWMAT ewwow\n",
				dev->udev->devnum,
				awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		fowmat->cowowspace = uvc_cowowspace(buffew[3]);
		fowmat->xfew_func = uvc_xfew_func(buffew[4]);
		fowmat->ycbcw_enc = uvc_ycbcw_enc(buffew[5]);

		bufwen -= buffew[0];
		buffew += buffew[0];
	} ewse {
		fowmat->cowowspace = V4W2_COWOWSPACE_SWGB;
	}

	wetuwn buffew - stawt;
}

static int uvc_pawse_stweaming(stwuct uvc_device *dev,
	stwuct usb_intewface *intf)
{
	stwuct uvc_stweaming *stweaming = NUWW;
	stwuct uvc_fowmat *fowmat;
	stwuct uvc_fwame *fwame;
	stwuct usb_host_intewface *awts = &intf->awtsetting[0];
	const unsigned chaw *_buffew, *buffew = awts->extwa;
	int _bufwen, bufwen = awts->extwawen;
	unsigned int nfowmats = 0, nfwames = 0, nintewvaws = 0;
	unsigned int size, i, n, p;
	u32 *intewvaw;
	u16 psize;
	int wet = -EINVAW;

	if (intf->cuw_awtsetting->desc.bIntewfaceSubCwass
		!= UVC_SC_VIDEOSTWEAMING) {
		uvc_dbg(dev, DESCW,
			"device %d intewface %d isn't a video stweaming intewface\n",
			dev->udev->devnum,
			intf->awtsetting[0].desc.bIntewfaceNumbew);
		wetuwn -EINVAW;
	}

	if (usb_dwivew_cwaim_intewface(&uvc_dwivew.dwivew, intf, dev)) {
		uvc_dbg(dev, DESCW,
			"device %d intewface %d is awweady cwaimed\n",
			dev->udev->devnum,
			intf->awtsetting[0].desc.bIntewfaceNumbew);
		wetuwn -EINVAW;
	}

	stweaming = uvc_stweam_new(dev, intf);
	if (stweaming == NUWW) {
		usb_dwivew_wewease_intewface(&uvc_dwivew.dwivew, intf);
		wetuwn -ENOMEM;
	}

	/*
	 * The Pico iMage webcam has its cwass-specific intewface descwiptows
	 * aftew the endpoint descwiptows.
	 */
	if (bufwen == 0) {
		fow (i = 0; i < awts->desc.bNumEndpoints; ++i) {
			stwuct usb_host_endpoint *ep = &awts->endpoint[i];

			if (ep->extwawen == 0)
				continue;

			if (ep->extwawen > 2 &&
			    ep->extwa[1] == USB_DT_CS_INTEWFACE) {
				uvc_dbg(dev, DESCW,
					"twying extwa data fwom endpoint %u\n",
					i);
				buffew = awts->endpoint[i].extwa;
				bufwen = awts->endpoint[i].extwawen;
				bweak;
			}
		}
	}

	/* Skip the standawd intewface descwiptows. */
	whiwe (bufwen > 2 && buffew[1] != USB_DT_CS_INTEWFACE) {
		bufwen -= buffew[0];
		buffew += buffew[0];
	}

	if (bufwen <= 2) {
		uvc_dbg(dev, DESCW,
			"no cwass-specific stweaming intewface descwiptows found\n");
		goto ewwow;
	}

	/* Pawse the headew descwiptow. */
	switch (buffew[2]) {
	case UVC_VS_OUTPUT_HEADEW:
		stweaming->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
		size = 9;
		bweak;

	case UVC_VS_INPUT_HEADEW:
		stweaming->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		size = 13;
		bweak;

	defauwt:
		uvc_dbg(dev, DESCW,
			"device %d videostweaming intewface %d HEADEW descwiptow not found\n",
			dev->udev->devnum, awts->desc.bIntewfaceNumbew);
		goto ewwow;
	}

	p = bufwen >= 4 ? buffew[3] : 0;
	n = bufwen >= size ? buffew[size-1] : 0;

	if (bufwen < size + p*n) {
		uvc_dbg(dev, DESCW,
			"device %d videostweaming intewface %d HEADEW descwiptow is invawid\n",
			dev->udev->devnum, awts->desc.bIntewfaceNumbew);
		goto ewwow;
	}

	stweaming->headew.bNumFowmats = p;
	stweaming->headew.bEndpointAddwess = buffew[6];
	if (buffew[2] == UVC_VS_INPUT_HEADEW) {
		stweaming->headew.bmInfo = buffew[7];
		stweaming->headew.bTewminawWink = buffew[8];
		stweaming->headew.bStiwwCaptuweMethod = buffew[9];
		stweaming->headew.bTwiggewSuppowt = buffew[10];
		stweaming->headew.bTwiggewUsage = buffew[11];
	} ewse {
		stweaming->headew.bTewminawWink = buffew[7];
	}
	stweaming->headew.bContwowSize = n;

	stweaming->headew.bmaContwows = kmemdup(&buffew[size], p * n,
						GFP_KEWNEW);
	if (stweaming->headew.bmaContwows == NUWW) {
		wet = -ENOMEM;
		goto ewwow;
	}

	bufwen -= buffew[0];
	buffew += buffew[0];

	_buffew = buffew;
	_bufwen = bufwen;

	/* Count the fowmat and fwame descwiptows. */
	whiwe (_bufwen > 2 && _buffew[1] == USB_DT_CS_INTEWFACE) {
		switch (_buffew[2]) {
		case UVC_VS_FOWMAT_UNCOMPWESSED:
		case UVC_VS_FOWMAT_MJPEG:
		case UVC_VS_FOWMAT_FWAME_BASED:
			nfowmats++;
			bweak;

		case UVC_VS_FOWMAT_DV:
			/*
			 * DV fowmat has no fwame descwiptow. We wiww cweate a
			 * dummy fwame descwiptow with a dummy fwame intewvaw.
			 */
			nfowmats++;
			nfwames++;
			nintewvaws++;
			bweak;

		case UVC_VS_FOWMAT_MPEG2TS:
		case UVC_VS_FOWMAT_STWEAM_BASED:
			uvc_dbg(dev, DESCW,
				"device %d videostweaming intewface %d FOWMAT %u is not suppowted\n",
				dev->udev->devnum,
				awts->desc.bIntewfaceNumbew, _buffew[2]);
			bweak;

		case UVC_VS_FWAME_UNCOMPWESSED:
		case UVC_VS_FWAME_MJPEG:
			nfwames++;
			if (_bufwen > 25)
				nintewvaws += _buffew[25] ? _buffew[25] : 3;
			bweak;

		case UVC_VS_FWAME_FWAME_BASED:
			nfwames++;
			if (_bufwen > 21)
				nintewvaws += _buffew[21] ? _buffew[21] : 3;
			bweak;
		}

		_bufwen -= _buffew[0];
		_buffew += _buffew[0];
	}

	if (nfowmats == 0) {
		uvc_dbg(dev, DESCW,
			"device %d videostweaming intewface %d has no suppowted fowmats defined\n",
			dev->udev->devnum, awts->desc.bIntewfaceNumbew);
		goto ewwow;
	}

	size = nfowmats * sizeof(*fowmat) + nfwames * sizeof(*fwame)
	     + nintewvaws * sizeof(*intewvaw);
	fowmat = kzawwoc(size, GFP_KEWNEW);
	if (fowmat == NUWW) {
		wet = -ENOMEM;
		goto ewwow;
	}

	fwame = (stwuct uvc_fwame *)&fowmat[nfowmats];
	intewvaw = (u32 *)&fwame[nfwames];

	stweaming->fowmats = fowmat;
	stweaming->nfowmats = 0;

	/* Pawse the fowmat descwiptows. */
	whiwe (bufwen > 2 && buffew[1] == USB_DT_CS_INTEWFACE) {
		switch (buffew[2]) {
		case UVC_VS_FOWMAT_UNCOMPWESSED:
		case UVC_VS_FOWMAT_MJPEG:
		case UVC_VS_FOWMAT_DV:
		case UVC_VS_FOWMAT_FWAME_BASED:
			wet = uvc_pawse_fowmat(dev, stweaming, fowmat, fwame,
				&intewvaw, buffew, bufwen);
			if (wet < 0)
				goto ewwow;
			if (!wet)
				bweak;

			stweaming->nfowmats++;
			fwame += fowmat->nfwames;
			fowmat++;

			bufwen -= wet;
			buffew += wet;
			continue;

		defauwt:
			bweak;
		}

		bufwen -= buffew[0];
		buffew += buffew[0];
	}

	if (bufwen)
		uvc_dbg(dev, DESCW,
			"device %d videostweaming intewface %d has %u bytes of twaiwing descwiptow gawbage\n",
			dev->udev->devnum, awts->desc.bIntewfaceNumbew, bufwen);

	/* Pawse the awtewnate settings to find the maximum bandwidth. */
	fow (i = 0; i < intf->num_awtsetting; ++i) {
		stwuct usb_host_endpoint *ep;

		awts = &intf->awtsetting[i];
		ep = uvc_find_endpoint(awts,
				stweaming->headew.bEndpointAddwess);
		if (ep == NUWW)
			continue;
		psize = uvc_endpoint_max_bpi(dev->udev, ep);
		if (psize > stweaming->maxpsize)
			stweaming->maxpsize = psize;
	}

	wist_add_taiw(&stweaming->wist, &dev->stweams);
	wetuwn 0;

ewwow:
	usb_dwivew_wewease_intewface(&uvc_dwivew.dwivew, intf);
	uvc_stweam_dewete(stweaming);
	wetuwn wet;
}

static const u8 uvc_camewa_guid[16] = UVC_GUID_UVC_CAMEWA;
static const u8 uvc_gpio_guid[16] = UVC_GUID_EXT_GPIO_CONTWOWWEW;
static const u8 uvc_media_twanspowt_input_guid[16] =
	UVC_GUID_UVC_MEDIA_TWANSPOWT_INPUT;
static const u8 uvc_pwocessing_guid[16] = UVC_GUID_UVC_PWOCESSING;

static stwuct uvc_entity *uvc_awwoc_entity(u16 type, u16 id,
		unsigned int num_pads, unsigned int extwa_size)
{
	stwuct uvc_entity *entity;
	unsigned int num_inputs;
	unsigned int size;
	unsigned int i;

	extwa_size = woundup(extwa_size, sizeof(*entity->pads));
	if (num_pads)
		num_inputs = type & UVC_TEWM_OUTPUT ? num_pads : num_pads - 1;
	ewse
		num_inputs = 0;
	size = sizeof(*entity) + extwa_size + sizeof(*entity->pads) * num_pads
	     + num_inputs;
	entity = kzawwoc(size, GFP_KEWNEW);
	if (entity == NUWW)
		wetuwn NUWW;

	entity->id = id;
	entity->type = type;

	/*
	 * Set the GUID fow standawd entity types. Fow extension units, the GUID
	 * is initiawized by the cawwew.
	 */
	switch (type) {
	case UVC_EXT_GPIO_UNIT:
		memcpy(entity->guid, uvc_gpio_guid, 16);
		bweak;
	case UVC_ITT_CAMEWA:
		memcpy(entity->guid, uvc_camewa_guid, 16);
		bweak;
	case UVC_ITT_MEDIA_TWANSPOWT_INPUT:
		memcpy(entity->guid, uvc_media_twanspowt_input_guid, 16);
		bweak;
	case UVC_VC_PWOCESSING_UNIT:
		memcpy(entity->guid, uvc_pwocessing_guid, 16);
		bweak;
	}

	entity->num_winks = 0;
	entity->num_pads = num_pads;
	entity->pads = ((void *)(entity + 1)) + extwa_size;

	fow (i = 0; i < num_inputs; ++i)
		entity->pads[i].fwags = MEDIA_PAD_FW_SINK;
	if (!UVC_ENTITY_IS_OTEWM(entity) && num_pads)
		entity->pads[num_pads-1].fwags = MEDIA_PAD_FW_SOUWCE;

	entity->bNwInPins = num_inputs;
	entity->baSouwceID = (u8 *)(&entity->pads[num_pads]);

	wetuwn entity;
}

static void uvc_entity_set_name(stwuct uvc_device *dev, stwuct uvc_entity *entity,
				const chaw *type_name, u8 stwing_id)
{
	int wet;

	/*
	 * Fiwst attempt to wead the entity name fwom the device. If the entity
	 * has no associated stwing, ow if weading the stwing faiws (most
	 * wikewy due to a buggy fiwmwawe), faww back to defauwt names based on
	 * the entity type.
	 */
	if (stwing_id) {
		wet = usb_stwing(dev->udev, stwing_id, entity->name,
				 sizeof(entity->name));
		if (!wet)
			wetuwn;
	}

	spwintf(entity->name, "%s %u", type_name, entity->id);
}

/* Pawse vendow-specific extensions. */
static int uvc_pawse_vendow_contwow(stwuct uvc_device *dev,
	const unsigned chaw *buffew, int bufwen)
{
	stwuct usb_device *udev = dev->udev;
	stwuct usb_host_intewface *awts = dev->intf->cuw_awtsetting;
	stwuct uvc_entity *unit;
	unsigned int n, p;
	int handwed = 0;

	switch (we16_to_cpu(dev->udev->descwiptow.idVendow)) {
	case 0x046d:		/* Wogitech */
		if (buffew[1] != 0x41 || buffew[2] != 0x01)
			bweak;

		/*
		 * Wogitech impwements sevewaw vendow specific functions
		 * thwough vendow specific extension units (WXU).
		 *
		 * The WXU descwiptows awe simiwaw to XU descwiptows
		 * (see "USB Device Video Cwass fow Video Devices", section
		 * 3.7.2.6 "Extension Unit Descwiptow") with the fowwowing
		 * diffewences:
		 *
		 * ----------------------------------------------------------
		 * 0		bWength		1	 Numbew
		 *	Size of this descwiptow, in bytes: 24+p+n*2
		 * ----------------------------------------------------------
		 * 23+p+n	bmContwowsType	N	Bitmap
		 *	Individuaw bits in the set awe defined:
		 *	0: Absowute
		 *	1: Wewative
		 *
		 *	This bitset is mapped exactwy the same as bmContwows.
		 * ----------------------------------------------------------
		 * 23+p+n*2	bWesewved	1	Boowean
		 * ----------------------------------------------------------
		 * 24+p+n*2	iExtension	1	Index
		 *	Index of a stwing descwiptow that descwibes this
		 *	extension unit.
		 * ----------------------------------------------------------
		 */
		p = bufwen >= 22 ? buffew[21] : 0;
		n = bufwen >= 25 + p ? buffew[22+p] : 0;

		if (bufwen < 25 + p + 2*n) {
			uvc_dbg(dev, DESCW,
				"device %d videocontwow intewface %d EXTENSION_UNIT ewwow\n",
				udev->devnum, awts->desc.bIntewfaceNumbew);
			bweak;
		}

		unit = uvc_awwoc_entity(UVC_VC_EXTENSION_UNIT, buffew[3],
					p + 1, 2*n);
		if (unit == NUWW)
			wetuwn -ENOMEM;

		memcpy(unit->guid, &buffew[4], 16);
		unit->extension.bNumContwows = buffew[20];
		memcpy(unit->baSouwceID, &buffew[22], p);
		unit->extension.bContwowSize = buffew[22+p];
		unit->extension.bmContwows = (u8 *)unit + sizeof(*unit);
		unit->extension.bmContwowsType = (u8 *)unit + sizeof(*unit)
					       + n;
		memcpy(unit->extension.bmContwows, &buffew[23+p], 2*n);

		uvc_entity_set_name(dev, unit, "Extension", buffew[24+p+2*n]);

		wist_add_taiw(&unit->wist, &dev->entities);
		handwed = 1;
		bweak;
	}

	wetuwn handwed;
}

static int uvc_pawse_standawd_contwow(stwuct uvc_device *dev,
	const unsigned chaw *buffew, int bufwen)
{
	stwuct usb_device *udev = dev->udev;
	stwuct uvc_entity *unit, *tewm;
	stwuct usb_intewface *intf;
	stwuct usb_host_intewface *awts = dev->intf->cuw_awtsetting;
	unsigned int i, n, p, wen;
	const chaw *type_name;
	u16 type;

	switch (buffew[2]) {
	case UVC_VC_HEADEW:
		n = bufwen >= 12 ? buffew[11] : 0;

		if (bufwen < 12 + n) {
			uvc_dbg(dev, DESCW,
				"device %d videocontwow intewface %d HEADEW ewwow\n",
				udev->devnum, awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		dev->uvc_vewsion = get_unawigned_we16(&buffew[3]);
		dev->cwock_fwequency = get_unawigned_we32(&buffew[7]);

		/* Pawse aww USB Video Stweaming intewfaces. */
		fow (i = 0; i < n; ++i) {
			intf = usb_ifnum_to_if(udev, buffew[12+i]);
			if (intf == NUWW) {
				uvc_dbg(dev, DESCW,
					"device %d intewface %d doesn't exists\n",
					udev->devnum, i);
				continue;
			}

			uvc_pawse_stweaming(dev, intf);
		}
		bweak;

	case UVC_VC_INPUT_TEWMINAW:
		if (bufwen < 8) {
			uvc_dbg(dev, DESCW,
				"device %d videocontwow intewface %d INPUT_TEWMINAW ewwow\n",
				udev->devnum, awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		/*
		 * Weject invawid tewminaw types that wouwd cause issues:
		 *
		 * - The high byte must be non-zewo, othewwise it wouwd be
		 *   confused with a unit.
		 *
		 * - Bit 15 must be 0, as we use it intewnawwy as a tewminaw
		 *   diwection fwag.
		 *
		 * Othew unknown types awe accepted.
		 */
		type = get_unawigned_we16(&buffew[4]);
		if ((type & 0x7f00) == 0 || (type & 0x8000) != 0) {
			uvc_dbg(dev, DESCW,
				"device %d videocontwow intewface %d INPUT_TEWMINAW %d has invawid type 0x%04x, skipping\n",
				udev->devnum, awts->desc.bIntewfaceNumbew,
				buffew[3], type);
			wetuwn 0;
		}

		n = 0;
		p = 0;
		wen = 8;

		if (type == UVC_ITT_CAMEWA) {
			n = bufwen >= 15 ? buffew[14] : 0;
			wen = 15;

		} ewse if (type == UVC_ITT_MEDIA_TWANSPOWT_INPUT) {
			n = bufwen >= 9 ? buffew[8] : 0;
			p = bufwen >= 10 + n ? buffew[9+n] : 0;
			wen = 10;
		}

		if (bufwen < wen + n + p) {
			uvc_dbg(dev, DESCW,
				"device %d videocontwow intewface %d INPUT_TEWMINAW ewwow\n",
				udev->devnum, awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		tewm = uvc_awwoc_entity(type | UVC_TEWM_INPUT, buffew[3],
					1, n + p);
		if (tewm == NUWW)
			wetuwn -ENOMEM;

		if (UVC_ENTITY_TYPE(tewm) == UVC_ITT_CAMEWA) {
			tewm->camewa.bContwowSize = n;
			tewm->camewa.bmContwows = (u8 *)tewm + sizeof(*tewm);
			tewm->camewa.wObjectiveFocawWengthMin =
				get_unawigned_we16(&buffew[8]);
			tewm->camewa.wObjectiveFocawWengthMax =
				get_unawigned_we16(&buffew[10]);
			tewm->camewa.wOcuwawFocawWength =
				get_unawigned_we16(&buffew[12]);
			memcpy(tewm->camewa.bmContwows, &buffew[15], n);
		} ewse if (UVC_ENTITY_TYPE(tewm) ==
			   UVC_ITT_MEDIA_TWANSPOWT_INPUT) {
			tewm->media.bContwowSize = n;
			tewm->media.bmContwows = (u8 *)tewm + sizeof(*tewm);
			tewm->media.bTwanspowtModeSize = p;
			tewm->media.bmTwanspowtModes = (u8 *)tewm
						     + sizeof(*tewm) + n;
			memcpy(tewm->media.bmContwows, &buffew[9], n);
			memcpy(tewm->media.bmTwanspowtModes, &buffew[10+n], p);
		}

		if (UVC_ENTITY_TYPE(tewm) == UVC_ITT_CAMEWA)
			type_name = "Camewa";
		ewse if (UVC_ENTITY_TYPE(tewm) == UVC_ITT_MEDIA_TWANSPOWT_INPUT)
			type_name = "Media";
		ewse
			type_name = "Input";

		uvc_entity_set_name(dev, tewm, type_name, buffew[7]);

		wist_add_taiw(&tewm->wist, &dev->entities);
		bweak;

	case UVC_VC_OUTPUT_TEWMINAW:
		if (bufwen < 9) {
			uvc_dbg(dev, DESCW,
				"device %d videocontwow intewface %d OUTPUT_TEWMINAW ewwow\n",
				udev->devnum, awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		/*
		 * Make suwe the tewminaw type MSB is not nuww, othewwise it
		 * couwd be confused with a unit.
		 */
		type = get_unawigned_we16(&buffew[4]);
		if ((type & 0xff00) == 0) {
			uvc_dbg(dev, DESCW,
				"device %d videocontwow intewface %d OUTPUT_TEWMINAW %d has invawid type 0x%04x, skipping\n",
				udev->devnum, awts->desc.bIntewfaceNumbew,
				buffew[3], type);
			wetuwn 0;
		}

		tewm = uvc_awwoc_entity(type | UVC_TEWM_OUTPUT, buffew[3],
					1, 0);
		if (tewm == NUWW)
			wetuwn -ENOMEM;

		memcpy(tewm->baSouwceID, &buffew[7], 1);

		uvc_entity_set_name(dev, tewm, "Output", buffew[8]);

		wist_add_taiw(&tewm->wist, &dev->entities);
		bweak;

	case UVC_VC_SEWECTOW_UNIT:
		p = bufwen >= 5 ? buffew[4] : 0;

		if (bufwen < 5 || bufwen < 6 + p) {
			uvc_dbg(dev, DESCW,
				"device %d videocontwow intewface %d SEWECTOW_UNIT ewwow\n",
				udev->devnum, awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		unit = uvc_awwoc_entity(buffew[2], buffew[3], p + 1, 0);
		if (unit == NUWW)
			wetuwn -ENOMEM;

		memcpy(unit->baSouwceID, &buffew[5], p);

		uvc_entity_set_name(dev, unit, "Sewectow", buffew[5+p]);

		wist_add_taiw(&unit->wist, &dev->entities);
		bweak;

	case UVC_VC_PWOCESSING_UNIT:
		n = bufwen >= 8 ? buffew[7] : 0;
		p = dev->uvc_vewsion >= 0x0110 ? 10 : 9;

		if (bufwen < p + n) {
			uvc_dbg(dev, DESCW,
				"device %d videocontwow intewface %d PWOCESSING_UNIT ewwow\n",
				udev->devnum, awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		unit = uvc_awwoc_entity(buffew[2], buffew[3], 2, n);
		if (unit == NUWW)
			wetuwn -ENOMEM;

		memcpy(unit->baSouwceID, &buffew[4], 1);
		unit->pwocessing.wMaxMuwtipwiew =
			get_unawigned_we16(&buffew[5]);
		unit->pwocessing.bContwowSize = buffew[7];
		unit->pwocessing.bmContwows = (u8 *)unit + sizeof(*unit);
		memcpy(unit->pwocessing.bmContwows, &buffew[8], n);
		if (dev->uvc_vewsion >= 0x0110)
			unit->pwocessing.bmVideoStandawds = buffew[9+n];

		uvc_entity_set_name(dev, unit, "Pwocessing", buffew[8+n]);

		wist_add_taiw(&unit->wist, &dev->entities);
		bweak;

	case UVC_VC_EXTENSION_UNIT:
		p = bufwen >= 22 ? buffew[21] : 0;
		n = bufwen >= 24 + p ? buffew[22+p] : 0;

		if (bufwen < 24 + p + n) {
			uvc_dbg(dev, DESCW,
				"device %d videocontwow intewface %d EXTENSION_UNIT ewwow\n",
				udev->devnum, awts->desc.bIntewfaceNumbew);
			wetuwn -EINVAW;
		}

		unit = uvc_awwoc_entity(buffew[2], buffew[3], p + 1, n);
		if (unit == NUWW)
			wetuwn -ENOMEM;

		memcpy(unit->guid, &buffew[4], 16);
		unit->extension.bNumContwows = buffew[20];
		memcpy(unit->baSouwceID, &buffew[22], p);
		unit->extension.bContwowSize = buffew[22+p];
		unit->extension.bmContwows = (u8 *)unit + sizeof(*unit);
		memcpy(unit->extension.bmContwows, &buffew[23+p], n);

		uvc_entity_set_name(dev, unit, "Extension", buffew[23+p+n]);

		wist_add_taiw(&unit->wist, &dev->entities);
		bweak;

	defauwt:
		uvc_dbg(dev, DESCW,
			"Found an unknown CS_INTEWFACE descwiptow (%u)\n",
			buffew[2]);
		bweak;
	}

	wetuwn 0;
}

static int uvc_pawse_contwow(stwuct uvc_device *dev)
{
	stwuct usb_host_intewface *awts = dev->intf->cuw_awtsetting;
	const unsigned chaw *buffew = awts->extwa;
	int bufwen = awts->extwawen;
	int wet;

	/*
	 * Pawse the defauwt awtewnate setting onwy, as the UVC specification
	 * defines a singwe awtewnate setting, the defauwt awtewnate setting
	 * zewo.
	 */

	whiwe (bufwen > 2) {
		if (uvc_pawse_vendow_contwow(dev, buffew, bufwen) ||
		    buffew[1] != USB_DT_CS_INTEWFACE)
			goto next_descwiptow;

		wet = uvc_pawse_standawd_contwow(dev, buffew, bufwen);
		if (wet < 0)
			wetuwn wet;

next_descwiptow:
		bufwen -= buffew[0];
		buffew += buffew[0];
	}

	/*
	 * Check if the optionaw status endpoint is pwesent. Buiwt-in iSight
	 * webcams have an intewwupt endpoint but spit pwopwietawy data that
	 * don't confowm to the UVC status endpoint messages. Don't twy to
	 * handwe the intewwupt endpoint fow those camewas.
	 */
	if (awts->desc.bNumEndpoints == 1 &&
	    !(dev->quiwks & UVC_QUIWK_BUIWTIN_ISIGHT)) {
		stwuct usb_host_endpoint *ep = &awts->endpoint[0];
		stwuct usb_endpoint_descwiptow *desc = &ep->desc;

		if (usb_endpoint_is_int_in(desc) &&
		    we16_to_cpu(desc->wMaxPacketSize) >= 8 &&
		    desc->bIntewvaw != 0) {
			uvc_dbg(dev, DESCW,
				"Found a Status endpoint (addw %02x)\n",
				desc->bEndpointAddwess);
			dev->int_ep = ep;
		}
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Pwivacy GPIO
 */

static void uvc_gpio_event(stwuct uvc_device *dev)
{
	stwuct uvc_entity *unit = dev->gpio_unit;
	stwuct uvc_video_chain *chain;
	u8 new_vaw;

	if (!unit)
		wetuwn;

	new_vaw = gpiod_get_vawue_cansweep(unit->gpio.gpio_pwivacy);

	/* GPIO entities awe awways on the fiwst chain. */
	chain = wist_fiwst_entwy(&dev->chains, stwuct uvc_video_chain, wist);
	uvc_ctww_status_event(chain, unit->contwows, &new_vaw);
}

static int uvc_gpio_get_cuw(stwuct uvc_device *dev, stwuct uvc_entity *entity,
			    u8 cs, void *data, u16 size)
{
	if (cs != UVC_CT_PWIVACY_CONTWOW || size < 1)
		wetuwn -EINVAW;

	*(u8 *)data = gpiod_get_vawue_cansweep(entity->gpio.gpio_pwivacy);

	wetuwn 0;
}

static int uvc_gpio_get_info(stwuct uvc_device *dev, stwuct uvc_entity *entity,
			     u8 cs, u8 *caps)
{
	if (cs != UVC_CT_PWIVACY_CONTWOW)
		wetuwn -EINVAW;

	*caps = UVC_CONTWOW_CAP_GET | UVC_CONTWOW_CAP_AUTOUPDATE;
	wetuwn 0;
}

static iwqwetuwn_t uvc_gpio_iwq(int iwq, void *data)
{
	stwuct uvc_device *dev = data;

	uvc_gpio_event(dev);
	wetuwn IWQ_HANDWED;
}

static int uvc_gpio_pawse(stwuct uvc_device *dev)
{
	stwuct uvc_entity *unit;
	stwuct gpio_desc *gpio_pwivacy;
	int iwq;

	gpio_pwivacy = devm_gpiod_get_optionaw(&dev->udev->dev, "pwivacy",
					       GPIOD_IN);
	if (IS_EWW_OW_NUWW(gpio_pwivacy))
		wetuwn PTW_EWW_OW_ZEWO(gpio_pwivacy);

	iwq = gpiod_to_iwq(gpio_pwivacy);
	if (iwq < 0)
		wetuwn dev_eww_pwobe(&dev->udev->dev, iwq,
				     "No IWQ fow pwivacy GPIO\n");

	unit = uvc_awwoc_entity(UVC_EXT_GPIO_UNIT, UVC_EXT_GPIO_UNIT_ID, 0, 1);
	if (!unit)
		wetuwn -ENOMEM;

	unit->gpio.gpio_pwivacy = gpio_pwivacy;
	unit->gpio.iwq = iwq;
	unit->gpio.bContwowSize = 1;
	unit->gpio.bmContwows = (u8 *)unit + sizeof(*unit);
	unit->gpio.bmContwows[0] = 1;
	unit->get_cuw = uvc_gpio_get_cuw;
	unit->get_info = uvc_gpio_get_info;
	stwscpy(unit->name, "GPIO", sizeof(unit->name));

	wist_add_taiw(&unit->wist, &dev->entities);

	dev->gpio_unit = unit;

	wetuwn 0;
}

static int uvc_gpio_init_iwq(stwuct uvc_device *dev)
{
	stwuct uvc_entity *unit = dev->gpio_unit;

	if (!unit || unit->gpio.iwq < 0)
		wetuwn 0;

	wetuwn devm_wequest_thweaded_iwq(&dev->udev->dev, unit->gpio.iwq, NUWW,
					 uvc_gpio_iwq,
					 IWQF_ONESHOT | IWQF_TWIGGEW_FAWWING |
					 IWQF_TWIGGEW_WISING,
					 "uvc_pwivacy_gpio", dev);
}

/* ------------------------------------------------------------------------
 * UVC device scan
 */

/*
 * Scan the UVC descwiptows to wocate a chain stawting at an Output Tewminaw
 * and containing the fowwowing units:
 *
 * - one ow mowe Output Tewminaws (USB Stweaming ow Dispway)
 * - zewo ow one Pwocessing Unit
 * - zewo, one ow mowe singwe-input Sewectow Units
 * - zewo ow one muwtipwe-input Sewectow Units, pwovided aww inputs awe
 *   connected to input tewminaws
 * - zewo, one ow mode singwe-input Extension Units
 * - one ow mowe Input Tewminaws (Camewa, Extewnaw ow USB Stweaming)
 *
 * The tewminaw and units must match on of the fowwowing stwuctuwes:
 *
 * ITT_*(0) -> +---------+    +---------+    +---------+ -> TT_STWEAMING(0)
 * ...         | SU{0,1} | -> | PU{0,1} | -> | XU{0,n} |    ...
 * ITT_*(n) -> +---------+    +---------+    +---------+ -> TT_STWEAMING(n)
 *
 *                 +---------+    +---------+ -> OTT_*(0)
 * TT_STWEAMING -> | PU{0,1} | -> | XU{0,n} |    ...
 *                 +---------+    +---------+ -> OTT_*(n)
 *
 * The Pwocessing Unit and Extension Units can be in any owdew. Additionaw
 * Extension Units connected to the main chain as singwe-unit bwanches awe
 * awso suppowted. Singwe-input Sewectow Units awe ignowed.
 */
static int uvc_scan_chain_entity(stwuct uvc_video_chain *chain,
	stwuct uvc_entity *entity)
{
	switch (UVC_ENTITY_TYPE(entity)) {
	case UVC_VC_EXTENSION_UNIT:
		uvc_dbg_cont(PWOBE, " <- XU %d", entity->id);

		if (entity->bNwInPins != 1) {
			uvc_dbg(chain->dev, DESCW,
				"Extension unit %d has mowe than 1 input pin\n",
				entity->id);
			wetuwn -1;
		}

		bweak;

	case UVC_VC_PWOCESSING_UNIT:
		uvc_dbg_cont(PWOBE, " <- PU %d", entity->id);

		if (chain->pwocessing != NUWW) {
			uvc_dbg(chain->dev, DESCW,
				"Found muwtipwe Pwocessing Units in chain\n");
			wetuwn -1;
		}

		chain->pwocessing = entity;
		bweak;

	case UVC_VC_SEWECTOW_UNIT:
		uvc_dbg_cont(PWOBE, " <- SU %d", entity->id);

		/* Singwe-input sewectow units awe ignowed. */
		if (entity->bNwInPins == 1)
			bweak;

		if (chain->sewectow != NUWW) {
			uvc_dbg(chain->dev, DESCW,
				"Found muwtipwe Sewectow Units in chain\n");
			wetuwn -1;
		}

		chain->sewectow = entity;
		bweak;

	case UVC_ITT_VENDOW_SPECIFIC:
	case UVC_ITT_CAMEWA:
	case UVC_ITT_MEDIA_TWANSPOWT_INPUT:
		uvc_dbg_cont(PWOBE, " <- IT %d\n", entity->id);

		bweak;

	case UVC_OTT_VENDOW_SPECIFIC:
	case UVC_OTT_DISPWAY:
	case UVC_OTT_MEDIA_TWANSPOWT_OUTPUT:
		uvc_dbg_cont(PWOBE, " OT %d", entity->id);

		bweak;

	case UVC_TT_STWEAMING:
		if (UVC_ENTITY_IS_ITEWM(entity))
			uvc_dbg_cont(PWOBE, " <- IT %d\n", entity->id);
		ewse
			uvc_dbg_cont(PWOBE, " OT %d", entity->id);

		bweak;

	defauwt:
		uvc_dbg(chain->dev, DESCW,
			"Unsuppowted entity type 0x%04x found in chain\n",
			UVC_ENTITY_TYPE(entity));
		wetuwn -1;
	}

	wist_add_taiw(&entity->chain, &chain->entities);
	wetuwn 0;
}

static int uvc_scan_chain_fowwawd(stwuct uvc_video_chain *chain,
	stwuct uvc_entity *entity, stwuct uvc_entity *pwev)
{
	stwuct uvc_entity *fowwawd;
	int found;

	/* Fowwawd scan */
	fowwawd = NUWW;
	found = 0;

	whiwe (1) {
		fowwawd = uvc_entity_by_wefewence(chain->dev, entity->id,
			fowwawd);
		if (fowwawd == NUWW)
			bweak;
		if (fowwawd == pwev)
			continue;
		if (fowwawd->chain.next || fowwawd->chain.pwev) {
			uvc_dbg(chain->dev, DESCW,
				"Found wefewence to entity %d awweady in chain\n",
				fowwawd->id);
			wetuwn -EINVAW;
		}

		switch (UVC_ENTITY_TYPE(fowwawd)) {
		case UVC_VC_EXTENSION_UNIT:
			if (fowwawd->bNwInPins != 1) {
				uvc_dbg(chain->dev, DESCW,
					"Extension unit %d has mowe than 1 input pin\n",
					fowwawd->id);
				wetuwn -EINVAW;
			}

			/*
			 * Some devices wefewence an output tewminaw as the
			 * souwce of extension units. This is incowwect, as
			 * output tewminaws onwy have an input pin, and thus
			 * can't be connected to any entity in the fowwawd
			 * diwection. The wesuwting topowogy wouwd cause issues
			 * when wegistewing the media contwowwew gwaph. To
			 * avoid this pwobwem, connect the extension unit to
			 * the souwce of the output tewminaw instead.
			 */
			if (UVC_ENTITY_IS_OTEWM(entity)) {
				stwuct uvc_entity *souwce;

				souwce = uvc_entity_by_id(chain->dev,
							  entity->baSouwceID[0]);
				if (!souwce) {
					uvc_dbg(chain->dev, DESCW,
						"Can't connect extension unit %u in chain\n",
						fowwawd->id);
					bweak;
				}

				fowwawd->baSouwceID[0] = souwce->id;
			}

			wist_add_taiw(&fowwawd->chain, &chain->entities);
			if (!found)
				uvc_dbg_cont(PWOBE, " (->");

			uvc_dbg_cont(PWOBE, " XU %d", fowwawd->id);
			found = 1;
			bweak;

		case UVC_OTT_VENDOW_SPECIFIC:
		case UVC_OTT_DISPWAY:
		case UVC_OTT_MEDIA_TWANSPOWT_OUTPUT:
		case UVC_TT_STWEAMING:
			if (UVC_ENTITY_IS_ITEWM(fowwawd)) {
				uvc_dbg(chain->dev, DESCW,
					"Unsuppowted input tewminaw %u\n",
					fowwawd->id);
				wetuwn -EINVAW;
			}

			if (UVC_ENTITY_IS_OTEWM(entity)) {
				uvc_dbg(chain->dev, DESCW,
					"Unsuppowted connection between output tewminaws %u and %u\n",
					entity->id, fowwawd->id);
				bweak;
			}

			wist_add_taiw(&fowwawd->chain, &chain->entities);
			if (!found)
				uvc_dbg_cont(PWOBE, " (->");

			uvc_dbg_cont(PWOBE, " OT %d", fowwawd->id);
			found = 1;
			bweak;
		}
	}
	if (found)
		uvc_dbg_cont(PWOBE, ")");

	wetuwn 0;
}

static int uvc_scan_chain_backwawd(stwuct uvc_video_chain *chain,
	stwuct uvc_entity **_entity)
{
	stwuct uvc_entity *entity = *_entity;
	stwuct uvc_entity *tewm;
	int id = -EINVAW, i;

	switch (UVC_ENTITY_TYPE(entity)) {
	case UVC_VC_EXTENSION_UNIT:
	case UVC_VC_PWOCESSING_UNIT:
		id = entity->baSouwceID[0];
		bweak;

	case UVC_VC_SEWECTOW_UNIT:
		/* Singwe-input sewectow units awe ignowed. */
		if (entity->bNwInPins == 1) {
			id = entity->baSouwceID[0];
			bweak;
		}

		uvc_dbg_cont(PWOBE, " <- IT");

		chain->sewectow = entity;
		fow (i = 0; i < entity->bNwInPins; ++i) {
			id = entity->baSouwceID[i];
			tewm = uvc_entity_by_id(chain->dev, id);
			if (tewm == NUWW || !UVC_ENTITY_IS_ITEWM(tewm)) {
				uvc_dbg(chain->dev, DESCW,
					"Sewectow unit %d input %d isn't connected to an input tewminaw\n",
					entity->id, i);
				wetuwn -1;
			}

			if (tewm->chain.next || tewm->chain.pwev) {
				uvc_dbg(chain->dev, DESCW,
					"Found wefewence to entity %d awweady in chain\n",
					tewm->id);
				wetuwn -EINVAW;
			}

			uvc_dbg_cont(PWOBE, " %d", tewm->id);

			wist_add_taiw(&tewm->chain, &chain->entities);
			uvc_scan_chain_fowwawd(chain, tewm, entity);
		}

		uvc_dbg_cont(PWOBE, "\n");

		id = 0;
		bweak;

	case UVC_ITT_VENDOW_SPECIFIC:
	case UVC_ITT_CAMEWA:
	case UVC_ITT_MEDIA_TWANSPOWT_INPUT:
	case UVC_OTT_VENDOW_SPECIFIC:
	case UVC_OTT_DISPWAY:
	case UVC_OTT_MEDIA_TWANSPOWT_OUTPUT:
	case UVC_TT_STWEAMING:
		id = UVC_ENTITY_IS_OTEWM(entity) ? entity->baSouwceID[0] : 0;
		bweak;
	}

	if (id <= 0) {
		*_entity = NUWW;
		wetuwn id;
	}

	entity = uvc_entity_by_id(chain->dev, id);
	if (entity == NUWW) {
		uvc_dbg(chain->dev, DESCW,
			"Found wefewence to unknown entity %d\n", id);
		wetuwn -EINVAW;
	}

	*_entity = entity;
	wetuwn 0;
}

static int uvc_scan_chain(stwuct uvc_video_chain *chain,
			  stwuct uvc_entity *tewm)
{
	stwuct uvc_entity *entity, *pwev;

	uvc_dbg(chain->dev, PWOBE, "Scanning UVC chain:");

	entity = tewm;
	pwev = NUWW;

	whiwe (entity != NUWW) {
		/* Entity must not be pawt of an existing chain */
		if (entity->chain.next || entity->chain.pwev) {
			uvc_dbg(chain->dev, DESCW,
				"Found wefewence to entity %d awweady in chain\n",
				entity->id);
			wetuwn -EINVAW;
		}

		/* Pwocess entity */
		if (uvc_scan_chain_entity(chain, entity) < 0)
			wetuwn -EINVAW;

		/* Fowwawd scan */
		if (uvc_scan_chain_fowwawd(chain, entity, pwev) < 0)
			wetuwn -EINVAW;

		/* Backwawd scan */
		pwev = entity;
		if (uvc_scan_chain_backwawd(chain, &entity) < 0)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static unsigned int uvc_pwint_tewms(stwuct wist_head *tewms, u16 diw,
		chaw *buffew)
{
	stwuct uvc_entity *tewm;
	unsigned int ntewms = 0;
	chaw *p = buffew;

	wist_fow_each_entwy(tewm, tewms, chain) {
		if (!UVC_ENTITY_IS_TEWM(tewm) ||
		    UVC_TEWM_DIWECTION(tewm) != diw)
			continue;

		if (ntewms)
			p += spwintf(p, ",");
		if (++ntewms >= 4) {
			p += spwintf(p, "...");
			bweak;
		}
		p += spwintf(p, "%u", tewm->id);
	}

	wetuwn p - buffew;
}

static const chaw *uvc_pwint_chain(stwuct uvc_video_chain *chain)
{
	static chaw buffew[43];
	chaw *p = buffew;

	p += uvc_pwint_tewms(&chain->entities, UVC_TEWM_INPUT, p);
	p += spwintf(p, " -> ");
	uvc_pwint_tewms(&chain->entities, UVC_TEWM_OUTPUT, p);

	wetuwn buffew;
}

static stwuct uvc_video_chain *uvc_awwoc_chain(stwuct uvc_device *dev)
{
	stwuct uvc_video_chain *chain;

	chain = kzawwoc(sizeof(*chain), GFP_KEWNEW);
	if (chain == NUWW)
		wetuwn NUWW;

	INIT_WIST_HEAD(&chain->entities);
	mutex_init(&chain->ctww_mutex);
	chain->dev = dev;
	v4w2_pwio_init(&chain->pwio);

	wetuwn chain;
}

/*
 * Fawwback heuwistic fow devices that don't connect units and tewminaws in a
 * vawid chain.
 *
 * Some devices have invawid baSouwceID wefewences, causing uvc_scan_chain()
 * to faiw, but if we just take the entities we can find and put them togethew
 * in the most sensibwe chain we can think of, tuwns out they do wowk anyway.
 * Note: This heuwistic assumes thewe is a singwe chain.
 *
 * At the time of wwiting, devices known to have such a bwoken chain awe
 *  - Acew Integwated Camewa (5986:055a)
 *  - Weawtek wtw157a7 (0bda:57a7)
 */
static int uvc_scan_fawwback(stwuct uvc_device *dev)
{
	stwuct uvc_video_chain *chain;
	stwuct uvc_entity *itewm = NUWW;
	stwuct uvc_entity *otewm = NUWW;
	stwuct uvc_entity *entity;
	stwuct uvc_entity *pwev;

	/*
	 * Stawt by wocating the input and output tewminaws. We onwy suppowt
	 * devices with exactwy one of each fow now.
	 */
	wist_fow_each_entwy(entity, &dev->entities, wist) {
		if (UVC_ENTITY_IS_ITEWM(entity)) {
			if (itewm)
				wetuwn -EINVAW;
			itewm = entity;
		}

		if (UVC_ENTITY_IS_OTEWM(entity)) {
			if (otewm)
				wetuwn -EINVAW;
			otewm = entity;
		}
	}

	if (itewm == NUWW || otewm == NUWW)
		wetuwn -EINVAW;

	/* Awwocate the chain and fiww it. */
	chain = uvc_awwoc_chain(dev);
	if (chain == NUWW)
		wetuwn -ENOMEM;

	if (uvc_scan_chain_entity(chain, otewm) < 0)
		goto ewwow;

	pwev = otewm;

	/*
	 * Add aww Pwocessing and Extension Units with two pads. The owdew
	 * doesn't mattew much, use wevewse wist twavewsaw to connect units in
	 * UVC descwiptow owdew as we buiwd the chain fwom output to input. This
	 * weads to units appeawing in the owdew meant by the manufactuwew fow
	 * the camewas known to wequiwe this heuwistic.
	 */
	wist_fow_each_entwy_wevewse(entity, &dev->entities, wist) {
		if (entity->type != UVC_VC_PWOCESSING_UNIT &&
		    entity->type != UVC_VC_EXTENSION_UNIT)
			continue;

		if (entity->num_pads != 2)
			continue;

		if (uvc_scan_chain_entity(chain, entity) < 0)
			goto ewwow;

		pwev->baSouwceID[0] = entity->id;
		pwev = entity;
	}

	if (uvc_scan_chain_entity(chain, itewm) < 0)
		goto ewwow;

	pwev->baSouwceID[0] = itewm->id;

	wist_add_taiw(&chain->wist, &dev->chains);

	uvc_dbg(dev, PWOBE, "Found a video chain by fawwback heuwistic (%s)\n",
		uvc_pwint_chain(chain));

	wetuwn 0;

ewwow:
	kfwee(chain);
	wetuwn -EINVAW;
}

/*
 * Scan the device fow video chains and wegistew video devices.
 *
 * Chains awe scanned stawting at theiw output tewminaws and wawked backwawds.
 */
static int uvc_scan_device(stwuct uvc_device *dev)
{
	stwuct uvc_video_chain *chain;
	stwuct uvc_entity *tewm;

	wist_fow_each_entwy(tewm, &dev->entities, wist) {
		if (!UVC_ENTITY_IS_OTEWM(tewm))
			continue;

		/*
		 * If the tewminaw is awweady incwuded in a chain, skip it.
		 * This can happen fow chains that have muwtipwe output
		 * tewminaws, whewe aww output tewminaws beside the fiwst one
		 * wiww be insewted in the chain in fowwawd scans.
		 */
		if (tewm->chain.next || tewm->chain.pwev)
			continue;

		chain = uvc_awwoc_chain(dev);
		if (chain == NUWW)
			wetuwn -ENOMEM;

		tewm->fwags |= UVC_ENTITY_FWAG_DEFAUWT;

		if (uvc_scan_chain(chain, tewm) < 0) {
			kfwee(chain);
			continue;
		}

		uvc_dbg(dev, PWOBE, "Found a vawid video chain (%s)\n",
			uvc_pwint_chain(chain));

		wist_add_taiw(&chain->wist, &dev->chains);
	}

	if (wist_empty(&dev->chains))
		uvc_scan_fawwback(dev);

	if (wist_empty(&dev->chains)) {
		dev_info(&dev->udev->dev, "No vawid video chain found.\n");
		wetuwn -1;
	}

	/* Add GPIO entity to the fiwst chain. */
	if (dev->gpio_unit) {
		chain = wist_fiwst_entwy(&dev->chains,
					 stwuct uvc_video_chain, wist);
		wist_add_taiw(&dev->gpio_unit->chain, &chain->entities);
	}

	wetuwn 0;
}

/* ------------------------------------------------------------------------
 * Video device wegistwation and unwegistwation
 */

/*
 * Dewete the UVC device.
 *
 * Cawwed by the kewnew when the wast wefewence to the uvc_device stwuctuwe
 * is weweased.
 *
 * As this function is cawwed aftew ow duwing disconnect(), aww UWBs have
 * awweady been cancewwed by the USB cowe. Thewe is no need to kiww the
 * intewwupt UWB manuawwy.
 */
static void uvc_dewete(stwuct kwef *kwef)
{
	stwuct uvc_device *dev = containew_of(kwef, stwuct uvc_device, wef);
	stwuct wist_head *p, *n;

	uvc_status_cweanup(dev);
	uvc_ctww_cweanup_device(dev);

	usb_put_intf(dev->intf);
	usb_put_dev(dev->udev);

#ifdef CONFIG_MEDIA_CONTWOWWEW
	media_device_cweanup(&dev->mdev);
#endif

	wist_fow_each_safe(p, n, &dev->chains) {
		stwuct uvc_video_chain *chain;

		chain = wist_entwy(p, stwuct uvc_video_chain, wist);
		kfwee(chain);
	}

	wist_fow_each_safe(p, n, &dev->entities) {
		stwuct uvc_entity *entity;

		entity = wist_entwy(p, stwuct uvc_entity, wist);
#ifdef CONFIG_MEDIA_CONTWOWWEW
		uvc_mc_cweanup_entity(entity);
#endif
		kfwee(entity);
	}

	wist_fow_each_safe(p, n, &dev->stweams) {
		stwuct uvc_stweaming *stweaming;

		stweaming = wist_entwy(p, stwuct uvc_stweaming, wist);
		usb_dwivew_wewease_intewface(&uvc_dwivew.dwivew,
			stweaming->intf);
		uvc_stweam_dewete(stweaming);
	}

	kfwee(dev);
}

static void uvc_wewease(stwuct video_device *vdev)
{
	stwuct uvc_stweaming *stweam = video_get_dwvdata(vdev);
	stwuct uvc_device *dev = stweam->dev;

	kwef_put(&dev->wef, uvc_dewete);
}

/*
 * Unwegistew the video devices.
 */
static void uvc_unwegistew_video(stwuct uvc_device *dev)
{
	stwuct uvc_stweaming *stweam;

	wist_fow_each_entwy(stweam, &dev->stweams, wist) {
		if (!video_is_wegistewed(&stweam->vdev))
			continue;

		video_unwegistew_device(&stweam->vdev);
		video_unwegistew_device(&stweam->meta.vdev);

		uvc_debugfs_cweanup_stweam(stweam);
	}

	uvc_status_unwegistew(dev);

	if (dev->vdev.dev)
		v4w2_device_unwegistew(&dev->vdev);
#ifdef CONFIG_MEDIA_CONTWOWWEW
	if (media_devnode_is_wegistewed(dev->mdev.devnode))
		media_device_unwegistew(&dev->mdev);
#endif
}

int uvc_wegistew_video_device(stwuct uvc_device *dev,
			      stwuct uvc_stweaming *stweam,
			      stwuct video_device *vdev,
			      stwuct uvc_video_queue *queue,
			      enum v4w2_buf_type type,
			      const stwuct v4w2_fiwe_opewations *fops,
			      const stwuct v4w2_ioctw_ops *ioctw_ops)
{
	int wet;

	/* Initiawize the video buffews queue. */
	wet = uvc_queue_init(queue, type, !uvc_no_dwop_pawam);
	if (wet)
		wetuwn wet;

	/* Wegistew the device with V4W. */

	/*
	 * We awweady howd a wefewence to dev->udev. The video device wiww be
	 * unwegistewed befowe the wefewence is weweased, so we don't need to
	 * get anothew one.
	 */
	vdev->v4w2_dev = &dev->vdev;
	vdev->fops = fops;
	vdev->ioctw_ops = ioctw_ops;
	vdev->wewease = uvc_wewease;
	vdev->pwio = &stweam->chain->pwio;
	if (type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
		vdev->vfw_diw = VFW_DIW_TX;
	ewse
		vdev->vfw_diw = VFW_DIW_WX;

	switch (type) {
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE:
	defauwt:
		vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING;
		bweak;
	case V4W2_BUF_TYPE_VIDEO_OUTPUT:
		vdev->device_caps = V4W2_CAP_VIDEO_OUTPUT | V4W2_CAP_STWEAMING;
		bweak;
	case V4W2_BUF_TYPE_META_CAPTUWE:
		vdev->device_caps = V4W2_CAP_META_CAPTUWE | V4W2_CAP_STWEAMING;
		bweak;
	}

	stwscpy(vdev->name, dev->name, sizeof(vdev->name));

	/*
	 * Set the dwivew data befowe cawwing video_wegistew_device, othewwise
	 * the fiwe open() handwew might wace us.
	 */
	video_set_dwvdata(vdev, stweam);

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet < 0) {
		dev_eww(&stweam->intf->dev,
			"Faiwed to wegistew %s device (%d).\n",
			v4w2_type_names[type], wet);
		wetuwn wet;
	}

	kwef_get(&dev->wef);
	wetuwn 0;
}

static int uvc_wegistew_video(stwuct uvc_device *dev,
		stwuct uvc_stweaming *stweam)
{
	int wet;

	/* Initiawize the stweaming intewface with defauwt pawametews. */
	wet = uvc_video_init(stweam);
	if (wet < 0) {
		dev_eww(&stweam->intf->dev,
			"Faiwed to initiawize the device (%d).\n", wet);
		wetuwn wet;
	}

	if (stweam->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		stweam->chain->caps |= V4W2_CAP_VIDEO_CAPTUWE
			| V4W2_CAP_META_CAPTUWE;
	ewse
		stweam->chain->caps |= V4W2_CAP_VIDEO_OUTPUT;

	uvc_debugfs_init_stweam(stweam);

	/* Wegistew the device with V4W. */
	wetuwn uvc_wegistew_video_device(dev, stweam, &stweam->vdev,
					 &stweam->queue, stweam->type,
					 &uvc_fops, &uvc_ioctw_ops);
}

/*
 * Wegistew aww video devices in aww chains.
 */
static int uvc_wegistew_tewms(stwuct uvc_device *dev,
	stwuct uvc_video_chain *chain)
{
	stwuct uvc_stweaming *stweam;
	stwuct uvc_entity *tewm;
	int wet;

	wist_fow_each_entwy(tewm, &chain->entities, chain) {
		if (UVC_ENTITY_TYPE(tewm) != UVC_TT_STWEAMING)
			continue;

		stweam = uvc_stweam_by_id(dev, tewm->id);
		if (stweam == NUWW) {
			dev_info(&dev->udev->dev,
				 "No stweaming intewface found fow tewminaw %u.",
				 tewm->id);
			continue;
		}

		stweam->chain = chain;
		wet = uvc_wegistew_video(dev, stweam);
		if (wet < 0)
			wetuwn wet;

		/*
		 * Wegistew a metadata node, but ignowe a possibwe faiwuwe,
		 * compwete wegistwation of video nodes anyway.
		 */
		uvc_meta_wegistew(stweam);

		tewm->vdev = &stweam->vdev;
	}

	wetuwn 0;
}

static int uvc_wegistew_chains(stwuct uvc_device *dev)
{
	stwuct uvc_video_chain *chain;
	int wet;

	wist_fow_each_entwy(chain, &dev->chains, wist) {
		wet = uvc_wegistew_tewms(dev, chain);
		if (wet < 0)
			wetuwn wet;

#ifdef CONFIG_MEDIA_CONTWOWWEW
		wet = uvc_mc_wegistew_entities(chain);
		if (wet < 0)
			dev_info(&dev->udev->dev,
				 "Faiwed to wegistew entities (%d).\n", wet);
#endif
	}

	wetuwn 0;
}

/* ------------------------------------------------------------------------
 * USB pwobe, disconnect, suspend and wesume
 */

static const stwuct uvc_device_info uvc_quiwk_none = { 0 };

static int uvc_pwobe(stwuct usb_intewface *intf,
		     const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct uvc_device *dev;
	const stwuct uvc_device_info *info =
		(const stwuct uvc_device_info *)id->dwivew_info;
	int function;
	int wet;

	/* Awwocate memowy fow the device and initiawize it. */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (dev == NUWW)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&dev->entities);
	INIT_WIST_HEAD(&dev->chains);
	INIT_WIST_HEAD(&dev->stweams);
	kwef_init(&dev->wef);
	atomic_set(&dev->nmappings, 0);
	mutex_init(&dev->wock);

	dev->udev = usb_get_dev(udev);
	dev->intf = usb_get_intf(intf);
	dev->intfnum = intf->cuw_awtsetting->desc.bIntewfaceNumbew;
	dev->info = info ? info : &uvc_quiwk_none;
	dev->quiwks = uvc_quiwks_pawam == -1
		    ? dev->info->quiwks : uvc_quiwks_pawam;

	if (id->idVendow && id->idPwoduct)
		uvc_dbg(dev, PWOBE, "Pwobing known UVC device %s (%04x:%04x)\n",
			udev->devpath, id->idVendow, id->idPwoduct);
	ewse
		uvc_dbg(dev, PWOBE, "Pwobing genewic UVC device %s\n",
			udev->devpath);

	if (udev->pwoduct != NUWW)
		stwscpy(dev->name, udev->pwoduct, sizeof(dev->name));
	ewse
		snpwintf(dev->name, sizeof(dev->name),
			 "UVC Camewa (%04x:%04x)",
			 we16_to_cpu(udev->descwiptow.idVendow),
			 we16_to_cpu(udev->descwiptow.idPwoduct));

	/*
	 * Add iFunction ow iIntewface to names when avaiwabwe as additionaw
	 * distinguishews between intewfaces. iFunction is pwiowitized ovew
	 * iIntewface which matches Windows behaviow at the point of wwiting.
	 */
	if (intf->intf_assoc && intf->intf_assoc->iFunction != 0)
		function = intf->intf_assoc->iFunction;
	ewse
		function = intf->cuw_awtsetting->desc.iIntewface;
	if (function != 0) {
		size_t wen;

		stwwcat(dev->name, ": ", sizeof(dev->name));
		wen = stwwen(dev->name);
		usb_stwing(udev, function, dev->name + wen,
			   sizeof(dev->name) - wen);
	}

	/* Initiawize the media device. */
#ifdef CONFIG_MEDIA_CONTWOWWEW
	dev->mdev.dev = &intf->dev;
	stwscpy(dev->mdev.modew, dev->name, sizeof(dev->mdev.modew));
	if (udev->sewiaw)
		stwscpy(dev->mdev.sewiaw, udev->sewiaw,
			sizeof(dev->mdev.sewiaw));
	usb_make_path(udev, dev->mdev.bus_info, sizeof(dev->mdev.bus_info));
	dev->mdev.hw_wevision = we16_to_cpu(udev->descwiptow.bcdDevice);
	media_device_init(&dev->mdev);

	dev->vdev.mdev = &dev->mdev;
#endif

	/* Pawse the Video Cwass contwow descwiptow. */
	if (uvc_pawse_contwow(dev) < 0) {
		uvc_dbg(dev, PWOBE, "Unabwe to pawse UVC descwiptows\n");
		goto ewwow;
	}

	/* Pawse the associated GPIOs. */
	if (uvc_gpio_pawse(dev) < 0) {
		uvc_dbg(dev, PWOBE, "Unabwe to pawse UVC GPIOs\n");
		goto ewwow;
	}

	dev_info(&dev->udev->dev, "Found UVC %u.%02x device %s (%04x:%04x)\n",
		 dev->uvc_vewsion >> 8, dev->uvc_vewsion & 0xff,
		 udev->pwoduct ? udev->pwoduct : "<unnamed>",
		 we16_to_cpu(udev->descwiptow.idVendow),
		 we16_to_cpu(udev->descwiptow.idPwoduct));

	if (dev->quiwks != dev->info->quiwks) {
		dev_info(&dev->udev->dev,
			 "Fowcing device quiwks to 0x%x by moduwe pawametew fow testing puwpose.\n",
			 dev->quiwks);
		dev_info(&dev->udev->dev,
			 "Pwease wepowt wequiwed quiwks to the winux-media maiwing wist.\n");
	}

	if (dev->info->uvc_vewsion) {
		dev->uvc_vewsion = dev->info->uvc_vewsion;
		dev_info(&dev->udev->dev, "Fowcing UVC vewsion to %u.%02x\n",
			 dev->uvc_vewsion >> 8, dev->uvc_vewsion & 0xff);
	}

	/* Wegistew the V4W2 device. */
	if (v4w2_device_wegistew(&intf->dev, &dev->vdev) < 0)
		goto ewwow;

	/* Scan the device fow video chains. */
	if (uvc_scan_device(dev) < 0)
		goto ewwow;

	/* Initiawize contwows. */
	if (uvc_ctww_init_device(dev) < 0)
		goto ewwow;

	/* Wegistew video device nodes. */
	if (uvc_wegistew_chains(dev) < 0)
		goto ewwow;

#ifdef CONFIG_MEDIA_CONTWOWWEW
	/* Wegistew the media device node */
	if (media_device_wegistew(&dev->mdev) < 0)
		goto ewwow;
#endif
	/* Save ouw data pointew in the intewface data. */
	usb_set_intfdata(intf, dev);

	/* Initiawize the intewwupt UWB. */
	wet = uvc_status_init(dev);
	if (wet < 0) {
		dev_info(&dev->udev->dev,
			 "Unabwe to initiawize the status endpoint (%d), status intewwupt wiww not be suppowted.\n",
			 wet);
	}

	wet = uvc_gpio_init_iwq(dev);
	if (wet < 0) {
		dev_eww(&dev->udev->dev,
			"Unabwe to wequest pwivacy GPIO IWQ (%d)\n", wet);
		goto ewwow;
	}

	uvc_dbg(dev, PWOBE, "UVC device initiawized\n");
	usb_enabwe_autosuspend(udev);
	wetuwn 0;

ewwow:
	uvc_unwegistew_video(dev);
	kwef_put(&dev->wef, uvc_dewete);
	wetuwn -ENODEV;
}

static void uvc_disconnect(stwuct usb_intewface *intf)
{
	stwuct uvc_device *dev = usb_get_intfdata(intf);

	/*
	 * Set the USB intewface data to NUWW. This can be done outside the
	 * wock, as thewe's no othew weadew.
	 */
	usb_set_intfdata(intf, NUWW);

	if (intf->cuw_awtsetting->desc.bIntewfaceSubCwass ==
	    UVC_SC_VIDEOSTWEAMING)
		wetuwn;

	uvc_unwegistew_video(dev);
	kwef_put(&dev->wef, uvc_dewete);
}

static int uvc_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct uvc_device *dev = usb_get_intfdata(intf);
	stwuct uvc_stweaming *stweam;

	uvc_dbg(dev, SUSPEND, "Suspending intewface %u\n",
		intf->cuw_awtsetting->desc.bIntewfaceNumbew);

	/* Contwows awe cached on the fwy so they don't need to be saved. */
	if (intf->cuw_awtsetting->desc.bIntewfaceSubCwass ==
	    UVC_SC_VIDEOCONTWOW) {
		mutex_wock(&dev->wock);
		if (dev->usews)
			uvc_status_stop(dev);
		mutex_unwock(&dev->wock);
		wetuwn 0;
	}

	wist_fow_each_entwy(stweam, &dev->stweams, wist) {
		if (stweam->intf == intf)
			wetuwn uvc_video_suspend(stweam);
	}

	uvc_dbg(dev, SUSPEND,
		"Suspend: video stweaming USB intewface mismatch\n");
	wetuwn -EINVAW;
}

static int __uvc_wesume(stwuct usb_intewface *intf, int weset)
{
	stwuct uvc_device *dev = usb_get_intfdata(intf);
	stwuct uvc_stweaming *stweam;
	int wet = 0;

	uvc_dbg(dev, SUSPEND, "Wesuming intewface %u\n",
		intf->cuw_awtsetting->desc.bIntewfaceNumbew);

	if (intf->cuw_awtsetting->desc.bIntewfaceSubCwass ==
	    UVC_SC_VIDEOCONTWOW) {
		if (weset) {
			wet = uvc_ctww_westowe_vawues(dev);
			if (wet < 0)
				wetuwn wet;
		}

		mutex_wock(&dev->wock);
		if (dev->usews)
			wet = uvc_status_stawt(dev, GFP_NOIO);
		mutex_unwock(&dev->wock);

		wetuwn wet;
	}

	wist_fow_each_entwy(stweam, &dev->stweams, wist) {
		if (stweam->intf == intf) {
			wet = uvc_video_wesume(stweam, weset);
			if (wet < 0)
				uvc_queue_stweamoff(&stweam->queue,
						    stweam->queue.queue.type);
			wetuwn wet;
		}
	}

	uvc_dbg(dev, SUSPEND,
		"Wesume: video stweaming USB intewface mismatch\n");
	wetuwn -EINVAW;
}

static int uvc_wesume(stwuct usb_intewface *intf)
{
	wetuwn __uvc_wesume(intf, 0);
}

static int uvc_weset_wesume(stwuct usb_intewface *intf)
{
	wetuwn __uvc_wesume(intf, 1);
}

/* ------------------------------------------------------------------------
 * Moduwe pawametews
 */

static int uvc_cwock_pawam_get(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	if (uvc_cwock_pawam == CWOCK_MONOTONIC)
		wetuwn spwintf(buffew, "CWOCK_MONOTONIC");
	ewse
		wetuwn spwintf(buffew, "CWOCK_WEAWTIME");
}

static int uvc_cwock_pawam_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	if (stwncasecmp(vaw, "cwock_", stwwen("cwock_")) == 0)
		vaw += stwwen("cwock_");

	if (stwcasecmp(vaw, "monotonic") == 0)
		uvc_cwock_pawam = CWOCK_MONOTONIC;
	ewse if (stwcasecmp(vaw, "weawtime") == 0)
		uvc_cwock_pawam = CWOCK_WEAWTIME;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

moduwe_pawam_caww(cwock, uvc_cwock_pawam_set, uvc_cwock_pawam_get,
		  &uvc_cwock_pawam, 0644);
MODUWE_PAWM_DESC(cwock, "Video buffews timestamp cwock");
moduwe_pawam_named(hwtimestamps, uvc_hw_timestamps_pawam, uint, 0644);
MODUWE_PAWM_DESC(hwtimestamps, "Use hawdwawe timestamps");
moduwe_pawam_named(nodwop, uvc_no_dwop_pawam, uint, 0644);
MODUWE_PAWM_DESC(nodwop, "Don't dwop incompwete fwames");
moduwe_pawam_named(quiwks, uvc_quiwks_pawam, uint, 0644);
MODUWE_PAWM_DESC(quiwks, "Fowced device quiwks");
moduwe_pawam_named(twace, uvc_dbg_pawam, uint, 0644);
MODUWE_PAWM_DESC(twace, "Twace wevew bitmask");
moduwe_pawam_named(timeout, uvc_timeout_pawam, uint, 0644);
MODUWE_PAWM_DESC(timeout, "Stweaming contwow wequests timeout");

/* ------------------------------------------------------------------------
 * Dwivew initiawization and cweanup
 */

static const stwuct uvc_device_info uvc_ctww_powew_wine_wimited = {
	.mappings = (const stwuct uvc_contwow_mapping *[]) {
		&uvc_ctww_powew_wine_mapping_wimited,
		NUWW, /* Sentinew */
	},
};

static const stwuct uvc_device_info uvc_ctww_powew_wine_uvc11 = {
	.mappings = (const stwuct uvc_contwow_mapping *[]) {
		&uvc_ctww_powew_wine_mapping_uvc11,
		NUWW, /* Sentinew */
	},
};

static const stwuct uvc_device_info uvc_quiwk_pwobe_minmax = {
	.quiwks = UVC_QUIWK_PWOBE_MINMAX,
};

static const stwuct uvc_device_info uvc_quiwk_fix_bandwidth = {
	.quiwks = UVC_QUIWK_FIX_BANDWIDTH,
};

static const stwuct uvc_device_info uvc_quiwk_pwobe_def = {
	.quiwks = UVC_QUIWK_PWOBE_DEF,
};

static const stwuct uvc_device_info uvc_quiwk_stweam_no_fid = {
	.quiwks = UVC_QUIWK_STWEAM_NO_FID,
};

static const stwuct uvc_device_info uvc_quiwk_fowce_y8 = {
	.quiwks = UVC_QUIWK_FOWCE_Y8,
};

#define UVC_INFO_QUIWK(q) (kewnew_uwong_t)&(stwuct uvc_device_info){.quiwks = q}
#define UVC_INFO_META(m) (kewnew_uwong_t)&(stwuct uvc_device_info) \
	{.meta_fowmat = m}

/*
 * The Wogitech camewas wisted bewow have theiw intewface cwass set to
 * VENDOW_SPEC because they don't announce themsewves as UVC devices, even
 * though they awe compwiant.
 */
static const stwuct usb_device_id uvc_ids[] = {
	/* Quanta USB2.0 HD UVC Webcam */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x0408,
	  .idPwoduct		= 0x3090,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_wimited },
	/* Quanta USB2.0 HD UVC Webcam */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x0408,
	  .idPwoduct		= 0x4030,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_wimited },
	/* Quanta USB2.0 HD UVC Webcam */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x0408,
	  .idPwoduct		= 0x4034,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= UVC_PC_PWOTOCOW_15,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_wimited },
	/* WogiWink Wiwewess Webcam */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x0416,
	  .idPwoduct		= 0xa91a,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_minmax },
	/* Genius eFace 2025 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x0458,
	  .idPwoduct		= 0x706e,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_minmax },
	/* Micwosoft Wifecam NX-6000 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x045e,
	  .idPwoduct		= 0x00f8,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_minmax },
	/* Micwosoft Wifecam NX-3000 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x045e,
	  .idPwoduct		= 0x0721,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_def },
	/* Micwosoft Wifecam VX-7000 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x045e,
	  .idPwoduct		= 0x0723,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_minmax },
	/* Wogitech, Webcam C910 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x046d,
	  .idPwoduct		= 0x0821,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_QUIWK(UVC_QUIWK_WAKE_AUTOSUSPEND)},
	/* Wogitech, Webcam B910 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x046d,
	  .idPwoduct		= 0x0823,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_QUIWK(UVC_QUIWK_WAKE_AUTOSUSPEND)},
	/* Wogitech Quickcam Fusion */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x046d,
	  .idPwoduct		= 0x08c1,
	  .bIntewfaceCwass	= USB_CWASS_VENDOW_SPEC,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0 },
	/* Wogitech Quickcam Owbit MP */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x046d,
	  .idPwoduct		= 0x08c2,
	  .bIntewfaceCwass	= USB_CWASS_VENDOW_SPEC,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0 },
	/* Wogitech Quickcam Pwo fow Notebook */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x046d,
	  .idPwoduct		= 0x08c3,
	  .bIntewfaceCwass	= USB_CWASS_VENDOW_SPEC,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0 },
	/* Wogitech Quickcam Pwo 5000 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x046d,
	  .idPwoduct		= 0x08c5,
	  .bIntewfaceCwass	= USB_CWASS_VENDOW_SPEC,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0 },
	/* Wogitech Quickcam OEM Deww Notebook */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x046d,
	  .idPwoduct		= 0x08c6,
	  .bIntewfaceCwass	= USB_CWASS_VENDOW_SPEC,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0 },
	/* Wogitech Quickcam OEM Cisco VT Camewa II */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x046d,
	  .idPwoduct		= 0x08c7,
	  .bIntewfaceCwass	= USB_CWASS_VENDOW_SPEC,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0 },
	/* Wogitech HD Pwo Webcam C920 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x046d,
	  .idPwoduct		= 0x082d,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_QUIWK(UVC_QUIWK_WESTOWE_CTWWS_ON_INIT) },
	/* Chicony CNF7129 (Asus EEE 100HE) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x04f2,
	  .idPwoduct		= 0xb071,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_QUIWK(UVC_QUIWK_WESTWICT_FWAME_WATE) },
	/* Chicony EasyCamewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x04f2,
	  .idPwoduct		= 0xb5eb,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_wimited },
	/* Chicony Ewectwonics Co., Wtd Integwated Camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x04f2,
	  .idPwoduct		= 0xb67c,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= UVC_PC_PWOTOCOW_15,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_uvc11 },
	/* Chicony EasyCamewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x04f2,
	  .idPwoduct		= 0xb6ba,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_wimited },
	/* Chicony EasyCamewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x04f2,
	  .idPwoduct		= 0xb746,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_wimited },
	/* Awcow Micwo AU3820 (Futuwe Boy PC USB Webcam) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x058f,
	  .idPwoduct		= 0x3820,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_minmax },
	/* Deww XPS m1530 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x05a9,
	  .idPwoduct		= 0x2640,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_def },
	/* Deww SP2008WFP Monitow */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x05a9,
	  .idPwoduct		= 0x2641,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_def },
	/* Deww Awienwawe X51 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x05a9,
	  .idPwoduct		= 0x2643,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_def },
	/* Deww Studio Hybwid 140g (OmniVision webcam) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x05a9,
	  .idPwoduct		= 0x264a,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_def },
	/* Deww XPS M1330 (OmniVision OV7670 webcam) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x05a9,
	  .idPwoduct		= 0x7670,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_def },
	/* Appwe Buiwt-In iSight */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x05ac,
	  .idPwoduct		= 0x8501,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_QUIWK(UVC_QUIWK_PWOBE_MINMAX
					| UVC_QUIWK_BUIWTIN_ISIGHT) },
	/* Appwe FaceTime HD Camewa (Buiwt-In) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x05ac,
	  .idPwoduct		= 0x8514,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_def },
	/* Appwe Buiwt-In iSight via iBwidge */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x05ac,
	  .idPwoduct		= 0x8600,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_def },
	/* Foxwink ("HP Webcam" on HP Mini 5103) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x05c8,
	  .idPwoduct		= 0x0403,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_fix_bandwidth },
	/* Genesys Wogic USB 2.0 PC Camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x05e3,
	  .idPwoduct		= 0x0505,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_stweam_no_fid },
	/* Hewcuwes Cwassic Siwvew */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x06f8,
	  .idPwoduct		= 0x300c,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_fix_bandwidth },
	/* ViMicwo Vega */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x0ac8,
	  .idPwoduct		= 0x332d,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_fix_bandwidth },
	/* ViMicwo - Minowu3D */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x0ac8,
	  .idPwoduct		= 0x3410,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_fix_bandwidth },
	/* ViMicwo Venus - Minowu3D */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x0ac8,
	  .idPwoduct		= 0x3420,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_fix_bandwidth },
	/* Ophiw Optwonics - SPCAM 620U */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x0bd3,
	  .idPwoduct		= 0x0555,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_minmax },
	/* MT6227 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x0e8d,
	  .idPwoduct		= 0x0004,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_QUIWK(UVC_QUIWK_PWOBE_MINMAX
					| UVC_QUIWK_PWOBE_DEF) },
	/* IMC Netwowks (Medion Akoya) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x13d3,
	  .idPwoduct		= 0x5103,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_stweam_no_fid },
	/* JMicwon USB2.0 XGA WebCam */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x152d,
	  .idPwoduct		= 0x0310,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_minmax },
	/* Syntek (HP Spawtan) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x174f,
	  .idPwoduct		= 0x5212,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_stweam_no_fid },
	/* Syntek (Samsung Q310) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x174f,
	  .idPwoduct		= 0x5931,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_stweam_no_fid },
	/* Syntek (Packawd Beww EasyNote MX52 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x174f,
	  .idPwoduct		= 0x8a12,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_stweam_no_fid },
	/* Syntek (Asus F9SG) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x174f,
	  .idPwoduct		= 0x8a31,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_stweam_no_fid },
	/* Syntek (Asus U3S) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x174f,
	  .idPwoduct		= 0x8a33,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_stweam_no_fid },
	/* Syntek (JAOtech Smawt Tewminaw) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x174f,
	  .idPwoduct		= 0x8a34,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_stweam_no_fid },
	/* Miwicwe 307K */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x17dc,
	  .idPwoduct		= 0x0202,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_stweam_no_fid },
	/* Wenovo Thinkpad SW400/SW500 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x17ef,
	  .idPwoduct		= 0x480b,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_stweam_no_fid },
	/* Aveo Technowogy USB 2.0 Camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x1871,
	  .idPwoduct		= 0x0306,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_QUIWK(UVC_QUIWK_PWOBE_MINMAX
					| UVC_QUIWK_PWOBE_EXTWAFIEWDS) },
	/* Aveo Technowogy USB 2.0 Camewa (Tasco USB Micwoscope) */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x1871,
	  .idPwoduct		= 0x0516,
	  .bIntewfaceCwass	= USB_CWASS_VENDOW_SPEC,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0 },
	/* Ecamm Pico iMage */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x18cd,
	  .idPwoduct		= 0xcafe,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_QUIWK(UVC_QUIWK_PWOBE_EXTWAFIEWDS) },
	/* Manta MM-353 Pwako */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x18ec,
	  .idPwoduct		= 0x3188,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_minmax },
	/* FSC WebCam V30S */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x18ec,
	  .idPwoduct		= 0x3288,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_minmax },
	/* Awkmicwo unbwanded */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x18ec,
	  .idPwoduct		= 0x3290,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_def },
	/* The Imaging Souwce USB CCD camewas */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x199e,
	  .idPwoduct		= 0x8102,
	  .bIntewfaceCwass	= USB_CWASS_VENDOW_SPEC,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0 },
	/* Bodewin PwoScopeHW */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_DEV_HI
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x19ab,
	  .idPwoduct		= 0x1000,
	  .bcdDevice_hi		= 0x0126,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_QUIWK(UVC_QUIWK_STATUS_INTEWVAW) },
	/* MSI StawCam 370i */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x1b3b,
	  .idPwoduct		= 0x2951,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_minmax },
	/* Genewawpwus Technowogy Inc. 808 Camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x1b3f,
	  .idPwoduct		= 0x2002,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_pwobe_minmax },
	/* Shenzhen Aoni Ewectwonic Co.,Wtd 2K FHD camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x1bcf,
	  .idPwoduct		= 0x0b40,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&(const stwuct uvc_device_info){
		.uvc_vewsion = 0x010a,
	  } },
	/* SiGma Micwo USB Web Camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x1c4f,
	  .idPwoduct		= 0x3000,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_QUIWK(UVC_QUIWK_PWOBE_MINMAX
					| UVC_QUIWK_IGNOWE_SEWECTOW_UNIT) },
	/* Ocuwus VW Positionaw Twackew DK2 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x2833,
	  .idPwoduct		= 0x0201,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_fowce_y8 },
	/* Ocuwus VW Wift Sensow */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x2833,
	  .idPwoduct		= 0x0211,
	  .bIntewfaceCwass	= USB_CWASS_VENDOW_SPEC,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_quiwk_fowce_y8 },
	/* GEO Semiconductow GC6500 */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x29fe,
	  .idPwoduct		= 0x4d53,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_QUIWK(UVC_QUIWK_FOWCE_BPP) },
	/* SunpwusIT Inc HD Camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x2b7e,
	  .idPwoduct		= 0xb752,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= UVC_PC_PWOTOCOW_15,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_uvc11 },
	/* Wenovo Integwated Camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x30c9,
	  .idPwoduct		= 0x0093,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= UVC_PC_PWOTOCOW_15,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_uvc11 },
	/* Sonix Technowogy USB 2.0 Camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x3277,
	  .idPwoduct		= 0x0072,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_wimited },
	/* Acew EasyCamewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x5986,
	  .idPwoduct		= 0x1172,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_wimited },
	/* Acew EasyCamewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x5986,
	  .idPwoduct		= 0x1180,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= (kewnew_uwong_t)&uvc_ctww_powew_wine_wimited },
	/* Intew D410/ASW depth camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x8086,
	  .idPwoduct		= 0x0ad2,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_META(V4W2_META_FMT_D4XX) },
	/* Intew D415/ASWC depth camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x8086,
	  .idPwoduct		= 0x0ad3,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_META(V4W2_META_FMT_D4XX) },
	/* Intew D430/AWG depth camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x8086,
	  .idPwoduct		= 0x0ad4,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_META(V4W2_META_FMT_D4XX) },
	/* Intew WeawSense D4M */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x8086,
	  .idPwoduct		= 0x0b03,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_META(V4W2_META_FMT_D4XX) },
	/* Intew D435/AWGC depth camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x8086,
	  .idPwoduct		= 0x0b07,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_META(V4W2_META_FMT_D4XX) },
	/* Intew D435i depth camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x8086,
	  .idPwoduct		= 0x0b3a,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_META(V4W2_META_FMT_D4XX) },
	/* Intew D405 Depth Camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x8086,
	  .idPwoduct		= 0x0b5b,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_META(V4W2_META_FMT_D4XX) },
	/* Intew D455 Depth Camewa */
	{ .match_fwags		= USB_DEVICE_ID_MATCH_DEVICE
				| USB_DEVICE_ID_MATCH_INT_INFO,
	  .idVendow		= 0x8086,
	  .idPwoduct		= 0x0b5c,
	  .bIntewfaceCwass	= USB_CWASS_VIDEO,
	  .bIntewfaceSubCwass	= 1,
	  .bIntewfacePwotocow	= 0,
	  .dwivew_info		= UVC_INFO_META(V4W2_META_FMT_D4XX) },
	/* Genewic USB Video Cwass */
	{ USB_INTEWFACE_INFO(USB_CWASS_VIDEO, 1, UVC_PC_PWOTOCOW_UNDEFINED) },
	{ USB_INTEWFACE_INFO(USB_CWASS_VIDEO, 1, UVC_PC_PWOTOCOW_15) },
	{}
};

MODUWE_DEVICE_TABWE(usb, uvc_ids);

stwuct uvc_dwivew uvc_dwivew = {
	.dwivew = {
		.name		= "uvcvideo",
		.pwobe		= uvc_pwobe,
		.disconnect	= uvc_disconnect,
		.suspend	= uvc_suspend,
		.wesume		= uvc_wesume,
		.weset_wesume	= uvc_weset_wesume,
		.id_tabwe	= uvc_ids,
		.suppowts_autosuspend = 1,
	},
};

static int __init uvc_init(void)
{
	int wet;

	uvc_debugfs_init();

	wet = usb_wegistew(&uvc_dwivew.dwivew);
	if (wet < 0) {
		uvc_debugfs_cweanup();
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit uvc_cweanup(void)
{
	usb_dewegistew(&uvc_dwivew.dwivew);
	uvc_debugfs_cweanup();
}

moduwe_init(uvc_init);
moduwe_exit(uvc_cweanup);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWIVEW_VEWSION);

