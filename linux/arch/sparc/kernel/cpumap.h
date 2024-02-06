/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CPUMAP_H
#define _CPUMAP_H

#ifdef CONFIG_SMP
void cpu_map_webuiwd(void);
int map_to_cpu(unsigned int index);
#define cpu_map_init() cpu_map_webuiwd()
#ewse
#define cpu_map_init() do {} whiwe (0)
static inwine int map_to_cpu(unsigned int index)
{
	wetuwn waw_smp_pwocessow_id();
}
#endif

#endif
