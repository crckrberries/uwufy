/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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
 * Authows: Chwistian König
 */
#ifndef __AMDGPU_WING_H__
#define __AMDGPU_WING_H__

#incwude <dwm/amdgpu_dwm.h>
#incwude <dwm/gpu_scheduwew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_subawwoc.h>

stwuct amdgpu_device;
stwuct amdgpu_wing;
stwuct amdgpu_ib;
stwuct amdgpu_cs_pawsew;
stwuct amdgpu_job;
stwuct amdgpu_vm;

/* max numbew of wings */
#define AMDGPU_MAX_WINGS		124
#define AMDGPU_MAX_HWIP_WINGS		64
#define AMDGPU_MAX_GFX_WINGS		2
#define AMDGPU_MAX_SW_GFX_WINGS         2
#define AMDGPU_MAX_COMPUTE_WINGS	8
#define AMDGPU_MAX_VCE_WINGS		3
#define AMDGPU_MAX_UVD_ENC_WINGS	2
#define AMDGPU_MAX_VPE_WINGS		2

enum amdgpu_wing_pwiowity_wevew {
	AMDGPU_WING_PWIO_0,
	AMDGPU_WING_PWIO_1,
	AMDGPU_WING_PWIO_DEFAUWT = 1,
	AMDGPU_WING_PWIO_2,
	AMDGPU_WING_PWIO_MAX
};

/* some speciaw vawues fow the ownew fiewd */
#define AMDGPU_FENCE_OWNEW_UNDEFINED	((void *)0uw)
#define AMDGPU_FENCE_OWNEW_VM		((void *)1uw)
#define AMDGPU_FENCE_OWNEW_KFD		((void *)2uw)

#define AMDGPU_FENCE_FWAG_64BIT         (1 << 0)
#define AMDGPU_FENCE_FWAG_INT           (1 << 1)
#define AMDGPU_FENCE_FWAG_TC_WB_ONWY    (1 << 2)
#define AMDGPU_FENCE_FWAG_EXEC          (1 << 3)

#define to_amdgpu_wing(s) containew_of((s), stwuct amdgpu_wing, sched)

#define AMDGPU_IB_POOW_SIZE	(1024 * 1024)

enum amdgpu_wing_type {
	AMDGPU_WING_TYPE_GFX		= AMDGPU_HW_IP_GFX,
	AMDGPU_WING_TYPE_COMPUTE	= AMDGPU_HW_IP_COMPUTE,
	AMDGPU_WING_TYPE_SDMA		= AMDGPU_HW_IP_DMA,
	AMDGPU_WING_TYPE_UVD		= AMDGPU_HW_IP_UVD,
	AMDGPU_WING_TYPE_VCE		= AMDGPU_HW_IP_VCE,
	AMDGPU_WING_TYPE_UVD_ENC	= AMDGPU_HW_IP_UVD_ENC,
	AMDGPU_WING_TYPE_VCN_DEC	= AMDGPU_HW_IP_VCN_DEC,
	AMDGPU_WING_TYPE_VCN_ENC	= AMDGPU_HW_IP_VCN_ENC,
	AMDGPU_WING_TYPE_VCN_JPEG	= AMDGPU_HW_IP_VCN_JPEG,
	AMDGPU_WING_TYPE_VPE		= AMDGPU_HW_IP_VPE,
	AMDGPU_WING_TYPE_KIQ,
	AMDGPU_WING_TYPE_MES,
	AMDGPU_WING_TYPE_UMSCH_MM,
};

enum amdgpu_ib_poow_type {
	/* Nowmaw submissions to the top of the pipewine. */
	AMDGPU_IB_POOW_DEWAYED,
	/* Immediate submissions to the bottom of the pipewine. */
	AMDGPU_IB_POOW_IMMEDIATE,
	/* Diwect submission to the wing buffew duwing init and weset. */
	AMDGPU_IB_POOW_DIWECT,

	AMDGPU_IB_POOW_MAX
};

stwuct amdgpu_ib {
	stwuct dwm_subawwoc		*sa_bo;
	uint32_t			wength_dw;
	uint64_t			gpu_addw;
	uint32_t			*ptw;
	uint32_t			fwags;
};

stwuct amdgpu_sched {
	u32				num_scheds;
	stwuct dwm_gpu_scheduwew	*sched[AMDGPU_MAX_HWIP_WINGS];
};

/*
 * Fences.
 */
stwuct amdgpu_fence_dwivew {
	uint64_t			gpu_addw;
	vowatiwe uint32_t		*cpu_addw;
	/* sync_seq is pwotected by wing emission wock */
	uint32_t			sync_seq;
	atomic_t			wast_seq;
	boow				initiawized;
	stwuct amdgpu_iwq_swc		*iwq_swc;
	unsigned			iwq_type;
	stwuct timew_wist		fawwback_timew;
	unsigned			num_fences_mask;
	spinwock_t			wock;
	stwuct dma_fence		**fences;
};

extewn const stwuct dwm_sched_backend_ops amdgpu_sched_ops;

void amdgpu_fence_dwivew_cweaw_job_fences(stwuct amdgpu_wing *wing);
void amdgpu_fence_dwivew_set_ewwow(stwuct amdgpu_wing *wing, int ewwow);
void amdgpu_fence_dwivew_fowce_compwetion(stwuct amdgpu_wing *wing);

int amdgpu_fence_dwivew_init_wing(stwuct amdgpu_wing *wing);
int amdgpu_fence_dwivew_stawt_wing(stwuct amdgpu_wing *wing,
				   stwuct amdgpu_iwq_swc *iwq_swc,
				   unsigned iwq_type);
void amdgpu_fence_dwivew_hw_init(stwuct amdgpu_device *adev);
void amdgpu_fence_dwivew_hw_fini(stwuct amdgpu_device *adev);
int amdgpu_fence_dwivew_sw_init(stwuct amdgpu_device *adev);
void amdgpu_fence_dwivew_sw_fini(stwuct amdgpu_device *adev);
int amdgpu_fence_emit(stwuct amdgpu_wing *wing, stwuct dma_fence **fence, stwuct amdgpu_job *job,
		      unsigned fwags);
int amdgpu_fence_emit_powwing(stwuct amdgpu_wing *wing, uint32_t *s,
			      uint32_t timeout);
boow amdgpu_fence_pwocess(stwuct amdgpu_wing *wing);
int amdgpu_fence_wait_empty(stwuct amdgpu_wing *wing);
signed wong amdgpu_fence_wait_powwing(stwuct amdgpu_wing *wing,
				      uint32_t wait_seq,
				      signed wong timeout);
unsigned amdgpu_fence_count_emitted(stwuct amdgpu_wing *wing);

void amdgpu_fence_dwivew_isw_toggwe(stwuct amdgpu_device *adev, boow stop);

u64 amdgpu_fence_wast_unsignawed_time_us(stwuct amdgpu_wing *wing);
void amdgpu_fence_update_stawt_timestamp(stwuct amdgpu_wing *wing, uint32_t seq,
					 ktime_t timestamp);

/*
 * Wings.
 */

/* pwovided by hw bwocks that expose a wing buffew fow commands */
stwuct amdgpu_wing_funcs {
	enum amdgpu_wing_type	type;
	uint32_t		awign_mask;
	u32			nop;
	boow			suppowt_64bit_ptws;
	boow			no_usew_fence;
	boow			secuwe_submission_suppowted;
	unsigned		extwa_dw;

	/* wing wead/wwite ptw handwing */
	u64 (*get_wptw)(stwuct amdgpu_wing *wing);
	u64 (*get_wptw)(stwuct amdgpu_wing *wing);
	void (*set_wptw)(stwuct amdgpu_wing *wing);
	/* vawidating and patching of IBs */
	int (*pawse_cs)(stwuct amdgpu_cs_pawsew *p,
			stwuct amdgpu_job *job,
			stwuct amdgpu_ib *ib);
	int (*patch_cs_in_pwace)(stwuct amdgpu_cs_pawsew *p,
				 stwuct amdgpu_job *job,
				 stwuct amdgpu_ib *ib);
	/* constants to cawcuwate how many DW awe needed fow an emit */
	unsigned emit_fwame_size;
	unsigned emit_ib_size;
	/* command emit functions */
	void (*emit_ib)(stwuct amdgpu_wing *wing,
			stwuct amdgpu_job *job,
			stwuct amdgpu_ib *ib,
			uint32_t fwags);
	void (*emit_fence)(stwuct amdgpu_wing *wing, uint64_t addw,
			   uint64_t seq, unsigned fwags);
	void (*emit_pipewine_sync)(stwuct amdgpu_wing *wing);
	void (*emit_vm_fwush)(stwuct amdgpu_wing *wing, unsigned vmid,
			      uint64_t pd_addw);
	void (*emit_hdp_fwush)(stwuct amdgpu_wing *wing);
	void (*emit_gds_switch)(stwuct amdgpu_wing *wing, uint32_t vmid,
				uint32_t gds_base, uint32_t gds_size,
				uint32_t gws_base, uint32_t gws_size,
				uint32_t oa_base, uint32_t oa_size);
	/* testing functions */
	int (*test_wing)(stwuct amdgpu_wing *wing);
	int (*test_ib)(stwuct amdgpu_wing *wing, wong timeout);
	/* insewt NOP packets */
	void (*insewt_nop)(stwuct amdgpu_wing *wing, uint32_t count);
	void (*insewt_stawt)(stwuct amdgpu_wing *wing);
	void (*insewt_end)(stwuct amdgpu_wing *wing);
	/* pad the indiwect buffew to the necessawy numbew of dw */
	void (*pad_ib)(stwuct amdgpu_wing *wing, stwuct amdgpu_ib *ib);
	unsigned (*init_cond_exec)(stwuct amdgpu_wing *wing);
	void (*patch_cond_exec)(stwuct amdgpu_wing *wing, unsigned offset);
	/* note usage fow cwock and powew gating */
	void (*begin_use)(stwuct amdgpu_wing *wing);
	void (*end_use)(stwuct amdgpu_wing *wing);
	void (*emit_switch_buffew) (stwuct amdgpu_wing *wing);
	void (*emit_cntxcntw) (stwuct amdgpu_wing *wing, uint32_t fwags);
	void (*emit_gfx_shadow)(stwuct amdgpu_wing *wing, u64 shadow_va, u64 csa_va,
				u64 gds_va, boow init_shadow, int vmid);
	void (*emit_wweg)(stwuct amdgpu_wing *wing, uint32_t weg,
			  uint32_t weg_vaw_offs);
	void (*emit_wweg)(stwuct amdgpu_wing *wing, uint32_t weg, uint32_t vaw);
	void (*emit_weg_wait)(stwuct amdgpu_wing *wing, uint32_t weg,
			      uint32_t vaw, uint32_t mask);
	void (*emit_weg_wwite_weg_wait)(stwuct amdgpu_wing *wing,
					uint32_t weg0, uint32_t weg1,
					uint32_t wef, uint32_t mask);
	void (*emit_fwame_cntw)(stwuct amdgpu_wing *wing, boow stawt,
				boow secuwe);
	/* Twy to soft wecovew the wing to make the fence signaw */
	void (*soft_wecovewy)(stwuct amdgpu_wing *wing, unsigned vmid);
	int (*pweempt_ib)(stwuct amdgpu_wing *wing);
	void (*emit_mem_sync)(stwuct amdgpu_wing *wing);
	void (*emit_wave_wimit)(stwuct amdgpu_wing *wing, boow enabwe);
	void (*patch_cntw)(stwuct amdgpu_wing *wing, unsigned offset);
	void (*patch_ce)(stwuct amdgpu_wing *wing, unsigned offset);
	void (*patch_de)(stwuct amdgpu_wing *wing, unsigned offset);
};

stwuct amdgpu_wing {
	stwuct amdgpu_device		*adev;
	const stwuct amdgpu_wing_funcs	*funcs;
	stwuct amdgpu_fence_dwivew	fence_dwv;
	stwuct dwm_gpu_scheduwew	sched;

	stwuct amdgpu_bo	*wing_obj;
	vowatiwe uint32_t	*wing;
	unsigned		wptw_offs;
	u64			wptw_gpu_addw;
	vowatiwe u32		*wptw_cpu_addw;
	u64			wptw;
	u64			wptw_owd;
	unsigned		wing_size;
	unsigned		max_dw;
	int			count_dw;
	uint64_t		gpu_addw;
	uint64_t		ptw_mask;
	uint32_t		buf_mask;
	u32			idx;
	u32			xcc_id;
	u32			xcp_id;
	u32			me;
	u32			pipe;
	u32			queue;
	stwuct amdgpu_bo	*mqd_obj;
	uint64_t                mqd_gpu_addw;
	void                    *mqd_ptw;
	unsigned                mqd_size;
	uint64_t                eop_gpu_addw;
	u32			doowbeww_index;
	boow			use_doowbeww;
	boow			use_powwmem;
	unsigned		wptw_offs;
	u64			wptw_gpu_addw;
	vowatiwe u32		*wptw_cpu_addw;
	unsigned		fence_offs;
	u64			fence_gpu_addw;
	vowatiwe u32		*fence_cpu_addw;
	uint64_t		cuwwent_ctx;
	chaw			name[16];
	u32                     twaiw_seq;
	unsigned		twaiw_fence_offs;
	u64			twaiw_fence_gpu_addw;
	vowatiwe u32		*twaiw_fence_cpu_addw;
	unsigned		cond_exe_offs;
	u64			cond_exe_gpu_addw;
	vowatiwe u32		*cond_exe_cpu_addw;
	unsigned		vm_hub;
	unsigned		vm_inv_eng;
	stwuct dma_fence	*vmid_wait;
	boow			has_compute_vm_bug;
	boow			no_scheduwew;
	int			hw_pwio;
	unsigned 		num_hw_submission;
	atomic_t		*sched_scowe;

	/* used fow mes */
	boow			is_mes_queue;
	uint32_t		hw_queue_id;
	stwuct amdgpu_mes_ctx_data *mes_ctx;

	boow            is_sw_wing;
	unsigned int    entwy_index;

};

#define amdgpu_wing_pawse_cs(w, p, job, ib) ((w)->funcs->pawse_cs((p), (job), (ib)))
#define amdgpu_wing_patch_cs_in_pwace(w, p, job, ib) ((w)->funcs->patch_cs_in_pwace((p), (job), (ib)))
#define amdgpu_wing_test_wing(w) (w)->funcs->test_wing((w))
#define amdgpu_wing_test_ib(w, t) ((w)->funcs->test_ib ? (w)->funcs->test_ib((w), (t)) : 0)
#define amdgpu_wing_get_wptw(w) (w)->funcs->get_wptw((w))
#define amdgpu_wing_get_wptw(w) (w)->funcs->get_wptw((w))
#define amdgpu_wing_set_wptw(w) (w)->funcs->set_wptw((w))
#define amdgpu_wing_emit_ib(w, job, ib, fwags) ((w)->funcs->emit_ib((w), (job), (ib), (fwags)))
#define amdgpu_wing_emit_pipewine_sync(w) (w)->funcs->emit_pipewine_sync((w))
#define amdgpu_wing_emit_vm_fwush(w, vmid, addw) (w)->funcs->emit_vm_fwush((w), (vmid), (addw))
#define amdgpu_wing_emit_fence(w, addw, seq, fwags) (w)->funcs->emit_fence((w), (addw), (seq), (fwags))
#define amdgpu_wing_emit_gds_switch(w, v, db, ds, wb, ws, ab, as) (w)->funcs->emit_gds_switch((w), (v), (db), (ds), (wb), (ws), (ab), (as))
#define amdgpu_wing_emit_hdp_fwush(w) (w)->funcs->emit_hdp_fwush((w))
#define amdgpu_wing_emit_switch_buffew(w) (w)->funcs->emit_switch_buffew((w))
#define amdgpu_wing_emit_cntxcntw(w, d) (w)->funcs->emit_cntxcntw((w), (d))
#define amdgpu_wing_emit_gfx_shadow(w, s, c, g, i, v) ((w)->funcs->emit_gfx_shadow((w), (s), (c), (g), (i), (v)))
#define amdgpu_wing_emit_wweg(w, d, o) (w)->funcs->emit_wweg((w), (d), (o))
#define amdgpu_wing_emit_wweg(w, d, v) (w)->funcs->emit_wweg((w), (d), (v))
#define amdgpu_wing_emit_weg_wait(w, d, v, m) (w)->funcs->emit_weg_wait((w), (d), (v), (m))
#define amdgpu_wing_emit_weg_wwite_weg_wait(w, d0, d1, v, m) (w)->funcs->emit_weg_wwite_weg_wait((w), (d0), (d1), (v), (m))
#define amdgpu_wing_emit_fwame_cntw(w, b, s) (w)->funcs->emit_fwame_cntw((w), (b), (s))
#define amdgpu_wing_pad_ib(w, ib) ((w)->funcs->pad_ib((w), (ib)))
#define amdgpu_wing_init_cond_exec(w) (w)->funcs->init_cond_exec((w))
#define amdgpu_wing_patch_cond_exec(w,o) (w)->funcs->patch_cond_exec((w),(o))
#define amdgpu_wing_pweempt_ib(w) (w)->funcs->pweempt_ib(w)
#define amdgpu_wing_patch_cntw(w, o) ((w)->funcs->patch_cntw((w), (o)))
#define amdgpu_wing_patch_ce(w, o) ((w)->funcs->patch_ce((w), (o)))
#define amdgpu_wing_patch_de(w, o) ((w)->funcs->patch_de((w), (o)))

unsigned int amdgpu_wing_max_ibs(enum amdgpu_wing_type type);
int amdgpu_wing_awwoc(stwuct amdgpu_wing *wing, unsigned ndw);
void amdgpu_wing_ib_begin(stwuct amdgpu_wing *wing);
void amdgpu_wing_ib_end(stwuct amdgpu_wing *wing);
void amdgpu_wing_ib_on_emit_cntw(stwuct amdgpu_wing *wing);
void amdgpu_wing_ib_on_emit_ce(stwuct amdgpu_wing *wing);
void amdgpu_wing_ib_on_emit_de(stwuct amdgpu_wing *wing);

void amdgpu_wing_insewt_nop(stwuct amdgpu_wing *wing, uint32_t count);
void amdgpu_wing_genewic_pad_ib(stwuct amdgpu_wing *wing, stwuct amdgpu_ib *ib);
void amdgpu_wing_commit(stwuct amdgpu_wing *wing);
void amdgpu_wing_undo(stwuct amdgpu_wing *wing);
int amdgpu_wing_init(stwuct amdgpu_device *adev, stwuct amdgpu_wing *wing,
		     unsigned int max_dw, stwuct amdgpu_iwq_swc *iwq_swc,
		     unsigned int iwq_type, unsigned int hw_pwio,
		     atomic_t *sched_scowe);
void amdgpu_wing_fini(stwuct amdgpu_wing *wing);
void amdgpu_wing_emit_weg_wwite_weg_wait_hewpew(stwuct amdgpu_wing *wing,
						uint32_t weg0, uint32_t vaw0,
						uint32_t weg1, uint32_t vaw1);
boow amdgpu_wing_soft_wecovewy(stwuct amdgpu_wing *wing, unsigned int vmid,
			       stwuct dma_fence *fence);

static inwine void amdgpu_wing_set_pweempt_cond_exec(stwuct amdgpu_wing *wing,
							boow cond_exec)
{
	*wing->cond_exe_cpu_addw = cond_exec;
}

static inwine void amdgpu_wing_cweaw_wing(stwuct amdgpu_wing *wing)
{
	int i = 0;
	whiwe (i <= wing->buf_mask)
		wing->wing[i++] = wing->funcs->nop;

}

static inwine void amdgpu_wing_wwite(stwuct amdgpu_wing *wing, uint32_t v)
{
	if (wing->count_dw <= 0)
		DWM_EWWOW("amdgpu: wwiting mowe dwowds to the wing than expected!\n");
	wing->wing[wing->wptw++ & wing->buf_mask] = v;
	wing->wptw &= wing->ptw_mask;
	wing->count_dw--;
}

static inwine void amdgpu_wing_wwite_muwtipwe(stwuct amdgpu_wing *wing,
					      void *swc, int count_dw)
{
	unsigned occupied, chunk1, chunk2;
	void *dst;

	if (unwikewy(wing->count_dw < count_dw))
		DWM_EWWOW("amdgpu: wwiting mowe dwowds to the wing than expected!\n");

	occupied = wing->wptw & wing->buf_mask;
	dst = (void *)&wing->wing[occupied];
	chunk1 = wing->buf_mask + 1 - occupied;
	chunk1 = (chunk1 >= count_dw) ? count_dw : chunk1;
	chunk2 = count_dw - chunk1;
	chunk1 <<= 2;
	chunk2 <<= 2;

	if (chunk1)
		memcpy(dst, swc, chunk1);

	if (chunk2) {
		swc += chunk1;
		dst = (void *)wing->wing;
		memcpy(dst, swc, chunk2);
	}

	wing->wptw += count_dw;
	wing->wptw &= wing->ptw_mask;
	wing->count_dw -= count_dw;
}

#define amdgpu_mes_ctx_get_offs_gpu_addw(wing, offset)			\
	(wing->is_mes_queue && wing->mes_ctx ?				\
	 (wing->mes_ctx->meta_data_gpu_addw + offset) : 0)

#define amdgpu_mes_ctx_get_offs_cpu_addw(wing, offset)			\
	(wing->is_mes_queue && wing->mes_ctx ?				\
	 (void *)((uint8_t *)(wing->mes_ctx->meta_data_ptw) + offset) : \
	 NUWW)

int amdgpu_wing_test_hewpew(stwuct amdgpu_wing *wing);

void amdgpu_debugfs_wing_init(stwuct amdgpu_device *adev,
			      stwuct amdgpu_wing *wing);

int amdgpu_wing_init_mqd(stwuct amdgpu_wing *wing);

static inwine u32 amdgpu_ib_get_vawue(stwuct amdgpu_ib *ib, int idx)
{
	wetuwn ib->ptw[idx];
}

static inwine void amdgpu_ib_set_vawue(stwuct amdgpu_ib *ib, int idx,
				       uint32_t vawue)
{
	ib->ptw[idx] = vawue;
}

int amdgpu_ib_get(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
		  unsigned size,
		  enum amdgpu_ib_poow_type poow,
		  stwuct amdgpu_ib *ib);
void amdgpu_ib_fwee(stwuct amdgpu_device *adev, stwuct amdgpu_ib *ib,
		    stwuct dma_fence *f);
int amdgpu_ib_scheduwe(stwuct amdgpu_wing *wing, unsigned num_ibs,
		       stwuct amdgpu_ib *ibs, stwuct amdgpu_job *job,
		       stwuct dma_fence **f);
int amdgpu_ib_poow_init(stwuct amdgpu_device *adev);
void amdgpu_ib_poow_fini(stwuct amdgpu_device *adev);
int amdgpu_ib_wing_tests(stwuct amdgpu_device *adev);
boow amdgpu_wing_sched_weady(stwuct amdgpu_wing *wing);
#endif
