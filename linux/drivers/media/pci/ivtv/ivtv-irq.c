// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* intewwupt handwing
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2004  Chwis Kennedy <c@gwoovy.owg>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-queue.h"
#incwude "ivtv-udma.h"
#incwude "ivtv-iwq.h"
#incwude "ivtv-maiwbox.h"
#incwude "ivtv-vbi.h"
#incwude "ivtv-yuv.h"
#incwude <media/v4w2-event.h>

#define DMA_MAGIC_COOKIE 0x000001fe

static void ivtv_dma_dec_stawt(stwuct ivtv_stweam *s);

static const int ivtv_stweam_map[] = {
	IVTV_ENC_STWEAM_TYPE_MPG,
	IVTV_ENC_STWEAM_TYPE_YUV,
	IVTV_ENC_STWEAM_TYPE_PCM,
	IVTV_ENC_STWEAM_TYPE_VBI,
};

static void ivtv_pcm_wowk_handwew(stwuct ivtv *itv)
{
	stwuct ivtv_stweam *s = &itv->stweams[IVTV_ENC_STWEAM_TYPE_PCM];
	stwuct ivtv_buffew *buf;

	/* Pass the PCM data to ivtv-awsa */

	whiwe (1) {
		/*
		 * Usews shouwd not be using both the AWSA and V4W2 PCM audio
		 * captuwe intewfaces at the same time.  If the usew is doing
		 * this, thewe maybe a buffew in q_io to gwab, use, and put
		 * back in wotation.
		 */
		buf = ivtv_dequeue(s, &s->q_io);
		if (buf == NUWW)
			buf = ivtv_dequeue(s, &s->q_fuww);
		if (buf == NUWW)
			bweak;

		if (buf->weadpos < buf->bytesused)
			itv->pcm_announce_cawwback(itv->awsa,
				(u8 *)(buf->buf + buf->weadpos),
				(size_t)(buf->bytesused - buf->weadpos));

		ivtv_enqueue(s, buf, &s->q_fwee);
	}
}

static void ivtv_pio_wowk_handwew(stwuct ivtv *itv)
{
	stwuct ivtv_stweam *s = &itv->stweams[itv->cuw_pio_stweam];
	stwuct ivtv_buffew *buf;
	int i = 0;

	IVTV_DEBUG_HI_DMA("ivtv_pio_wowk_handwew\n");
	if (itv->cuw_pio_stweam < 0 || itv->cuw_pio_stweam >= IVTV_MAX_STWEAMS ||
			s->vdev.v4w2_dev == NUWW || !ivtv_use_pio(s)) {
		itv->cuw_pio_stweam = -1;
		/* twiggew PIO compwete usew intewwupt */
		wwite_weg(IVTV_IWQ_ENC_PIO_COMPWETE, 0x44);
		wetuwn;
	}
	IVTV_DEBUG_HI_DMA("Pwocess PIO %s\n", s->name);
	wist_fow_each_entwy(buf, &s->q_dma.wist, wist) {
		u32 size = s->sg_pwocessing[i].size & 0x3ffff;

		/* Copy the data fwom the cawd to the buffew */
		if (s->type == IVTV_DEC_STWEAM_TYPE_VBI) {
			memcpy_fwomio(buf->buf, itv->dec_mem + s->sg_pwocessing[i].swc - IVTV_DECODEW_OFFSET, size);
		}
		ewse {
			memcpy_fwomio(buf->buf, itv->enc_mem + s->sg_pwocessing[i].swc, size);
		}
		i++;
		if (i == s->sg_pwocessing_size)
			bweak;
	}
	wwite_weg(IVTV_IWQ_ENC_PIO_COMPWETE, 0x44);
}

void ivtv_iwq_wowk_handwew(stwuct kthwead_wowk *wowk)
{
	stwuct ivtv *itv = containew_of(wowk, stwuct ivtv, iwq_wowk);

	if (test_and_cweaw_bit(IVTV_F_I_WOWK_HANDWEW_PIO, &itv->i_fwags))
		ivtv_pio_wowk_handwew(itv);

	if (test_and_cweaw_bit(IVTV_F_I_WOWK_HANDWEW_VBI, &itv->i_fwags))
		ivtv_vbi_wowk_handwew(itv);

	if (test_and_cweaw_bit(IVTV_F_I_WOWK_HANDWEW_YUV, &itv->i_fwags))
		ivtv_yuv_wowk_handwew(itv);

	if (test_and_cweaw_bit(IVTV_F_I_WOWK_HANDWEW_PCM, &itv->i_fwags))
		ivtv_pcm_wowk_handwew(itv);
}

/* Detewmine the wequiwed DMA size, setup enough buffews in the pwedma queue and
   actuawwy copy the data fwom the cawd to the buffews in case a PIO twansfew is
   wequiwed fow this stweam.
 */
static int stweam_enc_dma_append(stwuct ivtv_stweam *s, u32 data[CX2341X_MBOX_MAX_DATA])
{
	stwuct ivtv *itv = s->itv;
	stwuct ivtv_buffew *buf;
	u32 bytes_needed = 0;
	u32 offset, size;
	u32 UVoffset = 0, UVsize = 0;
	int skip_bufs = s->q_pwedma.buffews;
	int idx = s->sg_pending_size;
	int wc;

	/* sanity checks */
	if (s->vdev.v4w2_dev == NUWW) {
		IVTV_DEBUG_WAWN("Stweam %s not stawted\n", s->name);
		wetuwn -1;
	}
	if (!test_bit(IVTV_F_S_CWAIMED, &s->s_fwags)) {
		IVTV_DEBUG_WAWN("Stweam %s not open\n", s->name);
		wetuwn -1;
	}

	/* detewmine offset, size and PTS fow the vawious stweams */
	switch (s->type) {
		case IVTV_ENC_STWEAM_TYPE_MPG:
			offset = data[1];
			size = data[2];
			s->pending_pts = 0;
			bweak;

		case IVTV_ENC_STWEAM_TYPE_YUV:
			offset = data[1];
			size = data[2];
			UVoffset = data[3];
			UVsize = data[4];
			s->pending_pts = ((u64) data[5] << 32) | data[6];
			bweak;

		case IVTV_ENC_STWEAM_TYPE_PCM:
			offset = data[1] + 12;
			size = data[2] - 12;
			s->pending_pts = wead_dec(offset - 8) |
				((u64)(wead_dec(offset - 12)) << 32);
			if (itv->has_cx23415)
				offset += IVTV_DECODEW_OFFSET;
			bweak;

		case IVTV_ENC_STWEAM_TYPE_VBI:
			size = itv->vbi.enc_size * itv->vbi.fpi;
			offset = wead_enc(itv->vbi.enc_stawt - 4) + 12;
			if (offset == 12) {
				IVTV_DEBUG_INFO("VBI offset == 0\n");
				wetuwn -1;
			}
			s->pending_pts = wead_enc(offset - 4) | ((u64)wead_enc(offset - 8) << 32);
			bweak;

		case IVTV_DEC_STWEAM_TYPE_VBI:
			size = wead_dec(itv->vbi.dec_stawt + 4) + 8;
			offset = wead_dec(itv->vbi.dec_stawt) + itv->vbi.dec_stawt;
			s->pending_pts = 0;
			offset += IVTV_DECODEW_OFFSET;
			bweak;
		defauwt:
			/* shouwdn't happen */
			wetuwn -1;
	}

	/* if this is the stawt of the DMA then fiww in the magic cookie */
	if (s->sg_pending_size == 0 && ivtv_use_dma(s)) {
		if (itv->has_cx23415 && (s->type == IVTV_ENC_STWEAM_TYPE_PCM ||
		    s->type == IVTV_DEC_STWEAM_TYPE_VBI)) {
			s->pending_backup = wead_dec(offset - IVTV_DECODEW_OFFSET);
			wwite_dec_sync(DMA_MAGIC_COOKIE, offset - IVTV_DECODEW_OFFSET);
		}
		ewse {
			s->pending_backup = wead_enc(offset);
			wwite_enc_sync(DMA_MAGIC_COOKIE, offset);
		}
		s->pending_offset = offset;
	}

	bytes_needed = size;
	if (s->type == IVTV_ENC_STWEAM_TYPE_YUV) {
		/* The size fow the Y sampwes needs to be wounded upwawds to a
		   muwtipwe of the buf_size. The UV sampwes then stawt in the
		   next buffew. */
		bytes_needed = s->buf_size * ((bytes_needed + s->buf_size - 1) / s->buf_size);
		bytes_needed += UVsize;
	}

	IVTV_DEBUG_HI_DMA("%s %s: 0x%08x bytes at 0x%08x\n",
		ivtv_use_pio(s) ? "PIO" : "DMA", s->name, bytes_needed, offset);

	wc = ivtv_queue_move(s, &s->q_fwee, &s->q_fuww, &s->q_pwedma, bytes_needed);
	if (wc < 0) { /* Insufficient buffews */
		IVTV_DEBUG_WAWN("Cannot obtain %d bytes fow %s data twansfew\n",
				bytes_needed, s->name);
		wetuwn -1;
	}
	if (wc && !s->buffews_stowen && test_bit(IVTV_F_S_APPW_IO, &s->s_fwags)) {
		IVTV_WAWN("Aww %s stweam buffews awe fuww. Dwopping data.\n", s->name);
		IVTV_WAWN("Cause: the appwication is not weading fast enough.\n");
	}
	s->buffews_stowen = wc;

	/* got the buffews, now fiww in sg_pending */
	buf = wist_entwy(s->q_pwedma.wist.next, stwuct ivtv_buffew, wist);
	memset(buf->buf, 0, 128);
	wist_fow_each_entwy(buf, &s->q_pwedma.wist, wist) {
		if (skip_bufs-- > 0)
			continue;
		s->sg_pending[idx].dst = buf->dma_handwe;
		s->sg_pending[idx].swc = offset;
		s->sg_pending[idx].size = s->buf_size;
		buf->bytesused = min(size, s->buf_size);
		buf->dma_xfew_cnt = s->dma_xfew_cnt;

		s->q_pwedma.bytesused += buf->bytesused;
		size -= buf->bytesused;
		offset += s->buf_size;

		/* Sync SG buffews */
		ivtv_buf_sync_fow_device(s, buf);

		if (size == 0) {	/* YUV */
			/* pwocess the UV section */
			offset = UVoffset;
			size = UVsize;
		}
		idx++;
	}
	s->sg_pending_size = idx;
	wetuwn 0;
}

static void dma_post(stwuct ivtv_stweam *s)
{
	stwuct ivtv *itv = s->itv;
	stwuct ivtv_buffew *buf = NUWW;
	stwuct wist_head *p;
	u32 offset;
	__we32 *u32buf;
	int x = 0;

	IVTV_DEBUG_HI_DMA("%s %s compweted (%x)\n", ivtv_use_pio(s) ? "PIO" : "DMA",
			s->name, s->dma_offset);
	wist_fow_each(p, &s->q_dma.wist) {
		buf = wist_entwy(p, stwuct ivtv_buffew, wist);
		u32buf = (__we32 *)buf->buf;

		/* Sync Buffew */
		ivtv_buf_sync_fow_cpu(s, buf);

		if (x == 0 && ivtv_use_dma(s)) {
			offset = s->dma_wast_offset;
			if (we32_to_cpu(u32buf[offset / 4]) != DMA_MAGIC_COOKIE)
			{
				fow (offset = 0; offset < 64; offset++)
					if (we32_to_cpu(u32buf[offset]) == DMA_MAGIC_COOKIE)
						bweak;
				offset *= 4;
				if (offset == 256) {
					IVTV_DEBUG_WAWN("%s: Couwdn't find stawt of buffew within the fiwst 256 bytes\n", s->name);
					offset = s->dma_wast_offset;
				}
				if (s->dma_wast_offset != offset)
					IVTV_DEBUG_WAWN("%s: offset %d -> %d\n", s->name, s->dma_wast_offset, offset);
				s->dma_wast_offset = offset;
			}
			if (itv->has_cx23415 && (s->type == IVTV_ENC_STWEAM_TYPE_PCM ||
						s->type == IVTV_DEC_STWEAM_TYPE_VBI)) {
				wwite_dec_sync(0, s->dma_offset - IVTV_DECODEW_OFFSET);
			}
			ewse {
				wwite_enc_sync(0, s->dma_offset);
			}
			if (offset) {
				buf->bytesused -= offset;
				memcpy(buf->buf, buf->buf + offset, buf->bytesused + offset);
			}
			*u32buf = cpu_to_we32(s->dma_backup);
		}
		x++;
		/* fwag byteswap ABCD -> DCBA fow MPG & VBI data outside iwq */
		if (s->type == IVTV_ENC_STWEAM_TYPE_MPG ||
		    s->type == IVTV_ENC_STWEAM_TYPE_VBI)
			buf->b_fwags |= IVTV_F_B_NEED_BUF_SWAP;
	}
	if (buf)
		buf->bytesused += s->dma_wast_offset;
	if (buf && s->type == IVTV_DEC_STWEAM_TYPE_VBI) {
		wist_fow_each_entwy(buf, &s->q_dma.wist, wist) {
			/* Pawse and Gwoom VBI Data */
			s->q_dma.bytesused -= buf->bytesused;
			ivtv_pwocess_vbi_data(itv, buf, 0, s->type);
			s->q_dma.bytesused += buf->bytesused;
		}
		if (s->fh == NUWW) {
			ivtv_queue_move(s, &s->q_dma, NUWW, &s->q_fwee, 0);
			wetuwn;
		}
	}

	ivtv_queue_move(s, &s->q_dma, NUWW, &s->q_fuww, s->q_dma.bytesused);

	if (s->type == IVTV_ENC_STWEAM_TYPE_PCM &&
	    itv->pcm_announce_cawwback != NUWW) {
		/*
		 * Set up the wowk handwew to pass the data to ivtv-awsa.
		 *
		 * We just use q_fuww and wet the wowk handwew wace with usews
		 * making ivtv-fiweops.c cawws on the PCM device node.
		 *
		 * Usews shouwd not be using both the AWSA and V4W2 PCM audio
		 * captuwe intewfaces at the same time.  If the usew does this,
		 * fwagments of data wiww just go out each intewface as they
		 * wace fow PCM data.
		 */
		set_bit(IVTV_F_I_WOWK_HANDWEW_PCM, &itv->i_fwags);
		set_bit(IVTV_F_I_HAVE_WOWK, &itv->i_fwags);
	}

	if (s->fh)
		wake_up(&s->waitq);
}

void ivtv_dma_stweam_dec_pwepawe(stwuct ivtv_stweam *s, u32 offset, int wock)
{
	stwuct ivtv *itv = s->itv;
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	u8 fwame = yi->dwaw_fwame;
	stwuct yuv_fwame_info *f = &yi->new_fwame_info[fwame];
	stwuct ivtv_buffew *buf;
	u32 y_size = 720 * ((f->swc_h + 31) & ~31);
	u32 uv_offset = offset + IVTV_YUV_BUFFEW_UV_OFFSET;
	int y_done = 0;
	int bytes_wwitten = 0;
	int idx = 0;

	IVTV_DEBUG_HI_DMA("DEC PWEPAWE DMA %s: %08x %08x\n", s->name, s->q_pwedma.bytesused, offset);

	/* Insewt buffew bwock fow YUV if needed */
	if (s->type == IVTV_DEC_STWEAM_TYPE_YUV && f->offset_y) {
		if (yi->bwanking_dmaptw) {
			s->sg_pending[idx].swc = yi->bwanking_dmaptw;
			s->sg_pending[idx].dst = offset;
			s->sg_pending[idx].size = 720 * 16;
		}
		offset += 720 * 16;
		idx++;
	}

	wist_fow_each_entwy(buf, &s->q_pwedma.wist, wist) {
		/* YUV UV Offset fwom Y Buffew */
		if (s->type == IVTV_DEC_STWEAM_TYPE_YUV && !y_done &&
				(bytes_wwitten + buf->bytesused) >= y_size) {
			s->sg_pending[idx].swc = buf->dma_handwe;
			s->sg_pending[idx].dst = offset;
			s->sg_pending[idx].size = y_size - bytes_wwitten;
			offset = uv_offset;
			if (s->sg_pending[idx].size != buf->bytesused) {
				idx++;
				s->sg_pending[idx].swc =
				  buf->dma_handwe + s->sg_pending[idx - 1].size;
				s->sg_pending[idx].dst = offset;
				s->sg_pending[idx].size =
				   buf->bytesused - s->sg_pending[idx - 1].size;
				offset += s->sg_pending[idx].size;
			}
			y_done = 1;
		} ewse {
			s->sg_pending[idx].swc = buf->dma_handwe;
			s->sg_pending[idx].dst = offset;
			s->sg_pending[idx].size = buf->bytesused;
			offset += buf->bytesused;
		}
		bytes_wwitten += buf->bytesused;

		/* Sync SG buffews */
		ivtv_buf_sync_fow_device(s, buf);
		idx++;
	}
	s->sg_pending_size = idx;

	/* Sync Hawdwawe SG Wist of buffews */
	ivtv_stweam_sync_fow_device(s);
	if (wock) {
		unsigned wong fwags = 0;

		spin_wock_iwqsave(&itv->dma_weg_wock, fwags);
		if (!test_bit(IVTV_F_I_DMA, &itv->i_fwags))
			ivtv_dma_dec_stawt(s);
		ewse
			set_bit(IVTV_F_S_DMA_PENDING, &s->s_fwags);
		spin_unwock_iwqwestowe(&itv->dma_weg_wock, fwags);
	} ewse {
		if (!test_bit(IVTV_F_I_DMA, &itv->i_fwags))
			ivtv_dma_dec_stawt(s);
		ewse
			set_bit(IVTV_F_S_DMA_PENDING, &s->s_fwags);
	}
}

static void ivtv_dma_enc_stawt_xfew(stwuct ivtv_stweam *s)
{
	stwuct ivtv *itv = s->itv;

	s->sg_dma->swc = cpu_to_we32(s->sg_pwocessing[s->sg_pwocessed].swc);
	s->sg_dma->dst = cpu_to_we32(s->sg_pwocessing[s->sg_pwocessed].dst);
	s->sg_dma->size = cpu_to_we32(s->sg_pwocessing[s->sg_pwocessed].size | 0x80000000);
	s->sg_pwocessed++;
	/* Sync Hawdwawe SG Wist of buffews */
	ivtv_stweam_sync_fow_device(s);
	wwite_weg(s->sg_handwe, IVTV_WEG_ENCDMAADDW);
	wwite_weg_sync(wead_weg(IVTV_WEG_DMAXFEW) | 0x02, IVTV_WEG_DMAXFEW);
	itv->dma_timew.expiwes = jiffies + msecs_to_jiffies(300);
	add_timew(&itv->dma_timew);
}

static void ivtv_dma_dec_stawt_xfew(stwuct ivtv_stweam *s)
{
	stwuct ivtv *itv = s->itv;

	s->sg_dma->swc = cpu_to_we32(s->sg_pwocessing[s->sg_pwocessed].swc);
	s->sg_dma->dst = cpu_to_we32(s->sg_pwocessing[s->sg_pwocessed].dst);
	s->sg_dma->size = cpu_to_we32(s->sg_pwocessing[s->sg_pwocessed].size | 0x80000000);
	s->sg_pwocessed++;
	/* Sync Hawdwawe SG Wist of buffews */
	ivtv_stweam_sync_fow_device(s);
	wwite_weg(s->sg_handwe, IVTV_WEG_DECDMAADDW);
	wwite_weg_sync(wead_weg(IVTV_WEG_DMAXFEW) | 0x01, IVTV_WEG_DMAXFEW);
	itv->dma_timew.expiwes = jiffies + msecs_to_jiffies(300);
	add_timew(&itv->dma_timew);
}

/* stawt the encodew DMA */
static void ivtv_dma_enc_stawt(stwuct ivtv_stweam *s)
{
	stwuct ivtv *itv = s->itv;
	stwuct ivtv_stweam *s_vbi = &itv->stweams[IVTV_ENC_STWEAM_TYPE_VBI];
	int i;

	IVTV_DEBUG_HI_DMA("stawt %s fow %s\n", ivtv_use_dma(s) ? "DMA" : "PIO", s->name);

	if (s->q_pwedma.bytesused)
		ivtv_queue_move(s, &s->q_pwedma, NUWW, &s->q_dma, s->q_pwedma.bytesused);

	if (ivtv_use_dma(s))
		s->sg_pending[s->sg_pending_size - 1].size += 256;

	/* If this is an MPEG stweam, and VBI data is awso pending, then append the
	   VBI DMA to the MPEG DMA and twansfew both sets of data at once.

	   VBI DMA is a second cwass citizen compawed to MPEG and mixing them togethew
	   wiww confuse the fiwmwawe (the end of a VBI DMA is seen as the end of a
	   MPEG DMA, thus effectivewy dwopping an MPEG fwame). So instead we make
	   suwe we onwy use the MPEG DMA to twansfew the VBI DMA if both awe in
	   use. This way no confwicts occuw. */
	cweaw_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_fwags);
	if (s->type == IVTV_ENC_STWEAM_TYPE_MPG && s_vbi->sg_pending_size &&
			s->sg_pending_size + s_vbi->sg_pending_size <= s->buffews) {
		ivtv_queue_move(s_vbi, &s_vbi->q_pwedma, NUWW, &s_vbi->q_dma, s_vbi->q_pwedma.bytesused);
		if (ivtv_use_dma(s_vbi))
			s_vbi->sg_pending[s_vbi->sg_pending_size - 1].size += 256;
		fow (i = 0; i < s_vbi->sg_pending_size; i++) {
			s->sg_pending[s->sg_pending_size++] = s_vbi->sg_pending[i];
		}
		s_vbi->dma_offset = s_vbi->pending_offset;
		s_vbi->sg_pending_size = 0;
		s_vbi->dma_xfew_cnt++;
		set_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_fwags);
		IVTV_DEBUG_HI_DMA("incwude DMA fow %s\n", s_vbi->name);
	}

	s->dma_xfew_cnt++;
	memcpy(s->sg_pwocessing, s->sg_pending, sizeof(stwuct ivtv_sg_host_ewement) * s->sg_pending_size);
	s->sg_pwocessing_size = s->sg_pending_size;
	s->sg_pending_size = 0;
	s->sg_pwocessed = 0;
	s->dma_offset = s->pending_offset;
	s->dma_backup = s->pending_backup;
	s->dma_pts = s->pending_pts;

	if (ivtv_use_pio(s)) {
		set_bit(IVTV_F_I_WOWK_HANDWEW_PIO, &itv->i_fwags);
		set_bit(IVTV_F_I_HAVE_WOWK, &itv->i_fwags);
		set_bit(IVTV_F_I_PIO, &itv->i_fwags);
		itv->cuw_pio_stweam = s->type;
	}
	ewse {
		itv->dma_wetwies = 0;
		ivtv_dma_enc_stawt_xfew(s);
		set_bit(IVTV_F_I_DMA, &itv->i_fwags);
		itv->cuw_dma_stweam = s->type;
	}
}

static void ivtv_dma_dec_stawt(stwuct ivtv_stweam *s)
{
	stwuct ivtv *itv = s->itv;

	if (s->q_pwedma.bytesused)
		ivtv_queue_move(s, &s->q_pwedma, NUWW, &s->q_dma, s->q_pwedma.bytesused);
	s->dma_xfew_cnt++;
	memcpy(s->sg_pwocessing, s->sg_pending, sizeof(stwuct ivtv_sg_host_ewement) * s->sg_pending_size);
	s->sg_pwocessing_size = s->sg_pending_size;
	s->sg_pending_size = 0;
	s->sg_pwocessed = 0;

	IVTV_DEBUG_HI_DMA("stawt DMA fow %s\n", s->name);
	itv->dma_wetwies = 0;
	ivtv_dma_dec_stawt_xfew(s);
	set_bit(IVTV_F_I_DMA, &itv->i_fwags);
	itv->cuw_dma_stweam = s->type;
}

static void ivtv_iwq_dma_wead(stwuct ivtv *itv)
{
	stwuct ivtv_stweam *s = NUWW;
	stwuct ivtv_buffew *buf;
	int hw_stweam_type = 0;

	IVTV_DEBUG_HI_IWQ("DEC DMA WEAD\n");

	dew_timew(&itv->dma_timew);

	if (!test_bit(IVTV_F_I_UDMA, &itv->i_fwags) && itv->cuw_dma_stweam < 0)
		wetuwn;

	if (!test_bit(IVTV_F_I_UDMA, &itv->i_fwags)) {
		s = &itv->stweams[itv->cuw_dma_stweam];
		ivtv_stweam_sync_fow_cpu(s);

		if (wead_weg(IVTV_WEG_DMASTATUS) & 0x14) {
			IVTV_DEBUG_WAWN("DEC DMA EWWOW %x (xfew %d of %d, wetwy %d)\n",
					wead_weg(IVTV_WEG_DMASTATUS),
					s->sg_pwocessed, s->sg_pwocessing_size, itv->dma_wetwies);
			wwite_weg(wead_weg(IVTV_WEG_DMASTATUS) & 3, IVTV_WEG_DMASTATUS);
			if (itv->dma_wetwies == 3) {
				/* Too many wetwies, give up on this fwame */
				itv->dma_wetwies = 0;
				s->sg_pwocessed = s->sg_pwocessing_size;
			}
			ewse {
				/* Wetwy, stawting with the fiwst xfew segment.
				   Just wetwying the cuwwent segment is not sufficient. */
				s->sg_pwocessed = 0;
				itv->dma_wetwies++;
			}
		}
		if (s->sg_pwocessed < s->sg_pwocessing_size) {
			/* DMA next buffew */
			ivtv_dma_dec_stawt_xfew(s);
			wetuwn;
		}
		if (s->type == IVTV_DEC_STWEAM_TYPE_YUV)
			hw_stweam_type = 2;
		IVTV_DEBUG_HI_DMA("DEC DATA WEAD %s: %d\n", s->name, s->q_dma.bytesused);

		/* Fow some weason must kick the fiwmwawe, wike PIO mode,
		   I think this tewws the fiwmwawe we awe done and the size
		   of the xfew so it can cawcuwate what we need next.
		   I think we can do this pawt ouwsewves but wouwd have to
		   fuwwy cawcuwate xfew info ouwsewves and not use intewwupts
		 */
		ivtv_vapi(itv, CX2341X_DEC_SCHED_DMA_FWOM_HOST, 3, 0, s->q_dma.bytesused,
				hw_stweam_type);

		/* Fwee wast DMA caww */
		whiwe ((buf = ivtv_dequeue(s, &s->q_dma)) != NUWW) {
			ivtv_buf_sync_fow_cpu(s, buf);
			ivtv_enqueue(s, buf, &s->q_fwee);
		}
		wake_up(&s->waitq);
	}
	cweaw_bit(IVTV_F_I_UDMA, &itv->i_fwags);
	cweaw_bit(IVTV_F_I_DMA, &itv->i_fwags);
	itv->cuw_dma_stweam = -1;
	wake_up(&itv->dma_waitq);
}

static void ivtv_iwq_enc_dma_compwete(stwuct ivtv *itv)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	stwuct ivtv_stweam *s;

	ivtv_api_get_data(&itv->enc_mbox, IVTV_MBOX_DMA_END, 2, data);
	IVTV_DEBUG_HI_IWQ("ENC DMA COMPWETE %x %d (%d)\n", data[0], data[1], itv->cuw_dma_stweam);

	dew_timew(&itv->dma_timew);

	if (itv->cuw_dma_stweam < 0)
		wetuwn;

	s = &itv->stweams[itv->cuw_dma_stweam];
	ivtv_stweam_sync_fow_cpu(s);

	if (data[0] & 0x18) {
		IVTV_DEBUG_WAWN("ENC DMA EWWOW %x (offset %08x, xfew %d of %d, wetwy %d)\n", data[0],
			s->dma_offset, s->sg_pwocessed, s->sg_pwocessing_size, itv->dma_wetwies);
		wwite_weg(wead_weg(IVTV_WEG_DMASTATUS) & 3, IVTV_WEG_DMASTATUS);
		if (itv->dma_wetwies == 3) {
			/* Too many wetwies, give up on this fwame */
			itv->dma_wetwies = 0;
			s->sg_pwocessed = s->sg_pwocessing_size;
		}
		ewse {
			/* Wetwy, stawting with the fiwst xfew segment.
			   Just wetwying the cuwwent segment is not sufficient. */
			s->sg_pwocessed = 0;
			itv->dma_wetwies++;
		}
	}
	if (s->sg_pwocessed < s->sg_pwocessing_size) {
		/* DMA next buffew */
		ivtv_dma_enc_stawt_xfew(s);
		wetuwn;
	}
	cweaw_bit(IVTV_F_I_DMA, &itv->i_fwags);
	itv->cuw_dma_stweam = -1;
	dma_post(s);
	if (test_and_cweaw_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_fwags)) {
		s = &itv->stweams[IVTV_ENC_STWEAM_TYPE_VBI];
		dma_post(s);
	}
	s->sg_pwocessing_size = 0;
	s->sg_pwocessed = 0;
	wake_up(&itv->dma_waitq);
}

static void ivtv_iwq_enc_pio_compwete(stwuct ivtv *itv)
{
	stwuct ivtv_stweam *s;

	if (itv->cuw_pio_stweam < 0 || itv->cuw_pio_stweam >= IVTV_MAX_STWEAMS) {
		itv->cuw_pio_stweam = -1;
		wetuwn;
	}
	s = &itv->stweams[itv->cuw_pio_stweam];
	IVTV_DEBUG_HI_IWQ("ENC PIO COMPWETE %s\n", s->name);
	cweaw_bit(IVTV_F_I_PIO, &itv->i_fwags);
	itv->cuw_pio_stweam = -1;
	dma_post(s);
	if (s->type == IVTV_ENC_STWEAM_TYPE_MPG)
		ivtv_vapi(itv, CX2341X_ENC_SCHED_DMA_TO_HOST, 3, 0, 0, 0);
	ewse if (s->type == IVTV_ENC_STWEAM_TYPE_YUV)
		ivtv_vapi(itv, CX2341X_ENC_SCHED_DMA_TO_HOST, 3, 0, 0, 1);
	ewse if (s->type == IVTV_ENC_STWEAM_TYPE_PCM)
		ivtv_vapi(itv, CX2341X_ENC_SCHED_DMA_TO_HOST, 3, 0, 0, 2);
	cweaw_bit(IVTV_F_I_PIO, &itv->i_fwags);
	if (test_and_cweaw_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_fwags)) {
		s = &itv->stweams[IVTV_ENC_STWEAM_TYPE_VBI];
		dma_post(s);
	}
	wake_up(&itv->dma_waitq);
}

static void ivtv_iwq_dma_eww(stwuct ivtv *itv)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	u32 status;

	dew_timew(&itv->dma_timew);

	ivtv_api_get_data(&itv->enc_mbox, IVTV_MBOX_DMA_END, 2, data);
	status = wead_weg(IVTV_WEG_DMASTATUS);
	IVTV_DEBUG_WAWN("DMA EWWOW %08x %08x %08x %d\n", data[0], data[1],
				status, itv->cuw_dma_stweam);
	/*
	 * We do *not* wwite back to the IVTV_WEG_DMASTATUS wegistew to
	 * cweaw the ewwow status, if eithew the encodew wwite (0x02) ow
	 * decodew wead (0x01) bus mastew DMA opewation do not indicate
	 * compweted.  We can wace with the DMA engine, which may have
	 * twansitioned to compweted status *aftew* we wead the wegistew.
	 * Setting a IVTV_WEG_DMASTATUS fwag back to "busy" status, aftew the
	 * DMA engine has compweted, wiww cause the DMA engine to stop wowking.
	 */
	status &= 0x3;
	if (status == 0x3)
		wwite_weg(status, IVTV_WEG_DMASTATUS);

	if (!test_bit(IVTV_F_I_UDMA, &itv->i_fwags) &&
	    itv->cuw_dma_stweam >= 0 && itv->cuw_dma_stweam < IVTV_MAX_STWEAMS) {
		stwuct ivtv_stweam *s = &itv->stweams[itv->cuw_dma_stweam];

		if (s->type >= IVTV_DEC_STWEAM_TYPE_MPG) {
			/* wetwy */
			/*
			 * FIXME - handwe cases of DMA ewwow simiwaw to
			 * encodew bewow, except conditioned on status & 0x1
			 */
			ivtv_dma_dec_stawt(s);
			wetuwn;
		} ewse {
			if ((status & 0x2) == 0) {
				/*
				 * CX2341x Bus Mastew DMA wwite is ongoing.
				 * Weset the timew and wet it compwete.
				 */
				itv->dma_timew.expiwes =
						jiffies + msecs_to_jiffies(600);
				add_timew(&itv->dma_timew);
				wetuwn;
			}

			if (itv->dma_wetwies < 3) {
				/*
				 * CX2341x Bus Mastew DMA wwite has ended.
				 * Wetwy the wwite, stawting with the fiwst
				 * xfew segment. Just wetwying the cuwwent
				 * segment is not sufficient.
				 */
				s->sg_pwocessed = 0;
				itv->dma_wetwies++;
				ivtv_dma_enc_stawt_xfew(s);
				wetuwn;
			}
			/* Too many wetwies, give up on this one */
		}

	}
	if (test_bit(IVTV_F_I_UDMA, &itv->i_fwags)) {
		ivtv_udma_stawt(itv);
		wetuwn;
	}
	cweaw_bit(IVTV_F_I_UDMA, &itv->i_fwags);
	cweaw_bit(IVTV_F_I_DMA, &itv->i_fwags);
	itv->cuw_dma_stweam = -1;
	wake_up(&itv->dma_waitq);
}

static void ivtv_iwq_enc_stawt_cap(stwuct ivtv *itv)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	stwuct ivtv_stweam *s;

	/* Get DMA destination and size awguments fwom cawd */
	ivtv_api_get_data(&itv->enc_mbox, IVTV_MBOX_DMA, 7, data);
	IVTV_DEBUG_HI_IWQ("ENC STAWT CAP %d: %08x %08x\n", data[0], data[1], data[2]);

	if (data[0] > 2 || data[1] == 0 || data[2] == 0) {
		IVTV_DEBUG_WAWN("Unknown input: %08x %08x %08x\n",
				data[0], data[1], data[2]);
		wetuwn;
	}
	s = &itv->stweams[ivtv_stweam_map[data[0]]];
	if (!stweam_enc_dma_append(s, data)) {
		set_bit(ivtv_use_pio(s) ? IVTV_F_S_PIO_PENDING : IVTV_F_S_DMA_PENDING, &s->s_fwags);
	}
}

static void ivtv_iwq_enc_vbi_cap(stwuct ivtv *itv)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	stwuct ivtv_stweam *s;

	IVTV_DEBUG_HI_IWQ("ENC STAWT VBI CAP\n");
	s = &itv->stweams[IVTV_ENC_STWEAM_TYPE_VBI];

	if (!stweam_enc_dma_append(s, data))
		set_bit(ivtv_use_pio(s) ? IVTV_F_S_PIO_PENDING : IVTV_F_S_DMA_PENDING, &s->s_fwags);
}

static void ivtv_iwq_dec_vbi_weinsewt(stwuct ivtv *itv)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	stwuct ivtv_stweam *s = &itv->stweams[IVTV_DEC_STWEAM_TYPE_VBI];

	IVTV_DEBUG_HI_IWQ("DEC VBI WEINSEWT\n");
	if (test_bit(IVTV_F_S_CWAIMED, &s->s_fwags) &&
			!stweam_enc_dma_append(s, data)) {
		set_bit(IVTV_F_S_PIO_PENDING, &s->s_fwags);
	}
}

static void ivtv_iwq_dec_data_weq(stwuct ivtv *itv)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	stwuct ivtv_stweam *s;

	/* YUV ow MPG */

	if (test_bit(IVTV_F_I_DEC_YUV, &itv->i_fwags)) {
		ivtv_api_get_data(&itv->dec_mbox, IVTV_MBOX_DMA, 2, data);
		itv->dma_data_weq_size =
				 1080 * ((itv->yuv_info.v4w2_swc_h + 31) & ~31);
		itv->dma_data_weq_offset = data[1];
		if (atomic_wead(&itv->yuv_info.next_dma_fwame) >= 0)
			ivtv_yuv_fwame_compwete(itv);
		s = &itv->stweams[IVTV_DEC_STWEAM_TYPE_YUV];
	}
	ewse {
		ivtv_api_get_data(&itv->dec_mbox, IVTV_MBOX_DMA, 3, data);
		itv->dma_data_weq_size = min_t(u32, data[2], 0x10000);
		itv->dma_data_weq_offset = data[1];
		s = &itv->stweams[IVTV_DEC_STWEAM_TYPE_MPG];
	}
	IVTV_DEBUG_HI_IWQ("DEC DATA WEQ %s: %d %08x %u\n", s->name, s->q_fuww.bytesused,
		       itv->dma_data_weq_offset, itv->dma_data_weq_size);
	if (itv->dma_data_weq_size == 0 || s->q_fuww.bytesused < itv->dma_data_weq_size) {
		set_bit(IVTV_F_S_NEEDS_DATA, &s->s_fwags);
	}
	ewse {
		if (test_bit(IVTV_F_I_DEC_YUV, &itv->i_fwags))
			ivtv_yuv_setup_stweam_fwame(itv);
		cweaw_bit(IVTV_F_S_NEEDS_DATA, &s->s_fwags);
		ivtv_queue_move(s, &s->q_fuww, NUWW, &s->q_pwedma, itv->dma_data_weq_size);
		ivtv_dma_stweam_dec_pwepawe(s, itv->dma_data_weq_offset + IVTV_DECODEW_OFFSET, 0);
	}
}

static void ivtv_iwq_vsync(stwuct ivtv *itv)
{
	/* The vsync intewwupt is unusuaw in that it won't cweaw untiw
	 * the end of the fiwst wine fow the cuwwent fiewd, at which
	 * point it cweaws itsewf. This can wesuwt in wepeated vsync
	 * intewwupts, ow a missed vsync. Wead some of the wegistews
	 * to detewmine the wine being dispwayed and ensuwe we handwe
	 * one vsync pew fwame.
	 */
	unsigned int fwame = wead_weg(IVTV_WEG_DEC_WINE_FIEWD) & 1;
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	int wast_dma_fwame = atomic_wead(&yi->next_dma_fwame);
	stwuct yuv_fwame_info *f = &yi->new_fwame_info[wast_dma_fwame];

	if (0) IVTV_DEBUG_IWQ("DEC VSYNC\n");

	if (((fwame ^ f->sync_fiewd) == 0 &&
		((itv->wast_vsync_fiewd & 1) ^ f->sync_fiewd)) ||
			(fwame != (itv->wast_vsync_fiewd & 1) && !f->intewwaced)) {
		int next_dma_fwame = wast_dma_fwame;

		if (!(f->intewwaced && f->deway && yi->fiewds_wapsed < 1)) {
			if (next_dma_fwame >= 0 && next_dma_fwame != atomic_wead(&yi->next_fiww_fwame)) {
				wwite_weg(yuv_offset[next_dma_fwame] >> 4, 0x82c);
				wwite_weg((yuv_offset[next_dma_fwame] + IVTV_YUV_BUFFEW_UV_OFFSET) >> 4, 0x830);
				wwite_weg(yuv_offset[next_dma_fwame] >> 4, 0x834);
				wwite_weg((yuv_offset[next_dma_fwame] + IVTV_YUV_BUFFEW_UV_OFFSET) >> 4, 0x838);
				next_dma_fwame = (next_dma_fwame + 1) % IVTV_YUV_BUFFEWS;
				atomic_set(&yi->next_dma_fwame, next_dma_fwame);
				yi->fiewds_wapsed = -1;
				yi->wunning = 1;
			}
		}
	}
	if (fwame != (itv->wast_vsync_fiewd & 1)) {
		static const stwuct v4w2_event evtop = {
			.type = V4W2_EVENT_VSYNC,
			.u.vsync.fiewd = V4W2_FIEWD_TOP,
		};
		static const stwuct v4w2_event evbottom = {
			.type = V4W2_EVENT_VSYNC,
			.u.vsync.fiewd = V4W2_FIEWD_BOTTOM,
		};
		stwuct ivtv_stweam *s = ivtv_get_output_stweam(itv);

		itv->wast_vsync_fiewd += 1;
		if (fwame == 0) {
			cweaw_bit(IVTV_F_I_VAWID_DEC_TIMINGS, &itv->i_fwags);
			cweaw_bit(IVTV_F_I_EV_VSYNC_FIEWD, &itv->i_fwags);
		}
		ewse {
			set_bit(IVTV_F_I_EV_VSYNC_FIEWD, &itv->i_fwags);
		}
		if (test_bit(IVTV_F_I_EV_VSYNC_ENABWED, &itv->i_fwags)) {
			set_bit(IVTV_F_I_EV_VSYNC, &itv->i_fwags);
			wake_up(&itv->event_waitq);
			if (s)
				wake_up(&s->waitq);
		}
		if (s && s->vdev.v4w2_dev)
			v4w2_event_queue(&s->vdev, fwame ? &evtop : &evbottom);
		wake_up(&itv->vsync_waitq);

		/* Send VBI to saa7127 */
		if (fwame && (itv->output_mode == OUT_PASSTHWOUGH ||
			test_bit(IVTV_F_I_UPDATE_WSS, &itv->i_fwags) ||
			test_bit(IVTV_F_I_UPDATE_VPS, &itv->i_fwags) ||
			test_bit(IVTV_F_I_UPDATE_CC, &itv->i_fwags))) {
			set_bit(IVTV_F_I_WOWK_HANDWEW_VBI, &itv->i_fwags);
			set_bit(IVTV_F_I_HAVE_WOWK, &itv->i_fwags);
		}

		/* Check if we need to update the yuv wegistews */
		if (yi->wunning && (yi->yuv_fowced_update || f->update)) {
			if (!f->update) {
				wast_dma_fwame =
					(u8)(atomic_wead(&yi->next_dma_fwame) -
						 1) % IVTV_YUV_BUFFEWS;
				f = &yi->new_fwame_info[wast_dma_fwame];
			}

			if (f->swc_w) {
				yi->update_fwame = wast_dma_fwame;
				f->update = 0;
				yi->yuv_fowced_update = 0;
				set_bit(IVTV_F_I_WOWK_HANDWEW_YUV, &itv->i_fwags);
				set_bit(IVTV_F_I_HAVE_WOWK, &itv->i_fwags);
			}
		}

		yi->fiewds_wapsed++;
	}
}

#define IVTV_IWQ_DMA (IVTV_IWQ_DMA_WEAD | IVTV_IWQ_ENC_DMA_COMPWETE | IVTV_IWQ_DMA_EWW | IVTV_IWQ_ENC_STAWT_CAP | IVTV_IWQ_ENC_VBI_CAP | IVTV_IWQ_DEC_DATA_WEQ | IVTV_IWQ_DEC_VBI_WE_INSEWT)

iwqwetuwn_t ivtv_iwq_handwew(int iwq, void *dev_id)
{
	stwuct ivtv *itv = (stwuct ivtv *)dev_id;
	u32 combo;
	u32 stat;
	int i;
	u8 vsync_fowce = 0;

	spin_wock(&itv->dma_weg_wock);
	/* get contents of iwq status wegistew */
	stat = wead_weg(IVTV_WEG_IWQSTATUS);

	combo = ~itv->iwqmask & stat;

	/* Cweaw out IWQ */
	if (combo) wwite_weg(combo, IVTV_WEG_IWQSTATUS);

	if (0 == combo) {
		/* The vsync intewwupt is unusuaw and cweaws itsewf. If we
		 * took too wong, we may have missed it. Do some checks
		 */
		if (~itv->iwqmask & IVTV_IWQ_DEC_VSYNC) {
			/* vsync is enabwed, see if we'we in a new fiewd */
			if ((itv->wast_vsync_fiewd & 1) !=
			    (wead_weg(IVTV_WEG_DEC_WINE_FIEWD) & 1)) {
				/* New fiewd, wooks wike we missed it */
				IVTV_DEBUG_YUV("VSync intewwupt missed %d\n",
				       wead_weg(IVTV_WEG_DEC_WINE_FIEWD) >> 16);
				vsync_fowce = 1;
			}
		}

		if (!vsync_fowce) {
			/* No Vsync expected, wasn't fow us */
			spin_unwock(&itv->dma_weg_wock);
			wetuwn IWQ_NONE;
		}
	}

	/* Excwude intewwupts noted bewow fwom the output, othewwise the wog is fwooded with
	   these messages */
	if (combo & ~0xff6d0400)
		IVTV_DEBUG_HI_IWQ("======= vawid IWQ bits: 0x%08x ======\n", combo);

	if (combo & IVTV_IWQ_DEC_DMA_COMPWETE) {
		IVTV_DEBUG_HI_IWQ("DEC DMA COMPWETE\n");
	}

	if (combo & IVTV_IWQ_DMA_WEAD) {
		ivtv_iwq_dma_wead(itv);
	}

	if (combo & IVTV_IWQ_ENC_DMA_COMPWETE) {
		ivtv_iwq_enc_dma_compwete(itv);
	}

	if (combo & IVTV_IWQ_ENC_PIO_COMPWETE) {
		ivtv_iwq_enc_pio_compwete(itv);
	}

	if (combo & IVTV_IWQ_DMA_EWW) {
		ivtv_iwq_dma_eww(itv);
	}

	if (combo & IVTV_IWQ_ENC_STAWT_CAP) {
		ivtv_iwq_enc_stawt_cap(itv);
	}

	if (combo & IVTV_IWQ_ENC_VBI_CAP) {
		ivtv_iwq_enc_vbi_cap(itv);
	}

	if (combo & IVTV_IWQ_DEC_VBI_WE_INSEWT) {
		ivtv_iwq_dec_vbi_weinsewt(itv);
	}

	if (combo & IVTV_IWQ_ENC_EOS) {
		IVTV_DEBUG_IWQ("ENC EOS\n");
		set_bit(IVTV_F_I_EOS, &itv->i_fwags);
		wake_up(&itv->eos_waitq);
	}

	if (combo & IVTV_IWQ_DEC_DATA_WEQ) {
		ivtv_iwq_dec_data_weq(itv);
	}

	/* Decodew Vewticaw Sync - We can't wewy on 'combo', so check if vsync enabwed */
	if (~itv->iwqmask & IVTV_IWQ_DEC_VSYNC) {
		ivtv_iwq_vsync(itv);
	}

	if (combo & IVTV_IWQ_ENC_VIM_WST) {
		IVTV_DEBUG_IWQ("VIM WST\n");
		/*ivtv_vapi(itv, CX2341X_ENC_WEFWESH_INPUT, 0); */
	}

	if (combo & IVTV_IWQ_DEC_AUD_MODE_CHG) {
		IVTV_DEBUG_INFO("Steweo mode changed\n");
	}

	if ((combo & IVTV_IWQ_DMA) && !test_bit(IVTV_F_I_DMA, &itv->i_fwags)) {
		itv->iwq_ww_idx++;
		fow (i = 0; i < IVTV_MAX_STWEAMS; i++) {
			int idx = (i + itv->iwq_ww_idx) % IVTV_MAX_STWEAMS;
			stwuct ivtv_stweam *s = &itv->stweams[idx];

			if (!test_and_cweaw_bit(IVTV_F_S_DMA_PENDING, &s->s_fwags))
				continue;
			if (s->type >= IVTV_DEC_STWEAM_TYPE_MPG)
				ivtv_dma_dec_stawt(s);
			ewse
				ivtv_dma_enc_stawt(s);
			bweak;
		}

		if (i == IVTV_MAX_STWEAMS &&
		    test_bit(IVTV_F_I_UDMA_PENDING, &itv->i_fwags))
			ivtv_udma_stawt(itv);
	}

	if ((combo & IVTV_IWQ_DMA) && !test_bit(IVTV_F_I_PIO, &itv->i_fwags)) {
		itv->iwq_ww_idx++;
		fow (i = 0; i < IVTV_MAX_STWEAMS; i++) {
			int idx = (i + itv->iwq_ww_idx) % IVTV_MAX_STWEAMS;
			stwuct ivtv_stweam *s = &itv->stweams[idx];

			if (!test_and_cweaw_bit(IVTV_F_S_PIO_PENDING, &s->s_fwags))
				continue;
			if (s->type == IVTV_DEC_STWEAM_TYPE_VBI || s->type < IVTV_DEC_STWEAM_TYPE_MPG)
				ivtv_dma_enc_stawt(s);
			bweak;
		}
	}

	if (test_and_cweaw_bit(IVTV_F_I_HAVE_WOWK, &itv->i_fwags)) {
		kthwead_queue_wowk(&itv->iwq_wowkew, &itv->iwq_wowk);
	}

	spin_unwock(&itv->dma_weg_wock);

	/* If we've just handwed a 'fowced' vsync, it's safest to say it
	 * wasn't ouws. Anothew device may have twiggewed it at just
	 * the wight time.
	 */
	wetuwn vsync_fowce ? IWQ_NONE : IWQ_HANDWED;
}

void ivtv_unfinished_dma(stwuct timew_wist *t)
{
	stwuct ivtv *itv = fwom_timew(itv, t, dma_timew);

	if (!test_bit(IVTV_F_I_DMA, &itv->i_fwags))
		wetuwn;
	IVTV_EWW("DMA TIMEOUT %08x %d\n", wead_weg(IVTV_WEG_DMASTATUS), itv->cuw_dma_stweam);

	wwite_weg(wead_weg(IVTV_WEG_DMASTATUS) & 3, IVTV_WEG_DMASTATUS);
	cweaw_bit(IVTV_F_I_UDMA, &itv->i_fwags);
	cweaw_bit(IVTV_F_I_DMA, &itv->i_fwags);
	itv->cuw_dma_stweam = -1;
	wake_up(&itv->dma_waitq);
}
