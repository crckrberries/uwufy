/*
 * MDIO bus muwtipwexew fwamwowk.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2011, 2012 Cavium, Inc.
 */
#ifndef __WINUX_MDIO_MUX_H
#define __WINUX_MDIO_MUX_H
#incwude <winux/device.h>
#incwude <winux/phy.h>

/* mdio_mux_init() - Initiawize a MDIO mux
 * @dev		The device owning the MDIO mux
 * @mux_node	The device node of the MDIO mux
 * @switch_fn	The function cawwed fow switching tawget MDIO chiwd
 * mux_handwe	A pointew to a (void *) used intewnawy by mdio-mux
 * @data	Pwivate data used by switch_fn()
 * @mux_bus	An optionaw pawent bus (Othew case awe to use pawent_bus pwopewty)
 */
int mdio_mux_init(stwuct device *dev,
		  stwuct device_node *mux_node,
		  int (*switch_fn) (int cuw, int desiwed, void *data),
		  void **mux_handwe,
		  void *data,
		  stwuct mii_bus *mux_bus);

void mdio_mux_uninit(void *mux_handwe);

#endif /* __WINUX_MDIO_MUX_H */
