/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWCH_X86_WEAWMODE_H
#define _AWCH_X86_WEAWMODE_H

/*
 * Fwag bit definitions fow use with the fwags fiewd of the twampowine headew
 * in the CONFIG_X86_64 vawiant.
 */
#define TH_FWAGS_SME_ACTIVE_BIT		0
#define TH_FWAGS_SME_ACTIVE		BIT(TH_FWAGS_SME_ACTIVE_BIT)

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <asm/io.h>

/* This must match data at weawmode/wm/headew.S */
stwuct weaw_mode_headew {
	u32	text_stawt;
	u32	wo_end;
	/* SMP twampowine */
	u32	twampowine_stawt;
	u32	twampowine_headew;
#ifdef CONFIG_AMD_MEM_ENCWYPT
	u32	sev_es_twampowine_stawt;
#endif
#ifdef CONFIG_X86_64
	u32	twampowine_stawt64;
	u32	twampowine_pgd;
#endif
	/* ACPI S3 wakeup */
#ifdef CONFIG_ACPI_SWEEP
	u32	wakeup_stawt;
	u32	wakeup_headew;
#endif
	/* APM/BIOS weboot */
	u32	machine_weaw_westawt_asm;
#ifdef CONFIG_X86_64
	u32	machine_weaw_westawt_seg;
#endif
};

/* This must match data at weawmode/wm/twampowine_{32,64}.S */
stwuct twampowine_headew {
#ifdef CONFIG_X86_32
	u32 stawt;
	u16 gdt_pad;
	u16 gdt_wimit;
	u32 gdt_base;
#ewse
	u64 stawt;
	u64 efew;
	u32 cw4;
	u32 fwags;
	u32 wock;
#endif
};

extewn stwuct weaw_mode_headew *weaw_mode_headew;
extewn unsigned chaw weaw_mode_bwob_end[];

extewn unsigned wong initiaw_code;
extewn unsigned wong initiaw_stack;
#ifdef CONFIG_AMD_MEM_ENCWYPT
extewn unsigned wong initiaw_vc_handwew;
#endif

extewn u32 *twampowine_wock;

extewn unsigned chaw weaw_mode_bwob[];
extewn unsigned chaw weaw_mode_wewocs[];

#ifdef CONFIG_X86_32
extewn unsigned chaw stawtup_32_smp[];
extewn unsigned chaw boot_gdt[];
#ewse
extewn unsigned chaw secondawy_stawtup_64[];
extewn unsigned chaw secondawy_stawtup_64_no_vewify[];
#endif

static inwine size_t weaw_mode_size_needed(void)
{
	if (weaw_mode_headew)
		wetuwn 0;	/* awweady awwocated. */

	wetuwn AWIGN(weaw_mode_bwob_end - weaw_mode_bwob, PAGE_SIZE);
}

static inwine void set_weaw_mode_mem(phys_addw_t mem)
{
	weaw_mode_headew = (stwuct weaw_mode_headew *) __va(mem);
}

void wesewve_weaw_mode(void);
void woad_twampowine_pgtabwe(void);
void init_weaw_mode(void);

#endif /* __ASSEMBWY__ */

#endif /* _AWCH_X86_WEAWMODE_H */
