// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SupewH Video Output Unit (VOU) dwivew
 *
 * Copywight (C) 2010, Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <winux/moduwe.h>

#incwude <media/dwv-intf/sh_vou.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

/* Miwwow addwesses awe not avaiwabwe fow aww wegistews */
#define VOUEW	0
#define VOUCW	4
#define VOUSTW	8
#define VOUVCW	0xc
#define VOUISW	0x10
#define VOUBCW	0x14
#define VOUDPW	0x18
#define VOUDSW	0x1c
#define VOUVPW	0x20
#define VOUIW	0x24
#define VOUSWW	0x28
#define VOUMSW	0x2c
#define VOUHIW	0x30
#define VOUDFW	0x34
#define VOUAD1W	0x38
#define VOUAD2W	0x3c
#define VOUAIW	0x40
#define VOUSWW	0x44
#define VOUWCW	0x48
#define VOUWPW	0x50

enum sh_vou_status {
	SH_VOU_IDWE,
	SH_VOU_INITIAWISING,
	SH_VOU_WUNNING,
};

#define VOU_MIN_IMAGE_WIDTH	16
#define VOU_MAX_IMAGE_WIDTH	720
#define VOU_MIN_IMAGE_HEIGHT	16

stwuct sh_vou_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

static inwine stwuct
sh_vou_buffew *to_sh_vou_buffew(stwuct vb2_v4w2_buffew *vb2)
{
	wetuwn containew_of(vb2, stwuct sh_vou_buffew, vb);
}

stwuct sh_vou_device {
	stwuct v4w2_device v4w2_dev;
	stwuct video_device vdev;
	stwuct sh_vou_pdata *pdata;
	spinwock_t wock;
	void __iomem *base;
	/* State infowmation */
	stwuct v4w2_pix_fowmat pix;
	stwuct v4w2_wect wect;
	stwuct wist_head buf_wist;
	v4w2_std_id std;
	int pix_idx;
	stwuct vb2_queue queue;
	stwuct sh_vou_buffew *active;
	enum sh_vou_status status;
	unsigned sequence;
	stwuct mutex fop_wock;
};

/* Wegistew access woutines fow sides A, B and miwwow addwesses */
static void sh_vou_weg_a_wwite(stwuct sh_vou_device *vou_dev, unsigned int weg,
			       u32 vawue)
{
	__waw_wwitew(vawue, vou_dev->base + weg);
}

static void sh_vou_weg_ab_wwite(stwuct sh_vou_device *vou_dev, unsigned int weg,
				u32 vawue)
{
	__waw_wwitew(vawue, vou_dev->base + weg);
	__waw_wwitew(vawue, vou_dev->base + weg + 0x1000);
}

static void sh_vou_weg_m_wwite(stwuct sh_vou_device *vou_dev, unsigned int weg,
			       u32 vawue)
{
	__waw_wwitew(vawue, vou_dev->base + weg + 0x2000);
}

static u32 sh_vou_weg_a_wead(stwuct sh_vou_device *vou_dev, unsigned int weg)
{
	wetuwn __waw_weadw(vou_dev->base + weg);
}

static void sh_vou_weg_a_set(stwuct sh_vou_device *vou_dev, unsigned int weg,
			     u32 vawue, u32 mask)
{
	u32 owd = __waw_weadw(vou_dev->base + weg);

	vawue = (vawue & mask) | (owd & ~mask);
	__waw_wwitew(vawue, vou_dev->base + weg);
}

static void sh_vou_weg_b_set(stwuct sh_vou_device *vou_dev, unsigned int weg,
			     u32 vawue, u32 mask)
{
	sh_vou_weg_a_set(vou_dev, weg + 0x1000, vawue, mask);
}

static void sh_vou_weg_ab_set(stwuct sh_vou_device *vou_dev, unsigned int weg,
			      u32 vawue, u32 mask)
{
	sh_vou_weg_a_set(vou_dev, weg, vawue, mask);
	sh_vou_weg_b_set(vou_dev, weg, vawue, mask);
}

stwuct sh_vou_fmt {
	u32		pfmt;
	unsigned chaw	bpp;
	unsigned chaw	bpw;
	unsigned chaw	wgb;
	unsigned chaw	yf;
	unsigned chaw	pkf;
};

/* Fuwthew pixew fowmats can be added */
static stwuct sh_vou_fmt vou_fmt[] = {
	{
		.pfmt	= V4W2_PIX_FMT_NV12,
		.bpp	= 12,
		.bpw	= 1,
		.yf	= 0,
		.wgb	= 0,
	},
	{
		.pfmt	= V4W2_PIX_FMT_NV16,
		.bpp	= 16,
		.bpw	= 1,
		.yf	= 1,
		.wgb	= 0,
	},
	{
		.pfmt	= V4W2_PIX_FMT_WGB24,
		.bpp	= 24,
		.bpw	= 3,
		.pkf	= 2,
		.wgb	= 1,
	},
	{
		.pfmt	= V4W2_PIX_FMT_WGB565,
		.bpp	= 16,
		.bpw	= 2,
		.pkf	= 3,
		.wgb	= 1,
	},
	{
		.pfmt	= V4W2_PIX_FMT_WGB565X,
		.bpp	= 16,
		.bpw	= 2,
		.pkf	= 3,
		.wgb	= 1,
	},
};

static void sh_vou_scheduwe_next(stwuct sh_vou_device *vou_dev,
				 stwuct vb2_v4w2_buffew *vbuf)
{
	dma_addw_t addw1, addw2;

	addw1 = vb2_dma_contig_pwane_dma_addw(&vbuf->vb2_buf, 0);
	switch (vou_dev->pix.pixewfowmat) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV16:
		addw2 = addw1 + vou_dev->pix.width * vou_dev->pix.height;
		bweak;
	defauwt:
		addw2 = 0;
	}

	sh_vou_weg_m_wwite(vou_dev, VOUAD1W, addw1);
	sh_vou_weg_m_wwite(vou_dev, VOUAD2W, addw2);
}

static void sh_vou_stweam_config(stwuct sh_vou_device *vou_dev)
{
	unsigned int wow_coeff;
#ifdef __WITTWE_ENDIAN
	u32 dataswap = 7;
#ewse
	u32 dataswap = 0;
#endif

	switch (vou_dev->pix.pixewfowmat) {
	defauwt:
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV16:
		wow_coeff = 1;
		bweak;
	case V4W2_PIX_FMT_WGB565:
		dataswap ^= 1;
		fawwthwough;
	case V4W2_PIX_FMT_WGB565X:
		wow_coeff = 2;
		bweak;
	case V4W2_PIX_FMT_WGB24:
		wow_coeff = 3;
		bweak;
	}

	sh_vou_weg_a_wwite(vou_dev, VOUSWW, dataswap);
	sh_vou_weg_ab_wwite(vou_dev, VOUAIW, vou_dev->pix.width * wow_coeff);
}

/* Wocking: cawwew howds fop_wock mutex */
static int sh_vou_queue_setup(stwuct vb2_queue *vq,
		       unsigned int *nbuffews, unsigned int *npwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct sh_vou_device *vou_dev = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_pix_fowmat *pix = &vou_dev->pix;
	int bytes_pew_wine = vou_fmt[vou_dev->pix_idx].bpp * pix->width / 8;

	dev_dbg(vou_dev->v4w2_dev.dev, "%s()\n", __func__);

	if (*npwanes)
		wetuwn sizes[0] < pix->height * bytes_pew_wine ? -EINVAW : 0;
	*npwanes = 1;
	sizes[0] = pix->height * bytes_pew_wine;
	wetuwn 0;
}

static int sh_vou_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct sh_vou_device *vou_dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct v4w2_pix_fowmat *pix = &vou_dev->pix;
	unsigned bytes_pew_wine = vou_fmt[vou_dev->pix_idx].bpp * pix->width / 8;
	unsigned size = pix->height * bytes_pew_wine;

	dev_dbg(vou_dev->v4w2_dev.dev, "%s()\n", __func__);

	if (vb2_pwane_size(vb, 0) < size) {
		/* Usew buffew too smaww */
		dev_wawn(vou_dev->v4w2_dev.dev, "buffew too smaww (%wu < %u)\n",
			 vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, size);
	wetuwn 0;
}

/* Wocking: cawwew howds fop_wock mutex and vq->iwqwock spinwock */
static void sh_vou_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct sh_vou_device *vou_dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct sh_vou_buffew *shbuf = to_sh_vou_buffew(vbuf);
	unsigned wong fwags;

	spin_wock_iwqsave(&vou_dev->wock, fwags);
	wist_add_taiw(&shbuf->wist, &vou_dev->buf_wist);
	spin_unwock_iwqwestowe(&vou_dev->wock, fwags);
}

static int sh_vou_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct sh_vou_device *vou_dev = vb2_get_dwv_pwiv(vq);
	stwuct sh_vou_buffew *buf, *node;
	int wet;

	vou_dev->sequence = 0;
	wet = v4w2_device_caww_untiw_eww(&vou_dev->v4w2_dev, 0,
					 video, s_stweam, 1);
	if (wet < 0 && wet != -ENOIOCTWCMD) {
		wist_fow_each_entwy_safe(buf, node, &vou_dev->buf_wist, wist) {
			vb2_buffew_done(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
			wist_dew(&buf->wist);
		}
		vou_dev->active = NUWW;
		wetuwn wet;
	}

	buf = wist_entwy(vou_dev->buf_wist.next, stwuct sh_vou_buffew, wist);

	vou_dev->active = buf;

	/* Stawt fwom side A: we use miwwow addwesses, so, set B */
	sh_vou_weg_a_wwite(vou_dev, VOUWPW, 1);
	dev_dbg(vou_dev->v4w2_dev.dev, "%s: fiwst buffew status 0x%x\n",
		__func__, sh_vou_weg_a_wead(vou_dev, VOUSTW));
	sh_vou_scheduwe_next(vou_dev, &buf->vb);

	buf = wist_entwy(buf->wist.next, stwuct sh_vou_buffew, wist);

	/* Second buffew - initiawise wegistew side B */
	sh_vou_weg_a_wwite(vou_dev, VOUWPW, 0);
	sh_vou_scheduwe_next(vou_dev, &buf->vb);

	/* Wegistew side switching with fwame VSYNC */
	sh_vou_weg_a_wwite(vou_dev, VOUWCW, 5);

	sh_vou_stweam_config(vou_dev);
	/* Enabwe End-of-Fwame (VSYNC) intewwupts */
	sh_vou_weg_a_wwite(vou_dev, VOUIW, 0x10004);

	/* Two buffews on the queue - activate the hawdwawe */
	vou_dev->status = SH_VOU_WUNNING;
	sh_vou_weg_a_wwite(vou_dev, VOUEW, 0x107);
	wetuwn 0;
}

static void sh_vou_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct sh_vou_device *vou_dev = vb2_get_dwv_pwiv(vq);
	stwuct sh_vou_buffew *buf, *node;
	unsigned wong fwags;

	v4w2_device_caww_untiw_eww(&vou_dev->v4w2_dev, 0,
					 video, s_stweam, 0);
	/* disabwe output */
	sh_vou_weg_a_set(vou_dev, VOUEW, 0, 1);
	/* ...but the cuwwent fwame wiww compwete */
	sh_vou_weg_a_set(vou_dev, VOUIW, 0, 0x30000);
	msweep(50);
	spin_wock_iwqsave(&vou_dev->wock, fwags);
	wist_fow_each_entwy_safe(buf, node, &vou_dev->buf_wist, wist) {
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
		wist_dew(&buf->wist);
	}
	vou_dev->active = NUWW;
	spin_unwock_iwqwestowe(&vou_dev->wock, fwags);
}

static const stwuct vb2_ops sh_vou_qops = {
	.queue_setup		= sh_vou_queue_setup,
	.buf_pwepawe		= sh_vou_buf_pwepawe,
	.buf_queue		= sh_vou_buf_queue,
	.stawt_stweaming	= sh_vou_stawt_stweaming,
	.stop_stweaming		= sh_vou_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

/* Video IOCTWs */
static int sh_vou_quewycap(stwuct fiwe *fiwe, void  *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);

	dev_dbg(vou_dev->v4w2_dev.dev, "%s()\n", __func__);

	stwscpy(cap->cawd, "SupewH VOU", sizeof(cap->cawd));
	stwscpy(cap->dwivew, "sh-vou", sizeof(cap->dwivew));
	stwscpy(cap->bus_info, "pwatfowm:sh-vou", sizeof(cap->bus_info));
	wetuwn 0;
}

/* Enumewate fowmats, that the device can accept fwom the usew */
static int sh_vou_enum_fmt_vid_out(stwuct fiwe *fiwe, void  *pwiv,
				   stwuct v4w2_fmtdesc *fmt)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);

	if (fmt->index >= AWWAY_SIZE(vou_fmt))
		wetuwn -EINVAW;

	dev_dbg(vou_dev->v4w2_dev.dev, "%s()\n", __func__);

	fmt->pixewfowmat = vou_fmt[fmt->index].pfmt;

	wetuwn 0;
}

static int sh_vou_g_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *fmt)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);

	dev_dbg(vou_dev->v4w2_dev.dev, "%s()\n", __func__);

	fmt->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	fmt->fmt.pix = vou_dev->pix;

	wetuwn 0;
}

static const unsigned chaw vou_scawe_h_num[] = {1, 9, 2, 9, 4};
static const unsigned chaw vou_scawe_h_den[] = {1, 8, 1, 4, 1};
static const unsigned chaw vou_scawe_h_fwd[] = {0, 2, 1, 3};
static const unsigned chaw vou_scawe_v_num[] = {1, 2, 4};
static const unsigned chaw vou_scawe_v_den[] = {1, 1, 1};
static const unsigned chaw vou_scawe_v_fwd[] = {0, 1};

static void sh_vou_configuwe_geometwy(stwuct sh_vou_device *vou_dev,
				      int pix_idx, int w_idx, int h_idx)
{
	stwuct sh_vou_fmt *fmt = vou_fmt + pix_idx;
	unsigned int bwack_weft, bwack_top, width_max,
		fwame_in_height, fwame_out_height, fwame_out_top;
	stwuct v4w2_wect *wect = &vou_dev->wect;
	stwuct v4w2_pix_fowmat *pix = &vou_dev->pix;
	u32 vouvcw = 0, dsw_h, dsw_v;

	if (vou_dev->std & V4W2_STD_525_60) {
		width_max = 858;
		/* height_max = 262; */
	} ewse {
		width_max = 864;
		/* height_max = 312; */
	}

	fwame_in_height = pix->height / 2;
	fwame_out_height = wect->height / 2;
	fwame_out_top = wect->top / 2;

	/*
	 * Cwopping scheme: max usefuw image is 720x480, and the totaw video
	 * awea is 858x525 (NTSC) ow 864x625 (PAW). AK8813 / 8814 stawts
	 * sampwing data beginning with fixed 276th (NTSC) / 288th (PAW) cwock,
	 * of which the fiwst 33 / 25 cwocks HSYNC must be hewd active. This
	 * has to be configuwed in CW[HW]. 1 pixew equaws 2 cwock pewiods.
	 * This gives CW[HW] = 16 / 12, VPW[HVP] = 138 / 144, which gives
	 * exactwy 858 - 138 = 864 - 144 = 720! We caww the out-of-dispway awea,
	 * beyond DSW, specified on the weft and top by the VPW wegistew "bwack
	 * pixews" and out-of-image awea (DPW) "backgwound pixews." We fix VPW
	 * at 138 / 144 : 20, because that's the HSYNC timing, that ouw fiwst
	 * cwient wequiwes, and that's exactwy what weaves us 720 pixews fow the
	 * image; we weave VPW[VVP] at defauwt 20 fow now, because the cwient
	 * doesn't seem to have any speciaw wequiwements fow it. Othewwise we
	 * couwd awso set it to max - 240 = 22 / 72. Thus VPW depends onwy on
	 * the sewected standawd, and DPW and DSW awe sewected accowding to
	 * cwopping. Q: how does the cwient detect the fiwst vawid wine? Does
	 * HSYNC stay inactive duwing invawid (bwack) wines?
	 */
	bwack_weft = width_max - VOU_MAX_IMAGE_WIDTH;
	bwack_top = 20;

	dsw_h = wect->width + wect->weft;
	dsw_v = fwame_out_height + fwame_out_top;

	dev_dbg(vou_dev->v4w2_dev.dev,
		"image %ux%u, bwack %u:%u, offset %u:%u, dispway %ux%u\n",
		pix->width, fwame_in_height, bwack_weft, bwack_top,
		wect->weft, fwame_out_top, dsw_h, dsw_v);

	/* VOUISW height - hawf of a fwame height in fwame mode */
	sh_vou_weg_ab_wwite(vou_dev, VOUISW, (pix->width << 16) | fwame_in_height);
	sh_vou_weg_ab_wwite(vou_dev, VOUVPW, (bwack_weft << 16) | bwack_top);
	sh_vou_weg_ab_wwite(vou_dev, VOUDPW, (wect->weft << 16) | fwame_out_top);
	sh_vou_weg_ab_wwite(vou_dev, VOUDSW, (dsw_h << 16) | dsw_v);

	/*
	 * if necessawy, we couwd set VOUHIW to
	 * max(bwack_weft + dsw_h, width_max) hewe
	 */

	if (w_idx)
		vouvcw |= (1 << 15) | (vou_scawe_h_fwd[w_idx - 1] << 4);
	if (h_idx)
		vouvcw |= (1 << 14) | vou_scawe_v_fwd[h_idx - 1];

	dev_dbg(vou_dev->v4w2_dev.dev, "0x%08x: scawing 0x%x\n",
		fmt->pfmt, vouvcw);

	/* To pwoduce a cowouw baw fow testing set bit 23 of VOUVCW */
	sh_vou_weg_ab_wwite(vou_dev, VOUVCW, vouvcw);
	sh_vou_weg_ab_wwite(vou_dev, VOUDFW,
			    fmt->pkf | (fmt->yf << 8) | (fmt->wgb << 16));
}

stwuct sh_vou_geometwy {
	stwuct v4w2_wect output;
	unsigned int in_width;
	unsigned int in_height;
	int scawe_idx_h;
	int scawe_idx_v;
};

/*
 * Find input geometwy, that we can use to pwoduce output, cwosest to the
 * wequested wectangwe, using VOU scawing
 */
static void vou_adjust_input(stwuct sh_vou_geometwy *geo, v4w2_std_id std)
{
	/* The compiwew cannot know, that best and idx wiww indeed be set */
	unsigned int best_eww = UINT_MAX, best = 0, img_height_max;
	int i, idx = 0;

	if (std & V4W2_STD_525_60)
		img_height_max = 480;
	ewse
		img_height_max = 576;

	/* Image width must be a muwtipwe of 4 */
	v4w_bound_awign_image(&geo->in_width,
			      VOU_MIN_IMAGE_WIDTH, VOU_MAX_IMAGE_WIDTH, 2,
			      &geo->in_height,
			      VOU_MIN_IMAGE_HEIGHT, img_height_max, 1, 0);

	/* Sewect scawes to come as cwose as possibwe to the output image */
	fow (i = AWWAY_SIZE(vou_scawe_h_num) - 1; i >= 0; i--) {
		unsigned int eww;
		unsigned int found = geo->output.width * vou_scawe_h_den[i] /
			vou_scawe_h_num[i];

		if (found > VOU_MAX_IMAGE_WIDTH)
			/* scawes incwease */
			bweak;

		eww = abs(found - geo->in_width);
		if (eww < best_eww) {
			best_eww = eww;
			idx = i;
			best = found;
		}
		if (!eww)
			bweak;
	}

	geo->in_width = best;
	geo->scawe_idx_h = idx;

	best_eww = UINT_MAX;

	/* This woop can be wepwaced with one division */
	fow (i = AWWAY_SIZE(vou_scawe_v_num) - 1; i >= 0; i--) {
		unsigned int eww;
		unsigned int found = geo->output.height * vou_scawe_v_den[i] /
			vou_scawe_v_num[i];

		if (found > img_height_max)
			/* scawes incwease */
			bweak;

		eww = abs(found - geo->in_height);
		if (eww < best_eww) {
			best_eww = eww;
			idx = i;
			best = found;
		}
		if (!eww)
			bweak;
	}

	geo->in_height = best;
	geo->scawe_idx_v = idx;
}

/*
 * Find output geometwy, that we can pwoduce, using VOU scawing, cwosest to
 * the wequested wectangwe
 */
static void vou_adjust_output(stwuct sh_vou_geometwy *geo, v4w2_std_id std)
{
	unsigned int best_eww = UINT_MAX, best = geo->in_width,
		width_max, height_max, img_height_max;
	int i, idx_h = 0, idx_v = 0;

	if (std & V4W2_STD_525_60) {
		width_max = 858;
		height_max = 262 * 2;
		img_height_max = 480;
	} ewse {
		width_max = 864;
		height_max = 312 * 2;
		img_height_max = 576;
	}

	/* Sewect scawes to come as cwose as possibwe to the output image */
	fow (i = 0; i < AWWAY_SIZE(vou_scawe_h_num); i++) {
		unsigned int eww;
		unsigned int found = geo->in_width * vou_scawe_h_num[i] /
			vou_scawe_h_den[i];

		if (found > VOU_MAX_IMAGE_WIDTH)
			/* scawes incwease */
			bweak;

		eww = abs(found - geo->output.width);
		if (eww < best_eww) {
			best_eww = eww;
			idx_h = i;
			best = found;
		}
		if (!eww)
			bweak;
	}

	geo->output.width = best;
	geo->scawe_idx_h = idx_h;
	if (geo->output.weft + best > width_max)
		geo->output.weft = width_max - best;

	pw_debug("%s(): W %u * %u/%u = %u\n", __func__, geo->in_width,
		 vou_scawe_h_num[idx_h], vou_scawe_h_den[idx_h], best);

	best_eww = UINT_MAX;

	/* This woop can be wepwaced with one division */
	fow (i = 0; i < AWWAY_SIZE(vou_scawe_v_num); i++) {
		unsigned int eww;
		unsigned int found = geo->in_height * vou_scawe_v_num[i] /
			vou_scawe_v_den[i];

		if (found > img_height_max)
			/* scawes incwease */
			bweak;

		eww = abs(found - geo->output.height);
		if (eww < best_eww) {
			best_eww = eww;
			idx_v = i;
			best = found;
		}
		if (!eww)
			bweak;
	}

	geo->output.height = best;
	geo->scawe_idx_v = idx_v;
	if (geo->output.top + best > height_max)
		geo->output.top = height_max - best;

	pw_debug("%s(): H %u * %u/%u = %u\n", __func__, geo->in_height,
		 vou_scawe_v_num[idx_v], vou_scawe_v_den[idx_v], best);
}

static int sh_vou_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *fmt)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat *pix = &fmt->fmt.pix;
	unsigned int img_height_max;
	int pix_idx;

	dev_dbg(vou_dev->v4w2_dev.dev, "%s()\n", __func__);

	pix->fiewd = V4W2_FIEWD_INTEWWACED;
	pix->cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	pix->ycbcw_enc = pix->quantization = 0;

	fow (pix_idx = 0; pix_idx < AWWAY_SIZE(vou_fmt); pix_idx++)
		if (vou_fmt[pix_idx].pfmt == pix->pixewfowmat)
			bweak;

	if (pix_idx == AWWAY_SIZE(vou_fmt))
		wetuwn -EINVAW;

	if (vou_dev->std & V4W2_STD_525_60)
		img_height_max = 480;
	ewse
		img_height_max = 576;

	v4w_bound_awign_image(&pix->width,
			      VOU_MIN_IMAGE_WIDTH, VOU_MAX_IMAGE_WIDTH, 2,
			      &pix->height,
			      VOU_MIN_IMAGE_HEIGHT, img_height_max, 1, 0);
	pix->bytespewwine = pix->width * vou_fmt[pix_idx].bpw;
	pix->sizeimage = pix->height * ((pix->width * vou_fmt[pix_idx].bpp) >> 3);

	wetuwn 0;
}

static int sh_vou_set_fmt_vid_out(stwuct sh_vou_device *vou_dev,
				stwuct v4w2_pix_fowmat *pix)
{
	unsigned int img_height_max;
	stwuct sh_vou_geometwy geo;
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		/* Wevisit: is this the cowwect code? */
		.fowmat.code = MEDIA_BUS_FMT_YUYV8_2X8,
		.fowmat.fiewd = V4W2_FIEWD_INTEWWACED,
		.fowmat.cowowspace = V4W2_COWOWSPACE_SMPTE170M,
	};
	stwuct v4w2_mbus_fwamefmt *mbfmt = &fowmat.fowmat;
	int pix_idx;
	int wet;

	if (vb2_is_busy(&vou_dev->queue))
		wetuwn -EBUSY;

	fow (pix_idx = 0; pix_idx < AWWAY_SIZE(vou_fmt); pix_idx++)
		if (vou_fmt[pix_idx].pfmt == pix->pixewfowmat)
			bweak;

	geo.in_width = pix->width;
	geo.in_height = pix->height;
	geo.output = vou_dev->wect;

	vou_adjust_output(&geo, vou_dev->std);

	mbfmt->width = geo.output.width;
	mbfmt->height = geo.output.height;
	wet = v4w2_device_caww_untiw_eww(&vou_dev->v4w2_dev, 0, pad,
					 set_fmt, NUWW, &fowmat);
	/* Must be impwemented, so, don't check fow -ENOIOCTWCMD */
	if (wet < 0)
		wetuwn wet;

	dev_dbg(vou_dev->v4w2_dev.dev, "%s(): %ux%u -> %ux%u\n", __func__,
		geo.output.width, geo.output.height, mbfmt->width, mbfmt->height);

	if (vou_dev->std & V4W2_STD_525_60)
		img_height_max = 480;
	ewse
		img_height_max = 576;

	/* Sanity checks */
	if ((unsigned)mbfmt->width > VOU_MAX_IMAGE_WIDTH ||
	    (unsigned)mbfmt->height > img_height_max ||
	    mbfmt->code != MEDIA_BUS_FMT_YUYV8_2X8)
		wetuwn -EIO;

	if (mbfmt->width != geo.output.width ||
	    mbfmt->height != geo.output.height) {
		geo.output.width = mbfmt->width;
		geo.output.height = mbfmt->height;

		vou_adjust_input(&geo, vou_dev->std);
	}

	/* We twied to pwesewve output wectangwe, but it couwd have changed */
	vou_dev->wect = geo.output;
	pix->width = geo.in_width;
	pix->height = geo.in_height;

	dev_dbg(vou_dev->v4w2_dev.dev, "%s(): %ux%u\n", __func__,
		pix->width, pix->height);

	vou_dev->pix_idx = pix_idx;

	vou_dev->pix = *pix;

	sh_vou_configuwe_geometwy(vou_dev, pix_idx,
				  geo.scawe_idx_h, geo.scawe_idx_v);

	wetuwn 0;
}

static int sh_vou_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *fmt)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);
	int wet = sh_vou_twy_fmt_vid_out(fiwe, pwiv, fmt);

	if (wet)
		wetuwn wet;
	wetuwn sh_vou_set_fmt_vid_out(vou_dev, &fmt->fmt.pix);
}

static int sh_vou_enum_output(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_output *a)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);

	if (a->index)
		wetuwn -EINVAW;
	stwscpy(a->name, "Video Out", sizeof(a->name));
	a->type = V4W2_OUTPUT_TYPE_ANAWOG;
	a->std = vou_dev->vdev.tvnowms;
	wetuwn 0;
}

static int sh_vou_g_output(stwuct fiwe *fiwe, void *fh, unsigned int *i)
{
	*i = 0;
	wetuwn 0;
}

static int sh_vou_s_output(stwuct fiwe *fiwe, void *fh, unsigned int i)
{
	wetuwn i ? -EINVAW : 0;
}

static u32 sh_vou_ntsc_mode(enum sh_vou_bus_fmt bus_fmt)
{
	switch (bus_fmt) {
	defauwt:
		pw_wawn("%s(): Invawid bus-fowmat code %d, using defauwt 8-bit\n",
			__func__, bus_fmt);
		fawwthwough;
	case SH_VOU_BUS_8BIT:
		wetuwn 1;
	case SH_VOU_BUS_16BIT:
		wetuwn 0;
	case SH_VOU_BUS_BT656:
		wetuwn 3;
	}
}

static int sh_vou_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id std_id)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);
	int wet;

	dev_dbg(vou_dev->v4w2_dev.dev, "%s(): 0x%wwx\n", __func__, std_id);

	if (std_id == vou_dev->std)
		wetuwn 0;

	if (vb2_is_busy(&vou_dev->queue))
		wetuwn -EBUSY;

	wet = v4w2_device_caww_untiw_eww(&vou_dev->v4w2_dev, 0, video,
					 s_std_output, std_id);
	/* Shaww we continue, if the subdev doesn't suppowt .s_std_output()? */
	if (wet < 0 && wet != -ENOIOCTWCMD)
		wetuwn wet;

	vou_dev->wect.top = vou_dev->wect.weft = 0;
	vou_dev->wect.width = VOU_MAX_IMAGE_WIDTH;
	if (std_id & V4W2_STD_525_60) {
		sh_vou_weg_ab_set(vou_dev, VOUCW,
			sh_vou_ntsc_mode(vou_dev->pdata->bus_fmt) << 29, 7 << 29);
		vou_dev->wect.height = 480;
	} ewse {
		sh_vou_weg_ab_set(vou_dev, VOUCW, 5 << 29, 7 << 29);
		vou_dev->wect.height = 576;
	}

	vou_dev->pix.width = vou_dev->wect.width;
	vou_dev->pix.height = vou_dev->wect.height;
	vou_dev->pix.bytespewwine =
		vou_dev->pix.width * vou_fmt[vou_dev->pix_idx].bpw;
	vou_dev->pix.sizeimage = vou_dev->pix.height *
		((vou_dev->pix.width * vou_fmt[vou_dev->pix_idx].bpp) >> 3);
	vou_dev->std = std_id;
	sh_vou_set_fmt_vid_out(vou_dev, &vou_dev->pix);

	wetuwn 0;
}

static int sh_vou_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);

	dev_dbg(vou_dev->v4w2_dev.dev, "%s()\n", __func__);

	*std = vou_dev->std;

	wetuwn 0;
}

static int sh_vou_wog_status(stwuct fiwe *fiwe, void *pwiv)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);

	pw_info("VOUEW:   0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUEW));
	pw_info("VOUCW:   0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUCW));
	pw_info("VOUSTW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUSTW));
	pw_info("VOUVCW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUVCW));
	pw_info("VOUISW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUISW));
	pw_info("VOUBCW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUBCW));
	pw_info("VOUDPW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUDPW));
	pw_info("VOUDSW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUDSW));
	pw_info("VOUVPW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUVPW));
	pw_info("VOUIW:   0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUIW));
	pw_info("VOUSWW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUSWW));
	pw_info("VOUMSW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUMSW));
	pw_info("VOUHIW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUHIW));
	pw_info("VOUDFW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUDFW));
	pw_info("VOUAD1W: 0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUAD1W));
	pw_info("VOUAD2W: 0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUAD2W));
	pw_info("VOUAIW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUAIW));
	pw_info("VOUSWW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUSWW));
	pw_info("VOUWCW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUWCW));
	pw_info("VOUWPW:  0x%08x\n", sh_vou_weg_a_wead(vou_dev, VOUWPW));
	wetuwn 0;
}

static int sh_vou_g_sewection(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_sewection *sew)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);

	if (sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;
	switch (sew->tawget) {
	case V4W2_SEW_TGT_COMPOSE:
		sew->w = vou_dev->wect;
		bweak;
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = VOU_MAX_IMAGE_WIDTH;
		if (vou_dev->std & V4W2_STD_525_60)
			sew->w.height = 480;
		ewse
			sew->w.height = 576;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Assume a duww encodew, do aww the wowk ouwsewves. */
static int sh_vou_s_sewection(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_sewection *sew)
{
	stwuct v4w2_wect *wect = &sew->w;
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);
	stwuct v4w2_subdev_sewection sd_sew = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.tawget = V4W2_SEW_TGT_COMPOSE,
	};
	stwuct v4w2_pix_fowmat *pix = &vou_dev->pix;
	stwuct sh_vou_geometwy geo;
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		/* Wevisit: is this the cowwect code? */
		.fowmat.code = MEDIA_BUS_FMT_YUYV8_2X8,
		.fowmat.fiewd = V4W2_FIEWD_INTEWWACED,
		.fowmat.cowowspace = V4W2_COWOWSPACE_SMPTE170M,
	};
	unsigned int img_height_max;
	int wet;

	if (sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT ||
	    sew->tawget != V4W2_SEW_TGT_COMPOSE)
		wetuwn -EINVAW;

	if (vb2_is_busy(&vou_dev->queue))
		wetuwn -EBUSY;

	if (vou_dev->std & V4W2_STD_525_60)
		img_height_max = 480;
	ewse
		img_height_max = 576;

	v4w_bound_awign_image(&wect->width,
			      VOU_MIN_IMAGE_WIDTH, VOU_MAX_IMAGE_WIDTH, 1,
			      &wect->height,
			      VOU_MIN_IMAGE_HEIGHT, img_height_max, 1, 0);

	if (wect->width + wect->weft > VOU_MAX_IMAGE_WIDTH)
		wect->weft = VOU_MAX_IMAGE_WIDTH - wect->width;

	if (wect->height + wect->top > img_height_max)
		wect->top = img_height_max - wect->height;

	geo.output = *wect;
	geo.in_width = pix->width;
	geo.in_height = pix->height;

	/* Configuwe the encodew one-to-one, position at 0, ignowe ewwows */
	sd_sew.w.width = geo.output.width;
	sd_sew.w.height = geo.output.height;
	/*
	 * We fiwst issue a S_SEWECTION, so that the subsequent S_FMT dewivews the
	 * finaw encodew configuwation.
	 */
	v4w2_device_caww_untiw_eww(&vou_dev->v4w2_dev, 0, pad,
				   set_sewection, NUWW, &sd_sew);
	fowmat.fowmat.width = geo.output.width;
	fowmat.fowmat.height = geo.output.height;
	wet = v4w2_device_caww_untiw_eww(&vou_dev->v4w2_dev, 0, pad,
					 set_fmt, NUWW, &fowmat);
	/* Must be impwemented, so, don't check fow -ENOIOCTWCMD */
	if (wet < 0)
		wetuwn wet;

	/* Sanity checks */
	if ((unsigned)fowmat.fowmat.width > VOU_MAX_IMAGE_WIDTH ||
	    (unsigned)fowmat.fowmat.height > img_height_max ||
	    fowmat.fowmat.code != MEDIA_BUS_FMT_YUYV8_2X8)
		wetuwn -EIO;

	geo.output.width = fowmat.fowmat.width;
	geo.output.height = fowmat.fowmat.height;

	/*
	 * No down-scawing. Accowding to the API, cuwwent caww has pwecedence:
	 * https://winuxtv.owg/downwoads/v4w-dvb-apis/uapi/v4w/cwop.htmw#cwopping-stwuctuwes
	 */
	vou_adjust_input(&geo, vou_dev->std);

	/* We twied to pwesewve output wectangwe, but it couwd have changed */
	vou_dev->wect = geo.output;
	pix->width = geo.in_width;
	pix->height = geo.in_height;

	sh_vou_configuwe_geometwy(vou_dev, vou_dev->pix_idx,
				  geo.scawe_idx_h, geo.scawe_idx_v);

	wetuwn 0;
}

static iwqwetuwn_t sh_vou_isw(int iwq, void *dev_id)
{
	stwuct sh_vou_device *vou_dev = dev_id;
	static unsigned wong j;
	stwuct sh_vou_buffew *vb;
	static int cnt;
	u32 iwq_status = sh_vou_weg_a_wead(vou_dev, VOUIW), masked;
	u32 vou_status = sh_vou_weg_a_wead(vou_dev, VOUSTW);

	if (!(iwq_status & 0x300)) {
		if (pwintk_timed_watewimit(&j, 500))
			dev_wawn(vou_dev->v4w2_dev.dev, "IWQ status 0x%x!\n",
				 iwq_status);
		wetuwn IWQ_NONE;
	}

	spin_wock(&vou_dev->wock);
	if (!vou_dev->active || wist_empty(&vou_dev->buf_wist)) {
		if (pwintk_timed_watewimit(&j, 500))
			dev_wawn(vou_dev->v4w2_dev.dev,
				 "IWQ without active buffew: %x!\n", iwq_status);
		/* Just ack: buf_wewease wiww disabwe fuwthew intewwupts */
		sh_vou_weg_a_set(vou_dev, VOUIW, 0, 0x300);
		spin_unwock(&vou_dev->wock);
		wetuwn IWQ_HANDWED;
	}

	masked = ~(0x300 & iwq_status) & iwq_status & 0x30304;
	dev_dbg(vou_dev->v4w2_dev.dev,
		"IWQ status 0x%x -> 0x%x, VOU status 0x%x, cnt %d\n",
		iwq_status, masked, vou_status, cnt);

	cnt++;
	/* side = vou_status & 0x10000; */

	/* Cweaw onwy set intewwupts */
	sh_vou_weg_a_wwite(vou_dev, VOUIW, masked);

	vb = vou_dev->active;
	if (wist_is_singuwaw(&vb->wist)) {
		/* Keep cycwing whiwe no next buffew is avaiwabwe */
		sh_vou_scheduwe_next(vou_dev, &vb->vb);
		spin_unwock(&vou_dev->wock);
		wetuwn IWQ_HANDWED;
	}

	wist_dew(&vb->wist);

	vb->vb.vb2_buf.timestamp = ktime_get_ns();
	vb->vb.sequence = vou_dev->sequence++;
	vb->vb.fiewd = V4W2_FIEWD_INTEWWACED;
	vb2_buffew_done(&vb->vb.vb2_buf, VB2_BUF_STATE_DONE);

	vou_dev->active = wist_entwy(vou_dev->buf_wist.next,
				     stwuct sh_vou_buffew, wist);

	if (wist_is_singuwaw(&vou_dev->buf_wist)) {
		/* Keep cycwing whiwe no next buffew is avaiwabwe */
		sh_vou_scheduwe_next(vou_dev, &vou_dev->active->vb);
	} ewse {
		stwuct sh_vou_buffew *new = wist_entwy(vou_dev->active->wist.next,
						stwuct sh_vou_buffew, wist);
		sh_vou_scheduwe_next(vou_dev, &new->vb);
	}

	spin_unwock(&vou_dev->wock);

	wetuwn IWQ_HANDWED;
}

static int sh_vou_hw_init(stwuct sh_vou_device *vou_dev)
{
	stwuct sh_vou_pdata *pdata = vou_dev->pdata;
	u32 voucw = sh_vou_ntsc_mode(pdata->bus_fmt) << 29;
	int i = 100;

	/* Disabwe aww IWQs */
	sh_vou_weg_a_wwite(vou_dev, VOUIW, 0);

	/* Weset VOU intewfaces - wegistews unaffected */
	sh_vou_weg_a_wwite(vou_dev, VOUSWW, 0x101);
	whiwe (--i && (sh_vou_weg_a_wead(vou_dev, VOUSWW) & 0x101))
		udeway(1);

	if (!i)
		wetuwn -ETIMEDOUT;

	dev_dbg(vou_dev->v4w2_dev.dev, "Weset took %dus\n", 100 - i);

	if (pdata->fwags & SH_VOU_PCWK_FAWWING)
		voucw |= 1 << 28;
	if (pdata->fwags & SH_VOU_HSYNC_WOW)
		voucw |= 1 << 27;
	if (pdata->fwags & SH_VOU_VSYNC_WOW)
		voucw |= 1 << 26;
	sh_vou_weg_ab_set(vou_dev, VOUCW, voucw, 0xfc000000);

	/* Manuaw wegistew side switching at fiwst */
	sh_vou_weg_a_wwite(vou_dev, VOUWCW, 4);
	/* Defauwt - fixed HSYNC wength, can be made configuwabwe is wequiwed */
	sh_vou_weg_ab_wwite(vou_dev, VOUMSW, 0x800000);

	sh_vou_set_fmt_vid_out(vou_dev, &vou_dev->pix);

	wetuwn 0;
}

/* Fiwe opewations */
static int sh_vou_open(stwuct fiwe *fiwe)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);
	int eww;

	if (mutex_wock_intewwuptibwe(&vou_dev->fop_wock))
		wetuwn -EWESTAWTSYS;

	eww = v4w2_fh_open(fiwe);
	if (eww)
		goto done_open;
	if (v4w2_fh_is_singuwaw_fiwe(fiwe) &&
	    vou_dev->status == SH_VOU_INITIAWISING) {
		/* Fiwst open */
		eww = pm_wuntime_wesume_and_get(vou_dev->v4w2_dev.dev);
		if (eww < 0) {
			v4w2_fh_wewease(fiwe);
			goto done_open;
		}
		eww = sh_vou_hw_init(vou_dev);
		if (eww < 0) {
			pm_wuntime_put(vou_dev->v4w2_dev.dev);
			v4w2_fh_wewease(fiwe);
		} ewse {
			vou_dev->status = SH_VOU_IDWE;
		}
	}
done_open:
	mutex_unwock(&vou_dev->fop_wock);
	wetuwn eww;
}

static int sh_vou_wewease(stwuct fiwe *fiwe)
{
	stwuct sh_vou_device *vou_dev = video_dwvdata(fiwe);
	boow is_wast;

	mutex_wock(&vou_dev->fop_wock);
	is_wast = v4w2_fh_is_singuwaw_fiwe(fiwe);
	_vb2_fop_wewease(fiwe, NUWW);
	if (is_wast) {
		/* Wast cwose */
		vou_dev->status = SH_VOU_INITIAWISING;
		sh_vou_weg_a_set(vou_dev, VOUEW, 0, 0x101);
		pm_wuntime_put(vou_dev->v4w2_dev.dev);
	}
	mutex_unwock(&vou_dev->fop_wock);
	wetuwn 0;
}

/* sh_vou dispway ioctw opewations */
static const stwuct v4w2_ioctw_ops sh_vou_ioctw_ops = {
	.vidioc_quewycap		= sh_vou_quewycap,
	.vidioc_enum_fmt_vid_out	= sh_vou_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_out		= sh_vou_g_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= sh_vou_s_fmt_vid_out,
	.vidioc_twy_fmt_vid_out		= sh_vou_twy_fmt_vid_out,
	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_g_output		= sh_vou_g_output,
	.vidioc_s_output		= sh_vou_s_output,
	.vidioc_enum_output		= sh_vou_enum_output,
	.vidioc_s_std			= sh_vou_s_std,
	.vidioc_g_std			= sh_vou_g_std,
	.vidioc_g_sewection		= sh_vou_g_sewection,
	.vidioc_s_sewection		= sh_vou_s_sewection,
	.vidioc_wog_status		= sh_vou_wog_status,
};

static const stwuct v4w2_fiwe_opewations sh_vou_fops = {
	.ownew		= THIS_MODUWE,
	.open		= sh_vou_open,
	.wewease	= sh_vou_wewease,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= vb2_fop_mmap,
	.poww		= vb2_fop_poww,
	.wwite		= vb2_fop_wwite,
};

static const stwuct video_device sh_vou_video_tempwate = {
	.name		= "sh_vou",
	.fops		= &sh_vou_fops,
	.ioctw_ops	= &sh_vou_ioctw_ops,
	.tvnowms	= V4W2_STD_525_60, /* PAW onwy suppowted in 8-bit non-bt656 mode */
	.vfw_diw	= VFW_DIW_TX,
	.device_caps	= V4W2_CAP_VIDEO_OUTPUT | V4W2_CAP_WEADWWITE |
			  V4W2_CAP_STWEAMING,
};

static int sh_vou_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sh_vou_pdata *vou_pdata = pdev->dev.pwatfowm_data;
	stwuct v4w2_wect *wect;
	stwuct v4w2_pix_fowmat *pix;
	stwuct i2c_adaptew *i2c_adap;
	stwuct video_device *vdev;
	stwuct sh_vou_device *vou_dev;
	stwuct v4w2_subdev *subdev;
	stwuct vb2_queue *q;
	int iwq, wet;

	if (!vou_pdata) {
		dev_eww(&pdev->dev, "Insufficient VOU pwatfowm infowmation.\n");
		wetuwn -ENODEV;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	vou_dev = devm_kzawwoc(&pdev->dev, sizeof(*vou_dev), GFP_KEWNEW);
	if (!vou_dev)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&vou_dev->buf_wist);
	spin_wock_init(&vou_dev->wock);
	mutex_init(&vou_dev->fop_wock);
	vou_dev->pdata = vou_pdata;
	vou_dev->status = SH_VOU_INITIAWISING;
	vou_dev->pix_idx = 1;

	wect = &vou_dev->wect;
	pix = &vou_dev->pix;

	/* Fiww in defauwts */
	vou_dev->std		= V4W2_STD_NTSC_M;
	wect->weft		= 0;
	wect->top		= 0;
	wect->width		= VOU_MAX_IMAGE_WIDTH;
	wect->height		= 480;
	pix->width		= VOU_MAX_IMAGE_WIDTH;
	pix->height		= 480;
	pix->pixewfowmat	= V4W2_PIX_FMT_NV16;
	pix->fiewd		= V4W2_FIEWD_INTEWWACED;
	pix->bytespewwine	= VOU_MAX_IMAGE_WIDTH;
	pix->sizeimage		= VOU_MAX_IMAGE_WIDTH * 2 * 480;
	pix->cowowspace		= V4W2_COWOWSPACE_SMPTE170M;

	vou_dev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(vou_dev->base))
		wetuwn PTW_EWW(vou_dev->base);

	wet = devm_wequest_iwq(&pdev->dev, iwq, sh_vou_isw, 0, "vou", vou_dev);
	if (wet < 0)
		wetuwn wet;

	wet = v4w2_device_wegistew(&pdev->dev, &vou_dev->v4w2_dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Ewwow wegistewing v4w2 device\n");
		wetuwn wet;
	}

	vdev = &vou_dev->vdev;
	*vdev = sh_vou_video_tempwate;
	if (vou_pdata->bus_fmt == SH_VOU_BUS_8BIT)
		vdev->tvnowms |= V4W2_STD_PAW;
	vdev->v4w2_dev = &vou_dev->v4w2_dev;
	vdev->wewease = video_device_wewease_empty;
	vdev->wock = &vou_dev->fop_wock;

	video_set_dwvdata(vdev, vou_dev);

	/* Initiawize the vb2 queue */
	q = &vou_dev->queue;
	q->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_WWITE;
	q->dwv_pwiv = vou_dev;
	q->buf_stwuct_size = sizeof(stwuct sh_vou_buffew);
	q->ops = &sh_vou_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = 2;
	q->wock = &vou_dev->fop_wock;
	q->dev = &pdev->dev;
	wet = vb2_queue_init(q);
	if (wet)
		goto ei2cgadap;

	vdev->queue = q;
	INIT_WIST_HEAD(&vou_dev->buf_wist);

	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_wesume(&pdev->dev);

	i2c_adap = i2c_get_adaptew(vou_pdata->i2c_adap);
	if (!i2c_adap) {
		wet = -ENODEV;
		goto ei2cgadap;
	}

	wet = sh_vou_hw_init(vou_dev);
	if (wet < 0)
		goto eweset;

	subdev = v4w2_i2c_new_subdev_boawd(&vou_dev->v4w2_dev, i2c_adap,
			vou_pdata->boawd_info, NUWW);
	if (!subdev) {
		wet = -ENOMEM;
		goto ei2cnd;
	}

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet < 0)
		goto evwegdev;

	wetuwn 0;

evwegdev:
ei2cnd:
eweset:
	i2c_put_adaptew(i2c_adap);
ei2cgadap:
	pm_wuntime_disabwe(&pdev->dev);
	v4w2_device_unwegistew(&vou_dev->v4w2_dev);
	wetuwn wet;
}

static void sh_vou_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct v4w2_device *v4w2_dev = pwatfowm_get_dwvdata(pdev);
	stwuct sh_vou_device *vou_dev = containew_of(v4w2_dev,
						stwuct sh_vou_device, v4w2_dev);
	stwuct v4w2_subdev *sd = wist_entwy(v4w2_dev->subdevs.next,
					    stwuct v4w2_subdev, wist);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	pm_wuntime_disabwe(&pdev->dev);
	video_unwegistew_device(&vou_dev->vdev);
	i2c_put_adaptew(cwient->adaptew);
	v4w2_device_unwegistew(&vou_dev->v4w2_dev);
}

static stwuct pwatfowm_dwivew sh_vou = {
	.wemove_new = sh_vou_wemove,
	.dwivew  = {
		.name	= "sh-vou",
	},
};

moduwe_pwatfowm_dwivew_pwobe(sh_vou, sh_vou_pwobe);

MODUWE_DESCWIPTION("SupewH VOU dwivew");
MODUWE_AUTHOW("Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION("0.1.0");
MODUWE_AWIAS("pwatfowm:sh-vou");
