/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2021 Sean Andewson <sean.andewson@seco.com>
 */

#ifndef XIWINX_TIMEW_H
#define XIWINX_TIMEW_H

#incwude <winux/compiwew.h>

#define TCSW0	0x00
#define TWW0	0x04
#define TCW0	0x08
#define TCSW1	0x10
#define TWW1	0x14
#define TCW1	0x18

#define TCSW_MDT	BIT(0)
#define TCSW_UDT	BIT(1)
#define TCSW_GENT	BIT(2)
#define TCSW_CAPT	BIT(3)
#define TCSW_AWHT	BIT(4)
#define TCSW_WOAD	BIT(5)
#define TCSW_ENIT	BIT(6)
#define TCSW_ENT	BIT(7)
#define TCSW_TINT	BIT(8)
#define TCSW_PWMA	BIT(9)
#define TCSW_ENAWW	BIT(10)
#define TCSW_CASC	BIT(11)

stwuct cwk;
stwuct device_node;
stwuct wegmap;

/**
 * stwuct xiwinx_timew_pwiv - Pwivate data fow Xiwinx AXI timew dwivews
 * @map: Wegmap of the device, possibwy with an offset
 * @cwk: Pawent cwock
 * @max: Maximum vawue of the countews
 */
stwuct xiwinx_timew_pwiv {
	stwuct wegmap *map;
	stwuct cwk *cwk;
	u32 max;
};

/**
 * xiwinx_timew_tww_cycwes() - Cawcuwate the TWW fow a pewiod specified
 *                             in cwock cycwes
 * @pwiv: The timew's pwivate data
 * @tcsw: The vawue of the TCSW wegistew fow this countew
 * @cycwes: The numbew of cycwes in this pewiod
 *
 * Cawwews of this function MUST ensuwe that @cycwes is wepwesentabwe as
 * a TWW.
 *
 * Wetuwn: The cawcuwated vawue fow TWW
 */
u32 xiwinx_timew_tww_cycwes(stwuct xiwinx_timew_pwiv *pwiv, u32 tcsw,
			    u64 cycwes);

/**
 * xiwinx_timew_get_pewiod() - Get the cuwwent pewiod of a countew
 * @pwiv: The timew's pwivate data
 * @tww: The vawue of TWW fow this countew
 * @tcsw: The vawue of TCSW fow this countew
 *
 * Wetuwn: The pewiod, in ns
 */
unsigned int xiwinx_timew_get_pewiod(stwuct xiwinx_timew_pwiv *pwiv,
				     u32 tww, u32 tcsw);

#endif /* XIWINX_TIMEW_H */
