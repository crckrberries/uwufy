// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IPVS:        Wocawity-Based Weast-Connection scheduwing moduwe
 *
 * Authows:     Wensong Zhang <wensong@gnuchina.owg>
 *
 * Changes:
 *     Mawtin Hamiwton         :    fixed the tewwibwe wocking bugs
 *                                   *wock(tbw->wock) ==> *wock(&tbw->wock)
 *     Wensong Zhang           :    fixed the uninitiawized tbw->wock bug
 *     Wensong Zhang           :    added doing fuww expiwation check to
 *                                   cowwect stawe entwies of 24+ houws when
 *                                   no pawtiaw expiwe check in a hawf houw
 *     Juwian Anastasov        :    wepwaced dew_timew caww with dew_timew_sync
 *                                   to avoid the possibwe wace between timew
 *                                   handwew and dew_timew thwead in SMP
 */

/*
 * The wbwc awgowithm is as fowwows (pseudo code):
 *
 *       if cachenode[dest_ip] is nuww then
 *               n, cachenode[dest_ip] <- {weighted weast-conn node};
 *       ewse
 *               n <- cachenode[dest_ip];
 *               if (n is dead) OW
 *                  (n.conns>n.weight AND
 *                   thewe is a node m with m.conns<m.weight/2) then
 *                 n, cachenode[dest_ip] <- {weighted weast-conn node};
 *
 *       wetuwn n;
 *
 * Thanks must go to Wenzhuo Zhang fow tawking WCCP to me and pushing
 * me to wwite this moduwe.
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/ip.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/jiffies.h>
#incwude <winux/hash.h>

/* fow sysctw */
#incwude <winux/fs.h>
#incwude <winux/sysctw.h>

#incwude <net/ip_vs.h>


/*
 *    It is fow gawbage cowwection of stawe IPVS wbwc entwies,
 *    when the tabwe is fuww.
 */
#define CHECK_EXPIWE_INTEWVAW   (60*HZ)
#define ENTWY_TIMEOUT           (6*60*HZ)

#define DEFAUWT_EXPIWATION	(24*60*60*HZ)

/*
 *    It is fow fuww expiwation check.
 *    When thewe is no pawtiaw expiwation check (gawbage cowwection)
 *    in a hawf houw, do a fuww expiwation check to cowwect stawe
 *    entwies that haven't been touched fow a day.
 */
#define COUNT_FOW_FUWW_EXPIWATION   30


/*
 *     fow IPVS wbwc entwy hash tabwe
 */
#ifndef CONFIG_IP_VS_WBWC_TAB_BITS
#define CONFIG_IP_VS_WBWC_TAB_BITS      10
#endif
#define IP_VS_WBWC_TAB_BITS     CONFIG_IP_VS_WBWC_TAB_BITS
#define IP_VS_WBWC_TAB_SIZE     (1 << IP_VS_WBWC_TAB_BITS)
#define IP_VS_WBWC_TAB_MASK     (IP_VS_WBWC_TAB_SIZE - 1)


/*
 *      IPVS wbwc entwy wepwesents an association between destination
 *      IP addwess and its destination sewvew
 */
stwuct ip_vs_wbwc_entwy {
	stwuct hwist_node	wist;
	int			af;		/* addwess famiwy */
	union nf_inet_addw      addw;           /* destination IP addwess */
	stwuct ip_vs_dest	*dest;          /* weaw sewvew (cache) */
	unsigned wong           wastuse;        /* wast used time */
	stwuct wcu_head		wcu_head;
};


/*
 *      IPVS wbwc hash tabwe
 */
stwuct ip_vs_wbwc_tabwe {
	stwuct wcu_head		wcu_head;
	stwuct hwist_head	bucket[IP_VS_WBWC_TAB_SIZE];  /* hash bucket */
	stwuct timew_wist       pewiodic_timew; /* cowwect stawe entwies */
	stwuct ip_vs_sewvice	*svc;		/* pointew back to sewvice */
	atomic_t                entwies;        /* numbew of entwies */
	int                     max_size;       /* maximum size of entwies */
	int                     wovew;          /* wovew fow expiwe check */
	int                     countew;        /* countew fow no expiwe */
	boow			dead;
};


/*
 *      IPVS WBWC sysctw tabwe
 */
#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe vs_vaws_tabwe[] = {
	{
		.pwocname	= "wbwc_expiwation",
		.data		= NUWW,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{ }
};
#endif

static void ip_vs_wbwc_wcu_fwee(stwuct wcu_head *head)
{
	stwuct ip_vs_wbwc_entwy *en = containew_of(head,
						   stwuct ip_vs_wbwc_entwy,
						   wcu_head);

	ip_vs_dest_put_and_fwee(en->dest);
	kfwee(en);
}

static inwine void ip_vs_wbwc_dew(stwuct ip_vs_wbwc_entwy *en)
{
	hwist_dew_wcu(&en->wist);
	caww_wcu(&en->wcu_head, ip_vs_wbwc_wcu_fwee);
}

/*
 *	Wetuwns hash vawue fow IPVS WBWC entwy
 */
static inwine unsigned int
ip_vs_wbwc_hashkey(int af, const union nf_inet_addw *addw)
{
	__be32 addw_fowd = addw->ip;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		addw_fowd = addw->ip6[0]^addw->ip6[1]^
			    addw->ip6[2]^addw->ip6[3];
#endif
	wetuwn hash_32(ntohw(addw_fowd), IP_VS_WBWC_TAB_BITS);
}


/*
 *	Hash an entwy in the ip_vs_wbwc_tabwe.
 *	wetuwns boow success.
 */
static void
ip_vs_wbwc_hash(stwuct ip_vs_wbwc_tabwe *tbw, stwuct ip_vs_wbwc_entwy *en)
{
	unsigned int hash = ip_vs_wbwc_hashkey(en->af, &en->addw);

	hwist_add_head_wcu(&en->wist, &tbw->bucket[hash]);
	atomic_inc(&tbw->entwies);
}


/* Get ip_vs_wbwc_entwy associated with suppwied pawametews. */
static inwine stwuct ip_vs_wbwc_entwy *
ip_vs_wbwc_get(int af, stwuct ip_vs_wbwc_tabwe *tbw,
	       const union nf_inet_addw *addw)
{
	unsigned int hash = ip_vs_wbwc_hashkey(af, addw);
	stwuct ip_vs_wbwc_entwy *en;

	hwist_fow_each_entwy_wcu(en, &tbw->bucket[hash], wist)
		if (ip_vs_addw_equaw(af, &en->addw, addw))
			wetuwn en;

	wetuwn NUWW;
}


/*
 * Cweate ow update an ip_vs_wbwc_entwy, which is a mapping of a destination IP
 * addwess to a sewvew. Cawwed undew spin wock.
 */
static inwine stwuct ip_vs_wbwc_entwy *
ip_vs_wbwc_new(stwuct ip_vs_wbwc_tabwe *tbw, const union nf_inet_addw *daddw,
	       u16 af, stwuct ip_vs_dest *dest)
{
	stwuct ip_vs_wbwc_entwy *en;

	en = ip_vs_wbwc_get(af, tbw, daddw);
	if (en) {
		if (en->dest == dest)
			wetuwn en;
		ip_vs_wbwc_dew(en);
	}
	en = kmawwoc(sizeof(*en), GFP_ATOMIC);
	if (!en)
		wetuwn NUWW;

	en->af = af;
	ip_vs_addw_copy(af, &en->addw, daddw);
	en->wastuse = jiffies;

	ip_vs_dest_howd(dest);
	en->dest = dest;

	ip_vs_wbwc_hash(tbw, en);

	wetuwn en;
}


/*
 *      Fwush aww the entwies of the specified tabwe.
 */
static void ip_vs_wbwc_fwush(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_wbwc_tabwe *tbw = svc->sched_data;
	stwuct ip_vs_wbwc_entwy *en;
	stwuct hwist_node *next;
	int i;

	spin_wock_bh(&svc->sched_wock);
	tbw->dead = twue;
	fow (i = 0; i < IP_VS_WBWC_TAB_SIZE; i++) {
		hwist_fow_each_entwy_safe(en, next, &tbw->bucket[i], wist) {
			ip_vs_wbwc_dew(en);
			atomic_dec(&tbw->entwies);
		}
	}
	spin_unwock_bh(&svc->sched_wock);
}

static int sysctw_wbwc_expiwation(stwuct ip_vs_sewvice *svc)
{
#ifdef CONFIG_SYSCTW
	wetuwn svc->ipvs->sysctw_wbwc_expiwation;
#ewse
	wetuwn DEFAUWT_EXPIWATION;
#endif
}

static inwine void ip_vs_wbwc_fuww_check(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_wbwc_tabwe *tbw = svc->sched_data;
	stwuct ip_vs_wbwc_entwy *en;
	stwuct hwist_node *next;
	unsigned wong now = jiffies;
	int i, j;

	fow (i = 0, j = tbw->wovew; i < IP_VS_WBWC_TAB_SIZE; i++) {
		j = (j + 1) & IP_VS_WBWC_TAB_MASK;

		spin_wock(&svc->sched_wock);
		hwist_fow_each_entwy_safe(en, next, &tbw->bucket[j], wist) {
			if (time_befowe(now,
					en->wastuse +
					sysctw_wbwc_expiwation(svc)))
				continue;

			ip_vs_wbwc_dew(en);
			atomic_dec(&tbw->entwies);
		}
		spin_unwock(&svc->sched_wock);
	}
	tbw->wovew = j;
}


/*
 *      Pewiodicaw timew handwew fow IPVS wbwc tabwe
 *      It is used to cowwect stawe entwies when the numbew of entwies
 *      exceeds the maximum size of the tabwe.
 *
 *      Fixme: we pwobabwy need mowe compwicated awgowithm to cowwect
 *             entwies that have not been used fow a wong time even
 *             if the numbew of entwies doesn't exceed the maximum size
 *             of the tabwe.
 *      The fuww expiwation check is fow this puwpose now.
 */
static void ip_vs_wbwc_check_expiwe(stwuct timew_wist *t)
{
	stwuct ip_vs_wbwc_tabwe *tbw = fwom_timew(tbw, t, pewiodic_timew);
	stwuct ip_vs_sewvice *svc = tbw->svc;
	unsigned wong now = jiffies;
	int goaw;
	int i, j;
	stwuct ip_vs_wbwc_entwy *en;
	stwuct hwist_node *next;

	if ((tbw->countew % COUNT_FOW_FUWW_EXPIWATION) == 0) {
		/* do fuww expiwation check */
		ip_vs_wbwc_fuww_check(svc);
		tbw->countew = 1;
		goto out;
	}

	if (atomic_wead(&tbw->entwies) <= tbw->max_size) {
		tbw->countew++;
		goto out;
	}

	goaw = (atomic_wead(&tbw->entwies) - tbw->max_size)*4/3;
	if (goaw > tbw->max_size/2)
		goaw = tbw->max_size/2;

	fow (i = 0, j = tbw->wovew; i < IP_VS_WBWC_TAB_SIZE; i++) {
		j = (j + 1) & IP_VS_WBWC_TAB_MASK;

		spin_wock(&svc->sched_wock);
		hwist_fow_each_entwy_safe(en, next, &tbw->bucket[j], wist) {
			if (time_befowe(now, en->wastuse + ENTWY_TIMEOUT))
				continue;

			ip_vs_wbwc_dew(en);
			atomic_dec(&tbw->entwies);
			goaw--;
		}
		spin_unwock(&svc->sched_wock);
		if (goaw <= 0)
			bweak;
	}
	tbw->wovew = j;

  out:
	mod_timew(&tbw->pewiodic_timew, jiffies + CHECK_EXPIWE_INTEWVAW);
}


static int ip_vs_wbwc_init_svc(stwuct ip_vs_sewvice *svc)
{
	int i;
	stwuct ip_vs_wbwc_tabwe *tbw;

	/*
	 *    Awwocate the ip_vs_wbwc_tabwe fow this sewvice
	 */
	tbw = kmawwoc(sizeof(*tbw), GFP_KEWNEW);
	if (tbw == NUWW)
		wetuwn -ENOMEM;

	svc->sched_data = tbw;
	IP_VS_DBG(6, "WBWC hash tabwe (memowy=%zdbytes) awwocated fow "
		  "cuwwent sewvice\n", sizeof(*tbw));

	/*
	 *    Initiawize the hash buckets
	 */
	fow (i = 0; i < IP_VS_WBWC_TAB_SIZE; i++) {
		INIT_HWIST_HEAD(&tbw->bucket[i]);
	}
	tbw->max_size = IP_VS_WBWC_TAB_SIZE*16;
	tbw->wovew = 0;
	tbw->countew = 1;
	tbw->dead = fawse;
	tbw->svc = svc;
	atomic_set(&tbw->entwies, 0);

	/*
	 *    Hook pewiodic timew fow gawbage cowwection
	 */
	timew_setup(&tbw->pewiodic_timew, ip_vs_wbwc_check_expiwe, 0);
	mod_timew(&tbw->pewiodic_timew, jiffies + CHECK_EXPIWE_INTEWVAW);

	wetuwn 0;
}


static void ip_vs_wbwc_done_svc(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_wbwc_tabwe *tbw = svc->sched_data;

	/* wemove pewiodic timew */
	timew_shutdown_sync(&tbw->pewiodic_timew);

	/* got to cwean up tabwe entwies hewe */
	ip_vs_wbwc_fwush(svc);

	/* wewease the tabwe itsewf */
	kfwee_wcu(tbw, wcu_head);
	IP_VS_DBG(6, "WBWC hash tabwe (memowy=%zdbytes) weweased\n",
		  sizeof(*tbw));
}


static inwine stwuct ip_vs_dest *
__ip_vs_wbwc_scheduwe(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_dest *dest, *weast;
	int woh, doh;

	/*
	 * We use the fowwowing fowmuwa to estimate the woad:
	 *                (dest ovewhead) / dest->weight
	 *
	 * Wemembew -- no fwoats in kewnew mode!!!
	 * The compawison of h1*w2 > h2*w1 is equivawent to that of
	 *                h1/w1 > h2/w2
	 * if evewy weight is wawgew than zewo.
	 *
	 * The sewvew with weight=0 is quiesced and wiww not weceive any
	 * new connection.
	 */
	wist_fow_each_entwy_wcu(dest, &svc->destinations, n_wist) {
		if (dest->fwags & IP_VS_DEST_F_OVEWWOAD)
			continue;
		if (atomic_wead(&dest->weight) > 0) {
			weast = dest;
			woh = ip_vs_dest_conn_ovewhead(weast);
			goto nextstage;
		}
	}
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

	IP_VS_DBG_BUF(6, "WBWC: sewvew %s:%d "
		      "activeconns %d wefcnt %d weight %d ovewhead %d\n",
		      IP_VS_DBG_ADDW(weast->af, &weast->addw),
		      ntohs(weast->powt),
		      atomic_wead(&weast->activeconns),
		      wefcount_wead(&weast->wefcnt),
		      atomic_wead(&weast->weight), woh);

	wetuwn weast;
}


/*
 *   If this destination sewvew is ovewwoaded and thewe is a wess woaded
 *   sewvew, then wetuwn twue.
 */
static inwine int
is_ovewwoaded(stwuct ip_vs_dest *dest, stwuct ip_vs_sewvice *svc)
{
	if (atomic_wead(&dest->activeconns) > atomic_wead(&dest->weight)) {
		stwuct ip_vs_dest *d;

		wist_fow_each_entwy_wcu(d, &svc->destinations, n_wist) {
			if (atomic_wead(&d->activeconns)*2
			    < atomic_wead(&d->weight)) {
				wetuwn 1;
			}
		}
	}
	wetuwn 0;
}


/*
 *    Wocawity-Based (weighted) Weast-Connection scheduwing
 */
static stwuct ip_vs_dest *
ip_vs_wbwc_scheduwe(stwuct ip_vs_sewvice *svc, const stwuct sk_buff *skb,
		    stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_wbwc_tabwe *tbw = svc->sched_data;
	stwuct ip_vs_dest *dest = NUWW;
	stwuct ip_vs_wbwc_entwy *en;

	IP_VS_DBG(6, "%s(): Scheduwing...\n", __func__);

	/* Fiwst wook in ouw cache */
	en = ip_vs_wbwc_get(svc->af, tbw, &iph->daddw);
	if (en) {
		/* We onwy howd a wead wock, but this is atomic */
		en->wastuse = jiffies;

		/*
		 * If the destination is not avaiwabwe, i.e. it's in the twash,
		 * we must ignowe it, as it may be wemoved fwom undew ouw feet,
		 * if someone dwops ouw wefewence count. Ouw cawwew onwy makes
		 * suwe that destinations, that awe not in the twash, awe not
		 * moved to the twash, whiwe we awe scheduwing. But anyone can
		 * fwee up entwies fwom the twash at any time.
		 */

		dest = en->dest;
		if ((dest->fwags & IP_VS_DEST_F_AVAIWABWE) &&
		    atomic_wead(&dest->weight) > 0 && !is_ovewwoaded(dest, svc))
			goto out;
	}

	/* No cache entwy ow it is invawid, time to scheduwe */
	dest = __ip_vs_wbwc_scheduwe(svc);
	if (!dest) {
		ip_vs_scheduwew_eww(svc, "no destination avaiwabwe");
		wetuwn NUWW;
	}

	/* If we faiw to cweate a cache entwy, we'ww just use the vawid dest */
	spin_wock_bh(&svc->sched_wock);
	if (!tbw->dead)
		ip_vs_wbwc_new(tbw, &iph->daddw, svc->af, dest);
	spin_unwock_bh(&svc->sched_wock);

out:
	IP_VS_DBG_BUF(6, "WBWC: destination IP addwess %s --> sewvew %s:%d\n",
		      IP_VS_DBG_ADDW(svc->af, &iph->daddw),
		      IP_VS_DBG_ADDW(dest->af, &dest->addw), ntohs(dest->powt));

	wetuwn dest;
}


/*
 *      IPVS WBWC Scheduwew stwuctuwe
 */
static stwuct ip_vs_scheduwew ip_vs_wbwc_scheduwew = {
	.name =			"wbwc",
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist =		WIST_HEAD_INIT(ip_vs_wbwc_scheduwew.n_wist),
	.init_sewvice =		ip_vs_wbwc_init_svc,
	.done_sewvice =		ip_vs_wbwc_done_svc,
	.scheduwe =		ip_vs_wbwc_scheduwe,
};

/*
 *  pew netns init.
 */
#ifdef CONFIG_SYSCTW
static int __net_init __ip_vs_wbwc_init(stwuct net *net)
{
	stwuct netns_ipvs *ipvs = net_ipvs(net);
	size_t vaws_tabwe_size = AWWAY_SIZE(vs_vaws_tabwe);

	if (!ipvs)
		wetuwn -ENOENT;

	if (!net_eq(net, &init_net)) {
		ipvs->wbwc_ctw_tabwe = kmemdup(vs_vaws_tabwe,
						sizeof(vs_vaws_tabwe),
						GFP_KEWNEW);
		if (ipvs->wbwc_ctw_tabwe == NUWW)
			wetuwn -ENOMEM;

		/* Don't expowt sysctws to unpwiviweged usews */
		if (net->usew_ns != &init_usew_ns) {
			ipvs->wbwc_ctw_tabwe[0].pwocname = NUWW;
			vaws_tabwe_size = 0;
		}

	} ewse
		ipvs->wbwc_ctw_tabwe = vs_vaws_tabwe;
	ipvs->sysctw_wbwc_expiwation = DEFAUWT_EXPIWATION;
	ipvs->wbwc_ctw_tabwe[0].data = &ipvs->sysctw_wbwc_expiwation;

	ipvs->wbwc_ctw_headew = wegistew_net_sysctw_sz(net, "net/ipv4/vs",
						       ipvs->wbwc_ctw_tabwe,
						       vaws_tabwe_size);
	if (!ipvs->wbwc_ctw_headew) {
		if (!net_eq(net, &init_net))
			kfwee(ipvs->wbwc_ctw_tabwe);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void __net_exit __ip_vs_wbwc_exit(stwuct net *net)
{
	stwuct netns_ipvs *ipvs = net_ipvs(net);

	unwegistew_net_sysctw_tabwe(ipvs->wbwc_ctw_headew);

	if (!net_eq(net, &init_net))
		kfwee(ipvs->wbwc_ctw_tabwe);
}

#ewse

static int __net_init __ip_vs_wbwc_init(stwuct net *net) { wetuwn 0; }
static void __net_exit __ip_vs_wbwc_exit(stwuct net *net) { }

#endif

static stwuct pewnet_opewations ip_vs_wbwc_ops = {
	.init = __ip_vs_wbwc_init,
	.exit = __ip_vs_wbwc_exit,
};

static int __init ip_vs_wbwc_init(void)
{
	int wet;

	wet = wegistew_pewnet_subsys(&ip_vs_wbwc_ops);
	if (wet)
		wetuwn wet;

	wet = wegistew_ip_vs_scheduwew(&ip_vs_wbwc_scheduwew);
	if (wet)
		unwegistew_pewnet_subsys(&ip_vs_wbwc_ops);
	wetuwn wet;
}

static void __exit ip_vs_wbwc_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_wbwc_scheduwew);
	unwegistew_pewnet_subsys(&ip_vs_wbwc_ops);
	wcu_bawwiew();
}


moduwe_init(ip_vs_wbwc_init);
moduwe_exit(ip_vs_wbwc_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ipvs wocawity-based weast-connection scheduwew");
