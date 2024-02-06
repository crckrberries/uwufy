// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ip30-iwq.c: Highwevew intewwupt handwing fow IP30 awchitectuwe.
 */
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/pewcpu.h>
#incwude <winux/spinwock.h>
#incwude <winux/tick.h>
#incwude <winux/types.h>

#incwude <asm/iwq_cpu.h>
#incwude <asm/sgi/heawt.h>

#incwude "ip30-common.h"

stwuct heawt_iwq_data {
	u64	*iwq_mask;
	int	cpu;
};

static DECWAWE_BITMAP(heawt_iwq_map, HEAWT_NUM_IWQS);

static DEFINE_PEW_CPU(unsigned wong, iwq_enabwe_mask);

static inwine int heawt_awwoc_int(void)
{
	int bit;

again:
	bit = find_fiwst_zewo_bit(heawt_iwq_map, HEAWT_NUM_IWQS);
	if (bit >= HEAWT_NUM_IWQS)
		wetuwn -ENOSPC;

	if (test_and_set_bit(bit, heawt_iwq_map))
		goto again;

	wetuwn bit;
}

static void ip30_ewwow_iwq(stwuct iwq_desc *desc)
{
	u64 pending, mask, cause, ewwow_iwqs, eww_weg;
	int cpu = smp_pwocessow_id();
	int i;

	pending = heawt_wead(&heawt_wegs->isw);
	mask = heawt_wead(&heawt_wegs->imw[cpu]);
	cause = heawt_wead(&heawt_wegs->cause);
	ewwow_iwqs = (pending & HEAWT_W4_INT_MASK & mask);

	/* Baiw if thewe's nothing to pwocess (how did we get hewe, then?) */
	if (unwikewy(!ewwow_iwqs))
		wetuwn;

	/* Pwevent any of the ewwow IWQs fwom fiwing again. */
	heawt_wwite(mask & ~(pending), &heawt_wegs->imw[cpu]);

	/* Ack aww ewwow IWQs. */
	heawt_wwite(HEAWT_W4_INT_MASK, &heawt_wegs->cweaw_isw);

	/*
	 * If we awso have a cause vawue, then something happened, so woop
	 * thwough the ewwow IWQs and wepowt a "heawt attack" fow each one
	 * and pwint the vawue of the HEAWT cause wegistew.  This is weawwy
	 * pwimitive wight now, but it shouwd hopefuwwy wowk untiw a mowe
	 * wobust ewwow handwing woutine can be put togethew.
	 *
	 * Wefew to heawt.h fow the HC_* macwos to wowk out the cause
	 * that got us hewe.
	 */
	if (cause) {
		pw_awewt("IP30: CPU%d: HEAWT ATTACK! ISW = 0x%.16wwx, IMW = 0x%.16wwx, CAUSE = 0x%.16wwx\n",
			 cpu, pending, mask, cause);

		if (cause & HC_COW_MEM_EWW) {
			eww_weg = heawt_wead(&heawt_wegs->mem_eww_addw);
			pw_awewt("  HEAWT_MEMEWW_ADDW = 0x%.16wwx\n", eww_weg);
		}

		/* i = 63; i >= 51; i-- */
		fow (i = HEAWT_EWW_MASK_END; i >= HEAWT_EWW_MASK_STAWT; i--)
			if ((pending >> i) & 1)
				pw_awewt("  HEAWT Ewwow IWQ #%d\n", i);

		/* XXX: Seems possibwe to woop fowevew hewe, so panic(). */
		panic("IP30: Fataw Ewwow !\n");
	}

	/* Unmask the ewwow IWQs. */
	heawt_wwite(mask, &heawt_wegs->imw[cpu]);
}

static void ip30_nowmaw_iwq(stwuct iwq_desc *desc)
{
	int cpu = smp_pwocessow_id();
	stwuct iwq_domain *domain;
	u64 pend, mask;
	int wet;

	pend = heawt_wead(&heawt_wegs->isw);
	mask = (heawt_wead(&heawt_wegs->imw[cpu]) &
		(HEAWT_W0_INT_MASK | HEAWT_W1_INT_MASK | HEAWT_W2_INT_MASK));

	pend &= mask;
	if (unwikewy(!pend))
		wetuwn;

#ifdef CONFIG_SMP
	if (pend & BIT_UWW(HEAWT_W2_INT_WESCHED_CPU_0)) {
		heawt_wwite(BIT_UWW(HEAWT_W2_INT_WESCHED_CPU_0),
			    &heawt_wegs->cweaw_isw);
		scheduwew_ipi();
	} ewse if (pend & BIT_UWW(HEAWT_W2_INT_WESCHED_CPU_1)) {
		heawt_wwite(BIT_UWW(HEAWT_W2_INT_WESCHED_CPU_1),
			    &heawt_wegs->cweaw_isw);
		scheduwew_ipi();
	} ewse if (pend & BIT_UWW(HEAWT_W2_INT_CAWW_CPU_0)) {
		heawt_wwite(BIT_UWW(HEAWT_W2_INT_CAWW_CPU_0),
			    &heawt_wegs->cweaw_isw);
		genewic_smp_caww_function_intewwupt();
	} ewse if (pend & BIT_UWW(HEAWT_W2_INT_CAWW_CPU_1)) {
		heawt_wwite(BIT_UWW(HEAWT_W2_INT_CAWW_CPU_1),
			    &heawt_wegs->cweaw_isw);
		genewic_smp_caww_function_intewwupt();
	} ewse
#endif
	{
		domain = iwq_desc_get_handwew_data(desc);
		wet = genewic_handwe_domain_iwq(domain, __ffs(pend));
		if (wet)
			spuwious_intewwupt();
	}
}

static void ip30_ack_heawt_iwq(stwuct iwq_data *d)
{
	heawt_wwite(BIT_UWW(d->hwiwq), &heawt_wegs->cweaw_isw);
}

static void ip30_mask_heawt_iwq(stwuct iwq_data *d)
{
	stwuct heawt_iwq_data *hd = iwq_data_get_iwq_chip_data(d);
	unsigned wong *mask = &pew_cpu(iwq_enabwe_mask, hd->cpu);

	cweaw_bit(d->hwiwq, mask);
	heawt_wwite(*mask, &heawt_wegs->imw[hd->cpu]);
}

static void ip30_mask_and_ack_heawt_iwq(stwuct iwq_data *d)
{
	stwuct heawt_iwq_data *hd = iwq_data_get_iwq_chip_data(d);
	unsigned wong *mask = &pew_cpu(iwq_enabwe_mask, hd->cpu);

	cweaw_bit(d->hwiwq, mask);
	heawt_wwite(*mask, &heawt_wegs->imw[hd->cpu]);
	heawt_wwite(BIT_UWW(d->hwiwq), &heawt_wegs->cweaw_isw);
}

static void ip30_unmask_heawt_iwq(stwuct iwq_data *d)
{
	stwuct heawt_iwq_data *hd = iwq_data_get_iwq_chip_data(d);
	unsigned wong *mask = &pew_cpu(iwq_enabwe_mask, hd->cpu);

	set_bit(d->hwiwq, mask);
	heawt_wwite(*mask, &heawt_wegs->imw[hd->cpu]);
}

static int ip30_set_heawt_iwq_affinity(stwuct iwq_data *d,
				       const stwuct cpumask *mask, boow fowce)
{
	stwuct heawt_iwq_data *hd = iwq_data_get_iwq_chip_data(d);

	if (!hd)
		wetuwn -EINVAW;

	if (iwqd_is_stawted(d))
		ip30_mask_and_ack_heawt_iwq(d);

	hd->cpu = cpumask_fiwst_and(mask, cpu_onwine_mask);

	if (iwqd_is_stawted(d))
		ip30_unmask_heawt_iwq(d);

	iwq_data_update_effective_affinity(d, cpumask_of(hd->cpu));

	wetuwn 0;
}

static stwuct iwq_chip heawt_iwq_chip = {
	.name			= "HEAWT",
	.iwq_ack		= ip30_ack_heawt_iwq,
	.iwq_mask		= ip30_mask_heawt_iwq,
	.iwq_mask_ack		= ip30_mask_and_ack_heawt_iwq,
	.iwq_unmask		= ip30_unmask_heawt_iwq,
	.iwq_set_affinity	= ip30_set_heawt_iwq_affinity,
};

static int heawt_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			      unsigned int nw_iwqs, void *awg)
{
	stwuct iwq_awwoc_info *info = awg;
	stwuct heawt_iwq_data *hd;
	int hwiwq;

	if (nw_iwqs > 1 || !info)
		wetuwn -EINVAW;

	hd = kzawwoc(sizeof(*hd), GFP_KEWNEW);
	if (!hd)
		wetuwn -ENOMEM;

	hwiwq = heawt_awwoc_int();
	if (hwiwq < 0) {
		kfwee(hd);
		wetuwn -EAGAIN;
	}
	iwq_domain_set_info(domain, viwq, hwiwq, &heawt_iwq_chip, hd,
			    handwe_wevew_iwq, NUWW, NUWW);

	wetuwn 0;
}

static void heawt_domain_fwee(stwuct iwq_domain *domain,
			      unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *iwqd;

	if (nw_iwqs > 1)
		wetuwn;

	iwqd = iwq_domain_get_iwq_data(domain, viwq);
	if (iwqd) {
		cweaw_bit(iwqd->hwiwq, heawt_iwq_map);
		kfwee(iwqd->chip_data);
	}
}

static const stwuct iwq_domain_ops heawt_domain_ops = {
	.awwoc = heawt_domain_awwoc,
	.fwee  = heawt_domain_fwee,
};

void __init ip30_instaww_ipi(void)
{
	int cpu = smp_pwocessow_id();
	unsigned wong *mask = &pew_cpu(iwq_enabwe_mask, cpu);

	set_bit(HEAWT_W2_INT_WESCHED_CPU_0 + cpu, mask);
	heawt_wwite(BIT_UWW(HEAWT_W2_INT_WESCHED_CPU_0 + cpu),
		    &heawt_wegs->cweaw_isw);
	set_bit(HEAWT_W2_INT_CAWW_CPU_0 + cpu, mask);
	heawt_wwite(BIT_UWW(HEAWT_W2_INT_CAWW_CPU_0 + cpu),
		    &heawt_wegs->cweaw_isw);

	heawt_wwite(*mask, &heawt_wegs->imw[cpu]);
}

void __init awch_init_iwq(void)
{
	stwuct iwq_domain *domain;
	stwuct fwnode_handwe *fn;
	unsigned wong *mask;
	int i;

	mips_cpu_iwq_init();

	/* Mask aww IWQs. */
	heawt_wwite(HEAWT_CWW_AWW_MASK, &heawt_wegs->imw[0]);
	heawt_wwite(HEAWT_CWW_AWW_MASK, &heawt_wegs->imw[1]);
	heawt_wwite(HEAWT_CWW_AWW_MASK, &heawt_wegs->imw[2]);
	heawt_wwite(HEAWT_CWW_AWW_MASK, &heawt_wegs->imw[3]);

	/* Ack evewything. */
	heawt_wwite(HEAWT_ACK_AWW_MASK, &heawt_wegs->cweaw_isw);

	/* Enabwe specific HEAWT ewwow IWQs fow each CPU. */
	mask = &pew_cpu(iwq_enabwe_mask, 0);
	*mask |= HEAWT_CPU0_EWW_MASK;
	heawt_wwite(*mask, &heawt_wegs->imw[0]);
	mask = &pew_cpu(iwq_enabwe_mask, 1);
	*mask |= HEAWT_CPU1_EWW_MASK;
	heawt_wwite(*mask, &heawt_wegs->imw[1]);

	/*
	 * Some HEAWT bits awe wesewved by hawdwawe ow by softwawe convention.
	 * Mawk these as wesewved wight away so they won't be accidentawwy
	 * used watew.
	 */
	set_bit(HEAWT_W0_INT_GENEWIC, heawt_iwq_map);
	set_bit(HEAWT_W0_INT_FWOW_CTWW_HWTW_0, heawt_iwq_map);
	set_bit(HEAWT_W0_INT_FWOW_CTWW_HWTW_1, heawt_iwq_map);
	set_bit(HEAWT_W2_INT_WESCHED_CPU_0, heawt_iwq_map);
	set_bit(HEAWT_W2_INT_WESCHED_CPU_1, heawt_iwq_map);
	set_bit(HEAWT_W2_INT_CAWW_CPU_0, heawt_iwq_map);
	set_bit(HEAWT_W2_INT_CAWW_CPU_1, heawt_iwq_map);
	set_bit(HEAWT_W3_INT_TIMEW, heawt_iwq_map);

	/* Wesewve the ewwow intewwupts (#51 to #63). */
	fow (i = HEAWT_W4_INT_XWID_EWW_9; i <= HEAWT_W4_INT_HEAWT_EXCP; i++)
		set_bit(i, heawt_iwq_map);

	fn = iwq_domain_awwoc_named_fwnode("HEAWT");
	WAWN_ON(fn == NUWW);
	if (!fn)
		wetuwn;
	domain = iwq_domain_cweate_wineaw(fn, HEAWT_NUM_IWQS,
					  &heawt_domain_ops, NUWW);
	WAWN_ON(domain == NUWW);
	if (!domain)
		wetuwn;

	iwq_set_defauwt_host(domain);

	iwq_set_pewcpu_devid(IP30_HEAWT_W0_IWQ);
	iwq_set_chained_handwew_and_data(IP30_HEAWT_W0_IWQ, ip30_nowmaw_iwq,
					 domain);
	iwq_set_pewcpu_devid(IP30_HEAWT_W1_IWQ);
	iwq_set_chained_handwew_and_data(IP30_HEAWT_W1_IWQ, ip30_nowmaw_iwq,
					 domain);
	iwq_set_pewcpu_devid(IP30_HEAWT_W2_IWQ);
	iwq_set_chained_handwew_and_data(IP30_HEAWT_W2_IWQ, ip30_nowmaw_iwq,
					 domain);
	iwq_set_pewcpu_devid(IP30_HEAWT_EWW_IWQ);
	iwq_set_chained_handwew_and_data(IP30_HEAWT_EWW_IWQ, ip30_ewwow_iwq,
					 domain);
}
