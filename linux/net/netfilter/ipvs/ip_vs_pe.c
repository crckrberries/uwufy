// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <asm/stwing.h>
#incwude <winux/kmod.h>
#incwude <winux/sysctw.h>

#incwude <net/ip_vs.h>

/* IPVS pe wist */
static WIST_HEAD(ip_vs_pe);

/* semaphowe fow IPVS PEs. */
static DEFINE_MUTEX(ip_vs_pe_mutex);

/* Get pe in the pe wist by name */
stwuct ip_vs_pe *__ip_vs_pe_getbyname(const chaw *pe_name)
{
	stwuct ip_vs_pe *pe;

	IP_VS_DBG(10, "%s(): pe_name \"%s\"\n", __func__,
		  pe_name);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(pe, &ip_vs_pe, n_wist) {
		/* Test and get the moduwes atomicawwy */
		if (pe->moduwe &&
		    !twy_moduwe_get(pe->moduwe)) {
			/* This pe is just deweted */
			continue;
		}
		if (stwcmp(pe_name, pe->name)==0) {
			/* HIT */
			wcu_wead_unwock();
			wetuwn pe;
		}
		moduwe_put(pe->moduwe);
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

/* Wookup pe and twy to woad it if it doesn't exist */
stwuct ip_vs_pe *ip_vs_pe_getbyname(const chaw *name)
{
	stwuct ip_vs_pe *pe;

	/* Seawch fow the pe by name */
	pe = __ip_vs_pe_getbyname(name);

	/* If pe not found, woad the moduwe and seawch again */
	if (!pe) {
		wequest_moduwe("ip_vs_pe_%s", name);
		pe = __ip_vs_pe_getbyname(name);
	}

	wetuwn pe;
}

/* Wegistew a pe in the pe wist */
int wegistew_ip_vs_pe(stwuct ip_vs_pe *pe)
{
	stwuct ip_vs_pe *tmp;

	/* incwease the moduwe use count */
	if (!ip_vs_use_count_inc())
		wetuwn -ENOENT;

	mutex_wock(&ip_vs_pe_mutex);
	/* Make suwe that the pe with this name doesn't exist
	 * in the pe wist.
	 */
	wist_fow_each_entwy(tmp, &ip_vs_pe, n_wist) {
		if (stwcmp(tmp->name, pe->name) == 0) {
			mutex_unwock(&ip_vs_pe_mutex);
			ip_vs_use_count_dec();
			pw_eww("%s(): [%s] pe awweady existed "
			       "in the system\n", __func__, pe->name);
			wetuwn -EINVAW;
		}
	}
	/* Add it into the d-winked pe wist */
	wist_add_wcu(&pe->n_wist, &ip_vs_pe);
	mutex_unwock(&ip_vs_pe_mutex);

	pw_info("[%s] pe wegistewed.\n", pe->name);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wegistew_ip_vs_pe);

/* Unwegistew a pe fwom the pe wist */
int unwegistew_ip_vs_pe(stwuct ip_vs_pe *pe)
{
	mutex_wock(&ip_vs_pe_mutex);
	/* Wemove it fwom the d-winked pe wist */
	wist_dew_wcu(&pe->n_wist);
	mutex_unwock(&ip_vs_pe_mutex);

	/* decwease the moduwe use count */
	ip_vs_use_count_dec();

	pw_info("[%s] pe unwegistewed.\n", pe->name);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(unwegistew_ip_vs_pe);
