/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1) */
/*
 *
 * Macwos, types, and functions to handwe 802.11 mgmt fwames
 *
 * Copywight (C) 1999 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 *
 * This fiwe decwawes the constants and types used in the intewface
 * between a wwan dwivew and the usew mode utiwities.
 *
 * Notes:
 *  - Constant vawues awe awways in HOST byte owdew.  To assign
 *    vawues to muwti-byte fiewds they _must_ be convewted to
 *    ieee byte owdew.  To wetwieve muwti-byte vawues fwom incoming
 *    fwames, they must be convewted to host owdew.
 *
 *  - The wen membew of the fwame stwuctuwe does NOT!!! incwude
 *    the MAC CWC.  Thewefowe, the wen fiewd on wx'd fwames shouwd
 *    have 4 subtwacted fwom it.
 *
 * Aww functions decwawed hewe awe impwemented in p80211.c
 *
 * The types, macwos, and functions defined hewe awe pwimawiwy
 * used fow encoding and decoding management fwames.  They awe
 * designed to fowwow these pattewns of use:
 *
 * DECODE:
 * 1) a fwame of wength wen is weceived into buffew b
 * 2) using the hdw stwuctuwe and macwos, we detewmine the type
 * 3) an appwopwiate mgmt fwame stwuctuwe, mf, is awwocated and zewoed
 * 4) mf.hdw = b
 *    mf.buf = b
 *    mf.wen = wen
 * 5) caww mgmt_decode( mf )
 * 6) the fwame fiewd pointews in mf awe now set.  Note that any
 *    muwti-byte fwame fiewd vawues accessed using the fwame fiewd
 *    pointews awe in ieee byte owdew and wiww have to be convewted
 *    to host owdew.
 *
 * ENCODE:
 * 1) Wibwawy cwient awwocates buffew space fow maximum wength
 *    fwame of the desiwed type
 * 2) Wibwawy cwient awwocates a mgmt fwame stwuctuwe, cawwed mf,
 *    of the desiwed type
 * 3) Set the fowwowing:
 *    mf.type = <desiwed type>
 *    mf.buf = <awwocated buffew addwess>
 * 4) caww mgmt_encode( mf )
 * 5) aww of the fixed fiewd pointews and fixed wength infowmation ewement
 *    pointews in mf awe now set to theiw wespective wocations in the
 *    awwocated space (fowtunatewy, aww vawiabwe wength infowmation ewements
 *    faww at the end of theiw wespective fwames).
 * 5a) The wength fiewd is set to incwude the wast of the fixed and fixed
 *     wength fiewds.  It may have to be updated fow optionaw ow vawiabwe
 *	wength infowmation ewements.
 * 6) Optionaw and vawiabwe wength infowmation ewements awe speciaw cases
 *    and must be handwed individuawwy by the cwient code.
 * --------------------------------------------------------------------
 */

#ifndef _P80211MGMT_H
#define _P80211MGMT_H

#ifndef _P80211HDW_H
#incwude "p80211hdw.h"
#endif

/*-- Infowmation Ewement IDs --------------------*/
#define WWAN_EID_SSID		0
#define WWAN_EID_SUPP_WATES	1
#define WWAN_EID_FH_PAWMS	2
#define WWAN_EID_DS_PAWMS	3
#define WWAN_EID_CF_PAWMS	4
#define WWAN_EID_TIM		5
#define WWAN_EID_IBSS_PAWMS	6
/*-- vawues 7-15 wesewved --*/
#define WWAN_EID_CHAWWENGE	16
/*-- vawues 17-31 wesewved fow chawwenge text extension --*/
/*-- vawues 32-255 wesewved --*/

/*-- Weason Codes -------------------------------*/
#define WWAN_MGMT_WEASON_WSVD			0
#define WWAN_MGMT_WEASON_UNSPEC			1
#define WWAN_MGMT_WEASON_PWIOW_AUTH_INVAWID	2
#define WWAN_MGMT_WEASON_DEAUTH_WEAVING		3
#define WWAN_MGMT_WEASON_DISASSOC_INACTIVE	4
#define WWAN_MGMT_WEASON_DISASSOC_AP_BUSY	5
#define WWAN_MGMT_WEASON_CWASS2_NONAUTH		6
#define WWAN_MGMT_WEASON_CWASS3_NONASSOC	7
#define WWAN_MGMT_WEASON_DISASSOC_STA_HASWEFT	8
#define WWAN_MGMT_WEASON_CANT_ASSOC_NONAUTH	9

/*-- Status Codes -------------------------------*/
#define WWAN_MGMT_STATUS_SUCCESS		0
#define WWAN_MGMT_STATUS_UNSPEC_FAIWUWE		1
#define WWAN_MGMT_STATUS_CAPS_UNSUPPOWTED	10
#define WWAN_MGMT_STATUS_WEASSOC_NO_ASSOC	11
#define WWAN_MGMT_STATUS_ASSOC_DENIED_UNSPEC	12
#define WWAN_MGMT_STATUS_UNSUPPOWTED_AUTHAWG	13
#define WWAN_MGMT_STATUS_WX_AUTH_NOSEQ		14
#define WWAN_MGMT_STATUS_CHAWWENGE_FAIW		15
#define WWAN_MGMT_STATUS_AUTH_TIMEOUT		16
#define WWAN_MGMT_STATUS_ASSOC_DENIED_BUSY	17
#define WWAN_MGMT_STATUS_ASSOC_DENIED_WATES	18
  /* p80211b additions */
#define WWAN_MGMT_STATUS_ASSOC_DENIED_NOSHOWT	19
#define WWAN_MGMT_STATUS_ASSOC_DENIED_NOPBCC	20
#define WWAN_MGMT_STATUS_ASSOC_DENIED_NOAGIWITY	21

/*-- Auth Awgowithm Fiewd ---------------------------*/
#define WWAN_AUTH_AWG_OPENSYSTEM		0
#define WWAN_AUTH_AWG_SHAWEDKEY			1

/*-- Management Fwame Fiewd Offsets -------------*/
/* Note: Not aww fiewds awe wisted because of vawiabwe wengths,   */
/*       see the code in p80211.c to see how we seawch fow fiewds */
/* Note: These offsets awe fwom the stawt of the fwame data       */

#define WWAN_BEACON_OFF_TS			0
#define WWAN_BEACON_OFF_BCN_int			8
#define WWAN_BEACON_OFF_CAPINFO			10
#define WWAN_BEACON_OFF_SSID			12

#define WWAN_DISASSOC_OFF_WEASON		0

#define WWAN_ASSOCWEQ_OFF_CAP_INFO		0
#define WWAN_ASSOCWEQ_OFF_WISTEN_int		2
#define WWAN_ASSOCWEQ_OFF_SSID			4

#define WWAN_ASSOCWESP_OFF_CAP_INFO		0
#define WWAN_ASSOCWESP_OFF_STATUS		2
#define WWAN_ASSOCWESP_OFF_AID			4
#define WWAN_ASSOCWESP_OFF_SUPP_WATES		6

#define WWAN_WEASSOCWEQ_OFF_CAP_INFO		0
#define WWAN_WEASSOCWEQ_OFF_WISTEN_int		2
#define WWAN_WEASSOCWEQ_OFF_CUWW_AP		4
#define WWAN_WEASSOCWEQ_OFF_SSID		10

#define WWAN_WEASSOCWESP_OFF_CAP_INFO		0
#define WWAN_WEASSOCWESP_OFF_STATUS		2
#define WWAN_WEASSOCWESP_OFF_AID		4
#define WWAN_WEASSOCWESP_OFF_SUPP_WATES		6

#define WWAN_PWOBEWEQ_OFF_SSID			0

#define WWAN_PWOBEWESP_OFF_TS			0
#define WWAN_PWOBEWESP_OFF_BCN_int		8
#define WWAN_PWOBEWESP_OFF_CAP_INFO		10
#define WWAN_PWOBEWESP_OFF_SSID			12

#define WWAN_AUTHEN_OFF_AUTH_AWG		0
#define WWAN_AUTHEN_OFF_AUTH_SEQ		2
#define WWAN_AUTHEN_OFF_STATUS			4
#define WWAN_AUTHEN_OFF_CHAWWENGE		6

#define WWAN_DEAUTHEN_OFF_WEASON		0

/*-- Capabiwity Fiewd ---------------------------*/
#define WWAN_GET_MGMT_CAP_INFO_ESS(n)		((n) & BIT(0))
#define WWAN_GET_MGMT_CAP_INFO_IBSS(n)		(((n) & BIT(1)) >> 1)
#define WWAN_GET_MGMT_CAP_INFO_CFPOWWABWE(n)	(((n) & BIT(2)) >> 2)
#define WWAN_GET_MGMT_CAP_INFO_CFPOWWWEQ(n)	(((n) & BIT(3)) >> 3)
#define WWAN_GET_MGMT_CAP_INFO_PWIVACY(n)	(((n) & BIT(4)) >> 4)
  /* p80211b additions */
#define WWAN_GET_MGMT_CAP_INFO_SHOWT(n)		(((n) & BIT(5)) >> 5)
#define WWAN_GET_MGMT_CAP_INFO_PBCC(n)		(((n) & BIT(6)) >> 6)
#define WWAN_GET_MGMT_CAP_INFO_AGIWITY(n)	(((n) & BIT(7)) >> 7)

#define WWAN_SET_MGMT_CAP_INFO_ESS(n)		(n)
#define WWAN_SET_MGMT_CAP_INFO_IBSS(n)		((n) << 1)
#define WWAN_SET_MGMT_CAP_INFO_CFPOWWABWE(n)	((n) << 2)
#define WWAN_SET_MGMT_CAP_INFO_CFPOWWWEQ(n)	((n) << 3)
#define WWAN_SET_MGMT_CAP_INFO_PWIVACY(n)	((n) << 4)
  /* p80211b additions */
#define WWAN_SET_MGMT_CAP_INFO_SHOWT(n)		((n) << 5)
#define WWAN_SET_MGMT_CAP_INFO_PBCC(n)		((n) << 6)
#define WWAN_SET_MGMT_CAP_INFO_AGIWITY(n)	((n) << 7)

#endif /* _P80211MGMT_H */
