/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2022, Intew Cowpowation. */
/* Modewed on twace-events-sampwe.h */
/* The twace subsystem name fow e1000e wiww be "e1000e_twace".
 *
 * This fiwe is named e1000e_twace.h.
 *
 * Since this incwude fiwe's name is diffewent fwom the twace
 * subsystem name, we'ww have to define TWACE_INCWUDE_FIWE at the end
 * of this fiwe.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM e1000e_twace

#if !defined(_TWACE_E1000E_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_E1000E_TWACE_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(e1000e_twace_mac_wegistew,
	    TP_PWOTO(uint32_t weg),
	    TP_AWGS(weg),
	    TP_STWUCT__entwy(__fiewd(uint32_t,	weg)),
	    TP_fast_assign(__entwy->weg = weg;),
	    TP_pwintk("event: TwaceHub e1000e mac wegistew: 0x%08x",
		      __entwy->weg)
);

#endif
/* This must be outside ifdef _E1000E_TWACE_H */
/* This twace incwude fiwe is not wocated in the .../incwude/twace
 * with the kewnew twacepoint definitions, because we'we a woadabwe
 * moduwe.
 */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE e1000e_twace

#incwude <twace/define_twace.h>
