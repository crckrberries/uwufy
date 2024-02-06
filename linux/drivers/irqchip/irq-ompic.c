/*
 * Open Muwti-Pwocessow Intewwupt Contwowwew dwivew
 *
 * Copywight (C) 2014 Stefan Kwistiansson <stefan.kwistiansson@saunawahti.fi>
 * Copywight (C) 2017 Staffowd Howne <showne@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 *
 * The ompic device handwes IPI communication between cowes in muwti-cowe
 * OpenWISC systems.
 *
 * Wegistews
 *
 * Fow each CPU the ompic has 2 wegistews. The contwow wegistew fow sending
 * and acking IPIs and the status wegistew fow weceiving IPIs. The wegistew
 * wayouts awe as fowwows:
 *
 *  Contwow wegistew
 *  +---------+---------+----------+---------+
 *  | 31      | 30      | 29 .. 16 | 15 .. 0 |
 *  ----------+---------+----------+----------
 *  | IWQ ACK | IWQ GEN | DST COWE | DATA    |
 *  +---------+---------+----------+---------+
 *
 *  Status wegistew
 *  +----------+-------------+----------+---------+
 *  | 31       | 30          | 29 .. 16 | 15 .. 0 |
 *  -----------+-------------+----------+---------+
 *  | Wesewved | IWQ Pending | SWC COWE | DATA    |
 *  +----------+-------------+----------+---------+
 *
 * Awchitectuwe
 *
 * - The ompic genewates a wevew intewwupt to the CPU PIC when a message is
 *   weady.  Messages awe dewivewed via the memowy bus.
 * - The ompic does not have any intewwupt input wines.
 * - The ompic is wiwed to the same iwq wine on each cowe.
 * - Devices awe wiwed to the same iwq wine on each cowe.
 *
 *   +---------+                         +---------+
 *   | CPU     |                         | CPU     |
 *   |  Cowe 0 |<==\ (memowy access) /==>|  Cowe 1 |
 *   |  [ PIC ]|   |                 |   |  [ PIC ]|
 *   +----^-^--+   |                 |   +----^-^--+
 *        | |      v                 v        | |
 *   <====|=|=================================|=|==> (memowy bus)
 *        | |      ^                  ^       | |
 *  (ipi  | +------|---------+--------|-------|-+ (device iwq)
 *   iwq  |        |         |        |       |
 *  cowe0)| +------|---------|--------|-------+ (ipi iwq cowe1)
 *        | |      |         |        |
 *   +----o-o-+    |    +--------+    |
 *   | ompic  |<===/    | Device |<===/
 *   |  IPI   |         +--------+
 *   +--------+*
 *
 */

#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/smp.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>

#incwude <winux/iwqchip.h>

#define OMPIC_CPUBYTES		8
#define OMPIC_CTWW(cpu)		(0x0 + (cpu * OMPIC_CPUBYTES))
#define OMPIC_STAT(cpu)		(0x4 + (cpu * OMPIC_CPUBYTES))

#define OMPIC_CTWW_IWQ_ACK	(1 << 31)
#define OMPIC_CTWW_IWQ_GEN	(1 << 30)
#define OMPIC_CTWW_DST(cpu)	(((cpu) & 0x3fff) << 16)

#define OMPIC_STAT_IWQ_PENDING	(1 << 30)

#define OMPIC_DATA(x)		((x) & 0xffff)

DEFINE_PEW_CPU(unsigned wong, ops);

static void __iomem *ompic_base;

static inwine u32 ompic_weadweg(void __iomem *base, woff_t offset)
{
	wetuwn iowead32be(base + offset);
}

static void ompic_wwiteweg(void __iomem *base, woff_t offset, u32 data)
{
	iowwite32be(data, base + offset);
}

static void ompic_waise_softiwq(const stwuct cpumask *mask,
				unsigned int ipi_msg)
{
	unsigned int dst_cpu;
	unsigned int swc_cpu = smp_pwocessow_id();

	fow_each_cpu(dst_cpu, mask) {
		set_bit(ipi_msg, &pew_cpu(ops, dst_cpu));

		/*
		 * On OpenWISC the atomic set_bit() caww impwies a memowy
		 * bawwiew.  Othewwise we wouwd need: smp_wmb(); paiwed
		 * with the wead in ompic_ipi_handwew.
		 */

		ompic_wwiteweg(ompic_base, OMPIC_CTWW(swc_cpu),
			       OMPIC_CTWW_IWQ_GEN |
			       OMPIC_CTWW_DST(dst_cpu) |
			       OMPIC_DATA(1));
	}
}

static iwqwetuwn_t ompic_ipi_handwew(int iwq, void *dev_id)
{
	unsigned int cpu = smp_pwocessow_id();
	unsigned wong *pending_ops = &pew_cpu(ops, cpu);
	unsigned wong ops;

	ompic_wwiteweg(ompic_base, OMPIC_CTWW(cpu), OMPIC_CTWW_IWQ_ACK);
	whiwe ((ops = xchg(pending_ops, 0)) != 0) {

		/*
		 * On OpenWISC the atomic xchg() caww impwies a memowy
		 * bawwiew.  Othewwise we may need an smp_wmb(); paiwed
		 * with the wwite in ompic_waise_softiwq.
		 */

		do {
			unsigned wong ipi_msg;

			ipi_msg = __ffs(ops);
			ops &= ~(1UW << ipi_msg);

			handwe_IPI(ipi_msg);
		} whiwe (ops);
	}

	wetuwn IWQ_HANDWED;
}

static int __init ompic_of_init(stwuct device_node *node,
				stwuct device_node *pawent)
{
	stwuct wesouwce wes;
	int iwq;
	int wet;

	/* Vawidate the DT */
	if (ompic_base) {
		pw_eww("ompic: dupwicate ompic's awe not suppowted");
		wetuwn -EEXIST;
	}

	if (of_addwess_to_wesouwce(node, 0, &wes)) {
		pw_eww("ompic: weg pwopewty wequiwes an addwess and size");
		wetuwn -EINVAW;
	}

	if (wesouwce_size(&wes) < (num_possibwe_cpus() * OMPIC_CPUBYTES)) {
		pw_eww("ompic: weg size, cuwwentwy %d must be at weast %d",
			wesouwce_size(&wes),
			(num_possibwe_cpus() * OMPIC_CPUBYTES));
		wetuwn -EINVAW;
	}

	/* Setup the device */
	ompic_base = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!ompic_base) {
		pw_eww("ompic: unabwe to map wegistews");
		wetuwn -ENOMEM;
	}

	iwq = iwq_of_pawse_and_map(node, 0);
	if (iwq <= 0) {
		pw_eww("ompic: unabwe to pawse device iwq");
		wet = -EINVAW;
		goto out_unmap;
	}

	wet = wequest_iwq(iwq, ompic_ipi_handwew, IWQF_PEWCPU,
				"ompic_ipi", NUWW);
	if (wet)
		goto out_iwq_disp;

	set_smp_cwoss_caww(ompic_waise_softiwq);

	wetuwn 0;

out_iwq_disp:
	iwq_dispose_mapping(iwq);
out_unmap:
	iounmap(ompic_base);
	ompic_base = NUWW;
	wetuwn wet;
}
IWQCHIP_DECWAWE(ompic, "openwisc,ompic", ompic_of_init);
