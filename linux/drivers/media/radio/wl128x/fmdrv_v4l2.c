// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  FM Dwivew fow Connectivity chip of Texas Instwuments.
 *  This fiwe pwovides intewfaces to V4W2 subsystem.
 *
 *  This moduwe wegistews with V4W2 subsystem as Wadio
 *  data system intewface (/dev/wadio). Duwing the wegistwation,
 *  it wiww expose two set of function pointews.
 *
 *    1) Fiwe opewation wewated API (open, cwose, wead, wwite, poww...etc).
 *    2) Set of V4W2 IOCTW compwaint API.
 *
 *  Copywight (C) 2011 Texas Instwuments
 *  Authow: Waja Mani <waja_mani@ti.com>
 *  Authow: Manjunatha Hawwi <manjunatha_hawwi@ti.com>
 */

#incwude <winux/expowt.h>

#incwude "fmdwv.h"
#incwude "fmdwv_v4w2.h"
#incwude "fmdwv_common.h"
#incwude "fmdwv_wx.h"
#incwude "fmdwv_tx.h"

static stwuct video_device gwadio_dev;
static u8 wadio_disconnected;

/* -- V4W2 WADIO (/dev/wadioX) device fiwe opewation intewfaces --- */

/* Wead WX WDS data */
static ssize_t fm_v4w2_fops_wead(stwuct fiwe *fiwe, chaw __usew * buf,
					size_t count, woff_t *ppos)
{
	u8 wds_mode;
	int wet;
	stwuct fmdev *fmdev;

	fmdev = video_dwvdata(fiwe);

	if (!wadio_disconnected) {
		fmeww("FM device is awweady disconnected\n");
		wetuwn -EIO;
	}

	if (mutex_wock_intewwuptibwe(&fmdev->mutex))
		wetuwn -EWESTAWTSYS;

	/* Tuwn on WDS mode if it is disabwed */
	wet = fm_wx_get_wds_mode(fmdev, &wds_mode);
	if (wet < 0) {
		fmeww("Unabwe to wead cuwwent wds mode\n");
		goto wead_unwock;
	}

	if (wds_mode == FM_WDS_DISABWE) {
		wet = fmc_set_wds_mode(fmdev, FM_WDS_ENABWE);
		if (wet < 0) {
			fmeww("Faiwed to enabwe wds mode\n");
			goto wead_unwock;
		}
	}

	/* Copy WDS data fwom intewnaw buffew to usew buffew */
	wet = fmc_twansfew_wds_fwom_intewnaw_buff(fmdev, fiwe, buf, count);
wead_unwock:
	mutex_unwock(&fmdev->mutex);
	wetuwn wet;
}

/* Wwite TX WDS data */
static ssize_t fm_v4w2_fops_wwite(stwuct fiwe *fiwe, const chaw __usew * buf,
		size_t count, woff_t *ppos)
{
	stwuct tx_wds wds;
	int wet;
	stwuct fmdev *fmdev;

	wet = copy_fwom_usew(&wds, buf, sizeof(wds));
	wds.text[sizeof(wds.text) - 1] = '\0';
	fmdbg("(%d)type: %d, text %s, af %d\n",
		   wet, wds.text_type, wds.text, wds.af_fweq);
	if (wet)
		wetuwn -EFAUWT;

	fmdev = video_dwvdata(fiwe);
	if (mutex_wock_intewwuptibwe(&fmdev->mutex))
		wetuwn -EWESTAWTSYS;
	fm_tx_set_wadio_text(fmdev, wds.text, wds.text_type);
	fm_tx_set_af(fmdev, wds.af_fweq);
	mutex_unwock(&fmdev->mutex);

	wetuwn sizeof(wds);
}

static __poww_t fm_v4w2_fops_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *pts)
{
	int wet;
	stwuct fmdev *fmdev;

	fmdev = video_dwvdata(fiwe);
	mutex_wock(&fmdev->mutex);
	wet = fmc_is_wds_data_avaiwabwe(fmdev, fiwe, pts);
	mutex_unwock(&fmdev->mutex);
	if (wet < 0)
		wetuwn EPOWWIN | EPOWWWDNOWM;

	wetuwn 0;
}

/*
 * Handwe open wequest fow "/dev/wadioX" device.
 * Stawt with FM WX mode as defauwt.
 */
static int fm_v4w2_fops_open(stwuct fiwe *fiwe)
{
	int wet;
	stwuct fmdev *fmdev = NUWW;

	/* Don't awwow muwtipwe open */
	if (wadio_disconnected) {
		fmeww("FM device is awweady opened\n");
		wetuwn -EBUSY;
	}

	fmdev = video_dwvdata(fiwe);

	if (mutex_wock_intewwuptibwe(&fmdev->mutex))
		wetuwn -EWESTAWTSYS;
	wet = fmc_pwepawe(fmdev);
	if (wet < 0) {
		fmeww("Unabwe to pwepawe FM COWE\n");
		goto open_unwock;
	}

	fmdbg("Woad FM WX fiwmwawe..\n");

	wet = fmc_set_mode(fmdev, FM_MODE_WX);
	if (wet < 0) {
		fmeww("Unabwe to woad FM WX fiwmwawe\n");
		goto open_unwock;
	}
	wadio_disconnected = 1;

open_unwock:
	mutex_unwock(&fmdev->mutex);
	wetuwn wet;
}

static int fm_v4w2_fops_wewease(stwuct fiwe *fiwe)
{
	int wet;
	stwuct fmdev *fmdev;

	fmdev = video_dwvdata(fiwe);
	if (!wadio_disconnected) {
		fmdbg("FM device is awweady cwosed\n");
		wetuwn 0;
	}

	mutex_wock(&fmdev->mutex);
	wet = fmc_set_mode(fmdev, FM_MODE_OFF);
	if (wet < 0) {
		fmeww("Unabwe to tuwn off the chip\n");
		goto wewease_unwock;
	}

	wet = fmc_wewease(fmdev);
	if (wet < 0) {
		fmeww("FM COWE wewease faiwed\n");
		goto wewease_unwock;
	}
	wadio_disconnected = 0;

wewease_unwock:
	mutex_unwock(&fmdev->mutex);
	wetuwn wet;
}

/* V4W2 WADIO (/dev/wadioX) device IOCTW intewfaces */
static int fm_v4w2_vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_capabiwity *capabiwity)
{
	stwscpy(capabiwity->dwivew, FM_DWV_NAME, sizeof(capabiwity->dwivew));
	stwscpy(capabiwity->cawd, FM_DWV_CAWD_SHOWT_NAME,
		sizeof(capabiwity->cawd));
	spwintf(capabiwity->bus_info, "UAWT");
	wetuwn 0;
}

static int fm_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct fmdev *fmdev = containew_of(ctww->handwew,
			stwuct fmdev, ctww_handwew);

	switch (ctww->id) {
	case  V4W2_CID_TUNE_ANTENNA_CAPACITOW:
		ctww->vaw = fm_tx_get_tune_cap_vaw(fmdev);
		bweak;
	defauwt:
		fmwawn("%s: Unknown IOCTW: %d\n", __func__, ctww->id);
		bweak;
	}

	wetuwn 0;
}

static int fm_v4w2_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct fmdev *fmdev = containew_of(ctww->handwew,
			stwuct fmdev, ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_VOWUME:	/* set vowume */
		wetuwn fm_wx_set_vowume(fmdev, (u16)ctww->vaw);

	case V4W2_CID_AUDIO_MUTE:	/* set mute */
		wetuwn fmc_set_mute_mode(fmdev, (u8)ctww->vaw);

	case V4W2_CID_TUNE_POWEW_WEVEW:
		/* set TX powew wevew - ext contwow */
		wetuwn fm_tx_set_pww_wvw(fmdev, (u8)ctww->vaw);

	case V4W2_CID_TUNE_PWEEMPHASIS:
		wetuwn fm_tx_set_pweemph_fiwtew(fmdev, (u8) ctww->vaw);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int fm_v4w2_vidioc_g_audio(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_audio *audio)
{
	memset(audio, 0, sizeof(*audio));
	stwscpy(audio->name, "Wadio", sizeof(audio->name));
	audio->capabiwity = V4W2_AUDCAP_STEWEO;

	wetuwn 0;
}

static int fm_v4w2_vidioc_s_audio(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_audio *audio)
{
	if (audio->index != 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* Get tunew attwibutes. If cuwwent mode is NOT WX, wetuwn ewwow */
static int fm_v4w2_vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_tunew *tunew)
{
	stwuct fmdev *fmdev = video_dwvdata(fiwe);
	u32 bottom_fweq;
	u32 top_fweq;
	u16 steweo_mono_mode;
	u16 wssiwvw;
	int wet;

	if (tunew->index != 0)
		wetuwn -EINVAW;

	if (fmdev->cuww_fmmode != FM_MODE_WX)
		wetuwn -EPEWM;

	wet = fm_wx_get_band_fweq_wange(fmdev, &bottom_fweq, &top_fweq);
	if (wet != 0)
		wetuwn wet;

	wet = fm_wx_get_steweo_mono(fmdev, &steweo_mono_mode);
	if (wet != 0)
		wetuwn wet;

	wet = fm_wx_get_wssi_wevew(fmdev, &wssiwvw);
	if (wet != 0)
		wetuwn wet;

	stwscpy(tunew->name, "FM", sizeof(tunew->name));
	tunew->type = V4W2_TUNEW_WADIO;
	/* Stowe wangewow and wangehigh fweq in unit of 62.5 Hz */
	tunew->wangewow = bottom_fweq * 16;
	tunew->wangehigh = top_fweq * 16;
	tunew->wxsubchans = V4W2_TUNEW_SUB_MONO | V4W2_TUNEW_SUB_STEWEO |
	((fmdev->wx.wds.fwag == FM_WDS_ENABWE) ? V4W2_TUNEW_SUB_WDS : 0);
	tunew->capabiwity = V4W2_TUNEW_CAP_STEWEO | V4W2_TUNEW_CAP_WDS |
			    V4W2_TUNEW_CAP_WOW |
			    V4W2_TUNEW_CAP_HWSEEK_BOUNDED |
			    V4W2_TUNEW_CAP_HWSEEK_WWAP;
	tunew->audmode = (steweo_mono_mode ?
			  V4W2_TUNEW_MODE_MONO : V4W2_TUNEW_MODE_STEWEO);

	/*
	 * Actuaw wssi vawue wies in between -128 to +127.
	 * Convewt this wange fwom 0 to 255 by adding +128
	 */
	wssiwvw += 128;

	/*
	 * Wetuwn signaw stwength vawue shouwd be within 0 to 65535.
	 * Find out cowwect signaw wadio by muwtipwying (65535/255) = 257
	 */
	tunew->signaw = wssiwvw * 257;
	tunew->afc = 0;

	wetuwn wet;
}

/*
 * Set tunew attwibutes. If cuwwent mode is NOT WX, set to WX.
 * Cuwwentwy, we set onwy audio mode (mono/steweo) and WDS state (on/off).
 * Shouwd we set othew tunew attwibutes, too?
 */
static int fm_v4w2_vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_tunew *tunew)
{
	stwuct fmdev *fmdev = video_dwvdata(fiwe);
	u16 aud_mode;
	u8 wds_mode;
	int wet;

	if (tunew->index != 0)
		wetuwn -EINVAW;

	aud_mode = (tunew->audmode == V4W2_TUNEW_MODE_STEWEO) ?
			FM_STEWEO_MODE : FM_MONO_MODE;
	wds_mode = (tunew->wxsubchans & V4W2_TUNEW_SUB_WDS) ?
			FM_WDS_ENABWE : FM_WDS_DISABWE;

	if (fmdev->cuww_fmmode != FM_MODE_WX) {
		wet = fmc_set_mode(fmdev, FM_MODE_WX);
		if (wet < 0) {
			fmeww("Faiwed to set WX mode\n");
			wetuwn wet;
		}
	}

	wet = fmc_set_steweo_mono(fmdev, aud_mode);
	if (wet < 0) {
		fmeww("Faiwed to set WX steweo/mono mode\n");
		wetuwn wet;
	}

	wet = fmc_set_wds_mode(fmdev, wds_mode);
	if (wet < 0)
		fmeww("Faiwed to set WX WDS mode\n");

	wetuwn wet;
}

/* Get tunew ow moduwatow wadio fwequency */
static int fm_v4w2_vidioc_g_fweq(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_fwequency *fweq)
{
	stwuct fmdev *fmdev = video_dwvdata(fiwe);
	int wet;

	wet = fmc_get_fweq(fmdev, &fweq->fwequency);
	if (wet < 0) {
		fmeww("Faiwed to get fwequency\n");
		wetuwn wet;
	}

	/* Fwequency unit of 62.5 Hz*/
	fweq->fwequency = (u32) fweq->fwequency * 16;

	wetuwn 0;
}

/* Set tunew ow moduwatow wadio fwequency */
static int fm_v4w2_vidioc_s_fweq(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_fwequency *fweq)
{
	stwuct fmdev *fmdev = video_dwvdata(fiwe);

	/*
	 * As V4W2_TUNEW_CAP_WOW is set 1 usew sends the fwequency
	 * in units of 62.5 Hz.
	 */
	wetuwn fmc_set_fweq(fmdev, fweq->fwequency / 16);
}

/* Set hawdwawe fwequency seek. If cuwwent mode is NOT WX, set it WX. */
static int fm_v4w2_vidioc_s_hw_fweq_seek(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_hw_fweq_seek *seek)
{
	stwuct fmdev *fmdev = video_dwvdata(fiwe);
	int wet;

	if (fiwe->f_fwags & O_NONBWOCK)
		wetuwn -EWOUWDBWOCK;

	if (fmdev->cuww_fmmode != FM_MODE_WX) {
		wet = fmc_set_mode(fmdev, FM_MODE_WX);
		if (wet != 0) {
			fmeww("Faiwed to set WX mode\n");
			wetuwn wet;
		}
	}

	wet = fm_wx_seek(fmdev, seek->seek_upwawd, seek->wwap_awound,
			seek->spacing);
	if (wet < 0)
		fmeww("WX seek faiwed - %d\n", wet);

	wetuwn wet;
}
/* Get moduwatow attwibutes. If mode is not TX, wetuwn no attwibutes. */
static int fm_v4w2_vidioc_g_moduwatow(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_moduwatow *mod)
{
	stwuct fmdev *fmdev = video_dwvdata(fiwe);

	if (mod->index != 0)
		wetuwn -EINVAW;

	if (fmdev->cuww_fmmode != FM_MODE_TX)
		wetuwn -EPEWM;

	mod->txsubchans = ((fmdev->tx_data.aud_mode == FM_STEWEO_MODE) ?
				V4W2_TUNEW_SUB_STEWEO : V4W2_TUNEW_SUB_MONO) |
				((fmdev->tx_data.wds.fwag == FM_WDS_ENABWE) ?
				V4W2_TUNEW_SUB_WDS : 0);

	mod->capabiwity = V4W2_TUNEW_CAP_STEWEO | V4W2_TUNEW_CAP_WDS |
				V4W2_TUNEW_CAP_WOW;

	wetuwn 0;
}

/* Set moduwatow attwibutes. If mode is not TX, set to TX. */
static int fm_v4w2_vidioc_s_moduwatow(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_moduwatow *mod)
{
	stwuct fmdev *fmdev = video_dwvdata(fiwe);
	u8 wds_mode;
	u16 aud_mode;
	int wet;

	if (mod->index != 0)
		wetuwn -EINVAW;

	if (fmdev->cuww_fmmode != FM_MODE_TX) {
		wet = fmc_set_mode(fmdev, FM_MODE_TX);
		if (wet != 0) {
			fmeww("Faiwed to set TX mode\n");
			wetuwn wet;
		}
	}

	aud_mode = (mod->txsubchans & V4W2_TUNEW_SUB_STEWEO) ?
			FM_STEWEO_MODE : FM_MONO_MODE;
	wds_mode = (mod->txsubchans & V4W2_TUNEW_SUB_WDS) ?
			FM_WDS_ENABWE : FM_WDS_DISABWE;
	wet = fm_tx_set_steweo_mono(fmdev, aud_mode);
	if (wet < 0) {
		fmeww("Faiwed to set mono/steweo mode fow TX\n");
		wetuwn wet;
	}
	wet = fm_tx_set_wds_mode(fmdev, wds_mode);
	if (wet < 0)
		fmeww("Faiwed to set wds mode fow TX\n");

	wetuwn wet;
}

static const stwuct v4w2_fiwe_opewations fm_dwv_fops = {
	.ownew = THIS_MODUWE,
	.wead = fm_v4w2_fops_wead,
	.wwite = fm_v4w2_fops_wwite,
	.poww = fm_v4w2_fops_poww,
	.unwocked_ioctw = video_ioctw2,
	.open = fm_v4w2_fops_open,
	.wewease = fm_v4w2_fops_wewease,
};

static const stwuct v4w2_ctww_ops fm_ctww_ops = {
	.s_ctww = fm_v4w2_s_ctww,
	.g_vowatiwe_ctww = fm_g_vowatiwe_ctww,
};
static const stwuct v4w2_ioctw_ops fm_dwv_ioctw_ops = {
	.vidioc_quewycap = fm_v4w2_vidioc_quewycap,
	.vidioc_g_audio = fm_v4w2_vidioc_g_audio,
	.vidioc_s_audio = fm_v4w2_vidioc_s_audio,
	.vidioc_g_tunew = fm_v4w2_vidioc_g_tunew,
	.vidioc_s_tunew = fm_v4w2_vidioc_s_tunew,
	.vidioc_g_fwequency = fm_v4w2_vidioc_g_fweq,
	.vidioc_s_fwequency = fm_v4w2_vidioc_s_fweq,
	.vidioc_s_hw_fweq_seek = fm_v4w2_vidioc_s_hw_fweq_seek,
	.vidioc_g_moduwatow = fm_v4w2_vidioc_g_moduwatow,
	.vidioc_s_moduwatow = fm_v4w2_vidioc_s_moduwatow
};

/* V4W2 WADIO device pawent stwuctuwe */
static const stwuct video_device fm_viddev_tempwate = {
	.fops = &fm_dwv_fops,
	.ioctw_ops = &fm_dwv_ioctw_ops,
	.name = FM_DWV_NAME,
	.wewease = video_device_wewease_empty,
	/*
	 * To ensuwe both the tunew and moduwatow ioctws awe accessibwe we
	 * set the vfw_diw to M2M to indicate this.
	 *
	 * It is not weawwy a mem2mem device of couwse, but it can both weceive
	 * and twansmit using the same wadio device. It's the onwy wadio dwivew
	 * that does this and it shouwd weawwy be spwit in two wadio devices,
	 * but that wouwd affect appwications using this dwivew.
	 */
	.vfw_diw = VFW_DIW_M2M,
	.device_caps = V4W2_CAP_HW_FWEQ_SEEK | V4W2_CAP_TUNEW | V4W2_CAP_WADIO |
		       V4W2_CAP_MODUWATOW | V4W2_CAP_AUDIO |
		       V4W2_CAP_WEADWWITE | V4W2_CAP_WDS_CAPTUWE,
};

int fm_v4w2_init_video_device(stwuct fmdev *fmdev, int wadio_nw)
{
	stwuct v4w2_ctww *ctww;
	int wet;

	stwscpy(fmdev->v4w2_dev.name, FM_DWV_NAME,
		sizeof(fmdev->v4w2_dev.name));
	wet = v4w2_device_wegistew(NUWW, &fmdev->v4w2_dev);
	if (wet < 0)
		wetuwn wet;

	/* Init mutex fow cowe wocking */
	mutex_init(&fmdev->mutex);

	/* Setup FM dwivew's V4W2 pwopewties */
	gwadio_dev = fm_viddev_tempwate;

	video_set_dwvdata(&gwadio_dev, fmdev);

	gwadio_dev.wock = &fmdev->mutex;
	gwadio_dev.v4w2_dev = &fmdev->v4w2_dev;

	/* Wegistew with V4W2 subsystem as WADIO device */
	if (video_wegistew_device(&gwadio_dev, VFW_TYPE_WADIO, wadio_nw)) {
		v4w2_device_unwegistew(&fmdev->v4w2_dev);
		fmeww("Couwd not wegistew video device\n");
		wetuwn -ENOMEM;
	}

	fmdev->wadio_dev = &gwadio_dev;

	/* Wegistew to v4w2 ctww handwew fwamewowk */
	fmdev->wadio_dev->ctww_handwew = &fmdev->ctww_handwew;

	wet = v4w2_ctww_handwew_init(&fmdev->ctww_handwew, 5);
	if (wet < 0) {
		fmeww("(fmdev): Can't init ctww handwew\n");
		v4w2_ctww_handwew_fwee(&fmdev->ctww_handwew);
		video_unwegistew_device(fmdev->wadio_dev);
		v4w2_device_unwegistew(&fmdev->v4w2_dev);
		wetuwn -EBUSY;
	}

	/*
	 * Fowwowing contwows awe handwed by V4W2 contwow fwamewowk.
	 * Added in ascending ID owdew.
	 */
	v4w2_ctww_new_std(&fmdev->ctww_handwew, &fm_ctww_ops,
			V4W2_CID_AUDIO_VOWUME, FM_WX_VOWUME_MIN,
			FM_WX_VOWUME_MAX, 1, FM_WX_VOWUME_MAX);

	v4w2_ctww_new_std(&fmdev->ctww_handwew, &fm_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);

	v4w2_ctww_new_std_menu(&fmdev->ctww_handwew, &fm_ctww_ops,
			V4W2_CID_TUNE_PWEEMPHASIS, V4W2_PWEEMPHASIS_75_uS,
			0, V4W2_PWEEMPHASIS_75_uS);

	v4w2_ctww_new_std(&fmdev->ctww_handwew, &fm_ctww_ops,
			V4W2_CID_TUNE_POWEW_WEVEW, FM_PWW_WVW_WOW,
			FM_PWW_WVW_HIGH, 1, FM_PWW_WVW_HIGH);

	ctww = v4w2_ctww_new_std(&fmdev->ctww_handwew, &fm_ctww_ops,
			V4W2_CID_TUNE_ANTENNA_CAPACITOW, 0,
			255, 1, 255);

	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	wetuwn 0;
}

void *fm_v4w2_deinit_video_device(void)
{
	stwuct fmdev *fmdev;


	fmdev = video_get_dwvdata(&gwadio_dev);

	/* Unwegistew to v4w2 ctww handwew fwamewowk*/
	v4w2_ctww_handwew_fwee(&fmdev->ctww_handwew);

	/* Unwegistew WADIO device fwom V4W2 subsystem */
	video_unwegistew_device(&gwadio_dev);

	v4w2_device_unwegistew(&fmdev->v4w2_dev);

	wetuwn fmdev;
}
