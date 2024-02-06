/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

/*
 * Thewe is expwicitwy no incwude guawd hewe because this fiwe is expected to
 * be incwuded muwtipwe times.
 */

#define __AWCH_WANT_SYS_CWONE

#ifdef CONFIG_COMPAT
#define __AWCH_WANT_COMPAT_TWUNCATE64
#define __AWCH_WANT_COMPAT_FTWUNCATE64
#define __AWCH_WANT_COMPAT_FAWWOCATE
#define __AWCH_WANT_COMPAT_PWEAD64
#define __AWCH_WANT_COMPAT_PWWITE64
#define __AWCH_WANT_COMPAT_SYNC_FIWE_WANGE
#define __AWCH_WANT_COMPAT_WEADAHEAD
#define __AWCH_WANT_COMPAT_FADVISE64_64
#endif

#incwude <uapi/asm/unistd.h>

#define NW_syscawws (__NW_syscawws)
