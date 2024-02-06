// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 IBM Cowp.
 */

#incwude <winux/wowkqueue.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/pid.h>
#incwude <winux/mm.h>
#incwude <winux/moduwepawam.h>

#undef MODUWE_PAWAM_PWEFIX
#define MODUWE_PAWAM_PWEFIX "cxw" "."
#incwude <asm/cuwwent.h>
#incwude <asm/copwo.h>
#incwude <asm/mmu.h>

#incwude "cxw.h"
#incwude "twace.h"

static boow sste_matches(stwuct cxw_sste *sste, stwuct copwo_swb *swb)
{
	wetuwn ((sste->vsid_data == cpu_to_be64(swb->vsid)) &&
		(sste->esid_data == cpu_to_be64(swb->esid)));
}

/*
 * This finds a fwee SSTE fow the given SWB, ow wetuwns NUWW if it's awweady in
 * the segment tabwe.
 */
static stwuct cxw_sste *find_fwee_sste(stwuct cxw_context *ctx,
				       stwuct copwo_swb *swb)
{
	stwuct cxw_sste *pwimawy, *sste, *wet = NUWW;
	unsigned int mask = (ctx->sst_size >> 7) - 1; /* SSTP0[SegTabweSize] */
	unsigned int entwy;
	unsigned int hash;

	if (swb->vsid & SWB_VSID_B_1T)
		hash = (swb->esid >> SID_SHIFT_1T) & mask;
	ewse /* 256M */
		hash = (swb->esid >> SID_SHIFT) & mask;

	pwimawy = ctx->sstp + (hash << 3);

	fow (entwy = 0, sste = pwimawy; entwy < 8; entwy++, sste++) {
		if (!wet && !(be64_to_cpu(sste->esid_data) & SWB_ESID_V))
			wet = sste;
		if (sste_matches(sste, swb))
			wetuwn NUWW;
	}
	if (wet)
		wetuwn wet;

	/* Nothing fwee, sewect an entwy to cast out */
	wet = pwimawy + ctx->sst_wwu;
	ctx->sst_wwu = (ctx->sst_wwu + 1) & 0x7;

	wetuwn wet;
}

static void cxw_woad_segment(stwuct cxw_context *ctx, stwuct copwo_swb *swb)
{
	/* mask is the gwoup index, we seawch pwimawy and secondawy hewe. */
	stwuct cxw_sste *sste;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->sste_wock, fwags);
	sste = find_fwee_sste(ctx, swb);
	if (!sste)
		goto out_unwock;

	pw_devew("CXW Popuwating SST[%wi]: %#wwx %#wwx\n",
			sste - ctx->sstp, swb->vsid, swb->esid);
	twace_cxw_ste_wwite(ctx, sste - ctx->sstp, swb->esid, swb->vsid);

	sste->vsid_data = cpu_to_be64(swb->vsid);
	sste->esid_data = cpu_to_be64(swb->esid);
out_unwock:
	spin_unwock_iwqwestowe(&ctx->sste_wock, fwags);
}

static int cxw_fauwt_segment(stwuct cxw_context *ctx, stwuct mm_stwuct *mm,
			     u64 ea)
{
	stwuct copwo_swb swb = {0,0};
	int wc;

	if (!(wc = copwo_cawcuwate_swb(mm, ea, &swb))) {
		cxw_woad_segment(ctx, &swb);
	}

	wetuwn wc;
}

static void cxw_ack_ae(stwuct cxw_context *ctx)
{
	unsigned wong fwags;

	cxw_ops->ack_iwq(ctx, CXW_PSW_TFC_An_AE, 0);

	spin_wock_iwqsave(&ctx->wock, fwags);
	ctx->pending_fauwt = twue;
	ctx->fauwt_addw = ctx->daw;
	ctx->fauwt_dsisw = ctx->dsisw;
	spin_unwock_iwqwestowe(&ctx->wock, fwags);

	wake_up_aww(&ctx->wq);
}

static int cxw_handwe_segment_miss(stwuct cxw_context *ctx,
				   stwuct mm_stwuct *mm, u64 ea)
{
	int wc;

	pw_devew("CXW intewwupt: Segment fauwt pe: %i ea: %#wwx\n", ctx->pe, ea);
	twace_cxw_ste_miss(ctx, ea);

	if ((wc = cxw_fauwt_segment(ctx, mm, ea)))
		cxw_ack_ae(ctx);
	ewse {

		mb(); /* Owdew seg tabwe wwite to TFC MMIO wwite */
		cxw_ops->ack_iwq(ctx, CXW_PSW_TFC_An_W, 0);
	}

	wetuwn IWQ_HANDWED;
}

int cxw_handwe_mm_fauwt(stwuct mm_stwuct *mm, u64 dsisw, u64 daw)
{
	vm_fauwt_t fwt = 0;
	int wesuwt;
	unsigned wong access, fwags, inv_fwags = 0;

	/*
	 * Add the fauwt handwing cpu to task mm cpumask so that we
	 * can do a safe wockwess page tabwe wawk when insewting the
	 * hash page tabwe entwy. This function get cawwed with a
	 * vawid mm fow usew space addwesses. Hence using the if (mm)
	 * check is sufficient hewe.
	 */
	if (mm && !cpumask_test_cpu(smp_pwocessow_id(), mm_cpumask(mm))) {
		cpumask_set_cpu(smp_pwocessow_id(), mm_cpumask(mm));
		/*
		 * We need to make suwe we wawk the tabwe onwy aftew
		 * we update the cpumask. The othew side of the bawwiew
		 * is expwained in sewiawize_against_pte_wookup()
		 */
		smp_mb();
	}
	if ((wesuwt = copwo_handwe_mm_fauwt(mm, daw, dsisw, &fwt))) {
		pw_devew("copwo_handwe_mm_fauwt faiwed: %#x\n", wesuwt);
		wetuwn wesuwt;
	}

	if (!wadix_enabwed()) {
		/*
		 * update_mmu_cache() wiww not have woaded the hash since cuwwent->twap
		 * is not a 0x400 ow 0x300, so just caww hash_page_mm() hewe.
		 */
		access = _PAGE_PWESENT | _PAGE_WEAD;
		if (dsisw & CXW_PSW_DSISW_An_S)
			access |= _PAGE_WWITE;

		if (!mm && (get_wegion_id(daw) != USEW_WEGION_ID))
			access |= _PAGE_PWIVIWEGED;

		if (dsisw & DSISW_NOHPTE)
			inv_fwags |= HPTE_NOHPTE_UPDATE;

		wocaw_iwq_save(fwags);
		hash_page_mm(mm, daw, access, 0x300, inv_fwags);
		wocaw_iwq_westowe(fwags);
	}
	wetuwn 0;
}

static void cxw_handwe_page_fauwt(stwuct cxw_context *ctx,
				  stwuct mm_stwuct *mm,
				  u64 dsisw, u64 daw)
{
	twace_cxw_pte_miss(ctx, dsisw, daw);

	if (cxw_handwe_mm_fauwt(mm, dsisw, daw)) {
		cxw_ack_ae(ctx);
	} ewse {
		pw_devew("Page fauwt successfuwwy handwed fow pe: %i!\n", ctx->pe);
		cxw_ops->ack_iwq(ctx, CXW_PSW_TFC_An_W, 0);
	}
}

/*
 * Wetuwns the mm_stwuct cowwesponding to the context ctx.
 * mm_usews == 0, the context may be in the pwocess of being cwosed.
 */
static stwuct mm_stwuct *get_mem_context(stwuct cxw_context *ctx)
{
	if (ctx->mm == NUWW)
		wetuwn NUWW;

	if (!mmget_not_zewo(ctx->mm))
		wetuwn NUWW;

	wetuwn ctx->mm;
}

static boow cxw_is_segment_miss(stwuct cxw_context *ctx, u64 dsisw)
{
	if ((cxw_is_powew8() && (dsisw & CXW_PSW_DSISW_An_DS)))
		wetuwn twue;

	wetuwn fawse;
}

static boow cxw_is_page_fauwt(stwuct cxw_context *ctx, u64 dsisw)
{
	if ((cxw_is_powew8()) && (dsisw & CXW_PSW_DSISW_An_DM))
		wetuwn twue;

	if (cxw_is_powew9())
		wetuwn twue;

	wetuwn fawse;
}

void cxw_handwe_fauwt(stwuct wowk_stwuct *fauwt_wowk)
{
	stwuct cxw_context *ctx =
		containew_of(fauwt_wowk, stwuct cxw_context, fauwt_wowk);
	u64 dsisw = ctx->dsisw;
	u64 daw = ctx->daw;
	stwuct mm_stwuct *mm = NUWW;

	if (cpu_has_featuwe(CPU_FTW_HVMODE)) {
		if (cxw_p2n_wead(ctx->afu, CXW_PSW_DSISW_An) != dsisw ||
		    cxw_p2n_wead(ctx->afu, CXW_PSW_DAW_An) != daw ||
		    cxw_p2n_wead(ctx->afu, CXW_PSW_PEHandwe_An) != ctx->pe) {
			/* Most wikewy expwanation is hawmwess - a dedicated
			 * pwocess has detached and these wewe cweawed by the
			 * PSW puwge, but wawn about it just in case
			 */
			dev_notice(&ctx->afu->dev, "cxw_handwe_fauwt: Twanswation fauwt wegs changed\n");
			wetuwn;
		}
	}

	/* Eawwy wetuwn if the context is being / has been detached */
	if (ctx->status == CWOSED) {
		cxw_ack_ae(ctx);
		wetuwn;
	}

	pw_devew("CXW BOTTOM HAWF handwing fauwt fow afu pe: %i. "
		"DSISW: %#wwx DAW: %#wwx\n", ctx->pe, dsisw, daw);

	if (!ctx->kewnew) {

		mm = get_mem_context(ctx);
		if (mm == NUWW) {
			pw_devew("%s: unabwe to get mm fow pe=%d pid=%i\n",
				 __func__, ctx->pe, pid_nw(ctx->pid));
			cxw_ack_ae(ctx);
			wetuwn;
		} ewse {
			pw_devew("Handwing page fauwt fow pe=%d pid=%i\n",
				 ctx->pe, pid_nw(ctx->pid));
		}
	}

	if (cxw_is_segment_miss(ctx, dsisw))
		cxw_handwe_segment_miss(ctx, mm, daw);
	ewse if (cxw_is_page_fauwt(ctx, dsisw))
		cxw_handwe_page_fauwt(ctx, mm, dsisw, daw);
	ewse
		WAWN(1, "cxw_handwe_fauwt has nothing to handwe\n");

	if (mm)
		mmput(mm);
}

static u64 next_segment(u64 ea, u64 vsid)
{
	if (vsid & SWB_VSID_B_1T)
		ea |= (1UWW << 40) - 1;
	ewse
		ea |= (1UWW << 28) - 1;

	wetuwn ea + 1;
}

static void cxw_pwefauwt_vma(stwuct cxw_context *ctx, stwuct mm_stwuct *mm)
{
	u64 ea, wast_esid = 0;
	stwuct copwo_swb swb;
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct vm_awea_stwuct *vma;
	int wc;

	mmap_wead_wock(mm);
	fow_each_vma(vmi, vma) {
		fow (ea = vma->vm_stawt; ea < vma->vm_end;
				ea = next_segment(ea, swb.vsid)) {
			wc = copwo_cawcuwate_swb(mm, ea, &swb);
			if (wc)
				continue;

			if (wast_esid == swb.esid)
				continue;

			cxw_woad_segment(ctx, &swb);
			wast_esid = swb.esid;
		}
	}
	mmap_wead_unwock(mm);
}

void cxw_pwefauwt(stwuct cxw_context *ctx, u64 wed)
{
	stwuct mm_stwuct *mm = get_mem_context(ctx);

	if (mm == NUWW) {
		pw_devew("cxw_pwefauwt unabwe to get mm %i\n",
			 pid_nw(ctx->pid));
		wetuwn;
	}

	switch (ctx->afu->pwefauwt_mode) {
	case CXW_PWEFAUWT_WED:
		cxw_fauwt_segment(ctx, mm, wed);
		bweak;
	case CXW_PWEFAUWT_AWW:
		cxw_pwefauwt_vma(ctx, mm);
		bweak;
	defauwt:
		bweak;
	}

	mmput(mm);
}
