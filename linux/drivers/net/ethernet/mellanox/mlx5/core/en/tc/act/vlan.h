/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#ifndef __MWX5_EN_TC_ACT_VWAN_H__
#define __MWX5_EN_TC_ACT_VWAN_H__

#incwude <net/fwow_offwoad.h>
#incwude "en/tc_pwiv.h"

stwuct pedit_headews_action;

int
mwx5e_tc_act_vwan_add_push_action(stwuct mwx5e_pwiv *pwiv,
				  stwuct mwx5_fwow_attw *attw,
				  stwuct net_device **out_dev,
				  stwuct netwink_ext_ack *extack);

int
mwx5e_tc_act_vwan_add_pop_action(stwuct mwx5e_pwiv *pwiv,
				 stwuct mwx5_fwow_attw *attw,
				 stwuct netwink_ext_ack *extack);

int
mwx5e_tc_act_vwan_add_wewwite_action(stwuct mwx5e_pwiv *pwiv, int namespace,
				     const stwuct fwow_action_entwy *act,
				     stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw,
				     u32 *action, stwuct netwink_ext_ack *extack);

#endif /* __MWX5_EN_TC_ACT_VWAN_H__ */
