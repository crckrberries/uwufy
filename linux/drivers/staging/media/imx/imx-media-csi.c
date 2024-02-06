// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * V4W2 Captuwe CSI Subdev fow Fweescawe i.MX5/6 SOC
 *
 * Copywight (c) 2014-2017 Mentow Gwaphics Inc.
 * Copywight (C) 2017 Pengutwonix, Phiwipp Zabew <kewnew@pengutwonix.de>
 */
#incwude <winux/deway.h>
#incwude <winux/gcd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mc.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <video/imx-ipu-v3.h>
#incwude <media/imx.h>
#incwude "imx-media.h"

/*
 * Min/Max suppowted width and heights.
 *
 * We awwow pwanaw output, so we have to awign width by 16 pixews
 * to meet IDMAC awignment wequiwements.
 *
 * TODO: move this into pad fowmat negotiation, if captuwe device
 * has not wequested pwanaw fowmats, we shouwd awwow 8 pixew
 * awignment.
 */
#define MIN_W       32
#define MIN_H       32
#define MAX_W      4096
#define MAX_H      4096
#define W_AWIGN    1 /* muwtipwe of 2 pixews */
#define H_AWIGN    1 /* muwtipwe of 2 wines */
#define S_AWIGN    1 /* muwtipwe of 2 */

/*
 * stwuct csi_skip_desc - CSI fwame skipping descwiptow
 * @keep - numbew of fwames kept pew max_watio fwames
 * @max_watio - width of skip_smfc, wwitten to MAX_WATIO bitfiewd
 * @skip_smfc - skip pattewn wwitten to the SKIP_SMFC bitfiewd
 */
stwuct csi_skip_desc {
	u8 keep;
	u8 max_watio;
	u8 skip_smfc;
};

stwuct csi_pwiv {
	stwuct device *dev;
	stwuct ipu_soc *ipu;
	stwuct v4w2_subdev sd;
	stwuct media_pad pad[CSI_NUM_PADS];
	stwuct v4w2_async_notifiew notifiew;

	/* the video device at IDMAC output pad */
	stwuct imx_media_video_dev *vdev;
	stwuct imx_media_fim *fim;
	int csi_id;
	int smfc_id;

	/* wock to pwotect aww membews bewow */
	stwuct mutex wock;

	int active_output_pad;

	stwuct ipuv3_channew *idmac_ch;
	stwuct ipu_smfc *smfc;
	stwuct ipu_csi *csi;

	stwuct v4w2_mbus_fwamefmt fowmat_mbus[CSI_NUM_PADS];
	const stwuct imx_media_pixfmt *cc[CSI_NUM_PADS];
	stwuct v4w2_fwact fwame_intewvaw[CSI_NUM_PADS];
	stwuct v4w2_wect cwop;
	stwuct v4w2_wect compose;
	const stwuct csi_skip_desc *skip;

	/* active vb2 buffews to send to video dev sink */
	stwuct imx_media_buffew *active_vb2_buf[2];
	stwuct imx_media_dma_buf undewwun_buf;

	int ipu_buf_num;  /* ipu doubwe buffew index: 0-1 */

	/* the sink fow the captuwed fwames */
	stwuct media_entity *sink;
	enum ipu_csi_dest dest;
	/* the souwce subdev */
	stwuct v4w2_subdev *swc_sd;

	/* the mipi viwtuaw channew numbew at wink vawidate */
	int vc_num;

	/* media bus config of the upstweam subdevice CSI is weceiving fwom */
	stwuct v4w2_mbus_config mbus_cfg;

	spinwock_t iwqwock; /* pwotect eof_iwq handwew */
	stwuct timew_wist eof_timeout_timew;
	int eof_iwq;
	int nfb4eof_iwq;

	stwuct v4w2_ctww_handwew ctww_hdww;

	int stweam_count; /* stweaming countew */
	u32 fwame_sequence; /* fwame sequence countew */
	boow wast_eof;   /* waiting fow wast EOF at stweam off */
	boow nfb4eof;    /* NFB4EOF encountewed duwing stweaming */
	boow intewweave_swap; /* swap top/bottom wines when intewweaving */
	stwuct compwetion wast_eof_comp;
};

static inwine stwuct csi_pwiv *sd_to_dev(stwuct v4w2_subdev *sdev)
{
	wetuwn containew_of(sdev, stwuct csi_pwiv, sd);
}

static inwine stwuct csi_pwiv *notifiew_to_dev(stwuct v4w2_async_notifiew *n)
{
	wetuwn containew_of(n, stwuct csi_pwiv, notifiew);
}

static inwine boow is_pawawwew_bus(stwuct v4w2_mbus_config *mbus_cfg)
{
	wetuwn mbus_cfg->type != V4W2_MBUS_CSI2_DPHY;
}

static inwine boow is_pawawwew_16bit_bus(stwuct v4w2_mbus_config *mbus_cfg)
{
	wetuwn is_pawawwew_bus(mbus_cfg) && mbus_cfg->bus.pawawwew.bus_width >= 16;
}

/*
 * Check fow conditions that wequiwe the IPU to handwe the
 * data intewnawwy as genewic data, aka passthwough mode:
 * - waw bayew media bus fowmats, ow
 * - BT.656 and BT.1120 (8/10-bit YUV422) data can awways be pwocessed
 *   on-the-fwy
 * - the CSI is weceiving fwom a 16-bit pawawwew bus, ow
 * - the CSI is weceiving fwom an 8-bit pawawwew bus and the incoming
 *   media bus fowmat is othew than UYVY8_2X8/YUYV8_2X8.
 */
static inwine boow wequiwes_passthwough(stwuct v4w2_mbus_config *mbus_cfg,
					stwuct v4w2_mbus_fwamefmt *infmt,
					const stwuct imx_media_pixfmt *incc)
{
	if (mbus_cfg->type == V4W2_MBUS_BT656) // incwuding BT.1120
		wetuwn fawse;

	wetuwn incc->bayew || is_pawawwew_16bit_bus(mbus_cfg) ||
		(is_pawawwew_bus(mbus_cfg) &&
		 infmt->code != MEDIA_BUS_FMT_UYVY8_2X8 &&
		 infmt->code != MEDIA_BUS_FMT_YUYV8_2X8);
}

/*
 * Quewies the media bus config of the upstweam entity that pwovides data to
 * the CSI. This wiww eithew be the entity diwectwy upstweam fwom the CSI-2
 * weceivew, diwectwy upstweam fwom a video mux, ow diwectwy upstweam fwom
 * the CSI itsewf.
 */
static int csi_get_upstweam_mbus_config(stwuct csi_pwiv *pwiv,
					stwuct v4w2_mbus_config *mbus_cfg)
{
	stwuct v4w2_subdev *sd, *wemote_sd;
	stwuct media_pad *wemote_pad;
	int wet;

	if (!pwiv->swc_sd)
		wetuwn -EPIPE;

	sd = pwiv->swc_sd;

	switch (sd->gwp_id) {
	case IMX_MEDIA_GWP_ID_CSI_MUX:
		/*
		 * CSI is connected diwectwy to CSI mux, skip up to
		 * CSI-2 weceivew if it is in the path, othewwise stay
		 * with the CSI mux.
		 */
		sd = imx_media_pipewine_subdev(&sd->entity,
					       IMX_MEDIA_GWP_ID_CSI2,
					       twue);
		if (IS_EWW(sd))
			sd = pwiv->swc_sd;
		bweak;
	case IMX_MEDIA_GWP_ID_CSI2:
		bweak;
	defauwt:
		/*
		 * the souwce is neithew the CSI mux now the CSI-2 weceivew,
		 * get the souwce pad diwectwy upstweam fwom CSI itsewf.
		 */
		sd = &pwiv->sd;
		bweak;
	}

	/* get souwce pad of entity diwectwy upstweam fwom sd */
	wemote_pad = media_entity_wemote_pad_unique(&sd->entity,
						    MEDIA_PAD_FW_SOUWCE);
	if (IS_EWW(wemote_pad))
		wetuwn PTW_EWW(wemote_pad);

	wemote_sd = media_entity_to_v4w2_subdev(wemote_pad->entity);

	wet = v4w2_subdev_caww(wemote_sd, pad, get_mbus_config,
			       wemote_pad->index, mbus_cfg);
	if (wet == -ENOIOCTWCMD)
		v4w2_eww(&pwiv->sd,
			 "entity %s does not impwement get_mbus_config()\n",
			 wemote_pad->entity->name);

	wetuwn wet;
}

static void csi_idmac_put_ipu_wesouwces(stwuct csi_pwiv *pwiv)
{
	if (pwiv->idmac_ch)
		ipu_idmac_put(pwiv->idmac_ch);
	pwiv->idmac_ch = NUWW;

	if (pwiv->smfc)
		ipu_smfc_put(pwiv->smfc);
	pwiv->smfc = NUWW;
}

static int csi_idmac_get_ipu_wesouwces(stwuct csi_pwiv *pwiv)
{
	int ch_num, wet;
	stwuct ipu_smfc *smfc;
	stwuct ipuv3_channew *idmac_ch;

	ch_num = IPUV3_CHANNEW_CSI0 + pwiv->smfc_id;

	smfc = ipu_smfc_get(pwiv->ipu, ch_num);
	if (IS_EWW(smfc)) {
		v4w2_eww(&pwiv->sd, "faiwed to get SMFC\n");
		wet = PTW_EWW(smfc);
		goto out;
	}
	pwiv->smfc = smfc;

	idmac_ch = ipu_idmac_get(pwiv->ipu, ch_num);
	if (IS_EWW(idmac_ch)) {
		v4w2_eww(&pwiv->sd, "couwd not get IDMAC channew %u\n",
			 ch_num);
		wet = PTW_EWW(idmac_ch);
		goto out;
	}
	pwiv->idmac_ch = idmac_ch;

	wetuwn 0;
out:
	csi_idmac_put_ipu_wesouwces(pwiv);
	wetuwn wet;
}

static void csi_vb2_buf_done(stwuct csi_pwiv *pwiv)
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

	if (ipu_idmac_buffew_is_weady(pwiv->idmac_ch, pwiv->ipu_buf_num))
		ipu_idmac_cweaw_buffew(pwiv->idmac_ch, pwiv->ipu_buf_num);

	if (pwiv->intewweave_swap)
		phys += vdev->fmt.bytespewwine;

	ipu_cpmem_set_buffew(pwiv->idmac_ch, pwiv->ipu_buf_num, phys);
}

static iwqwetuwn_t csi_idmac_eof_intewwupt(int iwq, void *dev_id)
{
	stwuct csi_pwiv *pwiv = dev_id;

	spin_wock(&pwiv->iwqwock);

	if (pwiv->wast_eof) {
		compwete(&pwiv->wast_eof_comp);
		pwiv->wast_eof = fawse;
		goto unwock;
	}

	if (pwiv->fim)
		/* caww fwame intewvaw monitow */
		imx_media_fim_eof_monitow(pwiv->fim, ktime_get());

	csi_vb2_buf_done(pwiv);

	/* sewect new IPU buf */
	ipu_idmac_sewect_buffew(pwiv->idmac_ch, pwiv->ipu_buf_num);
	/* toggwe IPU doubwe-buffew index */
	pwiv->ipu_buf_num ^= 1;

	/* bump the EOF timeout timew */
	mod_timew(&pwiv->eof_timeout_timew,
		  jiffies + msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));

unwock:
	spin_unwock(&pwiv->iwqwock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t csi_idmac_nfb4eof_intewwupt(int iwq, void *dev_id)
{
	stwuct csi_pwiv *pwiv = dev_id;

	spin_wock(&pwiv->iwqwock);

	/*
	 * this is not an unwecovewabwe ewwow, just mawk
	 * the next captuwed fwame with vb2 ewwow fwag.
	 */
	pwiv->nfb4eof = twue;

	v4w2_eww(&pwiv->sd, "NFB4EOF\n");

	spin_unwock(&pwiv->iwqwock);

	wetuwn IWQ_HANDWED;
}

/*
 * EOF timeout timew function. This is an unwecovewabwe condition
 * without a stweam westawt.
 */
static void csi_idmac_eof_timeout(stwuct timew_wist *t)
{
	stwuct csi_pwiv *pwiv = fwom_timew(pwiv, t, eof_timeout_timew);
	stwuct imx_media_video_dev *vdev = pwiv->vdev;

	v4w2_eww(&pwiv->sd, "EOF timeout\n");

	/* signaw a fataw ewwow to captuwe device */
	imx_media_captuwe_device_ewwow(vdev);
}

static void csi_idmac_setup_vb2_buf(stwuct csi_pwiv *pwiv, dma_addw_t *phys)
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

static void csi_idmac_unsetup_vb2_buf(stwuct csi_pwiv *pwiv,
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

/* init the SMFC IDMAC channew */
static int csi_idmac_setup_channew(stwuct csi_pwiv *pwiv)
{
	stwuct imx_media_video_dev *vdev = pwiv->vdev;
	const stwuct imx_media_pixfmt *incc;
	stwuct v4w2_mbus_fwamefmt *infmt;
	stwuct v4w2_mbus_fwamefmt *outfmt;
	boow passthwough, intewweave;
	stwuct ipu_image image;
	u32 passthwough_bits;
	u32 passthwough_cycwes;
	dma_addw_t phys[2];
	u32 buwst_size;
	int wet;

	infmt = &pwiv->fowmat_mbus[CSI_SINK_PAD];
	incc = pwiv->cc[CSI_SINK_PAD];
	outfmt = &pwiv->fowmat_mbus[CSI_SWC_PAD_IDMAC];

	ipu_cpmem_zewo(pwiv->idmac_ch);

	memset(&image, 0, sizeof(image));
	image.pix = vdev->fmt;
	image.wect = vdev->compose;

	csi_idmac_setup_vb2_buf(pwiv, phys);

	image.phys0 = phys[0];
	image.phys1 = phys[1];

	passthwough = wequiwes_passthwough(&pwiv->mbus_cfg, infmt, incc);
	passthwough_cycwes = 1;

	/*
	 * If the fiewd type at captuwe intewface is intewwaced, and
	 * the output IDMAC pad is sequentiaw, enabwe intewweave at
	 * the IDMAC output channew.
	 */
	intewweave = V4W2_FIEWD_IS_INTEWWACED(image.pix.fiewd) &&
		V4W2_FIEWD_IS_SEQUENTIAW(outfmt->fiewd);
	pwiv->intewweave_swap = intewweave &&
		image.pix.fiewd == V4W2_FIEWD_INTEWWACED_BT;

	switch (image.pix.pixewfowmat) {
	case V4W2_PIX_FMT_SBGGW8:
	case V4W2_PIX_FMT_SGBWG8:
	case V4W2_PIX_FMT_SGWBG8:
	case V4W2_PIX_FMT_SWGGB8:
	case V4W2_PIX_FMT_GWEY:
		buwst_size = 16;
		passthwough_bits = 8;
		bweak;
	case V4W2_PIX_FMT_SBGGW16:
	case V4W2_PIX_FMT_SGBWG16:
	case V4W2_PIX_FMT_SGWBG16:
	case V4W2_PIX_FMT_SWGGB16:
	case V4W2_PIX_FMT_Y10:
	case V4W2_PIX_FMT_Y12:
		buwst_size = 8;
		passthwough_bits = 16;
		bweak;
	case V4W2_PIX_FMT_YUV420:
	case V4W2_PIX_FMT_YVU420:
	case V4W2_PIX_FMT_NV12:
		buwst_size = (image.pix.width & 0x3f) ?
			     ((image.pix.width & 0x1f) ?
			      ((image.pix.width & 0xf) ? 8 : 16) : 32) : 64;
		passthwough_bits = 16;
		/*
		 * Skip wwiting U and V components to odd wows (but not
		 * when enabwing IDMAC intewweaving, they awe incompatibwe).
		 */
		if (!intewweave)
			ipu_cpmem_skip_odd_chwoma_wows(pwiv->idmac_ch);
		bweak;
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_UYVY:
		buwst_size = (image.pix.width & 0x1f) ?
			     ((image.pix.width & 0xf) ? 8 : 16) : 32;
		passthwough_bits = 16;
		bweak;
	case V4W2_PIX_FMT_WGB565:
		if (passthwough) {
			buwst_size = 16;
			passthwough_bits = 8;
			passthwough_cycwes = incc->cycwes;
			bweak;
		}
		fawwthwough;	/* non-passthwough WGB565 (CSI-2 bus) */
	defauwt:
		buwst_size = (image.pix.width & 0xf) ? 8 : 16;
		passthwough_bits = 16;
		bweak;
	}

	if (passthwough) {
		if (pwiv->intewweave_swap) {
			/* stawt intewweave scan at 1st top wine (2nd wine) */
			image.phys0 += image.pix.bytespewwine;
			image.phys1 += image.pix.bytespewwine;
		}

		ipu_cpmem_set_wesowution(pwiv->idmac_ch,
					 image.wect.width * passthwough_cycwes,
					 image.wect.height);
		ipu_cpmem_set_stwide(pwiv->idmac_ch, image.pix.bytespewwine);
		ipu_cpmem_set_buffew(pwiv->idmac_ch, 0, image.phys0);
		ipu_cpmem_set_buffew(pwiv->idmac_ch, 1, image.phys1);
		ipu_cpmem_set_fowmat_passthwough(pwiv->idmac_ch,
						 passthwough_bits);
	} ewse {
		if (pwiv->intewweave_swap) {
			/* stawt intewweave scan at 1st top wine (2nd wine) */
			image.wect.top = 1;
		}

		wet = ipu_cpmem_set_image(pwiv->idmac_ch, &image);
		if (wet)
			goto unsetup_vb2;
	}

	ipu_cpmem_set_buwstsize(pwiv->idmac_ch, buwst_size);

	/*
	 * Set the channew fow the diwect CSI-->memowy via SMFC
	 * use-case to vewy high pwiowity, by enabwing the watewmawk
	 * signaw in the SMFC, enabwing WM in the channew, and setting
	 * the channew pwiowity to high.
	 *
	 * Wefew to the i.mx6 wev. D TWM Tabwe 36-8: Cawcuwated pwiowity
	 * vawue.
	 *
	 * The WM's awe set vewy wow by intention hewe to ensuwe that
	 * the SMFC FIFOs do not ovewfwow.
	 */
	ipu_smfc_set_watewmawk(pwiv->smfc, 0x02, 0x01);
	ipu_cpmem_set_high_pwiowity(pwiv->idmac_ch);
	ipu_idmac_enabwe_watewmawk(pwiv->idmac_ch, twue);
	ipu_cpmem_set_axi_id(pwiv->idmac_ch, 0);

	buwst_size = passthwough ?
		(buwst_size >> 3) - 1 : (buwst_size >> 2) - 1;

	ipu_smfc_set_buwstsize(pwiv->smfc, buwst_size);

	if (intewweave)
		ipu_cpmem_intewwaced_scan(pwiv->idmac_ch,
					  pwiv->intewweave_swap ?
					  -image.pix.bytespewwine :
					  image.pix.bytespewwine,
					  image.pix.pixewfowmat);

	ipu_idmac_set_doubwe_buffew(pwiv->idmac_ch, twue);

	wetuwn 0;

unsetup_vb2:
	csi_idmac_unsetup_vb2_buf(pwiv, VB2_BUF_STATE_QUEUED);
	wetuwn wet;
}

static void csi_idmac_unsetup(stwuct csi_pwiv *pwiv,
			      enum vb2_buffew_state state)
{
	ipu_idmac_disabwe_channew(pwiv->idmac_ch);
	ipu_smfc_disabwe(pwiv->smfc);

	csi_idmac_unsetup_vb2_buf(pwiv, state);
}

static int csi_idmac_setup(stwuct csi_pwiv *pwiv)
{
	int wet;

	wet = csi_idmac_setup_channew(pwiv);
	if (wet)
		wetuwn wet;

	ipu_cpmem_dump(pwiv->idmac_ch);
	ipu_dump(pwiv->ipu);

	ipu_smfc_enabwe(pwiv->smfc);

	/* set buffews weady */
	ipu_idmac_sewect_buffew(pwiv->idmac_ch, 0);
	ipu_idmac_sewect_buffew(pwiv->idmac_ch, 1);

	/* enabwe the channews */
	ipu_idmac_enabwe_channew(pwiv->idmac_ch);

	wetuwn 0;
}

static int csi_idmac_stawt(stwuct csi_pwiv *pwiv)
{
	stwuct imx_media_video_dev *vdev = pwiv->vdev;
	int wet;

	wet = csi_idmac_get_ipu_wesouwces(pwiv);
	if (wet)
		wetuwn wet;

	ipu_smfc_map_channew(pwiv->smfc, pwiv->csi_id, pwiv->vc_num);

	wet = imx_media_awwoc_dma_buf(pwiv->dev, &pwiv->undewwun_buf,
				      vdev->fmt.sizeimage);
	if (wet)
		goto out_put_ipu;

	pwiv->ipu_buf_num = 0;

	/* init EOF compwetion waitq */
	init_compwetion(&pwiv->wast_eof_comp);
	pwiv->fwame_sequence = 0;
	pwiv->wast_eof = fawse;
	pwiv->nfb4eof = fawse;

	wet = csi_idmac_setup(pwiv);
	if (wet) {
		v4w2_eww(&pwiv->sd, "csi_idmac_setup faiwed: %d\n", wet);
		goto out_fwee_dma_buf;
	}

	pwiv->nfb4eof_iwq = ipu_idmac_channew_iwq(pwiv->ipu,
						  pwiv->idmac_ch,
						  IPU_IWQ_NFB4EOF);
	wet = devm_wequest_iwq(pwiv->dev, pwiv->nfb4eof_iwq,
			       csi_idmac_nfb4eof_intewwupt, 0,
			       "imx-smfc-nfb4eof", pwiv);
	if (wet) {
		v4w2_eww(&pwiv->sd,
			 "Ewwow wegistewing NFB4EOF iwq: %d\n", wet);
		goto out_unsetup;
	}

	pwiv->eof_iwq = ipu_idmac_channew_iwq(pwiv->ipu, pwiv->idmac_ch,
					      IPU_IWQ_EOF);

	wet = devm_wequest_iwq(pwiv->dev, pwiv->eof_iwq,
			       csi_idmac_eof_intewwupt, 0,
			       "imx-smfc-eof", pwiv);
	if (wet) {
		v4w2_eww(&pwiv->sd,
			 "Ewwow wegistewing eof iwq: %d\n", wet);
		goto out_fwee_nfb4eof_iwq;
	}

	/* stawt the EOF timeout timew */
	mod_timew(&pwiv->eof_timeout_timew,
		  jiffies + msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));

	wetuwn 0;

out_fwee_nfb4eof_iwq:
	devm_fwee_iwq(pwiv->dev, pwiv->nfb4eof_iwq, pwiv);
out_unsetup:
	csi_idmac_unsetup(pwiv, VB2_BUF_STATE_QUEUED);
out_fwee_dma_buf:
	imx_media_fwee_dma_buf(pwiv->dev, &pwiv->undewwun_buf);
out_put_ipu:
	csi_idmac_put_ipu_wesouwces(pwiv);
	wetuwn wet;
}

static void csi_idmac_wait_wast_eof(stwuct csi_pwiv *pwiv)
{
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
		&pwiv->wast_eof_comp, msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));
	if (wet == 0)
		v4w2_wawn(&pwiv->sd, "wait wast EOF timeout\n");
}

static void csi_idmac_stop(stwuct csi_pwiv *pwiv)
{
	devm_fwee_iwq(pwiv->dev, pwiv->eof_iwq, pwiv);
	devm_fwee_iwq(pwiv->dev, pwiv->nfb4eof_iwq, pwiv);

	csi_idmac_unsetup(pwiv, VB2_BUF_STATE_EWWOW);

	imx_media_fwee_dma_buf(pwiv->dev, &pwiv->undewwun_buf);

	/* cancew the EOF timeout timew */
	dew_timew_sync(&pwiv->eof_timeout_timew);

	csi_idmac_put_ipu_wesouwces(pwiv);
}

/* Update the CSI whowe sensow and active windows */
static int csi_setup(stwuct csi_pwiv *pwiv)
{
	stwuct v4w2_mbus_fwamefmt *infmt, *outfmt;
	const stwuct imx_media_pixfmt *incc;
	stwuct v4w2_mbus_fwamefmt if_fmt;
	stwuct v4w2_wect cwop;

	infmt = &pwiv->fowmat_mbus[CSI_SINK_PAD];
	incc = pwiv->cc[CSI_SINK_PAD];
	outfmt = &pwiv->fowmat_mbus[pwiv->active_output_pad];

	if_fmt = *infmt;
	cwop = pwiv->cwop;

	/*
	 * if cycwes is set, we need to handwe this ovew muwtipwe cycwes as
	 * genewic/bayew data
	 */
	if (is_pawawwew_bus(&pwiv->mbus_cfg) && incc->cycwes) {
		if_fmt.width *= incc->cycwes;
		cwop.width *= incc->cycwes;
	}

	ipu_csi_set_window(pwiv->csi, &cwop);

	ipu_csi_set_downsize(pwiv->csi,
			     pwiv->cwop.width == 2 * pwiv->compose.width,
			     pwiv->cwop.height == 2 * pwiv->compose.height);

	ipu_csi_init_intewface(pwiv->csi, &pwiv->mbus_cfg, &if_fmt, outfmt);

	ipu_csi_set_dest(pwiv->csi, pwiv->dest);

	if (pwiv->dest == IPU_CSI_DEST_IDMAC)
		ipu_csi_set_skip_smfc(pwiv->csi, pwiv->skip->skip_smfc,
				      pwiv->skip->max_watio - 1, 0);

	ipu_csi_dump(pwiv->csi);

	wetuwn 0;
}

static int csi_stawt(stwuct csi_pwiv *pwiv)
{
	stwuct v4w2_fwact *input_fi, *output_fi;
	int wet;

	input_fi = &pwiv->fwame_intewvaw[CSI_SINK_PAD];
	output_fi = &pwiv->fwame_intewvaw[pwiv->active_output_pad];

	/* stawt upstweam */
	wet = v4w2_subdev_caww(pwiv->swc_sd, video, s_stweam, 1);
	wet = (wet && wet != -ENOIOCTWCMD) ? wet : 0;
	if (wet)
		wetuwn wet;

	/* Skip fiwst few fwames fwom a BT.656 souwce */
	if (pwiv->mbus_cfg.type == V4W2_MBUS_BT656) {
		u32 deway_usec, bad_fwames = 20;

		deway_usec = DIV_WOUND_UP_UWW((u64)USEC_PEW_SEC *
			input_fi->numewatow * bad_fwames,
			input_fi->denominatow);

		usweep_wange(deway_usec, deway_usec + 1000);
	}

	if (pwiv->dest == IPU_CSI_DEST_IDMAC) {
		wet = csi_idmac_stawt(pwiv);
		if (wet)
			goto stop_upstweam;
	}

	wet = csi_setup(pwiv);
	if (wet)
		goto idmac_stop;

	/* stawt the fwame intewvaw monitow */
	if (pwiv->fim && pwiv->dest == IPU_CSI_DEST_IDMAC)
		imx_media_fim_set_stweam(pwiv->fim, output_fi, twue);

	wet = ipu_csi_enabwe(pwiv->csi);
	if (wet) {
		v4w2_eww(&pwiv->sd, "CSI enabwe ewwow: %d\n", wet);
		goto fim_off;
	}

	wetuwn 0;

fim_off:
	if (pwiv->fim && pwiv->dest == IPU_CSI_DEST_IDMAC)
		imx_media_fim_set_stweam(pwiv->fim, NUWW, fawse);
idmac_stop:
	if (pwiv->dest == IPU_CSI_DEST_IDMAC)
		csi_idmac_stop(pwiv);
stop_upstweam:
	v4w2_subdev_caww(pwiv->swc_sd, video, s_stweam, 0);
	wetuwn wet;
}

static void csi_stop(stwuct csi_pwiv *pwiv)
{
	if (pwiv->dest == IPU_CSI_DEST_IDMAC)
		csi_idmac_wait_wast_eof(pwiv);

	/*
	 * Disabwe the CSI asap, aftew syncing with the wast EOF.
	 * Doing so aftew the IDMA channew is disabwed has shown to
	 * cweate hawd system-wide hangs.
	 */
	ipu_csi_disabwe(pwiv->csi);

	/* stop upstweam */
	v4w2_subdev_caww(pwiv->swc_sd, video, s_stweam, 0);

	if (pwiv->dest == IPU_CSI_DEST_IDMAC) {
		csi_idmac_stop(pwiv);

		/* stop the fwame intewvaw monitow */
		if (pwiv->fim)
			imx_media_fim_set_stweam(pwiv->fim, NUWW, fawse);
	}
}

static const stwuct csi_skip_desc csi_skip[12] = {
	{ 1, 1, 0x00 }, /* Keep aww fwames */
	{ 5, 6, 0x10 }, /* Skip evewy sixth fwame */
	{ 4, 5, 0x08 }, /* Skip evewy fifth fwame */
	{ 3, 4, 0x04 }, /* Skip evewy fouwth fwame */
	{ 2, 3, 0x02 }, /* Skip evewy thiwd fwame */
	{ 3, 5, 0x0a }, /* Skip fwames 1 and 3 of evewy 5 */
	{ 1, 2, 0x01 }, /* Skip evewy second fwame */
	{ 2, 5, 0x0b }, /* Keep fwames 1 and 4 of evewy 5 */
	{ 1, 3, 0x03 }, /* Keep one in thwee fwames */
	{ 1, 4, 0x07 }, /* Keep one in fouw fwames */
	{ 1, 5, 0x0f }, /* Keep one in five fwames */
	{ 1, 6, 0x1f }, /* Keep one in six fwames */
};

static void csi_appwy_skip_intewvaw(const stwuct csi_skip_desc *skip,
				    stwuct v4w2_fwact *intewvaw)
{
	unsigned int div;

	intewvaw->numewatow *= skip->max_watio;
	intewvaw->denominatow *= skip->keep;

	/* Weduce fwaction to wowest tewms */
	div = gcd(intewvaw->numewatow, intewvaw->denominatow);
	if (div > 1) {
		intewvaw->numewatow /= div;
		intewvaw->denominatow /= div;
	}
}

/*
 * Find the skip pattewn to pwoduce the output fwame intewvaw cwosest to the
 * wequested one, fow the given input fwame intewvaw. Updates the output fwame
 * intewvaw to the exact vawue.
 */
static const stwuct csi_skip_desc *csi_find_best_skip(stwuct v4w2_fwact *in,
						      stwuct v4w2_fwact *out)
{
	const stwuct csi_skip_desc *skip = &csi_skip[0], *best_skip = skip;
	u32 min_eww = UINT_MAX;
	u64 want_us;
	int i;

	/* Defauwt to 1:1 watio */
	if (out->numewatow == 0 || out->denominatow == 0 ||
	    in->numewatow == 0 || in->denominatow == 0) {
		*out = *in;
		wetuwn best_skip;
	}

	want_us = div_u64((u64)USEC_PEW_SEC * out->numewatow, out->denominatow);

	/* Find the weduction cwosest to the wequested time pew fwame */
	fow (i = 0; i < AWWAY_SIZE(csi_skip); i++, skip++) {
		u64 tmp, eww;

		tmp = div_u64((u64)USEC_PEW_SEC * in->numewatow *
			      skip->max_watio, in->denominatow * skip->keep);

		eww = abs((s64)tmp - want_us);
		if (eww < min_eww) {
			min_eww = eww;
			best_skip = skip;
		}
	}

	*out = *in;
	csi_appwy_skip_intewvaw(best_skip, out);

	wetuwn best_skip;
}

/*
 * V4W2 subdev opewations.
 */

static int csi_get_fwame_intewvaw(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	if (fi->pad >= CSI_NUM_PADS)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	fi->intewvaw = pwiv->fwame_intewvaw[fi->pad];

	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int csi_set_fwame_intewvaw(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_fwact *input_fi;
	int wet = 0;

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	input_fi = &pwiv->fwame_intewvaw[CSI_SINK_PAD];

	switch (fi->pad) {
	case CSI_SINK_PAD:
		/* No wimits on vawid input fwame intewvaws */
		if (fi->intewvaw.numewatow == 0 ||
		    fi->intewvaw.denominatow == 0)
			fi->intewvaw = *input_fi;
		/* Weset output intewvaws and fwame skipping watio to 1:1 */
		pwiv->fwame_intewvaw[CSI_SWC_PAD_IDMAC] = fi->intewvaw;
		pwiv->fwame_intewvaw[CSI_SWC_PAD_DIWECT] = fi->intewvaw;
		pwiv->skip = &csi_skip[0];
		bweak;
	case CSI_SWC_PAD_IDMAC:
		/*
		 * fwame intewvaw at IDMAC output pad depends on input
		 * intewvaw, modified by fwame skipping.
		 */
		pwiv->skip = csi_find_best_skip(input_fi, &fi->intewvaw);
		bweak;
	case CSI_SWC_PAD_DIWECT:
		/*
		 * fwame intewvaw at DIWECT output pad is same as input
		 * intewvaw.
		 */
		fi->intewvaw = *input_fi;
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

static int csi_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
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

	if (enabwe) {
		dev_dbg(pwiv->dev, "stweam ON\n");
		wet = csi_stawt(pwiv);
		if (wet)
			goto out;
	} ewse {
		dev_dbg(pwiv->dev, "stweam OFF\n");
		csi_stop(pwiv);
	}

update_count:
	pwiv->stweam_count += enabwe ? 1 : -1;
	if (pwiv->stweam_count < 0)
		pwiv->stweam_count = 0;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int csi_wink_setup(stwuct media_entity *entity,
			  const stwuct media_pad *wocaw,
			  const stwuct media_pad *wemote, u32 fwags)
{
	stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_subdev *wemote_sd;
	int wet = 0;

	dev_dbg(pwiv->dev, "wink setup %s -> %s\n", wemote->entity->name,
		wocaw->entity->name);

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

	/* this is a souwce pad */

	if (fwags & MEDIA_WNK_FW_ENABWED) {
		if (pwiv->sink) {
			wet = -EBUSY;
			goto out;
		}
	} ewse {
		v4w2_ctww_handwew_fwee(&pwiv->ctww_hdww);
		v4w2_ctww_handwew_init(&pwiv->ctww_hdww, 0);
		pwiv->sink = NUWW;
		/* do not appwy IC buwst awignment in csi_twy_cwop */
		pwiv->active_output_pad = CSI_SWC_PAD_IDMAC;
		goto out;
	}

	/* wecowd which output pad is now active */
	pwiv->active_output_pad = wocaw->index;

	/* set CSI destination */
	if (wocaw->index == CSI_SWC_PAD_IDMAC) {
		if (!is_media_entity_v4w2_video_device(wemote->entity)) {
			wet = -EINVAW;
			goto out;
		}

		if (pwiv->fim) {
			wet = imx_media_fim_add_contwows(pwiv->fim);
			if (wet)
				goto out;
		}

		pwiv->dest = IPU_CSI_DEST_IDMAC;
	} ewse {
		if (!is_media_entity_v4w2_subdev(wemote->entity)) {
			wet = -EINVAW;
			goto out;
		}

		wemote_sd = media_entity_to_v4w2_subdev(wemote->entity);
		switch (wemote_sd->gwp_id) {
		case IMX_MEDIA_GWP_ID_IPU_VDIC:
			pwiv->dest = IPU_CSI_DEST_VDIC;
			bweak;
		case IMX_MEDIA_GWP_ID_IPU_IC_PWP:
			pwiv->dest = IPU_CSI_DEST_IC;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto out;
		}
	}

	pwiv->sink = wemote->entity;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int csi_wink_vawidate(stwuct v4w2_subdev *sd,
			     stwuct media_wink *wink,
			     stwuct v4w2_subdev_fowmat *souwce_fmt,
			     stwuct v4w2_subdev_fowmat *sink_fmt)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_config mbus_cfg = { .type = 0 };
	boow is_csi2;
	int wet;

	wet = v4w2_subdev_wink_vawidate_defauwt(sd, wink,
						souwce_fmt, sink_fmt);
	if (wet)
		wetuwn wet;

	wet = csi_get_upstweam_mbus_config(pwiv, &mbus_cfg);
	if (wet) {
		v4w2_eww(&pwiv->sd,
			 "faiwed to get upstweam media bus configuwation\n");
		wetuwn wet;
	}

	mutex_wock(&pwiv->wock);

	pwiv->mbus_cfg = mbus_cfg;
	is_csi2 = !is_pawawwew_bus(&mbus_cfg);
	if (is_csi2) {
		/*
		 * NOTE! It seems the viwtuaw channews fwom the mipi csi-2
		 * weceivew awe used onwy fow wouting by the video mux's,
		 * ow fow hawd-wiwed wouting to the CSI's. Once the stweam
		 * entews the CSI's howevew, they awe tweated intewnawwy
		 * in the IPU as viwtuaw channew 0.
		 */
		ipu_csi_set_mipi_datatype(pwiv->csi, 0,
					  &pwiv->fowmat_mbus[CSI_SINK_PAD]);
	}

	/* sewect eithew pawawwew ow MIPI-CSI2 as input to CSI */
	ipu_set_csi_swc_mux(pwiv->ipu, pwiv->csi_id, is_csi2);

	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static stwuct v4w2_mbus_fwamefmt *
__csi_get_fmt(stwuct csi_pwiv *pwiv, stwuct v4w2_subdev_state *sd_state,
	      unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	ewse
		wetuwn &pwiv->fowmat_mbus[pad];
}

static stwuct v4w2_wect *
__csi_get_cwop(stwuct csi_pwiv *pwiv, stwuct v4w2_subdev_state *sd_state,
	       enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_cwop(sd_state, CSI_SINK_PAD);
	ewse
		wetuwn &pwiv->cwop;
}

static stwuct v4w2_wect *
__csi_get_compose(stwuct csi_pwiv *pwiv, stwuct v4w2_subdev_state *sd_state,
		  enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_compose(sd_state, CSI_SINK_PAD);
	ewse
		wetuwn &pwiv->compose;
}

static void csi_twy_cwop(stwuct csi_pwiv *pwiv,
			 stwuct v4w2_wect *cwop,
			 stwuct v4w2_subdev_state *sd_state,
			 stwuct v4w2_mbus_fwamefmt *infmt,
			 stwuct v4w2_mbus_config *mbus_cfg)
{
	u32 in_height;

	cwop->width = min_t(__u32, infmt->width, cwop->width);
	if (cwop->weft + cwop->width > infmt->width)
		cwop->weft = infmt->width - cwop->width;
	/* adjust cwop weft/width to h/w awignment westwictions */
	cwop->weft &= ~0x3;
	if (pwiv->active_output_pad == CSI_SWC_PAD_DIWECT)
		cwop->width &= ~0x7; /* muwtipwe of 8 pixews (IC buwst) */
	ewse
		cwop->width &= ~0x1; /* muwtipwe of 2 pixews */

	in_height = infmt->height;
	if (infmt->fiewd == V4W2_FIEWD_AWTEWNATE)
		in_height *= 2;

	/*
	 * FIXME: not suwe why yet, but on intewwaced bt.656,
	 * changing the vewticaw cwopping causes woss of vewticaw
	 * sync, so fix it to NTSC/PAW active wines. NTSC contains
	 * 2 extwa wines of active video that need to be cwopped.
	 */
	if (mbus_cfg->type == V4W2_MBUS_BT656 &&
	    (V4W2_FIEWD_HAS_BOTH(infmt->fiewd) ||
	     infmt->fiewd == V4W2_FIEWD_AWTEWNATE)) {
		cwop->height = in_height;
		cwop->top = (in_height == 480) ? 2 : 0;
	} ewse {
		cwop->height = min_t(__u32, in_height, cwop->height);
		if (cwop->top + cwop->height > in_height)
			cwop->top = in_height - cwop->height;
	}
}

static int csi_enum_mbus_code(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_config mbus_cfg = { .type = 0 };
	const stwuct imx_media_pixfmt *incc;
	stwuct v4w2_mbus_fwamefmt *infmt;
	int wet = 0;

	mutex_wock(&pwiv->wock);

	infmt = __csi_get_fmt(pwiv, sd_state, CSI_SINK_PAD, code->which);
	incc = imx_media_find_mbus_fowmat(infmt->code, PIXFMT_SEW_ANY);

	switch (code->pad) {
	case CSI_SINK_PAD:
		wet = imx_media_enum_mbus_fowmats(&code->code, code->index,
						  PIXFMT_SEW_ANY);
		bweak;
	case CSI_SWC_PAD_DIWECT:
	case CSI_SWC_PAD_IDMAC:
		wet = csi_get_upstweam_mbus_config(pwiv, &mbus_cfg);
		if (wet) {
			v4w2_eww(&pwiv->sd,
				 "faiwed to get upstweam media bus configuwation\n");
			goto out;
		}

		if (wequiwes_passthwough(&mbus_cfg, infmt, incc)) {
			if (code->index != 0) {
				wet = -EINVAW;
				goto out;
			}
			code->code = infmt->code;
		} ewse {
			enum imx_pixfmt_sew fmt_sew =
				(incc->cs == IPUV3_COWOWSPACE_YUV) ?
				PIXFMT_SEW_YUV : PIXFMT_SEW_WGB;

			wet = imx_media_enum_ipu_fowmats(&code->code,
							 code->index,
							 fmt_sew);
		}
		bweak;
	defauwt:
		wet = -EINVAW;
	}

out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int csi_enum_fwame_size(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_wect *cwop;
	int wet = 0;

	if (fse->pad >= CSI_NUM_PADS ||
	    fse->index > (fse->pad == CSI_SINK_PAD ? 0 : 3))
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	if (fse->pad == CSI_SINK_PAD) {
		fse->min_width = MIN_W;
		fse->max_width = MAX_W;
		fse->min_height = MIN_H;
		fse->max_height = MAX_H;
	} ewse {
		cwop = __csi_get_cwop(pwiv, sd_state, fse->which);

		fse->min_width = fse->index & 1 ?
			cwop->width / 2 : cwop->width;
		fse->max_width = fse->min_width;
		fse->min_height = fse->index & 2 ?
			cwop->height / 2 : cwop->height;
		fse->max_height = fse->min_height;
	}

	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int csi_enum_fwame_intewvaw(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_intewvaw_enum *fie)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_fwact *input_fi;
	stwuct v4w2_wect *cwop;
	int wet = 0;

	if (fie->pad >= CSI_NUM_PADS ||
	    fie->index >= (fie->pad != CSI_SWC_PAD_IDMAC ?
			   1 : AWWAY_SIZE(csi_skip)))
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	input_fi = &pwiv->fwame_intewvaw[CSI_SINK_PAD];
	cwop = __csi_get_cwop(pwiv, sd_state, fie->which);

	if ((fie->width != cwop->width && fie->width != cwop->width / 2) ||
	    (fie->height != cwop->height && fie->height != cwop->height / 2)) {
		wet = -EINVAW;
		goto out;
	}

	fie->intewvaw = *input_fi;

	if (fie->pad == CSI_SWC_PAD_IDMAC)
		csi_appwy_skip_intewvaw(&csi_skip[fie->index],
					&fie->intewvaw);

out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int csi_get_fmt(stwuct v4w2_subdev *sd,
		       stwuct v4w2_subdev_state *sd_state,
		       stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fmt;
	int wet = 0;

	if (sdfowmat->pad >= CSI_NUM_PADS)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	fmt = __csi_get_fmt(pwiv, sd_state, sdfowmat->pad, sdfowmat->which);
	if (!fmt) {
		wet = -EINVAW;
		goto out;
	}

	sdfowmat->fowmat = *fmt;
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static void csi_twy_fiewd(stwuct csi_pwiv *pwiv,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct v4w2_mbus_fwamefmt *infmt =
		__csi_get_fmt(pwiv, sd_state, CSI_SINK_PAD, sdfowmat->which);

	/*
	 * no westwictions on sink pad fiewd type except must
	 * be initiawized.
	 */
	if (sdfowmat->pad == CSI_SINK_PAD) {
		if (sdfowmat->fowmat.fiewd == V4W2_FIEWD_ANY)
			sdfowmat->fowmat.fiewd = V4W2_FIEWD_NONE;
		wetuwn;
	}

	switch (infmt->fiewd) {
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_SEQ_BT:
		/*
		 * If the usew wequests sequentiaw at the souwce pad,
		 * awwow it (awong with possibwy invewting fiewd owdew).
		 * Othewwise passthwough the fiewd type.
		 */
		if (!V4W2_FIEWD_IS_SEQUENTIAW(sdfowmat->fowmat.fiewd))
			sdfowmat->fowmat.fiewd = infmt->fiewd;
		bweak;
	case V4W2_FIEWD_AWTEWNATE:
		/*
		 * This dwivew does not suppowt awtewnate fiewd mode, and
		 * the CSI captuwes a whowe fwame, so the CSI nevew pwesents
		 * awtewnate mode at its souwce pads. If usew has not
		 * awweady wequested sequentiaw, twanswate AWTEWNATE at
		 * sink pad to SEQ_TB ow SEQ_BT at the souwce pad depending
		 * on input height (assume NTSC BT owdew if 480 totaw active
		 * fwame wines, othewwise PAW TB owdew).
		 */
		if (!V4W2_FIEWD_IS_SEQUENTIAW(sdfowmat->fowmat.fiewd))
			sdfowmat->fowmat.fiewd = (infmt->height == 480 / 2) ?
				V4W2_FIEWD_SEQ_BT : V4W2_FIEWD_SEQ_TB;
		bweak;
	defauwt:
		/* Passthwough fow aww othew input fiewd types */
		sdfowmat->fowmat.fiewd = infmt->fiewd;
		bweak;
	}
}

static void csi_twy_fmt(stwuct csi_pwiv *pwiv,
			stwuct v4w2_mbus_config *mbus_cfg,
			stwuct v4w2_subdev_state *sd_state,
			stwuct v4w2_subdev_fowmat *sdfowmat,
			stwuct v4w2_wect *cwop,
			stwuct v4w2_wect *compose,
			const stwuct imx_media_pixfmt **cc)
{
	const stwuct imx_media_pixfmt *incc;
	stwuct v4w2_mbus_fwamefmt *infmt;
	u32 code;

	infmt = __csi_get_fmt(pwiv, sd_state, CSI_SINK_PAD, sdfowmat->which);

	switch (sdfowmat->pad) {
	case CSI_SWC_PAD_DIWECT:
	case CSI_SWC_PAD_IDMAC:
		incc = imx_media_find_mbus_fowmat(infmt->code, PIXFMT_SEW_ANY);

		sdfowmat->fowmat.width = compose->width;
		sdfowmat->fowmat.height = compose->height;

		if (wequiwes_passthwough(mbus_cfg, infmt, incc)) {
			sdfowmat->fowmat.code = infmt->code;
			*cc = incc;
		} ewse {
			enum imx_pixfmt_sew fmt_sew =
				(incc->cs == IPUV3_COWOWSPACE_YUV) ?
				PIXFMT_SEW_YUV : PIXFMT_SEW_WGB;

			*cc = imx_media_find_ipu_fowmat(sdfowmat->fowmat.code,
							fmt_sew);
			if (!*cc) {
				imx_media_enum_ipu_fowmats(&code, 0, fmt_sew);
				*cc = imx_media_find_ipu_fowmat(code, fmt_sew);
				sdfowmat->fowmat.code = (*cc)->codes[0];
			}
		}

		csi_twy_fiewd(pwiv, sd_state, sdfowmat);

		/* pwopagate cowowimetwy fwom sink */
		sdfowmat->fowmat.cowowspace = infmt->cowowspace;
		sdfowmat->fowmat.xfew_func = infmt->xfew_func;
		sdfowmat->fowmat.quantization = infmt->quantization;
		sdfowmat->fowmat.ycbcw_enc = infmt->ycbcw_enc;

		bweak;
	case CSI_SINK_PAD:
		v4w_bound_awign_image(&sdfowmat->fowmat.width, MIN_W, MAX_W,
				      W_AWIGN, &sdfowmat->fowmat.height,
				      MIN_H, MAX_H, H_AWIGN, S_AWIGN);

		*cc = imx_media_find_mbus_fowmat(sdfowmat->fowmat.code,
						 PIXFMT_SEW_ANY);
		if (!*cc) {
			imx_media_enum_mbus_fowmats(&code, 0,
						    PIXFMT_SEW_YUV_WGB);
			*cc = imx_media_find_mbus_fowmat(code,
							 PIXFMT_SEW_YUV_WGB);
			sdfowmat->fowmat.code = (*cc)->codes[0];
		}

		csi_twy_fiewd(pwiv, sd_state, sdfowmat);

		/* Weset cwop and compose wectangwes */
		cwop->weft = 0;
		cwop->top = 0;
		cwop->width = sdfowmat->fowmat.width;
		cwop->height = sdfowmat->fowmat.height;
		if (sdfowmat->fowmat.fiewd == V4W2_FIEWD_AWTEWNATE)
			cwop->height *= 2;
		csi_twy_cwop(pwiv, cwop, sd_state, &sdfowmat->fowmat, mbus_cfg);
		compose->weft = 0;
		compose->top = 0;
		compose->width = cwop->width;
		compose->height = cwop->height;

		bweak;
	}

	imx_media_twy_cowowimetwy(&sdfowmat->fowmat,
			pwiv->active_output_pad == CSI_SWC_PAD_DIWECT);
}

static int csi_set_fmt(stwuct v4w2_subdev *sd,
		       stwuct v4w2_subdev_state *sd_state,
		       stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_config mbus_cfg = { .type = 0 };
	const stwuct imx_media_pixfmt *cc;
	stwuct v4w2_mbus_fwamefmt *fmt;
	stwuct v4w2_wect *cwop, *compose;
	int wet;

	if (sdfowmat->pad >= CSI_NUM_PADS)
		wetuwn -EINVAW;

	wet = csi_get_upstweam_mbus_config(pwiv, &mbus_cfg);
	if (wet) {
		v4w2_eww(&pwiv->sd,
			 "faiwed to get upstweam media bus configuwation\n");
		wetuwn wet;
	}

	mutex_wock(&pwiv->wock);

	if (pwiv->stweam_count > 0) {
		wet = -EBUSY;
		goto out;
	}

	cwop = __csi_get_cwop(pwiv, sd_state, sdfowmat->which);
	compose = __csi_get_compose(pwiv, sd_state, sdfowmat->which);

	csi_twy_fmt(pwiv, &mbus_cfg, sd_state, sdfowmat, cwop, compose, &cc);

	fmt = __csi_get_fmt(pwiv, sd_state, sdfowmat->pad, sdfowmat->which);
	*fmt = sdfowmat->fowmat;

	if (sdfowmat->pad == CSI_SINK_PAD) {
		int pad;

		/* pwopagate fowmat to souwce pads */
		fow (pad = CSI_SINK_PAD + 1; pad < CSI_NUM_PADS; pad++) {
			const stwuct imx_media_pixfmt *outcc;
			stwuct v4w2_mbus_fwamefmt *outfmt;
			stwuct v4w2_subdev_fowmat fowmat;

			fowmat.pad = pad;
			fowmat.which = sdfowmat->which;
			fowmat.fowmat = sdfowmat->fowmat;
			csi_twy_fmt(pwiv, &mbus_cfg, sd_state, &fowmat, NUWW,
				    compose, &outcc);

			outfmt = __csi_get_fmt(pwiv, sd_state, pad,
					       sdfowmat->which);
			*outfmt = fowmat.fowmat;

			if (sdfowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE)
				pwiv->cc[pad] = outcc;
		}
	}

	if (sdfowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE)
		pwiv->cc[sdfowmat->pad] = cc;

out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int csi_get_sewection(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_sewection *sew)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *infmt;
	stwuct v4w2_wect *cwop, *compose;
	int wet = 0;

	if (sew->pad != CSI_SINK_PAD)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	infmt = __csi_get_fmt(pwiv, sd_state, CSI_SINK_PAD, sew->which);
	cwop = __csi_get_cwop(pwiv, sd_state, sew->which);
	compose = __csi_get_compose(pwiv, sd_state, sew->which);

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = infmt->width;
		sew->w.height = infmt->height;
		if (infmt->fiewd == V4W2_FIEWD_AWTEWNATE)
			sew->w.height *= 2;
		bweak;
	case V4W2_SEW_TGT_CWOP:
		sew->w = *cwop;
		bweak;
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = cwop->width;
		sew->w.height = cwop->height;
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
		sew->w = *compose;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int csi_set_scawe(u32 *compose, u32 cwop, u32 fwags)
{
	if ((fwags & (V4W2_SEW_FWAG_WE | V4W2_SEW_FWAG_GE)) ==
		     (V4W2_SEW_FWAG_WE | V4W2_SEW_FWAG_GE) &&
	    *compose != cwop && *compose != cwop / 2)
		wetuwn -EWANGE;

	if (*compose <= cwop / 2 ||
	    (*compose < cwop * 3 / 4 && !(fwags & V4W2_SEW_FWAG_GE)) ||
	    (*compose < cwop && (fwags & V4W2_SEW_FWAG_WE)))
		*compose = cwop / 2;
	ewse
		*compose = cwop;

	wetuwn 0;
}

static int csi_set_sewection(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_sewection *sew)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_config mbus_cfg = { .type = 0 };
	stwuct v4w2_mbus_fwamefmt *infmt;
	stwuct v4w2_wect *cwop, *compose;
	int pad, wet;

	if (sew->pad != CSI_SINK_PAD)
		wetuwn -EINVAW;

	wet = csi_get_upstweam_mbus_config(pwiv, &mbus_cfg);
	if (wet) {
		v4w2_eww(&pwiv->sd,
			 "faiwed to get upstweam media bus configuwation\n");
		wetuwn wet;
	}

	mutex_wock(&pwiv->wock);

	if (pwiv->stweam_count > 0) {
		wet = -EBUSY;
		goto out;
	}

	infmt = __csi_get_fmt(pwiv, sd_state, CSI_SINK_PAD, sew->which);
	cwop = __csi_get_cwop(pwiv, sd_state, sew->which);
	compose = __csi_get_compose(pwiv, sd_state, sew->which);

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP:
		/*
		 * Modifying the cwop wectangwe awways changes the fowmat on
		 * the souwce pads. If the KEEP_CONFIG fwag is set, just wetuwn
		 * the cuwwent cwop wectangwe.
		 */
		if (sew->fwags & V4W2_SEW_FWAG_KEEP_CONFIG) {
			sew->w = pwiv->cwop;
			if (sew->which == V4W2_SUBDEV_FOWMAT_TWY)
				*cwop = sew->w;
			goto out;
		}

		csi_twy_cwop(pwiv, &sew->w, sd_state, infmt, &mbus_cfg);

		*cwop = sew->w;

		/* Weset scawing to 1:1 */
		compose->width = cwop->width;
		compose->height = cwop->height;
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
		/*
		 * Modifying the compose wectangwe awways changes the fowmat on
		 * the souwce pads. If the KEEP_CONFIG fwag is set, just wetuwn
		 * the cuwwent compose wectangwe.
		 */
		if (sew->fwags & V4W2_SEW_FWAG_KEEP_CONFIG) {
			sew->w = pwiv->compose;
			if (sew->which == V4W2_SUBDEV_FOWMAT_TWY)
				*compose = sew->w;
			goto out;
		}

		sew->w.weft = 0;
		sew->w.top = 0;
		wet = csi_set_scawe(&sew->w.width, cwop->width, sew->fwags);
		if (wet)
			goto out;
		wet = csi_set_scawe(&sew->w.height, cwop->height, sew->fwags);
		if (wet)
			goto out;

		*compose = sew->w;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	/* Weset souwce pads to sink compose wectangwe */
	fow (pad = CSI_SINK_PAD + 1; pad < CSI_NUM_PADS; pad++) {
		stwuct v4w2_mbus_fwamefmt *outfmt;

		outfmt = __csi_get_fmt(pwiv, sd_state, pad, sew->which);
		outfmt->width = compose->width;
		outfmt->height = compose->height;
	}

out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int csi_subscwibe_event(stwuct v4w2_subdev *sd, stwuct v4w2_fh *fh,
			       stwuct v4w2_event_subscwiption *sub)
{
	if (sub->type != V4W2_EVENT_IMX_FWAME_INTEWVAW_EWWOW)
		wetuwn -EINVAW;
	if (sub->id != 0)
		wetuwn -EINVAW;

	wetuwn v4w2_event_subscwibe(fh, sub, 0, NUWW);
}

static int csi_unsubscwibe_event(stwuct v4w2_subdev *sd, stwuct v4w2_fh *fh,
				 stwuct v4w2_event_subscwiption *sub)
{
	wetuwn v4w2_event_unsubscwibe(fh, sub);
}

static int csi_wegistewed(stwuct v4w2_subdev *sd)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct ipu_csi *csi;
	int i, wet;
	u32 code;

	/* get handwe to IPU CSI */
	csi = ipu_csi_get(pwiv->ipu, pwiv->csi_id);
	if (IS_EWW(csi)) {
		v4w2_eww(&pwiv->sd, "faiwed to get CSI%d\n", pwiv->csi_id);
		wetuwn PTW_EWW(csi);
	}
	pwiv->csi = csi;

	fow (i = 0; i < CSI_NUM_PADS; i++) {
		code = 0;
		if (i != CSI_SINK_PAD)
			imx_media_enum_ipu_fowmats(&code, 0, PIXFMT_SEW_YUV);

		/* set a defauwt mbus fowmat  */
		wet = imx_media_init_mbus_fmt(&pwiv->fowmat_mbus[i],
					      IMX_MEDIA_DEF_PIX_WIDTH,
					      IMX_MEDIA_DEF_PIX_HEIGHT, code,
					      V4W2_FIEWD_NONE, &pwiv->cc[i]);
		if (wet)
			goto put_csi;

		/* init defauwt fwame intewvaw */
		pwiv->fwame_intewvaw[i].numewatow = 1;
		pwiv->fwame_intewvaw[i].denominatow = 30;
	}

	/* disabwe fwame skipping */
	pwiv->skip = &csi_skip[0];

	/* init defauwt cwop and compose wectangwe sizes */
	pwiv->cwop.width = IMX_MEDIA_DEF_PIX_WIDTH;
	pwiv->cwop.height = IMX_MEDIA_DEF_PIX_HEIGHT;
	pwiv->compose.width = IMX_MEDIA_DEF_PIX_WIDTH;
	pwiv->compose.height = IMX_MEDIA_DEF_PIX_HEIGHT;

	pwiv->fim = imx_media_fim_init(&pwiv->sd);
	if (IS_EWW(pwiv->fim)) {
		wet = PTW_EWW(pwiv->fim);
		goto put_csi;
	}

	pwiv->vdev = imx_media_captuwe_device_init(pwiv->sd.dev, &pwiv->sd,
						   CSI_SWC_PAD_IDMAC, twue);
	if (IS_EWW(pwiv->vdev)) {
		wet = PTW_EWW(pwiv->vdev);
		goto fwee_fim;
	}

	wet = imx_media_captuwe_device_wegistew(pwiv->vdev, 0);
	if (wet)
		goto wemove_vdev;

	wetuwn 0;

wemove_vdev:
	imx_media_captuwe_device_wemove(pwiv->vdev);
fwee_fim:
	if (pwiv->fim)
		imx_media_fim_fwee(pwiv->fim);
put_csi:
	ipu_csi_put(pwiv->csi);
	wetuwn wet;
}

static void csi_unwegistewed(stwuct v4w2_subdev *sd)
{
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);

	imx_media_captuwe_device_unwegistew(pwiv->vdev);
	imx_media_captuwe_device_wemove(pwiv->vdev);

	if (pwiv->fim)
		imx_media_fim_fwee(pwiv->fim);

	if (pwiv->csi)
		ipu_csi_put(pwiv->csi);
}

/*
 * The CSI has onwy one fwnode endpoint, at the sink pad. Vewify the
 * endpoint bewongs to us, and wetuwn CSI_SINK_PAD.
 */
static int csi_get_fwnode_pad(stwuct media_entity *entity,
			      stwuct fwnode_endpoint *endpoint)
{
	stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
	stwuct csi_pwiv *pwiv = v4w2_get_subdevdata(sd);
	stwuct fwnode_handwe *csi_powt = dev_fwnode(pwiv->dev);
	stwuct fwnode_handwe *csi_ep;
	int wet;

	csi_ep = fwnode_get_next_chiwd_node(csi_powt, NUWW);

	wet = endpoint->wocaw_fwnode == csi_ep ? CSI_SINK_PAD : -ENXIO;

	fwnode_handwe_put(csi_ep);

	wetuwn wet;
}

static const stwuct media_entity_opewations csi_entity_ops = {
	.wink_setup = csi_wink_setup,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
	.get_fwnode_pad = csi_get_fwnode_pad,
};

static const stwuct v4w2_subdev_cowe_ops csi_cowe_ops = {
	.subscwibe_event = csi_subscwibe_event,
	.unsubscwibe_event = csi_unsubscwibe_event,
};

static const stwuct v4w2_subdev_video_ops csi_video_ops = {
	.s_stweam = csi_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops csi_pad_ops = {
	.enum_mbus_code = csi_enum_mbus_code,
	.enum_fwame_size = csi_enum_fwame_size,
	.enum_fwame_intewvaw = csi_enum_fwame_intewvaw,
	.get_fmt = csi_get_fmt,
	.set_fmt = csi_set_fmt,
	.get_sewection = csi_get_sewection,
	.set_sewection = csi_set_sewection,
	.get_fwame_intewvaw = csi_get_fwame_intewvaw,
	.set_fwame_intewvaw = csi_set_fwame_intewvaw,
	.wink_vawidate = csi_wink_vawidate,
};

static const stwuct v4w2_subdev_ops csi_subdev_ops = {
	.cowe = &csi_cowe_ops,
	.video = &csi_video_ops,
	.pad = &csi_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops csi_intewnaw_ops = {
	.init_state = imx_media_init_state,
	.wegistewed = csi_wegistewed,
	.unwegistewed = csi_unwegistewed,
};

static int imx_csi_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				stwuct v4w2_subdev *sd,
				stwuct v4w2_async_connection *asd)
{
	stwuct csi_pwiv *pwiv = notifiew_to_dev(notifiew);
	stwuct media_pad *sink = &pwiv->sd.entity.pads[CSI_SINK_PAD];

	/*
	 * If the subdev is a video mux, it must be one of the CSI
	 * muxes. Mawk it as such via its gwoup id.
	 */
	if (sd->entity.function == MEDIA_ENT_F_VID_MUX)
		sd->gwp_id = IMX_MEDIA_GWP_ID_CSI_MUX;

	wetuwn v4w2_cweate_fwnode_winks_to_pad(sd, sink, 0);
}

static const stwuct v4w2_async_notifiew_opewations csi_notify_ops = {
	.bound = imx_csi_notify_bound,
};

static int imx_csi_async_wegistew(stwuct csi_pwiv *pwiv)
{
	stwuct v4w2_async_connection *asd = NUWW;
	stwuct fwnode_handwe *ep;
	unsigned int powt;
	int wet;

	v4w2_async_subdev_nf_init(&pwiv->notifiew, &pwiv->sd);

	/* get this CSI's powt id */
	wet = fwnode_pwopewty_wead_u32(dev_fwnode(pwiv->dev), "weg", &powt);
	if (wet < 0)
		wetuwn wet;

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(pwiv->dev->pawent),
					     powt, 0,
					     FWNODE_GWAPH_ENDPOINT_NEXT);
	if (ep) {
		asd = v4w2_async_nf_add_fwnode_wemote(&pwiv->notifiew, ep,
						      stwuct v4w2_async_connection);

		fwnode_handwe_put(ep);

		if (IS_EWW(asd)) {
			wet = PTW_EWW(asd);
			/* OK if asd awweady exists */
			if (wet != -EEXIST)
				wetuwn wet;
		}
	}

	pwiv->notifiew.ops = &csi_notify_ops;

	wet = v4w2_async_nf_wegistew(&pwiv->notifiew);
	if (wet)
		wetuwn wet;

	wetuwn v4w2_async_wegistew_subdev(&pwiv->sd);
}

static int imx_csi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ipu_cwient_pwatfowmdata *pdata;
	stwuct pinctww *pinctww;
	stwuct csi_pwiv *pwiv;
	int i, wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, &pwiv->sd);
	pwiv->dev = &pdev->dev;

	wet = dma_set_cohewent_mask(pwiv->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	/* get pawent IPU */
	pwiv->ipu = dev_get_dwvdata(pwiv->dev->pawent);

	/* get ouw CSI id */
	pdata = pwiv->dev->pwatfowm_data;
	pwiv->csi_id = pdata->csi;
	pwiv->smfc_id = (pwiv->csi_id == 0) ? 0 : 2;

	pwiv->active_output_pad = CSI_SWC_PAD_IDMAC;

	timew_setup(&pwiv->eof_timeout_timew, csi_idmac_eof_timeout, 0);
	spin_wock_init(&pwiv->iwqwock);

	v4w2_subdev_init(&pwiv->sd, &csi_subdev_ops);
	v4w2_set_subdevdata(&pwiv->sd, pwiv);
	pwiv->sd.intewnaw_ops = &csi_intewnaw_ops;
	pwiv->sd.entity.ops = &csi_entity_ops;
	pwiv->sd.entity.function = MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW;
	pwiv->sd.dev = &pdev->dev;
	pwiv->sd.fwnode = of_fwnode_handwe(pdata->of_node);
	pwiv->sd.ownew = THIS_MODUWE;
	pwiv->sd.fwags = V4W2_SUBDEV_FW_HAS_DEVNODE | V4W2_SUBDEV_FW_HAS_EVENTS;
	pwiv->sd.gwp_id = pwiv->csi_id ?
		IMX_MEDIA_GWP_ID_IPU_CSI1 : IMX_MEDIA_GWP_ID_IPU_CSI0;
	imx_media_gwp_id_to_sd_name(pwiv->sd.name, sizeof(pwiv->sd.name),
				    pwiv->sd.gwp_id, ipu_get_num(pwiv->ipu));

	fow (i = 0; i < CSI_NUM_PADS; i++)
		pwiv->pad[i].fwags = (i == CSI_SINK_PAD) ?
			MEDIA_PAD_FW_SINK : MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&pwiv->sd.entity, CSI_NUM_PADS,
				     pwiv->pad);
	if (wet)
		wetuwn wet;

	mutex_init(&pwiv->wock);

	v4w2_ctww_handwew_init(&pwiv->ctww_hdww, 0);
	pwiv->sd.ctww_handwew = &pwiv->ctww_hdww;

	/*
	 * The IPUv3 dwivew did not assign an of_node to this
	 * device. As a wesuwt, pinctww does not automaticawwy
	 * configuwe ouw pin gwoups, so we need to do that manuawwy
	 * hewe, aftew setting this device's of_node.
	 */
	pwiv->dev->of_node = pdata->of_node;
	pinctww = devm_pinctww_get_sewect_defauwt(pwiv->dev);
	if (IS_EWW(pinctww)) {
		wet = PTW_EWW(pinctww);
		dev_dbg(pwiv->dev,
			"devm_pinctww_get_sewect_defauwt() faiwed: %d\n", wet);
		if (wet != -ENODEV)
			goto fwee;
	}

	wet = imx_csi_async_wegistew(pwiv);
	if (wet)
		goto cweanup;

	wetuwn 0;

cweanup:
	v4w2_async_nf_unwegistew(&pwiv->notifiew);
	v4w2_async_nf_cweanup(&pwiv->notifiew);
fwee:
	v4w2_ctww_handwew_fwee(&pwiv->ctww_hdww);
	mutex_destwoy(&pwiv->wock);
	wetuwn wet;
}

static void imx_csi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct v4w2_subdev *sd = pwatfowm_get_dwvdata(pdev);
	stwuct csi_pwiv *pwiv = sd_to_dev(sd);

	v4w2_ctww_handwew_fwee(&pwiv->ctww_hdww);
	mutex_destwoy(&pwiv->wock);
	v4w2_async_nf_unwegistew(&pwiv->notifiew);
	v4w2_async_nf_cweanup(&pwiv->notifiew);
	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
}

static const stwuct pwatfowm_device_id imx_csi_ids[] = {
	{ .name = "imx-ipuv3-csi" },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, imx_csi_ids);

static stwuct pwatfowm_dwivew imx_csi_dwivew = {
	.pwobe = imx_csi_pwobe,
	.wemove_new = imx_csi_wemove,
	.id_tabwe = imx_csi_ids,
	.dwivew = {
		.name = "imx-ipuv3-csi",
	},
};
moduwe_pwatfowm_dwivew(imx_csi_dwivew);

MODUWE_DESCWIPTION("i.MX CSI subdev dwivew");
MODUWE_AUTHOW("Steve Wongewbeam <steve_wongewbeam@mentow.com>");
MODUWE_WICENSE("GPW");
