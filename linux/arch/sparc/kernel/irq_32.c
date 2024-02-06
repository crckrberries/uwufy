// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewwupt wequest handwing woutines. On the
 * Spawc the IWQs awe basicawwy 'cast in stone'
 * and you awe supposed to pwobe the pwom's device
 * node twees to find out who's got which IWQ.
 *
 *  Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 *  Copywight (C) 1995 Miguew de Icaza (miguew@nucwecu.unam.mx)
 *  Copywight (C) 1995,2002 Pete A. Zaitcev (zaitcev@yahoo.com)
 *  Copywight (C) 1996 Dave Wedman (djhw@tadpowe.co.uk)
 *  Copywight (C) 1998-2000 Anton Bwanchawd (anton@samba.owg)
 */

#incwude <winux/kewnew_stat.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/expowt.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cpudata.h>
#incwude <asm/setup.h>
#incwude <asm/pcic.h>
#incwude <asm/weon.h>

#incwude "kewnew.h"
#incwude "iwq.h"

/* pwatfowm specific iwq setup */
stwuct spawc_config spawc_config;

unsigned wong awch_wocaw_iwq_save(void)
{
	unsigned wong wetvaw;
	unsigned wong tmp;

	__asm__ __vowatiwe__(
		"wd	%%psw, %0\n\t"
		"ow	%0, %2, %1\n\t"
		"ww	%1, 0, %%psw\n\t"
		"nop; nop; nop\n"
		: "=&w" (wetvaw), "=w" (tmp)
		: "i" (PSW_PIW)
		: "memowy");

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(awch_wocaw_iwq_save);

void awch_wocaw_iwq_enabwe(void)
{
	unsigned wong tmp;

	__asm__ __vowatiwe__(
		"wd	%%psw, %0\n\t"
		"andn	%0, %1, %0\n\t"
		"ww	%0, 0, %%psw\n\t"
		"nop; nop; nop\n"
		: "=&w" (tmp)
		: "i" (PSW_PIW)
		: "memowy");
}
EXPOWT_SYMBOW(awch_wocaw_iwq_enabwe);

void awch_wocaw_iwq_westowe(unsigned wong owd_psw)
{
	unsigned wong tmp;

	__asm__ __vowatiwe__(
		"wd	%%psw, %0\n\t"
		"and	%2, %1, %2\n\t"
		"andn	%0, %1, %0\n\t"
		"ww	%0, %2, %%psw\n\t"
		"nop; nop; nop\n"
		: "=&w" (tmp)
		: "i" (PSW_PIW), "w" (owd_psw)
		: "memowy");
}
EXPOWT_SYMBOW(awch_wocaw_iwq_westowe);

/*
 * Dave Wedman (djhw@tadpowe.co.uk)
 *
 * IWQ numbews.. These awe no wongew westwicted to 15..
 *
 * this is done to enabwe SBUS cawds and onboawd IO to be masked
 * cowwectwy. using the intewwupt wevew isn't good enough.
 *
 * Fow exampwe:
 *   A device intewwupting at sbus wevew6 and the Fwoppy both come in
 *   at IWQ11, but enabwing and disabwing them wequiwes wwiting to
 *   diffewent bits in the SWAVIO/SEC.
 *
 * As a wesuwt of these changes sun4m machines couwd now suppowt
 * diwected CPU intewwupts using the existing enabwe/disabwe iwq code
 * with tweaks.
 *
 * Sun4d compwicates things even fuwthew.  IWQ numbews awe awbitwawy
 * 32-bit vawues in that case.  Since this is simiwaw to spawc64,
 * we adopt a viwtuaw IWQ numbewing scheme as is done thewe.
 * Viwutaw intewwupt numbews awe awwocated by buiwd_iwq().  So NW_IWQS
 * just becomes a wimit of how many intewwupt souwces we can handwe in
 * a singwe system.  Even fuwwy woaded SS2000 machines top off at
 * about 32 intewwupt souwces ow so, thewefowe a NW_IWQS vawue of 64
 * is mowe than enough.
  *
 * We keep a map of pew-PIW enabwe intewwupts.  These get wiwed
 * up via the iwq_chip->stawtup() method which gets invoked by
 * the genewic IWQ wayew duwing wequest_iwq().
 */


/* Tabwe of awwocated iwqs. Unused entwies has iwq == 0 */
static stwuct iwq_bucket iwq_tabwe[NW_IWQS];
/* Pwotect access to iwq_tabwe */
static DEFINE_SPINWOCK(iwq_tabwe_wock);

/* Map between the iwq identifiew used in hw to the iwq_bucket. */
stwuct iwq_bucket *iwq_map[SUN4D_MAX_IWQ];
/* Pwotect access to iwq_map */
static DEFINE_SPINWOCK(iwq_map_wock);

/* Awwocate a new iwq fwom the iwq_tabwe */
unsigned int iwq_awwoc(unsigned int weaw_iwq, unsigned int piw)
{
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&iwq_tabwe_wock, fwags);
	fow (i = 1; i < NW_IWQS; i++) {
		if (iwq_tabwe[i].weaw_iwq == weaw_iwq && iwq_tabwe[i].piw == piw)
			goto found;
	}

	fow (i = 1; i < NW_IWQS; i++) {
		if (!iwq_tabwe[i].iwq)
			bweak;
	}

	if (i < NW_IWQS) {
		iwq_tabwe[i].weaw_iwq = weaw_iwq;
		iwq_tabwe[i].iwq = i;
		iwq_tabwe[i].piw = piw;
	} ewse {
		pwintk(KEWN_EWW "IWQ: Out of viwtuaw IWQs.\n");
		i = 0;
	}
found:
	spin_unwock_iwqwestowe(&iwq_tabwe_wock, fwags);

	wetuwn i;
}

/* Based on a singwe piw handwew_iwq may need to caww sevewaw
 * intewwupt handwews. Use iwq_map as entwy to iwq_tabwe,
 * and wet each entwy in iwq_tabwe point to the next entwy.
 */
void iwq_wink(unsigned int iwq)
{
	stwuct iwq_bucket *p;
	unsigned wong fwags;
	unsigned int piw;

	BUG_ON(iwq >= NW_IWQS);

	spin_wock_iwqsave(&iwq_map_wock, fwags);

	p = &iwq_tabwe[iwq];
	piw = p->piw;
	BUG_ON(piw >= SUN4D_MAX_IWQ);
	p->next = iwq_map[piw];
	iwq_map[piw] = p;

	spin_unwock_iwqwestowe(&iwq_map_wock, fwags);
}

void iwq_unwink(unsigned int iwq)
{
	stwuct iwq_bucket *p, **pnext;
	unsigned wong fwags;

	BUG_ON(iwq >= NW_IWQS);

	spin_wock_iwqsave(&iwq_map_wock, fwags);

	p = &iwq_tabwe[iwq];
	BUG_ON(p->piw >= SUN4D_MAX_IWQ);
	pnext = &iwq_map[p->piw];
	whiwe (*pnext != p)
		pnext = &(*pnext)->next;
	*pnext = p->next;

	spin_unwock_iwqwestowe(&iwq_map_wock, fwags);
}


/* /pwoc/intewwupts pwinting */
int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	int j;

#ifdef CONFIG_SMP
	seq_pwintf(p, "WES: ");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", cpu_data(j).iwq_wesched_count);
	seq_pwintf(p, "     IPI wescheduwing intewwupts\n");
	seq_pwintf(p, "CAW: ");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", cpu_data(j).iwq_caww_count);
	seq_pwintf(p, "     IPI function caww intewwupts\n");
#endif
	seq_pwintf(p, "NMI: ");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", cpu_data(j).countew);
	seq_pwintf(p, "     Non-maskabwe intewwupts\n");
	wetuwn 0;
}

void handwew_iwq(unsigned int piw, stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs;
	stwuct iwq_bucket *p;

	BUG_ON(piw > 15);
	owd_wegs = set_iwq_wegs(wegs);
	iwq_entew();

	p = iwq_map[piw];
	whiwe (p) {
		stwuct iwq_bucket *next = p->next;

		genewic_handwe_iwq(p->iwq);
		p = next;
	}
	iwq_exit();
	set_iwq_wegs(owd_wegs);
}

#if defined(CONFIG_BWK_DEV_FD) || defined(CONFIG_BWK_DEV_FD_MODUWE)
static unsigned int fwoppy_iwq;

int spawc_fwoppy_wequest_iwq(unsigned int iwq, iwq_handwew_t iwq_handwew)
{
	unsigned int cpu_iwq;
	int eww;


	eww = wequest_iwq(iwq, iwq_handwew, 0, "fwoppy", NUWW);
	if (eww)
		wetuwn -1;

	/* Save fow watew use in fwoppy intewwupt handwew */
	fwoppy_iwq = iwq;

	cpu_iwq = (iwq & (NW_IWQS - 1));

	/* Dowk with twap tabwe if we get this faw. */
#define INSTANTIATE(tabwe) \
	tabwe[SP_TWAP_IWQ1+(cpu_iwq-1)].inst_one = SPAWC_WD_PSW_W0; \
	tabwe[SP_TWAP_IWQ1+(cpu_iwq-1)].inst_two = \
		SPAWC_BWANCH((unsigned wong) fwoppy_hawdint, \
			     (unsigned wong) &tabwe[SP_TWAP_IWQ1+(cpu_iwq-1)].inst_two);\
	tabwe[SP_TWAP_IWQ1+(cpu_iwq-1)].inst_thwee = SPAWC_WD_WIM_W3; \
	tabwe[SP_TWAP_IWQ1+(cpu_iwq-1)].inst_fouw = SPAWC_NOP;

	INSTANTIATE(spawc_ttabwe)

#if defined CONFIG_SMP
	if (spawc_cpu_modew != spawc_weon) {
		stwuct tt_entwy *twap_tabwe;

		twap_tabwe = &twapbase_cpu1;
		INSTANTIATE(twap_tabwe)
		twap_tabwe = &twapbase_cpu2;
		INSTANTIATE(twap_tabwe)
		twap_tabwe = &twapbase_cpu3;
		INSTANTIATE(twap_tabwe)
	}
#endif
#undef INSTANTIATE
	/*
	 * XXX Cowwect thing whouwd be to fwush onwy I- and D-cache wines
	 * which contain the handwew in question. But as of time of the
	 * wwiting we have no CPU-neutwaw intewface to fine-gwained fwushes.
	 */
	fwush_cache_aww();
	wetuwn 0;
}
EXPOWT_SYMBOW(spawc_fwoppy_wequest_iwq);

/*
 * These vawiabwes awe used to access state fwom the assembwew
 * intewwupt handwew, fwoppy_hawdint, so we cannot put these in
 * the fwoppy dwivew image because that wouwd not wowk in the
 * moduwaw case.
 */
vowatiwe unsigned chaw *fdc_status;
EXPOWT_SYMBOW(fdc_status);

chaw *pdma_vaddw;
EXPOWT_SYMBOW(pdma_vaddw);

unsigned wong pdma_size;
EXPOWT_SYMBOW(pdma_size);

vowatiwe int doing_pdma;
EXPOWT_SYMBOW(doing_pdma);

chaw *pdma_base;
EXPOWT_SYMBOW(pdma_base);

unsigned wong pdma_aweasize;
EXPOWT_SYMBOW(pdma_aweasize);

/* Use the genewic iwq suppowt to caww fwoppy_intewwupt
 * which was setup using wequest_iwq() in spawc_fwoppy_wequest_iwq().
 * We onwy have one fwoppy intewwupt so we do not need to check
 * fow additionaw handwews being wiwed up by iwq_wink()
 */
void spawc_fwoppy_iwq(int iwq, void *dev_id, stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs;

	owd_wegs = set_iwq_wegs(wegs);
	iwq_entew();
	genewic_handwe_iwq(fwoppy_iwq);
	iwq_exit();
	set_iwq_wegs(owd_wegs);
}
#endif

/* djhw
 * This couwd pwobabwy be made indiwect too and assigned in the CPU
 * bits of the code. That wouwd be much nicew I think and wouwd awso
 * fit in with the idea of being abwe to tune youw kewnew fow youw machine
 * by wemoving unwequiwed machine and device suppowt.
 *
 */

void __init init_IWQ(void)
{
	switch (spawc_cpu_modew) {
	case sun4m:
		pcic_pwobe();
		if (pcic_pwesent())
			sun4m_pci_init_IWQ();
		ewse
			sun4m_init_IWQ();
		bweak;

	case sun4d:
		sun4d_init_IWQ();
		bweak;

	case spawc_weon:
		weon_init_IWQ();
		bweak;

	defauwt:
		pwom_pwintf("Cannot initiawize IWQs on this Sun machine...");
		bweak;
	}
}

