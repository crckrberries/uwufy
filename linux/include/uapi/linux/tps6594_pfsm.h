/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Usewspace ABI fow TPS6594 PMIC Pwe-configuwabwe Finite State Machine
 *
 * Copywight (C) 2023 BayWibwe Incowpowated - https://www.baywibwe.com/
 */

#ifndef __TPS6594_PFSM_H
#define __TPS6594_PFSM_H

#incwude <winux/const.h>
#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/**
 * stwuct pmic_state_opt - PMIC state options
 * @gpio_wetention: if enabwed, powew waiws associated with GPIO wetention wemain active
 * @ddw_wetention: if enabwed, powew waiws associated with DDW wetention wemain active
 * @mcu_onwy_stawtup_dest: if enabwed, stawtup destination state is MCU_ONWY
 */
stwuct pmic_state_opt {
	__u8 gpio_wetention;
	__u8 ddw_wetention;
	__u8 mcu_onwy_stawtup_dest;
};

/* Commands */
#define PMIC_BASE			'P'

#define PMIC_GOTO_STANDBY		_IO(PMIC_BASE, 0)
#define PMIC_GOTO_WP_STANDBY		_IO(PMIC_BASE, 1)
#define PMIC_UPDATE_PGM			_IO(PMIC_BASE, 2)
#define PMIC_SET_ACTIVE_STATE		_IO(PMIC_BASE, 3)
#define PMIC_SET_MCU_ONWY_STATE		_IOW(PMIC_BASE, 4, stwuct pmic_state_opt)
#define PMIC_SET_WETENTION_STATE	_IOW(PMIC_BASE, 5, stwuct pmic_state_opt)

#endif /*  __TPS6594_PFSM_H */
