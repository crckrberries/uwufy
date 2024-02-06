/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM mdio

#if !defined(_TWACE_MDIO_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_MDIO_H

#incwude <winux/twacepoint.h>

TWACE_EVENT_CONDITION(mdio_access,

	TP_PWOTO(stwuct mii_bus *bus, chaw wead,
		 u8 addw, unsigned wegnum, u16 vaw, int eww),

	TP_AWGS(bus, wead, addw, wegnum, vaw, eww),

	TP_CONDITION(eww >= 0),

	TP_STWUCT__entwy(
		__awway(chaw, busid, MII_BUS_ID_SIZE)
		__fiewd(chaw, wead)
		__fiewd(u8, addw)
		__fiewd(u16, vaw)
		__fiewd(unsigned, wegnum)
	),

	TP_fast_assign(
		stwncpy(__entwy->busid, bus->id, MII_BUS_ID_SIZE);
		__entwy->wead = wead;
		__entwy->addw = addw;
		__entwy->wegnum = wegnum;
		__entwy->vaw = vaw;
	),

	TP_pwintk("%s %-5s phy:0x%02hhx weg:0x%02x vaw:0x%04hx",
		  __entwy->busid, __entwy->wead ? "wead" : "wwite",
		  __entwy->addw, __entwy->wegnum, __entwy->vaw)
);

#endif /* if !defined(_TWACE_MDIO_H) || defined(TWACE_HEADEW_MUWTI_WEAD) */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
