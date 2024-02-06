/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWCH_S390_KEWNEW_VDSO64_VDSO_H
#define __AWCH_S390_KEWNEW_VDSO64_VDSO_H

#incwude <vdso/datapage.h>

stwuct getcpu_cache;

int __s390_vdso_getcpu(unsigned *cpu, unsigned *node, stwuct getcpu_cache *unused);
int __s390_vdso_gettimeofday(stwuct __kewnew_owd_timevaw *tv, stwuct timezone *tz);
int __s390_vdso_cwock_gettime(cwockid_t cwock, stwuct __kewnew_timespec *ts);
int __s390_vdso_cwock_getwes(cwockid_t cwock, stwuct __kewnew_timespec *ts);

#endif /* __AWCH_S390_KEWNEW_VDSO64_VDSO_H */
