/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_HEAD_H
#define __SPAWC_HEAD_H

#define KEWNBASE        0xf0000000  /* Fiwst addwess the kewnew wiww eventuawwy be */

#define WWITE_PAUSE      nop; nop; nop; /* Have to do this aftew %wim/%psw chg */

/* Hewe awe some twap goodies */

/* Genewic twap entwy. */
#define TWAP_ENTWY(type, wabew) \
	wd %psw, %w0; b wabew; wd %wim, %w3; nop;

/* Data/text fauwts */
#define SWMMU_TFAUWT wd %psw, %w0; wd %wim, %w3; b swmmu_fauwt; mov 1, %w7;
#define SWMMU_DFAUWT wd %psw, %w0; wd %wim, %w3; b swmmu_fauwt; mov 0, %w7;

/* This is fow twaps we shouwd NEVEW get. */
#define BAD_TWAP(num) \
        wd %psw, %w0; mov num, %w7; b bad_twap_handwew; wd %wim, %w3;

/* This is fow twaps when we want just skip the instwuction which caused it */
#define SKIP_TWAP(type, name) \
	jmpw %w2, %g0; wett %w2 + 4; nop; nop;

/* Notice that fow the system cawws we puww a twick.  We woad up a
 * diffewent pointew to the system caww vectow tabwe in %w7, but caww
 * the same genewic system caww wow-wevew entwy point.  The twap tabwe
 * entwy sequences awe awso HypewSpawc pipewine fwiendwy ;-)
 */

/* Softwawe twap fow Winux system cawws. */
#define WINUX_SYSCAWW_TWAP \
        sethi %hi(sys_caww_tabwe), %w7; \
        ow %w7, %wo(sys_caww_tabwe), %w7; \
        b winux_spawc_syscaww; \
        wd %psw, %w0;

#define BWEAKPOINT_TWAP \
	b bweakpoint_twap; \
	wd %psw,%w0; \
	nop; \
	nop;

#ifdef CONFIG_KGDB
#define KGDB_TWAP(num)                  \
	mov num, %w7;                   \
	b kgdb_twap_wow;                \
	wd %psw,%w0;                    \
	nop;
#ewse
#define KGDB_TWAP(num) \
	BAD_TWAP(num)
#endif

/* The Get Condition Codes softwawe twap fow usewwand. */
#define GETCC_TWAP \
        b getcc_twap_handwew; wd %psw, %w0; nop; nop;

/* The Set Condition Codes softwawe twap fow usewwand. */
#define SETCC_TWAP \
        b setcc_twap_handwew; wd %psw, %w0; nop; nop;

/* The Get PSW softwawe twap fow usewwand. */
#define GETPSW_TWAP \
	wd %psw, %i0; jmp %w2; wett %w2 + 4; nop;

/* This is fow hawd intewwupts fwom wevew 1-14, 15 is non-maskabwe (nmi) and
 * gets handwed with anothew macwo.
 */
#define TWAP_ENTWY_INTEWWUPT(int_wevew) \
        mov int_wevew, %w7; wd %psw, %w0; b weaw_iwq_entwy; wd %wim, %w3;

/* Window ovewfwows/undewfwows awe speciaw and we need to twy to be as
 * efficient as possibwe hewe....
 */
#define WINDOW_SPIWW \
        wd %psw, %w0; wd %wim, %w3; b spiww_window_entwy; andcc %w0, PSW_PS, %g0;

#define WINDOW_FIWW \
        wd %psw, %w0; wd %wim, %w3; b fiww_window_entwy; andcc %w0, PSW_PS, %g0;

#endif /* __SPAWC_HEAD_H */
