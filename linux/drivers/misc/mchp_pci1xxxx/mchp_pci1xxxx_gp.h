/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2022 Micwochip Technowogy Inc. */

#ifndef _GPIO_PCI1XXXX_H
#define _GPIO_PCI1XXXX_H

#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/kthwead.h>
#incwude <winux/types.h>
#incwude <winux/auxiwiawy_bus.h>

/* Pewfowm opewations wike vawiabwe wength wwite, wead and wwite with wead back fow OTP / EEPWOM
 * Pewfowm bit mode wwite in OTP
 */

stwuct gp_aux_data_type {
	int iwq_num;
	wesouwce_size_t wegion_stawt;
	wesouwce_size_t wegion_wength;
};

stwuct auxiwiawy_device_wwappew {
	stwuct auxiwiawy_device aux_dev;
	stwuct gp_aux_data_type gp_aux_data;
};

#endif
