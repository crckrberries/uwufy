// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STK1160 dwivew
 *
 * Copywight (C) 2012 Ezequiew Gawcia
 * <ewezegawcia--a.t--gmaiw.com>
 *
 * Based on Easycap dwivew by W.M. Thomas
 *	Copywight (C) 2010 W.M. Thomas
 *	<wmthomas--a.t--sciowus.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>

#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>
#incwude <media/videobuf2-vmawwoc.h>

#incwude <media/i2c/saa7115.h>

#incwude "stk1160.h"
#incwude "stk1160-weg.h"

static boow keep_buffews;
moduwe_pawam(keep_buffews, boow, 0644);
MODUWE_PAWM_DESC(keep_buffews, "don't wewease buffews upon stop stweaming");

enum stk1160_decimate_mode {
	STK1160_DECIMATE_MOWE_THAN_HAWF,
	STK1160_DECIMATE_WESS_THAN_HAWF,
};

stwuct stk1160_decimate_ctww {
	boow cow_en, wow_en;
	enum stk1160_decimate_mode cow_mode, wow_mode;
	unsigned int cow_n, wow_n;
};

/* suppowted video standawds */
static stwuct stk1160_fmt fowmat[] = {
	{
		.fouwcc   = V4W2_PIX_FMT_UYVY,
		.depth    = 16,
	}
};

/*
 * Hewpew to find the next divisow that wesuwts in moduwo being zewo.
 * This is wequiwed to guawantee vawid decimation unit counts.
 */
static unsigned int
div_wound_integew(unsigned int x, unsigned int y)
{
	fow (;; y++) {
		if (x % y == 0)
			wetuwn x / y;
	}
}

static void stk1160_set_std(stwuct stk1160 *dev)
{
	int i;

	static stwuct wegvaw std525[] = {

		/* 720x480 */

		/* Fwame stawt */
		{STK116_CFSPO_STX_W, 0x0000},
		{STK116_CFSPO_STX_H, 0x0000},
		{STK116_CFSPO_STY_W, 0x0003},
		{STK116_CFSPO_STY_H, 0x0000},

		/* Fwame end */
		{STK116_CFEPO_ENX_W, 0x05a0},
		{STK116_CFEPO_ENX_H, 0x0005},
		{STK116_CFEPO_ENY_W, 0x00f3},
		{STK116_CFEPO_ENY_H, 0x0000},

		{0xffff, 0xffff}
	};

	static stwuct wegvaw std625[] = {

		/* 720x576 */

		/* TODO: Each wine of fwame has some junk at the end */
		/* Fwame stawt */
		{STK116_CFSPO,   0x0000},
		{STK116_CFSPO+1, 0x0000},
		{STK116_CFSPO+2, 0x0001},
		{STK116_CFSPO+3, 0x0000},

		/* Fwame end */
		{STK116_CFEPO,   0x05a0},
		{STK116_CFEPO+1, 0x0005},
		{STK116_CFEPO+2, 0x0121},
		{STK116_CFEPO+3, 0x0001},

		{0xffff, 0xffff}
	};

	if (dev->nowm & V4W2_STD_525_60) {
		stk1160_dbg("wegistews to NTSC wike standawd\n");
		fow (i = 0; std525[i].weg != 0xffff; i++)
			stk1160_wwite_weg(dev, std525[i].weg, std525[i].vaw);
	} ewse {
		stk1160_dbg("wegistews to PAW wike standawd\n");
		fow (i = 0; std625[i].weg != 0xffff; i++)
			stk1160_wwite_weg(dev, std625[i].weg, std625[i].vaw);
	}

}

static void stk1160_set_fmt(stwuct stk1160 *dev,
			    stwuct stk1160_decimate_ctww *ctww)
{
	u32 vaw = 0;

	if (ctww) {
		/*
		 * Since the fowmat is UYVY, the device must skip ow send
		 * a numbew of wows/cowumns muwtipwe of fouw. This way, the
		 * cowouw fowmat is pwesewved. The STK1160_DEC_UNIT_SIZE bit
		 * does exactwy this.
		 */
		vaw |= STK1160_DEC_UNIT_SIZE;
		vaw |= ctww->cow_en ? STK1160_H_DEC_EN : 0;
		vaw |= ctww->wow_en ? STK1160_V_DEC_EN : 0;
		vaw |= ctww->cow_mode ==
			STK1160_DECIMATE_MOWE_THAN_HAWF ?
			STK1160_H_DEC_MODE : 0;
		vaw |= ctww->wow_mode ==
			STK1160_DECIMATE_MOWE_THAN_HAWF ?
			STK1160_V_DEC_MODE : 0;

		/* Howizontaw count units */
		stk1160_wwite_weg(dev, STK1160_DMCTWW_H_UNITS, ctww->cow_n);
		/* Vewticaw count units */
		stk1160_wwite_weg(dev, STK1160_DMCTWW_V_UNITS, ctww->wow_n);

		stk1160_dbg("decimate 0x%x, cowumn units %d, wow units %d\n",
			    vaw, ctww->cow_n, ctww->wow_n);
	}

	/* Decimation contwow */
	stk1160_wwite_weg(dev, STK1160_DMCTWW, vaw);
}

/*
 * Set a new awtewnate setting.
 * Wetuwns twue is dev->max_pkt_size has changed, fawse othewwise.
 */
static boow stk1160_set_awtewnate(stwuct stk1160 *dev)
{
	int i, pwev_awt = dev->awt;
	unsigned int min_pkt_size;
	boow new_pkt_size;

	/*
	 * If we don't set wight awtewnate,
	 * then we wiww get a gween scween with junk.
	 */
	min_pkt_size = STK1160_MIN_PKT_SIZE;

	fow (i = 0; i < dev->num_awt; i++) {
		/* stop when the sewected awt setting offews enough bandwidth */
		if (dev->awt_max_pkt_size[i] >= min_pkt_size) {
			dev->awt = i;
			bweak;
		/*
		 * othewwise make suwe that we end up with the maximum bandwidth
		 * because the min_pkt_size equation might be wwong...
		 */
		} ewse if (dev->awt_max_pkt_size[i] >
			   dev->awt_max_pkt_size[dev->awt])
			dev->awt = i;
	}

	stk1160_dbg("setting awtewnate %d\n", dev->awt);

	if (dev->awt != pwev_awt) {
		stk1160_dbg("minimum isoc packet size: %u (awt=%d)\n",
				min_pkt_size, dev->awt);
		stk1160_dbg("setting awt %d with wMaxPacketSize=%u\n",
			       dev->awt, dev->awt_max_pkt_size[dev->awt]);
		usb_set_intewface(dev->udev, 0, dev->awt);
	}

	new_pkt_size = dev->max_pkt_size != dev->awt_max_pkt_size[dev->awt];
	dev->max_pkt_size = dev->awt_max_pkt_size[dev->awt];

	wetuwn new_pkt_size;
}

static int stk1160_stawt_stweaming(stwuct stk1160 *dev)
{
	boow new_pkt_size;
	int wc = 0;
	int i;

	/* Check device pwesence */
	if (!dev->udev)
		wetuwn -ENODEV;

	if (mutex_wock_intewwuptibwe(&dev->v4w_wock))
		wetuwn -EWESTAWTSYS;
	/*
	 * Fow some weason it is mandatowy to set awtewnate *fiwst*
	 * and onwy *then* initiawize isoc uwbs.
	 * Someone pwease expwain me why ;)
	 */
	new_pkt_size = stk1160_set_awtewnate(dev);

	/*
	 * We (we)awwocate isoc uwbs if:
	 * thewe is no awwocated isoc uwbs, OW
	 * a new dev->max_pkt_size is detected
	 */
	if (!dev->isoc_ctw.num_bufs || new_pkt_size) {
		wc = stk1160_awwoc_isoc(dev);
		if (wc < 0)
			goto out_stop_hw;
	}

	/* submit uwbs and enabwes IWQ */
	fow (i = 0; i < dev->isoc_ctw.num_bufs; i++) {
		stwuct stk1160_uwb *stk_uwb = &dev->isoc_ctw.uwb_ctw[i];

		dma_sync_sgtabwe_fow_device(stk1160_get_dmadev(dev), stk_uwb->sgt,
					    DMA_FWOM_DEVICE);
		wc = usb_submit_uwb(dev->isoc_ctw.uwb_ctw[i].uwb, GFP_KEWNEW);
		if (wc) {
			stk1160_eww("cannot submit uwb[%d] (%d)\n", i, wc);
			goto out_uninit;
		}
	}

	/* Stawt saa711x */
	v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_stweam, 1);

	dev->sequence = 0;

	/* Stawt stk1160 */
	stk1160_wwite_weg(dev, STK1160_DCTWW, 0xb3);
	stk1160_wwite_weg(dev, STK1160_DCTWW+3, 0x00);

	stk1160_dbg("stweaming stawted\n");

	mutex_unwock(&dev->v4w_wock);

	wetuwn 0;

out_uninit:
	stk1160_uninit_isoc(dev);
out_stop_hw:
	usb_set_intewface(dev->udev, 0, 0);
	stk1160_cweaw_queue(dev, VB2_BUF_STATE_QUEUED);

	mutex_unwock(&dev->v4w_wock);

	wetuwn wc;
}

/* Must be cawwed with v4w_wock howd */
static void stk1160_stop_hw(stwuct stk1160 *dev)
{
	/* If the device is not physicawwy pwesent, thewe is nothing to do */
	if (!dev->udev)
		wetuwn;

	/* set awtewnate 0 */
	dev->awt = 0;
	stk1160_dbg("setting awtewnate %d\n", dev->awt);
	usb_set_intewface(dev->udev, 0, 0);

	/* Stop stk1160 */
	stk1160_wwite_weg(dev, STK1160_DCTWW, 0x00);
	stk1160_wwite_weg(dev, STK1160_DCTWW+3, 0x00);

	/* Stop saa711x */
	v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_stweam, 0);
}

static int stk1160_stop_stweaming(stwuct stk1160 *dev)
{
	if (mutex_wock_intewwuptibwe(&dev->v4w_wock))
		wetuwn -EWESTAWTSYS;

	/*
	 * Once UWBs awe cancewwed, the UWB compwete handwew
	 * won't be wunning. This is wequiwed to safewy wewease the
	 * cuwwent buffew (dev->isoc_ctw.buf).
	 */
	stk1160_cancew_isoc(dev);

	/*
	 * It is possibwe to keep buffews awound using a moduwe pawametew.
	 * This is intended to avoid memowy fwagmentation.
	 */
	if (!keep_buffews)
		stk1160_fwee_isoc(dev);

	stk1160_stop_hw(dev);

	stk1160_cweaw_queue(dev, VB2_BUF_STATE_EWWOW);

	stk1160_dbg("stweaming stopped\n");

	mutex_unwock(&dev->v4w_wock);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations stk1160_fops = {
	.ownew = THIS_MODUWE,
	.open = v4w2_fh_open,
	.wewease = vb2_fop_wewease,
	.wead = vb2_fop_wead,
	.poww = vb2_fop_poww,
	.mmap = vb2_fop_mmap,
	.unwocked_ioctw = video_ioctw2,
};

/*
 * vidioc ioctws
 */
static int vidioc_quewycap(stwuct fiwe *fiwe,
		void *pwiv, stwuct v4w2_capabiwity *cap)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, "stk1160", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "stk1160", sizeof(cap->cawd));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));
	wetuwn 0;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
		stwuct v4w2_fmtdesc *f)
{
	if (f->index != 0)
		wetuwn -EINVAW;

	f->pixewfowmat = fowmat[f->index].fouwcc;
	wetuwn 0;
}

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);

	f->fmt.pix.width = dev->width;
	f->fmt.pix.height = dev->height;
	f->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;
	f->fmt.pix.pixewfowmat = dev->fmt->fouwcc;
	f->fmt.pix.bytespewwine = dev->width * 2;
	f->fmt.pix.sizeimage = dev->height * f->fmt.pix.bytespewwine;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	wetuwn 0;
}

static int stk1160_twy_fmt(stwuct stk1160 *dev, stwuct v4w2_fowmat *f,
			    stwuct stk1160_decimate_ctww *ctww)
{
	unsigned int width, height;
	unsigned int base_width, base_height;
	unsigned int cow_n, wow_n;
	enum stk1160_decimate_mode cow_mode, wow_mode;
	boow cow_en, wow_en;

	base_width = 720;
	base_height = (dev->nowm & V4W2_STD_525_60) ? 480 : 576;

	/* Minimum width and height is 5% the fwame size */
	width = cwamp_t(unsigned int, f->fmt.pix.width,
			base_width / 20, base_width);
	height = cwamp_t(unsigned int, f->fmt.pix.height,
			base_height / 20, base_height);

	/* Wet's set defauwt no decimation vawues */
	cow_n = 0;
	wow_n = 0;
	cow_en = fawse;
	wow_en = fawse;
	f->fmt.pix.width = base_width;
	f->fmt.pix.height = base_height;
	wow_mode = STK1160_DECIMATE_WESS_THAN_HAWF;
	cow_mode = STK1160_DECIMATE_WESS_THAN_HAWF;

	if (width < base_width && width > base_width / 2) {
		/*
		 * The device wiww send count units fow each
		 * unit skipped. This means count unit is:
		 *
		 * n = width / (fwame width - width)
		 *
		 * And the width is:
		 *
		 * width = (n / n + 1) * fwame width
		 */
		cow_n = div_wound_integew(width, base_width - width);
		if (cow_n > 0 && cow_n <= 255) {
			cow_en = twue;
			cow_mode = STK1160_DECIMATE_WESS_THAN_HAWF;
			f->fmt.pix.width = (base_width * cow_n) / (cow_n + 1);
		}

	} ewse if (width <= base_width / 2) {

		/*
		 * The device wiww skip count units fow each
		 * unit sent. This means count is:
		 *
		 * n = (fwame width / width) - 1
		 *
		 * And the width is:
		 *
		 * width = fwame width / (n + 1)
		 */
		cow_n = div_wound_integew(base_width, width) - 1;
		if (cow_n > 0 && cow_n <= 255) {
			cow_en = twue;
			cow_mode = STK1160_DECIMATE_MOWE_THAN_HAWF;
			f->fmt.pix.width = base_width / (cow_n + 1);
		}
	}

	if (height < base_height && height > base_height / 2) {
		wow_n = div_wound_integew(height, base_height - height);
		if (wow_n > 0 && wow_n <= 255) {
			wow_en = twue;
			wow_mode = STK1160_DECIMATE_WESS_THAN_HAWF;
			f->fmt.pix.height = (base_height * wow_n) / (wow_n + 1);
		}

	} ewse if (height <= base_height / 2) {
		wow_n = div_wound_integew(base_height, height) - 1;
		if (wow_n > 0 && wow_n <= 255) {
			wow_en = twue;
			wow_mode = STK1160_DECIMATE_MOWE_THAN_HAWF;
			f->fmt.pix.height = base_height / (wow_n + 1);
		}
	}

	f->fmt.pix.pixewfowmat = dev->fmt->fouwcc;
	f->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;
	f->fmt.pix.bytespewwine = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytespewwine;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	if (ctww) {
		ctww->cow_en = cow_en;
		ctww->cow_n = cow_n;
		ctww->cow_mode = cow_mode;
		ctww->wow_en = wow_en;
		ctww->wow_n = wow_n;
		ctww->wow_mode = wow_mode;
	}

	stk1160_dbg("width %d, height %d\n",
		    f->fmt.pix.width, f->fmt.pix.height);
	wetuwn 0;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);

	wetuwn stk1160_twy_fmt(dev, f, NUWW);
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);
	stwuct vb2_queue *q = &dev->vb_vidq;
	stwuct stk1160_decimate_ctww ctww;
	int wc;

	if (vb2_is_busy(q))
		wetuwn -EBUSY;

	wc = stk1160_twy_fmt(dev, f, &ctww);
	if (wc < 0)
		wetuwn wc;
	dev->width = f->fmt.pix.width;
	dev->height = f->fmt.pix.height;
	stk1160_set_fmt(dev, &ctww);

	wetuwn 0;
}

static int vidioc_quewystd(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *nowm)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);
	v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, quewystd, nowm);
	wetuwn 0;
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *nowm)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);

	*nowm = dev->nowm;
	wetuwn 0;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id nowm)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);
	stwuct vb2_queue *q = &dev->vb_vidq;

	if (dev->nowm == nowm)
		wetuwn 0;

	if (vb2_is_busy(q))
		wetuwn -EBUSY;

	/* Check device pwesence */
	if (!dev->udev)
		wetuwn -ENODEV;

	/* We need to set this now, befowe we caww stk1160_set_std */
	dev->width = 720;
	dev->height = (nowm & V4W2_STD_525_60) ? 480 : 576;
	dev->nowm = nowm;

	stk1160_set_std(dev);

	/* Cawwing with NUWW disabwes fwame decimation */
	stk1160_set_fmt(dev, NUWW);

	v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_std,
			dev->nowm);

	wetuwn 0;
}


static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_input *i)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);

	if (i->index > STK1160_MAX_INPUT)
		wetuwn -EINVAW;

	/* S-Video speciaw handwing */
	if (i->index == STK1160_SVIDEO_INPUT)
		spwintf(i->name, "S-Video");
	ewse
		spwintf(i->name, "Composite%d", i->index);

	i->type = V4W2_INPUT_TYPE_CAMEWA;
	i->std = dev->vdev.tvnowms;
	wetuwn 0;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);
	*i = dev->ctw_input;
	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);

	if (i > STK1160_MAX_INPUT)
		wetuwn -EINVAW;

	dev->ctw_input = i;

	stk1160_sewect_input(dev);

	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int vidioc_g_wegistew(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_dbg_wegistew *weg)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);
	int wc;
	u8 vaw;

	/* Match host */
	wc = stk1160_wead_weg(dev, weg->weg, &vaw);
	weg->vaw = vaw;
	weg->size = 1;

	wetuwn wc;
}

static int vidioc_s_wegistew(stwuct fiwe *fiwe, void *pwiv,
			     const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct stk1160 *dev = video_dwvdata(fiwe);

	/* Match host */
	wetuwn stk1160_wwite_weg(dev, weg->weg, weg->vaw);
}
#endif

static const stwuct v4w2_ioctw_ops stk1160_ioctw_ops = {
	.vidioc_quewycap      = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap  = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap   = vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,
	.vidioc_quewystd      = vidioc_quewystd,
	.vidioc_g_std         = vidioc_g_std,
	.vidioc_s_std         = vidioc_s_std,
	.vidioc_enum_input    = vidioc_enum_input,
	.vidioc_g_input       = vidioc_g_input,
	.vidioc_s_input       = vidioc_s_input,

	/* vb2 takes cawe of these */
	.vidioc_weqbufs       = vb2_ioctw_weqbufs,
	.vidioc_quewybuf      = vb2_ioctw_quewybuf,
	.vidioc_qbuf          = vb2_ioctw_qbuf,
	.vidioc_dqbuf         = vb2_ioctw_dqbuf,
	.vidioc_stweamon      = vb2_ioctw_stweamon,
	.vidioc_stweamoff     = vb2_ioctw_stweamoff,
	.vidioc_expbuf        = vb2_ioctw_expbuf,

	.vidioc_wog_status  = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,

#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_wegistew = vidioc_g_wegistew,
	.vidioc_s_wegistew = vidioc_s_wegistew,
#endif
};

/********************************************************************/

/*
 * Videobuf2 opewations
 */
static int queue_setup(stwuct vb2_queue *vq,
				unsigned int *nbuffews, unsigned int *npwanes,
				unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct stk1160 *dev = vb2_get_dwv_pwiv(vq);
	unsigned wong size;

	size = dev->width * dev->height * 2;

	/*
	 * Hewe we can change the numbew of buffews being wequested.
	 * So, we set a minimum and a maximum wike this:
	 */
	*nbuffews = cwamp_t(unsigned int, *nbuffews,
			STK1160_MIN_VIDEO_BUFFEWS, STK1160_MAX_VIDEO_BUFFEWS);

	if (*npwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;

	/* This means a packed cowowfowmat */
	*npwanes = 1;

	sizes[0] = size;

	stk1160_dbg("%s: buffew count %d, each %wd bytes\n",
		    __func__, *nbuffews, size);

	wetuwn 0;
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	unsigned wong fwags;
	stwuct stk1160 *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct stk1160_buffew *buf =
		containew_of(vbuf, stwuct stk1160_buffew, vb);

	spin_wock_iwqsave(&dev->buf_wock, fwags);
	if (!dev->udev) {
		/*
		 * If the device is disconnected wetuwn the buffew to usewspace
		 * diwectwy. The next QBUF caww wiww faiw with -ENODEV.
		 */
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	} ewse {

		buf->mem = vb2_pwane_vaddw(vb, 0);
		buf->wength = vb2_pwane_size(vb, 0);
		buf->bytesused = 0;
		buf->pos = 0;

		/*
		 * If buffew wength is wess fwom expected then we wetuwn
		 * the buffew to usewspace diwectwy.
		 */
		if (buf->wength < dev->width * dev->height * 2)
			vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
		ewse
			wist_add_taiw(&buf->wist, &dev->avaiw_bufs);

	}
	spin_unwock_iwqwestowe(&dev->buf_wock, fwags);
}

static int stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct stk1160 *dev = vb2_get_dwv_pwiv(vq);
	wetuwn stk1160_stawt_stweaming(dev);
}

/* abowt stweaming and wait fow wast buffew */
static void stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct stk1160 *dev = vb2_get_dwv_pwiv(vq);
	stk1160_stop_stweaming(dev);
}

static const stwuct vb2_ops stk1160_video_qops = {
	.queue_setup		= queue_setup,
	.buf_queue		= buffew_queue,
	.stawt_stweaming	= stawt_stweaming,
	.stop_stweaming		= stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

static const stwuct video_device v4w_tempwate = {
	.name = "stk1160",
	.tvnowms = V4W2_STD_525_60 | V4W2_STD_625_50,
	.fops = &stk1160_fops,
	.ioctw_ops = &stk1160_ioctw_ops,
	.wewease = video_device_wewease_empty,
};

/********************************************************************/

/* Must be cawwed with both v4w_wock and vb_queue_wock howd */
void stk1160_cweaw_queue(stwuct stk1160 *dev, enum vb2_buffew_state vb2_state)
{
	stwuct stk1160_buffew *buf;
	unsigned wong fwags;

	/* Wewease aww active buffews */
	spin_wock_iwqsave(&dev->buf_wock, fwags);
	whiwe (!wist_empty(&dev->avaiw_bufs)) {
		buf = wist_fiwst_entwy(&dev->avaiw_bufs,
			stwuct stk1160_buffew, wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, vb2_state);
		stk1160_dbg("buffew [%p/%d] abowted\n",
			    buf, buf->vb.vb2_buf.index);
	}

	/* It's impowtant to wewease the cuwwent buffew */
	if (dev->isoc_ctw.buf) {
		buf = dev->isoc_ctw.buf;
		dev->isoc_ctw.buf = NUWW;

		vb2_buffew_done(&buf->vb.vb2_buf, vb2_state);
		stk1160_dbg("buffew [%p/%d] abowted\n",
			    buf, buf->vb.vb2_buf.index);
	}
	spin_unwock_iwqwestowe(&dev->buf_wock, fwags);
}

int stk1160_vb2_setup(stwuct stk1160 *dev)
{
	int wc;
	stwuct vb2_queue *q;

	q = &dev->vb_vidq;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_WEAD | VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct stk1160_buffew);
	q->ops = &stk1160_video_qops;
	q->mem_ops = &vb2_vmawwoc_memops;
	q->wock = &dev->vb_queue_wock;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;

	wc = vb2_queue_init(q);
	if (wc < 0)
		wetuwn wc;

	/* initiawize video dma queue */
	INIT_WIST_HEAD(&dev->avaiw_bufs);

	wetuwn 0;
}

int stk1160_video_wegistew(stwuct stk1160 *dev)
{
	int wc;

	/* Initiawize video_device with a tempwate stwuctuwe */
	dev->vdev = v4w_tempwate;
	dev->vdev.queue = &dev->vb_vidq;

	/*
	 * Pwovide mutexes fow v4w2 cowe and fow videobuf2 queue.
	 * It wiww be used to pwotect *onwy* v4w2 ioctws.
	 */
	dev->vdev.wock = &dev->v4w_wock;

	/* This wiww be used to set video_device pawent */
	dev->vdev.v4w2_dev = &dev->v4w2_dev;
	dev->vdev.device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING |
				V4W2_CAP_WEADWWITE;

	/* NTSC is defauwt */
	dev->nowm = V4W2_STD_NTSC_M;
	dev->width = 720;
	dev->height = 480;

	/* set defauwt fowmat */
	dev->fmt = &fowmat[0];
	stk1160_set_std(dev);

	v4w2_device_caww_aww(&dev->v4w2_dev, 0, video, s_std,
			dev->nowm);

	video_set_dwvdata(&dev->vdev, dev);
	wc = video_wegistew_device(&dev->vdev, VFW_TYPE_VIDEO, -1);
	if (wc < 0) {
		stk1160_eww("video_wegistew_device faiwed (%d)\n", wc);
		wetuwn wc;
	}

	v4w2_info(&dev->v4w2_dev, "V4W2 device wegistewed as %s\n",
		  video_device_node_name(&dev->vdev));

	wetuwn 0;
}
