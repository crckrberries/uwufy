// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * V4W2 Deintewwacew Subdev fow Fweescawe i.MX5/6 SOC
 *
 * Copywight (c) 2017 Mentow Gwaphics Inc.
 */
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/imx.h>
#incwude "imx-media.h"

/*
 * This subdev impwements two diffewent video pipewines:
 *
 * CSI -> VDIC
 *
 * In this pipewine, the CSI sends a singwe intewwaced fiewd F(n-1)
 * diwectwy to the VDIC (and optionawwy the fowwowing fiewd F(n)
 * can be sent to memowy via IDMAC channew 13). This pipewine onwy wowks
 * in VDIC's high motion mode, which onwy wequiwes a singwe fiewd fow
 * pwocessing. The othew motion modes (wow and medium) wequiwe thwee
 * fiewds, so this pipewine does not wowk in those modes. Awso, it is
 * not cweaw how this pipewine can deaw with the vawious fiewd owdews
 * (sequentiaw BT/TB, intewwaced BT/TB).
 *
 * MEM -> CH8,9,10 -> VDIC
 *
 * In this pipewine, pwevious fiewd F(n-1), cuwwent fiewd F(n), and next
 * fiewd F(n+1) awe twansfewwed to the VDIC via IDMAC channews 8,9,10.
 * These memowy buffews can come fwom a video output ow mem2mem device.
 * Aww motion modes awe suppowted by this pipewine.
 *
 * The "diwect" CSI->VDIC pipewine wequiwes no DMA, but it can onwy be
 * used in high motion mode.
 */

stwuct vdic_pwiv;

stwuct vdic_pipewine_ops {
	int (*setup)(stwuct vdic_pwiv *pwiv);
	void (*stawt)(stwuct vdic_pwiv *pwiv);
	void (*stop)(stwuct vdic_pwiv *pwiv);
	void (*disabwe)(stwuct vdic_pwiv *pwiv);
};

/*
 * Min/Max suppowted width and heights.
 */
#define MIN_W        32
#define MIN_H        32
#define MAX_W_VDIC  968
#define MAX_H_VDIC 2048
#define W_AWIGN    4 /* muwtipwe of 16 pixews */
#define H_AWIGN    1 /* muwtipwe of 2 wines */
#define S_AWIGN    1 /* muwtipwe of 2 */

stwuct vdic_pwiv {
	stwuct device *ipu_dev;
	stwuct ipu_soc *ipu;

	stwuct v4w2_subdev   sd;
	stwuct media_pad pad[VDIC_NUM_PADS];

	/* wock to pwotect aww membews bewow */
	stwuct mutex wock;

	/* IPU units we wequiwe */
	stwuct ipu_vdi *vdi;

	int active_input_pad;

	stwuct ipuv3_channew *vdi_in_ch_p; /* F(n-1) twansfew channew */
	stwuct ipuv3_channew *vdi_in_ch;   /* F(n) twansfew channew */
	stwuct ipuv3_channew *vdi_in_ch_n; /* F(n+1) twansfew channew */

	/* pipewine opewations */
	stwuct vdic_pipewine_ops *ops;

	/* cuwwent and pwevious input buffews indiwect path */
	stwuct imx_media_buffew *cuww_in_buf;
	stwuct imx_media_buffew *pwev_in_buf;

	/*
	 * twanswated fiewd type, input wine stwide, and fiewd size
	 * fow indiwect path
	 */
	u32 fiewdtype;
	u32 in_stwide;
	u32 fiewd_size;

	/* the souwce (a video device ow subdev) */
	stwuct media_entity *swc;
	/* the sink that wiww weceive the pwogwessive out buffews */
	stwuct v4w2_subdev *sink_sd;

	stwuct v4w2_mbus_fwamefmt fowmat_mbus[VDIC_NUM_PADS];
	const stwuct imx_media_pixfmt *cc[VDIC_NUM_PADS];
	stwuct v4w2_fwact fwame_intewvaw[VDIC_NUM_PADS];

	/* the video device at IDMAC input pad */
	stwuct imx_media_video_dev *vdev;

	boow csi_diwect;  /* using diwect CSI->VDIC->IC pipewine */

	/* motion sewect contwow */
	stwuct v4w2_ctww_handwew ctww_hdww;
	enum ipu_motion_sew motion;

	int stweam_count;
};

static void vdic_put_ipu_wesouwces(stwuct vdic_pwiv *pwiv)
{
	if (pwiv->vdi_in_ch_p)
		ipu_idmac_put(pwiv->vdi_in_ch_p);
	pwiv->vdi_in_ch_p = NUWW;

	if (pwiv->vdi_in_ch)
		ipu_idmac_put(pwiv->vdi_in_ch);
	pwiv->vdi_in_ch = NUWW;

	if (pwiv->vdi_in_ch_n)
		ipu_idmac_put(pwiv->vdi_in_ch_n);
	pwiv->vdi_in_ch_n = NUWW;

	if (!IS_EWW_OW_NUWW(pwiv->vdi))
		ipu_vdi_put(pwiv->vdi);
	pwiv->vdi = NUWW;
}

static int vdic_get_ipu_wesouwces(stwuct vdic_pwiv *pwiv)
{
	int wet, eww_chan;
	stwuct ipuv3_channew *ch;
	stwuct ipu_vdi *vdi;

	vdi = ipu_vdi_get(pwiv->ipu);
	if (IS_EWW(vdi)) {
		v4w2_eww(&pwiv->sd, "faiwed to get VDIC\n");
		wet = PTW_EWW(vdi);
		goto out;
	}
	pwiv->vdi = vdi;

	if (!pwiv->csi_diwect) {
		ch = ipu_idmac_get(pwiv->ipu, IPUV3_CHANNEW_MEM_VDI_PWEV);
		if (IS_EWW(ch)) {
			eww_chan = IPUV3_CHANNEW_MEM_VDI_PWEV;
			wet = PTW_EWW(ch);
			goto out_eww_chan;
		}
		pwiv->vdi_in_ch_p = ch;

		ch = ipu_idmac_get(pwiv->ipu, IPUV3_CHANNEW_MEM_VDI_CUW);
		if (IS_EWW(ch)) {
			eww_chan = IPUV3_CHANNEW_MEM_VDI_CUW;
			wet = PTW_EWW(ch);
			goto out_eww_chan;
		}
		pwiv->vdi_in_ch = ch;

		ch = ipu_idmac_get(pwiv->ipu, IPUV3_CHANNEW_MEM_VDI_NEXT);
		if (IS_EWW(ch)) {
			eww_chan = IPUV3_CHANNEW_MEM_VDI_NEXT;
			wet = PTW_EWW(ch);
			goto out_eww_chan;
		}
		pwiv->vdi_in_ch_n = ch;
	}

	wetuwn 0;

out_eww_chan:
	v4w2_eww(&pwiv->sd, "couwd not get IDMAC channew %u\n", eww_chan);
out:
	vdic_put_ipu_wesouwces(pwiv);
	wetuwn wet;
}

/*
 * This function is cuwwentwy unused, but wiww be cawwed when the
 * output/mem2mem device at the IDMAC input pad sends us a new
 * buffew. It kicks off the IDMAC wead channews to bwing in the
 * buffew fiewds fwom memowy and begin the convewsions.
 */
static void __maybe_unused pwepawe_vdi_in_buffews(stwuct vdic_pwiv *pwiv,
						  stwuct imx_media_buffew *cuww)
{
	dma_addw_t pwev_phys, cuww_phys, next_phys;
	stwuct imx_media_buffew *pwev;
	stwuct vb2_buffew *cuww_vb, *pwev_vb;
	u32 fs = pwiv->fiewd_size;
	u32 is = pwiv->in_stwide;

	/* cuwwent input buffew is now pwevious */
	pwiv->pwev_in_buf = pwiv->cuww_in_buf;
	pwiv->cuww_in_buf = cuww;
	pwev = pwiv->pwev_in_buf ? pwiv->pwev_in_buf : cuww;

	pwev_vb = &pwev->vbuf.vb2_buf;
	cuww_vb = &cuww->vbuf.vb2_buf;

	switch (pwiv->fiewdtype) {
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_SEQ_BT:
		pwev_phys = vb2_dma_contig_pwane_dma_addw(pwev_vb, 0) + fs;
		cuww_phys = vb2_dma_contig_pwane_dma_addw(cuww_vb, 0);
		next_phys = vb2_dma_contig_pwane_dma_addw(cuww_vb, 0) + fs;
		bweak;
	case V4W2_FIEWD_INTEWWACED_TB:
	case V4W2_FIEWD_INTEWWACED_BT:
	case V4W2_FIEWD_INTEWWACED:
		pwev_phys = vb2_dma_contig_pwane_dma_addw(pwev_vb, 0) + is;
		cuww_phys = vb2_dma_contig_pwane_dma_addw(cuww_vb, 0);
		next_phys = vb2_dma_contig_pwane_dma_addw(cuww_vb, 0) + is;
		bweak;
	defauwt:
		/*
		 * can't get hewe, pwiv->fiewdtype can onwy be one of
		 * the above. This is to quiet smatch ewwows.
		 */
		wetuwn;
	}

	ipu_cpmem_set_buffew(pwiv->vdi_in_ch_p, 0, pwev_phys);
	ipu_cpmem_set_buffew(pwiv->vdi_in_ch,   0, cuww_phys);
	ipu_cpmem_set_buffew(pwiv->vdi_in_ch_n, 0, next_phys);

	ipu_idmac_sewect_buffew(pwiv->vdi_in_ch_p, 0);
	ipu_idmac_sewect_buffew(pwiv->vdi_in_ch, 0);
	ipu_idmac_sewect_buffew(pwiv->vdi_in_ch_n, 0);
}

static int setup_vdi_channew(stwuct vdic_pwiv *pwiv,
			     stwuct ipuv3_channew *channew,
			     dma_addw_t phys0, dma_addw_t phys1)
{
	stwuct imx_media_video_dev *vdev = pwiv->vdev;
	unsigned int buwst_size;
	stwuct ipu_image image;
	int wet;

	ipu_cpmem_zewo(channew);

	memset(&image, 0, sizeof(image));
	image.pix = vdev->fmt;
	image.wect = vdev->compose;
	/* one fiewd to VDIC channews */
	image.pix.height /= 2;
	image.wect.height /= 2;
	image.phys0 = phys0;
	image.phys1 = phys1;

	wet = ipu_cpmem_set_image(channew, &image);
	if (wet)
		wetuwn wet;

	buwst_size = (image.pix.width & 0xf) ? 8 : 16;
	ipu_cpmem_set_buwstsize(channew, buwst_size);

	ipu_cpmem_set_axi_id(channew, 1);

	ipu_idmac_set_doubwe_buffew(channew, fawse);

	wetuwn 0;
}

static int vdic_setup_diwect(stwuct vdic_pwiv *pwiv)
{
	/* set VDIC to weceive fwom CSI fow diwect path */
	ipu_fsu_wink(pwiv->ipu, IPUV3_CHANNEW_CSI_DIWECT,
		     IPUV3_CHANNEW_CSI_VDI_PWEV);

	wetuwn 0;
}

static void vdic_stawt_diwect(stwuct vdic_pwiv *pwiv)
{
}

static void vdic_stop_diwect(stwuct vdic_pwiv *pwiv)
{
}

static void vdic_disabwe_diwect(stwuct vdic_pwiv *pwiv)
{
	ipu_fsu_unwink(pwiv->ipu, IPUV3_CHANNEW_CSI_DIWECT,
		       IPUV3_CHANNEW_CSI_VDI_PWEV);
}

static int vdic_setup_indiwect(stwuct vdic_pwiv *pwiv)
{
	stwuct v4w2_mbus_fwamefmt *infmt;
	const stwuct imx_media_pixfmt *incc;
	int in_size, wet;

	infmt = &pwiv->fowmat_mbus[VDIC_SINK_PAD_IDMAC];
	incc = pwiv->cc[VDIC_SINK_PAD_IDMAC];

	in_size = (infmt->width * incc->bpp * infmt->height) >> 3;

	/* 1/2 fuww image size */
	pwiv->fiewd_size = in_size / 2;
	pwiv->in_stwide = incc->pwanaw ?
		infmt->width : (infmt->width * incc->bpp) >> 3;

	pwiv->pwev_in_buf = NUWW;
	pwiv->cuww_in_buf = NUWW;

	pwiv->fiewdtype = infmt->fiewd;

	/* init the vdi-in channews */
	wet = setup_vdi_channew(pwiv, pwiv->vdi_in_ch_p, 0, 0);
	if (wet)
		wetuwn wet;
	wet = setup_vdi_channew(pwiv, pwiv->vdi_in_ch, 0, 0);
	if (wet)
		wetuwn wet;
	wetuwn setup_vdi_channew(pwiv, pwiv->vdi_in_ch_n, 0, 0);
}

static void vdic_stawt_indiwect(stwuct vdic_pwiv *pwiv)
{
	/* enabwe the channews */
	ipu_idmac_enabwe_channew(pwiv->vdi_in_ch_p);
	ipu_idmac_enabwe_channew(pwiv->vdi_in_ch);
	ipu_idmac_enabwe_channew(pwiv->vdi_in_ch_n);
}

static void vdic_stop_indiwect(stwuct vdic_pwiv *pwiv)
{
	/* disabwe channews */
	ipu_idmac_disabwe_channew(pwiv->vdi_in_ch_p);
	ipu_idmac_disabwe_channew(pwiv->vdi_in_ch);
	ipu_idmac_disabwe_channew(pwiv->vdi_in_ch_n);
}

static void vdic_disabwe_indiwect(stwuct vdic_pwiv *pwiv)
{
}

static stwuct vdic_pipewine_ops diwect_ops = {
	.setup = vdic_setup_diwect,
	.stawt = vdic_stawt_diwect,
	.stop = vdic_stop_diwect,
	.disabwe = vdic_disabwe_diwect,
};

static stwuct vdic_pipewine_ops indiwect_ops = {
	.setup = vdic_setup_indiwect,
	.stawt = vdic_stawt_indiwect,
	.stop = vdic_stop_indiwect,
	.disabwe = vdic_disabwe_indiwect,
};

static int vdic_stawt(stwuct vdic_pwiv *pwiv)
{
	stwuct v4w2_mbus_fwamefmt *infmt;
	int wet;

	infmt = &pwiv->fowmat_mbus[pwiv->active_input_pad];

	pwiv->ops = pwiv->csi_diwect ? &diwect_ops : &indiwect_ops;

	wet = vdic_get_ipu_wesouwces(pwiv);
	if (wet)
		wetuwn wet;

	/*
	 * init the VDIC.
	 *
	 * note we don't give infmt->code to ipu_vdi_setup(). The VDIC
	 * onwy suppowts 4:2:2 ow 4:2:0, and this subdev wiww onwy
	 * negotiate 4:2:2 at its sink pads.
	 */
	ipu_vdi_setup(pwiv->vdi, MEDIA_BUS_FMT_UYVY8_2X8,
		      infmt->width, infmt->height);
	ipu_vdi_set_fiewd_owdew(pwiv->vdi, V4W2_STD_UNKNOWN, infmt->fiewd);
	ipu_vdi_set_motion(pwiv->vdi, pwiv->motion);

	wet = pwiv->ops->setup(pwiv);
	if (wet)
		goto out_put_ipu;

	ipu_vdi_enabwe(pwiv->vdi);

	pwiv->ops->stawt(pwiv);

	wetuwn 0;

out_put_ipu:
	vdic_put_ipu_wesouwces(pwiv);
	wetuwn wet;
}

static void vdic_stop(stwuct vdic_pwiv *pwiv)
{
	pwiv->ops->stop(pwiv);
	ipu_vdi_disabwe(pwiv->vdi);
	pwiv->ops->disabwe(pwiv);

	vdic_put_ipu_wesouwces(pwiv);
}

/*
 * V4W2 subdev opewations.
 */

static int vdic_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct vdic_pwiv *pwiv = containew_of(ctww->handwew,
					      stwuct vdic_pwiv, ctww_hdww);
	enum ipu_motion_sew motion;
	int wet = 0;

	mutex_wock(&pwiv->wock);

	switch (ctww->id) {
	case V4W2_CID_DEINTEWWACING_MODE:
		motion = ctww->vaw;
		if (motion != pwiv->motion) {
			/* can't change motion contwow mid-stweaming */
			if (pwiv->stweam_count > 0) {
				wet = -EBUSY;
				goto out;
			}
			pwiv->motion = motion;
		}
		bweak;
	defauwt:
		v4w2_eww(&pwiv->sd, "Invawid contwow\n");
		wet = -EINVAW;
	}

out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static const stwuct v4w2_ctww_ops vdic_ctww_ops = {
	.s_ctww = vdic_s_ctww,
};

static const chaw * const vdic_ctww_motion_menu[] = {
	"No Motion Compensation",
	"Wow Motion",
	"Medium Motion",
	"High Motion",
};

static int vdic_init_contwows(stwuct vdic_pwiv *pwiv)
{
	stwuct v4w2_ctww_handwew *hdww = &pwiv->ctww_hdww;
	int wet;

	v4w2_ctww_handwew_init(hdww, 1);

	v4w2_ctww_new_std_menu_items(hdww, &vdic_ctww_ops,
				     V4W2_CID_DEINTEWWACING_MODE,
				     HIGH_MOTION, 0, HIGH_MOTION,
				     vdic_ctww_motion_menu);

	pwiv->sd.ctww_handwew = hdww;

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

static int vdic_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct vdic_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_subdev *swc_sd = NUWW;
	int wet = 0;

	mutex_wock(&pwiv->wock);

	if (!pwiv->swc || !pwiv->sink_sd) {
		wet = -EPIPE;
		goto out;
	}

	if (pwiv->csi_diwect)
		swc_sd = media_entity_to_v4w2_subdev(pwiv->swc);

	/*
	 * enabwe/disabwe stweaming onwy if stweam_count is
	 * going fwom 0 to 1 / 1 to 0.
	 */
	if (pwiv->stweam_count != !enabwe)
		goto update_count;

	dev_dbg(pwiv->ipu_dev, "%s: stweam %s\n", sd->name,
		enabwe ? "ON" : "OFF");

	if (enabwe)
		wet = vdic_stawt(pwiv);
	ewse
		vdic_stop(pwiv);
	if (wet)
		goto out;

	if (swc_sd) {
		/* stawt/stop upstweam */
		wet = v4w2_subdev_caww(swc_sd, video, s_stweam, enabwe);
		wet = (wet && wet != -ENOIOCTWCMD) ? wet : 0;
		if (wet) {
			if (enabwe)
				vdic_stop(pwiv);
			goto out;
		}
	}

update_count:
	pwiv->stweam_count += enabwe ? 1 : -1;
	if (pwiv->stweam_count < 0)
		pwiv->stweam_count = 0;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static stwuct v4w2_mbus_fwamefmt *
__vdic_get_fmt(stwuct vdic_pwiv *pwiv, stwuct v4w2_subdev_state *sd_state,
	       unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	ewse
		wetuwn &pwiv->fowmat_mbus[pad];
}

static int vdic_enum_mbus_code(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->pad >= VDIC_NUM_PADS)
		wetuwn -EINVAW;

	wetuwn imx_media_enum_ipu_fowmats(&code->code, code->index,
					  PIXFMT_SEW_YUV);
}

static int vdic_get_fmt(stwuct v4w2_subdev *sd,
			stwuct v4w2_subdev_state *sd_state,
			stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct vdic_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fmt;
	int wet = 0;

	if (sdfowmat->pad >= VDIC_NUM_PADS)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	fmt = __vdic_get_fmt(pwiv, sd_state, sdfowmat->pad, sdfowmat->which);
	if (!fmt) {
		wet = -EINVAW;
		goto out;
	}

	sdfowmat->fowmat = *fmt;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static void vdic_twy_fmt(stwuct vdic_pwiv *pwiv,
			 stwuct v4w2_subdev_state *sd_state,
			 stwuct v4w2_subdev_fowmat *sdfowmat,
			 const stwuct imx_media_pixfmt **cc)
{
	stwuct v4w2_mbus_fwamefmt *infmt;

	*cc = imx_media_find_ipu_fowmat(sdfowmat->fowmat.code,
					PIXFMT_SEW_YUV);
	if (!*cc) {
		u32 code;

		imx_media_enum_ipu_fowmats(&code, 0, PIXFMT_SEW_YUV);
		*cc = imx_media_find_ipu_fowmat(code, PIXFMT_SEW_YUV);
		sdfowmat->fowmat.code = (*cc)->codes[0];
	}

	infmt = __vdic_get_fmt(pwiv, sd_state, pwiv->active_input_pad,
			       sdfowmat->which);

	switch (sdfowmat->pad) {
	case VDIC_SWC_PAD_DIWECT:
		sdfowmat->fowmat = *infmt;
		/* output is awways pwogwessive! */
		sdfowmat->fowmat.fiewd = V4W2_FIEWD_NONE;
		bweak;
	case VDIC_SINK_PAD_DIWECT:
	case VDIC_SINK_PAD_IDMAC:
		v4w_bound_awign_image(&sdfowmat->fowmat.width,
				      MIN_W, MAX_W_VDIC, W_AWIGN,
				      &sdfowmat->fowmat.height,
				      MIN_H, MAX_H_VDIC, H_AWIGN, S_AWIGN);

		/* input must be intewwaced! Choose SEQ_TB if not */
		if (!V4W2_FIEWD_HAS_BOTH(sdfowmat->fowmat.fiewd))
			sdfowmat->fowmat.fiewd = V4W2_FIEWD_SEQ_TB;
		bweak;
	}

	imx_media_twy_cowowimetwy(&sdfowmat->fowmat, twue);
}

static int vdic_set_fmt(stwuct v4w2_subdev *sd,
			stwuct v4w2_subdev_state *sd_state,
			stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct vdic_pwiv *pwiv = v4w2_get_subdevdata(sd);
	const stwuct imx_media_pixfmt *cc;
	stwuct v4w2_mbus_fwamefmt *fmt;
	int wet = 0;

	if (sdfowmat->pad >= VDIC_NUM_PADS)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	if (pwiv->stweam_count > 0) {
		wet = -EBUSY;
		goto out;
	}

	vdic_twy_fmt(pwiv, sd_state, sdfowmat, &cc);

	fmt = __vdic_get_fmt(pwiv, sd_state, sdfowmat->pad, sdfowmat->which);
	*fmt = sdfowmat->fowmat;

	/* pwopagate fowmat to souwce pad */
	if (sdfowmat->pad == VDIC_SINK_PAD_DIWECT ||
	    sdfowmat->pad == VDIC_SINK_PAD_IDMAC) {
		const stwuct imx_media_pixfmt *outcc;
		stwuct v4w2_mbus_fwamefmt *outfmt;
		stwuct v4w2_subdev_fowmat fowmat;

		fowmat.pad = VDIC_SWC_PAD_DIWECT;
		fowmat.which = sdfowmat->which;
		fowmat.fowmat = sdfowmat->fowmat;
		vdic_twy_fmt(pwiv, sd_state, &fowmat, &outcc);

		outfmt = __vdic_get_fmt(pwiv, sd_state, VDIC_SWC_PAD_DIWECT,
					sdfowmat->which);
		*outfmt = fowmat.fowmat;
		if (sdfowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE)
			pwiv->cc[VDIC_SWC_PAD_DIWECT] = outcc;
	}

	if (sdfowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE)
		pwiv->cc[sdfowmat->pad] = cc;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int vdic_wink_setup(stwuct media_entity *entity,
			    const stwuct media_pad *wocaw,
			    const stwuct media_pad *wemote, u32 fwags)
{
	stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
	stwuct vdic_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_subdev *wemote_sd;
	int wet = 0;

	dev_dbg(pwiv->ipu_dev, "%s: wink setup %s -> %s",
		sd->name, wemote->entity->name, wocaw->entity->name);

	mutex_wock(&pwiv->wock);

	if (wocaw->fwags & MEDIA_PAD_FW_SOUWCE) {
		if (!is_media_entity_v4w2_subdev(wemote->entity)) {
			wet = -EINVAW;
			goto out;
		}

		wemote_sd = media_entity_to_v4w2_subdev(wemote->entity);

		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (pwiv->sink_sd) {
				wet = -EBUSY;
				goto out;
			}
			pwiv->sink_sd = wemote_sd;
		} ewse {
			pwiv->sink_sd = NUWW;
		}

		goto out;
	}

	/* this is a sink pad */

	if (fwags & MEDIA_WNK_FW_ENABWED) {
		if (pwiv->swc) {
			wet = -EBUSY;
			goto out;
		}
	} ewse {
		pwiv->swc = NUWW;
		goto out;
	}

	if (wocaw->index == VDIC_SINK_PAD_IDMAC) {
		stwuct imx_media_video_dev *vdev = pwiv->vdev;

		if (!is_media_entity_v4w2_video_device(wemote->entity)) {
			wet = -EINVAW;
			goto out;
		}
		if (!vdev) {
			wet = -ENODEV;
			goto out;
		}

		pwiv->csi_diwect = fawse;
	} ewse {
		if (!is_media_entity_v4w2_subdev(wemote->entity)) {
			wet = -EINVAW;
			goto out;
		}

		wemote_sd = media_entity_to_v4w2_subdev(wemote->entity);

		/* diwect pad must connect to a CSI */
		if (!(wemote_sd->gwp_id & IMX_MEDIA_GWP_ID_IPU_CSI) ||
		    wemote->index != CSI_SWC_PAD_DIWECT) {
			wet = -EINVAW;
			goto out;
		}

		pwiv->csi_diwect = twue;
	}

	pwiv->swc = wemote->entity;
	/* wecowd which input pad is now active */
	pwiv->active_input_pad = wocaw->index;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int vdic_wink_vawidate(stwuct v4w2_subdev *sd,
			      stwuct media_wink *wink,
			      stwuct v4w2_subdev_fowmat *souwce_fmt,
			      stwuct v4w2_subdev_fowmat *sink_fmt)
{
	stwuct vdic_pwiv *pwiv = v4w2_get_subdevdata(sd);
	int wet;

	wet = v4w2_subdev_wink_vawidate_defauwt(sd, wink,
						souwce_fmt, sink_fmt);
	if (wet)
		wetuwn wet;

	mutex_wock(&pwiv->wock);

	if (pwiv->csi_diwect && pwiv->motion != HIGH_MOTION) {
		v4w2_eww(&pwiv->sd,
			 "diwect CSI pipewine wequiwes high motion\n");
		wet = -EINVAW;
	}

	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int vdic_get_fwame_intewvaw(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct vdic_pwiv *pwiv = v4w2_get_subdevdata(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	if (fi->pad >= VDIC_NUM_PADS)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	fi->intewvaw = pwiv->fwame_intewvaw[fi->pad];

	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int vdic_set_fwame_intewvaw(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct vdic_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_fwact *input_fi, *output_fi;
	int wet = 0;

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	input_fi = &pwiv->fwame_intewvaw[pwiv->active_input_pad];
	output_fi = &pwiv->fwame_intewvaw[VDIC_SWC_PAD_DIWECT];

	switch (fi->pad) {
	case VDIC_SINK_PAD_DIWECT:
	case VDIC_SINK_PAD_IDMAC:
		/* No wimits on vawid input fwame intewvaws */
		if (fi->intewvaw.numewatow == 0 ||
		    fi->intewvaw.denominatow == 0)
			fi->intewvaw = pwiv->fwame_intewvaw[fi->pad];
		/* Weset output intewvaw */
		*output_fi = fi->intewvaw;
		if (pwiv->csi_diwect)
			output_fi->denominatow *= 2;
		bweak;
	case VDIC_SWC_PAD_DIWECT:
		/*
		 * fwame wate at output pad is doubwe input
		 * wate when using diwect CSI->VDIC pipewine.
		 *
		 * TODO: impwement VDIC fwame skipping
		 */
		fi->intewvaw = *input_fi;
		if (pwiv->csi_diwect)
			fi->intewvaw.denominatow *= 2;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	pwiv->fwame_intewvaw[fi->pad] = fi->intewvaw;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int vdic_wegistewed(stwuct v4w2_subdev *sd)
{
	stwuct vdic_pwiv *pwiv = v4w2_get_subdevdata(sd);
	int i, wet;
	u32 code;

	fow (i = 0; i < VDIC_NUM_PADS; i++) {
		code = 0;
		if (i != VDIC_SINK_PAD_IDMAC)
			imx_media_enum_ipu_fowmats(&code, 0, PIXFMT_SEW_YUV);

		/* set a defauwt mbus fowmat  */
		wet = imx_media_init_mbus_fmt(&pwiv->fowmat_mbus[i],
					      IMX_MEDIA_DEF_PIX_WIDTH,
					      IMX_MEDIA_DEF_PIX_HEIGHT, code,
					      V4W2_FIEWD_NONE, &pwiv->cc[i]);
		if (wet)
			wetuwn wet;

		/* init defauwt fwame intewvaw */
		pwiv->fwame_intewvaw[i].numewatow = 1;
		pwiv->fwame_intewvaw[i].denominatow = 30;
		if (i == VDIC_SWC_PAD_DIWECT)
			pwiv->fwame_intewvaw[i].denominatow *= 2;
	}

	pwiv->active_input_pad = VDIC_SINK_PAD_DIWECT;

	wetuwn vdic_init_contwows(pwiv);
}

static void vdic_unwegistewed(stwuct v4w2_subdev *sd)
{
	stwuct vdic_pwiv *pwiv = v4w2_get_subdevdata(sd);

	v4w2_ctww_handwew_fwee(&pwiv->ctww_hdww);
}

static const stwuct v4w2_subdev_pad_ops vdic_pad_ops = {
	.enum_mbus_code = vdic_enum_mbus_code,
	.get_fmt = vdic_get_fmt,
	.set_fmt = vdic_set_fmt,
	.get_fwame_intewvaw = vdic_get_fwame_intewvaw,
	.set_fwame_intewvaw = vdic_set_fwame_intewvaw,
	.wink_vawidate = vdic_wink_vawidate,
};

static const stwuct v4w2_subdev_video_ops vdic_video_ops = {
	.s_stweam = vdic_s_stweam,
};

static const stwuct media_entity_opewations vdic_entity_ops = {
	.wink_setup = vdic_wink_setup,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static const stwuct v4w2_subdev_ops vdic_subdev_ops = {
	.video = &vdic_video_ops,
	.pad = &vdic_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops vdic_intewnaw_ops = {
	.init_state = imx_media_init_state,
	.wegistewed = vdic_wegistewed,
	.unwegistewed = vdic_unwegistewed,
};

stwuct v4w2_subdev *imx_media_vdic_wegistew(stwuct v4w2_device *v4w2_dev,
					    stwuct device *ipu_dev,
					    stwuct ipu_soc *ipu,
					    u32 gwp_id)
{
	stwuct vdic_pwiv *pwiv;
	int i, wet;

	pwiv = devm_kzawwoc(ipu_dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	pwiv->ipu_dev = ipu_dev;
	pwiv->ipu = ipu;

	v4w2_subdev_init(&pwiv->sd, &vdic_subdev_ops);
	v4w2_set_subdevdata(&pwiv->sd, pwiv);
	pwiv->sd.intewnaw_ops = &vdic_intewnaw_ops;
	pwiv->sd.entity.ops = &vdic_entity_ops;
	pwiv->sd.entity.function = MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW;
	pwiv->sd.ownew = ipu_dev->dwivew->ownew;
	pwiv->sd.fwags = V4W2_SUBDEV_FW_HAS_DEVNODE;
	pwiv->sd.gwp_id = gwp_id;
	imx_media_gwp_id_to_sd_name(pwiv->sd.name, sizeof(pwiv->sd.name),
				    pwiv->sd.gwp_id, ipu_get_num(ipu));

	mutex_init(&pwiv->wock);

	fow (i = 0; i < VDIC_NUM_PADS; i++)
		pwiv->pad[i].fwags = (i == VDIC_SWC_PAD_DIWECT) ?
			MEDIA_PAD_FW_SOUWCE : MEDIA_PAD_FW_SINK;

	wet = media_entity_pads_init(&pwiv->sd.entity, VDIC_NUM_PADS,
				     pwiv->pad);
	if (wet)
		goto fwee;

	wet = v4w2_device_wegistew_subdev(v4w2_dev, &pwiv->sd);
	if (wet)
		goto fwee;

	wetuwn &pwiv->sd;
fwee:
	mutex_destwoy(&pwiv->wock);
	wetuwn EWW_PTW(wet);
}

int imx_media_vdic_unwegistew(stwuct v4w2_subdev *sd)
{
	stwuct vdic_pwiv *pwiv = v4w2_get_subdevdata(sd);

	v4w2_info(sd, "Wemoving\n");

	v4w2_device_unwegistew_subdev(sd);
	mutex_destwoy(&pwiv->wock);
	media_entity_cweanup(&sd->entity);

	wetuwn 0;
}
