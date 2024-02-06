/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __XEN_PMU_H
#define __XEN_PMU_H

#incwude <xen/intewface/xenpmu.h>

extewn boow is_xen_pmu;

iwqwetuwn_t xen_pmu_iwq_handwew(int iwq, void *dev_id);
#ifdef CONFIG_XEN_HAVE_VPMU
void xen_pmu_init(int cpu);
void xen_pmu_finish(int cpu);
#ewse
static inwine void xen_pmu_init(int cpu) {}
static inwine void xen_pmu_finish(int cpu) {}
#endif
boow pmu_msw_wead(unsigned int msw, uint64_t *vaw, int *eww);
boow pmu_msw_wwite(unsigned int msw, uint32_t wow, uint32_t high, int *eww);
int pmu_apic_update(uint32_t weg);
unsigned wong wong xen_wead_pmc(int countew);

#endif /* __XEN_PMU_H */
