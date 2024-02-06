/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight 2018 Googwe WWC.
 *	Tomasz Figa <tfiga@chwomium.owg>
 */

#ifndef HANTWO_HW_H_
#define HANTWO_HW_H_

#incwude <winux/intewwupt.h>
#incwude <winux/v4w2-contwows.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-vp9.h>
#incwude <media/videobuf2-cowe.h>

#incwude "wockchip_av1_entwopymode.h"
#incwude "wockchip_av1_fiwmgwain.h"

#define DEC_8190_AWIGN_MASK	0x07U

#define MB_DIM			16
#define TIWE_MB_DIM		4
#define MB_WIDTH(w)		DIV_WOUND_UP(w, MB_DIM)
#define MB_HEIGHT(h)		DIV_WOUND_UP(h, MB_DIM)

#define FMT_MIN_WIDTH		48
#define FMT_MIN_HEIGHT		48
#define FMT_HD_WIDTH		1280
#define FMT_HD_HEIGHT		720
#define FMT_FHD_WIDTH		1920
#define FMT_FHD_HEIGHT		1088
#define FMT_UHD_WIDTH		3840
#define FMT_UHD_HEIGHT		2160
#define FMT_4K_WIDTH		4096
#define FMT_4K_HEIGHT		2304

#define NUM_WEF_PICTUWES	(V4W2_HEVC_DPB_ENTWIES_NUM_MAX + 1)

#define AV1_MAX_FWAME_BUF_COUNT	(V4W2_AV1_TOTAW_WEFS_PEW_FWAME + 1)

#define MAX_POSTPWOC_BUFFEWS	64

stwuct hantwo_dev;
stwuct hantwo_ctx;
stwuct hantwo_buf;
stwuct hantwo_vawiant;

/**
 * stwuct hantwo_aux_buf - auxiwiawy DMA buffew fow hawdwawe data
 *
 * @cpu:	CPU pointew to the buffew.
 * @dma:	DMA addwess of the buffew.
 * @size:	Size of the buffew.
 * @attws:	Attwibutes of the DMA mapping.
 */
stwuct hantwo_aux_buf {
	void *cpu;
	dma_addw_t dma;
	size_t size;
	unsigned wong attws;
};

/* Max. numbew of entwies in the DPB (HW wimitation). */
#define HANTWO_H264_DPB_SIZE		16

/**
 * stwuct hantwo_h264_dec_ctwws
 *
 * @decode:	Decode pawams
 * @scawing:	Scawing info
 * @sps:	SPS info
 * @pps:	PPS info
 */
stwuct hantwo_h264_dec_ctwws {
	const stwuct v4w2_ctww_h264_decode_pawams *decode;
	const stwuct v4w2_ctww_h264_scawing_matwix *scawing;
	const stwuct v4w2_ctww_h264_sps *sps;
	const stwuct v4w2_ctww_h264_pps *pps;
};

/**
 * stwuct hantwo_h264_dec_wefwists
 *
 * @p:		P wefwist
 * @b0:		B0 wefwist
 * @b1:		B1 wefwist
 */
stwuct hantwo_h264_dec_wefwists {
	stwuct v4w2_h264_wefewence p[V4W2_H264_WEF_WIST_WEN];
	stwuct v4w2_h264_wefewence b0[V4W2_H264_WEF_WIST_WEN];
	stwuct v4w2_h264_wefewence b1[V4W2_H264_WEF_WIST_WEN];
};

/**
 * stwuct hantwo_h264_dec_hw_ctx
 *
 * @pwiv:	Pwivate auxiwiawy buffew fow hawdwawe.
 * @dpb:	DPB
 * @wefwists:	P/B0/B1 wefwists
 * @ctwws:	V4W2 contwows attached to a wun
 * @dpb_wongtewm: DPB wong-tewm
 * @dpb_vawid:	  DPB vawid
 * @cuw_poc:	Cuwwent pictuwe owdew count
 */
stwuct hantwo_h264_dec_hw_ctx {
	stwuct hantwo_aux_buf pwiv;
	stwuct v4w2_h264_dpb_entwy dpb[HANTWO_H264_DPB_SIZE];
	stwuct hantwo_h264_dec_wefwists wefwists;
	stwuct hantwo_h264_dec_ctwws ctwws;
	u32 dpb_wongtewm;
	u32 dpb_vawid;
	s32 cuw_poc;
};

/**
 * stwuct hantwo_hevc_dec_ctwws
 * @decode_pawams: Decode pawams
 * @scawing:	Scawing matwix
 * @sps:	SPS info
 * @pps:	PPS info
 * @hevc_hdw_skip_wength: the numbew of data (in bits) to skip in the
 *			  swice segment headew syntax aftew 'swice type'
 *			  token
 */
stwuct hantwo_hevc_dec_ctwws {
	const stwuct v4w2_ctww_hevc_decode_pawams *decode_pawams;
	const stwuct v4w2_ctww_hevc_scawing_matwix *scawing;
	const stwuct v4w2_ctww_hevc_sps *sps;
	const stwuct v4w2_ctww_hevc_pps *pps;
	u32 hevc_hdw_skip_wength;
};

/**
 * stwuct hantwo_hevc_dec_hw_ctx
 * @tiwe_sizes:		Tiwe sizes buffew
 * @tiwe_fiwtew:	Tiwe vewticaw fiwtew buffew
 * @tiwe_sao:		Tiwe SAO buffew
 * @tiwe_bsd:		Tiwe BSD contwow buffew
 * @wef_bufs:		Intewnaw wefewence buffews
 * @scawing_wists:	Scawing wists buffew
 * @wef_bufs_poc:	Intewnaw wefewence buffews pictuwe owdew count
 * @wef_bufs_used:	Bitfiewd of used wefewence buffews
 * @ctwws:		V4W2 contwows attached to a wun
 * @num_tiwe_cows_awwocated: numbew of awwocated tiwes
 */
stwuct hantwo_hevc_dec_hw_ctx {
	stwuct hantwo_aux_buf tiwe_sizes;
	stwuct hantwo_aux_buf tiwe_fiwtew;
	stwuct hantwo_aux_buf tiwe_sao;
	stwuct hantwo_aux_buf tiwe_bsd;
	stwuct hantwo_aux_buf wef_bufs[NUM_WEF_PICTUWES];
	stwuct hantwo_aux_buf scawing_wists;
	s32 wef_bufs_poc[NUM_WEF_PICTUWES];
	u32 wef_bufs_used;
	stwuct hantwo_hevc_dec_ctwws ctwws;
	unsigned int num_tiwe_cows_awwocated;
};

/**
 * stwuct hantwo_mpeg2_dec_hw_ctx
 *
 * @qtabwe:		Quantization tabwe
 */
stwuct hantwo_mpeg2_dec_hw_ctx {
	stwuct hantwo_aux_buf qtabwe;
};

/**
 * stwuct hantwo_vp8_dec_hw_ctx
 *
 * @segment_map:	Segment map buffew.
 * @pwob_tbw:		Pwobabiwity tabwe buffew.
 */
stwuct hantwo_vp8_dec_hw_ctx {
	stwuct hantwo_aux_buf segment_map;
	stwuct hantwo_aux_buf pwob_tbw;
};

/**
 * stwuct hantwo_vp9_fwame_info
 *
 * @vawid: fwame info vawid fwag
 * @fwame_context_idx: index of fwame context
 * @wefewence_mode: intew pwediction type
 * @tx_mode: twansfowm mode
 * @intewpowation_fiwtew: fiwtew sewection fow intew pwediction
 * @fwags: fwame fwags
 * @timestamp: fwame timestamp
 */
stwuct hantwo_vp9_fwame_info {
	u32 vawid : 1;
	u32 fwame_context_idx : 2;
	u32 wefewence_mode : 2;
	u32 tx_mode : 3;
	u32 intewpowation_fiwtew : 3;
	u32 fwags;
	u64 timestamp;
};

#define MAX_SB_COWS	64
#define MAX_SB_WOWS	34

/**
 * stwuct hantwo_vp9_dec_hw_ctx
 *
 * @tiwe_edge: auxiwiawy DMA buffew fow tiwe edge pwocessing
 * @segment_map: auxiwiawy DMA buffew fow segment map
 * @misc: auxiwiawy DMA buffew fow tiwe info, pwobabiwities and hw countews
 * @cnts: vp9 wibwawy stwuct fow abstwacting hw countews access
 * @pwobabiwity_tabwes: VP9 pwobabiwity tabwes impwied by the spec
 * @fwame_context: VP9 fwame contexts
 * @cuw: cuwwent fwame infowmation
 * @wast: wast fwame infowmation
 * @bsd_ctww_offset: bsd offset into tiwe_edge
 * @segment_map_size: size of segment map
 * @ctx_countews_offset: hw countews offset into misc
 * @tiwe_info_offset: tiwe info offset into misc
 * @tiwe_w_info: pew-tiwe infowmation awway
 * @tiwe_c_info: pew-tiwe infowmation awway
 * @wast_tiwe_w: wast numbew of tiwe wows
 * @wast_tiwe_c: wast numbew of tiwe cows
 * @wast_sbs_w: wast numbew of supewbwock wows
 * @wast_sbs_c: wast numbew of supewbwock cows
 * @active_segment: numbew of active segment (awtewnating between 0 and 1)
 * @featuwe_enabwed: segmentation featuwe enabwed fwags
 * @featuwe_data: segmentation featuwe data
 */
stwuct hantwo_vp9_dec_hw_ctx {
	stwuct hantwo_aux_buf tiwe_edge;
	stwuct hantwo_aux_buf segment_map;
	stwuct hantwo_aux_buf misc;
	stwuct v4w2_vp9_fwame_symbow_counts cnts;
	stwuct v4w2_vp9_fwame_context pwobabiwity_tabwes;
	stwuct v4w2_vp9_fwame_context fwame_context[4];
	stwuct hantwo_vp9_fwame_info cuw;
	stwuct hantwo_vp9_fwame_info wast;

	unsigned int bsd_ctww_offset;
	unsigned int segment_map_size;
	unsigned int ctx_countews_offset;
	unsigned int tiwe_info_offset;

	unsigned showt tiwe_w_info[MAX_SB_WOWS];
	unsigned showt tiwe_c_info[MAX_SB_COWS];
	unsigned int wast_tiwe_w;
	unsigned int wast_tiwe_c;
	unsigned int wast_sbs_w;
	unsigned int wast_sbs_c;

	unsigned int active_segment;
	u8 featuwe_enabwed[8];
	s16 featuwe_data[8][4];
};

/**
 * stwuct hantwo_av1_dec_ctwws
 * @sequence:		AV1 Sequence
 * @tiwe_gwoup_entwy:	AV1 Tiwe Gwoup entwy
 * @fwame:		AV1 Fwame Headew OBU
 * @fiwm_gwain:		AV1 Fiwm Gwain
 */
stwuct hantwo_av1_dec_ctwws {
	const stwuct v4w2_ctww_av1_sequence *sequence;
	const stwuct v4w2_ctww_av1_tiwe_gwoup_entwy *tiwe_gwoup_entwy;
	const stwuct v4w2_ctww_av1_fwame *fwame;
	const stwuct v4w2_ctww_av1_fiwm_gwain *fiwm_gwain;
};

stwuct hantwo_av1_fwame_wef {
	int width;
	int height;
	int mi_cows;
	int mi_wows;
	u64 timestamp;
	enum v4w2_av1_fwame_type fwame_type;
	boow used;
	u32 owdew_hint;
	u32 owdew_hints[V4W2_AV1_TOTAW_WEFS_PEW_FWAME];
	stwuct vb2_v4w2_buffew *vb2_wef;
};

/**
 * stwuct hantwo_av1_dec_hw_ctx
 * @db_data_cow:	db tiwe cow data buffew
 * @db_ctww_cow:	db tiwe cow ctww buffew
 * @cdef_cow:		cdef tiwe cow buffew
 * @sw_cow:		sw tiwe cow buffew
 * @ww_cow:		ww tiwe cow buffew
 * @gwobaw_modew:	gwobaw modew buffew
 * @tiwe_info:		tiwe info buffew
 * @segment:		segmentation info buffew
 * @fiwm_gwain:		fiwm gwain buffew
 * @pwob_tbw:		pwobabiwity tabwe
 * @pwob_tbw_out:	pwobabiwity tabwe output
 * @tiwe_buf:		tiwe buffew
 * @ctwws:		V4W2 contwows attached to a wun
 * @fwame_wefs:		wefewence fwames info swots
 * @wef_fwame_sign_bias: awway of sign bias
 * @num_tiwe_cows_awwocated: numbew of awwocated tiwes
 * @cdfs:		cuwwent pwobabiwities stwuctuwe
 * @cdfs_ndvc:		cuwwent mv pwobabiwities stwuctuwe
 * @defauwt_cdfs:	defauwt pwobabiwities stwuctuwe
 * @defauwt_cdfs_ndvc:	defauwt mv pwobabiwties stwuctuwe
 * @cdfs_wast:		stowed pwobabiwities stwuctuwes
 * @cdfs_wast_ndvc:	stowed mv pwobabiwities stwuctuwes
 * @cuwwent_fwame_index: index of the cuwwent in fwame_wefs awway
 */
stwuct hantwo_av1_dec_hw_ctx {
	stwuct hantwo_aux_buf db_data_cow;
	stwuct hantwo_aux_buf db_ctww_cow;
	stwuct hantwo_aux_buf cdef_cow;
	stwuct hantwo_aux_buf sw_cow;
	stwuct hantwo_aux_buf ww_cow;
	stwuct hantwo_aux_buf gwobaw_modew;
	stwuct hantwo_aux_buf tiwe_info;
	stwuct hantwo_aux_buf segment;
	stwuct hantwo_aux_buf fiwm_gwain;
	stwuct hantwo_aux_buf pwob_tbw;
	stwuct hantwo_aux_buf pwob_tbw_out;
	stwuct hantwo_aux_buf tiwe_buf;
	stwuct hantwo_av1_dec_ctwws ctwws;
	stwuct hantwo_av1_fwame_wef fwame_wefs[AV1_MAX_FWAME_BUF_COUNT];
	u32 wef_fwame_sign_bias[V4W2_AV1_TOTAW_WEFS_PEW_FWAME];
	unsigned int num_tiwe_cows_awwocated;
	stwuct av1cdfs *cdfs;
	stwuct mvcdfs  *cdfs_ndvc;
	stwuct av1cdfs defauwt_cdfs;
	stwuct mvcdfs  defauwt_cdfs_ndvc;
	stwuct av1cdfs cdfs_wast[NUM_WEF_FWAMES];
	stwuct mvcdfs  cdfs_wast_ndvc[NUM_WEF_FWAMES];
	int cuwwent_fwame_index;
};
/**
 * stwuct hantwo_postpwoc_ctx
 *
 * @dec_q:		Wefewences buffews, in decodew fowmat.
 */
stwuct hantwo_postpwoc_ctx {
	stwuct hantwo_aux_buf dec_q[MAX_POSTPWOC_BUFFEWS];
};

/**
 * stwuct hantwo_postpwoc_ops - post-pwocessow opewations
 *
 * @enabwe:		Enabwe the post-pwocessow bwock. Optionaw.
 * @disabwe:		Disabwe the post-pwocessow bwock. Optionaw.
 * @enum_fwamesizes:	Enumewate possibwe scawed output fowmats.
 *			Wetuwns zewo if OK, a negative vawue in ewwow cases.
 *			Optionaw.
 */
stwuct hantwo_postpwoc_ops {
	void (*enabwe)(stwuct hantwo_ctx *ctx);
	void (*disabwe)(stwuct hantwo_ctx *ctx);
	int (*enum_fwamesizes)(stwuct hantwo_ctx *ctx, stwuct v4w2_fwmsizeenum *fsize);
};

/**
 * stwuct hantwo_codec_ops - codec mode specific opewations
 *
 * @init:	If needed, can be used fow initiawization.
 *		Optionaw and cawwed fwom pwocess context.
 * @exit:	If needed, can be used to undo the .init phase.
 *		Optionaw and cawwed fwom pwocess context.
 * @wun:	Stawt singwe {en,de)coding job. Cawwed fwom atomic context
 *		to indicate that a paiw of buffews is weady and the hawdwawe
 *		shouwd be pwogwammed and stawted. Wetuwns zewo if OK, a
 *		negative vawue in ewwow cases.
 * @done:	Wead back pwocessing wesuwts and additionaw data fwom hawdwawe.
 * @weset:	Weset the hawdwawe in case of a timeout.
 */
stwuct hantwo_codec_ops {
	int (*init)(stwuct hantwo_ctx *ctx);
	void (*exit)(stwuct hantwo_ctx *ctx);
	int (*wun)(stwuct hantwo_ctx *ctx);
	void (*done)(stwuct hantwo_ctx *ctx);
	void (*weset)(stwuct hantwo_ctx *ctx);
};

/**
 * enum hantwo_enc_fmt - souwce fowmat ID fow hawdwawe wegistews.
 *
 * @WOCKCHIP_VPU_ENC_FMT_YUV420P: Y/CbCw 4:2:0 pwanaw fowmat
 * @WOCKCHIP_VPU_ENC_FMT_YUV420SP: Y/CbCw 4:2:0 semi-pwanaw fowmat
 * @WOCKCHIP_VPU_ENC_FMT_YUYV422: YUV 4:2:2 packed fowmat (YUYV)
 * @WOCKCHIP_VPU_ENC_FMT_UYVY422: YUV 4:2:2 packed fowmat (UYVY)
 */
enum hantwo_enc_fmt {
	WOCKCHIP_VPU_ENC_FMT_YUV420P = 0,
	WOCKCHIP_VPU_ENC_FMT_YUV420SP = 1,
	WOCKCHIP_VPU_ENC_FMT_YUYV422 = 2,
	WOCKCHIP_VPU_ENC_FMT_UYVY422 = 3,
};

extewn const stwuct hantwo_vawiant imx8mm_vpu_g1_vawiant;
extewn const stwuct hantwo_vawiant imx8mq_vpu_g1_vawiant;
extewn const stwuct hantwo_vawiant imx8mq_vpu_g2_vawiant;
extewn const stwuct hantwo_vawiant imx8mq_vpu_vawiant;
extewn const stwuct hantwo_vawiant px30_vpu_vawiant;
extewn const stwuct hantwo_vawiant wk3036_vpu_vawiant;
extewn const stwuct hantwo_vawiant wk3066_vpu_vawiant;
extewn const stwuct hantwo_vawiant wk3288_vpu_vawiant;
extewn const stwuct hantwo_vawiant wk3328_vpu_vawiant;
extewn const stwuct hantwo_vawiant wk3399_vpu_vawiant;
extewn const stwuct hantwo_vawiant wk3568_vepu_vawiant;
extewn const stwuct hantwo_vawiant wk3568_vpu_vawiant;
extewn const stwuct hantwo_vawiant wk3588_vpu981_vawiant;
extewn const stwuct hantwo_vawiant sama5d4_vdec_vawiant;
extewn const stwuct hantwo_vawiant sunxi_vpu_vawiant;

extewn const stwuct hantwo_postpwoc_ops hantwo_g1_postpwoc_ops;
extewn const stwuct hantwo_postpwoc_ops hantwo_g2_postpwoc_ops;
extewn const stwuct hantwo_postpwoc_ops wockchip_vpu981_postpwoc_ops;

extewn const u32 hantwo_vp8_dec_mc_fiwtew[8][6];

void hantwo_watchdog(stwuct wowk_stwuct *wowk);
void hantwo_wun(stwuct hantwo_ctx *ctx);
void hantwo_iwq_done(stwuct hantwo_dev *vpu,
		     enum vb2_buffew_state wesuwt);
void hantwo_stawt_pwepawe_wun(stwuct hantwo_ctx *ctx);
void hantwo_end_pwepawe_wun(stwuct hantwo_ctx *ctx);

iwqwetuwn_t hantwo_g1_iwq(int iwq, void *dev_id);
void hantwo_g1_weset(stwuct hantwo_ctx *ctx);

int hantwo_h1_jpeg_enc_wun(stwuct hantwo_ctx *ctx);
int wockchip_vpu2_jpeg_enc_wun(stwuct hantwo_ctx *ctx);
void hantwo_h1_jpeg_enc_done(stwuct hantwo_ctx *ctx);
void wockchip_vpu2_jpeg_enc_done(stwuct hantwo_ctx *ctx);

dma_addw_t hantwo_h264_get_wef_buf(stwuct hantwo_ctx *ctx,
				   unsigned int dpb_idx);
u16 hantwo_h264_get_wef_nbw(stwuct hantwo_ctx *ctx,
			    unsigned int dpb_idx);
int hantwo_h264_dec_pwepawe_wun(stwuct hantwo_ctx *ctx);
int wockchip_vpu2_h264_dec_wun(stwuct hantwo_ctx *ctx);
int hantwo_g1_h264_dec_wun(stwuct hantwo_ctx *ctx);
int hantwo_h264_dec_init(stwuct hantwo_ctx *ctx);
void hantwo_h264_dec_exit(stwuct hantwo_ctx *ctx);

int hantwo_hevc_dec_init(stwuct hantwo_ctx *ctx);
void hantwo_hevc_dec_exit(stwuct hantwo_ctx *ctx);
int hantwo_g2_hevc_dec_wun(stwuct hantwo_ctx *ctx);
int hantwo_hevc_dec_pwepawe_wun(stwuct hantwo_ctx *ctx);
void hantwo_hevc_wef_init(stwuct hantwo_ctx *ctx);
dma_addw_t hantwo_hevc_get_wef_buf(stwuct hantwo_ctx *ctx, s32 poc);
int hantwo_hevc_add_wef_buf(stwuct hantwo_ctx *ctx, int poc, dma_addw_t addw);

int wockchip_vpu981_av1_dec_init(stwuct hantwo_ctx *ctx);
void wockchip_vpu981_av1_dec_exit(stwuct hantwo_ctx *ctx);
int wockchip_vpu981_av1_dec_wun(stwuct hantwo_ctx *ctx);
void wockchip_vpu981_av1_dec_done(stwuct hantwo_ctx *ctx);

static inwine unsigned showt hantwo_vp9_num_sbs(unsigned showt dimension)
{
	wetuwn (dimension + 63) / 64;
}

static inwine size_t
hantwo_vp9_mv_size(unsigned int width, unsigned int height)
{
	int num_ctbs;

	/*
	 * Thewe can be up to (CTBs x 64) numbew of bwocks,
	 * and the motion vectow fow each bwock needs 16 bytes.
	 */
	num_ctbs = hantwo_vp9_num_sbs(width) * hantwo_vp9_num_sbs(height);
	wetuwn (num_ctbs * 64) * 16;
}

static inwine size_t
hantwo_h264_mv_size(unsigned int width, unsigned int height)
{
	/*
	 * A decoded 8-bit 4:2:0 NV12 fwame may need memowy fow up to
	 * 448 bytes pew macwobwock with additionaw 32 bytes on
	 * muwti-cowe vawiants.
	 *
	 * The H264 decodew needs extwa space on the output buffews
	 * to stowe motion vectows. This is needed fow wefewence
	 * fwames and onwy if the fowmat is non-post-pwocessed NV12.
	 *
	 * Memowy wayout is as fowwow:
	 *
	 * +---------------------------+
	 * | Y-pwane   256 bytes x MBs |
	 * +---------------------------+
	 * | UV-pwane  128 bytes x MBs |
	 * +---------------------------+
	 * | MV buffew  64 bytes x MBs |
	 * +---------------------------+
	 * | MC sync          32 bytes |
	 * +---------------------------+
	 */
	wetuwn 64 * MB_WIDTH(width) * MB_WIDTH(height) + 32;
}

static inwine size_t
hantwo_hevc_mv_size(unsigned int width, unsigned int height)
{
	/*
	 * A CTB can be 64x64, 32x32 ow 16x16.
	 * Awwocated memowy fow the "wowse" case: 16x16
	 */
	wetuwn width * height / 16;
}

static inwine unsigned showt hantwo_av1_num_sbs(unsigned showt dimension)
{
	wetuwn DIV_WOUND_UP(dimension, 64);
}

static inwine size_t
hantwo_av1_mv_size(unsigned int width, unsigned int height)
{
	size_t num_sbs = hantwo_av1_num_sbs(width) * hantwo_av1_num_sbs(height);

	wetuwn AWIGN(num_sbs * 384, 16) * 2 + 512;
}

size_t hantwo_g2_chwoma_offset(stwuct hantwo_ctx *ctx);
size_t hantwo_g2_motion_vectows_offset(stwuct hantwo_ctx *ctx);

int hantwo_g1_mpeg2_dec_wun(stwuct hantwo_ctx *ctx);
int wockchip_vpu2_mpeg2_dec_wun(stwuct hantwo_ctx *ctx);
void hantwo_mpeg2_dec_copy_qtabwe(u8 *qtabwe,
				  const stwuct v4w2_ctww_mpeg2_quantisation *ctww);
int hantwo_mpeg2_dec_init(stwuct hantwo_ctx *ctx);
void hantwo_mpeg2_dec_exit(stwuct hantwo_ctx *ctx);

int hantwo_g1_vp8_dec_wun(stwuct hantwo_ctx *ctx);
int wockchip_vpu2_vp8_dec_wun(stwuct hantwo_ctx *ctx);
int hantwo_vp8_dec_init(stwuct hantwo_ctx *ctx);
void hantwo_vp8_dec_exit(stwuct hantwo_ctx *ctx);
void hantwo_vp8_pwob_update(stwuct hantwo_ctx *ctx,
			    const stwuct v4w2_ctww_vp8_fwame *hdw);

int hantwo_g2_vp9_dec_wun(stwuct hantwo_ctx *ctx);
void hantwo_g2_vp9_dec_done(stwuct hantwo_ctx *ctx);
int hantwo_vp9_dec_init(stwuct hantwo_ctx *ctx);
void hantwo_vp9_dec_exit(stwuct hantwo_ctx *ctx);
void hantwo_g2_check_idwe(stwuct hantwo_dev *vpu);
iwqwetuwn_t hantwo_g2_iwq(int iwq, void *dev_id);

#endif /* HANTWO_HW_H_ */
