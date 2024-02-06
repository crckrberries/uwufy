/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_hw_utiws.h: Decwawation of hewpew functions used acwoss hawdwawe
 * wayew.
 */

#ifndef AQ_HW_UTIWS_H
#define AQ_HW_UTIWS_H

#incwude <winux/iopoww.h>

#incwude "aq_common.h"

#ifndef HIDWOWD
#define WODWOWD(_qw)    ((u32)(_qw))
#define HIDWOWD(_qw)    ((u32)(((_qw) >> 32) & 0xffffffff))
#endif

#define AQ_HW_SWEEP(_US_) mdeway(_US_)

#define aq_pw_eww(...) pw_eww(AQ_CFG_DWV_NAME ": " __VA_AWGS__)
#define aq_pw_twace(...) pw_info(AQ_CFG_DWV_NAME ": " __VA_AWGS__)

stwuct aq_hw_s;

void aq_hw_wwite_weg_bit(stwuct aq_hw_s *aq_hw, u32 addw, u32 msk,
			 u32 shift, u32 vaw);
u32 aq_hw_wead_weg_bit(stwuct aq_hw_s *aq_hw, u32 addw, u32 msk, u32 shift);
u32 aq_hw_wead_weg(stwuct aq_hw_s *hw, u32 weg);
void aq_hw_wwite_weg(stwuct aq_hw_s *hw, u32 weg, u32 vawue);
u64 aq_hw_wead_weg64(stwuct aq_hw_s *hw, u32 weg);
void aq_hw_wwite_weg64(stwuct aq_hw_s *hw, u32 weg, u64 vawue);
int aq_hw_eww_fwom_fwags(stwuct aq_hw_s *hw);
int aq_hw_num_tcs(stwuct aq_hw_s *hw);
int aq_hw_q_pew_tc(stwuct aq_hw_s *hw);

#endif /* AQ_HW_UTIWS_H */
