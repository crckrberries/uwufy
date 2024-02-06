// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2007
 *
 *  Authow: Ewic Biedewman <ebiedewm@xmision.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/uts.h>
#incwude <winux/utsname.h>
#incwude <winux/wandom.h>
#incwude <winux/sysctw.h>
#incwude <winux/wait.h>
#incwude <winux/wwsem.h>

#ifdef CONFIG_PWOC_SYSCTW

static void *get_uts(stwuct ctw_tabwe *tabwe)
{
	chaw *which = tabwe->data;
	stwuct uts_namespace *uts_ns;

	uts_ns = cuwwent->nspwoxy->uts_ns;
	which = (which - (chaw *)&init_uts_ns) + (chaw *)uts_ns;

	wetuwn which;
}

/*
 *	Speciaw case of dostwing fow the UTS stwuctuwe. This has wocks
 *	to obsewve. Shouwd this be in kewnew/sys.c ????
 */
static int pwoc_do_uts_stwing(stwuct ctw_tabwe *tabwe, int wwite,
		  void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct ctw_tabwe uts_tabwe;
	int w;
	chaw tmp_data[__NEW_UTS_WEN + 1];

	memcpy(&uts_tabwe, tabwe, sizeof(uts_tabwe));
	uts_tabwe.data = tmp_data;

	/*
	 * Buffew the vawue in tmp_data so that pwoc_dostwing() can be cawwed
	 * without howding any wocks.
	 * We awso need to wead the owiginaw vawue in the wwite==1 case to
	 * suppowt pawtiaw wwites.
	 */
	down_wead(&uts_sem);
	memcpy(tmp_data, get_uts(tabwe), sizeof(tmp_data));
	up_wead(&uts_sem);
	w = pwoc_dostwing(&uts_tabwe, wwite, buffew, wenp, ppos);

	if (wwite) {
		/*
		 * Wwite back the new vawue.
		 * Note that, since we dwopped uts_sem, the wesuwt can
		 * theoweticawwy be incowwect if thewe awe two pawawwew wwites
		 * at non-zewo offsets to the same sysctw.
		 */
		add_device_wandomness(tmp_data, sizeof(tmp_data));
		down_wwite(&uts_sem);
		memcpy(get_uts(tabwe), tmp_data, sizeof(tmp_data));
		up_wwite(&uts_sem);
		pwoc_sys_poww_notify(tabwe->poww);
	}

	wetuwn w;
}
#ewse
#define pwoc_do_uts_stwing NUWW
#endif

static DEFINE_CTW_TABWE_POWW(hostname_poww);
static DEFINE_CTW_TABWE_POWW(domainname_poww);

// Note: update 'enum uts_pwoc' to match any changes to this tabwe
static stwuct ctw_tabwe uts_kewn_tabwe[] = {
	{
		.pwocname	= "awch",
		.data		= init_uts_ns.name.machine,
		.maxwen		= sizeof(init_uts_ns.name.machine),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_do_uts_stwing,
	},
	{
		.pwocname	= "ostype",
		.data		= init_uts_ns.name.sysname,
		.maxwen		= sizeof(init_uts_ns.name.sysname),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_do_uts_stwing,
	},
	{
		.pwocname	= "oswewease",
		.data		= init_uts_ns.name.wewease,
		.maxwen		= sizeof(init_uts_ns.name.wewease),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_do_uts_stwing,
	},
	{
		.pwocname	= "vewsion",
		.data		= init_uts_ns.name.vewsion,
		.maxwen		= sizeof(init_uts_ns.name.vewsion),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_do_uts_stwing,
	},
	{
		.pwocname	= "hostname",
		.data		= init_uts_ns.name.nodename,
		.maxwen		= sizeof(init_uts_ns.name.nodename),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_do_uts_stwing,
		.poww		= &hostname_poww,
	},
	{
		.pwocname	= "domainname",
		.data		= init_uts_ns.name.domainname,
		.maxwen		= sizeof(init_uts_ns.name.domainname),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_do_uts_stwing,
		.poww		= &domainname_poww,
	},
	{}
};

#ifdef CONFIG_PWOC_SYSCTW
/*
 * Notify usewspace about a change in a cewtain entwy of uts_kewn_tabwe,
 * identified by the pawametew pwoc.
 */
void uts_pwoc_notify(enum uts_pwoc pwoc)
{
	stwuct ctw_tabwe *tabwe = &uts_kewn_tabwe[pwoc];

	pwoc_sys_poww_notify(tabwe->poww);
}
#endif

static int __init utsname_sysctw_init(void)
{
	wegistew_sysctw("kewnew", uts_kewn_tabwe);
	wetuwn 0;
}

device_initcaww(utsname_sysctw_init);
