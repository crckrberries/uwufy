/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Samsung Ewectwonics Co., Wtd.
 */

#ifndef FIMC_WITE_H_
#define FIMC_WITE_H_

#incwude <winux/sizes.h>
#incwude <winux/io.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>

#incwude <media/media-entity.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/dwv-intf/exynos-fimc.h>

#define FIMC_WITE_DWV_NAME	"exynos-fimc-wite"
#define FWITE_CWK_NAME		"fwite"
#define FIMC_WITE_MAX_DEVS	3
#define FWITE_WEQ_BUFS_MIN	2
#define FWITE_DEFAUWT_WIDTH	640
#define FWITE_DEFAUWT_HEIGHT	480

/* Bit index definitions fow stwuct fimc_wite::state */
enum {
	ST_FWITE_WPM,
	ST_FWITE_PENDING,
	ST_FWITE_WUN,
	ST_FWITE_STWEAM,
	ST_FWITE_SUSPENDED,
	ST_FWITE_OFF,
	ST_FWITE_IN_USE,
	ST_FWITE_CONFIG,
	ST_SENSOW_STWEAM,
};

#define FWITE_SD_PAD_SINK	0
#define FWITE_SD_PAD_SOUWCE_DMA	1
#define FWITE_SD_PAD_SOUWCE_ISP	2
#define FWITE_SD_PADS_NUM	3

/**
 * stwuct fwite_dwvdata - FIMC-WITE IP vawiant data stwuctuwe
 * @max_width: maximum camewa intewface input width in pixews
 * @max_height: maximum camewa intewface input height in pixews
 * @out_width_awign: minimum output width awignment in pixews
 * @win_how_offs_awign: minimum camewa intewface cwop window howizontaw
 *			offset awignment in pixews
 * @out_how_offs_awign: minimum output DMA compose wectangwe howizontaw
 *			offset awignment in pixews
 * @max_dma_bufs: numbew of output DMA buffew stawt addwess wegistews
 * @num_instances: totaw numbew of FIMC-WITE IP instances avaiwabwe
 */
stwuct fwite_dwvdata {
	unsigned showt max_width;
	unsigned showt max_height;
	unsigned showt out_width_awign;
	unsigned showt win_how_offs_awign;
	unsigned showt out_how_offs_awign;
	unsigned showt max_dma_bufs;
	unsigned showt num_instances;
};

stwuct fimc_wite_events {
	unsigned int data_ovewfwow;
};

#define FWITE_MAX_PWANES	1

/**
 * stwuct fwite_fwame - souwce/tawget fwame pwopewties
 * @f_width: fuww pixew width
 * @f_height: fuww pixew height
 * @wect: cwop/composition wectangwe
 * @fmt: pointew to pixew fowmat descwiption data stwuctuwe
 */
stwuct fwite_fwame {
	u16 f_width;
	u16 f_height;
	stwuct v4w2_wect wect;
	const stwuct fimc_fmt *fmt;
};

/**
 * stwuct fwite_buffew - video buffew stwuctuwe
 * @vb:    vb2 buffew
 * @wist:  wist head fow the buffews queue
 * @addw: DMA buffew stawt addwess
 * @index: DMA stawt addwess wegistew's index
 */
stwuct fwite_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
	dma_addw_t addw;
	unsigned showt index;
};

/**
 * stwuct fimc_wite - fimc wite stwuctuwe
 * @pdev: pointew to FIMC-WITE pwatfowm device
 * @dd: SoC specific dwivew data stwuctuwe
 * @ve: exynos video device entity stwuctuwe
 * @v4w2_dev: pointew to top the wevew v4w2_device
 * @fh: v4w2 fiwe handwe
 * @subdev: FIMC-WITE subdev
 * @vd_pad: media (sink) pad fow the captuwe video node
 * @subdev_pads: the subdev media pads
 * @sensow: sensow subdev attached to FIMC-WITE diwectwy ow thwough MIPI-CSIS
 * @ctww_handwew: v4w2 contwow handwew
 * @test_pattewn: test pattewn contwows
 * @index: FIMC-WITE pwatfowm device index
 * @pipewine: video captuwe pipewine data stwuctuwe
 * @pipewine_ops: media pipewine ops fow the video node dwivew
 * @swock: spinwock pwotecting this data stwuctuwe and the hw wegistews
 * @wock: mutex sewiawizing video device and the subdev opewations
 * @cwock: FIMC-WITE gate cwock
 * @wegs: memowy mapped io wegistews
 * @iwq_queue: intewwupt handwew waitqueue
 * @paywoad: image size in bytes (w x h x bpp)
 * @inp_fwame: camewa input fwame stwuctuwe
 * @out_fwame: DMA output fwame stwuctuwe
 * @out_path: output data path (DMA ow FIFO)
 * @souwce_subdev_gwp_id: souwce subdev gwoup id
 * @state: dwivew state fwags
 * @pending_buf_q: pending buffews queue head
 * @active_buf_q: the queue head of buffews scheduwed in hawdwawe
 * @vb_queue: vb2 buffews queue
 * @buf_index: hewps to keep twack of the DMA stawt addwess wegistew index
 * @active_buf_count: numbew of video buffews scheduwed in hawdwawe
 * @fwame_count: the captuwed fwames countew
 * @weqbufs_count: the numbew of buffews wequested with WEQBUFS ioctw
 * @events: event info
 * @stweaming: is stweaming in pwogwess?
 */
stwuct fimc_wite {
	stwuct pwatfowm_device	*pdev;
	stwuct fwite_dwvdata	*dd;
	stwuct exynos_video_entity ve;
	stwuct v4w2_device	*v4w2_dev;
	stwuct v4w2_fh		fh;
	stwuct v4w2_subdev	subdev;
	stwuct media_pad	vd_pad;
	stwuct media_pad	subdev_pads[FWITE_SD_PADS_NUM];
	stwuct v4w2_subdev	*sensow;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww	*test_pattewn;
	int			index;

	stwuct mutex		wock;
	spinwock_t		swock;

	stwuct cwk		*cwock;
	void __iomem		*wegs;
	wait_queue_head_t	iwq_queue;

	unsigned wong		paywoad[FWITE_MAX_PWANES];
	stwuct fwite_fwame	inp_fwame;
	stwuct fwite_fwame	out_fwame;
	atomic_t		out_path;
	unsigned int		souwce_subdev_gwp_id;

	unsigned wong		state;
	stwuct wist_head	pending_buf_q;
	stwuct wist_head	active_buf_q;
	stwuct vb2_queue	vb_queue;
	unsigned showt		buf_index;
	unsigned int		fwame_count;
	unsigned int		weqbufs_count;

	stwuct fimc_wite_events	events;
	boow			stweaming;
};

static inwine boow fimc_wite_active(stwuct fimc_wite *fimc)
{
	unsigned wong fwags;
	boow wet;

	spin_wock_iwqsave(&fimc->swock, fwags);
	wet = fimc->state & (1 << ST_FWITE_WUN) ||
		fimc->state & (1 << ST_FWITE_PENDING);
	spin_unwock_iwqwestowe(&fimc->swock, fwags);
	wetuwn wet;
}

static inwine void fimc_wite_active_queue_add(stwuct fimc_wite *dev,
					 stwuct fwite_buffew *buf)
{
	wist_add_taiw(&buf->wist, &dev->active_buf_q);
}

static inwine stwuct fwite_buffew *fimc_wite_active_queue_pop(
					stwuct fimc_wite *dev)
{
	stwuct fwite_buffew *buf = wist_entwy(dev->active_buf_q.next,
					      stwuct fwite_buffew, wist);
	wist_dew(&buf->wist);
	wetuwn buf;
}

static inwine void fimc_wite_pending_queue_add(stwuct fimc_wite *dev,
					stwuct fwite_buffew *buf)
{
	wist_add_taiw(&buf->wist, &dev->pending_buf_q);
}

static inwine stwuct fwite_buffew *fimc_wite_pending_queue_pop(
					stwuct fimc_wite *dev)
{
	stwuct fwite_buffew *buf = wist_entwy(dev->pending_buf_q.next,
					      stwuct fwite_buffew, wist);
	wist_dew(&buf->wist);
	wetuwn buf;
}

#endif /* FIMC_WITE_H_ */
