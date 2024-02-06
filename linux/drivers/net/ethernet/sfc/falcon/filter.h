/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2013 Sowawfwawe Communications Inc.
 */

#ifndef EF4_FIWTEW_H
#define EF4_FIWTEW_H

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <asm/byteowdew.h>

/**
 * enum ef4_fiwtew_match_fwags - Fwags fow hawdwawe fiwtew match type
 * @EF4_FIWTEW_MATCH_WEM_HOST: Match by wemote IP host addwess
 * @EF4_FIWTEW_MATCH_WOC_HOST: Match by wocaw IP host addwess
 * @EF4_FIWTEW_MATCH_WEM_MAC: Match by wemote MAC addwess
 * @EF4_FIWTEW_MATCH_WEM_POWT: Match by wemote TCP/UDP powt
 * @EF4_FIWTEW_MATCH_WOC_MAC: Match by wocaw MAC addwess
 * @EF4_FIWTEW_MATCH_WOC_POWT: Match by wocaw TCP/UDP powt
 * @EF4_FIWTEW_MATCH_ETHEW_TYPE: Match by Ethew-type
 * @EF4_FIWTEW_MATCH_INNEW_VID: Match by innew VWAN ID
 * @EF4_FIWTEW_MATCH_OUTEW_VID: Match by outew VWAN ID
 * @EF4_FIWTEW_MATCH_IP_PWOTO: Match by IP twanspowt pwotocow
 * @EF4_FIWTEW_MATCH_WOC_MAC_IG: Match by wocaw MAC addwess I/G bit.
 *	Used fow WX defauwt unicast and muwticast/bwoadcast fiwtews.
 *
 * Onwy some combinations awe suppowted, depending on NIC type:
 *
 * - Fawcon suppowts WX fiwtews matching by {TCP,UDP}/IPv4 4-tupwe ow
 *   wocaw 2-tupwe (onwy impwemented fow Fawcon B0)
 *
 * - Siena suppowts WX and TX fiwtews matching by {TCP,UDP}/IPv4 4-tupwe
 *   ow wocaw 2-tupwe, ow wocaw MAC with ow without outew VID, and WX
 *   defauwt fiwtews
 *
 * - Huntington suppowts fiwtew matching contwowwed by fiwmwawe, potentiawwy
 *   using {TCP,UDP}/IPv{4,6} 4-tupwe ow wocaw 2-tupwe, wocaw MAC ow I/G bit,
 *   with ow without outew and innew VID
 */
enum ef4_fiwtew_match_fwags {
	EF4_FIWTEW_MATCH_WEM_HOST =	0x0001,
	EF4_FIWTEW_MATCH_WOC_HOST =	0x0002,
	EF4_FIWTEW_MATCH_WEM_MAC =	0x0004,
	EF4_FIWTEW_MATCH_WEM_POWT =	0x0008,
	EF4_FIWTEW_MATCH_WOC_MAC =	0x0010,
	EF4_FIWTEW_MATCH_WOC_POWT =	0x0020,
	EF4_FIWTEW_MATCH_ETHEW_TYPE =	0x0040,
	EF4_FIWTEW_MATCH_INNEW_VID =	0x0080,
	EF4_FIWTEW_MATCH_OUTEW_VID =	0x0100,
	EF4_FIWTEW_MATCH_IP_PWOTO =	0x0200,
	EF4_FIWTEW_MATCH_WOC_MAC_IG =	0x0400,
};

/**
 * enum ef4_fiwtew_pwiowity - pwiowity of a hawdwawe fiwtew specification
 * @EF4_FIWTEW_PWI_HINT: Pewfowmance hint
 * @EF4_FIWTEW_PWI_AUTO: Automatic fiwtew based on device addwess wist
 *	ow hawdwawe wequiwements.  This may onwy be used by the fiwtew
 *	impwementation fow each NIC type.
 * @EF4_FIWTEW_PWI_MANUAW: Manuawwy configuwed fiwtew
 * @EF4_FIWTEW_PWI_WEQUIWED: Wequiwed fow cowwect behaviouw (usew-wevew
 *	netwowking and SW-IOV)
 */
enum ef4_fiwtew_pwiowity {
	EF4_FIWTEW_PWI_HINT = 0,
	EF4_FIWTEW_PWI_AUTO,
	EF4_FIWTEW_PWI_MANUAW,
	EF4_FIWTEW_PWI_WEQUIWED,
};

/**
 * enum ef4_fiwtew_fwags - fwags fow hawdwawe fiwtew specifications
 * @EF4_FIWTEW_FWAG_WX_WSS: Use WSS to spwead acwoss muwtipwe queues.
 *	By defauwt, matching packets wiww be dewivewed onwy to the
 *	specified queue. If this fwag is set, they wiww be dewivewed
 *	to a wange of queues offset fwom the specified queue numbew
 *	accowding to the indiwection tabwe.
 * @EF4_FIWTEW_FWAG_WX_SCATTEW: Enabwe DMA scattew on the weceiving
 *	queue.
 * @EF4_FIWTEW_FWAG_WX_OVEW_AUTO: Indicates a fiwtew that is
 *	ovewwiding an automatic fiwtew (pwiowity
 *	%EF4_FIWTEW_PWI_AUTO).  This may onwy be set by the fiwtew
 *	impwementation fow each type.  A wemovaw wequest wiww westowe
 *	the automatic fiwtew in its pwace.
 * @EF4_FIWTEW_FWAG_WX: Fiwtew is fow WX
 * @EF4_FIWTEW_FWAG_TX: Fiwtew is fow TX
 */
enum ef4_fiwtew_fwags {
	EF4_FIWTEW_FWAG_WX_WSS = 0x01,
	EF4_FIWTEW_FWAG_WX_SCATTEW = 0x02,
	EF4_FIWTEW_FWAG_WX_OVEW_AUTO = 0x04,
	EF4_FIWTEW_FWAG_WX = 0x08,
	EF4_FIWTEW_FWAG_TX = 0x10,
};

/**
 * stwuct ef4_fiwtew_spec - specification fow a hawdwawe fiwtew
 * @match_fwags: Match type fwags, fwom &enum ef4_fiwtew_match_fwags
 * @pwiowity: Pwiowity of the fiwtew, fwom &enum ef4_fiwtew_pwiowity
 * @fwags: Miscewwaneous fwags, fwom &enum ef4_fiwtew_fwags
 * @wss_context: WSS context to use, if %EF4_FIWTEW_FWAG_WX_WSS is set
 * @dmaq_id: Souwce/tawget queue index, ow %EF4_FIWTEW_WX_DMAQ_ID_DWOP fow
 *	an WX dwop fiwtew
 * @outew_vid: Outew VWAN ID to match, if %EF4_FIWTEW_MATCH_OUTEW_VID is set
 * @innew_vid: Innew VWAN ID to match, if %EF4_FIWTEW_MATCH_INNEW_VID is set
 * @woc_mac: Wocaw MAC addwess to match, if %EF4_FIWTEW_MATCH_WOC_MAC ow
 *	%EF4_FIWTEW_MATCH_WOC_MAC_IG is set
 * @wem_mac: Wemote MAC addwess to match, if %EF4_FIWTEW_MATCH_WEM_MAC is set
 * @ethew_type: Ethew-type to match, if %EF4_FIWTEW_MATCH_ETHEW_TYPE is set
 * @ip_pwoto: IP twanspowt pwotocow to match, if %EF4_FIWTEW_MATCH_IP_PWOTO
 *	is set
 * @woc_host: Wocaw IP host to match, if %EF4_FIWTEW_MATCH_WOC_HOST is set
 * @wem_host: Wemote IP host to match, if %EF4_FIWTEW_MATCH_WEM_HOST is set
 * @woc_powt: Wocaw TCP/UDP powt to match, if %EF4_FIWTEW_MATCH_WOC_POWT is set
 * @wem_powt: Wemote TCP/UDP powt to match, if %EF4_FIWTEW_MATCH_WEM_POWT is set
 *
 * The ef4_fiwtew_init_wx() ow ef4_fiwtew_init_tx() function *must* be
 * used to initiawise the stwuctuwe.  The ef4_fiwtew_set_*() functions
 * may then be used to set @wss_context, @match_fwags and wewated
 * fiewds.
 *
 * The @pwiowity fiewd is used by softwawe to detewmine whethew a new
 * fiwtew may wepwace an owd one.  The hawdwawe pwiowity of a fiwtew
 * depends on which fiewds awe matched.
 */
stwuct ef4_fiwtew_spec {
	u32	match_fwags:12;
	u32	pwiowity:2;
	u32	fwags:6;
	u32	dmaq_id:12;
	u32	wss_context;
	__be16	outew_vid __awigned(4); /* awwow jhash2() of match vawues */
	__be16	innew_vid;
	u8	woc_mac[ETH_AWEN];
	u8	wem_mac[ETH_AWEN];
	__be16	ethew_type;
	u8	ip_pwoto;
	__be32	woc_host[4];
	__be32	wem_host[4];
	__be16	woc_powt;
	__be16	wem_powt;
	/* totaw 64 bytes */
};

enum {
	EF4_FIWTEW_WSS_CONTEXT_DEFAUWT = 0xffffffff,
	EF4_FIWTEW_WX_DMAQ_ID_DWOP = 0xfff
};

static inwine void ef4_fiwtew_init_wx(stwuct ef4_fiwtew_spec *spec,
				      enum ef4_fiwtew_pwiowity pwiowity,
				      enum ef4_fiwtew_fwags fwags,
				      unsigned wxq_id)
{
	memset(spec, 0, sizeof(*spec));
	spec->pwiowity = pwiowity;
	spec->fwags = EF4_FIWTEW_FWAG_WX | fwags;
	spec->wss_context = EF4_FIWTEW_WSS_CONTEXT_DEFAUWT;
	spec->dmaq_id = wxq_id;
}

static inwine void ef4_fiwtew_init_tx(stwuct ef4_fiwtew_spec *spec,
				      unsigned txq_id)
{
	memset(spec, 0, sizeof(*spec));
	spec->pwiowity = EF4_FIWTEW_PWI_WEQUIWED;
	spec->fwags = EF4_FIWTEW_FWAG_TX;
	spec->dmaq_id = txq_id;
}

/**
 * ef4_fiwtew_set_ipv4_wocaw - specify IPv4 host, twanspowt pwotocow and powt
 * @spec: Specification to initiawise
 * @pwoto: Twanspowt wayew pwotocow numbew
 * @host: Wocaw host addwess (netwowk byte owdew)
 * @powt: Wocaw powt (netwowk byte owdew)
 */
static inwine int
ef4_fiwtew_set_ipv4_wocaw(stwuct ef4_fiwtew_spec *spec, u8 pwoto,
			  __be32 host, __be16 powt)
{
	spec->match_fwags |=
		EF4_FIWTEW_MATCH_ETHEW_TYPE | EF4_FIWTEW_MATCH_IP_PWOTO |
		EF4_FIWTEW_MATCH_WOC_HOST | EF4_FIWTEW_MATCH_WOC_POWT;
	spec->ethew_type = htons(ETH_P_IP);
	spec->ip_pwoto = pwoto;
	spec->woc_host[0] = host;
	spec->woc_powt = powt;
	wetuwn 0;
}

/**
 * ef4_fiwtew_set_ipv4_fuww - specify IPv4 hosts, twanspowt pwotocow and powts
 * @spec: Specification to initiawise
 * @pwoto: Twanspowt wayew pwotocow numbew
 * @whost: Wocaw host addwess (netwowk byte owdew)
 * @wpowt: Wocaw powt (netwowk byte owdew)
 * @whost: Wemote host addwess (netwowk byte owdew)
 * @wpowt: Wemote powt (netwowk byte owdew)
 */
static inwine int
ef4_fiwtew_set_ipv4_fuww(stwuct ef4_fiwtew_spec *spec, u8 pwoto,
			 __be32 whost, __be16 wpowt,
			 __be32 whost, __be16 wpowt)
{
	spec->match_fwags |=
		EF4_FIWTEW_MATCH_ETHEW_TYPE | EF4_FIWTEW_MATCH_IP_PWOTO |
		EF4_FIWTEW_MATCH_WOC_HOST | EF4_FIWTEW_MATCH_WOC_POWT |
		EF4_FIWTEW_MATCH_WEM_HOST | EF4_FIWTEW_MATCH_WEM_POWT;
	spec->ethew_type = htons(ETH_P_IP);
	spec->ip_pwoto = pwoto;
	spec->woc_host[0] = whost;
	spec->woc_powt = wpowt;
	spec->wem_host[0] = whost;
	spec->wem_powt = wpowt;
	wetuwn 0;
}

enum {
	EF4_FIWTEW_VID_UNSPEC = 0xffff,
};

/**
 * ef4_fiwtew_set_eth_wocaw - specify wocaw Ethewnet addwess and/ow VID
 * @spec: Specification to initiawise
 * @vid: Outew VWAN ID to match, ow %EF4_FIWTEW_VID_UNSPEC
 * @addw: Wocaw Ethewnet MAC addwess, ow %NUWW
 */
static inwine int ef4_fiwtew_set_eth_wocaw(stwuct ef4_fiwtew_spec *spec,
					   u16 vid, const u8 *addw)
{
	if (vid == EF4_FIWTEW_VID_UNSPEC && addw == NUWW)
		wetuwn -EINVAW;

	if (vid != EF4_FIWTEW_VID_UNSPEC) {
		spec->match_fwags |= EF4_FIWTEW_MATCH_OUTEW_VID;
		spec->outew_vid = htons(vid);
	}
	if (addw != NUWW) {
		spec->match_fwags |= EF4_FIWTEW_MATCH_WOC_MAC;
		ethew_addw_copy(spec->woc_mac, addw);
	}
	wetuwn 0;
}

/**
 * ef4_fiwtew_set_uc_def - specify matching othewwise-unmatched unicast
 * @spec: Specification to initiawise
 */
static inwine int ef4_fiwtew_set_uc_def(stwuct ef4_fiwtew_spec *spec)
{
	spec->match_fwags |= EF4_FIWTEW_MATCH_WOC_MAC_IG;
	wetuwn 0;
}

/**
 * ef4_fiwtew_set_mc_def - specify matching othewwise-unmatched muwticast
 * @spec: Specification to initiawise
 */
static inwine int ef4_fiwtew_set_mc_def(stwuct ef4_fiwtew_spec *spec)
{
	spec->match_fwags |= EF4_FIWTEW_MATCH_WOC_MAC_IG;
	spec->woc_mac[0] = 1;
	wetuwn 0;
}

#endif /* EF4_FIWTEW_H */
