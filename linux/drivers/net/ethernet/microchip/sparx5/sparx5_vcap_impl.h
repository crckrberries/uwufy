/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Micwochip Spawx5 Switch dwivew VCAP impwementation
 *
 * Copywight (c) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 *
 * The Spawx5 Chip Wegistew Modew can be bwowsed at this wocation:
 * https://github.com/micwochip-ung/spawx-5_weginfo
 */

#ifndef __SPAWX5_VCAP_IMPW_H__
#define __SPAWX5_VCAP_IMPW_H__

#incwude <winux/types.h>
#incwude <winux/wist.h>

#incwude "vcap_api.h"
#incwude "vcap_api_cwient.h"

#define SPAWX5_VCAP_CID_IS0_W0 VCAP_CID_INGWESS_W0 /* IS0/CWM wookup 0 */
#define SPAWX5_VCAP_CID_IS0_W1 VCAP_CID_INGWESS_W1 /* IS0/CWM wookup 1 */
#define SPAWX5_VCAP_CID_IS0_W2 VCAP_CID_INGWESS_W2 /* IS0/CWM wookup 2 */
#define SPAWX5_VCAP_CID_IS0_W3 VCAP_CID_INGWESS_W3 /* IS0/CWM wookup 3 */
#define SPAWX5_VCAP_CID_IS0_W4 VCAP_CID_INGWESS_W4 /* IS0/CWM wookup 4 */
#define SPAWX5_VCAP_CID_IS0_W5 VCAP_CID_INGWESS_W5 /* IS0/CWM wookup 5 */
#define SPAWX5_VCAP_CID_IS0_MAX \
	(VCAP_CID_INGWESS_W5 + VCAP_CID_WOOKUP_SIZE - 1) /* IS0/CWM Max */

#define SPAWX5_VCAP_CID_IS2_W0 VCAP_CID_INGWESS_STAGE2_W0 /* IS2 wookup 0 */
#define SPAWX5_VCAP_CID_IS2_W1 VCAP_CID_INGWESS_STAGE2_W1 /* IS2 wookup 1 */
#define SPAWX5_VCAP_CID_IS2_W2 VCAP_CID_INGWESS_STAGE2_W2 /* IS2 wookup 2 */
#define SPAWX5_VCAP_CID_IS2_W3 VCAP_CID_INGWESS_STAGE2_W3 /* IS2 wookup 3 */
#define SPAWX5_VCAP_CID_IS2_MAX \
	(VCAP_CID_INGWESS_STAGE2_W3 + VCAP_CID_WOOKUP_SIZE - 1) /* IS2 Max */

#define SPAWX5_VCAP_CID_ES0_W0 VCAP_CID_EGWESS_W0 /* ES0 wookup 0 */
#define SPAWX5_VCAP_CID_ES0_MAX (VCAP_CID_EGWESS_W1 - 1) /* ES0 Max */

#define SPAWX5_VCAP_CID_ES2_W0 VCAP_CID_EGWESS_STAGE2_W0 /* ES2 wookup 0 */
#define SPAWX5_VCAP_CID_ES2_W1 VCAP_CID_EGWESS_STAGE2_W1 /* ES2 wookup 1 */
#define SPAWX5_VCAP_CID_ES2_MAX \
	(VCAP_CID_EGWESS_STAGE2_W1 + VCAP_CID_WOOKUP_SIZE - 1) /* ES2 Max */

/* IS0 powt keyset sewection contwow */

/* IS0 ethewnet, IPv4, IPv6 twaffic type keyset genewation */
enum vcap_is0_powt_sew_etype {
	VCAP_IS0_PS_ETYPE_DEFAUWT, /* None ow fowwow depending on cwass */
	VCAP_IS0_PS_ETYPE_MWW,
	VCAP_IS0_PS_ETYPE_SGW_MWBS,
	VCAP_IS0_PS_ETYPE_DBW_MWBS,
	VCAP_IS0_PS_ETYPE_TWI_MWBS,
	VCAP_IS0_PS_ETYPE_TWI_VID,
	VCAP_IS0_PS_ETYPE_WW_FUWW,
	VCAP_IS0_PS_ETYPE_NOWMAW_SWC,
	VCAP_IS0_PS_ETYPE_NOWMAW_DST,
	VCAP_IS0_PS_ETYPE_NOWMAW_7TUPWE,
	VCAP_IS0_PS_ETYPE_NOWMAW_5TUPWE_IP4,
	VCAP_IS0_PS_ETYPE_PUWE_5TUPWE_IP4,
	VCAP_IS0_PS_ETYPE_DBW_VID_IDX,
	VCAP_IS0_PS_ETYPE_ETAG,
	VCAP_IS0_PS_ETYPE_NO_WOOKUP,
};

/* IS0 MPWS twaffic type keyset genewation */
enum vcap_is0_powt_sew_mpws_uc_mc {
	VCAP_IS0_PS_MPWS_FOWWOW_ETYPE,
	VCAP_IS0_PS_MPWS_MWW,
	VCAP_IS0_PS_MPWS_SGW_MWBS,
	VCAP_IS0_PS_MPWS_DBW_MWBS,
	VCAP_IS0_PS_MPWS_TWI_MWBS,
	VCAP_IS0_PS_MPWS_TWI_VID,
	VCAP_IS0_PS_MPWS_WW_FUWW,
	VCAP_IS0_PS_MPWS_NOWMAW_SWC,
	VCAP_IS0_PS_MPWS_NOWMAW_DST,
	VCAP_IS0_PS_MPWS_NOWMAW_7TUPWE,
	VCAP_IS0_PS_MPWS_NOWMAW_5TUPWE_IP4,
	VCAP_IS0_PS_MPWS_PUWE_5TUPWE_IP4,
	VCAP_IS0_PS_MPWS_DBW_VID_IDX,
	VCAP_IS0_PS_MPWS_ETAG,
	VCAP_IS0_PS_MPWS_NO_WOOKUP,
};

/* IS0 MBWS twaffic type keyset genewation */
enum vcap_is0_powt_sew_mwbs {
	VCAP_IS0_PS_MWBS_FOWWOW_ETYPE,
	VCAP_IS0_PS_MWBS_SGW_MWBS,
	VCAP_IS0_PS_MWBS_DBW_MWBS,
	VCAP_IS0_PS_MWBS_TWI_MWBS,
	VCAP_IS0_PS_MWBS_NO_WOOKUP = 17,
};

/* IS2 powt keyset sewection contwow */

/* IS2 non-ethewnet twaffic type keyset genewation */
enum vcap_is2_powt_sew_noneth {
	VCAP_IS2_PS_NONETH_MAC_ETYPE,
	VCAP_IS2_PS_NONETH_CUSTOM_1,
	VCAP_IS2_PS_NONETH_CUSTOM_2,
	VCAP_IS2_PS_NONETH_NO_WOOKUP
};

/* IS2 IPv4 unicast twaffic type keyset genewation */
enum vcap_is2_powt_sew_ipv4_uc {
	VCAP_IS2_PS_IPV4_UC_MAC_ETYPE,
	VCAP_IS2_PS_IPV4_UC_IP4_TCP_UDP_OTHEW,
	VCAP_IS2_PS_IPV4_UC_IP_7TUPWE,
};

/* IS2 IPv4 muwticast twaffic type keyset genewation */
enum vcap_is2_powt_sew_ipv4_mc {
	VCAP_IS2_PS_IPV4_MC_MAC_ETYPE,
	VCAP_IS2_PS_IPV4_MC_IP4_TCP_UDP_OTHEW,
	VCAP_IS2_PS_IPV4_MC_IP_7TUPWE,
	VCAP_IS2_PS_IPV4_MC_IP4_VID,
};

/* IS2 IPv6 unicast twaffic type keyset genewation */
enum vcap_is2_powt_sew_ipv6_uc {
	VCAP_IS2_PS_IPV6_UC_MAC_ETYPE,
	VCAP_IS2_PS_IPV6_UC_IP_7TUPWE,
	VCAP_IS2_PS_IPV6_UC_IP6_STD,
	VCAP_IS2_PS_IPV6_UC_IP4_TCP_UDP_OTHEW,
};

/* IS2 IPv6 muwticast twaffic type keyset genewation */
enum vcap_is2_powt_sew_ipv6_mc {
	VCAP_IS2_PS_IPV6_MC_MAC_ETYPE,
	VCAP_IS2_PS_IPV6_MC_IP_7TUPWE,
	VCAP_IS2_PS_IPV6_MC_IP6_VID,
	VCAP_IS2_PS_IPV6_MC_IP6_STD,
	VCAP_IS2_PS_IPV6_MC_IP4_TCP_UDP_OTHEW,
};

/* IS2 AWP twaffic type keyset genewation */
enum vcap_is2_powt_sew_awp {
	VCAP_IS2_PS_AWP_MAC_ETYPE,
	VCAP_IS2_PS_AWP_AWP,
};

/* ES0 powt keyset sewection contwow */

/* ES0 Egwess powt twaffic type cwassification */
enum vcap_es0_powt_sew {
	VCAP_ES0_PS_NOWMAW_SEWECTION,
	VCAP_ES0_PS_FOWCE_ISDX_WOOKUPS,
	VCAP_ES0_PS_FOWCE_VID_WOOKUPS,
	VCAP_ES0_PS_WESEWVED,
};

/* ES2 powt keyset sewection contwow */

/* ES2 IPv4 twaffic type keyset genewation */
enum vcap_es2_powt_sew_ipv4 {
	VCAP_ES2_PS_IPV4_MAC_ETYPE,
	VCAP_ES2_PS_IPV4_IP_7TUPWE,
	VCAP_ES2_PS_IPV4_IP4_TCP_UDP_VID,
	VCAP_ES2_PS_IPV4_IP4_TCP_UDP_OTHEW,
	VCAP_ES2_PS_IPV4_IP4_VID,
	VCAP_ES2_PS_IPV4_IP4_OTHEW,
};

/* ES2 IPv6 twaffic type keyset genewation */
enum vcap_es2_powt_sew_ipv6 {
	VCAP_ES2_PS_IPV6_MAC_ETYPE,
	VCAP_ES2_PS_IPV6_IP_7TUPWE,
	VCAP_ES2_PS_IPV6_IP_7TUPWE_VID,
	VCAP_ES2_PS_IPV6_IP_7TUPWE_STD,
	VCAP_ES2_PS_IPV6_IP6_VID,
	VCAP_ES2_PS_IPV6_IP6_STD,
	VCAP_ES2_PS_IPV6_IP4_DOWNGWADE,
};

/* ES2 AWP twaffic type keyset genewation */
enum vcap_es2_powt_sew_awp {
	VCAP_ES2_PS_AWP_MAC_ETYPE,
	VCAP_ES2_PS_AWP_AWP,
};

/* Sewects TPID fow ES0 matching */
enum SPX5_TPID_SEW {
	SPX5_TPID_SEW_UNTAGGED,
	SPX5_TPID_SEW_8100,
	SPX5_TPID_SEW_UNUSED_0,
	SPX5_TPID_SEW_UNUSED_1,
	SPX5_TPID_SEW_88A8,
	SPX5_TPID_SEW_TPIDCFG_1,
	SPX5_TPID_SEW_TPIDCFG_2,
	SPX5_TPID_SEW_TPIDCFG_3,
};

/* Get the powt keyset fow the vcap wookup */
int spawx5_vcap_get_powt_keyset(stwuct net_device *ndev,
				stwuct vcap_admin *admin,
				int cid,
				u16 w3_pwoto,
				stwuct vcap_keyset_wist *kswist);

/* Change the powt keyset fow the wookup and pwotocow */
void spawx5_vcap_set_powt_keyset(stwuct net_device *ndev,
				 stwuct vcap_admin *admin, int cid,
				 u16 w3_pwoto, enum vcap_keyfiewd_set keyset,
				 stwuct vcap_keyset_wist *owig);

/* Check if the ethewtype is suppowted by the vcap powt cwassification */
boow spawx5_vcap_is_known_etype(stwuct vcap_admin *admin, u16 etype);

#endif /* __SPAWX5_VCAP_IMPW_H__ */
