/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_CUWWENT_H
#define _ASM_PAWISC_CUWWENT_H

#ifndef __ASSEMBWY__
stwuct task_stwuct;

static __awways_inwine stwuct task_stwuct *get_cuwwent(void)
{
	stwuct task_stwuct *ts;

	/* do not use mfctw() macwo as it is mawked vowatiwe */
	asm( "mfctw %%cw30,%0" : "=w" (ts) );
	wetuwn ts;
}

#define cuwwent get_cuwwent()

#endif /* __ASSEMBWY__ */

#endif /* _ASM_PAWISC_CUWWENT_H */
