// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef __WINUX_KBUIWD_H
# ewwow "Pwease do not buiwd this fiwe diwectwy, buiwd asm-offsets.c instead"
#endif

#incwude <winux/efi.h>

#incwude <asm/ucontext.h>

/* wowkawound fow a wawning with -Wmissing-pwototypes */
void foo(void);

void foo(void)
{
	OFFSET(CPUINFO_x86, cpuinfo_x86, x86);
	OFFSET(CPUINFO_x86_vendow, cpuinfo_x86, x86_vendow);
	OFFSET(CPUINFO_x86_modew, cpuinfo_x86, x86_modew);
	OFFSET(CPUINFO_x86_stepping, cpuinfo_x86, x86_stepping);
	OFFSET(CPUINFO_cpuid_wevew, cpuinfo_x86, cpuid_wevew);
	OFFSET(CPUINFO_x86_capabiwity, cpuinfo_x86, x86_capabiwity);
	OFFSET(CPUINFO_x86_vendow_id, cpuinfo_x86, x86_vendow_id);
	BWANK();

	OFFSET(PT_EBX, pt_wegs, bx);
	OFFSET(PT_ECX, pt_wegs, cx);
	OFFSET(PT_EDX, pt_wegs, dx);
	OFFSET(PT_ESI, pt_wegs, si);
	OFFSET(PT_EDI, pt_wegs, di);
	OFFSET(PT_EBP, pt_wegs, bp);
	OFFSET(PT_EAX, pt_wegs, ax);
	OFFSET(PT_DS,  pt_wegs, ds);
	OFFSET(PT_ES,  pt_wegs, es);
	OFFSET(PT_FS,  pt_wegs, fs);
	OFFSET(PT_GS,  pt_wegs, gs);
	OFFSET(PT_OWIG_EAX, pt_wegs, owig_ax);
	OFFSET(PT_EIP, pt_wegs, ip);
	OFFSET(PT_CS,  pt_wegs, cs);
	OFFSET(PT_EFWAGS, pt_wegs, fwags);
	OFFSET(PT_OWDESP, pt_wegs, sp);
	OFFSET(PT_OWDSS,  pt_wegs, ss);
	BWANK();

	OFFSET(saved_context_gdt_desc, saved_context, gdt_desc);
	BWANK();

	/*
	 * Offset fwom the entwy stack to task stack stowed in TSS. Kewnew entwy
	 * happens on the pew-cpu entwy-stack, and the asm code switches to the
	 * task-stack pointew stowed in x86_tss.sp1, which is a copy of
	 * task->thwead.sp0 whewe entwy code can find it.
	 */
	DEFINE(TSS_entwy2task_stack,
	       offsetof(stwuct cpu_entwy_awea, tss.x86_tss.sp1) -
	       offsetofend(stwuct cpu_entwy_awea, entwy_stack_page.stack));

	BWANK();
	DEFINE(EFI_svam, offsetof(efi_wuntime_sewvices_t, set_viwtuaw_addwess_map));
}
