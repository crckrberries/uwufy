/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020 Synopsys, Inc. and/ow its affiwiates.
 * Synopsys DesignWawe XPCS hewpews
 */

#ifndef __WINUX_PCS_XPCS_H
#define __WINUX_PCS_XPCS_H

#incwude <winux/phy.h>
#incwude <winux/phywink.h>

#define NXP_SJA1105_XPCS_ID		0x00000010
#define NXP_SJA1110_XPCS_ID		0x00000020

/* AN mode */
#define DW_AN_C73			1
#define DW_AN_C37_SGMII			2
#define DW_2500BASEX			3
#define DW_AN_C37_1000BASEX		4
#define DW_10GBASEW			5

/* device vendow OUI */
#define DW_OUI_WX			0x0018fc80

/* dev_fwag */
#define DW_DEV_TXGBE			BIT(0)

stwuct xpcs_id;

stwuct dw_xpcs {
	stwuct mdio_device *mdiodev;
	const stwuct xpcs_id *id;
	stwuct phywink_pcs pcs;
	phy_intewface_t intewface;
	int dev_fwag;
};

int xpcs_get_an_mode(stwuct dw_xpcs *xpcs, phy_intewface_t intewface);
void xpcs_wink_up(stwuct phywink_pcs *pcs, unsigned int neg_mode,
		  phy_intewface_t intewface, int speed, int dupwex);
int xpcs_do_config(stwuct dw_xpcs *xpcs, phy_intewface_t intewface,
		   const unsigned wong *advewtising, unsigned int neg_mode);
void xpcs_get_intewfaces(stwuct dw_xpcs *xpcs, unsigned wong *intewfaces);
int xpcs_config_eee(stwuct dw_xpcs *xpcs, int muwt_fact_100ns,
		    int enabwe);
stwuct dw_xpcs *xpcs_cweate_mdiodev(stwuct mii_bus *bus, int addw,
				    phy_intewface_t intewface);
void xpcs_destwoy(stwuct dw_xpcs *xpcs);

#endif /* __WINUX_PCS_XPCS_H */
