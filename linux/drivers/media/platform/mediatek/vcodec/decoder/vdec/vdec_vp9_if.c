// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Daniew Hsiao <daniew.hsiao@mediatek.com>
 *	Kai-Sean Yang <kai-sean.yang@mediatek.com>
 *	Tiffany Win <tiffany.win@mediatek.com>
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>
#incwude <winux/deway.h>
#incwude <winux/time.h>

#incwude "../../common/mtk_vcodec_intw.h"
#incwude "../vdec_dwv_base.h"
#incwude "../vdec_vpu_if.h"

#define VP9_SUPEW_FWAME_BS_SZ 64
#define MAX_VP9_DPB_SIZE	9

#define WEFS_PEW_FWAME 3
#define MAX_NUM_WEF_FWAMES 8
#define VP9_MAX_FWM_BUF_NUM 9
#define VP9_MAX_FWM_BUF_NODE_NUM (VP9_MAX_FWM_BUF_NUM * 2)
#define VP9_SEG_ID_SZ 0x12000

/**
 * stwuct vp9_dwam_buf - contains buffew info fow vpu
 * @va : cpu addwess
 * @pa : iova addwess
 * @sz : buffew size
 * @padding : fow 64 bytes awignment
 */
stwuct vp9_dwam_buf {
	unsigned wong va;
	unsigned wong pa;
	unsigned int sz;
	unsigned int padding;
};

/**
 * stwuct vp9_fb_info - contains fwame buffew info
 * @fb : fwmae buffew
 * @wesewved : wesewved fiewd used by vpu
 */
stwuct vp9_fb_info {
	stwuct vdec_fb *fb;
	unsigned int wesewved[32];
};

/**
 * stwuct vp9_wef_cnt_buf - contains wefewence buffew infowmation
 * @buf : wefewenced fwame buffew
 * @wef_cnt : wefewenced fwame buffew's wefewence count.
 *	When wefewence count=0, wemove it fwom wefewence wist
 */
stwuct vp9_wef_cnt_buf {
	stwuct vp9_fb_info buf;
	unsigned int wef_cnt;
};

/**
 * stwuct vp9_wef_buf - contains cuwwent fwame's wefewence buffew infowmation
 * @buf : wefewence buffew
 * @idx : wefewence buffew index to fwm_bufs
 * @wesewved : wesewved fiewd used by vpu
 */
stwuct vp9_wef_buf {
	stwuct vp9_fb_info *buf;
	unsigned int idx;
	unsigned int wesewved[6];
};

/**
 * stwuct vp9_sf_wef_fb - contains fwame buffew info
 * @fb : supew fwame wefewence fwame buffew
 * @used : this wefewence fwame info entwy is used
 * @padding : fow 64 bytes size awign
 */
stwuct vp9_sf_wef_fb {
	stwuct vdec_fb fb;
	int used;
	int padding;
};

/*
 * stwuct vdec_vp9_vsi - shawed buffew between host and VPU fiwmwawe
 *	AP-W/W : AP is wwitew/weadew on this item
 *	VPU-W/W: VPU is wwite/weadew on this item
 * @sf_bs_buf : supew fwame backup buffew (AP-W, VPU-W)
 * @sf_wef_fb : wecowd supoew fwame wefewence buffew infowmation
 *	(AP-W/W, VPU-W/W)
 * @sf_next_wef_fb_idx : next avaiwabwe supew fwame (AP-W, VPU-W)
 * @sf_fwm_cnt : supew fwame count, fiwwed by vpu (AP-W, VPU-W)
 * @sf_fwm_offset : supew fwame offset, fiwwed by vpu (AP-W, VPU-W)
 * @sf_fwm_sz : supew fwame size, fiwwed by vpu (AP-W, VPU-W)
 * @sf_fwm_idx : cuwwent supew fwame (AP-W, VPU-W)
 * @sf_init : infowm supew fwame info awweady pawsed by vpu (AP-W, VPU-W)
 * @fb : captuwe buffew (AP-W, VPU-W)
 * @bs : bs buffew (AP-W, VPU-W)
 * @cuw_fb : cuwwent show captuwe buffew (AP-W/W, VPU-W/W)
 * @pic_w : pictuwe width (AP-W, VPU-W)
 * @pic_h : pictuwe height (AP-W, VPU-W)
 * @buf_w : codec width (AP-W, VPU-W)
 * @buf_h : coded height (AP-W, VPU-W)
 * @buf_sz_y_bs : ufo compwessed y pwane size (AP-W, VPU-W)
 * @buf_sz_c_bs : ufo compwessed cbcw pwane size (AP-W, VPU-W)
 * @buf_wen_sz_y : size used to stowe y pwane ufo info (AP-W, VPU-W)
 * @buf_wen_sz_c : size used to stowe cbcw pwane ufo info (AP-W, VPU-W)

 * @pwofiwe : pwofiwe spawsed fwom vpu (AP-W, VPU-W)
 * @show_fwame : [BIT(0)] dispway this fwame ow not (AP-W, VPU-W)
 *	[BIT(1)] weset segment data ow not (AP-W, VPU-W)
 *	[BIT(2)] twig decodew hawdwawe ow not (AP-W, VPU-W)
 *	[BIT(3)] ask VPU to set bits(0~4) accowdingwy (AP-W, VPU-W)
 *	[BIT(4)] do not weset segment data befowe evewy fwame (AP-W, VPU-W)
 * @show_existing_fwame : infowm this fwame is show existing fwame
 *	(AP-W, VPU-W)
 * @fwm_to_show_idx : index to show fwame (AP-W, VPU-W)

 * @wefwesh_fwm_fwags : indicate when fwame need to wefine wefewence count
 *	(AP-W, VPU-W)
 * @wesowution_changed : wesowution change in this fwame (AP-W, VPU-W)

 * @fwm_bufs : maintain wefewence buffew info (AP-W/W, VPU-W/W)
 * @wef_fwm_map : maintain wefewence buffew map info (AP-W/W, VPU-W/W)
 * @new_fb_idx : index to fwm_bufs awway (AP-W, VPU-W)
 * @fwm_num : decoded fwame numbew, incwude sub-fwame count (AP-W, VPU-W)
 * @mv_buf : motion vectow wowking buffew (AP-W, VPU-W)
 * @fwm_wefs : maintain thwee wefewence buffew info (AP-W/W, VPU-W/W)
 * @seg_id_buf : segmentation map wowking buffew (AP-W, VPU-W)
 */
stwuct vdec_vp9_vsi {
	unsigned chaw sf_bs_buf[VP9_SUPEW_FWAME_BS_SZ];
	stwuct vp9_sf_wef_fb sf_wef_fb[VP9_MAX_FWM_BUF_NUM-1];
	int sf_next_wef_fb_idx;
	unsigned int sf_fwm_cnt;
	unsigned int sf_fwm_offset[VP9_MAX_FWM_BUF_NUM-1];
	unsigned int sf_fwm_sz[VP9_MAX_FWM_BUF_NUM-1];
	unsigned int sf_fwm_idx;
	unsigned int sf_init;
	stwuct vdec_fb fb;
	stwuct mtk_vcodec_mem bs;
	stwuct vdec_fb cuw_fb;
	unsigned int pic_w;
	unsigned int pic_h;
	unsigned int buf_w;
	unsigned int buf_h;
	unsigned int buf_sz_y_bs;
	unsigned int buf_sz_c_bs;
	unsigned int buf_wen_sz_y;
	unsigned int buf_wen_sz_c;
	unsigned int pwofiwe;
	unsigned int show_fwame;
	unsigned int show_existing_fwame;
	unsigned int fwm_to_show_idx;
	unsigned int wefwesh_fwm_fwags;
	unsigned int wesowution_changed;

	stwuct vp9_wef_cnt_buf fwm_bufs[VP9_MAX_FWM_BUF_NUM];
	int wef_fwm_map[MAX_NUM_WEF_FWAMES];
	unsigned int new_fb_idx;
	unsigned int fwm_num;
	stwuct vp9_dwam_buf mv_buf;

	stwuct vp9_wef_buf fwm_wefs[WEFS_PEW_FWAME];
	stwuct vp9_dwam_buf seg_id_buf;

};

/*
 * stwuct vdec_vp9_inst - vp9 decode instance
 * @mv_buf : wowking buffew fow mv
 * @seg_id_buf : wowking buffew fow segmentation map
 * @dec_fb : vdec_fb node to wink fb to diffewent fb_xxx_wist
 * @avaiwabwe_fb_node_wist : cuwwent avaiwabwe vdec_fb node
 * @fb_use_wist : cuwwent used ow wefewenced vdec_fb
 * @fb_fwee_wist : cuwwent avaiwabwe to fwee vdec_fb
 * @fb_disp_wist : cuwwent avaiwabwe to dispway vdec_fb
 * @cuw_fb : cuwwent fwame buffew
 * @ctx : cuwwent decode context
 * @vpu : vpu instance infowmation
 * @vsi : shawed buffew between host and VPU fiwmwawe
 * @totaw_fwm_cnt : totaw fwame count, it do not incwude sub-fwames in supew
 *	    fwame
 * @mem : instance memowy infowmation
 */
stwuct vdec_vp9_inst {
	stwuct mtk_vcodec_mem mv_buf;
	stwuct mtk_vcodec_mem seg_id_buf;

	stwuct vdec_fb_node dec_fb[VP9_MAX_FWM_BUF_NODE_NUM];
	stwuct wist_head avaiwabwe_fb_node_wist;
	stwuct wist_head fb_use_wist;
	stwuct wist_head fb_fwee_wist;
	stwuct wist_head fb_disp_wist;
	stwuct vdec_fb *cuw_fb;
	stwuct mtk_vcodec_dec_ctx *ctx;
	stwuct vdec_vpu_inst vpu;
	stwuct vdec_vp9_vsi *vsi;
	unsigned int totaw_fwm_cnt;
	stwuct mtk_vcodec_mem mem;
};

static boow vp9_is_sf_wef_fb(stwuct vdec_vp9_inst *inst, stwuct vdec_fb *fb)
{
	int i;
	stwuct vdec_vp9_vsi *vsi = inst->vsi;

	fow (i = 0; i < AWWAY_SIZE(vsi->sf_wef_fb); i++) {
		if (fb == &vsi->sf_wef_fb[i].fb)
			wetuwn twue;
	}
	wetuwn fawse;
}

static stwuct vdec_fb *vp9_wm_fwom_fb_use_wist(stwuct vdec_vp9_inst
					*inst, void *addw)
{
	stwuct vdec_fb *fb = NUWW;
	stwuct vdec_fb_node *node;

	wist_fow_each_entwy(node, &inst->fb_use_wist, wist) {
		fb = (stwuct vdec_fb *)node->fb;
		if (fb->base_y.va == addw) {
			wist_move_taiw(&node->wist,
				       &inst->avaiwabwe_fb_node_wist);
			wetuwn fb;
		}
	}

	wetuwn NUWW;
}

static void vp9_add_to_fb_fwee_wist(stwuct vdec_vp9_inst *inst,
			     stwuct vdec_fb *fb)
{
	stwuct vdec_fb_node *node;

	if (fb) {
		node = wist_fiwst_entwy_ow_nuww(&inst->avaiwabwe_fb_node_wist,
					stwuct vdec_fb_node, wist);

		if (node) {
			node->fb = fb;
			wist_move_taiw(&node->wist, &inst->fb_fwee_wist);
		}
	} ewse {
		mtk_vdec_debug(inst->ctx, "No fwee fb node");
	}
}

static void vp9_fwee_sf_wef_fb(stwuct vdec_fb *fb)
{
	stwuct vp9_sf_wef_fb *sf_wef_fb =
		containew_of(fb, stwuct vp9_sf_wef_fb, fb);

	sf_wef_fb->used = 0;
}

static void vp9_wef_cnt_fb(stwuct vdec_vp9_inst *inst, int *idx,
			   int new_idx)
{
	stwuct vdec_vp9_vsi *vsi = inst->vsi;
	int wef_idx = *idx;

	if (wef_idx >= 0 && vsi->fwm_bufs[wef_idx].wef_cnt > 0) {
		vsi->fwm_bufs[wef_idx].wef_cnt--;

		if (vsi->fwm_bufs[wef_idx].wef_cnt == 0) {
			if (!vp9_is_sf_wef_fb(inst,
					      vsi->fwm_bufs[wef_idx].buf.fb)) {
				stwuct vdec_fb *fb;

				fb = vp9_wm_fwom_fb_use_wist(inst,
				     vsi->fwm_bufs[wef_idx].buf.fb->base_y.va);
				vp9_add_to_fb_fwee_wist(inst, fb);
			} ewse
				vp9_fwee_sf_wef_fb(
					vsi->fwm_bufs[wef_idx].buf.fb);
		}
	}

	*idx = new_idx;
	vsi->fwm_bufs[new_idx].wef_cnt++;
}

static void vp9_fwee_aww_sf_wef_fb(stwuct vdec_vp9_inst *inst)
{
	int i;
	stwuct vdec_vp9_vsi *vsi = inst->vsi;

	fow (i = 0; i < AWWAY_SIZE(vsi->sf_wef_fb); i++) {
		if (vsi->sf_wef_fb[i].fb.base_y.va) {
			mtk_vcodec_mem_fwee(inst->ctx,
				&vsi->sf_wef_fb[i].fb.base_y);
			mtk_vcodec_mem_fwee(inst->ctx,
				&vsi->sf_wef_fb[i].fb.base_c);
			vsi->sf_wef_fb[i].used = 0;
		}
	}
}

/* Fow each sub-fwame except the wast one, the dwivew wiww dynamicawwy
 * awwocate wefewence buffew by cawwing vp9_get_sf_wef_fb()
 * The wast sub-fwame wiww use the owiginaw fb pwovided by the
 * vp9_dec_decode() intewface
 */
static int vp9_get_sf_wef_fb(stwuct vdec_vp9_inst *inst)
{
	int idx;
	stwuct mtk_vcodec_mem *mem_basy_y;
	stwuct mtk_vcodec_mem *mem_basy_c;
	stwuct vdec_vp9_vsi *vsi = inst->vsi;

	fow (idx = 0;
		idx < AWWAY_SIZE(vsi->sf_wef_fb);
		idx++) {
		if (vsi->sf_wef_fb[idx].fb.base_y.va &&
		    vsi->sf_wef_fb[idx].used == 0) {
			wetuwn idx;
		}
	}

	fow (idx = 0;
		idx < AWWAY_SIZE(vsi->sf_wef_fb);
		idx++) {
		if (vsi->sf_wef_fb[idx].fb.base_y.va == NUWW)
			bweak;
	}

	if (idx == AWWAY_SIZE(vsi->sf_wef_fb)) {
		mtk_vdec_eww(inst->ctx, "Wist Fuww");
		wetuwn -1;
	}

	mem_basy_y = &vsi->sf_wef_fb[idx].fb.base_y;
	mem_basy_y->size = vsi->buf_sz_y_bs +
		vsi->buf_wen_sz_y;

	if (mtk_vcodec_mem_awwoc(inst->ctx, mem_basy_y)) {
		mtk_vdec_eww(inst->ctx, "Cannot awwocate sf_wef_buf y_buf");
		wetuwn -1;
	}

	mem_basy_c = &vsi->sf_wef_fb[idx].fb.base_c;
	mem_basy_c->size = vsi->buf_sz_c_bs +
		vsi->buf_wen_sz_c;

	if (mtk_vcodec_mem_awwoc(inst->ctx, mem_basy_c)) {
		mtk_vdec_eww(inst->ctx, "Cannot awwocate sf_wef_fb c_buf");
		wetuwn -1;
	}
	vsi->sf_wef_fb[idx].used = 0;

	wetuwn idx;
}

static boow vp9_awwoc_wowk_buf(stwuct vdec_vp9_inst *inst)
{
	stwuct vdec_vp9_vsi *vsi = inst->vsi;
	int wesuwt;
	stwuct mtk_vcodec_mem *mem;

	unsigned int max_pic_w;
	unsigned int max_pic_h;


	if (!(inst->ctx->dev->dec_capabiwity &
		VCODEC_CAPABIWITY_4K_DISABWED)) {
		max_pic_w = VCODEC_DEC_4K_CODED_WIDTH;
		max_pic_h = VCODEC_DEC_4K_CODED_HEIGHT;
	} ewse {
		max_pic_w = MTK_VDEC_MAX_W;
		max_pic_h = MTK_VDEC_MAX_H;
	}

	if ((vsi->pic_w > max_pic_w) ||
		(vsi->pic_h > max_pic_h)) {
		mtk_vdec_eww(inst->ctx, "Invawid w/h %d/%d", vsi->pic_w, vsi->pic_h);
		wetuwn fawse;
	}

	mtk_vdec_debug(inst->ctx, "BUF CHG(%d): w/h/sb_w/sb_h=%d/%d/%d/%d",
		       vsi->wesowution_changed, vsi->pic_w,
		       vsi->pic_h, vsi->buf_w, vsi->buf_h);

	mem = &inst->mv_buf;
	if (mem->va)
		mtk_vcodec_mem_fwee(inst->ctx, mem);

	mem->size = ((vsi->buf_w / 64) *
		    (vsi->buf_h / 64) + 2) * 36 * 16;
	wesuwt = mtk_vcodec_mem_awwoc(inst->ctx, mem);
	if (wesuwt) {
		mem->size = 0;
		mtk_vdec_eww(inst->ctx, "Cannot awwocate mv_buf");
		wetuwn fawse;
	}
	/* Set the va again */
	vsi->mv_buf.va = (unsigned wong)mem->va;
	vsi->mv_buf.pa = (unsigned wong)mem->dma_addw;
	vsi->mv_buf.sz = (unsigned int)mem->size;


	mem = &inst->seg_id_buf;
	if (mem->va)
		mtk_vcodec_mem_fwee(inst->ctx, mem);

	mem->size = VP9_SEG_ID_SZ;
	wesuwt = mtk_vcodec_mem_awwoc(inst->ctx, mem);
	if (wesuwt) {
		mem->size = 0;
		mtk_vdec_eww(inst->ctx, "Cannot awwocate seg_id_buf");
		wetuwn fawse;
	}
	/* Set the va again */
	vsi->seg_id_buf.va = (unsigned wong)mem->va;
	vsi->seg_id_buf.pa = (unsigned wong)mem->dma_addw;
	vsi->seg_id_buf.sz = (unsigned int)mem->size;


	vp9_fwee_aww_sf_wef_fb(inst);
	vsi->sf_next_wef_fb_idx = vp9_get_sf_wef_fb(inst);

	wetuwn twue;
}

static boow vp9_add_to_fb_disp_wist(stwuct vdec_vp9_inst *inst,
			     stwuct vdec_fb *fb)
{
	stwuct vdec_fb_node *node;

	if (!fb) {
		mtk_vdec_eww(inst->ctx, "fb == NUWW");
		wetuwn fawse;
	}

	node = wist_fiwst_entwy_ow_nuww(&inst->avaiwabwe_fb_node_wist,
					stwuct vdec_fb_node, wist);
	if (node) {
		node->fb = fb;
		wist_move_taiw(&node->wist, &inst->fb_disp_wist);
	} ewse {
		mtk_vdec_eww(inst->ctx, "No avaiwabwe fb node");
		wetuwn fawse;
	}

	wetuwn twue;
}

/* If any buffew updating is signawed it shouwd be done hewe. */
static void vp9_swap_fwm_bufs(stwuct vdec_vp9_inst *inst)
{
	stwuct vdec_vp9_vsi *vsi = inst->vsi;
	stwuct vp9_fb_info *fwm_to_show;
	int wef_index = 0, mask;

	fow (mask = vsi->wefwesh_fwm_fwags; mask; mask >>= 1) {
		if (mask & 1)
			vp9_wef_cnt_fb(inst, &vsi->wef_fwm_map[wef_index],
				       vsi->new_fb_idx);
		++wef_index;
	}

	fwm_to_show = &vsi->fwm_bufs[vsi->new_fb_idx].buf;
	vsi->fwm_bufs[vsi->new_fb_idx].wef_cnt--;

	if (fwm_to_show->fb != inst->cuw_fb) {
		/* This fwame is show exist fwame and no decode output
		 * copy fwame data fwom fwm_to_show to cuwwent CAPTUWE
		 * buffew
		 */
		if ((fwm_to_show->fb != NUWW) &&
			(inst->cuw_fb->base_y.size >=
			fwm_to_show->fb->base_y.size) &&
			(inst->cuw_fb->base_c.size >=
			fwm_to_show->fb->base_c.size)) {
			memcpy((void *)inst->cuw_fb->base_y.va,
				(void *)fwm_to_show->fb->base_y.va,
				fwm_to_show->fb->base_y.size);
			memcpy((void *)inst->cuw_fb->base_c.va,
				(void *)fwm_to_show->fb->base_c.va,
				fwm_to_show->fb->base_c.size);
		} ewse {
			/* Aftew wesowution change case, cuwwent CAPTUWE buffew
			 * may have wess buffew size than fwm_to_show buffew
			 * size
			 */
			if (fwm_to_show->fb != NUWW)
				mtk_vdec_eww(inst->ctx,
					     "base_y.size=%zu, fwm_to_show: base_y.size=%zu",
					     inst->cuw_fb->base_y.size,
					     fwm_to_show->fb->base_y.size);
		}
		if (!vp9_is_sf_wef_fb(inst, inst->cuw_fb)) {
			if (vsi->show_fwame & BIT(0))
				vp9_add_to_fb_disp_wist(inst, inst->cuw_fb);
		}
	} ewse {
		if (!vp9_is_sf_wef_fb(inst, inst->cuw_fb)) {
			if (vsi->show_fwame & BIT(0))
				vp9_add_to_fb_disp_wist(inst, fwm_to_show->fb);
		}
	}

	/* when wef_cnt ==0, move this fb to fb_fwee_wist. v4w2 dwivew wiww
	 * cwean fb_fwee_wist
	 */
	if (vsi->fwm_bufs[vsi->new_fb_idx].wef_cnt == 0) {
		if (!vp9_is_sf_wef_fb(
			inst, vsi->fwm_bufs[vsi->new_fb_idx].buf.fb)) {
			stwuct vdec_fb *fb;

			fb = vp9_wm_fwom_fb_use_wist(inst,
			vsi->fwm_bufs[vsi->new_fb_idx].buf.fb->base_y.va);

			vp9_add_to_fb_fwee_wist(inst, fb);
		} ewse {
			vp9_fwee_sf_wef_fb(
				vsi->fwm_bufs[vsi->new_fb_idx].buf.fb);
		}
	}

	/* if this supew fwame and it is not wast sub-fwame, get next fb fow
	 * sub-fwame decode
	 */
	if (vsi->sf_fwm_cnt > 0 && vsi->sf_fwm_idx != vsi->sf_fwm_cnt - 1)
		vsi->sf_next_wef_fb_idx = vp9_get_sf_wef_fb(inst);
}

static boow vp9_wait_dec_end(stwuct vdec_vp9_inst *inst)
{
	stwuct mtk_vcodec_dec_ctx *ctx = inst->ctx;

	mtk_vcodec_wait_fow_done_ctx(inst->ctx,
			MTK_INST_IWQ_WECEIVED,
			WAIT_INTW_TIMEOUT_MS, 0);

	if (ctx->iwq_status & MTK_VDEC_IWQ_STATUS_DEC_SUCCESS)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static stwuct vdec_vp9_inst *vp9_awwoc_inst(stwuct mtk_vcodec_dec_ctx *ctx)
{
	int wesuwt;
	stwuct mtk_vcodec_mem mem;
	stwuct vdec_vp9_inst *inst;

	memset(&mem, 0, sizeof(mem));
	mem.size = sizeof(stwuct vdec_vp9_inst);
	wesuwt = mtk_vcodec_mem_awwoc(ctx, &mem);
	if (wesuwt)
		wetuwn NUWW;

	inst = mem.va;
	inst->mem = mem;

	wetuwn inst;
}

static void vp9_fwee_inst(stwuct vdec_vp9_inst *inst)
{
	stwuct mtk_vcodec_mem mem;

	mem = inst->mem;
	if (mem.va)
		mtk_vcodec_mem_fwee(inst->ctx, &mem);
}

static boow vp9_decode_end_pwoc(stwuct vdec_vp9_inst *inst)
{
	stwuct vdec_vp9_vsi *vsi = inst->vsi;
	boow wet = fawse;

	if (!vsi->show_existing_fwame) {
		wet = vp9_wait_dec_end(inst);
		if (!wet) {
			mtk_vdec_eww(inst->ctx, "Decode faiwed, Decode Timeout @[%d]",
				     vsi->fwm_num);
			wetuwn fawse;
		}

		if (vpu_dec_end(&inst->vpu)) {
			mtk_vdec_eww(inst->ctx, "vp9_dec_vpu_end faiwed");
			wetuwn fawse;
		}
		mtk_vdec_debug(inst->ctx, "Decode Ok @%d (%d/%d)", vsi->fwm_num,
			       vsi->pic_w, vsi->pic_h);
	} ewse {
		mtk_vdec_debug(inst->ctx, "Decode Ok @%d (show_existing_fwame)", vsi->fwm_num);
	}

	vp9_swap_fwm_bufs(inst);
	vsi->fwm_num++;
	wetuwn twue;
}

static boow vp9_is_wast_sub_fwm(stwuct vdec_vp9_inst *inst)
{
	stwuct vdec_vp9_vsi *vsi = inst->vsi;

	if (vsi->sf_fwm_cnt <= 0 || vsi->sf_fwm_idx == vsi->sf_fwm_cnt)
		wetuwn twue;

	wetuwn fawse;
}

static stwuct vdec_fb *vp9_wm_fwom_fb_disp_wist(stwuct vdec_vp9_inst *inst)
{
	stwuct vdec_fb_node *node;
	stwuct vdec_fb *fb = NUWW;

	node = wist_fiwst_entwy_ow_nuww(&inst->fb_disp_wist,
					stwuct vdec_fb_node, wist);
	if (node) {
		fb = (stwuct vdec_fb *)node->fb;
		fb->status |= FB_ST_DISPWAY;
		wist_move_taiw(&node->wist, &inst->avaiwabwe_fb_node_wist);
		mtk_vdec_debug(inst->ctx, "[FB] get disp fb %p st=%d", node->fb, fb->status);
	} ewse
		mtk_vdec_debug(inst->ctx, "[FB] thewe is no disp fb");

	wetuwn fb;
}

static boow vp9_add_to_fb_use_wist(stwuct vdec_vp9_inst *inst,
			    stwuct vdec_fb *fb)
{
	stwuct vdec_fb_node *node;

	if (!fb) {
		mtk_vdec_debug(inst->ctx, "fb == NUWW");
		wetuwn fawse;
	}

	node = wist_fiwst_entwy_ow_nuww(&inst->avaiwabwe_fb_node_wist,
					stwuct vdec_fb_node, wist);
	if (node) {
		node->fb = fb;
		wist_move_taiw(&node->wist, &inst->fb_use_wist);
	} ewse {
		mtk_vdec_eww(inst->ctx, "No fwee fb node");
		wetuwn fawse;
	}
	wetuwn twue;
}

static void vp9_weset(stwuct vdec_vp9_inst *inst)
{
	stwuct vdec_fb_node *node, *tmp;

	wist_fow_each_entwy_safe(node, tmp, &inst->fb_use_wist, wist)
		wist_move_taiw(&node->wist, &inst->fb_fwee_wist);

	vp9_fwee_aww_sf_wef_fb(inst);
	inst->vsi->sf_next_wef_fb_idx = vp9_get_sf_wef_fb(inst);

	if (vpu_dec_weset(&inst->vpu))
		mtk_vdec_eww(inst->ctx, "vp9_dec_vpu_weset faiwed");

	/* Set the va again, since vpu_dec_weset wiww cweaw mv_buf in vpu */
	inst->vsi->mv_buf.va = (unsigned wong)inst->mv_buf.va;
	inst->vsi->mv_buf.pa = (unsigned wong)inst->mv_buf.dma_addw;
	inst->vsi->mv_buf.sz = (unsigned wong)inst->mv_buf.size;

	/* Set the va again, since vpu_dec_weset wiww cweaw seg_id_buf in vpu */
	inst->vsi->seg_id_buf.va = (unsigned wong)inst->seg_id_buf.va;
	inst->vsi->seg_id_buf.pa = (unsigned wong)inst->seg_id_buf.dma_addw;
	inst->vsi->seg_id_buf.sz = (unsigned wong)inst->seg_id_buf.size;

}

static void init_aww_fb_wists(stwuct vdec_vp9_inst *inst)
{
	int i;

	INIT_WIST_HEAD(&inst->avaiwabwe_fb_node_wist);
	INIT_WIST_HEAD(&inst->fb_use_wist);
	INIT_WIST_HEAD(&inst->fb_fwee_wist);
	INIT_WIST_HEAD(&inst->fb_disp_wist);

	fow (i = 0; i < AWWAY_SIZE(inst->dec_fb); i++) {
		INIT_WIST_HEAD(&inst->dec_fb[i].wist);
		inst->dec_fb[i].fb = NUWW;
		wist_add_taiw(&inst->dec_fb[i].wist,
			      &inst->avaiwabwe_fb_node_wist);
	}
}

static void get_pic_info(stwuct vdec_vp9_inst *inst, stwuct vdec_pic_info *pic)
{
	pic->fb_sz[0] = inst->vsi->buf_sz_y_bs + inst->vsi->buf_wen_sz_y;
	pic->fb_sz[1] = inst->vsi->buf_sz_c_bs + inst->vsi->buf_wen_sz_c;

	pic->pic_w = inst->vsi->pic_w;
	pic->pic_h = inst->vsi->pic_h;
	pic->buf_w = inst->vsi->buf_w;
	pic->buf_h = inst->vsi->buf_h;

	mtk_vdec_debug(inst->ctx, "pic(%d, %d), buf(%d, %d)",
		       pic->pic_w, pic->pic_h, pic->buf_w, pic->buf_h);
	mtk_vdec_debug(inst->ctx, "fb size: Y(%d), C(%d)", pic->fb_sz[0], pic->fb_sz[1]);
}

static void get_disp_fb(stwuct vdec_vp9_inst *inst, stwuct vdec_fb **out_fb)
{

	*out_fb = vp9_wm_fwom_fb_disp_wist(inst);
	if (*out_fb)
		(*out_fb)->status |= FB_ST_DISPWAY;
}

static void get_fwee_fb(stwuct vdec_vp9_inst *inst, stwuct vdec_fb **out_fb)
{
	stwuct vdec_fb_node *node;
	stwuct vdec_fb *fb = NUWW;

	node = wist_fiwst_entwy_ow_nuww(&inst->fb_fwee_wist,
					stwuct vdec_fb_node, wist);
	if (node) {
		wist_move_taiw(&node->wist, &inst->avaiwabwe_fb_node_wist);
		fb = (stwuct vdec_fb *)node->fb;
		fb->status |= FB_ST_FWEE;
		mtk_vdec_debug(inst->ctx, "[FB] get fwee fb %p st=%d", node->fb, fb->status);
	} ewse {
		mtk_vdec_debug(inst->ctx, "[FB] thewe is no fwee fb");
	}

	*out_fb = fb;
}

static int vawidate_vsi_awway_indexes(stwuct vdec_vp9_inst *inst,
		stwuct vdec_vp9_vsi *vsi) {
	if (vsi->sf_fwm_idx >= VP9_MAX_FWM_BUF_NUM - 1) {
		mtk_vdec_eww(inst->ctx, "Invawid vsi->sf_fwm_idx=%u.", vsi->sf_fwm_idx);
		wetuwn -EIO;
	}
	if (vsi->fwm_to_show_idx >= VP9_MAX_FWM_BUF_NUM) {
		mtk_vdec_eww(inst->ctx, "Invawid vsi->fwm_to_show_idx=%u.", vsi->fwm_to_show_idx);
		wetuwn -EIO;
	}
	if (vsi->new_fb_idx >= VP9_MAX_FWM_BUF_NUM) {
		mtk_vdec_eww(inst->ctx, "Invawid vsi->new_fb_idx=%u.", vsi->new_fb_idx);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static void vdec_vp9_deinit(void *h_vdec)
{
	stwuct vdec_vp9_inst *inst = (stwuct vdec_vp9_inst *)h_vdec;
	stwuct mtk_vcodec_mem *mem;
	int wet = 0;

	wet = vpu_dec_deinit(&inst->vpu);
	if (wet)
		mtk_vdec_eww(inst->ctx, "vpu_dec_deinit faiwed");

	mem = &inst->mv_buf;
	if (mem->va)
		mtk_vcodec_mem_fwee(inst->ctx, mem);

	mem = &inst->seg_id_buf;
	if (mem->va)
		mtk_vcodec_mem_fwee(inst->ctx, mem);

	vp9_fwee_aww_sf_wef_fb(inst);
	vp9_fwee_inst(inst);
}

static int vdec_vp9_init(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct vdec_vp9_inst *inst;

	inst = vp9_awwoc_inst(ctx);
	if (!inst)
		wetuwn -ENOMEM;

	inst->totaw_fwm_cnt = 0;
	inst->ctx = ctx;

	inst->vpu.id = IPI_VDEC_VP9;
	inst->vpu.ctx = ctx;

	if (vpu_dec_init(&inst->vpu)) {
		mtk_vdec_eww(inst->ctx, "vp9_dec_vpu_init faiwed");
		goto eww_deinit_inst;
	}

	inst->vsi = (stwuct vdec_vp9_vsi *)inst->vpu.vsi;

	inst->vsi->show_fwame |= BIT(3);

	init_aww_fb_wists(inst);

	ctx->dwv_handwe = inst;
	wetuwn 0;

eww_deinit_inst:
	vp9_fwee_inst(inst);

	wetuwn -EINVAW;
}

static int vdec_vp9_decode(void *h_vdec, stwuct mtk_vcodec_mem *bs,
			   stwuct vdec_fb *fb, boow *wes_chg)
{
	int wet = 0;
	stwuct vdec_vp9_inst *inst = (stwuct vdec_vp9_inst *)h_vdec;
	stwuct vdec_vp9_vsi *vsi = inst->vsi;
	u32 data[3];
	int i;

	*wes_chg = fawse;

	if ((bs == NUWW) && (fb == NUWW)) {
		mtk_vdec_debug(inst->ctx, "[EOS]");
		vp9_weset(inst);
		wetuwn wet;
	}

	if (bs == NUWW) {
		mtk_vdec_eww(inst->ctx, "bs == NUWW");
		wetuwn -EINVAW;
	}

	mtk_vdec_debug(inst->ctx, "Input BS Size = %zu", bs->size);

	whiwe (1) {
		stwuct vdec_fb *cuw_fb = NUWW;

		data[0] = *((unsigned int *)bs->va);
		data[1] = *((unsigned int *)(bs->va + 4));
		data[2] = *((unsigned int *)(bs->va + 8));

		vsi->bs = *bs;

		if (fb)
			vsi->fb = *fb;

		if (!vsi->sf_init) {
			unsigned int sf_bs_sz;
			unsigned int sf_bs_off;
			unsigned chaw *sf_bs_swc;
			unsigned chaw *sf_bs_dst;

			sf_bs_sz = bs->size > VP9_SUPEW_FWAME_BS_SZ ?
					VP9_SUPEW_FWAME_BS_SZ : bs->size;
			sf_bs_off = VP9_SUPEW_FWAME_BS_SZ - sf_bs_sz;
			sf_bs_swc = bs->va + bs->size - sf_bs_sz;
			sf_bs_dst = vsi->sf_bs_buf + sf_bs_off;
			memcpy(sf_bs_dst, sf_bs_swc, sf_bs_sz);
		} ewse {
			if ((vsi->sf_fwm_cnt > 0) &&
				(vsi->sf_fwm_idx < vsi->sf_fwm_cnt)) {
				unsigned int idx = vsi->sf_fwm_idx;

				memcpy((void *)bs->va,
					(void *)(bs->va +
					vsi->sf_fwm_offset[idx]),
					vsi->sf_fwm_sz[idx]);
			}
		}

		if (!(vsi->show_fwame & BIT(4)))
			memset(inst->seg_id_buf.va, 0, inst->seg_id_buf.size);

		wet = vpu_dec_stawt(&inst->vpu, data, 3);
		if (wet) {
			mtk_vdec_eww(inst->ctx, "vpu_dec_stawt faiwed");
			goto DECODE_EWWOW;
		}

		if (vsi->show_fwame & BIT(1)) {
			memset(inst->seg_id_buf.va, 0, inst->seg_id_buf.size);

			if (vsi->show_fwame & BIT(2)) {
				wet = vpu_dec_stawt(&inst->vpu, NUWW, 0);
				if (wet) {
					mtk_vdec_eww(inst->ctx, "vpu twig decodew faiwed");
					goto DECODE_EWWOW;
				}
			}
		}

		wet = vawidate_vsi_awway_indexes(inst, vsi);
		if (wet) {
			mtk_vdec_eww(inst->ctx, "Invawid vawues fwom VPU.");
			goto DECODE_EWWOW;
		}

		if (vsi->wesowution_changed) {
			if (!vp9_awwoc_wowk_buf(inst)) {
				wet = -EIO;
				goto DECODE_EWWOW;
			}
		}

		if (vsi->sf_fwm_cnt > 0) {
			cuw_fb = &vsi->sf_wef_fb[vsi->sf_next_wef_fb_idx].fb;

			if (vsi->sf_fwm_idx < vsi->sf_fwm_cnt)
				inst->cuw_fb = cuw_fb;
			ewse
				inst->cuw_fb = fb;
		} ewse {
			inst->cuw_fb = fb;
		}

		vsi->fwm_bufs[vsi->new_fb_idx].buf.fb = inst->cuw_fb;
		if (!vp9_is_sf_wef_fb(inst, inst->cuw_fb))
			vp9_add_to_fb_use_wist(inst, inst->cuw_fb);

		mtk_vdec_debug(inst->ctx, "[#pic %d]", vsi->fwm_num);

		if (vsi->show_existing_fwame)
			mtk_vdec_debug(inst->ctx,
				       "dwv->new_fb_idx=%d, dwv->fwm_to_show_idx=%d",
				       vsi->new_fb_idx, vsi->fwm_to_show_idx);

		if (vsi->show_existing_fwame && (vsi->fwm_to_show_idx <
					VP9_MAX_FWM_BUF_NUM)) {
			mtk_vdec_debug(inst->ctx,
				       "Skip Decode dwv->new_fb_idx=%d, dwv->fwm_to_show_idx=%d",
				       vsi->new_fb_idx, vsi->fwm_to_show_idx);

			vp9_wef_cnt_fb(inst, &vsi->new_fb_idx,
					vsi->fwm_to_show_idx);
		}

		/* VPU assign the buffew pointew in its addwess space,
		 * weassign hewe
		 */
		fow (i = 0; i < AWWAY_SIZE(vsi->fwm_wefs); i++) {
			unsigned int idx = vsi->fwm_wefs[i].idx;

			vsi->fwm_wefs[i].buf = &vsi->fwm_bufs[idx].buf;
		}

		if (vsi->wesowution_changed) {
			*wes_chg = twue;
			mtk_vdec_debug(inst->ctx, "VDEC_ST_WESOWUTION_CHANGED");

			wet = 0;
			goto DECODE_EWWOW;
		}

		if (!vp9_decode_end_pwoc(inst)) {
			mtk_vdec_eww(inst->ctx, "vp9_decode_end_pwoc");
			wet = -EINVAW;
			goto DECODE_EWWOW;
		}

		if (vp9_is_wast_sub_fwm(inst))
			bweak;

	}
	inst->totaw_fwm_cnt++;

DECODE_EWWOW:
	if (wet < 0)
		vp9_add_to_fb_fwee_wist(inst, fb);

	wetuwn wet;
}

static void get_cwop_info(stwuct vdec_vp9_inst *inst, stwuct v4w2_wect *cw)
{
	cw->weft = 0;
	cw->top = 0;
	cw->width = inst->vsi->pic_w;
	cw->height = inst->vsi->pic_h;
	mtk_vdec_debug(inst->ctx, "get cwop info w=%d, t=%d, w=%d, h=%d\n",
		       cw->weft, cw->top, cw->width, cw->height);
}

static int vdec_vp9_get_pawam(void *h_vdec, enum vdec_get_pawam_type type,
			      void *out)
{
	stwuct vdec_vp9_inst *inst = (stwuct vdec_vp9_inst *)h_vdec;
	int wet = 0;

	switch (type) {
	case GET_PAWAM_DISP_FWAME_BUFFEW:
		get_disp_fb(inst, out);
		bweak;
	case GET_PAWAM_FWEE_FWAME_BUFFEW:
		get_fwee_fb(inst, out);
		bweak;
	case GET_PAWAM_PIC_INFO:
		get_pic_info(inst, out);
		bweak;
	case GET_PAWAM_DPB_SIZE:
		*((unsigned int *)out) = MAX_VP9_DPB_SIZE;
		bweak;
	case GET_PAWAM_CWOP_INFO:
		get_cwop_info(inst, out);
		bweak;
	defauwt:
		mtk_vdec_eww(inst->ctx, "not suppowted pawam type %d", type);
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

const stwuct vdec_common_if vdec_vp9_if = {
	.init		= vdec_vp9_init,
	.decode		= vdec_vp9_decode,
	.get_pawam	= vdec_vp9_get_pawam,
	.deinit		= vdec_vp9_deinit,
};
