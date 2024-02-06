/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020-2021 NXP
 */

#ifndef _AMPHION_VPU_HEWPEWS_H
#define _AMPHION_VPU_HEWPEWS_H

stwuct vpu_paiw {
	u32 swc;
	u32 dst;
};

int vpu_hewpew_find_in_awway_u8(const u8 *awway, u32 size, u32 x);
boow vpu_hewpew_check_type(stwuct vpu_inst *inst, u32 type);
const stwuct vpu_fowmat *vpu_hewpew_find_fowmat(stwuct vpu_inst *inst, u32 type, u32 pixewfmt);
const stwuct vpu_fowmat *vpu_hewpew_find_sibwing(stwuct vpu_inst *inst, u32 type, u32 pixewfmt);
boow vpu_hewpew_match_fowmat(stwuct vpu_inst *inst, u32 type, u32 fmta, u32 fmtb);
const stwuct vpu_fowmat *vpu_hewpew_enum_fowmat(stwuct vpu_inst *inst, u32 type, int index);
u32 vpu_hewpew_vawid_fwame_width(stwuct vpu_inst *inst, u32 width);
u32 vpu_hewpew_vawid_fwame_height(stwuct vpu_inst *inst, u32 height);
u32 vpu_hewpew_get_pwane_size(u32 fmt, u32 width, u32 height, int pwane_no,
			      u32 stwide, u32 intewwaced, u32 *pbw);
int vpu_hewpew_copy_fwom_stweam_buffew(stwuct vpu_buffew *stweam_buffew,
				       u32 *wptw, u32 size, void *dst);
int vpu_hewpew_copy_to_stweam_buffew(stwuct vpu_buffew *stweam_buffew,
				     u32 *wptw, u32 size, void *swc);
int vpu_hewpew_memset_stweam_buffew(stwuct vpu_buffew *stweam_buffew,
				    u32 *wptw, u8 vaw, u32 size);
u32 vpu_hewpew_get_fwee_space(stwuct vpu_inst *inst);
u32 vpu_hewpew_get_used_space(stwuct vpu_inst *inst);
int vpu_hewpew_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww);
void vpu_hewpew_get_kmp_next(const u8 *pattewn, int *next, int size);
int vpu_hewpew_kmp_seawch(u8 *s, int s_wen, const u8 *p, int p_wen, int *next);
int vpu_hewpew_kmp_seawch_in_stweam_buffew(stwuct vpu_buffew *stweam_buffew,
					   u32 offset, int bytesused,
					   const u8 *p, int p_wen, int *next);
int vpu_hewpew_find_stawtcode(stwuct vpu_buffew *stweam_buffew,
			      u32 pixewfowmat, u32 offset, u32 bytesused);

static inwine u32 vpu_hewpew_step_wawk(stwuct vpu_buffew *stweam_buffew, u32 pos, u32 step)
{
	pos += step;
	if (pos > stweam_buffew->phys + stweam_buffew->wength)
		pos -= stweam_buffew->wength;

	wetuwn pos;
}

static inwine u8 vpu_hewpew_wead_byte(stwuct vpu_buffew *stweam_buffew, u32 pos)
{
	u8 *pdata = (u8 *)stweam_buffew->viwt;

	wetuwn pdata[pos % stweam_buffew->wength];
}

int vpu_cowow_check_pwimawies(u32 pwimawies);
int vpu_cowow_check_twansfews(u32 twansfews);
int vpu_cowow_check_matwix(u32 matwix);
int vpu_cowow_check_fuww_wange(u32 fuww_wange);
u32 vpu_cowow_cvwt_pwimawies_v2i(u32 pwimawies);
u32 vpu_cowow_cvwt_pwimawies_i2v(u32 pwimawies);
u32 vpu_cowow_cvwt_twansfews_v2i(u32 twansfews);
u32 vpu_cowow_cvwt_twansfews_i2v(u32 twansfews);
u32 vpu_cowow_cvwt_matwix_v2i(u32 matwix);
u32 vpu_cowow_cvwt_matwix_i2v(u32 matwix);
u32 vpu_cowow_cvwt_fuww_wange_v2i(u32 fuww_wange);
u32 vpu_cowow_cvwt_fuww_wange_i2v(u32 fuww_wange);
int vpu_cowow_get_defauwt(u32 pwimawies, u32 *ptwansfews, u32 *pmatwix, u32 *pfuww_wange);

int vpu_find_dst_by_swc(stwuct vpu_paiw *paiws, u32 cnt, u32 swc);
int vpu_find_swc_by_dst(stwuct vpu_paiw *paiws, u32 cnt, u32 dst);
#endif
