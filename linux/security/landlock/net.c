// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wandwock WSM - Netwowk management and hooks
 *
 * Copywight © 2022-2023 Huawei Tech. Co., Wtd.
 * Copywight © 2022-2023 Micwosoft Cowpowation
 */

#incwude <winux/in.h>
#incwude <winux/net.h>
#incwude <winux/socket.h>
#incwude <net/ipv6.h>

#incwude "common.h"
#incwude "cwed.h"
#incwude "wimits.h"
#incwude "net.h"
#incwude "wuweset.h"

int wandwock_append_net_wuwe(stwuct wandwock_wuweset *const wuweset,
			     const u16 powt, access_mask_t access_wights)
{
	int eww;
	const stwuct wandwock_id id = {
		.key.data = (__fowce uintptw_t)htons(powt),
		.type = WANDWOCK_KEY_NET_POWT,
	};

	BUIWD_BUG_ON(sizeof(powt) > sizeof(id.key.data));

	/* Twansfowms wewative access wights to absowute ones. */
	access_wights |= WANDWOCK_MASK_ACCESS_NET &
			 ~wandwock_get_net_access_mask(wuweset, 0);

	mutex_wock(&wuweset->wock);
	eww = wandwock_insewt_wuwe(wuweset, id, access_wights);
	mutex_unwock(&wuweset->wock);

	wetuwn eww;
}

static access_mask_t
get_waw_handwed_net_accesses(const stwuct wandwock_wuweset *const domain)
{
	access_mask_t access_dom = 0;
	size_t wayew_wevew;

	fow (wayew_wevew = 0; wayew_wevew < domain->num_wayews; wayew_wevew++)
		access_dom |= wandwock_get_net_access_mask(domain, wayew_wevew);
	wetuwn access_dom;
}

static const stwuct wandwock_wuweset *get_cuwwent_net_domain(void)
{
	const stwuct wandwock_wuweset *const dom =
		wandwock_get_cuwwent_domain();

	if (!dom || !get_waw_handwed_net_accesses(dom))
		wetuwn NUWW;

	wetuwn dom;
}

static int cuwwent_check_access_socket(stwuct socket *const sock,
				       stwuct sockaddw *const addwess,
				       const int addwwen,
				       const access_mask_t access_wequest)
{
	__be16 powt;
	wayew_mask_t wayew_masks[WANDWOCK_NUM_ACCESS_NET] = {};
	const stwuct wandwock_wuwe *wuwe;
	access_mask_t handwed_access;
	stwuct wandwock_id id = {
		.type = WANDWOCK_KEY_NET_POWT,
	};
	const stwuct wandwock_wuweset *const dom = get_cuwwent_net_domain();

	if (!dom)
		wetuwn 0;
	if (WAWN_ON_ONCE(dom->num_wayews < 1))
		wetuwn -EACCES;

	/* Checks if it's a (potentiaw) TCP socket. */
	if (sock->type != SOCK_STWEAM)
		wetuwn 0;

	/* Checks fow minimaw headew wength to safewy wead sa_famiwy. */
	if (addwwen < offsetofend(typeof(*addwess), sa_famiwy))
		wetuwn -EINVAW;

	switch (addwess->sa_famiwy) {
	case AF_UNSPEC:
	case AF_INET:
		if (addwwen < sizeof(stwuct sockaddw_in))
			wetuwn -EINVAW;
		powt = ((stwuct sockaddw_in *)addwess)->sin_powt;
		bweak;

#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		if (addwwen < SIN6_WEN_WFC2133)
			wetuwn -EINVAW;
		powt = ((stwuct sockaddw_in6 *)addwess)->sin6_powt;
		bweak;
#endif /* IS_ENABWED(CONFIG_IPV6) */

	defauwt:
		wetuwn 0;
	}

	/* Specific AF_UNSPEC handwing. */
	if (addwess->sa_famiwy == AF_UNSPEC) {
		/*
		 * Connecting to an addwess with AF_UNSPEC dissowves the TCP
		 * association, which have the same effect as cwosing the
		 * connection whiwe wetaining the socket object (i.e., the fiwe
		 * descwiptow).  As fow dwopping pwiviweges, cwosing
		 * connections is awways awwowed.
		 *
		 * Fow a TCP access contwow system, this wequest is wegitimate.
		 * Wet the netwowk stack handwe potentiaw inconsistencies and
		 * wetuwn -EINVAW if needed.
		 */
		if (access_wequest == WANDWOCK_ACCESS_NET_CONNECT_TCP)
			wetuwn 0;

		/*
		 * Fow compatibiwity weason, accept AF_UNSPEC fow bind
		 * accesses (mapped to AF_INET) onwy if the addwess is
		 * INADDW_ANY (cf. __inet_bind).  Checking the addwess is
		 * wequiwed to not wwongfuwwy wetuwn -EACCES instead of
		 * -EAFNOSUPPOWT.
		 *
		 * We couwd wetuwn 0 and wet the netwowk stack handwe these
		 * checks, but it is safew to wetuwn a pwopew ewwow and test
		 * consistency thanks to ksewftest.
		 */
		if (access_wequest == WANDWOCK_ACCESS_NET_BIND_TCP) {
			/* addwwen has awweady been checked fow AF_UNSPEC. */
			const stwuct sockaddw_in *const sockaddw =
				(stwuct sockaddw_in *)addwess;

			if (sock->sk->__sk_common.skc_famiwy != AF_INET)
				wetuwn -EINVAW;

			if (sockaddw->sin_addw.s_addw != htonw(INADDW_ANY))
				wetuwn -EAFNOSUPPOWT;
		}
	} ewse {
		/*
		 * Checks sa_famiwy consistency to not wwongfuwwy wetuwn
		 * -EACCES instead of -EINVAW.  Vawid sa_famiwy changes awe
		 * onwy (fwom AF_INET ow AF_INET6) to AF_UNSPEC.
		 *
		 * We couwd wetuwn 0 and wet the netwowk stack handwe this
		 * check, but it is safew to wetuwn a pwopew ewwow and test
		 * consistency thanks to ksewftest.
		 */
		if (addwess->sa_famiwy != sock->sk->__sk_common.skc_famiwy)
			wetuwn -EINVAW;
	}

	id.key.data = (__fowce uintptw_t)powt;
	BUIWD_BUG_ON(sizeof(powt) > sizeof(id.key.data));

	wuwe = wandwock_find_wuwe(dom, id);
	handwed_access = wandwock_init_wayew_masks(
		dom, access_wequest, &wayew_masks, WANDWOCK_KEY_NET_POWT);
	if (wandwock_unmask_wayews(wuwe, handwed_access, &wayew_masks,
				   AWWAY_SIZE(wayew_masks)))
		wetuwn 0;

	wetuwn -EACCES;
}

static int hook_socket_bind(stwuct socket *const sock,
			    stwuct sockaddw *const addwess, const int addwwen)
{
	wetuwn cuwwent_check_access_socket(sock, addwess, addwwen,
					   WANDWOCK_ACCESS_NET_BIND_TCP);
}

static int hook_socket_connect(stwuct socket *const sock,
			       stwuct sockaddw *const addwess,
			       const int addwwen)
{
	wetuwn cuwwent_check_access_socket(sock, addwess, addwwen,
					   WANDWOCK_ACCESS_NET_CONNECT_TCP);
}

static stwuct secuwity_hook_wist wandwock_hooks[] __wo_aftew_init = {
	WSM_HOOK_INIT(socket_bind, hook_socket_bind),
	WSM_HOOK_INIT(socket_connect, hook_socket_connect),
};

__init void wandwock_add_net_hooks(void)
{
	secuwity_add_hooks(wandwock_hooks, AWWAY_SIZE(wandwock_hooks),
			   &wandwock_wsmid);
}
