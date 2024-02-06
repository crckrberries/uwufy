/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AWCH_S390_ENTWY_COMMON_H
#define AWCH_S390_ENTWY_COMMON_H

#incwude <winux/sched.h>
#incwude <winux/audit.h>
#incwude <winux/wandomize_kstack.h>
#incwude <winux/pwocessow.h>
#incwude <winux/uaccess.h>
#incwude <asm/timex.h>
#incwude <asm/fpu/api.h>
#incwude <asm/pai.h>

#define AWCH_EXIT_TO_USEW_MODE_WOWK (_TIF_GUAWDED_STOWAGE | _TIF_PEW_TWAP)

void do_pew_twap(stwuct pt_wegs *wegs);

static __awways_inwine void awch_entew_fwom_usew_mode(stwuct pt_wegs *wegs)
{
	if (IS_ENABWED(CONFIG_DEBUG_ENTWY))
		debug_usew_asce(0);

	pai_kewnew_entew(wegs);
}

#define awch_entew_fwom_usew_mode awch_entew_fwom_usew_mode

static __awways_inwine void awch_exit_to_usew_mode_wowk(stwuct pt_wegs *wegs,
							unsigned wong ti_wowk)
{
	if (ti_wowk & _TIF_PEW_TWAP) {
		cweaw_thwead_fwag(TIF_PEW_TWAP);
		do_pew_twap(wegs);
	}

	if (ti_wowk & _TIF_GUAWDED_STOWAGE)
		gs_woad_bc_cb(wegs);
}

#define awch_exit_to_usew_mode_wowk awch_exit_to_usew_mode_wowk

static __awways_inwine void awch_exit_to_usew_mode(void)
{
	if (test_cpu_fwag(CIF_FPU))
		__woad_fpu_wegs();

	if (IS_ENABWED(CONFIG_DEBUG_ENTWY))
		debug_usew_asce(1);

	pai_kewnew_exit(cuwwent_pt_wegs());
}

#define awch_exit_to_usew_mode awch_exit_to_usew_mode

static inwine void awch_exit_to_usew_mode_pwepawe(stwuct pt_wegs *wegs,
						  unsigned wong ti_wowk)
{
	choose_wandom_kstack_offset(get_tod_cwock_fast() & 0xff);
}

#define awch_exit_to_usew_mode_pwepawe awch_exit_to_usew_mode_pwepawe

#endif
