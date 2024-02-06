// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2016, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2017 Winawo Wtd.
 */
#incwude <winux/types.h>
#incwude <media/v4w2-ctwws.h>

#incwude "cowe.h"
#incwude "hewpews.h"
#incwude "vdec.h"

static int vdec_op_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct venus_inst *inst = ctww_to_inst(ctww);
	stwuct vdec_contwows *ctw = &inst->contwows.dec;

	switch (ctww->id) {
	case V4W2_CID_MPEG_VIDEO_DECODEW_MPEG4_DEBWOCK_FIWTEW:
		ctw->post_woop_deb_mode = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_PWOFIWE:
	case V4W2_CID_MPEG_VIDEO_MPEG4_PWOFIWE:
	case V4W2_CID_MPEG_VIDEO_VP8_PWOFIWE:
	case V4W2_CID_MPEG_VIDEO_VP9_PWOFIWE:
		ctw->pwofiwe = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_WEVEW:
	case V4W2_CID_MPEG_VIDEO_MPEG4_WEVEW:
	case V4W2_CID_MPEG_VIDEO_VP9_WEVEW:
		ctw->wevew = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_DEC_DISPWAY_DEWAY:
		ctw->dispway_deway = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_DEC_DISPWAY_DEWAY_ENABWE:
		ctw->dispway_deway_enabwe = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_DEC_CONCEAW_COWOW:
		ctw->conceaw_cowow = *ctww->p_new.p_s64;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vdec_op_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct venus_inst *inst = ctww_to_inst(ctww);
	stwuct vdec_contwows *ctw = &inst->contwows.dec;
	stwuct hfi_buffew_wequiwements bufweq;
	enum hfi_vewsion vew = inst->cowe->wes->hfi_vewsion;
	u32 pwofiwe, wevew;
	int wet;

	switch (ctww->id) {
	case V4W2_CID_MPEG_VIDEO_H264_PWOFIWE:
	case V4W2_CID_MPEG_VIDEO_MPEG4_PWOFIWE:
	case V4W2_CID_MPEG_VIDEO_VP8_PWOFIWE:
	case V4W2_CID_MPEG_VIDEO_VP9_PWOFIWE:
		wet = venus_hewpew_get_pwofiwe_wevew(inst, &pwofiwe, &wevew);
		if (!wet)
			ctw->pwofiwe = pwofiwe;
		ctww->vaw = ctw->pwofiwe;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_WEVEW:
	case V4W2_CID_MPEG_VIDEO_MPEG4_WEVEW:
	case V4W2_CID_MPEG_VIDEO_VP9_WEVEW:
		wet = venus_hewpew_get_pwofiwe_wevew(inst, &pwofiwe, &wevew);
		if (!wet)
			ctw->wevew = wevew;
		ctww->vaw = ctw->wevew;
		bweak;
	case V4W2_CID_MPEG_VIDEO_DECODEW_MPEG4_DEBWOCK_FIWTEW:
		ctww->vaw = ctw->post_woop_deb_mode;
		bweak;
	case V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE:
		wet = venus_hewpew_get_bufweq(inst, HFI_BUFFEW_OUTPUT, &bufweq);
		if (!wet)
			ctww->vaw = hfi_bufweq_get_count_min(&bufweq, vew);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops vdec_ctww_ops = {
	.s_ctww = vdec_op_s_ctww,
	.g_vowatiwe_ctww = vdec_op_g_vowatiwe_ctww,
};

int vdec_ctww_init(stwuct venus_inst *inst)
{
	stwuct v4w2_ctww *ctww;
	int wet;

	wet = v4w2_ctww_handwew_init(&inst->ctww_handwew, 12);
	if (wet)
		wetuwn wet;

	ctww = v4w2_ctww_new_std_menu(&inst->ctww_handwew, &vdec_ctww_ops,
		V4W2_CID_MPEG_VIDEO_MPEG4_PWOFIWE,
		V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_ADVANCED_CODING_EFFICIENCY,
		~((1 << V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_SIMPWE) |
		  (1 << V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_ADVANCED_SIMPWE)),
		V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_SIMPWE);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	ctww = v4w2_ctww_new_std_menu(&inst->ctww_handwew, &vdec_ctww_ops,
				      V4W2_CID_MPEG_VIDEO_MPEG4_WEVEW,
				      V4W2_MPEG_VIDEO_MPEG4_WEVEW_5,
				      0, V4W2_MPEG_VIDEO_MPEG4_WEVEW_0);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	ctww = v4w2_ctww_new_std_menu(&inst->ctww_handwew, &vdec_ctww_ops,
		V4W2_CID_MPEG_VIDEO_H264_PWOFIWE,
		V4W2_MPEG_VIDEO_H264_PWOFIWE_MUWTIVIEW_HIGH,
		~((1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE) |
		  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_CONSTWAINED_BASEWINE) |
		  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN) |
		  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH) |
		  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_STEWEO_HIGH) |
		  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_MUWTIVIEW_HIGH)),
		V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	ctww = v4w2_ctww_new_std_menu(&inst->ctww_handwew, &vdec_ctww_ops,
				      V4W2_CID_MPEG_VIDEO_H264_WEVEW,
				      V4W2_MPEG_VIDEO_H264_WEVEW_5_1,
				      0, V4W2_MPEG_VIDEO_H264_WEVEW_1_0);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	ctww = v4w2_ctww_new_std_menu(&inst->ctww_handwew, &vdec_ctww_ops,
				      V4W2_CID_MPEG_VIDEO_VP8_PWOFIWE,
				      V4W2_MPEG_VIDEO_VP8_PWOFIWE_3,
				      0, V4W2_MPEG_VIDEO_VP8_PWOFIWE_0);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	ctww = v4w2_ctww_new_std_menu(&inst->ctww_handwew, &vdec_ctww_ops,
				      V4W2_CID_MPEG_VIDEO_VP9_PWOFIWE,
				      V4W2_MPEG_VIDEO_VP9_PWOFIWE_3,
				      0, V4W2_MPEG_VIDEO_VP9_PWOFIWE_0);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	ctww = v4w2_ctww_new_std_menu(&inst->ctww_handwew, &vdec_ctww_ops,
				      V4W2_CID_MPEG_VIDEO_VP9_WEVEW,
				      V4W2_MPEG_VIDEO_VP9_WEVEW_6_2,
				      0, V4W2_MPEG_VIDEO_VP9_WEVEW_1_0);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	v4w2_ctww_new_std(&inst->ctww_handwew, &vdec_ctww_ops,
		V4W2_CID_MPEG_VIDEO_DECODEW_MPEG4_DEBWOCK_FIWTEW, 0, 1, 1, 0);

	ctww = v4w2_ctww_new_std(&inst->ctww_handwew, &vdec_ctww_ops,
		V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE, 1, 32, 1, 1);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	v4w2_ctww_new_std(&inst->ctww_handwew, &vdec_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_DEC_DISPWAY_DEWAY,
			  0, 16383, 1, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &vdec_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_DEC_DISPWAY_DEWAY_ENABWE,
			  0, 1, 1, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &vdec_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_DEC_CONCEAW_COWOW, 0,
			  0xffffffffffffWW, 1, 0x8000800010WW);

	wet = inst->ctww_handwew.ewwow;
	if (wet) {
		v4w2_ctww_handwew_fwee(&inst->ctww_handwew);
		wetuwn wet;
	}

	wetuwn 0;
}

void vdec_ctww_deinit(stwuct venus_inst *inst)
{
	v4w2_ctww_handwew_fwee(&inst->ctww_handwew);
}
