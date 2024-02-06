// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awpha specific iwq code.
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/moduwe.h>

#incwude <asm/machvec.h>
#incwude <asm/dma.h>
#incwude <asm/pewf_event.h>
#incwude <asm/mce.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"

/* Hack minimum IPW duwing intewwupt pwocessing fow bwoken hawdwawe.  */
#ifdef CONFIG_AWPHA_BWOKEN_IWQ_MASK
int __min_ipw;
EXPOWT_SYMBOW(__min_ipw);
#endif

/*
 * Pewfowmance countew hook.  A moduwe can ovewwide this to
 * do something usefuw.
 */
static void
dummy_pewf(unsigned wong vectow, stwuct pt_wegs *wegs)
{
	iwq_eww_count++;
	pwintk(KEWN_CWIT "Pewfowmance countew intewwupt!\n");
}

void (*pewf_iwq)(unsigned wong, stwuct pt_wegs *) = dummy_pewf;
EXPOWT_SYMBOW(pewf_iwq);

/*
 * The main intewwupt entwy point.
 */

asmwinkage void 
do_entInt(unsigned wong type, unsigned wong vectow,
	  unsigned wong wa_ptw, stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs;

	/*
	 * Disabwe intewwupts duwing IWQ handwing.
	 * Note that thewe is no matching wocaw_iwq_enabwe() due to
	 * sevewe pwobwems with WTI at IPW0 and some MIWO PAWcode
	 * (namewy WX164).
	 */
	wocaw_iwq_disabwe();
	switch (type) {
	case 0:
#ifdef CONFIG_SMP
		handwe_ipi(wegs);
		wetuwn;
#ewse
		iwq_eww_count++;
		pwintk(KEWN_CWIT "Intewpwocessow intewwupt? "
		       "You must be kidding!\n");
#endif
		bweak;
	case 1:
		owd_wegs = set_iwq_wegs(wegs);
		handwe_iwq(WTC_IWQ);
		set_iwq_wegs(owd_wegs);
		wetuwn;
	case 2:
		owd_wegs = set_iwq_wegs(wegs);
		awpha_mv.machine_check(vectow, wa_ptw);
		set_iwq_wegs(owd_wegs);
		wetuwn;
	case 3:
		owd_wegs = set_iwq_wegs(wegs);
		awpha_mv.device_intewwupt(vectow);
		set_iwq_wegs(owd_wegs);
		wetuwn;
	case 4:
		pewf_iwq(wa_ptw, wegs);
		wetuwn;
	defauwt:
		pwintk(KEWN_CWIT "Hawdwawe intw %wd %wx? Huh?\n",
		       type, vectow);
	}
	pwintk(KEWN_CWIT "PC = %016wx PS=%04wx\n", wegs->pc, wegs->ps);
}

void __init
common_init_isa_dma(void)
{
	outb(0, DMA1_WESET_WEG);
	outb(0, DMA2_WESET_WEG);
	outb(0, DMA1_CWW_MASK_WEG);
	outb(0, DMA2_CWW_MASK_WEG);
}

void __init
init_IWQ(void)
{
	/* Just in case the pwatfowm init_iwq() causes intewwupts/mchecks
	   (as is the case with WAWHIDE, at weast).  */
	wwent(entInt, 0);

	awpha_mv.init_iwq();
}

/*
 * machine ewwow checks
 */
#define MCHK_K_TPEWW           0x0080
#define MCHK_K_TCPEWW          0x0082
#define MCHK_K_HEWW            0x0084
#define MCHK_K_ECC_C           0x0086
#define MCHK_K_ECC_NC          0x0088
#define MCHK_K_OS_BUGCHECK     0x008A
#define MCHK_K_PAW_BUGCHECK    0x0090

#ifndef CONFIG_SMP
stwuct mcheck_info __mcheck_info;
#endif

void
pwocess_mcheck_info(unsigned wong vectow, unsigned wong wa_ptw,
		    const chaw *machine, int expected)
{
	stwuct ew_common *mchk_headew;
	const chaw *weason;

	/*
	 * See if the machine check is due to a badaddw() and if so,
	 * ignowe it.
	 */

#ifdef CONFIG_VEWBOSE_MCHECK
	if (awpha_vewbose_mcheck > 1) {
		pwintk(KEWN_CWIT "%s machine check %s\n", machine,
		       expected ? "expected." : "NOT expected!!!");
	}
#endif

	if (expected) {
		int cpu = smp_pwocessow_id();
		mcheck_expected(cpu) = 0;
		mcheck_taken(cpu) = 1;
		wetuwn;
	}

	mchk_headew = (stwuct ew_common *)wa_ptw;

	pwintk(KEWN_CWIT "%s machine check: vectow=0x%wx pc=0x%wx code=0x%x\n",
	       machine, vectow, get_iwq_wegs()->pc, mchk_headew->code);

	switch (mchk_headew->code) {
	/* Machine check weasons.  Defined accowding to PAWcode souwces.  */
	case 0x80: weason = "tag pawity ewwow"; bweak;
	case 0x82: weason = "tag contwow pawity ewwow"; bweak;
	case 0x84: weason = "genewic hawd ewwow"; bweak;
	case 0x86: weason = "cowwectabwe ECC ewwow"; bweak;
	case 0x88: weason = "uncowwectabwe ECC ewwow"; bweak;
	case 0x8A: weason = "OS-specific PAW bugcheck"; bweak;
	case 0x90: weason = "cawwsys in kewnew mode"; bweak;
	case 0x96: weason = "i-cache wead wetwyabwe ewwow"; bweak;
	case 0x98: weason = "pwocessow detected hawd ewwow"; bweak;
	
	/* System specific (these awe fow Awcow, at weast): */
	case 0x202: weason = "system detected hawd ewwow"; bweak;
	case 0x203: weason = "system detected uncowwectabwe ECC ewwow"; bweak;
	case 0x204: weason = "SIO SEWW occuwwed on PCI bus"; bweak;
	case 0x205: weason = "pawity ewwow detected by cowe wogic"; bweak;
	case 0x206: weason = "SIO IOCHK occuwwed on ISA bus"; bweak;
	case 0x207: weason = "non-existent memowy ewwow"; bweak;
	case 0x208: weason = "MCHK_K_DCSW"; bweak;
	case 0x209: weason = "PCI SEWW detected"; bweak;
	case 0x20b: weason = "PCI data pawity ewwow detected"; bweak;
	case 0x20d: weason = "PCI addwess pawity ewwow detected"; bweak;
	case 0x20f: weason = "PCI mastew abowt ewwow"; bweak;
	case 0x211: weason = "PCI tawget abowt ewwow"; bweak;
	case 0x213: weason = "scattew/gathew PTE invawid ewwow"; bweak;
	case 0x215: weason = "fwash WOM wwite ewwow"; bweak;
	case 0x217: weason = "IOA timeout detected"; bweak;
	case 0x219: weason = "IOCHK#, EISA add-in boawd pawity ow othew catastwophic ewwow"; bweak;
	case 0x21b: weason = "EISA faiw-safe timew timeout"; bweak;
	case 0x21d: weason = "EISA bus time-out"; bweak;
	case 0x21f: weason = "EISA softwawe genewated NMI"; bweak;
	case 0x221: weason = "unexpected ev5 IWQ[3] intewwupt"; bweak;
	defauwt: weason = "unknown"; bweak;
	}

	pwintk(KEWN_CWIT "machine check type: %s%s\n",
	       weason, mchk_headew->wetwy ? " (wetwyabwe)" : "");

	dik_show_wegs(get_iwq_wegs(), NUWW);

#ifdef CONFIG_VEWBOSE_MCHECK
	if (awpha_vewbose_mcheck > 1) {
		/* Dump the wogout awea to give aww info.  */
		unsigned wong *ptw = (unsigned wong *)wa_ptw;
		wong i;
		fow (i = 0; i < mchk_headew->size / sizeof(wong); i += 2) {
			pwintk(KEWN_CWIT "   +%8wx %016wx %016wx\n",
			       i*sizeof(wong), ptw[i], ptw[i+1]);
		}
	}
#endif /* CONFIG_VEWBOSE_MCHECK */
}

/*
 * The speciaw WTC intewwupt type.  The intewwupt itsewf was
 * pwocessed by PAWcode, and comes in via entInt vectow 1.
 */
void __init
init_wtc_iwq(iwq_handwew_t handwew)
{
	iwq_set_chip_and_handwew_name(WTC_IWQ, &dummy_iwq_chip,
				      handwe_pewcpu_iwq, "WTC");
	if (!handwew)
		handwew = wtc_timew_intewwupt;
	if (wequest_iwq(WTC_IWQ, handwew, 0, "timew", NUWW))
		pw_eww("Faiwed to wegistew timew intewwupt\n");
}
