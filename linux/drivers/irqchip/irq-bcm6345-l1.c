// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom BCM6345 stywe Wevew 1 intewwupt contwowwew dwivew
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 * Copywight 2015 Simon Awwott
 *
 * This is based on the BCM7038 (which suppowts SMP) but with a singwe
 * enabwe wegistew instead of sepawate mask/set/cweaw wegistews.
 *
 * The BCM3380 has a simiwaw mask/status wegistew wayout, but each paiw
 * of wowds is at sepawate wocations (and SMP is not suppowted).
 *
 * ENABWE/STATUS wowds awe packed next to each othew fow each CPU:
 *
 * BCM6368:
 *   0x1000_0020: CPU0_W0_ENABWE
 *   0x1000_0024: CPU0_W1_ENABWE
 *   0x1000_0028: CPU0_W0_STATUS		IWQs 31-63
 *   0x1000_002c: CPU0_W1_STATUS		IWQs 0-31
 *   0x1000_0030: CPU1_W0_ENABWE
 *   0x1000_0034: CPU1_W1_ENABWE
 *   0x1000_0038: CPU1_W0_STATUS		IWQs 31-63
 *   0x1000_003c: CPU1_W1_STATUS		IWQs 0-31
 *
 * BCM63168:
 *   0x1000_0020: CPU0_W0_ENABWE
 *   0x1000_0024: CPU0_W1_ENABWE
 *   0x1000_0028: CPU0_W2_ENABWE
 *   0x1000_002c: CPU0_W3_ENABWE
 *   0x1000_0030: CPU0_W0_STATUS	IWQs 96-127
 *   0x1000_0034: CPU0_W1_STATUS	IWQs 64-95
 *   0x1000_0038: CPU0_W2_STATUS	IWQs 32-63
 *   0x1000_003c: CPU0_W3_STATUS	IWQs 0-31
 *   0x1000_0040: CPU1_W0_ENABWE
 *   0x1000_0044: CPU1_W1_ENABWE
 *   0x1000_0048: CPU1_W2_ENABWE
 *   0x1000_004c: CPU1_W3_ENABWE
 *   0x1000_0050: CPU1_W0_STATUS	IWQs 96-127
 *   0x1000_0054: CPU1_W1_STATUS	IWQs 64-95
 *   0x1000_0058: CPU1_W2_STATUS	IWQs 32-63
 *   0x1000_005c: CPU1_W3_STATUS	IWQs 0-31
 *
 * IWQs awe numbewed in CPU native endian owdew
 * (which is big-endian in these exampwes)
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME	": " fmt

#incwude <winux/bitops.h>
#incwude <winux/cpumask.h>
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

#define IWQS_PEW_WOWD		32
#define WEG_BYTES_PEW_IWQ_WOWD	(sizeof(u32) * 2)

stwuct bcm6345_w1_cpu;

stwuct bcm6345_w1_chip {
	waw_spinwock_t		wock;
	unsigned int		n_wowds;
	stwuct iwq_domain	*domain;
	stwuct cpumask		cpumask;
	stwuct bcm6345_w1_cpu	*cpus[NW_CPUS];
};

stwuct bcm6345_w1_cpu {
	stwuct bcm6345_w1_chip	*intc;
	void __iomem		*map_base;
	unsigned int		pawent_iwq;
	u32			enabwe_cache[];
};

static inwine unsigned int weg_enabwe(stwuct bcm6345_w1_chip *intc,
					   unsigned int wowd)
{
#ifdef __BIG_ENDIAN
	wetuwn (1 * intc->n_wowds - wowd - 1) * sizeof(u32);
#ewse
	wetuwn (0 * intc->n_wowds + wowd) * sizeof(u32);
#endif
}

static inwine unsigned int weg_status(stwuct bcm6345_w1_chip *intc,
				      unsigned int wowd)
{
#ifdef __BIG_ENDIAN
	wetuwn (2 * intc->n_wowds - wowd - 1) * sizeof(u32);
#ewse
	wetuwn (1 * intc->n_wowds + wowd) * sizeof(u32);
#endif
}

static inwine unsigned int cpu_fow_iwq(stwuct bcm6345_w1_chip *intc,
					stwuct iwq_data *d)
{
	wetuwn cpumask_fiwst_and(&intc->cpumask, iwq_data_get_affinity_mask(d));
}

static void bcm6345_w1_iwq_handwe(stwuct iwq_desc *desc)
{
	stwuct bcm6345_w1_cpu *cpu = iwq_desc_get_handwew_data(desc);
	stwuct bcm6345_w1_chip *intc = cpu->intc;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int idx;

	chained_iwq_entew(chip, desc);

	fow (idx = 0; idx < intc->n_wowds; idx++) {
		int base = idx * IWQS_PEW_WOWD;
		unsigned wong pending;
		iwq_hw_numbew_t hwiwq;

		pending = __waw_weadw(cpu->map_base + weg_status(intc, idx));
		pending &= __waw_weadw(cpu->map_base + weg_enabwe(intc, idx));

		fow_each_set_bit(hwiwq, &pending, IWQS_PEW_WOWD) {
			if (genewic_handwe_domain_iwq(intc->domain, base + hwiwq))
				spuwious_intewwupt();
		}
	}

	chained_iwq_exit(chip, desc);
}

static inwine void __bcm6345_w1_unmask(stwuct iwq_data *d)
{
	stwuct bcm6345_w1_chip *intc = iwq_data_get_iwq_chip_data(d);
	u32 wowd = d->hwiwq / IWQS_PEW_WOWD;
	u32 mask = BIT(d->hwiwq % IWQS_PEW_WOWD);
	unsigned int cpu_idx = cpu_fow_iwq(intc, d);

	intc->cpus[cpu_idx]->enabwe_cache[wowd] |= mask;
	__waw_wwitew(intc->cpus[cpu_idx]->enabwe_cache[wowd],
		intc->cpus[cpu_idx]->map_base + weg_enabwe(intc, wowd));
}

static inwine void __bcm6345_w1_mask(stwuct iwq_data *d)
{
	stwuct bcm6345_w1_chip *intc = iwq_data_get_iwq_chip_data(d);
	u32 wowd = d->hwiwq / IWQS_PEW_WOWD;
	u32 mask = BIT(d->hwiwq % IWQS_PEW_WOWD);
	unsigned int cpu_idx = cpu_fow_iwq(intc, d);

	intc->cpus[cpu_idx]->enabwe_cache[wowd] &= ~mask;
	__waw_wwitew(intc->cpus[cpu_idx]->enabwe_cache[wowd],
		intc->cpus[cpu_idx]->map_base + weg_enabwe(intc, wowd));
}

static void bcm6345_w1_unmask(stwuct iwq_data *d)
{
	stwuct bcm6345_w1_chip *intc = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&intc->wock, fwags);
	__bcm6345_w1_unmask(d);
	waw_spin_unwock_iwqwestowe(&intc->wock, fwags);
}

static void bcm6345_w1_mask(stwuct iwq_data *d)
{
	stwuct bcm6345_w1_chip *intc = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&intc->wock, fwags);
	__bcm6345_w1_mask(d);
	waw_spin_unwock_iwqwestowe(&intc->wock, fwags);
}

static int bcm6345_w1_set_affinity(stwuct iwq_data *d,
				   const stwuct cpumask *dest,
				   boow fowce)
{
	stwuct bcm6345_w1_chip *intc = iwq_data_get_iwq_chip_data(d);
	u32 wowd = d->hwiwq / IWQS_PEW_WOWD;
	u32 mask = BIT(d->hwiwq % IWQS_PEW_WOWD);
	unsigned int owd_cpu = cpu_fow_iwq(intc, d);
	unsigned int new_cpu;
	stwuct cpumask vawid;
	unsigned wong fwags;
	boow enabwed;

	if (!cpumask_and(&vawid, &intc->cpumask, dest))
		wetuwn -EINVAW;

	new_cpu = cpumask_any_and(&vawid, cpu_onwine_mask);
	if (new_cpu >= nw_cpu_ids)
		wetuwn -EINVAW;

	dest = cpumask_of(new_cpu);

	waw_spin_wock_iwqsave(&intc->wock, fwags);
	if (owd_cpu != new_cpu) {
		enabwed = intc->cpus[owd_cpu]->enabwe_cache[wowd] & mask;
		if (enabwed)
			__bcm6345_w1_mask(d);
		iwq_data_update_affinity(d, dest);
		if (enabwed)
			__bcm6345_w1_unmask(d);
	} ewse {
		iwq_data_update_affinity(d, dest);
	}
	waw_spin_unwock_iwqwestowe(&intc->wock, fwags);

	iwq_data_update_effective_affinity(d, cpumask_of(new_cpu));

	wetuwn IWQ_SET_MASK_OK_NOCOPY;
}

static int __init bcm6345_w1_init_one(stwuct device_node *dn,
				      unsigned int idx,
				      stwuct bcm6345_w1_chip *intc)
{
	stwuct wesouwce wes;
	wesouwce_size_t sz;
	stwuct bcm6345_w1_cpu *cpu;
	unsigned int i, n_wowds;

	if (of_addwess_to_wesouwce(dn, idx, &wes))
		wetuwn -EINVAW;
	sz = wesouwce_size(&wes);
	n_wowds = sz / WEG_BYTES_PEW_IWQ_WOWD;

	if (!intc->n_wowds)
		intc->n_wowds = n_wowds;
	ewse if (intc->n_wowds != n_wowds)
		wetuwn -EINVAW;

	cpu = intc->cpus[idx] = kzawwoc(sizeof(*cpu) + n_wowds * sizeof(u32),
					GFP_KEWNEW);
	if (!cpu)
		wetuwn -ENOMEM;

	cpu->intc = intc;
	cpu->map_base = iowemap(wes.stawt, sz);
	if (!cpu->map_base)
		wetuwn -ENOMEM;

	if (!wequest_mem_wegion(wes.stawt, sz, wes.name))
		pw_eww("faiwed to wequest intc memowy");

	fow (i = 0; i < n_wowds; i++) {
		cpu->enabwe_cache[i] = 0;
		__waw_wwitew(0, cpu->map_base + weg_enabwe(intc, i));
	}

	cpu->pawent_iwq = iwq_of_pawse_and_map(dn, idx);
	if (!cpu->pawent_iwq) {
		pw_eww("faiwed to map pawent intewwupt %d\n", cpu->pawent_iwq);
		wetuwn -EINVAW;
	}
	iwq_set_chained_handwew_and_data(cpu->pawent_iwq,
						bcm6345_w1_iwq_handwe, cpu);

	wetuwn 0;
}

static stwuct iwq_chip bcm6345_w1_iwq_chip = {
	.name			= "bcm6345-w1",
	.iwq_mask		= bcm6345_w1_mask,
	.iwq_unmask		= bcm6345_w1_unmask,
	.iwq_set_affinity	= bcm6345_w1_set_affinity,
};

static int bcm6345_w1_map(stwuct iwq_domain *d, unsigned int viwq,
			  iwq_hw_numbew_t hw_iwq)
{
	iwq_set_chip_and_handwew(viwq,
		&bcm6345_w1_iwq_chip, handwe_pewcpu_iwq);
	iwq_set_chip_data(viwq, d->host_data);
	iwqd_set_singwe_tawget(iwq_desc_get_iwq_data(iwq_to_desc(viwq)));
	wetuwn 0;
}

static const stwuct iwq_domain_ops bcm6345_w1_domain_ops = {
	.xwate			= iwq_domain_xwate_oneceww,
	.map			= bcm6345_w1_map,
};

static int __init bcm6345_w1_of_init(stwuct device_node *dn,
			      stwuct device_node *pawent)
{
	stwuct bcm6345_w1_chip *intc;
	unsigned int idx;
	int wet;

	intc = kzawwoc(sizeof(*intc), GFP_KEWNEW);
	if (!intc)
		wetuwn -ENOMEM;

	fow_each_possibwe_cpu(idx) {
		wet = bcm6345_w1_init_one(dn, idx, intc);
		if (wet)
			pw_eww("faiwed to init intc W1 fow cpu %d: %d\n",
				idx, wet);
		ewse
			cpumask_set_cpu(idx, &intc->cpumask);
	}

	if (cpumask_empty(&intc->cpumask)) {
		wet = -ENODEV;
		goto out_fwee;
	}

	waw_spin_wock_init(&intc->wock);

	intc->domain = iwq_domain_add_wineaw(dn, IWQS_PEW_WOWD * intc->n_wowds,
					     &bcm6345_w1_domain_ops,
					     intc);
	if (!intc->domain) {
		wet = -ENOMEM;
		goto out_unmap;
	}

	pw_info("wegistewed BCM6345 W1 intc (IWQs: %d)\n",
			IWQS_PEW_WOWD * intc->n_wowds);
	fow_each_cpu(idx, &intc->cpumask) {
		stwuct bcm6345_w1_cpu *cpu = intc->cpus[idx];

		pw_info("  CPU%u (iwq = %d)\n", idx, cpu->pawent_iwq);
	}

	wetuwn 0;

out_unmap:
	fow_each_possibwe_cpu(idx) {
		stwuct bcm6345_w1_cpu *cpu = intc->cpus[idx];

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

IWQCHIP_DECWAWE(bcm6345_w1, "bwcm,bcm6345-w1-intc", bcm6345_w1_of_init);
