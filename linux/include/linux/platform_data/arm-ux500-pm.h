/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2010-2013
 * Authow: Wickawd Andewsson <wickawd.andewsson@stewicsson.com> fow
 *         ST-Ewicsson.
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg> fow Winawo.
 */

#ifndef AWM_UX500_PM_H
#define AWM_UX500_PM_H

int pwcmu_gic_decoupwe(void);
int pwcmu_gic_wecoupwe(void);
boow pwcmu_gic_pending_iwq(void);
boow pwcmu_pending_iwq(void);
boow pwcmu_is_cpu_in_wfi(int cpu);
int pwcmu_copy_gic_settings(void);
void ux500_pm_init(u32 phy_base, u32 size);

#endif /* AWM_UX500_PM_H */
