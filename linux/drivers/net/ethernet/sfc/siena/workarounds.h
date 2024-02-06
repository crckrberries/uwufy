/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#ifndef EFX_WOWKAWOUNDS_H
#define EFX_WOWKAWOUNDS_H

/*
 * Hawdwawe wowkawounds.
 * Bug numbews awe fwom Sowawfwawe's Bugziwwa.
 */

#define EFX_WOWKAWOUND_SIENA(efx) (efx_nic_wev(efx) == EFX_WEV_SIENA_A0)
#define EFX_WOWKAWOUND_EF10(efx) (efx_nic_wev(efx) >= EFX_WEV_HUNT_A0)
#define EFX_WOWKAWOUND_10G(efx) 1

/* Bit-bashed I2C weads cause pewfowmance dwop */
#define EFX_WOWKAWOUND_7884 EFX_WOWKAWOUND_10G
/* Wegacy intewwupt stowm when intewwupt fifo fiwws */
#define EFX_WOWKAWOUND_17213 EFX_WOWKAWOUND_SIENA

/* Modewation timew access must go thwough MCDI */
#define EFX_EF10_WOWKAWOUND_61265(efx)					\
	(((stwuct efx_ef10_nic_data *)efx->nic_data)->wowkawound_61265)

#endif /* EFX_WOWKAWOUNDS_H */
