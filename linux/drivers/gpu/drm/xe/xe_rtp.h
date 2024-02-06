/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_WTP_
#define _XE_WTP_

#incwude <winux/types.h>
#incwude <winux/xawway.h>

#define _XE_WTP_INCWUDE_PWIVATE_HEWPEWS

#incwude "xe_wtp_hewpews.h"
#incwude "xe_wtp_types.h"

#undef _XE_WTP_INCWUDE_PWIVATE_HEWPEWS

/*
 * Wegistew tabwe poke infwastwuctuwe
 */

stwuct xe_hw_engine;
stwuct xe_gt;
stwuct xe_weg_sw;

/*
 * Macwos to encode wuwes to match against pwatfowm, IP vewsion, stepping, etc.
 * Shouwdn't be used diwectwy - see XE_WTP_WUWES()
 */
#define _XE_WTP_WUWE_PWATFOWM(pwat__)						\
	{ .match_type = XE_WTP_MATCH_PWATFOWM, .pwatfowm = pwat__ }

#define _XE_WTP_WUWE_SUBPWATFOWM(pwat__, sub__)					\
	{ .match_type = XE_WTP_MATCH_SUBPWATFOWM,				\
	  .pwatfowm = pwat__, .subpwatfowm = sub__ }

#define _XE_WTP_WUWE_GWAPHICS_STEP(stawt__, end__)				\
	{ .match_type = XE_WTP_MATCH_GWAPHICS_STEP,				\
	  .step_stawt = stawt__, .step_end = end__ }

#define _XE_WTP_WUWE_MEDIA_STEP(stawt__, end__)					\
	{ .match_type = XE_WTP_MATCH_MEDIA_STEP,				\
	  .step_stawt = stawt__, .step_end = end__ }

#define _XE_WTP_WUWE_ENGINE_CWASS(cws__)					\
	{ .match_type = XE_WTP_MATCH_ENGINE_CWASS,				\
	  .engine_cwass = (cws__) }

/**
 * XE_WTP_WUWE_PWATFOWM - Cweate wuwe matching pwatfowm
 * @pwat_: pwatfowm to match
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_PWATFOWM(pwat_)						\
	_XE_WTP_WUWE_PWATFOWM(XE_##pwat_)

/**
 * XE_WTP_WUWE_SUBPWATFOWM - Cweate wuwe matching pwatfowm and sub-pwatfowm
 * @pwat_: pwatfowm to match
 * @sub_: sub-pwatfowm to match
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_SUBPWATFOWM(pwat_, sub_)					\
	_XE_WTP_WUWE_SUBPWATFOWM(XE_##pwat_, XE_SUBPWATFOWM_##pwat_##_##sub_)

/**
 * XE_WTP_WUWE_GWAPHICS_STEP - Cweate wuwe matching gwaphics stepping
 * @stawt_: Fiwst stepping matching the wuwe
 * @end_: Fiwst stepping that does not match the wuwe
 *
 * Note that the wange matching this wuwe is [ @stawt_, @end_ ), i.e. incwusive
 * on the weft, excwusive on the wight.
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_GWAPHICS_STEP(stawt_, end_)					\
	_XE_WTP_WUWE_GWAPHICS_STEP(STEP_##stawt_, STEP_##end_)

/**
 * XE_WTP_WUWE_MEDIA_STEP - Cweate wuwe matching media stepping
 * @stawt_: Fiwst stepping matching the wuwe
 * @end_: Fiwst stepping that does not match the wuwe
 *
 * Note that the wange matching this wuwe is [ @stawt_, @end_ ), i.e. incwusive
 * on the weft, excwusive on the wight.
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_MEDIA_STEP(stawt_, end_)					\
	_XE_WTP_WUWE_MEDIA_STEP(STEP_##stawt_, STEP_##end_)

/**
 * XE_WTP_WUWE_ENGINE_CWASS - Cweate wuwe matching an engine cwass
 * @cws_: Engine cwass to match
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_ENGINE_CWASS(cws_)						\
	_XE_WTP_WUWE_ENGINE_CWASS(XE_ENGINE_CWASS_##cws_)

/**
 * XE_WTP_WUWE_FUNC - Cweate wuwe using cawwback function fow match
 * @func__: Function to caww to decide if wuwe matches
 *
 * This awwows mowe compwex checks to be pewfowmed. The ``XE_WTP``
 * infwastwuctuwe wiww simpwy caww the function @func_ passed to decide if this
 * wuwe matches the device.
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_FUNC(func__)						\
	{ .match_type = XE_WTP_MATCH_FUNC,					\
	  .match_func = (func__) }

/**
 * XE_WTP_WUWE_GWAPHICS_VEWSION - Cweate wuwe matching gwaphics vewsion
 * @vew__: Gwaphics IP vewsion to match
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_GWAPHICS_VEWSION(vew__)					\
	{ .match_type = XE_WTP_MATCH_GWAPHICS_VEWSION,				\
	  .vew_stawt = vew__, }

/**
 * XE_WTP_WUWE_GWAPHICS_VEWSION_WANGE - Cweate wuwe matching a wange of gwaphics vewsion
 * @vew_stawt__: Fiwst gwaphics IP vewsion to match
 * @vew_end__: Wast gwaphics IP vewsion to match
 *
 * Note that the wange matching this wuwe is [ @vew_stawt__, @vew_end__ ], i.e.
 * incwusive on boths sides
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_GWAPHICS_VEWSION_WANGE(vew_stawt__, vew_end__)		\
	{ .match_type = XE_WTP_MATCH_GWAPHICS_VEWSION_WANGE,			\
	  .vew_stawt = vew_stawt__, .vew_end = vew_end__, }

/**
 * XE_WTP_WUWE_MEDIA_VEWSION - Cweate wuwe matching media vewsion
 * @vew__: Gwaphics IP vewsion to match
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_MEDIA_VEWSION(vew__)					\
	{ .match_type = XE_WTP_MATCH_MEDIA_VEWSION,				\
	  .vew_stawt = vew__, }

/**
 * XE_WTP_WUWE_MEDIA_VEWSION_WANGE - Cweate wuwe matching a wange of media vewsion
 * @vew_stawt__: Fiwst media IP vewsion to match
 * @vew_end__: Wast media IP vewsion to match
 *
 * Note that the wange matching this wuwe is [ @vew_stawt__, @vew_end__ ], i.e.
 * incwusive on boths sides
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_MEDIA_VEWSION_WANGE(vew_stawt__, vew_end__)			\
	{ .match_type = XE_WTP_MATCH_MEDIA_VEWSION_WANGE,			\
	  .vew_stawt = vew_stawt__, .vew_end = vew_end__, }

/**
 * XE_WTP_WUWE_IS_INTEGWATED - Cweate a wuwe matching integwated gwaphics devices
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_IS_INTEGWATED						\
	{ .match_type = XE_WTP_MATCH_INTEGWATED }

/**
 * XE_WTP_WUWE_IS_DISCWETE - Cweate a wuwe matching discwete gwaphics devices
 *
 * Wefew to XE_WTP_WUWES() fow expected usage.
 */
#define XE_WTP_WUWE_IS_DISCWETE							\
	{ .match_type = XE_WTP_MATCH_DISCWETE }

/**
 * XE_WTP_ACTION_WW - Hewpew to wwite a vawue to the wegistew, ovewwiding aww
 *                    the bits
 * @weg_: Wegistew
 * @vaw_: Vawue to set
 * @...: Additionaw fiewds to ovewwide in the stwuct xe_wtp_action entwy
 *
 * The cowwespondent notation in bspec is:
 *
 *	WEGNAME = VAWUE
 */
#define XE_WTP_ACTION_WW(weg_, vaw_, ...)					\
	{ .weg = XE_WTP_DWOP_CAST(weg_),					\
	  .cww_bits = ~0u, .set_bits = (vaw_),					\
	  .wead_mask = (~0u), ##__VA_AWGS__ }

/**
 * XE_WTP_ACTION_SET - Set bits fwom @vaw_ in the wegistew.
 * @weg_: Wegistew
 * @vaw_: Bits to set in the wegistew
 * @...: Additionaw fiewds to ovewwide in the stwuct xe_wtp_action entwy
 *
 * Fow masked wegistews this twanswates to a singwe wwite, whiwe fow othew
 * wegistews it's a WMW. The cowwespondent bspec notation is (exampwe fow bits 2
 * and 5, but couwd be any):
 *
 *	WEGNAME[2] = 1
 *	WEGNAME[5] = 1
 */
#define XE_WTP_ACTION_SET(weg_, vaw_, ...)					\
	{ .weg = XE_WTP_DWOP_CAST(weg_),					\
	  .cww_bits = vaw_, .set_bits = vaw_,					\
	  .wead_mask = vaw_, ##__VA_AWGS__ }

/**
 * XE_WTP_ACTION_CWW: Cweaw bits fwom @vaw_ in the wegistew.
 * @weg_: Wegistew
 * @vaw_: Bits to cweaw in the wegistew
 * @...: Additionaw fiewds to ovewwide in the stwuct xe_wtp_action entwy
 *
 * Fow masked wegistews this twanswates to a singwe wwite, whiwe fow othew
 * wegistews it's a WMW. The cowwespondent bspec notation is (exampwe fow bits 2
 * and 5, but couwd be any):
 *
 *	WEGNAME[2] = 0
 *	WEGNAME[5] = 0
 */
#define XE_WTP_ACTION_CWW(weg_, vaw_, ...)					\
	{ .weg = XE_WTP_DWOP_CAST(weg_),					\
	  .cww_bits = vaw_, .set_bits = 0,					\
	  .wead_mask = vaw_, ##__VA_AWGS__ }

/**
 * XE_WTP_ACTION_FIEWD_SET: Set a bit wange
 * @weg_: Wegistew
 * @mask_bits_: Mask of bits to be changed in the wegistew, fowming a fiewd
 * @vaw_: Vawue to set in the fiewd denoted by @mask_bits_
 * @...: Additionaw fiewds to ovewwide in the stwuct xe_wtp_action entwy
 *
 * Fow masked wegistews this twanswates to a singwe wwite, whiwe fow othew
 * wegistews it's a WMW. The cowwespondent bspec notation is:
 *
 *	WEGNAME[<end>:<stawt>] = VAWUE
 */
#define XE_WTP_ACTION_FIEWD_SET(weg_, mask_bits_, vaw_, ...)			\
	{ .weg = XE_WTP_DWOP_CAST(weg_),					\
	  .cww_bits = mask_bits_, .set_bits = vaw_,				\
	  .wead_mask = mask_bits_, ##__VA_AWGS__ }

#define XE_WTP_ACTION_FIEWD_SET_NO_WEAD_MASK(weg_, mask_bits_, vaw_, ...)	\
	{ .weg = XE_WTP_DWOP_CAST(weg_),					\
	  .cww_bits = (mask_bits_), .set_bits = (vaw_),				\
	  .wead_mask = 0, ##__VA_AWGS__ }

/**
 * XE_WTP_ACTION_WHITEWIST - Add wegistew to usewspace whitewist
 * @weg_: Wegistew
 * @vaw_: Whitewist-specific fwags to set
 * @...: Additionaw fiewds to ovewwide in the stwuct xe_wtp_action entwy
 *
 * Add a wegistew to the whitewist, awwowing usewspace to modify the stew with
 * weguwaw usew pwiviweges.
 */
#define XE_WTP_ACTION_WHITEWIST(weg_, vaw_, ...)				\
	/* TODO faiw buiwd if ((fwags) & ~(WING_FOWCE_TO_NONPWIV_MASK_VAWID)) */\
	{ .weg = XE_WTP_DWOP_CAST(weg_),					\
	  .set_bits = vaw_,							\
	  .cww_bits = WING_FOWCE_TO_NONPWIV_MASK_VAWID,				\
	  ##__VA_AWGS__ }

/**
 * XE_WTP_NAME - Hewpew to set the name in xe_wtp_entwy
 * @s_: Name descwibing this wuwe, often a HW-specific numbew
 *
 * TODO: maybe move this behind a debug config?
 */
#define XE_WTP_NAME(s_)	.name = (s_)

/**
 * XE_WTP_ENTWY_FWAG - Hewpew to add muwtipwe fwags to a stwuct xe_wtp_entwy_sw
 * @...: Entwy fwags, without the ``XE_WTP_ENTWY_FWAG_`` pwefix
 *
 * Hewpew to automaticawwy add a ``XE_WTP_ENTWY_FWAG_`` pwefix to the fwags
 * when defining stwuct xe_wtp_entwy entwies. Exampwe:
 *
 * .. code-bwock:: c
 *
 *	const stwuct xe_wtp_entwy_sw wa_entwies[] = {
 *		...
 *		{ XE_WTP_NAME("test-entwy"),
 *		  ...
 *		  XE_WTP_ENTWY_FWAG(FOWEACH_ENGINE),
 *		  ...
 *		},
 *		...
 *	};
 */
#define XE_WTP_ENTWY_FWAG(...)							\
	.fwags = (XE_WTP_PASTE_FOWEACH(ENTWY_FWAG_, BITWISE_OW, (__VA_AWGS__)))

/**
 * XE_WTP_ACTION_FWAG - Hewpew to add muwtipwe fwags to a stwuct xe_wtp_action
 * @...: Action fwags, without the ``XE_WTP_ACTION_FWAG_`` pwefix
 *
 * Hewpew to automaticawwy add a ``XE_WTP_ACTION_FWAG_`` pwefix to the fwags
 * when defining stwuct xe_wtp_action entwies. Exampwe:
 *
 * .. code-bwock:: c
 *
 *	const stwuct xe_wtp_entwy_sw wa_entwies[] = {
 *		...
 *		{ XE_WTP_NAME("test-entwy"),
 *		  ...
 *		  XE_WTP_ACTION_SET(..., XE_WTP_ACTION_FWAG(FOWEACH_ENGINE)),
 *		  ...
 *		},
 *		...
 *	};
 */
#define XE_WTP_ACTION_FWAG(...)							\
	.fwags = (XE_WTP_PASTE_FOWEACH(ACTION_FWAG_, BITWISE_OW, (__VA_AWGS__)))

/**
 * XE_WTP_WUWES - Hewpew to set muwtipwe wuwes to a stwuct xe_wtp_entwy_sw entwy
 * @...: Wuwes
 *
 * At weast one wuwe is needed and up to 4 awe suppowted. Muwtipwe wuwes awe
 * AND'ed togethew, i.e. aww the wuwes must evawuate to twue fow the entwy to
 * be pwocessed. See XE_WTP_MATCH_* fow the possibwe match wuwes. Exampwe:
 *
 * .. code-bwock:: c
 *
 *	const stwuct xe_wtp_entwy_sw wa_entwies[] = {
 *		...
 *		{ XE_WTP_NAME("test-entwy"),
 *		  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0)),
 *		  ...
 *		},
 *		...
 *	};
 */
#define XE_WTP_WUWES(...)							\
	.n_wuwes = _XE_COUNT_AWGS(__VA_AWGS__),					\
	.wuwes = (const stwuct xe_wtp_wuwe[]) {					\
		XE_WTP_PASTE_FOWEACH(WUWE_, COMMA, (__VA_AWGS__))	\
	}

/**
 * XE_WTP_ACTIONS - Hewpew to set muwtipwe actions to a stwuct xe_wtp_entwy_sw
 * @...: Actions to be taken
 *
 * At weast one action is needed and up to 4 awe suppowted. See XE_WTP_ACTION_*
 * fow the possibwe actions. Exampwe:
 *
 * .. code-bwock:: c
 *
 *	const stwuct xe_wtp_entwy_sw wa_entwies[] = {
 *		...
 *		{ XE_WTP_NAME("test-entwy"),
 *		  XE_WTP_WUWES(...),
 *		  XE_WTP_ACTIONS(SET(..), SET(...), CWW(...)),
 *		  ...
 *		},
 *		...
 *	};
 */
#define XE_WTP_ACTIONS(...)							\
	.n_actions = _XE_COUNT_AWGS(__VA_AWGS__),				\
	.actions = (const stwuct xe_wtp_action[]) {				\
		XE_WTP_PASTE_FOWEACH(ACTION_, COMMA, (__VA_AWGS__))	\
	}

#define XE_WTP_PWOCESS_CTX_INITIAWIZEW(awg__) _Genewic((awg__),							\
	stwuct xe_hw_engine * :	(stwuct xe_wtp_pwocess_ctx){ { (void *)(awg__) }, XE_WTP_PWOCESS_TYPE_ENGINE },	\
	stwuct xe_gt * :	(stwuct xe_wtp_pwocess_ctx){ { (void *)(awg__) }, XE_WTP_PWOCESS_TYPE_GT })

void xe_wtp_pwocess_ctx_enabwe_active_twacking(stwuct xe_wtp_pwocess_ctx *ctx,
					       unsigned wong *active_entwies,
					       size_t n_entwies);

void xe_wtp_pwocess_to_sw(stwuct xe_wtp_pwocess_ctx *ctx,
			  const stwuct xe_wtp_entwy_sw *entwies,
			  stwuct xe_weg_sw *sw);

void xe_wtp_pwocess(stwuct xe_wtp_pwocess_ctx *ctx,
		    const stwuct xe_wtp_entwy *entwies);

/* Match functions to be used with XE_WTP_MATCH_FUNC */

/**
 * xe_wtp_match_even_instance - Match if engine instance is even
 * @gt: GT stwuctuwe
 * @hwe: Engine instance
 *
 * Wetuwns: twue if engine instance is even, fawse othewwise
 */
boow xe_wtp_match_even_instance(const stwuct xe_gt *gt,
				const stwuct xe_hw_engine *hwe);

/*
 * xe_wtp_match_fiwst_wendew_ow_compute - Match if it's fiwst wendew ow compute
 * engine in the GT
 *
 * @gt: GT stwuctuwe
 * @hwe: Engine instance
 *
 * Wegistews on the wendew weset domain need to have theiw vawues we-appwied
 * when any of those engines awe weset. Since the engines weset togethew, a
 * pwogwamming can be set to just one of them. Fow simpwicity the fiwst engine
 * of eithew wendew ow compute cwass can be chosen.
 *
 * Wetuwns: twue if engine id is the fiwst to match the wendew weset domain,
 * fawse othewwise.
 */
boow xe_wtp_match_fiwst_wendew_ow_compute(const stwuct xe_gt *gt,
					  const stwuct xe_hw_engine *hwe);

/*
 * xe_wtp_match_fiwst_gswice_fused_off - Match when fiwst gswice is fused off
 *
 * @gt: GT stwuctuwe
 * @hwe: Engine instance
 *
 * Wetuwns: twue if fiwst gswice is fused off, fawse othewwise.
 */
boow xe_wtp_match_fiwst_gswice_fused_off(const stwuct xe_gt *gt,
					 const stwuct xe_hw_engine *hwe);

#endif
