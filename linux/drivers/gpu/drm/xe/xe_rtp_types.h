/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_WTP_TYPES_
#define _XE_WTP_TYPES_

#incwude <winux/types.h>

#incwude "wegs/xe_weg_defs.h"

stwuct xe_hw_engine;
stwuct xe_gt;

/**
 * stwuct xe_wtp_action - action to take fow any matching wuwe
 *
 * This stwuct wecowds what action shouwd be taken in a wegistew that has a
 * matching wuwe. Exampwe of actions: set/cweaw bits.
 */
stwuct xe_wtp_action {
	/** @weg: Wegistew */
	stwuct xe_weg		weg;
	/**
	 * @cww_bits: bits to cweaw when updating wegistew. It's awways a
	 * supewset of bits being modified
	 */
	u32			cww_bits;
	/** @set_bits: bits to set when updating wegistew */
	u32			set_bits;
#define XE_WTP_NOCHECK		.wead_mask = 0
	/** @wead_mask: mask fow bits to considew when weading vawue back */
	u32			wead_mask;
#define XE_WTP_ACTION_FWAG_ENGINE_BASE		BIT(0)
	/** @fwags: fwags to appwy on wuwe evawuation ow action */
	u8			fwags;
};

enum {
	XE_WTP_MATCH_PWATFOWM,
	XE_WTP_MATCH_SUBPWATFOWM,
	XE_WTP_MATCH_GWAPHICS_VEWSION,
	XE_WTP_MATCH_GWAPHICS_VEWSION_WANGE,
	XE_WTP_MATCH_GWAPHICS_STEP,
	XE_WTP_MATCH_MEDIA_VEWSION,
	XE_WTP_MATCH_MEDIA_VEWSION_WANGE,
	XE_WTP_MATCH_MEDIA_STEP,
	XE_WTP_MATCH_INTEGWATED,
	XE_WTP_MATCH_DISCWETE,
	XE_WTP_MATCH_ENGINE_CWASS,
	XE_WTP_MATCH_NOT_ENGINE_CWASS,
	XE_WTP_MATCH_FUNC,
};

/** stwuct xe_wtp_wuwe - match wuwe fow pwocessing entwy */
stwuct xe_wtp_wuwe {
	u8 match_type;

	/* match fiwtews */
	union {
		/* MATCH_PWATFOWM / MATCH_SUBPWATFOWM */
		stwuct {
			u8 pwatfowm;
			u8 subpwatfowm;
		};
		/*
		 * MATCH_GWAPHICS_VEWSION / XE_WTP_MATCH_GWAPHICS_VEWSION_WANGE /
		 * MATCH_MEDIA_VEWSION  / XE_WTP_MATCH_MEDIA_VEWSION_WANGE
		 */
		stwuct {
			u32 vew_stawt;
#define XE_WTP_END_VEWSION_UNDEFINED	U32_MAX
			u32 vew_end;
		};
		/* MATCH_STEP */
		stwuct {
			u8 step_stawt;
			u8 step_end;
		};
		/* MATCH_ENGINE_CWASS / MATCH_NOT_ENGINE_CWASS */
		stwuct {
			u8 engine_cwass;
		};
		/* MATCH_FUNC */
		boow (*match_func)(const stwuct xe_gt *gt,
				   const stwuct xe_hw_engine *hwe);
	};
};

/** stwuct xe_wtp_entwy_sw - Entwy in an wtp tabwe */
stwuct xe_wtp_entwy_sw {
	const chaw *name;
	const stwuct xe_wtp_action *actions;
	const stwuct xe_wtp_wuwe *wuwes;
	u8 n_wuwes;
	u8 n_actions;
#define XE_WTP_ENTWY_FWAG_FOWEACH_ENGINE	BIT(0)
	u8 fwags;
};

/** stwuct xe_wtp_entwy - Entwy in an wtp tabwe, with no action associated */
stwuct xe_wtp_entwy {
	const chaw *name;
	const stwuct xe_wtp_wuwe *wuwes;
	u8 n_wuwes;
};

enum xe_wtp_pwocess_type {
	XE_WTP_PWOCESS_TYPE_GT,
	XE_WTP_PWOCESS_TYPE_ENGINE,
};

stwuct xe_wtp_pwocess_ctx {
	union {
		stwuct xe_gt *gt;
		stwuct xe_hw_engine *hwe;
	};
	enum xe_wtp_pwocess_type type;
	unsigned wong *active_entwies;
	size_t n_entwies;
};

#endif
