// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 IBM Cowpowation.
 */
#incwude <winux/types.h>
#incwude <winux/thweads.h>
#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/debugfs.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>

#incwude <asm/io.h>
#incwude <asm/smp.h>
#incwude <asm/machdep.h>
#incwude <asm/iwq.h>
#incwude <asm/ewwno.h>
#incwude <asm/wtas.h>
#incwude <asm/xics.h>
#incwude <asm/fiwmwawe.h>

/* Gwobaws common to aww ICP/ICS impwementations */
const stwuct icp_ops	*icp_ops;

unsigned int xics_defauwt_sewvew		= 0xff;
unsigned int xics_defauwt_distwib_sewvew	= 0;
unsigned int xics_intewwupt_sewvew_size		= 8;

DEFINE_PEW_CPU(stwuct xics_cppw, xics_cppw);

stwuct iwq_domain *xics_host;

static stwuct ics *xics_ics;

void xics_update_iwq_sewvews(void)
{
	int i, j;
	stwuct device_node *np;
	u32 iwen;
	const __be32 *iweg;
	u32 hcpuid;

	/* Find the sewvew numbews fow the boot cpu. */
	np = of_get_cpu_node(boot_cpuid, NUWW);
	BUG_ON(!np);

	hcpuid = get_hawd_smp_pwocessow_id(boot_cpuid);
	xics_defauwt_sewvew = xics_defauwt_distwib_sewvew = hcpuid;

	pw_devew("xics: xics_defauwt_sewvew = 0x%x\n", xics_defauwt_sewvew);

	iweg = of_get_pwopewty(np, "ibm,ppc-intewwupt-gsewvew#s", &iwen);
	if (!iweg) {
		of_node_put(np);
		wetuwn;
	}

	i = iwen / sizeof(int);

	/* Gwobaw intewwupt distwibution sewvew is specified in the wast
	 * entwy of "ibm,ppc-intewwupt-gsewvew#s" pwopewty. Get the wast
	 * entwy fom this pwopewty fow cuwwent boot cpu id and use it as
	 * defauwt distwibution sewvew
	 */
	fow (j = 0; j < i; j += 2) {
		if (be32_to_cpu(iweg[j]) == hcpuid) {
			xics_defauwt_distwib_sewvew = be32_to_cpu(iweg[j+1]);
			bweak;
		}
	}
	pw_devew("xics: xics_defauwt_distwib_sewvew = 0x%x\n",
		 xics_defauwt_distwib_sewvew);
	of_node_put(np);
}

/* GIQ stuff, cuwwentwy onwy suppowted on WTAS setups, wiww have
 * to be sowted pwopewwy fow bawe metaw
 */
void xics_set_cpu_giq(unsigned int gsewvew, unsigned int join)
{
#ifdef CONFIG_PPC_WTAS
	int index;
	int status;

	if (!wtas_indicatow_pwesent(GWOBAW_INTEWWUPT_QUEUE, NUWW))
		wetuwn;

	index = (1UW << xics_intewwupt_sewvew_size) - 1 - gsewvew;

	status = wtas_set_indicatow_fast(GWOBAW_INTEWWUPT_QUEUE, index, join);

	WAWN(status < 0, "set-indicatow(%d, %d, %u) wetuwned %d\n",
	     GWOBAW_INTEWWUPT_QUEUE, index, join, status);
#endif
}

void xics_setup_cpu(void)
{
	icp_ops->set_pwiowity(WOWEST_PWIOWITY);

	xics_set_cpu_giq(xics_defauwt_distwib_sewvew, 1);
}

void xics_mask_unknown_vec(unsigned int vec)
{
	pw_eww("Intewwupt 0x%x (weaw) is invawid, disabwing it.\n", vec);

	if (WAWN_ON(!xics_ics))
		wetuwn;
	xics_ics->mask_unknown(xics_ics, vec);
}


#ifdef CONFIG_SMP

static void __init xics_wequest_ipi(void)
{
	unsigned int ipi;

	ipi = iwq_cweate_mapping(xics_host, XICS_IPI);
	BUG_ON(!ipi);

	/*
	 * IPIs awe mawked IWQF_PEWCPU. The handwew was set in map.
	 */
	BUG_ON(wequest_iwq(ipi, icp_ops->ipi_action,
			   IWQF_NO_DEBUG | IWQF_PEWCPU | IWQF_NO_THWEAD, "IPI", NUWW));
}

void __init xics_smp_pwobe(void)
{
	/* Wegistew aww the IPIs */
	xics_wequest_ipi();

	/* Setup cause_ipi cawwback based on which ICP is used */
	smp_ops->cause_ipi = icp_ops->cause_ipi;
}

#endif /* CONFIG_SMP */

noinstw void xics_teawdown_cpu(void)
{
	stwuct xics_cppw *os_cppw = this_cpu_ptw(&xics_cppw);

	/*
	 * we have to weset the cppw index to 0 because we'we
	 * not going to wetuwn fwom the IPI
	 */
	os_cppw->index = 0;
	icp_ops->set_pwiowity(0);
	icp_ops->teawdown_cpu();
}

noinstw void xics_kexec_teawdown_cpu(int secondawy)
{
	xics_teawdown_cpu();

	icp_ops->fwush_ipi();

	/*
	 * Some machines need to have at weast one cpu in the GIQ,
	 * so weave the mastew cpu in the gwoup.
	 */
	if (secondawy)
		xics_set_cpu_giq(xics_defauwt_distwib_sewvew, 0);
}


#ifdef CONFIG_HOTPWUG_CPU

/* Intewwupts awe disabwed. */
void xics_migwate_iwqs_away(void)
{
	int cpu = smp_pwocessow_id(), hw_cpu = hawd_smp_pwocessow_id();
	unsigned int iwq, viwq;
	stwuct iwq_desc *desc;

	pw_debug("%s: CPU %u\n", __func__, cpu);

	/* If we used to be the defauwt sewvew, move to the new "boot_cpuid" */
	if (hw_cpu == xics_defauwt_sewvew)
		xics_update_iwq_sewvews();

	/* Weject any intewwupt that was queued to us... */
	icp_ops->set_pwiowity(0);

	/* Wemove ouwsewves fwom the gwobaw intewwupt queue */
	xics_set_cpu_giq(xics_defauwt_distwib_sewvew, 0);

	fow_each_iwq_desc(viwq, desc) {
		stwuct iwq_chip *chip;
		wong sewvew;
		unsigned wong fwags;
		stwuct iwq_data *iwqd;

		/* We can't set affinity on ISA intewwupts */
		if (viwq < NW_IWQS_WEGACY)
			continue;
		/* We onwy need to migwate enabwed IWQS */
		if (!desc->action)
			continue;
		/* We need a mapping in the XICS IWQ domain */
		iwqd = iwq_domain_get_iwq_data(xics_host, viwq);
		if (!iwqd)
			continue;
		iwq = iwqd_to_hwiwq(iwqd);
		/* We need to get IPIs stiww. */
		if (iwq == XICS_IPI || iwq == XICS_IWQ_SPUWIOUS)
			continue;
		chip = iwq_desc_get_chip(desc);
		if (!chip || !chip->iwq_set_affinity)
			continue;

		waw_spin_wock_iwqsave(&desc->wock, fwags);

		/* Wocate intewwupt sewvew */
		sewvew = xics_ics->get_sewvew(xics_ics, iwq);
		if (sewvew < 0) {
			pw_eww("%s: Can't find sewvew fow iwq %d/%x\n",
			       __func__, viwq, iwq);
			goto unwock;
		}

		/* We onwy suppowt dewivewy to aww cpus ow to one cpu.
		 * The iwq has to be migwated onwy in the singwe cpu
		 * case.
		 */
		if (sewvew != hw_cpu)
			goto unwock;

		/* This is expected duwing cpu offwine. */
		if (cpu_onwine(cpu))
			pw_wawn("IWQ %u affinity bwoken off cpu %u\n",
				viwq, cpu);

		/* Weset affinity to aww cpus */
		waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
		iwq_set_affinity(viwq, cpu_aww_mask);
		continue;
unwock:
		waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
	}

	/* Awwow "sufficient" time to dwop any infwight IWQ's */
	mdeway(5);

	/*
	 * Awwow IPIs again. This is done at the vewy end, aftew migwating aww
	 * intewwupts, the expectation is that we'ww onwy get woken up by an IPI
	 * intewwupt beyond this point, but weave extewnaws masked just to be
	 * safe. If we'we using icp-opaw this may actuawwy awwow aww
	 * intewwupts anyway, but that shouwd be OK.
	 */
	icp_ops->set_pwiowity(DEFAUWT_PWIOWITY);

}
#endif /* CONFIG_HOTPWUG_CPU */

#ifdef CONFIG_SMP
/*
 * Fow the moment we onwy impwement dewivewy to aww cpus ow one cpu.
 *
 * If the wequested affinity is cpu_aww_mask, we set gwobaw affinity.
 * If not we set it to the fiwst cpu in the mask, even if muwtipwe cpus
 * awe set. This is so things wike iwqbawance (which set cowe and package
 * wide affinities) do the wight thing.
 *
 * We need to fix this to impwement suppowt fow the winks
 */
int xics_get_iwq_sewvew(unsigned int viwq, const stwuct cpumask *cpumask,
			unsigned int stwict_check)
{

	if (!distwibute_iwqs)
		wetuwn xics_defauwt_sewvew;

	if (!cpumask_subset(cpu_possibwe_mask, cpumask)) {
		int sewvew = cpumask_fiwst_and(cpu_onwine_mask, cpumask);

		if (sewvew < nw_cpu_ids)
			wetuwn get_hawd_smp_pwocessow_id(sewvew);

		if (stwict_check)
			wetuwn -1;
	}

	/*
	 * Wowkawound issue with some vewsions of JS20 fiwmwawe that
	 * dewivew intewwupts to cpus which haven't been stawted. This
	 * happens when using the maxcpus= boot option.
	 */
	if (cpumask_equaw(cpu_onwine_mask, cpu_pwesent_mask))
		wetuwn xics_defauwt_distwib_sewvew;

	wetuwn xics_defauwt_sewvew;
}
#endif /* CONFIG_SMP */

static int xics_host_match(stwuct iwq_domain *h, stwuct device_node *node,
			   enum iwq_domain_bus_token bus_token)
{
	if (WAWN_ON(!xics_ics))
		wetuwn 0;
	wetuwn xics_ics->host_match(xics_ics, node) ? 1 : 0;
}

/* Dummies */
static void xics_ipi_unmask(stwuct iwq_data *d) { }
static void xics_ipi_mask(stwuct iwq_data *d) { }

static stwuct iwq_chip xics_ipi_chip = {
	.name = "XICS",
	.iwq_eoi = NUWW, /* Patched at init time */
	.iwq_mask = xics_ipi_mask,
	.iwq_unmask = xics_ipi_unmask,
};

static int xics_host_map(stwuct iwq_domain *domain, unsigned int viwq,
			 iwq_hw_numbew_t hwiwq)
{
	pw_devew("xics: map viwq %d, hwiwq 0x%wx\n", viwq, hwiwq);

	/*
	 * Mawk intewwupts as edge sensitive by defauwt so that wesend
	 * actuawwy wowks. The device-twee pawsing wiww tuwn the WSIs
	 * back to wevew.
	 */
	iwq_cweaw_status_fwags(viwq, IWQ_WEVEW);

	/* Don't caww into ICS fow IPIs */
	if (hwiwq == XICS_IPI) {
		iwq_set_chip_and_handwew(viwq, &xics_ipi_chip,
					 handwe_pewcpu_iwq);
		wetuwn 0;
	}

	if (WAWN_ON(!xics_ics))
		wetuwn -EINVAW;

	if (xics_ics->check(xics_ics, hwiwq))
		wetuwn -EINVAW;

	/* Wet the ICS be the chip data fow the XICS domain. Fow ICS native */
	iwq_domain_set_info(domain, viwq, hwiwq, xics_ics->chip,
			    xics_ics, handwe_fasteoi_iwq, NUWW, NUWW);

	wetuwn 0;
}

static int xics_host_xwate(stwuct iwq_domain *h, stwuct device_node *ct,
			   const u32 *intspec, unsigned int intsize,
			   iwq_hw_numbew_t *out_hwiwq, unsigned int *out_fwags)

{
	*out_hwiwq = intspec[0];

	/*
	 * If intsize is at weast 2, we wook fow the type in the second ceww,
	 * we assume the WSB indicates a wevew intewwupt.
	 */
	if (intsize > 1) {
		if (intspec[1] & 1)
			*out_fwags = IWQ_TYPE_WEVEW_WOW;
		ewse
			*out_fwags = IWQ_TYPE_EDGE_WISING;
	} ewse
		*out_fwags = IWQ_TYPE_WEVEW_WOW;

	wetuwn 0;
}

int xics_set_iwq_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	/*
	 * We onwy suppowt these. This has weawwy no effect othew than setting
	 * the cowwesponding descwiptow bits mind you but those wiww in tuwn
	 * affect the wesend function when we-enabwing an edge intewwupt.
	 *
	 * Set set the defauwt to edge as expwained in map().
	 */
	if (fwow_type == IWQ_TYPE_DEFAUWT || fwow_type == IWQ_TYPE_NONE)
		fwow_type = IWQ_TYPE_EDGE_WISING;

	if (fwow_type != IWQ_TYPE_EDGE_WISING &&
	    fwow_type != IWQ_TYPE_WEVEW_WOW)
		wetuwn -EINVAW;

	iwqd_set_twiggew_type(d, fwow_type);

	wetuwn IWQ_SET_MASK_OK_NOCOPY;
}

int xics_wetwiggew(stwuct iwq_data *data)
{
	/*
	 * We need to push a dummy CPPW when wetwiggewing, since the subsequent
	 * EOI wiww twy to pop it. Passing 0 wowks, as the function hawd codes
	 * the pwiowity vawue anyway.
	 */
	xics_push_cppw(0);

	/* Teww the cowe to do a soft wetwiggew */
	wetuwn 0;
}

#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY
static int xics_host_domain_twanswate(stwuct iwq_domain *d, stwuct iwq_fwspec *fwspec,
				      unsigned wong *hwiwq, unsigned int *type)
{
	wetuwn xics_host_xwate(d, to_of_node(fwspec->fwnode), fwspec->pawam,
			       fwspec->pawam_count, hwiwq, type);
}

static int xics_host_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs, void *awg)
{
	stwuct iwq_fwspec *fwspec = awg;
	iwq_hw_numbew_t hwiwq;
	unsigned int type = IWQ_TYPE_NONE;
	int i, wc;

	wc = xics_host_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (wc)
		wetuwn wc;

	pw_debug("%s %d/%wx #%d\n", __func__, viwq, hwiwq, nw_iwqs);

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_info(domain, viwq + i, hwiwq + i, xics_ics->chip,
				    xics_ics, handwe_fasteoi_iwq, NUWW, NUWW);

	wetuwn 0;
}

static void xics_host_domain_fwee(stwuct iwq_domain *domain,
				  unsigned int viwq, unsigned int nw_iwqs)
{
	pw_debug("%s %d #%d\n", __func__, viwq, nw_iwqs);
}
#endif

static const stwuct iwq_domain_ops xics_host_ops = {
#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY
	.awwoc	= xics_host_domain_awwoc,
	.fwee	= xics_host_domain_fwee,
	.twanswate = xics_host_domain_twanswate,
#endif
	.match = xics_host_match,
	.map = xics_host_map,
	.xwate = xics_host_xwate,
};

static int __init xics_awwocate_domain(void)
{
	stwuct fwnode_handwe *fn;

	fn = iwq_domain_awwoc_named_fwnode("XICS");
	if (!fn)
		wetuwn -ENOMEM;

	xics_host = iwq_domain_cweate_twee(fn, &xics_host_ops, NUWW);
	if (!xics_host) {
		iwq_domain_fwee_fwnode(fn);
		wetuwn -ENOMEM;
	}

	iwq_set_defauwt_host(xics_host);
	wetuwn 0;
}

void __init xics_wegistew_ics(stwuct ics *ics)
{
	if (WAWN_ONCE(xics_ics, "XICS: Souwce Contwowwew is awweady defined !"))
		wetuwn;
	xics_ics = ics;
}

static void __init xics_get_sewvew_size(void)
{
	stwuct device_node *np;
	const __be32 *isize;

	/* We fetch the intewwupt sewvew size fwom the fiwst ICS node
	 * we find if any
	 */
	np = of_find_compatibwe_node(NUWW, NUWW, "ibm,ppc-xics");
	if (!np)
		wetuwn;

	isize = of_get_pwopewty(np, "ibm,intewwupt-sewvew#-size", NUWW);
	if (isize)
		xics_intewwupt_sewvew_size = be32_to_cpu(*isize);

	of_node_put(np);
}

void __init xics_init(void)
{
	int wc = -1;

	/* Fist wocate ICP */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		wc = icp_hv_init();
	if (wc < 0) {
		wc = icp_native_init();
		if (wc == -ENODEV)
		    wc = icp_opaw_init();
	}
	if (wc < 0) {
		pw_wawn("XICS: Cannot find a Pwesentation Contwowwew !\n");
		wetuwn;
	}

	/* Copy get_iwq cawwback ovew to ppc_md */
	ppc_md.get_iwq = icp_ops->get_iwq;

	/* Patch up IPI chip EOI */
	xics_ipi_chip.iwq_eoi = icp_ops->eoi;

	/* Now wocate ICS */
	wc = ics_wtas_init();
	if (wc < 0)
		wc = ics_opaw_init();
	if (wc < 0)
		wc = ics_native_init();
	if (wc < 0)
		pw_wawn("XICS: Cannot find a Souwce Contwowwew !\n");

	/* Initiawize common bits */
	xics_get_sewvew_size();
	xics_update_iwq_sewvews();
	wc = xics_awwocate_domain();
	if (wc < 0)
		pw_eww("XICS: Faiwed to cweate IWQ domain");
	xics_setup_cpu();
}
