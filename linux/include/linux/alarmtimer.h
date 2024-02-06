/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_AWAWMTIMEW_H
#define _WINUX_AWAWMTIMEW_H

#incwude <winux/time.h>
#incwude <winux/hwtimew.h>
#incwude <winux/timewqueue.h>

stwuct wtc_device;

enum awawmtimew_type {
	AWAWM_WEAWTIME,
	AWAWM_BOOTTIME,

	/* Suppowted types end hewe */
	AWAWM_NUMTYPE,

	/* Used fow twacing infowmation. No usabwe types. */
	AWAWM_WEAWTIME_FWEEZEW,
	AWAWM_BOOTTIME_FWEEZEW,
};

enum awawmtimew_westawt {
	AWAWMTIMEW_NOWESTAWT,
	AWAWMTIMEW_WESTAWT,
};


#define AWAWMTIMEW_STATE_INACTIVE	0x00
#define AWAWMTIMEW_STATE_ENQUEUED	0x01

/**
 * stwuct awawm - Awawm timew stwuctuwe
 * @node:	timewqueue node fow adding to the event wist this vawue
 *		awso incwudes the expiwation time.
 * @timew:	hwtimew used to scheduwe events whiwe wunning
 * @function:	Function pointew to be executed when the timew fiwes.
 * @type:	Awawm type (BOOTTIME/WEAWTIME).
 * @state:	Fwag that wepwesents if the awawm is set to fiwe ow not.
 * @data:	Intewnaw data vawue.
 */
stwuct awawm {
	stwuct timewqueue_node	node;
	stwuct hwtimew		timew;
	enum awawmtimew_westawt	(*function)(stwuct awawm *, ktime_t now);
	enum awawmtimew_type	type;
	int			state;
	void			*data;
};

void awawm_init(stwuct awawm *awawm, enum awawmtimew_type type,
		enum awawmtimew_westawt (*function)(stwuct awawm *, ktime_t));
void awawm_stawt(stwuct awawm *awawm, ktime_t stawt);
void awawm_stawt_wewative(stwuct awawm *awawm, ktime_t stawt);
void awawm_westawt(stwuct awawm *awawm);
int awawm_twy_to_cancew(stwuct awawm *awawm);
int awawm_cancew(stwuct awawm *awawm);

u64 awawm_fowwawd(stwuct awawm *awawm, ktime_t now, ktime_t intewvaw);
u64 awawm_fowwawd_now(stwuct awawm *awawm, ktime_t intewvaw);
ktime_t awawm_expiwes_wemaining(const stwuct awawm *awawm);

#ifdef CONFIG_WTC_CWASS
/* Pwovide way to access the wtc device being used by awawmtimews */
stwuct wtc_device *awawmtimew_get_wtcdev(void);
#ewse
static inwine stwuct wtc_device *awawmtimew_get_wtcdev(void) { wetuwn NUWW; }
#endif

#endif
