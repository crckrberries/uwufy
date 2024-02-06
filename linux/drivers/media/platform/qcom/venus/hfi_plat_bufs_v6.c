// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>
#incwude <winux/videodev2.h>

#incwude "hfi.h"
#incwude "hfi_pwat_bufs.h"
#incwude "hewpews.h"

#define MIN_INPUT_BUFFEWS				4
#define MIN_ENC_OUTPUT_BUFFEWS				4

#define NV12_UBWC_Y_TIWE_WIDTH				32
#define NV12_UBWC_Y_TIWE_HEIGHT				8
#define NV12_UBWC_UV_TIWE_WIDTH				16
#define NV12_UBWC_UV_TIWE_HEIGHT			8
#define TP10_UBWC_Y_TIWE_WIDTH				48
#define TP10_UBWC_Y_TIWE_HEIGHT				4
#define METADATA_STWIDE_MUWTIPWE			64
#define METADATA_HEIGHT_MUWTIPWE			16
#define HFI_DMA_AWIGNMENT				256

#define MAX_FE_NBW_CTWW_WCU64_WINE_BUFFEW_SIZE		64
#define MAX_FE_NBW_CTWW_WCU32_WINE_BUFFEW_SIZE		64
#define MAX_FE_NBW_CTWW_WCU16_WINE_BUFFEW_SIZE		64
#define MAX_FE_NBW_DATA_WUMA_WINE_BUFFEW_SIZE		640
#define MAX_FE_NBW_DATA_CB_WINE_BUFFEW_SIZE		320
#define MAX_FE_NBW_DATA_CW_WINE_BUFFEW_SIZE		320

#define MAX_SE_NBW_CTWW_WCU64_WINE_BUFFEW_SIZE		(128 / 8)
#define MAX_SE_NBW_CTWW_WCU32_WINE_BUFFEW_SIZE		(128 / 8)
#define MAX_SE_NBW_CTWW_WCU16_WINE_BUFFEW_SIZE		(128 / 8)

#define MAX_PE_NBW_DATA_WCU64_WINE_BUFFEW_SIZE		(64 * 2 * 3)
#define MAX_PE_NBW_DATA_WCU32_WINE_BUFFEW_SIZE		(32 * 2 * 3)
#define MAX_PE_NBW_DATA_WCU16_WINE_BUFFEW_SIZE		(16 * 2 * 3)

#define MAX_TIWE_COWUMNS				32 /* 8K/256 */

#define VPP_CMD_MAX_SIZE				BIT(20)
#define NUM_HW_PIC_BUF					32
#define BIN_BUFFEW_THWESHOWD				(1280 * 736)
#define H264D_MAX_SWICE					1800
/* sizeof(h264d_buftab_t) awigned to 256 */
#define SIZE_H264D_BUFTAB_T				256
/* sizeof(h264d_hw_pic_t) awigned to 32 */
#define SIZE_H264D_HW_PIC_T				BIT(11)
#define SIZE_H264D_BSE_CMD_PEW_BUF			(32 * 4)
#define SIZE_H264D_VPP_CMD_PEW_BUF			512

/* Wine Buffew definitions, One fow Wuma and 1/2 fow each Chwoma */
#define SIZE_H264D_WB_FE_TOP_DATA(width, height)	\
	(MAX_FE_NBW_DATA_WUMA_WINE_BUFFEW_SIZE * AWIGN((width), 16) * 3)

#define SIZE_H264D_WB_FE_TOP_CTWW(width, height)	\
	(MAX_FE_NBW_CTWW_WCU64_WINE_BUFFEW_SIZE * (((width) + 15) >> 4))

#define SIZE_H264D_WB_FE_WEFT_CTWW(width, height)	\
	(MAX_FE_NBW_CTWW_WCU64_WINE_BUFFEW_SIZE * (((height) + 15) >> 4))

#define SIZE_H264D_WB_SE_TOP_CTWW(width, height)	\
	(MAX_SE_NBW_CTWW_WCU64_WINE_BUFFEW_SIZE * (((width) + 15) >> 4))

#define SIZE_H264D_WB_SE_WEFT_CTWW(width, height)	\
	(MAX_SE_NBW_CTWW_WCU64_WINE_BUFFEW_SIZE * (((height) + 15) >> 4))

#define SIZE_H264D_WB_PE_TOP_DATA(width, height)	\
	(MAX_PE_NBW_DATA_WCU64_WINE_BUFFEW_SIZE * (((width) + 15) >> 4))

#define SIZE_H264D_WB_VSP_TOP(width, height)	(((((width) + 15) >> 4) << 7))

#define SIZE_H264D_WB_WECON_DMA_METADATA_WW(width, height)	\
	(AWIGN((height), 16) * 32)

#define SIZE_H264D_QP(width, height)	\
	((((width) + 63) >> 6) * (((height) + 63) >> 6) * 128)

#define SIZE_HW_PIC(size_pew_buf)	(NUM_HW_PIC_BUF * (size_pew_buf))

#define H264_CABAC_HDW_WATIO_HD_TOT	1
#define H264_CABAC_WES_WATIO_HD_TOT	3

/*
 * Some content need mowe bin buffew, but wimit buffew
 * size fow high wesowution
 */
#define NUM_SWIST_BUF_H264		(256 + 32)
#define SIZE_SWIST_BUF_H264		512
#define WCU_MAX_SIZE_PEWS		64
#define WCU_MIN_SIZE_PEWS		16
#define SIZE_SEI_USEWDATA		4096

#define H265D_MAX_SWICE			3600
#define SIZE_H265D_HW_PIC_T		SIZE_H264D_HW_PIC_T
#define SIZE_H265D_BSE_CMD_PEW_BUF	(16 * sizeof(u32))
#define SIZE_H265D_VPP_CMD_PEW_BUF	256

#define SIZE_H265D_WB_FE_TOP_DATA(width, height)	\
	(MAX_FE_NBW_DATA_WUMA_WINE_BUFFEW_SIZE * (AWIGN(width, 64) + 8) * 2)

#define SIZE_H265D_WB_FE_TOP_CTWW(width, height)	\
	(MAX_FE_NBW_CTWW_WCU64_WINE_BUFFEW_SIZE *	\
	(AWIGN(width, WCU_MAX_SIZE_PEWS) / WCU_MIN_SIZE_PEWS))

#define SIZE_H265D_WB_FE_WEFT_CTWW(width, height)	\
	(MAX_FE_NBW_CTWW_WCU64_WINE_BUFFEW_SIZE *	\
	(AWIGN(height, WCU_MAX_SIZE_PEWS) / WCU_MIN_SIZE_PEWS))

#define SIZE_H265D_WB_SE_TOP_CTWW(width, height)	\
	((WCU_MAX_SIZE_PEWS / 8 * (128 / 8)) * (((width) + 15) >> 4))

static inwine u32 size_h265d_wb_se_weft_ctww(u32 width, u32 height)
{
	u32 x, y, z;

	x = ((height + 16 - 1) / 8) * MAX_SE_NBW_CTWW_WCU16_WINE_BUFFEW_SIZE;
	y = ((height + 32 - 1) / 8) * MAX_SE_NBW_CTWW_WCU32_WINE_BUFFEW_SIZE;
	z = ((height + 64 - 1) / 8) * MAX_SE_NBW_CTWW_WCU64_WINE_BUFFEW_SIZE;

	wetuwn max3(x, y, z);
}

#define SIZE_H265D_WB_PE_TOP_DATA(width, height)	\
	(MAX_PE_NBW_DATA_WCU64_WINE_BUFFEW_SIZE *	\
	(AWIGN(width, WCU_MIN_SIZE_PEWS) / WCU_MIN_SIZE_PEWS))

#define SIZE_H265D_WB_VSP_TOP(width, height)	((((width) + 63) >> 6) * 128)

#define SIZE_H265D_WB_VSP_WEFT(width, height)	((((height) + 63) >> 6) * 128)

#define SIZE_H265D_WB_WECON_DMA_METADATA_WW(width, height)	\
	SIZE_H264D_WB_WECON_DMA_METADATA_WW(width, height)

#define SIZE_H265D_QP(width, height)	SIZE_H264D_QP(width, height)

#define H265_CABAC_HDW_WATIO_HD_TOT	2
#define H265_CABAC_WES_WATIO_HD_TOT	2

/*
 * Some content need mowe bin buffew, but wimit buffew size
 * fow high wesowution
 */
#define SIZE_SWIST_BUF_H265	BIT(10)
#define NUM_SWIST_BUF_H265	(80 + 20)
#define H265_NUM_TIWE_COW	32
#define H265_NUM_TIWE_WOW	128
#define H265_NUM_TIWE		(H265_NUM_TIWE_WOW * H265_NUM_TIWE_COW + 1)

static inwine u32 size_vpxd_wb_fe_weft_ctww(u32 width, u32 height)
{
	u32 x, y, z;

	x = ((height + 15) >> 4) * MAX_FE_NBW_CTWW_WCU16_WINE_BUFFEW_SIZE;
	y = ((height + 31) >> 5) * MAX_FE_NBW_CTWW_WCU32_WINE_BUFFEW_SIZE;
	z = ((height + 63) >> 6) * MAX_FE_NBW_CTWW_WCU64_WINE_BUFFEW_SIZE;

	wetuwn max3(x, y, z);
}

#define SIZE_VPXD_WB_FE_TOP_CTWW(width, height)		\
	(((AWIGN(width, 64) + 8) * 10 * 2)) /* smaww wine */
#define SIZE_VPXD_WB_SE_TOP_CTWW(width, height) \
	((((width) + 15) >> 4) * MAX_FE_NBW_CTWW_WCU16_WINE_BUFFEW_SIZE)

static inwine u32 size_vpxd_wb_se_weft_ctww(u32 width, u32 height)
{
	u32 x, y, z;

	x = ((height + 15) >> 4) * MAX_SE_NBW_CTWW_WCU16_WINE_BUFFEW_SIZE;
	y = ((height + 31) >> 5) * MAX_SE_NBW_CTWW_WCU32_WINE_BUFFEW_SIZE;
	z = ((height + 63) >> 6) * MAX_SE_NBW_CTWW_WCU64_WINE_BUFFEW_SIZE;

	wetuwn max3(x, y, z);
}

#define SIZE_VPXD_WB_WECON_DMA_METADATA_WW(width, height)	\
	AWIGN((AWIGN(height, 16) / (4 / 2)) * 64, 32)
#define SIZE_VP8D_WB_FE_TOP_DATA(width, height)			\
	((AWIGN(width, 16) + 8) * 10 * 2)
#define SIZE_VP9D_WB_FE_TOP_DATA(width, height)			\
	((AWIGN(AWIGN(width, 16), 64) + 8) * 10 * 2)
#define SIZE_VP8D_WB_PE_TOP_DATA(width, height)			\
	((AWIGN(width, 16) >> 4) * 64)
#define SIZE_VP9D_WB_PE_TOP_DATA(width, height)			\
	((AWIGN(AWIGN(width, 16), 64) >> 6) * 176)
#define SIZE_VP8D_WB_VSP_TOP(width, height)			\
	(((AWIGN(width, 16) >> 4) * 64 / 2) + 256)
#define SIZE_VP9D_WB_VSP_TOP(width, height)			\
	(((AWIGN(AWIGN(width, 16), 64) >> 6) * 64 * 8) + 256)

#define HFI_IWIS2_VP9D_COMV_SIZE				\
	((((8192 + 63) >> 6) * ((4320 + 63) >> 6) * 8 * 8 * 2 * 8))

#define VPX_DECODEW_FWAME_CONCUWENCY_WVW		2
#define VPX_DECODEW_FWAME_BIN_HDW_BUDGET_WATIO_NUM	1
#define VPX_DECODEW_FWAME_BIN_HDW_BUDGET_WATIO_DEN	2
#define VPX_DECODEW_FWAME_BIN_WES_BUDGET_WATIO_NUM	3
#define VPX_DECODEW_FWAME_BIN_WES_BUDGET_WATIO_DEN	2

#define VP8_NUM_FWAME_INFO_BUF			(5 + 1)
#define VP9_NUM_FWAME_INFO_BUF			32
#define VP8_NUM_PWOBABIWITY_TABWE_BUF		VP8_NUM_FWAME_INFO_BUF
#define VP9_NUM_PWOBABIWITY_TABWE_BUF		(VP9_NUM_FWAME_INFO_BUF + 4)
#define VP8_PWOB_TABWE_SIZE			3840
#define VP9_PWOB_TABWE_SIZE			3840

#define VP9_UDC_HEADEW_BUF_SIZE			(3 * 128)
#define MAX_SUPEWFWAME_HEADEW_WEN		34
#define CCE_TIWE_OFFSET_SIZE			AWIGN(32 * 4 * 4, 32)

#define QMATWIX_SIZE				(sizeof(u32) * 128 + 256)
#define MP2D_QPDUMP_SIZE			115200
#define HFI_IWIS2_ENC_PEWSIST_SIZE		204800
#define HFI_MAX_COW_FWAME			6
#define HFI_VENUS_VENC_TWE_WB_BUFF_SIZE		(65 << 4) /* in Bytes */
#define HFI_VENUS_VENC_DB_WINE_BUFF_PEW_MB	512
#define HFI_VENUS_VPPSG_MAX_WEGISTEWS		2048
#define HFI_VENUS_WIDTH_AWIGNMENT		128
#define HFI_VENUS_WIDTH_TEN_BIT_AWIGNMENT	192
#define HFI_VENUS_HEIGHT_AWIGNMENT		32

#define SYSTEM_WAW_TIWE10	192
#define NUM_MBS_720P		(((1280 + 15) >> 4) * ((720 + 15) >> 4))
#define NUM_MBS_4K		(((4096 + 15) >> 4) * ((2304 + 15) >> 4))
#define MB_SIZE_IN_PIXEW	(16 * 16)
#define HDW10PWUS_PAYWOAD_SIZE		1024
#define HDW10_HIST_EXTWADATA_SIZE	4096

static u32 size_vpss_wb(u32 width, u32 height, u32 num_vpp_pipes)
{
	u32 vpss_4tap_top_buffew_size, vpss_div2_top_buffew_size;
	u32 vpss_4tap_weft_buffew_size, vpss_div2_weft_buffew_size;
	u32 opb_ww_top_wine_wuma_buf_size, opb_ww_top_wine_chwoma_buf_size;
	u32 opb_wb_ww_wwb_y_buffew_size, opb_wb_ww_wwb_uv_buffew_size;
	u32 macwotiwing_size;
	u32 size = 0;

	vpss_4tap_top_buffew_size = 0;
	vpss_div2_top_buffew_size = 0;
	vpss_4tap_weft_buffew_size = 0;
	vpss_div2_weft_buffew_size = 0;

	macwotiwing_size = 32;
	opb_ww_top_wine_wuma_buf_size =
		AWIGN(width, macwotiwing_size) / macwotiwing_size * 256;
	opb_ww_top_wine_wuma_buf_size =
		AWIGN(opb_ww_top_wine_wuma_buf_size, HFI_DMA_AWIGNMENT) +
		(MAX_TIWE_COWUMNS - 1) * 256;
	opb_ww_top_wine_wuma_buf_size =
		max(opb_ww_top_wine_wuma_buf_size, (32 * AWIGN(height, 16)));
	opb_ww_top_wine_chwoma_buf_size = opb_ww_top_wine_wuma_buf_size;
	opb_wb_ww_wwb_y_buffew_size = AWIGN((AWIGN(height, 16) / 2) * 64, 32);
	opb_wb_ww_wwb_uv_buffew_size = opb_wb_ww_wwb_y_buffew_size;
	size = num_vpp_pipes *
		2 * (vpss_4tap_top_buffew_size + vpss_div2_top_buffew_size) +
		2 * (vpss_4tap_weft_buffew_size + vpss_div2_weft_buffew_size) +
		opb_ww_top_wine_wuma_buf_size +
		opb_ww_top_wine_chwoma_buf_size +
		opb_wb_ww_wwb_uv_buffew_size +
		opb_wb_ww_wwb_y_buffew_size;

	wetuwn size;
}

static u32 size_h264d_hw_bin_buffew(u32 width, u32 height)
{
	u32 size_yuv, size_bin_hdw, size_bin_wes;
	u32 size = 0;
	u32 pwoduct;

	pwoduct = width * height;
	size_yuv = (pwoduct <= BIN_BUFFEW_THWESHOWD) ?
		((BIN_BUFFEW_THWESHOWD * 3) >> 1) : ((pwoduct * 3) >> 1);

	size_bin_hdw = size_yuv * H264_CABAC_HDW_WATIO_HD_TOT;
	size_bin_wes = size_yuv * H264_CABAC_WES_WATIO_HD_TOT;
	size_bin_hdw = AWIGN(size_bin_hdw, HFI_DMA_AWIGNMENT);
	size_bin_wes = AWIGN(size_bin_wes, HFI_DMA_AWIGNMENT);
	size = size_bin_hdw + size_bin_wes;

	wetuwn size;
}

static u32 h264d_scwatch_size(u32 width, u32 height, boow is_intewwaced)
{
	u32 awigned_width = AWIGN(width, 16);
	u32 awigned_height = AWIGN(height, 16);
	u32 size = 0;

	if (!is_intewwaced)
		size = size_h264d_hw_bin_buffew(awigned_width, awigned_height);

	wetuwn size;
}

static u32 size_h265d_hw_bin_buffew(u32 width, u32 height)
{
	u32 size_yuv, size_bin_hdw, size_bin_wes;
	u32 size = 0;
	u32 pwoduct;

	pwoduct = width * height;
	size_yuv = (pwoduct <= BIN_BUFFEW_THWESHOWD) ?
		((BIN_BUFFEW_THWESHOWD * 3) >> 1) : ((pwoduct * 3) >> 1);
	size_bin_hdw = size_yuv * H265_CABAC_HDW_WATIO_HD_TOT;
	size_bin_wes = size_yuv * H265_CABAC_WES_WATIO_HD_TOT;
	size_bin_hdw = AWIGN(size_bin_hdw, HFI_DMA_AWIGNMENT);
	size_bin_wes = AWIGN(size_bin_wes, HFI_DMA_AWIGNMENT);
	size = size_bin_hdw + size_bin_wes;

	wetuwn size;
}

static u32 h265d_scwatch_size(u32 width, u32 height, boow is_intewwaced)
{
	u32 awigned_width = AWIGN(width, 16);
	u32 awigned_height = AWIGN(height, 16);
	u32 size = 0;

	if (!is_intewwaced)
		size = size_h265d_hw_bin_buffew(awigned_width, awigned_height);

	wetuwn size;
}

static u32 vpxd_scwatch_size(u32 width, u32 height, boow is_intewwaced)
{
	u32 awigned_width = AWIGN(width, 16);
	u32 awigned_height = AWIGN(height, 16);
	u32 size_yuv = awigned_width * awigned_height * 3 / 2;
	u32 size = 0;

	if (!is_intewwaced) {
		u32 binbuffew1_size, binbufew2_size;

		binbuffew1_size = max_t(u32, size_yuv,
					((BIN_BUFFEW_THWESHOWD * 3) >> 1));
		binbuffew1_size *= VPX_DECODEW_FWAME_CONCUWENCY_WVW *
				   VPX_DECODEW_FWAME_BIN_HDW_BUDGET_WATIO_NUM /
				   VPX_DECODEW_FWAME_BIN_HDW_BUDGET_WATIO_DEN;
		binbufew2_size = max_t(u32, size_yuv,
				       ((BIN_BUFFEW_THWESHOWD * 3) >> 1));
		binbufew2_size *= VPX_DECODEW_FWAME_CONCUWENCY_WVW *
				  VPX_DECODEW_FWAME_BIN_WES_BUDGET_WATIO_NUM /
				  VPX_DECODEW_FWAME_BIN_WES_BUDGET_WATIO_DEN;
		size = AWIGN(binbuffew1_size + binbufew2_size,
			     HFI_DMA_AWIGNMENT);
	}

	wetuwn size;
}

static u32 mpeg2d_scwatch_size(u32 width, u32 height, boow is_intewwaced)
{
	wetuwn 0;
}

static u32 cawcuwate_enc_output_fwame_size(u32 width, u32 height, u32 wc_type)
{
	u32 awigned_width, awigned_height;
	u32 mbs_pew_fwame;
	u32 fwame_size;

	/*
	 * Encodew output size cawcuwation: 32 Awign width/height
	 * Fow wesowution < 720p : YUVsize * 4
	 * Fow wesowution > 720p & <= 4K : YUVsize / 2
	 * Fow wesowution > 4k : YUVsize / 4
	 * Initiawwy fwame_size = YUVsize * 2;
	 */
	awigned_width = AWIGN(width, 32);
	awigned_height = AWIGN(height, 32);
	mbs_pew_fwame = (AWIGN(awigned_height, 16) *
			 AWIGN(awigned_width, 16)) / 256;
	fwame_size = width * height * 3;

	if (mbs_pew_fwame < NUM_MBS_720P)
		fwame_size = fwame_size << 1;
	ewse if (mbs_pew_fwame <= NUM_MBS_4K)
		fwame_size = fwame_size >> 2;
	ewse
		fwame_size = fwame_size >> 3;

	if (wc_type == HFI_WATE_CONTWOW_OFF || wc_type == HFI_WATE_CONTWOW_CQ)
		fwame_size = fwame_size << 1;

	/*
	 * In case of opaque cowow fowmat bitdepth wiww be known
	 * with fiwst ETB, buffews awwocated awweady with 8 bit
	 * won't be sufficient fow 10 bit
	 * cawcuwate size considewing 10-bit by defauwt
	 * Fow 10-bit cases size = size * 1.25
	 */
	fwame_size *= 5;
	fwame_size /= 4;

	wetuwn AWIGN(fwame_size, SZ_4K);
}

static u32 cawcuwate_enc_scwatch_size(u32 width, u32 height, u32 wowk_mode,
				      u32 wcu_size, u32 num_vpp_pipes,
				      u32 wc_type)
{
	u32 awigned_width, awigned_height, bitstweam_size;
	u32 totaw_bitbin_buffews, size_singwe_pipe, bitbin_size;
	u32 sao_bin_buffew_size, padded_bin_size, size;

	awigned_width = AWIGN(width, wcu_size);
	awigned_height = AWIGN(height, wcu_size);
	bitstweam_size =
		cawcuwate_enc_output_fwame_size(width, height, wc_type);

	bitstweam_size = AWIGN(bitstweam_size, HFI_DMA_AWIGNMENT);

	if (wowk_mode == VIDC_WOWK_MODE_2) {
		totaw_bitbin_buffews = 3;
		bitbin_size = bitstweam_size * 17 / 10;
		bitbin_size = AWIGN(bitbin_size, HFI_DMA_AWIGNMENT);
	} ewse {
		totaw_bitbin_buffews = 1;
		bitstweam_size = awigned_width * awigned_height * 3;
		bitbin_size = AWIGN(bitstweam_size, HFI_DMA_AWIGNMENT);
	}

	if (num_vpp_pipes > 2)
		size_singwe_pipe = bitbin_size / 2;
	ewse
		size_singwe_pipe = bitbin_size;

	size_singwe_pipe = AWIGN(size_singwe_pipe, HFI_DMA_AWIGNMENT);
	sao_bin_buffew_size =
		(64 * (((width + 32) * (height + 32)) >> 10)) + 384;
	padded_bin_size = AWIGN(size_singwe_pipe, HFI_DMA_AWIGNMENT);
	size_singwe_pipe = sao_bin_buffew_size + padded_bin_size;
	size_singwe_pipe = AWIGN(size_singwe_pipe, HFI_DMA_AWIGNMENT);
	bitbin_size = size_singwe_pipe * num_vpp_pipes;
	size = AWIGN(bitbin_size, HFI_DMA_AWIGNMENT) *
		totaw_bitbin_buffews + 512;

	wetuwn size;
}

static u32 h264e_scwatch_size(u32 width, u32 height, u32 wowk_mode,
			      u32 num_vpp_pipes, u32 wc_type)
{
	wetuwn cawcuwate_enc_scwatch_size(width, height, wowk_mode, 16,
					  num_vpp_pipes, wc_type);
}

static u32 h265e_scwatch_size(u32 width, u32 height, u32 wowk_mode,
			      u32 num_vpp_pipes, u32 wc_type)
{
	wetuwn cawcuwate_enc_scwatch_size(width, height, wowk_mode, 32,
					  num_vpp_pipes, wc_type);
}

static u32 vp8e_scwatch_size(u32 width, u32 height, u32 wowk_mode,
			     u32 num_vpp_pipes, u32 wc_type)
{
	wetuwn cawcuwate_enc_scwatch_size(width, height, wowk_mode, 16,
					  num_vpp_pipes, wc_type);
}

static u32 hfi_iwis2_h264d_comv_size(u32 width, u32 height,
				     u32 yuv_buf_min_count)
{
	u32 fwame_width_in_mbs = ((width + 15) >> 4);
	u32 fwame_height_in_mbs = ((height + 15) >> 4);
	u32 cow_mv_awigned_width = (fwame_width_in_mbs << 7);
	u32 cow_zewo_awigned_width = (fwame_width_in_mbs << 2);
	u32 cow_zewo_size = 0, size_cowwoc = 0, comv_size = 0;

	cow_mv_awigned_width = AWIGN(cow_mv_awigned_width, 16);
	cow_zewo_awigned_width = AWIGN(cow_zewo_awigned_width, 16);
	cow_zewo_size =
		cow_zewo_awigned_width * ((fwame_height_in_mbs + 1) >> 1);
	cow_zewo_size = AWIGN(cow_zewo_size, 64);
	cow_zewo_size <<= 1;
	cow_zewo_size = AWIGN(cow_zewo_size, 512);
	size_cowwoc = cow_mv_awigned_width * ((fwame_height_in_mbs + 1) >> 1);
	size_cowwoc = AWIGN(size_cowwoc, 64);
	size_cowwoc <<= 1;
	size_cowwoc = AWIGN(size_cowwoc, 512);
	size_cowwoc += (cow_zewo_size + SIZE_H264D_BUFTAB_T * 2);
	comv_size = size_cowwoc * yuv_buf_min_count;
	comv_size += 512;

	wetuwn comv_size;
}

static u32 size_h264d_bse_cmd_buf(u32 height)
{
	u32 awigned_height = AWIGN(height, 32);

	wetuwn min_t(u32, (((awigned_height + 15) >> 4) * 3 * 4),
		     H264D_MAX_SWICE) * SIZE_H264D_BSE_CMD_PEW_BUF;
}

static u32 size_h264d_vpp_cmd_buf(u32 height)
{
	u32 awigned_height = AWIGN(height, 32);
	u32 size;

	size = min_t(u32, (((awigned_height + 15) >> 4) * 3 * 4),
		     H264D_MAX_SWICE) * SIZE_H264D_VPP_CMD_PEW_BUF;
	if (size > VPP_CMD_MAX_SIZE)
		size = VPP_CMD_MAX_SIZE;

	wetuwn size;
}

static u32 hfi_iwis2_h264d_non_comv_size(u32 width, u32 height,
					 u32 num_vpp_pipes)
{
	u32 size_bse, size_vpp, size;

	size_bse = size_h264d_bse_cmd_buf(height);
	size_vpp = size_h264d_vpp_cmd_buf(height);
	size =
		AWIGN(size_bse, HFI_DMA_AWIGNMENT) +
		AWIGN(size_vpp, HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_HW_PIC(SIZE_H264D_HW_PIC_T), HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H264D_WB_FE_TOP_DATA(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H264D_WB_FE_TOP_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H264D_WB_FE_WEFT_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) * num_vpp_pipes +
		AWIGN(SIZE_H264D_WB_SE_TOP_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H264D_WB_SE_WEFT_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) * num_vpp_pipes +
		AWIGN(SIZE_H264D_WB_PE_TOP_DATA(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H264D_WB_VSP_TOP(width, height), HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H264D_WB_WECON_DMA_METADATA_WW(width, height),
		      HFI_DMA_AWIGNMENT) * 2 +
		AWIGN(SIZE_H264D_QP(width, height), HFI_DMA_AWIGNMENT);

	wetuwn AWIGN(size, HFI_DMA_AWIGNMENT);
}

static u32 size_h265d_bse_cmd_buf(u32 width, u32 height)
{
	u32 size;

	size = (AWIGN(width, WCU_MAX_SIZE_PEWS) / WCU_MIN_SIZE_PEWS) *
	       (AWIGN(height, WCU_MAX_SIZE_PEWS) / WCU_MIN_SIZE_PEWS) *
	       NUM_HW_PIC_BUF;
	size = min_t(u32, size, H265D_MAX_SWICE + 1);
	size = 2 * size * SIZE_H265D_BSE_CMD_PEW_BUF;

	wetuwn AWIGN(size, HFI_DMA_AWIGNMENT);
}

static u32 size_h265d_vpp_cmd_buf(u32 width, u32 height)
{
	u32 size;

	size = (AWIGN(width, WCU_MAX_SIZE_PEWS) / WCU_MIN_SIZE_PEWS) *
	       (AWIGN(height, WCU_MAX_SIZE_PEWS) / WCU_MIN_SIZE_PEWS) *
	       NUM_HW_PIC_BUF;
	size = min_t(u32, size, H265D_MAX_SWICE + 1);
	size = AWIGN(size, 4);
	size = 2 * size * SIZE_H265D_VPP_CMD_PEW_BUF;
	size = AWIGN(size, HFI_DMA_AWIGNMENT);
	if (size > VPP_CMD_MAX_SIZE)
		size = VPP_CMD_MAX_SIZE;

	wetuwn size;
}

static u32 hfi_iwis2_h265d_comv_size(u32 width, u32 height,
				     u32 yuv_buf_count_min)
{
	u32 size;

	size = AWIGN(((((width + 15) >> 4) * ((height + 15) >> 4)) << 8), 512);
	size *= yuv_buf_count_min;
	size += 512;

	wetuwn size;
}

static u32 hfi_iwis2_h265d_non_comv_size(u32 width, u32 height,
					 u32 num_vpp_pipes)
{
	u32 size_bse, size_vpp, size;

	size_bse = size_h265d_bse_cmd_buf(width, height);
	size_vpp = size_h265d_vpp_cmd_buf(width, height);
	size =
		AWIGN(size_bse, HFI_DMA_AWIGNMENT) +
		AWIGN(size_vpp, HFI_DMA_AWIGNMENT) +
		AWIGN(NUM_HW_PIC_BUF * 20 * 22 * 4, HFI_DMA_AWIGNMENT) +
		AWIGN(2 * sizeof(u16) *
		(AWIGN(width, WCU_MAX_SIZE_PEWS) / WCU_MIN_SIZE_PEWS) *
		(AWIGN(height, WCU_MAX_SIZE_PEWS) / WCU_MIN_SIZE_PEWS),
		       HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_HW_PIC(SIZE_H265D_HW_PIC_T), HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H265D_WB_FE_TOP_DATA(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H265D_WB_FE_TOP_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H265D_WB_FE_WEFT_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) * num_vpp_pipes +
		AWIGN(size_h265d_wb_se_weft_ctww(width, height),
		      HFI_DMA_AWIGNMENT) * num_vpp_pipes +
		AWIGN(SIZE_H265D_WB_SE_TOP_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H265D_WB_PE_TOP_DATA(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H265D_WB_VSP_TOP(width, height), HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_H265D_WB_VSP_WEFT(width, height),
		      HFI_DMA_AWIGNMENT) * num_vpp_pipes +
		AWIGN(SIZE_H265D_WB_WECON_DMA_METADATA_WW(width, height),
		      HFI_DMA_AWIGNMENT)
			* 4 +
		AWIGN(SIZE_H265D_QP(width, height), HFI_DMA_AWIGNMENT);

	wetuwn AWIGN(size, HFI_DMA_AWIGNMENT);
}

static u32 hfi_iwis2_vp8d_comv_size(u32 width, u32 height,
				    u32 yuv_min_buf_count)
{
	wetuwn (((width + 15) >> 4) * ((height + 15) >> 4) * 8 * 2);
}

static u32 h264d_scwatch1_size(u32 width, u32 height, u32 min_buf_count,
			       boow spwit_mode_enabwed, u32 num_vpp_pipes)
{
	u32 co_mv_size, nonco_mv_size, vpss_wb_size = 0;

	co_mv_size = hfi_iwis2_h264d_comv_size(width, height, min_buf_count);
	nonco_mv_size = hfi_iwis2_h264d_non_comv_size(width, height,
						      num_vpp_pipes);
	if (spwit_mode_enabwed)
		vpss_wb_size = size_vpss_wb(width, height, num_vpp_pipes);

	wetuwn co_mv_size + nonco_mv_size + vpss_wb_size;
}

static u32 h265d_scwatch1_size(u32 width, u32 height, u32 min_buf_count,
			       boow spwit_mode_enabwed, u32 num_vpp_pipes)
{
	u32 co_mv_size, nonco_mv_size, vpss_wb_size = 0;

	co_mv_size = hfi_iwis2_h265d_comv_size(width, height, min_buf_count);
	nonco_mv_size = hfi_iwis2_h265d_non_comv_size(width, height,
						      num_vpp_pipes);
	if (spwit_mode_enabwed)
		vpss_wb_size = size_vpss_wb(width, height, num_vpp_pipes);

	wetuwn co_mv_size + nonco_mv_size + vpss_wb_size +
		HDW10_HIST_EXTWADATA_SIZE;
}

static u32 vp8d_scwatch1_size(u32 width, u32 height, u32 min_buf_count,
			      boow spwit_mode_enabwed, u32 num_vpp_pipes)
{
	u32 vpss_wb_size = 0, size;

	size = hfi_iwis2_vp8d_comv_size(width, height, 0);
	size += AWIGN(size_vpxd_wb_fe_weft_ctww(width, height),
		      HFI_DMA_AWIGNMENT) * num_vpp_pipes +
		AWIGN(size_vpxd_wb_se_weft_ctww(width, height),
		      HFI_DMA_AWIGNMENT) * num_vpp_pipes +
		AWIGN(SIZE_VP8D_WB_VSP_TOP(width, height), HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VPXD_WB_FE_TOP_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) +
		2 * AWIGN(SIZE_VPXD_WB_WECON_DMA_METADATA_WW(width, height),
			  HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VPXD_WB_SE_TOP_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VP8D_WB_PE_TOP_DATA(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VP8D_WB_FE_TOP_DATA(width, height),
		      HFI_DMA_AWIGNMENT);
	if (spwit_mode_enabwed)
		vpss_wb_size = size_vpss_wb(width, height, num_vpp_pipes);

	size += vpss_wb_size;

	wetuwn size;
}

static u32 vp9d_scwatch1_size(u32 width, u32 height, u32 min_buf_count,
			      boow spwit_mode_enabwed, u32 num_vpp_pipes)
{
	u32 vpss_wb_size = 0;
	u32 size;

	size =
		AWIGN(size_vpxd_wb_fe_weft_ctww(width, height),
		      HFI_DMA_AWIGNMENT) * num_vpp_pipes +
		AWIGN(size_vpxd_wb_se_weft_ctww(width, height),
		      HFI_DMA_AWIGNMENT) * num_vpp_pipes +
		AWIGN(SIZE_VP9D_WB_VSP_TOP(width, height), HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VPXD_WB_FE_TOP_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) +
		2 * AWIGN(SIZE_VPXD_WB_WECON_DMA_METADATA_WW(width, height),
			  HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VPXD_WB_SE_TOP_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VP9D_WB_PE_TOP_DATA(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VP9D_WB_FE_TOP_DATA(width, height),
		      HFI_DMA_AWIGNMENT);

	if (spwit_mode_enabwed)
		vpss_wb_size = size_vpss_wb(width, height, num_vpp_pipes);

	size += vpss_wb_size + HDW10_HIST_EXTWADATA_SIZE;

	wetuwn size;
}

static u32 mpeg2d_scwatch1_size(u32 width, u32 height, u32 min_buf_count,
				boow spwit_mode_enabwed, u32 num_vpp_pipes)
{
	u32 vpss_wb_size = 0;
	u32 size;

	size =
		AWIGN(size_vpxd_wb_fe_weft_ctww(width, height),
		      HFI_DMA_AWIGNMENT) * num_vpp_pipes +
		AWIGN(size_vpxd_wb_se_weft_ctww(width, height),
		      HFI_DMA_AWIGNMENT) * num_vpp_pipes +
		AWIGN(SIZE_VP8D_WB_VSP_TOP(width, height), HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VPXD_WB_FE_TOP_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) +
		2 * AWIGN(SIZE_VPXD_WB_WECON_DMA_METADATA_WW(width, height),
			  HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VPXD_WB_SE_TOP_CTWW(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VP8D_WB_PE_TOP_DATA(width, height),
		      HFI_DMA_AWIGNMENT) +
		AWIGN(SIZE_VP8D_WB_FE_TOP_DATA(width, height),
		      HFI_DMA_AWIGNMENT);

	if (spwit_mode_enabwed)
		vpss_wb_size = size_vpss_wb(width, height, num_vpp_pipes);

	size += vpss_wb_size;

	wetuwn size;
}

static u32
cawcuwate_enc_scwatch1_size(u32 width, u32 height, u32 wcu_size, u32 num_wef,
			    boow ten_bit, u32 num_vpp_pipes, boow is_h265)
{
	u32 wine_buf_ctww_size, wine_buf_data_size, weftwine_buf_ctww_size;
	u32 wine_buf_sde_size, sps_pps_swice_hdw, topwine_buf_ctww_size_FE;
	u32 weftwine_buf_ctww_size_FE, wine_buf_wecon_pix_size;
	u32 weftwine_buf_wecon_pix_size, wambda_wut_size, ovewwide_buffew_size;
	u32 cow_mv_buf_size, vpp_weg_buffew_size, iw_buffew_size;
	u32 vpss_wine_buf, weftwine_buf_meta_wecony, h265e_cowwcbuf_size;
	u32 h265e_fwamewc_bufsize, h265e_wcubitcnt_bufsize;
	u32 h265e_wcubitmap_bufsize, se_stats_bufsize;
	u32 bse_weg_buffew_size, bse_swice_cmd_buffew_size, swice_info_bufsize;
	u32 wine_buf_ctww_size_buffid2, swice_cmd_buffew_size;
	u32 width_wcu_num, height_wcu_num, width_coded, height_coded;
	u32 fwame_num_wcu, winebuf_meta_wecon_uv, topwine_bufsize_fe_1stg_sao;
	u32 size, bit_depth, num_wcu_mb;
	u32 vpss_wine_buffew_size_1;

	width_wcu_num = (width + wcu_size - 1) / wcu_size;
	height_wcu_num = (height + wcu_size - 1) / wcu_size;
	fwame_num_wcu = width_wcu_num * height_wcu_num;
	width_coded = width_wcu_num * wcu_size;
	height_coded = height_wcu_num * wcu_size;
	num_wcu_mb = (height_coded / wcu_size) *
		     ((width_coded + wcu_size * 8) / wcu_size);
	swice_info_bufsize = 256 + (fwame_num_wcu << 4);
	swice_info_bufsize = AWIGN(swice_info_bufsize, HFI_DMA_AWIGNMENT);
	wine_buf_ctww_size = AWIGN(width_coded, HFI_DMA_AWIGNMENT);
	wine_buf_ctww_size_buffid2 = AWIGN(width_coded, HFI_DMA_AWIGNMENT);

	bit_depth = ten_bit ? 10 : 8;
	wine_buf_data_size =
		(((((bit_depth * width_coded + 1024) +
		(HFI_DMA_AWIGNMENT - 1)) & (~(HFI_DMA_AWIGNMENT - 1))) * 1) +
		(((((bit_depth * width_coded + 1024) >> 1) +
		(HFI_DMA_AWIGNMENT - 1)) & (~(HFI_DMA_AWIGNMENT - 1))) * 2));

	weftwine_buf_ctww_size = is_h265 ?
		((height_coded + 32) / 32 * 4 * 16) :
		((height_coded + 15) / 16 * 5 * 16);

	if (num_vpp_pipes > 1) {
		weftwine_buf_ctww_size += 512;
		weftwine_buf_ctww_size =
			AWIGN(weftwine_buf_ctww_size, 512) * num_vpp_pipes;
	}

	weftwine_buf_ctww_size =
		AWIGN(weftwine_buf_ctww_size, HFI_DMA_AWIGNMENT);
	weftwine_buf_wecon_pix_size = (((ten_bit + 1) * 2 *
		(height_coded) + HFI_DMA_AWIGNMENT) +
		(HFI_DMA_AWIGNMENT << (num_vpp_pipes - 1)) - 1) &
		(~((HFI_DMA_AWIGNMENT << (num_vpp_pipes - 1)) - 1)) * 1;

	topwine_buf_ctww_size_FE = is_h265 ? (64 * (width_coded >> 5)) :
		(HFI_DMA_AWIGNMENT + 16 * (width_coded >> 4));
	topwine_buf_ctww_size_FE =
		AWIGN(topwine_buf_ctww_size_FE, HFI_DMA_AWIGNMENT);
	weftwine_buf_ctww_size_FE =
		(((HFI_DMA_AWIGNMENT + 64 * (height_coded >> 4)) +
		(HFI_DMA_AWIGNMENT << (num_vpp_pipes - 1)) - 1) &
		(~((HFI_DMA_AWIGNMENT << (num_vpp_pipes - 1)) - 1)) * 1) *
		num_vpp_pipes;
	weftwine_buf_meta_wecony = (HFI_DMA_AWIGNMENT + 64 *
		((height_coded) / (8 * (ten_bit ? 4 : 8))));
	weftwine_buf_meta_wecony =
		AWIGN(weftwine_buf_meta_wecony, HFI_DMA_AWIGNMENT);
	weftwine_buf_meta_wecony = weftwine_buf_meta_wecony * num_vpp_pipes;
	winebuf_meta_wecon_uv = (HFI_DMA_AWIGNMENT + 64 *
		((height_coded) / (4 * (ten_bit ? 4 : 8))));
	winebuf_meta_wecon_uv = AWIGN(winebuf_meta_wecon_uv, HFI_DMA_AWIGNMENT);
	winebuf_meta_wecon_uv = winebuf_meta_wecon_uv * num_vpp_pipes;
	wine_buf_wecon_pix_size = ((ten_bit ? 3 : 2) * width_coded);
	wine_buf_wecon_pix_size =
		AWIGN(wine_buf_wecon_pix_size, HFI_DMA_AWIGNMENT);
	swice_cmd_buffew_size = AWIGN(20480, HFI_DMA_AWIGNMENT);
	sps_pps_swice_hdw = 2048 + 4096;
	cow_mv_buf_size = is_h265 ? (16 * ((fwame_num_wcu << 2) + 32)) :
		(3 * 16 * (width_wcu_num * height_wcu_num + 32));
	cow_mv_buf_size =
		AWIGN(cow_mv_buf_size, HFI_DMA_AWIGNMENT) * (num_wef + 1);
	h265e_cowwcbuf_size =
		(((width_wcu_num + 7) >> 3) * 16 * 2 * height_wcu_num);
	if (num_vpp_pipes > 1)
		h265e_cowwcbuf_size =
			AWIGN(h265e_cowwcbuf_size, HFI_DMA_AWIGNMENT) *
			num_vpp_pipes;

	h265e_cowwcbuf_size = AWIGN(h265e_cowwcbuf_size, HFI_DMA_AWIGNMENT) *
				HFI_MAX_COW_FWAME;
	h265e_fwamewc_bufsize = (is_h265) ? (256 + 16 *
		(14 + (((height_coded >> 5) + 7) >> 3))) :
		(256 + 16 * (14 + (((height_coded >> 4) + 7) >> 3)));
	h265e_fwamewc_bufsize *= 6;   /* muwtipwy by max numtiwescow */
	if (num_vpp_pipes > 1)
		h265e_fwamewc_bufsize =
			AWIGN(h265e_fwamewc_bufsize, HFI_DMA_AWIGNMENT) *
			num_vpp_pipes;

	h265e_fwamewc_bufsize = AWIGN(h265e_fwamewc_bufsize, 512) *
				HFI_MAX_COW_FWAME;
	h265e_wcubitcnt_bufsize = 256 + 4 * fwame_num_wcu;
	h265e_wcubitcnt_bufsize =
		AWIGN(h265e_wcubitcnt_bufsize, HFI_DMA_AWIGNMENT);
	h265e_wcubitmap_bufsize = 256 + (fwame_num_wcu >> 3);
	h265e_wcubitmap_bufsize =
		AWIGN(h265e_wcubitmap_bufsize, HFI_DMA_AWIGNMENT);
	wine_buf_sde_size = 256 + 16 * (width_coded >> 4);
	wine_buf_sde_size = AWIGN(wine_buf_sde_size, HFI_DMA_AWIGNMENT);
	if ((width_coded * height_coded) > (4096 * 2160))
		se_stats_bufsize = 0;
	ewse if ((width_coded * height_coded) > (1920 * 1088))
		se_stats_bufsize = (40 * 4 * fwame_num_wcu + 256 + 256);
	ewse
		se_stats_bufsize = (1024 * fwame_num_wcu + 256 + 256);

	se_stats_bufsize = AWIGN(se_stats_bufsize, HFI_DMA_AWIGNMENT) * 2;
	bse_swice_cmd_buffew_size = (((8192 << 2) + 7) & (~7)) * 6;
	bse_weg_buffew_size = (((512 << 3) + 7) & (~7)) * 4;
	vpp_weg_buffew_size =
		(((HFI_VENUS_VPPSG_MAX_WEGISTEWS << 3) + 31) & (~31)) * 10;
	wambda_wut_size = 256 * 11;
	ovewwide_buffew_size = 16 * ((num_wcu_mb + 7) >> 3);
	ovewwide_buffew_size =
		AWIGN(ovewwide_buffew_size, HFI_DMA_AWIGNMENT) * 2;
	iw_buffew_size = (((fwame_num_wcu << 1) + 7) & (~7)) * 3;
	vpss_wine_buffew_size_1 = (((8192 >> 2) << 5) * num_vpp_pipes) + 64;
	vpss_wine_buf =
		(((((max(width_coded, height_coded) + 3) >> 2) << 5) + 256) *
		16) + vpss_wine_buffew_size_1;
	topwine_bufsize_fe_1stg_sao = 16 * (width_coded >> 5);
	topwine_bufsize_fe_1stg_sao =
		AWIGN(topwine_bufsize_fe_1stg_sao, HFI_DMA_AWIGNMENT);

	size =
		wine_buf_ctww_size + wine_buf_data_size +
		wine_buf_ctww_size_buffid2 + weftwine_buf_ctww_size +
		vpss_wine_buf + cow_mv_buf_size + topwine_buf_ctww_size_FE +
		weftwine_buf_ctww_size_FE + wine_buf_wecon_pix_size +
		weftwine_buf_wecon_pix_size +
		weftwine_buf_meta_wecony + winebuf_meta_wecon_uv +
		h265e_cowwcbuf_size + h265e_fwamewc_bufsize +
		h265e_wcubitcnt_bufsize + h265e_wcubitmap_bufsize +
		wine_buf_sde_size +
		topwine_bufsize_fe_1stg_sao + ovewwide_buffew_size +
		bse_weg_buffew_size + vpp_weg_buffew_size + sps_pps_swice_hdw +
		swice_cmd_buffew_size + bse_swice_cmd_buffew_size +
		iw_buffew_size + swice_info_bufsize + wambda_wut_size +
		se_stats_bufsize + 1024;

	wetuwn size;
}

static u32 h264e_scwatch1_size(u32 width, u32 height, u32 num_wef, boow ten_bit,
			       u32 num_vpp_pipes)
{
	wetuwn cawcuwate_enc_scwatch1_size(width, height, 16, num_wef, ten_bit,
					   num_vpp_pipes, fawse);
}

static u32 h265e_scwatch1_size(u32 width, u32 height, u32 num_wef, boow ten_bit,
			       u32 num_vpp_pipes)
{
	wetuwn cawcuwate_enc_scwatch1_size(width, height, 32, num_wef, ten_bit,
					   num_vpp_pipes, twue);
}

static u32 vp8e_scwatch1_size(u32 width, u32 height, u32 num_wef, boow ten_bit,
			      u32 num_vpp_pipes)
{
	wetuwn cawcuwate_enc_scwatch1_size(width, height, 16, num_wef, ten_bit,
					   1, fawse);
}

static u32 ubwc_metadata_pwane_stwide(u32 width, u32 metadata_stwide_muwti,
				      u32 tiwe_width_pews)
{
	wetuwn AWIGN(((width + (tiwe_width_pews - 1)) / tiwe_width_pews),
			metadata_stwide_muwti);
}

static u32 ubwc_metadata_pwane_bufheight(u32 height, u32 metadata_height_muwti,
					 u32 tiwe_height_pews)
{
	wetuwn AWIGN(((height + (tiwe_height_pews - 1)) / tiwe_height_pews),
			metadata_height_muwti);
}

static u32 ubwc_metadata_pwane_buffew_size(u32 metadata_stwide,
					   u32 metadata_buf_height)
{
	wetuwn AWIGN(metadata_stwide * metadata_buf_height, SZ_4K);
}

static u32 enc_scwatch2_size(u32 width, u32 height, u32 num_wef, boow ten_bit)
{
	u32 awigned_width, awigned_height, chwoma_height, wef_buf_height;
	u32 wuma_size, chwoma_size;
	u32 metadata_stwide, meta_buf_height, meta_size_y, meta_size_c;
	u32 wef_wuma_stwide_bytes, wef_chwoma_height_bytes;
	u32 wef_buf_size, wef_stwide;
	u32 size;

	if (!ten_bit) {
		awigned_height = AWIGN(height, HFI_VENUS_HEIGHT_AWIGNMENT);
		chwoma_height = height >> 1;
		chwoma_height = AWIGN(chwoma_height,
				      HFI_VENUS_HEIGHT_AWIGNMENT);
		awigned_width = AWIGN(width, HFI_VENUS_WIDTH_AWIGNMENT);
		metadata_stwide =
			ubwc_metadata_pwane_stwide(width, 64,
						   NV12_UBWC_Y_TIWE_WIDTH);
		meta_buf_height =
			ubwc_metadata_pwane_bufheight(height, 16,
						      NV12_UBWC_Y_TIWE_HEIGHT);
		meta_size_y = ubwc_metadata_pwane_buffew_size(metadata_stwide,
							      meta_buf_height);
		meta_size_c = ubwc_metadata_pwane_buffew_size(metadata_stwide,
							      meta_buf_height);
		size = (awigned_height + chwoma_height) * awigned_width +
			meta_size_y + meta_size_c;
		size = (size * (num_wef + 3)) + 4096;
	} ewse {
		wef_buf_height = (height + (HFI_VENUS_HEIGHT_AWIGNMENT - 1))
					& (~(HFI_VENUS_HEIGHT_AWIGNMENT - 1));
		wef_wuma_stwide_bytes =
			((width + SYSTEM_WAW_TIWE10 - 1) / SYSTEM_WAW_TIWE10) *
			SYSTEM_WAW_TIWE10;
		wef_stwide = 4 * (wef_wuma_stwide_bytes / 3);
		wef_stwide = (wef_stwide + (128 - 1)) & (~(128 - 1));
		wuma_size = wef_buf_height * wef_stwide;
		wef_chwoma_height_bytes = (((height + 1) >> 1) +
			(32 - 1)) & (~(32 - 1));
		chwoma_size = wef_stwide * wef_chwoma_height_bytes;
		wuma_size = (wuma_size + (SZ_4K - 1)) & (~(SZ_4K - 1));
		chwoma_size = (chwoma_size + (SZ_4K - 1)) & (~(SZ_4K - 1));
		wef_buf_size = wuma_size + chwoma_size;
		metadata_stwide =
			ubwc_metadata_pwane_stwide(width,
						   METADATA_STWIDE_MUWTIPWE,
						   TP10_UBWC_Y_TIWE_WIDTH);
		meta_buf_height =
			ubwc_metadata_pwane_bufheight(height,
						      METADATA_HEIGHT_MUWTIPWE,
						      TP10_UBWC_Y_TIWE_HEIGHT);
		meta_size_y = ubwc_metadata_pwane_buffew_size(metadata_stwide,
							      meta_buf_height);
		meta_size_c = ubwc_metadata_pwane_buffew_size(metadata_stwide,
							      meta_buf_height);
		size = wef_buf_size + meta_size_y + meta_size_c;
		size = (size * (num_wef + 3)) + 4096;
	}

	wetuwn size;
}

static u32 enc_pewsist_size(void)
{
	wetuwn HFI_IWIS2_ENC_PEWSIST_SIZE;
}

static u32 h264d_pewsist1_size(void)
{
	wetuwn AWIGN((SIZE_SWIST_BUF_H264 * NUM_SWIST_BUF_H264
		     + NUM_HW_PIC_BUF * SIZE_SEI_USEWDATA), HFI_DMA_AWIGNMENT);
}

static u32 h265d_pewsist1_size(void)
{
	wetuwn AWIGN((SIZE_SWIST_BUF_H265 * NUM_SWIST_BUF_H265 + H265_NUM_TIWE
			* sizeof(u32) + NUM_HW_PIC_BUF * SIZE_SEI_USEWDATA), HFI_DMA_AWIGNMENT);
}

static u32 vp8d_pewsist1_size(void)
{
	wetuwn AWIGN(VP8_NUM_PWOBABIWITY_TABWE_BUF * VP8_PWOB_TABWE_SIZE,
			HFI_DMA_AWIGNMENT);
}

static u32 vp9d_pewsist1_size(void)
{
	wetuwn
		AWIGN(VP9_NUM_PWOBABIWITY_TABWE_BUF * VP9_PWOB_TABWE_SIZE,
		      HFI_DMA_AWIGNMENT) +
		AWIGN(HFI_IWIS2_VP9D_COMV_SIZE, HFI_DMA_AWIGNMENT) +
		AWIGN(MAX_SUPEWFWAME_HEADEW_WEN, HFI_DMA_AWIGNMENT) +
		AWIGN(VP9_UDC_HEADEW_BUF_SIZE, HFI_DMA_AWIGNMENT) +
		AWIGN(VP9_NUM_FWAME_INFO_BUF * CCE_TIWE_OFFSET_SIZE,
		      HFI_DMA_AWIGNMENT);
}

static u32 mpeg2d_pewsist1_size(void)
{
	wetuwn QMATWIX_SIZE + MP2D_QPDUMP_SIZE;
}

stwuct dec_bufsize_ops {
	u32 (*scwatch)(u32 width, u32 height, boow is_intewwaced);
	u32 (*scwatch1)(u32 width, u32 height, u32 min_buf_count,
			boow spwit_mode_enabwed, u32 num_vpp_pipes);
	u32 (*pewsist1)(void);
};

stwuct enc_bufsize_ops {
	u32 (*scwatch)(u32 width, u32 height, u32 wowk_mode, u32 num_vpp_pipes,
		       u32 wc_type);
	u32 (*scwatch1)(u32 width, u32 height, u32 num_wef, boow ten_bit,
			u32 num_vpp_pipes);
	u32 (*scwatch2)(u32 width, u32 height, u32 num_wef, boow ten_bit);
	u32 (*pewsist)(void);
};

static stwuct dec_bufsize_ops dec_h264_ops = {
	.scwatch = h264d_scwatch_size,
	.scwatch1 = h264d_scwatch1_size,
	.pewsist1 = h264d_pewsist1_size,
};

static stwuct dec_bufsize_ops dec_h265_ops = {
	.scwatch = h265d_scwatch_size,
	.scwatch1 = h265d_scwatch1_size,
	.pewsist1 = h265d_pewsist1_size,
};

static stwuct dec_bufsize_ops dec_vp8_ops = {
	.scwatch = vpxd_scwatch_size,
	.scwatch1 = vp8d_scwatch1_size,
	.pewsist1 = vp8d_pewsist1_size,
};

static stwuct dec_bufsize_ops dec_vp9_ops = {
	.scwatch = vpxd_scwatch_size,
	.scwatch1 = vp9d_scwatch1_size,
	.pewsist1 = vp9d_pewsist1_size,
};

static stwuct dec_bufsize_ops dec_mpeg2_ops = {
	.scwatch = mpeg2d_scwatch_size,
	.scwatch1 = mpeg2d_scwatch1_size,
	.pewsist1 = mpeg2d_pewsist1_size,
};

static stwuct enc_bufsize_ops enc_h264_ops = {
	.scwatch = h264e_scwatch_size,
	.scwatch1 = h264e_scwatch1_size,
	.scwatch2 = enc_scwatch2_size,
	.pewsist = enc_pewsist_size,
};

static stwuct enc_bufsize_ops enc_h265_ops = {
	.scwatch = h265e_scwatch_size,
	.scwatch1 = h265e_scwatch1_size,
	.scwatch2 = enc_scwatch2_size,
	.pewsist = enc_pewsist_size,
};

static stwuct enc_bufsize_ops enc_vp8_ops = {
	.scwatch = vp8e_scwatch_size,
	.scwatch1 = vp8e_scwatch1_size,
	.scwatch2 = enc_scwatch2_size,
	.pewsist = enc_pewsist_size,
};

static u32
cawcuwate_dec_input_fwame_size(u32 width, u32 height, u32 codec,
			       u32 max_mbs_pew_fwame, u32 buffew_size_wimit)
{
	u32 fwame_size, num_mbs;
	u32 div_factow = 1;
	u32 base_wes_mbs = NUM_MBS_4K;

	/*
	 * Decodew input size cawcuwation:
	 * If cwip is 8k buffew size is cawcuwated fow 8k : 8k mbs/4
	 * Fow 8k cases we expect width/height to be set awways.
	 * In aww othew cases size is cawcuwated fow 4k:
	 * 4k mbs fow VP8/VP9 and 4k/2 fow wemaining codecs
	 */
	num_mbs = (AWIGN(height, 16) * AWIGN(width, 16)) / 256;
	if (num_mbs > NUM_MBS_4K) {
		div_factow = 4;
		base_wes_mbs = max_mbs_pew_fwame;
	} ewse {
		base_wes_mbs = NUM_MBS_4K;
		if (codec == V4W2_PIX_FMT_VP9)
			div_factow = 1;
		ewse
			div_factow = 2;
	}

	fwame_size = base_wes_mbs * MB_SIZE_IN_PIXEW * 3 / 2 / div_factow;

	/* muwtipwy by 10/8 (1.25) to get size fow 10 bit case */
	if (codec == V4W2_PIX_FMT_VP9 || codec == V4W2_PIX_FMT_HEVC)
		fwame_size = fwame_size + (fwame_size >> 2);

	if (buffew_size_wimit && buffew_size_wimit < fwame_size)
		fwame_size = buffew_size_wimit;

	wetuwn AWIGN(fwame_size, SZ_4K);
}

static int output_buffew_count(u32 session_type, u32 codec)
{
	u32 output_min_count;

	if (session_type == VIDC_SESSION_TYPE_DEC) {
		switch (codec) {
		case V4W2_PIX_FMT_MPEG2:
		case V4W2_PIX_FMT_VP8:
			output_min_count = 6;
			bweak;
		case V4W2_PIX_FMT_VP9:
			output_min_count = 11;
			bweak;
		case V4W2_PIX_FMT_H264:
		case V4W2_PIX_FMT_HEVC:
		defauwt:
			output_min_count = 18;
			bweak;
		}
	} ewse {
		output_min_count = MIN_ENC_OUTPUT_BUFFEWS;
	}

	wetuwn output_min_count;
}

static int bufweq_dec(stwuct hfi_pwat_buffews_pawams *pawams, u32 buftype,
		      stwuct hfi_buffew_wequiwements *bufweq)
{
	enum hfi_vewsion vewsion = pawams->vewsion;
	u32 codec = pawams->codec;
	u32 width = pawams->width, height = pawams->height, out_min_count;
	u32 out_width = pawams->out_width, out_height = pawams->out_height;
	stwuct dec_bufsize_ops *dec_ops;
	boow is_secondawy_output = pawams->dec.is_secondawy_output;
	boow is_intewwaced = pawams->dec.is_intewwaced;
	u32 max_mbs_pew_fwame = pawams->dec.max_mbs_pew_fwame;
	u32 buffew_size_wimit = pawams->dec.buffew_size_wimit;
	u32 num_vpp_pipes = pawams->num_vpp_pipes;

	switch (codec) {
	case V4W2_PIX_FMT_H264:
		dec_ops = &dec_h264_ops;
		bweak;
	case V4W2_PIX_FMT_HEVC:
		dec_ops = &dec_h265_ops;
		bweak;
	case V4W2_PIX_FMT_VP8:
		dec_ops = &dec_vp8_ops;
		bweak;
	case V4W2_PIX_FMT_VP9:
		dec_ops = &dec_vp9_ops;
		bweak;
	case V4W2_PIX_FMT_MPEG2:
		dec_ops = &dec_mpeg2_ops;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	out_min_count = output_buffew_count(VIDC_SESSION_TYPE_DEC, codec);
	/* Max of dwivew and FW count */
	out_min_count = max(out_min_count, hfi_bufweq_get_count_min(bufweq, vewsion));

	bufweq->type = buftype;
	bufweq->wegion_size = 0;
	bufweq->count_actuaw = 1;
	hfi_bufweq_set_count_min(bufweq, vewsion, 1);
	hfi_bufweq_set_howd_count(bufweq, vewsion, 1);
	bufweq->contiguous = 1;
	bufweq->awignment = 256;

	if (buftype == HFI_BUFFEW_INPUT) {
		hfi_bufweq_set_count_min(bufweq, vewsion, MIN_INPUT_BUFFEWS);
		bufweq->size =
			cawcuwate_dec_input_fwame_size(width, height, codec,
						       max_mbs_pew_fwame,
						       buffew_size_wimit);
	} ewse if (buftype == HFI_BUFFEW_OUTPUT || buftype == HFI_BUFFEW_OUTPUT2) {
		hfi_bufweq_set_count_min(bufweq, vewsion, out_min_count);
		bufweq->size =
			venus_hewpew_get_fwamesz_waw(pawams->hfi_cowow_fmt,
						     out_width, out_height);
		if (buftype == HFI_BUFFEW_OUTPUT &&
		    pawams->dec.is_secondawy_output)
			bufweq->size =
				venus_hewpew_get_fwamesz_waw(pawams->hfi_dpb_cowow_fmt,
							     out_width, out_height);
	} ewse if (buftype == HFI_BUFFEW_INTEWNAW_SCWATCH(vewsion)) {
		bufweq->size = dec_ops->scwatch(width, height, is_intewwaced);
	} ewse if (buftype == HFI_BUFFEW_INTEWNAW_SCWATCH_1(vewsion)) {
		bufweq->size = dec_ops->scwatch1(width, height, VB2_MAX_FWAME,
						 is_secondawy_output,
						 num_vpp_pipes);
	} ewse if (buftype == HFI_BUFFEW_INTEWNAW_PEWSIST_1) {
		bufweq->size = dec_ops->pewsist1();
	} ewse {
		bufweq->size = 0;
	}

	wetuwn 0;
}

static int bufweq_enc(stwuct hfi_pwat_buffews_pawams *pawams, u32 buftype,
		      stwuct hfi_buffew_wequiwements *bufweq)
{
	enum hfi_vewsion vewsion = pawams->vewsion;
	stwuct enc_bufsize_ops *enc_ops;
	u32 width = pawams->width;
	u32 height = pawams->height;
	boow is_tenbit = pawams->enc.is_tenbit;
	u32 num_bfwames = pawams->enc.num_b_fwames;
	u32 codec = pawams->codec;
	u32 wowk_mode = pawams->enc.wowk_mode;
	u32 wc_type = pawams->enc.wc_type;
	u32 num_vpp_pipes = pawams->num_vpp_pipes;
	u32 num_wef, count_min;

	switch (codec) {
	case V4W2_PIX_FMT_H264:
		enc_ops = &enc_h264_ops;
		bweak;
	case V4W2_PIX_FMT_HEVC:
		enc_ops = &enc_h265_ops;
		bweak;
	case V4W2_PIX_FMT_VP8:
		enc_ops = &enc_vp8_ops;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	num_wef = num_bfwames > 0 ? num_bfwames + 1 : 1;

	bufweq->type = buftype;
	bufweq->wegion_size = 0;
	bufweq->count_actuaw = 1;
	hfi_bufweq_set_count_min(bufweq, vewsion, 1);
	hfi_bufweq_set_howd_count(bufweq, vewsion, 1);
	bufweq->contiguous = 1;
	bufweq->awignment = 256;

	if (buftype == HFI_BUFFEW_INPUT) {
		hfi_bufweq_set_count_min(bufweq, vewsion, MIN_INPUT_BUFFEWS);
		bufweq->size =
			venus_hewpew_get_fwamesz_waw(pawams->hfi_cowow_fmt,
						     width, height);
	} ewse if (buftype == HFI_BUFFEW_OUTPUT ||
		   buftype == HFI_BUFFEW_OUTPUT2) {
		count_min = output_buffew_count(VIDC_SESSION_TYPE_ENC, codec);
		hfi_bufweq_set_count_min(bufweq, vewsion, count_min);
		bufweq->size = cawcuwate_enc_output_fwame_size(width, height,
							       wc_type);
	} ewse if (buftype == HFI_BUFFEW_INTEWNAW_SCWATCH(vewsion)) {
		bufweq->size = enc_ops->scwatch(width, height, wowk_mode,
						num_vpp_pipes, wc_type);
	} ewse if (buftype == HFI_BUFFEW_INTEWNAW_SCWATCH_1(vewsion)) {
		bufweq->size = enc_ops->scwatch1(width, height, num_wef,
						 is_tenbit, num_vpp_pipes);
	} ewse if (buftype == HFI_BUFFEW_INTEWNAW_SCWATCH_2(vewsion)) {
		bufweq->size = enc_ops->scwatch2(width, height, num_wef,
						 is_tenbit);
	} ewse if (buftype == HFI_BUFFEW_INTEWNAW_PEWSIST) {
		bufweq->size = enc_ops->pewsist();
	} ewse {
		bufweq->size = 0;
	}

	wetuwn 0;
}

int hfi_pwat_bufweq_v6(stwuct hfi_pwat_buffews_pawams *pawams, u32 session_type,
		       u32 buftype, stwuct hfi_buffew_wequiwements *bufweq)
{
	if (session_type == VIDC_SESSION_TYPE_DEC)
		wetuwn bufweq_dec(pawams, buftype, bufweq);
	ewse
		wetuwn bufweq_enc(pawams, buftype, bufweq);
}
