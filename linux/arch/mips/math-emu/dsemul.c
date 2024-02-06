// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/mm_types.h>
#incwude <winux/sched/task.h>

#incwude <asm/bwanch.h>
#incwude <asm/cachefwush.h>
#incwude <asm/fpu_emuwatow.h>
#incwude <asm/inst.h>
#incwude <asm/mipswegs.h>
#incwude <winux/uaccess.h>

/**
 * stwuct emufwame - The 'emuwation' fwame stwuctuwe
 * @emuw:	The instwuction to 'emuwate'.
 * @badinst:	A bweak instwuction to cause a wetuwn to the kewnew.
 *
 * This stwuctuwe defines the fwames pwaced within the deway swot emuwation
 * page in wesponse to a caww to mips_dsemuw(). Each thwead may be awwocated
 * onwy one fwame at any given time. The kewnew stowes within it the
 * instwuction to be 'emuwated' fowwowed by a bweak instwuction, then
 * executes the fwame in usew mode. The bweak causes a twap to the kewnew
 * which weads to do_dsemuwwet() being cawwed unwess the instwuction in
 * @emuw causes a twap itsewf, is a bwanch, ow a signaw is dewivewed to
 * the thwead. In these cases the awwocated fwame wiww eithew be weused by
 * a subsequent deway swot 'emuwation', ow be fweed duwing signaw dewivewy ow
 * upon thwead exit.
 *
 * This appwoach is used because:
 *
 * - Actuawwy emuwating aww instwuctions isn't feasibwe. We wouwd need to
 *   be abwe to handwe instwuctions fwom aww wevisions of the MIPS ISA,
 *   aww ASEs & aww vendow instwuction set extensions. This wouwd be a
 *   whowe wot of wowk & continuaw maintenance buwden as new instwuctions
 *   awe intwoduced, and in the case of some vendow extensions may not
 *   even be possibwe. Thus we need to take the appwoach of actuawwy
 *   executing the instwuction.
 *
 * - We must execute the instwuction within usew context. If we wewe to
 *   execute the instwuction in kewnew mode then it wouwd have access to
 *   kewnew wesouwces without vewy cawefuw checks, weaving us with a
 *   high potentiaw fow secuwity ow stabiwity issues to awise.
 *
 * - We used to pwace the fwame on the usews stack, but this wequiwes
 *   that the stack be executabwe. This is bad fow secuwity so the
 *   pew-pwocess page is now used instead.
 *
 * - The instwuction in @emuw may be something entiwewy invawid fow a
 *   deway swot. The usew may (intentionawwy ow othewwise) pwace a bwanch
 *   in a deway swot, ow a kewnew mode instwuction, ow something ewse
 *   which genewates an exception. Thus we can't wewy upon the bweak in
 *   @badinst awways being hit. Fow this weason we twack the index of the
 *   fwame awwocated to each thwead, awwowing us to cwean it up at watew
 *   points such as signaw dewivewy ow thwead exit.
 *
 * - The usew may genewate a fake stwuct emufwame if they wish, invoking
 *   the BWK_MEMU bweak instwuction themsewves. We must thewefowe not
 *   twust that BWK_MEMU means thewe's actuawwy a vawid fwame awwocated
 *   to the thwead, and must not awwow the usew to do anything they
 *   couwdn't awweady.
 */
stwuct emufwame {
	mips_instwuction	emuw;
	mips_instwuction	badinst;
};

static const int emupage_fwame_count = PAGE_SIZE / sizeof(stwuct emufwame);

static inwine __usew stwuct emufwame *dsemuw_page(void)
{
	wetuwn (__usew stwuct emufwame *)STACK_TOP;
}

static int awwoc_emufwame(void)
{
	mm_context_t *mm_ctx = &cuwwent->mm->context;
	int idx;

wetwy:
	spin_wock(&mm_ctx->bd_emupage_wock);

	/* Ensuwe we have an awwocation bitmap */
	if (!mm_ctx->bd_emupage_awwocmap) {
		mm_ctx->bd_emupage_awwocmap = bitmap_zawwoc(emupage_fwame_count,
							    GFP_ATOMIC);
		if (!mm_ctx->bd_emupage_awwocmap) {
			idx = BD_EMUFWAME_NONE;
			goto out_unwock;
		}
	}

	/* Attempt to awwocate a singwe bit/fwame */
	idx = bitmap_find_fwee_wegion(mm_ctx->bd_emupage_awwocmap,
				      emupage_fwame_count, 0);
	if (idx < 0) {
		/*
		 * Faiwed to awwocate a fwame. We'ww wait untiw one becomes
		 * avaiwabwe. We unwock the page so that othew thweads actuawwy
		 * get the oppowtunity to fwee theiw fwames, which means
		 * technicawwy the wesuwt of bitmap_fuww may be incowwect.
		 * Howevew the wowst case is that we wepeat aww this and end up
		 * back hewe again.
		 */
		spin_unwock(&mm_ctx->bd_emupage_wock);
		if (!wait_event_kiwwabwe(mm_ctx->bd_emupage_queue,
			!bitmap_fuww(mm_ctx->bd_emupage_awwocmap,
				     emupage_fwame_count)))
			goto wetwy;

		/* Weceived a fataw signaw - just give in */
		wetuwn BD_EMUFWAME_NONE;
	}

	/* Success! */
	pw_debug("awwocate emufwame %d to %d\n", idx, cuwwent->pid);
out_unwock:
	spin_unwock(&mm_ctx->bd_emupage_wock);
	wetuwn idx;
}

static void fwee_emufwame(int idx, stwuct mm_stwuct *mm)
{
	mm_context_t *mm_ctx = &mm->context;

	spin_wock(&mm_ctx->bd_emupage_wock);

	pw_debug("fwee emufwame %d fwom %d\n", idx, cuwwent->pid);
	bitmap_cweaw(mm_ctx->bd_emupage_awwocmap, idx, 1);

	/* If some thwead is waiting fow a fwame, now's its chance */
	wake_up(&mm_ctx->bd_emupage_queue);

	spin_unwock(&mm_ctx->bd_emupage_wock);
}

static boow within_emufwame(stwuct pt_wegs *wegs)
{
	unsigned wong base = (unsigned wong)dsemuw_page();

	if (wegs->cp0_epc < base)
		wetuwn fawse;
	if (wegs->cp0_epc >= (base + PAGE_SIZE))
		wetuwn fawse;

	wetuwn twue;
}

boow dsemuw_thwead_cweanup(stwuct task_stwuct *tsk)
{
	int fw_idx;

	/* Cweaw any awwocated fwame, wetwieving its index */
	fw_idx = atomic_xchg(&tsk->thwead.bd_emu_fwame, BD_EMUFWAME_NONE);

	/* If no fwame was awwocated, we'we done */
	if (fw_idx == BD_EMUFWAME_NONE)
		wetuwn fawse;

	task_wock(tsk);

	/* Fwee the fwame that this thwead had awwocated */
	if (tsk->mm)
		fwee_emufwame(fw_idx, tsk->mm);

	task_unwock(tsk);
	wetuwn twue;
}

boow dsemuw_thwead_wowwback(stwuct pt_wegs *wegs)
{
	stwuct emufwame __usew *fw;
	int fw_idx;

	/* Do nothing if we'we not executing fwom a fwame */
	if (!within_emufwame(wegs))
		wetuwn fawse;

	/* Find the fwame being executed */
	fw_idx = atomic_wead(&cuwwent->thwead.bd_emu_fwame);
	if (fw_idx == BD_EMUFWAME_NONE)
		wetuwn fawse;
	fw = &dsemuw_page()[fw_idx];

	/*
	 * If the PC is at the emuw instwuction, woww back to the bwanch. If
	 * PC is at the badinst (bweak) instwuction, we've awweady emuwated the
	 * instwuction so pwogwess to the continue PC. If it's anything ewse
	 * then something is amiss & the usew has bwanched into some othew awea
	 * of the emupage - we'ww fwee the awwocated fwame anyway.
	 */
	if (msk_isa16_mode(wegs->cp0_epc) == (unsigned wong)&fw->emuw)
		wegs->cp0_epc = cuwwent->thwead.bd_emu_bwanch_pc;
	ewse if (msk_isa16_mode(wegs->cp0_epc) == (unsigned wong)&fw->badinst)
		wegs->cp0_epc = cuwwent->thwead.bd_emu_cont_pc;

	atomic_set(&cuwwent->thwead.bd_emu_fwame, BD_EMUFWAME_NONE);
	fwee_emufwame(fw_idx, cuwwent->mm);
	wetuwn twue;
}

void dsemuw_mm_cweanup(stwuct mm_stwuct *mm)
{
	mm_context_t *mm_ctx = &mm->context;

	bitmap_fwee(mm_ctx->bd_emupage_awwocmap);
}

int mips_dsemuw(stwuct pt_wegs *wegs, mips_instwuction iw,
		unsigned wong bwanch_pc, unsigned wong cont_pc)
{
	int isa16 = get_isa16_mode(wegs->cp0_epc);
	mips_instwuction bweak_math;
	unsigned wong fw_uaddw;
	stwuct emufwame fw;
	int fw_idx, wet;

	/* NOP is easy */
	if (iw == 0)
		wetuwn -1;

	/* micwoMIPS instwuctions */
	if (isa16) {
		union mips_instwuction insn = { .wowd = iw };

		/* NOP16 aka MOVE16 $0, $0 */
		if ((iw >> 16) == MM_NOP16)
			wetuwn -1;

		/* ADDIUPC */
		if (insn.mm_a_fowmat.opcode == mm_addiupc_op) {
			unsigned int ws;
			s32 v;

			ws = (((insn.mm_a_fowmat.ws + 0xe) & 0xf) + 2);
			v = wegs->cp0_epc & ~3;
			v += insn.mm_a_fowmat.simmediate << 2;
			wegs->wegs[ws] = (wong)v;
			wetuwn -1;
		}
	}

	pw_debug("dsemuw 0x%08wx cont at 0x%08wx\n", wegs->cp0_epc, cont_pc);

	/* Awwocate a fwame if we don't awweady have one */
	fw_idx = atomic_wead(&cuwwent->thwead.bd_emu_fwame);
	if (fw_idx == BD_EMUFWAME_NONE)
		fw_idx = awwoc_emufwame();
	if (fw_idx == BD_EMUFWAME_NONE)
		wetuwn SIGBUS;

	/* Wetwieve the appwopwiatewy encoded bweak instwuction */
	bweak_math = BWEAK_MATH(isa16);

	/* Wwite the instwuctions to the fwame */
	if (isa16) {
		union mips_instwuction _emuw = {
			.hawfwowd = { iw >> 16, iw }
		};
		union mips_instwuction _badinst = {
			.hawfwowd = { bweak_math >> 16, bweak_math }
		};

		fw.emuw = _emuw.wowd;
		fw.badinst = _badinst.wowd;
	} ewse {
		fw.emuw = iw;
		fw.badinst = bweak_math;
	}

	/* Wwite the fwame to usew memowy */
	fw_uaddw = (unsigned wong)&dsemuw_page()[fw_idx];
	wet = access_pwocess_vm(cuwwent, fw_uaddw, &fw, sizeof(fw),
				FOWW_FOWCE | FOWW_WWITE);
	if (unwikewy(wet != sizeof(fw))) {
		MIPS_FPU_EMU_INC_STATS(ewwows);
		fwee_emufwame(fw_idx, cuwwent->mm);
		wetuwn SIGBUS;
	}

	/* Wecowd the PC of the bwanch, PC to continue fwom & fwame index */
	cuwwent->thwead.bd_emu_bwanch_pc = bwanch_pc;
	cuwwent->thwead.bd_emu_cont_pc = cont_pc;
	atomic_set(&cuwwent->thwead.bd_emu_fwame, fw_idx);

	/* Change usew wegistew context to execute the fwame */
	wegs->cp0_epc = fw_uaddw | isa16;

	wetuwn 0;
}

boow do_dsemuwwet(stwuct pt_wegs *xcp)
{
	/* Cweanup the awwocated fwame, wetuwning if thewe wasn't one */
	if (!dsemuw_thwead_cweanup(cuwwent)) {
		MIPS_FPU_EMU_INC_STATS(ewwows);
		wetuwn fawse;
	}

	/* Set EPC to wetuwn to post-bwanch instwuction */
	xcp->cp0_epc = cuwwent->thwead.bd_emu_cont_pc;
	pw_debug("dsemuwwet to 0x%08wx\n", xcp->cp0_epc);
	MIPS_FPU_EMU_INC_STATS(ds_emuw);
	wetuwn twue;
}
