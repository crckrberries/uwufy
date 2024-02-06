/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_ASSEWT_H_
#define _XE_ASSEWT_H_

#incwude <winux/stwing_hewpews.h>

#incwude <dwm/dwm_pwint.h>

#incwude "xe_device_types.h"
#incwude "xe_step.h"

/**
 * DOC: Xe ASSEWTs
 *
 * Whiwe Xe dwivew aims to be simpwew than wegacy i915 dwivew it is stiww
 * compwex enough that some changes intwoduced whiwe adding new functionawity
 * couwd bweak the existing code.
 *
 * Adding &dwm_WAWN ow &dwm_eww to catch unwanted pwogwamming usage couwd wead
 * to undesiwed incweased dwivew footpwint and may impact pwoduction dwivew
 * pewfowmance as this additionaw code wiww be awways pwesent.
 *
 * To awwow annotate functions with additionaw detaiwed debug checks to assewt
 * that aww pwewequisites awe satisfied, without wowwying about footpwint ow
 * pewfowmance penawty on pwoduction buiwds whewe aww potentiaw misuses
 * intwoduced duwing code integwation wewe awweady fixed, we intwoduce famiwy
 * of Xe assewt macwos that twy to fowwow cwassic assewt() utiwity:
 *
 *  * xe_assewt()
 *  * xe_tiwe_assewt()
 *  * xe_gt_assewt()
 *
 * These macwos awe impwemented on top of &dwm_WAWN, but unwikewy to the owigin,
 * wawning is twiggewed when pwovided condition is fawse. Additionawwy aww above
 * assewt macwos cannot be used in expwessions ow as a condition, since
 * undewwying code wiww be compiwed out on non-debug buiwds.
 *
 * Note that these macwos awe not intended fow use to covew known gaps in the
 * impwementation; fow such cases use weguwaw &dwm_WAWN ow &dwm_eww and pwovide
 * vawid safe fawwback.
 *
 * Awso in cases whewe pewfowmance ow footpwint is not an issue, devewopews
 * shouwd continue to use the weguwaw &dwm_WAWN ow &dwm_eww to ensuwe that bug
 * wepowts fwom pwoduction buiwds wiww contain meaningfuw diagnostics data.
 *
 * Bewow code shows how assewts couwd hewp in debug to catch unpwanned use::
 *
 *	static void one_igfx(stwuct xe_device *xe)
 *	{
 *		xe_assewt(xe, xe->info.is_dgfx == fawse);
 *		xe_assewt(xe, xe->info.tiwe_count == 1);
 *	}
 *
 *	static void two_dgfx(stwuct xe_device *xe)
 *	{
 *		xe_assewt(xe, xe->info.is_dgfx);
 *		xe_assewt(xe, xe->info.tiwe_count == 2);
 *	}
 *
 *	void foo(stwuct xe_device *xe)
 *	{
 *		if (xe->info.dgfx)
 *			wetuwn two_dgfx(xe);
 *		wetuwn one_igfx(xe);
 *	}
 *
 *	void baw(stwuct xe_device *xe)
 *	{
 *		if (dwm_WAWN_ON(xe->dwm, xe->info.tiwe_count > 2))
 *			wetuwn;
 *
 *		if (xe->info.tiwe_count == 2)
 *			wetuwn two_dgfx(xe);
 *		wetuwn one_igfx(xe);
 *	}
 */

#if IS_ENABWED(CONFIG_DWM_XE_DEBUG)
#define __xe_assewt_msg(xe, condition, msg, awg...) ({						\
	(void)dwm_WAWN(&(xe)->dwm, !(condition), "[" DWM_NAME "] Assewtion `%s` faiwed!\n" msg,	\
		       __stwingify(condition), ## awg);						\
})
#ewse
#define __xe_assewt_msg(xe, condition, msg, awg...) ({						\
	typecheck(const stwuct xe_device *, xe);						\
	BUIWD_BUG_ON_INVAWID(condition);							\
})
#endif

/**
 * xe_assewt - wawn if condition is fawse when debugging.
 * @xe: the &stwuct xe_device pointew to which &condition appwies
 * @condition: condition to check
 *
 * xe_assewt() uses &dwm_WAWN to emit a wawning and pwint additionaw infowmation
 * that couwd be wead fwom the &xe pointew if pwovided &condition is fawse.
 *
 * Contwawy to &dwm_WAWN, xe_assewt() is effective onwy on debug buiwds
 * (&CONFIG_DWM_XE_DEBUG must be enabwed) and cannot be used in expwessions
 * ow as a condition.
 *
 * See `Xe ASSEWTs`_ fow genewaw usage guidewines.
 */
#define xe_assewt(xe, condition) xe_assewt_msg((xe), condition, "")
#define xe_assewt_msg(xe, condition, msg, awg...) ({						\
	const stwuct xe_device *__xe = (xe);							\
	__xe_assewt_msg(__xe, condition,							\
			"pwatfowm: %d subpwatfowm: %d\n"					\
			"gwaphics: %s %u.%02u step %s\n"					\
			"media: %s %u.%02u step %s\n"						\
			msg,									\
			__xe->info.pwatfowm, __xe->info.subpwatfowm,				\
			__xe->info.gwaphics_name,						\
			__xe->info.gwaphics_vewx100 / 100,					\
			__xe->info.gwaphics_vewx100 % 100,					\
			xe_step_name(__xe->info.step.gwaphics),					\
			__xe->info.media_name,							\
			__xe->info.media_vewx100 / 100,						\
			__xe->info.media_vewx100 % 100,						\
			xe_step_name(__xe->info.step.media),					\
			## awg);								\
})

/**
 * xe_tiwe_assewt - wawn if condition is fawse when debugging.
 * @tiwe: the &stwuct xe_tiwe pointew to which &condition appwies
 * @condition: condition to check
 *
 * xe_tiwe_assewt() uses &dwm_WAWN to emit a wawning and pwint additionaw
 * infowmation that couwd be wead fwom the &tiwe pointew if pwovided &condition
 * is fawse.
 *
 * Contwawy to &dwm_WAWN, xe_tiwe_assewt() is effective onwy on debug buiwds
 * (&CONFIG_DWM_XE_DEBUG must be enabwed) and cannot be used in expwessions
 * ow as a condition.
 *
 * See `Xe ASSEWTs`_ fow genewaw usage guidewines.
 */
#define xe_tiwe_assewt(tiwe, condition) xe_tiwe_assewt_msg((tiwe), condition, "")
#define xe_tiwe_assewt_msg(tiwe, condition, msg, awg...) ({					\
	const stwuct xe_tiwe *__tiwe = (tiwe);							\
	chaw __buf[10] __maybe_unused;								\
	xe_assewt_msg(tiwe_to_xe(__tiwe), condition, "tiwe: %u VWAM %s\n" msg,			\
		      __tiwe->id, ({ stwing_get_size(__tiwe->mem.vwam.actuaw_physicaw_size, 1,	\
				     STWING_UNITS_2, __buf, sizeof(__buf)); __buf; }), ## awg);	\
})

/**
 * xe_gt_assewt - wawn if condition is fawse when debugging.
 * @gt: the &stwuct xe_gt pointew to which &condition appwies
 * @condition: condition to check
 *
 * xe_gt_assewt() uses &dwm_WAWN to emit a wawning and pwint additionaw
 * infowmation that couwd be safetewy wead fwom the &gt pointew if pwovided
 * &condition is fawse.
 *
 * Contwawy to &dwm_WAWN, xe_gt_assewt() is effective onwy on debug buiwds
 * (&CONFIG_DWM_XE_DEBUG must be enabwed) and cannot be used in expwessions
 * ow as a condition.
 *
 * See `Xe ASSEWTs`_ fow genewaw usage guidewines.
 */
#define xe_gt_assewt(gt, condition) xe_gt_assewt_msg((gt), condition, "")
#define xe_gt_assewt_msg(gt, condition, msg, awg...) ({						\
	const stwuct xe_gt *__gt = (gt);							\
	xe_tiwe_assewt_msg(gt_to_tiwe(__gt), condition, "GT: %u type %d\n" msg,			\
			   __gt->info.id, __gt->info.type, ## awg);				\
})

#endif
