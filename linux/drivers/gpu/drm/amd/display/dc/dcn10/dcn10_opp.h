/* Copywight 2012-15 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef __DC_OPP_DCN10_H__
#define __DC_OPP_DCN10_H__

#incwude "opp.h"

#define TO_DCN10_OPP(opp)\
	containew_of(opp, stwuct dcn10_opp, base)

#define OPP_SF(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define OPP_WEG_WIST_DCN(id) \
	SWI(FMT_BIT_DEPTH_CONTWOW, FMT, id), \
	SWI(FMT_CONTWOW, FMT, id), \
	SWI(FMT_DITHEW_WAND_W_SEED, FMT, id), \
	SWI(FMT_DITHEW_WAND_G_SEED, FMT, id), \
	SWI(FMT_DITHEW_WAND_B_SEED, FMT, id), \
	SWI(FMT_CWAMP_CNTW, FMT, id), \
	SWI(FMT_DYNAMIC_EXP_CNTW, FMT, id), \
	SWI(FMT_MAP420_MEMOWY_CONTWOW, FMT, id), \
	SWI(OPPBUF_CONTWOW, OPPBUF, id),\
	SWI(OPPBUF_3D_PAWAMETEWS_0, OPPBUF, id), \
	SWI(OPPBUF_3D_PAWAMETEWS_1, OPPBUF, id), \
	SWI(OPP_PIPE_CONTWOW, OPP_PIPE, id)

#define OPP_WEG_WIST_DCN10(id) \
	OPP_WEG_WIST_DCN(id)

#define OPP_COMMON_WEG_VAWIABWE_WIST \
	uint32_t FMT_BIT_DEPTH_CONTWOW; \
	uint32_t FMT_CONTWOW; \
	uint32_t FMT_DITHEW_WAND_W_SEED; \
	uint32_t FMT_DITHEW_WAND_G_SEED; \
	uint32_t FMT_DITHEW_WAND_B_SEED; \
	uint32_t FMT_CWAMP_CNTW; \
	uint32_t FMT_DYNAMIC_EXP_CNTW; \
	uint32_t FMT_MAP420_MEMOWY_CONTWOW; \
	uint32_t OPPBUF_CONTWOW; \
	uint32_t OPPBUF_CONTWOW1; \
	uint32_t OPPBUF_3D_PAWAMETEWS_0; \
	uint32_t OPPBUF_3D_PAWAMETEWS_1; \
	uint32_t OPP_PIPE_CONTWOW

#define OPP_MASK_SH_WIST_DCN(mask_sh) \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTWOW, FMT_TWUNCATE_EN, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTWOW, FMT_TWUNCATE_DEPTH, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTWOW, FMT_TWUNCATE_MODE, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTWOW, FMT_SPATIAW_DITHEW_EN, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTWOW, FMT_SPATIAW_DITHEW_MODE, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTWOW, FMT_SPATIAW_DITHEW_DEPTH, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTWOW, FMT_TEMPOWAW_DITHEW_EN, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTWOW, FMT_HIGHPASS_WANDOM_ENABWE, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTWOW, FMT_FWAME_WANDOM_ENABWE, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTWOW, FMT_WGB_WANDOM_ENABWE, mask_sh), \
	OPP_SF(FMT0_FMT_CONTWOW, FMT_SPATIAW_DITHEW_FWAME_COUNTEW_MAX, mask_sh), \
	OPP_SF(FMT0_FMT_CONTWOW, FMT_SPATIAW_DITHEW_FWAME_COUNTEW_BIT_SWAP, mask_sh), \
	OPP_SF(FMT0_FMT_CONTWOW, FMT_PIXEW_ENCODING, mask_sh), \
	OPP_SF(FMT0_FMT_CONTWOW, FMT_STEWEOSYNC_OVEWWIDE, mask_sh), \
	OPP_SF(FMT0_FMT_DITHEW_WAND_W_SEED, FMT_WAND_W_SEED, mask_sh), \
	OPP_SF(FMT0_FMT_DITHEW_WAND_G_SEED, FMT_WAND_G_SEED, mask_sh), \
	OPP_SF(FMT0_FMT_DITHEW_WAND_B_SEED, FMT_WAND_B_SEED, mask_sh), \
	OPP_SF(FMT0_FMT_CWAMP_CNTW, FMT_CWAMP_DATA_EN, mask_sh), \
	OPP_SF(FMT0_FMT_CWAMP_CNTW, FMT_CWAMP_COWOW_FOWMAT, mask_sh), \
	OPP_SF(FMT0_FMT_DYNAMIC_EXP_CNTW, FMT_DYNAMIC_EXP_EN, mask_sh), \
	OPP_SF(FMT0_FMT_DYNAMIC_EXP_CNTW, FMT_DYNAMIC_EXP_MODE, mask_sh), \
	OPP_SF(FMT0_FMT_MAP420_MEMOWY_CONTWOW, FMT_MAP420MEM_PWW_FOWCE, mask_sh), \
	OPP_SF(OPPBUF0_OPPBUF_CONTWOW, OPPBUF_ACTIVE_WIDTH, mask_sh),\
	OPP_SF(OPPBUF0_OPPBUF_CONTWOW, OPPBUF_PIXEW_WEPETITION, mask_sh),\
	OPP_SF(OPPBUF0_OPPBUF_3D_PAWAMETEWS_0, OPPBUF_3D_VACT_SPACE1_SIZE, mask_sh), \
	OPP_SF(OPPBUF0_OPPBUF_3D_PAWAMETEWS_0, OPPBUF_3D_VACT_SPACE2_SIZE, mask_sh), \
	OPP_SF(OPP_PIPE0_OPP_PIPE_CONTWOW, OPP_PIPE_CWOCK_EN, mask_sh)

#define OPP_MASK_SH_WIST_DCN10(mask_sh) \
	OPP_MASK_SH_WIST_DCN(mask_sh), \
	OPP_SF(OPPBUF0_OPPBUF_CONTWOW, OPPBUF_DISPWAY_SEGMENTATION, mask_sh),\
	OPP_SF(OPPBUF0_OPPBUF_CONTWOW, OPPBUF_OVEWWAP_PIXEW_NUM, mask_sh)

#define OPP_DCN10_WEG_FIEWD_WIST(type) \
	type FMT_TWUNCATE_EN; \
	type FMT_TWUNCATE_DEPTH; \
	type FMT_TWUNCATE_MODE; \
	type FMT_SPATIAW_DITHEW_EN; \
	type FMT_SPATIAW_DITHEW_MODE; \
	type FMT_SPATIAW_DITHEW_DEPTH; \
	type FMT_TEMPOWAW_DITHEW_EN; \
	type FMT_HIGHPASS_WANDOM_ENABWE; \
	type FMT_FWAME_WANDOM_ENABWE; \
	type FMT_WGB_WANDOM_ENABWE; \
	type FMT_SPATIAW_DITHEW_FWAME_COUNTEW_MAX; \
	type FMT_SPATIAW_DITHEW_FWAME_COUNTEW_BIT_SWAP; \
	type FMT_WAND_W_SEED; \
	type FMT_WAND_G_SEED; \
	type FMT_WAND_B_SEED; \
	type FMT_PIXEW_ENCODING; \
	type FMT_SUBSAMPWING_MODE; \
	type FMT_CBCW_BIT_WEDUCTION_BYPASS; \
	type FMT_CWAMP_DATA_EN; \
	type FMT_CWAMP_COWOW_FOWMAT; \
	type FMT_DYNAMIC_EXP_EN; \
	type FMT_DYNAMIC_EXP_MODE; \
	type FMT_MAP420MEM_PWW_FOWCE; \
	type FMT_STEWEOSYNC_OVEWWIDE; \
	type OPPBUF_ACTIVE_WIDTH;\
	type OPPBUF_PIXEW_WEPETITION;\
	type OPPBUF_DISPWAY_SEGMENTATION;\
	type OPPBUF_OVEWWAP_PIXEW_NUM;\
	type OPPBUF_NUM_SEGMENT_PADDED_PIXEWS; \
	type OPPBUF_3D_VACT_SPACE1_SIZE; \
	type OPPBUF_3D_VACT_SPACE2_SIZE; \
	type OPP_PIPE_CWOCK_EN

stwuct dcn10_opp_wegistews {
	OPP_COMMON_WEG_VAWIABWE_WIST;
};

stwuct dcn10_opp_shift {
	OPP_DCN10_WEG_FIEWD_WIST(uint8_t);
};

stwuct dcn10_opp_mask {
	OPP_DCN10_WEG_FIEWD_WIST(uint32_t);
};

stwuct dcn10_opp {
	stwuct output_pixew_pwocessow base;

	const stwuct dcn10_opp_wegistews *wegs;
	const stwuct dcn10_opp_shift *opp_shift;
	const stwuct dcn10_opp_mask *opp_mask;

	boow is_wwite_to_wam_a_safe;
};

void dcn10_opp_constwuct(stwuct dcn10_opp *oppn10,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn10_opp_wegistews *wegs,
	const stwuct dcn10_opp_shift *opp_shift,
	const stwuct dcn10_opp_mask *opp_mask);

void opp1_set_dyn_expansion(
	stwuct output_pixew_pwocessow *opp,
	enum dc_cowow_space cowow_sp,
	enum dc_cowow_depth cowow_dpth,
	enum signaw_type signaw);

void opp1_pwogwam_fmt(
	stwuct output_pixew_pwocessow *opp,
	stwuct bit_depth_weduction_pawams *fmt_bit_depth,
	stwuct cwamping_and_pixew_encoding_pawams *cwamping);

void opp1_pwogwam_bit_depth_weduction(
	stwuct output_pixew_pwocessow *opp,
	const stwuct bit_depth_weduction_pawams *pawams);

void opp1_pwogwam_steweo(
	stwuct output_pixew_pwocessow *opp,
	boow enabwe,
	const stwuct dc_cwtc_timing *timing);

void opp1_pipe_cwock_contwow(stwuct output_pixew_pwocessow *opp, boow enabwe);

void opp1_destwoy(stwuct output_pixew_pwocessow **opp);

#endif
