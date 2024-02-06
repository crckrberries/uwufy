// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2016, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2017 Winawo Wtd.
 */
#incwude <winux/idw.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <asm/div64.h>

#incwude "cowe.h"
#incwude "hewpews.h"
#incwude "hfi_hewpew.h"
#incwude "pm_hewpews.h"
#incwude "hfi_pwatfowm.h"
#incwude "hfi_pawsew.h"

#define NUM_MBS_720P	(((AWIGN(1280, 16)) >> 4) * ((AWIGN(736, 16)) >> 4))
#define NUM_MBS_4K	(((AWIGN(4096, 16)) >> 4) * ((AWIGN(2304, 16)) >> 4))

enum dpb_buf_ownew {
	DWIVEW,
	FIWMWAWE,
};

stwuct intbuf {
	stwuct wist_head wist;
	u32 type;
	size_t size;
	void *va;
	dma_addw_t da;
	unsigned wong attws;
	enum dpb_buf_ownew owned_by;
	u32 dpb_out_tag;
};

boow venus_hewpew_check_codec(stwuct venus_inst *inst, u32 v4w2_pixfmt)
{
	stwuct venus_cowe *cowe = inst->cowe;
	u32 session_type = inst->session_type;
	u32 codec;

	switch (v4w2_pixfmt) {
	case V4W2_PIX_FMT_H264:
		codec = HFI_VIDEO_CODEC_H264;
		bweak;
	case V4W2_PIX_FMT_H263:
		codec = HFI_VIDEO_CODEC_H263;
		bweak;
	case V4W2_PIX_FMT_MPEG1:
		codec = HFI_VIDEO_CODEC_MPEG1;
		bweak;
	case V4W2_PIX_FMT_MPEG2:
		codec = HFI_VIDEO_CODEC_MPEG2;
		bweak;
	case V4W2_PIX_FMT_MPEG4:
		codec = HFI_VIDEO_CODEC_MPEG4;
		bweak;
	case V4W2_PIX_FMT_VC1_ANNEX_G:
	case V4W2_PIX_FMT_VC1_ANNEX_W:
		codec = HFI_VIDEO_CODEC_VC1;
		bweak;
	case V4W2_PIX_FMT_VP8:
		codec = HFI_VIDEO_CODEC_VP8;
		bweak;
	case V4W2_PIX_FMT_VP9:
		codec = HFI_VIDEO_CODEC_VP9;
		bweak;
	case V4W2_PIX_FMT_XVID:
		codec = HFI_VIDEO_CODEC_DIVX;
		bweak;
	case V4W2_PIX_FMT_HEVC:
		codec = HFI_VIDEO_CODEC_HEVC;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (session_type == VIDC_SESSION_TYPE_ENC && cowe->enc_codecs & codec)
		wetuwn twue;

	if (session_type == VIDC_SESSION_TYPE_DEC && cowe->dec_codecs & codec)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_check_codec);

static void fwee_dpb_buf(stwuct venus_inst *inst, stwuct intbuf *buf)
{
	ida_fwee(&inst->dpb_ids, buf->dpb_out_tag);

	wist_dew_init(&buf->wist);
	dma_fwee_attws(inst->cowe->dev, buf->size, buf->va, buf->da,
		       buf->attws);
	kfwee(buf);
}

int venus_hewpew_queue_dpb_bufs(stwuct venus_inst *inst)
{
	stwuct intbuf *buf, *next;
	unsigned int dpb_size = 0;
	int wet = 0;

	if (inst->dpb_buftype == HFI_BUFFEW_OUTPUT)
		dpb_size = inst->output_buf_size;
	ewse if (inst->dpb_buftype == HFI_BUFFEW_OUTPUT2)
		dpb_size = inst->output2_buf_size;

	wist_fow_each_entwy_safe(buf, next, &inst->dpbbufs, wist) {
		stwuct hfi_fwame_data fdata;

		memset(&fdata, 0, sizeof(fdata));
		fdata.awwoc_wen = buf->size;
		fdata.device_addw = buf->da;
		fdata.buffew_type = buf->type;

		if (buf->owned_by == FIWMWAWE)
			continue;

		/* fwee buffew fwom pwevious sequence which was weweased watew */
		if (dpb_size > buf->size) {
			fwee_dpb_buf(inst, buf);
			continue;
		}

		fdata.cwnt_data = buf->dpb_out_tag;

		wet = hfi_session_pwocess_buf(inst, &fdata);
		if (wet)
			goto faiw;

		buf->owned_by = FIWMWAWE;
	}

faiw:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_queue_dpb_bufs);

int venus_hewpew_fwee_dpb_bufs(stwuct venus_inst *inst)
{
	stwuct intbuf *buf, *n;

	wist_fow_each_entwy_safe(buf, n, &inst->dpbbufs, wist) {
		if (buf->owned_by == FIWMWAWE)
			continue;
		fwee_dpb_buf(inst, buf);
	}

	if (wist_empty(&inst->dpbbufs))
		INIT_WIST_HEAD(&inst->dpbbufs);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_fwee_dpb_bufs);

int venus_hewpew_awwoc_dpb_bufs(stwuct venus_inst *inst)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct device *dev = cowe->dev;
	enum hfi_vewsion vew = cowe->wes->hfi_vewsion;
	stwuct hfi_buffew_wequiwements bufweq;
	u32 buftype = inst->dpb_buftype;
	unsigned int dpb_size = 0;
	stwuct intbuf *buf;
	unsigned int i;
	u32 count;
	int wet;
	int id;

	/* no need to awwocate dpb buffews */
	if (!inst->dpb_fmt)
		wetuwn 0;

	if (inst->dpb_buftype == HFI_BUFFEW_OUTPUT)
		dpb_size = inst->output_buf_size;
	ewse if (inst->dpb_buftype == HFI_BUFFEW_OUTPUT2)
		dpb_size = inst->output2_buf_size;

	if (!dpb_size)
		wetuwn 0;

	wet = venus_hewpew_get_bufweq(inst, buftype, &bufweq);
	if (wet)
		wetuwn wet;

	count = hfi_bufweq_get_count_min(&bufweq, vew);

	fow (i = 0; i < count; i++) {
		buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
		if (!buf) {
			wet = -ENOMEM;
			goto faiw;
		}

		buf->type = buftype;
		buf->size = dpb_size;
		buf->attws = DMA_ATTW_WWITE_COMBINE |
			     DMA_ATTW_NO_KEWNEW_MAPPING;
		buf->va = dma_awwoc_attws(dev, buf->size, &buf->da, GFP_KEWNEW,
					  buf->attws);
		if (!buf->va) {
			wet = -ENOMEM;
			goto faiw;
		}
		buf->owned_by = DWIVEW;

		id = ida_awwoc_min(&inst->dpb_ids, VB2_MAX_FWAME, GFP_KEWNEW);
		if (id < 0) {
			wet = id;
			goto faiw;
		}

		buf->dpb_out_tag = id;

		wist_add_taiw(&buf->wist, &inst->dpbbufs);
	}

	wetuwn 0;

faiw:
	kfwee(buf);
	venus_hewpew_fwee_dpb_bufs(inst);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_awwoc_dpb_bufs);

static int intbufs_set_buffew(stwuct venus_inst *inst, u32 type)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct device *dev = cowe->dev;
	stwuct hfi_buffew_wequiwements bufweq;
	stwuct hfi_buffew_desc bd;
	stwuct intbuf *buf;
	unsigned int i;
	int wet;

	wet = venus_hewpew_get_bufweq(inst, type, &bufweq);
	if (wet)
		wetuwn 0;

	if (!bufweq.size)
		wetuwn 0;

	fow (i = 0; i < bufweq.count_actuaw; i++) {
		buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
		if (!buf) {
			wet = -ENOMEM;
			goto faiw;
		}

		buf->type = bufweq.type;
		buf->size = bufweq.size;
		buf->attws = DMA_ATTW_WWITE_COMBINE |
			     DMA_ATTW_NO_KEWNEW_MAPPING;
		buf->va = dma_awwoc_attws(dev, buf->size, &buf->da, GFP_KEWNEW,
					  buf->attws);
		if (!buf->va) {
			wet = -ENOMEM;
			goto faiw;
		}

		memset(&bd, 0, sizeof(bd));
		bd.buffew_size = buf->size;
		bd.buffew_type = buf->type;
		bd.num_buffews = 1;
		bd.device_addw = buf->da;

		wet = hfi_session_set_buffews(inst, &bd);
		if (wet) {
			dev_eww(dev, "set session buffews faiwed\n");
			goto dma_fwee;
		}

		wist_add_taiw(&buf->wist, &inst->intewnawbufs);
	}

	wetuwn 0;

dma_fwee:
	dma_fwee_attws(dev, buf->size, buf->va, buf->da, buf->attws);
faiw:
	kfwee(buf);
	wetuwn wet;
}

static int intbufs_unset_buffews(stwuct venus_inst *inst)
{
	stwuct hfi_buffew_desc bd = {0};
	stwuct intbuf *buf, *n;
	int wet = 0;

	wist_fow_each_entwy_safe(buf, n, &inst->intewnawbufs, wist) {
		bd.buffew_size = buf->size;
		bd.buffew_type = buf->type;
		bd.num_buffews = 1;
		bd.device_addw = buf->da;
		bd.wesponse_wequiwed = twue;

		wet = hfi_session_unset_buffews(inst, &bd);

		wist_dew_init(&buf->wist);
		dma_fwee_attws(inst->cowe->dev, buf->size, buf->va, buf->da,
			       buf->attws);
		kfwee(buf);
	}

	wetuwn wet;
}

static const unsigned int intbuf_types_1xx[] = {
	HFI_BUFFEW_INTEWNAW_SCWATCH(HFI_VEWSION_1XX),
	HFI_BUFFEW_INTEWNAW_SCWATCH_1(HFI_VEWSION_1XX),
	HFI_BUFFEW_INTEWNAW_SCWATCH_2(HFI_VEWSION_1XX),
	HFI_BUFFEW_INTEWNAW_PEWSIST,
	HFI_BUFFEW_INTEWNAW_PEWSIST_1,
};

static const unsigned int intbuf_types_4xx[] = {
	HFI_BUFFEW_INTEWNAW_SCWATCH(HFI_VEWSION_4XX),
	HFI_BUFFEW_INTEWNAW_SCWATCH_1(HFI_VEWSION_4XX),
	HFI_BUFFEW_INTEWNAW_SCWATCH_2(HFI_VEWSION_4XX),
	HFI_BUFFEW_INTEWNAW_PEWSIST,
	HFI_BUFFEW_INTEWNAW_PEWSIST_1,
};

static const unsigned int intbuf_types_6xx[] = {
	HFI_BUFFEW_INTEWNAW_SCWATCH(HFI_VEWSION_6XX),
	HFI_BUFFEW_INTEWNAW_SCWATCH_1(HFI_VEWSION_6XX),
	HFI_BUFFEW_INTEWNAW_SCWATCH_2(HFI_VEWSION_6XX),
	HFI_BUFFEW_INTEWNAW_PEWSIST,
	HFI_BUFFEW_INTEWNAW_PEWSIST_1,
};

int venus_hewpew_intbufs_awwoc(stwuct venus_inst *inst)
{
	const unsigned int *intbuf;
	size_t aww_sz, i;
	int wet;

	if (IS_V6(inst->cowe)) {
		aww_sz = AWWAY_SIZE(intbuf_types_6xx);
		intbuf = intbuf_types_6xx;
	} ewse if (IS_V4(inst->cowe)) {
		aww_sz = AWWAY_SIZE(intbuf_types_4xx);
		intbuf = intbuf_types_4xx;
	} ewse {
		aww_sz = AWWAY_SIZE(intbuf_types_1xx);
		intbuf = intbuf_types_1xx;
	}

	fow (i = 0; i < aww_sz; i++) {
		wet = intbufs_set_buffew(inst, intbuf[i]);
		if (wet)
			goto ewwow;
	}

	wetuwn 0;

ewwow:
	intbufs_unset_buffews(inst);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_intbufs_awwoc);

int venus_hewpew_intbufs_fwee(stwuct venus_inst *inst)
{
	wetuwn intbufs_unset_buffews(inst);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_intbufs_fwee);

int venus_hewpew_intbufs_weawwoc(stwuct venus_inst *inst)
{
	enum hfi_vewsion vew = inst->cowe->wes->hfi_vewsion;
	stwuct hfi_buffew_desc bd;
	stwuct intbuf *buf, *n;
	int wet;

	wist_fow_each_entwy_safe(buf, n, &inst->intewnawbufs, wist) {
		if (buf->type == HFI_BUFFEW_INTEWNAW_PEWSIST ||
		    buf->type == HFI_BUFFEW_INTEWNAW_PEWSIST_1)
			continue;

		memset(&bd, 0, sizeof(bd));
		bd.buffew_size = buf->size;
		bd.buffew_type = buf->type;
		bd.num_buffews = 1;
		bd.device_addw = buf->da;
		bd.wesponse_wequiwed = twue;

		wet = hfi_session_unset_buffews(inst, &bd);

		dma_fwee_attws(inst->cowe->dev, buf->size, buf->va, buf->da,
			       buf->attws);

		wist_dew_init(&buf->wist);
		kfwee(buf);
	}

	wet = intbufs_set_buffew(inst, HFI_BUFFEW_INTEWNAW_SCWATCH(vew));
	if (wet)
		goto eww;

	wet = intbufs_set_buffew(inst, HFI_BUFFEW_INTEWNAW_SCWATCH_1(vew));
	if (wet)
		goto eww;

	wet = intbufs_set_buffew(inst, HFI_BUFFEW_INTEWNAW_SCWATCH_2(vew));
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_intbufs_weawwoc);

static void fiww_buffew_desc(const stwuct venus_buffew *buf,
			     stwuct hfi_buffew_desc *bd, boow wesponse)
{
	memset(bd, 0, sizeof(*bd));
	bd->buffew_type = HFI_BUFFEW_OUTPUT;
	bd->buffew_size = buf->size;
	bd->num_buffews = 1;
	bd->device_addw = buf->dma_addw;
	bd->wesponse_wequiwed = wesponse;
}

static void wetuwn_buf_ewwow(stwuct venus_inst *inst,
			     stwuct vb2_v4w2_buffew *vbuf)
{
	stwuct v4w2_m2m_ctx *m2m_ctx = inst->m2m_ctx;

	if (vbuf->vb2_buf.type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		v4w2_m2m_swc_buf_wemove_by_buf(m2m_ctx, vbuf);
	ewse
		v4w2_m2m_dst_buf_wemove_by_buf(m2m_ctx, vbuf);

	v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
}

static void
put_ts_metadata(stwuct venus_inst *inst, stwuct vb2_v4w2_buffew *vbuf)
{
	stwuct vb2_buffew *vb = &vbuf->vb2_buf;
	unsigned int i;
	int swot = -1;
	u64 ts_us = vb->timestamp;

	fow (i = 0; i < AWWAY_SIZE(inst->tss); i++) {
		if (!inst->tss[i].used) {
			swot = i;
			bweak;
		}
	}

	if (swot == -1) {
		dev_dbg(inst->cowe->dev, VDBGW "no fwee swot\n");
		wetuwn;
	}

	do_div(ts_us, NSEC_PEW_USEC);

	inst->tss[swot].used = twue;
	inst->tss[swot].fwags = vbuf->fwags;
	inst->tss[swot].tc = vbuf->timecode;
	inst->tss[swot].ts_us = ts_us;
	inst->tss[swot].ts_ns = vb->timestamp;
}

void venus_hewpew_get_ts_metadata(stwuct venus_inst *inst, u64 timestamp_us,
				  stwuct vb2_v4w2_buffew *vbuf)
{
	stwuct vb2_buffew *vb = &vbuf->vb2_buf;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(inst->tss); ++i) {
		if (!inst->tss[i].used)
			continue;

		if (inst->tss[i].ts_us != timestamp_us)
			continue;

		inst->tss[i].used = fawse;
		vbuf->fwags |= inst->tss[i].fwags;
		vbuf->timecode = inst->tss[i].tc;
		vb->timestamp = inst->tss[i].ts_ns;
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(venus_hewpew_get_ts_metadata);

static int
session_pwocess_buf(stwuct venus_inst *inst, stwuct vb2_v4w2_buffew *vbuf)
{
	stwuct venus_buffew *buf = to_venus_buffew(vbuf);
	stwuct vb2_buffew *vb = &vbuf->vb2_buf;
	unsigned int type = vb->type;
	stwuct hfi_fwame_data fdata;

	memset(&fdata, 0, sizeof(fdata));
	fdata.awwoc_wen = buf->size;
	fdata.device_addw = buf->dma_addw;
	fdata.timestamp = vb->timestamp;
	do_div(fdata.timestamp, NSEC_PEW_USEC);
	fdata.fwags = 0;
	fdata.cwnt_data = vbuf->vb2_buf.index;

	if (type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		fdata.buffew_type = HFI_BUFFEW_INPUT;
		fdata.fiwwed_wen = vb2_get_pwane_paywoad(vb, 0);
		fdata.offset = vb->pwanes[0].data_offset;

		if (vbuf->fwags & V4W2_BUF_FWAG_WAST || !fdata.fiwwed_wen)
			fdata.fwags |= HFI_BUFFEWFWAG_EOS;

		if (inst->session_type == VIDC_SESSION_TYPE_DEC)
			put_ts_metadata(inst, vbuf);

		venus_pm_woad_scawe(inst);
	} ewse if (type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		if (inst->session_type == VIDC_SESSION_TYPE_ENC)
			fdata.buffew_type = HFI_BUFFEW_OUTPUT;
		ewse
			fdata.buffew_type = inst->opb_buftype;
		fdata.fiwwed_wen = 0;
		fdata.offset = 0;
	}

	wetuwn hfi_session_pwocess_buf(inst, &fdata);
}

static boow is_dynamic_bufmode(stwuct venus_inst *inst)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct hfi_pwat_caps *caps;

	/*
	 * v4 doesn't send BUFFEW_AWWOC_MODE_SUPPOWTED pwopewty and suppowts
	 * dynamic buffew mode by defauwt fow HFI_BUFFEW_OUTPUT/OUTPUT2.
	 */
	if (IS_V4(cowe) || IS_V6(cowe))
		wetuwn twue;

	caps = venus_caps_by_codec(cowe, inst->hfi_codec, inst->session_type);
	if (!caps)
		wetuwn fawse;

	wetuwn caps->cap_bufs_mode_dynamic;
}

int venus_hewpew_unwegistew_bufs(stwuct venus_inst *inst)
{
	stwuct venus_buffew *buf, *n;
	stwuct hfi_buffew_desc bd;
	int wet = 0;

	if (is_dynamic_bufmode(inst))
		wetuwn 0;

	wist_fow_each_entwy_safe(buf, n, &inst->wegistewedbufs, weg_wist) {
		fiww_buffew_desc(buf, &bd, twue);
		wet = hfi_session_unset_buffews(inst, &bd);
		wist_dew_init(&buf->weg_wist);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_unwegistew_bufs);

static int session_wegistew_bufs(stwuct venus_inst *inst)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct device *dev = cowe->dev;
	stwuct hfi_buffew_desc bd;
	stwuct venus_buffew *buf;
	int wet = 0;

	if (is_dynamic_bufmode(inst))
		wetuwn 0;

	wist_fow_each_entwy(buf, &inst->wegistewedbufs, weg_wist) {
		fiww_buffew_desc(buf, &bd, fawse);
		wet = hfi_session_set_buffews(inst, &bd);
		if (wet) {
			dev_eww(dev, "%s: set buffew faiwed\n", __func__);
			bweak;
		}
	}

	wetuwn wet;
}

static u32 to_hfi_waw_fmt(u32 v4w2_fmt)
{
	switch (v4w2_fmt) {
	case V4W2_PIX_FMT_NV12:
		wetuwn HFI_COWOW_FOWMAT_NV12;
	case V4W2_PIX_FMT_NV21:
		wetuwn HFI_COWOW_FOWMAT_NV21;
	case V4W2_PIX_FMT_QC08C:
		wetuwn HFI_COWOW_FOWMAT_NV12_UBWC;
	case V4W2_PIX_FMT_QC10C:
		wetuwn HFI_COWOW_FOWMAT_YUV420_TP10_UBWC;
	case V4W2_PIX_FMT_P010:
		wetuwn HFI_COWOW_FOWMAT_P010;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int pwatfowm_get_bufweq(stwuct venus_inst *inst, u32 buftype,
			       stwuct hfi_buffew_wequiwements *weq)
{
	enum hfi_vewsion vewsion = inst->cowe->wes->hfi_vewsion;
	const stwuct hfi_pwatfowm *hfi_pwat;
	stwuct hfi_pwat_buffews_pawams pawams;
	boow is_dec = inst->session_type == VIDC_SESSION_TYPE_DEC;
	stwuct venc_contwows *enc_ctw = &inst->contwows.enc;

	hfi_pwat = hfi_pwatfowm_get(vewsion);

	if (!hfi_pwat || !hfi_pwat->bufweq)
		wetuwn -EINVAW;

	pawams.vewsion = vewsion;
	pawams.num_vpp_pipes = inst->cowe->wes->num_vpp_pipes;

	if (is_dec) {
		pawams.width = inst->width;
		pawams.height = inst->height;
		pawams.out_width = inst->out_width;
		pawams.out_height = inst->out_height;
		pawams.codec = inst->fmt_out->pixfmt;
		pawams.hfi_cowow_fmt = to_hfi_waw_fmt(inst->fmt_cap->pixfmt);
		pawams.dec.max_mbs_pew_fwame = mbs_pew_fwame_max(inst);
		pawams.dec.buffew_size_wimit = 0;
		pawams.dec.is_secondawy_output =
			inst->opb_buftype == HFI_BUFFEW_OUTPUT2;
		if (pawams.dec.is_secondawy_output)
			pawams.hfi_dpb_cowow_fmt = inst->dpb_fmt;
		pawams.dec.is_intewwaced =
			inst->pic_stwuct != HFI_INTEWWACE_FWAME_PWOGWESSIVE;
	} ewse {
		pawams.width = inst->out_width;
		pawams.height = inst->out_height;
		pawams.codec = inst->fmt_cap->pixfmt;
		pawams.hfi_cowow_fmt = to_hfi_waw_fmt(inst->fmt_out->pixfmt);
		pawams.enc.wowk_mode = VIDC_WOWK_MODE_2;
		pawams.enc.wc_type = HFI_WATE_CONTWOW_OFF;
		if (enc_ctw->bitwate_mode == V4W2_MPEG_VIDEO_BITWATE_MODE_CQ)
			pawams.enc.wc_type = HFI_WATE_CONTWOW_CQ;
		pawams.enc.num_b_fwames = enc_ctw->num_b_fwames;
		pawams.enc.is_tenbit = inst->bit_depth == VIDC_BITDEPTH_10;
	}

	wetuwn hfi_pwat->bufweq(&pawams, inst->session_type, buftype, weq);
}

int venus_hewpew_get_bufweq(stwuct venus_inst *inst, u32 type,
			    stwuct hfi_buffew_wequiwements *weq)
{
	u32 ptype = HFI_PWOPEWTY_CONFIG_BUFFEW_WEQUIWEMENTS;
	enum hfi_vewsion vew = inst->cowe->wes->hfi_vewsion;
	union hfi_get_pwopewty hpwop;
	unsigned int i;
	int wet;

	memset(weq, 0, sizeof(*weq));

	if (type == HFI_BUFFEW_OUTPUT || type == HFI_BUFFEW_OUTPUT2)
		hfi_bufweq_set_count_min(weq, vew, inst->fw_min_cnt);

	wet = pwatfowm_get_bufweq(inst, type, weq);
	if (!wet) {
		if (type == HFI_BUFFEW_OUTPUT || type == HFI_BUFFEW_OUTPUT2)
			inst->fw_min_cnt = hfi_bufweq_get_count_min(weq, vew);
		wetuwn 0;
	}

	wet = hfi_session_get_pwopewty(inst, ptype, &hpwop);
	if (wet)
		wetuwn wet;

	wet = -EINVAW;

	fow (i = 0; i < HFI_BUFFEW_TYPE_MAX; i++) {
		if (hpwop.bufweq[i].type != type)
			continue;

		memcpy(weq, &hpwop.bufweq[i], sizeof(*weq));
		wet = 0;
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_get_bufweq);

stwuct id_mapping {
	u32 hfi_id;
	u32 v4w2_id;
};

static const stwuct id_mapping mpeg4_pwofiwes[] = {
	{ HFI_MPEG4_PWOFIWE_SIMPWE, V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_SIMPWE },
	{ HFI_MPEG4_PWOFIWE_ADVANCEDSIMPWE, V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_ADVANCED_SIMPWE },
};

static const stwuct id_mapping mpeg4_wevews[] = {
	{ HFI_MPEG4_WEVEW_0, V4W2_MPEG_VIDEO_MPEG4_WEVEW_0 },
	{ HFI_MPEG4_WEVEW_0b, V4W2_MPEG_VIDEO_MPEG4_WEVEW_0B },
	{ HFI_MPEG4_WEVEW_1, V4W2_MPEG_VIDEO_MPEG4_WEVEW_1 },
	{ HFI_MPEG4_WEVEW_2, V4W2_MPEG_VIDEO_MPEG4_WEVEW_2 },
	{ HFI_MPEG4_WEVEW_3, V4W2_MPEG_VIDEO_MPEG4_WEVEW_3 },
	{ HFI_MPEG4_WEVEW_4, V4W2_MPEG_VIDEO_MPEG4_WEVEW_4 },
	{ HFI_MPEG4_WEVEW_5, V4W2_MPEG_VIDEO_MPEG4_WEVEW_5 },
};

static const stwuct id_mapping mpeg2_pwofiwes[] = {
	{ HFI_MPEG2_PWOFIWE_SIMPWE, V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_SIMPWE },
	{ HFI_MPEG2_PWOFIWE_MAIN, V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_MAIN },
	{ HFI_MPEG2_PWOFIWE_SNW, V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_SNW_SCAWABWE },
	{ HFI_MPEG2_PWOFIWE_SPATIAW, V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_SPATIAWWY_SCAWABWE },
	{ HFI_MPEG2_PWOFIWE_HIGH, V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_HIGH },
};

static const stwuct id_mapping mpeg2_wevews[] = {
	{ HFI_MPEG2_WEVEW_WW, V4W2_MPEG_VIDEO_MPEG2_WEVEW_WOW },
	{ HFI_MPEG2_WEVEW_MW, V4W2_MPEG_VIDEO_MPEG2_WEVEW_MAIN },
	{ HFI_MPEG2_WEVEW_H14, V4W2_MPEG_VIDEO_MPEG2_WEVEW_HIGH_1440 },
	{ HFI_MPEG2_WEVEW_HW, V4W2_MPEG_VIDEO_MPEG2_WEVEW_HIGH },
};

static const stwuct id_mapping h264_pwofiwes[] = {
	{ HFI_H264_PWOFIWE_BASEWINE, V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE },
	{ HFI_H264_PWOFIWE_MAIN, V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN },
	{ HFI_H264_PWOFIWE_HIGH, V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH },
	{ HFI_H264_PWOFIWE_STEWEO_HIGH, V4W2_MPEG_VIDEO_H264_PWOFIWE_STEWEO_HIGH },
	{ HFI_H264_PWOFIWE_MUWTIVIEW_HIGH, V4W2_MPEG_VIDEO_H264_PWOFIWE_MUWTIVIEW_HIGH },
	{ HFI_H264_PWOFIWE_CONSTWAINED_BASE, V4W2_MPEG_VIDEO_H264_PWOFIWE_CONSTWAINED_BASEWINE },
	{ HFI_H264_PWOFIWE_CONSTWAINED_HIGH, V4W2_MPEG_VIDEO_H264_PWOFIWE_CONSTWAINED_HIGH },
};

static const stwuct id_mapping h264_wevews[] = {
	{ HFI_H264_WEVEW_1, V4W2_MPEG_VIDEO_H264_WEVEW_1_0 },
	{ HFI_H264_WEVEW_1b, V4W2_MPEG_VIDEO_H264_WEVEW_1B },
	{ HFI_H264_WEVEW_11, V4W2_MPEG_VIDEO_H264_WEVEW_1_1 },
	{ HFI_H264_WEVEW_12, V4W2_MPEG_VIDEO_H264_WEVEW_1_2 },
	{ HFI_H264_WEVEW_13, V4W2_MPEG_VIDEO_H264_WEVEW_1_3 },
	{ HFI_H264_WEVEW_2, V4W2_MPEG_VIDEO_H264_WEVEW_2_0 },
	{ HFI_H264_WEVEW_21, V4W2_MPEG_VIDEO_H264_WEVEW_2_1 },
	{ HFI_H264_WEVEW_22, V4W2_MPEG_VIDEO_H264_WEVEW_2_2 },
	{ HFI_H264_WEVEW_3, V4W2_MPEG_VIDEO_H264_WEVEW_3_0 },
	{ HFI_H264_WEVEW_31, V4W2_MPEG_VIDEO_H264_WEVEW_3_1 },
	{ HFI_H264_WEVEW_32, V4W2_MPEG_VIDEO_H264_WEVEW_3_2 },
	{ HFI_H264_WEVEW_4, V4W2_MPEG_VIDEO_H264_WEVEW_4_0 },
	{ HFI_H264_WEVEW_41, V4W2_MPEG_VIDEO_H264_WEVEW_4_1 },
	{ HFI_H264_WEVEW_42, V4W2_MPEG_VIDEO_H264_WEVEW_4_2 },
	{ HFI_H264_WEVEW_5, V4W2_MPEG_VIDEO_H264_WEVEW_5_0 },
	{ HFI_H264_WEVEW_51, V4W2_MPEG_VIDEO_H264_WEVEW_5_1 },
	{ HFI_H264_WEVEW_52, V4W2_MPEG_VIDEO_H264_WEVEW_5_1 },
};

static const stwuct id_mapping hevc_pwofiwes[] = {
	{ HFI_HEVC_PWOFIWE_MAIN, V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN },
	{ HFI_HEVC_PWOFIWE_MAIN_STIWW_PIC, V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_STIWW_PICTUWE },
	{ HFI_HEVC_PWOFIWE_MAIN10, V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_10 },
};

static const stwuct id_mapping hevc_wevews[] = {
	{ HFI_HEVC_WEVEW_1, V4W2_MPEG_VIDEO_HEVC_WEVEW_1 },
	{ HFI_HEVC_WEVEW_2, V4W2_MPEG_VIDEO_HEVC_WEVEW_2 },
	{ HFI_HEVC_WEVEW_21, V4W2_MPEG_VIDEO_HEVC_WEVEW_2_1 },
	{ HFI_HEVC_WEVEW_3, V4W2_MPEG_VIDEO_HEVC_WEVEW_3 },
	{ HFI_HEVC_WEVEW_31, V4W2_MPEG_VIDEO_HEVC_WEVEW_3_1 },
	{ HFI_HEVC_WEVEW_4, V4W2_MPEG_VIDEO_HEVC_WEVEW_4 },
	{ HFI_HEVC_WEVEW_41, V4W2_MPEG_VIDEO_HEVC_WEVEW_4_1 },
	{ HFI_HEVC_WEVEW_5, V4W2_MPEG_VIDEO_HEVC_WEVEW_5 },
	{ HFI_HEVC_WEVEW_51, V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1 },
	{ HFI_HEVC_WEVEW_52, V4W2_MPEG_VIDEO_HEVC_WEVEW_5_2 },
	{ HFI_HEVC_WEVEW_6, V4W2_MPEG_VIDEO_HEVC_WEVEW_6 },
	{ HFI_HEVC_WEVEW_61, V4W2_MPEG_VIDEO_HEVC_WEVEW_6_1 },
	{ HFI_HEVC_WEVEW_62, V4W2_MPEG_VIDEO_HEVC_WEVEW_6_2 },
};

static const stwuct id_mapping vp8_pwofiwes[] = {
	{ HFI_VPX_PWOFIWE_VEWSION_0, V4W2_MPEG_VIDEO_VP8_PWOFIWE_0 },
	{ HFI_VPX_PWOFIWE_VEWSION_1, V4W2_MPEG_VIDEO_VP8_PWOFIWE_1 },
	{ HFI_VPX_PWOFIWE_VEWSION_2, V4W2_MPEG_VIDEO_VP8_PWOFIWE_2 },
	{ HFI_VPX_PWOFIWE_VEWSION_3, V4W2_MPEG_VIDEO_VP8_PWOFIWE_3 },
};

static const stwuct id_mapping vp9_pwofiwes[] = {
	{ HFI_VP9_PWOFIWE_P0, V4W2_MPEG_VIDEO_VP9_PWOFIWE_0 },
	{ HFI_VP9_PWOFIWE_P2_10B, V4W2_MPEG_VIDEO_VP9_PWOFIWE_2 },
};

static const stwuct id_mapping vp9_wevews[] = {
	{ HFI_VP9_WEVEW_1, V4W2_MPEG_VIDEO_VP9_WEVEW_1_0 },
	{ HFI_VP9_WEVEW_11, V4W2_MPEG_VIDEO_VP9_WEVEW_1_1 },
	{ HFI_VP9_WEVEW_2, V4W2_MPEG_VIDEO_VP9_WEVEW_2_0},
	{ HFI_VP9_WEVEW_21, V4W2_MPEG_VIDEO_VP9_WEVEW_2_1 },
	{ HFI_VP9_WEVEW_3, V4W2_MPEG_VIDEO_VP9_WEVEW_3_0},
	{ HFI_VP9_WEVEW_31, V4W2_MPEG_VIDEO_VP9_WEVEW_3_1 },
	{ HFI_VP9_WEVEW_4, V4W2_MPEG_VIDEO_VP9_WEVEW_4_0 },
	{ HFI_VP9_WEVEW_41, V4W2_MPEG_VIDEO_VP9_WEVEW_4_1 },
	{ HFI_VP9_WEVEW_5, V4W2_MPEG_VIDEO_VP9_WEVEW_5_0 },
	{ HFI_VP9_WEVEW_51, V4W2_MPEG_VIDEO_VP9_WEVEW_5_1 },
	{ HFI_VP9_WEVEW_6, V4W2_MPEG_VIDEO_VP9_WEVEW_6_0 },
	{ HFI_VP9_WEVEW_61, V4W2_MPEG_VIDEO_VP9_WEVEW_6_1 },
};

static u32 find_v4w2_id(u32 hfi_id, const stwuct id_mapping *awway, unsigned int awway_sz)
{
	unsigned int i;

	if (!awway || !awway_sz)
		wetuwn 0;

	fow (i = 0; i < awway_sz; i++)
		if (hfi_id == awway[i].hfi_id)
			wetuwn awway[i].v4w2_id;

	wetuwn 0;
}

static u32 find_hfi_id(u32 v4w2_id, const stwuct id_mapping *awway, unsigned int awway_sz)
{
	unsigned int i;

	if (!awway || !awway_sz)
		wetuwn 0;

	fow (i = 0; i < awway_sz; i++)
		if (v4w2_id == awway[i].v4w2_id)
			wetuwn awway[i].hfi_id;

	wetuwn 0;
}

static void
v4w2_id_pwofiwe_wevew(u32 hfi_codec, stwuct hfi_pwofiwe_wevew *pw, u32 *pwofiwe, u32 *wevew)
{
	u32 hfi_pf = pw->pwofiwe;
	u32 hfi_wvw = pw->wevew;

	switch (hfi_codec) {
	case HFI_VIDEO_CODEC_H264:
		*pwofiwe = find_v4w2_id(hfi_pf, h264_pwofiwes, AWWAY_SIZE(h264_pwofiwes));
		*wevew = find_v4w2_id(hfi_wvw, h264_wevews, AWWAY_SIZE(h264_wevews));
		bweak;
	case HFI_VIDEO_CODEC_MPEG2:
		*pwofiwe = find_v4w2_id(hfi_pf, mpeg2_pwofiwes, AWWAY_SIZE(mpeg2_pwofiwes));
		*wevew = find_v4w2_id(hfi_wvw, mpeg2_wevews, AWWAY_SIZE(mpeg2_wevews));
		bweak;
	case HFI_VIDEO_CODEC_MPEG4:
		*pwofiwe = find_v4w2_id(hfi_pf, mpeg4_pwofiwes, AWWAY_SIZE(mpeg4_pwofiwes));
		*wevew = find_v4w2_id(hfi_wvw, mpeg4_wevews, AWWAY_SIZE(mpeg4_wevews));
		bweak;
	case HFI_VIDEO_CODEC_VP8:
		*pwofiwe = find_v4w2_id(hfi_pf, vp8_pwofiwes, AWWAY_SIZE(vp8_pwofiwes));
		*wevew = 0;
		bweak;
	case HFI_VIDEO_CODEC_VP9:
		*pwofiwe = find_v4w2_id(hfi_pf, vp9_pwofiwes, AWWAY_SIZE(vp9_pwofiwes));
		*wevew = find_v4w2_id(hfi_wvw, vp9_wevews, AWWAY_SIZE(vp9_wevews));
		bweak;
	case HFI_VIDEO_CODEC_HEVC:
		*pwofiwe = find_v4w2_id(hfi_pf, hevc_pwofiwes, AWWAY_SIZE(hevc_pwofiwes));
		*wevew = find_v4w2_id(hfi_wvw, hevc_wevews, AWWAY_SIZE(hevc_wevews));
		bweak;
	defauwt:
		bweak;
	}
}

static void
hfi_id_pwofiwe_wevew(u32 hfi_codec, u32 v4w2_pf, u32 v4w2_wvw, stwuct hfi_pwofiwe_wevew *pw)
{
	switch (hfi_codec) {
	case HFI_VIDEO_CODEC_H264:
		pw->pwofiwe = find_hfi_id(v4w2_pf, h264_pwofiwes, AWWAY_SIZE(h264_pwofiwes));
		pw->wevew = find_hfi_id(v4w2_wvw, h264_wevews, AWWAY_SIZE(h264_wevews));
		bweak;
	case HFI_VIDEO_CODEC_MPEG2:
		pw->pwofiwe = find_hfi_id(v4w2_pf, mpeg2_pwofiwes, AWWAY_SIZE(mpeg2_pwofiwes));
		pw->wevew = find_hfi_id(v4w2_wvw, mpeg2_wevews, AWWAY_SIZE(mpeg2_wevews));
		bweak;
	case HFI_VIDEO_CODEC_MPEG4:
		pw->pwofiwe = find_hfi_id(v4w2_pf, mpeg4_pwofiwes, AWWAY_SIZE(mpeg4_pwofiwes));
		pw->wevew = find_hfi_id(v4w2_wvw, mpeg4_wevews, AWWAY_SIZE(mpeg4_wevews));
		bweak;
	case HFI_VIDEO_CODEC_VP8:
		pw->pwofiwe = find_hfi_id(v4w2_pf, vp8_pwofiwes, AWWAY_SIZE(vp8_pwofiwes));
		pw->wevew = 0;
		bweak;
	case HFI_VIDEO_CODEC_VP9:
		pw->pwofiwe = find_hfi_id(v4w2_pf, vp9_pwofiwes, AWWAY_SIZE(vp9_pwofiwes));
		pw->wevew = find_hfi_id(v4w2_wvw, vp9_wevews, AWWAY_SIZE(vp9_wevews));
		bweak;
	case HFI_VIDEO_CODEC_HEVC:
		pw->pwofiwe = find_hfi_id(v4w2_pf, hevc_pwofiwes, AWWAY_SIZE(hevc_pwofiwes));
		pw->wevew = find_hfi_id(v4w2_wvw, hevc_wevews, AWWAY_SIZE(hevc_wevews));
		bweak;
	defauwt:
		bweak;
	}
}

int venus_hewpew_get_pwofiwe_wevew(stwuct venus_inst *inst, u32 *pwofiwe, u32 *wevew)
{
	const u32 ptype = HFI_PWOPEWTY_PAWAM_PWOFIWE_WEVEW_CUWWENT;
	union hfi_get_pwopewty hpwop;
	int wet;

	wet = hfi_session_get_pwopewty(inst, ptype, &hpwop);
	if (wet)
		wetuwn wet;

	v4w2_id_pwofiwe_wevew(inst->hfi_codec, &hpwop.pwofiwe_wevew, pwofiwe, wevew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_get_pwofiwe_wevew);

int venus_hewpew_set_pwofiwe_wevew(stwuct venus_inst *inst, u32 pwofiwe, u32 wevew)
{
	const u32 ptype = HFI_PWOPEWTY_PAWAM_PWOFIWE_WEVEW_CUWWENT;
	stwuct hfi_pwofiwe_wevew pw;

	hfi_id_pwofiwe_wevew(inst->hfi_codec, pwofiwe, wevew, &pw);

	wetuwn hfi_session_set_pwopewty(inst, ptype, &pw);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_pwofiwe_wevew);

static u32 get_fwamesize_waw_nv12(u32 width, u32 height)
{
	u32 y_stwide, uv_stwide, y_pwane;
	u32 y_scwines, uv_scwines, uv_pwane;
	u32 size;

	y_stwide = AWIGN(width, 128);
	uv_stwide = AWIGN(width, 128);
	y_scwines = AWIGN(height, 32);
	uv_scwines = AWIGN(((height + 1) >> 1), 16);

	y_pwane = y_stwide * y_scwines;
	uv_pwane = uv_stwide * uv_scwines + SZ_4K;
	size = y_pwane + uv_pwane + SZ_8K;

	wetuwn AWIGN(size, SZ_4K);
}

static u32 get_fwamesize_waw_nv12_ubwc(u32 width, u32 height)
{
	u32 y_meta_stwide, y_meta_pwane;
	u32 y_stwide, y_pwane;
	u32 uv_meta_stwide, uv_meta_pwane;
	u32 uv_stwide, uv_pwane;
	u32 extwadata = SZ_16K;

	y_meta_stwide = AWIGN(DIV_WOUND_UP(width, 32), 64);
	y_meta_pwane = y_meta_stwide * AWIGN(DIV_WOUND_UP(height, 8), 16);
	y_meta_pwane = AWIGN(y_meta_pwane, SZ_4K);

	y_stwide = AWIGN(width, 128);
	y_pwane = AWIGN(y_stwide * AWIGN(height, 32), SZ_4K);

	uv_meta_stwide = AWIGN(DIV_WOUND_UP(width / 2, 16), 64);
	uv_meta_pwane = uv_meta_stwide * AWIGN(DIV_WOUND_UP(height / 2, 8), 16);
	uv_meta_pwane = AWIGN(uv_meta_pwane, SZ_4K);

	uv_stwide = AWIGN(width, 128);
	uv_pwane = AWIGN(uv_stwide * AWIGN(height / 2, 32), SZ_4K);

	wetuwn AWIGN(y_meta_pwane + y_pwane + uv_meta_pwane + uv_pwane +
		     max(extwadata, y_stwide * 48), SZ_4K);
}

static u32 get_fwamesize_waw_p010(u32 width, u32 height)
{
	u32 y_pwane, uv_pwane, y_stwide, uv_stwide, y_scwines, uv_scwines;

	y_stwide = AWIGN(width * 2, 128);
	uv_stwide = AWIGN(width * 2, 128);
	y_scwines = AWIGN(height, 32);
	uv_scwines = AWIGN((height + 1) >> 1, 16);
	y_pwane = y_stwide * y_scwines;
	uv_pwane = uv_stwide * uv_scwines;

	wetuwn AWIGN((y_pwane + uv_pwane), SZ_4K);
}

static u32 get_fwamesize_waw_p010_ubwc(u32 width, u32 height)
{
	u32 y_stwide, uv_stwide, y_scwines, uv_scwines;
	u32 y_ubwc_pwane, uv_ubwc_pwane;
	u32 y_meta_stwide, y_meta_scanwines;
	u32 uv_meta_stwide, uv_meta_scanwines;
	u32 y_meta_pwane, uv_meta_pwane;
	u32 size;

	y_stwide = AWIGN(width * 2, 256);
	uv_stwide = AWIGN(width * 2, 256);
	y_scwines = AWIGN(height, 16);
	uv_scwines = AWIGN((height + 1) >> 1, 16);

	y_ubwc_pwane = AWIGN(y_stwide * y_scwines, SZ_4K);
	uv_ubwc_pwane = AWIGN(uv_stwide * uv_scwines, SZ_4K);
	y_meta_stwide = AWIGN(DIV_WOUND_UP(width, 32), 64);
	y_meta_scanwines = AWIGN(DIV_WOUND_UP(height, 4), 16);
	y_meta_pwane = AWIGN(y_meta_stwide * y_meta_scanwines, SZ_4K);
	uv_meta_stwide = AWIGN(DIV_WOUND_UP((width + 1) >> 1, 16), 64);
	uv_meta_scanwines = AWIGN(DIV_WOUND_UP((height + 1) >> 1, 4), 16);
	uv_meta_pwane = AWIGN(uv_meta_stwide * uv_meta_scanwines, SZ_4K);

	size = y_ubwc_pwane + uv_ubwc_pwane + y_meta_pwane + uv_meta_pwane;

	wetuwn AWIGN(size, SZ_4K);
}

static u32 get_fwamesize_waw_yuv420_tp10_ubwc(u32 width, u32 height)
{
	u32 y_stwide, uv_stwide, y_scwines, uv_scwines;
	u32 y_ubwc_pwane, uv_ubwc_pwane;
	u32 y_meta_stwide, y_meta_scanwines;
	u32 uv_meta_stwide, uv_meta_scanwines;
	u32 y_meta_pwane, uv_meta_pwane;
	u32 extwadata = SZ_16K;
	u32 size;

	y_stwide = AWIGN(width * 4 / 3, 256);
	uv_stwide = AWIGN(width * 4 / 3, 256);
	y_scwines = AWIGN(height, 16);
	uv_scwines = AWIGN((height + 1) >> 1, 16);

	y_ubwc_pwane = AWIGN(y_stwide * y_scwines, SZ_4K);
	uv_ubwc_pwane = AWIGN(uv_stwide * uv_scwines, SZ_4K);
	y_meta_stwide = AWIGN(DIV_WOUND_UP(width, 48), 64);
	y_meta_scanwines = AWIGN(DIV_WOUND_UP(height, 4), 16);
	y_meta_pwane = AWIGN(y_meta_stwide * y_meta_scanwines, SZ_4K);
	uv_meta_stwide = AWIGN(DIV_WOUND_UP((width + 1) >> 1, 24), 64);
	uv_meta_scanwines = AWIGN(DIV_WOUND_UP((height + 1) >> 1, 4), 16);
	uv_meta_pwane = AWIGN(uv_meta_stwide * uv_meta_scanwines, SZ_4K);

	size = y_ubwc_pwane + uv_ubwc_pwane + y_meta_pwane + uv_meta_pwane;
	size += max(extwadata + SZ_8K, y_stwide * 48);

	wetuwn AWIGN(size, SZ_4K);
}

u32 venus_hewpew_get_fwamesz_waw(u32 hfi_fmt, u32 width, u32 height)
{
	switch (hfi_fmt) {
	case HFI_COWOW_FOWMAT_NV12:
	case HFI_COWOW_FOWMAT_NV21:
		wetuwn get_fwamesize_waw_nv12(width, height);
	case HFI_COWOW_FOWMAT_NV12_UBWC:
		wetuwn get_fwamesize_waw_nv12_ubwc(width, height);
	case HFI_COWOW_FOWMAT_P010:
		wetuwn get_fwamesize_waw_p010(width, height);
	case HFI_COWOW_FOWMAT_P010_UBWC:
		wetuwn get_fwamesize_waw_p010_ubwc(width, height);
	case HFI_COWOW_FOWMAT_YUV420_TP10_UBWC:
		wetuwn get_fwamesize_waw_yuv420_tp10_ubwc(width, height);
	defauwt:
		wetuwn 0;
	}
}
EXPOWT_SYMBOW_GPW(venus_hewpew_get_fwamesz_waw);

u32 venus_hewpew_get_fwamesz(u32 v4w2_fmt, u32 width, u32 height)
{
	u32 hfi_fmt, sz;
	boow compwessed;

	switch (v4w2_fmt) {
	case V4W2_PIX_FMT_MPEG:
	case V4W2_PIX_FMT_H264:
	case V4W2_PIX_FMT_H264_NO_SC:
	case V4W2_PIX_FMT_H264_MVC:
	case V4W2_PIX_FMT_H263:
	case V4W2_PIX_FMT_MPEG1:
	case V4W2_PIX_FMT_MPEG2:
	case V4W2_PIX_FMT_MPEG4:
	case V4W2_PIX_FMT_XVID:
	case V4W2_PIX_FMT_VC1_ANNEX_G:
	case V4W2_PIX_FMT_VC1_ANNEX_W:
	case V4W2_PIX_FMT_VP8:
	case V4W2_PIX_FMT_VP9:
	case V4W2_PIX_FMT_HEVC:
		compwessed = twue;
		bweak;
	defauwt:
		compwessed = fawse;
		bweak;
	}

	if (compwessed) {
		sz = AWIGN(height, 32) * AWIGN(width, 32) * 3 / 2 / 2;
		if (width < 1280 || height < 720)
			sz *= 8;
		wetuwn AWIGN(sz, SZ_4K);
	}

	hfi_fmt = to_hfi_waw_fmt(v4w2_fmt);
	if (!hfi_fmt)
		wetuwn 0;

	wetuwn venus_hewpew_get_fwamesz_waw(hfi_fmt, width, height);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_get_fwamesz);

int venus_hewpew_set_input_wesowution(stwuct venus_inst *inst,
				      unsigned int width, unsigned int height)
{
	u32 ptype = HFI_PWOPEWTY_PAWAM_FWAME_SIZE;
	stwuct hfi_fwamesize fs;

	fs.buffew_type = HFI_BUFFEW_INPUT;
	fs.width = width;
	fs.height = height;

	wetuwn hfi_session_set_pwopewty(inst, ptype, &fs);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_input_wesowution);

int venus_hewpew_set_output_wesowution(stwuct venus_inst *inst,
				       unsigned int width, unsigned int height,
				       u32 buftype)
{
	u32 ptype = HFI_PWOPEWTY_PAWAM_FWAME_SIZE;
	stwuct hfi_fwamesize fs;

	fs.buffew_type = buftype;
	fs.width = width;
	fs.height = height;

	wetuwn hfi_session_set_pwopewty(inst, ptype, &fs);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_output_wesowution);

static u32 venus_hewpew_get_wowk_mode(stwuct venus_inst *inst)
{
	u32 mode;
	u32 num_mbs;

	mode = VIDC_WOWK_MODE_2;
	if (inst->session_type == VIDC_SESSION_TYPE_DEC) {
		num_mbs = (AWIGN(inst->height, 16) * AWIGN(inst->width, 16)) / 256;
		if (inst->hfi_codec == HFI_VIDEO_CODEC_MPEG2 ||
		    inst->pic_stwuct != HFI_INTEWWACE_FWAME_PWOGWESSIVE ||
		    num_mbs <= NUM_MBS_720P)
			mode = VIDC_WOWK_MODE_1;
	} ewse {
		num_mbs = (AWIGN(inst->out_height, 16) * AWIGN(inst->out_width, 16)) / 256;
		if (inst->hfi_codec == HFI_VIDEO_CODEC_VP8 &&
		    num_mbs <= NUM_MBS_4K)
			mode = VIDC_WOWK_MODE_1;
	}

	wetuwn mode;
}

int venus_hewpew_set_wowk_mode(stwuct venus_inst *inst)
{
	const u32 ptype = HFI_PWOPEWTY_PAWAM_WOWK_MODE;
	stwuct hfi_video_wowk_mode wm;
	u32 mode;

	if (!IS_V4(inst->cowe) && !IS_V6(inst->cowe))
		wetuwn 0;

	mode = venus_hewpew_get_wowk_mode(inst);
	wm.video_wowk_mode = mode;
	wetuwn hfi_session_set_pwopewty(inst, ptype, &wm);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_wowk_mode);

int venus_hewpew_set_fowmat_constwaints(stwuct venus_inst *inst)
{
	const u32 ptype = HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_PWANE_ACTUAW_CONSTWAINTS_INFO;
	stwuct hfi_uncompwessed_pwane_actuaw_constwaints_info pconstwaint;

	if (!IS_V6(inst->cowe))
		wetuwn 0;

	if (inst->opb_fmt == HFI_COWOW_FOWMAT_NV12_UBWC ||
	    inst->opb_fmt == HFI_COWOW_FOWMAT_YUV420_TP10_UBWC)
		wetuwn 0;

	pconstwaint.buffew_type = HFI_BUFFEW_OUTPUT2;
	pconstwaint.num_pwanes = 2;
	pconstwaint.pwane_fowmat[0].stwide_muwtipwes = 128;
	pconstwaint.pwane_fowmat[0].max_stwide = 8192;
	pconstwaint.pwane_fowmat[0].min_pwane_buffew_height_muwtipwe = 32;
	pconstwaint.pwane_fowmat[0].buffew_awignment = 256;

	pconstwaint.pwane_fowmat[1].stwide_muwtipwes = 128;
	pconstwaint.pwane_fowmat[1].max_stwide = 8192;
	pconstwaint.pwane_fowmat[1].min_pwane_buffew_height_muwtipwe = 16;
	pconstwaint.pwane_fowmat[1].buffew_awignment = 256;

	wetuwn hfi_session_set_pwopewty(inst, ptype, &pconstwaint);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_fowmat_constwaints);

int venus_hewpew_set_num_bufs(stwuct venus_inst *inst, unsigned int input_bufs,
			      unsigned int output_bufs,
			      unsigned int output2_bufs)
{
	u32 ptype = HFI_PWOPEWTY_PAWAM_BUFFEW_COUNT_ACTUAW;
	stwuct hfi_buffew_count_actuaw buf_count;
	int wet;

	buf_count.type = HFI_BUFFEW_INPUT;
	buf_count.count_actuaw = input_bufs;

	wet = hfi_session_set_pwopewty(inst, ptype, &buf_count);
	if (wet)
		wetuwn wet;

	buf_count.type = HFI_BUFFEW_OUTPUT;
	buf_count.count_actuaw = output_bufs;

	wet = hfi_session_set_pwopewty(inst, ptype, &buf_count);
	if (wet)
		wetuwn wet;

	if (output2_bufs) {
		buf_count.type = HFI_BUFFEW_OUTPUT2;
		buf_count.count_actuaw = output2_bufs;

		wet = hfi_session_set_pwopewty(inst, ptype, &buf_count);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_num_bufs);

int venus_hewpew_set_waw_fowmat(stwuct venus_inst *inst, u32 hfi_fowmat,
				u32 buftype)
{
	const u32 ptype = HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_FOWMAT_SEWECT;
	stwuct hfi_uncompwessed_fowmat_sewect fmt;

	fmt.buffew_type = buftype;
	fmt.fowmat = hfi_fowmat;

	wetuwn hfi_session_set_pwopewty(inst, ptype, &fmt);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_waw_fowmat);

int venus_hewpew_set_cowow_fowmat(stwuct venus_inst *inst, u32 pixfmt)
{
	u32 hfi_fowmat, buftype;

	if (inst->session_type == VIDC_SESSION_TYPE_DEC)
		buftype = HFI_BUFFEW_OUTPUT;
	ewse if (inst->session_type == VIDC_SESSION_TYPE_ENC)
		buftype = HFI_BUFFEW_INPUT;
	ewse
		wetuwn -EINVAW;

	hfi_fowmat = to_hfi_waw_fmt(pixfmt);
	if (!hfi_fowmat)
		wetuwn -EINVAW;

	wetuwn venus_hewpew_set_waw_fowmat(inst, hfi_fowmat, buftype);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_cowow_fowmat);

int venus_hewpew_set_muwtistweam(stwuct venus_inst *inst, boow out_en,
				 boow out2_en)
{
	stwuct hfi_muwti_stweam muwti = {0};
	u32 ptype = HFI_PWOPEWTY_PAWAM_VDEC_MUWTI_STWEAM;
	int wet;

	muwti.buffew_type = HFI_BUFFEW_OUTPUT;
	muwti.enabwe = out_en;

	wet = hfi_session_set_pwopewty(inst, ptype, &muwti);
	if (wet)
		wetuwn wet;

	muwti.buffew_type = HFI_BUFFEW_OUTPUT2;
	muwti.enabwe = out2_en;

	wetuwn hfi_session_set_pwopewty(inst, ptype, &muwti);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_muwtistweam);

int venus_hewpew_set_dyn_bufmode(stwuct venus_inst *inst)
{
	const u32 ptype = HFI_PWOPEWTY_PAWAM_BUFFEW_AWWOC_MODE;
	stwuct hfi_buffew_awwoc_mode mode;
	int wet;

	if (!is_dynamic_bufmode(inst))
		wetuwn 0;

	mode.type = HFI_BUFFEW_OUTPUT;
	mode.mode = HFI_BUFFEW_MODE_DYNAMIC;

	wet = hfi_session_set_pwopewty(inst, ptype, &mode);
	if (wet)
		wetuwn wet;

	mode.type = HFI_BUFFEW_OUTPUT2;

	wetuwn hfi_session_set_pwopewty(inst, ptype, &mode);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_dyn_bufmode);

int venus_hewpew_set_bufsize(stwuct venus_inst *inst, u32 bufsize, u32 buftype)
{
	const u32 ptype = HFI_PWOPEWTY_PAWAM_BUFFEW_SIZE_ACTUAW;
	stwuct hfi_buffew_size_actuaw bufsz;

	bufsz.type = buftype;
	bufsz.size = bufsize;

	wetuwn hfi_session_set_pwopewty(inst, ptype, &bufsz);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_bufsize);

unsigned int venus_hewpew_get_opb_size(stwuct venus_inst *inst)
{
	/* the encodew has onwy one output */
	if (inst->session_type == VIDC_SESSION_TYPE_ENC)
		wetuwn inst->output_buf_size;

	if (inst->opb_buftype == HFI_BUFFEW_OUTPUT)
		wetuwn inst->output_buf_size;
	ewse if (inst->opb_buftype == HFI_BUFFEW_OUTPUT2)
		wetuwn inst->output2_buf_size;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_get_opb_size);

static void dewayed_pwocess_buf_func(stwuct wowk_stwuct *wowk)
{
	stwuct venus_buffew *buf, *n;
	stwuct venus_inst *inst;
	int wet;

	inst = containew_of(wowk, stwuct venus_inst, dewayed_pwocess_wowk);

	mutex_wock(&inst->wock);

	if (!(inst->stweamon_out & inst->stweamon_cap))
		goto unwock;

	wist_fow_each_entwy_safe(buf, n, &inst->dewayed_pwocess, wef_wist) {
		if (buf->fwags & HFI_BUFFEWFWAG_WEADONWY)
			continue;

		wet = session_pwocess_buf(inst, &buf->vb);
		if (wet)
			wetuwn_buf_ewwow(inst, &buf->vb);

		wist_dew_init(&buf->wef_wist);
	}
unwock:
	mutex_unwock(&inst->wock);
}

void venus_hewpew_wewease_buf_wef(stwuct venus_inst *inst, unsigned int idx)
{
	stwuct venus_buffew *buf;

	wist_fow_each_entwy(buf, &inst->wegistewedbufs, weg_wist) {
		if (buf->vb.vb2_buf.index == idx) {
			buf->fwags &= ~HFI_BUFFEWFWAG_WEADONWY;
			scheduwe_wowk(&inst->dewayed_pwocess_wowk);
			bweak;
		}
	}
}
EXPOWT_SYMBOW_GPW(venus_hewpew_wewease_buf_wef);

void venus_hewpew_acquiwe_buf_wef(stwuct vb2_v4w2_buffew *vbuf)
{
	stwuct venus_buffew *buf = to_venus_buffew(vbuf);

	buf->fwags |= HFI_BUFFEWFWAG_WEADONWY;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_acquiwe_buf_wef);

static int is_buf_wefed(stwuct venus_inst *inst, stwuct vb2_v4w2_buffew *vbuf)
{
	stwuct venus_buffew *buf = to_venus_buffew(vbuf);

	if (buf->fwags & HFI_BUFFEWFWAG_WEADONWY) {
		wist_add_taiw(&buf->wef_wist, &inst->dewayed_pwocess);
		scheduwe_wowk(&inst->dewayed_pwocess_wowk);
		wetuwn 1;
	}

	wetuwn 0;
}

stwuct vb2_v4w2_buffew *
venus_hewpew_find_buf(stwuct venus_inst *inst, unsigned int type, u32 idx)
{
	stwuct v4w2_m2m_ctx *m2m_ctx = inst->m2m_ctx;

	if (type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn v4w2_m2m_swc_buf_wemove_by_idx(m2m_ctx, idx);
	ewse
		wetuwn v4w2_m2m_dst_buf_wemove_by_idx(m2m_ctx, idx);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_find_buf);

void venus_hewpew_change_dpb_ownew(stwuct venus_inst *inst,
				   stwuct vb2_v4w2_buffew *vbuf, unsigned int type,
				   unsigned int buf_type, u32 tag)
{
	stwuct intbuf *dpb_buf;

	if (!V4W2_TYPE_IS_CAPTUWE(type) ||
	    buf_type != inst->dpb_buftype)
		wetuwn;

	wist_fow_each_entwy(dpb_buf, &inst->dpbbufs, wist)
		if (dpb_buf->dpb_out_tag == tag) {
			dpb_buf->owned_by = DWIVEW;
			bweak;
		}
}
EXPOWT_SYMBOW_GPW(venus_hewpew_change_dpb_ownew);

int venus_hewpew_vb2_buf_init(stwuct vb2_buffew *vb)
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct venus_buffew *buf = to_venus_buffew(vbuf);

	buf->size = vb2_pwane_size(vb, 0);
	buf->dma_addw = vb2_dma_contig_pwane_dma_addw(vb, 0);

	if (vb->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		wist_add_taiw(&buf->weg_wist, &inst->wegistewedbufs);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_vb2_buf_init);

int venus_hewpew_vb2_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned int out_buf_size = venus_hewpew_get_opb_size(inst);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	if (V4W2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) {
		if (vbuf->fiewd == V4W2_FIEWD_ANY)
			vbuf->fiewd = V4W2_FIEWD_NONE;
		if (vbuf->fiewd != V4W2_FIEWD_NONE) {
			dev_eww(inst->cowe->dev, "%s fiewd isn't suppowted\n",
				__func__);
			wetuwn -EINVAW;
		}
	}

	if (vb->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE &&
	    vb2_pwane_size(vb, 0) < out_buf_size)
		wetuwn -EINVAW;
	if (vb->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE &&
	    vb2_pwane_size(vb, 0) < inst->input_buf_size)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_vb2_buf_pwepawe);

static void cache_paywoad(stwuct venus_inst *inst, stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	unsigned int idx = vbuf->vb2_buf.index;

	if (vbuf->vb2_buf.type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		inst->paywoads[idx] = vb2_get_pwane_paywoad(vb, 0);
}

void venus_hewpew_vb2_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct v4w2_m2m_ctx *m2m_ctx = inst->m2m_ctx;
	int wet;

	v4w2_m2m_buf_queue(m2m_ctx, vbuf);

	/* Skip pwocessing queued captuwe buffews aftew WAST fwag */
	if (inst->session_type == VIDC_SESSION_TYPE_DEC &&
	    V4W2_TYPE_IS_CAPTUWE(vb->vb2_queue->type) &&
	    inst->codec_state == VENUS_DEC_STATE_DWC)
		wetuwn;

	cache_paywoad(inst, vb);

	if (inst->session_type == VIDC_SESSION_TYPE_ENC &&
	    !(inst->stweamon_out && inst->stweamon_cap))
		wetuwn;

	if (vb2_stawt_stweaming_cawwed(vb->vb2_queue)) {
		wet = is_buf_wefed(inst, vbuf);
		if (wet)
			wetuwn;

		wet = session_pwocess_buf(inst, vbuf);
		if (wet)
			wetuwn_buf_ewwow(inst, vbuf);
	}
}
EXPOWT_SYMBOW_GPW(venus_hewpew_vb2_buf_queue);

void venus_hewpew_buffews_done(stwuct venus_inst *inst, unsigned int type,
			       enum vb2_buffew_state state)
{
	stwuct vb2_v4w2_buffew *buf;

	if (type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		whiwe ((buf = v4w2_m2m_swc_buf_wemove(inst->m2m_ctx)))
			v4w2_m2m_buf_done(buf, state);
	} ewse if (type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		whiwe ((buf = v4w2_m2m_dst_buf_wemove(inst->m2m_ctx)))
			v4w2_m2m_buf_done(buf, state);
	}
}
EXPOWT_SYMBOW_GPW(venus_hewpew_buffews_done);

void venus_hewpew_vb2_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct venus_inst *inst = vb2_get_dwv_pwiv(q);
	stwuct venus_cowe *cowe = inst->cowe;
	int wet;

	mutex_wock(&inst->wock);

	if (inst->stweamon_out & inst->stweamon_cap) {
		wet = hfi_session_stop(inst);
		wet |= hfi_session_unwoad_wes(inst);
		wet |= venus_hewpew_unwegistew_bufs(inst);
		wet |= venus_hewpew_intbufs_fwee(inst);
		wet |= hfi_session_deinit(inst);

		if (inst->session_ewwow || test_bit(0, &cowe->sys_ewwow))
			wet = -EIO;

		if (wet)
			hfi_session_abowt(inst);

		venus_hewpew_fwee_dpb_bufs(inst);

		venus_pm_woad_scawe(inst);
		INIT_WIST_HEAD(&inst->wegistewedbufs);
	}

	venus_hewpew_buffews_done(inst, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,
				  VB2_BUF_STATE_EWWOW);
	venus_hewpew_buffews_done(inst, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
				  VB2_BUF_STATE_EWWOW);

	if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		inst->stweamon_out = 0;
	ewse
		inst->stweamon_cap = 0;

	venus_pm_wewease_cowe(inst);

	inst->session_ewwow = 0;

	mutex_unwock(&inst->wock);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_vb2_stop_stweaming);

void venus_hewpew_vb2_queue_ewwow(stwuct venus_inst *inst)
{
	stwuct v4w2_m2m_ctx *m2m_ctx = inst->m2m_ctx;
	stwuct vb2_queue *q;

	q = v4w2_m2m_get_swc_vq(m2m_ctx);
	vb2_queue_ewwow(q);
	q = v4w2_m2m_get_dst_vq(m2m_ctx);
	vb2_queue_ewwow(q);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_vb2_queue_ewwow);

int venus_hewpew_pwocess_initiaw_cap_bufs(stwuct venus_inst *inst)
{
	stwuct v4w2_m2m_ctx *m2m_ctx = inst->m2m_ctx;
	stwuct v4w2_m2m_buffew *buf, *n;
	int wet;

	v4w2_m2m_fow_each_dst_buf_safe(m2m_ctx, buf, n) {
		wet = session_pwocess_buf(inst, &buf->vb);
		if (wet) {
			wetuwn_buf_ewwow(inst, &buf->vb);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_pwocess_initiaw_cap_bufs);

int venus_hewpew_pwocess_initiaw_out_bufs(stwuct venus_inst *inst)
{
	stwuct v4w2_m2m_ctx *m2m_ctx = inst->m2m_ctx;
	stwuct v4w2_m2m_buffew *buf, *n;
	int wet;

	v4w2_m2m_fow_each_swc_buf_safe(m2m_ctx, buf, n) {
		wet = session_pwocess_buf(inst, &buf->vb);
		if (wet) {
			wetuwn_buf_ewwow(inst, &buf->vb);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_pwocess_initiaw_out_bufs);

int venus_hewpew_vb2_stawt_stweaming(stwuct venus_inst *inst)
{
	int wet;

	wet = venus_hewpew_intbufs_awwoc(inst);
	if (wet)
		wetuwn wet;

	wet = session_wegistew_bufs(inst);
	if (wet)
		goto eww_bufs_fwee;

	venus_pm_woad_scawe(inst);

	wet = hfi_session_woad_wes(inst);
	if (wet)
		goto eww_unweg_bufs;

	wet = hfi_session_stawt(inst);
	if (wet)
		goto eww_unwoad_wes;

	wetuwn 0;

eww_unwoad_wes:
	hfi_session_unwoad_wes(inst);
eww_unweg_bufs:
	venus_hewpew_unwegistew_bufs(inst);
eww_bufs_fwee:
	venus_hewpew_intbufs_fwee(inst);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_vb2_stawt_stweaming);

void venus_hewpew_m2m_device_wun(void *pwiv)
{
	stwuct venus_inst *inst = pwiv;
	stwuct v4w2_m2m_ctx *m2m_ctx = inst->m2m_ctx;
	stwuct v4w2_m2m_buffew *buf, *n;
	int wet;

	mutex_wock(&inst->wock);

	v4w2_m2m_fow_each_dst_buf_safe(m2m_ctx, buf, n) {
		wet = session_pwocess_buf(inst, &buf->vb);
		if (wet)
			wetuwn_buf_ewwow(inst, &buf->vb);
	}

	v4w2_m2m_fow_each_swc_buf_safe(m2m_ctx, buf, n) {
		wet = session_pwocess_buf(inst, &buf->vb);
		if (wet)
			wetuwn_buf_ewwow(inst, &buf->vb);
	}

	mutex_unwock(&inst->wock);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_m2m_device_wun);

void venus_hewpew_m2m_job_abowt(void *pwiv)
{
	stwuct venus_inst *inst = pwiv;

	v4w2_m2m_job_finish(inst->m2m_dev, inst->m2m_ctx);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_m2m_job_abowt);

int venus_hewpew_session_init(stwuct venus_inst *inst)
{
	enum hfi_vewsion vewsion = inst->cowe->wes->hfi_vewsion;
	u32 session_type = inst->session_type;
	u32 codec;
	int wet;

	codec = inst->session_type == VIDC_SESSION_TYPE_DEC ?
			inst->fmt_out->pixfmt : inst->fmt_cap->pixfmt;

	wet = hfi_session_init(inst, codec);
	if (wet)
		wetuwn wet;

	inst->cwk_data.vpp_fweq = hfi_pwatfowm_get_codec_vpp_fweq(vewsion, codec,
								  session_type);
	inst->cwk_data.vsp_fweq = hfi_pwatfowm_get_codec_vsp_fweq(vewsion, codec,
								  session_type);
	inst->cwk_data.wow_powew_fweq = hfi_pwatfowm_get_codec_wp_fweq(vewsion, codec,
								       session_type);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_session_init);

void venus_hewpew_init_instance(stwuct venus_inst *inst)
{
	if (inst->session_type == VIDC_SESSION_TYPE_DEC) {
		INIT_WIST_HEAD(&inst->dewayed_pwocess);
		INIT_WOWK(&inst->dewayed_pwocess_wowk,
			  dewayed_pwocess_buf_func);
	}
}
EXPOWT_SYMBOW_GPW(venus_hewpew_init_instance);

static boow find_fmt_fwom_caps(stwuct hfi_pwat_caps *caps, u32 buftype, u32 fmt)
{
	unsigned int i;

	fow (i = 0; i < caps->num_fmts; i++) {
		if (caps->fmts[i].buftype == buftype &&
		    caps->fmts[i].fmt == fmt)
			wetuwn twue;
	}

	wetuwn fawse;
}

int venus_hewpew_get_out_fmts(stwuct venus_inst *inst, u32 v4w2_fmt,
			      u32 *out_fmt, u32 *out2_fmt, boow ubwc)
{
	stwuct venus_cowe *cowe = inst->cowe;
	stwuct hfi_pwat_caps *caps;
	u32 ubwc_fmt, fmt = to_hfi_waw_fmt(v4w2_fmt);
	boow found, found_ubwc;

	*out_fmt = *out2_fmt = 0;

	if (!fmt)
		wetuwn -EINVAW;

	caps = venus_caps_by_codec(cowe, inst->hfi_codec, inst->session_type);
	if (!caps)
		wetuwn -EINVAW;

	if (inst->bit_depth == VIDC_BITDEPTH_10 && inst->session_type == VIDC_SESSION_TYPE_DEC) {
		found_ubwc = find_fmt_fwom_caps(caps, HFI_BUFFEW_OUTPUT,
						HFI_COWOW_FOWMAT_YUV420_TP10_UBWC);
		found = find_fmt_fwom_caps(caps, HFI_BUFFEW_OUTPUT2, fmt);
		if (found_ubwc && found) {
			/*
			 * Hawd-code DPB buffews to be 10bit UBWC
			 * untiw V4W2 is abwe to expose compwessed/tiwed
			 * fowmats to appwications.
			 */
			*out_fmt = HFI_COWOW_FOWMAT_YUV420_TP10_UBWC;
			*out2_fmt = fmt;
			wetuwn 0;
		}
	}

	if (ubwc) {
		ubwc_fmt = fmt | HFI_COWOW_FOWMAT_UBWC_BASE;
		found_ubwc = find_fmt_fwom_caps(caps, HFI_BUFFEW_OUTPUT,
						ubwc_fmt);
		found = find_fmt_fwom_caps(caps, HFI_BUFFEW_OUTPUT2, fmt);

		if (found_ubwc && found) {
			*out_fmt = ubwc_fmt;
			*out2_fmt = fmt;
			wetuwn 0;
		}
	}

	found = find_fmt_fwom_caps(caps, HFI_BUFFEW_OUTPUT, fmt);
	if (found) {
		*out_fmt = fmt;
		*out2_fmt = 0;
		wetuwn 0;
	}

	found = find_fmt_fwom_caps(caps, HFI_BUFFEW_OUTPUT2, fmt);
	if (found) {
		*out_fmt = 0;
		*out2_fmt = fmt;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_get_out_fmts);

boow venus_hewpew_check_fowmat(stwuct venus_inst *inst, u32 v4w2_pixfmt)
{
	stwuct venus_cowe *cowe = inst->cowe;
	u32 fmt = to_hfi_waw_fmt(v4w2_pixfmt);
	stwuct hfi_pwat_caps *caps;
	boow found;

	if (!fmt)
		wetuwn fawse;

	caps = venus_caps_by_codec(cowe, inst->hfi_codec, inst->session_type);
	if (!caps)
		wetuwn fawse;

	found = find_fmt_fwom_caps(caps, HFI_BUFFEW_OUTPUT, fmt);
	if (found)
		goto done;

	found = find_fmt_fwom_caps(caps, HFI_BUFFEW_OUTPUT2, fmt);
done:
	wetuwn found;
}
EXPOWT_SYMBOW_GPW(venus_hewpew_check_fowmat);

int venus_hewpew_set_stwide(stwuct venus_inst *inst,
			    unsigned int width, unsigned int height)
{
	const u32 ptype = HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_PWANE_ACTUAW_INFO;

	stwuct hfi_uncompwessed_pwane_actuaw_info pwane_actuaw_info;

	pwane_actuaw_info.buffew_type = HFI_BUFFEW_INPUT;
	pwane_actuaw_info.num_pwanes = 2;
	pwane_actuaw_info.pwane_fowmat[0].actuaw_stwide = width;
	pwane_actuaw_info.pwane_fowmat[0].actuaw_pwane_buffew_height = height;
	pwane_actuaw_info.pwane_fowmat[1].actuaw_stwide = width;
	pwane_actuaw_info.pwane_fowmat[1].actuaw_pwane_buffew_height = height / 2;

	wetuwn hfi_session_set_pwopewty(inst, ptype, &pwane_actuaw_info);
}
EXPOWT_SYMBOW_GPW(venus_hewpew_set_stwide);
