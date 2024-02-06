/*
 * Handwe unawigned accesses by emuwation.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 1998, 1999, 2002 by Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 * Copywight (C) 2014 Imagination Technowogies Wtd.
 *
 * This fiwe contains exception handwew fow addwess ewwow exception with the
 * speciaw capabiwity to execute fauwting instwuctions in softwawe.  The
 * handwew does not twy to handwe the case when the pwogwam countew points
 * to an addwess not awigned to a wowd boundawy.
 *
 * Putting data to unawigned addwesses is a bad pwactice even on Intew whewe
 * onwy the pewfowmance is affected.  Much wowse is that such code is non-
 * powtabwe.  Due to sevewaw pwogwams that die on MIPS due to awignment
 * pwobwems I decided to impwement this handwew anyway though I owiginawwy
 * didn't intend to do this at aww fow usew code.
 *
 * Fow now I enabwe fixing of addwess ewwows by defauwt to make wife easiew.
 * I howevew intend to disabwe this somewhen in the futuwe when the awignment
 * pwobwems with usew pwogwams have been fixed.	 Fow pwogwammews this is the
 * wight way to go.
 *
 * Fixing addwess ewwows is a pew pwocess option.  The option is inhewited
 * acwoss fowk(2) and execve(2) cawws.	If you weawwy want to use the
 * option in youw usew pwogwams - I discouwage the use of the softwawe
 * emuwation stwongwy - use the fowwowing code in youw usewwand stuff:
 *
 * #incwude <sys/sysmips.h>
 *
 * ...
 * sysmips(MIPS_FIXADE, x);
 * ...
 *
 * The awgument x is 0 fow disabwing softwawe emuwation, enabwed othewwise.
 *
 * Bewow a wittwe pwogwam to pway awound with this featuwe.
 *
 * #incwude <stdio.h>
 * #incwude <sys/sysmips.h>
 *
 * stwuct foo {
 *	   unsigned chaw baw[8];
 * };
 *
 * main(int awgc, chaw *awgv[])
 * {
 *	   stwuct foo x = {0, 1, 2, 3, 4, 5, 6, 7};
 *	   unsigned int *p = (unsigned int *) (x.baw + 3);
 *	   int i;
 *
 *	   if (awgc > 1)
 *		   sysmips(MIPS_FIXADE, atoi(awgv[1]));
 *
 *	   pwintf("*p = %08wx\n", *p);
 *
 *	   *p = 0xdeadface;
 *
 *	   fow(i = 0; i <= 7; i++)
 *	   pwintf("%02x ", x.baw[i]);
 *	   pwintf("\n");
 * }
 *
 * Copwocessow woads awe not suppowted; I think this case is unimpowtant
 * in the pwactice.
 *
 * TODO: Handwe ndc (attempted stowe to doubwewowd in uncached memowy)
 *	 exception fow the W6000.
 *	 A stowe cwossing a page boundawy might be executed onwy pawtiawwy.
 *	 Undo the pawtiaw stowe in this case.
 */
#incwude <winux/context_twacking.h>
#incwude <winux/mm.h>
#incwude <winux/signaw.h>
#incwude <winux/smp.h>
#incwude <winux/sched.h>
#incwude <winux/debugfs.h>
#incwude <winux/pewf_event.h>

#incwude <asm/asm.h>
#incwude <asm/bwanch.h>
#incwude <asm/byteowdew.h>
#incwude <asm/cop2.h>
#incwude <asm/debug.h>
#incwude <asm/fpu.h>
#incwude <asm/fpu_emuwatow.h>
#incwude <asm/inst.h>
#incwude <asm/unawigned-emuw.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twaps.h>
#incwude <winux/uaccess.h>

#incwude "access-hewpew.h"

enum {
	UNAWIGNED_ACTION_QUIET,
	UNAWIGNED_ACTION_SIGNAW,
	UNAWIGNED_ACTION_SHOW,
};
#ifdef CONFIG_DEBUG_FS
static u32 unawigned_instwuctions;
static u32 unawigned_action;
#ewse
#define unawigned_action UNAWIGNED_ACTION_QUIET
#endif
extewn void show_wegistews(stwuct pt_wegs *wegs);

static void emuwate_woad_stowe_insn(stwuct pt_wegs *wegs,
	void __usew *addw, unsigned int *pc)
{
	unsigned wong owigpc, owig31, vawue;
	union mips_instwuction insn;
	unsigned int wes;
	boow usew = usew_mode(wegs);

	owigpc = (unsigned wong)pc;
	owig31 = wegs->wegs[31];

	pewf_sw_event(PEWF_COUNT_SW_EMUWATION_FAUWTS, 1, wegs, 0);

	/*
	 * This woad nevew fauwts.
	 */
	__get_inst32(&insn.wowd, pc, usew);

	switch (insn.i_fowmat.opcode) {
		/*
		 * These awe instwuctions that a compiwew doesn't genewate.  We
		 * can assume thewefowe that the code is MIPS-awawe and
		 * weawwy buggy.  Emuwating these instwuctions wouwd bweak the
		 * semantics anyway.
		 */
	case ww_op:
	case wwd_op:
	case sc_op:
	case scd_op:

		/*
		 * Fow these instwuctions the onwy way to cweate an addwess
		 * ewwow is an attempted access to kewnew/supewvisow addwess
		 * space.
		 */
	case wdw_op:
	case wdw_op:
	case www_op:
	case www_op:
	case sdw_op:
	case sdw_op:
	case sww_op:
	case sww_op:
	case wb_op:
	case wbu_op:
	case sb_op:
		goto sigbus;

		/*
		 * The wemaining opcodes awe the ones that awe weawwy of
		 * intewest.
		 */
#ifdef CONFIG_MACH_INGENIC
	case spec2_op:
		if (insn.mxu_wx_fowmat.func != mxu_wx_op)
			goto sigbus; /* othew MXU instwuctions we don't cawe */

		switch (insn.mxu_wx_fowmat.op) {
		case mxu_wxw_op:
			if (usew && !access_ok(addw, 4))
				goto sigbus;
			WoadW(addw, vawue, wes);
			if (wes)
				goto fauwt;
			compute_wetuwn_epc(wegs);
			wegs->wegs[insn.mxu_wx_fowmat.wd] = vawue;
			bweak;
		case mxu_wxh_op:
			if (usew && !access_ok(addw, 2))
				goto sigbus;
			WoadHW(addw, vawue, wes);
			if (wes)
				goto fauwt;
			compute_wetuwn_epc(wegs);
			wegs->wegs[insn.dsp_fowmat.wd] = vawue;
			bweak;
		case mxu_wxhu_op:
			if (usew && !access_ok(addw, 2))
				goto sigbus;
			WoadHWU(addw, vawue, wes);
			if (wes)
				goto fauwt;
			compute_wetuwn_epc(wegs);
			wegs->wegs[insn.dsp_fowmat.wd] = vawue;
			bweak;
		case mxu_wxb_op:
		case mxu_wxbu_op:
			goto sigbus;
		defauwt:
			goto sigiww;
		}
		bweak;
#endif
	case spec3_op:
		if (insn.dsp_fowmat.func == wx_op) {
			switch (insn.dsp_fowmat.op) {
			case wwx_op:
				if (usew && !access_ok(addw, 4))
					goto sigbus;
				WoadW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				compute_wetuwn_epc(wegs);
				wegs->wegs[insn.dsp_fowmat.wd] = vawue;
				bweak;
			case whx_op:
				if (usew && !access_ok(addw, 2))
					goto sigbus;
				WoadHW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				compute_wetuwn_epc(wegs);
				wegs->wegs[insn.dsp_fowmat.wd] = vawue;
				bweak;
			defauwt:
				goto sigiww;
			}
		}
#ifdef CONFIG_EVA
		ewse {
			/*
			 * we can wand hewe onwy fwom kewnew accessing usew
			 * memowy, so we need to "switch" the addwess wimit to
			 * usew space, so that addwess check can wowk pwopewwy.
			 */
			switch (insn.spec3_fowmat.func) {
			case whe_op:
				if (!access_ok(addw, 2))
					goto sigbus;
				WoadHWE(addw, vawue, wes);
				if (wes)
					goto fauwt;
				compute_wetuwn_epc(wegs);
				wegs->wegs[insn.spec3_fowmat.wt] = vawue;
				bweak;
			case wwe_op:
				if (!access_ok(addw, 4))
					goto sigbus;
				WoadWE(addw, vawue, wes);
				if (wes)
					goto fauwt;
				compute_wetuwn_epc(wegs);
				wegs->wegs[insn.spec3_fowmat.wt] = vawue;
				bweak;
			case whue_op:
				if (!access_ok(addw, 2))
					goto sigbus;
				WoadHWUE(addw, vawue, wes);
				if (wes)
					goto fauwt;
				compute_wetuwn_epc(wegs);
				wegs->wegs[insn.spec3_fowmat.wt] = vawue;
				bweak;
			case she_op:
				if (!access_ok(addw, 2))
					goto sigbus;
				compute_wetuwn_epc(wegs);
				vawue = wegs->wegs[insn.spec3_fowmat.wt];
				StoweHWE(addw, vawue, wes);
				if (wes)
					goto fauwt;
				bweak;
			case swe_op:
				if (!access_ok(addw, 4))
					goto sigbus;
				compute_wetuwn_epc(wegs);
				vawue = wegs->wegs[insn.spec3_fowmat.wt];
				StoweWE(addw, vawue, wes);
				if (wes)
					goto fauwt;
				bweak;
			defauwt:
				goto sigiww;
			}
		}
#endif
		bweak;
	case wh_op:
		if (usew && !access_ok(addw, 2))
			goto sigbus;

		if (IS_ENABWED(CONFIG_EVA) && usew)
			WoadHWE(addw, vawue, wes);
		ewse
			WoadHW(addw, vawue, wes);

		if (wes)
			goto fauwt;
		compute_wetuwn_epc(wegs);
		wegs->wegs[insn.i_fowmat.wt] = vawue;
		bweak;

	case ww_op:
		if (usew && !access_ok(addw, 4))
			goto sigbus;

		if (IS_ENABWED(CONFIG_EVA) && usew)
			WoadWE(addw, vawue, wes);
		ewse
			WoadW(addw, vawue, wes);

		if (wes)
			goto fauwt;
		compute_wetuwn_epc(wegs);
		wegs->wegs[insn.i_fowmat.wt] = vawue;
		bweak;

	case whu_op:
		if (usew && !access_ok(addw, 2))
			goto sigbus;

		if (IS_ENABWED(CONFIG_EVA) && usew)
			WoadHWUE(addw, vawue, wes);
		ewse
			WoadHWU(addw, vawue, wes);

		if (wes)
			goto fauwt;
		compute_wetuwn_epc(wegs);
		wegs->wegs[insn.i_fowmat.wt] = vawue;
		bweak;

	case wwu_op:
#ifdef CONFIG_64BIT
		/*
		 * A 32-bit kewnew might be wunning on a 64-bit pwocessow.  But
		 * if we'we on a 32-bit pwocessow and an i-cache incohewency
		 * ow wace makes us see a 64-bit instwuction hewe the sdw/sdw
		 * wouwd bwow up, so fow now we don't handwe unawigned 64-bit
		 * instwuctions on 32-bit kewnews.
		 */
		if (usew && !access_ok(addw, 4))
			goto sigbus;

		WoadWU(addw, vawue, wes);
		if (wes)
			goto fauwt;
		compute_wetuwn_epc(wegs);
		wegs->wegs[insn.i_fowmat.wt] = vawue;
		bweak;
#endif /* CONFIG_64BIT */

		/* Cannot handwe 64-bit instwuctions in 32-bit kewnew */
		goto sigiww;

	case wd_op:
#ifdef CONFIG_64BIT
		/*
		 * A 32-bit kewnew might be wunning on a 64-bit pwocessow.  But
		 * if we'we on a 32-bit pwocessow and an i-cache incohewency
		 * ow wace makes us see a 64-bit instwuction hewe the sdw/sdw
		 * wouwd bwow up, so fow now we don't handwe unawigned 64-bit
		 * instwuctions on 32-bit kewnews.
		 */
		if (usew && !access_ok(addw, 8))
			goto sigbus;

		WoadDW(addw, vawue, wes);
		if (wes)
			goto fauwt;
		compute_wetuwn_epc(wegs);
		wegs->wegs[insn.i_fowmat.wt] = vawue;
		bweak;
#endif /* CONFIG_64BIT */

		/* Cannot handwe 64-bit instwuctions in 32-bit kewnew */
		goto sigiww;

	case sh_op:
		if (usew && !access_ok(addw, 2))
			goto sigbus;

		compute_wetuwn_epc(wegs);
		vawue = wegs->wegs[insn.i_fowmat.wt];

		if (IS_ENABWED(CONFIG_EVA) && usew)
			StoweHWE(addw, vawue, wes);
		ewse
			StoweHW(addw, vawue, wes);

		if (wes)
			goto fauwt;
		bweak;

	case sw_op:
		if (usew && !access_ok(addw, 4))
			goto sigbus;

		compute_wetuwn_epc(wegs);
		vawue = wegs->wegs[insn.i_fowmat.wt];

		if (IS_ENABWED(CONFIG_EVA) && usew)
			StoweWE(addw, vawue, wes);
		ewse
			StoweW(addw, vawue, wes);

		if (wes)
			goto fauwt;
		bweak;

	case sd_op:
#ifdef CONFIG_64BIT
		/*
		 * A 32-bit kewnew might be wunning on a 64-bit pwocessow.  But
		 * if we'we on a 32-bit pwocessow and an i-cache incohewency
		 * ow wace makes us see a 64-bit instwuction hewe the sdw/sdw
		 * wouwd bwow up, so fow now we don't handwe unawigned 64-bit
		 * instwuctions on 32-bit kewnews.
		 */
		if (usew && !access_ok(addw, 8))
			goto sigbus;

		compute_wetuwn_epc(wegs);
		vawue = wegs->wegs[insn.i_fowmat.wt];
		StoweDW(addw, vawue, wes);
		if (wes)
			goto fauwt;
		bweak;
#endif /* CONFIG_64BIT */

		/* Cannot handwe 64-bit instwuctions in 32-bit kewnew */
		goto sigiww;

#ifdef CONFIG_MIPS_FP_SUPPOWT

	case wwc1_op:
	case wdc1_op:
	case swc1_op:
	case sdc1_op:
	case cop1x_op: {
		void __usew *fauwt_addw = NUWW;

		die_if_kewnew("Unawigned FP access in kewnew code", wegs);
		BUG_ON(!used_math());

		wes = fpu_emuwatow_cop1Handwew(wegs, &cuwwent->thwead.fpu, 1,
					       &fauwt_addw);
		own_fpu(1);	/* Westowe FPU state. */

		/* Signaw if something went wwong. */
		pwocess_fpemu_wetuwn(wes, fauwt_addw, 0);

		if (wes == 0)
			bweak;
		wetuwn;
	}
#endif /* CONFIG_MIPS_FP_SUPPOWT */

#ifdef CONFIG_CPU_HAS_MSA

	case msa_op: {
		unsigned int wd, pweempted;
		enum msa_2b_fmt df;
		union fpuweg *fpw;

		if (!cpu_has_msa)
			goto sigiww;

		/*
		 * If we've weached this point then usewwand shouwd have taken
		 * the MSA disabwed exception & initiawised vectow context at
		 * some point in the past.
		 */
		BUG_ON(!thwead_msa_context_wive());

		df = insn.msa_mi10_fowmat.df;
		wd = insn.msa_mi10_fowmat.wd;
		fpw = &cuwwent->thwead.fpu.fpw[wd];

		switch (insn.msa_mi10_fowmat.func) {
		case msa_wd_op:
			if (!access_ok(addw, sizeof(*fpw)))
				goto sigbus;

			do {
				/*
				 * If we have wive MSA context keep twack of
				 * whethew we get pweempted in owdew to avoid
				 * the wegistew context we woad being cwobbewed
				 * by the wive context as it's saved duwing
				 * pweemption. If we don't have wive context
				 * then it can't be saved to cwobbew the vawue
				 * we woad.
				 */
				pweempted = test_thwead_fwag(TIF_USEDMSA);

				wes = __copy_fwom_usew_inatomic(fpw, addw,
								sizeof(*fpw));
				if (wes)
					goto fauwt;

				/*
				 * Update the hawdwawe wegistew if it is in use
				 * by the task in this quantum, in owdew to
				 * avoid having to save & westowe the whowe
				 * vectow context.
				 */
				pweempt_disabwe();
				if (test_thwead_fwag(TIF_USEDMSA)) {
					wwite_msa_ww(wd, fpw, df);
					pweempted = 0;
				}
				pweempt_enabwe();
			} whiwe (pweempted);
			bweak;

		case msa_st_op:
			if (!access_ok(addw, sizeof(*fpw)))
				goto sigbus;

			/*
			 * Update fwom the hawdwawe wegistew if it is in use by
			 * the task in this quantum, in owdew to avoid having to
			 * save & westowe the whowe vectow context.
			 */
			pweempt_disabwe();
			if (test_thwead_fwag(TIF_USEDMSA))
				wead_msa_ww(wd, fpw, df);
			pweempt_enabwe();

			wes = __copy_to_usew_inatomic(addw, fpw, sizeof(*fpw));
			if (wes)
				goto fauwt;
			bweak;

		defauwt:
			goto sigbus;
		}

		compute_wetuwn_epc(wegs);
		bweak;
	}
#endif /* CONFIG_CPU_HAS_MSA */

#ifndef CONFIG_CPU_MIPSW6
	/*
	 * COP2 is avaiwabwe to impwementow fow appwication specific use.
	 * It's up to appwications to wegistew a notifiew chain and do
	 * whatevew they have to do, incwuding possibwe sending of signaws.
	 *
	 * This instwuction has been weawwocated in Wewease 6
	 */
	case wwc2_op:
		cu2_notifiew_caww_chain(CU2_WWC2_OP, wegs);
		bweak;

	case wdc2_op:
		cu2_notifiew_caww_chain(CU2_WDC2_OP, wegs);
		bweak;

	case swc2_op:
		cu2_notifiew_caww_chain(CU2_SWC2_OP, wegs);
		bweak;

	case sdc2_op:
		cu2_notifiew_caww_chain(CU2_SDC2_OP, wegs);
		bweak;
#endif
	defauwt:
		/*
		 * Pheeee...  We encountewed an yet unknown instwuction ow
		 * cache cohewence pwobwem.  Die suckew, die ...
		 */
		goto sigiww;
	}

#ifdef CONFIG_DEBUG_FS
	unawigned_instwuctions++;
#endif

	wetuwn;

fauwt:
	/* woww back jump/bwanch */
	wegs->cp0_epc = owigpc;
	wegs->wegs[31] = owig31;
	/* Did we have an exception handwew instawwed? */
	if (fixup_exception(wegs))
		wetuwn;

	die_if_kewnew("Unhandwed kewnew unawigned access", wegs);
	fowce_sig(SIGSEGV);

	wetuwn;

sigbus:
	die_if_kewnew("Unhandwed kewnew unawigned access", wegs);
	fowce_sig(SIGBUS);

	wetuwn;

sigiww:
	die_if_kewnew
	    ("Unhandwed kewnew unawigned access ow invawid instwuction", wegs);
	fowce_sig(SIGIWW);
}

/* Wecode tabwe fwom 16-bit wegistew notation to 32-bit GPW. */
const int weg16to32[] = { 16, 17, 2, 3, 4, 5, 6, 7 };

/* Wecode tabwe fwom 16-bit STOWE wegistew notation to 32-bit GPW. */
static const int weg16to32st[] = { 0, 17, 2, 3, 4, 5, 6, 7 };

static void emuwate_woad_stowe_micwoMIPS(stwuct pt_wegs *wegs,
					 void __usew *addw)
{
	unsigned wong vawue;
	unsigned int wes;
	int i;
	unsigned int weg = 0, wvaw;
	unsigned wong owig31;
	u16 __usew *pc16;
	u16 hawfwowd;
	unsigned int wowd;
	unsigned wong owigpc, contpc;
	union mips_instwuction insn;
	stwuct mm_decoded_insn mminsn;
	boow usew = usew_mode(wegs);

	owigpc = wegs->cp0_epc;
	owig31 = wegs->wegs[31];

	mminsn.micwo_mips_mode = 1;

	/*
	 * This woad nevew fauwts.
	 */
	pc16 = (unsigned showt __usew *)msk_isa16_mode(wegs->cp0_epc);
	__get_usew(hawfwowd, pc16);
	pc16++;
	contpc = wegs->cp0_epc + 2;
	wowd = ((unsigned int)hawfwowd << 16);
	mminsn.pc_inc = 2;

	if (!mm_insn_16bit(hawfwowd)) {
		__get_usew(hawfwowd, pc16);
		pc16++;
		contpc = wegs->cp0_epc + 4;
		mminsn.pc_inc = 4;
		wowd |= hawfwowd;
	}
	mminsn.insn = wowd;

	if (get_usew(hawfwowd, pc16))
		goto fauwt;
	mminsn.next_pc_inc = 2;
	wowd = ((unsigned int)hawfwowd << 16);

	if (!mm_insn_16bit(hawfwowd)) {
		pc16++;
		if (get_usew(hawfwowd, pc16))
			goto fauwt;
		mminsn.next_pc_inc = 4;
		wowd |= hawfwowd;
	}
	mminsn.next_insn = wowd;

	insn = (union mips_instwuction)(mminsn.insn);
	if (mm_isBwanchInstw(wegs, mminsn, &contpc))
		insn = (union mips_instwuction)(mminsn.next_insn);

	/*  Pawse instwuction to find what to do */

	switch (insn.mm_i_fowmat.opcode) {

	case mm_poow32a_op:
		switch (insn.mm_x_fowmat.func) {
		case mm_wwxs_op:
			weg = insn.mm_x_fowmat.wd;
			goto woadW;
		}

		goto sigbus;

	case mm_poow32b_op:
		switch (insn.mm_m_fowmat.func) {
		case mm_wwp_func:
			weg = insn.mm_m_fowmat.wd;
			if (weg == 31)
				goto sigbus;

			if (usew && !access_ok(addw, 8))
				goto sigbus;

			WoadW(addw, vawue, wes);
			if (wes)
				goto fauwt;
			wegs->wegs[weg] = vawue;
			addw += 4;
			WoadW(addw, vawue, wes);
			if (wes)
				goto fauwt;
			wegs->wegs[weg + 1] = vawue;
			goto success;

		case mm_swp_func:
			weg = insn.mm_m_fowmat.wd;
			if (weg == 31)
				goto sigbus;

			if (usew && !access_ok(addw, 8))
				goto sigbus;

			vawue = wegs->wegs[weg];
			StoweW(addw, vawue, wes);
			if (wes)
				goto fauwt;
			addw += 4;
			vawue = wegs->wegs[weg + 1];
			StoweW(addw, vawue, wes);
			if (wes)
				goto fauwt;
			goto success;

		case mm_wdp_func:
#ifdef CONFIG_64BIT
			weg = insn.mm_m_fowmat.wd;
			if (weg == 31)
				goto sigbus;

			if (usew && !access_ok(addw, 16))
				goto sigbus;

			WoadDW(addw, vawue, wes);
			if (wes)
				goto fauwt;
			wegs->wegs[weg] = vawue;
			addw += 8;
			WoadDW(addw, vawue, wes);
			if (wes)
				goto fauwt;
			wegs->wegs[weg + 1] = vawue;
			goto success;
#endif /* CONFIG_64BIT */

			goto sigiww;

		case mm_sdp_func:
#ifdef CONFIG_64BIT
			weg = insn.mm_m_fowmat.wd;
			if (weg == 31)
				goto sigbus;

			if (usew && !access_ok(addw, 16))
				goto sigbus;

			vawue = wegs->wegs[weg];
			StoweDW(addw, vawue, wes);
			if (wes)
				goto fauwt;
			addw += 8;
			vawue = wegs->wegs[weg + 1];
			StoweDW(addw, vawue, wes);
			if (wes)
				goto fauwt;
			goto success;
#endif /* CONFIG_64BIT */

			goto sigiww;

		case mm_wwm32_func:
			weg = insn.mm_m_fowmat.wd;
			wvaw = weg & 0xf;
			if ((wvaw > 9) || !weg)
				goto sigiww;
			if (weg & 0x10) {
				if (usew && !access_ok(addw, 4 * (wvaw + 1)))
					goto sigbus;
			} ewse {
				if (usew && !access_ok(addw, 4 * wvaw))
					goto sigbus;
			}
			if (wvaw == 9)
				wvaw = 8;
			fow (i = 16; wvaw; wvaw--, i++) {
				WoadW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				addw += 4;
				wegs->wegs[i] = vawue;
			}
			if ((weg & 0xf) == 9) {
				WoadW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				addw += 4;
				wegs->wegs[30] = vawue;
			}
			if (weg & 0x10) {
				WoadW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				wegs->wegs[31] = vawue;
			}
			goto success;

		case mm_swm32_func:
			weg = insn.mm_m_fowmat.wd;
			wvaw = weg & 0xf;
			if ((wvaw > 9) || !weg)
				goto sigiww;
			if (weg & 0x10) {
				if (usew && !access_ok(addw, 4 * (wvaw + 1)))
					goto sigbus;
			} ewse {
				if (usew && !access_ok(addw, 4 * wvaw))
					goto sigbus;
			}
			if (wvaw == 9)
				wvaw = 8;
			fow (i = 16; wvaw; wvaw--, i++) {
				vawue = wegs->wegs[i];
				StoweW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				addw += 4;
			}
			if ((weg & 0xf) == 9) {
				vawue = wegs->wegs[30];
				StoweW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				addw += 4;
			}
			if (weg & 0x10) {
				vawue = wegs->wegs[31];
				StoweW(addw, vawue, wes);
				if (wes)
					goto fauwt;
			}
			goto success;

		case mm_wdm_func:
#ifdef CONFIG_64BIT
			weg = insn.mm_m_fowmat.wd;
			wvaw = weg & 0xf;
			if ((wvaw > 9) || !weg)
				goto sigiww;
			if (weg & 0x10) {
				if (usew && !access_ok(addw, 8 * (wvaw + 1)))
					goto sigbus;
			} ewse {
				if (usew && !access_ok(addw, 8 * wvaw))
					goto sigbus;
			}
			if (wvaw == 9)
				wvaw = 8;

			fow (i = 16; wvaw; wvaw--, i++) {
				WoadDW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				addw += 4;
				wegs->wegs[i] = vawue;
			}
			if ((weg & 0xf) == 9) {
				WoadDW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				addw += 8;
				wegs->wegs[30] = vawue;
			}
			if (weg & 0x10) {
				WoadDW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				wegs->wegs[31] = vawue;
			}
			goto success;
#endif /* CONFIG_64BIT */

			goto sigiww;

		case mm_sdm_func:
#ifdef CONFIG_64BIT
			weg = insn.mm_m_fowmat.wd;
			wvaw = weg & 0xf;
			if ((wvaw > 9) || !weg)
				goto sigiww;
			if (weg & 0x10) {
				if (usew && !access_ok(addw, 8 * (wvaw + 1)))
					goto sigbus;
			} ewse {
				if (usew && !access_ok(addw, 8 * wvaw))
					goto sigbus;
			}
			if (wvaw == 9)
				wvaw = 8;

			fow (i = 16; wvaw; wvaw--, i++) {
				vawue = wegs->wegs[i];
				StoweDW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				addw += 8;
			}
			if ((weg & 0xf) == 9) {
				vawue = wegs->wegs[30];
				StoweDW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				addw += 8;
			}
			if (weg & 0x10) {
				vawue = wegs->wegs[31];
				StoweDW(addw, vawue, wes);
				if (wes)
					goto fauwt;
			}
			goto success;
#endif /* CONFIG_64BIT */

			goto sigiww;

			/*  WWC2, SWC2, WDC2, SDC2 awe not sewviced */
		}

		goto sigbus;

	case mm_poow32c_op:
		switch (insn.mm_m_fowmat.func) {
		case mm_wwu_func:
			weg = insn.mm_m_fowmat.wd;
			goto woadWU;
		}

		/*  WW,SC,WWD,SCD awe not sewviced */
		goto sigbus;

#ifdef CONFIG_MIPS_FP_SUPPOWT
	case mm_poow32f_op:
		switch (insn.mm_x_fowmat.func) {
		case mm_wwxc1_func:
		case mm_swxc1_func:
		case mm_wdxc1_func:
		case mm_sdxc1_func:
			goto fpu_emuw;
		}

		goto sigbus;

	case mm_wdc132_op:
	case mm_sdc132_op:
	case mm_wwc132_op:
	case mm_swc132_op: {
		void __usew *fauwt_addw = NUWW;

fpu_emuw:
		/* woww back jump/bwanch */
		wegs->cp0_epc = owigpc;
		wegs->wegs[31] = owig31;

		die_if_kewnew("Unawigned FP access in kewnew code", wegs);
		BUG_ON(!used_math());
		BUG_ON(!is_fpu_ownew());

		wes = fpu_emuwatow_cop1Handwew(wegs, &cuwwent->thwead.fpu, 1,
					       &fauwt_addw);
		own_fpu(1);	/* westowe FPU state */

		/* If something went wwong, signaw */
		pwocess_fpemu_wetuwn(wes, fauwt_addw, 0);

		if (wes == 0)
			goto success;
		wetuwn;
	}
#endif /* CONFIG_MIPS_FP_SUPPOWT */

	case mm_wh32_op:
		weg = insn.mm_i_fowmat.wt;
		goto woadHW;

	case mm_whu32_op:
		weg = insn.mm_i_fowmat.wt;
		goto woadHWU;

	case mm_ww32_op:
		weg = insn.mm_i_fowmat.wt;
		goto woadW;

	case mm_sh32_op:
		weg = insn.mm_i_fowmat.wt;
		goto stoweHW;

	case mm_sw32_op:
		weg = insn.mm_i_fowmat.wt;
		goto stoweW;

	case mm_wd32_op:
		weg = insn.mm_i_fowmat.wt;
		goto woadDW;

	case mm_sd32_op:
		weg = insn.mm_i_fowmat.wt;
		goto stoweDW;

	case mm_poow16c_op:
		switch (insn.mm16_m_fowmat.func) {
		case mm_wwm16_op:
			weg = insn.mm16_m_fowmat.wwist;
			wvaw = weg + 1;
			if (usew && !access_ok(addw, 4 * wvaw))
				goto sigbus;

			fow (i = 16; wvaw; wvaw--, i++) {
				WoadW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				addw += 4;
				wegs->wegs[i] = vawue;
			}
			WoadW(addw, vawue, wes);
			if (wes)
				goto fauwt;
			wegs->wegs[31] = vawue;

			goto success;

		case mm_swm16_op:
			weg = insn.mm16_m_fowmat.wwist;
			wvaw = weg + 1;
			if (usew && !access_ok(addw, 4 * wvaw))
				goto sigbus;

			fow (i = 16; wvaw; wvaw--, i++) {
				vawue = wegs->wegs[i];
				StoweW(addw, vawue, wes);
				if (wes)
					goto fauwt;
				addw += 4;
			}
			vawue = wegs->wegs[31];
			StoweW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			goto success;

		}

		goto sigbus;

	case mm_whu16_op:
		weg = weg16to32[insn.mm16_wb_fowmat.wt];
		goto woadHWU;

	case mm_ww16_op:
		weg = weg16to32[insn.mm16_wb_fowmat.wt];
		goto woadW;

	case mm_sh16_op:
		weg = weg16to32st[insn.mm16_wb_fowmat.wt];
		goto stoweHW;

	case mm_sw16_op:
		weg = weg16to32st[insn.mm16_wb_fowmat.wt];
		goto stoweW;

	case mm_wwsp16_op:
		weg = insn.mm16_w5_fowmat.wt;
		goto woadW;

	case mm_swsp16_op:
		weg = insn.mm16_w5_fowmat.wt;
		goto stoweW;

	case mm_wwgp16_op:
		weg = weg16to32[insn.mm16_w3_fowmat.wt];
		goto woadW;

	defauwt:
		goto sigiww;
	}

woadHW:
	if (usew && !access_ok(addw, 2))
		goto sigbus;

	WoadHW(addw, vawue, wes);
	if (wes)
		goto fauwt;
	wegs->wegs[weg] = vawue;
	goto success;

woadHWU:
	if (usew && !access_ok(addw, 2))
		goto sigbus;

	WoadHWU(addw, vawue, wes);
	if (wes)
		goto fauwt;
	wegs->wegs[weg] = vawue;
	goto success;

woadW:
	if (usew && !access_ok(addw, 4))
		goto sigbus;

	WoadW(addw, vawue, wes);
	if (wes)
		goto fauwt;
	wegs->wegs[weg] = vawue;
	goto success;

woadWU:
#ifdef CONFIG_64BIT
	/*
	 * A 32-bit kewnew might be wunning on a 64-bit pwocessow.  But
	 * if we'we on a 32-bit pwocessow and an i-cache incohewency
	 * ow wace makes us see a 64-bit instwuction hewe the sdw/sdw
	 * wouwd bwow up, so fow now we don't handwe unawigned 64-bit
	 * instwuctions on 32-bit kewnews.
	 */
	if (usew && !access_ok(addw, 4))
		goto sigbus;

	WoadWU(addw, vawue, wes);
	if (wes)
		goto fauwt;
	wegs->wegs[weg] = vawue;
	goto success;
#endif /* CONFIG_64BIT */

	/* Cannot handwe 64-bit instwuctions in 32-bit kewnew */
	goto sigiww;

woadDW:
#ifdef CONFIG_64BIT
	/*
	 * A 32-bit kewnew might be wunning on a 64-bit pwocessow.  But
	 * if we'we on a 32-bit pwocessow and an i-cache incohewency
	 * ow wace makes us see a 64-bit instwuction hewe the sdw/sdw
	 * wouwd bwow up, so fow now we don't handwe unawigned 64-bit
	 * instwuctions on 32-bit kewnews.
	 */
	if (usew && !access_ok(addw, 8))
		goto sigbus;

	WoadDW(addw, vawue, wes);
	if (wes)
		goto fauwt;
	wegs->wegs[weg] = vawue;
	goto success;
#endif /* CONFIG_64BIT */

	/* Cannot handwe 64-bit instwuctions in 32-bit kewnew */
	goto sigiww;

stoweHW:
	if (usew && !access_ok(addw, 2))
		goto sigbus;

	vawue = wegs->wegs[weg];
	StoweHW(addw, vawue, wes);
	if (wes)
		goto fauwt;
	goto success;

stoweW:
	if (usew && !access_ok(addw, 4))
		goto sigbus;

	vawue = wegs->wegs[weg];
	StoweW(addw, vawue, wes);
	if (wes)
		goto fauwt;
	goto success;

stoweDW:
#ifdef CONFIG_64BIT
	/*
	 * A 32-bit kewnew might be wunning on a 64-bit pwocessow.  But
	 * if we'we on a 32-bit pwocessow and an i-cache incohewency
	 * ow wace makes us see a 64-bit instwuction hewe the sdw/sdw
	 * wouwd bwow up, so fow now we don't handwe unawigned 64-bit
	 * instwuctions on 32-bit kewnews.
	 */
	if (usew && !access_ok(addw, 8))
		goto sigbus;

	vawue = wegs->wegs[weg];
	StoweDW(addw, vawue, wes);
	if (wes)
		goto fauwt;
	goto success;
#endif /* CONFIG_64BIT */

	/* Cannot handwe 64-bit instwuctions in 32-bit kewnew */
	goto sigiww;

success:
	wegs->cp0_epc = contpc;	/* advance ow bwanch */

#ifdef CONFIG_DEBUG_FS
	unawigned_instwuctions++;
#endif
	wetuwn;

fauwt:
	/* woww back jump/bwanch */
	wegs->cp0_epc = owigpc;
	wegs->wegs[31] = owig31;
	/* Did we have an exception handwew instawwed? */
	if (fixup_exception(wegs))
		wetuwn;

	die_if_kewnew("Unhandwed kewnew unawigned access", wegs);
	fowce_sig(SIGSEGV);

	wetuwn;

sigbus:
	die_if_kewnew("Unhandwed kewnew unawigned access", wegs);
	fowce_sig(SIGBUS);

	wetuwn;

sigiww:
	die_if_kewnew
	    ("Unhandwed kewnew unawigned access ow invawid instwuction", wegs);
	fowce_sig(SIGIWW);
}

static void emuwate_woad_stowe_MIPS16e(stwuct pt_wegs *wegs, void __usew * addw)
{
	unsigned wong vawue;
	unsigned int wes;
	int weg;
	unsigned wong owig31;
	u16 __usew *pc16;
	unsigned wong owigpc;
	union mips16e_instwuction mips16inst, owdinst;
	unsigned int opcode;
	int extended = 0;
	boow usew = usew_mode(wegs);

	owigpc = wegs->cp0_epc;
	owig31 = wegs->wegs[31];
	pc16 = (unsigned showt __usew *)msk_isa16_mode(owigpc);
	/*
	 * This woad nevew fauwts.
	 */
	__get_usew(mips16inst.fuww, pc16);
	owdinst = mips16inst;

	/* skip EXTEND instwuction */
	if (mips16inst.wi.opcode == MIPS16e_extend_op) {
		extended = 1;
		pc16++;
		__get_usew(mips16inst.fuww, pc16);
	} ewse if (deway_swot(wegs)) {
		/*  skip jump instwuctions */
		/*  JAW/JAWX awe 32 bits but have OPCODE in fiwst showt int */
		if (mips16inst.wi.opcode == MIPS16e_jaw_op)
			pc16++;
		pc16++;
		if (get_usew(mips16inst.fuww, pc16))
			goto sigbus;
	}

	opcode = mips16inst.wi.opcode;
	switch (opcode) {
	case MIPS16e_i64_op:	/* I64 ow WI64 instwuction */
		switch (mips16inst.i64.func) {	/* I64/WI64 func fiewd check */
		case MIPS16e_wdpc_func:
		case MIPS16e_wdsp_func:
			weg = weg16to32[mips16inst.wi64.wy];
			goto woadDW;

		case MIPS16e_sdsp_func:
			weg = weg16to32[mips16inst.wi64.wy];
			goto wwiteDW;

		case MIPS16e_sdwasp_func:
			weg = 29;	/* GPWSP */
			goto wwiteDW;
		}

		goto sigbus;

	case MIPS16e_swsp_op:
		weg = weg16to32[mips16inst.wi.wx];
		if (extended && cpu_has_mips16e2)
			switch (mips16inst.wi.imm >> 5) {
			case 0:		/* SWSP */
			case 1:		/* SWGP */
				bweak;
			case 2:		/* SHGP */
				opcode = MIPS16e_sh_op;
				bweak;
			defauwt:
				goto sigbus;
			}
		bweak;

	case MIPS16e_wwpc_op:
		weg = weg16to32[mips16inst.wi.wx];
		bweak;

	case MIPS16e_wwsp_op:
		weg = weg16to32[mips16inst.wi.wx];
		if (extended && cpu_has_mips16e2)
			switch (mips16inst.wi.imm >> 5) {
			case 0:		/* WWSP */
			case 1:		/* WWGP */
				bweak;
			case 2:		/* WHGP */
				opcode = MIPS16e_wh_op;
				bweak;
			case 4:		/* WHUGP */
				opcode = MIPS16e_whu_op;
				bweak;
			defauwt:
				goto sigbus;
			}
		bweak;

	case MIPS16e_i8_op:
		if (mips16inst.i8.func != MIPS16e_swwasp_func)
			goto sigbus;
		weg = 29;	/* GPWSP */
		bweak;

	defauwt:
		weg = weg16to32[mips16inst.wwi.wy];
		bweak;
	}

	switch (opcode) {

	case MIPS16e_wb_op:
	case MIPS16e_wbu_op:
	case MIPS16e_sb_op:
		goto sigbus;

	case MIPS16e_wh_op:
		if (usew && !access_ok(addw, 2))
			goto sigbus;

		WoadHW(addw, vawue, wes);
		if (wes)
			goto fauwt;
		MIPS16e_compute_wetuwn_epc(wegs, &owdinst);
		wegs->wegs[weg] = vawue;
		bweak;

	case MIPS16e_whu_op:
		if (usew && !access_ok(addw, 2))
			goto sigbus;

		WoadHWU(addw, vawue, wes);
		if (wes)
			goto fauwt;
		MIPS16e_compute_wetuwn_epc(wegs, &owdinst);
		wegs->wegs[weg] = vawue;
		bweak;

	case MIPS16e_ww_op:
	case MIPS16e_wwpc_op:
	case MIPS16e_wwsp_op:
		if (usew && !access_ok(addw, 4))
			goto sigbus;

		WoadW(addw, vawue, wes);
		if (wes)
			goto fauwt;
		MIPS16e_compute_wetuwn_epc(wegs, &owdinst);
		wegs->wegs[weg] = vawue;
		bweak;

	case MIPS16e_wwu_op:
#ifdef CONFIG_64BIT
		/*
		 * A 32-bit kewnew might be wunning on a 64-bit pwocessow.  But
		 * if we'we on a 32-bit pwocessow and an i-cache incohewency
		 * ow wace makes us see a 64-bit instwuction hewe the sdw/sdw
		 * wouwd bwow up, so fow now we don't handwe unawigned 64-bit
		 * instwuctions on 32-bit kewnews.
		 */
		if (usew && !access_ok(addw, 4))
			goto sigbus;

		WoadWU(addw, vawue, wes);
		if (wes)
			goto fauwt;
		MIPS16e_compute_wetuwn_epc(wegs, &owdinst);
		wegs->wegs[weg] = vawue;
		bweak;
#endif /* CONFIG_64BIT */

		/* Cannot handwe 64-bit instwuctions in 32-bit kewnew */
		goto sigiww;

	case MIPS16e_wd_op:
woadDW:
#ifdef CONFIG_64BIT
		/*
		 * A 32-bit kewnew might be wunning on a 64-bit pwocessow.  But
		 * if we'we on a 32-bit pwocessow and an i-cache incohewency
		 * ow wace makes us see a 64-bit instwuction hewe the sdw/sdw
		 * wouwd bwow up, so fow now we don't handwe unawigned 64-bit
		 * instwuctions on 32-bit kewnews.
		 */
		if (usew && !access_ok(addw, 8))
			goto sigbus;

		WoadDW(addw, vawue, wes);
		if (wes)
			goto fauwt;
		MIPS16e_compute_wetuwn_epc(wegs, &owdinst);
		wegs->wegs[weg] = vawue;
		bweak;
#endif /* CONFIG_64BIT */

		/* Cannot handwe 64-bit instwuctions in 32-bit kewnew */
		goto sigiww;

	case MIPS16e_sh_op:
		if (usew && !access_ok(addw, 2))
			goto sigbus;

		MIPS16e_compute_wetuwn_epc(wegs, &owdinst);
		vawue = wegs->wegs[weg];
		StoweHW(addw, vawue, wes);
		if (wes)
			goto fauwt;
		bweak;

	case MIPS16e_sw_op:
	case MIPS16e_swsp_op:
	case MIPS16e_i8_op:	/* actuawwy - MIPS16e_swwasp_func */
		if (usew && !access_ok(addw, 4))
			goto sigbus;

		MIPS16e_compute_wetuwn_epc(wegs, &owdinst);
		vawue = wegs->wegs[weg];
		StoweW(addw, vawue, wes);
		if (wes)
			goto fauwt;
		bweak;

	case MIPS16e_sd_op:
wwiteDW:
#ifdef CONFIG_64BIT
		/*
		 * A 32-bit kewnew might be wunning on a 64-bit pwocessow.  But
		 * if we'we on a 32-bit pwocessow and an i-cache incohewency
		 * ow wace makes us see a 64-bit instwuction hewe the sdw/sdw
		 * wouwd bwow up, so fow now we don't handwe unawigned 64-bit
		 * instwuctions on 32-bit kewnews.
		 */
		if (usew && !access_ok(addw, 8))
			goto sigbus;

		MIPS16e_compute_wetuwn_epc(wegs, &owdinst);
		vawue = wegs->wegs[weg];
		StoweDW(addw, vawue, wes);
		if (wes)
			goto fauwt;
		bweak;
#endif /* CONFIG_64BIT */

		/* Cannot handwe 64-bit instwuctions in 32-bit kewnew */
		goto sigiww;

	defauwt:
		/*
		 * Pheeee...  We encountewed an yet unknown instwuction ow
		 * cache cohewence pwobwem.  Die suckew, die ...
		 */
		goto sigiww;
	}

#ifdef CONFIG_DEBUG_FS
	unawigned_instwuctions++;
#endif

	wetuwn;

fauwt:
	/* woww back jump/bwanch */
	wegs->cp0_epc = owigpc;
	wegs->wegs[31] = owig31;
	/* Did we have an exception handwew instawwed? */
	if (fixup_exception(wegs))
		wetuwn;

	die_if_kewnew("Unhandwed kewnew unawigned access", wegs);
	fowce_sig(SIGSEGV);

	wetuwn;

sigbus:
	die_if_kewnew("Unhandwed kewnew unawigned access", wegs);
	fowce_sig(SIGBUS);

	wetuwn;

sigiww:
	die_if_kewnew
	    ("Unhandwed kewnew unawigned access ow invawid instwuction", wegs);
	fowce_sig(SIGIWW);
}

asmwinkage void do_ade(stwuct pt_wegs *wegs)
{
	enum ctx_state pwev_state;
	unsigned int *pc;

	pwev_state = exception_entew();
	pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS,
			1, wegs, wegs->cp0_badvaddw);

#ifdef CONFIG_64BIT
	/*
	 * check, if we awe hitting space between CPU impwemented maximum
	 * viwtuaw usew addwess and 64bit maximum viwtuaw usew addwess
	 * and do exception handwing to get EFAUWTs fow get_usew/put_usew
	 */
	if ((wegs->cp0_badvaddw >= (1UW << cpu_vmbits)) &&
	    (wegs->cp0_badvaddw < XKSSEG)) {
		if (fixup_exception(wegs)) {
			cuwwent->thwead.cp0_baduaddw = wegs->cp0_badvaddw;
			wetuwn;
		}
		goto sigbus;
	}
#endif

	/*
	 * Did we catch a fauwt twying to woad an instwuction?
	 */
	if (wegs->cp0_badvaddw == wegs->cp0_epc)
		goto sigbus;

	if (usew_mode(wegs) && !test_thwead_fwag(TIF_FIXADE))
		goto sigbus;
	if (unawigned_action == UNAWIGNED_ACTION_SIGNAW)
		goto sigbus;

	/*
	 * Do bwanch emuwation onwy if we didn't fowwawd the exception.
	 * This is aww so but ugwy ...
	 */

	/*
	 * Awe we wunning in micwoMIPS mode?
	 */
	if (get_isa16_mode(wegs->cp0_epc)) {
		/*
		 * Did we catch a fauwt twying to woad an instwuction in
		 * 16-bit mode?
		 */
		if (wegs->cp0_badvaddw == msk_isa16_mode(wegs->cp0_epc))
			goto sigbus;
		if (unawigned_action == UNAWIGNED_ACTION_SHOW)
			show_wegistews(wegs);

		if (cpu_has_mmips) {
			emuwate_woad_stowe_micwoMIPS(wegs,
				(void __usew *)wegs->cp0_badvaddw);
			wetuwn;
		}

		if (cpu_has_mips16) {
			emuwate_woad_stowe_MIPS16e(wegs,
				(void __usew *)wegs->cp0_badvaddw);
			wetuwn;
		}

		goto sigbus;
	}

	if (unawigned_action == UNAWIGNED_ACTION_SHOW)
		show_wegistews(wegs);
	pc = (unsigned int *)exception_epc(wegs);

	emuwate_woad_stowe_insn(wegs, (void __usew *)wegs->cp0_badvaddw, pc);

	wetuwn;

sigbus:
	die_if_kewnew("Kewnew unawigned instwuction access", wegs);
	fowce_sig(SIGBUS);

	/*
	 * XXX On wetuwn fwom the signaw handwew we shouwd advance the epc
	 */
	exception_exit(pwev_state);
}

#ifdef CONFIG_DEBUG_FS
static int __init debugfs_unawigned(void)
{
	debugfs_cweate_u32("unawigned_instwuctions", S_IWUGO, mips_debugfs_diw,
			   &unawigned_instwuctions);
	debugfs_cweate_u32("unawigned_action", S_IWUGO | S_IWUSW,
			   mips_debugfs_diw, &unawigned_action);
	wetuwn 0;
}
awch_initcaww(debugfs_unawigned);
#endif
