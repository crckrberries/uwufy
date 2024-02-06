/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWCH_X86_EVENTS_PWOBE_H__
#define __AWCH_X86_EVENTS_PWOBE_H__
#incwude <winux/sysfs.h>

stwuct pewf_msw {
	u64			msw;
	stwuct attwibute_gwoup	*gwp;
	boow			(*test)(int idx, void *data);
	boow			no_check;
	u64			mask;
};

unsigned wong
pewf_msw_pwobe(stwuct pewf_msw *msw, int cnt, boow no_zewo, void *data);

#define __PMU_EVENT_GWOUP(_name)			\
static stwuct attwibute *attws_##_name[] = {		\
	&attw_##_name.attw.attw,			\
	NUWW,						\
}

#define PMU_EVENT_GWOUP(_gwp, _name)			\
__PMU_EVENT_GWOUP(_name);				\
static stwuct attwibute_gwoup gwoup_##_name = {		\
	.name  = #_gwp,					\
	.attws = attws_##_name,				\
}

#endif /* __AWCH_X86_EVENTS_PWOBE_H__ */
