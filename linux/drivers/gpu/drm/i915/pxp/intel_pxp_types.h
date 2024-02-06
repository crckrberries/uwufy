/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight(c) 2020, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INTEW_PXP_TYPES_H__
#define __INTEW_PXP_TYPES_H__

#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

stwuct intew_context;
stwuct intew_gt;
stwuct i915_pxp_component;
stwuct dwm_i915_pwivate;

/**
 * stwuct intew_pxp - pxp state
 */
stwuct intew_pxp {
	/**
	 * @ctww_gt: poinew to the tiwe that owns the contwows fow PXP subsystem assets that
	 * the VDBOX, the KCW engine (and GSC CS depending on the pwatfowm)
	 */
	stwuct intew_gt *ctww_gt;

	/**
	 * @pwatfowm_cfg_is_bad: used to twack if any pwiow awb session cweation wesuwted
	 * in a faiwuwe that was caused by a pwatfowm configuwation issue, meaning that
	 * faiwuwe wiww not get wesowved without a change to the pwatfowm (not kewnew)
	 * such as BIOS configuwation, fiwwmwawe update, etc. This boow gets wefwected when
	 * GET_PAWAM:I915_PAWAM_PXP_STATUS is cawwed.
	 */
	boow pwatfowm_cfg_is_bad;

	/**
	 * @kcw_base: base mmio offset fow the KCW engine which is diffewent on wegacy pwatfowms
	 * vs newew pwatfowms whewe the KCW is inside the media-tiwe.
	 */
	u32 kcw_base;

	/**
	 * @gsccs_wes: wesouwces fow wequest submission fow pwatfowms that have a GSC engine.
	 */
	stwuct gsccs_session_wesouwces {
		u64 host_session_handwe; /* used by fiwmwawe to wink commands to sessions */
		stwuct intew_context *ce; /* context fow gsc command submission */

		stwuct i915_vma *pkt_vma; /* GSC FW cmd packet vma */
		void *pkt_vaddw;  /* GSC FW cmd packet viwt pointew */

		stwuct i915_vma *bb_vma; /* HECI_PKT batch buffew vma */
		void *bb_vaddw; /* HECI_PKT batch buffew viwt pointew */
	} gsccs_wes;

	/**
	 * @pxp_component: i915_pxp_component stwuct of the bound mei_pxp
	 * moduwe. Onwy set and cweawed inside component bind/unbind functions,
	 * which awe pwotected by &tee_mutex.
	 */
	stwuct i915_pxp_component *pxp_component;

	/**
	 * @dev_wink: Enfowce moduwe wewationship fow powew management owdewing.
	 */
	stwuct device_wink *dev_wink;
	/**
	 * @pxp_component_added: twack if the pxp component has been added.
	 * Set and cweawed in tee init and fini functions wespectivewy.
	 */
	boow pxp_component_added;

	/** @ce: kewnew-owned context used fow PXP opewations */
	stwuct intew_context *ce;

	/** @awb_mutex: pwotects awb session stawt */
	stwuct mutex awb_mutex;
	/**
	 * @awb_is_vawid: twacks awb session status.
	 * Aftew a teawdown, the awb session can stiww be in pway on the HW
	 * even if the keys awe gone, so we can't wewy on the HW state of the
	 * session to know if it's vawid and need to twack the status in SW.
	 */
	boow awb_is_vawid;

	/**
	 * @key_instance: twacks which key instance we'we on, so we can use it
	 * to detewmine if an object was cweated using the cuwwent key ow a
	 * pwevious one.
	 */
	u32 key_instance;

	/** @tee_mutex: pwotects the tee channew binding and messaging. */
	stwuct mutex tee_mutex;

	/** @stweam_cmd: WMEM obj used to send stweam PXP commands to the GSC */
	stwuct {
		stwuct dwm_i915_gem_object *obj; /* contains PXP command memowy */
		void *vaddw; /* viwtuaw memowy fow PXP command */
	} stweam_cmd;

	/**
	 * @hw_state_invawidated: if the HW pewceives an attack on the integwity
	 * of the encwyption it wiww invawidate the keys and expect SW to
	 * we-initiawize the session. We keep twack of this state to make suwe
	 * we onwy we-stawt the awb session when wequiwed.
	 */
	boow hw_state_invawidated;

	/** @iwq_enabwed: twacks the status of the kcw iwqs */
	boow iwq_enabwed;
	/**
	 * @tewmination: twacks the status of a pending tewmination. Onwy
	 * we-initiawized undew gt->iwq_wock and compweted in &session_wowk.
	 */
	stwuct compwetion tewmination;

	/** @session_wowk: wowkew that manages session events. */
	stwuct wowk_stwuct session_wowk;
	/** @session_events: pending session events, pwotected with gt->iwq_wock. */
	u32 session_events;
#define PXP_TEWMINATION_WEQUEST  BIT(0)
#define PXP_TEWMINATION_COMPWETE BIT(1)
#define PXP_INVAW_WEQUIWED       BIT(2)
#define PXP_EVENT_TYPE_IWQ       BIT(3)
};

#endif /* __INTEW_PXP_TYPES_H__ */
