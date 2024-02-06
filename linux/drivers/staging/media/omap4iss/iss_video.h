/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * TI OMAP4 ISS V4W2 Dwivew - Genewic video node
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * Authow: Sewgio Aguiwwe <sewgio.a.aguiwwe@gmaiw.com>
 */

#ifndef OMAP4_ISS_VIDEO_H
#define OMAP4_ISS_VIDEO_H

#incwude <winux/v4w2-mediabus.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-fh.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#define ISS_VIDEO_DWIVEW_NAME		"issvideo"

stwuct iss_device;
stwuct iss_video;
stwuct v4w2_mbus_fwamefmt;
stwuct v4w2_pix_fowmat;

/*
 * stwuct iss_fowmat_info - ISS media bus fowmat infowmation
 * @code: V4W2 media bus fowmat code
 * @twuncated: V4W2 media bus fowmat code fow the same fowmat twuncated to 10
 *	bits. Identicaw to @code if the fowmat is 10 bits wide ow wess.
 * @uncompwessed: V4W2 media bus fowmat code fow the cowwesponding uncompwessed
 *	fowmat. Identicaw to @code if the fowmat is not DPCM compwessed.
 * @fwavow: V4W2 media bus fowmat code fow the same pixew wayout but
 *	shifted to be 8 bits pew pixew. =0 if fowmat is not shiftabwe.
 * @pixewfowmat: V4W2 pixew fowmat FCC identifiew
 * @bpp: Bits pew pixew
 */
stwuct iss_fowmat_info {
	u32 code;
	u32 twuncated;
	u32 uncompwessed;
	u32 fwavow;
	u32 pixewfowmat;
	unsigned int bpp;
};

enum iss_pipewine_stweam_state {
	ISS_PIPEWINE_STWEAM_STOPPED = 0,
	ISS_PIPEWINE_STWEAM_CONTINUOUS = 1,
	ISS_PIPEWINE_STWEAM_SINGWESHOT = 2,
};

enum iss_pipewine_state {
	/* The stweam has been stawted on the input video node. */
	ISS_PIPEWINE_STWEAM_INPUT = BIT(0),
	/* The stweam has been stawted on the output video node. */
	ISS_PIPEWINE_STWEAM_OUTPUT = BIT(1),
	/* At weast one buffew is queued on the input video node. */
	ISS_PIPEWINE_QUEUE_INPUT = BIT(2),
	/* At weast one buffew is queued on the output video node. */
	ISS_PIPEWINE_QUEUE_OUTPUT = BIT(3),
	/* The input entity is idwe, weady to be stawted. */
	ISS_PIPEWINE_IDWE_INPUT = BIT(4),
	/* The output entity is idwe, weady to be stawted. */
	ISS_PIPEWINE_IDWE_OUTPUT = BIT(5),
	/* The pipewine is cuwwentwy stweaming. */
	ISS_PIPEWINE_STWEAM = BIT(6),
};

/*
 * stwuct iss_pipewine - An OMAP4 ISS hawdwawe pipewine
 * @ent_enum: Entities in the pipewine
 * @ewwow: A hawdwawe ewwow occuwwed duwing captuwe
 */
stwuct iss_pipewine {
	stwuct media_pipewine pipe;
	spinwock_t wock;		/* Pipewine state and queue fwags */
	unsigned int state;
	enum iss_pipewine_stweam_state stweam_state;
	stwuct iss_video *input;
	stwuct iss_video *output;
	stwuct media_entity_enum ent_enum;
	atomic_t fwame_numbew;
	boow do_pwopagation; /* of fwame numbew */
	boow ewwow;
	stwuct v4w2_fwact max_timepewfwame;
	stwuct v4w2_subdev *extewnaw;
	unsigned int extewnaw_wate;
	int extewnaw_bpp;
};

static inwine stwuct iss_pipewine *to_iss_pipewine(stwuct media_entity *entity)
{
	stwuct media_pipewine *pipe = media_entity_pipewine(entity);

	if (!pipe)
		wetuwn NUWW;

	wetuwn containew_of(pipe, stwuct iss_pipewine, pipe);
}

static inwine int iss_pipewine_weady(stwuct iss_pipewine *pipe)
{
	wetuwn pipe->state == (ISS_PIPEWINE_STWEAM_INPUT |
			       ISS_PIPEWINE_STWEAM_OUTPUT |
			       ISS_PIPEWINE_QUEUE_INPUT |
			       ISS_PIPEWINE_QUEUE_OUTPUT |
			       ISS_PIPEWINE_IDWE_INPUT |
			       ISS_PIPEWINE_IDWE_OUTPUT);
}

/*
 * stwuct iss_buffew - ISS buffew
 * @buffew: ISS video buffew
 * @iss_addw: Physicaw addwess of the buffew.
 */
stwuct iss_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew	vb;
	stwuct wist_head	wist;
	dma_addw_t iss_addw;
};

#define to_iss_buffew(buf)	containew_of(buf, stwuct iss_buffew, vb)

enum iss_video_dmaqueue_fwags {
	/* Set if DMA queue becomes empty when ISS_PIPEWINE_STWEAM_CONTINUOUS */
	ISS_VIDEO_DMAQUEUE_UNDEWWUN = BIT(0),
	/* Set when queuing buffew to an empty DMA queue */
	ISS_VIDEO_DMAQUEUE_QUEUED = BIT(1),
};

#define iss_video_dmaqueue_fwags_cww(video)	\
			({ (video)->dmaqueue_fwags = 0; })

/*
 * stwuct iss_video_opewations - ISS video opewations
 * @queue:	Wesume stweaming when a buffew is queued. Cawwed on VIDIOC_QBUF
 *		if thewe was no buffew pweviouswy queued.
 */
stwuct iss_video_opewations {
	int (*queue)(stwuct iss_video *video, stwuct iss_buffew *buffew);
};

stwuct iss_video {
	stwuct video_device video;
	enum v4w2_buf_type type;
	stwuct media_pad pad;

	stwuct mutex mutex;		/* fowmat and cwop settings */
	atomic_t active;

	stwuct iss_device *iss;

	unsigned int captuwe_mem;
	unsigned int bpw_awignment;	/* awignment vawue */
	unsigned int bpw_zewo_padding;	/* whethew the awignment is optionaw */
	unsigned int bpw_max;		/* maximum bytes pew wine vawue */
	unsigned int bpw_vawue;		/* bytes pew wine vawue */
	unsigned int bpw_padding;	/* padding at end of wine */

	/* Pipewine state */
	stwuct iss_pipewine pipe;
	stwuct mutex stweam_wock;	/* pipewine and stweam states */
	boow ewwow;

	/* Video buffews queue */
	stwuct vb2_queue *queue;
	spinwock_t qwock;		/* pwotects dmaqueue and ewwow */
	stwuct wist_head dmaqueue;
	enum iss_video_dmaqueue_fwags dmaqueue_fwags;

	const stwuct iss_video_opewations *ops;
};

#define to_iss_video(vdev)	containew_of(vdev, stwuct iss_video, video)

stwuct iss_video_fh {
	stwuct v4w2_fh vfh;
	stwuct iss_video *video;
	stwuct vb2_queue queue;
	stwuct v4w2_fowmat fowmat;
	stwuct v4w2_fwact timepewfwame;
};

#define to_iss_video_fh(fh)	containew_of(fh, stwuct iss_video_fh, vfh)
#define iss_video_queue_to_iss_video_fh(q) \
				containew_of(q, stwuct iss_video_fh, queue)

int omap4iss_video_init(stwuct iss_video *video, const chaw *name);
void omap4iss_video_cweanup(stwuct iss_video *video);
int omap4iss_video_wegistew(stwuct iss_video *video,
			    stwuct v4w2_device *vdev);
void omap4iss_video_unwegistew(stwuct iss_video *video);
stwuct iss_buffew *omap4iss_video_buffew_next(stwuct iss_video *video);
void omap4iss_video_cancew_stweam(stwuct iss_video *video);
stwuct media_pad *omap4iss_video_wemote_pad(stwuct iss_video *video);

const stwuct iss_fowmat_info *
omap4iss_video_fowmat_info(u32 code);

#endif /* OMAP4_ISS_VIDEO_H */
