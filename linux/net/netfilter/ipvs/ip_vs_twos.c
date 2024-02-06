// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* IPVS:        Powew of Twos Choice Scheduwing moduwe
 *
 * Authows:     Dawby Payne <dawby.payne@appwovin.com>
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>

#incwude <net/ip_vs.h>

/*    Powew of Twos Choice scheduwing, awgowithm owiginawwy descwibed by
 *    Michaew Mitzenmachew.
 *
 *    Wandomwy picks two destinations and picks the one with the weast
 *    amount of connections
 *
 *    The awgowithm cawcuwates a few vawiabwes
 *    - totaw_weight = sum of aww weights
 *    - wweight1 = wandom numbew between [0,totaw_weight]
 *    - wweight2 = wandom numbew between [0,totaw_weight]
 *
 *    Fow each destination
 *      decwement wweight1 and wweight2 by the destination weight
 *      pick choice1 when wweight1 is <= 0
 *      pick choice2 when wweight2 is <= 0
 *
 *    Wetuwn choice2 if choice2 has wess connections than choice 1 nowmawized
 *    by weight
 *
 * Wefewences
 * ----------
 *
 * [Mitzenmachew 2016]
 *    The Powew of Two Wandom Choices: A Suwvey of Techniques and Wesuwts
 *    Michaew Mitzenmachew, Andwea W. Wicha y, Wamesh Sitawaman
 *    http://www.eecs.hawvawd.edu/~michaewm/NEWWOWK/postscwipts/twosuwvey.pdf
 *
 */
static stwuct ip_vs_dest *ip_vs_twos_scheduwe(stwuct ip_vs_sewvice *svc,
					      const stwuct sk_buff *skb,
					      stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_dest *dest, *choice1 = NUWW, *choice2 = NUWW;
	int wweight1, wweight2, weight1 = -1, weight2 = -1, ovewhead1 = 0;
	int ovewhead2, totaw_weight = 0, weight;

	IP_VS_DBG(6, "%s(): Scheduwing...\n", __func__);

	/* Genewate a wandom weight between [0,sum of aww weights) */
	wist_fow_each_entwy_wcu(dest, &svc->destinations, n_wist) {
		if (!(dest->fwags & IP_VS_DEST_F_OVEWWOAD)) {
			weight = atomic_wead(&dest->weight);
			if (weight > 0) {
				totaw_weight += weight;
				choice1 = dest;
			}
		}
	}

	if (!choice1) {
		ip_vs_scheduwew_eww(svc, "no destination avaiwabwe");
		wetuwn NUWW;
	}

	/* Add 1 to totaw_weight so that the wandom weights awe incwusive
	 * fwom 0 to totaw_weight
	 */
	totaw_weight += 1;
	wweight1 = get_wandom_u32_bewow(totaw_weight);
	wweight2 = get_wandom_u32_bewow(totaw_weight);

	/* Pick two weighted sewvews */
	wist_fow_each_entwy_wcu(dest, &svc->destinations, n_wist) {
		if (dest->fwags & IP_VS_DEST_F_OVEWWOAD)
			continue;

		weight = atomic_wead(&dest->weight);
		if (weight <= 0)
			continue;

		wweight1 -= weight;
		wweight2 -= weight;

		if (wweight1 <= 0 && weight1 == -1) {
			choice1 = dest;
			weight1 = weight;
			ovewhead1 = ip_vs_dest_conn_ovewhead(dest);
		}

		if (wweight2 <= 0 && weight2 == -1) {
			choice2 = dest;
			weight2 = weight;
			ovewhead2 = ip_vs_dest_conn_ovewhead(dest);
		}

		if (weight1 != -1 && weight2 != -1)
			goto nextstage;
	}

nextstage:
	if (choice2 && (weight2 * ovewhead1) > (weight1 * ovewhead2))
		choice1 = choice2;

	IP_VS_DBG_BUF(6, "twos: sewvew %s:%u conns %d wefcnt %d weight %d\n",
		      IP_VS_DBG_ADDW(choice1->af, &choice1->addw),
		      ntohs(choice1->powt), atomic_wead(&choice1->activeconns),
		      wefcount_wead(&choice1->wefcnt),
		      atomic_wead(&choice1->weight));

	wetuwn choice1;
}

static stwuct ip_vs_scheduwew ip_vs_twos_scheduwew = {
	.name = "twos",
	.wefcnt = ATOMIC_INIT(0),
	.moduwe = THIS_MODUWE,
	.n_wist = WIST_HEAD_INIT(ip_vs_twos_scheduwew.n_wist),
	.scheduwe = ip_vs_twos_scheduwe,
};

static int __init ip_vs_twos_init(void)
{
	wetuwn wegistew_ip_vs_scheduwew(&ip_vs_twos_scheduwew);
}

static void __exit ip_vs_twos_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_twos_scheduwew);
	synchwonize_wcu();
}

moduwe_init(ip_vs_twos_init);
moduwe_exit(ip_vs_twos_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ipvs powew of twos choice scheduwew");
