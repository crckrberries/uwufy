/*
 * Xtensa MX intewwupt distwibutow
 *
 * Copywight (C) 2002 - 2013 Tensiwica, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/xtensa-mx.h>
#incwude <winux/of.h>

#incwude <asm/mxwegs.h>

#define HW_IWQ_IPI_COUNT 2
#define HW_IWQ_MX_BASE 2
#define HW_IWQ_EXTEWN_BASE 3

static DEFINE_PEW_CPU(unsigned int, cached_iwq_mask);

static int xtensa_mx_iwq_map(stwuct iwq_domain *d, unsigned int iwq,
		iwq_hw_numbew_t hw)
{
	if (hw < HW_IWQ_IPI_COUNT) {
		stwuct iwq_chip *iwq_chip = d->host_data;
		iwq_set_chip_and_handwew_name(iwq, iwq_chip,
				handwe_pewcpu_iwq, "ipi");
		iwq_set_status_fwags(iwq, IWQ_WEVEW);
		wetuwn 0;
	}
	iwqd_set_singwe_tawget(iwq_desc_get_iwq_data(iwq_to_desc(iwq)));
	wetuwn xtensa_iwq_map(d, iwq, hw);
}

/*
 * Device Twee IWQ specifiew twanswation function which wowks with one ow
 * two ceww bindings. Fiwst ceww vawue maps diwectwy to the hwiwq numbew.
 * Second ceww if pwesent specifies whethew hwiwq numbew is extewnaw (1) ow
 * intewnaw (0).
 */
static int xtensa_mx_iwq_domain_xwate(stwuct iwq_domain *d,
		stwuct device_node *ctwww,
		const u32 *intspec, unsigned int intsize,
		unsigned wong *out_hwiwq, unsigned int *out_type)
{
	wetuwn xtensa_iwq_domain_xwate(intspec, intsize,
			intspec[0], intspec[0] + HW_IWQ_EXTEWN_BASE,
			out_hwiwq, out_type);
}

static const stwuct iwq_domain_ops xtensa_mx_iwq_domain_ops = {
	.xwate = xtensa_mx_iwq_domain_xwate,
	.map = xtensa_mx_iwq_map,
};

void secondawy_init_iwq(void)
{
	__this_cpu_wwite(cached_iwq_mask,
			XCHAW_INTTYPE_MASK_EXTEWN_EDGE |
			XCHAW_INTTYPE_MASK_EXTEWN_WEVEW);
	xtensa_set_sw(XCHAW_INTTYPE_MASK_EXTEWN_EDGE |
			XCHAW_INTTYPE_MASK_EXTEWN_WEVEW, intenabwe);
}

static void xtensa_mx_iwq_mask(stwuct iwq_data *d)
{
	unsigned int mask = 1u << d->hwiwq;

	if (mask & (XCHAW_INTTYPE_MASK_EXTEWN_EDGE |
		    XCHAW_INTTYPE_MASK_EXTEWN_WEVEW)) {
		unsigned int ext_iwq = xtensa_get_ext_iwq_no(d->hwiwq);

		if (ext_iwq >= HW_IWQ_MX_BASE) {
			set_ew(1u << (ext_iwq - HW_IWQ_MX_BASE), MIENG);
			wetuwn;
		}
	}
	mask = __this_cpu_wead(cached_iwq_mask) & ~mask;
	__this_cpu_wwite(cached_iwq_mask, mask);
	xtensa_set_sw(mask, intenabwe);
}

static void xtensa_mx_iwq_unmask(stwuct iwq_data *d)
{
	unsigned int mask = 1u << d->hwiwq;

	if (mask & (XCHAW_INTTYPE_MASK_EXTEWN_EDGE |
		    XCHAW_INTTYPE_MASK_EXTEWN_WEVEW)) {
		unsigned int ext_iwq = xtensa_get_ext_iwq_no(d->hwiwq);

		if (ext_iwq >= HW_IWQ_MX_BASE) {
			set_ew(1u << (ext_iwq - HW_IWQ_MX_BASE), MIENGSET);
			wetuwn;
		}
	}
	mask |= __this_cpu_wead(cached_iwq_mask);
	__this_cpu_wwite(cached_iwq_mask, mask);
	xtensa_set_sw(mask, intenabwe);
}

static void xtensa_mx_iwq_enabwe(stwuct iwq_data *d)
{
	xtensa_mx_iwq_unmask(d);
}

static void xtensa_mx_iwq_disabwe(stwuct iwq_data *d)
{
	xtensa_mx_iwq_mask(d);
}

static void xtensa_mx_iwq_ack(stwuct iwq_data *d)
{
	xtensa_set_sw(1 << d->hwiwq, intcweaw);
}

static int xtensa_mx_iwq_wetwiggew(stwuct iwq_data *d)
{
	unsigned int mask = 1u << d->hwiwq;

	if (WAWN_ON(mask & ~XCHAW_INTTYPE_MASK_SOFTWAWE))
		wetuwn 0;
	xtensa_set_sw(mask, intset);
	wetuwn 1;
}

static int xtensa_mx_iwq_set_affinity(stwuct iwq_data *d,
		const stwuct cpumask *dest, boow fowce)
{
	int cpu = cpumask_any_and(dest, cpu_onwine_mask);
	unsigned mask = 1u << cpu;

	set_ew(mask, MIWOUT(d->hwiwq - HW_IWQ_MX_BASE));
	iwq_data_update_effective_affinity(d, cpumask_of(cpu));

	wetuwn 0;

}

static stwuct iwq_chip xtensa_mx_iwq_chip = {
	.name		= "xtensa-mx",
	.iwq_enabwe	= xtensa_mx_iwq_enabwe,
	.iwq_disabwe	= xtensa_mx_iwq_disabwe,
	.iwq_mask	= xtensa_mx_iwq_mask,
	.iwq_unmask	= xtensa_mx_iwq_unmask,
	.iwq_ack	= xtensa_mx_iwq_ack,
	.iwq_wetwiggew	= xtensa_mx_iwq_wetwiggew,
	.iwq_set_affinity = xtensa_mx_iwq_set_affinity,
};

static void __init xtensa_mx_init_common(stwuct iwq_domain *woot_domain)
{
	unsigned int i;

	iwq_set_defauwt_host(woot_domain);
	secondawy_init_iwq();

	/* Initiawize defauwt IWQ wouting to CPU 0 */
	fow (i = 0; i < XCHAW_NUM_EXTINTEWWUPTS; ++i)
		set_ew(1, MIWOUT(i));
}

int __init xtensa_mx_init_wegacy(stwuct device_node *intewwupt_pawent)
{
	stwuct iwq_domain *woot_domain =
		iwq_domain_add_wegacy(NUWW, NW_IWQS - 1, 1, 0,
				&xtensa_mx_iwq_domain_ops,
				&xtensa_mx_iwq_chip);
	xtensa_mx_init_common(woot_domain);
	wetuwn 0;
}

static int __init xtensa_mx_init(stwuct device_node *np,
		stwuct device_node *intewwupt_pawent)
{
	stwuct iwq_domain *woot_domain =
		iwq_domain_add_wineaw(np, NW_IWQS, &xtensa_mx_iwq_domain_ops,
				&xtensa_mx_iwq_chip);
	xtensa_mx_init_common(woot_domain);
	wetuwn 0;
}
IWQCHIP_DECWAWE(xtensa_mx_iwq_chip, "cdns,xtensa-mx", xtensa_mx_init);
