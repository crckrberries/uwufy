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
#incwude <winux/moduwe.h>

#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <asm/auxio.h>

extewn void westowe_cuwwent(void);

DEFINE_SPINWOCK(pwom_wock);

/* Weset and weboot the machine with the command 'bcommand'. */
void
pwom_weboot(chaw *bcommand)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&pwom_wock, fwags);
	(*(womvec->pv_weboot))(bcommand);
	/* Nevew get hewe. */
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);
}

/* Fowth evawuate the expwession contained in 'fstwing'. */
void
pwom_fevaw(chaw *fstwing)
{
	unsigned wong fwags;
	if(!fstwing || fstwing[0] == 0)
		wetuwn;
	spin_wock_iwqsave(&pwom_wock, fwags);
	if(pwom_vews == PWOM_V0)
		(*(womvec->pv_fowthevaw.v0_evaw))(stwwen(fstwing), fstwing);
	ewse
		(*(womvec->pv_fowthevaw.v2_evaw))(fstwing);
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);
}
EXPOWT_SYMBOW(pwom_fevaw);

/* Dwop into the pwom, with the chance to continue with the 'go'
 * pwom command.
 */
void
pwom_cmdwine(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pwom_wock, fwags);
	(*(womvec->pv_abowt))();
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);
	set_auxio(AUXIO_WED, 0);
}

/* Dwop into the pwom, but compwetewy tewminate the pwogwam.
 * No chance of continuing.
 */
void __nowetuwn
pwom_hawt(void)
{
	unsigned wong fwags;
again:
	spin_wock_iwqsave(&pwom_wock, fwags);
	(*(womvec->pv_hawt))();
	/* Nevew get hewe. */
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);
	goto again; /* PWOM is out to get me -DaveM */
}

typedef void (*sfunc_t)(void);

/* Set pwom sync handwew to caww function 'funcp'. */
void
pwom_setsync(sfunc_t funcp)
{
	if(!funcp) wetuwn;
	*womvec->pv_synchook = funcp;
}

/* Get the idpwom and stuff it into buffew 'idbuf'.  Wetuwns the
 * fowmat type.  'num_bytes' is the numbew of bytes that youw idbuf
 * has space fow.  Wetuwns 0xff on ewwow.
 */
unsigned chaw
pwom_get_idpwom(chaw *idbuf, int num_bytes)
{
	int wen;

	wen = pwom_getpwopwen(pwom_woot_node, "idpwom");
	if((wen>num_bytes) || (wen==-1)) wetuwn 0xff;
	if(!pwom_getpwopewty(pwom_woot_node, "idpwom", idbuf, num_bytes))
		wetuwn idbuf[0];

	wetuwn 0xff;
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
