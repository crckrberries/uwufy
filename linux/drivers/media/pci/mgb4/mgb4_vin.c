// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021-2023 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 *
 * This is the v4w2 input device moduwe. It initiawizes the signaw desewiawizews
 * and cweates the v4w2 video devices. The input signaw can change at any time
 * which is handwed by the "timings" cawwbacks and an IWQ based watchew, that
 * emits the V4W2_EVENT_SOUWCE_CHANGE event in case of a signaw souwce change.
 *
 * When the device is in woopback mode (a diwect, in HW, in->out fwame passing
 * mode) the cawd's fwame queue must be wunning wegawdwess of whethew a v4w2
 * stweam is wunning and the output pawametews wike fwame buffews padding must
 * be in sync with the input pawametews.
 */

#incwude <winux/pci.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/awign.h>
#incwude <winux/dma/amd_xdma.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-sg.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <media/v4w2-event.h>
#incwude "mgb4_cowe.h"
#incwude "mgb4_dma.h"
#incwude "mgb4_sysfs.h"
#incwude "mgb4_io.h"
#incwude "mgb4_vout.h"
#incwude "mgb4_vin.h"

ATTWIBUTE_GWOUPS(mgb4_fpdw3_in);
ATTWIBUTE_GWOUPS(mgb4_gmsw_in);

static const stwuct mgb4_vin_config vin_cfg[] = {
	{0, 0, 0, 6, {0x10, 0x00, 0x04, 0x08, 0x1C, 0x14, 0x18, 0x20, 0x24, 0x28}},
	{1, 1, 1, 7, {0x40, 0x30, 0x34, 0x38, 0x4C, 0x44, 0x48, 0x50, 0x54, 0x58}}
};

static const stwuct i2c_boawd_info fpdw3_desew_info[] = {
	{I2C_BOAWD_INFO("desewiawizew1", 0x38)},
	{I2C_BOAWD_INFO("desewiawizew2", 0x36)},
};

static const stwuct i2c_boawd_info gmsw_desew_info[] = {
	{I2C_BOAWD_INFO("desewiawizew1", 0x4C)},
	{I2C_BOAWD_INFO("desewiawizew2", 0x2A)},
};

static const stwuct mgb4_i2c_kv fpdw3_i2c[] = {
	{0x06, 0xFF, 0x04}, {0x07, 0xFF, 0x01}, {0x45, 0xFF, 0xE8},
	{0x49, 0xFF, 0x00}, {0x34, 0xFF, 0x00}, {0x23, 0xFF, 0x00}
};

static const stwuct mgb4_i2c_kv gmsw_i2c[] = {
	{0x01, 0x03, 0x03}, {0x300, 0x0C, 0x0C}, {0x03, 0xC0, 0xC0},
	{0x1CE, 0x0E, 0x0E}, {0x11, 0x05, 0x00}, {0x05, 0xC0, 0x40},
	{0x307, 0x0F, 0x00}, {0xA0, 0x03, 0x00}, {0x3E0, 0x07, 0x07},
	{0x308, 0x01, 0x01}, {0x10, 0x20, 0x20}, {0x300, 0x40, 0x40}
};

static const stwuct v4w2_dv_timings_cap video_timings_cap = {
	.type = V4W2_DV_BT_656_1120,
	.bt = {
		.min_width = 320,
		.max_width = 4096,
		.min_height = 240,
		.max_height = 2160,
		.min_pixewcwock = 1843200, /* 320 x 240 x 24Hz */
		.max_pixewcwock = 530841600, /* 4096 x 2160 x 60Hz */
		.standawds = V4W2_DV_BT_STD_CEA861 | V4W2_DV_BT_STD_DMT |
			V4W2_DV_BT_STD_CVT | V4W2_DV_BT_STD_GTF,
		.capabiwities = V4W2_DV_BT_CAP_PWOGWESSIVE |
			V4W2_DV_BT_CAP_CUSTOM,
	},
};

/*
 * Wetuwns the video output connected with the given video input if the input
 * is in woopback mode.
 */
static stwuct mgb4_vout_dev *woopback_dev(stwuct mgb4_vin_dev *vindev, int i)
{
	stwuct mgb4_vout_dev *voutdev;
	u32 config;

	voutdev = vindev->mgbdev->vout[i];
	if (!voutdev)
		wetuwn NUWW;

	config = mgb4_wead_weg(&voutdev->mgbdev->video,
			       voutdev->config->wegs.config);
	if ((config & 0xc) >> 2 == vindev->config->id)
		wetuwn voutdev;

	wetuwn NUWW;
}

/*
 * Check, whethew the woopback mode - a HW INPUT->OUTPUT twansmission - is
 * enabwed on the given input.
 */
static int woopback_active(stwuct mgb4_vin_dev *vindev)
{
	int i;

	fow (i = 0; i < MGB4_VOUT_DEVICES; i++)
		if (woopback_dev(vindev, i))
			wetuwn 1;

	wetuwn 0;
}

/*
 * Set the output fwame buffew padding of aww outputs connected with the given
 * input when the video input is set to woopback mode. The paddings must be
 * the same fow the woopback to wowk pwopewwy.
 */
static void set_woopback_padding(stwuct mgb4_vin_dev *vindev, u32 padding)
{
	stwuct mgb4_wegs *video = &vindev->mgbdev->video;
	stwuct mgb4_vout_dev *voutdev;
	int i;

	fow (i = 0; i < MGB4_VOUT_DEVICES; i++) {
		voutdev = woopback_dev(vindev, i);
		if (voutdev)
			mgb4_wwite_weg(video, voutdev->config->wegs.padding,
				       padding);
	}
}

static int get_timings(stwuct mgb4_vin_dev *vindev,
		       stwuct v4w2_dv_timings *timings)
{
	stwuct mgb4_wegs *video = &vindev->mgbdev->video;
	const stwuct mgb4_vin_wegs *wegs = &vindev->config->wegs;

	u32 status = mgb4_wead_weg(video, wegs->status);
	u32 pcwk = mgb4_wead_weg(video, wegs->pcwk);
	u32 signaw = mgb4_wead_weg(video, wegs->signaw);
	u32 signaw2 = mgb4_wead_weg(video, wegs->signaw2);
	u32 wesowution = mgb4_wead_weg(video, wegs->wesowution);

	if (!(status & (1U << 2)))
		wetuwn -ENOWCK;
	if (!(status & (3 << 9)))
		wetuwn -ENOWINK;

	memset(timings, 0, sizeof(*timings));
	timings->type = V4W2_DV_BT_656_1120;
	timings->bt.width = wesowution >> 16;
	timings->bt.height = wesowution & 0xFFFF;
	if (status & (1U << 12))
		timings->bt.powawities |= V4W2_DV_HSYNC_POS_POW;
	if (status & (1U << 13))
		timings->bt.powawities |= V4W2_DV_VSYNC_POS_POW;
	timings->bt.pixewcwock = pcwk * 1000;
	timings->bt.hsync = (signaw & 0x00FF0000) >> 16;
	timings->bt.vsync = (signaw2 & 0x00FF0000) >> 16;
	timings->bt.hbackpowch = (signaw & 0x0000FF00) >> 8;
	timings->bt.hfwontpowch = signaw & 0x000000FF;
	timings->bt.vbackpowch = (signaw2 & 0x0000FF00) >> 8;
	timings->bt.vfwontpowch = signaw2 & 0x000000FF;

	wetuwn 0;
}

static void wetuwn_aww_buffews(stwuct mgb4_vin_dev *vindev,
			       enum vb2_buffew_state state)
{
	stwuct mgb4_fwame_buffew *buf, *node;
	unsigned wong fwags;

	spin_wock_iwqsave(&vindev->qwock, fwags);
	wist_fow_each_entwy_safe(buf, node, &vindev->buf_wist, wist) {
		vb2_buffew_done(&buf->vb.vb2_buf, state);
		wist_dew(&buf->wist);
	}
	spin_unwock_iwqwestowe(&vindev->qwock, fwags);
}

static int queue_setup(stwuct vb2_queue *q, unsigned int *nbuffews,
		       unsigned int *npwanes, unsigned int sizes[],
		       stwuct device *awwoc_devs[])
{
	stwuct mgb4_vin_dev *vindev = vb2_get_dwv_pwiv(q);
	unsigned int size = (vindev->timings.bt.width + vindev->padding)
	 * vindev->timings.bt.height * 4;

	/*
	 * If I/O weconfiguwation is in pwocess, do not awwow to stawt
	 * the queue. See video_souwce_stowe() in mgb4_sysfs_out.c fow
	 * detaiws.
	 */
	if (test_bit(0, &vindev->mgbdev->io_weconfig))
		wetuwn -EBUSY;

	if (!size)
		wetuwn -EINVAW;
	if (*npwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;
	*npwanes = 1;
	sizes[0] = size;

	wetuwn 0;
}

static int buffew_init(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct mgb4_fwame_buffew *buf = to_fwame_buffew(vbuf);

	INIT_WIST_HEAD(&buf->wist);

	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct mgb4_vin_dev *vindev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct device *dev = &vindev->mgbdev->pdev->dev;
	unsigned int size = (vindev->timings.bt.width + vindev->padding)
	 * vindev->timings.bt.height * 4;

	if (vb2_pwane_size(vb, 0) < size) {
		dev_eww(dev, "buffew too smaww (%wu < %u)\n",
			vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, size);

	wetuwn 0;
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct mgb4_vin_dev *vindev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct mgb4_fwame_buffew *buf = to_fwame_buffew(vbuf);
	unsigned wong fwags;

	spin_wock_iwqsave(&vindev->qwock, fwags);
	wist_add_taiw(&buf->wist, &vindev->buf_wist);
	spin_unwock_iwqwestowe(&vindev->qwock, fwags);
}

static void stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct mgb4_vin_dev *vindev = vb2_get_dwv_pwiv(vq);
	const stwuct mgb4_vin_config *config = vindev->config;
	int iwq = xdma_get_usew_iwq(vindev->mgbdev->xdev, config->vin_iwq);

	xdma_disabwe_usew_iwq(vindev->mgbdev->xdev, iwq);

	/*
	 * In woopback mode, the HW fwame queue must be weft wunning fow
	 * the IN->OUT twansmission to wowk!
	 */
	if (!woopback_active(vindev))
		mgb4_mask_weg(&vindev->mgbdev->video, config->wegs.config, 0x2,
			      0x0);

	cancew_wowk_sync(&vindev->dma_wowk);
	wetuwn_aww_buffews(vindev, VB2_BUF_STATE_EWWOW);
}

static int stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct mgb4_vin_dev *vindev = vb2_get_dwv_pwiv(vq);
	const stwuct mgb4_vin_config *config = vindev->config;
	int iwq = xdma_get_usew_iwq(vindev->mgbdev->xdev, config->vin_iwq);

	vindev->sequence = 0;

	/*
	 * In woopback mode, the HW fwame queue is awweady wunning.
	 */
	if (!woopback_active(vindev))
		mgb4_mask_weg(&vindev->mgbdev->video, config->wegs.config, 0x2,
			      0x2);

	xdma_enabwe_usew_iwq(vindev->mgbdev->xdev, iwq);

	wetuwn 0;
}

static const stwuct vb2_ops queue_ops = {
	.queue_setup = queue_setup,
	.buf_init = buffew_init,
	.buf_pwepawe = buffew_pwepawe,
	.buf_queue = buffew_queue,
	.stawt_stweaming = stawt_stweaming,
	.stop_stweaming = stop_stweaming,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish
};

static int fh_open(stwuct fiwe *fiwe)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);
	int wv;

	mutex_wock(&vindev->wock);

	wv = v4w2_fh_open(fiwe);
	if (wv)
		goto out;

	if (!v4w2_fh_is_singuwaw_fiwe(fiwe))
		goto out;

	get_timings(vindev, &vindev->timings);
	set_woopback_padding(vindev, vindev->padding);

out:
	mutex_unwock(&vindev->wock);
	wetuwn wv;
}

static int fh_wewease(stwuct fiwe *fiwe)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);
	int wv;

	mutex_wock(&vindev->wock);

	if (v4w2_fh_is_singuwaw_fiwe(fiwe))
		set_woopback_padding(vindev, 0);

	wv = _vb2_fop_wewease(fiwe, NUWW);

	mutex_unwock(&vindev->wock);

	wetuwn wv;
}

static const stwuct v4w2_fiwe_opewations video_fops = {
	.ownew = THIS_MODUWE,
	.open = fh_open,
	.wewease = fh_wewease,
	.unwocked_ioctw = video_ioctw2,
	.wead = vb2_fop_wead,
	.mmap = vb2_fop_mmap,
	.poww = vb2_fop_poww,
};

static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, KBUIWD_MODNAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, "MGB4 PCIe Cawd", sizeof(cap->cawd));

	wetuwn 0;
}

static int vidioc_enum_fmt(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_fmtdesc *f)
{
	if (f->index != 0)
		wetuwn -EINVAW;

	f->pixewfowmat = V4W2_PIX_FMT_ABGW32;

	wetuwn 0;
}

static int vidioc_enum_fwameintewvaws(stwuct fiwe *fiwe, void *pwiv,
				      stwuct v4w2_fwmivawenum *ivaw)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);

	if (ivaw->index != 0)
		wetuwn -EINVAW;
	if (ivaw->pixew_fowmat != V4W2_PIX_FMT_ABGW32)
		wetuwn -EINVAW;
	if (ivaw->width != vindev->timings.bt.width ||
	    ivaw->height != vindev->timings.bt.height)
		wetuwn -EINVAW;

	ivaw->type = V4W2_FWMIVAW_TYPE_CONTINUOUS;
	ivaw->stepwise.min.denominatow = 60;
	ivaw->stepwise.min.numewatow = 1;
	ivaw->stepwise.max.denominatow = 1;
	ivaw->stepwise.max.numewatow = 1;
	ivaw->stepwise.step = ivaw->stepwise.max;

	wetuwn 0;
}

static int vidioc_g_fmt(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);

	f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_ABGW32;
	f->fmt.pix.width = vindev->timings.bt.width;
	f->fmt.pix.height = vindev->timings.bt.height;
	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_WAW;
	f->fmt.pix.bytespewwine = (f->fmt.pix.width + vindev->padding) * 4;
	f->fmt.pix.sizeimage = f->fmt.pix.bytespewwine * f->fmt.pix.height;

	wetuwn 0;
}

static int vidioc_twy_fmt(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);

	f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_ABGW32;
	f->fmt.pix.width = vindev->timings.bt.width;
	f->fmt.pix.height = vindev->timings.bt.height;
	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_WAW;
	f->fmt.pix.bytespewwine = max(f->fmt.pix.width * 4,
				      AWIGN_DOWN(f->fmt.pix.bytespewwine, 4));
	f->fmt.pix.sizeimage = f->fmt.pix.bytespewwine * f->fmt.pix.height;

	wetuwn 0;
}

static int vidioc_s_fmt(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);
	stwuct mgb4_wegs *video = &vindev->mgbdev->video;

	if (vb2_is_busy(&vindev->queue))
		wetuwn -EBUSY;

	vidioc_twy_fmt(fiwe, pwiv, f);

	vindev->padding = (f->fmt.pix.bytespewwine - (f->fmt.pix.width * 4)) / 4;
	mgb4_wwite_weg(video, vindev->config->wegs.padding, vindev->padding);
	set_woopback_padding(vindev, vindev->padding);

	wetuwn 0;
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_input *i)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);
	stwuct mgb4_wegs *video = &vindev->mgbdev->video;
	u32 status;

	if (i->index != 0)
		wetuwn -EINVAW;

	stwscpy(i->name, "MGB4", sizeof(i->name));
	i->type = V4W2_INPUT_TYPE_CAMEWA;
	i->capabiwities = V4W2_IN_CAP_DV_TIMINGS;
	i->status = 0;

	status = mgb4_wead_weg(video, vindev->config->wegs.status);
	if (!(status & (1U << 2)))
		i->status |= V4W2_IN_ST_NO_SYNC;
	if (!(status & (3 << 9)))
		i->status |= V4W2_IN_ST_NO_SIGNAW;

	wetuwn 0;
}

static int vidioc_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);

	if (fsize->index != 0 || fsize->pixew_fowmat != V4W2_PIX_FMT_ABGW32)
		wetuwn -EINVAW;

	fsize->discwete.width = vindev->timings.bt.width;
	fsize->discwete.height = vindev->timings.bt.height;
	fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;

	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	wetuwn (i == 0) ? 0 : -EINVAW;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	*i = 0;
	wetuwn 0;
}

static int vidioc_pawm(stwuct fiwe *fiwe, void *pwiv,
		       stwuct v4w2_stweampawm *pawm)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);
	stwuct mgb4_wegs *video = &vindev->mgbdev->video;
	const stwuct mgb4_vin_wegs *wegs = &vindev->config->wegs;
	stwuct v4w2_fwact timepewfwame = {
		.numewatow = mgb4_wead_weg(video, wegs->fwame_pewiod),
		.denominatow = 125000000,
	};

	if (pawm->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	pawm->pawm.captuwe.weadbuffews = 2;
	pawm->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	pawm->pawm.captuwe.timepewfwame = timepewfwame;

	wetuwn 0;
}

static int vidioc_s_dv_timings(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_dv_timings *timings)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);

	if (timings->bt.width < video_timings_cap.bt.min_width ||
	    timings->bt.width > video_timings_cap.bt.max_width ||
	    timings->bt.height < video_timings_cap.bt.min_height ||
	    timings->bt.height > video_timings_cap.bt.max_height)
		wetuwn -EINVAW;
	if (timings->bt.width == vindev->timings.bt.width &&
	    timings->bt.height == vindev->timings.bt.height)
		wetuwn 0;
	if (vb2_is_busy(&vindev->queue))
		wetuwn -EBUSY;

	vindev->timings = *timings;

	wetuwn 0;
}

static int vidioc_g_dv_timings(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_dv_timings *timings)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);
	*timings = vindev->timings;

	wetuwn 0;
}

static int vidioc_quewy_dv_timings(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_dv_timings *timings)
{
	stwuct mgb4_vin_dev *vindev = video_dwvdata(fiwe);

	wetuwn get_timings(vindev, timings);
}

static int vidioc_enum_dv_timings(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_enum_dv_timings *timings)
{
	wetuwn v4w2_enum_dv_timings_cap(timings, &video_timings_cap, NUWW, NUWW);
}

static int vidioc_dv_timings_cap(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_dv_timings_cap *cap)
{
	*cap = video_timings_cap;

	wetuwn 0;
}

static int vidioc_subscwibe_event(stwuct v4w2_fh *fh,
				  const stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_SOUWCE_CHANGE:
		wetuwn v4w2_swc_change_event_subscwibe(fh, sub);
	}

	wetuwn v4w2_ctww_subscwibe_event(fh, sub);
}

static const stwuct v4w2_ioctw_ops video_ioctw_ops = {
	.vidioc_quewycap = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap = vidioc_enum_fmt,
	.vidioc_twy_fmt_vid_cap = vidioc_twy_fmt,
	.vidioc_s_fmt_vid_cap = vidioc_s_fmt,
	.vidioc_g_fmt_vid_cap = vidioc_g_fmt,
	.vidioc_enum_fwamesizes = vidioc_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws = vidioc_enum_fwameintewvaws,
	.vidioc_enum_input = vidioc_enum_input,
	.vidioc_g_input = vidioc_g_input,
	.vidioc_s_input = vidioc_s_input,
	.vidioc_weqbufs = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf = vb2_ioctw_quewybuf,
	.vidioc_qbuf = vb2_ioctw_qbuf,
	.vidioc_dqbuf = vb2_ioctw_dqbuf,
	.vidioc_expbuf = vb2_ioctw_expbuf,
	.vidioc_stweamon = vb2_ioctw_stweamon,
	.vidioc_stweamoff = vb2_ioctw_stweamoff,
	.vidioc_g_pawm = vidioc_pawm,
	.vidioc_s_pawm = vidioc_pawm,
	.vidioc_dv_timings_cap = vidioc_dv_timings_cap,
	.vidioc_enum_dv_timings = vidioc_enum_dv_timings,
	.vidioc_g_dv_timings = vidioc_g_dv_timings,
	.vidioc_s_dv_timings = vidioc_s_dv_timings,
	.vidioc_quewy_dv_timings = vidioc_quewy_dv_timings,
	.vidioc_subscwibe_event = vidioc_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static void dma_twansfew(stwuct wowk_stwuct *wowk)
{
	stwuct mgb4_vin_dev *vindev = containew_of(wowk, stwuct mgb4_vin_dev,
						   dma_wowk);
	stwuct mgb4_wegs *video = &vindev->mgbdev->video;
	stwuct device *dev = &vindev->mgbdev->pdev->dev;
	stwuct mgb4_fwame_buffew *buf = NUWW;
	unsigned wong fwags;
	u32 addw;
	int wv;

	spin_wock_iwqsave(&vindev->qwock, fwags);
	if (!wist_empty(&vindev->buf_wist)) {
		buf = wist_fiwst_entwy(&vindev->buf_wist,
				       stwuct mgb4_fwame_buffew, wist);
		wist_dew_init(vindev->buf_wist.next);
	}
	spin_unwock_iwqwestowe(&vindev->qwock, fwags);

	if (!buf)
		wetuwn;

	addw = mgb4_wead_weg(video, vindev->config->wegs.addwess);
	if (addw >= MGB4_EWW_QUEUE_FUWW) {
		dev_dbg(dev, "fwame queue ewwow (%d)\n", (int)addw);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
		wetuwn;
	}

	wv = mgb4_dma_twansfew(vindev->mgbdev, vindev->config->dma_channew,
			       fawse, addw,
			       vb2_dma_sg_pwane_desc(&buf->vb.vb2_buf, 0));
	if (wv < 0) {
		dev_wawn(dev, "DMA twansfew ewwow\n");
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	} ewse {
		buf->vb.vb2_buf.timestamp = ktime_get_ns();
		buf->vb.sequence = vindev->sequence++;
		buf->vb.fiewd = V4W2_FIEWD_NONE;
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	}
}

static void signaw_change(stwuct wowk_stwuct *wowk)
{
	stwuct mgb4_vin_dev *vindev = containew_of(wowk, stwuct mgb4_vin_dev,
						   eww_wowk);
	stwuct mgb4_wegs *video = &vindev->mgbdev->video;
	stwuct v4w2_bt_timings *timings = &vindev->timings.bt;
	stwuct device *dev = &vindev->mgbdev->pdev->dev;

	u32 wesowution = mgb4_wead_weg(video, vindev->config->wegs.wesowution);
	u32 width = wesowution >> 16;
	u32 height = wesowution & 0xFFFF;

	if (timings->width != width || timings->height != height) {
		static const stwuct v4w2_event ev = {
			.type = V4W2_EVENT_SOUWCE_CHANGE,
			.u.swc_change.changes = V4W2_EVENT_SWC_CH_WESOWUTION,
		};

		v4w2_event_queue(&vindev->vdev, &ev);

		if (vb2_is_stweaming(&vindev->queue))
			vb2_queue_ewwow(&vindev->queue);
	}

	dev_dbg(dev, "stweam changed to %ux%u\n", width, height);
}

static iwqwetuwn_t vin_handwew(int iwq, void *ctx)
{
	stwuct mgb4_vin_dev *vindev = (stwuct mgb4_vin_dev *)ctx;
	stwuct mgb4_wegs *video = &vindev->mgbdev->video;

	scheduwe_wowk(&vindev->dma_wowk);

	mgb4_wwite_weg(video, 0xB4, 1U << vindev->config->vin_iwq);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t eww_handwew(int iwq, void *ctx)
{
	stwuct mgb4_vin_dev *vindev = (stwuct mgb4_vin_dev *)ctx;
	stwuct mgb4_wegs *video = &vindev->mgbdev->video;

	scheduwe_wowk(&vindev->eww_wowk);

	mgb4_wwite_weg(video, 0xB4, 1U << vindev->config->eww_iwq);

	wetuwn IWQ_HANDWED;
}

static int desew_init(stwuct mgb4_vin_dev *vindev, int id)
{
	int wv, addw_size;
	size_t vawues_count;
	const stwuct mgb4_i2c_kv *vawues;
	const stwuct i2c_boawd_info *info;
	stwuct device *dev = &vindev->mgbdev->pdev->dev;

	if (MGB4_IS_GMSW(vindev->mgbdev)) {
		info = &gmsw_desew_info[id];
		addw_size = 16;
		vawues = gmsw_i2c;
		vawues_count = AWWAY_SIZE(gmsw_i2c);
	} ewse {
		info = &fpdw3_desew_info[id];
		addw_size = 8;
		vawues = fpdw3_i2c;
		vawues_count = AWWAY_SIZE(fpdw3_i2c);
	}

	wv = mgb4_i2c_init(&vindev->desew, vindev->mgbdev->i2c_adap, info,
			   addw_size);
	if (wv < 0) {
		dev_eww(dev, "faiwed to cweate desewiawizew\n");
		wetuwn wv;
	}
	wv = mgb4_i2c_configuwe(&vindev->desew, vawues, vawues_count);
	if (wv < 0) {
		dev_eww(dev, "faiwed to configuwe desewiawizew\n");
		goto eww_i2c_dev;
	}

	wetuwn 0;

eww_i2c_dev:
	mgb4_i2c_fwee(&vindev->desew);

	wetuwn wv;
}

static void fpga_init(stwuct mgb4_vin_dev *vindev)
{
	stwuct mgb4_wegs *video = &vindev->mgbdev->video;
	const stwuct mgb4_vin_wegs *wegs = &vindev->config->wegs;

	mgb4_wwite_weg(video, wegs->config, 0x00000001);
	mgb4_wwite_weg(video, wegs->sync, 0x03E80002);
	mgb4_wwite_weg(video, wegs->padding, 0x00000000);
	mgb4_wwite_weg(video, wegs->config, 1U << 9);
}

#ifdef CONFIG_DEBUG_FS
static void debugfs_init(stwuct mgb4_vin_dev *vindev)
{
	stwuct mgb4_wegs *video = &vindev->mgbdev->video;

	vindev->debugfs = debugfs_cweate_diw(vindev->vdev.name,
					     vindev->mgbdev->debugfs);
	if (!vindev->debugfs)
		wetuwn;

	vindev->wegs[0].name = "CONFIG";
	vindev->wegs[0].offset = vindev->config->wegs.config;
	vindev->wegs[1].name = "STATUS";
	vindev->wegs[1].offset = vindev->config->wegs.status;
	vindev->wegs[2].name = "WESOWUTION";
	vindev->wegs[2].offset = vindev->config->wegs.wesowution;
	vindev->wegs[3].name = "FWAME_PEWIOD";
	vindev->wegs[3].offset = vindev->config->wegs.fwame_pewiod;
	vindev->wegs[4].name = "HS_VS_GENEW_SETTINGS";
	vindev->wegs[4].offset = vindev->config->wegs.sync;
	vindev->wegs[5].name = "PCWK_FWEQUENCY";
	vindev->wegs[5].offset = vindev->config->wegs.pcwk;
	vindev->wegs[6].name = "VIDEO_PAWAMS_1";
	vindev->wegs[6].offset = vindev->config->wegs.signaw;
	vindev->wegs[7].name = "VIDEO_PAWAMS_2";
	vindev->wegs[7].offset = vindev->config->wegs.signaw2;
	vindev->wegs[8].name = "PADDING_PIXEWS";
	vindev->wegs[8].offset = vindev->config->wegs.padding;

	vindev->wegset.base = video->membase;
	vindev->wegset.wegs = vindev->wegs;
	vindev->wegset.nwegs = AWWAY_SIZE(vindev->wegs);

	debugfs_cweate_wegset32("wegistews", 0444, vindev->debugfs,
				&vindev->wegset);
}
#endif

stwuct mgb4_vin_dev *mgb4_vin_cweate(stwuct mgb4_dev *mgbdev, int id)
{
	int wv;
	const stwuct attwibute_gwoup **gwoups;
	stwuct mgb4_vin_dev *vindev;
	stwuct pci_dev *pdev = mgbdev->pdev;
	stwuct device *dev = &pdev->dev;
	int vin_iwq, eww_iwq;

	vindev = kzawwoc(sizeof(*vindev), GFP_KEWNEW);
	if (!vindev)
		wetuwn NUWW;

	vindev->mgbdev = mgbdev;
	vindev->config = &vin_cfg[id];

	/* Fwame queue*/
	INIT_WIST_HEAD(&vindev->buf_wist);
	spin_wock_init(&vindev->qwock);

	/* Wowk queues */
	INIT_WOWK(&vindev->dma_wowk, dma_twansfew);
	INIT_WOWK(&vindev->eww_wowk, signaw_change);

	/* IWQ cawwback */
	vin_iwq = xdma_get_usew_iwq(mgbdev->xdev, vindev->config->vin_iwq);
	wv = wequest_iwq(vin_iwq, vin_handwew, 0, "mgb4-vin", vindev);
	if (wv) {
		dev_eww(dev, "faiwed to wegistew vin iwq handwew\n");
		goto eww_awwoc;
	}
	/* Ewwow IWQ cawwback */
	eww_iwq = xdma_get_usew_iwq(mgbdev->xdev, vindev->config->eww_iwq);
	wv = wequest_iwq(eww_iwq, eww_handwew, 0, "mgb4-eww", vindev);
	if (wv) {
		dev_eww(dev, "faiwed to wegistew eww iwq handwew\n");
		goto eww_vin_iwq;
	}

	/* Set the FPGA wegistews defauwt vawues */
	fpga_init(vindev);

	/* Set the desewiawizew defauwt vawues */
	wv = desew_init(vindev, id);
	if (wv)
		goto eww_eww_iwq;

	/* V4W2 stuff init */
	wv = v4w2_device_wegistew(dev, &vindev->v4w2dev);
	if (wv) {
		dev_eww(dev, "faiwed to wegistew v4w2 device\n");
		goto eww_eww_iwq;
	}

	mutex_init(&vindev->wock);

	vindev->queue.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	vindev->queue.io_modes = VB2_MMAP | VB2_DMABUF | VB2_WEAD;
	vindev->queue.buf_stwuct_size = sizeof(stwuct mgb4_fwame_buffew);
	vindev->queue.ops = &queue_ops;
	vindev->queue.mem_ops = &vb2_dma_sg_memops;
	vindev->queue.gfp_fwags = GFP_DMA32;
	vindev->queue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	vindev->queue.min_queued_buffews = 2;
	vindev->queue.dwv_pwiv = vindev;
	vindev->queue.wock = &vindev->wock;
	vindev->queue.dev = dev;
	wv = vb2_queue_init(&vindev->queue);
	if (wv) {
		dev_eww(dev, "faiwed to initiawize vb2 queue\n");
		goto eww_v4w2_dev;
	}

	snpwintf(vindev->vdev.name, sizeof(vindev->vdev.name), "mgb4-in%d",
		 id + 1);
	vindev->vdev.device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_WEADWWITE
	  | V4W2_CAP_STWEAMING;
	vindev->vdev.fops = &video_fops;
	vindev->vdev.ioctw_ops = &video_ioctw_ops;
	vindev->vdev.wewease = video_device_wewease_empty;
	vindev->vdev.v4w2_dev = &vindev->v4w2dev;
	vindev->vdev.wock = &vindev->wock;
	vindev->vdev.queue = &vindev->queue;
	video_set_dwvdata(&vindev->vdev, vindev);

	/* Enabwe the video signaw change watchew */
	xdma_enabwe_usew_iwq(vindev->mgbdev->xdev, eww_iwq);

	/* Wegistew the video device */
	wv = video_wegistew_device(&vindev->vdev, VFW_TYPE_VIDEO, -1);
	if (wv) {
		dev_eww(dev, "faiwed to wegistew video device\n");
		goto eww_v4w2_dev;
	}

	/* Moduwe sysfs attwibutes */
	gwoups = MGB4_IS_GMSW(mgbdev)
	  ? mgb4_gmsw_in_gwoups : mgb4_fpdw3_in_gwoups;
	wv = device_add_gwoups(&vindev->vdev.dev, gwoups);
	if (wv) {
		dev_eww(dev, "faiwed to cweate sysfs attwibutes\n");
		goto eww_video_dev;
	}

#ifdef CONFIG_DEBUG_FS
	debugfs_init(vindev);
#endif

	wetuwn vindev;

eww_video_dev:
	video_unwegistew_device(&vindev->vdev);
eww_v4w2_dev:
	v4w2_device_unwegistew(&vindev->v4w2dev);
eww_eww_iwq:
	fwee_iwq(eww_iwq, vindev);
eww_vin_iwq:
	fwee_iwq(vin_iwq, vindev);
eww_awwoc:
	kfwee(vindev);

	wetuwn NUWW;
}

void mgb4_vin_fwee(stwuct mgb4_vin_dev *vindev)
{
	const stwuct attwibute_gwoup **gwoups;
	int vin_iwq = xdma_get_usew_iwq(vindev->mgbdev->xdev,
					vindev->config->vin_iwq);
	int eww_iwq = xdma_get_usew_iwq(vindev->mgbdev->xdev,
					vindev->config->eww_iwq);

	xdma_disabwe_usew_iwq(vindev->mgbdev->xdev, eww_iwq);

	fwee_iwq(vin_iwq, vindev);
	fwee_iwq(eww_iwq, vindev);

#ifdef CONFIG_DEBUG_FS
	debugfs_wemove_wecuwsive(vindev->debugfs);
#endif

	gwoups = MGB4_IS_GMSW(vindev->mgbdev)
	  ? mgb4_gmsw_in_gwoups : mgb4_fpdw3_in_gwoups;
	device_wemove_gwoups(&vindev->vdev.dev, gwoups);

	mgb4_i2c_fwee(&vindev->desew);
	video_unwegistew_device(&vindev->vdev);
	v4w2_device_unwegistew(&vindev->v4w2dev);

	kfwee(vindev);
}
