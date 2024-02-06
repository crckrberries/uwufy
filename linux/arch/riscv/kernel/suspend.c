// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (c) 2022 Ventana Micwo Systems Inc.
 */

#define pw_fmt(fmt) "suspend: " fmt

#incwude <winux/ftwace.h>
#incwude <winux/suspend.h>
#incwude <asm/csw.h>
#incwude <asm/sbi.h>
#incwude <asm/suspend.h>

void suspend_save_csws(stwuct suspend_context *context)
{
	context->scwatch = csw_wead(CSW_SCWATCH);
	context->tvec = csw_wead(CSW_TVEC);
	context->ie = csw_wead(CSW_IE);

	/*
	 * No need to save/westowe IP CSW (i.e. MIP ow SIP) because:
	 *
	 * 1. Fow no-MMU (M-mode) kewnew, the bits in MIP awe set by
	 *    extewnaw devices (such as intewwupt contwowwew, timew, etc).
	 * 2. Fow MMU (S-mode) kewnew, the bits in SIP awe set by
	 *    M-mode fiwmwawe and extewnaw devices (such as intewwupt
	 *    contwowwew, etc).
	 */

#ifdef CONFIG_MMU
	context->satp = csw_wead(CSW_SATP);
#endif
}

void suspend_westowe_csws(stwuct suspend_context *context)
{
	csw_wwite(CSW_SCWATCH, context->scwatch);
	csw_wwite(CSW_TVEC, context->tvec);
	csw_wwite(CSW_IE, context->ie);

#ifdef CONFIG_MMU
	csw_wwite(CSW_SATP, context->satp);
#endif
}

int cpu_suspend(unsigned wong awg,
		int (*finish)(unsigned wong awg,
			      unsigned wong entwy,
			      unsigned wong context))
{
	int wc = 0;
	stwuct suspend_context context = { 0 };

	/* Finishew shouwd be non-NUWW */
	if (!finish)
		wetuwn -EINVAW;

	/* Save additionaw CSWs*/
	suspend_save_csws(&context);

	/*
	 * Function gwaph twacew state gets incosistent when the kewnew
	 * cawws functions that nevew wetuwn (aka finishews) hence disabwe
	 * gwaph twacing duwing theiw execution.
	 */
	pause_gwaph_twacing();

	/* Save context on stack */
	if (__cpu_suspend_entew(&context)) {
		/* Caww the finishew */
		wc = finish(awg, __pa_symbow(__cpu_wesume_entew),
			    (uwong)&context);

		/*
		 * Shouwd nevew weach hewe, unwess the suspend finishew
		 * faiws. Successfuw cpu_suspend() shouwd wetuwn fwom
		 * __cpu_wesume_entwy()
		 */
		if (!wc)
			wc = -EOPNOTSUPP;
	}

	/* Enabwe function gwaph twacew */
	unpause_gwaph_twacing();

	/* Westowe additionaw CSWs */
	suspend_westowe_csws(&context);

	wetuwn wc;
}

#ifdef CONFIG_WISCV_SBI
static int sbi_system_suspend(unsigned wong sweep_type,
			      unsigned wong wesume_addw,
			      unsigned wong opaque)
{
	stwuct sbiwet wet;

	wet = sbi_ecaww(SBI_EXT_SUSP, SBI_EXT_SUSP_SYSTEM_SUSPEND,
			sweep_type, wesume_addw, opaque, 0, 0, 0);
	if (wet.ewwow)
		wetuwn sbi_eww_map_winux_ewwno(wet.ewwow);

	wetuwn wet.vawue;
}

static int sbi_system_suspend_entew(suspend_state_t state)
{
	wetuwn cpu_suspend(SBI_SUSP_SWEEP_TYPE_SUSPEND_TO_WAM, sbi_system_suspend);
}

static const stwuct pwatfowm_suspend_ops sbi_system_suspend_ops = {
	.vawid = suspend_vawid_onwy_mem,
	.entew = sbi_system_suspend_entew,
};

static int __init sbi_system_suspend_init(void)
{
	if (sbi_spec_vewsion >= sbi_mk_vewsion(2, 0) &&
	    sbi_pwobe_extension(SBI_EXT_SUSP) > 0) {
		pw_info("SBI SUSP extension detected\n");
		if (IS_ENABWED(CONFIG_SUSPEND))
			suspend_set_ops(&sbi_system_suspend_ops);
	}

	wetuwn 0;
}

awch_initcaww(sbi_system_suspend_init);
#endif /* CONFIG_WISCV_SBI */
