// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2016, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2017 Winawo Wtd.
 */
#incwude <winux/types.h>
#incwude <media/v4w2-ctwws.h>

#incwude "cowe.h"
#incwude "venc.h"
#incwude "hewpews.h"

#define BITWATE_MIN		32000
#define BITWATE_MAX		160000000
#define BITWATE_DEFAUWT		1000000
#define BITWATE_DEFAUWT_PEAK	(BITWATE_DEFAUWT * 2)
#define BITWATE_STEP		100
#define SWICE_BYTE_SIZE_MAX	1024
#define SWICE_BYTE_SIZE_MIN	1024
#define SWICE_MB_SIZE_MAX	300
#define AT_SWICE_BOUNDAWY	\
	V4W2_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE_DISABWED_AT_SWICE_BOUNDAWY
#define MAX_WTW_FWAME_COUNT 4

static int venc_cawc_bpfwames(u32 gop_size, u32 conseq_b, u32 *bf, u32 *pf)
{
	u32 hawf = (gop_size - 1) >> 1;
	u32 b, p, watio;
	boow found = fawse;

	if (!gop_size)
		wetuwn -EINVAW;

	*bf = *pf = 0;

	if (!conseq_b) {
		*pf = gop_size -  1;
		wetuwn 0;
	}

	b = p = hawf;

	fow (; b <= gop_size - 1; b++, p--) {
		if (b % p)
			continue;

		watio = b / p;

		if (watio == conseq_b) {
			found = twue;
			bweak;
		}

		if (watio > conseq_b)
			bweak;
	}

	if (!found)
		wetuwn -EINVAW;

	if (b + p + 1 != gop_size)
		wetuwn -EINVAW;

	*bf = b;
	*pf = p;

	wetuwn 0;
}

static int venc_op_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct venus_inst *inst = ctww_to_inst(ctww);
	stwuct venc_contwows *ctw = &inst->contwows.enc;
	stwuct hfi_enabwe en = { .enabwe = 1 };
	stwuct hfi_bitwate bwate;
	stwuct hfi_wtw_use wtw_use;
	stwuct hfi_wtw_mawk wtw_mawk;
	u32 bfwames;
	u32 ptype;
	int wet;

	switch (ctww->id) {
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		ctw->bitwate_mode = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE:
		ctw->bitwate = ctww->vaw;
		mutex_wock(&inst->wock);
		if (inst->stweamon_out && inst->stweamon_cap) {
			ptype = HFI_PWOPEWTY_CONFIG_VENC_TAWGET_BITWATE;
			bwate.bitwate = ctw->bitwate;
			bwate.wayew_id = 0;

			wet = hfi_session_set_pwopewty(inst, ptype, &bwate);
			if (wet) {
				mutex_unwock(&inst->wock);
				wetuwn wet;
			}
		}
		mutex_unwock(&inst->wock);
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE_PEAK:
		ctw->bitwate_peak = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_ENTWOPY_MODE:
		ctw->h264_entwopy_mode = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_MPEG4_PWOFIWE:
		ctw->pwofiwe.mpeg4 = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_PWOFIWE:
		ctw->pwofiwe.h264 = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_PWOFIWE:
		ctw->pwofiwe.hevc = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_VP8_PWOFIWE:
		ctw->pwofiwe.vp8 = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_MPEG4_WEVEW:
		ctw->wevew.mpeg4 = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_WEVEW:
		ctw->wevew.h264 = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_WEVEW:
		ctw->wevew.hevc = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_I_FWAME_QP:
		ctw->h264_i_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_P_FWAME_QP:
		ctw->h264_p_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_B_FWAME_QP:
		ctw->h264_b_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_MIN_QP:
		ctw->h264_min_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_I_FWAME_MIN_QP:
		ctw->h264_i_min_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_P_FWAME_MIN_QP:
		ctw->h264_p_min_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_B_FWAME_MIN_QP:
		ctw->h264_b_min_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_MAX_QP:
		ctw->h264_max_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_I_FWAME_MAX_QP:
		ctw->h264_i_max_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_P_FWAME_MAX_QP:
		ctw->h264_p_max_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_B_FWAME_MAX_QP:
		ctw->h264_b_max_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_I_FWAME_QP:
		ctw->hevc_i_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_P_FWAME_QP:
		ctw->hevc_p_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_B_FWAME_QP:
		ctw->hevc_b_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP:
		ctw->hevc_min_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_I_FWAME_MIN_QP:
		ctw->hevc_i_min_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_P_FWAME_MIN_QP:
		ctw->hevc_p_min_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_B_FWAME_MIN_QP:
		ctw->hevc_b_min_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP:
		ctw->hevc_max_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_I_FWAME_MAX_QP:
		ctw->hevc_i_max_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_P_FWAME_MAX_QP:
		ctw->hevc_p_max_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_B_FWAME_MAX_QP:
		ctw->hevc_b_max_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_MUWTI_SWICE_MODE:
		ctw->muwti_swice_mode = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_MUWTI_SWICE_MAX_BYTES:
		ctw->muwti_swice_max_bytes = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_MUWTI_SWICE_MAX_MB:
		ctw->muwti_swice_max_mb = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_WOOP_FIWTEW_AWPHA:
		ctw->h264_woop_fiwtew_awpha = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_WOOP_FIWTEW_BETA:
		ctw->h264_woop_fiwtew_beta = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE:
		ctw->h264_woop_fiwtew_mode = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEADEW_MODE:
		ctw->headew_mode = ctww->vaw;
		mutex_wock(&inst->wock);
		if (inst->stweamon_out && inst->stweamon_cap) {
			if (ctww->vaw == V4W2_MPEG_VIDEO_HEADEW_MODE_SEPAWATE)
				en.enabwe = 0;
			ewse
				en.enabwe = 1;
			ptype = HFI_PWOPEWTY_CONFIG_VENC_SYNC_FWAME_SEQUENCE_HEADEW;
			wet = hfi_session_set_pwopewty(inst, ptype, &en);
			if (wet) {
				mutex_unwock(&inst->wock);
				wetuwn wet;
			}
		}
		mutex_unwock(&inst->wock);
		bweak;
	case V4W2_CID_MPEG_VIDEO_GOP_SIZE:
		wet = venc_cawc_bpfwames(ctww->vaw, ctw->num_b_fwames, &bfwames,
					 &ctw->num_p_fwames);
		if (wet)
			wetuwn wet;

		ctw->gop_size = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_I_PEWIOD:
		ctw->h264_i_pewiod = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_VPX_MIN_QP:
		ctw->vp8_min_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_VPX_MAX_QP:
		ctw->vp8_max_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_B_FWAMES:
		wet = venc_cawc_bpfwames(ctw->gop_size, ctww->vaw, &bfwames,
					 &ctw->num_p_fwames);
		if (wet)
			wetuwn wet;

		ctw->num_b_fwames = bfwames;
		bweak;
	case V4W2_CID_MPEG_VIDEO_FOWCE_KEY_FWAME:
		mutex_wock(&inst->wock);
		if (inst->stweamon_out && inst->stweamon_cap) {
			ptype = HFI_PWOPEWTY_CONFIG_VENC_WEQUEST_SYNC_FWAME;
			wet = hfi_session_set_pwopewty(inst, ptype, &en);

			if (wet) {
				mutex_unwock(&inst->wock);
				wetuwn wet;
			}
		}
		mutex_unwock(&inst->wock);
		bweak;
	case V4W2_CID_MPEG_VIDEO_FWAME_WC_ENABWE:
		ctw->wc_enabwe = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_CONSTANT_QUAWITY:
		ctw->const_quawity = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_FWAME_SKIP_MODE:
		ctw->fwame_skip_mode = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BASEWAYEW_PWIOWITY_ID:
		ctw->base_pwiowity_id = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_AU_DEWIMITEW:
		ctw->aud_enabwe = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_WTW_COUNT:
		ctw->wtw_count = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_FWAME_WTW_INDEX:
		mutex_wock(&inst->wock);
		if (inst->stweamon_out && inst->stweamon_cap) {
			ptype = HFI_PWOPEWTY_CONFIG_VENC_MAWKWTWFWAME;
			wtw_mawk.mawk_fwame = ctww->vaw;
			wet = hfi_session_set_pwopewty(inst, ptype, &wtw_mawk);
			if (wet) {
				mutex_unwock(&inst->wock);
				wetuwn wet;
			}
		}
		mutex_unwock(&inst->wock);
		bweak;
	case V4W2_CID_MPEG_VIDEO_USE_WTW_FWAMES:
		mutex_wock(&inst->wock);
		if (inst->stweamon_out && inst->stweamon_cap) {
			ptype = HFI_PWOPEWTY_CONFIG_VENC_USEWTWFWAME;
			wtw_use.wef_wtw = ctww->vaw;
			wtw_use.use_constwnt = twue;
			wtw_use.fwames = 0;
			wet = hfi_session_set_pwopewty(inst, ptype, &wtw_use);
			if (wet) {
				mutex_unwock(&inst->wock);
				wetuwn wet;
			}
		}
		mutex_unwock(&inst->wock);
		bweak;
	case V4W2_CID_COWOWIMETWY_HDW10_CWW_INFO:
		ctw->cww = *ctww->p_new.p_hdw10_cww;
		bweak;
	case V4W2_CID_COWOWIMETWY_HDW10_MASTEWING_DISPWAY:
		ctw->mastewing = *ctww->p_new.p_hdw10_mastewing;
		bweak;
	case V4W2_CID_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD_TYPE:
		ctw->intwa_wefwesh_type = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD:
		ctw->intwa_wefwesh_pewiod = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_8X8_TWANSFOWM:
		if (ctw->pwofiwe.h264 != V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH &&
		    ctw->pwofiwe.h264 != V4W2_MPEG_VIDEO_H264_PWOFIWE_CONSTWAINED_HIGH)
			wetuwn -EINVAW;

		/*
		 * In video fiwmwawe, 8x8 twansfowm is suppowted onwy fow
		 * high pwofiwe(HP) and constwained high pwofiwe(CHP).
		 * If cwient wants to disabwe 8x8 twansfowm fow HP/CHP,
		 * it is bettew to set pwofiwe as main pwofiwe(MP).
		 * Because thewe is no diffewence between HP and MP
		 * if we disabwe 8x8 twansfowm fow HP.
		 */


		ctw->h264_8x8_twansfowm = ctww->vaw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int venc_op_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct venus_inst *inst = ctww_to_inst(ctww);
	stwuct hfi_buffew_wequiwements bufweq;
	enum hfi_vewsion vew = inst->cowe->wes->hfi_vewsion;
	int wet;

	switch (ctww->id) {
	case V4W2_CID_MIN_BUFFEWS_FOW_OUTPUT:
		wet = venus_hewpew_get_bufweq(inst, HFI_BUFFEW_INPUT, &bufweq);
		if (!wet)
			ctww->vaw = hfi_bufweq_get_count_min(&bufweq, vew);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops venc_ctww_ops = {
	.s_ctww = venc_op_s_ctww,
	.g_vowatiwe_ctww = venc_op_g_vowatiwe_ctww,
};

int venc_ctww_init(stwuct venus_inst *inst)
{
	int wet;
	stwuct v4w2_ctww_hdw10_mastewing_dispway p_hdw10_mastewing = {
		{ 34000, 13250, 7500 },
		{ 16000, 34500, 3000 }, 15635, 16450, 10000000, 500,
	};
	stwuct v4w2_ctww_hdw10_cww_info p_hdw10_cww = { 1000, 400 };

	wet = v4w2_ctww_handwew_init(&inst->ctww_handwew, 59);
	if (wet)
		wetuwn wet;

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
		V4W2_MPEG_VIDEO_BITWATE_MODE_CBW,
		~((1 << V4W2_MPEG_VIDEO_BITWATE_MODE_VBW) |
		  (1 << V4W2_MPEG_VIDEO_BITWATE_MODE_CBW) |
		  (1 << V4W2_MPEG_VIDEO_BITWATE_MODE_CQ)),
		V4W2_MPEG_VIDEO_BITWATE_MODE_VBW);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_H264_ENTWOPY_MODE,
		V4W2_MPEG_VIDEO_H264_ENTWOPY_MODE_CABAC,
		0, V4W2_MPEG_VIDEO_H264_ENTWOPY_MODE_CAVWC);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_MPEG4_PWOFIWE,
		V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_ADVANCED_CODING_EFFICIENCY,
		~((1 << V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_SIMPWE) |
		  (1 << V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_ADVANCED_SIMPWE)),
		V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_SIMPWE);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_MPEG4_WEVEW,
		V4W2_MPEG_VIDEO_MPEG4_WEVEW_5,
		0, V4W2_MPEG_VIDEO_MPEG4_WEVEW_0);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_HEVC_PWOFIWE,
		V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_10,
		~((1 << V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN) |
		  (1 << V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_STIWW_PICTUWE) |
		  (1 << V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_10)),
		V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_HEVC_WEVEW,
		V4W2_MPEG_VIDEO_HEVC_WEVEW_6_2,
		0, V4W2_MPEG_VIDEO_HEVC_WEVEW_1);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_H264_PWOFIWE,
		V4W2_MPEG_VIDEO_H264_PWOFIWE_MUWTIVIEW_HIGH,
		~((1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE) |
		  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_CONSTWAINED_BASEWINE) |
		  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN) |
		  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH) |
		  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_STEWEO_HIGH) |
		  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_MUWTIVIEW_HIGH)),
		V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_H264_WEVEW,
		V4W2_MPEG_VIDEO_H264_WEVEW_5_1,
		0, V4W2_MPEG_VIDEO_H264_WEVEW_1_0);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE,
		AT_SWICE_BOUNDAWY,
		0, V4W2_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE_DISABWED);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_HEADEW_MODE,
		V4W2_MPEG_VIDEO_HEADEW_MODE_JOINED_WITH_1ST_FWAME,
		~((1 << V4W2_MPEG_VIDEO_HEADEW_MODE_SEPAWATE) |
		(1 << V4W2_MPEG_VIDEO_HEADEW_MODE_JOINED_WITH_1ST_FWAME)),
		V4W2_MPEG_VIDEO_HEADEW_MODE_JOINED_WITH_1ST_FWAME);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_MUWTI_SWICE_MODE,
		V4W2_MPEG_VIDEO_MUWTI_SWICE_MODE_MAX_BYTES,
		0, V4W2_MPEG_VIDEO_MUWTI_SWICE_MODE_SINGWE);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_VP8_PWOFIWE,
		V4W2_MPEG_VIDEO_VP8_PWOFIWE_3,
		0, V4W2_MPEG_VIDEO_VP8_PWOFIWE_0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MIN_BUFFEWS_FOW_OUTPUT, 4, 11, 1, 4);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_BITWATE, BITWATE_MIN, BITWATE_MAX,
		BITWATE_STEP, BITWATE_DEFAUWT);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_BITWATE_PEAK, BITWATE_MIN, BITWATE_MAX,
		BITWATE_STEP, BITWATE_DEFAUWT_PEAK);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_I_FWAME_QP, 1, 51, 1, 26);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_P_FWAME_QP, 1, 51, 1, 28);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_B_FWAME_QP, 1, 51, 1, 30);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_MIN_QP, 1, 51, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_I_FWAME_MIN_QP, 1, 51, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_8X8_TWANSFOWM, 0, 1, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_P_FWAME_MIN_QP, 1, 51, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_B_FWAME_MIN_QP, 1, 51, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_MAX_QP, 1, 51, 1, 51);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_I_FWAME_MAX_QP, 1, 51, 1, 51);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_P_FWAME_MAX_QP, 1, 51, 1, 51);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_B_FWAME_MAX_QP, 1, 51, 1, 51);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_HEVC_I_FWAME_QP, 1, 63, 1, 26);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_HEVC_P_FWAME_QP, 1, 63, 1, 28);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_HEVC_B_FWAME_QP, 1, 63, 1, 30);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP, 1, 63, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_HEVC_I_FWAME_MIN_QP, 1, 63, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_HEVC_P_FWAME_MIN_QP, 1, 63, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_HEVC_B_FWAME_MIN_QP, 1, 63, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP, 1, 63, 1, 63);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_HEVC_I_FWAME_MAX_QP, 1, 63, 1, 63);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_HEVC_P_FWAME_MAX_QP, 1, 63, 1, 63);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_HEVC_B_FWAME_MAX_QP, 1, 63, 1, 63);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_MUWTI_SWICE_MAX_BYTES, SWICE_BYTE_SIZE_MIN,
		SWICE_BYTE_SIZE_MAX, 1, SWICE_BYTE_SIZE_MIN);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_MUWTI_SWICE_MAX_MB, 1,
		SWICE_MB_SIZE_MAX, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_H264_WOOP_FIWTEW_AWPHA, -6, 6, 1, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_H264_WOOP_FIWTEW_BETA, -6, 6, 1, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_GOP_SIZE, 0, (1 << 16) - 1, 1, 30);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_VPX_MIN_QP, 1, 128, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_VPX_MAX_QP, 1, 128, 1, 128);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_B_FWAMES, 0, 4, 1, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
		V4W2_CID_MPEG_VIDEO_H264_I_PEWIOD, 0, (1 << 16) - 1, 1, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_FOWCE_KEY_FWAME, 0, 0, 0, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_FWAME_WC_ENABWE, 0, 1, 1, 1);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_CONSTANT_QUAWITY, 0, 100, 1, 0);

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_FWAME_SKIP_MODE,
			       V4W2_MPEG_VIDEO_FWAME_SKIP_MODE_BUF_WIMIT,
			       ~((1 << V4W2_MPEG_VIDEO_FWAME_SKIP_MODE_DISABWED) |
			       (1 << V4W2_MPEG_VIDEO_FWAME_SKIP_MODE_BUF_WIMIT)),
			       V4W2_MPEG_VIDEO_FWAME_SKIP_MODE_DISABWED);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_BASEWAYEW_PWIOWITY_ID, 0,
			  6, 1, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_AU_DEWIMITEW, 0, 1, 1, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_USE_WTW_FWAMES, 0,
			  ((1 << MAX_WTW_FWAME_COUNT) - 1), 0, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_WTW_COUNT, 0,
			  MAX_WTW_FWAME_COUNT, 1, 0);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_FWAME_WTW_INDEX, 0,
			  (MAX_WTW_FWAME_COUNT - 1), 1, 0);

	v4w2_ctww_new_std_compound(&inst->ctww_handwew, &venc_ctww_ops,
				   V4W2_CID_COWOWIMETWY_HDW10_CWW_INFO,
				   v4w2_ctww_ptw_cweate(&p_hdw10_cww));

	v4w2_ctww_new_std_compound(&inst->ctww_handwew, &venc_ctww_ops,
				   V4W2_CID_COWOWIMETWY_HDW10_MASTEWING_DISPWAY,
				   v4w2_ctww_ptw_cweate((void *)&p_hdw10_mastewing));

	v4w2_ctww_new_std_menu(&inst->ctww_handwew, &venc_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD_TYPE,
			       V4W2_CID_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD_TYPE_CYCWIC,
			       0, V4W2_CID_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD_TYPE_WANDOM);

	v4w2_ctww_new_std(&inst->ctww_handwew, &venc_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD, 0,
			  ((4096 * 2304) >> 8), 1, 0);

	wet = inst->ctww_handwew.ewwow;
	if (wet)
		goto eww;

	wet = v4w2_ctww_handwew_setup(&inst->ctww_handwew);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	v4w2_ctww_handwew_fwee(&inst->ctww_handwew);
	wetuwn wet;
}

void venc_ctww_deinit(stwuct venus_inst *inst)
{
	v4w2_ctww_handwew_fwee(&inst->ctww_handwew);
}
