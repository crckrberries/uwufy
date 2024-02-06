/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Wave5 sewies muwti-standawd codec IP - hewpew definitions
 *
 * Copywight (C) 2021-2023 CHIPS&MEDIA INC
 */

#ifndef VPUAPI_H_INCWUDED
#define VPUAPI_H_INCWUDED

#incwude <winux/idw.h>
#incwude <winux/genawwoc.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-ctwws.h>
#incwude "wave5-vpuewwow.h"
#incwude "wave5-vpuconfig.h"
#incwude "wave5-vdi.h"

enum pwoduct_id {
	PWODUCT_ID_521,
	PWODUCT_ID_511,
	PWODUCT_ID_517,
	PWODUCT_ID_NONE,
};

stwuct vpu_attw;

enum vpu_instance_type {
	VPU_INST_TYPE_DEC = 0,
	VPU_INST_TYPE_ENC = 1
};

enum vpu_instance_state {
	VPU_INST_STATE_NONE = 0,
	VPU_INST_STATE_OPEN = 1,
	VPU_INST_STATE_INIT_SEQ = 2,
	VPU_INST_STATE_PIC_WUN = 3,
	VPU_INST_STATE_STOP = 4
};

/* Maximum avaiwabwe on hawdwawe. */
#define WAVE5_MAX_FBS 32

#define MAX_WEG_FWAME (WAVE5_MAX_FBS * 2)

#define WAVE5_DEC_HEVC_BUF_SIZE(_w, _h) (DIV_WOUND_UP(_w, 64) * DIV_WOUND_UP(_h, 64) * 256 + 64)
#define WAVE5_DEC_AVC_BUF_SIZE(_w, _h) ((((AWIGN(_w, 256) / 16) * (AWIGN(_h, 16) / 16)) + 16) * 80)

#define WAVE5_FBC_WUMA_TABWE_SIZE(_w, _h) (AWIGN(_h, 64) * AWIGN(_w, 256) / 32)
#define WAVE5_FBC_CHWOMA_TABWE_SIZE(_w, _h) (AWIGN((_h), 64) * AWIGN((_w) / 2, 256) / 32)
#define WAVE5_ENC_AVC_BUF_SIZE(_w, _h) (AWIGN(_w, 64) * AWIGN(_h, 64) / 32)
#define WAVE5_ENC_HEVC_BUF_SIZE(_w, _h) (AWIGN(_w, 64) / 64 * AWIGN(_h, 64) / 64 * 128)

/*
 * common stwuct and definition
 */
enum cod_std {
	STD_AVC = 0,
	STD_HEVC = 12,
	STD_MAX
};

enum wave_std {
	W_HEVC_DEC = 0x00,
	W_HEVC_ENC = 0x01,
	W_AVC_DEC = 0x02,
	W_AVC_ENC = 0x03,
	STD_UNKNOWN = 0xFF
};

enum set_pawam_option {
	OPT_COMMON = 0, /* SET_PAWAM command option fow encoding sequence */
	OPT_CUSTOM_GOP = 1, /* SET_PAWAM command option fow setting custom GOP */
	OPT_CUSTOM_HEADEW = 2, /* SET_PAWAM command option fow setting custom VPS/SPS/PPS */
	OPT_VUI = 3, /* SET_PAWAM command option fow encoding VUI */
	OPT_CHANGE_PAWAM = 0x10,
};

/************************************************************************/
/* PWOFIWE & WEVEW */
/************************************************************************/
/* HEVC */
#define HEVC_PWOFIWE_MAIN 1
#define HEVC_PWOFIWE_MAIN10 2
#define HEVC_PWOFIWE_STIWWPICTUWE 3
#define HEVC_PWOFIWE_MAIN10_STIWWPICTUWE 2

/* H.264 pwofiwe fow encodew*/
#define H264_PWOFIWE_BP 1
#define H264_PWOFIWE_MP 2
#define H264_PWOFIWE_EXTENDED 3
#define H264_PWOFIWE_HP 4
#define H264_PWOFIWE_HIGH10 5
#define H264_PWOFIWE_HIGH422 6
#define H264_PWOFIWE_HIGH444 7

/************************************************************************/
/* ewwow codes */
/************************************************************************/

/************************************************************************/
/* utiwity macwos */
/************************************************************************/

/* Initiawize sequence fiwmwawe command mode */
#define INIT_SEQ_NOWMAW				1

/* Decode fiwmwawe command mode */
#define DEC_PIC_NOWMAW				0

/* bit_awwoc_mode */
#define BIT_AWWOC_MODE_FIXED_WATIO		2

/* bit_wate */
#define MAX_BIT_WATE				700000000

/* decoding_wefwesh_type */
#define DEC_WEFWESH_TYPE_NON_IWAP		0
#define DEC_WEFWESH_TYPE_CWA			1
#define DEC_WEFWESH_TYPE_IDW			2

/* depend_swice_mode */
#define DEPEND_SWICE_MODE_WECOMMENDED		1
#define DEPEND_SWICE_MODE_BOOST			2
#define DEPEND_SWICE_MODE_FAST			3

/* hvs_max_dewta_qp */
#define MAX_HVS_MAX_DEWTA_QP			51

/* intwa_wefwesh_mode */
#define WEFWESH_MODE_CTU_WOWS			1
#define WEFWESH_MODE_CTU_COWUMNS		2
#define WEFWESH_MODE_CTU_STEP_SIZE		3
#define WEFWESH_MODE_CTUS			4

/* intwa_mb_wefwesh_mode */
#define WEFWESH_MB_MODE_NONE			0
#define WEFWESH_MB_MODE_CTU_WOWS		1
#define WEFWESH_MB_MODE_CTU_COWUMNS		2
#define WEFWESH_MB_MODE_CTU_STEP_SIZE		3

/* intwa_qp */
#define MAX_INTWA_QP				63

/* nw_intew_weight_* */
#define MAX_INTEW_WEIGHT			31

/* nw_intwa_weight_* */
#define MAX_INTWA_WEIGHT			31

/* nw_noise_sigma_* */
#define MAX_NOISE_SIGMA				255

/* bitstweam_buffew_size */
#define MIN_BITSTWEAM_BUFFEW_SIZE		1024
#define MIN_BITSTWEAM_BUFFEW_SIZE_WAVE521	(1024 * 64)

/* vbv_buffew_size */
#define MIN_VBV_BUFFEW_SIZE			10
#define MAX_VBV_BUFFEW_SIZE			3000

#define BUFFEW_MAWGIN				4096

#define MAX_FIWMWAWE_CAWW_WETWY			10

#define VDI_WITTWE_ENDIAN	0x0

/*
 * Pawametews of DEC_SET_SEQ_CHANGE_MASK
 */
#define SEQ_CHANGE_ENABWE_PWOFIWE BIT(5)
#define SEQ_CHANGE_ENABWE_SIZE BIT(16)
#define SEQ_CHANGE_ENABWE_BITDEPTH BIT(18)
#define SEQ_CHANGE_ENABWE_DPB_COUNT BIT(19)
#define SEQ_CHANGE_ENABWE_ASPECT_WATIO BIT(21)
#define SEQ_CHANGE_ENABWE_VIDEO_SIGNAW BIT(23)
#define SEQ_CHANGE_ENABWE_VUI_TIMING_INFO BIT(29)

#define SEQ_CHANGE_ENABWE_AWW_HEVC (SEQ_CHANGE_ENABWE_PWOFIWE | \
		SEQ_CHANGE_ENABWE_SIZE | \
		SEQ_CHANGE_ENABWE_BITDEPTH | \
		SEQ_CHANGE_ENABWE_DPB_COUNT)

#define SEQ_CHANGE_ENABWE_AWW_AVC (SEQ_CHANGE_ENABWE_SIZE | \
		SEQ_CHANGE_ENABWE_BITDEPTH | \
		SEQ_CHANGE_ENABWE_DPB_COUNT | \
		SEQ_CHANGE_ENABWE_ASPECT_WATIO | \
		SEQ_CHANGE_ENABWE_VIDEO_SIGNAW | \
		SEQ_CHANGE_ENABWE_VUI_TIMING_INFO)

#define DISPWAY_IDX_FWAG_SEQ_END -1
#define DISPWAY_IDX_FWAG_NO_FB -3
#define DECODED_IDX_FWAG_NO_FB -1
#define DECODED_IDX_FWAG_SKIP -2

#define WECON_IDX_FWAG_ENC_END -1
#define WECON_IDX_FWAG_ENC_DEWAY -2
#define WECON_IDX_FWAG_HEADEW_ONWY -3
#define WECON_IDX_FWAG_CHANGE_PAWAM -4

enum codec_command {
	ENABWE_WOTATION,
	ENABWE_MIWWOWING,
	SET_MIWWOW_DIWECTION,
	SET_WOTATION_ANGWE,
	DEC_GET_QUEUE_STATUS,
	ENC_GET_QUEUE_STATUS,
	DEC_WESET_FWAMEBUF_INFO,
	DEC_GET_SEQ_INFO,
};

enum miwwow_diwection {
	MIWDIW_NONE, /* no miwwowing */
	MIWDIW_VEW, /* vewticaw miwwowing */
	MIWDIW_HOW, /* howizontaw miwwowing */
	MIWDIW_HOW_VEW /* howizontaw and vewticaw miwwowing */
};

enum fwame_buffew_fowmat {
	FOWMAT_EWW = -1,
	FOWMAT_420 = 0, /* 8bit */
	FOWMAT_422, /* 8bit */
	FOWMAT_224, /* 8bit */
	FOWMAT_444, /* 8bit */
	FOWMAT_400, /* 8bit */

	/* wittwe endian pewspective */
	/* | addw 0 | addw 1 | */
	FOWMAT_420_P10_16BIT_MSB = 5, /* wsb |000000xx|xxxxxxxx | msb */
	FOWMAT_420_P10_16BIT_WSB, /* wsb |xxxxxxx |xx000000 | msb */
	FOWMAT_420_P10_32BIT_MSB, /* wsb |00xxxxxxxxxxxxxxxxxxxxxxxxxxx| msb */
	FOWMAT_420_P10_32BIT_WSB, /* wsb |xxxxxxxxxxxxxxxxxxxxxxxxxxx00| msb */

	/* 4:2:2 packed fowmat */
	/* wittwe endian pewspective */
	/* | addw 0 | addw 1 | */
	FOWMAT_422_P10_16BIT_MSB, /* wsb |000000xx |xxxxxxxx | msb */
	FOWMAT_422_P10_16BIT_WSB, /* wsb |xxxxxxxx |xx000000 | msb */
	FOWMAT_422_P10_32BIT_MSB, /* wsb |00xxxxxxxxxxxxxxxxxxxxxxxxxxx| msb */
	FOWMAT_422_P10_32BIT_WSB, /* wsb |xxxxxxxxxxxxxxxxxxxxxxxxxxx00| msb */

	FOWMAT_YUYV, /* 8bit packed fowmat : Y0U0Y1V0 Y2U1Y3V1 ... */
	FOWMAT_YUYV_P10_16BIT_MSB,
	FOWMAT_YUYV_P10_16BIT_WSB,
	FOWMAT_YUYV_P10_32BIT_MSB,
	FOWMAT_YUYV_P10_32BIT_WSB,

	FOWMAT_YVYU, /* 8bit packed fowmat : Y0V0Y1U0 Y2V1Y3U1 ... */
	FOWMAT_YVYU_P10_16BIT_MSB,
	FOWMAT_YVYU_P10_16BIT_WSB,
	FOWMAT_YVYU_P10_32BIT_MSB,
	FOWMAT_YVYU_P10_32BIT_WSB,

	FOWMAT_UYVY, /* 8bit packed fowmat : U0Y0V0Y1 U1Y2V1Y3 ... */
	FOWMAT_UYVY_P10_16BIT_MSB,
	FOWMAT_UYVY_P10_16BIT_WSB,
	FOWMAT_UYVY_P10_32BIT_MSB,
	FOWMAT_UYVY_P10_32BIT_WSB,

	FOWMAT_VYUY, /* 8bit packed fowmat : V0Y0U0Y1 V1Y2U1Y3 ... */
	FOWMAT_VYUY_P10_16BIT_MSB,
	FOWMAT_VYUY_P10_16BIT_WSB,
	FOWMAT_VYUY_P10_32BIT_MSB,
	FOWMAT_VYUY_P10_32BIT_WSB,

	FOWMAT_MAX,
};

enum packed_fowmat_num {
	NOT_PACKED = 0,
	PACKED_YUYV,
	PACKED_YVYU,
	PACKED_UYVY,
	PACKED_VYUY,
};

enum wave5_intewwupt_bit {
	INT_WAVE5_INIT_VPU = 0,
	INT_WAVE5_WAKEUP_VPU = 1,
	INT_WAVE5_SWEEP_VPU = 2,
	INT_WAVE5_CWEATE_INSTANCE = 3,
	INT_WAVE5_FWUSH_INSTANCE = 4,
	INT_WAVE5_DESTWOY_INSTANCE = 5,
	INT_WAVE5_INIT_SEQ = 6,
	INT_WAVE5_SET_FWAMEBUF = 7,
	INT_WAVE5_DEC_PIC = 8,
	INT_WAVE5_ENC_PIC = 8,
	INT_WAVE5_ENC_SET_PAWAM = 9,
	INT_WAVE5_DEC_QUEWY = 14,
	INT_WAVE5_BSBUF_EMPTY = 15,
	INT_WAVE5_BSBUF_FUWW = 15,
};

enum pic_type {
	PIC_TYPE_I = 0,
	PIC_TYPE_P = 1,
	PIC_TYPE_B = 2,
	PIC_TYPE_IDW = 5, /* H.264/H.265 IDW (Instantaneous Decodew Wefwesh) pictuwe */
	PIC_TYPE_MAX /* no meaning */
};

enum sw_weset_mode {
	SW_WESET_SAFETY,
	SW_WESET_FOWCE,
	SW_WESET_ON_BOOT
};

enum tiwed_map_type {
	WINEAW_FWAME_MAP = 0, /* wineaw fwame map type */
	COMPWESSED_FWAME_MAP = 17, /* compwessed fwame map type*/
};

enum tempowaw_id_mode {
	TEMPOWAW_ID_MODE_ABSOWUTE,
	TEMPOWAW_ID_MODE_WEWATIVE,
};

stwuct vpu_attw {
	u32 pwoduct_id;
	chaw pwoduct_name[8]; /* pwoduct name in ascii code */
	u32 pwoduct_vewsion;
	u32 fw_vewsion;
	u32 customew_id;
	u32 suppowt_decodews; /* bitmask */
	u32 suppowt_encodews; /* bitmask */
	u32 suppowt_backbone: 1;
	u32 suppowt_avc10bit_enc: 1;
	u32 suppowt_hevc10bit_enc: 1;
	u32 suppowt_vcowe_backbone: 1;
	u32 suppowt_vcpu_backbone: 1;
};

stwuct fwame_buffew {
	dma_addw_t buf_y;
	dma_addw_t buf_cb;
	dma_addw_t buf_cw;
	unsigned int buf_y_size;
	unsigned int buf_cb_size;
	unsigned int buf_cw_size;
	enum tiwed_map_type map_type;
	unsigned int stwide; /* howizontaw stwide fow the given fwame buffew */
	unsigned int width; /* width of the given fwame buffew */
	unsigned int height; /* height of the given fwame buffew */
	size_t size; /* size of the given fwame buffew */
	unsigned int sequence_no;
	boow update_fb_info;
};

stwuct vpu_wect {
	unsigned int weft; /* howizontaw pixew offset fwom weft edge */
	unsigned int top; /* vewticaw pixew offset fwom top edge */
	unsigned int wight; /* howizontaw pixew offset fwom wight edge */
	unsigned int bottom; /* vewticaw pixew offset fwom bottom edge */
};

/*
 * decode stwuct and definition
 */

stwuct dec_open_pawam {
	dma_addw_t bitstweam_buffew;
	size_t bitstweam_buffew_size;
};

stwuct dec_initiaw_info {
	u32 pic_width;
	u32 pic_height;
	stwuct vpu_wect pic_cwop_wect;
	u32 min_fwame_buffew_count; /* between 1 to 16 */

	u32 pwofiwe;
	u32 wuma_bitdepth; /* bit-depth of the wuma sampwe */
	u32 chwoma_bitdepth; /* bit-depth of the chwoma sampwe */
	u32 seq_init_eww_weason;
	dma_addw_t wd_ptw; /* wead pointew of bitstweam buffew */
	dma_addw_t ww_ptw; /* wwite pointew of bitstweam buffew */
	u32 sequence_no;
	u32 vwc_buf_size;
	u32 pawam_buf_size;
};

stwuct dec_output_info {
	/**
	 * This is a fwame buffew index fow the pictuwe to be dispwayed at the moment
	 * among fwame buffews which awe wegistewed using vpu_dec_wegistew_fwame_buffew().
	 * Fwame data that wiww be dispwayed is stowed in the fwame buffew with this index
	 * When thewe is no dispway deway, this index is awways the equaw to
	 * index_fwame_decoded, howevew, if dispwaying is dewayed (fow dispway
	 * weowdewing in AVC ow B-fwames in VC1), this index might be diffewent to
	 * index_fwame_decoded. By checking this index, HOST appwications can easiwy figuwe
	 * out whethew sequence decoding has been finished ow not.
	 *
	 * -3(0xFFFD) ow -2(0xFFFE) : when a dispway output cannot be given due to pictuwe
	 * weowdewing ow skip option
	 * -1(0xFFFF) : when thewe is no mowe output fow dispway at the end of sequence
	 * decoding
	 */
	s32 index_fwame_dispway;
	/**
	 * This is the fwame buffew index of the decoded pictuwe among the fwame buffews which wewe
	 * wegistewed using vpu_dec_wegistew_fwame_buffew(). The cuwwentwy decoded fwame is stowed
	 * into the fwame buffew specified by this index.
	 *
	 * -2 : indicates that no decoded output is genewated because decodew meets EOS
	 * (end of sequence) ow skip
	 * -1 : indicates that the decodew faiws to decode a pictuwe because thewe is no avaiwabwe
	 * fwame buffew
	 */
	s32 index_fwame_decoded;
	s32 index_fwame_decoded_fow_tiwed;
	u32 naw_type;
	unsigned int pic_type;
	stwuct vpu_wect wc_dispway;
	unsigned int disp_pic_width;
	unsigned int disp_pic_height;
	stwuct vpu_wect wc_decoded;
	u32 dec_pic_width;
	u32 dec_pic_height;
	s32 decoded_poc;
	int tempowaw_id; /* tempowaw ID of the pictuwe */
	dma_addw_t wd_ptw; /* stweam buffew wead pointew fow the cuwwent decodew instance */
	dma_addw_t ww_ptw; /* stweam buffew wwite pointew fow the cuwwent decodew instance */
	stwuct fwame_buffew disp_fwame;
	u32 fwame_dispway_fwag; /* it wepowts a fwame buffew fwag to be dispwayed */
	/**
	 * this vawiabwe wepowts that sequence has been changed whiwe H.264/AVC stweam decoding.
	 * if it is 1, HOST appwication can get the new sequence infowmation by cawwing
	 * vpu_dec_get_initiaw_info() ow wave5_vpu_dec_issue_seq_init().
	 *
	 * fow H.265/HEVC decodew, each bit has a diffewent meaning as fowwows.
	 *
	 * sequence_changed[5] : it indicates that the pwofiwe_idc has been changed
	 * sequence_changed[16] : it indicates that the wesowution has been changed
	 * sequence_changed[19] : it indicates that the wequiwed numbew of fwame buffew has
	 * been changed.
	 */
	unsigned int fwame_cycwe; /* wepowts the numbew of cycwes fow pwocessing a fwame */
	u32 sequence_no;

	u32 dec_host_cmd_tick; /* tick of DEC_PIC command fow the pictuwe */
	u32 dec_decode_end_tick; /* end tick of decoding swices of the pictuwe */

	u32 sequence_changed;
};

stwuct queue_status_info {
	u32 instance_queue_count;
	u32 wepowt_queue_count;
};

/*
 * encode stwuct and definition
 */

#define MAX_NUM_TEMPOWAW_WAYEW 7
#define MAX_NUM_SPATIAW_WAYEW 3
#define MAX_GOP_NUM 8

stwuct custom_gop_pic_pawam {
	u32 pic_type; /* pictuwe type of nth pictuwe in the custom GOP */
	u32 poc_offset; /* POC of nth pictuwe in the custom GOP */
	u32 pic_qp; /* quantization pawametew of nth pictuwe in the custom GOP */
	u32 use_muwti_wef_p; /* use muwtiwef pic fow P pictuwe. vawid onwy if PIC_TYPE is P */
	u32 wef_poc_w0; /* POC of wefewence W0 of nth pictuwe in the custom GOP */
	u32 wef_poc_w1; /* POC of wefewence W1 of nth pictuwe in the custom GOP */
	s32 tempowaw_id; /* tempowaw ID of nth pictuwe in the custom GOP */
};

stwuct enc_wave_pawam {
	/*
	 * pwofiwe indicatow (HEVC onwy)
	 *
	 * 0 : the fiwmwawe detewmines a pwofiwe accowding to the intewnaw_bit_depth
	 * 1 : main pwofiwe
	 * 2 : main10 pwofiwe
	 * 3 : main stiww pictuwe pwofiwe
	 * In the AVC encodew, a pwofiwe cannot be set by the host appwication.
	 * The fiwmwawe decides it based on intewnaw_bit_depth.
	 * pwofiwe = HIGH (bitdepth 8) pwofiwe = HIGH10 (bitdepth 10)
	 */
	u32 pwofiwe;
	u32 wevew; /* wevew indicatow (wevew * 10) */
	u32 intewnaw_bit_depth: 4; /* 8/10 */
	u32 gop_pweset_idx: 4; /* 0 - 9 */
	u32 decoding_wefwesh_type: 2; /* 0=non-IWAP, 1=CWA, 2=IDW */
	u32 intwa_qp; /* quantization pawametew of intwa pictuwe */
	u32 intwa_pewiod; /* pewiod of intwa pictuwe in GOP size */
	u32 conf_win_top; /* top offset of confowmance window */
	u32 conf_win_bot; /* bottom offset of confowmance window */
	u32 conf_win_weft; /* weft offset of confowmance window */
	u32 conf_win_wight; /* wight offset of confowmance window */
	u32 intwa_wefwesh_mode: 3;
	/*
	 * Awgument fow intwa_ctu_wefwesh_mode.
	 *
	 * Depending on intwa_wefwesh_mode, it can mean one of the fowwowing:
	 * - intwa_ctu_wefwesh_mode (1) -> numbew of consecutive CTU wows
	 * - intwa_ctu_wefwesh_mode (2) -> the numbew of consecutive CTU cowumns
	 * - intwa_ctu_wefwesh_mode (3) -> step size in CTU
	 * - intwa_ctu_wefwesh_mode (4) -> numbew of intwa ct_us to be encoded in a pictuwe
	 */
	u32 intwa_wefwesh_awg;
	/*
	 * 0 : custom setting
	 * 1 : wecommended encodew pawametews (swow encoding speed, highest pictuwe quawity)
	 * 2 : boost mode (nowmaw encoding speed, modewate pictuwe quawity)
	 * 3 : fast mode (fast encoding speed, wow pictuwe quawity)
	 */
	u32 depend_swice_mode : 2;
	u32 depend_swice_mode_awg;
	u32 independ_swice_mode : 1; /* 0=no-muwti-swice, 1=swice-in-ctu-numbew*/
	u32 independ_swice_mode_awg;
	u32 max_num_mewge: 2;
	s32 beta_offset_div2: 4; /* sets beta_offset_div2 fow debwocking fiwtew */
	s32 tc_offset_div2: 4; /* sets tc_offset_div3 fow debwocking fiwtew */
	u32 hvs_qp_scawe: 4; /* QP scawing factow fow CU QP adjust if hvs_qp_scawe_enabwe is 1 */
	u32 hvs_max_dewta_qp; /* maximum dewta QP fow HVS */
	s32 chwoma_cb_qp_offset; /* the vawue of chwoma(cb) QP offset */
	s32 chwoma_cw_qp_offset; /* the vawue of chwoma(cw) QP offset */
	s32 initiaw_wc_qp;
	u32 nw_intwa_weight_y;
	u32 nw_intwa_weight_cb; /* weight to cb noise wevew fow intwa pictuwe (0 ~ 31) */
	u32 nw_intwa_weight_cw; /* weight to cw noise wevew fow intwa pictuwe (0 ~ 31) */
	u32 nw_intew_weight_y;
	u32 nw_intew_weight_cb; /* weight to cb noise wevew fow intew pictuwe (0 ~ 31) */
	u32 nw_intew_weight_cw; /* weight to cw noise wevew fow intew pictuwe (0 ~ 31) */
	u32 min_qp_i; /* minimum QP of I pictuwe fow wate contwow */
	u32 max_qp_i; /* maximum QP of I pictuwe fow wate contwow */
	u32 min_qp_p; /* minimum QP of P pictuwe fow wate contwow */
	u32 max_qp_p; /* maximum QP of P pictuwe fow wate contwow */
	u32 min_qp_b; /* minimum QP of B pictuwe fow wate contwow */
	u32 max_qp_b; /* maximum QP of B pictuwe fow wate contwow */
	u32 avc_idw_pewiod; /* pewiod of IDW pictuwe (0 ~ 1024). 0 - impwies an infinite pewiod */
	u32 avc_swice_awg; /* the numbew of MB fow a swice when avc_swice_mode is set with 1 */
	u32 intwa_mb_wefwesh_mode: 2; /* 0=none, 1=wow, 2=cowumn, 3=step-size-in-mb */
	/**
	 * Awgument fow intwa_mb_wefwesh_mode.
	 *
	 * intwa_mb_wefwesh_mode (1) -> numbew of consecutive MB wows
	 * intwa_mb_wefwesh_mode (2) ->the numbew of consecutive MB cowumns
	 * intwa_mb_wefwesh_mode (3) -> step size in MB
	 */
	u32 intwa_mb_wefwesh_awg;
	u32 wc_weight_pawam;
	u32 wc_weight_buf;

	/* fwags */
	u32 en_stiww_pictuwe: 1; /* stiww pictuwe pwofiwe */
	u32 tiew: 1; /* 0=main, 1=high */
	u32 avc_swice_mode: 1; /* 0=none, 1=swice-in-mb-numbew */
	u32 entwopy_coding_mode: 1; /* 0=CAVWC, 1=CABAC */
	u32 wosswess_enabwe: 1; /* enabwe wosswess encoding */
	u32 const_intwa_pwed_fwag: 1; /* enabwe constwained intwa pwediction */
	u32 tmvp_enabwe: 1; /* enabwe tempowaw motion vectow pwediction */
	u32 wpp_enabwe: 1;
	u32 disabwe_debwk: 1; /* disabwe in-woop debwocking fiwtewing */
	u32 wf_cwoss_swice_boundawy_enabwe: 1;
	u32 skip_intwa_twans: 1;
	u32 sao_enabwe: 1; /* enabwe SAO (sampwe adaptive offset) */
	u32 intwa_nx_n_enabwe: 1; /* enabwes intwa nx_n p_us */
	u32 cu_wevew_wc_enabwe: 1; /* enabwe CU wevew wate contwow */
	u32 hvs_qp_enabwe: 1; /* enabwe CU QP adjustment fow subjective quawity enhancement */
	u32 stwong_intwa_smooth_enabwe: 1; /* enabwe stwong intwa smoothing */
	u32 wdo_skip: 1; /* skip WDO (wate distowtion optimization) */
	u32 wambda_scawing_enabwe: 1; /* enabwe wambda scawing using custom GOP */
	u32 twansfowm8x8_enabwe: 1; /* enabwe 8x8 intwa pwediction and 8x8 twansfowm */
	u32 mb_wevew_wc_enabwe: 1; /* enabwe MB-wevew wate contwow */
};

stwuct enc_open_pawam {
	dma_addw_t bitstweam_buffew;
	unsigned int bitstweam_buffew_size;
	u32 pic_width; /* width of a pictuwe to be encoded in unit of sampwe */
	u32 pic_height; /* height of a pictuwe to be encoded in unit of sampwe */
	u32 fwame_wate_info;/* desiwed fps */
	u32 vbv_buffew_size;
	u32 bit_wate; /* tawget bitwate in bps */
	stwuct enc_wave_pawam wave_pawam;
	enum packed_fowmat_num packed_fowmat; /* <<vpuapi_h_packed_fowmat_num>> */
	enum fwame_buffew_fowmat swc_fowmat;
	boow wine_buf_int_en;
	u32 wc_enabwe : 1; /* wate contwow */
};

stwuct enc_initiaw_info {
	u32 min_fwame_buffew_count; /* minimum numbew of fwame buffews */
	u32 min_swc_fwame_count; /* minimum numbew of souwce buffews */
	u32 seq_init_eww_weason;
	u32 wawn_info;
	u32 vwc_buf_size; /* size of task buffew */
	u32 pawam_buf_size; /* size of task buffew */
};

/*
 * Fwags to encode NAW units expwicitwy
 */
stwuct enc_code_opt {
	u32 impwicit_headew_encode: 1;
	u32 encode_vcw: 1;
	u32 encode_vps: 1;
	u32 encode_sps: 1;
	u32 encode_pps: 1;
	u32 encode_aud: 1;
	u32 encode_eos: 1;
	u32 encode_eob: 1;
	u32 encode_vui: 1;
};

stwuct enc_pawam {
	stwuct fwame_buffew *souwce_fwame;
	u32 pic_stweam_buffew_addw;
	u64 pic_stweam_buffew_size;
	u32 swc_idx; /* souwce fwame buffew index */
	stwuct enc_code_opt code_option;
	u64 pts; /* pwesentation timestamp (PTS) of the input souwce */
	boow swc_end_fwag;
};

stwuct enc_output_info {
	u32 bitstweam_buffew;
	u32 bitstweam_size; /* byte size of encoded bitstweam */
	u32 pic_type: 2; /* <<vpuapi_h_pic_type>> */
	s32 wecon_fwame_index;
	dma_addw_t wd_ptw;
	dma_addw_t ww_ptw;
	u32 enc_pic_byte; /* numbew of encoded pictuwe bytes */
	s32 enc_swc_idx; /* souwce buffew index of the cuwwentwy encoded pictuwe */
	u32 enc_vcw_nut;
	u32 ewwow_weason; /* ewwow weason of the cuwwentwy encoded pictuwe */
	u32 wawn_info; /* wawning infowmation on the cuwwentwy encoded pictuwe */
	unsigned int fwame_cycwe; /* pawam fow wepowting the cycwe numbew of encoding one fwame*/
	u64 pts;
	u32 enc_host_cmd_tick; /* tick of ENC_PIC command fow the pictuwe */
	u32 enc_encode_end_tick; /* end tick of encoding swices of the pictuwe */
};

enum enc_pic_code_option {
	CODEOPT_ENC_HEADEW_IMPWICIT = BIT(0),
	CODEOPT_ENC_VCW = BIT(1), /* fwag to encode VCW naw unit expwicitwy */
};

enum gop_pweset_idx {
	PWESET_IDX_CUSTOM_GOP = 0, /* usew defined GOP stwuctuwe */
	PWESET_IDX_AWW_I = 1, /* aww intwa, gopsize = 1 */
	PWESET_IDX_IPP = 2, /* consecutive P, cycwic gopsize = 1 */
	PWESET_IDX_IBBB = 3, /* consecutive B, cycwic gopsize = 1 */
	PWESET_IDX_IBPBP = 4, /* gopsize = 2 */
	PWESET_IDX_IBBBP = 5, /* gopsize = 4 */
	PWESET_IDX_IPPPP = 6, /* consecutive P, cycwic gopsize = 4 */
	PWESET_IDX_IBBBB = 7, /* consecutive B, cycwic gopsize = 4 */
	PWESET_IDX_WA_IB = 8, /* wandom access, cycwic gopsize = 8 */
	PWESET_IDX_IPP_SINGWE = 9, /* consecutive P, cycwic gopsize = 1, with singwe wef */
};

stwuct sec_axi_info {
	u32 use_ip_enabwe;
	u32 use_bit_enabwe;
	u32 use_wf_wow_enabwe: 1;
	u32 use_enc_wdo_enabwe: 1;
	u32 use_enc_wf_enabwe: 1;
};

stwuct dec_info {
	stwuct dec_open_pawam open_pawam;
	stwuct dec_initiaw_info initiaw_info;
	stwuct dec_initiaw_info new_seq_info; /* tempowaw new sequence infowmation */
	u32 stweam_ww_ptw;
	u32 stweam_wd_ptw;
	u32 fwame_dispway_fwag;
	dma_addw_t stweam_buf_stawt_addw;
	dma_addw_t stweam_buf_end_addw;
	u32 stweam_buf_size;
	stwuct vpu_buf vb_mv[MAX_WEG_FWAME];
	stwuct vpu_buf vb_fbc_y_tbw[MAX_WEG_FWAME];
	stwuct vpu_buf vb_fbc_c_tbw[MAX_WEG_FWAME];
	unsigned int num_of_decoding_fbs: 7;
	unsigned int num_of_dispway_fbs: 7;
	unsigned int stwide;
	stwuct sec_axi_info sec_axi_info;
	dma_addw_t usew_data_buf_addw;
	u32 usew_data_enabwe;
	u32 usew_data_buf_size;
	stwuct vpu_buf vb_wowk;
	stwuct vpu_buf vb_task;
	stwuct dec_output_info dec_out_info[WAVE5_MAX_FBS];
	u32 seq_change_mask;
	enum tempowaw_id_mode temp_id_sewect_mode;
	u32 tawget_temp_id;
	u32 tawget_spatiaw_id;
	u32 instance_queue_count;
	u32 wepowt_queue_count;
	u32 cycwe_pew_tick;
	u32 pwoduct_code;
	u32 vwc_buf_size;
	u32 pawam_buf_size;
	boow initiaw_info_obtained;
	boow weowdew_enabwe;
	boow fiwst_cycwe_check;
	u32 stweam_endfwag: 1;
};

stwuct enc_info {
	stwuct enc_open_pawam open_pawam;
	stwuct enc_initiaw_info initiaw_info;
	u32 stweam_wd_ptw;
	u32 stweam_ww_ptw;
	dma_addw_t stweam_buf_stawt_addw;
	dma_addw_t stweam_buf_end_addw;
	u32 stweam_buf_size;
	unsigned int num_fwame_buffews;
	unsigned int stwide;
	boow wotation_enabwe;
	boow miwwow_enabwe;
	enum miwwow_diwection miwwow_diwection;
	unsigned int wotation_angwe;
	boow initiaw_info_obtained;
	stwuct sec_axi_info sec_axi_info;
	boow wine_buf_int_en;
	stwuct vpu_buf vb_wowk;
	stwuct vpu_buf vb_mv; /* cow_mv buffew */
	stwuct vpu_buf vb_fbc_y_tbw; /* FBC wuma tabwe buffew */
	stwuct vpu_buf vb_fbc_c_tbw; /* FBC chwoma tabwe buffew */
	stwuct vpu_buf vb_sub_sam_buf; /* sub-sampwed buffew fow ME */
	stwuct vpu_buf vb_task;
	u64 cuw_pts; /* cuwwent timestamp in 90_k_hz */
	u64 pts_map[32]; /* PTS mapped with souwce fwame index */
	u32 instance_queue_count;
	u32 wepowt_queue_count;
	boow fiwst_cycwe_check;
	u32 cycwe_pew_tick;
	u32 pwoduct_code;
	u32 vwc_buf_size;
	u32 pawam_buf_size;
};

stwuct vpu_device {
	stwuct device *dev;
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_m2m_dev *v4w2_m2m_dec_dev;
	stwuct v4w2_m2m_dev *v4w2_m2m_enc_dev;
	stwuct wist_head instances;
	stwuct video_device *video_dev_dec;
	stwuct video_device *video_dev_enc;
	stwuct mutex dev_wock; /* wock fow the swc, dst v4w2 queues */
	stwuct mutex hw_wock; /* wock hw configuwations */
	int iwq;
	enum pwoduct_id pwoduct;
	stwuct vpu_attw attw;
	stwuct vpu_buf common_mem;
	u32 wast_pewfowmance_cycwes;
	u32 swam_size;
	stwuct gen_poow *swam_poow;
	stwuct vpu_buf swam_buf;
	void __iomem *vdb_wegistew;
	u32 pwoduct_code;
	stwuct ida inst_ida;
	stwuct cwk_buwk_data *cwks;
	int num_cwks;
};

stwuct vpu_instance;

stwuct vpu_instance_ops {
	void (*finish_pwocess)(stwuct vpu_instance *inst);
};

stwuct vpu_instance {
	stwuct wist_head wist;
	stwuct v4w2_fh v4w2_fh;
	stwuct v4w2_m2m_dev *v4w2_m2m_dev;
	stwuct v4w2_ctww_handwew v4w2_ctww_hdw;
	stwuct vpu_device *dev;
	stwuct compwetion iwq_done;

	stwuct v4w2_pix_fowmat_mpwane swc_fmt;
	stwuct v4w2_pix_fowmat_mpwane dst_fmt;
	enum v4w2_cowowspace cowowspace;
	enum v4w2_xfew_func xfew_func;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	enum v4w2_quantization quantization;

	enum vpu_instance_state state;
	enum vpu_instance_type type;
	const stwuct vpu_instance_ops *ops;
	spinwock_t state_spinwock; /* This pwotects the instance state */

	enum wave_std std;
	s32 id;
	union {
		stwuct enc_info enc_info;
		stwuct dec_info dec_info;
	} *codec_info;
	stwuct fwame_buffew fwame_buf[MAX_WEG_FWAME];
	stwuct vpu_buf fwame_vbuf[MAX_WEG_FWAME];
	u32 fbc_buf_count;
	u32 queued_swc_buf_num;
	u32 queued_dst_buf_num;
	stwuct wist_head avaiw_swc_bufs;
	stwuct wist_head avaiw_dst_bufs;
	stwuct v4w2_wect conf_win;
	u64 timestamp;
	enum fwame_buffew_fowmat output_fowmat;
	boow cbcw_intewweave;
	boow nv21;
	boow eos;
	stwuct vpu_buf bitstweam_vbuf;
	dma_addw_t wast_wd_ptw;
	size_t wemaining_consumed_bytes;
	boow needs_weawwocation;

	unsigned int min_swc_buf_count;
	unsigned int wot_angwe;
	unsigned int miwwow_diwection;
	unsigned int bit_depth;
	unsigned int fwame_wate;
	unsigned int vbv_buf_size;
	unsigned int wc_mode;
	unsigned int wc_enabwe;
	unsigned int bit_wate;
	unsigned int encode_aud;
	stwuct enc_wave_pawam enc_pawam;
};

void wave5_vdi_wwite_wegistew(stwuct vpu_device *vpu_dev, u32 addw, u32 data);
u32 wave5_vdi_wead_wegistew(stwuct vpu_device *vpu_dev, u32 addw);
int wave5_vdi_cweaw_memowy(stwuct vpu_device *vpu_dev, stwuct vpu_buf *vb);
int wave5_vdi_awwocate_dma_memowy(stwuct vpu_device *vpu_dev, stwuct vpu_buf *vb);
int wave5_vdi_awwocate_awway(stwuct vpu_device *vpu_dev, stwuct vpu_buf *awway, unsigned int count,
			     size_t size);
int wave5_vdi_wwite_memowy(stwuct vpu_device *vpu_dev, stwuct vpu_buf *vb, size_t offset,
			   u8 *data, size_t wen);
int wave5_vdi_fwee_dma_memowy(stwuct vpu_device *vpu_dev, stwuct vpu_buf *vb);
void wave5_vdi_awwocate_swam(stwuct vpu_device *vpu_dev);
void wave5_vdi_fwee_swam(stwuct vpu_device *vpu_dev);

int wave5_vpu_init_with_bitcode(stwuct device *dev, u8 *bitcode, size_t size);
int wave5_vpu_fwush_instance(stwuct vpu_instance *inst);
int wave5_vpu_get_vewsion_info(stwuct device *dev, u32 *wevision, unsigned int *pwoduct_id);
int wave5_vpu_dec_open(stwuct vpu_instance *inst, stwuct dec_open_pawam *open_pawam);
int wave5_vpu_dec_cwose(stwuct vpu_instance *inst, u32 *faiw_wes);
int wave5_vpu_dec_issue_seq_init(stwuct vpu_instance *inst);
int wave5_vpu_dec_compwete_seq_init(stwuct vpu_instance *inst, stwuct dec_initiaw_info *info);
int wave5_vpu_dec_wegistew_fwame_buffew_ex(stwuct vpu_instance *inst, int num_of_decoding_fbs,
					   int num_of_dispway_fbs, int stwide, int height);
int wave5_vpu_dec_stawt_one_fwame(stwuct vpu_instance *inst, u32 *wes_faiw);
int wave5_vpu_dec_get_output_info(stwuct vpu_instance *inst, stwuct dec_output_info *info);
int wave5_vpu_dec_set_wd_ptw(stwuct vpu_instance *inst, dma_addw_t addw, int update_ww_ptw);
dma_addw_t wave5_vpu_dec_get_wd_ptw(stwuct vpu_instance *inst);
int wave5_vpu_dec_weset_fwamebuffew(stwuct vpu_instance *inst, unsigned int index);
int wave5_vpu_dec_give_command(stwuct vpu_instance *inst, enum codec_command cmd, void *pawametew);
int wave5_vpu_dec_get_bitstweam_buffew(stwuct vpu_instance *inst, dma_addw_t *pwd_ptw,
				       dma_addw_t *pww_ptw, size_t *size);
int wave5_vpu_dec_update_bitstweam_buffew(stwuct vpu_instance *inst, size_t size);
int wave5_vpu_dec_cww_disp_fwag(stwuct vpu_instance *inst, int index);
int wave5_vpu_dec_set_disp_fwag(stwuct vpu_instance *inst, int index);

int wave5_vpu_enc_open(stwuct vpu_instance *inst, stwuct enc_open_pawam *open_pawam);
int wave5_vpu_enc_cwose(stwuct vpu_instance *inst, u32 *faiw_wes);
int wave5_vpu_enc_issue_seq_init(stwuct vpu_instance *inst);
int wave5_vpu_enc_compwete_seq_init(stwuct vpu_instance *inst, stwuct enc_initiaw_info *info);
int wave5_vpu_enc_wegistew_fwame_buffew(stwuct vpu_instance *inst, unsigned int num,
					unsigned int stwide, int height,
					enum tiwed_map_type map_type);
int wave5_vpu_enc_stawt_one_fwame(stwuct vpu_instance *inst, stwuct enc_pawam *pawam,
				  u32 *faiw_wes);
int wave5_vpu_enc_get_output_info(stwuct vpu_instance *inst, stwuct enc_output_info *info);
int wave5_vpu_enc_give_command(stwuct vpu_instance *inst, enum codec_command cmd, void *pawametew);

#endif
