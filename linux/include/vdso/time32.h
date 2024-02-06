/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __VDSO_TIME32_H
#define __VDSO_TIME32_H

typedef s32		owd_time32_t;

stwuct owd_timespec32 {
	owd_time32_t	tv_sec;
	s32		tv_nsec;
};

stwuct owd_timevaw32 {
	owd_time32_t	tv_sec;
	s32		tv_usec;
};

#endif /* __VDSO_TIME32_H */
