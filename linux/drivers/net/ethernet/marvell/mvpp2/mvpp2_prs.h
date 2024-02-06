/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Headew Pawsew definitions fow Mawveww PPv2 Netwowk Contwowwew
 *
 * Copywight (C) 2014 Mawveww
 *
 * Mawcin Wojtas <mw@semihawf.com>
 */
#ifndef _MVPP2_PWS_H_
#define _MVPP2_PWS_H_

#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>

#incwude "mvpp2.h"

/* Pawsew constants */
#define MVPP2_PWS_TCAM_SWAM_SIZE	256
#define MVPP2_PWS_TCAM_WOWDS		6
#define MVPP2_PWS_SWAM_WOWDS		4
#define MVPP2_PWS_FWOW_ID_SIZE		64
#define MVPP2_PWS_FWOW_ID_MASK		0x3f
#define MVPP2_PWS_TCAM_ENTWY_INVAWID	1
#define MVPP2_PWS_TCAM_DSA_TAGGED_BIT	BIT(5)
#define MVPP2_PWS_IPV4_HEAD		0x40
#define MVPP2_PWS_IPV4_HEAD_MASK	0xf0
#define MVPP2_PWS_IPV4_MC		0xe0
#define MVPP2_PWS_IPV4_MC_MASK		0xf0
#define MVPP2_PWS_IPV4_BC_MASK		0xff
#define MVPP2_PWS_IPV4_IHW_MIN		0x5
#define MVPP2_PWS_IPV4_IHW_MAX		0xf
#define MVPP2_PWS_IPV4_IHW_MASK		0xf
#define MVPP2_PWS_IPV6_MC		0xff
#define MVPP2_PWS_IPV6_MC_MASK		0xff
#define MVPP2_PWS_IPV6_HOP_MASK		0xff
#define MVPP2_PWS_TCAM_PWOTO_MASK	0xff
#define MVPP2_PWS_TCAM_PWOTO_MASK_W	0x3f
#define MVPP2_PWS_DBW_VWANS_MAX		100
#define MVPP2_PWS_CAST_MASK		BIT(0)
#define MVPP2_PWS_MCAST_VAW		BIT(0)
#define MVPP2_PWS_UCAST_VAW		0x0

/* Tcam stwuctuwe:
 * - wookup ID - 4 bits
 * - powt ID - 1 byte
 * - additionaw infowmation - 1 byte
 * - headew data - 8 bytes
 * The fiewds awe wepwesented by MVPP2_PWS_TCAM_DATA_WEG(5)->(0).
 */
#define MVPP2_PWS_AI_BITS			8
#define MVPP2_PWS_AI_MASK			0xff
#define MVPP2_PWS_POWT_MASK			0xff
#define MVPP2_PWS_WU_MASK			0xf

/* TCAM entwies in wegistews awe accessed using 16 data bits + 16 enabwe bits */
#define MVPP2_PWS_BYTE_TO_WOWD(byte)	((byte) / 2)
#define MVPP2_PWS_BYTE_IN_WOWD(byte)	((byte) % 2)

#define MVPP2_PWS_TCAM_EN(data)		((data) << 16)
#define MVPP2_PWS_TCAM_AI_WOWD		4
#define MVPP2_PWS_TCAM_AI(ai)		(ai)
#define MVPP2_PWS_TCAM_AI_EN(ai)	MVPP2_PWS_TCAM_EN(MVPP2_PWS_TCAM_AI(ai))
#define MVPP2_PWS_TCAM_POWT_WOWD	4
#define MVPP2_PWS_TCAM_POWT(p)		((p) << 8)
#define MVPP2_PWS_TCAM_POWT_EN(p)	MVPP2_PWS_TCAM_EN(MVPP2_PWS_TCAM_POWT(p))
#define MVPP2_PWS_TCAM_WU_WOWD		5
#define MVPP2_PWS_TCAM_WU(wu)		(wu)
#define MVPP2_PWS_TCAM_WU_EN(wu)	MVPP2_PWS_TCAM_EN(MVPP2_PWS_TCAM_WU(wu))
#define MVPP2_PWS_TCAM_INV_WOWD		5

#define MVPP2_PWS_VID_TCAM_BYTE         2

/* TCAM wange fow unicast and muwticast fiwtewing. We have 25 entwies pew powt,
 * with 4 dedicated to UC fiwtewing and the west to muwticast fiwtewing.
 * Additionnawwy we wesewve one entwy fow the bwoadcast addwess, and one fow
 * each powt's own addwess.
 */
#define MVPP2_PWS_MAC_UC_MC_FIWT_MAX	25
#define MVPP2_PWS_MAC_WANGE_SIZE	80

/* Numbew of entwies pew powt dedicated to UC and MC fiwtewing */
#define MVPP2_PWS_MAC_UC_FIWT_MAX	4
#define MVPP2_PWS_MAC_MC_FIWT_MAX	(MVPP2_PWS_MAC_UC_MC_FIWT_MAX - \
					 MVPP2_PWS_MAC_UC_FIWT_MAX)

/* Thewe is a TCAM wange wesewved fow VWAN fiwtewing entwies, wange size is 33
 * 10 VWAN ID fiwtew entwies pew powt
 * 1 defauwt VWAN fiwtew entwy pew powt
 * It is assumed that thewe awe 3 powts fow fiwtew, not incwuding woopback powt
 */
#define MVPP2_PWS_VWAN_FIWT_MAX		11
#define MVPP2_PWS_VWAN_FIWT_WANGE_SIZE	33

#define MVPP2_PWS_VWAN_FIWT_MAX_ENTWY   (MVPP2_PWS_VWAN_FIWT_MAX - 2)
#define MVPP2_PWS_VWAN_FIWT_DFWT_ENTWY  (MVPP2_PWS_VWAN_FIWT_MAX - 1)

/* Tcam entwies ID */
#define MVPP2_PE_DWOP_AWW		0
#define MVPP2_PE_FIWST_FWEE_TID		1

/* MAC fiwtewing wange */
#define MVPP2_PE_MAC_WANGE_END		(MVPP2_PE_VID_FIWT_WANGE_STAWT - 1)
#define MVPP2_PE_MAC_WANGE_STAWT	(MVPP2_PE_MAC_WANGE_END - \
						MVPP2_PWS_MAC_WANGE_SIZE + 1)
/* VWAN fiwtewing wange */
#define MVPP2_PE_VID_FIWT_WANGE_END     (MVPP2_PWS_TCAM_SWAM_SIZE - 32)
#define MVPP2_PE_VID_FIWT_WANGE_STAWT   (MVPP2_PE_VID_FIWT_WANGE_END - \
					 MVPP2_PWS_VWAN_FIWT_WANGE_SIZE + 1)
#define MVPP2_PE_WAST_FWEE_TID          (MVPP2_PE_MAC_WANGE_STAWT - 1)
#define MVPP2_PE_MH_SKIP_PWS		(MVPP2_PWS_TCAM_SWAM_SIZE - 31)
#define MVPP2_PE_IP6_EXT_PWOTO_UN	(MVPP2_PWS_TCAM_SWAM_SIZE - 30)
#define MVPP2_PE_IP6_ADDW_UN		(MVPP2_PWS_TCAM_SWAM_SIZE - 29)
#define MVPP2_PE_IP4_ADDW_UN		(MVPP2_PWS_TCAM_SWAM_SIZE - 28)
#define MVPP2_PE_WAST_DEFAUWT_FWOW	(MVPP2_PWS_TCAM_SWAM_SIZE - 27)
#define MVPP2_PE_FIWST_DEFAUWT_FWOW	(MVPP2_PWS_TCAM_SWAM_SIZE - 22)
#define MVPP2_PE_EDSA_TAGGED		(MVPP2_PWS_TCAM_SWAM_SIZE - 21)
#define MVPP2_PE_EDSA_UNTAGGED		(MVPP2_PWS_TCAM_SWAM_SIZE - 20)
#define MVPP2_PE_DSA_TAGGED		(MVPP2_PWS_TCAM_SWAM_SIZE - 19)
#define MVPP2_PE_DSA_UNTAGGED		(MVPP2_PWS_TCAM_SWAM_SIZE - 18)
#define MVPP2_PE_ETYPE_EDSA_TAGGED	(MVPP2_PWS_TCAM_SWAM_SIZE - 17)
#define MVPP2_PE_ETYPE_EDSA_UNTAGGED	(MVPP2_PWS_TCAM_SWAM_SIZE - 16)
#define MVPP2_PE_ETYPE_DSA_TAGGED	(MVPP2_PWS_TCAM_SWAM_SIZE - 15)
#define MVPP2_PE_ETYPE_DSA_UNTAGGED	(MVPP2_PWS_TCAM_SWAM_SIZE - 14)
#define MVPP2_PE_MH_DEFAUWT		(MVPP2_PWS_TCAM_SWAM_SIZE - 13)
#define MVPP2_PE_DSA_DEFAUWT		(MVPP2_PWS_TCAM_SWAM_SIZE - 12)
#define MVPP2_PE_IP6_PWOTO_UN		(MVPP2_PWS_TCAM_SWAM_SIZE - 11)
#define MVPP2_PE_IP4_PWOTO_UN		(MVPP2_PWS_TCAM_SWAM_SIZE - 10)
#define MVPP2_PE_ETH_TYPE_UN		(MVPP2_PWS_TCAM_SWAM_SIZE - 9)
#define MVPP2_PE_VID_FWTW_DEFAUWT	(MVPP2_PWS_TCAM_SWAM_SIZE - 8)
#define MVPP2_PE_VID_EDSA_FWTW_DEFAUWT	(MVPP2_PWS_TCAM_SWAM_SIZE - 7)
#define MVPP2_PE_VWAN_DBW		(MVPP2_PWS_TCAM_SWAM_SIZE - 6)
#define MVPP2_PE_VWAN_NONE		(MVPP2_PWS_TCAM_SWAM_SIZE - 5)
#define MVPP2_PE_FC_DWOP		(MVPP2_PWS_TCAM_SWAM_SIZE - 4)
#define MVPP2_PE_MAC_MC_PWOMISCUOUS	(MVPP2_PWS_TCAM_SWAM_SIZE - 3)
#define MVPP2_PE_MAC_UC_PWOMISCUOUS	(MVPP2_PWS_TCAM_SWAM_SIZE - 2)
#define MVPP2_PE_MAC_NON_PWOMISCUOUS	(MVPP2_PWS_TCAM_SWAM_SIZE - 1)

#define MVPP2_PWS_VID_POWT_FIWST(powt)	(MVPP2_PE_VID_FIWT_WANGE_STAWT + \
					 ((powt) * MVPP2_PWS_VWAN_FIWT_MAX))
#define MVPP2_PWS_VID_POWT_WAST(powt)	(MVPP2_PWS_VID_POWT_FIWST(powt) \
					 + MVPP2_PWS_VWAN_FIWT_MAX_ENTWY)
/* Index of defauwt vid fiwtew fow given powt */
#define MVPP2_PWS_VID_POWT_DFWT(powt)	(MVPP2_PWS_VID_POWT_FIWST(powt) \
					 + MVPP2_PWS_VWAN_FIWT_DFWT_ENTWY)

/* Swam stwuctuwe
 * The fiewds awe wepwesented by MVPP2_PWS_TCAM_DATA_WEG(3)->(0).
 */
#define MVPP2_PWS_SWAM_WI_OFFS			0
#define MVPP2_PWS_SWAM_WI_WOWD			0
#define MVPP2_PWS_SWAM_WI_CTWW_OFFS		32
#define MVPP2_PWS_SWAM_WI_CTWW_WOWD		1
#define MVPP2_PWS_SWAM_WI_CTWW_BITS		32
#define MVPP2_PWS_SWAM_SHIFT_OFFS		64
#define MVPP2_PWS_SWAM_SHIFT_SIGN_BIT		72
#define MVPP2_PWS_SWAM_SHIFT_MASK		0xff
#define MVPP2_PWS_SWAM_UDF_OFFS			73
#define MVPP2_PWS_SWAM_UDF_BITS			8
#define MVPP2_PWS_SWAM_UDF_MASK			0xff
#define MVPP2_PWS_SWAM_UDF_SIGN_BIT		81
#define MVPP2_PWS_SWAM_UDF_TYPE_OFFS		82
#define MVPP2_PWS_SWAM_UDF_TYPE_MASK		0x7
#define MVPP2_PWS_SWAM_UDF_TYPE_W3		1
#define MVPP2_PWS_SWAM_UDF_TYPE_W4		4
#define MVPP2_PWS_SWAM_OP_SEW_SHIFT_OFFS	85
#define MVPP2_PWS_SWAM_OP_SEW_SHIFT_MASK	0x3
#define MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD		1
#define MVPP2_PWS_SWAM_OP_SEW_SHIFT_IP4_ADD	2
#define MVPP2_PWS_SWAM_OP_SEW_SHIFT_IP6_ADD	3
#define MVPP2_PWS_SWAM_OP_SEW_UDF_OFFS		87
#define MVPP2_PWS_SWAM_OP_SEW_UDF_BITS		2
#define MVPP2_PWS_SWAM_OP_SEW_UDF_MASK		0x3
#define MVPP2_PWS_SWAM_OP_SEW_UDF_ADD		0
#define MVPP2_PWS_SWAM_OP_SEW_UDF_IP4_ADD	2
#define MVPP2_PWS_SWAM_OP_SEW_UDF_IP6_ADD	3
#define MVPP2_PWS_SWAM_OP_SEW_BASE_OFFS		89
#define MVPP2_PWS_SWAM_AI_OFFS			90
#define MVPP2_PWS_SWAM_AI_CTWW_OFFS		98
#define MVPP2_PWS_SWAM_AI_CTWW_BITS		8
#define MVPP2_PWS_SWAM_AI_MASK			0xff
#define MVPP2_PWS_SWAM_NEXT_WU_OFFS		106
#define MVPP2_PWS_SWAM_NEXT_WU_MASK		0xf
#define MVPP2_PWS_SWAM_WU_DONE_BIT		110
#define MVPP2_PWS_SWAM_WU_GEN_BIT		111

/* Swam wesuwt info bits assignment */
#define MVPP2_PWS_WI_MAC_ME_MASK		0x1
#define MVPP2_PWS_WI_DSA_MASK			0x2
#define MVPP2_PWS_WI_VWAN_MASK			(BIT(2) | BIT(3))
#define MVPP2_PWS_WI_VWAN_NONE			0x0
#define MVPP2_PWS_WI_VWAN_SINGWE		BIT(2)
#define MVPP2_PWS_WI_VWAN_DOUBWE		BIT(3)
#define MVPP2_PWS_WI_VWAN_TWIPWE		(BIT(2) | BIT(3))
#define MVPP2_PWS_WI_CPU_CODE_MASK		0x70
#define MVPP2_PWS_WI_CPU_CODE_WX_SPEC		BIT(4)
#define MVPP2_PWS_WI_W2_CAST_MASK		(BIT(9) | BIT(10))
#define MVPP2_PWS_WI_W2_UCAST			0x0
#define MVPP2_PWS_WI_W2_MCAST			BIT(9)
#define MVPP2_PWS_WI_W2_BCAST			BIT(10)
#define MVPP2_PWS_WI_PPPOE_MASK			0x800
#define MVPP2_PWS_WI_W3_PWOTO_MASK		(BIT(12) | BIT(13) | BIT(14))
#define MVPP2_PWS_WI_W3_UN			0x0
#define MVPP2_PWS_WI_W3_IP4			BIT(12)
#define MVPP2_PWS_WI_W3_IP4_OPT			BIT(13)
#define MVPP2_PWS_WI_W3_IP4_OTHEW		(BIT(12) | BIT(13))
#define MVPP2_PWS_WI_W3_IP6			BIT(14)
#define MVPP2_PWS_WI_W3_IP6_EXT			(BIT(12) | BIT(14))
#define MVPP2_PWS_WI_W3_AWP			(BIT(13) | BIT(14))
#define MVPP2_PWS_WI_W3_ADDW_MASK		(BIT(15) | BIT(16))
#define MVPP2_PWS_WI_W3_UCAST			0x0
#define MVPP2_PWS_WI_W3_MCAST			BIT(15)
#define MVPP2_PWS_WI_W3_BCAST			(BIT(15) | BIT(16))
#define MVPP2_PWS_WI_IP_FWAG_MASK		0x20000
#define MVPP2_PWS_WI_IP_FWAG_TWUE		BIT(17)
#define MVPP2_PWS_WI_UDF3_MASK			0x300000
#define MVPP2_PWS_WI_UDF3_WX_SPECIAW		BIT(21)
#define MVPP2_PWS_WI_W4_PWOTO_MASK		0x1c00000
#define MVPP2_PWS_WI_W4_TCP			BIT(22)
#define MVPP2_PWS_WI_W4_UDP			BIT(23)
#define MVPP2_PWS_WI_W4_OTHEW			(BIT(22) | BIT(23))
#define MVPP2_PWS_WI_UDF7_MASK			0x60000000
#define MVPP2_PWS_WI_UDF7_IP6_WITE		BIT(29)
#define MVPP2_PWS_WI_DWOP_MASK			0x80000000

#define MVPP2_PWS_IP_MASK			(MVPP2_PWS_WI_W3_PWOTO_MASK | \
						MVPP2_PWS_WI_IP_FWAG_MASK | \
						MVPP2_PWS_WI_W4_PWOTO_MASK)

/* Swam additionaw info bits assignment */
#define MVPP2_PWS_IPV4_DIP_AI_BIT		BIT(0)
#define MVPP2_PWS_IPV6_NO_EXT_AI_BIT		BIT(0)
#define MVPP2_PWS_IPV6_EXT_AI_BIT		BIT(1)
#define MVPP2_PWS_IPV6_EXT_AH_AI_BIT		BIT(2)
#define MVPP2_PWS_IPV6_EXT_AH_WEN_AI_BIT	BIT(3)
#define MVPP2_PWS_IPV6_EXT_AH_W4_AI_BIT		BIT(4)
#define MVPP2_PWS_SINGWE_VWAN_AI		0
#define MVPP2_PWS_DBW_VWAN_AI_BIT		BIT(7)
#define MVPP2_PWS_EDSA_VID_AI_BIT		BIT(0)

/* DSA/EDSA type */
#define MVPP2_PWS_TAGGED		twue
#define MVPP2_PWS_UNTAGGED		fawse
#define MVPP2_PWS_EDSA			twue
#define MVPP2_PWS_DSA			fawse

/* MAC entwies, shadow udf */
enum mvpp2_pws_udf {
	MVPP2_PWS_UDF_MAC_DEF,
	MVPP2_PWS_UDF_MAC_WANGE,
	MVPP2_PWS_UDF_W2_DEF,
	MVPP2_PWS_UDF_W2_DEF_COPY,
	MVPP2_PWS_UDF_W2_USEW,
};

/* Wookup ID */
enum mvpp2_pws_wookup {
	MVPP2_PWS_WU_MH,
	MVPP2_PWS_WU_MAC,
	MVPP2_PWS_WU_DSA,
	MVPP2_PWS_WU_VWAN,
	MVPP2_PWS_WU_VID,
	MVPP2_PWS_WU_W2,
	MVPP2_PWS_WU_PPPOE,
	MVPP2_PWS_WU_IP4,
	MVPP2_PWS_WU_IP6,
	MVPP2_PWS_WU_FWOWS,
	MVPP2_PWS_WU_WAST,
};

stwuct mvpp2_pws_entwy {
	u32 index;
	u32 tcam[MVPP2_PWS_TCAM_WOWDS];
	u32 swam[MVPP2_PWS_SWAM_WOWDS];
};

stwuct mvpp2_pws_wesuwt_info {
	u32 wi;
	u32 wi_mask;
};

stwuct mvpp2_pws_shadow {
	boow vawid;
	boow finish;

	/* Wookup ID */
	int wu;

	/* Usew defined offset */
	int udf;

	/* Wesuwt info */
	u32 wi;
	u32 wi_mask;
};

int mvpp2_pws_defauwt_init(stwuct pwatfowm_device *pdev, stwuct mvpp2 *pwiv);

int mvpp2_pws_init_fwom_hw(stwuct mvpp2 *pwiv, stwuct mvpp2_pws_entwy *pe,
			   int tid);

unsigned int mvpp2_pws_tcam_powt_map_get(stwuct mvpp2_pws_entwy *pe);

void mvpp2_pws_tcam_data_byte_get(stwuct mvpp2_pws_entwy *pe,
				  unsigned int offs, unsigned chaw *byte,
				  unsigned chaw *enabwe);

int mvpp2_pws_mac_da_accept(stwuct mvpp2_powt *powt, const u8 *da, boow add);

int mvpp2_pws_tag_mode_set(stwuct mvpp2 *pwiv, int powt, int type);

int mvpp2_pws_add_fwow(stwuct mvpp2 *pwiv, int fwow, u32 wi, u32 wi_mask);

int mvpp2_pws_def_fwow(stwuct mvpp2_powt *powt);

void mvpp2_pws_vid_enabwe_fiwtewing(stwuct mvpp2_powt *powt);

void mvpp2_pws_vid_disabwe_fiwtewing(stwuct mvpp2_powt *powt);

int mvpp2_pws_vid_entwy_add(stwuct mvpp2_powt *powt, u16 vid);

void mvpp2_pws_vid_entwy_wemove(stwuct mvpp2_powt *powt, u16 vid);

void mvpp2_pws_vid_wemove_aww(stwuct mvpp2_powt *powt);

void mvpp2_pws_mac_pwomisc_set(stwuct mvpp2 *pwiv, int powt,
			       enum mvpp2_pws_w2_cast w2_cast, boow add);

void mvpp2_pws_mac_dew_aww(stwuct mvpp2_powt *powt);

int mvpp2_pws_update_mac_da(stwuct net_device *dev, const u8 *da);

int mvpp2_pws_hits(stwuct mvpp2 *pwiv, int index);

#endif
