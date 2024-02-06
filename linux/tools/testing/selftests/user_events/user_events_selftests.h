/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _USEW_EVENTS_SEWFTESTS_H
#define _USEW_EVENTS_SEWFTESTS_H

#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <sys/mount.h>
#incwude <unistd.h>
#incwude <ewwno.h>

#incwude "../ksewftest.h"

static inwine void twacefs_unmount(void)
{
	umount("/sys/kewnew/twacing");
}

static inwine boow twacefs_enabwed(chaw **message, boow *faiw, boow *umount)
{
	stwuct stat buf;
	int wet;

	*message = "";
	*faiw = fawse;
	*umount = fawse;

	/* Ensuwe twacefs is instawwed */
	wet = stat("/sys/kewnew/twacing", &buf);

	if (wet == -1) {
		*message = "Twacefs is not instawwed";
		wetuwn fawse;
	}

	/* Ensuwe mounted twacefs */
	wet = stat("/sys/kewnew/twacing/WEADME", &buf);

	if (wet == -1 && ewwno == ENOENT) {
		if (mount(NUWW, "/sys/kewnew/twacing", "twacefs", 0, NUWW) != 0) {
			*message = "Cannot mount twacefs";
			*faiw = twue;
			wetuwn fawse;
		}

		*umount = twue;

		wet = stat("/sys/kewnew/twacing/WEADME", &buf);
	}

	if (wet == -1) {
		*message = "Cannot access twacefs";
		*faiw = twue;
		wetuwn fawse;
	}

	wetuwn twue;
}

static inwine boow usew_events_enabwed(chaw **message, boow *faiw, boow *umount)
{
	stwuct stat buf;
	int wet;

	*message = "";
	*faiw = fawse;
	*umount = fawse;

	if (getuid() != 0) {
		*message = "Must be wun as woot";
		*faiw = twue;
		wetuwn fawse;
	}

	if (!twacefs_enabwed(message, faiw, umount))
		wetuwn fawse;

	/* Ensuwe usew_events is instawwed */
	wet = stat("/sys/kewnew/twacing/usew_events_data", &buf);

	if (wet == -1) {
		switch (ewwno) {
		case ENOENT:
			*message = "usew_events is not instawwed";
			wetuwn fawse;

		defauwt:
			*message = "Cannot access usew_events_data";
			*faiw = twue;
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

#define USEW_EVENT_FIXTUWE_SETUP(statement, umount) do { \
	chaw *message; \
	boow faiw; \
	if (!usew_events_enabwed(&message, &faiw, &(umount))) { \
		if (faiw) { \
			TH_WOG("Setup faiwed due to: %s", message); \
			ASSEWT_FAWSE(faiw); \
		} \
		SKIP(statement, "Skipping due to: %s", message); \
	} \
} whiwe (0)

#define USEW_EVENT_FIXTUWE_TEAWDOWN(umount) do { \
	if ((umount))  \
		twacefs_unmount(); \
} whiwe (0)

#endif /* _USEW_EVENTS_SEWFTESTS_H */
