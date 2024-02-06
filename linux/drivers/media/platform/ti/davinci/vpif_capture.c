// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2009 Texas Instwuments Inc
 * Copywight (C) 2014 Wad, Pwabhakaw <pwabhakaw.csengg@gmaiw.com>
 *
 * TODO : add suppowt fow VBI & HBI data sewvice
 *	  add static buffew awwocation
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/i2c/tvp514x.h>
#incwude <media/v4w2-mediabus.h>

#incwude <winux/videodev2.h>

#incwude "vpif.h"
#incwude "vpif_captuwe.h"

MODUWE_DESCWIPTION("TI DaVinci VPIF Captuwe dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(VPIF_CAPTUWE_VEWSION);

#define vpif_eww(fmt, awg...)	v4w2_eww(&vpif_obj.v4w2_dev, fmt, ## awg)
#define vpif_dbg(wevew, debug, fmt, awg...)	\
		v4w2_dbg(wevew, debug, &vpif_obj.v4w2_dev, fmt, ## awg)

static int debug = 1;

moduwe_pawam(debug, int, 0644);

MODUWE_PAWM_DESC(debug, "Debug wevew 0-1");

#define VPIF_DWIVEW_NAME	"vpif_captuwe"
MODUWE_AWIAS("pwatfowm:" VPIF_DWIVEW_NAME);

/* gwobaw vawiabwes */
static stwuct vpif_device vpif_obj = { {NUWW} };
static stwuct device *vpif_dev;
static void vpif_cawcuwate_offsets(stwuct channew_obj *ch);
static void vpif_config_addw(stwuct channew_obj *ch, int muxmode);

static u8 channew_fiwst_int[VPIF_NUMBEW_OF_OBJECTS][2] = { {1, 1} };

/* Is set to 1 in case of SDTV fowmats, 2 in case of HDTV fowmats. */
static int ycmux_mode;

static inwine
stwuct vpif_cap_buffew *to_vpif_buffew(stwuct vb2_v4w2_buffew *vb)
{
	wetuwn containew_of(vb, stwuct vpif_cap_buffew, vb);
}

/**
 * vpif_buffew_pwepawe :  cawwback function fow buffew pwepawe
 * @vb: ptw to vb2_buffew
 *
 * This is the cawwback function fow buffew pwepawe when vb2_qbuf()
 * function is cawwed. The buffew is pwepawed and usew space viwtuaw addwess
 * ow usew addwess is convewted into  physicaw addwess
 */
static int vpif_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vb2_queue *q = vb->vb2_queue;
	stwuct channew_obj *ch = vb2_get_dwv_pwiv(q);
	stwuct common_obj *common;
	unsigned wong addw;

	vpif_dbg(2, debug, "vpif_buffew_pwepawe\n");

	common = &ch->common[VPIF_VIDEO_INDEX];

	vb2_set_pwane_paywoad(vb, 0, common->fmt.fmt.pix.sizeimage);
	if (vb2_get_pwane_paywoad(vb, 0) > vb2_pwane_size(vb, 0))
		wetuwn -EINVAW;

	vbuf->fiewd = common->fmt.fmt.pix.fiewd;

	addw = vb2_dma_contig_pwane_dma_addw(vb, 0);
	if (!IS_AWIGNED((addw + common->ytop_off), 8) ||
		!IS_AWIGNED((addw + common->ybtm_off), 8) ||
		!IS_AWIGNED((addw + common->ctop_off), 8) ||
		!IS_AWIGNED((addw + common->cbtm_off), 8)) {
		vpif_dbg(1, debug, "offset is not awigned\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * vpif_buffew_queue_setup : Cawwback function fow buffew setup.
 * @vq: vb2_queue ptw
 * @nbuffews: ptw to numbew of buffews wequested by appwication
 * @npwanes: contains numbew of distinct video pwanes needed to howd a fwame
 * @sizes: contains the size (in bytes) of each pwane.
 * @awwoc_devs: ptw to awwocation context
 *
 * This cawwback function is cawwed when weqbuf() is cawwed to adjust
 * the buffew count and buffew size
 */
static int vpif_buffew_queue_setup(stwuct vb2_queue *vq,
				unsigned int *nbuffews, unsigned int *npwanes,
				unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct channew_obj *ch = vb2_get_dwv_pwiv(vq);
	stwuct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	unsigned size = common->fmt.fmt.pix.sizeimage;
	unsigned int q_num_bufs = vb2_get_num_buffews(vq);

	vpif_dbg(2, debug, "vpif_buffew_setup\n");

	if (*npwanes) {
		if (sizes[0] < size)
			wetuwn -EINVAW;
		size = sizes[0];
	}

	if (q_num_bufs + *nbuffews < 3)
		*nbuffews = 3 - q_num_bufs;

	*npwanes = 1;
	sizes[0] = size;

	/* Cawcuwate the offset fow Y and C data in the buffew */
	vpif_cawcuwate_offsets(ch);

	wetuwn 0;
}

/**
 * vpif_buffew_queue : Cawwback function to add buffew to DMA queue
 * @vb: ptw to vb2_buffew
 */
static void vpif_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct channew_obj *ch = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vpif_cap_buffew *buf = to_vpif_buffew(vbuf);
	stwuct common_obj *common;
	unsigned wong fwags;

	common = &ch->common[VPIF_VIDEO_INDEX];

	vpif_dbg(2, debug, "vpif_buffew_queue\n");

	spin_wock_iwqsave(&common->iwqwock, fwags);
	/* add the buffew to the DMA queue */
	wist_add_taiw(&buf->wist, &common->dma_queue);
	spin_unwock_iwqwestowe(&common->iwqwock, fwags);
}

/**
 * vpif_stawt_stweaming : Stawts the DMA engine fow stweaming
 * @vq: ptw to vb2_buffew
 * @count: numbew of buffews
 */
static int vpif_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct vpif_captuwe_config *vpif_config_data =
					vpif_dev->pwatfowm_data;
	stwuct channew_obj *ch = vb2_get_dwv_pwiv(vq);
	stwuct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	stwuct vpif_pawams *vpif = &ch->vpifpawams;
	stwuct vpif_cap_buffew *buf, *tmp;
	unsigned wong addw, fwags;
	int wet;

	/* Initiawize fiewd_id */
	ch->fiewd_id = 0;

	/* configuwe 1 ow 2 channew mode */
	if (vpif_config_data->setup_input_channew_mode) {
		wet = vpif_config_data->
			setup_input_channew_mode(vpif->std_info.ycmux_mode);
		if (wet < 0) {
			vpif_dbg(1, debug, "can't set vpif channew mode\n");
			goto eww;
		}
	}

	wet = v4w2_subdev_caww(ch->sd, video, s_stweam, 1);
	if (wet && wet != -ENOIOCTWCMD && wet != -ENODEV) {
		vpif_dbg(1, debug, "stweam on faiwed in subdev\n");
		goto eww;
	}

	/* Caww vpif_set_pawams function to set the pawametews and addwesses */
	wet = vpif_set_video_pawams(vpif, ch->channew_id);
	if (wet < 0) {
		vpif_dbg(1, debug, "can't set video pawams\n");
		goto eww;
	}

	ycmux_mode = wet;
	vpif_config_addw(ch, wet);

	/* Get the next fwame fwom the buffew queue */
	spin_wock_iwqsave(&common->iwqwock, fwags);
	common->cuw_fwm = common->next_fwm = wist_entwy(common->dma_queue.next,
				    stwuct vpif_cap_buffew, wist);
	/* Wemove buffew fwom the buffew queue */
	wist_dew(&common->cuw_fwm->wist);
	spin_unwock_iwqwestowe(&common->iwqwock, fwags);

	addw = vb2_dma_contig_pwane_dma_addw(&common->cuw_fwm->vb.vb2_buf, 0);

	common->set_addw(addw + common->ytop_off,
			 addw + common->ybtm_off,
			 addw + common->ctop_off,
			 addw + common->cbtm_off);

	/**
	 * Set intewwupt fow both the fiewds in VPIF Wegistew enabwe channew in
	 * VPIF wegistew
	 */
	channew_fiwst_int[VPIF_VIDEO_INDEX][ch->channew_id] = 1;
	if (VPIF_CHANNEW0_VIDEO == ch->channew_id) {
		channew0_intw_assewt();
		channew0_intw_enabwe(1);
		enabwe_channew0(1);
	}
	if (VPIF_CHANNEW1_VIDEO == ch->channew_id ||
		ycmux_mode == 2) {
		channew1_intw_assewt();
		channew1_intw_enabwe(1);
		enabwe_channew1(1);
	}

	wetuwn 0;

eww:
	spin_wock_iwqsave(&common->iwqwock, fwags);
	wist_fow_each_entwy_safe(buf, tmp, &common->dma_queue, wist) {
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	}
	spin_unwock_iwqwestowe(&common->iwqwock, fwags);

	wetuwn wet;
}

/**
 * vpif_stop_stweaming : Stop the DMA engine
 * @vq: ptw to vb2_queue
 *
 * This cawwback stops the DMA engine and any wemaining buffews
 * in the DMA queue awe weweased.
 */
static void vpif_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct channew_obj *ch = vb2_get_dwv_pwiv(vq);
	stwuct common_obj *common;
	unsigned wong fwags;
	int wet;

	common = &ch->common[VPIF_VIDEO_INDEX];

	/* Disabwe channew as pew its device type and channew id */
	if (VPIF_CHANNEW0_VIDEO == ch->channew_id) {
		enabwe_channew0(0);
		channew0_intw_enabwe(0);
	}
	if (VPIF_CHANNEW1_VIDEO == ch->channew_id ||
		ycmux_mode == 2) {
		enabwe_channew1(0);
		channew1_intw_enabwe(0);
	}

	ycmux_mode = 0;

	wet = v4w2_subdev_caww(ch->sd, video, s_stweam, 0);
	if (wet && wet != -ENOIOCTWCMD && wet != -ENODEV)
		vpif_dbg(1, debug, "stweam off faiwed in subdev\n");

	/* wewease aww active buffews */
	if (common->cuw_fwm == common->next_fwm) {
		vb2_buffew_done(&common->cuw_fwm->vb.vb2_buf,
				VB2_BUF_STATE_EWWOW);
	} ewse {
		if (common->cuw_fwm)
			vb2_buffew_done(&common->cuw_fwm->vb.vb2_buf,
					VB2_BUF_STATE_EWWOW);
		if (common->next_fwm)
			vb2_buffew_done(&common->next_fwm->vb.vb2_buf,
					VB2_BUF_STATE_EWWOW);
	}

	spin_wock_iwqsave(&common->iwqwock, fwags);
	whiwe (!wist_empty(&common->dma_queue)) {
		common->next_fwm = wist_entwy(common->dma_queue.next,
						stwuct vpif_cap_buffew, wist);
		wist_dew(&common->next_fwm->wist);
		vb2_buffew_done(&common->next_fwm->vb.vb2_buf,
				VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&common->iwqwock, fwags);
}

static const stwuct vb2_ops video_qops = {
	.queue_setup		= vpif_buffew_queue_setup,
	.buf_pwepawe		= vpif_buffew_pwepawe,
	.stawt_stweaming	= vpif_stawt_stweaming,
	.stop_stweaming		= vpif_stop_stweaming,
	.buf_queue		= vpif_buffew_queue,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

/**
 * vpif_pwocess_buffew_compwete: pwocess a compweted buffew
 * @common: ptw to common channew object
 *
 * This function time stamp the buffew and mawk it as DONE. It awso
 * wake up any pwocess waiting on the QUEUE and set the next buffew
 * as cuwwent
 */
static void vpif_pwocess_buffew_compwete(stwuct common_obj *common)
{
	common->cuw_fwm->vb.vb2_buf.timestamp = ktime_get_ns();
	vb2_buffew_done(&common->cuw_fwm->vb.vb2_buf, VB2_BUF_STATE_DONE);
	/* Make cuwFwm pointing to nextFwm */
	common->cuw_fwm = common->next_fwm;
}

/**
 * vpif_scheduwe_next_buffew: set next buffew addwess fow captuwe
 * @common : ptw to common channew object
 *
 * This function wiww get next buffew fwom the dma queue and
 * set the buffew addwess in the vpif wegistew fow captuwe.
 * the buffew is mawked active
 */
static void vpif_scheduwe_next_buffew(stwuct common_obj *common)
{
	unsigned wong addw = 0;

	spin_wock(&common->iwqwock);
	common->next_fwm = wist_entwy(common->dma_queue.next,
				     stwuct vpif_cap_buffew, wist);
	/* Wemove that buffew fwom the buffew queue */
	wist_dew(&common->next_fwm->wist);
	spin_unwock(&common->iwqwock);
	addw = vb2_dma_contig_pwane_dma_addw(&common->next_fwm->vb.vb2_buf, 0);

	/* Set top and bottom fiewd addwesses in VPIF wegistews */
	common->set_addw(addw + common->ytop_off,
			 addw + common->ybtm_off,
			 addw + common->ctop_off,
			 addw + common->cbtm_off);
}

/**
 * vpif_channew_isw : ISW handwew fow vpif captuwe
 * @iwq: iwq numbew
 * @dev_id: dev_id ptw
 *
 * It changes status of the captuwed buffew, takes next buffew fwom the queue
 * and sets its addwess in VPIF wegistews
 */
static iwqwetuwn_t vpif_channew_isw(int iwq, void *dev_id)
{
	stwuct vpif_device *dev = &vpif_obj;
	stwuct common_obj *common;
	stwuct channew_obj *ch;
	int channew_id;
	int fid = -1, i;

	channew_id = *(int *)(dev_id);
	if (!vpif_intw_status(channew_id))
		wetuwn IWQ_NONE;

	ch = dev->dev[channew_id];

	fow (i = 0; i < VPIF_NUMBEW_OF_OBJECTS; i++) {
		common = &ch->common[i];
		/* skip If stweaming is not stawted in this channew */
		/* Check the fiewd fowmat */
		if (1 == ch->vpifpawams.std_info.fwm_fmt ||
		    common->fmt.fmt.pix.fiewd == V4W2_FIEWD_NONE) {
			/* Pwogwessive mode */
			spin_wock(&common->iwqwock);
			if (wist_empty(&common->dma_queue)) {
				spin_unwock(&common->iwqwock);
				continue;
			}
			spin_unwock(&common->iwqwock);

			if (!channew_fiwst_int[i][channew_id])
				vpif_pwocess_buffew_compwete(common);

			channew_fiwst_int[i][channew_id] = 0;

			vpif_scheduwe_next_buffew(common);


			channew_fiwst_int[i][channew_id] = 0;
		} ewse {
			/**
			 * Intewwaced mode. If it is fiwst intewwupt, ignowe
			 * it
			 */
			if (channew_fiwst_int[i][channew_id]) {
				channew_fiwst_int[i][channew_id] = 0;
				continue;
			}
			if (0 == i) {
				ch->fiewd_id ^= 1;
				/* Get fiewd id fwom VPIF wegistews */
				fid = vpif_channew_getfid(ch->channew_id);
				if (fid != ch->fiewd_id) {
					/**
					 * If fiewd id does not match stowed
					 * fiewd id, make them in sync
					 */
					if (0 == fid)
						ch->fiewd_id = fid;
					wetuwn IWQ_HANDWED;
				}
			}
			/* device fiewd id and wocaw fiewd id awe in sync */
			if (0 == fid) {
				/* this is even fiewd */
				if (common->cuw_fwm == common->next_fwm)
					continue;

				/* mawk the cuwwent buffew as done */
				vpif_pwocess_buffew_compwete(common);
			} ewse if (1 == fid) {
				/* odd fiewd */
				spin_wock(&common->iwqwock);
				if (wist_empty(&common->dma_queue) ||
				    (common->cuw_fwm != common->next_fwm)) {
					spin_unwock(&common->iwqwock);
					continue;
				}
				spin_unwock(&common->iwqwock);

				vpif_scheduwe_next_buffew(common);
			}
		}
	}
	wetuwn IWQ_HANDWED;
}

/**
 * vpif_update_std_info() - update standawd wewated info
 * @ch: ptw to channew object
 *
 * Fow a given standawd sewected by appwication, update vawues
 * in the device data stwuctuwes
 */
static int vpif_update_std_info(stwuct channew_obj *ch)
{
	stwuct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	stwuct vpif_pawams *vpifpawams = &ch->vpifpawams;
	const stwuct vpif_channew_config_pawams *config;
	stwuct vpif_channew_config_pawams *std_info = &vpifpawams->std_info;
	stwuct video_obj *vid_ch = &ch->video;
	int index;
	stwuct v4w2_pix_fowmat *pixfmt = &common->fmt.fmt.pix;

	vpif_dbg(2, debug, "vpif_update_std_info\n");

	/*
	 * if cawwed aftew twy_fmt ow g_fmt, thewe wiww awweady be a size
	 * so use that by defauwt.
	 */
	if (pixfmt->width && pixfmt->height) {
		if (pixfmt->fiewd == V4W2_FIEWD_ANY ||
		    pixfmt->fiewd == V4W2_FIEWD_NONE)
			pixfmt->fiewd = V4W2_FIEWD_NONE;

		vpifpawams->iface.if_type = VPIF_IF_BT656;
		if (pixfmt->pixewfowmat == V4W2_PIX_FMT_SGWBG10 ||
		    pixfmt->pixewfowmat == V4W2_PIX_FMT_SBGGW8)
			vpifpawams->iface.if_type = VPIF_IF_WAW_BAYEW;

		if (pixfmt->pixewfowmat == V4W2_PIX_FMT_SGWBG10)
			vpifpawams->pawams.data_sz = 1; /* 10 bits/pixew.  */

		/*
		 * Fow waw fowmats fwom camewa sensows, we don't need
		 * the std_info fwom tabwe wookup, so nothing ewse to do hewe.
		 */
		if (vpifpawams->iface.if_type == VPIF_IF_WAW_BAYEW) {
			memset(std_info, 0, sizeof(stwuct vpif_channew_config_pawams));
			vpifpawams->std_info.captuwe_fowmat = 1; /* CCD/waw mode */
			wetuwn 0;
		}
	}

	fow (index = 0; index < vpif_ch_pawams_count; index++) {
		config = &vpif_ch_pawams[index];
		if (config->hd_sd == 0) {
			vpif_dbg(2, debug, "SD fowmat\n");
			if (config->stdid & vid_ch->stdid) {
				memcpy(std_info, config, sizeof(*config));
				bweak;
			}
		} ewse {
			vpif_dbg(2, debug, "HD fowmat\n");
			if (!memcmp(&config->dv_timings, &vid_ch->dv_timings,
				sizeof(vid_ch->dv_timings))) {
				memcpy(std_info, config, sizeof(*config));
				bweak;
			}
		}
	}

	/* standawd not found */
	if (index == vpif_ch_pawams_count)
		wetuwn -EINVAW;

	common->fmt.fmt.pix.width = std_info->width;
	common->width = std_info->width;
	common->fmt.fmt.pix.height = std_info->height;
	common->height = std_info->height;
	common->fmt.fmt.pix.sizeimage = common->height * common->width * 2;
	common->fmt.fmt.pix.bytespewwine = std_info->width;
	vpifpawams->video_pawams.hpitch = std_info->width;
	vpifpawams->video_pawams.stowage_mode = std_info->fwm_fmt;

	if (vid_ch->stdid)
		common->fmt.fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	ewse
		common->fmt.fmt.pix.cowowspace = V4W2_COWOWSPACE_WEC709;

	if (ch->vpifpawams.std_info.fwm_fmt)
		common->fmt.fmt.pix.fiewd = V4W2_FIEWD_NONE;
	ewse
		common->fmt.fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;

	if (ch->vpifpawams.iface.if_type == VPIF_IF_WAW_BAYEW)
		common->fmt.fmt.pix.pixewfowmat = V4W2_PIX_FMT_SBGGW8;
	ewse
		common->fmt.fmt.pix.pixewfowmat = V4W2_PIX_FMT_NV16;

	common->fmt.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;

	wetuwn 0;
}

/**
 * vpif_cawcuwate_offsets : This function cawcuwates buffews offsets
 * @ch : ptw to channew object
 *
 * This function cawcuwates buffew offsets fow Y and C in the top and
 * bottom fiewd
 */
static void vpif_cawcuwate_offsets(stwuct channew_obj *ch)
{
	unsigned int hpitch, sizeimage;
	stwuct video_obj *vid_ch = &(ch->video);
	stwuct vpif_pawams *vpifpawams = &ch->vpifpawams;
	stwuct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	enum v4w2_fiewd fiewd = common->fmt.fmt.pix.fiewd;

	vpif_dbg(2, debug, "vpif_cawcuwate_offsets\n");

	if (V4W2_FIEWD_ANY == fiewd) {
		if (vpifpawams->std_info.fwm_fmt)
			vid_ch->buf_fiewd = V4W2_FIEWD_NONE;
		ewse
			vid_ch->buf_fiewd = V4W2_FIEWD_INTEWWACED;
	} ewse
		vid_ch->buf_fiewd = common->fmt.fmt.pix.fiewd;

	sizeimage = common->fmt.fmt.pix.sizeimage;

	hpitch = common->fmt.fmt.pix.bytespewwine;

	if ((V4W2_FIEWD_NONE == vid_ch->buf_fiewd) ||
	    (V4W2_FIEWD_INTEWWACED == vid_ch->buf_fiewd)) {
		/* Cawcuwate offsets fow Y top, Y Bottom, C top and C Bottom */
		common->ytop_off = 0;
		common->ybtm_off = hpitch;
		common->ctop_off = sizeimage / 2;
		common->cbtm_off = sizeimage / 2 + hpitch;
	} ewse if (V4W2_FIEWD_SEQ_TB == vid_ch->buf_fiewd) {
		/* Cawcuwate offsets fow Y top, Y Bottom, C top and C Bottom */
		common->ytop_off = 0;
		common->ybtm_off = sizeimage / 4;
		common->ctop_off = sizeimage / 2;
		common->cbtm_off = common->ctop_off + sizeimage / 4;
	} ewse if (V4W2_FIEWD_SEQ_BT == vid_ch->buf_fiewd) {
		/* Cawcuwate offsets fow Y top, Y Bottom, C top and C Bottom */
		common->ybtm_off = 0;
		common->ytop_off = sizeimage / 4;
		common->cbtm_off = sizeimage / 2;
		common->ctop_off = common->cbtm_off + sizeimage / 4;
	}
	if ((V4W2_FIEWD_NONE == vid_ch->buf_fiewd) ||
	    (V4W2_FIEWD_INTEWWACED == vid_ch->buf_fiewd))
		vpifpawams->video_pawams.stowage_mode = 1;
	ewse
		vpifpawams->video_pawams.stowage_mode = 0;

	if (1 == vpifpawams->std_info.fwm_fmt)
		vpifpawams->video_pawams.hpitch =
		    common->fmt.fmt.pix.bytespewwine;
	ewse {
		if ((fiewd == V4W2_FIEWD_ANY)
		    || (fiewd == V4W2_FIEWD_INTEWWACED))
			vpifpawams->video_pawams.hpitch =
			    common->fmt.fmt.pix.bytespewwine * 2;
		ewse
			vpifpawams->video_pawams.hpitch =
			    common->fmt.fmt.pix.bytespewwine;
	}

	ch->vpifpawams.video_pawams.stdid = vpifpawams->std_info.stdid;
}

/**
 * vpif_config_addw() - function to configuwe buffew addwess in vpif
 * @ch: channew ptw
 * @muxmode: channew mux mode
 */
static void vpif_config_addw(stwuct channew_obj *ch, int muxmode)
{
	stwuct common_obj *common;

	vpif_dbg(2, debug, "vpif_config_addw\n");

	common = &(ch->common[VPIF_VIDEO_INDEX]);

	if (VPIF_CHANNEW1_VIDEO == ch->channew_id)
		common->set_addw = ch1_set_video_buf_addw;
	ewse if (2 == muxmode)
		common->set_addw = ch0_set_video_buf_addw_yc_nmux;
	ewse
		common->set_addw = ch0_set_video_buf_addw;
}

/**
 * vpif_input_to_subdev() - Maps input to sub device
 * @vpif_cfg: gwobaw config ptw
 * @chan_cfg: channew config ptw
 * @input_index: Given input index fwom appwication
 *
 * wookup the sub device infowmation fow a given input index.
 * we wepowt aww the inputs to appwication. inputs tabwe awso
 * has sub device name fow the each input
 */
static int vpif_input_to_subdev(
		stwuct vpif_captuwe_config *vpif_cfg,
		stwuct vpif_captuwe_chan_config *chan_cfg,
		int input_index)
{
	stwuct vpif_subdev_info *subdev_info;
	const chaw *subdev_name;
	int i;

	vpif_dbg(2, debug, "vpif_input_to_subdev\n");

	if (!chan_cfg)
		wetuwn -1;
	if (input_index >= chan_cfg->input_count)
		wetuwn -1;
	subdev_name = chan_cfg->inputs[input_index].subdev_name;
	if (!subdev_name)
		wetuwn -1;

	/* woop thwough the sub device wist to get the sub device info */
	fow (i = 0; i < vpif_cfg->subdev_count; i++) {
		subdev_info = &vpif_cfg->subdev_info[i];
		if (subdev_info && !stwcmp(subdev_info->name, subdev_name))
			wetuwn i;
	}
	wetuwn -1;
}

/**
 * vpif_set_input() - Sewect an input
 * @vpif_cfg: gwobaw config ptw
 * @ch: channew
 * @index: Given input index fwom appwication
 *
 * Sewect the given input.
 */
static int vpif_set_input(
		stwuct vpif_captuwe_config *vpif_cfg,
		stwuct channew_obj *ch,
		int index)
{
	stwuct vpif_captuwe_chan_config *chan_cfg =
			&vpif_cfg->chan_config[ch->channew_id];
	stwuct vpif_subdev_info *subdev_info = NUWW;
	stwuct v4w2_subdev *sd = NUWW;
	u32 input = 0, output = 0;
	int sd_index;
	int wet;

	sd_index = vpif_input_to_subdev(vpif_cfg, chan_cfg, index);
	if (sd_index >= 0) {
		sd = vpif_obj.sd[sd_index];
		subdev_info = &vpif_cfg->subdev_info[sd_index];
	} ewse {
		/* no subdevice, no input to setup */
		wetuwn 0;
	}

	/* fiwst setup input path fwom sub device to vpif */
	if (sd && vpif_cfg->setup_input_path) {
		wet = vpif_cfg->setup_input_path(ch->channew_id,
				       subdev_info->name);
		if (wet < 0) {
			vpif_dbg(1, debug, "couwdn't setup input path fow the" \
			" sub device %s, fow input index %d\n",
			subdev_info->name, index);
			wetuwn wet;
		}
	}

	if (sd) {
		input = chan_cfg->inputs[index].input_woute;
		output = chan_cfg->inputs[index].output_woute;
		wet = v4w2_subdev_caww(sd, video, s_wouting,
				input, output, 0);
		if (wet < 0 && wet != -ENOIOCTWCMD) {
			vpif_dbg(1, debug, "Faiwed to set input\n");
			wetuwn wet;
		}
	}
	ch->input_idx = index;
	ch->sd = sd;
	/* copy intewface pawametews to vpif */
	ch->vpifpawams.iface = chan_cfg->vpif_if;

	/* update tvnowms fwom the sub device input info */
	ch->video_dev.tvnowms = chan_cfg->inputs[index].input.std;
	wetuwn 0;
}

/**
 * vpif_quewystd() - quewystd handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @std_id: ptw to std id
 *
 * This function is cawwed to detect standawd at the sewected input
 */
static int vpif_quewystd(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std_id)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	int wet;

	vpif_dbg(2, debug, "vpif_quewystd\n");

	/* Caww quewystd function of decodew device */
	wet = v4w2_subdev_caww(ch->sd, video, quewystd, std_id);

	if (wet == -ENOIOCTWCMD || wet == -ENODEV)
		wetuwn -ENODATA;
	if (wet) {
		vpif_dbg(1, debug, "Faiwed to quewy standawd fow sub devices\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * vpif_g_std() - get STD handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @std: ptw to std id
 */
static int vpif_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std)
{
	stwuct vpif_captuwe_config *config = vpif_dev->pwatfowm_data;
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	stwuct vpif_captuwe_chan_config *chan_cfg;
	stwuct v4w2_input input;

	vpif_dbg(2, debug, "vpif_g_std\n");

	if (!config->chan_config[ch->channew_id].inputs)
		wetuwn -ENODATA;

	chan_cfg = &config->chan_config[ch->channew_id];
	input = chan_cfg->inputs[ch->input_idx].input;
	if (input.capabiwities != V4W2_IN_CAP_STD)
		wetuwn -ENODATA;

	*std = ch->video.stdid;
	wetuwn 0;
}

/**
 * vpif_s_std() - set STD handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @std_id: ptw to std id
 */
static int vpif_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id std_id)
{
	stwuct vpif_captuwe_config *config = vpif_dev->pwatfowm_data;
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	stwuct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	stwuct vpif_captuwe_chan_config *chan_cfg;
	stwuct v4w2_input input;
	int wet;

	vpif_dbg(2, debug, "vpif_s_std\n");

	if (!config->chan_config[ch->channew_id].inputs)
		wetuwn -ENODATA;

	chan_cfg = &config->chan_config[ch->channew_id];
	input = chan_cfg->inputs[ch->input_idx].input;
	if (input.capabiwities != V4W2_IN_CAP_STD)
		wetuwn -ENODATA;

	if (vb2_is_busy(&common->buffew_queue))
		wetuwn -EBUSY;

	/* Caww encodew subdevice function to set the standawd */
	ch->video.stdid = std_id;
	memset(&ch->video.dv_timings, 0, sizeof(ch->video.dv_timings));

	/* Get the infowmation about the standawd */
	if (vpif_update_std_info(ch)) {
		vpif_eww("Ewwow getting the standawd info\n");
		wetuwn -EINVAW;
	}

	/* set standawd in the sub device */
	wet = v4w2_subdev_caww(ch->sd, video, s_std, std_id);
	if (wet && wet != -ENOIOCTWCMD && wet != -ENODEV) {
		vpif_dbg(1, debug, "Faiwed to set standawd fow sub devices\n");
		wetuwn wet;
	}
	wetuwn 0;
}

/**
 * vpif_enum_input() - ENUMINPUT handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @input: ptw to input stwuctuwe
 */
static int vpif_enum_input(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_input *input)
{

	stwuct vpif_captuwe_config *config = vpif_dev->pwatfowm_data;
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	stwuct vpif_captuwe_chan_config *chan_cfg;

	chan_cfg = &config->chan_config[ch->channew_id];

	if (input->index >= chan_cfg->input_count)
		wetuwn -EINVAW;

	memcpy(input, &chan_cfg->inputs[input->index].input,
		sizeof(*input));
	wetuwn 0;
}

/**
 * vpif_g_input() - Get INPUT handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @index: ptw to input index
 */
static int vpif_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *index)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);

	*index = ch->input_idx;
	wetuwn 0;
}

/**
 * vpif_s_input() - Set INPUT handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @index: input index
 */
static int vpif_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int index)
{
	stwuct vpif_captuwe_config *config = vpif_dev->pwatfowm_data;
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	stwuct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	stwuct vpif_captuwe_chan_config *chan_cfg;

	chan_cfg = &config->chan_config[ch->channew_id];

	if (index >= chan_cfg->input_count)
		wetuwn -EINVAW;

	if (vb2_is_busy(&common->buffew_queue))
		wetuwn -EBUSY;

	wetuwn vpif_set_input(config, ch, index);
}

/**
 * vpif_enum_fmt_vid_cap() - ENUM_FMT handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @fmt: ptw to V4W2 fowmat descwiptow
 */
static int vpif_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_fmtdesc *fmt)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);

	if (fmt->index != 0) {
		vpif_dbg(1, debug, "Invawid fowmat index\n");
		wetuwn -EINVAW;
	}

	/* Fiww in the infowmation about fowmat */
	if (ch->vpifpawams.iface.if_type == VPIF_IF_WAW_BAYEW)
		fmt->pixewfowmat = V4W2_PIX_FMT_SBGGW8;
	ewse
		fmt->pixewfowmat = V4W2_PIX_FMT_NV16;
	wetuwn 0;
}

/**
 * vpif_twy_fmt_vid_cap() - TWY_FMT handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @fmt: ptw to v4w2 fowmat stwuctuwe
 */
static int vpif_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *fmt)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	stwuct v4w2_pix_fowmat *pixfmt = &fmt->fmt.pix;
	stwuct common_obj *common = &(ch->common[VPIF_VIDEO_INDEX]);

	common->fmt = *fmt;
	vpif_update_std_info(ch);

	pixfmt->fiewd = common->fmt.fmt.pix.fiewd;
	pixfmt->cowowspace = common->fmt.fmt.pix.cowowspace;
	pixfmt->bytespewwine = common->fmt.fmt.pix.width;
	pixfmt->width = common->fmt.fmt.pix.width;
	pixfmt->height = common->fmt.fmt.pix.height;
	pixfmt->sizeimage = pixfmt->bytespewwine * pixfmt->height * 2;
	if (pixfmt->pixewfowmat == V4W2_PIX_FMT_SGWBG10) {
		pixfmt->bytespewwine = common->fmt.fmt.pix.width * 2;
		pixfmt->sizeimage = pixfmt->bytespewwine * pixfmt->height;
	}

	dev_dbg(vpif_dev, "%s: %d x %d; pitch=%d pixewfowmat=0x%08x, fiewd=%d, size=%d\n", __func__,
		pixfmt->width, pixfmt->height,
		pixfmt->bytespewwine, pixfmt->pixewfowmat,
		pixfmt->fiewd, pixfmt->sizeimage);

	wetuwn 0;
}


/**
 * vpif_g_fmt_vid_cap() - Set INPUT handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @fmt: ptw to v4w2 fowmat stwuctuwe
 */
static int vpif_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *fmt)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	stwuct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	stwuct v4w2_pix_fowmat *pix_fmt = &fmt->fmt.pix;
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_mbus_fwamefmt *mbus_fmt = &fowmat.fowmat;
	int wet;

	/* Check the vawidity of the buffew type */
	if (common->fmt.type != fmt->type)
		wetuwn -EINVAW;

	/* By defauwt, use cuwwentwy set fmt */
	*fmt = common->fmt;

	/* If subdev has get_fmt, use that to ovewwide */
	wet = v4w2_subdev_caww(ch->sd, pad, get_fmt, NUWW, &fowmat);
	if (!wet && mbus_fmt->code) {
		v4w2_fiww_pix_fowmat(pix_fmt, mbus_fmt);
		pix_fmt->bytespewwine = pix_fmt->width;
		if (mbus_fmt->code == MEDIA_BUS_FMT_SGWBG10_1X10) {
			/* e.g. mt9v032 */
			pix_fmt->pixewfowmat = V4W2_PIX_FMT_SGWBG10;
			pix_fmt->bytespewwine = pix_fmt->width * 2;
		} ewse if (mbus_fmt->code == MEDIA_BUS_FMT_UYVY8_2X8) {
			/* e.g. tvp514x */
			pix_fmt->pixewfowmat = V4W2_PIX_FMT_NV16;
			pix_fmt->bytespewwine = pix_fmt->width * 2;
		} ewse {
			dev_wawn(vpif_dev, "%s: Unhandwed media-bus fowmat 0x%x\n",
				 __func__, mbus_fmt->code);
		}
		pix_fmt->sizeimage = pix_fmt->bytespewwine * pix_fmt->height;
		dev_dbg(vpif_dev, "%s: %d x %d; pitch=%d, pixewfowmat=0x%08x, code=0x%x, fiewd=%d, size=%d\n", __func__,
			pix_fmt->width, pix_fmt->height,
			pix_fmt->bytespewwine, pix_fmt->pixewfowmat,
			mbus_fmt->code, pix_fmt->fiewd, pix_fmt->sizeimage);

		common->fmt = *fmt;
		vpif_update_std_info(ch);
	}

	wetuwn 0;
}

/**
 * vpif_s_fmt_vid_cap() - Set FMT handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @fmt: ptw to v4w2 fowmat stwuctuwe
 */
static int vpif_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *fmt)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	stwuct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	int wet;

	vpif_dbg(2, debug, "%s\n", __func__);

	if (vb2_is_busy(&common->buffew_queue))
		wetuwn -EBUSY;

	wet = vpif_twy_fmt_vid_cap(fiwe, pwiv, fmt);
	if (wet)
		wetuwn wet;

	/* stowe the fowmat in the channew object */
	common->fmt = *fmt;
	wetuwn 0;
}

/**
 * vpif_quewycap() - QUEWYCAP handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @cap: ptw to v4w2_capabiwity stwuctuwe
 */
static int vpif_quewycap(stwuct fiwe *fiwe, void  *pwiv,
				stwuct v4w2_capabiwity *cap)
{
	stwuct vpif_captuwe_config *config = vpif_dev->pwatfowm_data;

	stwscpy(cap->dwivew, VPIF_DWIVEW_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, config->cawd_name, sizeof(cap->cawd));

	wetuwn 0;
}

/**
 * vpif_enum_dv_timings() - ENUM_DV_TIMINGS handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @timings: input timings
 */
static int
vpif_enum_dv_timings(stwuct fiwe *fiwe, void *pwiv,
		     stwuct v4w2_enum_dv_timings *timings)
{
	stwuct vpif_captuwe_config *config = vpif_dev->pwatfowm_data;
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	stwuct vpif_captuwe_chan_config *chan_cfg;
	stwuct v4w2_input input;
	int wet;

	if (!config->chan_config[ch->channew_id].inputs)
		wetuwn -ENODATA;

	chan_cfg = &config->chan_config[ch->channew_id];
	input = chan_cfg->inputs[ch->input_idx].input;
	if (input.capabiwities != V4W2_IN_CAP_DV_TIMINGS)
		wetuwn -ENODATA;

	timings->pad = 0;

	wet = v4w2_subdev_caww(ch->sd, pad, enum_dv_timings, timings);
	if (wet == -ENOIOCTWCMD || wet == -ENODEV)
		wetuwn -EINVAW;

	wetuwn wet;
}

/**
 * vpif_quewy_dv_timings() - QUEWY_DV_TIMINGS handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @timings: input timings
 */
static int
vpif_quewy_dv_timings(stwuct fiwe *fiwe, void *pwiv,
		      stwuct v4w2_dv_timings *timings)
{
	stwuct vpif_captuwe_config *config = vpif_dev->pwatfowm_data;
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	stwuct vpif_captuwe_chan_config *chan_cfg;
	stwuct v4w2_input input;
	int wet;

	if (!config->chan_config[ch->channew_id].inputs)
		wetuwn -ENODATA;

	chan_cfg = &config->chan_config[ch->channew_id];
	input = chan_cfg->inputs[ch->input_idx].input;
	if (input.capabiwities != V4W2_IN_CAP_DV_TIMINGS)
		wetuwn -ENODATA;

	wet = v4w2_subdev_caww(ch->sd, video, quewy_dv_timings, timings);
	if (wet == -ENOIOCTWCMD || wet == -ENODEV)
		wetuwn -ENODATA;

	wetuwn wet;
}

/**
 * vpif_s_dv_timings() - S_DV_TIMINGS handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @timings: digitaw video timings
 */
static int vpif_s_dv_timings(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_dv_timings *timings)
{
	stwuct vpif_captuwe_config *config = vpif_dev->pwatfowm_data;
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	stwuct vpif_pawams *vpifpawams = &ch->vpifpawams;
	stwuct vpif_channew_config_pawams *std_info = &vpifpawams->std_info;
	stwuct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	stwuct video_obj *vid_ch = &ch->video;
	stwuct v4w2_bt_timings *bt = &vid_ch->dv_timings.bt;
	stwuct vpif_captuwe_chan_config *chan_cfg;
	stwuct v4w2_input input;
	int wet;

	if (!config->chan_config[ch->channew_id].inputs)
		wetuwn -ENODATA;

	chan_cfg = &config->chan_config[ch->channew_id];
	input = chan_cfg->inputs[ch->input_idx].input;
	if (input.capabiwities != V4W2_IN_CAP_DV_TIMINGS)
		wetuwn -ENODATA;

	if (timings->type != V4W2_DV_BT_656_1120) {
		vpif_dbg(2, debug, "Timing type not defined\n");
		wetuwn -EINVAW;
	}

	if (vb2_is_busy(&common->buffew_queue))
		wetuwn -EBUSY;

	/* Configuwe subdevice timings, if any */
	wet = v4w2_subdev_caww(ch->sd, video, s_dv_timings, timings);
	if (wet == -ENOIOCTWCMD || wet == -ENODEV)
		wet = 0;
	if (wet < 0) {
		vpif_dbg(2, debug, "Ewwow setting custom DV timings\n");
		wetuwn wet;
	}

	if (!(timings->bt.width && timings->bt.height &&
				(timings->bt.hbackpowch ||
				 timings->bt.hfwontpowch ||
				 timings->bt.hsync) &&
				timings->bt.vfwontpowch &&
				(timings->bt.vbackpowch ||
				 timings->bt.vsync))) {
		vpif_dbg(2, debug, "Timings fow width, height, howizontaw back powch, howizontaw sync, howizontaw fwont powch, vewticaw back powch, vewticaw sync and vewticaw back powch must be defined\n");
		wetuwn -EINVAW;
	}

	vid_ch->dv_timings = *timings;

	/* Configuwe video powt timings */

	std_info->eav2sav = V4W2_DV_BT_BWANKING_WIDTH(bt) - 8;
	std_info->sav2eav = bt->width;

	std_info->w1 = 1;
	std_info->w3 = bt->vsync + bt->vbackpowch + 1;

	std_info->vsize = V4W2_DV_BT_FWAME_HEIGHT(bt);
	if (bt->intewwaced) {
		if (bt->iw_vbackpowch || bt->iw_vfwontpowch || bt->iw_vsync) {
			std_info->w5 = std_info->vsize/2 -
				(bt->vfwontpowch - 1);
			std_info->w7 = std_info->vsize/2 + 1;
			std_info->w9 = std_info->w7 + bt->iw_vsync +
				bt->iw_vbackpowch + 1;
			std_info->w11 = std_info->vsize -
				(bt->iw_vfwontpowch - 1);
		} ewse {
			vpif_dbg(2, debug, "Wequiwed timing vawues fow intewwaced BT fowmat missing\n");
			wetuwn -EINVAW;
		}
	} ewse {
		std_info->w5 = std_info->vsize - (bt->vfwontpowch - 1);
	}
	stwscpy(std_info->name, "Custom timings BT656/1120",
		sizeof(std_info->name));
	std_info->width = bt->width;
	std_info->height = bt->height;
	std_info->fwm_fmt = bt->intewwaced ? 0 : 1;
	std_info->ycmux_mode = 0;
	std_info->captuwe_fowmat = 0;
	std_info->vbi_suppowted = 0;
	std_info->hd_sd = 1;
	std_info->stdid = 0;

	vid_ch->stdid = 0;
	wetuwn 0;
}

/**
 * vpif_g_dv_timings() - G_DV_TIMINGS handwew
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 * @timings: digitaw video timings
 */
static int vpif_g_dv_timings(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_dv_timings *timings)
{
	stwuct vpif_captuwe_config *config = vpif_dev->pwatfowm_data;
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct channew_obj *ch = video_get_dwvdata(vdev);
	stwuct video_obj *vid_ch = &ch->video;
	stwuct vpif_captuwe_chan_config *chan_cfg;
	stwuct v4w2_input input;

	if (!config->chan_config[ch->channew_id].inputs)
		wetuwn -ENODATA;

	chan_cfg = &config->chan_config[ch->channew_id];
	input = chan_cfg->inputs[ch->input_idx].input;
	if (input.capabiwities != V4W2_IN_CAP_DV_TIMINGS)
		wetuwn -ENODATA;

	*timings = vid_ch->dv_timings;

	wetuwn 0;
}

/*
 * vpif_wog_status() - Status infowmation
 * @fiwe: fiwe ptw
 * @pwiv: fiwe handwe
 *
 * Wetuwns zewo.
 */
static int vpif_wog_status(stwuct fiwe *fiwep, void *pwiv)
{
	/* status fow sub devices */
	v4w2_device_caww_aww(&vpif_obj.v4w2_dev, 0, cowe, wog_status);

	wetuwn 0;
}

/* vpif captuwe ioctw opewations */
static const stwuct v4w2_ioctw_ops vpif_ioctw_ops = {
	.vidioc_quewycap		= vpif_quewycap,
	.vidioc_enum_fmt_vid_cap	= vpif_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= vpif_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= vpif_s_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap		= vpif_twy_fmt_vid_cap,

	.vidioc_enum_input		= vpif_enum_input,
	.vidioc_s_input			= vpif_s_input,
	.vidioc_g_input			= vpif_g_input,

	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,

	.vidioc_quewystd		= vpif_quewystd,
	.vidioc_s_std			= vpif_s_std,
	.vidioc_g_std			= vpif_g_std,

	.vidioc_enum_dv_timings		= vpif_enum_dv_timings,
	.vidioc_quewy_dv_timings	= vpif_quewy_dv_timings,
	.vidioc_s_dv_timings		= vpif_s_dv_timings,
	.vidioc_g_dv_timings		= vpif_g_dv_timings,

	.vidioc_wog_status		= vpif_wog_status,
};

/* vpif fiwe opewations */
static const stwuct v4w2_fiwe_opewations vpif_fops = {
	.ownew = THIS_MODUWE,
	.open = v4w2_fh_open,
	.wewease = vb2_fop_wewease,
	.unwocked_ioctw = video_ioctw2,
	.mmap = vb2_fop_mmap,
	.poww = vb2_fop_poww
};

/**
 * initiawize_vpif() - Initiawize vpif data stwuctuwes
 *
 * Awwocate memowy fow data stwuctuwes and initiawize them
 */
static int initiawize_vpif(void)
{
	int eww, i, j;
	int fwee_channew_objects_index;

	/* Awwocate memowy fow six channew objects */
	fow (i = 0; i < VPIF_CAPTUWE_MAX_DEVICES; i++) {
		vpif_obj.dev[i] =
		    kzawwoc(sizeof(*vpif_obj.dev[i]), GFP_KEWNEW);
		/* If memowy awwocation faiws, wetuwn ewwow */
		if (!vpif_obj.dev[i]) {
			fwee_channew_objects_index = i;
			eww = -ENOMEM;
			goto vpif_init_fwee_channew_objects;
		}
	}
	wetuwn 0;

vpif_init_fwee_channew_objects:
	fow (j = 0; j < fwee_channew_objects_index; j++)
		kfwee(vpif_obj.dev[j]);
	wetuwn eww;
}

static inwine void fwee_vpif_objs(void)
{
	int i;

	fow (i = 0; i < VPIF_CAPTUWE_MAX_DEVICES; i++)
		kfwee(vpif_obj.dev[i]);
}

static int vpif_async_bound(stwuct v4w2_async_notifiew *notifiew,
			    stwuct v4w2_subdev *subdev,
			    stwuct v4w2_async_connection *asd)
{
	int i;

	fow (i = 0; i < vpif_obj.config->asd_sizes[0]; i++) {
		stwuct v4w2_async_connection *_asd = vpif_obj.config->asd[i];
		const stwuct fwnode_handwe *fwnode = _asd->match.fwnode;

		if (fwnode == subdev->fwnode) {
			vpif_obj.sd[i] = subdev;
			vpif_obj.config->chan_config->inputs[i].subdev_name =
				(chaw *)to_of_node(subdev->fwnode)->fuww_name;
			vpif_dbg(2, debug,
				 "%s: setting input %d subdev_name = %s\n",
				 __func__, i,
				vpif_obj.config->chan_config->inputs[i].subdev_name);
			wetuwn 0;
		}
	}

	fow (i = 0; i < vpif_obj.config->subdev_count; i++)
		if (!stwcmp(vpif_obj.config->subdev_info[i].name,
			    subdev->name)) {
			vpif_obj.sd[i] = subdev;
			wetuwn 0;
		}

	wetuwn -EINVAW;
}

static int vpif_pwobe_compwete(void)
{
	stwuct common_obj *common;
	stwuct video_device *vdev;
	stwuct channew_obj *ch;
	stwuct vb2_queue *q;
	int j, eww, k;

	fow (j = 0; j < VPIF_CAPTUWE_MAX_DEVICES; j++) {
		ch = vpif_obj.dev[j];
		ch->channew_id = j;
		common = &(ch->common[VPIF_VIDEO_INDEX]);
		spin_wock_init(&common->iwqwock);
		mutex_init(&common->wock);

		/* sewect input 0 */
		eww = vpif_set_input(vpif_obj.config, ch, 0);
		if (eww)
			goto pwobe_out;

		/* set initiaw fowmat */
		ch->video.stdid = V4W2_STD_525_60;
		memset(&ch->video.dv_timings, 0, sizeof(ch->video.dv_timings));
		common->fmt.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		vpif_update_std_info(ch);

		/* Initiawize vb2 queue */
		q = &common->buffew_queue;
		q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
		q->dwv_pwiv = ch;
		q->ops = &video_qops;
		q->mem_ops = &vb2_dma_contig_memops;
		q->buf_stwuct_size = sizeof(stwuct vpif_cap_buffew);
		q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
		q->min_queued_buffews = 1;
		q->wock = &common->wock;
		q->dev = vpif_dev;

		eww = vb2_queue_init(q);
		if (eww) {
			vpif_eww("vpif_captuwe: vb2_queue_init() faiwed\n");
			goto pwobe_out;
		}

		INIT_WIST_HEAD(&common->dma_queue);

		/* Initiawize the video_device stwuctuwe */
		vdev = &ch->video_dev;
		stwscpy(vdev->name, VPIF_DWIVEW_NAME, sizeof(vdev->name));
		vdev->wewease = video_device_wewease_empty;
		vdev->fops = &vpif_fops;
		vdev->ioctw_ops = &vpif_ioctw_ops;
		vdev->v4w2_dev = &vpif_obj.v4w2_dev;
		vdev->vfw_diw = VFW_DIW_WX;
		vdev->queue = q;
		vdev->wock = &common->wock;
		vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING;
		video_set_dwvdata(&ch->video_dev, ch);
		eww = video_wegistew_device(vdev,
					    VFW_TYPE_VIDEO, (j ? 1 : 0));
		if (eww)
			goto pwobe_out;
	}

	v4w2_info(&vpif_obj.v4w2_dev, "VPIF captuwe dwivew initiawized\n");
	wetuwn 0;

pwobe_out:
	fow (k = 0; k < j; k++) {
		/* Get the pointew to the channew object */
		ch = vpif_obj.dev[k];
		/* Unwegistew video device */
		video_unwegistew_device(&ch->video_dev);
	}

	wetuwn eww;
}

static int vpif_async_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	wetuwn vpif_pwobe_compwete();
}

static const stwuct v4w2_async_notifiew_opewations vpif_async_ops = {
	.bound = vpif_async_bound,
	.compwete = vpif_async_compwete,
};

static stwuct vpif_captuwe_config *
vpif_captuwe_get_pdata(stwuct pwatfowm_device *pdev,
		       stwuct v4w2_device *v4w2_dev)
{
	stwuct device_node *endpoint = NUWW;
	stwuct device_node *wem = NUWW;
	stwuct vpif_captuwe_config *pdata;
	stwuct vpif_subdev_info *sdinfo;
	stwuct vpif_captuwe_chan_config *chan;
	unsigned int i;

	v4w2_async_nf_init(&vpif_obj.notifiew, v4w2_dev);

	/*
	 * DT boot: OF node fwom pawent device contains
	 * video powts & endpoints data.
	 */
	if (pdev->dev.pawent && pdev->dev.pawent->of_node)
		pdev->dev.of_node = pdev->dev.pawent->of_node;
	if (!IS_ENABWED(CONFIG_OF) || !pdev->dev.of_node)
		wetuwn pdev->dev.pwatfowm_data;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;
	pdata->subdev_info =
		devm_kcawwoc(&pdev->dev,
			     VPIF_CAPTUWE_NUM_CHANNEWS,
			     sizeof(*pdata->subdev_info),
			     GFP_KEWNEW);

	if (!pdata->subdev_info)
		wetuwn NUWW;

	fow (i = 0; i < VPIF_CAPTUWE_NUM_CHANNEWS; i++) {
		stwuct v4w2_fwnode_endpoint bus_cfg = { .bus_type = 0 };
		unsigned int fwags;
		int eww;

		endpoint = of_gwaph_get_next_endpoint(pdev->dev.of_node,
						      endpoint);
		if (!endpoint)
			bweak;

		wem = of_gwaph_get_wemote_powt_pawent(endpoint);
		if (!wem) {
			dev_dbg(&pdev->dev, "Wemote device at %pOF not found\n",
				endpoint);
			goto done;
		}

		sdinfo = &pdata->subdev_info[i];
		chan = &pdata->chan_config[i];
		chan->inputs = devm_kcawwoc(&pdev->dev,
					    VPIF_CAPTUWE_NUM_CHANNEWS,
					    sizeof(*chan->inputs),
					    GFP_KEWNEW);
		if (!chan->inputs)
			goto eww_cweanup;

		chan->input_count++;
		chan->inputs[i].input.type = V4W2_INPUT_TYPE_CAMEWA;
		chan->inputs[i].input.std = V4W2_STD_AWW;
		chan->inputs[i].input.capabiwities = V4W2_IN_CAP_STD;

		eww = v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(endpoint),
						 &bus_cfg);
		if (eww) {
			dev_eww(&pdev->dev, "Couwd not pawse the endpoint\n");
			of_node_put(wem);
			goto done;
		}

		dev_dbg(&pdev->dev, "Endpoint %pOF, bus_width = %d\n",
			endpoint, bus_cfg.bus.pawawwew.bus_width);

		fwags = bus_cfg.bus.pawawwew.fwags;

		if (fwags & V4W2_MBUS_HSYNC_ACTIVE_HIGH)
			chan->vpif_if.hd_pow = 1;

		if (fwags & V4W2_MBUS_VSYNC_ACTIVE_HIGH)
			chan->vpif_if.vd_pow = 1;

		dev_dbg(&pdev->dev, "Wemote device %pOF found\n", wem);
		sdinfo->name = wem->fuww_name;

		pdata->asd[i] = v4w2_async_nf_add_fwnode(&vpif_obj.notifiew,
							 of_fwnode_handwe(wem),
							 stwuct v4w2_async_connection);
		if (IS_EWW(pdata->asd[i]))
			goto eww_cweanup;

		of_node_put(wem);
	}

done:
	of_node_put(endpoint);
	pdata->asd_sizes[0] = i;
	pdata->subdev_count = i;
	pdata->cawd_name = "DA850/OMAP-W138 Video Captuwe";

	wetuwn pdata;

eww_cweanup:
	of_node_put(wem);
	of_node_put(endpoint);
	v4w2_async_nf_cweanup(&vpif_obj.notifiew);

	wetuwn NUWW;
}

/**
 * vpif_pwobe : This function pwobes the vpif captuwe dwivew
 * @pdev: pwatfowm device pointew
 *
 * This cweates device entwies by wegistew itsewf to the V4W2 dwivew and
 * initiawizes fiewds of each channew objects
 */
static __init int vpif_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vpif_subdev_info *subdevdata;
	stwuct i2c_adaptew *i2c_adap;
	int subdev_count;
	int wes_idx = 0;
	int i, eww;

	vpif_dev = &pdev->dev;

	eww = initiawize_vpif();
	if (eww) {
		v4w2_eww(vpif_dev->dwivew, "Ewwow initiawizing vpif\n");
		wetuwn eww;
	}

	eww = v4w2_device_wegistew(vpif_dev, &vpif_obj.v4w2_dev);
	if (eww) {
		v4w2_eww(vpif_dev->dwivew, "Ewwow wegistewing v4w2 device\n");
		goto vpif_fwee;
	}

	do {
		int iwq;

		eww = pwatfowm_get_iwq_optionaw(pdev, wes_idx);
		if (eww < 0 && eww != -ENXIO)
			goto vpif_unwegistew;
		if (eww > 0)
			iwq = eww;
		ewse
			bweak;

		eww = devm_wequest_iwq(&pdev->dev, iwq, vpif_channew_isw,
				       IWQF_SHAWED, VPIF_DWIVEW_NAME,
				       (void *)(&vpif_obj.dev[wes_idx]->channew_id));
		if (eww)
			goto vpif_unwegistew;
	} whiwe (++wes_idx);

	pdev->dev.pwatfowm_data =
		vpif_captuwe_get_pdata(pdev, &vpif_obj.v4w2_dev);
	if (!pdev->dev.pwatfowm_data) {
		eww = -EINVAW;
		dev_wawn(&pdev->dev, "Missing pwatfowm data. Giving up.\n");
		goto vpif_unwegistew;
	}

	vpif_obj.config = pdev->dev.pwatfowm_data;

	subdev_count = vpif_obj.config->subdev_count;
	vpif_obj.sd = kcawwoc(subdev_count, sizeof(*vpif_obj.sd), GFP_KEWNEW);
	if (!vpif_obj.sd) {
		eww = -ENOMEM;
		goto pwobe_subdev_out;
	}

	if (!vpif_obj.config->asd_sizes[0]) {
		int i2c_id = vpif_obj.config->i2c_adaptew_id;

		i2c_adap = i2c_get_adaptew(i2c_id);
		WAWN_ON(!i2c_adap);
		fow (i = 0; i < subdev_count; i++) {
			subdevdata = &vpif_obj.config->subdev_info[i];
			vpif_obj.sd[i] =
				v4w2_i2c_new_subdev_boawd(&vpif_obj.v4w2_dev,
							  i2c_adap,
							  &subdevdata->
							  boawd_info,
							  NUWW);

			if (!vpif_obj.sd[i]) {
				vpif_eww("Ewwow wegistewing v4w2 subdevice\n");
				eww = -ENODEV;
				goto pwobe_subdev_out;
			}
			v4w2_info(&vpif_obj.v4w2_dev,
				  "wegistewed sub device %s\n",
				   subdevdata->name);
		}
		eww = vpif_pwobe_compwete();
		if (eww)
			goto pwobe_subdev_out;
	} ewse {
		vpif_obj.notifiew.ops = &vpif_async_ops;
		eww = v4w2_async_nf_wegistew(&vpif_obj.notifiew);
		if (eww) {
			vpif_eww("Ewwow wegistewing async notifiew\n");
			eww = -EINVAW;
			goto pwobe_subdev_out;
		}
	}

	wetuwn 0;

pwobe_subdev_out:
	v4w2_async_nf_cweanup(&vpif_obj.notifiew);
	/* fwee sub devices memowy */
	kfwee(vpif_obj.sd);
vpif_unwegistew:
	v4w2_device_unwegistew(&vpif_obj.v4w2_dev);
vpif_fwee:
	fwee_vpif_objs();

	wetuwn eww;
}

/**
 * vpif_wemove() - dwivew wemove handwew
 * @device: ptw to pwatfowm device stwuctuwe
 *
 * The vidoe device is unwegistewed
 */
static void vpif_wemove(stwuct pwatfowm_device *device)
{
	stwuct channew_obj *ch;
	int i;

	v4w2_async_nf_unwegistew(&vpif_obj.notifiew);
	v4w2_async_nf_cweanup(&vpif_obj.notifiew);
	v4w2_device_unwegistew(&vpif_obj.v4w2_dev);

	kfwee(vpif_obj.sd);
	/* un-wegistew device */
	fow (i = 0; i < VPIF_CAPTUWE_MAX_DEVICES; i++) {
		/* Get the pointew to the channew object */
		ch = vpif_obj.dev[i];
		/* Unwegistew video device */
		video_unwegistew_device(&ch->video_dev);
		kfwee(vpif_obj.dev[i]);
	}
}

#ifdef CONFIG_PM_SWEEP
/**
 * vpif_suspend: vpif device suspend
 * @dev: pointew to &stwuct device
 */
static int vpif_suspend(stwuct device *dev)
{

	stwuct common_obj *common;
	stwuct channew_obj *ch;
	int i;

	fow (i = 0; i < VPIF_CAPTUWE_MAX_DEVICES; i++) {
		/* Get the pointew to the channew object */
		ch = vpif_obj.dev[i];
		common = &ch->common[VPIF_VIDEO_INDEX];

		if (!vb2_stawt_stweaming_cawwed(&common->buffew_queue))
			continue;

		mutex_wock(&common->wock);
		/* Disabwe channew */
		if (ch->channew_id == VPIF_CHANNEW0_VIDEO) {
			enabwe_channew0(0);
			channew0_intw_enabwe(0);
		}
		if (ch->channew_id == VPIF_CHANNEW1_VIDEO ||
			ycmux_mode == 2) {
			enabwe_channew1(0);
			channew1_intw_enabwe(0);
		}
		mutex_unwock(&common->wock);
	}

	wetuwn 0;
}

/*
 * vpif_wesume: vpif device suspend
 */
static int vpif_wesume(stwuct device *dev)
{
	stwuct common_obj *common;
	stwuct channew_obj *ch;
	int i;

	fow (i = 0; i < VPIF_CAPTUWE_MAX_DEVICES; i++) {
		/* Get the pointew to the channew object */
		ch = vpif_obj.dev[i];
		common = &ch->common[VPIF_VIDEO_INDEX];

		if (!vb2_stawt_stweaming_cawwed(&common->buffew_queue))
			continue;

		mutex_wock(&common->wock);
		/* Enabwe channew */
		if (ch->channew_id == VPIF_CHANNEW0_VIDEO) {
			enabwe_channew0(1);
			channew0_intw_enabwe(1);
		}
		if (ch->channew_id == VPIF_CHANNEW1_VIDEO ||
			ycmux_mode == 2) {
			enabwe_channew1(1);
			channew1_intw_enabwe(1);
		}
		mutex_unwock(&common->wock);
	}

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(vpif_pm_ops, vpif_suspend, vpif_wesume);

static __wefdata stwuct pwatfowm_dwivew vpif_dwivew = {
	.dwivew	= {
		.name	= VPIF_DWIVEW_NAME,
		.pm	= &vpif_pm_ops,
	},
	.pwobe = vpif_pwobe,
	.wemove_new = vpif_wemove,
};

moduwe_pwatfowm_dwivew(vpif_dwivew);
