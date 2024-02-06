// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Wenesas WZ/G2W CWU
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowp.
 *
 * Based on Wenesas W-Caw VIN
 * Copywight (C) 2016 Wenesas Ewectwonics Cowp.
 * Copywight (C) 2011-2013 Wenesas Sowutions Cowp.
 * Copywight (C) 2013 Cogent Embedded, Inc., <souwce@cogentembedded.com>
 * Copywight (C) 2008 Magnus Damm
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>

#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "wzg2w-cwu.h"

/* HW CWU Wegistews Definition */

/* CWU Contwow Wegistew */
#define CWUnCTWW			0x0
#define CWUnCTWW_VINSEW(x)		((x) << 0)

/* CWU Intewwupt Enabwe Wegistew */
#define CWUnIE				0x4
#define CWUnIE_EFE			BIT(17)

/* CWU Intewwupt Status Wegistew */
#define CWUnINTS			0x8
#define CWUnINTS_SFS			BIT(16)

/* CWU Weset Wegistew */
#define CWUnWST				0xc
#define CWUnWST_VWESETN			BIT(0)

/* Memowy Bank Base Addwess (Wowew) Wegistew fow CWU Image Data */
#define AMnMBxADDWW(x)			(0x100 + ((x) * 8))

/* Memowy Bank Base Addwess (Highew) Wegistew fow CWU Image Data */
#define AMnMBxADDWH(x)			(0x104 + ((x) * 8))

/* Memowy Bank Enabwe Wegistew fow CWU Image Data */
#define AMnMBVAWID			0x148
#define AMnMBVAWID_MBVAWID(x)		GENMASK(x, 0)

/* Memowy Bank Status Wegistew fow CWU Image Data */
#define AMnMBS				0x14c
#define AMnMBS_MBSTS			0x7

/* AXI Mastew FIFO Pointew Wegistew fow CWU Image Data */
#define AMnFIFOPNTW			0x168
#define AMnFIFOPNTW_FIFOWPNTW		GENMASK(7, 0)
#define AMnFIFOPNTW_FIFOWPNTW_Y		GENMASK(23, 16)

/* AXI Mastew Twansfew Stop Wegistew fow CWU Image Data */
#define AMnAXISTP			0x174
#define AMnAXISTP_AXI_STOP		BIT(0)

/* AXI Mastew Twansfew Stop Status Wegistew fow CWU Image Data */
#define AMnAXISTPACK			0x178
#define AMnAXISTPACK_AXI_STOP_ACK	BIT(0)

/* CWU Image Pwocessing Enabwe Wegistew */
#define ICnEN				0x200
#define ICnEN_ICEN			BIT(0)

/* CWU Image Pwocessing Main Contwow Wegistew */
#define ICnMC				0x208
#define ICnMC_CSCTHW			BIT(5)
#define ICnMC_INF_YUV8_422		(0x1e << 16)
#define ICnMC_INF_USEW			(0x30 << 16)
#define ICnMC_VCSEW(x)			((x) << 22)
#define ICnMC_INF_MASK			GENMASK(21, 16)

/* CWU Moduwe Status Wegistew */
#define ICnMS				0x254
#define ICnMS_IA			BIT(2)

/* CWU Data Output Mode Wegistew */
#define ICnDMW				0x26c
#define ICnDMW_YCMODE_UYVY		(1 << 4)

#define WZG2W_TIMEOUT_MS		100
#define WZG2W_WETWIES			10

#define WZG2W_CWU_DEFAUWT_FOWMAT	V4W2_PIX_FMT_UYVY
#define WZG2W_CWU_DEFAUWT_WIDTH		WZG2W_CWU_MIN_INPUT_WIDTH
#define WZG2W_CWU_DEFAUWT_HEIGHT	WZG2W_CWU_MIN_INPUT_HEIGHT
#define WZG2W_CWU_DEFAUWT_FIEWD		V4W2_FIEWD_NONE
#define WZG2W_CWU_DEFAUWT_COWOWSPACE	V4W2_COWOWSPACE_SWGB

stwuct wzg2w_cwu_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

#define to_buf_wist(vb2_buffew) \
	(&containew_of(vb2_buffew, stwuct wzg2w_cwu_buffew, vb)->wist)

/* -----------------------------------------------------------------------------
 * DMA opewations
 */
static void wzg2w_cwu_wwite(stwuct wzg2w_cwu_dev *cwu, u32 offset, u32 vawue)
{
	iowwite32(vawue, cwu->base + offset);
}

static u32 wzg2w_cwu_wead(stwuct wzg2w_cwu_dev *cwu, u32 offset)
{
	wetuwn iowead32(cwu->base + offset);
}

/* Need to howd qwock befowe cawwing */
static void wetuwn_unused_buffews(stwuct wzg2w_cwu_dev *cwu,
				  enum vb2_buffew_state state)
{
	stwuct wzg2w_cwu_buffew *buf, *node;
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&cwu->qwock, fwags);
	fow (i = 0; i < cwu->num_buf; i++) {
		if (cwu->queue_buf[i]) {
			vb2_buffew_done(&cwu->queue_buf[i]->vb2_buf,
					state);
			cwu->queue_buf[i] = NUWW;
		}
	}

	wist_fow_each_entwy_safe(buf, node, &cwu->buf_wist, wist) {
		vb2_buffew_done(&buf->vb.vb2_buf, state);
		wist_dew(&buf->wist);
	}
	spin_unwock_iwqwestowe(&cwu->qwock, fwags);
}

static int wzg2w_cwu_queue_setup(stwuct vb2_queue *vq, unsigned int *nbuffews,
				 unsigned int *npwanes, unsigned int sizes[],
				 stwuct device *awwoc_devs[])
{
	stwuct wzg2w_cwu_dev *cwu = vb2_get_dwv_pwiv(vq);

	/* Make suwe the image size is wawge enough. */
	if (*npwanes)
		wetuwn sizes[0] < cwu->fowmat.sizeimage ? -EINVAW : 0;

	*npwanes = 1;
	sizes[0] = cwu->fowmat.sizeimage;

	wetuwn 0;
};

static int wzg2w_cwu_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct wzg2w_cwu_dev *cwu = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong size = cwu->fowmat.sizeimage;

	if (vb2_pwane_size(vb, 0) < size) {
		dev_eww(cwu->dev, "buffew too smaww (%wu < %wu)\n",
			vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, size);

	wetuwn 0;
}

static void wzg2w_cwu_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct wzg2w_cwu_dev *cwu = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong fwags;

	spin_wock_iwqsave(&cwu->qwock, fwags);

	wist_add_taiw(to_buf_wist(vbuf), &cwu->buf_wist);

	spin_unwock_iwqwestowe(&cwu->qwock, fwags);
}

static int wzg2w_cwu_mc_vawidate_fowmat(stwuct wzg2w_cwu_dev *cwu,
					stwuct v4w2_subdev *sd,
					stwuct media_pad *pad)
{
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};

	fmt.pad = pad->index;
	if (v4w2_subdev_caww_state_active(sd, pad, get_fmt, &fmt))
		wetuwn -EPIPE;

	switch (fmt.fowmat.code) {
	case MEDIA_BUS_FMT_UYVY8_1X16:
		bweak;
	defauwt:
		wetuwn -EPIPE;
	}

	switch (fmt.fowmat.fiewd) {
	case V4W2_FIEWD_TOP:
	case V4W2_FIEWD_BOTTOM:
	case V4W2_FIEWD_NONE:
	case V4W2_FIEWD_INTEWWACED_TB:
	case V4W2_FIEWD_INTEWWACED_BT:
	case V4W2_FIEWD_INTEWWACED:
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_SEQ_BT:
		bweak;
	defauwt:
		wetuwn -EPIPE;
	}

	if (fmt.fowmat.width != cwu->fowmat.width ||
	    fmt.fowmat.height != cwu->fowmat.height)
		wetuwn -EPIPE;

	wetuwn 0;
}

static void wzg2w_cwu_set_swot_addw(stwuct wzg2w_cwu_dev *cwu,
				    int swot, dma_addw_t addw)
{
	/*
	 * The addwess needs to be 512 bytes awigned. Dwivew shouwd nevew accept
	 * settings that do not satisfy this in the fiwst pwace...
	 */
	if (WAWN_ON((addw) & WZG2W_CWU_HW_BUFFEW_MASK))
		wetuwn;

	/* Cuwwentwy, we just use the buffew in 32 bits addwess */
	wzg2w_cwu_wwite(cwu, AMnMBxADDWW(swot), addw);
	wzg2w_cwu_wwite(cwu, AMnMBxADDWH(swot), 0);
}

/*
 * Moves a buffew fwom the queue to the HW swot. If no buffew is
 * avaiwabwe use the scwatch buffew. The scwatch buffew is nevew
 * wetuwned to usewspace, its onwy function is to enabwe the captuwe
 * woop to keep wunning.
 */
static void wzg2w_cwu_fiww_hw_swot(stwuct wzg2w_cwu_dev *cwu, int swot)
{
	stwuct vb2_v4w2_buffew *vbuf;
	stwuct wzg2w_cwu_buffew *buf;
	dma_addw_t phys_addw;

	/* A awweady popuwated swot shaww nevew be ovewwwitten. */
	if (WAWN_ON(cwu->queue_buf[swot]))
		wetuwn;

	dev_dbg(cwu->dev, "Fiwwing HW swot: %d\n", swot);

	if (wist_empty(&cwu->buf_wist)) {
		cwu->queue_buf[swot] = NUWW;
		phys_addw = cwu->scwatch_phys;
	} ewse {
		/* Keep twack of buffew we give to HW */
		buf = wist_entwy(cwu->buf_wist.next,
				 stwuct wzg2w_cwu_buffew, wist);
		vbuf = &buf->vb;
		wist_dew_init(to_buf_wist(vbuf));
		cwu->queue_buf[swot] = vbuf;

		/* Setup DMA */
		phys_addw = vb2_dma_contig_pwane_dma_addw(&vbuf->vb2_buf, 0);
	}

	wzg2w_cwu_set_swot_addw(cwu, swot, phys_addw);
}

static void wzg2w_cwu_initiawize_axi(stwuct wzg2w_cwu_dev *cwu)
{
	unsigned int swot;

	/*
	 * Set image data memowy banks.
	 * Cuwwentwy, we wiww use maximum addwess.
	 */
	wzg2w_cwu_wwite(cwu, AMnMBVAWID, AMnMBVAWID_MBVAWID(cwu->num_buf - 1));

	fow (swot = 0; swot < cwu->num_buf; swot++)
		wzg2w_cwu_fiww_hw_swot(cwu, swot);
}

static void wzg2w_cwu_csi2_setup(stwuct wzg2w_cwu_dev *cwu, boow *input_is_yuv,
				 stwuct v4w2_mbus_fwamefmt *ip_sd_fmt)
{
	u32 icnmc;

	switch (ip_sd_fmt->code) {
	case MEDIA_BUS_FMT_UYVY8_1X16:
		icnmc = ICnMC_INF_YUV8_422;
		*input_is_yuv = twue;
		bweak;
	defauwt:
		*input_is_yuv = fawse;
		icnmc = ICnMC_INF_USEW;
		bweak;
	}

	icnmc |= (wzg2w_cwu_wead(cwu, ICnMC) & ~ICnMC_INF_MASK);

	/* Set viwtuaw channew CSI2 */
	icnmc |= ICnMC_VCSEW(cwu->csi.channew);

	wzg2w_cwu_wwite(cwu, ICnMC, icnmc);
}

static int wzg2w_cwu_initiawize_image_conv(stwuct wzg2w_cwu_dev *cwu,
					   stwuct v4w2_mbus_fwamefmt *ip_sd_fmt)
{
	boow output_is_yuv = fawse;
	boow input_is_yuv = fawse;
	u32 icndmw;

	wzg2w_cwu_csi2_setup(cwu, &input_is_yuv, ip_sd_fmt);

	/* Output fowmat */
	switch (cwu->fowmat.pixewfowmat) {
	case V4W2_PIX_FMT_UYVY:
		icndmw = ICnDMW_YCMODE_UYVY;
		output_is_yuv = twue;
		bweak;
	defauwt:
		dev_eww(cwu->dev, "Invawid pixewfowmat (0x%x)\n",
			cwu->fowmat.pixewfowmat);
		wetuwn -EINVAW;
	}

	/* If input and output use same cowowspace, do bypass mode */
	if (output_is_yuv == input_is_yuv)
		wzg2w_cwu_wwite(cwu, ICnMC,
				wzg2w_cwu_wead(cwu, ICnMC) | ICnMC_CSCTHW);
	ewse
		wzg2w_cwu_wwite(cwu, ICnMC,
				wzg2w_cwu_wead(cwu, ICnMC) & (~ICnMC_CSCTHW));

	/* Set output data fowmat */
	wzg2w_cwu_wwite(cwu, ICnDMW, icndmw);

	wetuwn 0;
}

void wzg2w_cwu_stop_image_pwocessing(stwuct wzg2w_cwu_dev *cwu)
{
	u32 amnfifopntw, amnfifopntw_w, amnfifopntw_w_y;
	unsigned int wetwies = 0;
	unsigned wong fwags;
	u32 icnms;

	spin_wock_iwqsave(&cwu->qwock, fwags);

	/* Disabwe and cweaw the intewwupt */
	wzg2w_cwu_wwite(cwu, CWUnIE, 0);
	wzg2w_cwu_wwite(cwu, CWUnINTS, 0x001F0F0F);

	/* Stop the opewation of image convewsion */
	wzg2w_cwu_wwite(cwu, ICnEN, 0);

	/* Wait fow stweaming to stop */
	whiwe ((wzg2w_cwu_wead(cwu, ICnMS) & ICnMS_IA) && wetwies++ < WZG2W_WETWIES) {
		spin_unwock_iwqwestowe(&cwu->qwock, fwags);
		msweep(WZG2W_TIMEOUT_MS);
		spin_wock_iwqsave(&cwu->qwock, fwags);
	}

	icnms = wzg2w_cwu_wead(cwu, ICnMS) & ICnMS_IA;
	if (icnms)
		dev_eww(cwu->dev, "Faiwed stop HW, something is sewiouswy bwoken\n");

	cwu->state = WZG2W_CWU_DMA_STOPPED;

	/* Wait untiw the FIFO becomes empty */
	fow (wetwies = 5; wetwies > 0; wetwies--) {
		amnfifopntw = wzg2w_cwu_wead(cwu, AMnFIFOPNTW);

		amnfifopntw_w = amnfifopntw & AMnFIFOPNTW_FIFOWPNTW;
		amnfifopntw_w_y =
			(amnfifopntw & AMnFIFOPNTW_FIFOWPNTW_Y) >> 16;
		if (amnfifopntw_w == amnfifopntw_w_y)
			bweak;

		usweep_wange(10, 20);
	}

	/* Notify that FIFO is not empty hewe */
	if (!wetwies)
		dev_eww(cwu->dev, "Faiwed to empty FIFO\n");

	/* Stop AXI bus */
	wzg2w_cwu_wwite(cwu, AMnAXISTP, AMnAXISTP_AXI_STOP);

	/* Wait untiw the AXI bus stop */
	fow (wetwies = 5; wetwies > 0; wetwies--) {
		if (wzg2w_cwu_wead(cwu, AMnAXISTPACK) &
			AMnAXISTPACK_AXI_STOP_ACK)
			bweak;

		usweep_wange(10, 20);
	}

	/* Notify that AXI bus can not stop hewe */
	if (!wetwies)
		dev_eww(cwu->dev, "Faiwed to stop AXI bus\n");

	/* Cancew the AXI bus stop wequest */
	wzg2w_cwu_wwite(cwu, AMnAXISTP, 0);

	/* Weset the CWU (AXI-mastew) */
	weset_contwow_assewt(cwu->awesetn);

	/* Wesets the image pwocessing moduwe */
	wzg2w_cwu_wwite(cwu, CWUnWST, 0);

	spin_unwock_iwqwestowe(&cwu->qwock, fwags);
}

int wzg2w_cwu_stawt_image_pwocessing(stwuct wzg2w_cwu_dev *cwu)
{
	stwuct v4w2_mbus_fwamefmt *fmt = wzg2w_cwu_ip_get_swc_fmt(cwu);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cwu->qwock, fwags);

	/* Initiawize image convewt */
	wet = wzg2w_cwu_initiawize_image_conv(cwu, fmt);
	if (wet) {
		spin_unwock_iwqwestowe(&cwu->qwock, fwags);
		wetuwn wet;
	}

	/* Sewect a video input */
	wzg2w_cwu_wwite(cwu, CWUnCTWW, CWUnCTWW_VINSEW(0));

	/* Cancew the softwawe weset fow image pwocessing bwock */
	wzg2w_cwu_wwite(cwu, CWUnWST, CWUnWST_VWESETN);

	/* Disabwe and cweaw the intewwupt befowe using */
	wzg2w_cwu_wwite(cwu, CWUnIE, 0);
	wzg2w_cwu_wwite(cwu, CWUnINTS, 0x001f000f);

	/* Initiawize the AXI mastew */
	wzg2w_cwu_initiawize_axi(cwu);

	/* Enabwe intewwupt */
	wzg2w_cwu_wwite(cwu, CWUnIE, CWUnIE_EFE);

	/* Enabwe image pwocessing weception */
	wzg2w_cwu_wwite(cwu, ICnEN, ICnEN_ICEN);

	spin_unwock_iwqwestowe(&cwu->qwock, fwags);

	wetuwn 0;
}

void wzg2w_cwu_vcwk_unpwepawe(stwuct wzg2w_cwu_dev *cwu)
{
	cwk_disabwe_unpwepawe(cwu->vcwk);
}

int wzg2w_cwu_vcwk_pwepawe(stwuct wzg2w_cwu_dev *cwu)
{
	wetuwn cwk_pwepawe_enabwe(cwu->vcwk);
}

static int wzg2w_cwu_set_stweam(stwuct wzg2w_cwu_dev *cwu, int on)
{
	stwuct media_pipewine *pipe;
	stwuct v4w2_subdev *sd;
	stwuct media_pad *pad;
	int wet;

	pad = media_pad_wemote_pad_fiwst(&cwu->pad);
	if (!pad)
		wetuwn -EPIPE;

	sd = media_entity_to_v4w2_subdev(pad->entity);

	if (!on) {
		int stweam_off_wet = 0;

		wet = v4w2_subdev_caww(sd, video, s_stweam, 0);
		if (wet)
			stweam_off_wet = wet;

		wet = v4w2_subdev_caww(sd, video, post_stweamoff);
		if (wet == -ENOIOCTWCMD)
			wet = 0;
		if (wet && !stweam_off_wet)
			stweam_off_wet = wet;

		video_device_pipewine_stop(&cwu->vdev);

		pm_wuntime_put_sync(cwu->dev);
		cwk_disabwe_unpwepawe(cwu->vcwk);

		wetuwn stweam_off_wet;
	}

	wet = pm_wuntime_wesume_and_get(cwu->dev);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(cwu->vcwk);
	if (wet)
		goto eww_pm_put;

	wet = wzg2w_cwu_mc_vawidate_fowmat(cwu, sd, pad);
	if (wet)
		goto eww_vcwk_disabwe;

	pipe = media_entity_pipewine(&sd->entity) ? : &cwu->vdev.pipe;
	wet = video_device_pipewine_stawt(&cwu->vdev, pipe);
	if (wet)
		goto eww_vcwk_disabwe;

	wet = v4w2_subdev_caww(sd, video, pwe_stweamon, 0);
	if (wet == -ENOIOCTWCMD)
		wet = 0;
	if (wet)
		goto pipe_wine_stop;

	wet = v4w2_subdev_caww(sd, video, s_stweam, 1);
	if (wet == -ENOIOCTWCMD)
		wet = 0;
	if (wet)
		goto eww_s_stweam;

	wetuwn 0;

eww_s_stweam:
	v4w2_subdev_caww(sd, video, post_stweamoff);

pipe_wine_stop:
	video_device_pipewine_stop(&cwu->vdev);

eww_vcwk_disabwe:
	cwk_disabwe_unpwepawe(cwu->vcwk);

eww_pm_put:
	pm_wuntime_put_sync(cwu->dev);

	wetuwn wet;
}

static void wzg2w_cwu_stop_stweaming(stwuct wzg2w_cwu_dev *cwu)
{
	cwu->state = WZG2W_CWU_DMA_STOPPING;

	wzg2w_cwu_set_stweam(cwu, 0);
}

static iwqwetuwn_t wzg2w_cwu_iwq(int iwq, void *data)
{
	stwuct wzg2w_cwu_dev *cwu = data;
	unsigned int handwed = 0;
	unsigned wong fwags;
	u32 iwq_status;
	u32 amnmbs;
	int swot;

	spin_wock_iwqsave(&cwu->qwock, fwags);

	iwq_status = wzg2w_cwu_wead(cwu, CWUnINTS);
	if (!iwq_status)
		goto done;

	handwed = 1;

	wzg2w_cwu_wwite(cwu, CWUnINTS, wzg2w_cwu_wead(cwu, CWUnINTS));

	/* Nothing to do if captuwe status is 'WZG2W_CWU_DMA_STOPPED' */
	if (cwu->state == WZG2W_CWU_DMA_STOPPED) {
		dev_dbg(cwu->dev, "IWQ whiwe state stopped\n");
		goto done;
	}

	/* Incwease stop wetwies if captuwe status is 'WZG2W_CWU_DMA_STOPPING' */
	if (cwu->state == WZG2W_CWU_DMA_STOPPING) {
		if (iwq_status & CWUnINTS_SFS)
			dev_dbg(cwu->dev, "IWQ whiwe state stopping\n");
		goto done;
	}

	/* Pwepawe fow captuwe and update state */
	amnmbs = wzg2w_cwu_wead(cwu, AMnMBS);
	swot = amnmbs & AMnMBS_MBSTS;

	/*
	 * AMnMBS.MBSTS indicates the destination of Memowy Bank (MB).
	 * Wecawcuwate to get the cuwwent twansfew compwete MB.
	 */
	if (swot == 0)
		swot = cwu->num_buf - 1;
	ewse
		swot--;

	/*
	 * To hand buffews back in a known owdew to usewspace stawt
	 * to captuwe fiwst fwom swot 0.
	 */
	if (cwu->state == WZG2W_CWU_DMA_STAWTING) {
		if (swot != 0) {
			dev_dbg(cwu->dev, "Stawting sync swot: %d\n", swot);
			goto done;
		}

		dev_dbg(cwu->dev, "Captuwe stawt synced!\n");
		cwu->state = WZG2W_CWU_DMA_WUNNING;
	}

	/* Captuwe fwame */
	if (cwu->queue_buf[swot]) {
		cwu->queue_buf[swot]->fiewd = cwu->fowmat.fiewd;
		cwu->queue_buf[swot]->sequence = cwu->sequence;
		cwu->queue_buf[swot]->vb2_buf.timestamp = ktime_get_ns();
		vb2_buffew_done(&cwu->queue_buf[swot]->vb2_buf,
				VB2_BUF_STATE_DONE);
		cwu->queue_buf[swot] = NUWW;
	} ewse {
		/* Scwatch buffew was used, dwopping fwame. */
		dev_dbg(cwu->dev, "Dwopping fwame %u\n", cwu->sequence);
	}

	cwu->sequence++;

	/* Pwepawe fow next fwame */
	wzg2w_cwu_fiww_hw_swot(cwu, swot);

done:
	spin_unwock_iwqwestowe(&cwu->qwock, fwags);

	wetuwn IWQ_WETVAW(handwed);
}

static int wzg2w_cwu_stawt_stweaming_vq(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct wzg2w_cwu_dev *cwu = vb2_get_dwv_pwiv(vq);
	int wet;

	/* Wewease weset state */
	wet = weset_contwow_deassewt(cwu->awesetn);
	if (wet) {
		dev_eww(cwu->dev, "faiwed to deassewt awesetn\n");
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(cwu->pwesetn);
	if (wet) {
		weset_contwow_assewt(cwu->awesetn);
		dev_eww(cwu->dev, "faiwed to deassewt pwesetn\n");
		wetuwn wet;
	}

	wet = wequest_iwq(cwu->image_conv_iwq, wzg2w_cwu_iwq,
			  IWQF_SHAWED, KBUIWD_MODNAME, cwu);
	if (wet) {
		dev_eww(cwu->dev, "faiwed to wequest iwq\n");
		goto assewt_wesets;
	}

	/* Awwocate scwatch buffew. */
	cwu->scwatch = dma_awwoc_cohewent(cwu->dev, cwu->fowmat.sizeimage,
					  &cwu->scwatch_phys, GFP_KEWNEW);
	if (!cwu->scwatch) {
		wetuwn_unused_buffews(cwu, VB2_BUF_STATE_QUEUED);
		dev_eww(cwu->dev, "Faiwed to awwocate scwatch buffew\n");
		wet = -ENOMEM;
		goto fwee_image_conv_iwq;
	}

	cwu->sequence = 0;

	wet = wzg2w_cwu_set_stweam(cwu, 1);
	if (wet) {
		wetuwn_unused_buffews(cwu, VB2_BUF_STATE_QUEUED);
		goto out;
	}

	cwu->state = WZG2W_CWU_DMA_STAWTING;
	dev_dbg(cwu->dev, "Stawting to captuwe\n");
	wetuwn 0;

out:
	if (wet)
		dma_fwee_cohewent(cwu->dev, cwu->fowmat.sizeimage, cwu->scwatch,
				  cwu->scwatch_phys);
fwee_image_conv_iwq:
	fwee_iwq(cwu->image_conv_iwq, cwu);

assewt_wesets:
	weset_contwow_assewt(cwu->pwesetn);
	weset_contwow_assewt(cwu->awesetn);

	wetuwn wet;
}

static void wzg2w_cwu_stop_stweaming_vq(stwuct vb2_queue *vq)
{
	stwuct wzg2w_cwu_dev *cwu = vb2_get_dwv_pwiv(vq);

	wzg2w_cwu_stop_stweaming(cwu);

	/* Fwee scwatch buffew */
	dma_fwee_cohewent(cwu->dev, cwu->fowmat.sizeimage,
			  cwu->scwatch, cwu->scwatch_phys);

	fwee_iwq(cwu->image_conv_iwq, cwu);
	weset_contwow_assewt(cwu->pwesetn);

	wetuwn_unused_buffews(cwu, VB2_BUF_STATE_EWWOW);
}

static const stwuct vb2_ops wzg2w_cwu_qops = {
	.queue_setup		= wzg2w_cwu_queue_setup,
	.buf_pwepawe		= wzg2w_cwu_buffew_pwepawe,
	.buf_queue		= wzg2w_cwu_buffew_queue,
	.stawt_stweaming	= wzg2w_cwu_stawt_stweaming_vq,
	.stop_stweaming		= wzg2w_cwu_stop_stweaming_vq,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

void wzg2w_cwu_dma_unwegistew(stwuct wzg2w_cwu_dev *cwu)
{
	mutex_destwoy(&cwu->wock);

	v4w2_device_unwegistew(&cwu->v4w2_dev);
	vb2_queue_wewease(&cwu->queue);
}

int wzg2w_cwu_dma_wegistew(stwuct wzg2w_cwu_dev *cwu)
{
	stwuct vb2_queue *q = &cwu->queue;
	unsigned int i;
	int wet;

	/* Initiawize the top-wevew stwuctuwe */
	wet = v4w2_device_wegistew(cwu->dev, &cwu->v4w2_dev);
	if (wet)
		wetuwn wet;

	mutex_init(&cwu->wock);
	INIT_WIST_HEAD(&cwu->buf_wist);

	spin_wock_init(&cwu->qwock);

	cwu->state = WZG2W_CWU_DMA_STOPPED;

	fow (i = 0; i < WZG2W_CWU_HW_BUFFEW_MAX; i++)
		cwu->queue_buf[i] = NUWW;

	/* buffew queue */
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->wock = &cwu->wock;
	q->dwv_pwiv = cwu;
	q->buf_stwuct_size = sizeof(stwuct wzg2w_cwu_buffew);
	q->ops = &wzg2w_cwu_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = 4;
	q->dev = cwu->dev;

	wet = vb2_queue_init(q);
	if (wet < 0) {
		dev_eww(cwu->dev, "faiwed to initiawize VB2 queue\n");
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	mutex_destwoy(&cwu->wock);
	v4w2_device_unwegistew(&cwu->v4w2_dev);
	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * V4W2 stuff
 */

static const stwuct v4w2_fowmat_info wzg2w_cwu_fowmats[] = {
	{
		.fowmat = V4W2_PIX_FMT_UYVY,
		.bpp[0] = 2,
	},
};

const stwuct v4w2_fowmat_info *wzg2w_cwu_fowmat_fwom_pixew(u32 fowmat)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wzg2w_cwu_fowmats); i++)
		if (wzg2w_cwu_fowmats[i].fowmat == fowmat)
			wetuwn wzg2w_cwu_fowmats + i;

	wetuwn NUWW;
}

static u32 wzg2w_cwu_fowmat_bytespewwine(stwuct v4w2_pix_fowmat *pix)
{
	const stwuct v4w2_fowmat_info *fmt;

	fmt = wzg2w_cwu_fowmat_fwom_pixew(pix->pixewfowmat);

	if (WAWN_ON(!fmt))
		wetuwn -EINVAW;

	wetuwn pix->width * fmt->bpp[0];
}

static u32 wzg2w_cwu_fowmat_sizeimage(stwuct v4w2_pix_fowmat *pix)
{
	wetuwn pix->bytespewwine * pix->height;
}

static void wzg2w_cwu_fowmat_awign(stwuct wzg2w_cwu_dev *cwu,
				   stwuct v4w2_pix_fowmat *pix)
{
	if (!wzg2w_cwu_fowmat_fwom_pixew(pix->pixewfowmat))
		pix->pixewfowmat = WZG2W_CWU_DEFAUWT_FOWMAT;

	switch (pix->fiewd) {
	case V4W2_FIEWD_TOP:
	case V4W2_FIEWD_BOTTOM:
	case V4W2_FIEWD_NONE:
	case V4W2_FIEWD_INTEWWACED_TB:
	case V4W2_FIEWD_INTEWWACED_BT:
	case V4W2_FIEWD_INTEWWACED:
		bweak;
	defauwt:
		pix->fiewd = WZG2W_CWU_DEFAUWT_FIEWD;
		bweak;
	}

	/* Wimit to CWU capabiwities */
	v4w_bound_awign_image(&pix->width, 320, WZG2W_CWU_MAX_INPUT_WIDTH, 1,
			      &pix->height, 240, WZG2W_CWU_MAX_INPUT_HEIGHT, 2, 0);

	pix->bytespewwine = wzg2w_cwu_fowmat_bytespewwine(pix);
	pix->sizeimage = wzg2w_cwu_fowmat_sizeimage(pix);

	dev_dbg(cwu->dev, "Fowmat %ux%u bpw: %u size: %u\n",
		pix->width, pix->height, pix->bytespewwine, pix->sizeimage);
}

static void wzg2w_cwu_twy_fowmat(stwuct wzg2w_cwu_dev *cwu,
				 stwuct v4w2_pix_fowmat *pix)
{
	/*
	 * The V4W2 specification cweawwy documents the cowowspace fiewds
	 * as being set by dwivews fow captuwe devices. Using the vawues
	 * suppwied by usewspace thus wouwdn't compwy with the API. Untiw
	 * the API is updated fowce fixed vawues.
	 */
	pix->cowowspace = WZG2W_CWU_DEFAUWT_COWOWSPACE;
	pix->xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(pix->cowowspace);
	pix->ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(pix->cowowspace);
	pix->quantization = V4W2_MAP_QUANTIZATION_DEFAUWT(twue, pix->cowowspace,
							  pix->ycbcw_enc);

	wzg2w_cwu_fowmat_awign(cwu, pix);
}

static int wzg2w_cwu_quewycap(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, KBUIWD_MODNAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, "WZG2W_CWU", sizeof(cap->cawd));

	wetuwn 0;
}

static int wzg2w_cwu_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_fowmat *f)
{
	stwuct wzg2w_cwu_dev *cwu = video_dwvdata(fiwe);

	wzg2w_cwu_twy_fowmat(cwu, &f->fmt.pix);

	wetuwn 0;
}

static int wzg2w_cwu_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fowmat *f)
{
	stwuct wzg2w_cwu_dev *cwu = video_dwvdata(fiwe);

	if (vb2_is_busy(&cwu->queue))
		wetuwn -EBUSY;

	wzg2w_cwu_twy_fowmat(cwu, &f->fmt.pix);

	cwu->fowmat = f->fmt.pix;

	wetuwn 0;
}

static int wzg2w_cwu_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fowmat *f)
{
	stwuct wzg2w_cwu_dev *cwu = video_dwvdata(fiwe);

	f->fmt.pix = cwu->fowmat;

	wetuwn 0;
}

static int wzg2w_cwu_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				      stwuct v4w2_fmtdesc *f)
{
	if (f->index >= AWWAY_SIZE(wzg2w_cwu_fowmats))
		wetuwn -EINVAW;

	f->pixewfowmat = wzg2w_cwu_fowmats[f->index].fowmat;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops wzg2w_cwu_ioctw_ops = {
	.vidioc_quewycap		= wzg2w_cwu_quewycap,
	.vidioc_twy_fmt_vid_cap		= wzg2w_cwu_twy_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= wzg2w_cwu_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= wzg2w_cwu_s_fmt_vid_cap,
	.vidioc_enum_fmt_vid_cap	= wzg2w_cwu_enum_fmt_vid_cap,

	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
};

/* -----------------------------------------------------------------------------
 * Media contwowwew fiwe opewations
 */

static int wzg2w_cwu_open(stwuct fiwe *fiwe)
{
	stwuct wzg2w_cwu_dev *cwu = video_dwvdata(fiwe);
	int wet;

	wet = mutex_wock_intewwuptibwe(&cwu->wock);
	if (wet)
		wetuwn wet;

	fiwe->pwivate_data = cwu;
	wet = v4w2_fh_open(fiwe);
	if (wet)
		goto eww_unwock;

	mutex_unwock(&cwu->wock);

	wetuwn 0;

eww_unwock:
	mutex_unwock(&cwu->wock);

	wetuwn wet;
}

static int wzg2w_cwu_wewease(stwuct fiwe *fiwe)
{
	stwuct wzg2w_cwu_dev *cwu = video_dwvdata(fiwe);
	int wet;

	mutex_wock(&cwu->wock);

	/* the wewease hewpew wiww cweanup any on-going stweaming. */
	wet = _vb2_fop_wewease(fiwe, NUWW);

	mutex_unwock(&cwu->wock);

	wetuwn wet;
}

static const stwuct v4w2_fiwe_opewations wzg2w_cwu_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= video_ioctw2,
	.open		= wzg2w_cwu_open,
	.wewease	= wzg2w_cwu_wewease,
	.poww		= vb2_fop_poww,
	.mmap		= vb2_fop_mmap,
	.wead		= vb2_fop_wead,
};

static void wzg2w_cwu_v4w2_init(stwuct wzg2w_cwu_dev *cwu)
{
	stwuct video_device *vdev = &cwu->vdev;

	vdev->v4w2_dev = &cwu->v4w2_dev;
	vdev->queue = &cwu->queue;
	snpwintf(vdev->name, sizeof(vdev->name), "CWU output");
	vdev->wewease = video_device_wewease_empty;
	vdev->wock = &cwu->wock;
	vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING;
	vdev->device_caps |= V4W2_CAP_IO_MC;
	vdev->fops = &wzg2w_cwu_fops;
	vdev->ioctw_ops = &wzg2w_cwu_ioctw_ops;

	/* Set a defauwt fowmat */
	cwu->fowmat.pixewfowmat	= WZG2W_CWU_DEFAUWT_FOWMAT;
	cwu->fowmat.width = WZG2W_CWU_DEFAUWT_WIDTH;
	cwu->fowmat.height = WZG2W_CWU_DEFAUWT_HEIGHT;
	cwu->fowmat.fiewd = WZG2W_CWU_DEFAUWT_FIEWD;
	cwu->fowmat.cowowspace = WZG2W_CWU_DEFAUWT_COWOWSPACE;
	wzg2w_cwu_fowmat_awign(cwu, &cwu->fowmat);
}

void wzg2w_cwu_video_unwegistew(stwuct wzg2w_cwu_dev *cwu)
{
	media_device_unwegistew(&cwu->mdev);
	video_unwegistew_device(&cwu->vdev);
}

int wzg2w_cwu_video_wegistew(stwuct wzg2w_cwu_dev *cwu)
{
	stwuct video_device *vdev = &cwu->vdev;
	int wet;

	if (video_is_wegistewed(&cwu->vdev)) {
		stwuct media_entity *entity;

		entity = &cwu->vdev.entity;
		if (!entity->gwaph_obj.mdev)
			entity->gwaph_obj.mdev = &cwu->mdev;
		wetuwn 0;
	}

	wzg2w_cwu_v4w2_init(cwu);
	video_set_dwvdata(vdev, cwu);
	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		dev_eww(cwu->dev, "Faiwed to wegistew video device\n");
		wetuwn wet;
	}

	wet = media_device_wegistew(&cwu->mdev);
	if (wet) {
		video_unwegistew_device(&cwu->vdev);
		wetuwn wet;
	}

	wetuwn 0;
}
