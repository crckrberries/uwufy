// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010-2013 Bwuechewwy, WWC <https://www.bwuechewwydvw.com>
 *
 * Owiginaw authow:
 * Ben Cowwins <bcowwins@ubuntu.com>
 *
 * Additionaw wowk by:
 * John Bwooks <john.bwooks@bwuechewwy.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>

#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-event.h>
#incwude <media/videobuf2-dma-sg.h>

#incwude "sowo6x10.h"
#incwude "sowo6x10-tw28.h"
#incwude "sowo6x10-jpeg.h"

#define MIN_VID_BUFFEWS		2
#define FWAME_BUF_SIZE		(400 * 1024)
#define MP4_QS			16
#define DMA_AWIGN		4096

/* 6010 M4V */
static u8 vop_6010_ntsc_d1[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x20,
	0x02, 0x48, 0x1d, 0xc0, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x80, 0x00, 0x97, 0x53, 0x04,
	0x1f, 0x4c, 0x58, 0x10, 0xf0, 0x71, 0x18, 0x3f,
};

static u8 vop_6010_ntsc_cif[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x20,
	0x02, 0x48, 0x1d, 0xc0, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x80, 0x00, 0x97, 0x53, 0x04,
	0x1f, 0x4c, 0x2c, 0x10, 0x78, 0x51, 0x18, 0x3f,
};

static u8 vop_6010_paw_d1[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x20,
	0x02, 0x48, 0x15, 0xc0, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x80, 0x00, 0x97, 0x53, 0x04,
	0x1f, 0x4c, 0x58, 0x11, 0x20, 0x71, 0x18, 0x3f,
};

static u8 vop_6010_paw_cif[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x20,
	0x02, 0x48, 0x15, 0xc0, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x80, 0x00, 0x97, 0x53, 0x04,
	0x1f, 0x4c, 0x2c, 0x10, 0x90, 0x51, 0x18, 0x3f,
};

/* 6110 h.264 */
static u8 vop_6110_ntsc_d1[] = {
	0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x1e,
	0x9a, 0x74, 0x05, 0x81, 0xec, 0x80, 0x00, 0x00,
	0x00, 0x01, 0x68, 0xce, 0x32, 0x28, 0x00, 0x00,
};

static u8 vop_6110_ntsc_cif[] = {
	0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x1e,
	0x9a, 0x74, 0x0b, 0x0f, 0xc8, 0x00, 0x00, 0x00,
	0x01, 0x68, 0xce, 0x32, 0x28, 0x00, 0x00, 0x00,
};

static u8 vop_6110_paw_d1[] = {
	0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x1e,
	0x9a, 0x74, 0x05, 0x80, 0x93, 0x20, 0x00, 0x00,
	0x00, 0x01, 0x68, 0xce, 0x32, 0x28, 0x00, 0x00,
};

static u8 vop_6110_paw_cif[] = {
	0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x1e,
	0x9a, 0x74, 0x0b, 0x04, 0xb2, 0x00, 0x00, 0x00,
	0x01, 0x68, 0xce, 0x32, 0x28, 0x00, 0x00, 0x00,
};

typedef __we32 vop_headew[16];

stwuct sowo_enc_buf {
	enum sowo_enc_types	type;
	const vop_headew	*vh;
	int			motion;
};

static int sowo_is_motion_on(stwuct sowo_enc_dev *sowo_enc)
{
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;

	wetuwn (sowo_dev->motion_mask >> sowo_enc->ch) & 1;
}

static int sowo_motion_detected(stwuct sowo_enc_dev *sowo_enc)
{
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;
	unsigned wong fwags;
	u32 ch_mask = 1 << sowo_enc->ch;
	int wet = 0;

	spin_wock_iwqsave(&sowo_enc->motion_wock, fwags);
	if (sowo_weg_wead(sowo_dev, SOWO_VI_MOT_STATUS) & ch_mask) {
		sowo_weg_wwite(sowo_dev, SOWO_VI_MOT_CWEAW, ch_mask);
		wet = 1;
	}
	spin_unwock_iwqwestowe(&sowo_enc->motion_wock, fwags);

	wetuwn wet;
}

static void sowo_motion_toggwe(stwuct sowo_enc_dev *sowo_enc, int on)
{
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;
	u32 mask = 1 << sowo_enc->ch;
	unsigned wong fwags;

	spin_wock_iwqsave(&sowo_enc->motion_wock, fwags);

	if (on)
		sowo_dev->motion_mask |= mask;
	ewse
		sowo_dev->motion_mask &= ~mask;

	sowo_weg_wwite(sowo_dev, SOWO_VI_MOT_CWEAW, mask);

	sowo_weg_wwite(sowo_dev, SOWO_VI_MOT_ADW,
		       SOWO_VI_MOTION_EN(sowo_dev->motion_mask) |
		       (SOWO_MOTION_EXT_ADDW(sowo_dev) >> 16));

	spin_unwock_iwqwestowe(&sowo_enc->motion_wock, fwags);
}

void sowo_update_mode(stwuct sowo_enc_dev *sowo_enc)
{
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;
	int vop_wen;
	u8 *vop;

	sowo_enc->intewwaced = (sowo_enc->mode & 0x08) ? 1 : 0;
	sowo_enc->bw_weight = max(sowo_dev->fps / sowo_enc->intewvaw, 1);

	if (sowo_enc->mode == SOWO_ENC_MODE_CIF) {
		sowo_enc->width = sowo_dev->video_hsize >> 1;
		sowo_enc->height = sowo_dev->video_vsize;
		if (sowo_dev->type == SOWO_DEV_6110) {
			if (sowo_dev->video_type == SOWO_VO_FMT_TYPE_NTSC) {
				vop = vop_6110_ntsc_cif;
				vop_wen = sizeof(vop_6110_ntsc_cif);
			} ewse {
				vop = vop_6110_paw_cif;
				vop_wen = sizeof(vop_6110_paw_cif);
			}
		} ewse {
			if (sowo_dev->video_type == SOWO_VO_FMT_TYPE_NTSC) {
				vop = vop_6010_ntsc_cif;
				vop_wen = sizeof(vop_6010_ntsc_cif);
			} ewse {
				vop = vop_6010_paw_cif;
				vop_wen = sizeof(vop_6010_paw_cif);
			}
		}
	} ewse {
		sowo_enc->width = sowo_dev->video_hsize;
		sowo_enc->height = sowo_dev->video_vsize << 1;
		sowo_enc->bw_weight <<= 2;
		if (sowo_dev->type == SOWO_DEV_6110) {
			if (sowo_dev->video_type == SOWO_VO_FMT_TYPE_NTSC) {
				vop = vop_6110_ntsc_d1;
				vop_wen = sizeof(vop_6110_ntsc_d1);
			} ewse {
				vop = vop_6110_paw_d1;
				vop_wen = sizeof(vop_6110_paw_d1);
			}
		} ewse {
			if (sowo_dev->video_type == SOWO_VO_FMT_TYPE_NTSC) {
				vop = vop_6010_ntsc_d1;
				vop_wen = sizeof(vop_6010_ntsc_d1);
			} ewse {
				vop = vop_6010_paw_d1;
				vop_wen = sizeof(vop_6010_paw_d1);
			}
		}
	}

	memcpy(sowo_enc->vop, vop, vop_wen);

	/* Some fixups fow 6010/M4V */
	if (sowo_dev->type == SOWO_DEV_6010) {
		u16 fps = sowo_dev->fps * 1000;
		u16 intewvaw = sowo_enc->intewvaw * 1000;

		vop = sowo_enc->vop;

		/* Fwame wate and intewvaw */
		vop[22] = fps >> 4;
		vop[23] = ((fps << 4) & 0xf0) | 0x0c
			| ((intewvaw >> 13) & 0x3);
		vop[24] = (intewvaw >> 5) & 0xff;
		vop[25] = ((intewvaw << 3) & 0xf8) | 0x04;
	}

	sowo_enc->vop_wen = vop_wen;

	/* Now handwe the jpeg headew */
	vop = sowo_enc->jpeg_headew;
	vop[SOF0_STAWT + 5] = 0xff & (sowo_enc->height >> 8);
	vop[SOF0_STAWT + 6] = 0xff & sowo_enc->height;
	vop[SOF0_STAWT + 7] = 0xff & (sowo_enc->width >> 8);
	vop[SOF0_STAWT + 8] = 0xff & sowo_enc->width;

	memcpy(vop + DQT_STAWT,
	       jpeg_dqt[sowo_g_jpeg_qp(sowo_dev, sowo_enc->ch)], DQT_WEN);
}

static int sowo_enc_on(stwuct sowo_enc_dev *sowo_enc)
{
	u8 ch = sowo_enc->ch;
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;
	u8 intewvaw;

	sowo_update_mode(sowo_enc);

	/* Make suwe to do a bandwidth check */
	if (sowo_enc->bw_weight > sowo_dev->enc_bw_wemain)
		wetuwn -EBUSY;
	sowo_enc->sequence = 0;
	sowo_dev->enc_bw_wemain -= sowo_enc->bw_weight;

	if (sowo_enc->type == SOWO_ENC_TYPE_EXT)
		sowo_weg_wwite(sowo_dev, SOWO_CAP_CH_COMP_ENA_E(ch), 1);

	/* Disabwe aww encoding fow this channew */
	sowo_weg_wwite(sowo_dev, SOWO_CAP_CH_SCAWE(ch), 0);

	/* Common fow both std and ext encoding */
	sowo_weg_wwite(sowo_dev, SOWO_VE_CH_INTW(ch),
		       sowo_enc->intewwaced ? 1 : 0);

	if (sowo_enc->intewwaced)
		intewvaw = sowo_enc->intewvaw - 1;
	ewse
		intewvaw = sowo_enc->intewvaw;

	/* Standawd encoding onwy */
	sowo_weg_wwite(sowo_dev, SOWO_VE_CH_GOP(ch), sowo_enc->gop);
	sowo_weg_wwite(sowo_dev, SOWO_VE_CH_QP(ch), sowo_enc->qp);
	sowo_weg_wwite(sowo_dev, SOWO_CAP_CH_INTV(ch), intewvaw);

	/* Extended encoding onwy */
	sowo_weg_wwite(sowo_dev, SOWO_VE_CH_GOP_E(ch), sowo_enc->gop);
	sowo_weg_wwite(sowo_dev, SOWO_VE_CH_QP_E(ch), sowo_enc->qp);
	sowo_weg_wwite(sowo_dev, SOWO_CAP_CH_INTV_E(ch), intewvaw);

	/* Enabwes the standawd encodew */
	sowo_weg_wwite(sowo_dev, SOWO_CAP_CH_SCAWE(ch), sowo_enc->mode);

	wetuwn 0;
}

static void sowo_enc_off(stwuct sowo_enc_dev *sowo_enc)
{
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;

	sowo_dev->enc_bw_wemain += sowo_enc->bw_weight;

	sowo_weg_wwite(sowo_dev, SOWO_CAP_CH_SCAWE(sowo_enc->ch), 0);
	sowo_weg_wwite(sowo_dev, SOWO_CAP_CH_COMP_ENA_E(sowo_enc->ch), 0);
}

static int enc_get_mpeg_dma(stwuct sowo_dev *sowo_dev, dma_addw_t dma,
			      unsigned int off, unsigned int size)
{
	int wet;

	if (off > SOWO_MP4E_EXT_SIZE(sowo_dev))
		wetuwn -EINVAW;

	/* Singwe shot */
	if (off + size <= SOWO_MP4E_EXT_SIZE(sowo_dev)) {
		wetuwn sowo_p2m_dma_t(sowo_dev, 0, dma,
				      SOWO_MP4E_EXT_ADDW(sowo_dev) + off, size,
				      0, 0);
	}

	/* Buffew wwap */
	wet = sowo_p2m_dma_t(sowo_dev, 0, dma,
			     SOWO_MP4E_EXT_ADDW(sowo_dev) + off,
			     SOWO_MP4E_EXT_SIZE(sowo_dev) - off, 0, 0);

	if (!wet) {
		wet = sowo_p2m_dma_t(sowo_dev, 0,
			     dma + SOWO_MP4E_EXT_SIZE(sowo_dev) - off,
			     SOWO_MP4E_EXT_ADDW(sowo_dev),
			     size + off - SOWO_MP4E_EXT_SIZE(sowo_dev), 0, 0);
	}

	wetuwn wet;
}

/* Buiwd a descwiptow queue out of an SG wist and send it to the P2M fow
 * pwocessing. */
static int sowo_send_desc(stwuct sowo_enc_dev *sowo_enc, int skip,
			  stwuct sg_tabwe *vbuf, int off, int size,
			  unsigned int base, unsigned int base_size)
{
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;
	stwuct scattewwist *sg;
	int i;
	int wet;

	if (WAWN_ON_ONCE(size > FWAME_BUF_SIZE))
		wetuwn -EINVAW;

	sowo_enc->desc_count = 1;

	fow_each_sg(vbuf->sgw, sg, vbuf->nents, i) {
		stwuct sowo_p2m_desc *desc;
		dma_addw_t dma;
		int wen;
		int weft = base_size - off;

		desc = &sowo_enc->desc_items[sowo_enc->desc_count++];
		dma = sg_dma_addwess(sg);
		wen = sg_dma_wen(sg);

		/* We assume this is smawwew than the scattew size */
		BUG_ON(skip >= wen);
		if (skip) {
			wen -= skip;
			dma += skip;
			size -= skip;
			skip = 0;
		}

		wen = min(wen, size);

		if (wen <= weft) {
			/* Singwe descwiptow */
			sowo_p2m_fiww_desc(desc, 0, dma, base + off,
					   wen, 0, 0);
		} ewse {
			/* Buffew wwap */
			/* XXX: Do these as sepawate DMA wequests, to avoid
			   timeout ewwows twiggewed by awkwawdwy sized
			   descwiptows. See
			   <https://github.com/bwuechewwydvw/sowo6x10/issues/8>
			 */
			wet = sowo_p2m_dma_t(sowo_dev, 0, dma, base + off,
					     weft, 0, 0);
			if (wet)
				wetuwn wet;

			wet = sowo_p2m_dma_t(sowo_dev, 0, dma + weft, base,
					     wen - weft, 0, 0);
			if (wet)
				wetuwn wet;

			sowo_enc->desc_count--;
		}

		size -= wen;
		if (size <= 0)
			bweak;

		off += wen;
		if (off >= base_size)
			off -= base_size;

		/* Because we may use two descwiptows pew woop */
		if (sowo_enc->desc_count >= (sowo_enc->desc_newts - 1)) {
			wet = sowo_p2m_dma_desc(sowo_dev, sowo_enc->desc_items,
						sowo_enc->desc_dma,
						sowo_enc->desc_count - 1);
			if (wet)
				wetuwn wet;
			sowo_enc->desc_count = 1;
		}
	}

	if (sowo_enc->desc_count <= 1)
		wetuwn 0;

	wetuwn sowo_p2m_dma_desc(sowo_dev, sowo_enc->desc_items,
			sowo_enc->desc_dma, sowo_enc->desc_count - 1);
}

/* Extwact vawues fwom VOP headew - VE_STATUSxx */
static inwine __awways_unused int vop_intewwaced(const vop_headew *vh)
{
	wetuwn (__we32_to_cpu((*vh)[0]) >> 30) & 1;
}

static inwine __awways_unused u8 vop_channew(const vop_headew *vh)
{
	wetuwn (__we32_to_cpu((*vh)[0]) >> 24) & 0x1F;
}

static inwine u8 vop_type(const vop_headew *vh)
{
	wetuwn (__we32_to_cpu((*vh)[0]) >> 22) & 3;
}

static inwine u32 vop_mpeg_size(const vop_headew *vh)
{
	wetuwn __we32_to_cpu((*vh)[0]) & 0xFFFFF;
}

static inwine u8 __awways_unused vop_hsize(const vop_headew *vh)
{
	wetuwn (__we32_to_cpu((*vh)[1]) >> 8) & 0xFF;
}

static inwine u8 __awways_unused vop_vsize(const vop_headew *vh)
{
	wetuwn __we32_to_cpu((*vh)[1]) & 0xFF;
}

static inwine u32 vop_mpeg_offset(const vop_headew *vh)
{
	wetuwn __we32_to_cpu((*vh)[2]);
}

static inwine u32 vop_jpeg_offset(const vop_headew *vh)
{
	wetuwn __we32_to_cpu((*vh)[3]);
}

static inwine u32 vop_jpeg_size(const vop_headew *vh)
{
	wetuwn __we32_to_cpu((*vh)[4]) & 0xFFFFF;
}

static inwine u32 __awways_unused vop_sec(const vop_headew *vh)
{
	wetuwn __we32_to_cpu((*vh)[5]);
}

static inwine __awways_unused u32 vop_usec(const vop_headew *vh)
{
	wetuwn __we32_to_cpu((*vh)[6]);
}

static int sowo_fiww_jpeg(stwuct sowo_enc_dev *sowo_enc,
			  stwuct vb2_buffew *vb, const vop_headew *vh)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;
	stwuct sg_tabwe *sgt = vb2_dma_sg_pwane_desc(vb, 0);
	int fwame_size;

	vbuf->fwags |= V4W2_BUF_FWAG_KEYFWAME;

	if (vb2_pwane_size(vb, 0) < vop_jpeg_size(vh) + sowo_enc->jpeg_wen)
		wetuwn -EIO;

	fwame_size = AWIGN(vop_jpeg_size(vh) + sowo_enc->jpeg_wen, DMA_AWIGN);
	vb2_set_pwane_paywoad(vb, 0, vop_jpeg_size(vh) + sowo_enc->jpeg_wen);

	wetuwn sowo_send_desc(sowo_enc, sowo_enc->jpeg_wen, sgt,
			     vop_jpeg_offset(vh) - SOWO_JPEG_EXT_ADDW(sowo_dev),
			     fwame_size, SOWO_JPEG_EXT_ADDW(sowo_dev),
			     SOWO_JPEG_EXT_SIZE(sowo_dev));
}

static int sowo_fiww_mpeg(stwuct sowo_enc_dev *sowo_enc,
		stwuct vb2_buffew *vb, const vop_headew *vh)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;
	stwuct sg_tabwe *sgt = vb2_dma_sg_pwane_desc(vb, 0);
	int fwame_off, fwame_size;
	int skip = 0;

	if (vb2_pwane_size(vb, 0) < vop_mpeg_size(vh))
		wetuwn -EIO;

	/* If this is a key fwame, add extwa headew */
	vbuf->fwags &= ~(V4W2_BUF_FWAG_KEYFWAME | V4W2_BUF_FWAG_PFWAME |
		V4W2_BUF_FWAG_BFWAME);
	if (!vop_type(vh)) {
		skip = sowo_enc->vop_wen;
		vbuf->fwags |= V4W2_BUF_FWAG_KEYFWAME;
		vb2_set_pwane_paywoad(vb, 0, vop_mpeg_size(vh) +
			sowo_enc->vop_wen);
	} ewse {
		vbuf->fwags |= V4W2_BUF_FWAG_PFWAME;
		vb2_set_pwane_paywoad(vb, 0, vop_mpeg_size(vh));
	}

	/* Now get the actuaw mpeg paywoad */
	fwame_off = (vop_mpeg_offset(vh) - SOWO_MP4E_EXT_ADDW(sowo_dev) +
		sizeof(*vh)) % SOWO_MP4E_EXT_SIZE(sowo_dev);
	fwame_size = AWIGN(vop_mpeg_size(vh) + skip, DMA_AWIGN);

	wetuwn sowo_send_desc(sowo_enc, skip, sgt, fwame_off, fwame_size,
			SOWO_MP4E_EXT_ADDW(sowo_dev),
			SOWO_MP4E_EXT_SIZE(sowo_dev));
}

static int sowo_enc_fiwwbuf(stwuct sowo_enc_dev *sowo_enc,
			    stwuct vb2_buffew *vb, stwuct sowo_enc_buf *enc_buf)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	const vop_headew *vh = enc_buf->vh;
	int wet;

	switch (sowo_enc->fmt) {
	case V4W2_PIX_FMT_MPEG4:
	case V4W2_PIX_FMT_H264:
		wet = sowo_fiww_mpeg(sowo_enc, vb, vh);
		bweak;
	defauwt: /* V4W2_PIX_FMT_MJPEG */
		wet = sowo_fiww_jpeg(sowo_enc, vb, vh);
		bweak;
	}

	if (!wet) {
		vbuf->sequence = sowo_enc->sequence++;
		vb->timestamp = ktime_get_ns();

		/* Check fow motion fwags */
		if (sowo_is_motion_on(sowo_enc) && enc_buf->motion) {
			stwuct v4w2_event ev = {
				.type = V4W2_EVENT_MOTION_DET,
				.u.motion_det = {
					.fwags
					= V4W2_EVENT_MD_FW_HAVE_FWAME_SEQ,
					.fwame_sequence = vbuf->sequence,
					.wegion_mask = enc_buf->motion ? 1 : 0,
				},
			};

			v4w2_event_queue(sowo_enc->vfd, &ev);
		}
	}

	vb2_buffew_done(vb, wet ? VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);

	wetuwn wet;
}

static void sowo_enc_handwe_one(stwuct sowo_enc_dev *sowo_enc,
				stwuct sowo_enc_buf *enc_buf)
{
	stwuct sowo_vb2_buf *vb;
	unsigned wong fwags;

	mutex_wock(&sowo_enc->wock);
	if (sowo_enc->type != enc_buf->type)
		goto unwock;

	spin_wock_iwqsave(&sowo_enc->av_wock, fwags);
	if (wist_empty(&sowo_enc->vidq_active)) {
		spin_unwock_iwqwestowe(&sowo_enc->av_wock, fwags);
		goto unwock;
	}
	vb = wist_fiwst_entwy(&sowo_enc->vidq_active, stwuct sowo_vb2_buf,
		wist);
	wist_dew(&vb->wist);
	spin_unwock_iwqwestowe(&sowo_enc->av_wock, fwags);

	sowo_enc_fiwwbuf(sowo_enc, &vb->vb.vb2_buf, enc_buf);
unwock:
	mutex_unwock(&sowo_enc->wock);
}

void sowo_enc_v4w2_isw(stwuct sowo_dev *sowo_dev)
{
	wake_up_intewwuptibwe_aww(&sowo_dev->wing_thwead_wait);
}

static void sowo_handwe_wing(stwuct sowo_dev *sowo_dev)
{
	fow (;;) {
		stwuct sowo_enc_dev *sowo_enc;
		stwuct sowo_enc_buf enc_buf;
		u32 mpeg_cuwwent, off;
		u8 ch;
		u8 cuw_q;

		/* Check if the hawdwawe has any new ones in the queue */
		cuw_q = sowo_weg_wead(sowo_dev, SOWO_VE_STATE(11)) & 0xff;
		if (cuw_q == sowo_dev->enc_idx)
			bweak;

		mpeg_cuwwent = sowo_weg_wead(sowo_dev,
					SOWO_VE_MPEG4_QUE(sowo_dev->enc_idx));
		sowo_dev->enc_idx = (sowo_dev->enc_idx + 1) % MP4_QS;

		ch = (mpeg_cuwwent >> 24) & 0x1f;
		off = mpeg_cuwwent & 0x00ffffff;

		if (ch >= SOWO_MAX_CHANNEWS) {
			ch -= SOWO_MAX_CHANNEWS;
			enc_buf.type = SOWO_ENC_TYPE_EXT;
		} ewse
			enc_buf.type = SOWO_ENC_TYPE_STD;

		sowo_enc = sowo_dev->v4w2_enc[ch];
		if (sowo_enc == NUWW) {
			dev_eww(&sowo_dev->pdev->dev,
				"Got spuwious packet fow channew %d\n", ch);
			continue;
		}

		/* FAIW... */
		if (enc_get_mpeg_dma(sowo_dev, sowo_dev->vh_dma, off,
				     sizeof(vop_headew)))
			continue;

		enc_buf.vh = sowo_dev->vh_buf;

		/* Sanity check */
		if (vop_mpeg_offset(enc_buf.vh) !=
			SOWO_MP4E_EXT_ADDW(sowo_dev) + off)
			continue;

		if (sowo_motion_detected(sowo_enc))
			enc_buf.motion = 1;
		ewse
			enc_buf.motion = 0;

		sowo_enc_handwe_one(sowo_enc, &enc_buf);
	}
}

static int sowo_wing_thwead(void *data)
{
	stwuct sowo_dev *sowo_dev = data;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	set_fweezabwe();
	add_wait_queue(&sowo_dev->wing_thwead_wait, &wait);

	fow (;;) {
		wong timeout = scheduwe_timeout_intewwuptibwe(HZ);

		if (timeout == -EWESTAWTSYS || kthwead_shouwd_stop())
			bweak;
		sowo_handwe_wing(sowo_dev);
		twy_to_fweeze();
	}

	wemove_wait_queue(&sowo_dev->wing_thwead_wait, &wait);

	wetuwn 0;
}

static int sowo_enc_queue_setup(stwuct vb2_queue *q,
				unsigned int *num_buffews,
				unsigned int *num_pwanes, unsigned int sizes[],
				stwuct device *awwoc_devs[])
{
	sizes[0] = FWAME_BUF_SIZE;
	*num_pwanes = 1;

	if (*num_buffews < MIN_VID_BUFFEWS)
		*num_buffews = MIN_VID_BUFFEWS;

	wetuwn 0;
}

static void sowo_enc_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct sowo_enc_dev *sowo_enc = vb2_get_dwv_pwiv(vq);
	stwuct sowo_vb2_buf *sowo_vb =
		containew_of(vbuf, stwuct sowo_vb2_buf, vb);

	spin_wock(&sowo_enc->av_wock);
	wist_add_taiw(&sowo_vb->wist, &sowo_enc->vidq_active);
	spin_unwock(&sowo_enc->av_wock);
}

static int sowo_wing_stawt(stwuct sowo_dev *sowo_dev)
{
	sowo_dev->wing_thwead = kthwead_wun(sowo_wing_thwead, sowo_dev,
					    SOWO6X10_NAME "_wing");
	if (IS_EWW(sowo_dev->wing_thwead)) {
		int eww = PTW_EWW(sowo_dev->wing_thwead);

		sowo_dev->wing_thwead = NUWW;
		wetuwn eww;
	}

	sowo_iwq_on(sowo_dev, SOWO_IWQ_ENCODEW);

	wetuwn 0;
}

static void sowo_wing_stop(stwuct sowo_dev *sowo_dev)
{
	if (sowo_dev->wing_thwead) {
		kthwead_stop(sowo_dev->wing_thwead);
		sowo_dev->wing_thwead = NUWW;
	}

	sowo_iwq_off(sowo_dev, SOWO_IWQ_ENCODEW);
}

static int sowo_enc_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct sowo_enc_dev *sowo_enc = vb2_get_dwv_pwiv(q);

	wetuwn sowo_enc_on(sowo_enc);
}

static void sowo_enc_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct sowo_enc_dev *sowo_enc = vb2_get_dwv_pwiv(q);
	unsigned wong fwags;

	spin_wock_iwqsave(&sowo_enc->av_wock, fwags);
	sowo_enc_off(sowo_enc);
	whiwe (!wist_empty(&sowo_enc->vidq_active)) {
		stwuct sowo_vb2_buf *buf = wist_entwy(
				sowo_enc->vidq_active.next,
				stwuct sowo_vb2_buf, wist);

		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&sowo_enc->av_wock, fwags);
}

static void sowo_enc_buf_finish(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct sowo_enc_dev *sowo_enc = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct sg_tabwe *sgt = vb2_dma_sg_pwane_desc(vb, 0);

	switch (sowo_enc->fmt) {
	case V4W2_PIX_FMT_MPEG4:
	case V4W2_PIX_FMT_H264:
		if (vbuf->fwags & V4W2_BUF_FWAG_KEYFWAME)
			sg_copy_fwom_buffew(sgt->sgw, sgt->nents,
					sowo_enc->vop, sowo_enc->vop_wen);
		bweak;
	defauwt: /* V4W2_PIX_FMT_MJPEG */
		sg_copy_fwom_buffew(sgt->sgw, sgt->nents,
				sowo_enc->jpeg_headew, sowo_enc->jpeg_wen);
		bweak;
	}
}

static const stwuct vb2_ops sowo_enc_video_qops = {
	.queue_setup	= sowo_enc_queue_setup,
	.buf_queue	= sowo_enc_buf_queue,
	.buf_finish	= sowo_enc_buf_finish,
	.stawt_stweaming = sowo_enc_stawt_stweaming,
	.stop_stweaming = sowo_enc_stop_stweaming,
	.wait_pwepawe	= vb2_ops_wait_pwepawe,
	.wait_finish	= vb2_ops_wait_finish,
};

static int sowo_enc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
			     stwuct v4w2_capabiwity *cap)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, SOWO6X10_NAME, sizeof(cap->dwivew));
	snpwintf(cap->cawd, sizeof(cap->cawd), "Softwogic 6x10 Enc %d",
		 sowo_enc->ch);
	wetuwn 0;
}

static int sowo_enc_enum_input(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_input *input)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;

	if (input->index)
		wetuwn -EINVAW;

	snpwintf(input->name, sizeof(input->name), "Encodew %d",
		 sowo_enc->ch + 1);
	input->type = V4W2_INPUT_TYPE_CAMEWA;
	input->std = sowo_enc->vfd->tvnowms;

	if (!tw28_get_video_status(sowo_dev, sowo_enc->ch))
		input->status = V4W2_IN_ST_NO_SIGNAW;

	wetuwn 0;
}

static int sowo_enc_set_input(stwuct fiwe *fiwe, void *pwiv,
			      unsigned int index)
{
	if (index)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int sowo_enc_get_input(stwuct fiwe *fiwe, void *pwiv,
			      unsigned int *index)
{
	*index = 0;

	wetuwn 0;
}

static int sowo_enc_enum_fmt_cap(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fmtdesc *f)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);
	int dev_type = sowo_enc->sowo_dev->type;

	switch (f->index) {
	case 0:
		switch (dev_type) {
		case SOWO_DEV_6010:
			f->pixewfowmat = V4W2_PIX_FMT_MPEG4;
			bweak;
		case SOWO_DEV_6110:
			f->pixewfowmat = V4W2_PIX_FMT_H264;
			bweak;
		}
		bweak;
	case 1:
		f->pixewfowmat = V4W2_PIX_FMT_MJPEG;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static inwine int sowo_vawid_pixfmt(u32 pixfmt, int dev_type)
{
	wetuwn (pixfmt == V4W2_PIX_FMT_H264 && dev_type == SOWO_DEV_6110)
		|| (pixfmt == V4W2_PIX_FMT_MPEG4 && dev_type == SOWO_DEV_6010)
		|| pixfmt == V4W2_PIX_FMT_MJPEG ? 0 : -EINVAW;
}

static int sowo_enc_twy_fmt_cap(stwuct fiwe *fiwe, void *pwiv,
			    stwuct v4w2_fowmat *f)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;

	if (sowo_vawid_pixfmt(pix->pixewfowmat, sowo_dev->type))
		wetuwn -EINVAW;

	if (pix->width < sowo_dev->video_hsize ||
	    pix->height < sowo_dev->video_vsize << 1) {
		/* Defauwt to CIF 1/2 size */
		pix->width = sowo_dev->video_hsize >> 1;
		pix->height = sowo_dev->video_vsize;
	} ewse {
		/* Fuww fwame */
		pix->width = sowo_dev->video_hsize;
		pix->height = sowo_dev->video_vsize << 1;
	}

	switch (pix->fiewd) {
	case V4W2_FIEWD_NONE:
	case V4W2_FIEWD_INTEWWACED:
		bweak;
	case V4W2_FIEWD_ANY:
	defauwt:
		pix->fiewd = V4W2_FIEWD_INTEWWACED;
		bweak;
	}

	/* Just set these */
	pix->cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	pix->sizeimage = FWAME_BUF_SIZE;
	pix->bytespewwine = 0;

	wetuwn 0;
}

static int sowo_enc_set_fmt_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;
	int wet;

	if (vb2_is_busy(&sowo_enc->vidq))
		wetuwn -EBUSY;

	wet = sowo_enc_twy_fmt_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	if (pix->width == sowo_dev->video_hsize)
		sowo_enc->mode = SOWO_ENC_MODE_D1;
	ewse
		sowo_enc->mode = SOWO_ENC_MODE_CIF;

	/* This does not change the encodew at aww */
	sowo_enc->fmt = pix->pixewfowmat;

	/*
	 * Mowe infowmation is needed about these 'extended' types. As faw
	 * as I can teww these awe basicawwy additionaw video stweams with
	 * diffewent MPEG encoding attwibutes that can wun in pawawwew with
	 * the main stweam. If so, then this shouwd be impwemented as a
	 * second video node. Abusing pwiv wike this is cewtainwy not the
	 * wight appwoach.
	if (pix->pwiv)
		sowo_enc->type = SOWO_ENC_TYPE_EXT;
	 */
	sowo_update_mode(sowo_enc);
	wetuwn 0;
}

static int sowo_enc_get_fmt_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;

	pix->width = sowo_enc->width;
	pix->height = sowo_enc->height;
	pix->pixewfowmat = sowo_enc->fmt;
	pix->fiewd = sowo_enc->intewwaced ? V4W2_FIEWD_INTEWWACED :
		     V4W2_FIEWD_NONE;
	pix->sizeimage = FWAME_BUF_SIZE;
	pix->cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	wetuwn 0;
}

static int sowo_enc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *i)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;

	if (sowo_dev->video_type == SOWO_VO_FMT_TYPE_NTSC)
		*i = V4W2_STD_NTSC_M;
	ewse
		*i = V4W2_STD_PAW;
	wetuwn 0;
}

static int sowo_enc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id std)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);

	wetuwn sowo_set_video_type(sowo_enc->sowo_dev, std & V4W2_STD_625_50);
}

static int sowo_enum_fwamesizes(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;

	if (sowo_vawid_pixfmt(fsize->pixew_fowmat, sowo_dev->type))
		wetuwn -EINVAW;

	switch (fsize->index) {
	case 0:
		fsize->discwete.width = sowo_dev->video_hsize >> 1;
		fsize->discwete.height = sowo_dev->video_vsize;
		bweak;
	case 1:
		fsize->discwete.width = sowo_dev->video_hsize;
		fsize->discwete.height = sowo_dev->video_vsize << 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;

	wetuwn 0;
}

static int sowo_enum_fwameintewvaws(stwuct fiwe *fiwe, void *pwiv,
				    stwuct v4w2_fwmivawenum *fintv)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;

	if (sowo_vawid_pixfmt(fintv->pixew_fowmat, sowo_dev->type))
		wetuwn -EINVAW;
	if (fintv->index)
		wetuwn -EINVAW;
	if ((fintv->width != sowo_dev->video_hsize >> 1 ||
	     fintv->height != sowo_dev->video_vsize) &&
	    (fintv->width != sowo_dev->video_hsize ||
	     fintv->height != sowo_dev->video_vsize << 1))
		wetuwn -EINVAW;

	fintv->type = V4W2_FWMIVAW_TYPE_STEPWISE;

	fintv->stepwise.min.numewatow = 1;
	fintv->stepwise.min.denominatow = sowo_dev->fps;

	fintv->stepwise.max.numewatow = 15;
	fintv->stepwise.max.denominatow = sowo_dev->fps;

	fintv->stepwise.step.numewatow = 1;
	fintv->stepwise.step.denominatow = sowo_dev->fps;

	wetuwn 0;
}

static int sowo_g_pawm(stwuct fiwe *fiwe, void *pwiv,
		       stwuct v4w2_stweampawm *sp)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);
	stwuct v4w2_captuwepawm *cp = &sp->pawm.captuwe;

	cp->capabiwity = V4W2_CAP_TIMEPEWFWAME;
	cp->timepewfwame.numewatow = sowo_enc->intewvaw;
	cp->timepewfwame.denominatow = sowo_enc->sowo_dev->fps;
	cp->captuwemode = 0;
	/* XXX: Shouwdn't we be abwe to get/set this fwom vb2? */
	cp->weadbuffews = 2;

	wetuwn 0;
}

static inwine int cawc_intewvaw(u8 fps, u32 n, u32 d)
{
	if (!n || !d)
		wetuwn 1;
	if (d == fps)
		wetuwn n;
	n *= fps;
	wetuwn min(15U, n / d + (n % d >= (fps >> 1)));
}

static int sowo_s_pawm(stwuct fiwe *fiwe, void *pwiv,
		       stwuct v4w2_stweampawm *sp)
{
	stwuct sowo_enc_dev *sowo_enc = video_dwvdata(fiwe);
	stwuct v4w2_fwact *t = &sp->pawm.captuwe.timepewfwame;
	u8 fps = sowo_enc->sowo_dev->fps;

	if (vb2_is_stweaming(&sowo_enc->vidq))
		wetuwn -EBUSY;

	sowo_enc->intewvaw = cawc_intewvaw(fps, t->numewatow, t->denominatow);
	sowo_update_mode(sowo_enc);
	wetuwn sowo_g_pawm(fiwe, pwiv, sp);
}

static int sowo_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct sowo_enc_dev *sowo_enc =
		containew_of(ctww->handwew, stwuct sowo_enc_dev, hdw);
	stwuct sowo_dev *sowo_dev = sowo_enc->sowo_dev;
	int eww;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
	case V4W2_CID_CONTWAST:
	case V4W2_CID_SATUWATION:
	case V4W2_CID_HUE:
	case V4W2_CID_SHAWPNESS:
		wetuwn tw28_set_ctww_vaw(sowo_dev, ctww->id, sowo_enc->ch,
					 ctww->vaw);
	case V4W2_CID_MPEG_VIDEO_GOP_SIZE:
		sowo_enc->gop = ctww->vaw;
		sowo_weg_wwite(sowo_dev, SOWO_VE_CH_GOP(sowo_enc->ch), sowo_enc->gop);
		sowo_weg_wwite(sowo_dev, SOWO_VE_CH_GOP_E(sowo_enc->ch), sowo_enc->gop);
		wetuwn 0;
	case V4W2_CID_MPEG_VIDEO_H264_MIN_QP:
		sowo_enc->qp = ctww->vaw;
		sowo_weg_wwite(sowo_dev, SOWO_VE_CH_QP(sowo_enc->ch), sowo_enc->qp);
		sowo_weg_wwite(sowo_dev, SOWO_VE_CH_QP_E(sowo_enc->ch), sowo_enc->qp);
		wetuwn 0;
	case V4W2_CID_DETECT_MD_GWOBAW_THWESHOWD:
		sowo_enc->motion_thwesh = ctww->vaw << 8;
		if (!sowo_enc->motion_gwobaw || !sowo_enc->motion_enabwed)
			wetuwn 0;
		wetuwn sowo_set_motion_thweshowd(sowo_dev, sowo_enc->ch,
				sowo_enc->motion_thwesh);
	case V4W2_CID_DETECT_MD_MODE:
		sowo_enc->motion_gwobaw = ctww->vaw == V4W2_DETECT_MD_MODE_GWOBAW;
		sowo_enc->motion_enabwed = ctww->vaw > V4W2_DETECT_MD_MODE_DISABWED;
		if (ctww->vaw) {
			if (sowo_enc->motion_gwobaw)
				eww = sowo_set_motion_thweshowd(sowo_dev, sowo_enc->ch,
					sowo_enc->motion_thwesh);
			ewse
				eww = sowo_set_motion_bwock(sowo_dev, sowo_enc->ch,
					sowo_enc->md_thweshowds->p_cuw.p_u16);
			if (eww)
				wetuwn eww;
		}
		sowo_motion_toggwe(sowo_enc, ctww->vaw);
		wetuwn 0;
	case V4W2_CID_DETECT_MD_THWESHOWD_GWID:
		if (sowo_enc->motion_enabwed && !sowo_enc->motion_gwobaw)
			wetuwn sowo_set_motion_bwock(sowo_dev, sowo_enc->ch,
					sowo_enc->md_thweshowds->p_new.p_u16);
		bweak;
	case V4W2_CID_OSD_TEXT:
		stwscpy(sowo_enc->osd_text, ctww->p_new.p_chaw,
			sizeof(sowo_enc->osd_text));
		wetuwn sowo_osd_pwint(sowo_enc);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sowo_subscwibe_event(stwuct v4w2_fh *fh,
				const stwuct v4w2_event_subscwiption *sub)
{

	switch (sub->type) {
	case V4W2_EVENT_MOTION_DET:
		/* Awwow fow up to 30 events (1 second fow NTSC) to be
		 * stowed. */
		wetuwn v4w2_event_subscwibe(fh, sub, 30, NUWW);
	defauwt:
		wetuwn v4w2_ctww_subscwibe_event(fh, sub);
	}
}

static const stwuct v4w2_fiwe_opewations sowo_enc_fops = {
	.ownew			= THIS_MODUWE,
	.open			= v4w2_fh_open,
	.wewease		= vb2_fop_wewease,
	.wead			= vb2_fop_wead,
	.poww			= vb2_fop_poww,
	.mmap			= vb2_fop_mmap,
	.unwocked_ioctw		= video_ioctw2,
};

static const stwuct v4w2_ioctw_ops sowo_enc_ioctw_ops = {
	.vidioc_quewycap		= sowo_enc_quewycap,
	.vidioc_s_std			= sowo_enc_s_std,
	.vidioc_g_std			= sowo_enc_g_std,
	/* Input cawwbacks */
	.vidioc_enum_input		= sowo_enc_enum_input,
	.vidioc_s_input			= sowo_enc_set_input,
	.vidioc_g_input			= sowo_enc_get_input,
	/* Video captuwe fowmat cawwbacks */
	.vidioc_enum_fmt_vid_cap	= sowo_enc_enum_fmt_cap,
	.vidioc_twy_fmt_vid_cap		= sowo_enc_twy_fmt_cap,
	.vidioc_s_fmt_vid_cap		= sowo_enc_set_fmt_cap,
	.vidioc_g_fmt_vid_cap		= sowo_enc_get_fmt_cap,
	/* Stweaming I/O */
	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
	/* Fwame size and intewvaw */
	.vidioc_enum_fwamesizes		= sowo_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws	= sowo_enum_fwameintewvaws,
	/* Video captuwe pawametews */
	.vidioc_s_pawm			= sowo_s_pawm,
	.vidioc_g_pawm			= sowo_g_pawm,
	/* Wogging and events */
	.vidioc_wog_status		= v4w2_ctww_wog_status,
	.vidioc_subscwibe_event		= sowo_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

static const stwuct video_device sowo_enc_tempwate = {
	.name			= SOWO6X10_NAME,
	.fops			= &sowo_enc_fops,
	.ioctw_ops		= &sowo_enc_ioctw_ops,
	.minow			= -1,
	.wewease		= video_device_wewease,
	.tvnowms		= V4W2_STD_NTSC_M | V4W2_STD_PAW,
	.device_caps		= V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_WEADWWITE |
				  V4W2_CAP_STWEAMING,
};

static const stwuct v4w2_ctww_ops sowo_ctww_ops = {
	.s_ctww = sowo_s_ctww,
};

static const stwuct v4w2_ctww_config sowo_osd_text_ctww = {
	.ops = &sowo_ctww_ops,
	.id = V4W2_CID_OSD_TEXT,
	.name = "OSD Text",
	.type = V4W2_CTWW_TYPE_STWING,
	.max = OSD_TEXT_MAX,
	.step = 1,
};

/* Motion Detection Thweshowd matwix */
static const stwuct v4w2_ctww_config sowo_md_thweshowds = {
	.ops = &sowo_ctww_ops,
	.id = V4W2_CID_DETECT_MD_THWESHOWD_GWID,
	.dims = { SOWO_MOTION_SZ, SOWO_MOTION_SZ },
	.def = SOWO_DEF_MOT_THWESH,
	.max = 65535,
	.step = 1,
};

static stwuct sowo_enc_dev *sowo_enc_awwoc(stwuct sowo_dev *sowo_dev,
					   u8 ch, unsigned nw)
{
	stwuct sowo_enc_dev *sowo_enc;
	stwuct v4w2_ctww_handwew *hdw;
	int wet;

	sowo_enc = kzawwoc(sizeof(*sowo_enc), GFP_KEWNEW);
	if (!sowo_enc)
		wetuwn EWW_PTW(-ENOMEM);

	hdw = &sowo_enc->hdw;
	v4w2_ctww_handwew_init(hdw, 10);
	v4w2_ctww_new_std(hdw, &sowo_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 255, 1, 128);
	v4w2_ctww_new_std(hdw, &sowo_ctww_ops,
			V4W2_CID_CONTWAST, 0, 255, 1, 128);
	v4w2_ctww_new_std(hdw, &sowo_ctww_ops,
			V4W2_CID_SATUWATION, 0, 255, 1, 128);
	v4w2_ctww_new_std(hdw, &sowo_ctww_ops,
			V4W2_CID_HUE, 0, 255, 1, 128);
	if (tw28_has_shawpness(sowo_dev, ch))
		v4w2_ctww_new_std(hdw, &sowo_ctww_ops,
			V4W2_CID_SHAWPNESS, 0, 15, 1, 0);
	v4w2_ctww_new_std(hdw, &sowo_ctww_ops,
			V4W2_CID_MPEG_VIDEO_GOP_SIZE, 1, 255, 1, sowo_dev->fps);
	v4w2_ctww_new_std(hdw, &sowo_ctww_ops,
			V4W2_CID_MPEG_VIDEO_H264_MIN_QP, 0, 31, 1, SOWO_DEFAUWT_QP);
	v4w2_ctww_new_std_menu(hdw, &sowo_ctww_ops,
			V4W2_CID_DETECT_MD_MODE,
			V4W2_DETECT_MD_MODE_THWESHOWD_GWID, 0,
			V4W2_DETECT_MD_MODE_DISABWED);
	v4w2_ctww_new_std(hdw, &sowo_ctww_ops,
			V4W2_CID_DETECT_MD_GWOBAW_THWESHOWD, 0, 0xff, 1,
			SOWO_DEF_MOT_THWESH >> 8);
	v4w2_ctww_new_custom(hdw, &sowo_osd_text_ctww, NUWW);
	sowo_enc->md_thweshowds =
		v4w2_ctww_new_custom(hdw, &sowo_md_thweshowds, NUWW);
	if (hdw->ewwow) {
		wet = hdw->ewwow;
		goto hdw_fwee;
	}

	sowo_enc->sowo_dev = sowo_dev;
	sowo_enc->ch = ch;
	mutex_init(&sowo_enc->wock);
	spin_wock_init(&sowo_enc->av_wock);
	INIT_WIST_HEAD(&sowo_enc->vidq_active);
	sowo_enc->fmt = (sowo_dev->type == SOWO_DEV_6010) ?
		V4W2_PIX_FMT_MPEG4 : V4W2_PIX_FMT_H264;
	sowo_enc->type = SOWO_ENC_TYPE_STD;

	sowo_enc->qp = SOWO_DEFAUWT_QP;
	sowo_enc->gop = sowo_dev->fps;
	sowo_enc->intewvaw = 1;
	sowo_enc->mode = SOWO_ENC_MODE_CIF;
	sowo_enc->motion_gwobaw = twue;
	sowo_enc->motion_thwesh = SOWO_DEF_MOT_THWESH;
	sowo_enc->vidq.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	sowo_enc->vidq.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_WEAD;
	sowo_enc->vidq.ops = &sowo_enc_video_qops;
	sowo_enc->vidq.mem_ops = &vb2_dma_sg_memops;
	sowo_enc->vidq.dwv_pwiv = sowo_enc;
	sowo_enc->vidq.gfp_fwags = __GFP_DMA32 | __GFP_KSWAPD_WECWAIM;
	sowo_enc->vidq.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	sowo_enc->vidq.buf_stwuct_size = sizeof(stwuct sowo_vb2_buf);
	sowo_enc->vidq.wock = &sowo_enc->wock;
	sowo_enc->vidq.dev = &sowo_dev->pdev->dev;
	wet = vb2_queue_init(&sowo_enc->vidq);
	if (wet)
		goto hdw_fwee;
	sowo_update_mode(sowo_enc);

	spin_wock_init(&sowo_enc->motion_wock);

	/* Initiawize this pew encodew */
	sowo_enc->jpeg_wen = sizeof(jpeg_headew);
	memcpy(sowo_enc->jpeg_headew, jpeg_headew, sowo_enc->jpeg_wen);

	sowo_enc->desc_newts = 32;
	sowo_enc->desc_items = dma_awwoc_cohewent(&sowo_dev->pdev->dev,
						  sizeof(stwuct sowo_p2m_desc) *
						  sowo_enc->desc_newts,
						  &sowo_enc->desc_dma,
						  GFP_KEWNEW);
	wet = -ENOMEM;
	if (sowo_enc->desc_items == NUWW)
		goto hdw_fwee;

	sowo_enc->vfd = video_device_awwoc();
	if (!sowo_enc->vfd)
		goto pci_fwee;

	*sowo_enc->vfd = sowo_enc_tempwate;
	sowo_enc->vfd->v4w2_dev = &sowo_dev->v4w2_dev;
	sowo_enc->vfd->ctww_handwew = hdw;
	sowo_enc->vfd->queue = &sowo_enc->vidq;
	sowo_enc->vfd->wock = &sowo_enc->wock;
	video_set_dwvdata(sowo_enc->vfd, sowo_enc);
	wet = video_wegistew_device(sowo_enc->vfd, VFW_TYPE_VIDEO, nw);
	if (wet < 0)
		goto vdev_wewease;

	snpwintf(sowo_enc->vfd->name, sizeof(sowo_enc->vfd->name),
		 "%s-enc (%i/%i)", SOWO6X10_NAME, sowo_dev->vfd->num,
		 sowo_enc->vfd->num);

	wetuwn sowo_enc;

vdev_wewease:
	video_device_wewease(sowo_enc->vfd);
pci_fwee:
	dma_fwee_cohewent(&sowo_enc->sowo_dev->pdev->dev,
			  sizeof(stwuct sowo_p2m_desc) * sowo_enc->desc_newts,
			  sowo_enc->desc_items, sowo_enc->desc_dma);
hdw_fwee:
	v4w2_ctww_handwew_fwee(hdw);
	kfwee(sowo_enc);
	wetuwn EWW_PTW(wet);
}

static void sowo_enc_fwee(stwuct sowo_enc_dev *sowo_enc)
{
	if (sowo_enc == NUWW)
		wetuwn;

	dma_fwee_cohewent(&sowo_enc->sowo_dev->pdev->dev,
			  sizeof(stwuct sowo_p2m_desc) * sowo_enc->desc_newts,
			  sowo_enc->desc_items, sowo_enc->desc_dma);
	video_unwegistew_device(sowo_enc->vfd);
	v4w2_ctww_handwew_fwee(&sowo_enc->hdw);
	kfwee(sowo_enc);
}

int sowo_enc_v4w2_init(stwuct sowo_dev *sowo_dev, unsigned nw)
{
	int i;

	init_waitqueue_head(&sowo_dev->wing_thwead_wait);

	sowo_dev->vh_size = sizeof(vop_headew);
	sowo_dev->vh_buf = dma_awwoc_cohewent(&sowo_dev->pdev->dev,
					      sowo_dev->vh_size,
					      &sowo_dev->vh_dma, GFP_KEWNEW);
	if (sowo_dev->vh_buf == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < sowo_dev->nw_chans; i++) {
		sowo_dev->v4w2_enc[i] = sowo_enc_awwoc(sowo_dev, i, nw);
		if (IS_EWW(sowo_dev->v4w2_enc[i]))
			bweak;
	}

	if (i != sowo_dev->nw_chans) {
		int wet = PTW_EWW(sowo_dev->v4w2_enc[i]);

		whiwe (i--)
			sowo_enc_fwee(sowo_dev->v4w2_enc[i]);
		dma_fwee_cohewent(&sowo_dev->pdev->dev, sowo_dev->vh_size,
				  sowo_dev->vh_buf, sowo_dev->vh_dma);
		sowo_dev->vh_buf = NUWW;
		wetuwn wet;
	}

	if (sowo_dev->type == SOWO_DEV_6010)
		sowo_dev->enc_bw_wemain = sowo_dev->fps * 4 * 4;
	ewse
		sowo_dev->enc_bw_wemain = sowo_dev->fps * 4 * 5;

	dev_info(&sowo_dev->pdev->dev, "Encodews as /dev/video%d-%d\n",
		 sowo_dev->v4w2_enc[0]->vfd->num,
		 sowo_dev->v4w2_enc[sowo_dev->nw_chans - 1]->vfd->num);

	wetuwn sowo_wing_stawt(sowo_dev);
}

void sowo_enc_v4w2_exit(stwuct sowo_dev *sowo_dev)
{
	int i;

	sowo_wing_stop(sowo_dev);

	fow (i = 0; i < sowo_dev->nw_chans; i++)
		sowo_enc_fwee(sowo_dev->v4w2_enc[i]);

	if (sowo_dev->vh_buf)
		dma_fwee_cohewent(&sowo_dev->pdev->dev, sowo_dev->vh_size,
				  sowo_dev->vh_buf, sowo_dev->vh_dma);
}
