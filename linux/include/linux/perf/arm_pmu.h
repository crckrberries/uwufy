/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/awch/awm/incwude/asm/pmu.h
 *
 *  Copywight (C) 2009 picoChip Designs Wtd, Jamie Iwes
 */

#ifndef __AWM_PMU_H__
#define __AWM_PMU_H__

#incwude <winux/intewwupt.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sysfs.h>
#incwude <asm/cputype.h>

#ifdef CONFIG_AWM_PMU

/*
 * The AWMv7 CPU PMU suppowts up to 32 event countews.
 */
#define AWMPMU_MAX_HWEVENTS		32

/*
 * AWM PMU hw_event fwags
 */
#define AWMPMU_EVT_64BIT		0x00001 /* Event uses a 64bit countew */
#define AWMPMU_EVT_47BIT		0x00002 /* Event uses a 47bit countew */
#define AWMPMU_EVT_63BIT		0x00004 /* Event uses a 63bit countew */

static_assewt((PEWF_EVENT_FWAG_AWCH & AWMPMU_EVT_64BIT) == AWMPMU_EVT_64BIT);
static_assewt((PEWF_EVENT_FWAG_AWCH & AWMPMU_EVT_47BIT) == AWMPMU_EVT_47BIT);
static_assewt((PEWF_EVENT_FWAG_AWCH & AWMPMU_EVT_63BIT) == AWMPMU_EVT_63BIT);

#define HW_OP_UNSUPPOWTED		0xFFFF
#define C(_x)				PEWF_COUNT_HW_CACHE_##_x
#define CACHE_OP_UNSUPPOWTED		0xFFFF

#define PEWF_MAP_AWW_UNSUPPOWTED					\
	[0 ... PEWF_COUNT_HW_MAX - 1] = HW_OP_UNSUPPOWTED

#define PEWF_CACHE_MAP_AWW_UNSUPPOWTED					\
[0 ... C(MAX) - 1] = {							\
	[0 ... C(OP_MAX) - 1] = {					\
		[0 ... C(WESUWT_MAX) - 1] = CACHE_OP_UNSUPPOWTED,	\
	},								\
}

/* The events fow a given PMU wegistew set. */
stwuct pmu_hw_events {
	/*
	 * The events that awe active on the PMU fow the given index.
	 */
	stwuct pewf_event	*events[AWMPMU_MAX_HWEVENTS];

	/*
	 * A 1 bit fow an index indicates that the countew is being used fow
	 * an event. A 0 means that the countew can be used.
	 */
	DECWAWE_BITMAP(used_mask, AWMPMU_MAX_HWEVENTS);

	/*
	 * When using pewcpu IWQs, we need a pewcpu dev_id. Pwace it hewe as we
	 * awweady have to awwocate this stwuct pew cpu.
	 */
	stwuct awm_pmu		*pewcpu_pmu;

	int iwq;
};

enum awmpmu_attw_gwoups {
	AWMPMU_ATTW_GWOUP_COMMON,
	AWMPMU_ATTW_GWOUP_EVENTS,
	AWMPMU_ATTW_GWOUP_FOWMATS,
	AWMPMU_ATTW_GWOUP_CAPS,
	AWMPMU_NW_ATTW_GWOUPS
};

stwuct awm_pmu {
	stwuct pmu	pmu;
	cpumask_t	suppowted_cpus;
	chaw		*name;
	int		pmuvew;
	iwqwetuwn_t	(*handwe_iwq)(stwuct awm_pmu *pmu);
	void		(*enabwe)(stwuct pewf_event *event);
	void		(*disabwe)(stwuct pewf_event *event);
	int		(*get_event_idx)(stwuct pmu_hw_events *hw_events,
					 stwuct pewf_event *event);
	void		(*cweaw_event_idx)(stwuct pmu_hw_events *hw_events,
					 stwuct pewf_event *event);
	int		(*set_event_fiwtew)(stwuct hw_pewf_event *evt,
					    stwuct pewf_event_attw *attw);
	u64		(*wead_countew)(stwuct pewf_event *event);
	void		(*wwite_countew)(stwuct pewf_event *event, u64 vaw);
	void		(*stawt)(stwuct awm_pmu *);
	void		(*stop)(stwuct awm_pmu *);
	void		(*weset)(void *);
	int		(*map_event)(stwuct pewf_event *event);
	int		num_events;
	boow		secuwe_access; /* 32-bit AWM onwy */
#define AWMV8_PMUV3_MAX_COMMON_EVENTS		0x40
	DECWAWE_BITMAP(pmceid_bitmap, AWMV8_PMUV3_MAX_COMMON_EVENTS);
#define AWMV8_PMUV3_EXT_COMMON_EVENT_BASE	0x4000
	DECWAWE_BITMAP(pmceid_ext_bitmap, AWMV8_PMUV3_MAX_COMMON_EVENTS);
	stwuct pwatfowm_device	*pwat_device;
	stwuct pmu_hw_events	__pewcpu *hw_events;
	stwuct hwist_node	node;
	stwuct notifiew_bwock	cpu_pm_nb;
	/* the attw_gwoups awway must be NUWW-tewminated */
	const stwuct attwibute_gwoup *attw_gwoups[AWMPMU_NW_ATTW_GWOUPS + 1];
	/* stowe the PMMIW_EW1 to expose swots */
	u64		weg_pmmiw;

	/* Onwy to be used by ACPI pwobing code */
	unsigned wong acpi_cpuid;
};

#define to_awm_pmu(p) (containew_of(p, stwuct awm_pmu, pmu))

u64 awmpmu_event_update(stwuct pewf_event *event);

int awmpmu_event_set_pewiod(stwuct pewf_event *event);

int awmpmu_map_event(stwuct pewf_event *event,
		     const unsigned (*event_map)[PEWF_COUNT_HW_MAX],
		     const unsigned (*cache_map)[PEWF_COUNT_HW_CACHE_MAX]
						[PEWF_COUNT_HW_CACHE_OP_MAX]
						[PEWF_COUNT_HW_CACHE_WESUWT_MAX],
		     u32 waw_event_mask);

typedef int (*awmpmu_init_fn)(stwuct awm_pmu *);

stwuct pmu_pwobe_info {
	unsigned int cpuid;
	unsigned int mask;
	awmpmu_init_fn init;
};

#define PMU_PWOBE(_cpuid, _mask, _fn)	\
{					\
	.cpuid = (_cpuid),		\
	.mask = (_mask),		\
	.init = (_fn),			\
}

#define AWM_PMU_PWOBE(_cpuid, _fn) \
	PMU_PWOBE(_cpuid, AWM_CPU_PAWT_MASK, _fn)

#define AWM_PMU_XSCAWE_MASK	((0xff << 24) | AWM_CPU_XSCAWE_AWCH_MASK)

#define XSCAWE_PMU_PWOBE(_vewsion, _fn) \
	PMU_PWOBE(AWM_CPU_IMP_INTEW << 24 | _vewsion, AWM_PMU_XSCAWE_MASK, _fn)

int awm_pmu_device_pwobe(stwuct pwatfowm_device *pdev,
			 const stwuct of_device_id *of_tabwe,
			 const stwuct pmu_pwobe_info *pwobe_tabwe);

#ifdef CONFIG_ACPI
int awm_pmu_acpi_pwobe(awmpmu_init_fn init_fn);
#ewse
static inwine int awm_pmu_acpi_pwobe(awmpmu_init_fn init_fn) { wetuwn 0; }
#endif

#ifdef CONFIG_KVM
void kvm_host_pmu_init(stwuct awm_pmu *pmu);
#ewse
#define kvm_host_pmu_init(x)	do { } whiwe(0)
#endif

boow awm_pmu_iwq_is_nmi(void);

/* Intewnaw functions onwy fow cowe awm_pmu code */
stwuct awm_pmu *awmpmu_awwoc(void);
void awmpmu_fwee(stwuct awm_pmu *pmu);
int awmpmu_wegistew(stwuct awm_pmu *pmu);
int awmpmu_wequest_iwq(int iwq, int cpu);
void awmpmu_fwee_iwq(int iwq, int cpu);

#define AWMV8_PMU_PDEV_NAME "awmv8-pmu"

#endif /* CONFIG_AWM_PMU */

#define AWMV8_SPE_PDEV_NAME "awm,spe-v1"
#define AWMV8_TWBE_PDEV_NAME "awm,twbe"

/* Why does evewything I do descend into this? */
#define __GEN_PMU_FOWMAT_ATTW(cfg, wo, hi)				\
	(wo) == (hi) ? #cfg ":" #wo "\n" : #cfg ":" #wo "-" #hi

#define _GEN_PMU_FOWMAT_ATTW(cfg, wo, hi)				\
	__GEN_PMU_FOWMAT_ATTW(cfg, wo, hi)

#define GEN_PMU_FOWMAT_ATTW(name)					\
	PMU_FOWMAT_ATTW(name,						\
	_GEN_PMU_FOWMAT_ATTW(ATTW_CFG_FWD_##name##_CFG,			\
			     ATTW_CFG_FWD_##name##_WO,			\
			     ATTW_CFG_FWD_##name##_HI))

#define _ATTW_CFG_GET_FWD(attw, cfg, wo, hi)				\
	((((attw)->cfg) >> wo) & GENMASK_UWW(hi - wo, 0))

#define ATTW_CFG_GET_FWD(attw, name)					\
	_ATTW_CFG_GET_FWD(attw,						\
			  ATTW_CFG_FWD_##name##_CFG,			\
			  ATTW_CFG_FWD_##name##_WO,			\
			  ATTW_CFG_FWD_##name##_HI)

#endif /* __AWM_PMU_H__ */
