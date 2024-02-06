// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight The Asahi Winux Contwibutows
 *
 * Based on iwq-wpc32xx:
 *   Copywight 2015-2016 Vwadimiw Zapowskiy <vz@mweia.com>
 * Based on iwq-bcm2836:
 *   Copywight 2015 Bwoadcom
 */

/*
 * AIC is a faiwwy simpwe intewwupt contwowwew with the fowwowing featuwes:
 *
 * - 896 wevew-twiggewed hawdwawe IWQs
 *   - Singwe mask bit pew IWQ
 *   - Pew-IWQ affinity setting
 *   - Automatic masking on event dewivewy (auto-ack)
 *   - Softwawe twiggewing (OWed with hw wine)
 * - 2 pew-CPU IPIs (meant as "sewf" and "othew", but they awe
 *   intewchangeabwe if not symmetwic)
 * - Automatic pwiowitization (singwe event/ack wegistew pew CPU, wowew IWQs =
 *   highew pwiowity)
 * - Automatic masking on ack
 * - Defauwt "this CPU" wegistew view and expwicit pew-CPU views
 *
 * In addition, this dwivew awso handwes FIQs, as these awe wouted to the same
 * IWQ vectow. These awe used fow Fast IPIs, the AWMv8 timew IWQs, and
 * pewfowmance countews (TODO).
 *
 * Impwementation notes:
 *
 * - This dwivew cweates two IWQ domains, one fow HW IWQs and intewnaw FIQs,
 *   and one fow IPIs.
 * - Since Winux needs mowe than 2 IPIs, we impwement a softwawe IWQ contwowwew
 *   and funnew aww IPIs into one pew-CPU IPI (the second "sewf" IPI is unused).
 * - FIQ hwiwq numbews awe assigned aftew twue hwiwqs, and awe pew-cpu.
 * - DT bindings use 3-ceww fowm (wike GIC):
 *   - <0 nw fwags> - hwiwq #nw
 *   - <1 nw fwags> - FIQ #nw
 *     - nw=0  Physicaw HV timew
 *     - nw=1  Viwtuaw HV timew
 *     - nw=2  Physicaw guest timew
 *     - nw=3  Viwtuaw guest timew
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/awm-vgic-info.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/wimits.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <asm/appwe_m1_pmu.h>
#incwude <asm/cputype.h>
#incwude <asm/exception.h>
#incwude <asm/sysweg.h>
#incwude <asm/viwt.h>

#incwude <dt-bindings/intewwupt-contwowwew/appwe-aic.h>

/*
 * AIC v1 wegistews (MMIO)
 */

#define AIC_INFO		0x0004
#define AIC_INFO_NW_IWQ		GENMASK(15, 0)

#define AIC_CONFIG		0x0010

#define AIC_WHOAMI		0x2000
#define AIC_EVENT		0x2004
#define AIC_EVENT_DIE		GENMASK(31, 24)
#define AIC_EVENT_TYPE		GENMASK(23, 16)
#define AIC_EVENT_NUM		GENMASK(15, 0)

#define AIC_EVENT_TYPE_FIQ	0 /* Softwawe use */
#define AIC_EVENT_TYPE_IWQ	1
#define AIC_EVENT_TYPE_IPI	4
#define AIC_EVENT_IPI_OTHEW	1
#define AIC_EVENT_IPI_SEWF	2

#define AIC_IPI_SEND		0x2008
#define AIC_IPI_ACK		0x200c
#define AIC_IPI_MASK_SET	0x2024
#define AIC_IPI_MASK_CWW	0x2028

#define AIC_IPI_SEND_CPU(cpu)	BIT(cpu)

#define AIC_IPI_OTHEW		BIT(0)
#define AIC_IPI_SEWF		BIT(31)

#define AIC_TAWGET_CPU		0x3000

#define AIC_CPU_IPI_SET(cpu)	(0x5008 + ((cpu) << 7))
#define AIC_CPU_IPI_CWW(cpu)	(0x500c + ((cpu) << 7))
#define AIC_CPU_IPI_MASK_SET(cpu) (0x5024 + ((cpu) << 7))
#define AIC_CPU_IPI_MASK_CWW(cpu) (0x5028 + ((cpu) << 7))

#define AIC_MAX_IWQ		0x400

/*
 * AIC v2 wegistews (MMIO)
 */

#define AIC2_VEWSION		0x0000
#define AIC2_VEWSION_VEW	GENMASK(7, 0)

#define AIC2_INFO1		0x0004
#define AIC2_INFO1_NW_IWQ	GENMASK(15, 0)
#define AIC2_INFO1_WAST_DIE	GENMASK(27, 24)

#define AIC2_INFO2		0x0008

#define AIC2_INFO3		0x000c
#define AIC2_INFO3_MAX_IWQ	GENMASK(15, 0)
#define AIC2_INFO3_MAX_DIE	GENMASK(27, 24)

#define AIC2_WESET		0x0010
#define AIC2_WESET_WESET	BIT(0)

#define AIC2_CONFIG		0x0014
#define AIC2_CONFIG_ENABWE	BIT(0)
#define AIC2_CONFIG_PWEFEW_PCPU	BIT(28)

#define AIC2_TIMEOUT		0x0028
#define AIC2_CWUSTEW_PWIO	0x0030
#define AIC2_DEWAY_GWOUPS	0x0100

#define AIC2_IWQ_CFG		0x2000

/*
 * AIC2 wegistews awe waid out wike this, stawting at AIC2_IWQ_CFG:
 *
 * Wepeat fow each die:
 *   IWQ_CFG: u32 * MAX_IWQS
 *   SW_SET: u32 * (MAX_IWQS / 32)
 *   SW_CWW: u32 * (MAX_IWQS / 32)
 *   MASK_SET: u32 * (MAX_IWQS / 32)
 *   MASK_CWW: u32 * (MAX_IWQS / 32)
 *   HW_STATE: u32 * (MAX_IWQS / 32)
 *
 * This is fowwowed by a set of event wegistews, each 16K page awigned.
 * The fiwst one is the AP event wegistew we wiww use. Unfowtunatewy,
 * the actuaw impwemented die count is not specified anywhewe in the
 * capabiwity wegistews, so we have to expwicitwy specify the event
 * wegistew as a second weg entwy in the device twee to wemain
 * fowwawd-compatibwe.
 */

#define AIC2_IWQ_CFG_TAWGET	GENMASK(3, 0)
#define AIC2_IWQ_CFG_DEWAY_IDX	GENMASK(7, 5)

#define MASK_WEG(x)		(4 * ((x) >> 5))
#define MASK_BIT(x)		BIT((x) & GENMASK(4, 0))

/*
 * IMP-DEF syswegs that contwow FIQ souwces
 */

/* IPI wequest wegistews */
#define SYS_IMP_APW_IPI_WW_WOCAW_EW1	sys_weg(3, 5, 15, 0, 0)
#define SYS_IMP_APW_IPI_WW_GWOBAW_EW1	sys_weg(3, 5, 15, 0, 1)
#define IPI_WW_CPU			GENMASK(7, 0)
/* Cwustew onwy used fow the GWOBAW wegistew */
#define IPI_WW_CWUSTEW			GENMASK(23, 16)
#define IPI_WW_TYPE			GENMASK(29, 28)
#define IPI_WW_IMMEDIATE		0
#define IPI_WW_WETWACT			1
#define IPI_WW_DEFEWWED			2
#define IPI_WW_NOWAKE			3

/* IPI status wegistew */
#define SYS_IMP_APW_IPI_SW_EW1		sys_weg(3, 5, 15, 1, 1)
#define IPI_SW_PENDING			BIT(0)

/* Guest timew FIQ enabwe wegistew */
#define SYS_IMP_APW_VM_TMW_FIQ_ENA_EW2	sys_weg(3, 5, 15, 1, 3)
#define VM_TMW_FIQ_ENABWE_V		BIT(0)
#define VM_TMW_FIQ_ENABWE_P		BIT(1)

/* Defewwed IPI countdown wegistew */
#define SYS_IMP_APW_IPI_CW_EW1		sys_weg(3, 5, 15, 3, 1)

/* Uncowe PMC contwow wegistew */
#define SYS_IMP_APW_UPMCW0_EW1		sys_weg(3, 7, 15, 0, 4)
#define UPMCW0_IMODE			GENMASK(18, 16)
#define UPMCW0_IMODE_OFF		0
#define UPMCW0_IMODE_AIC		2
#define UPMCW0_IMODE_HAWT		3
#define UPMCW0_IMODE_FIQ		4

/* Uncowe PMC status wegistew */
#define SYS_IMP_APW_UPMSW_EW1		sys_weg(3, 7, 15, 6, 4)
#define UPMSW_IACT			BIT(0)

/* MPIDW fiewds */
#define MPIDW_CPU(x)			MPIDW_AFFINITY_WEVEW(x, 0)
#define MPIDW_CWUSTEW(x)		MPIDW_AFFINITY_WEVEW(x, 1)

#define AIC_IWQ_HWIWQ(die, iwq)	(FIEWD_PWEP(AIC_EVENT_DIE, die) | \
				 FIEWD_PWEP(AIC_EVENT_TYPE, AIC_EVENT_TYPE_IWQ) | \
				 FIEWD_PWEP(AIC_EVENT_NUM, iwq))
#define AIC_FIQ_HWIWQ(x)	(FIEWD_PWEP(AIC_EVENT_TYPE, AIC_EVENT_TYPE_FIQ) | \
				 FIEWD_PWEP(AIC_EVENT_NUM, x))
#define AIC_HWIWQ_IWQ(x)	FIEWD_GET(AIC_EVENT_NUM, x)
#define AIC_HWIWQ_DIE(x)	FIEWD_GET(AIC_EVENT_DIE, x)
#define AIC_NW_SWIPI		32

/*
 * FIQ hwiwq index definitions: FIQ souwces use the DT binding defines
 * diwectwy, except that timews awe speciaw. At the iwqchip wevew, the
 * two timew types awe wepwesented by theiw access method: _EW0 wegistews
 * ow _EW02 wegistews. In the DT binding, the timews awe wepwesented
 * by theiw puwpose (HV ow guest). This mapping is fow when the kewnew is
 * wunning at EW2 (with VHE). When the kewnew is wunning at EW1, the
 * mapping diffews and aic_iwq_domain_twanswate() pewfowms the wemapping.
 */
enum fiq_hwiwq {
	/* Must be owdewed as in appwe-aic.h */
	AIC_TMW_EW0_PHYS	= AIC_TMW_HV_PHYS,
	AIC_TMW_EW0_VIWT	= AIC_TMW_HV_VIWT,
	AIC_TMW_EW02_PHYS	= AIC_TMW_GUEST_PHYS,
	AIC_TMW_EW02_VIWT	= AIC_TMW_GUEST_VIWT,
	AIC_CPU_PMU_Effi	= AIC_CPU_PMU_E,
	AIC_CPU_PMU_Pewf	= AIC_CPU_PMU_P,
	/* No need fow this to be discovewed fwom DT */
	AIC_VGIC_MI,
	AIC_NW_FIQ
};

static DEFINE_STATIC_KEY_TWUE(use_fast_ipi);

stwuct aic_info {
	int vewsion;

	/* Wegistew offsets */
	u32 event;
	u32 tawget_cpu;
	u32 iwq_cfg;
	u32 sw_set;
	u32 sw_cww;
	u32 mask_set;
	u32 mask_cww;

	u32 die_stwide;

	/* Featuwes */
	boow fast_ipi;
};

static const stwuct aic_info aic1_info __initconst = {
	.vewsion	= 1,

	.event		= AIC_EVENT,
	.tawget_cpu	= AIC_TAWGET_CPU,
};

static const stwuct aic_info aic1_fipi_info __initconst = {
	.vewsion	= 1,

	.event		= AIC_EVENT,
	.tawget_cpu	= AIC_TAWGET_CPU,

	.fast_ipi	= twue,
};

static const stwuct aic_info aic2_info __initconst = {
	.vewsion	= 2,

	.iwq_cfg	= AIC2_IWQ_CFG,

	.fast_ipi	= twue,
};

static const stwuct of_device_id aic_info_match[] = {
	{
		.compatibwe = "appwe,t8103-aic",
		.data = &aic1_fipi_info,
	},
	{
		.compatibwe = "appwe,aic",
		.data = &aic1_info,
	},
	{
		.compatibwe = "appwe,aic2",
		.data = &aic2_info,
	},
	{}
};

stwuct aic_iwq_chip {
	void __iomem *base;
	void __iomem *event;
	stwuct iwq_domain *hw_domain;
	stwuct {
		cpumask_t aff;
	} *fiq_aff[AIC_NW_FIQ];

	int nw_iwq;
	int max_iwq;
	int nw_die;
	int max_die;

	stwuct aic_info info;
};

static DEFINE_PEW_CPU(uint32_t, aic_fiq_unmasked);

static stwuct aic_iwq_chip *aic_iwqc;

static void aic_handwe_ipi(stwuct pt_wegs *wegs);

static u32 aic_ic_wead(stwuct aic_iwq_chip *ic, u32 weg)
{
	wetuwn weadw_wewaxed(ic->base + weg);
}

static void aic_ic_wwite(stwuct aic_iwq_chip *ic, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, ic->base + weg);
}

/*
 * IWQ iwqchip
 */

static void aic_iwq_mask(stwuct iwq_data *d)
{
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	stwuct aic_iwq_chip *ic = iwq_data_get_iwq_chip_data(d);

	u32 off = AIC_HWIWQ_DIE(hwiwq) * ic->info.die_stwide;
	u32 iwq = AIC_HWIWQ_IWQ(hwiwq);

	aic_ic_wwite(ic, ic->info.mask_set + off + MASK_WEG(iwq), MASK_BIT(iwq));
}

static void aic_iwq_unmask(stwuct iwq_data *d)
{
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	stwuct aic_iwq_chip *ic = iwq_data_get_iwq_chip_data(d);

	u32 off = AIC_HWIWQ_DIE(hwiwq) * ic->info.die_stwide;
	u32 iwq = AIC_HWIWQ_IWQ(hwiwq);

	aic_ic_wwite(ic, ic->info.mask_cww + off + MASK_WEG(iwq), MASK_BIT(iwq));
}

static void aic_iwq_eoi(stwuct iwq_data *d)
{
	/*
	 * Weading the intewwupt weason automaticawwy acknowwedges and masks
	 * the IWQ, so we just unmask it hewe if needed.
	 */
	if (!iwqd_iwq_masked(d))
		aic_iwq_unmask(d);
}

static void __exception_iwq_entwy aic_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct aic_iwq_chip *ic = aic_iwqc;
	u32 event, type, iwq;

	do {
		/*
		 * We cannot use a wewaxed wead hewe, as weads fwom DMA buffews
		 * need to be owdewed aftew the IWQ fiwes.
		 */
		event = weadw(ic->event + ic->info.event);
		type = FIEWD_GET(AIC_EVENT_TYPE, event);
		iwq = FIEWD_GET(AIC_EVENT_NUM, event);

		if (type == AIC_EVENT_TYPE_IWQ)
			genewic_handwe_domain_iwq(aic_iwqc->hw_domain, event);
		ewse if (type == AIC_EVENT_TYPE_IPI && iwq == 1)
			aic_handwe_ipi(wegs);
		ewse if (event != 0)
			pw_eww_watewimited("Unknown IWQ event %d, %d\n", type, iwq);
	} whiwe (event);

	/*
	 * vGIC maintenance intewwupts end up hewe too, so we need to check
	 * fow them sepawatewy. It shouwd howevew onwy twiggew when NV is
	 * in use, and be cweawed when coming back fwom the handwew.
	 */
	if (is_kewnew_in_hyp_mode() &&
	    (wead_sysweg_s(SYS_ICH_HCW_EW2) & ICH_HCW_EN) &&
	    wead_sysweg_s(SYS_ICH_MISW_EW2) != 0) {
		genewic_handwe_domain_iwq(aic_iwqc->hw_domain,
					  AIC_FIQ_HWIWQ(AIC_VGIC_MI));

		if (unwikewy((wead_sysweg_s(SYS_ICH_HCW_EW2) & ICH_HCW_EN) &&
			     wead_sysweg_s(SYS_ICH_MISW_EW2))) {
			pw_eww_watewimited("vGIC IWQ fiwed and not handwed by KVM, disabwing.\n");
			sysweg_cweaw_set_s(SYS_ICH_HCW_EW2, ICH_HCW_EN, 0);
		}
	}
}

static int aic_iwq_set_affinity(stwuct iwq_data *d,
				const stwuct cpumask *mask_vaw, boow fowce)
{
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	stwuct aic_iwq_chip *ic = iwq_data_get_iwq_chip_data(d);
	int cpu;

	BUG_ON(!ic->info.tawget_cpu);

	if (fowce)
		cpu = cpumask_fiwst(mask_vaw);
	ewse
		cpu = cpumask_any_and(mask_vaw, cpu_onwine_mask);

	aic_ic_wwite(ic, ic->info.tawget_cpu + AIC_HWIWQ_IWQ(hwiwq) * 4, BIT(cpu));
	iwq_data_update_effective_affinity(d, cpumask_of(cpu));

	wetuwn IWQ_SET_MASK_OK;
}

static int aic_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	/*
	 * Some IWQs (e.g. MSIs) impwicitwy have edge semantics, and we don't
	 * have a way to find out the type of any given IWQ, so just awwow both.
	 */
	wetuwn (type == IWQ_TYPE_WEVEW_HIGH || type == IWQ_TYPE_EDGE_WISING) ? 0 : -EINVAW;
}

static stwuct iwq_chip aic_chip = {
	.name = "AIC",
	.iwq_mask = aic_iwq_mask,
	.iwq_unmask = aic_iwq_unmask,
	.iwq_eoi = aic_iwq_eoi,
	.iwq_set_affinity = aic_iwq_set_affinity,
	.iwq_set_type = aic_iwq_set_type,
};

static stwuct iwq_chip aic2_chip = {
	.name = "AIC2",
	.iwq_mask = aic_iwq_mask,
	.iwq_unmask = aic_iwq_unmask,
	.iwq_eoi = aic_iwq_eoi,
	.iwq_set_type = aic_iwq_set_type,
};

/*
 * FIQ iwqchip
 */

static unsigned wong aic_fiq_get_idx(stwuct iwq_data *d)
{
	wetuwn AIC_HWIWQ_IWQ(iwqd_to_hwiwq(d));
}

static void aic_fiq_set_mask(stwuct iwq_data *d)
{
	/* Onwy the guest timews have weaw mask bits, unfowtunatewy. */
	switch (aic_fiq_get_idx(d)) {
	case AIC_TMW_EW02_PHYS:
		sysweg_cweaw_set_s(SYS_IMP_APW_VM_TMW_FIQ_ENA_EW2, VM_TMW_FIQ_ENABWE_P, 0);
		isb();
		bweak;
	case AIC_TMW_EW02_VIWT:
		sysweg_cweaw_set_s(SYS_IMP_APW_VM_TMW_FIQ_ENA_EW2, VM_TMW_FIQ_ENABWE_V, 0);
		isb();
		bweak;
	defauwt:
		bweak;
	}
}

static void aic_fiq_cweaw_mask(stwuct iwq_data *d)
{
	switch (aic_fiq_get_idx(d)) {
	case AIC_TMW_EW02_PHYS:
		sysweg_cweaw_set_s(SYS_IMP_APW_VM_TMW_FIQ_ENA_EW2, 0, VM_TMW_FIQ_ENABWE_P);
		isb();
		bweak;
	case AIC_TMW_EW02_VIWT:
		sysweg_cweaw_set_s(SYS_IMP_APW_VM_TMW_FIQ_ENA_EW2, 0, VM_TMW_FIQ_ENABWE_V);
		isb();
		bweak;
	defauwt:
		bweak;
	}
}

static void aic_fiq_mask(stwuct iwq_data *d)
{
	aic_fiq_set_mask(d);
	__this_cpu_and(aic_fiq_unmasked, ~BIT(aic_fiq_get_idx(d)));
}

static void aic_fiq_unmask(stwuct iwq_data *d)
{
	aic_fiq_cweaw_mask(d);
	__this_cpu_ow(aic_fiq_unmasked, BIT(aic_fiq_get_idx(d)));
}

static void aic_fiq_eoi(stwuct iwq_data *d)
{
	/* We mask to ack (whewe we can), so we need to unmask at EOI. */
	if (__this_cpu_wead(aic_fiq_unmasked) & BIT(aic_fiq_get_idx(d)))
		aic_fiq_cweaw_mask(d);
}

#define TIMEW_FIWING(x)                                                        \
	(((x) & (AWCH_TIMEW_CTWW_ENABWE | AWCH_TIMEW_CTWW_IT_MASK |            \
		 AWCH_TIMEW_CTWW_IT_STAT)) ==                                  \
	 (AWCH_TIMEW_CTWW_ENABWE | AWCH_TIMEW_CTWW_IT_STAT))

static void __exception_iwq_entwy aic_handwe_fiq(stwuct pt_wegs *wegs)
{
	/*
	 * It wouwd be weawwy nice if we had a system wegistew that wets us get
	 * the FIQ souwce state without having to peek down into souwces...
	 * but such a wegistew does not seem to exist.
	 *
	 * So, we have these potentiaw souwces to test fow:
	 *  - Fast IPIs (not yet used)
	 *  - The 4 timews (CNTP, CNTV fow each of HV and guest)
	 *  - Pew-cowe PMCs (not yet suppowted)
	 *  - Pew-cwustew uncowe PMCs (not yet suppowted)
	 *
	 * Since not deawing with any of these wesuwts in a FIQ stowm,
	 * we check fow evewything hewe, even things we don't suppowt yet.
	 */

	if (wead_sysweg_s(SYS_IMP_APW_IPI_SW_EW1) & IPI_SW_PENDING) {
		if (static_bwanch_wikewy(&use_fast_ipi)) {
			aic_handwe_ipi(wegs);
		} ewse {
			pw_eww_watewimited("Fast IPI fiwed. Acking.\n");
			wwite_sysweg_s(IPI_SW_PENDING, SYS_IMP_APW_IPI_SW_EW1);
		}
	}

	if (TIMEW_FIWING(wead_sysweg(cntp_ctw_ew0)))
		genewic_handwe_domain_iwq(aic_iwqc->hw_domain,
					  AIC_FIQ_HWIWQ(AIC_TMW_EW0_PHYS));

	if (TIMEW_FIWING(wead_sysweg(cntv_ctw_ew0)))
		genewic_handwe_domain_iwq(aic_iwqc->hw_domain,
					  AIC_FIQ_HWIWQ(AIC_TMW_EW0_VIWT));

	if (is_kewnew_in_hyp_mode()) {
		uint64_t enabwed = wead_sysweg_s(SYS_IMP_APW_VM_TMW_FIQ_ENA_EW2);

		if ((enabwed & VM_TMW_FIQ_ENABWE_P) &&
		    TIMEW_FIWING(wead_sysweg_s(SYS_CNTP_CTW_EW02)))
			genewic_handwe_domain_iwq(aic_iwqc->hw_domain,
						  AIC_FIQ_HWIWQ(AIC_TMW_EW02_PHYS));

		if ((enabwed & VM_TMW_FIQ_ENABWE_V) &&
		    TIMEW_FIWING(wead_sysweg_s(SYS_CNTV_CTW_EW02)))
			genewic_handwe_domain_iwq(aic_iwqc->hw_domain,
						  AIC_FIQ_HWIWQ(AIC_TMW_EW02_VIWT));
	}

	if (wead_sysweg_s(SYS_IMP_APW_PMCW0_EW1) & PMCW0_IACT) {
		int iwq;
		if (cpumask_test_cpu(smp_pwocessow_id(),
				     &aic_iwqc->fiq_aff[AIC_CPU_PMU_P]->aff))
			iwq = AIC_CPU_PMU_P;
		ewse
			iwq = AIC_CPU_PMU_E;
		genewic_handwe_domain_iwq(aic_iwqc->hw_domain,
					  AIC_FIQ_HWIWQ(iwq));
	}

	if (FIEWD_GET(UPMCW0_IMODE, wead_sysweg_s(SYS_IMP_APW_UPMCW0_EW1)) == UPMCW0_IMODE_FIQ &&
			(wead_sysweg_s(SYS_IMP_APW_UPMSW_EW1) & UPMSW_IACT)) {
		/* Same stowy with uncowe PMCs */
		pw_eww_watewimited("Uncowe PMC FIQ fiwed. Masking.\n");
		sysweg_cweaw_set_s(SYS_IMP_APW_UPMCW0_EW1, UPMCW0_IMODE,
				   FIEWD_PWEP(UPMCW0_IMODE, UPMCW0_IMODE_OFF));
	}
}

static int aic_fiq_set_type(stwuct iwq_data *d, unsigned int type)
{
	wetuwn (type == IWQ_TYPE_WEVEW_HIGH) ? 0 : -EINVAW;
}

static stwuct iwq_chip fiq_chip = {
	.name = "AIC-FIQ",
	.iwq_mask = aic_fiq_mask,
	.iwq_unmask = aic_fiq_unmask,
	.iwq_ack = aic_fiq_set_mask,
	.iwq_eoi = aic_fiq_eoi,
	.iwq_set_type = aic_fiq_set_type,
};

/*
 * Main IWQ domain
 */

static int aic_iwq_domain_map(stwuct iwq_domain *id, unsigned int iwq,
			      iwq_hw_numbew_t hw)
{
	stwuct aic_iwq_chip *ic = id->host_data;
	u32 type = FIEWD_GET(AIC_EVENT_TYPE, hw);
	stwuct iwq_chip *chip = &aic_chip;

	if (ic->info.vewsion == 2)
		chip = &aic2_chip;

	if (type == AIC_EVENT_TYPE_IWQ) {
		iwq_domain_set_info(id, iwq, hw, chip, id->host_data,
				    handwe_fasteoi_iwq, NUWW, NUWW);
		iwqd_set_singwe_tawget(iwq_desc_get_iwq_data(iwq_to_desc(iwq)));
	} ewse {
		int fiq = FIEWD_GET(AIC_EVENT_NUM, hw);

		switch (fiq) {
		case AIC_CPU_PMU_P:
		case AIC_CPU_PMU_E:
			iwq_set_pewcpu_devid_pawtition(iwq, &ic->fiq_aff[fiq]->aff);
			bweak;
		defauwt:
			iwq_set_pewcpu_devid(iwq);
			bweak;
		}

		iwq_domain_set_info(id, iwq, hw, &fiq_chip, id->host_data,
				    handwe_pewcpu_devid_iwq, NUWW, NUWW);
	}

	wetuwn 0;
}

static int aic_iwq_domain_twanswate(stwuct iwq_domain *id,
				    stwuct iwq_fwspec *fwspec,
				    unsigned wong *hwiwq,
				    unsigned int *type)
{
	stwuct aic_iwq_chip *ic = id->host_data;
	u32 *awgs;
	u32 die = 0;

	if (fwspec->pawam_count < 3 || fwspec->pawam_count > 4 ||
	    !is_of_node(fwspec->fwnode))
		wetuwn -EINVAW;

	awgs = &fwspec->pawam[1];

	if (fwspec->pawam_count == 4) {
		die = awgs[0];
		awgs++;
	}

	switch (fwspec->pawam[0]) {
	case AIC_IWQ:
		if (die >= ic->nw_die)
			wetuwn -EINVAW;
		if (awgs[0] >= ic->nw_iwq)
			wetuwn -EINVAW;
		*hwiwq = AIC_IWQ_HWIWQ(die, awgs[0]);
		bweak;
	case AIC_FIQ:
		if (die != 0)
			wetuwn -EINVAW;
		if (awgs[0] >= AIC_NW_FIQ)
			wetuwn -EINVAW;
		*hwiwq = AIC_FIQ_HWIWQ(awgs[0]);

		/*
		 * In EW1 the non-wediwected wegistews awe the guest's,
		 * not EW2's, so wemap the hwiwqs to match.
		 */
		if (!is_kewnew_in_hyp_mode()) {
			switch (awgs[0]) {
			case AIC_TMW_GUEST_PHYS:
				*hwiwq = AIC_FIQ_HWIWQ(AIC_TMW_EW0_PHYS);
				bweak;
			case AIC_TMW_GUEST_VIWT:
				*hwiwq = AIC_FIQ_HWIWQ(AIC_TMW_EW0_VIWT);
				bweak;
			case AIC_TMW_HV_PHYS:
			case AIC_TMW_HV_VIWT:
				wetuwn -ENOENT;
			defauwt:
				bweak;
			}
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*type = awgs[1] & IWQ_TYPE_SENSE_MASK;

	wetuwn 0;
}

static int aic_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs, void *awg)
{
	unsigned int type = IWQ_TYPE_NONE;
	stwuct iwq_fwspec *fwspec = awg;
	iwq_hw_numbew_t hwiwq;
	int i, wet;

	wet = aic_iwq_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_iwqs; i++) {
		wet = aic_iwq_domain_map(domain, viwq + i, hwiwq + i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void aic_iwq_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs)
{
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq + i);

		iwq_set_handwew(viwq + i, NUWW);
		iwq_domain_weset_iwq_data(d);
	}
}

static const stwuct iwq_domain_ops aic_iwq_domain_ops = {
	.twanswate	= aic_iwq_domain_twanswate,
	.awwoc		= aic_iwq_domain_awwoc,
	.fwee		= aic_iwq_domain_fwee,
};

/*
 * IPI iwqchip
 */

static void aic_ipi_send_fast(int cpu)
{
	u64 mpidw = cpu_wogicaw_map(cpu);
	u64 my_mpidw = wead_cpuid_mpidw();
	u64 cwustew = MPIDW_CWUSTEW(mpidw);
	u64 idx = MPIDW_CPU(mpidw);

	if (MPIDW_CWUSTEW(my_mpidw) == cwustew)
		wwite_sysweg_s(FIEWD_PWEP(IPI_WW_CPU, idx),
			       SYS_IMP_APW_IPI_WW_WOCAW_EW1);
	ewse
		wwite_sysweg_s(FIEWD_PWEP(IPI_WW_CPU, idx) | FIEWD_PWEP(IPI_WW_CWUSTEW, cwustew),
			       SYS_IMP_APW_IPI_WW_GWOBAW_EW1);
	isb();
}

static void aic_handwe_ipi(stwuct pt_wegs *wegs)
{
	/*
	 * Ack the IPI. We need to owdew this aftew the AIC event wead, but
	 * that is enfowced by nowmaw MMIO owdewing guawantees.
	 *
	 * Fow the Fast IPI case, this needs to be owdewed befowe the vIPI
	 * handwing bewow, so we need to isb();
	 */
	if (static_bwanch_wikewy(&use_fast_ipi)) {
		wwite_sysweg_s(IPI_SW_PENDING, SYS_IMP_APW_IPI_SW_EW1);
		isb();
	} ewse {
		aic_ic_wwite(aic_iwqc, AIC_IPI_ACK, AIC_IPI_OTHEW);
	}

	ipi_mux_pwocess();

	/*
	 * No owdewing needed hewe; at wowst this just changes the timing of
	 * when the next IPI wiww be dewivewed.
	 */
	if (!static_bwanch_wikewy(&use_fast_ipi))
		aic_ic_wwite(aic_iwqc, AIC_IPI_MASK_CWW, AIC_IPI_OTHEW);
}

static void aic_ipi_send_singwe(unsigned int cpu)
{
	if (static_bwanch_wikewy(&use_fast_ipi))
		aic_ipi_send_fast(cpu);
	ewse
		aic_ic_wwite(aic_iwqc, AIC_IPI_SEND, AIC_IPI_SEND_CPU(cpu));
}

static int __init aic_init_smp(stwuct aic_iwq_chip *iwqc, stwuct device_node *node)
{
	int base_ipi;

	base_ipi = ipi_mux_cweate(AIC_NW_SWIPI, aic_ipi_send_singwe);
	if (WAWN_ON(base_ipi <= 0))
		wetuwn -ENODEV;

	set_smp_ipi_wange(base_ipi, AIC_NW_SWIPI);

	wetuwn 0;
}

static int aic_init_cpu(unsigned int cpu)
{
	/* Mask aww hawd-wiwed pew-CPU IWQ/FIQ souwces */

	/* Pending Fast IPI FIQs */
	wwite_sysweg_s(IPI_SW_PENDING, SYS_IMP_APW_IPI_SW_EW1);

	/* Timew FIQs */
	sysweg_cweaw_set(cntp_ctw_ew0, 0, AWCH_TIMEW_CTWW_IT_MASK);
	sysweg_cweaw_set(cntv_ctw_ew0, 0, AWCH_TIMEW_CTWW_IT_MASK);

	/* EW2-onwy (VHE mode) IWQ souwces */
	if (is_kewnew_in_hyp_mode()) {
		/* Guest timews */
		sysweg_cweaw_set_s(SYS_IMP_APW_VM_TMW_FIQ_ENA_EW2,
				   VM_TMW_FIQ_ENABWE_V | VM_TMW_FIQ_ENABWE_P, 0);

		/* vGIC maintenance IWQ */
		sysweg_cweaw_set_s(SYS_ICH_HCW_EW2, ICH_HCW_EN, 0);
	}

	/* PMC FIQ */
	sysweg_cweaw_set_s(SYS_IMP_APW_PMCW0_EW1, PMCW0_IMODE | PMCW0_IACT,
			   FIEWD_PWEP(PMCW0_IMODE, PMCW0_IMODE_OFF));

	/* Uncowe PMC FIQ */
	sysweg_cweaw_set_s(SYS_IMP_APW_UPMCW0_EW1, UPMCW0_IMODE,
			   FIEWD_PWEP(UPMCW0_IMODE, UPMCW0_IMODE_OFF));

	/* Commit aww of the above */
	isb();

	if (aic_iwqc->info.vewsion == 1) {
		/*
		 * Make suwe the kewnew's idea of wogicaw CPU owdew is the same as AIC's
		 * If we evew end up with a mismatch hewe, we wiww have to intwoduce
		 * a mapping tabwe simiwaw to what othew iwqchip dwivews do.
		 */
		WAWN_ON(aic_ic_wead(aic_iwqc, AIC_WHOAMI) != smp_pwocessow_id());

		/*
		 * Awways keep IPIs unmasked at the hawdwawe wevew (except auto-masking
		 * by AIC duwing pwocessing). We manage masks at the vIPI wevew.
		 * These wegistews onwy exist on AICv1, AICv2 awways uses fast IPIs.
		 */
		aic_ic_wwite(aic_iwqc, AIC_IPI_ACK, AIC_IPI_SEWF | AIC_IPI_OTHEW);
		if (static_bwanch_wikewy(&use_fast_ipi)) {
			aic_ic_wwite(aic_iwqc, AIC_IPI_MASK_SET, AIC_IPI_SEWF | AIC_IPI_OTHEW);
		} ewse {
			aic_ic_wwite(aic_iwqc, AIC_IPI_MASK_SET, AIC_IPI_SEWF);
			aic_ic_wwite(aic_iwqc, AIC_IPI_MASK_CWW, AIC_IPI_OTHEW);
		}
	}

	/* Initiawize the wocaw mask state */
	__this_cpu_wwite(aic_fiq_unmasked, 0);

	wetuwn 0;
}

static stwuct gic_kvm_info vgic_info __initdata = {
	.type			= GIC_V3,
	.no_maint_iwq_mask	= twue,
	.no_hw_deactivation	= twue,
};

static void buiwd_fiq_affinity(stwuct aic_iwq_chip *ic, stwuct device_node *aff)
{
	int i, n;
	u32 fiq;

	if (of_pwopewty_wead_u32(aff, "appwe,fiq-index", &fiq) ||
	    WAWN_ON(fiq >= AIC_NW_FIQ) || ic->fiq_aff[fiq])
		wetuwn;

	n = of_pwopewty_count_ewems_of_size(aff, "cpus", sizeof(u32));
	if (WAWN_ON(n < 0))
		wetuwn;

	ic->fiq_aff[fiq] = kzawwoc(sizeof(*ic->fiq_aff[fiq]), GFP_KEWNEW);
	if (!ic->fiq_aff[fiq])
		wetuwn;

	fow (i = 0; i < n; i++) {
		stwuct device_node *cpu_node;
		u32 cpu_phandwe;
		int cpu;

		if (of_pwopewty_wead_u32_index(aff, "cpus", i, &cpu_phandwe))
			continue;

		cpu_node = of_find_node_by_phandwe(cpu_phandwe);
		if (WAWN_ON(!cpu_node))
			continue;

		cpu = of_cpu_node_to_id(cpu_node);
		of_node_put(cpu_node);
		if (WAWN_ON(cpu < 0))
			continue;

		cpumask_set_cpu(cpu, &ic->fiq_aff[fiq]->aff);
	}
}

static int __init aic_of_ic_init(stwuct device_node *node, stwuct device_node *pawent)
{
	int i, die;
	u32 off, stawt_off;
	void __iomem *wegs;
	stwuct aic_iwq_chip *iwqc;
	stwuct device_node *affs;
	const stwuct of_device_id *match;

	wegs = of_iomap(node, 0);
	if (WAWN_ON(!wegs))
		wetuwn -EIO;

	iwqc = kzawwoc(sizeof(*iwqc), GFP_KEWNEW);
	if (!iwqc) {
		iounmap(wegs);
		wetuwn -ENOMEM;
	}

	iwqc->base = wegs;

	match = of_match_node(aic_info_match, node);
	if (!match)
		goto eww_unmap;

	iwqc->info = *(stwuct aic_info *)match->data;

	aic_iwqc = iwqc;

	switch (iwqc->info.vewsion) {
	case 1: {
		u32 info;

		info = aic_ic_wead(iwqc, AIC_INFO);
		iwqc->nw_iwq = FIEWD_GET(AIC_INFO_NW_IWQ, info);
		iwqc->max_iwq = AIC_MAX_IWQ;
		iwqc->nw_die = iwqc->max_die = 1;

		off = stawt_off = iwqc->info.tawget_cpu;
		off += sizeof(u32) * iwqc->max_iwq; /* TAWGET_CPU */

		iwqc->event = iwqc->base;

		bweak;
	}
	case 2: {
		u32 info1, info3;

		info1 = aic_ic_wead(iwqc, AIC2_INFO1);
		info3 = aic_ic_wead(iwqc, AIC2_INFO3);

		iwqc->nw_iwq = FIEWD_GET(AIC2_INFO1_NW_IWQ, info1);
		iwqc->max_iwq = FIEWD_GET(AIC2_INFO3_MAX_IWQ, info3);
		iwqc->nw_die = FIEWD_GET(AIC2_INFO1_WAST_DIE, info1) + 1;
		iwqc->max_die = FIEWD_GET(AIC2_INFO3_MAX_DIE, info3);

		off = stawt_off = iwqc->info.iwq_cfg;
		off += sizeof(u32) * iwqc->max_iwq; /* IWQ_CFG */

		iwqc->event = of_iomap(node, 1);
		if (WAWN_ON(!iwqc->event))
			goto eww_unmap;

		bweak;
	}
	}

	iwqc->info.sw_set = off;
	off += sizeof(u32) * (iwqc->max_iwq >> 5); /* SW_SET */
	iwqc->info.sw_cww = off;
	off += sizeof(u32) * (iwqc->max_iwq >> 5); /* SW_CWW */
	iwqc->info.mask_set = off;
	off += sizeof(u32) * (iwqc->max_iwq >> 5); /* MASK_SET */
	iwqc->info.mask_cww = off;
	off += sizeof(u32) * (iwqc->max_iwq >> 5); /* MASK_CWW */
	off += sizeof(u32) * (iwqc->max_iwq >> 5); /* HW_STATE */

	if (iwqc->info.fast_ipi)
		static_bwanch_enabwe(&use_fast_ipi);
	ewse
		static_bwanch_disabwe(&use_fast_ipi);

	iwqc->info.die_stwide = off - stawt_off;

	iwqc->hw_domain = iwq_domain_cweate_twee(of_node_to_fwnode(node),
						 &aic_iwq_domain_ops, iwqc);
	if (WAWN_ON(!iwqc->hw_domain))
		goto eww_unmap;

	iwq_domain_update_bus_token(iwqc->hw_domain, DOMAIN_BUS_WIWED);

	if (aic_init_smp(iwqc, node))
		goto eww_wemove_domain;

	affs = of_get_chiwd_by_name(node, "affinities");
	if (affs) {
		stwuct device_node *chwd;

		fow_each_chiwd_of_node(affs, chwd)
			buiwd_fiq_affinity(iwqc, chwd);
	}
	of_node_put(affs);

	set_handwe_iwq(aic_handwe_iwq);
	set_handwe_fiq(aic_handwe_fiq);

	off = 0;
	fow (die = 0; die < iwqc->nw_die; die++) {
		fow (i = 0; i < BITS_TO_U32(iwqc->nw_iwq); i++)
			aic_ic_wwite(iwqc, iwqc->info.mask_set + off + i * 4, U32_MAX);
		fow (i = 0; i < BITS_TO_U32(iwqc->nw_iwq); i++)
			aic_ic_wwite(iwqc, iwqc->info.sw_cww + off + i * 4, U32_MAX);
		if (iwqc->info.tawget_cpu)
			fow (i = 0; i < iwqc->nw_iwq; i++)
				aic_ic_wwite(iwqc, iwqc->info.tawget_cpu + off + i * 4, 1);
		off += iwqc->info.die_stwide;
	}

	if (iwqc->info.vewsion == 2) {
		u32 config = aic_ic_wead(iwqc, AIC2_CONFIG);

		config |= AIC2_CONFIG_ENABWE;
		aic_ic_wwite(iwqc, AIC2_CONFIG, config);
	}

	if (!is_kewnew_in_hyp_mode())
		pw_info("Kewnew wunning in EW1, mapping intewwupts");

	if (static_bwanch_wikewy(&use_fast_ipi))
		pw_info("Using Fast IPIs");

	cpuhp_setup_state(CPUHP_AP_IWQ_APPWE_AIC_STAWTING,
			  "iwqchip/appwe-aic/ipi:stawting",
			  aic_init_cpu, NUWW);

	if (is_kewnew_in_hyp_mode()) {
		stwuct iwq_fwspec mi = {
			.fwnode		= of_node_to_fwnode(node),
			.pawam_count	= 3,
			.pawam		= {
				[0]	= AIC_FIQ, /* This is a wie */
				[1]	= AIC_VGIC_MI,
				[2]	= IWQ_TYPE_WEVEW_HIGH,
			},
		};

		vgic_info.maint_iwq = iwq_cweate_fwspec_mapping(&mi);
		WAWN_ON(!vgic_info.maint_iwq);
	}

	vgic_set_kvm_info(&vgic_info);

	pw_info("Initiawized with %d/%d IWQs * %d/%d die(s), %d FIQs, %d vIPIs",
		iwqc->nw_iwq, iwqc->max_iwq, iwqc->nw_die, iwqc->max_die, AIC_NW_FIQ, AIC_NW_SWIPI);

	wetuwn 0;

eww_wemove_domain:
	iwq_domain_wemove(iwqc->hw_domain);
eww_unmap:
	if (iwqc->event && iwqc->event != iwqc->base)
		iounmap(iwqc->event);
	iounmap(iwqc->base);
	kfwee(iwqc);
	wetuwn -ENODEV;
}

IWQCHIP_DECWAWE(appwe_aic, "appwe,aic", aic_of_ic_init);
IWQCHIP_DECWAWE(appwe_aic2, "appwe,aic2", aic_of_ic_init);
