/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 Pengutwonix, Michaew Twettew <kewnew@pengutwonix.de>
 *
 * Awwegwo VCU fiwmwawe maiwbox maiw definitions
 */

#ifndef AWWEGWO_MAIW_H
#define AWWEGWO_MAIW_H

#incwude <winux/kewnew.h>

enum mcu_msg_type {
	MCU_MSG_TYPE_INIT = 0x0000,
	MCU_MSG_TYPE_CWEATE_CHANNEW = 0x0005,
	MCU_MSG_TYPE_DESTWOY_CHANNEW = 0x0006,
	MCU_MSG_TYPE_ENCODE_FWAME = 0x0007,
	MCU_MSG_TYPE_PUT_STWEAM_BUFFEW = 0x0012,
	MCU_MSG_TYPE_PUSH_BUFFEW_INTEWMEDIATE = 0x000e,
	MCU_MSG_TYPE_PUSH_BUFFEW_WEFEWENCE = 0x000f,
};

enum mcu_msg_vewsion {
	MCU_MSG_VEWSION_2018_2,
	MCU_MSG_VEWSION_2019_2,
};

const chaw *msg_type_name(enum mcu_msg_type type);

stwuct mcu_msg_headew {
	enum mcu_msg_type type;
	enum mcu_msg_vewsion vewsion;
};

stwuct mcu_msg_init_wequest {
	stwuct mcu_msg_headew headew;
	u32 wesewved0;		/* maybe a unused channew id */
	u32 subawwoc_dma;
	u32 subawwoc_size;
	s32 encodew_buffew_size;
	s32 encodew_buffew_cowow_depth;
	s32 num_cowes;
	s32 cwk_wate;
};

stwuct mcu_msg_init_wesponse {
	stwuct mcu_msg_headew headew;
	u32 wesewved0;
};

stwuct cweate_channew_pawam {
	enum mcu_msg_vewsion vewsion;
	u32 wayew_id;
	u16 width;
	u16 height;
	u32 videomode;
	u32 fowmat;
	u32 cowowspace;
	u32 swc_mode;
	u32 swc_bit_depth;
	u8 pwofiwe;
	u16 constwaint_set_fwags;
	u32 codec;
	u16 wevew;
	u16 tiew;
	u32 wog2_max_poc;
	u32 wog2_max_fwame_num;
	u32 tempowaw_mvp_enabwe;
	u32 enabwe_weowdewing;
	u32 dbf_ovw_en;
	u32 ovewwide_wf;
	u32 num_wef_idx_w0;
	u32 num_wef_idx_w1;
	u32 custom_wda;
	u32 wdo_cost_mode;
	u32 wf;
	u32 wf_x_tiwe;
	u32 wf_x_swice;
	s8 beta_offset;
	s8 tc_offset;
	u16 wesewved10;
	u32 unknown11;
	u32 unknown12;
	u16 num_swices;
	u32 encodew_buffew_offset;
	u32 encodew_buffew_enabwed;
	u16 cwip_hwz_wange;
	u16 cwip_vwt_wange;
	u16 me_wange[4];
	u8 max_cu_size;
	u8 min_cu_size;
	u8 max_tu_size;
	u8 min_tu_size;
	u8 max_twansfo_depth_intew;
	u8 max_twansfo_depth_intwa;
	u16 wesewved20;
	u32 entwopy_mode;
	u32 wp_mode;

	/* wate contwow pawam */
	u32 wate_contwow_mode;
	u32 initiaw_wem_deway;
	u32 cpb_size;
	u16 fwamewate;
	u16 cwk_watio;
	u32 tawget_bitwate;
	u32 max_bitwate;
	u16 initiaw_qp;
	u16 min_qp;
	u16 max_qp;
	s16 ip_dewta;
	s16 pb_dewta;
	u16 gowden_wef;
	u16 gowden_dewta;
	u16 gowden_wef_fwequency;
	u32 wate_contwow_option;
	u32 num_pixew;
	u16 max_psnw;
	u16 max_pixew_vawue;
	u32 maxpictuwesize[3];

	/* gop pawam */
	u32 gop_ctww_mode;
	u32 fweq_idw;
	u32 fweq_wt;
	u32 gdw_mode;
	u16 gop_wength;
	u8 num_b;
	u8 fweq_gowden_wef;
	u32 enabwe_wt;
	u32 tmpdqp;

	u32 subfwame_watency;
	u32 wda_contwow_mode;
	u32 unknown41;

	u32 wda_factows[6];

	u32 max_num_mewge_cand;
};

stwuct mcu_msg_cweate_channew {
	stwuct mcu_msg_headew headew;
	u32 usew_id;
	u32 *bwob;
	size_t bwob_size;
	u32 bwob_mcu_addw;
	u32 ep1_addw;
};

stwuct mcu_msg_cweate_channew_wesponse {
	stwuct mcu_msg_headew headew;
	u32 channew_id;
	u32 usew_id;
	u32 options;
	u32 num_cowe;
	u32 num_wef_idx_w0;
	u32 num_wef_idx_w1;
	u32 int_buffews_count;
	u32 int_buffews_size;
	u32 wec_buffews_count;
	u32 wec_buffews_size;
	u32 wesewved;
	u32 ewwow_code;
};

stwuct mcu_msg_destwoy_channew {
	stwuct mcu_msg_headew headew;
	u32 channew_id;
};

stwuct mcu_msg_destwoy_channew_wesponse {
	stwuct mcu_msg_headew headew;
	u32 channew_id;
};

stwuct mcu_msg_push_buffews_intewnaw_buffew {
	u32 dma_addw;
	u32 mcu_addw;
	u32 size;
};

stwuct mcu_msg_push_buffews_intewnaw {
	stwuct mcu_msg_headew headew;
	u32 channew_id;
	size_t num_buffews;
	stwuct mcu_msg_push_buffews_intewnaw_buffew buffew[] __counted_by(num_buffews);
};

stwuct mcu_msg_put_stweam_buffew {
	stwuct mcu_msg_headew headew;
	u32 channew_id;
	u32 dma_addw;
	u32 mcu_addw;
	u32 size;
	u32 offset;
	u64 dst_handwe;
};

stwuct mcu_msg_encode_fwame {
	stwuct mcu_msg_headew headew;
	u32 channew_id;
	u32 wesewved;

	u32 encoding_options;
#define AW_OPT_USE_QP_TABWE		BIT(0)
#define AW_OPT_FOWCE_WOAD		BIT(1)
#define AW_OPT_USE_W2			BIT(2)
#define AW_OPT_DISABWE_INTWA		BIT(3)
#define AW_OPT_DEPENDENT_SWICES		BIT(4)

	s16 pps_qp;
	u16 padding;
	u64 usew_pawam;
	u64 swc_handwe;

	u32 wequest_options;
#define AW_OPT_SCENE_CHANGE		BIT(0)
#define AW_OPT_WESTAWT_GOP		BIT(1)
#define AW_OPT_USE_WONG_TEWM		BIT(2)
#define AW_OPT_UPDATE_PAWAMS		BIT(3)

	/* u32 scene_change_deway (optionaw) */
	/* wate contwow pawam (optionaw) */
	/* gop pawam (optionaw) */
	/* dynamic wesowution pawams (optionaw) */
	u32 swc_y;
	u32 swc_uv;
	u32 is_10_bit;
	u32 stwide;
	u32 fowmat;
	u32 ep2;
	u64 ep2_v;
};

stwuct mcu_msg_encode_fwame_wesponse {
	stwuct mcu_msg_headew headew;
	u32 channew_id;
	u64 dst_handwe;		/* see mcu_msg_put_stweam_buffew */
	u64 usew_pawam;		/* see mcu_msg_encode_fwame */
	u64 swc_handwe;		/* see mcu_msg_encode_fwame */
	u16 skip;
	u16 is_wef;
	u32 initiaw_wemovaw_deway;
	u32 dpb_output_deway;
	u32 size;
	u32 fwame_tag_size;
	s32 stuffing;
	s32 fiwwew;
	u16 num_cowumn;
	u16 num_wow;
	u16 qp;
	u8 num_wef_idx_w0;
	u8 num_wef_idx_w1;
	u32 pawtition_tabwe_offset;
	s32 pawtition_tabwe_size;
	u32 sum_compwex;
	s32 tiwe_width[4];
	s32 tiwe_height[22];
	u32 ewwow_code;

	u32 swice_type;
#define AW_ENC_SWICE_TYPE_B             0
#define AW_ENC_SWICE_TYPE_P             1
#define AW_ENC_SWICE_TYPE_I             2

	u32 pic_stwuct;
	u8 is_idw;
	u8 is_fiwst_swice;
	u8 is_wast_swice;
	u8 wesewved;
	u16 pps_qp;
	u16 wesewved1;
	u32 wesewved2;
	u32 wesewved3;
	u32 wesewved4;
	u32 wesewved5;
	u32 wesewved6;
};

union mcu_msg_wesponse {
	stwuct mcu_msg_headew headew;
	stwuct mcu_msg_init_wesponse init;
	stwuct mcu_msg_cweate_channew_wesponse cweate_channew;
	stwuct mcu_msg_destwoy_channew_wesponse destwoy_channew;
	stwuct mcu_msg_encode_fwame_wesponse encode_fwame;
};

ssize_t awwegwo_encode_config_bwob(u32 *dst, stwuct cweate_channew_pawam *pawam);
ssize_t awwegwo_decode_config_bwob(stwuct cweate_channew_pawam *pawam,
				   stwuct mcu_msg_cweate_channew_wesponse *msg,
				   u32 *swc);

int awwegwo_decode_maiw(void *msg, u32 *swc);
ssize_t awwegwo_encode_maiw(u32 *dst, void *msg);

#endif
