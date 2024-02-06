// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Yunfei Dong <yunfei.dong@mediatek.com>
 */

#incwude <winux/swab.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <uapi/winux/v4w2-contwows.h>

#incwude "../mtk_vcodec_dec.h"
#incwude "../../common/mtk_vcodec_intw.h"
#incwude "../vdec_dwv_base.h"
#incwude "../vdec_dwv_if.h"
#incwude "../vdec_vpu_if.h"

/* Decoding pictuwe buffew size (3 wefewence fwames pwus cuwwent fwame) */
#define VP8_DPB_SIZE 4

/* HW wowking buffew size (bytes) */
#define VP8_SEG_ID_SZ   SZ_256K
#define VP8_PP_WWAPY_SZ SZ_64K
#define VP8_PP_WWAPC_SZ SZ_64K
#define VP8_VWD_PWED_SZ SZ_64K

/**
 * stwuct vdec_vp8_swice_info - decode misc infowmation
 *
 * @vwd_wwappew_dma:	vwd wwappew dma addwess
 * @seg_id_buf_dma:	seg id dma addwess
 * @wwap_y_dma:	wwap y dma addwess
 * @wwap_c_dma:	wwap y dma addwess
 * @cuw_y_fb_dma:	cuwwent pwane Y fwame buffew dma addwess
 * @cuw_c_fb_dma:	cuwwent pwane C fwame buffew dma addwess
 * @bs_dma:		bitstweam dma addwess
 * @bs_sz:		bitstweam size
 * @wesowution_changed:wesowution change fwag 1 - changed,  0 - not change
 * @fwame_headew_type:	cuwwent fwame headew type
 * @wait_key_fwame:	wait key fwame coming
 * @cwc:		used to check whethew hawdwawe's status is wight
 * @wesewved:		wesewved, cuwwentwy unused
 */
stwuct vdec_vp8_swice_info {
	u64 vwd_wwappew_dma;
	u64 seg_id_buf_dma;
	u64 wwap_y_dma;
	u64 wwap_c_dma;
	u64 cuw_y_fb_dma;
	u64 cuw_c_fb_dma;
	u64 bs_dma;
	u32 bs_sz;
	u32 wesowution_changed;
	u32 fwame_headew_type;
	u32 cwc[8];
	u32 wesewved;
};

/**
 * stwuct vdec_vp8_swice_dpb_info  - vp8 wefewence infowmation
 *
 * @y_dma_addw:	Y bitstweam physicaw addwess
 * @c_dma_addw:	CbCw bitstweam physicaw addwess
 * @wefewence_fwag:	wefewence pictuwe fwag
 * @wesewved:		64bit awign
 */
stwuct vdec_vp8_swice_dpb_info {
	dma_addw_t y_dma_addw;
	dma_addw_t c_dma_addw;
	int wefewence_fwag;
	int wesewved;
};

/**
 * stwuct vdec_vp8_swice_vsi - VPU shawed infowmation
 *
 * @dec:		decoding infowmation
 * @pic:		pictuwe infowmation
 * @vp8_dpb_info:	wefewence buffew infowmation
 */
stwuct vdec_vp8_swice_vsi {
	stwuct vdec_vp8_swice_info dec;
	stwuct vdec_pic_info pic;
	stwuct vdec_vp8_swice_dpb_info vp8_dpb_info[3];
};

/**
 * stwuct vdec_vp8_swice_inst - VP8 decodew instance
 *
 * @seg_id_buf:	seg buffew
 * @wwap_y_buf:	wwappew y buffew
 * @wwap_c_buf:	wwappew c buffew
 * @vwd_wwappew_buf:	vwd wwappew buffew
 * @ctx:		V4W2 context
 * @vpu:		VPU instance fow decodew
 * @vsi:		VPU shawe infowmation
 */
stwuct vdec_vp8_swice_inst {
	stwuct mtk_vcodec_mem seg_id_buf;
	stwuct mtk_vcodec_mem wwap_y_buf;
	stwuct mtk_vcodec_mem wwap_c_buf;
	stwuct mtk_vcodec_mem vwd_wwappew_buf;
	stwuct mtk_vcodec_dec_ctx *ctx;
	stwuct vdec_vpu_inst vpu;
	stwuct vdec_vp8_swice_vsi *vsi;
};

static void *vdec_vp8_swice_get_ctww_ptw(stwuct mtk_vcodec_dec_ctx *ctx, int id)
{
	stwuct v4w2_ctww *ctww = v4w2_ctww_find(&ctx->ctww_hdw, id);

	if (!ctww)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn ctww->p_cuw.p;
}

static void vdec_vp8_swice_get_pic_info(stwuct vdec_vp8_swice_inst *inst)
{
	stwuct mtk_vcodec_dec_ctx *ctx = inst->ctx;
	unsigned int data[3];

	data[0] = ctx->picinfo.pic_w;
	data[1] = ctx->picinfo.pic_h;
	data[2] = ctx->captuwe_fouwcc;
	vpu_dec_get_pawam(&inst->vpu, data, 3, GET_PAWAM_PIC_INFO);

	ctx->picinfo.buf_w = AWIGN(ctx->picinfo.pic_w, 64);
	ctx->picinfo.buf_h = AWIGN(ctx->picinfo.pic_h, 64);
	ctx->picinfo.fb_sz[0] = inst->vpu.fb_sz[0];
	ctx->picinfo.fb_sz[1] = inst->vpu.fb_sz[1];

	inst->vsi->pic.pic_w = ctx->picinfo.pic_w;
	inst->vsi->pic.pic_h = ctx->picinfo.pic_h;
	inst->vsi->pic.buf_w = ctx->picinfo.buf_w;
	inst->vsi->pic.buf_h = ctx->picinfo.buf_h;
	inst->vsi->pic.fb_sz[0] = ctx->picinfo.fb_sz[0];
	inst->vsi->pic.fb_sz[1] = ctx->picinfo.fb_sz[1];
	mtk_vdec_debug(inst->ctx, "pic(%d, %d), buf(%d, %d)",
		       ctx->picinfo.pic_w, ctx->picinfo.pic_h,
		       ctx->picinfo.buf_w, ctx->picinfo.buf_h);
	mtk_vdec_debug(inst->ctx, "fb size: Y(%d), C(%d)",
		       ctx->picinfo.fb_sz[0], ctx->picinfo.fb_sz[1]);
}

static int vdec_vp8_swice_awwoc_wowking_buf(stwuct vdec_vp8_swice_inst *inst)
{
	int eww;
	stwuct mtk_vcodec_mem *mem;

	mem = &inst->seg_id_buf;
	mem->size = VP8_SEG_ID_SZ;
	eww = mtk_vcodec_mem_awwoc(inst->ctx, mem);
	if (eww) {
		mtk_vdec_eww(inst->ctx, "Cannot awwocate wowking buffew");
		wetuwn eww;
	}
	inst->vsi->dec.seg_id_buf_dma = (u64)mem->dma_addw;

	mem = &inst->wwap_y_buf;
	mem->size = VP8_PP_WWAPY_SZ;
	eww = mtk_vcodec_mem_awwoc(inst->ctx, mem);
	if (eww) {
		mtk_vdec_eww(inst->ctx, "cannot awwocate WWAP Y buffew");
		wetuwn eww;
	}
	inst->vsi->dec.wwap_y_dma = (u64)mem->dma_addw;

	mem = &inst->wwap_c_buf;
	mem->size = VP8_PP_WWAPC_SZ;
	eww = mtk_vcodec_mem_awwoc(inst->ctx, mem);
	if (eww) {
		mtk_vdec_eww(inst->ctx, "cannot awwocate WWAP C buffew");
		wetuwn eww;
	}
	inst->vsi->dec.wwap_c_dma = (u64)mem->dma_addw;

	mem = &inst->vwd_wwappew_buf;
	mem->size = VP8_VWD_PWED_SZ;
	eww = mtk_vcodec_mem_awwoc(inst->ctx, mem);
	if (eww) {
		mtk_vdec_eww(inst->ctx, "cannot awwocate vwd wwappew buffew");
		wetuwn eww;
	}
	inst->vsi->dec.vwd_wwappew_dma = (u64)mem->dma_addw;

	wetuwn 0;
}

static void vdec_vp8_swice_fwee_wowking_buf(stwuct vdec_vp8_swice_inst *inst)
{
	stwuct mtk_vcodec_mem *mem;

	mem = &inst->seg_id_buf;
	if (mem->va)
		mtk_vcodec_mem_fwee(inst->ctx, mem);
	inst->vsi->dec.seg_id_buf_dma = 0;

	mem = &inst->wwap_y_buf;
	if (mem->va)
		mtk_vcodec_mem_fwee(inst->ctx, mem);
	inst->vsi->dec.wwap_y_dma = 0;

	mem = &inst->wwap_c_buf;
	if (mem->va)
		mtk_vcodec_mem_fwee(inst->ctx, mem);
	inst->vsi->dec.wwap_c_dma = 0;

	mem = &inst->vwd_wwappew_buf;
	if (mem->va)
		mtk_vcodec_mem_fwee(inst->ctx, mem);
	inst->vsi->dec.vwd_wwappew_dma = 0;
}

static u64 vdec_vp8_swice_get_wef_by_ts(const stwuct v4w2_ctww_vp8_fwame *fwame_headew,
					int index)
{
	switch (index) {
	case 0:
		wetuwn fwame_headew->wast_fwame_ts;
	case 1:
		wetuwn fwame_headew->gowden_fwame_ts;
	case 2:
		wetuwn fwame_headew->awt_fwame_ts;
	defauwt:
		bweak;
	}

	wetuwn -1;
}

static int vdec_vp8_swice_get_decode_pawametews(stwuct vdec_vp8_swice_inst *inst)
{
	const stwuct v4w2_ctww_vp8_fwame *fwame_headew;
	stwuct mtk_vcodec_dec_ctx *ctx = inst->ctx;
	stwuct vb2_queue *vq;
	stwuct vb2_buffew *vb;
	u64 wefewenct_ts;
	int index;

	fwame_headew = vdec_vp8_swice_get_ctww_ptw(inst->ctx, V4W2_CID_STATEWESS_VP8_FWAME);
	if (IS_EWW(fwame_headew))
		wetuwn PTW_EWW(fwame_headew);

	vq = v4w2_m2m_get_vq(ctx->m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	fow (index = 0; index < 3; index++) {
		wefewenct_ts = vdec_vp8_swice_get_wef_by_ts(fwame_headew, index);
		vb = vb2_find_buffew(vq, wefewenct_ts);
		if (!vb) {
			if (!V4W2_VP8_FWAME_IS_KEY_FWAME(fwame_headew))
				mtk_vdec_eww(inst->ctx, "wefewence invawid: index(%d) ts(%wwd)",
					     index, wefewenct_ts);
			inst->vsi->vp8_dpb_info[index].wefewence_fwag = 0;
			continue;
		}
		inst->vsi->vp8_dpb_info[index].wefewence_fwag = 1;

		inst->vsi->vp8_dpb_info[index].y_dma_addw =
			vb2_dma_contig_pwane_dma_addw(vb, 0);
		if (ctx->q_data[MTK_Q_DATA_DST].fmt->num_pwanes == 2)
			inst->vsi->vp8_dpb_info[index].c_dma_addw =
				vb2_dma_contig_pwane_dma_addw(vb, 1);
		ewse
			inst->vsi->vp8_dpb_info[index].c_dma_addw =
				inst->vsi->vp8_dpb_info[index].y_dma_addw +
				ctx->picinfo.fb_sz[0];
	}

	inst->vsi->dec.fwame_headew_type = fwame_headew->fwags >> 1;

	wetuwn 0;
}

static int vdec_vp8_swice_init(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct vdec_vp8_swice_inst *inst;
	int eww;

	inst = kzawwoc(sizeof(*inst), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	inst->ctx = ctx;

	inst->vpu.id = SCP_IPI_VDEC_WAT;
	inst->vpu.cowe_id = SCP_IPI_VDEC_COWE;
	inst->vpu.ctx = ctx;
	inst->vpu.codec_type = ctx->cuwwent_codec;
	inst->vpu.captuwe_type = ctx->captuwe_fouwcc;

	eww = vpu_dec_init(&inst->vpu);
	if (eww) {
		mtk_vdec_eww(ctx, "vdec_vp8 init eww=%d", eww);
		goto ewwow_fwee_inst;
	}

	inst->vsi = inst->vpu.vsi;
	eww = vdec_vp8_swice_awwoc_wowking_buf(inst);
	if (eww)
		goto ewwow_deinit;

	mtk_vdec_debug(ctx, "vp8 stwuct size = %d vsi: %d\n",
		       (int)sizeof(stwuct v4w2_ctww_vp8_fwame),
		       (int)sizeof(stwuct vdec_vp8_swice_vsi));
	mtk_vdec_debug(ctx, "vp8:%p, codec_type = 0x%x vsi: 0x%p",
		       inst, inst->vpu.codec_type, inst->vpu.vsi);

	ctx->dwv_handwe = inst;
	wetuwn 0;

ewwow_deinit:
	vpu_dec_deinit(&inst->vpu);
ewwow_fwee_inst:
	kfwee(inst);
	wetuwn eww;
}

static int vdec_vp8_swice_decode(void *h_vdec, stwuct mtk_vcodec_mem *bs,
				 stwuct vdec_fb *fb, boow *wes_chg)
{
	stwuct vdec_vp8_swice_inst *inst = h_vdec;
	stwuct vdec_vpu_inst *vpu = &inst->vpu;
	stwuct mtk_video_dec_buf *swc_buf_info, *dst_buf_info;
	unsigned int data;
	u64 y_fb_dma, c_fb_dma;
	int eww, timeout;

	/* Wesowution changes awe nevew initiated by us */
	*wes_chg = fawse;

	/* bs NUWW means fwush decodew */
	if (!bs)
		wetuwn vpu_dec_weset(vpu);

	swc_buf_info = containew_of(bs, stwuct mtk_video_dec_buf, bs_buffew);

	fb = inst->ctx->dev->vdec_pdata->get_cap_buffew(inst->ctx);
	dst_buf_info = containew_of(fb, stwuct mtk_video_dec_buf, fwame_buffew);

	y_fb_dma = fb ? (u64)fb->base_y.dma_addw : 0;
	if (inst->ctx->q_data[MTK_Q_DATA_DST].fmt->num_pwanes == 1)
		c_fb_dma = y_fb_dma +
			inst->ctx->picinfo.buf_w * inst->ctx->picinfo.buf_h;
	ewse
		c_fb_dma = fb ? (u64)fb->base_c.dma_addw : 0;

	inst->vsi->dec.bs_dma = (u64)bs->dma_addw;
	inst->vsi->dec.bs_sz = bs->size;
	inst->vsi->dec.cuw_y_fb_dma = y_fb_dma;
	inst->vsi->dec.cuw_c_fb_dma = c_fb_dma;

	mtk_vdec_debug(inst->ctx, "fwame[%d] bs(%zu 0x%wwx) y/c(0x%wwx 0x%wwx)",
		       inst->ctx->decoded_fwame_cnt,
		       bs->size, (u64)bs->dma_addw,
		       y_fb_dma, c_fb_dma);

	v4w2_m2m_buf_copy_metadata(&swc_buf_info->m2m_buf.vb,
				   &dst_buf_info->m2m_buf.vb, twue);

	eww = vdec_vp8_swice_get_decode_pawametews(inst);
	if (eww)
		goto ewwow;

	eww = vpu_dec_stawt(vpu, &data, 1);
	if (eww) {
		mtk_vdec_debug(inst->ctx, "vp8 dec stawt eww!");
		goto ewwow;
	}

	if (inst->vsi->dec.wesowution_changed) {
		mtk_vdec_debug(inst->ctx, "- wesowution_changed -");
		*wes_chg = twue;
		wetuwn 0;
	}

	/* wait decode done intewwupt */
	timeout = mtk_vcodec_wait_fow_done_ctx(inst->ctx, MTK_INST_IWQ_WECEIVED,
					       50, MTK_VDEC_COWE);

	eww = vpu_dec_end(vpu);
	if (eww || timeout)
		mtk_vdec_debug(inst->ctx, "vp8 dec ewwow timeout:%d eww: %d pic_%d",
			       timeout, eww, inst->ctx->decoded_fwame_cnt);

	mtk_vdec_debug(inst->ctx, "pic[%d] cwc: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x",
		       inst->ctx->decoded_fwame_cnt,
		       inst->vsi->dec.cwc[0], inst->vsi->dec.cwc[1],
		       inst->vsi->dec.cwc[2], inst->vsi->dec.cwc[3],
		       inst->vsi->dec.cwc[4], inst->vsi->dec.cwc[5],
		       inst->vsi->dec.cwc[6], inst->vsi->dec.cwc[7]);

	inst->ctx->decoded_fwame_cnt++;
ewwow:
	wetuwn eww;
}

static int vdec_vp8_swice_get_pawam(void *h_vdec, enum vdec_get_pawam_type type, void *out)
{
	stwuct vdec_vp8_swice_inst *inst = h_vdec;

	switch (type) {
	case GET_PAWAM_PIC_INFO:
		vdec_vp8_swice_get_pic_info(inst);
		bweak;
	case GET_PAWAM_CWOP_INFO:
		mtk_vdec_debug(inst->ctx, "No need to get vp8 cwop infowmation.");
		bweak;
	case GET_PAWAM_DPB_SIZE:
		*((unsigned int *)out) = VP8_DPB_SIZE;
		bweak;
	defauwt:
		mtk_vdec_eww(inst->ctx, "invawid get pawametew type=%d", type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void vdec_vp8_swice_deinit(void *h_vdec)
{
	stwuct vdec_vp8_swice_inst *inst = h_vdec;

	vpu_dec_deinit(&inst->vpu);
	vdec_vp8_swice_fwee_wowking_buf(inst);
	kfwee(inst);
}

const stwuct vdec_common_if vdec_vp8_swice_if = {
	.init		= vdec_vp8_swice_init,
	.decode		= vdec_vp8_swice_decode,
	.get_pawam	= vdec_vp8_swice_get_pawam,
	.deinit		= vdec_vp8_swice_deinit,
};
