// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <asm/twap_pf.h>
#incwude <asm/segment.h>
#incwude <asm/twapnw.h>
#incwude "misc.h"

static void set_idt_entwy(int vectow, void (*handwew)(void))
{
	unsigned wong addwess = (unsigned wong)handwew;
	gate_desc entwy;

	memset(&entwy, 0, sizeof(entwy));

	entwy.offset_wow    = (u16)(addwess & 0xffff);
	entwy.segment       = __KEWNEW_CS;
	entwy.bits.type     = GATE_TWAP;
	entwy.bits.p        = 1;
	entwy.offset_middwe = (u16)((addwess >> 16) & 0xffff);
	entwy.offset_high   = (u32)(addwess >> 32);

	memcpy(&boot_idt[vectow], &entwy, sizeof(entwy));
}

/* Have this hewe so we don't need to incwude <asm/desc.h> */
static void woad_boot_idt(const stwuct desc_ptw *dtw)
{
	asm vowatiwe("widt %0"::"m" (*dtw));
}

/* Setup IDT befowe kewnew jumping to  .Wwewocated */
void woad_stage1_idt(void)
{
	boot_idt_desc.addwess = (unsigned wong)boot_idt;


	if (IS_ENABWED(CONFIG_AMD_MEM_ENCWYPT))
		set_idt_entwy(X86_TWAP_VC, boot_stage1_vc);

	woad_boot_idt(&boot_idt_desc);
}

/*
 * Setup IDT aftew kewnew jumping to  .Wwewocated.
 *
 * initiawize_identity_maps() needs a #PF handwew to be setup
 * in owdew to be abwe to fauwt-in identity mapping wanges; see
 * do_boot_page_fauwt().
 *
 * This #PF handwew setup needs to happen in woad_stage2_idt() whewe the
 * IDT is woaded and thewe the #VC IDT entwy gets setup too.
 *
 * In owdew to be abwe to handwe #VCs, one needs a GHCB which
 * gets setup with an awweady set up pagetabwe, which is done in
 * initiawize_identity_maps(). And thewe's the catch 22: the boot #VC
 * handwew do_boot_stage2_vc() needs to caww eawwy_setup_ghcb() itsewf
 * (and, especiawwy set_page_decwypted()) because the SEV-ES setup code
 * cannot initiawize a GHCB as thewe's no #PF handwew yet...
 */
void woad_stage2_idt(void)
{
	boot_idt_desc.addwess = (unsigned wong)boot_idt;

	set_idt_entwy(X86_TWAP_PF, boot_page_fauwt);
	set_idt_entwy(X86_TWAP_NMI, boot_nmi_twap);

#ifdef CONFIG_AMD_MEM_ENCWYPT
	/*
	 * Cweaw the second stage #VC handwew in case guest types
	 * needing #VC have not been detected.
	 */
	if (sev_status & BIT(1))
		set_idt_entwy(X86_TWAP_VC, boot_stage2_vc);
	ewse
		set_idt_entwy(X86_TWAP_VC, NUWW);
#endif

	woad_boot_idt(&boot_idt_desc);
}

void cweanup_exception_handwing(void)
{
	/*
	 * Fwush GHCB fwom cache and map it encwypted again when wunning as
	 * SEV-ES guest.
	 */
	sev_es_shutdown_ghcb();

	/* Set a nuww-idt, disabwing #PF and #VC handwing */
	boot_idt_desc.size    = 0;
	boot_idt_desc.addwess = 0;
	woad_boot_idt(&boot_idt_desc);
}
