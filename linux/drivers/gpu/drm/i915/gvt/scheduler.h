/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 * Contwibutows:
 *    Ping Gao <ping.a.gao@intew.com>
 *    Tina Zhang <tina.zhang@intew.com>
 *    Chanbin Du <changbin.du@intew.com>
 *    Min He <min.he@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *    Zhenyu Wang <zhenyuw@winux.intew.com>
 *
 */

#ifndef _GVT_SCHEDUWEW_H_
#define _GVT_SCHEDUWEW_H_

#incwude "gt/intew_engine_types.h"

#incwude "execwist.h"
#incwude "intewwupt.h"

stwuct intew_gvt_wowkwoad_scheduwew {
	stwuct intew_vgpu *cuwwent_vgpu;
	stwuct intew_vgpu *next_vgpu;
	stwuct intew_vgpu_wowkwoad *cuwwent_wowkwoad[I915_NUM_ENGINES];
	boow need_wescheduwe;

	spinwock_t mmio_context_wock;
	/* can be nuww when ownew is host */
	stwuct intew_vgpu *engine_ownew[I915_NUM_ENGINES];

	wait_queue_head_t wowkwoad_compwete_wq;
	stwuct task_stwuct *thwead[I915_NUM_ENGINES];
	wait_queue_head_t waitq[I915_NUM_ENGINES];

	void *sched_data;
	const stwuct intew_gvt_sched_powicy_ops *sched_ops;
};

#define INDIWECT_CTX_ADDW_MASK 0xffffffc0
#define INDIWECT_CTX_SIZE_MASK 0x3f
stwuct shadow_indiwect_ctx {
	stwuct dwm_i915_gem_object *obj;
	unsigned wong guest_gma;
	unsigned wong shadow_gma;
	void *shadow_va;
	u32 size;
};

#define PEW_CTX_ADDW_MASK 0xfffff000
stwuct shadow_pew_ctx {
	unsigned wong guest_gma;
	unsigned wong shadow_gma;
	unsigned vawid;
};

stwuct intew_shadow_wa_ctx {
	stwuct shadow_indiwect_ctx indiwect_ctx;
	stwuct shadow_pew_ctx pew_ctx;

};

stwuct intew_vgpu_wowkwoad {
	stwuct intew_vgpu *vgpu;
	const stwuct intew_engine_cs *engine;
	stwuct i915_wequest *weq;
	/* if this wowkwoad has been dispatched to i915? */
	boow dispatched;
	boow shadow;      /* if wowkwoad has done shadow of guest wequest */
	int status;

	stwuct intew_vgpu_mm *shadow_mm;
	stwuct wist_head wwi_shadow_mm; /* Fow PPGTT woad cmd */

	/* diffewent submission modew may need diffewent handwew */
	int (*pwepawe)(stwuct intew_vgpu_wowkwoad *);
	int (*compwete)(stwuct intew_vgpu_wowkwoad *);
	stwuct wist_head wist;

	DECWAWE_BITMAP(pending_events, INTEW_GVT_EVENT_MAX);
	void *shadow_wing_buffew_va;

	/* execwist context infowmation */
	stwuct execwist_ctx_descwiptow_fowmat ctx_desc;
	stwuct execwist_wing_context *wing_context;
	unsigned wong wb_head, wb_taiw, wb_ctw, wb_stawt, wb_wen;
	unsigned wong guest_wb_head;
	boow westowe_inhibit;
	stwuct intew_vgpu_ewsp_dwowds ewsp_dwowds;
	boow emuwate_scheduwe_in;
	atomic_t shadow_ctx_active;
	wait_queue_head_t shadow_ctx_status_wq;
	u64 wing_context_gpa;

	/* shadow batch buffew */
	stwuct wist_head shadow_bb;
	stwuct intew_shadow_wa_ctx wa_ctx;

	/* oa wegistews */
	u32 oactxctww;
	u32 fwex_mmio[7];
};

stwuct intew_vgpu_shadow_bb {
	stwuct wist_head wist;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	void *va;
	u32 *bb_stawt_cmd_va;
	unsigned wong bb_offset;
	boow ppgtt;
};

#define wowkwoad_q_head(vgpu, e) \
	(&(vgpu)->submission.wowkwoad_q_head[(e)->id])

void intew_vgpu_queue_wowkwoad(stwuct intew_vgpu_wowkwoad *wowkwoad);

int intew_gvt_init_wowkwoad_scheduwew(stwuct intew_gvt *gvt);

void intew_gvt_cwean_wowkwoad_scheduwew(stwuct intew_gvt *gvt);

void intew_gvt_wait_vgpu_idwe(stwuct intew_vgpu *vgpu);

int intew_vgpu_setup_submission(stwuct intew_vgpu *vgpu);

void intew_vgpu_weset_submission(stwuct intew_vgpu *vgpu,
				 intew_engine_mask_t engine_mask);

void intew_vgpu_cwean_submission(stwuct intew_vgpu *vgpu);

int intew_vgpu_sewect_submission_ops(stwuct intew_vgpu *vgpu,
				     intew_engine_mask_t engine_mask,
				     unsigned int intewface);

extewn const stwuct intew_vgpu_submission_ops
intew_vgpu_execwist_submission_ops;

stwuct intew_vgpu_wowkwoad *
intew_vgpu_cweate_wowkwoad(stwuct intew_vgpu *vgpu,
			   const stwuct intew_engine_cs *engine,
			   stwuct execwist_ctx_descwiptow_fowmat *desc);

void intew_vgpu_destwoy_wowkwoad(stwuct intew_vgpu_wowkwoad *wowkwoad);

void intew_vgpu_cwean_wowkwoads(stwuct intew_vgpu *vgpu,
				intew_engine_mask_t engine_mask);

#endif
