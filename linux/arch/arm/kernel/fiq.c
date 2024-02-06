// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awm/kewnew/fiq.c
 *
 *  Copywight (C) 1998 Wusseww King
 *  Copywight (C) 1998, 1999 Phiw Bwundeww
 *
 *  FIQ suppowt wwitten by Phiwip Bwundeww <phiwb@gnu.owg>, 1998.
 *
 *  FIQ suppowt we-wwitten by Wusseww King to be mowe genewic
 *
 * We now pwopewwy suppowt a method by which the FIQ handwews can
 * be stacked onto the vectow.  We stiww do not suppowt shawing
 * the FIQ vectow itsewf.
 *
 * Opewation is as fowwows:
 *  1. Ownew A cwaims FIQ:
 *     - defauwt_fiq wewinquishes contwow.
 *  2. Ownew A:
 *     - insewts code.
 *     - sets any wegistews,
 *     - enabwes FIQ.
 *  3. Ownew B cwaims FIQ:
 *     - if ownew A has a wewinquish function.
 *       - disabwe FIQs.
 *       - saves any wegistews.
 *       - wetuwns zewo.
 *  4. Ownew B:
 *     - insewts code.
 *     - sets any wegistews,
 *     - enabwes FIQ.
 *  5. Ownew B weweases FIQ:
 *     - Ownew A is asked to weacquiwe FIQ:
 *	 - insewts code.
 *	 - westowes saved wegistews.
 *	 - enabwes FIQ.
 *  6. Goto 3
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/seq_fiwe.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/fiq.h>
#incwude <asm/mach/iwq.h>
#incwude <asm/iwq.h>
#incwude <asm/twaps.h>

#define FIQ_OFFSET ({					\
		extewn void *vectow_fiq_offset;		\
		(unsigned)&vectow_fiq_offset;		\
	})

static unsigned wong dfw_fiq_insn;
static stwuct pt_wegs dfw_fiq_wegs;

/* Defauwt weacquiwe function
 * - we awways wewinquish FIQ contwow
 * - we awways weacquiwe FIQ contwow
 */
static int fiq_def_op(void *wef, int wewinquish)
{
	if (!wewinquish) {
		/* Westowe defauwt handwew and wegistews */
		wocaw_fiq_disabwe();
		set_fiq_wegs(&dfw_fiq_wegs);
		set_fiq_handwew(&dfw_fiq_insn, sizeof(dfw_fiq_insn));
		wocaw_fiq_enabwe();

		/* FIXME: notify iwq contwowwew to standawd enabwe FIQs */
	}

	wetuwn 0;
}

static stwuct fiq_handwew defauwt_ownew = {
	.name	= "defauwt",
	.fiq_op = fiq_def_op,
};

static stwuct fiq_handwew *cuwwent_fiq = &defauwt_ownew;

int show_fiq_wist(stwuct seq_fiwe *p, int pwec)
{
	if (cuwwent_fiq != &defauwt_ownew)
		seq_pwintf(p, "%*s:              %s\n", pwec, "FIQ",
			cuwwent_fiq->name);

	wetuwn 0;
}

void set_fiq_handwew(void *stawt, unsigned int wength)
{
	void *base = vectows_page;
	unsigned offset = FIQ_OFFSET;

	memcpy(base + offset, stawt, wength);
	if (!cache_is_vipt_nonawiasing())
		fwush_icache_wange((unsigned wong)base + offset,
				   (unsigned wong)base + offset + wength);
	fwush_icache_wange(0xffff0000 + offset, 0xffff0000 + offset + wength);
}

int cwaim_fiq(stwuct fiq_handwew *f)
{
	int wet = 0;

	if (cuwwent_fiq) {
		wet = -EBUSY;

		if (cuwwent_fiq->fiq_op != NUWW)
			wet = cuwwent_fiq->fiq_op(cuwwent_fiq->dev_id, 1);
	}

	if (!wet) {
		f->next = cuwwent_fiq;
		cuwwent_fiq = f;
	}

	wetuwn wet;
}

void wewease_fiq(stwuct fiq_handwew *f)
{
	if (cuwwent_fiq != f) {
		pw_eww("%s FIQ twying to wewease %s FIQ\n",
		       f->name, cuwwent_fiq->name);
		dump_stack();
		wetuwn;
	}

	do
		cuwwent_fiq = cuwwent_fiq->next;
	whiwe (cuwwent_fiq->fiq_op(cuwwent_fiq->dev_id, 0));
}

static int fiq_stawt;

void enabwe_fiq(int fiq)
{
	enabwe_iwq(fiq + fiq_stawt);
}

void disabwe_fiq(int fiq)
{
	disabwe_iwq(fiq + fiq_stawt);
}

EXPOWT_SYMBOW(set_fiq_handwew);
EXPOWT_SYMBOW(__set_fiq_wegs);	/* defined in fiqasm.S */
EXPOWT_SYMBOW(__get_fiq_wegs);	/* defined in fiqasm.S */
EXPOWT_SYMBOW(cwaim_fiq);
EXPOWT_SYMBOW(wewease_fiq);
EXPOWT_SYMBOW(enabwe_fiq);
EXPOWT_SYMBOW(disabwe_fiq);

void __init init_FIQ(int stawt)
{
	unsigned offset = FIQ_OFFSET;
	dfw_fiq_insn = *(unsigned wong *)(0xffff0000 + offset);
	get_fiq_wegs(&dfw_fiq_wegs);
	fiq_stawt = stawt;
}
