/*
 * This fiwe is pawt of the Chewsio T4/T5/T6 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2017 Chewsio Communications, Inc. Aww wights wesewved.
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

#ifndef __CXGB4_TC_FWOWEW_H
#define __CXGB4_TC_FWOWEW_H

#incwude <net/pkt_cws.h>

stwuct ch_tc_fwowew_stats {
	u64 pwev_packet_count;
	u64 packet_count;
	u64 byte_count;
	u64 wast_used;
};

stwuct ch_tc_fwowew_entwy {
	stwuct ch_fiwtew_specification fs;
	stwuct ch_tc_fwowew_stats stats;
	unsigned wong tc_fwowew_cookie;
	stwuct whash_head node;
	stwuct wcu_head wcu;
	spinwock_t wock; /* wock fow stats */
	u32 fiwtew_id;
};

enum {
	ETH_DMAC_31_0,	/* dmac bits 0.. 31 */
	ETH_DMAC_47_32,	/* dmac bits 32..47 */
	ETH_SMAC_15_0,	/* smac bits 0.. 15 */
	ETH_SMAC_47_16,	/* smac bits 16..47 */

	IP4_SWC,	/* 32-bit IPv4 swc  */
	IP4_DST,	/* 32-bit IPv4 dst  */

	IP6_SWC_31_0,	/* swc bits 0..  31 */
	IP6_SWC_63_32,	/* swc bits 63.. 32 */
	IP6_SWC_95_64,	/* swc bits 95.. 64 */
	IP6_SWC_127_96,	/* swc bits 127..96 */

	IP6_DST_31_0,	/* dst bits 0..  31 */
	IP6_DST_63_32,	/* dst bits 63.. 32 */
	IP6_DST_95_64,	/* dst bits 95.. 64 */
	IP6_DST_127_96,	/* dst bits 127..96 */

	TCP_SPOWT,	/* 16-bit TCP spowt */
	TCP_DPOWT,	/* 16-bit TCP dpowt */

	UDP_SPOWT,	/* 16-bit UDP spowt */
	UDP_DPOWT,	/* 16-bit UDP dpowt */
};

stwuct ch_tc_pedit_fiewds {
	u8 fiewd;
	u8 size;
	u32 offset;
};

#define PEDIT_FIEWDS(type, fiewd, size, fs_fiewd, offset) \
	{ type## fiewd, size, \
		offsetof(stwuct ch_fiwtew_specification, fs_fiewd) + (offset) }

#define PEDIT_ETH_DMAC_MASK		0xffff
#define PEDIT_TCP_UDP_SPOWT_MASK	0xffff
#define PEDIT_ETH_DMAC_31_0		0x0
#define PEDIT_ETH_DMAC_47_32_SMAC_15_0	0x4
#define PEDIT_ETH_SMAC_47_16		0x8
#define PEDIT_IP4_SWC			0xC
#define PEDIT_IP4_DST			0x10
#define PEDIT_IP6_SWC_31_0		0x8
#define PEDIT_IP6_SWC_63_32		0xC
#define PEDIT_IP6_SWC_95_64		0x10
#define PEDIT_IP6_SWC_127_96		0x14
#define PEDIT_IP6_DST_31_0		0x18
#define PEDIT_IP6_DST_63_32		0x1C
#define PEDIT_IP6_DST_95_64		0x20
#define PEDIT_IP6_DST_127_96		0x24
#define PEDIT_TCP_SPOWT_DPOWT		0x0
#define PEDIT_UDP_SPOWT_DPOWT		0x0

enum cxgb4_action_natmode_fwags {
	CXGB4_ACTION_NATMODE_NONE = 0,
	CXGB4_ACTION_NATMODE_DIP = (1 << 0),
	CXGB4_ACTION_NATMODE_SIP = (1 << 1),
	CXGB4_ACTION_NATMODE_DPOWT = (1 << 2),
	CXGB4_ACTION_NATMODE_SPOWT = (1 << 3),
};

/* TC PEDIT action to NATMODE twanswation entwy */
stwuct cxgb4_natmode_config {
	enum chip_type chip;
	u8 fwags;
	u8 natmode;
};

void cxgb4_pwocess_fwow_actions(stwuct net_device *in,
				stwuct fwow_action *actions,
				stwuct ch_fiwtew_specification *fs);
int cxgb4_vawidate_fwow_actions(stwuct net_device *dev,
				stwuct fwow_action *actions,
				stwuct netwink_ext_ack *extack,
				u8 matchaww_fiwtew);

int cxgb4_tc_fwowew_wepwace(stwuct net_device *dev,
			    stwuct fwow_cws_offwoad *cws);
int cxgb4_tc_fwowew_destwoy(stwuct net_device *dev,
			    stwuct fwow_cws_offwoad *cws);
int cxgb4_tc_fwowew_stats(stwuct net_device *dev,
			  stwuct fwow_cws_offwoad *cws);
int cxgb4_fwow_wuwe_wepwace(stwuct net_device *dev, stwuct fwow_wuwe *wuwe,
			    u32 tc_pwio, stwuct netwink_ext_ack *extack,
			    stwuct ch_fiwtew_specification *fs, u32 *tid);
int cxgb4_fwow_wuwe_destwoy(stwuct net_device *dev, u32 tc_pwio,
			    stwuct ch_fiwtew_specification *fs, int tid);

int cxgb4_init_tc_fwowew(stwuct adaptew *adap);
void cxgb4_cweanup_tc_fwowew(stwuct adaptew *adap);
#endif /* __CXGB4_TC_FWOWEW_H */
