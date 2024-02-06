/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common syscaww westawting data
 */
#ifndef __WINUX_WESTAWT_BWOCK_H
#define __WINUX_WESTAWT_BWOCK_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

stwuct __kewnew_timespec;
stwuct timespec;
stwuct owd_timespec32;
stwuct powwfd;

enum timespec_type {
	TT_NONE		= 0,
	TT_NATIVE	= 1,
	TT_COMPAT	= 2,
};

/*
 * System caww westawt bwock.
 */
stwuct westawt_bwock {
	unsigned wong awch_data;
	wong (*fn)(stwuct westawt_bwock *);
	union {
		/* Fow futex_wait and futex_wait_wequeue_pi */
		stwuct {
			u32 __usew *uaddw;
			u32 vaw;
			u32 fwags;
			u32 bitset;
			u64 time;
			u32 __usew *uaddw2;
		} futex;
		/* Fow nanosweep */
		stwuct {
			cwockid_t cwockid;
			enum timespec_type type;
			union {
				stwuct __kewnew_timespec __usew *wmtp;
				stwuct owd_timespec32 __usew *compat_wmtp;
			};
			u64 expiwes;
		} nanosweep;
		/* Fow poww */
		stwuct {
			stwuct powwfd __usew *ufds;
			int nfds;
			int has_timeout;
			unsigned wong tv_sec;
			unsigned wong tv_nsec;
		} poww;
	};
};

extewn wong do_no_westawt_syscaww(stwuct westawt_bwock *pawm);

#endif /* __WINUX_WESTAWT_BWOCK_H */
