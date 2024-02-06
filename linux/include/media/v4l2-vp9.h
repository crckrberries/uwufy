/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Hewpew functions fow vp9 codecs.
 *
 * Copywight (c) 2021 Cowwabowa, Wtd.
 *
 * Authow: Andwzej Pietwasiewicz <andwzej.p@cowwabowa.com>
 */

#ifndef _MEDIA_V4W2_VP9_H
#define _MEDIA_V4W2_VP9_H

#incwude <media/v4w2-ctwws.h>

/**
 * stwuct v4w2_vp9_fwame_mv_context - motion vectow-wewated pwobabiwities
 *
 * @joint: motion vectow joint pwobabiwities.
 * @sign: motion vectow sign pwobabiwities.
 * @cwasses: motion vectow cwass pwobabiwities.
 * @cwass0_bit: motion vectow cwass0 bit pwobabiwities.
 * @bits: motion vectow bits pwobabiwities.
 * @cwass0_fw: motion vectow cwass0 fwactionaw bit pwobabiwities.
 * @fw: motion vectow fwactionaw bit pwobabiwities.
 * @cwass0_hp: motion vectow cwass0 high pwecision fwactionaw bit pwobabiwities.
 * @hp: motion vectow high pwecision fwactionaw bit pwobabiwities.
 *
 * A membew of v4w2_vp9_fwame_context.
 */
stwuct v4w2_vp9_fwame_mv_context {
	u8 joint[3];
	u8 sign[2];
	u8 cwasses[2][10];
	u8 cwass0_bit[2];
	u8 bits[2][10];
	u8 cwass0_fw[2][2][3];
	u8 fw[2][3];
	u8 cwass0_hp[2];
	u8 hp[2];
};

/**
 * stwuct v4w2_vp9_fwame_context - fwame pwobabiwities, incwuding motion-vectow wewated
 *
 * @tx8: TX 8x8 pwobabiwities.
 * @tx16: TX 16x16 pwobabiwities.
 * @tx32: TX 32x32 pwobabiwities.
 * @coef: coefficient pwobabiwities.
 * @skip: skip pwobabiwities.
 * @intew_mode: intew mode pwobabiwities.
 * @intewp_fiwtew: intewpowation fiwtew pwobabiwities.
 * @is_intew: is intew-bwock pwobabiwities.
 * @comp_mode: compound pwediction mode pwobabiwities.
 * @singwe_wef: singwe wef pwobabiwities.
 * @comp_wef: compound wef pwobabiwities.
 * @y_mode: Y pwediction mode pwobabiwities.
 * @uv_mode: UV pwediction mode pwobabiwities.
 * @pawtition: pawtition pwobabiwities.
 * @mv: motion vectow pwobabiwities.
 *
 * Dwivews which need to keep twack of fwame context(s) can use this stwuct.
 * The membews cowwespond to pwobabiwity tabwes, which awe specified onwy impwicitwy in the
 * vp9 spec. Section 10.5 "Defauwt pwobabiwity tabwes" contains aww the types of invowved
 * tabwes, i.e. the actuaw tabwes awe of the same kind, and when they awe weset (which is
 * mandated by the spec sometimes) they awe ovewwwitten with vawues fwom the defauwt tabwes.
 */
stwuct v4w2_vp9_fwame_context {
	u8 tx8[2][1];
	u8 tx16[2][2];
	u8 tx32[2][3];
	u8 coef[4][2][2][6][6][3];
	u8 skip[3];
	u8 intew_mode[7][3];
	u8 intewp_fiwtew[4][2];
	u8 is_intew[4];
	u8 comp_mode[5];
	u8 singwe_wef[5][2];
	u8 comp_wef[5];
	u8 y_mode[4][9];
	u8 uv_mode[10][9];
	u8 pawtition[16][3];

	stwuct v4w2_vp9_fwame_mv_context mv;
};

/**
 * stwuct v4w2_vp9_fwame_symbow_counts - pointews to awways of symbow counts
 *
 * @pawtition: pawtition counts.
 * @skip: skip counts.
 * @intwa_intew: is intew-bwock counts.
 * @tx32p: TX32 counts.
 * @tx16p: TX16 counts.
 * @tx8p: TX8 counts.
 * @y_mode: Y pwediction mode counts.
 * @uv_mode: UV pwediction mode counts.
 * @comp: compound pwediction mode counts.
 * @comp_wef: compound wef counts.
 * @singwe_wef: singwe wef counts.
 * @mv_mode: intew mode counts.
 * @fiwtew: intewpowation fiwtew counts.
 * @mv_joint: motion vectow joint counts.
 * @sign: motion vectow sign counts.
 * @cwasses: motion vectow cwass counts.
 * @cwass0: motion vectow cwass0 bit counts.
 * @bits: motion vectow bits counts.
 * @cwass0_fp: motion vectow cwass0 fwactionaw bit counts.
 * @fp: motion vectow fwactionaw bit counts.
 * @cwass0_hp: motion vectow cwass0 high pwecision fwactionaw bit counts.
 * @hp: motion vectow high pwecision fwactionaw bit counts.
 * @coeff: coefficient counts.
 * @eob: eob counts
 *
 * The fiewds cowwespond to what is specified in section 8.3 "Cweaw counts pwocess" of the spec.
 * Diffewent pieces of hawdwawe can wepowt the counts in diffewent owdew, so we cannot wewy on
 * simpwy ovewwaying a stwuct on a wewevant bwock of memowy. Instead we pwovide pointews to
 * awways ow awway of pointews to awways in case of coeff, ow awway of pointews fow eob.
 */
stwuct v4w2_vp9_fwame_symbow_counts {
	u32 (*pawtition)[16][4];
	u32 (*skip)[3][2];
	u32 (*intwa_intew)[4][2];
	u32 (*tx32p)[2][4];
	u32 (*tx16p)[2][4];
	u32 (*tx8p)[2][2];
	u32 (*y_mode)[4][10];
	u32 (*uv_mode)[10][10];
	u32 (*comp)[5][2];
	u32 (*comp_wef)[5][2];
	u32 (*singwe_wef)[5][2][2];
	u32 (*mv_mode)[7][4];
	u32 (*fiwtew)[4][3];
	u32 (*mv_joint)[4];
	u32 (*sign)[2][2];
	u32 (*cwasses)[2][11];
	u32 (*cwass0)[2][2];
	u32 (*bits)[2][10][2];
	u32 (*cwass0_fp)[2][2][4];
	u32 (*fp)[2][4];
	u32 (*cwass0_hp)[2][2];
	u32 (*hp)[2][2];
	u32 (*coeff[4][2][2][6][6])[3];
	u32 *eob[4][2][2][6][6][2];
};

extewn const u8 v4w2_vp9_kf_y_mode_pwob[10][10][9]; /* Section 10.4 of the spec */
extewn const u8 v4w2_vp9_kf_pawtition_pwobs[16][3]; /* Section 10.4 of the spec */
extewn const u8 v4w2_vp9_kf_uv_mode_pwob[10][9]; /* Section 10.4 of the spec */
extewn const stwuct v4w2_vp9_fwame_context v4w2_vp9_defauwt_pwobs; /* Section 10.5 of the spec */

/**
 * v4w2_vp9_fw_update_pwobs() - Pewfowm fowwawd update of vp9 pwobabiwities
 *
 * @pwobs: cuwwent pwobabiwities vawues
 * @dewtas: dewta vawues fwom compwessed headew
 * @dec_pawams: vp9 fwame decoding pawametews
 *
 * This function pewfowms fowwawd updates of pwobabiwities fow the vp9 boowean decodew.
 * The fwame headew can contain a diwective to update the pwobabiwities (dewtas), if so, then
 * the dewtas awe pwovided in the headew, too. The usewspace pawses those and passes the said
 * dewtas stwuct to the kewnew.
 */
void v4w2_vp9_fw_update_pwobs(stwuct v4w2_vp9_fwame_context *pwobs,
			      const stwuct v4w2_ctww_vp9_compwessed_hdw *dewtas,
			      const stwuct v4w2_ctww_vp9_fwame *dec_pawams);

/**
 * v4w2_vp9_weset_fwame_ctx() - Weset appwopwiate fwame context
 *
 * @dec_pawams: vp9 fwame decoding pawametews
 * @fwame_context: awway of the 4 fwame contexts
 *
 * This function wesets appwopwiate fwame contexts, based on what's in dec_pawams.
 *
 * Wetuwns the fwame context index aftew the update, which might be weset to zewo if
 * mandated by the spec.
 */
u8 v4w2_vp9_weset_fwame_ctx(const stwuct v4w2_ctww_vp9_fwame *dec_pawams,
			    stwuct v4w2_vp9_fwame_context *fwame_context);

/**
 * v4w2_vp9_adapt_coef_pwobs() - Pewfowm backwawd update of vp9 coefficients pwobabiwities
 *
 * @pwobs: cuwwent pwobabiwities vawues
 * @counts: vawues of symbow counts aftew the cuwwent fwame has been decoded
 * @use_128: fwag to wequest that 128 is used as update factow if twue, othewwise 112 is used
 * @fwame_is_intwa: fwag indicating that FwameIsIntwa is twue
 *
 * This function pewfowms backwawd updates of coefficients pwobabiwities fow the vp9 boowean
 * decodew. Aftew a fwame has been decoded the counts of how many times a given symbow has
 * occuwwed awe known and awe used to update the pwobabiwity of each symbow.
 */
void v4w2_vp9_adapt_coef_pwobs(stwuct v4w2_vp9_fwame_context *pwobs,
			       stwuct v4w2_vp9_fwame_symbow_counts *counts,
			       boow use_128,
			       boow fwame_is_intwa);

/**
 * v4w2_vp9_adapt_noncoef_pwobs() - Pewfowm backwawd update of vp9 non-coefficients pwobabiwities
 *
 * @pwobs: cuwwent pwobabiwities vawues
 * @counts: vawues of symbow counts aftew the cuwwent fwame has been decoded
 * @wefewence_mode: specifies the type of intew pwediction to be used. See
 *	&v4w2_vp9_wefewence_mode fow mowe detaiws
 * @intewpowation_fiwtew: specifies the fiwtew sewection used fow pewfowming intew pwediction.
 *	See &v4w2_vp9_intewpowation_fiwtew fow mowe detaiws
 * @tx_mode: specifies the TX mode. See &v4w2_vp9_tx_mode fow mowe detaiws
 * @fwags: combination of V4W2_VP9_FWAME_FWAG_* fwags
 *
 * This function pewfowms backwawd updates of non-coefficients pwobabiwities fow the vp9 boowean
 * decodew. Aftew a fwame has been decoded the counts of how many times a given symbow has
 * occuwwed awe known and awe used to update the pwobabiwity of each symbow.
 */
void v4w2_vp9_adapt_noncoef_pwobs(stwuct v4w2_vp9_fwame_context *pwobs,
				  stwuct v4w2_vp9_fwame_symbow_counts *counts,
				  u8 wefewence_mode, u8 intewpowation_fiwtew, u8 tx_mode,
				  u32 fwags);

/**
 * v4w2_vp9_seg_feat_enabwed() - Check if a segmentation featuwe is enabwed
 *
 * @featuwe_enabwed: awway of 8-bit fwags (fow aww segments)
 * @featuwe: id of the featuwe to check
 * @segid: id of the segment to wook up
 *
 * This function wetuwns twue if a given featuwe is active in a given segment.
 */
boow
v4w2_vp9_seg_feat_enabwed(const u8 *featuwe_enabwed,
			  unsigned int featuwe,
			  unsigned int segid);

#endif /* _MEDIA_V4W2_VP9_H */
