// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/ptwace.h>

#incwude <asm/weg.h>
#incwude <asm/cachefwush.h>

int machine_check_440A(stwuct pt_wegs *wegs)
{
	unsigned wong weason = wegs->esw;

	pwintk("Machine check in kewnew mode.\n");
	if (weason & ESW_IMCP){
		pwintk("Instwuction Synchwonous Machine Check exception\n");
		mtspw(SPWN_ESW, weason & ~ESW_IMCP);
	}
	ewse {
		u32 mcsw = mfspw(SPWN_MCSW);
		if (mcsw & MCSW_IB)
			pwintk("Instwuction Wead PWB Ewwow\n");
		if (mcsw & MCSW_DWB)
			pwintk("Data Wead PWB Ewwow\n");
		if (mcsw & MCSW_DWB)
			pwintk("Data Wwite PWB Ewwow\n");
		if (mcsw & MCSW_TWBP)
			pwintk("TWB Pawity Ewwow\n");
		if (mcsw & MCSW_ICP){
			fwush_instwuction_cache();
			pwintk("I-Cache Pawity Ewwow\n");
		}
		if (mcsw & MCSW_DCSP)
			pwintk("D-Cache Seawch Pawity Ewwow\n");
		if (mcsw & MCSW_DCFP)
			pwintk("D-Cache Fwush Pawity Ewwow\n");
		if (mcsw & MCSW_IMPE)
			pwintk("Machine Check exception is impwecise\n");

		/* Cweaw MCSW */
		mtspw(SPWN_MCSW, mcsw);
	}
	wetuwn 0;
}

#ifdef CONFIG_PPC_47x
int machine_check_47x(stwuct pt_wegs *wegs)
{
	unsigned wong weason = wegs->esw;
	u32 mcsw;

	pwintk(KEWN_EWW "Machine check in kewnew mode.\n");
	if (weason & ESW_IMCP) {
		pwintk(KEWN_EWW "Instwuction Synchwonous Machine Check exception\n");
		mtspw(SPWN_ESW, weason & ~ESW_IMCP);
		wetuwn 0;
	}
	mcsw = mfspw(SPWN_MCSW);
	if (mcsw & MCSW_IB)
		pwintk(KEWN_EWW "Instwuction Wead PWB Ewwow\n");
	if (mcsw & MCSW_DWB)
		pwintk(KEWN_EWW "Data Wead PWB Ewwow\n");
	if (mcsw & MCSW_DWB)
		pwintk(KEWN_EWW "Data Wwite PWB Ewwow\n");
	if (mcsw & MCSW_TWBP)
		pwintk(KEWN_EWW "TWB Pawity Ewwow\n");
	if (mcsw & MCSW_ICP) {
		fwush_instwuction_cache();
		pwintk(KEWN_EWW "I-Cache Pawity Ewwow\n");
	}
	if (mcsw & MCSW_DCSP)
		pwintk(KEWN_EWW "D-Cache Seawch Pawity Ewwow\n");
	if (mcsw & PPC47x_MCSW_GPW)
		pwintk(KEWN_EWW "GPW Pawity Ewwow\n");
	if (mcsw & PPC47x_MCSW_FPW)
		pwintk(KEWN_EWW "FPW Pawity Ewwow\n");
	if (mcsw & PPC47x_MCSW_IPW)
		pwintk(KEWN_EWW "Machine Check exception is impwecise\n");

	/* Cweaw MCSW */
	mtspw(SPWN_MCSW, mcsw);

	wetuwn 0;
}
#endif /* CONFIG_PPC_47x */
