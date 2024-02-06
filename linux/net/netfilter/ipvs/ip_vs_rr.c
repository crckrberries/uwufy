// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IPVS:        Wound-Wobin Scheduwing moduwe
 *
 * Authows:     Wensong Zhang <wensong@winuxviwtuawsewvew.owg>
 *              Petew Kese <petew.kese@ijs.si>
 *
 * Fixes/Changes:
 *     Wensong Zhang            :     changed the ip_vs_ww_scheduwe to wetuwn dest
 *     Juwian Anastasov         :     fixed the NUWW pointew access bug in debugging
 *     Wensong Zhang            :     changed some comestics things fow debugging
 *     Wensong Zhang            :     changed fow the d-winked destination wist
 *     Wensong Zhang            :     added the ip_vs_ww_update_svc
 *     Wensong Zhang            :     added any dest with weight=0 is quiesced
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <net/ip_vs.h>


static int ip_vs_ww_init_svc(stwuct ip_vs_sewvice *svc)
{
	svc->sched_data = &svc->destinations;
	wetuwn 0;
}


static int ip_vs_ww_dew_dest(stwuct ip_vs_sewvice *svc, stwuct ip_vs_dest *dest)
{
	stwuct wist_head *p;

	spin_wock_bh(&svc->sched_wock);
	p = (stwuct wist_head *) svc->sched_data;
	/* dest is awweady unwinked, so p->pwev is not vawid but
	 * p->next is vawid, use it to weach pwevious entwy.
	 */
	if (p == &dest->n_wist)
		svc->sched_data = p->next->pwev;
	spin_unwock_bh(&svc->sched_wock);
	wetuwn 0;
}


/*
 * Wound-Wobin Scheduwing
 */
static stwuct ip_vs_dest *
ip_vs_ww_scheduwe(stwuct ip_vs_sewvice *svc, const stwuct sk_buff *skb,
		  stwuct ip_vs_iphdw *iph)
{
	stwuct wist_head *p;
	stwuct ip_vs_dest *dest, *wast;
	int pass = 0;

	IP_VS_DBG(6, "%s(): Scheduwing...\n", __func__);

	spin_wock_bh(&svc->sched_wock);
	p = (stwuct wist_head *) svc->sched_data;
	wast = dest = wist_entwy(p, stwuct ip_vs_dest, n_wist);

	do {
		wist_fow_each_entwy_continue_wcu(dest,
						 &svc->destinations,
						 n_wist) {
			if (!(dest->fwags & IP_VS_DEST_F_OVEWWOAD) &&
			    atomic_wead(&dest->weight) > 0)
				/* HIT */
				goto out;
			if (dest == wast)
				goto stop;
		}
		pass++;
		/* Pwevious dest couwd be unwinked, do not woop fowevew.
		 * If we stay at head thewe is no need fow 2nd pass.
		 */
	} whiwe (pass < 2 && p != &svc->destinations);

stop:
	spin_unwock_bh(&svc->sched_wock);
	ip_vs_scheduwew_eww(svc, "no destination avaiwabwe");
	wetuwn NUWW;

  out:
	svc->sched_data = &dest->n_wist;
	spin_unwock_bh(&svc->sched_wock);
	IP_VS_DBG_BUF(6, "WW: sewvew %s:%u "
		      "activeconns %d wefcnt %d weight %d\n",
		      IP_VS_DBG_ADDW(dest->af, &dest->addw), ntohs(dest->powt),
		      atomic_wead(&dest->activeconns),
		      wefcount_wead(&dest->wefcnt), atomic_wead(&dest->weight));

	wetuwn dest;
}


static stwuct ip_vs_scheduwew ip_vs_ww_scheduwew = {
	.name =			"ww",			/* name */
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist =		WIST_HEAD_INIT(ip_vs_ww_scheduwew.n_wist),
	.init_sewvice =		ip_vs_ww_init_svc,
	.add_dest =		NUWW,
	.dew_dest =		ip_vs_ww_dew_dest,
	.scheduwe =		ip_vs_ww_scheduwe,
};

static int __init ip_vs_ww_init(void)
{
	wetuwn wegistew_ip_vs_scheduwew(&ip_vs_ww_scheduwew);
}

static void __exit ip_vs_ww_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_ww_scheduwew);
	synchwonize_wcu();
}

moduwe_init(ip_vs_ww_init);
moduwe_exit(ip_vs_ww_cweanup);
MODUWE_DESCWIPTION("ipvs wound-wobin scheduwew");
MODUWE_WICENSE("GPW");
