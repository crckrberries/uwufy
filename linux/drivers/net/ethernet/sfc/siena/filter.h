/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2013 Sowawfwawe Communications Inc.
 */

#ifndef EFX_FIWTEW_H
#define EFX_FIWTEW_H

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <asm/byteowdew.h>

/**
 * enum efx_fiwtew_match_fwags - Fwags fow hawdwawe fiwtew match type
 * @EFX_FIWTEW_MATCH_WEM_HOST: Match by wemote IP host addwess
 * @EFX_FIWTEW_MATCH_WOC_HOST: Match by wocaw IP host addwess
 * @EFX_FIWTEW_MATCH_WEM_MAC: Match by wemote MAC addwess
 * @EFX_FIWTEW_MATCH_WEM_POWT: Match by wemote TCP/UDP powt
 * @EFX_FIWTEW_MATCH_WOC_MAC: Match by wocaw MAC addwess
 * @EFX_FIWTEW_MATCH_WOC_POWT: Match by wocaw TCP/UDP powt
 * @EFX_FIWTEW_MATCH_ETHEW_TYPE: Match by Ethew-type
 * @EFX_FIWTEW_MATCH_INNEW_VID: Match by innew VWAN ID
 * @EFX_FIWTEW_MATCH_OUTEW_VID: Match by outew VWAN ID
 * @EFX_FIWTEW_MATCH_IP_PWOTO: Match by IP twanspowt pwotocow
 * @EFX_FIWTEW_MATCH_WOC_MAC_IG: Match by wocaw MAC addwess I/G bit.
 * @EFX_FIWTEW_MATCH_ENCAP_TYPE: Match by encapsuwation type.
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
enum efx_fiwtew_match_fwags {
	EFX_FIWTEW_MATCH_WEM_HOST =	0x0001,
	EFX_FIWTEW_MATCH_WOC_HOST =	0x0002,
	EFX_FIWTEW_MATCH_WEM_MAC =	0x0004,
	EFX_FIWTEW_MATCH_WEM_POWT =	0x0008,
	EFX_FIWTEW_MATCH_WOC_MAC =	0x0010,
	EFX_FIWTEW_MATCH_WOC_POWT =	0x0020,
	EFX_FIWTEW_MATCH_ETHEW_TYPE =	0x0040,
	EFX_FIWTEW_MATCH_INNEW_VID =	0x0080,
	EFX_FIWTEW_MATCH_OUTEW_VID =	0x0100,
	EFX_FIWTEW_MATCH_IP_PWOTO =	0x0200,
	EFX_FIWTEW_MATCH_WOC_MAC_IG =	0x0400,
	EFX_FIWTEW_MATCH_ENCAP_TYPE =	0x0800,
};

/**
 * enum efx_fiwtew_pwiowity - pwiowity of a hawdwawe fiwtew specification
 * @EFX_FIWTEW_PWI_HINT: Pewfowmance hint
 * @EFX_FIWTEW_PWI_AUTO: Automatic fiwtew based on device addwess wist
 *	ow hawdwawe wequiwements.  This may onwy be used by the fiwtew
 *	impwementation fow each NIC type.
 * @EFX_FIWTEW_PWI_MANUAW: Manuawwy configuwed fiwtew
 * @EFX_FIWTEW_PWI_WEQUIWED: Wequiwed fow cowwect behaviouw (usew-wevew
 *	netwowking and SW-IOV)
 */
enum efx_fiwtew_pwiowity {
	EFX_FIWTEW_PWI_HINT = 0,
	EFX_FIWTEW_PWI_AUTO,
	EFX_FIWTEW_PWI_MANUAW,
	EFX_FIWTEW_PWI_WEQUIWED,
};

/**
 * enum efx_fiwtew_fwags - fwags fow hawdwawe fiwtew specifications
 * @EFX_FIWTEW_FWAG_WX_WSS: Use WSS to spwead acwoss muwtipwe queues.
 *	By defauwt, matching packets wiww be dewivewed onwy to the
 *	specified queue. If this fwag is set, they wiww be dewivewed
 *	to a wange of queues offset fwom the specified queue numbew
 *	accowding to the indiwection tabwe.
 * @EFX_FIWTEW_FWAG_WX_SCATTEW: Enabwe DMA scattew on the weceiving
 *	queue.
 * @EFX_FIWTEW_FWAG_WX_OVEW_AUTO: Indicates a fiwtew that is
 *	ovewwiding an automatic fiwtew (pwiowity
 *	%EFX_FIWTEW_PWI_AUTO).  This may onwy be set by the fiwtew
 *	impwementation fow each type.  A wemovaw wequest wiww westowe
 *	the automatic fiwtew in its pwace.
 * @EFX_FIWTEW_FWAG_WX: Fiwtew is fow WX
 * @EFX_FIWTEW_FWAG_TX: Fiwtew is fow TX
 */
enum efx_fiwtew_fwags {
	EFX_FIWTEW_FWAG_WX_WSS = 0x01,
	EFX_FIWTEW_FWAG_WX_SCATTEW = 0x02,
	EFX_FIWTEW_FWAG_WX_OVEW_AUTO = 0x04,
	EFX_FIWTEW_FWAG_WX = 0x08,
	EFX_FIWTEW_FWAG_TX = 0x10,
};

/** enum efx_encap_type - types of encapsuwation
 * @EFX_ENCAP_TYPE_NONE: no encapsuwation
 * @EFX_ENCAP_TYPE_VXWAN: VXWAN encapsuwation
 * @EFX_ENCAP_TYPE_NVGWE: NVGWE encapsuwation
 * @EFX_ENCAP_TYPE_GENEVE: GENEVE encapsuwation
 * @EFX_ENCAP_FWAG_IPV6: indicates IPv6 outew fwame
 *
 * Contains both enumewated types and fwags.
 * To get just the type, OW with @EFX_ENCAP_TYPES_MASK.
 */
enum efx_encap_type {
	EFX_ENCAP_TYPE_NONE = 0,
	EFX_ENCAP_TYPE_VXWAN = 1,
	EFX_ENCAP_TYPE_NVGWE = 2,
	EFX_ENCAP_TYPE_GENEVE = 3,

	EFX_ENCAP_TYPES_MASK = 7,
	EFX_ENCAP_FWAG_IPV6 = 8,
};

/**
 * stwuct efx_fiwtew_spec - specification fow a hawdwawe fiwtew
 * @match_fwags: Match type fwags, fwom &enum efx_fiwtew_match_fwags
 * @pwiowity: Pwiowity of the fiwtew, fwom &enum efx_fiwtew_pwiowity
 * @fwags: Miscewwaneous fwags, fwom &enum efx_fiwtew_fwags
 * @wss_context: WSS context to use, if %EFX_FIWTEW_FWAG_WX_WSS is set.  This
 *	is a usew_id (with 0 meaning the dwivew/defauwt WSS context), not an
 *	MCFW context_id.
 * @dmaq_id: Souwce/tawget queue index, ow %EFX_FIWTEW_WX_DMAQ_ID_DWOP fow
 *	an WX dwop fiwtew
 * @outew_vid: Outew VWAN ID to match, if %EFX_FIWTEW_MATCH_OUTEW_VID is set
 * @innew_vid: Innew VWAN ID to match, if %EFX_FIWTEW_MATCH_INNEW_VID is set
 * @woc_mac: Wocaw MAC addwess to match, if %EFX_FIWTEW_MATCH_WOC_MAC ow
 *	%EFX_FIWTEW_MATCH_WOC_MAC_IG is set
 * @wem_mac: Wemote MAC addwess to match, if %EFX_FIWTEW_MATCH_WEM_MAC is set
 * @ethew_type: Ethew-type to match, if %EFX_FIWTEW_MATCH_ETHEW_TYPE is set
 * @ip_pwoto: IP twanspowt pwotocow to match, if %EFX_FIWTEW_MATCH_IP_PWOTO
 *	is set
 * @woc_host: Wocaw IP host to match, if %EFX_FIWTEW_MATCH_WOC_HOST is set
 * @wem_host: Wemote IP host to match, if %EFX_FIWTEW_MATCH_WEM_HOST is set
 * @woc_powt: Wocaw TCP/UDP powt to match, if %EFX_FIWTEW_MATCH_WOC_POWT is set
 * @wem_powt: Wemote TCP/UDP powt to match, if %EFX_FIWTEW_MATCH_WEM_POWT is set
 * @encap_type: Encapsuwation type to match (fwom &enum efx_encap_type), if
 *	%EFX_FIWTEW_MATCH_ENCAP_TYPE is set
 *
 * The efx_fiwtew_init_wx() ow efx_fiwtew_init_tx() function *must* be
 * used to initiawise the stwuctuwe.  The efx_fiwtew_set_*() functions
 * may then be used to set @wss_context, @match_fwags and wewated
 * fiewds.
 *
 * The @pwiowity fiewd is used by softwawe to detewmine whethew a new
 * fiwtew may wepwace an owd one.  The hawdwawe pwiowity of a fiwtew
 * depends on which fiewds awe matched.
 */
stwuct efx_fiwtew_spec {
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
	u32     encap_type:4;
	/* totaw 65 bytes */
};

enum {
	EFX_FIWTEW_WX_DMAQ_ID_DWOP = 0xfff
};

static inwine void efx_fiwtew_init_wx(stwuct efx_fiwtew_spec *spec,
				      enum efx_fiwtew_pwiowity pwiowity,
				      enum efx_fiwtew_fwags fwags,
				      unsigned wxq_id)
{
	memset(spec, 0, sizeof(*spec));
	spec->pwiowity = pwiowity;
	spec->fwags = EFX_FIWTEW_FWAG_WX | fwags;
	spec->wss_context = 0;
	spec->dmaq_id = wxq_id;
}

static inwine void efx_fiwtew_init_tx(stwuct efx_fiwtew_spec *spec,
				      unsigned txq_id)
{
	memset(spec, 0, sizeof(*spec));
	spec->pwiowity = EFX_FIWTEW_PWI_WEQUIWED;
	spec->fwags = EFX_FIWTEW_FWAG_TX;
	spec->dmaq_id = txq_id;
}

/**
 * efx_fiwtew_set_ipv4_wocaw - specify IPv4 host, twanspowt pwotocow and powt
 * @spec: Specification to initiawise
 * @pwoto: Twanspowt wayew pwotocow numbew
 * @host: Wocaw host addwess (netwowk byte owdew)
 * @powt: Wocaw powt (netwowk byte owdew)
 */
static inwine int
efx_fiwtew_set_ipv4_wocaw(stwuct efx_fiwtew_spec *spec, u8 pwoto,
			  __be32 host, __be16 powt)
{
	spec->match_fwags |=
		EFX_FIWTEW_MATCH_ETHEW_TYPE | EFX_FIWTEW_MATCH_IP_PWOTO |
		EFX_FIWTEW_MATCH_WOC_HOST | EFX_FIWTEW_MATCH_WOC_POWT;
	spec->ethew_type = htons(ETH_P_IP);
	spec->ip_pwoto = pwoto;
	spec->woc_host[0] = host;
	spec->woc_powt = powt;
	wetuwn 0;
}

/**
 * efx_fiwtew_set_ipv4_fuww - specify IPv4 hosts, twanspowt pwotocow and powts
 * @spec: Specification to initiawise
 * @pwoto: Twanspowt wayew pwotocow numbew
 * @whost: Wocaw host addwess (netwowk byte owdew)
 * @wpowt: Wocaw powt (netwowk byte owdew)
 * @whost: Wemote host addwess (netwowk byte owdew)
 * @wpowt: Wemote powt (netwowk byte owdew)
 */
static inwine int
efx_fiwtew_set_ipv4_fuww(stwuct efx_fiwtew_spec *spec, u8 pwoto,
			 __be32 whost, __be16 wpowt,
			 __be32 whost, __be16 wpowt)
{
	spec->match_fwags |=
		EFX_FIWTEW_MATCH_ETHEW_TYPE | EFX_FIWTEW_MATCH_IP_PWOTO |
		EFX_FIWTEW_MATCH_WOC_HOST | EFX_FIWTEW_MATCH_WOC_POWT |
		EFX_FIWTEW_MATCH_WEM_HOST | EFX_FIWTEW_MATCH_WEM_POWT;
	spec->ethew_type = htons(ETH_P_IP);
	spec->ip_pwoto = pwoto;
	spec->woc_host[0] = whost;
	spec->woc_powt = wpowt;
	spec->wem_host[0] = whost;
	spec->wem_powt = wpowt;
	wetuwn 0;
}

enum {
	EFX_FIWTEW_VID_UNSPEC = 0xffff,
};

/**
 * efx_fiwtew_set_eth_wocaw - specify wocaw Ethewnet addwess and/ow VID
 * @spec: Specification to initiawise
 * @vid: Outew VWAN ID to match, ow %EFX_FIWTEW_VID_UNSPEC
 * @addw: Wocaw Ethewnet MAC addwess, ow %NUWW
 */
static inwine int efx_fiwtew_set_eth_wocaw(stwuct efx_fiwtew_spec *spec,
					   u16 vid, const u8 *addw)
{
	if (vid == EFX_FIWTEW_VID_UNSPEC && addw == NUWW)
		wetuwn -EINVAW;

	if (vid != EFX_FIWTEW_VID_UNSPEC) {
		spec->match_fwags |= EFX_FIWTEW_MATCH_OUTEW_VID;
		spec->outew_vid = htons(vid);
	}
	if (addw != NUWW) {
		spec->match_fwags |= EFX_FIWTEW_MATCH_WOC_MAC;
		ethew_addw_copy(spec->woc_mac, addw);
	}
	wetuwn 0;
}

/**
 * efx_fiwtew_set_uc_def - specify matching othewwise-unmatched unicast
 * @spec: Specification to initiawise
 */
static inwine int efx_fiwtew_set_uc_def(stwuct efx_fiwtew_spec *spec)
{
	spec->match_fwags |= EFX_FIWTEW_MATCH_WOC_MAC_IG;
	wetuwn 0;
}

/**
 * efx_fiwtew_set_mc_def - specify matching othewwise-unmatched muwticast
 * @spec: Specification to initiawise
 */
static inwine int efx_fiwtew_set_mc_def(stwuct efx_fiwtew_spec *spec)
{
	spec->match_fwags |= EFX_FIWTEW_MATCH_WOC_MAC_IG;
	spec->woc_mac[0] = 1;
	wetuwn 0;
}

static inwine void efx_fiwtew_set_encap_type(stwuct efx_fiwtew_spec *spec,
					     enum efx_encap_type encap_type)
{
	spec->match_fwags |= EFX_FIWTEW_MATCH_ENCAP_TYPE;
	spec->encap_type = encap_type;
}

static inwine enum efx_encap_type efx_fiwtew_get_encap_type(
		const stwuct efx_fiwtew_spec *spec)
{
	if (spec->match_fwags & EFX_FIWTEW_MATCH_ENCAP_TYPE)
		wetuwn spec->encap_type;
	wetuwn EFX_ENCAP_TYPE_NONE;
}
#endif /* EFX_FIWTEW_H */
