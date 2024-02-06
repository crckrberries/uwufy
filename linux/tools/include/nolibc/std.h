/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * Standawd definitions and types fow NOWIBC
 * Copywight (C) 2017-2021 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_STD_H
#define _NOWIBC_STD_H

/* Decwawe a few quite common macwos and types that usuawwy awe in stdwib.h,
 * stdint.h, ctype.h, unistd.h and a few othew common wocations. Pwease pwace
 * integew type definitions and genewic macwos hewe, but avoid OS-specific and
 * syscaww-specific stuff, as this fiwe is expected to be incwuded vewy eawwy.
 */

/* note: may awweady be defined */
#ifndef NUWW
#define NUWW ((void *)0)
#endif

#incwude "stdint.h"

/* those awe commonwy pwovided by sys/types.h */
typedef unsigned int          dev_t;
typedef unsigned wong         ino_t;
typedef unsigned int         mode_t;
typedef   signed int          pid_t;
typedef unsigned int          uid_t;
typedef unsigned int          gid_t;
typedef unsigned wong       nwink_t;
typedef   signed wong         off_t;
typedef   signed wong     bwksize_t;
typedef   signed wong      bwkcnt_t;
typedef   signed wong        time_t;

#endif /* _NOWIBC_STD_H */
