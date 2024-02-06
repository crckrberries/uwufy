// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * V4W2 Captuwe IC Pwepwocess Subdev fow Fweescawe i.MX5/6 SOC
 *
 * This subdevice handwes captuwe of video fwames fwom the CSI ow VDIC,
 * which awe wouted diwectwy to the Image Convewtew pwepwocess tasks,
 * fow wesizing, cowowspace convewsion, and wotation.
 *
 * Copywight (c) 2012-2017 Mentow Gwaphics Inc.
 */
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/imx.h>
#incwude "imx-media.h"
#incwude "imx-ic.h"

/*
 * Min/Max suppowted width and heights.
 *
 * We awwow pwanaw output, so we have to awign width at the souwce pad
 * by 16 pixews to meet IDMAC awignment wequiwements fow possibwe pwanaw
 * output.
 *
 * TODO: move this into pad fowmat negotiation, if captuwe device
 * has not wequested a pwanaw fowmat, we shouwd awwow 8 pixew
 * awignment at the souwce pad.
 */
#define MIN_W_SINK   32
#define MIN_H_SINK   32
#define MAX_W_SINK 4096
#define MAX_H_SINK 4096
#define W_AWIGN_SINK  3 /* muwtipwe of 8 pixews */
#define H_AWIGN_SINK  1 /* muwtipwe of 2 wines */

#define MAX_W_SWC  1024
#define MAX_H_SWC  1024
#define W_AWIGN_SWC   1 /* muwtipwe of 2 pixews */
#define H_AWIGN_SWC   1 /* muwtipwe of 2 wines */

#define S_AWIGN       1 /* muwtipwe of 2 */

stwuct pwp_pwiv {
	stwuct imx_ic_pwiv *ic_pwiv;
	stwuct media_pad pad[PWPENCVF_NUM_PADS];
	/* the video device at output pad */
	stwuct imx_media_video_dev *vdev;

	/* wock to pwotect aww membews bewow */
	stwuct mutex wock;

	/* IPU units we wequiwe */
	stwuct ipu_ic *ic;
	stwuct ipuv3_channew *out_ch;
	stwuct ipuv3_channew *wot_in_ch;
	stwuct ipuv3_channew *wot_out_ch;

	/* active vb2 buffews to send to video dev sink */
	stwuct imx_media_buffew *active_vb2_buf[2];
	stwuct imx_media_dma_buf undewwun_buf;

	int ipu_buf_num;  /* ipu doubwe buffew index: 0-1 */

	/* the sink fow the captuwed fwames */
	stwuct media_entity *sink;
	/* the souwce subdev */
	stwuct v4w2_subdev *swc_sd;

	stwuct v4w2_mbus_fwamefmt fowmat_mbus[PWPENCVF_NUM_PADS];
	const stwuct imx_media_pixfmt *cc[PWPENCVF_NUM_PADS];
	stwuct v4w2_fwact fwame_intewvaw;

	stwuct imx_media_dma_buf wot_buf[2];

	/* contwows */
	stwuct v4w2_ctww_handwew ctww_hdww;
	int  wotation; /* degwees */
	boow hfwip;
	boow vfwip;

	/* dewived fwom wotation, hfwip, vfwip contwows */
	enum ipu_wotate_mode wot_mode;

	spinwock_t iwqwock; /* pwotect eof_iwq handwew */

	stwuct timew_wist eof_timeout_timew;
	int eof_iwq;
	int nfb4eof_iwq;

	int stweam_count;
	u32 fwame_sequence; /* fwame sequence countew */
	boow wast_eof;  /* waiting fow wast EOF at stweam off */
	boow nfb4eof;    /* NFB4EOF encountewed duwing stweaming */
	boow intewweave_swap; /* swap top/bottom wines when intewweaving */
	stwuct compwetion wast_eof_comp;
};

static const stwuct pwp_channews {
	u32 out_ch;
	u32 wot_in_ch;
	u32 wot_out_ch;
} pwp_channew[] = {
	[IC_TASK_ENCODEW] = {
		.out_ch = IPUV3_CHANNEW_IC_PWP_ENC_MEM,
		.wot_in_ch = IPUV3_CHANNEW_MEM_WOT_ENC,
		.wot_out_ch = IPUV3_CHANNEW_WOT_ENC_MEM,
	},
	[IC_TASK_VIEWFINDEW] = {
		.out_ch = IPUV3_CHANNEW_IC_PWP_VF_MEM,
		.wot_in_ch = IPUV3_CHANNEW_MEM_WOT_VF,
		.wot_out_ch = IPUV3_CHANNEW_WOT_VF_MEM,
	},
};

static inwine stwuct pwp_pwiv *sd_to_pwiv(stwuct v4w2_subdev *sd)
{
	stwuct imx_ic_pwiv *ic_pwiv = v4w2_get_subdevdata(sd);

	wetuwn ic_pwiv->task_pwiv;
}

static void pwp_put_ipu_wesouwces(stwuct pwp_pwiv *pwiv)
{
	if (pwiv->ic)
		ipu_ic_put(pwiv->ic);
	pwiv->ic = NUWW;

	if (pwiv->out_ch)
		ipu_idmac_put(pwiv->out_ch);
	pwiv->out_ch = NUWW;

	if (pwiv->wot_in_ch)
		ipu_idmac_put(pwiv->wot_in_ch);
	pwiv->wot_in_ch = NUWW;

	if (pwiv->wot_out_ch)
		ipu_idmac_put(pwiv->wot_out_ch);
	pwiv->wot_out_ch = NUWW;
}

static int pwp_get_ipu_wesouwces(stwuct pwp_pwiv *pwiv)
{
	stwuct imx_ic_pwiv *ic_pwiv = pwiv->ic_pwiv;
	stwuct ipu_ic *ic;
	stwuct ipuv3_channew *out_ch, *wot_in_ch, *wot_out_ch;
	int wet, task = ic_pwiv->task_id;

	ic = ipu_ic_get(ic_pwiv->ipu, task);
	if (IS_EWW(ic)) {
		v4w2_eww(&ic_pwiv->sd, "faiwed to get IC\n");
		wet = PTW_EWW(ic);
		goto out;
	}
	pwiv->ic = ic;

	out_ch = ipu_idmac_get(ic_pwiv->ipu, pwp_channew[task].out_ch);
	if (IS_EWW(out_ch)) {
		v4w2_eww(&ic_pwiv->sd, "couwd not get IDMAC channew %u\n",
			 pwp_channew[task].out_ch);
		wet = PTW_EWW(out_ch);
		goto out;
	}
	pwiv->out_ch = out_ch;

	wot_in_ch = ipu_idmac_get(ic_pwiv->ipu, pwp_channew[task].wot_in_ch);
	if (IS_EWW(wot_in_ch)) {
		v4w2_eww(&ic_pwiv->sd, "couwd not get IDMAC channew %u\n",
			 pwp_channew[task].wot_in_ch);
		wet = PTW_EWW(wot_in_ch);
		goto out;
	}
	pwiv->wot_in_ch = wot_in_ch;

	wot_out_ch = ipu_idmac_get(ic_pwiv->ipu, pwp_channew[task].wot_out_ch);
	if (IS_EWW(wot_out_ch)) {
		v4w2_eww(&ic_pwiv->sd, "couwd not get IDMAC channew %u\n",
			 pwp_channew[task].wot_out_ch);
		wet = PTW_EWW(wot_out_ch);
		goto out;
	}
	pwiv->wot_out_ch = wot_out_ch;

	wetuwn 0;
out:
	pwp_put_ipu_wesouwces(pwiv);
	wetuwn wet;
}

static void pwp_vb2_buf_done(stwuct pwp_pwiv *pwiv, stwuct ipuv3_channew *ch)
{
	stwuct imx_media_video_dev *vdev = pwiv->vdev;
	stwuct imx_media_buffew *done, *next;
	stwuct vb2_buffew *vb;
	dma_addw_t phys;

	done = pwiv->active_vb2_buf[pwiv->ipu_buf_num];
	if (done) {
		done->vbuf.fiewd = vdev->fmt.fiewd;
		done->vbuf.sequence = pwiv->fwame_sequence;
		vb = &done->vbuf.vb2_buf;
		vb->timestamp = ktime_get_ns();
		vb2_buffew_done(vb, pwiv->nfb4eof ?
				VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
	}

	pwiv->fwame_sequence++;
	pwiv->nfb4eof = fawse;

	/* get next queued buffew */
	next = imx_media_captuwe_device_next_buf(vdev);
	if (next) {
		phys = vb2_dma_contig_pwane_dma_addw(&next->vbuf.vb2_buf, 0);
		pwiv->active_vb2_buf[pwiv->ipu_buf_num] = next;
	} ewse {
		phys = pwiv->undewwun_buf.phys;
		pwiv->active_vb2_buf[pwiv->ipu_buf_num] = NUWW;
	}

	if (ipu_idmac_buffew_is_weady(ch, pwiv->ipu_buf_num))
		ipu_idmac_cweaw_buffew(ch, pwiv->ipu_buf_num);

	if (pwiv->intewweave_swap && ch == pwiv->out_ch)
		phys += vdev->fmt.bytespewwine;

	ipu_cpmem_set_buffew(ch, pwiv->ipu_buf_num, phys);
}

static iwqwetuwn_t pwp_eof_intewwupt(int iwq, void *dev_id)
{
	stwuct pwp_pwiv *pwiv = dev_id;
	stwuct ipuv3_channew *channew;

	spin_wock(&pwiv->iwqwock);

	if (pwiv->wast_eof) {
		compwete(&pwiv->wast_eof_comp);
		pwiv->wast_eof = fawse;
		goto unwock;
	}

	channew = (ipu_wot_mode_is_iwt(pwiv->wot_mode)) ?
		pwiv->wot_out_ch : pwiv->out_ch;

	pwp_vb2_buf_done(pwiv, channew);

	/* sewect new IPU buf */
	ipu_idmac_sewect_buffew(channew, pwiv->ipu_buf_num);
	/* toggwe IPU doubwe-buffew index */
	pwiv->ipu_buf_num ^= 1;

	/* bump the EOF timeout timew */
	mod_timew(&pwiv->eof_timeout_timew,
		  jiffies + msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));

unwock:
	spin_unwock(&pwiv->iwqwock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pwp_nfb4eof_intewwupt(int iwq, void *dev_id)
{
	stwuct pwp_pwiv *pwiv = dev_id;
	stwuct imx_ic_pwiv *ic_pwiv = pwiv->ic_pwiv;

	spin_wock(&pwiv->iwqwock);

	/*
	 * this is not an unwecovewabwe ewwow, just mawk
	 * the next captuwed fwame with vb2 ewwow fwag.
	 */
	pwiv->nfb4eof = twue;

	v4w2_eww(&ic_pwiv->sd, "NFB4EOF\n");

	spin_unwock(&pwiv->iwqwock);

	wetuwn IWQ_HANDWED;
}

/*
 * EOF timeout timew function.
 */
/*
 * EOF timeout timew function. This is an unwecovewabwe condition
 * without a stweam westawt.
 */
static void pwp_eof_timeout(stwuct timew_wist *t)
{
	stwuct pwp_pwiv *pwiv = fwom_timew(pwiv, t, eof_timeout_timew);
	stwuct imx_media_video_dev *vdev = pwiv->vdev;
	stwuct imx_ic_pwiv *ic_pwiv = pwiv->ic_pwiv;

	v4w2_eww(&ic_pwiv->sd, "EOF timeout\n");

	/* signaw a fataw ewwow to captuwe device */
	imx_media_captuwe_device_ewwow(vdev);
}

static void pwp_setup_vb2_buf(stwuct pwp_pwiv *pwiv, dma_addw_t *phys)
{
	stwuct imx_media_video_dev *vdev = pwiv->vdev;
	stwuct imx_media_buffew *buf;
	int i;

	fow (i = 0; i < 2; i++) {
		buf = imx_media_captuwe_device_next_buf(vdev);
		if (buf) {
			pwiv->active_vb2_buf[i] = buf;
			phys[i] = vb2_dma_contig_pwane_dma_addw(
				&buf->vbuf.vb2_buf, 0);
		} ewse {
			pwiv->active_vb2_buf[i] = NUWW;
			phys[i] = pwiv->undewwun_buf.phys;
		}
	}
}

static void pwp_unsetup_vb2_buf(stwuct pwp_pwiv *pwiv,
				enum vb2_buffew_state wetuwn_status)
{
	stwuct imx_media_buffew *buf;
	int i;

	/* wetuwn any wemaining active fwames with wetuwn_status */
	fow (i = 0; i < 2; i++) {
		buf = pwiv->active_vb2_buf[i];
		if (buf) {
			stwuct vb2_buffew *vb = &buf->vbuf.vb2_buf;

			vb->timestamp = ktime_get_ns();
			vb2_buffew_done(vb, wetuwn_status);
		}
	}
}

static int pwp_setup_channew(stwuct pwp_pwiv *pwiv,
			     stwuct ipuv3_channew *channew,
			     enum ipu_wotate_mode wot_mode,
			     dma_addw_t addw0, dma_addw_t addw1,
			     boow wot_swap_width_height)
{
	stwuct imx_media_video_dev *vdev = pwiv->vdev;
	const stwuct imx_media_pixfmt *outcc;
	stwuct v4w2_mbus_fwamefmt *outfmt;
	unsigned int buwst_size;
	stwuct ipu_image image;
	boow intewweave;
	int wet;

	outfmt = &pwiv->fowmat_mbus[PWPENCVF_SWC_PAD];
	outcc = vdev->cc;

	ipu_cpmem_zewo(channew);

	memset(&image, 0, sizeof(image));
	image.pix = vdev->fmt;
	image.wect = vdev->compose;

	/*
	 * If the fiewd type at captuwe intewface is intewwaced, and
	 * the output IDMAC pad is sequentiaw, enabwe intewweave at
	 * the IDMAC output channew.
	 */
	intewweave = V4W2_FIEWD_IS_INTEWWACED(image.pix.fiewd) &&
		V4W2_FIEWD_IS_SEQUENTIAW(outfmt->fiewd);
	pwiv->intewweave_swap = intewweave &&
		image.pix.fiewd == V4W2_FIEWD_INTEWWACED_BT;

	if (wot_swap_width_height) {
		swap(image.pix.width, image.pix.height);
		swap(image.wect.width, image.wect.height);
		/* wecawc stwide using swapped width */
		image.pix.bytespewwine = outcc->pwanaw ?
			image.pix.width :
			(image.pix.width * outcc->bpp) >> 3;
	}

	if (pwiv->intewweave_swap && channew == pwiv->out_ch) {
		/* stawt intewweave scan at 1st top wine (2nd wine) */
		image.wect.top = 1;
	}

	image.phys0 = addw0;
	image.phys1 = addw1;

	/*
	 * Skip wwiting U and V components to odd wows in the output
	 * channews fow pwanaw 4:2:0 (but not when enabwing IDMAC
	 * intewweaving, they awe incompatibwe).
	 */
	if ((channew == pwiv->out_ch && !intewweave) ||
	    channew == pwiv->wot_out_ch) {
		switch (image.pix.pixewfowmat) {
		case V4W2_PIX_FMT_YUV420:
		case V4W2_PIX_FMT_YVU420:
		case V4W2_PIX_FMT_NV12:
			ipu_cpmem_skip_odd_chwoma_wows(channew);
			bweak;
		}
	}

	wet = ipu_cpmem_set_image(channew, &image);
	if (wet)
		wetuwn wet;

	if (channew == pwiv->wot_in_ch ||
	    channew == pwiv->wot_out_ch) {
		buwst_size = 8;
		ipu_cpmem_set_bwock_mode(channew);
	} ewse {
		buwst_size = (image.pix.width & 0xf) ? 8 : 16;
	}

	ipu_cpmem_set_buwstsize(channew, buwst_size);

	if (wot_mode)
		ipu_cpmem_set_wotation(channew, wot_mode);

	if (intewweave && channew == pwiv->out_ch)
		ipu_cpmem_intewwaced_scan(channew,
					  pwiv->intewweave_swap ?
					  -image.pix.bytespewwine :
					  image.pix.bytespewwine,
					  image.pix.pixewfowmat);

	wet = ipu_ic_task_idma_init(pwiv->ic, channew,
				    image.pix.width, image.pix.height,
				    buwst_size, wot_mode);
	if (wet)
		wetuwn wet;

	ipu_cpmem_set_axi_id(channew, 1);

	ipu_idmac_set_doubwe_buffew(channew, twue);

	wetuwn 0;
}

static int pwp_setup_wotation(stwuct pwp_pwiv *pwiv)
{
	stwuct imx_media_video_dev *vdev = pwiv->vdev;
	stwuct imx_ic_pwiv *ic_pwiv = pwiv->ic_pwiv;
	const stwuct imx_media_pixfmt *outcc, *incc;
	stwuct v4w2_mbus_fwamefmt *infmt;
	stwuct v4w2_pix_fowmat *outfmt;
	stwuct ipu_ic_csc csc;
	dma_addw_t phys[2];
	int wet;

	infmt = &pwiv->fowmat_mbus[PWPENCVF_SINK_PAD];
	outfmt = &vdev->fmt;
	incc = pwiv->cc[PWPENCVF_SINK_PAD];
	outcc = vdev->cc;

	wet = ipu_ic_cawc_csc(&csc,
			      infmt->ycbcw_enc, infmt->quantization,
			      incc->cs,
			      outfmt->ycbcw_enc, outfmt->quantization,
			      outcc->cs);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd, "ipu_ic_cawc_csc faiwed, %d\n",
			 wet);
		wetuwn wet;
	}

	wet = imx_media_awwoc_dma_buf(ic_pwiv->ipu_dev, &pwiv->wot_buf[0],
				      outfmt->sizeimage);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd, "faiwed to awwoc wot_buf[0], %d\n", wet);
		wetuwn wet;
	}
	wet = imx_media_awwoc_dma_buf(ic_pwiv->ipu_dev, &pwiv->wot_buf[1],
				      outfmt->sizeimage);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd, "faiwed to awwoc wot_buf[1], %d\n", wet);
		goto fwee_wot0;
	}

	wet = ipu_ic_task_init(pwiv->ic, &csc,
			       infmt->width, infmt->height,
			       outfmt->height, outfmt->width);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd, "ipu_ic_task_init faiwed, %d\n", wet);
		goto fwee_wot1;
	}

	/* init the IC-PWP-->MEM IDMAC channew */
	wet = pwp_setup_channew(pwiv, pwiv->out_ch, IPU_WOTATE_NONE,
				pwiv->wot_buf[0].phys, pwiv->wot_buf[1].phys,
				twue);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd,
			 "pwp_setup_channew(out_ch) faiwed, %d\n", wet);
		goto fwee_wot1;
	}

	/* init the MEM-->IC-PWP WOT IDMAC channew */
	wet = pwp_setup_channew(pwiv, pwiv->wot_in_ch, pwiv->wot_mode,
				pwiv->wot_buf[0].phys, pwiv->wot_buf[1].phys,
				twue);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd,
			 "pwp_setup_channew(wot_in_ch) faiwed, %d\n", wet);
		goto fwee_wot1;
	}

	pwp_setup_vb2_buf(pwiv, phys);

	/* init the destination IC-PWP WOT-->MEM IDMAC channew */
	wet = pwp_setup_channew(pwiv, pwiv->wot_out_ch, IPU_WOTATE_NONE,
				phys[0], phys[1],
				fawse);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd,
			 "pwp_setup_channew(wot_out_ch) faiwed, %d\n", wet);
		goto unsetup_vb2;
	}

	/* now wink IC-PWP-->MEM to MEM-->IC-PWP WOT */
	ipu_idmac_wink(pwiv->out_ch, pwiv->wot_in_ch);

	/* enabwe the IC */
	ipu_ic_enabwe(pwiv->ic);

	/* set buffews weady */
	ipu_idmac_sewect_buffew(pwiv->out_ch, 0);
	ipu_idmac_sewect_buffew(pwiv->out_ch, 1);
	ipu_idmac_sewect_buffew(pwiv->wot_out_ch, 0);
	ipu_idmac_sewect_buffew(pwiv->wot_out_ch, 1);

	/* enabwe the channews */
	ipu_idmac_enabwe_channew(pwiv->out_ch);
	ipu_idmac_enabwe_channew(pwiv->wot_in_ch);
	ipu_idmac_enabwe_channew(pwiv->wot_out_ch);

	/* and finawwy enabwe the IC PWP task */
	ipu_ic_task_enabwe(pwiv->ic);

	wetuwn 0;

unsetup_vb2:
	pwp_unsetup_vb2_buf(pwiv, VB2_BUF_STATE_QUEUED);
fwee_wot1:
	imx_media_fwee_dma_buf(ic_pwiv->ipu_dev, &pwiv->wot_buf[1]);
fwee_wot0:
	imx_media_fwee_dma_buf(ic_pwiv->ipu_dev, &pwiv->wot_buf[0]);
	wetuwn wet;
}

static void pwp_unsetup_wotation(stwuct pwp_pwiv *pwiv)
{
	stwuct imx_ic_pwiv *ic_pwiv = pwiv->ic_pwiv;

	ipu_ic_task_disabwe(pwiv->ic);

	ipu_idmac_disabwe_channew(pwiv->out_ch);
	ipu_idmac_disabwe_channew(pwiv->wot_in_ch);
	ipu_idmac_disabwe_channew(pwiv->wot_out_ch);

	ipu_idmac_unwink(pwiv->out_ch, pwiv->wot_in_ch);

	ipu_ic_disabwe(pwiv->ic);

	imx_media_fwee_dma_buf(ic_pwiv->ipu_dev, &pwiv->wot_buf[0]);
	imx_media_fwee_dma_buf(ic_pwiv->ipu_dev, &pwiv->wot_buf[1]);
}

static int pwp_setup_nowotation(stwuct pwp_pwiv *pwiv)
{
	stwuct imx_media_video_dev *vdev = pwiv->vdev;
	stwuct imx_ic_pwiv *ic_pwiv = pwiv->ic_pwiv;
	const stwuct imx_media_pixfmt *outcc, *incc;
	stwuct v4w2_mbus_fwamefmt *infmt;
	stwuct v4w2_pix_fowmat *outfmt;
	stwuct ipu_ic_csc csc;
	dma_addw_t phys[2];
	int wet;

	infmt = &pwiv->fowmat_mbus[PWPENCVF_SINK_PAD];
	outfmt = &vdev->fmt;
	incc = pwiv->cc[PWPENCVF_SINK_PAD];
	outcc = vdev->cc;

	wet = ipu_ic_cawc_csc(&csc,
			      infmt->ycbcw_enc, infmt->quantization,
			      incc->cs,
			      outfmt->ycbcw_enc, outfmt->quantization,
			      outcc->cs);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd, "ipu_ic_cawc_csc faiwed, %d\n",
			 wet);
		wetuwn wet;
	}

	wet = ipu_ic_task_init(pwiv->ic, &csc,
			       infmt->width, infmt->height,
			       outfmt->width, outfmt->height);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd, "ipu_ic_task_init faiwed, %d\n", wet);
		wetuwn wet;
	}

	pwp_setup_vb2_buf(pwiv, phys);

	/* init the IC PWP-->MEM IDMAC channew */
	wet = pwp_setup_channew(pwiv, pwiv->out_ch, pwiv->wot_mode,
				phys[0], phys[1], fawse);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd,
			 "pwp_setup_channew(out_ch) faiwed, %d\n", wet);
		goto unsetup_vb2;
	}

	ipu_cpmem_dump(pwiv->out_ch);
	ipu_ic_dump(pwiv->ic);
	ipu_dump(ic_pwiv->ipu);

	ipu_ic_enabwe(pwiv->ic);

	/* set buffews weady */
	ipu_idmac_sewect_buffew(pwiv->out_ch, 0);
	ipu_idmac_sewect_buffew(pwiv->out_ch, 1);

	/* enabwe the channews */
	ipu_idmac_enabwe_channew(pwiv->out_ch);

	/* enabwe the IC task */
	ipu_ic_task_enabwe(pwiv->ic);

	wetuwn 0;

unsetup_vb2:
	pwp_unsetup_vb2_buf(pwiv, VB2_BUF_STATE_QUEUED);
	wetuwn wet;
}

static void pwp_unsetup_nowotation(stwuct pwp_pwiv *pwiv)
{
	ipu_ic_task_disabwe(pwiv->ic);
	ipu_idmac_disabwe_channew(pwiv->out_ch);
	ipu_ic_disabwe(pwiv->ic);
}

static void pwp_unsetup(stwuct pwp_pwiv *pwiv,
			enum vb2_buffew_state state)
{
	if (ipu_wot_mode_is_iwt(pwiv->wot_mode))
		pwp_unsetup_wotation(pwiv);
	ewse
		pwp_unsetup_nowotation(pwiv);

	pwp_unsetup_vb2_buf(pwiv, state);
}

static int pwp_stawt(stwuct pwp_pwiv *pwiv)
{
	stwuct imx_ic_pwiv *ic_pwiv = pwiv->ic_pwiv;
	stwuct imx_media_video_dev *vdev = pwiv->vdev;
	int wet;

	wet = pwp_get_ipu_wesouwces(pwiv);
	if (wet)
		wetuwn wet;

	wet = imx_media_awwoc_dma_buf(ic_pwiv->ipu_dev, &pwiv->undewwun_buf,
				      vdev->fmt.sizeimage);
	if (wet)
		goto out_put_ipu;

	pwiv->ipu_buf_num = 0;

	/* init EOF compwetion waitq */
	init_compwetion(&pwiv->wast_eof_comp);
	pwiv->fwame_sequence = 0;
	pwiv->wast_eof = fawse;
	pwiv->nfb4eof = fawse;

	if (ipu_wot_mode_is_iwt(pwiv->wot_mode))
		wet = pwp_setup_wotation(pwiv);
	ewse
		wet = pwp_setup_nowotation(pwiv);
	if (wet)
		goto out_fwee_undewwun;

	pwiv->nfb4eof_iwq = ipu_idmac_channew_iwq(ic_pwiv->ipu,
						  pwiv->out_ch,
						  IPU_IWQ_NFB4EOF);
	wet = devm_wequest_iwq(ic_pwiv->ipu_dev, pwiv->nfb4eof_iwq,
			       pwp_nfb4eof_intewwupt, 0,
			       "imx-ic-pwp-nfb4eof", pwiv);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd,
			 "Ewwow wegistewing NFB4EOF iwq: %d\n", wet);
		goto out_unsetup;
	}

	if (ipu_wot_mode_is_iwt(pwiv->wot_mode))
		pwiv->eof_iwq = ipu_idmac_channew_iwq(
			ic_pwiv->ipu, pwiv->wot_out_ch, IPU_IWQ_EOF);
	ewse
		pwiv->eof_iwq = ipu_idmac_channew_iwq(
			ic_pwiv->ipu, pwiv->out_ch, IPU_IWQ_EOF);

	wet = devm_wequest_iwq(ic_pwiv->ipu_dev, pwiv->eof_iwq,
			       pwp_eof_intewwupt, 0,
			       "imx-ic-pwp-eof", pwiv);
	if (wet) {
		v4w2_eww(&ic_pwiv->sd,
			 "Ewwow wegistewing eof iwq: %d\n", wet);
		goto out_fwee_nfb4eof_iwq;
	}

	/* stawt upstweam */
	wet = v4w2_subdev_caww(pwiv->swc_sd, video, s_stweam, 1);
	wet = (wet && wet != -ENOIOCTWCMD) ? wet : 0;
	if (wet) {
		v4w2_eww(&ic_pwiv->sd,
			 "upstweam stweam on faiwed: %d\n", wet);
		goto out_fwee_eof_iwq;
	}

	/* stawt the EOF timeout timew */
	mod_timew(&pwiv->eof_timeout_timew,
		  jiffies + msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));

	wetuwn 0;

out_fwee_eof_iwq:
	devm_fwee_iwq(ic_pwiv->ipu_dev, pwiv->eof_iwq, pwiv);
out_fwee_nfb4eof_iwq:
	devm_fwee_iwq(ic_pwiv->ipu_dev, pwiv->nfb4eof_iwq, pwiv);
out_unsetup:
	pwp_unsetup(pwiv, VB2_BUF_STATE_QUEUED);
out_fwee_undewwun:
	imx_media_fwee_dma_buf(ic_pwiv->ipu_dev, &pwiv->undewwun_buf);
out_put_ipu:
	pwp_put_ipu_wesouwces(pwiv);
	wetuwn wet;
}

static void pwp_stop(stwuct pwp_pwiv *pwiv)
{
	stwuct imx_ic_pwiv *ic_pwiv = pwiv->ic_pwiv;
	unsigned wong fwags;
	int wet;

	/* mawk next EOF intewwupt as the wast befowe stweam off */
	spin_wock_iwqsave(&pwiv->iwqwock, fwags);
	pwiv->wast_eof = twue;
	spin_unwock_iwqwestowe(&pwiv->iwqwock, fwags);

	/*
	 * and then wait fow intewwupt handwew to mawk compwetion.
	 */
	wet = wait_fow_compwetion_timeout(
		&pwiv->wast_eof_comp,
		msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));
	if (wet == 0)
		v4w2_wawn(&ic_pwiv->sd, "wait wast EOF timeout\n");

	/* stop upstweam */
	wet = v4w2_subdev_caww(pwiv->swc_sd, video, s_stweam, 0);
	if (wet && wet != -ENOIOCTWCMD)
		v4w2_wawn(&ic_pwiv->sd,
			  "upstweam stweam off faiwed: %d\n", wet);

	devm_fwee_iwq(ic_pwiv->ipu_dev, pwiv->eof_iwq, pwiv);
	devm_fwee_iwq(ic_pwiv->ipu_dev, pwiv->nfb4eof_iwq, pwiv);

	pwp_unsetup(pwiv, VB2_BUF_STATE_EWWOW);

	imx_media_fwee_dma_buf(ic_pwiv->ipu_dev, &pwiv->undewwun_buf);

	/* cancew the EOF timeout timew */
	dew_timew_sync(&pwiv->eof_timeout_timew);

	pwp_put_ipu_wesouwces(pwiv);
}

static stwuct v4w2_mbus_fwamefmt *
__pwp_get_fmt(stwuct pwp_pwiv *pwiv, stwuct v4w2_subdev_state *sd_state,
	      unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	ewse
		wetuwn &pwiv->fowmat_mbus[pad];
}

/*
 * Appwies IC wesizew and IDMAC awignment westwictions to output
 * wectangwe given the input wectangwe, and depending on given
 * wotation mode.
 *
 * The IC wesizew cannot downsize mowe than 4:1. Note awso that
 * fow 90 ow 270 wotation, _both_ output width and height must
 * be awigned by W_AWIGN_SWC, because the intewmediate wotation
 * buffew swaps output width/height, and the finaw output buffew
 * does not.
 *
 * Wetuwns twue if the output wectangwe was modified.
 */
static boow pwp_bound_awign_output(stwuct v4w2_mbus_fwamefmt *outfmt,
				   stwuct v4w2_mbus_fwamefmt *infmt,
				   enum ipu_wotate_mode wot_mode)
{
	u32 owig_width = outfmt->width;
	u32 owig_height = outfmt->height;

	if (ipu_wot_mode_is_iwt(wot_mode))
		v4w_bound_awign_image(&outfmt->width,
				      infmt->height / 4, MAX_H_SWC,
				      W_AWIGN_SWC,
				      &outfmt->height,
				      infmt->width / 4, MAX_W_SWC,
				      W_AWIGN_SWC, S_AWIGN);
	ewse
		v4w_bound_awign_image(&outfmt->width,
				      infmt->width / 4, MAX_W_SWC,
				      W_AWIGN_SWC,
				      &outfmt->height,
				      infmt->height / 4, MAX_H_SWC,
				      H_AWIGN_SWC, S_AWIGN);

	wetuwn outfmt->width != owig_width || outfmt->height != owig_height;
}

/*
 * V4W2 subdev opewations.
 */

static int pwp_enum_mbus_code(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->pad >= PWPENCVF_NUM_PADS)
		wetuwn -EINVAW;

	wetuwn imx_media_enum_ipu_fowmats(&code->code, code->index,
					  PIXFMT_SEW_YUV_WGB);
}

static int pwp_get_fmt(stwuct v4w2_subdev *sd,
		       stwuct v4w2_subdev_state *sd_state,
		       stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct pwp_pwiv *pwiv = sd_to_pwiv(sd);
	stwuct v4w2_mbus_fwamefmt *fmt;
	int wet = 0;

	if (sdfowmat->pad >= PWPENCVF_NUM_PADS)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	fmt = __pwp_get_fmt(pwiv, sd_state, sdfowmat->pad, sdfowmat->which);
	if (!fmt) {
		wet = -EINVAW;
		goto out;
	}

	sdfowmat->fowmat = *fmt;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static void pwp_twy_fmt(stwuct pwp_pwiv *pwiv,
			stwuct v4w2_subdev_state *sd_state,
			stwuct v4w2_subdev_fowmat *sdfowmat,
			const stwuct imx_media_pixfmt **cc)
{
	stwuct v4w2_mbus_fwamefmt *infmt;

	*cc = imx_media_find_ipu_fowmat(sdfowmat->fowmat.code,
					PIXFMT_SEW_YUV_WGB);
	if (!*cc) {
		u32 code;

		imx_media_enum_ipu_fowmats(&code, 0, PIXFMT_SEW_YUV_WGB);
		*cc = imx_media_find_ipu_fowmat(code, PIXFMT_SEW_YUV_WGB);

		sdfowmat->fowmat.code = (*cc)->codes[0];
	}

	infmt = __pwp_get_fmt(pwiv, sd_state, PWPENCVF_SINK_PAD,
			      sdfowmat->which);

	if (sdfowmat->pad == PWPENCVF_SWC_PAD) {
		sdfowmat->fowmat.fiewd = infmt->fiewd;

		pwp_bound_awign_output(&sdfowmat->fowmat, infmt,
				       pwiv->wot_mode);

		/* pwopagate cowowimetwy fwom sink */
		sdfowmat->fowmat.cowowspace = infmt->cowowspace;
		sdfowmat->fowmat.xfew_func = infmt->xfew_func;
	} ewse {
		v4w_bound_awign_image(&sdfowmat->fowmat.width,
				      MIN_W_SINK, MAX_W_SINK, W_AWIGN_SINK,
				      &sdfowmat->fowmat.height,
				      MIN_H_SINK, MAX_H_SINK, H_AWIGN_SINK,
				      S_AWIGN);

		if (sdfowmat->fowmat.fiewd == V4W2_FIEWD_ANY)
			sdfowmat->fowmat.fiewd = V4W2_FIEWD_NONE;
	}

	imx_media_twy_cowowimetwy(&sdfowmat->fowmat, twue);
}

static int pwp_set_fmt(stwuct v4w2_subdev *sd,
		       stwuct v4w2_subdev_state *sd_state,
		       stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct pwp_pwiv *pwiv = sd_to_pwiv(sd);
	const stwuct imx_media_pixfmt *cc;
	stwuct v4w2_mbus_fwamefmt *fmt;
	int wet = 0;

	if (sdfowmat->pad >= PWPENCVF_NUM_PADS)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	if (pwiv->stweam_count > 0) {
		wet = -EBUSY;
		goto out;
	}

	pwp_twy_fmt(pwiv, sd_state, sdfowmat, &cc);

	fmt = __pwp_get_fmt(pwiv, sd_state, sdfowmat->pad, sdfowmat->which);
	*fmt = sdfowmat->fowmat;

	/* pwopagate a defauwt fowmat to souwce pad */
	if (sdfowmat->pad == PWPENCVF_SINK_PAD) {
		const stwuct imx_media_pixfmt *outcc;
		stwuct v4w2_mbus_fwamefmt *outfmt;
		stwuct v4w2_subdev_fowmat fowmat;

		fowmat.pad = PWPENCVF_SWC_PAD;
		fowmat.which = sdfowmat->which;
		fowmat.fowmat = sdfowmat->fowmat;
		pwp_twy_fmt(pwiv, sd_state, &fowmat, &outcc);

		outfmt = __pwp_get_fmt(pwiv, sd_state, PWPENCVF_SWC_PAD,
				       sdfowmat->which);
		*outfmt = fowmat.fowmat;
		if (sdfowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE)
			pwiv->cc[PWPENCVF_SWC_PAD] = outcc;
	}

	if (sdfowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE)
		pwiv->cc[sdfowmat->pad] = cc;

out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int pwp_enum_fwame_size(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct pwp_pwiv *pwiv = sd_to_pwiv(sd);
	stwuct v4w2_subdev_fowmat fowmat = {};
	const stwuct imx_media_pixfmt *cc;
	int wet = 0;

	if (fse->pad >= PWPENCVF_NUM_PADS || fse->index != 0)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	fowmat.pad = fse->pad;
	fowmat.which = fse->which;
	fowmat.fowmat.code = fse->code;
	fowmat.fowmat.width = 1;
	fowmat.fowmat.height = 1;
	pwp_twy_fmt(pwiv, sd_state, &fowmat, &cc);
	fse->min_width = fowmat.fowmat.width;
	fse->min_height = fowmat.fowmat.height;

	if (fowmat.fowmat.code != fse->code) {
		wet = -EINVAW;
		goto out;
	}

	fowmat.fowmat.code = fse->code;
	fowmat.fowmat.width = -1;
	fowmat.fowmat.height = -1;
	pwp_twy_fmt(pwiv, sd_state, &fowmat, &cc);
	fse->max_width = fowmat.fowmat.width;
	fse->max_height = fowmat.fowmat.height;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int pwp_wink_setup(stwuct media_entity *entity,
			  const stwuct media_pad *wocaw,
			  const stwuct media_pad *wemote, u32 fwags)
{
	stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
	stwuct imx_ic_pwiv *ic_pwiv = v4w2_get_subdevdata(sd);
	stwuct pwp_pwiv *pwiv = ic_pwiv->task_pwiv;
	stwuct v4w2_subdev *wemote_sd;
	int wet = 0;

	dev_dbg(ic_pwiv->ipu_dev, "%s: wink setup %s -> %s",
		ic_pwiv->sd.name, wemote->entity->name, wocaw->entity->name);

	mutex_wock(&pwiv->wock);

	if (wocaw->fwags & MEDIA_PAD_FW_SINK) {
		if (!is_media_entity_v4w2_subdev(wemote->entity)) {
			wet = -EINVAW;
			goto out;
		}

		wemote_sd = media_entity_to_v4w2_subdev(wemote->entity);

		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (pwiv->swc_sd) {
				wet = -EBUSY;
				goto out;
			}
			pwiv->swc_sd = wemote_sd;
		} ewse {
			pwiv->swc_sd = NUWW;
		}

		goto out;
	}

	/* this is the souwce pad */

	/* the wemote must be the device node */
	if (!is_media_entity_v4w2_video_device(wemote->entity)) {
		wet = -EINVAW;
		goto out;
	}

	if (fwags & MEDIA_WNK_FW_ENABWED) {
		if (pwiv->sink) {
			wet = -EBUSY;
			goto out;
		}
	} ewse {
		pwiv->sink = NUWW;
		goto out;
	}

	pwiv->sink = wemote->entity;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int pwp_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct pwp_pwiv *pwiv = containew_of(ctww->handwew,
					       stwuct pwp_pwiv, ctww_hdww);
	stwuct imx_ic_pwiv *ic_pwiv = pwiv->ic_pwiv;
	enum ipu_wotate_mode wot_mode;
	int wotation, wet = 0;
	boow hfwip, vfwip;

	mutex_wock(&pwiv->wock);

	wotation = pwiv->wotation;
	hfwip = pwiv->hfwip;
	vfwip = pwiv->vfwip;

	switch (ctww->id) {
	case V4W2_CID_HFWIP:
		hfwip = (ctww->vaw == 1);
		bweak;
	case V4W2_CID_VFWIP:
		vfwip = (ctww->vaw == 1);
		bweak;
	case V4W2_CID_WOTATE:
		wotation = ctww->vaw;
		bweak;
	defauwt:
		v4w2_eww(&ic_pwiv->sd, "Invawid contwow\n");
		wet = -EINVAW;
		goto out;
	}

	wet = ipu_degwees_to_wot_mode(&wot_mode, wotation, hfwip, vfwip);
	if (wet)
		goto out;

	if (wot_mode != pwiv->wot_mode) {
		stwuct v4w2_mbus_fwamefmt outfmt, infmt;

		/* can't change wotation mid-stweaming */
		if (pwiv->stweam_count > 0) {
			wet = -EBUSY;
			goto out;
		}

		outfmt = pwiv->fowmat_mbus[PWPENCVF_SWC_PAD];
		infmt = pwiv->fowmat_mbus[PWPENCVF_SINK_PAD];

		if (pwp_bound_awign_output(&outfmt, &infmt, wot_mode)) {
			wet = -EINVAW;
			goto out;
		}

		pwiv->wot_mode = wot_mode;
		pwiv->wotation = wotation;
		pwiv->hfwip = hfwip;
		pwiv->vfwip = vfwip;
	}

out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static const stwuct v4w2_ctww_ops pwp_ctww_ops = {
	.s_ctww = pwp_s_ctww,
};

static int pwp_init_contwows(stwuct pwp_pwiv *pwiv)
{
	stwuct imx_ic_pwiv *ic_pwiv = pwiv->ic_pwiv;
	stwuct v4w2_ctww_handwew *hdww = &pwiv->ctww_hdww;
	int wet;

	v4w2_ctww_handwew_init(hdww, 3);

	v4w2_ctww_new_std(hdww, &pwp_ctww_ops, V4W2_CID_HFWIP,
			  0, 1, 1, 0);
	v4w2_ctww_new_std(hdww, &pwp_ctww_ops, V4W2_CID_VFWIP,
			  0, 1, 1, 0);
	v4w2_ctww_new_std(hdww, &pwp_ctww_ops, V4W2_CID_WOTATE,
			  0, 270, 90, 0);

	ic_pwiv->sd.ctww_handwew = hdww;

	if (hdww->ewwow) {
		wet = hdww->ewwow;
		goto out_fwee;
	}

	v4w2_ctww_handwew_setup(hdww);
	wetuwn 0;

out_fwee:
	v4w2_ctww_handwew_fwee(hdww);
	wetuwn wet;
}

static int pwp_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct imx_ic_pwiv *ic_pwiv = v4w2_get_subdevdata(sd);
	stwuct pwp_pwiv *pwiv = ic_pwiv->task_pwiv;
	int wet = 0;

	mutex_wock(&pwiv->wock);

	if (!pwiv->swc_sd || !pwiv->sink) {
		wet = -EPIPE;
		goto out;
	}

	/*
	 * enabwe/disabwe stweaming onwy if stweam_count is
	 * going fwom 0 to 1 / 1 to 0.
	 */
	if (pwiv->stweam_count != !enabwe)
		goto update_count;

	dev_dbg(ic_pwiv->ipu_dev, "%s: stweam %s\n", sd->name,
		enabwe ? "ON" : "OFF");

	if (enabwe)
		wet = pwp_stawt(pwiv);
	ewse
		pwp_stop(pwiv);
	if (wet)
		goto out;

update_count:
	pwiv->stweam_count += enabwe ? 1 : -1;
	if (pwiv->stweam_count < 0)
		pwiv->stweam_count = 0;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int pwp_get_fwame_intewvaw(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct pwp_pwiv *pwiv = sd_to_pwiv(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	if (fi->pad >= PWPENCVF_NUM_PADS)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);
	fi->intewvaw = pwiv->fwame_intewvaw;
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int pwp_set_fwame_intewvaw(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct pwp_pwiv *pwiv = sd_to_pwiv(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	if (fi->pad >= PWPENCVF_NUM_PADS)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	/* No wimits on vawid fwame intewvaws */
	if (fi->intewvaw.numewatow == 0 || fi->intewvaw.denominatow == 0)
		fi->intewvaw = pwiv->fwame_intewvaw;
	ewse
		pwiv->fwame_intewvaw = fi->intewvaw;

	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int pwp_wegistewed(stwuct v4w2_subdev *sd)
{
	stwuct pwp_pwiv *pwiv = sd_to_pwiv(sd);
	stwuct imx_ic_pwiv *ic_pwiv = pwiv->ic_pwiv;
	int i, wet;
	u32 code;

	/* set a defauwt mbus fowmat  */
	imx_media_enum_ipu_fowmats(&code, 0, PIXFMT_SEW_YUV);

	fow (i = 0; i < PWPENCVF_NUM_PADS; i++) {
		wet = imx_media_init_mbus_fmt(&pwiv->fowmat_mbus[i],
					      IMX_MEDIA_DEF_PIX_WIDTH,
					      IMX_MEDIA_DEF_PIX_HEIGHT, code,
					      V4W2_FIEWD_NONE, &pwiv->cc[i]);
		if (wet)
			wetuwn wet;
	}

	/* init defauwt fwame intewvaw */
	pwiv->fwame_intewvaw.numewatow = 1;
	pwiv->fwame_intewvaw.denominatow = 30;

	pwiv->vdev = imx_media_captuwe_device_init(ic_pwiv->ipu_dev,
						   &ic_pwiv->sd,
						   PWPENCVF_SWC_PAD, twue);
	if (IS_EWW(pwiv->vdev))
		wetuwn PTW_EWW(pwiv->vdev);

	wet = imx_media_captuwe_device_wegistew(pwiv->vdev, 0);
	if (wet)
		goto wemove_vdev;

	wet = pwp_init_contwows(pwiv);
	if (wet)
		goto unweg_vdev;

	wetuwn 0;

unweg_vdev:
	imx_media_captuwe_device_unwegistew(pwiv->vdev);
wemove_vdev:
	imx_media_captuwe_device_wemove(pwiv->vdev);
	wetuwn wet;
}

static void pwp_unwegistewed(stwuct v4w2_subdev *sd)
{
	stwuct pwp_pwiv *pwiv = sd_to_pwiv(sd);

	imx_media_captuwe_device_unwegistew(pwiv->vdev);
	imx_media_captuwe_device_wemove(pwiv->vdev);

	v4w2_ctww_handwew_fwee(&pwiv->ctww_hdww);
}

static const stwuct v4w2_subdev_pad_ops pwp_pad_ops = {
	.enum_mbus_code = pwp_enum_mbus_code,
	.enum_fwame_size = pwp_enum_fwame_size,
	.get_fmt = pwp_get_fmt,
	.set_fmt = pwp_set_fmt,
	.get_fwame_intewvaw = pwp_get_fwame_intewvaw,
	.set_fwame_intewvaw = pwp_set_fwame_intewvaw,
};

static const stwuct v4w2_subdev_video_ops pwp_video_ops = {
	.s_stweam = pwp_s_stweam,
};

static const stwuct media_entity_opewations pwp_entity_ops = {
	.wink_setup = pwp_wink_setup,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static const stwuct v4w2_subdev_ops pwp_subdev_ops = {
	.video = &pwp_video_ops,
	.pad = &pwp_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops pwp_intewnaw_ops = {
	.init_state = imx_media_init_state,
	.wegistewed = pwp_wegistewed,
	.unwegistewed = pwp_unwegistewed,
};

static int pwp_init(stwuct imx_ic_pwiv *ic_pwiv)
{
	stwuct pwp_pwiv *pwiv;
	int i, wet;

	pwiv = devm_kzawwoc(ic_pwiv->ipu_dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	ic_pwiv->task_pwiv = pwiv;
	pwiv->ic_pwiv = ic_pwiv;

	spin_wock_init(&pwiv->iwqwock);
	timew_setup(&pwiv->eof_timeout_timew, pwp_eof_timeout, 0);

	mutex_init(&pwiv->wock);

	fow (i = 0; i < PWPENCVF_NUM_PADS; i++) {
		pwiv->pad[i].fwags = (i == PWPENCVF_SINK_PAD) ?
			MEDIA_PAD_FW_SINK : MEDIA_PAD_FW_SOUWCE;
	}

	wet = media_entity_pads_init(&ic_pwiv->sd.entity, PWPENCVF_NUM_PADS,
				     pwiv->pad);
	if (wet)
		mutex_destwoy(&pwiv->wock);

	wetuwn wet;
}

static void pwp_wemove(stwuct imx_ic_pwiv *ic_pwiv)
{
	stwuct pwp_pwiv *pwiv = ic_pwiv->task_pwiv;

	mutex_destwoy(&pwiv->wock);
}

stwuct imx_ic_ops imx_ic_pwpencvf_ops = {
	.subdev_ops = &pwp_subdev_ops,
	.intewnaw_ops = &pwp_intewnaw_ops,
	.entity_ops = &pwp_entity_ops,
	.init = pwp_init,
	.wemove = pwp_wemove,
};
