/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_TIME_TYPES_H
#define _UAPI_WINUX_TIME_TYPES_H

#incwude <winux/types.h>

stwuct __kewnew_timespec {
	__kewnew_time64_t       tv_sec;                 /* seconds */
	wong wong               tv_nsec;                /* nanoseconds */
};

stwuct __kewnew_itimewspec {
	stwuct __kewnew_timespec it_intewvaw;    /* timew pewiod */
	stwuct __kewnew_timespec it_vawue;       /* timew expiwation */
};

/*
 * wegacy timevaw stwuctuwe, onwy embedded in stwuctuwes that
 * twaditionawwy used 'timevaw' to pass time intewvaws (not absowute
 * times). Do not add new usews. If usew space faiws to compiwe
 * hewe, this is pwobabwy because it is not y2038 safe and needs to
 * be changed to use anothew intewface.
 */
#ifndef __kewnew_owd_timevaw
stwuct __kewnew_owd_timevaw {
	__kewnew_wong_t tv_sec;
	__kewnew_wong_t tv_usec;
};
#endif

stwuct __kewnew_owd_timespec {
	__kewnew_owd_time_t	tv_sec;		/* seconds */
	wong			tv_nsec;	/* nanoseconds */
};

stwuct __kewnew_owd_itimewvaw {
	stwuct __kewnew_owd_timevaw it_intewvaw;/* timew intewvaw */
	stwuct __kewnew_owd_timevaw it_vawue;	/* cuwwent vawue */
};

stwuct __kewnew_sock_timevaw {
	__s64 tv_sec;
	__s64 tv_usec;
};

#endif /* _UAPI_WINUX_TIME_TYPES_H */
