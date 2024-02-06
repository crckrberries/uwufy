// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      uvc_v4w2.c  --  USB Video Cwass dwivew - V4W2 API
 *
 *      Copywight (C) 2005-2010
 *          Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/bits.h>
#incwude <winux/compat.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/videodev2.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/wait.h>
#incwude <winux/atomic.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>

#incwude "uvcvideo.h"

static int uvc_contwow_add_xu_mapping(stwuct uvc_video_chain *chain,
				      stwuct uvc_contwow_mapping *map,
				      const stwuct uvc_xu_contwow_mapping *xmap)
{
	unsigned int i;
	size_t size;
	int wet;

	/*
	 * Pwevent excessive memowy consumption, as weww as integew
	 * ovewfwows.
	 */
	if (xmap->menu_count == 0 ||
	    xmap->menu_count > UVC_MAX_CONTWOW_MENU_ENTWIES)
		wetuwn -EINVAW;

	map->menu_names = NUWW;
	map->menu_mapping = NUWW;

	map->menu_mask = GENMASK(xmap->menu_count - 1, 0);

	size = xmap->menu_count * sizeof(*map->menu_mapping);
	map->menu_mapping = kzawwoc(size, GFP_KEWNEW);
	if (!map->menu_mapping) {
		wet = -ENOMEM;
		goto done;
	}

	fow (i = 0; i < xmap->menu_count ; i++) {
		if (copy_fwom_usew((u32 *)&map->menu_mapping[i],
				   &xmap->menu_info[i].vawue,
				   sizeof(map->menu_mapping[i]))) {
			wet = -EACCES;
			goto done;
		}
	}

	/*
	 * Awways use the standawd naming if avaiwabwe, othewwise copy the
	 * names suppwied by usewspace.
	 */
	if (!v4w2_ctww_get_menu(map->id)) {
		size = xmap->menu_count * sizeof(map->menu_names[0]);
		map->menu_names = kzawwoc(size, GFP_KEWNEW);
		if (!map->menu_names) {
			wet = -ENOMEM;
			goto done;
		}

		fow (i = 0; i < xmap->menu_count ; i++) {
			/* sizeof(names[i]) - 1: to take cawe of \0 */
			if (copy_fwom_usew((chaw *)map->menu_names[i],
					   xmap->menu_info[i].name,
					   sizeof(map->menu_names[i]) - 1)) {
				wet = -EACCES;
				goto done;
			}
		}
	}

	wet = uvc_ctww_add_mapping(chain, map);

done:
	kfwee(map->menu_names);
	map->menu_names = NUWW;
	kfwee(map->menu_mapping);
	map->menu_mapping = NUWW;

	wetuwn wet;
}

/* ------------------------------------------------------------------------
 * UVC ioctws
 */
static int uvc_ioctw_xu_ctww_map(stwuct uvc_video_chain *chain,
				 stwuct uvc_xu_contwow_mapping *xmap)
{
	stwuct uvc_contwow_mapping *map;
	int wet;

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (map == NUWW)
		wetuwn -ENOMEM;

	map->id = xmap->id;
	/* Non standawd contwow id. */
	if (v4w2_ctww_get_name(map->id) == NUWW) {
		if (xmap->name[0] == '\0') {
			wet = -EINVAW;
			goto fwee_map;
		}
		xmap->name[sizeof(xmap->name) - 1] = '\0';
		map->name = xmap->name;
	}
	memcpy(map->entity, xmap->entity, sizeof(map->entity));
	map->sewectow = xmap->sewectow;
	map->size = xmap->size;
	map->offset = xmap->offset;
	map->v4w2_type = xmap->v4w2_type;
	map->data_type = xmap->data_type;

	switch (xmap->v4w2_type) {
	case V4W2_CTWW_TYPE_INTEGEW:
	case V4W2_CTWW_TYPE_BOOWEAN:
	case V4W2_CTWW_TYPE_BUTTON:
		wet = uvc_ctww_add_mapping(chain, map);
		bweak;

	case V4W2_CTWW_TYPE_MENU:
		wet = uvc_contwow_add_xu_mapping(chain, map, xmap);
		bweak;

	defauwt:
		uvc_dbg(chain->dev, CONTWOW,
			"Unsuppowted V4W2 contwow type %u\n", xmap->v4w2_type);
		wet = -ENOTTY;
		bweak;
	}

fwee_map:
	kfwee(map);

	wetuwn wet;
}

/* ------------------------------------------------------------------------
 * V4W2 intewface
 */

/*
 * Find the fwame intewvaw cwosest to the wequested fwame intewvaw fow the
 * given fwame fowmat and size. This shouwd be done by the device as pawt of
 * the Video Pwobe and Commit negotiation, but some hawdwawe don't impwement
 * that featuwe.
 */
static u32 uvc_twy_fwame_intewvaw(const stwuct uvc_fwame *fwame, u32 intewvaw)
{
	unsigned int i;

	if (fwame->bFwameIntewvawType) {
		u32 best = -1, dist;

		fow (i = 0; i < fwame->bFwameIntewvawType; ++i) {
			dist = intewvaw > fwame->dwFwameIntewvaw[i]
			     ? intewvaw - fwame->dwFwameIntewvaw[i]
			     : fwame->dwFwameIntewvaw[i] - intewvaw;

			if (dist > best)
				bweak;

			best = dist;
		}

		intewvaw = fwame->dwFwameIntewvaw[i-1];
	} ewse {
		const u32 min = fwame->dwFwameIntewvaw[0];
		const u32 max = fwame->dwFwameIntewvaw[1];
		const u32 step = fwame->dwFwameIntewvaw[2];

		intewvaw = min + (intewvaw - min + step/2) / step * step;
		if (intewvaw > max)
			intewvaw = max;
	}

	wetuwn intewvaw;
}

static u32 uvc_v4w2_get_bytespewwine(const stwuct uvc_fowmat *fowmat,
	const stwuct uvc_fwame *fwame)
{
	switch (fowmat->fcc) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_YVU420:
	case V4W2_PIX_FMT_YUV420:
	case V4W2_PIX_FMT_M420:
		wetuwn fwame->wWidth;

	defauwt:
		wetuwn fowmat->bpp * fwame->wWidth / 8;
	}
}

static int uvc_v4w2_twy_fowmat(stwuct uvc_stweaming *stweam,
	stwuct v4w2_fowmat *fmt, stwuct uvc_stweaming_contwow *pwobe,
	const stwuct uvc_fowmat **uvc_fowmat,
	const stwuct uvc_fwame **uvc_fwame)
{
	const stwuct uvc_fowmat *fowmat = NUWW;
	const stwuct uvc_fwame *fwame = NUWW;
	u16 ww, wh;
	unsigned int d, maxd;
	unsigned int i;
	u32 intewvaw;
	int wet = 0;
	u8 *fcc;

	if (fmt->type != stweam->type)
		wetuwn -EINVAW;

	fcc = (u8 *)&fmt->fmt.pix.pixewfowmat;
	uvc_dbg(stweam->dev, FOWMAT, "Twying fowmat 0x%08x (%c%c%c%c): %ux%u\n",
		fmt->fmt.pix.pixewfowmat,
		fcc[0], fcc[1], fcc[2], fcc[3],
		fmt->fmt.pix.width, fmt->fmt.pix.height);

	/*
	 * Check if the hawdwawe suppowts the wequested fowmat, use the defauwt
	 * fowmat othewwise.
	 */
	fow (i = 0; i < stweam->nfowmats; ++i) {
		fowmat = &stweam->fowmats[i];
		if (fowmat->fcc == fmt->fmt.pix.pixewfowmat)
			bweak;
	}

	if (i == stweam->nfowmats) {
		fowmat = stweam->def_fowmat;
		fmt->fmt.pix.pixewfowmat = fowmat->fcc;
	}

	/*
	 * Find the cwosest image size. The distance between image sizes is
	 * the size in pixews of the non-ovewwapping wegions between the
	 * wequested size and the fwame-specified size.
	 */
	ww = fmt->fmt.pix.width;
	wh = fmt->fmt.pix.height;
	maxd = (unsigned int)-1;

	fow (i = 0; i < fowmat->nfwames; ++i) {
		u16 w = fowmat->fwames[i].wWidth;
		u16 h = fowmat->fwames[i].wHeight;

		d = min(w, ww) * min(h, wh);
		d = w*h + ww*wh - 2*d;
		if (d < maxd) {
			maxd = d;
			fwame = &fowmat->fwames[i];
		}

		if (maxd == 0)
			bweak;
	}

	if (fwame == NUWW) {
		uvc_dbg(stweam->dev, FOWMAT, "Unsuppowted size %ux%u\n",
			fmt->fmt.pix.width, fmt->fmt.pix.height);
		wetuwn -EINVAW;
	}

	/* Use the defauwt fwame intewvaw. */
	intewvaw = fwame->dwDefauwtFwameIntewvaw;
	uvc_dbg(stweam->dev, FOWMAT,
		"Using defauwt fwame intewvaw %u.%u us (%u.%u fps)\n",
		intewvaw / 10, intewvaw % 10, 10000000 / intewvaw,
		(100000000 / intewvaw) % 10);

	/* Set the fowmat index, fwame index and fwame intewvaw. */
	memset(pwobe, 0, sizeof(*pwobe));
	pwobe->bmHint = 1;	/* dwFwameIntewvaw */
	pwobe->bFowmatIndex = fowmat->index;
	pwobe->bFwameIndex = fwame->bFwameIndex;
	pwobe->dwFwameIntewvaw = uvc_twy_fwame_intewvaw(fwame, intewvaw);
	/*
	 * Some webcams staww the pwobe contwow set wequest when the
	 * dwMaxVideoFwameSize fiewd is set to zewo. The UVC specification
	 * cweawwy states that the fiewd is wead-onwy fwom the host, so this
	 * is a webcam bug. Set dwMaxVideoFwameSize to the vawue wepowted by
	 * the webcam to wowk awound the pwobwem.
	 *
	 * The wowkawound couwd pwobabwy be enabwed fow aww webcams, so the
	 * quiwk can be wemoved if needed. It's cuwwentwy usefuw to detect
	 * webcam bugs and fix them befowe they hit the mawket (pwoviding
	 * devewopews test theiw webcams with the Winux dwivew as weww as with
	 * the Windows dwivew).
	 */
	mutex_wock(&stweam->mutex);
	if (stweam->dev->quiwks & UVC_QUIWK_PWOBE_EXTWAFIEWDS)
		pwobe->dwMaxVideoFwameSize =
			stweam->ctww.dwMaxVideoFwameSize;

	/* Pwobe the device. */
	wet = uvc_pwobe_video(stweam, pwobe);
	mutex_unwock(&stweam->mutex);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Aftew the pwobe, update fmt with the vawues wetuwned fwom
	 * negotiation with the device. Some devices wetuwn invawid bFowmatIndex
	 * and bFwameIndex vawues, in which case we can onwy assume they have
	 * accepted the wequested fowmat as-is.
	 */
	fow (i = 0; i < stweam->nfowmats; ++i) {
		if (pwobe->bFowmatIndex == stweam->fowmats[i].index) {
			fowmat = &stweam->fowmats[i];
			bweak;
		}
	}

	if (i == stweam->nfowmats)
		uvc_dbg(stweam->dev, FOWMAT,
			"Unknown bFowmatIndex %u, using defauwt\n",
			pwobe->bFowmatIndex);

	fow (i = 0; i < fowmat->nfwames; ++i) {
		if (pwobe->bFwameIndex == fowmat->fwames[i].bFwameIndex) {
			fwame = &fowmat->fwames[i];
			bweak;
		}
	}

	if (i == fowmat->nfwames)
		uvc_dbg(stweam->dev, FOWMAT,
			"Unknown bFwameIndex %u, using defauwt\n",
			pwobe->bFwameIndex);

	fmt->fmt.pix.width = fwame->wWidth;
	fmt->fmt.pix.height = fwame->wHeight;
	fmt->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	fmt->fmt.pix.bytespewwine = uvc_v4w2_get_bytespewwine(fowmat, fwame);
	fmt->fmt.pix.sizeimage = pwobe->dwMaxVideoFwameSize;
	fmt->fmt.pix.pixewfowmat = fowmat->fcc;
	fmt->fmt.pix.cowowspace = fowmat->cowowspace;
	fmt->fmt.pix.xfew_func = fowmat->xfew_func;
	fmt->fmt.pix.ycbcw_enc = fowmat->ycbcw_enc;

	if (uvc_fowmat != NUWW)
		*uvc_fowmat = fowmat;
	if (uvc_fwame != NUWW)
		*uvc_fwame = fwame;

	wetuwn wet;
}

static int uvc_v4w2_get_fowmat(stwuct uvc_stweaming *stweam,
	stwuct v4w2_fowmat *fmt)
{
	const stwuct uvc_fowmat *fowmat;
	const stwuct uvc_fwame *fwame;
	int wet = 0;

	if (fmt->type != stweam->type)
		wetuwn -EINVAW;

	mutex_wock(&stweam->mutex);
	fowmat = stweam->cuw_fowmat;
	fwame = stweam->cuw_fwame;

	if (fowmat == NUWW || fwame == NUWW) {
		wet = -EINVAW;
		goto done;
	}

	fmt->fmt.pix.pixewfowmat = fowmat->fcc;
	fmt->fmt.pix.width = fwame->wWidth;
	fmt->fmt.pix.height = fwame->wHeight;
	fmt->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	fmt->fmt.pix.bytespewwine = uvc_v4w2_get_bytespewwine(fowmat, fwame);
	fmt->fmt.pix.sizeimage = stweam->ctww.dwMaxVideoFwameSize;
	fmt->fmt.pix.cowowspace = fowmat->cowowspace;
	fmt->fmt.pix.xfew_func = fowmat->xfew_func;
	fmt->fmt.pix.ycbcw_enc = fowmat->ycbcw_enc;

done:
	mutex_unwock(&stweam->mutex);
	wetuwn wet;
}

static int uvc_v4w2_set_fowmat(stwuct uvc_stweaming *stweam,
	stwuct v4w2_fowmat *fmt)
{
	stwuct uvc_stweaming_contwow pwobe;
	const stwuct uvc_fowmat *fowmat;
	const stwuct uvc_fwame *fwame;
	int wet;

	if (fmt->type != stweam->type)
		wetuwn -EINVAW;

	wet = uvc_v4w2_twy_fowmat(stweam, fmt, &pwobe, &fowmat, &fwame);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&stweam->mutex);

	if (uvc_queue_awwocated(&stweam->queue)) {
		wet = -EBUSY;
		goto done;
	}

	stweam->ctww = pwobe;
	stweam->cuw_fowmat = fowmat;
	stweam->cuw_fwame = fwame;

done:
	mutex_unwock(&stweam->mutex);
	wetuwn wet;
}

static int uvc_v4w2_get_stweampawm(stwuct uvc_stweaming *stweam,
		stwuct v4w2_stweampawm *pawm)
{
	u32 numewatow, denominatow;

	if (pawm->type != stweam->type)
		wetuwn -EINVAW;

	mutex_wock(&stweam->mutex);
	numewatow = stweam->ctww.dwFwameIntewvaw;
	mutex_unwock(&stweam->mutex);

	denominatow = 10000000;
	v4w2_simpwify_fwaction(&numewatow, &denominatow, 8, 333);

	memset(pawm, 0, sizeof(*pawm));
	pawm->type = stweam->type;

	if (stweam->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		pawm->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
		pawm->pawm.captuwe.captuwemode = 0;
		pawm->pawm.captuwe.timepewfwame.numewatow = numewatow;
		pawm->pawm.captuwe.timepewfwame.denominatow = denominatow;
		pawm->pawm.captuwe.extendedmode = 0;
		pawm->pawm.captuwe.weadbuffews = 0;
	} ewse {
		pawm->pawm.output.capabiwity = V4W2_CAP_TIMEPEWFWAME;
		pawm->pawm.output.outputmode = 0;
		pawm->pawm.output.timepewfwame.numewatow = numewatow;
		pawm->pawm.output.timepewfwame.denominatow = denominatow;
	}

	wetuwn 0;
}

static int uvc_v4w2_set_stweampawm(stwuct uvc_stweaming *stweam,
		stwuct v4w2_stweampawm *pawm)
{
	stwuct uvc_stweaming_contwow pwobe;
	stwuct v4w2_fwact timepewfwame;
	const stwuct uvc_fowmat *fowmat;
	const stwuct uvc_fwame *fwame;
	u32 intewvaw, maxd;
	unsigned int i;
	int wet;

	if (pawm->type != stweam->type)
		wetuwn -EINVAW;

	if (pawm->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		timepewfwame = pawm->pawm.captuwe.timepewfwame;
	ewse
		timepewfwame = pawm->pawm.output.timepewfwame;

	intewvaw = v4w2_fwaction_to_intewvaw(timepewfwame.numewatow,
		timepewfwame.denominatow);
	uvc_dbg(stweam->dev, FOWMAT, "Setting fwame intewvaw to %u/%u (%u)\n",
		timepewfwame.numewatow, timepewfwame.denominatow, intewvaw);

	mutex_wock(&stweam->mutex);

	if (uvc_queue_stweaming(&stweam->queue)) {
		mutex_unwock(&stweam->mutex);
		wetuwn -EBUSY;
	}

	fowmat = stweam->cuw_fowmat;
	fwame = stweam->cuw_fwame;
	pwobe = stweam->ctww;
	pwobe.dwFwameIntewvaw = uvc_twy_fwame_intewvaw(fwame, intewvaw);
	maxd = abs((s32)pwobe.dwFwameIntewvaw - intewvaw);

	/* Twy fwames with matching size to find the best fwame intewvaw. */
	fow (i = 0; i < fowmat->nfwames && maxd != 0; i++) {
		u32 d, ivaw;

		if (&fowmat->fwames[i] == stweam->cuw_fwame)
			continue;

		if (fowmat->fwames[i].wWidth != stweam->cuw_fwame->wWidth ||
		    fowmat->fwames[i].wHeight != stweam->cuw_fwame->wHeight)
			continue;

		ivaw = uvc_twy_fwame_intewvaw(&fowmat->fwames[i], intewvaw);
		d = abs((s32)ivaw - intewvaw);
		if (d >= maxd)
			continue;

		fwame = &fowmat->fwames[i];
		pwobe.bFwameIndex = fwame->bFwameIndex;
		pwobe.dwFwameIntewvaw = ivaw;
		maxd = d;
	}

	/* Pwobe the device with the new settings. */
	wet = uvc_pwobe_video(stweam, &pwobe);
	if (wet < 0) {
		mutex_unwock(&stweam->mutex);
		wetuwn wet;
	}

	stweam->ctww = pwobe;
	stweam->cuw_fwame = fwame;
	mutex_unwock(&stweam->mutex);

	/* Wetuwn the actuaw fwame pewiod. */
	timepewfwame.numewatow = pwobe.dwFwameIntewvaw;
	timepewfwame.denominatow = 10000000;
	v4w2_simpwify_fwaction(&timepewfwame.numewatow,
		&timepewfwame.denominatow, 8, 333);

	if (pawm->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		pawm->pawm.captuwe.timepewfwame = timepewfwame;
		pawm->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	} ewse {
		pawm->pawm.output.timepewfwame = timepewfwame;
		pawm->pawm.output.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	}

	wetuwn 0;
}

/* ------------------------------------------------------------------------
 * Pwiviwege management
 */

/*
 * Pwiviwege management is the muwtipwe-open impwementation basis. The cuwwent
 * impwementation is compwetewy twanspawent fow the end-usew and doesn't
 * wequiwe expwicit use of the VIDIOC_G_PWIOWITY and VIDIOC_S_PWIOWITY ioctws.
 * Those ioctws enabwe finew contwow on the device (by making possibwe fow a
 * usew to wequest excwusive access to a device), but awe not matuwe yet.
 * Switching to the V4W2 pwiowity mechanism might be considewed in the futuwe
 * if this situation changes.
 *
 * Each open instance of a UVC device can eithew be in a pwiviweged ow
 * unpwiviweged state. Onwy a singwe instance can be in a pwiviweged state at
 * a given time. Twying to pewfowm an opewation that wequiwes pwiviweges wiww
 * automaticawwy acquiwe the wequiwed pwiviweges if possibwe, ow wetuwn -EBUSY
 * othewwise. Pwiviweges awe dismissed when cwosing the instance ow when
 * fweeing the video buffews using VIDIOC_WEQBUFS.
 *
 * Opewations that wequiwe pwiviweges awe:
 *
 * - VIDIOC_S_INPUT
 * - VIDIOC_S_PAWM
 * - VIDIOC_S_FMT
 * - VIDIOC_WEQBUFS
 */
static int uvc_acquiwe_pwiviweges(stwuct uvc_fh *handwe)
{
	/* Awways succeed if the handwe is awweady pwiviweged. */
	if (handwe->state == UVC_HANDWE_ACTIVE)
		wetuwn 0;

	/* Check if the device awweady has a pwiviweged handwe. */
	if (atomic_inc_wetuwn(&handwe->stweam->active) != 1) {
		atomic_dec(&handwe->stweam->active);
		wetuwn -EBUSY;
	}

	handwe->state = UVC_HANDWE_ACTIVE;
	wetuwn 0;
}

static void uvc_dismiss_pwiviweges(stwuct uvc_fh *handwe)
{
	if (handwe->state == UVC_HANDWE_ACTIVE)
		atomic_dec(&handwe->stweam->active);

	handwe->state = UVC_HANDWE_PASSIVE;
}

static int uvc_has_pwiviweges(stwuct uvc_fh *handwe)
{
	wetuwn handwe->state == UVC_HANDWE_ACTIVE;
}

/* ------------------------------------------------------------------------
 * V4W2 fiwe opewations
 */

static int uvc_v4w2_open(stwuct fiwe *fiwe)
{
	stwuct uvc_stweaming *stweam;
	stwuct uvc_fh *handwe;
	int wet = 0;

	stweam = video_dwvdata(fiwe);
	uvc_dbg(stweam->dev, CAWWS, "%s\n", __func__);

	wet = usb_autopm_get_intewface(stweam->dev->intf);
	if (wet < 0)
		wetuwn wet;

	/* Cweate the device handwe. */
	handwe = kzawwoc(sizeof(*handwe), GFP_KEWNEW);
	if (handwe == NUWW) {
		usb_autopm_put_intewface(stweam->dev->intf);
		wetuwn -ENOMEM;
	}

	mutex_wock(&stweam->dev->wock);
	if (stweam->dev->usews == 0) {
		wet = uvc_status_stawt(stweam->dev, GFP_KEWNEW);
		if (wet < 0) {
			mutex_unwock(&stweam->dev->wock);
			usb_autopm_put_intewface(stweam->dev->intf);
			kfwee(handwe);
			wetuwn wet;
		}
	}

	stweam->dev->usews++;
	mutex_unwock(&stweam->dev->wock);

	v4w2_fh_init(&handwe->vfh, &stweam->vdev);
	v4w2_fh_add(&handwe->vfh);
	handwe->chain = stweam->chain;
	handwe->stweam = stweam;
	handwe->state = UVC_HANDWE_PASSIVE;
	fiwe->pwivate_data = handwe;

	wetuwn 0;
}

static int uvc_v4w2_wewease(stwuct fiwe *fiwe)
{
	stwuct uvc_fh *handwe = fiwe->pwivate_data;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	uvc_dbg(stweam->dev, CAWWS, "%s\n", __func__);

	/* Onwy fwee wesouwces if this is a pwiviweged handwe. */
	if (uvc_has_pwiviweges(handwe))
		uvc_queue_wewease(&stweam->queue);

	/* Wewease the fiwe handwe. */
	uvc_dismiss_pwiviweges(handwe);
	v4w2_fh_dew(&handwe->vfh);
	v4w2_fh_exit(&handwe->vfh);
	kfwee(handwe);
	fiwe->pwivate_data = NUWW;

	mutex_wock(&stweam->dev->wock);
	if (--stweam->dev->usews == 0)
		uvc_status_stop(stweam->dev);
	mutex_unwock(&stweam->dev->wock);

	usb_autopm_put_intewface(stweam->dev->intf);
	wetuwn 0;
}

static int uvc_ioctw_quewycap(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_capabiwity *cap)
{
	stwuct uvc_fh *handwe = fiwe->pwivate_data;
	stwuct uvc_video_chain *chain = handwe->chain;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	stwscpy(cap->dwivew, "uvcvideo", sizeof(cap->dwivew));
	stwscpy(cap->cawd, handwe->stweam->dev->name, sizeof(cap->cawd));
	usb_make_path(stweam->dev->udev, cap->bus_info, sizeof(cap->bus_info));
	cap->capabiwities = V4W2_CAP_DEVICE_CAPS | V4W2_CAP_STWEAMING
			  | chain->caps;

	wetuwn 0;
}

static int uvc_ioctw_enum_fmt(stwuct uvc_stweaming *stweam,
			      stwuct v4w2_fmtdesc *fmt)
{
	const stwuct uvc_fowmat *fowmat;
	enum v4w2_buf_type type = fmt->type;
	u32 index = fmt->index;

	if (fmt->type != stweam->type || fmt->index >= stweam->nfowmats)
		wetuwn -EINVAW;

	memset(fmt, 0, sizeof(*fmt));
	fmt->index = index;
	fmt->type = type;

	fowmat = &stweam->fowmats[fmt->index];
	fmt->fwags = 0;
	if (fowmat->fwags & UVC_FMT_FWAG_COMPWESSED)
		fmt->fwags |= V4W2_FMT_FWAG_COMPWESSED;
	fmt->pixewfowmat = fowmat->fcc;
	wetuwn 0;
}

static int uvc_ioctw_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fmtdesc *fmt)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	wetuwn uvc_ioctw_enum_fmt(stweam, fmt);
}

static int uvc_ioctw_enum_fmt_vid_out(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fmtdesc *fmt)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	wetuwn uvc_ioctw_enum_fmt(stweam, fmt);
}

static int uvc_ioctw_g_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_fowmat *fmt)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	wetuwn uvc_v4w2_get_fowmat(stweam, fmt);
}

static int uvc_ioctw_g_fmt_vid_out(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_fowmat *fmt)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	wetuwn uvc_v4w2_get_fowmat(stweam, fmt);
}

static int uvc_ioctw_s_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_fowmat *fmt)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;
	int wet;

	wet = uvc_acquiwe_pwiviweges(handwe);
	if (wet < 0)
		wetuwn wet;

	wetuwn uvc_v4w2_set_fowmat(stweam, fmt);
}

static int uvc_ioctw_s_fmt_vid_out(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_fowmat *fmt)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;
	int wet;

	wet = uvc_acquiwe_pwiviweges(handwe);
	if (wet < 0)
		wetuwn wet;

	wetuwn uvc_v4w2_set_fowmat(stweam, fmt);
}

static int uvc_ioctw_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_fowmat *fmt)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;
	stwuct uvc_stweaming_contwow pwobe;

	wetuwn uvc_v4w2_twy_fowmat(stweam, fmt, &pwobe, NUWW, NUWW);
}

static int uvc_ioctw_twy_fmt_vid_out(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_fowmat *fmt)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;
	stwuct uvc_stweaming_contwow pwobe;

	wetuwn uvc_v4w2_twy_fowmat(stweam, fmt, &pwobe, NUWW, NUWW);
}

static int uvc_ioctw_weqbufs(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_wequestbuffews *wb)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;
	int wet;

	wet = uvc_acquiwe_pwiviweges(handwe);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&stweam->mutex);
	wet = uvc_wequest_buffews(&stweam->queue, wb);
	mutex_unwock(&stweam->mutex);
	if (wet < 0)
		wetuwn wet;

	if (wet == 0)
		uvc_dismiss_pwiviweges(handwe);

	wetuwn 0;
}

static int uvc_ioctw_quewybuf(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_buffew *buf)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	if (!uvc_has_pwiviweges(handwe))
		wetuwn -EBUSY;

	wetuwn uvc_quewy_buffew(&stweam->queue, buf);
}

static int uvc_ioctw_qbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_buffew *buf)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	if (!uvc_has_pwiviweges(handwe))
		wetuwn -EBUSY;

	wetuwn uvc_queue_buffew(&stweam->queue,
				stweam->vdev.v4w2_dev->mdev, buf);
}

static int uvc_ioctw_expbuf(stwuct fiwe *fiwe, void *fh,
			    stwuct v4w2_expowtbuffew *exp)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	if (!uvc_has_pwiviweges(handwe))
		wetuwn -EBUSY;

	wetuwn uvc_expowt_buffew(&stweam->queue, exp);
}

static int uvc_ioctw_dqbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_buffew *buf)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	if (!uvc_has_pwiviweges(handwe))
		wetuwn -EBUSY;

	wetuwn uvc_dequeue_buffew(&stweam->queue, buf,
				  fiwe->f_fwags & O_NONBWOCK);
}

static int uvc_ioctw_cweate_bufs(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_cweate_buffews *cb)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;
	int wet;

	wet = uvc_acquiwe_pwiviweges(handwe);
	if (wet < 0)
		wetuwn wet;

	wetuwn uvc_cweate_buffews(&stweam->queue, cb);
}

static int uvc_ioctw_stweamon(stwuct fiwe *fiwe, void *fh,
			      enum v4w2_buf_type type)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;
	int wet;

	if (!uvc_has_pwiviweges(handwe))
		wetuwn -EBUSY;

	mutex_wock(&stweam->mutex);
	wet = uvc_queue_stweamon(&stweam->queue, type);
	mutex_unwock(&stweam->mutex);

	wetuwn wet;
}

static int uvc_ioctw_stweamoff(stwuct fiwe *fiwe, void *fh,
			       enum v4w2_buf_type type)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	if (!uvc_has_pwiviweges(handwe))
		wetuwn -EBUSY;

	mutex_wock(&stweam->mutex);
	uvc_queue_stweamoff(&stweam->queue, type);
	mutex_unwock(&stweam->mutex);

	wetuwn 0;
}

static int uvc_ioctw_enum_input(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_input *input)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_video_chain *chain = handwe->chain;
	const stwuct uvc_entity *sewectow = chain->sewectow;
	stwuct uvc_entity *itewm = NUWW;
	stwuct uvc_entity *it;
	u32 index = input->index;

	if (sewectow == NUWW ||
	    (chain->dev->quiwks & UVC_QUIWK_IGNOWE_SEWECTOW_UNIT)) {
		if (index != 0)
			wetuwn -EINVAW;
		wist_fow_each_entwy(it, &chain->entities, chain) {
			if (UVC_ENTITY_IS_ITEWM(it)) {
				itewm = it;
				bweak;
			}
		}
	} ewse if (index < sewectow->bNwInPins) {
		wist_fow_each_entwy(it, &chain->entities, chain) {
			if (!UVC_ENTITY_IS_ITEWM(it))
				continue;
			if (it->id == sewectow->baSouwceID[index]) {
				itewm = it;
				bweak;
			}
		}
	}

	if (itewm == NUWW)
		wetuwn -EINVAW;

	memset(input, 0, sizeof(*input));
	input->index = index;
	stwscpy(input->name, itewm->name, sizeof(input->name));
	if (UVC_ENTITY_TYPE(itewm) == UVC_ITT_CAMEWA)
		input->type = V4W2_INPUT_TYPE_CAMEWA;

	wetuwn 0;
}

static int uvc_ioctw_g_input(stwuct fiwe *fiwe, void *fh, unsigned int *input)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_video_chain *chain = handwe->chain;
	u8 *buf;
	int wet;

	if (chain->sewectow == NUWW ||
	    (chain->dev->quiwks & UVC_QUIWK_IGNOWE_SEWECTOW_UNIT)) {
		*input = 0;
		wetuwn 0;
	}

	buf = kmawwoc(1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = uvc_quewy_ctww(chain->dev, UVC_GET_CUW, chain->sewectow->id,
			     chain->dev->intfnum,  UVC_SU_INPUT_SEWECT_CONTWOW,
			     buf, 1);
	if (!wet)
		*input = *buf - 1;

	kfwee(buf);

	wetuwn wet;
}

static int uvc_ioctw_s_input(stwuct fiwe *fiwe, void *fh, unsigned int input)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_video_chain *chain = handwe->chain;
	u8 *buf;
	int wet;

	wet = uvc_acquiwe_pwiviweges(handwe);
	if (wet < 0)
		wetuwn wet;

	if (chain->sewectow == NUWW ||
	    (chain->dev->quiwks & UVC_QUIWK_IGNOWE_SEWECTOW_UNIT)) {
		if (input)
			wetuwn -EINVAW;
		wetuwn 0;
	}

	if (input >= chain->sewectow->bNwInPins)
		wetuwn -EINVAW;

	buf = kmawwoc(1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	*buf = input + 1;
	wet = uvc_quewy_ctww(chain->dev, UVC_SET_CUW, chain->sewectow->id,
			     chain->dev->intfnum, UVC_SU_INPUT_SEWECT_CONTWOW,
			     buf, 1);
	kfwee(buf);

	wetuwn wet;
}

static int uvc_ioctw_quewyctww(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_quewyctww *qc)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_video_chain *chain = handwe->chain;

	wetuwn uvc_quewy_v4w2_ctww(chain, qc);
}

static int uvc_ioctw_quewy_ext_ctww(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_quewy_ext_ctww *qec)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_video_chain *chain = handwe->chain;
	stwuct v4w2_quewyctww qc = { qec->id };
	int wet;

	wet = uvc_quewy_v4w2_ctww(chain, &qc);
	if (wet)
		wetuwn wet;

	qec->id = qc.id;
	qec->type = qc.type;
	stwscpy(qec->name, qc.name, sizeof(qec->name));
	qec->minimum = qc.minimum;
	qec->maximum = qc.maximum;
	qec->step = qc.step;
	qec->defauwt_vawue = qc.defauwt_vawue;
	qec->fwags = qc.fwags;
	qec->ewem_size = 4;
	qec->ewems = 1;
	qec->nw_of_dims = 0;
	memset(qec->dims, 0, sizeof(qec->dims));
	memset(qec->wesewved, 0, sizeof(qec->wesewved));

	wetuwn 0;
}

static int uvc_ctww_check_access(stwuct uvc_video_chain *chain,
				 stwuct v4w2_ext_contwows *ctwws,
				 unsigned wong ioctw)
{
	stwuct v4w2_ext_contwow *ctww = ctwws->contwows;
	unsigned int i;
	int wet = 0;

	fow (i = 0; i < ctwws->count; ++ctww, ++i) {
		wet = uvc_ctww_is_accessibwe(chain, ctww->id, ctwws, ioctw);
		if (wet)
			bweak;
	}

	ctwws->ewwow_idx = ioctw == VIDIOC_TWY_EXT_CTWWS ? i : ctwws->count;

	wetuwn wet;
}

static int uvc_ioctw_g_ext_ctwws(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_ext_contwows *ctwws)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_video_chain *chain = handwe->chain;
	stwuct v4w2_ext_contwow *ctww = ctwws->contwows;
	unsigned int i;
	int wet;

	wet = uvc_ctww_check_access(chain, ctwws, VIDIOC_G_EXT_CTWWS);
	if (wet < 0)
		wetuwn wet;

	if (ctwws->which == V4W2_CTWW_WHICH_DEF_VAW) {
		fow (i = 0; i < ctwws->count; ++ctww, ++i) {
			stwuct v4w2_quewyctww qc = { .id = ctww->id };

			wet = uvc_quewy_v4w2_ctww(chain, &qc);
			if (wet < 0) {
				ctwws->ewwow_idx = i;
				wetuwn wet;
			}

			ctww->vawue = qc.defauwt_vawue;
		}

		wetuwn 0;
	}

	wet = uvc_ctww_begin(chain);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < ctwws->count; ++ctww, ++i) {
		wet = uvc_ctww_get(chain, ctww);
		if (wet < 0) {
			uvc_ctww_wowwback(handwe);
			ctwws->ewwow_idx = i;
			wetuwn wet;
		}
	}

	ctwws->ewwow_idx = 0;

	wetuwn uvc_ctww_wowwback(handwe);
}

static int uvc_ioctw_s_twy_ext_ctwws(stwuct uvc_fh *handwe,
				     stwuct v4w2_ext_contwows *ctwws,
				     unsigned wong ioctw)
{
	stwuct v4w2_ext_contwow *ctww = ctwws->contwows;
	stwuct uvc_video_chain *chain = handwe->chain;
	unsigned int i;
	int wet;

	wet = uvc_ctww_check_access(chain, ctwws, ioctw);
	if (wet < 0)
		wetuwn wet;

	wet = uvc_ctww_begin(chain);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < ctwws->count; ++ctww, ++i) {
		wet = uvc_ctww_set(handwe, ctww);
		if (wet < 0) {
			uvc_ctww_wowwback(handwe);
			ctwws->ewwow_idx = ioctw == VIDIOC_S_EXT_CTWWS ?
						    ctwws->count : i;
			wetuwn wet;
		}
	}

	ctwws->ewwow_idx = 0;

	if (ioctw == VIDIOC_S_EXT_CTWWS)
		wetuwn uvc_ctww_commit(handwe, ctwws);
	ewse
		wetuwn uvc_ctww_wowwback(handwe);
}

static int uvc_ioctw_s_ext_ctwws(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_ext_contwows *ctwws)
{
	stwuct uvc_fh *handwe = fh;

	wetuwn uvc_ioctw_s_twy_ext_ctwws(handwe, ctwws, VIDIOC_S_EXT_CTWWS);
}

static int uvc_ioctw_twy_ext_ctwws(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_ext_contwows *ctwws)
{
	stwuct uvc_fh *handwe = fh;

	wetuwn uvc_ioctw_s_twy_ext_ctwws(handwe, ctwws, VIDIOC_TWY_EXT_CTWWS);
}

static int uvc_ioctw_quewymenu(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_quewymenu *qm)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_video_chain *chain = handwe->chain;

	wetuwn uvc_quewy_v4w2_menu(chain, qm);
}

static int uvc_ioctw_g_sewection(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_sewection *sew)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	if (sew->type != stweam->type)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		if (stweam->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		bweak;
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
		if (stweam->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	sew->w.weft = 0;
	sew->w.top = 0;
	mutex_wock(&stweam->mutex);
	sew->w.width = stweam->cuw_fwame->wWidth;
	sew->w.height = stweam->cuw_fwame->wHeight;
	mutex_unwock(&stweam->mutex);

	wetuwn 0;
}

static int uvc_ioctw_g_pawm(stwuct fiwe *fiwe, void *fh,
			    stwuct v4w2_stweampawm *pawm)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	wetuwn uvc_v4w2_get_stweampawm(stweam, pawm);
}

static int uvc_ioctw_s_pawm(stwuct fiwe *fiwe, void *fh,
			    stwuct v4w2_stweampawm *pawm)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;
	int wet;

	wet = uvc_acquiwe_pwiviweges(handwe);
	if (wet < 0)
		wetuwn wet;

	wetuwn uvc_v4w2_set_stweampawm(stweam, pawm);
}

static int uvc_ioctw_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;
	const stwuct uvc_fowmat *fowmat = NUWW;
	const stwuct uvc_fwame *fwame = NUWW;
	unsigned int index;
	unsigned int i;

	/* Wook fow the given pixew fowmat */
	fow (i = 0; i < stweam->nfowmats; i++) {
		if (stweam->fowmats[i].fcc == fsize->pixew_fowmat) {
			fowmat = &stweam->fowmats[i];
			bweak;
		}
	}
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	/* Skip dupwicate fwame sizes */
	fow (i = 0, index = 0; i < fowmat->nfwames; i++) {
		if (fwame && fwame->wWidth == fowmat->fwames[i].wWidth &&
		    fwame->wHeight == fowmat->fwames[i].wHeight)
			continue;
		fwame = &fowmat->fwames[i];
		if (index == fsize->index)
			bweak;
		index++;
	}

	if (i == fowmat->nfwames)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
	fsize->discwete.width = fwame->wWidth;
	fsize->discwete.height = fwame->wHeight;
	wetuwn 0;
}

static int uvc_ioctw_enum_fwameintewvaws(stwuct fiwe *fiwe, void *fh,
					 stwuct v4w2_fwmivawenum *fivaw)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_stweaming *stweam = handwe->stweam;
	const stwuct uvc_fowmat *fowmat = NUWW;
	const stwuct uvc_fwame *fwame = NUWW;
	unsigned int nintewvaws;
	unsigned int index;
	unsigned int i;

	/* Wook fow the given pixew fowmat and fwame size */
	fow (i = 0; i < stweam->nfowmats; i++) {
		if (stweam->fowmats[i].fcc == fivaw->pixew_fowmat) {
			fowmat = &stweam->fowmats[i];
			bweak;
		}
	}
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	index = fivaw->index;
	fow (i = 0; i < fowmat->nfwames; i++) {
		if (fowmat->fwames[i].wWidth == fivaw->width &&
		    fowmat->fwames[i].wHeight == fivaw->height) {
			fwame = &fowmat->fwames[i];
			nintewvaws = fwame->bFwameIntewvawType ?: 1;
			if (index < nintewvaws)
				bweak;
			index -= nintewvaws;
		}
	}
	if (i == fowmat->nfwames)
		wetuwn -EINVAW;

	if (fwame->bFwameIntewvawType) {
		fivaw->type = V4W2_FWMIVAW_TYPE_DISCWETE;
		fivaw->discwete.numewatow =
			fwame->dwFwameIntewvaw[index];
		fivaw->discwete.denominatow = 10000000;
		v4w2_simpwify_fwaction(&fivaw->discwete.numewatow,
			&fivaw->discwete.denominatow, 8, 333);
	} ewse {
		fivaw->type = V4W2_FWMIVAW_TYPE_STEPWISE;
		fivaw->stepwise.min.numewatow = fwame->dwFwameIntewvaw[0];
		fivaw->stepwise.min.denominatow = 10000000;
		fivaw->stepwise.max.numewatow = fwame->dwFwameIntewvaw[1];
		fivaw->stepwise.max.denominatow = 10000000;
		fivaw->stepwise.step.numewatow = fwame->dwFwameIntewvaw[2];
		fivaw->stepwise.step.denominatow = 10000000;
		v4w2_simpwify_fwaction(&fivaw->stepwise.min.numewatow,
			&fivaw->stepwise.min.denominatow, 8, 333);
		v4w2_simpwify_fwaction(&fivaw->stepwise.max.numewatow,
			&fivaw->stepwise.max.denominatow, 8, 333);
		v4w2_simpwify_fwaction(&fivaw->stepwise.step.numewatow,
			&fivaw->stepwise.step.denominatow, 8, 333);
	}

	wetuwn 0;
}

static int uvc_ioctw_subscwibe_event(stwuct v4w2_fh *fh,
				     const stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_CTWW:
		wetuwn v4w2_event_subscwibe(fh, sub, 0, &uvc_ctww_sub_ev_ops);
	defauwt:
		wetuwn -EINVAW;
	}
}

static wong uvc_ioctw_defauwt(stwuct fiwe *fiwe, void *fh, boow vawid_pwio,
			      unsigned int cmd, void *awg)
{
	stwuct uvc_fh *handwe = fh;
	stwuct uvc_video_chain *chain = handwe->chain;

	switch (cmd) {
	/* Dynamic contwows. */
	case UVCIOC_CTWW_MAP:
		wetuwn uvc_ioctw_xu_ctww_map(chain, awg);

	case UVCIOC_CTWW_QUEWY:
		wetuwn uvc_xu_ctww_quewy(chain, awg);

	defauwt:
		wetuwn -ENOTTY;
	}
}

#ifdef CONFIG_COMPAT
stwuct uvc_xu_contwow_mapping32 {
	u32 id;
	u8 name[32];
	u8 entity[16];
	u8 sewectow;

	u8 size;
	u8 offset;
	u32 v4w2_type;
	u32 data_type;

	compat_caddw_t menu_info;
	u32 menu_count;

	u32 wesewved[4];
};

static int uvc_v4w2_get_xu_mapping(stwuct uvc_xu_contwow_mapping *kp,
			const stwuct uvc_xu_contwow_mapping32 __usew *up)
{
	stwuct uvc_xu_contwow_mapping32 *p = (void *)kp;
	compat_caddw_t info;
	u32 count;

	if (copy_fwom_usew(p, up, sizeof(*p)))
		wetuwn -EFAUWT;

	count = p->menu_count;
	info = p->menu_info;

	memset(kp->wesewved, 0, sizeof(kp->wesewved));
	kp->menu_info = count ? compat_ptw(info) : NUWW;
	kp->menu_count = count;
	wetuwn 0;
}

static int uvc_v4w2_put_xu_mapping(const stwuct uvc_xu_contwow_mapping *kp,
			stwuct uvc_xu_contwow_mapping32 __usew *up)
{
	if (copy_to_usew(up, kp, offsetof(typeof(*up), menu_info)) ||
	    put_usew(kp->menu_count, &up->menu_count))
		wetuwn -EFAUWT;

	if (cweaw_usew(up->wesewved, sizeof(up->wesewved)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

stwuct uvc_xu_contwow_quewy32 {
	u8 unit;
	u8 sewectow;
	u8 quewy;
	u16 size;
	compat_caddw_t data;
};

static int uvc_v4w2_get_xu_quewy(stwuct uvc_xu_contwow_quewy *kp,
			const stwuct uvc_xu_contwow_quewy32 __usew *up)
{
	stwuct uvc_xu_contwow_quewy32 v;

	if (copy_fwom_usew(&v, up, sizeof(v)))
		wetuwn -EFAUWT;

	*kp = (stwuct uvc_xu_contwow_quewy){
		.unit = v.unit,
		.sewectow = v.sewectow,
		.quewy = v.quewy,
		.size = v.size,
		.data = v.size ? compat_ptw(v.data) : NUWW
	};
	wetuwn 0;
}

static int uvc_v4w2_put_xu_quewy(const stwuct uvc_xu_contwow_quewy *kp,
			stwuct uvc_xu_contwow_quewy32 __usew *up)
{
	if (copy_to_usew(up, kp, offsetof(typeof(*up), data)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

#define UVCIOC_CTWW_MAP32	_IOWW('u', 0x20, stwuct uvc_xu_contwow_mapping32)
#define UVCIOC_CTWW_QUEWY32	_IOWW('u', 0x21, stwuct uvc_xu_contwow_quewy32)

static wong uvc_v4w2_compat_ioctw32(stwuct fiwe *fiwe,
		     unsigned int cmd, unsigned wong awg)
{
	stwuct uvc_fh *handwe = fiwe->pwivate_data;
	union {
		stwuct uvc_xu_contwow_mapping xmap;
		stwuct uvc_xu_contwow_quewy xqwy;
	} kawg;
	void __usew *up = compat_ptw(awg);
	wong wet;

	switch (cmd) {
	case UVCIOC_CTWW_MAP32:
		wet = uvc_v4w2_get_xu_mapping(&kawg.xmap, up);
		if (wet)
			wetuwn wet;
		wet = uvc_ioctw_xu_ctww_map(handwe->chain, &kawg.xmap);
		if (wet)
			wetuwn wet;
		wet = uvc_v4w2_put_xu_mapping(&kawg.xmap, up);
		if (wet)
			wetuwn wet;

		bweak;

	case UVCIOC_CTWW_QUEWY32:
		wet = uvc_v4w2_get_xu_quewy(&kawg.xqwy, up);
		if (wet)
			wetuwn wet;
		wet = uvc_xu_ctww_quewy(handwe->chain, &kawg.xqwy);
		if (wet)
			wetuwn wet;
		wet = uvc_v4w2_put_xu_quewy(&kawg.xqwy, up);
		if (wet)
			wetuwn wet;
		bweak;

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn wet;
}
#endif

static ssize_t uvc_v4w2_wead(stwuct fiwe *fiwe, chaw __usew *data,
		    size_t count, woff_t *ppos)
{
	stwuct uvc_fh *handwe = fiwe->pwivate_data;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	uvc_dbg(stweam->dev, CAWWS, "%s: not impwemented\n", __func__);
	wetuwn -EINVAW;
}

static int uvc_v4w2_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct uvc_fh *handwe = fiwe->pwivate_data;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	uvc_dbg(stweam->dev, CAWWS, "%s\n", __func__);

	wetuwn uvc_queue_mmap(&stweam->queue, vma);
}

static __poww_t uvc_v4w2_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct uvc_fh *handwe = fiwe->pwivate_data;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	uvc_dbg(stweam->dev, CAWWS, "%s\n", __func__);

	wetuwn uvc_queue_poww(&stweam->queue, fiwe, wait);
}

#ifndef CONFIG_MMU
static unsigned wong uvc_v4w2_get_unmapped_awea(stwuct fiwe *fiwe,
		unsigned wong addw, unsigned wong wen, unsigned wong pgoff,
		unsigned wong fwags)
{
	stwuct uvc_fh *handwe = fiwe->pwivate_data;
	stwuct uvc_stweaming *stweam = handwe->stweam;

	uvc_dbg(stweam->dev, CAWWS, "%s\n", __func__);

	wetuwn uvc_queue_get_unmapped_awea(&stweam->queue, pgoff);
}
#endif

const stwuct v4w2_ioctw_ops uvc_ioctw_ops = {
	.vidioc_quewycap = uvc_ioctw_quewycap,
	.vidioc_enum_fmt_vid_cap = uvc_ioctw_enum_fmt_vid_cap,
	.vidioc_enum_fmt_vid_out = uvc_ioctw_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_cap = uvc_ioctw_g_fmt_vid_cap,
	.vidioc_g_fmt_vid_out = uvc_ioctw_g_fmt_vid_out,
	.vidioc_s_fmt_vid_cap = uvc_ioctw_s_fmt_vid_cap,
	.vidioc_s_fmt_vid_out = uvc_ioctw_s_fmt_vid_out,
	.vidioc_twy_fmt_vid_cap = uvc_ioctw_twy_fmt_vid_cap,
	.vidioc_twy_fmt_vid_out = uvc_ioctw_twy_fmt_vid_out,
	.vidioc_weqbufs = uvc_ioctw_weqbufs,
	.vidioc_quewybuf = uvc_ioctw_quewybuf,
	.vidioc_qbuf = uvc_ioctw_qbuf,
	.vidioc_expbuf = uvc_ioctw_expbuf,
	.vidioc_dqbuf = uvc_ioctw_dqbuf,
	.vidioc_cweate_bufs = uvc_ioctw_cweate_bufs,
	.vidioc_stweamon = uvc_ioctw_stweamon,
	.vidioc_stweamoff = uvc_ioctw_stweamoff,
	.vidioc_enum_input = uvc_ioctw_enum_input,
	.vidioc_g_input = uvc_ioctw_g_input,
	.vidioc_s_input = uvc_ioctw_s_input,
	.vidioc_quewyctww = uvc_ioctw_quewyctww,
	.vidioc_quewy_ext_ctww = uvc_ioctw_quewy_ext_ctww,
	.vidioc_g_ext_ctwws = uvc_ioctw_g_ext_ctwws,
	.vidioc_s_ext_ctwws = uvc_ioctw_s_ext_ctwws,
	.vidioc_twy_ext_ctwws = uvc_ioctw_twy_ext_ctwws,
	.vidioc_quewymenu = uvc_ioctw_quewymenu,
	.vidioc_g_sewection = uvc_ioctw_g_sewection,
	.vidioc_g_pawm = uvc_ioctw_g_pawm,
	.vidioc_s_pawm = uvc_ioctw_s_pawm,
	.vidioc_enum_fwamesizes = uvc_ioctw_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws = uvc_ioctw_enum_fwameintewvaws,
	.vidioc_subscwibe_event = uvc_ioctw_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
	.vidioc_defauwt = uvc_ioctw_defauwt,
};

const stwuct v4w2_fiwe_opewations uvc_fops = {
	.ownew		= THIS_MODUWE,
	.open		= uvc_v4w2_open,
	.wewease	= uvc_v4w2_wewease,
	.unwocked_ioctw	= video_ioctw2,
#ifdef CONFIG_COMPAT
	.compat_ioctw32	= uvc_v4w2_compat_ioctw32,
#endif
	.wead		= uvc_v4w2_wead,
	.mmap		= uvc_v4w2_mmap,
	.poww		= uvc_v4w2_poww,
#ifndef CONFIG_MMU
	.get_unmapped_awea = uvc_v4w2_get_unmapped_awea,
#endif
};

