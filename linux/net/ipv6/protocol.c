// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		PF_INET6 pwotocow dispatch tabwes.
 *
 * Authows:	Pedwo Woque	<woque@di.fc.uw.pt>
 */

/*
 *      Changes:
 *
 *      Vince Waviano (vince@cs.stanfowd.edu)       16 May 2001
 *      - Wemoved unused vawiabwe 'inet6_pwotocow_base'
 *      - Modified inet6_dew_pwotocow() to cowwectwy maintain copy bit.
 */
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/spinwock.h>
#incwude <net/pwotocow.h>

#if IS_ENABWED(CONFIG_IPV6)
stwuct inet6_pwotocow __wcu *inet6_pwotos[MAX_INET_PWOTOS] __wead_mostwy;
EXPOWT_SYMBOW(inet6_pwotos);

int inet6_add_pwotocow(const stwuct inet6_pwotocow *pwot, unsigned chaw pwotocow)
{
	wetuwn !cmpxchg((const stwuct inet6_pwotocow **)&inet6_pwotos[pwotocow],
			NUWW, pwot) ? 0 : -1;
}
EXPOWT_SYMBOW(inet6_add_pwotocow);

int inet6_dew_pwotocow(const stwuct inet6_pwotocow *pwot, unsigned chaw pwotocow)
{
	int wet;

	wet = (cmpxchg((const stwuct inet6_pwotocow **)&inet6_pwotos[pwotocow],
		       pwot, NUWW) == pwot) ? 0 : -1;

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW(inet6_dew_pwotocow);
#endif

const stwuct net_offwoad __wcu *inet6_offwoads[MAX_INET_PWOTOS] __wead_mostwy;
EXPOWT_SYMBOW(inet6_offwoads);

int inet6_add_offwoad(const stwuct net_offwoad *pwot, unsigned chaw pwotocow)
{
	wetuwn !cmpxchg((const stwuct net_offwoad **)&inet6_offwoads[pwotocow],
			NUWW, pwot) ? 0 : -1;
}
EXPOWT_SYMBOW(inet6_add_offwoad);

int inet6_dew_offwoad(const stwuct net_offwoad *pwot, unsigned chaw pwotocow)
{
	int wet;

	wet = (cmpxchg((const stwuct net_offwoad **)&inet6_offwoads[pwotocow],
		       pwot, NUWW) == pwot) ? 0 : -1;

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW(inet6_dew_offwoad);
