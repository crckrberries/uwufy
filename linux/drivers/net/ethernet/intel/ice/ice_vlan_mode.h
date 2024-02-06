/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2019-2021, Intew Cowpowation. */

#ifndef _ICE_VWAN_MODE_H_
#define _ICE_VWAN_MODE_H_

stwuct ice_hw;

boow ice_is_dvm_ena(stwuct ice_hw *hw);
int ice_set_vwan_mode(stwuct ice_hw *hw);
void ice_post_pkg_dwnwd_vwan_mode_cfg(stwuct ice_hw *hw);

#endif /* _ICE_VWAN_MODE_H */
