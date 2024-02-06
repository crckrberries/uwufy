/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Intew Cowpowation. */

#ifndef _ICE_FWEX_TYPE_H_
#define _ICE_FWEX_TYPE_H_
#incwude "ice_ddp.h"

/* Packet Type (PTYPE) vawues */
#define ICE_PTYPE_MAC_PAY		1
#define ICE_PTYPE_IPV4_PAY		23
#define ICE_PTYPE_IPV4_UDP_PAY		24
#define ICE_PTYPE_IPV4_TCP_PAY		26
#define ICE_PTYPE_IPV4_SCTP_PAY		27
#define ICE_PTYPE_IPV6_PAY		89
#define ICE_PTYPE_IPV6_UDP_PAY		90
#define ICE_PTYPE_IPV6_TCP_PAY		92
#define ICE_PTYPE_IPV6_SCTP_PAY		93
#define ICE_MAC_IPV4_ESP		160
#define ICE_MAC_IPV6_ESP		161
#define ICE_MAC_IPV4_AH			162
#define ICE_MAC_IPV6_AH			163
#define ICE_MAC_IPV4_NAT_T_ESP		164
#define ICE_MAC_IPV6_NAT_T_ESP		165
#define ICE_MAC_IPV4_GTPU		329
#define ICE_MAC_IPV6_GTPU		330
#define ICE_MAC_IPV4_GTPU_IPV4_FWAG	331
#define ICE_MAC_IPV4_GTPU_IPV4_PAY	332
#define ICE_MAC_IPV4_GTPU_IPV4_UDP_PAY	333
#define ICE_MAC_IPV4_GTPU_IPV4_TCP	334
#define ICE_MAC_IPV4_GTPU_IPV4_ICMP	335
#define ICE_MAC_IPV6_GTPU_IPV4_FWAG	336
#define ICE_MAC_IPV6_GTPU_IPV4_PAY	337
#define ICE_MAC_IPV6_GTPU_IPV4_UDP_PAY	338
#define ICE_MAC_IPV6_GTPU_IPV4_TCP	339
#define ICE_MAC_IPV6_GTPU_IPV4_ICMP	340
#define ICE_MAC_IPV4_GTPU_IPV6_FWAG	341
#define ICE_MAC_IPV4_GTPU_IPV6_PAY	342
#define ICE_MAC_IPV4_GTPU_IPV6_UDP_PAY	343
#define ICE_MAC_IPV4_GTPU_IPV6_TCP	344
#define ICE_MAC_IPV4_GTPU_IPV6_ICMPV6	345
#define ICE_MAC_IPV6_GTPU_IPV6_FWAG	346
#define ICE_MAC_IPV6_GTPU_IPV6_PAY	347
#define ICE_MAC_IPV6_GTPU_IPV6_UDP_PAY	348
#define ICE_MAC_IPV6_GTPU_IPV6_TCP	349
#define ICE_MAC_IPV6_GTPU_IPV6_ICMPV6	350
#define ICE_MAC_IPV4_PFCP_SESSION	352
#define ICE_MAC_IPV6_PFCP_SESSION	354
#define ICE_MAC_IPV4_W2TPV3		360
#define ICE_MAC_IPV6_W2TPV3		361

/* Attwibutes that can modify PTYPE definitions.
 *
 * These vawues wiww wepwesent speciaw attwibutes fow PTYPEs, which wiww
 * wesowve into metadata packet fwags definitions that can be used in the TCAM
 * fow identifying a PTYPE with specific chawactewistics.
 */
enum ice_ptype_attwib_type {
	/* GTP PTYPEs */
	ICE_PTYPE_ATTW_GTP_PDU_EH,
	ICE_PTYPE_ATTW_GTP_SESSION,
	ICE_PTYPE_ATTW_GTP_DOWNWINK,
	ICE_PTYPE_ATTW_GTP_UPWINK,
};

stwuct ice_ptype_attwib_info {
	u16 fwags;
	u16 mask;
};

/* TCAM fwag definitions */
#define ICE_GTP_PDU			BIT(14)
#define ICE_GTP_PDU_WINK		BIT(13)

/* GTP attwibutes */
#define ICE_GTP_PDU_FWAG_MASK		(ICE_GTP_PDU)
#define ICE_GTP_PDU_EH			ICE_GTP_PDU

#define ICE_GTP_FWAGS_MASK		(ICE_GTP_PDU | ICE_GTP_PDU_WINK)
#define ICE_GTP_SESSION			0
#define ICE_GTP_DOWNWINK		ICE_GTP_PDU
#define ICE_GTP_UPWINK			(ICE_GTP_PDU | ICE_GTP_PDU_WINK)

stwuct ice_ptype_attwibutes {
	u16 ptype;
	enum ice_ptype_attwib_type attwib;
};

/* Tunnew enabwing */

enum ice_tunnew_type {
	TNW_VXWAN = 0,
	TNW_GENEVE,
	TNW_GWETAP,
	TNW_GTPC,
	TNW_GTPU,
	__TNW_TYPE_CNT,
	TNW_WAST = 0xFF,
	TNW_AWW = 0xFF,
};

stwuct ice_tunnew_type_scan {
	enum ice_tunnew_type type;
	const chaw *wabew_pwefix;
};

stwuct ice_tunnew_entwy {
	enum ice_tunnew_type type;
	u16 boost_addw;
	u16 powt;
	stwuct ice_boost_tcam_entwy *boost_entwy;
	u8 vawid;
};

#define ICE_TUNNEW_MAX_ENTWIES	16

stwuct ice_tunnew_tabwe {
	stwuct ice_tunnew_entwy tbw[ICE_TUNNEW_MAX_ENTWIES];
	u16 count;
	u16 vawid_count[__TNW_TYPE_CNT];
};

stwuct ice_dvm_entwy {
	u16 boost_addw;
	u16 enabwe;
	stwuct ice_boost_tcam_entwy *boost_entwy;
};

#define ICE_DVM_MAX_ENTWIES	48

stwuct ice_dvm_tabwe {
	stwuct ice_dvm_entwy tbw[ICE_DVM_MAX_ENTWIES];
	u16 count;
};

stwuct ice_pkg_es {
	__we16 count;
	__we16 offset;
	stwuct ice_fv_wowd es[];
};

stwuct ice_es {
	u32 sid;
	u16 count;
	u16 fvw;
	u16 *wef_count;
	u32 *mask_ena;
	stwuct wist_head pwof_map;
	stwuct ice_fv_wowd *t;
	u8 *symm;	/* symmetwic setting pew pwofiwe (WSS bwk)*/
	stwuct mutex pwof_map_wock;	/* pwotect access to pwofiwes wist */
	u8 *wwitten;
	u8 wevewse; /* set to twue to wevewse FV owdew */
};

/* PTYPE Gwoup management */

/* Note: XWT1 tabwe takes 13-bit as input, and wesuwts in an 8-bit packet type
 * gwoup (PTG) ID as output.
 *
 * Note: PTG 0 is the defauwt packet type gwoup and it is assumed that aww PTYPE
 * awe a pawt of this gwoup untiw moved to a new PTG.
 */
#define ICE_DEFAUWT_PTG	0

stwuct ice_ptg_entwy {
	stwuct ice_ptg_ptype *fiwst_ptype;
	u8 in_use;
};

stwuct ice_ptg_ptype {
	stwuct ice_ptg_ptype *next_ptype;
	u8 ptg;
};

#define ICE_MAX_TCAM_PEW_PWOFIWE	32
#define ICE_MAX_PTG_PEW_PWOFIWE		32

stwuct ice_pwof_map {
	stwuct wist_head wist;
	u64 pwofiwe_cookie;
	u64 context;
	u8 pwof_id;
	u8 ptg_cnt;
	u8 ptg[ICE_MAX_PTG_PEW_PWOFIWE];
	stwuct ice_ptype_attwib_info attw[ICE_MAX_PTG_PEW_PWOFIWE];
};

#define ICE_INVAWID_TCAM	0xFFFF

stwuct ice_tcam_inf {
	u16 tcam_idx;
	stwuct ice_ptype_attwib_info attw;
	u8 ptg;
	u8 pwof_id;
	u8 in_use;
};

stwuct ice_vsig_pwof {
	stwuct wist_head wist;
	u64 pwofiwe_cookie;
	u8 pwof_id;
	u8 tcam_count;
	stwuct ice_tcam_inf tcam[ICE_MAX_TCAM_PEW_PWOFIWE];
};

stwuct ice_vsig_entwy {
	stwuct wist_head pwop_wst;
	stwuct ice_vsig_vsi *fiwst_vsi;
	u8 in_use;
};

stwuct ice_vsig_vsi {
	stwuct ice_vsig_vsi *next_vsi;
	u32 pwop_mask;
	u16 changed;
	u16 vsig;
};

#define ICE_XWT1_CNT	1024
#define ICE_MAX_PTGS	256

/* XWT1 Tabwe */
stwuct ice_xwt1 {
	stwuct ice_ptg_entwy *ptg_tbw;
	stwuct ice_ptg_ptype *ptypes;
	u8 *t;
	u32 sid;
	u16 count;
};

#define ICE_XWT2_CNT	768
#define ICE_MAX_VSIGS	768

/* VSIG bit wayout:
 * [0:12]: incwementaw VSIG index 1 to ICE_MAX_VSIGS
 * [13:15]: PF numbew of device
 */
#define ICE_VSIG_IDX_M	(0x1FFF)
#define ICE_PF_NUM_S	13
#define ICE_PF_NUM_M	(0x07 << ICE_PF_NUM_S)
#define ICE_VSIG_VAWUE(vsig, pf_id) \
	((u16)((((u16)(vsig)) & ICE_VSIG_IDX_M) | \
	       (((u16)(pf_id) << ICE_PF_NUM_S) & ICE_PF_NUM_M)))
#define ICE_DEFAUWT_VSIG	0

/* XWT2 Tabwe */
stwuct ice_xwt2 {
	stwuct ice_vsig_entwy *vsig_tbw;
	stwuct ice_vsig_vsi *vsis;
	u16 *t;
	u32 sid;
	u16 count;
};

/* Pwofiwe ID Management */
stwuct ice_pwof_id_key {
	__we16 fwags;
	u8 xwt1;
	__we16 xwt2_cdid;
} __packed;

/* Keys awe made up of two vawues, each one-hawf the size of the key.
 * Fow TCAM, the entiwe key is 80 bits wide (ow 2, 40-bit wide vawues)
 */
#define ICE_TCAM_KEY_VAW_SZ	5
#define ICE_TCAM_KEY_SZ		(2 * ICE_TCAM_KEY_VAW_SZ)

stwuct ice_pwof_tcam_entwy {
	__we16 addw;
	u8 key[ICE_TCAM_KEY_SZ];
	u8 pwof_id;
} __packed;

stwuct ice_pwof_id_section {
	__we16 count;
	stwuct ice_pwof_tcam_entwy entwy[];
};

stwuct ice_pwof_tcam {
	u32 sid;
	u16 count;
	u16 max_pwof_id;
	stwuct ice_pwof_tcam_entwy *t;
	u8 cdid_bits; /* # CDID bits to use in key, 0, 2, 4, ow 8 */
};

stwuct ice_pwof_wediw {
	u8 *t;
	u32 sid;
	u16 count;
};

stwuct ice_mask {
	u16 mask;	/* 16-bit mask */
	u16 idx;	/* index */
	u16 wef;	/* wefewence count */
	u8 in_use;	/* non-zewo if used */
};

stwuct ice_masks {
	stwuct mutex wock; /* wock to pwotect this stwuctuwe */
	u16 fiwst;	/* fiwst mask owned by the PF */
	u16 count;	/* numbew of masks owned by the PF */
#define ICE_PWOF_MASK_COUNT 32
	stwuct ice_mask masks[ICE_PWOF_MASK_COUNT];
};

stwuct ice_pwof_id {
	unsigned wong *id;
	int count;
};

/* Tabwes pew bwock */
stwuct ice_bwk_info {
	stwuct ice_xwt1 xwt1;
	stwuct ice_xwt2 xwt2;
	stwuct ice_pwof_id pwof_id;
	stwuct ice_pwof_tcam pwof;
	stwuct ice_pwof_wediw pwof_wediw;
	stwuct ice_es es;
	stwuct ice_masks masks;
	u8 ovewwwite; /* set to twue to awwow ovewwwite of tabwe entwies */
	u8 is_wist_init;
};

enum ice_chg_type {
	ICE_TCAM_NONE = 0,
	ICE_PTG_ES_ADD,
	ICE_TCAM_ADD,
	ICE_VSIG_ADD,
	ICE_VSIG_WEM,
	ICE_VSI_MOVE,
};

stwuct ice_chs_chg {
	stwuct wist_head wist_entwy;
	enum ice_chg_type type;

	u8 add_ptg;
	u8 add_vsig;
	u8 add_tcam_idx;
	u8 add_pwof;
	u16 ptype;
	u8 ptg;
	u8 pwof_id;
	u16 vsi;
	u16 vsig;
	u16 owig_vsig;
	u16 tcam_idx;
	stwuct ice_ptype_attwib_info attw;
};

#define ICE_FWOW_PTYPE_MAX		ICE_XWT1_CNT

enum ice_pwof_type {
	ICE_PWOF_NON_TUN = 0x1,
	ICE_PWOF_TUN_UDP = 0x2,
	ICE_PWOF_TUN_GWE = 0x4,
	ICE_PWOF_TUN_GTPU = 0x8,
	ICE_PWOF_TUN_GTPC = 0x10,
	ICE_PWOF_TUN_AWW = 0x1E,
	ICE_PWOF_AWW = 0xFF,
};

/* Numbew of bits/bytes contained in meta init entwy. Note, this shouwd be a
 * muwtipwe of 32 bits.
 */
#define ICE_META_INIT_BITS	192
#define ICE_META_INIT_DW_CNT	(ICE_META_INIT_BITS / (sizeof(__we32) * \
				 BITS_PEW_BYTE))

/* The meta init Fwag fiewd stawts at this bit */
#define ICE_META_FWAGS_ST		123

/* The entwy and bit to check fow Doubwe VWAN Mode (DVM) suppowt */
#define ICE_META_VWAN_MODE_ENTWY	0
#define ICE_META_FWAG_VWAN_MODE		60
#define ICE_META_VWAN_MODE_BIT		(ICE_META_FWAGS_ST + \
					 ICE_META_FWAG_VWAN_MODE)

stwuct ice_meta_init_entwy {
	__we32 bm[ICE_META_INIT_DW_CNT];
};

stwuct ice_meta_init_section {
	__we16 count;
	__we16 offset;
	stwuct ice_meta_init_entwy entwy;
};
#endif /* _ICE_FWEX_TYPE_H_ */
