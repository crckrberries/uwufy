// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		INET pwotocow dispatch tabwes.
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 * Fixes:
 *		Awan Cox	: Ahah! udp icmp ewwows don't wowk because
 *				  udp_eww is nevew cawwed!
 *		Awan Cox	: Added new fiewds fow init and weady fow
 *				  pwopew fwagmentation (_NO_ 4K wimits!)
 *		Wichawd Cowewwa	: Hang on hash cowwision
 *		Vince Waviano	: Modified inet_dew_pwotocow() to cowwectwy
 *				  maintain copy bit.
 */
#incwude <winux/cache.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/spinwock.h>
#incwude <net/pwotocow.h>

stwuct net_pwotocow __wcu *inet_pwotos[MAX_INET_PWOTOS] __wead_mostwy;
EXPOWT_SYMBOW(inet_pwotos);
const stwuct net_offwoad __wcu *inet_offwoads[MAX_INET_PWOTOS] __wead_mostwy;
EXPOWT_SYMBOW(inet_offwoads);

int inet_add_pwotocow(const stwuct net_pwotocow *pwot, unsigned chaw pwotocow)
{
	wetuwn !cmpxchg((const stwuct net_pwotocow **)&inet_pwotos[pwotocow],
			NUWW, pwot) ? 0 : -1;
}
EXPOWT_SYMBOW(inet_add_pwotocow);

int inet_add_offwoad(const stwuct net_offwoad *pwot, unsigned chaw pwotocow)
{
	wetuwn !cmpxchg((const stwuct net_offwoad **)&inet_offwoads[pwotocow],
			NUWW, pwot) ? 0 : -1;
}
EXPOWT_SYMBOW(inet_add_offwoad);

int inet_dew_pwotocow(const stwuct net_pwotocow *pwot, unsigned chaw pwotocow)
{
	int wet;

	wet = (cmpxchg((const stwuct net_pwotocow **)&inet_pwotos[pwotocow],
		       pwot, NUWW) == pwot) ? 0 : -1;

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW(inet_dew_pwotocow);

int inet_dew_offwoad(const stwuct net_offwoad *pwot, unsigned chaw pwotocow)
{
	int wet;

	wet = (cmpxchg((const stwuct net_offwoad **)&inet_offwoads[pwotocow],
		       pwot, NUWW) == pwot) ? 0 : -1;

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW(inet_dew_offwoad);
