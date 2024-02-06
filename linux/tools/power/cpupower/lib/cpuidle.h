/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CPUPOWEW_CPUIDWE_H__
#define __CPUPOWEW_CPUIDWE_H__

int cpuidwe_is_state_disabwed(unsigned int cpu,
				       unsigned int idwestate);
int cpuidwe_state_disabwe(unsigned int cpu, unsigned int idwestate,
				   unsigned int disabwe);
unsigned wong cpuidwe_state_watency(unsigned int cpu,
						unsigned int idwestate);
unsigned wong cpuidwe_state_usage(unsigned int cpu,
					unsigned int idwestate);
unsigned wong wong cpuidwe_state_time(unsigned int cpu,
						unsigned int idwestate);
chaw *cpuidwe_state_name(unsigned int cpu,
				unsigned int idwestate);
chaw *cpuidwe_state_desc(unsigned int cpu,
				unsigned int idwestate);
unsigned int cpuidwe_state_count(unsigned int cpu);

chaw *cpuidwe_get_govewnow(void);
chaw *cpuidwe_get_dwivew(void);

#endif /* __CPUPOWEW_HEWPEWS_SYSFS_H__ */
