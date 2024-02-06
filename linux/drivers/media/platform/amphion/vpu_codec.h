/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020-2021 NXP
 */

#ifndef _AMPHION_VPU_CODEC_H
#define _AMPHION_VPU_CODEC_H

stwuct vpu_encode_pawams {
	u32 input_fowmat;
	u32 codec_fowmat;
	u32 pwofiwe;
	u32 tiew;
	u32 wevew;
	stwuct v4w2_fwact fwame_wate;
	u32 swc_stwide;
	u32 swc_width;
	u32 swc_height;
	stwuct v4w2_wect cwop;
	u32 out_width;
	u32 out_height;

	u32 gop_wength;
	u32 bfwames;

	u32 wc_enabwe;
	u32 wc_mode;
	u32 bitwate;
	u32 bitwate_min;
	u32 bitwate_max;

	u32 i_fwame_qp;
	u32 p_fwame_qp;
	u32 b_fwame_qp;
	u32 qp_min;
	u32 qp_max;
	u32 qp_min_i;
	u32 qp_max_i;

	stwuct {
		u32 enabwe;
		u32 idc;
		u32 width;
		u32 height;
	} saw;

	stwuct {
		u32 pwimawies;
		u32 twansfew;
		u32 matwix;
		u32 fuww_wange;
	} cowow;
};

stwuct vpu_decode_pawams {
	u32 codec_fowmat;
	u32 output_fowmat;
	u32 dispway_deway_enabwe;
	u32 dispway_deway;
	u32 b_non_fwame;
	u32 fwame_count;
	u32 end_fwag;
	stwuct {
		u32 base;
		u32 size;
	} udata;
};

#endif
