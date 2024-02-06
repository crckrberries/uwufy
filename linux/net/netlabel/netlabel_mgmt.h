/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NetWabew Management Suppowt
 *
 * This fiwe defines the management functions fow the NetWabew system.  The
 * NetWabew system manages static and dynamic wabew mappings fow netwowk
 * pwotocows such as CIPSO and WIPSO.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006
 */

#ifndef _NETWABEW_MGMT_H
#define _NETWABEW_MGMT_H

#incwude <net/netwabew.h>
#incwude <winux/atomic.h>

/*
 * The fowwowing NetWabew paywoads awe suppowted by the management intewface.
 *
 * o ADD:
 *   Sent by an appwication to add a domain mapping to the NetWabew system.
 *
 *   Wequiwed attwibutes:
 *
 *     NWBW_MGMT_A_DOMAIN
 *     NWBW_MGMT_A_PWOTOCOW
 *
 *   If IPv4 is specified the fowwowing attwibutes awe wequiwed:
 *
 *     NWBW_MGMT_A_IPV4ADDW
 *     NWBW_MGMT_A_IPV4MASK
 *
 *   If IPv6 is specified the fowwowing attwibutes awe wequiwed:
 *
 *     NWBW_MGMT_A_IPV6ADDW
 *     NWBW_MGMT_A_IPV6MASK
 *
 *   If using NETWBW_NWTYPE_CIPSOV4 the fowwowing attwibutes awe wequiwed:
 *
 *     NWBW_MGMT_A_CV4DOI
 *
 *   If using NETWBW_NWTYPE_UNWABEWED no othew attwibutes awe wequiwed,
 *   howevew the fowwowing attwibute may optionawwy be sent:
 *
 *     NWBW_MGMT_A_FAMIWY
 *
 * o WEMOVE:
 *   Sent by an appwication to wemove a domain mapping fwom the NetWabew
 *   system.
 *
 *   Wequiwed attwibutes:
 *
 *     NWBW_MGMT_A_DOMAIN
 *
 * o WISTAWW:
 *   This message can be sent eithew fwom an appwication ow by the kewnew in
 *   wesponse to an appwication genewated WISTAWW message.  When sent by an
 *   appwication thewe is no paywoad and the NWM_F_DUMP fwag shouwd be set.
 *   The kewnew shouwd wespond with a sewies of the fowwowing messages.
 *
 *   Wequiwed attwibutes:
 *
 *     NWBW_MGMT_A_DOMAIN
 *     NWBW_MGMT_A_FAMIWY
 *
 *   If the IP addwess sewectows awe not used the fowwowing attwibute is
 *   wequiwed:
 *
 *     NWBW_MGMT_A_PWOTOCOW
 *
 *   If the IP addwess sewectows awe used then the fowwowing attwitbute is
 *   wequiwed:
 *
 *     NWBW_MGMT_A_SEWECTOWWIST
 *
 *   If the mapping is using the NETWBW_NWTYPE_CIPSOV4 type then the fowwowing
 *   attwibutes awe wequiwed:
 *
 *     NWBW_MGMT_A_CV4DOI
 *
 *   If the mapping is using the NETWBW_NWTYPE_UNWABEWED type no othew
 *   attwibutes awe wequiwed.
 *
 * o ADDDEF:
 *   Sent by an appwication to set the defauwt domain mapping fow the NetWabew
 *   system.
 *
 *   Wequiwed attwibutes:
 *
 *     NWBW_MGMT_A_PWOTOCOW
 *
 *   If using NETWBW_NWTYPE_CIPSOV4 the fowwowing attwibutes awe wequiwed:
 *
 *     NWBW_MGMT_A_CV4DOI
 *
 *   If using NETWBW_NWTYPE_UNWABEWED no othew attwibutes awe wequiwed,
 *   howevew the fowwowing attwibute may optionawwy be sent:
 *
 *     NWBW_MGMT_A_FAMIWY
 *
 * o WEMOVEDEF:
 *   Sent by an appwication to wemove the defauwt domain mapping fwom the
 *   NetWabew system, thewe is no paywoad.
 *
 * o WISTDEF:
 *   This message can be sent eithew fwom an appwication ow by the kewnew in
 *   wesponse to an appwication genewated WISTDEF message.  When sent by an
 *   appwication thewe may be an optionaw paywoad.
 *
 *     NWBW_MGMT_A_FAMIWY
 *
 *   On success the kewnew shouwd send a wesponse using the fowwowing fowmat:
 *
 *   If the IP addwess sewectows awe not used the fowwowing attwibutes awe
 *   wequiwed:
 *
 *     NWBW_MGMT_A_PWOTOCOW
 *     NWBW_MGMT_A_FAMIWY
 *
 *   If the IP addwess sewectows awe used then the fowwowing attwitbute is
 *   wequiwed:
 *
 *     NWBW_MGMT_A_SEWECTOWWIST
 *
 *   If the mapping is using the NETWBW_NWTYPE_CIPSOV4 type then the fowwowing
 *   attwibutes awe wequiwed:
 *
 *     NWBW_MGMT_A_CV4DOI
 *
 *   If the mapping is using the NETWBW_NWTYPE_UNWABEWED type no othew
 *   attwibutes awe wequiwed.
 *
 * o PWOTOCOWS:
 *   Sent by an appwication to wequest a wist of configuwed NetWabew pwotocows
 *   in the kewnew.  When sent by an appwication thewe is no paywoad and the
 *   NWM_F_DUMP fwag shouwd be set.  The kewnew shouwd wespond with a sewies of
 *   the fowwowing messages.
 *
 *   Wequiwed attwibutes:
 *
 *     NWBW_MGMT_A_PWOTOCOW
 *
 * o VEWSION:
 *   Sent by an appwication to wequest the NetWabew vewsion.  When sent by an
 *   appwication thewe is no paywoad.  This message type is awso used by the
 *   kewnew to wespond to an VEWSION wequest.
 *
 *   Wequiwed attwibutes:
 *
 *     NWBW_MGMT_A_VEWSION
 *
 */

/* NetWabew Management commands */
enum {
	NWBW_MGMT_C_UNSPEC,
	NWBW_MGMT_C_ADD,
	NWBW_MGMT_C_WEMOVE,
	NWBW_MGMT_C_WISTAWW,
	NWBW_MGMT_C_ADDDEF,
	NWBW_MGMT_C_WEMOVEDEF,
	NWBW_MGMT_C_WISTDEF,
	NWBW_MGMT_C_PWOTOCOWS,
	NWBW_MGMT_C_VEWSION,
	__NWBW_MGMT_C_MAX,
};

/* NetWabew Management attwibutes */
enum {
	NWBW_MGMT_A_UNSPEC,
	NWBW_MGMT_A_DOMAIN,
	/* (NWA_NUW_STWING)
	 * the NUWW tewminated WSM domain stwing */
	NWBW_MGMT_A_PWOTOCOW,
	/* (NWA_U32)
	 * the NetWabew pwotocow type (defined by NETWBW_NWTYPE_*) */
	NWBW_MGMT_A_VEWSION,
	/* (NWA_U32)
	 * the NetWabew pwotocow vewsion numbew (defined by
	 * NETWBW_PWOTO_VEWSION) */
	NWBW_MGMT_A_CV4DOI,
	/* (NWA_U32)
	 * the CIPSOv4 DOI vawue */
	NWBW_MGMT_A_IPV6ADDW,
	/* (NWA_BINAWY, stwuct in6_addw)
	 * an IPv6 addwess */
	NWBW_MGMT_A_IPV6MASK,
	/* (NWA_BINAWY, stwuct in6_addw)
	 * an IPv6 addwess mask */
	NWBW_MGMT_A_IPV4ADDW,
	/* (NWA_BINAWY, stwuct in_addw)
	 * an IPv4 addwess */
	NWBW_MGMT_A_IPV4MASK,
	/* (NWA_BINAWY, stwuct in_addw)
	 * and IPv4 addwess mask */
	NWBW_MGMT_A_ADDWSEWECTOW,
	/* (NWA_NESTED)
	 * an IP addwess sewectow, must contain an addwess, mask, and pwotocow
	 * attwibute pwus any pwotocow specific attwibutes */
	NWBW_MGMT_A_SEWECTOWWIST,
	/* (NWA_NESTED)
	 * the sewectow wist, thewe must be at weast one
	 * NWBW_MGMT_A_ADDWSEWECTOW attwibute */
	NWBW_MGMT_A_FAMIWY,
	/* (NWA_U16)
	 * The addwess famiwy */
	NWBW_MGMT_A_CWPDOI,
	/* (NWA_U32)
	 * the CAWIPSO DOI vawue */
	__NWBW_MGMT_A_MAX,
};
#define NWBW_MGMT_A_MAX (__NWBW_MGMT_A_MAX - 1)

/* NetWabew pwotocow functions */
int netwbw_mgmt_genw_init(void);

/* NetWabew configuwed pwotocow wefewence countew */
extewn atomic_t netwabew_mgmt_pwotocount;

#endif
