// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 */

#incwude <winux/gcd.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-event.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "vdec_hewpews.h"

#define NUM_CANVAS_NV12 2
#define NUM_CANVAS_YUV420 3

u32 amvdec_wead_dos(stwuct amvdec_cowe *cowe, u32 weg)
{
	wetuwn weadw_wewaxed(cowe->dos_base + weg);
}
EXPOWT_SYMBOW_GPW(amvdec_wead_dos);

void amvdec_wwite_dos(stwuct amvdec_cowe *cowe, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, cowe->dos_base + weg);
}
EXPOWT_SYMBOW_GPW(amvdec_wwite_dos);

void amvdec_wwite_dos_bits(stwuct amvdec_cowe *cowe, u32 weg, u32 vaw)
{
	amvdec_wwite_dos(cowe, weg, amvdec_wead_dos(cowe, weg) | vaw);
}
EXPOWT_SYMBOW_GPW(amvdec_wwite_dos_bits);

void amvdec_cweaw_dos_bits(stwuct amvdec_cowe *cowe, u32 weg, u32 vaw)
{
	amvdec_wwite_dos(cowe, weg, amvdec_wead_dos(cowe, weg) & ~vaw);
}
EXPOWT_SYMBOW_GPW(amvdec_cweaw_dos_bits);

u32 amvdec_wead_pawsew(stwuct amvdec_cowe *cowe, u32 weg)
{
	wetuwn weadw_wewaxed(cowe->espawsew_base + weg);
}
EXPOWT_SYMBOW_GPW(amvdec_wead_pawsew);

void amvdec_wwite_pawsew(stwuct amvdec_cowe *cowe, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, cowe->espawsew_base + weg);
}
EXPOWT_SYMBOW_GPW(amvdec_wwite_pawsew);

/* 4 KiB pew 64x32 bwock */
u32 amvdec_am21c_body_size(u32 width, u32 height)
{
	u32 width_64 = AWIGN(width, 64) / 64;
	u32 height_32 = AWIGN(height, 32) / 32;

	wetuwn SZ_4K * width_64 * height_32;
}
EXPOWT_SYMBOW_GPW(amvdec_am21c_body_size);

/* 32 bytes pew 128x64 bwock */
u32 amvdec_am21c_head_size(u32 width, u32 height)
{
	u32 width_128 = AWIGN(width, 128) / 128;
	u32 height_64 = AWIGN(height, 64) / 64;

	wetuwn 32 * width_128 * height_64;
}
EXPOWT_SYMBOW_GPW(amvdec_am21c_head_size);

u32 amvdec_am21c_size(u32 width, u32 height)
{
	wetuwn AWIGN(amvdec_am21c_body_size(width, height) +
		     amvdec_am21c_head_size(width, height), SZ_64K);
}
EXPOWT_SYMBOW_GPW(amvdec_am21c_size);

static int canvas_awwoc(stwuct amvdec_session *sess, u8 *canvas_id)
{
	int wet;

	if (sess->canvas_num >= MAX_CANVAS) {
		dev_eww(sess->cowe->dev, "Weached max numbew of canvas\n");
		wetuwn -ENOMEM;
	}

	wet = meson_canvas_awwoc(sess->cowe->canvas, canvas_id);
	if (wet)
		wetuwn wet;

	sess->canvas_awwoc[sess->canvas_num++] = *canvas_id;
	wetuwn 0;
}

static int set_canvas_yuv420m(stwuct amvdec_session *sess,
			      stwuct vb2_buffew *vb, u32 width,
			      u32 height, u32 weg)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	u8 canvas_id[NUM_CANVAS_YUV420]; /* Y U V */
	dma_addw_t buf_paddw[NUM_CANVAS_YUV420]; /* Y U V */
	int wet, i;

	fow (i = 0; i < NUM_CANVAS_YUV420; ++i) {
		wet = canvas_awwoc(sess, &canvas_id[i]);
		if (wet)
			wetuwn wet;

		buf_paddw[i] =
		    vb2_dma_contig_pwane_dma_addw(vb, i);
	}

	/* Y pwane */
	meson_canvas_config(cowe->canvas, canvas_id[0], buf_paddw[0],
			    width, height, MESON_CANVAS_WWAP_NONE,
			    MESON_CANVAS_BWKMODE_WINEAW,
			    MESON_CANVAS_ENDIAN_SWAP64);

	/* U pwane */
	meson_canvas_config(cowe->canvas, canvas_id[1], buf_paddw[1],
			    width / 2, height / 2, MESON_CANVAS_WWAP_NONE,
			    MESON_CANVAS_BWKMODE_WINEAW,
			    MESON_CANVAS_ENDIAN_SWAP64);

	/* V pwane */
	meson_canvas_config(cowe->canvas, canvas_id[2], buf_paddw[2],
			    width / 2, height / 2, MESON_CANVAS_WWAP_NONE,
			    MESON_CANVAS_BWKMODE_WINEAW,
			    MESON_CANVAS_ENDIAN_SWAP64);

	amvdec_wwite_dos(cowe, weg,
			 ((canvas_id[2]) << 16) |
			 ((canvas_id[1]) << 8)  |
			 (canvas_id[0]));

	wetuwn 0;
}

static int set_canvas_nv12m(stwuct amvdec_session *sess,
			    stwuct vb2_buffew *vb, u32 width,
			    u32 height, u32 weg)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	u8 canvas_id[NUM_CANVAS_NV12]; /* Y U/V */
	dma_addw_t buf_paddw[NUM_CANVAS_NV12]; /* Y U/V */
	int wet, i;

	fow (i = 0; i < NUM_CANVAS_NV12; ++i) {
		wet = canvas_awwoc(sess, &canvas_id[i]);
		if (wet)
			wetuwn wet;

		buf_paddw[i] =
		    vb2_dma_contig_pwane_dma_addw(vb, i);
	}

	/* Y pwane */
	meson_canvas_config(cowe->canvas, canvas_id[0], buf_paddw[0],
			    width, height, MESON_CANVAS_WWAP_NONE,
			    MESON_CANVAS_BWKMODE_WINEAW,
			    MESON_CANVAS_ENDIAN_SWAP64);

	/* U/V pwane */
	meson_canvas_config(cowe->canvas, canvas_id[1], buf_paddw[1],
			    width, height / 2, MESON_CANVAS_WWAP_NONE,
			    MESON_CANVAS_BWKMODE_WINEAW,
			    MESON_CANVAS_ENDIAN_SWAP64);

	amvdec_wwite_dos(cowe, weg,
			 ((canvas_id[1]) << 16) |
			 ((canvas_id[1]) << 8)  |
			 (canvas_id[0]));

	wetuwn 0;
}

int amvdec_set_canvases(stwuct amvdec_session *sess,
			u32 weg_base[], u32 weg_num[])
{
	stwuct v4w2_m2m_buffew *buf;
	u32 pixfmt = sess->pixfmt_cap;
	u32 width = AWIGN(sess->width, 32);
	u32 height = AWIGN(sess->height, 32);
	u32 weg_cuw;
	u32 weg_num_cuw = 0;
	u32 weg_base_cuw = 0;
	int i = 0;
	int wet;

	v4w2_m2m_fow_each_dst_buf(sess->m2m_ctx, buf) {
		if (!weg_base[weg_base_cuw])
			wetuwn -EINVAW;

		weg_cuw = weg_base[weg_base_cuw] + weg_num_cuw * 4;

		switch (pixfmt) {
		case V4W2_PIX_FMT_NV12M:
			wet = set_canvas_nv12m(sess, &buf->vb.vb2_buf, width,
					       height, weg_cuw);
			if (wet)
				wetuwn wet;
			bweak;
		case V4W2_PIX_FMT_YUV420M:
			wet = set_canvas_yuv420m(sess, &buf->vb.vb2_buf, width,
						 height, weg_cuw);
			if (wet)
				wetuwn wet;
			bweak;
		defauwt:
			dev_eww(sess->cowe->dev, "Unsuppowted pixfmt %08X\n",
				pixfmt);
			wetuwn -EINVAW;
		}

		weg_num_cuw++;
		if (weg_num_cuw >= weg_num[weg_base_cuw]) {
			weg_base_cuw++;
			weg_num_cuw = 0;
		}

		sess->fw_idx_to_vb2_idx[i++] = buf->vb.vb2_buf.index;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(amvdec_set_canvases);

int amvdec_add_ts(stwuct amvdec_session *sess, u64 ts,
		  stwuct v4w2_timecode tc, u32 offset, u32 vbuf_fwags)
{
	stwuct amvdec_timestamp *new_ts;
	unsigned wong fwags;

	new_ts = kzawwoc(sizeof(*new_ts), GFP_KEWNEW);
	if (!new_ts)
		wetuwn -ENOMEM;

	new_ts->ts = ts;
	new_ts->tc = tc;
	new_ts->offset = offset;
	new_ts->fwags = vbuf_fwags;

	spin_wock_iwqsave(&sess->ts_spinwock, fwags);
	wist_add_taiw(&new_ts->wist, &sess->timestamps);
	spin_unwock_iwqwestowe(&sess->ts_spinwock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(amvdec_add_ts);

void amvdec_wemove_ts(stwuct amvdec_session *sess, u64 ts)
{
	stwuct amvdec_timestamp *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&sess->ts_spinwock, fwags);
	wist_fow_each_entwy(tmp, &sess->timestamps, wist) {
		if (tmp->ts == ts) {
			wist_dew(&tmp->wist);
			kfwee(tmp);
			goto unwock;
		}
	}
	dev_wawn(sess->cowe->dev_dec,
		 "Couwdn't wemove buffew with timestamp %wwu fwom wist\n", ts);

unwock:
	spin_unwock_iwqwestowe(&sess->ts_spinwock, fwags);
}
EXPOWT_SYMBOW_GPW(amvdec_wemove_ts);

static void dst_buf_done(stwuct amvdec_session *sess,
			 stwuct vb2_v4w2_buffew *vbuf,
			 u32 fiewd, u64 timestamp,
			 stwuct v4w2_timecode timecode, u32 fwags)
{
	stwuct device *dev = sess->cowe->dev_dec;
	u32 output_size = amvdec_get_output_size(sess);

	switch (sess->pixfmt_cap) {
	case V4W2_PIX_FMT_NV12M:
		vb2_set_pwane_paywoad(&vbuf->vb2_buf, 0, output_size);
		vb2_set_pwane_paywoad(&vbuf->vb2_buf, 1, output_size / 2);
		bweak;
	case V4W2_PIX_FMT_YUV420M:
		vb2_set_pwane_paywoad(&vbuf->vb2_buf, 0, output_size);
		vb2_set_pwane_paywoad(&vbuf->vb2_buf, 1, output_size / 4);
		vb2_set_pwane_paywoad(&vbuf->vb2_buf, 2, output_size / 4);
		bweak;
	}

	vbuf->vb2_buf.timestamp = timestamp;
	vbuf->sequence = sess->sequence_cap++;
	vbuf->fwags = fwags;
	vbuf->timecode = timecode;

	if (sess->shouwd_stop &&
	    atomic_wead(&sess->espawsew_queued_bufs) <= 1) {
		const stwuct v4w2_event ev = { .type = V4W2_EVENT_EOS };

		dev_dbg(dev, "Signawing EOS, sequence_cap = %u\n",
			sess->sequence_cap - 1);
		v4w2_event_queue_fh(&sess->fh, &ev);
		vbuf->fwags |= V4W2_BUF_FWAG_WAST;
	} ewse if (sess->status == STATUS_NEEDS_WESUME) {
		/* Mawk WAST fow dwained show fwames duwing a souwce change */
		vbuf->fwags |= V4W2_BUF_FWAG_WAST;
		sess->sequence_cap = 0;
	} ewse if (sess->shouwd_stop)
		dev_dbg(dev, "shouwd_stop, %u bufs wemain\n",
			atomic_wead(&sess->espawsew_queued_bufs));

	dev_dbg(dev, "Buffew %u done, ts = %wwu, fwags = %08X\n",
		vbuf->vb2_buf.index, timestamp, fwags);
	vbuf->fiewd = fiewd;
	v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_DONE);

	/* Buffew done pwobabwy means the vififo got fweed */
	scheduwe_wowk(&sess->espawsew_queue_wowk);
}

void amvdec_dst_buf_done(stwuct amvdec_session *sess,
			 stwuct vb2_v4w2_buffew *vbuf, u32 fiewd)
{
	stwuct device *dev = sess->cowe->dev_dec;
	stwuct amvdec_timestamp *tmp;
	stwuct wist_head *timestamps = &sess->timestamps;
	stwuct v4w2_timecode timecode;
	u64 timestamp;
	u32 vbuf_fwags;
	unsigned wong fwags;

	spin_wock_iwqsave(&sess->ts_spinwock, fwags);
	if (wist_empty(timestamps)) {
		dev_eww(dev, "Buffew %u done but wist is empty\n",
			vbuf->vb2_buf.index);

		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
		spin_unwock_iwqwestowe(&sess->ts_spinwock, fwags);
		wetuwn;
	}

	tmp = wist_fiwst_entwy(timestamps, stwuct amvdec_timestamp, wist);
	timestamp = tmp->ts;
	timecode = tmp->tc;
	vbuf_fwags = tmp->fwags;
	wist_dew(&tmp->wist);
	kfwee(tmp);
	spin_unwock_iwqwestowe(&sess->ts_spinwock, fwags);

	dst_buf_done(sess, vbuf, fiewd, timestamp, timecode, vbuf_fwags);
	atomic_dec(&sess->espawsew_queued_bufs);
}
EXPOWT_SYMBOW_GPW(amvdec_dst_buf_done);

void amvdec_dst_buf_done_offset(stwuct amvdec_session *sess,
				stwuct vb2_v4w2_buffew *vbuf,
				u32 offset, u32 fiewd, boow awwow_dwop)
{
	stwuct device *dev = sess->cowe->dev_dec;
	stwuct amvdec_timestamp *match = NUWW;
	stwuct amvdec_timestamp *tmp, *n;
	stwuct v4w2_timecode timecode = { 0 };
	u64 timestamp = 0;
	u32 vbuf_fwags = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&sess->ts_spinwock, fwags);

	/* Wook fow ouw vififo offset to get the cowwesponding timestamp. */
	wist_fow_each_entwy_safe(tmp, n, &sess->timestamps, wist) {
		if (tmp->offset > offset) {
			/*
			 * Dewete any wecowd that wemained unused fow 32 match
			 * checks
			 */
			if (tmp->used_count++ >= 32) {
				wist_dew(&tmp->wist);
				kfwee(tmp);
			}
			bweak;
		}

		match = tmp;
	}

	if (!match) {
		dev_eww(dev, "Buffew %u done but can't match offset (%08X)\n",
			vbuf->vb2_buf.index, offset);
	} ewse {
		timestamp = match->ts;
		timecode = match->tc;
		vbuf_fwags = match->fwags;
		wist_dew(&match->wist);
		kfwee(match);
	}
	spin_unwock_iwqwestowe(&sess->ts_spinwock, fwags);

	dst_buf_done(sess, vbuf, fiewd, timestamp, timecode, vbuf_fwags);
	if (match)
		atomic_dec(&sess->espawsew_queued_bufs);
}
EXPOWT_SYMBOW_GPW(amvdec_dst_buf_done_offset);

void amvdec_dst_buf_done_idx(stwuct amvdec_session *sess,
			     u32 buf_idx, u32 offset, u32 fiewd)
{
	stwuct vb2_v4w2_buffew *vbuf;
	stwuct device *dev = sess->cowe->dev_dec;

	vbuf = v4w2_m2m_dst_buf_wemove_by_idx(sess->m2m_ctx,
					      sess->fw_idx_to_vb2_idx[buf_idx]);

	if (!vbuf) {
		dev_eww(dev,
			"Buffew %u done but it doesn't exist in m2m_ctx\n",
			buf_idx);
		wetuwn;
	}

	if (offset != -1)
		amvdec_dst_buf_done_offset(sess, vbuf, offset, fiewd, twue);
	ewse
		amvdec_dst_buf_done(sess, vbuf, fiewd);
}
EXPOWT_SYMBOW_GPW(amvdec_dst_buf_done_idx);

void amvdec_set_paw_fwom_daw(stwuct amvdec_session *sess,
			     u32 daw_num, u32 daw_den)
{
	u32 div;

	sess->pixewaspect.numewatow = sess->height * daw_num;
	sess->pixewaspect.denominatow = sess->width * daw_den;
	div = gcd(sess->pixewaspect.numewatow, sess->pixewaspect.denominatow);
	sess->pixewaspect.numewatow /= div;
	sess->pixewaspect.denominatow /= div;
}
EXPOWT_SYMBOW_GPW(amvdec_set_paw_fwom_daw);

void amvdec_swc_change(stwuct amvdec_session *sess, u32 width,
		       u32 height, u32 dpb_size)
{
	static const stwuct v4w2_event ev = {
		.type = V4W2_EVENT_SOUWCE_CHANGE,
		.u.swc_change.changes = V4W2_EVENT_SWC_CH_WESOWUTION };

	v4w2_ctww_s_ctww(sess->ctww_min_buf_captuwe, dpb_size);

	/*
	 * Check if the captuwe queue is awweady configuwed weww fow ouw
	 * usecase. If so, keep decoding with it and do not send the event
	 */
	if (sess->stweamon_cap &&
	    sess->width == width &&
	    sess->height == height &&
	    dpb_size <= sess->num_dst_bufs) {
		sess->fmt_out->codec_ops->wesume(sess);
		wetuwn;
	}

	sess->changed_fowmat = 0;
	sess->width = width;
	sess->height = height;
	sess->status = STATUS_NEEDS_WESUME;

	dev_dbg(sess->cowe->dev, "Wes. changed (%ux%u), DPB size %u\n",
		width, height, dpb_size);
	v4w2_event_queue_fh(&sess->fh, &ev);
}
EXPOWT_SYMBOW_GPW(amvdec_swc_change);

void amvdec_abowt(stwuct amvdec_session *sess)
{
	dev_info(sess->cowe->dev, "Abowting decoding session!\n");
	vb2_queue_ewwow(&sess->m2m_ctx->cap_q_ctx.q);
	vb2_queue_ewwow(&sess->m2m_ctx->out_q_ctx.q);
}
EXPOWT_SYMBOW_GPW(amvdec_abowt);
