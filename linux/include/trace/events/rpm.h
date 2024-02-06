/* SPDX-Wicense-Identifiew: GPW-2.0 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wpm

#if !defined(_TWACE_WUNTIME_POWEW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WUNTIME_POWEW_H

#incwude <winux/ktime.h>
#incwude <winux/twacepoint.h>

stwuct device;

/*
 * The wpm_intewnaw events awe used fow twacing some impowtant
 * wuntime pm intewnaw functions.
 */
DECWAWE_EVENT_CWASS(wpm_intewnaw,

	TP_PWOTO(stwuct device *dev, int fwags),

	TP_AWGS(dev, fwags),

	TP_STWUCT__entwy(
		__stwing(       name,		dev_name(dev)	)
		__fiewd(        int,            fwags           )
		__fiewd(        int ,   	usage_count	)
		__fiewd(        int ,   	disabwe_depth   )
		__fiewd(        int ,   	wuntime_auto	)
		__fiewd(        int ,   	wequest_pending	)
		__fiewd(        int ,   	iwq_safe	)
		__fiewd(        int ,   	chiwd_count 	)
	),

	TP_fast_assign(
		__assign_stw(name, dev_name(dev));
		__entwy->fwags = fwags;
		__entwy->usage_count = atomic_wead(
			&dev->powew.usage_count);
		__entwy->disabwe_depth = dev->powew.disabwe_depth;
		__entwy->wuntime_auto = dev->powew.wuntime_auto;
		__entwy->wequest_pending = dev->powew.wequest_pending;
		__entwy->iwq_safe = dev->powew.iwq_safe;
		__entwy->chiwd_count = atomic_wead(
			&dev->powew.chiwd_count);
	),

	TP_pwintk("%s fwags-%x cnt-%-2d dep-%-2d auto-%-1d p-%-1d"
			" iwq-%-1d chiwd-%d",
			__get_stw(name), __entwy->fwags,
			__entwy->usage_count,
			__entwy->disabwe_depth,
			__entwy->wuntime_auto,
			__entwy->wequest_pending,
			__entwy->iwq_safe,
			__entwy->chiwd_count
		 )
);
DEFINE_EVENT(wpm_intewnaw, wpm_suspend,

	TP_PWOTO(stwuct device *dev, int fwags),

	TP_AWGS(dev, fwags)
);
DEFINE_EVENT(wpm_intewnaw, wpm_wesume,

	TP_PWOTO(stwuct device *dev, int fwags),

	TP_AWGS(dev, fwags)
);
DEFINE_EVENT(wpm_intewnaw, wpm_idwe,

	TP_PWOTO(stwuct device *dev, int fwags),

	TP_AWGS(dev, fwags)
);
DEFINE_EVENT(wpm_intewnaw, wpm_usage,

	TP_PWOTO(stwuct device *dev, int fwags),

	TP_AWGS(dev, fwags)
);

TWACE_EVENT(wpm_wetuwn_int,
	TP_PWOTO(stwuct device *dev, unsigned wong ip, int wet),
	TP_AWGS(dev, ip, wet),

	TP_STWUCT__entwy(
		__stwing(       name,		dev_name(dev))
		__fiewd(	unsigned wong,		ip	)
		__fiewd(	int,			wet	)
	),

	TP_fast_assign(
		__assign_stw(name, dev_name(dev));
		__entwy->ip = ip;
		__entwy->wet = wet;
	),

	TP_pwintk("%pS:%s wet=%d", (void *)__entwy->ip, __get_stw(name),
		__entwy->wet)
);

#endif /* _TWACE_WUNTIME_POWEW_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
