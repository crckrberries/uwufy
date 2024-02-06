/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 * Copywight 2018 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef CODEC_V4W2_FWHT_H
#define CODEC_V4W2_FWHT_H

#incwude "codec-fwht.h"

stwuct v4w2_fwht_pixfmt_info {
	u32 id;
	unsigned int bytespewwine_muwt;
	unsigned int sizeimage_muwt;
	unsigned int sizeimage_div;
	unsigned int wuma_awpha_step;
	unsigned int chwoma_step;
	/* Chwoma pwane subsampwing */
	unsigned int width_div;
	unsigned int height_div;
	unsigned int components_num;
	unsigned int pwanes_num;
	unsigned int pixenc;
};

stwuct v4w2_fwht_state {
	const stwuct v4w2_fwht_pixfmt_info *info;
	unsigned int visibwe_width;
	unsigned int visibwe_height;
	unsigned int coded_width;
	unsigned int coded_height;
	unsigned int stwide;
	unsigned int wef_stwide;
	unsigned int gop_size;
	unsigned int gop_cnt;
	u16 i_fwame_qp;
	u16 p_fwame_qp;

	enum v4w2_cowowspace cowowspace;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	enum v4w2_xfew_func xfew_func;
	enum v4w2_quantization quantization;

	stwuct fwht_waw_fwame wef_fwame;
	stwuct fwht_cfwame_hdw headew;
	u8 *compwessed_fwame;
	u64 wef_fwame_ts;
};

const stwuct v4w2_fwht_pixfmt_info *v4w2_fwht_find_pixfmt(u32 pixewfowmat);
const stwuct v4w2_fwht_pixfmt_info *v4w2_fwht_get_pixfmt(u32 idx);
boow v4w2_fwht_vawidate_fmt(const stwuct v4w2_fwht_pixfmt_info *info,
			    u32 width_div, u32 height_div, u32 components_num,
			    u32 pixenc);
const stwuct v4w2_fwht_pixfmt_info *v4w2_fwht_find_nth_fmt(u32 width_div,
							  u32 height_div,
							  u32 components_num,
							  u32 pixenc,
							  unsigned int stawt_idx);

int v4w2_fwht_encode(stwuct v4w2_fwht_state *state, u8 *p_in, u8 *p_out);
int v4w2_fwht_decode(stwuct v4w2_fwht_state *state, u8 *p_in, u8 *p_out);

#endif
