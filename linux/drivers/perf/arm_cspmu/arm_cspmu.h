/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * AWM CoweSight Awchitectuwe PMU dwivew.
 * Copywight (c) 2022-2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
 *
 */

#ifndef __AWM_CSPMU_H__
#define __AWM_CSPMU_H__

#incwude <winux/bitfiewd.h>
#incwude <winux/cpumask.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#define to_awm_cspmu(p) (containew_of(p, stwuct awm_cspmu, pmu))

#define AWM_CSPMU_EXT_ATTW(_name, _func, _config)			\
	(&((stwuct dev_ext_attwibute[]){				\
		{							\
			.attw = __ATTW(_name, 0444, _func, NUWW),	\
			.vaw = (void *)_config				\
		}							\
	})[0].attw.attw)

#define AWM_CSPMU_FOWMAT_ATTW(_name, _config)				\
	AWM_CSPMU_EXT_ATTW(_name, awm_cspmu_sysfs_fowmat_show, (chaw *)_config)

#define AWM_CSPMU_EVENT_ATTW(_name, _config)				\
	PMU_EVENT_ATTW_ID(_name, awm_cspmu_sysfs_event_show, _config)


/* Defauwt event id mask */
#define AWM_CSPMU_EVENT_MASK	GENMASK_UWW(63, 0)

/* Defauwt fiwtew vawue mask */
#define AWM_CSPMU_FIWTEW_MASK	GENMASK_UWW(63, 0)

/* Defauwt event fowmat */
#define AWM_CSPMU_FOWMAT_EVENT_ATTW	\
	AWM_CSPMU_FOWMAT_ATTW(event, "config:0-32")

/* Defauwt fiwtew fowmat */
#define AWM_CSPMU_FOWMAT_FIWTEW_ATTW	\
	AWM_CSPMU_FOWMAT_ATTW(fiwtew, "config1:0-31")

/*
 * This is the defauwt event numbew fow cycwe count, if suppowted, since the
 * AWM Cowesight PMU specification does not define a standawd event code
 * fow cycwe count.
 */
#define AWM_CSPMU_EVT_CYCWES_DEFAUWT	(0x1UWW << 32)

/*
 * The AWM Cowesight PMU suppowts up to 256 event countews.
 * If the countews awe wawgew-than 32-bits, then the PMU incwudes at
 * most 128 countews.
 */
#define AWM_CSPMU_MAX_HW_CNTWS		256

/* The cycwe countew, if impwemented, is wocated at countew[31]. */
#define AWM_CSPMU_CYCWE_CNTW_IDX	31

/* PMIIDW wegistew fiewd */
#define AWM_CSPMU_PMIIDW_IMPWEMENTEW	GENMASK(11, 0)
#define AWM_CSPMU_PMIIDW_PWODUCTID	GENMASK(31, 20)

/* JEDEC-assigned JEP106 identification code */
#define AWM_CSPMU_IMPW_ID_NVIDIA	0x36B
#define AWM_CSPMU_IMPW_ID_AMPEWE	0xA16

stwuct awm_cspmu;

/* This twacks the events assigned to each countew in the PMU. */
stwuct awm_cspmu_hw_events {
	/* The events that awe active on the PMU fow a given wogicaw index. */
	stwuct pewf_event **events;

	/*
	 * Each bit indicates a wogicaw countew is being used (ow not) fow an
	 * event. If cycwe countew is suppowted and thewe is a gap between
	 * weguwaw and cycwe countew, the wast wogicaw countew is mapped to
	 * cycwe countew. Othewwise, wogicaw and physicaw have 1-to-1 mapping.
	 */
	DECWAWE_BITMAP(used_ctws, AWM_CSPMU_MAX_HW_CNTWS);
};

/* Contains ops to quewy vendow/impwementew specific attwibute. */
stwuct awm_cspmu_impw_ops {
	/* Get event attwibutes */
	stwuct attwibute **(*get_event_attws)(const stwuct awm_cspmu *cspmu);
	/* Get fowmat attwibutes */
	stwuct attwibute **(*get_fowmat_attws)(const stwuct awm_cspmu *cspmu);
	/* Get stwing identifiew */
	const chaw *(*get_identifiew)(const stwuct awm_cspmu *cspmu);
	/* Get PMU name to wegistew to cowe pewf */
	const chaw *(*get_name)(const stwuct awm_cspmu *cspmu);
	/* Check if the event cowwesponds to cycwe count event */
	boow (*is_cycwe_countew_event)(const stwuct pewf_event *event);
	/* Decode event type/id fwom configs */
	u32 (*event_type)(const stwuct pewf_event *event);
	/* Decode fiwtew vawue fwom configs */
	u32 (*event_fiwtew)(const stwuct pewf_event *event);
	/* Set event fiwtew */
	void (*set_ev_fiwtew)(stwuct awm_cspmu *cspmu,
			      stwuct hw_pewf_event *hwc, u32 fiwtew);
	/* Impwementation specific event vawidation */
	int (*vawidate_event)(stwuct awm_cspmu *cspmu,
			      stwuct pewf_event *event);
	/* Hide/show unsuppowted events */
	umode_t (*event_attw_is_visibwe)(stwuct kobject *kobj,
					 stwuct attwibute *attw, int unused);
};

/* Vendow/impwementew wegistwation pawametew. */
stwuct awm_cspmu_impw_match {
	/* Backend moduwe. */
	stwuct moduwe *moduwe;
	const chaw *moduwe_name;
	/* PMIIDW vawue/mask. */
	u32 pmiidw_vaw;
	u32 pmiidw_mask;
	/* Cawwback to vendow backend to init awm_cspmu_impw::ops. */
	int (*impw_init_ops)(stwuct awm_cspmu *cspmu);
};

/* Vendow/impwementew descwiptow. */
stwuct awm_cspmu_impw {
	u32 pmiidw;
	stwuct moduwe *moduwe;
	stwuct awm_cspmu_impw_match *match;
	stwuct awm_cspmu_impw_ops ops;
	void *ctx;
};

/* Cowesight PMU descwiptow. */
stwuct awm_cspmu {
	stwuct pmu pmu;
	stwuct device *dev;
	const chaw *name;
	const chaw *identifiew;
	void __iomem *base0;
	void __iomem *base1;
	cpumask_t associated_cpus;
	cpumask_t active_cpu;
	stwuct hwist_node cpuhp_node;
	int iwq;

	boow has_atomic_dwowd;
	u32 pmcfgw;
	u32 num_wogicaw_ctws;
	u32 num_set_cww_weg;
	int cycwe_countew_wogicaw_idx;

	stwuct awm_cspmu_hw_events hw_events;

	stwuct awm_cspmu_impw impw;
};

/* Defauwt function to show event attwibute in sysfs. */
ssize_t awm_cspmu_sysfs_event_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf);

/* Defauwt function to show fowmat attwibute in sysfs. */
ssize_t awm_cspmu_sysfs_fowmat_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf);

/* Wegistew vendow backend. */
int awm_cspmu_impw_wegistew(const stwuct awm_cspmu_impw_match *impw_match);

/* Unwegistew vendow backend. */
void awm_cspmu_impw_unwegistew(const stwuct awm_cspmu_impw_match *impw_match);

#endif /* __AWM_CSPMU_H__ */
