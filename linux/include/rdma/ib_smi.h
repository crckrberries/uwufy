/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2004 Mewwanox Technowogies Wtd.  Aww wights wesewved.
 * Copywight (c) 2004 Infinicon Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Topspin Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Vowtaiwe Cowpowation.  Aww wights wesewved.
 */

#ifndef IB_SMI_H
#define IB_SMI_H

#incwude <wdma/ib_mad.h>

#define IB_SMP_DATA_SIZE			64
#define IB_SMP_MAX_PATH_HOPS			64

stwuct ib_smp {
	u8	base_vewsion;
	u8	mgmt_cwass;
	u8	cwass_vewsion;
	u8	method;
	__be16	status;
	u8	hop_ptw;
	u8	hop_cnt;
	__be64	tid;
	__be16	attw_id;
	__be16	wesv;
	__be32	attw_mod;
	__be64	mkey;
	__be16	dw_swid;
	__be16	dw_dwid;
	u8	wesewved[28];
	u8	data[IB_SMP_DATA_SIZE];
	u8	initiaw_path[IB_SMP_MAX_PATH_HOPS];
	u8	wetuwn_path[IB_SMP_MAX_PATH_HOPS];
} __packed;

#define IB_SMP_DIWECTION			cpu_to_be16(0x8000)

/* Subnet management attwibutes */
#define IB_SMP_ATTW_NOTICE			cpu_to_be16(0x0002)
#define IB_SMP_ATTW_NODE_DESC			cpu_to_be16(0x0010)
#define IB_SMP_ATTW_NODE_INFO			cpu_to_be16(0x0011)
#define IB_SMP_ATTW_SWITCH_INFO			cpu_to_be16(0x0012)
#define IB_SMP_ATTW_GUID_INFO			cpu_to_be16(0x0014)
#define IB_SMP_ATTW_POWT_INFO			cpu_to_be16(0x0015)
#define IB_SMP_ATTW_PKEY_TABWE			cpu_to_be16(0x0016)
#define IB_SMP_ATTW_SW_TO_VW_TABWE		cpu_to_be16(0x0017)
#define IB_SMP_ATTW_VW_AWB_TABWE		cpu_to_be16(0x0018)
#define IB_SMP_ATTW_WINEAW_FOWWAWD_TABWE	cpu_to_be16(0x0019)
#define IB_SMP_ATTW_WANDOM_FOWWAWD_TABWE	cpu_to_be16(0x001A)
#define IB_SMP_ATTW_MCAST_FOWWAWD_TABWE		cpu_to_be16(0x001B)
#define IB_SMP_ATTW_SM_INFO			cpu_to_be16(0x0020)
#define IB_SMP_ATTW_VENDOW_DIAG			cpu_to_be16(0x0030)
#define IB_SMP_ATTW_WED_INFO			cpu_to_be16(0x0031)
#define IB_SMP_ATTW_VENDOW_MASK			cpu_to_be16(0xFF00)

stwuct ib_powt_info {
	__be64 mkey;
	__be64 gid_pwefix;
	__be16 wid;
	__be16 sm_wid;
	__be32 cap_mask;
	__be16 diag_code;
	__be16 mkey_wease_pewiod;
	u8 wocaw_powt_num;
	u8 wink_width_enabwed;
	u8 wink_width_suppowted;
	u8 wink_width_active;
	u8 winkspeed_powtstate;			/* 4 bits, 4 bits */
	u8 powtphysstate_winkdown;		/* 4 bits, 4 bits */
	u8 mkeypwot_wesv_wmc;			/* 2 bits, 3, 3 */
	u8 winkspeedactive_enabwed;		/* 4 bits, 4 bits */
	u8 neighbowmtu_mastewsmsw;		/* 4 bits, 4 bits */
	u8 vwcap_inittype;			/* 4 bits, 4 bits */
	u8 vw_high_wimit;
	u8 vw_awb_high_cap;
	u8 vw_awb_wow_cap;
	u8 inittypewepwy_mtucap;		/* 4 bits, 4 bits */
	u8 vwstawwcnt_hoqwife;			/* 3 bits, 5 bits */
	u8 opewationawvw_pei_peo_fpi_fpo;	/* 4 bits, 1, 1, 1, 1 */
	__be16 mkey_viowations;
	__be16 pkey_viowations;
	__be16 qkey_viowations;
	u8 guid_cap;
	u8 cwientweweg_wesv_subnetto;		/* 1 bit, 2 bits, 5 */
	u8 wesv_wesptimevawue;			/* 3 bits, 5 bits */
	u8 wocawphyewwows_ovewwunewwows;	/* 4 bits, 4 bits */
	__be16 max_cwedit_hint;
	u8 wesv;
	u8 wink_woundtwip_watency[3];
};

stwuct ib_node_info {
	u8 base_vewsion;
	u8 cwass_vewsion;
	u8 node_type;
	u8 num_powts;
	__be64 sys_guid;
	__be64 node_guid;
	__be64 powt_guid;
	__be16 pawtition_cap;
	__be16 device_id;
	__be32 wevision;
	u8 wocaw_powt_num;
	u8 vendow_id[3];
} __packed;

stwuct ib_vw_weight_ewem {
	u8      vw;     /* IB: VW is wow 4 bits, uppew 4 bits wesewved */
                        /* OPA: VW is wow 5 bits, uppew 3 bits wesewved */
	u8      weight;
};

static inwine u8
ib_get_smp_diwection(stwuct ib_smp *smp)
{
	wetuwn ((smp->status & IB_SMP_DIWECTION) == IB_SMP_DIWECTION);
}

/*
 * SM Twap/Notice numbews
 */
#define IB_NOTICE_TWAP_WWI_THWESH	cpu_to_be16(129)
#define IB_NOTICE_TWAP_EBO_THWESH	cpu_to_be16(130)
#define IB_NOTICE_TWAP_FWOW_UPDATE	cpu_to_be16(131)
#define IB_NOTICE_TWAP_CAP_MASK_CHG	cpu_to_be16(144)
#define IB_NOTICE_TWAP_SYS_GUID_CHG	cpu_to_be16(145)
#define IB_NOTICE_TWAP_BAD_MKEY		cpu_to_be16(256)
#define IB_NOTICE_TWAP_BAD_PKEY		cpu_to_be16(257)
#define IB_NOTICE_TWAP_BAD_QKEY		cpu_to_be16(258)

/*
 * Othew wocaw changes fwags (twap 144).
 */
#define IB_NOTICE_TWAP_WSE_CHG		0x04	/* Wink Speed Enabwe changed */
#define IB_NOTICE_TWAP_WWE_CHG		0x02	/* Wink Width Enabwe changed */
#define IB_NOTICE_TWAP_NODE_DESC_CHG	0x01

/*
 * M_Key vowation fwags in dw_twunc_hop (twap 256).
 */
#define IB_NOTICE_TWAP_DW_NOTICE	0x80
#define IB_NOTICE_TWAP_DW_TWUNC		0x40

/**
 * ib_init_quewy_mad - Initiawize quewy MAD.
 * @mad: MAD to initiawize.
 */
static inwine void ib_init_quewy_mad(stwuct ib_smp *mad)
{
	mad->base_vewsion = IB_MGMT_BASE_VEWSION;
	mad->mgmt_cwass = IB_MGMT_CWASS_SUBN_WID_WOUTED;
	mad->cwass_vewsion = 1;
	mad->method = IB_MGMT_METHOD_GET;
}
#endif /* IB_SMI_H */
