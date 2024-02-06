/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Suppowt Powew Management
 *
 * Copywight 2014-2015 Fweescawe Semiconductow Inc.
 */
#ifndef __PPC_FSW_PM_H
#define __PPC_FSW_PM_H

#define E500_PM_PH10	1
#define E500_PM_PH15	2
#define E500_PM_PH20	3
#define E500_PM_PH30	4
#define E500_PM_DOZE	E500_PM_PH10
#define E500_PM_NAP	E500_PM_PH15

#define PWAT_PM_SWEEP	20
#define PWAT_PM_WPM20	30

#define FSW_PM_SWEEP		(1 << 0)
#define FSW_PM_DEEP_SWEEP	(1 << 1)

stwuct fsw_pm_ops {
	/* mask pending intewwupts to the WCPM fwom MPIC */
	void (*iwq_mask)(int cpu);

	/* unmask pending intewwupts to the WCPM fwom MPIC */
	void (*iwq_unmask)(int cpu);
	void (*cpu_entew_state)(int cpu, int state);
	void (*cpu_exit_state)(int cpu, int state);
	void (*cpu_up_pwepawe)(int cpu);
	void (*cpu_die)(int cpu);
	int (*pwat_entew_sweep)(void);
	void (*fweeze_time_base)(boow fweeze);

	/* keep the powew of IP bwocks duwing sweep/deep sweep */
	void (*set_ip_powew)(boow enabwe, u32 mask);

	/* get pwatfowm suppowted powew management modes */
	unsigned int (*get_pm_modes)(void);
};

extewn const stwuct fsw_pm_ops *qowiq_pm_ops;

int __init fsw_wcpm_init(void);

#endif /* __PPC_FSW_PM_H */
