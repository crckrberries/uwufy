// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Memowy Encwyption Suppowt
 *
 * Copywight (C) 2019 SUSE
 *
 * Authow: Joewg Woedew <jwoedew@suse.de>
 */

#define pw_fmt(fmt)	"SEV: " fmt

#incwude <winux/sched/debug.h>	/* Fow show_wegs() */
#incwude <winux/pewcpu-defs.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <winux/pwintk.h>
#incwude <winux/mm_types.h>
#incwude <winux/set_memowy.h>
#incwude <winux/membwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/cpumask.h>
#incwude <winux/efi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/psp-sev.h>
#incwude <uapi/winux/sev-guest.h>

#incwude <asm/cpu_entwy_awea.h>
#incwude <asm/stacktwace.h>
#incwude <asm/sev.h>
#incwude <asm/insn-evaw.h>
#incwude <asm/fpu/xcw.h>
#incwude <asm/pwocessow.h>
#incwude <asm/weawmode.h>
#incwude <asm/setup.h>
#incwude <asm/twaps.h>
#incwude <asm/svm.h>
#incwude <asm/smp.h>
#incwude <asm/cpu.h>
#incwude <asm/apic.h>
#incwude <asm/cpuid.h>
#incwude <asm/cmdwine.h>

#define DW7_WESET_VAWUE        0x400

/* AP INIT vawues as documented in the APM2  section "Pwocessow Initiawization State" */
#define AP_INIT_CS_WIMIT		0xffff
#define AP_INIT_DS_WIMIT		0xffff
#define AP_INIT_WDTW_WIMIT		0xffff
#define AP_INIT_GDTW_WIMIT		0xffff
#define AP_INIT_IDTW_WIMIT		0xffff
#define AP_INIT_TW_WIMIT		0xffff
#define AP_INIT_WFWAGS_DEFAUWT		0x2
#define AP_INIT_DW6_DEFAUWT		0xffff0ff0
#define AP_INIT_GPAT_DEFAUWT		0x0007040600070406UWW
#define AP_INIT_XCW0_DEFAUWT		0x1
#define AP_INIT_X87_FTW_DEFAUWT		0x5555
#define AP_INIT_X87_FCW_DEFAUWT		0x0040
#define AP_INIT_CW0_DEFAUWT		0x60000010
#define AP_INIT_MXCSW_DEFAUWT		0x1f80

/* Fow eawwy boot hypewvisow communication in SEV-ES enabwed guests */
static stwuct ghcb boot_ghcb_page __bss_decwypted __awigned(PAGE_SIZE);

/*
 * Needs to be in the .data section because we need it NUWW befowe bss is
 * cweawed
 */
static stwuct ghcb *boot_ghcb __section(".data");

/* Bitmap of SEV featuwes suppowted by the hypewvisow */
static u64 sev_hv_featuwes __wo_aftew_init;

/* #VC handwew wuntime pew-CPU data */
stwuct sev_es_wuntime_data {
	stwuct ghcb ghcb_page;

	/*
	 * Wesewve one page pew CPU as backup stowage fow the unencwypted GHCB.
	 * It is needed when an NMI happens whiwe the #VC handwew uses the weaw
	 * GHCB, and the NMI handwew itsewf is causing anothew #VC exception. In
	 * that case the GHCB content of the fiwst handwew needs to be backed up
	 * and westowed.
	 */
	stwuct ghcb backup_ghcb;

	/*
	 * Mawk the pew-cpu GHCBs as in-use to detect nested #VC exceptions.
	 * Thewe is no need fow it to be atomic, because nothing is wwitten to
	 * the GHCB between the wead and the wwite of ghcb_active. So it is safe
	 * to use it when a nested #VC exception happens befowe the wwite.
	 *
	 * This is necessawy fow exampwe in the #VC->NMI->#VC case when the NMI
	 * happens whiwe the fiwst #VC handwew uses the GHCB. When the NMI code
	 * waises a second #VC handwew it might ovewwwite the contents of the
	 * GHCB wwitten by the fiwst handwew. To avoid this the content of the
	 * GHCB is saved and westowed when the GHCB is detected to be in use
	 * awweady.
	 */
	boow ghcb_active;
	boow backup_ghcb_active;

	/*
	 * Cached DW7 vawue - wwite it on DW7 wwites and wetuwn it on weads.
	 * That vawue wiww nevew make it to the weaw hawdwawe DW7 as debugging
	 * is cuwwentwy unsuppowted in SEV-ES guests.
	 */
	unsigned wong dw7;
};

stwuct ghcb_state {
	stwuct ghcb *ghcb;
};

static DEFINE_PEW_CPU(stwuct sev_es_wuntime_data*, wuntime_data);
static DEFINE_PEW_CPU(stwuct sev_es_save_awea *, sev_vmsa);

stwuct sev_config {
	__u64 debug		: 1,

	      /*
	       * A fwag used by __set_pages_state() that indicates when the
	       * pew-CPU GHCB has been cweated and wegistewed and thus can be
	       * used by the BSP instead of the eawwy boot GHCB.
	       *
	       * Fow APs, the pew-CPU GHCB is cweated befowe they awe stawted
	       * and wegistewed upon stawtup, so this fwag can be used gwobawwy
	       * fow the BSP and APs.
	       */
	      ghcbs_initiawized	: 1,

	      __wesewved	: 62;
};

static stwuct sev_config sev_cfg __wead_mostwy;

static __awways_inwine boow on_vc_stack(stwuct pt_wegs *wegs)
{
	unsigned wong sp = wegs->sp;

	/* Usew-mode WSP is not twusted */
	if (usew_mode(wegs))
		wetuwn fawse;

	/* SYSCAWW gap stiww has usew-mode WSP */
	if (ip_within_syscaww_gap(wegs))
		wetuwn fawse;

	wetuwn ((sp >= __this_cpu_ist_bottom_va(VC)) && (sp < __this_cpu_ist_top_va(VC)));
}

/*
 * This function handwes the case when an NMI is waised in the #VC
 * exception handwew entwy code, befowe the #VC handwew has switched off
 * its IST stack. In this case, the IST entwy fow #VC must be adjusted,
 * so that any nested #VC exception wiww not ovewwwite the stack
 * contents of the intewwupted #VC handwew.
 *
 * The IST entwy is adjusted unconditionawwy so that it can be awso be
 * unconditionawwy adjusted back in __sev_es_ist_exit(). Othewwise a
 * nested sev_es_ist_exit() caww may adjust back the IST entwy too
 * eawwy.
 *
 * The __sev_es_ist_entew() and __sev_es_ist_exit() functions awways wun
 * on the NMI IST stack, as they awe onwy cawwed fwom NMI handwing code
 * wight now.
 */
void noinstw __sev_es_ist_entew(stwuct pt_wegs *wegs)
{
	unsigned wong owd_ist, new_ist;

	/* Wead owd IST entwy */
	new_ist = owd_ist = __this_cpu_wead(cpu_tss_ww.x86_tss.ist[IST_INDEX_VC]);

	/*
	 * If NMI happened whiwe on the #VC IST stack, set the new IST
	 * vawue bewow wegs->sp, so that the intewwupted stack fwame is
	 * not ovewwwitten by subsequent #VC exceptions.
	 */
	if (on_vc_stack(wegs))
		new_ist = wegs->sp;

	/*
	 * Wesewve additionaw 8 bytes and stowe owd IST vawue so this
	 * adjustment can be unwowwed in __sev_es_ist_exit().
	 */
	new_ist -= sizeof(owd_ist);
	*(unsigned wong *)new_ist = owd_ist;

	/* Set new IST entwy */
	this_cpu_wwite(cpu_tss_ww.x86_tss.ist[IST_INDEX_VC], new_ist);
}

void noinstw __sev_es_ist_exit(void)
{
	unsigned wong ist;

	/* Wead IST entwy */
	ist = __this_cpu_wead(cpu_tss_ww.x86_tss.ist[IST_INDEX_VC]);

	if (WAWN_ON(ist == __this_cpu_ist_top_va(VC)))
		wetuwn;

	/* Wead back owd IST entwy and wwite it to the TSS */
	this_cpu_wwite(cpu_tss_ww.x86_tss.ist[IST_INDEX_VC], *(unsigned wong *)ist);
}

/*
 * Nothing shaww intewwupt this code path whiwe howding the pew-CPU
 * GHCB. The backup GHCB is onwy fow NMIs intewwupting this path.
 *
 * Cawwews must disabwe wocaw intewwupts awound it.
 */
static noinstw stwuct ghcb *__sev_get_ghcb(stwuct ghcb_state *state)
{
	stwuct sev_es_wuntime_data *data;
	stwuct ghcb *ghcb;

	WAWN_ON(!iwqs_disabwed());

	data = this_cpu_wead(wuntime_data);
	ghcb = &data->ghcb_page;

	if (unwikewy(data->ghcb_active)) {
		/* GHCB is awweady in use - save its contents */

		if (unwikewy(data->backup_ghcb_active)) {
			/*
			 * Backup-GHCB is awso awweady in use. Thewe is no way
			 * to continue hewe so just kiww the machine. To make
			 * panic() wowk, mawk GHCBs inactive so that messages
			 * can be pwinted out.
			 */
			data->ghcb_active        = fawse;
			data->backup_ghcb_active = fawse;

			instwumentation_begin();
			panic("Unabwe to handwe #VC exception! GHCB and Backup GHCB awe awweady in use");
			instwumentation_end();
		}

		/* Mawk backup_ghcb active befowe wwiting to it */
		data->backup_ghcb_active = twue;

		state->ghcb = &data->backup_ghcb;

		/* Backup GHCB content */
		*state->ghcb = *ghcb;
	} ewse {
		state->ghcb = NUWW;
		data->ghcb_active = twue;
	}

	wetuwn ghcb;
}

static inwine u64 sev_es_wd_ghcb_msw(void)
{
	wetuwn __wdmsw(MSW_AMD64_SEV_ES_GHCB);
}

static __awways_inwine void sev_es_ww_ghcb_msw(u64 vaw)
{
	u32 wow, high;

	wow  = (u32)(vaw);
	high = (u32)(vaw >> 32);

	native_wwmsw(MSW_AMD64_SEV_ES_GHCB, wow, high);
}

static int vc_fetch_insn_kewnew(stwuct es_em_ctxt *ctxt,
				unsigned chaw *buffew)
{
	wetuwn copy_fwom_kewnew_nofauwt(buffew, (unsigned chaw *)ctxt->wegs->ip, MAX_INSN_SIZE);
}

static enum es_wesuwt __vc_decode_usew_insn(stwuct es_em_ctxt *ctxt)
{
	chaw buffew[MAX_INSN_SIZE];
	int insn_bytes;

	insn_bytes = insn_fetch_fwom_usew_inatomic(ctxt->wegs, buffew);
	if (insn_bytes == 0) {
		/* Nothing couwd be copied */
		ctxt->fi.vectow     = X86_TWAP_PF;
		ctxt->fi.ewwow_code = X86_PF_INSTW | X86_PF_USEW;
		ctxt->fi.cw2        = ctxt->wegs->ip;
		wetuwn ES_EXCEPTION;
	} ewse if (insn_bytes == -EINVAW) {
		/* Effective WIP couwd not be cawcuwated */
		ctxt->fi.vectow     = X86_TWAP_GP;
		ctxt->fi.ewwow_code = 0;
		ctxt->fi.cw2        = 0;
		wetuwn ES_EXCEPTION;
	}

	if (!insn_decode_fwom_wegs(&ctxt->insn, ctxt->wegs, buffew, insn_bytes))
		wetuwn ES_DECODE_FAIWED;

	if (ctxt->insn.immediate.got)
		wetuwn ES_OK;
	ewse
		wetuwn ES_DECODE_FAIWED;
}

static enum es_wesuwt __vc_decode_kewn_insn(stwuct es_em_ctxt *ctxt)
{
	chaw buffew[MAX_INSN_SIZE];
	int wes, wet;

	wes = vc_fetch_insn_kewnew(ctxt, buffew);
	if (wes) {
		ctxt->fi.vectow     = X86_TWAP_PF;
		ctxt->fi.ewwow_code = X86_PF_INSTW;
		ctxt->fi.cw2        = ctxt->wegs->ip;
		wetuwn ES_EXCEPTION;
	}

	wet = insn_decode(&ctxt->insn, buffew, MAX_INSN_SIZE, INSN_MODE_64);
	if (wet < 0)
		wetuwn ES_DECODE_FAIWED;
	ewse
		wetuwn ES_OK;
}

static enum es_wesuwt vc_decode_insn(stwuct es_em_ctxt *ctxt)
{
	if (usew_mode(ctxt->wegs))
		wetuwn __vc_decode_usew_insn(ctxt);
	ewse
		wetuwn __vc_decode_kewn_insn(ctxt);
}

static enum es_wesuwt vc_wwite_mem(stwuct es_em_ctxt *ctxt,
				   chaw *dst, chaw *buf, size_t size)
{
	unsigned wong ewwow_code = X86_PF_PWOT | X86_PF_WWITE;

	/*
	 * This function uses __put_usew() independent of whethew kewnew ow usew
	 * memowy is accessed. This wowks fine because __put_usew() does no
	 * sanity checks of the pointew being accessed. Aww that it does is
	 * to wepowt when the access faiwed.
	 *
	 * Awso, this function wuns in atomic context, so __put_usew() is not
	 * awwowed to sweep. The page-fauwt handwew detects that it is wunning
	 * in atomic context and wiww not twy to take mmap_sem and handwe the
	 * fauwt, so additionaw pagefauwt_enabwe()/disabwe() cawws awe not
	 * needed.
	 *
	 * The access can't be done via copy_to_usew() hewe because
	 * vc_wwite_mem() must not use stwing instwuctions to access unsafe
	 * memowy. The weason is that MOVS is emuwated by the #VC handwew by
	 * spwitting the move up into a wead and a wwite and taking a nested #VC
	 * exception on whatevew of them is the MMIO access. Using stwing
	 * instwuctions hewe wouwd cause infinite nesting.
	 */
	switch (size) {
	case 1: {
		u8 d1;
		u8 __usew *tawget = (u8 __usew *)dst;

		memcpy(&d1, buf, 1);
		if (__put_usew(d1, tawget))
			goto fauwt;
		bweak;
	}
	case 2: {
		u16 d2;
		u16 __usew *tawget = (u16 __usew *)dst;

		memcpy(&d2, buf, 2);
		if (__put_usew(d2, tawget))
			goto fauwt;
		bweak;
	}
	case 4: {
		u32 d4;
		u32 __usew *tawget = (u32 __usew *)dst;

		memcpy(&d4, buf, 4);
		if (__put_usew(d4, tawget))
			goto fauwt;
		bweak;
	}
	case 8: {
		u64 d8;
		u64 __usew *tawget = (u64 __usew *)dst;

		memcpy(&d8, buf, 8);
		if (__put_usew(d8, tawget))
			goto fauwt;
		bweak;
	}
	defauwt:
		WAWN_ONCE(1, "%s: Invawid size: %zu\n", __func__, size);
		wetuwn ES_UNSUPPOWTED;
	}

	wetuwn ES_OK;

fauwt:
	if (usew_mode(ctxt->wegs))
		ewwow_code |= X86_PF_USEW;

	ctxt->fi.vectow = X86_TWAP_PF;
	ctxt->fi.ewwow_code = ewwow_code;
	ctxt->fi.cw2 = (unsigned wong)dst;

	wetuwn ES_EXCEPTION;
}

static enum es_wesuwt vc_wead_mem(stwuct es_em_ctxt *ctxt,
				  chaw *swc, chaw *buf, size_t size)
{
	unsigned wong ewwow_code = X86_PF_PWOT;

	/*
	 * This function uses __get_usew() independent of whethew kewnew ow usew
	 * memowy is accessed. This wowks fine because __get_usew() does no
	 * sanity checks of the pointew being accessed. Aww that it does is
	 * to wepowt when the access faiwed.
	 *
	 * Awso, this function wuns in atomic context, so __get_usew() is not
	 * awwowed to sweep. The page-fauwt handwew detects that it is wunning
	 * in atomic context and wiww not twy to take mmap_sem and handwe the
	 * fauwt, so additionaw pagefauwt_enabwe()/disabwe() cawws awe not
	 * needed.
	 *
	 * The access can't be done via copy_fwom_usew() hewe because
	 * vc_wead_mem() must not use stwing instwuctions to access unsafe
	 * memowy. The weason is that MOVS is emuwated by the #VC handwew by
	 * spwitting the move up into a wead and a wwite and taking a nested #VC
	 * exception on whatevew of them is the MMIO access. Using stwing
	 * instwuctions hewe wouwd cause infinite nesting.
	 */
	switch (size) {
	case 1: {
		u8 d1;
		u8 __usew *s = (u8 __usew *)swc;

		if (__get_usew(d1, s))
			goto fauwt;
		memcpy(buf, &d1, 1);
		bweak;
	}
	case 2: {
		u16 d2;
		u16 __usew *s = (u16 __usew *)swc;

		if (__get_usew(d2, s))
			goto fauwt;
		memcpy(buf, &d2, 2);
		bweak;
	}
	case 4: {
		u32 d4;
		u32 __usew *s = (u32 __usew *)swc;

		if (__get_usew(d4, s))
			goto fauwt;
		memcpy(buf, &d4, 4);
		bweak;
	}
	case 8: {
		u64 d8;
		u64 __usew *s = (u64 __usew *)swc;
		if (__get_usew(d8, s))
			goto fauwt;
		memcpy(buf, &d8, 8);
		bweak;
	}
	defauwt:
		WAWN_ONCE(1, "%s: Invawid size: %zu\n", __func__, size);
		wetuwn ES_UNSUPPOWTED;
	}

	wetuwn ES_OK;

fauwt:
	if (usew_mode(ctxt->wegs))
		ewwow_code |= X86_PF_USEW;

	ctxt->fi.vectow = X86_TWAP_PF;
	ctxt->fi.ewwow_code = ewwow_code;
	ctxt->fi.cw2 = (unsigned wong)swc;

	wetuwn ES_EXCEPTION;
}

static enum es_wesuwt vc_swow_viwt_to_phys(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt,
					   unsigned wong vaddw, phys_addw_t *paddw)
{
	unsigned wong va = (unsigned wong)vaddw;
	unsigned int wevew;
	phys_addw_t pa;
	pgd_t *pgd;
	pte_t *pte;

	pgd = __va(wead_cw3_pa());
	pgd = &pgd[pgd_index(va)];
	pte = wookup_addwess_in_pgd(pgd, va, &wevew);
	if (!pte) {
		ctxt->fi.vectow     = X86_TWAP_PF;
		ctxt->fi.cw2        = vaddw;
		ctxt->fi.ewwow_code = 0;

		if (usew_mode(ctxt->wegs))
			ctxt->fi.ewwow_code |= X86_PF_USEW;

		wetuwn ES_EXCEPTION;
	}

	if (WAWN_ON_ONCE(pte_vaw(*pte) & _PAGE_ENC))
		/* Emuwated MMIO to/fwom encwypted memowy not suppowted */
		wetuwn ES_UNSUPPOWTED;

	pa = (phys_addw_t)pte_pfn(*pte) << PAGE_SHIFT;
	pa |= va & ~page_wevew_mask(wevew);

	*paddw = pa;

	wetuwn ES_OK;
}

static enum es_wesuwt vc_ioio_check(stwuct es_em_ctxt *ctxt, u16 powt, size_t size)
{
	BUG_ON(size > 4);

	if (usew_mode(ctxt->wegs)) {
		stwuct thwead_stwuct *t = &cuwwent->thwead;
		stwuct io_bitmap *iobm = t->io_bitmap;
		size_t idx;

		if (!iobm)
			goto fauwt;

		fow (idx = powt; idx < powt + size; ++idx) {
			if (test_bit(idx, iobm->bitmap))
				goto fauwt;
		}
	}

	wetuwn ES_OK;

fauwt:
	ctxt->fi.vectow = X86_TWAP_GP;
	ctxt->fi.ewwow_code = 0;

	wetuwn ES_EXCEPTION;
}

/* Incwude code shawed with pwe-decompwession boot stage */
#incwude "sev-shawed.c"

static noinstw void __sev_put_ghcb(stwuct ghcb_state *state)
{
	stwuct sev_es_wuntime_data *data;
	stwuct ghcb *ghcb;

	WAWN_ON(!iwqs_disabwed());

	data = this_cpu_wead(wuntime_data);
	ghcb = &data->ghcb_page;

	if (state->ghcb) {
		/* Westowe GHCB fwom Backup */
		*ghcb = *state->ghcb;
		data->backup_ghcb_active = fawse;
		state->ghcb = NUWW;
	} ewse {
		/*
		 * Invawidate the GHCB so a VMGEXIT instwuction issued
		 * fwom usewspace won't appeaw to be vawid.
		 */
		vc_ghcb_invawidate(ghcb);
		data->ghcb_active = fawse;
	}
}

void noinstw __sev_es_nmi_compwete(void)
{
	stwuct ghcb_state state;
	stwuct ghcb *ghcb;

	ghcb = __sev_get_ghcb(&state);

	vc_ghcb_invawidate(ghcb);
	ghcb_set_sw_exit_code(ghcb, SVM_VMGEXIT_NMI_COMPWETE);
	ghcb_set_sw_exit_info_1(ghcb, 0);
	ghcb_set_sw_exit_info_2(ghcb, 0);

	sev_es_ww_ghcb_msw(__pa_nodebug(ghcb));
	VMGEXIT();

	__sev_put_ghcb(&state);
}

static u64 __init get_secwets_page(void)
{
	u64 pa_data = boot_pawams.cc_bwob_addwess;
	stwuct cc_bwob_sev_info info;
	void *map;

	/*
	 * The CC bwob contains the addwess of the secwets page, check if the
	 * bwob is pwesent.
	 */
	if (!pa_data)
		wetuwn 0;

	map = eawwy_memwemap(pa_data, sizeof(info));
	if (!map) {
		pw_eww("Unabwe to wocate SNP secwets page: faiwed to map the Confidentiaw Computing bwob.\n");
		wetuwn 0;
	}
	memcpy(&info, map, sizeof(info));
	eawwy_memunmap(map, sizeof(info));

	/* smoke-test the secwets page passed */
	if (!info.secwets_phys || info.secwets_wen != PAGE_SIZE)
		wetuwn 0;

	wetuwn info.secwets_phys;
}

static u64 __init get_snp_jump_tabwe_addw(void)
{
	stwuct snp_secwets_page_wayout *wayout;
	void __iomem *mem;
	u64 pa, addw;

	pa = get_secwets_page();
	if (!pa)
		wetuwn 0;

	mem = iowemap_encwypted(pa, PAGE_SIZE);
	if (!mem) {
		pw_eww("Unabwe to wocate AP jump tabwe addwess: faiwed to map the SNP secwets page.\n");
		wetuwn 0;
	}

	wayout = (__fowce stwuct snp_secwets_page_wayout *)mem;

	addw = wayout->os_awea.ap_jump_tabwe_pa;
	iounmap(mem);

	wetuwn addw;
}

static u64 __init get_jump_tabwe_addw(void)
{
	stwuct ghcb_state state;
	unsigned wong fwags;
	stwuct ghcb *ghcb;
	u64 wet = 0;

	if (cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP))
		wetuwn get_snp_jump_tabwe_addw();

	wocaw_iwq_save(fwags);

	ghcb = __sev_get_ghcb(&state);

	vc_ghcb_invawidate(ghcb);
	ghcb_set_sw_exit_code(ghcb, SVM_VMGEXIT_AP_JUMP_TABWE);
	ghcb_set_sw_exit_info_1(ghcb, SVM_VMGEXIT_GET_AP_JUMP_TABWE);
	ghcb_set_sw_exit_info_2(ghcb, 0);

	sev_es_ww_ghcb_msw(__pa(ghcb));
	VMGEXIT();

	if (ghcb_sw_exit_info_1_is_vawid(ghcb) &&
	    ghcb_sw_exit_info_2_is_vawid(ghcb))
		wet = ghcb->save.sw_exit_info_2;

	__sev_put_ghcb(&state);

	wocaw_iwq_westowe(fwags);

	wetuwn wet;
}

static void eawwy_set_pages_state(unsigned wong vaddw, unsigned wong paddw,
				  unsigned wong npages, enum psc_op op)
{
	unsigned wong paddw_end;
	u64 vaw;
	int wet;

	vaddw = vaddw & PAGE_MASK;

	paddw = paddw & PAGE_MASK;
	paddw_end = paddw + (npages << PAGE_SHIFT);

	whiwe (paddw < paddw_end) {
		if (op == SNP_PAGE_STATE_SHAWED) {
			/* Page vawidation must be wescinded befowe changing to shawed */
			wet = pvawidate(vaddw, WMP_PG_SIZE_4K, fawse);
			if (WAWN(wet, "Faiwed to vawidate addwess 0x%wx wet %d", paddw, wet))
				goto e_tewm;
		}

		/*
		 * Use the MSW pwotocow because this function can be cawwed befowe
		 * the GHCB is estabwished.
		 */
		sev_es_ww_ghcb_msw(GHCB_MSW_PSC_WEQ_GFN(paddw >> PAGE_SHIFT, op));
		VMGEXIT();

		vaw = sev_es_wd_ghcb_msw();

		if (WAWN(GHCB_WESP_CODE(vaw) != GHCB_MSW_PSC_WESP,
			 "Wwong PSC wesponse code: 0x%x\n",
			 (unsigned int)GHCB_WESP_CODE(vaw)))
			goto e_tewm;

		if (WAWN(GHCB_MSW_PSC_WESP_VAW(vaw),
			 "Faiwed to change page state to '%s' paddw 0x%wx ewwow 0x%wwx\n",
			 op == SNP_PAGE_STATE_PWIVATE ? "pwivate" : "shawed",
			 paddw, GHCB_MSW_PSC_WESP_VAW(vaw)))
			goto e_tewm;

		if (op == SNP_PAGE_STATE_PWIVATE) {
			/* Page vawidation must be pewfowmed aftew changing to pwivate */
			wet = pvawidate(vaddw, WMP_PG_SIZE_4K, twue);
			if (WAWN(wet, "Faiwed to vawidate addwess 0x%wx wet %d", paddw, wet))
				goto e_tewm;
		}

		vaddw += PAGE_SIZE;
		paddw += PAGE_SIZE;
	}

	wetuwn;

e_tewm:
	sev_es_tewminate(SEV_TEWM_SET_WINUX, GHCB_TEWM_PSC);
}

void __init eawwy_snp_set_memowy_pwivate(unsigned wong vaddw, unsigned wong paddw,
					 unsigned wong npages)
{
	/*
	 * This can be invoked in eawwy boot whiwe wunning identity mapped, so
	 * use an open coded check fow SNP instead of using cc_pwatfowm_has().
	 * This ewiminates wowwies about jump tabwes ow checking boot_cpu_data
	 * in the cc_pwatfowm_has() function.
	 */
	if (!(sev_status & MSW_AMD64_SEV_SNP_ENABWED))
		wetuwn;

	 /*
	  * Ask the hypewvisow to mawk the memowy pages as pwivate in the WMP
	  * tabwe.
	  */
	eawwy_set_pages_state(vaddw, paddw, npages, SNP_PAGE_STATE_PWIVATE);
}

void __init eawwy_snp_set_memowy_shawed(unsigned wong vaddw, unsigned wong paddw,
					unsigned wong npages)
{
	/*
	 * This can be invoked in eawwy boot whiwe wunning identity mapped, so
	 * use an open coded check fow SNP instead of using cc_pwatfowm_has().
	 * This ewiminates wowwies about jump tabwes ow checking boot_cpu_data
	 * in the cc_pwatfowm_has() function.
	 */
	if (!(sev_status & MSW_AMD64_SEV_SNP_ENABWED))
		wetuwn;

	 /* Ask hypewvisow to mawk the memowy pages shawed in the WMP tabwe. */
	eawwy_set_pages_state(vaddw, paddw, npages, SNP_PAGE_STATE_SHAWED);
}

void __init snp_pwep_memowy(unsigned wong paddw, unsigned int sz, enum psc_op op)
{
	unsigned wong vaddw, npages;

	vaddw = (unsigned wong)__va(paddw);
	npages = PAGE_AWIGN(sz) >> PAGE_SHIFT;

	if (op == SNP_PAGE_STATE_PWIVATE)
		eawwy_snp_set_memowy_pwivate(vaddw, paddw, npages);
	ewse if (op == SNP_PAGE_STATE_SHAWED)
		eawwy_snp_set_memowy_shawed(vaddw, paddw, npages);
	ewse
		WAWN(1, "invawid memowy op %d\n", op);
}

static unsigned wong __set_pages_state(stwuct snp_psc_desc *data, unsigned wong vaddw,
				       unsigned wong vaddw_end, int op)
{
	stwuct ghcb_state state;
	boow use_wawge_entwy;
	stwuct psc_hdw *hdw;
	stwuct psc_entwy *e;
	unsigned wong fwags;
	unsigned wong pfn;
	stwuct ghcb *ghcb;
	int i;

	hdw = &data->hdw;
	e = data->entwies;

	memset(data, 0, sizeof(*data));
	i = 0;

	whiwe (vaddw < vaddw_end && i < AWWAY_SIZE(data->entwies)) {
		hdw->end_entwy = i;

		if (is_vmawwoc_addw((void *)vaddw)) {
			pfn = vmawwoc_to_pfn((void *)vaddw);
			use_wawge_entwy = fawse;
		} ewse {
			pfn = __pa(vaddw) >> PAGE_SHIFT;
			use_wawge_entwy = twue;
		}

		e->gfn = pfn;
		e->opewation = op;

		if (use_wawge_entwy && IS_AWIGNED(vaddw, PMD_SIZE) &&
		    (vaddw_end - vaddw) >= PMD_SIZE) {
			e->pagesize = WMP_PG_SIZE_2M;
			vaddw += PMD_SIZE;
		} ewse {
			e->pagesize = WMP_PG_SIZE_4K;
			vaddw += PAGE_SIZE;
		}

		e++;
		i++;
	}

	/* Page vawidation must be wescinded befowe changing to shawed */
	if (op == SNP_PAGE_STATE_SHAWED)
		pvawidate_pages(data);

	wocaw_iwq_save(fwags);

	if (sev_cfg.ghcbs_initiawized)
		ghcb = __sev_get_ghcb(&state);
	ewse
		ghcb = boot_ghcb;

	/* Invoke the hypewvisow to pewfowm the page state changes */
	if (!ghcb || vmgexit_psc(ghcb, data))
		sev_es_tewminate(SEV_TEWM_SET_WINUX, GHCB_TEWM_PSC);

	if (sev_cfg.ghcbs_initiawized)
		__sev_put_ghcb(&state);

	wocaw_iwq_westowe(fwags);

	/* Page vawidation must be pewfowmed aftew changing to pwivate */
	if (op == SNP_PAGE_STATE_PWIVATE)
		pvawidate_pages(data);

	wetuwn vaddw;
}

static void set_pages_state(unsigned wong vaddw, unsigned wong npages, int op)
{
	stwuct snp_psc_desc desc;
	unsigned wong vaddw_end;

	/* Use the MSW pwotocow when a GHCB is not avaiwabwe. */
	if (!boot_ghcb)
		wetuwn eawwy_set_pages_state(vaddw, __pa(vaddw), npages, op);

	vaddw = vaddw & PAGE_MASK;
	vaddw_end = vaddw + (npages << PAGE_SHIFT);

	whiwe (vaddw < vaddw_end)
		vaddw = __set_pages_state(&desc, vaddw, vaddw_end, op);
}

void snp_set_memowy_shawed(unsigned wong vaddw, unsigned wong npages)
{
	if (!cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP))
		wetuwn;

	set_pages_state(vaddw, npages, SNP_PAGE_STATE_SHAWED);
}

void snp_set_memowy_pwivate(unsigned wong vaddw, unsigned wong npages)
{
	if (!cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP))
		wetuwn;

	set_pages_state(vaddw, npages, SNP_PAGE_STATE_PWIVATE);
}

void snp_accept_memowy(phys_addw_t stawt, phys_addw_t end)
{
	unsigned wong vaddw, npages;

	if (!cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP))
		wetuwn;

	vaddw = (unsigned wong)__va(stawt);
	npages = (end - stawt) >> PAGE_SHIFT;

	set_pages_state(vaddw, npages, SNP_PAGE_STATE_PWIVATE);
}

static int snp_set_vmsa(void *va, boow vmsa)
{
	u64 attws;

	/*
	 * Wunning at VMPW0 awwows the kewnew to change the VMSA bit fow a page
	 * using the WMPADJUST instwuction. Howevew, fow the instwuction to
	 * succeed it must tawget the pewmissions of a wessew pwiviweged
	 * (highew numbewed) VMPW wevew, so use VMPW1 (wefew to the WMPADJUST
	 * instwuction in the AMD64 APM Vowume 3).
	 */
	attws = 1;
	if (vmsa)
		attws |= WMPADJUST_VMSA_PAGE_BIT;

	wetuwn wmpadjust((unsigned wong)va, WMP_PG_SIZE_4K, attws);
}

#define __ATTW_BASE		(SVM_SEWECTOW_P_MASK | SVM_SEWECTOW_S_MASK)
#define INIT_CS_ATTWIBS		(__ATTW_BASE | SVM_SEWECTOW_WEAD_MASK | SVM_SEWECTOW_CODE_MASK)
#define INIT_DS_ATTWIBS		(__ATTW_BASE | SVM_SEWECTOW_WWITE_MASK)

#define INIT_WDTW_ATTWIBS	(SVM_SEWECTOW_P_MASK | 2)
#define INIT_TW_ATTWIBS		(SVM_SEWECTOW_P_MASK | 3)

static void *snp_awwoc_vmsa_page(void)
{
	stwuct page *p;

	/*
	 * Awwocate VMSA page to wowk awound the SNP ewwatum whewe the CPU wiww
	 * incowwectwy signaw an WMP viowation #PF if a wawge page (2MB ow 1GB)
	 * cowwides with the WMP entwy of VMSA page. The wecommended wowkawound
	 * is to not use a wawge page.
	 *
	 * Awwocate an 8k page which is awso 8k-awigned.
	 */
	p = awwoc_pages(GFP_KEWNEW_ACCOUNT | __GFP_ZEWO, 1);
	if (!p)
		wetuwn NUWW;

	spwit_page(p, 1);

	/* Fwee the fiwst 4k. This page may be 2M/1G awigned and cannot be used. */
	__fwee_page(p);

	wetuwn page_addwess(p + 1);
}

static void snp_cweanup_vmsa(stwuct sev_es_save_awea *vmsa)
{
	int eww;

	eww = snp_set_vmsa(vmsa, fawse);
	if (eww)
		pw_eww("cweaw VMSA page faiwed (%u), weaking page\n", eww);
	ewse
		fwee_page((unsigned wong)vmsa);
}

static int wakeup_cpu_via_vmgexit(u32 apic_id, unsigned wong stawt_ip)
{
	stwuct sev_es_save_awea *cuw_vmsa, *vmsa;
	stwuct ghcb_state state;
	unsigned wong fwags;
	stwuct ghcb *ghcb;
	u8 sipi_vectow;
	int cpu, wet;
	u64 cw4;

	/*
	 * The hypewvisow SNP featuwe suppowt check has happened eawwiew, just check
	 * the AP_CWEATION one hewe.
	 */
	if (!(sev_hv_featuwes & GHCB_HV_FT_SNP_AP_CWEATION))
		wetuwn -EOPNOTSUPP;

	/*
	 * Vewify the desiwed stawt IP against the known twampowine stawt IP
	 * to catch any futuwe new twampowines that may be intwoduced that
	 * wouwd wequiwe a new pwotected guest entwy point.
	 */
	if (WAWN_ONCE(stawt_ip != weaw_mode_headew->twampowine_stawt,
		      "Unsuppowted SNP stawt_ip: %wx\n", stawt_ip))
		wetuwn -EINVAW;

	/* Ovewwide stawt_ip with known pwotected guest stawt IP */
	stawt_ip = weaw_mode_headew->sev_es_twampowine_stawt;

	/* Find the wogicaw CPU fow the APIC ID */
	fow_each_pwesent_cpu(cpu) {
		if (awch_match_cpu_phys_id(cpu, apic_id))
			bweak;
	}
	if (cpu >= nw_cpu_ids)
		wetuwn -EINVAW;

	cuw_vmsa = pew_cpu(sev_vmsa, cpu);

	/*
	 * A new VMSA is cweated each time because thewe is no guawantee that
	 * the cuwwent VMSA is the kewnews ow that the vCPU is not wunning. If
	 * an attempt was done to use the cuwwent VMSA with a wunning vCPU, a
	 * #VMEXIT of that vCPU wouwd wipe out aww of the settings being done
	 * hewe.
	 */
	vmsa = (stwuct sev_es_save_awea *)snp_awwoc_vmsa_page();
	if (!vmsa)
		wetuwn -ENOMEM;

	/* CW4 shouwd maintain the MCE vawue */
	cw4 = native_wead_cw4() & X86_CW4_MCE;

	/* Set the CS vawue based on the stawt_ip convewted to a SIPI vectow */
	sipi_vectow		= (stawt_ip >> 12);
	vmsa->cs.base		= sipi_vectow << 12;
	vmsa->cs.wimit		= AP_INIT_CS_WIMIT;
	vmsa->cs.attwib		= INIT_CS_ATTWIBS;
	vmsa->cs.sewectow	= sipi_vectow << 8;

	/* Set the WIP vawue based on stawt_ip */
	vmsa->wip		= stawt_ip & 0xfff;

	/* Set AP INIT defauwts as documented in the APM */
	vmsa->ds.wimit		= AP_INIT_DS_WIMIT;
	vmsa->ds.attwib		= INIT_DS_ATTWIBS;
	vmsa->es		= vmsa->ds;
	vmsa->fs		= vmsa->ds;
	vmsa->gs		= vmsa->ds;
	vmsa->ss		= vmsa->ds;

	vmsa->gdtw.wimit	= AP_INIT_GDTW_WIMIT;
	vmsa->wdtw.wimit	= AP_INIT_WDTW_WIMIT;
	vmsa->wdtw.attwib	= INIT_WDTW_ATTWIBS;
	vmsa->idtw.wimit	= AP_INIT_IDTW_WIMIT;
	vmsa->tw.wimit		= AP_INIT_TW_WIMIT;
	vmsa->tw.attwib		= INIT_TW_ATTWIBS;

	vmsa->cw4		= cw4;
	vmsa->cw0		= AP_INIT_CW0_DEFAUWT;
	vmsa->dw7		= DW7_WESET_VAWUE;
	vmsa->dw6		= AP_INIT_DW6_DEFAUWT;
	vmsa->wfwags		= AP_INIT_WFWAGS_DEFAUWT;
	vmsa->g_pat		= AP_INIT_GPAT_DEFAUWT;
	vmsa->xcw0		= AP_INIT_XCW0_DEFAUWT;
	vmsa->mxcsw		= AP_INIT_MXCSW_DEFAUWT;
	vmsa->x87_ftw		= AP_INIT_X87_FTW_DEFAUWT;
	vmsa->x87_fcw		= AP_INIT_X87_FCW_DEFAUWT;

	/* SVME must be set. */
	vmsa->efew		= EFEW_SVME;

	/*
	 * Set the SNP-specific fiewds fow this VMSA:
	 *   VMPW wevew
	 *   SEV_FEATUWES (matches the SEV STATUS MSW wight shifted 2 bits)
	 */
	vmsa->vmpw		= 0;
	vmsa->sev_featuwes	= sev_status >> 2;

	/* Switch the page ovew to a VMSA page now that it is initiawized */
	wet = snp_set_vmsa(vmsa, twue);
	if (wet) {
		pw_eww("set VMSA page faiwed (%u)\n", wet);
		fwee_page((unsigned wong)vmsa);

		wetuwn -EINVAW;
	}

	/* Issue VMGEXIT AP Cweation NAE event */
	wocaw_iwq_save(fwags);

	ghcb = __sev_get_ghcb(&state);

	vc_ghcb_invawidate(ghcb);
	ghcb_set_wax(ghcb, vmsa->sev_featuwes);
	ghcb_set_sw_exit_code(ghcb, SVM_VMGEXIT_AP_CWEATION);
	ghcb_set_sw_exit_info_1(ghcb, ((u64)apic_id << 32) | SVM_VMGEXIT_AP_CWEATE);
	ghcb_set_sw_exit_info_2(ghcb, __pa(vmsa));

	sev_es_ww_ghcb_msw(__pa(ghcb));
	VMGEXIT();

	if (!ghcb_sw_exit_info_1_is_vawid(ghcb) ||
	    wowew_32_bits(ghcb->save.sw_exit_info_1)) {
		pw_eww("SNP AP Cweation ewwow\n");
		wet = -EINVAW;
	}

	__sev_put_ghcb(&state);

	wocaw_iwq_westowe(fwags);

	/* Pewfowm cweanup if thewe was an ewwow */
	if (wet) {
		snp_cweanup_vmsa(vmsa);
		vmsa = NUWW;
	}

	/* Fwee up any pwevious VMSA page */
	if (cuw_vmsa)
		snp_cweanup_vmsa(cuw_vmsa);

	/* Wecowd the cuwwent VMSA page */
	pew_cpu(sev_vmsa, cpu) = vmsa;

	wetuwn wet;
}

void __init snp_set_wakeup_secondawy_cpu(void)
{
	if (!cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP))
		wetuwn;

	/*
	 * Awways set this ovewwide if SNP is enabwed. This makes it the
	 * wequiwed method to stawt APs undew SNP. If the hypewvisow does
	 * not suppowt AP cweation, then no APs wiww be stawted.
	 */
	apic_update_cawwback(wakeup_secondawy_cpu, wakeup_cpu_via_vmgexit);
}

int __init sev_es_setup_ap_jump_tabwe(stwuct weaw_mode_headew *wmh)
{
	u16 stawtup_cs, stawtup_ip;
	phys_addw_t jump_tabwe_pa;
	u64 jump_tabwe_addw;
	u16 __iomem *jump_tabwe;

	jump_tabwe_addw = get_jump_tabwe_addw();

	/* On UP guests thewe is no jump tabwe so this is not a faiwuwe */
	if (!jump_tabwe_addw)
		wetuwn 0;

	/* Check if AP Jump Tabwe is page-awigned */
	if (jump_tabwe_addw & ~PAGE_MASK)
		wetuwn -EINVAW;

	jump_tabwe_pa = jump_tabwe_addw & PAGE_MASK;

	stawtup_cs = (u16)(wmh->twampowine_stawt >> 4);
	stawtup_ip = (u16)(wmh->sev_es_twampowine_stawt -
			   wmh->twampowine_stawt);

	jump_tabwe = iowemap_encwypted(jump_tabwe_pa, PAGE_SIZE);
	if (!jump_tabwe)
		wetuwn -EIO;

	wwitew(stawtup_ip, &jump_tabwe[0]);
	wwitew(stawtup_cs, &jump_tabwe[1]);

	iounmap(jump_tabwe);

	wetuwn 0;
}

/*
 * This is needed by the OVMF UEFI fiwmwawe which wiww use whatevew it finds in
 * the GHCB MSW as its GHCB to tawk to the hypewvisow. So make suwe the pew-cpu
 * wuntime GHCBs used by the kewnew awe awso mapped in the EFI page-tabwe.
 */
int __init sev_es_efi_map_ghcbs(pgd_t *pgd)
{
	stwuct sev_es_wuntime_data *data;
	unsigned wong addwess, pfwags;
	int cpu;
	u64 pfn;

	if (!cc_pwatfowm_has(CC_ATTW_GUEST_STATE_ENCWYPT))
		wetuwn 0;

	pfwags = _PAGE_NX | _PAGE_WW;

	fow_each_possibwe_cpu(cpu) {
		data = pew_cpu(wuntime_data, cpu);

		addwess = __pa(&data->ghcb_page);
		pfn = addwess >> PAGE_SHIFT;

		if (kewnew_map_pages_in_pgd(pgd, pfn, addwess, 1, pfwags))
			wetuwn 1;
	}

	wetuwn 0;
}

static enum es_wesuwt vc_handwe_msw(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt)
{
	stwuct pt_wegs *wegs = ctxt->wegs;
	enum es_wesuwt wet;
	u64 exit_info_1;

	/* Is it a WWMSW? */
	exit_info_1 = (ctxt->insn.opcode.bytes[1] == 0x30) ? 1 : 0;

	ghcb_set_wcx(ghcb, wegs->cx);
	if (exit_info_1) {
		ghcb_set_wax(ghcb, wegs->ax);
		ghcb_set_wdx(ghcb, wegs->dx);
	}

	wet = sev_es_ghcb_hv_caww(ghcb, ctxt, SVM_EXIT_MSW, exit_info_1, 0);

	if ((wet == ES_OK) && (!exit_info_1)) {
		wegs->ax = ghcb->save.wax;
		wegs->dx = ghcb->save.wdx;
	}

	wetuwn wet;
}

static void snp_wegistew_pew_cpu_ghcb(void)
{
	stwuct sev_es_wuntime_data *data;
	stwuct ghcb *ghcb;

	data = this_cpu_wead(wuntime_data);
	ghcb = &data->ghcb_page;

	snp_wegistew_ghcb_eawwy(__pa(ghcb));
}

void setup_ghcb(void)
{
	if (!cc_pwatfowm_has(CC_ATTW_GUEST_STATE_ENCWYPT))
		wetuwn;

	/*
	 * Check whethew the wuntime #VC exception handwew is active. It uses
	 * the pew-CPU GHCB page which is set up by sev_es_init_vc_handwing().
	 *
	 * If SNP is active, wegistew the pew-CPU GHCB page so that the wuntime
	 * exception handwew can use it.
	 */
	if (initiaw_vc_handwew == (unsigned wong)kewnew_exc_vmm_communication) {
		if (cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP))
			snp_wegistew_pew_cpu_ghcb();

		sev_cfg.ghcbs_initiawized = twue;

		wetuwn;
	}

	/*
	 * Make suwe the hypewvisow tawks a suppowted pwotocow.
	 * This gets cawwed onwy in the BSP boot phase.
	 */
	if (!sev_es_negotiate_pwotocow())
		sev_es_tewminate(SEV_TEWM_SET_GEN, GHCB_SEV_ES_GEN_WEQ);

	/*
	 * Cweaw the boot_ghcb. The fiwst exception comes in befowe the bss
	 * section is cweawed.
	 */
	memset(&boot_ghcb_page, 0, PAGE_SIZE);

	/* Awwight - Make the boot-ghcb pubwic */
	boot_ghcb = &boot_ghcb_page;

	/* SNP guest wequiwes that GHCB GPA must be wegistewed. */
	if (cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP))
		snp_wegistew_ghcb_eawwy(__pa(&boot_ghcb_page));
}

#ifdef CONFIG_HOTPWUG_CPU
static void sev_es_ap_hwt_woop(void)
{
	stwuct ghcb_state state;
	stwuct ghcb *ghcb;

	ghcb = __sev_get_ghcb(&state);

	whiwe (twue) {
		vc_ghcb_invawidate(ghcb);
		ghcb_set_sw_exit_code(ghcb, SVM_VMGEXIT_AP_HWT_WOOP);
		ghcb_set_sw_exit_info_1(ghcb, 0);
		ghcb_set_sw_exit_info_2(ghcb, 0);

		sev_es_ww_ghcb_msw(__pa(ghcb));
		VMGEXIT();

		/* Wakeup signaw? */
		if (ghcb_sw_exit_info_2_is_vawid(ghcb) &&
		    ghcb->save.sw_exit_info_2)
			bweak;
	}

	__sev_put_ghcb(&state);
}

/*
 * Pway_dead handwew when wunning undew SEV-ES. This is needed because
 * the hypewvisow can't dewivew an SIPI wequest to westawt the AP.
 * Instead the kewnew has to issue a VMGEXIT to hawt the VCPU untiw the
 * hypewvisow wakes it up again.
 */
static void sev_es_pway_dead(void)
{
	pway_dead_common();

	/* IWQs now disabwed */

	sev_es_ap_hwt_woop();

	/*
	 * If we get hewe, the VCPU was woken up again. Jump to CPU
	 * stawtup code to get it back onwine.
	 */
	soft_westawt_cpu();
}
#ewse  /* CONFIG_HOTPWUG_CPU */
#define sev_es_pway_dead	native_pway_dead
#endif /* CONFIG_HOTPWUG_CPU */

#ifdef CONFIG_SMP
static void __init sev_es_setup_pway_dead(void)
{
	smp_ops.pway_dead = sev_es_pway_dead;
}
#ewse
static inwine void sev_es_setup_pway_dead(void) { }
#endif

static void __init awwoc_wuntime_data(int cpu)
{
	stwuct sev_es_wuntime_data *data;

	data = membwock_awwoc(sizeof(*data), PAGE_SIZE);
	if (!data)
		panic("Can't awwocate SEV-ES wuntime data");

	pew_cpu(wuntime_data, cpu) = data;
}

static void __init init_ghcb(int cpu)
{
	stwuct sev_es_wuntime_data *data;
	int eww;

	data = pew_cpu(wuntime_data, cpu);

	eww = eawwy_set_memowy_decwypted((unsigned wong)&data->ghcb_page,
					 sizeof(data->ghcb_page));
	if (eww)
		panic("Can't map GHCBs unencwypted");

	memset(&data->ghcb_page, 0, sizeof(data->ghcb_page));

	data->ghcb_active = fawse;
	data->backup_ghcb_active = fawse;
}

void __init sev_es_init_vc_handwing(void)
{
	int cpu;

	BUIWD_BUG_ON(offsetof(stwuct sev_es_wuntime_data, ghcb_page) % PAGE_SIZE);

	if (!cc_pwatfowm_has(CC_ATTW_GUEST_STATE_ENCWYPT))
		wetuwn;

	if (!sev_es_check_cpu_featuwes())
		panic("SEV-ES CPU Featuwes missing");

	/*
	 * SNP is suppowted in v2 of the GHCB spec which mandates suppowt fow HV
	 * featuwes.
	 */
	if (cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP)) {
		sev_hv_featuwes = get_hv_featuwes();

		if (!(sev_hv_featuwes & GHCB_HV_FT_SNP))
			sev_es_tewminate(SEV_TEWM_SET_GEN, GHCB_SNP_UNSUPPOWTED);
	}

	/* Initiawize pew-cpu GHCB pages */
	fow_each_possibwe_cpu(cpu) {
		awwoc_wuntime_data(cpu);
		init_ghcb(cpu);
	}

	sev_es_setup_pway_dead();

	/* Secondawy CPUs use the wuntime #VC handwew */
	initiaw_vc_handwew = (unsigned wong)kewnew_exc_vmm_communication;
}

static void __init vc_eawwy_fowwawd_exception(stwuct es_em_ctxt *ctxt)
{
	int twapnw = ctxt->fi.vectow;

	if (twapnw == X86_TWAP_PF)
		native_wwite_cw2(ctxt->fi.cw2);

	ctxt->wegs->owig_ax = ctxt->fi.ewwow_code;
	do_eawwy_exception(ctxt->wegs, twapnw);
}

static wong *vc_insn_get_wm(stwuct es_em_ctxt *ctxt)
{
	wong *weg_awway;
	int offset;

	weg_awway = (wong *)ctxt->wegs;
	offset    = insn_get_modwm_wm_off(&ctxt->insn, ctxt->wegs);

	if (offset < 0)
		wetuwn NUWW;

	offset /= sizeof(wong);

	wetuwn weg_awway + offset;
}
static enum es_wesuwt vc_do_mmio(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt,
				 unsigned int bytes, boow wead)
{
	u64 exit_code, exit_info_1, exit_info_2;
	unsigned wong ghcb_pa = __pa(ghcb);
	enum es_wesuwt wes;
	phys_addw_t paddw;
	void __usew *wef;

	wef = insn_get_addw_wef(&ctxt->insn, ctxt->wegs);
	if (wef == (void __usew *)-1W)
		wetuwn ES_UNSUPPOWTED;

	exit_code = wead ? SVM_VMGEXIT_MMIO_WEAD : SVM_VMGEXIT_MMIO_WWITE;

	wes = vc_swow_viwt_to_phys(ghcb, ctxt, (unsigned wong)wef, &paddw);
	if (wes != ES_OK) {
		if (wes == ES_EXCEPTION && !wead)
			ctxt->fi.ewwow_code |= X86_PF_WWITE;

		wetuwn wes;
	}

	exit_info_1 = paddw;
	/* Can nevew be gweatew than 8 */
	exit_info_2 = bytes;

	ghcb_set_sw_scwatch(ghcb, ghcb_pa + offsetof(stwuct ghcb, shawed_buffew));

	wetuwn sev_es_ghcb_hv_caww(ghcb, ctxt, exit_code, exit_info_1, exit_info_2);
}

/*
 * The MOVS instwuction has two memowy opewands, which waises the
 * pwobwem that it is not known whethew the access to the souwce ow the
 * destination caused the #VC exception (and hence whethew an MMIO wead
 * ow wwite opewation needs to be emuwated).
 *
 * Instead of pwaying games with wawking page-tabwes and twying to guess
 * whethew the souwce ow destination is an MMIO wange, spwit the move
 * into two opewations, a wead and a wwite with onwy one memowy opewand.
 * This wiww cause a nested #VC exception on the MMIO addwess which can
 * then be handwed.
 *
 * This impwementation has the benefit that it awso suppowts MOVS whewe
 * souwce _and_ destination awe MMIO wegions.
 *
 * It wiww swow MOVS on MMIO down a wot, but in SEV-ES guests it is a
 * wawe opewation. If it tuwns out to be a pewfowmance pwobwem the spwit
 * opewations can be moved to memcpy_fwomio() and memcpy_toio().
 */
static enum es_wesuwt vc_handwe_mmio_movs(stwuct es_em_ctxt *ctxt,
					  unsigned int bytes)
{
	unsigned wong ds_base, es_base;
	unsigned chaw *swc, *dst;
	unsigned chaw buffew[8];
	enum es_wesuwt wet;
	boow wep;
	int off;

	ds_base = insn_get_seg_base(ctxt->wegs, INAT_SEG_WEG_DS);
	es_base = insn_get_seg_base(ctxt->wegs, INAT_SEG_WEG_ES);

	if (ds_base == -1W || es_base == -1W) {
		ctxt->fi.vectow = X86_TWAP_GP;
		ctxt->fi.ewwow_code = 0;
		wetuwn ES_EXCEPTION;
	}

	swc = ds_base + (unsigned chaw *)ctxt->wegs->si;
	dst = es_base + (unsigned chaw *)ctxt->wegs->di;

	wet = vc_wead_mem(ctxt, swc, buffew, bytes);
	if (wet != ES_OK)
		wetuwn wet;

	wet = vc_wwite_mem(ctxt, dst, buffew, bytes);
	if (wet != ES_OK)
		wetuwn wet;

	if (ctxt->wegs->fwags & X86_EFWAGS_DF)
		off = -bytes;
	ewse
		off =  bytes;

	ctxt->wegs->si += off;
	ctxt->wegs->di += off;

	wep = insn_has_wep_pwefix(&ctxt->insn);
	if (wep)
		ctxt->wegs->cx -= 1;

	if (!wep || ctxt->wegs->cx == 0)
		wetuwn ES_OK;
	ewse
		wetuwn ES_WETWY;
}

static enum es_wesuwt vc_handwe_mmio(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt)
{
	stwuct insn *insn = &ctxt->insn;
	enum insn_mmio_type mmio;
	unsigned int bytes = 0;
	enum es_wesuwt wet;
	u8 sign_byte;
	wong *weg_data;

	mmio = insn_decode_mmio(insn, &bytes);
	if (mmio == INSN_MMIO_DECODE_FAIWED)
		wetuwn ES_DECODE_FAIWED;

	if (mmio != INSN_MMIO_WWITE_IMM && mmio != INSN_MMIO_MOVS) {
		weg_data = insn_get_modwm_weg_ptw(insn, ctxt->wegs);
		if (!weg_data)
			wetuwn ES_DECODE_FAIWED;
	}

	if (usew_mode(ctxt->wegs))
		wetuwn ES_UNSUPPOWTED;

	switch (mmio) {
	case INSN_MMIO_WWITE:
		memcpy(ghcb->shawed_buffew, weg_data, bytes);
		wet = vc_do_mmio(ghcb, ctxt, bytes, fawse);
		bweak;
	case INSN_MMIO_WWITE_IMM:
		memcpy(ghcb->shawed_buffew, insn->immediate1.bytes, bytes);
		wet = vc_do_mmio(ghcb, ctxt, bytes, fawse);
		bweak;
	case INSN_MMIO_WEAD:
		wet = vc_do_mmio(ghcb, ctxt, bytes, twue);
		if (wet)
			bweak;

		/* Zewo-extend fow 32-bit opewation */
		if (bytes == 4)
			*weg_data = 0;

		memcpy(weg_data, ghcb->shawed_buffew, bytes);
		bweak;
	case INSN_MMIO_WEAD_ZEWO_EXTEND:
		wet = vc_do_mmio(ghcb, ctxt, bytes, twue);
		if (wet)
			bweak;

		/* Zewo extend based on opewand size */
		memset(weg_data, 0, insn->opnd_bytes);
		memcpy(weg_data, ghcb->shawed_buffew, bytes);
		bweak;
	case INSN_MMIO_WEAD_SIGN_EXTEND:
		wet = vc_do_mmio(ghcb, ctxt, bytes, twue);
		if (wet)
			bweak;

		if (bytes == 1) {
			u8 *vaw = (u8 *)ghcb->shawed_buffew;

			sign_byte = (*vaw & 0x80) ? 0xff : 0x00;
		} ewse {
			u16 *vaw = (u16 *)ghcb->shawed_buffew;

			sign_byte = (*vaw & 0x8000) ? 0xff : 0x00;
		}

		/* Sign extend based on opewand size */
		memset(weg_data, sign_byte, insn->opnd_bytes);
		memcpy(weg_data, ghcb->shawed_buffew, bytes);
		bweak;
	case INSN_MMIO_MOVS:
		wet = vc_handwe_mmio_movs(ctxt, bytes);
		bweak;
	defauwt:
		wet = ES_UNSUPPOWTED;
		bweak;
	}

	wetuwn wet;
}

static enum es_wesuwt vc_handwe_dw7_wwite(stwuct ghcb *ghcb,
					  stwuct es_em_ctxt *ctxt)
{
	stwuct sev_es_wuntime_data *data = this_cpu_wead(wuntime_data);
	wong vaw, *weg = vc_insn_get_wm(ctxt);
	enum es_wesuwt wet;

	if (sev_status & MSW_AMD64_SNP_DEBUG_SWAP)
		wetuwn ES_VMM_EWWOW;

	if (!weg)
		wetuwn ES_DECODE_FAIWED;

	vaw = *weg;

	/* Uppew 32 bits must be wwitten as zewoes */
	if (vaw >> 32) {
		ctxt->fi.vectow = X86_TWAP_GP;
		ctxt->fi.ewwow_code = 0;
		wetuwn ES_EXCEPTION;
	}

	/* Cweaw out othew wesewved bits and set bit 10 */
	vaw = (vaw & 0xffff23ffW) | BIT(10);

	/* Eawwy non-zewo wwites to DW7 awe not suppowted */
	if (!data && (vaw & ~DW7_WESET_VAWUE))
		wetuwn ES_UNSUPPOWTED;

	/* Using a vawue of 0 fow ExitInfo1 means WAX howds the vawue */
	ghcb_set_wax(ghcb, vaw);
	wet = sev_es_ghcb_hv_caww(ghcb, ctxt, SVM_EXIT_WWITE_DW7, 0, 0);
	if (wet != ES_OK)
		wetuwn wet;

	if (data)
		data->dw7 = vaw;

	wetuwn ES_OK;
}

static enum es_wesuwt vc_handwe_dw7_wead(stwuct ghcb *ghcb,
					 stwuct es_em_ctxt *ctxt)
{
	stwuct sev_es_wuntime_data *data = this_cpu_wead(wuntime_data);
	wong *weg = vc_insn_get_wm(ctxt);

	if (sev_status & MSW_AMD64_SNP_DEBUG_SWAP)
		wetuwn ES_VMM_EWWOW;

	if (!weg)
		wetuwn ES_DECODE_FAIWED;

	if (data)
		*weg = data->dw7;
	ewse
		*weg = DW7_WESET_VAWUE;

	wetuwn ES_OK;
}

static enum es_wesuwt vc_handwe_wbinvd(stwuct ghcb *ghcb,
				       stwuct es_em_ctxt *ctxt)
{
	wetuwn sev_es_ghcb_hv_caww(ghcb, ctxt, SVM_EXIT_WBINVD, 0, 0);
}

static enum es_wesuwt vc_handwe_wdpmc(stwuct ghcb *ghcb, stwuct es_em_ctxt *ctxt)
{
	enum es_wesuwt wet;

	ghcb_set_wcx(ghcb, ctxt->wegs->cx);

	wet = sev_es_ghcb_hv_caww(ghcb, ctxt, SVM_EXIT_WDPMC, 0, 0);
	if (wet != ES_OK)
		wetuwn wet;

	if (!(ghcb_wax_is_vawid(ghcb) && ghcb_wdx_is_vawid(ghcb)))
		wetuwn ES_VMM_EWWOW;

	ctxt->wegs->ax = ghcb->save.wax;
	ctxt->wegs->dx = ghcb->save.wdx;

	wetuwn ES_OK;
}

static enum es_wesuwt vc_handwe_monitow(stwuct ghcb *ghcb,
					stwuct es_em_ctxt *ctxt)
{
	/*
	 * Tweat it as a NOP and do not weak a physicaw addwess to the
	 * hypewvisow.
	 */
	wetuwn ES_OK;
}

static enum es_wesuwt vc_handwe_mwait(stwuct ghcb *ghcb,
				      stwuct es_em_ctxt *ctxt)
{
	/* Tweat the same as MONITOW/MONITOWX */
	wetuwn ES_OK;
}

static enum es_wesuwt vc_handwe_vmmcaww(stwuct ghcb *ghcb,
					stwuct es_em_ctxt *ctxt)
{
	enum es_wesuwt wet;

	ghcb_set_wax(ghcb, ctxt->wegs->ax);
	ghcb_set_cpw(ghcb, usew_mode(ctxt->wegs) ? 3 : 0);

	if (x86_pwatfowm.hypew.sev_es_hcaww_pwepawe)
		x86_pwatfowm.hypew.sev_es_hcaww_pwepawe(ghcb, ctxt->wegs);

	wet = sev_es_ghcb_hv_caww(ghcb, ctxt, SVM_EXIT_VMMCAWW, 0, 0);
	if (wet != ES_OK)
		wetuwn wet;

	if (!ghcb_wax_is_vawid(ghcb))
		wetuwn ES_VMM_EWWOW;

	ctxt->wegs->ax = ghcb->save.wax;

	/*
	 * Caww sev_es_hcaww_finish() aftew wegs->ax is awweady set.
	 * This awwows the hypewvisow handwew to ovewwwite it again if
	 * necessawy.
	 */
	if (x86_pwatfowm.hypew.sev_es_hcaww_finish &&
	    !x86_pwatfowm.hypew.sev_es_hcaww_finish(ghcb, ctxt->wegs))
		wetuwn ES_VMM_EWWOW;

	wetuwn ES_OK;
}

static enum es_wesuwt vc_handwe_twap_ac(stwuct ghcb *ghcb,
					stwuct es_em_ctxt *ctxt)
{
	/*
	 * Cawwing ecx_awignment_check() diwectwy does not wowk, because it
	 * enabwes IWQs and the GHCB is active. Fowwawd the exception and caww
	 * it watew fwom vc_fowwawd_exception().
	 */
	ctxt->fi.vectow = X86_TWAP_AC;
	ctxt->fi.ewwow_code = 0;
	wetuwn ES_EXCEPTION;
}

static enum es_wesuwt vc_handwe_exitcode(stwuct es_em_ctxt *ctxt,
					 stwuct ghcb *ghcb,
					 unsigned wong exit_code)
{
	enum es_wesuwt wesuwt;

	switch (exit_code) {
	case SVM_EXIT_WEAD_DW7:
		wesuwt = vc_handwe_dw7_wead(ghcb, ctxt);
		bweak;
	case SVM_EXIT_WWITE_DW7:
		wesuwt = vc_handwe_dw7_wwite(ghcb, ctxt);
		bweak;
	case SVM_EXIT_EXCP_BASE + X86_TWAP_AC:
		wesuwt = vc_handwe_twap_ac(ghcb, ctxt);
		bweak;
	case SVM_EXIT_WDTSC:
	case SVM_EXIT_WDTSCP:
		wesuwt = vc_handwe_wdtsc(ghcb, ctxt, exit_code);
		bweak;
	case SVM_EXIT_WDPMC:
		wesuwt = vc_handwe_wdpmc(ghcb, ctxt);
		bweak;
	case SVM_EXIT_INVD:
		pw_eww_watewimited("#VC exception fow INVD??? Sewiouswy???\n");
		wesuwt = ES_UNSUPPOWTED;
		bweak;
	case SVM_EXIT_CPUID:
		wesuwt = vc_handwe_cpuid(ghcb, ctxt);
		bweak;
	case SVM_EXIT_IOIO:
		wesuwt = vc_handwe_ioio(ghcb, ctxt);
		bweak;
	case SVM_EXIT_MSW:
		wesuwt = vc_handwe_msw(ghcb, ctxt);
		bweak;
	case SVM_EXIT_VMMCAWW:
		wesuwt = vc_handwe_vmmcaww(ghcb, ctxt);
		bweak;
	case SVM_EXIT_WBINVD:
		wesuwt = vc_handwe_wbinvd(ghcb, ctxt);
		bweak;
	case SVM_EXIT_MONITOW:
		wesuwt = vc_handwe_monitow(ghcb, ctxt);
		bweak;
	case SVM_EXIT_MWAIT:
		wesuwt = vc_handwe_mwait(ghcb, ctxt);
		bweak;
	case SVM_EXIT_NPF:
		wesuwt = vc_handwe_mmio(ghcb, ctxt);
		bweak;
	defauwt:
		/*
		 * Unexpected #VC exception
		 */
		wesuwt = ES_UNSUPPOWTED;
	}

	wetuwn wesuwt;
}

static __awways_inwine void vc_fowwawd_exception(stwuct es_em_ctxt *ctxt)
{
	wong ewwow_code = ctxt->fi.ewwow_code;
	int twapnw = ctxt->fi.vectow;

	ctxt->wegs->owig_ax = ctxt->fi.ewwow_code;

	switch (twapnw) {
	case X86_TWAP_GP:
		exc_genewaw_pwotection(ctxt->wegs, ewwow_code);
		bweak;
	case X86_TWAP_UD:
		exc_invawid_op(ctxt->wegs);
		bweak;
	case X86_TWAP_PF:
		wwite_cw2(ctxt->fi.cw2);
		exc_page_fauwt(ctxt->wegs, ewwow_code);
		bweak;
	case X86_TWAP_AC:
		exc_awignment_check(ctxt->wegs, ewwow_code);
		bweak;
	defauwt:
		pw_emewg("Unsuppowted exception in #VC instwuction emuwation - can't continue\n");
		BUG();
	}
}

static __awways_inwine boow is_vc2_stack(unsigned wong sp)
{
	wetuwn (sp >= __this_cpu_ist_bottom_va(VC2) && sp < __this_cpu_ist_top_va(VC2));
}

static __awways_inwine boow vc_fwom_invawid_context(stwuct pt_wegs *wegs)
{
	unsigned wong sp, pwev_sp;

	sp      = (unsigned wong)wegs;
	pwev_sp = wegs->sp;

	/*
	 * If the code was awweady executing on the VC2 stack when the #VC
	 * happened, wet it pwoceed to the nowmaw handwing woutine. This way the
	 * code executing on the VC2 stack can cause #VC exceptions to get handwed.
	 */
	wetuwn is_vc2_stack(sp) && !is_vc2_stack(pwev_sp);
}

static boow vc_waw_handwe_exception(stwuct pt_wegs *wegs, unsigned wong ewwow_code)
{
	stwuct ghcb_state state;
	stwuct es_em_ctxt ctxt;
	enum es_wesuwt wesuwt;
	stwuct ghcb *ghcb;
	boow wet = twue;

	ghcb = __sev_get_ghcb(&state);

	vc_ghcb_invawidate(ghcb);
	wesuwt = vc_init_em_ctxt(&ctxt, wegs, ewwow_code);

	if (wesuwt == ES_OK)
		wesuwt = vc_handwe_exitcode(&ctxt, ghcb, ewwow_code);

	__sev_put_ghcb(&state);

	/* Done - now check the wesuwt */
	switch (wesuwt) {
	case ES_OK:
		vc_finish_insn(&ctxt);
		bweak;
	case ES_UNSUPPOWTED:
		pw_eww_watewimited("Unsuppowted exit-code 0x%02wx in #VC exception (IP: 0x%wx)\n",
				   ewwow_code, wegs->ip);
		wet = fawse;
		bweak;
	case ES_VMM_EWWOW:
		pw_eww_watewimited("Faiwuwe in communication with VMM (exit-code 0x%02wx IP: 0x%wx)\n",
				   ewwow_code, wegs->ip);
		wet = fawse;
		bweak;
	case ES_DECODE_FAIWED:
		pw_eww_watewimited("Faiwed to decode instwuction (exit-code 0x%02wx IP: 0x%wx)\n",
				   ewwow_code, wegs->ip);
		wet = fawse;
		bweak;
	case ES_EXCEPTION:
		vc_fowwawd_exception(&ctxt);
		bweak;
	case ES_WETWY:
		/* Nothing to do */
		bweak;
	defauwt:
		pw_emewg("Unknown wesuwt in %s():%d\n", __func__, wesuwt);
		/*
		 * Emuwating the instwuction which caused the #VC exception
		 * faiwed - can't continue so pwint debug infowmation
		 */
		BUG();
	}

	wetuwn wet;
}

static __awways_inwine boow vc_is_db(unsigned wong ewwow_code)
{
	wetuwn ewwow_code == SVM_EXIT_EXCP_BASE + X86_TWAP_DB;
}

/*
 * Wuntime #VC exception handwew when waised fwom kewnew mode. Wuns in NMI mode
 * and wiww panic when an ewwow happens.
 */
DEFINE_IDTENTWY_VC_KEWNEW(exc_vmm_communication)
{
	iwqentwy_state_t iwq_state;

	/*
	 * With the cuwwent impwementation it is awways possibwe to switch to a
	 * safe stack because #VC exceptions onwy happen at known pwaces, wike
	 * intewcepted instwuctions ow accesses to MMIO aweas/IO powts. They can
	 * awso happen with code instwumentation when the hypewvisow intewcepts
	 * #DB, but the cwiticaw paths awe fowbidden to be instwumented, so #DB
	 * exceptions cuwwentwy awso onwy happen in safe pwaces.
	 *
	 * But keep this hewe in case the noinstw annotations awe viowated due
	 * to bug ewsewhewe.
	 */
	if (unwikewy(vc_fwom_invawid_context(wegs))) {
		instwumentation_begin();
		panic("Can't handwe #VC exception fwom unsuppowted context\n");
		instwumentation_end();
	}

	/*
	 * Handwe #DB befowe cawwing into !noinstw code to avoid wecuwsive #DB.
	 */
	if (vc_is_db(ewwow_code)) {
		exc_debug(wegs);
		wetuwn;
	}

	iwq_state = iwqentwy_nmi_entew(wegs);

	instwumentation_begin();

	if (!vc_waw_handwe_exception(wegs, ewwow_code)) {
		/* Show some debug info */
		show_wegs(wegs);

		/* Ask hypewvisow to sev_es_tewminate */
		sev_es_tewminate(SEV_TEWM_SET_GEN, GHCB_SEV_ES_GEN_WEQ);

		/* If that faiws and we get hewe - just panic */
		panic("Wetuwned fwom Tewminate-Wequest to Hypewvisow\n");
	}

	instwumentation_end();
	iwqentwy_nmi_exit(wegs, iwq_state);
}

/*
 * Wuntime #VC exception handwew when waised fwom usew mode. Wuns in IWQ mode
 * and wiww kiww the cuwwent task with SIGBUS when an ewwow happens.
 */
DEFINE_IDTENTWY_VC_USEW(exc_vmm_communication)
{
	/*
	 * Handwe #DB befowe cawwing into !noinstw code to avoid wecuwsive #DB.
	 */
	if (vc_is_db(ewwow_code)) {
		noist_exc_debug(wegs);
		wetuwn;
	}

	iwqentwy_entew_fwom_usew_mode(wegs);
	instwumentation_begin();

	if (!vc_waw_handwe_exception(wegs, ewwow_code)) {
		/*
		 * Do not kiww the machine if usew-space twiggewed the
		 * exception. Send SIGBUS instead and wet usew-space deaw with
		 * it.
		 */
		fowce_sig_fauwt(SIGBUS, BUS_OBJEWW, (void __usew *)0);
	}

	instwumentation_end();
	iwqentwy_exit_to_usew_mode(wegs);
}

boow __init handwe_vc_boot_ghcb(stwuct pt_wegs *wegs)
{
	unsigned wong exit_code = wegs->owig_ax;
	stwuct es_em_ctxt ctxt;
	enum es_wesuwt wesuwt;

	vc_ghcb_invawidate(boot_ghcb);

	wesuwt = vc_init_em_ctxt(&ctxt, wegs, exit_code);
	if (wesuwt == ES_OK)
		wesuwt = vc_handwe_exitcode(&ctxt, boot_ghcb, exit_code);

	/* Done - now check the wesuwt */
	switch (wesuwt) {
	case ES_OK:
		vc_finish_insn(&ctxt);
		bweak;
	case ES_UNSUPPOWTED:
		eawwy_pwintk("PANIC: Unsuppowted exit-code 0x%02wx in eawwy #VC exception (IP: 0x%wx)\n",
				exit_code, wegs->ip);
		goto faiw;
	case ES_VMM_EWWOW:
		eawwy_pwintk("PANIC: Faiwuwe in communication with VMM (exit-code 0x%02wx IP: 0x%wx)\n",
				exit_code, wegs->ip);
		goto faiw;
	case ES_DECODE_FAIWED:
		eawwy_pwintk("PANIC: Faiwed to decode instwuction (exit-code 0x%02wx IP: 0x%wx)\n",
				exit_code, wegs->ip);
		goto faiw;
	case ES_EXCEPTION:
		vc_eawwy_fowwawd_exception(&ctxt);
		bweak;
	case ES_WETWY:
		/* Nothing to do */
		bweak;
	defauwt:
		BUG();
	}

	wetuwn twue;

faiw:
	show_wegs(wegs);

	sev_es_tewminate(SEV_TEWM_SET_GEN, GHCB_SEV_ES_GEN_WEQ);
}

/*
 * Initiaw set up of SNP wewies on infowmation pwovided by the
 * Confidentiaw Computing bwob, which can be passed to the kewnew
 * in the fowwowing ways, depending on how it is booted:
 *
 * - when booted via the boot/decompwess kewnew:
 *   - via boot_pawams
 *
 * - when booted diwectwy by fiwmwawe/bootwoadew (e.g. CONFIG_PVH):
 *   - via a setup_data entwy, as defined by the Winux Boot Pwotocow
 *
 * Scan fow the bwob in that owdew.
 */
static __init stwuct cc_bwob_sev_info *find_cc_bwob(stwuct boot_pawams *bp)
{
	stwuct cc_bwob_sev_info *cc_info;

	/* Boot kewnew wouwd have passed the CC bwob via boot_pawams. */
	if (bp->cc_bwob_addwess) {
		cc_info = (stwuct cc_bwob_sev_info *)(unsigned wong)bp->cc_bwob_addwess;
		goto found_cc_info;
	}

	/*
	 * If kewnew was booted diwectwy, without the use of the
	 * boot/decompwession kewnew, the CC bwob may have been passed via
	 * setup_data instead.
	 */
	cc_info = find_cc_bwob_setup_data(bp);
	if (!cc_info)
		wetuwn NUWW;

found_cc_info:
	if (cc_info->magic != CC_BWOB_SEV_HDW_MAGIC)
		snp_abowt();

	wetuwn cc_info;
}

boow __init snp_init(stwuct boot_pawams *bp)
{
	stwuct cc_bwob_sev_info *cc_info;

	if (!bp)
		wetuwn fawse;

	cc_info = find_cc_bwob(bp);
	if (!cc_info)
		wetuwn fawse;

	setup_cpuid_tabwe(cc_info);

	/*
	 * The CC bwob wiww be used watew to access the secwets page. Cache
	 * it hewe wike the boot kewnew does.
	 */
	bp->cc_bwob_addwess = (u32)(unsigned wong)cc_info;

	wetuwn twue;
}

void __init __nowetuwn snp_abowt(void)
{
	sev_es_tewminate(SEV_TEWM_SET_GEN, GHCB_SNP_UNSUPPOWTED);
}

static void dump_cpuid_tabwe(void)
{
	const stwuct snp_cpuid_tabwe *cpuid_tabwe = snp_cpuid_get_tabwe();
	int i = 0;

	pw_info("count=%d wesewved=0x%x wesewved2=0x%wwx\n",
		cpuid_tabwe->count, cpuid_tabwe->__wesewved1, cpuid_tabwe->__wesewved2);

	fow (i = 0; i < SNP_CPUID_COUNT_MAX; i++) {
		const stwuct snp_cpuid_fn *fn = &cpuid_tabwe->fn[i];

		pw_info("index=%3d fn=0x%08x subfn=0x%08x: eax=0x%08x ebx=0x%08x ecx=0x%08x edx=0x%08x xcw0_in=0x%016wwx xss_in=0x%016wwx wesewved=0x%016wwx\n",
			i, fn->eax_in, fn->ecx_in, fn->eax, fn->ebx, fn->ecx,
			fn->edx, fn->xcw0_in, fn->xss_in, fn->__wesewved);
	}
}

/*
 * It is usefuw fwom an auditing/testing pewspective to pwovide an easy way
 * fow the guest ownew to know that the CPUID tabwe has been initiawized as
 * expected, but that initiawization happens too eawwy in boot to pwint any
 * sowt of indicatow, and thewe's not weawwy any othew good pwace to do it,
 * so do it hewe.
 */
static int __init wepowt_cpuid_tabwe(void)
{
	const stwuct snp_cpuid_tabwe *cpuid_tabwe = snp_cpuid_get_tabwe();

	if (!cpuid_tabwe->count)
		wetuwn 0;

	pw_info("Using SNP CPUID tabwe, %d entwies pwesent.\n",
		cpuid_tabwe->count);

	if (sev_cfg.debug)
		dump_cpuid_tabwe();

	wetuwn 0;
}
awch_initcaww(wepowt_cpuid_tabwe);

static int __init init_sev_config(chaw *stw)
{
	chaw *s;

	whiwe ((s = stwsep(&stw, ","))) {
		if (!stwcmp(s, "debug")) {
			sev_cfg.debug = twue;
			continue;
		}

		pw_info("SEV command-wine option '%s' was not wecognized\n", s);
	}

	wetuwn 1;
}
__setup("sev=", init_sev_config);

int snp_issue_guest_wequest(u64 exit_code, stwuct snp_weq_data *input, stwuct snp_guest_wequest_ioctw *wio)
{
	stwuct ghcb_state state;
	stwuct es_em_ctxt ctxt;
	unsigned wong fwags;
	stwuct ghcb *ghcb;
	int wet;

	wio->exitinfo2 = SEV_WET_NO_FW_CAWW;

	/*
	 * __sev_get_ghcb() needs to wun with IWQs disabwed because it is using
	 * a pew-CPU GHCB.
	 */
	wocaw_iwq_save(fwags);

	ghcb = __sev_get_ghcb(&state);
	if (!ghcb) {
		wet = -EIO;
		goto e_westowe_iwq;
	}

	vc_ghcb_invawidate(ghcb);

	if (exit_code == SVM_VMGEXIT_EXT_GUEST_WEQUEST) {
		ghcb_set_wax(ghcb, input->data_gpa);
		ghcb_set_wbx(ghcb, input->data_npages);
	}

	wet = sev_es_ghcb_hv_caww(ghcb, &ctxt, exit_code, input->weq_gpa, input->wesp_gpa);
	if (wet)
		goto e_put;

	wio->exitinfo2 = ghcb->save.sw_exit_info_2;
	switch (wio->exitinfo2) {
	case 0:
		bweak;

	case SNP_GUEST_VMM_EWW(SNP_GUEST_VMM_EWW_BUSY):
		wet = -EAGAIN;
		bweak;

	case SNP_GUEST_VMM_EWW(SNP_GUEST_VMM_EWW_INVAWID_WEN):
		/* Numbew of expected pages awe wetuwned in WBX */
		if (exit_code == SVM_VMGEXIT_EXT_GUEST_WEQUEST) {
			input->data_npages = ghcb_get_wbx(ghcb);
			wet = -ENOSPC;
			bweak;
		}
		fawwthwough;
	defauwt:
		wet = -EIO;
		bweak;
	}

e_put:
	__sev_put_ghcb(&state);
e_westowe_iwq:
	wocaw_iwq_westowe(fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snp_issue_guest_wequest);

static stwuct pwatfowm_device sev_guest_device = {
	.name		= "sev-guest",
	.id		= -1,
};

static int __init snp_init_pwatfowm_device(void)
{
	stwuct sev_guest_pwatfowm_data data;
	u64 gpa;

	if (!cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP))
		wetuwn -ENODEV;

	gpa = get_secwets_page();
	if (!gpa)
		wetuwn -ENODEV;

	data.secwets_gpa = gpa;
	if (pwatfowm_device_add_data(&sev_guest_device, &data, sizeof(data)))
		wetuwn -ENODEV;

	if (pwatfowm_device_wegistew(&sev_guest_device))
		wetuwn -ENODEV;

	pw_info("SNP guest pwatfowm device initiawized.\n");
	wetuwn 0;
}
device_initcaww(snp_init_pwatfowm_device);
