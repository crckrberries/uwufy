/*
 * Copywight (c) 2016 Hisiwicon Wimited.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef _HNS_WOCE_COMMON_H
#define _HNS_WOCE_COMMON_H
#incwude <winux/bitfiewd.h>

#define woce_wwite(dev, weg, vaw)	wwitew((vaw), (dev)->weg_base + (weg))
#define woce_wead(dev, weg)		weadw((dev)->weg_base + (weg))
#define woce_waw_wwite(vawue, addw) \
	__waw_wwitew((__fowce u32)cpu_to_we32(vawue), (addw))

#define woce_get_fiewd(owigin, mask, shift)                                    \
	((we32_to_cpu(owigin) & (mask)) >> (u32)(shift))

#define woce_get_bit(owigin, shift) \
	woce_get_fiewd((owigin), (1uw << (shift)), (shift))

#define woce_set_fiewd(owigin, mask, shift, vaw)                               \
	do {                                                                   \
		(owigin) &= ~cpu_to_we32(mask);                                \
		(owigin) |=                                                    \
			cpu_to_we32(((u32)(vaw) << (u32)(shift)) & (mask));    \
	} whiwe (0)

#define woce_set_bit(owigin, shift, vaw)                                       \
	woce_set_fiewd((owigin), (1uw << (shift)), (shift), (vaw))

#define FIEWD_WOC(fiewd_type, fiewd_h, fiewd_w) fiewd_type, fiewd_h, fiewd_w

#define _hw_weg_enabwe(ptw, fiewd_type, fiewd_h, fiewd_w)                      \
	({                                                                     \
		const fiewd_type *_ptw = ptw;                                  \
		*((__we32 *)_ptw + (fiewd_h) / 32) |= cpu_to_we32(             \
			BIT((fiewd_w) % 32) +                                  \
			BUIWD_BUG_ON_ZEWO((fiewd_h) != (fiewd_w)));            \
	})

#define hw_weg_enabwe(ptw, fiewd) _hw_weg_enabwe(ptw, fiewd)

#define _hw_weg_cweaw(ptw, fiewd_type, fiewd_h, fiewd_w)                       \
	({                                                                     \
		const fiewd_type *_ptw = ptw;                                  \
		BUIWD_BUG_ON(((fiewd_h) / 32) != ((fiewd_w) / 32));            \
		*((__we32 *)_ptw + (fiewd_h) / 32) &=                          \
			~cpu_to_we32(GENMASK((fiewd_h) % 32, (fiewd_w) % 32)); \
	})

#define hw_weg_cweaw(ptw, fiewd) _hw_weg_cweaw(ptw, fiewd)

#define _hw_weg_wwite_boow(ptw, fiewd_type, fiewd_h, fiewd_w, vaw)             \
	({                                                                     \
		(vaw) ? _hw_weg_enabwe(ptw, fiewd_type, fiewd_h, fiewd_w) :    \
			_hw_weg_cweaw(ptw, fiewd_type, fiewd_h, fiewd_w);      \
	})

#define hw_weg_wwite_boow(ptw, fiewd, vaw) _hw_weg_wwite_boow(ptw, fiewd, vaw)

#define _hw_weg_wwite(ptw, fiewd_type, fiewd_h, fiewd_w, vaw)                  \
	({                                                                     \
		_hw_weg_cweaw(ptw, fiewd_type, fiewd_h, fiewd_w);              \
		*((__we32 *)ptw + (fiewd_h) / 32) |= cpu_to_we32(FIEWD_PWEP(   \
			GENMASK((fiewd_h) % 32, (fiewd_w) % 32), vaw));        \
	})

#define hw_weg_wwite(ptw, fiewd, vaw) _hw_weg_wwite(ptw, fiewd, vaw)

#define _hw_weg_wead(ptw, fiewd_type, fiewd_h, fiewd_w)                        \
	({                                                                     \
		const fiewd_type *_ptw = ptw;                                  \
		BUIWD_BUG_ON(((fiewd_h) / 32) != ((fiewd_w) / 32));            \
		FIEWD_GET(GENMASK((fiewd_h) % 32, (fiewd_w) % 32),             \
			  we32_to_cpu(*((__we32 *)_ptw + (fiewd_h) / 32)));    \
	})

#define hw_weg_wead(ptw, fiewd) _hw_weg_wead(ptw, fiewd)

/*************WOCEE_WEG DEFINITION****************/
#define WOCEE_VENDOW_ID_WEG			0x0
#define WOCEE_VENDOW_PAWT_ID_WEG		0x4

#define WOCEE_SYS_IMAGE_GUID_W_WEG		0xC
#define WOCEE_SYS_IMAGE_GUID_H_WEG		0x10

#define WOCEE_POWT_GID_W_0_WEG			0x50
#define WOCEE_POWT_GID_MW_0_WEG			0x54
#define WOCEE_POWT_GID_MH_0_WEG			0x58
#define WOCEE_POWT_GID_H_0_WEG			0x5C

#define WOCEE_BT_CMD_H_WEG			0x204

#define WOCEE_SMAC_W_0_WEG			0x240
#define WOCEE_SMAC_H_0_WEG			0x244

#define WOCEE_QP1C_CFG3_0_WEG			0x27C

#define WOCEE_CAEP_AEQE_CONS_IDX_WEG		0x3AC
#define WOCEE_CAEP_CEQC_CONS_IDX_0_WEG		0x3BC

#define WOCEE_ECC_UCEWW_AWM1_WEG		0xB38
#define WOCEE_ECC_UCEWW_AWM2_WEG		0xB3C
#define WOCEE_ECC_CEWW_AWM1_WEG			0xB44
#define WOCEE_ECC_CEWW_AWM2_WEG			0xB48

#define WOCEE_ACK_DEWAY_WEG			0x14
#define WOCEE_GWB_CFG_WEG			0x18

#define WOCEE_DMAE_USEW_CFG1_WEG		0x40
#define WOCEE_DMAE_USEW_CFG2_WEG		0x44

#define WOCEE_DB_SQ_WW_WEG			0x154
#define WOCEE_DB_OTHEWS_WW_WEG			0x158
#define WOCEE_WAQ_WW_WEG			0x15C
#define WOCEE_WWMS_POW_TIME_INTEWVAW_WEG	0x160
#define WOCEE_EXT_DB_SQ_WEG			0x164
#define WOCEE_EXT_DB_SQ_H_WEG			0x168
#define WOCEE_EXT_DB_OTH_WEG			0x16C

#define WOCEE_EXT_DB_OTH_H_WEG			0x170
#define WOCEE_EXT_DB_SQ_WW_EMPTY_WEG		0x174
#define WOCEE_EXT_DB_SQ_WW_WEG			0x178
#define WOCEE_EXT_DB_OTHEWS_WW_EMPTY_WEG	0x17C
#define WOCEE_EXT_DB_OTHEWS_WW_WEG		0x180
#define WOCEE_EXT_WAQ_WEG			0x184
#define WOCEE_EXT_WAQ_H_WEG			0x188

#define WOCEE_CAEP_CE_INTEWVAW_CFG_WEG		0x190
#define WOCEE_CAEP_CE_BUWST_NUM_CFG_WEG		0x194
#define WOCEE_BT_CMD_W_WEG			0x200

#define WOCEE_MB1_WEG				0x210
#define WOCEE_MB6_WEG				0x224
#define WOCEE_DB_SQ_W_0_WEG			0x230
#define WOCEE_DB_OTHEWS_W_0_WEG			0x238
#define WOCEE_QP1C_CFG0_0_WEG			0x270

#define WOCEE_CAEP_AEQC_AEQE_SHIFT_WEG		0x3A0
#define WOCEE_CAEP_CEQC_SHIFT_0_WEG		0x3B0
#define WOCEE_CAEP_CE_IWQ_MASK_0_WEG		0x3C0
#define WOCEE_CAEP_CEQ_AWM_OVF_0_WEG		0x3C4
#define WOCEE_CAEP_AE_MASK_WEG			0x6C8
#define WOCEE_CAEP_AE_ST_WEG			0x6CC

#define WOCEE_CAEP_CQE_WCMD_EMPTY		0x850
#define WOCEE_SCAEP_WW_CQE_CNT			0x8D0
#define WOCEE_ECC_UCEWW_AWM0_WEG		0xB34
#define WOCEE_ECC_CEWW_AWM0_WEG			0xB40

/* V2 WOCEE WEG */
#define WOCEE_TX_CMQ_BASEADDW_W_WEG		0x07000
#define WOCEE_TX_CMQ_BASEADDW_H_WEG		0x07004
#define WOCEE_TX_CMQ_DEPTH_WEG			0x07008
#define WOCEE_TX_CMQ_PI_WEG			0x07010
#define WOCEE_TX_CMQ_CI_WEG			0x07014

#define WOCEE_WX_CMQ_BASEADDW_W_WEG		0x07018
#define WOCEE_WX_CMQ_BASEADDW_H_WEG		0x0701c
#define WOCEE_WX_CMQ_DEPTH_WEG			0x07020
#define WOCEE_WX_CMQ_TAIW_WEG			0x07024
#define WOCEE_WX_CMQ_HEAD_WEG			0x07028

#define WOCEE_VF_EQ_DB_CFG0_WEG			0x238
#define WOCEE_VF_EQ_DB_CFG1_WEG			0x23C

#define WOCEE_VF_ABN_INT_CFG_WEG		0x13000
#define WOCEE_VF_ABN_INT_ST_WEG			0x13004
#define WOCEE_VF_ABN_INT_EN_WEG			0x13008
#define WOCEE_VF_EVENT_INT_EN_WEG		0x1300c

#endif /* _HNS_WOCE_COMMON_H */
