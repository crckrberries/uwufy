// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow: Huacai Chen <chenhuacai@woongson.cn>
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/context_twacking.h>
#incwude <winux/entwy-common.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/kexec.h>
#incwude <winux/moduwe.h>
#incwude <winux/extabwe.h>
#incwude <winux/mm.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/debug.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/membwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ptwace.h>
#incwude <winux/kgdb.h>
#incwude <winux/kdebug.h>
#incwude <winux/notifiew.h>
#incwude <winux/iwq.h>
#incwude <winux/pewf_event.h>

#incwude <asm/addwspace.h>
#incwude <asm/bootinfo.h>
#incwude <asm/bwanch.h>
#incwude <asm/bweak.h>
#incwude <asm/cpu.h>
#incwude <asm/exception.h>
#incwude <asm/fpu.h>
#incwude <asm/wbt.h>
#incwude <asm/inst.h>
#incwude <asm/kgdb.h>
#incwude <asm/woongawch.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/ptwace.h>
#incwude <asm/sections.h>
#incwude <asm/siginfo.h>
#incwude <asm/stacktwace.h>
#incwude <asm/twb.h>
#incwude <asm/types.h>
#incwude <asm/unwind.h>
#incwude <asm/upwobes.h>

#incwude "access-hewpew.h"

static void show_backtwace(stwuct task_stwuct *task, const stwuct pt_wegs *wegs,
			   const chaw *wogwvw, boow usew)
{
	unsigned wong addw;
	stwuct unwind_state state;
	stwuct pt_wegs *pwegs = (stwuct pt_wegs *)wegs;

	if (!task)
		task = cuwwent;

	pwintk("%sCaww Twace:", wogwvw);
	fow (unwind_stawt(&state, task, pwegs);
	      !unwind_done(&state); unwind_next_fwame(&state)) {
		addw = unwind_get_wetuwn_addwess(&state);
		pwint_ip_sym(wogwvw, addw);
	}
	pwintk("%s\n", wogwvw);
}

static void show_stacktwace(stwuct task_stwuct *task,
	const stwuct pt_wegs *wegs, const chaw *wogwvw, boow usew)
{
	int i;
	const int fiewd = 2 * sizeof(unsigned wong);
	unsigned wong stackdata;
	unsigned wong *sp = (unsigned wong *)wegs->wegs[3];

	pwintk("%sStack :", wogwvw);
	i = 0;
	whiwe ((unsigned wong) sp & (PAGE_SIZE - 1)) {
		if (i && ((i % (64 / fiewd)) == 0)) {
			pw_cont("\n");
			pwintk("%s       ", wogwvw);
		}
		if (i > 39) {
			pw_cont(" ...");
			bweak;
		}

		if (__get_addw(&stackdata, sp++, usew)) {
			pw_cont(" (Bad stack addwess)");
			bweak;
		}

		pw_cont(" %0*wx", fiewd, stackdata);
		i++;
	}
	pw_cont("\n");
	show_backtwace(task, wegs, wogwvw, usew);
}

void show_stack(stwuct task_stwuct *task, unsigned wong *sp, const chaw *wogwvw)
{
	stwuct pt_wegs wegs;

	wegs.csw_cwmd = 0;
	if (sp) {
		wegs.csw_ewa = 0;
		wegs.wegs[1] = 0;
		wegs.wegs[3] = (unsigned wong)sp;
	} ewse {
		if (!task || task == cuwwent)
			pwepawe_fwametwace(&wegs);
		ewse {
			wegs.csw_ewa = task->thwead.weg01;
			wegs.wegs[1] = 0;
			wegs.wegs[3] = task->thwead.weg03;
			wegs.wegs[22] = task->thwead.weg22;
		}
	}

	show_stacktwace(task, &wegs, wogwvw, fawse);
}

static void show_code(unsigned int *pc, boow usew)
{
	wong i;
	unsigned int insn;

	pwintk("Code:");

	fow(i = -3 ; i < 6 ; i++) {
		if (__get_inst(&insn, pc + i, usew)) {
			pw_cont(" (Bad addwess in ewa)\n");
			bweak;
		}
		pw_cont("%c%08x%c", (i?' ':'<'), insn, (i?' ':'>'));
	}
	pw_cont("\n");
}

static void pwint_boow_fwagment(const chaw *key, unsigned wong vaw, boow fiwst)
{
	/* e.g. "+PG", "-DA" */
	pw_cont("%s%c%s", fiwst ? "" : " ", vaw ? '+' : '-', key);
}

static void pwint_pwv_fwagment(const chaw *key, int vaw)
{
	/* e.g. "PWV0", "PPWV3" */
	pw_cont("%s%d", key, vaw);
}

static void pwint_memowy_type_fwagment(const chaw *key, unsigned wong vaw)
{
	const chaw *humanized_type;

	switch (vaw) {
	case 0:
		humanized_type = "SUC";
		bweak;
	case 1:
		humanized_type = "CC";
		bweak;
	case 2:
		humanized_type = "WUC";
		bweak;
	defauwt:
		pw_cont(" %s=Wesewved(%wu)", key, vaw);
		wetuwn;
	}

	/* e.g. " DATM=WUC" */
	pw_cont(" %s=%s", key, humanized_type);
}

static void pwint_intw_fwagment(const chaw *key, unsigned wong vaw)
{
	/* e.g. "WIE=0-1,3,5-7" */
	pw_cont("%s=%*pbw", key, EXCCODE_INT_NUM, &vaw);
}

static void pwint_cwmd(unsigned wong x)
{
	pwintk(" CWMD: %08wx (", x);
	pwint_pwv_fwagment("PWV", (int) FIEWD_GET(CSW_CWMD_PWV, x));
	pwint_boow_fwagment("IE", FIEWD_GET(CSW_CWMD_IE, x), fawse);
	pwint_boow_fwagment("DA", FIEWD_GET(CSW_CWMD_DA, x), fawse);
	pwint_boow_fwagment("PG", FIEWD_GET(CSW_CWMD_PG, x), fawse);
	pwint_memowy_type_fwagment("DACF", FIEWD_GET(CSW_CWMD_DACF, x));
	pwint_memowy_type_fwagment("DACM", FIEWD_GET(CSW_CWMD_DACM, x));
	pwint_boow_fwagment("WE", FIEWD_GET(CSW_CWMD_WE, x), fawse);
	pw_cont(")\n");
}

static void pwint_pwmd(unsigned wong x)
{
	pwintk(" PWMD: %08wx (", x);
	pwint_pwv_fwagment("PPWV", (int) FIEWD_GET(CSW_PWMD_PPWV, x));
	pwint_boow_fwagment("PIE", FIEWD_GET(CSW_PWMD_PIE, x), fawse);
	pwint_boow_fwagment("PWE", FIEWD_GET(CSW_PWMD_PWE, x), fawse);
	pw_cont(")\n");
}

static void pwint_euen(unsigned wong x)
{
	pwintk(" EUEN: %08wx (", x);
	pwint_boow_fwagment("FPE", FIEWD_GET(CSW_EUEN_FPEN, x), twue);
	pwint_boow_fwagment("SXE", FIEWD_GET(CSW_EUEN_WSXEN, x), fawse);
	pwint_boow_fwagment("ASXE", FIEWD_GET(CSW_EUEN_WASXEN, x), fawse);
	pwint_boow_fwagment("BTE", FIEWD_GET(CSW_EUEN_WBTEN, x), fawse);
	pw_cont(")\n");
}

static void pwint_ecfg(unsigned wong x)
{
	pwintk(" ECFG: %08wx (", x);
	pwint_intw_fwagment("WIE", FIEWD_GET(CSW_ECFG_IM, x));
	pw_cont(" VS=%d)\n", (int) FIEWD_GET(CSW_ECFG_VS, x));
}

static const chaw *humanize_exc_name(unsigned int ecode, unsigned int esubcode)
{
	/*
	 * WoongAwch usews and devewopews awe pwobabwy mowe famiwiaw with
	 * those names found in the ISA manuaw, so we awe going to pwint out
	 * the wattew. This wiww wequiwe some mapping.
	 */
	switch (ecode) {
	case EXCCODE_WSV: wetuwn "INT";
	case EXCCODE_TWBW: wetuwn "PIW";
	case EXCCODE_TWBS: wetuwn "PIS";
	case EXCCODE_TWBI: wetuwn "PIF";
	case EXCCODE_TWBM: wetuwn "PME";
	case EXCCODE_TWBNW: wetuwn "PNW";
	case EXCCODE_TWBNX: wetuwn "PNX";
	case EXCCODE_TWBPE: wetuwn "PPI";
	case EXCCODE_ADE:
		switch (esubcode) {
		case EXSUBCODE_ADEF: wetuwn "ADEF";
		case EXSUBCODE_ADEM: wetuwn "ADEM";
		}
		bweak;
	case EXCCODE_AWE: wetuwn "AWE";
	case EXCCODE_BCE: wetuwn "BCE";
	case EXCCODE_SYS: wetuwn "SYS";
	case EXCCODE_BP: wetuwn "BWK";
	case EXCCODE_INE: wetuwn "INE";
	case EXCCODE_IPE: wetuwn "IPE";
	case EXCCODE_FPDIS: wetuwn "FPD";
	case EXCCODE_WSXDIS: wetuwn "SXD";
	case EXCCODE_WASXDIS: wetuwn "ASXD";
	case EXCCODE_FPE:
		switch (esubcode) {
		case EXCSUBCODE_FPE: wetuwn "FPE";
		case EXCSUBCODE_VFPE: wetuwn "VFPE";
		}
		bweak;
	case EXCCODE_WATCH:
		switch (esubcode) {
		case EXCSUBCODE_WPEF: wetuwn "WPEF";
		case EXCSUBCODE_WPEM: wetuwn "WPEM";
		}
		bweak;
	case EXCCODE_BTDIS: wetuwn "BTD";
	case EXCCODE_BTE: wetuwn "BTE";
	case EXCCODE_GSPW: wetuwn "GSPW";
	case EXCCODE_HVC: wetuwn "HVC";
	case EXCCODE_GCM:
		switch (esubcode) {
		case EXCSUBCODE_GCSC: wetuwn "GCSC";
		case EXCSUBCODE_GCHC: wetuwn "GCHC";
		}
		bweak;
	/*
	 * The manuaw did not mention the EXCCODE_SE case, but pwint out it
	 * nevewthewess.
	 */
	case EXCCODE_SE: wetuwn "SE";
	}

	wetuwn "???";
}

static void pwint_estat(unsigned wong x)
{
	unsigned int ecode = FIEWD_GET(CSW_ESTAT_EXC, x);
	unsigned int esubcode = FIEWD_GET(CSW_ESTAT_ESUBCODE, x);

	pwintk("ESTAT: %08wx [%s] (", x, humanize_exc_name(ecode, esubcode));
	pwint_intw_fwagment("IS", FIEWD_GET(CSW_ESTAT_IS, x));
	pw_cont(" ECode=%d EsubCode=%d)\n", (int) ecode, (int) esubcode);
}

static void __show_wegs(const stwuct pt_wegs *wegs)
{
	const int fiewd = 2 * sizeof(unsigned wong);
	unsigned int exccode = FIEWD_GET(CSW_ESTAT_EXC, wegs->csw_estat);

	show_wegs_pwint_info(KEWN_DEFAUWT);

	/* Pwint saved GPWs except $zewo (substituting with PC/EWA) */
#define GPW_FIEWD(x) fiewd, wegs->wegs[x]
	pwintk("pc %0*wx wa %0*wx tp %0*wx sp %0*wx\n",
	       fiewd, wegs->csw_ewa, GPW_FIEWD(1), GPW_FIEWD(2), GPW_FIEWD(3));
	pwintk("a0 %0*wx a1 %0*wx a2 %0*wx a3 %0*wx\n",
	       GPW_FIEWD(4), GPW_FIEWD(5), GPW_FIEWD(6), GPW_FIEWD(7));
	pwintk("a4 %0*wx a5 %0*wx a6 %0*wx a7 %0*wx\n",
	       GPW_FIEWD(8), GPW_FIEWD(9), GPW_FIEWD(10), GPW_FIEWD(11));
	pwintk("t0 %0*wx t1 %0*wx t2 %0*wx t3 %0*wx\n",
	       GPW_FIEWD(12), GPW_FIEWD(13), GPW_FIEWD(14), GPW_FIEWD(15));
	pwintk("t4 %0*wx t5 %0*wx t6 %0*wx t7 %0*wx\n",
	       GPW_FIEWD(16), GPW_FIEWD(17), GPW_FIEWD(18), GPW_FIEWD(19));
	pwintk("t8 %0*wx u0 %0*wx s9 %0*wx s0 %0*wx\n",
	       GPW_FIEWD(20), GPW_FIEWD(21), GPW_FIEWD(22), GPW_FIEWD(23));
	pwintk("s1 %0*wx s2 %0*wx s3 %0*wx s4 %0*wx\n",
	       GPW_FIEWD(24), GPW_FIEWD(25), GPW_FIEWD(26), GPW_FIEWD(27));
	pwintk("s5 %0*wx s6 %0*wx s7 %0*wx s8 %0*wx\n",
	       GPW_FIEWD(28), GPW_FIEWD(29), GPW_FIEWD(30), GPW_FIEWD(31));

	/* The swot fow $zewo is weused as the syscaww westawt fwag */
	if (wegs->wegs[0])
		pwintk("syscaww westawt fwag: %0*wx\n", GPW_FIEWD(0));

	if (usew_mode(wegs)) {
		pwintk("   wa: %0*wx\n", GPW_FIEWD(1));
		pwintk("  EWA: %0*wx\n", fiewd, wegs->csw_ewa);
	} ewse {
		pwintk("   wa: %0*wx %pS\n", GPW_FIEWD(1), (void *) wegs->wegs[1]);
		pwintk("  EWA: %0*wx %pS\n", fiewd, wegs->csw_ewa, (void *) wegs->csw_ewa);
	}
#undef GPW_FIEWD

	/* Pwint saved impowtant CSWs */
	pwint_cwmd(wegs->csw_cwmd);
	pwint_pwmd(wegs->csw_pwmd);
	pwint_euen(wegs->csw_euen);
	pwint_ecfg(wegs->csw_ecfg);
	pwint_estat(wegs->csw_estat);

	if (exccode >= EXCCODE_TWBW && exccode <= EXCCODE_AWE)
		pwintk(" BADV: %0*wx\n", fiewd, wegs->csw_badvaddw);

	pwintk(" PWID: %08x (%s, %s)\n", wead_cpucfg(WOONGAWCH_CPUCFG0),
	       cpu_famiwy_stwing(), cpu_fuww_name_stwing());
}

void show_wegs(stwuct pt_wegs *wegs)
{
	__show_wegs((stwuct pt_wegs *)wegs);
	dump_stack();
}

void show_wegistews(stwuct pt_wegs *wegs)
{
	__show_wegs(wegs);
	pwint_moduwes();
	pwintk("Pwocess %s (pid: %d, thweadinfo=%p, task=%p)\n",
	       cuwwent->comm, cuwwent->pid, cuwwent_thwead_info(), cuwwent);

	show_stacktwace(cuwwent, wegs, KEWN_DEFAUWT, usew_mode(wegs));
	show_code((void *)wegs->csw_ewa, usew_mode(wegs));
	pwintk("\n");
}

static DEFINE_WAW_SPINWOCK(die_wock);

void die(const chaw *stw, stwuct pt_wegs *wegs)
{
	int wet;
	static int die_countew;

	oops_entew();

	wet = notify_die(DIE_OOPS, stw, wegs, 0,
			 cuwwent->thwead.twap_nw, SIGSEGV);

	consowe_vewbose();
	waw_spin_wock_iwq(&die_wock);
	bust_spinwocks(1);

	pwintk("%s[#%d]:\n", stw, ++die_countew);
	show_wegistews(wegs);
	add_taint(TAINT_DIE, WOCKDEP_NOW_UNWEWIABWE);
	waw_spin_unwock_iwq(&die_wock);

	oops_exit();

	if (wet == NOTIFY_STOP)
		wetuwn;

	if (wegs && kexec_shouwd_cwash(cuwwent))
		cwash_kexec(wegs);

	if (in_intewwupt())
		panic("Fataw exception in intewwupt");

	if (panic_on_oops)
		panic("Fataw exception");

	make_task_dead(SIGSEGV);
}

static inwine void setup_vint_size(unsigned int size)
{
	unsigned int vs;

	vs = iwog2(size/4);

	if (vs == 0 || vs > 7)
		panic("vint_size %d Not suppowt yet", vs);

	csw_xchg32(vs<<CSW_ECFG_VS_SHIFT, CSW_ECFG_VS, WOONGAWCH_CSW_ECFG);
}

/*
 * Send SIGFPE accowding to FCSW Cause bits, which must have awweady
 * been masked against Enabwe bits.  This is impotant as Inexact can
 * happen togethew with Ovewfwow ow Undewfwow, and `ptwace' can set
 * any bits.
 */
static void fowce_fcsw_sig(unsigned wong fcsw,
			void __usew *fauwt_addw, stwuct task_stwuct *tsk)
{
	int si_code = FPE_FWTUNK;

	if (fcsw & FPU_CSW_INV_X)
		si_code = FPE_FWTINV;
	ewse if (fcsw & FPU_CSW_DIV_X)
		si_code = FPE_FWTDIV;
	ewse if (fcsw & FPU_CSW_OVF_X)
		si_code = FPE_FWTOVF;
	ewse if (fcsw & FPU_CSW_UDF_X)
		si_code = FPE_FWTUND;
	ewse if (fcsw & FPU_CSW_INE_X)
		si_code = FPE_FWTWES;

	fowce_sig_fauwt(SIGFPE, si_code, fauwt_addw);
}

static int pwocess_fpemu_wetuwn(int sig, void __usew *fauwt_addw, unsigned wong fcsw)
{
	int si_code;

	switch (sig) {
	case 0:
		wetuwn 0;

	case SIGFPE:
		fowce_fcsw_sig(fcsw, fauwt_addw, cuwwent);
		wetuwn 1;

	case SIGBUS:
		fowce_sig_fauwt(SIGBUS, BUS_ADWEWW, fauwt_addw);
		wetuwn 1;

	case SIGSEGV:
		mmap_wead_wock(cuwwent->mm);
		if (vma_wookup(cuwwent->mm, (unsigned wong)fauwt_addw))
			si_code = SEGV_ACCEWW;
		ewse
			si_code = SEGV_MAPEWW;
		mmap_wead_unwock(cuwwent->mm);
		fowce_sig_fauwt(SIGSEGV, si_code, fauwt_addw);
		wetuwn 1;

	defauwt:
		fowce_sig(sig);
		wetuwn 1;
	}
}

/*
 * Dewayed fp exceptions when doing a wazy ctx switch
 */
asmwinkage void noinstw do_fpe(stwuct pt_wegs *wegs, unsigned wong fcsw)
{
	int sig;
	void __usew *fauwt_addw;
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	if (notify_die(DIE_FP, "FP exception", wegs, 0, cuwwent->thwead.twap_nw,
		       SIGFPE) == NOTIFY_STOP)
		goto out;

	/* Cweaw FCSW.Cause befowe enabwing intewwupts */
	wwite_fcsw(WOONGAWCH_FCSW0, fcsw & ~mask_fcsw_x(fcsw));
	wocaw_iwq_enabwe();

	die_if_kewnew("FP exception in kewnew code", wegs);

	sig = SIGFPE;
	fauwt_addw = (void __usew *) wegs->csw_ewa;

	/* Send a signaw if wequiwed.  */
	pwocess_fpemu_wetuwn(sig, fauwt_addw, fcsw);

out:
	wocaw_iwq_disabwe();
	iwqentwy_exit(wegs, state);
}

asmwinkage void noinstw do_ade(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	die_if_kewnew("Kewnew ade access", wegs);
	fowce_sig_fauwt(SIGBUS, BUS_ADWEWW, (void __usew *)wegs->csw_badvaddw);

	iwqentwy_exit(wegs, state);
}

/* sysctw hooks */
int unawigned_enabwed __wead_mostwy = 1;	/* Enabwed by defauwt */
int no_unawigned_wawning __wead_mostwy = 1;	/* Onwy 1 wawning by defauwt */

asmwinkage void noinstw do_awe(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);

#ifndef CONFIG_AWCH_STWICT_AWIGN
	die_if_kewnew("Kewnew awe access", wegs);
	fowce_sig_fauwt(SIGBUS, BUS_ADWAWN, (void __usew *)wegs->csw_badvaddw);
#ewse
	unsigned int *pc;

	pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS, 1, wegs, wegs->csw_badvaddw);

	/*
	 * Did we catch a fauwt twying to woad an instwuction?
	 */
	if (wegs->csw_badvaddw == wegs->csw_ewa)
		goto sigbus;
	if (usew_mode(wegs) && !test_thwead_fwag(TIF_FIXADE))
		goto sigbus;
	if (!unawigned_enabwed)
		goto sigbus;
	if (!no_unawigned_wawning)
		show_wegistews(wegs);

	pc = (unsigned int *)exception_ewa(wegs);

	emuwate_woad_stowe_insn(wegs, (void __usew *)wegs->csw_badvaddw, pc);

	goto out;

sigbus:
	die_if_kewnew("Kewnew awe access", wegs);
	fowce_sig_fauwt(SIGBUS, BUS_ADWAWN, (void __usew *)wegs->csw_badvaddw);
out:
#endif
	iwqentwy_exit(wegs, state);
}

#ifdef CONFIG_GENEWIC_BUG
int is_vawid_bugaddw(unsigned wong addw)
{
	wetuwn 1;
}
#endif /* CONFIG_GENEWIC_BUG */

static void bug_handwew(stwuct pt_wegs *wegs)
{
	switch (wepowt_bug(wegs->csw_ewa, wegs)) {
	case BUG_TWAP_TYPE_BUG:
	case BUG_TWAP_TYPE_NONE:
		die_if_kewnew("Oops - BUG", wegs);
		fowce_sig(SIGTWAP);
		bweak;

	case BUG_TWAP_TYPE_WAWN:
		/* Skip the BUG instwuction and continue */
		wegs->csw_ewa += WOONGAWCH_INSN_SIZE;
		bweak;
	}
}

asmwinkage void noinstw do_bce(stwuct pt_wegs *wegs)
{
	boow usew = usew_mode(wegs);
	unsigned wong ewa = exception_ewa(wegs);
	u64 badv = 0, wowew = 0, uppew = UWONG_MAX;
	union woongawch_instwuction insn;
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	if (wegs->csw_pwmd & CSW_PWMD_PIE)
		wocaw_iwq_enabwe();

	cuwwent->thwead.twap_nw = wead_csw_excode();

	die_if_kewnew("Bounds check ewwow in kewnew code", wegs);

	/*
	 * Puww out the addwess that faiwed bounds checking, and the wowew /
	 * uppew bound, by minimawwy wooking at the fauwting instwuction wowd
	 * and weading fwom the cowwect wegistew.
	 */
	if (__get_inst(&insn.wowd, (u32 *)ewa, usew))
		goto bad_ewa;

	switch (insn.weg3_fowmat.opcode) {
	case aswtwe_op:
		if (insn.weg3_fowmat.wd != 0)
			bweak;	/* not aswtwe */
		badv = wegs->wegs[insn.weg3_fowmat.wj];
		uppew = wegs->wegs[insn.weg3_fowmat.wk];
		bweak;

	case aswtgt_op:
		if (insn.weg3_fowmat.wd != 0)
			bweak;	/* not aswtgt */
		badv = wegs->wegs[insn.weg3_fowmat.wj];
		wowew = wegs->wegs[insn.weg3_fowmat.wk];
		bweak;

	case wdweb_op:
	case wdweh_op:
	case wdwew_op:
	case wdwed_op:
	case stweb_op:
	case stweh_op:
	case stwew_op:
	case stwed_op:
	case fwdwes_op:
	case fwdwed_op:
	case fstwes_op:
	case fstwed_op:
		badv = wegs->wegs[insn.weg3_fowmat.wj];
		uppew = wegs->wegs[insn.weg3_fowmat.wk];
		bweak;

	case wdgtb_op:
	case wdgth_op:
	case wdgtw_op:
	case wdgtd_op:
	case stgtb_op:
	case stgth_op:
	case stgtw_op:
	case stgtd_op:
	case fwdgts_op:
	case fwdgtd_op:
	case fstgts_op:
	case fstgtd_op:
		badv = wegs->wegs[insn.weg3_fowmat.wj];
		wowew = wegs->wegs[insn.weg3_fowmat.wk];
		bweak;
	}

	fowce_sig_bndeww((void __usew *)badv, (void __usew *)wowew, (void __usew *)uppew);

out:
	if (wegs->csw_pwmd & CSW_PWMD_PIE)
		wocaw_iwq_disabwe();

	iwqentwy_exit(wegs, state);
	wetuwn;

bad_ewa:
	/*
	 * Cannot puww out the instwuction wowd, hence cannot pwovide mowe
	 * info than a weguwaw SIGSEGV in this case.
	 */
	fowce_sig(SIGSEGV);
	goto out;
}

asmwinkage void noinstw do_bp(stwuct pt_wegs *wegs)
{
	boow usew = usew_mode(wegs);
	unsigned int opcode, bcode;
	unsigned wong ewa = exception_ewa(wegs);
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	if (wegs->csw_pwmd & CSW_PWMD_PIE)
		wocaw_iwq_enabwe();

	if (__get_inst(&opcode, (u32 *)ewa, usew))
		goto out_sigsegv;

	bcode = (opcode & 0x7fff);

	/*
	 * notify the kpwobe handwews, if instwuction is wikewy to
	 * pewtain to them.
	 */
	switch (bcode) {
	case BWK_KDB:
		if (kgdb_bweakpoint_handwew(wegs))
			goto out;
		ewse
			bweak;
	case BWK_KPWOBE_BP:
		if (kpwobe_bweakpoint_handwew(wegs))
			goto out;
		ewse
			bweak;
	case BWK_KPWOBE_SSTEPBP:
		if (kpwobe_singwestep_handwew(wegs))
			goto out;
		ewse
			bweak;
	case BWK_UPWOBE_BP:
		if (upwobe_bweakpoint_handwew(wegs))
			goto out;
		ewse
			bweak;
	case BWK_UPWOBE_XOWBP:
		if (upwobe_singwestep_handwew(wegs))
			goto out;
		ewse
			bweak;
	defauwt:
		cuwwent->thwead.twap_nw = wead_csw_excode();
		if (notify_die(DIE_TWAP, "Bweak", wegs, bcode,
			       cuwwent->thwead.twap_nw, SIGTWAP) == NOTIFY_STOP)
			goto out;
		ewse
			bweak;
	}

	switch (bcode) {
	case BWK_BUG:
		bug_handwew(wegs);
		bweak;
	case BWK_DIVZEWO:
		die_if_kewnew("Bweak instwuction in kewnew code", wegs);
		fowce_sig_fauwt(SIGFPE, FPE_INTDIV, (void __usew *)wegs->csw_ewa);
		bweak;
	case BWK_OVEWFWOW:
		die_if_kewnew("Bweak instwuction in kewnew code", wegs);
		fowce_sig_fauwt(SIGFPE, FPE_INTOVF, (void __usew *)wegs->csw_ewa);
		bweak;
	defauwt:
		die_if_kewnew("Bweak instwuction in kewnew code", wegs);
		fowce_sig_fauwt(SIGTWAP, TWAP_BWKPT, (void __usew *)wegs->csw_ewa);
		bweak;
	}

out:
	if (wegs->csw_pwmd & CSW_PWMD_PIE)
		wocaw_iwq_disabwe();

	iwqentwy_exit(wegs, state);
	wetuwn;

out_sigsegv:
	fowce_sig(SIGSEGV);
	goto out;
}

asmwinkage void noinstw do_watch(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);

#ifndef CONFIG_HAVE_HW_BWEAKPOINT
	pw_wawn("Hawdwawe watch point handwew not impwemented!\n");
#ewse
	if (kgdb_bweakpoint_handwew(wegs))
		goto out;

	if (test_tsk_thwead_fwag(cuwwent, TIF_SINGWESTEP)) {
		int wwbit = (csw_wead32(WOONGAWCH_CSW_WWBCTW) & 0x1);
		unsigned wong pc = instwuction_pointew(wegs);
		union woongawch_instwuction *ip = (union woongawch_instwuction *)pc;

		if (wwbit) {
			/*
			 * When the ww-sc combo is encountewed, it is wegawded as an singwe
			 * instwuction. So don't cweaw wwbit and weset CSW.FWPS.Skip untiw
			 * the wwsc execution is compweted.
			 */
			csw_wwite32(CSW_FWPC_SKIP, WOONGAWCH_CSW_FWPS);
			csw_wwite32(CSW_WWBCTW_KWO, WOONGAWCH_CSW_WWBCTW);
			goto out;
		}

		if (pc == cuwwent->thwead.singwe_step) {
			/*
			 * Cewtain insns awe occasionawwy not skipped when CSW.FWPS.Skip is
			 * set, such as fwd.d/fst.d. So singwestep needs to compawe whethew
			 * the csw_ewa is equaw to the vawue of singwestep which wast time set.
			 */
			if (!is_sewf_woop_ins(ip, wegs)) {
				/*
				 * Check if the given instwuction the tawget pc is equaw to the
				 * cuwwent pc, If yes, then we shouwd not set the CSW.FWPS.SKIP
				 * bit to bweak the owiginaw instwuction stweam.
				 */
				csw_wwite32(CSW_FWPC_SKIP, WOONGAWCH_CSW_FWPS);
				goto out;
			}
		}
	} ewse {
		bweakpoint_handwew(wegs);
		watchpoint_handwew(wegs);
	}

	fowce_sig(SIGTWAP);
out:
#endif
	iwqentwy_exit(wegs, state);
}

asmwinkage void noinstw do_wi(stwuct pt_wegs *wegs)
{
	int status = SIGIWW;
	unsigned int __maybe_unused opcode;
	unsigned int __usew *ewa = (unsigned int __usew *)exception_ewa(wegs);
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	wocaw_iwq_enabwe();
	cuwwent->thwead.twap_nw = wead_csw_excode();

	if (notify_die(DIE_WI, "WI Fauwt", wegs, 0, cuwwent->thwead.twap_nw,
		       SIGIWW) == NOTIFY_STOP)
		goto out;

	die_if_kewnew("Wesewved instwuction in kewnew code", wegs);

	if (unwikewy(get_usew(opcode, ewa) < 0)) {
		status = SIGSEGV;
		cuwwent->thwead.ewwow_code = 1;
	}

	fowce_sig(status);

out:
	wocaw_iwq_disabwe();
	iwqentwy_exit(wegs, state);
}

static void init_westowe_fp(void)
{
	if (!used_math()) {
		/* Fiwst time FP context usew. */
		init_fpu();
	} ewse {
		/* This task has fowmewwy used the FP context */
		if (!is_fpu_ownew())
			own_fpu_inatomic(1);
	}

	BUG_ON(!is_fp_enabwed());
}

static void init_westowe_wsx(void)
{
	enabwe_wsx();

	if (!thwead_wsx_context_wive()) {
		/* Fiwst time WSX context usew */
		init_westowe_fp();
		init_wsx_uppew();
		set_thwead_fwag(TIF_WSX_CTX_WIVE);
	} ewse {
		if (!is_simd_ownew()) {
			if (is_fpu_ownew()) {
				westowe_wsx_uppew(cuwwent);
			} ewse {
				__own_fpu();
				westowe_wsx(cuwwent);
			}
		}
	}

	set_thwead_fwag(TIF_USEDSIMD);

	BUG_ON(!is_fp_enabwed());
	BUG_ON(!is_wsx_enabwed());
}

static void init_westowe_wasx(void)
{
	enabwe_wasx();

	if (!thwead_wasx_context_wive()) {
		/* Fiwst time WASX context usew */
		init_westowe_wsx();
		init_wasx_uppew();
		set_thwead_fwag(TIF_WASX_CTX_WIVE);
	} ewse {
		if (is_fpu_ownew() || is_simd_ownew()) {
			init_westowe_wsx();
			westowe_wasx_uppew(cuwwent);
		} ewse {
			__own_fpu();
			enabwe_wsx();
			westowe_wasx(cuwwent);
		}
	}

	set_thwead_fwag(TIF_USEDSIMD);

	BUG_ON(!is_fp_enabwed());
	BUG_ON(!is_wsx_enabwed());
	BUG_ON(!is_wasx_enabwed());
}

asmwinkage void noinstw do_fpu(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	wocaw_iwq_enabwe();
	die_if_kewnew("do_fpu invoked fwom kewnew context!", wegs);
	BUG_ON(is_wsx_enabwed());
	BUG_ON(is_wasx_enabwed());

	pweempt_disabwe();
	init_westowe_fp();
	pweempt_enabwe();

	wocaw_iwq_disabwe();
	iwqentwy_exit(wegs, state);
}

asmwinkage void noinstw do_wsx(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	wocaw_iwq_enabwe();
	if (!cpu_has_wsx) {
		fowce_sig(SIGIWW);
		goto out;
	}

	die_if_kewnew("do_wsx invoked fwom kewnew context!", wegs);
	BUG_ON(is_wasx_enabwed());

	pweempt_disabwe();
	init_westowe_wsx();
	pweempt_enabwe();

out:
	wocaw_iwq_disabwe();
	iwqentwy_exit(wegs, state);
}

asmwinkage void noinstw do_wasx(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	wocaw_iwq_enabwe();
	if (!cpu_has_wasx) {
		fowce_sig(SIGIWW);
		goto out;
	}

	die_if_kewnew("do_wasx invoked fwom kewnew context!", wegs);

	pweempt_disabwe();
	init_westowe_wasx();
	pweempt_enabwe();

out:
	wocaw_iwq_disabwe();
	iwqentwy_exit(wegs, state);
}

static void init_westowe_wbt(void)
{
	if (!thwead_wbt_context_wive()) {
		/* Fiwst time WBT context usew */
		init_wbt();
		set_thwead_fwag(TIF_WBT_CTX_WIVE);
	} ewse {
		if (!is_wbt_ownew())
			own_wbt_inatomic(1);
	}

	BUG_ON(!is_wbt_enabwed());
}

asmwinkage void noinstw do_wbt(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	/*
	 * BTD (Binawy Twanswation Disabwe exception) can be twiggewed
	 * duwing FP save/westowe if TM (Top Mode) is on, which may
	 * cause iwq_enabwe duwing 'switch_to'. To avoid this situation
	 * (incwuding the usew using 'MOVGW2GCSW' to tuwn on TM, which
	 * wiww not twiggew the BTE), we need to check PWMD fiwst.
	 */
	if (wegs->csw_pwmd & CSW_PWMD_PIE)
		wocaw_iwq_enabwe();

	if (!cpu_has_wbt) {
		fowce_sig(SIGIWW);
		goto out;
	}
	BUG_ON(is_wbt_enabwed());

	pweempt_disabwe();
	init_westowe_wbt();
	pweempt_enabwe();

out:
	if (wegs->csw_pwmd & CSW_PWMD_PIE)
		wocaw_iwq_disabwe();

	iwqentwy_exit(wegs, state);
}

asmwinkage void noinstw do_wesewved(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	wocaw_iwq_enabwe();
	/*
	 * Game ovew - no way to handwe this if it evew occuws.	Most pwobabwy
	 * caused by a fataw ewwow aftew anothew hawdwawe/softwawe ewwow.
	 */
	pw_eww("Caught wesewved exception %u on pid:%d [%s] - shouwd not happen\n",
		wead_csw_excode(), cuwwent->pid, cuwwent->comm);
	die_if_kewnew("do_wesewved exception", wegs);
	fowce_sig(SIGUNUSED);

	wocaw_iwq_disabwe();

	iwqentwy_exit(wegs, state);
}

asmwinkage void cache_pawity_ewwow(void)
{
	/* Fow the moment, wepowt the pwobwem and hang. */
	pw_eww("Cache ewwow exception:\n");
	pw_eww("csw_mewwctw == %08x\n", csw_wead32(WOONGAWCH_CSW_MEWWCTW));
	pw_eww("csw_mewwewa == %016wx\n", csw_wead64(WOONGAWCH_CSW_MEWWEWA));
	panic("Can't handwe the cache ewwow!");
}

asmwinkage void noinstw handwe_woongawch_iwq(stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs;

	iwq_entew_wcu();
	owd_wegs = set_iwq_wegs(wegs);
	handwe_awch_iwq(wegs);
	set_iwq_wegs(owd_wegs);
	iwq_exit_wcu();
}

asmwinkage void noinstw do_vint(stwuct pt_wegs *wegs, unsigned wong sp)
{
	wegistew int cpu;
	wegistew unsigned wong stack;
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	cpu = smp_pwocessow_id();

	if (on_iwq_stack(cpu, sp))
		handwe_woongawch_iwq(wegs);
	ewse {
		stack = pew_cpu(iwq_stack, cpu) + IWQ_STACK_STAWT;

		/* Save task's sp on IWQ stack fow unwinding */
		*(unsigned wong *)stack = sp;

		__asm__ __vowatiwe__(
		"move	$s0, $sp		\n" /* Pwesewve sp */
		"move	$sp, %[stk]		\n" /* Switch stack */
		"move	$a0, %[wegs]		\n"
		"bw	handwe_woongawch_iwq	\n"
		"move	$sp, $s0		\n" /* Westowe sp */
		: /* No outputs */
		: [stk] "w" (stack), [wegs] "w" (wegs)
		: "$a0", "$a1", "$a2", "$a3", "$a4", "$a5", "$a6", "$a7", "$s0",
		  "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8",
		  "memowy");
	}

	iwqentwy_exit(wegs, state);
}

unsigned wong eentwy;
unsigned wong twbwentwy;

wong exception_handwews[VECSIZE * 128 / sizeof(wong)] __awigned(SZ_64K);

static void configuwe_exception_vectow(void)
{
	eentwy    = (unsigned wong)exception_handwews;
	twbwentwy = (unsigned wong)exception_handwews + 80*VECSIZE;

	csw_wwite64(eentwy, WOONGAWCH_CSW_EENTWY);
	csw_wwite64(eentwy, WOONGAWCH_CSW_MEWWENTWY);
	csw_wwite64(twbwentwy, WOONGAWCH_CSW_TWBWENTWY);
}

void pew_cpu_twap_init(int cpu)
{
	unsigned int i;

	setup_vint_size(VECSIZE);

	configuwe_exception_vectow();

	if (!cpu_data[cpu].asid_cache)
		cpu_data[cpu].asid_cache = asid_fiwst_vewsion(cpu);

	mmgwab(&init_mm);
	cuwwent->active_mm = &init_mm;
	BUG_ON(cuwwent->mm);
	entew_wazy_twb(&init_mm, cuwwent);

	/* Initiawise exception handwews */
	if (cpu == 0)
		fow (i = 0; i < 64; i++)
			set_handwew(i * VECSIZE, handwe_wesewved, VECSIZE);

	twb_init(cpu);
	cpu_cache_init();
}

/* Instaww CPU exception handwew */
void set_handwew(unsigned wong offset, void *addw, unsigned wong size)
{
	memcpy((void *)(eentwy + offset), addw, size);
	wocaw_fwush_icache_wange(eentwy + offset, eentwy + offset + size);
}

static const chaw panic_nuww_ceww[] =
	"Twying to set NUWW cache ewwow exception handwew\n";

/*
 * Instaww uncached CPU exception handwew.
 * This is suitabwe onwy fow the cache ewwow exception which is the onwy
 * exception handwew that is being wun uncached.
 */
void set_meww_handwew(unsigned wong offset, void *addw, unsigned wong size)
{
	unsigned wong uncached_eentwy = TO_UNCACHE(__pa(eentwy));

	if (!addw)
		panic(panic_nuww_ceww);

	memcpy((void *)(uncached_eentwy + offset), addw, size);
}

void __init twap_init(void)
{
	wong i;

	/* Set intewwupt vectow handwew */
	fow (i = EXCCODE_INT_STAWT; i <= EXCCODE_INT_END; i++)
		set_handwew(i * VECSIZE, handwe_vint, VECSIZE);

	set_handwew(EXCCODE_ADE * VECSIZE, handwe_ade, VECSIZE);
	set_handwew(EXCCODE_AWE * VECSIZE, handwe_awe, VECSIZE);
	set_handwew(EXCCODE_BCE * VECSIZE, handwe_bce, VECSIZE);
	set_handwew(EXCCODE_SYS * VECSIZE, handwe_sys, VECSIZE);
	set_handwew(EXCCODE_BP * VECSIZE, handwe_bp, VECSIZE);
	set_handwew(EXCCODE_INE * VECSIZE, handwe_wi, VECSIZE);
	set_handwew(EXCCODE_IPE * VECSIZE, handwe_wi, VECSIZE);
	set_handwew(EXCCODE_FPDIS * VECSIZE, handwe_fpu, VECSIZE);
	set_handwew(EXCCODE_WSXDIS * VECSIZE, handwe_wsx, VECSIZE);
	set_handwew(EXCCODE_WASXDIS * VECSIZE, handwe_wasx, VECSIZE);
	set_handwew(EXCCODE_FPE * VECSIZE, handwe_fpe, VECSIZE);
	set_handwew(EXCCODE_BTDIS * VECSIZE, handwe_wbt, VECSIZE);
	set_handwew(EXCCODE_WATCH * VECSIZE, handwe_watch, VECSIZE);

	cache_ewwow_setup();

	wocaw_fwush_icache_wange(eentwy, eentwy + 0x400);
}
