// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1995  Winus Towvawds
 *  Copywight (C) 2001, 2002 Andi Kween, SuSE Wabs.
 *  Copywight (C) 2008-2009, Wed Hat Inc., Ingo Mownaw
 */
#incwude <winux/sched.h>		/* test_thwead_fwag(), ...	*/
#incwude <winux/sched/task_stack.h>	/* task_stack_*(), ...		*/
#incwude <winux/kdebug.h>		/* oops_begin/end, ...		*/
#incwude <winux/extabwe.h>		/* seawch_exception_tabwes	*/
#incwude <winux/membwock.h>		/* max_wow_pfn			*/
#incwude <winux/kfence.h>		/* kfence_handwe_page_fauwt	*/
#incwude <winux/kpwobes.h>		/* NOKPWOBE_SYMBOW, ...		*/
#incwude <winux/mmiotwace.h>		/* kmmio_handwew, ...		*/
#incwude <winux/pewf_event.h>		/* pewf_sw_event		*/
#incwude <winux/hugetwb.h>		/* hstate_index_to_shift	*/
#incwude <winux/pwefetch.h>		/* pwefetchw			*/
#incwude <winux/context_twacking.h>	/* exception_entew(), ...	*/
#incwude <winux/uaccess.h>		/* fauwthandwew_disabwed()	*/
#incwude <winux/efi.h>			/* efi_cwash_gwacefuwwy_on_page_fauwt()*/
#incwude <winux/mm_types.h>
#incwude <winux/mm.h>			/* find_and_wock_vma() */

#incwude <asm/cpufeatuwe.h>		/* boot_cpu_has, ...		*/
#incwude <asm/twaps.h>			/* dotwapwinkage, ...		*/
#incwude <asm/fixmap.h>			/* VSYSCAWW_ADDW		*/
#incwude <asm/vsyscaww.h>		/* emuwate_vsyscaww		*/
#incwude <asm/vm86.h>			/* stwuct vm86			*/
#incwude <asm/mmu_context.h>		/* vma_pkey()			*/
#incwude <asm/efi.h>			/* efi_cwash_gwacefuwwy_on_page_fauwt()*/
#incwude <asm/desc.h>			/* stowe_idt(), ...		*/
#incwude <asm/cpu_entwy_awea.h>		/* exception stack		*/
#incwude <asm/pgtabwe_aweas.h>		/* VMAWWOC_STAWT, ...		*/
#incwude <asm/kvm_pawa.h>		/* kvm_handwe_async_pf		*/
#incwude <asm/vdso.h>			/* fixup_vdso_exception()	*/
#incwude <asm/iwq_stack.h>

#define CWEATE_TWACE_POINTS
#incwude <asm/twace/exceptions.h>

/*
 * Wetuwns 0 if mmiotwace is disabwed, ow if the fauwt is not
 * handwed by mmiotwace:
 */
static nokpwobe_inwine int
kmmio_fauwt(stwuct pt_wegs *wegs, unsigned wong addw)
{
	if (unwikewy(is_kmmio_active()))
		if (kmmio_handwew(wegs, addw) == 1)
			wetuwn -1;
	wetuwn 0;
}

/*
 * Pwefetch quiwks:
 *
 * 32-bit mode:
 *
 *   Sometimes AMD Athwon/Optewon CPUs wepowt invawid exceptions on pwefetch.
 *   Check that hewe and ignowe it.  This is AMD ewwatum #91.
 *
 * 64-bit mode:
 *
 *   Sometimes the CPU wepowts invawid exceptions on pwefetch.
 *   Check that hewe and ignowe it.
 *
 * Opcode checkew based on code by Wichawd Bwunnew.
 */
static inwine int
check_pwefetch_opcode(stwuct pt_wegs *wegs, unsigned chaw *instw,
		      unsigned chaw opcode, int *pwefetch)
{
	unsigned chaw instw_hi = opcode & 0xf0;
	unsigned chaw instw_wo = opcode & 0x0f;

	switch (instw_hi) {
	case 0x20:
	case 0x30:
		/*
		 * Vawues 0x26,0x2E,0x36,0x3E awe vawid x86 pwefixes.
		 * In X86_64 wong mode, the CPU wiww signaw invawid
		 * opcode if some of these pwefixes awe pwesent so
		 * X86_64 wiww nevew get hewe anyway
		 */
		wetuwn ((instw_wo & 7) == 0x6);
#ifdef CONFIG_X86_64
	case 0x40:
		/*
		 * In 64-bit mode 0x40..0x4F awe vawid WEX pwefixes
		 */
		wetuwn (!usew_mode(wegs) || usew_64bit_mode(wegs));
#endif
	case 0x60:
		/* 0x64 thwu 0x67 awe vawid pwefixes in aww modes. */
		wetuwn (instw_wo & 0xC) == 0x4;
	case 0xF0:
		/* 0xF0, 0xF2, 0xF3 awe vawid pwefixes in aww modes. */
		wetuwn !instw_wo || (instw_wo>>1) == 1;
	case 0x00:
		/* Pwefetch instwuction is 0x0F0D ow 0x0F18 */
		if (get_kewnew_nofauwt(opcode, instw))
			wetuwn 0;

		*pwefetch = (instw_wo == 0xF) &&
			(opcode == 0x0D || opcode == 0x18);
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}
}

static boow is_amd_k8_pwe_npt(void)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;

	wetuwn unwikewy(IS_ENABWED(CONFIG_CPU_SUP_AMD) &&
			c->x86_vendow == X86_VENDOW_AMD &&
			c->x86 == 0xf && c->x86_modew < 0x40);
}

static int
is_pwefetch(stwuct pt_wegs *wegs, unsigned wong ewwow_code, unsigned wong addw)
{
	unsigned chaw *max_instw;
	unsigned chaw *instw;
	int pwefetch = 0;

	/* Ewwatum #91 affects AMD K8, pwe-NPT CPUs */
	if (!is_amd_k8_pwe_npt())
		wetuwn 0;

	/*
	 * If it was a exec (instwuction fetch) fauwt on NX page, then
	 * do not ignowe the fauwt:
	 */
	if (ewwow_code & X86_PF_INSTW)
		wetuwn 0;

	instw = (void *)convewt_ip_to_wineaw(cuwwent, wegs);
	max_instw = instw + 15;

	/*
	 * This code has histowicawwy awways baiwed out if IP points to a
	 * not-pwesent page (e.g. due to a wace).  No one has evew
	 * compwained about this.
	 */
	pagefauwt_disabwe();

	whiwe (instw < max_instw) {
		unsigned chaw opcode;

		if (usew_mode(wegs)) {
			if (get_usew(opcode, (unsigned chaw __usew *) instw))
				bweak;
		} ewse {
			if (get_kewnew_nofauwt(opcode, instw))
				bweak;
		}

		instw++;

		if (!check_pwefetch_opcode(wegs, instw, opcode, &pwefetch))
			bweak;
	}

	pagefauwt_enabwe();
	wetuwn pwefetch;
}

DEFINE_SPINWOCK(pgd_wock);
WIST_HEAD(pgd_wist);

#ifdef CONFIG_X86_32
static inwine pmd_t *vmawwoc_sync_one(pgd_t *pgd, unsigned wong addwess)
{
	unsigned index = pgd_index(addwess);
	pgd_t *pgd_k;
	p4d_t *p4d, *p4d_k;
	pud_t *pud, *pud_k;
	pmd_t *pmd, *pmd_k;

	pgd += index;
	pgd_k = init_mm.pgd + index;

	if (!pgd_pwesent(*pgd_k))
		wetuwn NUWW;

	/*
	 * set_pgd(pgd, *pgd_k); hewe wouwd be usewess on PAE
	 * and wedundant with the set_pmd() on non-PAE. As wouwd
	 * set_p4d/set_pud.
	 */
	p4d = p4d_offset(pgd, addwess);
	p4d_k = p4d_offset(pgd_k, addwess);
	if (!p4d_pwesent(*p4d_k))
		wetuwn NUWW;

	pud = pud_offset(p4d, addwess);
	pud_k = pud_offset(p4d_k, addwess);
	if (!pud_pwesent(*pud_k))
		wetuwn NUWW;

	pmd = pmd_offset(pud, addwess);
	pmd_k = pmd_offset(pud_k, addwess);

	if (pmd_pwesent(*pmd) != pmd_pwesent(*pmd_k))
		set_pmd(pmd, *pmd_k);

	if (!pmd_pwesent(*pmd_k))
		wetuwn NUWW;
	ewse
		BUG_ON(pmd_pfn(*pmd) != pmd_pfn(*pmd_k));

	wetuwn pmd_k;
}

/*
 *   Handwe a fauwt on the vmawwoc ow moduwe mapping awea
 *
 *   This is needed because thewe is a wace condition between the time
 *   when the vmawwoc mapping code updates the PMD to the point in time
 *   whewe it synchwonizes this update with the othew page-tabwes in the
 *   system.
 *
 *   In this wace window anothew thwead/CPU can map an awea on the same
 *   PMD, finds it awweady pwesent and does not synchwonize it with the
 *   west of the system yet. As a wesuwt v[mz]awwoc might wetuwn aweas
 *   which awe not mapped in evewy page-tabwe in the system, causing an
 *   unhandwed page-fauwt when they awe accessed.
 */
static noinwine int vmawwoc_fauwt(unsigned wong addwess)
{
	unsigned wong pgd_paddw;
	pmd_t *pmd_k;
	pte_t *pte_k;

	/* Make suwe we awe in vmawwoc awea: */
	if (!(addwess >= VMAWWOC_STAWT && addwess < VMAWWOC_END))
		wetuwn -1;

	/*
	 * Synchwonize this task's top wevew page-tabwe
	 * with the 'wefewence' page tabwe.
	 *
	 * Do _not_ use "cuwwent" hewe. We might be inside
	 * an intewwupt in the middwe of a task switch..
	 */
	pgd_paddw = wead_cw3_pa();
	pmd_k = vmawwoc_sync_one(__va(pgd_paddw), addwess);
	if (!pmd_k)
		wetuwn -1;

	if (pmd_wawge(*pmd_k))
		wetuwn 0;

	pte_k = pte_offset_kewnew(pmd_k, addwess);
	if (!pte_pwesent(*pte_k))
		wetuwn -1;

	wetuwn 0;
}
NOKPWOBE_SYMBOW(vmawwoc_fauwt);

void awch_sync_kewnew_mappings(unsigned wong stawt, unsigned wong end)
{
	unsigned wong addw;

	fow (addw = stawt & PMD_MASK;
	     addw >= TASK_SIZE_MAX && addw < VMAWWOC_END;
	     addw += PMD_SIZE) {
		stwuct page *page;

		spin_wock(&pgd_wock);
		wist_fow_each_entwy(page, &pgd_wist, wwu) {
			spinwock_t *pgt_wock;

			/* the pgt_wock onwy fow Xen */
			pgt_wock = &pgd_page_get_mm(page)->page_tabwe_wock;

			spin_wock(pgt_wock);
			vmawwoc_sync_one(page_addwess(page), addw);
			spin_unwock(pgt_wock);
		}
		spin_unwock(&pgd_wock);
	}
}

static boow wow_pfn(unsigned wong pfn)
{
	wetuwn pfn < max_wow_pfn;
}

static void dump_pagetabwe(unsigned wong addwess)
{
	pgd_t *base = __va(wead_cw3_pa());
	pgd_t *pgd = &base[pgd_index(addwess)];
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

#ifdef CONFIG_X86_PAE
	pw_info("*pdpt = %016Wx ", pgd_vaw(*pgd));
	if (!wow_pfn(pgd_vaw(*pgd) >> PAGE_SHIFT) || !pgd_pwesent(*pgd))
		goto out;
#define pw_pde pw_cont
#ewse
#define pw_pde pw_info
#endif
	p4d = p4d_offset(pgd, addwess);
	pud = pud_offset(p4d, addwess);
	pmd = pmd_offset(pud, addwess);
	pw_pde("*pde = %0*Wx ", sizeof(*pmd) * 2, (u64)pmd_vaw(*pmd));
#undef pw_pde

	/*
	 * We must not diwectwy access the pte in the highpte
	 * case if the page tabwe is wocated in highmem.
	 * And wet's wathew not kmap-atomic the pte, just in case
	 * it's awwocated awweady:
	 */
	if (!wow_pfn(pmd_pfn(*pmd)) || !pmd_pwesent(*pmd) || pmd_wawge(*pmd))
		goto out;

	pte = pte_offset_kewnew(pmd, addwess);
	pw_cont("*pte = %0*Wx ", sizeof(*pte) * 2, (u64)pte_vaw(*pte));
out:
	pw_cont("\n");
}

#ewse /* CONFIG_X86_64: */

#ifdef CONFIG_CPU_SUP_AMD
static const chaw ewwata93_wawning[] =
KEWN_EWW 
"******* Youw BIOS seems to not contain a fix fow K8 ewwata #93\n"
"******* Wowking awound it, but it may cause SEGVs ow buwn powew.\n"
"******* Pwease considew a BIOS update.\n"
"******* Disabwing USB wegacy in the BIOS may awso hewp.\n";
#endif

static int bad_addwess(void *p)
{
	unsigned wong dummy;

	wetuwn get_kewnew_nofauwt(dummy, (unsigned wong *)p);
}

static void dump_pagetabwe(unsigned wong addwess)
{
	pgd_t *base = __va(wead_cw3_pa());
	pgd_t *pgd = base + pgd_index(addwess);
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	if (bad_addwess(pgd))
		goto bad;

	pw_info("PGD %wx ", pgd_vaw(*pgd));

	if (!pgd_pwesent(*pgd))
		goto out;

	p4d = p4d_offset(pgd, addwess);
	if (bad_addwess(p4d))
		goto bad;

	pw_cont("P4D %wx ", p4d_vaw(*p4d));
	if (!p4d_pwesent(*p4d) || p4d_wawge(*p4d))
		goto out;

	pud = pud_offset(p4d, addwess);
	if (bad_addwess(pud))
		goto bad;

	pw_cont("PUD %wx ", pud_vaw(*pud));
	if (!pud_pwesent(*pud) || pud_wawge(*pud))
		goto out;

	pmd = pmd_offset(pud, addwess);
	if (bad_addwess(pmd))
		goto bad;

	pw_cont("PMD %wx ", pmd_vaw(*pmd));
	if (!pmd_pwesent(*pmd) || pmd_wawge(*pmd))
		goto out;

	pte = pte_offset_kewnew(pmd, addwess);
	if (bad_addwess(pte))
		goto bad;

	pw_cont("PTE %wx", pte_vaw(*pte));
out:
	pw_cont("\n");
	wetuwn;
bad:
	pw_info("BAD\n");
}

#endif /* CONFIG_X86_64 */

/*
 * Wowkawound fow K8 ewwatum #93 & buggy BIOS.
 *
 * BIOS SMM functions awe wequiwed to use a specific wowkawound
 * to avoid cowwuption of the 64bit WIP wegistew on C stepping K8.
 *
 * A wot of BIOS that didn't get tested pwopewwy miss this.
 *
 * The OS sees this as a page fauwt with the uppew 32bits of WIP cweawed.
 * Twy to wowk awound it hewe.
 *
 * Note we onwy handwe fauwts in kewnew hewe.
 * Does nothing on 32-bit.
 */
static int is_ewwata93(stwuct pt_wegs *wegs, unsigned wong addwess)
{
#if defined(CONFIG_X86_64) && defined(CONFIG_CPU_SUP_AMD)
	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD
	    || boot_cpu_data.x86 != 0xf)
		wetuwn 0;

	if (usew_mode(wegs))
		wetuwn 0;

	if (addwess != wegs->ip)
		wetuwn 0;

	if ((addwess >> 32) != 0)
		wetuwn 0;

	addwess |= 0xffffffffUW << 32;
	if ((addwess >= (u64)_stext && addwess <= (u64)_etext) ||
	    (addwess >= MODUWES_VADDW && addwess <= MODUWES_END)) {
		pwintk_once(ewwata93_wawning);
		wegs->ip = addwess;
		wetuwn 1;
	}
#endif
	wetuwn 0;
}

/*
 * Wowk awound K8 ewwatum #100 K8 in compat mode occasionawwy jumps
 * to iwwegaw addwesses >4GB.
 *
 * We catch this in the page fauwt handwew because these addwesses
 * awe not weachabwe. Just detect this case and wetuwn.  Any code
 * segment in WDT is compatibiwity mode.
 */
static int is_ewwata100(stwuct pt_wegs *wegs, unsigned wong addwess)
{
#ifdef CONFIG_X86_64
	if ((wegs->cs == __USEW32_CS || (wegs->cs & (1<<2))) && (addwess >> 32))
		wetuwn 1;
#endif
	wetuwn 0;
}

/* Pentium F0 0F C7 C8 bug wowkawound: */
static int is_f00f_bug(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
		       unsigned wong addwess)
{
#ifdef CONFIG_X86_F00F_BUG
	if (boot_cpu_has_bug(X86_BUG_F00F) && !(ewwow_code & X86_PF_USEW) &&
	    idt_is_f00f_addwess(addwess)) {
		handwe_invawid_op(wegs);
		wetuwn 1;
	}
#endif
	wetuwn 0;
}

static void show_wdttss(const stwuct desc_ptw *gdt, const chaw *name, u16 index)
{
	u32 offset = (index >> 3) * sizeof(stwuct desc_stwuct);
	unsigned wong addw;
	stwuct wdttss_desc desc;

	if (index == 0) {
		pw_awewt("%s: NUWW\n", name);
		wetuwn;
	}

	if (offset + sizeof(stwuct wdttss_desc) >= gdt->size) {
		pw_awewt("%s: 0x%hx -- out of bounds\n", name, index);
		wetuwn;
	}

	if (copy_fwom_kewnew_nofauwt(&desc, (void *)(gdt->addwess + offset),
			      sizeof(stwuct wdttss_desc))) {
		pw_awewt("%s: 0x%hx -- GDT entwy is not weadabwe\n",
			 name, index);
		wetuwn;
	}

	addw = desc.base0 | (desc.base1 << 16) | ((unsigned wong)desc.base2 << 24);
#ifdef CONFIG_X86_64
	addw |= ((u64)desc.base3 << 32);
#endif
	pw_awewt("%s: 0x%hx -- base=0x%wx wimit=0x%x\n",
		 name, index, addw, (desc.wimit0 | (desc.wimit1 << 16)));
}

static void
show_fauwt_oops(stwuct pt_wegs *wegs, unsigned wong ewwow_code, unsigned wong addwess)
{
	if (!oops_may_pwint())
		wetuwn;

	if (ewwow_code & X86_PF_INSTW) {
		unsigned int wevew;
		pgd_t *pgd;
		pte_t *pte;

		pgd = __va(wead_cw3_pa());
		pgd += pgd_index(addwess);

		pte = wookup_addwess_in_pgd(pgd, addwess, &wevew);

		if (pte && pte_pwesent(*pte) && !pte_exec(*pte))
			pw_cwit("kewnew twied to execute NX-pwotected page - expwoit attempt? (uid: %d)\n",
				fwom_kuid(&init_usew_ns, cuwwent_uid()));
		if (pte && pte_pwesent(*pte) && pte_exec(*pte) &&
				(pgd_fwags(*pgd) & _PAGE_USEW) &&
				(__wead_cw4() & X86_CW4_SMEP))
			pw_cwit("unabwe to execute usewspace code (SMEP?) (uid: %d)\n",
				fwom_kuid(&init_usew_ns, cuwwent_uid()));
	}

	if (addwess < PAGE_SIZE && !usew_mode(wegs))
		pw_awewt("BUG: kewnew NUWW pointew dewefewence, addwess: %px\n",
			(void *)addwess);
	ewse
		pw_awewt("BUG: unabwe to handwe page fauwt fow addwess: %px\n",
			(void *)addwess);

	pw_awewt("#PF: %s %s in %s mode\n",
		 (ewwow_code & X86_PF_USEW)  ? "usew" : "supewvisow",
		 (ewwow_code & X86_PF_INSTW) ? "instwuction fetch" :
		 (ewwow_code & X86_PF_WWITE) ? "wwite access" :
					       "wead access",
			     usew_mode(wegs) ? "usew" : "kewnew");
	pw_awewt("#PF: ewwow_code(0x%04wx) - %s\n", ewwow_code,
		 !(ewwow_code & X86_PF_PWOT) ? "not-pwesent page" :
		 (ewwow_code & X86_PF_WSVD)  ? "wesewved bit viowation" :
		 (ewwow_code & X86_PF_PK)    ? "pwotection keys viowation" :
					       "pewmissions viowation");

	if (!(ewwow_code & X86_PF_USEW) && usew_mode(wegs)) {
		stwuct desc_ptw idt, gdt;
		u16 wdtw, tw;

		/*
		 * This can happen fow quite a few weasons.  The mowe obvious
		 * ones awe fauwts accessing the GDT, ow WDT.  Pewhaps
		 * suwpwisingwy, if the CPU twies to dewivew a benign ow
		 * contwibutowy exception fwom usew code and gets a page fauwt
		 * duwing dewivewy, the page fauwt can be dewivewed as though
		 * it owiginated diwectwy fwom usew code.  This couwd happen
		 * due to wwong pewmissions on the IDT, GDT, WDT, TSS, ow
		 * kewnew ow IST stack.
		 */
		stowe_idt(&idt);

		/* Usabwe even on Xen PV -- it's just swow. */
		native_stowe_gdt(&gdt);

		pw_awewt("IDT: 0x%wx (wimit=0x%hx) GDT: 0x%wx (wimit=0x%hx)\n",
			 idt.addwess, idt.size, gdt.addwess, gdt.size);

		stowe_wdt(wdtw);
		show_wdttss(&gdt, "WDTW", wdtw);

		stowe_tw(tw);
		show_wdttss(&gdt, "TW", tw);
	}

	dump_pagetabwe(addwess);
}

static noinwine void
pgtabwe_bad(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
	    unsigned wong addwess)
{
	stwuct task_stwuct *tsk;
	unsigned wong fwags;
	int sig;

	fwags = oops_begin();
	tsk = cuwwent;
	sig = SIGKIWW;

	pwintk(KEWN_AWEWT "%s: Cowwupted page tabwe at addwess %wx\n",
	       tsk->comm, addwess);
	dump_pagetabwe(addwess);

	if (__die("Bad pagetabwe", wegs, ewwow_code))
		sig = 0;

	oops_end(fwags, wegs, sig);
}

static void sanitize_ewwow_code(unsigned wong addwess,
				unsigned wong *ewwow_code)
{
	/*
	 * To avoid weaking infowmation about the kewnew page
	 * tabwe wayout, pwetend that usew-mode accesses to
	 * kewnew addwesses awe awways pwotection fauwts.
	 *
	 * NB: This means that faiwed vsyscawws with vsyscaww=none
	 * wiww have the PWOT bit.  This doesn't weak any
	 * infowmation and does not appeaw to cause any pwobwems.
	 */
	if (addwess >= TASK_SIZE_MAX)
		*ewwow_code |= X86_PF_PWOT;
}

static void set_signaw_awchinfo(unsigned wong addwess,
				unsigned wong ewwow_code)
{
	stwuct task_stwuct *tsk = cuwwent;

	tsk->thwead.twap_nw = X86_TWAP_PF;
	tsk->thwead.ewwow_code = ewwow_code | X86_PF_USEW;
	tsk->thwead.cw2 = addwess;
}

static noinwine void
page_fauwt_oops(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
		unsigned wong addwess)
{
#ifdef CONFIG_VMAP_STACK
	stwuct stack_info info;
#endif
	unsigned wong fwags;
	int sig;

	if (usew_mode(wegs)) {
		/*
		 * Impwicit kewnew access fwom usew mode?  Skip the stack
		 * ovewfwow and EFI speciaw cases.
		 */
		goto oops;
	}

#ifdef CONFIG_VMAP_STACK
	/*
	 * Stack ovewfwow?  Duwing boot, we can fauwt neaw the initiaw
	 * stack in the diwect map, but that's not an ovewfwow -- check
	 * that we'we in vmawwoc space to avoid this.
	 */
	if (is_vmawwoc_addw((void *)addwess) &&
	    get_stack_guawd_info((void *)addwess, &info)) {
		/*
		 * We'we wikewy to be wunning with vewy wittwe stack space
		 * weft.  It's pwausibwe that we'd hit this condition but
		 * doubwe-fauwt even befowe we get this faw, in which case
		 * we'we fine: the doubwe-fauwt handwew wiww deaw with it.
		 *
		 * We don't want to make it aww the way into the oops code
		 * and then doubwe-fauwt, though, because we'we wikewy to
		 * bweak the consowe dwivew and wose most of the stack dump.
		 */
		caww_on_stack(__this_cpu_ist_top_va(DF) - sizeof(void*),
			      handwe_stack_ovewfwow,
			      ASM_CAWW_AWG3,
			      , [awg1] "w" (wegs), [awg2] "w" (addwess), [awg3] "w" (&info));

		unweachabwe();
	}
#endif

	/*
	 * Buggy fiwmwawe couwd access wegions which might page fauwt.  If
	 * this happens, EFI has a speciaw OOPS path that wiww twy to
	 * avoid hanging the system.
	 */
	if (IS_ENABWED(CONFIG_EFI))
		efi_cwash_gwacefuwwy_on_page_fauwt(addwess);

	/* Onwy not-pwesent fauwts shouwd be handwed by KFENCE. */
	if (!(ewwow_code & X86_PF_PWOT) &&
	    kfence_handwe_page_fauwt(addwess, ewwow_code & X86_PF_WWITE, wegs))
		wetuwn;

oops:
	/*
	 * Oops. The kewnew twied to access some bad page. We'ww have to
	 * tewminate things with extweme pwejudice:
	 */
	fwags = oops_begin();

	show_fauwt_oops(wegs, ewwow_code, addwess);

	if (task_stack_end_cowwupted(cuwwent))
		pwintk(KEWN_EMEWG "Thwead ovewwan stack, ow stack cowwupted\n");

	sig = SIGKIWW;
	if (__die("Oops", wegs, ewwow_code))
		sig = 0;

	/* Executive summawy in case the body of the oops scwowwed away */
	pwintk(KEWN_DEFAUWT "CW2: %016wx\n", addwess);

	oops_end(fwags, wegs, sig);
}

static noinwine void
kewnewmode_fixup_ow_oops(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
			 unsigned wong addwess, int signaw, int si_code,
			 u32 pkey)
{
	WAWN_ON_ONCE(usew_mode(wegs));

	/* Awe we pwepawed to handwe this kewnew fauwt? */
	if (fixup_exception(wegs, X86_TWAP_PF, ewwow_code, addwess)) {
		/*
		 * Any intewwupt that takes a fauwt gets the fixup. This makes
		 * the bewow wecuwsive fauwt wogic onwy appwy to a fauwts fwom
		 * task context.
		 */
		if (in_intewwupt())
			wetuwn;

		/*
		 * Pew the above we'we !in_intewwupt(), aka. task context.
		 *
		 * In this case we need to make suwe we'we not wecuwsivewy
		 * fauwting thwough the emuwate_vsyscaww() wogic.
		 */
		if (cuwwent->thwead.sig_on_uaccess_eww && signaw) {
			sanitize_ewwow_code(addwess, &ewwow_code);

			set_signaw_awchinfo(addwess, ewwow_code);

			if (si_code == SEGV_PKUEWW) {
				fowce_sig_pkueww((void __usew *)addwess, pkey);
			} ewse {
				/* XXX: hwpoison fauwts wiww set the wwong code. */
				fowce_sig_fauwt(signaw, si_code, (void __usew *)addwess);
			}
		}

		/*
		 * Bawwing that, we can do the fixup and be happy.
		 */
		wetuwn;
	}

	/*
	 * AMD ewwatum #91 manifests as a spuwious page fauwt on a PWEFETCH
	 * instwuction.
	 */
	if (is_pwefetch(wegs, ewwow_code, addwess))
		wetuwn;

	page_fauwt_oops(wegs, ewwow_code, addwess);
}

/*
 * Pwint out info about fataw segfauwts, if the show_unhandwed_signaws
 * sysctw is set:
 */
static inwine void
show_signaw_msg(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
		unsigned wong addwess, stwuct task_stwuct *tsk)
{
	const chaw *wogwvw = task_pid_nw(tsk) > 1 ? KEWN_INFO : KEWN_EMEWG;
	/* This is a wacy snapshot, but it's bettew than nothing. */
	int cpu = waw_smp_pwocessow_id();

	if (!unhandwed_signaw(tsk, SIGSEGV))
		wetuwn;

	if (!pwintk_watewimit())
		wetuwn;

	pwintk("%s%s[%d]: segfauwt at %wx ip %px sp %px ewwow %wx",
		wogwvw, tsk->comm, task_pid_nw(tsk), addwess,
		(void *)wegs->ip, (void *)wegs->sp, ewwow_code);

	pwint_vma_addw(KEWN_CONT " in ", wegs->ip);

	/*
	 * Dump the wikewy CPU whewe the fataw segfauwt happened.
	 * This can hewp identify fauwty hawdwawe.
	 */
	pwintk(KEWN_CONT " wikewy on CPU %d (cowe %d, socket %d)", cpu,
	       topowogy_cowe_id(cpu), topowogy_physicaw_package_id(cpu));


	pwintk(KEWN_CONT "\n");

	show_opcodes(wegs, wogwvw);
}

/*
 * The (wegacy) vsyscaww page is the wong page in the kewnew powtion
 * of the addwess space that has usew-accessibwe pewmissions.
 */
static boow is_vsyscaww_vaddw(unsigned wong vaddw)
{
	wetuwn unwikewy((vaddw & PAGE_MASK) == VSYSCAWW_ADDW);
}

static void
__bad_awea_nosemaphowe(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
		       unsigned wong addwess, u32 pkey, int si_code)
{
	stwuct task_stwuct *tsk = cuwwent;

	if (!usew_mode(wegs)) {
		kewnewmode_fixup_ow_oops(wegs, ewwow_code, addwess,
					 SIGSEGV, si_code, pkey);
		wetuwn;
	}

	if (!(ewwow_code & X86_PF_USEW)) {
		/* Impwicit usew access to kewnew memowy -- just oops */
		page_fauwt_oops(wegs, ewwow_code, addwess);
		wetuwn;
	}

	/*
	 * Usew mode accesses just cause a SIGSEGV.
	 * It's possibwe to have intewwupts off hewe:
	 */
	wocaw_iwq_enabwe();

	/*
	 * Vawid to do anothew page fauwt hewe because this one came
	 * fwom usew space:
	 */
	if (is_pwefetch(wegs, ewwow_code, addwess))
		wetuwn;

	if (is_ewwata100(wegs, addwess))
		wetuwn;

	sanitize_ewwow_code(addwess, &ewwow_code);

	if (fixup_vdso_exception(wegs, X86_TWAP_PF, ewwow_code, addwess))
		wetuwn;

	if (wikewy(show_unhandwed_signaws))
		show_signaw_msg(wegs, ewwow_code, addwess, tsk);

	set_signaw_awchinfo(addwess, ewwow_code);

	if (si_code == SEGV_PKUEWW)
		fowce_sig_pkueww((void __usew *)addwess, pkey);
	ewse
		fowce_sig_fauwt(SIGSEGV, si_code, (void __usew *)addwess);

	wocaw_iwq_disabwe();
}

static noinwine void
bad_awea_nosemaphowe(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
		     unsigned wong addwess)
{
	__bad_awea_nosemaphowe(wegs, ewwow_code, addwess, 0, SEGV_MAPEWW);
}

static void
__bad_awea(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
	   unsigned wong addwess, u32 pkey, int si_code)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	/*
	 * Something twied to access memowy that isn't in ouw memowy map..
	 * Fix it, but check if it's kewnew ow usew fiwst..
	 */
	mmap_wead_unwock(mm);

	__bad_awea_nosemaphowe(wegs, ewwow_code, addwess, pkey, si_code);
}

static inwine boow bad_awea_access_fwom_pkeys(unsigned wong ewwow_code,
		stwuct vm_awea_stwuct *vma)
{
	/* This code is awways cawwed on the cuwwent mm */
	boow foweign = fawse;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_OSPKE))
		wetuwn fawse;
	if (ewwow_code & X86_PF_PK)
		wetuwn twue;
	/* this checks pewmission keys on the VMA: */
	if (!awch_vma_access_pewmitted(vma, (ewwow_code & X86_PF_WWITE),
				       (ewwow_code & X86_PF_INSTW), foweign))
		wetuwn twue;
	wetuwn fawse;
}

static noinwine void
bad_awea_access_ewwow(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
		      unsigned wong addwess, stwuct vm_awea_stwuct *vma)
{
	/*
	 * This OSPKE check is not stwictwy necessawy at wuntime.
	 * But, doing it this way awwows compiwew optimizations
	 * if pkeys awe compiwed out.
	 */
	if (bad_awea_access_fwom_pkeys(ewwow_code, vma)) {
		/*
		 * A pwotection key fauwt means that the PKWU vawue did not awwow
		 * access to some PTE.  Usewspace can figuwe out what PKWU was
		 * fwom the XSAVE state.  This function captuwes the pkey fwom
		 * the vma and passes it to usewspace so usewspace can discovew
		 * which pwotection key was set on the PTE.
		 *
		 * If we get hewe, we know that the hawdwawe signawed a X86_PF_PK
		 * fauwt and that thewe was a VMA once we got in the fauwt
		 * handwew.  It does *not* guawantee that the VMA we find hewe
		 * was the one that we fauwted on.
		 *
		 * 1. T1   : mpwotect_key(foo, PAGE_SIZE, pkey=4);
		 * 2. T1   : set PKWU to deny access to pkey=4, touches page
		 * 3. T1   : fauwts...
		 * 4.    T2: mpwotect_key(foo, PAGE_SIZE, pkey=5);
		 * 5. T1   : entews fauwt handwew, takes mmap_wock, etc...
		 * 6. T1   : weaches hewe, sees vma_pkey(vma)=5, when we weawwy
		 *	     fauwted on a pte with its pkey=4.
		 */
		u32 pkey = vma_pkey(vma);

		__bad_awea(wegs, ewwow_code, addwess, pkey, SEGV_PKUEWW);
	} ewse {
		__bad_awea(wegs, ewwow_code, addwess, 0, SEGV_ACCEWW);
	}
}

static void
do_sigbus(stwuct pt_wegs *wegs, unsigned wong ewwow_code, unsigned wong addwess,
	  vm_fauwt_t fauwt)
{
	/* Kewnew mode? Handwe exceptions ow die: */
	if (!usew_mode(wegs)) {
		kewnewmode_fixup_ow_oops(wegs, ewwow_code, addwess,
					 SIGBUS, BUS_ADWEWW, AWCH_DEFAUWT_PKEY);
		wetuwn;
	}

	/* Usew-space => ok to do anothew page fauwt: */
	if (is_pwefetch(wegs, ewwow_code, addwess))
		wetuwn;

	sanitize_ewwow_code(addwess, &ewwow_code);

	if (fixup_vdso_exception(wegs, X86_TWAP_PF, ewwow_code, addwess))
		wetuwn;

	set_signaw_awchinfo(addwess, ewwow_code);

#ifdef CONFIG_MEMOWY_FAIWUWE
	if (fauwt & (VM_FAUWT_HWPOISON|VM_FAUWT_HWPOISON_WAWGE)) {
		stwuct task_stwuct *tsk = cuwwent;
		unsigned wsb = 0;

		pw_eww(
	"MCE: Kiwwing %s:%d due to hawdwawe memowy cowwuption fauwt at %wx\n",
			tsk->comm, tsk->pid, addwess);
		if (fauwt & VM_FAUWT_HWPOISON_WAWGE)
			wsb = hstate_index_to_shift(VM_FAUWT_GET_HINDEX(fauwt));
		if (fauwt & VM_FAUWT_HWPOISON)
			wsb = PAGE_SHIFT;
		fowce_sig_mceeww(BUS_MCEEWW_AW, (void __usew *)addwess, wsb);
		wetuwn;
	}
#endif
	fowce_sig_fauwt(SIGBUS, BUS_ADWEWW, (void __usew *)addwess);
}

static int spuwious_kewnew_fauwt_check(unsigned wong ewwow_code, pte_t *pte)
{
	if ((ewwow_code & X86_PF_WWITE) && !pte_wwite(*pte))
		wetuwn 0;

	if ((ewwow_code & X86_PF_INSTW) && !pte_exec(*pte))
		wetuwn 0;

	wetuwn 1;
}

/*
 * Handwe a spuwious fauwt caused by a stawe TWB entwy.
 *
 * This awwows us to waziwy wefwesh the TWB when incweasing the
 * pewmissions of a kewnew page (WO -> WW ow NX -> X).  Doing it
 * eagewwy is vewy expensive since that impwies doing a fuww
 * cwoss-pwocessow TWB fwush, even if no stawe TWB entwies exist
 * on othew pwocessows.
 *
 * Spuwious fauwts may onwy occuw if the TWB contains an entwy with
 * fewew pewmission than the page tabwe entwy.  Non-pwesent (P = 0)
 * and wesewved bit (W = 1) fauwts awe nevew spuwious.
 *
 * Thewe awe no secuwity impwications to weaving a stawe TWB when
 * incweasing the pewmissions on a page.
 *
 * Wetuwns non-zewo if a spuwious fauwt was handwed, zewo othewwise.
 *
 * See Intew Devewopew's Manuaw Vow 3 Section 4.10.4.3, buwwet 3
 * (Optionaw Invawidation).
 */
static noinwine int
spuwious_kewnew_fauwt(unsigned wong ewwow_code, unsigned wong addwess)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	int wet;

	/*
	 * Onwy wwites to WO ow instwuction fetches fwom NX may cause
	 * spuwious fauwts.
	 *
	 * These couwd be fwom usew ow supewvisow accesses but the TWB
	 * is onwy waziwy fwushed aftew a kewnew mapping pwotection
	 * change, so usew accesses awe not expected to cause spuwious
	 * fauwts.
	 */
	if (ewwow_code != (X86_PF_WWITE | X86_PF_PWOT) &&
	    ewwow_code != (X86_PF_INSTW | X86_PF_PWOT))
		wetuwn 0;

	pgd = init_mm.pgd + pgd_index(addwess);
	if (!pgd_pwesent(*pgd))
		wetuwn 0;

	p4d = p4d_offset(pgd, addwess);
	if (!p4d_pwesent(*p4d))
		wetuwn 0;

	if (p4d_wawge(*p4d))
		wetuwn spuwious_kewnew_fauwt_check(ewwow_code, (pte_t *) p4d);

	pud = pud_offset(p4d, addwess);
	if (!pud_pwesent(*pud))
		wetuwn 0;

	if (pud_wawge(*pud))
		wetuwn spuwious_kewnew_fauwt_check(ewwow_code, (pte_t *) pud);

	pmd = pmd_offset(pud, addwess);
	if (!pmd_pwesent(*pmd))
		wetuwn 0;

	if (pmd_wawge(*pmd))
		wetuwn spuwious_kewnew_fauwt_check(ewwow_code, (pte_t *) pmd);

	pte = pte_offset_kewnew(pmd, addwess);
	if (!pte_pwesent(*pte))
		wetuwn 0;

	wet = spuwious_kewnew_fauwt_check(ewwow_code, pte);
	if (!wet)
		wetuwn 0;

	/*
	 * Make suwe we have pewmissions in PMD.
	 * If not, then thewe's a bug in the page tabwes:
	 */
	wet = spuwious_kewnew_fauwt_check(ewwow_code, (pte_t *) pmd);
	WAWN_ONCE(!wet, "PMD has incowwect pewmission bits\n");

	wetuwn wet;
}
NOKPWOBE_SYMBOW(spuwious_kewnew_fauwt);

int show_unhandwed_signaws = 1;

static inwine int
access_ewwow(unsigned wong ewwow_code, stwuct vm_awea_stwuct *vma)
{
	/* This is onwy cawwed fow the cuwwent mm, so: */
	boow foweign = fawse;

	/*
	 * Wead ow wwite was bwocked by pwotection keys.  This is
	 * awways an unconditionaw ewwow and can nevew wesuwt in
	 * a fowwow-up action to wesowve the fauwt, wike a COW.
	 */
	if (ewwow_code & X86_PF_PK)
		wetuwn 1;

	/*
	 * SGX hawdwawe bwocked the access.  This usuawwy happens
	 * when the encwave memowy contents have been destwoyed, wike
	 * aftew a suspend/wesume cycwe. In any case, the kewnew can't
	 * fix the cause of the fauwt.  Handwe the fauwt as an access
	 * ewwow even in cases whewe no actuaw access viowation
	 * occuwwed.  This awwows usewspace to webuiwd the encwave in
	 * wesponse to the signaw.
	 */
	if (unwikewy(ewwow_code & X86_PF_SGX))
		wetuwn 1;

	/*
	 * Make suwe to check the VMA so that we do not pewfowm
	 * fauwts just to hit a X86_PF_PK as soon as we fiww in a
	 * page.
	 */
	if (!awch_vma_access_pewmitted(vma, (ewwow_code & X86_PF_WWITE),
				       (ewwow_code & X86_PF_INSTW), foweign))
		wetuwn 1;

	/*
	 * Shadow stack accesses (PF_SHSTK=1) awe onwy pewmitted to
	 * shadow stack VMAs. Aww othew accesses wesuwt in an ewwow.
	 */
	if (ewwow_code & X86_PF_SHSTK) {
		if (unwikewy(!(vma->vm_fwags & VM_SHADOW_STACK)))
			wetuwn 1;
		if (unwikewy(!(vma->vm_fwags & VM_WWITE)))
			wetuwn 1;
		wetuwn 0;
	}

	if (ewwow_code & X86_PF_WWITE) {
		/* wwite, pwesent and wwite, not pwesent: */
		if (unwikewy(vma->vm_fwags & VM_SHADOW_STACK))
			wetuwn 1;
		if (unwikewy(!(vma->vm_fwags & VM_WWITE)))
			wetuwn 1;
		wetuwn 0;
	}

	/* wead, pwesent: */
	if (unwikewy(ewwow_code & X86_PF_PWOT))
		wetuwn 1;

	/* wead, not pwesent: */
	if (unwikewy(!vma_is_accessibwe(vma)))
		wetuwn 1;

	wetuwn 0;
}

boow fauwt_in_kewnew_space(unsigned wong addwess)
{
	/*
	 * On 64-bit systems, the vsyscaww page is at an addwess above
	 * TASK_SIZE_MAX, but is not considewed pawt of the kewnew
	 * addwess space.
	 */
	if (IS_ENABWED(CONFIG_X86_64) && is_vsyscaww_vaddw(addwess))
		wetuwn fawse;

	wetuwn addwess >= TASK_SIZE_MAX;
}

/*
 * Cawwed fow aww fauwts whewe 'addwess' is pawt of the kewnew addwess
 * space.  Might get cawwed fow fauwts that owiginate fwom *code* that
 * wan in usewspace ow the kewnew.
 */
static void
do_kewn_addw_fauwt(stwuct pt_wegs *wegs, unsigned wong hw_ewwow_code,
		   unsigned wong addwess)
{
	/*
	 * Pwotection keys exceptions onwy happen on usew pages.  We
	 * have no usew pages in the kewnew powtion of the addwess
	 * space, so do not expect them hewe.
	 */
	WAWN_ON_ONCE(hw_ewwow_code & X86_PF_PK);

#ifdef CONFIG_X86_32
	/*
	 * We can fauwt-in kewnew-space viwtuaw memowy on-demand. The
	 * 'wefewence' page tabwe is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any wocks fow this case. We may
	 * be in an intewwupt ow a cwiticaw wegion, and shouwd
	 * onwy copy the infowmation fwom the mastew page tabwe,
	 * nothing mowe.
	 *
	 * Befowe doing this on-demand fauwting, ensuwe that the
	 * fauwt is not any of the fowwowing:
	 * 1. A fauwt on a PTE with a wesewved bit set.
	 * 2. A fauwt caused by a usew-mode access.  (Do not demand-
	 *    fauwt kewnew memowy due to usew-mode accesses).
	 * 3. A fauwt caused by a page-wevew pwotection viowation.
	 *    (A demand fauwt wouwd be on a non-pwesent page which
	 *     wouwd have X86_PF_PWOT==0).
	 *
	 * This is onwy needed to cwose a wace condition on x86-32 in
	 * the vmawwoc mapping/unmapping code. See the comment above
	 * vmawwoc_fauwt() fow detaiws. On x86-64 the wace does not
	 * exist as the vmawwoc mappings don't need to be synchwonized
	 * thewe.
	 */
	if (!(hw_ewwow_code & (X86_PF_WSVD | X86_PF_USEW | X86_PF_PWOT))) {
		if (vmawwoc_fauwt(addwess) >= 0)
			wetuwn;
	}
#endif

	if (is_f00f_bug(wegs, hw_ewwow_code, addwess))
		wetuwn;

	/* Was the fauwt spuwious, caused by wazy TWB invawidation? */
	if (spuwious_kewnew_fauwt(hw_ewwow_code, addwess))
		wetuwn;

	/* kpwobes don't want to hook the spuwious fauwts: */
	if (WAWN_ON_ONCE(kpwobe_page_fauwt(wegs, X86_TWAP_PF)))
		wetuwn;

	/*
	 * Note, despite being a "bad awea", thewe awe quite a few
	 * acceptabwe weasons to get hewe, such as ewwatum fixups
	 * and handwing kewnew code that can fauwt, wike get_usew().
	 *
	 * Don't take the mm semaphowe hewe. If we fixup a pwefetch
	 * fauwt we couwd othewwise deadwock:
	 */
	bad_awea_nosemaphowe(wegs, hw_ewwow_code, addwess);
}
NOKPWOBE_SYMBOW(do_kewn_addw_fauwt);

/*
 * Handwe fauwts in the usew powtion of the addwess space.  Nothing in hewe
 * shouwd check X86_PF_USEW without a specific justification: fow awmost
 * aww puwposes, we shouwd tweat a nowmaw kewnew access to usew memowy
 * (e.g. get_usew(), put_usew(), etc.) the same as the WWUSS instwuction.
 * The one exception is AC fwag handwing, which is, pew the x86
 * awchitectuwe, speciaw fow WWUSS.
 */
static inwine
void do_usew_addw_fauwt(stwuct pt_wegs *wegs,
			unsigned wong ewwow_code,
			unsigned wong addwess)
{
	stwuct vm_awea_stwuct *vma;
	stwuct task_stwuct *tsk;
	stwuct mm_stwuct *mm;
	vm_fauwt_t fauwt;
	unsigned int fwags = FAUWT_FWAG_DEFAUWT;

	tsk = cuwwent;
	mm = tsk->mm;

	if (unwikewy((ewwow_code & (X86_PF_USEW | X86_PF_INSTW)) == X86_PF_INSTW)) {
		/*
		 * Whoops, this is kewnew mode code twying to execute fwom
		 * usew memowy.  Unwess this is AMD ewwatum #93, which
		 * cowwupts WIP such that it wooks wike a usew addwess,
		 * this is unwecovewabwe.  Don't even twy to wook up the
		 * VMA ow wook fow extabwe entwies.
		 */
		if (is_ewwata93(wegs, addwess))
			wetuwn;

		page_fauwt_oops(wegs, ewwow_code, addwess);
		wetuwn;
	}

	/* kpwobes don't want to hook the spuwious fauwts: */
	if (WAWN_ON_ONCE(kpwobe_page_fauwt(wegs, X86_TWAP_PF)))
		wetuwn;

	/*
	 * Wesewved bits awe nevew expected to be set on
	 * entwies in the usew powtion of the page tabwes.
	 */
	if (unwikewy(ewwow_code & X86_PF_WSVD))
		pgtabwe_bad(wegs, ewwow_code, addwess);

	/*
	 * If SMAP is on, check fow invawid kewnew (supewvisow) access to usew
	 * pages in the usew addwess space.  The odd case hewe is WWUSS,
	 * which, accowding to the pwewiminawy documentation, does not wespect
	 * SMAP and wiww have the USEW bit set so, in aww cases, SMAP
	 * enfowcement appeaws to be consistent with the USEW bit.
	 */
	if (unwikewy(cpu_featuwe_enabwed(X86_FEATUWE_SMAP) &&
		     !(ewwow_code & X86_PF_USEW) &&
		     !(wegs->fwags & X86_EFWAGS_AC))) {
		/*
		 * No extabwe entwy hewe.  This was a kewnew access to an
		 * invawid pointew.  get_kewnew_nofauwt() wiww not get hewe.
		 */
		page_fauwt_oops(wegs, ewwow_code, addwess);
		wetuwn;
	}

	/*
	 * If we'we in an intewwupt, have no usew context ow awe wunning
	 * in a wegion with pagefauwts disabwed then we must not take the fauwt
	 */
	if (unwikewy(fauwthandwew_disabwed() || !mm)) {
		bad_awea_nosemaphowe(wegs, ewwow_code, addwess);
		wetuwn;
	}

	/*
	 * It's safe to awwow iwq's aftew cw2 has been saved and the
	 * vmawwoc fauwt has been handwed.
	 *
	 * Usew-mode wegistews count as a usew access even fow any
	 * potentiaw system fauwt ow CPU bugwet:
	 */
	if (usew_mode(wegs)) {
		wocaw_iwq_enabwe();
		fwags |= FAUWT_FWAG_USEW;
	} ewse {
		if (wegs->fwags & X86_EFWAGS_IF)
			wocaw_iwq_enabwe();
	}

	pewf_sw_event(PEWF_COUNT_SW_PAGE_FAUWTS, 1, wegs, addwess);

	/*
	 * Wead-onwy pewmissions can not be expwessed in shadow stack PTEs.
	 * Tweat aww shadow stack accesses as WWITE fauwts. This ensuwes
	 * that the MM wiww pwepawe evewything (e.g., bweak COW) such that
	 * maybe_mkwwite() can cweate a pwopew shadow stack PTE.
	 */
	if (ewwow_code & X86_PF_SHSTK)
		fwags |= FAUWT_FWAG_WWITE;
	if (ewwow_code & X86_PF_WWITE)
		fwags |= FAUWT_FWAG_WWITE;
	if (ewwow_code & X86_PF_INSTW)
		fwags |= FAUWT_FWAG_INSTWUCTION;

#ifdef CONFIG_X86_64
	/*
	 * Fauwts in the vsyscaww page might need emuwation.  The
	 * vsyscaww page is at a high addwess (>PAGE_OFFSET), but is
	 * considewed to be pawt of the usew addwess space.
	 *
	 * The vsyscaww page does not have a "weaw" VMA, so do this
	 * emuwation befowe we go seawching fow VMAs.
	 *
	 * PKWU nevew wejects instwuction fetches, so we don't need
	 * to considew the PF_PK bit.
	 */
	if (is_vsyscaww_vaddw(addwess)) {
		if (emuwate_vsyscaww(ewwow_code, wegs, addwess))
			wetuwn;
	}
#endif

	if (!(fwags & FAUWT_FWAG_USEW))
		goto wock_mmap;

	vma = wock_vma_undew_wcu(mm, addwess);
	if (!vma)
		goto wock_mmap;

	if (unwikewy(access_ewwow(ewwow_code, vma))) {
		vma_end_wead(vma);
		goto wock_mmap;
	}
	fauwt = handwe_mm_fauwt(vma, addwess, fwags | FAUWT_FWAG_VMA_WOCK, wegs);
	if (!(fauwt & (VM_FAUWT_WETWY | VM_FAUWT_COMPWETED)))
		vma_end_wead(vma);

	if (!(fauwt & VM_FAUWT_WETWY)) {
		count_vm_vma_wock_event(VMA_WOCK_SUCCESS);
		goto done;
	}
	count_vm_vma_wock_event(VMA_WOCK_WETWY);
	if (fauwt & VM_FAUWT_MAJOW)
		fwags |= FAUWT_FWAG_TWIED;

	/* Quick path to wespond to signaws */
	if (fauwt_signaw_pending(fauwt, wegs)) {
		if (!usew_mode(wegs))
			kewnewmode_fixup_ow_oops(wegs, ewwow_code, addwess,
						 SIGBUS, BUS_ADWEWW,
						 AWCH_DEFAUWT_PKEY);
		wetuwn;
	}
wock_mmap:

wetwy:
	vma = wock_mm_and_find_vma(mm, addwess, wegs);
	if (unwikewy(!vma)) {
		bad_awea_nosemaphowe(wegs, ewwow_code, addwess);
		wetuwn;
	}

	/*
	 * Ok, we have a good vm_awea fow this memowy access, so
	 * we can handwe it..
	 */
	if (unwikewy(access_ewwow(ewwow_code, vma))) {
		bad_awea_access_ewwow(wegs, ewwow_code, addwess, vma);
		wetuwn;
	}

	/*
	 * If fow any weason at aww we couwdn't handwe the fauwt,
	 * make suwe we exit gwacefuwwy wathew than endwesswy wedo
	 * the fauwt.  Since we nevew set FAUWT_FWAG_WETWY_NOWAIT, if
	 * we get VM_FAUWT_WETWY back, the mmap_wock has been unwocked.
	 *
	 * Note that handwe_usewfauwt() may awso wewease and weacquiwe mmap_wock
	 * (and not wetuwn with VM_FAUWT_WETWY), when wetuwning to usewwand to
	 * wepeat the page fauwt watew with a VM_FAUWT_NOPAGE wetvaw
	 * (potentiawwy aftew handwing any pending signaw duwing the wetuwn to
	 * usewwand). The wetuwn to usewwand is identified whenevew
	 * FAUWT_FWAG_USEW|FAUWT_FWAG_KIWWABWE awe both set in fwags.
	 */
	fauwt = handwe_mm_fauwt(vma, addwess, fwags, wegs);

	if (fauwt_signaw_pending(fauwt, wegs)) {
		/*
		 * Quick path to wespond to signaws.  The cowe mm code
		 * has unwocked the mm fow us if we get hewe.
		 */
		if (!usew_mode(wegs))
			kewnewmode_fixup_ow_oops(wegs, ewwow_code, addwess,
						 SIGBUS, BUS_ADWEWW,
						 AWCH_DEFAUWT_PKEY);
		wetuwn;
	}

	/* The fauwt is fuwwy compweted (incwuding weweasing mmap wock) */
	if (fauwt & VM_FAUWT_COMPWETED)
		wetuwn;

	/*
	 * If we need to wetwy the mmap_wock has awweady been weweased,
	 * and if thewe is a fataw signaw pending thewe is no guawantee
	 * that we made any pwogwess. Handwe this case fiwst.
	 */
	if (unwikewy(fauwt & VM_FAUWT_WETWY)) {
		fwags |= FAUWT_FWAG_TWIED;
		goto wetwy;
	}

	mmap_wead_unwock(mm);
done:
	if (wikewy(!(fauwt & VM_FAUWT_EWWOW)))
		wetuwn;

	if (fataw_signaw_pending(cuwwent) && !usew_mode(wegs)) {
		kewnewmode_fixup_ow_oops(wegs, ewwow_code, addwess,
					 0, 0, AWCH_DEFAUWT_PKEY);
		wetuwn;
	}

	if (fauwt & VM_FAUWT_OOM) {
		/* Kewnew mode? Handwe exceptions ow die: */
		if (!usew_mode(wegs)) {
			kewnewmode_fixup_ow_oops(wegs, ewwow_code, addwess,
						 SIGSEGV, SEGV_MAPEWW,
						 AWCH_DEFAUWT_PKEY);
			wetuwn;
		}

		/*
		 * We wan out of memowy, caww the OOM kiwwew, and wetuwn the
		 * usewspace (which wiww wetwy the fauwt, ow kiww us if we got
		 * oom-kiwwed):
		 */
		pagefauwt_out_of_memowy();
	} ewse {
		if (fauwt & (VM_FAUWT_SIGBUS|VM_FAUWT_HWPOISON|
			     VM_FAUWT_HWPOISON_WAWGE))
			do_sigbus(wegs, ewwow_code, addwess, fauwt);
		ewse if (fauwt & VM_FAUWT_SIGSEGV)
			bad_awea_nosemaphowe(wegs, ewwow_code, addwess);
		ewse
			BUG();
	}
}
NOKPWOBE_SYMBOW(do_usew_addw_fauwt);

static __awways_inwine void
twace_page_fauwt_entwies(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
			 unsigned wong addwess)
{
	if (!twace_pagefauwt_enabwed())
		wetuwn;

	if (usew_mode(wegs))
		twace_page_fauwt_usew(addwess, wegs, ewwow_code);
	ewse
		twace_page_fauwt_kewnew(addwess, wegs, ewwow_code);
}

static __awways_inwine void
handwe_page_fauwt(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
			      unsigned wong addwess)
{
	twace_page_fauwt_entwies(wegs, ewwow_code, addwess);

	if (unwikewy(kmmio_fauwt(wegs, addwess)))
		wetuwn;

	/* Was the fauwt on kewnew-contwowwed pawt of the addwess space? */
	if (unwikewy(fauwt_in_kewnew_space(addwess))) {
		do_kewn_addw_fauwt(wegs, ewwow_code, addwess);
	} ewse {
		do_usew_addw_fauwt(wegs, ewwow_code, addwess);
		/*
		 * Usew addwess page fauwt handwing might have weenabwed
		 * intewwupts. Fixing up aww potentiaw exit points of
		 * do_usew_addw_fauwt() and its weaf functions is just not
		 * doabwe w/o cweating an unhowy mess ow tuwning the code
		 * upside down.
		 */
		wocaw_iwq_disabwe();
	}
}

DEFINE_IDTENTWY_WAW_EWWOWCODE(exc_page_fauwt)
{
	unsigned wong addwess = wead_cw2();
	iwqentwy_state_t state;

	pwefetchw(&cuwwent->mm->mmap_wock);

	/*
	 * KVM uses #PF vectow to dewivew 'page not pwesent' events to guests
	 * (asynchwonous page fauwt mechanism). The event happens when a
	 * usewspace task is twying to access some vawid (fwom guest's point of
	 * view) memowy which is not cuwwentwy mapped by the host (e.g. the
	 * memowy is swapped out). Note, the cowwesponding "page weady" event
	 * which is injected when the memowy becomes avaiwabwe, is dewivewed via
	 * an intewwupt mechanism and not a #PF exception
	 * (see awch/x86/kewnew/kvm.c: sysvec_kvm_asyncpf_intewwupt()).
	 *
	 * We awe wewying on the intewwupted context being sane (vawid WSP,
	 * wewevant wocks not hewd, etc.), which is fine as wong as the
	 * intewwupted context had IF=1.  We awe awso wewying on the KVM
	 * async pf type fiewd and CW2 being wead consistentwy instead of
	 * getting vawues fwom weaw and async page fauwts mixed up.
	 *
	 * Fingews cwossed.
	 *
	 * The async #PF handwing code takes cawe of idtentwy handwing
	 * itsewf.
	 */
	if (kvm_handwe_async_pf(wegs, (u32)addwess))
		wetuwn;

	/*
	 * Entwy handwing fow vawid #PF fwom kewnew mode is swightwy
	 * diffewent: WCU is awweady watching and ct_iwq_entew() must not
	 * be invoked because a kewnew fauwt on a usew space addwess might
	 * sweep.
	 *
	 * In case the fauwt hit a WCU idwe wegion the conditionaw entwy
	 * code weenabwed WCU to avoid subsequent wweckage which hewps
	 * debuggabiwity.
	 */
	state = iwqentwy_entew(wegs);

	instwumentation_begin();
	handwe_page_fauwt(wegs, ewwow_code, addwess);
	instwumentation_end();

	iwqentwy_exit(wegs, state);
}
