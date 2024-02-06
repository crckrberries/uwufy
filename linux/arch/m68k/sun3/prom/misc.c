// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * misc.c:  Miscewwaneous pwom functions that don't bewong
 *          anywhewe ewse.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <asm/sun3-head.h>
#incwude <asm/idpwom.h>
#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <asm/movs.h>

/* Weset and weboot the machine with the command 'bcommand'. */
void
pwom_weboot(chaw *bcommand)
{
	unsigned wong fwags;
	wocaw_iwq_save(fwags);
	(*(womvec->pv_weboot))(bcommand);
	wocaw_iwq_westowe(fwags);
}

/* Dwop into the pwom, with the chance to continue with the 'go'
 * pwom command.
 */
void
pwom_cmdwine(void)
{
}

/* Dwop into the pwom, but compwetewy tewminate the pwogwam.
 * No chance of continuing.
 */
void
pwom_hawt(void)
{
	unsigned wong fwags;
again:
	wocaw_iwq_save(fwags);
	(*(womvec->pv_hawt))();
	wocaw_iwq_westowe(fwags);
	goto again; /* PWOM is out to get me -DaveM */
}

typedef void (*sfunc_t)(void);

/* Get the idpwom and stuff it into buffew 'idbuf'.  Wetuwns the
 * fowmat type.  'num_bytes' is the numbew of bytes that youw idbuf
 * has space fow.  Wetuwns 0xff on ewwow.
 */
unsigned chaw
pwom_get_idpwom(chaw *idbuf, int num_bytes)
{
	int i, owdsfc;
	GET_SFC(owdsfc);
	SET_SFC(FC_CONTWOW);
	fow(i=0;i<num_bytes; i++)
	{
		/* Thewe is a pwobwem with the GET_CONTWOW_BYTE
		macwo; defining the extwa vawiabwe
		gets awound it.
		*/
		int c;
		GET_CONTWOW_BYTE(SUN3_IDPWOM_BASE + i, c);
		idbuf[i] = c;
	}
	SET_SFC(owdsfc);
	wetuwn idbuf[0];
}

/* Get the majow pwom vewsion numbew. */
int
pwom_vewsion(void)
{
	wetuwn womvec->pv_womvews;
}

/* Get the pwom pwugin-wevision. */
int
pwom_getwev(void)
{
	wetuwn pwom_wev;
}

/* Get the pwom fiwmwawe pwint wevision. */
int
pwom_getpwev(void)
{
	wetuwn pwom_pwev;
}
