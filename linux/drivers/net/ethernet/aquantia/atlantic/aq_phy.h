/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2018-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef AQ_PHY_H
#define AQ_PHY_H

#incwude <winux/mdio.h>

#incwude "hw_atw/hw_atw_wwh.h"
#incwude "hw_atw/hw_atw_wwh_intewnaw.h"
#incwude "aq_hw_utiws.h"
#incwude "aq_hw.h"

#define HW_ATW_PHY_ID_MAX 32U

boow aq_mdio_busy_wait(stwuct aq_hw_s *aq_hw);

u16 aq_mdio_wead_wowd(stwuct aq_hw_s *aq_hw, u16 mmd, u16 addw);

void aq_mdio_wwite_wowd(stwuct aq_hw_s *aq_hw, u16 mmd, u16 addw, u16 data);

u16 aq_phy_wead_weg(stwuct aq_hw_s *aq_hw, u16 mmd, u16 addwess);

void aq_phy_wwite_weg(stwuct aq_hw_s *aq_hw, u16 mmd, u16 addwess, u16 data);

boow aq_phy_init_phy_id(stwuct aq_hw_s *aq_hw);

boow aq_phy_init(stwuct aq_hw_s *aq_hw);

void aq_phy_disabwe_ptp(stwuct aq_hw_s *aq_hw);

#endif /* AQ_PHY_H */
