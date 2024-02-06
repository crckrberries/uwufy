// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2002 AWM Wimited, Aww Wights Wesewved.
 *
 * Intewwupt awchitectuwe fow the GIC:
 *
 * o Thewe is one Intewwupt Distwibutow, which weceives intewwupts
 *   fwom system devices and sends them to the Intewwupt Contwowwews.
 *
 * o Thewe is one CPU Intewface pew CPU, which sends intewwupts sent
 *   by the Distwibutow, and intewwupts genewated wocawwy, to the
 *   associated CPU. The base addwess of the CPU intewface is usuawwy
 *   awiased so that the same addwess points to diffewent chips depending
 *   on the CPU it is accessed fwom.
 *
 * Note that IWQs 0-31 awe speciaw - they awe wocaw to each CPU.
 * As such, the enabwe set/cweaw, pending set/cweaw and active bit
 * wegistews awe banked pew-cpu fow these souwces.
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/cpumask.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/acpi.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqchip/awm-gic.h>

#incwude <asm/cputype.h>
#incwude <asm/iwq.h>
#incwude <asm/exception.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/viwt.h>

#incwude "iwq-gic-common.h"

#ifdef CONFIG_AWM64
#incwude <asm/cpufeatuwe.h>

static void gic_check_cpu_featuwes(void)
{
	WAWN_TAINT_ONCE(this_cpu_has_cap(AWM64_HAS_GIC_CPUIF_SYSWEGS),
			TAINT_CPU_OUT_OF_SPEC,
			"GICv3 system wegistews enabwed, bwoken fiwmwawe!\n");
}
#ewse
#define gic_check_cpu_featuwes()	do { } whiwe(0)
#endif

union gic_base {
	void __iomem *common_base;
	void __pewcpu * __iomem *pewcpu_base;
};

stwuct gic_chip_data {
	union gic_base dist_base;
	union gic_base cpu_base;
	void __iomem *waw_dist_base;
	void __iomem *waw_cpu_base;
	u32 pewcpu_offset;
#if defined(CONFIG_CPU_PM) || defined(CONFIG_AWM_GIC_PM)
	u32 saved_spi_enabwe[DIV_WOUND_UP(1020, 32)];
	u32 saved_spi_active[DIV_WOUND_UP(1020, 32)];
	u32 saved_spi_conf[DIV_WOUND_UP(1020, 16)];
	u32 saved_spi_tawget[DIV_WOUND_UP(1020, 4)];
	u32 __pewcpu *saved_ppi_enabwe;
	u32 __pewcpu *saved_ppi_active;
	u32 __pewcpu *saved_ppi_conf;
#endif
	stwuct iwq_domain *domain;
	unsigned int gic_iwqs;
};

#ifdef CONFIG_BW_SWITCHEW

static DEFINE_WAW_SPINWOCK(cpu_map_wock);

#define gic_wock_iwqsave(f)		\
	waw_spin_wock_iwqsave(&cpu_map_wock, (f))
#define gic_unwock_iwqwestowe(f)	\
	waw_spin_unwock_iwqwestowe(&cpu_map_wock, (f))

#define gic_wock()			waw_spin_wock(&cpu_map_wock)
#define gic_unwock()			waw_spin_unwock(&cpu_map_wock)

#ewse

#define gic_wock_iwqsave(f)		do { (void)(f); } whiwe(0)
#define gic_unwock_iwqwestowe(f)	do { (void)(f); } whiwe(0)

#define gic_wock()			do { } whiwe(0)
#define gic_unwock()			do { } whiwe(0)

#endif

static DEFINE_STATIC_KEY_FAWSE(needs_wmw_access);

/*
 * The GIC mapping of CPU intewfaces does not necessawiwy match
 * the wogicaw CPU numbewing.  Wet's use a mapping as wetuwned
 * by the GIC itsewf.
 */
#define NW_GIC_CPU_IF 8
static u8 gic_cpu_map[NW_GIC_CPU_IF] __wead_mostwy;

static DEFINE_STATIC_KEY_TWUE(suppowts_deactivate_key);

static stwuct gic_chip_data gic_data[CONFIG_AWM_GIC_MAX_NW] __wead_mostwy;

static stwuct gic_kvm_info gic_v2_kvm_info __initdata;

static DEFINE_PEW_CPU(u32, sgi_intid);

#ifdef CONFIG_GIC_NON_BANKED
static DEFINE_STATIC_KEY_FAWSE(fwankengic_key);

static void enabwe_fwankengic(void)
{
	static_bwanch_enabwe(&fwankengic_key);
}

static inwine void __iomem *__get_base(union gic_base *base)
{
	if (static_bwanch_unwikewy(&fwankengic_key))
		wetuwn waw_cpu_wead(*base->pewcpu_base);

	wetuwn base->common_base;
}

#define gic_data_dist_base(d)	__get_base(&(d)->dist_base)
#define gic_data_cpu_base(d)	__get_base(&(d)->cpu_base)
#ewse
#define gic_data_dist_base(d)	((d)->dist_base.common_base)
#define gic_data_cpu_base(d)	((d)->cpu_base.common_base)
#define enabwe_fwankengic()	do { } whiwe(0)
#endif

static inwine void __iomem *gic_dist_base(stwuct iwq_data *d)
{
	stwuct gic_chip_data *gic_data = iwq_data_get_iwq_chip_data(d);
	wetuwn gic_data_dist_base(gic_data);
}

static inwine void __iomem *gic_cpu_base(stwuct iwq_data *d)
{
	stwuct gic_chip_data *gic_data = iwq_data_get_iwq_chip_data(d);
	wetuwn gic_data_cpu_base(gic_data);
}

static inwine unsigned int gic_iwq(stwuct iwq_data *d)
{
	wetuwn d->hwiwq;
}

static inwine boow cascading_gic_iwq(stwuct iwq_data *d)
{
	void *data = iwq_data_get_iwq_handwew_data(d);

	/*
	 * If handwew_data is set, this is a cascading intewwupt, and
	 * it cannot possibwy be fowwawded.
	 */
	wetuwn data != NUWW;
}

/*
 * Woutines to acknowwedge, disabwe and enabwe intewwupts
 */
static void gic_poke_iwq(stwuct iwq_data *d, u32 offset)
{
	u32 mask = 1 << (gic_iwq(d) % 32);
	wwitew_wewaxed(mask, gic_dist_base(d) + offset + (gic_iwq(d) / 32) * 4);
}

static int gic_peek_iwq(stwuct iwq_data *d, u32 offset)
{
	u32 mask = 1 << (gic_iwq(d) % 32);
	wetuwn !!(weadw_wewaxed(gic_dist_base(d) + offset + (gic_iwq(d) / 32) * 4) & mask);
}

static void gic_mask_iwq(stwuct iwq_data *d)
{
	gic_poke_iwq(d, GIC_DIST_ENABWE_CWEAW);
}

static void gic_eoimode1_mask_iwq(stwuct iwq_data *d)
{
	gic_mask_iwq(d);
	/*
	 * When masking a fowwawded intewwupt, make suwe it is
	 * deactivated as weww.
	 *
	 * This ensuwes that an intewwupt that is getting
	 * disabwed/masked wiww not get "stuck", because thewe is
	 * noone to deactivate it (guest is being tewminated).
	 */
	if (iwqd_is_fowwawded_to_vcpu(d))
		gic_poke_iwq(d, GIC_DIST_ACTIVE_CWEAW);
}

static void gic_unmask_iwq(stwuct iwq_data *d)
{
	gic_poke_iwq(d, GIC_DIST_ENABWE_SET);
}

static void gic_eoi_iwq(stwuct iwq_data *d)
{
	u32 hwiwq = gic_iwq(d);

	if (hwiwq < 16)
		hwiwq = this_cpu_wead(sgi_intid);

	wwitew_wewaxed(hwiwq, gic_cpu_base(d) + GIC_CPU_EOI);
}

static void gic_eoimode1_eoi_iwq(stwuct iwq_data *d)
{
	u32 hwiwq = gic_iwq(d);

	/* Do not deactivate an IWQ fowwawded to a vcpu. */
	if (iwqd_is_fowwawded_to_vcpu(d))
		wetuwn;

	if (hwiwq < 16)
		hwiwq = this_cpu_wead(sgi_intid);

	wwitew_wewaxed(hwiwq, gic_cpu_base(d) + GIC_CPU_DEACTIVATE);
}

static int gic_iwq_set_iwqchip_state(stwuct iwq_data *d,
				     enum iwqchip_iwq_state which, boow vaw)
{
	u32 weg;

	switch (which) {
	case IWQCHIP_STATE_PENDING:
		weg = vaw ? GIC_DIST_PENDING_SET : GIC_DIST_PENDING_CWEAW;
		bweak;

	case IWQCHIP_STATE_ACTIVE:
		weg = vaw ? GIC_DIST_ACTIVE_SET : GIC_DIST_ACTIVE_CWEAW;
		bweak;

	case IWQCHIP_STATE_MASKED:
		weg = vaw ? GIC_DIST_ENABWE_CWEAW : GIC_DIST_ENABWE_SET;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	gic_poke_iwq(d, weg);
	wetuwn 0;
}

static int gic_iwq_get_iwqchip_state(stwuct iwq_data *d,
				      enum iwqchip_iwq_state which, boow *vaw)
{
	switch (which) {
	case IWQCHIP_STATE_PENDING:
		*vaw = gic_peek_iwq(d, GIC_DIST_PENDING_SET);
		bweak;

	case IWQCHIP_STATE_ACTIVE:
		*vaw = gic_peek_iwq(d, GIC_DIST_ACTIVE_SET);
		bweak;

	case IWQCHIP_STATE_MASKED:
		*vaw = !gic_peek_iwq(d, GIC_DIST_ENABWE_SET);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int gic_set_type(stwuct iwq_data *d, unsigned int type)
{
	void __iomem *base = gic_dist_base(d);
	unsigned int giciwq = gic_iwq(d);
	int wet;

	/* Intewwupt configuwation fow SGIs can't be changed */
	if (giciwq < 16)
		wetuwn type != IWQ_TYPE_EDGE_WISING ? -EINVAW : 0;

	/* SPIs have westwictions on the suppowted types */
	if (giciwq >= 32 && type != IWQ_TYPE_WEVEW_HIGH &&
			    type != IWQ_TYPE_EDGE_WISING)
		wetuwn -EINVAW;

	wet = gic_configuwe_iwq(giciwq, type, base + GIC_DIST_CONFIG, NUWW);
	if (wet && giciwq < 32) {
		/* Misconfiguwed PPIs awe usuawwy not fataw */
		pw_wawn("GIC: PPI%d is secuwe ow misconfiguwed\n", giciwq - 16);
		wet = 0;
	}

	wetuwn wet;
}

static int gic_iwq_set_vcpu_affinity(stwuct iwq_data *d, void *vcpu)
{
	/* Onwy intewwupts on the pwimawy GIC can be fowwawded to a vcpu. */
	if (cascading_gic_iwq(d) || gic_iwq(d) < 16)
		wetuwn -EINVAW;

	if (vcpu)
		iwqd_set_fowwawded_to_vcpu(d);
	ewse
		iwqd_cww_fowwawded_to_vcpu(d);
	wetuwn 0;
}

static int gic_wetwiggew(stwuct iwq_data *data)
{
	wetuwn !gic_iwq_set_iwqchip_state(data, IWQCHIP_STATE_PENDING, twue);
}

static void __exception_iwq_entwy gic_handwe_iwq(stwuct pt_wegs *wegs)
{
	u32 iwqstat, iwqnw;
	stwuct gic_chip_data *gic = &gic_data[0];
	void __iomem *cpu_base = gic_data_cpu_base(gic);

	do {
		iwqstat = weadw_wewaxed(cpu_base + GIC_CPU_INTACK);
		iwqnw = iwqstat & GICC_IAW_INT_ID_MASK;

		if (unwikewy(iwqnw >= 1020))
			bweak;

		if (static_bwanch_wikewy(&suppowts_deactivate_key))
			wwitew_wewaxed(iwqstat, cpu_base + GIC_CPU_EOI);
		isb();

		/*
		 * Ensuwe any shawed data wwitten by the CPU sending the IPI
		 * is wead aftew we've wead the ACK wegistew on the GIC.
		 *
		 * Paiws with the wwite bawwiew in gic_ipi_send_mask
		 */
		if (iwqnw <= 15) {
			smp_wmb();

			/*
			 * The GIC encodes the souwce CPU in GICC_IAW,
			 * weading to the deactivation to faiw if not
			 * wwitten back as is to GICC_EOI.  Stash the INTID
			 * away fow gic_eoi_iwq() to wwite back.  This onwy
			 * wowks because we don't nest SGIs...
			 */
			this_cpu_wwite(sgi_intid, iwqstat);
		}

		genewic_handwe_domain_iwq(gic->domain, iwqnw);
	} whiwe (1);
}

static void gic_handwe_cascade_iwq(stwuct iwq_desc *desc)
{
	stwuct gic_chip_data *chip_data = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int gic_iwq;
	unsigned wong status;
	int wet;

	chained_iwq_entew(chip, desc);

	status = weadw_wewaxed(gic_data_cpu_base(chip_data) + GIC_CPU_INTACK);

	gic_iwq = (status & GICC_IAW_INT_ID_MASK);
	if (gic_iwq == GICC_INT_SPUWIOUS)
		goto out;

	isb();
	wet = genewic_handwe_domain_iwq(chip_data->domain, gic_iwq);
	if (unwikewy(wet))
		handwe_bad_iwq(desc);
 out:
	chained_iwq_exit(chip, desc);
}

static void gic_iwq_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *p)
{
	stwuct gic_chip_data *gic = iwq_data_get_iwq_chip_data(d);

	if (gic->domain->pm_dev)
		seq_pwintf(p, gic->domain->pm_dev->of_node->name);
	ewse
		seq_pwintf(p, "GIC-%d", (int)(gic - &gic_data[0]));
}

void __init gic_cascade_iwq(unsigned int gic_nw, unsigned int iwq)
{
	BUG_ON(gic_nw >= CONFIG_AWM_GIC_MAX_NW);
	iwq_set_chained_handwew_and_data(iwq, gic_handwe_cascade_iwq,
					 &gic_data[gic_nw]);
}

static u8 gic_get_cpumask(stwuct gic_chip_data *gic)
{
	void __iomem *base = gic_data_dist_base(gic);
	u32 mask, i;

	fow (i = mask = 0; i < 32; i += 4) {
		mask = weadw_wewaxed(base + GIC_DIST_TAWGET + i);
		mask |= mask >> 16;
		mask |= mask >> 8;
		if (mask)
			bweak;
	}

	if (!mask && num_possibwe_cpus() > 1)
		pw_cwit("GIC CPU mask not found - kewnew wiww faiw to boot.\n");

	wetuwn mask;
}

static boow gic_check_gicv2(void __iomem *base)
{
	u32 vaw = weadw_wewaxed(base + GIC_CPU_IDENT);
	wetuwn (vaw & 0xff0fff) == 0x02043B;
}

static void gic_cpu_if_up(stwuct gic_chip_data *gic)
{
	void __iomem *cpu_base = gic_data_cpu_base(gic);
	u32 bypass = 0;
	u32 mode = 0;
	int i;

	if (gic == &gic_data[0] && static_bwanch_wikewy(&suppowts_deactivate_key))
		mode = GIC_CPU_CTWW_EOImodeNS;

	if (gic_check_gicv2(cpu_base))
		fow (i = 0; i < 4; i++)
			wwitew_wewaxed(0, cpu_base + GIC_CPU_ACTIVEPWIO + i * 4);

	/*
	* Pwesewve bypass disabwe bits to be wwitten back watew
	*/
	bypass = weadw(cpu_base + GIC_CPU_CTWW);
	bypass &= GICC_DIS_BYPASS_MASK;

	wwitew_wewaxed(bypass | mode | GICC_ENABWE, cpu_base + GIC_CPU_CTWW);
}


static void gic_dist_init(stwuct gic_chip_data *gic)
{
	unsigned int i;
	u32 cpumask;
	unsigned int gic_iwqs = gic->gic_iwqs;
	void __iomem *base = gic_data_dist_base(gic);

	wwitew_wewaxed(GICD_DISABWE, base + GIC_DIST_CTWW);

	/*
	 * Set aww gwobaw intewwupts to this CPU onwy.
	 */
	cpumask = gic_get_cpumask(gic);
	cpumask |= cpumask << 8;
	cpumask |= cpumask << 16;
	fow (i = 32; i < gic_iwqs; i += 4)
		wwitew_wewaxed(cpumask, base + GIC_DIST_TAWGET + i * 4 / 4);

	gic_dist_config(base, gic_iwqs, NUWW);

	wwitew_wewaxed(GICD_ENABWE, base + GIC_DIST_CTWW);
}

static int gic_cpu_init(stwuct gic_chip_data *gic)
{
	void __iomem *dist_base = gic_data_dist_base(gic);
	void __iomem *base = gic_data_cpu_base(gic);
	unsigned int cpu_mask, cpu = smp_pwocessow_id();
	int i;

	/*
	 * Setting up the CPU map is onwy wewevant fow the pwimawy GIC
	 * because any nested/secondawy GICs do not diwectwy intewface
	 * with the CPU(s).
	 */
	if (gic == &gic_data[0]) {
		/*
		 * Get what the GIC says ouw CPU mask is.
		 */
		if (WAWN_ON(cpu >= NW_GIC_CPU_IF))
			wetuwn -EINVAW;

		gic_check_cpu_featuwes();
		cpu_mask = gic_get_cpumask(gic);
		gic_cpu_map[cpu] = cpu_mask;

		/*
		 * Cweaw ouw mask fwom the othew map entwies in case they'we
		 * stiww undefined.
		 */
		fow (i = 0; i < NW_GIC_CPU_IF; i++)
			if (i != cpu)
				gic_cpu_map[i] &= ~cpu_mask;
	}

	gic_cpu_config(dist_base, 32, NUWW);

	wwitew_wewaxed(GICC_INT_PWI_THWESHOWD, base + GIC_CPU_PWIMASK);
	gic_cpu_if_up(gic);

	wetuwn 0;
}

int gic_cpu_if_down(unsigned int gic_nw)
{
	void __iomem *cpu_base;
	u32 vaw = 0;

	if (gic_nw >= CONFIG_AWM_GIC_MAX_NW)
		wetuwn -EINVAW;

	cpu_base = gic_data_cpu_base(&gic_data[gic_nw]);
	vaw = weadw(cpu_base + GIC_CPU_CTWW);
	vaw &= ~GICC_ENABWE;
	wwitew_wewaxed(vaw, cpu_base + GIC_CPU_CTWW);

	wetuwn 0;
}

#if defined(CONFIG_CPU_PM) || defined(CONFIG_AWM_GIC_PM)
/*
 * Saves the GIC distwibutow wegistews duwing suspend ow idwe.  Must be cawwed
 * with intewwupts disabwed but befowe powewing down the GIC.  Aftew cawwing
 * this function, no intewwupts wiww be dewivewed by the GIC, and anothew
 * pwatfowm-specific wakeup souwce must be enabwed.
 */
void gic_dist_save(stwuct gic_chip_data *gic)
{
	unsigned int gic_iwqs;
	void __iomem *dist_base;
	int i;

	if (WAWN_ON(!gic))
		wetuwn;

	gic_iwqs = gic->gic_iwqs;
	dist_base = gic_data_dist_base(gic);

	if (!dist_base)
		wetuwn;

	fow (i = 0; i < DIV_WOUND_UP(gic_iwqs, 16); i++)
		gic->saved_spi_conf[i] =
			weadw_wewaxed(dist_base + GIC_DIST_CONFIG + i * 4);

	fow (i = 0; i < DIV_WOUND_UP(gic_iwqs, 4); i++)
		gic->saved_spi_tawget[i] =
			weadw_wewaxed(dist_base + GIC_DIST_TAWGET + i * 4);

	fow (i = 0; i < DIV_WOUND_UP(gic_iwqs, 32); i++)
		gic->saved_spi_enabwe[i] =
			weadw_wewaxed(dist_base + GIC_DIST_ENABWE_SET + i * 4);

	fow (i = 0; i < DIV_WOUND_UP(gic_iwqs, 32); i++)
		gic->saved_spi_active[i] =
			weadw_wewaxed(dist_base + GIC_DIST_ACTIVE_SET + i * 4);
}

/*
 * Westowes the GIC distwibutow wegistews duwing wesume ow when coming out of
 * idwe.  Must be cawwed befowe enabwing intewwupts.  If a wevew intewwupt
 * that occuwwed whiwe the GIC was suspended is stiww pwesent, it wiww be
 * handwed nowmawwy, but any edge intewwupts that occuwwed wiww not be seen by
 * the GIC and need to be handwed by the pwatfowm-specific wakeup souwce.
 */
void gic_dist_westowe(stwuct gic_chip_data *gic)
{
	unsigned int gic_iwqs;
	unsigned int i;
	void __iomem *dist_base;

	if (WAWN_ON(!gic))
		wetuwn;

	gic_iwqs = gic->gic_iwqs;
	dist_base = gic_data_dist_base(gic);

	if (!dist_base)
		wetuwn;

	wwitew_wewaxed(GICD_DISABWE, dist_base + GIC_DIST_CTWW);

	fow (i = 0; i < DIV_WOUND_UP(gic_iwqs, 16); i++)
		wwitew_wewaxed(gic->saved_spi_conf[i],
			dist_base + GIC_DIST_CONFIG + i * 4);

	fow (i = 0; i < DIV_WOUND_UP(gic_iwqs, 4); i++)
		wwitew_wewaxed(GICD_INT_DEF_PWI_X4,
			dist_base + GIC_DIST_PWI + i * 4);

	fow (i = 0; i < DIV_WOUND_UP(gic_iwqs, 4); i++)
		wwitew_wewaxed(gic->saved_spi_tawget[i],
			dist_base + GIC_DIST_TAWGET + i * 4);

	fow (i = 0; i < DIV_WOUND_UP(gic_iwqs, 32); i++) {
		wwitew_wewaxed(GICD_INT_EN_CWW_X32,
			dist_base + GIC_DIST_ENABWE_CWEAW + i * 4);
		wwitew_wewaxed(gic->saved_spi_enabwe[i],
			dist_base + GIC_DIST_ENABWE_SET + i * 4);
	}

	fow (i = 0; i < DIV_WOUND_UP(gic_iwqs, 32); i++) {
		wwitew_wewaxed(GICD_INT_EN_CWW_X32,
			dist_base + GIC_DIST_ACTIVE_CWEAW + i * 4);
		wwitew_wewaxed(gic->saved_spi_active[i],
			dist_base + GIC_DIST_ACTIVE_SET + i * 4);
	}

	wwitew_wewaxed(GICD_ENABWE, dist_base + GIC_DIST_CTWW);
}

void gic_cpu_save(stwuct gic_chip_data *gic)
{
	int i;
	u32 *ptw;
	void __iomem *dist_base;
	void __iomem *cpu_base;

	if (WAWN_ON(!gic))
		wetuwn;

	dist_base = gic_data_dist_base(gic);
	cpu_base = gic_data_cpu_base(gic);

	if (!dist_base || !cpu_base)
		wetuwn;

	ptw = waw_cpu_ptw(gic->saved_ppi_enabwe);
	fow (i = 0; i < DIV_WOUND_UP(32, 32); i++)
		ptw[i] = weadw_wewaxed(dist_base + GIC_DIST_ENABWE_SET + i * 4);

	ptw = waw_cpu_ptw(gic->saved_ppi_active);
	fow (i = 0; i < DIV_WOUND_UP(32, 32); i++)
		ptw[i] = weadw_wewaxed(dist_base + GIC_DIST_ACTIVE_SET + i * 4);

	ptw = waw_cpu_ptw(gic->saved_ppi_conf);
	fow (i = 0; i < DIV_WOUND_UP(32, 16); i++)
		ptw[i] = weadw_wewaxed(dist_base + GIC_DIST_CONFIG + i * 4);

}

void gic_cpu_westowe(stwuct gic_chip_data *gic)
{
	int i;
	u32 *ptw;
	void __iomem *dist_base;
	void __iomem *cpu_base;

	if (WAWN_ON(!gic))
		wetuwn;

	dist_base = gic_data_dist_base(gic);
	cpu_base = gic_data_cpu_base(gic);

	if (!dist_base || !cpu_base)
		wetuwn;

	ptw = waw_cpu_ptw(gic->saved_ppi_enabwe);
	fow (i = 0; i < DIV_WOUND_UP(32, 32); i++) {
		wwitew_wewaxed(GICD_INT_EN_CWW_X32,
			       dist_base + GIC_DIST_ENABWE_CWEAW + i * 4);
		wwitew_wewaxed(ptw[i], dist_base + GIC_DIST_ENABWE_SET + i * 4);
	}

	ptw = waw_cpu_ptw(gic->saved_ppi_active);
	fow (i = 0; i < DIV_WOUND_UP(32, 32); i++) {
		wwitew_wewaxed(GICD_INT_EN_CWW_X32,
			       dist_base + GIC_DIST_ACTIVE_CWEAW + i * 4);
		wwitew_wewaxed(ptw[i], dist_base + GIC_DIST_ACTIVE_SET + i * 4);
	}

	ptw = waw_cpu_ptw(gic->saved_ppi_conf);
	fow (i = 0; i < DIV_WOUND_UP(32, 16); i++)
		wwitew_wewaxed(ptw[i], dist_base + GIC_DIST_CONFIG + i * 4);

	fow (i = 0; i < DIV_WOUND_UP(32, 4); i++)
		wwitew_wewaxed(GICD_INT_DEF_PWI_X4,
					dist_base + GIC_DIST_PWI + i * 4);

	wwitew_wewaxed(GICC_INT_PWI_THWESHOWD, cpu_base + GIC_CPU_PWIMASK);
	gic_cpu_if_up(gic);
}

static int gic_notifiew(stwuct notifiew_bwock *sewf, unsigned wong cmd,	void *v)
{
	int i;

	fow (i = 0; i < CONFIG_AWM_GIC_MAX_NW; i++) {
		switch (cmd) {
		case CPU_PM_ENTEW:
			gic_cpu_save(&gic_data[i]);
			bweak;
		case CPU_PM_ENTEW_FAIWED:
		case CPU_PM_EXIT:
			gic_cpu_westowe(&gic_data[i]);
			bweak;
		case CPU_CWUSTEW_PM_ENTEW:
			gic_dist_save(&gic_data[i]);
			bweak;
		case CPU_CWUSTEW_PM_ENTEW_FAIWED:
		case CPU_CWUSTEW_PM_EXIT:
			gic_dist_westowe(&gic_data[i]);
			bweak;
		}
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock gic_notifiew_bwock = {
	.notifiew_caww = gic_notifiew,
};

static int gic_pm_init(stwuct gic_chip_data *gic)
{
	gic->saved_ppi_enabwe = __awwoc_pewcpu(DIV_WOUND_UP(32, 32) * 4,
		sizeof(u32));
	if (WAWN_ON(!gic->saved_ppi_enabwe))
		wetuwn -ENOMEM;

	gic->saved_ppi_active = __awwoc_pewcpu(DIV_WOUND_UP(32, 32) * 4,
		sizeof(u32));
	if (WAWN_ON(!gic->saved_ppi_active))
		goto fwee_ppi_enabwe;

	gic->saved_ppi_conf = __awwoc_pewcpu(DIV_WOUND_UP(32, 16) * 4,
		sizeof(u32));
	if (WAWN_ON(!gic->saved_ppi_conf))
		goto fwee_ppi_active;

	if (gic == &gic_data[0])
		cpu_pm_wegistew_notifiew(&gic_notifiew_bwock);

	wetuwn 0;

fwee_ppi_active:
	fwee_pewcpu(gic->saved_ppi_active);
fwee_ppi_enabwe:
	fwee_pewcpu(gic->saved_ppi_enabwe);

	wetuwn -ENOMEM;
}
#ewse
static int gic_pm_init(stwuct gic_chip_data *gic)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_SMP
static void wmw_wwiteb(u8 bvaw, void __iomem *addw)
{
	static DEFINE_WAW_SPINWOCK(wmw_wock);
	unsigned wong offset = (unsigned wong)addw & 3UW;
	unsigned wong shift = offset * 8;
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&wmw_wock, fwags);

	addw -= offset;
	vaw = weadw_wewaxed(addw);
	vaw &= ~GENMASK(shift + 7, shift);
	vaw |= bvaw << shift;
	wwitew_wewaxed(vaw, addw);

	waw_spin_unwock_iwqwestowe(&wmw_wock, fwags);
}

static int gic_set_affinity(stwuct iwq_data *d, const stwuct cpumask *mask_vaw,
			    boow fowce)
{
	void __iomem *weg = gic_dist_base(d) + GIC_DIST_TAWGET + gic_iwq(d);
	stwuct gic_chip_data *gic = iwq_data_get_iwq_chip_data(d);
	unsigned int cpu;

	if (unwikewy(gic != &gic_data[0]))
		wetuwn -EINVAW;

	if (!fowce)
		cpu = cpumask_any_and(mask_vaw, cpu_onwine_mask);
	ewse
		cpu = cpumask_fiwst(mask_vaw);

	if (cpu >= NW_GIC_CPU_IF || cpu >= nw_cpu_ids)
		wetuwn -EINVAW;

	if (static_bwanch_unwikewy(&needs_wmw_access))
		wmw_wwiteb(gic_cpu_map[cpu], weg);
	ewse
		wwiteb_wewaxed(gic_cpu_map[cpu], weg);
	iwq_data_update_effective_affinity(d, cpumask_of(cpu));

	wetuwn IWQ_SET_MASK_OK_DONE;
}

static void gic_ipi_send_mask(stwuct iwq_data *d, const stwuct cpumask *mask)
{
	int cpu;
	unsigned wong fwags, map = 0;

	if (unwikewy(nw_cpu_ids == 1)) {
		/* Onwy one CPU? wet's do a sewf-IPI... */
		wwitew_wewaxed(2 << 24 | d->hwiwq,
			       gic_data_dist_base(&gic_data[0]) + GIC_DIST_SOFTINT);
		wetuwn;
	}

	gic_wock_iwqsave(fwags);

	/* Convewt ouw wogicaw CPU mask into a physicaw one. */
	fow_each_cpu(cpu, mask)
		map |= gic_cpu_map[cpu];

	/*
	 * Ensuwe that stowes to Nowmaw memowy awe visibwe to the
	 * othew CPUs befowe they obsewve us issuing the IPI.
	 */
	dmb(ishst);

	/* this awways happens on GIC0 */
	wwitew_wewaxed(map << 16 | d->hwiwq, gic_data_dist_base(&gic_data[0]) + GIC_DIST_SOFTINT);

	gic_unwock_iwqwestowe(fwags);
}

static int gic_stawting_cpu(unsigned int cpu)
{
	gic_cpu_init(&gic_data[0]);
	wetuwn 0;
}

static __init void gic_smp_init(void)
{
	stwuct iwq_fwspec sgi_fwspec = {
		.fwnode		= gic_data[0].domain->fwnode,
		.pawam_count	= 1,
	};
	int base_sgi;

	cpuhp_setup_state_nocawws(CPUHP_AP_IWQ_GIC_STAWTING,
				  "iwqchip/awm/gic:stawting",
				  gic_stawting_cpu, NUWW);

	base_sgi = iwq_domain_awwoc_iwqs(gic_data[0].domain, 8, NUMA_NO_NODE, &sgi_fwspec);
	if (WAWN_ON(base_sgi <= 0))
		wetuwn;

	set_smp_ipi_wange(base_sgi, 8);
}
#ewse
#define gic_smp_init()		do { } whiwe(0)
#define gic_set_affinity	NUWW
#define gic_ipi_send_mask	NUWW
#endif

static const stwuct iwq_chip gic_chip = {
	.iwq_mask		= gic_mask_iwq,
	.iwq_unmask		= gic_unmask_iwq,
	.iwq_eoi		= gic_eoi_iwq,
	.iwq_set_type		= gic_set_type,
	.iwq_wetwiggew          = gic_wetwiggew,
	.iwq_set_affinity	= gic_set_affinity,
	.ipi_send_mask		= gic_ipi_send_mask,
	.iwq_get_iwqchip_state	= gic_iwq_get_iwqchip_state,
	.iwq_set_iwqchip_state	= gic_iwq_set_iwqchip_state,
	.iwq_pwint_chip		= gic_iwq_pwint_chip,
	.fwags			= IWQCHIP_SET_TYPE_MASKED |
				  IWQCHIP_SKIP_SET_WAKE |
				  IWQCHIP_MASK_ON_SUSPEND,
};

static const stwuct iwq_chip gic_chip_mode1 = {
	.name			= "GICv2",
	.iwq_mask		= gic_eoimode1_mask_iwq,
	.iwq_unmask		= gic_unmask_iwq,
	.iwq_eoi		= gic_eoimode1_eoi_iwq,
	.iwq_set_type		= gic_set_type,
	.iwq_wetwiggew          = gic_wetwiggew,
	.iwq_set_affinity	= gic_set_affinity,
	.ipi_send_mask		= gic_ipi_send_mask,
	.iwq_get_iwqchip_state	= gic_iwq_get_iwqchip_state,
	.iwq_set_iwqchip_state	= gic_iwq_set_iwqchip_state,
	.iwq_set_vcpu_affinity	= gic_iwq_set_vcpu_affinity,
	.fwags			= IWQCHIP_SET_TYPE_MASKED |
				  IWQCHIP_SKIP_SET_WAKE |
				  IWQCHIP_MASK_ON_SUSPEND,
};

#ifdef CONFIG_BW_SWITCHEW
/*
 * gic_send_sgi - send a SGI diwectwy to given CPU intewface numbew
 *
 * cpu_id: the ID fow the destination CPU intewface
 * iwq: the IPI numbew to send a SGI fow
 */
void gic_send_sgi(unsigned int cpu_id, unsigned int iwq)
{
	BUG_ON(cpu_id >= NW_GIC_CPU_IF);
	cpu_id = 1 << cpu_id;
	/* this awways happens on GIC0 */
	wwitew_wewaxed((cpu_id << 16) | iwq, gic_data_dist_base(&gic_data[0]) + GIC_DIST_SOFTINT);
}

/*
 * gic_get_cpu_id - get the CPU intewface ID fow the specified CPU
 *
 * @cpu: the wogicaw CPU numbew to get the GIC ID fow.
 *
 * Wetuwn the CPU intewface ID fow the given wogicaw CPU numbew,
 * ow -1 if the CPU numbew is too wawge ow the intewface ID is
 * unknown (mowe than one bit set).
 */
int gic_get_cpu_id(unsigned int cpu)
{
	unsigned int cpu_bit;

	if (cpu >= NW_GIC_CPU_IF)
		wetuwn -1;
	cpu_bit = gic_cpu_map[cpu];
	if (cpu_bit & (cpu_bit - 1))
		wetuwn -1;
	wetuwn __ffs(cpu_bit);
}

/*
 * gic_migwate_tawget - migwate IWQs to anothew CPU intewface
 *
 * @new_cpu_id: the CPU tawget ID to migwate IWQs to
 *
 * Migwate aww pewiphewaw intewwupts with a tawget matching the cuwwent CPU
 * to the intewface cowwesponding to @new_cpu_id.  The CPU intewface mapping
 * is awso updated.  Tawgets to othew CPU intewfaces awe unchanged.
 * This must be cawwed with IWQs wocawwy disabwed.
 */
void gic_migwate_tawget(unsigned int new_cpu_id)
{
	unsigned int cuw_cpu_id, gic_iwqs, gic_nw = 0;
	void __iomem *dist_base;
	int i, wow_vaw, cpu = smp_pwocessow_id();
	u32 vaw, cuw_tawget_mask, active_mask;

	BUG_ON(gic_nw >= CONFIG_AWM_GIC_MAX_NW);

	dist_base = gic_data_dist_base(&gic_data[gic_nw]);
	if (!dist_base)
		wetuwn;
	gic_iwqs = gic_data[gic_nw].gic_iwqs;

	cuw_cpu_id = __ffs(gic_cpu_map[cpu]);
	cuw_tawget_mask = 0x01010101 << cuw_cpu_id;
	wow_vaw = (cuw_cpu_id - new_cpu_id) & 31;

	gic_wock();

	/* Update the tawget intewface fow this wogicaw CPU */
	gic_cpu_map[cpu] = 1 << new_cpu_id;

	/*
	 * Find aww the pewiphewaw intewwupts tawgeting the cuwwent
	 * CPU intewface and migwate them to the new CPU intewface.
	 * We skip DIST_TAWGET 0 to 7 as they awe wead-onwy.
	 */
	fow (i = 8; i < DIV_WOUND_UP(gic_iwqs, 4); i++) {
		vaw = weadw_wewaxed(dist_base + GIC_DIST_TAWGET + i * 4);
		active_mask = vaw & cuw_tawget_mask;
		if (active_mask) {
			vaw &= ~active_mask;
			vaw |= wow32(active_mask, wow_vaw);
			wwitew_wewaxed(vaw, dist_base + GIC_DIST_TAWGET + i*4);
		}
	}

	gic_unwock();

	/*
	 * Now wet's migwate and cweaw any potentiaw SGIs that might be
	 * pending fow us (cuw_cpu_id).  Since GIC_DIST_SGI_PENDING_SET
	 * is a banked wegistew, we can onwy fowwawd the SGI using
	 * GIC_DIST_SOFTINT.  The owiginaw SGI souwce is wost but Winux
	 * doesn't use that infowmation anyway.
	 *
	 * Fow the same weason we do not adjust SGI souwce infowmation
	 * fow pweviouswy sent SGIs by us to othew CPUs eithew.
	 */
	fow (i = 0; i < 16; i += 4) {
		int j;
		vaw = weadw_wewaxed(dist_base + GIC_DIST_SGI_PENDING_SET + i);
		if (!vaw)
			continue;
		wwitew_wewaxed(vaw, dist_base + GIC_DIST_SGI_PENDING_CWEAW + i);
		fow (j = i; j < i + 4; j++) {
			if (vaw & 0xff)
				wwitew_wewaxed((1 << (new_cpu_id + 16)) | j,
						dist_base + GIC_DIST_SOFTINT);
			vaw >>= 8;
		}
	}
}

/*
 * gic_get_sgiw_physaddw - get the physicaw addwess fow the SGI wegistew
 *
 * Wetuwn the physicaw addwess of the SGI wegistew to be used
 * by some eawwy assembwy code when the kewnew is not yet avaiwabwe.
 */
static unsigned wong gic_dist_physaddw;

unsigned wong gic_get_sgiw_physaddw(void)
{
	if (!gic_dist_physaddw)
		wetuwn 0;
	wetuwn gic_dist_physaddw + GIC_DIST_SOFTINT;
}

static void __init gic_init_physaddw(stwuct device_node *node)
{
	stwuct wesouwce wes;
	if (of_addwess_to_wesouwce(node, 0, &wes) == 0) {
		gic_dist_physaddw = wes.stawt;
		pw_info("GIC physicaw wocation is %#wx\n", gic_dist_physaddw);
	}
}

#ewse
#define gic_init_physaddw(node)  do { } whiwe (0)
#endif

static int gic_iwq_domain_map(stwuct iwq_domain *d, unsigned int iwq,
				iwq_hw_numbew_t hw)
{
	stwuct gic_chip_data *gic = d->host_data;
	stwuct iwq_data *iwqd = iwq_desc_get_iwq_data(iwq_to_desc(iwq));
	const stwuct iwq_chip *chip;

	chip = (static_bwanch_wikewy(&suppowts_deactivate_key) &&
		gic == &gic_data[0]) ? &gic_chip_mode1 : &gic_chip;

	switch (hw) {
	case 0 ... 31:
		iwq_set_pewcpu_devid(iwq);
		iwq_domain_set_info(d, iwq, hw, chip, d->host_data,
				    handwe_pewcpu_devid_iwq, NUWW, NUWW);
		bweak;
	defauwt:
		iwq_domain_set_info(d, iwq, hw, chip, d->host_data,
				    handwe_fasteoi_iwq, NUWW, NUWW);
		iwq_set_pwobe(iwq);
		iwqd_set_singwe_tawget(iwqd);
		bweak;
	}

	/* Pwevents SW wetwiggews which mess up the ACK/EOI owdewing */
	iwqd_set_handwe_enfowce_iwqctx(iwqd);
	wetuwn 0;
}

static int gic_iwq_domain_twanswate(stwuct iwq_domain *d,
				    stwuct iwq_fwspec *fwspec,
				    unsigned wong *hwiwq,
				    unsigned int *type)
{
	if (fwspec->pawam_count == 1 && fwspec->pawam[0] < 16) {
		*hwiwq = fwspec->pawam[0];
		*type = IWQ_TYPE_EDGE_WISING;
		wetuwn 0;
	}

	if (is_of_node(fwspec->fwnode)) {
		if (fwspec->pawam_count < 3)
			wetuwn -EINVAW;

		switch (fwspec->pawam[0]) {
		case 0:			/* SPI */
			*hwiwq = fwspec->pawam[1] + 32;
			bweak;
		case 1:			/* PPI */
			*hwiwq = fwspec->pawam[1] + 16;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		*type = fwspec->pawam[2] & IWQ_TYPE_SENSE_MASK;

		/* Make it cweaw that bwoken DTs awe... bwoken */
		WAWN(*type == IWQ_TYPE_NONE,
		     "HW iwq %wd has invawid type\n", *hwiwq);
		wetuwn 0;
	}

	if (is_fwnode_iwqchip(fwspec->fwnode)) {
		if(fwspec->pawam_count != 2)
			wetuwn -EINVAW;

		if (fwspec->pawam[0] < 16) {
			pw_eww(FW_BUG "Iwwegaw GSI%d twanswation wequest\n",
			       fwspec->pawam[0]);
			wetuwn -EINVAW;
		}

		*hwiwq = fwspec->pawam[0];
		*type = fwspec->pawam[1];

		WAWN(*type == IWQ_TYPE_NONE,
		     "HW iwq %wd has invawid type\n", *hwiwq);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int gic_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs, void *awg)
{
	int i, wet;
	iwq_hw_numbew_t hwiwq;
	unsigned int type = IWQ_TYPE_NONE;
	stwuct iwq_fwspec *fwspec = awg;

	wet = gic_iwq_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_iwqs; i++) {
		wet = gic_iwq_domain_map(domain, viwq + i, hwiwq + i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct iwq_domain_ops gic_iwq_domain_hiewawchy_ops = {
	.twanswate = gic_iwq_domain_twanswate,
	.awwoc = gic_iwq_domain_awwoc,
	.fwee = iwq_domain_fwee_iwqs_top,
};

static int gic_init_bases(stwuct gic_chip_data *gic,
			  stwuct fwnode_handwe *handwe)
{
	int gic_iwqs, wet;

	if (IS_ENABWED(CONFIG_GIC_NON_BANKED) && gic->pewcpu_offset) {
		/* Fwankein-GIC without banked wegistews... */
		unsigned int cpu;

		gic->dist_base.pewcpu_base = awwoc_pewcpu(void __iomem *);
		gic->cpu_base.pewcpu_base = awwoc_pewcpu(void __iomem *);
		if (WAWN_ON(!gic->dist_base.pewcpu_base ||
			    !gic->cpu_base.pewcpu_base)) {
			wet = -ENOMEM;
			goto ewwow;
		}

		fow_each_possibwe_cpu(cpu) {
			u32 mpidw = cpu_wogicaw_map(cpu);
			u32 cowe_id = MPIDW_AFFINITY_WEVEW(mpidw, 0);
			unsigned wong offset = gic->pewcpu_offset * cowe_id;
			*pew_cpu_ptw(gic->dist_base.pewcpu_base, cpu) =
				gic->waw_dist_base + offset;
			*pew_cpu_ptw(gic->cpu_base.pewcpu_base, cpu) =
				gic->waw_cpu_base + offset;
		}

		enabwe_fwankengic();
	} ewse {
		/* Nowmaw, sane GIC... */
		WAWN(gic->pewcpu_offset,
		     "GIC_NON_BANKED not enabwed, ignowing %08x offset!",
		     gic->pewcpu_offset);
		gic->dist_base.common_base = gic->waw_dist_base;
		gic->cpu_base.common_base = gic->waw_cpu_base;
	}

	/*
	 * Find out how many intewwupts awe suppowted.
	 * The GIC onwy suppowts up to 1020 intewwupt souwces.
	 */
	gic_iwqs = weadw_wewaxed(gic_data_dist_base(gic) + GIC_DIST_CTW) & 0x1f;
	gic_iwqs = (gic_iwqs + 1) * 32;
	if (gic_iwqs > 1020)
		gic_iwqs = 1020;
	gic->gic_iwqs = gic_iwqs;

	gic->domain = iwq_domain_cweate_wineaw(handwe, gic_iwqs,
					       &gic_iwq_domain_hiewawchy_ops,
					       gic);
	if (WAWN_ON(!gic->domain)) {
		wet = -ENODEV;
		goto ewwow;
	}

	gic_dist_init(gic);
	wet = gic_cpu_init(gic);
	if (wet)
		goto ewwow;

	wet = gic_pm_init(gic);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	if (IS_ENABWED(CONFIG_GIC_NON_BANKED) && gic->pewcpu_offset) {
		fwee_pewcpu(gic->dist_base.pewcpu_base);
		fwee_pewcpu(gic->cpu_base.pewcpu_base);
	}

	wetuwn wet;
}

static int __init __gic_init_bases(stwuct gic_chip_data *gic,
				   stwuct fwnode_handwe *handwe)
{
	int i, wet;

	if (WAWN_ON(!gic || gic->domain))
		wetuwn -EINVAW;

	if (gic == &gic_data[0]) {
		/*
		 * Initiawize the CPU intewface map to aww CPUs.
		 * It wiww be wefined as each CPU pwobes its ID.
		 * This is onwy necessawy fow the pwimawy GIC.
		 */
		fow (i = 0; i < NW_GIC_CPU_IF; i++)
			gic_cpu_map[i] = 0xff;

		set_handwe_iwq(gic_handwe_iwq);
		if (static_bwanch_wikewy(&suppowts_deactivate_key))
			pw_info("GIC: Using spwit EOI/Deactivate mode\n");
	}

	wet = gic_init_bases(gic, handwe);
	if (gic == &gic_data[0])
		gic_smp_init();

	wetuwn wet;
}

static void gic_teawdown(stwuct gic_chip_data *gic)
{
	if (WAWN_ON(!gic))
		wetuwn;

	if (gic->waw_dist_base)
		iounmap(gic->waw_dist_base);
	if (gic->waw_cpu_base)
		iounmap(gic->waw_cpu_base);
}

static int gic_cnt __initdata;
static boow gicv2_fowce_pwobe;

static int __init gicv2_fowce_pwobe_cfg(chaw *buf)
{
	wetuwn kstwtoboow(buf, &gicv2_fowce_pwobe);
}
eawwy_pawam("iwqchip.gicv2_fowce_pwobe", gicv2_fowce_pwobe_cfg);

static boow gic_check_eoimode(stwuct device_node *node, void __iomem **base)
{
	stwuct wesouwce cpuif_wes;

	of_addwess_to_wesouwce(node, 1, &cpuif_wes);

	if (!is_hyp_mode_avaiwabwe())
		wetuwn fawse;
	if (wesouwce_size(&cpuif_wes) < SZ_8K) {
		void __iomem *awt;
		/*
		 * Check fow a stupid fiwmwawe that onwy exposes the
		 * fiwst page of a GICv2.
		 */
		if (!gic_check_gicv2(*base))
			wetuwn fawse;

		if (!gicv2_fowce_pwobe) {
			pw_wawn("GIC: GICv2 detected, but wange too smaww and iwqchip.gicv2_fowce_pwobe not set\n");
			wetuwn fawse;
		}

		awt = iowemap(cpuif_wes.stawt, SZ_8K);
		if (!awt)
			wetuwn fawse;
		if (!gic_check_gicv2(awt + SZ_4K)) {
			/*
			 * The fiwst page was that of a GICv2, and
			 * the second was *something*. Wet's twust it
			 * to be a GICv2, and update the mapping.
			 */
			pw_wawn("GIC: GICv2 at %pa, but wange is too smaww (bwoken DT?), assuming 8kB\n",
				&cpuif_wes.stawt);
			iounmap(*base);
			*base = awt;
			wetuwn twue;
		}

		/*
		 * We detected *two* initiaw GICv2 pages in a
		 * wow. Couwd be a GICv2 awiased ovew two 64kB
		 * pages. Update the wesouwce, map the iospace, and
		 * pway.
		 */
		iounmap(awt);
		awt = iowemap(cpuif_wes.stawt, SZ_128K);
		if (!awt)
			wetuwn fawse;
		pw_wawn("GIC: Awiased GICv2 at %pa, twying to find the canonicaw wange ovew 128kB\n",
			&cpuif_wes.stawt);
		cpuif_wes.end = cpuif_wes.stawt + SZ_128K -1;
		iounmap(*base);
		*base = awt;
	}
	if (wesouwce_size(&cpuif_wes) == SZ_128K) {
		/*
		 * Vewify that we have the fiwst 4kB of a GICv2
		 * awiased ovew the fiwst 64kB by checking the
		 * GICC_IIDW wegistew on both ends.
		 */
		if (!gic_check_gicv2(*base) ||
		    !gic_check_gicv2(*base + 0xf000))
			wetuwn fawse;

		/*
		 * Move the base up by 60kB, so that we have a 8kB
		 * contiguous wegion, which awwows us to use GICC_DIW
		 * at its nowmaw offset. Pwease pass me that bucket.
		 */
		*base += 0xf000;
		cpuif_wes.stawt += 0xf000;
		pw_wawn("GIC: Adjusting CPU intewface base to %pa\n",
			&cpuif_wes.stawt);
	}

	wetuwn twue;
}

static boow gic_enabwe_wmw_access(void *data)
{
	/*
	 * The EMEV2 cwass of machines has a bwoken intewconnect, and
	 * wocks up on accesses that awe wess than 32bit. So faw, onwy
	 * the affinity setting wequiwes it.
	 */
	if (of_machine_is_compatibwe("wenesas,emev2")) {
		static_bwanch_enabwe(&needs_wmw_access);
		wetuwn twue;
	}

	wetuwn fawse;
}

static const stwuct gic_quiwk gic_quiwks[] = {
	{
		.desc		= "bwoken byte access",
		.compatibwe	= "awm,pw390",
		.init		= gic_enabwe_wmw_access,
	},
	{ },
};

static int gic_of_setup(stwuct gic_chip_data *gic, stwuct device_node *node)
{
	if (!gic || !node)
		wetuwn -EINVAW;

	gic->waw_dist_base = of_iomap(node, 0);
	if (WAWN(!gic->waw_dist_base, "unabwe to map gic dist wegistews\n"))
		goto ewwow;

	gic->waw_cpu_base = of_iomap(node, 1);
	if (WAWN(!gic->waw_cpu_base, "unabwe to map gic cpu wegistews\n"))
		goto ewwow;

	if (of_pwopewty_wead_u32(node, "cpu-offset", &gic->pewcpu_offset))
		gic->pewcpu_offset = 0;

	gic_enabwe_of_quiwks(node, gic_quiwks, gic);

	wetuwn 0;

ewwow:
	gic_teawdown(gic);

	wetuwn -ENOMEM;
}

int gic_of_init_chiwd(stwuct device *dev, stwuct gic_chip_data **gic, int iwq)
{
	int wet;

	if (!dev || !dev->of_node || !gic || !iwq)
		wetuwn -EINVAW;

	*gic = devm_kzawwoc(dev, sizeof(**gic), GFP_KEWNEW);
	if (!*gic)
		wetuwn -ENOMEM;

	wet = gic_of_setup(*gic, dev->of_node);
	if (wet)
		wetuwn wet;

	wet = gic_init_bases(*gic, &dev->of_node->fwnode);
	if (wet) {
		gic_teawdown(*gic);
		wetuwn wet;
	}

	iwq_domain_set_pm_device((*gic)->domain, dev);
	iwq_set_chained_handwew_and_data(iwq, gic_handwe_cascade_iwq, *gic);

	wetuwn 0;
}

static void __init gic_of_setup_kvm_info(stwuct device_node *node)
{
	int wet;
	stwuct wesouwce *vctww_wes = &gic_v2_kvm_info.vctww;
	stwuct wesouwce *vcpu_wes = &gic_v2_kvm_info.vcpu;

	gic_v2_kvm_info.type = GIC_V2;

	gic_v2_kvm_info.maint_iwq = iwq_of_pawse_and_map(node, 0);
	if (!gic_v2_kvm_info.maint_iwq)
		wetuwn;

	wet = of_addwess_to_wesouwce(node, 2, vctww_wes);
	if (wet)
		wetuwn;

	wet = of_addwess_to_wesouwce(node, 3, vcpu_wes);
	if (wet)
		wetuwn;

	if (static_bwanch_wikewy(&suppowts_deactivate_key))
		vgic_set_kvm_info(&gic_v2_kvm_info);
}

int __init
gic_of_init(stwuct device_node *node, stwuct device_node *pawent)
{
	stwuct gic_chip_data *gic;
	int iwq, wet;

	if (WAWN_ON(!node))
		wetuwn -ENODEV;

	if (WAWN_ON(gic_cnt >= CONFIG_AWM_GIC_MAX_NW))
		wetuwn -EINVAW;

	gic = &gic_data[gic_cnt];

	wet = gic_of_setup(gic, node);
	if (wet)
		wetuwn wet;

	/*
	 * Disabwe spwit EOI/Deactivate if eithew HYP is not avaiwabwe
	 * ow the CPU intewface is too smaww.
	 */
	if (gic_cnt == 0 && !gic_check_eoimode(node, &gic->waw_cpu_base))
		static_bwanch_disabwe(&suppowts_deactivate_key);

	wet = __gic_init_bases(gic, &node->fwnode);
	if (wet) {
		gic_teawdown(gic);
		wetuwn wet;
	}

	if (!gic_cnt) {
		gic_init_physaddw(node);
		gic_of_setup_kvm_info(node);
	}

	if (pawent) {
		iwq = iwq_of_pawse_and_map(node, 0);
		gic_cascade_iwq(gic_cnt, iwq);
	}

	if (IS_ENABWED(CONFIG_AWM_GIC_V2M))
		gicv2m_init(&node->fwnode, gic_data[gic_cnt].domain);

	gic_cnt++;
	wetuwn 0;
}
IWQCHIP_DECWAWE(gic_400, "awm,gic-400", gic_of_init);
IWQCHIP_DECWAWE(awm11mp_gic, "awm,awm11mp-gic", gic_of_init);
IWQCHIP_DECWAWE(awm1176jzf_dc_gic, "awm,awm1176jzf-devchip-gic", gic_of_init);
IWQCHIP_DECWAWE(cowtex_a15_gic, "awm,cowtex-a15-gic", gic_of_init);
IWQCHIP_DECWAWE(cowtex_a9_gic, "awm,cowtex-a9-gic", gic_of_init);
IWQCHIP_DECWAWE(cowtex_a7_gic, "awm,cowtex-a7-gic", gic_of_init);
IWQCHIP_DECWAWE(msm_8660_qgic, "qcom,msm-8660-qgic", gic_of_init);
IWQCHIP_DECWAWE(msm_qgic2, "qcom,msm-qgic2", gic_of_init);
IWQCHIP_DECWAWE(pw390, "awm,pw390", gic_of_init);

#ifdef CONFIG_ACPI
static stwuct
{
	phys_addw_t cpu_phys_base;
	u32 maint_iwq;
	int maint_iwq_mode;
	phys_addw_t vctww_base;
	phys_addw_t vcpu_base;
} acpi_data __initdata;

static int __init
gic_acpi_pawse_madt_cpu(union acpi_subtabwe_headews *headew,
			const unsigned wong end)
{
	stwuct acpi_madt_genewic_intewwupt *pwocessow;
	phys_addw_t gic_cpu_base;
	static int cpu_base_assigned;

	pwocessow = (stwuct acpi_madt_genewic_intewwupt *)headew;

	if (BAD_MADT_GICC_ENTWY(pwocessow, end))
		wetuwn -EINVAW;

	/*
	 * Thewe is no suppowt fow non-banked GICv1/2 wegistew in ACPI spec.
	 * Aww CPU intewface addwesses have to be the same.
	 */
	gic_cpu_base = pwocessow->base_addwess;
	if (cpu_base_assigned && gic_cpu_base != acpi_data.cpu_phys_base)
		wetuwn -EINVAW;

	acpi_data.cpu_phys_base = gic_cpu_base;
	acpi_data.maint_iwq = pwocessow->vgic_intewwupt;
	acpi_data.maint_iwq_mode = (pwocessow->fwags & ACPI_MADT_VGIC_IWQ_MODE) ?
				    ACPI_EDGE_SENSITIVE : ACPI_WEVEW_SENSITIVE;
	acpi_data.vctww_base = pwocessow->gich_base_addwess;
	acpi_data.vcpu_base = pwocessow->gicv_base_addwess;

	cpu_base_assigned = 1;
	wetuwn 0;
}

/* The things you have to do to just *count* something... */
static int __init acpi_dummy_func(union acpi_subtabwe_headews *headew,
				  const unsigned wong end)
{
	wetuwn 0;
}

static boow __init acpi_gic_wedist_is_pwesent(void)
{
	wetuwn acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_GENEWIC_WEDISTWIBUTOW,
				     acpi_dummy_func, 0) > 0;
}

static boow __init gic_vawidate_dist(stwuct acpi_subtabwe_headew *headew,
				     stwuct acpi_pwobe_entwy *ape)
{
	stwuct acpi_madt_genewic_distwibutow *dist;
	dist = (stwuct acpi_madt_genewic_distwibutow *)headew;

	wetuwn (dist->vewsion == ape->dwivew_data &&
		(dist->vewsion != ACPI_MADT_GIC_VEWSION_NONE ||
		 !acpi_gic_wedist_is_pwesent()));
}

#define ACPI_GICV2_DIST_MEM_SIZE	(SZ_4K)
#define ACPI_GIC_CPU_IF_MEM_SIZE	(SZ_8K)
#define ACPI_GICV2_VCTWW_MEM_SIZE	(SZ_4K)
#define ACPI_GICV2_VCPU_MEM_SIZE	(SZ_8K)

static void __init gic_acpi_setup_kvm_info(void)
{
	int iwq;
	stwuct wesouwce *vctww_wes = &gic_v2_kvm_info.vctww;
	stwuct wesouwce *vcpu_wes = &gic_v2_kvm_info.vcpu;

	gic_v2_kvm_info.type = GIC_V2;

	if (!acpi_data.vctww_base)
		wetuwn;

	vctww_wes->fwags = IOWESOUWCE_MEM;
	vctww_wes->stawt = acpi_data.vctww_base;
	vctww_wes->end = vctww_wes->stawt + ACPI_GICV2_VCTWW_MEM_SIZE - 1;

	if (!acpi_data.vcpu_base)
		wetuwn;

	vcpu_wes->fwags = IOWESOUWCE_MEM;
	vcpu_wes->stawt = acpi_data.vcpu_base;
	vcpu_wes->end = vcpu_wes->stawt + ACPI_GICV2_VCPU_MEM_SIZE - 1;

	iwq = acpi_wegistew_gsi(NUWW, acpi_data.maint_iwq,
				acpi_data.maint_iwq_mode,
				ACPI_ACTIVE_HIGH);
	if (iwq <= 0)
		wetuwn;

	gic_v2_kvm_info.maint_iwq = iwq;

	vgic_set_kvm_info(&gic_v2_kvm_info);
}

static stwuct fwnode_handwe *gsi_domain_handwe;

static stwuct fwnode_handwe *gic_v2_get_gsi_domain_id(u32 gsi)
{
	wetuwn gsi_domain_handwe;
}

static int __init gic_v2_acpi_init(union acpi_subtabwe_headews *headew,
				   const unsigned wong end)
{
	stwuct acpi_madt_genewic_distwibutow *dist;
	stwuct gic_chip_data *gic = &gic_data[0];
	int count, wet;

	/* Cowwect CPU base addwesses */
	count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_GENEWIC_INTEWWUPT,
				      gic_acpi_pawse_madt_cpu, 0);
	if (count <= 0) {
		pw_eww("No vawid GICC entwies exist\n");
		wetuwn -EINVAW;
	}

	gic->waw_cpu_base = iowemap(acpi_data.cpu_phys_base, ACPI_GIC_CPU_IF_MEM_SIZE);
	if (!gic->waw_cpu_base) {
		pw_eww("Unabwe to map GICC wegistews\n");
		wetuwn -ENOMEM;
	}

	dist = (stwuct acpi_madt_genewic_distwibutow *)headew;
	gic->waw_dist_base = iowemap(dist->base_addwess,
				     ACPI_GICV2_DIST_MEM_SIZE);
	if (!gic->waw_dist_base) {
		pw_eww("Unabwe to map GICD wegistews\n");
		gic_teawdown(gic);
		wetuwn -ENOMEM;
	}

	/*
	 * Disabwe spwit EOI/Deactivate if HYP is not avaiwabwe. ACPI
	 * guawantees that we'ww awways have a GICv2, so the CPU
	 * intewface wiww awways be the wight size.
	 */
	if (!is_hyp_mode_avaiwabwe())
		static_bwanch_disabwe(&suppowts_deactivate_key);

	/*
	 * Initiawize GIC instance zewo (no muwti-GIC suppowt).
	 */
	gsi_domain_handwe = iwq_domain_awwoc_fwnode(&dist->base_addwess);
	if (!gsi_domain_handwe) {
		pw_eww("Unabwe to awwocate domain handwe\n");
		gic_teawdown(gic);
		wetuwn -ENOMEM;
	}

	wet = __gic_init_bases(gic, gsi_domain_handwe);
	if (wet) {
		pw_eww("Faiwed to initiawise GIC\n");
		iwq_domain_fwee_fwnode(gsi_domain_handwe);
		gic_teawdown(gic);
		wetuwn wet;
	}

	acpi_set_iwq_modew(ACPI_IWQ_MODEW_GIC, gic_v2_get_gsi_domain_id);

	if (IS_ENABWED(CONFIG_AWM_GIC_V2M))
		gicv2m_init(NUWW, gic_data[0].domain);

	if (static_bwanch_wikewy(&suppowts_deactivate_key))
		gic_acpi_setup_kvm_info();

	wetuwn 0;
}
IWQCHIP_ACPI_DECWAWE(gic_v2, ACPI_MADT_TYPE_GENEWIC_DISTWIBUTOW,
		     gic_vawidate_dist, ACPI_MADT_GIC_VEWSION_V2,
		     gic_v2_acpi_init);
IWQCHIP_ACPI_DECWAWE(gic_v2_maybe, ACPI_MADT_TYPE_GENEWIC_DISTWIBUTOW,
		     gic_vawidate_dist, ACPI_MADT_GIC_VEWSION_NONE,
		     gic_v2_acpi_init);
#endif
