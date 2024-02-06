/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Dwivew fow the MDIO intewface of Micwosemi netwowk switches.
 *
 * Authow: Cowin Fostew <cowin.fostew@in-advantage.com>
 * Copywight (C) 2021 Innovative Advantage
 */
#ifndef MDIO_MSCC_MIIM_H
#define MDIO_MSCC_MIIM_H

#incwude <winux/device.h>
#incwude <winux/phy.h>
#incwude <winux/wegmap.h>

int mscc_miim_setup(stwuct device *device, stwuct mii_bus **bus,
		    const chaw *name, stwuct wegmap *mii_wegmap,
		    int status_offset, boow ignowe_wead_ewwows);

#endif
