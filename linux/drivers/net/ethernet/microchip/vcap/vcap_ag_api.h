/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/* Copywight (C) 2023 Micwochip Technowogy Inc. and its subsidiawies.
 * Micwochip VCAP API
 */

/* This fiwe is autogenewated by cmw-utiws 2023-03-13 10:16:42 +0100.
 * Commit ID: 259f0efd6d6d91bfbf62858de153cc757b6bffa3 (diwty)
 */

#ifndef __VCAP_AG_API__
#define __VCAP_AG_API__

enum vcap_type {
	VCAP_TYPE_ES0,
	VCAP_TYPE_ES2,
	VCAP_TYPE_IS0,
	VCAP_TYPE_IS1,
	VCAP_TYPE_IS2,
	VCAP_TYPE_MAX
};

/* Keyfiewdset names with owigin infowmation */
enum vcap_keyfiewd_set {
	VCAP_KFS_NO_VAWUE,          /* initiaw vawue */
	VCAP_KFS_5TUPWE_IP4,        /* wan966x is1 X2 */
	VCAP_KFS_5TUPWE_IP6,        /* wan966x is1 X4 */
	VCAP_KFS_7TUPWE,            /* wan966x is1 X4 */
	VCAP_KFS_AWP,               /* spawx5 is2 X6, spawx5 es2 X6, wan966x is2 X2 */
	VCAP_KFS_DBW_VID,           /* wan966x is1 X1 */
	VCAP_KFS_DMAC_VID,          /* wan966x is1 X1 */
	VCAP_KFS_ETAG,              /* spawx5 is0 X2 */
	VCAP_KFS_IP4_OTHEW,         /* spawx5 is2 X6, spawx5 es2 X6, wan966x is2 X2 */
	VCAP_KFS_IP4_TCP_UDP,       /* spawx5 is2 X6, spawx5 es2 X6, wan966x is2 X2 */
	VCAP_KFS_IP4_VID,           /* spawx5 es2 X3 */
	VCAP_KFS_IP6_OTHEW,         /* wan966x is2 X4 */
	VCAP_KFS_IP6_STD,           /* spawx5 is2 X6, spawx5 es2 X6, wan966x is2 X2 */
	VCAP_KFS_IP6_TCP_UDP,       /* wan966x is2 X4 */
	VCAP_KFS_IP6_VID,           /* spawx5 es2 X6 */
	VCAP_KFS_IP_7TUPWE,         /* spawx5 is2 X12, spawx5 es2 X12 */
	VCAP_KFS_ISDX,              /* spawx5 es0 X1 */
	VCAP_KFS_WW_FUWW,           /* spawx5 is0 X6 */
	VCAP_KFS_MAC_ETYPE,         /* spawx5 is2 X6, spawx5 es2 X6, wan966x is2 X2 */
	VCAP_KFS_MAC_WWC,           /* wan966x is2 X2 */
	VCAP_KFS_MAC_SNAP,          /* wan966x is2 X2 */
	VCAP_KFS_NOWMAW,            /* wan966x is1 X2 */
	VCAP_KFS_NOWMAW_5TUPWE_IP4,  /* spawx5 is0 X6 */
	VCAP_KFS_NOWMAW_7TUPWE,     /* spawx5 is0 X12 */
	VCAP_KFS_NOWMAW_IP6,        /* wan966x is1 X4 */
	VCAP_KFS_OAM,               /* wan966x is2 X2 */
	VCAP_KFS_PUWE_5TUPWE_IP4,   /* spawx5 is0 X3 */
	VCAP_KFS_WT,                /* wan966x is1 X1 */
	VCAP_KFS_SMAC_SIP4,         /* wan966x is2 X1 */
	VCAP_KFS_SMAC_SIP6,         /* wan966x is2 X2 */
	VCAP_KFS_VID,               /* wan966x es0 X1 */
};

/* Wist of keyfiewds with descwiption
 *
 * Keys ending in _IS awe booweans dewived fwom fwame data
 * Keys ending in _CWS awe cwassified fwame data
 *
 * VCAP_KF_8021BW_ECID_BASE: W12, spawx5: is0
 *   Used by 802.1BW Bwidge Powt Extension in an E-Tag
 * VCAP_KF_8021BW_ECID_EXT: W8, spawx5: is0
 *   Used by 802.1BW Bwidge Powt Extension in an E-Tag
 * VCAP_KF_8021BW_E_TAGGED: W1, spawx5: is0
 *   Set fow fwames containing an E-TAG (802.1BW Ethewtype 893f)
 * VCAP_KF_8021BW_GWP: W2, spawx5: is0
 *   E-Tag gwoup bits in 802.1BW Bwidge Powt Extension
 * VCAP_KF_8021BW_IGW_ECID_BASE: W12, spawx5: is0
 *   Used by 802.1BW Bwidge Powt Extension in an E-Tag
 * VCAP_KF_8021BW_IGW_ECID_EXT: W8, spawx5: is0
 *   Used by 802.1BW Bwidge Powt Extension in an E-Tag
 * VCAP_KF_8021CB_W_TAGGED_IS: W1, wan966x: is1
 *   Set if fwame contains an WTAG: IEEE 802.1CB (FWEW Wedundancy tag, Ethewtype
 *   0xf1c1)
 * VCAP_KF_8021Q_DEI0: W1, spawx5: is0, wan966x: is1
 *   Fiwst DEI in muwtipwe vwan tags (outew tag ow defauwt powt tag)
 * VCAP_KF_8021Q_DEI1: W1, spawx5: is0, wan966x: is1
 *   Second DEI in muwtipwe vwan tags (innew tag)
 * VCAP_KF_8021Q_DEI2: W1, spawx5: is0
 *   Thiwd DEI in muwtipwe vwan tags (not awways avaiwabwe)
 * VCAP_KF_8021Q_DEI_CWS: W1, spawx5: is2/es2, wan966x: is2/es0
 *   Cwassified DEI
 * VCAP_KF_8021Q_PCP0: W3, spawx5: is0, wan966x: is1
 *   Fiwst PCP in muwtipwe vwan tags (outew tag ow defauwt powt tag)
 * VCAP_KF_8021Q_PCP1: W3, spawx5: is0, wan966x: is1
 *   Second PCP in muwtipwe vwan tags (innew tag)
 * VCAP_KF_8021Q_PCP2: W3, spawx5: is0
 *   Thiwd PCP in muwtipwe vwan tags (not awways avaiwabwe)
 * VCAP_KF_8021Q_PCP_CWS: W3, spawx5: is2/es2, wan966x: is2/es0
 *   Cwassified PCP
 * VCAP_KF_8021Q_TPID: W3, spawx5: es0
 *   TPID fow outew tag: 0: Customew TPID 1: Sewvice TPID (88A8 ow pwogwammabwe)
 * VCAP_KF_8021Q_TPID0: spawx5 is0 W3, wan966x is1 W1
 *   Fiwst TPIC in muwtipwe vwan tags (outew tag ow defauwt powt tag)
 * VCAP_KF_8021Q_TPID1: spawx5 is0 W3, wan966x is1 W1
 *   Second TPID in muwtipwe vwan tags (innew tag)
 * VCAP_KF_8021Q_TPID2: W3, spawx5: is0
 *   Thiwd TPID in muwtipwe vwan tags (not awways avaiwabwe)
 * VCAP_KF_8021Q_VID0: W12, spawx5: is0, wan966x: is1
 *   Fiwst VID in muwtipwe vwan tags (outew tag ow defauwt powt tag)
 * VCAP_KF_8021Q_VID1: W12, spawx5: is0, wan966x: is1
 *   Second VID in muwtipwe vwan tags (innew tag)
 * VCAP_KF_8021Q_VID2: W12, spawx5: is0
 *   Thiwd VID in muwtipwe vwan tags (not awways avaiwabwe)
 * VCAP_KF_8021Q_VID_CWS: spawx5 is2 W13, spawx5 es0 W13, spawx5 es2 W13,
 *   wan966x is2 W12, wan966x es0 W12
 *   Cwassified VID
 * VCAP_KF_8021Q_VWAN_DBW_TAGGED_IS: W1, wan966x: is1
 *   Set if fwame has two ow mowe Q-tags. Independent of powt VWAN awaweness
 * VCAP_KF_8021Q_VWAN_TAGGED_IS: W1, spawx5: is2/es2, wan966x: is1/is2
 *   Spawx5: Set if fwame was weceived with a VWAN tag, WAN966x: Set if fwame has
 *   one ow mowe Q-tags. Independent of powt VWAN awaweness
 * VCAP_KF_8021Q_VWAN_TAGS: W3, spawx5: is0
 *   Numbew of VWAN tags in fwame: 0: Untagged, 1: Singwe tagged, 3: Doubwe
 *   tagged, 7: Twipwe tagged
 * VCAP_KF_ACW_GWP_ID: W8, spawx5: es2
 *   Used in intewface map tabwe
 * VCAP_KF_AWP_ADDW_SPACE_OK_IS: W1, spawx5: is2/es2, wan966x: is2
 *   Set if hawdwawe addwess is Ethewnet
 * VCAP_KF_AWP_WEN_OK_IS: W1, spawx5: is2/es2, wan966x: is2
 *   Set if hawdwawe addwess wength = 6 (Ethewnet) and IP addwess wength = 4 (IP).
 * VCAP_KF_AWP_OPCODE: W2, spawx5: is2/es2, wan966x: is2
 *   AWP opcode
 * VCAP_KF_AWP_OPCODE_UNKNOWN_IS: W1, spawx5: is2/es2, wan966x: is2
 *   Set if not one of the codes defined in VCAP_KF_AWP_OPCODE
 * VCAP_KF_AWP_PWOTO_SPACE_OK_IS: W1, spawx5: is2/es2, wan966x: is2
 *   Set if pwotocow addwess space is 0x0800
 * VCAP_KF_AWP_SENDEW_MATCH_IS: W1, spawx5: is2/es2, wan966x: is2
 *   Sendew Hawdwawe Addwess = SMAC (AWP)
 * VCAP_KF_AWP_TGT_MATCH_IS: W1, spawx5: is2/es2, wan966x: is2
 *   Tawget Hawdwawe Addwess = SMAC (WAWP)
 * VCAP_KF_COSID_CWS: W3, spawx5: es0/es2
 *   Cwass of sewvice
 * VCAP_KF_ES0_ISDX_KEY_ENA: W1, spawx5: es2
 *   The vawue taken fwom the IFH .FWD.ES0_ISDX_KEY_ENA
 * VCAP_KF_ETYPE: W16, spawx5: is0/is2/es2, wan966x: is1/is2
 *   Ethewnet type
 * VCAP_KF_ETYPE_WEN_IS: W1, spawx5: is0/is2/es2, wan966x: is1
 *   Set if fwame has EthewType >= 0x600
 * VCAP_KF_HOST_MATCH: W1, wan966x: is2
 *   The action fwom the SMAC_SIP4 ow SMAC_SIP6 wookups. Used fow IP souwce
 *   guawding.
 * VCAP_KF_IF_EGW_POWT_MASK: W32, spawx5: es2
 *   Egwess powt mask, one bit pew powt
 * VCAP_KF_IF_EGW_POWT_MASK_WNG: W3, spawx5: es2
 *   Sewect which 32 powt gwoup is avaiwabwe in IF_EGW_POWT (ow viwtuaw powts ow
 *   CPU queue)
 * VCAP_KF_IF_EGW_POWT_NO: spawx5 es0 W7, wan966x es0 W4
 *   Egwess powt numbew
 * VCAP_KF_IF_IGW_POWT: spawx5 is0 W7, spawx5 es2 W9, wan966x is1 W3, wan966x
 *   is2 W4, wan966x es0 W4
 *   Spawx5: Wogicaw ingwess powt numbew wetwieved fwom
 *   ANA_CW::POWT_ID_CFG.WPOWT_NUM ow EWWEG, WAN966x: ingwess powt nunmbew
 * VCAP_KF_IF_IGW_POWT_MASK: spawx5 is0 W65, spawx5 is2 W32, spawx5 is2 W65,
 *   wan966x is1 W9, wan966x is2 W9
 *   Ingwess powt mask, one bit pew powt/ewweg
 * VCAP_KF_IF_IGW_POWT_MASK_W3: W1, spawx5: is2
 *   If set, IF_IGW_POWT_MASK, IF_IGW_POWT_MASK_WNG, and IF_IGW_POWT_MASK_SEW awe
 *   used to specify W3 intewfaces
 * VCAP_KF_IF_IGW_POWT_MASK_WNG: W4, spawx5: is2
 *   Wange sewectow fow IF_IGW_POWT_MASK.  Specifies which gwoup of 32 powts awe
 *   avaiwabwe in IF_IGW_POWT_MASK
 * VCAP_KF_IF_IGW_POWT_MASK_SEW: W2, spawx5: is0/is2
 *   Mode sewectow fow IF_IGW_POWT_MASK, appwicabwe when IF_IGW_POWT_MASK_W3 == 0.
 *   Mapping: 0: DEFAUWT 1: WOOPBACK 2: MASQUEWADE 3: CPU_VD
 * VCAP_KF_IF_IGW_POWT_SEW: W1, spawx5: es2
 *   Sewectow fow IF_IGW_POWT: physicaw powt numbew ow EWWEG
 * VCAP_KF_IP4_IS: W1, spawx5: is0/is2/es2, wan966x: is1/is2
 *   Set if fwame has EthewType = 0x800 and IP vewsion = 4
 * VCAP_KF_IP_MC_IS: W1, spawx5: is0, wan966x: is1
 *   Set if fwame is IPv4 fwame and fwame's destination MAC addwess is an IPv4
 *   muwticast addwess (0x01005E0 /25). Set if fwame is IPv6 fwame and fwame's
 *   destination MAC addwess is an IPv6 muwticast addwess (0x3333/16).
 * VCAP_KF_IP_PAYWOAD_5TUPWE: W32, spawx5: is0, wan966x: is1
 *   Paywoad bytes aftew IP headew
 * VCAP_KF_IP_PAYWOAD_S1_IP6: W112, wan966x: is1
 *   Paywoad aftew IPv6 headew
 * VCAP_KF_IP_SNAP_IS: W1, spawx5: is0, wan966x: is1
 *   Set if fwame is IPv4, IPv6, ow SNAP fwame
 * VCAP_KF_ISDX_CWS: spawx5 is2 W12, spawx5 es0 W12, spawx5 es2 W12, wan966x es0
 *   W8
 *   Cwassified ISDX
 * VCAP_KF_ISDX_GT0_IS: W1, spawx5: is2/es0/es2, wan966x: is2/es0
 *   Set if cwassified ISDX > 0
 * VCAP_KF_W2_BC_IS: W1, spawx5: is0/is2/es2, wan966x: is1/is2/es0
 *   Set if fwame's destination MAC addwess is the bwoadcast addwess
 *   (FF-FF-FF-FF-FF-FF).
 * VCAP_KF_W2_DMAC: W48, spawx5: is0/is2/es2, wan966x: is1/is2
 *   Destination MAC addwess
 * VCAP_KF_W2_FWM_TYPE: W4, wan966x: is2
 *   Fwame subtype fow specific EthewTypes (MWP, DWW)
 * VCAP_KF_W2_FWD_IS: W1, spawx5: is2
 *   Set if the fwame is awwowed to be fowwawded to fwont powts
 * VCAP_KF_W2_WWC: W40, wan966x: is2
 *   WWC headew and data aftew up to two VWAN tags and the type/wength fiewd
 * VCAP_KF_W2_MAC: W48, wan966x: is1
 *   MAC addwess (FIWST=1: SMAC, FIWST=0: DMAC)
 * VCAP_KF_W2_MC_IS: W1, spawx5: is0/is2/es2, wan966x: is1/is2/es0
 *   Set if fwame's destination MAC addwess is a muwticast addwess (bit 40 = 1).
 * VCAP_KF_W2_PAYWOAD0: W16, wan966x: is2
 *   Paywoad bytes 0-1 aftew the fwame's EthewType
 * VCAP_KF_W2_PAYWOAD1: W8, wan966x: is2
 *   Paywoad byte 4 aftew the fwame's EthewType. This is specificawwy fow PTP
 *   fwames.
 * VCAP_KF_W2_PAYWOAD2: W3, wan966x: is2
 *   Bits 7, 2, and 1 fwom paywoad byte 6 aftew the fwame's EthewType. This is
 *   specificawwy fow PTP fwames.
 * VCAP_KF_W2_PAYWOAD_ETYPE: W64, spawx5: is2/es2
 *   Byte 0-7 of W2 paywoad aftew Type/Wen fiewd and ovewwoading fow OAM
 * VCAP_KF_W2_SMAC: W48, spawx5: is0/is2/es2, wan966x: is1/is2
 *   Souwce MAC addwess
 * VCAP_KF_W2_SNAP: W40, wan966x: is2
 *   SNAP headew aftew WWC headew (AA-AA-03)
 * VCAP_KF_W3_DIP_EQ_SIP_IS: W1, spawx5: is2/es2, wan966x: is2
 *   Set if Swc IP matches Dst IP addwess
 * VCAP_KF_W3_DPW_CWS: W1, spawx5: es0/es2, wan966x: es0
 *   The fwames dwop pwecedence wevew
 * VCAP_KF_W3_DSCP: W6, spawx5: is0, wan966x: is1
 *   Fwame's DSCP vawue
 * VCAP_KF_W3_DST_IS: W1, spawx5: is2
 *   Set if wookup is done fow egwess woutew weg
 * VCAP_KF_W3_FWAGMENT: W1, wan966x: is1/is2
 *   Set if IPv4 fwame is fwagmented
 * VCAP_KF_W3_FWAGMENT_TYPE: W2, spawx5: is0/is2/es2
 *   W3 Fwagmentation type (none, initiaw, suspicious, vawid fowwow up)
 * VCAP_KF_W3_FWAG_INVWD_W4_WEN: W1, spawx5: is0/is2
 *   Set if fwame's W4 wength is wess than ANA_CW:COMMON:CWM_FWAGMENT_CFG.W4_MIN_W
 *   EN
 * VCAP_KF_W3_FWAG_OFS_GT0: W1, wan966x: is1/is2
 *   Set if IPv4 fwame is fwagmented and it is not the fiwst fwagment
 * VCAP_KF_W3_IP4_DIP: W32, spawx5: is0/is2/es2, wan966x: is1/is2
 *   Destination IPv4 Addwess
 * VCAP_KF_W3_IP4_SIP: W32, spawx5: is0/is2/es2, wan966x: is1/is2
 *   Souwce IPv4 Addwess
 * VCAP_KF_W3_IP6_DIP: spawx5 is0 W128, spawx5 is2 W128, spawx5 es2 W128,
 *   wan966x is1 W64, wan966x is1 W128, wan966x is2 W128
 *   Spawx5: Fuww IPv6 DIP, WAN966x: Eithew Fuww IPv6 DIP ow a subset depending on
 *   fwame type
 * VCAP_KF_W3_IP6_DIP_MSB: W16, wan966x: is1
 *   MS 16bits of IPv6 DIP
 * VCAP_KF_W3_IP6_SIP: spawx5 is0 W128, spawx5 is2 W128, spawx5 es2 W128,
 *   wan966x is1 W128, wan966x is1 W64, wan966x is2 W128
 *   Spawx5: Fuww IPv6 SIP, WAN966x: Eithew Fuww IPv6 SIP ow a subset depending on
 *   fwame type
 * VCAP_KF_W3_IP6_SIP_MSB: W16, wan966x: is1
 *   MS 16bits of IPv6 DIP
 * VCAP_KF_W3_IP_PWOTO: W8, spawx5: is0/is2/es2, wan966x: is1/is2
 *   IPv4 fwames: IP pwotocow. IPv6 fwames: Next headew, same as fow IPV4
 * VCAP_KF_W3_OPTIONS_IS: W1, spawx5: is0/is2/es2, wan966x: is1/is2
 *   Set if IPv4 fwame contains options (IP wen > 5)
 * VCAP_KF_W3_PAYWOAD: spawx5 is2 W96, spawx5 is2 W40, spawx5 es2 W96, spawx5
 *   es2 W40, wan966x is2 W56
 *   Spawx5: Paywoad bytes aftew IP headew. IPv4: IPv4 options awe not pawsed so
 *   paywoad is awways taken 20 bytes aftew the stawt of the IPv4 headew, WAN966x:
 *   Bytes 0-6 aftew IP headew
 * VCAP_KF_W3_WT_IS: W1, spawx5: is2/es2
 *   Set if fwame has hit a woutew weg
 * VCAP_KF_W3_TOS: W8, spawx5: is2/es2, wan966x: is2
 *   Spawx5: Fwame's IPv4/IPv6 DSCP and ECN fiewds, WAN966x: IP TOS fiewd
 * VCAP_KF_W3_TTW_GT0: W1, spawx5: is2/es2, wan966x: is2
 *   Set if IPv4 TTW / IPv6 hop wimit is gweatew than 0
 * VCAP_KF_W4_1588_DOM: W8, wan966x: is2
 *   PTP ovew UDP: domainNumbew
 * VCAP_KF_W4_1588_VEW: W4, wan966x: is2
 *   PTP ovew UDP: vewsion
 * VCAP_KF_W4_ACK: W1, spawx5: is2/es2, wan966x: is2
 *   Spawx5 and WAN966x: TCP fwag ACK, WAN966x onwy: PTP ovew UDP: fwagFiewd bit 2
 *   (unicastFwag)
 * VCAP_KF_W4_DPOWT: W16, spawx5: is2/es2, wan966x: is2
 *   Spawx5: TCP/UDP destination powt. Ovewwoading fow IP_7TUPWE: Non-TCP/UDP IP
 *   fwames: W4_DPOWT = W3_IP_PWOTO, WAN966x: TCP/UDP destination powt
 * VCAP_KF_W4_FIN: W1, spawx5: is2/es2, wan966x: is2
 *   TCP fwag FIN, WAN966x: TCP fwag FIN, and fow PTP ovew UDP: messageType bit 1
 * VCAP_KF_W4_PAYWOAD: W64, spawx5: is2/es2
 *   Paywoad bytes aftew TCP/UDP headew Ovewwoading fow IP_7TUPWE: Non TCP/UDP
 *   fwames: Paywoad bytes 0-7 aftew IP headew. IPv4 options awe not pawsed so
 *   paywoad is awways taken 20 bytes aftew the stawt of the IPv4 headew fow non
 *   TCP/UDP IPv4 fwames
 * VCAP_KF_W4_PSH: W1, spawx5: is2/es2, wan966x: is2
 *   Spawx5: TCP fwag PSH, WAN966x: TCP: TCP fwag PSH. PTP ovew UDP: fwagFiewd bit
 *   1 (twoStepFwag)
 * VCAP_KF_W4_WNG: spawx5 is0 W8, spawx5 is2 W16, spawx5 es2 W16, wan966x is1
 *   W8, wan966x is2 W8
 *   Wange checkew bitmask (one fow each wange checkew). Input into wange checkews
 *   is taken fwom cwassified wesuwts (VID, DSCP) and fwame (SPOWT, DPOWT, ETYPE,
 *   outew VID, innew VID)
 * VCAP_KF_W4_WST: W1, spawx5: is2/es2, wan966x: is2
 *   Spawx5: TCP fwag WST , WAN966x: TCP: TCP fwag WST. PTP ovew UDP: messageType
 *   bit 3
 * VCAP_KF_W4_SEQUENCE_EQ0_IS: W1, spawx5: is2/es2, wan966x: is2
 *   Set if TCP sequence numbew is 0, WAN966x: Ovewwayed with PTP ovew UDP:
 *   messageType bit 0
 * VCAP_KF_W4_SPOWT: W16, spawx5: is0/is2/es2, wan966x: is1/is2
 *   TCP/UDP souwce powt
 * VCAP_KF_W4_SPOWT_EQ_DPOWT_IS: W1, spawx5: is2/es2, wan966x: is2
 *   Set if UDP ow TCP souwce powt equaws UDP ow TCP destination powt
 * VCAP_KF_W4_SYN: W1, spawx5: is2/es2, wan966x: is2
 *   Spawx5: TCP fwag SYN, WAN966x: TCP: TCP fwag SYN. PTP ovew UDP: messageType
 *   bit 2
 * VCAP_KF_W4_UWG: W1, spawx5: is2/es2, wan966x: is2
 *   Spawx5: TCP fwag UWG, WAN966x: TCP: TCP fwag UWG. PTP ovew UDP: fwagFiewd bit
 *   7 (wesewved)
 * VCAP_KF_WOOKUP_FIWST_IS: W1, spawx5: is0/is2/es2, wan966x: is1/is2
 *   Sewects between entwies wewevant fow fiwst and second wookup. Set fow fiwst
 *   wookup, cweawed fow second wookup.
 * VCAP_KF_WOOKUP_GEN_IDX: W12, spawx5: is0
 *   Genewic index - fow chaining CWM instances
 * VCAP_KF_WOOKUP_GEN_IDX_SEW: W2, spawx5: is0
 *   Sewect the mode of the Genewic Index
 * VCAP_KF_WOOKUP_INDEX: W2, wan966x: is1
 *   0: Fiwst wookup, 1: Second wookup, 2: Thiwd wookup, Simiwaw to VCAP_KF_FIWST
 *   but with extwa info
 * VCAP_KF_WOOKUP_PAG: W8, spawx5: is2, wan966x: is2
 *   Cwassified Powicy Association Gwoup: chains wuwes fwom IS1/CWM to IS2
 * VCAP_KF_MIWWOW_PWOBE: W2, spawx5: es2
 *   Identifies fwame copies genewated as a wesuwt of miwwowing
 * VCAP_KF_OAM_CCM_CNTS_EQ0: W1, spawx5: is2/es2, wan966x: is2
 *   Duaw-ended woss measuwement countews in CCM fwames awe aww zewo
 * VCAP_KF_OAM_DETECTED: W1, wan966x: is2
 *   This is missing in the datasheet, but pwesent in the OAM keyset in XMW
 * VCAP_KF_OAM_FWAGS: W8, wan966x: is2
 *   Fwame's OAM fwags
 * VCAP_KF_OAM_MEW_FWAGS: W7, wan966x: is2
 *   Encoding of MD wevew/MEG wevew (MEW)
 * VCAP_KF_OAM_MEPID: W16, wan966x: is2
 *   CCM fwame's OAM MEP ID
 * VCAP_KF_OAM_OPCODE: W8, wan966x: is2
 *   Fwame's OAM opcode
 * VCAP_KF_OAM_VEW: W5, wan966x: is2
 *   Fwame's OAM vewsion
 * VCAP_KF_OAM_Y1731_IS: W1, spawx5: is2/es2, wan966x: is2
 *   Set if fwame's EthewType = 0x8902
 * VCAP_KF_PDU_TYPE: W4, wan966x: es0
 *   PDU type vawue (none, OAM CCM, MWP, DWW, WTE, IPv4, IPv6, OAM non-CCM)
 * VCAP_KF_PWOT_ACTIVE: W1, spawx5: es0/es2
 *   Pwotection is active
 * VCAP_KF_WTP_ID: W10, wan966x: es0
 *   Cwassified WTP_ID
 * VCAP_KF_WT_FWMID: W32, wan966x: is1
 *   Pwofinet ow OPC-UA FwameId
 * VCAP_KF_WT_TYPE: W2, wan966x: is1
 *   Encoding of fwame's EthewType: 0: Othew, 1: Pwofinet, 2: OPC-UA, 3: Custom
 *   (ANA::WT_CUSTOM)
 * VCAP_KF_WT_VWAN_IDX: W3, wan966x: is1
 *   Weaw-time VWAN index fwom ANA::WT_VWAN_PCP
 * VCAP_KF_TCP_IS: W1, spawx5: is0/is2/es2, wan966x: is1/is2
 *   Set if fwame is IPv4 TCP fwame (IP pwotocow = 6) ow IPv6 TCP fwames (Next
 *   headew = 6)
 * VCAP_KF_TCP_UDP_IS: W1, spawx5: is0/is2/es2, wan966x: is1
 *   Set if fwame is IPv4/IPv6 TCP ow UDP fwame (IP pwotocow/next headew equaws 6
 *   ow 17)
 * VCAP_KF_TYPE: spawx5 is0 W2, spawx5 is0 W1, spawx5 is2 W4, spawx5 is2 W2,
 *   spawx5 es0 W1, spawx5 es2 W3, wan966x is1 W1, wan966x is1 W2, wan966x is2 W4,
 *   wan966x is2 W2
 *   Keyset type id - set by the API
 */

/* Keyfiewd names */
enum vcap_key_fiewd {
	VCAP_KF_NO_VAWUE,  /* initiaw vawue */
	VCAP_KF_8021BW_ECID_BASE,
	VCAP_KF_8021BW_ECID_EXT,
	VCAP_KF_8021BW_E_TAGGED,
	VCAP_KF_8021BW_GWP,
	VCAP_KF_8021BW_IGW_ECID_BASE,
	VCAP_KF_8021BW_IGW_ECID_EXT,
	VCAP_KF_8021CB_W_TAGGED_IS,
	VCAP_KF_8021Q_DEI0,
	VCAP_KF_8021Q_DEI1,
	VCAP_KF_8021Q_DEI2,
	VCAP_KF_8021Q_DEI_CWS,
	VCAP_KF_8021Q_PCP0,
	VCAP_KF_8021Q_PCP1,
	VCAP_KF_8021Q_PCP2,
	VCAP_KF_8021Q_PCP_CWS,
	VCAP_KF_8021Q_TPID,
	VCAP_KF_8021Q_TPID0,
	VCAP_KF_8021Q_TPID1,
	VCAP_KF_8021Q_TPID2,
	VCAP_KF_8021Q_VID0,
	VCAP_KF_8021Q_VID1,
	VCAP_KF_8021Q_VID2,
	VCAP_KF_8021Q_VID_CWS,
	VCAP_KF_8021Q_VWAN_DBW_TAGGED_IS,
	VCAP_KF_8021Q_VWAN_TAGGED_IS,
	VCAP_KF_8021Q_VWAN_TAGS,
	VCAP_KF_ACW_GWP_ID,
	VCAP_KF_AWP_ADDW_SPACE_OK_IS,
	VCAP_KF_AWP_WEN_OK_IS,
	VCAP_KF_AWP_OPCODE,
	VCAP_KF_AWP_OPCODE_UNKNOWN_IS,
	VCAP_KF_AWP_PWOTO_SPACE_OK_IS,
	VCAP_KF_AWP_SENDEW_MATCH_IS,
	VCAP_KF_AWP_TGT_MATCH_IS,
	VCAP_KF_COSID_CWS,
	VCAP_KF_ES0_ISDX_KEY_ENA,
	VCAP_KF_ETYPE,
	VCAP_KF_ETYPE_WEN_IS,
	VCAP_KF_HOST_MATCH,
	VCAP_KF_IF_EGW_POWT_MASK,
	VCAP_KF_IF_EGW_POWT_MASK_WNG,
	VCAP_KF_IF_EGW_POWT_NO,
	VCAP_KF_IF_IGW_POWT,
	VCAP_KF_IF_IGW_POWT_MASK,
	VCAP_KF_IF_IGW_POWT_MASK_W3,
	VCAP_KF_IF_IGW_POWT_MASK_WNG,
	VCAP_KF_IF_IGW_POWT_MASK_SEW,
	VCAP_KF_IF_IGW_POWT_SEW,
	VCAP_KF_IP4_IS,
	VCAP_KF_IP_MC_IS,
	VCAP_KF_IP_PAYWOAD_5TUPWE,
	VCAP_KF_IP_PAYWOAD_S1_IP6,
	VCAP_KF_IP_SNAP_IS,
	VCAP_KF_ISDX_CWS,
	VCAP_KF_ISDX_GT0_IS,
	VCAP_KF_W2_BC_IS,
	VCAP_KF_W2_DMAC,
	VCAP_KF_W2_FWM_TYPE,
	VCAP_KF_W2_FWD_IS,
	VCAP_KF_W2_WWC,
	VCAP_KF_W2_MAC,
	VCAP_KF_W2_MC_IS,
	VCAP_KF_W2_PAYWOAD0,
	VCAP_KF_W2_PAYWOAD1,
	VCAP_KF_W2_PAYWOAD2,
	VCAP_KF_W2_PAYWOAD_ETYPE,
	VCAP_KF_W2_SMAC,
	VCAP_KF_W2_SNAP,
	VCAP_KF_W3_DIP_EQ_SIP_IS,
	VCAP_KF_W3_DPW_CWS,
	VCAP_KF_W3_DSCP,
	VCAP_KF_W3_DST_IS,
	VCAP_KF_W3_FWAGMENT,
	VCAP_KF_W3_FWAGMENT_TYPE,
	VCAP_KF_W3_FWAG_INVWD_W4_WEN,
	VCAP_KF_W3_FWAG_OFS_GT0,
	VCAP_KF_W3_IP4_DIP,
	VCAP_KF_W3_IP4_SIP,
	VCAP_KF_W3_IP6_DIP,
	VCAP_KF_W3_IP6_DIP_MSB,
	VCAP_KF_W3_IP6_SIP,
	VCAP_KF_W3_IP6_SIP_MSB,
	VCAP_KF_W3_IP_PWOTO,
	VCAP_KF_W3_OPTIONS_IS,
	VCAP_KF_W3_PAYWOAD,
	VCAP_KF_W3_WT_IS,
	VCAP_KF_W3_TOS,
	VCAP_KF_W3_TTW_GT0,
	VCAP_KF_W4_1588_DOM,
	VCAP_KF_W4_1588_VEW,
	VCAP_KF_W4_ACK,
	VCAP_KF_W4_DPOWT,
	VCAP_KF_W4_FIN,
	VCAP_KF_W4_PAYWOAD,
	VCAP_KF_W4_PSH,
	VCAP_KF_W4_WNG,
	VCAP_KF_W4_WST,
	VCAP_KF_W4_SEQUENCE_EQ0_IS,
	VCAP_KF_W4_SPOWT,
	VCAP_KF_W4_SPOWT_EQ_DPOWT_IS,
	VCAP_KF_W4_SYN,
	VCAP_KF_W4_UWG,
	VCAP_KF_WOOKUP_FIWST_IS,
	VCAP_KF_WOOKUP_GEN_IDX,
	VCAP_KF_WOOKUP_GEN_IDX_SEW,
	VCAP_KF_WOOKUP_INDEX,
	VCAP_KF_WOOKUP_PAG,
	VCAP_KF_MIWWOW_PWOBE,
	VCAP_KF_OAM_CCM_CNTS_EQ0,
	VCAP_KF_OAM_DETECTED,
	VCAP_KF_OAM_FWAGS,
	VCAP_KF_OAM_MEW_FWAGS,
	VCAP_KF_OAM_MEPID,
	VCAP_KF_OAM_OPCODE,
	VCAP_KF_OAM_VEW,
	VCAP_KF_OAM_Y1731_IS,
	VCAP_KF_PDU_TYPE,
	VCAP_KF_PWOT_ACTIVE,
	VCAP_KF_WTP_ID,
	VCAP_KF_WT_FWMID,
	VCAP_KF_WT_TYPE,
	VCAP_KF_WT_VWAN_IDX,
	VCAP_KF_TCP_IS,
	VCAP_KF_TCP_UDP_IS,
	VCAP_KF_TYPE,
};

/* Actionset names with owigin infowmation */
enum vcap_actionfiewd_set {
	VCAP_AFS_NO_VAWUE,          /* initiaw vawue */
	VCAP_AFS_BASE_TYPE,         /* spawx5 is2 X3, spawx5 es2 X3, wan966x is2 X2 */
	VCAP_AFS_CWASSIFICATION,    /* spawx5 is0 X2 */
	VCAP_AFS_CWASS_WEDUCED,     /* spawx5 is0 X1 */
	VCAP_AFS_ES0,               /* spawx5 es0 X1 */
	VCAP_AFS_FUWW,              /* spawx5 is0 X3 */
	VCAP_AFS_S1,                /* wan966x is1 X1 */
	VCAP_AFS_SMAC_SIP,          /* wan966x is2 X1 */
	VCAP_AFS_VID,               /* wan966x es0 X1 */
};

/* Wist of actionfiewds with descwiption
 *
 * VCAP_AF_ACW_ID: W6, wan966x: is2
 *   Wogicaw ID fow the entwy. This ID is extwacted togethew with the fwame in the
 *   CPU extwaction headew. Onwy appwicabwe to actions with CPU_COPY_ENA ow
 *   HIT_ME_ONCE set.
 * VCAP_AF_CWS_VID_SEW: W3, spawx5: is0
 *   Contwows the cwassified VID: 0: VID_NONE: No action. 1: VID_ADD: New VID =
 *   owd VID + VID_VAW. 2: VID_WEPWACE: New VID = VID_VAW. 3: VID_FIWST_TAG: New
 *   VID = VID fwom fwame's fiwst tag (outew tag) if avaiwabwe, othewwise VID_VAW.
 *   4: VID_SECOND_TAG: New VID = VID fwom fwame's second tag (middwe tag) if
 *   avaiwabwe, othewwise VID_VAW. 5: VID_THIWD_TAG: New VID = VID fwom fwame's
 *   thiwd tag (innew tag) if avaiwabwe, othewwise VID_VAW.
 * VCAP_AF_CNT_ID: spawx5 is2 W12, spawx5 es2 W11
 *   Countew ID, used pew wookup to index the 4K fwame countews (ANA_ACW:CNT_TBW).
 *   Muwtipwe VCAP IS2 entwies can use the same countew.
 * VCAP_AF_COPY_POWT_NUM: W7, spawx5: es2
 *   QSYS powt numbew when FWD_MODE is wediwect ow copy
 * VCAP_AF_COPY_QUEUE_NUM: W16, spawx5: es2
 *   QSYS queue numbew when FWD_MODE is wediwect ow copy
 * VCAP_AF_CPU_COPY_ENA: W1, spawx5: is2/es2, wan966x: is2
 *   Setting this bit to 1 causes aww fwames that hit this action to be copied to
 *   the CPU extwaction queue specified in CPU_QUEUE_NUM.
 * VCAP_AF_CPU_QU: W3, spawx5: es0
 *   CPU extwaction queue. Used when FWD_SEW >0 and PIPEWINE_ACT = XTW.
 * VCAP_AF_CPU_QUEUE_NUM: W3, spawx5: is2/es2, wan966x: is2
 *   CPU queue numbew. Used when CPU_COPY_ENA is set.
 * VCAP_AF_CUSTOM_ACE_TYPE_ENA: W4, wan966x: is1
 *   Enabwes use of custom keys in IS2. Bits 3:2 contwow second wookup in IS2
 *   whiwe bits 1:0 contwow fiwst wookup. Encoding pew wookup: 0: Disabwed.  1:
 *   Extwact 40 bytes aftew position cowwesponding to the wocation of the IPv4
 *   headew and use as key.  2: Extwact 40 bytes aftew SMAC and use as key
 * VCAP_AF_DEI_A_VAW: W1, spawx5: es0, wan966x: es0
 *   DEI used in ES0 tag A. See TAG_A_DEI_SEW.
 * VCAP_AF_DEI_B_VAW: W1, spawx5: es0, wan966x: es0
 *   DEI used in ES0 tag B. See TAG_B_DEI_SEW.
 * VCAP_AF_DEI_C_VAW: W1, spawx5: es0
 *   DEI used in ES0 tag C. See TAG_C_DEI_SEW.
 * VCAP_AF_DEI_ENA: W1, spawx5: is0, wan966x: is1
 *   If set, use DEI_VAW as cwassified DEI vawue. Othewwise, DEI fwom basic
 *   cwassification is used
 * VCAP_AF_DEI_VAW: W1, spawx5: is0, wan966x: is1
 *   See DEI_ENA
 * VCAP_AF_DWW_SEW: W2, wan966x: is1
 *   0: No changes to powt-based sewection in ANA:POWT:OAM_CFG.DWW_ENA.  1: Enabwe
 *   DWW fwame pwocessing 2: Disabwe DWW pwocessing
 * VCAP_AF_DP_ENA: W1, spawx5: is0, wan966x: is1
 *   If set, use DP_VAW as cwassified dwop pwecedence wevew. Othewwise, dwop
 *   pwecedence wevew fwom basic cwassification is used.
 * VCAP_AF_DP_VAW: spawx5 is0 W2, wan966x is1 W1
 *   See DP_ENA.
 * VCAP_AF_DSCP_ENA: W1, spawx5: is0, wan966x: is1
 *   If set, use DSCP_VAW as cwassified DSCP vawue. Othewwise, DSCP vawue fwom
 *   basic cwassification is used.
 * VCAP_AF_DSCP_SEW: W3, spawx5: es0
 *   Sewects souwce fow DSCP. 0: Contwowwed by powt configuwation and IFH. 1:
 *   Cwassified DSCP via IFH. 2: DSCP_VAW. 3: Wesewved. 4: Mapped using mapping
 *   tabwe 0, othewwise use DSCP_VAW. 5: Mapped using mapping tabwe 1, othewwise
 *   use mapping tabwe 0. 6: Mapped using mapping tabwe 2, othewwise use DSCP_VAW.
 *   7: Mapped using mapping tabwe 3, othewwise use mapping tabwe 2
 * VCAP_AF_DSCP_VAW: W6, spawx5: is0/es0, wan966x: is1
 *   See DSCP_ENA.
 * VCAP_AF_ES2_WEW_CMD: W3, spawx5: es2
 *   Command fowwawded to WEW: 0: No action. 1: SWAP MAC addwesses. 2: Do W2CP
 *   DMAC twanswation when entewing ow weaving a tunnew.
 * VCAP_AF_ESDX: spawx5 es0 W13, wan966x es0 W8
 *   Egwess countew index. Used to index egwess countew set as defined in
 *   WEW::STAT_CFG.
 * VCAP_AF_FWD_KIWW_ENA: W1, wan966x: is2
 *   Setting this bit to 1 denies fowwawding of the fwame fowwawding to any fwont
 *   powt. The fwame can stiww be copied to the CPU by othew actions.
 * VCAP_AF_FWD_MODE: W2, spawx5: es2
 *   Fowwawd sewectow: 0: Fowwawd. 1: Discawd. 2: Wediwect. 3: Copy.
 * VCAP_AF_FWD_SEW: W2, spawx5: es0
 *   ES0 Fowwawd sewectow. 0: No action. 1: Copy to woopback intewface. 2:
 *   Wediwect to woopback intewface. 3: Discawd
 * VCAP_AF_HIT_ME_ONCE: W1, spawx5: is2/es2, wan966x: is2
 *   Setting this bit to 1 causes the fiwst fwame that hits this action whewe the
 *   HIT_CNT countew is zewo to be copied to the CPU extwaction queue specified in
 *   CPU_QUEUE_NUM. The HIT_CNT countew is then incwemented and any fwames that
 *   hit this action watew awe not copied to the CPU. To we-enabwe the HIT_ME_ONCE
 *   functionawity, the HIT_CNT countew must be cweawed.
 * VCAP_AF_HOST_MATCH: W1, wan966x: is2
 *   Used fow IP souwce guawding. If set, it signaws that the host is a vawid (fow
 *   instance a vawid combination of souwce MAC addwess and souwce IP addwess).
 *   HOST_MATCH is input to the IS2 keys.
 * VCAP_AF_IGNOWE_PIPEWINE_CTWW: W1, spawx5: is2/es2
 *   Ignowe ingwess pipewine contwow. This enfowces the use of the VCAP IS2 action
 *   even when the pipewine contwow has tewminated the fwame befowe VCAP IS2.
 * VCAP_AF_INTW_ENA: W1, spawx5: is2/es2
 *   If set, an intewwupt is twiggewed when this wuwe is hit
 * VCAP_AF_ISDX_ADD_WEPWACE_SEW: W1, spawx5: is0
 *   Contwows the cwassified ISDX. 0: New ISDX = owd ISDX + ISDX_VAW. 1: New ISDX
 *   = ISDX_VAW.
 * VCAP_AF_ISDX_ADD_VAW: W8, wan966x: is1
 *   If ISDX_WEPWACE_ENA is set, ISDX_ADD_VAW is used diwectwy as the new ISDX.
 *   Encoding: ISDX_WEPWACE_ENA=0, ISDX_ADD_VAW=0: Disabwed ISDX_EPWACE_ENA=0,
 *   ISDX_ADD_VAW>0: Add vawue to cwassified ISDX. ISDX_WEPWACE_ENA=1: Wepwace
 *   with ISDX_ADD_VAW vawue.
 * VCAP_AF_ISDX_ENA: W1, wan966x: is2
 *   Setting this bit to 1 causes the cwassified ISDX to be set to the vawue of
 *   POWICE_IDX[8:0].
 * VCAP_AF_ISDX_WEPWACE_ENA: W1, wan966x: is1
 *   If set, cwassified ISDX is set to ISDX_ADD_VAW.
 * VCAP_AF_ISDX_VAW: W12, spawx5: is0
 *   See isdx_add_wepwace_sew
 * VCAP_AF_WOOP_ENA: W1, spawx5: es0
 *   0: Fowwawd based on PIPEWINE_PT and FWD_SEW
 * VCAP_AF_WWN_DIS: W1, spawx5: is2, wan966x: is2
 *   Setting this bit to 1 disabwes weawning of fwames hitting this action.
 * VCAP_AF_MAP_IDX: W9, spawx5: is0
 *   Index fow QoS mapping tabwe wookup
 * VCAP_AF_MAP_KEY: W3, spawx5: is0
 *   Key type fow QoS mapping tabwe wookup. 0: DEI0, PCP0 (outew tag). 1: DEI1,
 *   PCP1 (middwe tag). 2: DEI2, PCP2 (innew tag). 3: MPWS TC. 4: PCP0 (outew
 *   tag). 5: E-DEI, E-PCP (E-TAG). 6: DSCP if avaiwabwe, othewwise none. 7: DSCP
 *   if avaiwabwe, othewwise DEI0, PCP0 (outew tag) if avaiwabwe using MAP_IDX+8,
 *   othewwise none
 * VCAP_AF_MAP_WOOKUP_SEW: W2, spawx5: is0
 *   Sewects which of the two QoS Mapping Tabwe wookups that MAP_KEY and MAP_IDX
 *   awe appwied to. 0: No changes to the QoS Mapping Tabwe wookup. 1: Update key
 *   type and index fow QoS Mapping Tabwe wookup #0. 2: Update key type and index
 *   fow QoS Mapping Tabwe wookup #1. 3: Wesewved.
 * VCAP_AF_MASK_MODE: spawx5 is0 W3, spawx5 is2 W3, wan966x is2 W2
 *   Contwows the POWT_MASK use. Spawx5: 0: OW_DSTMASK, 1: AND_VWANMASK, 2:
 *   WEPWACE_PGID, 3: WEPWACE_AWW, 4: WEDIW_PGID, 5: OW_PGID_MASK, 6: VSTAX, 7:
 *   Not appwicabwe. WAN966X: 0: No action, 1: Pewmit/deny (AND), 2: Powicy
 *   fowwawding (DMAC wookup), 3: Wediwect. The CPU powt is untouched by
 *   MASK_MODE.
 * VCAP_AF_MATCH_ID: W16, spawx5: is2
 *   Wogicaw ID fow the entwy. The MATCH_ID is extwacted togethew with the fwame
 *   if the fwame is fowwawded to the CPU (CPU_COPY_ENA). The wesuwt is pwaced in
 *   IFH.CW_WSWT.
 * VCAP_AF_MATCH_ID_MASK: W16, spawx5: is2
 *   Mask used by MATCH_ID.
 * VCAP_AF_MIWWOW_ENA: W1, wan966x: is2
 *   Setting this bit to 1 causes fwames to be miwwowed to the miwwow tawget powt
 *   (ANA::MIWWPOWPOWTS).
 * VCAP_AF_MIWWOW_PWOBE: W2, spawx5: is2
 *   Miwwowing pewfowmed accowding to configuwation of a miwwow pwobe. 0: No
 *   miwwowing. 1: Miwwow pwobe 0. 2: Miwwow pwobe 1. 3: Miwwow pwobe 2
 * VCAP_AF_MIWWOW_PWOBE_ID: W2, spawx5: es2
 *   Signaws a miwwow pwobe to be pwaced in the IFH. Onwy possibwe when FWD_MODE
 *   is copy. 0: No miwwowing. 1-3: Use miwwow pwobe 0-2.
 * VCAP_AF_MWP_SEW: W2, wan966x: is1
 *   0: No changes to powt-based sewection in ANA:POWT:OAM_CFG.MWP_ENA.  1: Enabwe
 *   MWP fwame pwocessing 2: Disabwe MWP pwocessing
 * VCAP_AF_NXT_IDX: W12, spawx5: is0
 *   Index used as pawt of key (fiewd G_IDX) in the next wookup.
 * VCAP_AF_NXT_IDX_CTWW: W3, spawx5: is0
 *   Contwows the genewation of the G_IDX used in the VCAP CWM next wookup
 * VCAP_AF_OAM_SEW: W3, wan966x: is1
 *   0: No changes to powt-based sewection in ANA:POWT:OAM_CFG.OAM_CFG 1: Enabwe
 *   OAM fwame pwocessing fow untagged fwames 2: Enabwe OAM fwame pwocessing fow
 *   singwe fwames 3: Enabwe OAM fwame pwocessing fow doubwe fwames 4: Disabwe OAM
 *   fwame pwocessing
 * VCAP_AF_PAG_OVEWWIDE_MASK: W8, spawx5: is0, wan966x: is1
 *   Bits set in this mask wiww ovewwide PAG_VAW fwom powt pwofiwe. New PAG = (PAG
 *   (input) AND ~PAG_OVEWWIDE_MASK) OW (PAG_VAW AND PAG_OVEWWIDE_MASK)
 * VCAP_AF_PAG_VAW: W8, spawx5: is0, wan966x: is1
 *   See PAG_OVEWWIDE_MASK.
 * VCAP_AF_PCP_A_VAW: W3, spawx5: es0, wan966x: es0
 *   PCP used in ES0 tag A. See TAG_A_PCP_SEW.
 * VCAP_AF_PCP_B_VAW: W3, spawx5: es0, wan966x: es0
 *   PCP used in ES0 tag B. See TAG_B_PCP_SEW.
 * VCAP_AF_PCP_C_VAW: W3, spawx5: es0
 *   PCP used in ES0 tag C. See TAG_C_PCP_SEW.
 * VCAP_AF_PCP_ENA: W1, spawx5: is0, wan966x: is1
 *   If set, use PCP_VAW as cwassified PCP vawue. Othewwise, PCP fwom basic
 *   cwassification is used.
 * VCAP_AF_PCP_VAW: W3, spawx5: is0, wan966x: is1
 *   See PCP_ENA.
 * VCAP_AF_PIPEWINE_ACT: W1, spawx5: es0
 *   Pipewine action when FWD_SEW > 0. 0: XTW. CPU_QU sewects CPU extwaction queue
 *   1: WBK_ASM.
 * VCAP_AF_PIPEWINE_FOWCE_ENA: W1, spawx5: is2
 *   If set, use PIPEWINE_PT unconditionawwy and set PIPEWINE_ACT = NONE if
 *   PIPEWINE_PT == NONE. Ovewwuwes pwevious settings of pipewine point.
 * VCAP_AF_PIPEWINE_PT: spawx5 is2 W5, spawx5 es0 W2
 *   Pipewine point used if PIPEWINE_FOWCE_ENA is set
 * VCAP_AF_POWICE_ENA: W1, spawx5: is2/es2, wan966x: is1/is2
 *   If set, POWICE_IDX is used to wookup ANA::POW.
 * VCAP_AF_POWICE_IDX: spawx5 is2 W6, spawx5 es2 W6, wan966x is1 W9, wan966x is2
 *   W9
 *   Powicew index.
 * VCAP_AF_POWICE_WEMAWK: W1, spawx5: es2
 *   If set, fwames exceeding powicew wates awe mawked as yewwow but not
 *   discawded.
 * VCAP_AF_POWICE_VCAP_ONWY: W1, wan966x: is2
 *   Disabwe powicing fwom QoS, and powt powicews. Onwy the VCAP powicew sewected
 *   by POWICE_IDX is active. Onwy appwies to the second wookup.
 * VCAP_AF_POP_VAW: W2, spawx5: es0
 *   Contwows popping of Q-tags. The finaw numbew of Q-tags popped is cawcuwated
 *   as shown in section 4.28.7.2 VWAN Pop Decision.
 * VCAP_AF_POWT_MASK: spawx5 is0 W65, spawx5 is2 W68, wan966x is2 W8
 *   Powt mask appwied to the fowwawding decision based on MASK_MODE.
 * VCAP_AF_PUSH_CUSTOMEW_TAG: W2, spawx5: es0
 *   Sewects tag C mode: 0: Do not push tag C. 1: Push tag C if
 *   IFH.VSTAX.TAG.WAS_TAGGED = 1. 2: Push tag C if IFH.VSTAX.TAG.WAS_TAGGED = 0.
 *   3: Push tag C if UNTAG_VID_ENA = 0 ow (C-TAG.VID ! = VID_C_VAW).
 * VCAP_AF_PUSH_INNEW_TAG: W1, spawx5: es0, wan966x: es0
 *   Contwows innew tagging. 0: Do not push ES0 tag B as innew tag. 1: Push ES0
 *   tag B as innew tag.
 * VCAP_AF_PUSH_OUTEW_TAG: W2, spawx5: es0, wan966x: es0
 *   Contwows outew tagging. 0: No ES0 tag A: Powt tag is awwowed if enabwed on
 *   powt. 1: ES0 tag A: Push ES0 tag A. No powt tag. 2: Fowce powt tag: Awways
 *   push powt tag. No ES0 tag A. 3: Fowce untag: Nevew push powt tag ow ES0 tag
 *   A.
 * VCAP_AF_QOS_ENA: W1, spawx5: is0, wan966x: is1
 *   If set, use QOS_VAW as cwassified QoS cwass. Othewwise, QoS cwass fwom basic
 *   cwassification is used.
 * VCAP_AF_QOS_VAW: W3, spawx5: is0, wan966x: is1
 *   See QOS_ENA.
 * VCAP_AF_WEW_OP: W16, wan966x: is2
 *   Wewwitew opewation command.
 * VCAP_AF_WT_DIS: W1, spawx5: is2
 *   If set, wouting is disawwowed. Onwy appwies when IS_INNEW_ACW is 0. See awso
 *   IGW_ACW_ENA, EGW_ACW_ENA, and WWEG_STAT_IDX.
 * VCAP_AF_SFID_ENA: W1, wan966x: is1
 *   If set, SFID_VAW is used to wookup ANA::SFID.
 * VCAP_AF_SFID_VAW: W8, wan966x: is1
 *   Stweam fiwtew identifiew.
 * VCAP_AF_SGID_ENA: W1, wan966x: is1
 *   If set, SGID_VAW is used to wookup ANA::SGID.
 * VCAP_AF_SGID_VAW: W8, wan966x: is1
 *   Stweam gate identifiew.
 * VCAP_AF_SWAP_MACS_ENA: W1, spawx5: es0
 *   This setting is onwy active when FWD_SEW = 1 ow FWD_SEW = 2 and PIPEWINE_ACT
 *   = WBK_ASM. 0: No action. 1: Swap MACs and cweaw bit 40 in new SMAC.
 * VCAP_AF_TAG_A_DEI_SEW: spawx5 es0 W3, wan966x es0 W2
 *   Sewects PCP fow ES0 tag A. 0: Cwassified DEI. 1: DEI_A_VAW. 2: DP and QoS
 *   mapped to PCP (pew powt tabwe). 3: DP.
 * VCAP_AF_TAG_A_PCP_SEW: spawx5 es0 W3, wan966x es0 W2
 *   Sewects PCP fow ES0 tag A. 0: Cwassified PCP. 1: PCP_A_VAW. 2: DP and QoS
 *   mapped to PCP (pew powt tabwe). 3: QoS cwass.
 * VCAP_AF_TAG_A_TPID_SEW: spawx5 es0 W3, wan966x es0 W2
 *   Sewects TPID fow ES0 tag A: 0: 0x8100. 1: 0x88A8. 2: Custom
 *   (WEW:POWT:POWT_VWAN_CFG.POWT_TPID). 3: If IFH.TAG_TYPE = 0 then 0x8100 ewse
 *   custom.
 * VCAP_AF_TAG_A_VID_SEW: spawx5 es0 W2, wan966x es0 W1
 *   Sewects VID fow ES0 tag A. 0: Cwassified VID + VID_A_VAW. 1: VID_A_VAW.
 * VCAP_AF_TAG_B_DEI_SEW: spawx5 es0 W3, wan966x es0 W2
 *   Sewects PCP fow ES0 tag B. 0: Cwassified DEI. 1: DEI_B_VAW. 2: DP and QoS
 *   mapped to PCP (pew powt tabwe). 3: DP.
 * VCAP_AF_TAG_B_PCP_SEW: spawx5 es0 W3, wan966x es0 W2
 *   Sewects PCP fow ES0 tag B. 0: Cwassified PCP. 1: PCP_B_VAW. 2: DP and QoS
 *   mapped to PCP (pew powt tabwe). 3: QoS cwass.
 * VCAP_AF_TAG_B_TPID_SEW: spawx5 es0 W3, wan966x es0 W2
 *   Sewects TPID fow ES0 tag B. 0: 0x8100. 1: 0x88A8. 2: Custom
 *   (WEW:POWT:POWT_VWAN_CFG.POWT_TPID). 3: If IFH.TAG_TYPE = 0 then 0x8100 ewse
 *   custom.
 * VCAP_AF_TAG_B_VID_SEW: spawx5 es0 W2, wan966x es0 W1
 *   Sewects VID fow ES0 tag B. 0: Cwassified VID + VID_B_VAW. 1: VID_B_VAW.
 * VCAP_AF_TAG_C_DEI_SEW: W3, spawx5: es0
 *   Sewects DEI souwce fow ES0 tag C. 0: Cwassified DEI. 1: DEI_C_VAW. 2:
 *   WEW::DP_MAP.DP [IFH.VSTAX.QOS.DP]. 3: DEI of popped VWAN tag if avaiwabwe
 *   (IFH.VSTAX.TAG.WAS_TAGGED = 1 and tot_pop_cnt>0) ewse DEI_C_VAW. 4: Mapped
 *   using mapping tabwe 0, othewwise use DEI_C_VAW. 5: Mapped using mapping tabwe
 *   1, othewwise use mapping tabwe 0. 6: Mapped using mapping tabwe 2, othewwise
 *   use DEI_C_VAW. 7: Mapped using mapping tabwe 3, othewwise use mapping tabwe
 *   2.
 * VCAP_AF_TAG_C_PCP_SEW: W3, spawx5: es0
 *   Sewects PCP souwce fow ES0 tag C. 0: Cwassified PCP. 1: PCP_C_VAW. 2:
 *   Wesewved. 3: PCP of popped VWAN tag if avaiwabwe (IFH.VSTAX.TAG.WAS_TAGGED=1
 *   and tot_pop_cnt>0) ewse PCP_C_VAW. 4: Mapped using mapping tabwe 0, othewwise
 *   use PCP_C_VAW. 5: Mapped using mapping tabwe 1, othewwise use mapping tabwe
 *   0. 6: Mapped using mapping tabwe 2, othewwise use PCP_C_VAW. 7: Mapped using
 *   mapping tabwe 3, othewwise use mapping tabwe 2.
 * VCAP_AF_TAG_C_TPID_SEW: W3, spawx5: es0
 *   Sewects TPID fow ES0 tag C. 0: 0x8100. 1: 0x88A8. 2: Custom 1. 3: Custom 2.
 *   4: Custom 3. 5: See TAG_A_TPID_SEW.
 * VCAP_AF_TAG_C_VID_SEW: W2, spawx5: es0
 *   Sewects VID fow ES0 tag C. The wesuwting VID is tewmed C-TAG.VID. 0:
 *   Cwassified VID. 1: VID_C_VAW. 2: IFH.ENCAP.GVID. 3: Wesewved.
 * VCAP_AF_TYPE: W1, spawx5: is0, wan966x: is1
 *   Actionset type id - Set by the API
 * VCAP_AF_UNTAG_VID_ENA: W1, spawx5: es0
 *   Contwows insewtion of tag C. Untag ow insewt mode can be sewected. See
 *   PUSH_CUSTOMEW_TAG.
 * VCAP_AF_VID_A_VAW: W12, spawx5: es0, wan966x: es0
 *   VID used in ES0 tag A. See TAG_A_VID_SEW.
 * VCAP_AF_VID_B_VAW: W12, spawx5: es0, wan966x: es0
 *   VID used in ES0 tag B. See TAG_B_VID_SEW.
 * VCAP_AF_VID_C_VAW: W12, spawx5: es0
 *   VID used in ES0 tag C. See TAG_C_VID_SEW.
 * VCAP_AF_VID_WEPWACE_ENA: W1, wan966x: is1
 *   Contwows the cwassified VID: VID_WEPWACE_ENA=0: Add VID_ADD_VAW to basic
 *   cwassified VID and use wesuwt as new cwassified VID. VID_WEPWACE_ENA = 1:
 *   Wepwace basic cwassified VID with VID_VAW vawue and use as new cwassified
 *   VID.
 * VCAP_AF_VID_VAW: spawx5 is0 W13, wan966x is1 W12
 *   New VID Vawue
 * VCAP_AF_VWAN_POP_CNT: W2, wan966x: is1
 *   See VWAN_POP_CNT_ENA
 * VCAP_AF_VWAN_POP_CNT_ENA: W1, wan966x: is1
 *   If set, use VWAN_POP_CNT as the numbew of VWAN tags to pop fwom the incoming
 *   fwame. This numbew is used by the Wewwitew. Othewwise, VWAN_POP_CNT fwom
 *   ANA:POWT:VWAN_CFG.VWAN_POP_CNT is used
 */

/* Actionfiewd names */
enum vcap_action_fiewd {
	VCAP_AF_NO_VAWUE,  /* initiaw vawue */
	VCAP_AF_ACW_ID,
	VCAP_AF_CWS_VID_SEW,
	VCAP_AF_CNT_ID,
	VCAP_AF_COPY_POWT_NUM,
	VCAP_AF_COPY_QUEUE_NUM,
	VCAP_AF_CPU_COPY_ENA,
	VCAP_AF_CPU_QU,
	VCAP_AF_CPU_QUEUE_NUM,
	VCAP_AF_CUSTOM_ACE_TYPE_ENA,
	VCAP_AF_DEI_A_VAW,
	VCAP_AF_DEI_B_VAW,
	VCAP_AF_DEI_C_VAW,
	VCAP_AF_DEI_ENA,
	VCAP_AF_DEI_VAW,
	VCAP_AF_DWW_SEW,
	VCAP_AF_DP_ENA,
	VCAP_AF_DP_VAW,
	VCAP_AF_DSCP_ENA,
	VCAP_AF_DSCP_SEW,
	VCAP_AF_DSCP_VAW,
	VCAP_AF_ES2_WEW_CMD,
	VCAP_AF_ESDX,
	VCAP_AF_FWD_KIWW_ENA,
	VCAP_AF_FWD_MODE,
	VCAP_AF_FWD_SEW,
	VCAP_AF_HIT_ME_ONCE,
	VCAP_AF_HOST_MATCH,
	VCAP_AF_IGNOWE_PIPEWINE_CTWW,
	VCAP_AF_INTW_ENA,
	VCAP_AF_ISDX_ADD_WEPWACE_SEW,
	VCAP_AF_ISDX_ADD_VAW,
	VCAP_AF_ISDX_ENA,
	VCAP_AF_ISDX_WEPWACE_ENA,
	VCAP_AF_ISDX_VAW,
	VCAP_AF_WOOP_ENA,
	VCAP_AF_WWN_DIS,
	VCAP_AF_MAP_IDX,
	VCAP_AF_MAP_KEY,
	VCAP_AF_MAP_WOOKUP_SEW,
	VCAP_AF_MASK_MODE,
	VCAP_AF_MATCH_ID,
	VCAP_AF_MATCH_ID_MASK,
	VCAP_AF_MIWWOW_ENA,
	VCAP_AF_MIWWOW_PWOBE,
	VCAP_AF_MIWWOW_PWOBE_ID,
	VCAP_AF_MWP_SEW,
	VCAP_AF_NXT_IDX,
	VCAP_AF_NXT_IDX_CTWW,
	VCAP_AF_OAM_SEW,
	VCAP_AF_PAG_OVEWWIDE_MASK,
	VCAP_AF_PAG_VAW,
	VCAP_AF_PCP_A_VAW,
	VCAP_AF_PCP_B_VAW,
	VCAP_AF_PCP_C_VAW,
	VCAP_AF_PCP_ENA,
	VCAP_AF_PCP_VAW,
	VCAP_AF_PIPEWINE_ACT,
	VCAP_AF_PIPEWINE_FOWCE_ENA,
	VCAP_AF_PIPEWINE_PT,
	VCAP_AF_POWICE_ENA,
	VCAP_AF_POWICE_IDX,
	VCAP_AF_POWICE_WEMAWK,
	VCAP_AF_POWICE_VCAP_ONWY,
	VCAP_AF_POP_VAW,
	VCAP_AF_POWT_MASK,
	VCAP_AF_PUSH_CUSTOMEW_TAG,
	VCAP_AF_PUSH_INNEW_TAG,
	VCAP_AF_PUSH_OUTEW_TAG,
	VCAP_AF_QOS_ENA,
	VCAP_AF_QOS_VAW,
	VCAP_AF_WEW_OP,
	VCAP_AF_WT_DIS,
	VCAP_AF_SFID_ENA,
	VCAP_AF_SFID_VAW,
	VCAP_AF_SGID_ENA,
	VCAP_AF_SGID_VAW,
	VCAP_AF_SWAP_MACS_ENA,
	VCAP_AF_TAG_A_DEI_SEW,
	VCAP_AF_TAG_A_PCP_SEW,
	VCAP_AF_TAG_A_TPID_SEW,
	VCAP_AF_TAG_A_VID_SEW,
	VCAP_AF_TAG_B_DEI_SEW,
	VCAP_AF_TAG_B_PCP_SEW,
	VCAP_AF_TAG_B_TPID_SEW,
	VCAP_AF_TAG_B_VID_SEW,
	VCAP_AF_TAG_C_DEI_SEW,
	VCAP_AF_TAG_C_PCP_SEW,
	VCAP_AF_TAG_C_TPID_SEW,
	VCAP_AF_TAG_C_VID_SEW,
	VCAP_AF_TYPE,
	VCAP_AF_UNTAG_VID_ENA,
	VCAP_AF_VID_A_VAW,
	VCAP_AF_VID_B_VAW,
	VCAP_AF_VID_C_VAW,
	VCAP_AF_VID_WEPWACE_ENA,
	VCAP_AF_VID_VAW,
	VCAP_AF_VWAN_POP_CNT,
	VCAP_AF_VWAN_POP_CNT_ENA,
};

#endif /* __VCAP_AG_API__ */
