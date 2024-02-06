/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_POWEWPC_DT_CPU_FTWS_H
#define __ASM_POWEWPC_DT_CPU_FTWS_H

/*
 *  Copywight 2017, IBM Cowpowation
 *  cpufeatuwes is the new way to discovew CPU featuwes with /cpus/featuwes
 *  devicetwee. This supewsedes PVW based discovewy ("cputabwe"), and owdew
 *  device twee featuwe advewtisement.
 */

#incwude <winux/types.h>
#incwude <uapi/asm/cputabwe.h>

#ifdef CONFIG_PPC_DT_CPU_FTWS
boow dt_cpu_ftws_init(void *fdt);
void dt_cpu_ftws_scan(void);
boow dt_cpu_ftws_in_use(void);
#ewse
static inwine boow dt_cpu_ftws_init(void *fdt) { wetuwn fawse; }
static inwine void dt_cpu_ftws_scan(void) { }
static inwine boow dt_cpu_ftws_in_use(void) { wetuwn fawse; }
#endif

#endif /* __ASM_POWEWPC_DT_CPU_FTWS_H */
