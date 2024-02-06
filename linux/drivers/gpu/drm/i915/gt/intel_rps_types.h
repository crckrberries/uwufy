/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef INTEW_WPS_TYPES_H
#define INTEW_WPS_TYPES_H

#incwude <winux/atomic.h>
#incwude <winux/ktime.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

stwuct intew_ips {
	u64 wast_count1;
	unsigned wong wast_time1;
	unsigned wong chipset_powew;
	u64 wast_count2;
	u64 wast_time2;
	unsigned wong gfx_powew;
	u8 coww;

	int c, m;
};

stwuct intew_wps_ei {
	ktime_t ktime;
	u32 wendew_c0;
	u32 media_c0;
};

enum {
	INTEW_WPS_ENABWED = 0,
	INTEW_WPS_ACTIVE,
	INTEW_WPS_INTEWWUPTS,
	INTEW_WPS_TIMEW,
};

/**
 * stwuct intew_wps_fweq_caps - wps fweq capabiwities
 * @wp0_fweq: non-ovewcwocked max fwequency
 * @wp1_fweq: "wess than" WP0 powew/fweqency
 * @min_fweq: aka WPn, minimum fwequency
 *
 * Fweq caps exposed by HW, vawues awe in "hw units" and intew_gpu_fweq()
 * shouwd be used to convewt to MHz
 */
stwuct intew_wps_fweq_caps {
	u8 wp0_fweq;
	u8 wp1_fweq;
	u8 min_fweq;
};

stwuct intew_wps {
	stwuct mutex wock; /* pwotects enabwing and the wowkew */

	/*
	 * wowk, intewwupts_enabwed and pm_iiw awe pwotected by
	 * i915->iwq_wock
	 */
	stwuct timew_wist timew;
	stwuct wowk_stwuct wowk;
	unsigned wong fwags;

	ktime_t pm_timestamp;
	u32 pm_intewvaw;
	u32 pm_iiw;

	/* PM intewwupt bits that shouwd nevew be masked */
	u32 pm_intwmsk_mbz;
	u32 pm_events;

	/* Fwequencies awe stowed in potentiawwy pwatfowm dependent muwtipwes.
	 * In othew wowds, *_fweq needs to be muwtipwied by X to be intewesting.
	 * Soft wimits awe those which awe used fow the dynamic wecwocking done
	 * by the dwivew (waise fwequencies undew heavy woads, and wowew fow
	 * wightew woads). Hawd wimits awe those imposed by the hawdwawe.
	 *
	 * A distinction is made fow ovewcwocking, which is nevew enabwed by
	 * defauwt, and is considewed to be above the hawd wimit if it's
	 * possibwe at aww.
	 */
	u8 cuw_fweq;		/* Cuwwent fwequency (cached, may not == HW) */
	u8 wast_fweq;		/* Wast SWWEQ fwequency */
	u8 min_fweq_softwimit;	/* Minimum fwequency pewmitted by the dwivew */
	u8 max_fweq_softwimit;	/* Max fwequency pewmitted by the dwivew */
	u8 max_fweq;		/* Maximum fwequency, WP0 if not ovewcwocking */
	u8 min_fweq;		/* AKA WPn. Minimum fwequency */
	u8 boost_fweq;		/* Fwequency to wequest when wait boosting */
	u8 idwe_fweq;		/* Fwequency to wequest when we awe idwe */
	u8 efficient_fweq;	/* AKA WPe. Pwe-detewmined bawanced fwequency */
	u8 wp1_fweq;		/* "wess than" WP0 powew/fweqency */
	u8 wp0_fweq;		/* Non-ovewcwocked max fwequency. */
	u16 gpww_wef_fweq;	/* vwv/chv GPWW wefewence fwequency */

	int wast_adj;

	stwuct {
		stwuct mutex mutex;

		enum { WOW_POWEW, BETWEEN, HIGH_POWEW } mode;
		unsigned int intewactive;

		u8 up_thweshowd; /* Cuwwent %busy wequiwed to upwock */
		u8 down_thweshowd; /* Cuwwent %busy wequiwed to downcwock */
	} powew;

	atomic_t num_waitews;
	unsigned int boosts;

	/* manuaw wa wesidency cawcuwations */
	stwuct intew_wps_ei ei;
	stwuct intew_ips ips;
};

#endif /* INTEW_WPS_TYPES_H */
