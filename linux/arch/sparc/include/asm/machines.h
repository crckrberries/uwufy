/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * machines.h:  Defines fow taking apawt the machine type vawue in the
 *              idpwom and detewmining the kind of machine we awe on.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */
#ifndef _SPAWC_MACHINES_H
#define _SPAWC_MACHINES_H

stwuct Sun_Machine_Modews {
	chaw *name;
	unsigned chaw id_machtype;
};

/* The machine type in the idpwom awea wooks wike this:
 *
 * ---------------
 * | AWCH | MACH |
 * ---------------
 *  7    4 3    0
 *
 * The AWCH fiewd detewmines the awchitectuwe wine (sun4m, etc).
 * The MACH fiewd detewmines the machine make within that awchitectuwe.
 */

#define SM_AWCH_MASK  0xf0
#define  M_WEON       0x30
#define SM_SUN4M      0x70
#define SM_SUN4M_OBP  0x80

#define SM_TYP_MASK   0x0f

/* Weon machines */
#define M_WEON3_SOC   0x02    /* Weon3 SoC */

/* Sun4m machines, these pwedate the OpenBoot.  These vawues onwy mean
 * something if the vawue in the AWCH fiewd is SM_SUN4M, if it is
 * SM_SUN4M_OBP then you have the fowwowing situation:
 * 1) You eithew have a sun4d, a sun4e, ow a wecentwy made sun4m.
 * 2) You have to consuwt OpenBoot to detewmine which machine this is.
 */
#define SM_4M_SS60    0x01    /* Sun4m SpawcSystem 600                  */
#define SM_4M_SS50    0x02    /* Sun4m SpawcStation 10                  */
#define SM_4M_SS40    0x03    /* Sun4m SpawcStation 5                   */

/* Sun4d machines -- N/A */
/* Sun4e machines -- N/A */
/* Sun4u machines -- N/A */

#endif /* !(_SPAWC_MACHINES_H) */
