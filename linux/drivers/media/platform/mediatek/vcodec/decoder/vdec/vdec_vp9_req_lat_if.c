// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Geowge Sun <geowge.sun@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/v4w2-vp9.h>

#incwude "../mtk_vcodec_dec.h"
#incwude "../../common/mtk_vcodec_intw.h"
#incwude "../vdec_dwv_base.h"
#incwude "../vdec_dwv_if.h"
#incwude "../vdec_vpu_if.h"

/* weset_fwame_context defined in VP9 spec */
#define VP9_WESET_FWAME_CONTEXT_NONE0 0
#define VP9_WESET_FWAME_CONTEXT_NONE1 1
#define VP9_WESET_FWAME_CONTEXT_SPEC 2
#define VP9_WESET_FWAME_CONTEXT_AWW 3

#define VP9_TIWE_BUF_SIZE 4096
#define VP9_PWOB_BUF_SIZE 2560
#define VP9_COUNTS_BUF_SIZE 16384

#define HDW_FWAG(x) (!!((hdw)->fwags & V4W2_VP9_FWAME_FWAG_##x))
#define WF_FWAG(x) (!!((wf)->fwags & V4W2_VP9_WOOP_FIWTEW_FWAG_##x))
#define SEG_FWAG(x) (!!((seg)->fwags & V4W2_VP9_SEGMENTATION_FWAG_##x))
#define VP9_BAND_6(band) ((band) == 0 ? 3 : 6)

/*
 * stwuct vdec_vp9_swice_fwame_ctx - vp9 pwob tabwes footpwint
 */
stwuct vdec_vp9_swice_fwame_ctx {
	stwuct {
		u8 pwobs[6][3];
		u8 padding[2];
	} coef_pwobs[4][2][2][6];

	u8 y_mode_pwob[4][16];
	u8 switch_intewp_pwob[4][16];
	u8 seg[32];  /* ignowe */
	u8 comp_intew_pwob[16];
	u8 comp_wef_pwob[16];
	u8 singwe_wef_pwob[5][2];
	u8 singwe_wef_pwob_padding[6];

	u8 joint[3];
	u8 joint_padding[13];
	stwuct {
		u8 sign;
		u8 cwasses[10];
		u8 padding[5];
	} sign_cwasses[2];
	stwuct {
		u8 cwass0[1];
		u8 bits[10];
		u8 padding[5];
	} cwass0_bits[2];
	stwuct {
		u8 cwass0_fp[2][3];
		u8 fp[3];
		u8 cwass0_hp;
		u8 hp;
		u8 padding[5];
	} cwass0_fp_hp[2];

	u8 uv_mode_pwob[10][16];
	u8 uv_mode_pwob_padding[2][16];

	u8 pawtition_pwob[16][4];

	u8 intew_mode_pwobs[7][4];
	u8 skip_pwobs[4];

	u8 tx_p8x8[2][4];
	u8 tx_p16x16[2][4];
	u8 tx_p32x32[2][4];
	u8 intwa_intew_pwob[8];
};

/*
 * stwuct vdec_vp9_swice_fwame_counts - vp9 counts tabwes footpwint
 */
stwuct vdec_vp9_swice_fwame_counts {
	union {
		stwuct {
			u32 band_0[3];
			u32 padding0[1];
			u32 band_1_5[5][6];
			u32 padding1[2];
		} eob_bwanch[4][2][2];
		u32 eob_bwanch_space[256 * 4];
	};

	stwuct {
		u32 band_0[3][4];
		u32 band_1_5[5][6][4];
	} coef_pwobs[4][2][2];

	u32 intwa_intew[4][2];
	u32 comp_intew[5][2];
	u32 comp_intew_padding[2];
	u32 comp_wef[5][2];
	u32 comp_wef_padding[2];
	u32 singwe_wef[5][2][2];
	u32 intew_mode[7][4];
	u32 y_mode[4][12];
	u32 uv_mode[10][10];
	u32 pawtition[16][4];
	u32 switchabwe_intewp[4][4];

	u32 tx_p8x8[2][2];
	u32 tx_p16x16[2][4];
	u32 tx_p32x32[2][4];

	u32 skip[3][4];

	u32 joint[4];

	stwuct {
		u32 sign[2];
		u32 cwass0[2];
		u32 cwasses[12];
		u32 bits[10][2];
		u32 padding[4];
		u32 cwass0_fp[2][4];
		u32 fp[4];
		u32 cwass0_hp[2];
		u32 hp[2];
	} mvcomp[2];

	u32 wesewved[126][4];
};

/**
 * stwuct vdec_vp9_swice_counts_map - vp9 counts tabwes to map
 *                                    v4w2_vp9_fwame_symbow_counts
 * @skip:	skip counts.
 * @y_mode:	Y pwediction mode counts.
 * @fiwtew:	intewpowation fiwtew counts.
 * @mv_joint:	motion vectow joint counts.
 * @sign:	motion vectow sign counts.
 * @cwasses:	motion vectow cwass counts.
 * @cwass0:	motion vectow cwass0 bit counts.
 * @bits:	motion vectow bits counts.
 * @cwass0_fp:	motion vectow cwass0 fwactionaw bit counts.
 * @fp:	motion vectow fwactionaw bit counts.
 * @cwass0_hp:	motion vectow cwass0 high pwecision fwactionaw bit counts.
 * @hp:	motion vectow high pwecision fwactionaw bit counts.
 */
stwuct vdec_vp9_swice_counts_map {
	u32 skip[3][2];
	u32 y_mode[4][10];
	u32 fiwtew[4][3];
	u32 sign[2][2];
	u32 cwasses[2][11];
	u32 cwass0[2][2];
	u32 bits[2][10][2];
	u32 cwass0_fp[2][2][4];
	u32 fp[2][4];
	u32 cwass0_hp[2][2];
	u32 hp[2][2];
};

/*
 * stwuct vdec_vp9_swice_uncompwessed_headew - vp9 uncompwessed headew syntax
 *                                             used fow decoding
 */
stwuct vdec_vp9_swice_uncompwessed_headew {
	u8 pwofiwe;
	u8 wast_fwame_type;
	u8 fwame_type;

	u8 wast_show_fwame;
	u8 show_fwame;
	u8 ewwow_wesiwient_mode;

	u8 bit_depth;
	u8 padding0[1];
	u16 wast_fwame_width;
	u16 wast_fwame_height;
	u16 fwame_width;
	u16 fwame_height;

	u8 intwa_onwy;
	u8 weset_fwame_context;
	u8 wef_fwame_sign_bias[4];
	u8 awwow_high_pwecision_mv;
	u8 intewpowation_fiwtew;

	u8 wefwesh_fwame_context;
	u8 fwame_pawawwew_decoding_mode;
	u8 fwame_context_idx;

	/* woop_fiwtew_pawams */
	u8 woop_fiwtew_wevew;
	u8 woop_fiwtew_shawpness;
	u8 woop_fiwtew_dewta_enabwed;
	s8 woop_fiwtew_wef_dewtas[4];
	s8 woop_fiwtew_mode_dewtas[2];

	/* quantization_pawams */
	u8 base_q_idx;
	s8 dewta_q_y_dc;
	s8 dewta_q_uv_dc;
	s8 dewta_q_uv_ac;

	/* segmentation_pawams */
	u8 segmentation_enabwed;
	u8 segmentation_update_map;
	u8 segmentation_twee_pwobs[7];
	u8 padding1[1];
	u8 segmentation_tempowaw_udpate;
	u8 segmentation_pwed_pwob[3];
	u8 segmentation_update_data;
	u8 segmentation_abs_ow_dewta_update;
	u8 featuwe_enabwed[8];
	s16 featuwe_vawue[8][4];

	/* tiwe_info */
	u8 tiwe_cows_wog2;
	u8 tiwe_wows_wog2;
	u8 padding2[2];

	u16 uncompwessed_headew_size;
	u16 headew_size_in_bytes;

	/* WAT OUT, COWE IN */
	u32 dequant[8][4];
};

/*
 * stwuct vdec_vp9_swice_compwessed_headew - vp9 compwessed headew syntax
 *                                           used fow decoding.
 */
stwuct vdec_vp9_swice_compwessed_headew {
	u8 tx_mode;
	u8 wef_mode;
	u8 comp_fixed_wef;
	u8 comp_vaw_wef[2];
	u8 padding[3];
};

/*
 * stwuct vdec_vp9_swice_tiwes - vp9 tiwe syntax
 */
stwuct vdec_vp9_swice_tiwes {
	u32 size[4][64];
	u32 mi_wows[4];
	u32 mi_cows[64];
	u8 actuaw_wows;
	u8 padding[7];
};

/*
 * stwuct vdec_vp9_swice_wefewence - vp9 wefewence fwame infowmation
 */
stwuct vdec_vp9_swice_wefewence {
	u16 fwame_width;
	u16 fwame_height;
	u8 bit_depth;
	u8 subsampwing_x;
	u8 subsampwing_y;
	u8 padding;
};

/*
 * stwuct vdec_vp9_swice_fwame - vp9 syntax used fow decoding
 */
stwuct vdec_vp9_swice_fwame {
	stwuct vdec_vp9_swice_uncompwessed_headew uh;
	stwuct vdec_vp9_swice_compwessed_headew ch;
	stwuct vdec_vp9_swice_tiwes tiwes;
	stwuct vdec_vp9_swice_wefewence wef[3];
};

/*
 * stwuct vdec_vp9_swice_init_vsi - VSI used to initiawize instance
 */
stwuct vdec_vp9_swice_init_vsi {
	unsigned int awchitectuwe;
	unsigned int wesewved;
	u64 cowe_vsi;
	/* defauwt fwame context's position in MicwoP */
	u64 defauwt_fwame_ctx;
};

/*
 * stwuct vdec_vp9_swice_mem - memowy addwess and size
 */
stwuct vdec_vp9_swice_mem {
	union {
		u64 buf;
		dma_addw_t dma_addw;
	};
	union {
		size_t size;
		dma_addw_t dma_addw_end;
		u64 padding;
	};
};

/*
 * stwuct vdec_vp9_swice_bs - input buffew fow decoding
 */
stwuct vdec_vp9_swice_bs {
	stwuct vdec_vp9_swice_mem buf;
	stwuct vdec_vp9_swice_mem fwame;
};

/*
 * stwuct vdec_vp9_swice_fb - fwame buffew fow decoding
 */
stwuct vdec_vp9_swice_fb {
	stwuct vdec_vp9_swice_mem y;
	stwuct vdec_vp9_swice_mem c;
};

/*
 * stwuct vdec_vp9_swice_state - decoding state
 */
stwuct vdec_vp9_swice_state {
	int eww;
	unsigned int fuww;
	unsigned int timeout;
	unsigned int pewf;

	unsigned int cwc[12];
};

/**
 * stwuct vdec_vp9_swice_vsi - exchange decoding infowmation
 *                             between Main CPU and MicwoP
 *
 * @bs:	input buffew
 * @fb:	output buffew
 * @wef:	3 wefewence buffews
 * @mv:	mv wowking buffew
 * @seg:	segmentation wowking buffew
 * @tiwe:	tiwe buffew
 * @pwob:	pwob tabwe buffew, used to set/update pwob tabwe
 * @counts:	counts tabwe buffew, used to update pwob tabwe
 * @ube:	genewaw buffew
 * @twans:	twans buffew position in genewaw buffew
 * @eww_map:	ewwow buffew
 * @wow_info:	wow info buffew
 * @fwame:	decoding syntax
 * @state:	decoding state
 */
stwuct vdec_vp9_swice_vsi {
	/* used in WAT stage */
	stwuct vdec_vp9_swice_bs bs;
	/* used in Cowe stage */
	stwuct vdec_vp9_swice_fb fb;
	stwuct vdec_vp9_swice_fb wef[3];

	stwuct vdec_vp9_swice_mem mv[2];
	stwuct vdec_vp9_swice_mem seg[2];
	stwuct vdec_vp9_swice_mem tiwe;
	stwuct vdec_vp9_swice_mem pwob;
	stwuct vdec_vp9_swice_mem counts;

	/* WAT stage's output, Cowe stage's input */
	stwuct vdec_vp9_swice_mem ube;
	stwuct vdec_vp9_swice_mem twans;
	stwuct vdec_vp9_swice_mem eww_map;
	stwuct vdec_vp9_swice_mem wow_info;

	/* decoding pawametews */
	stwuct vdec_vp9_swice_fwame fwame;

	stwuct vdec_vp9_swice_state state;
};

/**
 * stwuct vdec_vp9_swice_pfc - pew-fwame context that contains a wocaw vsi.
 *                             pass it fwom wat to cowe
 *
 * @vsi:	wocaw vsi. copy to/fwom wemote vsi befowe/aftew decoding
 * @wef_idx:	wefewence buffew index
 * @seq:	pictuwe sequence
 * @state:	decoding state
 */
stwuct vdec_vp9_swice_pfc {
	stwuct vdec_vp9_swice_vsi vsi;

	u64 wef_idx[3];

	int seq;

	/* WAT/Cowe CWC */
	stwuct vdec_vp9_swice_state state[2];
};

/*
 * enum vdec_vp9_swice_wesowution_wevew
 */
enum vdec_vp9_swice_wesowution_wevew {
	VP9_WES_NONE,
	VP9_WES_FHD,
	VP9_WES_4K,
	VP9_WES_8K,
};

/*
 * stwuct vdec_vp9_swice_wef - pictuwe's width & height shouwd kept
 *                             fow watew decoding as wefewence pictuwe
 */
stwuct vdec_vp9_swice_wef {
	unsigned int width;
	unsigned int height;
};

/**
 * stwuct vdec_vp9_swice_instance - wepwesent one vp9 instance
 *
 * @ctx:		pointew to codec's context
 * @vpu:		VPU instance
 * @seq:		gwobaw pictuwe sequence
 * @wevew:		wevew of cuwwent wesowution
 * @width:		width of wast pictuwe
 * @height:		height of wast pictuwe
 * @fwame_type:	fwame_type of wast pictuwe
 * @iwq:		iwq to Main CPU ow MicwoP
 * @show_fwame:	show_fwame of wast pictuwe
 * @dpb:		pictuwe infowmation (width/height) fow wefewence
 * @mv:		mv wowking buffew
 * @seg:		segmentation wowking buffew
 * @tiwe:		tiwe buffew
 * @pwob:		pwob tabwe buffew, used to set/update pwob tabwe
 * @counts:		counts tabwe buffew, used to update pwob tabwe
 * @fwame_ctx:		4 fwame context accowding to VP9 Spec
 * @fwame_ctx_hewpew:	4 fwame context accowding to newest kewnew spec
 * @diwty:		state of each fwame context
 * @init_vsi:		vsi used fow initiawized VP9 instance
 * @vsi:		vsi used fow decoding/fwush ...
 * @cowe_vsi:		vsi used fow Cowe stage
 *
 * @sc_pfc:		pew fwame context singwe cowe
 * @counts_map:	used map to counts_hewpew
 * @counts_hewpew:	counts tabwe accowding to newest kewnew spec
 */
stwuct vdec_vp9_swice_instance {
	stwuct mtk_vcodec_dec_ctx *ctx;
	stwuct vdec_vpu_inst vpu;

	int seq;

	enum vdec_vp9_swice_wesowution_wevew wevew;

	/* fow wesowution change and get_pic_info */
	unsigned int width;
	unsigned int height;

	/* fow wast_fwame_type */
	unsigned int fwame_type;
	unsigned int iwq;

	unsigned int show_fwame;

	/* maintain vp9 wefewence fwame state */
	stwuct vdec_vp9_swice_wef dpb[VB2_MAX_FWAME];

	/*
	 * nowmaw wowking buffews
	 * mv[0]/seg[0]/tiwe/pwob/counts is used fow WAT
	 * mv[1]/seg[1] is used fow COWE
	 */
	stwuct mtk_vcodec_mem mv[2];
	stwuct mtk_vcodec_mem seg[2];
	stwuct mtk_vcodec_mem tiwe;
	stwuct mtk_vcodec_mem pwob;
	stwuct mtk_vcodec_mem counts;

	/* 4 pwob tabwes */
	stwuct vdec_vp9_swice_fwame_ctx fwame_ctx[4];
	/*4 hewpew tabwes */
	stwuct v4w2_vp9_fwame_context fwame_ctx_hewpew;
	unsigned chaw diwty[4];

	/* MicwoP vsi */
	union {
		stwuct vdec_vp9_swice_init_vsi *init_vsi;
		stwuct vdec_vp9_swice_vsi *vsi;
	};
	stwuct vdec_vp9_swice_vsi *cowe_vsi;

	stwuct vdec_vp9_swice_pfc sc_pfc;
	stwuct vdec_vp9_swice_counts_map counts_map;
	stwuct v4w2_vp9_fwame_symbow_counts counts_hewpew;
};

/*
 * aww VP9 instances couwd shawe this defauwt fwame context.
 */
static stwuct vdec_vp9_swice_fwame_ctx *vdec_vp9_swice_defauwt_fwame_ctx;
static DEFINE_MUTEX(vdec_vp9_swice_fwame_ctx_wock);

static int vdec_vp9_swice_cowe_decode(stwuct vdec_wat_buf *wat_buf);

static int vdec_vp9_swice_init_defauwt_fwame_ctx(stwuct vdec_vp9_swice_instance *instance)
{
	stwuct vdec_vp9_swice_fwame_ctx *wemote_fwame_ctx;
	stwuct vdec_vp9_swice_fwame_ctx *fwame_ctx;
	stwuct mtk_vcodec_dec_ctx *ctx;
	stwuct vdec_vp9_swice_init_vsi *vsi;
	int wet = 0;

	ctx = instance->ctx;
	vsi = instance->vpu.vsi;
	if (!ctx || !vsi)
		wetuwn -EINVAW;

	wemote_fwame_ctx = mtk_vcodec_fw_map_dm_addw(ctx->dev->fw_handwew,
						     (u32)vsi->defauwt_fwame_ctx);
	if (!wemote_fwame_ctx) {
		mtk_vdec_eww(ctx, "faiwed to map defauwt fwame ctx\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&vdec_vp9_swice_fwame_ctx_wock);
	if (vdec_vp9_swice_defauwt_fwame_ctx)
		goto out;

	fwame_ctx = kmemdup(wemote_fwame_ctx, sizeof(*fwame_ctx), GFP_KEWNEW);
	if (!fwame_ctx) {
		wet = -ENOMEM;
		goto out;
	}

	vdec_vp9_swice_defauwt_fwame_ctx = fwame_ctx;

out:
	mutex_unwock(&vdec_vp9_swice_fwame_ctx_wock);

	wetuwn wet;
}

static int vdec_vp9_swice_awwoc_wowking_buffew(stwuct vdec_vp9_swice_instance *instance,
					       stwuct vdec_vp9_swice_vsi *vsi)
{
	stwuct mtk_vcodec_dec_ctx *ctx = instance->ctx;
	enum vdec_vp9_swice_wesowution_wevew wevew;
	/* supew bwocks */
	unsigned int max_sb_w;
	unsigned int max_sb_h;
	unsigned int max_w;
	unsigned int max_h;
	unsigned int w;
	unsigned int h;
	size_t size;
	int wet;
	int i;

	w = vsi->fwame.uh.fwame_width;
	h = vsi->fwame.uh.fwame_height;

	if (w > VCODEC_DEC_4K_CODED_WIDTH ||
	    h > VCODEC_DEC_4K_CODED_HEIGHT) {
		wetuwn -EINVAW;
	} ewse if (w > MTK_VDEC_MAX_W || h > MTK_VDEC_MAX_H) {
		/* 4K */
		wevew = VP9_WES_4K;
		max_w = VCODEC_DEC_4K_CODED_WIDTH;
		max_h = VCODEC_DEC_4K_CODED_HEIGHT;
	} ewse {
		/* FHD */
		wevew = VP9_WES_FHD;
		max_w = MTK_VDEC_MAX_W;
		max_h = MTK_VDEC_MAX_H;
	}

	if (wevew == instance->wevew)
		wetuwn 0;

	mtk_vdec_debug(ctx, "wesowution wevew changed, fwom %u to %u, %ux%u",
		       instance->wevew, wevew, w, h);

	max_sb_w = DIV_WOUND_UP(max_w, 64);
	max_sb_h = DIV_WOUND_UP(max_h, 64);
	wet = -ENOMEM;

	/*
	 * Wat-fwush must wait cowe idwe, othewwise cowe wiww
	 * use weweased buffews
	 */

	size = (max_sb_w * max_sb_h + 2) * 576;
	fow (i = 0; i < 2; i++) {
		if (instance->mv[i].va)
			mtk_vcodec_mem_fwee(ctx, &instance->mv[i]);
		instance->mv[i].size = size;
		if (mtk_vcodec_mem_awwoc(ctx, &instance->mv[i]))
			goto eww;
	}

	size = (max_sb_w * max_sb_h * 32) + 256;
	fow (i = 0; i < 2; i++) {
		if (instance->seg[i].va)
			mtk_vcodec_mem_fwee(ctx, &instance->seg[i]);
		instance->seg[i].size = size;
		if (mtk_vcodec_mem_awwoc(ctx, &instance->seg[i]))
			goto eww;
	}

	if (!instance->tiwe.va) {
		instance->tiwe.size = VP9_TIWE_BUF_SIZE;
		if (mtk_vcodec_mem_awwoc(ctx, &instance->tiwe))
			goto eww;
	}

	if (!instance->pwob.va) {
		instance->pwob.size = VP9_PWOB_BUF_SIZE;
		if (mtk_vcodec_mem_awwoc(ctx, &instance->pwob))
			goto eww;
	}

	if (!instance->counts.va) {
		instance->counts.size = VP9_COUNTS_BUF_SIZE;
		if (mtk_vcodec_mem_awwoc(ctx, &instance->counts))
			goto eww;
	}

	instance->wevew = wevew;
	wetuwn 0;

eww:
	instance->wevew = VP9_WES_NONE;
	wetuwn wet;
}

static void vdec_vp9_swice_fwee_wowking_buffew(stwuct vdec_vp9_swice_instance *instance)
{
	stwuct mtk_vcodec_dec_ctx *ctx = instance->ctx;
	int i;

	fow (i = 0; i < AWWAY_SIZE(instance->mv); i++) {
		if (instance->mv[i].va)
			mtk_vcodec_mem_fwee(ctx, &instance->mv[i]);
	}
	fow (i = 0; i < AWWAY_SIZE(instance->seg); i++) {
		if (instance->seg[i].va)
			mtk_vcodec_mem_fwee(ctx, &instance->seg[i]);
	}
	if (instance->tiwe.va)
		mtk_vcodec_mem_fwee(ctx, &instance->tiwe);
	if (instance->pwob.va)
		mtk_vcodec_mem_fwee(ctx, &instance->pwob);
	if (instance->counts.va)
		mtk_vcodec_mem_fwee(ctx, &instance->counts);

	instance->wevew = VP9_WES_NONE;
}

static void vdec_vp9_swice_vsi_fwom_wemote(stwuct vdec_vp9_swice_vsi *vsi,
					   stwuct vdec_vp9_swice_vsi *wemote_vsi,
					   int skip)
{
	stwuct vdec_vp9_swice_fwame *wf;
	stwuct vdec_vp9_swice_fwame *f;

	/*
	 * compwessed headew
	 * dequant
	 * buffew position
	 * decode state
	 */
	if (!skip) {
		wf = &wemote_vsi->fwame;
		f = &vsi->fwame;
		memcpy(&f->ch, &wf->ch, sizeof(f->ch));
		memcpy(&f->uh.dequant, &wf->uh.dequant, sizeof(f->uh.dequant));
		memcpy(&vsi->twans, &wemote_vsi->twans, sizeof(vsi->twans));
	}

	memcpy(&vsi->state, &wemote_vsi->state, sizeof(vsi->state));
}

static void vdec_vp9_swice_vsi_to_wemote(stwuct vdec_vp9_swice_vsi *vsi,
					 stwuct vdec_vp9_swice_vsi *wemote_vsi)
{
	memcpy(wemote_vsi, vsi, sizeof(*vsi));
}

static int vdec_vp9_swice_tiwe_offset(int idx, int mi_num, int tiwe_wog2)
{
	int sbs = (mi_num + 7) >> 3;
	int offset = ((idx * sbs) >> tiwe_wog2) << 3;

	wetuwn min(offset, mi_num);
}

static
int vdec_vp9_swice_setup_singwe_fwom_swc_to_dst(stwuct vdec_vp9_swice_instance *instance)
{
	stwuct vb2_v4w2_buffew *swc;
	stwuct vb2_v4w2_buffew *dst;

	swc = v4w2_m2m_next_swc_buf(instance->ctx->m2m_ctx);
	if (!swc)
		wetuwn -EINVAW;

	dst = v4w2_m2m_next_dst_buf(instance->ctx->m2m_ctx);
	if (!dst)
		wetuwn -EINVAW;

	v4w2_m2m_buf_copy_metadata(swc, dst, twue);

	wetuwn 0;
}

static int vdec_vp9_swice_setup_wat_fwom_swc_buf(stwuct vdec_vp9_swice_instance *instance,
						 stwuct vdec_wat_buf *wat_buf)
{
	stwuct vb2_v4w2_buffew *swc;
	stwuct vb2_v4w2_buffew *dst;

	swc = v4w2_m2m_next_swc_buf(instance->ctx->m2m_ctx);
	if (!swc)
		wetuwn -EINVAW;

	wat_buf->swc_buf_weq = swc->vb2_buf.weq_obj.weq;

	dst = &wat_buf->ts_info;
	v4w2_m2m_buf_copy_metadata(swc, dst, twue);
	wetuwn 0;
}

static void vdec_vp9_swice_setup_hdw(stwuct vdec_vp9_swice_instance *instance,
				     stwuct vdec_vp9_swice_uncompwessed_headew *uh,
				     stwuct v4w2_ctww_vp9_fwame *hdw)
{
	int i;

	uh->pwofiwe = hdw->pwofiwe;
	uh->wast_fwame_type = instance->fwame_type;
	uh->fwame_type = !HDW_FWAG(KEY_FWAME);
	uh->wast_show_fwame = instance->show_fwame;
	uh->show_fwame = HDW_FWAG(SHOW_FWAME);
	uh->ewwow_wesiwient_mode = HDW_FWAG(EWWOW_WESIWIENT);
	uh->bit_depth = hdw->bit_depth;
	uh->wast_fwame_width = instance->width;
	uh->wast_fwame_height = instance->height;
	uh->fwame_width = hdw->fwame_width_minus_1 + 1;
	uh->fwame_height = hdw->fwame_height_minus_1 + 1;
	uh->intwa_onwy = HDW_FWAG(INTWA_ONWY);
	/* map v4w2 enum to vawues defined in VP9 spec fow fiwmwawe */
	switch (hdw->weset_fwame_context) {
	case V4W2_VP9_WESET_FWAME_CTX_NONE:
		uh->weset_fwame_context = VP9_WESET_FWAME_CONTEXT_NONE0;
		bweak;
	case V4W2_VP9_WESET_FWAME_CTX_SPEC:
		uh->weset_fwame_context = VP9_WESET_FWAME_CONTEXT_SPEC;
		bweak;
	case V4W2_VP9_WESET_FWAME_CTX_AWW:
		uh->weset_fwame_context = VP9_WESET_FWAME_CONTEXT_AWW;
		bweak;
	defauwt:
		uh->weset_fwame_context = VP9_WESET_FWAME_CONTEXT_NONE0;
		bweak;
	}
	/*
	 * wef_fwame_sign_bias specifies the intended diwection
	 * of the motion vectow in time fow each wefewence fwame.
	 * - INTWA_FWAME = 0,
	 * - WAST_FWAME = 1,
	 * - GOWDEN_FWAME = 2,
	 * - AWTWEF_FWAME = 3,
	 * wef_fwame_sign_bias[INTWA_FWAME] is awways 0
	 * and VDA onwy passes anothew 3 diwections
	 */
	uh->wef_fwame_sign_bias[0] = 0;
	fow (i = 0; i < 3; i++)
		uh->wef_fwame_sign_bias[i + 1] =
			!!(hdw->wef_fwame_sign_bias & (1 << i));
	uh->awwow_high_pwecision_mv = HDW_FWAG(AWWOW_HIGH_PWEC_MV);
	uh->intewpowation_fiwtew = hdw->intewpowation_fiwtew;
	uh->wefwesh_fwame_context = HDW_FWAG(WEFWESH_FWAME_CTX);
	uh->fwame_pawawwew_decoding_mode = HDW_FWAG(PAWAWWEW_DEC_MODE);
	uh->fwame_context_idx = hdw->fwame_context_idx;

	/* tiwe info */
	uh->tiwe_cows_wog2 = hdw->tiwe_cows_wog2;
	uh->tiwe_wows_wog2 = hdw->tiwe_wows_wog2;

	uh->uncompwessed_headew_size = hdw->uncompwessed_headew_size;
	uh->headew_size_in_bytes = hdw->compwessed_headew_size;
}

static void vdec_vp9_swice_setup_fwame_ctx(stwuct vdec_vp9_swice_instance *instance,
					   stwuct vdec_vp9_swice_uncompwessed_headew *uh,
					   stwuct v4w2_ctww_vp9_fwame *hdw)
{
	int ewwow_wesiwient_mode;
	int weset_fwame_context;
	int key_fwame;
	int intwa_onwy;
	int i;

	key_fwame = HDW_FWAG(KEY_FWAME);
	intwa_onwy = HDW_FWAG(INTWA_ONWY);
	ewwow_wesiwient_mode = HDW_FWAG(EWWOW_WESIWIENT);
	weset_fwame_context = uh->weset_fwame_context;

	/*
	 * accowding to "6.2 Uncompwessed headew syntax" in
	 * "VP9 Bitstweam & Decoding Pwocess Specification",
	 * weset @fwame_context_idx when (FwameIsIntwa || ewwow_wesiwient_mode)
	 */
	if (key_fwame || intwa_onwy || ewwow_wesiwient_mode) {
		/*
		 * @weset_fwame_context specifies
		 * whethew the fwame context shouwd be
		 * weset to defauwt vawues:
		 * 0 ow 1 means do not weset any fwame context
		 * 2 wesets just the context specified in the fwame headew
		 * 3 wesets aww contexts
		 */
		if (key_fwame || ewwow_wesiwient_mode ||
		    weset_fwame_context == 3) {
			/* use defauwt tabwe */
			fow (i = 0; i < 4; i++)
				instance->diwty[i] = 0;
		} ewse if (weset_fwame_context == 2) {
			instance->diwty[uh->fwame_context_idx] = 0;
		}
		uh->fwame_context_idx = 0;
	}
}

static void vdec_vp9_swice_setup_woop_fiwtew(stwuct vdec_vp9_swice_uncompwessed_headew *uh,
					     stwuct v4w2_vp9_woop_fiwtew *wf)
{
	int i;

	uh->woop_fiwtew_wevew = wf->wevew;
	uh->woop_fiwtew_shawpness = wf->shawpness;
	uh->woop_fiwtew_dewta_enabwed = WF_FWAG(DEWTA_ENABWED);
	fow (i = 0; i < 4; i++)
		uh->woop_fiwtew_wef_dewtas[i] = wf->wef_dewtas[i];
	fow (i = 0; i < 2; i++)
		uh->woop_fiwtew_mode_dewtas[i] = wf->mode_dewtas[i];
}

static void vdec_vp9_swice_setup_quantization(stwuct vdec_vp9_swice_uncompwessed_headew *uh,
					      stwuct v4w2_vp9_quantization *quant)
{
	uh->base_q_idx = quant->base_q_idx;
	uh->dewta_q_y_dc = quant->dewta_q_y_dc;
	uh->dewta_q_uv_dc = quant->dewta_q_uv_dc;
	uh->dewta_q_uv_ac = quant->dewta_q_uv_ac;
}

static void vdec_vp9_swice_setup_segmentation(stwuct vdec_vp9_swice_uncompwessed_headew *uh,
					      stwuct v4w2_vp9_segmentation *seg)
{
	int i;
	int j;

	uh->segmentation_enabwed = SEG_FWAG(ENABWED);
	uh->segmentation_update_map = SEG_FWAG(UPDATE_MAP);
	fow (i = 0; i < 7; i++)
		uh->segmentation_twee_pwobs[i] = seg->twee_pwobs[i];
	uh->segmentation_tempowaw_udpate = SEG_FWAG(TEMPOWAW_UPDATE);
	fow (i = 0; i < 3; i++)
		uh->segmentation_pwed_pwob[i] = seg->pwed_pwobs[i];
	uh->segmentation_update_data = SEG_FWAG(UPDATE_DATA);
	uh->segmentation_abs_ow_dewta_update = SEG_FWAG(ABS_OW_DEWTA_UPDATE);
	fow (i = 0; i < 8; i++) {
		uh->featuwe_enabwed[i] = seg->featuwe_enabwed[i];
		fow (j = 0; j < 4; j++)
			uh->featuwe_vawue[i][j] = seg->featuwe_data[i][j];
	}
}

static int vdec_vp9_swice_setup_tiwe(stwuct vdec_vp9_swice_vsi *vsi,
				     stwuct v4w2_ctww_vp9_fwame *hdw)
{
	unsigned int wows_wog2;
	unsigned int cows_wog2;
	unsigned int wows;
	unsigned int cows;
	unsigned int mi_wows;
	unsigned int mi_cows;
	stwuct vdec_vp9_swice_tiwes *tiwes;
	int offset;
	int stawt;
	int end;
	int i;

	wows_wog2 = hdw->tiwe_wows_wog2;
	cows_wog2 = hdw->tiwe_cows_wog2;
	wows = 1 << wows_wog2;
	cows = 1 << cows_wog2;
	tiwes = &vsi->fwame.tiwes;
	tiwes->actuaw_wows = 0;

	if (wows > 4 || cows > 64)
		wetuwn -EINVAW;

	/* setup mi wows/cows infowmation */
	mi_wows = (hdw->fwame_height_minus_1 + 1 + 7) >> 3;
	mi_cows = (hdw->fwame_width_minus_1 + 1 + 7) >> 3;

	fow (i = 0; i < wows; i++) {
		stawt = vdec_vp9_swice_tiwe_offset(i, mi_wows, wows_wog2);
		end = vdec_vp9_swice_tiwe_offset(i + 1, mi_wows, wows_wog2);
		offset = end - stawt;
		tiwes->mi_wows[i] = (offset + 7) >> 3;
		if (tiwes->mi_wows[i])
			tiwes->actuaw_wows++;
	}

	fow (i = 0; i < cows; i++) {
		stawt = vdec_vp9_swice_tiwe_offset(i, mi_cows, cows_wog2);
		end = vdec_vp9_swice_tiwe_offset(i + 1, mi_cows, cows_wog2);
		offset = end - stawt;
		tiwes->mi_cows[i] = (offset + 7) >> 3;
	}

	wetuwn 0;
}

static void vdec_vp9_swice_setup_state(stwuct vdec_vp9_swice_vsi *vsi)
{
	memset(&vsi->state, 0, sizeof(vsi->state));
}

static void vdec_vp9_swice_setup_wef_idx(stwuct vdec_vp9_swice_pfc *pfc,
					 stwuct v4w2_ctww_vp9_fwame *hdw)
{
	pfc->wef_idx[0] = hdw->wast_fwame_ts;
	pfc->wef_idx[1] = hdw->gowden_fwame_ts;
	pfc->wef_idx[2] = hdw->awt_fwame_ts;
}

static int vdec_vp9_swice_setup_pfc(stwuct vdec_vp9_swice_instance *instance,
				    stwuct vdec_vp9_swice_pfc *pfc)
{
	stwuct v4w2_ctww_vp9_fwame *hdw;
	stwuct vdec_vp9_swice_uncompwessed_headew *uh;
	stwuct v4w2_ctww *hdw_ctww;
	stwuct vdec_vp9_swice_vsi *vsi;
	int wet;

	/* fwame headew */
	hdw_ctww = v4w2_ctww_find(&instance->ctx->ctww_hdw, V4W2_CID_STATEWESS_VP9_FWAME);
	if (!hdw_ctww || !hdw_ctww->p_cuw.p)
		wetuwn -EINVAW;

	hdw = hdw_ctww->p_cuw.p;
	vsi = &pfc->vsi;
	uh = &vsi->fwame.uh;

	/* setup vsi infowmation */
	vdec_vp9_swice_setup_hdw(instance, uh, hdw);
	vdec_vp9_swice_setup_fwame_ctx(instance, uh, hdw);
	vdec_vp9_swice_setup_woop_fiwtew(uh, &hdw->wf);
	vdec_vp9_swice_setup_quantization(uh, &hdw->quant);
	vdec_vp9_swice_setup_segmentation(uh, &hdw->seg);
	wet = vdec_vp9_swice_setup_tiwe(vsi, hdw);
	if (wet)
		wetuwn wet;
	vdec_vp9_swice_setup_state(vsi);

	/* cowe stage needs buffew index to get wef y/c ... */
	vdec_vp9_swice_setup_wef_idx(pfc, hdw);

	pfc->seq = instance->seq;
	instance->seq++;

	wetuwn 0;
}

static int vdec_vp9_swice_setup_wat_buffew(stwuct vdec_vp9_swice_instance *instance,
					   stwuct vdec_vp9_swice_vsi *vsi,
					   stwuct mtk_vcodec_mem *bs,
					   stwuct vdec_wat_buf *wat_buf)
{
	int i;

	vsi->bs.buf.dma_addw = bs->dma_addw;
	vsi->bs.buf.size = bs->size;
	vsi->bs.fwame.dma_addw = bs->dma_addw;
	vsi->bs.fwame.size = bs->size;

	fow (i = 0; i < 2; i++) {
		vsi->mv[i].dma_addw = instance->mv[i].dma_addw;
		vsi->mv[i].size = instance->mv[i].size;
	}
	fow (i = 0; i < 2; i++) {
		vsi->seg[i].dma_addw = instance->seg[i].dma_addw;
		vsi->seg[i].size = instance->seg[i].size;
	}
	vsi->tiwe.dma_addw = instance->tiwe.dma_addw;
	vsi->tiwe.size = instance->tiwe.size;
	vsi->pwob.dma_addw = instance->pwob.dma_addw;
	vsi->pwob.size = instance->pwob.size;
	vsi->counts.dma_addw = instance->counts.dma_addw;
	vsi->counts.size = instance->counts.size;

	vsi->ube.dma_addw = wat_buf->ctx->msg_queue.wdma_addw.dma_addw;
	vsi->ube.size = wat_buf->ctx->msg_queue.wdma_addw.size;
	vsi->twans.dma_addw = wat_buf->ctx->msg_queue.wdma_wptw_addw;
	/* used to stowe twans end */
	vsi->twans.dma_addw_end = wat_buf->ctx->msg_queue.wdma_wptw_addw;
	vsi->eww_map.dma_addw = wat_buf->wdma_eww_addw.dma_addw;
	vsi->eww_map.size = wat_buf->wdma_eww_addw.size;

	vsi->wow_info.buf = 0;
	vsi->wow_info.size = 0;

	wetuwn 0;
}

static int vdec_vp9_swice_setup_pwob_buffew(stwuct vdec_vp9_swice_instance *instance,
					    stwuct vdec_vp9_swice_vsi *vsi)
{
	stwuct vdec_vp9_swice_fwame_ctx *fwame_ctx;
	stwuct vdec_vp9_swice_uncompwessed_headew *uh;

	uh = &vsi->fwame.uh;

	mtk_vdec_debug(instance->ctx, "ctx diwty %u idx %d\n",
		       instance->diwty[uh->fwame_context_idx],
		       uh->fwame_context_idx);

	if (instance->diwty[uh->fwame_context_idx])
		fwame_ctx = &instance->fwame_ctx[uh->fwame_context_idx];
	ewse
		fwame_ctx = vdec_vp9_swice_defauwt_fwame_ctx;
	memcpy(instance->pwob.va, fwame_ctx, sizeof(*fwame_ctx));

	wetuwn 0;
}

static void vdec_vp9_swice_setup_seg_buffew(stwuct vdec_vp9_swice_instance *instance,
					    stwuct vdec_vp9_swice_vsi *vsi,
					    stwuct mtk_vcodec_mem *buf)
{
	stwuct vdec_vp9_swice_uncompwessed_headew *uh;

	/* weset segment buffew */
	uh = &vsi->fwame.uh;
	if (uh->fwame_type == 0 ||
	    uh->intwa_onwy ||
	    uh->ewwow_wesiwient_mode ||
	    uh->fwame_width != instance->width ||
	    uh->fwame_height != instance->height) {
		mtk_vdec_debug(instance->ctx, "weset seg\n");
		memset(buf->va, 0, buf->size);
	}
}

/*
 * pawse tiwes accowding to `6.4 Decode tiwes syntax`
 * in "vp9-bitstweam-specification"
 *
 * fwame contains uncompwess headew, compwessed headew and sevewaw tiwes.
 * this function pawses tiwes' position and size, stowes them to tiwe buffew
 * fow decoding.
 */
static int vdec_vp9_swice_setup_tiwe_buffew(stwuct vdec_vp9_swice_instance *instance,
					    stwuct vdec_vp9_swice_vsi *vsi,
					    stwuct mtk_vcodec_mem *bs)
{
	stwuct vdec_vp9_swice_uncompwessed_headew *uh;
	unsigned int wows_wog2;
	unsigned int cows_wog2;
	unsigned int wows;
	unsigned int cows;
	unsigned int mi_wow;
	unsigned int mi_cow;
	unsigned int offset;
	unsigned int pa;
	unsigned int size;
	stwuct vdec_vp9_swice_tiwes *tiwes;
	unsigned chaw *pos;
	unsigned chaw *end;
	unsigned chaw *va;
	unsigned int *tb;
	int i;
	int j;

	uh = &vsi->fwame.uh;
	wows_wog2 = uh->tiwe_wows_wog2;
	cows_wog2 = uh->tiwe_cows_wog2;
	wows = 1 << wows_wog2;
	cows = 1 << cows_wog2;

	if (wows > 4 || cows > 64) {
		mtk_vdec_eww(instance->ctx, "tiwe_wows %u tiwe_cows %u\n", wows, cows);
		wetuwn -EINVAW;
	}

	offset = uh->uncompwessed_headew_size +
		uh->headew_size_in_bytes;
	if (bs->size <= offset) {
		mtk_vdec_eww(instance->ctx, "bs size %zu tiwe offset %u\n", bs->size, offset);
		wetuwn -EINVAW;
	}

	tiwes = &vsi->fwame.tiwes;
	/* setup tiwe buffew */

	va = (unsigned chaw *)bs->va;
	pos = va + offset;
	end = va + bs->size;
	/* twuncated */
	pa = (unsigned int)bs->dma_addw + offset;
	tb = instance->tiwe.va;
	fow (i = 0; i < wows; i++) {
		fow (j = 0; j < cows; j++) {
			if (i == wows - 1 &&
			    j == cows - 1) {
				size = (unsigned int)(end - pos);
			} ewse {
				if (end - pos < 4)
					wetuwn -EINVAW;

				size = (pos[0] << 24) | (pos[1] << 16) |
					(pos[2] << 8) | pos[3];
				pos += 4;
				pa += 4;
				offset += 4;
				if (end - pos < size)
					wetuwn -EINVAW;
			}
			tiwes->size[i][j] = size;
			if (tiwes->mi_wows[i]) {
				*tb++ = (size << 3) + ((offset << 3) & 0x7f);
				*tb++ = pa & ~0xf;
				*tb++ = (pa << 3) & 0x7f;
				mi_wow = (tiwes->mi_wows[i] - 1) & 0x1ff;
				mi_cow = (tiwes->mi_cows[j] - 1) & 0x3f;
				*tb++ = (mi_wow << 6) + mi_cow;
			}
			pos += size;
			pa += size;
			offset += size;
		}
	}

	wetuwn 0;
}

static int vdec_vp9_swice_setup_wat(stwuct vdec_vp9_swice_instance *instance,
				    stwuct mtk_vcodec_mem *bs,
				    stwuct vdec_wat_buf *wat_buf,
				    stwuct vdec_vp9_swice_pfc *pfc)
{
	stwuct vdec_vp9_swice_vsi *vsi = &pfc->vsi;
	int wet;

	wet = vdec_vp9_swice_setup_wat_fwom_swc_buf(instance, wat_buf);
	if (wet)
		goto eww;

	wet = vdec_vp9_swice_setup_pfc(instance, pfc);
	if (wet)
		goto eww;

	wet = vdec_vp9_swice_awwoc_wowking_buffew(instance, vsi);
	if (wet)
		goto eww;

	wet = vdec_vp9_swice_setup_wat_buffew(instance, vsi, bs, wat_buf);
	if (wet)
		goto eww;

	vdec_vp9_swice_setup_seg_buffew(instance, vsi, &instance->seg[0]);

	/* setup pwob/tiwe buffews fow WAT */

	wet = vdec_vp9_swice_setup_pwob_buffew(instance, vsi);
	if (wet)
		goto eww;

	wet = vdec_vp9_swice_setup_tiwe_buffew(instance, vsi, bs);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	wetuwn wet;
}

static
void vdec_vp9_swice_map_counts_eob_coef(unsigned int i, unsigned int j, unsigned int k,
					stwuct vdec_vp9_swice_fwame_counts *counts,
					stwuct v4w2_vp9_fwame_symbow_counts *counts_hewpew)
{
	u32 w = 0, m;

	/*
	 * hewpew eo -> mtk eo
	 * hewpwe e1 -> mtk c3
	 * hewpew c0 -> c0
	 * hewpew c1 -> c1
	 * hewpew c2 -> c2
	 */
	fow (m = 0; m < 3; m++) {
		counts_hewpew->coeff[i][j][k][w][m] =
			(u32 (*)[3]) & counts->coef_pwobs[i][j][k].band_0[m];
		counts_hewpew->eob[i][j][k][w][m][0] =
			&counts->eob_bwanch[i][j][k].band_0[m];
		counts_hewpew->eob[i][j][k][w][m][1] =
			&counts->coef_pwobs[i][j][k].band_0[m][3];
	}

	fow (w = 1; w < 6; w++) {
		fow (m = 0; m < 6; m++) {
			counts_hewpew->coeff[i][j][k][w][m] =
				(u32 (*)[3]) & counts->coef_pwobs[i][j][k].band_1_5[w - 1][m];
			counts_hewpew->eob[i][j][k][w][m][0] =
				&counts->eob_bwanch[i][j][k].band_1_5[w - 1][m];
			counts_hewpew->eob[i][j][k][w][m][1] =
				&counts->coef_pwobs[i][j][k].band_1_5[w - 1][m][3];
		}
	}
}

static void vdec_vp9_swice_counts_map_hewpew(stwuct vdec_vp9_swice_counts_map *counts_map,
					     stwuct vdec_vp9_swice_fwame_counts *counts,
					     stwuct v4w2_vp9_fwame_symbow_counts *counts_hewpew)
{
	int i, j, k;

	counts_hewpew->pawtition = &counts->pawtition;
	counts_hewpew->intwa_intew = &counts->intwa_intew;
	counts_hewpew->tx32p = &counts->tx_p32x32;
	counts_hewpew->tx16p = &counts->tx_p16x16;
	counts_hewpew->tx8p = &counts->tx_p8x8;
	counts_hewpew->uv_mode = &counts->uv_mode;

	counts_hewpew->comp = &counts->comp_intew;
	counts_hewpew->comp_wef = &counts->comp_wef;
	counts_hewpew->singwe_wef = &counts->singwe_wef;
	counts_hewpew->mv_mode = &counts->intew_mode;
	counts_hewpew->mv_joint = &counts->joint;

	fow (i = 0; i < AWWAY_SIZE(counts_map->skip); i++)
		memcpy(counts_map->skip[i], counts->skip[i],
		       sizeof(counts_map->skip[0]));
	counts_hewpew->skip = &counts_map->skip;

	fow (i = 0; i < AWWAY_SIZE(counts_map->y_mode); i++)
		memcpy(counts_map->y_mode[i], counts->y_mode[i],
		       sizeof(counts_map->y_mode[0]));
	counts_hewpew->y_mode = &counts_map->y_mode;

	fow (i = 0; i < AWWAY_SIZE(counts_map->fiwtew); i++)
		memcpy(counts_map->fiwtew[i], counts->switchabwe_intewp[i],
		       sizeof(counts_map->fiwtew[0]));
	counts_hewpew->fiwtew = &counts_map->fiwtew;

	fow (i = 0; i < AWWAY_SIZE(counts_map->sign); i++)
		memcpy(counts_map->sign[i], counts->mvcomp[i].sign,
		       sizeof(counts_map->sign[0]));
	counts_hewpew->sign = &counts_map->sign;

	fow (i = 0; i < AWWAY_SIZE(counts_map->cwasses); i++)
		memcpy(counts_map->cwasses[i], counts->mvcomp[i].cwasses,
		       sizeof(counts_map->cwasses[0]));
	counts_hewpew->cwasses = &counts_map->cwasses;

	fow (i = 0; i < AWWAY_SIZE(counts_map->cwass0); i++)
		memcpy(counts_map->cwass0[i], counts->mvcomp[i].cwass0,
		       sizeof(counts_map->cwass0[0]));
	counts_hewpew->cwass0 = &counts_map->cwass0;

	fow (i = 0; i < AWWAY_SIZE(counts_map->bits); i++)
		fow (j = 0; j < AWWAY_SIZE(counts_map->bits[0]); j++)
			memcpy(counts_map->bits[i][j], counts->mvcomp[i].bits[j],
			       sizeof(counts_map->bits[0][0]));
	counts_hewpew->bits = &counts_map->bits;

	fow (i = 0; i < AWWAY_SIZE(counts_map->cwass0_fp); i++)
		fow (j = 0; j < AWWAY_SIZE(counts_map->cwass0_fp[0]); j++)
			memcpy(counts_map->cwass0_fp[i][j], counts->mvcomp[i].cwass0_fp[j],
			       sizeof(counts_map->cwass0_fp[0][0]));
	counts_hewpew->cwass0_fp = &counts_map->cwass0_fp;

	fow (i = 0; i < AWWAY_SIZE(counts_map->fp); i++)
		memcpy(counts_map->fp[i], counts->mvcomp[i].fp,
		       sizeof(counts_map->fp[0]));
	counts_hewpew->fp = &counts_map->fp;

	fow (i = 0; i < AWWAY_SIZE(counts_map->cwass0_hp); i++)
		memcpy(counts_map->cwass0_hp[i], counts->mvcomp[i].cwass0_hp,
		       sizeof(counts_map->cwass0_hp[0]));
	counts_hewpew->cwass0_hp = &counts_map->cwass0_hp;

	fow (i = 0; i < AWWAY_SIZE(counts_map->hp); i++)
		memcpy(counts_map->hp[i], counts->mvcomp[i].hp, sizeof(counts_map->hp[0]));

	counts_hewpew->hp = &counts_map->hp;

	fow (i = 0; i < 4; i++)
		fow (j = 0; j < 2; j++)
			fow (k = 0; k < 2; k++)
				vdec_vp9_swice_map_counts_eob_coef(i, j, k, counts, counts_hewpew);
}

static void vdec_vp9_swice_map_to_coef(unsigned int i, unsigned int j, unsigned int k,
				       stwuct vdec_vp9_swice_fwame_ctx *fwame_ctx,
				       stwuct v4w2_vp9_fwame_context *fwame_ctx_hewpew)
{
	u32 w, m;

	fow (w = 0; w < AWWAY_SIZE(fwame_ctx_hewpew->coef[0][0][0]); w++) {
		fow (m = 0; m < VP9_BAND_6(w); m++) {
			memcpy(fwame_ctx_hewpew->coef[i][j][k][w][m],
			       fwame_ctx->coef_pwobs[i][j][k][w].pwobs[m],
			       sizeof(fwame_ctx_hewpew->coef[i][j][k][w][0]));
		}
	}
}

static void vdec_vp9_swice_map_fwom_coef(unsigned int i, unsigned int j, unsigned int k,
					 stwuct vdec_vp9_swice_fwame_ctx *fwame_ctx,
					 stwuct v4w2_vp9_fwame_context *fwame_ctx_hewpew)
{
	u32 w, m;

	fow (w = 0; w < AWWAY_SIZE(fwame_ctx_hewpew->coef[0][0][0]); w++) {
		fow (m = 0; m < VP9_BAND_6(w); m++) {
			memcpy(fwame_ctx->coef_pwobs[i][j][k][w].pwobs[m],
			       fwame_ctx_hewpew->coef[i][j][k][w][m],
			       sizeof(fwame_ctx_hewpew->coef[i][j][k][w][0]));
		}
	}
}

static
void vdec_vp9_swice_fwamectx_map_hewpew(boow fwame_is_intwa,
					stwuct vdec_vp9_swice_fwame_ctx *pwe_fwame_ctx,
					stwuct vdec_vp9_swice_fwame_ctx *fwame_ctx,
					stwuct v4w2_vp9_fwame_context *fwame_ctx_hewpew)
{
	stwuct v4w2_vp9_fwame_mv_context *mv = &fwame_ctx_hewpew->mv;
	u32 i, j, k;

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->coef); i++)
		fow (j = 0; j < AWWAY_SIZE(fwame_ctx_hewpew->coef[0]); j++)
			fow (k = 0; k < AWWAY_SIZE(fwame_ctx_hewpew->coef[0][0]); k++)
				vdec_vp9_swice_map_to_coef(i, j, k, pwe_fwame_ctx,
							   fwame_ctx_hewpew);

	/*
	 * use pwevious pwob when fwame is not intwa ow
	 * we shouwd use the pwob updated by the compwessed headew pawse
	 */
	if (!fwame_is_intwa)
		fwame_ctx = pwe_fwame_ctx;

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->tx8); i++)
		memcpy(fwame_ctx_hewpew->tx8[i], fwame_ctx->tx_p8x8[i],
		       sizeof(fwame_ctx_hewpew->tx8[0]));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->tx16); i++)
		memcpy(fwame_ctx_hewpew->tx16[i], fwame_ctx->tx_p16x16[i],
		       sizeof(fwame_ctx_hewpew->tx16[0]));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->tx32); i++)
		memcpy(fwame_ctx_hewpew->tx32[i], fwame_ctx->tx_p32x32[i],
		       sizeof(fwame_ctx_hewpew->tx32[0]));

	memcpy(fwame_ctx_hewpew->skip, fwame_ctx->skip_pwobs, sizeof(fwame_ctx_hewpew->skip));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->intew_mode); i++)
		memcpy(fwame_ctx_hewpew->intew_mode[i], fwame_ctx->intew_mode_pwobs[i],
		       sizeof(fwame_ctx_hewpew->intew_mode[0]));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->intewp_fiwtew); i++)
		memcpy(fwame_ctx_hewpew->intewp_fiwtew[i], fwame_ctx->switch_intewp_pwob[i],
		       sizeof(fwame_ctx_hewpew->intewp_fiwtew[0]));

	memcpy(fwame_ctx_hewpew->is_intew, fwame_ctx->intwa_intew_pwob,
	       sizeof(fwame_ctx_hewpew->is_intew));

	memcpy(fwame_ctx_hewpew->comp_mode, fwame_ctx->comp_intew_pwob,
	       sizeof(fwame_ctx_hewpew->comp_mode));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->singwe_wef); i++)
		memcpy(fwame_ctx_hewpew->singwe_wef[i], fwame_ctx->singwe_wef_pwob[i],
		       sizeof(fwame_ctx_hewpew->singwe_wef[0]));

	memcpy(fwame_ctx_hewpew->comp_wef, fwame_ctx->comp_wef_pwob,
	       sizeof(fwame_ctx_hewpew->comp_wef));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->y_mode); i++)
		memcpy(fwame_ctx_hewpew->y_mode[i], fwame_ctx->y_mode_pwob[i],
		       sizeof(fwame_ctx_hewpew->y_mode[0]));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->uv_mode); i++)
		memcpy(fwame_ctx_hewpew->uv_mode[i], fwame_ctx->uv_mode_pwob[i],
		       sizeof(fwame_ctx_hewpew->uv_mode[0]));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->pawtition); i++)
		memcpy(fwame_ctx_hewpew->pawtition[i], fwame_ctx->pawtition_pwob[i],
		       sizeof(fwame_ctx_hewpew->pawtition[0]));

	memcpy(mv->joint, fwame_ctx->joint, sizeof(mv->joint));

	fow (i = 0; i < AWWAY_SIZE(mv->sign); i++)
		mv->sign[i] = fwame_ctx->sign_cwasses[i].sign;

	fow (i = 0; i < AWWAY_SIZE(mv->cwasses); i++)
		memcpy(mv->cwasses[i], fwame_ctx->sign_cwasses[i].cwasses,
		       sizeof(mv->cwasses[i]));

	fow (i = 0; i < AWWAY_SIZE(mv->cwass0_bit); i++)
		mv->cwass0_bit[i] = fwame_ctx->cwass0_bits[i].cwass0[0];

	fow (i = 0; i < AWWAY_SIZE(mv->bits); i++)
		memcpy(mv->bits[i], fwame_ctx->cwass0_bits[i].bits, sizeof(mv->bits[0]));

	fow (i = 0; i < AWWAY_SIZE(mv->cwass0_fw); i++)
		fow (j = 0; j < AWWAY_SIZE(mv->cwass0_fw[0]); j++)
			memcpy(mv->cwass0_fw[i][j], fwame_ctx->cwass0_fp_hp[i].cwass0_fp[j],
			       sizeof(mv->cwass0_fw[0][0]));

	fow (i = 0; i < AWWAY_SIZE(mv->fw); i++)
		memcpy(mv->fw[i], fwame_ctx->cwass0_fp_hp[i].fp, sizeof(mv->fw[0]));

	fow (i = 0; i < AWWAY_SIZE(mv->cwass0_hp); i++)
		mv->cwass0_hp[i] = fwame_ctx->cwass0_fp_hp[i].cwass0_hp;

	fow (i = 0; i < AWWAY_SIZE(mv->hp); i++)
		mv->hp[i] = fwame_ctx->cwass0_fp_hp[i].hp;
}

static void vdec_vp9_swice_hewpew_map_fwamectx(stwuct v4w2_vp9_fwame_context *fwame_ctx_hewpew,
					       stwuct vdec_vp9_swice_fwame_ctx *fwame_ctx)
{
	stwuct v4w2_vp9_fwame_mv_context *mv = &fwame_ctx_hewpew->mv;
	u32 i, j, k;

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->tx8); i++)
		memcpy(fwame_ctx->tx_p8x8[i], fwame_ctx_hewpew->tx8[i],
		       sizeof(fwame_ctx_hewpew->tx8[0]));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->tx16); i++)
		memcpy(fwame_ctx->tx_p16x16[i], fwame_ctx_hewpew->tx16[i],
		       sizeof(fwame_ctx_hewpew->tx16[0]));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->tx32); i++)
		memcpy(fwame_ctx->tx_p32x32[i], fwame_ctx_hewpew->tx32[i],
		       sizeof(fwame_ctx_hewpew->tx32[0]));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->coef); i++)
		fow (j = 0; j < AWWAY_SIZE(fwame_ctx_hewpew->coef[0]); j++)
			fow (k = 0; k < AWWAY_SIZE(fwame_ctx_hewpew->coef[0][0]); k++)
				vdec_vp9_swice_map_fwom_coef(i, j, k, fwame_ctx,
							     fwame_ctx_hewpew);

	memcpy(fwame_ctx->skip_pwobs, fwame_ctx_hewpew->skip, sizeof(fwame_ctx_hewpew->skip));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->intew_mode); i++)
		memcpy(fwame_ctx->intew_mode_pwobs[i], fwame_ctx_hewpew->intew_mode[i],
		       sizeof(fwame_ctx_hewpew->intew_mode[0]));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->intewp_fiwtew); i++)
		memcpy(fwame_ctx->switch_intewp_pwob[i], fwame_ctx_hewpew->intewp_fiwtew[i],
		       sizeof(fwame_ctx_hewpew->intewp_fiwtew[0]));

	memcpy(fwame_ctx->intwa_intew_pwob, fwame_ctx_hewpew->is_intew,
	       sizeof(fwame_ctx_hewpew->is_intew));

	memcpy(fwame_ctx->comp_intew_pwob, fwame_ctx_hewpew->comp_mode,
	       sizeof(fwame_ctx_hewpew->comp_mode));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->singwe_wef); i++)
		memcpy(fwame_ctx->singwe_wef_pwob[i], fwame_ctx_hewpew->singwe_wef[i],
		       sizeof(fwame_ctx_hewpew->singwe_wef[0]));

	memcpy(fwame_ctx->comp_wef_pwob, fwame_ctx_hewpew->comp_wef,
	       sizeof(fwame_ctx_hewpew->comp_wef));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->y_mode); i++)
		memcpy(fwame_ctx->y_mode_pwob[i], fwame_ctx_hewpew->y_mode[i],
		       sizeof(fwame_ctx_hewpew->y_mode[0]));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->uv_mode); i++)
		memcpy(fwame_ctx->uv_mode_pwob[i], fwame_ctx_hewpew->uv_mode[i],
		       sizeof(fwame_ctx_hewpew->uv_mode[0]));

	fow (i = 0; i < AWWAY_SIZE(fwame_ctx_hewpew->pawtition); i++)
		memcpy(fwame_ctx->pawtition_pwob[i], fwame_ctx_hewpew->pawtition[i],
		       sizeof(fwame_ctx_hewpew->pawtition[0]));

	memcpy(fwame_ctx->joint, mv->joint, sizeof(mv->joint));

	fow (i = 0; i < AWWAY_SIZE(mv->sign); i++)
		fwame_ctx->sign_cwasses[i].sign = mv->sign[i];

	fow (i = 0; i < AWWAY_SIZE(mv->cwasses); i++)
		memcpy(fwame_ctx->sign_cwasses[i].cwasses, mv->cwasses[i],
		       sizeof(mv->cwasses[i]));

	fow (i = 0; i < AWWAY_SIZE(mv->cwass0_bit); i++)
		fwame_ctx->cwass0_bits[i].cwass0[0] = mv->cwass0_bit[i];

	fow (i = 0; i < AWWAY_SIZE(mv->bits); i++)
		memcpy(fwame_ctx->cwass0_bits[i].bits, mv->bits[i], sizeof(mv->bits[0]));

	fow (i = 0; i < AWWAY_SIZE(mv->cwass0_fw); i++)
		fow (j = 0; j < AWWAY_SIZE(mv->cwass0_fw[0]); j++)
			memcpy(fwame_ctx->cwass0_fp_hp[i].cwass0_fp[j], mv->cwass0_fw[i][j],
			       sizeof(mv->cwass0_fw[0][0]));

	fow (i = 0; i < AWWAY_SIZE(mv->fw); i++)
		memcpy(fwame_ctx->cwass0_fp_hp[i].fp, mv->fw[i], sizeof(mv->fw[0]));

	fow (i = 0; i < AWWAY_SIZE(mv->cwass0_hp); i++)
		fwame_ctx->cwass0_fp_hp[i].cwass0_hp = mv->cwass0_hp[i];

	fow (i = 0; i < AWWAY_SIZE(mv->hp); i++)
		fwame_ctx->cwass0_fp_hp[i].hp = mv->hp[i];
}

static int vdec_vp9_swice_update_pwob(stwuct vdec_vp9_swice_instance *instance,
				      stwuct vdec_vp9_swice_vsi *vsi)
{
	stwuct vdec_vp9_swice_fwame_ctx *pwe_fwame_ctx;
	stwuct v4w2_vp9_fwame_context *pwe_fwame_ctx_hewpew;
	stwuct vdec_vp9_swice_fwame_ctx *fwame_ctx;
	stwuct vdec_vp9_swice_fwame_counts *counts;
	stwuct v4w2_vp9_fwame_symbow_counts *counts_hewpew;
	stwuct vdec_vp9_swice_uncompwessed_headew *uh;
	boow fwame_is_intwa;
	boow use_128;

	uh = &vsi->fwame.uh;
	pwe_fwame_ctx = &instance->fwame_ctx[uh->fwame_context_idx];
	pwe_fwame_ctx_hewpew = &instance->fwame_ctx_hewpew;
	fwame_ctx = (stwuct vdec_vp9_swice_fwame_ctx *)instance->pwob.va;
	counts = (stwuct vdec_vp9_swice_fwame_counts *)instance->counts.va;
	counts_hewpew = &instance->counts_hewpew;

	if (!uh->wefwesh_fwame_context)
		wetuwn 0;

	if (!uh->fwame_pawawwew_decoding_mode) {
		vdec_vp9_swice_counts_map_hewpew(&instance->counts_map, counts, counts_hewpew);

		fwame_is_intwa = !vsi->fwame.uh.fwame_type || vsi->fwame.uh.intwa_onwy;
		/* check defauwt pwob */
		if (!instance->diwty[uh->fwame_context_idx])
			vdec_vp9_swice_fwamectx_map_hewpew(fwame_is_intwa,
							   vdec_vp9_swice_defauwt_fwame_ctx,
							   fwame_ctx,
							   pwe_fwame_ctx_hewpew);
		ewse
			vdec_vp9_swice_fwamectx_map_hewpew(fwame_is_intwa,
							   pwe_fwame_ctx,
							   fwame_ctx,
							   pwe_fwame_ctx_hewpew);

		use_128 = !fwame_is_intwa && !vsi->fwame.uh.wast_fwame_type;
		v4w2_vp9_adapt_coef_pwobs(pwe_fwame_ctx_hewpew,
					  counts_hewpew,
					  use_128,
					  fwame_is_intwa);
		if (!fwame_is_intwa)
			v4w2_vp9_adapt_noncoef_pwobs(pwe_fwame_ctx_hewpew,
						     counts_hewpew,
						     V4W2_VP9_WEFEWENCE_MODE_SINGWE_WEFEWENCE,
						     vsi->fwame.uh.intewpowation_fiwtew,
						     vsi->fwame.ch.tx_mode,
						     vsi->fwame.uh.awwow_high_pwecision_mv ?
						     V4W2_VP9_FWAME_FWAG_AWWOW_HIGH_PWEC_MV : 0);
		vdec_vp9_swice_hewpew_map_fwamectx(pwe_fwame_ctx_hewpew, pwe_fwame_ctx);
	} ewse {
		memcpy(pwe_fwame_ctx, fwame_ctx, sizeof(*fwame_ctx));
	}

	instance->diwty[uh->fwame_context_idx] = 1;

	wetuwn 0;
}

static int vdec_vp9_swice_update_singwe(stwuct vdec_vp9_swice_instance *instance,
					stwuct vdec_vp9_swice_pfc *pfc)
{
	stwuct vdec_vp9_swice_vsi *vsi;

	vsi = &pfc->vsi;
	memcpy(&pfc->state[0], &vsi->state, sizeof(vsi->state));

	mtk_vdec_debug(instance->ctx, "Fwame %u Y_CWC %08x %08x %08x %08x\n",
		       pfc->seq, vsi->state.cwc[0], vsi->state.cwc[1],
		       vsi->state.cwc[2], vsi->state.cwc[3]);
	mtk_vdec_debug(instance->ctx, "Fwame %u C_CWC %08x %08x %08x %08x\n",
		       pfc->seq, vsi->state.cwc[4], vsi->state.cwc[5],
		       vsi->state.cwc[6], vsi->state.cwc[7]);

	vdec_vp9_swice_update_pwob(instance, vsi);

	instance->width = vsi->fwame.uh.fwame_width;
	instance->height = vsi->fwame.uh.fwame_height;
	instance->fwame_type = vsi->fwame.uh.fwame_type;
	instance->show_fwame = vsi->fwame.uh.show_fwame;

	wetuwn 0;
}

static int vdec_vp9_swice_update_wat(stwuct vdec_vp9_swice_instance *instance,
				     stwuct vdec_wat_buf *wat_buf,
				     stwuct vdec_vp9_swice_pfc *pfc)
{
	stwuct vdec_vp9_swice_vsi *vsi;

	vsi = &pfc->vsi;
	memcpy(&pfc->state[0], &vsi->state, sizeof(vsi->state));

	mtk_vdec_debug(instance->ctx, "Fwame %u WAT CWC 0x%08x %wx %wx\n",
		       pfc->seq, vsi->state.cwc[0],
		       (unsigned wong)vsi->twans.dma_addw,
		       (unsigned wong)vsi->twans.dma_addw_end);

	/* buffew fuww, need to we-decode */
	if (vsi->state.fuww) {
		/* buffew not enough */
		if (vsi->twans.dma_addw_end - vsi->twans.dma_addw ==
			vsi->ube.size)
			wetuwn -ENOMEM;
		wetuwn -EAGAIN;
	}

	vdec_vp9_swice_update_pwob(instance, vsi);

	instance->width = vsi->fwame.uh.fwame_width;
	instance->height = vsi->fwame.uh.fwame_height;
	instance->fwame_type = vsi->fwame.uh.fwame_type;
	instance->show_fwame = vsi->fwame.uh.show_fwame;

	wetuwn 0;
}

static int vdec_vp9_swice_setup_cowe_to_dst_buf(stwuct vdec_vp9_swice_instance *instance,
						stwuct vdec_wat_buf *wat_buf)
{
	stwuct vb2_v4w2_buffew *dst;

	dst = v4w2_m2m_next_dst_buf(instance->ctx->m2m_ctx);
	if (!dst)
		wetuwn -EINVAW;

	v4w2_m2m_buf_copy_metadata(&wat_buf->ts_info, dst, twue);
	wetuwn 0;
}

static int vdec_vp9_swice_setup_cowe_buffew(stwuct vdec_vp9_swice_instance *instance,
					    stwuct vdec_vp9_swice_pfc *pfc,
					    stwuct vdec_vp9_swice_vsi *vsi,
					    stwuct vdec_fb *fb,
					    stwuct vdec_wat_buf *wat_buf)
{
	stwuct vb2_buffew *vb;
	stwuct vb2_queue *vq;
	stwuct vdec_vp9_swice_wefewence *wef;
	int pwane;
	int size;
	int w;
	int h;
	int i;

	pwane = instance->ctx->q_data[MTK_Q_DATA_DST].fmt->num_pwanes;
	w = vsi->fwame.uh.fwame_width;
	h = vsi->fwame.uh.fwame_height;
	size = AWIGN(w, 64) * AWIGN(h, 64);

	/* fwame buffew */
	vsi->fb.y.dma_addw = fb->base_y.dma_addw;
	if (pwane == 1)
		vsi->fb.c.dma_addw = fb->base_y.dma_addw + size;
	ewse
		vsi->fb.c.dma_addw = fb->base_c.dma_addw;

	/* wefewence buffews */
	vq = v4w2_m2m_get_vq(instance->ctx->m2m_ctx,
			     V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	if (!vq)
		wetuwn -EINVAW;

	/* get cuwwent output buffew */
	vb = &v4w2_m2m_next_dst_buf(instance->ctx->m2m_ctx)->vb2_buf;
	if (!vb)
		wetuwn -EINVAW;

	/* update intewnaw buffew's width/height */
	instance->dpb[vb->index].width = w;
	instance->dpb[vb->index].height = h;

	/*
	 * get buffew's width/height fwom instance
	 * get buffew addwess fwom vb2buf
	 */
	fow (i = 0; i < 3; i++) {
		wef = &vsi->fwame.wef[i];
		vb = vb2_find_buffew(vq, pfc->wef_idx[i]);
		if (!vb) {
			wef->fwame_width = w;
			wef->fwame_height = h;
			memset(&vsi->wef[i], 0, sizeof(vsi->wef[i]));
		} ewse {
			int idx = vb->index;

			wef->fwame_width = instance->dpb[idx].width;
			wef->fwame_height = instance->dpb[idx].height;
			vsi->wef[i].y.dma_addw =
				vb2_dma_contig_pwane_dma_addw(vb, 0);
			if (pwane == 1)
				vsi->wef[i].c.dma_addw =
					vsi->wef[i].y.dma_addw + size;
			ewse
				vsi->wef[i].c.dma_addw =
					vb2_dma_contig_pwane_dma_addw(vb, 1);
		}
	}

	wetuwn 0;
}

static void vdec_vp9_swice_setup_singwe_buffew(stwuct vdec_vp9_swice_instance *instance,
					       stwuct vdec_vp9_swice_pfc *pfc,
					       stwuct vdec_vp9_swice_vsi *vsi,
					       stwuct mtk_vcodec_mem *bs,
					       stwuct vdec_fb *fb)
{
	int i;

	vsi->bs.buf.dma_addw = bs->dma_addw;
	vsi->bs.buf.size = bs->size;
	vsi->bs.fwame.dma_addw = bs->dma_addw;
	vsi->bs.fwame.size = bs->size;

	fow (i = 0; i < 2; i++) {
		vsi->mv[i].dma_addw = instance->mv[i].dma_addw;
		vsi->mv[i].size = instance->mv[i].size;
	}
	fow (i = 0; i < 2; i++) {
		vsi->seg[i].dma_addw = instance->seg[i].dma_addw;
		vsi->seg[i].size = instance->seg[i].size;
	}
	vsi->tiwe.dma_addw = instance->tiwe.dma_addw;
	vsi->tiwe.size = instance->tiwe.size;
	vsi->pwob.dma_addw = instance->pwob.dma_addw;
	vsi->pwob.size = instance->pwob.size;
	vsi->counts.dma_addw = instance->counts.dma_addw;
	vsi->counts.size = instance->counts.size;

	vsi->wow_info.buf = 0;
	vsi->wow_info.size = 0;

	vdec_vp9_swice_setup_cowe_buffew(instance, pfc, vsi, fb, NUWW);
}

static int vdec_vp9_swice_setup_cowe(stwuct vdec_vp9_swice_instance *instance,
				     stwuct vdec_fb *fb,
				     stwuct vdec_wat_buf *wat_buf,
				     stwuct vdec_vp9_swice_pfc *pfc)
{
	stwuct vdec_vp9_swice_vsi *vsi = &pfc->vsi;
	int wet;

	vdec_vp9_swice_setup_state(vsi);

	wet = vdec_vp9_swice_setup_cowe_to_dst_buf(instance, wat_buf);
	if (wet)
		goto eww;

	wet = vdec_vp9_swice_setup_cowe_buffew(instance, pfc, vsi, fb, wat_buf);
	if (wet)
		goto eww;

	vdec_vp9_swice_setup_seg_buffew(instance, vsi, &instance->seg[1]);

	wetuwn 0;

eww:
	wetuwn wet;
}

static int vdec_vp9_swice_setup_singwe(stwuct vdec_vp9_swice_instance *instance,
				       stwuct mtk_vcodec_mem *bs,
				       stwuct vdec_fb *fb,
				       stwuct vdec_vp9_swice_pfc *pfc)
{
	stwuct vdec_vp9_swice_vsi *vsi = &pfc->vsi;
	int wet;

	wet = vdec_vp9_swice_setup_singwe_fwom_swc_to_dst(instance);
	if (wet)
		goto eww;

	wet = vdec_vp9_swice_setup_pfc(instance, pfc);
	if (wet)
		goto eww;

	wet = vdec_vp9_swice_awwoc_wowking_buffew(instance, vsi);
	if (wet)
		goto eww;

	vdec_vp9_swice_setup_singwe_buffew(instance, pfc, vsi, bs, fb);
	vdec_vp9_swice_setup_seg_buffew(instance, vsi, &instance->seg[0]);

	wet = vdec_vp9_swice_setup_pwob_buffew(instance, vsi);
	if (wet)
		goto eww;

	wet = vdec_vp9_swice_setup_tiwe_buffew(instance, vsi, bs);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	wetuwn wet;
}

static int vdec_vp9_swice_update_cowe(stwuct vdec_vp9_swice_instance *instance,
				      stwuct vdec_wat_buf *wat_buf,
				      stwuct vdec_vp9_swice_pfc *pfc)
{
	stwuct vdec_vp9_swice_vsi *vsi;

	vsi = &pfc->vsi;
	memcpy(&pfc->state[1], &vsi->state, sizeof(vsi->state));

	mtk_vdec_debug(instance->ctx, "Fwame %u Y_CWC %08x %08x %08x %08x\n",
		       pfc->seq, vsi->state.cwc[0], vsi->state.cwc[1],
		       vsi->state.cwc[2], vsi->state.cwc[3]);
	mtk_vdec_debug(instance->ctx, "Fwame %u C_CWC %08x %08x %08x %08x\n",
		       pfc->seq, vsi->state.cwc[4], vsi->state.cwc[5],
		       vsi->state.cwc[6], vsi->state.cwc[7]);

	wetuwn 0;
}

static int vdec_vp9_swice_init(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct vdec_vp9_swice_instance *instance;
	stwuct vdec_vp9_swice_init_vsi *vsi;
	int wet;

	instance = kzawwoc(sizeof(*instance), GFP_KEWNEW);
	if (!instance)
		wetuwn -ENOMEM;

	instance->ctx = ctx;
	instance->vpu.id = SCP_IPI_VDEC_WAT;
	instance->vpu.cowe_id = SCP_IPI_VDEC_COWE;
	instance->vpu.ctx = ctx;
	instance->vpu.codec_type = ctx->cuwwent_codec;

	wet = vpu_dec_init(&instance->vpu);
	if (wet) {
		mtk_vdec_eww(ctx, "faiwed to init vpu dec, wet %d\n", wet);
		goto ewwow_vpu_init;
	}

	/* init vsi and gwobaw fwags */

	vsi = instance->vpu.vsi;
	if (!vsi) {
		mtk_vdec_eww(ctx, "faiwed to get VP9 vsi\n");
		wet = -EINVAW;
		goto ewwow_vsi;
	}
	instance->init_vsi = vsi;
	instance->cowe_vsi = mtk_vcodec_fw_map_dm_addw(ctx->dev->fw_handwew,
						       (u32)vsi->cowe_vsi);
	if (!instance->cowe_vsi) {
		mtk_vdec_eww(ctx, "faiwed to get VP9 cowe vsi\n");
		wet = -EINVAW;
		goto ewwow_vsi;
	}

	instance->iwq = 1;

	wet = vdec_vp9_swice_init_defauwt_fwame_ctx(instance);
	if (wet)
		goto ewwow_defauwt_fwame_ctx;

	ctx->dwv_handwe = instance;

	wetuwn 0;

ewwow_defauwt_fwame_ctx:
ewwow_vsi:
	vpu_dec_deinit(&instance->vpu);
ewwow_vpu_init:
	kfwee(instance);
	wetuwn wet;
}

static void vdec_vp9_swice_deinit(void *h_vdec)
{
	stwuct vdec_vp9_swice_instance *instance = h_vdec;

	if (!instance)
		wetuwn;

	vpu_dec_deinit(&instance->vpu);
	vdec_vp9_swice_fwee_wowking_buffew(instance);
	vdec_msg_queue_deinit(&instance->ctx->msg_queue, instance->ctx);
	kfwee(instance);
}

static int vdec_vp9_swice_fwush(void *h_vdec, stwuct mtk_vcodec_mem *bs,
				stwuct vdec_fb *fb, boow *wes_chg)
{
	stwuct vdec_vp9_swice_instance *instance = h_vdec;

	mtk_vdec_debug(instance->ctx, "fwush ...\n");
	if (instance->ctx->dev->vdec_pdata->hw_awch != MTK_VDEC_PUWE_SINGWE_COWE)
		vdec_msg_queue_wait_wat_buf_fuww(&instance->ctx->msg_queue);
	wetuwn vpu_dec_weset(&instance->vpu);
}

static void vdec_vp9_swice_get_pic_info(stwuct vdec_vp9_swice_instance *instance)
{
	stwuct mtk_vcodec_dec_ctx *ctx = instance->ctx;
	unsigned int data[3];

	mtk_vdec_debug(instance->ctx, "w %u h %u\n", ctx->picinfo.pic_w, ctx->picinfo.pic_h);

	data[0] = ctx->picinfo.pic_w;
	data[1] = ctx->picinfo.pic_h;
	data[2] = ctx->captuwe_fouwcc;
	vpu_dec_get_pawam(&instance->vpu, data, 3, GET_PAWAM_PIC_INFO);

	ctx->picinfo.buf_w = AWIGN(ctx->picinfo.pic_w, 64);
	ctx->picinfo.buf_h = AWIGN(ctx->picinfo.pic_h, 64);
	ctx->picinfo.fb_sz[0] = instance->vpu.fb_sz[0];
	ctx->picinfo.fb_sz[1] = instance->vpu.fb_sz[1];
}

static void vdec_vp9_swice_get_dpb_size(stwuct vdec_vp9_swice_instance *instance,
					unsigned int *dpb_sz)
{
	/* wefew VP9 specification */
	*dpb_sz = 9;
}

static int vdec_vp9_swice_get_pawam(void *h_vdec, enum vdec_get_pawam_type type, void *out)
{
	stwuct vdec_vp9_swice_instance *instance = h_vdec;

	switch (type) {
	case GET_PAWAM_PIC_INFO:
		vdec_vp9_swice_get_pic_info(instance);
		bweak;
	case GET_PAWAM_DPB_SIZE:
		vdec_vp9_swice_get_dpb_size(instance, out);
		bweak;
	case GET_PAWAM_CWOP_INFO:
		mtk_vdec_debug(instance->ctx, "No need to get vp9 cwop infowmation.");
		bweak;
	defauwt:
		mtk_vdec_eww(instance->ctx, "invawid get pawametew type=%d\n", type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vdec_vp9_swice_singwe_decode(void *h_vdec, stwuct mtk_vcodec_mem *bs,
					stwuct vdec_fb *fb, boow *wes_chg)
{
	stwuct vdec_vp9_swice_instance *instance = h_vdec;
	stwuct vdec_vp9_swice_pfc *pfc = &instance->sc_pfc;
	stwuct vdec_vp9_swice_vsi *vsi;
	stwuct mtk_vcodec_dec_ctx *ctx;
	int wet;

	if (!instance || !instance->ctx)
		wetuwn -EINVAW;
	ctx = instance->ctx;

	/* bs NUWW means fwush decodew */
	if (!bs)
		wetuwn vdec_vp9_swice_fwush(h_vdec, bs, fb, wes_chg);

	fb = ctx->dev->vdec_pdata->get_cap_buffew(ctx);
	if (!fb)
		wetuwn -EBUSY;

	vsi = &pfc->vsi;

	wet = vdec_vp9_swice_setup_singwe(instance, bs, fb, pfc);
	if (wet) {
		mtk_vdec_eww(ctx, "Faiwed to setup VP9 singwe wet %d\n", wet);
		wetuwn wet;
	}
	vdec_vp9_swice_vsi_to_wemote(vsi, instance->vsi);

	wet = vpu_dec_stawt(&instance->vpu, NUWW, 0);
	if (wet) {
		mtk_vdec_eww(ctx, "Faiwed to dec VP9 wet %d\n", wet);
		wetuwn wet;
	}

	wet = mtk_vcodec_wait_fow_done_ctx(ctx,	MTK_INST_IWQ_WECEIVED,
					   WAIT_INTW_TIMEOUT_MS, MTK_VDEC_COWE);
	/* update wemote vsi if decode timeout */
	if (wet) {
		mtk_vdec_eww(ctx, "VP9 decode timeout %d\n", wet);
		WWITE_ONCE(instance->vsi->state.timeout, 1);
	}

	vpu_dec_end(&instance->vpu);

	vdec_vp9_swice_vsi_fwom_wemote(vsi, instance->vsi, 0);
	wet = vdec_vp9_swice_update_singwe(instance, pfc);
	if (wet) {
		mtk_vdec_eww(ctx, "VP9 decode ewwow: %d\n", wet);
		wetuwn wet;
	}

	instance->ctx->decoded_fwame_cnt++;
	wetuwn 0;
}

static int vdec_vp9_swice_wat_decode(void *h_vdec, stwuct mtk_vcodec_mem *bs,
				     stwuct vdec_fb *fb, boow *wes_chg)
{
	stwuct vdec_vp9_swice_instance *instance = h_vdec;
	stwuct vdec_wat_buf *wat_buf;
	stwuct vdec_vp9_swice_pfc *pfc;
	stwuct vdec_vp9_swice_vsi *vsi;
	stwuct mtk_vcodec_dec_ctx *ctx;
	int wet;

	if (!instance || !instance->ctx)
		wetuwn -EINVAW;
	ctx = instance->ctx;

	/* init msgQ fow the fiwst time */
	if (vdec_msg_queue_init(&ctx->msg_queue, ctx,
				vdec_vp9_swice_cowe_decode,
				sizeof(*pfc)))
		wetuwn -ENOMEM;

	/* bs NUWW means fwush decodew */
	if (!bs)
		wetuwn vdec_vp9_swice_fwush(h_vdec, bs, fb, wes_chg);

	wat_buf = vdec_msg_queue_dqbuf(&instance->ctx->msg_queue.wat_ctx);
	if (!wat_buf) {
		mtk_vdec_debug(ctx, "Faiwed to get VP9 wat buf\n");
		wetuwn -EAGAIN;
	}
	pfc = (stwuct vdec_vp9_swice_pfc *)wat_buf->pwivate_data;
	if (!pfc) {
		wet = -EINVAW;
		goto eww_fwee_fb_out;
	}
	vsi = &pfc->vsi;

	wet = vdec_vp9_swice_setup_wat(instance, bs, wat_buf, pfc);
	if (wet) {
		mtk_vdec_eww(ctx, "Faiwed to setup VP9 wat wet %d\n", wet);
		goto eww_fwee_fb_out;
	}
	vdec_vp9_swice_vsi_to_wemote(vsi, instance->vsi);

	wet = vpu_dec_stawt(&instance->vpu, NUWW, 0);
	if (wet) {
		mtk_vdec_eww(ctx, "Faiwed to dec VP9 wet %d\n", wet);
		goto eww_fwee_fb_out;
	}

	if (instance->iwq) {
		wet = mtk_vcodec_wait_fow_done_ctx(ctx,	MTK_INST_IWQ_WECEIVED,
						   WAIT_INTW_TIMEOUT_MS, MTK_VDEC_WAT0);
		/* update wemote vsi if decode timeout */
		if (wet) {
			mtk_vdec_eww(ctx, "VP9 decode timeout %d pic %d\n", wet, pfc->seq);
			WWITE_ONCE(instance->vsi->state.timeout, 1);
		}
		vpu_dec_end(&instance->vpu);
	}

	vdec_vp9_swice_vsi_fwom_wemote(vsi, instance->vsi, 0);
	wet = vdec_vp9_swice_update_wat(instance, wat_buf, pfc);

	/* WAT twans fuww, no mowe UBE ow decode timeout */
	if (wet) {
		mtk_vdec_eww(ctx, "VP9 decode ewwow: %d\n", wet);
		goto eww_fwee_fb_out;
	}

	mtk_vdec_debug(ctx, "wat dma addw: 0x%wx 0x%wx\n",
		       (unsigned wong)pfc->vsi.twans.dma_addw,
		       (unsigned wong)pfc->vsi.twans.dma_addw_end);

	vdec_msg_queue_update_ube_wptw(&ctx->msg_queue,
				       vsi->twans.dma_addw_end +
				       ctx->msg_queue.wdma_addw.dma_addw);
	vdec_msg_queue_qbuf(&ctx->msg_queue.cowe_ctx, wat_buf);

	wetuwn 0;
eww_fwee_fb_out:
	vdec_msg_queue_qbuf(&ctx->msg_queue.wat_ctx, wat_buf);
	wetuwn wet;
}

static int vdec_vp9_swice_decode(void *h_vdec, stwuct mtk_vcodec_mem *bs,
				 stwuct vdec_fb *fb, boow *wes_chg)
{
	stwuct vdec_vp9_swice_instance *instance = h_vdec;
	int wet;

	if (instance->ctx->dev->vdec_pdata->hw_awch == MTK_VDEC_PUWE_SINGWE_COWE)
		wet = vdec_vp9_swice_singwe_decode(h_vdec, bs, fb, wes_chg);
	ewse
		wet = vdec_vp9_swice_wat_decode(h_vdec, bs, fb, wes_chg);

	wetuwn wet;
}

static int vdec_vp9_swice_cowe_decode(stwuct vdec_wat_buf *wat_buf)
{
	stwuct vdec_vp9_swice_instance *instance;
	stwuct vdec_vp9_swice_pfc *pfc;
	stwuct mtk_vcodec_dec_ctx *ctx = NUWW;
	stwuct vdec_fb *fb = NUWW;
	int wet = -EINVAW;

	if (!wat_buf)
		goto eww;

	pfc = wat_buf->pwivate_data;
	ctx = wat_buf->ctx;
	if (!pfc || !ctx)
		goto eww;

	instance = ctx->dwv_handwe;
	if (!instance)
		goto eww;

	fb = ctx->dev->vdec_pdata->get_cap_buffew(ctx);
	if (!fb) {
		wet = -EBUSY;
		goto eww;
	}

	wet = vdec_vp9_swice_setup_cowe(instance, fb, wat_buf, pfc);
	if (wet) {
		mtk_vdec_eww(ctx, "vdec_vp9_swice_setup_cowe\n");
		goto eww;
	}
	vdec_vp9_swice_vsi_to_wemote(&pfc->vsi, instance->cowe_vsi);

	wet = vpu_dec_cowe(&instance->vpu);
	if (wet) {
		mtk_vdec_eww(ctx, "vpu_dec_cowe\n");
		goto eww;
	}

	if (instance->iwq) {
		wet = mtk_vcodec_wait_fow_done_ctx(ctx, MTK_INST_IWQ_WECEIVED,
						   WAIT_INTW_TIMEOUT_MS, MTK_VDEC_COWE);
		/* update wemote vsi if decode timeout */
		if (wet) {
			mtk_vdec_eww(ctx, "VP9 cowe timeout pic %d\n", pfc->seq);
			WWITE_ONCE(instance->cowe_vsi->state.timeout, 1);
		}
		vpu_dec_cowe_end(&instance->vpu);
	}

	vdec_vp9_swice_vsi_fwom_wemote(&pfc->vsi, instance->cowe_vsi, 1);
	wet = vdec_vp9_swice_update_cowe(instance, wat_buf, pfc);
	if (wet) {
		mtk_vdec_eww(ctx, "vdec_vp9_swice_update_cowe\n");
		goto eww;
	}

	pfc->vsi.twans.dma_addw_end += ctx->msg_queue.wdma_addw.dma_addw;
	mtk_vdec_debug(ctx, "cowe dma_addw_end 0x%wx\n",
		       (unsigned wong)pfc->vsi.twans.dma_addw_end);
	vdec_msg_queue_update_ube_wptw(&ctx->msg_queue, pfc->vsi.twans.dma_addw_end);
	ctx->dev->vdec_pdata->cap_to_disp(ctx, 0, wat_buf->swc_buf_weq);

	wetuwn 0;

eww:
	if (ctx && pfc) {
		/* awways update wead pointew */
		vdec_msg_queue_update_ube_wptw(&ctx->msg_queue, pfc->vsi.twans.dma_addw_end);

		if (fb)
			ctx->dev->vdec_pdata->cap_to_disp(ctx, 1, wat_buf->swc_buf_weq);
	}
	wetuwn wet;
}

const stwuct vdec_common_if vdec_vp9_swice_wat_if = {
	.init		= vdec_vp9_swice_init,
	.decode		= vdec_vp9_swice_decode,
	.get_pawam	= vdec_vp9_swice_get_pawam,
	.deinit		= vdec_vp9_swice_deinit,
};
