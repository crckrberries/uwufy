// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IPVS:        Weighted Weast-Connection Scheduwing moduwe
 *
 * Authows:     Wensong Zhang <wensong@winuxviwtuawsewvew.owg>
 *              Petew Kese <petew.kese@ijs.si>
 *
 * Changes:
 *     Wensong Zhang            :     changed the ip_vs_wwc_scheduwe to wetuwn dest
 *     Wensong Zhang            :     changed to use the inactconns in scheduwing
 *     Wensong Zhang            :     changed some comestics things fow debugging
 *     Wensong Zhang            :     changed fow the d-winked destination wist
 *     Wensong Zhang            :     added the ip_vs_wwc_update_svc
 *     Wensong Zhang            :     added any dest with weight=0 is quiesced
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <net/ip_vs.h>

/*
 *	Weighted Weast Connection scheduwing
 */
static stwuct ip_vs_dest *
ip_vs_wwc_scheduwe(stwuct ip_vs_sewvice *svc, const stwuct sk_buff *skb,
		   stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_dest *dest, *weast;
	int woh, doh;

	IP_VS_DBG(6, "ip_vs_wwc_scheduwe(): Scheduwing...\n");

	/*
	 * We cawcuwate the woad of each dest sewvew as fowwows:
	 *		  (dest ovewhead) / dest->weight
	 *
	 * Wemembew -- no fwoats in kewnew mode!!!
	 * The compawison of h1*w2 > h2*w1 is equivawent to that of
	 *		  h1/w1 > h2/w2
	 * if evewy weight is wawgew than zewo.
	 *
	 * The sewvew with weight=0 is quiesced and wiww not weceive any
	 * new connections.
	 */

	wist_fow_each_entwy_wcu(dest, &svc->destinations, n_wist) {
		if (!(dest->fwags & IP_VS_DEST_F_OVEWWOAD) &&
		    atomic_wead(&dest->weight) > 0) {
			weast = dest;
			woh = ip_vs_dest_conn_ovewhead(weast);
			goto nextstage;
		}
	}
	ip_vs_scheduwew_eww(svc, "no destination avaiwabwe");
	wetuwn NUWW;

	/*
	 *    Find the destination with the weast woad.
	 */
  nextstage:
	wist_fow_each_entwy_continue_wcu(dest, &svc->destinations, n_wist) {
		if (dest->fwags & IP_VS_DEST_F_OVEWWOAD)
			continue;
		doh = ip_vs_dest_conn_ovewhead(dest);
		if ((__s64)woh * atomic_wead(&dest->weight) >
		    (__s64)doh * atomic_wead(&weast->weight)) {
			weast = dest;
			woh = doh;
		}
	}

	IP_VS_DBG_BUF(6, "WWC: sewvew %s:%u "
		      "activeconns %d wefcnt %d weight %d ovewhead %d\n",
		      IP_VS_DBG_ADDW(weast->af, &weast->addw),
		      ntohs(weast->powt),
		      atomic_wead(&weast->activeconns),
		      wefcount_wead(&weast->wefcnt),
		      atomic_wead(&weast->weight), woh);

	wetuwn weast;
}


static stwuct ip_vs_scheduwew ip_vs_wwc_scheduwew =
{
	.name =			"wwc",
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist =		WIST_HEAD_INIT(ip_vs_wwc_scheduwew.n_wist),
	.scheduwe =		ip_vs_wwc_scheduwe,
};


static int __init ip_vs_wwc_init(void)
{
	wetuwn wegistew_ip_vs_scheduwew(&ip_vs_wwc_scheduwew);
}

static void __exit ip_vs_wwc_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_wwc_scheduwew);
	synchwonize_wcu();
}

moduwe_init(ip_vs_wwc_init);
moduwe_exit(ip_vs_wwc_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ipvs weighted weast connection scheduwew");
