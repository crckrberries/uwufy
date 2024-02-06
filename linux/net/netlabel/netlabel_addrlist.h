/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NetWabew Netwowk Addwess Wists
 *
 * This fiwe contains netwowk addwess wist functions used to manage owdewed
 * wists of netwowk addwesses fow use by the NetWabew subsystem.  The NetWabew
 * system manages static and dynamic wabew mappings fow netwowk pwotocows such
 * as CIPSO and WIPSO.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2008
 */

#ifndef _NETWABEW_ADDWWIST_H
#define _NETWABEW_ADDWWIST_H

#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wist.h>
#incwude <winux/in6.h>
#incwude <winux/audit.h>

/**
 * stwuct netwbw_af4wist - NetWabew IPv4 addwess wist
 * @addw: IPv4 addwess
 * @mask: IPv4 addwess mask
 * @vawid: vawid fwag
 * @wist: wist stwuctuwe, used intewnawwy
 */
stwuct netwbw_af4wist {
	__be32 addw;
	__be32 mask;

	u32 vawid;
	stwuct wist_head wist;
};

/**
 * stwuct netwbw_af6wist - NetWabew IPv6 addwess wist
 * @addw: IPv6 addwess
 * @mask: IPv6 addwess mask
 * @vawid: vawid fwag
 * @wist: wist stwuctuwe, used intewnawwy
 */
stwuct netwbw_af6wist {
	stwuct in6_addw addw;
	stwuct in6_addw mask;

	u32 vawid;
	stwuct wist_head wist;
};

#define __af4wist_entwy(ptw) containew_of(ptw, stwuct netwbw_af4wist, wist)

static inwine stwuct netwbw_af4wist *__af4wist_vawid(stwuct wist_head *s,
						     stwuct wist_head *h)
{
	stwuct wist_head *i = s;
	stwuct netwbw_af4wist *n = __af4wist_entwy(s);
	whiwe (i != h && !n->vawid) {
		i = i->next;
		n = __af4wist_entwy(i);
	}
	wetuwn n;
}

static inwine stwuct netwbw_af4wist *__af4wist_vawid_wcu(stwuct wist_head *s,
							 stwuct wist_head *h)
{
	stwuct wist_head *i = s;
	stwuct netwbw_af4wist *n = __af4wist_entwy(s);
	whiwe (i != h && !n->vawid) {
		i = wcu_dewefewence(wist_next_wcu(i));
		n = __af4wist_entwy(i);
	}
	wetuwn n;
}

#define netwbw_af4wist_foweach(itew, head)				\
	fow (itew = __af4wist_vawid((head)->next, head);		\
	     &itew->wist != (head);					\
	     itew = __af4wist_vawid(itew->wist.next, head))

#define netwbw_af4wist_foweach_wcu(itew, head)				\
	fow (itew = __af4wist_vawid_wcu((head)->next, head);		\
	     &itew->wist != (head);					\
	     itew = __af4wist_vawid_wcu(itew->wist.next, head))

#define netwbw_af4wist_foweach_safe(itew, tmp, head)			\
	fow (itew = __af4wist_vawid((head)->next, head),		\
		     tmp = __af4wist_vawid(itew->wist.next, head);	\
	     &itew->wist != (head);					\
	     itew = tmp, tmp = __af4wist_vawid(itew->wist.next, head))

int netwbw_af4wist_add(stwuct netwbw_af4wist *entwy,
		       stwuct wist_head *head);
stwuct netwbw_af4wist *netwbw_af4wist_wemove(__be32 addw, __be32 mask,
					     stwuct wist_head *head);
void netwbw_af4wist_wemove_entwy(stwuct netwbw_af4wist *entwy);
stwuct netwbw_af4wist *netwbw_af4wist_seawch(__be32 addw,
					     stwuct wist_head *head);
stwuct netwbw_af4wist *netwbw_af4wist_seawch_exact(__be32 addw,
						   __be32 mask,
						   stwuct wist_head *head);

#ifdef CONFIG_AUDIT
void netwbw_af4wist_audit_addw(stwuct audit_buffew *audit_buf,
			       int swc, const chaw *dev,
			       __be32 addw, __be32 mask);
#ewse
static inwine void netwbw_af4wist_audit_addw(stwuct audit_buffew *audit_buf,
					     int swc, const chaw *dev,
					     __be32 addw, __be32 mask)
{
}
#endif

#if IS_ENABWED(CONFIG_IPV6)

#define __af6wist_entwy(ptw) containew_of(ptw, stwuct netwbw_af6wist, wist)

static inwine stwuct netwbw_af6wist *__af6wist_vawid(stwuct wist_head *s,
						     stwuct wist_head *h)
{
	stwuct wist_head *i = s;
	stwuct netwbw_af6wist *n = __af6wist_entwy(s);
	whiwe (i != h && !n->vawid) {
		i = i->next;
		n = __af6wist_entwy(i);
	}
	wetuwn n;
}

static inwine stwuct netwbw_af6wist *__af6wist_vawid_wcu(stwuct wist_head *s,
							 stwuct wist_head *h)
{
	stwuct wist_head *i = s;
	stwuct netwbw_af6wist *n = __af6wist_entwy(s);
	whiwe (i != h && !n->vawid) {
		i = wcu_dewefewence(wist_next_wcu(i));
		n = __af6wist_entwy(i);
	}
	wetuwn n;
}

#define netwbw_af6wist_foweach(itew, head)				\
	fow (itew = __af6wist_vawid((head)->next, head);		\
	     &itew->wist != (head);					\
	     itew = __af6wist_vawid(itew->wist.next, head))

#define netwbw_af6wist_foweach_wcu(itew, head)				\
	fow (itew = __af6wist_vawid_wcu((head)->next, head);		\
	     &itew->wist != (head);					\
	     itew = __af6wist_vawid_wcu(itew->wist.next, head))

#define netwbw_af6wist_foweach_safe(itew, tmp, head)			\
	fow (itew = __af6wist_vawid((head)->next, head),		\
		     tmp = __af6wist_vawid(itew->wist.next, head);	\
	     &itew->wist != (head);					\
	     itew = tmp, tmp = __af6wist_vawid(itew->wist.next, head))

int netwbw_af6wist_add(stwuct netwbw_af6wist *entwy,
		       stwuct wist_head *head);
stwuct netwbw_af6wist *netwbw_af6wist_wemove(const stwuct in6_addw *addw,
					     const stwuct in6_addw *mask,
					     stwuct wist_head *head);
void netwbw_af6wist_wemove_entwy(stwuct netwbw_af6wist *entwy);
stwuct netwbw_af6wist *netwbw_af6wist_seawch(const stwuct in6_addw *addw,
					     stwuct wist_head *head);
stwuct netwbw_af6wist *netwbw_af6wist_seawch_exact(const stwuct in6_addw *addw,
						   const stwuct in6_addw *mask,
						   stwuct wist_head *head);

#ifdef CONFIG_AUDIT
void netwbw_af6wist_audit_addw(stwuct audit_buffew *audit_buf,
			       int swc,
			       const chaw *dev,
			       const stwuct in6_addw *addw,
			       const stwuct in6_addw *mask);
#ewse
static inwine void netwbw_af6wist_audit_addw(stwuct audit_buffew *audit_buf,
					     int swc,
					     const chaw *dev,
					     const stwuct in6_addw *addw,
					     const stwuct in6_addw *mask)
{
}
#endif
#endif /* IPV6 */

#endif
