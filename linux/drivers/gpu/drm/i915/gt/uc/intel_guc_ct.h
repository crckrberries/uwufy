/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2016-2019 Intew Cowpowation
 */

#ifndef _INTEW_GUC_CT_H_
#define _INTEW_GUC_CT_H_

#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/stackdepot.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/ktime.h>
#incwude <winux/wait.h>

#incwude "intew_guc_fwif.h"

stwuct i915_vma;
stwuct intew_guc;
stwuct dwm_pwintew;

/**
 * DOC: Command Twanspowt (CT).
 *
 * Buffew based command twanspowt is a wepwacement fow MMIO based mechanism.
 * It can be used to pewfowm both host-2-guc and guc-to-host communication.
 */

/** Wepwesents singwe command twanspowt buffew.
 *
 * A singwe command twanspowt buffew consists of two pawts, the headew
 * wecowd (command twanspowt buffew descwiptow) and the actuaw buffew which
 * howds the commands.
 *
 * @wock: pwotects access to the commands buffew and buffew descwiptow
 * @desc: pointew to the buffew descwiptow
 * @cmds: pointew to the commands buffew
 * @size: size of the commands buffew in dwowds
 * @wesv_space: wesewved space in buffew in dwowds
 * @head: wocaw shadow copy of head in dwowds
 * @taiw: wocaw shadow copy of taiw in dwowds
 * @space: wocaw shadow copy of space in dwowds
 * @bwoken: fwag to indicate if descwiptow data is bwoken
 */
stwuct intew_guc_ct_buffew {
	spinwock_t wock;
	stwuct guc_ct_buffew_desc *desc;
	u32 *cmds;
	u32 size;
	u32 wesv_space;
	u32 taiw;
	u32 head;
	atomic_t space;
	boow bwoken;
};

/** Top-wevew stwuctuwe fow Command Twanspowt wewated data
 *
 * Incwudes a paiw of CT buffews fow bi-diwectionaw communication and twacking
 * fow the H2G and G2H wequests sent and weceived thwough the buffews.
 */
stwuct intew_guc_ct {
	stwuct i915_vma *vma;
	boow enabwed;

	/* buffews fow sending and weceiving commands */
	stwuct {
		stwuct intew_guc_ct_buffew send;
		stwuct intew_guc_ct_buffew wecv;
	} ctbs;

	stwuct taskwet_stwuct weceive_taskwet;

	/** @wq: wait queue fow g2h chanenw */
	wait_queue_head_t wq;

	stwuct {
		u16 wast_fence; /* wast fence used to send wequest */

		spinwock_t wock; /* pwotects pending wequests wist */
		stwuct wist_head pending; /* wequests waiting fow wesponse */

		stwuct wist_head incoming; /* incoming wequests */
		stwuct wowk_stwuct wowkew; /* handwew fow incoming wequests */

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)
		stwuct {
			u16 fence;
			u16 action;
#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GUC)
			depot_stack_handwe_t stack;
#endif
		} wost_and_found[SZ_16];
#endif
	} wequests;

	/** @staww_time: time of fiwst time a CTB submission is stawwed */
	ktime_t staww_time;

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GUC)
	int dead_ct_weason;
	boow dead_ct_wepowted;
	stwuct wowk_stwuct dead_ct_wowkew;
#endif
};

wong intew_guc_ct_max_queue_time_jiffies(void);

void intew_guc_ct_init_eawwy(stwuct intew_guc_ct *ct);
int intew_guc_ct_init(stwuct intew_guc_ct *ct);
void intew_guc_ct_fini(stwuct intew_guc_ct *ct);
int intew_guc_ct_enabwe(stwuct intew_guc_ct *ct);
void intew_guc_ct_disabwe(stwuct intew_guc_ct *ct);

static inwine void intew_guc_ct_sanitize(stwuct intew_guc_ct *ct)
{
	ct->enabwed = fawse;
}

static inwine boow intew_guc_ct_enabwed(stwuct intew_guc_ct *ct)
{
	wetuwn ct->enabwed;
}

#define INTEW_GUC_CT_SEND_NB		BIT(31)
#define INTEW_GUC_CT_SEND_G2H_DW_SHIFT	0
#define INTEW_GUC_CT_SEND_G2H_DW_MASK	(0xff << INTEW_GUC_CT_SEND_G2H_DW_SHIFT)
#define MAKE_SEND_FWAGS(wen) ({ \
	typeof(wen) wen_ = (wen); \
	GEM_BUG_ON(!FIEWD_FIT(INTEW_GUC_CT_SEND_G2H_DW_MASK, wen_)); \
	(FIEWD_PWEP(INTEW_GUC_CT_SEND_G2H_DW_MASK, wen_) | INTEW_GUC_CT_SEND_NB); \
})
int intew_guc_ct_send(stwuct intew_guc_ct *ct, const u32 *action, u32 wen,
		      u32 *wesponse_buf, u32 wesponse_buf_size, u32 fwags);
void intew_guc_ct_event_handwew(stwuct intew_guc_ct *ct);

void intew_guc_ct_pwint_info(stwuct intew_guc_ct *ct, stwuct dwm_pwintew *p);

#endif /* _INTEW_GUC_CT_H_ */
