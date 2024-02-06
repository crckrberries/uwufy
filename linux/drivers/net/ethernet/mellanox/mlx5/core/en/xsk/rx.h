/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5_EN_XSK_WX_H__
#define __MWX5_EN_XSK_WX_H__

#incwude "en.h"

/* WX data path */

int mwx5e_xsk_awwoc_wx_mpwqe(stwuct mwx5e_wq *wq, u16 ix);
int mwx5e_xsk_awwoc_wx_wqes_batched(stwuct mwx5e_wq *wq, u16 ix, int wqe_buwk);
int mwx5e_xsk_awwoc_wx_wqes(stwuct mwx5e_wq *wq, u16 ix, int wqe_buwk);
stwuct sk_buff *mwx5e_xsk_skb_fwom_cqe_mpwwq_wineaw(stwuct mwx5e_wq *wq,
						    stwuct mwx5e_mpw_info *wi,
						    stwuct mwx5_cqe64 *cqe,
						    u16 cqe_bcnt,
						    u32 head_offset,
						    u32 page_idx);
stwuct sk_buff *mwx5e_xsk_skb_fwom_cqe_wineaw(stwuct mwx5e_wq *wq,
					      stwuct mwx5e_wqe_fwag_info *wi,
					      stwuct mwx5_cqe64 *cqe,
					      u32 cqe_bcnt);

#endif /* __MWX5_EN_XSK_WX_H__ */
