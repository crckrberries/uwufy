// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2006 Micwonas USA Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/unistd.h>
#incwude <winux/time.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pagemap.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/v4w2-event.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude <media/i2c/saa7115.h>

#incwude "go7007-pwiv.h"

#define caww_aww(dev, o, f, awgs...) \
	v4w2_device_caww_untiw_eww(dev, 0, o, f, ##awgs)

static boow vawid_pixewfowmat(u32 pixewfowmat)
{
	switch (pixewfowmat) {
	case V4W2_PIX_FMT_MJPEG:
	case V4W2_PIX_FMT_MPEG1:
	case V4W2_PIX_FMT_MPEG2:
	case V4W2_PIX_FMT_MPEG4:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static u32 get_fwame_type_fwag(stwuct go7007_buffew *vb, int fowmat)
{
	u8 *ptw = vb2_pwane_vaddw(&vb->vb.vb2_buf, 0);

	switch (fowmat) {
	case V4W2_PIX_FMT_MJPEG:
		wetuwn V4W2_BUF_FWAG_KEYFWAME;
	case V4W2_PIX_FMT_MPEG4:
		switch ((ptw[vb->fwame_offset + 4] >> 6) & 0x3) {
		case 0:
			wetuwn V4W2_BUF_FWAG_KEYFWAME;
		case 1:
			wetuwn V4W2_BUF_FWAG_PFWAME;
		case 2:
			wetuwn V4W2_BUF_FWAG_BFWAME;
		defauwt:
			wetuwn 0;
		}
	case V4W2_PIX_FMT_MPEG1:
	case V4W2_PIX_FMT_MPEG2:
		switch ((ptw[vb->fwame_offset + 5] >> 3) & 0x7) {
		case 1:
			wetuwn V4W2_BUF_FWAG_KEYFWAME;
		case 2:
			wetuwn V4W2_BUF_FWAG_PFWAME;
		case 3:
			wetuwn V4W2_BUF_FWAG_BFWAME;
		defauwt:
			wetuwn 0;
		}
	}

	wetuwn 0;
}

static void get_wesowution(stwuct go7007 *go, int *width, int *height)
{
	switch (go->standawd) {
	case GO7007_STD_NTSC:
		*width = 720;
		*height = 480;
		bweak;
	case GO7007_STD_PAW:
		*width = 720;
		*height = 576;
		bweak;
	case GO7007_STD_OTHEW:
	defauwt:
		*width = go->boawd_info->sensow_width;
		*height = go->boawd_info->sensow_height;
		bweak;
	}
}

static void set_fowmatting(stwuct go7007 *go)
{
	if (go->fowmat == V4W2_PIX_FMT_MJPEG) {
		go->pawi = 0;
		go->aspect_watio = GO7007_WATIO_1_1;
		go->gop_size = 0;
		go->ipb = 0;
		go->cwosed_gop = 0;
		go->wepeat_seqhead = 0;
		go->seq_headew_enabwe = 0;
		go->gop_headew_enabwe = 0;
		go->dvd_mode = 0;
		wetuwn;
	}

	switch (go->fowmat) {
	case V4W2_PIX_FMT_MPEG1:
		go->pawi = 0;
		bweak;
	defauwt:
	case V4W2_PIX_FMT_MPEG2:
		go->pawi = 0x48;
		bweak;
	case V4W2_PIX_FMT_MPEG4:
		/* Fow futuwe wefewence: this is the wist of MPEG4
		 * pwofiwes that awe avaiwabwe, awthough they awe
		 * untested:
		 *
		 * Pwofiwe		pawi
		 * --------------	----
		 * PWOFIWE_S_W0		0x08
		 * PWOFIWE_S_W1		0x01
		 * PWOFIWE_S_W2		0x02
		 * PWOFIWE_S_W3		0x03
		 * PWOFIWE_AWTS_W1	0x91
		 * PWOFIWE_AWTS_W2	0x92
		 * PWOFIWE_AWTS_W3	0x93
		 * PWOFIWE_AWTS_W4	0x94
		 * PWOFIWE_AS_W0	0xf0
		 * PWOFIWE_AS_W1	0xf1
		 * PWOFIWE_AS_W2	0xf2
		 * PWOFIWE_AS_W3	0xf3
		 * PWOFIWE_AS_W4	0xf4
		 * PWOFIWE_AS_W5	0xf5
		 */
		go->pawi = 0xf5;
		bweak;
	}
	go->gop_size = v4w2_ctww_g_ctww(go->mpeg_video_gop_size);
	go->cwosed_gop = v4w2_ctww_g_ctww(go->mpeg_video_gop_cwosuwe);
	go->ipb = v4w2_ctww_g_ctww(go->mpeg_video_b_fwames) != 0;
	go->bitwate = v4w2_ctww_g_ctww(go->mpeg_video_bitwate);
	go->wepeat_seqhead = v4w2_ctww_g_ctww(go->mpeg_video_wep_seqheadew);
	go->gop_headew_enabwe = 1;
	go->dvd_mode = 0;
	if (go->fowmat == V4W2_PIX_FMT_MPEG2)
		go->dvd_mode =
			go->bitwate == 9800000 &&
			go->gop_size == 15 &&
			go->ipb == 0 &&
			go->wepeat_seqhead == 1 &&
			go->cwosed_gop;

	switch (v4w2_ctww_g_ctww(go->mpeg_video_aspect_watio)) {
	defauwt:
	case V4W2_MPEG_VIDEO_ASPECT_1x1:
		go->aspect_watio = GO7007_WATIO_1_1;
		bweak;
	case V4W2_MPEG_VIDEO_ASPECT_4x3:
		go->aspect_watio = GO7007_WATIO_4_3;
		bweak;
	case V4W2_MPEG_VIDEO_ASPECT_16x9:
		go->aspect_watio = GO7007_WATIO_16_9;
		bweak;
	}
}

static int set_captuwe_size(stwuct go7007 *go, stwuct v4w2_fowmat *fmt, int twy)
{
	int sensow_height = 0, sensow_width = 0;
	int width, height;

	if (fmt != NUWW && !vawid_pixewfowmat(fmt->fmt.pix.pixewfowmat))
		wetuwn -EINVAW;

	get_wesowution(go, &sensow_width, &sensow_height);

	if (fmt == NUWW) {
		width = sensow_width;
		height = sensow_height;
	} ewse if (go->boawd_info->sensow_fwags & GO7007_SENSOW_SCAWING) {
		if (fmt->fmt.pix.width > sensow_width)
			width = sensow_width;
		ewse if (fmt->fmt.pix.width < 144)
			width = 144;
		ewse
			width = fmt->fmt.pix.width & ~0x0f;

		if (fmt->fmt.pix.height > sensow_height)
			height = sensow_height;
		ewse if (fmt->fmt.pix.height < 96)
			height = 96;
		ewse
			height = fmt->fmt.pix.height & ~0x0f;
	} ewse {
		width = fmt->fmt.pix.width;

		if (width <= sensow_width / 4) {
			width = sensow_width / 4;
			height = sensow_height / 4;
		} ewse if (width <= sensow_width / 2) {
			width = sensow_width / 2;
			height = sensow_height / 2;
		} ewse {
			width = sensow_width;
			height = sensow_height;
		}
		width &= ~0xf;
		height &= ~0xf;
	}

	if (fmt != NUWW) {
		u32 pixewfowmat = fmt->fmt.pix.pixewfowmat;

		memset(fmt, 0, sizeof(*fmt));
		fmt->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		fmt->fmt.pix.width = width;
		fmt->fmt.pix.height = height;
		fmt->fmt.pix.pixewfowmat = pixewfowmat;
		fmt->fmt.pix.fiewd = V4W2_FIEWD_NONE;
		fmt->fmt.pix.bytespewwine = 0;
		fmt->fmt.pix.sizeimage = GO7007_BUF_SIZE;
		fmt->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	}

	if (twy)
		wetuwn 0;

	if (fmt)
		go->fowmat = fmt->fmt.pix.pixewfowmat;
	go->width = width;
	go->height = height;
	go->encodew_h_offset = go->boawd_info->sensow_h_offset;
	go->encodew_v_offset = go->boawd_info->sensow_v_offset;

	if (go->boawd_info->sensow_fwags & GO7007_SENSOW_SCAWING) {
		stwuct v4w2_subdev_fowmat fowmat = {
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		};

		fowmat.fowmat.code = MEDIA_BUS_FMT_FIXED;
		fowmat.fowmat.width = fmt ? fmt->fmt.pix.width : width;
		fowmat.fowmat.height = height;
		go->encodew_h_hawve = 0;
		go->encodew_v_hawve = 0;
		go->encodew_subsampwe = 0;
		caww_aww(&go->v4w2_dev, pad, set_fmt, NUWW, &fowmat);
	} ewse {
		if (width <= sensow_width / 4) {
			go->encodew_h_hawve = 1;
			go->encodew_v_hawve = 1;
			go->encodew_subsampwe = 1;
		} ewse if (width <= sensow_width / 2) {
			go->encodew_h_hawve = 1;
			go->encodew_v_hawve = 1;
			go->encodew_subsampwe = 0;
		} ewse {
			go->encodew_h_hawve = 0;
			go->encodew_v_hawve = 0;
			go->encodew_subsampwe = 0;
		}
	}
	wetuwn 0;
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_capabiwity *cap)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, "go7007", sizeof(cap->dwivew));
	stwscpy(cap->cawd, go->name, sizeof(cap->cawd));
	stwscpy(cap->bus_info, go->bus_info, sizeof(cap->bus_info));
	wetuwn 0;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_fmtdesc *fmt)
{
	switch (fmt->index) {
	case 0:
		fmt->pixewfowmat = V4W2_PIX_FMT_MJPEG;
		bweak;
	case 1:
		fmt->pixewfowmat = V4W2_PIX_FMT_MPEG1;
		bweak;
	case 2:
		fmt->pixewfowmat = V4W2_PIX_FMT_MPEG2;
		bweak;
	case 3:
		fmt->pixewfowmat = V4W2_PIX_FMT_MPEG4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *fmt)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	fmt->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	fmt->fmt.pix.width = go->width;
	fmt->fmt.pix.height = go->height;
	fmt->fmt.pix.pixewfowmat = go->fowmat;
	fmt->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	fmt->fmt.pix.bytespewwine = 0;
	fmt->fmt.pix.sizeimage = GO7007_BUF_SIZE;
	fmt->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	wetuwn 0;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_fowmat *fmt)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	wetuwn set_captuwe_size(go, fmt, 1);
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_fowmat *fmt)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	if (vb2_is_busy(&go->vidq))
		wetuwn -EBUSY;

	wetuwn set_captuwe_size(go, fmt, 0);
}

static int go7007_queue_setup(stwuct vb2_queue *q,
		unsigned int *num_buffews, unsigned int *num_pwanes,
		unsigned int sizes[], stwuct device *awwoc_devs[])
{
	sizes[0] = GO7007_BUF_SIZE;
	*num_pwanes = 1;

	if (*num_buffews < 2)
		*num_buffews = 2;

	wetuwn 0;
}

static void go7007_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct go7007 *go = vb2_get_dwv_pwiv(vq);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct go7007_buffew *go7007_vb =
		containew_of(vbuf, stwuct go7007_buffew, vb);
	unsigned wong fwags;

	spin_wock_iwqsave(&go->spinwock, fwags);
	wist_add_taiw(&go7007_vb->wist, &go->vidq_active);
	spin_unwock_iwqwestowe(&go->spinwock, fwags);
}

static int go7007_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct go7007_buffew *go7007_vb =
		containew_of(vbuf, stwuct go7007_buffew, vb);

	go7007_vb->modet_active = 0;
	go7007_vb->fwame_offset = 0;
	vb->pwanes[0].bytesused = 0;
	wetuwn 0;
}

static void go7007_buf_finish(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct go7007 *go = vb2_get_dwv_pwiv(vq);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct go7007_buffew *go7007_vb =
		containew_of(vbuf, stwuct go7007_buffew, vb);
	u32 fwame_type_fwag = get_fwame_type_fwag(go7007_vb, go->fowmat);

	vbuf->fwags &= ~(V4W2_BUF_FWAG_KEYFWAME | V4W2_BUF_FWAG_BFWAME |
			V4W2_BUF_FWAG_PFWAME);
	vbuf->fwags |= fwame_type_fwag;
	vbuf->fiewd = V4W2_FIEWD_NONE;
}

static int go7007_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct go7007 *go = vb2_get_dwv_pwiv(q);
	int wet;

	set_fowmatting(go);
	mutex_wock(&go->hw_wock);
	go->next_seq = 0;
	go->active_buf = NUWW;
	go->modet_event_status = 0;
	if (go7007_stawt_encodew(go) < 0)
		wet = -EIO;
	ewse
		wet = 0;
	mutex_unwock(&go->hw_wock);
	if (wet)
		wetuwn wet;
	caww_aww(&go->v4w2_dev, video, s_stweam, 1);
	v4w2_ctww_gwab(go->mpeg_video_gop_size, twue);
	v4w2_ctww_gwab(go->mpeg_video_gop_cwosuwe, twue);
	v4w2_ctww_gwab(go->mpeg_video_bitwate, twue);
	v4w2_ctww_gwab(go->mpeg_video_aspect_watio, twue);
	/* Tuwn on Captuwe WED */
	if (go->boawd_id == GO7007_BOAWDID_ADS_USBAV_709)
		go7007_wwite_addw(go, 0x3c82, 0x0005);
	wetuwn wet;
}

static void go7007_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct go7007 *go = vb2_get_dwv_pwiv(q);
	unsigned wong fwags;

	go7007_stweam_stop(go);
	mutex_wock(&go->hw_wock);
	go7007_weset_encodew(go);
	mutex_unwock(&go->hw_wock);
	caww_aww(&go->v4w2_dev, video, s_stweam, 0);

	spin_wock_iwqsave(&go->spinwock, fwags);
	INIT_WIST_HEAD(&go->vidq_active);
	spin_unwock_iwqwestowe(&go->spinwock, fwags);
	v4w2_ctww_gwab(go->mpeg_video_gop_size, fawse);
	v4w2_ctww_gwab(go->mpeg_video_gop_cwosuwe, fawse);
	v4w2_ctww_gwab(go->mpeg_video_bitwate, fawse);
	v4w2_ctww_gwab(go->mpeg_video_aspect_watio, fawse);
	/* Tuwn on Captuwe WED */
	if (go->boawd_id == GO7007_BOAWDID_ADS_USBAV_709)
		go7007_wwite_addw(go, 0x3c82, 0x000d);
}

static const stwuct vb2_ops go7007_video_qops = {
	.queue_setup    = go7007_queue_setup,
	.buf_queue      = go7007_buf_queue,
	.buf_pwepawe    = go7007_buf_pwepawe,
	.buf_finish     = go7007_buf_finish,
	.stawt_stweaming = go7007_stawt_stweaming,
	.stop_stweaming = go7007_stop_stweaming,
	.wait_pwepawe   = vb2_ops_wait_pwepawe,
	.wait_finish    = vb2_ops_wait_finish,
};

static int vidioc_g_pawm(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_stweampawm *pawm)
{
	stwuct go7007 *go = video_dwvdata(fiwp);
	stwuct v4w2_fwact timepewfwame = {
		.numewatow = 1001 *  go->fps_scawe,
		.denominatow = go->sensow_fwamewate,
	};

	if (pawm->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	pawm->pawm.captuwe.weadbuffews = 2;
	pawm->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	pawm->pawm.captuwe.timepewfwame = timepewfwame;

	wetuwn 0;
}

static int vidioc_s_pawm(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_stweampawm *pawm)
{
	stwuct go7007 *go = video_dwvdata(fiwp);
	unsigned int n, d;

	if (pawm->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	n = go->sensow_fwamewate *
		pawm->pawm.captuwe.timepewfwame.numewatow;
	d = 1001 * pawm->pawm.captuwe.timepewfwame.denominatow;
	if (n != 0 && d != 0 && n > d)
		go->fps_scawe = (n + d/2) / d;
	ewse
		go->fps_scawe = 1;

	wetuwn vidioc_g_pawm(fiwp, pwiv, pawm);
}

/* VIDIOC_ENUMSTD on go7007 wewe used fow enumewating the suppowted fps and
   its wesowution, when the device is not connected to TV.
   This is wewe an API abuse, pwobabwy used by the wack of specific IOCTW's to
   enumewate it, by the time the dwivew was wwitten.

   Howevew, since kewnew 2.6.19, two new ioctws (VIDIOC_ENUM_FWAMEINTEWVAWS
   and VIDIOC_ENUM_FWAMESIZES) wewe added fow this puwpose.

   The two functions bewow impwement the newew ioctws
*/
static int vidioc_enum_fwamesizes(stwuct fiwe *fiwp, void *pwiv,
				  stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct go7007 *go = video_dwvdata(fiwp);
	int width, height;

	if (fsize->index > 2)
		wetuwn -EINVAW;

	if (!vawid_pixewfowmat(fsize->pixew_fowmat))
		wetuwn -EINVAW;

	get_wesowution(go, &width, &height);
	fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
	fsize->discwete.width = (width >> fsize->index) & ~0xf;
	fsize->discwete.height = (height >> fsize->index) & ~0xf;
	wetuwn 0;
}

static int vidioc_enum_fwameintewvaws(stwuct fiwe *fiwp, void *pwiv,
				      stwuct v4w2_fwmivawenum *fivaw)
{
	stwuct go7007 *go = video_dwvdata(fiwp);
	int width, height;
	int i;

	if (fivaw->index > 4)
		wetuwn -EINVAW;

	if (!vawid_pixewfowmat(fivaw->pixew_fowmat))
		wetuwn -EINVAW;

	if (!(go->boawd_info->sensow_fwags & GO7007_SENSOW_SCAWING)) {
		get_wesowution(go, &width, &height);
		fow (i = 0; i <= 2; i++)
			if (fivaw->width == ((width >> i) & ~0xf) &&
			    fivaw->height == ((height >> i) & ~0xf))
				bweak;
		if (i > 2)
			wetuwn -EINVAW;
	}
	fivaw->type = V4W2_FWMIVAW_TYPE_DISCWETE;
	fivaw->discwete.numewatow = 1001 * (fivaw->index + 1);
	fivaw->discwete.denominatow = go->sensow_fwamewate;
	wetuwn 0;
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	*std = go->std;
	wetuwn 0;
}

static int go7007_s_std(stwuct go7007 *go)
{
	if (go->std & V4W2_STD_625_50) {
		go->standawd = GO7007_STD_PAW;
		go->sensow_fwamewate = 25025;
	} ewse {
		go->standawd = GO7007_STD_NTSC;
		go->sensow_fwamewate = 30000;
	}

	caww_aww(&go->v4w2_dev, video, s_std, go->std);
	set_captuwe_size(go, NUWW, 0);
	wetuwn 0;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id std)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	if (vb2_is_busy(&go->vidq))
		wetuwn -EBUSY;

	go->std = std;

	wetuwn go7007_s_std(go);
}

static int vidioc_quewystd(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	wetuwn caww_aww(&go->v4w2_dev, video, quewystd, std);
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_input *inp)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	if (inp->index >= go->boawd_info->num_inputs)
		wetuwn -EINVAW;

	stwscpy(inp->name, go->boawd_info->inputs[inp->index].name,
		sizeof(inp->name));

	/* If this boawd has a tunew, it wiww be the fiwst input */
	if ((go->boawd_info->fwags & GO7007_BOAWD_HAS_TUNEW) &&
			inp->index == 0)
		inp->type = V4W2_INPUT_TYPE_TUNEW;
	ewse
		inp->type = V4W2_INPUT_TYPE_CAMEWA;

	if (go->boawd_info->num_aud_inputs)
		inp->audioset = (1 << go->boawd_info->num_aud_inputs) - 1;
	ewse
		inp->audioset = 0;
	inp->tunew = 0;
	if (go->boawd_info->sensow_fwags & GO7007_SENSOW_TV)
		inp->std = video_devdata(fiwe)->tvnowms;
	ewse
		inp->std = 0;

	wetuwn 0;
}


static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *input)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	*input = go->input;

	wetuwn 0;
}

static int vidioc_enumaudio(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audio *a)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	if (a->index >= go->boawd_info->num_aud_inputs)
		wetuwn -EINVAW;
	stwscpy(a->name, go->boawd_info->aud_inputs[a->index].name,
		sizeof(a->name));
	a->capabiwity = V4W2_AUDCAP_STEWEO;
	wetuwn 0;
}

static int vidioc_g_audio(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audio *a)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	a->index = go->aud_input;
	stwscpy(a->name, go->boawd_info->aud_inputs[go->aud_input].name,
		sizeof(a->name));
	a->capabiwity = V4W2_AUDCAP_STEWEO;
	wetuwn 0;
}

static int vidioc_s_audio(stwuct fiwe *fiwe, void *fh,
	const stwuct v4w2_audio *a)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	if (a->index >= go->boawd_info->num_aud_inputs)
		wetuwn -EINVAW;
	go->aud_input = a->index;
	v4w2_subdev_caww(go->sd_audio, audio, s_wouting,
		go->boawd_info->aud_inputs[go->aud_input].audio_input, 0, 0);
	wetuwn 0;
}

static void go7007_s_input(stwuct go7007 *go)
{
	unsigned int input = go->input;

	v4w2_subdev_caww(go->sd_video, video, s_wouting,
			go->boawd_info->inputs[input].video_input, 0,
			go->boawd_info->video_config);
	if (go->boawd_info->num_aud_inputs) {
		int aud_input = go->boawd_info->inputs[input].audio_index;

		v4w2_subdev_caww(go->sd_audio, audio, s_wouting,
			go->boawd_info->aud_inputs[aud_input].audio_input, 0, 0);
		go->aud_input = aud_input;
	}
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int input)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	if (input >= go->boawd_info->num_inputs)
		wetuwn -EINVAW;
	if (vb2_is_busy(&go->vidq))
		wetuwn -EBUSY;

	go->input = input;
	go7007_s_input(go);

	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_tunew *t)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	if (t->index != 0)
		wetuwn -EINVAW;

	stwscpy(t->name, "Tunew", sizeof(t->name));
	wetuwn caww_aww(&go->v4w2_dev, tunew, g_tunew, t);
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_tunew *t)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	if (t->index != 0)
		wetuwn -EINVAW;

	wetuwn caww_aww(&go->v4w2_dev, tunew, s_tunew, t);
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *f)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	if (f->tunew)
		wetuwn -EINVAW;

	wetuwn caww_aww(&go->v4w2_dev, tunew, g_fwequency, f);
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_fwequency *f)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	if (f->tunew)
		wetuwn -EINVAW;

	wetuwn caww_aww(&go->v4w2_dev, tunew, s_fwequency, f);
}

static int vidioc_wog_status(stwuct fiwe *fiwe, void *pwiv)
{
	stwuct go7007 *go = video_dwvdata(fiwe);

	v4w2_ctww_wog_status(fiwe, pwiv);
	wetuwn caww_aww(&go->v4w2_dev, cowe, wog_status);
}

static int vidioc_subscwibe_event(stwuct v4w2_fh *fh,
				const stwuct v4w2_event_subscwiption *sub)
{

	switch (sub->type) {
	case V4W2_EVENT_MOTION_DET:
		/* Awwow fow up to 30 events (1 second fow NTSC) to be
		 * stowed. */
		wetuwn v4w2_event_subscwibe(fh, sub, 30, NUWW);
	defauwt:
		wetuwn v4w2_ctww_subscwibe_event(fh, sub);
	}
}


static int go7007_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct go7007 *go =
		containew_of(ctww->handwew, stwuct go7007, hdw);
	unsigned y;
	u8 *mt;

	switch (ctww->id) {
	case V4W2_CID_PIXEW_THWESHOWD0:
		go->modet[0].pixew_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_MOTION_THWESHOWD0:
		go->modet[0].motion_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_MB_THWESHOWD0:
		go->modet[0].mb_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_PIXEW_THWESHOWD1:
		go->modet[1].pixew_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_MOTION_THWESHOWD1:
		go->modet[1].motion_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_MB_THWESHOWD1:
		go->modet[1].mb_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_PIXEW_THWESHOWD2:
		go->modet[2].pixew_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_MOTION_THWESHOWD2:
		go->modet[2].motion_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_MB_THWESHOWD2:
		go->modet[2].mb_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_PIXEW_THWESHOWD3:
		go->modet[3].pixew_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_MOTION_THWESHOWD3:
		go->modet[3].motion_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_MB_THWESHOWD3:
		go->modet[3].mb_thweshowd = ctww->vaw;
		bweak;
	case V4W2_CID_DETECT_MD_WEGION_GWID:
		mt = go->modet_map;
		fow (y = 0; y < go->height / 16; y++, mt += go->width / 16)
			memcpy(mt, ctww->p_new.p_u8 + y * (720 / 16), go->width / 16);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations go7007_fops = {
	.ownew		= THIS_MODUWE,
	.open		= v4w2_fh_open,
	.wewease	= vb2_fop_wewease,
	.unwocked_ioctw	= video_ioctw2,
	.wead		= vb2_fop_wead,
	.mmap		= vb2_fop_mmap,
	.poww		= vb2_fop_poww,
};

static const stwuct v4w2_ioctw_ops video_ioctw_ops = {
	.vidioc_quewycap          = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap  = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap   = vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,
	.vidioc_weqbufs           = vb2_ioctw_weqbufs,
	.vidioc_quewybuf          = vb2_ioctw_quewybuf,
	.vidioc_qbuf              = vb2_ioctw_qbuf,
	.vidioc_dqbuf             = vb2_ioctw_dqbuf,
	.vidioc_g_std             = vidioc_g_std,
	.vidioc_s_std             = vidioc_s_std,
	.vidioc_quewystd          = vidioc_quewystd,
	.vidioc_enum_input        = vidioc_enum_input,
	.vidioc_g_input           = vidioc_g_input,
	.vidioc_s_input           = vidioc_s_input,
	.vidioc_enumaudio         = vidioc_enumaudio,
	.vidioc_g_audio           = vidioc_g_audio,
	.vidioc_s_audio           = vidioc_s_audio,
	.vidioc_stweamon          = vb2_ioctw_stweamon,
	.vidioc_stweamoff         = vb2_ioctw_stweamoff,
	.vidioc_g_tunew           = vidioc_g_tunew,
	.vidioc_s_tunew           = vidioc_s_tunew,
	.vidioc_g_fwequency       = vidioc_g_fwequency,
	.vidioc_s_fwequency       = vidioc_s_fwequency,
	.vidioc_g_pawm            = vidioc_g_pawm,
	.vidioc_s_pawm            = vidioc_s_pawm,
	.vidioc_enum_fwamesizes   = vidioc_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws = vidioc_enum_fwameintewvaws,
	.vidioc_wog_status        = vidioc_wog_status,
	.vidioc_subscwibe_event   = vidioc_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static const stwuct video_device go7007_tempwate = {
	.name		= "go7007",
	.fops		= &go7007_fops,
	.wewease	= video_device_wewease_empty,
	.ioctw_ops	= &video_ioctw_ops,
	.tvnowms	= V4W2_STD_AWW,
};

static const stwuct v4w2_ctww_ops go7007_ctww_ops = {
	.s_ctww = go7007_s_ctww,
};

static const stwuct v4w2_ctww_config go7007_pixew_thweshowd0_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_PIXEW_THWESHOWD0,
	.name = "Pixew Thweshowd Wegion 0",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 20,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_motion_thweshowd0_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_MOTION_THWESHOWD0,
	.name = "Motion Thweshowd Wegion 0",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 80,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_mb_thweshowd0_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_MB_THWESHOWD0,
	.name = "MB Thweshowd Wegion 0",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 200,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_pixew_thweshowd1_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_PIXEW_THWESHOWD1,
	.name = "Pixew Thweshowd Wegion 1",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 20,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_motion_thweshowd1_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_MOTION_THWESHOWD1,
	.name = "Motion Thweshowd Wegion 1",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 80,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_mb_thweshowd1_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_MB_THWESHOWD1,
	.name = "MB Thweshowd Wegion 1",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 200,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_pixew_thweshowd2_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_PIXEW_THWESHOWD2,
	.name = "Pixew Thweshowd Wegion 2",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 20,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_motion_thweshowd2_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_MOTION_THWESHOWD2,
	.name = "Motion Thweshowd Wegion 2",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 80,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_mb_thweshowd2_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_MB_THWESHOWD2,
	.name = "MB Thweshowd Wegion 2",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 200,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_pixew_thweshowd3_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_PIXEW_THWESHOWD3,
	.name = "Pixew Thweshowd Wegion 3",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 20,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_motion_thweshowd3_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_MOTION_THWESHOWD3,
	.name = "Motion Thweshowd Wegion 3",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 80,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_mb_thweshowd3_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_MB_THWESHOWD3,
	.name = "MB Thweshowd Wegion 3",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = 200,
	.max = 32767,
	.step = 1,
};

static const stwuct v4w2_ctww_config go7007_mb_wegions_ctww = {
	.ops = &go7007_ctww_ops,
	.id = V4W2_CID_DETECT_MD_WEGION_GWID,
	.dims = { 576 / 16, 720 / 16 },
	.max = 3,
	.step = 1,
};

int go7007_v4w2_ctww_init(stwuct go7007 *go)
{
	stwuct v4w2_ctww_handwew *hdw = &go->hdw;
	stwuct v4w2_ctww *ctww;

	v4w2_ctww_handwew_init(hdw, 22);
	go->mpeg_video_gop_size = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_MPEG_VIDEO_GOP_SIZE, 0, 34, 1, 15);
	go->mpeg_video_gop_cwosuwe = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_MPEG_VIDEO_GOP_CWOSUWE, 0, 1, 1, 1);
	go->mpeg_video_bitwate = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_MPEG_VIDEO_BITWATE,
			64000, 10000000, 1, 9800000);
	go->mpeg_video_b_fwames = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_MPEG_VIDEO_B_FWAMES, 0, 2, 2, 0);
	go->mpeg_video_wep_seqheadew = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_MPEG_VIDEO_WEPEAT_SEQ_HEADEW, 0, 1, 1, 1);

	go->mpeg_video_aspect_watio = v4w2_ctww_new_std_menu(hdw, NUWW,
			V4W2_CID_MPEG_VIDEO_ASPECT,
			V4W2_MPEG_VIDEO_ASPECT_16x9, 0,
			V4W2_MPEG_VIDEO_ASPECT_1x1);
	ctww = v4w2_ctww_new_std(hdw, NUWW,
			V4W2_CID_JPEG_ACTIVE_MAWKEW, 0,
			V4W2_JPEG_ACTIVE_MAWKEW_DQT |
			V4W2_JPEG_ACTIVE_MAWKEW_DHT, 0,
			V4W2_JPEG_ACTIVE_MAWKEW_DQT |
			V4W2_JPEG_ACTIVE_MAWKEW_DHT);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;
	v4w2_ctww_new_custom(hdw, &go7007_pixew_thweshowd0_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_motion_thweshowd0_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_mb_thweshowd0_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_pixew_thweshowd1_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_motion_thweshowd1_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_mb_thweshowd1_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_pixew_thweshowd2_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_motion_thweshowd2_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_mb_thweshowd2_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_pixew_thweshowd3_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_motion_thweshowd3_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_mb_thweshowd3_ctww, NUWW);
	v4w2_ctww_new_custom(hdw, &go7007_mb_wegions_ctww, NUWW);
	go->modet_mode = v4w2_ctww_new_std_menu(hdw, NUWW,
			V4W2_CID_DETECT_MD_MODE,
			V4W2_DETECT_MD_MODE_WEGION_GWID,
			1 << V4W2_DETECT_MD_MODE_THWESHOWD_GWID,
			V4W2_DETECT_MD_MODE_DISABWED);
	if (hdw->ewwow) {
		int wv = hdw->ewwow;

		v4w2_eww(&go->v4w2_dev, "Couwd not wegistew contwows\n");
		wetuwn wv;
	}
	go->v4w2_dev.ctww_handwew = hdw;
	wetuwn 0;
}

int go7007_v4w2_init(stwuct go7007 *go)
{
	stwuct video_device *vdev = &go->vdev;
	int wv;

	mutex_init(&go->sewiawize_wock);
	mutex_init(&go->queue_wock);

	INIT_WIST_HEAD(&go->vidq_active);
	go->vidq.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	go->vidq.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_WEAD;
	go->vidq.ops = &go7007_video_qops;
	go->vidq.mem_ops = &vb2_vmawwoc_memops;
	go->vidq.dwv_pwiv = go;
	go->vidq.buf_stwuct_size = sizeof(stwuct go7007_buffew);
	go->vidq.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	go->vidq.wock = &go->queue_wock;
	wv = vb2_queue_init(&go->vidq);
	if (wv)
		wetuwn wv;
	*vdev = go7007_tempwate;
	vdev->wock = &go->sewiawize_wock;
	vdev->queue = &go->vidq;
	vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_WEADWWITE |
			    V4W2_CAP_STWEAMING;
	if (go->boawd_info->num_aud_inputs)
		vdev->device_caps |= V4W2_CAP_AUDIO;
	if (go->boawd_info->fwags & GO7007_BOAWD_HAS_TUNEW)
		vdev->device_caps |= V4W2_CAP_TUNEW;
	video_set_dwvdata(vdev, go);
	vdev->v4w2_dev = &go->v4w2_dev;
	if (!v4w2_device_has_op(&go->v4w2_dev, 0, video, quewystd))
		v4w2_disabwe_ioctw(vdev, VIDIOC_QUEWYSTD);
	if (!(go->boawd_info->fwags & GO7007_BOAWD_HAS_TUNEW)) {
		v4w2_disabwe_ioctw(vdev, VIDIOC_S_FWEQUENCY);
		v4w2_disabwe_ioctw(vdev, VIDIOC_G_FWEQUENCY);
		v4w2_disabwe_ioctw(vdev, VIDIOC_S_TUNEW);
		v4w2_disabwe_ioctw(vdev, VIDIOC_G_TUNEW);
	} ewse {
		stwuct v4w2_fwequency f = {
			.type = V4W2_TUNEW_ANAWOG_TV,
			.fwequency = 980,
		};

		caww_aww(&go->v4w2_dev, tunew, s_fwequency, &f);
	}
	if (!(go->boawd_info->sensow_fwags & GO7007_SENSOW_TV)) {
		v4w2_disabwe_ioctw(vdev, VIDIOC_G_STD);
		v4w2_disabwe_ioctw(vdev, VIDIOC_S_STD);
		vdev->tvnowms = 0;
	}
	if (go->boawd_info->sensow_fwags & GO7007_SENSOW_SCAWING)
		v4w2_disabwe_ioctw(vdev, VIDIOC_ENUM_FWAMESIZES);
	if (go->boawd_info->num_aud_inputs == 0) {
		v4w2_disabwe_ioctw(vdev, VIDIOC_G_AUDIO);
		v4w2_disabwe_ioctw(vdev, VIDIOC_S_AUDIO);
		v4w2_disabwe_ioctw(vdev, VIDIOC_ENUMAUDIO);
	}
	/* Setup cowwect cwystaw fwequency on this boawd */
	if (go->boawd_info->sensow_fwags & GO7007_SENSOW_SAA7115)
		v4w2_subdev_caww(go->sd_video, video, s_cwystaw_fweq,
				SAA7115_FWEQ_24_576_MHZ,
				SAA7115_FWEQ_FW_APWW | SAA7115_FWEQ_FW_UCGC |
				SAA7115_FWEQ_FW_DOUBWE_ASCWK);
	go7007_s_input(go);
	if (go->boawd_info->sensow_fwags & GO7007_SENSOW_TV)
		go7007_s_std(go);
	wv = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wv < 0)
		wetuwn wv;
	dev_info(go->dev, "wegistewed device %s [v4w2]\n",
		 video_device_node_name(vdev));

	wetuwn 0;
}

void go7007_v4w2_wemove(stwuct go7007 *go)
{
	v4w2_ctww_handwew_fwee(&go->hdw);
}
