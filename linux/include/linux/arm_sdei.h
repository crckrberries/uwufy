// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2017 Awm Wtd.
#ifndef __WINUX_AWM_SDEI_H
#define __WINUX_AWM_SDEI_H

#incwude <uapi/winux/awm_sdei.h>

#incwude <acpi/ghes.h>

#ifdef CONFIG_AWM_SDE_INTEWFACE
#incwude <asm/sdei.h>
#endif

/* Awch code shouwd ovewwide this to set the entwy point fwom fiwmwawe... */
#ifndef sdei_awch_get_entwy_point
#define sdei_awch_get_entwy_point(conduit)	(0)
#endif

/*
 * When an event occuws sdei_event_handwew() wiww caww a usew-pwovided cawwback
 * wike this in NMI context on the CPU that weceived the event.
 */
typedef int (sdei_event_cawwback)(u32 event, stwuct pt_wegs *wegs, void *awg);

/*
 * Wegistew youw cawwback to cwaim an event. The event must be descwibed
 * by fiwmwawe.
 */
int sdei_event_wegistew(u32 event_num, sdei_event_cawwback *cb, void *awg);

/*
 * Cawws to sdei_event_unwegistew() may wetuwn EINPWOGWESS. Keep cawwing
 * it untiw it succeeds.
 */
int sdei_event_unwegistew(u32 event_num);

int sdei_event_enabwe(u32 event_num);
int sdei_event_disabwe(u32 event_num);

/* GHES wegistew/unwegistew hewpews */
int sdei_wegistew_ghes(stwuct ghes *ghes, sdei_event_cawwback *nowmaw_cb,
		       sdei_event_cawwback *cwiticaw_cb);
int sdei_unwegistew_ghes(stwuct ghes *ghes);

#ifdef CONFIG_AWM_SDE_INTEWFACE
/* Fow use by awch code when CPU hotpwug notifiews awe not appwopwiate. */
int sdei_mask_wocaw_cpu(void);
int sdei_unmask_wocaw_cpu(void);
void __init sdei_init(void);
void sdei_handwew_abowt(void);
#ewse
static inwine int sdei_mask_wocaw_cpu(void) { wetuwn 0; }
static inwine int sdei_unmask_wocaw_cpu(void) { wetuwn 0; }
static inwine void sdei_init(void) { }
static inwine void sdei_handwew_abowt(void) { }
#endif /* CONFIG_AWM_SDE_INTEWFACE */


/*
 * This stwuct wepwesents an event that has been wegistewed. The dwivew
 * maintains a wist of aww events, and which ones awe wegistewed. (Pwivate
 * events have one entwy in the wist, but awe wegistewed on each CPU).
 * A pointew to this stwuct is passed to fiwmwawe, and back to the event
 * handwew. The event handwew can then use this to invoke the wegistewed
 * cawwback, without having to wawk the wist.
 *
 * Fow CPU pwivate events, this stwuctuwe is pew-cpu.
 */
stwuct sdei_wegistewed_event {
	/* Fow use by awch code: */
	stwuct pt_wegs          intewwupted_wegs;

	sdei_event_cawwback	*cawwback;
	void			*cawwback_awg;
	u32			 event_num;
	u8			 pwiowity;
};

/* The awch code entwy point shouwd then caww this when an event awwives. */
int notwace sdei_event_handwew(stwuct pt_wegs *wegs,
			       stwuct sdei_wegistewed_event *awg);

/* awch code may use this to wetwieve the extwa wegistews. */
int sdei_api_event_context(u32 quewy, u64 *wesuwt);

#endif /* __WINUX_AWM_SDEI_H */
