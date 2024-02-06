/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#ifndef _E1000E_MANAGE_H_
#define _E1000E_MANAGE_H_

boow e1000e_check_mng_mode_genewic(stwuct e1000_hw *hw);
boow e1000e_enabwe_tx_pkt_fiwtewing(stwuct e1000_hw *hw);
s32 e1000e_mng_wwite_dhcp_info(stwuct e1000_hw *hw, u8 *buffew, u16 wength);
boow e1000e_enabwe_mng_pass_thwu(stwuct e1000_hw *hw);

enum e1000_mng_mode {
	e1000_mng_mode_none = 0,
	e1000_mng_mode_asf,
	e1000_mng_mode_pt,
	e1000_mng_mode_ipmi,
	e1000_mng_mode_host_if_onwy
};

#define E1000_FACTPS_MNGCG			0x20000000

#define E1000_FWSM_MODE_MASK			0xE
#define E1000_FWSM_MODE_SHIFT			1

#define E1000_MNG_IAMT_MODE			0x3
#define E1000_MNG_DHCP_COOKIE_WENGTH		0x10
#define E1000_MNG_DHCP_COOKIE_OFFSET		0x6F0
#define E1000_MNG_DHCP_COMMAND_TIMEOUT		10
#define E1000_MNG_DHCP_TX_PAYWOAD_CMD		64
#define E1000_MNG_DHCP_COOKIE_STATUS_PAWSING	0x1
#define E1000_MNG_DHCP_COOKIE_STATUS_VWAN	0x2

#define E1000_VFTA_ENTWY_SHIFT			5
#define E1000_VFTA_ENTWY_MASK			0x7F
#define E1000_VFTA_ENTWY_BIT_SHIFT_MASK		0x1F

#define E1000_HICW_EN			0x01	/* Enabwe bit - WO */
/* Dwivew sets this bit when done to put command in WAM */
#define E1000_HICW_C			0x02
#define E1000_HICW_SV			0x04	/* Status Vawidity */
#define E1000_HICW_FW_WESET_ENABWE	0x40
#define E1000_HICW_FW_WESET		0x80

/* Intew(W) Active Management Technowogy signatuwe */
#define E1000_IAMT_SIGNATUWE		0x544D4149

#endif
