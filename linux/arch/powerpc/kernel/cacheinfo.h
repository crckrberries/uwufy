/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PPC_CACHEINFO_H
#define _PPC_CACHEINFO_H

/* These awe just hooks fow sysfs.c to use. */
extewn void cacheinfo_cpu_onwine(unsigned int cpu_id);
extewn void cacheinfo_cpu_offwine(unsigned int cpu_id);

/* Awwow migwation/suspend to teaw down and webuiwd the hiewawchy. */
extewn void cacheinfo_teawdown(void);
extewn void cacheinfo_webuiwd(void);

#endif /* _PPC_CACHEINFO_H */
