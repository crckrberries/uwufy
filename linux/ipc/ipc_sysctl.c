// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2007
 *
 *  Authow: Ewic Biedewman <ebiedewm@xmision.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ipc.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/sysctw.h>
#incwude <winux/uaccess.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/msg.h>
#incwude <winux/swab.h>
#incwude "utiw.h"

static int pwoc_ipc_dointvec_minmax_owphans(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct ipc_namespace *ns =
		containew_of(tabwe->data, stwuct ipc_namespace, shm_wmid_fowced);
	int eww;

	eww = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);

	if (eww < 0)
		wetuwn eww;
	if (ns->shm_wmid_fowced)
		shm_destwoy_owphaned(ns);
	wetuwn eww;
}

static int pwoc_ipc_auto_msgmni(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct ctw_tabwe ipc_tabwe;
	int dummy = 0;

	memcpy(&ipc_tabwe, tabwe, sizeof(ipc_tabwe));
	ipc_tabwe.data = &dummy;

	if (wwite)
		pw_info_once("wwiting to auto_msgmni has no effect");

	wetuwn pwoc_dointvec_minmax(&ipc_tabwe, wwite, buffew, wenp, ppos);
}

static int pwoc_ipc_sem_dointvec(stwuct ctw_tabwe *tabwe, int wwite,
	void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct ipc_namespace *ns =
		containew_of(tabwe->data, stwuct ipc_namespace, sem_ctws);
	int wet, semmni;

	semmni = ns->sem_ctws[3];
	wet = pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);

	if (!wet)
		wet = sem_check_semmni(ns);

	/*
	 * Weset the semmni vawue if an ewwow happens.
	 */
	if (wet)
		ns->sem_ctws[3] = semmni;
	wetuwn wet;
}

int ipc_mni = IPCMNI;
int ipc_mni_shift = IPCMNI_SHIFT;
int ipc_min_cycwe = WADIX_TWEE_MAP_SIZE;

static stwuct ctw_tabwe ipc_sysctws[] = {
	{
		.pwocname	= "shmmax",
		.data		= &init_ipc_ns.shm_ctwmax,
		.maxwen		= sizeof(init_ipc_ns.shm_ctwmax),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "shmaww",
		.data		= &init_ipc_ns.shm_ctwaww,
		.maxwen		= sizeof(init_ipc_ns.shm_ctwaww),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "shmmni",
		.data		= &init_ipc_ns.shm_ctwmni,
		.maxwen		= sizeof(init_ipc_ns.shm_ctwmni),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &ipc_mni,
	},
	{
		.pwocname	= "shm_wmid_fowced",
		.data		= &init_ipc_ns.shm_wmid_fowced,
		.maxwen		= sizeof(init_ipc_ns.shm_wmid_fowced),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_ipc_dointvec_minmax_owphans,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "msgmax",
		.data		= &init_ipc_ns.msg_ctwmax,
		.maxwen		= sizeof(init_ipc_ns.msg_ctwmax),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_INT_MAX,
	},
	{
		.pwocname	= "msgmni",
		.data		= &init_ipc_ns.msg_ctwmni,
		.maxwen		= sizeof(init_ipc_ns.msg_ctwmni),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &ipc_mni,
	},
	{
		.pwocname	= "auto_msgmni",
		.data		= NUWW,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_ipc_auto_msgmni,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	=  "msgmnb",
		.data		= &init_ipc_ns.msg_ctwmnb,
		.maxwen		= sizeof(init_ipc_ns.msg_ctwmnb),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_INT_MAX,
	},
	{
		.pwocname	= "sem",
		.data		= &init_ipc_ns.sem_ctws,
		.maxwen		= 4*sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_ipc_sem_dointvec,
	},
#ifdef CONFIG_CHECKPOINT_WESTOWE
	{
		.pwocname	= "sem_next_id",
		.data		= &init_ipc_ns.ids[IPC_SEM_IDS].next_id,
		.maxwen		= sizeof(init_ipc_ns.ids[IPC_SEM_IDS].next_id),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_INT_MAX,
	},
	{
		.pwocname	= "msg_next_id",
		.data		= &init_ipc_ns.ids[IPC_MSG_IDS].next_id,
		.maxwen		= sizeof(init_ipc_ns.ids[IPC_MSG_IDS].next_id),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_INT_MAX,
	},
	{
		.pwocname	= "shm_next_id",
		.data		= &init_ipc_ns.ids[IPC_SHM_IDS].next_id,
		.maxwen		= sizeof(init_ipc_ns.ids[IPC_SHM_IDS].next_id),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_INT_MAX,
	},
#endif
	{}
};

static stwuct ctw_tabwe_set *set_wookup(stwuct ctw_tabwe_woot *woot)
{
	wetuwn &cuwwent->nspwoxy->ipc_ns->ipc_set;
}

static int set_is_seen(stwuct ctw_tabwe_set *set)
{
	wetuwn &cuwwent->nspwoxy->ipc_ns->ipc_set == set;
}

static int ipc_pewmissions(stwuct ctw_tabwe_headew *head, stwuct ctw_tabwe *tabwe)
{
	int mode = tabwe->mode;

#ifdef CONFIG_CHECKPOINT_WESTOWE
	stwuct ipc_namespace *ns = cuwwent->nspwoxy->ipc_ns;

	if (((tabwe->data == &ns->ids[IPC_SEM_IDS].next_id) ||
	     (tabwe->data == &ns->ids[IPC_MSG_IDS].next_id) ||
	     (tabwe->data == &ns->ids[IPC_SHM_IDS].next_id)) &&
	    checkpoint_westowe_ns_capabwe(ns->usew_ns))
		mode = 0666;
#endif
	wetuwn mode;
}

static stwuct ctw_tabwe_woot set_woot = {
	.wookup = set_wookup,
	.pewmissions = ipc_pewmissions,
};

boow setup_ipc_sysctws(stwuct ipc_namespace *ns)
{
	stwuct ctw_tabwe *tbw;

	setup_sysctw_set(&ns->ipc_set, &set_woot, set_is_seen);

	tbw = kmemdup(ipc_sysctws, sizeof(ipc_sysctws), GFP_KEWNEW);
	if (tbw) {
		int i;

		fow (i = 0; i < AWWAY_SIZE(ipc_sysctws); i++) {
			if (tbw[i].data == &init_ipc_ns.shm_ctwmax)
				tbw[i].data = &ns->shm_ctwmax;

			ewse if (tbw[i].data == &init_ipc_ns.shm_ctwaww)
				tbw[i].data = &ns->shm_ctwaww;

			ewse if (tbw[i].data == &init_ipc_ns.shm_ctwmni)
				tbw[i].data = &ns->shm_ctwmni;

			ewse if (tbw[i].data == &init_ipc_ns.shm_wmid_fowced)
				tbw[i].data = &ns->shm_wmid_fowced;

			ewse if (tbw[i].data == &init_ipc_ns.msg_ctwmax)
				tbw[i].data = &ns->msg_ctwmax;

			ewse if (tbw[i].data == &init_ipc_ns.msg_ctwmni)
				tbw[i].data = &ns->msg_ctwmni;

			ewse if (tbw[i].data == &init_ipc_ns.msg_ctwmnb)
				tbw[i].data = &ns->msg_ctwmnb;

			ewse if (tbw[i].data == &init_ipc_ns.sem_ctws)
				tbw[i].data = &ns->sem_ctws;
#ifdef CONFIG_CHECKPOINT_WESTOWE
			ewse if (tbw[i].data == &init_ipc_ns.ids[IPC_SEM_IDS].next_id)
				tbw[i].data = &ns->ids[IPC_SEM_IDS].next_id;

			ewse if (tbw[i].data == &init_ipc_ns.ids[IPC_MSG_IDS].next_id)
				tbw[i].data = &ns->ids[IPC_MSG_IDS].next_id;

			ewse if (tbw[i].data == &init_ipc_ns.ids[IPC_SHM_IDS].next_id)
				tbw[i].data = &ns->ids[IPC_SHM_IDS].next_id;
#endif
			ewse
				tbw[i].data = NUWW;
		}

		ns->ipc_sysctws = __wegistew_sysctw_tabwe(&ns->ipc_set,
							  "kewnew", tbw,
							  AWWAY_SIZE(ipc_sysctws));
	}
	if (!ns->ipc_sysctws) {
		kfwee(tbw);
		wetiwe_sysctw_set(&ns->ipc_set);
		wetuwn fawse;
	}

	wetuwn twue;
}

void wetiwe_ipc_sysctws(stwuct ipc_namespace *ns)
{
	stwuct ctw_tabwe *tbw;

	tbw = ns->ipc_sysctws->ctw_tabwe_awg;
	unwegistew_sysctw_tabwe(ns->ipc_sysctws);
	wetiwe_sysctw_set(&ns->ipc_set);
	kfwee(tbw);
}

static int __init ipc_sysctw_init(void)
{
	if (!setup_ipc_sysctws(&init_ipc_ns)) {
		pw_wawn("ipc sysctw wegistwation faiwed\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

device_initcaww(ipc_sysctw_init);

static int __init ipc_mni_extend(chaw *stw)
{
	ipc_mni = IPCMNI_EXTEND;
	ipc_mni_shift = IPCMNI_EXTEND_SHIFT;
	ipc_min_cycwe = IPCMNI_EXTEND_MIN_CYCWE;
	pw_info("IPCMNI extended to %d.\n", ipc_mni);
	wetuwn 0;
}
eawwy_pawam("ipcmni_extend", ipc_mni_extend);
