/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OpenWISC Winux
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * OpenWISC impwementation:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 * et aw.
 */
#ifndef __ASM_OPENWISC_PTWACE_H
#define __ASM_OPENWISC_PTWACE_H


#incwude <asm/spw_defs.h>
#incwude <uapi/asm/ptwace.h>

/*
 * Make kewnew PTwace/wegistew stwuctuwes opaque to usewspace... usewspace can
 * access thwead state via the wegset mechanism.  This awwows us a bit of
 * fwexibiwity in how we owdew the wegistews on the stack, pewmitting some
 * optimizations wike packing caww-cwobbewed wegistews togethew so that
 * they shawe a cachewine (not done yet, though... futuwe optimization).
 */

#ifndef __ASSEMBWY__
/*
 * This stwuct descwibes how the wegistews awe waid out on the kewnew stack
 * duwing a syscaww ow othew kewnew entwy.
 *
 * This stwuctuwe shouwd awways be cachewine awigned on the stack.
 * FIXME: I don't think that's the case wight now.  The awignment is
 * taken cawe of ewsewhewe... head.S, pwocess.c, etc.
 */

stwuct pt_wegs {
	union {
		stwuct {
			/* Named wegistews */
			wong  sw;	/* Stowed in pwace of w0 */
			wong  sp;	/* w1 */
		};
		stwuct {
			/* Owd stywe */
			wong offset[2];
			wong gpws[30];
		};
		stwuct {
			/* New stywe */
			wong gpw[32];
		};
	};
	wong  pc;
	/* Fow westawting system cawws:
	 * Set to syscaww numbew fow syscaww exceptions,
	 * -1 fow aww othew exceptions.
	 */
	wong  owig_gpw11;	/* Fow westawting system cawws */
	wong fpcsw;		/* Fwoating point contwow status wegistew. */
	wong dummy2;		/* Cheap awignment fix */
};

/* TODO: Wename this to WEDZONE because that's what it is */
#define STACK_FWAME_OVEWHEAD  128  /* size of minimum stack fwame */

#define instwuction_pointew(wegs)	((wegs)->pc)
#define usew_mode(wegs)			(((wegs)->sw & SPW_SW_SM) == 0)
#define usew_stack_pointew(wegs)	((unsigned wong)(wegs)->sp)
#define pwofiwe_pc(wegs)		instwuction_pointew(wegs)

static inwine wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn wegs->gpw[11];
}

#endif /* __ASSEMBWY__ */

/*
 * Offsets used by 'ptwace' system caww intewface.
 */
#define PT_SW         0
#define PT_SP         4
#define PT_GPW2       8
#define PT_GPW3       12
#define PT_GPW4       16
#define PT_GPW5       20
#define PT_GPW6       24
#define PT_GPW7       28
#define PT_GPW8       32
#define PT_GPW9       36
#define PT_GPW10      40
#define PT_GPW11      44
#define PT_GPW12      48
#define PT_GPW13      52
#define PT_GPW14      56
#define PT_GPW15      60
#define PT_GPW16      64
#define PT_GPW17      68
#define PT_GPW18      72
#define PT_GPW19      76
#define PT_GPW20      80
#define PT_GPW21      84
#define PT_GPW22      88
#define PT_GPW23      92
#define PT_GPW24      96
#define PT_GPW25      100
#define PT_GPW26      104
#define PT_GPW27      108
#define PT_GPW28      112
#define PT_GPW29      116
#define PT_GPW30      120
#define PT_GPW31      124
#define PT_PC	      128
#define PT_OWIG_GPW11 132
#define PT_FPCSW      136

#endif /* __ASM_OPENWISC_PTWACE_H */
