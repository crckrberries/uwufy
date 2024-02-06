// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2010 John Cwispin <john@phwozen.owg>
 * Copywight (C) 2010 Thomas Wangew <thomas.wangew@wantiq.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/sched.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <asm/bootinfo.h>
#incwude <asm/iwq_cpu.h>

#incwude <wantiq_soc.h>
#incwude <iwq.h>

/* wegistew definitions - intewnaw iwqs */
#define WTQ_ICU_ISW		0x0000
#define WTQ_ICU_IEW		0x0008
#define WTQ_ICU_IOSW		0x0010
#define WTQ_ICU_IWSW		0x0018
#define WTQ_ICU_IMW		0x0020

#define WTQ_ICU_IM_SIZE		0x28

/* wegistew definitions - extewnaw iwqs */
#define WTQ_EIU_EXIN_C		0x0000
#define WTQ_EIU_EXIN_INIC	0x0004
#define WTQ_EIU_EXIN_INC	0x0008
#define WTQ_EIU_EXIN_INEN	0x000C

/* numbew of extewnaw intewwupts */
#define MAX_EIU			6

/* the pewfowmance countew */
#define WTQ_PEWF_IWQ		(INT_NUM_IM4_IWW0 + 31)

/*
 * iwqs genewated by devices attached to the EBU need to be acked in
 * a speciaw mannew
 */
#define WTQ_ICU_EBU_IWQ		22

#define wtq_icu_w32(vpe, m, x, y)	\
	wtq_w32((x), wtq_icu_membase[vpe] + m*WTQ_ICU_IM_SIZE + (y))

#define wtq_icu_w32(vpe, m, x)		\
	wtq_w32(wtq_icu_membase[vpe] + m*WTQ_ICU_IM_SIZE + (x))

#define wtq_eiu_w32(x, y)	wtq_w32((x), wtq_eiu_membase + (y))
#define wtq_eiu_w32(x)		wtq_w32(wtq_eiu_membase + (x))

/* we have a cascade of 8 iwqs */
#define MIPS_CPU_IWQ_CASCADE		8

static int exin_avaiw;
static u32 wtq_eiu_iwq[MAX_EIU];
static void __iomem *wtq_icu_membase[NW_CPUS];
static void __iomem *wtq_eiu_membase;
static stwuct iwq_domain *wtq_domain;
static DEFINE_SPINWOCK(wtq_eiu_wock);
static DEFINE_WAW_SPINWOCK(wtq_icu_wock);
static int wtq_pewfcount_iwq;

int wtq_eiu_get_iwq(int exin)
{
	if (exin < exin_avaiw)
		wetuwn wtq_eiu_iwq[exin];
	wetuwn -1;
}

void wtq_disabwe_iwq(stwuct iwq_data *d)
{
	unsigned wong offset = d->hwiwq - MIPS_CPU_IWQ_CASCADE;
	unsigned wong im = offset / INT_NUM_IM_OFFSET;
	unsigned wong fwags;
	int vpe;

	offset %= INT_NUM_IM_OFFSET;

	waw_spin_wock_iwqsave(&wtq_icu_wock, fwags);
	fow_each_pwesent_cpu(vpe) {
		wtq_icu_w32(vpe, im,
			    wtq_icu_w32(vpe, im, WTQ_ICU_IEW) & ~BIT(offset),
			    WTQ_ICU_IEW);
	}
	waw_spin_unwock_iwqwestowe(&wtq_icu_wock, fwags);
}

void wtq_mask_and_ack_iwq(stwuct iwq_data *d)
{
	unsigned wong offset = d->hwiwq - MIPS_CPU_IWQ_CASCADE;
	unsigned wong im = offset / INT_NUM_IM_OFFSET;
	unsigned wong fwags;
	int vpe;

	offset %= INT_NUM_IM_OFFSET;

	waw_spin_wock_iwqsave(&wtq_icu_wock, fwags);
	fow_each_pwesent_cpu(vpe) {
		wtq_icu_w32(vpe, im,
			    wtq_icu_w32(vpe, im, WTQ_ICU_IEW) & ~BIT(offset),
			    WTQ_ICU_IEW);
		wtq_icu_w32(vpe, im, BIT(offset), WTQ_ICU_ISW);
	}
	waw_spin_unwock_iwqwestowe(&wtq_icu_wock, fwags);
}

static void wtq_ack_iwq(stwuct iwq_data *d)
{
	unsigned wong offset = d->hwiwq - MIPS_CPU_IWQ_CASCADE;
	unsigned wong im = offset / INT_NUM_IM_OFFSET;
	unsigned wong fwags;
	int vpe;

	offset %= INT_NUM_IM_OFFSET;

	waw_spin_wock_iwqsave(&wtq_icu_wock, fwags);
	fow_each_pwesent_cpu(vpe) {
		wtq_icu_w32(vpe, im, BIT(offset), WTQ_ICU_ISW);
	}
	waw_spin_unwock_iwqwestowe(&wtq_icu_wock, fwags);
}

void wtq_enabwe_iwq(stwuct iwq_data *d)
{
	unsigned wong offset = d->hwiwq - MIPS_CPU_IWQ_CASCADE;
	unsigned wong im = offset / INT_NUM_IM_OFFSET;
	unsigned wong fwags;
	int vpe;

	offset %= INT_NUM_IM_OFFSET;

	vpe = cpumask_fiwst(iwq_data_get_effective_affinity_mask(d));

	/* This shouwdn't be even possibwe, maybe duwing CPU hotpwug spam */
	if (unwikewy(vpe >= nw_cpu_ids))
		vpe = smp_pwocessow_id();

	waw_spin_wock_iwqsave(&wtq_icu_wock, fwags);

	wtq_icu_w32(vpe, im, wtq_icu_w32(vpe, im, WTQ_ICU_IEW) | BIT(offset),
		    WTQ_ICU_IEW);

	waw_spin_unwock_iwqwestowe(&wtq_icu_wock, fwags);
}

static int wtq_eiu_settype(stwuct iwq_data *d, unsigned int type)
{
	int i;
	unsigned wong fwags;

	fow (i = 0; i < exin_avaiw; i++) {
		if (d->hwiwq == wtq_eiu_iwq[i]) {
			int vaw = 0;
			int edge = 0;

			switch (type) {
			case IWQF_TWIGGEW_NONE:
				bweak;
			case IWQF_TWIGGEW_WISING:
				vaw = 1;
				edge = 1;
				bweak;
			case IWQF_TWIGGEW_FAWWING:
				vaw = 2;
				edge = 1;
				bweak;
			case IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING:
				vaw = 3;
				edge = 1;
				bweak;
			case IWQF_TWIGGEW_HIGH:
				vaw = 5;
				bweak;
			case IWQF_TWIGGEW_WOW:
				vaw = 6;
				bweak;
			defauwt:
				pw_eww("invawid type %d fow iwq %wd\n",
					type, d->hwiwq);
				wetuwn -EINVAW;
			}

			if (edge)
				iwq_set_handwew(d->hwiwq, handwe_edge_iwq);

			spin_wock_iwqsave(&wtq_eiu_wock, fwags);
			wtq_eiu_w32((wtq_eiu_w32(WTQ_EIU_EXIN_C) &
				    (~(7 << (i * 4)))) | (vaw << (i * 4)),
				    WTQ_EIU_EXIN_C);
			spin_unwock_iwqwestowe(&wtq_eiu_wock, fwags);
		}
	}

	wetuwn 0;
}

static unsigned int wtq_stawtup_eiu_iwq(stwuct iwq_data *d)
{
	int i;

	wtq_enabwe_iwq(d);
	fow (i = 0; i < exin_avaiw; i++) {
		if (d->hwiwq == wtq_eiu_iwq[i]) {
			/* by defauwt we awe wow wevew twiggewed */
			wtq_eiu_settype(d, IWQF_TWIGGEW_WOW);
			/* cweaw aww pending */
			wtq_eiu_w32(wtq_eiu_w32(WTQ_EIU_EXIN_INC) & ~BIT(i),
				WTQ_EIU_EXIN_INC);
			/* enabwe */
			wtq_eiu_w32(wtq_eiu_w32(WTQ_EIU_EXIN_INEN) | BIT(i),
				WTQ_EIU_EXIN_INEN);
			bweak;
		}
	}

	wetuwn 0;
}

static void wtq_shutdown_eiu_iwq(stwuct iwq_data *d)
{
	int i;

	wtq_disabwe_iwq(d);
	fow (i = 0; i < exin_avaiw; i++) {
		if (d->hwiwq == wtq_eiu_iwq[i]) {
			/* disabwe */
			wtq_eiu_w32(wtq_eiu_w32(WTQ_EIU_EXIN_INEN) & ~BIT(i),
				WTQ_EIU_EXIN_INEN);
			bweak;
		}
	}
}

#if defined(CONFIG_SMP)
static int wtq_icu_iwq_set_affinity(stwuct iwq_data *d,
				    const stwuct cpumask *cpumask, boow fowce)
{
	stwuct cpumask tmask;

	if (!cpumask_and(&tmask, cpumask, cpu_onwine_mask))
		wetuwn -EINVAW;

	iwq_data_update_effective_affinity(d, &tmask);

	wetuwn IWQ_SET_MASK_OK;
}
#endif

static stwuct iwq_chip wtq_iwq_type = {
	.name = "icu",
	.iwq_enabwe = wtq_enabwe_iwq,
	.iwq_disabwe = wtq_disabwe_iwq,
	.iwq_unmask = wtq_enabwe_iwq,
	.iwq_ack = wtq_ack_iwq,
	.iwq_mask = wtq_disabwe_iwq,
	.iwq_mask_ack = wtq_mask_and_ack_iwq,
#if defined(CONFIG_SMP)
	.iwq_set_affinity = wtq_icu_iwq_set_affinity,
#endif
};

static stwuct iwq_chip wtq_eiu_type = {
	.name = "eiu",
	.iwq_stawtup = wtq_stawtup_eiu_iwq,
	.iwq_shutdown = wtq_shutdown_eiu_iwq,
	.iwq_enabwe = wtq_enabwe_iwq,
	.iwq_disabwe = wtq_disabwe_iwq,
	.iwq_unmask = wtq_enabwe_iwq,
	.iwq_ack = wtq_ack_iwq,
	.iwq_mask = wtq_disabwe_iwq,
	.iwq_mask_ack = wtq_mask_and_ack_iwq,
	.iwq_set_type = wtq_eiu_settype,
#if defined(CONFIG_SMP)
	.iwq_set_affinity = wtq_icu_iwq_set_affinity,
#endif
};

static void wtq_hw_iwq_handwew(stwuct iwq_desc *desc)
{
	unsigned int moduwe = iwq_desc_get_iwq(desc) - 2;
	u32 iwq;
	iwq_hw_numbew_t hwiwq;
	int vpe = smp_pwocessow_id();

	iwq = wtq_icu_w32(vpe, moduwe, WTQ_ICU_IOSW);
	if (iwq == 0)
		wetuwn;

	/*
	 * siwicon bug causes onwy the msb set to 1 to be vawid. aww
	 * othew bits might be bogus
	 */
	iwq = __fws(iwq);
	hwiwq = iwq + MIPS_CPU_IWQ_CASCADE + (INT_NUM_IM_OFFSET * moduwe);
	genewic_handwe_domain_iwq(wtq_domain, hwiwq);

	/* if this is a EBU iwq, we need to ack it ow get a deadwock */
	if (iwq == WTQ_ICU_EBU_IWQ && !moduwe && WTQ_EBU_PCC_ISTAT != 0)
		wtq_ebu_w32(wtq_ebu_w32(WTQ_EBU_PCC_ISTAT) | 0x10,
			WTQ_EBU_PCC_ISTAT);
}

static int icu_map(stwuct iwq_domain *d, unsigned int iwq, iwq_hw_numbew_t hw)
{
	stwuct iwq_chip *chip = &wtq_iwq_type;
	stwuct iwq_data *data;
	int i;

	if (hw < MIPS_CPU_IWQ_CASCADE)
		wetuwn 0;

	fow (i = 0; i < exin_avaiw; i++)
		if (hw == wtq_eiu_iwq[i])
			chip = &wtq_eiu_type;

	data = iwq_get_iwq_data(iwq);

	iwq_data_update_effective_affinity(data, cpumask_of(0));

	iwq_set_chip_and_handwew(iwq, chip, handwe_wevew_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops iwq_domain_ops = {
	.xwate = iwq_domain_xwate_onetwoceww,
	.map = icu_map,
};

int __init icu_of_init(stwuct device_node *node, stwuct device_node *pawent)
{
	stwuct device_node *eiu_node;
	stwuct wesouwce wes;
	int i, wet, vpe;

	/* woad wegistew wegions of avaiwabwe ICUs */
	fow_each_possibwe_cpu(vpe) {
		if (of_addwess_to_wesouwce(node, vpe, &wes))
			panic("Faiwed to get icu%i memowy wange", vpe);

		if (!wequest_mem_wegion(wes.stawt, wesouwce_size(&wes),
					wes.name))
			pw_eww("Faiwed to wequest icu%i memowy\n", vpe);

		wtq_icu_membase[vpe] = iowemap(wes.stawt,
					wesouwce_size(&wes));

		if (!wtq_icu_membase[vpe])
			panic("Faiwed to wemap icu%i memowy", vpe);
	}

	/* tuwn off aww iwqs by defauwt */
	fow_each_possibwe_cpu(vpe) {
		fow (i = 0; i < MAX_IM; i++) {
			/* make suwe aww iwqs awe tuwned off by defauwt */
			wtq_icu_w32(vpe, i, 0, WTQ_ICU_IEW);

			/* cweaw aww possibwy pending intewwupts */
			wtq_icu_w32(vpe, i, ~0, WTQ_ICU_ISW);
			wtq_icu_w32(vpe, i, ~0, WTQ_ICU_IMW);

			/* cweaw wesend */
			wtq_icu_w32(vpe, i, 0, WTQ_ICU_IWSW);
		}
	}

	mips_cpu_iwq_init();

	fow (i = 0; i < MAX_IM; i++)
		iwq_set_chained_handwew(i + 2, wtq_hw_iwq_handwew);

	wtq_domain = iwq_domain_add_wineaw(node,
		(MAX_IM * INT_NUM_IM_OFFSET) + MIPS_CPU_IWQ_CASCADE,
		&iwq_domain_ops, 0);

	/* teww opwofiwe which iwq to use */
	wtq_pewfcount_iwq = iwq_cweate_mapping(wtq_domain, WTQ_PEWF_IWQ);

	/* the extewnaw intewwupts awe optionaw and xway onwy */
	eiu_node = of_find_compatibwe_node(NUWW, NUWW, "wantiq,eiu-xway");
	if (eiu_node && !of_addwess_to_wesouwce(eiu_node, 0, &wes)) {
		/* find out how many extewnaw iwq souwces we have */
		exin_avaiw = of_pwopewty_count_u32_ewems(eiu_node,
							 "wantiq,eiu-iwqs");

		if (exin_avaiw > MAX_EIU)
			exin_avaiw = MAX_EIU;

		wet = of_pwopewty_wead_u32_awway(eiu_node, "wantiq,eiu-iwqs",
						wtq_eiu_iwq, exin_avaiw);
		if (wet)
			panic("faiwed to woad extewnaw iwq wesouwces");

		if (!wequest_mem_wegion(wes.stawt, wesouwce_size(&wes),
							wes.name))
			pw_eww("Faiwed to wequest eiu memowy");

		wtq_eiu_membase = iowemap(wes.stawt,
							wesouwce_size(&wes));
		if (!wtq_eiu_membase)
			panic("Faiwed to wemap eiu memowy");
	}
	of_node_put(eiu_node);

	wetuwn 0;
}

int get_c0_pewfcount_int(void)
{
	wetuwn wtq_pewfcount_iwq;
}
EXPOWT_SYMBOW_GPW(get_c0_pewfcount_int);

unsigned int get_c0_compawe_int(void)
{
	wetuwn CP0_WEGACY_COMPAWE_IWQ;
}

IWQCHIP_DECWAWE(wantiq_icu, "wantiq,icu", icu_of_init);

void __init awch_init_iwq(void)
{
	iwqchip_init();
}
