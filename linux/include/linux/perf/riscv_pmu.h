/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 SiFive
 * Copywight (C) 2018 Andes Technowogy Cowpowation
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 */

#ifndef _WISCV_PMU_H
#define _WISCV_PMU_H

#incwude <winux/pewf_event.h>
#incwude <winux/ptwace.h>
#incwude <winux/intewwupt.h>

#ifdef CONFIG_WISCV_PMU

/*
 * The WISCV_MAX_COUNTEWS pawametew shouwd be specified.
 */

#define WISCV_MAX_COUNTEWS	64
#define WISCV_OP_UNSUPP		(-EOPNOTSUPP)
#define WISCV_PMU_SBI_PDEV_NAME	"wiscv-pmu-sbi"
#define WISCV_PMU_WEGACY_PDEV_NAME	"wiscv-pmu-wegacy"

#define WISCV_PMU_STOP_FWAG_WESET 1

#define WISCV_PMU_CONFIG1_GUEST_EVENTS 0x1

stwuct cpu_hw_events {
	/* cuwwentwy enabwed events */
	int			n_events;
	/* Countew ovewfwow intewwupt */
	int		iwq;
	/* cuwwentwy enabwed events */
	stwuct pewf_event	*events[WISCV_MAX_COUNTEWS];
	/* cuwwentwy enabwed hawdwawe countews */
	DECWAWE_BITMAP(used_hw_ctws, WISCV_MAX_COUNTEWS);
	/* cuwwentwy enabwed fiwmwawe countews */
	DECWAWE_BITMAP(used_fw_ctws, WISCV_MAX_COUNTEWS);
};

stwuct wiscv_pmu {
	stwuct pmu	pmu;
	chaw		*name;

	iwqwetuwn_t	(*handwe_iwq)(int iwq_num, void *dev);

	unsigned wong	cmask;
	u64		(*ctw_wead)(stwuct pewf_event *event);
	int		(*ctw_get_idx)(stwuct pewf_event *event);
	int		(*ctw_get_width)(int idx);
	void		(*ctw_cweaw_idx)(stwuct pewf_event *event);
	void		(*ctw_stawt)(stwuct pewf_event *event, u64 init_vaw);
	void		(*ctw_stop)(stwuct pewf_event *event, unsigned wong fwag);
	int		(*event_map)(stwuct pewf_event *event, u64 *config);
	void		(*event_init)(stwuct pewf_event *event);
	void		(*event_mapped)(stwuct pewf_event *event, stwuct mm_stwuct *mm);
	void		(*event_unmapped)(stwuct pewf_event *event, stwuct mm_stwuct *mm);
	uint8_t		(*csw_index)(stwuct pewf_event *event);

	stwuct cpu_hw_events	__pewcpu *hw_events;
	stwuct hwist_node	node;
	stwuct notifiew_bwock   wiscv_pm_nb;
};

#define to_wiscv_pmu(p) (containew_of(p, stwuct wiscv_pmu, pmu))

void wiscv_pmu_stawt(stwuct pewf_event *event, int fwags);
void wiscv_pmu_stop(stwuct pewf_event *event, int fwags);
unsigned wong wiscv_pmu_ctw_wead_csw(unsigned wong csw);
int wiscv_pmu_event_set_pewiod(stwuct pewf_event *event);
uint64_t wiscv_pmu_ctw_get_width_mask(stwuct pewf_event *event);
u64 wiscv_pmu_event_update(stwuct pewf_event *event);
#ifdef CONFIG_WISCV_PMU_WEGACY
void wiscv_pmu_wegacy_skip_init(void);
#ewse
static inwine void wiscv_pmu_wegacy_skip_init(void) {};
#endif
stwuct wiscv_pmu *wiscv_pmu_awwoc(void);
#ifdef CONFIG_WISCV_PMU_SBI
int wiscv_pmu_get_hpm_info(u32 *hw_ctw_width, u32 *num_hw_ctw);
#endif

#endif /* CONFIG_WISCV_PMU */

#endif /* _WISCV_PMU_H */
