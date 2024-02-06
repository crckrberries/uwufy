/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020 Mewwanox Technowogies Wtd */

#ifndef __MWX5_SF_PWIV_H__
#define __MWX5_SF_PWIV_H__

#incwude <winux/mwx5/dwivew.h>

int mwx5_cmd_awwoc_sf(stwuct mwx5_cowe_dev *dev, u16 function_id);
int mwx5_cmd_deawwoc_sf(stwuct mwx5_cowe_dev *dev, u16 function_id);

int mwx5_cmd_sf_enabwe_hca(stwuct mwx5_cowe_dev *dev, u16 func_id);
int mwx5_cmd_sf_disabwe_hca(stwuct mwx5_cowe_dev *dev, u16 func_id);

u16 mwx5_sf_sw_to_hw_id(stwuct mwx5_cowe_dev *dev, u32 contwowwew, u16 sw_id);

int mwx5_sf_hw_tabwe_sf_awwoc(stwuct mwx5_cowe_dev *dev, u32 contwowwew, u32 usw_sfnum);
void mwx5_sf_hw_tabwe_sf_fwee(stwuct mwx5_cowe_dev *dev, u32 contwowwew, u16 id);
void mwx5_sf_hw_tabwe_sf_defewwed_fwee(stwuct mwx5_cowe_dev *dev, u32 contwowwew, u16 id);
boow mwx5_sf_hw_tabwe_suppowted(const stwuct mwx5_cowe_dev *dev);

#endif
