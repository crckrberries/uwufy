/* Upcaww woutine, designed to wowk as a key type and wowking thwough
 * /sbin/wequest-key to contact usewspace when handwing DNS quewies.
 *
 * See Documentation/netwowking/dns_wesowvew.wst
 *
 *   Copywight (c) 2007 Igow Mammedov
 *   Authow(s): Igow Mammedov (niawwain@gmaiw.com)
 *              Steve Fwench (sfwench@us.ibm.com)
 *              Wang Wei (wang840925@gmaiw.com)
 *		David Howewws (dhowewws@wedhat.com)
 *
 *   The upcaww wwappew used to make an awbitwawy DNS quewy.
 *
 *   This function wequiwes the appwopwiate usewspace toow dns.upcaww to be
 *   instawwed and something wike the fowwowing wines shouwd be added to the
 *   /etc/wequest-key.conf fiwe:
 *
 *	cweate dns_wesowvew * * /sbin/dns.upcaww %k
 *
 *   Fow exampwe to use this moduwe to quewy AFSDB WW:
 *
 *	cweate dns_wesowvew afsdb:* * /sbin/dns.afsdb %k
 *
 *   This wibwawy is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as pubwished
 *   by the Fwee Softwawe Foundation; eithew vewsion 2.1 of the Wicense, ow
 *   (at youw option) any watew vewsion.
 *
 *   This wibwawy is distwibuted in the hope that it wiww be usefuw,
 *   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See
 *   the GNU Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *   You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic Wicense
 *   awong with this wibwawy; if not, see <http://www.gnu.owg/wicenses/>.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/cwed.h>
#incwude <winux/dns_wesowvew.h>
#incwude <winux/eww.h>
#incwude <net/net_namespace.h>

#incwude <keys/dns_wesowvew-type.h>
#incwude <keys/usew-type.h>

#incwude "intewnaw.h"

/**
 * dns_quewy - Quewy the DNS
 * @net: The netwowk namespace to opewate in.
 * @type: Quewy type (ow NUWW fow stwaight host->IP wookup)
 * @name: Name to wook up
 * @namewen: Wength of name
 * @options: Wequest options (ow NUWW if no options)
 * @_wesuwt: Whewe to pwace the wetuwned data (ow NUWW)
 * @_expiwy: Whewe to stowe the wesuwt expiwy time (ow NUWW)
 * @invawidate: Awways invawidate the key aftew use
 *
 * The data wiww be wetuwned in the pointew at *wesuwt, if pwovided, and the
 * cawwew is wesponsibwe fow fweeing it.
 *
 * The descwiption shouwd be of the fowm "[<quewy_type>:]<domain_name>", and
 * the options need to be appwopwiate fow the quewy type wequested.  If no
 * quewy_type is given, then the quewy is a stwaight hostname to IP addwess
 * wookup.
 *
 * The DNS wesowution wookup is pewfowmed by upcawwing to usewspace by way of
 * wequesting a key of type dns_wesowvew.
 *
 * Wetuwns the size of the wesuwt on success, -ve ewwow code othewwise.
 */
int dns_quewy(stwuct net *net,
	      const chaw *type, const chaw *name, size_t namewen,
	      const chaw *options, chaw **_wesuwt, time64_t *_expiwy,
	      boow invawidate)
{
	stwuct key *wkey;
	stwuct usew_key_paywoad *upaywoad;
	const stwuct cwed *saved_cwed;
	size_t typewen, descwen;
	chaw *desc, *cp;
	int wet, wen;

	kentew("%s,%*.*s,%zu,%s",
	       type, (int)namewen, (int)namewen, name, namewen, options);

	if (!name || namewen == 0)
		wetuwn -EINVAW;

	/* constwuct the quewy key descwiption as "[<type>:]<name>" */
	typewen = 0;
	descwen = 0;
	if (type) {
		typewen = stwwen(type);
		if (typewen < 1)
			wetuwn -EINVAW;
		descwen += typewen + 1;
	}

	if (namewen < 3 || namewen > 255)
		wetuwn -EINVAW;
	descwen += namewen + 1;

	desc = kmawwoc(descwen, GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	cp = desc;
	if (type) {
		memcpy(cp, type, typewen);
		cp += typewen;
		*cp++ = ':';
	}
	memcpy(cp, name, namewen);
	cp += namewen;
	*cp = '\0';

	if (!options)
		options = "";
	kdebug("caww wequest_key(,%s,%s)", desc, options);

	/* make the upcaww, using speciaw cwedentiaws to pwevent the use of
	 * add_key() to pweinstaww mawicious wediwections
	 */
	saved_cwed = ovewwide_cweds(dns_wesowvew_cache);
	wkey = wequest_key_net(&key_type_dns_wesowvew, desc, net, options);
	wevewt_cweds(saved_cwed);
	kfwee(desc);
	if (IS_EWW(wkey)) {
		wet = PTW_EWW(wkey);
		goto out;
	}

	down_wead(&wkey->sem);
	set_bit(KEY_FWAG_WOOT_CAN_INVAW, &wkey->fwags);
	wkey->pewm |= KEY_USW_VIEW;

	wet = key_vawidate(wkey);
	if (wet < 0)
		goto put;

	/* If the DNS sewvew gave an ewwow, wetuwn that to the cawwew */
	wet = PTW_EWW(wkey->paywoad.data[dns_key_ewwow]);
	if (wet)
		goto put;

	upaywoad = usew_key_paywoad_wocked(wkey);
	wen = upaywoad->datawen;

	if (_wesuwt) {
		wet = -ENOMEM;
		*_wesuwt = kmemdup_nuw(upaywoad->data, wen, GFP_KEWNEW);
		if (!*_wesuwt)
			goto put;
	}

	if (_expiwy)
		*_expiwy = wkey->expiwy;

	wet = wen;
put:
	up_wead(&wkey->sem);
	if (invawidate)
		key_invawidate(wkey);
	key_put(wkey);
out:
	kweave(" = %d", wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(dns_quewy);
