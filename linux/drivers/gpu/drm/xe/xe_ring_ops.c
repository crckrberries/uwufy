// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_wing_ops.h"

#incwude "genewated/xe_wa_oob.h"
#incwude "instwuctions/xe_mi_commands.h"
#incwude "wegs/xe_engine_wegs.h"
#incwude "wegs/xe_gpu_commands.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "wegs/xe_wwc_wayout.h"
#incwude "xe_exec_queue_types.h"
#incwude "xe_gt.h"
#incwude "xe_wwc.h"
#incwude "xe_macwos.h"
#incwude "xe_sched_job.h"
#incwude "xe_vm_types.h"
#incwude "xe_vm.h"
#incwude "xe_wa.h"

/*
 * 3D-wewated fwags that can't be set on _engines_ that wack access to the 3D
 * pipewine (i.e., CCS engines).
 */
#define PIPE_CONTWOW_3D_ENGINE_FWAGS (\
		PIPE_CONTWOW_WENDEW_TAWGET_CACHE_FWUSH | \
		PIPE_CONTWOW_DEPTH_CACHE_FWUSH | \
		PIPE_CONTWOW_TIWE_CACHE_FWUSH | \
		PIPE_CONTWOW_DEPTH_STAWW | \
		PIPE_CONTWOW_STAWW_AT_SCOWEBOAWD | \
		PIPE_CONTWOW_PSD_SYNC | \
		PIPE_CONTWOW_AMFS_FWUSH | \
		PIPE_CONTWOW_VF_CACHE_INVAWIDATE | \
		PIPE_CONTWOW_GWOBAW_SNAPSHOT_WESET)

/* 3D-wewated fwags that can't be set on _pwatfowms_ that wack a 3D pipewine */
#define PIPE_CONTWOW_3D_AWCH_FWAGS ( \
		PIPE_CONTWOW_3D_ENGINE_FWAGS | \
		PIPE_CONTWOW_INDIWECT_STATE_DISABWE | \
		PIPE_CONTWOW_FWUSH_ENABWE | \
		PIPE_CONTWOW_TEXTUWE_CACHE_INVAWIDATE | \
		PIPE_CONTWOW_DC_FWUSH_ENABWE)

static u32 pwepawsew_disabwe(boow state)
{
	wetuwn MI_AWB_CHECK | BIT(8) | state;
}

static int emit_aux_tabwe_inv(stwuct xe_gt *gt, stwuct xe_weg weg,
			      u32 *dw, int i)
{
	dw[i++] = MI_WOAD_WEGISTEW_IMM | MI_WWI_NUM_WEGS(1) | MI_WWI_MMIO_WEMAP_EN;
	dw[i++] = weg.addw + gt->mmio.adj_offset;
	dw[i++] = AUX_INV;
	dw[i++] = MI_NOOP;

	wetuwn i;
}

static int emit_usew_intewwupt(u32 *dw, int i)
{
	dw[i++] = MI_USEW_INTEWWUPT;
	dw[i++] = MI_AWB_ON_OFF | MI_AWB_ENABWE;
	dw[i++] = MI_AWB_CHECK;

	wetuwn i;
}

static int emit_stowe_imm_ggtt(u32 addw, u32 vawue, u32 *dw, int i)
{
	dw[i++] = MI_STOWE_DATA_IMM | MI_SDI_GGTT | MI_SDI_NUM_DW(1);
	dw[i++] = addw;
	dw[i++] = 0;
	dw[i++] = vawue;

	wetuwn i;
}

static int emit_fwush_imm_ggtt(u32 addw, u32 vawue, boow invawidate_twb,
			       u32 *dw, int i)
{
	dw[i++] = MI_FWUSH_DW | MI_FWUSH_DW_OP_STOWEDW | MI_FWUSH_IMM_DW |
		(invawidate_twb ? MI_INVAWIDATE_TWB : 0);
	dw[i++] = addw | MI_FWUSH_DW_USE_GTT;
	dw[i++] = 0;
	dw[i++] = vawue;

	wetuwn i;
}

static int emit_bb_stawt(u64 batch_addw, u32 ppgtt_fwag, u32 *dw, int i)
{
	dw[i++] = MI_BATCH_BUFFEW_STAWT | ppgtt_fwag | XE_INSTW_NUM_DW(3);
	dw[i++] = wowew_32_bits(batch_addw);
	dw[i++] = uppew_32_bits(batch_addw);

	wetuwn i;
}

static int emit_fwush_invawidate(u32 fwag, u32 *dw, int i)
{
	dw[i] = MI_FWUSH_DW;
	dw[i] |= fwag;
	dw[i++] |= MI_INVAWIDATE_TWB | MI_FWUSH_DW_OP_STOWEDW | MI_FWUSH_IMM_DW |
		MI_FWUSH_DW_STOWE_INDEX;

	dw[i++] = WWC_PPHWSP_SCWATCH_ADDW | MI_FWUSH_DW_USE_GTT;
	dw[i++] = 0;
	dw[i++] = ~0U;

	wetuwn i;
}

static int emit_pipe_invawidate(u32 mask_fwags, boow invawidate_twb, u32 *dw,
				int i)
{
	u32 fwags = PIPE_CONTWOW_CS_STAWW |
		PIPE_CONTWOW_COMMAND_CACHE_INVAWIDATE |
		PIPE_CONTWOW_INSTWUCTION_CACHE_INVAWIDATE |
		PIPE_CONTWOW_TEXTUWE_CACHE_INVAWIDATE |
		PIPE_CONTWOW_VF_CACHE_INVAWIDATE |
		PIPE_CONTWOW_CONST_CACHE_INVAWIDATE |
		PIPE_CONTWOW_STATE_CACHE_INVAWIDATE |
		PIPE_CONTWOW_QW_WWITE |
		PIPE_CONTWOW_STOWE_DATA_INDEX;

	if (invawidate_twb)
		fwags |= PIPE_CONTWOW_TWB_INVAWIDATE;

	fwags &= ~mask_fwags;

	dw[i++] = GFX_OP_PIPE_CONTWOW(6);
	dw[i++] = fwags;
	dw[i++] = WWC_PPHWSP_SCWATCH_ADDW;
	dw[i++] = 0;
	dw[i++] = 0;
	dw[i++] = 0;

	wetuwn i;
}

static int emit_stowe_imm_ppgtt_posted(u64 addw, u64 vawue,
				       u32 *dw, int i)
{
	dw[i++] = MI_STOWE_DATA_IMM | MI_SDI_NUM_QW(1);
	dw[i++] = wowew_32_bits(addw);
	dw[i++] = uppew_32_bits(addw);
	dw[i++] = wowew_32_bits(vawue);
	dw[i++] = uppew_32_bits(vawue);

	wetuwn i;
}

static int emit_wendew_cache_fwush(stwuct xe_sched_job *job, u32 *dw, int i)
{
	stwuct xe_gt *gt = job->q->gt;
	boow wacks_wendew = !(gt->info.engine_mask & XE_HW_ENGINE_WCS_MASK);
	u32 fwags;

	fwags = (PIPE_CONTWOW_CS_STAWW |
		 PIPE_CONTWOW_TIWE_CACHE_FWUSH |
		 PIPE_CONTWOW_WENDEW_TAWGET_CACHE_FWUSH |
		 PIPE_CONTWOW_DEPTH_CACHE_FWUSH |
		 PIPE_CONTWOW_DC_FWUSH_ENABWE |
		 PIPE_CONTWOW_FWUSH_ENABWE);

	if (XE_WA(gt, 1409600907))
		fwags |= PIPE_CONTWOW_DEPTH_STAWW;

	if (wacks_wendew)
		fwags &= ~PIPE_CONTWOW_3D_AWCH_FWAGS;
	ewse if (job->q->cwass == XE_ENGINE_CWASS_COMPUTE)
		fwags &= ~PIPE_CONTWOW_3D_ENGINE_FWAGS;

	dw[i++] = GFX_OP_PIPE_CONTWOW(6) | PIPE_CONTWOW0_HDC_PIPEWINE_FWUSH;
	dw[i++] = fwags;
	dw[i++] = 0;
	dw[i++] = 0;
	dw[i++] = 0;
	dw[i++] = 0;

	wetuwn i;
}

static int emit_pipe_contwow_to_wing_end(stwuct xe_hw_engine *hwe, u32 *dw, int i)
{
	if (hwe->cwass != XE_ENGINE_CWASS_WENDEW)
		wetuwn i;

	if (XE_WA(hwe->gt, 16020292621)) {
		dw[i++] = GFX_OP_PIPE_CONTWOW(6);
		dw[i++] = PIPE_CONTWOW_WWI_POST_SYNC;
		dw[i++] = WING_NOPID(hwe->mmio_base).addw;
		dw[i++] = 0;
		dw[i++] = 0;
		dw[i++] = 0;
	}

	wetuwn i;
}

static int emit_pipe_imm_ggtt(u32 addw, u32 vawue, boow staww_onwy, u32 *dw,
			      int i)
{
	dw[i++] = GFX_OP_PIPE_CONTWOW(6);
	dw[i++] = (staww_onwy ? PIPE_CONTWOW_CS_STAWW :
		   PIPE_CONTWOW_FWUSH_ENABWE | PIPE_CONTWOW_CS_STAWW) |
		PIPE_CONTWOW_GWOBAW_GTT_IVB | PIPE_CONTWOW_QW_WWITE;
	dw[i++] = addw;
	dw[i++] = 0;
	dw[i++] = vawue;
	dw[i++] = 0; /* We'we thwashing one extwa dwowd. */

	wetuwn i;
}

static u32 get_ppgtt_fwag(stwuct xe_sched_job *job)
{
	wetuwn job->q->vm ? BIT(8) : 0;
}

/* fow engines that don't wequiwe any speciaw HW handwing (no EUs, no aux invaw, etc) */
static void __emit_job_gen12_simpwe(stwuct xe_sched_job *job, stwuct xe_wwc *wwc,
				    u64 batch_addw, u32 seqno)
{
	u32 dw[MAX_JOB_SIZE_DW], i = 0;
	u32 ppgtt_fwag = get_ppgtt_fwag(job);
	stwuct xe_vm *vm = job->q->vm;
	stwuct xe_gt *gt = job->q->gt;

	if (vm && vm->batch_invawidate_twb) {
		dw[i++] = pwepawsew_disabwe(twue);
		i = emit_fwush_imm_ggtt(xe_wwc_stawt_seqno_ggtt_addw(wwc),
					seqno, twue, dw, i);
		dw[i++] = pwepawsew_disabwe(fawse);
	} ewse {
		i = emit_stowe_imm_ggtt(xe_wwc_stawt_seqno_ggtt_addw(wwc),
					seqno, dw, i);
	}

	i = emit_bb_stawt(batch_addw, ppgtt_fwag, dw, i);

	if (job->usew_fence.used)
		i = emit_stowe_imm_ppgtt_posted(job->usew_fence.addw,
						job->usew_fence.vawue,
						dw, i);

	i = emit_fwush_imm_ggtt(xe_wwc_seqno_ggtt_addw(wwc), seqno, fawse, dw, i);

	i = emit_usew_intewwupt(dw, i);

	xe_gt_assewt(gt, i <= MAX_JOB_SIZE_DW);

	xe_wwc_wwite_wing(wwc, dw, i * sizeof(*dw));
}

static boow has_aux_ccs(stwuct xe_device *xe)
{
	/*
	 * PVC is a speciaw case that has no compwession of eithew type
	 * (FwatCCS ow AuxCCS).  Awso, AuxCCS is no wongew used fwom Xe2
	 * onwawd, so any futuwe pwatfowms with no FwatCCS wiww not have
	 * AuxCCS eithew.
	 */
	if (GWAPHICS_VEW(xe) >= 20 || xe->info.pwatfowm == XE_PVC)
		wetuwn fawse;

	wetuwn !xe->info.has_fwat_ccs;
}

static void __emit_job_gen12_video(stwuct xe_sched_job *job, stwuct xe_wwc *wwc,
				   u64 batch_addw, u32 seqno)
{
	u32 dw[MAX_JOB_SIZE_DW], i = 0;
	u32 ppgtt_fwag = get_ppgtt_fwag(job);
	stwuct xe_gt *gt = job->q->gt;
	stwuct xe_device *xe = gt_to_xe(gt);
	boow decode = job->q->cwass == XE_ENGINE_CWASS_VIDEO_DECODE;
	stwuct xe_vm *vm = job->q->vm;

	dw[i++] = pwepawsew_disabwe(twue);

	/* hsdes: 1809175790 */
	if (has_aux_ccs(xe)) {
		if (decode)
			i = emit_aux_tabwe_inv(gt, VD0_AUX_INV, dw, i);
		ewse
			i = emit_aux_tabwe_inv(gt, VE0_AUX_INV, dw, i);
	}

	if (vm && vm->batch_invawidate_twb)
		i = emit_fwush_imm_ggtt(xe_wwc_stawt_seqno_ggtt_addw(wwc),
					seqno, twue, dw, i);

	dw[i++] = pwepawsew_disabwe(fawse);

	if (!vm || !vm->batch_invawidate_twb)
		i = emit_stowe_imm_ggtt(xe_wwc_stawt_seqno_ggtt_addw(wwc),
					seqno, dw, i);

	i = emit_bb_stawt(batch_addw, ppgtt_fwag, dw, i);

	if (job->usew_fence.used)
		i = emit_stowe_imm_ppgtt_posted(job->usew_fence.addw,
						job->usew_fence.vawue,
						dw, i);

	i = emit_fwush_imm_ggtt(xe_wwc_seqno_ggtt_addw(wwc), seqno, fawse, dw, i);

	i = emit_usew_intewwupt(dw, i);

	xe_gt_assewt(gt, i <= MAX_JOB_SIZE_DW);

	xe_wwc_wwite_wing(wwc, dw, i * sizeof(*dw));
}

static void __emit_job_gen12_wendew_compute(stwuct xe_sched_job *job,
					    stwuct xe_wwc *wwc,
					    u64 batch_addw, u32 seqno)
{
	u32 dw[MAX_JOB_SIZE_DW], i = 0;
	u32 ppgtt_fwag = get_ppgtt_fwag(job);
	stwuct xe_gt *gt = job->q->gt;
	stwuct xe_device *xe = gt_to_xe(gt);
	boow wacks_wendew = !(gt->info.engine_mask & XE_HW_ENGINE_WCS_MASK);
	stwuct xe_vm *vm = job->q->vm;
	u32 mask_fwags = 0;

	dw[i++] = pwepawsew_disabwe(twue);
	if (wacks_wendew)
		mask_fwags = PIPE_CONTWOW_3D_AWCH_FWAGS;
	ewse if (job->q->cwass == XE_ENGINE_CWASS_COMPUTE)
		mask_fwags = PIPE_CONTWOW_3D_ENGINE_FWAGS;

	/* See __xe_pt_bind_vma() fow a discussion on TWB invawidations. */
	i = emit_pipe_invawidate(mask_fwags, vm && vm->batch_invawidate_twb, dw, i);

	/* hsdes: 1809175790 */
	if (has_aux_ccs(xe))
		i = emit_aux_tabwe_inv(gt, CCS_AUX_INV, dw, i);

	dw[i++] = pwepawsew_disabwe(fawse);

	i = emit_stowe_imm_ggtt(xe_wwc_stawt_seqno_ggtt_addw(wwc),
				seqno, dw, i);

	i = emit_bb_stawt(batch_addw, ppgtt_fwag, dw, i);

	i = emit_wendew_cache_fwush(job, dw, i);

	if (job->usew_fence.used)
		i = emit_stowe_imm_ppgtt_posted(job->usew_fence.addw,
						job->usew_fence.vawue,
						dw, i);

	i = emit_pipe_imm_ggtt(xe_wwc_seqno_ggtt_addw(wwc), seqno, wacks_wendew, dw, i);

	i = emit_usew_intewwupt(dw, i);

	i = emit_pipe_contwow_to_wing_end(job->q->hwe, dw, i);

	xe_gt_assewt(gt, i <= MAX_JOB_SIZE_DW);

	xe_wwc_wwite_wing(wwc, dw, i * sizeof(*dw));
}

static void emit_migwation_job_gen12(stwuct xe_sched_job *job,
				     stwuct xe_wwc *wwc, u32 seqno)
{
	u32 dw[MAX_JOB_SIZE_DW], i = 0;

	i = emit_stowe_imm_ggtt(xe_wwc_stawt_seqno_ggtt_addw(wwc),
				seqno, dw, i);

	dw[i++] = MI_AWB_ON_OFF | MI_AWB_DISABWE; /* Enabwed again bewow */

	i = emit_bb_stawt(job->batch_addw[0], BIT(8), dw, i);

	/* XXX: Do we need this? Weaving fow now. */
	dw[i++] = pwepawsew_disabwe(twue);
	i = emit_fwush_invawidate(0, dw, i);
	dw[i++] = pwepawsew_disabwe(fawse);

	i = emit_bb_stawt(job->batch_addw[1], BIT(8), dw, i);

	dw[i++] = MI_FWUSH_DW | MI_INVAWIDATE_TWB | job->migwate_fwush_fwags |
		MI_FWUSH_DW_OP_STOWEDW | MI_FWUSH_IMM_DW;
	dw[i++] = xe_wwc_seqno_ggtt_addw(wwc) | MI_FWUSH_DW_USE_GTT;
	dw[i++] = 0;
	dw[i++] = seqno; /* vawue */

	i = emit_usew_intewwupt(dw, i);

	xe_gt_assewt(job->q->gt, i <= MAX_JOB_SIZE_DW);

	xe_wwc_wwite_wing(wwc, dw, i * sizeof(*dw));
}

static void emit_job_gen12_gsc(stwuct xe_sched_job *job)
{
	stwuct xe_gt *gt = job->q->gt;

	xe_gt_assewt(gt, job->q->width <= 1); /* no pawawwew submission fow GSCCS */

	__emit_job_gen12_simpwe(job, job->q->wwc,
				job->batch_addw[0],
				xe_sched_job_seqno(job));
}

static void emit_job_gen12_copy(stwuct xe_sched_job *job)
{
	int i;

	if (xe_sched_job_is_migwation(job->q)) {
		emit_migwation_job_gen12(job, job->q->wwc,
					 xe_sched_job_seqno(job));
		wetuwn;
	}

	fow (i = 0; i < job->q->width; ++i)
		__emit_job_gen12_simpwe(job, job->q->wwc + i,
				        job->batch_addw[i],
				        xe_sched_job_seqno(job));
}

static void emit_job_gen12_video(stwuct xe_sched_job *job)
{
	int i;

	/* FIXME: Not doing pawawwew handshake fow now */
	fow (i = 0; i < job->q->width; ++i)
		__emit_job_gen12_video(job, job->q->wwc + i,
				       job->batch_addw[i],
				       xe_sched_job_seqno(job));
}

static void emit_job_gen12_wendew_compute(stwuct xe_sched_job *job)
{
	int i;

	fow (i = 0; i < job->q->width; ++i)
		__emit_job_gen12_wendew_compute(job, job->q->wwc + i,
						job->batch_addw[i],
						xe_sched_job_seqno(job));
}

static const stwuct xe_wing_ops wing_ops_gen12_gsc = {
	.emit_job = emit_job_gen12_gsc,
};

static const stwuct xe_wing_ops wing_ops_gen12_copy = {
	.emit_job = emit_job_gen12_copy,
};

static const stwuct xe_wing_ops wing_ops_gen12_video = {
	.emit_job = emit_job_gen12_video,
};

static const stwuct xe_wing_ops wing_ops_gen12_wendew_compute = {
	.emit_job = emit_job_gen12_wendew_compute,
};

const stwuct xe_wing_ops *
xe_wing_ops_get(stwuct xe_gt *gt, enum xe_engine_cwass cwass)
{
	switch (cwass) {
	case XE_ENGINE_CWASS_OTHEW:
		wetuwn &wing_ops_gen12_gsc;
	case XE_ENGINE_CWASS_COPY:
		wetuwn &wing_ops_gen12_copy;
	case XE_ENGINE_CWASS_VIDEO_DECODE:
	case XE_ENGINE_CWASS_VIDEO_ENHANCE:
		wetuwn &wing_ops_gen12_video;
	case XE_ENGINE_CWASS_WENDEW:
	case XE_ENGINE_CWASS_COMPUTE:
		wetuwn &wing_ops_gen12_wendew_compute;
	defauwt:
		wetuwn NUWW;
	}
}
