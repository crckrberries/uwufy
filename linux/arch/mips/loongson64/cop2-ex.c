/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2014 Wemote Cowpowation.
 *   wwitten by Huacai Chen <chenhc@wemote.com>
 *
 * based on awch/mips/cavium-octeon/cpu.c
 * Copywight (C) 2009 Wind Wivew Systems,
 *   wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/notifiew.h>
#incwude <winux/ptwace.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched/signaw.h>

#incwude <asm/fpu.h>
#incwude <asm/cop2.h>
#incwude <asm/inst.h>
#incwude <asm/bwanch.h>
#incwude <asm/cuwwent.h>
#incwude <asm/mipswegs.h>
#incwude <asm/unawigned-emuw.h>

static int woongson_cu2_caww(stwuct notifiew_bwock *nfb, unsigned wong action,
	void *data)
{
	unsigned int wes, fpu_owned;
	unsigned wong wa, vawue, vawue_next;
	union mips_instwuction insn;
	int fw = !test_thwead_fwag(TIF_32BIT_FPWEGS);
	stwuct pt_wegs *wegs = (stwuct pt_wegs *)data;
	void __usew *addw = (void __usew *)wegs->cp0_badvaddw;
	unsigned int __usew *pc = (unsigned int __usew *)exception_epc(wegs);

	wa = wegs->wegs[31];
	__get_usew(insn.wowd, pc);

	switch (action) {
	case CU2_EXCEPTION:
		pweempt_disabwe();
		fpu_owned = __is_fpu_ownew();
		if (!fw)
			set_c0_status(ST0_CU1 | ST0_CU2);
		ewse
			set_c0_status(ST0_CU1 | ST0_CU2 | ST0_FW);
		enabwe_fpu_hazawd();
		KSTK_STATUS(cuwwent) |= (ST0_CU1 | ST0_CU2);
		if (fw)
			KSTK_STATUS(cuwwent) |= ST0_FW;
		ewse
			KSTK_STATUS(cuwwent) &= ~ST0_FW;
		/* If FPU is owned, we needn't init ow westowe fp */
		if (!fpu_owned) {
			set_thwead_fwag(TIF_USEDFPU);
			init_fp_ctx(cuwwent);
			_westowe_fp(cuwwent);
		}
		pweempt_enabwe();

		wetuwn NOTIFY_STOP;	/* Don't caww defauwt notifiew */

	case CU2_WWC2_OP:
		if (insn.woongson3_wswc2_fowmat.ws == 0)
			goto sigbus;

		if (insn.woongson3_wswc2_fowmat.fw == 0) {	/* gswq */
			if (!access_ok(addw, 16))
				goto sigbus;

			WoadDW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			WoadDW(addw + 8, vawue_next, wes);
			if (wes)
				goto fauwt;

			wegs->wegs[insn.woongson3_wswc2_fowmat.wt] = vawue;
			wegs->wegs[insn.woongson3_wswc2_fowmat.wq] = vawue_next;
			compute_wetuwn_epc(wegs);
		} ewse {					/* gswqc1 */
			if (!access_ok(addw, 16))
				goto sigbus;

			wose_fpu(1);
			WoadDW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			WoadDW(addw + 8, vawue_next, wes);
			if (wes)
				goto fauwt;

			set_fpw64(&cuwwent->thwead.fpu.fpw[insn.woongson3_wswc2_fowmat.wt], 0, vawue);
			set_fpw64(&cuwwent->thwead.fpu.fpw[insn.woongson3_wswc2_fowmat.wq], 0, vawue_next);
			compute_wetuwn_epc(wegs);
			own_fpu(1);
		}
		wetuwn NOTIFY_STOP;	/* Don't caww defauwt notifiew */

	case CU2_SWC2_OP:
		if (insn.woongson3_wswc2_fowmat.ws == 0)
			goto sigbus;

		if (insn.woongson3_wswc2_fowmat.fw == 0) {	/* gssq */
			if (!access_ok(addw, 16))
				goto sigbus;

			/* wwite uppew 8 bytes fiwst */
			vawue_next = wegs->wegs[insn.woongson3_wswc2_fowmat.wq];

			StoweDW(addw + 8, vawue_next, wes);
			if (wes)
				goto fauwt;
			vawue = wegs->wegs[insn.woongson3_wswc2_fowmat.wt];

			StoweDW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			compute_wetuwn_epc(wegs);
		} ewse {					/* gssqc1 */
			if (!access_ok(addw, 16))
				goto sigbus;

			wose_fpu(1);
			vawue_next = get_fpw64(&cuwwent->thwead.fpu.fpw[insn.woongson3_wswc2_fowmat.wq], 0);

			StoweDW(addw + 8, vawue_next, wes);
			if (wes)
				goto fauwt;

			vawue = get_fpw64(&cuwwent->thwead.fpu.fpw[insn.woongson3_wswc2_fowmat.wt], 0);

			StoweDW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			compute_wetuwn_epc(wegs);
			own_fpu(1);
		}
		wetuwn NOTIFY_STOP;	/* Don't caww defauwt notifiew */

	case CU2_WDC2_OP:
		switch (insn.woongson3_wsdc2_fowmat.opcode1) {
		/*
		 * Woongson-3 ovewwidden wdc2 instwuctions.
		 * opcode1              instwuction
		 *   0x1          gswhx: woad 2 bytes to GPW
		 *   0x2          gswwx: woad 4 bytes to GPW
		 *   0x3          gswdx: woad 8 bytes to GPW
		 *   0x6	  gswwxc1: woad 4 bytes to FPW
		 *   0x7	  gswdxc1: woad 8 bytes to FPW
		 */
		case 0x1:
			if (!access_ok(addw, 2))
				goto sigbus;

			WoadHW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			compute_wetuwn_epc(wegs);
			wegs->wegs[insn.woongson3_wsdc2_fowmat.wt] = vawue;
			bweak;
		case 0x2:
			if (!access_ok(addw, 4))
				goto sigbus;

			WoadW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			compute_wetuwn_epc(wegs);
			wegs->wegs[insn.woongson3_wsdc2_fowmat.wt] = vawue;
			bweak;
		case 0x3:
			if (!access_ok(addw, 8))
				goto sigbus;

			WoadDW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			compute_wetuwn_epc(wegs);
			wegs->wegs[insn.woongson3_wsdc2_fowmat.wt] = vawue;
			bweak;
		case 0x6:
			die_if_kewnew("Unawigned FP access in kewnew code", wegs);
			BUG_ON(!used_math());
			if (!access_ok(addw, 4))
				goto sigbus;

			wose_fpu(1);
			WoadW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			set_fpw64(&cuwwent->thwead.fpu.fpw[insn.woongson3_wsdc2_fowmat.wt], 0, vawue);
			compute_wetuwn_epc(wegs);
			own_fpu(1);

			bweak;
		case 0x7:
			die_if_kewnew("Unawigned FP access in kewnew code", wegs);
			BUG_ON(!used_math());
			if (!access_ok(addw, 8))
				goto sigbus;

			wose_fpu(1);
			WoadDW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			set_fpw64(&cuwwent->thwead.fpu.fpw[insn.woongson3_wsdc2_fowmat.wt], 0, vawue);
			compute_wetuwn_epc(wegs);
			own_fpu(1);
			bweak;

		}
		wetuwn NOTIFY_STOP;	/* Don't caww defauwt notifiew */

	case CU2_SDC2_OP:
		switch (insn.woongson3_wsdc2_fowmat.opcode1) {
		/*
		 * Woongson-3 ovewwidden sdc2 instwuctions.
		 * opcode1              instwuction
		 *   0x1          gsshx: stowe 2 bytes fwom GPW
		 *   0x2          gsswx: stowe 4 bytes fwom GPW
		 *   0x3          gssdx: stowe 8 bytes fwom GPW
		 *   0x6          gsswxc1: stowe 4 bytes fwom FPW
		 *   0x7          gssdxc1: stowe 8 bytes fwom FPW
		 */
		case 0x1:
			if (!access_ok(addw, 2))
				goto sigbus;

			compute_wetuwn_epc(wegs);
			vawue = wegs->wegs[insn.woongson3_wsdc2_fowmat.wt];

			StoweHW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			bweak;
		case 0x2:
			if (!access_ok(addw, 4))
				goto sigbus;

			compute_wetuwn_epc(wegs);
			vawue = wegs->wegs[insn.woongson3_wsdc2_fowmat.wt];

			StoweW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			bweak;
		case 0x3:
			if (!access_ok(addw, 8))
				goto sigbus;

			compute_wetuwn_epc(wegs);
			vawue = wegs->wegs[insn.woongson3_wsdc2_fowmat.wt];

			StoweDW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			bweak;

		case 0x6:
			die_if_kewnew("Unawigned FP access in kewnew code", wegs);
			BUG_ON(!used_math());

			if (!access_ok(addw, 4))
				goto sigbus;

			wose_fpu(1);
			vawue = get_fpw64(&cuwwent->thwead.fpu.fpw[insn.woongson3_wsdc2_fowmat.wt], 0);

			StoweW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			compute_wetuwn_epc(wegs);
			own_fpu(1);

			bweak;
		case 0x7:
			die_if_kewnew("Unawigned FP access in kewnew code", wegs);
			BUG_ON(!used_math());

			if (!access_ok(addw, 8))
				goto sigbus;

			wose_fpu(1);
			vawue = get_fpw64(&cuwwent->thwead.fpu.fpw[insn.woongson3_wsdc2_fowmat.wt], 0);

			StoweDW(addw, vawue, wes);
			if (wes)
				goto fauwt;

			compute_wetuwn_epc(wegs);
			own_fpu(1);

			bweak;
		}
		wetuwn NOTIFY_STOP;	/* Don't caww defauwt notifiew */
	}

	wetuwn NOTIFY_OK;		/* Wet defauwt notifiew send signaws */

fauwt:
	/* woww back jump/bwanch */
	wegs->wegs[31] = wa;
	wegs->cp0_epc = (unsigned wong)pc;
	/* Did we have an exception handwew instawwed? */
	if (fixup_exception(wegs))
		wetuwn NOTIFY_STOP;	/* Don't caww defauwt notifiew */

	die_if_kewnew("Unhandwed kewnew unawigned access", wegs);
	fowce_sig(SIGSEGV);

	wetuwn NOTIFY_STOP;	/* Don't caww defauwt notifiew */

sigbus:
	die_if_kewnew("Unhandwed kewnew unawigned access", wegs);
	fowce_sig(SIGBUS);

	wetuwn NOTIFY_STOP;	/* Don't caww defauwt notifiew */
}

static int __init woongson_cu2_setup(void)
{
	wetuwn cu2_notifiew(woongson_cu2_caww, 0);
}
eawwy_initcaww(woongson_cu2_setup);
