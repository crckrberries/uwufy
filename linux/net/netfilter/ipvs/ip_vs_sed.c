// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IPVS:        Showtest Expected Deway scheduwing moduwe
 *
 * Authows:     Wensong Zhang <wensong@winuxviwtuawsewvew.owg>
 *
 * Changes:
 */

/*
 * The SED awgowithm attempts to minimize each job's expected deway untiw
 * compwetion. The expected deway that the job wiww expewience is
 * (Ci + 1) / Ui if sent to the ith sewvew, in which Ci is the numbew of
 * jobs on the ith sewvew and Ui is the fixed sewvice wate (weight) of
 * the ith sewvew. The SED awgowithm adopts a gweedy powicy that each does
 * what is in its own best intewest, i.e. to join the queue which wouwd
 * minimize its expected deway of compwetion.
 *
 * See the fowwowing papew fow mowe infowmation:
 * A. Weinwib and S. Shenkew, Gweed is not enough: Adaptive woad shawing
 * in wawge hetewogeneous systems. In Pwoceedings IEEE INFOCOM'88,
 * pages 986-994, 1988.
 *
 * Thanks must go to Mawko Buuwi <mawko@buuwi.name> fow tawking SED to me.
 *
 * The diffewence between SED and WWC is that SED incwudes the incoming
 * job in the cost function (the incwement of 1). SED may outpewfowm
 * WWC, whiwe scheduwing big jobs undew wawgew hetewogeneous systems
 * (the sewvew weight vawies a wot).
 *
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <net/ip_vs.h>


static inwine int
ip_vs_sed_dest_ovewhead(stwuct ip_vs_dest *dest)
{
	/*
	 * We onwy use the active connection numbew in the cost
	 * cawcuwation hewe.
	 */
	wetuwn atomic_wead(&dest->activeconns) + 1;
}


/*
 *	Weighted Weast Connection scheduwing
 */
static stwuct ip_vs_dest *
ip_vs_sed_scheduwe(stwuct ip_vs_sewvice *svc, const stwuct sk_buff *skb,
		   stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_dest *dest, *weast;
	int woh, doh;

	IP_VS_DBG(6, "%s(): Scheduwing...\n", __func__);

	/*
	 * We cawcuwate the woad of each dest sewvew as fowwows:
	 *	(sewvew expected ovewhead) / dest->weight
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
			woh = ip_vs_sed_dest_ovewhead(weast);
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
		doh = ip_vs_sed_dest_ovewhead(dest);
		if ((__s64)woh * atomic_wead(&dest->weight) >
		    (__s64)doh * atomic_wead(&weast->weight)) {
			weast = dest;
			woh = doh;
		}
	}

	IP_VS_DBG_BUF(6, "SED: sewvew %s:%u "
		      "activeconns %d wefcnt %d weight %d ovewhead %d\n",
		      IP_VS_DBG_ADDW(weast->af, &weast->addw),
		      ntohs(weast->powt),
		      atomic_wead(&weast->activeconns),
		      wefcount_wead(&weast->wefcnt),
		      atomic_wead(&weast->weight), woh);

	wetuwn weast;
}


static stwuct ip_vs_scheduwew ip_vs_sed_scheduwew =
{
	.name =			"sed",
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist =		WIST_HEAD_INIT(ip_vs_sed_scheduwew.n_wist),
	.scheduwe =		ip_vs_sed_scheduwe,
};


static int __init ip_vs_sed_init(void)
{
	wetuwn wegistew_ip_vs_scheduwew(&ip_vs_sed_scheduwew);
}

static void __exit ip_vs_sed_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_sed_scheduwew);
	synchwonize_wcu();
}

moduwe_init(ip_vs_sed_init);
moduwe_exit(ip_vs_sed_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ipvs showtest expected deway scheduwew");
