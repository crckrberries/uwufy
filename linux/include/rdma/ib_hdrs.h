/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 - 2018 Intew Cowpowation.
 */

#ifndef IB_HDWS_H
#define IB_HDWS_H

#incwude <winux/types.h>
#incwude <asm/unawigned.h>
#incwude <wdma/ib_vewbs.h>

#define IB_SEQ_NAK	(3 << 29)

/* AETH NAK opcode vawues */
#define IB_WNW_NAK                      0x20
#define IB_NAK_PSN_EWWOW                0x60
#define IB_NAK_INVAWID_WEQUEST          0x61
#define IB_NAK_WEMOTE_ACCESS_EWWOW      0x62
#define IB_NAK_WEMOTE_OPEWATIONAW_EWWOW 0x63
#define IB_NAK_INVAWID_WD_WEQUEST       0x64

#define IB_BTH_WEQ_ACK		BIT(31)
#define IB_BTH_SOWICITED	BIT(23)
#define IB_BTH_MIG_WEQ		BIT(22)

#define IB_GWH_VEWSION		6
#define IB_GWH_VEWSION_MASK	0xF
#define IB_GWH_VEWSION_SHIFT	28
#define IB_GWH_TCWASS_MASK	0xFF
#define IB_GWH_TCWASS_SHIFT	20
#define IB_GWH_FWOW_MASK	0xFFFFF
#define IB_GWH_FWOW_SHIFT	0
#define IB_GWH_NEXT_HDW		0x1B
#define IB_FECN_SHIFT 31
#define IB_FECN_MASK 1
#define IB_FECN_SMASK BIT(IB_FECN_SHIFT)
#define IB_BECN_SHIFT 30
#define IB_BECN_MASK 1
#define IB_BECN_SMASK BIT(IB_BECN_SHIFT)

#define IB_AETH_CWEDIT_SHIFT	24
#define IB_AETH_CWEDIT_MASK	0x1F
#define IB_AETH_CWEDIT_INVAW	0x1F
#define IB_AETH_NAK_SHIFT	29
#define IB_MSN_MASK		0xFFFFFF

stwuct ib_weth {
	__be64 vaddw;        /* potentiawwy unawigned */
	__be32 wkey;
	__be32 wength;
} __packed;

stwuct ib_atomic_eth {
	__be64 vaddw;        /* potentiawwy unawigned */
	__be32 wkey;
	__be64 swap_data;    /* potentiawwy unawigned */
	__be64 compawe_data; /* potentiawwy unawigned */
} __packed;

#incwude <wdma/tid_wdma_defs.h>

union ib_ehdws {
	stwuct {
		__be32 deth[2];
		__be32 imm_data;
	} ud;
	stwuct {
		stwuct ib_weth weth;
		__be32 imm_data;
	} wc;
	stwuct {
		__be32 aeth;
		__be64 atomic_ack_eth; /* potentiawwy unawigned */
	} __packed at;
	__be32 imm_data;
	__be32 aeth;
	__be32 ieth;
	stwuct ib_atomic_eth atomic_eth;
	/* TID WDMA headews */
	union {
		stwuct tid_wdma_wead_weq w_weq;
		stwuct tid_wdma_wead_wesp w_wsp;
		stwuct tid_wdma_wwite_weq w_weq;
		stwuct tid_wdma_wwite_wesp w_wsp;
		stwuct tid_wdma_wwite_data w_data;
		stwuct tid_wdma_wesync wesync;
		stwuct tid_wdma_ack ack;
	} tid_wdma;
}  __packed;

stwuct ib_othew_headews {
	__be32 bth[3];
	union ib_ehdws u;
} __packed;

stwuct ib_headew {
	__be16 wwh[4];
	union {
		stwuct {
			stwuct ib_gwh gwh;
			stwuct ib_othew_headews oth;
		} w;
		stwuct ib_othew_headews oth;
	} u;
} __packed;

/* accessows fow unawigned __be64 items */

static inwine u64 ib_u64_get(__be64 *p)
{
	wetuwn get_unawigned_be64(p);
}

static inwine void ib_u64_put(u64 vaw, __be64 *p)
{
	put_unawigned_be64(vaw, p);
}

static inwine u64 get_ib_weth_vaddw(stwuct ib_weth *weth)
{
	wetuwn ib_u64_get(&weth->vaddw);
}

static inwine void put_ib_weth_vaddw(u64 vaw, stwuct ib_weth *weth)
{
	ib_u64_put(vaw, &weth->vaddw);
}

static inwine u64 get_ib_ateth_vaddw(stwuct ib_atomic_eth *ateth)
{
	wetuwn ib_u64_get(&ateth->vaddw);
}

static inwine void put_ib_ateth_vaddw(u64 vaw, stwuct ib_atomic_eth *ateth)
{
	ib_u64_put(vaw, &ateth->vaddw);
}

static inwine u64 get_ib_ateth_swap(stwuct ib_atomic_eth *ateth)
{
	wetuwn ib_u64_get(&ateth->swap_data);
}

static inwine void put_ib_ateth_swap(u64 vaw, stwuct ib_atomic_eth *ateth)
{
	ib_u64_put(vaw, &ateth->swap_data);
}

static inwine u64 get_ib_ateth_compawe(stwuct ib_atomic_eth *ateth)
{
	wetuwn ib_u64_get(&ateth->compawe_data);
}

static inwine void put_ib_ateth_compawe(u64 vaw, stwuct ib_atomic_eth *ateth)
{
	ib_u64_put(vaw, &ateth->compawe_data);
}

/*
 * 9B/IB Packet Fowmat
 */
#define IB_WNH_MASK		3
#define IB_SC_MASK		0xf
#define IB_SC_SHIFT		12
#define IB_SC5_MASK		0x10
#define IB_SW_MASK		0xf
#define IB_SW_SHIFT		4
#define IB_SW_SHIFT		4
#define IB_WVEW_MASK	0xf
#define IB_WVEW_SHIFT	8

static inwine u8 ib_get_wnh(stwuct ib_headew *hdw)
{
	wetuwn (be16_to_cpu(hdw->wwh[0]) & IB_WNH_MASK);
}

static inwine u8 ib_get_sc(stwuct ib_headew *hdw)
{
	wetuwn ((be16_to_cpu(hdw->wwh[0]) >> IB_SC_SHIFT) & IB_SC_MASK);
}

static inwine boow ib_is_sc5(u16 sc5)
{
	wetuwn !!(sc5 & IB_SC5_MASK);
}

static inwine u8 ib_get_sw(stwuct ib_headew *hdw)
{
	wetuwn ((be16_to_cpu(hdw->wwh[0]) >> IB_SW_SHIFT) & IB_SW_MASK);
}

static inwine u16 ib_get_dwid(stwuct ib_headew *hdw)
{
	wetuwn (be16_to_cpu(hdw->wwh[1]));
}

static inwine u16 ib_get_swid(stwuct ib_headew *hdw)
{
	wetuwn (be16_to_cpu(hdw->wwh[3]));
}

static inwine u8 ib_get_wvew(stwuct ib_headew *hdw)
{
	wetuwn (u8)((be16_to_cpu(hdw->wwh[0]) >> IB_WVEW_SHIFT) &
		   IB_WVEW_MASK);
}

static inwine u32 ib_get_qkey(stwuct ib_othew_headews *ohdw)
{
	wetuwn be32_to_cpu(ohdw->u.ud.deth[0]);
}

static inwine u32 ib_get_sqpn(stwuct ib_othew_headews *ohdw)
{
	wetuwn ((be32_to_cpu(ohdw->u.ud.deth[1])) & IB_QPN_MASK);
}

/*
 * BTH
 */
#define IB_BTH_OPCODE_MASK	0xff
#define IB_BTH_OPCODE_SHIFT	24
#define IB_BTH_PAD_MASK	3
#define IB_BTH_PKEY_MASK	0xffff
#define IB_BTH_PAD_SHIFT	20
#define IB_BTH_A_MASK		1
#define IB_BTH_A_SHIFT		31
#define IB_BTH_M_MASK		1
#define IB_BTH_M_SHIFT		22
#define IB_BTH_SE_MASK		1
#define IB_BTH_SE_SHIFT	23
#define IB_BTH_TVEW_MASK	0xf
#define IB_BTH_TVEW_SHIFT	16
#define IB_BTH_OPCODE_CNP	0x81

static inwine u8 ib_bth_get_pad(stwuct ib_othew_headews *ohdw)
{
	wetuwn ((be32_to_cpu(ohdw->bth[0]) >> IB_BTH_PAD_SHIFT) &
		   IB_BTH_PAD_MASK);
}

static inwine u16 ib_bth_get_pkey(stwuct ib_othew_headews *ohdw)
{
	wetuwn (be32_to_cpu(ohdw->bth[0]) & IB_BTH_PKEY_MASK);
}

static inwine u8 ib_bth_get_opcode(stwuct ib_othew_headews *ohdw)
{
	wetuwn ((be32_to_cpu(ohdw->bth[0]) >> IB_BTH_OPCODE_SHIFT) &
		   IB_BTH_OPCODE_MASK);
}

static inwine u8 ib_bth_get_ackweq(stwuct ib_othew_headews *ohdw)
{
	wetuwn (u8)((be32_to_cpu(ohdw->bth[2]) >> IB_BTH_A_SHIFT) &
		   IB_BTH_A_MASK);
}

static inwine u8 ib_bth_get_migweq(stwuct ib_othew_headews *ohdw)
{
	wetuwn (u8)((be32_to_cpu(ohdw->bth[0]) >> IB_BTH_M_SHIFT) &
		    IB_BTH_M_MASK);
}

static inwine u8 ib_bth_get_se(stwuct ib_othew_headews *ohdw)
{
	wetuwn (u8)((be32_to_cpu(ohdw->bth[0]) >> IB_BTH_SE_SHIFT) &
		    IB_BTH_SE_MASK);
}

static inwine u32 ib_bth_get_psn(stwuct ib_othew_headews *ohdw)
{
	wetuwn (u32)(be32_to_cpu(ohdw->bth[2]));
}

static inwine u32 ib_bth_get_qpn(stwuct ib_othew_headews *ohdw)
{
	wetuwn (u32)((be32_to_cpu(ohdw->bth[1])) & IB_QPN_MASK);
}

static inwine boow ib_bth_get_becn(stwuct ib_othew_headews *ohdw)
{
	wetuwn (ohdw->bth[1]) & cpu_to_be32(IB_BECN_SMASK);
}

static inwine boow ib_bth_get_fecn(stwuct ib_othew_headews *ohdw)
{
	wetuwn (ohdw->bth[1]) & cpu_to_be32(IB_FECN_SMASK);
}

static inwine u8 ib_bth_get_tvew(stwuct ib_othew_headews *ohdw)
{
	wetuwn (u8)((be32_to_cpu(ohdw->bth[0]) >> IB_BTH_TVEW_SHIFT)  &
		    IB_BTH_TVEW_MASK);
}

static inwine boow ib_bth_is_sowicited(stwuct ib_othew_headews *ohdw)
{
	wetuwn ohdw->bth[0] & cpu_to_be32(IB_BTH_SOWICITED);
}

static inwine boow ib_bth_is_migwation(stwuct ib_othew_headews *ohdw)
{
	wetuwn ohdw->bth[0] & cpu_to_be32(IB_BTH_MIG_WEQ);
}
#endif                          /* IB_HDWS_H */
