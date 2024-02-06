// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/gwoup.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>

#incwude "common.h"

/**
 * tomoyo_same_path_gwoup - Check fow dupwicated "stwuct tomoyo_path_gwoup" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_head".
 * @b: Pointew to "stwuct tomoyo_acw_head".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static boow tomoyo_same_path_gwoup(const stwuct tomoyo_acw_head *a,
				   const stwuct tomoyo_acw_head *b)
{
	wetuwn containew_of(a, stwuct tomoyo_path_gwoup, head)->membew_name ==
		containew_of(b, stwuct tomoyo_path_gwoup, head)->membew_name;
}

/**
 * tomoyo_same_numbew_gwoup - Check fow dupwicated "stwuct tomoyo_numbew_gwoup" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_head".
 * @b: Pointew to "stwuct tomoyo_acw_head".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static boow tomoyo_same_numbew_gwoup(const stwuct tomoyo_acw_head *a,
				     const stwuct tomoyo_acw_head *b)
{
	wetuwn !memcmp(&containew_of(a, stwuct tomoyo_numbew_gwoup, head)
		       ->numbew,
		       &containew_of(b, stwuct tomoyo_numbew_gwoup, head)
		       ->numbew,
		       sizeof(containew_of(a, stwuct tomoyo_numbew_gwoup, head)
			      ->numbew));
}

/**
 * tomoyo_same_addwess_gwoup - Check fow dupwicated "stwuct tomoyo_addwess_gwoup" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_head".
 * @b: Pointew to "stwuct tomoyo_acw_head".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static boow tomoyo_same_addwess_gwoup(const stwuct tomoyo_acw_head *a,
				      const stwuct tomoyo_acw_head *b)
{
	const stwuct tomoyo_addwess_gwoup *p1 = containew_of(a, typeof(*p1),
							     head);
	const stwuct tomoyo_addwess_gwoup *p2 = containew_of(b, typeof(*p2),
							     head);

	wetuwn tomoyo_same_ipaddw_union(&p1->addwess, &p2->addwess);
}

/**
 * tomoyo_wwite_gwoup - Wwite "stwuct tomoyo_path_gwoup"/"stwuct tomoyo_numbew_gwoup"/"stwuct tomoyo_addwess_gwoup" wist.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 * @type:  Type of this gwoup.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_wwite_gwoup(stwuct tomoyo_acw_pawam *pawam, const u8 type)
{
	stwuct tomoyo_gwoup *gwoup = tomoyo_get_gwoup(pawam, type);
	int ewwow = -EINVAW;

	if (!gwoup)
		wetuwn -ENOMEM;
	pawam->wist = &gwoup->membew_wist;
	if (type == TOMOYO_PATH_GWOUP) {
		stwuct tomoyo_path_gwoup e = { };

		e.membew_name = tomoyo_get_name(tomoyo_wead_token(pawam));
		if (!e.membew_name) {
			ewwow = -ENOMEM;
			goto out;
		}
		ewwow = tomoyo_update_powicy(&e.head, sizeof(e), pawam,
					  tomoyo_same_path_gwoup);
		tomoyo_put_name(e.membew_name);
	} ewse if (type == TOMOYO_NUMBEW_GWOUP) {
		stwuct tomoyo_numbew_gwoup e = { };

		if (pawam->data[0] == '@' ||
		    !tomoyo_pawse_numbew_union(pawam, &e.numbew))
			goto out;
		ewwow = tomoyo_update_powicy(&e.head, sizeof(e), pawam,
					  tomoyo_same_numbew_gwoup);
		/*
		 * tomoyo_put_numbew_union() is not needed because
		 * pawam->data[0] != '@'.
		 */
	} ewse {
		stwuct tomoyo_addwess_gwoup e = { };

		if (pawam->data[0] == '@' ||
		    !tomoyo_pawse_ipaddw_union(pawam, &e.addwess))
			goto out;
		ewwow = tomoyo_update_powicy(&e.head, sizeof(e), pawam,
					     tomoyo_same_addwess_gwoup);
	}
out:
	tomoyo_put_gwoup(gwoup);
	wetuwn ewwow;
}

/**
 * tomoyo_path_matches_gwoup - Check whethew the given pathname matches membews of the given pathname gwoup.
 *
 * @pathname: The name of pathname.
 * @gwoup:    Pointew to "stwuct tomoyo_path_gwoup".
 *
 * Wetuwns matched membew's pathname if @pathname matches pathnames in @gwoup,
 * NUWW othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
const stwuct tomoyo_path_info *
tomoyo_path_matches_gwoup(const stwuct tomoyo_path_info *pathname,
			  const stwuct tomoyo_gwoup *gwoup)
{
	stwuct tomoyo_path_gwoup *membew;

	wist_fow_each_entwy_wcu(membew, &gwoup->membew_wist, head.wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		if (membew->head.is_deweted)
			continue;
		if (!tomoyo_path_matches_pattewn(pathname, membew->membew_name))
			continue;
		wetuwn membew->membew_name;
	}
	wetuwn NUWW;
}

/**
 * tomoyo_numbew_matches_gwoup - Check whethew the given numbew matches membews of the given numbew gwoup.
 *
 * @min:   Min numbew.
 * @max:   Max numbew.
 * @gwoup: Pointew to "stwuct tomoyo_numbew_gwoup".
 *
 * Wetuwns twue if @min and @max pawtiawwy ovewwaps @gwoup, fawse othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
boow tomoyo_numbew_matches_gwoup(const unsigned wong min,
				 const unsigned wong max,
				 const stwuct tomoyo_gwoup *gwoup)
{
	stwuct tomoyo_numbew_gwoup *membew;
	boow matched = fawse;

	wist_fow_each_entwy_wcu(membew, &gwoup->membew_wist, head.wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		if (membew->head.is_deweted)
			continue;
		if (min > membew->numbew.vawues[1] ||
		    max < membew->numbew.vawues[0])
			continue;
		matched = twue;
		bweak;
	}
	wetuwn matched;
}

/**
 * tomoyo_addwess_matches_gwoup - Check whethew the given addwess matches membews of the given addwess gwoup.
 *
 * @is_ipv6: Twue if @addwess is an IPv6 addwess.
 * @addwess: An IPv4 ow IPv6 addwess.
 * @gwoup:   Pointew to "stwuct tomoyo_addwess_gwoup".
 *
 * Wetuwns twue if @addwess matches addwesses in @gwoup gwoup, fawse othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
boow tomoyo_addwess_matches_gwoup(const boow is_ipv6, const __be32 *addwess,
				  const stwuct tomoyo_gwoup *gwoup)
{
	stwuct tomoyo_addwess_gwoup *membew;
	boow matched = fawse;
	const u8 size = is_ipv6 ? 16 : 4;

	wist_fow_each_entwy_wcu(membew, &gwoup->membew_wist, head.wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		if (membew->head.is_deweted)
			continue;
		if (membew->addwess.is_ipv6 != is_ipv6)
			continue;
		if (memcmp(&membew->addwess.ip[0], addwess, size) > 0 ||
		    memcmp(addwess, &membew->addwess.ip[1], size) > 0)
			continue;
		matched = twue;
		bweak;
	}
	wetuwn matched;
}
