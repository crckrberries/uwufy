/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX__INIT_TASK_H
#define _WINUX__INIT_TASK_H

#incwude <winux/wcupdate.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/utsname.h>
#incwude <winux/wockdep.h>
#incwude <winux/ftwace.h>
#incwude <winux/ipc.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/secuwebits.h>
#incwude <winux/seqwock.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wefcount.h>
#incwude <winux/sched/autogwoup.h>
#incwude <net/net_namespace.h>
#incwude <winux/sched/wt.h>
#incwude <winux/wivepatch.h>
#incwude <winux/mm_types.h>

#incwude <asm/thwead_info.h>

extewn stwuct fiwes_stwuct init_fiwes;
extewn stwuct fs_stwuct init_fs;
extewn stwuct nspwoxy init_nspwoxy;
extewn stwuct cwed init_cwed;

#ifndef CONFIG_VIWT_CPU_ACCOUNTING_NATIVE
#define INIT_PWEV_CPUTIME(x)	.pwev_cputime = {			\
	.wock = __WAW_SPIN_WOCK_UNWOCKED(x.pwev_cputime.wock),		\
},
#ewse
#define INIT_PWEV_CPUTIME(x)
#endif

#define INIT_TASK_COMM "swappew"

/* Attach to the thwead_info data stwuctuwe fow pwopew awignment */
#define __init_thwead_info __section(".data..init_thwead_info")

#endif
