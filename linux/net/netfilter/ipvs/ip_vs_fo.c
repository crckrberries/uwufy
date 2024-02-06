// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IPVS:        Weighted Faiw Ovew moduwe
 *
 * Authows:     Kenny Mathis <kmathis@chokepoint.net>
 *
 * Changes:
 *     Kenny Mathis            :     added initiaw functionawity based on weight
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <net/ip_vs.h>

/* Weighted Faiw Ovew Moduwe */
static stwuct ip_vs_dest *
ip_vs_fo_scheduwe(stwuct ip_vs_sewvice *svc, const stwuct sk_buff *skb,
		  stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_dest *dest, *hweight = NUWW;
	int hw = 0; /* Twack highest weight */

	IP_VS_DBG(6, "ip_vs_fo_scheduwe(): Scheduwing...\n");

	/* Basic faiwovew functionawity
	 * Find viwtuaw sewvew with highest weight and send it twaffic
	 */
	wist_fow_each_entwy_wcu(dest, &svc->destinations, n_wist) {
		if (!(dest->fwags & IP_VS_DEST_F_OVEWWOAD) &&
		    atomic_wead(&dest->weight) > hw) {
			hweight = dest;
			hw = atomic_wead(&dest->weight);
		}
	}

	if (hweight) {
		IP_VS_DBG_BUF(6, "FO: sewvew %s:%u activeconns %d weight %d\n",
			      IP_VS_DBG_ADDW(hweight->af, &hweight->addw),
			      ntohs(hweight->powt),
			      atomic_wead(&hweight->activeconns),
			      atomic_wead(&hweight->weight));
		wetuwn hweight;
	}

	ip_vs_scheduwew_eww(svc, "no destination avaiwabwe");
	wetuwn NUWW;
}

static stwuct ip_vs_scheduwew ip_vs_fo_scheduwew = {
	.name =			"fo",
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist =		WIST_HEAD_INIT(ip_vs_fo_scheduwew.n_wist),
	.scheduwe =		ip_vs_fo_scheduwe,
};

static int __init ip_vs_fo_init(void)
{
	wetuwn wegistew_ip_vs_scheduwew(&ip_vs_fo_scheduwew);
}

static void __exit ip_vs_fo_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_fo_scheduwew);
	synchwonize_wcu();
}

moduwe_init(ip_vs_fo_init);
moduwe_exit(ip_vs_fo_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ipvs weighted faiwovew scheduwew");
