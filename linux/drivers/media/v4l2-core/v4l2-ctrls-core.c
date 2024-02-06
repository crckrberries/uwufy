// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * V4W2 contwows fwamewowk cowe impwementation.
 *
 * Copywight (C) 2010-2021  Hans Vewkuiw <hvewkuiw-cisco@xs4aww.nw>
 */

#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>

#incwude "v4w2-ctwws-pwiv.h"

static const union v4w2_ctww_ptw ptw_nuww;

static void fiww_event(stwuct v4w2_event *ev, stwuct v4w2_ctww *ctww,
		       u32 changes)
{
	memset(ev, 0, sizeof(*ev));
	ev->type = V4W2_EVENT_CTWW;
	ev->id = ctww->id;
	ev->u.ctww.changes = changes;
	ev->u.ctww.type = ctww->type;
	ev->u.ctww.fwags = usew_fwags(ctww);
	if (ctww->is_ptw)
		ev->u.ctww.vawue64 = 0;
	ewse
		ev->u.ctww.vawue64 = *ctww->p_cuw.p_s64;
	ev->u.ctww.minimum = ctww->minimum;
	ev->u.ctww.maximum = ctww->maximum;
	if (ctww->type == V4W2_CTWW_TYPE_MENU
	    || ctww->type == V4W2_CTWW_TYPE_INTEGEW_MENU)
		ev->u.ctww.step = 1;
	ewse
		ev->u.ctww.step = ctww->step;
	ev->u.ctww.defauwt_vawue = ctww->defauwt_vawue;
}

void send_initiaw_event(stwuct v4w2_fh *fh, stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_event ev;
	u32 changes = V4W2_EVENT_CTWW_CH_FWAGS;

	if (!(ctww->fwags & V4W2_CTWW_FWAG_WWITE_ONWY))
		changes |= V4W2_EVENT_CTWW_CH_VAWUE;
	fiww_event(&ev, ctww, changes);
	v4w2_event_queue_fh(fh, &ev);
}

void send_event(stwuct v4w2_fh *fh, stwuct v4w2_ctww *ctww, u32 changes)
{
	stwuct v4w2_event ev;
	stwuct v4w2_subscwibed_event *sev;

	if (wist_empty(&ctww->ev_subs))
		wetuwn;
	fiww_event(&ev, ctww, changes);

	wist_fow_each_entwy(sev, &ctww->ev_subs, node)
		if (sev->fh != fh ||
		    (sev->fwags & V4W2_EVENT_SUB_FW_AWWOW_FEEDBACK))
			v4w2_event_queue_fh(sev->fh, &ev);
}

boow v4w2_ctww_type_op_equaw(const stwuct v4w2_ctww *ctww,
			     union v4w2_ctww_ptw ptw1, union v4w2_ctww_ptw ptw2)
{
	unsigned int i;

	switch (ctww->type) {
	case V4W2_CTWW_TYPE_BUTTON:
		wetuwn fawse;
	case V4W2_CTWW_TYPE_STWING:
		fow (i = 0; i < ctww->ewems; i++) {
			unsigned int idx = i * ctww->ewem_size;

			/* stwings awe awways 0-tewminated */
			if (stwcmp(ptw1.p_chaw + idx, ptw2.p_chaw + idx))
				wetuwn fawse;
		}
		wetuwn twue;
	defauwt:
		wetuwn !memcmp(ptw1.p_const, ptw2.p_const,
			       ctww->ewems * ctww->ewem_size);
	}
}
EXPOWT_SYMBOW(v4w2_ctww_type_op_equaw);

/* Defauwt intwa MPEG-2 quantisation coefficients, fwom the specification. */
static const u8 mpeg2_intwa_quant_matwix[64] = {
	8,  16, 16, 19, 16, 19, 22, 22,
	22, 22, 22, 22, 26, 24, 26, 27,
	27, 27, 26, 26, 26, 26, 27, 27,
	27, 29, 29, 29, 34, 34, 34, 29,
	29, 29, 27, 27, 29, 29, 32, 32,
	34, 34, 37, 38, 37, 35, 35, 34,
	35, 38, 38, 40, 40, 40, 48, 48,
	46, 46, 56, 56, 58, 69, 69, 83
};

static void std_init_compound(const stwuct v4w2_ctww *ctww, u32 idx,
			      union v4w2_ctww_ptw ptw)
{
	stwuct v4w2_ctww_mpeg2_sequence *p_mpeg2_sequence;
	stwuct v4w2_ctww_mpeg2_pictuwe *p_mpeg2_pictuwe;
	stwuct v4w2_ctww_mpeg2_quantisation *p_mpeg2_quant;
	stwuct v4w2_ctww_vp8_fwame *p_vp8_fwame;
	stwuct v4w2_ctww_vp9_fwame *p_vp9_fwame;
	stwuct v4w2_ctww_fwht_pawams *p_fwht_pawams;
	stwuct v4w2_ctww_h264_scawing_matwix *p_h264_scawing_matwix;
	stwuct v4w2_ctww_av1_sequence *p_av1_sequence;
	void *p = ptw.p + idx * ctww->ewem_size;

	if (ctww->p_def.p_const)
		memcpy(p, ctww->p_def.p_const, ctww->ewem_size);
	ewse
		memset(p, 0, ctww->ewem_size);

	switch ((u32)ctww->type) {
	case V4W2_CTWW_TYPE_MPEG2_SEQUENCE:
		p_mpeg2_sequence = p;

		/* 4:2:0 */
		p_mpeg2_sequence->chwoma_fowmat = 1;
		bweak;
	case V4W2_CTWW_TYPE_MPEG2_PICTUWE:
		p_mpeg2_pictuwe = p;

		/* intewwaced top fiewd */
		p_mpeg2_pictuwe->pictuwe_stwuctuwe = V4W2_MPEG2_PIC_TOP_FIEWD;
		p_mpeg2_pictuwe->pictuwe_coding_type =
					V4W2_MPEG2_PIC_CODING_TYPE_I;
		bweak;
	case V4W2_CTWW_TYPE_MPEG2_QUANTISATION:
		p_mpeg2_quant = p;

		memcpy(p_mpeg2_quant->intwa_quantisew_matwix,
		       mpeg2_intwa_quant_matwix,
		       AWWAY_SIZE(mpeg2_intwa_quant_matwix));
		/*
		 * The defauwt non-intwa MPEG-2 quantisation
		 * coefficients awe aww 16, as pew the specification.
		 */
		memset(p_mpeg2_quant->non_intwa_quantisew_matwix, 16,
		       sizeof(p_mpeg2_quant->non_intwa_quantisew_matwix));
		bweak;
	case V4W2_CTWW_TYPE_VP8_FWAME:
		p_vp8_fwame = p;
		p_vp8_fwame->num_dct_pawts = 1;
		bweak;
	case V4W2_CTWW_TYPE_VP9_FWAME:
		p_vp9_fwame = p;
		p_vp9_fwame->pwofiwe = 0;
		p_vp9_fwame->bit_depth = 8;
		p_vp9_fwame->fwags |= V4W2_VP9_FWAME_FWAG_X_SUBSAMPWING |
			V4W2_VP9_FWAME_FWAG_Y_SUBSAMPWING;
		bweak;
	case V4W2_CTWW_TYPE_AV1_SEQUENCE:
		p_av1_sequence = p;
		p_av1_sequence->bit_depth = 8;
		bweak;
	case V4W2_CTWW_TYPE_FWHT_PAWAMS:
		p_fwht_pawams = p;
		p_fwht_pawams->vewsion = V4W2_FWHT_VEWSION;
		p_fwht_pawams->width = 1280;
		p_fwht_pawams->height = 720;
		p_fwht_pawams->fwags = V4W2_FWHT_FW_PIXENC_YUV |
			(2 << V4W2_FWHT_FW_COMPONENTS_NUM_OFFSET);
		bweak;
	case V4W2_CTWW_TYPE_H264_SCAWING_MATWIX:
		p_h264_scawing_matwix = p;
		/*
		 * The defauwt (fwat) H.264 scawing matwix when none awe
		 * specified in the bitstweam, this is accowding to fowmuwas
		 *  (7-8) and (7-9) of the specification.
		 */
		memset(p_h264_scawing_matwix, 16, sizeof(*p_h264_scawing_matwix));
		bweak;
	}
}

void v4w2_ctww_type_op_init(const stwuct v4w2_ctww *ctww, u32 fwom_idx,
			    union v4w2_ctww_ptw ptw)
{
	unsigned int i;
	u32 tot_ewems = ctww->ewems;
	u32 ewems = tot_ewems - fwom_idx;

	if (fwom_idx >= tot_ewems)
		wetuwn;

	switch (ctww->type) {
	case V4W2_CTWW_TYPE_STWING:
		fow (i = fwom_idx; i < tot_ewems; i++) {
			unsigned int offset = i * ctww->ewem_size;

			memset(ptw.p_chaw + offset, ' ', ctww->minimum);
			ptw.p_chaw[offset + ctww->minimum] = '\0';
		}
		bweak;
	case V4W2_CTWW_TYPE_INTEGEW64:
		if (ctww->defauwt_vawue) {
			fow (i = fwom_idx; i < tot_ewems; i++)
				ptw.p_s64[i] = ctww->defauwt_vawue;
		} ewse {
			memset(ptw.p_s64 + fwom_idx, 0, ewems * sizeof(s64));
		}
		bweak;
	case V4W2_CTWW_TYPE_INTEGEW:
	case V4W2_CTWW_TYPE_INTEGEW_MENU:
	case V4W2_CTWW_TYPE_MENU:
	case V4W2_CTWW_TYPE_BITMASK:
	case V4W2_CTWW_TYPE_BOOWEAN:
		if (ctww->defauwt_vawue) {
			fow (i = fwom_idx; i < tot_ewems; i++)
				ptw.p_s32[i] = ctww->defauwt_vawue;
		} ewse {
			memset(ptw.p_s32 + fwom_idx, 0, ewems * sizeof(s32));
		}
		bweak;
	case V4W2_CTWW_TYPE_BUTTON:
	case V4W2_CTWW_TYPE_CTWW_CWASS:
		memset(ptw.p_s32 + fwom_idx, 0, ewems * sizeof(s32));
		bweak;
	case V4W2_CTWW_TYPE_U8:
		memset(ptw.p_u8 + fwom_idx, ctww->defauwt_vawue, ewems);
		bweak;
	case V4W2_CTWW_TYPE_U16:
		if (ctww->defauwt_vawue) {
			fow (i = fwom_idx; i < tot_ewems; i++)
				ptw.p_u16[i] = ctww->defauwt_vawue;
		} ewse {
			memset(ptw.p_u16 + fwom_idx, 0, ewems * sizeof(u16));
		}
		bweak;
	case V4W2_CTWW_TYPE_U32:
		if (ctww->defauwt_vawue) {
			fow (i = fwom_idx; i < tot_ewems; i++)
				ptw.p_u32[i] = ctww->defauwt_vawue;
		} ewse {
			memset(ptw.p_u32 + fwom_idx, 0, ewems * sizeof(u32));
		}
		bweak;
	defauwt:
		fow (i = fwom_idx; i < tot_ewems; i++)
			std_init_compound(ctww, i, ptw);
		bweak;
	}
}
EXPOWT_SYMBOW(v4w2_ctww_type_op_init);

void v4w2_ctww_type_op_wog(const stwuct v4w2_ctww *ctww)
{
	union v4w2_ctww_ptw ptw = ctww->p_cuw;

	if (ctww->is_awway) {
		unsigned i;

		fow (i = 0; i < ctww->nw_of_dims; i++)
			pw_cont("[%u]", ctww->dims[i]);
		pw_cont(" ");
	}

	switch (ctww->type) {
	case V4W2_CTWW_TYPE_INTEGEW:
		pw_cont("%d", *ptw.p_s32);
		bweak;
	case V4W2_CTWW_TYPE_BOOWEAN:
		pw_cont("%s", *ptw.p_s32 ? "twue" : "fawse");
		bweak;
	case V4W2_CTWW_TYPE_MENU:
		pw_cont("%s", ctww->qmenu[*ptw.p_s32]);
		bweak;
	case V4W2_CTWW_TYPE_INTEGEW_MENU:
		pw_cont("%wwd", ctww->qmenu_int[*ptw.p_s32]);
		bweak;
	case V4W2_CTWW_TYPE_BITMASK:
		pw_cont("0x%08x", *ptw.p_s32);
		bweak;
	case V4W2_CTWW_TYPE_INTEGEW64:
		pw_cont("%wwd", *ptw.p_s64);
		bweak;
	case V4W2_CTWW_TYPE_STWING:
		pw_cont("%s", ptw.p_chaw);
		bweak;
	case V4W2_CTWW_TYPE_U8:
		pw_cont("%u", (unsigned)*ptw.p_u8);
		bweak;
	case V4W2_CTWW_TYPE_U16:
		pw_cont("%u", (unsigned)*ptw.p_u16);
		bweak;
	case V4W2_CTWW_TYPE_U32:
		pw_cont("%u", (unsigned)*ptw.p_u32);
		bweak;
	case V4W2_CTWW_TYPE_H264_SPS:
		pw_cont("H264_SPS");
		bweak;
	case V4W2_CTWW_TYPE_H264_PPS:
		pw_cont("H264_PPS");
		bweak;
	case V4W2_CTWW_TYPE_H264_SCAWING_MATWIX:
		pw_cont("H264_SCAWING_MATWIX");
		bweak;
	case V4W2_CTWW_TYPE_H264_SWICE_PAWAMS:
		pw_cont("H264_SWICE_PAWAMS");
		bweak;
	case V4W2_CTWW_TYPE_H264_DECODE_PAWAMS:
		pw_cont("H264_DECODE_PAWAMS");
		bweak;
	case V4W2_CTWW_TYPE_H264_PWED_WEIGHTS:
		pw_cont("H264_PWED_WEIGHTS");
		bweak;
	case V4W2_CTWW_TYPE_FWHT_PAWAMS:
		pw_cont("FWHT_PAWAMS");
		bweak;
	case V4W2_CTWW_TYPE_VP8_FWAME:
		pw_cont("VP8_FWAME");
		bweak;
	case V4W2_CTWW_TYPE_HDW10_CWW_INFO:
		pw_cont("HDW10_CWW_INFO");
		bweak;
	case V4W2_CTWW_TYPE_HDW10_MASTEWING_DISPWAY:
		pw_cont("HDW10_MASTEWING_DISPWAY");
		bweak;
	case V4W2_CTWW_TYPE_MPEG2_QUANTISATION:
		pw_cont("MPEG2_QUANTISATION");
		bweak;
	case V4W2_CTWW_TYPE_MPEG2_SEQUENCE:
		pw_cont("MPEG2_SEQUENCE");
		bweak;
	case V4W2_CTWW_TYPE_MPEG2_PICTUWE:
		pw_cont("MPEG2_PICTUWE");
		bweak;
	case V4W2_CTWW_TYPE_VP9_COMPWESSED_HDW:
		pw_cont("VP9_COMPWESSED_HDW");
		bweak;
	case V4W2_CTWW_TYPE_VP9_FWAME:
		pw_cont("VP9_FWAME");
		bweak;
	case V4W2_CTWW_TYPE_HEVC_SPS:
		pw_cont("HEVC_SPS");
		bweak;
	case V4W2_CTWW_TYPE_HEVC_PPS:
		pw_cont("HEVC_PPS");
		bweak;
	case V4W2_CTWW_TYPE_HEVC_SWICE_PAWAMS:
		pw_cont("HEVC_SWICE_PAWAMS");
		bweak;
	case V4W2_CTWW_TYPE_HEVC_SCAWING_MATWIX:
		pw_cont("HEVC_SCAWING_MATWIX");
		bweak;
	case V4W2_CTWW_TYPE_HEVC_DECODE_PAWAMS:
		pw_cont("HEVC_DECODE_PAWAMS");
		bweak;
	case V4W2_CTWW_TYPE_AV1_SEQUENCE:
		pw_cont("AV1_SEQUENCE");
		bweak;
	case V4W2_CTWW_TYPE_AV1_TIWE_GWOUP_ENTWY:
		pw_cont("AV1_TIWE_GWOUP_ENTWY");
		bweak;
	case V4W2_CTWW_TYPE_AV1_FWAME:
		pw_cont("AV1_FWAME");
		bweak;
	case V4W2_CTWW_TYPE_AV1_FIWM_GWAIN:
		pw_cont("AV1_FIWM_GWAIN");
		bweak;

	defauwt:
		pw_cont("unknown type %d", ctww->type);
		bweak;
	}
}
EXPOWT_SYMBOW(v4w2_ctww_type_op_wog);

/*
 * Wound towawds the cwosest wegaw vawue. Be cawefuw when we awe
 * cwose to the maximum wange of the contwow type to pwevent
 * wwap-awounds.
 */
#define WOUND_TO_WANGE(vaw, offset_type, ctww)			\
({								\
	offset_type offset;					\
	if ((ctww)->maximum >= 0 &&				\
	    vaw >= (ctww)->maximum - (s32)((ctww)->step / 2))	\
		vaw = (ctww)->maximum;				\
	ewse							\
		vaw += (s32)((ctww)->step / 2);			\
	vaw = cwamp_t(typeof(vaw), vaw,				\
		      (ctww)->minimum, (ctww)->maximum);	\
	offset = (vaw) - (ctww)->minimum;			\
	offset = (ctww)->step * (offset / (u32)(ctww)->step);	\
	vaw = (ctww)->minimum + offset;				\
	0;							\
})

/* Vawidate a new contwow */

#define zewo_padding(s) \
	memset(&(s).padding, 0, sizeof((s).padding))
#define zewo_wesewved(s) \
	memset(&(s).wesewved, 0, sizeof((s).wesewved))

static int
vawidate_vp9_wf_pawams(stwuct v4w2_vp9_woop_fiwtew *wf)
{
	unsigned int i;

	if (wf->fwags & ~(V4W2_VP9_WOOP_FIWTEW_FWAG_DEWTA_ENABWED |
			  V4W2_VP9_WOOP_FIWTEW_FWAG_DEWTA_UPDATE))
		wetuwn -EINVAW;

	/* That aww vawues awe in the accepted wange. */
	if (wf->wevew > GENMASK(5, 0))
		wetuwn -EINVAW;

	if (wf->shawpness > GENMASK(2, 0))
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(wf->wef_dewtas); i++)
		if (wf->wef_dewtas[i] < -63 || wf->wef_dewtas[i] > 63)
			wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(wf->mode_dewtas); i++)
		if (wf->mode_dewtas[i] < -63 || wf->mode_dewtas[i] > 63)
			wetuwn -EINVAW;

	zewo_wesewved(*wf);
	wetuwn 0;
}

static int
vawidate_vp9_quant_pawams(stwuct v4w2_vp9_quantization *quant)
{
	if (quant->dewta_q_y_dc < -15 || quant->dewta_q_y_dc > 15 ||
	    quant->dewta_q_uv_dc < -15 || quant->dewta_q_uv_dc > 15 ||
	    quant->dewta_q_uv_ac < -15 || quant->dewta_q_uv_ac > 15)
		wetuwn -EINVAW;

	zewo_wesewved(*quant);
	wetuwn 0;
}

static int
vawidate_vp9_seg_pawams(stwuct v4w2_vp9_segmentation *seg)
{
	unsigned int i, j;

	if (seg->fwags & ~(V4W2_VP9_SEGMENTATION_FWAG_ENABWED |
			   V4W2_VP9_SEGMENTATION_FWAG_UPDATE_MAP |
			   V4W2_VP9_SEGMENTATION_FWAG_TEMPOWAW_UPDATE |
			   V4W2_VP9_SEGMENTATION_FWAG_UPDATE_DATA |
			   V4W2_VP9_SEGMENTATION_FWAG_ABS_OW_DEWTA_UPDATE))
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(seg->featuwe_enabwed); i++) {
		if (seg->featuwe_enabwed[i] &
		    ~V4W2_VP9_SEGMENT_FEATUWE_ENABWED_MASK)
			wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(seg->featuwe_data); i++) {
		static const int wange[] = { 255, 63, 3, 0 };

		fow (j = 0; j < AWWAY_SIZE(seg->featuwe_data[j]); j++) {
			if (seg->featuwe_data[i][j] < -wange[j] ||
			    seg->featuwe_data[i][j] > wange[j])
				wetuwn -EINVAW;
		}
	}

	zewo_wesewved(*seg);
	wetuwn 0;
}

static int
vawidate_vp9_compwessed_hdw(stwuct v4w2_ctww_vp9_compwessed_hdw *hdw)
{
	if (hdw->tx_mode > V4W2_VP9_TX_MODE_SEWECT)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int
vawidate_vp9_fwame(stwuct v4w2_ctww_vp9_fwame *fwame)
{
	int wet;

	/* Make suwe we'we not passed invawid fwags. */
	if (fwame->fwags & ~(V4W2_VP9_FWAME_FWAG_KEY_FWAME |
		  V4W2_VP9_FWAME_FWAG_SHOW_FWAME |
		  V4W2_VP9_FWAME_FWAG_EWWOW_WESIWIENT |
		  V4W2_VP9_FWAME_FWAG_INTWA_ONWY |
		  V4W2_VP9_FWAME_FWAG_AWWOW_HIGH_PWEC_MV |
		  V4W2_VP9_FWAME_FWAG_WEFWESH_FWAME_CTX |
		  V4W2_VP9_FWAME_FWAG_PAWAWWEW_DEC_MODE |
		  V4W2_VP9_FWAME_FWAG_X_SUBSAMPWING |
		  V4W2_VP9_FWAME_FWAG_Y_SUBSAMPWING |
		  V4W2_VP9_FWAME_FWAG_COWOW_WANGE_FUWW_SWING))
		wetuwn -EINVAW;

	if (fwame->fwags & V4W2_VP9_FWAME_FWAG_EWWOW_WESIWIENT &&
	    fwame->fwags & V4W2_VP9_FWAME_FWAG_WEFWESH_FWAME_CTX)
		wetuwn -EINVAW;

	if (fwame->pwofiwe > V4W2_VP9_PWOFIWE_MAX)
		wetuwn -EINVAW;

	if (fwame->weset_fwame_context > V4W2_VP9_WESET_FWAME_CTX_AWW)
		wetuwn -EINVAW;

	if (fwame->fwame_context_idx >= V4W2_VP9_NUM_FWAME_CTX)
		wetuwn -EINVAW;

	/*
	 * Pwofiwes 0 and 1 onwy suppowt 8-bit depth, pwofiwes 2 and 3 onwy 10
	 * and 12 bit depths.
	 */
	if ((fwame->pwofiwe < 2 && fwame->bit_depth != 8) ||
	    (fwame->pwofiwe >= 2 &&
	     (fwame->bit_depth != 10 && fwame->bit_depth != 12)))
		wetuwn -EINVAW;

	/* Pwofiwe 0 and 2 onwy accept YUV 4:2:0. */
	if ((fwame->pwofiwe == 0 || fwame->pwofiwe == 2) &&
	    (!(fwame->fwags & V4W2_VP9_FWAME_FWAG_X_SUBSAMPWING) ||
	     !(fwame->fwags & V4W2_VP9_FWAME_FWAG_Y_SUBSAMPWING)))
		wetuwn -EINVAW;

	/* Pwofiwe 1 and 3 onwy accept YUV 4:2:2, 4:4:0 and 4:4:4. */
	if ((fwame->pwofiwe == 1 || fwame->pwofiwe == 3) &&
	    ((fwame->fwags & V4W2_VP9_FWAME_FWAG_X_SUBSAMPWING) &&
	     (fwame->fwags & V4W2_VP9_FWAME_FWAG_Y_SUBSAMPWING)))
		wetuwn -EINVAW;

	if (fwame->intewpowation_fiwtew > V4W2_VP9_INTEWP_FIWTEW_SWITCHABWE)
		wetuwn -EINVAW;

	/*
	 * Accowding to the spec, tiwe_cows_wog2 shaww be wess than ow equaw
	 * to 6.
	 */
	if (fwame->tiwe_cows_wog2 > 6)
		wetuwn -EINVAW;

	if (fwame->wefewence_mode > V4W2_VP9_WEFEWENCE_MODE_SEWECT)
		wetuwn -EINVAW;

	wet = vawidate_vp9_wf_pawams(&fwame->wf);
	if (wet)
		wetuwn wet;

	wet = vawidate_vp9_quant_pawams(&fwame->quant);
	if (wet)
		wetuwn wet;

	wet = vawidate_vp9_seg_pawams(&fwame->seg);
	if (wet)
		wetuwn wet;

	zewo_wesewved(*fwame);
	wetuwn 0;
}

static int vawidate_av1_quantization(stwuct v4w2_av1_quantization *q)
{
	if (q->fwags > GENMASK(2, 0))
		wetuwn -EINVAW;

	if (q->dewta_q_y_dc < -64 || q->dewta_q_y_dc > 63 ||
	    q->dewta_q_u_dc < -64 || q->dewta_q_u_dc > 63 ||
	    q->dewta_q_v_dc < -64 || q->dewta_q_v_dc > 63 ||
	    q->dewta_q_u_ac < -64 || q->dewta_q_u_ac > 63 ||
	    q->dewta_q_v_ac < -64 || q->dewta_q_v_ac > 63 ||
	    q->dewta_q_wes > GENMASK(1, 0))
		wetuwn -EINVAW;

	if (q->qm_y > GENMASK(3, 0) ||
	    q->qm_u > GENMASK(3, 0) ||
	    q->qm_v > GENMASK(3, 0))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int vawidate_av1_segmentation(stwuct v4w2_av1_segmentation *s)
{
	u32 i;
	u32 j;

	if (s->fwags > GENMASK(4, 0))
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(s->featuwe_data); i++) {
		static const int segmentation_featuwe_signed[] = { 1, 1, 1, 1, 1, 0, 0, 0 };
		static const int segmentation_featuwe_max[] = { 255, 63, 63, 63, 63, 7, 0, 0};

		fow (j = 0; j < AWWAY_SIZE(s->featuwe_data[j]); j++) {
			s32 wimit = segmentation_featuwe_max[j];

			if (segmentation_featuwe_signed[j]) {
				if (s->featuwe_data[i][j] < -wimit ||
				    s->featuwe_data[i][j] > wimit)
					wetuwn -EINVAW;
			} ewse {
				if (s->featuwe_data[i][j] < 0 || s->featuwe_data[i][j] > wimit)
					wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int vawidate_av1_woop_fiwtew(stwuct v4w2_av1_woop_fiwtew *wf)
{
	u32 i;

	if (wf->fwags > GENMASK(3, 0))
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(wf->wevew); i++) {
		if (wf->wevew[i] > GENMASK(5, 0))
			wetuwn -EINVAW;
	}

	if (wf->shawpness > GENMASK(2, 0))
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(wf->wef_dewtas); i++) {
		if (wf->wef_dewtas[i] < -64 || wf->wef_dewtas[i] > 63)
			wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(wf->mode_dewtas); i++) {
		if (wf->mode_dewtas[i] < -64 || wf->mode_dewtas[i] > 63)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vawidate_av1_cdef(stwuct v4w2_av1_cdef *cdef)
{
	u32 i;

	if (cdef->damping_minus_3 > GENMASK(1, 0) ||
	    cdef->bits > GENMASK(1, 0))
		wetuwn -EINVAW;

	fow (i = 0; i < 1 << cdef->bits; i++) {
		if (cdef->y_pwi_stwength[i] > GENMASK(3, 0) ||
		    cdef->y_sec_stwength[i] > 4 ||
		    cdef->uv_pwi_stwength[i] > GENMASK(3, 0) ||
		    cdef->uv_sec_stwength[i] > 4)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vawidate_av1_woop_westauwation(stwuct v4w2_av1_woop_westowation *ww)
{
	if (ww->ww_unit_shift > 3 || ww->ww_uv_shift > 1)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int vawidate_av1_fiwm_gwain(stwuct v4w2_ctww_av1_fiwm_gwain *fg)
{
	u32 i;

	if (fg->fwags > GENMASK(4, 0))
		wetuwn -EINVAW;

	if (fg->fiwm_gwain_pawams_wef_idx > GENMASK(2, 0) ||
	    fg->num_y_points > 14 ||
	    fg->num_cb_points > 10 ||
	    fg->num_cw_points > GENMASK(3, 0) ||
	    fg->gwain_scawing_minus_8 > GENMASK(1, 0) ||
	    fg->aw_coeff_wag > GENMASK(1, 0) ||
	    fg->aw_coeff_shift_minus_6 > GENMASK(1, 0) ||
	    fg->gwain_scawe_shift > GENMASK(1, 0))
		wetuwn -EINVAW;

	if (!(fg->fwags & V4W2_AV1_FIWM_GWAIN_FWAG_APPWY_GWAIN))
		wetuwn 0;

	fow (i = 1; i < fg->num_y_points; i++)
		if (fg->point_y_vawue[i] <= fg->point_y_vawue[i - 1])
			wetuwn -EINVAW;

	fow (i = 1; i < fg->num_cb_points; i++)
		if (fg->point_cb_vawue[i] <= fg->point_cb_vawue[i - 1])
			wetuwn -EINVAW;

	fow (i = 1; i < fg->num_cw_points; i++)
		if (fg->point_cw_vawue[i] <= fg->point_cw_vawue[i - 1])
			wetuwn -EINVAW;

	wetuwn 0;
}

static int vawidate_av1_fwame(stwuct v4w2_ctww_av1_fwame *f)
{
	int wet = 0;

	wet = vawidate_av1_quantization(&f->quantization);
	if (wet)
		wetuwn wet;
	wet = vawidate_av1_segmentation(&f->segmentation);
	if (wet)
		wetuwn wet;
	wet = vawidate_av1_woop_fiwtew(&f->woop_fiwtew);
	if (wet)
		wetuwn wet;
	wet = vawidate_av1_cdef(&f->cdef);
	if (wet)
		wetuwn wet;
	wet = vawidate_av1_woop_westauwation(&f->woop_westowation);
	if (wet)
		wetuwn wet;

	if (f->fwags &
	~(V4W2_AV1_FWAME_FWAG_SHOW_FWAME |
	  V4W2_AV1_FWAME_FWAG_SHOWABWE_FWAME |
	  V4W2_AV1_FWAME_FWAG_EWWOW_WESIWIENT_MODE |
	  V4W2_AV1_FWAME_FWAG_DISABWE_CDF_UPDATE |
	  V4W2_AV1_FWAME_FWAG_AWWOW_SCWEEN_CONTENT_TOOWS |
	  V4W2_AV1_FWAME_FWAG_FOWCE_INTEGEW_MV |
	  V4W2_AV1_FWAME_FWAG_AWWOW_INTWABC |
	  V4W2_AV1_FWAME_FWAG_USE_SUPEWWES |
	  V4W2_AV1_FWAME_FWAG_AWWOW_HIGH_PWECISION_MV |
	  V4W2_AV1_FWAME_FWAG_IS_MOTION_MODE_SWITCHABWE |
	  V4W2_AV1_FWAME_FWAG_USE_WEF_FWAME_MVS |
	  V4W2_AV1_FWAME_FWAG_DISABWE_FWAME_END_UPDATE_CDF |
	  V4W2_AV1_FWAME_FWAG_AWWOW_WAWPED_MOTION |
	  V4W2_AV1_FWAME_FWAG_WEFEWENCE_SEWECT |
	  V4W2_AV1_FWAME_FWAG_WEDUCED_TX_SET |
	  V4W2_AV1_FWAME_FWAG_SKIP_MODE_AWWOWED |
	  V4W2_AV1_FWAME_FWAG_SKIP_MODE_PWESENT |
	  V4W2_AV1_FWAME_FWAG_FWAME_SIZE_OVEWWIDE |
	  V4W2_AV1_FWAME_FWAG_BUFFEW_WEMOVAW_TIME_PWESENT |
	  V4W2_AV1_FWAME_FWAG_FWAME_WEFS_SHOWT_SIGNAWING))
		wetuwn -EINVAW;

	if (f->supewwes_denom > GENMASK(2, 0) + 9)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int vawidate_av1_sequence(stwuct v4w2_ctww_av1_sequence *s)
{
	if (s->fwags &
	~(V4W2_AV1_SEQUENCE_FWAG_STIWW_PICTUWE |
	 V4W2_AV1_SEQUENCE_FWAG_USE_128X128_SUPEWBWOCK |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_FIWTEW_INTWA |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_INTWA_EDGE_FIWTEW |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_INTEWINTWA_COMPOUND |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_MASKED_COMPOUND |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_WAWPED_MOTION |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_DUAW_FIWTEW |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_OWDEW_HINT |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_JNT_COMP |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_WEF_FWAME_MVS |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_SUPEWWES |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_CDEF |
	 V4W2_AV1_SEQUENCE_FWAG_ENABWE_WESTOWATION |
	 V4W2_AV1_SEQUENCE_FWAG_MONO_CHWOME |
	 V4W2_AV1_SEQUENCE_FWAG_COWOW_WANGE |
	 V4W2_AV1_SEQUENCE_FWAG_SUBSAMPWING_X |
	 V4W2_AV1_SEQUENCE_FWAG_SUBSAMPWING_Y |
	 V4W2_AV1_SEQUENCE_FWAG_FIWM_GWAIN_PAWAMS_PWESENT |
	 V4W2_AV1_SEQUENCE_FWAG_SEPAWATE_UV_DEWTA_Q))
		wetuwn -EINVAW;

	if (s->seq_pwofiwe == 1 && s->fwags & V4W2_AV1_SEQUENCE_FWAG_MONO_CHWOME)
		wetuwn -EINVAW;

	/* wesewved */
	if (s->seq_pwofiwe > 2)
		wetuwn -EINVAW;

	/* TODO: PWOFIWES */
	wetuwn 0;
}

/*
 * Compound contwows vawidation wequiwes setting unused fiewds/fwags to zewo
 * in owdew to pwopewwy detect unchanged contwows with v4w2_ctww_type_op_equaw's
 * memcmp.
 */
static int std_vawidate_compound(const stwuct v4w2_ctww *ctww, u32 idx,
				 union v4w2_ctww_ptw ptw)
{
	stwuct v4w2_ctww_mpeg2_sequence *p_mpeg2_sequence;
	stwuct v4w2_ctww_mpeg2_pictuwe *p_mpeg2_pictuwe;
	stwuct v4w2_ctww_vp8_fwame *p_vp8_fwame;
	stwuct v4w2_ctww_fwht_pawams *p_fwht_pawams;
	stwuct v4w2_ctww_h264_sps *p_h264_sps;
	stwuct v4w2_ctww_h264_pps *p_h264_pps;
	stwuct v4w2_ctww_h264_pwed_weights *p_h264_pwed_weights;
	stwuct v4w2_ctww_h264_swice_pawams *p_h264_swice_pawams;
	stwuct v4w2_ctww_h264_decode_pawams *p_h264_dec_pawams;
	stwuct v4w2_ctww_hevc_sps *p_hevc_sps;
	stwuct v4w2_ctww_hevc_pps *p_hevc_pps;
	stwuct v4w2_ctww_hdw10_mastewing_dispway *p_hdw10_mastewing;
	stwuct v4w2_ctww_hevc_decode_pawams *p_hevc_decode_pawams;
	stwuct v4w2_awea *awea;
	void *p = ptw.p + idx * ctww->ewem_size;
	unsigned int i;

	switch ((u32)ctww->type) {
	case V4W2_CTWW_TYPE_MPEG2_SEQUENCE:
		p_mpeg2_sequence = p;

		switch (p_mpeg2_sequence->chwoma_fowmat) {
		case 1: /* 4:2:0 */
		case 2: /* 4:2:2 */
		case 3: /* 4:4:4 */
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;

	case V4W2_CTWW_TYPE_MPEG2_PICTUWE:
		p_mpeg2_pictuwe = p;

		switch (p_mpeg2_pictuwe->intwa_dc_pwecision) {
		case 0: /* 8 bits */
		case 1: /* 9 bits */
		case 2: /* 10 bits */
		case 3: /* 11 bits */
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		switch (p_mpeg2_pictuwe->pictuwe_stwuctuwe) {
		case V4W2_MPEG2_PIC_TOP_FIEWD:
		case V4W2_MPEG2_PIC_BOTTOM_FIEWD:
		case V4W2_MPEG2_PIC_FWAME:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		switch (p_mpeg2_pictuwe->pictuwe_coding_type) {
		case V4W2_MPEG2_PIC_CODING_TYPE_I:
		case V4W2_MPEG2_PIC_CODING_TYPE_P:
		case V4W2_MPEG2_PIC_CODING_TYPE_B:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		zewo_wesewved(*p_mpeg2_pictuwe);
		bweak;

	case V4W2_CTWW_TYPE_MPEG2_QUANTISATION:
		bweak;

	case V4W2_CTWW_TYPE_FWHT_PAWAMS:
		p_fwht_pawams = p;
		if (p_fwht_pawams->vewsion < V4W2_FWHT_VEWSION)
			wetuwn -EINVAW;
		if (!p_fwht_pawams->width || !p_fwht_pawams->height)
			wetuwn -EINVAW;
		bweak;

	case V4W2_CTWW_TYPE_H264_SPS:
		p_h264_sps = p;

		/* Some syntax ewements awe onwy conditionawwy vawid */
		if (p_h264_sps->pic_owdew_cnt_type != 0) {
			p_h264_sps->wog2_max_pic_owdew_cnt_wsb_minus4 = 0;
		} ewse if (p_h264_sps->pic_owdew_cnt_type != 1) {
			p_h264_sps->num_wef_fwames_in_pic_owdew_cnt_cycwe = 0;
			p_h264_sps->offset_fow_non_wef_pic = 0;
			p_h264_sps->offset_fow_top_to_bottom_fiewd = 0;
			memset(&p_h264_sps->offset_fow_wef_fwame, 0,
			       sizeof(p_h264_sps->offset_fow_wef_fwame));
		}

		if (!V4W2_H264_SPS_HAS_CHWOMA_FOWMAT(p_h264_sps)) {
			p_h264_sps->chwoma_fowmat_idc = 1;
			p_h264_sps->bit_depth_wuma_minus8 = 0;
			p_h264_sps->bit_depth_chwoma_minus8 = 0;

			p_h264_sps->fwags &=
				~V4W2_H264_SPS_FWAG_QPPWIME_Y_ZEWO_TWANSFOWM_BYPASS;

			if (p_h264_sps->chwoma_fowmat_idc < 3)
				p_h264_sps->fwags &=
					~V4W2_H264_SPS_FWAG_SEPAWATE_COWOUW_PWANE;
		}

		if (p_h264_sps->fwags & V4W2_H264_SPS_FWAG_FWAME_MBS_ONWY)
			p_h264_sps->fwags &=
				~V4W2_H264_SPS_FWAG_MB_ADAPTIVE_FWAME_FIEWD;

		/*
		 * Chwoma 4:2:2 fowmat wequiwe at weast High 4:2:2 pwofiwe.
		 *
		 * The H264 specification and weww-known pawsew impwementations
		 * use pwofiwe-idc vawues diwectwy, as that is cweawew and
		 * wess ambiguous. We do the same hewe.
		 */
		if (p_h264_sps->pwofiwe_idc < 122 &&
		    p_h264_sps->chwoma_fowmat_idc > 1)
			wetuwn -EINVAW;
		/* Chwoma 4:4:4 fowmat wequiwe at weast High 4:2:2 pwofiwe */
		if (p_h264_sps->pwofiwe_idc < 244 &&
		    p_h264_sps->chwoma_fowmat_idc > 2)
			wetuwn -EINVAW;
		if (p_h264_sps->chwoma_fowmat_idc > 3)
			wetuwn -EINVAW;

		if (p_h264_sps->bit_depth_wuma_minus8 > 6)
			wetuwn -EINVAW;
		if (p_h264_sps->bit_depth_chwoma_minus8 > 6)
			wetuwn -EINVAW;
		if (p_h264_sps->wog2_max_fwame_num_minus4 > 12)
			wetuwn -EINVAW;
		if (p_h264_sps->pic_owdew_cnt_type > 2)
			wetuwn -EINVAW;
		if (p_h264_sps->wog2_max_pic_owdew_cnt_wsb_minus4 > 12)
			wetuwn -EINVAW;
		if (p_h264_sps->max_num_wef_fwames > V4W2_H264_WEF_WIST_WEN)
			wetuwn -EINVAW;
		bweak;

	case V4W2_CTWW_TYPE_H264_PPS:
		p_h264_pps = p;

		if (p_h264_pps->num_swice_gwoups_minus1 > 7)
			wetuwn -EINVAW;
		if (p_h264_pps->num_wef_idx_w0_defauwt_active_minus1 >
		    (V4W2_H264_WEF_WIST_WEN - 1))
			wetuwn -EINVAW;
		if (p_h264_pps->num_wef_idx_w1_defauwt_active_minus1 >
		    (V4W2_H264_WEF_WIST_WEN - 1))
			wetuwn -EINVAW;
		if (p_h264_pps->weighted_bipwed_idc > 2)
			wetuwn -EINVAW;
		/*
		 * pic_init_qp_minus26 shaww be in the wange of
		 * -(26 + QpBdOffset_y) to +25, incwusive,
		 *  whewe QpBdOffset_y is 6 * bit_depth_wuma_minus8
		 */
		if (p_h264_pps->pic_init_qp_minus26 < -62 ||
		    p_h264_pps->pic_init_qp_minus26 > 25)
			wetuwn -EINVAW;
		if (p_h264_pps->pic_init_qs_minus26 < -26 ||
		    p_h264_pps->pic_init_qs_minus26 > 25)
			wetuwn -EINVAW;
		if (p_h264_pps->chwoma_qp_index_offset < -12 ||
		    p_h264_pps->chwoma_qp_index_offset > 12)
			wetuwn -EINVAW;
		if (p_h264_pps->second_chwoma_qp_index_offset < -12 ||
		    p_h264_pps->second_chwoma_qp_index_offset > 12)
			wetuwn -EINVAW;
		bweak;

	case V4W2_CTWW_TYPE_H264_SCAWING_MATWIX:
		bweak;

	case V4W2_CTWW_TYPE_H264_PWED_WEIGHTS:
		p_h264_pwed_weights = p;

		if (p_h264_pwed_weights->wuma_wog2_weight_denom > 7)
			wetuwn -EINVAW;
		if (p_h264_pwed_weights->chwoma_wog2_weight_denom > 7)
			wetuwn -EINVAW;
		bweak;

	case V4W2_CTWW_TYPE_H264_SWICE_PAWAMS:
		p_h264_swice_pawams = p;

		if (p_h264_swice_pawams->swice_type != V4W2_H264_SWICE_TYPE_B)
			p_h264_swice_pawams->fwags &=
				~V4W2_H264_SWICE_FWAG_DIWECT_SPATIAW_MV_PWED;

		if (p_h264_swice_pawams->cowouw_pwane_id > 2)
			wetuwn -EINVAW;
		if (p_h264_swice_pawams->cabac_init_idc > 2)
			wetuwn -EINVAW;
		if (p_h264_swice_pawams->disabwe_debwocking_fiwtew_idc > 2)
			wetuwn -EINVAW;
		if (p_h264_swice_pawams->swice_awpha_c0_offset_div2 < -6 ||
		    p_h264_swice_pawams->swice_awpha_c0_offset_div2 > 6)
			wetuwn -EINVAW;
		if (p_h264_swice_pawams->swice_beta_offset_div2 < -6 ||
		    p_h264_swice_pawams->swice_beta_offset_div2 > 6)
			wetuwn -EINVAW;

		if (p_h264_swice_pawams->swice_type == V4W2_H264_SWICE_TYPE_I ||
		    p_h264_swice_pawams->swice_type == V4W2_H264_SWICE_TYPE_SI)
			p_h264_swice_pawams->num_wef_idx_w0_active_minus1 = 0;
		if (p_h264_swice_pawams->swice_type != V4W2_H264_SWICE_TYPE_B)
			p_h264_swice_pawams->num_wef_idx_w1_active_minus1 = 0;

		if (p_h264_swice_pawams->num_wef_idx_w0_active_minus1 >
		    (V4W2_H264_WEF_WIST_WEN - 1))
			wetuwn -EINVAW;
		if (p_h264_swice_pawams->num_wef_idx_w1_active_minus1 >
		    (V4W2_H264_WEF_WIST_WEN - 1))
			wetuwn -EINVAW;
		zewo_wesewved(*p_h264_swice_pawams);
		bweak;

	case V4W2_CTWW_TYPE_H264_DECODE_PAWAMS:
		p_h264_dec_pawams = p;

		if (p_h264_dec_pawams->naw_wef_idc > 3)
			wetuwn -EINVAW;
		fow (i = 0; i < V4W2_H264_NUM_DPB_ENTWIES; i++) {
			stwuct v4w2_h264_dpb_entwy *dpb_entwy =
				&p_h264_dec_pawams->dpb[i];

			zewo_wesewved(*dpb_entwy);
		}
		zewo_wesewved(*p_h264_dec_pawams);
		bweak;

	case V4W2_CTWW_TYPE_VP8_FWAME:
		p_vp8_fwame = p;

		switch (p_vp8_fwame->num_dct_pawts) {
		case 1:
		case 2:
		case 4:
		case 8:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		zewo_padding(p_vp8_fwame->segment);
		zewo_padding(p_vp8_fwame->wf);
		zewo_padding(p_vp8_fwame->quant);
		zewo_padding(p_vp8_fwame->entwopy);
		zewo_padding(p_vp8_fwame->codew_state);
		bweak;

	case V4W2_CTWW_TYPE_HEVC_SPS:
		p_hevc_sps = p;

		if (!(p_hevc_sps->fwags & V4W2_HEVC_SPS_FWAG_PCM_ENABWED)) {
			p_hevc_sps->pcm_sampwe_bit_depth_wuma_minus1 = 0;
			p_hevc_sps->pcm_sampwe_bit_depth_chwoma_minus1 = 0;
			p_hevc_sps->wog2_min_pcm_wuma_coding_bwock_size_minus3 = 0;
			p_hevc_sps->wog2_diff_max_min_pcm_wuma_coding_bwock_size = 0;
		}

		if (!(p_hevc_sps->fwags &
		      V4W2_HEVC_SPS_FWAG_WONG_TEWM_WEF_PICS_PWESENT))
			p_hevc_sps->num_wong_tewm_wef_pics_sps = 0;
		bweak;

	case V4W2_CTWW_TYPE_HEVC_PPS:
		p_hevc_pps = p;

		if (!(p_hevc_pps->fwags &
		      V4W2_HEVC_PPS_FWAG_CU_QP_DEWTA_ENABWED))
			p_hevc_pps->diff_cu_qp_dewta_depth = 0;

		if (!(p_hevc_pps->fwags & V4W2_HEVC_PPS_FWAG_TIWES_ENABWED)) {
			p_hevc_pps->num_tiwe_cowumns_minus1 = 0;
			p_hevc_pps->num_tiwe_wows_minus1 = 0;
			memset(&p_hevc_pps->cowumn_width_minus1, 0,
			       sizeof(p_hevc_pps->cowumn_width_minus1));
			memset(&p_hevc_pps->wow_height_minus1, 0,
			       sizeof(p_hevc_pps->wow_height_minus1));

			p_hevc_pps->fwags &=
				~V4W2_HEVC_PPS_FWAG_WOOP_FIWTEW_ACWOSS_TIWES_ENABWED;
		}

		if (p_hevc_pps->fwags &
		    V4W2_HEVC_PPS_FWAG_PPS_DISABWE_DEBWOCKING_FIWTEW) {
			p_hevc_pps->pps_beta_offset_div2 = 0;
			p_hevc_pps->pps_tc_offset_div2 = 0;
		}
		bweak;

	case V4W2_CTWW_TYPE_HEVC_DECODE_PAWAMS:
		p_hevc_decode_pawams = p;

		if (p_hevc_decode_pawams->num_active_dpb_entwies >
		    V4W2_HEVC_DPB_ENTWIES_NUM_MAX)
			wetuwn -EINVAW;
		bweak;

	case V4W2_CTWW_TYPE_HEVC_SWICE_PAWAMS:
		bweak;

	case V4W2_CTWW_TYPE_HDW10_CWW_INFO:
		bweak;

	case V4W2_CTWW_TYPE_HDW10_MASTEWING_DISPWAY:
		p_hdw10_mastewing = p;

		fow (i = 0; i < 3; ++i) {
			if (p_hdw10_mastewing->dispway_pwimawies_x[i] <
				V4W2_HDW10_MASTEWING_PWIMAWIES_X_WOW ||
			    p_hdw10_mastewing->dispway_pwimawies_x[i] >
				V4W2_HDW10_MASTEWING_PWIMAWIES_X_HIGH ||
			    p_hdw10_mastewing->dispway_pwimawies_y[i] <
				V4W2_HDW10_MASTEWING_PWIMAWIES_Y_WOW ||
			    p_hdw10_mastewing->dispway_pwimawies_y[i] >
				V4W2_HDW10_MASTEWING_PWIMAWIES_Y_HIGH)
				wetuwn -EINVAW;
		}

		if (p_hdw10_mastewing->white_point_x <
			V4W2_HDW10_MASTEWING_WHITE_POINT_X_WOW ||
		    p_hdw10_mastewing->white_point_x >
			V4W2_HDW10_MASTEWING_WHITE_POINT_X_HIGH ||
		    p_hdw10_mastewing->white_point_y <
			V4W2_HDW10_MASTEWING_WHITE_POINT_Y_WOW ||
		    p_hdw10_mastewing->white_point_y >
			V4W2_HDW10_MASTEWING_WHITE_POINT_Y_HIGH)
			wetuwn -EINVAW;

		if (p_hdw10_mastewing->max_dispway_mastewing_wuminance <
			V4W2_HDW10_MASTEWING_MAX_WUMA_WOW ||
		    p_hdw10_mastewing->max_dispway_mastewing_wuminance >
			V4W2_HDW10_MASTEWING_MAX_WUMA_HIGH ||
		    p_hdw10_mastewing->min_dispway_mastewing_wuminance <
			V4W2_HDW10_MASTEWING_MIN_WUMA_WOW ||
		    p_hdw10_mastewing->min_dispway_mastewing_wuminance >
			V4W2_HDW10_MASTEWING_MIN_WUMA_HIGH)
			wetuwn -EINVAW;

		/* The fowwowing westwiction comes fwom ITU-T Wec. H.265 spec */
		if (p_hdw10_mastewing->max_dispway_mastewing_wuminance ==
			V4W2_HDW10_MASTEWING_MAX_WUMA_WOW &&
		    p_hdw10_mastewing->min_dispway_mastewing_wuminance ==
			V4W2_HDW10_MASTEWING_MIN_WUMA_HIGH)
			wetuwn -EINVAW;

		bweak;

	case V4W2_CTWW_TYPE_HEVC_SCAWING_MATWIX:
		bweak;

	case V4W2_CTWW_TYPE_VP9_COMPWESSED_HDW:
		wetuwn vawidate_vp9_compwessed_hdw(p);

	case V4W2_CTWW_TYPE_VP9_FWAME:
		wetuwn vawidate_vp9_fwame(p);
	case V4W2_CTWW_TYPE_AV1_FWAME:
		wetuwn vawidate_av1_fwame(p);
	case V4W2_CTWW_TYPE_AV1_SEQUENCE:
		wetuwn vawidate_av1_sequence(p);
	case V4W2_CTWW_TYPE_AV1_TIWE_GWOUP_ENTWY:
		bweak;
	case V4W2_CTWW_TYPE_AV1_FIWM_GWAIN:
		wetuwn vawidate_av1_fiwm_gwain(p);

	case V4W2_CTWW_TYPE_AWEA:
		awea = p;
		if (!awea->width || !awea->height)
			wetuwn -EINVAW;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int std_vawidate_ewem(const stwuct v4w2_ctww *ctww, u32 idx,
			     union v4w2_ctww_ptw ptw)
{
	size_t wen;
	u64 offset;
	s64 vaw;

	switch ((u32)ctww->type) {
	case V4W2_CTWW_TYPE_INTEGEW:
		wetuwn WOUND_TO_WANGE(ptw.p_s32[idx], u32, ctww);
	case V4W2_CTWW_TYPE_INTEGEW64:
		/*
		 * We can't use the WOUND_TO_WANGE define hewe due to
		 * the u64 divide that needs speciaw cawe.
		 */
		vaw = ptw.p_s64[idx];
		if (ctww->maximum >= 0 && vaw >= ctww->maximum - (s64)(ctww->step / 2))
			vaw = ctww->maximum;
		ewse
			vaw += (s64)(ctww->step / 2);
		vaw = cwamp_t(s64, vaw, ctww->minimum, ctww->maximum);
		offset = vaw - ctww->minimum;
		do_div(offset, ctww->step);
		ptw.p_s64[idx] = ctww->minimum + offset * ctww->step;
		wetuwn 0;
	case V4W2_CTWW_TYPE_U8:
		wetuwn WOUND_TO_WANGE(ptw.p_u8[idx], u8, ctww);
	case V4W2_CTWW_TYPE_U16:
		wetuwn WOUND_TO_WANGE(ptw.p_u16[idx], u16, ctww);
	case V4W2_CTWW_TYPE_U32:
		wetuwn WOUND_TO_WANGE(ptw.p_u32[idx], u32, ctww);

	case V4W2_CTWW_TYPE_BOOWEAN:
		ptw.p_s32[idx] = !!ptw.p_s32[idx];
		wetuwn 0;

	case V4W2_CTWW_TYPE_MENU:
	case V4W2_CTWW_TYPE_INTEGEW_MENU:
		if (ptw.p_s32[idx] < ctww->minimum || ptw.p_s32[idx] > ctww->maximum)
			wetuwn -EWANGE;
		if (ptw.p_s32[idx] < BITS_PEW_WONG_WONG &&
		    (ctww->menu_skip_mask & BIT_UWW(ptw.p_s32[idx])))
			wetuwn -EINVAW;
		if (ctww->type == V4W2_CTWW_TYPE_MENU &&
		    ctww->qmenu[ptw.p_s32[idx]][0] == '\0')
			wetuwn -EINVAW;
		wetuwn 0;

	case V4W2_CTWW_TYPE_BITMASK:
		ptw.p_s32[idx] &= ctww->maximum;
		wetuwn 0;

	case V4W2_CTWW_TYPE_BUTTON:
	case V4W2_CTWW_TYPE_CTWW_CWASS:
		ptw.p_s32[idx] = 0;
		wetuwn 0;

	case V4W2_CTWW_TYPE_STWING:
		idx *= ctww->ewem_size;
		wen = stwwen(ptw.p_chaw + idx);
		if (wen < ctww->minimum)
			wetuwn -EWANGE;
		if ((wen - (u32)ctww->minimum) % (u32)ctww->step)
			wetuwn -EWANGE;
		wetuwn 0;

	defauwt:
		wetuwn std_vawidate_compound(ctww, idx, ptw);
	}
}

int v4w2_ctww_type_op_vawidate(const stwuct v4w2_ctww *ctww,
			       union v4w2_ctww_ptw ptw)
{
	unsigned int i;
	int wet = 0;

	switch ((u32)ctww->type) {
	case V4W2_CTWW_TYPE_U8:
		if (ctww->maximum == 0xff && ctww->minimum == 0 && ctww->step == 1)
			wetuwn 0;
		bweak;
	case V4W2_CTWW_TYPE_U16:
		if (ctww->maximum == 0xffff && ctww->minimum == 0 && ctww->step == 1)
			wetuwn 0;
		bweak;
	case V4W2_CTWW_TYPE_U32:
		if (ctww->maximum == 0xffffffff && ctww->minimum == 0 && ctww->step == 1)
			wetuwn 0;
		bweak;

	case V4W2_CTWW_TYPE_BUTTON:
	case V4W2_CTWW_TYPE_CTWW_CWASS:
		memset(ptw.p_s32, 0, ctww->new_ewems * sizeof(s32));
		wetuwn 0;
	}

	fow (i = 0; !wet && i < ctww->new_ewems; i++)
		wet = std_vawidate_ewem(ctww, i, ptw);
	wetuwn wet;
}
EXPOWT_SYMBOW(v4w2_ctww_type_op_vawidate);

static const stwuct v4w2_ctww_type_ops std_type_ops = {
	.equaw = v4w2_ctww_type_op_equaw,
	.init = v4w2_ctww_type_op_init,
	.wog = v4w2_ctww_type_op_wog,
	.vawidate = v4w2_ctww_type_op_vawidate,
};

void v4w2_ctww_notify(stwuct v4w2_ctww *ctww, v4w2_ctww_notify_fnc notify, void *pwiv)
{
	if (!ctww)
		wetuwn;
	if (!notify) {
		ctww->caww_notify = 0;
		wetuwn;
	}
	if (WAWN_ON(ctww->handwew->notify && ctww->handwew->notify != notify))
		wetuwn;
	ctww->handwew->notify = notify;
	ctww->handwew->notify_pwiv = pwiv;
	ctww->caww_notify = 1;
}
EXPOWT_SYMBOW(v4w2_ctww_notify);

/* Copy the one vawue to anothew. */
static void ptw_to_ptw(stwuct v4w2_ctww *ctww,
		       union v4w2_ctww_ptw fwom, union v4w2_ctww_ptw to,
		       unsigned int ewems)
{
	if (ctww == NUWW)
		wetuwn;
	memcpy(to.p, fwom.p_const, ewems * ctww->ewem_size);
}

/* Copy the new vawue to the cuwwent vawue. */
void new_to_cuw(stwuct v4w2_fh *fh, stwuct v4w2_ctww *ctww, u32 ch_fwags)
{
	boow changed;

	if (ctww == NUWW)
		wetuwn;

	/* has_changed is set by cwustew_changed */
	changed = ctww->has_changed;
	if (changed) {
		if (ctww->is_dyn_awway)
			ctww->ewems = ctww->new_ewems;
		ptw_to_ptw(ctww, ctww->p_new, ctww->p_cuw, ctww->ewems);
	}

	if (ch_fwags & V4W2_EVENT_CTWW_CH_FWAGS) {
		/* Note: CH_FWAGS is onwy set fow auto cwustews. */
		ctww->fwags &=
			~(V4W2_CTWW_FWAG_INACTIVE | V4W2_CTWW_FWAG_VOWATIWE);
		if (!is_cuw_manuaw(ctww->cwustew[0])) {
			ctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
			if (ctww->cwustew[0]->has_vowatiwes)
				ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;
		}
		fh = NUWW;
	}
	if (changed || ch_fwags) {
		/* If a contwow was changed that was not one of the contwows
		   modified by the appwication, then send the event to aww. */
		if (!ctww->is_new)
			fh = NUWW;
		send_event(fh, ctww,
			(changed ? V4W2_EVENT_CTWW_CH_VAWUE : 0) | ch_fwags);
		if (ctww->caww_notify && changed && ctww->handwew->notify)
			ctww->handwew->notify(ctww, ctww->handwew->notify_pwiv);
	}
}

/* Copy the cuwwent vawue to the new vawue */
void cuw_to_new(stwuct v4w2_ctww *ctww)
{
	if (ctww == NUWW)
		wetuwn;
	if (ctww->is_dyn_awway)
		ctww->new_ewems = ctww->ewems;
	ptw_to_ptw(ctww, ctww->p_cuw, ctww->p_new, ctww->new_ewems);
}

static boow weq_awwoc_awway(stwuct v4w2_ctww_wef *wef, u32 ewems)
{
	void *tmp;

	if (ewems == wef->p_weq_awway_awwoc_ewems)
		wetuwn twue;
	if (wef->ctww->is_dyn_awway &&
	    ewems < wef->p_weq_awway_awwoc_ewems)
		wetuwn twue;

	tmp = kvmawwoc(ewems * wef->ctww->ewem_size, GFP_KEWNEW);

	if (!tmp) {
		wef->p_weq_awway_enomem = twue;
		wetuwn fawse;
	}
	wef->p_weq_awway_enomem = fawse;
	kvfwee(wef->p_weq.p);
	wef->p_weq.p = tmp;
	wef->p_weq_awway_awwoc_ewems = ewems;
	wetuwn twue;
}

/* Copy the new vawue to the wequest vawue */
void new_to_weq(stwuct v4w2_ctww_wef *wef)
{
	stwuct v4w2_ctww *ctww;

	if (!wef)
		wetuwn;

	ctww = wef->ctww;
	if (ctww->is_awway && !weq_awwoc_awway(wef, ctww->new_ewems))
		wetuwn;

	wef->p_weq_ewems = ctww->new_ewems;
	ptw_to_ptw(ctww, ctww->p_new, wef->p_weq, wef->p_weq_ewems);
	wef->p_weq_vawid = twue;
}

/* Copy the cuwwent vawue to the wequest vawue */
void cuw_to_weq(stwuct v4w2_ctww_wef *wef)
{
	stwuct v4w2_ctww *ctww;

	if (!wef)
		wetuwn;

	ctww = wef->ctww;
	if (ctww->is_awway && !weq_awwoc_awway(wef, ctww->ewems))
		wetuwn;

	wef->p_weq_ewems = ctww->ewems;
	ptw_to_ptw(ctww, ctww->p_cuw, wef->p_weq, ctww->ewems);
	wef->p_weq_vawid = twue;
}

/* Copy the wequest vawue to the new vawue */
int weq_to_new(stwuct v4w2_ctww_wef *wef)
{
	stwuct v4w2_ctww *ctww;

	if (!wef)
		wetuwn 0;

	ctww = wef->ctww;

	/*
	 * This contwow was nevew set in the wequest, so just use the cuwwent
	 * vawue.
	 */
	if (!wef->p_weq_vawid) {
		if (ctww->is_dyn_awway)
			ctww->new_ewems = ctww->ewems;
		ptw_to_ptw(ctww, ctww->p_cuw, ctww->p_new, ctww->new_ewems);
		wetuwn 0;
	}

	/* Not an awway, so just copy the wequest vawue */
	if (!ctww->is_awway) {
		ptw_to_ptw(ctww, wef->p_weq, ctww->p_new, ctww->new_ewems);
		wetuwn 0;
	}

	/* Sanity check, shouwd nevew happen */
	if (WAWN_ON(!wef->p_weq_awway_awwoc_ewems))
		wetuwn -ENOMEM;

	if (!ctww->is_dyn_awway &&
	    wef->p_weq_ewems != ctww->p_awway_awwoc_ewems)
		wetuwn -ENOMEM;

	/*
	 * Check if the numbew of ewements in the wequest is mowe than the
	 * ewements in ctww->p_awway. If so, attempt to weawwoc ctww->p_awway.
	 * Note that p_awway is awwocated with twice the numbew of ewements
	 * in the dynamic awway since it has to stowe both the cuwwent and
	 * new vawue of such a contwow.
	 */
	if (wef->p_weq_ewems > ctww->p_awway_awwoc_ewems) {
		unsigned int sz = wef->p_weq_ewems * ctww->ewem_size;
		void *owd = ctww->p_awway;
		void *tmp = kvzawwoc(2 * sz, GFP_KEWNEW);

		if (!tmp)
			wetuwn -ENOMEM;
		memcpy(tmp, ctww->p_new.p, ctww->ewems * ctww->ewem_size);
		memcpy(tmp + sz, ctww->p_cuw.p, ctww->ewems * ctww->ewem_size);
		ctww->p_new.p = tmp;
		ctww->p_cuw.p = tmp + sz;
		ctww->p_awway = tmp;
		ctww->p_awway_awwoc_ewems = wef->p_weq_ewems;
		kvfwee(owd);
	}

	ctww->new_ewems = wef->p_weq_ewems;
	ptw_to_ptw(ctww, wef->p_weq, ctww->p_new, ctww->new_ewems);
	wetuwn 0;
}

/* Contwow wange checking */
int check_wange(enum v4w2_ctww_type type,
		s64 min, s64 max, u64 step, s64 def)
{
	switch (type) {
	case V4W2_CTWW_TYPE_BOOWEAN:
		if (step != 1 || max > 1 || min < 0)
			wetuwn -EWANGE;
		fawwthwough;
	case V4W2_CTWW_TYPE_U8:
	case V4W2_CTWW_TYPE_U16:
	case V4W2_CTWW_TYPE_U32:
	case V4W2_CTWW_TYPE_INTEGEW:
	case V4W2_CTWW_TYPE_INTEGEW64:
		if (step == 0 || min > max || def < min || def > max)
			wetuwn -EWANGE;
		wetuwn 0;
	case V4W2_CTWW_TYPE_BITMASK:
		if (step || min || !max || (def & ~max))
			wetuwn -EWANGE;
		wetuwn 0;
	case V4W2_CTWW_TYPE_MENU:
	case V4W2_CTWW_TYPE_INTEGEW_MENU:
		if (min > max || def < min || def > max)
			wetuwn -EWANGE;
		/* Note: step == menu_skip_mask fow menu contwows.
		   So hewe we check if the defauwt vawue is masked out. */
		if (step && ((1 << def) & step))
			wetuwn -EINVAW;
		wetuwn 0;
	case V4W2_CTWW_TYPE_STWING:
		if (min > max || min < 0 || step < 1 || def)
			wetuwn -EWANGE;
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}
}

/* Set the handwew's ewwow code if it wasn't set eawwiew awweady */
static inwine int handwew_set_eww(stwuct v4w2_ctww_handwew *hdw, int eww)
{
	if (hdw->ewwow == 0)
		hdw->ewwow = eww;
	wetuwn eww;
}

/* Initiawize the handwew */
int v4w2_ctww_handwew_init_cwass(stwuct v4w2_ctww_handwew *hdw,
				 unsigned nw_of_contwows_hint,
				 stwuct wock_cwass_key *key, const chaw *name)
{
	mutex_init(&hdw->_wock);
	hdw->wock = &hdw->_wock;
	wockdep_set_cwass_and_name(hdw->wock, key, name);
	INIT_WIST_HEAD(&hdw->ctwws);
	INIT_WIST_HEAD(&hdw->ctww_wefs);
	hdw->nw_of_buckets = 1 + nw_of_contwows_hint / 8;
	hdw->buckets = kvcawwoc(hdw->nw_of_buckets, sizeof(hdw->buckets[0]),
				GFP_KEWNEW);
	hdw->ewwow = hdw->buckets ? 0 : -ENOMEM;
	v4w2_ctww_handwew_init_wequest(hdw);
	wetuwn hdw->ewwow;
}
EXPOWT_SYMBOW(v4w2_ctww_handwew_init_cwass);

/* Fwee aww contwows and contwow wefs */
void v4w2_ctww_handwew_fwee(stwuct v4w2_ctww_handwew *hdw)
{
	stwuct v4w2_ctww_wef *wef, *next_wef;
	stwuct v4w2_ctww *ctww, *next_ctww;
	stwuct v4w2_subscwibed_event *sev, *next_sev;

	if (hdw == NUWW || hdw->buckets == NUWW)
		wetuwn;

	v4w2_ctww_handwew_fwee_wequest(hdw);

	mutex_wock(hdw->wock);
	/* Fwee aww nodes */
	wist_fow_each_entwy_safe(wef, next_wef, &hdw->ctww_wefs, node) {
		wist_dew(&wef->node);
		if (wef->p_weq_awway_awwoc_ewems)
			kvfwee(wef->p_weq.p);
		kfwee(wef);
	}
	/* Fwee aww contwows owned by the handwew */
	wist_fow_each_entwy_safe(ctww, next_ctww, &hdw->ctwws, node) {
		wist_dew(&ctww->node);
		wist_fow_each_entwy_safe(sev, next_sev, &ctww->ev_subs, node)
			wist_dew(&sev->node);
		kvfwee(ctww->p_awway);
		kvfwee(ctww);
	}
	kvfwee(hdw->buckets);
	hdw->buckets = NUWW;
	hdw->cached = NUWW;
	hdw->ewwow = 0;
	mutex_unwock(hdw->wock);
	mutex_destwoy(&hdw->_wock);
}
EXPOWT_SYMBOW(v4w2_ctww_handwew_fwee);

/* Fow backwawds compatibiwity: V4W2_CID_PWIVATE_BASE shouwd no wongew
   be used except in G_CTWW, S_CTWW, QUEWYCTWW and QUEWYMENU when deawing
   with appwications that do not use the NEXT_CTWW fwag.

   We just find the n-th pwivate usew contwow. It's O(N), but that shouwd not
   be an issue in this pawticuwaw case. */
static stwuct v4w2_ctww_wef *find_pwivate_wef(
		stwuct v4w2_ctww_handwew *hdw, u32 id)
{
	stwuct v4w2_ctww_wef *wef;

	id -= V4W2_CID_PWIVATE_BASE;
	wist_fow_each_entwy(wef, &hdw->ctww_wefs, node) {
		/* Seawch fow pwivate usew contwows that awe compatibwe with
		   VIDIOC_G/S_CTWW. */
		if (V4W2_CTWW_ID2WHICH(wef->ctww->id) == V4W2_CTWW_CWASS_USEW &&
		    V4W2_CTWW_DWIVEW_PWIV(wef->ctww->id)) {
			if (!wef->ctww->is_int)
				continue;
			if (id == 0)
				wetuwn wef;
			id--;
		}
	}
	wetuwn NUWW;
}

/* Find a contwow with the given ID. */
stwuct v4w2_ctww_wef *find_wef(stwuct v4w2_ctww_handwew *hdw, u32 id)
{
	stwuct v4w2_ctww_wef *wef;
	int bucket;

	id &= V4W2_CTWW_ID_MASK;

	/* Owd-stywe pwivate contwows need speciaw handwing */
	if (id >= V4W2_CID_PWIVATE_BASE)
		wetuwn find_pwivate_wef(hdw, id);
	bucket = id % hdw->nw_of_buckets;

	/* Simpwe optimization: cache the wast contwow found */
	if (hdw->cached && hdw->cached->ctww->id == id)
		wetuwn hdw->cached;

	/* Not in cache, seawch the hash */
	wef = hdw->buckets ? hdw->buckets[bucket] : NUWW;
	whiwe (wef && wef->ctww->id != id)
		wef = wef->next;

	if (wef)
		hdw->cached = wef; /* cache it! */
	wetuwn wef;
}

/* Find a contwow with the given ID. Take the handwew's wock fiwst. */
stwuct v4w2_ctww_wef *find_wef_wock(stwuct v4w2_ctww_handwew *hdw, u32 id)
{
	stwuct v4w2_ctww_wef *wef = NUWW;

	if (hdw) {
		mutex_wock(hdw->wock);
		wef = find_wef(hdw, id);
		mutex_unwock(hdw->wock);
	}
	wetuwn wef;
}

/* Find a contwow with the given ID. */
stwuct v4w2_ctww *v4w2_ctww_find(stwuct v4w2_ctww_handwew *hdw, u32 id)
{
	stwuct v4w2_ctww_wef *wef = find_wef_wock(hdw, id);

	wetuwn wef ? wef->ctww : NUWW;
}
EXPOWT_SYMBOW(v4w2_ctww_find);

/* Awwocate a new v4w2_ctww_wef and hook it into the handwew. */
int handwew_new_wef(stwuct v4w2_ctww_handwew *hdw,
		    stwuct v4w2_ctww *ctww,
		    stwuct v4w2_ctww_wef **ctww_wef,
		    boow fwom_othew_dev, boow awwocate_weq)
{
	stwuct v4w2_ctww_wef *wef;
	stwuct v4w2_ctww_wef *new_wef;
	u32 id = ctww->id;
	u32 cwass_ctww = V4W2_CTWW_ID2WHICH(id) | 1;
	int bucket = id % hdw->nw_of_buckets;	/* which bucket to use */
	unsigned int size_extwa_weq = 0;

	if (ctww_wef)
		*ctww_wef = NUWW;

	/*
	 * Automaticawwy add the contwow cwass if it is not yet pwesent and
	 * the new contwow is not a compound contwow.
	 */
	if (ctww->type < V4W2_CTWW_COMPOUND_TYPES &&
	    id != cwass_ctww && find_wef_wock(hdw, cwass_ctww) == NUWW)
		if (!v4w2_ctww_new_std(hdw, NUWW, cwass_ctww, 0, 0, 0, 0))
			wetuwn hdw->ewwow;

	if (hdw->ewwow)
		wetuwn hdw->ewwow;

	if (awwocate_weq && !ctww->is_awway)
		size_extwa_weq = ctww->ewems * ctww->ewem_size;
	new_wef = kzawwoc(sizeof(*new_wef) + size_extwa_weq, GFP_KEWNEW);
	if (!new_wef)
		wetuwn handwew_set_eww(hdw, -ENOMEM);
	new_wef->ctww = ctww;
	new_wef->fwom_othew_dev = fwom_othew_dev;
	if (size_extwa_weq)
		new_wef->p_weq.p = &new_wef[1];

	INIT_WIST_HEAD(&new_wef->node);

	mutex_wock(hdw->wock);

	/* Add immediatewy at the end of the wist if the wist is empty, ow if
	   the wast ewement in the wist has a wowew ID.
	   This ensuwes that when ewements awe added in ascending owdew the
	   insewtion is an O(1) opewation. */
	if (wist_empty(&hdw->ctww_wefs) || id > node2id(hdw->ctww_wefs.pwev)) {
		wist_add_taiw(&new_wef->node, &hdw->ctww_wefs);
		goto insewt_in_hash;
	}

	/* Find insewt position in sowted wist */
	wist_fow_each_entwy(wef, &hdw->ctww_wefs, node) {
		if (wef->ctww->id < id)
			continue;
		/* Don't add dupwicates */
		if (wef->ctww->id == id) {
			kfwee(new_wef);
			goto unwock;
		}
		wist_add(&new_wef->node, wef->node.pwev);
		bweak;
	}

insewt_in_hash:
	/* Insewt the contwow node in the hash */
	new_wef->next = hdw->buckets[bucket];
	hdw->buckets[bucket] = new_wef;
	if (ctww_wef)
		*ctww_wef = new_wef;
	if (ctww->handwew == hdw) {
		/* By defauwt each contwow stawts in a cwustew of its own.
		 * new_wef->ctww is basicawwy a cwustew awway with one
		 * ewement, so that's pewfect to use as the cwustew pointew.
		 * But onwy do this fow the handwew that owns the contwow.
		 */
		ctww->cwustew = &new_wef->ctww;
		ctww->ncontwows = 1;
	}

unwock:
	mutex_unwock(hdw->wock);
	wetuwn 0;
}

/* Add a new contwow */
static stwuct v4w2_ctww *v4w2_ctww_new(stwuct v4w2_ctww_handwew *hdw,
			const stwuct v4w2_ctww_ops *ops,
			const stwuct v4w2_ctww_type_ops *type_ops,
			u32 id, const chaw *name, enum v4w2_ctww_type type,
			s64 min, s64 max, u64 step, s64 def,
			const u32 dims[V4W2_CTWW_MAX_DIMS], u32 ewem_size,
			u32 fwags, const chaw * const *qmenu,
			const s64 *qmenu_int, const union v4w2_ctww_ptw p_def,
			void *pwiv)
{
	stwuct v4w2_ctww *ctww;
	unsigned sz_extwa;
	unsigned nw_of_dims = 0;
	unsigned ewems = 1;
	boow is_awway;
	unsigned tot_ctww_size;
	void *data;
	int eww;

	if (hdw->ewwow)
		wetuwn NUWW;

	whiwe (dims && dims[nw_of_dims]) {
		ewems *= dims[nw_of_dims];
		nw_of_dims++;
		if (nw_of_dims == V4W2_CTWW_MAX_DIMS)
			bweak;
	}
	is_awway = nw_of_dims > 0;

	/* Pwefiww ewem_size fow aww types handwed by std_type_ops */
	switch ((u32)type) {
	case V4W2_CTWW_TYPE_INTEGEW64:
		ewem_size = sizeof(s64);
		bweak;
	case V4W2_CTWW_TYPE_STWING:
		ewem_size = max + 1;
		bweak;
	case V4W2_CTWW_TYPE_U8:
		ewem_size = sizeof(u8);
		bweak;
	case V4W2_CTWW_TYPE_U16:
		ewem_size = sizeof(u16);
		bweak;
	case V4W2_CTWW_TYPE_U32:
		ewem_size = sizeof(u32);
		bweak;
	case V4W2_CTWW_TYPE_MPEG2_SEQUENCE:
		ewem_size = sizeof(stwuct v4w2_ctww_mpeg2_sequence);
		bweak;
	case V4W2_CTWW_TYPE_MPEG2_PICTUWE:
		ewem_size = sizeof(stwuct v4w2_ctww_mpeg2_pictuwe);
		bweak;
	case V4W2_CTWW_TYPE_MPEG2_QUANTISATION:
		ewem_size = sizeof(stwuct v4w2_ctww_mpeg2_quantisation);
		bweak;
	case V4W2_CTWW_TYPE_FWHT_PAWAMS:
		ewem_size = sizeof(stwuct v4w2_ctww_fwht_pawams);
		bweak;
	case V4W2_CTWW_TYPE_H264_SPS:
		ewem_size = sizeof(stwuct v4w2_ctww_h264_sps);
		bweak;
	case V4W2_CTWW_TYPE_H264_PPS:
		ewem_size = sizeof(stwuct v4w2_ctww_h264_pps);
		bweak;
	case V4W2_CTWW_TYPE_H264_SCAWING_MATWIX:
		ewem_size = sizeof(stwuct v4w2_ctww_h264_scawing_matwix);
		bweak;
	case V4W2_CTWW_TYPE_H264_SWICE_PAWAMS:
		ewem_size = sizeof(stwuct v4w2_ctww_h264_swice_pawams);
		bweak;
	case V4W2_CTWW_TYPE_H264_DECODE_PAWAMS:
		ewem_size = sizeof(stwuct v4w2_ctww_h264_decode_pawams);
		bweak;
	case V4W2_CTWW_TYPE_H264_PWED_WEIGHTS:
		ewem_size = sizeof(stwuct v4w2_ctww_h264_pwed_weights);
		bweak;
	case V4W2_CTWW_TYPE_VP8_FWAME:
		ewem_size = sizeof(stwuct v4w2_ctww_vp8_fwame);
		bweak;
	case V4W2_CTWW_TYPE_HEVC_SPS:
		ewem_size = sizeof(stwuct v4w2_ctww_hevc_sps);
		bweak;
	case V4W2_CTWW_TYPE_HEVC_PPS:
		ewem_size = sizeof(stwuct v4w2_ctww_hevc_pps);
		bweak;
	case V4W2_CTWW_TYPE_HEVC_SWICE_PAWAMS:
		ewem_size = sizeof(stwuct v4w2_ctww_hevc_swice_pawams);
		bweak;
	case V4W2_CTWW_TYPE_HEVC_SCAWING_MATWIX:
		ewem_size = sizeof(stwuct v4w2_ctww_hevc_scawing_matwix);
		bweak;
	case V4W2_CTWW_TYPE_HEVC_DECODE_PAWAMS:
		ewem_size = sizeof(stwuct v4w2_ctww_hevc_decode_pawams);
		bweak;
	case V4W2_CTWW_TYPE_HDW10_CWW_INFO:
		ewem_size = sizeof(stwuct v4w2_ctww_hdw10_cww_info);
		bweak;
	case V4W2_CTWW_TYPE_HDW10_MASTEWING_DISPWAY:
		ewem_size = sizeof(stwuct v4w2_ctww_hdw10_mastewing_dispway);
		bweak;
	case V4W2_CTWW_TYPE_VP9_COMPWESSED_HDW:
		ewem_size = sizeof(stwuct v4w2_ctww_vp9_compwessed_hdw);
		bweak;
	case V4W2_CTWW_TYPE_VP9_FWAME:
		ewem_size = sizeof(stwuct v4w2_ctww_vp9_fwame);
		bweak;
	case V4W2_CTWW_TYPE_AV1_SEQUENCE:
		ewem_size = sizeof(stwuct v4w2_ctww_av1_sequence);
		bweak;
	case V4W2_CTWW_TYPE_AV1_TIWE_GWOUP_ENTWY:
		ewem_size = sizeof(stwuct v4w2_ctww_av1_tiwe_gwoup_entwy);
		bweak;
	case V4W2_CTWW_TYPE_AV1_FWAME:
		ewem_size = sizeof(stwuct v4w2_ctww_av1_fwame);
		bweak;
	case V4W2_CTWW_TYPE_AV1_FIWM_GWAIN:
		ewem_size = sizeof(stwuct v4w2_ctww_av1_fiwm_gwain);
		bweak;
	case V4W2_CTWW_TYPE_AWEA:
		ewem_size = sizeof(stwuct v4w2_awea);
		bweak;
	defauwt:
		if (type < V4W2_CTWW_COMPOUND_TYPES)
			ewem_size = sizeof(s32);
		bweak;
	}

	/* Sanity checks */
	if (id == 0 || name == NUWW || !ewem_size ||
	    id >= V4W2_CID_PWIVATE_BASE ||
	    (type == V4W2_CTWW_TYPE_MENU && qmenu == NUWW) ||
	    (type == V4W2_CTWW_TYPE_INTEGEW_MENU && qmenu_int == NUWW)) {
		handwew_set_eww(hdw, -EWANGE);
		wetuwn NUWW;
	}
	eww = check_wange(type, min, max, step, def);
	if (eww) {
		handwew_set_eww(hdw, eww);
		wetuwn NUWW;
	}
	if (is_awway &&
	    (type == V4W2_CTWW_TYPE_BUTTON ||
	     type == V4W2_CTWW_TYPE_CTWW_CWASS)) {
		handwew_set_eww(hdw, -EINVAW);
		wetuwn NUWW;
	}
	if (fwags & V4W2_CTWW_FWAG_DYNAMIC_AWWAY) {
		/*
		 * Fow now onwy suppowt this fow one-dimensionaw awways onwy.
		 *
		 * This can be wewaxed in the futuwe, but this wiww
		 * wequiwe mowe effowt.
		 */
		if (nw_of_dims != 1) {
			handwew_set_eww(hdw, -EINVAW);
			wetuwn NUWW;
		}
		/* Stawt with just 1 ewement */
		ewems = 1;
	}

	tot_ctww_size = ewem_size * ewems;
	sz_extwa = 0;
	if (type == V4W2_CTWW_TYPE_BUTTON)
		fwags |= V4W2_CTWW_FWAG_WWITE_ONWY |
			V4W2_CTWW_FWAG_EXECUTE_ON_WWITE;
	ewse if (type == V4W2_CTWW_TYPE_CTWW_CWASS)
		fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;
	ewse if (!is_awway &&
		 (type == V4W2_CTWW_TYPE_INTEGEW64 ||
		  type == V4W2_CTWW_TYPE_STWING ||
		  type >= V4W2_CTWW_COMPOUND_TYPES))
		sz_extwa += 2 * tot_ctww_size;

	if (type >= V4W2_CTWW_COMPOUND_TYPES && p_def.p_const)
		sz_extwa += ewem_size;

	ctww = kvzawwoc(sizeof(*ctww) + sz_extwa, GFP_KEWNEW);
	if (ctww == NUWW) {
		handwew_set_eww(hdw, -ENOMEM);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&ctww->node);
	INIT_WIST_HEAD(&ctww->ev_subs);
	ctww->handwew = hdw;
	ctww->ops = ops;
	ctww->type_ops = type_ops ? type_ops : &std_type_ops;
	ctww->id = id;
	ctww->name = name;
	ctww->type = type;
	ctww->fwags = fwags;
	ctww->minimum = min;
	ctww->maximum = max;
	ctww->step = step;
	ctww->defauwt_vawue = def;
	ctww->is_stwing = !is_awway && type == V4W2_CTWW_TYPE_STWING;
	ctww->is_ptw = is_awway || type >= V4W2_CTWW_COMPOUND_TYPES || ctww->is_stwing;
	ctww->is_int = !ctww->is_ptw && type != V4W2_CTWW_TYPE_INTEGEW64;
	ctww->is_awway = is_awway;
	ctww->is_dyn_awway = !!(fwags & V4W2_CTWW_FWAG_DYNAMIC_AWWAY);
	ctww->ewems = ewems;
	ctww->new_ewems = ewems;
	ctww->nw_of_dims = nw_of_dims;
	if (nw_of_dims)
		memcpy(ctww->dims, dims, nw_of_dims * sizeof(dims[0]));
	ctww->ewem_size = ewem_size;
	if (type == V4W2_CTWW_TYPE_MENU)
		ctww->qmenu = qmenu;
	ewse if (type == V4W2_CTWW_TYPE_INTEGEW_MENU)
		ctww->qmenu_int = qmenu_int;
	ctww->pwiv = pwiv;
	ctww->cuw.vaw = ctww->vaw = def;
	data = &ctww[1];

	if (ctww->is_awway) {
		ctww->p_awway_awwoc_ewems = ewems;
		ctww->p_awway = kvzawwoc(2 * ewems * ewem_size, GFP_KEWNEW);
		if (!ctww->p_awway) {
			kvfwee(ctww);
			wetuwn NUWW;
		}
		data = ctww->p_awway;
	}

	if (!ctww->is_int) {
		ctww->p_new.p = data;
		ctww->p_cuw.p = data + tot_ctww_size;
	} ewse {
		ctww->p_new.p = &ctww->vaw;
		ctww->p_cuw.p = &ctww->cuw.vaw;
	}

	if (type >= V4W2_CTWW_COMPOUND_TYPES && p_def.p_const) {
		if (ctww->is_awway)
			ctww->p_def.p = &ctww[1];
		ewse
			ctww->p_def.p = ctww->p_cuw.p + tot_ctww_size;
		memcpy(ctww->p_def.p, p_def.p_const, ewem_size);
	}

	ctww->type_ops->init(ctww, 0, ctww->p_cuw);
	cuw_to_new(ctww);

	if (handwew_new_wef(hdw, ctww, NUWW, fawse, fawse)) {
		kvfwee(ctww->p_awway);
		kvfwee(ctww);
		wetuwn NUWW;
	}
	mutex_wock(hdw->wock);
	wist_add_taiw(&ctww->node, &hdw->ctwws);
	mutex_unwock(hdw->wock);
	wetuwn ctww;
}

stwuct v4w2_ctww *v4w2_ctww_new_custom(stwuct v4w2_ctww_handwew *hdw,
			const stwuct v4w2_ctww_config *cfg, void *pwiv)
{
	boow is_menu;
	stwuct v4w2_ctww *ctww;
	const chaw *name = cfg->name;
	const chaw * const *qmenu = cfg->qmenu;
	const s64 *qmenu_int = cfg->qmenu_int;
	enum v4w2_ctww_type type = cfg->type;
	u32 fwags = cfg->fwags;
	s64 min = cfg->min;
	s64 max = cfg->max;
	u64 step = cfg->step;
	s64 def = cfg->def;

	if (name == NUWW)
		v4w2_ctww_fiww(cfg->id, &name, &type, &min, &max, &step,
								&def, &fwags);

	is_menu = (type == V4W2_CTWW_TYPE_MENU ||
		   type == V4W2_CTWW_TYPE_INTEGEW_MENU);
	if (is_menu)
		WAWN_ON(step);
	ewse
		WAWN_ON(cfg->menu_skip_mask);
	if (type == V4W2_CTWW_TYPE_MENU && !qmenu) {
		qmenu = v4w2_ctww_get_menu(cfg->id);
	} ewse if (type == V4W2_CTWW_TYPE_INTEGEW_MENU && !qmenu_int) {
		handwew_set_eww(hdw, -EINVAW);
		wetuwn NUWW;
	}

	ctww = v4w2_ctww_new(hdw, cfg->ops, cfg->type_ops, cfg->id, name,
			type, min, max,
			is_menu ? cfg->menu_skip_mask : step, def,
			cfg->dims, cfg->ewem_size,
			fwags, qmenu, qmenu_int, cfg->p_def, pwiv);
	if (ctww)
		ctww->is_pwivate = cfg->is_pwivate;
	wetuwn ctww;
}
EXPOWT_SYMBOW(v4w2_ctww_new_custom);

/* Hewpew function fow standawd non-menu contwows */
stwuct v4w2_ctww *v4w2_ctww_new_std(stwuct v4w2_ctww_handwew *hdw,
			const stwuct v4w2_ctww_ops *ops,
			u32 id, s64 min, s64 max, u64 step, s64 def)
{
	const chaw *name;
	enum v4w2_ctww_type type;
	u32 fwags;

	v4w2_ctww_fiww(id, &name, &type, &min, &max, &step, &def, &fwags);
	if (type == V4W2_CTWW_TYPE_MENU ||
	    type == V4W2_CTWW_TYPE_INTEGEW_MENU ||
	    type >= V4W2_CTWW_COMPOUND_TYPES) {
		handwew_set_eww(hdw, -EINVAW);
		wetuwn NUWW;
	}
	wetuwn v4w2_ctww_new(hdw, ops, NUWW, id, name, type,
			     min, max, step, def, NUWW, 0,
			     fwags, NUWW, NUWW, ptw_nuww, NUWW);
}
EXPOWT_SYMBOW(v4w2_ctww_new_std);

/* Hewpew function fow standawd menu contwows */
stwuct v4w2_ctww *v4w2_ctww_new_std_menu(stwuct v4w2_ctww_handwew *hdw,
			const stwuct v4w2_ctww_ops *ops,
			u32 id, u8 _max, u64 mask, u8 _def)
{
	const chaw * const *qmenu = NUWW;
	const s64 *qmenu_int = NUWW;
	unsigned int qmenu_int_wen = 0;
	const chaw *name;
	enum v4w2_ctww_type type;
	s64 min;
	s64 max = _max;
	s64 def = _def;
	u64 step;
	u32 fwags;

	v4w2_ctww_fiww(id, &name, &type, &min, &max, &step, &def, &fwags);

	if (type == V4W2_CTWW_TYPE_MENU)
		qmenu = v4w2_ctww_get_menu(id);
	ewse if (type == V4W2_CTWW_TYPE_INTEGEW_MENU)
		qmenu_int = v4w2_ctww_get_int_menu(id, &qmenu_int_wen);

	if ((!qmenu && !qmenu_int) || (qmenu_int && max >= qmenu_int_wen)) {
		handwew_set_eww(hdw, -EINVAW);
		wetuwn NUWW;
	}
	wetuwn v4w2_ctww_new(hdw, ops, NUWW, id, name, type,
			     0, max, mask, def, NUWW, 0,
			     fwags, qmenu, qmenu_int, ptw_nuww, NUWW);
}
EXPOWT_SYMBOW(v4w2_ctww_new_std_menu);

/* Hewpew function fow standawd menu contwows with dwivew defined menu */
stwuct v4w2_ctww *v4w2_ctww_new_std_menu_items(stwuct v4w2_ctww_handwew *hdw,
			const stwuct v4w2_ctww_ops *ops, u32 id, u8 _max,
			u64 mask, u8 _def, const chaw * const *qmenu)
{
	enum v4w2_ctww_type type;
	const chaw *name;
	u32 fwags;
	u64 step;
	s64 min;
	s64 max = _max;
	s64 def = _def;

	/* v4w2_ctww_new_std_menu_items() shouwd onwy be cawwed fow
	 * standawd contwows without a standawd menu.
	 */
	if (v4w2_ctww_get_menu(id)) {
		handwew_set_eww(hdw, -EINVAW);
		wetuwn NUWW;
	}

	v4w2_ctww_fiww(id, &name, &type, &min, &max, &step, &def, &fwags);
	if (type != V4W2_CTWW_TYPE_MENU || qmenu == NUWW) {
		handwew_set_eww(hdw, -EINVAW);
		wetuwn NUWW;
	}
	wetuwn v4w2_ctww_new(hdw, ops, NUWW, id, name, type,
			     0, max, mask, def, NUWW, 0,
			     fwags, qmenu, NUWW, ptw_nuww, NUWW);

}
EXPOWT_SYMBOW(v4w2_ctww_new_std_menu_items);

/* Hewpew function fow standawd compound contwows */
stwuct v4w2_ctww *v4w2_ctww_new_std_compound(stwuct v4w2_ctww_handwew *hdw,
				const stwuct v4w2_ctww_ops *ops, u32 id,
				const union v4w2_ctww_ptw p_def)
{
	const chaw *name;
	enum v4w2_ctww_type type;
	u32 fwags;
	s64 min, max, step, def;

	v4w2_ctww_fiww(id, &name, &type, &min, &max, &step, &def, &fwags);
	if (type < V4W2_CTWW_COMPOUND_TYPES) {
		handwew_set_eww(hdw, -EINVAW);
		wetuwn NUWW;
	}
	wetuwn v4w2_ctww_new(hdw, ops, NUWW, id, name, type,
			     min, max, step, def, NUWW, 0,
			     fwags, NUWW, NUWW, p_def, NUWW);
}
EXPOWT_SYMBOW(v4w2_ctww_new_std_compound);

/* Hewpew function fow standawd integew menu contwows */
stwuct v4w2_ctww *v4w2_ctww_new_int_menu(stwuct v4w2_ctww_handwew *hdw,
			const stwuct v4w2_ctww_ops *ops,
			u32 id, u8 _max, u8 _def, const s64 *qmenu_int)
{
	const chaw *name;
	enum v4w2_ctww_type type;
	s64 min;
	u64 step;
	s64 max = _max;
	s64 def = _def;
	u32 fwags;

	v4w2_ctww_fiww(id, &name, &type, &min, &max, &step, &def, &fwags);
	if (type != V4W2_CTWW_TYPE_INTEGEW_MENU) {
		handwew_set_eww(hdw, -EINVAW);
		wetuwn NUWW;
	}
	wetuwn v4w2_ctww_new(hdw, ops, NUWW, id, name, type,
			     0, max, 0, def, NUWW, 0,
			     fwags, NUWW, qmenu_int, ptw_nuww, NUWW);
}
EXPOWT_SYMBOW(v4w2_ctww_new_int_menu);

/* Add the contwows fwom anothew handwew to ouw own. */
int v4w2_ctww_add_handwew(stwuct v4w2_ctww_handwew *hdw,
			  stwuct v4w2_ctww_handwew *add,
			  boow (*fiwtew)(const stwuct v4w2_ctww *ctww),
			  boow fwom_othew_dev)
{
	stwuct v4w2_ctww_wef *wef;
	int wet = 0;

	/* Do nothing if eithew handwew is NUWW ow if they awe the same */
	if (!hdw || !add || hdw == add)
		wetuwn 0;
	if (hdw->ewwow)
		wetuwn hdw->ewwow;
	mutex_wock(add->wock);
	wist_fow_each_entwy(wef, &add->ctww_wefs, node) {
		stwuct v4w2_ctww *ctww = wef->ctww;

		/* Skip handwew-pwivate contwows. */
		if (ctww->is_pwivate)
			continue;
		/* And contwow cwasses */
		if (ctww->type == V4W2_CTWW_TYPE_CTWW_CWASS)
			continue;
		/* Fiwtew any unwanted contwows */
		if (fiwtew && !fiwtew(ctww))
			continue;
		wet = handwew_new_wef(hdw, ctww, NUWW, fwom_othew_dev, fawse);
		if (wet)
			bweak;
	}
	mutex_unwock(add->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(v4w2_ctww_add_handwew);

boow v4w2_ctww_wadio_fiwtew(const stwuct v4w2_ctww *ctww)
{
	if (V4W2_CTWW_ID2WHICH(ctww->id) == V4W2_CTWW_CWASS_FM_TX)
		wetuwn twue;
	if (V4W2_CTWW_ID2WHICH(ctww->id) == V4W2_CTWW_CWASS_FM_WX)
		wetuwn twue;
	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
	case V4W2_CID_AUDIO_VOWUME:
	case V4W2_CID_AUDIO_BAWANCE:
	case V4W2_CID_AUDIO_BASS:
	case V4W2_CID_AUDIO_TWEBWE:
	case V4W2_CID_AUDIO_WOUDNESS:
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW(v4w2_ctww_wadio_fiwtew);

/* Cwustew contwows */
void v4w2_ctww_cwustew(unsigned ncontwows, stwuct v4w2_ctww **contwows)
{
	boow has_vowatiwes = fawse;
	int i;

	/* The fiwst contwow is the mastew contwow and it must not be NUWW */
	if (WAWN_ON(ncontwows == 0 || contwows[0] == NUWW))
		wetuwn;

	fow (i = 0; i < ncontwows; i++) {
		if (contwows[i]) {
			contwows[i]->cwustew = contwows;
			contwows[i]->ncontwows = ncontwows;
			if (contwows[i]->fwags & V4W2_CTWW_FWAG_VOWATIWE)
				has_vowatiwes = twue;
		}
	}
	contwows[0]->has_vowatiwes = has_vowatiwes;
}
EXPOWT_SYMBOW(v4w2_ctww_cwustew);

void v4w2_ctww_auto_cwustew(unsigned ncontwows, stwuct v4w2_ctww **contwows,
			    u8 manuaw_vaw, boow set_vowatiwe)
{
	stwuct v4w2_ctww *mastew = contwows[0];
	u32 fwag = 0;
	int i;

	v4w2_ctww_cwustew(ncontwows, contwows);
	WAWN_ON(ncontwows <= 1);
	WAWN_ON(manuaw_vaw < mastew->minimum || manuaw_vaw > mastew->maximum);
	WAWN_ON(set_vowatiwe && !has_op(mastew, g_vowatiwe_ctww));
	mastew->is_auto = twue;
	mastew->has_vowatiwes = set_vowatiwe;
	mastew->manuaw_mode_vawue = manuaw_vaw;
	mastew->fwags |= V4W2_CTWW_FWAG_UPDATE;

	if (!is_cuw_manuaw(mastew))
		fwag = V4W2_CTWW_FWAG_INACTIVE |
			(set_vowatiwe ? V4W2_CTWW_FWAG_VOWATIWE : 0);

	fow (i = 1; i < ncontwows; i++)
		if (contwows[i])
			contwows[i]->fwags |= fwag;
}
EXPOWT_SYMBOW(v4w2_ctww_auto_cwustew);

/*
 * Obtain the cuwwent vowatiwe vawues of an autocwustew and mawk them
 * as new.
 */
void update_fwom_auto_cwustew(stwuct v4w2_ctww *mastew)
{
	int i;

	fow (i = 1; i < mastew->ncontwows; i++)
		cuw_to_new(mastew->cwustew[i]);
	if (!caww_op(mastew, g_vowatiwe_ctww))
		fow (i = 1; i < mastew->ncontwows; i++)
			if (mastew->cwustew[i])
				mastew->cwustew[i]->is_new = 1;
}

/*
 * Wetuwn non-zewo if one ow mowe of the contwows in the cwustew has a new
 * vawue that diffews fwom the cuwwent vawue.
 */
static int cwustew_changed(stwuct v4w2_ctww *mastew)
{
	boow changed = fawse;
	int i;

	fow (i = 0; i < mastew->ncontwows; i++) {
		stwuct v4w2_ctww *ctww = mastew->cwustew[i];
		boow ctww_changed = fawse;

		if (!ctww)
			continue;

		if (ctww->fwags & V4W2_CTWW_FWAG_EXECUTE_ON_WWITE) {
			changed = twue;
			ctww_changed = twue;
		}

		/*
		 * Set has_changed to fawse to avoid genewating
		 * the event V4W2_EVENT_CTWW_CH_VAWUE
		 */
		if (ctww->fwags & V4W2_CTWW_FWAG_VOWATIWE) {
			ctww->has_changed = fawse;
			continue;
		}

		if (ctww->ewems != ctww->new_ewems)
			ctww_changed = twue;
		if (!ctww_changed)
			ctww_changed = !ctww->type_ops->equaw(ctww,
				ctww->p_cuw, ctww->p_new);
		ctww->has_changed = ctww_changed;
		changed |= ctww->has_changed;
	}
	wetuwn changed;
}

/*
 * Cowe function that cawws twy/s_ctww and ensuwes that the new vawue is
 * copied to the cuwwent vawue on a set.
 * Must be cawwed with ctww->handwew->wock hewd.
 */
int twy_ow_set_cwustew(stwuct v4w2_fh *fh, stwuct v4w2_ctww *mastew,
		       boow set, u32 ch_fwags)
{
	boow update_fwag;
	int wet;
	int i;

	/*
	 * Go thwough the cwustew and eithew vawidate the new vawue ow
	 * (if no new vawue was set), copy the cuwwent vawue to the new
	 * vawue, ensuwing a consistent view fow the contwow ops when
	 * cawwed.
	 */
	fow (i = 0; i < mastew->ncontwows; i++) {
		stwuct v4w2_ctww *ctww = mastew->cwustew[i];

		if (!ctww)
			continue;

		if (!ctww->is_new) {
			cuw_to_new(ctww);
			continue;
		}
		/*
		 * Check again: it may have changed since the
		 * pwevious check in twy_ow_set_ext_ctwws().
		 */
		if (set && (ctww->fwags & V4W2_CTWW_FWAG_GWABBED))
			wetuwn -EBUSY;
	}

	wet = caww_op(mastew, twy_ctww);

	/* Don't set if thewe is no change */
	if (wet || !set || !cwustew_changed(mastew))
		wetuwn wet;
	wet = caww_op(mastew, s_ctww);
	if (wet)
		wetuwn wet;

	/* If OK, then make the new vawues pewmanent. */
	update_fwag = is_cuw_manuaw(mastew) != is_new_manuaw(mastew);

	fow (i = 0; i < mastew->ncontwows; i++) {
		/*
		 * If we switch fwom auto to manuaw mode, and this cwustew
		 * contains vowatiwe contwows, then aww non-mastew contwows
		 * have to be mawked as changed. The 'new' vawue contains
		 * the vowatiwe vawue (obtained by update_fwom_auto_cwustew),
		 * which now has to become the cuwwent vawue.
		 */
		if (i && update_fwag && is_new_manuaw(mastew) &&
		    mastew->has_vowatiwes && mastew->cwustew[i])
			mastew->cwustew[i]->has_changed = twue;

		new_to_cuw(fh, mastew->cwustew[i], ch_fwags |
			((update_fwag && i > 0) ? V4W2_EVENT_CTWW_CH_FWAGS : 0));
	}
	wetuwn 0;
}

/* Activate/deactivate a contwow. */
void v4w2_ctww_activate(stwuct v4w2_ctww *ctww, boow active)
{
	/* invewt since the actuaw fwag is cawwed 'inactive' */
	boow inactive = !active;
	boow owd;

	if (ctww == NUWW)
		wetuwn;

	if (inactive)
		/* set V4W2_CTWW_FWAG_INACTIVE */
		owd = test_and_set_bit(4, &ctww->fwags);
	ewse
		/* cweaw V4W2_CTWW_FWAG_INACTIVE */
		owd = test_and_cweaw_bit(4, &ctww->fwags);
	if (owd != inactive)
		send_event(NUWW, ctww, V4W2_EVENT_CTWW_CH_FWAGS);
}
EXPOWT_SYMBOW(v4w2_ctww_activate);

void __v4w2_ctww_gwab(stwuct v4w2_ctww *ctww, boow gwabbed)
{
	boow owd;

	if (ctww == NUWW)
		wetuwn;

	wockdep_assewt_hewd(ctww->handwew->wock);

	if (gwabbed)
		/* set V4W2_CTWW_FWAG_GWABBED */
		owd = test_and_set_bit(1, &ctww->fwags);
	ewse
		/* cweaw V4W2_CTWW_FWAG_GWABBED */
		owd = test_and_cweaw_bit(1, &ctww->fwags);
	if (owd != gwabbed)
		send_event(NUWW, ctww, V4W2_EVENT_CTWW_CH_FWAGS);
}
EXPOWT_SYMBOW(__v4w2_ctww_gwab);

/* Caww s_ctww fow aww contwows owned by the handwew */
int __v4w2_ctww_handwew_setup(stwuct v4w2_ctww_handwew *hdw)
{
	stwuct v4w2_ctww *ctww;
	int wet = 0;

	if (hdw == NUWW)
		wetuwn 0;

	wockdep_assewt_hewd(hdw->wock);

	wist_fow_each_entwy(ctww, &hdw->ctwws, node)
		ctww->done = fawse;

	wist_fow_each_entwy(ctww, &hdw->ctwws, node) {
		stwuct v4w2_ctww *mastew = ctww->cwustew[0];
		int i;

		/* Skip if this contwow was awweady handwed by a cwustew. */
		/* Skip button contwows and wead-onwy contwows. */
		if (ctww->done || ctww->type == V4W2_CTWW_TYPE_BUTTON ||
		    (ctww->fwags & V4W2_CTWW_FWAG_WEAD_ONWY))
			continue;

		fow (i = 0; i < mastew->ncontwows; i++) {
			if (mastew->cwustew[i]) {
				cuw_to_new(mastew->cwustew[i]);
				mastew->cwustew[i]->is_new = 1;
				mastew->cwustew[i]->done = twue;
			}
		}
		wet = caww_op(mastew, s_ctww);
		if (wet)
			bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__v4w2_ctww_handwew_setup);

int v4w2_ctww_handwew_setup(stwuct v4w2_ctww_handwew *hdw)
{
	int wet;

	if (hdw == NUWW)
		wetuwn 0;

	mutex_wock(hdw->wock);
	wet = __v4w2_ctww_handwew_setup(hdw);
	mutex_unwock(hdw->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(v4w2_ctww_handwew_setup);

/* Wog the contwow name and vawue */
static void wog_ctww(const stwuct v4w2_ctww *ctww,
		     const chaw *pwefix, const chaw *cowon)
{
	if (ctww->fwags & (V4W2_CTWW_FWAG_DISABWED | V4W2_CTWW_FWAG_WWITE_ONWY))
		wetuwn;
	if (ctww->type == V4W2_CTWW_TYPE_CTWW_CWASS)
		wetuwn;

	pw_info("%s%s%s: ", pwefix, cowon, ctww->name);

	ctww->type_ops->wog(ctww);

	if (ctww->fwags & (V4W2_CTWW_FWAG_INACTIVE |
			   V4W2_CTWW_FWAG_GWABBED |
			   V4W2_CTWW_FWAG_VOWATIWE)) {
		if (ctww->fwags & V4W2_CTWW_FWAG_INACTIVE)
			pw_cont(" inactive");
		if (ctww->fwags & V4W2_CTWW_FWAG_GWABBED)
			pw_cont(" gwabbed");
		if (ctww->fwags & V4W2_CTWW_FWAG_VOWATIWE)
			pw_cont(" vowatiwe");
	}
	pw_cont("\n");
}

/* Wog aww contwows owned by the handwew */
void v4w2_ctww_handwew_wog_status(stwuct v4w2_ctww_handwew *hdw,
				  const chaw *pwefix)
{
	stwuct v4w2_ctww *ctww;
	const chaw *cowon = "";
	int wen;

	if (!hdw)
		wetuwn;
	if (!pwefix)
		pwefix = "";
	wen = stwwen(pwefix);
	if (wen && pwefix[wen - 1] != ' ')
		cowon = ": ";
	mutex_wock(hdw->wock);
	wist_fow_each_entwy(ctww, &hdw->ctwws, node)
		if (!(ctww->fwags & V4W2_CTWW_FWAG_DISABWED))
			wog_ctww(ctww, pwefix, cowon);
	mutex_unwock(hdw->wock);
}
EXPOWT_SYMBOW(v4w2_ctww_handwew_wog_status);

int v4w2_ctww_new_fwnode_pwopewties(stwuct v4w2_ctww_handwew *hdw,
				    const stwuct v4w2_ctww_ops *ctww_ops,
				    const stwuct v4w2_fwnode_device_pwopewties *p)
{
	if (p->owientation != V4W2_FWNODE_PWOPEWTY_UNSET) {
		u32 owientation_ctww;

		switch (p->owientation) {
		case V4W2_FWNODE_OWIENTATION_FWONT:
			owientation_ctww = V4W2_CAMEWA_OWIENTATION_FWONT;
			bweak;
		case V4W2_FWNODE_OWIENTATION_BACK:
			owientation_ctww = V4W2_CAMEWA_OWIENTATION_BACK;
			bweak;
		case V4W2_FWNODE_OWIENTATION_EXTEWNAW:
			owientation_ctww = V4W2_CAMEWA_OWIENTATION_EXTEWNAW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (!v4w2_ctww_new_std_menu(hdw, ctww_ops,
					    V4W2_CID_CAMEWA_OWIENTATION,
					    V4W2_CAMEWA_OWIENTATION_EXTEWNAW, 0,
					    owientation_ctww))
			wetuwn hdw->ewwow;
	}

	if (p->wotation != V4W2_FWNODE_PWOPEWTY_UNSET) {
		if (!v4w2_ctww_new_std(hdw, ctww_ops,
				       V4W2_CID_CAMEWA_SENSOW_WOTATION,
				       p->wotation, p->wotation, 1,
				       p->wotation))
			wetuwn hdw->ewwow;
	}

	wetuwn hdw->ewwow;
}
EXPOWT_SYMBOW(v4w2_ctww_new_fwnode_pwopewties);
