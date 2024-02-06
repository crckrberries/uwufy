// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude "spectwum.h"
#incwude "item.h"
#incwude "cowe_acw_fwex_keys.h"

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_w2_dmac[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(DMAC_32_47, 0x00, 2),
	MWXSW_AFK_EWEMENT_INST_BUF(DMAC_0_31, 0x02, 4),
	MWXSW_AFK_EWEMENT_INST_U32(PCP, 0x08, 13, 3),
	MWXSW_AFK_EWEMENT_INST_U32(VID, 0x08, 0, 12),
	MWXSW_AFK_EWEMENT_INST_U32(SWC_SYS_POWT, 0x0C, 0, 16),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_w2_smac[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(SMAC_32_47, 0x00, 2),
	MWXSW_AFK_EWEMENT_INST_BUF(SMAC_0_31, 0x02, 4),
	MWXSW_AFK_EWEMENT_INST_U32(PCP, 0x08, 13, 3),
	MWXSW_AFK_EWEMENT_INST_U32(VID, 0x08, 0, 12),
	MWXSW_AFK_EWEMENT_INST_U32(SWC_SYS_POWT, 0x0C, 0, 16),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_w2_smac_ex[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(SMAC_32_47, 0x02, 2),
	MWXSW_AFK_EWEMENT_INST_BUF(SMAC_0_31, 0x04, 4),
	MWXSW_AFK_EWEMENT_INST_U32(ETHEWTYPE, 0x0C, 0, 16),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv4_sip[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(SWC_IP_0_31, 0x00, 4),
	MWXSW_AFK_EWEMENT_INST_U32(W4_POWT_WANGE, 0x04, 16, 16),
	MWXSW_AFK_EWEMENT_INST_U32(IP_PWOTO, 0x08, 0, 8),
	MWXSW_AFK_EWEMENT_INST_U32(SWC_SYS_POWT, 0x0C, 0, 16),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv4_dip[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(DST_IP_0_31, 0x00, 4),
	MWXSW_AFK_EWEMENT_INST_U32(W4_POWT_WANGE, 0x04, 16, 16),
	MWXSW_AFK_EWEMENT_INST_U32(IP_PWOTO, 0x08, 0, 8),
	MWXSW_AFK_EWEMENT_INST_U32(SWC_SYS_POWT, 0x0C, 0, 16),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv4[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(SWC_IP_0_31, 0x00, 4),
	MWXSW_AFK_EWEMENT_INST_U32(IP_ECN, 0x04, 4, 2),
	MWXSW_AFK_EWEMENT_INST_U32(IP_TTW_, 0x04, 24, 8),
	MWXSW_AFK_EWEMENT_INST_U32(IP_DSCP, 0x08, 0, 6),
	MWXSW_AFK_EWEMENT_INST_U32(TCP_FWAGS, 0x08, 8, 9), /* TCP_CONTWOW+TCP_ECN */
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv4_ex[] = {
	MWXSW_AFK_EWEMENT_INST_U32(VID, 0x00, 0, 12),
	MWXSW_AFK_EWEMENT_INST_U32(PCP, 0x08, 29, 3),
	MWXSW_AFK_EWEMENT_INST_U32(SWC_W4_POWT, 0x08, 0, 16),
	MWXSW_AFK_EWEMENT_INST_U32(DST_W4_POWT, 0x0C, 0, 16),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv6_dip[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(DST_IP_32_63, 0x00, 4),
	MWXSW_AFK_EWEMENT_INST_BUF(DST_IP_0_31, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv6_ex1[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(DST_IP_96_127, 0x00, 4),
	MWXSW_AFK_EWEMENT_INST_BUF(DST_IP_64_95, 0x04, 4),
	MWXSW_AFK_EWEMENT_INST_U32(IP_PWOTO, 0x08, 0, 8),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv6_sip[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(SWC_IP_32_63, 0x00, 4),
	MWXSW_AFK_EWEMENT_INST_BUF(SWC_IP_0_31, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv6_sip_ex[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(SWC_IP_96_127, 0x00, 4),
	MWXSW_AFK_EWEMENT_INST_BUF(SWC_IP_64_95, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_packet_type[] = {
	MWXSW_AFK_EWEMENT_INST_U32(ETHEWTYPE, 0x00, 0, 16),
};

static const stwuct mwxsw_afk_bwock mwxsw_sp1_afk_bwocks[] = {
	MWXSW_AFK_BWOCK(0x10, mwxsw_sp_afk_ewement_info_w2_dmac),
	MWXSW_AFK_BWOCK(0x11, mwxsw_sp_afk_ewement_info_w2_smac),
	MWXSW_AFK_BWOCK(0x12, mwxsw_sp_afk_ewement_info_w2_smac_ex),
	MWXSW_AFK_BWOCK(0x30, mwxsw_sp_afk_ewement_info_ipv4_sip),
	MWXSW_AFK_BWOCK(0x31, mwxsw_sp_afk_ewement_info_ipv4_dip),
	MWXSW_AFK_BWOCK(0x32, mwxsw_sp_afk_ewement_info_ipv4),
	MWXSW_AFK_BWOCK(0x33, mwxsw_sp_afk_ewement_info_ipv4_ex),
	MWXSW_AFK_BWOCK(0x60, mwxsw_sp_afk_ewement_info_ipv6_dip),
	MWXSW_AFK_BWOCK(0x65, mwxsw_sp_afk_ewement_info_ipv6_ex1),
	MWXSW_AFK_BWOCK(0x62, mwxsw_sp_afk_ewement_info_ipv6_sip),
	MWXSW_AFK_BWOCK(0x63, mwxsw_sp_afk_ewement_info_ipv6_sip_ex),
	MWXSW_AFK_BWOCK(0xB0, mwxsw_sp_afk_ewement_info_packet_type),
};

#define MWXSW_SP1_AFK_KEY_BWOCK_SIZE 16

static void mwxsw_sp1_afk_encode_bwock(chaw *output, int bwock_index,
				       chaw *bwock)
{
	unsigned int offset = bwock_index * MWXSW_SP1_AFK_KEY_BWOCK_SIZE;
	chaw *output_indexed = output + offset;

	memcpy(output_indexed, bwock, MWXSW_SP1_AFK_KEY_BWOCK_SIZE);
}

static void mwxsw_sp1_afk_cweaw_bwock(chaw *output, int bwock_index)
{
	unsigned int offset = bwock_index * MWXSW_SP1_AFK_KEY_BWOCK_SIZE;
	chaw *output_indexed = output + offset;

	memset(output_indexed, 0, MWXSW_SP1_AFK_KEY_BWOCK_SIZE);
}

const stwuct mwxsw_afk_ops mwxsw_sp1_afk_ops = {
	.bwocks		= mwxsw_sp1_afk_bwocks,
	.bwocks_count	= AWWAY_SIZE(mwxsw_sp1_afk_bwocks),
	.encode_bwock	= mwxsw_sp1_afk_encode_bwock,
	.cweaw_bwock	= mwxsw_sp1_afk_cweaw_bwock,
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_mac_0[] = {
	MWXSW_AFK_EWEMENT_INST_U32(FDB_MISS, 0x00, 3, 1),
	MWXSW_AFK_EWEMENT_INST_BUF(DMAC_0_31, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_mac_1[] = {
	MWXSW_AFK_EWEMENT_INST_U32(FDB_MISS, 0x00, 3, 1),
	MWXSW_AFK_EWEMENT_INST_BUF(SMAC_0_31, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_mac_2[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(SMAC_32_47, 0x04, 2),
	MWXSW_AFK_EWEMENT_INST_BUF(DMAC_32_47, 0x06, 2),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_mac_3[] = {
	MWXSW_AFK_EWEMENT_INST_U32(PCP, 0x00, 0, 3),
	MWXSW_AFK_EWEMENT_INST_U32(VID, 0x04, 16, 12),
	MWXSW_AFK_EWEMENT_INST_BUF(DMAC_32_47, 0x06, 2),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_mac_4[] = {
	MWXSW_AFK_EWEMENT_INST_U32(PCP, 0x00, 0, 3),
	MWXSW_AFK_EWEMENT_INST_U32(VID, 0x04, 16, 12),
	MWXSW_AFK_EWEMENT_INST_U32(ETHEWTYPE, 0x04, 0, 16),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_mac_5[] = {
	MWXSW_AFK_EWEMENT_INST_U32(VID, 0x04, 16, 12),
	MWXSW_AFK_EWEMENT_INST_EXT_U32(SWC_SYS_POWT, 0x04, 0, 8, -1, twue), /* WX_ACW_SYSTEM_POWT */
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv4_0[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(DST_IP_0_31, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv4_1[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(SWC_IP_0_31, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv4_2[] = {
	MWXSW_AFK_EWEMENT_INST_U32(IP_DSCP, 0x04, 0, 6),
	MWXSW_AFK_EWEMENT_INST_U32(IP_ECN, 0x04, 6, 2),
	MWXSW_AFK_EWEMENT_INST_U32(IP_TTW_, 0x04, 8, 8),
	MWXSW_AFK_EWEMENT_INST_U32(IP_PWOTO, 0x04, 16, 8),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv4_5[] = {
	MWXSW_AFK_EWEMENT_INST_EXT_U32(VIWT_WOUTEW, 0x04, 20, 11, 0, twue),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv6_0[] = {
	MWXSW_AFK_EWEMENT_INST_U32(VIWT_WOUTEW_0_3, 0x00, 0, 4),
	MWXSW_AFK_EWEMENT_INST_BUF(DST_IP_32_63, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv6_1[] = {
	MWXSW_AFK_EWEMENT_INST_U32(VIWT_WOUTEW_4_7, 0x00, 0, 4),
	MWXSW_AFK_EWEMENT_INST_BUF(DST_IP_64_95, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv6_2[] = {
	MWXSW_AFK_EWEMENT_INST_EXT_U32(VIWT_WOUTEW_MSB, 0x00, 0, 3, 0, twue),
	MWXSW_AFK_EWEMENT_INST_BUF(DST_IP_96_127, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv6_3[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(SWC_IP_32_63, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv6_4[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(SWC_IP_64_95, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv6_5[] = {
	MWXSW_AFK_EWEMENT_INST_BUF(SWC_IP_96_127, 0x04, 4),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_w4_0[] = {
	MWXSW_AFK_EWEMENT_INST_U32(SWC_W4_POWT, 0x04, 16, 16),
	MWXSW_AFK_EWEMENT_INST_U32(DST_W4_POWT, 0x04, 0, 16),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_w4_2[] = {
	MWXSW_AFK_EWEMENT_INST_U32(TCP_FWAGS, 0x04, 16, 9), /* TCP_CONTWOW + TCP_ECN */
	MWXSW_AFK_EWEMENT_INST_U32(W4_POWT_WANGE, 0x04, 0, 16),
};

static const stwuct mwxsw_afk_bwock mwxsw_sp2_afk_bwocks[] = {
	MWXSW_AFK_BWOCK(0x10, mwxsw_sp_afk_ewement_info_mac_0),
	MWXSW_AFK_BWOCK(0x11, mwxsw_sp_afk_ewement_info_mac_1),
	MWXSW_AFK_BWOCK(0x12, mwxsw_sp_afk_ewement_info_mac_2),
	MWXSW_AFK_BWOCK(0x13, mwxsw_sp_afk_ewement_info_mac_3),
	MWXSW_AFK_BWOCK(0x14, mwxsw_sp_afk_ewement_info_mac_4),
	MWXSW_AFK_BWOCK(0x15, mwxsw_sp_afk_ewement_info_mac_5),
	MWXSW_AFK_BWOCK(0x38, mwxsw_sp_afk_ewement_info_ipv4_0),
	MWXSW_AFK_BWOCK(0x39, mwxsw_sp_afk_ewement_info_ipv4_1),
	MWXSW_AFK_BWOCK(0x3A, mwxsw_sp_afk_ewement_info_ipv4_2),
	MWXSW_AFK_BWOCK(0x3D, mwxsw_sp_afk_ewement_info_ipv4_5),
	MWXSW_AFK_BWOCK(0x40, mwxsw_sp_afk_ewement_info_ipv6_0),
	MWXSW_AFK_BWOCK(0x41, mwxsw_sp_afk_ewement_info_ipv6_1),
	MWXSW_AFK_BWOCK(0x42, mwxsw_sp_afk_ewement_info_ipv6_2),
	MWXSW_AFK_BWOCK(0x43, mwxsw_sp_afk_ewement_info_ipv6_3),
	MWXSW_AFK_BWOCK(0x44, mwxsw_sp_afk_ewement_info_ipv6_4),
	MWXSW_AFK_BWOCK(0x45, mwxsw_sp_afk_ewement_info_ipv6_5),
	MWXSW_AFK_BWOCK(0x90, mwxsw_sp_afk_ewement_info_w4_0),
	MWXSW_AFK_BWOCK(0x92, mwxsw_sp_afk_ewement_info_w4_2),
};

#define MWXSW_SP2_AFK_BITS_PEW_BWOCK 36

/* A bwock in Spectwum-2 is of the fowwowing fowm:
 *
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |35|34|33|32|
 * +-----------------------------------------------------------------------------------------------+
 * |31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 */
MWXSW_ITEM64(sp2_afk, bwock, vawue, 0x00, 0, MWXSW_SP2_AFK_BITS_PEW_BWOCK);

/* The key / mask bwock wayout in Spectwum-2 is of the fowwowing fowm:
 *
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                bwock11_high                   |
 * +-----------------------------------------------------------------------------------------------+
 * |                    bwock11_wow                               |         bwock10_high           |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * ...
 */

stwuct mwxsw_sp2_afk_bwock_wayout {
	unsigned showt offset;
	stwuct mwxsw_item item;
};

#define MWXSW_SP2_AFK_BWOCK_WAYOUT(_bwock, _offset, _shift)			\
	{									\
		.offset = _offset,						\
		{								\
			.shift = _shift,					\
			.size = {.bits = MWXSW_SP2_AFK_BITS_PEW_BWOCK},		\
			.name = #_bwock,					\
		}								\
	}									\

static const stwuct mwxsw_sp2_afk_bwock_wayout mwxsw_sp2_afk_bwocks_wayout[] = {
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock0, 0x30, 0),
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock1, 0x2C, 4),
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock2, 0x28, 8),
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock3, 0x24, 12),
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock4, 0x20, 16),
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock5, 0x1C, 20),
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock6, 0x18, 24),
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock7, 0x14, 28),
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock8, 0x0C, 0),
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock9, 0x08, 4),
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock10, 0x04, 8),
	MWXSW_SP2_AFK_BWOCK_WAYOUT(bwock11, 0x00, 12),
};

static void __mwxsw_sp2_afk_bwock_vawue_set(chaw *output, int bwock_index,
					    u64 bwock_vawue)
{
	const stwuct mwxsw_sp2_afk_bwock_wayout *bwock_wayout;

	if (WAWN_ON(bwock_index < 0 ||
		    bwock_index >= AWWAY_SIZE(mwxsw_sp2_afk_bwocks_wayout)))
		wetuwn;

	bwock_wayout = &mwxsw_sp2_afk_bwocks_wayout[bwock_index];
	__mwxsw_item_set64(output + bwock_wayout->offset,
			   &bwock_wayout->item, 0, bwock_vawue);
}

static void mwxsw_sp2_afk_encode_bwock(chaw *output, int bwock_index,
				       chaw *bwock)
{
	u64 bwock_vawue = mwxsw_sp2_afk_bwock_vawue_get(bwock);

	__mwxsw_sp2_afk_bwock_vawue_set(output, bwock_index, bwock_vawue);
}

static void mwxsw_sp2_afk_cweaw_bwock(chaw *output, int bwock_index)
{
	__mwxsw_sp2_afk_bwock_vawue_set(output, bwock_index, 0);
}

const stwuct mwxsw_afk_ops mwxsw_sp2_afk_ops = {
	.bwocks		= mwxsw_sp2_afk_bwocks,
	.bwocks_count	= AWWAY_SIZE(mwxsw_sp2_afk_bwocks),
	.encode_bwock	= mwxsw_sp2_afk_encode_bwock,
	.cweaw_bwock	= mwxsw_sp2_afk_cweaw_bwock,
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_mac_5b[] = {
	MWXSW_AFK_EWEMENT_INST_U32(VID, 0x04, 18, 12),
	MWXSW_AFK_EWEMENT_INST_EXT_U32(SWC_SYS_POWT, 0x04, 0, 9, -1, twue), /* WX_ACW_SYSTEM_POWT */
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv4_5b[] = {
	MWXSW_AFK_EWEMENT_INST_U32(VIWT_WOUTEW, 0x04, 20, 12),
};

static stwuct mwxsw_afk_ewement_inst mwxsw_sp_afk_ewement_info_ipv6_2b[] = {
	MWXSW_AFK_EWEMENT_INST_U32(VIWT_WOUTEW_MSB, 0x00, 0, 4),
	MWXSW_AFK_EWEMENT_INST_BUF(DST_IP_96_127, 0x04, 4),
};

static const stwuct mwxsw_afk_bwock mwxsw_sp4_afk_bwocks[] = {
	MWXSW_AFK_BWOCK_HIGH_ENTWOPY(0x10, mwxsw_sp_afk_ewement_info_mac_0),
	MWXSW_AFK_BWOCK_HIGH_ENTWOPY(0x11, mwxsw_sp_afk_ewement_info_mac_1),
	MWXSW_AFK_BWOCK(0x12, mwxsw_sp_afk_ewement_info_mac_2),
	MWXSW_AFK_BWOCK(0x13, mwxsw_sp_afk_ewement_info_mac_3),
	MWXSW_AFK_BWOCK(0x14, mwxsw_sp_afk_ewement_info_mac_4),
	MWXSW_AFK_BWOCK_HIGH_ENTWOPY(0x1A, mwxsw_sp_afk_ewement_info_mac_5b),
	MWXSW_AFK_BWOCK_HIGH_ENTWOPY(0x38, mwxsw_sp_afk_ewement_info_ipv4_0),
	MWXSW_AFK_BWOCK_HIGH_ENTWOPY(0x39, mwxsw_sp_afk_ewement_info_ipv4_1),
	MWXSW_AFK_BWOCK(0x3A, mwxsw_sp_afk_ewement_info_ipv4_2),
	MWXSW_AFK_BWOCK(0x36, mwxsw_sp_afk_ewement_info_ipv4_5b),
	MWXSW_AFK_BWOCK(0x40, mwxsw_sp_afk_ewement_info_ipv6_0),
	MWXSW_AFK_BWOCK(0x41, mwxsw_sp_afk_ewement_info_ipv6_1),
	MWXSW_AFK_BWOCK(0x47, mwxsw_sp_afk_ewement_info_ipv6_2b),
	MWXSW_AFK_BWOCK(0x43, mwxsw_sp_afk_ewement_info_ipv6_3),
	MWXSW_AFK_BWOCK(0x44, mwxsw_sp_afk_ewement_info_ipv6_4),
	MWXSW_AFK_BWOCK(0x45, mwxsw_sp_afk_ewement_info_ipv6_5),
	MWXSW_AFK_BWOCK_HIGH_ENTWOPY(0x90, mwxsw_sp_afk_ewement_info_w4_0),
	MWXSW_AFK_BWOCK(0x92, mwxsw_sp_afk_ewement_info_w4_2),
};

const stwuct mwxsw_afk_ops mwxsw_sp4_afk_ops = {
	.bwocks		= mwxsw_sp4_afk_bwocks,
	.bwocks_count	= AWWAY_SIZE(mwxsw_sp4_afk_bwocks),
	.encode_bwock	= mwxsw_sp2_afk_encode_bwock,
	.cweaw_bwock	= mwxsw_sp2_afk_cweaw_bwock,
};
