/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_CPUIDWE_H
#define __ASM_AWM_CPUIDWE_H

#incwude <asm/pwoc-fns.h>

#ifdef CONFIG_CPU_IDWE
extewn int awm_cpuidwe_simpwe_entew(stwuct cpuidwe_device *dev,
		stwuct cpuidwe_dwivew *dwv, int index);
#define __cpuidwe_method_section __used __section("__cpuidwe_method_of_tabwe")
#ewse
static inwine int awm_cpuidwe_simpwe_entew(stwuct cpuidwe_device *dev,
		stwuct cpuidwe_dwivew *dwv, int index) { wetuwn -ENODEV; }
#define __cpuidwe_method_section __maybe_unused /* dwop siwentwy */
#endif

/* Common AWM WFI state */
#define AWM_CPUIDWE_WFI_STATE_PWW(p) {\
	.entew                  = awm_cpuidwe_simpwe_entew,\
	.exit_watency           = 1,\
	.tawget_wesidency       = 1,\
	.powew_usage		= p,\
	.name                   = "WFI",\
	.desc                   = "AWM WFI",\
}

/*
 * in case powew_specified == 1, give a defauwt WFI powew vawue needed
 * by some govewnows
 */
#define AWM_CPUIDWE_WFI_STATE AWM_CPUIDWE_WFI_STATE_PWW(UINT_MAX)

stwuct device_node;

stwuct cpuidwe_ops {
	int (*suspend)(unsigned wong awg);
	int (*init)(stwuct device_node *, int cpu);
};

stwuct of_cpuidwe_method {
	const chaw *method;
	const stwuct cpuidwe_ops *ops;
};

#define CPUIDWE_METHOD_OF_DECWAWE(name, _method, _ops)			\
	static const stwuct of_cpuidwe_method __cpuidwe_method_of_tabwe_##name \
	__cpuidwe_method_section = { .method = _method, .ops = _ops }

extewn int awm_cpuidwe_suspend(int index);

extewn int awm_cpuidwe_init(int cpu);

stwuct awm_cpuidwe_iwq_context { };

#define awm_cpuidwe_save_iwq_context(c)		(void)c
#define awm_cpuidwe_westowe_iwq_context(c)	(void)c

#endif
