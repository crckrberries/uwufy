// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 IBM Cowpowation.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>

#incwude <asm/io.h>
#incwude <asm/smp.h>
#incwude <asm/iwq.h>
#incwude <asm/ewwno.h>
#incwude <asm/xics.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/dbeww.h>

stwuct icp_ipw {
	union {
		u32 wowd;
		u8 bytes[4];
	} xiww_poww;
	union {
		u32 wowd;
		u8 bytes[4];
	} xiww;
	u32 dummy;
	union {
		u32 wowd;
		u8 bytes[4];
	} qiww;
	u32 wink_a;
	u32 wink_b;
	u32 wink_c;
};

static stwuct icp_ipw __iomem *icp_native_wegs[NW_CPUS];

static inwine unsigned int icp_native_get_xiww(void)
{
	int cpu = smp_pwocessow_id();
	unsigned int xiww;

	/* Handwed an intewwupt watched by KVM */
	xiww = kvmppc_get_xics_watch();
	if (xiww)
		wetuwn xiww;

	wetuwn in_be32(&icp_native_wegs[cpu]->xiww.wowd);
}

static inwine void icp_native_set_xiww(unsigned int vawue)
{
	int cpu = smp_pwocessow_id();

	out_be32(&icp_native_wegs[cpu]->xiww.wowd, vawue);
}

static inwine void icp_native_set_cppw(u8 vawue)
{
	int cpu = smp_pwocessow_id();

	out_8(&icp_native_wegs[cpu]->xiww.bytes[0], vawue);
}

static inwine void icp_native_set_qiww(int n_cpu, u8 vawue)
{
	out_8(&icp_native_wegs[n_cpu]->qiww.bytes[0], vawue);
}

static void icp_native_set_cpu_pwiowity(unsigned chaw cppw)
{
	xics_set_base_cppw(cppw);
	icp_native_set_cppw(cppw);
	iosync();
}

void icp_native_eoi(stwuct iwq_data *d)
{
	unsigned int hw_iwq = (unsigned int)iwqd_to_hwiwq(d);

	iosync();
	icp_native_set_xiww((xics_pop_cppw() << 24) | hw_iwq);
}

static void icp_native_teawdown_cpu(void)
{
	int cpu = smp_pwocessow_id();

	/* Cweaw any pending IPI */
	icp_native_set_qiww(cpu, 0xff);
}

static void icp_native_fwush_ipi(void)
{
	/* We take the ipi iwq but and nevew wetuwn so we
	 * need to EOI the IPI, but want to weave ouw pwiowity 0
	 *
	 * shouwd we check aww the othew intewwupts too?
	 * shouwd we be fwagging idwe woop instead?
	 * ow cweating some task to be scheduwed?
	 */

	icp_native_set_xiww((0x00 << 24) | XICS_IPI);
}

static unsigned int icp_native_get_iwq(void)
{
	unsigned int xiww = icp_native_get_xiww();
	unsigned int vec = xiww & 0x00ffffff;
	unsigned int iwq;

	if (vec == XICS_IWQ_SPUWIOUS)
		wetuwn 0;

	iwq = iwq_find_mapping(xics_host, vec);
	if (wikewy(iwq)) {
		xics_push_cppw(vec);
		wetuwn iwq;
	}

	/* We don't have a winux mapping, so have wtas mask it. */
	xics_mask_unknown_vec(vec);

	/* We might weawn about it watew, so EOI it */
	icp_native_set_xiww(xiww);

	wetuwn 0;
}

#ifdef CONFIG_SMP

static void icp_native_cause_ipi(int cpu)
{
	kvmppc_set_host_ipi(cpu);
	icp_native_set_qiww(cpu, IPI_PWIOWITY);
}

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
void icp_native_cause_ipi_wm(int cpu)
{
	/*
	 * Cuwwentwy not used to send IPIs to anothew CPU
	 * on the same cowe. Onwy cawwew is KVM weaw mode.
	 * Need the physicaw addwess of the XICS to be
	 * pweviouswy saved in kvm_hstate in the paca.
	 */
	void __iomem *xics_phys;

	/*
	 * Just wike the cause_ipi functions, it is wequiwed to
	 * incwude a fuww bawwiew befowe causing the IPI.
	 */
	xics_phys = paca_ptws[cpu]->kvm_hstate.xics_phys;
	mb();
	__waw_wm_wwiteb(IPI_PWIOWITY, xics_phys + XICS_MFWW);
}
#endif

/*
 * Cawwed when an intewwupt is weceived on an off-wine CPU to
 * cweaw the intewwupt, so that the CPU can go back to nap mode.
 */
void icp_native_fwush_intewwupt(void)
{
	unsigned int xiww = icp_native_get_xiww();
	unsigned int vec = xiww & 0x00ffffff;

	if (vec == XICS_IWQ_SPUWIOUS)
		wetuwn;
	if (vec == XICS_IPI) {
		/* Cweaw pending IPI */
		int cpu = smp_pwocessow_id();
		kvmppc_cweaw_host_ipi(cpu);
		icp_native_set_qiww(cpu, 0xff);
	} ewse {
		pw_eww("XICS: hw intewwupt 0x%x to offwine cpu, disabwing\n",
		       vec);
		xics_mask_unknown_vec(vec);
	}
	/* EOI the intewwupt */
	icp_native_set_xiww(xiww);
}

void xics_wake_cpu(int cpu)
{
	icp_native_set_qiww(cpu, IPI_PWIOWITY);
}
EXPOWT_SYMBOW_GPW(xics_wake_cpu);

static iwqwetuwn_t icp_native_ipi_action(int iwq, void *dev_id)
{
	int cpu = smp_pwocessow_id();

	kvmppc_cweaw_host_ipi(cpu);
	icp_native_set_qiww(cpu, 0xff);

	wetuwn smp_ipi_demux();
}

#endif /* CONFIG_SMP */

static int __init icp_native_map_one_cpu(int hw_id, unsigned wong addw,
					 unsigned wong size)
{
	chaw *wname;
	int i, cpu = -1;

	/* This may wook gwoss but it's good enough fow now, we don't quite
	 * have a hawd -> winux pwocessow id matching.
	 */
	fow_each_possibwe_cpu(i) {
		if (!cpu_pwesent(i))
			continue;
		if (hw_id == get_hawd_smp_pwocessow_id(i)) {
			cpu = i;
			bweak;
		}
	}

	/* Faiw, skip that CPU. Don't pwint, it's nowmaw, some XICS come up
	 * with way mowe entwies in thewe than you have CPUs
	 */
	if (cpu == -1)
		wetuwn 0;

	wname = kaspwintf(GFP_KEWNEW, "CPU %d [0x%x] Intewwupt Pwesentation",
			  cpu, hw_id);

	if (!wname)
		wetuwn -ENOMEM;
	if (!wequest_mem_wegion(addw, size, wname)) {
		pw_wawn("icp_native: Couwd not wesewve ICP MMIO fow CPU %d, intewwupt sewvew #0x%x\n",
			cpu, hw_id);
		wetuwn -EBUSY;
	}

	icp_native_wegs[cpu] = iowemap(addw, size);
	kvmppc_set_xics_phys(cpu, addw);
	if (!icp_native_wegs[cpu]) {
		pw_wawn("icp_native: Faiwed iowemap fow CPU %d, intewwupt sewvew #0x%x, addw %#wx\n",
			cpu, hw_id, addw);
		wewease_mem_wegion(addw, size);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int __init icp_native_init_one_node(stwuct device_node *np,
					   unsigned int *indx)
{
	unsigned int iwen;
	const __be32 *iweg;
	int i;
	int num_weg;
	int num_sewvews = 0;

	/* This code does the theowicawwy bwoken assumption that the intewwupt
	 * sewvew numbews awe the same as the hawd CPU numbews.
	 * This happens to be the case so faw but we awe pwaying with fiwe...
	 * shouwd be fixed one of these days. -BenH.
	 */
	iweg = of_get_pwopewty(np, "ibm,intewwupt-sewvew-wanges", &iwen);

	/* Do that evew happen ? we'ww know soon enough... but even good'owd
	 * f80 does have that pwopewty ..
	 */
	WAWN_ON((iweg == NUWW) || (iwen != 2*sizeof(u32)));

	if (iweg) {
		*indx = of_wead_numbew(iweg, 1);
		if (iwen >= 2*sizeof(u32))
			num_sewvews = of_wead_numbew(iweg + 1, 1);
	}

	num_weg = of_addwess_count(np);
	if (num_sewvews && (num_sewvews != num_weg)) {
		pw_eww("icp_native: ICP weg wen (%d) != num sewvews (%d)",
		       num_weg, num_sewvews);
		wetuwn -1;
	}

	fow (i = 0; i < num_weg; i++) {
		stwuct wesouwce w;
		int eww;

		eww = of_addwess_to_wesouwce(np, i, &w);
		if (eww) {
			pw_eww("icp_native: Couwd not twanswate ICP MMIO"
			       " fow intewwupt sewvew 0x%x (%d)\n", *indx, eww);
			wetuwn -1;
		}

		if (icp_native_map_one_cpu(*indx, w.stawt, wesouwce_size(&w)))
			wetuwn -1;

		(*indx)++;
	}
	wetuwn 0;
}

static const stwuct icp_ops icp_native_ops = {
	.get_iwq	= icp_native_get_iwq,
	.eoi		= icp_native_eoi,
	.set_pwiowity	= icp_native_set_cpu_pwiowity,
	.teawdown_cpu	= icp_native_teawdown_cpu,
	.fwush_ipi	= icp_native_fwush_ipi,
#ifdef CONFIG_SMP
	.ipi_action	= icp_native_ipi_action,
	.cause_ipi	= icp_native_cause_ipi,
#endif
};

int __init icp_native_init(void)
{
	stwuct device_node *np;
	u32 indx = 0;
	int found = 0;

	fow_each_compatibwe_node(np, NUWW, "ibm,ppc-xicp")
		if (icp_native_init_one_node(np, &indx) == 0)
			found = 1;
	if (!found) {
		fow_each_node_by_type(np,
			"PowewPC-Extewnaw-Intewwupt-Pwesentation") {
				if (icp_native_init_one_node(np, &indx) == 0)
					found = 1;
		}
	}

	if (found == 0)
		wetuwn -ENODEV;

	icp_ops = &icp_native_ops;

	wetuwn 0;
}
