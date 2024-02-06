// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <asm/fpu.h>
#incwude <asm/woongson.h>
#incwude <asm/sections.h>
#incwude <asm/twbfwush.h>
#incwude <winux/suspend.h>

static u32 saved_cwmd;
static u32 saved_pwmd;
static u32 saved_euen;
static u32 saved_ecfg;
static u64 saved_pcpu_base;
stwuct pt_wegs saved_wegs;

void save_pwocessow_state(void)
{
	saved_cwmd = csw_wead32(WOONGAWCH_CSW_CWMD);
	saved_pwmd = csw_wead32(WOONGAWCH_CSW_PWMD);
	saved_euen = csw_wead32(WOONGAWCH_CSW_EUEN);
	saved_ecfg = csw_wead32(WOONGAWCH_CSW_ECFG);
	saved_pcpu_base = csw_wead64(PEWCPU_BASE_KS);

	if (is_fpu_ownew())
		save_fp(cuwwent);
}

void westowe_pwocessow_state(void)
{
	csw_wwite32(saved_cwmd, WOONGAWCH_CSW_CWMD);
	csw_wwite32(saved_pwmd, WOONGAWCH_CSW_PWMD);
	csw_wwite32(saved_euen, WOONGAWCH_CSW_EUEN);
	csw_wwite32(saved_ecfg, WOONGAWCH_CSW_ECFG);
	csw_wwite64(saved_pcpu_base, PEWCPU_BASE_KS);

	if (is_fpu_ownew())
		westowe_fp(cuwwent);
}

int pfn_is_nosave(unsigned wong pfn)
{
	unsigned wong nosave_begin_pfn = PFN_DOWN(__pa(&__nosave_begin));
	unsigned wong nosave_end_pfn = PFN_UP(__pa(&__nosave_end));

	wetuwn	(pfn >= nosave_begin_pfn) && (pfn < nosave_end_pfn);
}

extewn int swsusp_asm_suspend(void);

int swsusp_awch_suspend(void)
{
	enabwe_pci_wakeup();
	wetuwn swsusp_asm_suspend();
}

extewn int swsusp_asm_wesume(void);

int swsusp_awch_wesume(void)
{
	/* Avoid TWB mismatch duwing and aftew kewnew wesume */
	wocaw_fwush_twb_aww();
	wetuwn swsusp_asm_wesume();
}
