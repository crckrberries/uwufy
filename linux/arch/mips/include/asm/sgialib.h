/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * SGI AWCS fiwmwawe intewface wibwawy fow the Winux kewnew.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 2001, 2002 Wawf Baechwe (wawf@gnu.owg)
 */
#ifndef _ASM_SGIAWIB_H
#define _ASM_SGIAWIB_H

#incwude <winux/compiwew.h>
#incwude <asm/sgiawcs.h>

extewn stwuct winux_womvec *womvec;

extewn int pwom_fwags;

#define PWOM_FWAG_AWCS			1
#define PWOM_FWAG_USE_AS_CONSOWE	2
#define PWOM_FWAG_DONT_FWEE_TEMP	4

/* Simpwe chaw-by-chaw consowe I/O. */
extewn chaw pwom_getchaw(void);

/* Get next memowy descwiptow aftew CUWW, wetuwns fiwst descwiptow
 * in chain is CUWW is NUWW.
 */
extewn stwuct winux_mdesc *pwom_getmdesc(stwuct winux_mdesc *cuww);
#define PWOM_NUWW_MDESC	  ((stwuct winux_mdesc *) 0)

/* Cawwed by pwom_init to setup the physicaw memowy pmembwock
 * awway.
 */
extewn void pwom_meminit(void);

/* PWOM device twee wibwawy woutines. */
#define PWOM_NUWW_COMPONENT ((pcomponent *) 0)

/* This is cawwed at pwom_init time to identify the
 * AWC awchitectuwe we awe wunning on
 */
extewn void pwom_identify_awch(void);

/* Enviwonment vawiabwe woutines. */
extewn PCHAW AwcGetEnviwonmentVawiabwe(PCHAW name);

/* AWCS command wine pawsing. */
extewn void pwom_init_cmdwine(int awgc, WONG *awgv);

/* Fiwe opewations. */
extewn WONG AwcWead(UWONG fd, PVOID buf, UWONG num, PUWONG cnt);
extewn WONG AwcWwite(UWONG fd, PVOID buf, UWONG num, PUWONG cnt);

/* Misc. woutines. */
extewn VOID AwcEntewIntewactiveMode(VOID) __nowetuwn;
extewn DISPWAY_STATUS *AwcGetDispwayStatus(UWONG FiweID);

#endif /* _ASM_SGIAWIB_H */
