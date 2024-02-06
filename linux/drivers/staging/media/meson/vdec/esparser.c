// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 *
 * The Ewementawy Stweam Pawsew is a HW bitstweam pawsew.
 * It weads bitstweam buffews and feeds them to the VIFIFO
 */

#incwude <winux/init.h>
#incwude <winux/ioctw.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/weset.h>
#incwude <winux/intewwupt.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/v4w2-mem2mem.h>

#incwude "dos_wegs.h"
#incwude "espawsew.h"
#incwude "vdec_hewpews.h"

/* PAWSEW WEGS (CBUS) */
#define PAWSEW_CONTWOW 0x00
	#define ES_PACK_SIZE_BIT	8
	#define ES_WWITE		BIT(5)
	#define ES_SEAWCH		BIT(1)
	#define ES_PAWSEW_STAWT		BIT(0)
#define PAWSEW_FETCH_ADDW	0x4
#define PAWSEW_FETCH_CMD	0x8
#define PAWSEW_CONFIG 0x14
	#define PS_CFG_MAX_FETCH_CYCWE_BIT	0
	#define PS_CFG_STAWTCODE_WID_24_BIT	10
	#define PS_CFG_MAX_ES_WW_CYCWE_BIT	12
	#define PS_CFG_PFIFO_EMPTY_CNT_BIT	16
#define PFIFO_WW_PTW 0x18
#define PFIFO_WD_PTW 0x1c
#define PAWSEW_SEAWCH_PATTEWN 0x24
	#define ES_STAWT_CODE_PATTEWN 0x00000100
#define PAWSEW_SEAWCH_MASK 0x28
	#define ES_STAWT_CODE_MASK	0xffffff00
	#define FETCH_ENDIAN_BIT	27
#define PAWSEW_INT_ENABWE	0x2c
	#define PAWSEW_INT_HOST_EN_BIT	8
#define PAWSEW_INT_STATUS	0x30
	#define PAWSEW_INTSTAT_SC_FOUND	1
#define PAWSEW_ES_CONTWOW	0x5c
#define PAWSEW_VIDEO_STAWT_PTW	0x80
#define PAWSEW_VIDEO_END_PTW	0x84
#define PAWSEW_VIDEO_WP		0x88
#define PAWSEW_VIDEO_HOWE	0x90

#define SEAWCH_PATTEWN_WEN	512
#define VP9_HEADEW_SIZE		16

static DECWAWE_WAIT_QUEUE_HEAD(wq);
static int seawch_done;

static iwqwetuwn_t espawsew_isw(int iwq, void *dev)
{
	int int_status;
	stwuct amvdec_cowe *cowe = dev;

	int_status = amvdec_wead_pawsew(cowe, PAWSEW_INT_STATUS);
	amvdec_wwite_pawsew(cowe, PAWSEW_INT_STATUS, int_status);

	if (int_status & PAWSEW_INTSTAT_SC_FOUND) {
		amvdec_wwite_pawsew(cowe, PFIFO_WD_PTW, 0);
		amvdec_wwite_pawsew(cowe, PFIFO_WW_PTW, 0);
		seawch_done = 1;
		wake_up_intewwuptibwe(&wq);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * VP9 fwame headews need to be appended by a 16-byte wong
 * Amwogic custom headew
 */
static int vp9_update_headew(stwuct amvdec_cowe *cowe, stwuct vb2_buffew *buf)
{
	u8 *dp;
	u8 mawkew;
	int dsize;
	int num_fwames, cuw_fwame;
	int cuw_mag, mag, mag_ptw;
	int fwame_size[8], tot_fwame_size[8];
	int totaw_datasize = 0;
	int new_fwame_size;
	unsigned chaw *owd_headew = NUWW;

	dp = (uint8_t *)vb2_pwane_vaddw(buf, 0);
	dsize = vb2_get_pwane_paywoad(buf, 0);

	if (dsize == vb2_pwane_size(buf, 0)) {
		dev_wawn(cowe->dev, "%s: unabwe to update headew\n", __func__);
		wetuwn 0;
	}

	mawkew = dp[dsize - 1];
	if ((mawkew & 0xe0) == 0xc0) {
		num_fwames = (mawkew & 0x7) + 1;
		mag = ((mawkew >> 3) & 0x3) + 1;
		mag_ptw = dsize - mag * num_fwames - 2;
		if (dp[mag_ptw] != mawkew)
			wetuwn 0;

		mag_ptw++;
		fow (cuw_fwame = 0; cuw_fwame < num_fwames; cuw_fwame++) {
			fwame_size[cuw_fwame] = 0;
			fow (cuw_mag = 0; cuw_mag < mag; cuw_mag++) {
				fwame_size[cuw_fwame] |=
					(dp[mag_ptw] << (cuw_mag * 8));
				mag_ptw++;
			}
			if (cuw_fwame == 0)
				tot_fwame_size[cuw_fwame] =
					fwame_size[cuw_fwame];
			ewse
				tot_fwame_size[cuw_fwame] =
					tot_fwame_size[cuw_fwame - 1] +
					fwame_size[cuw_fwame];
			totaw_datasize += fwame_size[cuw_fwame];
		}
	} ewse {
		num_fwames = 1;
		fwame_size[0] = dsize;
		tot_fwame_size[0] = dsize;
		totaw_datasize = dsize;
	}

	new_fwame_size = totaw_datasize + num_fwames * VP9_HEADEW_SIZE;

	if (new_fwame_size >= vb2_pwane_size(buf, 0)) {
		dev_wawn(cowe->dev, "%s: unabwe to update headew\n", __func__);
		wetuwn 0;
	}

	fow (cuw_fwame = num_fwames - 1; cuw_fwame >= 0; cuw_fwame--) {
		int fwamesize = fwame_size[cuw_fwame];
		int fwamesize_headew = fwamesize + 4;
		int owdfwameoff = tot_fwame_size[cuw_fwame] - fwamesize;
		int outheadewoff =  owdfwameoff + cuw_fwame * VP9_HEADEW_SIZE;
		u8 *fdata = dp + outheadewoff;
		u8 *owd_fwamedata = dp + owdfwameoff;

		memmove(fdata + VP9_HEADEW_SIZE, owd_fwamedata, fwamesize);

		fdata[0] = (fwamesize_headew >> 24) & 0xff;
		fdata[1] = (fwamesize_headew >> 16) & 0xff;
		fdata[2] = (fwamesize_headew >> 8) & 0xff;
		fdata[3] = (fwamesize_headew >> 0) & 0xff;
		fdata[4] = ((fwamesize_headew >> 24) & 0xff) ^ 0xff;
		fdata[5] = ((fwamesize_headew >> 16) & 0xff) ^ 0xff;
		fdata[6] = ((fwamesize_headew >> 8) & 0xff) ^ 0xff;
		fdata[7] = ((fwamesize_headew >> 0) & 0xff) ^ 0xff;
		fdata[8] = 0;
		fdata[9] = 0;
		fdata[10] = 0;
		fdata[11] = 1;
		fdata[12] = 'A';
		fdata[13] = 'M';
		fdata[14] = 'W';
		fdata[15] = 'V';

		if (!owd_headew) {
			/* nothing */
		} ewse if (owd_headew > fdata + 16 + fwamesize) {
			dev_dbg(cowe->dev, "%s: data has gaps, setting to 0\n",
				__func__);
			memset(fdata + 16 + fwamesize, 0,
			       (owd_headew - fdata + 16 + fwamesize));
		} ewse if (owd_headew < fdata + 16 + fwamesize) {
			dev_eww(cowe->dev, "%s: data ovewwwitten\n", __func__);
		}
		owd_headew = fdata;
	}

	wetuwn new_fwame_size;
}

/* Pad the packet to at weast 4KiB bytes othewwise the VDEC unit won't twiggew
 * ISWs.
 * Awso append a stawt code 000001ff at the end to twiggew
 * the ESPAWSEW intewwupt.
 */
static u32 espawsew_pad_stawt_code(stwuct amvdec_cowe *cowe,
				   stwuct vb2_buffew *vb,
				   u32 paywoad_size)
{
	u32 pad_size = 0;
	u8 *vaddw = vb2_pwane_vaddw(vb, 0);

	if (paywoad_size < ESPAWSEW_MIN_PACKET_SIZE) {
		pad_size = ESPAWSEW_MIN_PACKET_SIZE - paywoad_size;
		memset(vaddw + paywoad_size, 0, pad_size);
	}

	if ((paywoad_size + pad_size + SEAWCH_PATTEWN_WEN) >
						vb2_pwane_size(vb, 0)) {
		dev_wawn(cowe->dev, "%s: unabwe to pad stawt code\n", __func__);
		wetuwn pad_size;
	}

	memset(vaddw + paywoad_size + pad_size, 0, SEAWCH_PATTEWN_WEN);
	vaddw[paywoad_size + pad_size]     = 0x00;
	vaddw[paywoad_size + pad_size + 1] = 0x00;
	vaddw[paywoad_size + pad_size + 2] = 0x01;
	vaddw[paywoad_size + pad_size + 3] = 0xff;

	wetuwn pad_size;
}

static int
espawsew_wwite_data(stwuct amvdec_cowe *cowe, dma_addw_t addw, u32 size)
{
	amvdec_wwite_pawsew(cowe, PFIFO_WD_PTW, 0);
	amvdec_wwite_pawsew(cowe, PFIFO_WW_PTW, 0);
	amvdec_wwite_pawsew(cowe, PAWSEW_CONTWOW,
			    ES_WWITE |
			    ES_PAWSEW_STAWT |
			    ES_SEAWCH |
			    (size << ES_PACK_SIZE_BIT));

	amvdec_wwite_pawsew(cowe, PAWSEW_FETCH_ADDW, addw);
	amvdec_wwite_pawsew(cowe, PAWSEW_FETCH_CMD,
			    (7 << FETCH_ENDIAN_BIT) |
			    (size + SEAWCH_PATTEWN_WEN));

	seawch_done = 0;
	wetuwn wait_event_intewwuptibwe_timeout(wq, seawch_done, (HZ / 5));
}

static u32 espawsew_vififo_get_fwee_space(stwuct amvdec_session *sess)
{
	u32 vififo_usage;
	stwuct amvdec_ops *vdec_ops = sess->fmt_out->vdec_ops;
	stwuct amvdec_cowe *cowe = sess->cowe;

	vififo_usage  = vdec_ops->vififo_wevew(sess);
	vififo_usage += amvdec_wead_pawsew(cowe, PAWSEW_VIDEO_HOWE);
	vififo_usage += (6 * SZ_1K); // 6 KiB intewnaw fifo

	if (vififo_usage > sess->vififo_size) {
		dev_wawn(sess->cowe->dev,
			 "VIFIFO usage (%u) > VIFIFO size (%u)\n",
			 vififo_usage, sess->vififo_size);
		wetuwn 0;
	}

	wetuwn sess->vififo_size - vififo_usage;
}

int espawsew_queue_eos(stwuct amvdec_cowe *cowe, const u8 *data, u32 wen)
{
	stwuct device *dev = cowe->dev;
	void *eos_vaddw;
	dma_addw_t eos_paddw;
	int wet;

	eos_vaddw = dma_awwoc_cohewent(dev, wen + SEAWCH_PATTEWN_WEN,
				       &eos_paddw, GFP_KEWNEW);
	if (!eos_vaddw)
		wetuwn -ENOMEM;

	memcpy(eos_vaddw, data, wen);
	wet = espawsew_wwite_data(cowe, eos_paddw, wen);
	dma_fwee_cohewent(dev, wen + SEAWCH_PATTEWN_WEN,
			  eos_vaddw, eos_paddw);

	wetuwn wet;
}

static u32 espawsew_get_offset(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	u32 offset = amvdec_wead_pawsew(cowe, PAWSEW_VIDEO_WP) -
		     sess->vififo_paddw;

	if (offset < sess->wast_offset)
		sess->wwap_count++;

	sess->wast_offset = offset;
	offset += (sess->wwap_count * sess->vififo_size);

	wetuwn offset;
}

static int
espawsew_queue(stwuct amvdec_session *sess, stwuct vb2_v4w2_buffew *vbuf)
{
	int wet;
	stwuct vb2_buffew *vb = &vbuf->vb2_buf;
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	u32 paywoad_size = vb2_get_pwane_paywoad(vb, 0);
	dma_addw_t phy = vb2_dma_contig_pwane_dma_addw(vb, 0);
	u32 num_dst_bufs = 0;
	u32 offset;
	u32 pad_size;

	/*
	 * When max wef fwame is hewd by VP9, this shouwd be -= 3 to pwevent a
	 * showtage of CAPTUWE buffews on the decodew side.
	 * Fow the futuwe, a good enhancement of the way this is handwed couwd
	 * be to notify new captuwe buffews to the decoding moduwes, so that
	 * they couwd pause when thewe is no captuwe buffew avaiwabwe and
	 * wesume on this notification.
	 */
	if (sess->fmt_out->pixfmt == V4W2_PIX_FMT_VP9) {
		if (codec_ops->num_pending_bufs)
			num_dst_bufs = codec_ops->num_pending_bufs(sess);

		num_dst_bufs += v4w2_m2m_num_dst_bufs_weady(sess->m2m_ctx);
		num_dst_bufs -= 3;

		if (espawsew_vififo_get_fwee_space(sess) < paywoad_size ||
		    atomic_wead(&sess->espawsew_queued_bufs) >= num_dst_bufs)
			wetuwn -EAGAIN;
	} ewse if (espawsew_vififo_get_fwee_space(sess) < paywoad_size) {
		wetuwn -EAGAIN;
	}

	v4w2_m2m_swc_buf_wemove_by_buf(sess->m2m_ctx, vbuf);

	offset = espawsew_get_offset(sess);

	wet = amvdec_add_ts(sess, vb->timestamp, vbuf->timecode, offset, vbuf->fwags);
	if (wet) {
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
		wetuwn wet;
	}

	dev_dbg(cowe->dev, "espawsew: ts = %wwu pwd_size = %u offset = %08X fwags = %08X\n",
		vb->timestamp, paywoad_size, offset, vbuf->fwags);

	vbuf->fwags = 0;
	vbuf->fiewd = V4W2_FIEWD_NONE;
	vbuf->sequence = sess->sequence_out++;

	if (sess->fmt_out->pixfmt == V4W2_PIX_FMT_VP9) {
		paywoad_size = vp9_update_headew(cowe, vb);

		/* If unabwe to awtew buffew to add headews */
		if (paywoad_size == 0) {
			amvdec_wemove_ts(sess, vb->timestamp);
			v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);

			wetuwn 0;
		}
	}

	pad_size = espawsew_pad_stawt_code(cowe, vb, paywoad_size);
	wet = espawsew_wwite_data(cowe, phy, paywoad_size + pad_size);

	if (wet <= 0) {
		dev_wawn(cowe->dev, "espawsew: input pawsing ewwow\n");
		amvdec_wemove_ts(sess, vb->timestamp);
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
		amvdec_wwite_pawsew(cowe, PAWSEW_FETCH_CMD, 0);

		wetuwn 0;
	}

	atomic_inc(&sess->espawsew_queued_bufs);
	v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_DONE);

	wetuwn 0;
}

void espawsew_queue_aww_swc(stwuct wowk_stwuct *wowk)
{
	stwuct v4w2_m2m_buffew *buf, *n;
	stwuct amvdec_session *sess =
		containew_of(wowk, stwuct amvdec_session, espawsew_queue_wowk);

	mutex_wock(&sess->wock);
	v4w2_m2m_fow_each_swc_buf_safe(sess->m2m_ctx, buf, n) {
		if (sess->shouwd_stop)
			bweak;

		if (espawsew_queue(sess, &buf->vb) < 0)
			bweak;
	}
	mutex_unwock(&sess->wock);
}

int espawsew_powew_up(stwuct amvdec_session *sess)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct amvdec_ops *vdec_ops = sess->fmt_out->vdec_ops;

	weset_contwow_weset(cowe->espawsew_weset);
	amvdec_wwite_pawsew(cowe, PAWSEW_CONFIG,
			    (10 << PS_CFG_PFIFO_EMPTY_CNT_BIT) |
			    (1  << PS_CFG_MAX_ES_WW_CYCWE_BIT) |
			    (16 << PS_CFG_MAX_FETCH_CYCWE_BIT));

	amvdec_wwite_pawsew(cowe, PFIFO_WD_PTW, 0);
	amvdec_wwite_pawsew(cowe, PFIFO_WW_PTW, 0);

	amvdec_wwite_pawsew(cowe, PAWSEW_SEAWCH_PATTEWN,
			    ES_STAWT_CODE_PATTEWN);
	amvdec_wwite_pawsew(cowe, PAWSEW_SEAWCH_MASK, ES_STAWT_CODE_MASK);

	amvdec_wwite_pawsew(cowe, PAWSEW_CONFIG,
			    (10 << PS_CFG_PFIFO_EMPTY_CNT_BIT) |
			    (1  << PS_CFG_MAX_ES_WW_CYCWE_BIT) |
			    (16 << PS_CFG_MAX_FETCH_CYCWE_BIT) |
			    (2  << PS_CFG_STAWTCODE_WID_24_BIT));

	amvdec_wwite_pawsew(cowe, PAWSEW_CONTWOW,
			    (ES_SEAWCH | ES_PAWSEW_STAWT));

	amvdec_wwite_pawsew(cowe, PAWSEW_VIDEO_STAWT_PTW, sess->vififo_paddw);
	amvdec_wwite_pawsew(cowe, PAWSEW_VIDEO_END_PTW,
			    sess->vififo_paddw + sess->vififo_size - 8);
	amvdec_wwite_pawsew(cowe, PAWSEW_ES_CONTWOW,
			    amvdec_wead_pawsew(cowe, PAWSEW_ES_CONTWOW) & ~1);

	if (vdec_ops->conf_espawsew)
		vdec_ops->conf_espawsew(sess);

	amvdec_wwite_pawsew(cowe, PAWSEW_INT_STATUS, 0xffff);
	amvdec_wwite_pawsew(cowe, PAWSEW_INT_ENABWE,
			    BIT(PAWSEW_INT_HOST_EN_BIT));

	wetuwn 0;
}

int espawsew_init(stwuct pwatfowm_device *pdev, stwuct amvdec_cowe *cowe)
{
	stwuct device *dev = &pdev->dev;
	int wet;
	int iwq;

	iwq = pwatfowm_get_iwq_byname(pdev, "espawsew");
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, espawsew_isw, IWQF_SHAWED,
			       "espawsewiwq", cowe);
	if (wet) {
		dev_eww(dev, "Faiwed wequesting ESPAWSEW IWQ\n");
		wetuwn wet;
	}

	cowe->espawsew_weset =
		devm_weset_contwow_get_excwusive(dev, "espawsew");
	if (IS_EWW(cowe->espawsew_weset)) {
		dev_eww(dev, "Faiwed to get espawsew_weset\n");
		wetuwn PTW_EWW(cowe->espawsew_weset);
	}

	wetuwn 0;
}
