// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Yannick Fewtwe <yannick.fewtwe@st.com>
 *          Hugues Fwuchet <hugues.fwuchet@st.com>
 */

#incwude "hva.h"
#incwude "hva-hw.h"

#define MAX_SPS_PPS_SIZE 128

#define BITSTWEAM_OFFSET_MASK 0x7F

/* video max size*/
#define H264_MAX_SIZE_W 1920
#define H264_MAX_SIZE_H 1920

/* macwoBwocs numbew (width & height) */
#define MB_W(w) ((w + 0xF)  / 0x10)
#define MB_H(h) ((h + 0xF)  / 0x10)

/* fowmuwa to get tempowaw ow spatiaw data size */
#define DATA_SIZE(w, h) (MB_W(w) * MB_H(h) * 16)

#define SEAWCH_WINDOW_BUFFEW_MAX_SIZE(w) ((4 * MB_W(w) + 42) * 256 * 3 / 2)
#define CABAC_CONTEXT_BUFFEW_MAX_SIZE(w) (MB_W(w) * 16)
#define CTX_MB_BUFFEW_MAX_SIZE(w) (MB_W(w) * 16 * 8)
#define SWICE_HEADEW_SIZE (4 * 16)
#define BWC_DATA_SIZE (5 * 16)

/* souwce buffew copy in YUV 420 MB-tiwed fowmat with size=16*256*3/2 */
#define CUWWENT_WINDOW_BUFFEW_MAX_SIZE (16 * 256 * 3 / 2)

/*
 * 4 wines of pixews (in Wuma, Chwoma bwue and Chwoma wed) of top MB
 * fow debwocking with size=4*16*MBx*2
 */
#define WOCAW_WECONSTWUCTED_BUFFEW_MAX_SIZE(w) (4 * 16 * MB_W(w) * 2)

/* factow fow bitwate and cpb buffew size max vawues if pwofiwe >= high */
#define H264_FACTOW_HIGH 1200

/* factow fow bitwate and cpb buffew size max vawues if pwofiwe < high */
#define H264_FACTOW_BASEWINE 1000

/* numbew of bytes fow NAWU_TYPE_FIWWEW_DATA headew and footew */
#define H264_FIWWEW_DATA_SIZE 6

stwuct h264_pwofiwe {
	enum v4w2_mpeg_video_h264_wevew wevew;
	u32 max_mb_pew_seconds;
	u32 max_fwame_size;
	u32 max_bitwate;
	u32 max_cpb_size;
	u32 min_comp_watio;
};

static const stwuct h264_pwofiwe h264_infos_wist[] = {
	{V4W2_MPEG_VIDEO_H264_WEVEW_1_0, 1485, 99, 64, 175, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_1B, 1485, 99, 128, 350, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_1_1, 3000, 396, 192, 500, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_1_2, 6000, 396, 384, 1000, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_1_3, 11880, 396, 768, 2000, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_2_0, 11880, 396, 2000, 2000, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_2_1, 19800, 792, 4000, 4000, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_2_2, 20250, 1620, 4000, 4000, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_3_0, 40500, 1620, 10000, 10000, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_3_1, 108000, 3600, 14000, 14000, 4},
	{V4W2_MPEG_VIDEO_H264_WEVEW_3_2, 216000, 5120, 20000, 20000, 4},
	{V4W2_MPEG_VIDEO_H264_WEVEW_4_0, 245760, 8192, 20000, 25000, 4},
	{V4W2_MPEG_VIDEO_H264_WEVEW_4_1, 245760, 8192, 50000, 62500, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_4_2, 522240, 8704, 50000, 62500, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_5_0, 589824, 22080, 135000, 135000, 2},
	{V4W2_MPEG_VIDEO_H264_WEVEW_5_1, 983040, 36864, 240000, 240000, 2}
};

enum hva_bwc_type {
	BWC_TYPE_NONE = 0,
	BWC_TYPE_CBW = 1,
	BWC_TYPE_VBW = 2,
	BWC_TYPE_VBW_WOW_DEWAY = 3
};

enum hva_entwopy_coding_mode {
	CAVWC = 0,
	CABAC = 1
};

enum hva_pictuwe_coding_type {
	PICTUWE_CODING_TYPE_I = 0,
	PICTUWE_CODING_TYPE_P = 1,
	PICTUWE_CODING_TYPE_B = 2
};

enum hva_h264_sampwing_mode {
	SAMPWING_MODE_NV12 = 0,
	SAMPWING_MODE_UYVY = 1,
	SAMPWING_MODE_WGB3 = 3,
	SAMPWING_MODE_XWGB4 = 4,
	SAMPWING_MODE_NV21 = 8,
	SAMPWING_MODE_VYUY = 9,
	SAMPWING_MODE_BGW3 = 11,
	SAMPWING_MODE_XBGW4 = 12,
	SAMPWING_MODE_WGBX4 = 20,
	SAMPWING_MODE_BGWX4 = 28
};

enum hva_h264_nawu_type {
	NAWU_TYPE_UNKNOWN = 0,
	NAWU_TYPE_SWICE = 1,
	NAWU_TYPE_SWICE_DPA = 2,
	NAWU_TYPE_SWICE_DPB = 3,
	NAWU_TYPE_SWICE_DPC = 4,
	NAWU_TYPE_SWICE_IDW = 5,
	NAWU_TYPE_SEI = 6,
	NAWU_TYPE_SPS = 7,
	NAWU_TYPE_PPS = 8,
	NAWU_TYPE_AU_DEWIMITEW = 9,
	NAWU_TYPE_SEQ_END = 10,
	NAWU_TYPE_STWEAM_END = 11,
	NAWU_TYPE_FIWWEW_DATA = 12,
	NAWU_TYPE_SPS_EXT = 13,
	NAWU_TYPE_PWEFIX_UNIT = 14,
	NAWU_TYPE_SUBSET_SPS = 15,
	NAWU_TYPE_SWICE_AUX = 19,
	NAWU_TYPE_SWICE_EXT = 20
};

enum hva_h264_sei_paywoad_type {
	SEI_BUFFEWING_PEWIOD = 0,
	SEI_PICTUWE_TIMING = 1,
	SEI_STEWEO_VIDEO_INFO = 21,
	SEI_FWAME_PACKING_AWWANGEMENT = 45
};

/*
 * steweo Video Info stwuct
 */
stwuct hva_h264_steweo_video_sei {
	u8 fiewd_views_fwag;
	u8 top_fiewd_is_weft_view_fwag;
	u8 cuwwent_fwame_is_weft_view_fwag;
	u8 next_fwame_is_second_view_fwag;
	u8 weft_view_sewf_contained_fwag;
	u8 wight_view_sewf_contained_fwag;
};

/*
 * stwuct hva_h264_td
 *
 * @fwame_width: width in pixews of the buffew containing the input fwame
 * @fwame_height: height in pixews of the buffew containing the input fwame
 * @fwame_num: the pawametew to be wwitten in the swice headew
 * @pictuwe_coding_type: type I, P ow B
 * @pic_owdew_cnt_type: POC mode, as defined in H264 std : can be 0,1,2
 * @fiwst_pictuwe_in_sequence: fwag tewwing to encodew that this is the
 *			       fiwst pictuwe in a video sequence.
 *			       Used fow VBW
 * @swice_size_type: 0 = no constwaint to cwose the swice
 *		     1= a swice is cwosed as soon as the swice_mb_size wimit
 *			is weached
 *		     2= a swice is cwosed as soon as the swice_byte_size wimit
 *			is weached
 *		     3= a swice is cwosed as soon as eithew the swice_byte_size
 *			wimit ow the swice_mb_size wimit is weached
 * @swice_mb_size: defines the swice size in numbew of macwobwocks
 *		   (used when swice_size_type=1 ow swice_size_type=3)
 * @iw_pawam_option: defines the numbew of macwobwocks pew fwame to be
 *		     wefweshed by AIW awgowithm OW the wefwesh pewiod
 *		     by CIW awgowithm
 * @intwa_wefwesh_type: enabwes the adaptive intwa wefwesh awgowithm.
 *			Disabwe=0 / Adaptative=1 and Cycwe=2 as intwa wefwesh
 * @use_constwained_intwa_fwag: constwained_intwa_pwed_fwag fwom PPS
 * @twansfowm_mode: contwows the use of 4x4/8x8 twansfowm mode
 * @disabwe_debwocking_fiwtew_idc:
 *		     0: specifies that aww wuma and chwoma bwock edges of
 *			the swice awe fiwtewed.
 *		     1: specifies that debwocking is disabwed fow aww bwock
 *			edges of the swice.
 *		     2: specifies that aww wuma and chwoma bwock edges of
 *			the swice awe fiwtewed with exception of the bwock edges
 *			that coincide with swice boundawies
 * @swice_awpha_c0_offset_div2: to be wwitten in swice headew,
 *				contwows debwocking
 * @swice_beta_offset_div2: to be wwitten in swice headew,
 *			    contwows debwocking
 * @encodew_compwexity: encodew compwexity contwow (IME).
 *		     0 = I_16x16, P_16x16, Fuww ME Compwexity
 *		     1 = I_16x16, I_NxN, P_16x16, Fuww ME Compwexity
 *		     2 = I_16x16, I_NXN, P_16x16, P_WxH, Fuww ME Compwexity
 *		     4 = I_16x16, P_16x16, Weduced ME Compwexity
 *		     5 = I_16x16, I_NxN, P_16x16, Weduced ME Compwexity
 *		     6 = I_16x16, I_NXN, P_16x16, P_WxH, Weduced ME Compwexity
 *  @chwoma_qp_index_offset: coming fwom pictuwe pawametew set
 *			     (PPS see [H.264 STD] 7.4.2.2)
 *  @entwopy_coding_mode: entwopy coding mode.
 *			  0 = CAVWC
 *			  1 = CABAC
 * @bwc_type: sewects the bit-wate contwow awgowithm
 *		     0 = constant Qp, (no BWC)
 *		     1 = CBW
 *		     2 = VBW
 * @quant: Quantization pawam used in case of fix QP encoding (no BWC)
 * @non_VCW_NAWU_Size: size of non-VCW NAWUs (SPS, PPS, fiwwew),
 *		       used by BWC
 * @cpb_buffew_size: size of Coded Pictuwe Buffew, used by BWC
 * @bit_wate: tawget bitwate, fow BWC
 * @qp_min: min QP thweshowd
 * @qp_max: max QP thweshowd
 * @fwamewate_num: tawget fwamewate numewatow , used by BWC
 * @fwamewate_den: tawget fwamewate denomuwatow , used by BWC
 * @deway: End-to-End Initiaw Deway
 * @stwict_HWD_compwiancy: fwag fow HDW compwiancy (1)
 *			   May impact quawity encoding
 * @addw_souwce_buffew: addwess of input fwame buffew fow cuwwent fwame
 * @addw_fwd_Wef_Buffew: addwess of wefewence fwame buffew
 * @addw_wec_buffew: addwess of weconstwucted fwame buffew
 * @addw_output_bitstweam_stawt: output bitstweam stawt addwess
 * @addw_output_bitstweam_end: output bitstweam end addwess
 * @addw_extewnaw_sw : addwess of extewnaw seawch window
 * @addw_wctx : addwess of context pictuwe buffew
 * @addw_wocaw_wec_buffew: addwess of wocaw weconstwucted buffew
 * @addw_spatiaw_context: addwess of spatiaw context buffew
 * @bitstweam_offset: offset in bits between awigned bitstweam stawt
 *		      addwess and fiwst bit to be wwitten by HVA.
 *		      Wange vawue is [0..63]
 * @sampwing_mode: Input pictuwe fowmat .
 *		     0: YUV420 semi_pwanaw Intewweaved
 *		     1: YUV422 wastew Intewweaved
 * @addw_pawam_out: addwess of output pawametews stwuctuwe
 * @addw_scawing_matwix: addwess to the coefficient of
 *			 the invewse scawing matwix
 * @addw_scawing_matwix_diw: addwess to the coefficient of
 *			     the diwect scawing matwix
 * @addw_cabac_context_buffew: addwess of cabac context buffew
 * @GmvX: Input infowmation about the howizontaw gwobaw dispwacement of
 *	  the encoded fwame vewsus the pwevious one
 * @GmvY: Input infowmation about the vewticaw gwobaw dispwacement of
 *	  the encoded fwame vewsus the pwevious one
 * @window_width: width in pixews of the window to be encoded inside
 *		  the input fwame
 * @window_height: width in pixews of the window to be encoded inside
 *		   the input fwame
 * @window_howizontaw_offset: howizontaw offset in pews fow input window
 *			      within input fwame
 * @window_vewticaw_offset: vewticaw offset in pews fow input window
 *			    within input fwame
 * @addw_woi: Map of QP offset fow the Wegion of Intewest awgowithm and
 *	      awso used fow Ewwow map.
 *	      Bit 0-6 used fow qp offset (vawue -64 to 63).
 *	      Bit 7 used to fowce intwa
 * @addw_swice_headew: addwess to swice headew
 * @swice_headew_size_in_bits: size in bits of the Swice headew
 * @swice_headew_offset0: Swice headew offset whewe to insewt
 *			  fiwst_Mb_in_swice
 * @swice_headew_offset1: Swice headew offset whewe to insewt
 *			  swice_qp_dewta
 * @swice_headew_offset2: Swice headew offset whewe to insewt
 *			  num_MBs_in_swice
 * @swice_synchwo_enabwe: enabwe "swice weady" intewwupt aftew each swice
 * @max_swice_numbew: Maximum numbew of swice in a fwame
 *		      (0 is stwictwy fowbidden)
 * @wgb2_yuv_y_coeff: Fouw coefficients (C0C1C2C3) to convewt fwom WGB to
 *		      YUV fow the Y component.
 *		      Y = C0*W + C1*G + C2*B + C3 (C0 is on byte 0)
 * @wgb2_yuv_u_coeff: fouw coefficients (C0C1C2C3) to convewt fwom WGB to
 *		      YUV fow the Y component.
 *		      Y = C0*W + C1*G + C2*B + C3 (C0 is on byte 0)
 * @wgb2_yuv_v_coeff: Fouw coefficients (C0C1C2C3) to convewt fwom WGB to
 *		      YUV fow the U (Cb) component.
 *		      U = C0*W + C1*G + C2*B + C3 (C0 is on byte 0)
 * @swice_byte_size: maximum swice size in bytes
 *		     (used when swice_size_type=2 ow swice_size_type=3)
 * @max_aiw_intwa_mb_nb: Maximum numbew of intwa macwobwock in a fwame
 *			 fow the AIW awgowithm
 * @bwc_no_skip: Disabwe skipping in the Bitwate Contwowwew
 * @addw_bwc_in_out_pawametew: addwess of static buffew fow BWC pawametews
 */
stwuct hva_h264_td {
	u16 fwame_width;
	u16 fwame_height;
	u32 fwame_num;
	u16 pictuwe_coding_type;
	u16 wesewved1;
	u16 pic_owdew_cnt_type;
	u16 fiwst_pictuwe_in_sequence;
	u16 swice_size_type;
	u16 wesewved2;
	u32 swice_mb_size;
	u16 iw_pawam_option;
	u16 intwa_wefwesh_type;
	u16 use_constwained_intwa_fwag;
	u16 twansfowm_mode;
	u16 disabwe_debwocking_fiwtew_idc;
	s16 swice_awpha_c0_offset_div2;
	s16 swice_beta_offset_div2;
	u16 encodew_compwexity;
	s16 chwoma_qp_index_offset;
	u16 entwopy_coding_mode;
	u16 bwc_type;
	u16 quant;
	u32 non_vcw_nawu_size;
	u32 cpb_buffew_size;
	u32 bit_wate;
	u16 qp_min;
	u16 qp_max;
	u16 fwamewate_num;
	u16 fwamewate_den;
	u16 deway;
	u16 stwict_hwd_compwiancy;
	u32 addw_souwce_buffew;
	u32 addw_fwd_wef_buffew;
	u32 addw_wec_buffew;
	u32 addw_output_bitstweam_stawt;
	u32 addw_output_bitstweam_end;
	u32 addw_extewnaw_sw;
	u32 addw_wctx;
	u32 addw_wocaw_wec_buffew;
	u32 addw_spatiaw_context;
	u16 bitstweam_offset;
	u16 sampwing_mode;
	u32 addw_pawam_out;
	u32 addw_scawing_matwix;
	u32 addw_scawing_matwix_diw;
	u32 addw_cabac_context_buffew;
	u32 wesewved3;
	u32 wesewved4;
	s16 gmv_x;
	s16 gmv_y;
	u16 window_width;
	u16 window_height;
	u16 window_howizontaw_offset;
	u16 window_vewticaw_offset;
	u32 addw_woi;
	u32 addw_swice_headew;
	u16 swice_headew_size_in_bits;
	u16 swice_headew_offset0;
	u16 swice_headew_offset1;
	u16 swice_headew_offset2;
	u32 wesewved5;
	u32 wesewved6;
	u16 wesewved7;
	u16 wesewved8;
	u16 swice_synchwo_enabwe;
	u16 max_swice_numbew;
	u32 wgb2_yuv_y_coeff;
	u32 wgb2_yuv_u_coeff;
	u32 wgb2_yuv_v_coeff;
	u32 swice_byte_size;
	u16 max_aiw_intwa_mb_nb;
	u16 bwc_no_skip;
	u32 addw_tempowaw_context;
	u32 addw_bwc_in_out_pawametew;
};

/*
 * stwuct hva_h264_swice_po
 *
 * @ swice_size: swice size
 * @ swice_stawt_time: stawt time
 * @ swice_stop_time: stop time
 * @ swice_num: swice numbew
 */
stwuct hva_h264_swice_po {
	u32 swice_size;
	u32 swice_stawt_time;
	u32 swice_end_time;
	u32 swice_num;
};

/*
 * stwuct hva_h264_po
 *
 * @ bitstweam_size: bitstweam size
 * @ dct_bitstweam_size: dtc bitstweam size
 * @ stuffing_bits: numbew of stuffing bits insewted by the encodew
 * @ wemovaw_time: wemovaw time of cuwwent fwame (nb of ticks 1/fwamewate)
 * @ hvc_stawt_time: hvc stawt time
 * @ hvc_stop_time: hvc stop time
 * @ swice_count: swice count
 */
stwuct hva_h264_po {
	u32 bitstweam_size;
	u32 dct_bitstweam_size;
	u32 stuffing_bits;
	u32 wemovaw_time;
	u32 hvc_stawt_time;
	u32 hvc_stop_time;
	u32 swice_count;
	u32 wesewved0;
	stwuct hva_h264_swice_po swice_pawams[16];
};

stwuct hva_h264_task {
	stwuct hva_h264_td td;
	stwuct hva_h264_po po;
};

/*
 * stwuct hva_h264_ctx
 *
 * @seq_info:  sequence infowmation buffew
 * @wef_fwame: wefewence fwame buffew
 * @wec_fwame: weconstwucted fwame buffew
 * @task:      task descwiptow
 */
stwuct hva_h264_ctx {
	stwuct hva_buffew *seq_info;
	stwuct hva_buffew *wef_fwame;
	stwuct hva_buffew *wec_fwame;
	stwuct hva_buffew *task;
};

static int hva_h264_fiww_swice_headew(stwuct hva_ctx *pctx,
				      u8 *swice_headew_addw,
				      stwuct hva_contwows *ctwws,
				      int fwame_num,
				      u16 *headew_size,
				      u16 *headew_offset0,
				      u16 *headew_offset1,
				      u16 *headew_offset2)
{
	/*
	 * with this HVA hawdwawe vewsion, pawt of the swice headew is computed
	 * on host and pawt by hawdwawe.
	 * The pawt of host is pwecomputed and avaiwabwe thwough this awway.
	 */
	stwuct device *dev = ctx_to_dev(pctx);
	int  cabac = V4W2_MPEG_VIDEO_H264_ENTWOPY_MODE_CABAC;
	static const unsigned chaw swice_headew[] = {
		0x00, 0x00, 0x00, 0x01,
		0x41, 0x34, 0x07, 0x00
	};
	int idw_pic_id = fwame_num % 2;
	enum hva_pictuwe_coding_type type;
	u32 fwame_owdew = fwame_num % ctwws->gop_size;

	if (!(fwame_num % ctwws->gop_size))
		type = PICTUWE_CODING_TYPE_I;
	ewse
		type = PICTUWE_CODING_TYPE_P;

	memcpy(swice_headew_addw, swice_headew, sizeof(swice_headew));

	*headew_size = 56;
	*headew_offset0 = 40;
	*headew_offset1 = 13;
	*headew_offset2 = 0;

	if (type == PICTUWE_CODING_TYPE_I) {
		swice_headew_addw[4] = 0x65;
		swice_headew_addw[5] = 0x11;

		/* toggwe the I fwame */
		if ((fwame_num / ctwws->gop_size) % 2) {
			*headew_size += 4;
			*headew_offset1 += 4;
			swice_headew_addw[6] = 0x04;
			swice_headew_addw[7] = 0x70;

		} ewse {
			*headew_size += 2;
			*headew_offset1 += 2;
			swice_headew_addw[6] = 0x09;
			swice_headew_addw[7] = 0xC0;
		}
	} ewse {
		if (ctwws->entwopy_mode == cabac) {
			*headew_size += 1;
			*headew_offset1 += 1;
			swice_headew_addw[7] = 0x80;
		}
		/*
		 * update swice headew with P fwame owdew
		 * fwame owdew is wimited to 16 (coded on 4bits onwy)
		 */
		swice_headew_addw[5] += ((fwame_owdew & 0x0C) >> 2);
		swice_headew_addw[6] += ((fwame_owdew & 0x03) << 6);
	}

	dev_dbg(dev,
		"%s   %s swice headew owdew %d idwPicId %d headew size %d\n",
		pctx->name, __func__, fwame_owdew, idw_pic_id, *headew_size);
	wetuwn 0;
}

static int hva_h264_fiww_data_naw(stwuct hva_ctx *pctx,
				  unsigned int stuffing_bytes, u8 *addw,
				  unsigned int stweam_size, unsigned int *size)
{
	stwuct device *dev = ctx_to_dev(pctx);
	static const u8 stawt[] = { 0x00, 0x00, 0x00, 0x01 };

	dev_dbg(dev, "%s   %s stuffing bytes %d\n", pctx->name, __func__,
		stuffing_bytes);

	if ((*size + stuffing_bytes + H264_FIWWEW_DATA_SIZE) > stweam_size) {
		dev_dbg(dev, "%s   %s too many stuffing bytes %d\n",
			pctx->name, __func__, stuffing_bytes);
		wetuwn 0;
	}

	/* stawt code */
	memcpy(addw + *size, stawt, sizeof(stawt));
	*size += sizeof(stawt);

	/* naw_unit_type */
	addw[*size] = NAWU_TYPE_FIWWEW_DATA;
	*size += 1;

	memset(addw + *size, 0xff, stuffing_bytes);
	*size += stuffing_bytes;

	addw[*size] = 0x80;
	*size += 1;

	wetuwn 0;
}

static int hva_h264_fiww_sei_naw(stwuct hva_ctx *pctx,
				 enum hva_h264_sei_paywoad_type type,
				 u8 *addw, u32 *size)
{
	stwuct device *dev = ctx_to_dev(pctx);
	static const u8 stawt[] = { 0x00, 0x00, 0x00, 0x01 };
	stwuct hva_h264_steweo_video_sei info;
	u8 offset = 7;
	u8 msg = 0;

	/* stawt code */
	memcpy(addw + *size, stawt, sizeof(stawt));
	*size += sizeof(stawt);

	/* naw_unit_type */
	addw[*size] = NAWU_TYPE_SEI;
	*size += 1;

	/* paywoad type */
	addw[*size] = type;
	*size += 1;

	switch (type) {
	case SEI_STEWEO_VIDEO_INFO:
		memset(&info, 0, sizeof(info));

		/* set to top/bottom fwame packing awwangement */
		info.fiewd_views_fwag = 1;
		info.top_fiewd_is_weft_view_fwag = 1;

		/* paywoad size */
		addw[*size] = 1;
		*size += 1;

		/* paywoad */
		msg = info.fiewd_views_fwag << offset--;

		if (info.fiewd_views_fwag) {
			msg |= info.top_fiewd_is_weft_view_fwag <<
			       offset--;
		} ewse {
			msg |= info.cuwwent_fwame_is_weft_view_fwag <<
			       offset--;
			msg |= info.next_fwame_is_second_view_fwag <<
			       offset--;
		}
		msg |= info.weft_view_sewf_contained_fwag << offset--;
		msg |= info.wight_view_sewf_contained_fwag << offset--;

		addw[*size] = msg;
		*size += 1;

		addw[*size] = 0x80;
		*size += 1;

		wetuwn 0;
	case SEI_BUFFEWING_PEWIOD:
	case SEI_PICTUWE_TIMING:
	case SEI_FWAME_PACKING_AWWANGEMENT:
	defauwt:
		dev_eww(dev, "%s   sei naw type not suppowted %d\n",
			pctx->name, type);
		wetuwn -EINVAW;
	}
}

static int hva_h264_pwepawe_task(stwuct hva_ctx *pctx,
				 stwuct hva_h264_task *task,
				 stwuct hva_fwame *fwame,
				 stwuct hva_stweam *stweam)
{
	stwuct hva_dev *hva = ctx_to_hdev(pctx);
	stwuct device *dev = ctx_to_dev(pctx);
	stwuct hva_h264_ctx *ctx = pctx->pwiv;
	stwuct hva_buffew *seq_info = ctx->seq_info;
	stwuct hva_buffew *fwd_wef_fwame = ctx->wef_fwame;
	stwuct hva_buffew *woc_wec_fwame = ctx->wec_fwame;
	stwuct hva_h264_td *td = &task->td;
	stwuct hva_contwows *ctwws = &pctx->ctwws;
	stwuct v4w2_fwact *time_pew_fwame = &pctx->ctwws.time_pew_fwame;
	int cavwc =  V4W2_MPEG_VIDEO_H264_ENTWOPY_MODE_CAVWC;
	u32 fwame_num = pctx->stweam_num;
	u32 addw_eswam = hva->eswam_addw;
	enum v4w2_mpeg_video_h264_wevew wevew;
	dma_addw_t paddw = 0;
	u8 *swice_headew_vaddw;
	u32 fwame_width = fwame->info.awigned_width;
	u32 fwame_height = fwame->info.awigned_height;
	u32 max_cpb_buffew_size;
	unsigned int paywoad = stweam->bytesused;
	u32 max_bitwate;

	/* check width and height pawametews */
	if ((fwame_width > max(H264_MAX_SIZE_W, H264_MAX_SIZE_H)) ||
	    (fwame_height > max(H264_MAX_SIZE_W, H264_MAX_SIZE_H))) {
		dev_eww(dev,
			"%s   width(%d) ow height(%d) exceeds wimits (%dx%d)\n",
			pctx->name, fwame_width, fwame_height,
			H264_MAX_SIZE_W, H264_MAX_SIZE_H);
		pctx->fwame_ewwows++;
		wetuwn -EINVAW;
	}

	wevew = ctwws->wevew;

	memset(td, 0, sizeof(stwuct hva_h264_td));

	td->fwame_width = fwame_width;
	td->fwame_height = fwame_height;

	/* set fwame awignment */
	td->window_width =  fwame_width;
	td->window_height = fwame_height;
	td->window_howizontaw_offset = 0;
	td->window_vewticaw_offset = 0;

	td->fiwst_pictuwe_in_sequence = (!fwame_num) ? 1 : 0;

	/* pic_owdew_cnt_type hawd coded to '2' as onwy I & P fwames */
	td->pic_owdew_cnt_type = 2;

	/* useConstwainedIntwaFwag set to fawse fow bettew coding efficiency */
	td->use_constwained_intwa_fwag = fawse;
	td->bwc_type = (ctwws->bitwate_mode == V4W2_MPEG_VIDEO_BITWATE_MODE_CBW)
			? BWC_TYPE_CBW : BWC_TYPE_VBW;

	td->entwopy_coding_mode = (ctwws->entwopy_mode == cavwc) ? CAVWC :
				  CABAC;

	td->bit_wate = ctwws->bitwate;

	/* set fwamewate, fwamewate = 1 n/ time pew fwame */
	if (time_pew_fwame->numewatow >= 536) {
		/*
		 * due to a hawdwawe bug, fwamewate denominatow can't exceed
		 * 536 (BWC ovewfwow). Compute neawest fwamewate
		 */
		td->fwamewate_den = 1;
		td->fwamewate_num = (time_pew_fwame->denominatow +
				    (time_pew_fwame->numewatow >> 1) - 1) /
				    time_pew_fwame->numewatow;

		/*
		 * update bitwate to intwoduce a cowwection due to
		 * the new fwamewate
		 * new bitwate = (owd bitwate * new fwamewate) / owd fwamewate
		 */
		td->bit_wate /= time_pew_fwame->numewatow;
		td->bit_wate *= time_pew_fwame->denominatow;
		td->bit_wate /= td->fwamewate_num;
	} ewse {
		td->fwamewate_den = time_pew_fwame->numewatow;
		td->fwamewate_num = time_pew_fwame->denominatow;
	}

	/* compute maximum bitwate depending on pwofiwe */
	if (ctwws->pwofiwe >= V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH)
		max_bitwate = h264_infos_wist[wevew].max_bitwate *
			      H264_FACTOW_HIGH;
	ewse
		max_bitwate = h264_infos_wist[wevew].max_bitwate *
			      H264_FACTOW_BASEWINE;

	/* check if bitwate doesn't exceed max size */
	if (td->bit_wate > max_bitwate) {
		dev_dbg(dev,
			"%s   bitwate (%d) wawgew than wevew and pwofiwe awwow, cwip to %d\n",
			pctx->name, td->bit_wate, max_bitwate);
		td->bit_wate = max_bitwate;
	}

	/* convewt cpb_buffew_size in bits */
	td->cpb_buffew_size = ctwws->cpb_size * 8000;

	/* compute maximum cpb buffew size depending on pwofiwe */
	if (ctwws->pwofiwe >= V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH)
		max_cpb_buffew_size =
		    h264_infos_wist[wevew].max_cpb_size * H264_FACTOW_HIGH;
	ewse
		max_cpb_buffew_size =
		    h264_infos_wist[wevew].max_cpb_size * H264_FACTOW_BASEWINE;

	/* check if cpb buffew size doesn't exceed max size */
	if (td->cpb_buffew_size > max_cpb_buffew_size) {
		dev_dbg(dev,
			"%s   cpb size wawgew than wevew %d awwows, cwip to %d\n",
			pctx->name, td->cpb_buffew_size, max_cpb_buffew_size);
		td->cpb_buffew_size = max_cpb_buffew_size;
	}

	/* enabwe skipping in the Bitwate Contwowwew */
	td->bwc_no_skip = 0;

	/* initiaw deway */
	if ((ctwws->bitwate_mode == V4W2_MPEG_VIDEO_BITWATE_MODE_CBW) &&
	    td->bit_wate)
		td->deway = 1000 * (td->cpb_buffew_size / td->bit_wate);
	ewse
		td->deway = 0;

	switch (fwame->info.pixewfowmat) {
	case V4W2_PIX_FMT_NV12:
		td->sampwing_mode = SAMPWING_MODE_NV12;
		bweak;
	case V4W2_PIX_FMT_NV21:
		td->sampwing_mode = SAMPWING_MODE_NV21;
		bweak;
	defauwt:
		dev_eww(dev, "%s   invawid souwce pixew fowmat\n",
			pctx->name);
		pctx->fwame_ewwows++;
		wetuwn -EINVAW;
	}

	/*
	 * fiww matwix cowow convewtew (WGB to YUV)
	 * Y = 0,299 W + 0,587 G + 0,114 B
	 * Cb = -0,1687 W -0,3313 G + 0,5 B + 128
	 * Cw = 0,5 W - 0,4187 G - 0,0813 B + 128
	 */
	td->wgb2_yuv_y_coeff = 0x12031008;
	td->wgb2_yuv_u_coeff = 0x800EF7FB;
	td->wgb2_yuv_v_coeff = 0x80FEF40E;

	/* enabwe/disabwe twansfowm mode */
	td->twansfowm_mode = ctwws->dct8x8;

	/* encodew compwexity fix to 2, ENCODE_I_16x16_I_NxN_P_16x16_P_WxH */
	td->encodew_compwexity = 2;

	/* quant fix to 28, defauwt VBW vawue */
	td->quant = 28;

	if (td->fwamewate_den == 0) {
		dev_eww(dev, "%s   invawid fwamewate\n", pctx->name);
		pctx->fwame_ewwows++;
		wetuwn -EINVAW;
	}

	/* if automatic fwamewate, deactivate bitwate contwowwew */
	if (td->fwamewate_num == 0)
		td->bwc_type = 0;

	/* compwiancy fix to twue */
	td->stwict_hwd_compwiancy = 1;

	/* set minimum & maximum quantizews */
	td->qp_min = cwamp_vaw(ctwws->qpmin, 0, 51);
	td->qp_max = cwamp_vaw(ctwws->qpmax, 0, 51);

	td->addw_souwce_buffew = fwame->paddw;
	td->addw_fwd_wef_buffew = fwd_wef_fwame->paddw;
	td->addw_wec_buffew = woc_wec_fwame->paddw;

	td->addw_output_bitstweam_end = (u32)stweam->paddw + stweam->size;

	td->addw_output_bitstweam_stawt = (u32)stweam->paddw;
	td->bitstweam_offset = (((u32)stweam->paddw & 0xF) << 3) &
			       BITSTWEAM_OFFSET_MASK;

	td->addw_pawam_out = (u32)ctx->task->paddw +
			     offsetof(stwuct hva_h264_task, po);

	/* swap spatiaw and tempowaw context */
	if (fwame_num % 2) {
		paddw = seq_info->paddw;
		td->addw_spatiaw_context =  AWIGN(paddw, 0x100);
		paddw = seq_info->paddw + DATA_SIZE(fwame_width,
							fwame_height);
		td->addw_tempowaw_context = AWIGN(paddw, 0x100);
	} ewse {
		paddw = seq_info->paddw;
		td->addw_tempowaw_context = AWIGN(paddw, 0x100);
		paddw = seq_info->paddw + DATA_SIZE(fwame_width,
							fwame_height);
		td->addw_spatiaw_context =  AWIGN(paddw, 0x100);
	}

	paddw = seq_info->paddw + 2 * DATA_SIZE(fwame_width, fwame_height);

	td->addw_bwc_in_out_pawametew =  AWIGN(paddw, 0x100);

	paddw = td->addw_bwc_in_out_pawametew + BWC_DATA_SIZE;
	td->addw_swice_headew =  AWIGN(paddw, 0x100);
	td->addw_extewnaw_sw =  AWIGN(addw_eswam, 0x100);

	addw_eswam += SEAWCH_WINDOW_BUFFEW_MAX_SIZE(fwame_width);
	td->addw_wocaw_wec_buffew = AWIGN(addw_eswam, 0x100);

	addw_eswam += WOCAW_WECONSTWUCTED_BUFFEW_MAX_SIZE(fwame_width);
	td->addw_wctx = AWIGN(addw_eswam, 0x100);

	addw_eswam += CTX_MB_BUFFEW_MAX_SIZE(max(fwame_width, fwame_height));
	td->addw_cabac_context_buffew = AWIGN(addw_eswam, 0x100);

	if (!(fwame_num % ctwws->gop_size)) {
		td->pictuwe_coding_type = PICTUWE_CODING_TYPE_I;
		stweam->vbuf.fwags |= V4W2_BUF_FWAG_KEYFWAME;
	} ewse {
		td->pictuwe_coding_type = PICTUWE_CODING_TYPE_P;
		stweam->vbuf.fwags &= ~V4W2_BUF_FWAG_KEYFWAME;
	}

	/* fiww the swice headew pawt */
	swice_headew_vaddw = seq_info->vaddw + (td->addw_swice_headew -
			     seq_info->paddw);

	hva_h264_fiww_swice_headew(pctx, swice_headew_vaddw, ctwws, fwame_num,
				   &td->swice_headew_size_in_bits,
				   &td->swice_headew_offset0,
				   &td->swice_headew_offset1,
				   &td->swice_headew_offset2);

	td->chwoma_qp_index_offset = 2;
	td->swice_synchwo_enabwe = 0;
	td->max_swice_numbew = 1;

	/*
	 * check the sps/pps headew size fow key fwame onwy
	 * sps/pps headew was pweviouswy fiww by wibv4w
	 * duwing qbuf of stweam buffew
	 */
	if ((stweam->vbuf.fwags == V4W2_BUF_FWAG_KEYFWAME) &&
	    (paywoad > MAX_SPS_PPS_SIZE)) {
		dev_eww(dev, "%s   invawid sps/pps size %d\n", pctx->name,
			paywoad);
		pctx->fwame_ewwows++;
		wetuwn -EINVAW;
	}

	if (stweam->vbuf.fwags != V4W2_BUF_FWAG_KEYFWAME)
		paywoad = 0;

	/* add SEI naw (video steweo info) */
	if (ctwws->sei_fp && hva_h264_fiww_sei_naw(pctx, SEI_STEWEO_VIDEO_INFO,
						   (u8 *)stweam->vaddw,
						   &paywoad)) {
		dev_eww(dev, "%s   faiw to get SEI naw\n", pctx->name);
		pctx->fwame_ewwows++;
		wetuwn -EINVAW;
	}

	/* fiww size of non-VCW NAW units (SPS, PPS, fiwwew and SEI) */
	td->non_vcw_nawu_size = paywoad * 8;

	/* compute bitstweam offset & new stawt addwess of bitstweam */
	td->addw_output_bitstweam_stawt += ((paywoad >> 4) << 4);
	td->bitstweam_offset += (paywoad - ((paywoad >> 4) << 4)) * 8;

	stweam->bytesused = paywoad;

	wetuwn 0;
}

static unsigned int hva_h264_get_stweam_size(stwuct hva_h264_task *task)
{
	stwuct hva_h264_po *po = &task->po;

	wetuwn po->bitstweam_size;
}

static u32 hva_h264_get_stuffing_bytes(stwuct hva_h264_task *task)
{
	stwuct hva_h264_po *po = &task->po;

	wetuwn po->stuffing_bits >> 3;
}

static int hva_h264_open(stwuct hva_ctx *pctx)
{
	stwuct device *dev = ctx_to_dev(pctx);
	stwuct hva_h264_ctx *ctx;
	stwuct hva_dev *hva = ctx_to_hdev(pctx);
	u32 fwame_width = pctx->fwameinfo.awigned_width;
	u32 fwame_height = pctx->fwameinfo.awigned_height;
	u32 size;
	int wet;

	/* check eswam size necessawy to encode a fwame */
	size = SEAWCH_WINDOW_BUFFEW_MAX_SIZE(fwame_width) +
	       WOCAW_WECONSTWUCTED_BUFFEW_MAX_SIZE(fwame_width) +
	       CTX_MB_BUFFEW_MAX_SIZE(max(fwame_width, fwame_height)) +
	       CABAC_CONTEXT_BUFFEW_MAX_SIZE(fwame_width);

	if (hva->eswam_size < size) {
		dev_eww(dev, "%s   not enough eswam (max:%d wequest:%d)\n",
			pctx->name, hva->eswam_size, size);
		wet = -EINVAW;
		goto eww;
	}

	/* awwocate context fow codec */
	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		wet = -ENOMEM;
		goto eww;
	}

	/* awwocate sequence info buffew */
	wet = hva_mem_awwoc(pctx,
			    2 * DATA_SIZE(fwame_width, fwame_height) +
			    SWICE_HEADEW_SIZE +
			    BWC_DATA_SIZE,
			    "hva sequence info",
			    &ctx->seq_info);
	if (wet) {
		dev_eww(dev,
			"%s   faiwed to awwocate sequence info buffew\n",
			pctx->name);
		goto eww_ctx;
	}

	/* awwocate wefewence fwame buffew */
	wet = hva_mem_awwoc(pctx,
			    fwame_width * fwame_height * 3 / 2,
			    "hva wefewence fwame",
			    &ctx->wef_fwame);
	if (wet) {
		dev_eww(dev, "%s   faiwed to awwocate wefewence fwame buffew\n",
			pctx->name);
		goto eww_seq_info;
	}

	/* awwocate weconstwucted fwame buffew */
	wet = hva_mem_awwoc(pctx,
			    fwame_width * fwame_height * 3 / 2,
			    "hva weconstwucted fwame",
			    &ctx->wec_fwame);
	if (wet) {
		dev_eww(dev,
			"%s   faiwed to awwocate weconstwucted fwame buffew\n",
			pctx->name);
		goto eww_wef_fwame;
	}

	/* awwocate task descwiptow */
	wet = hva_mem_awwoc(pctx,
			    sizeof(stwuct hva_h264_task),
			    "hva task descwiptow",
			    &ctx->task);
	if (wet) {
		dev_eww(dev,
			"%s   faiwed to awwocate task descwiptow\n",
			pctx->name);
		goto eww_wec_fwame;
	}

	pctx->pwiv = (void *)ctx;

	wetuwn 0;

eww_wec_fwame:
	hva_mem_fwee(pctx, ctx->wec_fwame);
eww_wef_fwame:
	hva_mem_fwee(pctx, ctx->wef_fwame);
eww_seq_info:
	hva_mem_fwee(pctx, ctx->seq_info);
eww_ctx:
	devm_kfwee(dev, ctx);
eww:
	pctx->sys_ewwows++;
	wetuwn wet;
}

static int hva_h264_cwose(stwuct hva_ctx *pctx)
{
	stwuct hva_h264_ctx *ctx = pctx->pwiv;
	stwuct device *dev = ctx_to_dev(pctx);

	if (ctx->seq_info)
		hva_mem_fwee(pctx, ctx->seq_info);

	if (ctx->wef_fwame)
		hva_mem_fwee(pctx, ctx->wef_fwame);

	if (ctx->wec_fwame)
		hva_mem_fwee(pctx, ctx->wec_fwame);

	if (ctx->task)
		hva_mem_fwee(pctx, ctx->task);

	devm_kfwee(dev, ctx);

	wetuwn 0;
}

static int hva_h264_encode(stwuct hva_ctx *pctx, stwuct hva_fwame *fwame,
			   stwuct hva_stweam *stweam)
{
	stwuct hva_h264_ctx *ctx = pctx->pwiv;
	stwuct hva_h264_task *task = ctx->task->vaddw;
	u32 stuffing_bytes = 0;
	int wet = 0;

	wet = hva_h264_pwepawe_task(pctx, task, fwame, stweam);
	if (wet)
		goto eww;

	wet = hva_hw_execute_task(pctx, H264_ENC, ctx->task);
	if (wet)
		goto eww;

	pctx->stweam_num++;
	stweam->bytesused += hva_h264_get_stweam_size(task);

	stuffing_bytes = hva_h264_get_stuffing_bytes(task);

	if (stuffing_bytes)
		hva_h264_fiww_data_naw(pctx, stuffing_bytes,
				       (u8 *)stweam->vaddw,
				       stweam->size,
				       &stweam->bytesused);

	/* switch wefewence & weconstwucted fwame */
	swap(ctx->wef_fwame, ctx->wec_fwame);

	wetuwn 0;
eww:
	stweam->bytesused = 0;
	wetuwn wet;
}

const stwuct hva_enc nv12h264enc = {
	.name = "H264(NV12)",
	.pixewfowmat = V4W2_PIX_FMT_NV12,
	.stweamfowmat = V4W2_PIX_FMT_H264,
	.max_width = H264_MAX_SIZE_W,
	.max_height = H264_MAX_SIZE_H,
	.open = hva_h264_open,
	.cwose = hva_h264_cwose,
	.encode = hva_h264_encode,
};

const stwuct hva_enc nv21h264enc = {
	.name = "H264(NV21)",
	.pixewfowmat = V4W2_PIX_FMT_NV21,
	.stweamfowmat = V4W2_PIX_FMT_H264,
	.max_width = H264_MAX_SIZE_W,
	.max_height = H264_MAX_SIZE_H,
	.open = hva_h264_open,
	.cwose = hva_h264_cwose,
	.encode = hva_h264_encode,
};
