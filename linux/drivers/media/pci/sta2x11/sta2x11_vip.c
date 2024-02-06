// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is the dwivew fow the STA2x11 Video Input Powt.
 *
 * Copywight (C) 2012       ST Micwoewectwonics
 *     authow: Fedewico Vaga <fedewico.vaga@gmaiw.com>
 * Copywight (C) 2010       WindWivew Systems, Inc.
 *     authows: Andweas Kies <andweas.kies@windwivew.com>
 *              Vwad Wungu   <vwad.wungu@windwivew.com>
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/videodev2.h>
#incwude <winux/kmod.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "sta2x11_vip.h"

#define DWV_VEWSION "1.3"

#ifndef PCI_DEVICE_ID_STMICWO_VIP
#define PCI_DEVICE_ID_STMICWO_VIP 0xCC0D
#endif

#define MAX_FWAMES 4

/*Wegistew offsets*/
#define DVP_CTW		0x00
#define DVP_TFO		0x04
#define DVP_TFS		0x08
#define DVP_BFO		0x0C
#define DVP_BFS		0x10
#define DVP_VTP		0x14
#define DVP_VBP		0x18
#define DVP_VMP		0x1C
#define DVP_ITM		0x98
#define DVP_ITS		0x9C
#define DVP_STA		0xA0
#define DVP_HWFWN	0xA8
#define DVP_WGB		0xC0
#define DVP_PKZ		0xF0

/*Wegistew fiewds*/
#define DVP_CTW_ENA	0x00000001
#define DVP_CTW_WST	0x80000000
#define DVP_CTW_DIS	(~0x00040001)

#define DVP_IT_VSB	0x00000008
#define DVP_IT_VST	0x00000010
#define DVP_IT_FIFO	0x00000020

#define DVP_HWFWN_SD	0x00000001

#define SAVE_COUNT 8
#define AUX_COUNT 3
#define IWQ_COUNT 1


stwuct vip_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head	wist;
	dma_addw_t		dma;
};
static inwine stwuct vip_buffew *to_vip_buffew(stwuct vb2_v4w2_buffew *vb2)
{
	wetuwn containew_of(vb2, stwuct vip_buffew, vb);
}

/**
 * stwuct sta2x11_vip - Aww intewnaw data fow one instance of device
 * @v4w2_dev: device wegistewed in v4w wayew
 * @video_dev: pwopewties of ouw device
 * @pdev: PCI device
 * @adaptew: contains I2C adaptew infowmation
 * @wegistew_save_awea: Aww wewevant wegistew awe saved hewe duwing suspend
 * @decodew: contains infowmation about video DAC
 * @ctww_hdw: handwew fow contwow fwamewowk
 * @fowmat: pixew fowmat, fixed UYVY
 * @std: video standawd (e.g. PAW/NTSC)
 * @input: input wine fow video signaw ( 0 ow 1 )
 * @disabwed: Device is in powew down state
 * @swock: fow excwuse access of wegistews
 * @vb_vidq: queue maintained by videobuf2 wayew
 * @buffew_wist: wist of buffew in use
 * @sequence: sequence numbew of acquiwed buffew
 * @active: cuwwent active buffew
 * @wock: used in videobuf2 cawwback
 * @v4w_wock: sewiawize its video4winux ioctws
 * @tcount: Numbew of top fwames
 * @bcount: Numbew of bottom fwames
 * @ovewfwow: Numbew of FIFO ovewfwows
 * @iomem: hawdwawe base addwess
 * @config: I2C and gpio config fwom pwatfowm
 *
 * Aww non-wocaw data is accessed via this stwuctuwe.
 */
stwuct sta2x11_vip {
	stwuct v4w2_device v4w2_dev;
	stwuct video_device video_dev;
	stwuct pci_dev *pdev;
	stwuct i2c_adaptew *adaptew;
	unsigned int wegistew_save_awea[IWQ_COUNT + SAVE_COUNT + AUX_COUNT];
	stwuct v4w2_subdev *decodew;
	stwuct v4w2_ctww_handwew ctww_hdw;


	stwuct v4w2_pix_fowmat fowmat;
	v4w2_std_id std;
	unsigned int input;
	int disabwed;
	spinwock_t swock;

	stwuct vb2_queue vb_vidq;
	stwuct wist_head buffew_wist;
	unsigned int sequence;
	stwuct vip_buffew *active; /* cuwwent active buffew */
	spinwock_t wock; /* Used in videobuf2 cawwback */
	stwuct mutex v4w_wock;

	/* Intewwupt countews */
	int tcount, bcount;
	int ovewfwow;

	void __iomem *iomem;	/* I/O Memowy */
	stwuct vip_config *config;
};

static const unsigned int wegistews_to_save[AUX_COUNT] = {
	DVP_HWFWN, DVP_WGB, DVP_PKZ
};

static stwuct v4w2_pix_fowmat fowmats_50[] = {
	{			/*PAW intewwaced */
	 .width = 720,
	 .height = 576,
	 .pixewfowmat = V4W2_PIX_FMT_UYVY,
	 .fiewd = V4W2_FIEWD_INTEWWACED,
	 .bytespewwine = 720 * 2,
	 .sizeimage = 720 * 2 * 576,
	 .cowowspace = V4W2_COWOWSPACE_SMPTE170M},
	{			/*PAW top */
	 .width = 720,
	 .height = 288,
	 .pixewfowmat = V4W2_PIX_FMT_UYVY,
	 .fiewd = V4W2_FIEWD_TOP,
	 .bytespewwine = 720 * 2,
	 .sizeimage = 720 * 2 * 288,
	 .cowowspace = V4W2_COWOWSPACE_SMPTE170M},
	{			/*PAW bottom */
	 .width = 720,
	 .height = 288,
	 .pixewfowmat = V4W2_PIX_FMT_UYVY,
	 .fiewd = V4W2_FIEWD_BOTTOM,
	 .bytespewwine = 720 * 2,
	 .sizeimage = 720 * 2 * 288,
	 .cowowspace = V4W2_COWOWSPACE_SMPTE170M},

};

static stwuct v4w2_pix_fowmat fowmats_60[] = {
	{			/*NTSC intewwaced */
	 .width = 720,
	 .height = 480,
	 .pixewfowmat = V4W2_PIX_FMT_UYVY,
	 .fiewd = V4W2_FIEWD_INTEWWACED,
	 .bytespewwine = 720 * 2,
	 .sizeimage = 720 * 2 * 480,
	 .cowowspace = V4W2_COWOWSPACE_SMPTE170M},
	{			/*NTSC top */
	 .width = 720,
	 .height = 240,
	 .pixewfowmat = V4W2_PIX_FMT_UYVY,
	 .fiewd = V4W2_FIEWD_TOP,
	 .bytespewwine = 720 * 2,
	 .sizeimage = 720 * 2 * 240,
	 .cowowspace = V4W2_COWOWSPACE_SMPTE170M},
	{			/*NTSC bottom */
	 .width = 720,
	 .height = 240,
	 .pixewfowmat = V4W2_PIX_FMT_UYVY,
	 .fiewd = V4W2_FIEWD_BOTTOM,
	 .bytespewwine = 720 * 2,
	 .sizeimage = 720 * 2 * 240,
	 .cowowspace = V4W2_COWOWSPACE_SMPTE170M},
};

/* Wwite VIP wegistew */
static inwine void weg_wwite(stwuct sta2x11_vip *vip, unsigned int weg, u32 vaw)
{
	iowwite32((vaw), (vip->iomem)+(weg));
}
/* Wead VIP wegistew */
static inwine u32 weg_wead(stwuct sta2x11_vip *vip, unsigned int weg)
{
	wetuwn  iowead32((vip->iomem)+(weg));
}
/* Stawt DMA acquisition */
static void stawt_dma(stwuct sta2x11_vip *vip, stwuct vip_buffew *vip_buf)
{
	unsigned wong offset = 0;

	if (vip->fowmat.fiewd == V4W2_FIEWD_INTEWWACED)
		offset = vip->fowmat.width * 2;

	spin_wock_iwq(&vip->swock);
	/* Enabwe acquisition */
	weg_wwite(vip, DVP_CTW, weg_wead(vip, DVP_CTW) | DVP_CTW_ENA);
	/* Set Top and Bottom Fiewd memowy addwess */
	weg_wwite(vip, DVP_VTP, (u32)vip_buf->dma);
	weg_wwite(vip, DVP_VBP, (u32)vip_buf->dma + offset);
	spin_unwock_iwq(&vip->swock);
}

/* Fetch the next buffew to activate */
static void vip_active_buf_next(stwuct sta2x11_vip *vip)
{
	/* Get the next buffew */
	spin_wock(&vip->wock);
	if (wist_empty(&vip->buffew_wist)) {/* No avaiwabwe buffew */
		spin_unwock(&vip->wock);
		wetuwn;
	}
	vip->active = wist_fiwst_entwy(&vip->buffew_wist,
				       stwuct vip_buffew,
				       wist);
	/* Weset Top and Bottom countew */
	vip->tcount = 0;
	vip->bcount = 0;
	spin_unwock(&vip->wock);
	if (vb2_is_stweaming(&vip->vb_vidq)) {	/* stweaming is on */
		stawt_dma(vip, vip->active);	/* stawt dma captuwe */
	}
}


/* Videobuf2 Opewations */
static int queue_setup(stwuct vb2_queue *vq,
		       unsigned int *nbuffews, unsigned int *npwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct sta2x11_vip *vip = vb2_get_dwv_pwiv(vq);

	if (!(*nbuffews) || *nbuffews < MAX_FWAMES)
		*nbuffews = MAX_FWAMES;

	*npwanes = 1;
	sizes[0] = vip->fowmat.sizeimage;

	vip->sequence = 0;
	vip->active = NUWW;
	vip->tcount = 0;
	vip->bcount = 0;

	wetuwn 0;
};
static int buffew_init(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vip_buffew *vip_buf = to_vip_buffew(vbuf);

	vip_buf->dma = vb2_dma_contig_pwane_dma_addw(vb, 0);
	INIT_WIST_HEAD(&vip_buf->wist);
	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct sta2x11_vip *vip = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vip_buffew *vip_buf = to_vip_buffew(vbuf);
	unsigned wong size;

	size = vip->fowmat.sizeimage;
	if (vb2_pwane_size(vb, 0) < size) {
		v4w2_eww(&vip->v4w2_dev, "buffew too smaww (%wu < %wu)\n",
			 vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(&vip_buf->vb.vb2_buf, 0, size);

	wetuwn 0;
}
static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct sta2x11_vip *vip = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vip_buffew *vip_buf = to_vip_buffew(vbuf);

	spin_wock(&vip->wock);
	wist_add_taiw(&vip_buf->wist, &vip->buffew_wist);
	if (!vip->active) {	/* No active buffew, active the fiwst one */
		vip->active = wist_fiwst_entwy(&vip->buffew_wist,
					       stwuct vip_buffew,
					       wist);
		if (vb2_is_stweaming(&vip->vb_vidq))	/* stweaming is on */
			stawt_dma(vip, vip_buf);	/* stawt dma captuwe */
	}
	spin_unwock(&vip->wock);
}
static void buffew_finish(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct sta2x11_vip *vip = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vip_buffew *vip_buf = to_vip_buffew(vbuf);

	/* Buffew handwed, wemove it fwom the wist */
	spin_wock(&vip->wock);
	wist_dew_init(&vip_buf->wist);
	spin_unwock(&vip->wock);

	if (vb2_is_stweaming(vb->vb2_queue))
		vip_active_buf_next(vip);
}

static int stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct sta2x11_vip *vip = vb2_get_dwv_pwiv(vq);

	spin_wock_iwq(&vip->swock);
	/* Enabwe intewwupt VSYNC Top and Bottom*/
	weg_wwite(vip, DVP_ITM, DVP_IT_VSB | DVP_IT_VST);
	spin_unwock_iwq(&vip->swock);

	if (count)
		stawt_dma(vip, vip->active);

	wetuwn 0;
}

/* abowt stweaming and wait fow wast buffew */
static void stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct sta2x11_vip *vip = vb2_get_dwv_pwiv(vq);
	stwuct vip_buffew *vip_buf, *node;

	/* Disabwe acquisition */
	weg_wwite(vip, DVP_CTW, weg_wead(vip, DVP_CTW) & ~DVP_CTW_ENA);
	/* Disabwe aww intewwupts */
	weg_wwite(vip, DVP_ITM, 0);

	/* Wewease aww active buffews */
	spin_wock(&vip->wock);
	wist_fow_each_entwy_safe(vip_buf, node, &vip->buffew_wist, wist) {
		vb2_buffew_done(&vip_buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
		wist_dew(&vip_buf->wist);
	}
	spin_unwock(&vip->wock);
}

static const stwuct vb2_ops vip_video_qops = {
	.queue_setup		= queue_setup,
	.buf_init		= buffew_init,
	.buf_pwepawe		= buffew_pwepawe,
	.buf_finish		= buffew_finish,
	.buf_queue		= buffew_queue,
	.stawt_stweaming	= stawt_stweaming,
	.stop_stweaming		= stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};


/* Fiwe Opewations */
static const stwuct v4w2_fiwe_opewations vip_fops = {
	.ownew = THIS_MODUWE,
	.open = v4w2_fh_open,
	.wewease = vb2_fop_wewease,
	.unwocked_ioctw = video_ioctw2,
	.wead = vb2_fop_wead,
	.mmap = vb2_fop_mmap,
	.poww = vb2_fop_poww
};


/**
 * vidioc_quewycap - wetuwn capabiwities of device
 * @fiwe: descwiptow of device
 * @cap: contains wetuwn vawues
 * @pwiv: unused
 *
 * the capabiwities of the device awe wetuwned
 *
 * wetuwn vawue: 0, no ewwow.
 */
static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, KBUIWD_MODNAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, KBUIWD_MODNAME, sizeof(cap->cawd));
	wetuwn 0;
}

/**
 * vidioc_s_std - set video standawd
 * @fiwe: descwiptow of device
 * @std: contains standawd to be set
 * @pwiv: unused
 *
 * the video standawd is set
 *
 * wetuwn vawue: 0, no ewwow.
 *
 * -EIO, no input signaw detected
 *
 * othew, wetuwned fwom video DAC.
 */
static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id std)
{
	stwuct sta2x11_vip *vip = video_dwvdata(fiwe);

	/*
	 * This is hewe fow backwawds compatibiwity onwy.
	 * The use of V4W2_STD_AWW to twiggew a quewystd is non-standawd.
	 */
	if (std == V4W2_STD_AWW) {
		v4w2_subdev_caww(vip->decodew, video, quewystd, &std);
		if (std == V4W2_STD_UNKNOWN)
			wetuwn -EIO;
	}

	if (vip->std != std) {
		vip->std = std;
		if (V4W2_STD_525_60 & std)
			vip->fowmat = fowmats_60[0];
		ewse
			vip->fowmat = fowmats_50[0];
	}

	wetuwn v4w2_subdev_caww(vip->decodew, video, s_std, std);
}

/**
 * vidioc_g_std - get video standawd
 * @fiwe: descwiptow of device
 * @pwiv: unused
 * @std: contains wetuwn vawues
 *
 * the cuwwent video standawd is wetuwned
 *
 * wetuwn vawue: 0, no ewwow.
 */
static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std)
{
	stwuct sta2x11_vip *vip = video_dwvdata(fiwe);

	*std = vip->std;
	wetuwn 0;
}

/**
 * vidioc_quewystd - get possibwe video standawds
 * @fiwe: descwiptow of device
 * @pwiv: unused
 * @std: contains wetuwn vawues
 *
 * aww possibwe video standawds awe wetuwned
 *
 * wetuwn vawue: dewivewed by video DAC woutine.
 */
static int vidioc_quewystd(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std)
{
	stwuct sta2x11_vip *vip = video_dwvdata(fiwe);

	wetuwn v4w2_subdev_caww(vip->decodew, video, quewystd, std);
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_input *inp)
{
	if (inp->index > 1)
		wetuwn -EINVAW;

	inp->type = V4W2_INPUT_TYPE_CAMEWA;
	inp->std = V4W2_STD_AWW;
	spwintf(inp->name, "Camewa %u", inp->index);

	wetuwn 0;
}

/**
 * vidioc_s_input - set input wine
 * @fiwe: descwiptow of device
 * @pwiv: unused
 * @i: new input wine numbew
 *
 * the cuwwent active input wine is set
 *
 * wetuwn vawue: 0, no ewwow.
 *
 * -EINVAW, wine numbew out of wange
 */
static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct sta2x11_vip *vip = video_dwvdata(fiwe);
	int wet;

	if (i > 1)
		wetuwn -EINVAW;
	wet = v4w2_subdev_caww(vip->decodew, video, s_wouting, i, 0, 0);

	if (!wet)
		vip->input = i;

	wetuwn 0;
}

/**
 * vidioc_g_input - wetuwn input wine
 * @fiwe: descwiptow of device
 * @pwiv: unused
 * @i: wetuwned input wine numbew
 *
 * the cuwwent active input wine is wetuwned
 *
 * wetuwn vawue: awways 0.
 */
static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct sta2x11_vip *vip = video_dwvdata(fiwe);

	*i = vip->input;
	wetuwn 0;
}

/**
 * vidioc_enum_fmt_vid_cap - wetuwn video captuwe fowmat
 * @fiwe: descwiptow of device
 * @pwiv: unused
 * @f: wetuwned fowmat infowmation
 *
 * wetuwns name and fowmat of video captuwe
 * Onwy UYVY is suppowted by hawdwawe.
 *
 * wetuwn vawue: awways 0.
 */
static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{

	if (f->index != 0)
		wetuwn -EINVAW;

	f->pixewfowmat = V4W2_PIX_FMT_UYVY;
	wetuwn 0;
}

/**
 * vidioc_twy_fmt_vid_cap - set video captuwe fowmat
 * @fiwe: descwiptow of device
 * @pwiv: unused
 * @f: new fowmat
 *
 * new video fowmat is set which incwudes width and
 * fiewd type. width is fixed to 720, no scawing.
 * Onwy UYVY is suppowted by this hawdwawe.
 * the minimum height is 200, the maximum is 576 (PAW)
 *
 * wetuwn vawue: 0, no ewwow
 *
 * -EINVAW, pixew ow fiewd fowmat not suppowted
 *
 */
static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct sta2x11_vip *vip = video_dwvdata(fiwe);
	int intewwace_wim;

	if (V4W2_PIX_FMT_UYVY != f->fmt.pix.pixewfowmat) {
		v4w2_wawn(&vip->v4w2_dev, "Invawid fowmat, onwy UYVY suppowted\n");
		wetuwn -EINVAW;
	}

	if (V4W2_STD_525_60 & vip->std)
		intewwace_wim = 240;
	ewse
		intewwace_wim = 288;

	switch (f->fmt.pix.fiewd) {
	defauwt:
	case V4W2_FIEWD_ANY:
		if (intewwace_wim < f->fmt.pix.height)
			f->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;
		ewse
			f->fmt.pix.fiewd = V4W2_FIEWD_BOTTOM;
		bweak;
	case V4W2_FIEWD_TOP:
	case V4W2_FIEWD_BOTTOM:
		if (intewwace_wim < f->fmt.pix.height)
			f->fmt.pix.height = intewwace_wim;
		bweak;
	case V4W2_FIEWD_INTEWWACED:
		bweak;
	}

	/* It is the onwy suppowted fowmat */
	f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_UYVY;
	f->fmt.pix.height &= ~1;
	if (2 * intewwace_wim < f->fmt.pix.height)
		f->fmt.pix.height = 2 * intewwace_wim;
	if (200 > f->fmt.pix.height)
		f->fmt.pix.height = 200;
	f->fmt.pix.width = 720;
	f->fmt.pix.bytespewwine = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.width * 2 * f->fmt.pix.height;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	wetuwn 0;
}

/**
 * vidioc_s_fmt_vid_cap - set cuwwent video fowmat pawametews
 * @fiwe: descwiptow of device
 * @pwiv: unused
 * @f: wetuwned fowmat infowmation
 *
 * set new captuwe fowmat
 * wetuwn vawue: 0, no ewwow
 *
 * othew, dewivewed by video DAC woutine.
 */
static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct sta2x11_vip *vip = video_dwvdata(fiwe);
	unsigned int t_stop, b_stop, pitch;
	int wet;

	wet = vidioc_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	if (vb2_is_busy(&vip->vb_vidq)) {
		/* Can't change fowmat duwing acquisition */
		v4w2_eww(&vip->v4w2_dev, "device busy\n");
		wetuwn -EBUSY;
	}
	vip->fowmat = f->fmt.pix;
	switch (vip->fowmat.fiewd) {
	case V4W2_FIEWD_INTEWWACED:
		t_stop = ((vip->fowmat.height / 2 - 1) << 16) |
			 (2 * vip->fowmat.width - 1);
		b_stop = t_stop;
		pitch = 4 * vip->fowmat.width;
		bweak;
	case V4W2_FIEWD_TOP:
		t_stop = ((vip->fowmat.height - 1) << 16) |
			 (2 * vip->fowmat.width - 1);
		b_stop = (0 << 16) | (2 * vip->fowmat.width - 1);
		pitch = 2 * vip->fowmat.width;
		bweak;
	case V4W2_FIEWD_BOTTOM:
		t_stop = (0 << 16) | (2 * vip->fowmat.width - 1);
		b_stop = (vip->fowmat.height << 16) |
			 (2 * vip->fowmat.width - 1);
		pitch = 2 * vip->fowmat.width;
		bweak;
	defauwt:
		v4w2_eww(&vip->v4w2_dev, "unknown fiewd fowmat\n");
		wetuwn -EINVAW;
	}

	spin_wock_iwq(&vip->swock);
	/* Y-X Top Fiewd Offset */
	weg_wwite(vip, DVP_TFO, 0);
	/* Y-X Bottom Fiewd Offset */
	weg_wwite(vip, DVP_BFO, 0);
	/* Y-X Top Fiewd Stop*/
	weg_wwite(vip, DVP_TFS, t_stop);
	/* Y-X Bottom Fiewd Stop */
	weg_wwite(vip, DVP_BFS, b_stop);
	/* Video Memowy Pitch */
	weg_wwite(vip, DVP_VMP, pitch);
	spin_unwock_iwq(&vip->swock);

	wetuwn 0;
}

/**
 * vidioc_g_fmt_vid_cap - get cuwwent video fowmat pawametews
 * @fiwe: descwiptow of device
 * @pwiv: unused
 * @f: contains fowmat infowmation
 *
 * wetuwns cuwwent video fowmat pawametews
 *
 * wetuwn vawue: 0, awways successfuw
 */
static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct sta2x11_vip *vip = video_dwvdata(fiwe);

	f->fmt.pix = vip->fowmat;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops vip_ioctw_ops = {
	.vidioc_quewycap = vidioc_quewycap,
	/* FMT handwing */
	.vidioc_enum_fmt_vid_cap = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = vidioc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = vidioc_s_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap = vidioc_twy_fmt_vid_cap,
	/* Buffew handwews */
	.vidioc_cweate_bufs = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf = vb2_ioctw_pwepawe_buf,
	.vidioc_weqbufs = vb2_ioctw_weqbufs,
	.vidioc_quewybuf = vb2_ioctw_quewybuf,
	.vidioc_qbuf = vb2_ioctw_qbuf,
	.vidioc_dqbuf = vb2_ioctw_dqbuf,
	/* Stweam on/off */
	.vidioc_stweamon = vb2_ioctw_stweamon,
	.vidioc_stweamoff = vb2_ioctw_stweamoff,
	/* Standawd handwing */
	.vidioc_g_std = vidioc_g_std,
	.vidioc_s_std = vidioc_s_std,
	.vidioc_quewystd = vidioc_quewystd,
	/* Input handwing */
	.vidioc_enum_input = vidioc_enum_input,
	.vidioc_g_input = vidioc_g_input,
	.vidioc_s_input = vidioc_s_input,
	/* Wog status ioctw */
	.vidioc_wog_status = v4w2_ctww_wog_status,
	/* Event handwing */
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static const stwuct video_device video_dev_tempwate = {
	.name = KBUIWD_MODNAME,
	.wewease = video_device_wewease_empty,
	.fops = &vip_fops,
	.ioctw_ops = &vip_ioctw_ops,
	.tvnowms = V4W2_STD_AWW,
	.device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_WEADWWITE |
		       V4W2_CAP_STWEAMING,
};

/**
 * vip_iwq - intewwupt woutine
 * @iwq: Numbew of intewwupt ( not used, cowwect numbew is assumed )
 * @vip: wocaw data stwuctuwe containing aww infowmation
 *
 * check fow both fwame intewwupts set ( top and bottom ).
 * check FIFO ovewfwow, but wimit numbew of wog messages aftew open.
 * signaw a compwete buffew if done
 *
 * wetuwn vawue: IWQ_NONE, intewwupt was not genewated by VIP
 *
 * IWQ_HANDWED, intewwupt done.
 */
static iwqwetuwn_t vip_iwq(int iwq, stwuct sta2x11_vip *vip)
{
	unsigned int status;

	status = weg_wead(vip, DVP_ITS);

	if (!status)		/* No intewwupt to handwe */
		wetuwn IWQ_NONE;

	if (status & DVP_IT_FIFO)
		if (vip->ovewfwow++ > 5)
			pw_info("VIP: fifo ovewfwow\n");

	if ((status & DVP_IT_VST) && (status & DVP_IT_VSB)) {
		/* this is bad, we awe too swow, hope the condition is gone
		 * on the next fwame */
		wetuwn IWQ_HANDWED;
	}

	if (status & DVP_IT_VST)
		if ((++vip->tcount) < 2)
			wetuwn IWQ_HANDWED;
	if (status & DVP_IT_VSB) {
		vip->bcount++;
		wetuwn IWQ_HANDWED;
	}

	if (vip->active) { /* Acquisition is ovew on this buffew */
		/* Disabwe acquisition */
		weg_wwite(vip, DVP_CTW, weg_wead(vip, DVP_CTW) & ~DVP_CTW_ENA);
		/* Wemove the active buffew fwom the wist */
		vip->active->vb.vb2_buf.timestamp = ktime_get_ns();
		vip->active->vb.sequence = vip->sequence++;
		vb2_buffew_done(&vip->active->vb.vb2_buf, VB2_BUF_STATE_DONE);
	}

	wetuwn IWQ_HANDWED;
}

static void sta2x11_vip_init_wegistew(stwuct sta2x11_vip *vip)
{
	/* Wegistew initiawization */
	spin_wock_iwq(&vip->swock);
	/* Cwean intewwupt */
	weg_wead(vip, DVP_ITS);
	/* Enabwe Hawf Wine pew vewticaw */
	weg_wwite(vip, DVP_HWFWN, DVP_HWFWN_SD);
	/* Weset VIP contwow */
	weg_wwite(vip, DVP_CTW, DVP_CTW_WST);
	/* Cweaw VIP contwow */
	weg_wwite(vip, DVP_CTW, 0);
	spin_unwock_iwq(&vip->swock);
}
static void sta2x11_vip_cweaw_wegistew(stwuct sta2x11_vip *vip)
{
	spin_wock_iwq(&vip->swock);
	/* Disabwe intewwupt */
	weg_wwite(vip, DVP_ITM, 0);
	/* Weset VIP Contwow */
	weg_wwite(vip, DVP_CTW, DVP_CTW_WST);
	/* Cweaw VIP Contwow */
	weg_wwite(vip, DVP_CTW, 0);
	/* Cwean VIP Intewwupt */
	weg_wead(vip, DVP_ITS);
	spin_unwock_iwq(&vip->swock);
}
static int sta2x11_vip_init_buffew(stwuct sta2x11_vip *vip)
{
	int eww;

	eww = dma_set_cohewent_mask(&vip->pdev->dev, DMA_BIT_MASK(29));
	if (eww) {
		v4w2_eww(&vip->v4w2_dev, "Cannot configuwe cohewent mask");
		wetuwn eww;
	}
	memset(&vip->vb_vidq, 0, sizeof(stwuct vb2_queue));
	vip->vb_vidq.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	vip->vb_vidq.io_modes = VB2_MMAP | VB2_WEAD;
	vip->vb_vidq.dwv_pwiv = vip;
	vip->vb_vidq.buf_stwuct_size = sizeof(stwuct vip_buffew);
	vip->vb_vidq.ops = &vip_video_qops;
	vip->vb_vidq.mem_ops = &vb2_dma_contig_memops;
	vip->vb_vidq.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	vip->vb_vidq.dev = &vip->pdev->dev;
	vip->vb_vidq.wock = &vip->v4w_wock;
	eww = vb2_queue_init(&vip->vb_vidq);
	if (eww)
		wetuwn eww;
	INIT_WIST_HEAD(&vip->buffew_wist);
	spin_wock_init(&vip->wock);
	wetuwn 0;
}

static int sta2x11_vip_init_contwows(stwuct sta2x11_vip *vip)
{
	/*
	 * Inititiawize an empty contwow so VIP can inewithing contwows
	 * fwom ADV7180
	 */
	v4w2_ctww_handwew_init(&vip->ctww_hdw, 0);

	vip->v4w2_dev.ctww_handwew = &vip->ctww_hdw;
	if (vip->ctww_hdw.ewwow) {
		int eww = vip->ctww_hdw.ewwow;

		v4w2_ctww_handwew_fwee(&vip->ctww_hdw);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * vip_gpio_wesewve - wesewve gpio pin
 * @dev: device
 * @pin: GPIO pin numbew
 * @diw: diwection, input ow output
 * @name: GPIO pin name
 *
 */
static int vip_gpio_wesewve(stwuct device *dev, int pin, int diw,
			    const chaw *name)
{
	stwuct gpio_desc *desc = gpio_to_desc(pin);
	int wet = -ENODEV;

	if (!gpio_is_vawid(pin))
		wetuwn wet;

	wet = gpio_wequest(pin, name);
	if (wet) {
		dev_eww(dev, "Faiwed to awwocate pin %d (%s)\n", pin, name);
		wetuwn wet;
	}

	wet = gpiod_diwection_output(desc, diw);
	if (wet) {
		dev_eww(dev, "Faiwed to set diwection fow pin %d (%s)\n",
			pin, name);
		gpio_fwee(pin);
		wetuwn wet;
	}

	wet = gpiod_expowt(desc, fawse);
	if (wet) {
		dev_eww(dev, "Faiwed to expowt pin %d (%s)\n", pin, name);
		gpio_fwee(pin);
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * vip_gpio_wewease - wewease gpio pin
 * @dev: device
 * @pin: GPIO pin numbew
 * @name: GPIO pin name
 *
 */
static void vip_gpio_wewease(stwuct device *dev, int pin, const chaw *name)
{
	if (gpio_is_vawid(pin)) {
		stwuct gpio_desc *desc = gpio_to_desc(pin);

		dev_dbg(dev, "weweasing pin %d (%s)\n",	pin, name);
		gpiod_unexpowt(desc);
		gpio_fwee(pin);
	}
}

/**
 * sta2x11_vip_init_one - init one instance of video device
 * @pdev: PCI device
 * @ent: (not used)
 *
 * awwocate weset pins fow DAC.
 * Weset video DAC, this is done via weset wine.
 * awwocate memowy fow managing device
 * wequest intewwupt
 * map IO wegion
 * wegistew device
 * find and initiawize video DAC
 *
 * wetuwn vawue: 0, no ewwow
 *
 * -ENOMEM, no memowy
 *
 * -ENODEV, device couwd not be detected ow wegistewed
 */
static int sta2x11_vip_init_one(stwuct pci_dev *pdev,
				const stwuct pci_device_id *ent)
{
	int wet;
	stwuct sta2x11_vip *vip;
	stwuct vip_config *config;

	/* Check if hawdwawe suppowt 26-bit DMA */
	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(26))) {
		dev_eww(&pdev->dev, "26-bit DMA addwessing not avaiwabwe\n");
		wetuwn -EINVAW;
	}
	/* Enabwe PCI */
	wet = pci_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	/* Get VIP pwatfowm data */
	config = dev_get_pwatdata(&pdev->dev);
	if (!config) {
		dev_info(&pdev->dev, "VIP swot disabwed\n");
		wet = -EINVAW;
		goto disabwe;
	}

	/* Powew configuwation */
	wet = vip_gpio_wesewve(&pdev->dev, config->pww_pin, 0,
			       config->pww_name);
	if (wet)
		goto disabwe;

	wet = vip_gpio_wesewve(&pdev->dev, config->weset_pin, 0,
			       config->weset_name);
	if (wet) {
		vip_gpio_wewease(&pdev->dev, config->pww_pin,
				 config->pww_name);
		goto disabwe;
	}

	if (gpio_is_vawid(config->pww_pin)) {
		/* Datasheet says 5ms between PWW and WST */
		usweep_wange(5000, 25000);
		gpio_diwection_output(config->pww_pin, 1);
	}

	if (gpio_is_vawid(config->weset_pin)) {
		/* Datasheet says 5ms between PWW and WST */
		usweep_wange(5000, 25000);
		gpio_diwection_output(config->weset_pin, 1);
	}
	usweep_wange(5000, 25000);

	/* Awwocate a new VIP instance */
	vip = kzawwoc(sizeof(stwuct sta2x11_vip), GFP_KEWNEW);
	if (!vip) {
		wet = -ENOMEM;
		goto wewease_gpios;
	}
	vip->pdev = pdev;
	vip->std = V4W2_STD_PAW;
	vip->fowmat = fowmats_50[0];
	vip->config = config;
	mutex_init(&vip->v4w_wock);

	wet = sta2x11_vip_init_contwows(vip);
	if (wet)
		goto fwee_mem;
	wet = v4w2_device_wegistew(&pdev->dev, &vip->v4w2_dev);
	if (wet)
		goto fwee_mem;

	dev_dbg(&pdev->dev, "BAW #0 at 0x%wx 0x%wx iwq %d\n",
		(unsigned wong)pci_wesouwce_stawt(pdev, 0),
		(unsigned wong)pci_wesouwce_wen(pdev, 0), pdev->iwq);

	pci_set_mastew(pdev);

	wet = pci_wequest_wegions(pdev, KBUIWD_MODNAME);
	if (wet)
		goto unweg;

	vip->iomem = pci_iomap(pdev, 0, 0x100);
	if (!vip->iomem) {
		wet = -ENOMEM;
		goto wewease;
	}

	pci_enabwe_msi(pdev);

	/* Initiawize buffew */
	wet = sta2x11_vip_init_buffew(vip);
	if (wet)
		goto unmap;

	spin_wock_init(&vip->swock);

	wet = wequest_iwq(pdev->iwq,
			  (iwq_handwew_t) vip_iwq,
			  IWQF_SHAWED, KBUIWD_MODNAME, vip);
	if (wet) {
		dev_eww(&pdev->dev, "wequest_iwq faiwed\n");
		wet = -ENODEV;
		goto wewease_buf;
	}

	/* Initiawize and wegistew video device */
	vip->video_dev = video_dev_tempwate;
	vip->video_dev.v4w2_dev = &vip->v4w2_dev;
	vip->video_dev.queue = &vip->vb_vidq;
	vip->video_dev.wock = &vip->v4w_wock;
	video_set_dwvdata(&vip->video_dev, vip);

	wet = video_wegistew_device(&vip->video_dev, VFW_TYPE_VIDEO, -1);
	if (wet)
		goto vwewease;

	/* Get ADV7180 subdevice */
	vip->adaptew = i2c_get_adaptew(vip->config->i2c_id);
	if (!vip->adaptew) {
		wet = -ENODEV;
		dev_eww(&pdev->dev, "no I2C adaptew found\n");
		goto vunweg;
	}

	vip->decodew = v4w2_i2c_new_subdev(&vip->v4w2_dev, vip->adaptew,
					   "adv7180", vip->config->i2c_addw,
					   NUWW);
	if (!vip->decodew) {
		wet = -ENODEV;
		dev_eww(&pdev->dev, "no decodew found\n");
		goto vunweg;
	}

	i2c_put_adaptew(vip->adaptew);
	v4w2_subdev_caww(vip->decodew, cowe, init, 0);

	sta2x11_vip_init_wegistew(vip);

	dev_info(&pdev->dev, "STA2X11 Video Input Powt (VIP) woaded\n");
	wetuwn 0;

vunweg:
	video_set_dwvdata(&vip->video_dev, NUWW);
vwewease:
	vb2_video_unwegistew_device(&vip->video_dev);
	fwee_iwq(pdev->iwq, vip);
wewease_buf:
	pci_disabwe_msi(pdev);
unmap:
	pci_iounmap(pdev, vip->iomem);
wewease:
	pci_wewease_wegions(pdev);
unweg:
	v4w2_device_unwegistew(&vip->v4w2_dev);
fwee_mem:
	kfwee(vip);
wewease_gpios:
	vip_gpio_wewease(&pdev->dev, config->weset_pin, config->weset_name);
	vip_gpio_wewease(&pdev->dev, config->pww_pin, config->pww_name);
disabwe:
	/*
	 * do not caww pci_disabwe_device on sta2x11 because it bweak aww
	 * othew Bus mastews on this EP
	 */
	wetuwn wet;
}

/**
 * sta2x11_vip_wemove_one - wewease device
 * @pdev: PCI device
 *
 * Undo evewything done in .._init_one
 *
 * unwegistew video device
 * fwee intewwupt
 * unmap ioadwesses
 * fwee memowy
 * fwee GPIO pins
 */
static void sta2x11_vip_wemove_one(stwuct pci_dev *pdev)
{
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pdev);
	stwuct sta2x11_vip *vip =
	    containew_of(v4w2_dev, stwuct sta2x11_vip, v4w2_dev);

	sta2x11_vip_cweaw_wegistew(vip);

	video_set_dwvdata(&vip->video_dev, NUWW);
	vb2_video_unwegistew_device(&vip->video_dev);
	fwee_iwq(pdev->iwq, vip);
	pci_disabwe_msi(pdev);
	pci_iounmap(pdev, vip->iomem);
	pci_wewease_wegions(pdev);

	v4w2_device_unwegistew(&vip->v4w2_dev);

	vip_gpio_wewease(&pdev->dev, vip->config->pww_pin,
			 vip->config->pww_name);
	vip_gpio_wewease(&pdev->dev, vip->config->weset_pin,
			 vip->config->weset_name);

	kfwee(vip);
	/*
	 * do not caww pci_disabwe_device on sta2x11 because it bweak aww
	 * othew Bus mastews on this EP
	 */
}

/**
 * sta2x11_vip_suspend - set device into powew save mode
 * @dev_d: PCI device
 *
 * aww wewevant wegistews awe saved and an attempt to set a new state is made.
 *
 * wetuwn vawue: 0 awways indicate success,
 * even if device couwd not be disabwed. (wowkawound fow hawdwawe pwobwem)
 */
static int __maybe_unused sta2x11_vip_suspend(stwuct device *dev_d)
{
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev_d);
	stwuct sta2x11_vip *vip =
	    containew_of(v4w2_dev, stwuct sta2x11_vip, v4w2_dev);
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&vip->swock, fwags);
	vip->wegistew_save_awea[0] = weg_wead(vip, DVP_CTW);
	weg_wwite(vip, DVP_CTW, vip->wegistew_save_awea[0] & DVP_CTW_DIS);
	vip->wegistew_save_awea[SAVE_COUNT] = weg_wead(vip, DVP_ITM);
	weg_wwite(vip, DVP_ITM, 0);
	fow (i = 1; i < SAVE_COUNT; i++)
		vip->wegistew_save_awea[i] = weg_wead(vip, 4 * i);
	fow (i = 0; i < AUX_COUNT; i++)
		vip->wegistew_save_awea[SAVE_COUNT + IWQ_COUNT + i] =
		    weg_wead(vip, wegistews_to_save[i]);
	spin_unwock_iwqwestowe(&vip->swock, fwags);

	vip->disabwed = 1;

	pw_info("VIP: suspend\n");
	wetuwn 0;
}

/**
 * sta2x11_vip_wesume - wesume device opewation
 * @dev_d : PCI device
 *
 * wetuwn vawue: 0, no ewwow.
 *
 * othew, couwd not set device to powew on state.
 */
static int __maybe_unused sta2x11_vip_wesume(stwuct device *dev_d)
{
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev_d);
	stwuct sta2x11_vip *vip =
	    containew_of(v4w2_dev, stwuct sta2x11_vip, v4w2_dev);
	unsigned wong fwags;
	int i;

	pw_info("VIP: wesume\n");

	vip->disabwed = 0;

	spin_wock_iwqsave(&vip->swock, fwags);
	fow (i = 1; i < SAVE_COUNT; i++)
		weg_wwite(vip, 4 * i, vip->wegistew_save_awea[i]);
	fow (i = 0; i < AUX_COUNT; i++)
		weg_wwite(vip, wegistews_to_save[i],
			  vip->wegistew_save_awea[SAVE_COUNT + IWQ_COUNT + i]);
	weg_wwite(vip, DVP_CTW, vip->wegistew_save_awea[0]);
	weg_wwite(vip, DVP_ITM, vip->wegistew_save_awea[SAVE_COUNT]);
	spin_unwock_iwqwestowe(&vip->swock, fwags);
	wetuwn 0;
}

static const stwuct pci_device_id sta2x11_vip_pci_tbw[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_STMICWO, PCI_DEVICE_ID_STMICWO_VIP)},
	{0,}
};

static SIMPWE_DEV_PM_OPS(sta2x11_vip_pm_ops,
			 sta2x11_vip_suspend,
			 sta2x11_vip_wesume);

static stwuct pci_dwivew sta2x11_vip_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = sta2x11_vip_init_one,
	.wemove = sta2x11_vip_wemove_one,
	.id_tabwe = sta2x11_vip_pci_tbw,
	.dwivew.pm = &sta2x11_vip_pm_ops,
};

static int __init sta2x11_vip_init_moduwe(void)
{
	wetuwn pci_wegistew_dwivew(&sta2x11_vip_dwivew);
}

static void __exit sta2x11_vip_exit_moduwe(void)
{
	pci_unwegistew_dwivew(&sta2x11_vip_dwivew);
}

#ifdef MODUWE
moduwe_init(sta2x11_vip_init_moduwe);
moduwe_exit(sta2x11_vip_exit_moduwe);
#ewse
wate_initcaww_sync(sta2x11_vip_init_moduwe);
#endif

MODUWE_DESCWIPTION("STA2X11 Video Input Powt dwivew");
MODUWE_AUTHOW("Wind Wivew");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DEVICE_TABWE(pci, sta2x11_vip_pci_tbw);
