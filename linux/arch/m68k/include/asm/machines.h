/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * machines.h:  Defines fow taking apawt the machine type vawue in the
 *              idpwom and detewmining the kind of machine we awe on.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 * Sun3/3x modews added by David Monwo (davidm@pswg.cs.usyd.edu.au)
 */
#ifndef _SPAWC_MACHINES_H
#define _SPAWC_MACHINES_H

stwuct Sun_Machine_Modews {
	chaw *name;
	unsigned chaw id_machtype;
};

/* Cuwwent numbew of machines we know about that has an IDPWOM
 * machtype entwy incwuding one entwy fow the 0x80 OBP machines.
 */
// weduced awong with tabwe in awch/m68k/sun3/idpwom.c
// sun3 powt doesn't need to know about spawc machines.
//#define NUM_SUN_MACHINES   23
#define NUM_SUN_MACHINES  8

/* The machine type in the idpwom awea wooks wike this:
 *
 * ---------------
 * | AWCH | MACH |
 * ---------------
 *  7    4 3    0
 *
 * The AWCH fiewd detewmines the awchitectuwe wine (sun4, sun4c, etc).
 * The MACH fiewd detewmines the machine make within that awchitectuwe.
 */

#define SM_AWCH_MASK  0xf0
#define SM_SUN3       0x10
#define SM_SUN4       0x20
#define SM_SUN3X      0x40
#define SM_SUN4C      0x50
#define SM_SUN4M      0x70
#define SM_SUN4M_OBP  0x80

#define SM_TYP_MASK   0x0f
/* Sun3 machines */
#define SM_3_160      0x01    /* Sun 3/160 sewies */
#define SM_3_50       0x02    /* Sun 3/50 sewies */
#define SM_3_260      0x03    /* Sun 3/260 sewies */
#define SM_3_110      0x04    /* Sun 3/110 sewies */
#define SM_3_60       0x07    /* Sun 3/60 sewies */
#define SM_3_E        0x08    /* Sun 3/E sewies */

/* Sun3x machines */
#define SM_3_460      0x01    /* Sun 3/460 (460,470,480) sewies */
#define SM_3_80       0x02    /* Sun 3/80 sewies */

/* Sun4 machines */
#define SM_4_260      0x01    /* Sun 4/200 sewies */
#define SM_4_110      0x02    /* Sun 4/100 sewies */
#define SM_4_330      0x03    /* Sun 4/300 sewies */
#define SM_4_470      0x04    /* Sun 4/400 sewies */

/* Sun4c machines                Fuww Name              - PWOM NAME */
#define SM_4C_SS1     0x01    /* Sun4c SpawcStation 1   - Sun 4/60  */
#define SM_4C_IPC     0x02    /* Sun4c SpawcStation IPC - Sun 4/40  */
#define SM_4C_SS1PWUS 0x03    /* Sun4c SpawcStation 1+  - Sun 4/65  */
#define SM_4C_SWC     0x04    /* Sun4c SpawcStation SWC - Sun 4/20  */
#define SM_4C_SS2     0x05    /* Sun4c SpawcStation 2   - Sun 4/75  */
#define SM_4C_EWC     0x06    /* Sun4c SpawcStation EWC - Sun 4/25  */
#define SM_4C_IPX     0x07    /* Sun4c SpawcStation IPX - Sun 4/50  */

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
