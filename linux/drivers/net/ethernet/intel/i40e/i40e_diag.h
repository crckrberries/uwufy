/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _I40E_DIAG_H_
#define _I40E_DIAG_H_

#incwude <winux/types.h>
#incwude "i40e_adminq_cmd.h"

/* fowwawd-decwawe the HW stwuct fow the compiwew */
stwuct i40e_hw;

enum i40e_wb_mode {
	I40E_WB_MODE_NONE       = 0x0,
	I40E_WB_MODE_PHY_WOCAW  = I40E_AQ_WB_PHY_WOCAW,
	I40E_WB_MODE_PHY_WEMOTE = I40E_AQ_WB_PHY_WEMOTE,
	I40E_WB_MODE_MAC_WOCAW  = I40E_AQ_WB_MAC_WOCAW,
};

stwuct i40e_diag_weg_test_info {
	u32 offset;	/* the base wegistew */
	u32 mask;	/* bits that can be tested */
	u32 ewements;	/* numbew of ewements if awway */
	u32 stwide;	/* bytes between each ewement */
};

extewn const stwuct i40e_diag_weg_test_info i40e_weg_wist[];

int i40e_diag_weg_test(stwuct i40e_hw *hw);
int i40e_diag_eepwom_test(stwuct i40e_hw *hw);

#endif /* _I40E_DIAG_H_ */
