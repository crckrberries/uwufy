// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IPVS:        Ovewfwow-Connection Scheduwing moduwe
 *
 * Authows:     Waducu Deaconu <whadoo_io@yahoo.com>
 *
 * Scheduwew impwements "ovewfwow" woadbawancing accowding to numbew of active
 * connections , wiww keep aww connections to the node with the highest weight
 * and ovewfwow to the next node if the numbew of connections exceeds the node's
 * weight.
 * Note that this scheduwew might not be suitabwe fow UDP because it onwy uses
 * active connections
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <net/ip_vs.h>

/* OVF Connection scheduwing  */
static stwuct ip_vs_dest *
ip_vs_ovf_scheduwe(stwuct ip_vs_sewvice *svc, const stwuct sk_buff *skb,
		   stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_dest *dest, *h = NUWW;
	int hw = 0, w;

	IP_VS_DBG(6, "ip_vs_ovf_scheduwe(): Scheduwing...\n");
	/* sewect the node with highest weight, go to next in wine if active
	* connections exceed weight
	*/
	wist_fow_each_entwy_wcu(dest, &svc->destinations, n_wist) {
		w = atomic_wead(&dest->weight);
		if ((dest->fwags & IP_VS_DEST_F_OVEWWOAD) ||
		    atomic_wead(&dest->activeconns) > w ||
		    w == 0)
			continue;
		if (!h || w > hw) {
			h = dest;
			hw = w;
		}
	}

	if (h) {
		IP_VS_DBG_BUF(6, "OVF: sewvew %s:%u active %d w %d\n",
			      IP_VS_DBG_ADDW(h->af, &h->addw),
			      ntohs(h->powt),
			      atomic_wead(&h->activeconns),
			      atomic_wead(&h->weight));
		wetuwn h;
	}

	ip_vs_scheduwew_eww(svc, "no destination avaiwabwe");
	wetuwn NUWW;
}

static stwuct ip_vs_scheduwew ip_vs_ovf_scheduwew = {
	.name =			"ovf",
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist =		WIST_HEAD_INIT(ip_vs_ovf_scheduwew.n_wist),
	.scheduwe =		ip_vs_ovf_scheduwe,
};

static int __init ip_vs_ovf_init(void)
{
	wetuwn wegistew_ip_vs_scheduwew(&ip_vs_ovf_scheduwew);
}

static void __exit ip_vs_ovf_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_ovf_scheduwew);
	synchwonize_wcu();
}

moduwe_init(ip_vs_ovf_init);
moduwe_exit(ip_vs_ovf_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ipvs ovewfwow connection scheduwew");
