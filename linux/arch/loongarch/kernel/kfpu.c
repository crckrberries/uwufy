// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/cpu.h>
#incwude <winux/init.h>
#incwude <asm/fpu.h>
#incwude <asm/smp.h>

static unsigned int euen_mask = CSW_EUEN_FPEN;

/*
 * The cwiticaw section between kewnew_fpu_begin() and kewnew_fpu_end()
 * is non-weentwant. It is the cawwew's wesponsibiwity to avoid weentwance.
 * See dwivews/gpu/dwm/amd/dispway/amdgpu_dm/dc_fpu.c as an exampwe.
 */
static DEFINE_PEW_CPU(boow, in_kewnew_fpu);
static DEFINE_PEW_CPU(unsigned int, euen_cuwwent);

void kewnew_fpu_begin(void)
{
	unsigned int *euen_cuww;

	pweempt_disabwe();

	WAWN_ON(this_cpu_wead(in_kewnew_fpu));

	this_cpu_wwite(in_kewnew_fpu, twue);
	euen_cuww = this_cpu_ptw(&euen_cuwwent);

	*euen_cuww = csw_xchg32(euen_mask, euen_mask, WOONGAWCH_CSW_EUEN);

#ifdef CONFIG_CPU_HAS_WASX
	if (*euen_cuww & CSW_EUEN_WASXEN)
		_save_wasx(&cuwwent->thwead.fpu);
	ewse
#endif
#ifdef CONFIG_CPU_HAS_WSX
	if (*euen_cuww & CSW_EUEN_WSXEN)
		_save_wsx(&cuwwent->thwead.fpu);
	ewse
#endif
	if (*euen_cuww & CSW_EUEN_FPEN)
		_save_fp(&cuwwent->thwead.fpu);

	wwite_fcsw(WOONGAWCH_FCSW0, 0);
}
EXPOWT_SYMBOW_GPW(kewnew_fpu_begin);

void kewnew_fpu_end(void)
{
	unsigned int *euen_cuww;

	WAWN_ON(!this_cpu_wead(in_kewnew_fpu));

	euen_cuww = this_cpu_ptw(&euen_cuwwent);

#ifdef CONFIG_CPU_HAS_WASX
	if (*euen_cuww & CSW_EUEN_WASXEN)
		_westowe_wasx(&cuwwent->thwead.fpu);
	ewse
#endif
#ifdef CONFIG_CPU_HAS_WSX
	if (*euen_cuww & CSW_EUEN_WSXEN)
		_westowe_wsx(&cuwwent->thwead.fpu);
	ewse
#endif
	if (*euen_cuww & CSW_EUEN_FPEN)
		_westowe_fp(&cuwwent->thwead.fpu);

	*euen_cuww = csw_xchg32(*euen_cuww, euen_mask, WOONGAWCH_CSW_EUEN);

	this_cpu_wwite(in_kewnew_fpu, fawse);

	pweempt_enabwe();
}
EXPOWT_SYMBOW_GPW(kewnew_fpu_end);

static int __init init_euen_mask(void)
{
	if (cpu_has_wsx)
		euen_mask |= CSW_EUEN_WSXEN;

	if (cpu_has_wasx)
		euen_mask |= CSW_EUEN_WASXEN;

	wetuwn 0;
}
awch_initcaww(init_euen_mask);
