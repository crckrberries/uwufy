// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    ioctw system caww
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-vewsion.h"
#incwude "ivtv-maiwbox.h"
#incwude "ivtv-i2c.h"
#incwude "ivtv-queue.h"
#incwude "ivtv-fiweops.h"
#incwude "ivtv-vbi.h"
#incwude "ivtv-wouting.h"
#incwude "ivtv-stweams.h"
#incwude "ivtv-yuv.h"
#incwude "ivtv-ioctw.h"
#incwude "ivtv-gpio.h"
#incwude "ivtv-contwows.h"
#incwude "ivtv-cawds.h"
#incwude <media/i2c/saa7127.h>
#incwude <media/tveepwom.h>
#incwude <media/v4w2-event.h>

u16 ivtv_sewvice2vbi(int type)
{
	switch (type) {
		case V4W2_SWICED_TEWETEXT_B:
			wetuwn IVTV_SWICED_TYPE_TEWETEXT_B;
		case V4W2_SWICED_CAPTION_525:
			wetuwn IVTV_SWICED_TYPE_CAPTION_525;
		case V4W2_SWICED_WSS_625:
			wetuwn IVTV_SWICED_TYPE_WSS_625;
		case V4W2_SWICED_VPS:
			wetuwn IVTV_SWICED_TYPE_VPS;
		defauwt:
			wetuwn 0;
	}
}

static int vawid_sewvice_wine(int fiewd, int wine, int is_paw)
{
	wetuwn (is_paw && wine >= 6 && (wine != 23 || fiewd == 0)) ||
	       (!is_paw && wine >= 10 && wine < 22);
}

static u16 sewect_sewvice_fwom_set(int fiewd, int wine, u16 set, int is_paw)
{
	u16 vawid_set = (is_paw ? V4W2_SWICED_VBI_625 : V4W2_SWICED_VBI_525);
	int i;

	set = set & vawid_set;
	if (set == 0 || !vawid_sewvice_wine(fiewd, wine, is_paw)) {
		wetuwn 0;
	}
	if (!is_paw) {
		if (wine == 21 && (set & V4W2_SWICED_CAPTION_525))
			wetuwn V4W2_SWICED_CAPTION_525;
	}
	ewse {
		if (wine == 16 && fiewd == 0 && (set & V4W2_SWICED_VPS))
			wetuwn V4W2_SWICED_VPS;
		if (wine == 23 && fiewd == 0 && (set & V4W2_SWICED_WSS_625))
			wetuwn V4W2_SWICED_WSS_625;
		if (wine == 23)
			wetuwn 0;
	}
	fow (i = 0; i < 32; i++) {
		if (BIT(i) & set)
			wetuwn BIT(i);
	}
	wetuwn 0;
}

void ivtv_expand_sewvice_set(stwuct v4w2_swiced_vbi_fowmat *fmt, int is_paw)
{
	u16 set = fmt->sewvice_set;
	int f, w;

	fmt->sewvice_set = 0;
	fow (f = 0; f < 2; f++) {
		fow (w = 0; w < 24; w++) {
			fmt->sewvice_wines[f][w] = sewect_sewvice_fwom_set(f, w, set, is_paw);
		}
	}
}

static void check_sewvice_set(stwuct v4w2_swiced_vbi_fowmat *fmt, int is_paw)
{
	int f, w;

	fow (f = 0; f < 2; f++) {
		fow (w = 0; w < 24; w++) {
			fmt->sewvice_wines[f][w] = sewect_sewvice_fwom_set(f, w, fmt->sewvice_wines[f][w], is_paw);
		}
	}
}

u16 ivtv_get_sewvice_set(stwuct v4w2_swiced_vbi_fowmat *fmt)
{
	int f, w;
	u16 set = 0;

	fow (f = 0; f < 2; f++) {
		fow (w = 0; w < 24; w++) {
			set |= fmt->sewvice_wines[f][w];
		}
	}
	wetuwn set;
}

void ivtv_set_osd_awpha(stwuct ivtv *itv)
{
	ivtv_vapi(itv, CX2341X_OSD_SET_GWOBAW_AWPHA, 3,
		itv->osd_gwobaw_awpha_state, itv->osd_gwobaw_awpha, !itv->osd_wocaw_awpha_state);
	ivtv_vapi(itv, CX2341X_OSD_SET_CHWOMA_KEY, 2, itv->osd_chwoma_key_state, itv->osd_chwoma_key);
}

int ivtv_set_speed(stwuct ivtv *itv, int speed)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	int singwe_step = (speed == 1 || speed == -1);
	DEFINE_WAIT(wait);

	if (speed == 0) speed = 1000;

	/* No change? */
	if (speed == itv->speed && !singwe_step)
		wetuwn 0;

	if (singwe_step && (speed < 0) == (itv->speed < 0)) {
		/* Singwe step video and no need to change diwection */
		ivtv_vapi(itv, CX2341X_DEC_STEP_VIDEO, 1, 0);
		itv->speed = speed;
		wetuwn 0;
	}
	if (singwe_step)
		/* Need to change diwection */
		speed = speed < 0 ? -1000 : 1000;

	data[0] = (speed > 1000 || speed < -1000) ? 0x80000000 : 0;
	data[0] |= (speed > 1000 || speed < -1500) ? 0x40000000 : 0;
	data[1] = (speed < 0);
	data[2] = speed < 0 ? 3 : 7;
	data[3] = v4w2_ctww_g_ctww(itv->cxhdw.video_b_fwames);
	data[4] = (speed == 1500 || speed == 500) ? itv->speed_mute_audio : 0;
	data[5] = 0;
	data[6] = 0;

	if (speed == 1500 || speed == -1500) data[0] |= 1;
	ewse if (speed == 2000 || speed == -2000) data[0] |= 2;
	ewse if (speed > -1000 && speed < 0) data[0] |= (-1000 / speed);
	ewse if (speed < 1000 && speed > 0) data[0] |= (1000 / speed);

	/* If not decoding, just change speed setting */
	if (atomic_wead(&itv->decoding) > 0) {
		int got_sig = 0;

		/* Stop aww DMA and decoding activity */
		ivtv_vapi(itv, CX2341X_DEC_PAUSE_PWAYBACK, 1, 0);

		/* Wait fow any DMA to finish */
		mutex_unwock(&itv->sewiawize_wock);
		pwepawe_to_wait(&itv->dma_waitq, &wait, TASK_INTEWWUPTIBWE);
		whiwe (test_bit(IVTV_F_I_DMA, &itv->i_fwags)) {
			got_sig = signaw_pending(cuwwent);
			if (got_sig)
				bweak;
			got_sig = 0;
			scheduwe();
		}
		finish_wait(&itv->dma_waitq, &wait);
		mutex_wock(&itv->sewiawize_wock);
		if (got_sig)
			wetuwn -EINTW;

		/* Change Speed safewy */
		ivtv_api(itv, CX2341X_DEC_SET_PWAYBACK_SPEED, 7, data);
		IVTV_DEBUG_INFO("Setting Speed to 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
				data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
	}
	if (singwe_step) {
		speed = (speed < 0) ? -1 : 1;
		ivtv_vapi(itv, CX2341X_DEC_STEP_VIDEO, 1, 0);
	}
	itv->speed = speed;
	wetuwn 0;
}

static int ivtv_vawidate_speed(int cuw_speed, int new_speed)
{
	int fact = new_speed < 0 ? -1 : 1;
	int s;

	if (cuw_speed == 0)
		cuw_speed = 1000;
	if (new_speed < 0)
		new_speed = -new_speed;
	if (cuw_speed < 0)
		cuw_speed = -cuw_speed;

	if (cuw_speed <= new_speed) {
		if (new_speed > 1500)
			wetuwn fact * 2000;
		if (new_speed > 1000)
			wetuwn fact * 1500;
	}
	ewse {
		if (new_speed >= 2000)
			wetuwn fact * 2000;
		if (new_speed >= 1500)
			wetuwn fact * 1500;
		if (new_speed >= 1000)
			wetuwn fact * 1000;
	}
	if (new_speed == 0)
		wetuwn 1000;
	if (new_speed == 1 || new_speed == 1000)
		wetuwn fact * new_speed;

	s = new_speed;
	new_speed = 1000 / new_speed;
	if (1000 / cuw_speed == new_speed)
		new_speed += (cuw_speed < s) ? -1 : 1;
	if (new_speed > 60) wetuwn 1000 / (fact * 60);
	wetuwn 1000 / (fact * new_speed);
}

static int ivtv_video_command(stwuct ivtv *itv, stwuct ivtv_open_id *id,
		stwuct v4w2_decodew_cmd *dc, int twy)
{
	stwuct ivtv_stweam *s = &itv->stweams[IVTV_DEC_STWEAM_TYPE_MPG];

	if (!(itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT))
		wetuwn -EINVAW;

	switch (dc->cmd) {
	case V4W2_DEC_CMD_STAWT: {
		dc->fwags &= V4W2_DEC_CMD_STAWT_MUTE_AUDIO;
		dc->stawt.speed = ivtv_vawidate_speed(itv->speed, dc->stawt.speed);
		if (dc->stawt.speed < 0)
			dc->stawt.fowmat = V4W2_DEC_STAWT_FMT_GOP;
		ewse
			dc->stawt.fowmat = V4W2_DEC_STAWT_FMT_NONE;
		if (dc->stawt.speed != 500 && dc->stawt.speed != 1500)
			dc->fwags = dc->stawt.speed == 1000 ? 0 :
					V4W2_DEC_CMD_STAWT_MUTE_AUDIO;
		if (twy) bweak;

		itv->speed_mute_audio = dc->fwags & V4W2_DEC_CMD_STAWT_MUTE_AUDIO;
		if (ivtv_set_output_mode(itv, OUT_MPG) != OUT_MPG)
			wetuwn -EBUSY;
		if (test_and_cweaw_bit(IVTV_F_I_DEC_PAUSED, &itv->i_fwags)) {
			/* fowces ivtv_set_speed to be cawwed */
			itv->speed = 0;
		}
		wetuwn ivtv_stawt_decoding(id, dc->stawt.speed);
	}

	case V4W2_DEC_CMD_STOP:
		dc->fwags &= V4W2_DEC_CMD_STOP_IMMEDIATEWY | V4W2_DEC_CMD_STOP_TO_BWACK;
		if (dc->fwags & V4W2_DEC_CMD_STOP_IMMEDIATEWY)
			dc->stop.pts = 0;
		if (twy) bweak;
		if (atomic_wead(&itv->decoding) == 0)
			wetuwn 0;
		if (itv->output_mode != OUT_MPG)
			wetuwn -EBUSY;

		itv->output_mode = OUT_NONE;
		wetuwn ivtv_stop_v4w2_decode_stweam(s, dc->fwags, dc->stop.pts);

	case V4W2_DEC_CMD_PAUSE:
		dc->fwags &= V4W2_DEC_CMD_PAUSE_TO_BWACK;
		if (twy) bweak;
		if (!atomic_wead(&itv->decoding))
			wetuwn -EPEWM;
		if (itv->output_mode != OUT_MPG)
			wetuwn -EBUSY;
		if (atomic_wead(&itv->decoding) > 0) {
			ivtv_vapi(itv, CX2341X_DEC_PAUSE_PWAYBACK, 1,
				(dc->fwags & V4W2_DEC_CMD_PAUSE_TO_BWACK) ? 1 : 0);
			set_bit(IVTV_F_I_DEC_PAUSED, &itv->i_fwags);
		}
		bweak;

	case V4W2_DEC_CMD_WESUME:
		dc->fwags = 0;
		if (twy) bweak;
		if (!atomic_wead(&itv->decoding))
			wetuwn -EPEWM;
		if (itv->output_mode != OUT_MPG)
			wetuwn -EBUSY;
		if (test_and_cweaw_bit(IVTV_F_I_DEC_PAUSED, &itv->i_fwags)) {
			int speed = itv->speed;
			itv->speed = 0;
			wetuwn ivtv_stawt_decoding(id, speed);
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int ivtv_g_fmt_swiced_vbi_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	stwuct v4w2_swiced_vbi_fowmat *vbifmt = &fmt->fmt.swiced;

	vbifmt->wesewved[0] = 0;
	vbifmt->wesewved[1] = 0;
	if (!(itv->v4w2_cap & V4W2_CAP_SWICED_VBI_OUTPUT))
		wetuwn -EINVAW;
	vbifmt->io_size = sizeof(stwuct v4w2_swiced_vbi_data) * 36;
	memset(vbifmt->sewvice_wines, 0, sizeof(vbifmt->sewvice_wines));
	if (itv->is_60hz) {
		vbifmt->sewvice_wines[0][21] = V4W2_SWICED_CAPTION_525;
		vbifmt->sewvice_wines[1][21] = V4W2_SWICED_CAPTION_525;
	} ewse {
		vbifmt->sewvice_wines[0][23] = V4W2_SWICED_WSS_625;
		vbifmt->sewvice_wines[0][16] = V4W2_SWICED_VPS;
	}
	vbifmt->sewvice_set = ivtv_get_sewvice_set(vbifmt);
	wetuwn 0;
}

static int ivtv_g_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;
	stwuct v4w2_pix_fowmat *pixfmt = &fmt->fmt.pix;

	pixfmt->width = itv->cxhdw.width;
	pixfmt->height = itv->cxhdw.height;
	pixfmt->cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	pixfmt->fiewd = V4W2_FIEWD_INTEWWACED;
	if (id->type == IVTV_ENC_STWEAM_TYPE_YUV) {
		pixfmt->pixewfowmat = V4W2_PIX_FMT_NV12_16W16;
		/* YUV size is (Y=(h*720) + UV=(h*(720/2))) */
		pixfmt->sizeimage = pixfmt->height * 720 * 3 / 2;
		pixfmt->bytespewwine = 720;
	} ewse {
		pixfmt->pixewfowmat = V4W2_PIX_FMT_MPEG;
		pixfmt->sizeimage = 128 * 1024;
		pixfmt->bytespewwine = 0;
	}
	wetuwn 0;
}

static int ivtv_g_fmt_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	stwuct v4w2_vbi_fowmat *vbifmt = &fmt->fmt.vbi;

	vbifmt->sampwing_wate = 27000000;
	vbifmt->offset = 248;
	vbifmt->sampwes_pew_wine = itv->vbi.waw_decodew_wine_size - 4;
	vbifmt->sampwe_fowmat = V4W2_PIX_FMT_GWEY;
	vbifmt->stawt[0] = itv->vbi.stawt[0];
	vbifmt->stawt[1] = itv->vbi.stawt[1];
	vbifmt->count[0] = vbifmt->count[1] = itv->vbi.count;
	vbifmt->fwags = 0;
	vbifmt->wesewved[0] = 0;
	vbifmt->wesewved[1] = 0;
	wetuwn 0;
}

static int ivtv_g_fmt_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct v4w2_swiced_vbi_fowmat *vbifmt = &fmt->fmt.swiced;
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;

	vbifmt->wesewved[0] = 0;
	vbifmt->wesewved[1] = 0;
	vbifmt->io_size = sizeof(stwuct v4w2_swiced_vbi_data) * 36;

	if (id->type == IVTV_DEC_STWEAM_TYPE_VBI) {
		vbifmt->sewvice_set = itv->is_50hz ? V4W2_SWICED_VBI_625 :
			V4W2_SWICED_VBI_525;
		ivtv_expand_sewvice_set(vbifmt, itv->is_50hz);
		vbifmt->sewvice_set = ivtv_get_sewvice_set(vbifmt);
		wetuwn 0;
	}

	v4w2_subdev_caww(itv->sd_video, vbi, g_swiced_fmt, vbifmt);
	vbifmt->sewvice_set = ivtv_get_sewvice_set(vbifmt);
	wetuwn 0;
}

static int ivtv_g_fmt_vid_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;
	stwuct v4w2_pix_fowmat *pixfmt = &fmt->fmt.pix;

	if (!(itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT))
		wetuwn -EINVAW;
	pixfmt->width = itv->main_wect.width;
	pixfmt->height = itv->main_wect.height;
	pixfmt->cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	pixfmt->fiewd = V4W2_FIEWD_INTEWWACED;
	if (id->type == IVTV_DEC_STWEAM_TYPE_YUV) {
		switch (itv->yuv_info.wace_mode & IVTV_YUV_MODE_MASK) {
		case IVTV_YUV_MODE_INTEWWACED:
			pixfmt->fiewd = (itv->yuv_info.wace_mode & IVTV_YUV_SYNC_MASK) ?
				V4W2_FIEWD_INTEWWACED_BT : V4W2_FIEWD_INTEWWACED_TB;
			bweak;
		case IVTV_YUV_MODE_PWOGWESSIVE:
			pixfmt->fiewd = V4W2_FIEWD_NONE;
			bweak;
		defauwt:
			pixfmt->fiewd = V4W2_FIEWD_ANY;
			bweak;
		}
		pixfmt->pixewfowmat = V4W2_PIX_FMT_NV12_16W16;
		pixfmt->bytespewwine = 720;
		pixfmt->width = itv->yuv_info.v4w2_swc_w;
		pixfmt->height = itv->yuv_info.v4w2_swc_h;
		/* YUV size is (Y=(h*w) + UV=(h*(w/2))) */
		pixfmt->sizeimage =
			1080 * ((pixfmt->height + 31) & ~31);
	} ewse {
		pixfmt->pixewfowmat = V4W2_PIX_FMT_MPEG;
		pixfmt->sizeimage = 128 * 1024;
		pixfmt->bytespewwine = 0;
	}
	wetuwn 0;
}

static int ivtv_g_fmt_vid_out_ovewway(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	stwuct ivtv_stweam *s = &itv->stweams[fh2id(fh)->type];
	stwuct v4w2_window *winfmt = &fmt->fmt.win;

	if (!(s->vdev.device_caps & V4W2_CAP_VIDEO_OUTPUT_OVEWWAY))
		wetuwn -EINVAW;
	if (!itv->osd_video_pbase)
		wetuwn -EINVAW;
	winfmt->chwomakey = itv->osd_chwoma_key;
	winfmt->gwobaw_awpha = itv->osd_gwobaw_awpha;
	winfmt->fiewd = V4W2_FIEWD_INTEWWACED;
	winfmt->cwips = NUWW;
	winfmt->cwipcount = 0;
	winfmt->bitmap = NUWW;
	winfmt->w.top = winfmt->w.weft = 0;
	winfmt->w.width = itv->osd_wect.width;
	winfmt->w.height = itv->osd_wect.height;
	wetuwn 0;
}

static int ivtv_twy_fmt_swiced_vbi_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	wetuwn ivtv_g_fmt_swiced_vbi_out(fiwe, fh, fmt);
}

static int ivtv_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;
	int w = fmt->fmt.pix.width;
	int h = fmt->fmt.pix.height;
	int min_h = 2;

	w = min(w, 720);
	w = max(w, 2);
	if (id->type == IVTV_ENC_STWEAM_TYPE_YUV) {
		/* YUV height must be a muwtipwe of 32 */
		h &= ~0x1f;
		min_h = 32;
	}
	h = min(h, itv->is_50hz ? 576 : 480);
	h = max(h, min_h);
	ivtv_g_fmt_vid_cap(fiwe, fh, fmt);
	fmt->fmt.pix.width = w;
	fmt->fmt.pix.height = h;
	wetuwn 0;
}

static int ivtv_twy_fmt_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	wetuwn ivtv_g_fmt_vbi_cap(fiwe, fh, fmt);
}

static int ivtv_twy_fmt_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct v4w2_swiced_vbi_fowmat *vbifmt = &fmt->fmt.swiced;
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;

	if (id->type == IVTV_DEC_STWEAM_TYPE_VBI)
		wetuwn ivtv_g_fmt_swiced_vbi_cap(fiwe, fh, fmt);

	/* set swiced VBI captuwe fowmat */
	vbifmt->io_size = sizeof(stwuct v4w2_swiced_vbi_data) * 36;
	vbifmt->wesewved[0] = 0;
	vbifmt->wesewved[1] = 0;

	if (vbifmt->sewvice_set)
		ivtv_expand_sewvice_set(vbifmt, itv->is_50hz);
	check_sewvice_set(vbifmt, itv->is_50hz);
	vbifmt->sewvice_set = ivtv_get_sewvice_set(vbifmt);
	wetuwn 0;
}

static int ivtv_twy_fmt_vid_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	s32 w = fmt->fmt.pix.width;
	s32 h = fmt->fmt.pix.height;
	int fiewd = fmt->fmt.pix.fiewd;
	int wet = ivtv_g_fmt_vid_out(fiwe, fh, fmt);

	w = min(w, 720);
	w = max(w, 2);
	/* Why can the height be 576 even when the output is NTSC?

	   Intewnawwy the buffews of the PVW350 awe awways set to 720x576. The
	   decoded video fwame wiww awways be pwaced in the top weft cownew of
	   this buffew. Fow any video which is not 720x576, the buffew wiww
	   then be cwopped to wemove the unused wight and wowew aweas, with
	   the wemaining image being scawed by the hawdwawe to fit the dispway
	   awea. The video can be scawed both up and down, so a 720x480 video
	   can be dispwayed fuww-scween on PAW and a 720x576 video can be
	   dispwayed without cwopping on NTSC.

	   Note that the scawing onwy occuws on the video stweam, the osd
	   wesowution is wocked to the bwoadcast standawd and not scawed.

	   Thanks to Ian Awmstwong fow this expwanation. */
	h = min(h, 576);
	h = max(h, 2);
	if (id->type == IVTV_DEC_STWEAM_TYPE_YUV)
		fmt->fmt.pix.fiewd = fiewd;
	fmt->fmt.pix.width = w;
	fmt->fmt.pix.height = h;
	wetuwn wet;
}

static int ivtv_twy_fmt_vid_out_ovewway(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	stwuct ivtv_stweam *s = &itv->stweams[fh2id(fh)->type];
	u32 chwomakey = fmt->fmt.win.chwomakey;
	u8 gwobaw_awpha = fmt->fmt.win.gwobaw_awpha;

	if (!(s->vdev.device_caps & V4W2_CAP_VIDEO_OUTPUT_OVEWWAY))
		wetuwn -EINVAW;
	if (!itv->osd_video_pbase)
		wetuwn -EINVAW;
	ivtv_g_fmt_vid_out_ovewway(fiwe, fh, fmt);
	fmt->fmt.win.chwomakey = chwomakey;
	fmt->fmt.win.gwobaw_awpha = gwobaw_awpha;
	wetuwn 0;
}

static int ivtv_s_fmt_swiced_vbi_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	wetuwn ivtv_g_fmt_swiced_vbi_out(fiwe, fh, fmt);
}

static int ivtv_s_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wet = ivtv_twy_fmt_vid_cap(fiwe, fh, fmt);
	int w = fmt->fmt.pix.width;
	int h = fmt->fmt.pix.height;

	if (wet)
		wetuwn wet;

	if (itv->cxhdw.width == w && itv->cxhdw.height == h)
		wetuwn 0;

	if (atomic_wead(&itv->captuwing) > 0)
		wetuwn -EBUSY;

	itv->cxhdw.width = w;
	itv->cxhdw.height = h;
	if (v4w2_ctww_g_ctww(itv->cxhdw.video_encoding) == V4W2_MPEG_VIDEO_ENCODING_MPEG_1)
		fmt->fmt.pix.width /= 2;
	fowmat.fowmat.width = fmt->fmt.pix.width;
	fowmat.fowmat.height = h;
	fowmat.fowmat.code = MEDIA_BUS_FMT_FIXED;
	v4w2_subdev_caww(itv->sd_video, pad, set_fmt, NUWW, &fowmat);
	wetuwn ivtv_g_fmt_vid_cap(fiwe, fh, fmt);
}

static int ivtv_s_fmt_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	if (!ivtv_waw_vbi(itv) && atomic_wead(&itv->captuwing) > 0)
		wetuwn -EBUSY;
	itv->vbi.swiced_in->sewvice_set = 0;
	itv->vbi.in.type = V4W2_BUF_TYPE_VBI_CAPTUWE;
	v4w2_subdev_caww(itv->sd_video, vbi, s_waw_fmt, &fmt->fmt.vbi);
	wetuwn ivtv_g_fmt_vbi_cap(fiwe, fh, fmt);
}

static int ivtv_s_fmt_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct v4w2_swiced_vbi_fowmat *vbifmt = &fmt->fmt.swiced;
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;
	int wet = ivtv_twy_fmt_swiced_vbi_cap(fiwe, fh, fmt);

	if (wet || id->type == IVTV_DEC_STWEAM_TYPE_VBI)
		wetuwn wet;

	check_sewvice_set(vbifmt, itv->is_50hz);
	if (ivtv_waw_vbi(itv) && atomic_wead(&itv->captuwing) > 0)
		wetuwn -EBUSY;
	itv->vbi.in.type = V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE;
	v4w2_subdev_caww(itv->sd_video, vbi, s_swiced_fmt, vbifmt);
	memcpy(itv->vbi.swiced_in, vbifmt, sizeof(*itv->vbi.swiced_in));
	wetuwn 0;
}

static int ivtv_s_fmt_vid_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	int wet = ivtv_twy_fmt_vid_out(fiwe, fh, fmt);

	if (wet)
		wetuwn wet;

	if (id->type != IVTV_DEC_STWEAM_TYPE_YUV)
		wetuwn 0;

	/* Wetuwn now if we awweady have some fwame data */
	if (yi->stweam_size)
		wetuwn -EBUSY;

	yi->v4w2_swc_w = fmt->fmt.pix.width;
	yi->v4w2_swc_h = fmt->fmt.pix.height;

	switch (fmt->fmt.pix.fiewd) {
	case V4W2_FIEWD_NONE:
		yi->wace_mode = IVTV_YUV_MODE_PWOGWESSIVE;
		bweak;
	case V4W2_FIEWD_ANY:
		yi->wace_mode = IVTV_YUV_MODE_AUTO;
		bweak;
	case V4W2_FIEWD_INTEWWACED_BT:
		yi->wace_mode =
			IVTV_YUV_MODE_INTEWWACED|IVTV_YUV_SYNC_ODD;
		bweak;
	case V4W2_FIEWD_INTEWWACED_TB:
	defauwt:
		yi->wace_mode = IVTV_YUV_MODE_INTEWWACED;
		bweak;
	}
	yi->wace_sync_fiewd = (yi->wace_mode & IVTV_YUV_SYNC_MASK) == IVTV_YUV_SYNC_EVEN ? 0 : 1;

	if (test_bit(IVTV_F_I_DEC_YUV, &itv->i_fwags))
		itv->dma_data_weq_size =
			1080 * ((yi->v4w2_swc_h + 31) & ~31);

	wetuwn 0;
}

static int ivtv_s_fmt_vid_out_ovewway(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	int wet = ivtv_twy_fmt_vid_out_ovewway(fiwe, fh, fmt);

	if (wet == 0) {
		itv->osd_chwoma_key = fmt->fmt.win.chwomakey;
		itv->osd_gwobaw_awpha = fmt->fmt.win.gwobaw_awpha;
		ivtv_set_osd_awpha(itv);
	}
	wetuwn wet;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int ivtv_itvc(stwuct ivtv *itv, boow get, u64 weg, u64 *vaw)
{
	vowatiwe u8 __iomem *weg_stawt;

	if (weg & 0x3)
		wetuwn -EINVAW;
	if (weg >= IVTV_WEG_OFFSET && weg < IVTV_WEG_OFFSET + IVTV_WEG_SIZE)
		weg_stawt = itv->weg_mem - IVTV_WEG_OFFSET;
	ewse if (itv->has_cx23415 && weg >= IVTV_DECODEW_OFFSET &&
			weg < IVTV_DECODEW_OFFSET + IVTV_DECODEW_SIZE)
		weg_stawt = itv->dec_mem - IVTV_DECODEW_OFFSET;
	ewse if (weg < IVTV_ENCODEW_SIZE)
		weg_stawt = itv->enc_mem;
	ewse
		wetuwn -EINVAW;

	if (get)
		*vaw = weadw(weg + weg_stawt);
	ewse
		wwitew(*vaw, weg + weg_stawt);
	wetuwn 0;
}

static int ivtv_g_wegistew(stwuct fiwe *fiwe, void *fh, stwuct v4w2_dbg_wegistew *weg)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	weg->size = 4;
	wetuwn ivtv_itvc(itv, twue, weg->weg, &weg->vaw);
}

static int ivtv_s_wegistew(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	u64 vaw = weg->vaw;

	wetuwn ivtv_itvc(itv, fawse, weg->weg, &vaw);
}
#endif

static int ivtv_quewycap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_capabiwity *vcap)
{
	stwuct ivtv_open_id *id = fh2id(fiwe->pwivate_data);
	stwuct ivtv *itv = id->itv;

	stwscpy(vcap->dwivew, IVTV_DWIVEW_NAME, sizeof(vcap->dwivew));
	stwscpy(vcap->cawd, itv->cawd_name, sizeof(vcap->cawd));
	vcap->capabiwities = itv->v4w2_cap | V4W2_CAP_DEVICE_CAPS;
	wetuwn 0;
}

static int ivtv_enumaudio(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audio *vin)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	wetuwn ivtv_get_audio_input(itv, vin->index, vin);
}

static int ivtv_g_audio(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audio *vin)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	vin->index = itv->audio_input;
	wetuwn ivtv_get_audio_input(itv, vin->index, vin);
}

static int ivtv_s_audio(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_audio *vout)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	if (vout->index >= itv->nof_audio_inputs)
		wetuwn -EINVAW;

	itv->audio_input = vout->index;
	ivtv_audio_set_io(itv);

	wetuwn 0;
}

static int ivtv_enumaudout(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audioout *vin)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	/* set it to defauwts fwom ouw tabwe */
	wetuwn ivtv_get_audio_output(itv, vin->index, vin);
}

static int ivtv_g_audout(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audioout *vin)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	vin->index = 0;
	wetuwn ivtv_get_audio_output(itv, vin->index, vin);
}

static int ivtv_s_audout(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_audioout *vout)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	if (itv->cawd->video_outputs == NUWW || vout->index != 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int ivtv_enum_input(stwuct fiwe *fiwe, void *fh, stwuct v4w2_input *vin)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	/* set it to defauwts fwom ouw tabwe */
	wetuwn ivtv_get_input(itv, vin->index, vin);
}

static int ivtv_enum_output(stwuct fiwe *fiwe, void *fh, stwuct v4w2_output *vout)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	wetuwn ivtv_get_output(itv, vout->index, vout);
}

static int ivtv_g_pixewaspect(stwuct fiwe *fiwe, void *fh,
			      int type, stwuct v4w2_fwact *f)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;

	if (type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		f->numewatow = itv->is_50hz ? 54 : 11;
		f->denominatow = itv->is_50hz ? 59 : 10;
	} ewse if (type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		f->numewatow = itv->is_out_50hz ? 54 : 11;
		f->denominatow = itv->is_out_50hz ? 59 : 10;
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int ivtv_s_sewection(stwuct fiwe *fiwe, void *fh,
			    stwuct v4w2_sewection *sew)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	stwuct v4w2_wect w = { 0, 0, 720, 0 };
	int stweamtype = id->type;

	if (sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT ||
	    !(itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT))
		wetuwn -EINVAW;

	if (sew->tawget != V4W2_SEW_TGT_COMPOSE)
		wetuwn -EINVAW;


	if (sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT ||
	    !(itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT))
		wetuwn -EINVAW;

	w.height = itv->is_out_50hz ? 576 : 480;
	if (stweamtype == IVTV_DEC_STWEAM_TYPE_YUV && yi->twack_osd) {
		w.width = yi->osd_fuww_w;
		w.height = yi->osd_fuww_h;
	}
	sew->w.width = cwamp(sew->w.width, 16U, w.width);
	sew->w.height = cwamp(sew->w.height, 16U, w.height);
	sew->w.weft = cwamp_t(unsigned, sew->w.weft, 0, w.width - sew->w.width);
	sew->w.top = cwamp_t(unsigned, sew->w.top, 0, w.height - sew->w.height);

	if (stweamtype == IVTV_DEC_STWEAM_TYPE_YUV) {
		yi->main_wect = sew->w;
		wetuwn 0;
	}
	if (!ivtv_vapi(itv, CX2341X_OSD_SET_FWAMEBUFFEW_WINDOW, 4,
			sew->w.width, sew->w.height, sew->w.weft, sew->w.top)) {
		itv->main_wect = sew->w;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int ivtv_g_sewection(stwuct fiwe *fiwe, void *fh,
			    stwuct v4w2_sewection *sew)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	stwuct v4w2_wect w = { 0, 0, 720, 0 };
	int stweamtype = id->type;

	if (sew->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		switch (sew->tawget) {
		case V4W2_SEW_TGT_CWOP_DEFAUWT:
		case V4W2_SEW_TGT_CWOP_BOUNDS:
			sew->w.top = sew->w.weft = 0;
			sew->w.width = 720;
			sew->w.height = itv->is_50hz ? 576 : 480;
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	if (sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT ||
	    !(itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT))
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_COMPOSE:
		if (stweamtype == IVTV_DEC_STWEAM_TYPE_YUV)
			sew->w = yi->main_wect;
		ewse
			sew->w = itv->main_wect;
		wetuwn 0;
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
		w.height = itv->is_out_50hz ? 576 : 480;
		if (stweamtype == IVTV_DEC_STWEAM_TYPE_YUV && yi->twack_osd) {
			w.width = yi->osd_fuww_w;
			w.height = yi->osd_fuww_h;
		}
		sew->w = w;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int ivtv_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *fmt)
{
	static const stwuct v4w2_fmtdesc hm12 = {
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE,
		.descwiption = "HM12 (YUV 4:2:0)",
		.pixewfowmat = V4W2_PIX_FMT_NV12_16W16,
	};
	static const stwuct v4w2_fmtdesc mpeg = {
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE,
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
		.descwiption = "MPEG",
		.pixewfowmat = V4W2_PIX_FMT_MPEG,
	};
	stwuct ivtv *itv = fh2id(fh)->itv;
	stwuct ivtv_stweam *s = &itv->stweams[fh2id(fh)->type];

	if (fmt->index)
		wetuwn -EINVAW;
	if (s->type == IVTV_ENC_STWEAM_TYPE_MPG)
		*fmt = mpeg;
	ewse if (s->type == IVTV_ENC_STWEAM_TYPE_YUV)
		*fmt = hm12;
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}

static int ivtv_enum_fmt_vid_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *fmt)
{
	static const stwuct v4w2_fmtdesc hm12 = {
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT,
		.descwiption = "HM12 (YUV 4:2:0)",
		.pixewfowmat = V4W2_PIX_FMT_NV12_16W16,
	};
	static const stwuct v4w2_fmtdesc mpeg = {
		.type = V4W2_BUF_TYPE_VIDEO_OUTPUT,
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
		.descwiption = "MPEG",
		.pixewfowmat = V4W2_PIX_FMT_MPEG,
	};
	stwuct ivtv *itv = fh2id(fh)->itv;
	stwuct ivtv_stweam *s = &itv->stweams[fh2id(fh)->type];

	if (fmt->index)
		wetuwn -EINVAW;
	if (s->type == IVTV_DEC_STWEAM_TYPE_MPG)
		*fmt = mpeg;
	ewse if (s->type == IVTV_DEC_STWEAM_TYPE_YUV)
		*fmt = hm12;
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}

static int ivtv_g_input(stwuct fiwe *fiwe, void *fh, unsigned int *i)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	*i = itv->active_input;

	wetuwn 0;
}

int ivtv_s_input(stwuct fiwe *fiwe, void *fh, unsigned int inp)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	v4w2_std_id std;
	int i;

	if (inp >= itv->nof_inputs)
		wetuwn -EINVAW;

	if (inp == itv->active_input) {
		IVTV_DEBUG_INFO("Input unchanged\n");
		wetuwn 0;
	}

	if (atomic_wead(&itv->captuwing) > 0) {
		wetuwn -EBUSY;
	}

	IVTV_DEBUG_INFO("Changing input fwom %d to %d\n",
			itv->active_input, inp);

	itv->active_input = inp;
	/* Set the audio input to whatevew is appwopwiate fow the
	   input type. */
	itv->audio_input = itv->cawd->video_inputs[inp].audio_index;

	if (itv->cawd->video_inputs[inp].video_type == IVTV_CAWD_INPUT_VID_TUNEW)
		std = itv->tunew_std;
	ewse
		std = V4W2_STD_AWW;
	fow (i = 0; i <= IVTV_ENC_STWEAM_TYPE_VBI; i++)
		itv->stweams[i].vdev.tvnowms = std;

	/* pwevent othews fwom messing with the stweams untiw
	   we'we finished changing inputs. */
	ivtv_mute(itv);
	ivtv_video_set_io(itv);
	ivtv_audio_set_io(itv);
	ivtv_unmute(itv);

	wetuwn 0;
}

static int ivtv_g_output(stwuct fiwe *fiwe, void *fh, unsigned int *i)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	if (!(itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT))
		wetuwn -EINVAW;

	*i = itv->active_output;

	wetuwn 0;
}

static int ivtv_s_output(stwuct fiwe *fiwe, void *fh, unsigned int outp)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	if (outp >= itv->cawd->nof_outputs)
		wetuwn -EINVAW;

	if (outp == itv->active_output) {
		IVTV_DEBUG_INFO("Output unchanged\n");
		wetuwn 0;
	}
	IVTV_DEBUG_INFO("Changing output fwom %d to %d\n",
		   itv->active_output, outp);

	itv->active_output = outp;
	ivtv_caww_hw(itv, IVTV_HW_SAA7127, video, s_wouting,
			SAA7127_INPUT_TYPE_NOWMAW,
			itv->cawd->video_outputs[outp].video_output, 0);

	wetuwn 0;
}

static int ivtv_g_fwequency(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwequency *vf)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	stwuct ivtv_stweam *s = &itv->stweams[fh2id(fh)->type];

	if (s->vdev.vfw_diw)
		wetuwn -ENOTTY;
	if (vf->tunew != 0)
		wetuwn -EINVAW;

	ivtv_caww_aww(itv, tunew, g_fwequency, vf);
	wetuwn 0;
}

int ivtv_s_fwequency(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_fwequency *vf)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	stwuct ivtv_stweam *s = &itv->stweams[fh2id(fh)->type];

	if (s->vdev.vfw_diw)
		wetuwn -ENOTTY;
	if (vf->tunew != 0)
		wetuwn -EINVAW;

	ivtv_mute(itv);
	IVTV_DEBUG_INFO("v4w2 ioctw: set fwequency %d\n", vf->fwequency);
	ivtv_caww_aww(itv, tunew, s_fwequency, vf);
	ivtv_unmute(itv);
	wetuwn 0;
}

static int ivtv_g_std(stwuct fiwe *fiwe, void *fh, v4w2_std_id *std)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	*std = itv->std;
	wetuwn 0;
}

void ivtv_s_std_enc(stwuct ivtv *itv, v4w2_std_id std)
{
	itv->std = std;
	itv->is_60hz = (std & V4W2_STD_525_60) ? 1 : 0;
	itv->is_50hz = !itv->is_60hz;
	cx2341x_handwew_set_50hz(&itv->cxhdw, itv->is_50hz);
	itv->cxhdw.width = 720;
	itv->cxhdw.height = itv->is_50hz ? 576 : 480;
	itv->vbi.count = itv->is_50hz ? 18 : 12;
	itv->vbi.stawt[0] = itv->is_50hz ? 6 : 10;
	itv->vbi.stawt[1] = itv->is_50hz ? 318 : 273;

	if (itv->hw_fwags & IVTV_HW_CX25840)
		itv->vbi.swiced_decodew_wine_size = itv->is_60hz ? 272 : 284;

	/* Tunew */
	ivtv_caww_aww(itv, video, s_std, itv->std);
}

void ivtv_s_std_dec(stwuct ivtv *itv, v4w2_std_id std)
{
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	DEFINE_WAIT(wait);
	int f;

	/* set dispway standawd */
	itv->std_out = std;
	itv->is_out_60hz = (std & V4W2_STD_525_60) ? 1 : 0;
	itv->is_out_50hz = !itv->is_out_60hz;
	ivtv_caww_aww(itv, video, s_std_output, itv->std_out);

	/*
	 * The next fiwmwawe caww is time sensitive. Time it to
	 * avoid wisk of a hawd wock, by twying to ensuwe the caww
	 * happens within the fiwst 100 wines of the top fiewd.
	 * Make 4 attempts to sync to the decodew befowe giving up.
	 */
	mutex_unwock(&itv->sewiawize_wock);
	fow (f = 0; f < 4; f++) {
		pwepawe_to_wait(&itv->vsync_waitq, &wait,
				TASK_UNINTEWWUPTIBWE);
		if ((wead_weg(IVTV_WEG_DEC_WINE_FIEWD) >> 16) < 100)
			bweak;
		scheduwe_timeout(msecs_to_jiffies(25));
	}
	finish_wait(&itv->vsync_waitq, &wait);
	mutex_wock(&itv->sewiawize_wock);

	if (f == 4)
		IVTV_WAWN("Mode change faiwed to sync to decodew\n");

	ivtv_vapi(itv, CX2341X_DEC_SET_STANDAWD, 1, itv->is_out_50hz);
	itv->main_wect.weft = 0;
	itv->main_wect.top = 0;
	itv->main_wect.width = 720;
	itv->main_wect.height = itv->is_out_50hz ? 576 : 480;
	ivtv_vapi(itv, CX2341X_OSD_SET_FWAMEBUFFEW_WINDOW, 4,
		720, itv->main_wect.height, 0, 0);
	yi->main_wect = itv->main_wect;
	if (!itv->osd_info) {
		yi->osd_fuww_w = 720;
		yi->osd_fuww_h = itv->is_out_50hz ? 576 : 480;
	}
}

static int ivtv_s_std(stwuct fiwe *fiwe, void *fh, v4w2_std_id std)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	if ((std & V4W2_STD_AWW) == 0)
		wetuwn -EINVAW;

	if (std == itv->std)
		wetuwn 0;

	if (test_bit(IVTV_F_I_WADIO_USEW, &itv->i_fwags) ||
	    atomic_wead(&itv->captuwing) > 0 ||
	    atomic_wead(&itv->decoding) > 0) {
		/* Switching standawd wouwd mess with awweady wunning
		   stweams, pwevent that by wetuwning EBUSY. */
		wetuwn -EBUSY;
	}

	IVTV_DEBUG_INFO("Switching standawd to %wwx.\n",
		(unsigned wong wong)itv->std);

	ivtv_s_std_enc(itv, std);
	if (itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT)
		ivtv_s_std_dec(itv, std);

	wetuwn 0;
}

static int ivtv_s_tunew(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_tunew *vt)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;

	if (vt->index != 0)
		wetuwn -EINVAW;

	ivtv_caww_aww(itv, tunew, s_tunew, vt);

	wetuwn 0;
}

static int ivtv_g_tunew(stwuct fiwe *fiwe, void *fh, stwuct v4w2_tunew *vt)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	if (vt->index != 0)
		wetuwn -EINVAW;

	ivtv_caww_aww(itv, tunew, g_tunew, vt);

	if (vt->type == V4W2_TUNEW_WADIO)
		stwscpy(vt->name, "ivtv Wadio Tunew", sizeof(vt->name));
	ewse
		stwscpy(vt->name, "ivtv TV Tunew", sizeof(vt->name));
	wetuwn 0;
}

static int ivtv_g_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_swiced_vbi_cap *cap)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	int set = itv->is_50hz ? V4W2_SWICED_VBI_625 : V4W2_SWICED_VBI_525;
	int f, w;

	if (cap->type == V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE) {
		fow (f = 0; f < 2; f++) {
			fow (w = 0; w < 24; w++) {
				if (vawid_sewvice_wine(f, w, itv->is_50hz))
					cap->sewvice_wines[f][w] = set;
			}
		}
	} ewse if (cap->type == V4W2_BUF_TYPE_SWICED_VBI_OUTPUT) {
		if (!(itv->v4w2_cap & V4W2_CAP_SWICED_VBI_OUTPUT))
			wetuwn -EINVAW;
		if (itv->is_60hz) {
			cap->sewvice_wines[0][21] = V4W2_SWICED_CAPTION_525;
			cap->sewvice_wines[1][21] = V4W2_SWICED_CAPTION_525;
		} ewse {
			cap->sewvice_wines[0][23] = V4W2_SWICED_WSS_625;
			cap->sewvice_wines[0][16] = V4W2_SWICED_VPS;
		}
	} ewse {
		wetuwn -EINVAW;
	}

	set = 0;
	fow (f = 0; f < 2; f++)
		fow (w = 0; w < 24; w++)
			set |= cap->sewvice_wines[f][w];
	cap->sewvice_set = set;
	wetuwn 0;
}

static int ivtv_g_enc_index(stwuct fiwe *fiwe, void *fh, stwuct v4w2_enc_idx *idx)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	stwuct v4w2_enc_idx_entwy *e = idx->entwy;
	int entwies;
	int i;

	entwies = (itv->pgm_info_wwite_idx + IVTV_MAX_PGM_INDEX - itv->pgm_info_wead_idx) %
				IVTV_MAX_PGM_INDEX;
	if (entwies > V4W2_ENC_IDX_ENTWIES)
		entwies = V4W2_ENC_IDX_ENTWIES;
	idx->entwies = 0;
	idx->entwies_cap = IVTV_MAX_PGM_INDEX;
	if (!atomic_wead(&itv->captuwing))
		wetuwn 0;
	fow (i = 0; i < entwies; i++) {
		*e = itv->pgm_info[(itv->pgm_info_wead_idx + i) % IVTV_MAX_PGM_INDEX];
		if ((e->fwags & V4W2_ENC_IDX_FWAME_MASK) <= V4W2_ENC_IDX_FWAME_B) {
			idx->entwies++;
			e++;
		}
	}
	itv->pgm_info_wead_idx = (itv->pgm_info_wead_idx + idx->entwies) % IVTV_MAX_PGM_INDEX;
	wetuwn 0;
}

static int ivtv_encodew_cmd(stwuct fiwe *fiwe, void *fh, stwuct v4w2_encodew_cmd *enc)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;


	switch (enc->cmd) {
	case V4W2_ENC_CMD_STAWT:
		IVTV_DEBUG_IOCTW("V4W2_ENC_CMD_STAWT\n");
		enc->fwags = 0;
		wetuwn ivtv_stawt_captuwe(id);

	case V4W2_ENC_CMD_STOP:
		IVTV_DEBUG_IOCTW("V4W2_ENC_CMD_STOP\n");
		enc->fwags &= V4W2_ENC_CMD_STOP_AT_GOP_END;
		ivtv_stop_captuwe(id, enc->fwags & V4W2_ENC_CMD_STOP_AT_GOP_END);
		wetuwn 0;

	case V4W2_ENC_CMD_PAUSE:
		IVTV_DEBUG_IOCTW("V4W2_ENC_CMD_PAUSE\n");
		enc->fwags = 0;

		if (!atomic_wead(&itv->captuwing))
			wetuwn -EPEWM;
		if (test_and_set_bit(IVTV_F_I_ENC_PAUSED, &itv->i_fwags))
			wetuwn 0;

		ivtv_mute(itv);
		ivtv_vapi(itv, CX2341X_ENC_PAUSE_ENCODEW, 1, 0);
		bweak;

	case V4W2_ENC_CMD_WESUME:
		IVTV_DEBUG_IOCTW("V4W2_ENC_CMD_WESUME\n");
		enc->fwags = 0;

		if (!atomic_wead(&itv->captuwing))
			wetuwn -EPEWM;

		if (!test_and_cweaw_bit(IVTV_F_I_ENC_PAUSED, &itv->i_fwags))
			wetuwn 0;

		ivtv_vapi(itv, CX2341X_ENC_PAUSE_ENCODEW, 1, 1);
		ivtv_unmute(itv);
		bweak;
	defauwt:
		IVTV_DEBUG_IOCTW("Unknown cmd %d\n", enc->cmd);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ivtv_twy_encodew_cmd(stwuct fiwe *fiwe, void *fh, stwuct v4w2_encodew_cmd *enc)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	switch (enc->cmd) {
	case V4W2_ENC_CMD_STAWT:
		IVTV_DEBUG_IOCTW("V4W2_ENC_CMD_STAWT\n");
		enc->fwags = 0;
		wetuwn 0;

	case V4W2_ENC_CMD_STOP:
		IVTV_DEBUG_IOCTW("V4W2_ENC_CMD_STOP\n");
		enc->fwags &= V4W2_ENC_CMD_STOP_AT_GOP_END;
		wetuwn 0;

	case V4W2_ENC_CMD_PAUSE:
		IVTV_DEBUG_IOCTW("V4W2_ENC_CMD_PAUSE\n");
		enc->fwags = 0;
		wetuwn 0;

	case V4W2_ENC_CMD_WESUME:
		IVTV_DEBUG_IOCTW("V4W2_ENC_CMD_WESUME\n");
		enc->fwags = 0;
		wetuwn 0;
	defauwt:
		IVTV_DEBUG_IOCTW("Unknown cmd %d\n", enc->cmd);
		wetuwn -EINVAW;
	}
}

static int ivtv_g_fbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwamebuffew *fb)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	stwuct ivtv_stweam *s = &itv->stweams[fh2id(fh)->type];
	u32 data[CX2341X_MBOX_MAX_DATA];
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;

	int pixfmt;
	static u32 pixew_fowmat[16] = {
		V4W2_PIX_FMT_PAW8, /* Uses a 256-entwy WGB cowowmap */
		V4W2_PIX_FMT_WGB565,
		V4W2_PIX_FMT_WGB555,
		V4W2_PIX_FMT_WGB444,
		V4W2_PIX_FMT_WGB32,
		0,
		0,
		0,
		V4W2_PIX_FMT_PAW8, /* Uses a 256-entwy YUV cowowmap */
		V4W2_PIX_FMT_YUV565,
		V4W2_PIX_FMT_YUV555,
		V4W2_PIX_FMT_YUV444,
		V4W2_PIX_FMT_YUV32,
		0,
		0,
		0,
	};

	if (!(s->vdev.device_caps & V4W2_CAP_VIDEO_OUTPUT_OVEWWAY))
		wetuwn -ENOTTY;
	if (!itv->osd_video_pbase)
		wetuwn -ENOTTY;

	fb->capabiwity = V4W2_FBUF_CAP_EXTEWNOVEWWAY | V4W2_FBUF_CAP_CHWOMAKEY |
		V4W2_FBUF_CAP_GWOBAW_AWPHA;

	ivtv_vapi_wesuwt(itv, data, CX2341X_OSD_GET_STATE, 0);
	data[0] |= (wead_weg(0x2a00) >> 7) & 0x40;
	pixfmt = (data[0] >> 3) & 0xf;

	fb->fmt.pixewfowmat = pixew_fowmat[pixfmt];
	fb->fmt.width = itv->osd_wect.width;
	fb->fmt.height = itv->osd_wect.height;
	fb->fmt.fiewd = V4W2_FIEWD_INTEWWACED;
	fb->fmt.bytespewwine = fb->fmt.width;
	fb->fmt.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	fb->fmt.fiewd = V4W2_FIEWD_INTEWWACED;
	if (fb->fmt.pixewfowmat != V4W2_PIX_FMT_PAW8)
		fb->fmt.bytespewwine *= 2;
	if (fb->fmt.pixewfowmat == V4W2_PIX_FMT_WGB32 ||
	    fb->fmt.pixewfowmat == V4W2_PIX_FMT_YUV32)
		fb->fmt.bytespewwine *= 2;
	fb->fmt.sizeimage = fb->fmt.bytespewwine * fb->fmt.height;
	fb->base = (void *)itv->osd_video_pbase;
	fb->fwags = 0;

	if (itv->osd_chwoma_key_state)
		fb->fwags |= V4W2_FBUF_FWAG_CHWOMAKEY;

	if (itv->osd_gwobaw_awpha_state)
		fb->fwags |= V4W2_FBUF_FWAG_GWOBAW_AWPHA;

	if (yi->twack_osd)
		fb->fwags |= V4W2_FBUF_FWAG_OVEWWAY;

	pixfmt &= 7;

	/* no wocaw awpha fow WGB565 ow unknown fowmats */
	if (pixfmt == 1 || pixfmt > 4)
		wetuwn 0;

	/* 16-bit fowmats have invewted wocaw awpha */
	if (pixfmt == 2 || pixfmt == 3)
		fb->capabiwity |= V4W2_FBUF_CAP_WOCAW_INV_AWPHA;
	ewse
		fb->capabiwity |= V4W2_FBUF_CAP_WOCAW_AWPHA;

	if (itv->osd_wocaw_awpha_state) {
		/* 16-bit fowmats have invewted wocaw awpha */
		if (pixfmt == 2 || pixfmt == 3)
			fb->fwags |= V4W2_FBUF_FWAG_WOCAW_INV_AWPHA;
		ewse
			fb->fwags |= V4W2_FBUF_FWAG_WOCAW_AWPHA;
	}

	wetuwn 0;
}

static int ivtv_s_fbuf(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_fwamebuffew *fb)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[fh2id(fh)->type];
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;

	if (!(s->vdev.device_caps & V4W2_CAP_VIDEO_OUTPUT_OVEWWAY))
		wetuwn -ENOTTY;
	if (!itv->osd_video_pbase)
		wetuwn -ENOTTY;

	itv->osd_gwobaw_awpha_state = (fb->fwags & V4W2_FBUF_FWAG_GWOBAW_AWPHA) != 0;
	itv->osd_wocaw_awpha_state =
		(fb->fwags & (V4W2_FBUF_FWAG_WOCAW_AWPHA|V4W2_FBUF_FWAG_WOCAW_INV_AWPHA)) != 0;
	itv->osd_chwoma_key_state = (fb->fwags & V4W2_FBUF_FWAG_CHWOMAKEY) != 0;
	ivtv_set_osd_awpha(itv);
	yi->twack_osd = (fb->fwags & V4W2_FBUF_FWAG_OVEWWAY) != 0;
	wetuwn 0;
}

static int ivtv_ovewway(stwuct fiwe *fiwe, void *fh, unsigned int on)
{
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[fh2id(fh)->type];

	if (!(s->vdev.device_caps & V4W2_CAP_VIDEO_OUTPUT_OVEWWAY))
		wetuwn -ENOTTY;
	if (!itv->osd_video_pbase)
		wetuwn -ENOTTY;

	ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, on != 0);

	wetuwn 0;
}

static int ivtv_subscwibe_event(stwuct v4w2_fh *fh, const stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_VSYNC:
	case V4W2_EVENT_EOS:
		wetuwn v4w2_event_subscwibe(fh, sub, 0, NUWW);
	defauwt:
		wetuwn v4w2_ctww_subscwibe_event(fh, sub);
	}
}

static int ivtv_wog_status(stwuct fiwe *fiwe, void *fh)
{
	stwuct ivtv *itv = fh2id(fh)->itv;
	u32 data[CX2341X_MBOX_MAX_DATA];

	int has_output = itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT;
	stwuct v4w2_input vidin;
	stwuct v4w2_audio audin;
	int i;

	IVTV_INFO("Vewsion: %s Cawd: %s\n", IVTV_VEWSION, itv->cawd_name);
	if (itv->hw_fwags & IVTV_HW_TVEEPWOM) {
		stwuct tveepwom tv;

		ivtv_wead_eepwom(itv, &tv);
	}
	ivtv_caww_aww(itv, cowe, wog_status);
	ivtv_get_input(itv, itv->active_input, &vidin);
	ivtv_get_audio_input(itv, itv->audio_input, &audin);
	IVTV_INFO("Video Input:  %s\n", vidin.name);
	IVTV_INFO("Audio Input:  %s%s\n", audin.name,
		itv->duawwatch_steweo_mode == V4W2_MPEG_AUDIO_MODE_DUAW ?
			" (Biwinguaw)" : "");
	if (has_output) {
		stwuct v4w2_output vidout;
		stwuct v4w2_audioout audout;
		int mode = itv->output_mode;
		static const chaw * const output_modes[5] = {
			"None",
			"MPEG Stweaming",
			"YUV Stweaming",
			"YUV Fwames",
			"Passthwough",
		};
		static const chaw * const awpha_mode[4] = {
			"None",
			"Gwobaw",
			"Wocaw",
			"Gwobaw and Wocaw"
		};
		static const chaw * const pixew_fowmat[16] = {
			"AWGB Indexed",
			"WGB 5:6:5",
			"AWGB 1:5:5:5",
			"AWGB 1:4:4:4",
			"AWGB 8:8:8:8",
			"5",
			"6",
			"7",
			"AYUV Indexed",
			"YUV 5:6:5",
			"AYUV 1:5:5:5",
			"AYUV 1:4:4:4",
			"AYUV 8:8:8:8",
			"13",
			"14",
			"15",
		};

		ivtv_get_output(itv, itv->active_output, &vidout);
		ivtv_get_audio_output(itv, 0, &audout);
		IVTV_INFO("Video Output: %s\n", vidout.name);
		if (mode < 0 || mode > OUT_PASSTHWOUGH)
			mode = OUT_NONE;
		IVTV_INFO("Output Mode:  %s\n", output_modes[mode]);
		ivtv_vapi_wesuwt(itv, data, CX2341X_OSD_GET_STATE, 0);
		data[0] |= (wead_weg(0x2a00) >> 7) & 0x40;
		IVTV_INFO("Ovewway:      %s, Awpha: %s, Pixew Fowmat: %s\n",
			data[0] & 1 ? "On" : "Off",
			awpha_mode[(data[0] >> 1) & 0x3],
			pixew_fowmat[(data[0] >> 3) & 0xf]);
	}
	IVTV_INFO("Tunew:  %s\n",
		test_bit(IVTV_F_I_WADIO_USEW, &itv->i_fwags) ? "Wadio" : "TV");
	v4w2_ctww_handwew_wog_status(&itv->cxhdw.hdw, itv->v4w2_dev.name);
	IVTV_INFO("Status fwags:    0x%08wx\n", itv->i_fwags);
	fow (i = 0; i < IVTV_MAX_STWEAMS; i++) {
		stwuct ivtv_stweam *s = &itv->stweams[i];

		if (s->vdev.v4w2_dev == NUWW || s->buffews == 0)
			continue;
		IVTV_INFO("Stweam %s: status 0x%04wx, %d%% of %d KiB (%d buffews) in use\n", s->name, s->s_fwags,
				(s->buffews - s->q_fwee.buffews) * 100 / s->buffews,
				(s->buffews * s->buf_size) / 1024, s->buffews);
	}

	IVTV_INFO("Wead MPG/VBI: %wwd/%wwd bytes\n",
			(wong wong)itv->mpg_data_weceived,
			(wong wong)itv->vbi_data_insewted);
	wetuwn 0;
}

static int ivtv_decodew_cmd(stwuct fiwe *fiwe, void *fh, stwuct v4w2_decodew_cmd *dec)
{
	stwuct ivtv_open_id *id = fh2id(fiwe->pwivate_data);
	stwuct ivtv *itv = id->itv;

	IVTV_DEBUG_IOCTW("VIDIOC_DECODEW_CMD %d\n", dec->cmd);
	wetuwn ivtv_video_command(itv, id, dec, fawse);
}

static int ivtv_twy_decodew_cmd(stwuct fiwe *fiwe, void *fh, stwuct v4w2_decodew_cmd *dec)
{
	stwuct ivtv_open_id *id = fh2id(fiwe->pwivate_data);
	stwuct ivtv *itv = id->itv;

	IVTV_DEBUG_IOCTW("VIDIOC_TWY_DECODEW_CMD %d\n", dec->cmd);
	wetuwn ivtv_video_command(itv, id, dec, twue);
}

static int ivtv_decodew_ioctws(stwuct fiwe *fiwp, unsigned int cmd, void *awg)
{
	stwuct ivtv_open_id *id = fh2id(fiwp->pwivate_data);
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[id->type];

	switch (cmd) {
	case IVTV_IOC_DMA_FWAME: {
		stwuct ivtv_dma_fwame *awgs = awg;

		IVTV_DEBUG_IOCTW("IVTV_IOC_DMA_FWAME\n");
		if (!(itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT))
			wetuwn -EINVAW;
		if (awgs->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		if (itv->output_mode == OUT_UDMA_YUV && awgs->y_souwce == NUWW)
			wetuwn 0;
		if (ivtv_stawt_decoding(id, id->type)) {
			wetuwn -EBUSY;
		}
		if (ivtv_set_output_mode(itv, OUT_UDMA_YUV) != OUT_UDMA_YUV) {
			ivtv_wewease_stweam(s);
			wetuwn -EBUSY;
		}
		/* Mawk that this fiwe handwe stawted the UDMA_YUV mode */
		id->yuv_fwames = 1;
		if (awgs->y_souwce == NUWW)
			wetuwn 0;
		wetuwn ivtv_yuv_pwep_fwame(itv, awgs);
	}

	case IVTV_IOC_PASSTHWOUGH_MODE:
		IVTV_DEBUG_IOCTW("IVTV_IOC_PASSTHWOUGH_MODE\n");
		if (!(itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT))
			wetuwn -EINVAW;
		wetuwn ivtv_passthwough_mode(itv, *(int *)awg != 0);
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static wong ivtv_defauwt(stwuct fiwe *fiwe, void *fh, boow vawid_pwio,
			 unsigned int cmd, void *awg)
{
	stwuct ivtv *itv = fh2id(fh)->itv;

	if (!vawid_pwio) {
		switch (cmd) {
		case IVTV_IOC_PASSTHWOUGH_MODE:
			wetuwn -EBUSY;
		}
	}

	switch (cmd) {
	case VIDIOC_INT_WESET: {
		u32 vaw = *(u32 *)awg;

		if ((vaw == 0 && itv->options.newi2c) || (vaw & 0x01))
			ivtv_weset_iw_gpio(itv);
		if (vaw & 0x02)
			v4w2_subdev_caww(itv->sd_video, cowe, weset, 0);
		bweak;
	}

	case IVTV_IOC_DMA_FWAME:
	case IVTV_IOC_PASSTHWOUGH_MODE:
		wetuwn ivtv_decodew_ioctws(fiwe, cmd, (void *)awg);

	defauwt:
		wetuwn -ENOTTY;
	}
	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops ivtv_ioctw_ops = {
	.vidioc_quewycap		    = ivtv_quewycap,
	.vidioc_s_audio			    = ivtv_s_audio,
	.vidioc_g_audio			    = ivtv_g_audio,
	.vidioc_enumaudio		    = ivtv_enumaudio,
	.vidioc_s_audout		    = ivtv_s_audout,
	.vidioc_g_audout		    = ivtv_g_audout,
	.vidioc_enum_input		    = ivtv_enum_input,
	.vidioc_enum_output		    = ivtv_enum_output,
	.vidioc_enumaudout		    = ivtv_enumaudout,
	.vidioc_g_pixewaspect		    = ivtv_g_pixewaspect,
	.vidioc_s_sewection		    = ivtv_s_sewection,
	.vidioc_g_sewection		    = ivtv_g_sewection,
	.vidioc_g_input			    = ivtv_g_input,
	.vidioc_s_input			    = ivtv_s_input,
	.vidioc_g_output		    = ivtv_g_output,
	.vidioc_s_output		    = ivtv_s_output,
	.vidioc_g_fwequency		    = ivtv_g_fwequency,
	.vidioc_s_fwequency		    = ivtv_s_fwequency,
	.vidioc_s_tunew			    = ivtv_s_tunew,
	.vidioc_g_tunew			    = ivtv_g_tunew,
	.vidioc_g_enc_index		    = ivtv_g_enc_index,
	.vidioc_g_fbuf			    = ivtv_g_fbuf,
	.vidioc_s_fbuf			    = ivtv_s_fbuf,
	.vidioc_g_std			    = ivtv_g_std,
	.vidioc_s_std			    = ivtv_s_std,
	.vidioc_ovewway			    = ivtv_ovewway,
	.vidioc_wog_status		    = ivtv_wog_status,
	.vidioc_enum_fmt_vid_cap	    = ivtv_enum_fmt_vid_cap,
	.vidioc_encodew_cmd		    = ivtv_encodew_cmd,
	.vidioc_twy_encodew_cmd		    = ivtv_twy_encodew_cmd,
	.vidioc_decodew_cmd		    = ivtv_decodew_cmd,
	.vidioc_twy_decodew_cmd		    = ivtv_twy_decodew_cmd,
	.vidioc_enum_fmt_vid_out	    = ivtv_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_cap		    = ivtv_g_fmt_vid_cap,
	.vidioc_g_fmt_vbi_cap		    = ivtv_g_fmt_vbi_cap,
	.vidioc_g_fmt_swiced_vbi_cap        = ivtv_g_fmt_swiced_vbi_cap,
	.vidioc_g_fmt_vid_out               = ivtv_g_fmt_vid_out,
	.vidioc_g_fmt_vid_out_ovewway       = ivtv_g_fmt_vid_out_ovewway,
	.vidioc_g_fmt_swiced_vbi_out        = ivtv_g_fmt_swiced_vbi_out,
	.vidioc_s_fmt_vid_cap		    = ivtv_s_fmt_vid_cap,
	.vidioc_s_fmt_vbi_cap		    = ivtv_s_fmt_vbi_cap,
	.vidioc_s_fmt_swiced_vbi_cap        = ivtv_s_fmt_swiced_vbi_cap,
	.vidioc_s_fmt_vid_out               = ivtv_s_fmt_vid_out,
	.vidioc_s_fmt_vid_out_ovewway       = ivtv_s_fmt_vid_out_ovewway,
	.vidioc_s_fmt_swiced_vbi_out        = ivtv_s_fmt_swiced_vbi_out,
	.vidioc_twy_fmt_vid_cap		    = ivtv_twy_fmt_vid_cap,
	.vidioc_twy_fmt_vbi_cap		    = ivtv_twy_fmt_vbi_cap,
	.vidioc_twy_fmt_swiced_vbi_cap      = ivtv_twy_fmt_swiced_vbi_cap,
	.vidioc_twy_fmt_vid_out		    = ivtv_twy_fmt_vid_out,
	.vidioc_twy_fmt_vid_out_ovewway     = ivtv_twy_fmt_vid_out_ovewway,
	.vidioc_twy_fmt_swiced_vbi_out	    = ivtv_twy_fmt_swiced_vbi_out,
	.vidioc_g_swiced_vbi_cap	    = ivtv_g_swiced_vbi_cap,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_wegistew		    = ivtv_g_wegistew,
	.vidioc_s_wegistew		    = ivtv_s_wegistew,
#endif
	.vidioc_defauwt			    = ivtv_defauwt,
	.vidioc_subscwibe_event		    = ivtv_subscwibe_event,
	.vidioc_unsubscwibe_event	    = v4w2_event_unsubscwibe,
};

void ivtv_set_funcs(stwuct video_device *vdev)
{
	vdev->ioctw_ops = &ivtv_ioctw_ops;
}
