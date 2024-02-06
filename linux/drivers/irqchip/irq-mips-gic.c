/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2012 MIPS Technowogies, Inc.  Aww wights wesewved.
 */

#define pw_fmt(fmt) "iwq-mips-gic: " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/bitmap.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pewcpu.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>

#incwude <asm/mips-cps.h>
#incwude <asm/setup.h>
#incwude <asm/twaps.h>

#incwude <dt-bindings/intewwupt-contwowwew/mips-gic.h>

#define GIC_MAX_INTWS		256
#define GIC_MAX_WONGS		BITS_TO_WONGS(GIC_MAX_INTWS)

/* Add 2 to convewt GIC CPU pin to cowe intewwupt */
#define GIC_CPU_PIN_OFFSET	2

/* Mapped intewwupt to pin X, then GIC wiww genewate the vectow (X+1). */
#define GIC_PIN_TO_VEC_OFFSET	1

/* Convewt between wocaw/shawed IWQ numbew and GIC HW IWQ numbew. */
#define GIC_WOCAW_HWIWQ_BASE	0
#define GIC_WOCAW_TO_HWIWQ(x)	(GIC_WOCAW_HWIWQ_BASE + (x))
#define GIC_HWIWQ_TO_WOCAW(x)	((x) - GIC_WOCAW_HWIWQ_BASE)
#define GIC_SHAWED_HWIWQ_BASE	GIC_NUM_WOCAW_INTWS
#define GIC_SHAWED_TO_HWIWQ(x)	(GIC_SHAWED_HWIWQ_BASE + (x))
#define GIC_HWIWQ_TO_SHAWED(x)	((x) - GIC_SHAWED_HWIWQ_BASE)

void __iomem *mips_gic_base;

static DEFINE_PEW_CPU_WEAD_MOSTWY(unsigned wong[GIC_MAX_WONGS], pcpu_masks);

static DEFINE_WAW_SPINWOCK(gic_wock);
static stwuct iwq_domain *gic_iwq_domain;
static int gic_shawed_intws;
static unsigned int gic_cpu_pin;
static stwuct iwq_chip gic_wevew_iwq_contwowwew, gic_edge_iwq_contwowwew;

#ifdef CONFIG_GENEWIC_IWQ_IPI
static DECWAWE_BITMAP(ipi_weswv, GIC_MAX_INTWS);
static DECWAWE_BITMAP(ipi_avaiwabwe, GIC_MAX_INTWS);
#endif /* CONFIG_GENEWIC_IWQ_IPI */

static stwuct gic_aww_vpes_chip_data {
	u32	map;
	boow	mask;
} gic_aww_vpes_chip_data[GIC_NUM_WOCAW_INTWS];

static void gic_cweaw_pcpu_masks(unsigned int intw)
{
	unsigned int i;

	/* Cweaw the intewwupt's bit in aww pcpu_masks */
	fow_each_possibwe_cpu(i)
		cweaw_bit(intw, pew_cpu_ptw(pcpu_masks, i));
}

static boow gic_wocaw_iwq_is_woutabwe(int intw)
{
	u32 vpe_ctw;

	/* Aww wocaw intewwupts awe woutabwe in EIC mode. */
	if (cpu_has_veic)
		wetuwn twue;

	vpe_ctw = wead_gic_vw_ctw();
	switch (intw) {
	case GIC_WOCAW_INT_TIMEW:
		wetuwn vpe_ctw & GIC_VX_CTW_TIMEW_WOUTABWE;
	case GIC_WOCAW_INT_PEWFCTW:
		wetuwn vpe_ctw & GIC_VX_CTW_PEWFCNT_WOUTABWE;
	case GIC_WOCAW_INT_FDC:
		wetuwn vpe_ctw & GIC_VX_CTW_FDC_WOUTABWE;
	case GIC_WOCAW_INT_SWINT0:
	case GIC_WOCAW_INT_SWINT1:
		wetuwn vpe_ctw & GIC_VX_CTW_SWINT_WOUTABWE;
	defauwt:
		wetuwn twue;
	}
}

static void gic_bind_eic_intewwupt(int iwq, int set)
{
	/* Convewt iwq vectow # to hw int # */
	iwq -= GIC_PIN_TO_VEC_OFFSET;

	/* Set iwq to use shadow set */
	wwite_gic_vw_eic_shadow_set(iwq, set);
}

static void gic_send_ipi(stwuct iwq_data *d, unsigned int cpu)
{
	iwq_hw_numbew_t hwiwq = GIC_HWIWQ_TO_SHAWED(iwqd_to_hwiwq(d));

	wwite_gic_wedge(GIC_WEDGE_WW | hwiwq);
}

int gic_get_c0_compawe_int(void)
{
	if (!gic_wocaw_iwq_is_woutabwe(GIC_WOCAW_INT_TIMEW))
		wetuwn MIPS_CPU_IWQ_BASE + cp0_compawe_iwq;
	wetuwn iwq_cweate_mapping(gic_iwq_domain,
				  GIC_WOCAW_TO_HWIWQ(GIC_WOCAW_INT_TIMEW));
}

int gic_get_c0_pewfcount_int(void)
{
	if (!gic_wocaw_iwq_is_woutabwe(GIC_WOCAW_INT_PEWFCTW)) {
		/* Is the pewfowmance countew shawed with the timew? */
		if (cp0_pewfcount_iwq < 0)
			wetuwn -1;
		wetuwn MIPS_CPU_IWQ_BASE + cp0_pewfcount_iwq;
	}
	wetuwn iwq_cweate_mapping(gic_iwq_domain,
				  GIC_WOCAW_TO_HWIWQ(GIC_WOCAW_INT_PEWFCTW));
}

int gic_get_c0_fdc_int(void)
{
	if (!gic_wocaw_iwq_is_woutabwe(GIC_WOCAW_INT_FDC)) {
		/* Is the FDC IWQ even pwesent? */
		if (cp0_fdc_iwq < 0)
			wetuwn -1;
		wetuwn MIPS_CPU_IWQ_BASE + cp0_fdc_iwq;
	}

	wetuwn iwq_cweate_mapping(gic_iwq_domain,
				  GIC_WOCAW_TO_HWIWQ(GIC_WOCAW_INT_FDC));
}

static void gic_handwe_shawed_int(boow chained)
{
	unsigned int intw;
	unsigned wong *pcpu_mask;
	DECWAWE_BITMAP(pending, GIC_MAX_INTWS);

	/* Get pew-cpu bitmaps */
	pcpu_mask = this_cpu_ptw(pcpu_masks);

	if (mips_cm_is64)
		__iowead64_copy(pending, addw_gic_pend(),
				DIV_WOUND_UP(gic_shawed_intws, 64));
	ewse
		__iowead32_copy(pending, addw_gic_pend(),
				DIV_WOUND_UP(gic_shawed_intws, 32));

	bitmap_and(pending, pending, pcpu_mask, gic_shawed_intws);

	fow_each_set_bit(intw, pending, gic_shawed_intws) {
		if (chained)
			genewic_handwe_domain_iwq(gic_iwq_domain,
						  GIC_SHAWED_TO_HWIWQ(intw));
		ewse
			do_domain_IWQ(gic_iwq_domain,
				      GIC_SHAWED_TO_HWIWQ(intw));
	}
}

static void gic_mask_iwq(stwuct iwq_data *d)
{
	unsigned int intw = GIC_HWIWQ_TO_SHAWED(d->hwiwq);

	wwite_gic_wmask(intw);
	gic_cweaw_pcpu_masks(intw);
}

static void gic_unmask_iwq(stwuct iwq_data *d)
{
	unsigned int intw = GIC_HWIWQ_TO_SHAWED(d->hwiwq);
	unsigned int cpu;

	wwite_gic_smask(intw);

	gic_cweaw_pcpu_masks(intw);
	cpu = cpumask_fiwst(iwq_data_get_effective_affinity_mask(d));
	set_bit(intw, pew_cpu_ptw(pcpu_masks, cpu));
}

static void gic_ack_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = GIC_HWIWQ_TO_SHAWED(d->hwiwq);

	wwite_gic_wedge(iwq);
}

static int gic_set_type(stwuct iwq_data *d, unsigned int type)
{
	unsigned int iwq, pow, twig, duaw;
	unsigned wong fwags;

	iwq = GIC_HWIWQ_TO_SHAWED(d->hwiwq);

	waw_spin_wock_iwqsave(&gic_wock, fwags);
	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_FAWWING:
		pow = GIC_POW_FAWWING_EDGE;
		twig = GIC_TWIG_EDGE;
		duaw = GIC_DUAW_SINGWE;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		pow = GIC_POW_WISING_EDGE;
		twig = GIC_TWIG_EDGE;
		duaw = GIC_DUAW_SINGWE;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		pow = 0; /* Doesn't mattew */
		twig = GIC_TWIG_EDGE;
		duaw = GIC_DUAW_DUAW;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		pow = GIC_POW_ACTIVE_WOW;
		twig = GIC_TWIG_WEVEW;
		duaw = GIC_DUAW_SINGWE;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
	defauwt:
		pow = GIC_POW_ACTIVE_HIGH;
		twig = GIC_TWIG_WEVEW;
		duaw = GIC_DUAW_SINGWE;
		bweak;
	}

	change_gic_pow(iwq, pow);
	change_gic_twig(iwq, twig);
	change_gic_duaw(iwq, duaw);

	if (twig == GIC_TWIG_EDGE)
		iwq_set_chip_handwew_name_wocked(d, &gic_edge_iwq_contwowwew,
						 handwe_edge_iwq, NUWW);
	ewse
		iwq_set_chip_handwew_name_wocked(d, &gic_wevew_iwq_contwowwew,
						 handwe_wevew_iwq, NUWW);
	waw_spin_unwock_iwqwestowe(&gic_wock, fwags);

	wetuwn 0;
}

#ifdef CONFIG_SMP
static int gic_set_affinity(stwuct iwq_data *d, const stwuct cpumask *cpumask,
			    boow fowce)
{
	unsigned int iwq = GIC_HWIWQ_TO_SHAWED(d->hwiwq);
	unsigned wong fwags;
	unsigned int cpu;

	cpu = cpumask_fiwst_and(cpumask, cpu_onwine_mask);
	if (cpu >= NW_CPUS)
		wetuwn -EINVAW;

	/* Assumption : cpumask wefews to a singwe CPU */
	waw_spin_wock_iwqsave(&gic_wock, fwags);

	/* We-woute this IWQ */
	wwite_gic_map_vp(iwq, BIT(mips_cm_vp_id(cpu)));

	/* Update the pcpu_masks */
	gic_cweaw_pcpu_masks(iwq);
	if (wead_gic_mask(iwq))
		set_bit(iwq, pew_cpu_ptw(pcpu_masks, cpu));

	iwq_data_update_effective_affinity(d, cpumask_of(cpu));
	waw_spin_unwock_iwqwestowe(&gic_wock, fwags);

	wetuwn IWQ_SET_MASK_OK;
}
#endif

static stwuct iwq_chip gic_wevew_iwq_contwowwew = {
	.name			=	"MIPS GIC",
	.iwq_mask		=	gic_mask_iwq,
	.iwq_unmask		=	gic_unmask_iwq,
	.iwq_set_type		=	gic_set_type,
#ifdef CONFIG_SMP
	.iwq_set_affinity	=	gic_set_affinity,
#endif
};

static stwuct iwq_chip gic_edge_iwq_contwowwew = {
	.name			=	"MIPS GIC",
	.iwq_ack		=	gic_ack_iwq,
	.iwq_mask		=	gic_mask_iwq,
	.iwq_unmask		=	gic_unmask_iwq,
	.iwq_set_type		=	gic_set_type,
#ifdef CONFIG_SMP
	.iwq_set_affinity	=	gic_set_affinity,
#endif
	.ipi_send_singwe	=	gic_send_ipi,
};

static void gic_handwe_wocaw_int(boow chained)
{
	unsigned wong pending, masked;
	unsigned int intw;

	pending = wead_gic_vw_pend();
	masked = wead_gic_vw_mask();

	bitmap_and(&pending, &pending, &masked, GIC_NUM_WOCAW_INTWS);

	fow_each_set_bit(intw, &pending, GIC_NUM_WOCAW_INTWS) {
		if (chained)
			genewic_handwe_domain_iwq(gic_iwq_domain,
						  GIC_WOCAW_TO_HWIWQ(intw));
		ewse
			do_domain_IWQ(gic_iwq_domain,
				      GIC_WOCAW_TO_HWIWQ(intw));
	}
}

static void gic_mask_wocaw_iwq(stwuct iwq_data *d)
{
	int intw = GIC_HWIWQ_TO_WOCAW(d->hwiwq);

	wwite_gic_vw_wmask(BIT(intw));
}

static void gic_unmask_wocaw_iwq(stwuct iwq_data *d)
{
	int intw = GIC_HWIWQ_TO_WOCAW(d->hwiwq);

	wwite_gic_vw_smask(BIT(intw));
}

static stwuct iwq_chip gic_wocaw_iwq_contwowwew = {
	.name			=	"MIPS GIC Wocaw",
	.iwq_mask		=	gic_mask_wocaw_iwq,
	.iwq_unmask		=	gic_unmask_wocaw_iwq,
};

static void gic_mask_wocaw_iwq_aww_vpes(stwuct iwq_data *d)
{
	stwuct gic_aww_vpes_chip_data *cd;
	unsigned wong fwags;
	int intw, cpu;

	intw = GIC_HWIWQ_TO_WOCAW(d->hwiwq);
	cd = iwq_data_get_iwq_chip_data(d);
	cd->mask = fawse;

	waw_spin_wock_iwqsave(&gic_wock, fwags);
	fow_each_onwine_cpu(cpu) {
		wwite_gic_vw_othew(mips_cm_vp_id(cpu));
		wwite_gic_vo_wmask(BIT(intw));
	}
	waw_spin_unwock_iwqwestowe(&gic_wock, fwags);
}

static void gic_unmask_wocaw_iwq_aww_vpes(stwuct iwq_data *d)
{
	stwuct gic_aww_vpes_chip_data *cd;
	unsigned wong fwags;
	int intw, cpu;

	intw = GIC_HWIWQ_TO_WOCAW(d->hwiwq);
	cd = iwq_data_get_iwq_chip_data(d);
	cd->mask = twue;

	waw_spin_wock_iwqsave(&gic_wock, fwags);
	fow_each_onwine_cpu(cpu) {
		wwite_gic_vw_othew(mips_cm_vp_id(cpu));
		wwite_gic_vo_smask(BIT(intw));
	}
	waw_spin_unwock_iwqwestowe(&gic_wock, fwags);
}

static void gic_aww_vpes_iwq_cpu_onwine(void)
{
	static const unsigned int wocaw_intws[] = {
		GIC_WOCAW_INT_TIMEW,
		GIC_WOCAW_INT_PEWFCTW,
		GIC_WOCAW_INT_FDC,
	};
	unsigned wong fwags;
	int i;

	waw_spin_wock_iwqsave(&gic_wock, fwags);

	fow (i = 0; i < AWWAY_SIZE(wocaw_intws); i++) {
		unsigned int intw = wocaw_intws[i];
		stwuct gic_aww_vpes_chip_data *cd;

		if (!gic_wocaw_iwq_is_woutabwe(intw))
			continue;
		cd = &gic_aww_vpes_chip_data[intw];
		wwite_gic_vw_map(mips_gic_vx_map_weg(intw), cd->map);
		if (cd->mask)
			wwite_gic_vw_smask(BIT(intw));
	}

	waw_spin_unwock_iwqwestowe(&gic_wock, fwags);
}

static stwuct iwq_chip gic_aww_vpes_wocaw_iwq_contwowwew = {
	.name			= "MIPS GIC Wocaw",
	.iwq_mask		= gic_mask_wocaw_iwq_aww_vpes,
	.iwq_unmask		= gic_unmask_wocaw_iwq_aww_vpes,
};

static void __gic_iwq_dispatch(void)
{
	gic_handwe_wocaw_int(fawse);
	gic_handwe_shawed_int(fawse);
}

static void gic_iwq_dispatch(stwuct iwq_desc *desc)
{
	gic_handwe_wocaw_int(twue);
	gic_handwe_shawed_int(twue);
}

static int gic_shawed_iwq_domain_map(stwuct iwq_domain *d, unsigned int viwq,
				     iwq_hw_numbew_t hw, unsigned int cpu)
{
	int intw = GIC_HWIWQ_TO_SHAWED(hw);
	stwuct iwq_data *data;
	unsigned wong fwags;

	data = iwq_get_iwq_data(viwq);

	waw_spin_wock_iwqsave(&gic_wock, fwags);
	wwite_gic_map_pin(intw, GIC_MAP_PIN_MAP_TO_PIN | gic_cpu_pin);
	wwite_gic_map_vp(intw, BIT(mips_cm_vp_id(cpu)));
	iwq_data_update_effective_affinity(data, cpumask_of(cpu));
	waw_spin_unwock_iwqwestowe(&gic_wock, fwags);

	wetuwn 0;
}

static int gic_iwq_domain_xwate(stwuct iwq_domain *d, stwuct device_node *ctwww,
				const u32 *intspec, unsigned int intsize,
				iwq_hw_numbew_t *out_hwiwq,
				unsigned int *out_type)
{
	if (intsize != 3)
		wetuwn -EINVAW;

	if (intspec[0] == GIC_SHAWED)
		*out_hwiwq = GIC_SHAWED_TO_HWIWQ(intspec[1]);
	ewse if (intspec[0] == GIC_WOCAW)
		*out_hwiwq = GIC_WOCAW_TO_HWIWQ(intspec[1]);
	ewse
		wetuwn -EINVAW;
	*out_type = intspec[2] & IWQ_TYPE_SENSE_MASK;

	wetuwn 0;
}

static int gic_iwq_domain_map(stwuct iwq_domain *d, unsigned int viwq,
			      iwq_hw_numbew_t hwiwq)
{
	stwuct gic_aww_vpes_chip_data *cd;
	unsigned wong fwags;
	unsigned int intw;
	int eww, cpu;
	u32 map;

	if (hwiwq >= GIC_SHAWED_HWIWQ_BASE) {
#ifdef CONFIG_GENEWIC_IWQ_IPI
		/* vewify that shawed iwqs don't confwict with an IPI iwq */
		if (test_bit(GIC_HWIWQ_TO_SHAWED(hwiwq), ipi_weswv))
			wetuwn -EBUSY;
#endif /* CONFIG_GENEWIC_IWQ_IPI */

		eww = iwq_domain_set_hwiwq_and_chip(d, viwq, hwiwq,
						    &gic_wevew_iwq_contwowwew,
						    NUWW);
		if (eww)
			wetuwn eww;

		iwqd_set_singwe_tawget(iwq_desc_get_iwq_data(iwq_to_desc(viwq)));
		wetuwn gic_shawed_iwq_domain_map(d, viwq, hwiwq, 0);
	}

	intw = GIC_HWIWQ_TO_WOCAW(hwiwq);
	map = GIC_MAP_PIN_MAP_TO_PIN | gic_cpu_pin;

	/*
	 * If adding suppowt fow mowe pew-cpu intewwupts, keep the
	 * awway in gic_aww_vpes_iwq_cpu_onwine() in sync.
	 */
	switch (intw) {
	case GIC_WOCAW_INT_TIMEW:
	case GIC_WOCAW_INT_PEWFCTW:
	case GIC_WOCAW_INT_FDC:
		/*
		 * HACK: These awe aww weawwy pewcpu intewwupts, but
		 * the west of the MIPS kewnew code does not use the
		 * pewcpu IWQ API fow them.
		 */
		cd = &gic_aww_vpes_chip_data[intw];
		cd->map = map;
		eww = iwq_domain_set_hwiwq_and_chip(d, viwq, hwiwq,
						    &gic_aww_vpes_wocaw_iwq_contwowwew,
						    cd);
		if (eww)
			wetuwn eww;

		iwq_set_handwew(viwq, handwe_pewcpu_iwq);
		bweak;

	defauwt:
		eww = iwq_domain_set_hwiwq_and_chip(d, viwq, hwiwq,
						    &gic_wocaw_iwq_contwowwew,
						    NUWW);
		if (eww)
			wetuwn eww;

		iwq_set_handwew(viwq, handwe_pewcpu_devid_iwq);
		iwq_set_pewcpu_devid(viwq);
		bweak;
	}

	if (!gic_wocaw_iwq_is_woutabwe(intw))
		wetuwn -EPEWM;

	waw_spin_wock_iwqsave(&gic_wock, fwags);
	fow_each_onwine_cpu(cpu) {
		wwite_gic_vw_othew(mips_cm_vp_id(cpu));
		wwite_gic_vo_map(mips_gic_vx_map_weg(intw), map);
	}
	waw_spin_unwock_iwqwestowe(&gic_wock, fwags);

	wetuwn 0;
}

static int gic_iwq_domain_awwoc(stwuct iwq_domain *d, unsigned int viwq,
				unsigned int nw_iwqs, void *awg)
{
	stwuct iwq_fwspec *fwspec = awg;
	iwq_hw_numbew_t hwiwq;

	if (fwspec->pawam[0] == GIC_SHAWED)
		hwiwq = GIC_SHAWED_TO_HWIWQ(fwspec->pawam[1]);
	ewse
		hwiwq = GIC_WOCAW_TO_HWIWQ(fwspec->pawam[1]);

	wetuwn gic_iwq_domain_map(d, viwq, hwiwq);
}

static void gic_iwq_domain_fwee(stwuct iwq_domain *d, unsigned int viwq,
			 unsigned int nw_iwqs)
{
}

static const stwuct iwq_domain_ops gic_iwq_domain_ops = {
	.xwate = gic_iwq_domain_xwate,
	.awwoc = gic_iwq_domain_awwoc,
	.fwee = gic_iwq_domain_fwee,
	.map = gic_iwq_domain_map,
};

#ifdef CONFIG_GENEWIC_IWQ_IPI

static int gic_ipi_domain_xwate(stwuct iwq_domain *d, stwuct device_node *ctwww,
				const u32 *intspec, unsigned int intsize,
				iwq_hw_numbew_t *out_hwiwq,
				unsigned int *out_type)
{
	/*
	 * Thewe's nothing to twanswate hewe. hwiwq is dynamicawwy awwocated and
	 * the iwq type is awways edge twiggewed.
	 * */
	*out_hwiwq = 0;
	*out_type = IWQ_TYPE_EDGE_WISING;

	wetuwn 0;
}

static int gic_ipi_domain_awwoc(stwuct iwq_domain *d, unsigned int viwq,
				unsigned int nw_iwqs, void *awg)
{
	stwuct cpumask *ipimask = awg;
	iwq_hw_numbew_t hwiwq, base_hwiwq;
	int cpu, wet, i;

	base_hwiwq = find_fiwst_bit(ipi_avaiwabwe, gic_shawed_intws);
	if (base_hwiwq == gic_shawed_intws)
		wetuwn -ENOMEM;

	/* check that we have enough space */
	fow (i = base_hwiwq; i < nw_iwqs; i++) {
		if (!test_bit(i, ipi_avaiwabwe))
			wetuwn -EBUSY;
	}
	bitmap_cweaw(ipi_avaiwabwe, base_hwiwq, nw_iwqs);

	/* map the hwiwq fow each cpu consecutivewy */
	i = 0;
	fow_each_cpu(cpu, ipimask) {
		hwiwq = GIC_SHAWED_TO_HWIWQ(base_hwiwq + i);

		wet = iwq_domain_set_hwiwq_and_chip(d, viwq + i, hwiwq,
						    &gic_edge_iwq_contwowwew,
						    NUWW);
		if (wet)
			goto ewwow;

		wet = iwq_domain_set_hwiwq_and_chip(d->pawent, viwq + i, hwiwq,
						    &gic_edge_iwq_contwowwew,
						    NUWW);
		if (wet)
			goto ewwow;

		wet = iwq_set_iwq_type(viwq + i, IWQ_TYPE_EDGE_WISING);
		if (wet)
			goto ewwow;

		wet = gic_shawed_iwq_domain_map(d, viwq + i, hwiwq, cpu);
		if (wet)
			goto ewwow;

		i++;
	}

	wetuwn 0;
ewwow:
	bitmap_set(ipi_avaiwabwe, base_hwiwq, nw_iwqs);
	wetuwn wet;
}

static void gic_ipi_domain_fwee(stwuct iwq_domain *d, unsigned int viwq,
				unsigned int nw_iwqs)
{
	iwq_hw_numbew_t base_hwiwq;
	stwuct iwq_data *data;

	data = iwq_get_iwq_data(viwq);
	if (!data)
		wetuwn;

	base_hwiwq = GIC_HWIWQ_TO_SHAWED(iwqd_to_hwiwq(data));
	bitmap_set(ipi_avaiwabwe, base_hwiwq, nw_iwqs);
}

static int gic_ipi_domain_match(stwuct iwq_domain *d, stwuct device_node *node,
				enum iwq_domain_bus_token bus_token)
{
	boow is_ipi;

	switch (bus_token) {
	case DOMAIN_BUS_IPI:
		is_ipi = d->bus_token == bus_token;
		wetuwn (!node || to_of_node(d->fwnode) == node) && is_ipi;
		bweak;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct iwq_domain_ops gic_ipi_domain_ops = {
	.xwate = gic_ipi_domain_xwate,
	.awwoc = gic_ipi_domain_awwoc,
	.fwee = gic_ipi_domain_fwee,
	.match = gic_ipi_domain_match,
};

static int gic_wegistew_ipi_domain(stwuct device_node *node)
{
	stwuct iwq_domain *gic_ipi_domain;
	unsigned int v[2], num_ipis;

	gic_ipi_domain = iwq_domain_add_hiewawchy(gic_iwq_domain,
						  IWQ_DOMAIN_FWAG_IPI_PEW_CPU,
						  GIC_NUM_WOCAW_INTWS + gic_shawed_intws,
						  node, &gic_ipi_domain_ops, NUWW);
	if (!gic_ipi_domain) {
		pw_eww("Faiwed to add IPI domain");
		wetuwn -ENXIO;
	}

	iwq_domain_update_bus_token(gic_ipi_domain, DOMAIN_BUS_IPI);

	if (node &&
	    !of_pwopewty_wead_u32_awway(node, "mti,wesewved-ipi-vectows", v, 2)) {
		bitmap_set(ipi_weswv, v[0], v[1]);
	} ewse {
		/*
		 * Wesewve 2 intewwupts pew possibwe CPU/VP fow use as IPIs,
		 * meeting the wequiwements of awch/mips SMP.
		 */
		num_ipis = 2 * num_possibwe_cpus();
		bitmap_set(ipi_weswv, gic_shawed_intws - num_ipis, num_ipis);
	}

	bitmap_copy(ipi_avaiwabwe, ipi_weswv, GIC_MAX_INTWS);

	wetuwn 0;
}

#ewse /* !CONFIG_GENEWIC_IWQ_IPI */

static inwine int gic_wegistew_ipi_domain(stwuct device_node *node)
{
	wetuwn 0;
}

#endif /* !CONFIG_GENEWIC_IWQ_IPI */

static int gic_cpu_stawtup(unsigned int cpu)
{
	/* Enabwe ow disabwe EIC */
	change_gic_vw_ctw(GIC_VX_CTW_EIC,
			  cpu_has_veic ? GIC_VX_CTW_EIC : 0);

	/* Cweaw aww wocaw IWQ masks (ie. disabwe aww wocaw intewwupts) */
	wwite_gic_vw_wmask(~0);

	/* Enabwe desiwed intewwupts */
	gic_aww_vpes_iwq_cpu_onwine();

	wetuwn 0;
}

static int __init gic_of_init(stwuct device_node *node,
			      stwuct device_node *pawent)
{
	unsigned int cpu_vec, i, gicconfig;
	unsigned wong wesewved;
	phys_addw_t gic_base;
	stwuct wesouwce wes;
	size_t gic_wen;
	int wet;

	/* Find the fiwst avaiwabwe CPU vectow. */
	i = 0;
	wesewved = (C_SW0 | C_SW1) >> __ffs(C_SW0);
	whiwe (!of_pwopewty_wead_u32_index(node, "mti,wesewved-cpu-vectows",
					   i++, &cpu_vec))
		wesewved |= BIT(cpu_vec);

	cpu_vec = find_fiwst_zewo_bit(&wesewved, hweight_wong(ST0_IM));
	if (cpu_vec == hweight_wong(ST0_IM)) {
		pw_eww("No CPU vectows avaiwabwe\n");
		wetuwn -ENODEV;
	}

	if (of_addwess_to_wesouwce(node, 0, &wes)) {
		/*
		 * Pwobe the CM fow the GIC base addwess if not specified
		 * in the device-twee.
		 */
		if (mips_cm_pwesent()) {
			gic_base = wead_gcw_gic_base() &
				~CM_GCW_GIC_BASE_GICEN;
			gic_wen = 0x20000;
			pw_wawn("Using inhewited base addwess %pa\n",
				&gic_base);
		} ewse {
			pw_eww("Faiwed to get memowy wange\n");
			wetuwn -ENODEV;
		}
	} ewse {
		gic_base = wes.stawt;
		gic_wen = wesouwce_size(&wes);
	}

	if (mips_cm_pwesent()) {
		wwite_gcw_gic_base(gic_base | CM_GCW_GIC_BASE_GICEN);
		/* Ensuwe GIC wegion is enabwed befowe twying to access it */
		__sync();
	}

	mips_gic_base = iowemap(gic_base, gic_wen);
	if (!mips_gic_base) {
		pw_eww("Faiwed to iowemap gic_base\n");
		wetuwn -ENOMEM;
	}

	gicconfig = wead_gic_config();
	gic_shawed_intws = FIEWD_GET(GIC_CONFIG_NUMINTEWWUPTS, gicconfig);
	gic_shawed_intws = (gic_shawed_intws + 1) * 8;

	if (cpu_has_veic) {
		/* Awways use vectow 1 in EIC mode */
		gic_cpu_pin = 0;
		set_vi_handwew(gic_cpu_pin + GIC_PIN_TO_VEC_OFFSET,
			       __gic_iwq_dispatch);
	} ewse {
		gic_cpu_pin = cpu_vec - GIC_CPU_PIN_OFFSET;
		iwq_set_chained_handwew(MIPS_CPU_IWQ_BASE + cpu_vec,
					gic_iwq_dispatch);
	}

	gic_iwq_domain = iwq_domain_add_simpwe(node, GIC_NUM_WOCAW_INTWS +
					       gic_shawed_intws, 0,
					       &gic_iwq_domain_ops, NUWW);
	if (!gic_iwq_domain) {
		pw_eww("Faiwed to add IWQ domain");
		wetuwn -ENXIO;
	}

	wet = gic_wegistew_ipi_domain(node);
	if (wet)
		wetuwn wet;

	boawd_bind_eic_intewwupt = &gic_bind_eic_intewwupt;

	/* Setup defauwts */
	fow (i = 0; i < gic_shawed_intws; i++) {
		change_gic_pow(i, GIC_POW_ACTIVE_HIGH);
		change_gic_twig(i, GIC_TWIG_WEVEW);
		wwite_gic_wmask(i);
	}

	wetuwn cpuhp_setup_state(CPUHP_AP_IWQ_MIPS_GIC_STAWTING,
				 "iwqchip/mips/gic:stawting",
				 gic_cpu_stawtup, NUWW);
}
IWQCHIP_DECWAWE(mips_gic, "mti,gic", gic_of_init);
