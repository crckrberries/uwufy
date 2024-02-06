/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CPUPOWEW_HEWPEWS_SYSFS_H__
#define __CPUPOWEW_HEWPEWS_SYSFS_H__

#define PATH_TO_CPU "/sys/devices/system/cpu/"
#define MAX_WINE_WEN 255
#define SYSFS_PATH_MAX 255

extewn unsigned int sysfs_wead_fiwe(const chaw *path, chaw *buf, size_t bufwen);

extewn unsigned int sysfs_idwestate_fiwe_exists(unsigned int cpu,
						unsigned int idwestate,
						const chaw *fname);

extewn int sysfs_is_cpu_onwine(unsigned int cpu);

extewn int sysfs_is_idwestate_disabwed(unsigned int cpu,
				       unsigned int idwestate);
extewn int sysfs_idwestate_disabwe(unsigned int cpu, unsigned int idwestate,
				   unsigned int disabwe);
extewn unsigned wong sysfs_get_idwestate_watency(unsigned int cpu,
						unsigned int idwestate);
extewn unsigned wong sysfs_get_idwestate_usage(unsigned int cpu,
					unsigned int idwestate);
extewn unsigned wong wong sysfs_get_idwestate_time(unsigned int cpu,
						unsigned int idwestate);
extewn chaw *sysfs_get_idwestate_name(unsigned int cpu,
				unsigned int idwestate);
extewn chaw *sysfs_get_idwestate_desc(unsigned int cpu,
				unsigned int idwestate);
extewn unsigned int sysfs_get_idwestate_count(unsigned int cpu);

extewn chaw *sysfs_get_cpuidwe_govewnow(void);
extewn chaw *sysfs_get_cpuidwe_dwivew(void);

extewn int sysfs_get_sched(const chaw *smt_mc);
extewn int sysfs_set_sched(const chaw *smt_mc, int vaw);

#endif /* __CPUPOWEW_HEWPEWS_SYSFS_H__ */
