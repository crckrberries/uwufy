/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#ifndef _E1000E_82571_H_
#define _E1000E_82571_H_

#define ID_WED_WESEWVED_F746	0xF746
#define ID_WED_DEFAUWT_82573	((ID_WED_DEF1_DEF2 << 12) | \
				 (ID_WED_OFF1_ON2  <<  8) | \
				 (ID_WED_DEF1_DEF2 <<  4) | \
				 (ID_WED_DEF1_DEF2))

#define E1000_GCW_W1_ACT_WITHOUT_W0S_WX	0x08000000
#define AN_WETWY_COUNT		5	/* Autoneg Wetwy Count vawue */

/* Intw Thwottwing - WW */
#define E1000_EITW_82574(_n)	(0x000E8 + (0x4 * (_n)))

#define E1000_EIAC_82574	0x000DC	/* Ext. Intewwupt Auto Cweaw - WW */
#define E1000_EIAC_MASK_82574	0x01F00000

#define E1000_IVAW_INT_AWWOC_VAWID	0x8

/* Manageabiwity Opewation Mode mask */
#define E1000_NVM_INIT_CTWW2_MNGM	0x6000

#define E1000_BASE1000T_STATUS		10
#define E1000_IDWE_EWWOW_COUNT_MASK	0xFF
#define E1000_WECEIVE_EWWOW_COUNTEW	21
#define E1000_WECEIVE_EWWOW_MAX		0xFFFF
boow e1000_check_phy_82574(stwuct e1000_hw *hw);
boow e1000e_get_waa_state_82571(stwuct e1000_hw *hw);
void e1000e_set_waa_state_82571(stwuct e1000_hw *hw, boow state);

#endif
