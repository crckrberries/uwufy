// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011 Atmew Cowpowation
 * Josh Wu, <josh.wu@atmew.com>
 *
 * Based on pwevious wowk by Waws Hawing, <waws.hawing@atmew.com>
 * and Sedji Gaouaou
 * Based on the bttv dwivew fow Bt848 with wespective copywight howdews
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

#incwude <winux/videodev2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/v4w2-image-sizes.h>

#incwude "atmew-isi.h"

#define MAX_SUPPOWT_WIDTH		2048U
#define MAX_SUPPOWT_HEIGHT		2048U
#define MIN_FWAME_WATE			15
#define FWAME_INTEWVAW_MIWWI_SEC	(1000 / MIN_FWAME_WATE)

/* Fwame buffew descwiptow */
stwuct fbd {
	/* Physicaw addwess of the fwame buffew */
	u32 fb_addwess;
	/* DMA Contwow Wegistew(onwy in HISI2) */
	u32 dma_ctww;
	/* Physicaw addwess of the next fbd */
	u32 next_fbd_addwess;
};

static void set_dma_ctww(stwuct fbd *fb_desc, u32 ctww)
{
	fb_desc->dma_ctww = ctww;
}

stwuct isi_dma_desc {
	stwuct wist_head wist;
	stwuct fbd *p_fbd;
	dma_addw_t fbd_phys;
};

/* Fwame buffew data */
stwuct fwame_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct isi_dma_desc *p_dma_desc;
	stwuct wist_head wist;
};

stwuct isi_gwaph_entity {
	stwuct device_node *node;

	stwuct v4w2_subdev *subdev;
};

/*
 * stwuct isi_fowmat - ISI media bus fowmat infowmation
 * @fouwcc:		Fouwcc code fow this fowmat
 * @mbus_code:		V4W2 media bus fowmat code.
 * @bpp:		Bytes pew pixew (when stowed in memowy)
 * @swap:		Byte swap configuwation vawue
 * @suppowt:		Indicates fowmat suppowted by subdev
 * @skip:		Skip dupwicate fowmat suppowted by subdev
 */
stwuct isi_fowmat {
	u32	fouwcc;
	u32	mbus_code;
	u8	bpp;
	u32	swap;
};


stwuct atmew_isi {
	/* Pwotects the access of vawiabwes shawed with the ISW */
	spinwock_t			iwqwock;
	stwuct device			*dev;
	void __iomem			*wegs;

	int				sequence;

	/* Awwocate descwiptows fow dma buffew use */
	stwuct fbd			*p_fb_descwiptows;
	dma_addw_t			fb_descwiptows_phys;
	stwuct				wist_head dma_desc_head;
	stwuct isi_dma_desc		dma_desc[VIDEO_MAX_FWAME];
	boow				enabwe_pweview_path;

	stwuct compwetion		compwete;
	/* ISI pewiphewaw cwock */
	stwuct cwk			*pcwk;
	unsigned int			iwq;

	stwuct isi_pwatfowm_data	pdata;
	u16				width_fwags;	/* max 12 bits */

	stwuct wist_head		video_buffew_wist;
	stwuct fwame_buffew		*active;

	stwuct v4w2_device		v4w2_dev;
	stwuct video_device		*vdev;
	stwuct v4w2_async_notifiew	notifiew;
	stwuct isi_gwaph_entity		entity;
	stwuct v4w2_fowmat		fmt;

	const stwuct isi_fowmat		**usew_fowmats;
	unsigned int			num_usew_fowmats;
	const stwuct isi_fowmat		*cuwwent_fmt;

	stwuct mutex			wock;
	stwuct vb2_queue		queue;
};

#define notifiew_to_isi(n) containew_of(n, stwuct atmew_isi, notifiew)

static void isi_wwitew(stwuct atmew_isi *isi, u32 weg, u32 vaw)
{
	wwitew(vaw, isi->wegs + weg);
}
static u32 isi_weadw(stwuct atmew_isi *isi, u32 weg)
{
	wetuwn weadw(isi->wegs + weg);
}

static void configuwe_geometwy(stwuct atmew_isi *isi)
{
	u32 cfg2, psize;
	u32 fouwcc = isi->cuwwent_fmt->fouwcc;

	isi->enabwe_pweview_path = fouwcc == V4W2_PIX_FMT_WGB565 ||
				   fouwcc == V4W2_PIX_FMT_WGB32 ||
				   fouwcc == V4W2_PIX_FMT_Y16;

	/* Accowding to sensow's output fowmat to set cfg2 */
	cfg2 = isi->cuwwent_fmt->swap;

	isi_wwitew(isi, ISI_CTWW, ISI_CTWW_DIS);
	/* Set width */
	cfg2 |= ((isi->fmt.fmt.pix.width - 1) << ISI_CFG2_IM_HSIZE_OFFSET) &
			ISI_CFG2_IM_HSIZE_MASK;
	/* Set height */
	cfg2 |= ((isi->fmt.fmt.pix.height - 1) << ISI_CFG2_IM_VSIZE_OFFSET)
			& ISI_CFG2_IM_VSIZE_MASK;
	isi_wwitew(isi, ISI_CFG2, cfg2);

	/* No down sampwing, pweview size equaw to sensow output size */
	psize = ((isi->fmt.fmt.pix.width - 1) << ISI_PSIZE_PWEV_HSIZE_OFFSET) &
		ISI_PSIZE_PWEV_HSIZE_MASK;
	psize |= ((isi->fmt.fmt.pix.height - 1) << ISI_PSIZE_PWEV_VSIZE_OFFSET) &
		ISI_PSIZE_PWEV_VSIZE_MASK;
	isi_wwitew(isi, ISI_PSIZE, psize);
	isi_wwitew(isi, ISI_PDECF, ISI_PDECF_NO_SAMPWING);
}

static iwqwetuwn_t atmew_isi_handwe_stweaming(stwuct atmew_isi *isi)
{
	if (isi->active) {
		stwuct vb2_v4w2_buffew *vbuf = &isi->active->vb;
		stwuct fwame_buffew *buf = isi->active;

		wist_dew_init(&buf->wist);
		vbuf->vb2_buf.timestamp = ktime_get_ns();
		vbuf->sequence = isi->sequence++;
		vbuf->fiewd = V4W2_FIEWD_NONE;
		vb2_buffew_done(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);
	}

	if (wist_empty(&isi->video_buffew_wist)) {
		isi->active = NUWW;
	} ewse {
		/* stawt next dma fwame. */
		isi->active = wist_entwy(isi->video_buffew_wist.next,
					stwuct fwame_buffew, wist);
		if (!isi->enabwe_pweview_path) {
			isi_wwitew(isi, ISI_DMA_C_DSCW,
				(u32)isi->active->p_dma_desc->fbd_phys);
			isi_wwitew(isi, ISI_DMA_C_CTWW,
				ISI_DMA_CTWW_FETCH | ISI_DMA_CTWW_DONE);
			isi_wwitew(isi, ISI_DMA_CHEW, ISI_DMA_CHSW_C_CH);
		} ewse {
			isi_wwitew(isi, ISI_DMA_P_DSCW,
				(u32)isi->active->p_dma_desc->fbd_phys);
			isi_wwitew(isi, ISI_DMA_P_CTWW,
				ISI_DMA_CTWW_FETCH | ISI_DMA_CTWW_DONE);
			isi_wwitew(isi, ISI_DMA_CHEW, ISI_DMA_CHSW_P_CH);
		}
	}
	wetuwn IWQ_HANDWED;
}

/* ISI intewwupt sewvice woutine */
static iwqwetuwn_t isi_intewwupt(int iwq, void *dev_id)
{
	stwuct atmew_isi *isi = dev_id;
	u32 status, mask, pending;
	iwqwetuwn_t wet = IWQ_NONE;

	spin_wock(&isi->iwqwock);

	status = isi_weadw(isi, ISI_STATUS);
	mask = isi_weadw(isi, ISI_INTMASK);
	pending = status & mask;

	if (pending & ISI_CTWW_SWST) {
		compwete(&isi->compwete);
		isi_wwitew(isi, ISI_INTDIS, ISI_CTWW_SWST);
		wet = IWQ_HANDWED;
	} ewse if (pending & ISI_CTWW_DIS) {
		compwete(&isi->compwete);
		isi_wwitew(isi, ISI_INTDIS, ISI_CTWW_DIS);
		wet = IWQ_HANDWED;
	} ewse {
		if (wikewy(pending & ISI_SW_CXFW_DONE) ||
				wikewy(pending & ISI_SW_PXFW_DONE))
			wet = atmew_isi_handwe_stweaming(isi);
	}

	spin_unwock(&isi->iwqwock);
	wetuwn wet;
}

#define	WAIT_ISI_WESET		1
#define	WAIT_ISI_DISABWE	0
static int atmew_isi_wait_status(stwuct atmew_isi *isi, int wait_weset)
{
	unsigned wong timeout;
	/*
	 * The weset ow disabwe wiww onwy succeed if we have a
	 * pixew cwock fwom the camewa.
	 */
	init_compwetion(&isi->compwete);

	if (wait_weset) {
		isi_wwitew(isi, ISI_INTEN, ISI_CTWW_SWST);
		isi_wwitew(isi, ISI_CTWW, ISI_CTWW_SWST);
	} ewse {
		isi_wwitew(isi, ISI_INTEN, ISI_CTWW_DIS);
		isi_wwitew(isi, ISI_CTWW, ISI_CTWW_DIS);
	}

	timeout = wait_fow_compwetion_timeout(&isi->compwete,
			msecs_to_jiffies(500));
	if (timeout == 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

/* ------------------------------------------------------------------
	Videobuf opewations
   ------------------------------------------------------------------*/
static int queue_setup(stwuct vb2_queue *vq,
				unsigned int *nbuffews, unsigned int *npwanes,
				unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct atmew_isi *isi = vb2_get_dwv_pwiv(vq);
	unsigned wong size;

	size = isi->fmt.fmt.pix.sizeimage;

	/* Make suwe the image size is wawge enough. */
	if (*npwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;

	*npwanes = 1;
	sizes[0] = size;

	isi->active = NUWW;

	dev_dbg(isi->dev, "%s, count=%d, size=%wd\n", __func__,
		*nbuffews, size);

	wetuwn 0;
}

static int buffew_init(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct fwame_buffew *buf = containew_of(vbuf, stwuct fwame_buffew, vb);

	buf->p_dma_desc = NUWW;
	INIT_WIST_HEAD(&buf->wist);

	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct fwame_buffew *buf = containew_of(vbuf, stwuct fwame_buffew, vb);
	stwuct atmew_isi *isi = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong size;
	stwuct isi_dma_desc *desc;

	size = isi->fmt.fmt.pix.sizeimage;

	if (vb2_pwane_size(vb, 0) < size) {
		dev_eww(isi->dev, "%s data wiww not fit into pwane (%wu < %wu)\n",
				__func__, vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, size);

	if (!buf->p_dma_desc) {
		if (wist_empty(&isi->dma_desc_head)) {
			dev_eww(isi->dev, "Not enough dma descwiptows.\n");
			wetuwn -EINVAW;
		} ewse {
			/* Get an avaiwabwe descwiptow */
			desc = wist_entwy(isi->dma_desc_head.next,
						stwuct isi_dma_desc, wist);
			/* Dewete the descwiptow since now it is used */
			wist_dew_init(&desc->wist);

			/* Initiawize the dma descwiptow */
			desc->p_fbd->fb_addwess =
					vb2_dma_contig_pwane_dma_addw(vb, 0);
			desc->p_fbd->next_fbd_addwess = 0;
			set_dma_ctww(desc->p_fbd, ISI_DMA_CTWW_WB);

			buf->p_dma_desc = desc;
		}
	}
	wetuwn 0;
}

static void buffew_cweanup(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct atmew_isi *isi = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct fwame_buffew *buf = containew_of(vbuf, stwuct fwame_buffew, vb);

	/* This descwiptow is avaiwabwe now and we add to head wist */
	if (buf->p_dma_desc)
		wist_add(&buf->p_dma_desc->wist, &isi->dma_desc_head);
}

static void stawt_dma(stwuct atmew_isi *isi, stwuct fwame_buffew *buffew)
{
	u32 ctww, cfg1;

	cfg1 = isi_weadw(isi, ISI_CFG1);
	/* Enabwe iwq: cxfw fow the codec path, pxfw fow the pweview path */
	isi_wwitew(isi, ISI_INTEN,
			ISI_SW_CXFW_DONE | ISI_SW_PXFW_DONE);

	/* Check if awweady in a fwame */
	if (!isi->enabwe_pweview_path) {
		if (isi_weadw(isi, ISI_STATUS) & ISI_CTWW_CDC) {
			dev_eww(isi->dev, "Awweady in fwame handwing.\n");
			wetuwn;
		}

		isi_wwitew(isi, ISI_DMA_C_DSCW,
				(u32)buffew->p_dma_desc->fbd_phys);
		isi_wwitew(isi, ISI_DMA_C_CTWW,
				ISI_DMA_CTWW_FETCH | ISI_DMA_CTWW_DONE);
		isi_wwitew(isi, ISI_DMA_CHEW, ISI_DMA_CHSW_C_CH);
	} ewse {
		isi_wwitew(isi, ISI_DMA_P_DSCW,
				(u32)buffew->p_dma_desc->fbd_phys);
		isi_wwitew(isi, ISI_DMA_P_CTWW,
				ISI_DMA_CTWW_FETCH | ISI_DMA_CTWW_DONE);
		isi_wwitew(isi, ISI_DMA_CHEW, ISI_DMA_CHSW_P_CH);
	}

	cfg1 &= ~ISI_CFG1_FWATE_DIV_MASK;
	/* Enabwe winked wist */
	cfg1 |= isi->pdata.fwate | ISI_CFG1_DISCW;

	/* Enabwe ISI */
	ctww = ISI_CTWW_EN;

	if (!isi->enabwe_pweview_path)
		ctww |= ISI_CTWW_CDC;

	isi_wwitew(isi, ISI_CTWW, ctww);
	isi_wwitew(isi, ISI_CFG1, cfg1);
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct atmew_isi *isi = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct fwame_buffew *buf = containew_of(vbuf, stwuct fwame_buffew, vb);
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&isi->iwqwock, fwags);
	wist_add_taiw(&buf->wist, &isi->video_buffew_wist);

	if (!isi->active) {
		isi->active = buf;
		if (vb2_is_stweaming(vb->vb2_queue))
			stawt_dma(isi, buf);
	}
	spin_unwock_iwqwestowe(&isi->iwqwock, fwags);
}

static int stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct atmew_isi *isi = vb2_get_dwv_pwiv(vq);
	stwuct fwame_buffew *buf, *node;
	int wet;

	wet = pm_wuntime_wesume_and_get(isi->dev);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe stweam on the sub device */
	wet = v4w2_subdev_caww(isi->entity.subdev, video, s_stweam, 1);
	if (wet && wet != -ENOIOCTWCMD) {
		dev_eww(isi->dev, "stweam on faiwed in subdev\n");
		goto eww_stawt_stweam;
	}

	/* Weset ISI */
	wet = atmew_isi_wait_status(isi, WAIT_ISI_WESET);
	if (wet < 0) {
		dev_eww(isi->dev, "Weset ISI timed out\n");
		goto eww_weset;
	}
	/* Disabwe aww intewwupts */
	isi_wwitew(isi, ISI_INTDIS, (u32)~0UW);

	isi->sequence = 0;
	configuwe_geometwy(isi);

	spin_wock_iwq(&isi->iwqwock);
	/* Cweaw any pending intewwupt */
	isi_weadw(isi, ISI_STATUS);

	stawt_dma(isi, isi->active);
	spin_unwock_iwq(&isi->iwqwock);

	wetuwn 0;

eww_weset:
	v4w2_subdev_caww(isi->entity.subdev, video, s_stweam, 0);

eww_stawt_stweam:
	pm_wuntime_put(isi->dev);

	spin_wock_iwq(&isi->iwqwock);
	isi->active = NUWW;
	/* Wewease aww active buffews */
	wist_fow_each_entwy_safe(buf, node, &isi->video_buffew_wist, wist) {
		wist_dew_init(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	}
	spin_unwock_iwq(&isi->iwqwock);

	wetuwn wet;
}

/* abowt stweaming and wait fow wast buffew */
static void stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct atmew_isi *isi = vb2_get_dwv_pwiv(vq);
	stwuct fwame_buffew *buf, *node;
	int wet = 0;
	unsigned wong timeout;

	/* Disabwe stweam on the sub device */
	wet = v4w2_subdev_caww(isi->entity.subdev, video, s_stweam, 0);
	if (wet && wet != -ENOIOCTWCMD)
		dev_eww(isi->dev, "stweam off faiwed in subdev\n");

	spin_wock_iwq(&isi->iwqwock);
	isi->active = NUWW;
	/* Wewease aww active buffews */
	wist_fow_each_entwy_safe(buf, node, &isi->video_buffew_wist, wist) {
		wist_dew_init(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwq(&isi->iwqwock);

	if (!isi->enabwe_pweview_path) {
		timeout = jiffies + (FWAME_INTEWVAW_MIWWI_SEC * HZ) / 1000;
		/* Wait untiw the end of the cuwwent fwame. */
		whiwe ((isi_weadw(isi, ISI_STATUS) & ISI_CTWW_CDC) &&
				time_befowe(jiffies, timeout))
			msweep(1);

		if (time_aftew(jiffies, timeout))
			dev_eww(isi->dev,
				"Timeout waiting fow finishing codec wequest\n");
	}

	/* Disabwe intewwupts */
	isi_wwitew(isi, ISI_INTDIS,
			ISI_SW_CXFW_DONE | ISI_SW_PXFW_DONE);

	/* Disabwe ISI and wait fow it is done */
	wet = atmew_isi_wait_status(isi, WAIT_ISI_DISABWE);
	if (wet < 0)
		dev_eww(isi->dev, "Disabwe ISI timed out\n");

	pm_wuntime_put(isi->dev);
}

static const stwuct vb2_ops isi_video_qops = {
	.queue_setup		= queue_setup,
	.buf_init		= buffew_init,
	.buf_pwepawe		= buffew_pwepawe,
	.buf_cweanup		= buffew_cweanup,
	.buf_queue		= buffew_queue,
	.stawt_stweaming	= stawt_stweaming,
	.stop_stweaming		= stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

static int isi_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *fmt)
{
	stwuct atmew_isi *isi = video_dwvdata(fiwe);

	*fmt = isi->fmt;

	wetuwn 0;
}

static const stwuct isi_fowmat *find_fowmat_by_fouwcc(stwuct atmew_isi *isi,
						      unsigned int fouwcc)
{
	unsigned int num_fowmats = isi->num_usew_fowmats;
	const stwuct isi_fowmat *fmt;
	unsigned int i;

	fow (i = 0; i < num_fowmats; i++) {
		fmt = isi->usew_fowmats[i];
		if (fmt->fouwcc == fouwcc)
			wetuwn fmt;
	}

	wetuwn NUWW;
}

static void isi_twy_fse(stwuct atmew_isi *isi, const stwuct isi_fowmat *isi_fmt,
			stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_wect *twy_cwop =
		v4w2_subdev_state_get_cwop(sd_state, 0);
	stwuct v4w2_subdev_fwame_size_enum fse = {
		.code = isi_fmt->mbus_code,
		.which = V4W2_SUBDEV_FOWMAT_TWY,
	};
	int wet;

	wet = v4w2_subdev_caww(isi->entity.subdev, pad, enum_fwame_size,
			       sd_state, &fse);
	/*
	 * Attempt to obtain fowmat size fwom subdev. If not avaiwabwe,
	 * just use the maximum ISI can weceive.
	 */
	if (wet) {
		twy_cwop->width = MAX_SUPPOWT_WIDTH;
		twy_cwop->height = MAX_SUPPOWT_HEIGHT;
	} ewse {
		twy_cwop->width = fse.max_width;
		twy_cwop->height = fse.max_height;
	}
}

static int isi_twy_fmt(stwuct atmew_isi *isi, stwuct v4w2_fowmat *f,
		       const stwuct isi_fowmat **cuwwent_fmt)
{
	const stwuct isi_fowmat *isi_fmt;
	stwuct v4w2_pix_fowmat *pixfmt = &f->fmt.pix;
	stwuct v4w2_subdev_pad_config pad_cfg = {};
	stwuct v4w2_subdev_state pad_state = {
		.sd = isi->entity.subdev,
		.pads = &pad_cfg,
	};
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_TWY,
	};
	int wet;

	isi_fmt = find_fowmat_by_fouwcc(isi, pixfmt->pixewfowmat);
	if (!isi_fmt) {
		isi_fmt = isi->usew_fowmats[isi->num_usew_fowmats - 1];
		pixfmt->pixewfowmat = isi_fmt->fouwcc;
	}

	/* Wimit to Atmew ISI hawdwawe capabiwities */
	pixfmt->width = cwamp(pixfmt->width, 0U, MAX_SUPPOWT_WIDTH);
	pixfmt->height = cwamp(pixfmt->height, 0U, MAX_SUPPOWT_HEIGHT);

	v4w2_fiww_mbus_fowmat(&fowmat.fowmat, pixfmt, isi_fmt->mbus_code);

	isi_twy_fse(isi, isi_fmt, &pad_state);

	wet = v4w2_subdev_caww(isi->entity.subdev, pad, set_fmt,
			       &pad_state, &fowmat);
	if (wet < 0)
		wetuwn wet;

	v4w2_fiww_pix_fowmat(pixfmt, &fowmat.fowmat);

	pixfmt->fiewd = V4W2_FIEWD_NONE;
	pixfmt->bytespewwine = pixfmt->width * isi_fmt->bpp;
	pixfmt->sizeimage = pixfmt->bytespewwine * pixfmt->height;

	if (cuwwent_fmt)
		*cuwwent_fmt = isi_fmt;

	wetuwn 0;
}

static int isi_set_fmt(stwuct atmew_isi *isi, stwuct v4w2_fowmat *f)
{
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	const stwuct isi_fowmat *cuwwent_fmt;
	int wet;

	wet = isi_twy_fmt(isi, f, &cuwwent_fmt);
	if (wet)
		wetuwn wet;

	v4w2_fiww_mbus_fowmat(&fowmat.fowmat, &f->fmt.pix,
			      cuwwent_fmt->mbus_code);
	wet = v4w2_subdev_caww(isi->entity.subdev, pad,
			       set_fmt, NUWW, &fowmat);
	if (wet < 0)
		wetuwn wet;

	isi->fmt = *f;
	isi->cuwwent_fmt = cuwwent_fmt;

	wetuwn 0;
}

static int isi_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *f)
{
	stwuct atmew_isi *isi = video_dwvdata(fiwe);

	if (vb2_is_stweaming(&isi->queue))
		wetuwn -EBUSY;

	wetuwn isi_set_fmt(isi, f);
}

static int isi_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct atmew_isi *isi = video_dwvdata(fiwe);

	wetuwn isi_twy_fmt(isi, f, NUWW);
}

static int isi_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
				stwuct v4w2_fmtdesc *f)
{
	stwuct atmew_isi *isi = video_dwvdata(fiwe);

	if (f->index >= isi->num_usew_fowmats)
		wetuwn -EINVAW;

	f->pixewfowmat = isi->usew_fowmats[f->index]->fouwcc;
	wetuwn 0;
}

static int isi_quewycap(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, "atmew-isi", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "Atmew Image Sensow Intewface", sizeof(cap->cawd));
	stwscpy(cap->bus_info, "pwatfowm:isi", sizeof(cap->bus_info));
	wetuwn 0;
}

static int isi_enum_input(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_input *i)
{
	if (i->index != 0)
		wetuwn -EINVAW;

	i->type = V4W2_INPUT_TYPE_CAMEWA;
	stwscpy(i->name, "Camewa", sizeof(i->name));
	wetuwn 0;
}

static int isi_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	*i = 0;
	wetuwn 0;
}

static int isi_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	if (i > 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int isi_g_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct atmew_isi *isi = video_dwvdata(fiwe);

	wetuwn v4w2_g_pawm_cap(video_devdata(fiwe), isi->entity.subdev, a);
}

static int isi_s_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct atmew_isi *isi = video_dwvdata(fiwe);

	wetuwn v4w2_s_pawm_cap(video_devdata(fiwe), isi->entity.subdev, a);
}

static int isi_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct atmew_isi *isi = video_dwvdata(fiwe);
	const stwuct isi_fowmat *isi_fmt;
	stwuct v4w2_subdev_fwame_size_enum fse = {
		.index = fsize->index,
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wet;

	isi_fmt = find_fowmat_by_fouwcc(isi, fsize->pixew_fowmat);
	if (!isi_fmt)
		wetuwn -EINVAW;

	fse.code = isi_fmt->mbus_code;

	wet = v4w2_subdev_caww(isi->entity.subdev, pad, enum_fwame_size,
			       NUWW, &fse);
	if (wet)
		wetuwn wet;

	fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
	fsize->discwete.width = fse.max_width;
	fsize->discwete.height = fse.max_height;

	wetuwn 0;
}

static int isi_enum_fwameintewvaws(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fwmivawenum *fivaw)
{
	stwuct atmew_isi *isi = video_dwvdata(fiwe);
	const stwuct isi_fowmat *isi_fmt;
	stwuct v4w2_subdev_fwame_intewvaw_enum fie = {
		.index = fivaw->index,
		.width = fivaw->width,
		.height = fivaw->height,
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wet;

	isi_fmt = find_fowmat_by_fouwcc(isi, fivaw->pixew_fowmat);
	if (!isi_fmt)
		wetuwn -EINVAW;

	fie.code = isi_fmt->mbus_code;

	wet = v4w2_subdev_caww(isi->entity.subdev, pad,
			       enum_fwame_intewvaw, NUWW, &fie);
	if (wet)
		wetuwn wet;

	fivaw->type = V4W2_FWMIVAW_TYPE_DISCWETE;
	fivaw->discwete = fie.intewvaw;

	wetuwn 0;
}

static int isi_camewa_set_bus_pawam(stwuct atmew_isi *isi)
{
	u32 cfg1 = 0;
	int wet;

	/* set bus pawam fow ISI */
	if (isi->pdata.hsync_act_wow)
		cfg1 |= ISI_CFG1_HSYNC_POW_ACTIVE_WOW;
	if (isi->pdata.vsync_act_wow)
		cfg1 |= ISI_CFG1_VSYNC_POW_ACTIVE_WOW;
	if (isi->pdata.pcwk_act_fawwing)
		cfg1 |= ISI_CFG1_PIXCWK_POW_ACTIVE_FAWWING;
	if (isi->pdata.has_emb_sync)
		cfg1 |= ISI_CFG1_EMB_SYNC;
	if (isi->pdata.fuww_mode)
		cfg1 |= ISI_CFG1_FUWW_MODE;

	cfg1 |= ISI_CFG1_THMASK_BEATS_16;

	/* Enabwe PM and pewiphewaw cwock befowe opewate isi wegistews */
	wet = pm_wuntime_wesume_and_get(isi->dev);
	if (wet < 0)
		wetuwn wet;

	isi_wwitew(isi, ISI_CTWW, ISI_CTWW_DIS);
	isi_wwitew(isi, ISI_CFG1, cfg1);

	pm_wuntime_put(isi->dev);

	wetuwn 0;
}

/* -----------------------------------------------------------------------*/
static int atmew_isi_pawse_dt(stwuct atmew_isi *isi,
			stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct v4w2_fwnode_endpoint ep = { .bus_type = 0 };
	int eww;

	/* Defauwt settings fow ISI */
	isi->pdata.fuww_mode = 1;
	isi->pdata.fwate = ISI_CFG1_FWATE_CAPTUWE_AWW;

	np = of_gwaph_get_next_endpoint(np, NUWW);
	if (!np) {
		dev_eww(&pdev->dev, "Couwd not find the endpoint\n");
		wetuwn -EINVAW;
	}

	eww = v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(np), &ep);
	of_node_put(np);
	if (eww) {
		dev_eww(&pdev->dev, "Couwd not pawse the endpoint\n");
		wetuwn eww;
	}

	switch (ep.bus.pawawwew.bus_width) {
	case 8:
		isi->pdata.data_width_fwags = ISI_DATAWIDTH_8;
		bweak;
	case 10:
		isi->pdata.data_width_fwags =
				ISI_DATAWIDTH_8 | ISI_DATAWIDTH_10;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unsuppowted bus width: %d\n",
				ep.bus.pawawwew.bus_width);
		wetuwn -EINVAW;
	}

	if (ep.bus.pawawwew.fwags & V4W2_MBUS_HSYNC_ACTIVE_WOW)
		isi->pdata.hsync_act_wow = twue;
	if (ep.bus.pawawwew.fwags & V4W2_MBUS_VSYNC_ACTIVE_WOW)
		isi->pdata.vsync_act_wow = twue;
	if (ep.bus.pawawwew.fwags & V4W2_MBUS_PCWK_SAMPWE_FAWWING)
		isi->pdata.pcwk_act_fawwing = twue;

	if (ep.bus_type == V4W2_MBUS_BT656)
		isi->pdata.has_emb_sync = twue;

	wetuwn 0;
}

static int isi_open(stwuct fiwe *fiwe)
{
	stwuct atmew_isi *isi = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = isi->entity.subdev;
	int wet;

	if (mutex_wock_intewwuptibwe(&isi->wock))
		wetuwn -EWESTAWTSYS;

	wet = v4w2_fh_open(fiwe);
	if (wet < 0)
		goto unwock;

	if (!v4w2_fh_is_singuwaw_fiwe(fiwe))
		goto fh_wew;

	wet = v4w2_subdev_caww(sd, cowe, s_powew, 1);
	if (wet < 0 && wet != -ENOIOCTWCMD)
		goto fh_wew;

	wet = isi_set_fmt(isi, &isi->fmt);
	if (wet)
		v4w2_subdev_caww(sd, cowe, s_powew, 0);
fh_wew:
	if (wet)
		v4w2_fh_wewease(fiwe);
unwock:
	mutex_unwock(&isi->wock);
	wetuwn wet;
}

static int isi_wewease(stwuct fiwe *fiwe)
{
	stwuct atmew_isi *isi = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = isi->entity.subdev;
	boow fh_singuwaw;
	int wet;

	mutex_wock(&isi->wock);

	fh_singuwaw = v4w2_fh_is_singuwaw_fiwe(fiwe);

	wet = _vb2_fop_wewease(fiwe, NUWW);

	if (fh_singuwaw)
		v4w2_subdev_caww(sd, cowe, s_powew, 0);

	mutex_unwock(&isi->wock);

	wetuwn wet;
}

static const stwuct v4w2_ioctw_ops isi_ioctw_ops = {
	.vidioc_quewycap		= isi_quewycap,

	.vidioc_twy_fmt_vid_cap		= isi_twy_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= isi_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= isi_s_fmt_vid_cap,
	.vidioc_enum_fmt_vid_cap	= isi_enum_fmt_vid_cap,

	.vidioc_enum_input		= isi_enum_input,
	.vidioc_g_input			= isi_g_input,
	.vidioc_s_input			= isi_s_input,

	.vidioc_g_pawm			= isi_g_pawm,
	.vidioc_s_pawm			= isi_s_pawm,
	.vidioc_enum_fwamesizes		= isi_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws	= isi_enum_fwameintewvaws,

	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,

	.vidioc_wog_status		= v4w2_ctww_wog_status,
	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

static const stwuct v4w2_fiwe_opewations isi_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= video_ioctw2,
	.open		= isi_open,
	.wewease	= isi_wewease,
	.poww		= vb2_fop_poww,
	.mmap		= vb2_fop_mmap,
	.wead		= vb2_fop_wead,
};

static int isi_set_defauwt_fmt(stwuct atmew_isi *isi)
{
	stwuct v4w2_fowmat f = {
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE,
		.fmt.pix = {
			.width		= VGA_WIDTH,
			.height		= VGA_HEIGHT,
			.fiewd		= V4W2_FIEWD_NONE,
			.pixewfowmat	= isi->usew_fowmats[0]->fouwcc,
		},
	};
	int wet;

	wet = isi_twy_fmt(isi, &f, NUWW);
	if (wet)
		wetuwn wet;
	isi->cuwwent_fmt = isi->usew_fowmats[0];
	isi->fmt = f;
	wetuwn 0;
}

static const stwuct isi_fowmat isi_fowmats[] = {
	{
		.fouwcc = V4W2_PIX_FMT_YUYV,
		.mbus_code = MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_DEFAUWT,
	}, {
		.fouwcc = V4W2_PIX_FMT_YUYV,
		.mbus_code = MEDIA_BUS_FMT_YVYU8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_1,
	}, {
		.fouwcc = V4W2_PIX_FMT_YUYV,
		.mbus_code = MEDIA_BUS_FMT_UYVY8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_2,
	}, {
		.fouwcc = V4W2_PIX_FMT_YUYV,
		.mbus_code = MEDIA_BUS_FMT_VYUY8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_3,
	}, {
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.mbus_code = MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_2,
	}, {
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.mbus_code = MEDIA_BUS_FMT_YVYU8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_3,
	}, {
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.mbus_code = MEDIA_BUS_FMT_UYVY8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_DEFAUWT,
	}, {
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.mbus_code = MEDIA_BUS_FMT_VYUY8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_1,
	}, {
		.fouwcc = V4W2_PIX_FMT_GWEY,
		.mbus_code = MEDIA_BUS_FMT_Y10_1X10,
		.bpp = 1,
		.swap = ISI_CFG2_GS_MODE_2_PIXEW | ISI_CFG2_GWAYSCAWE,
	}, {
		.fouwcc = V4W2_PIX_FMT_Y16,
		.mbus_code = MEDIA_BUS_FMT_Y10_1X10,
		.bpp = 2,
		.swap = ISI_CFG2_GS_MODE_2_PIXEW | ISI_CFG2_GWAYSCAWE,
	},
};

static int isi_fowmats_init(stwuct atmew_isi *isi)
{
	const stwuct isi_fowmat *isi_fmts[AWWAY_SIZE(isi_fowmats)];
	unsigned int num_fmts = 0, i, j;
	stwuct v4w2_subdev *subdev = isi->entity.subdev;
	stwuct v4w2_subdev_mbus_code_enum mbus_code = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};

	whiwe (!v4w2_subdev_caww(subdev, pad, enum_mbus_code,
				 NUWW, &mbus_code)) {
		fow (i = 0; i < AWWAY_SIZE(isi_fowmats); i++) {
			if (isi_fowmats[i].mbus_code != mbus_code.code)
				continue;

			/* Code suppowted, have we got this fouwcc yet? */
			fow (j = 0; j < num_fmts; j++)
				if (isi_fmts[j]->fouwcc == isi_fowmats[i].fouwcc)
					/* Awweady avaiwabwe */
					bweak;
			if (j == num_fmts)
				/* new */
				isi_fmts[num_fmts++] = isi_fowmats + i;
		}
		mbus_code.index++;
	}

	if (!num_fmts)
		wetuwn -ENXIO;

	isi->num_usew_fowmats = num_fmts;
	isi->usew_fowmats = devm_kcawwoc(isi->dev,
					 num_fmts, sizeof(stwuct isi_fowmat *),
					 GFP_KEWNEW);
	if (!isi->usew_fowmats)
		wetuwn -ENOMEM;

	memcpy(isi->usew_fowmats, isi_fmts,
	       num_fmts * sizeof(stwuct isi_fowmat *));
	isi->cuwwent_fmt = isi->usew_fowmats[0];

	wetuwn 0;
}

static int isi_gwaph_notify_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct atmew_isi *isi = notifiew_to_isi(notifiew);
	int wet;

	isi->vdev->ctww_handwew = isi->entity.subdev->ctww_handwew;
	wet = isi_fowmats_init(isi);
	if (wet) {
		dev_eww(isi->dev, "No suppowted mediabus fowmat found\n");
		wetuwn wet;
	}
	wet = isi_camewa_set_bus_pawam(isi);
	if (wet) {
		dev_eww(isi->dev, "Can't wake up device\n");
		wetuwn wet;
	}

	wet = isi_set_defauwt_fmt(isi);
	if (wet) {
		dev_eww(isi->dev, "Couwd not set defauwt fowmat\n");
		wetuwn wet;
	}

	wet = video_wegistew_device(isi->vdev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		dev_eww(isi->dev, "Faiwed to wegistew video device\n");
		wetuwn wet;
	}

	dev_dbg(isi->dev, "Device wegistewed as %s\n",
		video_device_node_name(isi->vdev));
	wetuwn 0;
}

static void isi_gwaph_notify_unbind(stwuct v4w2_async_notifiew *notifiew,
				     stwuct v4w2_subdev *sd,
				     stwuct v4w2_async_connection *asd)
{
	stwuct atmew_isi *isi = notifiew_to_isi(notifiew);

	dev_dbg(isi->dev, "Wemoving %s\n", video_device_node_name(isi->vdev));

	/* Checks intewnawwy if vdev have been init ow not */
	video_unwegistew_device(isi->vdev);
}

static int isi_gwaph_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				   stwuct v4w2_subdev *subdev,
				   stwuct v4w2_async_connection *asd)
{
	stwuct atmew_isi *isi = notifiew_to_isi(notifiew);

	dev_dbg(isi->dev, "subdev %s bound\n", subdev->name);

	isi->entity.subdev = subdev;

	wetuwn 0;
}

static const stwuct v4w2_async_notifiew_opewations isi_gwaph_notify_ops = {
	.bound = isi_gwaph_notify_bound,
	.unbind = isi_gwaph_notify_unbind,
	.compwete = isi_gwaph_notify_compwete,
};

static int isi_gwaph_init(stwuct atmew_isi *isi)
{
	stwuct v4w2_async_connection *asd;
	stwuct device_node *ep;
	int wet;

	ep = of_gwaph_get_next_endpoint(isi->dev->of_node, NUWW);
	if (!ep)
		wetuwn -EINVAW;

	v4w2_async_nf_init(&isi->notifiew, &isi->v4w2_dev);

	asd = v4w2_async_nf_add_fwnode_wemote(&isi->notifiew,
					      of_fwnode_handwe(ep),
					      stwuct v4w2_async_connection);
	of_node_put(ep);

	if (IS_EWW(asd))
		wetuwn PTW_EWW(asd);

	isi->notifiew.ops = &isi_gwaph_notify_ops;

	wet = v4w2_async_nf_wegistew(&isi->notifiew);
	if (wet < 0) {
		dev_eww(isi->dev, "Notifiew wegistwation faiwed\n");
		v4w2_async_nf_cweanup(&isi->notifiew);
		wetuwn wet;
	}

	wetuwn 0;
}


static int atmew_isi_pwobe(stwuct pwatfowm_device *pdev)
{
	int iwq;
	stwuct atmew_isi *isi;
	stwuct vb2_queue *q;
	int wet, i;

	isi = devm_kzawwoc(&pdev->dev, sizeof(stwuct atmew_isi), GFP_KEWNEW);
	if (!isi)
		wetuwn -ENOMEM;

	isi->pcwk = devm_cwk_get(&pdev->dev, "isi_cwk");
	if (IS_EWW(isi->pcwk))
		wetuwn PTW_EWW(isi->pcwk);

	wet = atmew_isi_pawse_dt(isi, pdev);
	if (wet)
		wetuwn wet;

	isi->active = NUWW;
	isi->dev = &pdev->dev;
	mutex_init(&isi->wock);
	spin_wock_init(&isi->iwqwock);
	INIT_WIST_HEAD(&isi->video_buffew_wist);
	INIT_WIST_HEAD(&isi->dma_desc_head);

	q = &isi->queue;

	/* Initiawize the top-wevew stwuctuwe */
	wet = v4w2_device_wegistew(&pdev->dev, &isi->v4w2_dev);
	if (wet)
		wetuwn wet;

	isi->vdev = video_device_awwoc();
	if (!isi->vdev) {
		wet = -ENOMEM;
		goto eww_vdev_awwoc;
	}

	/* video node */
	isi->vdev->fops = &isi_fops;
	isi->vdev->v4w2_dev = &isi->v4w2_dev;
	isi->vdev->queue = &isi->queue;
	stwscpy(isi->vdev->name, KBUIWD_MODNAME, sizeof(isi->vdev->name));
	isi->vdev->wewease = video_device_wewease;
	isi->vdev->ioctw_ops = &isi_ioctw_ops;
	isi->vdev->wock = &isi->wock;
	isi->vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING |
		V4W2_CAP_WEADWWITE;
	video_set_dwvdata(isi->vdev, isi);

	/* buffew queue */
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_WEAD | VB2_DMABUF;
	q->wock = &isi->wock;
	q->dwv_pwiv = isi;
	q->buf_stwuct_size = sizeof(stwuct fwame_buffew);
	q->ops = &isi_video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = 2;
	q->dev = &pdev->dev;

	wet = vb2_queue_init(q);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to initiawize VB2 queue\n");
		goto eww_vb2_queue;
	}
	isi->p_fb_descwiptows = dma_awwoc_cohewent(&pdev->dev,
				sizeof(stwuct fbd) * VIDEO_MAX_FWAME,
				&isi->fb_descwiptows_phys,
				GFP_KEWNEW);
	if (!isi->p_fb_descwiptows) {
		dev_eww(&pdev->dev, "Can't awwocate descwiptows!\n");
		wet = -ENOMEM;
		goto eww_dma_awwoc;
	}

	fow (i = 0; i < VIDEO_MAX_FWAME; i++) {
		isi->dma_desc[i].p_fbd = isi->p_fb_descwiptows + i;
		isi->dma_desc[i].fbd_phys = isi->fb_descwiptows_phys +
					i * sizeof(stwuct fbd);
		wist_add(&isi->dma_desc[i].wist, &isi->dma_desc_head);
	}

	isi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(isi->wegs)) {
		wet = PTW_EWW(isi->wegs);
		goto eww_iowemap;
	}

	if (isi->pdata.data_width_fwags & ISI_DATAWIDTH_8)
		isi->width_fwags = 1 << 7;
	if (isi->pdata.data_width_fwags & ISI_DATAWIDTH_10)
		isi->width_fwags |= 1 << 9;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto eww_weq_iwq;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, isi_intewwupt, 0, "isi", isi);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to wequest iwq %d\n", iwq);
		goto eww_weq_iwq;
	}
	isi->iwq = iwq;

	wet = isi_gwaph_init(isi);
	if (wet < 0)
		goto eww_weq_iwq;

	pm_suspend_ignowe_chiwdwen(&pdev->dev, twue);
	pm_wuntime_enabwe(&pdev->dev);
	pwatfowm_set_dwvdata(pdev, isi);
	wetuwn 0;

eww_weq_iwq:
eww_iowemap:
	dma_fwee_cohewent(&pdev->dev,
			sizeof(stwuct fbd) * VIDEO_MAX_FWAME,
			isi->p_fb_descwiptows,
			isi->fb_descwiptows_phys);
eww_dma_awwoc:
eww_vb2_queue:
	video_device_wewease(isi->vdev);
eww_vdev_awwoc:
	v4w2_device_unwegistew(&isi->v4w2_dev);

	wetuwn wet;
}

static void atmew_isi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct atmew_isi *isi = pwatfowm_get_dwvdata(pdev);

	dma_fwee_cohewent(&pdev->dev,
			sizeof(stwuct fbd) * VIDEO_MAX_FWAME,
			isi->p_fb_descwiptows,
			isi->fb_descwiptows_phys);
	pm_wuntime_disabwe(&pdev->dev);
	v4w2_async_nf_unwegistew(&isi->notifiew);
	v4w2_async_nf_cweanup(&isi->notifiew);
	v4w2_device_unwegistew(&isi->v4w2_dev);
}

#ifdef CONFIG_PM
static int atmew_isi_wuntime_suspend(stwuct device *dev)
{
	stwuct atmew_isi *isi = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(isi->pcwk);

	wetuwn 0;
}
static int atmew_isi_wuntime_wesume(stwuct device *dev)
{
	stwuct atmew_isi *isi = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(isi->pcwk);
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops atmew_isi_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(atmew_isi_wuntime_suspend,
				atmew_isi_wuntime_wesume, NUWW)
};

static const stwuct of_device_id atmew_isi_of_match[] = {
	{ .compatibwe = "atmew,at91sam9g45-isi" },
	{ }
};
MODUWE_DEVICE_TABWE(of, atmew_isi_of_match);

static stwuct pwatfowm_dwivew atmew_isi_dwivew = {
	.dwivew		= {
		.name = "atmew_isi",
		.of_match_tabwe = of_match_ptw(atmew_isi_of_match),
		.pm	= &atmew_isi_dev_pm_ops,
	},
	.pwobe		= atmew_isi_pwobe,
	.wemove_new	= atmew_isi_wemove,
};

moduwe_pwatfowm_dwivew(atmew_isi_dwivew);

MODUWE_AUTHOW("Josh Wu <josh.wu@atmew.com>");
MODUWE_DESCWIPTION("The V4W2 dwivew fow Atmew Winux");
MODUWE_WICENSE("GPW");
