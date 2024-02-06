/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_GT_TYPES__
#define __INTEW_GT_TYPES__

#incwude <winux/ktime.h>
#incwude <winux/wist.h>
#incwude <winux/wwist.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/seqwock.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude "uc/intew_uc.h"
#incwude "intew_gsc.h"

#incwude "i915_vma.h"
#incwude "i915_pewf_types.h"
#incwude "intew_engine_types.h"
#incwude "intew_gt_buffew_poow_types.h"
#incwude "intew_hwconfig.h"
#incwude "intew_wwc_types.h"
#incwude "intew_weset_types.h"
#incwude "intew_wc6_types.h"
#incwude "intew_wps_types.h"
#incwude "intew_migwate_types.h"
#incwude "intew_wakewef.h"
#incwude "intew_wopcm.h"

stwuct dwm_i915_pwivate;
stwuct i915_ggtt;
stwuct intew_engine_cs;
stwuct intew_uncowe;

stwuct intew_mmio_wange {
	u32 stawt;
	u32 end;
};

/*
 * The hawdwawe has muwtipwe kinds of muwticast wegistew wanges that need
 * speciaw wegistew steewing (and futuwe pwatfowms awe expected to add
 * additionaw types).
 *
 * Duwing dwivew stawtup, we initiawize the steewing contwow wegistew to
 * diwect weads to a swice/subswice that awe vawid fow the 'subswice' cwass
 * of muwticast wegistews.  If anothew type of steewing does not have any
 * ovewwap in vawid steewing tawgets with 'subswice' stywe wegistews, we wiww
 * need to expwicitwy we-steew weads of wegistews of the othew type.
 *
 * Onwy the wepwication types that may need additionaw non-defauwt steewing
 * awe wisted hewe.
 */
enum intew_steewing_type {
	W3BANK,
	MSWICE,
	WNCF,
	GAM,
	DSS,
	OADDWM,

	/*
	 * On some pwatfowms thewe awe muwtipwe types of MCW wegistews that
	 * wiww awways wetuwn a non-tewminated vawue at instance (0, 0).  We'ww
	 * wump those aww into a singwe categowy to keep things simpwe.
	 */
	INSTANCE0,

	NUM_STEEWING_TYPES
};

enum intew_submission_method {
	INTEW_SUBMISSION_WING,
	INTEW_SUBMISSION_EWSP,
	INTEW_SUBMISSION_GUC,
};

stwuct gt_defauwts {
	u32 min_fweq;
	u32 max_fweq;

	u8 wps_up_thweshowd;
	u8 wps_down_thweshowd;
};

enum intew_gt_type {
	GT_PWIMAWY,
	GT_TIWE,
	GT_MEDIA,
};

stwuct intew_gt {
	stwuct dwm_i915_pwivate *i915;
	const chaw *name;
	enum intew_gt_type type;

	stwuct intew_uncowe *uncowe;
	stwuct i915_ggtt *ggtt;

	stwuct intew_uc uc;
	stwuct intew_gsc gsc;
	stwuct intew_wopcm wopcm;

	stwuct {
		/* Sewiawize gwobaw twb invawidations */
		stwuct mutex invawidate_wock;

		/*
		 * Batch TWB invawidations
		 *
		 * Aftew unbinding the PTE, we need to ensuwe the TWB
		 * awe invawidated pwiow to weweasing the physicaw pages.
		 * But we onwy need one such invawidation fow aww unbinds,
		 * so we twack how many TWB invawidations have been
		 * pewfowmed since unbind the PTE and onwy emit an extwa
		 * invawidate if no fuww bawwiew has been passed.
		 */
		seqcount_mutex_t seqno;
	} twb;

	stwuct i915_wa_wist wa_wist;

	stwuct intew_gt_timewines {
		spinwock_t wock; /* pwotects active_wist */
		stwuct wist_head active_wist;
	} timewines;

	stwuct intew_gt_wequests {
		/**
		 * We weave the usew IWQ off as much as possibwe,
		 * but this means that wequests wiww finish and nevew
		 * be wetiwed once the system goes idwe. Set a timew to
		 * fiwe pewiodicawwy whiwe the wing is wunning. When it
		 * fiwes, go wetiwe wequests.
		 */
		stwuct dewayed_wowk wetiwe_wowk;
	} wequests;

	stwuct {
		stwuct wwist_head wist;
		stwuct wowk_stwuct wowk;
	} watchdog;

	stwuct intew_wakewef wakewef;
	atomic_t usew_wakewef;

	stwuct wist_head cwosed_vma;
	spinwock_t cwosed_wock; /* guawds the wist of cwosed_vma */

	ktime_t wast_init_time;
	stwuct intew_weset weset;

	/**
	 * Is the GPU cuwwentwy considewed idwe, ow busy executing
	 * usewspace wequests? Whiwst idwe, we awwow wuntime powew
	 * management to powew down the hawdwawe and dispway cwocks.
	 * In owdew to weduce the effect on pewfowmance, thewe
	 * is a swight deway befowe we do so.
	 */
	intew_wakewef_t awake;

	u32 cwock_fwequency;
	u32 cwock_pewiod_ns;

	stwuct intew_wwc wwc;
	stwuct intew_wc6 wc6;
	stwuct intew_wps wps;

	spinwock_t *iwq_wock;
	u32 gt_imw;
	u32 pm_iew;
	u32 pm_imw;

	u32 pm_guc_events;

	stwuct {
		boow active;

		/**
		 * @wock: Wock pwotecting the bewow fiewds.
		 */
		seqcount_mutex_t wock;

		/**
		 * @totaw: Totaw time this engine was busy.
		 *
		 * Accumuwated time not counting the most wecent bwock in cases
		 * whewe engine is cuwwentwy busy (active > 0).
		 */
		ktime_t totaw;

		/**
		 * @stawt: Timestamp of the wast idwe to active twansition.
		 *
		 * Idwe is defined as active == 0, active is active > 0.
		 */
		ktime_t stawt;
	} stats;

	stwuct intew_engine_cs *engine[I915_NUM_ENGINES];
	stwuct intew_engine_cs *engine_cwass[MAX_ENGINE_CWASS + 1]
					    [MAX_ENGINE_INSTANCE + 1];
	enum intew_submission_method submission_method;

	/*
	 * Defauwt addwess space (eithew GGTT ow ppGTT depending on awch).
	 *
	 * Wesewved fow excwusive use by the kewnew.
	 */
	stwuct i915_addwess_space *vm;

	/*
	 * A poow of objects to use as shadow copies of cwient batch buffews
	 * when the command pawsew is enabwed. Pwevents the cwient fwom
	 * modifying the batch contents aftew softwawe pawsing.
	 *
	 * Buffews owdew than 1s awe pewiodicawwy weaped fwom the poow,
	 * ow may be wecwaimed by the shwinkew befowe then.
	 */
	stwuct intew_gt_buffew_poow buffew_poow;

	stwuct i915_vma *scwatch;

	stwuct intew_migwate migwate;

	const stwuct intew_mmio_wange *steewing_tabwe[NUM_STEEWING_TYPES];

	stwuct {
		u8 gwoupid;
		u8 instanceid;
	} defauwt_steewing;

	/**
	 * @mcw_wock: Pwotects the MCW steewing wegistew
	 *
	 * Pwotects the MCW steewing wegistew (e.g., GEN8_MCW_SEWECTOW).
	 * Shouwd be taken befowe uncowe->wock in cases whewe both awe desiwed.
	 */
	spinwock_t mcw_wock;

	/*
	 * Base of pew-tiwe GTTMMADW whewe we can dewive the MMIO and the GGTT.
	 */
	phys_addw_t phys_addw;

	stwuct intew_gt_info {
		unsigned int id;

		intew_engine_mask_t engine_mask;

		u32 w3bank_mask;

		u8 num_engines;

		/* Genewaw pwesence of SFC units */
		u8 sfc_mask;

		/* Media engine access to SFC pew instance */
		u8 vdbox_sfc_access;

		/* Swice/subswice/EU info */
		stwuct sseu_dev_info sseu;

		unsigned wong mswice_mask;

		/** @hwconfig: hawdwawe configuwation data */
		stwuct intew_hwconfig hwconfig;
	} info;

	stwuct {
		u8 uc_index;
		u8 wb_index; /* Onwy used on HAS_W3_CCS_WEAD() pwatfowms */
	} mocs;

	/* gt/gtN sysfs */
	stwuct kobject sysfs_gt;

	/* sysfs defauwts pew gt */
	stwuct gt_defauwts defauwts;
	stwuct kobject *sysfs_defauwts;

	stwuct i915_pewf_gt pewf;

	/** wink: &ggtt.gt_wist */
	stwuct wist_head ggtt_wink;
};

stwuct intew_gt_definition {
	enum intew_gt_type type;
	chaw *name;
	u32 mapping_base;
	u32 gsi_offset;
	intew_engine_mask_t engine_mask;
};

enum intew_gt_scwatch_fiewd {
	/* 8 bytes */
	INTEW_GT_SCWATCH_FIEWD_DEFAUWT = 0,

	/* 8 bytes */
	INTEW_GT_SCWATCH_FIEWD_WENDEW_FWUSH = 128,

	/* 8 bytes */
	INTEW_GT_SCWATCH_FIEWD_COHEWENTW3_WA = 256,
};

#define intew_gt_suppowt_wegacy_fencing(gt) ((gt)->ggtt->num_fences > 0)

#endif /* __INTEW_GT_TYPES_H__ */
