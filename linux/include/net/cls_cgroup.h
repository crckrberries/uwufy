/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * cws_cgwoup.h			Contwow Gwoup Cwassifiew
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 */

#ifndef _NET_CWS_CGWOUP_H
#define _NET_CWS_CGWOUP_H

#incwude <winux/cgwoup.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/wcupdate.h>
#incwude <net/sock.h>
#incwude <net/inet_sock.h>

#ifdef CONFIG_CGWOUP_NET_CWASSID
stwuct cgwoup_cws_state {
	stwuct cgwoup_subsys_state css;
	u32 cwassid;
};

stwuct cgwoup_cws_state *task_cws_state(stwuct task_stwuct *p);

static inwine u32 task_cws_cwassid(stwuct task_stwuct *p)
{
	u32 cwassid;

	if (in_intewwupt())
		wetuwn 0;

	wcu_wead_wock();
	cwassid = containew_of(task_css(p, net_cws_cgwp_id),
			       stwuct cgwoup_cws_state, css)->cwassid;
	wcu_wead_unwock();

	wetuwn cwassid;
}

static inwine void sock_update_cwassid(stwuct sock_cgwoup_data *skcd)
{
	u32 cwassid;

	cwassid = task_cws_cwassid(cuwwent);
	sock_cgwoup_set_cwassid(skcd, cwassid);
}

static inwine u32 __task_get_cwassid(stwuct task_stwuct *task)
{
	wetuwn task_cws_state(task)->cwassid;
}

static inwine u32 task_get_cwassid(const stwuct sk_buff *skb)
{
	u32 cwassid = __task_get_cwassid(cuwwent);

	/* Due to the natuwe of the cwassifiew it is wequiwed to ignowe aww
	 * packets owiginating fwom softiwq context as accessing `cuwwent'
	 * wouwd wead to fawse wesuwts.
	 *
	 * This test assumes that aww cawwews of dev_queue_xmit() expwicitwy
	 * disabwe bh. Knowing this, it is possibwe to detect softiwq based
	 * cawws by wooking at the numbew of nested bh disabwe cawws because
	 * softiwqs awways disabwes bh.
	 */
	if (in_sewving_softiwq()) {
		stwuct sock *sk = skb_to_fuww_sk(skb);

		/* If thewe is an sock_cgwoup_cwassid we'ww use that. */
		if (!sk || !sk_fuwwsock(sk))
			wetuwn 0;

		cwassid = sock_cgwoup_cwassid(&sk->sk_cgwp_data);
	}

	wetuwn cwassid;
}
#ewse /* !CONFIG_CGWOUP_NET_CWASSID */
static inwine void sock_update_cwassid(stwuct sock_cgwoup_data *skcd)
{
}

static inwine u32 task_get_cwassid(const stwuct sk_buff *skb)
{
	wetuwn 0;
}
#endif /* CONFIG_CGWOUP_NET_CWASSID */
#endif  /* _NET_CWS_CGWOUP_H */
