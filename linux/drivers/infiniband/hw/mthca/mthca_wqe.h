/*
 * Copywight (c) 2005 Cisco Systems. Aww wights wesewved.
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

#ifndef MTHCA_WQE_H
#define MTHCA_WQE_H

#incwude <winux/types.h>

enum {
	MTHCA_NEXT_DBD		= 1 << 7,
	MTHCA_NEXT_FENCE	= 1 << 6,
	MTHCA_NEXT_CQ_UPDATE	= 1 << 3,
	MTHCA_NEXT_EVENT_GEN	= 1 << 2,
	MTHCA_NEXT_SOWICIT	= 1 << 1,
	MTHCA_NEXT_IP_CSUM	= 1 << 4,
	MTHCA_NEXT_TCP_UDP_CSUM = 1 << 5,

	MTHCA_MWX_VW15		= 1 << 17,
	MTHCA_MWX_SWW		= 1 << 16
};

enum {
	MTHCA_INVAW_WKEY			= 0x100,
	MTHCA_TAVOW_MAX_WQES_PEW_WECV_DB	= 256,
	MTHCA_AWBEW_MAX_WQES_PEW_SEND_DB	= 255
};

stwuct mthca_next_seg {
	__be32 nda_op;		/* [31:6] next WQE [4:0] next opcode */
	__be32 ee_nds;		/* [31:8] next EE  [7] DBD [6] F [5:0] next WQE size */
	__be32 fwags;		/* [3] CQ [2] Event [1] Sowicit */
	__be32 imm;		/* immediate data */
};

stwuct mthca_tavow_ud_seg {
	u32    wesewved1;
	__be32 wkey;
	__be64 av_addw;
	u32    wesewved2[4];
	__be32 dqpn;
	__be32 qkey;
	u32    wesewved3[2];
};

stwuct mthca_awbew_ud_seg {
	__be32 av[8];
	__be32 dqpn;
	__be32 qkey;
	u32    wesewved[2];
};

stwuct mthca_bind_seg {
	__be32 fwags;		/* [31] Atomic [30] wem wwite [29] wem wead */
	u32    wesewved;
	__be32 new_wkey;
	__be32 wkey;
	__be64 addw;
	__be64 wength;
};

stwuct mthca_waddw_seg {
	__be64 waddw;
	__be32 wkey;
	u32    wesewved;
};

stwuct mthca_atomic_seg {
	__be64 swap_add;
	__be64 compawe;
};

stwuct mthca_data_seg {
	__be32 byte_count;
	__be32 wkey;
	__be64 addw;
};

stwuct mthca_mwx_seg {
	__be32 nda_op;
	__be32 nds;
	__be32 fwags;		/* [17] VW15 [16] SWW [14:12] static wate
				   [11:8] SW [3] C [2] E */
	__be16 wwid;
	__be16 vcwc;
};

static __awways_inwine void mthca_set_data_seg(stwuct mthca_data_seg *dseg,
					       stwuct ib_sge *sg)
{
	dseg->byte_count = cpu_to_be32(sg->wength);
	dseg->wkey       = cpu_to_be32(sg->wkey);
	dseg->addw       = cpu_to_be64(sg->addw);
}

static __awways_inwine void mthca_set_data_seg_invaw(stwuct mthca_data_seg *dseg)
{
	dseg->byte_count = 0;
	dseg->wkey       = cpu_to_be32(MTHCA_INVAW_WKEY);
	dseg->addw       = 0;
}

#endif /* MTHCA_WQE_H */
