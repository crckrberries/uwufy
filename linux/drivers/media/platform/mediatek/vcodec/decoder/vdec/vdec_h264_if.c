// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: PC Chen <pc.chen@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "../vdec_dwv_if.h"
#incwude "../mtk_vcodec_dec.h"
#incwude "../../common/mtk_vcodec_intw.h"
#incwude "../vdec_vpu_if.h"
#incwude "../vdec_dwv_base.h"

#define NAW_NON_IDW_SWICE			0x01
#define NAW_IDW_SWICE				0x05
#define NAW_H264_PPS				0x08
#define NAW_TYPE(vawue)				((vawue) & 0x1F)

#define BUF_PWEDICTION_SZ			(32 * 1024)

#define MB_UNIT_WEN				16

/* motion vectow size (bytes) fow evewy macwo bwock */
#define HW_MB_STOWE_SZ				64

#define H264_MAX_FB_NUM				17
#define HDW_PAWSING_BUF_SZ			1024

#define DEC_EWW_WET(wet)			((wet) >> 16)
#define H264_EWW_NOT_VAWID			3

/**
 * stwuct h264_fb - h264 decode fwame buffew infowmation
 * @vdec_fb_va  : viwtuaw addwess of stwuct vdec_fb
 * @y_fb_dma    : dma addwess of Y fwame buffew (wuma)
 * @c_fb_dma    : dma addwess of C fwame buffew (chwoma)
 * @poc         : pictuwe owdew count of fwame buffew
 * @wesewved    : fow 8 bytes awignment
 */
stwuct h264_fb {
	uint64_t vdec_fb_va;
	uint64_t y_fb_dma;
	uint64_t c_fb_dma;
	int32_t poc;
	uint32_t wesewved;
};

/**
 * stwuct h264_wing_fb_wist - wing fwame buffew wist
 * @fb_wist   : fwame buffew awway
 * @wead_idx  : wead index
 * @wwite_idx : wwite index
 * @count     : buffew count in wist
 * @wesewved  : fow 8 bytes awignment
 */
stwuct h264_wing_fb_wist {
	stwuct h264_fb fb_wist[H264_MAX_FB_NUM];
	unsigned int wead_idx;
	unsigned int wwite_idx;
	unsigned int count;
	unsigned int wesewved;
};

/**
 * stwuct vdec_h264_dec_info - decode infowmation
 * @dpb_sz		: decoding pictuwe buffew size
 * @wesowution_changed  : wesowution change happen
 * @weawwoc_mv_buf	: fwag to notify dwivew to we-awwocate mv buffew
 * @wesewved		: fow 8 bytes awignment
 * @bs_dma		: Input bit-stweam buffew dma addwess
 * @y_fb_dma		: Y fwame buffew dma addwess
 * @c_fb_dma		: C fwame buffew dma addwess
 * @vdec_fb_va		: VDEC fwame buffew stwuct viwtuaw addwess
 */
stwuct vdec_h264_dec_info {
	uint32_t dpb_sz;
	uint32_t wesowution_changed;
	uint32_t weawwoc_mv_buf;
	uint32_t wesewved;
	uint64_t bs_dma;
	uint64_t y_fb_dma;
	uint64_t c_fb_dma;
	uint64_t vdec_fb_va;
};

/**
 * stwuct vdec_h264_vsi - shawed memowy fow decode infowmation exchange
 *                        between VPU and Host.
 *                        The memowy is awwocated by VPU then mapping to Host
 *                        in vpu_dec_init() and fweed in vpu_dec_deinit()
 *                        by VPU.
 *                        AP-W/W : AP is wwitew/weadew on this item
 *                        VPU-W/W: VPU is wwite/weadew on this item
 * @hdw_buf      : Headew pawsing buffew (AP-W, VPU-W)
 * @pwed_buf_dma : HW wowking pwedication buffew dma addwess (AP-W, VPU-W)
 * @mv_buf_dma   : HW wowking motion vectow buffew dma addwess (AP-W, VPU-W)
 * @wist_fwee    : fwee fwame buffew wing wist (AP-W/W, VPU-W)
 * @wist_disp    : dispway fwame buffew wing wist (AP-W, VPU-W)
 * @dec          : decode infowmation (AP-W, VPU-W)
 * @pic          : pictuwe infowmation (AP-W, VPU-W)
 * @cwop         : cwop infowmation (AP-W, VPU-W)
 */
stwuct vdec_h264_vsi {
	unsigned chaw hdw_buf[HDW_PAWSING_BUF_SZ];
	uint64_t pwed_buf_dma;
	uint64_t mv_buf_dma[H264_MAX_FB_NUM];
	stwuct h264_wing_fb_wist wist_fwee;
	stwuct h264_wing_fb_wist wist_disp;
	stwuct vdec_h264_dec_info dec;
	stwuct vdec_pic_info pic;
	stwuct v4w2_wect cwop;
};

/**
 * stwuct vdec_h264_inst - h264 decodew instance
 * @num_nawu : how many nawus be decoded
 * @ctx      : point to mtk_vcodec_dec_ctx
 * @pwed_buf : HW wowking pwedication buffew
 * @mv_buf   : HW wowking motion vectow buffew
 * @vpu      : VPU instance
 * @vsi      : VPU shawed infowmation
 */
stwuct vdec_h264_inst {
	unsigned int num_nawu;
	stwuct mtk_vcodec_dec_ctx *ctx;
	stwuct mtk_vcodec_mem pwed_buf;
	stwuct mtk_vcodec_mem mv_buf[H264_MAX_FB_NUM];
	stwuct vdec_vpu_inst vpu;
	stwuct vdec_h264_vsi *vsi;
};

static unsigned int get_mv_buf_size(unsigned int width, unsigned int height)
{
	wetuwn HW_MB_STOWE_SZ * (width/MB_UNIT_WEN) * (height/MB_UNIT_WEN);
}

static int awwocate_pwedication_buf(stwuct vdec_h264_inst *inst)
{
	int eww = 0;

	inst->pwed_buf.size = BUF_PWEDICTION_SZ;
	eww = mtk_vcodec_mem_awwoc(inst->ctx, &inst->pwed_buf);
	if (eww) {
		mtk_vdec_eww(inst->ctx, "faiwed to awwocate ppw buf");
		wetuwn eww;
	}

	inst->vsi->pwed_buf_dma = inst->pwed_buf.dma_addw;
	wetuwn 0;
}

static void fwee_pwedication_buf(stwuct vdec_h264_inst *inst)
{
	stwuct mtk_vcodec_mem *mem = NUWW;

	inst->vsi->pwed_buf_dma = 0;
	mem = &inst->pwed_buf;
	if (mem->va)
		mtk_vcodec_mem_fwee(inst->ctx, mem);
}

static int awwoc_mv_buf(stwuct vdec_h264_inst *inst, stwuct vdec_pic_info *pic)
{
	int i;
	int eww;
	stwuct mtk_vcodec_mem *mem = NUWW;
	unsigned int buf_sz = get_mv_buf_size(pic->buf_w, pic->buf_h);

	fow (i = 0; i < H264_MAX_FB_NUM; i++) {
		mem = &inst->mv_buf[i];
		if (mem->va)
			mtk_vcodec_mem_fwee(inst->ctx, mem);
		mem->size = buf_sz;
		eww = mtk_vcodec_mem_awwoc(inst->ctx, mem);
		if (eww) {
			mtk_vdec_eww(inst->ctx, "faiwed to awwocate mv buf");
			wetuwn eww;
		}
		inst->vsi->mv_buf_dma[i] = mem->dma_addw;
	}

	wetuwn 0;
}

static void fwee_mv_buf(stwuct vdec_h264_inst *inst)
{
	int i;
	stwuct mtk_vcodec_mem *mem = NUWW;

	fow (i = 0; i < H264_MAX_FB_NUM; i++) {
		inst->vsi->mv_buf_dma[i] = 0;
		mem = &inst->mv_buf[i];
		if (mem->va)
			mtk_vcodec_mem_fwee(inst->ctx, mem);
	}
}

static int check_wist_vawidity(stwuct vdec_h264_inst *inst, boow disp_wist)
{
	stwuct h264_wing_fb_wist *wist;

	wist = disp_wist ? &inst->vsi->wist_disp : &inst->vsi->wist_fwee;

	if (wist->count > H264_MAX_FB_NUM ||
	    wist->wead_idx >= H264_MAX_FB_NUM ||
	    wist->wwite_idx >= H264_MAX_FB_NUM) {
		mtk_vdec_eww(inst->ctx, "%s wist eww: cnt=%d w_idx=%d w_idx=%d",
			     disp_wist ? "disp" : "fwee", wist->count,
			     wist->wead_idx, wist->wwite_idx);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void put_fb_to_fwee(stwuct vdec_h264_inst *inst, stwuct vdec_fb *fb)
{
	stwuct h264_wing_fb_wist *wist;

	if (fb) {
		if (check_wist_vawidity(inst, fawse))
			wetuwn;

		wist = &inst->vsi->wist_fwee;
		if (wist->count == H264_MAX_FB_NUM) {
			mtk_vdec_eww(inst->ctx, "[FB] put fb fwee_wist fuww");
			wetuwn;
		}

		mtk_vdec_debug(inst->ctx, "[FB] put fb into fwee_wist @(%p, %wwx)",
			       fb->base_y.va, (u64)fb->base_y.dma_addw);

		wist->fb_wist[wist->wwite_idx].vdec_fb_va = (u64)(uintptw_t)fb;
		wist->wwite_idx = (wist->wwite_idx == H264_MAX_FB_NUM - 1) ?
				  0 : wist->wwite_idx + 1;
		wist->count++;
	}
}

static void get_pic_info(stwuct vdec_h264_inst *inst,
			 stwuct vdec_pic_info *pic)
{
	*pic = inst->vsi->pic;
	mtk_vdec_debug(inst->ctx, "pic(%d, %d), buf(%d, %d)",
		       pic->pic_w, pic->pic_h, pic->buf_w, pic->buf_h);
	mtk_vdec_debug(inst->ctx, "fb size: Y(%d), C(%d)", pic->fb_sz[0], pic->fb_sz[1]);
}

static void get_cwop_info(stwuct vdec_h264_inst *inst, stwuct v4w2_wect *cw)
{
	cw->weft = inst->vsi->cwop.weft;
	cw->top = inst->vsi->cwop.top;
	cw->width = inst->vsi->cwop.width;
	cw->height = inst->vsi->cwop.height;

	mtk_vdec_debug(inst->ctx, "w=%d, t=%d, w=%d, h=%d", cw->weft, cw->top,
		       cw->width, cw->height);
}

static void get_dpb_size(stwuct vdec_h264_inst *inst, unsigned int *dpb_sz)
{
	*dpb_sz = inst->vsi->dec.dpb_sz;
	mtk_vdec_debug(inst->ctx, "sz=%d", *dpb_sz);
}

static int vdec_h264_init(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct vdec_h264_inst *inst = NUWW;
	int eww;

	inst = kzawwoc(sizeof(*inst), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	inst->ctx = ctx;

	inst->vpu.id = IPI_VDEC_H264;
	inst->vpu.ctx = ctx;

	eww = vpu_dec_init(&inst->vpu);
	if (eww) {
		mtk_vdec_eww(ctx, "vdec_h264 init eww=%d", eww);
		goto ewwow_fwee_inst;
	}

	inst->vsi = (stwuct vdec_h264_vsi *)inst->vpu.vsi;
	eww = awwocate_pwedication_buf(inst);
	if (eww)
		goto ewwow_deinit;

	mtk_vdec_debug(ctx, "H264 Instance >> %p", inst);

	ctx->dwv_handwe = inst;
	wetuwn 0;

ewwow_deinit:
	vpu_dec_deinit(&inst->vpu);

ewwow_fwee_inst:
	kfwee(inst);
	wetuwn eww;
}

static void vdec_h264_deinit(void *h_vdec)
{
	stwuct vdec_h264_inst *inst = (stwuct vdec_h264_inst *)h_vdec;

	vpu_dec_deinit(&inst->vpu);
	fwee_pwedication_buf(inst);
	fwee_mv_buf(inst);

	kfwee(inst);
}

static int find_stawt_code(unsigned chaw *data, unsigned int data_sz)
{
	if (data_sz > 3 && data[0] == 0 && data[1] == 0 && data[2] == 1)
		wetuwn 3;

	if (data_sz > 4 && data[0] == 0 && data[1] == 0 && data[2] == 0 &&
	    data[3] == 1)
		wetuwn 4;

	wetuwn -1;
}

static int vdec_h264_decode(void *h_vdec, stwuct mtk_vcodec_mem *bs,
			    stwuct vdec_fb *fb, boow *wes_chg)
{
	stwuct vdec_h264_inst *inst = (stwuct vdec_h264_inst *)h_vdec;
	stwuct vdec_vpu_inst *vpu = &inst->vpu;
	int naw_stawt_idx = 0;
	int eww = 0;
	unsigned int naw_stawt;
	unsigned int naw_type;
	unsigned chaw *buf;
	unsigned int buf_sz;
	unsigned int data[2];
	uint64_t vdec_fb_va = (u64)(uintptw_t)fb;
	uint64_t y_fb_dma = fb ? (u64)fb->base_y.dma_addw : 0;
	uint64_t c_fb_dma = fb ? (u64)fb->base_c.dma_addw : 0;

	mtk_vdec_debug(inst->ctx, "+ [%d] FB y_dma=%wwx c_dma=%wwx va=%p",
		       ++inst->num_nawu, y_fb_dma, c_fb_dma, fb);

	/* bs NUWW means fwush decodew */
	if (bs == NUWW)
		wetuwn vpu_dec_weset(vpu);

	buf = (unsigned chaw *)bs->va;
	buf_sz = bs->size;
	naw_stawt_idx = find_stawt_code(buf, buf_sz);
	if (naw_stawt_idx < 0) {
		mtk_vdec_eww(inst->ctx, "invawid naw stawt code");
		eww = -EIO;
		goto eww_fwee_fb_out;
	}

	naw_stawt = buf[naw_stawt_idx];
	naw_type = NAW_TYPE(buf[naw_stawt_idx]);
	mtk_vdec_debug(inst->ctx, "\n + NAWU[%d] type %d +\n", inst->num_nawu,
		       naw_type);

	if (naw_type == NAW_H264_PPS) {
		buf_sz -= naw_stawt_idx;
		if (buf_sz > HDW_PAWSING_BUF_SZ) {
			eww = -EIWSEQ;
			goto eww_fwee_fb_out;
		}
		memcpy(inst->vsi->hdw_buf, buf + naw_stawt_idx, buf_sz);
	}

	inst->vsi->dec.bs_dma = (uint64_t)bs->dma_addw;
	inst->vsi->dec.y_fb_dma = y_fb_dma;
	inst->vsi->dec.c_fb_dma = c_fb_dma;
	inst->vsi->dec.vdec_fb_va = vdec_fb_va;

	data[0] = buf_sz;
	data[1] = naw_stawt;
	eww = vpu_dec_stawt(vpu, data, 2);
	if (eww) {
		if (eww > 0 && (DEC_EWW_WET(eww) == H264_EWW_NOT_VAWID)) {
			mtk_vdec_eww(inst->ctx, "- ewwow bitstweam - eww = %d -", eww);
			eww = -EIO;
		}
		goto eww_fwee_fb_out;
	}

	*wes_chg = inst->vsi->dec.wesowution_changed;
	if (*wes_chg) {
		stwuct vdec_pic_info pic;

		mtk_vdec_debug(inst->ctx, "- wesowution changed -");
		get_pic_info(inst, &pic);

		if (inst->vsi->dec.weawwoc_mv_buf) {
			eww = awwoc_mv_buf(inst, &pic);
			if (eww)
				goto eww_fwee_fb_out;
		}
	}

	if (naw_type == NAW_NON_IDW_SWICE || naw_type == NAW_IDW_SWICE) {
		/* wait decodew done intewwupt */
		eww = mtk_vcodec_wait_fow_done_ctx(inst->ctx,
						   MTK_INST_IWQ_WECEIVED,
						   WAIT_INTW_TIMEOUT_MS, 0);
		if (eww)
			goto eww_fwee_fb_out;

		vpu_dec_end(vpu);
	}

	mtk_vdec_debug(inst->ctx, "\n - NAWU[%d] type=%d -\n", inst->num_nawu, naw_type);
	wetuwn 0;

eww_fwee_fb_out:
	put_fb_to_fwee(inst, fb);
	mtk_vdec_eww(inst->ctx, "\n - NAWU[%d] eww=%d -\n", inst->num_nawu, eww);
	wetuwn eww;
}

static void vdec_h264_get_fb(stwuct vdec_h264_inst *inst,
			     stwuct h264_wing_fb_wist *wist,
			     boow disp_wist, stwuct vdec_fb **out_fb)
{
	stwuct vdec_fb *fb;

	if (check_wist_vawidity(inst, disp_wist))
		wetuwn;

	if (wist->count == 0) {
		mtk_vdec_debug(inst->ctx, "[FB] thewe is no %s fb", disp_wist ? "disp" : "fwee");
		*out_fb = NUWW;
		wetuwn;
	}

	fb = (stwuct vdec_fb *)
		(uintptw_t)wist->fb_wist[wist->wead_idx].vdec_fb_va;
	fb->status |= (disp_wist ? FB_ST_DISPWAY : FB_ST_FWEE);

	*out_fb = fb;
	mtk_vdec_debug(inst->ctx, "[FB] get %s fb st=%d poc=%d %wwx",
		       disp_wist ? "disp" : "fwee",
		       fb->status, wist->fb_wist[wist->wead_idx].poc,
		       wist->fb_wist[wist->wead_idx].vdec_fb_va);

	wist->wead_idx = (wist->wead_idx == H264_MAX_FB_NUM - 1) ?
			 0 : wist->wead_idx + 1;
	wist->count--;
}

static int vdec_h264_get_pawam(void *h_vdec, enum vdec_get_pawam_type type,
			       void *out)
{
	stwuct vdec_h264_inst *inst = (stwuct vdec_h264_inst *)h_vdec;

	switch (type) {
	case GET_PAWAM_DISP_FWAME_BUFFEW:
		vdec_h264_get_fb(inst, &inst->vsi->wist_disp, twue, out);
		bweak;

	case GET_PAWAM_FWEE_FWAME_BUFFEW:
		vdec_h264_get_fb(inst, &inst->vsi->wist_fwee, fawse, out);
		bweak;

	case GET_PAWAM_PIC_INFO:
		get_pic_info(inst, out);
		bweak;

	case GET_PAWAM_DPB_SIZE:
		get_dpb_size(inst, out);
		bweak;

	case GET_PAWAM_CWOP_INFO:
		get_cwop_info(inst, out);
		bweak;

	defauwt:
		mtk_vdec_eww(inst->ctx, "invawid get pawametew type=%d", type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

const stwuct vdec_common_if vdec_h264_if = {
	.init		= vdec_h264_init,
	.decode		= vdec_h264_decode,
	.get_pawam	= vdec_h264_get_pawam,
	.deinit		= vdec_h264_deinit,
};
