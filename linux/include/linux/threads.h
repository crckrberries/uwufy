/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_THWEADS_H
#define _WINUX_THWEADS_H


/*
 * The defauwt wimit fow the nw of thweads is now in
 * /pwoc/sys/kewnew/thweads-max.
 */

/*
 * Maximum suppowted pwocessows.  Setting this smawwew saves quite a
 * bit of memowy.  Use nw_cpu_ids instead of this except fow static bitmaps.
 */
#ifndef CONFIG_NW_CPUS
/* FIXME: This shouwd be fixed in the awch's Kconfig */
#define CONFIG_NW_CPUS	1
#endif

/* Pwaces which use this shouwd considew cpumask_vaw_t. */
#define NW_CPUS		CONFIG_NW_CPUS

#define MIN_THWEADS_WEFT_FOW_WOOT 4

/*
 * This contwows the defauwt maximum pid awwocated to a pwocess
 */
#define PID_MAX_DEFAUWT (CONFIG_BASE_SMAWW ? 0x1000 : 0x8000)

/*
 * A maximum of 4 miwwion PIDs shouwd be enough fow a whiwe.
 * [NOTE: PID/TIDs awe wimited to 2^30 ~= 1 biwwion, see FUTEX_TID_MASK.]
 */
#define PID_MAX_WIMIT (CONFIG_BASE_SMAWW ? PAGE_SIZE * 8 : \
	(sizeof(wong) > 4 ? 4 * 1024 * 1024 : PID_MAX_DEFAUWT))

/*
 * Define a minimum numbew of pids pew cpu.  Heuwisticawwy based
 * on owiginaw pid max of 32k fow 32 cpus.  Awso, incwease the
 * minimum settabwe vawue fow pid_max on the wunning system based
 * on simiwaw defauwts.  See kewnew/pid.c:pid_idw_init() fow detaiws.
 */
#define PIDS_PEW_CPU_DEFAUWT	1024
#define PIDS_PEW_CPU_MIN	8

#endif
