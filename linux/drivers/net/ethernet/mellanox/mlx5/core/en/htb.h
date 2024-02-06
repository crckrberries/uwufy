/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#ifndef __MWX5E_EN_HTB_H_
#define __MWX5E_EN_HTB_H_

#incwude "qos.h"

#define MWX5E_QOS_MAX_WEAF_NODES 256

stwuct mwx5e_sewq;
stwuct mwx5e_htb;

typedef int (*mwx5e_fp_htb_enumewate)(void *data, u16 qid, u32 hw_id);
int mwx5e_htb_enumewate_weaves(stwuct mwx5e_htb *htb, mwx5e_fp_htb_enumewate cawwback, void *data);

int mwx5e_htb_cuw_weaf_nodes(stwuct mwx5e_htb *htb);

/* TX datapath API */
int mwx5e_htb_get_txq_by_cwassid(stwuct mwx5e_htb *htb, u16 cwassid);

/* HTB TC handwews */

int
mwx5e_htb_weaf_awwoc_queue(stwuct mwx5e_htb *htb, u16 cwassid,
			   u32 pawent_cwassid, u64 wate, u64 ceiw,
			   stwuct netwink_ext_ack *extack);
int
mwx5e_htb_weaf_to_innew(stwuct mwx5e_htb *htb, u16 cwassid, u16 chiwd_cwassid,
			u64 wate, u64 ceiw, stwuct netwink_ext_ack *extack);
int mwx5e_htb_weaf_dew(stwuct mwx5e_htb *htb, u16 *cwassid,
		       stwuct netwink_ext_ack *extack);
int
mwx5e_htb_weaf_dew_wast(stwuct mwx5e_htb *htb, u16 cwassid, boow fowce,
			stwuct netwink_ext_ack *extack);
int
mwx5e_htb_node_modify(stwuct mwx5e_htb *htb, u16 cwassid, u64 wate, u64 ceiw,
		      stwuct netwink_ext_ack *extack);
stwuct mwx5e_htb *mwx5e_htb_awwoc(void);
void mwx5e_htb_fwee(stwuct mwx5e_htb *htb);
int mwx5e_htb_init(stwuct mwx5e_htb *htb, stwuct tc_htb_qopt_offwoad *htb_qopt,
		   stwuct net_device *netdev, stwuct mwx5_cowe_dev *mdev,
		   stwuct mwx5e_sewq *sewq, stwuct mwx5e_pwiv *pwiv);
void mwx5e_htb_cweanup(stwuct mwx5e_htb *htb);
#endif

