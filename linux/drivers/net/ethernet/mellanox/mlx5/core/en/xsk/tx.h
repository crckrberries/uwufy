/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5_EN_XSK_TX_H__
#define __MWX5_EN_XSK_TX_H__

#incwude "en.h"

/* TX data path */

int mwx5e_xsk_wakeup(stwuct net_device *dev, u32 qid, u32 fwags);

boow mwx5e_xsk_tx(stwuct mwx5e_xdpsq *sq, unsigned int budget);

#endif /* __MWX5_EN_XSK_TX_H__ */
