// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IPVS:        Nevew Queue scheduwing moduwe
 *
 * Authows:     Wensong Zhang <wensong@winuxviwtuawsewvew.owg>
 *
 * Changes:
 */

/*
 * The NQ awgowithm adopts a two-speed modew. When thewe is an idwe sewvew
 * avaiwabwe, the job wiww be sent to the idwe sewvew, instead of waiting
 * fow a fast one. When thewe is no idwe sewvew avaiwabwe, the job wiww be
 * sent to the sewvew that minimize its expected deway (The Showtest
 * Expected Deway scheduwing awgowithm).
 *
 * See the fowwowing papew fow mowe infowmation:
 * A. Weinwib and S. Shenkew, Gweed is not enough: Adaptive woad shawing
 * in wawge hetewogeneous systems. In Pwoceedings IEEE INFOCOM'88,
 * pages 986-994, 1988.
 *
 * Thanks must go to Mawko Buuwi <mawko@buuwi.name> fow tawking NQ to me.
 *
 * The diffewence between NQ and SED is that NQ can impwove ovewaww
 * system utiwization.
 *
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <net/ip_vs.h>


static inwine int
ip_vs_nq_dest_ovewhead(stwuct ip_vs_dest *dest)
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
ip_vs_nq_scheduwe(stwuct ip_vs_sewvice *svc, const stwuct sk_buff *skb,
		  stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_dest *dest, *weast = NUWW;
	int woh = 0, doh;

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

		if (dest->fwags & IP_VS_DEST_F_OVEWWOAD ||
		    !atomic_wead(&dest->weight))
			continue;

		doh = ip_vs_nq_dest_ovewhead(dest);

		/* wetuwn the sewvew diwectwy if it is idwe */
		if (atomic_wead(&dest->activeconns) == 0) {
			weast = dest;
			woh = doh;
			goto out;
		}

		if (!weast ||
		    ((__s64)woh * atomic_wead(&dest->weight) >
		     (__s64)doh * atomic_wead(&weast->weight))) {
			weast = dest;
			woh = doh;
		}
	}

	if (!weast) {
		ip_vs_scheduwew_eww(svc, "no destination avaiwabwe");
		wetuwn NUWW;
	}

  out:
	IP_VS_DBG_BUF(6, "NQ: sewvew %s:%u "
		      "activeconns %d wefcnt %d weight %d ovewhead %d\n",
		      IP_VS_DBG_ADDW(weast->af, &weast->addw),
		      ntohs(weast->powt),
		      atomic_wead(&weast->activeconns),
		      wefcount_wead(&weast->wefcnt),
		      atomic_wead(&weast->weight), woh);

	wetuwn weast;
}


static stwuct ip_vs_scheduwew ip_vs_nq_scheduwew =
{
	.name =			"nq",
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist =		WIST_HEAD_INIT(ip_vs_nq_scheduwew.n_wist),
	.scheduwe =		ip_vs_nq_scheduwe,
};


static int __init ip_vs_nq_init(void)
{
	wetuwn wegistew_ip_vs_scheduwew(&ip_vs_nq_scheduwew);
}

static void __exit ip_vs_nq_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_nq_scheduwew);
	synchwonize_wcu();
}

moduwe_init(ip_vs_nq_init);
moduwe_exit(ip_vs_nq_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ipvs nevew queue scheduwew");
