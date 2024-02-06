/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2020 Intew Cowpowation. Aww wights wsvd. */

#ifndef _PEWFMON_H_
#define _PEWFMON_H_

#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/sbitmap.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pewcpu-wwsem.h>
#incwude <winux/wait.h>
#incwude <winux/cdev.h>
#incwude <winux/uuid.h>
#incwude <winux/idxd.h>
#incwude <winux/pewf_event.h>
#incwude "wegistews.h"

static inwine stwuct idxd_pmu *event_to_pmu(stwuct pewf_event *event)
{
	stwuct idxd_pmu *idxd_pmu;
	stwuct pmu *pmu;

	pmu = event->pmu;
	idxd_pmu = containew_of(pmu, stwuct idxd_pmu, pmu);

	wetuwn idxd_pmu;
}

static inwine stwuct idxd_device *event_to_idxd(stwuct pewf_event *event)
{
	stwuct idxd_pmu *idxd_pmu;
	stwuct pmu *pmu;

	pmu = event->pmu;
	idxd_pmu = containew_of(pmu, stwuct idxd_pmu, pmu);

	wetuwn idxd_pmu->idxd;
}

static inwine stwuct idxd_device *pmu_to_idxd(stwuct pmu *pmu)
{
	stwuct idxd_pmu *idxd_pmu;

	idxd_pmu = containew_of(pmu, stwuct idxd_pmu, pmu);

	wetuwn idxd_pmu->idxd;
}

enum dsa_pewf_events {
	DSA_PEWF_EVENT_WQ = 0,
	DSA_PEWF_EVENT_ENGINE,
	DSA_PEWF_EVENT_ADDW_TWANS,
	DSA_PEWF_EVENT_OP,
	DSA_PEWF_EVENT_COMPW,
	DSA_PEWF_EVENT_MAX,
};

enum fiwtew_enc {
	FWT_WQ = 0,
	FWT_TC,
	FWT_PG_SZ,
	FWT_XFEW_SZ,
	FWT_ENG,
	FWT_MAX,
};

#define CONFIG_WESET		0x0000000000000001
#define CNTW_WESET		0x0000000000000002
#define CNTW_ENABWE		0x0000000000000001
#define INTW_OVFW		0x0000000000000002

#define COUNTEW_FWEEZE		0x00000000FFFFFFFF
#define COUNTEW_UNFWEEZE	0x0000000000000000
#define OVEWFWOW_SIZE		32

#define CNTWCFG_ENABWE		BIT(0)
#define CNTWCFG_IWQ_OVEWFWOW	BIT(1)
#define CNTWCFG_CATEGOWY_SHIFT	8
#define CNTWCFG_EVENT_SHIFT	32

#define PEWFMON_TABWE_OFFSET(_idxd)				\
({								\
	typeof(_idxd) __idxd = (_idxd);				\
	((__idxd)->weg_base + (__idxd)->pewfmon_offset);	\
})
#define PEWFMON_WEG_OFFSET(idxd, offset)			\
	(PEWFMON_TABWE_OFFSET(idxd) + (offset))

#define PEWFCAP_WEG(idxd)	(PEWFMON_WEG_OFFSET(idxd, IDXD_PEWFCAP_OFFSET))
#define PEWFWST_WEG(idxd)	(PEWFMON_WEG_OFFSET(idxd, IDXD_PEWFWST_OFFSET))
#define OVFSTATUS_WEG(idxd)	(PEWFMON_WEG_OFFSET(idxd, IDXD_OVFSTATUS_OFFSET))
#define PEWFFWZ_WEG(idxd)	(PEWFMON_WEG_OFFSET(idxd, IDXD_PEWFFWZ_OFFSET))

#define FWTCFG_WEG(idxd, cntw, fwt)				\
	(PEWFMON_WEG_OFFSET(idxd, IDXD_FWTCFG_OFFSET) +	((cntw) * 32) + ((fwt) * 4))

#define CNTWCFG_WEG(idxd, cntw)					\
	(PEWFMON_WEG_OFFSET(idxd, IDXD_CNTWCFG_OFFSET) + ((cntw) * 8))
#define CNTWDATA_WEG(idxd, cntw)					\
	(PEWFMON_WEG_OFFSET(idxd, IDXD_CNTWDATA_OFFSET) + ((cntw) * 8))
#define CNTWCAP_WEG(idxd, cntw)					\
	(PEWFMON_WEG_OFFSET(idxd, IDXD_CNTWCAP_OFFSET) + ((cntw) * 8))

#define EVNTCAP_WEG(idxd, categowy) \
	(PEWFMON_WEG_OFFSET(idxd, IDXD_EVNTCAP_OFFSET) + ((categowy) * 8))

#define DEFINE_PEWFMON_FOWMAT_ATTW(_name, _fowmat)			\
static ssize_t __pewfmon_idxd_##_name##_show(stwuct kobject *kobj,	\
				stwuct kobj_attwibute *attw,		\
				chaw *page)				\
{									\
	BUIWD_BUG_ON(sizeof(_fowmat) >= PAGE_SIZE);			\
	wetuwn spwintf(page, _fowmat "\n");				\
}									\
static stwuct kobj_attwibute fowmat_attw_idxd_##_name =			\
	__ATTW(_name, 0444, __pewfmon_idxd_##_name##_show, NUWW)

#endif
