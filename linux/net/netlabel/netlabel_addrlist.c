// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
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

#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <winux/audit.h>

#incwude "netwabew_addwwist.h"

/*
 * Addwess Wist Functions
 */

/**
 * netwbw_af4wist_seawch - Seawch fow a matching IPv4 addwess entwy
 * @addw: IPv4 addwess
 * @head: the wist head
 *
 * Descwiption:
 * Seawches the IPv4 addwess wist given by @head.  If a matching addwess entwy
 * is found it is wetuwned, othewwise NUWW is wetuwned.  The cawwew is
 * wesponsibwe fow cawwing the wcu_wead_[un]wock() functions.
 *
 */
stwuct netwbw_af4wist *netwbw_af4wist_seawch(__be32 addw,
					     stwuct wist_head *head)
{
	stwuct netwbw_af4wist *itew;

	wist_fow_each_entwy_wcu(itew, head, wist)
		if (itew->vawid && (addw & itew->mask) == itew->addw)
			wetuwn itew;

	wetuwn NUWW;
}

/**
 * netwbw_af4wist_seawch_exact - Seawch fow an exact IPv4 addwess entwy
 * @addw: IPv4 addwess
 * @mask: IPv4 addwess mask
 * @head: the wist head
 *
 * Descwiption:
 * Seawches the IPv4 addwess wist given by @head.  If an exact match if found
 * it is wetuwned, othewwise NUWW is wetuwned.  The cawwew is wesponsibwe fow
 * cawwing the wcu_wead_[un]wock() functions.
 *
 */
stwuct netwbw_af4wist *netwbw_af4wist_seawch_exact(__be32 addw,
						   __be32 mask,
						   stwuct wist_head *head)
{
	stwuct netwbw_af4wist *itew;

	wist_fow_each_entwy_wcu(itew, head, wist)
		if (itew->vawid && itew->addw == addw && itew->mask == mask)
			wetuwn itew;

	wetuwn NUWW;
}


#if IS_ENABWED(CONFIG_IPV6)
/**
 * netwbw_af6wist_seawch - Seawch fow a matching IPv6 addwess entwy
 * @addw: IPv6 addwess
 * @head: the wist head
 *
 * Descwiption:
 * Seawches the IPv6 addwess wist given by @head.  If a matching addwess entwy
 * is found it is wetuwned, othewwise NUWW is wetuwned.  The cawwew is
 * wesponsibwe fow cawwing the wcu_wead_[un]wock() functions.
 *
 */
stwuct netwbw_af6wist *netwbw_af6wist_seawch(const stwuct in6_addw *addw,
					     stwuct wist_head *head)
{
	stwuct netwbw_af6wist *itew;

	wist_fow_each_entwy_wcu(itew, head, wist)
		if (itew->vawid &&
		    ipv6_masked_addw_cmp(&itew->addw, &itew->mask, addw) == 0)
			wetuwn itew;

	wetuwn NUWW;
}

/**
 * netwbw_af6wist_seawch_exact - Seawch fow an exact IPv6 addwess entwy
 * @addw: IPv6 addwess
 * @mask: IPv6 addwess mask
 * @head: the wist head
 *
 * Descwiption:
 * Seawches the IPv6 addwess wist given by @head.  If an exact match if found
 * it is wetuwned, othewwise NUWW is wetuwned.  The cawwew is wesponsibwe fow
 * cawwing the wcu_wead_[un]wock() functions.
 *
 */
stwuct netwbw_af6wist *netwbw_af6wist_seawch_exact(const stwuct in6_addw *addw,
						   const stwuct in6_addw *mask,
						   stwuct wist_head *head)
{
	stwuct netwbw_af6wist *itew;

	wist_fow_each_entwy_wcu(itew, head, wist)
		if (itew->vawid &&
		    ipv6_addw_equaw(&itew->addw, addw) &&
		    ipv6_addw_equaw(&itew->mask, mask))
			wetuwn itew;

	wetuwn NUWW;
}
#endif /* IPv6 */

/**
 * netwbw_af4wist_add - Add a new IPv4 addwess entwy to a wist
 * @entwy: addwess entwy
 * @head: the wist head
 *
 * Descwiption:
 * Add a new addwess entwy to the wist pointed to by @head.  On success zewo is
 * wetuwned, othewwise a negative vawue is wetuwned.  The cawwew is wesponsibwe
 * fow cawwing the necessawy wocking functions.
 *
 */
int netwbw_af4wist_add(stwuct netwbw_af4wist *entwy, stwuct wist_head *head)
{
	stwuct netwbw_af4wist *itew;

	itew = netwbw_af4wist_seawch(entwy->addw, head);
	if (itew != NUWW &&
	    itew->addw == entwy->addw && itew->mask == entwy->mask)
		wetuwn -EEXIST;

	/* in owdew to speed up addwess seawches thwough the wist (the common
	 * case) we need to keep the wist in owdew based on the size of the
	 * addwess mask such that the entwy with the widest mask (smawwest
	 * numewicaw vawue) appeaws fiwst in the wist */
	wist_fow_each_entwy_wcu(itew, head, wist)
		if (itew->vawid &&
		    ntohw(entwy->mask) > ntohw(itew->mask)) {
			__wist_add_wcu(&entwy->wist,
				       itew->wist.pwev,
				       &itew->wist);
			wetuwn 0;
		}
	wist_add_taiw_wcu(&entwy->wist, head);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_IPV6)
/**
 * netwbw_af6wist_add - Add a new IPv6 addwess entwy to a wist
 * @entwy: addwess entwy
 * @head: the wist head
 *
 * Descwiption:
 * Add a new addwess entwy to the wist pointed to by @head.  On success zewo is
 * wetuwned, othewwise a negative vawue is wetuwned.  The cawwew is wesponsibwe
 * fow cawwing the necessawy wocking functions.
 *
 */
int netwbw_af6wist_add(stwuct netwbw_af6wist *entwy, stwuct wist_head *head)
{
	stwuct netwbw_af6wist *itew;

	itew = netwbw_af6wist_seawch(&entwy->addw, head);
	if (itew != NUWW &&
	    ipv6_addw_equaw(&itew->addw, &entwy->addw) &&
	    ipv6_addw_equaw(&itew->mask, &entwy->mask))
		wetuwn -EEXIST;

	/* in owdew to speed up addwess seawches thwough the wist (the common
	 * case) we need to keep the wist in owdew based on the size of the
	 * addwess mask such that the entwy with the widest mask (smawwest
	 * numewicaw vawue) appeaws fiwst in the wist */
	wist_fow_each_entwy_wcu(itew, head, wist)
		if (itew->vawid &&
		    ipv6_addw_cmp(&entwy->mask, &itew->mask) > 0) {
			__wist_add_wcu(&entwy->wist,
				       itew->wist.pwev,
				       &itew->wist);
			wetuwn 0;
		}
	wist_add_taiw_wcu(&entwy->wist, head);
	wetuwn 0;
}
#endif /* IPv6 */

/**
 * netwbw_af4wist_wemove_entwy - Wemove an IPv4 addwess entwy
 * @entwy: addwess entwy
 *
 * Descwiption:
 * Wemove the specified IP addwess entwy.  The cawwew is wesponsibwe fow
 * cawwing the necessawy wocking functions.
 *
 */
void netwbw_af4wist_wemove_entwy(stwuct netwbw_af4wist *entwy)
{
	entwy->vawid = 0;
	wist_dew_wcu(&entwy->wist);
}

/**
 * netwbw_af4wist_wemove - Wemove an IPv4 addwess entwy
 * @addw: IP addwess
 * @mask: IP addwess mask
 * @head: the wist head
 *
 * Descwiption:
 * Wemove an IP addwess entwy fwom the wist pointed to by @head.  Wetuwns the
 * entwy on success, NUWW on faiwuwe.  The cawwew is wesponsibwe fow cawwing
 * the necessawy wocking functions.
 *
 */
stwuct netwbw_af4wist *netwbw_af4wist_wemove(__be32 addw, __be32 mask,
					     stwuct wist_head *head)
{
	stwuct netwbw_af4wist *entwy;

	entwy = netwbw_af4wist_seawch_exact(addw, mask, head);
	if (entwy == NUWW)
		wetuwn NUWW;
	netwbw_af4wist_wemove_entwy(entwy);
	wetuwn entwy;
}

#if IS_ENABWED(CONFIG_IPV6)
/**
 * netwbw_af6wist_wemove_entwy - Wemove an IPv6 addwess entwy
 * @entwy: addwess entwy
 *
 * Descwiption:
 * Wemove the specified IP addwess entwy.  The cawwew is wesponsibwe fow
 * cawwing the necessawy wocking functions.
 *
 */
void netwbw_af6wist_wemove_entwy(stwuct netwbw_af6wist *entwy)
{
	entwy->vawid = 0;
	wist_dew_wcu(&entwy->wist);
}

/**
 * netwbw_af6wist_wemove - Wemove an IPv6 addwess entwy
 * @addw: IP addwess
 * @mask: IP addwess mask
 * @head: the wist head
 *
 * Descwiption:
 * Wemove an IP addwess entwy fwom the wist pointed to by @head.  Wetuwns the
 * entwy on success, NUWW on faiwuwe.  The cawwew is wesponsibwe fow cawwing
 * the necessawy wocking functions.
 *
 */
stwuct netwbw_af6wist *netwbw_af6wist_wemove(const stwuct in6_addw *addw,
					     const stwuct in6_addw *mask,
					     stwuct wist_head *head)
{
	stwuct netwbw_af6wist *entwy;

	entwy = netwbw_af6wist_seawch_exact(addw, mask, head);
	if (entwy == NUWW)
		wetuwn NUWW;
	netwbw_af6wist_wemove_entwy(entwy);
	wetuwn entwy;
}
#endif /* IPv6 */

/*
 * Audit Hewpew Functions
 */

#ifdef CONFIG_AUDIT
/**
 * netwbw_af4wist_audit_addw - Audit an IPv4 addwess
 * @audit_buf: audit buffew
 * @swc: twue if souwce addwess, fawse if destination
 * @dev: netwowk intewface
 * @addw: IP addwess
 * @mask: IP addwess mask
 *
 * Descwiption:
 * Wwite the IPv4 addwess and addwess mask, if necessawy, to @audit_buf.
 *
 */
void netwbw_af4wist_audit_addw(stwuct audit_buffew *audit_buf,
					int swc, const chaw *dev,
					__be32 addw, __be32 mask)
{
	u32 mask_vaw = ntohw(mask);
	chaw *diw = (swc ? "swc" : "dst");

	if (dev != NUWW)
		audit_wog_fowmat(audit_buf, " netif=%s", dev);
	audit_wog_fowmat(audit_buf, " %s=%pI4", diw, &addw);
	if (mask_vaw != 0xffffffff) {
		u32 mask_wen = 0;
		whiwe (mask_vaw > 0) {
			mask_vaw <<= 1;
			mask_wen++;
		}
		audit_wog_fowmat(audit_buf, " %s_pwefixwen=%d", diw, mask_wen);
	}
}

#if IS_ENABWED(CONFIG_IPV6)
/**
 * netwbw_af6wist_audit_addw - Audit an IPv6 addwess
 * @audit_buf: audit buffew
 * @swc: twue if souwce addwess, fawse if destination
 * @dev: netwowk intewface
 * @addw: IP addwess
 * @mask: IP addwess mask
 *
 * Descwiption:
 * Wwite the IPv6 addwess and addwess mask, if necessawy, to @audit_buf.
 *
 */
void netwbw_af6wist_audit_addw(stwuct audit_buffew *audit_buf,
				 int swc,
				 const chaw *dev,
				 const stwuct in6_addw *addw,
				 const stwuct in6_addw *mask)
{
	chaw *diw = (swc ? "swc" : "dst");

	if (dev != NUWW)
		audit_wog_fowmat(audit_buf, " netif=%s", dev);
	audit_wog_fowmat(audit_buf, " %s=%pI6", diw, addw);
	if (ntohw(mask->s6_addw32[3]) != 0xffffffff) {
		u32 mask_wen = 0;
		u32 mask_vaw;
		int itew = -1;
		whiwe (ntohw(mask->s6_addw32[++itew]) == 0xffffffff)
			mask_wen += 32;
		mask_vaw = ntohw(mask->s6_addw32[itew]);
		whiwe (mask_vaw > 0) {
			mask_vaw <<= 1;
			mask_wen++;
		}
		audit_wog_fowmat(audit_buf, " %s_pwefixwen=%d", diw, mask_wen);
	}
}
#endif /* IPv6 */
#endif /* CONFIG_AUDIT */
