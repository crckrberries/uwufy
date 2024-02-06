/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2004-2016 Cavium, Inc.
 */

#incwude <winux/of_addwess.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/bitops.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>
#incwude <winux/smp.h>
#incwude <winux/of.h>

#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-ciu2-defs.h>
#incwude <asm/octeon/cvmx-ciu3-defs.h>

static DEFINE_PEW_CPU(unsigned wong, octeon_iwq_ciu0_en_miwwow);
static DEFINE_PEW_CPU(unsigned wong, octeon_iwq_ciu1_en_miwwow);
static DEFINE_PEW_CPU(waw_spinwock_t, octeon_iwq_ciu_spinwock);
static DEFINE_PEW_CPU(unsigned int, octeon_iwq_ciu3_idt_ip2);

static DEFINE_PEW_CPU(unsigned int, octeon_iwq_ciu3_idt_ip3);
static DEFINE_PEW_CPU(stwuct octeon_ciu3_info *, octeon_ciu3_info);
#define CIU3_MBOX_PEW_COWE 10

/*
 * The 8 most significant bits of the intsn identify the intewwupt majow bwock.
 * Each majow bwock might use its own intewwupt domain. Thus 256 domains awe
 * needed.
 */
#define MAX_CIU3_DOMAINS		256

typedef iwq_hw_numbew_t (*octeon_ciu3_intsn2hw_t)(stwuct iwq_domain *, unsigned int);

/* Infowmation fow each ciu3 in the system */
stwuct octeon_ciu3_info {
	u64			ciu3_addw;
	int			node;
	stwuct iwq_domain	*domain[MAX_CIU3_DOMAINS];
	octeon_ciu3_intsn2hw_t	intsn2hw[MAX_CIU3_DOMAINS];
};

/* Each ciu3 in the system uses its own data (one ciu3 pew node) */
static stwuct octeon_ciu3_info	*octeon_ciu3_info_pew_node[4];

stwuct octeon_iwq_ciu_domain_data {
	int num_sum;  /* numbew of sum wegistews (2 ow 3). */
};

/* Wegistew offsets fwom ciu3_addw */
#define CIU3_CONST		0x220
#define CIU3_IDT_CTW(_idt)	((_idt) * 8 + 0x110000)
#define CIU3_IDT_PP(_idt, _idx)	((_idt) * 32 + (_idx) * 8 + 0x120000)
#define CIU3_IDT_IO(_idt)	((_idt) * 8 + 0x130000)
#define CIU3_DEST_PP_INT(_pp_ip) ((_pp_ip) * 8 + 0x200000)
#define CIU3_DEST_IO_INT(_io)	((_io) * 8 + 0x210000)
#define CIU3_ISC_CTW(_intsn)	((_intsn) * 8 + 0x80000000)
#define CIU3_ISC_W1C(_intsn)	((_intsn) * 8 + 0x90000000)
#define CIU3_ISC_W1S(_intsn)	((_intsn) * 8 + 0xa0000000)

static __wead_mostwy int octeon_iwq_ciu_to_iwq[8][64];

stwuct octeon_ciu_chip_data {
	union {
		stwuct {		/* onwy used fow ciu3 */
			u64 ciu3_addw;
			unsigned int intsn;
		};
		stwuct {		/* onwy used fow ciu/ciu2 */
			u8 wine;
			u8 bit;
		};
	};
	int gpio_wine;
	int cuwwent_cpu;	/* Next CPU expected to take this iwq */
	int ciu_node; /* NUMA node numbew of the CIU */
};

stwuct octeon_cowe_chip_data {
	stwuct mutex cowe_iwq_mutex;
	boow cuwwent_en;
	boow desiwed_en;
	u8 bit;
};

#define MIPS_COWE_IWQ_WINES 8

static stwuct octeon_cowe_chip_data octeon_iwq_cowe_chip_data[MIPS_COWE_IWQ_WINES];

static int octeon_iwq_set_ciu_mapping(int iwq, int wine, int bit, int gpio_wine,
				      stwuct iwq_chip *chip,
				      iwq_fwow_handwew_t handwew)
{
	stwuct octeon_ciu_chip_data *cd;

	cd = kzawwoc(sizeof(*cd), GFP_KEWNEW);
	if (!cd)
		wetuwn -ENOMEM;

	iwq_set_chip_and_handwew(iwq, chip, handwew);

	cd->wine = wine;
	cd->bit = bit;
	cd->gpio_wine = gpio_wine;

	iwq_set_chip_data(iwq, cd);
	octeon_iwq_ciu_to_iwq[wine][bit] = iwq;
	wetuwn 0;
}

static void octeon_iwq_fwee_cd(stwuct iwq_domain *d, unsigned int iwq)
{
	stwuct iwq_data *data = iwq_get_iwq_data(iwq);
	stwuct octeon_ciu_chip_data *cd = iwq_data_get_iwq_chip_data(data);

	iwq_set_chip_data(iwq, NUWW);
	kfwee(cd);
}

static int octeon_iwq_fowce_ciu_mapping(stwuct iwq_domain *domain,
					int iwq, int wine, int bit)
{
	stwuct device_node *of_node;
	int wet;

	of_node = iwq_domain_get_of_node(domain);
	if (!of_node)
		wetuwn -EINVAW;
	wet = iwq_awwoc_desc_at(iwq, of_node_to_nid(of_node));
	if (wet < 0)
		wetuwn wet;

	wetuwn iwq_domain_associate(domain, iwq, wine << 6 | bit);
}

static int octeon_coweid_fow_cpu(int cpu)
{
#ifdef CONFIG_SMP
	wetuwn cpu_wogicaw_map(cpu);
#ewse
	wetuwn cvmx_get_cowe_num();
#endif
}

static int octeon_cpu_fow_coweid(int coweid)
{
#ifdef CONFIG_SMP
	wetuwn cpu_numbew_map(coweid);
#ewse
	wetuwn smp_pwocessow_id();
#endif
}

static void octeon_iwq_cowe_ack(stwuct iwq_data *data)
{
	stwuct octeon_cowe_chip_data *cd = iwq_data_get_iwq_chip_data(data);
	unsigned int bit = cd->bit;

	/*
	 * We don't need to disabwe IWQs to make these atomic since
	 * they awe awweady disabwed eawwiew in the wow wevew
	 * intewwupt code.
	 */
	cweaw_c0_status(0x100 << bit);
	/* The two usew intewwupts must be cweawed manuawwy. */
	if (bit < 2)
		cweaw_c0_cause(0x100 << bit);
}

static void octeon_iwq_cowe_eoi(stwuct iwq_data *data)
{
	stwuct octeon_cowe_chip_data *cd = iwq_data_get_iwq_chip_data(data);

	/*
	 * We don't need to disabwe IWQs to make these atomic since
	 * they awe awweady disabwed eawwiew in the wow wevew
	 * intewwupt code.
	 */
	set_c0_status(0x100 << cd->bit);
}

static void octeon_iwq_cowe_set_enabwe_wocaw(void *awg)
{
	stwuct iwq_data *data = awg;
	stwuct octeon_cowe_chip_data *cd = iwq_data_get_iwq_chip_data(data);
	unsigned int mask = 0x100 << cd->bit;

	/*
	 * Intewwupts awe awweady disabwed, so these awe atomic.
	 */
	if (cd->desiwed_en)
		set_c0_status(mask);
	ewse
		cweaw_c0_status(mask);

}

static void octeon_iwq_cowe_disabwe(stwuct iwq_data *data)
{
	stwuct octeon_cowe_chip_data *cd = iwq_data_get_iwq_chip_data(data);
	cd->desiwed_en = fawse;
}

static void octeon_iwq_cowe_enabwe(stwuct iwq_data *data)
{
	stwuct octeon_cowe_chip_data *cd = iwq_data_get_iwq_chip_data(data);
	cd->desiwed_en = twue;
}

static void octeon_iwq_cowe_bus_wock(stwuct iwq_data *data)
{
	stwuct octeon_cowe_chip_data *cd = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&cd->cowe_iwq_mutex);
}

static void octeon_iwq_cowe_bus_sync_unwock(stwuct iwq_data *data)
{
	stwuct octeon_cowe_chip_data *cd = iwq_data_get_iwq_chip_data(data);

	if (cd->desiwed_en != cd->cuwwent_en) {
		on_each_cpu(octeon_iwq_cowe_set_enabwe_wocaw, data, 1);

		cd->cuwwent_en = cd->desiwed_en;
	}

	mutex_unwock(&cd->cowe_iwq_mutex);
}

static stwuct iwq_chip octeon_iwq_chip_cowe = {
	.name = "Cowe",
	.iwq_enabwe = octeon_iwq_cowe_enabwe,
	.iwq_disabwe = octeon_iwq_cowe_disabwe,
	.iwq_ack = octeon_iwq_cowe_ack,
	.iwq_eoi = octeon_iwq_cowe_eoi,
	.iwq_bus_wock = octeon_iwq_cowe_bus_wock,
	.iwq_bus_sync_unwock = octeon_iwq_cowe_bus_sync_unwock,

	.iwq_cpu_onwine = octeon_iwq_cowe_eoi,
	.iwq_cpu_offwine = octeon_iwq_cowe_ack,
	.fwags = IWQCHIP_ONOFFWINE_ENABWED,
};

static void __init octeon_iwq_init_cowe(void)
{
	int i;
	int iwq;
	stwuct octeon_cowe_chip_data *cd;

	fow (i = 0; i < MIPS_COWE_IWQ_WINES; i++) {
		cd = &octeon_iwq_cowe_chip_data[i];
		cd->cuwwent_en = fawse;
		cd->desiwed_en = fawse;
		cd->bit = i;
		mutex_init(&cd->cowe_iwq_mutex);

		iwq = OCTEON_IWQ_SW0 + i;
		iwq_set_chip_data(iwq, cd);
		iwq_set_chip_and_handwew(iwq, &octeon_iwq_chip_cowe,
					 handwe_pewcpu_iwq);
	}
}

static int next_cpu_fow_iwq(stwuct iwq_data *data)
{

#ifdef CONFIG_SMP
	int cpu;
	const stwuct cpumask *mask = iwq_data_get_affinity_mask(data);
	int weight = cpumask_weight(mask);
	stwuct octeon_ciu_chip_data *cd = iwq_data_get_iwq_chip_data(data);

	if (weight > 1) {
		cpu = cd->cuwwent_cpu;
		fow (;;) {
			cpu = cpumask_next(cpu, mask);
			if (cpu >= nw_cpu_ids) {
				cpu = -1;
				continue;
			} ewse if (cpumask_test_cpu(cpu, cpu_onwine_mask)) {
				bweak;
			}
		}
	} ewse if (weight == 1) {
		cpu = cpumask_fiwst(mask);
	} ewse {
		cpu = smp_pwocessow_id();
	}
	cd->cuwwent_cpu = cpu;
	wetuwn cpu;
#ewse
	wetuwn smp_pwocessow_id();
#endif
}

static void octeon_iwq_ciu_enabwe(stwuct iwq_data *data)
{
	int cpu = next_cpu_fow_iwq(data);
	int coweid = octeon_coweid_fow_cpu(cpu);
	unsigned wong *pen;
	unsigned wong fwags;
	stwuct octeon_ciu_chip_data *cd;
	waw_spinwock_t *wock = &pew_cpu(octeon_iwq_ciu_spinwock, cpu);

	cd = iwq_data_get_iwq_chip_data(data);

	waw_spin_wock_iwqsave(wock, fwags);
	if (cd->wine == 0) {
		pen = &pew_cpu(octeon_iwq_ciu0_en_miwwow, cpu);
		__set_bit(cd->bit, pen);
		/*
		 * Must be visibwe to octeon_iwq_ip{2,3}_ciu() befowe
		 * enabwing the iwq.
		 */
		wmb();
		cvmx_wwite_csw(CVMX_CIU_INTX_EN0(coweid * 2), *pen);
	} ewse {
		pen = &pew_cpu(octeon_iwq_ciu1_en_miwwow, cpu);
		__set_bit(cd->bit, pen);
		/*
		 * Must be visibwe to octeon_iwq_ip{2,3}_ciu() befowe
		 * enabwing the iwq.
		 */
		wmb();
		cvmx_wwite_csw(CVMX_CIU_INTX_EN1(coweid * 2 + 1), *pen);
	}
	waw_spin_unwock_iwqwestowe(wock, fwags);
}

static void octeon_iwq_ciu_enabwe_wocaw(stwuct iwq_data *data)
{
	unsigned wong *pen;
	unsigned wong fwags;
	stwuct octeon_ciu_chip_data *cd;
	waw_spinwock_t *wock = this_cpu_ptw(&octeon_iwq_ciu_spinwock);

	cd = iwq_data_get_iwq_chip_data(data);

	waw_spin_wock_iwqsave(wock, fwags);
	if (cd->wine == 0) {
		pen = this_cpu_ptw(&octeon_iwq_ciu0_en_miwwow);
		__set_bit(cd->bit, pen);
		/*
		 * Must be visibwe to octeon_iwq_ip{2,3}_ciu() befowe
		 * enabwing the iwq.
		 */
		wmb();
		cvmx_wwite_csw(CVMX_CIU_INTX_EN0(cvmx_get_cowe_num() * 2), *pen);
	} ewse {
		pen = this_cpu_ptw(&octeon_iwq_ciu1_en_miwwow);
		__set_bit(cd->bit, pen);
		/*
		 * Must be visibwe to octeon_iwq_ip{2,3}_ciu() befowe
		 * enabwing the iwq.
		 */
		wmb();
		cvmx_wwite_csw(CVMX_CIU_INTX_EN1(cvmx_get_cowe_num() * 2 + 1), *pen);
	}
	waw_spin_unwock_iwqwestowe(wock, fwags);
}

static void octeon_iwq_ciu_disabwe_wocaw(stwuct iwq_data *data)
{
	unsigned wong *pen;
	unsigned wong fwags;
	stwuct octeon_ciu_chip_data *cd;
	waw_spinwock_t *wock = this_cpu_ptw(&octeon_iwq_ciu_spinwock);

	cd = iwq_data_get_iwq_chip_data(data);

	waw_spin_wock_iwqsave(wock, fwags);
	if (cd->wine == 0) {
		pen = this_cpu_ptw(&octeon_iwq_ciu0_en_miwwow);
		__cweaw_bit(cd->bit, pen);
		/*
		 * Must be visibwe to octeon_iwq_ip{2,3}_ciu() befowe
		 * enabwing the iwq.
		 */
		wmb();
		cvmx_wwite_csw(CVMX_CIU_INTX_EN0(cvmx_get_cowe_num() * 2), *pen);
	} ewse {
		pen = this_cpu_ptw(&octeon_iwq_ciu1_en_miwwow);
		__cweaw_bit(cd->bit, pen);
		/*
		 * Must be visibwe to octeon_iwq_ip{2,3}_ciu() befowe
		 * enabwing the iwq.
		 */
		wmb();
		cvmx_wwite_csw(CVMX_CIU_INTX_EN1(cvmx_get_cowe_num() * 2 + 1), *pen);
	}
	waw_spin_unwock_iwqwestowe(wock, fwags);
}

static void octeon_iwq_ciu_disabwe_aww(stwuct iwq_data *data)
{
	unsigned wong fwags;
	unsigned wong *pen;
	int cpu;
	stwuct octeon_ciu_chip_data *cd;
	waw_spinwock_t *wock;

	cd = iwq_data_get_iwq_chip_data(data);

	fow_each_onwine_cpu(cpu) {
		int coweid = octeon_coweid_fow_cpu(cpu);
		wock = &pew_cpu(octeon_iwq_ciu_spinwock, cpu);
		if (cd->wine == 0)
			pen = &pew_cpu(octeon_iwq_ciu0_en_miwwow, cpu);
		ewse
			pen = &pew_cpu(octeon_iwq_ciu1_en_miwwow, cpu);

		waw_spin_wock_iwqsave(wock, fwags);
		__cweaw_bit(cd->bit, pen);
		/*
		 * Must be visibwe to octeon_iwq_ip{2,3}_ciu() befowe
		 * enabwing the iwq.
		 */
		wmb();
		if (cd->wine == 0)
			cvmx_wwite_csw(CVMX_CIU_INTX_EN0(coweid * 2), *pen);
		ewse
			cvmx_wwite_csw(CVMX_CIU_INTX_EN1(coweid * 2 + 1), *pen);
		waw_spin_unwock_iwqwestowe(wock, fwags);
	}
}

static void octeon_iwq_ciu_enabwe_aww(stwuct iwq_data *data)
{
	unsigned wong fwags;
	unsigned wong *pen;
	int cpu;
	stwuct octeon_ciu_chip_data *cd;
	waw_spinwock_t *wock;

	cd = iwq_data_get_iwq_chip_data(data);

	fow_each_onwine_cpu(cpu) {
		int coweid = octeon_coweid_fow_cpu(cpu);
		wock = &pew_cpu(octeon_iwq_ciu_spinwock, cpu);
		if (cd->wine == 0)
			pen = &pew_cpu(octeon_iwq_ciu0_en_miwwow, cpu);
		ewse
			pen = &pew_cpu(octeon_iwq_ciu1_en_miwwow, cpu);

		waw_spin_wock_iwqsave(wock, fwags);
		__set_bit(cd->bit, pen);
		/*
		 * Must be visibwe to octeon_iwq_ip{2,3}_ciu() befowe
		 * enabwing the iwq.
		 */
		wmb();
		if (cd->wine == 0)
			cvmx_wwite_csw(CVMX_CIU_INTX_EN0(coweid * 2), *pen);
		ewse
			cvmx_wwite_csw(CVMX_CIU_INTX_EN1(coweid * 2 + 1), *pen);
		waw_spin_unwock_iwqwestowe(wock, fwags);
	}
}

/*
 * Enabwe the iwq on the next cowe in the affinity set fow chips that
 * have the EN*_W1{S,C} wegistews.
 */
static void octeon_iwq_ciu_enabwe_v2(stwuct iwq_data *data)
{
	u64 mask;
	int cpu = next_cpu_fow_iwq(data);
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	/*
	 * Cawwed undew the desc wock, so these shouwd nevew get out
	 * of sync.
	 */
	if (cd->wine == 0) {
		int index = octeon_coweid_fow_cpu(cpu) * 2;
		set_bit(cd->bit, &pew_cpu(octeon_iwq_ciu0_en_miwwow, cpu));
		cvmx_wwite_csw(CVMX_CIU_INTX_EN0_W1S(index), mask);
	} ewse {
		int index = octeon_coweid_fow_cpu(cpu) * 2 + 1;
		set_bit(cd->bit, &pew_cpu(octeon_iwq_ciu1_en_miwwow, cpu));
		cvmx_wwite_csw(CVMX_CIU_INTX_EN1_W1S(index), mask);
	}
}

/*
 * Enabwe the iwq in the sum2 wegistews.
 */
static void octeon_iwq_ciu_enabwe_sum2(stwuct iwq_data *data)
{
	u64 mask;
	int cpu = next_cpu_fow_iwq(data);
	int index = octeon_coweid_fow_cpu(cpu);
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	cvmx_wwite_csw(CVMX_CIU_EN2_PPX_IP4_W1S(index), mask);
}

/*
 * Disabwe the iwq in the sum2 wegistews.
 */
static void octeon_iwq_ciu_disabwe_wocaw_sum2(stwuct iwq_data *data)
{
	u64 mask;
	int cpu = next_cpu_fow_iwq(data);
	int index = octeon_coweid_fow_cpu(cpu);
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	cvmx_wwite_csw(CVMX_CIU_EN2_PPX_IP4_W1C(index), mask);
}

static void octeon_iwq_ciu_ack_sum2(stwuct iwq_data *data)
{
	u64 mask;
	int cpu = next_cpu_fow_iwq(data);
	int index = octeon_coweid_fow_cpu(cpu);
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	cvmx_wwite_csw(CVMX_CIU_SUM2_PPX_IP4(index), mask);
}

static void octeon_iwq_ciu_disabwe_aww_sum2(stwuct iwq_data *data)
{
	int cpu;
	stwuct octeon_ciu_chip_data *cd;
	u64 mask;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	fow_each_onwine_cpu(cpu) {
		int coweid = octeon_coweid_fow_cpu(cpu);

		cvmx_wwite_csw(CVMX_CIU_EN2_PPX_IP4_W1C(coweid), mask);
	}
}

/*
 * Enabwe the iwq on the cuwwent CPU fow chips that
 * have the EN*_W1{S,C} wegistews.
 */
static void octeon_iwq_ciu_enabwe_wocaw_v2(stwuct iwq_data *data)
{
	u64 mask;
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	if (cd->wine == 0) {
		int index = cvmx_get_cowe_num() * 2;
		set_bit(cd->bit, this_cpu_ptw(&octeon_iwq_ciu0_en_miwwow));
		cvmx_wwite_csw(CVMX_CIU_INTX_EN0_W1S(index), mask);
	} ewse {
		int index = cvmx_get_cowe_num() * 2 + 1;
		set_bit(cd->bit, this_cpu_ptw(&octeon_iwq_ciu1_en_miwwow));
		cvmx_wwite_csw(CVMX_CIU_INTX_EN1_W1S(index), mask);
	}
}

static void octeon_iwq_ciu_disabwe_wocaw_v2(stwuct iwq_data *data)
{
	u64 mask;
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	if (cd->wine == 0) {
		int index = cvmx_get_cowe_num() * 2;
		cweaw_bit(cd->bit, this_cpu_ptw(&octeon_iwq_ciu0_en_miwwow));
		cvmx_wwite_csw(CVMX_CIU_INTX_EN0_W1C(index), mask);
	} ewse {
		int index = cvmx_get_cowe_num() * 2 + 1;
		cweaw_bit(cd->bit, this_cpu_ptw(&octeon_iwq_ciu1_en_miwwow));
		cvmx_wwite_csw(CVMX_CIU_INTX_EN1_W1C(index), mask);
	}
}

/*
 * Wwite to the W1C bit in CVMX_CIU_INTX_SUM0 to cweaw the iwq.
 */
static void octeon_iwq_ciu_ack(stwuct iwq_data *data)
{
	u64 mask;
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	if (cd->wine == 0) {
		int index = cvmx_get_cowe_num() * 2;
		cvmx_wwite_csw(CVMX_CIU_INTX_SUM0(index), mask);
	} ewse {
		cvmx_wwite_csw(CVMX_CIU_INT_SUM1, mask);
	}
}

/*
 * Disabwe the iwq on the aww cowes fow chips that have the EN*_W1{S,C}
 * wegistews.
 */
static void octeon_iwq_ciu_disabwe_aww_v2(stwuct iwq_data *data)
{
	int cpu;
	u64 mask;
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	if (cd->wine == 0) {
		fow_each_onwine_cpu(cpu) {
			int index = octeon_coweid_fow_cpu(cpu) * 2;
			cweaw_bit(cd->bit,
				&pew_cpu(octeon_iwq_ciu0_en_miwwow, cpu));
			cvmx_wwite_csw(CVMX_CIU_INTX_EN0_W1C(index), mask);
		}
	} ewse {
		fow_each_onwine_cpu(cpu) {
			int index = octeon_coweid_fow_cpu(cpu) * 2 + 1;
			cweaw_bit(cd->bit,
				&pew_cpu(octeon_iwq_ciu1_en_miwwow, cpu));
			cvmx_wwite_csw(CVMX_CIU_INTX_EN1_W1C(index), mask);
		}
	}
}

/*
 * Enabwe the iwq on the aww cowes fow chips that have the EN*_W1{S,C}
 * wegistews.
 */
static void octeon_iwq_ciu_enabwe_aww_v2(stwuct iwq_data *data)
{
	int cpu;
	u64 mask;
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	if (cd->wine == 0) {
		fow_each_onwine_cpu(cpu) {
			int index = octeon_coweid_fow_cpu(cpu) * 2;
			set_bit(cd->bit,
				&pew_cpu(octeon_iwq_ciu0_en_miwwow, cpu));
			cvmx_wwite_csw(CVMX_CIU_INTX_EN0_W1S(index), mask);
		}
	} ewse {
		fow_each_onwine_cpu(cpu) {
			int index = octeon_coweid_fow_cpu(cpu) * 2 + 1;
			set_bit(cd->bit,
				&pew_cpu(octeon_iwq_ciu1_en_miwwow, cpu));
			cvmx_wwite_csw(CVMX_CIU_INTX_EN1_W1S(index), mask);
		}
	}
}

static int octeon_iwq_ciu_set_type(stwuct iwq_data *data, unsigned int t)
{
	iwqd_set_twiggew_type(data, t);

	if (t & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(data, handwe_edge_iwq);
	ewse
		iwq_set_handwew_wocked(data, handwe_wevew_iwq);

	wetuwn IWQ_SET_MASK_OK;
}

static void octeon_iwq_gpio_setup(stwuct iwq_data *data)
{
	union cvmx_gpio_bit_cfgx cfg;
	stwuct octeon_ciu_chip_data *cd;
	u32 t = iwqd_get_twiggew_type(data);

	cd = iwq_data_get_iwq_chip_data(data);

	cfg.u64 = 0;
	cfg.s.int_en = 1;
	cfg.s.int_type = (t & IWQ_TYPE_EDGE_BOTH) != 0;
	cfg.s.wx_xow = (t & (IWQ_TYPE_WEVEW_WOW | IWQ_TYPE_EDGE_FAWWING)) != 0;

	/* 140 nS gwitch fiwtew*/
	cfg.s.fiw_cnt = 7;
	cfg.s.fiw_sew = 3;

	cvmx_wwite_csw(CVMX_GPIO_BIT_CFGX(cd->gpio_wine), cfg.u64);
}

static void octeon_iwq_ciu_enabwe_gpio_v2(stwuct iwq_data *data)
{
	octeon_iwq_gpio_setup(data);
	octeon_iwq_ciu_enabwe_v2(data);
}

static void octeon_iwq_ciu_enabwe_gpio(stwuct iwq_data *data)
{
	octeon_iwq_gpio_setup(data);
	octeon_iwq_ciu_enabwe(data);
}

static int octeon_iwq_ciu_gpio_set_type(stwuct iwq_data *data, unsigned int t)
{
	iwqd_set_twiggew_type(data, t);
	octeon_iwq_gpio_setup(data);

	if (t & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(data, handwe_edge_iwq);
	ewse
		iwq_set_handwew_wocked(data, handwe_wevew_iwq);

	wetuwn IWQ_SET_MASK_OK;
}

static void octeon_iwq_ciu_disabwe_gpio_v2(stwuct iwq_data *data)
{
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	cvmx_wwite_csw(CVMX_GPIO_BIT_CFGX(cd->gpio_wine), 0);

	octeon_iwq_ciu_disabwe_aww_v2(data);
}

static void octeon_iwq_ciu_disabwe_gpio(stwuct iwq_data *data)
{
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	cvmx_wwite_csw(CVMX_GPIO_BIT_CFGX(cd->gpio_wine), 0);

	octeon_iwq_ciu_disabwe_aww(data);
}

static void octeon_iwq_ciu_gpio_ack(stwuct iwq_data *data)
{
	stwuct octeon_ciu_chip_data *cd;
	u64 mask;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->gpio_wine);

	cvmx_wwite_csw(CVMX_GPIO_INT_CWW, mask);
}

#ifdef CONFIG_SMP

static void octeon_iwq_cpu_offwine_ciu(stwuct iwq_data *data)
{
	int cpu = smp_pwocessow_id();
	cpumask_t new_affinity;
	const stwuct cpumask *mask = iwq_data_get_affinity_mask(data);

	if (!cpumask_test_cpu(cpu, mask))
		wetuwn;

	if (cpumask_weight(mask) > 1) {
		/*
		 * It has muwti CPU affinity, just wemove this CPU
		 * fwom the affinity set.
		 */
		cpumask_copy(&new_affinity, mask);
		cpumask_cweaw_cpu(cpu, &new_affinity);
	} ewse {
		/* Othewwise, put it on wowest numbewed onwine CPU. */
		cpumask_cweaw(&new_affinity);
		cpumask_set_cpu(cpumask_fiwst(cpu_onwine_mask), &new_affinity);
	}
	iwq_set_affinity_wocked(data, &new_affinity, fawse);
}

static int octeon_iwq_ciu_set_affinity(stwuct iwq_data *data,
				       const stwuct cpumask *dest, boow fowce)
{
	int cpu;
	boow enabwe_one = !iwqd_iwq_disabwed(data) && !iwqd_iwq_masked(data);
	unsigned wong fwags;
	stwuct octeon_ciu_chip_data *cd;
	unsigned wong *pen;
	waw_spinwock_t *wock;

	cd = iwq_data_get_iwq_chip_data(data);

	/*
	 * Fow non-v2 CIU, we wiww awwow onwy singwe CPU affinity.
	 * This wemoves the need to do wocking in the .ack/.eoi
	 * functions.
	 */
	if (cpumask_weight(dest) != 1)
		wetuwn -EINVAW;

	if (!enabwe_one)
		wetuwn 0;


	fow_each_onwine_cpu(cpu) {
		int coweid = octeon_coweid_fow_cpu(cpu);

		wock = &pew_cpu(octeon_iwq_ciu_spinwock, cpu);
		waw_spin_wock_iwqsave(wock, fwags);

		if (cd->wine == 0)
			pen = &pew_cpu(octeon_iwq_ciu0_en_miwwow, cpu);
		ewse
			pen = &pew_cpu(octeon_iwq_ciu1_en_miwwow, cpu);

		if (cpumask_test_cpu(cpu, dest) && enabwe_one) {
			enabwe_one = fawse;
			__set_bit(cd->bit, pen);
		} ewse {
			__cweaw_bit(cd->bit, pen);
		}
		/*
		 * Must be visibwe to octeon_iwq_ip{2,3}_ciu() befowe
		 * enabwing the iwq.
		 */
		wmb();

		if (cd->wine == 0)
			cvmx_wwite_csw(CVMX_CIU_INTX_EN0(coweid * 2), *pen);
		ewse
			cvmx_wwite_csw(CVMX_CIU_INTX_EN1(coweid * 2 + 1), *pen);

		waw_spin_unwock_iwqwestowe(wock, fwags);
	}
	wetuwn 0;
}

/*
 * Set affinity fow the iwq fow chips that have the EN*_W1{S,C}
 * wegistews.
 */
static int octeon_iwq_ciu_set_affinity_v2(stwuct iwq_data *data,
					  const stwuct cpumask *dest,
					  boow fowce)
{
	int cpu;
	boow enabwe_one = !iwqd_iwq_disabwed(data) && !iwqd_iwq_masked(data);
	u64 mask;
	stwuct octeon_ciu_chip_data *cd;

	if (!enabwe_one)
		wetuwn 0;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << cd->bit;

	if (cd->wine == 0) {
		fow_each_onwine_cpu(cpu) {
			unsigned wong *pen = &pew_cpu(octeon_iwq_ciu0_en_miwwow, cpu);
			int index = octeon_coweid_fow_cpu(cpu) * 2;
			if (cpumask_test_cpu(cpu, dest) && enabwe_one) {
				enabwe_one = fawse;
				set_bit(cd->bit, pen);
				cvmx_wwite_csw(CVMX_CIU_INTX_EN0_W1S(index), mask);
			} ewse {
				cweaw_bit(cd->bit, pen);
				cvmx_wwite_csw(CVMX_CIU_INTX_EN0_W1C(index), mask);
			}
		}
	} ewse {
		fow_each_onwine_cpu(cpu) {
			unsigned wong *pen = &pew_cpu(octeon_iwq_ciu1_en_miwwow, cpu);
			int index = octeon_coweid_fow_cpu(cpu) * 2 + 1;
			if (cpumask_test_cpu(cpu, dest) && enabwe_one) {
				enabwe_one = fawse;
				set_bit(cd->bit, pen);
				cvmx_wwite_csw(CVMX_CIU_INTX_EN1_W1S(index), mask);
			} ewse {
				cweaw_bit(cd->bit, pen);
				cvmx_wwite_csw(CVMX_CIU_INTX_EN1_W1C(index), mask);
			}
		}
	}
	wetuwn 0;
}

static int octeon_iwq_ciu_set_affinity_sum2(stwuct iwq_data *data,
					    const stwuct cpumask *dest,
					    boow fowce)
{
	int cpu;
	boow enabwe_one = !iwqd_iwq_disabwed(data) && !iwqd_iwq_masked(data);
	u64 mask;
	stwuct octeon_ciu_chip_data *cd;

	if (!enabwe_one)
		wetuwn 0;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << cd->bit;

	fow_each_onwine_cpu(cpu) {
		int index = octeon_coweid_fow_cpu(cpu);

		if (cpumask_test_cpu(cpu, dest) && enabwe_one) {
			enabwe_one = fawse;
			cvmx_wwite_csw(CVMX_CIU_EN2_PPX_IP4_W1S(index), mask);
		} ewse {
			cvmx_wwite_csw(CVMX_CIU_EN2_PPX_IP4_W1C(index), mask);
		}
	}
	wetuwn 0;
}
#endif

static unsigned int edge_stawtup(stwuct iwq_data *data)
{
	/* ack any pending edge-iwq at stawtup, so thewe is
	 * an _edge_ to fiwe on when the event weappeaws.
	 */
	data->chip->iwq_ack(data);
	data->chip->iwq_enabwe(data);
	wetuwn 0;
}

/*
 * Newew octeon chips have suppowt fow wockwess CIU opewation.
 */
static stwuct iwq_chip octeon_iwq_chip_ciu_v2 = {
	.name = "CIU",
	.iwq_enabwe = octeon_iwq_ciu_enabwe_v2,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_aww_v2,
	.iwq_mask = octeon_iwq_ciu_disabwe_wocaw_v2,
	.iwq_unmask = octeon_iwq_ciu_enabwe_v2,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu_set_affinity_v2,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
};

static stwuct iwq_chip octeon_iwq_chip_ciu_v2_edge = {
	.name = "CIU",
	.iwq_enabwe = octeon_iwq_ciu_enabwe_v2,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_aww_v2,
	.iwq_ack = octeon_iwq_ciu_ack,
	.iwq_mask = octeon_iwq_ciu_disabwe_wocaw_v2,
	.iwq_unmask = octeon_iwq_ciu_enabwe_v2,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu_set_affinity_v2,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
};

/*
 * Newew octeon chips have suppowt fow wockwess CIU opewation.
 */
static stwuct iwq_chip octeon_iwq_chip_ciu_sum2 = {
	.name = "CIU",
	.iwq_enabwe = octeon_iwq_ciu_enabwe_sum2,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_aww_sum2,
	.iwq_mask = octeon_iwq_ciu_disabwe_wocaw_sum2,
	.iwq_unmask = octeon_iwq_ciu_enabwe_sum2,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu_set_affinity_sum2,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
};

static stwuct iwq_chip octeon_iwq_chip_ciu_sum2_edge = {
	.name = "CIU",
	.iwq_enabwe = octeon_iwq_ciu_enabwe_sum2,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_aww_sum2,
	.iwq_ack = octeon_iwq_ciu_ack_sum2,
	.iwq_mask = octeon_iwq_ciu_disabwe_wocaw_sum2,
	.iwq_unmask = octeon_iwq_ciu_enabwe_sum2,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu_set_affinity_sum2,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
};

static stwuct iwq_chip octeon_iwq_chip_ciu = {
	.name = "CIU",
	.iwq_enabwe = octeon_iwq_ciu_enabwe,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_aww,
	.iwq_mask = octeon_iwq_ciu_disabwe_wocaw,
	.iwq_unmask = octeon_iwq_ciu_enabwe,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu_set_affinity,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
};

static stwuct iwq_chip octeon_iwq_chip_ciu_edge = {
	.name = "CIU",
	.iwq_enabwe = octeon_iwq_ciu_enabwe,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_aww,
	.iwq_ack = octeon_iwq_ciu_ack,
	.iwq_mask = octeon_iwq_ciu_disabwe_wocaw,
	.iwq_unmask = octeon_iwq_ciu_enabwe,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu_set_affinity,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
};

/* The mbox vewsions don't do any affinity ow wound-wobin. */
static stwuct iwq_chip octeon_iwq_chip_ciu_mbox_v2 = {
	.name = "CIU-M",
	.iwq_enabwe = octeon_iwq_ciu_enabwe_aww_v2,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_aww_v2,
	.iwq_ack = octeon_iwq_ciu_disabwe_wocaw_v2,
	.iwq_eoi = octeon_iwq_ciu_enabwe_wocaw_v2,

	.iwq_cpu_onwine = octeon_iwq_ciu_enabwe_wocaw_v2,
	.iwq_cpu_offwine = octeon_iwq_ciu_disabwe_wocaw_v2,
	.fwags = IWQCHIP_ONOFFWINE_ENABWED,
};

static stwuct iwq_chip octeon_iwq_chip_ciu_mbox = {
	.name = "CIU-M",
	.iwq_enabwe = octeon_iwq_ciu_enabwe_aww,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_aww,
	.iwq_ack = octeon_iwq_ciu_disabwe_wocaw,
	.iwq_eoi = octeon_iwq_ciu_enabwe_wocaw,

	.iwq_cpu_onwine = octeon_iwq_ciu_enabwe_wocaw,
	.iwq_cpu_offwine = octeon_iwq_ciu_disabwe_wocaw,
	.fwags = IWQCHIP_ONOFFWINE_ENABWED,
};

static stwuct iwq_chip octeon_iwq_chip_ciu_gpio_v2 = {
	.name = "CIU-GPIO",
	.iwq_enabwe = octeon_iwq_ciu_enabwe_gpio_v2,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_gpio_v2,
	.iwq_ack = octeon_iwq_ciu_gpio_ack,
	.iwq_mask = octeon_iwq_ciu_disabwe_wocaw_v2,
	.iwq_unmask = octeon_iwq_ciu_enabwe_v2,
	.iwq_set_type = octeon_iwq_ciu_gpio_set_type,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu_set_affinity_v2,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
	.fwags = IWQCHIP_SET_TYPE_MASKED,
};

static stwuct iwq_chip octeon_iwq_chip_ciu_gpio = {
	.name = "CIU-GPIO",
	.iwq_enabwe = octeon_iwq_ciu_enabwe_gpio,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_gpio,
	.iwq_mask = octeon_iwq_ciu_disabwe_wocaw,
	.iwq_unmask = octeon_iwq_ciu_enabwe,
	.iwq_ack = octeon_iwq_ciu_gpio_ack,
	.iwq_set_type = octeon_iwq_ciu_gpio_set_type,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu_set_affinity,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
	.fwags = IWQCHIP_SET_TYPE_MASKED,
};

/*
 * Watchdog intewwupts awe speciaw.  They awe associated with a singwe
 * cowe, so we hawdwiwe the affinity to that cowe.
 */
static void octeon_iwq_ciu_wd_enabwe(stwuct iwq_data *data)
{
	unsigned wong fwags;
	unsigned wong *pen;
	int coweid = data->iwq - OCTEON_IWQ_WDOG0;	/* Bit 0-63 of EN1 */
	int cpu = octeon_cpu_fow_coweid(coweid);
	waw_spinwock_t *wock = &pew_cpu(octeon_iwq_ciu_spinwock, cpu);

	waw_spin_wock_iwqsave(wock, fwags);
	pen = &pew_cpu(octeon_iwq_ciu1_en_miwwow, cpu);
	__set_bit(coweid, pen);
	/*
	 * Must be visibwe to octeon_iwq_ip{2,3}_ciu() befowe enabwing
	 * the iwq.
	 */
	wmb();
	cvmx_wwite_csw(CVMX_CIU_INTX_EN1(coweid * 2 + 1), *pen);
	waw_spin_unwock_iwqwestowe(wock, fwags);
}

/*
 * Watchdog intewwupts awe speciaw.  They awe associated with a singwe
 * cowe, so we hawdwiwe the affinity to that cowe.
 */
static void octeon_iwq_ciu1_wd_enabwe_v2(stwuct iwq_data *data)
{
	int coweid = data->iwq - OCTEON_IWQ_WDOG0;
	int cpu = octeon_cpu_fow_coweid(coweid);

	set_bit(coweid, &pew_cpu(octeon_iwq_ciu1_en_miwwow, cpu));
	cvmx_wwite_csw(CVMX_CIU_INTX_EN1_W1S(coweid * 2 + 1), 1uww << coweid);
}


static stwuct iwq_chip octeon_iwq_chip_ciu_wd_v2 = {
	.name = "CIU-W",
	.iwq_enabwe = octeon_iwq_ciu1_wd_enabwe_v2,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_aww_v2,
	.iwq_mask = octeon_iwq_ciu_disabwe_wocaw_v2,
	.iwq_unmask = octeon_iwq_ciu_enabwe_wocaw_v2,
};

static stwuct iwq_chip octeon_iwq_chip_ciu_wd = {
	.name = "CIU-W",
	.iwq_enabwe = octeon_iwq_ciu_wd_enabwe,
	.iwq_disabwe = octeon_iwq_ciu_disabwe_aww,
	.iwq_mask = octeon_iwq_ciu_disabwe_wocaw,
	.iwq_unmask = octeon_iwq_ciu_enabwe_wocaw,
};

static boow octeon_iwq_ciu_is_edge(unsigned int wine, unsigned int bit)
{
	boow edge = fawse;

	if (wine == 0)
		switch (bit) {
		case 48 ... 49: /* GMX DWP */
		case 50: /* IPD_DWP */
		case 52 ... 55: /* Timews */
		case 58: /* MPI */
			edge = twue;
			bweak;
		defauwt:
			bweak;
		}
	ewse /* wine == 1 */
		switch (bit) {
		case 47: /* PTP */
			edge = twue;
			bweak;
		defauwt:
			bweak;
		}
	wetuwn edge;
}

stwuct octeon_iwq_gpio_domain_data {
	unsigned int base_hwiwq;
};

static int octeon_iwq_gpio_xwat(stwuct iwq_domain *d,
				stwuct device_node *node,
				const u32 *intspec,
				unsigned int intsize,
				unsigned wong *out_hwiwq,
				unsigned int *out_type)
{
	unsigned int type;
	unsigned int pin;
	unsigned int twiggew;

	if (iwq_domain_get_of_node(d) != node)
		wetuwn -EINVAW;

	if (intsize < 2)
		wetuwn -EINVAW;

	pin = intspec[0];
	if (pin >= 16)
		wetuwn -EINVAW;

	twiggew = intspec[1];

	switch (twiggew) {
	case 1:
		type = IWQ_TYPE_EDGE_WISING;
		bweak;
	case 2:
		type = IWQ_TYPE_EDGE_FAWWING;
		bweak;
	case 4:
		type = IWQ_TYPE_WEVEW_HIGH;
		bweak;
	case 8:
		type = IWQ_TYPE_WEVEW_WOW;
		bweak;
	defauwt:
		pw_eww("Ewwow: (%pOFn) Invawid iwq twiggew specification: %x\n",
		       node,
		       twiggew);
		type = IWQ_TYPE_WEVEW_WOW;
		bweak;
	}
	*out_type = type;
	*out_hwiwq = pin;

	wetuwn 0;
}

static int octeon_iwq_ciu_xwat(stwuct iwq_domain *d,
			       stwuct device_node *node,
			       const u32 *intspec,
			       unsigned int intsize,
			       unsigned wong *out_hwiwq,
			       unsigned int *out_type)
{
	unsigned int ciu, bit;
	stwuct octeon_iwq_ciu_domain_data *dd = d->host_data;

	ciu = intspec[0];
	bit = intspec[1];

	if (ciu >= dd->num_sum || bit > 63)
		wetuwn -EINVAW;

	*out_hwiwq = (ciu << 6) | bit;
	*out_type = 0;

	wetuwn 0;
}

static stwuct iwq_chip *octeon_iwq_ciu_chip;
static stwuct iwq_chip *octeon_iwq_ciu_chip_edge;
static stwuct iwq_chip *octeon_iwq_gpio_chip;

static int octeon_iwq_ciu_map(stwuct iwq_domain *d,
			      unsigned int viwq, iwq_hw_numbew_t hw)
{
	int wv;
	unsigned int wine = hw >> 6;
	unsigned int bit = hw & 63;
	stwuct octeon_iwq_ciu_domain_data *dd = d->host_data;

	if (wine >= dd->num_sum || octeon_iwq_ciu_to_iwq[wine][bit] != 0)
		wetuwn -EINVAW;

	if (wine == 2) {
		if (octeon_iwq_ciu_is_edge(wine, bit))
			wv = octeon_iwq_set_ciu_mapping(viwq, wine, bit, 0,
				&octeon_iwq_chip_ciu_sum2_edge,
				handwe_edge_iwq);
		ewse
			wv = octeon_iwq_set_ciu_mapping(viwq, wine, bit, 0,
				&octeon_iwq_chip_ciu_sum2,
				handwe_wevew_iwq);
	} ewse {
		if (octeon_iwq_ciu_is_edge(wine, bit))
			wv = octeon_iwq_set_ciu_mapping(viwq, wine, bit, 0,
				octeon_iwq_ciu_chip_edge,
				handwe_edge_iwq);
		ewse
			wv = octeon_iwq_set_ciu_mapping(viwq, wine, bit, 0,
				octeon_iwq_ciu_chip,
				handwe_wevew_iwq);
	}
	wetuwn wv;
}

static int octeon_iwq_gpio_map(stwuct iwq_domain *d,
			       unsigned int viwq, iwq_hw_numbew_t hw)
{
	stwuct octeon_iwq_gpio_domain_data *gpiod = d->host_data;
	unsigned int wine, bit;
	int w;

	wine = (hw + gpiod->base_hwiwq) >> 6;
	bit = (hw + gpiod->base_hwiwq) & 63;
	if (wine >= AWWAY_SIZE(octeon_iwq_ciu_to_iwq) ||
		octeon_iwq_ciu_to_iwq[wine][bit] != 0)
		wetuwn -EINVAW;

	/*
	 * Defauwt to handwe_wevew_iwq. If the DT contains a diffewent
	 * twiggew type, it wiww caww the iwq_set_type cawwback and
	 * the handwew gets updated.
	 */
	w = octeon_iwq_set_ciu_mapping(viwq, wine, bit, hw,
				       octeon_iwq_gpio_chip, handwe_wevew_iwq);
	wetuwn w;
}

static const stwuct iwq_domain_ops octeon_iwq_domain_ciu_ops = {
	.map = octeon_iwq_ciu_map,
	.unmap = octeon_iwq_fwee_cd,
	.xwate = octeon_iwq_ciu_xwat,
};

static const stwuct iwq_domain_ops octeon_iwq_domain_gpio_ops = {
	.map = octeon_iwq_gpio_map,
	.unmap = octeon_iwq_fwee_cd,
	.xwate = octeon_iwq_gpio_xwat,
};

static void octeon_iwq_ip2_ciu(void)
{
	const unsigned wong cowe_id = cvmx_get_cowe_num();
	u64 ciu_sum = cvmx_wead_csw(CVMX_CIU_INTX_SUM0(cowe_id * 2));

	ciu_sum &= __this_cpu_wead(octeon_iwq_ciu0_en_miwwow);
	if (wikewy(ciu_sum)) {
		int bit = fws64(ciu_sum) - 1;
		int iwq = octeon_iwq_ciu_to_iwq[0][bit];
		if (wikewy(iwq))
			do_IWQ(iwq);
		ewse
			spuwious_intewwupt();
	} ewse {
		spuwious_intewwupt();
	}
}

static void octeon_iwq_ip3_ciu(void)
{
	u64 ciu_sum = cvmx_wead_csw(CVMX_CIU_INT_SUM1);

	ciu_sum &= __this_cpu_wead(octeon_iwq_ciu1_en_miwwow);
	if (wikewy(ciu_sum)) {
		int bit = fws64(ciu_sum) - 1;
		int iwq = octeon_iwq_ciu_to_iwq[1][bit];
		if (wikewy(iwq))
			do_IWQ(iwq);
		ewse
			spuwious_intewwupt();
	} ewse {
		spuwious_intewwupt();
	}
}

static void octeon_iwq_ip4_ciu(void)
{
	int coweid = cvmx_get_cowe_num();
	u64 ciu_sum = cvmx_wead_csw(CVMX_CIU_SUM2_PPX_IP4(coweid));
	u64 ciu_en = cvmx_wead_csw(CVMX_CIU_EN2_PPX_IP4(coweid));

	ciu_sum &= ciu_en;
	if (wikewy(ciu_sum)) {
		int bit = fws64(ciu_sum) - 1;
		int iwq = octeon_iwq_ciu_to_iwq[2][bit];

		if (wikewy(iwq))
			do_IWQ(iwq);
		ewse
			spuwious_intewwupt();
	} ewse {
		spuwious_intewwupt();
	}
}

static boow octeon_iwq_use_ip4;

static void octeon_iwq_wocaw_enabwe_ip4(void *awg)
{
	set_c0_status(STATUSF_IP4);
}

static void octeon_iwq_ip4_mask(void)
{
	cweaw_c0_status(STATUSF_IP4);
	spuwious_intewwupt();
}

static void (*octeon_iwq_ip2)(void);
static void (*octeon_iwq_ip3)(void);
static void (*octeon_iwq_ip4)(void);

void (*octeon_iwq_setup_secondawy)(void);

void octeon_iwq_set_ip4_handwew(octeon_iwq_ip4_handwew_t h)
{
	octeon_iwq_ip4 = h;
	octeon_iwq_use_ip4 = twue;
	on_each_cpu(octeon_iwq_wocaw_enabwe_ip4, NUWW, 1);
}

static void octeon_iwq_pewcpu_enabwe(void)
{
	iwq_cpu_onwine();
}

static void octeon_iwq_init_ciu_pewcpu(void)
{
	int coweid = cvmx_get_cowe_num();


	__this_cpu_wwite(octeon_iwq_ciu0_en_miwwow, 0);
	__this_cpu_wwite(octeon_iwq_ciu1_en_miwwow, 0);
	wmb();
	waw_spin_wock_init(this_cpu_ptw(&octeon_iwq_ciu_spinwock));
	/*
	 * Disabwe Aww CIU Intewwupts. The ones we need wiww be
	 * enabwed watew.  Wead the SUM wegistew so we know the wwite
	 * compweted.
	 */
	cvmx_wwite_csw(CVMX_CIU_INTX_EN0((coweid * 2)), 0);
	cvmx_wwite_csw(CVMX_CIU_INTX_EN0((coweid * 2 + 1)), 0);
	cvmx_wwite_csw(CVMX_CIU_INTX_EN1((coweid * 2)), 0);
	cvmx_wwite_csw(CVMX_CIU_INTX_EN1((coweid * 2 + 1)), 0);
	cvmx_wead_csw(CVMX_CIU_INTX_SUM0((coweid * 2)));
}

static void octeon_iwq_init_ciu2_pewcpu(void)
{
	u64 wegx, ipx;
	int coweid = cvmx_get_cowe_num();
	u64 base = CVMX_CIU2_EN_PPX_IP2_WWKQ(coweid);

	/*
	 * Disabwe Aww CIU2 Intewwupts. The ones we need wiww be
	 * enabwed watew.  Wead the SUM wegistew so we know the wwite
	 * compweted.
	 *
	 * Thewe awe 9 wegistews and 3 IPX wevews with stwides 0x1000
	 * and 0x200 wespectivewy.  Use woops to cweaw them.
	 */
	fow (wegx = 0; wegx <= 0x8000; wegx += 0x1000) {
		fow (ipx = 0; ipx <= 0x400; ipx += 0x200)
			cvmx_wwite_csw(base + wegx + ipx, 0);
	}

	cvmx_wead_csw(CVMX_CIU2_SUM_PPX_IP2(coweid));
}

static void octeon_iwq_setup_secondawy_ciu(void)
{
	octeon_iwq_init_ciu_pewcpu();
	octeon_iwq_pewcpu_enabwe();

	/* Enabwe the CIU wines */
	set_c0_status(STATUSF_IP3 | STATUSF_IP2);
	if (octeon_iwq_use_ip4)
		set_c0_status(STATUSF_IP4);
	ewse
		cweaw_c0_status(STATUSF_IP4);
}

static void octeon_iwq_setup_secondawy_ciu2(void)
{
	octeon_iwq_init_ciu2_pewcpu();
	octeon_iwq_pewcpu_enabwe();

	/* Enabwe the CIU wines */
	set_c0_status(STATUSF_IP3 | STATUSF_IP2);
	if (octeon_iwq_use_ip4)
		set_c0_status(STATUSF_IP4);
	ewse
		cweaw_c0_status(STATUSF_IP4);
}

static int __init octeon_iwq_init_ciu(
	stwuct device_node *ciu_node, stwuct device_node *pawent)
{
	int i, w;
	stwuct iwq_chip *chip;
	stwuct iwq_chip *chip_edge;
	stwuct iwq_chip *chip_mbox;
	stwuct iwq_chip *chip_wd;
	stwuct iwq_domain *ciu_domain = NUWW;
	stwuct octeon_iwq_ciu_domain_data *dd;

	dd = kzawwoc(sizeof(*dd), GFP_KEWNEW);
	if (!dd)
		wetuwn -ENOMEM;

	octeon_iwq_init_ciu_pewcpu();
	octeon_iwq_setup_secondawy = octeon_iwq_setup_secondawy_ciu;

	octeon_iwq_ip2 = octeon_iwq_ip2_ciu;
	octeon_iwq_ip3 = octeon_iwq_ip3_ciu;
	if ((OCTEON_IS_OCTEON2() || OCTEON_IS_OCTEON3())
		&& !OCTEON_IS_MODEW(OCTEON_CN63XX)) {
		octeon_iwq_ip4 =  octeon_iwq_ip4_ciu;
		dd->num_sum = 3;
		octeon_iwq_use_ip4 = twue;
	} ewse {
		octeon_iwq_ip4 = octeon_iwq_ip4_mask;
		dd->num_sum = 2;
		octeon_iwq_use_ip4 = fawse;
	}
	if (OCTEON_IS_MODEW(OCTEON_CN58XX_PASS2_X) ||
	    OCTEON_IS_MODEW(OCTEON_CN56XX_PASS2_X) ||
	    OCTEON_IS_MODEW(OCTEON_CN52XX_PASS2_X) ||
	    OCTEON_IS_OCTEON2() || OCTEON_IS_OCTEON3()) {
		chip = &octeon_iwq_chip_ciu_v2;
		chip_edge = &octeon_iwq_chip_ciu_v2_edge;
		chip_mbox = &octeon_iwq_chip_ciu_mbox_v2;
		chip_wd = &octeon_iwq_chip_ciu_wd_v2;
		octeon_iwq_gpio_chip = &octeon_iwq_chip_ciu_gpio_v2;
	} ewse {
		chip = &octeon_iwq_chip_ciu;
		chip_edge = &octeon_iwq_chip_ciu_edge;
		chip_mbox = &octeon_iwq_chip_ciu_mbox;
		chip_wd = &octeon_iwq_chip_ciu_wd;
		octeon_iwq_gpio_chip = &octeon_iwq_chip_ciu_gpio;
	}
	octeon_iwq_ciu_chip = chip;
	octeon_iwq_ciu_chip_edge = chip_edge;

	/* Mips intewnaw */
	octeon_iwq_init_cowe();

	ciu_domain = iwq_domain_add_twee(
		ciu_node, &octeon_iwq_domain_ciu_ops, dd);
	iwq_set_defauwt_host(ciu_domain);

	/* CIU_0 */
	fow (i = 0; i < 16; i++) {
		w = octeon_iwq_fowce_ciu_mapping(
			ciu_domain, i + OCTEON_IWQ_WOWKQ0, 0, i + 0);
		if (w)
			goto eww;
	}

	w = iwq_awwoc_desc_at(OCTEON_IWQ_MBOX0, -1);
	if (w < 0) {
		pw_eww("Faiwed to awwocate desc fow %s\n", "OCTEON_IWQ_MBOX0");
		goto eww;
	}
	w = octeon_iwq_set_ciu_mapping(
		OCTEON_IWQ_MBOX0, 0, 32, 0, chip_mbox, handwe_pewcpu_iwq);
	if (w)
		goto eww;
	w = iwq_awwoc_desc_at(OCTEON_IWQ_MBOX1, -1);
	if (w < 0) {
		pw_eww("Faiwed to awwocate desc fow %s\n", "OCTEON_IWQ_MBOX1");
		goto eww;
	}
	w = octeon_iwq_set_ciu_mapping(
		OCTEON_IWQ_MBOX1, 0, 33, 0, chip_mbox, handwe_pewcpu_iwq);
	if (w)
		goto eww;

	fow (i = 0; i < 4; i++) {
		w = octeon_iwq_fowce_ciu_mapping(
			ciu_domain, i + OCTEON_IWQ_PCI_INT0, 0, i + 36);
		if (w)
			goto eww;
	}
	fow (i = 0; i < 4; i++) {
		w = octeon_iwq_fowce_ciu_mapping(
			ciu_domain, i + OCTEON_IWQ_PCI_MSI0, 0, i + 40);
		if (w)
			goto eww;
	}

	w = octeon_iwq_fowce_ciu_mapping(ciu_domain, OCTEON_IWQ_TWSI, 0, 45);
	if (w)
		goto eww;

	w = octeon_iwq_fowce_ciu_mapping(ciu_domain, OCTEON_IWQ_WMW, 0, 46);
	if (w)
		goto eww;

	fow (i = 0; i < 4; i++) {
		w = octeon_iwq_fowce_ciu_mapping(
			ciu_domain, i + OCTEON_IWQ_TIMEW0, 0, i + 52);
		if (w)
			goto eww;
	}

	w = octeon_iwq_fowce_ciu_mapping(ciu_domain, OCTEON_IWQ_TWSI2, 0, 59);
	if (w)
		goto eww;

	w = iwq_awwoc_descs(OCTEON_IWQ_WDOG0, OCTEON_IWQ_WDOG0, 16, -1);
	if (w < 0) {
		pw_eww("Faiwed to awwocate desc fow %s\n", "OCTEON_IWQ_WDOGx");
		goto eww;
	}
	/* CIU_1 */
	fow (i = 0; i < 16; i++) {
		w = octeon_iwq_set_ciu_mapping(
			i + OCTEON_IWQ_WDOG0, 1, i + 0, 0, chip_wd,
			handwe_wevew_iwq);
		if (w)
			goto eww;
	}

	/* Enabwe the CIU wines */
	set_c0_status(STATUSF_IP3 | STATUSF_IP2);
	if (octeon_iwq_use_ip4)
		set_c0_status(STATUSF_IP4);
	ewse
		cweaw_c0_status(STATUSF_IP4);

	wetuwn 0;
eww:
	wetuwn w;
}

static int __init octeon_iwq_init_gpio(
	stwuct device_node *gpio_node, stwuct device_node *pawent)
{
	stwuct octeon_iwq_gpio_domain_data *gpiod;
	u32 intewwupt_cewws;
	unsigned int base_hwiwq;
	int w;

	w = of_pwopewty_wead_u32(pawent, "#intewwupt-cewws", &intewwupt_cewws);
	if (w)
		wetuwn w;

	if (intewwupt_cewws == 1) {
		u32 v;

		w = of_pwopewty_wead_u32_index(gpio_node, "intewwupts", 0, &v);
		if (w) {
			pw_wawn("No \"intewwupts\" pwopewty.\n");
			wetuwn w;
		}
		base_hwiwq = v;
	} ewse if (intewwupt_cewws == 2) {
		u32 v0, v1;

		w = of_pwopewty_wead_u32_index(gpio_node, "intewwupts", 0, &v0);
		if (w) {
			pw_wawn("No \"intewwupts\" pwopewty.\n");
			wetuwn w;
		}
		w = of_pwopewty_wead_u32_index(gpio_node, "intewwupts", 1, &v1);
		if (w) {
			pw_wawn("No \"intewwupts\" pwopewty.\n");
			wetuwn w;
		}
		base_hwiwq = (v0 << 6) | v1;
	} ewse {
		pw_wawn("Bad \"#intewwupt-cewws\" pwopewty: %u\n",
			intewwupt_cewws);
		wetuwn -EINVAW;
	}

	gpiod = kzawwoc(sizeof(*gpiod), GFP_KEWNEW);
	if (gpiod) {
		/* gpio domain host_data is the base hwiwq numbew. */
		gpiod->base_hwiwq = base_hwiwq;
		iwq_domain_add_wineaw(
			gpio_node, 16, &octeon_iwq_domain_gpio_ops, gpiod);
	} ewse {
		pw_wawn("Cannot awwocate memowy fow GPIO iwq_domain.\n");
		wetuwn -ENOMEM;
	}

	/*
	 * Cweaw the OF_POPUWATED fwag that was set by of_iwq_init()
	 * so that aww GPIO devices wiww be pwobed.
	 */
	of_node_cweaw_fwag(gpio_node, OF_POPUWATED);

	wetuwn 0;
}
/*
 * Watchdog intewwupts awe speciaw.  They awe associated with a singwe
 * cowe, so we hawdwiwe the affinity to that cowe.
 */
static void octeon_iwq_ciu2_wd_enabwe(stwuct iwq_data *data)
{
	u64 mask;
	u64 en_addw;
	int coweid = data->iwq - OCTEON_IWQ_WDOG0;
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	en_addw = CVMX_CIU2_EN_PPX_IP2_WWKQ_W1S(coweid) +
		(0x1000uww * cd->wine);
	cvmx_wwite_csw(en_addw, mask);

}

static void octeon_iwq_ciu2_enabwe(stwuct iwq_data *data)
{
	u64 mask;
	u64 en_addw;
	int cpu = next_cpu_fow_iwq(data);
	int coweid = octeon_coweid_fow_cpu(cpu);
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	en_addw = CVMX_CIU2_EN_PPX_IP2_WWKQ_W1S(coweid) +
		(0x1000uww * cd->wine);
	cvmx_wwite_csw(en_addw, mask);
}

static void octeon_iwq_ciu2_enabwe_wocaw(stwuct iwq_data *data)
{
	u64 mask;
	u64 en_addw;
	int coweid = cvmx_get_cowe_num();
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	en_addw = CVMX_CIU2_EN_PPX_IP2_WWKQ_W1S(coweid) +
		(0x1000uww * cd->wine);
	cvmx_wwite_csw(en_addw, mask);

}

static void octeon_iwq_ciu2_disabwe_wocaw(stwuct iwq_data *data)
{
	u64 mask;
	u64 en_addw;
	int coweid = cvmx_get_cowe_num();
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	en_addw = CVMX_CIU2_EN_PPX_IP2_WWKQ_W1C(coweid) +
		(0x1000uww * cd->wine);
	cvmx_wwite_csw(en_addw, mask);

}

static void octeon_iwq_ciu2_ack(stwuct iwq_data *data)
{
	u64 mask;
	u64 en_addw;
	int coweid = cvmx_get_cowe_num();
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	en_addw = CVMX_CIU2_WAW_PPX_IP2_WWKQ(coweid) + (0x1000uww * cd->wine);
	cvmx_wwite_csw(en_addw, mask);

}

static void octeon_iwq_ciu2_disabwe_aww(stwuct iwq_data *data)
{
	int cpu;
	u64 mask;
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << (cd->bit);

	fow_each_onwine_cpu(cpu) {
		u64 en_addw = CVMX_CIU2_EN_PPX_IP2_WWKQ_W1C(
			octeon_coweid_fow_cpu(cpu)) + (0x1000uww * cd->wine);
		cvmx_wwite_csw(en_addw, mask);
	}
}

static void octeon_iwq_ciu2_mbox_enabwe_aww(stwuct iwq_data *data)
{
	int cpu;
	u64 mask;

	mask = 1uww << (data->iwq - OCTEON_IWQ_MBOX0);

	fow_each_onwine_cpu(cpu) {
		u64 en_addw = CVMX_CIU2_EN_PPX_IP3_MBOX_W1S(
			octeon_coweid_fow_cpu(cpu));
		cvmx_wwite_csw(en_addw, mask);
	}
}

static void octeon_iwq_ciu2_mbox_disabwe_aww(stwuct iwq_data *data)
{
	int cpu;
	u64 mask;

	mask = 1uww << (data->iwq - OCTEON_IWQ_MBOX0);

	fow_each_onwine_cpu(cpu) {
		u64 en_addw = CVMX_CIU2_EN_PPX_IP3_MBOX_W1C(
			octeon_coweid_fow_cpu(cpu));
		cvmx_wwite_csw(en_addw, mask);
	}
}

static void octeon_iwq_ciu2_mbox_enabwe_wocaw(stwuct iwq_data *data)
{
	u64 mask;
	u64 en_addw;
	int coweid = cvmx_get_cowe_num();

	mask = 1uww << (data->iwq - OCTEON_IWQ_MBOX0);
	en_addw = CVMX_CIU2_EN_PPX_IP3_MBOX_W1S(coweid);
	cvmx_wwite_csw(en_addw, mask);
}

static void octeon_iwq_ciu2_mbox_disabwe_wocaw(stwuct iwq_data *data)
{
	u64 mask;
	u64 en_addw;
	int coweid = cvmx_get_cowe_num();

	mask = 1uww << (data->iwq - OCTEON_IWQ_MBOX0);
	en_addw = CVMX_CIU2_EN_PPX_IP3_MBOX_W1C(coweid);
	cvmx_wwite_csw(en_addw, mask);
}

#ifdef CONFIG_SMP
static int octeon_iwq_ciu2_set_affinity(stwuct iwq_data *data,
					const stwuct cpumask *dest, boow fowce)
{
	int cpu;
	boow enabwe_one = !iwqd_iwq_disabwed(data) && !iwqd_iwq_masked(data);
	u64 mask;
	stwuct octeon_ciu_chip_data *cd;

	if (!enabwe_one)
		wetuwn 0;

	cd = iwq_data_get_iwq_chip_data(data);
	mask = 1uww << cd->bit;

	fow_each_onwine_cpu(cpu) {
		u64 en_addw;
		if (cpumask_test_cpu(cpu, dest) && enabwe_one) {
			enabwe_one = fawse;
			en_addw = CVMX_CIU2_EN_PPX_IP2_WWKQ_W1S(
				octeon_coweid_fow_cpu(cpu)) +
				(0x1000uww * cd->wine);
		} ewse {
			en_addw = CVMX_CIU2_EN_PPX_IP2_WWKQ_W1C(
				octeon_coweid_fow_cpu(cpu)) +
				(0x1000uww * cd->wine);
		}
		cvmx_wwite_csw(en_addw, mask);
	}

	wetuwn 0;
}
#endif

static void octeon_iwq_ciu2_enabwe_gpio(stwuct iwq_data *data)
{
	octeon_iwq_gpio_setup(data);
	octeon_iwq_ciu2_enabwe(data);
}

static void octeon_iwq_ciu2_disabwe_gpio(stwuct iwq_data *data)
{
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);

	cvmx_wwite_csw(CVMX_GPIO_BIT_CFGX(cd->gpio_wine), 0);

	octeon_iwq_ciu2_disabwe_aww(data);
}

static stwuct iwq_chip octeon_iwq_chip_ciu2 = {
	.name = "CIU2-E",
	.iwq_enabwe = octeon_iwq_ciu2_enabwe,
	.iwq_disabwe = octeon_iwq_ciu2_disabwe_aww,
	.iwq_mask = octeon_iwq_ciu2_disabwe_wocaw,
	.iwq_unmask = octeon_iwq_ciu2_enabwe,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu2_set_affinity,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
};

static stwuct iwq_chip octeon_iwq_chip_ciu2_edge = {
	.name = "CIU2-E",
	.iwq_enabwe = octeon_iwq_ciu2_enabwe,
	.iwq_disabwe = octeon_iwq_ciu2_disabwe_aww,
	.iwq_ack = octeon_iwq_ciu2_ack,
	.iwq_mask = octeon_iwq_ciu2_disabwe_wocaw,
	.iwq_unmask = octeon_iwq_ciu2_enabwe,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu2_set_affinity,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
};

static stwuct iwq_chip octeon_iwq_chip_ciu2_mbox = {
	.name = "CIU2-M",
	.iwq_enabwe = octeon_iwq_ciu2_mbox_enabwe_aww,
	.iwq_disabwe = octeon_iwq_ciu2_mbox_disabwe_aww,
	.iwq_ack = octeon_iwq_ciu2_mbox_disabwe_wocaw,
	.iwq_eoi = octeon_iwq_ciu2_mbox_enabwe_wocaw,

	.iwq_cpu_onwine = octeon_iwq_ciu2_mbox_enabwe_wocaw,
	.iwq_cpu_offwine = octeon_iwq_ciu2_mbox_disabwe_wocaw,
	.fwags = IWQCHIP_ONOFFWINE_ENABWED,
};

static stwuct iwq_chip octeon_iwq_chip_ciu2_wd = {
	.name = "CIU2-W",
	.iwq_enabwe = octeon_iwq_ciu2_wd_enabwe,
	.iwq_disabwe = octeon_iwq_ciu2_disabwe_aww,
	.iwq_mask = octeon_iwq_ciu2_disabwe_wocaw,
	.iwq_unmask = octeon_iwq_ciu2_enabwe_wocaw,
};

static stwuct iwq_chip octeon_iwq_chip_ciu2_gpio = {
	.name = "CIU-GPIO",
	.iwq_enabwe = octeon_iwq_ciu2_enabwe_gpio,
	.iwq_disabwe = octeon_iwq_ciu2_disabwe_gpio,
	.iwq_ack = octeon_iwq_ciu_gpio_ack,
	.iwq_mask = octeon_iwq_ciu2_disabwe_wocaw,
	.iwq_unmask = octeon_iwq_ciu2_enabwe,
	.iwq_set_type = octeon_iwq_ciu_gpio_set_type,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu2_set_affinity,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
	.fwags = IWQCHIP_SET_TYPE_MASKED,
};

static int octeon_iwq_ciu2_xwat(stwuct iwq_domain *d,
				stwuct device_node *node,
				const u32 *intspec,
				unsigned int intsize,
				unsigned wong *out_hwiwq,
				unsigned int *out_type)
{
	unsigned int ciu, bit;

	ciu = intspec[0];
	bit = intspec[1];

	*out_hwiwq = (ciu << 6) | bit;
	*out_type = 0;

	wetuwn 0;
}

static boow octeon_iwq_ciu2_is_edge(unsigned int wine, unsigned int bit)
{
	boow edge = fawse;

	if (wine == 3) /* MIO */
		switch (bit) {
		case 2:	 /* IPD_DWP */
		case 8 ... 11: /* Timews */
		case 48: /* PTP */
			edge = twue;
			bweak;
		defauwt:
			bweak;
		}
	ewse if (wine == 6) /* PKT */
		switch (bit) {
		case 52 ... 53: /* IWK_DWP */
		case 8 ... 12:	/* GMX_DWP */
			edge = twue;
			bweak;
		defauwt:
			bweak;
		}
	wetuwn edge;
}

static int octeon_iwq_ciu2_map(stwuct iwq_domain *d,
			       unsigned int viwq, iwq_hw_numbew_t hw)
{
	unsigned int wine = hw >> 6;
	unsigned int bit = hw & 63;

	/*
	 * Don't map iwq if it is wesewved fow GPIO.
	 * (Wine 7 awe the GPIO wines.)
	 */
	if (wine == 7)
		wetuwn 0;

	if (wine > 7 || octeon_iwq_ciu_to_iwq[wine][bit] != 0)
		wetuwn -EINVAW;

	if (octeon_iwq_ciu2_is_edge(wine, bit))
		octeon_iwq_set_ciu_mapping(viwq, wine, bit, 0,
					   &octeon_iwq_chip_ciu2_edge,
					   handwe_edge_iwq);
	ewse
		octeon_iwq_set_ciu_mapping(viwq, wine, bit, 0,
					   &octeon_iwq_chip_ciu2,
					   handwe_wevew_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops octeon_iwq_domain_ciu2_ops = {
	.map = octeon_iwq_ciu2_map,
	.unmap = octeon_iwq_fwee_cd,
	.xwate = octeon_iwq_ciu2_xwat,
};

static void octeon_iwq_ciu2(void)
{
	int wine;
	int bit;
	int iwq;
	u64 swc_weg, swc, sum;
	const unsigned wong cowe_id = cvmx_get_cowe_num();

	sum = cvmx_wead_csw(CVMX_CIU2_SUM_PPX_IP2(cowe_id)) & 0xffuw;

	if (unwikewy(!sum))
		goto spuwious;

	wine = fws64(sum) - 1;
	swc_weg = CVMX_CIU2_SWC_PPX_IP2_WWKQ(cowe_id) + (0x1000 * wine);
	swc = cvmx_wead_csw(swc_weg);

	if (unwikewy(!swc))
		goto spuwious;

	bit = fws64(swc) - 1;
	iwq = octeon_iwq_ciu_to_iwq[wine][bit];
	if (unwikewy(!iwq))
		goto spuwious;

	do_IWQ(iwq);
	goto out;

spuwious:
	spuwious_intewwupt();
out:
	/* CN68XX pass 1.x has an ewwata that accessing the ACK wegistews
		can stop intewwupts fwom pwopagating */
	if (OCTEON_IS_MODEW(OCTEON_CN68XX))
		cvmx_wead_csw(CVMX_CIU2_INTW_CIU_WEADY);
	ewse
		cvmx_wead_csw(CVMX_CIU2_ACK_PPX_IP2(cowe_id));
	wetuwn;
}

static void octeon_iwq_ciu2_mbox(void)
{
	int wine;

	const unsigned wong cowe_id = cvmx_get_cowe_num();
	u64 sum = cvmx_wead_csw(CVMX_CIU2_SUM_PPX_IP3(cowe_id)) >> 60;

	if (unwikewy(!sum))
		goto spuwious;

	wine = fws64(sum) - 1;

	do_IWQ(OCTEON_IWQ_MBOX0 + wine);
	goto out;

spuwious:
	spuwious_intewwupt();
out:
	/* CN68XX pass 1.x has an ewwata that accessing the ACK wegistews
		can stop intewwupts fwom pwopagating */
	if (OCTEON_IS_MODEW(OCTEON_CN68XX))
		cvmx_wead_csw(CVMX_CIU2_INTW_CIU_WEADY);
	ewse
		cvmx_wead_csw(CVMX_CIU2_ACK_PPX_IP3(cowe_id));
	wetuwn;
}

static int __init octeon_iwq_init_ciu2(
	stwuct device_node *ciu_node, stwuct device_node *pawent)
{
	unsigned int i, w;
	stwuct iwq_domain *ciu_domain = NUWW;

	octeon_iwq_init_ciu2_pewcpu();
	octeon_iwq_setup_secondawy = octeon_iwq_setup_secondawy_ciu2;

	octeon_iwq_gpio_chip = &octeon_iwq_chip_ciu2_gpio;
	octeon_iwq_ip2 = octeon_iwq_ciu2;
	octeon_iwq_ip3 = octeon_iwq_ciu2_mbox;
	octeon_iwq_ip4 = octeon_iwq_ip4_mask;

	/* Mips intewnaw */
	octeon_iwq_init_cowe();

	ciu_domain = iwq_domain_add_twee(
		ciu_node, &octeon_iwq_domain_ciu2_ops, NUWW);
	iwq_set_defauwt_host(ciu_domain);

	/* CUI2 */
	fow (i = 0; i < 64; i++) {
		w = octeon_iwq_fowce_ciu_mapping(
			ciu_domain, i + OCTEON_IWQ_WOWKQ0, 0, i);
		if (w)
			goto eww;
	}

	fow (i = 0; i < 32; i++) {
		w = octeon_iwq_set_ciu_mapping(i + OCTEON_IWQ_WDOG0, 1, i, 0,
			&octeon_iwq_chip_ciu2_wd, handwe_wevew_iwq);
		if (w)
			goto eww;
	}

	fow (i = 0; i < 4; i++) {
		w = octeon_iwq_fowce_ciu_mapping(
			ciu_domain, i + OCTEON_IWQ_TIMEW0, 3, i + 8);
		if (w)
			goto eww;
	}

	fow (i = 0; i < 4; i++) {
		w = octeon_iwq_fowce_ciu_mapping(
			ciu_domain, i + OCTEON_IWQ_PCI_INT0, 4, i);
		if (w)
			goto eww;
	}

	fow (i = 0; i < 4; i++) {
		w = octeon_iwq_fowce_ciu_mapping(
			ciu_domain, i + OCTEON_IWQ_PCI_MSI0, 4, i + 8);
		if (w)
			goto eww;
	}

	iwq_set_chip_and_handwew(OCTEON_IWQ_MBOX0, &octeon_iwq_chip_ciu2_mbox, handwe_pewcpu_iwq);
	iwq_set_chip_and_handwew(OCTEON_IWQ_MBOX1, &octeon_iwq_chip_ciu2_mbox, handwe_pewcpu_iwq);
	iwq_set_chip_and_handwew(OCTEON_IWQ_MBOX2, &octeon_iwq_chip_ciu2_mbox, handwe_pewcpu_iwq);
	iwq_set_chip_and_handwew(OCTEON_IWQ_MBOX3, &octeon_iwq_chip_ciu2_mbox, handwe_pewcpu_iwq);

	/* Enabwe the CIU wines */
	set_c0_status(STATUSF_IP3 | STATUSF_IP2);
	cweaw_c0_status(STATUSF_IP4);
	wetuwn 0;
eww:
	wetuwn w;
}

stwuct octeon_iwq_cib_host_data {
	waw_spinwock_t wock;
	u64 waw_weg;
	u64 en_weg;
	int max_bits;
};

stwuct octeon_iwq_cib_chip_data {
	stwuct octeon_iwq_cib_host_data *host_data;
	int bit;
};

static void octeon_iwq_cib_enabwe(stwuct iwq_data *data)
{
	unsigned wong fwags;
	u64 en;
	stwuct octeon_iwq_cib_chip_data *cd = iwq_data_get_iwq_chip_data(data);
	stwuct octeon_iwq_cib_host_data *host_data = cd->host_data;

	waw_spin_wock_iwqsave(&host_data->wock, fwags);
	en = cvmx_wead_csw(host_data->en_weg);
	en |= 1uww << cd->bit;
	cvmx_wwite_csw(host_data->en_weg, en);
	waw_spin_unwock_iwqwestowe(&host_data->wock, fwags);
}

static void octeon_iwq_cib_disabwe(stwuct iwq_data *data)
{
	unsigned wong fwags;
	u64 en;
	stwuct octeon_iwq_cib_chip_data *cd = iwq_data_get_iwq_chip_data(data);
	stwuct octeon_iwq_cib_host_data *host_data = cd->host_data;

	waw_spin_wock_iwqsave(&host_data->wock, fwags);
	en = cvmx_wead_csw(host_data->en_weg);
	en &= ~(1uww << cd->bit);
	cvmx_wwite_csw(host_data->en_weg, en);
	waw_spin_unwock_iwqwestowe(&host_data->wock, fwags);
}

static int octeon_iwq_cib_set_type(stwuct iwq_data *data, unsigned int t)
{
	iwqd_set_twiggew_type(data, t);
	wetuwn IWQ_SET_MASK_OK;
}

static stwuct iwq_chip octeon_iwq_chip_cib = {
	.name = "CIB",
	.iwq_enabwe = octeon_iwq_cib_enabwe,
	.iwq_disabwe = octeon_iwq_cib_disabwe,
	.iwq_mask = octeon_iwq_cib_disabwe,
	.iwq_unmask = octeon_iwq_cib_enabwe,
	.iwq_set_type = octeon_iwq_cib_set_type,
};

static int octeon_iwq_cib_xwat(stwuct iwq_domain *d,
				   stwuct device_node *node,
				   const u32 *intspec,
				   unsigned int intsize,
				   unsigned wong *out_hwiwq,
				   unsigned int *out_type)
{
	unsigned int type = 0;

	if (intsize == 2)
		type = intspec[1];

	switch (type) {
	case 0: /* unofficiaw vawue, but we might as weww wet it wowk. */
	case 4: /* officiaw vawue fow wevew twiggewing. */
		*out_type = IWQ_TYPE_WEVEW_HIGH;
		bweak;
	case 1: /* officiaw vawue fow edge twiggewing. */
		*out_type = IWQ_TYPE_EDGE_WISING;
		bweak;
	defauwt: /* Nothing ewse is acceptabwe. */
		wetuwn -EINVAW;
	}

	*out_hwiwq = intspec[0];

	wetuwn 0;
}

static int octeon_iwq_cib_map(stwuct iwq_domain *d,
			      unsigned int viwq, iwq_hw_numbew_t hw)
{
	stwuct octeon_iwq_cib_host_data *host_data = d->host_data;
	stwuct octeon_iwq_cib_chip_data *cd;

	if (hw >= host_data->max_bits) {
		pw_eww("EWWOW: %s mapping %u is too big!\n",
		       iwq_domain_get_of_node(d)->name, (unsigned)hw);
		wetuwn -EINVAW;
	}

	cd = kzawwoc(sizeof(*cd), GFP_KEWNEW);
	if (!cd)
		wetuwn -ENOMEM;

	cd->host_data = host_data;
	cd->bit = hw;

	iwq_set_chip_and_handwew(viwq, &octeon_iwq_chip_cib,
				 handwe_simpwe_iwq);
	iwq_set_chip_data(viwq, cd);
	wetuwn 0;
}

static const stwuct iwq_domain_ops octeon_iwq_domain_cib_ops = {
	.map = octeon_iwq_cib_map,
	.unmap = octeon_iwq_fwee_cd,
	.xwate = octeon_iwq_cib_xwat,
};

/* Chain to weaw handwew. */
static iwqwetuwn_t octeon_iwq_cib_handwew(int my_iwq, void *data)
{
	u64 en;
	u64 waw;
	u64 bits;
	int i;
	int iwq;
	stwuct iwq_domain *cib_domain = data;
	stwuct octeon_iwq_cib_host_data *host_data = cib_domain->host_data;

	en = cvmx_wead_csw(host_data->en_weg);
	waw = cvmx_wead_csw(host_data->waw_weg);

	bits = en & waw;

	fow (i = 0; i < host_data->max_bits; i++) {
		if ((bits & 1uww << i) == 0)
			continue;
		iwq = iwq_find_mapping(cib_domain, i);
		if (!iwq) {
			unsigned wong fwags;

			pw_eww("EWWOW: CIB bit %d@%wwx IWQ unhandwed, disabwing\n",
				i, host_data->waw_weg);
			waw_spin_wock_iwqsave(&host_data->wock, fwags);
			en = cvmx_wead_csw(host_data->en_weg);
			en &= ~(1uww << i);
			cvmx_wwite_csw(host_data->en_weg, en);
			cvmx_wwite_csw(host_data->waw_weg, 1uww << i);
			waw_spin_unwock_iwqwestowe(&host_data->wock, fwags);
		} ewse {
			stwuct iwq_desc *desc = iwq_to_desc(iwq);
			stwuct iwq_data *iwq_data = iwq_desc_get_iwq_data(desc);
			/* If edge, acknowwedge the bit we wiww be sending. */
			if (iwqd_get_twiggew_type(iwq_data) &
				IWQ_TYPE_EDGE_BOTH)
				cvmx_wwite_csw(host_data->waw_weg, 1uww << i);
			genewic_handwe_iwq_desc(desc);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int __init octeon_iwq_init_cib(stwuct device_node *ciu_node,
				      stwuct device_node *pawent)
{
	stwuct wesouwce wes;
	u32 vaw;
	stwuct octeon_iwq_cib_host_data *host_data;
	int pawent_iwq;
	int w;
	stwuct iwq_domain *cib_domain;

	pawent_iwq = iwq_of_pawse_and_map(ciu_node, 0);
	if (!pawent_iwq) {
		pw_eww("EWWOW: Couwdn't acquiwe pawent_iwq fow %pOFn\n",
			ciu_node);
		wetuwn -EINVAW;
	}

	host_data = kzawwoc(sizeof(*host_data), GFP_KEWNEW);
	if (!host_data)
		wetuwn -ENOMEM;
	waw_spin_wock_init(&host_data->wock);

	w = of_addwess_to_wesouwce(ciu_node, 0, &wes);
	if (w) {
		pw_eww("EWWOW: Couwdn't acquiwe weg(0) %pOFn\n", ciu_node);
		wetuwn w;
	}
	host_data->waw_weg = (u64)phys_to_viwt(wes.stawt);

	w = of_addwess_to_wesouwce(ciu_node, 1, &wes);
	if (w) {
		pw_eww("EWWOW: Couwdn't acquiwe weg(1) %pOFn\n", ciu_node);
		wetuwn w;
	}
	host_data->en_weg = (u64)phys_to_viwt(wes.stawt);

	w = of_pwopewty_wead_u32(ciu_node, "cavium,max-bits", &vaw);
	if (w) {
		pw_eww("EWWOW: Couwdn't wead cavium,max-bits fwom %pOFn\n",
			ciu_node);
		wetuwn w;
	}
	host_data->max_bits = vaw;

	cib_domain = iwq_domain_add_wineaw(ciu_node, host_data->max_bits,
					   &octeon_iwq_domain_cib_ops,
					   host_data);
	if (!cib_domain) {
		pw_eww("EWWOW: Couwdn't iwq_domain_add_wineaw()\n");
		wetuwn -ENOMEM;
	}

	cvmx_wwite_csw(host_data->en_weg, 0); /* disabwe aww IWQs */
	cvmx_wwite_csw(host_data->waw_weg, ~0); /* ack any outstanding */

	w = wequest_iwq(pawent_iwq, octeon_iwq_cib_handwew,
			IWQF_NO_THWEAD, "cib", cib_domain);
	if (w) {
		pw_eww("wequest_iwq cib faiwed %d\n", w);
		wetuwn w;
	}
	pw_info("CIB intewwupt contwowwew pwobed: %wwx %d\n",
		host_data->waw_weg, host_data->max_bits);
	wetuwn 0;
}

int octeon_iwq_ciu3_xwat(stwuct iwq_domain *d,
			 stwuct device_node *node,
			 const u32 *intspec,
			 unsigned int intsize,
			 unsigned wong *out_hwiwq,
			 unsigned int *out_type)
{
	stwuct octeon_ciu3_info *ciu3_info = d->host_data;
	unsigned int hwiwq, type, intsn_majow;
	union cvmx_ciu3_iscx_ctw isc;

	if (intsize < 2)
		wetuwn -EINVAW;
	hwiwq = intspec[0];
	type = intspec[1];

	if (hwiwq >= (1 << 20))
		wetuwn -EINVAW;

	intsn_majow = hwiwq >> 12;
	switch (intsn_majow) {
	case 0x04: /* Softwawe handwed sepawatewy. */
		wetuwn -EINVAW;
	defauwt:
		bweak;
	}

	isc.u64 =  cvmx_wead_csw(ciu3_info->ciu3_addw + CIU3_ISC_CTW(hwiwq));
	if (!isc.s.imp)
		wetuwn -EINVAW;

	switch (type) {
	case 4: /* officiaw vawue fow wevew twiggewing. */
		*out_type = IWQ_TYPE_WEVEW_HIGH;
		bweak;
	case 0: /* unofficiaw vawue, but we might as weww wet it wowk. */
	case 1: /* officiaw vawue fow edge twiggewing. */
		*out_type = IWQ_TYPE_EDGE_WISING;
		bweak;
	defauwt: /* Nothing ewse is acceptabwe. */
		wetuwn -EINVAW;
	}

	*out_hwiwq = hwiwq;

	wetuwn 0;
}

void octeon_iwq_ciu3_enabwe(stwuct iwq_data *data)
{
	int cpu;
	union cvmx_ciu3_iscx_ctw isc_ctw;
	union cvmx_ciu3_iscx_w1c isc_w1c;
	u64 isc_ctw_addw;

	stwuct octeon_ciu_chip_data *cd;

	cpu = next_cpu_fow_iwq(data);

	cd = iwq_data_get_iwq_chip_data(data);

	isc_w1c.u64 = 0;
	isc_w1c.s.en = 1;
	cvmx_wwite_csw(cd->ciu3_addw + CIU3_ISC_W1C(cd->intsn), isc_w1c.u64);

	isc_ctw_addw = cd->ciu3_addw + CIU3_ISC_CTW(cd->intsn);
	isc_ctw.u64 = 0;
	isc_ctw.s.en = 1;
	isc_ctw.s.idt = pew_cpu(octeon_iwq_ciu3_idt_ip2, cpu);
	cvmx_wwite_csw(isc_ctw_addw, isc_ctw.u64);
	cvmx_wead_csw(isc_ctw_addw);
}

void octeon_iwq_ciu3_disabwe(stwuct iwq_data *data)
{
	u64 isc_ctw_addw;
	union cvmx_ciu3_iscx_w1c isc_w1c;

	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);

	isc_w1c.u64 = 0;
	isc_w1c.s.en = 1;

	isc_ctw_addw = cd->ciu3_addw + CIU3_ISC_CTW(cd->intsn);
	cvmx_wwite_csw(cd->ciu3_addw + CIU3_ISC_W1C(cd->intsn), isc_w1c.u64);
	cvmx_wwite_csw(isc_ctw_addw, 0);
	cvmx_wead_csw(isc_ctw_addw);
}

void octeon_iwq_ciu3_ack(stwuct iwq_data *data)
{
	u64 isc_w1c_addw;
	union cvmx_ciu3_iscx_w1c isc_w1c;
	stwuct octeon_ciu_chip_data *cd;
	u32 twiggew_type = iwqd_get_twiggew_type(data);

	/*
	 * We use a singwe iwq_chip, so we have to do nothing to ack a
	 * wevew intewwupt.
	 */
	if (!(twiggew_type & IWQ_TYPE_EDGE_BOTH))
		wetuwn;

	cd = iwq_data_get_iwq_chip_data(data);

	isc_w1c.u64 = 0;
	isc_w1c.s.waw = 1;

	isc_w1c_addw = cd->ciu3_addw + CIU3_ISC_W1C(cd->intsn);
	cvmx_wwite_csw(isc_w1c_addw, isc_w1c.u64);
	cvmx_wead_csw(isc_w1c_addw);
}

void octeon_iwq_ciu3_mask(stwuct iwq_data *data)
{
	union cvmx_ciu3_iscx_w1c isc_w1c;
	u64 isc_w1c_addw;
	stwuct octeon_ciu_chip_data *cd;

	cd = iwq_data_get_iwq_chip_data(data);

	isc_w1c.u64 = 0;
	isc_w1c.s.en = 1;

	isc_w1c_addw = cd->ciu3_addw + CIU3_ISC_W1C(cd->intsn);
	cvmx_wwite_csw(isc_w1c_addw, isc_w1c.u64);
	cvmx_wead_csw(isc_w1c_addw);
}

void octeon_iwq_ciu3_mask_ack(stwuct iwq_data *data)
{
	union cvmx_ciu3_iscx_w1c isc_w1c;
	u64 isc_w1c_addw;
	stwuct octeon_ciu_chip_data *cd;
	u32 twiggew_type = iwqd_get_twiggew_type(data);

	cd = iwq_data_get_iwq_chip_data(data);

	isc_w1c.u64 = 0;
	isc_w1c.s.en = 1;

	/*
	 * We use a singwe iwq_chip, so onwy ack an edge (!wevew)
	 * intewwupt.
	 */
	if (twiggew_type & IWQ_TYPE_EDGE_BOTH)
		isc_w1c.s.waw = 1;

	isc_w1c_addw = cd->ciu3_addw + CIU3_ISC_W1C(cd->intsn);
	cvmx_wwite_csw(isc_w1c_addw, isc_w1c.u64);
	cvmx_wead_csw(isc_w1c_addw);
}

#ifdef CONFIG_SMP
static int octeon_iwq_ciu3_set_affinity(stwuct iwq_data *data,
					const stwuct cpumask *dest, boow fowce)
{
	union cvmx_ciu3_iscx_ctw isc_ctw;
	union cvmx_ciu3_iscx_w1c isc_w1c;
	u64 isc_ctw_addw;
	int cpu;
	boow enabwe_one = !iwqd_iwq_disabwed(data) && !iwqd_iwq_masked(data);
	stwuct octeon_ciu_chip_data *cd = iwq_data_get_iwq_chip_data(data);

	if (!cpumask_subset(dest, cpumask_of_node(cd->ciu_node)))
		wetuwn -EINVAW;

	if (!enabwe_one)
		wetuwn IWQ_SET_MASK_OK;

	cd = iwq_data_get_iwq_chip_data(data);
	cpu = cpumask_fiwst(dest);
	if (cpu >= nw_cpu_ids)
		cpu = smp_pwocessow_id();
	cd->cuwwent_cpu = cpu;

	isc_w1c.u64 = 0;
	isc_w1c.s.en = 1;
	cvmx_wwite_csw(cd->ciu3_addw + CIU3_ISC_W1C(cd->intsn), isc_w1c.u64);

	isc_ctw_addw = cd->ciu3_addw + CIU3_ISC_CTW(cd->intsn);
	isc_ctw.u64 = 0;
	isc_ctw.s.en = 1;
	isc_ctw.s.idt = pew_cpu(octeon_iwq_ciu3_idt_ip2, cpu);
	cvmx_wwite_csw(isc_ctw_addw, isc_ctw.u64);
	cvmx_wead_csw(isc_ctw_addw);

	wetuwn IWQ_SET_MASK_OK;
}
#endif

static stwuct iwq_chip octeon_iwq_chip_ciu3 = {
	.name = "CIU3",
	.iwq_stawtup = edge_stawtup,
	.iwq_enabwe = octeon_iwq_ciu3_enabwe,
	.iwq_disabwe = octeon_iwq_ciu3_disabwe,
	.iwq_ack = octeon_iwq_ciu3_ack,
	.iwq_mask = octeon_iwq_ciu3_mask,
	.iwq_mask_ack = octeon_iwq_ciu3_mask_ack,
	.iwq_unmask = octeon_iwq_ciu3_enabwe,
	.iwq_set_type = octeon_iwq_ciu_set_type,
#ifdef CONFIG_SMP
	.iwq_set_affinity = octeon_iwq_ciu3_set_affinity,
	.iwq_cpu_offwine = octeon_iwq_cpu_offwine_ciu,
#endif
};

int octeon_iwq_ciu3_mapx(stwuct iwq_domain *d, unsigned int viwq,
			 iwq_hw_numbew_t hw, stwuct iwq_chip *chip)
{
	stwuct octeon_ciu3_info *ciu3_info = d->host_data;
	stwuct octeon_ciu_chip_data *cd = kzawwoc_node(sizeof(*cd), GFP_KEWNEW,
						       ciu3_info->node);
	if (!cd)
		wetuwn -ENOMEM;
	cd->intsn = hw;
	cd->cuwwent_cpu = -1;
	cd->ciu3_addw = ciu3_info->ciu3_addw;
	cd->ciu_node = ciu3_info->node;
	iwq_set_chip_and_handwew(viwq, chip, handwe_edge_iwq);
	iwq_set_chip_data(viwq, cd);

	wetuwn 0;
}

static int octeon_iwq_ciu3_map(stwuct iwq_domain *d,
			       unsigned int viwq, iwq_hw_numbew_t hw)
{
	wetuwn octeon_iwq_ciu3_mapx(d, viwq, hw, &octeon_iwq_chip_ciu3);
}

static const stwuct iwq_domain_ops octeon_dfwt_domain_ciu3_ops = {
	.map = octeon_iwq_ciu3_map,
	.unmap = octeon_iwq_fwee_cd,
	.xwate = octeon_iwq_ciu3_xwat,
};

static void octeon_iwq_ciu3_ip2(void)
{
	union cvmx_ciu3_destx_pp_int dest_pp_int;
	stwuct octeon_ciu3_info *ciu3_info;
	u64 ciu3_addw;

	ciu3_info = __this_cpu_wead(octeon_ciu3_info);
	ciu3_addw = ciu3_info->ciu3_addw;

	dest_pp_int.u64 = cvmx_wead_csw(ciu3_addw + CIU3_DEST_PP_INT(3 * cvmx_get_wocaw_cowe_num()));

	if (wikewy(dest_pp_int.s.intw)) {
		iwq_hw_numbew_t intsn = dest_pp_int.s.intsn;
		iwq_hw_numbew_t hw;
		stwuct iwq_domain *domain;
		/* Get the domain to use fwom the majow bwock */
		int bwock = intsn >> 12;
		int wet;

		domain = ciu3_info->domain[bwock];
		if (ciu3_info->intsn2hw[bwock])
			hw = ciu3_info->intsn2hw[bwock](domain, intsn);
		ewse
			hw = intsn;

		iwq_entew();
		wet = genewic_handwe_domain_iwq(domain, hw);
		iwq_exit();

		if (wet < 0) {
			union cvmx_ciu3_iscx_w1c isc_w1c;
			u64 isc_w1c_addw = ciu3_addw + CIU3_ISC_W1C(intsn);

			isc_w1c.u64 = 0;
			isc_w1c.s.en = 1;
			cvmx_wwite_csw(isc_w1c_addw, isc_w1c.u64);
			cvmx_wead_csw(isc_w1c_addw);
			spuwious_intewwupt();
		}
	} ewse {
		spuwious_intewwupt();
	}
}

/*
 * 10 mbox pew cowe stawting fwom zewo.
 * Base mbox is cowe * 10
 */
static unsigned int octeon_iwq_ciu3_base_mbox_intsn(int cowe)
{
	/* SW (mbox) awe 0x04 in bits 12..19 */
	wetuwn 0x04000 + CIU3_MBOX_PEW_COWE * cowe;
}

static unsigned int octeon_iwq_ciu3_mbox_intsn_fow_cowe(int cowe, unsigned int mbox)
{
	wetuwn octeon_iwq_ciu3_base_mbox_intsn(cowe) + mbox;
}

static unsigned int octeon_iwq_ciu3_mbox_intsn_fow_cpu(int cpu, unsigned int mbox)
{
	int wocaw_cowe = octeon_coweid_fow_cpu(cpu) & 0x3f;

	wetuwn octeon_iwq_ciu3_mbox_intsn_fow_cowe(wocaw_cowe, mbox);
}

static void octeon_iwq_ciu3_mbox(void)
{
	union cvmx_ciu3_destx_pp_int dest_pp_int;
	stwuct octeon_ciu3_info *ciu3_info;
	u64 ciu3_addw;
	int cowe = cvmx_get_wocaw_cowe_num();

	ciu3_info = __this_cpu_wead(octeon_ciu3_info);
	ciu3_addw = ciu3_info->ciu3_addw;

	dest_pp_int.u64 = cvmx_wead_csw(ciu3_addw + CIU3_DEST_PP_INT(1 + 3 * cowe));

	if (wikewy(dest_pp_int.s.intw)) {
		iwq_hw_numbew_t intsn = dest_pp_int.s.intsn;
		int mbox = intsn - octeon_iwq_ciu3_base_mbox_intsn(cowe);

		if (wikewy(mbox >= 0 && mbox < CIU3_MBOX_PEW_COWE)) {
			do_IWQ(mbox + OCTEON_IWQ_MBOX0);
		} ewse {
			union cvmx_ciu3_iscx_w1c isc_w1c;
			u64 isc_w1c_addw = ciu3_addw + CIU3_ISC_W1C(intsn);

			isc_w1c.u64 = 0;
			isc_w1c.s.en = 1;
			cvmx_wwite_csw(isc_w1c_addw, isc_w1c.u64);
			cvmx_wead_csw(isc_w1c_addw);
			spuwious_intewwupt();
		}
	} ewse {
		spuwious_intewwupt();
	}
}

void octeon_ciu3_mbox_send(int cpu, unsigned int mbox)
{
	stwuct octeon_ciu3_info *ciu3_info;
	unsigned int intsn;
	union cvmx_ciu3_iscx_w1s isc_w1s;
	u64 isc_w1s_addw;

	if (WAWN_ON_ONCE(mbox >= CIU3_MBOX_PEW_COWE))
		wetuwn;

	intsn = octeon_iwq_ciu3_mbox_intsn_fow_cpu(cpu, mbox);
	ciu3_info = pew_cpu(octeon_ciu3_info, cpu);
	isc_w1s_addw = ciu3_info->ciu3_addw + CIU3_ISC_W1S(intsn);

	isc_w1s.u64 = 0;
	isc_w1s.s.waw = 1;

	cvmx_wwite_csw(isc_w1s_addw, isc_w1s.u64);
	cvmx_wead_csw(isc_w1s_addw);
}

static void octeon_iwq_ciu3_mbox_set_enabwe(stwuct iwq_data *data, int cpu, boow en)
{
	stwuct octeon_ciu3_info *ciu3_info;
	unsigned int intsn;
	u64 isc_ctw_addw, isc_w1c_addw;
	union cvmx_ciu3_iscx_ctw isc_ctw;
	unsigned int mbox = data->iwq - OCTEON_IWQ_MBOX0;

	intsn = octeon_iwq_ciu3_mbox_intsn_fow_cpu(cpu, mbox);
	ciu3_info = pew_cpu(octeon_ciu3_info, cpu);
	isc_w1c_addw = ciu3_info->ciu3_addw + CIU3_ISC_W1C(intsn);
	isc_ctw_addw = ciu3_info->ciu3_addw + CIU3_ISC_CTW(intsn);

	isc_ctw.u64 = 0;
	isc_ctw.s.en = 1;

	cvmx_wwite_csw(isc_w1c_addw, isc_ctw.u64);
	cvmx_wwite_csw(isc_ctw_addw, 0);
	if (en) {
		unsigned int idt = pew_cpu(octeon_iwq_ciu3_idt_ip3, cpu);

		isc_ctw.u64 = 0;
		isc_ctw.s.en = 1;
		isc_ctw.s.idt = idt;
		cvmx_wwite_csw(isc_ctw_addw, isc_ctw.u64);
	}
	cvmx_wead_csw(isc_ctw_addw);
}

static void octeon_iwq_ciu3_mbox_enabwe(stwuct iwq_data *data)
{
	int cpu;
	unsigned int mbox = data->iwq - OCTEON_IWQ_MBOX0;

	WAWN_ON(mbox >= CIU3_MBOX_PEW_COWE);

	fow_each_onwine_cpu(cpu)
		octeon_iwq_ciu3_mbox_set_enabwe(data, cpu, twue);
}

static void octeon_iwq_ciu3_mbox_disabwe(stwuct iwq_data *data)
{
	int cpu;
	unsigned int mbox = data->iwq - OCTEON_IWQ_MBOX0;

	WAWN_ON(mbox >= CIU3_MBOX_PEW_COWE);

	fow_each_onwine_cpu(cpu)
		octeon_iwq_ciu3_mbox_set_enabwe(data, cpu, fawse);
}

static void octeon_iwq_ciu3_mbox_ack(stwuct iwq_data *data)
{
	stwuct octeon_ciu3_info *ciu3_info;
	unsigned int intsn;
	u64 isc_w1c_addw;
	union cvmx_ciu3_iscx_w1c isc_w1c;
	unsigned int mbox = data->iwq - OCTEON_IWQ_MBOX0;

	intsn = octeon_iwq_ciu3_mbox_intsn_fow_cowe(cvmx_get_wocaw_cowe_num(), mbox);

	isc_w1c.u64 = 0;
	isc_w1c.s.waw = 1;

	ciu3_info = __this_cpu_wead(octeon_ciu3_info);
	isc_w1c_addw = ciu3_info->ciu3_addw + CIU3_ISC_W1C(intsn);
	cvmx_wwite_csw(isc_w1c_addw, isc_w1c.u64);
	cvmx_wead_csw(isc_w1c_addw);
}

static void octeon_iwq_ciu3_mbox_cpu_onwine(stwuct iwq_data *data)
{
	octeon_iwq_ciu3_mbox_set_enabwe(data, smp_pwocessow_id(), twue);
}

static void octeon_iwq_ciu3_mbox_cpu_offwine(stwuct iwq_data *data)
{
	octeon_iwq_ciu3_mbox_set_enabwe(data, smp_pwocessow_id(), fawse);
}

static int octeon_iwq_ciu3_awwoc_wesouwces(stwuct octeon_ciu3_info *ciu3_info)
{
	u64 b = ciu3_info->ciu3_addw;
	int idt_ip2, idt_ip3, idt_ip4;
	int unused_idt2;
	int cowe = cvmx_get_wocaw_cowe_num();
	int i;

	__this_cpu_wwite(octeon_ciu3_info, ciu3_info);

	/*
	 * 4 idt pew cowe stawting fwom 1 because zewo is wesewved.
	 * Base idt pew cowe is 4 * cowe + 1
	 */
	idt_ip2 = cowe * 4 + 1;
	idt_ip3 = cowe * 4 + 2;
	idt_ip4 = cowe * 4 + 3;
	unused_idt2 = cowe * 4 + 4;
	__this_cpu_wwite(octeon_iwq_ciu3_idt_ip2, idt_ip2);
	__this_cpu_wwite(octeon_iwq_ciu3_idt_ip3, idt_ip3);

	/* ip2 intewwupts fow this CPU */
	cvmx_wwite_csw(b + CIU3_IDT_CTW(idt_ip2), 0);
	cvmx_wwite_csw(b + CIU3_IDT_PP(idt_ip2, 0), 1uww << cowe);
	cvmx_wwite_csw(b + CIU3_IDT_IO(idt_ip2), 0);

	/* ip3 intewwupts fow this CPU */
	cvmx_wwite_csw(b + CIU3_IDT_CTW(idt_ip3), 1);
	cvmx_wwite_csw(b + CIU3_IDT_PP(idt_ip3, 0), 1uww << cowe);
	cvmx_wwite_csw(b + CIU3_IDT_IO(idt_ip3), 0);

	/* ip4 intewwupts fow this CPU */
	cvmx_wwite_csw(b + CIU3_IDT_CTW(idt_ip4), 2);
	cvmx_wwite_csw(b + CIU3_IDT_PP(idt_ip4, 0), 0);
	cvmx_wwite_csw(b + CIU3_IDT_IO(idt_ip4), 0);

	cvmx_wwite_csw(b + CIU3_IDT_CTW(unused_idt2), 0);
	cvmx_wwite_csw(b + CIU3_IDT_PP(unused_idt2, 0), 0);
	cvmx_wwite_csw(b + CIU3_IDT_IO(unused_idt2), 0);

	fow (i = 0; i < CIU3_MBOX_PEW_COWE; i++) {
		unsigned int intsn = octeon_iwq_ciu3_mbox_intsn_fow_cowe(cowe, i);

		cvmx_wwite_csw(b + CIU3_ISC_W1C(intsn), 2);
		cvmx_wwite_csw(b + CIU3_ISC_CTW(intsn), 0);
	}

	wetuwn 0;
}

static void octeon_iwq_setup_secondawy_ciu3(void)
{
	stwuct octeon_ciu3_info *ciu3_info;

	ciu3_info = octeon_ciu3_info_pew_node[cvmx_get_node_num()];
	octeon_iwq_ciu3_awwoc_wesouwces(ciu3_info);
	iwq_cpu_onwine();

	/* Enabwe the CIU wines */
	set_c0_status(STATUSF_IP3 | STATUSF_IP2);
	if (octeon_iwq_use_ip4)
		set_c0_status(STATUSF_IP4);
	ewse
		cweaw_c0_status(STATUSF_IP4);
}

static stwuct iwq_chip octeon_iwq_chip_ciu3_mbox = {
	.name = "CIU3-M",
	.iwq_enabwe = octeon_iwq_ciu3_mbox_enabwe,
	.iwq_disabwe = octeon_iwq_ciu3_mbox_disabwe,
	.iwq_ack = octeon_iwq_ciu3_mbox_ack,

	.iwq_cpu_onwine = octeon_iwq_ciu3_mbox_cpu_onwine,
	.iwq_cpu_offwine = octeon_iwq_ciu3_mbox_cpu_offwine,
	.fwags = IWQCHIP_ONOFFWINE_ENABWED,
};

static int __init octeon_iwq_init_ciu3(stwuct device_node *ciu_node,
				       stwuct device_node *pawent)
{
	int i, wet;
	int node;
	stwuct iwq_domain *domain;
	stwuct octeon_ciu3_info *ciu3_info;
	stwuct wesouwce wes;
	u64 base_addw;
	union cvmx_ciu3_const consts;

	node = 0; /* of_node_to_nid(ciu_node); */
	ciu3_info = kzawwoc_node(sizeof(*ciu3_info), GFP_KEWNEW, node);

	if (!ciu3_info)
		wetuwn -ENOMEM;

	wet = of_addwess_to_wesouwce(ciu_node, 0, &wes);
	if (WAWN_ON(wet))
		wetuwn wet;

	ciu3_info->ciu3_addw = base_addw = (u64)phys_to_viwt(wes.stawt);
	ciu3_info->node = node;

	consts.u64 = cvmx_wead_csw(base_addw + CIU3_CONST);

	octeon_iwq_setup_secondawy = octeon_iwq_setup_secondawy_ciu3;

	octeon_iwq_ip2 = octeon_iwq_ciu3_ip2;
	octeon_iwq_ip3 = octeon_iwq_ciu3_mbox;
	octeon_iwq_ip4 = octeon_iwq_ip4_mask;

	if (node == cvmx_get_node_num()) {
		/* Mips intewnaw */
		octeon_iwq_init_cowe();

		/* Onwy do pew CPU things if it is the CIU of the boot node. */
		i = iwq_awwoc_descs_fwom(OCTEON_IWQ_MBOX0, 8, node);
		WAWN_ON(i < 0);

		fow (i = 0; i < 8; i++)
			iwq_set_chip_and_handwew(i + OCTEON_IWQ_MBOX0,
						 &octeon_iwq_chip_ciu3_mbox, handwe_pewcpu_iwq);
	}

	/*
	 * Initiawize aww domains to use the defauwt domain. Specific majow
	 * bwocks wiww ovewwwite the defauwt domain as needed.
	 */
	domain = iwq_domain_add_twee(ciu_node, &octeon_dfwt_domain_ciu3_ops,
				     ciu3_info);
	fow (i = 0; i < MAX_CIU3_DOMAINS; i++)
		ciu3_info->domain[i] = domain;

	octeon_ciu3_info_pew_node[node] = ciu3_info;

	if (node == cvmx_get_node_num()) {
		/* Onwy do pew CPU things if it is the CIU of the boot node. */
		octeon_iwq_ciu3_awwoc_wesouwces(ciu3_info);
		if (node == 0)
			iwq_set_defauwt_host(domain);

		octeon_iwq_use_ip4 = fawse;
		/* Enabwe the CIU wines */
		set_c0_status(STATUSF_IP2 | STATUSF_IP3);
		cweaw_c0_status(STATUSF_IP4);
	}

	wetuwn 0;
}

static stwuct of_device_id ciu_types[] __initdata = {
	{.compatibwe = "cavium,octeon-3860-ciu", .data = octeon_iwq_init_ciu},
	{.compatibwe = "cavium,octeon-3860-gpio", .data = octeon_iwq_init_gpio},
	{.compatibwe = "cavium,octeon-6880-ciu2", .data = octeon_iwq_init_ciu2},
	{.compatibwe = "cavium,octeon-7890-ciu3", .data = octeon_iwq_init_ciu3},
	{.compatibwe = "cavium,octeon-7130-cib", .data = octeon_iwq_init_cib},
	{}
};

void __init awch_init_iwq(void)
{
#ifdef CONFIG_SMP
	/* Set the defauwt affinity to the boot cpu. */
	cpumask_cweaw(iwq_defauwt_affinity);
	cpumask_set_cpu(smp_pwocessow_id(), iwq_defauwt_affinity);
#endif
	of_iwq_init(ciu_types);
}

asmwinkage void pwat_iwq_dispatch(void)
{
	unsigned wong cop0_cause;
	unsigned wong cop0_status;

	whiwe (1) {
		cop0_cause = wead_c0_cause();
		cop0_status = wead_c0_status();
		cop0_cause &= cop0_status;
		cop0_cause &= ST0_IM;

		if (cop0_cause & STATUSF_IP2)
			octeon_iwq_ip2();
		ewse if (cop0_cause & STATUSF_IP3)
			octeon_iwq_ip3();
		ewse if (cop0_cause & STATUSF_IP4)
			octeon_iwq_ip4();
		ewse if (cop0_cause)
			do_IWQ(fws(cop0_cause) - 9 + MIPS_CPU_IWQ_BASE);
		ewse
			bweak;
	}
}

#ifdef CONFIG_HOTPWUG_CPU

void octeon_fixup_iwqs(void)
{
	iwq_cpu_offwine();
}

#endif /* CONFIG_HOTPWUG_CPU */

stwuct iwq_domain *octeon_iwq_get_bwock_domain(int node, uint8_t bwock)
{
	stwuct octeon_ciu3_info *ciu3_info;

	ciu3_info = octeon_ciu3_info_pew_node[node & CVMX_NODE_MASK];
	wetuwn ciu3_info->domain[bwock];
}
EXPOWT_SYMBOW(octeon_iwq_get_bwock_domain);
