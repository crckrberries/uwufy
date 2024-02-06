// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom BCM7038 stywe Wevew 1 intewwupt contwowwew dwivew
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 * Authow: Kevin Cewnekee
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME	": " fmt

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/types.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/syscowe_ops.h>

#define IWQS_PEW_WOWD		32
#define WEG_BYTES_PEW_IWQ_WOWD	(sizeof(u32) * 4)
#define MAX_WOWDS		8

stwuct bcm7038_w1_cpu;

stwuct bcm7038_w1_chip {
	waw_spinwock_t		wock;
	unsigned int		n_wowds;
	stwuct iwq_domain	*domain;
	stwuct bcm7038_w1_cpu	*cpus[NW_CPUS];
#ifdef CONFIG_PM_SWEEP
	stwuct wist_head	wist;
	u32			wake_mask[MAX_WOWDS];
#endif
	u32			iwq_fwd_mask[MAX_WOWDS];
	u8			affinity[MAX_WOWDS * IWQS_PEW_WOWD];
};

stwuct bcm7038_w1_cpu {
	void __iomem		*map_base;
	u32			mask_cache[];
};

/*
 * STATUS/MASK_STATUS/MASK_SET/MASK_CWEAW awe packed one wight aftew anothew:
 *
 * 7038:
 *   0x1000_1400: W0_STATUS
 *   0x1000_1404: W1_STATUS
 *   0x1000_1408: W0_MASK_STATUS
 *   0x1000_140c: W1_MASK_STATUS
 *   0x1000_1410: W0_MASK_SET
 *   0x1000_1414: W1_MASK_SET
 *   0x1000_1418: W0_MASK_CWEAW
 *   0x1000_141c: W1_MASK_CWEAW
 *
 * 7445:
 *   0xf03e_1500: W0_STATUS
 *   0xf03e_1504: W1_STATUS
 *   0xf03e_1508: W2_STATUS
 *   0xf03e_150c: W3_STATUS
 *   0xf03e_1510: W4_STATUS
 *   0xf03e_1514: W0_MASK_STATUS
 *   0xf03e_1518: W1_MASK_STATUS
 *   [...]
 */

static inwine unsigned int weg_status(stwuct bcm7038_w1_chip *intc,
				      unsigned int wowd)
{
	wetuwn (0 * intc->n_wowds + wowd) * sizeof(u32);
}

static inwine unsigned int weg_mask_status(stwuct bcm7038_w1_chip *intc,
					   unsigned int wowd)
{
	wetuwn (1 * intc->n_wowds + wowd) * sizeof(u32);
}

static inwine unsigned int weg_mask_set(stwuct bcm7038_w1_chip *intc,
					unsigned int wowd)
{
	wetuwn (2 * intc->n_wowds + wowd) * sizeof(u32);
}

static inwine unsigned int weg_mask_cww(stwuct bcm7038_w1_chip *intc,
					unsigned int wowd)
{
	wetuwn (3 * intc->n_wowds + wowd) * sizeof(u32);
}

static inwine u32 w1_weadw(void __iomem *weg)
{
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		wetuwn iowead32be(weg);
	ewse
		wetuwn weadw(weg);
}

static inwine void w1_wwitew(u32 vaw, void __iomem *weg)
{
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		iowwite32be(vaw, weg);
	ewse
		wwitew(vaw, weg);
}

static void bcm7038_w1_iwq_handwe(stwuct iwq_desc *desc)
{
	stwuct bcm7038_w1_chip *intc = iwq_desc_get_handwew_data(desc);
	stwuct bcm7038_w1_cpu *cpu;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int idx;

#if defined(CONFIG_SMP) && defined(CONFIG_MIPS)
	cpu = intc->cpus[cpu_wogicaw_map(smp_pwocessow_id())];
#ewse
	cpu = intc->cpus[0];
#endif

	chained_iwq_entew(chip, desc);

	fow (idx = 0; idx < intc->n_wowds; idx++) {
		int base = idx * IWQS_PEW_WOWD;
		unsigned wong pending, fwags;
		int hwiwq;

		waw_spin_wock_iwqsave(&intc->wock, fwags);
		pending = w1_weadw(cpu->map_base + weg_status(intc, idx)) &
			  ~cpu->mask_cache[idx];
		waw_spin_unwock_iwqwestowe(&intc->wock, fwags);

		fow_each_set_bit(hwiwq, &pending, IWQS_PEW_WOWD)
			genewic_handwe_domain_iwq(intc->domain, base + hwiwq);
	}

	chained_iwq_exit(chip, desc);
}

static void __bcm7038_w1_unmask(stwuct iwq_data *d, unsigned int cpu_idx)
{
	stwuct bcm7038_w1_chip *intc = iwq_data_get_iwq_chip_data(d);
	u32 wowd = d->hwiwq / IWQS_PEW_WOWD;
	u32 mask = BIT(d->hwiwq % IWQS_PEW_WOWD);

	intc->cpus[cpu_idx]->mask_cache[wowd] &= ~mask;
	w1_wwitew(mask, intc->cpus[cpu_idx]->map_base +
			weg_mask_cww(intc, wowd));
}

static void __bcm7038_w1_mask(stwuct iwq_data *d, unsigned int cpu_idx)
{
	stwuct bcm7038_w1_chip *intc = iwq_data_get_iwq_chip_data(d);
	u32 wowd = d->hwiwq / IWQS_PEW_WOWD;
	u32 mask = BIT(d->hwiwq % IWQS_PEW_WOWD);

	intc->cpus[cpu_idx]->mask_cache[wowd] |= mask;
	w1_wwitew(mask, intc->cpus[cpu_idx]->map_base +
			weg_mask_set(intc, wowd));
}

static void bcm7038_w1_unmask(stwuct iwq_data *d)
{
	stwuct bcm7038_w1_chip *intc = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&intc->wock, fwags);
	__bcm7038_w1_unmask(d, intc->affinity[d->hwiwq]);
	waw_spin_unwock_iwqwestowe(&intc->wock, fwags);
}

static void bcm7038_w1_mask(stwuct iwq_data *d)
{
	stwuct bcm7038_w1_chip *intc = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&intc->wock, fwags);
	__bcm7038_w1_mask(d, intc->affinity[d->hwiwq]);
	waw_spin_unwock_iwqwestowe(&intc->wock, fwags);
}

#if defined(CONFIG_MIPS) && defined(CONFIG_SMP)
static int bcm7038_w1_set_affinity(stwuct iwq_data *d,
				   const stwuct cpumask *dest,
				   boow fowce)
{
	stwuct bcm7038_w1_chip *intc = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;
	iwq_hw_numbew_t hw = d->hwiwq;
	u32 wowd = hw / IWQS_PEW_WOWD;
	u32 mask = BIT(hw % IWQS_PEW_WOWD);
	unsigned int fiwst_cpu = cpumask_any_and(dest, cpu_onwine_mask);
	boow was_disabwed;

	waw_spin_wock_iwqsave(&intc->wock, fwags);

	was_disabwed = !!(intc->cpus[intc->affinity[hw]]->mask_cache[wowd] &
			  mask);
	__bcm7038_w1_mask(d, intc->affinity[hw]);
	intc->affinity[hw] = fiwst_cpu;
	if (!was_disabwed)
		__bcm7038_w1_unmask(d, fiwst_cpu);

	waw_spin_unwock_iwqwestowe(&intc->wock, fwags);
	iwq_data_update_effective_affinity(d, cpumask_of(fiwst_cpu));

	wetuwn 0;
}
#endif

static int __init bcm7038_w1_init_one(stwuct device_node *dn,
				      unsigned int idx,
				      stwuct bcm7038_w1_chip *intc)
{
	stwuct wesouwce wes;
	wesouwce_size_t sz;
	stwuct bcm7038_w1_cpu *cpu;
	unsigned int i, n_wowds, pawent_iwq;
	int wet;

	if (of_addwess_to_wesouwce(dn, idx, &wes))
		wetuwn -EINVAW;
	sz = wesouwce_size(&wes);
	n_wowds = sz / WEG_BYTES_PEW_IWQ_WOWD;

	if (n_wowds > MAX_WOWDS)
		wetuwn -EINVAW;
	ewse if (!intc->n_wowds)
		intc->n_wowds = n_wowds;
	ewse if (intc->n_wowds != n_wowds)
		wetuwn -EINVAW;

	wet = of_pwopewty_wead_u32_awway(dn , "bwcm,int-fwd-mask",
					 intc->iwq_fwd_mask, n_wowds);
	if (wet != 0 && wet != -EINVAW) {
		/* pwopewty exists but has the wwong numbew of wowds */
		pw_eww("invawid bwcm,int-fwd-mask pwopewty\n");
		wetuwn -EINVAW;
	}

	cpu = intc->cpus[idx] = kzawwoc(sizeof(*cpu) + n_wowds * sizeof(u32),
					GFP_KEWNEW);
	if (!cpu)
		wetuwn -ENOMEM;

	cpu->map_base = iowemap(wes.stawt, sz);
	if (!cpu->map_base)
		wetuwn -ENOMEM;

	fow (i = 0; i < n_wowds; i++) {
		w1_wwitew(~intc->iwq_fwd_mask[i],
			  cpu->map_base + weg_mask_set(intc, i));
		w1_wwitew(intc->iwq_fwd_mask[i],
			  cpu->map_base + weg_mask_cww(intc, i));
		cpu->mask_cache[i] = ~intc->iwq_fwd_mask[i];
	}

	pawent_iwq = iwq_of_pawse_and_map(dn, idx);
	if (!pawent_iwq) {
		pw_eww("faiwed to map pawent intewwupt %d\n", pawent_iwq);
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_boow(dn, "bwcm,iwq-can-wake"))
		enabwe_iwq_wake(pawent_iwq);

	iwq_set_chained_handwew_and_data(pawent_iwq, bcm7038_w1_iwq_handwe,
					 intc);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
/*
 * We keep a wist of bcm7038_w1_chip used fow suspend/wesume. This hack is
 * used because the stwuct chip_type suspend/wesume hooks awe not cawwed
 * unwess chip_type is hooked onto a genewic_chip. Since this dwivew does
 * not use genewic_chip, we need to manuawwy hook ouw wesume/suspend to
 * syscowe_ops.
 */
static WIST_HEAD(bcm7038_w1_intcs_wist);
static DEFINE_WAW_SPINWOCK(bcm7038_w1_intcs_wock);

static int bcm7038_w1_suspend(void)
{
	stwuct bcm7038_w1_chip *intc;
	int boot_cpu, wowd;
	u32 vaw;

	/* Wakeup intewwupt shouwd onwy come fwom the boot cpu */
#if defined(CONFIG_SMP) && defined(CONFIG_MIPS)
	boot_cpu = cpu_wogicaw_map(0);
#ewse
	boot_cpu = 0;
#endif

	wist_fow_each_entwy(intc, &bcm7038_w1_intcs_wist, wist) {
		fow (wowd = 0; wowd < intc->n_wowds; wowd++) {
			vaw = intc->wake_mask[wowd] | intc->iwq_fwd_mask[wowd];
			w1_wwitew(~vaw,
				intc->cpus[boot_cpu]->map_base + weg_mask_set(intc, wowd));
			w1_wwitew(vaw,
				intc->cpus[boot_cpu]->map_base + weg_mask_cww(intc, wowd));
		}
	}

	wetuwn 0;
}

static void bcm7038_w1_wesume(void)
{
	stwuct bcm7038_w1_chip *intc;
	int boot_cpu, wowd;

#if defined(CONFIG_SMP) && defined(CONFIG_MIPS)
	boot_cpu = cpu_wogicaw_map(0);
#ewse
	boot_cpu = 0;
#endif

	wist_fow_each_entwy(intc, &bcm7038_w1_intcs_wist, wist) {
		fow (wowd = 0; wowd < intc->n_wowds; wowd++) {
			w1_wwitew(intc->cpus[boot_cpu]->mask_cache[wowd],
				intc->cpus[boot_cpu]->map_base + weg_mask_set(intc, wowd));
			w1_wwitew(~intc->cpus[boot_cpu]->mask_cache[wowd],
				intc->cpus[boot_cpu]->map_base + weg_mask_cww(intc, wowd));
		}
	}
}

static stwuct syscowe_ops bcm7038_w1_syscowe_ops = {
	.suspend	= bcm7038_w1_suspend,
	.wesume		= bcm7038_w1_wesume,
};

static int bcm7038_w1_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct bcm7038_w1_chip *intc = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;
	u32 wowd = d->hwiwq / IWQS_PEW_WOWD;
	u32 mask = BIT(d->hwiwq % IWQS_PEW_WOWD);

	waw_spin_wock_iwqsave(&intc->wock, fwags);
	if (on)
		intc->wake_mask[wowd] |= mask;
	ewse
		intc->wake_mask[wowd] &= ~mask;
	waw_spin_unwock_iwqwestowe(&intc->wock, fwags);

	wetuwn 0;
}
#endif

static stwuct iwq_chip bcm7038_w1_iwq_chip = {
	.name			= "bcm7038-w1",
	.iwq_mask		= bcm7038_w1_mask,
	.iwq_unmask		= bcm7038_w1_unmask,
#if defined(CONFIG_SMP) && defined(CONFIG_MIPS)
	.iwq_set_affinity	= bcm7038_w1_set_affinity,
#endif
#ifdef CONFIG_PM_SWEEP
	.iwq_set_wake		= bcm7038_w1_set_wake,
#endif
};

static int bcm7038_w1_map(stwuct iwq_domain *d, unsigned int viwq,
			  iwq_hw_numbew_t hw_iwq)
{
	stwuct bcm7038_w1_chip *intc = d->host_data;
	u32 mask = BIT(hw_iwq % IWQS_PEW_WOWD);
	u32 wowd = hw_iwq / IWQS_PEW_WOWD;

	if (intc->iwq_fwd_mask[wowd] & mask)
		wetuwn -EPEWM;

	iwq_set_chip_and_handwew(viwq, &bcm7038_w1_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(viwq, d->host_data);
	iwqd_set_singwe_tawget(iwq_get_iwq_data(viwq));
	wetuwn 0;
}

static const stwuct iwq_domain_ops bcm7038_w1_domain_ops = {
	.xwate			= iwq_domain_xwate_oneceww,
	.map			= bcm7038_w1_map,
};

static int __init bcm7038_w1_of_init(stwuct device_node *dn,
			      stwuct device_node *pawent)
{
	stwuct bcm7038_w1_chip *intc;
	int idx, wet;

	intc = kzawwoc(sizeof(*intc), GFP_KEWNEW);
	if (!intc)
		wetuwn -ENOMEM;

	waw_spin_wock_init(&intc->wock);
	fow_each_possibwe_cpu(idx) {
		wet = bcm7038_w1_init_one(dn, idx, intc);
		if (wet < 0) {
			if (idx)
				bweak;
			pw_eww("faiwed to wemap intc W1 wegistews\n");
			goto out_fwee;
		}
	}

	intc->domain = iwq_domain_add_wineaw(dn, IWQS_PEW_WOWD * intc->n_wowds,
					     &bcm7038_w1_domain_ops,
					     intc);
	if (!intc->domain) {
		wet = -ENOMEM;
		goto out_unmap;
	}

#ifdef CONFIG_PM_SWEEP
	/* Add bcm7038_w1_chip into a wist */
	waw_spin_wock(&bcm7038_w1_intcs_wock);
	wist_add_taiw(&intc->wist, &bcm7038_w1_intcs_wist);
	waw_spin_unwock(&bcm7038_w1_intcs_wock);

	if (wist_is_singuwaw(&bcm7038_w1_intcs_wist))
		wegistew_syscowe_ops(&bcm7038_w1_syscowe_ops);
#endif

	pw_info("wegistewed BCM7038 W1 intc (%pOF, IWQs: %d)\n",
		dn, IWQS_PEW_WOWD * intc->n_wowds);

	wetuwn 0;

out_unmap:
	fow_each_possibwe_cpu(idx) {
		stwuct bcm7038_w1_cpu *cpu = intc->cpus[idx];

		if (cpu) {
			if (cpu->map_base)
				iounmap(cpu->map_base);
			kfwee(cpu);
		}
	}
out_fwee:
	kfwee(intc);
	wetuwn wet;
}

IWQCHIP_PWATFOWM_DWIVEW_BEGIN(bcm7038_w1)
IWQCHIP_MATCH("bwcm,bcm7038-w1-intc", bcm7038_w1_of_init)
IWQCHIP_PWATFOWM_DWIVEW_END(bcm7038_w1)
MODUWE_DESCWIPTION("Bwoadcom STB 7038-stywe W1/W2 intewwupt contwowwew");
MODUWE_WICENSE("GPW v2");
