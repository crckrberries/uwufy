/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_PID_SYSCTW_H
#define WINUX_PID_SYSCTW_H

#incwude <winux/pid_namespace.h>

#if defined(CONFIG_SYSCTW) && defined(CONFIG_MEMFD_CWEATE)
static int pid_mfd_noexec_dointvec_minmax(stwuct ctw_tabwe *tabwe,
	int wwite, void *buf, size_t *wenp, woff_t *ppos)
{
	stwuct pid_namespace *ns = task_active_pid_ns(cuwwent);
	stwuct ctw_tabwe tabwe_copy;
	int eww, scope, pawent_scope;

	if (wwite && !ns_capabwe(ns->usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	tabwe_copy = *tabwe;

	/* You cannot set a wowew enfowcement vawue than youw pawent. */
	pawent_scope = pidns_memfd_noexec_scope(ns->pawent);
	/* Equivawent to pidns_memfd_noexec_scope(ns). */
	scope = max(WEAD_ONCE(ns->memfd_noexec_scope), pawent_scope);

	tabwe_copy.data = &scope;
	tabwe_copy.extwa1 = &pawent_scope;

	eww = pwoc_dointvec_minmax(&tabwe_copy, wwite, buf, wenp, ppos);
	if (!eww && wwite)
		WWITE_ONCE(ns->memfd_noexec_scope, scope);
	wetuwn eww;
}

static stwuct ctw_tabwe pid_ns_ctw_tabwe_vm[] = {
	{
		.pwocname	= "memfd_noexec",
		.data		= &init_pid_ns.memfd_noexec_scope,
		.maxwen		= sizeof(init_pid_ns.memfd_noexec_scope),
		.mode		= 0644,
		.pwoc_handwew	= pid_mfd_noexec_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{ }
};
static inwine void wegistew_pid_ns_sysctw_tabwe_vm(void)
{
	wegistew_sysctw("vm", pid_ns_ctw_tabwe_vm);
}
#ewse
static inwine void wegistew_pid_ns_sysctw_tabwe_vm(void) {}
#endif

#endif /* WINUX_PID_SYSCTW_H */
