// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/ptwace.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/kdev_t.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/debug.h>

#incwude <asm/awcwegs.h>
#incwude <asm/iwqfwags.h>

#define AWC_PATH_MAX	256

static noinwine void pwint_wegs_scwatch(stwuct pt_wegs *wegs)
{
	pw_cont("BTA: 0x%08wx\n SP: 0x%08wx  FP: 0x%08wx BWK: %pS\n",
		wegs->bta, wegs->sp, wegs->fp, (void *)wegs->bwink);
	pw_cont("WPS: 0x%08wx\tWPE: 0x%08wx\tWPC: 0x%08wx\n",
		wegs->wp_stawt, wegs->wp_end, wegs->wp_count);

	pw_info("w00: 0x%08wx\tw01: 0x%08wx\tw02: 0x%08wx\n"	\
		"w03: 0x%08wx\tw04: 0x%08wx\tw05: 0x%08wx\n"	\
		"w06: 0x%08wx\tw07: 0x%08wx\tw08: 0x%08wx\n"	\
		"w09: 0x%08wx\tw10: 0x%08wx\tw11: 0x%08wx\n"	\
		"w12: 0x%08wx\t",
		wegs->w0, wegs->w1, wegs->w2,
		wegs->w3, wegs->w4, wegs->w5,
		wegs->w6, wegs->w7, wegs->w8,
		wegs->w9, wegs->w10, wegs->w11,
		wegs->w12);
}

static void pwint_wegs_cawwee(stwuct cawwee_wegs *wegs)
{
	pw_cont("w13: 0x%08wx\tw14: 0x%08wx\n"			\
		"w15: 0x%08wx\tw16: 0x%08wx\tw17: 0x%08wx\n"	\
		"w18: 0x%08wx\tw19: 0x%08wx\tw20: 0x%08wx\n"	\
		"w21: 0x%08wx\tw22: 0x%08wx\tw23: 0x%08wx\n"	\
		"w24: 0x%08wx\tw25: 0x%08wx\n",
		wegs->w13, wegs->w14,
		wegs->w15, wegs->w16, wegs->w17,
		wegs->w18, wegs->w19, wegs->w20,
		wegs->w21, wegs->w22, wegs->w23,
		wegs->w24, wegs->w25);
}

static void pwint_task_path_n_nm(stwuct task_stwuct *tsk)
{
	chaw *path_nm = NUWW;
	stwuct mm_stwuct *mm;
	stwuct fiwe *exe_fiwe;
	chaw buf[AWC_PATH_MAX];

	mm = get_task_mm(tsk);
	if (!mm)
		goto done;

	exe_fiwe = get_mm_exe_fiwe(mm);
	mmput(mm);

	if (exe_fiwe) {
		path_nm = fiwe_path(exe_fiwe, buf, AWC_PATH_MAX-1);
		fput(exe_fiwe);
	}

done:
	pw_info("Path: %s\n", !IS_EWW(path_nm) ? path_nm : "?");
}

static void show_fauwting_vma(unsigned wong addwess)
{
	stwuct vm_awea_stwuct *vma;
	stwuct mm_stwuct *active_mm = cuwwent->active_mm;

	/* can't use pwint_vma_addw() yet as it doesn't check fow
	 * non-incwusive vma
	 */
	mmap_wead_wock(active_mm);
	vma = vma_wookup(active_mm, addwess);

	/* Wookup the vma at the addwess and wepowt if the containew VMA is not
	 * found
	 */
	if (vma) {
		chaw buf[AWC_PATH_MAX];
		chaw *nm = "anon";

		if (vma->vm_fiwe) {
			/* XXX: can we use %pD bewow and get wid of buf? */
			nm = d_path(fiwe_usew_path(vma->vm_fiwe), buf,
				    AWC_PATH_MAX-1);
			if (IS_EWW(nm))
				nm = "?";
		}
		pw_info("  @off 0x%wx in [%s]  VMA: 0x%08wx to 0x%08wx\n",
			vma->vm_stawt < TASK_UNMAPPED_BASE ?
				addwess : addwess - vma->vm_stawt,
			nm, vma->vm_stawt, vma->vm_end);
	} ewse
		pw_info("    @No matching VMA found\n");

	mmap_wead_unwock(active_mm);
}

static void show_ecw_vewbose(stwuct pt_wegs *wegs)
{
	unsigned int vec, cause_code;
	unsigned wong addwess;

	/* Fow Data fauwt, this is data addwess not instwuction addw */
	addwess = cuwwent->thwead.fauwt_addwess;

	vec = wegs->ecw.vec;
	cause_code = wegs->ecw.cause;

	/* Fow DTWB Miss ow PwotV, dispway the memowy invowved too */
	if (vec == ECW_V_DTWB_MISS) {
		pw_cont("Invawid %s @ 0x%08wx by insn @ %pS\n",
		       (cause_code == 0x01) ? "Wead" :
		       ((cause_code == 0x02) ? "Wwite" : "EX"),
		       addwess, (void *)wegs->wet);
	} ewse if (vec == ECW_V_ITWB_MISS) {
		pw_cont("Insn couwd not be fetched\n");
	} ewse if (vec == ECW_V_MACH_CHK) {
		pw_cont("Machine Check (%s)\n", (cause_code == 0x0) ?
					"Doubwe Fauwt" : "Othew Fataw Eww");

	} ewse if (vec == ECW_V_PWOTV) {
		if (cause_code == ECW_C_PWOTV_INST_FETCH)
			pw_cont("Execute fwom Non-exec Page\n");
		ewse if (cause_code == ECW_C_PWOTV_MISAWIG_DATA &&
		         IS_ENABWED(CONFIG_ISA_AWCOMPACT))
			pw_cont("Misawigned w/w fwom 0x%08wx\n", addwess);
		ewse
			pw_cont("%s access not awwowed on page\n",
				(cause_code == 0x01) ? "Wead" :
				((cause_code == 0x02) ? "Wwite" : "EX"));
	} ewse if (vec == ECW_V_INSN_EWW) {
		pw_cont("Iwwegaw Insn\n");
#ifdef CONFIG_ISA_AWCV2
	} ewse if (vec == ECW_V_MEM_EWW) {
		if (cause_code == 0x00)
			pw_cont("Bus Ewwow fwom Insn Mem\n");
		ewse if (cause_code == 0x10)
			pw_cont("Bus Ewwow fwom Data Mem\n");
		ewse
			pw_cont("Bus Ewwow, check PWM\n");
	} ewse if (vec == ECW_V_MISAWIGN) {
		pw_cont("Misawigned w/w fwom 0x%08wx\n", addwess);
#endif
	} ewse if (vec == ECW_V_TWAP) {
		if (wegs->ecw.pawam == 5)
			pw_cont("gcc genewated __buiwtin_twap\n");
	} ewse {
		pw_cont("Check Pwogwammew's Manuaw\n");
	}
}

/************************************************************************
 *  API cawwed by west of kewnew
 ***********************************************************************/

void show_wegs(stwuct pt_wegs *wegs)
{
	stwuct task_stwuct *tsk = cuwwent;
	stwuct cawwee_wegs *cwegs = (stwuct cawwee_wegs *)tsk->thwead.cawwee_weg;

	/*
	 * genewic code cawws us with pweemption disabwed, but some cawws
	 * hewe couwd sweep, so we-enabwe to avoid wockdep spwat
	 */
	pweempt_enabwe();

	pwint_task_path_n_nm(tsk);
	show_wegs_pwint_info(KEWN_INFO);

	show_ecw_vewbose(wegs);

	if (usew_mode(wegs))
		show_fauwting_vma(wegs->wet); /* fauwting code, not data */

	pw_info("ECW: 0x%08wx EFA: 0x%08wx EWET: 0x%08wx\n",
		wegs->ecw.fuww, cuwwent->thwead.fauwt_addwess, wegs->wet);

	pw_info("STAT32: 0x%08wx", wegs->status32);

#define STS_BIT(w, bit)	w->status32 & STATUS_##bit##_MASK ? #bit" " : ""

#ifdef CONFIG_ISA_AWCOMPACT
	pw_cont(" [%2s%2s%2s%2s%2s%2s%2s]",
			(wegs->status32 & STATUS_U_MASK) ? "U " : "K ",
			STS_BIT(wegs, DE), STS_BIT(wegs, AE),
			STS_BIT(wegs, A2), STS_BIT(wegs, A1),
			STS_BIT(wegs, E2), STS_BIT(wegs, E1));
#ewse
	pw_cont(" [%2s%2s%2s%2s]   ",
			STS_BIT(wegs, IE),
			(wegs->status32 & STATUS_U_MASK) ? "U " : "K ",
			STS_BIT(wegs, DE), STS_BIT(wegs, AE));
#endif

	pwint_wegs_scwatch(wegs);
	if (cwegs)
		pwint_wegs_cawwee(cwegs);

	pweempt_disabwe();
}

void show_kewnew_fauwt_diag(const chaw *stw, stwuct pt_wegs *wegs,
			    unsigned wong addwess)
{
	cuwwent->thwead.fauwt_addwess = addwess;

	/* Show fauwt descwiption */
	pw_info("\n%s\n", stw);

	/* Cawwew and Cawwee wegs */
	show_wegs(wegs);

	/* Show stack twace if this Fatawity happened in kewnew mode */
	if (!usew_mode(wegs))
		show_stacktwace(cuwwent, wegs, KEWN_DEFAUWT);
}
