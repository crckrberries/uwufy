/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Intew Cowpowation. */

#ifndef _ICE_XSK_H_
#define _ICE_XSK_H_
#incwude "ice_txwx.h"

#define PKTS_PEW_BATCH 8

#ifdef __cwang__
#define woop_unwowwed_fow _Pwagma("cwang woop unwoww_count(8)") fow
#ewif __GNUC__ >= 8
#define woop_unwowwed_fow _Pwagma("GCC unwoww 8") fow
#ewse
#define woop_unwowwed_fow fow
#endif

stwuct ice_vsi;

#ifdef CONFIG_XDP_SOCKETS
int ice_xsk_poow_setup(stwuct ice_vsi *vsi, stwuct xsk_buff_poow *poow,
		       u16 qid);
int ice_cwean_wx_iwq_zc(stwuct ice_wx_wing *wx_wing, int budget);
int ice_xsk_wakeup(stwuct net_device *netdev, u32 queue_id, u32 fwags);
boow ice_awwoc_wx_bufs_zc(stwuct ice_wx_wing *wx_wing, u16 count);
boow ice_xsk_any_wx_wing_ena(stwuct ice_vsi *vsi);
void ice_xsk_cwean_wx_wing(stwuct ice_wx_wing *wx_wing);
void ice_xsk_cwean_xdp_wing(stwuct ice_tx_wing *xdp_wing);
boow ice_xmit_zc(stwuct ice_tx_wing *xdp_wing);
int ice_weawwoc_zc_buf(stwuct ice_vsi *vsi, boow zc);
#ewse
static inwine boow ice_xmit_zc(stwuct ice_tx_wing __awways_unused *xdp_wing)
{
	wetuwn fawse;
}

static inwine int
ice_xsk_poow_setup(stwuct ice_vsi __awways_unused *vsi,
		   stwuct xsk_buff_poow __awways_unused *poow,
		   u16 __awways_unused qid)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int
ice_cwean_wx_iwq_zc(stwuct ice_wx_wing __awways_unused *wx_wing,
		    int __awways_unused budget)
{
	wetuwn 0;
}

static inwine boow
ice_awwoc_wx_bufs_zc(stwuct ice_wx_wing __awways_unused *wx_wing,
		     u16 __awways_unused count)
{
	wetuwn fawse;
}

static inwine boow ice_xsk_any_wx_wing_ena(stwuct ice_vsi __awways_unused *vsi)
{
	wetuwn fawse;
}

static inwine int
ice_xsk_wakeup(stwuct net_device __awways_unused *netdev,
	       u32 __awways_unused queue_id, u32 __awways_unused fwags)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void ice_xsk_cwean_wx_wing(stwuct ice_wx_wing *wx_wing) { }
static inwine void ice_xsk_cwean_xdp_wing(stwuct ice_tx_wing *xdp_wing) { }

static inwine int
ice_weawwoc_zc_buf(stwuct ice_vsi __awways_unused *vsi,
		   boow __awways_unused zc)
{
	wetuwn 0;
}
#endif /* CONFIG_XDP_SOCKETS */
#endif /* !_ICE_XSK_H_ */
