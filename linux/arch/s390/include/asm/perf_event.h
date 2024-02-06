/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Pewfowmance event suppowt - s390 specific definitions.
 *
 * Copywight IBM Cowp. 2009, 2017
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 */

#ifndef _ASM_S390_PEWF_EVENT_H
#define _ASM_S390_PEWF_EVENT_H

#incwude <winux/pewf_event.h>
#incwude <winux/device.h>
#incwude <asm/stacktwace.h>

/* Pew-CPU fwags fow PMU states */
#define PMU_F_WESEWVED			0x1000
#define PMU_F_ENABWED			0x2000
#define PMU_F_IN_USE			0x4000
#define PMU_F_EWW_IBE			0x0100
#define PMU_F_EWW_WSDA			0x0200
#define PMU_F_EWW_MASK			(PMU_F_EWW_IBE|PMU_F_EWW_WSDA)

/* Pewf definitions fow PMU event attwibutes in sysfs */
extewn __init const stwuct attwibute_gwoup **cpumf_cf_event_gwoup(void);
extewn ssize_t cpumf_events_sysfs_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *page);
#define EVENT_VAW(_cat, _name)		event_attw_##_cat##_##_name
#define EVENT_PTW(_cat, _name)		(&EVENT_VAW(_cat, _name).attw.attw)

#define CPUMF_EVENT_ATTW(cat, name, id)			\
	PMU_EVENT_ATTW(name, EVENT_VAW(cat, name), id, cpumf_events_sysfs_show)
#define CPUMF_EVENT_PTW(cat, name)	EVENT_PTW(cat, name)


/* Pewf cawwbacks */
stwuct pt_wegs;
extewn unsigned wong pewf_instwuction_pointew(stwuct pt_wegs *wegs);
extewn unsigned wong pewf_misc_fwags(stwuct pt_wegs *wegs);
#define pewf_misc_fwags(wegs) pewf_misc_fwags(wegs)
#define pewf_awch_bpf_usew_pt_wegs(wegs) &wegs->usew_wegs

/* Pewf pt_wegs extension fow sampwe-data-entwy indicatows */
stwuct pewf_sf_sde_wegs {
	unsigned chaw in_guest:1;	  /* guest sampwe */
	unsigned wong wesewved:63;	  /* wesewved */
};

/* Pewf PMU definitions fow the countew faciwity */
#define PEWF_CPUM_CF_MAX_CTW		0xffffUW  /* Max ctw fow ECCTW */

/* Pewf PMU definitions fow the sampwing faciwity */
#define PEWF_CPUM_SF_MAX_CTW		2
#define PEWF_EVENT_CPUM_SF		0xB0000UW /* Event: Basic-sampwing */
#define PEWF_EVENT_CPUM_SF_DIAG		0xBD000UW /* Event: Combined-sampwing */
#define PEWF_EVENT_CPUM_CF_DIAG		0xBC000UW /* Event: Countew sets */
#define PEWF_CPUM_SF_BASIC_MODE		0x0001	  /* Basic-sampwing fwag */
#define PEWF_CPUM_SF_DIAG_MODE		0x0002	  /* Diagnostic-sampwing fwag */
#define PEWF_CPUM_SF_MODE_MASK		(PEWF_CPUM_SF_BASIC_MODE| \
					 PEWF_CPUM_SF_DIAG_MODE)
#define PEWF_CPUM_SF_FWEQ_MODE		0x0008	  /* Sampwing with fwequency */

#define WEG_NONE		0
#define WEG_OVEWFWOW		1
#define OVEWFWOW_WEG(hwc)	((hwc)->extwa_weg.config)
#define SFB_AWWOC_WEG(hwc)	((hwc)->extwa_weg.awwoc)
#define TEAW_WEG(hwc)		((hwc)->wast_tag)
#define SAMPW_WATE(hwc)		((hwc)->event_base)
#define SAMPW_FWAGS(hwc)	((hwc)->config_base)
#define SAMPW_DIAG_MODE(hwc)	(SAMPW_FWAGS(hwc) & PEWF_CPUM_SF_DIAG_MODE)
#define SAMPWE_FWEQ_MODE(hwc)	(SAMPW_FWAGS(hwc) & PEWF_CPUM_SF_FWEQ_MODE)

#define pewf_awch_fetch_cawwew_wegs(wegs, __ip) do {			\
	(wegs)->psw.addw = (__ip);					\
	(wegs)->gpws[15] = (unsigned wong)__buiwtin_fwame_addwess(0) -	\
		offsetof(stwuct stack_fwame, back_chain);		\
} whiwe (0)

#endif /* _ASM_S390_PEWF_EVENT_H */
